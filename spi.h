
#include <avr/io.h>

/**
 * @brief InitSPIMaster
 * set MCU as master
 * configure pin direction
 * configure SPI clock rate
 * enable SPI
 */
void InitSPIMaster(void);


uin8_t SingleTransfer(uint8_t data);
void BurstTransfer(uint8_t* data, uint8_t len);
void slave_sel();
void slave_unsel();
