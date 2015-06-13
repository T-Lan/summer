
#include <avr/io.h>

/**
 * @brief init_spi_master
 * set MCU as master
 * configure pin direction
 * configure SPI clock rate
 * enable SPI
 */
void init_spi_master(void);

/**
 * @brief spi
 * @param b: 8-bit data to be sent
 * @return 8-bit data received
 */
uint8_t spi(uint8_t b);


