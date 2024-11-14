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

// Librería adicional para el manejo de servos
#define BUTTON_UP PIN_B1      // Botón para incrementar valor
#define BUTTON_DOWN PIN_B2    // Botón para decrementar valor
#define BUTTON_SELECT PIN_B3  // Botón para confirmar selección
#define BUTTON_MENU PIN_B0  

#include <lcd.c>         // Librería para el manejo de la LCD
#include <MPU6050.c>     // Librería para el manejo del MPU6050
#include <servo_st.c>    // Librería para servos



void main() {
    lcd_init();
    MPU6050_init();  // Inicializa el MPU6050
    servo_init();    // Inicializa los servos

    printf(lcd_putc, "BIENVENIDO");

    float Ax, Ay;

    while (true) {
        // Obtener los valores de los ángulos
        Ax = MPU6050_get_Ax();  // Obtener valor en el eje X
        Ay = MPU6050_get_Ay();  // Obtener valor en el eje Y

        // Mostrar los valores de los ángulos en la pantalla LCD
        lcd_gotoxy(1, 1);
        printf(lcd_putc, "\fAx:%d Ay:%d", (int)(Ax * 100), (int)(Ay * 100)); // Mostrar como valores enteros

  
        // Enviar los ángulos a los servos
        servo_1_write(60);   // Mueve el servo 1 a angle_x
        delay_ms(500);           // Espera para que el servo complete el movimiento
        servo_1_write(90);   // Mueve el servo 2 a angle_y
        delay_ms(500);  

        servo_1_write(120);   // Mueve el servo 1 a angle_x
        delay_ms(500);           // Espera para que el servo complete el movimiento
        servo_1_write(90);   // Mueve el servo 2 a angle_y
        delay_ms(500);
        // Enviar los ángulos a los servos
        servo_2_write(60);   // Mueve el servo 1 a angle_x
        delay_ms(500);           // Espera para que el servo complete el movimiento
        servo_2_write(90);   // Mueve el servo 2 a angle_y
        delay_ms(500);  

        servo_2_write(120);   // Mueve el servo 1 a angle_x
        delay_ms(500);           // Espera para que el servo complete el movimiento
        servo_2_write(90);   // Mueve el servo 2 a angle_y
        delay_ms(500);  
    }
}

