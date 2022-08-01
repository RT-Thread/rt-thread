/* See LICENSE file for licence details */

#ifndef N200_TIMER_H
#define N200_TIMER_H

#define TIMER_MSIP 0xFFC
#define TIMER_MSIP_size   0x4
#define TIMER_MTIMECMP 0x8
#define TIMER_MTIMECMP_size 0x8
#define TIMER_MTIME 0x0
#define TIMER_MTIME_size 0x8

#define TIMER_CTRL_ADDR           0xd1000000
#define TIMER_REG(offset)         _REG32(TIMER_CTRL_ADDR, offset)
#define TIMER_FREQ                ((uint32_t)SystemCoreClock/4)

#endif

