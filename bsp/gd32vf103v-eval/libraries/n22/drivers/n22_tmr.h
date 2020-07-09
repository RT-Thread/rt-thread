// See LICENSE file for licence details

#ifndef N22_TMR_H
#define N22_TMR_H

#define TMR_MSIP 0xFFC
#define TMR_MSIP_size   0x4
#define TMR_MTIMECMP 0x8
#define TMR_MTIMECMP_size 0x8
#define TMR_MTIME 0x0
#define TMR_MTIME_size 0x8

#define TMR_CTRL_ADDR           0xd1000000
#define TMR_REG(offset)         _REG32(TMR_CTRL_ADDR, offset)
#define TMR_FREQ	            ((uint32_t)SystemCoreClock/4)  //units HZ

#endif
