/*********************COPYRIGHT(C)  2019 WCH. A11 rights reserved***********************
 * File Name          : ch32f10x_pwr.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : This file provides all the PWR firmware functions.
 ***************************************************************************************/
#include "ch32f10x_pwr.h"
#include "ch32f10x_rcc.h"

/* PWR registers bit address in the alias region */
#define PWR_OFFSET               (PWR_BASE - PERIPH_BASE)

/* CTLR Register */
/* Alias word address of DBP bit */
#define CTLR_OFFSET              (PWR_OFFSET + 0x00)
#define DBP_BitNumber            0x08
#define CTLR_DBP_BB              (PERIPH_BB_BASE + (CTLR_OFFSET * 32) + (DBP_BitNumber * 4))

/* Alias word address of PVDE bit */
#define PVDE_BitNumber           0x04
#define CTLR_PVDE_BB             (PERIPH_BB_BASE + (CTLR_OFFSET * 32) + (PVDE_BitNumber * 4))

/* CSR Register */
/* Alias word address of EWUP bit */
#define CSR_OFFSET               (PWR_OFFSET + 0x04)
#define EWUP_BitNumber           0x08
#define CSR_EWUP_BB              (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (EWUP_BitNumber * 4))

/* PWR registers bit mask */
/* CTLR register bit mask */
#define CTLR_DS_MASK             ((uint32_t)0xFFFFFFFC)
#define CTLR_PLS_MASK            ((uint32_t)0xFFFFFF1F)

/********************************************************************************
 * Function Name  : PWR_DeInit
 * Description    : Deinitializes the PWR peripheral registers to their default 
 *                  reset values. 
 * Input          : None
 * Return         : None
 *********************************************************************************/	
void PWR_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, DISABLE);
}


/********************************************************************************
 * Function Name  : PWR_BackupAccessCmd
 * Description    : Enables or disables access to the RTC and backup registers.  
 * Input          : NewState: new state of the access to the RTC and backup registers,
 *                            This parameter can be: ENABLE or DISABLE. 
 * Return         : None
 *********************************************************************************/	
void PWR_BackupAccessCmd(FunctionalState NewState)
{
  *(__IO uint32_t *) CTLR_DBP_BB = (uint32_t)NewState;
}


/********************************************************************************
 * Function Name  : PWR_PVDCmd
 * Description    : Enables or disables the Power Voltage Detector(PVD).
 * Input          : NewState: new state of the PVD(ENABLE or DISABLE).
 * Return         : None
 *********************************************************************************/	
void PWR_PVDCmd(FunctionalState NewState)
{
  *(__IO uint32_t *) CTLR_PVDE_BB = (uint32_t)NewState;
}


/********************************************************************************
 * Function Name  : PWR_PVDLevelConfig
 * Description    : Configures the voltage threshold detected by the Power Voltage 
 *                  Detector(PVD).
 * Input          : PWR_PVDLevel: specifies the PVD detection level
 *                     PWR_PVDLevel_2V2: PVD detection level set to 2.2V
 *                     PWR_PVDLevel_2V3: PVD detection level set to 2.3V
 *                     PWR_PVDLevel_2V4: PVD detection level set to 2.4V
 *                     PWR_PVDLevel_2V5: PVD detection level set to 2.5V
 *                     PWR_PVDLevel_2V6: PVD detection level set to 2.6V
 *                     PWR_PVDLevel_2V7: PVD detection level set to 2.7V
 *                     PWR_PVDLevel_2V8: PVD detection level set to 2.8V
 *                     PWR_PVDLevel_2V9: PVD detection level set to 2.9V
 * Return         : None
 *********************************************************************************/	
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel)
{
  uint32_t tmpreg = 0;
  tmpreg = PWR->CTLR;
  tmpreg &= CTLR_PLS_MASK;
  tmpreg |= PWR_PVDLevel;
  PWR->CTLR = tmpreg;
}


/********************************************************************************
 * Function Name  : PWR_WakeUpPinCmd
 * Description    : Enables or disables the WakeUp Pin functionality.
 * Input          : NewState: new state of the WakeUp Pin functionality(ENABLE or DISABLE).
 * Return         : None
 *********************************************************************************/	
void PWR_WakeUpPinCmd(FunctionalState NewState)
{
  *(__IO uint32_t *) CSR_EWUP_BB = (uint32_t)NewState;
}


/********************************************************************************
 * Function Name  : PWR_EnterSTOPMode
 * Description    : Enters STOP mode.
 * Input          : PWR_Regulator: specifies the regulator state in STOP mode.
 *                    PWR_Regulator_ON: STOP mode with regulator ON
 *                    PWR_Regulator_LowPower: STOP mode with regulator in low power mode  
 *                  PWR_STOPEntry: specifies if STOP mode in entered with WFI or WFE instruction.
 *                    PWR_STOPEntry_WFI: enter STOP mode with WFI instruction
 *                    PWR_STOPEntry_WFE: enter STOP mode with WFE instruction
 * Return         : None
 *********************************************************************************/	
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
{
  uint32_t tmpreg = 0;
  tmpreg = PWR->CTLR;
  tmpreg &= CTLR_DS_MASK;
  tmpreg |= PWR_Regulator;
  PWR->CTLR = tmpreg;
  SCB->SCR |= SCB_SCR_SLEEPDEEP;
  
  if(PWR_STOPEntry == PWR_STOPEntry_WFI)
  {   
    __WFI();
  }
  else
  {
    __WFE();
  }
  
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP);  
}

/********************************************************************************
 * Function Name  : PWR_EnterSTANDBYMode
 * Description    : Enters STANDBY mode.
 * Input          : None
 * Return         : None
 *********************************************************************************/	
void PWR_EnterSTANDBYMode(void)
{
  PWR->CTLR |= PWR_CTLR_CWUF;
  PWR->CTLR |= PWR_CTLR_PDDS;
  SCB->SCR |= SCB_SCR_SLEEPDEEP;
#if defined ( __CC_ARM   )
  __force_stores();
#endif
  __WFI();
}


/********************************************************************************
 * Function Name  : PWR_GetFlagStatus
 * Description    : Checks whether the specified PWR flag is set or not.
 * Input          : PWR_FLAG: specifies the flag to check.
 *                     PWR_FLAG_WU: Wake Up flag
 *                     PWR_FLAG_SB: StandBy flag
 *                     PWR_FLAG_PVDO: PVD Output
 * Return         : The new state of PWR_FLAG (SET or RESET).
 *********************************************************************************/
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
  FlagStatus bitstatus = RESET;
  
  if ((PWR->CSR & PWR_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}


/********************************************************************************
 * Function Name  : PWR_ClearFlag
 * Description    : Clears the PWR's pending flags.
 * Input          : PWR_FLAG: specifies the flag to clear.
 *                     PWR_FLAG_WU: Wake Up flag
 *                     PWR_FLAG_SB: StandBy flag
 * Return         : None
 *********************************************************************************/
void PWR_ClearFlag(uint32_t PWR_FLAG)
{        
  PWR->CTLR |=  PWR_FLAG << 2;
}

