/*
 * I2C.h
 *
 *  Created on: Mar 16, 2018
 *      Author: Phong
 */

#ifndef I2C_I2C_H_
#define I2C_I2C_H_

#include "../include.h"

/*
 * Select I2C module (ex: I2C0)
 * Enable fast mode (ex: #define FAST_MODE true)
 */
#define I2C1
#define FAST_MODE false

extern void I2C_Config(void);
extern void Write_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t length, uint8_t *data);
extern void Read_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t length, uint8_t *data);

#endif /* I2C_I2C_H_ */
