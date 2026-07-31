/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_DUMP_MEM_H
#define BSP_DUMP_MEM_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/* Retention section definitions */
extern uint32_t __ddsc_RAM_END;

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

uint32_t   BSP_GetFaultPc(void);
void       BSP_SetFaultPc(uint32_t pc);
uint8_t    BSP_GetFaultCount(void);
void       BSP_SetFaultCount(uint8_t cnt);
void       BSP_SaveOopsDump(uint32_t * mspfile, uint32_t * pspfile, uint32_t mode);
uint16_t   BSP_SaveOopsDumpThreadInfo(void);
void       BSP_InitOopsData(void);
void       BSP_DisplayOopsDump(char * halt_color_ptr, char * bold_color_ptr, char * clear_color_ptr);
uint32_t * BSP_GetOopsThreadPtr(void);
uint16_t   BSP_GetOopsThreadSize(void);

#ifndef TEST_HAS_OWN_EXCEPTION_HDL
void HardFault_HandlerC(unsigned long * exception_args);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);

#endif

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
