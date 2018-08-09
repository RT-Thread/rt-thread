#ifndef _BOARD_H_
#define _BOARD_H_

#include <rtthread.h>

#include "nrf.h"

#define CHIP_SRAM_END       (0x20000000 + 64*1024)

/**@brief Macro for converting milliseconds to ticks.
 *
 * @param[in] TIME          Number of milliseconds to convert.
 */
#define MSEC_TO_OS_TICK(TIME) ((TIME) * (RT_TIMER_TICK_PER_SECOND)/1000)

void rt_hw_board_init(void);

#endif
