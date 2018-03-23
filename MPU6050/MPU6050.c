/*
 * MPU6050.c
 *
 *  Created on: Mar 19, 2018
 *      Author: Phong
 */

#include "MPU6050.h"

static uint8_t mpu6050_addr;
static double gyro_scale, accel_scale;

static int32_t accel_x_calib, accel_y_calib, accel_z_calib;
static int32_t gyro_x_calib, gyro_y_calib, gyro_z_calib;


void MPU6050_Config(uint8_t dev_addr, uint8_t gyro_FS_SEL, uint8_t accel_FS_SEL)
{
    /*
     * Assign gyro & accel scaler to match with the selected Full Scale setting
     */
    switch (gyro_FS_SEL)
    {
    case 0: // +- 250 deg/s
        gyro_scale = 131.0;
        break;
    case 1: // +- 500 deg/s
        gyro_scale = 65.5;
        break;
    case 2: // +- 1000 deg/s
        gyro_scale = 32.8;
        break;
    case 3: // +- 2000 deg/s
        gyro_scale = 16.4;
        break;
    }

    switch (accel_FS_SEL)
    {
    case 0: // +- 2g
        accel_scale = 16384.0;
        break;
    case 1: // +- 4g
        accel_scale = 8192.0;
        break;
    case 2: // +- 8g
        accel_scale = 4096.0;
        break;
    case 3: // +- 16g
        accel_scale = 2048.0;
        break;
    }

    /*
     * Save device's address for later use in MPU6050_Read_raw()
     */
    mpu6050_addr = dev_addr;

    /*
     * Configure MPU6050
     */
    // Wake up from sleep & enable temperature reading
    uint8_t PWR_MGMT_1_value = 0x00;
    I2C_Write_bytes(mpu6050_addr, PWR_MGMT_1, 1, &PWR_MGMT_1_value);

    // Configure sensors' full scale range using Buffer
    I2C_Read_bytes(mpu6050_addr, CONFIG_ADDR, 2, MPU6050_Buf_14_uint8);  // Read from register -> buffer
    MPU6050_Buf_14_uint8[0] |= gyro_FS_SEL  << 3;                        // Set Gyro full scale range (FS_SEL)
    MPU6050_Buf_14_uint8[1] |= accel_FS_SEL << 3;                        // Set Accel full scale range (AFS_SEL)
    I2C_Write_bytes(mpu6050_addr, CONFIG_ADDR, 2, MPU6050_Buf_14_uint8); // Write back from Buffer -> register
}

void MPU6050_Read_raw(int16_t *accel_x, int16_t *accel_y, int16_t *accel_z,
                      int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z,
                      int16_t *temp)
{
    // Read data from MPU6050 and store in Buffer
    I2C_Read_bytes(mpu6050_addr, DATA_REG_ADDR, 14, MPU6050_Buf_14_uint8);

    // Extract data from Buffer and store in the following variables
    *accel_x = (MPU6050_Buf_14_uint8[0] << 8) | MPU6050_Buf_14_uint8[1];
    *accel_y = (MPU6050_Buf_14_uint8[2] << 8) | MPU6050_Buf_14_uint8[3];
    *accel_z = (MPU6050_Buf_14_uint8[4] << 8) | MPU6050_Buf_14_uint8[5];
    *temp    = (MPU6050_Buf_14_uint8[6] << 8) | MPU6050_Buf_14_uint8[7];
    *gyro_x =  (MPU6050_Buf_14_uint8[8] << 8) | MPU6050_Buf_14_uint8[9];
    *gyro_y = (MPU6050_Buf_14_uint8[10] << 8) | MPU6050_Buf_14_uint8[11];
    *gyro_z = (MPU6050_Buf_14_uint8[12] << 8) | MPU6050_Buf_14_uint8[13];
}


void MPU6050_Calibrate(uint16_t num)
{
    uint16_t i = 0;

    // Read num samples for each data & add to Calib variables
    for (i = 0; i < num; i++)
    {
        MPU6050_Read_raw(&MPU6050_Buf_7_int16[0], &MPU6050_Buf_7_int16[1], &MPU6050_Buf_7_int16[2], // Accel_x_Calib, Accel_y_Calib, Accel_z_Calib
                         &MPU6050_Buf_7_int16[3], &MPU6050_Buf_7_int16[4], &MPU6050_Buf_7_int16[5], // Gyro_x_Calib, Gyro_y_Calib, Gyro_z_Calib
                         &MPU6050_Buf_7_int16[6]);                                                  // temp_Calib
        accel_x_calib += MPU6050_Buf_7_int16[0];
        accel_y_calib += MPU6050_Buf_7_int16[1];
        accel_z_calib += MPU6050_Buf_7_int16[2];
        gyro_x_calib  += MPU6050_Buf_7_int16[3];
        gyro_y_calib  += MPU6050_Buf_7_int16[4];
        gyro_z_calib  += MPU6050_Buf_7_int16[5];
    }

    //Divide the sum by num (num = number of samples taken)
    accel_x_calib /= i;
    accel_y_calib /= i;
    accel_z_calib = abs(accel_z_calib / i) - accel_scale;          // IMPORTANT: unlike others (Calibrated to 0), Accel_z_Calib is calibrated to 1g
    gyro_x_calib  /= i;
    gyro_y_calib  /= i;
    gyro_z_calib  /= i;
}


void MPU6050_Read_raw_Calibrated(int16_t *accel_x, int16_t *accel_y, int16_t *accel_z,
                                 int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z,
                                 int16_t *temp)
{
    MPU6050_Read_raw(accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z, temp);

    *accel_x -= accel_x_calib;
    *accel_y -= accel_y_calib;
    *accel_z -= accel_z_calib;
    *gyro_x  -= gyro_x_calib;
    *gyro_y  -= gyro_y_calib;
    *gyro_z  -= gyro_z_calib;
}


void MPU6050_Read(double *accel_x_g, double *accel_y_g, double *accel_z_g,
                  double *gyro_x_deg, double *gyro_y_deg, double *gyro_z_deg,
                  double *temp_c)
{
    //Create temporary variable to store data read from MPU6050_Read_raw_Calibrated()
    int16_t accel_x, accel_y, accel_z;
    int16_t gyro_x, gyro_y, gyro_z;
    int16_t temp;

    MPU6050_Read_raw_Calibrated(&accel_x, &accel_y, &accel_z, &gyro_x, &gyro_y, &gyro_z, &temp);

    // Calculate Accelerometer readings in g
    *accel_x_g = accel_x/accel_scale;
    *accel_y_g = accel_y/accel_scale;
    *accel_z_g = accel_z/accel_scale;

    // Calculate Gyroscope readings in degree per second
    *gyro_x_deg = gyro_x/gyro_scale;
    *gyro_y_deg = gyro_y/gyro_scale;
    *gyro_z_deg = gyro_z/gyro_scale;

    // Calculate temperature in Celsius
    *temp_c = temp/340+36.35;
}


void MPU6050_Read_Angle(double *gyro_pitch, double *gyro_roll, double *gyro_yaw,
                        double *accel_pitch, double * accel_roll)
{
    // Create temporary variable to store data read from MPU6050_Read_raw_Calibrated()
    int16_t accel_x, accel_y, accel_z;
    int16_t gyro_x, gyro_y, gyro_z;
    int16_t temp;

    MPU6050_Read_raw_Calibrated(&accel_x, &accel_y, &accel_z, &gyro_x, &gyro_y, &gyro_z, &temp);

    // Calculate Accel angles using asin function
    double total_vector = sqrt((double)accel_x*accel_x + (double)accel_y*accel_y + (double)accel_z*accel_z);
    *accel_pitch = -asin(accel_x/total_vector)*(180/(double)M_PI);  // *180/M_PI to convert from rad to deg
    *accel_roll  =  asin(accel_y/total_vector)*(180/(double)M_PI);

    // Integrate gyro values to find the moved angles
    *gyro_pitch += (double)gyro_y / (gyro_scale * loop_time);    // divided by Gyro_scale to get (degree/second); multiplied by loop time = 4ms means divided by 50 Hz
    *gyro_roll  += (double)gyro_x / (gyro_scale * loop_time);
    *gyro_yaw   += (double)gyro_z / (gyro_scale * loop_time);
}

void MPU6050_Read_Comple_Angle(double *pitch, double *roll, double *yaw, double COMPLE_GAIN)
{
    // Create temporary variable to store data read from MPU6050_Read_raw_Calibrated()
    int16_t accel_x, accel_y, accel_z;
    int16_t gyro_x, gyro_y, gyro_z;
    int16_t temp;

    MPU6050_Read_raw_Calibrated(&accel_x, &accel_y, &accel_z, &gyro_x, &gyro_y, &gyro_z, &temp);

    // Calculate Accel angles using asin function
    double total_vector = sqrt((double)accel_x*accel_x + (double)accel_y*accel_y + (double)accel_z*accel_z);
    double accel_pitch = -asin(accel_x/total_vector)*(180/(double)M_PI);  // *180/M_PI to convert from rad to deg
    double accel_roll  =  asin(accel_y/total_vector)*(180/(double)M_PI);

    // Add integrated Gyro's measurement to current Angles
    *pitch += ( (float)gyro_y / (gyro_scale) ) * loop_time;
    *roll  += ( (float)gyro_x / (gyro_scale) ) * loop_time;
    *yaw   += ( (float)gyro_z / (gyro_scale) ) * loop_time;

    // Complementary fusion: fuse angle with accelerometer readings
    *pitch = COMPLE_GAIN*(*pitch) + (1-COMPLE_GAIN)*(accel_pitch);
    *roll  = COMPLE_GAIN*(*roll)  + (1-COMPLE_GAIN)*(accel_roll);
}
