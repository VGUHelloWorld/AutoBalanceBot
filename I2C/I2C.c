/*
 * I2C.c
 *
 *  Created on: Mar 16, 2018
 *      Author: Phong
 */

#include "I2C.h"

/*
 * static variables used to setup I2C according to the selected I2C module
 * default to I2C0
 */
static uint32_t SYSCTL_PERIPH_I2C     = SYSCTL_PERIPH_I2C0;
static uint32_t SYSCTL_PERIPH_GPIO    = SYSCTL_PERIPH_GPIOB;
static uint32_t GPIO_I2C_SCL          = GPIO_PB2_I2C0SCL;
static uint32_t GPIO_I2C_SDA          = GPIO_PB3_I2C0SDA;
static uint32_t GPIO_PORT             = GPIO_PORTB_BASE;
static uint32_t GPIO_SCL_PIN          = GPIO_PIN_2;
static uint32_t GPIO_SDA_PIN          = GPIO_PIN_3;
static uint32_t I2C_BASE              = I2C0_BASE;

/*
 * Configure selected I2C module
 * @param <const> <char*> I2C_SELECT for selecting I2C module
 * @param <bool> en_Fast_Mode enable/disable fast mode 400 Kbps
 *      ex: I2C_Config("I2C0", true)  -> select module I2C0 & enable fast mode
 * @return void
 */
void I2C_Config(const char* I2C_SELECT, bool en_Fast_Mode)
{
    /*
     * Change I2C setup values to match with the selected I2C module
     */
    if (strcmp(I2C_SELECT, "I2C0")==0)
    {
        /*Leave as default*/
    }
    else if (strcmp(I2C_SELECT, "I2C1")==0)
    {
        SYSCTL_PERIPH_I2C     = SYSCTL_PERIPH_I2C1;
        SYSCTL_PERIPH_GPIO    = SYSCTL_PERIPH_GPIOA;
        GPIO_I2C_SCL          = GPIO_PA6_I2C1SCL;
        GPIO_I2C_SDA          = GPIO_PA7_I2C1SDA;
        GPIO_PORT             = GPIO_PORTA_BASE;
        GPIO_SCL_PIN          = GPIO_PIN_6;
        GPIO_SDA_PIN          = GPIO_PIN_7;
        I2C_BASE              = I2C1_BASE;
    }
    else if (strcmp(I2C_SELECT, "I2C2")==0)
    {
        SYSCTL_PERIPH_I2C     = SYSCTL_PERIPH_I2C2;
        SYSCTL_PERIPH_GPIO    = SYSCTL_PERIPH_GPIOE;
        GPIO_I2C_SCL          = GPIO_PE4_I2C2SCL;
        GPIO_I2C_SDA          = GPIO_PE5_I2C2SDA;
        GPIO_PORT             = GPIO_PORTE_BASE;
        GPIO_SCL_PIN          = GPIO_PIN_4;
        GPIO_SDA_PIN          = GPIO_PIN_5;
        I2C_BASE              = I2C2_BASE;
    }
    else if (strcmp(I2C_SELECT, "I2C3")==0)
    {
        SYSCTL_PERIPH_I2C     = SYSCTL_PERIPH_I2C3;
        SYSCTL_PERIPH_GPIO    = SYSCTL_PERIPH_GPIOD;
        GPIO_I2C_SCL          = GPIO_PD0_I2C3SCL;
        GPIO_I2C_SDA          = GPIO_PD1_I2C3SDA;
        GPIO_PORT             = GPIO_PORTD_BASE;
        GPIO_SCL_PIN          = GPIO_PIN_0;
        GPIO_SDA_PIN          = GPIO_PIN_1;
        I2C_BASE              = I2C3_BASE;
    }

    /*
     * Configure selected I2C module
     */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    GPIOPinConfigure(GPIO_I2C_SCL);
    GPIOPinConfigure(GPIO_I2C_SDA);
    GPIOPinTypeI2C(GPIO_PORT, GPIO_SDA_PIN);
    GPIOPinTypeI2CSCL(GPIO_PORT, GPIO_SCL_PIN);
    I2CMasterInitExpClk(I2C_BASE, SysCtlClockGet(), en_Fast_Mode);
}

/*
 * Write byte(s) consecutively to a slave device
 * @param <uint8_t> $dev_addr address of the device to write to
 * @param <uint8_t> $reg_addr address of the (starting) register to write
 * @param <uint8_t> $num   number of byte(s) to write
 * @param <uint8_t> $*data    data to write
 *      Usage: accepts an address of a value-storing variable when writing single byte
 *         or: accepts a value-storing array when writing single/multiple byte(s)
 * @return void
 */
void I2C_Write_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t num, uint8_t *data)
{
    uint8_t count = 0;

    I2CMasterSlaveAddrSet(I2C_BASE, dev_addr, false);
    I2CMasterDataPut(I2C_BASE, reg_addr);
    I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C_BASE));

    for (count = 0; count < num-1; count ++) {
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
 * @param <uint8_t> $num   number of byte(s) to read
 * @param <uint8_t> $*data    data to read
 *      Usage: accepts an address of a value-storing variable when reading single byte
 *         or: accepts a value-storing array when reading single/multiple byte(s)
 * @return void
 */
void I2C_Read_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t num, uint8_t *data)
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

    for (count = 1; count < num-1; count++) {
        I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
        while(I2CMasterBusy(I2C_BASE));
        data[count] = I2CMasterDataGet(I2C_BASE);
    }

    I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    while(I2CMasterBusy(I2C_BASE));
    data[count] = I2CMasterDataGet(I2C_BASE);
}
