/*******************************************************************************
 * (c) Copyright 2007-2013 Microsemi SoC Products Group. All rights reserved.
 * 
 *  Hardware registers access macros.
 * 
 *  THE MACROS DEFINED IN THIS FILE ARE DEPRECATED. DO NOT USED FOR NEW 
 *  DEVELOPMENT.
 *
 * These macros are used to access peripheral's registers. They allow access to
 * 8, 16 and 32 bit wide registers. All accesses to peripheral registers should
 * be done through these macros in order to ease porting accross different 
 * processors/bus architectures.
 * 
 * Some of these macros also allow to access a specific register field.
 * 
 * SVN $Revision: 5258 $
 * SVN $Date: 2013-03-21 18:11:02 +0530 (Thu, 21 Mar 2013) $
 */
#ifndef __HW_REGISTER_MACROS_H
#define __HW_REGISTER_MACROS_H  1

/*------------------------------------------------------------------------------
 * 32 bits registers access:
 */
#define HW_get_uint32_reg(BASE_ADDR, REG_OFFSET) (*((uint32_t volatile *)(BASE_ADDR + REG_OFFSET##_REG_OFFSET)))

#define HW_set_uint32_reg(BASE_ADDR, REG_OFFSET, VALUE) (*((uint32_t volatile *)(BASE_ADDR + REG_OFFSET##_REG_OFFSET)) = (VALUE))

#define HW_set_uint32_reg_field(BASE_ADDR, FIELD, VALUE) \
            (*((uint32_t volatile *)(BASE_ADDR + FIELD##_OFFSET)) =  \
                ( \
                    (uint32_t) \
                    ( \
                    (*((uint32_t volatile *)(BASE_ADDR + FIELD##_OFFSET))) & ~FIELD##_MASK) | \
                    (uint32_t)(((VALUE) << FIELD##_SHIFT) & FIELD##_MASK) \
                ) \
            )

#define HW_get_uint32_reg_field( BASE_ADDR, FIELD ) \
            (( (*((uint32_t volatile *)(BASE_ADDR + FIELD##_OFFSET))) & FIELD##_MASK) >> FIELD##_SHIFT)

/*------------------------------------------------------------------------------
 * 32 bits memory access:
 */
#define HW_get_uint32(BASE_ADDR) (*((uint32_t volatile *)(BASE_ADDR)))

#define HW_set_uint32(BASE_ADDR, VALUE) (*((uint32_t volatile *)(BASE_ADDR)) = (VALUE))

/*------------------------------------------------------------------------------
 * 16 bits registers access:
 */
#define HW_get_uint16_reg(BASE_ADDR, REG_OFFSET) (*((uint16_t volatile *)(BASE_ADDR + REG_OFFSET##_REG_OFFSET)))

#define HW_set_uint16_reg(BASE_ADDR, REG_OFFSET, VALUE) (*((uint16_t volatile *)(BASE_ADDR + REG_OFFSET##_REG_OFFSET)) = (VALUE))

#define HW_set_uint16_reg_field(BASE_ADDR, FIELD, VALUE) \
            (*((uint16_t volatile *)(BASE_ADDR + FIELD##_OFFSET)) =  \
                ( \
                    (uint16_t) \
                    ( \
                    (*((uint16_t volatile *)(BASE_ADDR + FIELD##_OFFSET))) & ~FIELD##_MASK) | \
                    (uint16_t)(((VALUE) << FIELD##_SHIFT) & FIELD##_MASK) \
                ) \
            )

#define HW_get_uint16_reg_field( BASE_ADDR, FIELD ) \
            (( (*((uint16_t volatile *)(BASE_ADDR + FIELD##_OFFSET))) & FIELD##_MASK) >> FIELD##_SHIFT)

/*------------------------------------------------------------------------------
 * 8 bits registers access:
 */
#define HW_get_uint8_reg(BASE_ADDR, REG_OFFSET) (*((uint8_t volatile *)(BASE_ADDR + REG_OFFSET##_REG_OFFSET)))

#define HW_set_uint8_reg(BASE_ADDR, REG_OFFSET, VALUE) (*((uint8_t volatile *)(BASE_ADDR + REG_OFFSET##_REG_OFFSET)) = (VALUE))
 
#define HW_set_uint8_reg_field(BASE_ADDR, FIELD, VALUE) \
            (*((uint8_t volatile *)(BASE_ADDR + FIELD##_OFFSET)) =  \
                ( \
                    (uint8_t) \
                    ( \
                    (*((uint8_t volatile *)(BASE_ADDR + FIELD##_OFFSET))) & ~FIELD##_MASK) | \
                    (uint8_t)(((VALUE) << FIELD##_SHIFT) & FIELD##_MASK) \
                ) \
            )

#define HW_get_uint8_reg_field( BASE_ADDR, FIELD ) \
            (( (*((uint8_t volatile *)(BASE_ADDR + FIELD##_OFFSET))) & FIELD##_MASK) >> FIELD##_SHIFT)

/*------------------------------------------------------------------------------
 * 8 bits memory access:
 */
#define HW_get_uint8(BASE_ADDR) (*((uint8_t volatile *)(BASE_ADDR)))

#define HW_set_uint8(BASE_ADDR, VALUE) (*((uint8_t volatile *)(BASE_ADDR)) = (VALUE))
 
#endif  /* __HW_REGISTER_MACROS_H */
