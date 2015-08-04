
#include "spi.h"

void InitSPIMaster(void)
{
        // CSn, MOSI, SCK output
        // dont have to set MISO as input by DDRB?
        DDRB = _BV(PB4) | _BV(PB5) | _BV(PB7);

        // enable SPI, set MCU as master, SPI clock rate (what is the clock rate?)
        SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0); /* F_SCK = F_CPU/16 = 750 kHz */
}

void BurstTransfer(uint8_t* data, uint8_t len)
{
	uint8_t i;

	for (i = 0; i<len; i++)
	{
                data[i] = SingleTransfer(data[i]);
	}
}

uint8_t SingleTransfer(uint8_t data)
{
        SPDR = data;
        while(!(SPSR & _BV(SPIF)));
        return SPDR;
}

void SlaveSel()
{
	PORTB &= ~_BV(4);
}

void SlaveUnsel()
{
	PORTB |= _BV(4);
}
