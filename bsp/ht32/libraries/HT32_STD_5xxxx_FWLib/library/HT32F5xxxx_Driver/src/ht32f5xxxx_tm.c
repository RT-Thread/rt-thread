/*********************************************************************************************************//**
 * @file    ht32f5xxxx_tm.c
 * @version $Rev:: 7059         $
 * @date    $Date:: 2023-07-27 #$
 * @brief   This file provides all the TM firmware functions.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f5xxxx_tm.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup TM TM
  * @brief TM driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup TM_Private_Define TM private definitions
  * @{
  */
#define CNTCFR_UEVDIS       0x00000001ul
#define CNTCFR_UGDIS        0x00000002ul
#define CNTCFR_DIR          0x01000000ul
#define CNTCFR_CMSEL_MASK   ~0x00030000ul
#define CNTCFR_CKDIV_MASK   ~0x00000300ul

#define MDCFR_SPMSET        0x01000000ul
#define MDCFR_TSE           0x00000001ul
#define MDCFR_SMSEL_MASK    ~0x00000700ul
#define MDCFR_MMSEL_MASK    ~0x00070000ul

#if 0
#define TRCFR_ECME          0x01000000ul
#define TRCFR_ETI_POL       0x00010000ul
#define TRCFR_ETI_PSC_MASK  ~0x00003000ul
#define TRCFR_ETIF_MASK     ~0x00000F00ul
#define TRCFR_ETI_CONF_MASK ~0x00013F00ul
#endif
#define TRCFR_TRSEL_MASK    ~0x0000000Ful

#define CTR_TME             0x00000001ul
#define CTR_CRBE            0x00000002ul
#define CTR_CHCCDS          0x00010000ul

#define CH0ICFR_CH0SRC      0x80000000ul
#define CHICFR_CHF_MASK     ~0x000000FFul
#define CHICFR_CHCCS_MASK   ~0x00030000ul
#define CHICFR_CHPSC_MASK   ~0x000C0000ul

#define CHOCFR_REFCE        0x00000008ul
#define CHOCFR_CHPRE        0x00000010ul
#define CHOCFR_IMAE         0x00000020ul
#define CHOCFR_CHOM_MASK    ~0x00000107ul

#define CHPOLR_CH0P         0x00000001ul
#define CHPOLR_CH1P         0x00000004ul
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
static void _TM_CHx_Config(HT_TM_TypeDef* TMx, TM_CH_Enum Ch, TM_CHP_Enum Pol, TM_CHCCS_Enum Sel, u8 Filter);

/* Private macro -------------------------------------------------------------------------------------------*/
#if (LIBCFG_TM_TIFN_5BIT)
#define FILTER_PROCESS(cap)                ((cap->Fsampling << 5) + cap->Event)
#else
#define FILTER_PROCESS(cap)                ((cap->Fsampling << 4) + cap->Event)
#endif

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup TM_Exported_Functions TM exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the TMx peripheral registers to their default reset values.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @retval None
 ************************************************************************************************************/
void TM_DeInit(HT_TM_TypeDef* TMx)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));

  #if (!LIBCFG_NO_GPTM0)
  if (TMx == HT_GPTM0)
  {
    RSTCUReset.Bit.GPTM0 = 1;
  }
  #endif
  #if (LIBCFG_GPTM1)
  else if (TMx == HT_GPTM1)
  {
    RSTCUReset.Bit.GPTM1 = 1;
  }
  #endif
  #if (LIBCFG_MCTM0)
  else if (TMx == HT_MCTM0)
  {
    RSTCUReset.Bit.MCTM0 = 1;
  }
  #endif
  #if (LIBCFG_SCTM0)
  if (TMx == HT_SCTM0)
  {
    RSTCUReset.Bit.SCTM0 = 1;
  }
  #endif
  #if (LIBCFG_SCTM1)
  else if (TMx == HT_SCTM1)
  {
    RSTCUReset.Bit.SCTM1 = 1;
  }
  #endif
  #if (LIBCFG_SCTM2)
  else if (TMx == HT_SCTM2)
  {
    RSTCUReset.Bit.SCTM2 = 1;
  }
  #endif
  #if (LIBCFG_SCTM3)
  else if (TMx == HT_SCTM3)
  {
    RSTCUReset.Bit.SCTM3 = 1;
  }
  #endif
  #if (LIBCFG_PWM0)
  if (TMx == HT_PWM0)
  {
    RSTCUReset.Bit.PWM0 = 1;
  }
  #endif
  #if (LIBCFG_PWM1)
  else if (TMx == HT_PWM1)
  {
    RSTCUReset.Bit.PWM1 = 1;
  }
  #endif
  #if (LIBCFG_PWM2)
  else if (TMx == HT_PWM2)
  {
    RSTCUReset.Bit.PWM1 = 1;
  }
  #endif

  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Initialize the TMx counter to reload, prescaler, counter mode and repetition counter.
 * @param TMx: where TMx is the selected TM from the TM peripheral.
 * @param TimeBaseInit: Point to a \ref TM_TimeBaseInitTypeDef that contains the configuration information.
 * @retval None
 ************************************************************************************************************/
void TM_TimeBaseInit(HT_TM_TypeDef* TMx, TM_TimeBaseInitTypeDef* TimeBaseInit)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CNT_MODE(TimeBaseInit->CounterMode));
  Assert_Param(IS_TM_PSC_RLD(TimeBaseInit->PSCReloadTime));

  /* Set the counter reload value                                                                           */
  TMx->CRR = TimeBaseInit->CounterReload;

  /* Set the Prescaler value                                                                                */
  TMx->PSCR = TimeBaseInit->Prescaler;

  /* Select the Counter Mode                                                                                */
  TMx->CNTCFR &= CNTCFR_CMSEL_MASK;        /* CNTCFR_DIR is read only when the timer configured as          */
  TMx->CNTCFR &= ~(u32)CNTCFR_DIR;         /* Center-aligned mode. Reset mode first and then reset the      */
                                           /* CNTCFR_DIR bit (separate as two steps).                       */

  TMx->CNTCFR |= TimeBaseInit->CounterMode;

  #if (LIBCFG_MCTM0)
  if (TMx == HT_MCTM0)
  {
    /* Set the Repetition value                                                                             */
    TMx->REPR = TimeBaseInit->RepetitionCounter;
  }
  #endif

  /* To reload the Prescaler value immediatly or next update event                                          */
  TMx->EVGR = TimeBaseInit->PSCReloadTime;
}

/*********************************************************************************************************//**
 * @brief Initialize the TMx channel N output.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param OutInit: Point to a \ref TM_OutputInitTypeDef structure that contains
                   the configuration information.
 * @retval None
 ************************************************************************************************************/
void TM_OutputInit(HT_TM_TypeDef* TMx, TM_OutputInitTypeDef* OutInit)
{
  vu32 *pOcfr = (vu32*)&TMx->CH0OCFR + OutInit->Channel;
  vu32 *pCcr = (vu32*)&TMx->CH0CCR + OutInit->Channel;
  vu32 *pAcr = (vu32*)&TMx->CH0ACR + OutInit->Channel;
  u8 bChPos = OutInit->Channel << 1;
  u32 wTmpMask;
  u32 wTmpReg;

  #if (LIBCFG_MCTM0)
  if (TMx == HT_MCTM0)
  {
    wTmpMask = ~(0x3ul << bChPos);
  }
  else
  #endif
  {
    wTmpMask = ~(0x1ul << bChPos);
  }

#if (LIBCFG_PWM_8_CHANNEL)
  if ((OutInit->Channel > TM_CH_3) && (OutInit->Channel <= TM_CH_7) )
  {
    u8 bOffset = OutInit->Channel - 4;
    pOcfr = (vu32*)&TMx->CH4OCFR + bOffset;
    pCcr   = (vu32*)&TMx->CH4CR + bOffset;
  }
#endif

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CH(OutInit->Channel));
  Assert_Param(IS_TM_OM(OutInit->OutputMode));
#if (LIBCFG_PWM_8_CHANNEL)
  if ((OutInit->Channel > TM_CH_3) && (OutInit->Channel <= TM_CH_7) )
  {
    Assert_Param(IS_TM_OM_NOASYM(OutInit->OutputMode));
  }
#endif
  Assert_Param(IS_TM_CHCTL(OutInit->Control));
  Assert_Param(IS_TM_CHP(OutInit->Polarity));
  #if (LIBCFG_MCTM0)
  if (TMx == HT_MCTM0)
  {
    Assert_Param(IS_TM_CHCTL(OutInit->ControlN));
    Assert_Param(IS_TM_CHP(OutInit->PolarityN));
    Assert_Param(IS_MCTM_OIS(OutInit->IdleState));
    Assert_Param(IS_MCTM_OIS(OutInit->IdleStateN));
  }
  #endif

  /* Disable the Channel                                                                                    */
  TMx->CHCTR &= wTmpMask;

  /* Set the Output Compare Polarity                                                                        */
  wTmpReg = TMx->CHPOLR & wTmpMask;
  #if (LIBCFG_MCTM0)
  if (TMx == HT_MCTM0)
  {
    wTmpReg |= (u32)(OutInit->Polarity | (OutInit->PolarityN << 1)) << bChPos;
  }
  else
  #endif
  {
    wTmpReg |= (u32)(OutInit->Polarity) << bChPos;
  }

  TMx->CHPOLR = wTmpReg;

  /* Set the Output Idle State                                                                              */
  #if (LIBCFG_MCTM0)
  if (TMx == HT_MCTM0)
  {
    wTmpReg = TMx->CHBRKCFR & wTmpMask;
    wTmpReg |= (u32)(OutInit->IdleState | (OutInit->IdleStateN << 1)) << bChPos;
    TMx->CHBRKCFR = wTmpReg;
  }
  #endif

  /* Select the Output Compare Mode                                                                         */
  *pOcfr &= CHOCFR_CHOM_MASK;
  *pOcfr |= OutInit->OutputMode;

  /* Set the Capture Compare Register value                                                                 */
  *pCcr = OutInit->Compare;

  /* Set the Asymmetric Compare Register value                                                              */
  *pAcr = OutInit->AsymmetricCompare;

  /* Set the channel state                                                                                  */
  #if (LIBCFG_MCTM0)
  if (TMx == HT_MCTM0)
  {
    TMx->CHCTR |= (u32)(OutInit->Control | (OutInit->ControlN << 1)) << bChPos;
  }
  else
  #endif
  {
    TMx->CHCTR |= (u32)(OutInit->Control) << bChPos;
  }
}

/*********************************************************************************************************//**
 * @brief Initialize input capture of the TMx channel.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param CapInit: Point to a \ref TM_CaptureInitTypeDef structure that contains the configuration
 *                information.
 * @retval None
 ************************************************************************************************************/
void TM_CaptureInit(HT_TM_TypeDef* TMx, TM_CaptureInitTypeDef* CapInit)
{
  u8 Filter;
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CH(CapInit->Channel));
  Assert_Param(IS_TM_CHP(CapInit->Polarity));
  Assert_Param(IS_TM_CHCCS(CapInit->Selection));
  Assert_Param(IS_TM_CHPSC(CapInit->Prescaler));
  #if (LIBCFG_TM_652XX_V1)
  #else
  Assert_Param(IS_TM_FILTER(CapInit->Filter));
  #endif

  #if (LIBCFG_TM_652XX_V1)
  Filter = FILTER_PROCESS(CapInit);
  #else
  Filter = CapInit->Filter;
  #endif
  _TM_CHx_Config(TMx, CapInit->Channel, CapInit->Polarity, CapInit->Selection, Filter);

  /* Set the Input Capture Prescaler value                                                                  */
  TM_CHPSCConfig(TMx, CapInit->Channel, CapInit->Prescaler);
}

/*********************************************************************************************************//**
 * @brief Configure the TMx to measure an external PWM signal.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param CapInit: Point to a \ref TM_CaptureInitTypeDef structure that contains the configuration
 *                information.
 * @retval None
 * @note The CapInit->Channel can only be TM_CH_0 or TM_CH_1. CH2/CH3 are not supported since it cannot be
 *       the STI source to reset the counter.
 ************************************************************************************************************/
void TM_PwmInputInit(HT_TM_TypeDef* TMx, TM_CaptureInitTypeDef* CapInit)
{
  u8 Filter;
  TM_CHP_Enum OppositePol;
  TM_CHCCS_Enum OppositeSel;
  TM_CH_Enum OppositeChannel;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CH_PWMI(CapInit->Channel));
  Assert_Param(IS_TM_CHP(CapInit->Polarity));
  Assert_Param(IS_TM_CHCCS(CapInit->Selection));
  Assert_Param(IS_TM_CHPSC(CapInit->Prescaler));
  #if (LIBCFG_TM_652XX_V1)
  #else
  Assert_Param(IS_TM_FILTER(CapInit->Filter));
  #endif

  /* Select the Opposite Input Polarity                                                                     */
  if (CapInit->Polarity == TM_CHP_NONINVERTED)
  {
    OppositePol = TM_CHP_INVERTED;
  }
  else
  {
    OppositePol = TM_CHP_NONINVERTED;
  }

  /* Select the Opposite Input                                                                              */
  if (CapInit->Selection == TM_CHCCS_DIRECT)
  {
    OppositeSel = TM_CHCCS_INDIRECT;
  }
  else
  {
    OppositeSel = TM_CHCCS_DIRECT;
  }

  /* Can only be TM_CH_0 or TM_CH_1. CH2/CH3 are not supported since it cannot be the STI source to         */
  /* reset the counter                                                                                      */
  if (CapInit->Channel == TM_CH_0)
  {
    OppositeChannel = TM_CH_1;
  }
  else
  {
    OppositeChannel = TM_CH_0;
  }

  #if (LIBCFG_TM_652XX_V1)
  Filter = FILTER_PROCESS(CapInit);
  #else
  Filter = CapInit->Filter;
  #endif

  /* Capture Channel Configuration                                                                          */
  _TM_CHx_Config(TMx, CapInit->Channel, CapInit->Polarity, CapInit->Selection, Filter);

  /* Set the Input Capture Prescaler value                                                                  */
  TM_CHPSCConfig(TMx, CapInit->Channel, CapInit->Prescaler);

  /* Opposite Channel Configuration                                                                         */
  _TM_CHx_Config(TMx, OppositeChannel, OppositePol, OppositeSel, Filter);

  /* Set the Input Capture Prescaler value                                                                  */
  TM_CHPSCConfig(TMx, OppositeChannel, CapInit->Prescaler);
}

/*********************************************************************************************************//**
 * @brief Fill each TimeBaseInit member with its default value.
 * @param TimeBaseInit: Point to a \ref TM_TimeBaseInitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void TM_TimeBaseStructInit(TM_TimeBaseInitTypeDef* TimeBaseInit)
{
  /* Set the default configuration                                                                          */
  TimeBaseInit->CounterMode = TM_CNT_MODE_UP;
  TimeBaseInit->CounterReload = 0xFFFF;
  TimeBaseInit->Prescaler = 0x0000;
  TimeBaseInit->PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
  #if (LIBCFG_MCTM0)
  TimeBaseInit->RepetitionCounter = 0;
  #endif
}

/*********************************************************************************************************//**
 * @brief Fill each OutInit member with its default value.
 * @param OutInit: Point to a \ref TM_OutputInitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void TM_OutputStructInit(TM_OutputInitTypeDef* OutInit)
{
  /* Set the default configuration                                                                          */
  OutInit->Channel = TM_CH_0;
  OutInit->OutputMode = TM_OM_MATCH_NOCHANGE;
  OutInit->Control = TM_CHCTL_DISABLE;
  OutInit->Polarity = TM_CHP_NONINVERTED;
  #if (LIBCFG_MCTM0)
  OutInit->ControlN = TM_CHCTL_DISABLE;
  OutInit->PolarityN = TM_CHP_NONINVERTED;
  OutInit->IdleState = MCTM_OIS_LOW;
  OutInit->IdleStateN = MCTM_OIS_LOW;
  #endif
  OutInit->Compare = 0x0000;
  OutInit->AsymmetricCompare = 0x0000;
}

/*********************************************************************************************************//**
 * @brief Fill each CapInit member with its default value.
 * @param CapInit: Point to a \ref TM_CaptureInitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void TM_CaptureStructInit(TM_CaptureInitTypeDef* CapInit)
{
  /* Set the default configuration                                                                          */
  CapInit->Channel = TM_CH_0;
  CapInit->Polarity = TM_CHP_NONINVERTED;
  CapInit->Selection = TM_CHCCS_DIRECT;
  CapInit->Prescaler = TM_CHPSC_OFF;
  #if (LIBCFG_TM_652XX_V1)
  CapInit->Fsampling = TM_CHFDIV_1;
  CapInit->Event = TM_CHFEV_OFF;
  #else
  CapInit->Filter = 0x00;
  #endif
}

/*********************************************************************************************************//**
 * @brief Enable or Disable TMx counter.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TM_Cmd(HT_TM_TypeDef* TMx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the TM Counter                                                                                */
    TMx->CTR |= CTR_TME;
  }
  else
  {
    /* Disable the TM Counter                                                                               */
    TMx->CTR &= ~CTR_TME;
  }
}

#if (LIBCFG_TM_NO_ITI == 1)
#else
/*********************************************************************************************************//**
 * @brief Configure external clock mode of the TMx. Used ITIx as the clock source.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Iti: Trigger source.
 *        This parameter can be one of the following values:
 *        @arg TM_TRSEL_ITI0: Internal trigger 0
 *        @arg TM_TRSEL_ITI1: Internal trigger 1
 *        @arg TM_TRSEL_ITI2: Internal trigger 2
 * @retval None
 ************************************************************************************************************/
void TM_ItiExternalClockConfig(HT_TM_TypeDef* TMx, TM_TRSEL_Enum Iti)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_ITI(Iti));

  /* Select the Internal Trigger. Slave mode will be disable in this function                               */
  TM_StiConfig(TMx, Iti);

  /* Select the STIED as external clock source                                                              */
  TMx->MDCFR |= TM_SMSEL_STIED;
}
#endif

/*********************************************************************************************************//**
 * @brief Configure external clock mode of the TMx. Used CHx as the clock source.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Sel: Specify the channel source.
 *        This parameter can be one of the following values:
 *        @arg TM_TRSEL_TI0BED : TI0 both edge detector
 *        @arg TM_TRSEL_TI0S0 : Filtered timer input 0
 *        @arg TM_TRSEL_TI1S1 : Filtered timer input 1
 * @param Pol: Specify the CHx Polarity.
 *        This parameter can be one of the following values:
 *        @arg TM_CHP_NONINVERTED : active high.
 *        @arg TM_CHP_INVERTED    : active low.
 * @param Filter: Specify the filter value.
 *        This parameter must be a value between 0x0 and 0xF.
 * @retval None
 ************************************************************************************************************/
void TM_ChExternalClockConfig(HT_TM_TypeDef* TMx, TM_TRSEL_Enum Sel, TM_CHP_Enum Pol, u8 Filter)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_TRSEL_CH(Sel));
  Assert_Param(IS_TM_CHP(Pol));
  #if (LIBCFG_TM_652XX_V1)
  #else
  Assert_Param(IS_TM_FILTER(Filter));
  #endif

  /* Configure the Timer Input Clock Source                                                                 */
  if (Sel == TM_TRSEL_TI1S1)
  {
    _TM_CHx_Config(TMx, TM_CH_1, Pol, TM_CHCCS_DIRECT, Filter);
  }
  else
  {
    _TM_CHx_Config(TMx, TM_CH_0, Pol, TM_CHCCS_DIRECT, Filter);
  }

  /* Select the external clock source. Slave mode will be disable in this function                          */
  TM_StiConfig(TMx, Sel);

  /* Select the STIED as external clock source                                                              */
  TMx->MDCFR |= TM_SMSEL_STIED;
}

#if 0
/*********************************************************************************************************//**
 * @brief Configure external clock mode of the TMx. Used ETI as the clock source.
 * @param TMx: where TMx is the selected TM from the TM peripheral.
 * @param Psc: The external Trigger Prescaler.
 *        It can be one of the following values:
 *        @arg TM_ETIPSC_OFF : ETI prescaler off
 *        @arg TM_ETIPSC_2   : ETIP frequency divided by 2
 *        @arg TM_ETIPSC_4   : ETIP frequency divided by 4
 *        @arg TM_ETIPSC_8   : ETIP frequency divided by 8
 * @param Pol: The external trigger input polarity.
 *        It can be one of the following values:
 *        @arg TM_ETIPOL_NONINVERTED : Active high level or rising edge
 *        @arg TM_ETIPOL_INVERTED    : Active low level or falling edge
 * @param Filter: Filter for ETI input.
 *        This parameter must be a value between 0x00 and 0x0F
 * @retval None
 ************************************************************************************************************/
void TM_EtiExternalClockConfig(HT_TM_TypeDef* TMx, TM_ETIPSC_Enum Psc, TM_ETIPOL_Enum Pol, u8 Filter)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_ETIPSC(Psc));
  Assert_Param(IS_TM_ETIPOL(Pol));
  Assert_Param(IS_TM_FILTER(Filter));

  /* Configure the ETI Clock source                                                                         */
  TM_EtiConfig(TMx, Psc, Pol, Filter);

  /* Enable the external clock mode                                                                         */
  TMx->TRCFR |= TRCFR_ECME;
}

/*********************************************************************************************************//**
 * @brief Configure external trigger input (ETI) of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripheral.
 * @param Psc: The external Trigger Prescaler.
 *        It can be one of the following values:
 *        @arg TM_ETIPSC_OFF : ETI prescaler off
 *        @arg TM_ETIPSC_2   : ETIP frequency divided by 2
 *        @arg TM_ETIPSC_4   : ETIP frequency divided by 4
 *        @arg TM_ETIPSC_8   : ETIP frequency divided by 8
 * @param Pol: The external trigger input polarity.
 *        It can be one of the following values:
 *        @arg TM_ETIPOL_NONINVERTED : Active high level or rising edge
 *        @arg TM_ETIPOL_INVERTED    : Active low level or falling edge
 * @param Filter: Filter for ETI input.
 *        This parameter must be a value between 0x00 and 0x0F
 * @retval None
 ************************************************************************************************************/
void TM_EtiConfig(HT_TM_TypeDef* TMx, TM_ETIPSC_Enum Psc, TM_ETIPOL_Enum Pol, u8 Filter)
{
  u32 wTrcfr;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_ETIPSC(Psc));
  Assert_Param(IS_TM_ETIPOL(Pol));
  Assert_Param(IS_TM_FILTER(Filter));

  /* Get TRCFR value with cleared ETI configuration bits                                                    */
  wTrcfr = TMx->TRCFR & TRCFR_ETI_CONF_MASK;

  /* Set the prescaler, filter and polarity for ETI input                                                   */
  wTrcfr |= (u32)Psc | Pol | ((u32)Filter << 8);

  /* Write to TMx TRCFR                                                                                     */
  TMx->TRCFR = wTrcfr;
}
#endif

/*********************************************************************************************************//**
 * @brief Configure prescaler of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Psc: Specify the prescaler value.
 * @param PscReloadTime: Specify the TM prescaler reload time.
 *        This parameter can be one of the following values:
 *        @arg TM_PSC_RLD_UPDATE    : The prescaler is loaded at the next update event.
 *        @arg TM_PSC_RLD_IMMEDIATE : The prescaler is loaded immediatly.
 * @retval None
 ************************************************************************************************************/
void TM_PrescalerConfig(HT_TM_TypeDef* TMx, u16 Psc, TM_PSC_RLD_Enum PscReloadTime)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_PSC_RLD(PscReloadTime));

  /* Set the prescaler value                                                                                */
  TMx->PSCR = Psc;

  /* Set the UEVG bit or not                                                                                */
  TMx->EVGR = PscReloadTime;
}

/*********************************************************************************************************//**
 * @brief Configure counter mode of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Mod: Specify the counter mode to be used.
 *        This parameter can be one of the following values:
 *        @arg TM_CNT_MODE_UP   : TM up counting mode.
 *        @arg TM_CNT_MODE_DOWN : TM down counting mode.
 *        @arg TM_CNT_MODE_CA1  : TM center aligned mode 1.
 *        @arg TM_CNT_MODE_CA2  : TM center aligned mode 2.
 *        @arg TM_CNT_MODE_CA3  : TM center aligned mode 3.
 * @retval None
 ************************************************************************************************************/
void TM_CounterModeConfig(HT_TM_TypeDef* TMx, TM_CNT_MODE_Enum Mod)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CNT_MODE(Mod));

  /* Reset the CMSEL and DIR Bits                                                                           */
  TMx->CNTCFR &= CNTCFR_CMSEL_MASK;        /* CNTCFR_DIR is read only when the timer configured as          */
  TMx->CNTCFR &= ~(u32)CNTCFR_DIR;         /* Center-aligned mode. Reset mode first and then reset the      */
                                           /* CNTCFR_DIR bit (separate as two steps).                       */

  /* Set the Counter Mode                                                                                   */
  TMx->CNTCFR |= Mod;
}

/*********************************************************************************************************//**
 * @brief Select the STI source.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Sel: Specify the STI source.
 *        This parameter can be one of the following:
 *        @arg TM_TRSEL_ITI0  : Internal trigger 0.
 *        @arg TM_TRSEL_ITI1  : Internal trigger 1.
 *        @arg TM_TRSEL_ITI2  : Internal trigger 2.
 *        @arg TM_TRSEL_TI0BED : TI0 both edge detector.
 *        @arg TM_TRSEL_TI0S0 : Filtered channel 0 input.
 *        @arg TM_TRSEL_TI1S1 : Filtered channel 1 input.
 *        @arg TM_TRSEL_ETIF  : External trigger input.
 *        @arg TM_TRSEL_UEVG  : Trigger by setting UEVG bit.
 * @retval None
 ************************************************************************************************************/
void TM_StiConfig(HT_TM_TypeDef* TMx, TM_TRSEL_Enum Sel)
{
  u32 wTrcfr;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_TRSEL(Sel));

  /* Disable slave mode                                                                                     */
  TMx->MDCFR &= MDCFR_SMSEL_MASK;

  /* Get the TRCFR value with cleared TRSEL                                                                 */
  wTrcfr = TMx->TRCFR & TRCFR_TRSEL_MASK;

  /* Set the STI source                                                                                     */
  TMx->TRCFR |= wTrcfr | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure encoder interface of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param DecoderMod: Specify the TMx decoder mode.
 *        This parameter can be one of the following values:
 *        @arg TM_SMSEL_DECODER1 : Counter counts on CH0 edge depending on CH1 level.
 *        @arg TM_SMSEL_DECODER2 : Counter counts on CH1 edge depending on CH0 level.
 *        @arg TM_SMSEL_DECODER3 : Counter counts on both CH0 and CH1 edges depending on
 *             the level of the other input.
 * @param CH0P: Specify the CH0 polarity.
 *        This parameter can be one of the following values:
 *        @arg TM_CHP_NONINVERTED : Active high level or rising edge
 *        @arg TM_CHP_INVERTED    : Active low level or falling edge
 * @param CH1P: Specify the CH1 polarity.
 *        This parameter can be one of the following values:
 *        @arg TM_CHP_NONINVERTED : Active high level or rising edge
 *        @arg TM_CHP_INVERTED    : Active low level or falling edge
 * @retval None
 ************************************************************************************************************/
void TM_DecoderConfig(HT_TM_TypeDef* TMx, TM_SMSEL_Enum DecoderMod, TM_CHP_Enum CH0P, TM_CHP_Enum CH1P)
{
  u32 wMdcfr, wCh0Icfr, wCh1Icfr, wChpolr;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_SMSEL_DECODER(DecoderMod));
  Assert_Param(IS_TM_CHP(CH0P));
  Assert_Param(IS_TM_CHP(CH1P));

  /* Get the TMx MDCFR register value                                                                       */
  wMdcfr = TMx->MDCFR;

  /* Get the TMx CH0ICFR & CH1ICFR register value                                                           */
  wCh0Icfr = TMx->CH0ICFR;
  wCh1Icfr = TMx->CH1ICFR;

  /* Get the TMx CHPOLR register value                                                                      */
  wChpolr = TMx->CHPOLR;

  /* Set the decoder mode                                                                                   */
  wMdcfr &= MDCFR_SMSEL_MASK;
  wMdcfr |= DecoderMod;

  /* Select the channel 0 and the channel 1 as input and clear CH0SRC                                       */
  wCh0Icfr &= CHICFR_CHCCS_MASK & (~CH0ICFR_CH0SRC);
  wCh1Icfr &= CHICFR_CHCCS_MASK;
  wCh0Icfr |= TM_CHCCS_DIRECT;
  wCh1Icfr |= TM_CHCCS_DIRECT;

  /* Set the CH0 and the CH1 polarities                                                                     */
  wChpolr &= ~(CHPOLR_CH0P | CHPOLR_CH1P);
  wChpolr |= (CH0P | (CH1P << 2));

  /* Write to TMx MDCFR                                                                                     */
  TMx->MDCFR = wMdcfr;

  /* Write to TMx CH0ICFR & CH1ICFR                                                                         */
  TMx->CH0ICFR = wCh0Icfr;
  TMx->CH1ICFR = wCh1Icfr;

  /* Write to TMx CHPOLR                                                                                    */
  TMx->CHPOLR = wChpolr;
}

/*********************************************************************************************************//**
 * @brief Force the TMx CHnOREF waveform to active or inactive level.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param TM_CH_n: Specify the TM channel.
 *        This parameter can be one of the following values:
 *        @arg TM_CH_0 : TM channel 0
 *        @arg TM_CH_1 : TM channel 1
 *        @arg TM_CH_2 : TM channel 2
 *        @arg TM_CH_3 : TM channel 3
 *        @arg TM_CH_4 : TM channel 4
 *        @arg TM_CH_5 : TM channel 5
 *        @arg TM_CH_6 : TM channel 6
 *        @arg TM_CH_7 : TM channel 7
 * @param ForcedAction: Specify the forced action to be set to the output waveform.
 *        This parameter can be one of the following values:
 *        @arg TM_OM_FORCED_ACTIVE   : Forced active level on CH0OREF
 *        @arg TM_OM_FORCED_INACTIVE : Forced inactive level on CH0OREF.
 * @retval None
 ************************************************************************************************************/
void TM_ForcedOREF(HT_TM_TypeDef* TMx, TM_CH_Enum TM_CH_n, TM_OM_Enum ForcedAction)
{
  vu32* pCHnOCFR = ((vu32*)&TMx->CH0OCFR) + (TM_CH_n * 1);
#if (LIBCFG_PWM_8_CHANNEL)
  if ((TM_CH_n > TM_CH_3) && (TM_CH_n <= TM_CH_7) )
  {
    pCHnOCFR = ((vu32*)&TMx->CH4OCFR) + ((TM_CH_n -4) * 1);
  }
#endif

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CH(TM_CH_n));
  Assert_Param(IS_TM_OM_FORCED(ForcedAction));

  /* Configure The forced output mode                                                                       */
  *pCHnOCFR = (*pCHnOCFR & CHOCFR_CHOM_MASK) | ForcedAction;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the TMx CRR preload function.
 * @param TMx: where TMx is the selected TM from the TM peripheral.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TM_CRRPreloadCmd(HT_TM_TypeDef* TMx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    /* Set the CRR preload control bit                                                                      */
    TMx->CTR |= CTR_CRBE;
  }
  else
  {
    /* Reset the CRR preload control bit                                                                    */
    TMx->CTR &= ~CTR_CRBE;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the TMx CHxCCR preload function.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Channel: Specify the TM channel.
 *        This parameter can be one of the following values:
 *        @arg TM_CH_0 : TM channel 0
 *        @arg TM_CH_1 : TM channel 1
 *        @arg TM_CH_2 : TM channel 2
 *        @arg TM_CH_3 : TM channel 3
 *        @arg TM_CH_4 : TM channel 4
 *        @arg TM_CH_5 : TM channel 5
 *        @arg TM_CH_6 : TM channel 6
 *        @arg TM_CH_7 : TM channel 7
 * @param NewState This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TM_CHCCRPreloadConfig(HT_TM_TypeDef* TMx, TM_CH_Enum Channel, ControlStatus NewState)
{
  vu32 *pOcfr = (vu32*)&TMx->CH0OCFR + Channel;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CH(Channel));
  Assert_Param(IS_CONTROL_STATUS(NewState));
#if (LIBCFG_PWM_8_CHANNEL)
  if ((Channel > TM_CH_3) && (Channel <= TM_CH_7))
  {
    u8 bOffset = Channel - 4;
    pOcfr = (vu32*)&TMx->CH4OCFR + bOffset;
  }
#endif
  /* Enable or disable the channel N CCR preload feature                                                    */
  if (NewState != DISABLE)
  {
    *pOcfr |= CHOCFR_CHPRE;
  }
  else
  {
    *pOcfr &= ~CHOCFR_CHPRE;
  }
}

/*********************************************************************************************************//**
 * @brief Clear or Safeguard the CHxOREF signal when ETI is active.
 * @param TMx: where TMx is the selected TM from the TM peripheral.
 * @param Channel: Specify the TM channel.
 *        This parameter can be one of the following values:
 *        @arg TM_CH_0 : TM channel 0
 *        @arg TM_CH_1 : TM channel 1
 *        @arg TM_CH_2 : TM channel 2
 *        @arg TM_CH_3 : TM channel 3
 * @param NewState This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TM_ClearOREFConfig(HT_TM_TypeDef* TMx, TM_CH_Enum Channel, ControlStatus NewState)
{
  vu32 *pOcfr = (vu32*)&TMx->CH0OCFR + Channel;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CH(Channel));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  /* Enable or Disable the channel N clear Oref at ETI active function                                      */
  if (NewState != DISABLE)
  {
    *pOcfr |= CHOCFR_REFCE;
  }
  else
  {
    *pOcfr &= ~CHOCFR_REFCE;
  }
}

/*********************************************************************************************************//**
 * @brief Configure polarity of the TMx channel N.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Channel: Specify the TM channel.
 *        This parameter can be one of the following values:
 *        @arg TM_CH_0 : TM channel 0
 *        @arg TM_CH_1 : TM channel 1
 *        @arg TM_CH_2 : TM channel 2
 *        @arg TM_CH_3 : TM channel 3
 *        @arg TM_CH_4 : TM channel 4
 *        @arg TM_CH_5 : TM channel 5
 *        @arg TM_CH_6 : TM channel 6
 *        @arg TM_CH_7 : TM channel 7
 * @param Pol: Specify the polarity of channel N.
 *        This parameter can be one of the following values:
 *        @arg TM_CHP_NONINVERTED : active high
 *        @arg TM_CHP_INVERTED    : active low
 * @retval None
 ************************************************************************************************************/
void TM_ChPolarityConfig(HT_TM_TypeDef* TMx, TM_CH_Enum Channel, TM_CHP_Enum Pol)
{
  u32 wChpolr;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CH(Channel));
  Assert_Param(IS_TM_CHP(Pol));

  /* Set or reset the CHx polarity                                                                          */
  wChpolr = TMx->CHPOLR & (~(u32)(0x1 << (Channel << 1)));
  TMx->CHPOLR = wChpolr | (Pol << (Channel << 1));
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the single pulse immediate active function.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Channel: Specify the TM channel.
 *        This parameter can be one of the following values:
 *        @arg TM_CH_0 : TM channel 0
 *        @arg TM_CH_1 : TM channel 1
 *        @arg TM_CH_2 : TM channel 2
 *        @arg TM_CH_3 : TM channel 3
 *        @arg TM_CH_4 : TM channel 4
 *        @arg TM_CH_5 : TM channel 5
 *        @arg TM_CH_6 : TM channel 6
 *        @arg TM_CH_7 : TM channel 7
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 * @note Must configure output mode to PWM1 or PWM2 before invoke this function.
 ************************************************************************************************************/
void TM_ImmActiveConfig(HT_TM_TypeDef* TMx, TM_CH_Enum Channel, ControlStatus NewState)
{
  vu32 *pOcfr = (vu32*)&TMx->CH0OCFR + Channel;

#if (LIBCFG_PWM_8_CHANNEL)
  if ((Channel > TM_CH_3) && (Channel <= TM_CH_7) )
  {
    u8 bOffset = Channel - 4;
    pOcfr = (vu32*)&TMx->CH4OCFR + bOffset;
  }
#endif
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CH(Channel));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  /* Enable or disable the channel N clear CHxOREF at ETI active function                                   */
  if (NewState != DISABLE)
  {
    *pOcfr |= CHOCFR_IMAE;
  }
  else
  {
    *pOcfr &= ~CHOCFR_IMAE;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the TMx channel N.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Channel: Specify the TM channel.
 *        This parameter can be one of the following values:
 *        @arg TM_CH_0 : TM channel 0
 *        @arg TM_CH_1 : TM channel 1
 *        @arg TM_CH_2 : TM channel 2
 *        @arg TM_CH_3 : TM channel 3
 *        @arg TM_CH_4 : TM channel 4
 *        @arg TM_CH_5 : TM channel 5
 *        @arg TM_CH_6 : TM channel 6
 *        @arg TM_CH_7 : TM channel 7
 * @param Control: This parameter can be TM_CHCTL_ENABLE or TM_CHCTL_DISABLE.
 * @retval None
 ************************************************************************************************************/
void TM_ChannelConfig(HT_TM_TypeDef* TMx, TM_CH_Enum Channel, TM_CHCTL_Enum Control)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CH(Channel));
  Assert_Param(IS_TM_CHCTL(Control));

  /* Reset the CHxE Bit                                                                                     */
  TMx->CHCTR &= ~(u32)(0x1 << (Channel << 1));

  /* Set or reset the CHxE Bit                                                                              */
  TMx->CHCTR |= (u32)Control << (Channel << 1);
}

/*********************************************************************************************************//**
 * @brief Configure output mode of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Channel: Specify the TM channel.
 *        This parameter can be one of the following values:
 *        @arg TM_CH_0 : TM channel 0
 *        @arg TM_CH_1 : TM channel 1
 *        @arg TM_CH_2 : TM channel 2
 *        @arg TM_CH_3 : TM channel 3
 *        @arg TM_CH_4 : TM channel 4
 *        @arg TM_CH_5 : TM channel 5
 *        @arg TM_CH_6 : TM channel 6
 *        @arg TM_CH_7 : TM channel 7
 * @param Mod: Specify the TM output mode.
 *        This parameter can be one of the following values:
 *        @arg TM_OM_MATCH_NOCHANGE  : Output dont change on match
 *        @arg TM_OM_MATCH_INACTIVE  : Output inactive on compare match
 *        @arg TM_OM_MATCH_ACTIVE    : Output active on compare match
 *        @arg TM_OM_MATCH_TOGGLE    : Output toggle on compare match
 *        @arg TM_OM_FORCED_INACTIVE : Output forced inactive
 *        @arg TM_OM_FORCED_ACTIVE   : Output forced active
 *        @arg TM_OM_PWM1            : PWM1 mode
 *        @arg TM_OM_PWM2            : PWM2 mode
 *        @arg TM_OM_ASYMMETRIC_PWM1 : Asymmetric PWM1 mode
 *        @arg TM_OM_ASYMMETRIC_PWM2 : Asymmetric PWM2 mode
 * @retval None
 * @note This function disables the selected channel before changing the output mode.
 ************************************************************************************************************/
void TM_OutputModeConfig(HT_TM_TypeDef* TMx, TM_CH_Enum Channel, TM_OM_Enum Mod)
{
  vu32 *pOcfr = (vu32*)&TMx->CH0OCFR + Channel;

#if (LIBCFG_PWM_8_CHANNEL)
  if ((Channel > TM_CH_3) && (Channel <= TM_CH_7) )
  {
    u8 bOffset = Channel - 4;
    pOcfr = (vu32*)&TMx->CH4OCFR + bOffset;
  }
#endif
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CH(Channel));
  Assert_Param(IS_TM_OM(Mod));
#if (LIBCFG_PWM_8_CHANNEL)
  if ((Channel > TM_CH_3) && (Channel <= TM_CH_7) )
  {
    Assert_Param(IS_TM_OM_NOASYM(Mod));
  }
#endif

  /* Disable the channel: Reset the CHxE Bit                                                                */
  TMx->CHCTR &= ~(u32)(0x1 << (Channel << 1));

  /* Selects the TM output mode                                                                             */
  *pOcfr = (*pOcfr & CHOCFR_CHOM_MASK) | Mod;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable update event of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param NewState: This parameter can be ENABLE (default) or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TM_UpdateCmd(HT_TM_TypeDef* TMx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState == DISABLE)
  {
    /* Set the update disable bit                                                                           */
    TMx->CNTCFR |= CNTCFR_UEVDIS;
  }
  else
  {
    /* Reset the update disable bit                                                                         */
    TMx->CNTCFR &= ~CNTCFR_UEVDIS;
  }
}

/*********************************************************************************************************//**
 * @brief Configure UEVG interrupt function of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param NewState: This parameter can be one of the following value:
 *    @arg ENABLE  : Default value. Any of the following events will generate an update event interrupt:
 *                   - Counter overflow/underflow
 *                   - Setting the UEVG bit
 *                   - Update generation through the slave restart mode
 *    @arg DISABLE : Only counter overflow/underflow generations an update event interrupt.
 * @retval None
 ************************************************************************************************************/
void TM_UEVG_IntConfig(HT_TM_TypeDef* TMx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState == DISABLE)
  {
    /* Set the UEVG interrupt disable bit                                                                   */
    TMx->CNTCFR |= CNTCFR_UGDIS;
  }
  else
  {
    /* Reset the UEVG interrupt disable bit                                                                 */
    TMx->CNTCFR &= ~CNTCFR_UGDIS;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable hall sensor interface of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TM_HallInterfaceCmd(HT_TM_TypeDef* TMx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    /* Set the CH0SRC Bit                                                                                   */
    TMx->CH0ICFR |= CH0ICFR_CH0SRC;
  }
  else
  {
    /* Reset the CH0SRC Bit                                                                                 */
    TMx->CH0ICFR &= ~CH0ICFR_CH0SRC;
  }
}

/*********************************************************************************************************//**
 * @brief Select single pulse mode of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TM_SinglePulseModeCmd(HT_TM_TypeDef* TMx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    TMx->MDCFR |= MDCFR_SPMSET;
  }
  else
  {
    TMx->MDCFR &= ~MDCFR_SPMSET;
  }
}

/*********************************************************************************************************//**
 * @brief Select master trigger output source of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Sel: Specify the master trigger output source.
 *        This parameter can be as follow:
 *        @arg TM_MMSEL_RESET   : Send trigger signal when S/W setting UEVG or slave restart
 *        @arg TM_MMSEL_ENABLE  : The counter enable signal is used as trigger output.
 *        @arg TM_MMSEL_UPDATE  : The update event is used as trigger output.
 *        @arg TM_MMSEL_CH0CC   : Channel 0 capture or compare match occurred as trigger output.
 *        @arg TM_MMSEL_CH0OREF : The CH0OREF signal is used as trigger output.
 *        @arg TM_MMSEL_CH1OREF : The CH1OREF signal is used as trigger output.
 *        @arg TM_MMSEL_CH2OREF : The CH2OREF signal is used as trigger output.
 *        @arg TM_MMSEL_CH3OREF : The CH3OREF signal is used as trigger output.
 *        @arg TM_MMSEL_CH4OREF : The CH4OREF signal is used as trigger output.
 *        @arg TM_MMSEL_CH5OREF : The CH5OREF signal is used as trigger output.
 *        @arg TM_MMSEL_CH6OREF : The CH6OREF signal is used as trigger output.
 *        @arg TM_MMSEL_CH7OREF : The CH7OREF signal is used as trigger output.
 * @retval None
 ************************************************************************************************************/
void TM_MMSELConfig(HT_TM_TypeDef* TMx, TM_MMSEL_Enum Sel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_MMSEL(Sel));

  /* Select the MTO source                                                                                  */
  TMx->MDCFR = (TMx->MDCFR & MDCFR_MMSEL_MASK) | Sel;
}

/*********************************************************************************************************//**
 * @brief Select slave mode of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Sel: Specify the timer slave mode.
 *        This parameter can be one of the following values:
 *        @arg TM_SMSEL_RESTART : Slave restart counter mode.
 *        @arg TM_SMSEL_PAUSE   : Slave pause counter mode.
 *        @arg TM_SMSEL_TRIGGER : Slave trigger counter start mode.
 *        @arg TM_SMSEL_STIED   : Used rising edge of STI as prescaler clock source.
 * @retval None
 ************************************************************************************************************/
void TM_SlaveModeConfig(HT_TM_TypeDef* TMx, TM_SMSEL_Enum Sel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_SLAVE_MODE(Sel));

  /* Select the slave mode                                                                                  */
  TMx->MDCFR = (TMx->MDCFR & MDCFR_SMSEL_MASK) | Sel;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the master & slave TMx synchronous function.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TM_TimSyncCmd(HT_TM_TypeDef* TMx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    /* Set the TSE Bit                                                                                      */
    TMx->MDCFR |= MDCFR_TSE;
  }
  else
  {
    /* Reset the TSE Bit                                                                                    */
    TMx->MDCFR &= ~MDCFR_TSE;
  }
}

/*********************************************************************************************************//**
 * @brief Set counter register value of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Counter: Specify the counter register new value.
 * @retval None
 ************************************************************************************************************/
void TM_SetCounter(HT_TM_TypeDef* TMx, u16 Counter)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));

  /* Set the Counter Register value                                                                         */
  TMx->CNTR = Counter;
}

/*********************************************************************************************************//**
 * @brief Set counter reload register value of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Reload: Specify the counter reload register new value.
 * @retval None
 ************************************************************************************************************/
void TM_SetCounterReload(HT_TM_TypeDef* TMx, u16 Reload)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));

  /* Set the counter reload register value                                                                  */
  TMx->CRR = Reload;
}

/*********************************************************************************************************//**
 * @brief Set channel n capture/compare register value of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param TM_CH_n: Specify the TM channel.
 *        This parameter can be one of the following values:
 *        @arg TM_CH_0 : TM channel 0
 *        @arg TM_CH_1 : TM channel 1
 *        @arg TM_CH_2 : TM channel 2
 *        @arg TM_CH_3 : TM channel 3
 *        @arg TM_CH_4 : TM channel 4
 *        @arg TM_CH_5 : TM channel 5
 *        @arg TM_CH_6 : TM channel 6
 *        @arg TM_CH_7 : TM channel 7
 * @param Cmp: Specify the CH0CCR register new value.
 * @retval None
 ************************************************************************************************************/
void TM_SetCaptureCompare(HT_TM_TypeDef* TMx, TM_CH_Enum TM_CH_n, u16 Cmp)
{
  vu32* pCHnCCR = ((vu32*)&TMx->CH0CCR) + (TM_CH_n * 1);
  #if (LIBCFG_PWM_8_CHANNEL)
  if ((TM_CH_n > TM_CH_3) && (TM_CH_n <= TM_CH_7) )
  {
    pCHnCCR = ((vu32*)&TMx->CH4CR) + ((TM_CH_n - 4) * 1);
  }
  #endif
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CH(TM_CH_n));

  /* Set the CHnCCR register new value                                                                      */
  *pCHnCCR = Cmp;
}

/*********************************************************************************************************//**
 * @brief Set channel n asymmetric compare register value of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param TM_CH_n: Specify the TM channel.
 *        This parameter can be one of the following values:
 *        @arg TM_CH_0 : TM channel 0
 *        @arg TM_CH_1 : TM channel 1
 *        @arg TM_CH_2 : TM channel 2
 *        @arg TM_CH_3 : TM channel 3
 * @param Cmp: Specify the CH0ACR register new value.
 * @retval None
 ************************************************************************************************************/
void TM_SetAsymmetricCompare(HT_TM_TypeDef* TMx, TM_CH_Enum TM_CH_n, u16 Cmp)
{
  vu32* pCHnACR = ((vu32*)&TMx->CH0ACR) + (TM_CH_n * 1);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CH(TM_CH_n));

  /* Set the CHnACR register new value                                                                      */
  *pCHnACR = Cmp;
}

/*********************************************************************************************************//**
 * @brief Configure input capture prescaler.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Channel: Specify the TM channel.
 *        This parameter can be one of the following values:
 *        @arg TM_CH_0 : TM channel 0
 *        @arg TM_CH_1 : TM channel 1
 *        @arg TM_CH_2 : TM channel 2
 *        @arg TM_CH_3 : TM channel 3
 * @param Psc: Specify the input capture prescaler new value.
 *        This parameter can be one of the following values:
 *        @arg TM_CHPSC_OFF : No prescaler
 *        @arg TM_CHPSC_2   : Capture is done once every 2 events
 *        @arg TM_CHPSC_4   : Capture is done once every 4 events
 *        @arg TM_CHPSC_8   : Capture is done once every 8 events
 * @retval None
 ************************************************************************************************************/
void TM_CHPSCConfig(HT_TM_TypeDef* TMx, TM_CH_Enum Channel, TM_CHPSC_Enum Psc)
{
  vu32 *pIcfr = (vu32*)&TMx->CH0ICFR + Channel;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CH(Channel));
  Assert_Param(IS_TM_CHPSC(Psc));

  /* Reset the CHxPSC bits                                                                                  */
  *pIcfr &= CHICFR_CHPSC_MASK;

  /* Set the capture input prescaler value                                                                  */
  *pIcfr |= Psc;
}

/*********************************************************************************************************//**
 * @brief Set clock division value of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Div: Specify the clock division value.
 *        This parameter can be one of the following value:
 *        @arg TM_CKDIV_OFF : fDTS = fCLKIN
 *        @arg TM_CKDIV_2   : fDTS = fCLKIN / 2
 *        @arg TM_CKDIV_4   : fDTS = fCLKIN / 4
 *        @arg TM_CKDIV_8   : fDTS = fCLKIN / 8
 * @retval None
 ************************************************************************************************************/
void TM_CKDIVConfig(HT_TM_TypeDef* TMx, TM_CKDIV_Enum Div)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CKDIV(Div));

  /* Reset the CKDIV Bits                                                                                   */
  TMx->CNTCFR &= CNTCFR_CKDIV_MASK;

  /* Set the CKDIV value                                                                                    */
  TMx->CNTCFR |= Div;
}

/*********************************************************************************************************//**
 * @brief Get channel n capture/compare register value of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param TM_CH_n: Specify the TM channel.
 *        This parameter can be one of the following values:
 *        @arg TM_CH_0 : TM channel 0
 *        @arg TM_CH_1 : TM channel 1
 *        @arg TM_CH_2 : TM channel 2
 *        @arg TM_CH_3 : TM channel 3
 * @retval Value of CH0CCR register
 ************************************************************************************************************/
u32 TM_GetCaptureCompare(HT_TM_TypeDef* TMx, TM_CH_Enum TM_CH_n)
{
  vu32* pCHnCCR = ((vu32*)&TMx->CH0CCR) + (TM_CH_n * 1);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CH(TM_CH_n));

  #if (LIBCFG_PWM_8_CHANNEL)
  if ((TM_CH_n > TM_CH_3) && (TM_CH_n <= TM_CH_7))
  {
    pCHnCCR = ((vu32*)&TMx->CH4CR) + ((TM_CH_n - 4) * 1);
  }
  #endif

  /* Get the CHnCCR register value                                                                          */
  return (*pCHnCCR);
}

/*********************************************************************************************************//**
 * @brief Get counter value of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @retval Value of Counter register
 ************************************************************************************************************/
u32 TM_GetCounter(HT_TM_TypeDef* TMx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));

  /* Get the Counter Register value                                                                         */
  return TMx->CNTR;
}

/*********************************************************************************************************//**
 * @brief Get prescaler value of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @retval Value of Prescaler register
 ************************************************************************************************************/
u32 TM_GetPrescaler(HT_TM_TypeDef* TMx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));

  /* Get the Prescaler Register value                                                                       */
  return TMx->PSCR;
}

/*********************************************************************************************************//**
 * @brief Generate TMx events.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param TM_EVENT: Stores the event source.
 *        This parameter can be any combination of following:
 *        @arg TM_EVENT_CH0CC     : Timer Capture/compare 0 event
 *        @arg TM_EVENT_CH1CC     : Timer Capture/compare 1 event
 *        @arg TM_EVENT_CH2CC     : Timer Capture/compare 2 event
 *        @arg TM_EVENT_CH3CC     : Timer Capture/compare 3 event
 *        @arg TM_EVENT_CH4CC     : Timer Compare 4 event
 *        @arg TM_EVENT_CH5CC     : Timer Compare 5 event
 *        @arg TM_EVENT_CH6CC     : Timer Compare 6 event
 *        @arg TM_EVENT_CH7CC     : Timer Compare 7 event
 *        @arg TM_EVENT_UEV       : Timer update event
 *        @arg TM_EVENT_UEV2      : Timer update event 2
 *        @arg TM_EVENT_TEV       : Timer trigger event
 *        @arg TM_EVENT_BRKEV     : Timer break event
 * @retval None
 ************************************************************************************************************/
void TM_GenerateEvent(HT_TM_TypeDef* TMx, u32 TM_EVENT)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_EVENT(TM_EVENT));

  /* Set the event sources                                                                                  */
  TMx->EVGR = TM_EVENT;
}

/*********************************************************************************************************//**
 * @brief Check whether the specified TMx flag has been set.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param TM_FLAG: Specify the flag to be checked.
 *        This parameter can be one of the following values:
 *        @arg TM_FLAG_CH0CC    : TM Capture/compare 0 flag
 *        @arg TM_FLAG_CH1CC    : TM Capture/compare 1 flag
 *        @arg TM_FLAG_CH2CC    : TM Capture/compare 2 flag
 *        @arg TM_FLAG_CH3CC    : TM Capture/compare 3 flag
 *        @arg TM_FLAG_CH4CC    : TM Compare 4 flag
 *        @arg TM_FLAG_CH5CC    : TM Compare 5 flag
 *        @arg TM_FLAG_CH6CC    : TM Compare 6 flag
 *        @arg TM_FLAG_CH7CC    : TM Compare 7 flag
 *        @arg TM_FLAG_CH0OC    : TM channel 0 overcapture flag
 *        @arg TM_FLAG_CH1OC    : TM channel 1 overcapture flag
 *        @arg TM_FLAG_CH2OC    : TM channel 2 overcapture flag
 *        @arg TM_FLAG_CH3OC    : TM channel 3 overcapture flag
 *        @arg TM_FLAG_UEV      : TM update flag
 *        @arg TM_FLAG_UEV2     : TM update 2 flag
 *        @arg TM_FLAG_TEV      : TM trigger flag
 *        @arg TM_FLAG_BRK0     : TM break 0 flag
 *        @arg TM_FLAG_BRK1     : TM break 1 flag
 * @retval The new state of TM_FLAG (SET or RESET).
 ************************************************************************************************************/
FlagStatus TM_GetFlagStatus(HT_TM_TypeDef* TMx, u32 TM_FLAG)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_FLAG(TM_FLAG));

  if ((TMx->INTSR & TM_FLAG) != 0)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Clear flags of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param TM_FLAG: Specify the flag to be cleared.
 *        This parameter can be any combination of the following values:
 *        @arg TM_FLAG_CH0CC    : TM Capture/compare 0 flag
 *        @arg TM_FLAG_CH1CC    : TM Capture/compare 1 flag
 *        @arg TM_FLAG_CH2CC    : TM Capture/compare 2 flag
 *        @arg TM_FLAG_CH3CC    : TM Capture/compare 3 flag
 *        @arg TM_FLAG_CH4CC    : TM Compare 4 flag
 *        @arg TM_FLAG_CH5CC    : TM Compare 5 flag
 *        @arg TM_FLAG_CH6CC    : TM Compare 6 flag
 *        @arg TM_FLAG_CH7CC    : TM Compare 7 flag
 *        @arg TM_FLAG_CH0OC    : TM channel 0 overcapture flag
 *        @arg TM_FLAG_CH1OC    : TM channel 1 overcapture flag
 *        @arg TM_FLAG_CH2OC    : TM channel 2 overcapture flag
 *        @arg TM_FLAG_CH3OC    : TM channel 3 overcapture flag
 *        @arg TM_FLAG_UEV      : TM update flag
 *        @arg TM_FLAG_UEV2     : TM update 2 flag
 *        @arg TM_FLAG_TEV      : TM trigger flag
 *        @arg TM_FLAG_BRK0     : TM break 0 flag
 *        @arg TM_FLAG_BRK1     : TM break 1 flag
 * @retval None
 ************************************************************************************************************/
void TM_ClearFlag(HT_TM_TypeDef* TMx, u32 TM_FLAG)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_FLAG_CLR(TM_FLAG));

  /* Clear the flags                                                                                        */
  TMx->INTSR = ~TM_FLAG;

  /*--------------------------------------------------------------------------------------------------------*/
  /* DSB instruction is added in this function to ensure the write operation which is for clearing interrupt*/
  /* flag is actually completed before exiting ISR. It prevents the NVIC from detecting the interrupt again */
  /* since the write register operation may be pended in the internal write buffer of Cortex-Mx when program*/
  /* has exited interrupt routine. This DSB instruction may be masked if this function is called in the     */
  /* beginning of ISR and there are still some instructions before exiting ISR.                             */
  /*--------------------------------------------------------------------------------------------------------*/
  __DSB();
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified interrupts of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param TM_INT: Specify the TM interrupts sources to be enabled or disabled.
 *        This parameter can be any combination of the following values:
 *        @arg TM_INT_CH0CC     : TM Capture/compare 0 interrupt
 *        @arg TM_INT_CH1CC     : TM Capture/compare 1 interrupt
 *        @arg TM_INT_CH2CC     : TM Capture/compare 2 interrupt
 *        @arg TM_INT_CH3CC     : TM Capture/compare 3 interrupt
 *        @arg TM_INT_CH4CC     : TM Compare 4 interrupt
 *        @arg TM_INT_CH5CC     : TM Compare 5 interrupt
 *        @arg TM_INT_CH6CC     : TM Compare 6 interrupt
 *        @arg TM_INT_CH7CC     : TM Compare 7 interrupt
 *        @arg TM_INT_UEV       : TM update interrupt
 *        @arg TM_INT_UEV2      : TM update 2 interrupt
 *        @arg TM_INT_TEV       : TM trigger interrupt
 *        @arg TM_INT_BRKEV     : TM break interrupt
 *        @arg MCTM_INT_CH0CD   : MCTM Channel 0 Count-Down compare interrupt
 *        @arg MCTM_INT_CH1CD   : MCTM Channel 1 Count-Down compare interrupt
 *        @arg MCTM_INT_CH2CD   : MCTM Channel 2 Count-Down compare interrupt
 *        @arg MCTM_INT_CH3CD   : MCTM Channel 3 Count-Down compare interrupt
 *        @arg TM_INT_VC        : TM Velocity clock trigger interrupt
 *        @arg TM_INT_QC        : TM Quadrature decoder CLKPULSE interrupt
 *        @arg TM_INT_PE        : TM Phase error interrupt
 *        @arg TM_INT_DC        : TM Counter direction change interrupt
 *        @arg MCTM_INT_OVER    : MCTM CNTR Overflow interrupt
 *        @arg MCTM_INT_UNDER   : MCTM CNTR Underflow interrupt
 *        @arg MCTM_INT_RECCDIF : MCTM CCIF or CIDF interrupt flag control by REPR
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TM_IntConfig(HT_TM_TypeDef* TMx, u32 TM_INT, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_INT(TM_INT));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the interrupt sources                                                                         */
    TMx->DICTR |= TM_INT;
  }
  else
  {
    /* Disable the interrupt sources                                                                        */
    TMx->DICTR &= ~TM_INT;
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the TMx interrupt has occurred.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param TM_INT: Specify the TM interrupt source to be checked.
 *        This parameter can be one of the following values:
 *        @arg TM_INT_CH0CC     : TM Capture/compare 0 interrupt
 *        @arg TM_INT_CH1CC     : TM Capture/compare 1 interrupt
 *        @arg TM_INT_CH2CC     : TM Capture/compare 2 interrupt
 *        @arg TM_INT_CH3CC     : TM Capture/compare 3 interrupt
 *        @arg TM_INT_CH4CC     : TM Compare 4 interrupt
 *        @arg TM_INT_CH5CC     : TM Compare 5 interrupt
 *        @arg TM_INT_CH6CC     : TM Compare 6 interrupt
 *        @arg TM_INT_CH7CC     : TM Compare 7 interrupt
 *        @arg TM_INT_UEV       : TM update interrupt
 *        @arg TM_INT_UEV2      : TM update 2 interrupt
 *        @arg TM_INT_TEV       : TM trigger interrupt
 *        @arg TM_INT_BRKEV     : TM break interrupt
 * @retval The new state of the TM_INT(SET or RESET)
 ************************************************************************************************************/
FlagStatus TM_GetIntStatus(HT_TM_TypeDef* TMx, u32 TM_INT)
{
  u32 itstatus, itenable;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_GET_INT(TM_INT));

  itstatus = TMx->INTSR & TM_INT;
  itenable = TMx->DICTR & TM_INT;

  if ((itstatus != 0) && (itenable != 0))
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Clear interrupt pending bits of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param TM_INT: Specify the TM interrupt to be cleared.
 *        This parameter can be any combination of the following values:
 *        @arg TM_INT_CH0CC     : TM Capture/compare 0 interrupt
 *        @arg TM_INT_CH1CC     : TM Capture/compare 1 interrupt
 *        @arg TM_INT_CH2CC     : TM Capture/compare 2 interrupt
 *        @arg TM_INT_CH3CC     : TM Capture/compare 3 interrupt
 *        @arg TM_INT_CH4CC     : TM Compare 4 interrupt
 *        @arg TM_INT_CH5CC     : TM Compare 5 interrupt
 *        @arg TM_INT_CH6CC     : TM Compare 6 interrupt
 *        @arg TM_INT_CH7CC     : TM Compare 7 interrupt
 *        @arg TM_INT_UEV       : TM update interrupt
 *        @arg TM_INT_UEV2      : TM update 2 interrupt
 *        @arg TM_INT_TEV       : TM trigger interrupt
 *        @arg TM_INT_BRKEV     : TM break interrupt
 * @retval None
 ************************************************************************************************************/
void TM_ClearIntPendingBit(HT_TM_TypeDef* TMx, u32 TM_INT)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_INT(TM_INT));

  /* Clear the interrupt pending Bit                                                                        */
  TMx->INTSR = ~TM_INT;

  /*--------------------------------------------------------------------------------------------------------*/
  /* DSB instruction is added in this function to ensure the write operation which is for clearing interrupt*/
  /* flag is actually completed before exiting ISR. It prevents the NVIC from detecting the interrupt again */
  /* since the write register operation may be pended in the internal write buffer of Cortex-Mx when program*/
  /* has exited interrupt routine. This DSB instruction may be masked if this function is called in the     */
  /* beginning of ISR and there are still some instructions before exiting ISR.                             */
  /*--------------------------------------------------------------------------------------------------------*/
  __DSB();
}

/*********************************************************************************************************//**
 * @brief Disable slave mode to clock the prescaler directly with the internal clock.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @retval None
 ************************************************************************************************************/
void TM_InternalClockConfig(HT_TM_TypeDef* TMx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));

  /* Disable slave mode to clock the prescaler directly with the internal clock                             */
  TMx->MDCFR &= MDCFR_SMSEL_MASK;
}

#if (LIBCFG_PDMA)
/*********************************************************************************************************//**
 * @brief Select Channel Capture/Compare PDMA event of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Selection: This parameter can be TM_CHCCDS_CHCCEV or TM_CHCCDS_UEV.
 * @retval None
 ************************************************************************************************************/
void TM_CHCCDSConfig(HT_TM_TypeDef* TMx, TM_CHCCDS_Enum Selection)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_CHCCDS(Selection));

  if (Selection != TM_CHCCDS_CHCCEV)
  {
    TMx->CTR |= CTR_CHCCDS;
  }
  else
  {
    TMx->CTR &= ~CTR_CHCCDS;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified PDMA requests of the TMx.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param TM_PDMA: Specify the TM PDMA requests to be enabled or disabled.
 *        This parameter can be any combination of the following values:
 *        @arg TM_PDMA_CH0CC     : TM Capture/compare 0 PDMA request
 *        @arg TM_PDMA_CH1CC     : TM Capture/compare 1 PDMA request
 *        @arg TM_PDMA_CH2CC     : TM Capture/compare 2 PDMA request
 *        @arg TM_PDMA_CH3CC     : TM Capture/compare 3 PDMA request
 *        @arg TM_PDMA_UEV       : TM update PDMA request
 *        @arg TM_PDMA_UEV2      : TM update 2 PDMA request
 *        @arg TM_PDMA_TEV       : TM trigger PDMA request
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TM_PDMAConfig(HT_TM_TypeDef* TMx, u32 TM_PDMA, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_TM(TMx));
  Assert_Param(IS_TM_PDMA(TM_PDMA));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the PDMA request                                                                              */
    TMx->DICTR |= TM_PDMA;
  }
  else
  {
    /* Disable the PDMA request                                                                             */
    TMx->DICTR &= ~TM_PDMA;
  }
}
#endif
/**
  * @}
  */

/* Private functions ---------------------------------------------------------------------------------------*/
/** @defgroup TM_Private_Functions TM private functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Configure the CHx as input.
 * @param TMx: where TMx is the selected TM from the TM peripherals.
 * @param Ch: Specify the TM Channel.
 *        This parameter can be one of the following values:
 *        @arg TM_CH_0 : TM channel 0
 *        @arg TM_CH_1 : TM channel 1
 *        @arg TM_CH_2 : TM channel 2
 *        @arg TM_CH_3 : TM channel 3
 * @param Pol: The input polarity.
 *        This parameter can be one of the following values:
 *        @arg TM_CHP_NONINVERTED : Active high level or rising edge
 *        @arg TM_CHP_INVERTED    : Active low level or falling edge
 * @param Sel: Specify the input to be used.
 *        This parameter can be one of the following values:
 *        @arg TM_CHCCS_DIRECT   : TM CHxI is mapped on CHx.
 *        @arg TM_CHCCS_INDIRECT : TM CH1I is mapped on CH0 (or CH0I->CH1 or CH2I->CH3 or CH3I->CH2).
 *        @arg TM_CHCCS_TRCED    : TM CHx is mapped on TRC.
 * @param Filter: Specify the input capture filter.
 *        This parameter must be a value between 0x00 and 0x0F.
 * @retval None
 ************************************************************************************************************/
static void _TM_CHx_Config(HT_TM_TypeDef* TMx, TM_CH_Enum Ch, TM_CHP_Enum Pol, TM_CHCCS_Enum Sel, u8 Filter)
{
  vu32* pIcfr = (vu32*)&TMx->CH0ICFR + Ch;
  u32 wIcfr, wChpolr;

  /* Disable the channel N: reset the CHxE bit                                                              */
  TMx->CHCTR &= ~((u32)0x1 << (Ch << 1));

  wIcfr = *pIcfr;
  wChpolr = TMx->CHPOLR;

  /* Select the input and set the filter                                                                    */
  wIcfr &= CHICFR_CHCCS_MASK & CHICFR_CHF_MASK;
  wIcfr |= Sel | Filter;
  *pIcfr = wIcfr;

  /* Select the polarity bit                                                                                */
  wChpolr &= ~((u32)0x1 << (Ch << 1));
  wChpolr |= (u32)Pol << (Ch << 1);
  TMx->CHPOLR = wChpolr;

  /* Set the CHxE Bit                                                                                       */
  TMx->CHCTR |= (u32)0x1 << (Ch << 1);
}
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */
