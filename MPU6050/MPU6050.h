/*
 * MPU6050.h
 *
 *  Created on: Mar 19, 2018
 *      Author: Phong
 */

#include "../include.h"

#ifndef MPU6050_MPU6050_H_
#define MPU6050_MPU6050_H_

#define DATA_REG_ADDR   0x3B    // address of MPU6050's first data registers
#define PWR_MGMT_1      0x6B    // Address of PWR_MGMT_1 register -> used to wake MPU6050 & enable TEMP_MEASUREMENT
#define CONFIG_ADDR     0x1B    // starting from GYRO_CONFIG at 0x1B, next register is ACCEL_CONFIG at 0x1C

static uint8_t MPU6050_Buf_14_uint8[14];
static int16_t MPU6050_Buf_7_int16[7];

extern void MPU6050_Config(uint8_t dev_addr, uint8_t gyro_FS_SEL, uint8_t accel_FS_SEL);
extern void MPU6050_Calibrate(uint16_t num);
extern void MPU6050_Read_raw(int16_t *accel_x, int16_t *accel_y, int16_t *accel_z,
                             int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z,
                             int16_t *temp);
extern void MPU6050_Read_raw_Calibrated(int16_t *accel_x, int16_t *accel_y, int16_t *accel_z,
                                        int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z,
                                        int16_t *temp);
extern void MPU6050_Read(double *accel_x_g,  double *accel_y_g,  double *accel_z_g,
                         double *gyro_x_deg, double *gyro_y_deg, double *gyro_z_deg,
                         double *temp_c);
extern void MPU6050_Read_Angle(double *gyro_pitch,  double *gyro_roll, double *gyro_yaw,
                               double *accel_pitch, double * accel_roll);
extern void MPU6050_Read_Comple_Angle(double *pitch, double *roll, double *yaw, const double COMPLE_GAIN);

#endif /* MPU6050_MPU6050_H_ */
