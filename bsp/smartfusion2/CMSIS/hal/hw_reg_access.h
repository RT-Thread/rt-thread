/***************************************************************************//**
 * (c) Copyright 2007-2013 Microsemi SoC Products Group. All rights reserved.
 * 
 * Hardware registers access functions.
 * The implementation of these function is platform and toolchain specific.
 * The functions declared here are implemented using assembler as part of the 
 * processor/toolchain specific HAL.
 * 
 * SVN $Revision: 5258 $
 * SVN $Date: 2013-03-21 18:11:02 +0530 (Thu, 21 Mar 2013) $
 */
#ifndef HW_REG_ACCESS
#define HW_REG_ACCESS

/***************************************************************************//**
 * HW_set_32bit_reg is used to write the content of a 32 bits wide peripheral
 * register.
 * 
 * @param reg_addr  Address in the processor's memory map of the register to
 *                  write.
 * @param value     Value to be written into the peripheral register.
 */
void
HW_set_32bit_reg
(
	addr_t reg_addr,
	uint32_t value
);

/***************************************************************************//**
 * HW_get_32bit_reg is used to read the content of a 32 bits wide peripheral
 * register.
 * 
 * @param reg_addr  Address in the processor's memory map of the register to
 *                  read.
 * @return          32 bits value read from the peripheral register.
 */
uint32_t
HW_get_32bit_reg
(
	addr_t reg_addr
);

/***************************************************************************//**
 * HW_set_32bit_reg_field is used to set the content of a field in a 32 bits 
 * wide peripheral register.
 * 
 * @param reg_addr  Address in the processor's memory map of the register to
 *                  be written.
 * @param shift     Bit offset of the register field to be read within the 
 *                  register.
 * @param mask      Bit mask to be applied to the raw register value to filter
 *                  out the other register fields values.
 * @param value     Value to be written in the specified field.
 */
void
HW_set_32bit_reg_field
(
    addr_t reg_addr,
    int_fast8_t shift,
    uint32_t mask,
    uint32_t value
);

/***************************************************************************//**
 * HW_get_32bit_reg_field is used to read the content of a field out of a 
 * 32 bits wide peripheral register.
 * 
 * @param reg_addr  Address in the processor's memory map of the register to
 *                  read.
 * @param shift     Bit offset of the register field to be written within the 
 *                  register.
 * @param mask      Bit mask to be applied to the raw register value to filter
 *                  out the other register fields values.
 *
 * @return          32 bits value containing the register field value specified
 *                  as parameter.
 */
uint32_t 
HW_get_32bit_reg_field
(
    addr_t reg_addr,
    int_fast8_t shift,
    uint32_t mask
);

/***************************************************************************//**
 * HW_set_16bit_reg is used to write the content of a 16 bits wide peripheral
 * register.
 * 
 * @param reg_addr  Address in the processor's memory map of the register to
 *                  write.
 * @param value     Value to be written into the peripheral register.
 */
void
HW_set_16bit_reg
(
	addr_t reg_addr,
	uint_fast16_t value
);

/***************************************************************************//**
 * HW_get_16bit_reg is used to read the content of a 16 bits wide peripheral
 * register.
 * 
 * @param reg_addr  Address in the processor's memory map of the register to
 *                  read.
 * @return          16 bits value read from the peripheral register.
 */
uint16_t
HW_get_16bit_reg
(
	addr_t reg_addr
);

/***************************************************************************//**
 * HW_set_16bit_reg_field is used to set the content of a field in a 16 bits 
 * wide peripheral register.
 * 
 * @param reg_addr  Address in the processor's memory map of the register to
 *                  be written.
 * @param shift     Bit offset of the register field to be read within the 
 *                  register.
 * @param mask      Bit mask to be applied to the raw register value to filter
 *                  out the other register fields values.
 * @param value     Value to be written in the specified field.
 */
void HW_set_16bit_reg_field
(
    addr_t reg_addr,
    int_fast8_t shift,
    uint_fast16_t mask,
    uint_fast16_t value
);

/***************************************************************************//**
 * HW_get_16bit_reg_field is used to read the content of a field from a 
 * 16 bits wide peripheral register.
 * 
 * @param reg_addr  Address in the processor's memory map of the register to
 *                  read.
 * @param shift     Bit offset of the register field to be written within the 
 *                  register.
 * @param mask      Bit mask to be applied to the raw register value to filter
 *                  out the other register fields values.
 *
 * @return          16 bits value containing the register field value specified
 *                  as parameter.
 */
uint16_t HW_get_16bit_reg_field
(
    addr_t reg_addr,
    int_fast8_t shift,
    uint_fast16_t mask
);

/***************************************************************************//**
 * HW_set_8bit_reg is used to write the content of a 8 bits wide peripheral
 * register.
 * 
 * @param reg_addr  Address in the processor's memory map of the register to
 *                  write.
 * @param value     Value to be written into the peripheral register.
 */
void
HW_set_8bit_reg
(
	addr_t reg_addr,
	uint_fast8_t value
);

/***************************************************************************//**
 * HW_get_8bit_reg is used to read the content of a 8 bits wide peripheral
 * register.
 * 
 * @param reg_addr  Address in the processor's memory map of the register to
 *                  read.
 * @return          8 bits value read from the peripheral register.
 */
uint8_t
HW_get_8bit_reg
(
    addr_t reg_addr
);

/***************************************************************************//**
 * HW_set_8bit_reg_field is used to set the content of a field in a 8 bits 
 * wide peripheral register.
 * 
 * @param reg_addr  Address in the processor's memory map of the register to
 *                  be written.
 * @param shift     Bit offset of the register field to be read within the 
 *                  register.
 * @param mask      Bit mask to be applied to the raw register value to filter
 *                  out the other register fields values.
 * @param value     Value to be written in the specified field.
 */
void HW_set_8bit_reg_field
(
    addr_t reg_addr,
    int_fast8_t shift,
    uint_fast8_t mask,
    uint_fast8_t value
);

/***************************************************************************//**
 * HW_get_8bit_reg_field is used to read the content of a field from a 
 * 8 bits wide peripheral register.
 * 
 * @param reg_addr  Address in the processor's memory map of the register to
 *                  read.
 * @param shift     Bit offset of the register field to be written within the 
 *                  register.
 * @param mask      Bit mask to be applied to the raw register value to filter
 *                  out the other register fields values.
 *
 * @return          16 bits value containing the register field value specified
 *                  as parameter.
 */
uint8_t HW_get_8bit_reg_field
(
    addr_t reg_addr,
    int_fast8_t shift,
    uint_fast8_t mask
);

#endif /* HW_REG_ACCESS */
