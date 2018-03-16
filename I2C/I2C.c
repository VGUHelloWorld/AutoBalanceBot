/*
 * I2C.c
 *
 *  Created on: Mar 16, 2018
 *      Author: Phong
 */

#include "I2C.h"


#ifdef I2C0
    #define     SYSCTL_PERIPH_I2C   SYSCTL_PERIPH_I2C0
    #define     SYSCTL_PERIPH_GPIO  SYSCTL_PERIPH_GPIOB
    #define     GPIO_I2C_SCL        GPIO_PB2_I2C0SCL
    #define     GPIO_I2C_SDA        GPIO_PB3_I2C0SDA
    #define     GPIO_PORT           GPIO_PORTB_BASE
    #define     GPIO_SCL_PIN        GPIO_PIN_2
    #define     GPIO_SDA_PIN        GPIO_PIN_3
    #define     I2C_BASE            I2C0_BASE
#endif

#ifdef I2C1
    #define     SYSCTL_PERIPH_I2C   SYSCTL_PERIPH_I2C1
    #define     SYSCTL_PERIPH_GPIO  SYSCTL_PERIPH_GPIOA
    #define     GPIO_I2C_SCL        GPIO_PA6_I2C1SCL
    #define     GPIO_I2C_SDA        GPIO_PA7_I2C1SDA
    #define     GPIO_PORT           GPIO_PORTA_BASE
    #define     GPIO_SCL_PIN        GPIO_PIN_6
    #define     GPIO_SDA_PIN        GPIO_PIN_7
    #define     I2C_BASE            I2C1_BASE
#endif

#ifdef I2C2
    #define     SYSCTL_PERIPH_I2C   SYSCTL_PERIPH_I2C2
    #define     SYSCTL_PERIPH_GPIO  SYSCTL_PERIPH_GPIOE
    #define     GPIO_I2C_SCL        GPIO_PE4_I2C2SCL
    #define     GPIO_I2C_SDA        GPIO_PE5_I2C2SDA
    #define     GPIO_PORT           GPIO_PORTE_BASE
    #define     GPIO_SCL_PIN        GPIO_PIN_4
    #define     GPIO_SDA_PIN        GPIO_PIN_5
    #define     I2C_BASE            I2C2_BASE
#endif

#ifdef I2C3
    #define     SYSCTL_PERIPH_I2C   SYSCTL_PERIPH_I2C3
    #define     SYSCTL_PERIPH_GPIO  SYSCTL_PERIPH_GPIOD
    #define     GPIO_I2C_SCL        GPIO_PD0_I2C3SCL
    #define     GPIO_I2C_SDA        GPIO_PD1_I2C3SDA
    #define     GPIO_PORT           GPIO_PORTD_BASE
    #define     GPIO_SCL_PIN        GPIO_PIN_0
    #define     GPIO_SDA_PIN        GPIO_PIN_1
    #define     I2C_BASE            I2C3_BASE
#endif

/*
 * Configure selected I2C module
 * @param none
 * @return void
 */
void I2C_Config(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    GPIOPinConfigure(GPIO_I2C_SCL);
    GPIOPinConfigure(GPIO_I2C_SDA);
    GPIOPinTypeI2C(GPIO_PORT, GPIO_SDA_PIN);
    GPIOPinTypeI2CSCL(GPIO_PORT, GPIO_SCL_PIN);
    I2CMasterInitExpClk(I2C_BASE, SysCtlClockGet(), FAST_MODE);
}

/*
 * Write byte(s) consecutively to a slave device
 * @param <uint8_t> $dev_addr address of the device to write to
 * @param <uint8_t> $reg_addr address of the (starting) register to write
 * @param <uint8_t> $length   number of byte(s) to write
 * @param <uint8_t> $*data    data to write
 *      Usage: accepts an address of a value-storing variable when writing single byte
 *         or: accepts a value-storing array when writing single/multiple byte(s)
 * @return void
 */
void Write_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t length, uint8_t *data)
{
    uint8_t count = 0;

    I2CMasterSlaveAddrSet(I2C_BASE, dev_addr, false);
    I2CMasterDataPut(I2C_BASE, reg_addr);
    I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C_BASE));

    for (count = 0; count < length-1; count ++) {
        I2CMasterDataPut(I2C_BASE, data[count]);
        I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
        while(I2CMasterBusy(I2C_BASE));
    }

    I2CMasterDataPut(I2C_BASE, data[count]);
    I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(I2C_BASE));
}

/*
 * Read byte(s) consecutively from a slave device
 * @param <uint8_t> $dev_addr address of the device to read from
 * @param <uint8_t> $reg_addr address of the (starting) register to read
 * @param <uint8_t> $length   number of byte(s) to read
 * @param <uint8_t> $*data    data to read
 *      Usage: accepts an address of a value-storing variable when reading single byte
 *         or: accepts a value-storing array when reading single/multiple byte(s)
 * @return void
 */
void Read_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t length, uint8_t *data)
{
    uint8_t count = 0;

    I2CMasterSlaveAddrSet(I2C_BASE, dev_addr, false);
    I2CMasterDataPut(I2C_BASE, reg_addr);
    I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_SINGLE_SEND);
    while(I2CMasterBusy(I2C_BASE));

    I2CMasterSlaveAddrSet(I2C_BASE, dev_addr, true);
    I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
    while(I2CMasterBusy(I2C_BASE));
    data[0] = I2CMasterDataGet(I2C_BASE);

    for (count = 1; count < length-1; count++) {
        I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
        while(I2CMasterBusy(I2C_BASE));
        data[count] = I2CMasterDataGet(I2C_BASE);
    }

    I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    while(I2CMasterBusy(I2C_BASE));
    data[count] = I2CMasterDataGet(I2C_BASE);
}
