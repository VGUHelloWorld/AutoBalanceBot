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

/*
 * Configure MPU6050
 * @param <uint8_t> $dev_addr address of the MPU6050 device to read from
 *      0x68 normally
 *      0x69 if AD0 is connected to VCC
 * @param <uint8_t> $gyro_FS_SEL select gyroscope's full scale range
 *      gyro_FS_SEL     Full scale range        LSB sensitivity
 *          0           +- 250  deg/sec         131.0 LSB/deg/sec
 *          1           +- 500  deg/sec         65.5  LSB/deg/sec
 *          2           +- 1000 deg/sec         32.8  LSB/deg/sec
 *          3           +- 2000 deg/sec         16.4  LSB/deg/sec
 * @param <uint8_t> $accel_FS_SEL select accelerometer's full scale range
 *      accel_FS_SEL        Full scale range        LSB sensitivity
 *          0                   +- 2  g               16384 LSB/g
 *          1                   +- 4  g               8192  LSB/g
 *          2                   +- 8  g               4096  LSB/g
 *          3                   +- 16 g               2048  LSB/g
 * @return void
 */
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

/*
 * Read raw data from MPU6050
 * @param <int16_t*> $accel_x, $accel_y, $accel_z, $gyro_x, $gyro_y, $gyro_z, $temp
 *      pointers to storing variables after reading MPU6050's raw data
 * @return void
 */
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

/*
 * Calibrate MPU6050: calculate the mean values of MPU6050's initial offsets
 * @param <uint16_t> $num number of calibration using MPU6050_Read_raw()
 * @return void
 */
void MPU6050_Calibrate(uint16_t num)
{
    uint16_t i = 0;

    // Read num samples for each data & add to Calib variables
    for (i = 0; i < num; i++)
    {
        MPU6050_Read_raw(&MPU6050_Buf_7_int16[0], &MPU6050_Buf_7_int16[1], &MPU6050_Buf_7_int16[2],
                         &MPU6050_Buf_7_int16[3], &MPU6050_Buf_7_int16[4], &MPU6050_Buf_7_int16[5],
                         &MPU6050_Buf_7_int16[6]);
        accel_x_calib += MPU6050_Buf_7_int16[0];
        accel_y_calib += MPU6050_Buf_7_int16[1];
        accel_z_calib += MPU6050_Buf_7_int16[2];
        gyro_x_calib  += MPU6050_Buf_7_int16[3];
        gyro_y_calib  += MPU6050_Buf_7_int16[4];
        gyro_z_calib  += MPU6050_Buf_7_int16[5];
    }

    // Divide the sum by num (num = number of samples taken)
    // IMPORTANT: unlike others (Calibrated to 0), Accel_z_Calib is calibrated to 1g
    accel_x_calib /= i;
    accel_y_calib /= i;
    accel_z_calib  = accel_z_calib / i - (-accel_scale);
    gyro_x_calib  /= i;
    gyro_y_calib  /= i;
    gyro_z_calib  /= i;
}

/*
 * Set initial offsets values after calibration
 * @param <int32_t> $a_x, $a_y, $a_z, $g_x, $g_y, $g_z sensor's offsets
 * @return void
 */
void MPU6050_Calib_Set(int32_t a_x, int32_t a_y, int32_t a_z, int32_t g_x, int32_t g_y, int32_t g_z)
{
    accel_x_calib = a_x;
    accel_y_calib = a_y;
    accel_z_calib = a_z;
    gyro_x_calib  = g_x;
    gyro_y_calib  = g_y;
    gyro_z_calib  = g_z;
}

/*
 * Read raw data from MPU6050, subtracted by the measured initial offsets
 * @param <int16_t*> $accel_x, $accel_y, $accel_z, $gyro_x, $gyro_y, $gyro_z, $temp
 *      pointers to storing variables
 * @return void
 */
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

/*
 * Read calibrated raw data, calculate:
 *      accel's readings in g
 *      gyro's  readings in deg/sec
 *      temp    reading  in celsius
 * @param <double*> $accel_x_g, $accel_y_g, $accel_z_g, $gyro_x_deg, $gyro_y_deg, $gyro_z_deg, $temp_c
 *      pointers to storing variables
 * @return void
 */
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

/*
 * Read calibrated raw data, calculate pitch-roll-yaw angles
 *      NOTE: output angles from this function haven't been fused
 *            Thus, gyro will drift and accel is vulnerable to vibrations
 * @param <double*> $gyro_pitch, $gyro_roll, $gyro_yaw, $accel_pitch, $accel_roll
 * @return void
 */
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
    *accel_pitch =  asin((double)accel_x/total_vector)*(180.0f/(double)M_PI);  // *180/M_PI to convert from rad to deg
    *accel_roll  = -asin((double)accel_y/total_vector)*(180.0f/(double)M_PI);

    // Integrate gyro values to find the moved angles
    *gyro_pitch += ( (double)gyro_y / gyro_scale ) * loop_time;    // divided by Gyro_scale to get (degree/second)
    *gyro_roll  += ( (double)gyro_x / gyro_scale ) * loop_time;    // multiplied by loop time to get angles in (degree)
    *gyro_yaw   += ( (double)gyro_z / gyro_scale ) * loop_time;
}

/*
 * Read calibrated raw data, calculate accel & gyro angles, fused the two signals using Complementary filter
 * @param <double*> $pitch, $roll, $yaw
 *      pointers to storing variables
 * @param <double> RCOMPLE_GAIN  the gain of complementary filter (how much gyro is trusted)
 * @return void
 */
void MPU6050_Read_Comple_Angle(double *pitch, double *roll, double *yaw, double COMPLE_GAIN)
{
    // Create temporary variable to store data read from MPU6050_Read_raw_Calibrated()
    int16_t accel_x, accel_y, accel_z;
    int16_t gyro_x, gyro_y, gyro_z;
    int16_t temp;

    MPU6050_Read_raw_Calibrated(&accel_x, &accel_y, &accel_z, &gyro_x, &gyro_y, &gyro_z, &temp);

    // Calculate Accel angles using asin function
    double total_vector = sqrt((double)accel_x*accel_x + (double)accel_y*accel_y + (double)accel_z*accel_z);
    //double accel_pitch =  asin((double)accel_x/total_vector)*(180.0f/(double)M_PI);
    double accel_pitch = -atan2(-accel_x, sqrt(accel_y*accel_y + accel_z*accel_z))*(180.0f/(double)M_PI);                 // *180/M_PI to convert from rad to deg
    double accel_roll  = -asin((double)accel_y/total_vector)*(180.0f/(double)M_PI);

    // Add integrated Gyro's measurement to current Angles
    *pitch += ( (double)gyro_y / (gyro_scale) ) * loop_time;
    *roll  += ( (double)gyro_x / (gyro_scale) ) * loop_time;
    *yaw   += ( (double)gyro_z / (gyro_scale) ) * loop_time;

    // Complementary fusion: fuse angle with accelerometer readings
    *pitch = COMPLE_GAIN*(*pitch) + (1-COMPLE_GAIN)*(accel_pitch);
    *roll  = COMPLE_GAIN*(*roll)  + (1-COMPLE_GAIN)*(accel_roll);
}
