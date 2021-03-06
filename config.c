#include "config.h"
#include "spi.h"
#include "register.h"

void Initcc1125()
{
	init_spi_master();

	// configure registers
	// set mode

}

uint8_t SingleRegAccess(uint8_t r_nw, uint16_t addr, uint8_t* data)
{
    // check if it is an extended config reg
    uint8_t TempExt = (uint8_t) (addr >>8);
    uint8_t TempAddr = (uint8_t)(addr & 0x00FF);

    // chip status received from sending addr byte (or command if it is ext).
    uint8_t ChipStatus;

    if (TempExt == 0)
    {
      //configuraion registers
      SlaveSel();
      ChipStatus = SingleTransfer(r_nw|TempAddr);
      *data = SingleTransfer(*data);
      SlaveUnsel();

    }
    else if (TempExt == 0x2F)
    {
      //extended configuration registers
        SlaveSel();
        ChipStatus = SingleTransfer(r_nw|0x2F);
        SingleTransfer(TempAddr);
        *data = SingleTransfer(*data);
        SlaveUnsel();
    }
    return ChipStatus;
}


uint8_t BurstRegAccess(uint8_t r_nw, uint16_t addr, uint8_t *data, uint8_t len)
{
    // check if it is an extended config reg
    uint8_t TempExt = (uint8_t) (addr >>8);
    uint8_t TempAddr = (uint8_t)(addr & 0x00FF);


    // chip status received from sending addr byte (or command if it is ext).
    uint8_t ChipStatus;
    if (TempExt == 0)
    {
      //configuration registers
        SlaveSel();
        ChipStatus = SingleTransfer(r_nw | BURST | TempAddr);
        BurstTransfer(data, len);
        SlaveUnsel();
    }
    else if (TempExt == 0x2F)
    {
        //exteneded configuration registers

        SlaveSel();
        ChipStatus = SingleTransfer(r_nw | BURST | 0x2F);
        SingleTransfer(TempAddr);
        BurstTransfer(data,len);
        SlaveUnsel();
    }
    return ChipStatus;
}


uint8_t CommandStrobe(uint8_t cmd)
{
    uint8_t ChipStatus;
    SlaveSel();
    ChipStatus = SingleTransfer(cmd);
    SlaveUnsel();
    return ChipStatus;
}



//direct FIFO Access can be used for debugging purposes together with the FIFO pointers from ext regs.
//addr < 0x80: TX FIFO
//0x80 ≤ addr ≤ 0xFF: RX FIFO
uint8_t DirFIFOAccess(uint8_t r_nw, uint8_t addr, uint8_t* data, uint8_t len)
{
  uint8_t ChipStatus;

  if (len==1)
  {
    //single access
    SlaveSel();
    ChipStatus = SingleTransfer(r_nw|0x3E);
    SingleTransfer(addr);
    SingleTransfer(*data);
    SlaveUnsel();
  }
  else
  {
    //burst access
    SlaveSel();
    ChipStatus = SingleTransfer(r_nw|BURST|0x3E);
    SignleTransfer(addr);
    BurstTransfer(data,len);
    SlaveUnsel();
  }
  return ChipStatus;
}


uint8_t StandardFIFOAccess (uint8_t dirFIFO, uint8_t* data,uint8_t len)
{
  uint8_t ChipStatus;
  if (len ==1)
  {
    //single access
    if (dirFIFO == RX)
        ChipStatus = SingleStandardFIFO(CC1125_SINGLE_RXFIFO, *data);
    else if (dirFIFO == TX)
        ChipStatus = SingleStandardFIFO(CC1125_SINGLE_TXFIFO, *data);
         else
            return 0;
  }
  else
  {
    if(dirFIFO == RX)
        ChipStatus = BurstStandardFIFO(CC1125_BURST_RXFIFO, data, len);
    else if (dirFIFO == TX)
            ChipStatus = BurstStandardFIFO(CC1125_BURST_TXFIFO, data, len);
         else
            return 0;
  }

  return ChipStatus;
}


uint8_t SingleStandardFIFO (uint16_t reg, uint8_t* data)
{
    uint8_t ChipStatus;
    SlaveSel();
    ChipStatus = SingleTransfer(reg);
    SingleTransfer(*data);
    SlaveUnsel();
    return ChipStatus;
}

uint8_t BurstStandardFIFO (uint16_t reg, uint8_t* data, uint8_t len)
{
    uint8_t ChipStatus;
    SlaveSel();
    ChipStatus = SingleTransfer(reg);
    BurstTransfer(data,len);
    SlaveUnsel();
    return ChipStatus;
}
