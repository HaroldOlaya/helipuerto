/* #include <MPU6050.c>
*
* Creada por: Ing. Abiezer Hernandez O.
* Fecha de creacion: 24/04/2019
* Electronica y Circuitos
*
*/

#define W_DATA         0xD0
#define R_DATA         0xD1
#define PWR_MGMT_1     0x6B
#define PWR_MGMT_2     0x6C
#define SMPRT_DIV      0x19
#define CONFIG_R       0x1A
#define GYRO_CONFIG    0x1B
#define ACCEL_CONFIG   0x1C
#define ACCEL_XOUT_H   0x3B
#define ACCEL_XOUT_L   0x3C
#define ACCEL_YOUT_H   0x3D
#define ACCEL_YOUT_L   0x3E
#define ACCEL_ZOUT_H   0x3F
#define ACCEL_ZOUT_L   0x40
#define TEMP_OUT_H     0x41
#define TEMP_OUT_L     0x42
#define GYRO_XOUT_H    0x43
#define GYRO_XOUT_L    0x44
#define GYRO_YOUT_H    0x45
#define GYRO_YOUT_L    0x46
#define GYRO_ZOUT_H    0x47
#define GYRO_ZOUT_L    0x48

void mpu6050_write(int add, int data)
{
   i2c_start();
   i2c_write(W_DATA);
   i2c_write(add);
   i2c_write(data);
   i2c_stop();
}

unsigned int mpu6050_read(int add)
{
   unsigned int retval;
   i2c_start();
   i2c_write(W_DATA);
   i2c_write(add);
   i2c_start();
   i2c_write(R_DATA);
   retval = i2c_read(0);
   i2c_stop();
   return retval;
}

void mpu6050_init()
{
   mpu6050_write(PWR_MGMT_1, 0x00);
   delay_ms(100);
   mpu6050_write(SMPRT_DIV, 0x07);
   delay_ms(100);
}

float mpu6050_get_ax(void)
{
   signed long axv = make16(mpu6050_read(ACCEL_XOUT_H), mpu6050_read(ACCEL_XOUT_L));
   float acx = (float)axv/(float)16384;
   return acx;
}

float mpu6050_get_ay(void)
{
   signed long ayv = make16(mpu6050_read(ACCEL_YOUT_H), mpu6050_read(ACCEL_YOUT_L));
   float acy = (float)ayv/(float)16384;
   return acy;
}

float mpu6050_get_az(void)
{
   signed long azv = make16(mpu6050_read(ACCEL_ZOUT_H), mpu6050_read(ACCEL_ZOUT_L));
   float acz = (float)azv/(float)16384;
   return acz;
}

float mpu6050_get_gx(void)
{
   signed long gxv = make16(mpu6050_read(GYRO_XOUT_H), mpu6050_read(GYRO_XOUT_L));
   float grx = (float)gxv/(float)131;
   return grx;
}

float mpu6050_get_gy(void)
{
   signed long gyv = make16(mpu6050_read(GYRO_YOUT_H), mpu6050_read(GYRO_YOUT_L));
   float gry = (float)gyv/(float)131;
   return gry;
}

float mpu6050_get_gz(void)
{
   signed long gzv = make16(mpu6050_read(GYRO_ZOUT_H), mpu6050_read(GYRO_ZOUT_L));
   float grz = (float)gzv/(float)131;
   return grz;
}

float mpu6050_get_temp()
{
   signed long tmpv = make16(mpu6050_read(TEMP_OUT_H), mpu6050_read(TEMP_OUT_L));
   float tmp_mpu = (float)(tmpv/(float)340 + (float)36.53);
   return tmp_mpu;
}
