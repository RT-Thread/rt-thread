/*******************************************************************************
 * (c) Copyright 2011-2013 Microsemi SoC Products Group. All rights reserved.
 *
 *  SmartFusion2 Cortex Microcontroller Software Interface - Peripheral
 *  Access Layer.
 *
 *  This file provides interfaces to perform register and register bit level 
 *  read / write operations. These interfaces support bit-banding in case of 
 *  Cortex-M3 CPU.
 *
 * SVN $Revision: 5263 $
 * SVN $Date: 2013-03-21 14:44:58 +0000 (Thu, 21 Mar 2013) $
 */

#ifndef HW_REG_IO_H_
#define HW_REG_IO_H_

#include <stdint.h>                       /* Include standard types */

#if defined ( __CC_ARM   )
  #define __INLINE         __inline       /*!< inline keyword for ARM Compiler       */

#elif defined ( __ICCARM__ )
  #define __INLINE        inline          /*!< inline keyword for IAR Compiler. Only avaiable in High optimization mode! */

#elif defined   (  __GNUC__  )
  #define __INLINE        inline          /*!< inline keyword for GNU Compiler       */
#endif

/*****************************************************************************************
 * Definitions for register access
 */

#define HW_REG(addr)            (*((volatile uint32_t *) (addr)))

static __INLINE void write_reg32(volatile uint32_t * reg, uint32_t val)
{
    HW_REG(reg) = val;
}
static __INLINE void write_reg16(volatile uint16_t * reg, uint16_t val)
{
    HW_REG(reg) = val;
}
static __INLINE void write_reg8(volatile uint8_t * reg, uint8_t val)
{
    HW_REG(reg) = val;
}

static __INLINE uint32_t read_reg32(volatile uint32_t * reg)
{
    return ( HW_REG(reg) );
}
static __INLINE uint16_t read_reg16(volatile uint16_t * reg)
{
    return ( HW_REG(reg) );
}
static __INLINE uint8_t read_reg8(volatile uint8_t * reg)
{
    return ( HW_REG(reg) );
}
/*****************************************************************************************
 * Definitions for register bits access using bit-band aliases for Cortex-M3 
 */
#define BITBAND(addr,bitnum)    (((uint32_t)addr & 0xF0000000)+0x02000000+(((uint32_t)addr & 0xFFFFF)<<5)+(bitnum<<2))
#define HW_REG_BIT(reg,bitnum)  (*(volatile unsigned int *)((BITBAND(reg,bitnum))))

/*****************************************************************************************
 * Functions to set a bit field in Cortex-M3 
 */
static __INLINE void set_bit_reg32(volatile uint32_t * reg, uint8_t bit)
{
    HW_REG_BIT(reg,bit) = 0x1;
}
static __INLINE void set_bit_reg16(volatile uint16_t * reg, uint8_t bit)
{
    HW_REG_BIT(reg,bit) = 0x1;
}
static __INLINE void set_bit_reg8(volatile uint8_t * reg, uint8_t bit)
{
    HW_REG_BIT(reg,bit) = 0x1;
}
/*****************************************************************************************
 * Functions to clear a bit field in Cortex-M3
 */
static __INLINE void clear_bit_reg32(volatile uint32_t * reg, uint8_t bit)
{
    HW_REG_BIT(reg,bit) = 0x0;
}
static __INLINE void clear_bit_reg16(volatile uint16_t * reg, uint8_t bit)
{
    HW_REG_BIT(reg,bit) = 0x0;
}
static __INLINE void clear_bit_reg8(volatile uint8_t * reg, uint8_t bit)
{
    HW_REG_BIT(reg,bit) = 0x0;
}
/*****************************************************************************************
 * Functions to read a bit field in Cortex-M3
 */
static __INLINE uint8_t read_bit_reg32(volatile uint32_t * reg, uint8_t bit)
{
    return (HW_REG_BIT(reg,bit));
}
static __INLINE uint8_t read_bit_reg16(volatile uint16_t * reg, uint8_t bit)
{
    return (HW_REG_BIT(reg,bit));
}
static __INLINE uint8_t read_bit_reg8(volatile uint8_t * reg, uint8_t bit)
{
    return (HW_REG_BIT(reg,bit));
}

#endif /* HW_REG_IO_H_ */
