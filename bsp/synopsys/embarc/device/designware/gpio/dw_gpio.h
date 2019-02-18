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
 * \file
 * \brief	designware gpio driver
 * \ingroup	DEVICE_DW_GPIO
 * \brief	Designware GPIO driver header file
 */

#ifndef _DW_GPIO_H_
#define _DW_GPIO_H_

#include "device/device_hal/inc/dev_gpio.h"

#include "inc/arc/arc_exception.h"

#define DW_GPIO_PORT_A	(0x00)
#define DW_GPIO_PORT_B	(0x01)
#define DW_GPIO_PORT_C	(0x02)
#define DW_GPIO_PORT_D	(0x03)

#define DW_GPIO_INT_ACT_LOW			GPIO_INT_ACTIVE_LOW
#define DW_GPIO_INT_ACT_HIGH			GPIO_INT_ACTIVE_HIGH

#define DW_GPIO_INT_LEVEL_TRIG			GPIO_INT_LEVEL_TRIG
#define DW_GPIO_INT_EDGE_TRIG			GPIO_INT_EDGE_TRIG

#define DW_GPIO_INT_NO_DEBOUNCE			GPIO_INT_NO_DEBOUNCE
#define DW_GPIO_INT_DEBOUNCE			GPIO_INT_DEBOUNCE

#define DW_GPIO_ALL_ZERO			(0x0)
#define DW_GPIO_ALL_ONE				(0xffffffff)
#define DW_GPIO_MASK_ALL			(0xffffffff)
#define DW_GPIO_INPUT_ALL			(0x0)
#define DW_GPIO_OUTPUT_ALL			(0xffffffff)

/**
 * \name	DesignWare GPIO Register Structure
 * \brief	contains definitions of DesignWare GPIO register structure.
 * @{
 */
typedef struct port_ctrl {
	uint32_t DR;
	uint32_t DDR;
	uint32_t CTRL;
} PORT_CTRL;

/* DW GPIO PORTS Registers */
typedef volatile struct dw_gpio_reg {
	PORT_CTRL SWPORTS[4];
	uint32_t INTEN;		/*!< (0x30) */
	uint32_t INTMASK;	/*!< (0x34) */
	uint32_t INTTYPE_LEVEL;	/*!< (0x38) */
	uint32_t INT_POLARITY;	/*!< (0x3c) */
	uint32_t INTSTATUS;	/*!< (0x40) */
	uint32_t RAW_INTSTATUS;	/*!< (0x44) */
	uint32_t DEBOUNCE;	/*!< (0x48) */
	uint32_t PORTA_EOI;	/*!< (0x4c) */
	uint32_t EXT_PORTS[4];	/*!< (0x50) -A
				     (0x54) -B
				     (0x58) -C
				     (0x5c) -D */
	uint32_t LS_SYNC;	/*!< (0x60) */
	uint32_t ID_CODE;	/*!< (0x64) */
	uint32_t RESERVED_3;	/*!< (0x68) */
	uint32_t VER_ID_CODE;	/*!< (0x6c) */
	uint32_t CONFIG_REG2;	/*!< (0x70) */
	uint32_t CONFIG_REG1;	/*!< (0x74) */
} DW_GPIO_REG, *DW_GPIO_REG_PTR;
/** @} */

/** interrupt handler for each port bit */
typedef struct dw_gpio_bit_isr {
	uint32_t int_bit_max_cnt;		/*!< max bit count for each port */
	DEV_GPIO_HANDLER *int_bit_handler_ptr;	/*!< interrupt handler pointer */
} DW_GPIO_BIT_ISR, * DW_GPIO_BIT_ISR_PTR;

/**
 * \brief	DesignWare GPIO control structure definition
 * \details	implement of dev_gpio_info::gpio_ctrl
 */
typedef struct dw_gpio_port {
	uint32_t no;				/*!< gpio port number */
	DW_GPIO_REG_PTR	regs;			/*!< gpio port register */
	uint32_t intno;				/*!< gpio interrupt vector number */
	uint32_t valid_bit_mask;		/*!< valid bit mask of gpio port */
	INT_HANDLER int_handler;		/*!< gpio interrupt handler */
	DW_GPIO_BIT_ISR_PTR gpio_bit_isr;	/*!< gpio bit handler struct */
} DW_GPIO_PORT, *DW_GPIO_PORT_PTR;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name	DesignWare GPIO Function Declaration
 * \brief	contains declarations of designware gpio functions.
 * \details	This are only used in gpio object implementation source file
 * @{
 */
extern int32_t dw_gpio_open(DEV_GPIO *gpio_obj, uint32_t dir);
extern int32_t dw_gpio_close(DEV_GPIO *gpio_obj);
extern int32_t dw_gpio_read(DEV_GPIO *gpio_obj, uint32_t *val, uint32_t mask);
extern int32_t dw_gpio_write(DEV_GPIO *gpio_obj, uint32_t val, uint32_t mask);
extern int32_t dw_gpio_control(DEV_GPIO *gpio_obj, uint32_t ctrl_cmd, void *param);
extern int32_t dw_gpio_isr_handler(DEV_GPIO *gpio_obj, void *ptr);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* _DW_GPIO_H_ */
