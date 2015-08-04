#ifndef CONFIG_H
#define CONFIG_H
// It is not possible in C to creat 2D array with different data types. Create 2 arrays instead, each storing register name and configuration value. My strategy is to match line number -.-
// Comment out register name array and use burst mode to configure configuration registers
// use single mode to configure extended configuration registers
#include <avr/io.h>
// #include"register.h", only for array of 47 configuration registers

#define READ 0x80
#define RX 0x80
#define WRITE 0x00
#define TX 0x00
#define BURST 0x40

// Array of 47 configuration registers. In case burst write fails, loop through both arrays with single register access function.
/*static const uint16_t config_reg[47]=
{
    // configuration registers only
    // extended configuration registers are to be set individually
    CC1125_IOCFG3,
    CC1125_IOCFG2,
    CC1125_IOCFG1,
    CC1125_IOCFG0,
    CC1125_SYNC3,
    CC1125_SYNC2,
    CC1125_SYNC1,
    CC1125_SYNC0,
    CC1125_SYNC_CFG1,
    CC1125_SYNC_CFG0,
    CC1125_DEVIATION_M,
    CC1125_MODCFG_DEV_E,
    CC1125_DCFILT_CFG,
    CC1125_PREAMBLE_CFG1,
    CC1125_PREAMBLE_CFG0,
    CC1125_FREQ_IF_CFG,
    CC1125_IQIC,
    CC1125_CHAN_BW,
    CC1125_MDMCFG1,
    CC1125_MDMCFG0,
    CC1125_SYMBOL_RATE2,
    CC1125_SYMBOL_RATE1,
    CC1125_SYMBOL_RATE0,
    CC1125_AGC_REF,
    CC1125_AGC_CS_THR,
    CC1125_AGC_GAIN_ADJUST,
    CC1125_AGC_CFG3,
    CC1125_AGC_CFG2,
    CC1125_AGC_CFG1,
    CC1125_AGC_CFG0,
    CC1125_FIFO_CFG,
    CC1125_DEV_ADDR,
    CC1125_SETTLING_CFG,
    CC1125_FS_CFG,
    CC1125_WOR_CFG1,
    CC1125_WOR_CFG0,
    CC1125_WOR_EVENT0_MSB,
    CC1125_WOR_EVENT0_LSB,
    CC1125_PKT_CFG2,
    CC1125_PKT_CFG1,
    CC1125_PKT_CFG0,
    CC1125_RFEND_CFG1,
    CC1125_RFEND_CFG0,
    CC1125_PA_CFG2,
    CC1125_PA_CFG1,
    CC1125_PA_CFG0,
    CC1125_PKT_LEN
};*/

// Array of 47 configuration registers values.
static const uint8_t config_val[47]=
{
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};


//prototypes

/**
 * @brief init_cc1125: initialise the chip, set up config reg through burst, ext config reg through single, set mode etc.
 */
void init_cc1125();

/**
 * @brief SingleRegAccess
 * @param r_nw: either READ or WRITE as defined above
 * @param addr: 16-bit register address as defined in register.h
 * @param data: data to be written or the variable to hold the read value
 * @return: chip status received from sending the header byte
*/

uint8_t SingleRegAccess(uint8_t r_nw, uint16_t addr, uint8_t data);

/**
 * @brief BurstRegAccess
 * @param r_nw: either READ or WRITE as defined above
 * @param addr: 16-bit register address as defined in register.h
 * @param data: the byte array which holds the data
 * @param len: number of bytes in the array, max 8-bit = 256
 * @return: chip status received from sending the header byte
 */
uint8_t BurstRegAccess(uint8_t r_nw, uint16_t addr, uint8_t* data, uint8_t len);


/**
 * @brief CommandStrobe
 * @param r_nw: either READ or WRITE as defined above ==> why r_nw needed???
 * @param cmd: 8-bit command strobe registers as defined by register.h (0x30 to 0x3D)
 * @return: chip status received from sending the command
 */
uint8_t CommandStrobe(uint8_t r_nw,uint8_t cmd);

/**
 * @brief DirFIFOAccess
 * @param r_nw: either READ or WRITE
 * @param addr: 8-bit FIFO register address, can refer to the ext reg 0x2FD2 through 0x2FD5 (FIFO pointers)
 * @param data
 * @param len: data length
 * @return: chip status received from sending the command 0x3E
 */
uint8_t DirFIFOAccess(uint8_t r_nw, uint8_t addr, uint8_t data, uint8_t len);


/**
 * @brief StandardFIFOAccess
 * @param dirFIFO: either RX or TX, equivalent to WRITE or READ respectively
 * @param data
 * @param len: data length
 * @return: chip status received from sending the address
 */
uint8_t StandardFIFOAccess (uint8_t dirFIFO, uint8_t data,uint8_t len);


#endif // CONFIG_H

