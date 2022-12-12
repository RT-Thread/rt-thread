/**
  ******************************************************************************
  * @file    lib_misc.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   MISC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_misc.h"

/**
  * @brief  Gets MISC flag status.
  * @param  FlagMask:
                MISC_FLAG_LOCKUP 
                MISC_FLAG_PIAC     
                MISC_FLAG_HIAC
                MISC_FLAG_PERR     
  * @retval Flag status.
  */
uint8_t MISC_GetFlag(uint32_t FlagMask)
{
  /* Check parameters */ 
  assert_parameters(IS_MISC_FLAGR(FlagMask)); 
  
  if (MISC1->SRAMINT&FlagMask)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Clears MISC flag status.
  * @param  FlagMask: can use the '|' operator
                MISC_FLAG_LOCKUP 
                MISC_FLAG_PIAC     
                MISC_FLAG_HIAC          
                MISC_FLAG_PERR     
  * @retval None
  */
void MISC_ClearFlag(uint32_t FlagMask)
{
  /* Check parameters */ 
  assert_parameters(IS_MISC_FLAGC(FlagMask)); 
  
  MISC1->SRAMINT = FlagMask;
}

/**
  * @brief  Enables or disables MISC interrupt.
  * @param  INTMask: can use the '|' operator
                MISC_INT_LOCK 
                MISC_INT_PIAC   
                MISC_INT_HIAC      
                MISC_INT_PERR   
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void MISC_INTConfig(uint32_t INTMask, uint32_t NewState)
{
  uint32_t tmp;
  
  /* Check parameters */ 
  assert_parameters(IS_MISC_INT(INTMask));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  tmp = MISC1->SRAMINIT;
  if (NewState == ENABLE)
  {
    tmp |= INTMask;
  }
  else
  {
    tmp &= ~INTMask;
  }
  MISC1->SRAMINIT = tmp;
}

/**
  * @brief  Enables or disables SRAM parity.
  * @param  NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void MISC_SRAMParityCmd(uint32_t NewState)
{  
  /* Check parameters */ 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    MISC1->SRAMINIT |= MISC1_SRAMINIT_PEN;
  }
  else
  {
    MISC1->SRAMINIT &= ~MISC1_SRAMINIT_PEN;
  }
}

/**
  * @brief  Gets SRAM parity error address.
  * @param  None
  * @retval parity error address.
  */
uint32_t MISC_GetSRAMPEAddr(void)
{
  uint32_t tmp;
    
  tmp = MISC1->PARERR;
  tmp = tmp*4 + 0x20000000;
  return tmp;
}

/**
  * @brief  Gets APB error address.
  * @param  None
  * @retval APB error address.
  */
uint32_t MISC_GetAPBErrAddr(void)
{
  uint32_t tmp;
    
  tmp = MISC1->PIADDR;
  tmp = tmp + 0x40000000;
  return tmp;
}

/**
  * @brief  Gets AHB error address.
  * @param  None
  * @retval AHB error address.
  */
uint32_t MISC_GetAHBErrAddr(void)
{
  return (MISC1->HIADDR);
}

/**
  * @brief  Enables or disables UART transmit IR function.
  * @param  IRx:
                MISC_IREN_TX0
                MISC_IREN_TX1 
                MISC_IREN_TX2 
                MISC_IREN_TX3 
                MISC_IREN_TX4 
                MISC_IREN_TX5 
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void MISC_IRCmd(uint32_t IRx, uint32_t NewState)
{
  uint32_t tmp;
  
  /* Check parameters */ 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));  
  assert_parameters(IS_MISC_IREN(IRx));
  
  tmp = MISC1->IREN;
  if (NewState == ENABLE)
  {
    tmp |= IRx;
  }
  else
  {
    tmp &= ~IRx;
  }
  MISC1->IREN = tmp;
}

/**
  * @brief  Configures SUART transmit IR duty.
  * @param  DutyHigh
                The high pulse width will be (DUTYH + 1)*APBCLK period.
            DutyLow
                The low pulse width will be (DUTYL + 1)*APBCLK period.
  * @retval None
  */
void MISC_IRDutyConfig(uint16_t DutyHigh, uint16_t DutyLow)
{
  MISC1->DUTYH = DutyHigh;
  MISC1->DUTYL = DutyLow;
}

/**
  * @brief  Enables or disables Hardfault generation.
  * @param  NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void MISC_HardFaultCmd(uint32_t NewState)
{
   /* Check parameters */ 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 
  
  if (NewState == ENABLE)
  {
    MISC1->IRQLAT &= ~MISC1_IRQLAT_NOHARDFAULT;
  }
  else
  {
    MISC1->IRQLAT |= MISC1_IRQLAT_NOHARDFAULT;
  }
}

/**
  * @brief  Enables or disables a system reset when the CM0 lockup happened.
  * @param  NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void MISC_LockResetCmd(uint32_t NewState)
{
   /* Check parameters */ 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 
  
  if (NewState == ENABLE)
  {
    MISC1->IRQLAT |= MISC1_IRQLAT_LOCKRESET;
  }
  else
  {
    MISC1->IRQLAT &= ~MISC1_IRQLAT_LOCKRESET;
  }
}

/**
  * @brief  Configures IRQ latency.
  * @param  Latency:0~255
  * @retval None
  */
void MISC_IRQLATConfig(uint8_t Latency)
{
  uint32_t tmp;
    
  tmp = MISC1->IRQLAT;
  tmp &= ~MISC1_IRQLAT_IRQLAT;
  tmp |= Latency;
  MISC1->IRQLAT = tmp;
}

/*********************************** END OF FILE ******************************/
