
#include "spi.h"

void init_spi_master(void)
{
        // CSn, MOSI, SCK output
        // dont have to set MISO as input by DDRB?
        DDRB = _BV(PB4) | _BV(PB5) | _BV(PB7);

        // enable SPI, set MCU as master, SPI clock rate (what is the clock rate?)
        SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0); /* F_SCK = F_CPU/16 = 750 kHz */
}

uint8_t spi(uint8_t b)
{
        // set CSn low ????
        // datasheet p8 : When CSn is pulled low, the MCU must wait until CC112X SO pin goes low before starting to transfer the header byte.
        // is it necessary to write a function for header byte to wait for SO going low?
        PORTB &= ~_BV(4);

        SPDR = b;
        while(!(SPSR & _BV(SPIF)));
        return SPDR;
        // leave CSn low in case of burst?
        // for single access, leave it low??


}
