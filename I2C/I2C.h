/*
 * I2C.h
 *
 *  Created on: Mar 16, 2018
 *      Author: Phong
 */

#ifndef I2C_I2C_H_
#define I2C_I2C_H_

#include "../include.h"
#include <string.h>     // strcmp()

extern void I2C_Config(const char* I2C_SELECT, bool en_Fast_Mode);
extern void I2C_Write_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t num, uint8_t *data);
extern void I2C_Read_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t num, uint8_t *data);

#endif /* I2C_I2C_H_ */
