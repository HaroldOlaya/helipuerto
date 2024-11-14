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


// Rango de tolerancia de ±2 grados
float tolerance = 2.0;

// Función para aplicar corrección manual en el eje X
void aplicar_correccion_x(float Ax) {
    int servo_x_output = 90;  // Posición inicial del servo en el centro (90 grados)

    while (abs(Ax) > tolerance) {
        if (Ax > 0) {
            servo_x_output = 90 - 5;  // Corrige hacia la derecha
            if (servo_x_output < 0) servo_x_output = 0;  // Limitar a 0
        } else {
            servo_x_output = 90 + 5;  // Corrige hacia la izquierda
            if (servo_x_output > 180) servo_x_output = 180;  // Limitar a 180
        }

        servo_1_write(servo_x_output);  // Mueve el servo en el eje X
        delay_ms(1000);  // Espera entre movimientos

        // Actualizar el valor de Ax
        Ax = MPU6050_get_Ax();  // Lee el valor actual en el eje X desde el giroscopio

        // Ajustes finos de 1 grado una vez cerca del setpoint
        if (abs(Ax) <= tolerance) {
            if (Ax > 0) {
                servo_x_output = 90 - 1;
                if (servo_x_output < 0) servo_x_output = 0;
            } else {
                servo_x_output = 90 + 1;
                if (servo_x_output > 180) servo_x_output = 180;
            }
            servo_1_write(servo_x_output);
            delay_ms(50);
        }
    }
}

// Función para aplicar corrección manual en el eje Y
void aplicar_correccion_y(float Ay) {
    int servo_y_output = 90;  // Posición inicial del servo en el centro (90 grados)

    while (abs(Ay) > tolerance) {
        if (Ay > 0) {
            servo_y_output = 90 + 5;  // Mueve el servo hacia arriba
            if (servo_y_output > 180) servo_y_output = 180;  // Limitar a 180
        } else {
            servo_y_output = 90 - 5;  // Mueve el servo hacia abajo
            if (servo_y_output < 0) servo_y_output = 0;  // Limitar a 0
        }

        servo_2_write(servo_y_output);  // Mueve el servo en el eje Y
        delay_ms(1000);  // Espera entre movimientos

        // Actualizar el valor de Ay
        Ay = MPU6050_get_Ay();  // Lee el valor actual en el eje Y desde el giroscopio

        // Ajustes finos de 1 grado una vez cerca del setpoint
        if (abs(Ay) <= tolerance) {
            if (Ay > 0) {
                servo_y_output = 90 + 1;
                if (servo_y_output > 180) servo_y_output = 180;
            } else {
                servo_y_output = 90 - 1;
                if (servo_y_output < 0) servo_y_output = 0;
            }
            servo_2_write(servo_y_output);
            delay_ms(50);
        }
    }
}

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

        // Aplicar corrección para los ejes X e Y
        aplicar_correccion_x(Ax);
        aplicar_correccion_y(Ay);

        delay_ms(200);  // Espera breve entre lecturas
    }
}

