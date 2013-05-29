/** @file sys_vim.h
*   @brief Vectored Interrupt Module Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - VIM Type Definitions
*   - VIM General Definitions
*   .
*   which are relevant for Vectored Interrupt Controller.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __SYS_VIM_H__
#define __SYS_VIM_H__

#include "reg_vim.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */


/* VIM Type Definitions */

/** @typedef t_isrFuncPTR
*   @brief ISR Function Pointer Type Definition
*
*   This type is used to access the ISR handler.
*/
typedef void (*t_isrFuncPTR)(void);

/* USER CODE BEGIN (1) */
/* USER CODE END */


/* VIM General Configuration */

#define VIM_CHANNELS 96U

/* USER CODE BEGIN (2) */
/* USER CODE END */

/* Interrupt Handlers */

extern void esmHighInterrupt(void);
extern void phantomInterrupt(void);
extern void rtiCompare3Interrupt(void);
extern void linHighLevelInterrupt(void);

/* USER CODE BEGIN (3) */
/* USER CODE END */

#define VIM_PARFLG		(*(volatile uint32 *)0xFFFFFDECU)
#define VIM_PARCTL		(*(volatile uint32 *)0xFFFFFDF0U)
#define VIM_ADDERR		(*(volatile uint32 *)0xFFFFFDF4U)
#define VIM_FBPARERR	(*(volatile uint32 *)0xFFFFFDF8U)

#define VIMRAMPARLOC	(*(volatile uint32 *)0xFFF82400U)
#define VIMRAMLOC		(*(volatile uint32 *)0xFFF82000U)

/* Configuration registers */
typedef struct vim_config_reg
{
    uint32 CONFIG_FIRQPR0;
    uint32 CONFIG_FIRQPR1;
    uint32 CONFIG_FIRQPR2;
    uint32 CONFIG_FIRQPR3;
    uint32 CONFIG_REQMASKSET0;
    uint32 CONFIG_REQMASKSET1;
    uint32 CONFIG_REQMASKSET2;
    uint32 CONFIG_REQMASKSET3;
    uint32 CONFIG_WAKEMASKSET0;
    uint32 CONFIG_WAKEMASKSET1;
    uint32 CONFIG_WAKEMASKSET2;
    uint32 CONFIG_WAKEMASKSET3;
    uint32 CONFIG_CAPEVT;
    uint32 CONFIG_CHANCTRL[24U];
} vim_config_reg_t;

/* Configuration registers initial value */
#define VIM_FIRQPR0_CONFIGVALUE	SYS_FIQ\
                    | (SYS_FIQ <<  1U)\
                    | (SYS_IRQ <<  2U)\
                    | (SYS_IRQ <<  3U)\
                    | (SYS_IRQ <<  4U)\
                    | (SYS_IRQ <<  5U)\
                    | (SYS_IRQ <<  6U)\
                    | (SYS_IRQ <<  7U)\
                    | (SYS_IRQ <<  8U)\
                    | (SYS_IRQ <<  9U)\
                    | (SYS_IRQ << 10U)\
                    | (SYS_IRQ << 11U)\
                    | (SYS_IRQ << 12U)\
                    | (SYS_IRQ << 13U)\
                    | (SYS_IRQ << 14U)\
                    | (SYS_IRQ << 15U)\
                    | (SYS_IRQ << 16U)\
                    | (SYS_IRQ << 17U)\
                    | (SYS_IRQ << 18U)\
                    | (SYS_IRQ << 19U)\
                    | (SYS_IRQ << 20U)\
                    | (SYS_IRQ << 21U)\
                    | (SYS_IRQ << 22U)\
                    | (SYS_IRQ << 23U)\
                    | (SYS_IRQ << 24U)\
                    | (SYS_IRQ << 25U)\
                    | (SYS_IRQ << 26U)\
                    | (SYS_IRQ << 27U)\
                    | (SYS_IRQ << 28U)\
                    | (SYS_IRQ << 29U)\
                    | (SYS_IRQ << 30U)\
                    | (SYS_IRQ << 31U)
					
#define VIM_FIRQPR1_CONFIGVALUE	SYS_IRQ\
                    | (SYS_IRQ <<  1U)\
                    | (SYS_IRQ <<  2U)\
                    | (SYS_IRQ <<  3U)\
                    | (SYS_IRQ <<  4U)\
                    | (SYS_IRQ <<  5U)\
                    | (SYS_IRQ <<  6U)\
                    | (SYS_IRQ <<  7U)\
                    | (SYS_IRQ <<  8U)\
                    | (SYS_IRQ <<  9U)\
                    | (SYS_IRQ << 10U)\
                    | (SYS_IRQ << 11U)\
                    | (SYS_IRQ << 12U)\
                    | (SYS_IRQ << 13U)\
                    | (SYS_IRQ << 14U)\
                    | (SYS_IRQ << 15U)\
                    | (SYS_IRQ << 16U)\
                    | (SYS_IRQ << 17U)\
                    | (SYS_IRQ << 18U)\
                    | (SYS_IRQ << 19U)\
                    | (SYS_IRQ << 20U)\
                    | (SYS_IRQ << 21U)\
                    | (SYS_IRQ << 22U)\
                    | (SYS_IRQ << 23U)\
                    | (SYS_IRQ << 24U)\
                    | (SYS_IRQ << 25U)\
                    | (SYS_IRQ << 26U)\
                    | (SYS_IRQ << 27U)\
                    | (SYS_IRQ << 28U)\
                    | (SYS_IRQ << 29U)\
                    | (SYS_IRQ << 30U)\
                    | (SYS_IRQ << 31U)
					
#define VIM_FIRQPR2_CONFIGVALUE	SYS_IRQ\
                    | (SYS_IRQ << 1U)\
                    | (SYS_IRQ << 2U)\
                    | (SYS_IRQ << 3U)\
                    | (SYS_IRQ << 4U)\
                    | (SYS_IRQ << 5U)\
                    | (SYS_IRQ << 6U)\
                    | (SYS_IRQ << 7U)\
                    | (SYS_IRQ << 8U)\
                    | (SYS_IRQ << 9U)\
                    | (SYS_IRQ << 10U)\
                    | (SYS_IRQ << 11U)\
                    | (SYS_IRQ << 12U)\
                    | (SYS_IRQ << 13U)\
                    | (SYS_IRQ << 14U)\
                    | (SYS_IRQ << 15U)\
                    | (SYS_IRQ << 16U)\
                    | (SYS_IRQ << 17U)\
                    | (SYS_IRQ << 18U)\
                    | (SYS_IRQ << 19U)\
                    | (SYS_IRQ << 20U)\
                    | (SYS_IRQ << 21U)\
                    | (SYS_IRQ << 22U)\
                    | (SYS_IRQ << 23U)\
                    | (SYS_IRQ << 24U)\
                    | (SYS_IRQ << 25U)\
					| (SYS_IRQ << 26U)\
                    | (SYS_IRQ << 27U)\
                    | (SYS_IRQ << 28U)\
                    | (SYS_IRQ << 29U)\
                    | (SYS_IRQ << 30U)\
                    | (SYS_IRQ << 31U)
					
#define VIM_FIRQPR3_CONFIGVALUE	SYS_IRQ\
                    | (SYS_IRQ << 1U)\
                    | (SYS_IRQ << 2U)\
                    | (SYS_IRQ << 3U)\
                    | (SYS_IRQ << 4U)\
                    | (SYS_IRQ << 5U)\
                    | (SYS_IRQ << 6U)\
                    | (SYS_IRQ << 7U)\
                    | (SYS_IRQ << 8U)\
                    | (SYS_IRQ << 9U)\
                    | (SYS_IRQ << 10U)\
                    | (SYS_IRQ << 11U)\
                    | (SYS_IRQ << 12U)\
                    | (SYS_IRQ << 13U)\
                    | (SYS_IRQ << 14U)\
                    | (SYS_IRQ << 15U)\
                    | (SYS_IRQ << 16U)\
                    | (SYS_IRQ << 17U)\
                    | (SYS_IRQ << 18U)\
                    | (SYS_IRQ << 19U)\
                    | (SYS_IRQ << 20U)\
                    | (SYS_IRQ << 21U)\
                    | (SYS_IRQ << 22U)\
                    | (SYS_IRQ << 23U)\
                    | (SYS_IRQ << 24U)\
                    | (SYS_IRQ << 25U)\
					| (SYS_IRQ << 26U)\
                    | (SYS_IRQ << 27U)\
                    | (SYS_IRQ << 28U)\
                    | (SYS_IRQ << 29U)\
                    | (SYS_IRQ << 30U)\
                    | (SYS_IRQ << 31U)
					
#define VIM_REQMASKSET0_CONFIGVALUE	1U\
                        | (1U << 1U)\
                        | (0U << 2U)\
                        | (0U << 3U)\
                        | (0U << 4U)\
                        | (1U << 5U)\
                        | (0U << 6U)\
                        | (0U << 7U)\
                        | (0U << 8U)\
                        | (0U << 9U)\
                        | (0U << 10U)\
                        | (0U << 11U)\
                        | (0U << 12U)\
                        | (1U << 13U)\
                        | (0U << 14U)\
                        | (0U << 15U)\
                        | (0U << 16U)\
                        | (0U << 17U)\
                        | (0U << 18U)\
                        | (0U << 19U)\
                        | (0U << 20U)\
                        | (0U << 21U)\
                        | (0U << 22U)\
                        | (0U << 23U)\
                        | (0U << 24U)\
                        | (0U << 25U)\
                        | (0U << 26U)\
                        | (0U << 27U)\
                        | (0U << 28U)\
                        | (0U << 29U)\
                        | (0U << 30U)\
                        | (0U << 31U)
						
#define VIM_REQMASKSET1_CONFIGVALUE	0U\
                        | (0U << 1U)\
                        | (0U << 2U)\
                        | (0U << 3U)\
                        | (0U << 4U)\
                        | (0U << 5U)\
                        | (0U << 6U)\
                        | (0U << 7U)\
                        | (0U << 8U)\
                        | (0U << 9U)\
                        | (0U << 10U)\
                        | (0U << 11U)\
                        | (0U << 12U)\
                        | (0U << 13U)\
                        | (0U << 14U)\
                        | (0U << 15U)\
                        | (0U << 16U)\
                        | (0U << 17U)\
                        | (0U << 18U)\
                        | (0U << 19U)\
                        | (0U << 20U)\
                        | (0U << 21U)\
                        | (0U << 22U)\
                        | (0U << 23U)\
                        | (0U << 24U)\
                        | (0U << 25U)\
                        | (0U << 26U)\
                        | (0U << 27U)\
                        | (0U << 28U)\
                        | (0U << 29U)\
                        | (0U << 30U)\
                        | (0U << 31U)
						
#define VIM_REQMASKSET2_CONFIGVALUE	0U\
                        | (0U << 1U)\
                        | (0U << 2U)\
                        | (0U << 3U)\
                        | (0U << 4U)\
                        | (0U << 5U)\
                        | (0U << 6U)\
                        | (0U << 7U)\
                        | (0U << 8U)\
                        | (0U << 9U)\
                        | (0U << 10U)\
                        | (0U << 11U)\
                        | (0U << 12U)\
                        | (0U << 13U)\
                        | (0U << 14U)\
                        | (0U << 15U)\
                        | (0U << 16U)\
                        | (0U << 17U)\
                        | (0U << 18U)\
                        | (0U << 19U)\
                        | (0U << 20U)\
                        | (0U << 21U)\
                        | (0U << 22U)\
                        | (0U << 23U)\
                        | (0U << 24U)\
                        | (0U << 25U)\
					    | (0U << 26U)\
                        | (0U << 27U)\
                        | (0U << 28U)\
                        | (0U << 29U)\
                        | (0U << 30U)\
                        | (0U << 31U)
						
#define VIM_REQMASKSET3_CONFIGVALUE	0U\
                        | (0U << 1U)\
                        | (0U << 2U)\
                        | (0U << 3U)\
                        | (0U << 4U)\
                        | (0U << 5U)\
                        | (0U << 6U)\
                        | (0U << 7U)\
                        | (0U << 8U)\
                        | (0U << 9U)\
                        | (0U << 10U)\
                        | (0U << 11U)\
                        | (0U << 12U)\
                        | (0U << 13U)\
                        | (0U << 14U)\
                        | (0U << 15U)\
                        | (0U << 16U)\
                        | (0U << 17U)\
                        | (0U << 18U)\
                        | (0U << 19U)\
                        | (0U << 20U)\
                        | (0U << 21U)\
                        | (0U << 22U)\
                        | (0U << 23U)\
                        | (0U << 24U)\
                        | (0U << 25U)\
						| (0U << 26U)\
                        | (0U << 27U)\
                        | (0U << 28U)\
                        | (0U << 29U)\
                        | (0U << 30U)\
                        | (0U << 31U)
						
#define VIM_WAKEMASKSET0_CONFIGVALUE	0xFFFFFFFFU
#define VIM_WAKEMASKSET1_CONFIGVALUE	0xFFFFFFFFU
#define VIM_WAKEMASKSET2_CONFIGVALUE	0xFFFFFFFFU
#define VIM_WAKEMASKSET3_CONFIGVALUE	0U
#define VIM_CAPEVT_CONFIGVALUE	    	0U

#define VIM_CHANCTRL_CONFIGVALUE	{0x00010203U,\
	0x04050607U,\
	0x08090A0BU,\
	0x0C0D0E0FU,\
	0x10111213U,\
	0x14151617U,\
	0x18191A1BU,\
	0x1C1D1E1FU,\
	0x20212223U,\
	0x24252627U,\
	0x28292A2BU,\
	0x2C2D2E2FU,\
	0x30313233U,\
	0x34353637U,\
	0x38393A3BU,\
	0x3C3D3E3FU,\
	0x40414243U,\
	0x44454647U,\
	0x48494A4BU,\
	0x4C4D4E4FU,\
	0x50515253U,\
	0x54555657U,\
	0x58595A5BU,\
	0x5C5D5E5FU}

/**
 * @defgroup VIM VIM
 * @brief Vectored Interrupt Manager
 *
 * The vectored interrupt manager (VIM) provides hardware assistance for prioritizing and controlling the
 * many interrupt sources present on a device. Interrupts are caused by events outside of the normal flow of
 * program execution.
 *
 * Related files:
 * - reg_vim.h
 * - sys_vim.h
 * - sys_vim.c
 *
 * @addtogroup VIM
 * @{
 */
/*VIM Interface functions*/
void vimInit(void);
void vimChannelMap(uint32 request, uint32 channel, t_isrFuncPTR handler);
void vimEnableInterrupt(uint32 channel, boolean inttype);
void vimDisableInterrupt(uint32 channel);
void vimGetConfigValue(vim_config_reg_t *config_reg, config_value_type_t type);
/*@}*/
#endif
