/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_pwr.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all the PWR firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_pwr.h"
#include "stm32f10x_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* --------- PWR registers bit address in the alias region ---------- */
#define PWR_OFFSET               (PWR_BASE - PERIPH_BASE)

/* --- CR Register ---*/
/* Alias word address of DBP bit */
#define CR_OFFSET                (PWR_OFFSET + 0x00)
#define DBP_BitNumber            0x08
#define CR_DBP_BB                (PERIPH_BB_BASE + (CR_OFFSET * 32) + (DBP_BitNumber * 4))

/* Alias word address of PVDE bit */
#define PVDE_BitNumber           0x04
#define CR_PVDE_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PVDE_BitNumber * 4))

/* --- CSR Register ---*/
/* Alias word address of EWUP bit */
#define CSR_OFFSET               (PWR_OFFSET + 0x04)
#define EWUP_BitNumber           0x08
#define CSR_EWUP_BB              (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (EWUP_BitNumber * 4))

/* ------------------ PWR registers bit mask ------------------------ */
/* CR register bit mask */
#define CR_PDDS_Set              ((u32)0x00000002)
#define CR_DS_Mask               ((u32)0xFFFFFFFC)
#define CR_CWUF_Set              ((u32)0x00000004)
#define CR_PLS_Mask              ((u32)0xFFFFFF1F)

/* --------- Cortex System Control register bit mask ---------------- */
/* Cortex System Control register address */
#define SCB_SysCtrl              ((u32)0xE000ED10)
/* SLEEPDEEP bit mask */
#define SysCtrl_SLEEPDEEP_Set    ((u32)0x00000004)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : PWR_DeInit
* Description    : Deinitializes the PWR peripheral registers to their default
*                  reset values.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PWR_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, DISABLE);
}

/*******************************************************************************
* Function Name  : PWR_BackupAccessCmd
* Description    : Enables or disables access to the RTC and backup registers.
* Input          : - NewState: new state of the access to the RTC and backup
*                    registers. This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void PWR_BackupAccessCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(vu32 *) CR_DBP_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : PWR_PVDCmd
* Description    : Enables or disables the Power Voltage Detector(PVD).
* Input          : - NewState: new state of the PVD.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void PWR_PVDCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(vu32 *) CR_PVDE_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : PWR_PVDLevelConfig
* Description    : Configures the voltage threshold detected by the Power Voltage
*                  Detector(PVD).
* Input          : - PWR_PVDLevel: specifies the PVD detection level
*                    This parameter can be one of the following values:
*                       - PWR_PVDLevel_2V2: PVD detection level set to 2.2V
*                       - PWR_PVDLevel_2V3: PVD detection level set to 2.3V
*                       - PWR_PVDLevel_2V4: PVD detection level set to 2.4V
*                       - PWR_PVDLevel_2V5: PVD detection level set to 2.5V
*                       - PWR_PVDLevel_2V6: PVD detection level set to 2.6V
*                       - PWR_PVDLevel_2V7: PVD detection level set to 2.7V
*                       - PWR_PVDLevel_2V8: PVD detection level set to 2.8V
*                       - PWR_PVDLevel_2V9: PVD detection level set to 2.9V
* Output         : None
* Return         : None
*******************************************************************************/
void PWR_PVDLevelConfig(u32 PWR_PVDLevel)
{
  u32 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));

  tmpreg = PWR->CR;

  /* Clear PLS[7:5] bits */
  tmpreg &= CR_PLS_Mask;

  /* Set PLS[7:5] bits according to PWR_PVDLevel value */
  tmpreg |= PWR_PVDLevel;

  /* Store the new value */
  PWR->CR = tmpreg;
}

/*******************************************************************************
* Function Name  : PWR_WakeUpPinCmd
* Description    : Enables or disables the WakeUp Pin functionality.
* Input          : - NewState: new state of the WakeUp Pin functionality.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void PWR_WakeUpPinCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(vu32 *) CSR_EWUP_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : PWR_EnterSTOPMode
* Description    : Enters STOP mode.
* Input          : - PWR_Regulator: specifies the regulator state in STOP mode.
*                    This parameter can be one of the following values:
*                       - PWR_Regulator_ON: STOP mode with regulator ON
*                       - PWR_Regulator_LowPower: STOP mode with
*                         regulator in low power mode
*                  - PWR_STOPEntry: specifies if STOP mode in entered with WFI or 
*                    WFE instruction.
*                    This parameter can be one of the following values:
*                       - PWR_STOPEntry_WFI: enter STOP mode with WFI instruction
*                       - PWR_STOPEntry_WFE: enter STOP mode with WFE instruction
* Output         : None
* Return         : None
*******************************************************************************/
void PWR_EnterSTOPMode(u32 PWR_Regulator, u8 PWR_STOPEntry)
{
  u32 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_PWR_REGULATOR(PWR_Regulator));
  assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));
  
  /* Select the regulator state in STOP mode ---------------------------------*/
  tmpreg = PWR->CR;

  /* Clear PDDS and LPDS bits */
  tmpreg &= CR_DS_Mask;

  /* Set LPDS bit according to PWR_Regulator value */
  tmpreg |= PWR_Regulator;

  /* Store the new value */
  PWR->CR = tmpreg;

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  *(vu32 *) SCB_SysCtrl |= SysCtrl_SLEEPDEEP_Set;
  
  /* Select STOP mode entry --------------------------------------------------*/
  if(PWR_STOPEntry == PWR_STOPEntry_WFI)
  {   
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __WFE();
  }
}

/*******************************************************************************
* Function Name  : PWR_EnterSTANDBYMode
* Description    : Enters STANDBY mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PWR_EnterSTANDBYMode(void)
{
  /* Clear Wake-up flag */
  PWR->CR |= CR_CWUF_Set;

  /* Select STANDBY mode */
  PWR->CR |= CR_PDDS_Set;

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  *(vu32 *) SCB_SysCtrl |= SysCtrl_SLEEPDEEP_Set;

  /* Request Wait For Interrupt */
  __WFI();
}

/*******************************************************************************
* Function Name  : PWR_GetFlagStatus
* Description    : Checks whether the specified PWR flag is set or not.
* Input          : - PWR_FLAG: specifies the flag to check.
*                    This parameter can be one of the following values:
*                       - PWR_FLAG_WU: Wake Up flag
*                       - PWR_FLAG_SB: StandBy flag
*                       - PWR_FLAG_PVDO: PVD Output
* Output         : None
* Return         : The new state of PWR_FLAG (SET or RESET).
*******************************************************************************/
FlagStatus PWR_GetFlagStatus(u32 PWR_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_PWR_GET_FLAG(PWR_FLAG));
  
  if ((PWR->CSR & PWR_FLAG) != (u32)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the flag status */
  return bitstatus;
}

/*******************************************************************************
* Function Name  : PWR_ClearFlag
* Description    : Clears the PWR's pending flags.
* Input          : - PWR_FLAG: specifies the flag to clear.
*                    This parameter can be one of the following values:
*                       - PWR_FLAG_WU: Wake Up flag
*                       - PWR_FLAG_SB: StandBy flag
* Output         : None
* Return         : None
*******************************************************************************/
void PWR_ClearFlag(u32 PWR_FLAG)
{
  /* Check the parameters */
  assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));
         
  PWR->CR |=  PWR_FLAG << 2;
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
