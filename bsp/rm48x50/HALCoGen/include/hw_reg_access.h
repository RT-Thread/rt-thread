/*
 * hw_reg_access.h.h
 */

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef _HW_REG_ACCESS_H_
#define _HW_REG_ACCESS_H_

/*******************************************************************************
*
* Macros for hardware access, both direct and via the bit-band region.
*
*****************************************************************************/
#define HWREG(x)                                                              \
        (*((volatile uint32 *)(x)))
#define HWREGH(x)                                                             \
        (*((volatile uint16 *)(x)))
#define HWREGB(x)                                                             \
        (*((volatile uint8 *)(x)))
#define HWREGBITW(x, b)                                                       \
        HWREG(((uint32)(x) & 0xF0000000U) | 0x02000000U |                \
              (((uint32)(x) & 0x000FFFFFU) << 5U) | ((b) << 2U))
#define HWREGBITH(x, b)                                                       \
        HWREGH(((uint32)(x) & 0xF0000000U) | 0x02000000U |               \
               (((uint32)(x) & 0x000FFFFFU) << 5U) | ((b) << 2U))
#define HWREGBITB(x, b)                                                       \
        HWREGB(((uint32)(x) & 0xF0000000U) | 0x02000000U |               \
               (((uint32)(x) & 0x000FFFFFU) << 5U) | ((b) << 2U))



#endif /* __HW_TYPES_H__ */
