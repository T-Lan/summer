#include <stdio.h>
#include "config.h"
#include "spi.h"

int main(void)
{
  // init serial
  init_debug_uart0();
  printf("debugging tool set up.");

  // config CC1125
  init_cc1125();

  while (1)
  {

  }



  return 1;
}

