#ifndef BOARD_H__
#define BOARD_H__

#include <stdint.h>

/* V861 / V881 C907. FEL writes this image at 0x40000000.
 * RT_USING_SMP: dual C907 with CLINT MSIP IPI. */
#define V861_DRAM_BASE          0x40000000
#define V861_DRAM_SIZE          0x00200000

#define V861_UART0_BASE         0x02500000
#define V861_UART0_CLOCK_HZ     24000000
#define V861_UART0_BAUD         115200
#define V861_PIO_PH_CFG1        0x02000154
#define V861_PH9_PH10_MUX_MASK  0xFFFFF00F
#define V861_PH9_PH10_MUX5      0x00000550

extern unsigned int __bss_end;
extern unsigned int __stack_start__;

#define RT_HW_HEAP_BEGIN ((void *)&__bss_end)
#define RT_HW_HEAP_END   ((void *)(V861_DRAM_BASE + V861_DRAM_SIZE))

void rt_hw_board_init(void);

#endif
