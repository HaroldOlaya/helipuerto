#include <16f877a.h>
#include <math.h>  // Para usar atan

#fuses HS, NOWDT, NOPROTECT, NOPUT, NOLVP, NOBROWNOUT
#use delay(clock=20000000)
#use I2C(MASTER, SDA=PIN_C4, SCL=PIN_C3, SLOW)

#use standard_io(D)
#use standard_io(A)
#define use_servo_1 
#define use_servo_2
// Definiciones de pines para los servos
#define servo_1 PIN_A0
#define servo_2 PIN_A1

#include <lcd.c>         // Librería para el manejo de la LCD
#include <MPU6050.c>     // Librería para el manejo del MPU6050
#include <servo_st.c>    // Librería adicional para el manejo de servos

float Ax, Ay, Az, Gx, Gy, Gz, t;

void main() {
    set_tris_d(0x00);  // Configura el puerto D completo como salida para la LCD
    set_tris_a(0xFC);  // Configura A0 y A1 como salidas para los servos
    
    lcd_init();         // Inicializa la pantalla LCD
    servo_init();       // Inicializa el control de los servos
    MPU6050_init();     // Inicializa el MPU6050

    printf(lcd_putc, " BIENVENIDO");
    delay_ms(1000);

    // Configurar los servos inicialmente en 90 grados
    int angle_x = 90;
    int angle_y = 90;
    servo_1_write(angle_x);
    servo_2_write(angle_y);
    
    // Esperar 5 segundos con los servos en 90 grados
    delay_ms(5000);

    // Variables de control de ángulo
    int min_angle = 70;
    int max_angle = 120;
    int decreasing_x = 0;  // Control de dirección para servo 1
    int decreasing_y = 0;  // Control de dirección para servo 2

    // Bucle principal
    while (true) {
        // Obtener datos del MPU6050
        Ax = MPU6050_get_Ax();
        Ay = MPU6050_get_Ay();
        Az = MPU6050_get_Az();
        Gx = MPU6050_get_Gx();
        Gy = MPU6050_get_Gy();
        Gz = MPU6050_get_Gz();
        t = MPU6050_get_Temp();

        // Mostrar datos en la pantalla LCD
        lcd_gotoxy(1, 1);
        printf(lcd_putc, "Ax:%0.2f Ay:%0.2f", Ax, Ay);
        
        lcd_gotoxy(1, 2);
        printf(lcd_putc, "Gx:%0.2f Gy:%0.2f", Gx, Gy);

        // Movimiento suave del servo en eje X
        if (decreasing_x) {
            angle_x--;
            if (angle_x <= min_angle) decreasing_x = 0;
        } else {
            angle_x++;
            if (angle_x >= max_angle) decreasing_x = 1;
        }
        servo_1_write(angle_x);

        // Movimiento suave del servo en eje Y
        if (decreasing_y) {
            angle_y--;
            if (angle_y <= min_angle) decreasing_y = 0;
        } else {
            angle_y++;
            if (angle_y >= max_angle) decreasing_y = 1;
        }
        servo_2_write(angle_y);

        delay_ms(100);  // Pausa para suavizar el movimiento
    }
}

