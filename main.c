#include <stdio.h>
#include "config.h"

int main(void)
{
  // init serial
  init_debug_uart0();

  // config CC1125
  init_cc1125();



  return 0;
}

