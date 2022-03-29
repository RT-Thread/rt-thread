/**
  ******************************************************************************
  * @file    lib_CodeRAM.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   Codes executed in SRAM.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "lib_CodeRAM.h"

#ifndef __GNUC__
/**
  * @brief  Enter idle mode with flash deep standby.
  * @note   This function is executed in RAM.
  * @param  None
  * @retval None
  */
__RAM_FUNC void PMU_EnterIdle_FlashDSTB(void)
{
  /* Flash deep standby */
  FLASH->PASS = 0x55AAAA55;
  FLASH->DSTB = 0xAA5555AA;
  /* Enter Idle mode */
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
  __WFI();
}
#endif

/*********************************** END OF FILE ******************************/
