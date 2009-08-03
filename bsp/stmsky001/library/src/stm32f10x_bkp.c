/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_bkp.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all the BKP firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_bkp.h"
#include "stm32f10x_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ------------ BKP registers bit address in the alias region ----------- */
#define BKP_OFFSET        (BKP_BASE - PERIPH_BASE)

/* --- CR Register ---*/
/* Alias word address of TPAL bit */
#define CR_OFFSET         (BKP_OFFSET + 0x30)
#define TPAL_BitNumber    0x01
#define CR_TPAL_BB        (PERIPH_BB_BASE + (CR_OFFSET * 32) + (TPAL_BitNumber * 4))

/* Alias word address of TPE bit */
#define TPE_BitNumber     0x00
#define CR_TPE_BB         (PERIPH_BB_BASE + (CR_OFFSET * 32) + (TPE_BitNumber * 4))

/* --- CSR Register ---*/
/* Alias word address of TPIE bit */
#define CSR_OFFSET        (BKP_OFFSET + 0x34)
#define TPIE_BitNumber    0x02
#define CSR_TPIE_BB       (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TPIE_BitNumber * 4))

/* Alias word address of TIF bit */
#define TIF_BitNumber     0x09
#define CSR_TIF_BB        (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TIF_BitNumber * 4))

/* Alias word address of TEF bit */
#define TEF_BitNumber     0x08
#define CSR_TEF_BB        (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TEF_BitNumber * 4))


/* ---------------------- BKP registers bit mask ------------------------ */
/* RTCCR register bit mask */
#define RTCCR_CAL_Mask    ((u16)0xFF80)
#define RTCCR_Mask        ((u16)0xFC7F)

/* CSR register bit mask */
#define CSR_CTE_Set       ((u16)0x0001)
#define CSR_CTI_Set       ((u16)0x0002)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : BKP_DeInit
* Description    : Deinitializes the BKP peripheral registers to their default
*                  reset values.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BKP_DeInit(void)
{
  RCC_BackupResetCmd(ENABLE);
  RCC_BackupResetCmd(DISABLE);
}

/*******************************************************************************
* Function Name  : BKP_TamperPinLevelConfig
* Description    : Configures the Tamper Pin active level.
* Input          : - BKP_TamperPinLevel: specifies the Tamper Pin active level.
*                    This parameter can be one of the following values:
*                       - BKP_TamperPinLevel_High: Tamper pin active on high level
*                       - BKP_TamperPinLevel_Low: Tamper pin active on low level
* Output         : None
* Return         : None
*******************************************************************************/
void BKP_TamperPinLevelConfig(u16 BKP_TamperPinLevel)
{
  /* Check the parameters */
  assert_param(IS_BKP_TAMPER_PIN_LEVEL(BKP_TamperPinLevel));

  *(vu32 *) CR_TPAL_BB = BKP_TamperPinLevel;
}

/*******************************************************************************
* Function Name  : BKP_TamperPinCmd
* Description    : Enables or disables the Tamper Pin activation.
* Input          : - NewState: new state of the Tamper Pin activation.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void BKP_TamperPinCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(vu32 *) CR_TPE_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : BKP_ITConfig
* Description    : Enables or disables the Tamper Pin Interrupt.
* Input          : - NewState: new state of the Tamper Pin Interrupt.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void BKP_ITConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(vu32 *) CSR_TPIE_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : BKP_RTCOutputConfig
* Description    : Select the RTC output source to output on the Tamper pin.
* Input          : - BKP_RTCOutputSource: specifies the RTC output source.
*                    This parameter can be one of the following values:
*                       - BKP_RTCOutputSource_None: no RTC output on the Tamper pin.
*                       - BKP_RTCOutputSource_CalibClock: output the RTC clock
*                         with frequency divided by 64 on the Tamper pin.
*                       - BKP_RTCOutputSource_Alarm: output the RTC Alarm pulse 
*                         signal on the Tamper pin.
*                       - BKP_RTCOutputSource_Second: output the RTC Second pulse 
*                         signal on the Tamper pin.  
* Output         : None
* Return         : None
*******************************************************************************/
void BKP_RTCOutputConfig(u16 BKP_RTCOutputSource)
{
  u16 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_BKP_RTC_OUTPUT_SOURCE(BKP_RTCOutputSource));

  tmpreg = BKP->RTCCR;

  /* Clear CCO, ASOE and ASOS bits */
  tmpreg &= RTCCR_Mask;
  
  /* Set CCO, ASOE and ASOS bits according to BKP_RTCOutputSource value */
  tmpreg |= BKP_RTCOutputSource;

  /* Store the new value */
  BKP->RTCCR = tmpreg;
}

/*******************************************************************************
* Function Name  : BKP_SetRTCCalibrationValue
* Description    : Sets RTC Clock Calibration value.
* Input          : - CalibrationValue: specifies the RTC Clock Calibration value.
*                    This parameter must be a number between 0 and 0x7F.
* Output         : None
* Return         : None
*******************************************************************************/
void BKP_SetRTCCalibrationValue(u8 CalibrationValue)
{
  u16 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_BKP_CALIBRATION_VALUE(CalibrationValue));

  tmpreg = BKP->RTCCR;

  /* Clear CAL[6:0] bits */
  tmpreg &= RTCCR_CAL_Mask;

  /* Set CAL[6:0] bits according to CalibrationValue value */
  tmpreg |= CalibrationValue;

  /* Store the new value */
  BKP->RTCCR = tmpreg;
}

/*******************************************************************************
* Function Name  : BKP_WriteBackupRegister
* Description    : Writes user data to the specified Data Backup Register.
* Input          : - BKP_DR: specifies the Data Backup Register.
*                    This parameter can be BKP_DRx where x:[1, 42]
*                  - Data: data to write
* Output         : None
* Return         : None
*******************************************************************************/
void BKP_WriteBackupRegister(u16 BKP_DR, u16 Data)
{
  /* Check the parameters */
  assert_param(IS_BKP_DR(BKP_DR));

  *(vu16 *) (BKP_BASE + BKP_DR) = Data;
}

/*******************************************************************************
* Function Name  : BKP_ReadBackupRegister
* Description    : Reads data from the specified Data Backup Register.
* Input          : - BKP_DR: specifies the Data Backup Register.
*                    This parameter can be BKP_DRx where x:[1, 42]
* Output         : None
* Return         : The content of the specified Data Backup Register
*******************************************************************************/
u16 BKP_ReadBackupRegister(u16 BKP_DR)
{
  /* Check the parameters */
  assert_param(IS_BKP_DR(BKP_DR));

  return (*(vu16 *) (BKP_BASE + BKP_DR));
}

/*******************************************************************************
* Function Name  : BKP_GetFlagStatus
* Description    : Checks whether the Tamper Pin Event flag is set or not.
* Input          : None
* Output         : None
* Return         : The new state of the Tamper Pin Event flag (SET or RESET).
*******************************************************************************/
FlagStatus BKP_GetFlagStatus(void)
{
  return (FlagStatus)(*(vu32 *) CSR_TEF_BB);
}

/*******************************************************************************
* Function Name  : BKP_ClearFlag
* Description    : Clears Tamper Pin Event pending flag.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BKP_ClearFlag(void)
{
  /* Set CTE bit to clear Tamper Pin Event flag */
  BKP->CSR |= CSR_CTE_Set;
}

/*******************************************************************************
* Function Name  : BKP_GetITStatus
* Description    : Checks whether the Tamper Pin Interrupt has occurred or not.
* Input          : None
* Output         : None
* Return         : The new state of the Tamper Pin Interrupt (SET or RESET).
*******************************************************************************/
ITStatus BKP_GetITStatus(void)
{
  return (ITStatus)(*(vu32 *) CSR_TIF_BB);
}

/*******************************************************************************
* Function Name  : BKP_ClearITPendingBit
* Description    : Clears Tamper Pin Interrupt pending bit.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BKP_ClearITPendingBit(void)
{
  /* Set CTI bit to clear Tamper Pin Interrupt pending bit */
  BKP->CSR |= CSR_CTI_Set;
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
