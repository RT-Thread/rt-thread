/******************************************************************************
*
* Navota Microelectronics Inc.  Navota Camels 32 Bit MCU
* (c) Copyright 2015-2016 Navota Microelectronics, Inc.
* ALL RIGHTS RESERVED.
*
******************************************************************************
*
* @file flash_cmd.c
*
* @brief application entry point which performs application specific tasks. 
*
*******************************************************************************
*
* provide a demo for how to initialize the NV32, output messages via SCI, 
* flash operations, etc.
* NOTE:
*	printf call may occupy a lot of memory (around 1924 bytes), so please
*	consider your code size before using printf.
******************************************************************************
*
* provide FLASH driver
*
******************************************************************************/

#include "flash.h"

void EFM_LaunchCMD(uint32_t EFM_CMD)
{
   #define DisableInterrupts£»
		if((EFMCMD&EFM_DONE_MASK)== EFM_STATUS_READY)
		{
	  EFMCMD = EFM_CMD;
		}
	while(1)
	{
		if((EFMCMD&EFM_DONE_MASK) == EFM_STATUS_DONE) break;
	}
		#define EnableInterrupts;
}
