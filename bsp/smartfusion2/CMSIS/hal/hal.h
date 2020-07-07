/***************************************************************************//**
 * (c) Copyright 2007-2013 Microsemi SoC Products Group. All rights reserved.
 * 
 * Hardware abstraction layer functions.
 * 
 * SVN $Revision: 5258 $
 * SVN $Date: 2013-03-21 18:11:02 +0530 (Thu, 21 Mar 2013) $
 */
#ifndef HAL_H_
#define HAL_H_

#include "cpu_types.h"
#include "hw_reg_access.h"

/***************************************************************************//**
 * Enable all interrupts at the processor level.
 */
void HAL_enable_interrupts( void );

/***************************************************************************//**
 * Disable all interrupts at the processor core level.
 * Return the interrupts enable state before disabling occured so that it can 
 * later be restored. 
 */
psr_t HAL_disable_interrupts( void );

/***************************************************************************//**
 * Restore the interrupts enable state at the processor core level.
 * This function is normally passed the value returned from a previous call to
 * HAL_disable_interrupts(). 
 */
void HAL_restore_interrupts( psr_t saved_psr );

/***************************************************************************//**
 */
#define FIELD_OFFSET(FIELD_NAME)  (FIELD_NAME##_OFFSET)
#define FIELD_SHIFT(FIELD_NAME)   (FIELD_NAME##_SHIFT)
#define FIELD_MASK(FIELD_NAME)    (FIELD_NAME##_MASK)

/***************************************************************************//**
 * The macro HAL_set_32bit_reg() allows writing a 32 bits wide register.
 *
 * BASE_ADDR:   A variable of type addr_t specifying the base address of the
 *              peripheral containing the register.
 * REG_NAME:    A string identifying the register to write. These strings are
 *              specified in a header file associated with the peripheral.
 * VALUE:       A variable of type uint32_t containing the value to write.
 */
#define HAL_set_32bit_reg(BASE_ADDR, REG_NAME, VALUE) \
          (HW_set_32bit_reg( ((BASE_ADDR) + (REG_NAME##_REG_OFFSET)), (VALUE) ))

/***************************************************************************//**
 * The macro HAL_get_32bit_reg() is used to read the value  of a 32 bits wide
 * register.
 * 
 * BASE_ADDR:   A variable of type addr_t specifying the base address of the
 *              peripheral containing the register.
 * REG_NAME:    A string identifying the register to read. These strings are
 *              specified in a header file associated with the peripheral.
 * RETURN:		This function-like macro returns a uint32_t value.
 */
#define HAL_get_32bit_reg(BASE_ADDR, REG_NAME) \
          (HW_get_32bit_reg( ((BASE_ADDR) + (REG_NAME##_REG_OFFSET)) ))

/***************************************************************************//**
 * The macro HAL_set_32bit_reg_field() is used to write a field within a
 * 32 bits wide register. The field written can be one or more bits.
 * 
 * BASE_ADDR:   A variable of type addr_t specifying the base address of the
 *              peripheral containing the register.
 * FIELD_NAME:  A string identifying the register field to write. These strings
 * 				are specified in a header file associated with the peripheral.
 * VALUE:       A variable of type uint32_t containing the field value to write.
 */
#define HAL_set_32bit_reg_field(BASE_ADDR, FIELD_NAME, VALUE) \
            (HW_set_32bit_reg_field(\
                (BASE_ADDR) + FIELD_OFFSET(FIELD_NAME),\
                FIELD_SHIFT(FIELD_NAME),\
                FIELD_MASK(FIELD_NAME),\
                (VALUE)))
  
/***************************************************************************//**
 * The macro HAL_get_32bit_reg_field() is used to read a register field from
 * within a 32 bit wide peripheral register. The field can be one or more bits.
 * 
 * BASE_ADDR:   A variable of type addr_t specifying the base address of the
 *              peripheral containing the register.
 * FIELD_NAME:  A string identifying the register field to write. These strings
 * 				are specified in a header file associated with the peripheral.
 * RETURN:		This function-like macro returns a uint32_t value.
 */
#define HAL_get_32bit_reg_field(BASE_ADDR, FIELD_NAME) \
            (HW_get_32bit_reg_field(\
                (BASE_ADDR) + FIELD_OFFSET(FIELD_NAME),\
                FIELD_SHIFT(FIELD_NAME),\
                FIELD_MASK(FIELD_NAME)))
  
/***************************************************************************//**
 * The macro HAL_set_16bit_reg() allows writing a 16 bits wide register.
 *
 * BASE_ADDR:   A variable of type addr_t specifying the base address of the
 *              peripheral containing the register.
 * REG_NAME:    A string identifying the register to write. These strings are
 *              specified in a header file associated with the peripheral.
 * VALUE:       A variable of type uint_fast16_t containing the value to write.
 */
#define HAL_set_16bit_reg(BASE_ADDR, REG_NAME, VALUE) \
            (HW_set_16bit_reg( ((BASE_ADDR) + (REG_NAME##_REG_OFFSET)), (VALUE) ))

/***************************************************************************//**
 * The macro HAL_get_16bit_reg() is used to read the value  of a 16 bits wide
 * register.
 * 
 * BASE_ADDR:   A variable of type addr_t specifying the base address of the
 *              peripheral containing the register.
 * REG_NAME:    A string identifying the register to read. These strings are
 *              specified in a header file associated with the peripheral.
 * RETURN:		This function-like macro returns a uint16_t value.
 */
#define HAL_get_16bit_reg(BASE_ADDR, REG_NAME) \
            (HW_get_16bit_reg( (BASE_ADDR) + (REG_NAME##_REG_OFFSET) ))

/***************************************************************************//**
 * The macro HAL_set_16bit_reg_field() is used to write a field within a
 * 16 bits wide register. The field written can be one or more bits.
 * 
 * BASE_ADDR:   A variable of type addr_t specifying the base address of the
 *              peripheral containing the register.
 * FIELD_NAME:  A string identifying the register field to write. These strings
 * 				are specified in a header file associated with the peripheral.
 * VALUE:       A variable of type uint16_t containing the field value to write.
 */
#define HAL_set_16bit_reg_field(BASE_ADDR, FIELD_NAME, VALUE) \
            (HW_set_16bit_reg_field(\
                (BASE_ADDR) + FIELD_OFFSET(FIELD_NAME),\
                FIELD_SHIFT(FIELD_NAME),\
                FIELD_MASK(FIELD_NAME),\
                (VALUE)))  

/***************************************************************************//**
 * The macro HAL_get_16bit_reg_field() is used to read a register field from
 * within a 8 bit wide peripheral register. The field can be one or more bits.
 * 
 * BASE_ADDR:   A variable of type addr_t specifying the base address of the
 *              peripheral containing the register.
 * FIELD_NAME:  A string identifying the register field to write. These strings
 * 				are specified in a header file associated with the peripheral.
 * RETURN:		This function-like macro returns a uint16_t value.
 */
#define HAL_get_16bit_reg_field(BASE_ADDR, FIELD_NAME) \
            (HW_get_16bit_reg_field(\
                (BASE_ADDR) + FIELD_OFFSET(FIELD_NAME),\
                FIELD_SHIFT(FIELD_NAME),\
                FIELD_MASK(FIELD_NAME)))

/***************************************************************************//**
 * The macro HAL_set_8bit_reg() allows writing a 8 bits wide register.
 *
 * BASE_ADDR:   A variable of type addr_t specifying the base address of the
 *              peripheral containing the register.
 * REG_NAME:    A string identifying the register to write. These strings are
 *              specified in a header file associated with the peripheral.
 * VALUE:       A variable of type uint_fast8_t containing the value to write.
 */
#define HAL_set_8bit_reg(BASE_ADDR, REG_NAME, VALUE) \
          (HW_set_8bit_reg( ((BASE_ADDR) + (REG_NAME##_REG_OFFSET)), (VALUE) ))

/***************************************************************************//**
 * The macro HAL_get_8bit_reg() is used to read the value of a 8 bits wide
 * register.
 * 
 * BASE_ADDR:   A variable of type addr_t specifying the base address of the
 *              peripheral containing the register.
 * REG_NAME:    A string identifying the register to read. These strings are
 *              specified in a header file associated with the peripheral.
 * RETURN:		This function-like macro returns a uint8_t value.
 */
#define HAL_get_8bit_reg(BASE_ADDR, REG_NAME) \
          (HW_get_8bit_reg( (BASE_ADDR) + (REG_NAME##_REG_OFFSET) ))

/***************************************************************************//**
 */
#define HAL_set_8bit_reg_field(BASE_ADDR, FIELD_NAME, VALUE) \
            (HW_set_8bit_reg_field(\
                (BASE_ADDR) + FIELD_OFFSET(FIELD_NAME),\
                FIELD_SHIFT(FIELD_NAME),\
                FIELD_MASK(FIELD_NAME),\
                (VALUE)))

/***************************************************************************//**
 * The macro HAL_get_8bit_reg_field() is used to read a register field from
 * within a 8 bit wide peripheral register. The field can be one or more bits.
 * 
 * BASE_ADDR:   A variable of type addr_t specifying the base address of the
 *              peripheral containing the register.
 * FIELD_NAME:  A string identifying the register field to write. These strings
 * 				are specified in a header file associated with the peripheral.
 * RETURN:		This function-like macro returns a uint8_t value.
 */
#define HAL_get_8bit_reg_field(BASE_ADDR, FIELD_NAME) \
            (HW_get_8bit_reg_field(\
                (BASE_ADDR) + FIELD_OFFSET(FIELD_NAME),\
                FIELD_SHIFT(FIELD_NAME),\
                FIELD_MASK(FIELD_NAME)))
  
#endif /*HAL_H_*/
