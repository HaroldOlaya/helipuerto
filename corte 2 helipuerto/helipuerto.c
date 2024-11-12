#include <16f877a.h>
#include <math.h>  // Incluir la librería math.h para usar atan

#fuses HS, NOWDT, NOPROTECT, NOPUT, NOLVP, NOBROWNOUT
#use delay(clock=20000000)
#use I2C(MASTER, SDA=PIN_C4, SCL=PIN_C3, SLOW)

#use standard_io(D)
#use standard_io(A)
#define use_servo_1 
#define use_servo_2 

#define servo_1 PIN_A0   // Pin del servo 1
#define servo_2 PIN_A1   // Pin del servo 2

#include <lcd.c>
#include <MPU6050.c>
#include <servo_st.c>

float Ax, Ay, Az, Gx, Gy, Gz, t;
int angle_x, angle_y;

float Kp_x = 1.0, Ki_x = 0.1, Kd_x = 0.05;  
float Kp_y = 1.0, Ki_y = 0.1, Kd_y = 0.05;  
float error_x, error_y;                     
float prev_error_x = 0, prev_error_y = 0;  
float integral_x = 0, integral_y = 0;       
float output_x, output_y;

int menu_option = 0;  // Variable para almacenar la opción del menú
int adjusting = 0;    // Bandera para saber si estamos en modo ajuste

#INT_RB
void RB_isr() {
    // Detectar qué botón se presiona y realizar la acción correspondiente
    if (input(PIN_B0)) {  // Entrada al modo de ajuste
        adjusting = 1;    // Activar modo de ajuste
        menu_option = 0;  // Empezar desde la primera opción
        delay_ms(200);    // Debouncing
    } 
    if (adjusting) {
        if (input(PIN_B1)) {  // Botón para aumentar el valor
            switch(menu_option) {
                case 0: Kp_x += 0.1; break;
                case 1: Ki_x += 0.01; break;
                case 2: Kd_x += 0.01; break;
                case 3: Kp_y += 0.1; break;
                case 4: Ki_y += 0.01; break;
                case 5: Kd_y += 0.01; break;
            }
            delay_ms(200);
        }
        if (input(PIN_B2)) {  // Botón para disminuir el valor
            switch(menu_option) {
                case 0: Kp_x -= 0.1; if (Kp_x < 0) Kp_x = 0; break;
                case 1: Ki_x -= 0.01; if (Ki_x < 0) Ki_x = 0; break;
                case 2: Kd_x -= 0.01; if (Kd_x < 0) Kd_x = 0; break;
                case 3: Kp_y -= 0.1; if (Kp_y < 0) Kp_y = 0; break;
                case 4: Ki_y -= 0.01; if (Ki_y < 0) Ki_y = 0; break;
                case 5: Kd_y -= 0.01; if (Kd_y < 0) Kd_y = 0; break;
            }
            delay_ms(200);
        }
        if (input(PIN_B3)) {  // Botón OK para pasar a la siguiente opción
            menu_option++;
            if (menu_option > 5) {  // Volver a la primera opción al final
                adjusting = 0;  // Salir del modo de ajuste
            }
            delay_ms(200);
        }
    }
}

void mostrar_valores() {
    // Mostrar la opción actual y el valor correspondiente en la LCD
    lcd_gotoxy(1, 1);
    switch(menu_option) {
        case 0: printf(lcd_putc, "Kp_x: %0.2f  ", Kp_x); break;
        case 1: printf(lcd_putc, "Ki_x: %0.2f  ", Ki_x); break;
        case 2: printf(lcd_putc, "Kd_x: %0.2f  ", Kd_x); break;
        case 3: printf(lcd_putc, "Kp_y: %0.2f  ", Kp_y); break;
        case 4: printf(lcd_putc, "Ki_y: %0.2f  ", Ki_y); break;
        case 5: printf(lcd_putc, "Kd_y: %0.2f  ", Kd_y); break;
    }
}

void main() {
    set_tris_d(0x00);
    set_tris_a(0xFC);
    set_tris_b(0xF0);  // RB0-RB3 como entradas
    
    lcd_init();
    servo_init();
    MPU6050_init();
    enable_interrupts(INT_RB);
    enable_interrupts(GLOBAL);
    printf(lcd_putc, " BIENVENIDO");
    delay_ms(1000);

    while (true) {
        if (adjusting) {
            mostrar_valores();
        } else {
            // Obtener y procesar los datos del MPU6050 como antes
            Ax = MPU6050_get_Ax(); Ay = MPU6050_get_Ay();
            Gx = MPU6050_get_Gx(); Gy = MPU6050_get_Gy();
            
            error_x = 0 - Gx;
            error_y = 0 - Gy;
            integral_x += error_x;
            integral_y += error_y;
            float derivative_x = error_x - prev_error_x;
            float derivative_y = error_y - prev_error_y;
            output_x = Kp_x * error_x + Ki_x * integral_x + Kd_x * derivative_x;
            output_y = Kp_y * error_y + Ki_y * integral_y + Kd_y * derivative_y;
            prev_error_x = error_x;
            prev_error_y = error_y;
            
            angle_x = 90 + (int)output_x;
            angle_y = 90 - (int)output_y;
            
            if (angle_x < 0) angle_x = 0;
            if (angle_x > 180) angle_x = 180;
            if (angle_y < 0) angle_y = 0;
            if (angle_y > 180) angle_y = 180;
            
            servo_1_write(angle_x);
            delay_ms(200);
            servo_2_write(angle_y);
            delay_ms(200);
            
            lcd_gotoxy(1, 1);
            printf(lcd_putc, "Ax:%0.2f Ay:%0.2f", Ax, Ay);
            lcd_gotoxy(1, 2);
            printf(lcd_putc, "Gx:%0.2f Gy:%0.2f", Gx, Gy);
        }
        delay_ms(200);
    }
}

