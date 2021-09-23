/**
  ******************************************************************************
  * @file    lib_misc.c 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   MISC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_misc.h"

/**
  * @brief  Get flag status.
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
  
  if (MISC->SRAMINT&FlagMask)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Clear flag status.
  * @param  FlagMask: can use the ¡®|¡¯ operator
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
  
  MISC->SRAMINT = FlagMask;
}

/**
  * @brief  Interrupt configure.
  * @param  INTMask: can use the ¡®|¡¯ operator
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
  
  tmp = MISC->SRAMINIT;
  if (NewState == ENABLE)
  {
    tmp |= INTMask;
  }
  else
  {
    tmp &= ~INTMask;
  }
  MISC->SRAMINIT = tmp;
}

/**
  * @brief  sram parity contrl.
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
    MISC->SRAMINIT |= MISC_SRAMINIT_PEN;
  }
  else
  {
    MISC->SRAMINIT &= ~MISC_SRAMINIT_PEN;
  }
}

/**
  * @brief  Get sram parity error address.
  * @param  None
  * @retval parity error address.
  */
uint32_t MISC_GetSRAMPEAddr(void)
{
  uint32_t tmp;
    
  tmp = MISC->PARERR;
  tmp = tmp*4 + 0x20000000;
  return tmp;
}

/**
  * @brief  Get APB error address.
  * @param  None
  * @retval APB error address.
  */
uint32_t MISC_GetAPBErrAddr(void)
{
  uint32_t tmp;
    
  tmp = MISC->PIADDR;
  tmp = tmp + 0x40010000;
  return tmp;
}

/**
  * @brief  Get AHB error address.
  * @param  None
  * @retval AHB error address.
  */
uint32_t MISC_GetAHBErrAddr(void)
{
  uint32_t tmp;
    
  tmp = MISC->HIADDR;
  tmp = tmp + 0x40000000;
  return tmp;
}

/**
  * @brief  IR control.
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
  
  tmp = MISC->IREN;
  if (NewState == ENABLE)
  {
    tmp |= IRx;
  }
  else
  {
    tmp &= ~IRx;
  }
  MISC->IREN = tmp;
}

/**
  * @brief  IR duty configure.
  * @param  DutyHigh
                The high pulse width will be (DUTYH + 1)*APBCLK period.
            DutyLow
                The low pulse width will be (DUTYL + 1)*APBCLK period.
  * @retval None
  */
void MISC_IRDutyConfig(uint16_t DutyHigh, uint16_t DutyLow)
{
  MISC->DUTYH = DutyHigh;
  MISC->DUTYL = DutyLow;
}

/**
  * @brief  Hardfault generation configure.
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
    MISC->IRQLAT &= ~MISC_IRQLAT_NOHARDFAULT;
  }
  else
  {
    MISC->IRQLAT |= MISC_IRQLAT_NOHARDFAULT;
  }
}

/**
  * @brief  Control if the lockup will issue a system reset.
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
    MISC->IRQLAT |= MISC_IRQLAT_LOCKRESET;
  }
  else
  {
    MISC->IRQLAT &= ~MISC_IRQLAT_LOCKRESET;
  }
}

/**
  * @brief  IRQLAT configure.
  * @param  Latency:0~255
  * @retval None
  */
void MISC_IRQLATConfig(uint8_t Latency)
{
  uint32_t tmp;
    
  tmp = MISC->IRQLAT;
  tmp &= ~MISC_IRQLAT_IRQLAT;
  tmp |= Latency;
  MISC->IRQLAT = tmp;
}

/*********************************** END OF FILE ******************************/
