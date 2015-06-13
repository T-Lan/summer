#include "config.h"
#include "spi.h"
#include "register.h"

void init_cc1125()
{
  init_spi_master();

  // configuration register through burst write
  // data pointers! change!
  BurstRegAccess(WRITE, 0x0000, config_val, 47);

  // ext config reg through single write

  // set mode



}

uint8_t SingleRegAccess(uint8_t r_nw, uint16_t addr, uint8_t* pointer)
{
    // check if it is an extended config reg
    uint8_t TempExt = (uint8_t) (addr >>8);
    uint8_t TempAddr = (uint8_t)(addr & 0x00FF);

    // chip status received from sending header byte/or command if it is ext.
    uint8_t ChipStatus;

    if (TempExt == 0)
    {
      //configuraion registers
      ChipStatus = spi(r_nw|TempAddr);
      SingleTransfer (pointer);
    }
    else if (TempExt == 0x2F)
    {
      //extended configuration registers
      ChipStatus = spi(r_nw|0x2F);
      spi(TempAddr);
      SingleTransfer (pointer);
    }

    return ChipStatus;
}

uint8_t BurstRegAccess(uint8_t r_nw, uint16_t addr, uint8_t *pointer, uint8_t len)
{
    //check if it is extended reg
    // check if it is an extended config reg
    uint8_t TempExt = (uint8_t) (addr >>8);
    uint8_t TempAddr = (uint8_t)(addr & 0x00FF);


    // chip status received from sending header byte/or command if it is ext.
    uint8_t ChipStatus;
    if (TempExt == 0)
    {
      //configuration registers
      ChipStatus = spi(r_nw|BURST|TempAddr);
      BurstTransfer(pointer, len);
    }
    else if (TempExt == 0x2F)
    {
        //exteneded configuration registers
        ChipStatus = spi(r_nw|BURST|0x2F);
        spi(TempAddr);
        BurstTransfer(pointer, len);
    }
    return ChipStatus;
}

uint8_t CommandStrobe(uint8_t r_nw,uint8_t cmd)
{
  //why do we read command strobe?
  return (spi(r_nw|cmd));
}

uint8_t DirFIFOAccess(uint8_t r_nw, uint8_t addr, uint8_t* pointer, uint8_t len)
{
  uint8_t ChipStatus;

  if (len==1)
  {
    //single access
    ChipStatus = spi(r_nw|0x3E);
    spi(addr);
    SingleTransfer(pointer);
  }
  else
  {
    //burst access
    ChipStatus = spi(r_nw|BURST|0x3E);
    spi(addr);
    BurstTransfer(pointer,len);
  }
  return ChipStatus;
}

uint8_t StandardFIFOAccess (uint8_t dirFIFO, uint8_t* pointer,uint8_t len)
{
  uint8_t ChipStatus;
  if (len ==1)
  {
    //single access
    if (dirFIFO == RX)
    {
        ChipStatus = spi(CC1125_SINGLE_RXFIFO);
        SingleTransfer(pointer);
    }
    else if (dirFIFO == TX)
    {
      ChipStatus = spi(CC1125_SINGLE_TXFIFO);
      SingleTransfer(pointer);
    }
    else
      return 0;
  }
  else
  {
    if(dirFIFO == RX)
    {
      ChipStatus = spi(CC1125_BURST_RXFIFO);
      BurstTransfer(pointer,len);
    }
    else if (dirFIFO == TX)
    {
      ChipStatus = spi(CC1125_BURST_TXFIFO);
      BurstTransfer(pointer,len);
    }
    else
      return 0;
  }

  return ChipStatus;
}

void SingleTransfer (uint8_t *pointer)
{
    *pointer = spi(*pointer);
    // pull CSn high to terminate transfer
    PORTB |= _BV(4);
}

void BurstTransfer(uint8_t *pointer, uint8_t len)
{
  uint8_t i;
  for (i = 0;i<len;i++)
  {
    *pointer = spi(*pointer);
    pointer = pointer+1;
  }
  // pull CSn high to terminate transfer
  PORTB |= _BV(4);

}
