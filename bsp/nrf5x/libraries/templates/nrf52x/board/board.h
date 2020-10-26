#ifndef _BOARD_H_
#define _BOARD_H_

#include <rtthread.h>

#include "nrf.h"

#define CHIP_SRAM_END       (0x20000000 + 64*1024)

void rt_hw_board_init(void);

#endif

