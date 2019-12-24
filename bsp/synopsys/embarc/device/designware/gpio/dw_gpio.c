/* ------------------------------------------
 * Copyright (c) 2016, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * \version 2016.05
 * \date 2014-07-22
 * \author Wayne Ren(Wei.Ren@synopsys.com)
--------------------------------------------- */

/**
 * \defgroup	DEVICE_DW_GPIO	Designware GPIO Driver
 * \ingroup	DEVICE_DW
 * \brief	Designware GPIO Driver Implementation
 */

/**
 * \file
 * \brief	designware gpio driver
 * \ingroup	DEVICE_DW_GPIO
 * \brief	Designware GPIO driver
 */
#include "inc/embARC_toolchain.h"
#include "inc/embARC_error.h"
#include "inc/arc/arc_exception.h"

#include "device/designware/gpio/dw_gpio.h"

/** check expressions used in DesignWare GPIO driver implementation */
#define DW_GPIO_CHECK_EXP(EXPR, ERROR_CODE)		CHECK_EXP(EXPR, ercd, ERROR_CODE, error_exit)

#ifndef DISABLE_DEVICE_OBJECT_VALID_CHECK
/** valid check of uart info object */
#define VALID_CHK_GPIO_INFO_OBJECT(gpioinfo_obj_ptr)		{				\
			DW_GPIO_CHECK_EXP((gpioinfo_obj_ptr)!=NULL, E_OBJ);			\
			DW_GPIO_CHECK_EXP(((gpioinfo_obj_ptr)->gpio_ctrl)!=NULL, E_OBJ);	\
 		}
#endif

/**
 * \defgroup	DEVICE_DW_GPIO_STATIC	DesignWare GPIO Driver Static Functions
 * \ingroup	DEVICE_DW_GPIO
 * \brief	Static or inline functions, variables for DesignWare GPIO handle gpio operations,
 * 	only used in this file
 * @{
 */
Inline uint32_t dw_gpio_read_ext(DW_GPIO_PORT_PTR port)
{
	return  port->regs->EXT_PORTS[port->no];
}

Inline uint32_t dw_gpio_read_dir(DW_GPIO_PORT_PTR port)
{
	return port->regs->SWPORTS[port->no].DDR;
}

Inline uint32_t dw_gpio_read_dr(DW_GPIO_PORT_PTR port)
{
	return port->regs->SWPORTS[port->no].DR;
}

Inline uint32_t dw_gpio_read_mthd(DW_GPIO_PORT_PTR port)
{
	return port->regs->INTEN;
}

Inline void dw_gpio_int_enable(DW_GPIO_PORT_PTR port, uint32_t bit_mask)
{
	port->regs->INTEN |= bit_mask;
}

Inline void dw_gpio_int_disable(DW_GPIO_PORT_PTR port, uint32_t bit_mask)
{
	port->regs->INTEN &= (~bit_mask);
}

Inline void dw_gpio_int_mask(DW_GPIO_PORT_PTR port, uint32_t bit_mask)
{
	port->regs->INTMASK |= bit_mask;
}

Inline void dw_gpio_int_unmask(DW_GPIO_PORT_PTR port, uint32_t bit_mask)
{
	port->regs->INTMASK &= (~bit_mask);
}

Inline uint32_t dw_gpio_int_read_level(DW_GPIO_PORT_PTR port)
{
	return port->regs->INTTYPE_LEVEL;
}

Inline uint32_t dw_gpio_int_read_polarity(DW_GPIO_PORT_PTR port)
{
	return port->regs->INT_POLARITY;
}

Inline uint32_t dw_gpio_int_read_debounce(DW_GPIO_PORT_PTR port)
{
	return port->regs->DEBOUNCE;
}

Inline uint32_t dw_gpio_int_read_status(DW_GPIO_PORT_PTR port)
{
	return port->regs->INTSTATUS;
}

Inline void dw_gpio_int_clear(DW_GPIO_PORT_PTR port, uint32_t bit_mask)
{
	port->regs->PORTA_EOI = bit_mask;
}

static void dw_gpio_int_write_level(DW_GPIO_PORT_PTR port, uint32_t bit_mask, uint32_t bit_level)
{
	uint32_t reg_val;

	reg_val = port->regs->INTTYPE_LEVEL;
	reg_val &= (~bit_mask);
	bit_level &= bit_mask;
	reg_val |= bit_level;

	port->regs->INTTYPE_LEVEL = reg_val;
}

static void dw_gpio_int_write_polarity(DW_GPIO_PORT_PTR port, uint32_t bit_mask, uint32_t bit_polarity)
{
	uint32_t reg_val;

	reg_val = port->regs->INT_POLARITY;

	reg_val &= (~bit_mask);
	bit_polarity &= bit_mask;
	reg_val |= bit_polarity;

	port->regs->INT_POLARITY = reg_val;
}

static void dw_gpio_int_write_debounce(DW_GPIO_PORT_PTR port, uint32_t bit_mask, uint32_t bit_debounce)
{
	uint32_t reg_val;

	reg_val = port->regs->DEBOUNCE;

	reg_val &= (~bit_mask);
	bit_debounce &= bit_mask;
	reg_val |= bit_debounce;

	port->regs->DEBOUNCE = reg_val;
}

static void dw_gpio_set_int_cfg(DW_GPIO_PORT_PTR port, DEV_GPIO_INT_CFG *int_cfg)
{
	dw_gpio_int_write_level(port, int_cfg->int_bit_mask, int_cfg->int_bit_type);
	dw_gpio_int_write_polarity(port, int_cfg->int_bit_mask, int_cfg->int_bit_polarity);
	dw_gpio_int_write_debounce(port, int_cfg->int_bit_mask, int_cfg->int_bit_debounce);
}

static void dw_gpio_get_int_cfg(DW_GPIO_PORT_PTR port, DEV_GPIO_INT_CFG *int_cfg)
{
	int_cfg->int_bit_type = dw_gpio_int_read_level(port) & int_cfg->int_bit_mask;
	int_cfg->int_bit_polarity = dw_gpio_int_read_polarity(port) & int_cfg->int_bit_mask;
	int_cfg->int_bit_debounce = dw_gpio_int_read_debounce(port) & int_cfg->int_bit_mask;
}

static void dw_gpio_write_dr(DW_GPIO_PORT_PTR port, uint32_t bit_mask, uint32_t val)
{
	uint32_t temp_reg;

	temp_reg = port->regs->SWPORTS[port->no].DR;
	temp_reg &= ~bit_mask;
	val &= bit_mask;
	temp_reg |= val;

	port->regs->SWPORTS[port->no].DR = temp_reg;
}

static void dw_gpio_write_dir(DW_GPIO_PORT_PTR port, uint32_t bit_mask, uint32_t val)
{
	uint32_t temp_reg;

	temp_reg = port->regs->SWPORTS[port->no].DDR;
	temp_reg &= ~bit_mask;
	val &= bit_mask;
	temp_reg |= val;

	port->regs->SWPORTS[port->no].DDR = temp_reg;
}

static uint32_t dw_gpio_read_val(DW_GPIO_PORT_PTR port)
{
	uint32_t val;

	val = dw_gpio_read_ext(port) & (~dw_gpio_read_dir(port));
	val |= dw_gpio_read_dr(port) & dw_gpio_read_dir(port);

	return val;
}

/** @} end of group DEVICE_DW_GPIO_STATIC */

/* interface for DEV_GPIO */
/** Open designware gpio device with specified io direction configuration */
int32_t dw_gpio_open(DEV_GPIO *gpio_obj, uint32_t dir)
{
	int32_t ercd = E_OK;
	DEV_GPIO_INFO_PTR port_info_ptr = &(gpio_obj->gpio_info);

	/* START ERROR CHECK */
	VALID_CHK_GPIO_INFO_OBJECT(port_info_ptr);
	/* END OF ERROR CHECK */

	DW_GPIO_PORT_PTR port = (DW_GPIO_PORT_PTR)(port_info_ptr->gpio_ctrl);
	DW_GPIO_CHECK_EXP(port->no <= DW_GPIO_PORT_D, E_OBJ);

	port_info_ptr->opn_cnt ++;
	if (port_info_ptr->opn_cnt > 1) { /* opened before */
		if (dir == port_info_ptr->direction) { /* direction is the same */
			return E_OK;
		} else { /* open with different direction */
			return E_OPNED;
		}
	}

	dw_gpio_write_dir(port, port->valid_bit_mask, dir);

	if (port->no == DW_GPIO_PORT_A) {
		dw_gpio_int_clear(port, DW_GPIO_MASK_ALL);
		dw_gpio_int_disable(port, DW_GPIO_MASK_ALL);
		dw_gpio_int_unmask(port, DW_GPIO_MASK_ALL);
		/* install gpio interrupt handler */
		int_handler_install(port->intno, port->int_handler);
		int_disable(port->intno);
		/** Set int type, int polarity and debounce configuration to default settings of device gpio */
		dw_gpio_set_int_cfg(port, (DEV_GPIO_INT_CFG *)(&gpio_int_cfg_default));
		port_info_ptr->method = dw_gpio_read_mthd(port);
	} else {
		port_info_ptr->method = DEV_GPIO_BITS_MTHD_DEFAULT;
	}

	dw_gpio_write_dr(port, port->valid_bit_mask, 0);

	port_info_ptr->direction = dir;
	port_info_ptr->extra = NULL;

error_exit:
	return ercd;
}

/** Close designware gpio device */
int32_t dw_gpio_close(DEV_GPIO *gpio_obj)
{
	int32_t ercd = E_OK;
	DEV_GPIO_INFO_PTR port_info_ptr = &(gpio_obj->gpio_info);

	/* START ERROR CHECK */
	VALID_CHK_GPIO_INFO_OBJECT(port_info_ptr);
	/* END OF ERROR CHECK */

	DW_GPIO_PORT_PTR port = (DW_GPIO_PORT_PTR)(port_info_ptr->gpio_ctrl);
	DW_GPIO_CHECK_EXP(port->no <= DW_GPIO_PORT_D, E_OBJ);

	DW_GPIO_CHECK_EXP(port_info_ptr->opn_cnt > 0, E_OK);

	port_info_ptr->opn_cnt --;
	if (port_info_ptr->opn_cnt == 0) {
		dw_gpio_write_dr(port, port->valid_bit_mask, 0);
		dw_gpio_write_dir(port, port->valid_bit_mask, 0);
		if (port->no == DW_GPIO_PORT_A) {
			dw_gpio_int_clear(port, DW_GPIO_MASK_ALL);
			dw_gpio_int_disable(port, DW_GPIO_MASK_ALL);
			int_disable(port->intno);
		}

		port_info_ptr->direction = 0;
		port_info_ptr->method = 0;
		port_info_ptr->extra = NULL;
	} else {
		ercd = E_OPNED;
	}

error_exit:
	return ercd;
}

/** Read designware gpio device value */
int32_t dw_gpio_read(DEV_GPIO *gpio_obj, uint32_t *val, uint32_t mask)
{
	int32_t ercd = E_OK;
	DEV_GPIO_INFO_PTR port_info_ptr = &(gpio_obj->gpio_info);

	/* START ERROR CHECK */
	VALID_CHK_GPIO_INFO_OBJECT(port_info_ptr);
	/* END OF ERROR CHECK */

	DW_GPIO_PORT_PTR port = (DW_GPIO_PORT_PTR)(port_info_ptr->gpio_ctrl);
	DW_GPIO_CHECK_EXP(port->no <= DW_GPIO_PORT_D, E_OBJ);
	DW_GPIO_CHECK_EXP(port_info_ptr->opn_cnt > 0, E_CLSED);

	DW_GPIO_CHECK_EXP(val!=NULL, E_PAR);

	//*val = dw_gpio_read_ext(port) & mask;
	*val = dw_gpio_read_val(port) & mask;

error_exit:
	return ercd;
}

/** Write designware gpio device value */
int32_t dw_gpio_write(DEV_GPIO *gpio_obj, uint32_t val, uint32_t mask)
{
	int32_t ercd = E_OK;
	DEV_GPIO_INFO_PTR port_info_ptr = &(gpio_obj->gpio_info);

	/* START ERROR CHECK */
	VALID_CHK_GPIO_INFO_OBJECT(port_info_ptr);
	/* END OF ERROR CHECK */

	DW_GPIO_PORT_PTR port = (DW_GPIO_PORT_PTR)(port_info_ptr->gpio_ctrl);
	DW_GPIO_CHECK_EXP(port->no <= DW_GPIO_PORT_D, E_OBJ);
	DW_GPIO_CHECK_EXP(port_info_ptr->opn_cnt > 0, E_CLSED);

	dw_gpio_write_dr(port, mask, val);

error_exit:
	return ercd;
}

/** Control designware gpio device */
int32_t dw_gpio_control(DEV_GPIO *gpio_obj, uint32_t ctrl_cmd, void *param)
{
	int32_t ercd = E_OK;
	DEV_GPIO_INFO_PTR port_info_ptr = &(gpio_obj->gpio_info);

	/* START ERROR CHECK */
	VALID_CHK_GPIO_INFO_OBJECT(port_info_ptr);
	/* END OF ERROR CHECK */

	DW_GPIO_PORT_PTR port = (DW_GPIO_PORT_PTR)(port_info_ptr->gpio_ctrl);
	DW_GPIO_CHECK_EXP(port->no <= DW_GPIO_PORT_D, E_OBJ);
	DW_GPIO_CHECK_EXP(port_info_ptr->opn_cnt > 0, E_CLSED);

	uint32_t val32;	/** to receive unsigned int value */

	if (ctrl_cmd == GPIO_CMD_SET_BIT_DIR_INPUT) {
		val32 = (uint32_t)param;
		dw_gpio_write_dir(port, val32, DW_GPIO_INPUT_ALL);
		port_info_ptr->direction = dw_gpio_read_dir(port);
	} else if (ctrl_cmd == GPIO_CMD_SET_BIT_DIR_OUTPUT) {
		val32 = (uint32_t)param;
		dw_gpio_write_dir(port, val32, DW_GPIO_OUTPUT_ALL);
		port_info_ptr->direction = dw_gpio_read_dir(port);
	} else if (ctrl_cmd == GPIO_CMD_GET_BIT_DIR) {
		DW_GPIO_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
		port_info_ptr->direction = dw_gpio_read_dir(port);
		*((int32_t *)param) = port_info_ptr->direction;
	} else {
		DW_GPIO_CHECK_EXP(port->no == DW_GPIO_PORT_A, E_NOSPT);
		/* output pin cannot be used as interrupt */
		DEV_GPIO_INT_CFG *gpio_int_cfg;
		DEV_GPIO_BIT_ISR *port_bit_isr;

		switch (ctrl_cmd) {
			case GPIO_CMD_SET_BIT_INT_CFG:
				DW_GPIO_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
				gpio_int_cfg = (DEV_GPIO_INT_CFG *)param;
				dw_gpio_set_int_cfg(port, gpio_int_cfg);
				break;
			case GPIO_CMD_GET_BIT_INT_CFG:
				DW_GPIO_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
				gpio_int_cfg = (DEV_GPIO_INT_CFG *)param;
				/** read configuration, each bit stands for different configuration */
				dw_gpio_get_int_cfg(port, gpio_int_cfg);
				break;
			case GPIO_CMD_SET_BIT_ISR:
				DW_GPIO_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
				port_bit_isr = (DEV_GPIO_BIT_ISR *)param;
				if (port_bit_isr->int_bit_ofs < port->gpio_bit_isr->int_bit_max_cnt) {
					port->gpio_bit_isr->int_bit_handler_ptr[port_bit_isr->int_bit_ofs] = port_bit_isr->int_bit_handler;
				} else {
					ercd = E_PAR;
				}
				break;
			case GPIO_CMD_GET_BIT_ISR:
				DW_GPIO_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
				port_bit_isr = (DEV_GPIO_BIT_ISR *)param;
				if (port_bit_isr->int_bit_ofs < port->gpio_bit_isr->int_bit_max_cnt) {
					port_bit_isr->int_bit_handler = port->gpio_bit_isr->int_bit_handler_ptr[port_bit_isr->int_bit_ofs];
				} else {
					ercd = E_PAR;
				}
				break;
			case GPIO_CMD_ENA_BIT_INT:
				val32 = (uint32_t)param;
				dw_gpio_int_enable(port, val32);
				port_info_ptr->method = dw_gpio_read_mthd(port);
				if (port_info_ptr->method) {
					int_enable(port->intno);
				}
				break;
			case GPIO_CMD_DIS_BIT_INT:
				val32 = (uint32_t)param;
				dw_gpio_int_disable(port, val32);
				port_info_ptr->method = dw_gpio_read_mthd(port);
				if (port_info_ptr->method == 0) {
					int_disable(port->intno);
				}
				break;
			case GPIO_CMD_GET_BIT_MTHD:
				DW_GPIO_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
				port_info_ptr->method = dw_gpio_read_mthd(port);
				*((int32_t *)param) = port_info_ptr->method;
				break;
			default:
				ercd = E_NOSPT;
				break;
		}
	}
error_exit:
	return ercd;
}

/** designware gpio interrupt process */
int32_t dw_gpio_isr_handler(DEV_GPIO *gpio_obj, void *ptr)
{
	int32_t ercd = E_OK;
	DEV_GPIO_INFO_PTR port_info_ptr = &(gpio_obj->gpio_info);

	/* START ERROR CHECK */
	VALID_CHK_GPIO_INFO_OBJECT(port_info_ptr);
	/* END OF ERROR CHECK */

	DW_GPIO_PORT_PTR port = (DW_GPIO_PORT_PTR)(port_info_ptr->gpio_ctrl);
	DW_GPIO_CHECK_EXP(port->no == DW_GPIO_PORT_A, E_NOSPT);

	uint32_t i, gpio_bit_isr_state;
	uint32_t max_int_bit_count = 0;

	/** read interrupt status */
	gpio_bit_isr_state = dw_gpio_int_read_status(port);

	if (port->gpio_bit_isr) {
		max_int_bit_count = (port->gpio_bit_isr->int_bit_max_cnt);
	} else {
		dw_gpio_int_clear(port, gpio_bit_isr_state);
	}

	for (i=0; i<max_int_bit_count; i++) {
		if (gpio_bit_isr_state & (1<<i)) {
			/* this bit interrupt enabled */
			if (port->gpio_bit_isr->int_bit_handler_ptr[i]) {
				port->gpio_bit_isr->int_bit_handler_ptr[i](gpio_obj);
			}
			dw_gpio_int_clear(port, (1<<i)); /** clear this bit interrupt */
		}
	}

error_exit:
	return ercd;
}
