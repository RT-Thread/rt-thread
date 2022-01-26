/**
  ******************************************************************************
  * @file    tae32f53xx_ll_hrpwm.c
  * @author  MCD Application Team
  * @brief   HRPWM LL module driver
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll.h"


#define DBG_TAG             "HRPWM LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup HRPWM_LL HRPWM LL
  * @brief      HRPWM LL module driver
  * @{
  */

#ifdef LL_HRPWM_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup HRPWM_LL_Private_Functions HRPWM LL Private Functions
  * @brief    HRPWM LL Private Functions
  * @{
  */
static void HRPWM_MasterBase_Config(HRPWM_TypeDef *Instance, HRPWM_TimerBaseCfgTypeDef *pTimeBaseCfg);
static void HRPWM_TimingUnitBase_Config(HRPWM_TypeDef *Instance, uint32_t TimerIdx, HRPWM_TimerBaseCfgTypeDef *pTimeBaseCfg);
static void HRPWM_MasterCompare_Config(HRPWM_TypeDef *Instance, HRPWM_TimerCompareCfgTypeDef *pTimerCompCfg);
static void HRPWM_TimingUnitCompare_Config(HRPWM_TypeDef *Instance, uint32_t TimerIdx,
        HRPWM_TimerCompareCfgTypeDef *pTimerCompCfg);
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup HRPWM_LL_Exported_Functions HRPWM LL Exported Functions
  * @brief    HRPWM LL Exported Functions
  * @{
  */

/** @defgroup HRPWM_LL_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions
@verbatim
 ===============================================================================
              ##### Initialization and Time Base Configuration functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize a HRPWM instance
      (+) De-initialize a HRPWM instance
      (+) Initialize the HRPWM MSP
      (+) De-initialize the HRPWM MSP
      (+) Start the high-resolution unit and configure relevant paramter (start DLL calibration)
      (+) Only Start the high-resolution (start DLL calibration)
      (+) Configure the time base unit of a HRPWM timer
@endverbatim
  * @{
  */

/**
  * @brief  Initialize a HRPWM instance
  * @param  pSync pointer to HRPWM_MasterSyncTypeDef
  * @retval LL status
  */
LL_StatusETypeDef LL_HRPWM_Init(HRPWM_TypeDef *Instance, HRPWM_MasterSyncTypeDef *pMasterSync)
{

    uint32_t hrpwm_mcr;

    /* Init the low level hardware */
    LL_HRPWM_MspInit(Instance);

    /* HRPWM output synchronization configuration (if required) */
    if ((pMasterSync->SyncOptions & HRPWM_SYNCOPTION_MASTER) != (uint32_t)RESET) {
        /* Check parameters */
        assert_param(IS_HRPWM_SYNCOUTPUTSOURCE(pMasterSync->SyncOutputSource));
        assert_param(IS_HRPWM_SYNCOUTPUTPOLARITY(pMasterSync->SyncOutputPolarity));

        /* The synchronization output initialization procedure must be done prior
           to the configuration of the MCU outputs (done within LL_HRPWM_MspInit)
        */

        hrpwm_mcr = Instance->Master.MCR;

        /* Set the event to be sent on the synchronization output */
        hrpwm_mcr &= ~(HRPWM_MCR_SYNCOUT_SRC);
        hrpwm_mcr |= (pMasterSync->SyncOutputSource & HRPWM_MCR_SYNCOUT_SRC);

        /* Set the polarity of the synchronization output */
        hrpwm_mcr &= ~(HRPWM_MCR_SYNCOUT_POL);
        hrpwm_mcr |= (pMasterSync->SyncOutputPolarity & HRPWM_MCR_SYNCOUT_POL);

        /* Set the polarity of the synchronization output */
        hrpwm_mcr &= ~(HRPWM_MCR_SYNCOUT_EN);
        hrpwm_mcr |= (pMasterSync->SyncOutputEnable & HRPWM_MCR_SYNCOUT_EN);

        /* Update the HRPWM registers */
        Instance->Master.MCR = hrpwm_mcr;
    }

    /* HRPWM input synchronization configuration (if required)  MultiplePWM*/
    if ((pMasterSync->SyncOptions & HRPWM_SYNCOPTION_SLAVE) != (uint32_t)RESET) {
        /* Check parameters */
        assert_param(IS_HRPWM_SYNINPUTSOURCE(pMasterSync->SyncInputSource));

        hrpwm_mcr = Instance->Master.MCR;

        /* Set the synchronization input */
        hrpwm_mcr &= ~(HRPWM_MCR_SYNCIN_EN | HRPWM_MCR_SYNCIN_SRC);
        hrpwm_mcr |= (pMasterSync->SyncInputSource & (HRPWM_MCR_SYNCIN_EN | HRPWM_MCR_SYNCIN_SRC));

        /* Update the HRPWM registers */
        Instance->Master.MCR = hrpwm_mcr;
    }


    return LL_OK;
}

/**
  * @brief  De-initialize a HRPWM instance
  * @param  hhrpwm pointer to LL HRPWM handle
  * @retval LL status
  */
LL_StatusETypeDef LL_HRPWM_DeInit(HRPWM_TypeDef *Instance)
{
    /*stop all counter and output*/
    __LL_HRPWM_ALL_TIMER_DISABLE(Instance);
    __LL_HRPWM_OUTPUT_STOP(HRPWM_OUTPUT_ODIS0A | HRPWM_OUTPUT_ODIS0B |
                           HRPWM_OUTPUT_ODIS1A | HRPWM_OUTPUT_ODIS1B |
                           HRPWM_OUTPUT_ODIS2A | HRPWM_OUTPUT_ODIS2B |
                           HRPWM_OUTPUT_ODIS3A | HRPWM_OUTPUT_ODIS3B |
                           HRPWM_OUTPUT_ODIS4A | HRPWM_OUTPUT_ODIS4B |
                           HRPWM_OUTPUT_ODIS5A | HRPWM_OUTPUT_ODIS5B
                          );
    /* DeInit the low level hardware */
    LL_HRPWM_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  MSP initialization for a HRPWM instance
  * @retval None
  */
__WEAK void LL_HRPWM_MspInit(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_MspInit could be implemented in the user file
     */
}

/**
  * @brief  MSP de-initialization of a HRPWM instance
  * @retval None
  */
__WEAK void LL_HRPWM_MspDeInit(HRPWM_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_HRPWM_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup HRPWM_LL_Exported_Functions_Group2 HRPWM Config Functions
  * @brief    HRPWM Config Functions
  * @{
  */

/**
  * @brief  Start the DLL configuration
  * @param  CalibrationRate DLL calibration period
  *                    This parameter can be one of the following values:
  *                    @arg HRPWM_DLLCR_DLLGCP
  * @retval LL status
  * @note LL_HRPWM_DLLCalibration function, just before exiting the function.
  */
LL_StatusETypeDef LL_HRPWM_DLLStartConfig(HRPWM_TypeDef *Instance, HRPWM_DLLCfgTypedef *DLLConfig)
{
    uint32_t temp_dllcr;
    /* Check the parameters */
    assert_param(IS_HRPWM_DLLGCP(DLLConfig->CurrentSel));

    temp_dllcr = Instance->Common.DLLCR;

    /*config dll paramter*/
    temp_dllcr &= ~(HRPWM_DLLCR_DLLGCP | HRPWM_DLLCR_DLLTHRES1 | HRPWM_DLLCR_DLLTHRES0);
    temp_dllcr |= (DLLConfig->CurrentSel & HRPWM_DLLCR_DLLGCP) |
                  ((DLLConfig->ClockDelayThres0 << 11U) & HRPWM_DLLCR_DLLTHRES0) |
                  ((DLLConfig->ClockDelayThres1 << 6U) & HRPWM_DLLCR_DLLTHRES1);

    /*enable dll and start*/
    temp_dllcr |= (HRPWM_DLLCR_DLLEN | HRPWM_DLLCR_DLLSTART);

    /*configuration current*/
    Instance->Common.DLLCR = temp_dllcr;

    return LL_OK;
}

/**
  * @brief  Start the DLL
  * @retval LL status
  * @note  Only enable and start DLL, do not do other related parameter configuration, use the default value.
  */
LL_StatusETypeDef LL_HRPWM_DLLStart(HRPWM_TypeDef *Instance)
{
    /*enable dll and start*/
    Instance->Common.DLLCR |= (HRPWM_DLLCR_DLLEN | HRPWM_DLLCR_DLLSTART);
    /*Start 20us after DLL is started, wait for 1ms to stabilize*/
    return LL_OK;
}

/**
  * @brief  Configure the time base unit of a timer
  * @param  hhrpwm pointer to LL HRPWM handle
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_MASTER for master timer
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @param  pTimeBaseCfg pointer to the time base configuration structure
  * @note This function must be called prior starting the timer
  * @note   The time-base unit initialization parameters specify:
  *           The timer counter operating mode (continuous, one shot),
  *           The timer clock prescaler,
  *           The timer period,
  *           The timer repetition counter.
  * @retval LL status
  */
LL_StatusETypeDef LL_HRPWM_TimerBaseConfig(HRPWM_TypeDef *Instance, uint32_t TimerIdx, HRPWM_TimerBaseCfgTypeDef *pTimeBaseCfg)
{
    /* Check the parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));
    assert_param(IS_HRPWM_SYNCSTART(pTimeBaseCfg->StartOnSync));
    assert_param(IS_HRPWM_SYNCRESET(pTimeBaseCfg->ResetOnSync));
    assert_param(IS_HRPWM_PRESCALERRATIO(pTimeBaseCfg->PrescalerRatio));
    assert_param(IS_HRPWM_MODE(pTimeBaseCfg->Mode));

    if (TimerIdx == HRPWM_INDEX_MASTER) {
        assert_param(IS_HRPWM_MASTER_IT(pTimeBaseCfg->InterruptRequests));
        /* Configure master timer time base unit */
        HRPWM_MasterBase_Config(Instance, pTimeBaseCfg);
    } else {
        /* Check parameters */
        assert_param(IS_HRPWM_TIMER_IT(pTimeBaseCfg->InterruptRequests));
        assert_param(IS_HRPWM_RST_EVENT(pTimeBaseCfg->ResetTrigger));
        assert_param(IS_HRPWM_RESYNCUPDATE(pTimeBaseCfg->ReSyncUpdate));
        /* Configure timing unit time base unit */
        HRPWM_TimingUnitBase_Config(Instance, TimerIdx, pTimeBaseCfg);
    }

    return LL_OK;
}

/**
  * @brief  Configure the general behavior of a timer operating in waveform mode
  * @param  hhrpwm pointer to LL HRPWM handle
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_MASTER for master timer
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @param  TimeBaseCfg pointer to the time base configuration structure
  * @note This function must be called prior starting the timer
  * @note   The time-base unit initialization parameters specify:
  *           The timer counter operating mode (continuous, one shot),
  *           The timer clock prescaler,
  *           The timer period,
  *           The timer repetition counter.
  * @retval LL status
  */
LL_StatusETypeDef LL_HRPWM_TimerCompareConfig(HRPWM_TypeDef *Instance, uint32_t TimerIdx,
        HRPWM_TimerCompareCfgTypeDef *pTimerCompCfg)
{
    /* Check the parameters, Relevant for all HRPWM timers, including the master*/
    assert_param(IS_HRPWM_INDEX(TimerIdx));
    assert_param(IS_HRPWM_PRELOAD(pTimerCompCfg->PreloadEnable));


    if (TimerIdx == HRPWM_INDEX_MASTER) {
        /* Configure master timer time base unit */
        HRPWM_MasterCompare_Config(Instance, pTimerCompCfg);
    } else {
        assert_param(IS_HRPWM_UPDATETRIGGER(pTimerCompCfg->UpdateTrigger));
        /* Configure timing unit time base unit */
        HRPWM_TimingUnitCompare_Config(Instance, TimerIdx, pTimerCompCfg);
    }

    return LL_OK;
}
/**
  * @}
  */


/** @defgroup HRPWM_LL_Exported_Functions_Group3 HRPWM Simple time base mode functions
 *  @brief    HRPWM Simple time base mode functions
@verbatim
 ===============================================================================
              ##### Simple time base mode functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Start simple time base counter
      (+) Stop simple time base counter
      -@-  When a HRPWM timer operates in simple time base mode, the timer
           counter counts from 0 to the period value.
@endverbatim
  * @{
  */

/**
  * @brief  Start the counter of a timer operating in simple time base mode.
  * @param  hhrpwm pointer to HAL HRPWM handle
  * @param  TimerIdx Timer index.
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_MASTER  for master timer
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @retval HAL status
  */
LL_StatusETypeDef LL_HRPWM_StartCounter(uint32_t TimerIdx)
{
    /* Check the parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));

    /* Enable the timer counter */
    __LL_HRPWM_TIMER_ENABLE(TimerIdx);

    return LL_OK;
}

/**
  * @brief  Stop the counter of a timer operating in simple time base mode.
  * @param  hhrpwm pointer to HAL HRPWM handle
  * @param  TimerIdx Timer index.
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_MASTER  for master timer
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @retval HAL status
  */
LL_StatusETypeDef LL_HRPWM_StopCounter(uint32_t TimerIdx)
{
    /* Check the parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));

    /* Disable the timer counter */
    __LL_HRPWM_TIMER_DISABLE(TimerIdx);

    return LL_OK;
}
/**
  * @}
  */


/** @defgroup HRPWM_LL_Exported_Functions_Group4 HRPWM Simple PWM output mode functions
 *  @brief    HRPWM Simple PWM output functions
@verbatim
 ===============================================================================
              ##### Simple PWM output functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the contrl refister - rollover mode
      (+) Configure the Dual Channel Dac behavior
      (+) Configure updown counter rollover mode
       -@- When a HRPWM timer operates in simple output compare mode
           the output level is set to a programmable value when a match
           is found between the compare register and the counter.
           Compare unit A is automatically associated to output A
           Compare unit B is automatically associated to output B
@endverbatim
  * @{
  */

/**
  * @brief  Configure the Dual Channel Dac behavior and updown count rollover mode
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @param  pTimerRollOverCfg pointer to the timer RollOver configuration structure
  * @note When the timer operates in waveform mode, all the features supported by
  *       the HRPWM are available without any limitation.
  * @retval LL status
  * @note This function must be called before starting the timer
  */
LL_StatusETypeDef LL_HRPWM_TimerUintRollOverContrl(HRPWM_TypeDef *Instance, uint32_t TimerIdx,
        HRPWM_TimerRollOverCfgTypeDef *pTimerRollOverCfg)
{
    if (TimerIdx == HRPWM_INDEX_MASTER) {
        return LL_ERROR;
    }

    uint32_t hrpwm_cr1;
    /* Check the parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));
    assert_param(IS_HRPWM_ROLLOVERMODE(pTimerRollOverCfg->RollOverMode));
    assert_param(IS_HRPWM_OUTPUTROLLOVERMODE(pTimerRollOverCfg->OutputRollOverMode));
    assert_param(IS_HRPWM_ADCROLLOVERMODE(pTimerRollOverCfg->AdcRollOverMode));
    assert_param(IS_HRPWM_FLTROLLOVERMODE(pTimerRollOverCfg->FaultRollOverMode));
    assert_param(IS_HRPWM_EVTROLLOVERMODE(pTimerRollOverCfg->EeventRollOverMode));

    /* Configure timing unit (Timer 0 to Timer 5) */
    hrpwm_cr1 = Instance->PWM[TimerIdx].CR1;

    if (pTimerRollOverCfg->UpDownMode == HRPWM_CR1_UDM) {
        /* Set the UpDown counting Mode */
        hrpwm_cr1 &= ~(HRPWM_CR1_UDM | HRPWM_CR1_ROM | HRPWM_CR1_OUTROM | HRPWM_CR1_ADROM | HRPWM_CR1_FLTROM |
                       HRPWM_CR1_EEVROM);
        hrpwm_cr1 |= ((pTimerRollOverCfg->OutputRollOverMode & HRPWM_CR1_OUTROM) |
                      (pTimerRollOverCfg->UpDownMode & HRPWM_CR1_UDM) |
                      (pTimerRollOverCfg->RollOverMode & HRPWM_CR1_ROM) |
                      (pTimerRollOverCfg->AdcRollOverMode & HRPWM_CR1_ADROM) |
                      (pTimerRollOverCfg->FaultRollOverMode & HRPWM_CR1_FLTROM) |
                      (pTimerRollOverCfg->EeventRollOverMode & HRPWM_CR1_EEVROM));
    }

    /* Update the HRPWM registers */
    Instance->PWM[TimerIdx].CR1 |= hrpwm_cr1;

    return LL_OK;
}

/**
  * @brief  Configure the Dual Channel Dac behavior of a timer operating in waveform mode
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @param  pTimerDacCfg pointer to the timer DualChannel Dac configuration structure
  * @note When the timer operates in waveform mode, all the features supported by
  *       the HRPWM are available without any limitation.
  * @retval LL status
  * @note This function must be called before starting the timer
  */
LL_StatusETypeDef LL_HRPWM_TimerDualChannelDacConfig(HRPWM_TypeDef *Instance, uint32_t TimerIdx,
        HRPWM_TimerDaulDacCfgTypeDef *pTimerDacCfg)
{
    if (TimerIdx == HRPWM_INDEX_MASTER) {
        return LL_ERROR;
    }

    uint32_t hrpwm_cr1;
    /* Check the parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));
    assert_param(IS_HRPWM_DUALDAC_RESET(pTimerDacCfg->DualChannelDacReset));
    assert_param(IS_HRPWM_DUALDAC_STEP(pTimerDacCfg->DualChannelDacStep));
    assert_param(IS_HRPWM_DUALDAC_ENABLE(pTimerDacCfg->DualChannelDacEnable));


    /* Configure timing unit (Timer 0 to Timer 5) */
    hrpwm_cr1 = Instance->PWM[TimerIdx].CR1;

    if (pTimerDacCfg->DualChannelDacEnable == HRPWM_DAC_DCDE_ENABLE) {
        /* Set the DualChannel DAC Reset trigger : requires DCDE enabled */
        hrpwm_cr1 &= ~(HRPWM_CR1_DCDR);
        hrpwm_cr1 |= pTimerDacCfg->DualChannelDacReset;

        /* Set the DualChannel DAC Step trigger : requires DCDE enabled */
        hrpwm_cr1 &= ~(HRPWM_CR1_DCDS);
        hrpwm_cr1 |= pTimerDacCfg->DualChannelDacStep;

        /* Enable the DualChannel DAC trigger */
        hrpwm_cr1 &= ~(HRPWM_CR1_DCDE);
        hrpwm_cr1 |= pTimerDacCfg->DualChannelDacEnable;
    }

    /* Update the HRPWM registers */
    Instance->PWM[TimerIdx].CR1  |= hrpwm_cr1;

    return LL_OK;
}

/**
  * @brief  Configure timing RollOver Mode (Timer 0 to Timer 5)
  * @param  TimerIdx Timer index
  * @param  pRollOverMode: a combination of the timer RollOver Mode configuration
  *         @arg HRPWM_Timer_RollOver_Mode relevant paramter
  *         @arg HRPWM_Timer_Output_RollOver_Mode relevant paramter
  *         @arg HRPWM_Timer_ADTrig_RollOver_Mode relevant paramter
  *         @arg HRPWM_Timer_Event_RollOver_Mode relevant paramter
  *         @arg HRPWM_Timer_Fault_RollOver_Mode relevant paramter
  *         @arg HRPWM_Timer_UpDown_Mode relevant paramter
  *         eg: HRPWM_FLTROM_ZERO | HRPWM_ADROM_BOTH
  *         Rollover can be configured in several modes or together, Only valid in updowm counting mode
  * @retval None
  */
LL_StatusETypeDef  LL_HRPWM_TimerRollOverMode(HRPWM_TypeDef *Instance, uint32_t TimerIdx, uint32_t pRollOverMode)
{
    if (TimerIdx == HRPWM_INDEX_MASTER) {
        return LL_ERROR;
    }

    uint32_t hrpwm_cr1;

    /* Configure timing unit (Timer 0 to Timer 5) */
    hrpwm_cr1 = Instance->PWM[TimerIdx].CR1;

    /*The following modes are only valid in updown counting mode, so first determine if they are in updown counting mode*/
    if (((hrpwm_cr1 & HRPWM_CR1_UDM) != 0U) || ((pRollOverMode & HRPWM_CR1_UDM) != 0U)) {
        /* xxROM bitfield must be reset before programming a new value */
        hrpwm_cr1 &= ~(HRPWM_CR1_ROM | HRPWM_CR1_OUTROM | HRPWM_CR1_ADROM | HRPWM_CR1_FLTROM | HRPWM_CR1_EEVROM);

        /* Update the HRPWM TIMER CR1 register , start updown counter mode*/
        hrpwm_cr1 |= (pRollOverMode & (HRPWM_CR1_ROM | HRPWM_CR1_OUTROM | HRPWM_CR1_ADROM | HRPWM_CR1_FLTROM | HRPWM_CR1_EEVROM)) |
                     HRPWM_CR1_UDM;

        Instance->PWM[TimerIdx].CR1 |= hrpwm_cr1;
    }

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup HRPWM_LL_Exported_Functions_Group5 HRPWM Configuration functions
 *  @brief    HRPWM Configuration functions
@verbatim
 ===============================================================================
              ##### HRPWM configuration functions #####
 ===============================================================================
    [..]  This section provides functions allowing to configure the HRPWM
          resources shared by all the HRPWM timers operating in waveform mode:
      (+) Configure a fault inputs conditioning
      (+) Configure the faults blanking
      (+) Configure the faults counter
      (+) Configure the faults counter Reset
      (+) Configure an ADC trigger
      (+) Configure an output level & polarity
      (+) Configure dead-time value
      (+) Configure chopper output & freq\duty
      (+) Configure an external event conditioning
      (+) Configure the external events A conditioning
      (+) Configure the external events A filter windows and latch
@endverbatim
  * @{
  */

/**
  * @brief  Configure the conditioning of fault input
  * @param  Fault fault input to configure
  *                    This parameter can be one of the following values:
  *                    @arg HRPWM_FAULT_0: Fault input 0
  *                    @arg HRPWM_FAULT_1: Fault input 1
  *                    @arg HRPWM_FAULT_2: Fault input 2
  *                    @arg HRPWM_FAULT_3: Fault input 3
  *                    @arg HRPWM_FAULT_4: Fault input 4
  *                    @arg HRPWM_FAULT_5: Fault input 5
  * @param  pFaultCfg pointer to the fault conditioning configuration structure
  * @param  pFaultBlkCfg pointer to the fault blanking conditioning configuration structure
  * @note This function must be called before starting the timer and before
  *       enabling faults inputs
  * @retval LL status
  */
LL_StatusETypeDef LL_HRPWM_FaultConfig(HRPWM_TypeDef *Instance, uint32_t Fault,
                                       HRPWM_FaultCfgTypeDef *pFaultCfg,
                                       HRPWM_FaultBlankingCfgTypeDef *pFaultBlkCfg)
{
    uint32_t hrpwm_fltinr0;
    uint32_t hrpwm_fltinr1;
    uint32_t hrpwm_fltinr2;
    uint32_t hrpwm_fltinr3;

    /* Check parameters */
    assert_param(IS_HRPWM_FAULT(Fault));
    assert_param(IS_HRPWM_FAULT_IT(pFaultCfg->InterruptEn));
    assert_param(IS_HRPWM_FAULTSOURCE(pFaultCfg->Source));
    assert_param(IS_HRPWM_FAULTPOLARITY(pFaultCfg->Polarity));
    assert_param(IS_HRPWM_FAULTFILTER(pFaultCfg->Filter));
    assert_param(IS_HRPWM_FAULTSAMPCLK(pFaultCfg->SampClockDiv));
    assert_param(IS_HRPWM_FAULTBLKEN(pFaultBlkCfg->BlankingEnable));
    assert_param(IS_HRPWM_FAULTBLKSRC(pFaultBlkCfg->BlankingSource));
    assert_param(IS_HRPWM_FAULTRSTMODE(pFaultBlkCfg->ResetMode));


    /* Configure fault channel */
    hrpwm_fltinr0 = Instance->Common.FLTINR0;
    hrpwm_fltinr1 = Instance->Common.FLTINR1;
    hrpwm_fltinr2 = Instance->Common.FLTINR2;
    hrpwm_fltinr3 = Instance->Common.FLTINR3;

    switch (Fault) {
        case HRPWM_FAULT_0: {
            /*clear relevant register bit */
            hrpwm_fltinr0 &= ~(HRPWM_FLTINR0_FLT0SRC | HRPWM_FLTINR0_FLT0P | HRPWM_FLTINR0_FLT0E);
            /*Configure fault enable */
            hrpwm_fltinr0 |= (pFaultCfg->Enable & HRPWM_FLTINR0_FLT0E);
            /*Configure fault polarity */
            hrpwm_fltinr0 |= (pFaultCfg->Polarity & HRPWM_FLTINR0_FLT0P);
            /*Configure fault source */
            hrpwm_fltinr0 |= (pFaultCfg->Source & HRPWM_FLTINR0_FLT0SRC);
            /*Configure fault filter counter */
            hrpwm_fltinr1 &= ~(HRPWM_FLTINR1_FLT0F);
            hrpwm_fltinr1 |= (pFaultCfg->Filter & HRPWM_FLTINR1_FLT0F);
            /*Configure fault blanking function */
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT0BLKE | HRPWM_FLTINR2_FLT0BLKS | HRPWM_FLTINR2_FLT0RSTM);
            hrpwm_fltinr2 |= (pFaultBlkCfg->BlankingEnable & HRPWM_FLTINR2_FLT0BLKE) |
                             (pFaultBlkCfg->BlankingSource & HRPWM_FLTINR2_FLT0BLKS) |
                             (pFaultBlkCfg->ResetMode & HRPWM_FLTINR2_FLT0RSTM);
            /*Configure fault count the number of edges */
            hrpwm_fltinr3 &= ~(HRPWM_FLTINR3_FLT0CNT);
            hrpwm_fltinr3 |= (pFaultBlkCfg->Threshold & HRPWM_FLTINR3_FLT0CNT);

            /*enable interrupt*/
            SET_BIT(Instance->Common.IER, (pFaultCfg->InterruptEn & HRPWM_IT_FLT0));
        }
        break;

        case HRPWM_FAULT_1: {
            /*clear relevant register bit */
            hrpwm_fltinr0 &= ~(HRPWM_FLTINR0_FLT1SRC | HRPWM_FLTINR0_FLT1P | HRPWM_FLTINR0_FLT1E);
            /*Configure fault enable */
            hrpwm_fltinr0 |= ((pFaultCfg->Enable << 4U) & HRPWM_FLTINR0_FLT1E);
            /*Configure fault polarity */
            hrpwm_fltinr0 |= ((pFaultCfg->Polarity << 4U) & HRPWM_FLTINR0_FLT1P);
            /*Configure fault source */
            hrpwm_fltinr0 |= ((pFaultCfg->Source << 4U) & HRPWM_FLTINR0_FLT1SRC);
            /*Configure fault filter counter */
            hrpwm_fltinr1 &= ~(HRPWM_FLTINR1_FLT1F);
            hrpwm_fltinr1 |= ((pFaultCfg->Filter << 4U) & HRPWM_FLTINR1_FLT1F);
            /*Configure fault blanking function */
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT1BLKE | HRPWM_FLTINR2_FLT1BLKS | HRPWM_FLTINR2_FLT1RSTM);
            hrpwm_fltinr2 |= ((pFaultBlkCfg->BlankingEnable << 4U) & HRPWM_FLTINR2_FLT1BLKE) |
                             ((pFaultBlkCfg->BlankingSource << 4U) & HRPWM_FLTINR2_FLT1BLKS) |
                             ((pFaultBlkCfg->ResetMode << 4U) & HRPWM_FLTINR2_FLT1RSTM);
            /*Configure fault count the number of edges */
            hrpwm_fltinr3 &= ~(HRPWM_FLTINR3_FLT1CNT);
            hrpwm_fltinr3 |= (pFaultBlkCfg->Threshold & HRPWM_FLTINR3_FLT1CNT);

            /*enable interrupt*/
            SET_BIT(Instance->Common.IER, (pFaultCfg->InterruptEn & HRPWM_IT_FLT1));
        }
        break;

        case HRPWM_FAULT_2: {
            /*clear relevant register bit */
            hrpwm_fltinr0 &= ~(HRPWM_FLTINR0_FLT2SRC | HRPWM_FLTINR0_FLT2P | HRPWM_FLTINR0_FLT2E);
            /*Configure fault enable */
            hrpwm_fltinr0 |= ((pFaultCfg->Enable << 8U) & HRPWM_FLTINR0_FLT2E);
            /*Configure fault polarity */
            hrpwm_fltinr0 |= ((pFaultCfg->Polarity << 8U) & HRPWM_FLTINR0_FLT2P);
            /*Configure fault source */
            hrpwm_fltinr0 |= ((pFaultCfg->Source << 8U) & HRPWM_FLTINR0_FLT2SRC);
            /*Configure fault filter counter */
            hrpwm_fltinr1 &= ~(HRPWM_FLTINR1_FLT2F);
            hrpwm_fltinr1 |= ((pFaultCfg->Filter << 8U) & HRPWM_FLTINR1_FLT2F);
            /*Configure fault blanking function */
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT2BLKE | HRPWM_FLTINR2_FLT2BLKS | HRPWM_FLTINR2_FLT2RSTM);
            hrpwm_fltinr2 |= ((pFaultBlkCfg->BlankingEnable << 8U) & HRPWM_FLTINR2_FLT2BLKE) |
                             ((pFaultBlkCfg->BlankingSource << 8U) & HRPWM_FLTINR2_FLT2BLKS) |
                             ((pFaultBlkCfg->ResetMode << 8U) & HRPWM_FLTINR2_FLT2RSTM);
            /*Configure fault count the number of edges */
            hrpwm_fltinr3 &= ~(HRPWM_FLTINR3_FLT2CNT);
            hrpwm_fltinr3 |= (pFaultBlkCfg->Threshold & HRPWM_FLTINR3_FLT2CNT);

            /*enable interrupt*/
            SET_BIT(Instance->Common.IER, (pFaultCfg->InterruptEn & HRPWM_IT_FLT2));
        }
        break;

        case HRPWM_FAULT_3: {
            /*clear relevant register bit */
            hrpwm_fltinr0 &= ~(HRPWM_FLTINR0_FLT3SRC | HRPWM_FLTINR0_FLT3P | HRPWM_FLTINR0_FLT3E);
            /*Configure fault enable */
            hrpwm_fltinr0 |= ((pFaultCfg->Enable << 12U) & HRPWM_FLTINR0_FLT3E);
            /*Configure fault polarity */
            hrpwm_fltinr0 |= ((pFaultCfg->Polarity << 12U) & HRPWM_FLTINR0_FLT3P);
            /*Configure fault source */
            hrpwm_fltinr0 |= ((pFaultCfg->Source << 12U) & HRPWM_FLTINR0_FLT3SRC);
            /*Configure fault filter counter */
            hrpwm_fltinr1 &= ~(HRPWM_FLTINR1_FLT3F);
            hrpwm_fltinr1 |= ((pFaultCfg->Filter << 12U) & HRPWM_FLTINR1_FLT3F);
            /*Configure fault blanking function */
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT3BLKE | HRPWM_FLTINR2_FLT3BLKS | HRPWM_FLTINR2_FLT3RSTM);
            hrpwm_fltinr2 |= ((pFaultBlkCfg->BlankingEnable << 12U) & HRPWM_FLTINR2_FLT3BLKE) |
                             ((pFaultBlkCfg->BlankingSource << 12U) & HRPWM_FLTINR2_FLT3BLKS) |
                             ((pFaultBlkCfg->ResetMode << 12U) & HRPWM_FLTINR2_FLT3RSTM);
            /*Configure fault count the number of edges */
            hrpwm_fltinr3 &= ~(HRPWM_FLTINR3_FLT3CNT);
            hrpwm_fltinr3 |= (pFaultBlkCfg->Threshold & HRPWM_FLTINR3_FLT3CNT);

            /*enable interrupt*/
            SET_BIT(Instance->Common.IER, (pFaultCfg->InterruptEn & HRPWM_IT_FLT3));
        }
        break;

        case HRPWM_FAULT_4: {
            /*clear relevant register bit */
            hrpwm_fltinr0 &= ~(HRPWM_FLTINR0_FLT4SRC | HRPWM_FLTINR0_FLT4P | HRPWM_FLTINR0_FLT4E);
            /*Configure fault enable */
            hrpwm_fltinr0 |= ((pFaultCfg->Enable << 16U) & HRPWM_FLTINR0_FLT4E);
            /*Configure fault polarity */
            hrpwm_fltinr0 |= ((pFaultCfg->Polarity << 16U) & HRPWM_FLTINR0_FLT4P);
            /*Configure fault source */
            hrpwm_fltinr0 |= ((pFaultCfg->Source << 16U) & HRPWM_FLTINR0_FLT4SRC);
            /*Configure fault filter counter */
            hrpwm_fltinr1 &= ~(HRPWM_FLTINR1_FLT4F);
            hrpwm_fltinr1 |= ((pFaultCfg->Filter << 16U) & HRPWM_FLTINR1_FLT4F);
            /*Configure fault blanking function */
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT4BLKE | HRPWM_FLTINR2_FLT4BLKS | HRPWM_FLTINR2_FLT4RSTM);
            hrpwm_fltinr2 |= ((pFaultBlkCfg->BlankingEnable << 16U) & HRPWM_FLTINR2_FLT4BLKE) |
                             ((pFaultBlkCfg->BlankingSource << 16U) & HRPWM_FLTINR2_FLT4BLKS) |
                             ((pFaultBlkCfg->ResetMode << 16U) & HRPWM_FLTINR2_FLT4RSTM);
            /*Configure fault count the number of edges */
            hrpwm_fltinr3 &= ~(HRPWM_FLTINR3_FLT4CNT);
            hrpwm_fltinr3 |= (pFaultBlkCfg->Threshold & HRPWM_FLTINR3_FLT4CNT);

            /*enable interrupt*/
            SET_BIT(Instance->Common.IER, (pFaultCfg->InterruptEn & HRPWM_IT_FLT4));
        }
        break;

        case HRPWM_FAULT_5: {
            /*clear relevant register bit */
            hrpwm_fltinr0 &= ~(HRPWM_FLTINR0_FLT5SRC | HRPWM_FLTINR0_FLT5P | HRPWM_FLTINR0_FLT5E);
            /*Configure fault enable */
            hrpwm_fltinr0 |= ((pFaultCfg->Enable << 20U) & HRPWM_FLTINR0_FLT5E);
            /*Configure fault polarity */
            hrpwm_fltinr0 |= ((pFaultCfg->Polarity << 20U) & HRPWM_FLTINR0_FLT5P);
            /*Configure fault source */
            hrpwm_fltinr0 |= ((pFaultCfg->Source << 20U) & HRPWM_FLTINR0_FLT5SRC);
            /*Configure fault filter counter */
            hrpwm_fltinr1 &= ~(HRPWM_FLTINR1_FLT5F);
            hrpwm_fltinr1 |= ((pFaultCfg->Filter << 20U) & HRPWM_FLTINR1_FLT5F);
            /*Configure fault blanking function */
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT5BLKE | HRPWM_FLTINR2_FLT5BLKS | HRPWM_FLTINR2_FLT5RSTM);
            hrpwm_fltinr2 |= ((pFaultBlkCfg->BlankingEnable << 20U) & HRPWM_FLTINR2_FLT5BLKE) |
                             ((pFaultBlkCfg->BlankingSource << 20U) & HRPWM_FLTINR2_FLT5BLKS) |
                             ((pFaultBlkCfg->ResetMode << 20U) & HRPWM_FLTINR2_FLT5RSTM);
            /*Configure fault count the number of edges */
            hrpwm_fltinr3 &= ~(HRPWM_FLTINR3_FLT5CNT);
            hrpwm_fltinr3 |= (pFaultBlkCfg->Threshold & HRPWM_FLTINR3_FLT5CNT);

            /*enable interrupt*/
            SET_BIT(Instance->Common.IER, (pFaultCfg->InterruptEn & HRPWM_IT_FLT5));
        }
        break;

        case HRPWM_SYSFAULT: {
            /*enable interrupt*/
            SET_BIT(Instance->Common.IER, (pFaultCfg->InterruptEn & HRPWM_IT_SYSFLT));
        }
        break;

        default:
            break;
    }

    Instance->Common.FLTINR0 = hrpwm_fltinr0;
    /* Configure the fault conditioning block prescaler */
    Instance->Common.FLTINR1 &= (~(HRPWM_FLTINR1_FLTSD));
    Instance->Common.FLTINR1 |= hrpwm_fltinr1 | (pFaultCfg->SampClockDiv & HRPWM_FLTINR1_FLTSD);

    Instance->Common.FLTINR2 = hrpwm_fltinr2;
    Instance->Common.FLTINR3 = hrpwm_fltinr3;

    return LL_OK;
}

/**
  * @brief  Configure the conditioning of fault blanking
  * @param  Fault fault input to configure
  *                    This parameter can be one of the following values:
  *                    @arg HRPWM_FAULT_0: Fault input 0
  *                    @arg HRPWM_FAULT_1: Fault input 1
  *                    @arg HRPWM_FAULT_2: Fault input 2
  *                    @arg HRPWM_FAULT_3: Fault input 3
  *                    @arg HRPWM_FAULT_4: Fault input 4
  *                    @arg HRPWM_FAULT_5: Fault input 5
  * @param  pFaultBlkCfg pointer to the fault blanking conditioning configuration structure
  * @note This function must be called before starting the timer and before
  *       enabling faults inputs, Configure blanking only without enabling;
  * @retval LL status
  */
LL_StatusETypeDef LL_HRPWM_FaultBlankingConfig(HRPWM_TypeDef *Instance, uint32_t Fault,
        HRPWM_FaultBlankingCfgTypeDef *pFaultBlkCfg)
{
    uint32_t hrpwm_fltinr2;

    /* Check parameters */
    assert_param(IS_HRPWM_FAULT(Fault));
    assert_param(IS_HRPWM_FAULTBLKEN(pFaultBlkCfg->BlankingEnable));
    assert_param(IS_HRPWM_FAULTBLKSRC(pFaultBlkCfg->BlankingSource));
    assert_param(IS_HRPWM_FAULTRSTMODE(pFaultBlkCfg->ResetMode));

    /* Configure fault blanking channel */
    hrpwm_fltinr2 = Instance->Common.FLTINR2;

    switch (Fault) {
        case HRPWM_FAULT_0: {
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT0BLKE | HRPWM_FLTINR2_FLT0BLKS | HRPWM_FLTINR2_FLT0RSTM);
            hrpwm_fltinr2 |= (pFaultBlkCfg->BlankingEnable & HRPWM_FLTINR2_FLT0BLKE) |
                             (pFaultBlkCfg->BlankingSource & HRPWM_FLTINR2_FLT0BLKS) |
                             (pFaultBlkCfg->ResetMode & HRPWM_FLTINR2_FLT0RSTM);
        }
        break;

        case HRPWM_FAULT_1: {
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT1BLKE | HRPWM_FLTINR2_FLT1BLKS | HRPWM_FLTINR2_FLT1RSTM);
            hrpwm_fltinr2 |= ((pFaultBlkCfg->BlankingEnable << 4U) & HRPWM_FLTINR2_FLT1BLKE) |
                             ((pFaultBlkCfg->BlankingSource << 4U) & HRPWM_FLTINR2_FLT1BLKS) |
                             ((pFaultBlkCfg->ResetMode << 4U) & HRPWM_FLTINR2_FLT1RSTM);
        }
        break;

        case HRPWM_FAULT_2: {
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT2BLKE | HRPWM_FLTINR2_FLT2BLKS | HRPWM_FLTINR2_FLT2RSTM);
            hrpwm_fltinr2 |= ((pFaultBlkCfg->BlankingEnable << 8U) & HRPWM_FLTINR2_FLT2BLKE) |
                             ((pFaultBlkCfg->BlankingSource << 8U) & HRPWM_FLTINR2_FLT2BLKS) |
                             ((pFaultBlkCfg->ResetMode << 8U) & HRPWM_FLTINR2_FLT2RSTM);

        }
        break;

        case HRPWM_FAULT_3: {
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT3BLKE | HRPWM_FLTINR2_FLT3BLKS | HRPWM_FLTINR2_FLT3RSTM);
            hrpwm_fltinr2 |= ((pFaultBlkCfg->BlankingEnable << 12U) & HRPWM_FLTINR2_FLT3BLKE) |
                             ((pFaultBlkCfg->BlankingSource << 12U) & HRPWM_FLTINR2_FLT3BLKS) |
                             ((pFaultBlkCfg->ResetMode << 12U) & HRPWM_FLTINR2_FLT3RSTM);
        }
        break;

        case HRPWM_FAULT_4: {
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT4BLKE | HRPWM_FLTINR2_FLT4BLKS | HRPWM_FLTINR2_FLT4RSTM);
            hrpwm_fltinr2 |= ((pFaultBlkCfg->BlankingEnable << 16U) & HRPWM_FLTINR2_FLT4BLKE) |
                             ((pFaultBlkCfg->BlankingSource << 16U) & HRPWM_FLTINR2_FLT4BLKS) |
                             ((pFaultBlkCfg->ResetMode << 16U) & HRPWM_FLTINR2_FLT4RSTM);

        }
        break;

        case HRPWM_FAULT_5: {
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT5BLKE | HRPWM_FLTINR2_FLT5BLKS | HRPWM_FLTINR2_FLT5RSTM);
            hrpwm_fltinr2 |= ((pFaultBlkCfg->BlankingEnable << 20U) & HRPWM_FLTINR2_FLT5BLKE) |
                             ((pFaultBlkCfg->BlankingSource << 20U) & HRPWM_FLTINR2_FLT5BLKS) |
                             ((pFaultBlkCfg->ResetMode << 20U) & HRPWM_FLTINR2_FLT5RSTM);

        }
        break;

        default:
            break;
    }


    Instance->Common.FLTINR2 = hrpwm_fltinr2;

    return LL_OK;
}

/**
  * @brief  Configure the Fault Counter (Threshold and Reset Mode)
  * @param  Fault fault input to configure
  *                    This parameter can be one of the following values:
  *                    @arg HRPWM_FAULT_0: Fault input 0
  *                    @arg HRPWM_FAULT_1: Fault input 1
  *                    @arg HRPWM_FAULT_2: Fault input 2
  *                    @arg HRPWM_FAULT_3: Fault input 3
  *                    @arg HRPWM_FAULT_4: Fault input 4
  *                    @arg HRPWM_FAULT_5: Fault input 5
  * @param  pFaultBlkCfg: pointer to the fault conditioning configuration structure
  * @retval LL status
  * @note  A fault is considered valid when the number of
  *        events is equal to the (FLTxCNT[3:0]+1) value
  *
  * @retval LL status
  */
LL_StatusETypeDef LL_HRPWM_FaultCounterConfig(HRPWM_TypeDef *Instance, uint32_t Fault,
        HRPWM_FaultBlankingCfgTypeDef *pFaultBlkCfg)
{
    uint32_t hrpwm_fltinr2;
    uint32_t hrpwm_fltinr3;

    /* Check parameters */
    assert_param(IS_HRPWM_FAULT(Fault));
    assert_param(IS_HRPWM_FAULTRSTMODE(pFaultBlkCfg->ResetMode));


    /* Configure fault channel */
    hrpwm_fltinr2 = Instance->Common.FLTINR2;
    hrpwm_fltinr3 = Instance->Common.FLTINR3;

    switch (Fault) {
        case HRPWM_FAULT_0: {
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT0RSTM);
            hrpwm_fltinr2 |= (pFaultBlkCfg->ResetMode & HRPWM_FLTINR2_FLT0RSTM);
            /*The number of effective edges. How many edges are collected is considered as a fault*/
            hrpwm_fltinr3 &= ~(HRPWM_FLTINR3_FLT0CNT);
            hrpwm_fltinr3 |= (pFaultBlkCfg->Threshold & HRPWM_FLTINR3_FLT0CNT);
        }
        break;

        case HRPWM_FAULT_1: {
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT1RSTM);
            hrpwm_fltinr2 |= ((pFaultBlkCfg->ResetMode << 4U) & HRPWM_FLTINR2_FLT1RSTM);
            /*The number of effective edges. How many edges are collected is considered as a fault*/
            hrpwm_fltinr3 &= ~(HRPWM_FLTINR3_FLT1CNT);
            hrpwm_fltinr3 |= (pFaultBlkCfg->Threshold & HRPWM_FLTINR3_FLT1CNT);
        }
        break;

        case HRPWM_FAULT_2: {
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT2RSTM);
            hrpwm_fltinr2 |= ((pFaultBlkCfg->ResetMode << 8U) & HRPWM_FLTINR2_FLT2RSTM);
            /*The number of effective edges. How many edges are collected is considered as a fault*/
            hrpwm_fltinr3 &= ~(HRPWM_FLTINR3_FLT2CNT);
            hrpwm_fltinr3 |= (pFaultBlkCfg->Threshold & HRPWM_FLTINR3_FLT2CNT);
        }
        break;

        case HRPWM_FAULT_3: {
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT3RSTM);
            hrpwm_fltinr2 |= ((pFaultBlkCfg->ResetMode << 12U) & HRPWM_FLTINR2_FLT3RSTM);
            /*The number of effective edges. How many edges are collected is considered as a fault*/
            hrpwm_fltinr3 &= ~(HRPWM_FLTINR3_FLT3CNT);
            hrpwm_fltinr3 |= (pFaultBlkCfg->Threshold & HRPWM_FLTINR3_FLT3CNT);
        }
        break;

        case HRPWM_FAULT_4: {
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT4RSTM);
            hrpwm_fltinr2 |= ((pFaultBlkCfg->ResetMode << 16U) & HRPWM_FLTINR2_FLT4RSTM);
            /*The number of effective edges. How many edges are collected is considered as a fault*/
            hrpwm_fltinr3 &= ~(HRPWM_FLTINR3_FLT4CNT);
            hrpwm_fltinr3 |= (pFaultBlkCfg->Threshold & HRPWM_FLTINR3_FLT4CNT);
        }
        break;

        case HRPWM_FAULT_5: {
            hrpwm_fltinr2 &= ~(HRPWM_FLTINR2_FLT5RSTM);
            hrpwm_fltinr2 |= ((pFaultBlkCfg->ResetMode << 20U) & HRPWM_FLTINR2_FLT5RSTM);
            /*The number of effective edges. How many edges are collected is considered as a fault*/
            hrpwm_fltinr3 &= ~(HRPWM_FLTINR3_FLT5CNT);
            hrpwm_fltinr3 |= (pFaultBlkCfg->Threshold & HRPWM_FLTINR3_FLT5CNT);
        }
        break;

        default:
            break;
    }

    Instance->Common.FLTINR2 = hrpwm_fltinr2;
    Instance->Common.FLTINR3 = hrpwm_fltinr3;

    return LL_OK;
}

/**
  * @brief  Reset the fault Counter Reset
  * @param  Fault fault input to configure
  *                    This parameter can be one of the following values:
  *                    @arg HRPWM_FAULT_0: Fault input 0
  *                    @arg HRPWM_FAULT_1: Fault input 1
  *                    @arg HRPWM_FAULT_2: Fault input 2
  *                    @arg HRPWM_FAULT_3: Fault input 3
  *                    @arg HRPWM_FAULT_4: Fault input 4
  *                    @arg HRPWM_FAULT_5: Fault input 5
  * @retval LL status
  */
LL_StatusETypeDef LL_HRPWM_FaultCounterReset(uint32_t Fault)
{
    /* Check parameters */
    assert_param(IS_HRPWM_FAULT(Fault));

    /* Configure fault channel */
    switch (Fault) {
        case HRPWM_FAULT_0: {
            MODIFY_REG(HRPWM->Common.FLTINR2, HRPWM_FLTINR2_FLT0CRES, HRPWM_FLTINR2_FLT0CRES);
        }
        break;

        case HRPWM_FAULT_1: {
            MODIFY_REG(HRPWM->Common.FLTINR2, HRPWM_FLTINR2_FLT1CRES, HRPWM_FLTINR2_FLT1CRES);
        }
        break;

        case HRPWM_FAULT_2: {
            MODIFY_REG(HRPWM->Common.FLTINR2, HRPWM_FLTINR2_FLT2CRES, HRPWM_FLTINR2_FLT2CRES);
        }
        break;

        case HRPWM_FAULT_3: {
            MODIFY_REG(HRPWM->Common.FLTINR2, HRPWM_FLTINR2_FLT3CRES, HRPWM_FLTINR2_FLT3CRES);
        }
        break;

        case HRPWM_FAULT_4: {
            MODIFY_REG(HRPWM->Common.FLTINR2, HRPWM_FLTINR2_FLT4CRES, HRPWM_FLTINR2_FLT4CRES);
        }
        break;

        case HRPWM_FAULT_5: {
            MODIFY_REG(HRPWM->Common.FLTINR2, HRPWM_FLTINR2_FLT5CRES, HRPWM_FLTINR2_FLT5CRES);
        }
        break;

        default:
            break;
    }

    return LL_OK;
}

/**
  * @brief  Configure both the ADC trigger register update source and the ADC
  *         trigger source.
  * @param  ADCTrigger group ADC trigger to configure
  *                    This parameter can be one of the following values:
  *                    @arg HRPWM_ADCTRIGGER_0: ADC trigger 0
  *                    @arg HRPWM_ADCTRIGGER_1: ADC trigger 1
  *                    @arg HRPWM_ADCTRIGGER_2: ADC trigger 2
  *                    @arg HRPWM_ADCTRIGGER_3: ADC trigger 3
  *                    @arg HRPWM_ADCTRIGGER_4: ADC trigger 4
  *                    @arg HRPWM_ADCTRIGGER_5: ADC trigger 5
  *                    @arg HRPWM_ADCTRIGGER_6: ADC trigger 6
  *                    @arg HRPWM_ADCTRIGGER_7: ADC trigger 7
  * @param  pADCTriggerCfg pointer to the ADC trigger configuration structure
  *                    for Trigger nb (0/2/4/6): pADCTriggerCfg->Trigger parameter
  *                    can be a combination of the following values
  *                    @arg HRPWM_ADCTRIGGEREVENT02_...
  *                    @arg HRPWM_ADCTRIGGEREVENT46_...
  *                    for Trigger nb (1/3/5/7): pADCTriggerCfg->Trigger parameter
  *                    can be one of the following values
  *                    @arg HRPWM_ADCTRIGGEREVENT13_...
  *                    @arg HRPWM_ADCTRIGGEREVENT57...
  * @retval LL status
  * @note This function must be called before starting the timer
  */
LL_StatusETypeDef LL_HRPWM_ADDATriggerConfig(HRPWM_TypeDef *Instance, HRPWM_ADCTriggerCfgTypeDef *pADCTriggerCfg)
{
    uint32_t hrpwm_cr0;
    uint32_t hrpwm_cr2;
    uint32_t hrpwm_adpsr;

    /* Check parameters */
    assert_param(IS_HRPWM_ADCTRIGGER(pADCTriggerCfg->TriggerGroup));
    assert_param(IS_HRPWM_ADCTRIGGER_UPDATESRC(pADCTriggerCfg->UpdateSource));
    assert_param(IS_HRPWM_ADCTRIGGER_LENGTH(pADCTriggerCfg->TriggerLength));
    assert_param(IS_HRPWM_ADCTRIGGER_POSTSCALER(pADCTriggerCfg->TriggerPostScaler));

    /* Set the ADC trigger update source */
    hrpwm_cr0 = Instance->Common.CR0;
    hrpwm_cr2 = Instance->Common.CR2;
    hrpwm_adpsr = Instance->Common.ADPSR;

    switch (pADCTriggerCfg->TriggerGroup) {
        case HRPWM_ADCTRIGGER_0: {
            hrpwm_cr0 &= ~(HRPWM_CR0_ADUSRC0);
            hrpwm_cr0 |= ((pADCTriggerCfg->UpdateSource << 8U) & HRPWM_CR0_ADUSRC0);
            /*Set trigger pulse length*/
            hrpwm_cr2 &= ~(HRPWM_CR2_TLEN0);
            hrpwm_cr2 |= ((pADCTriggerCfg->TriggerLength << 0U) & HRPWM_CR2_TLEN0);
            /* Set the ADC trigger postcaler */
            hrpwm_adpsr &= ~(HRPWM_ADPSR_ADPSC0);
            hrpwm_adpsr |= ((pADCTriggerCfg->TriggerPostScaler << 0U) & HRPWM_ADPSR_ADPSC0);
            /* Set the ADC trigger 0 source */
            Instance->Common.ADTR[pADCTriggerCfg->TriggerGroup] = pADCTriggerCfg->Trigger;
            break;
        }

        case HRPWM_ADCTRIGGER_1: {
            hrpwm_cr0 &= ~(HRPWM_CR0_ADUSRC1);
            hrpwm_cr0 |= ((pADCTriggerCfg->UpdateSource << 11U) & HRPWM_CR0_ADUSRC1);
            /*Set trigger pulse length*/
            hrpwm_cr2 &= ~(HRPWM_CR2_TLEN1);
            hrpwm_cr2 |= ((pADCTriggerCfg->TriggerLength << 4U) & HRPWM_CR2_TLEN1);
            /* Set the ADC trigger postcaler */
            hrpwm_adpsr &= ~(HRPWM_ADPSR_ADPSC1);
            hrpwm_adpsr |= ((pADCTriggerCfg->TriggerPostScaler << 4U) & HRPWM_ADPSR_ADPSC1);
            /* Set the ADC trigger 1 source */
            Instance->Common.ADTR[pADCTriggerCfg->TriggerGroup] = pADCTriggerCfg->Trigger;
            break;
        }

        case HRPWM_ADCTRIGGER_2: {
            hrpwm_cr0 &= ~(HRPWM_CR0_ADUSRC2);
            hrpwm_cr0 |= ((pADCTriggerCfg->UpdateSource << 14U) & HRPWM_CR0_ADUSRC2);
            /*Set trigger pulse length*/
            hrpwm_cr2 &= ~(HRPWM_CR2_TLEN2);
            hrpwm_cr2 |= ((pADCTriggerCfg->TriggerLength << 8U) & HRPWM_CR2_TLEN2);
            /* Set the ADC trigger postcaler */
            hrpwm_adpsr &= ~(HRPWM_ADPSR_ADPSC2);
            hrpwm_adpsr |= ((pADCTriggerCfg->TriggerPostScaler << 8U) & HRPWM_ADPSR_ADPSC2);
            /* Set the ADC trigger 2 source */
            Instance->Common.ADTR[pADCTriggerCfg->TriggerGroup] = pADCTriggerCfg->Trigger;
            break;
        }

        case HRPWM_ADCTRIGGER_3: {
            hrpwm_cr0 &= ~(HRPWM_CR0_ADUSRC3);
            hrpwm_cr0 |= ((pADCTriggerCfg->UpdateSource << 17U) & HRPWM_CR0_ADUSRC3);
            /*Set trigger pulse length*/
            hrpwm_cr2 &= ~(HRPWM_CR2_TLEN3);
            hrpwm_cr2 |= ((pADCTriggerCfg->TriggerLength << 12U) & HRPWM_CR2_TLEN3);
            /* Set the ADC trigger postcaler */
            hrpwm_adpsr &= ~(HRPWM_ADPSR_ADPSC3);
            hrpwm_adpsr |= ((pADCTriggerCfg->TriggerPostScaler << 12U) & HRPWM_ADPSR_ADPSC3);
            /* Set the ADC trigger 3 source */
            Instance->Common.ADTR[pADCTriggerCfg->TriggerGroup] = pADCTriggerCfg->Trigger;
            break;
        }

        case HRPWM_ADCTRIGGER_4: {
            hrpwm_cr0 &= ~(HRPWM_CR0_ADUSRC4);
            hrpwm_cr0 |= ((pADCTriggerCfg->UpdateSource << 20U) & HRPWM_CR0_ADUSRC4);
            /*Set trigger pulse length*/
            hrpwm_cr2 &= ~(HRPWM_CR2_TLEN4);
            hrpwm_cr2 |= ((pADCTriggerCfg->TriggerLength << 16U) & HRPWM_CR2_TLEN4);
            /* Set the ADC trigger postcaler */
            hrpwm_adpsr &= ~(HRPWM_ADPSR_ADPSC4);
            hrpwm_adpsr |= ((pADCTriggerCfg->TriggerPostScaler << 16U) & HRPWM_ADPSR_ADPSC4);
            /* Set the ADC trigger 4 source */
            Instance->Common.ADTR[pADCTriggerCfg->TriggerGroup] = pADCTriggerCfg->Trigger;
            break;
        }

        case HRPWM_ADCTRIGGER_5: {
            hrpwm_cr0 &= ~(HRPWM_CR0_ADUSRC5);
            hrpwm_cr0 |= ((pADCTriggerCfg->UpdateSource << 23U) & HRPWM_CR0_ADUSRC5);
            /*Set trigger pulse length*/
            hrpwm_cr2 &= ~(HRPWM_CR2_TLEN5);
            hrpwm_cr2 |= ((pADCTriggerCfg->TriggerLength << 20U) & HRPWM_CR2_TLEN5);
            /* Set the ADC trigger postcaler */
            hrpwm_adpsr &= ~(HRPWM_ADPSR_ADPSC5);
            hrpwm_adpsr |= ((pADCTriggerCfg->TriggerPostScaler << 20U) & HRPWM_ADPSR_ADPSC5);
            /* Set the ADC trigger 5 source */
            Instance->Common.ADTR[pADCTriggerCfg->TriggerGroup] = pADCTriggerCfg->Trigger;
            break;
        }

        case HRPWM_ADCTRIGGER_6: {
            hrpwm_cr0 &= ~(HRPWM_CR0_ADUSRC6);
            hrpwm_cr0 |= ((pADCTriggerCfg->UpdateSource << 26U) & HRPWM_CR0_ADUSRC6);
            /*Set trigger pulse length*/
            hrpwm_cr2 &= ~(HRPWM_CR2_TLEN6);
            hrpwm_cr2 |= ((pADCTriggerCfg->TriggerLength << 24U) & HRPWM_CR2_TLEN6);
            /* Set the ADC trigger postcaler */
            hrpwm_adpsr &= ~(HRPWM_ADPSR_ADPSC6);
            hrpwm_adpsr |= ((pADCTriggerCfg->TriggerPostScaler << 24U) & HRPWM_ADPSR_ADPSC6);
            /* Set the ADC trigger 6 source */
            Instance->Common.ADTR[pADCTriggerCfg->TriggerGroup] = pADCTriggerCfg->Trigger;
            break;
        }

        case HRPWM_ADCTRIGGER_7: {
            hrpwm_cr0 &= ~(HRPWM_CR0_ADUSRC7);
            hrpwm_cr0 |= ((pADCTriggerCfg->UpdateSource << 29U) & HRPWM_CR0_ADUSRC7);
            /*Set trigger pulse length*/
            hrpwm_cr2 &= ~(HRPWM_CR2_TLEN7);
            hrpwm_cr2 |= ((pADCTriggerCfg->TriggerLength << 28U) & HRPWM_CR2_TLEN7);
            /* Set the ADC trigger postcaler */
            hrpwm_adpsr &= ~(HRPWM_ADPSR_ADPSC7);
            hrpwm_adpsr |= ((pADCTriggerCfg->TriggerPostScaler << 28U) & HRPWM_ADPSR_ADPSC7);
            /* Set the ADC trigger 7 source */
            Instance->Common.ADTR[pADCTriggerCfg->TriggerGroup] = pADCTriggerCfg->Trigger;
            break;;
        }

        default:
            break;
    }

    /* Update the HRPWM registers */
    Instance->Common.CR0 = hrpwm_cr0;
    Instance->Common.CR2 = hrpwm_cr2;
    Instance->Common.ADPSR = hrpwm_adpsr;

    return LL_OK;
}

/**
  * @brief  Configure the output of a timing unit
  * @param  TimerIdx Timer index
  * @param  Output timing unit output identifier
  * @param  pOutputCfg pointer to the output configuration data structure
  * @retval None
  */
LL_StatusETypeDef LL_HRPWM_OutputConfig(HRPWM_TypeDef *Instance, uint32_t TimerIdx, HRPWM_OutputCfgTypeDef *pOutputCfg)
{
    if (TimerIdx == HRPWM_INDEX_MASTER) {
        return LL_ERROR;
    }

    uint32_t hrpwm_outr;

    /* Check the parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));
    assert_param(IS_HRPWM_OUTPUTA_POLARITY(pOutputCfg->OutputAPolarity));
    assert_param(IS_HRPWM_OUTPUTA_IDLELEVEL(pOutputCfg->IdleALevel));
    assert_param(IS_HRPWM_OUTPUTA_FLTLEVEL(pOutputCfg->FaultALevel));
    assert_param(IS_HRPWM_OUTPUTA_CHOPPEREN(pOutputCfg->ChopperAModeEnable));
    assert_param(IS_HRPWM_OUTPUTB_POLARITY(pOutputCfg->OutputBPolarity));
    assert_param(IS_HRPWM_OUTPUTB_IDLELEVEL(pOutputCfg->IdleBLevel));
    assert_param(IS_HRPWM_OUTPUTB_FLTLEVEL(pOutputCfg->FaultBLevel));
    assert_param(IS_HRPWM_OUTPUTB_CHOPPEREN(pOutputCfg->ChopperBModeEnable));

    assert_param(IS_HRPWM_OUTPUT_CLEAR_EVENT(pOutputCfg->OutputAClearSource));
    assert_param(IS_HRPWM_OUTPUT_CLEAR_EVENT(pOutputCfg->OutputBClearSource));
    assert_param(IS_HRPWM_OUTPUT_SET_EVENT(pOutputCfg->OutputASetSource));
    assert_param(IS_HRPWM_OUTPUT_SET_EVENT(pOutputCfg->OutputBSetSource));

    hrpwm_outr = Instance->PWM[TimerIdx].OUTR;

    /* Set the output set/reset crossbar */
    Instance->PWM[TimerIdx].SETAR = pOutputCfg->OutputASetSource;
    Instance->PWM[TimerIdx].CLRAR = pOutputCfg->OutputAClearSource;

    /* Set the output set/reset crossbar */
    Instance->PWM[TimerIdx].SETBR = pOutputCfg->OutputBSetSource;
    Instance->PWM[TimerIdx].CLRBR = pOutputCfg->OutputBClearSource;

    /* Clear output config */
    hrpwm_outr &= ~(HRPWM_OUTR_POLA |
                    HRPWM_OUTR_IDLESA |
                    HRPWM_OUTR_FAULTA |
                    HRPWM_OUTR_CHPA |
                    HRPWM_OUTR_POLB |
                    HRPWM_OUTR_IDLESB |
                    HRPWM_OUTR_FAULTB |
                    HRPWM_OUTR_CHPB);

    /* Set the polarity */
    hrpwm_outr |= (pOutputCfg->OutputAPolarity) | (pOutputCfg->OutputBPolarity);

    /* Set the IDLE state */
    hrpwm_outr |= (pOutputCfg->IdleALevel) | (pOutputCfg->IdleBLevel);

    /* Set the FAULT state */
    hrpwm_outr |= (pOutputCfg->FaultALevel) | (pOutputCfg->FaultBLevel);

    /* Set the chopper mode */
    hrpwm_outr |= (pOutputCfg->ChopperAModeEnable) | (pOutputCfg->ChopperBModeEnable);

    /* Update HRPWM register */
    Instance->PWM[TimerIdx].OUTR |= hrpwm_outr;

    return LL_OK;

}

/**
  * @brief  Configure the dead-time output of a timing unit
  * @param  TimerIdx Timer index
  * @param  Output timing unit output identifier
  * @param  pOutputCfg pointer to the output configuration data structure
  * @retval None
  */
LL_StatusETypeDef LL_HRPWM_DeadTimeConfig(HRPWM_TypeDef *Instance, uint32_t TimerIdx, HRPWM_DeadTimeCfgTypeDef *pDeaTimedCfg)
{
    uint32_t hrpwm_outr;
    uint32_t hrpwm_dtr;

    /* Check the parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));
    assert_param(IS_HRPWM_DEADTIME_SDTF(pDeaTimedCfg->FallingSign));
    assert_param(IS_HRPWM_DEADTIME_SDTR(pDeaTimedCfg->RisingSign));

    hrpwm_outr = Instance->PWM[TimerIdx].OUTR;
    hrpwm_dtr  = Instance->PWM[TimerIdx].DTR;

    /* Clear deadtime register config */
    hrpwm_outr &= (~HRPWM_OUTR_DTEN);
    hrpwm_dtr &= ~(HRPWM_DTR_SDTF | HRPWM_DTR_DTF | HRPWM_DTR_SDTR | HRPWM_DTR_DTR);

    /* Set the fall dead time sign and value */
    hrpwm_dtr |= (pDeaTimedCfg->FallingSign) | ((pDeaTimedCfg->FallingValue  << 16U) & HRPWM_DTR_DTF);

    /* Set Set the rise dead time sign and value */
    hrpwm_dtr |= (pDeaTimedCfg->RisingSign) | (pDeaTimedCfg->RisingValue & HRPWM_DTR_DTR);

    /* Eanble dead-time output */
    hrpwm_outr |= (pDeaTimedCfg->DeadTimeEn << 31U);

    /* Update HRPWM register */
    Instance->PWM[TimerIdx].OUTR |= hrpwm_outr;
    Instance->PWM[TimerIdx].DTR = hrpwm_dtr;

    return LL_OK;
}

/**
  * @brief  Configure the Chopper output of a timing unit
  * @param  TimerIdx Timer index
  * @param  Output timing unit output identifier
  * @param  pOutputCfg pointer to the output configuration data structure
  * @retval None
  */
LL_StatusETypeDef LL_HRPWM_ChopperConfig(HRPWM_TypeDef *Instance, uint32_t TimerIdx, HRPWM_ChopperModeCfgTypeDef *pChopperCfg)
{
    uint32_t hrpwm_outr;
    uint32_t hrpwm_chpr;

    /* Check the parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));
    assert_param(IS_HRPWM_OUTPUTA_CHOPPEREN(pChopperCfg->ChopperAModeEnable));
    assert_param(IS_HRPWM_OUTPUTB_CHOPPEREN(pChopperCfg->ChopperBModeEnable));
    assert_param(IS_HRPWM_CHOPPER_CARDTY(pChopperCfg->DutyCycle));
    assert_param(IS_HRPWM_CHOPPER_STRPW(pChopperCfg->StartPulse));
    assert_param(IS_HRPWM_CHOPPER_CARFRQ(pChopperCfg->CarrierFreq));


    hrpwm_outr = Instance->PWM[TimerIdx].OUTR;
    hrpwm_chpr = Instance->PWM[TimerIdx].CHPR;

    /* Clear chopper register config */
    hrpwm_outr &= (~HRPWM_OUTR_CHPB | HRPWM_OUTR_CHPA);
    hrpwm_chpr &= ~(HRPWM_CHPR_STRPW | HRPWM_CHPR_CARDTY | HRPWM_CHPR_CARFRQ);

    /* Set the start pulse width */
    hrpwm_chpr |= (pChopperCfg->StartPulse & HRPWM_CHPR_STRPW);

    /* Set the carrier freq */
    hrpwm_chpr |= (pChopperCfg->CarrierFreq & HRPWM_CHPR_CARFRQ);

    /* Set the chopper duty */
    hrpwm_chpr |= (pChopperCfg->DutyCycle & HRPWM_CHPR_CARDTY);

    /* Eanble chopper A\B output */
    hrpwm_outr |= ((pChopperCfg->ChopperAModeEnable & HRPWM_OUTR_CHPA) |
                   (pChopperCfg->ChopperBModeEnable & HRPWM_OUTR_CHPB));

    /* Update HRPWM register */
    Instance->PWM[TimerIdx].OUTR |= hrpwm_outr;
    Instance->PWM[TimerIdx].CHPR = hrpwm_chpr;

    return LL_OK;
}

/**
  * @brief  Configure an external event channel
  * @param  Event Event channel identifier
  * @param  pEventCfg pointer to the event channel configuration data structure
  * @retval None
  */
LL_StatusETypeDef LL_HRPWM_EventConfig(HRPWM_TypeDef *Instance, uint32_t Event, HRPWM_EventCfgTypeDef *pEventCfg)
{

    /* Check parameters */
    assert_param(IS_HRPWM_EVENT(Event));
    assert_param(IS_HRPWM_EVENTSOURCE(pEventCfg->Source));
    assert_param(IS_HRPWM_EVENTPOLARITY(pEventCfg->Polarity));
    assert_param(IS_HRPWM_EVENTFILTER(pEventCfg->Filter));
    assert_param(IS_HRPWM_EVENTSAMPCLK(pEventCfg->SampClockDiv));
    assert_param(IS_HRPWM_EVENTFASTMODE(pEventCfg->FastMode));
    assert_param(IS_HRPWM_EVENTSNS(pEventCfg->Sensitivity));


    uint32_t hrpwm_eecr0;
    uint32_t hrpwm_eecr1;
    uint32_t hrpwm_eecr2;

    /* Configure external event channel */
    hrpwm_eecr0 = Instance->Common.EECR0;
    hrpwm_eecr1 = Instance->Common.EECR1;
    hrpwm_eecr2 = Instance->Common.EECR2;

    hrpwm_eecr2 &= ~(HRPWM_EECR2_EEVSD);
    hrpwm_eecr2 |= (pEventCfg->SampClockDiv & HRPWM_EECR2_EEVSD);


    switch (Event) {
        case HRPWM_EVENT_NONE: {
            /* Update the HRPWM registers */
            Instance->Common.EECR0 = 0U;
            Instance->Common.EECR1 = 0U;
            Instance->Common.EECR2 = 0U;
            break;
        }

        case HRPWM_EVENT_0: {
            hrpwm_eecr0 &= ~(HRPWM_EECR0_EE0SRC | HRPWM_EECR0_EE0POL | HRPWM_EECR0_EE0SNS | HRPWM_EECR0_EE0FAST);
            hrpwm_eecr0 |= (pEventCfg->Source & HRPWM_EECR0_EE0SRC);
            hrpwm_eecr0 |= (pEventCfg->Polarity & HRPWM_EECR0_EE0POL);
            hrpwm_eecr0 |= (pEventCfg->Sensitivity & HRPWM_EECR0_EE0SNS);
            /* Update the HRPWM registers (all bitfields but EE1FAST bit) */
            Instance->Common.EECR0 = hrpwm_eecr0;
            /* Update the HRPWM registers (EE1FAST bit) */
            hrpwm_eecr0 |= (pEventCfg->FastMode & HRPWM_EECR0_EE0FAST);
            Instance->Common.EECR0 = hrpwm_eecr0;
            /*HRPWM EVENT0 filter*/
            hrpwm_eecr2 &= ~(HRPWM_EECR2_EE0F);
            hrpwm_eecr2 |= (pEventCfg->Filter & HRPWM_EECR2_EE0F);
            Instance->Common.EECR2 = hrpwm_eecr2;
            break;
        }

        case HRPWM_EVENT_1: {
            hrpwm_eecr0 &= ~(HRPWM_EECR0_EE1SRC | HRPWM_EECR0_EE1POL | HRPWM_EECR0_EE1SNS | HRPWM_EECR0_EE1FAST);
            hrpwm_eecr0 |= ((pEventCfg->Source << 6U) & HRPWM_EECR0_EE1SRC);
            hrpwm_eecr0 |= ((pEventCfg->Polarity << 6U) & HRPWM_EECR0_EE1POL);
            hrpwm_eecr0 |= ((pEventCfg->Sensitivity << 6U) & HRPWM_EECR0_EE1SNS);
            /* Update the HRPWM registers (all bitfields but EE1FAST bit) */
            Instance->Common.EECR0 = hrpwm_eecr0;
            /* Update the HRPWM registers (EE1FAST bit) */
            hrpwm_eecr0 |= ((pEventCfg->FastMode << 6U) & HRPWM_EECR0_EE1FAST);
            Instance->Common.EECR0 = hrpwm_eecr0;
            /*HRPWM EVENT1 filter*/
            hrpwm_eecr2 &= ~(HRPWM_EECR2_EE1F);
            hrpwm_eecr2 |= ((pEventCfg->Filter << HRPWM_EECR2_EE1F_Pos) & HRPWM_EECR2_EE1F);
            Instance->Common.EECR2 = hrpwm_eecr2;
            break;
        }

        case HRPWM_EVENT_2: {
            hrpwm_eecr0 &= ~(HRPWM_EECR0_EE2SRC | HRPWM_EECR0_EE2POL | HRPWM_EECR0_EE2SNS | HRPWM_EECR0_EE2FAST);
            hrpwm_eecr0 |= ((pEventCfg->Source << 12U) & HRPWM_EECR0_EE2SRC);
            hrpwm_eecr0 |= ((pEventCfg->Polarity << 12U) & HRPWM_EECR0_EE2POL);
            hrpwm_eecr0 |= ((pEventCfg->Sensitivity << 12U) & HRPWM_EECR0_EE2SNS);
            /* Update the HRPWM registers (all bitfields but EE2FAST bit) */
            Instance->Common.EECR0 = hrpwm_eecr0;
            /* Update the HRPWM registers (EE2FAST bit) */
            hrpwm_eecr0 |= ((pEventCfg->FastMode << 12U) & HRPWM_EECR0_EE2FAST);
            Instance->Common.EECR0 = hrpwm_eecr0;
            /*HRPWM EVENT2 filter*/
            hrpwm_eecr2 &= ~(HRPWM_EECR2_EE2F);
            hrpwm_eecr2 |= ((pEventCfg->Filter << HRPWM_EECR2_EE2F_Pos) & HRPWM_EECR2_EE2F);
            Instance->Common.EECR2 = hrpwm_eecr2;
            break;
        }

        case HRPWM_EVENT_3: {
            hrpwm_eecr0 &= ~(HRPWM_EECR0_EE3SRC | HRPWM_EECR0_EE3POL | HRPWM_EECR0_EE3SNS | HRPWM_EECR0_EE3FAST);
            hrpwm_eecr0 |= ((pEventCfg->Source << 18U) & HRPWM_EECR0_EE3SRC);
            hrpwm_eecr0 |= ((pEventCfg->Polarity << 18U) & HRPWM_EECR0_EE3POL);
            hrpwm_eecr0 |= ((pEventCfg->Sensitivity << 18U) & HRPWM_EECR0_EE3SNS);
            /* Update the HRPWM registers (all bitfields but EE3FAST bit) */
            Instance->Common.EECR0 = hrpwm_eecr0;
            /* Update the HRPWM registers (EE3FAST bit) */
            hrpwm_eecr0 |= ((pEventCfg->FastMode << 18U) & HRPWM_EECR0_EE3FAST);
            Instance->Common.EECR0 = hrpwm_eecr0;
            /*HRPWM EVENT3 filter*/
            hrpwm_eecr2 &= ~(HRPWM_EECR2_EE3F);
            hrpwm_eecr2 |= ((pEventCfg->Filter << HRPWM_EECR2_EE3F_Pos) & HRPWM_EECR2_EE3F);
            Instance->Common.EECR2 = hrpwm_eecr2;
            break;
        }

        case HRPWM_EVENT_4: {
            hrpwm_eecr0 &= ~(HRPWM_EECR0_EE4SRC | HRPWM_EECR0_EE4POL | HRPWM_EECR0_EE4SNS | HRPWM_EECR0_EE4FAST);
            hrpwm_eecr0 |= ((pEventCfg->Source << 24U) & HRPWM_EECR0_EE4SRC);
            hrpwm_eecr0 |= ((pEventCfg->Polarity << 24U) & HRPWM_EECR0_EE4POL);
            hrpwm_eecr0 |= ((pEventCfg->Sensitivity << 24U) & HRPWM_EECR0_EE4SNS);
            /* Update the HRPWM registers (all bitfields but EE4FAST bit) */
            Instance->Common.EECR0 = hrpwm_eecr0;
            /* Update the HRPWM registers (EE4FAST bit) */
            hrpwm_eecr0 |= ((pEventCfg->FastMode << 24U) & HRPWM_EECR0_EE4FAST);
            Instance->Common.EECR0 = hrpwm_eecr0;
            /*HRPWM EVENT4 filter*/
            hrpwm_eecr2 &= ~(HRPWM_EECR2_EE4F);
            hrpwm_eecr2 |= ((pEventCfg->Filter << HRPWM_EECR2_EE4F_Pos) & HRPWM_EECR2_EE4F);
            Instance->Common.EECR2 = hrpwm_eecr2;
            break;
        }

        case HRPWM_EVENT_5: {
            hrpwm_eecr1 &= ~(HRPWM_EECR1_EE5SRC | HRPWM_EECR1_EE5POL | HRPWM_EECR1_EE5SNS | HRPWM_EECR1_EE5FAST);
            hrpwm_eecr1 |= (pEventCfg->Source & HRPWM_EECR1_EE5SRC);
            hrpwm_eecr1 |= (pEventCfg->Polarity & HRPWM_EECR1_EE5POL);
            hrpwm_eecr1 |= (pEventCfg->Sensitivity & HRPWM_EECR1_EE5SNS);
            /* Update the HRPWM registers (all bitfields but EE5FAST bit) */
            Instance->Common.EECR1 = hrpwm_eecr1;
            /* Update the HRPWM registers (EE5FAST bit) */
            hrpwm_eecr1 |= (pEventCfg->FastMode & HRPWM_EECR1_EE5FAST);
            Instance->Common.EECR1 = hrpwm_eecr1;
            /*HRPWM EVENT5 filter*/
            hrpwm_eecr2 &= ~(HRPWM_EECR2_EE5F);
            hrpwm_eecr2 |= ((pEventCfg->Filter << HRPWM_EECR2_EE5F_Pos) & HRPWM_EECR2_EE5F);
            Instance->Common.EECR2 = hrpwm_eecr2;
            break;
        }

        default:
            break;
    }

    return LL_OK;

}

/**
  * @brief  Configure the timer select event A config
  * @param  TimerIdx Timer index
  * @param  Event Event channel identifier
  * @retval None
  */
LL_StatusETypeDef LL_HRPWM_TimerEventAConfig(HRPWM_TypeDef *Instance, uint32_t TimerIdx,
        HRPWM_ExternalEventACfgTypeDef *pEventCfg,
        HRPWM_TimerEventFilteringCfgTypeDef *pEventFilter)
{
    /* Check parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));
    assert_param(IS_HRPWM_EVENTA_FILTER(pEventFilter->Filter));
    assert_param(IS_HRPWM_EVENTA_LATCH(pEventFilter->Latch));
    assert_param(IS_HRPWM_EVENTA_SOURCE(pEventCfg->Source));
    assert_param(IS_HRPWM_EVENTA_RSTMODE(pEventCfg->ResetMode));
    assert_param(IS_HRPWM_EVENTA_COUNTEREN(pEventCfg->CounterEnable));


    uint32_t hrpwm_eefr0 = 0;
    uint32_t hrpwm_eefr1 = 0;

    hrpwm_eefr0 = Instance->PWM[TimerIdx].EEFR0;
    hrpwm_eefr1 = Instance->PWM[TimerIdx].EEFR1;

    switch (pEventCfg->Source) {
        case HRPWM_EEVASEL_SOURCE_EEVENT0:
            hrpwm_eefr0 &= ~(HRPWM_EEFR0_EE0LTCH | HRPWM_EEFR0_EE0FLTR);
            hrpwm_eefr0 |= (pEventFilter->Filter & HRPWM_EEFR0_EE0FLTR) | (pEventFilter->Latch);
            break;

        case HRPWM_EEVASEL_SOURCE_EEVENT1:
            hrpwm_eefr0 &= ~(HRPWM_EEFR0_EE1LTCH | HRPWM_EEFR0_EE1FLTR);
            hrpwm_eefr0 |= ((pEventFilter->Filter << 5U) & HRPWM_EEFR0_EE1FLTR) | (pEventFilter->Latch);
            break;

        case HRPWM_EEVASEL_SOURCE_EEVENT2:
            hrpwm_eefr0 &= ~(HRPWM_EEFR0_EE2LTCH | HRPWM_EEFR0_EE2FLTR);
            hrpwm_eefr0 |= ((pEventFilter->Filter << 10U) & HRPWM_EEFR0_EE2FLTR) | (pEventFilter->Latch);
            break;

        case HRPWM_EEVASEL_SOURCE_EEVENT3:
            hrpwm_eefr0 &= ~(HRPWM_EEFR0_EE3LTCH | HRPWM_EEFR0_EE3FLTR);
            hrpwm_eefr0 |= ((pEventFilter->Filter << 15U) & HRPWM_EEFR0_EE3FLTR) | (pEventFilter->Latch);
            break;

        case HRPWM_EEVASEL_SOURCE_EEVENT4:
            hrpwm_eefr0 &= ~(HRPWM_EEFR0_EE4LTCH | HRPWM_EEFR0_EE4FLTR);
            hrpwm_eefr0 |= ((pEventFilter->Filter << 20U) & HRPWM_EEFR0_EE4FLTR) | (pEventFilter->Latch);
            break;

        case HRPWM_EEVASEL_SOURCE_EEVENT5:
            hrpwm_eefr0 &= ~(HRPWM_EEFR0_EE5LTCH | HRPWM_EEFR0_EE5FLTR);
            hrpwm_eefr0 |= ((pEventFilter->Filter << 25U) & HRPWM_EEFR0_EE5FLTR) | (pEventFilter->Latch);
            break;

        default :
            hrpwm_eefr0 = 0;
            break;
    }

    Instance->PWM[TimerIdx].EEFR0 = hrpwm_eefr0;

    if (pEventCfg->CounterEnable != 0x0U) {
        /*clear event A register */
        hrpwm_eefr1 &= ~(HRPWM_EEFR1_EEVACE   |
                         HRPWM_EEFR1_EEVARSTM |
                         HRPWM_EEFR1_EEVASEL  |
                         HRPWM_EEFR1_EEVACNT);
        /*config event A register */
        hrpwm_eefr1 |= pEventCfg->CounterEnable |
                       pEventCfg->Source        |
                       pEventCfg->ResetMode     |
                       (pEventCfg->Counter << 8U);
    }

    Instance->PWM[TimerIdx].EEFR1 = hrpwm_eefr1;

    return LL_OK;
}

/**
  * @brief  Configure the timer select event A config latch or windows
  * @param  TimerIdx Timer index
  * @param  Event A filter windows select or latch identifier
  * @retval None
  */
LL_StatusETypeDef LL_HRPWM_TimerEventAFilter(HRPWM_TypeDef *Instance, uint32_t TimerIdx, uint32_t Event,
        HRPWM_TimerEventFilteringCfgTypeDef *pEventFilter)
{
    /* Check parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));
    assert_param(IS_HRPWM_EVENT(Event));
    assert_param(IS_HRPWM_EVENTA_FILTER(pEventFilter->Filter));
    assert_param(IS_HRPWM_EVENTA_LATCH(pEventFilter->Latch));


    uint32_t hrpwm_eefr0 = 0;

    hrpwm_eefr0 = Instance->PWM[TimerIdx].EEFR0;

    switch (Event) {
        case HRPWM_EVENT_0:
            hrpwm_eefr0 &= ~(HRPWM_EEFR0_EE0LTCH | HRPWM_EEFR0_EE0FLTR);
            hrpwm_eefr0 |= (pEventFilter->Filter & HRPWM_EEFR0_EE0FLTR) | (pEventFilter->Latch);
            break;

        case HRPWM_EVENT_1:
            hrpwm_eefr0 &= ~(HRPWM_EEFR0_EE1LTCH | HRPWM_EEFR0_EE1FLTR);
            hrpwm_eefr0 |= ((pEventFilter->Filter << 5U) & HRPWM_EEFR0_EE1FLTR) | (pEventFilter->Latch);
            break;

        case HRPWM_EVENT_2:
            hrpwm_eefr0 &= ~(HRPWM_EEFR0_EE2LTCH | HRPWM_EEFR0_EE2FLTR);
            hrpwm_eefr0 |= ((pEventFilter->Filter << 10U) & HRPWM_EEFR0_EE2FLTR) | (pEventFilter->Latch);
            break;

        case HRPWM_EVENT_3:
            hrpwm_eefr0 &= ~(HRPWM_EEFR0_EE3LTCH | HRPWM_EEFR0_EE3FLTR);
            hrpwm_eefr0 |= ((pEventFilter->Filter << 15U) & HRPWM_EEFR0_EE3FLTR) | (pEventFilter->Latch);
            break;

        case HRPWM_EVENT_4:
            hrpwm_eefr0 &= ~(HRPWM_EEFR0_EE4LTCH | HRPWM_EEFR0_EE4FLTR);
            hrpwm_eefr0 |= ((pEventFilter->Filter << 20U) & HRPWM_EEFR0_EE4FLTR) | (pEventFilter->Latch);
            break;

        case HRPWM_EVENT_5:
            hrpwm_eefr0 &= ~(HRPWM_EEFR0_EE5LTCH | HRPWM_EEFR0_EE5FLTR);
            hrpwm_eefr0 |= ((pEventFilter->Filter << 25U) & HRPWM_EEFR0_EE5FLTR) | (pEventFilter->Latch);
            break;

        case HRPWM_EVENT_NONE:
            Instance->PWM[TimerIdx].EEFR0 = 0;
            break;

        default :
            break;
    }

    Instance->PWM[TimerIdx].EEFR0 = hrpwm_eefr0;

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup HRPWM_LL_Exported_Functions_Group6 HRPWM Timer waveform configuration and functions
 *  @brief    HRPWM timer configuration and control functions
@verbatim
 ===============================================================================
              ##### HRPWM timer configuration and control functions #####
 ===============================================================================
    [..]  This section provides functions used to configure and control a
          HRPWM timer operating in waveform mode:
      (+) software force timer register update
      (+) Disable timer register update
      (+) Enable timer register update
      (+) Enable timer Output start
      (+) Enable timer Output stop
      (+) Timer Start output
      (+) Timer stop output
      (+) timer output swap
      (+) Software reset counter
@endverbatim
  * @{
  */

/**
  * @brief  Force an immediate transfer from the preload to the active registers.
  * @param  TimerIdx Timer index
  * @retval None
  */
LL_StatusETypeDef LL_HRPWM_ForceRegistersUpdate(uint32_t TimerIdx)
{
    /* Check parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));

    switch (TimerIdx) {
        case HRPWM_INDEX_MASTER: {
            HRPWM->Common.CR1 |= HRPWM_CR1_MSWU;
            break;
        }

        case HRPWM_INDEX_SLAVE_0: {
            HRPWM->Common.CR1 |= HRPWM_CR1_SWU0;
            break;
        }

        case HRPWM_INDEX_SLAVE_1: {
            HRPWM->Common.CR1 |= HRPWM_CR1_SWU1;
            break;
        }

        case HRPWM_INDEX_SLAVE_2: {
            HRPWM->Common.CR1 |= HRPWM_CR1_SWU2;
            break;
        }

        case HRPWM_INDEX_SLAVE_3: {
            HRPWM->Common.CR1 |= HRPWM_CR1_SWU3;
            break;
        }

        case HRPWM_INDEX_SLAVE_4: {
            HRPWM->Common.CR1 |= HRPWM_CR1_SWU4;
            break;
        }

        case HRPWM_INDEX_SLAVE_5: {
            HRPWM->Common.CR1 |= HRPWM_CR1_SWU5;
            break;
        }

        default:
            break;
    }

    return LL_OK;
}

/**
  * @brief  Disable transfer from the preload to the active registers.
  * @param  TimerIdx Timer index
  * @retval None
  */
LL_StatusETypeDef LL_HRPWM_DisRegisterUpdate(uint32_t TimerIdx)
{
    /* Check parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));

    switch (TimerIdx) {
        case HRPWM_INDEX_MASTER: {
            HRPWM->Common.CR0 |= HRPWM_CR0_MUDIS;
            break;
        }

        case HRPWM_INDEX_SLAVE_0: {
            HRPWM->Common.CR0 |= HRPWM_CR0_UDIS0;
            break;
        }

        case HRPWM_INDEX_SLAVE_1: {
            HRPWM->Common.CR0 |= HRPWM_CR0_UDIS1;
            break;
        }

        case HRPWM_INDEX_SLAVE_2: {
            HRPWM->Common.CR0 |= HRPWM_CR0_UDIS2;
            break;
        }

        case HRPWM_INDEX_SLAVE_3: {
            HRPWM->Common.CR0 |= HRPWM_CR0_UDIS3;
            break;
        }

        case HRPWM_INDEX_SLAVE_4: {
            HRPWM->Common.CR0 |= HRPWM_CR0_UDIS4;
            break;
        }

        case HRPWM_INDEX_SLAVE_5: {
            HRPWM->Common.CR0 |= HRPWM_CR0_UDIS5;
            break;
        }

        default:
            break;
    }

    return LL_OK;
}

/**
  * @brief  Enable transfer from the preload to the active registers.
  * @param  TimerIdx Timer index
  * @retval None
  */
LL_StatusETypeDef LL_HRPWM_EnRegUpdate(uint32_t TimerIdx)
{
    /* Check parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));

    switch (TimerIdx) {
        case HRPWM_INDEX_MASTER: {
            HRPWM->Common.CR0 &= ~(HRPWM_CR0_MUDIS);
            break;
        }

        case HRPWM_INDEX_SLAVE_0: {
            HRPWM->Common.CR0 &= ~(HRPWM_CR0_UDIS0);
            break;
        }

        case HRPWM_INDEX_SLAVE_1: {
            HRPWM->Common.CR0 &= ~(HRPWM_CR0_UDIS1);
            break;
        }

        case HRPWM_INDEX_SLAVE_2: {
            HRPWM->Common.CR0 &= ~(HRPWM_CR0_UDIS2);
            break;
        }

        case HRPWM_INDEX_SLAVE_3: {
            HRPWM->Common.CR0 &= ~(HRPWM_CR0_UDIS3);
            break;
        }

        case HRPWM_INDEX_SLAVE_4: {
            HRPWM->Common.CR0 &= ~(HRPWM_CR0_UDIS4);
            break;
        }

        case HRPWM_INDEX_SLAVE_5: {
            HRPWM->Common.CR0 &= ~(HRPWM_CR0_UDIS5);
            break;
        }

        default:
            break;
    }

    return LL_OK;
}

/**
  * @brief  Enable output start ,this bit only write 1, can read.
  * @param  TimerIdx Timer index
  * @retval None
  */
LL_StatusETypeDef LL_HRPWM_StartOutput(uint32_t TimerIdx)
{
    /* Check parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));

    switch (TimerIdx) {
        case HRPWM_INDEX_SLAVE_0: {
            HRPWM->Common.OENR |= HRPWM_OENR_OEN0A | HRPWM_OENR_OEN0B;
            break;
        }

        case HRPWM_INDEX_SLAVE_1: {
            HRPWM->Common.OENR |= HRPWM_OENR_OEN1A | HRPWM_OENR_OEN1B;
            break;
        }

        case HRPWM_INDEX_SLAVE_2: {
            HRPWM->Common.OENR |= HRPWM_OENR_OEN2A | HRPWM_OENR_OEN2B;
            break;
        }

        case HRPWM_INDEX_SLAVE_3: {
            HRPWM->Common.OENR |= HRPWM_OENR_OEN3A | HRPWM_OENR_OEN3B;
            break;
        }

        case HRPWM_INDEX_SLAVE_4: {
            HRPWM->Common.OENR |= HRPWM_OENR_OEN4A | HRPWM_OENR_OEN4B;
            break;
        }

        case HRPWM_INDEX_SLAVE_5: {
            HRPWM->Common.OENR |= HRPWM_OENR_OEN5A | HRPWM_OENR_OEN5B;
            break;
        }

        default:
            break;
    }

    return LL_OK;
}

/**
  * @brief  Enable output stop, stop putput , this bit only write 1, can read.
  * @param  TimerIdx Timer index
  * @retval None
  */
LL_StatusETypeDef LL_HRPWM_StopOutput(uint32_t TimerIdx)
{
    /* Check parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));

    switch (TimerIdx) {
        case HRPWM_INDEX_SLAVE_0: {
            HRPWM->Common.ODISR |= HRPWM_ODISR_ODIS0A | HRPWM_ODISR_ODIS0B;
            break;
        }

        case HRPWM_INDEX_SLAVE_1: {
            HRPWM->Common.ODISR |= HRPWM_ODISR_ODIS1A | HRPWM_ODISR_ODIS1B;
            break;
        }

        case HRPWM_INDEX_SLAVE_2: {
            HRPWM->Common.ODISR |= HRPWM_ODISR_ODIS2A | HRPWM_ODISR_ODIS2B;
            break;
        }

        case HRPWM_INDEX_SLAVE_3: {
            HRPWM->Common.ODISR |= HRPWM_ODISR_ODIS3A | HRPWM_ODISR_ODIS3B;
            break;
        }

        case HRPWM_INDEX_SLAVE_4: {
            HRPWM->Common.ODISR |= HRPWM_ODISR_ODIS4A | HRPWM_ODISR_ODIS4B;
            break;
        }

        case HRPWM_INDEX_SLAVE_5: {
            HRPWM->Common.ODISR |= HRPWM_ODISR_ODIS5A | HRPWM_ODISR_ODIS5B;
            break;
        }

        default:
            break;
    }

    return LL_OK;
}

/**
  * @brief  Configure swap output
  * @param  TimerIdx Timer index
  * @param  swap: 0: no swap; 1:swap ;So you can exchange the output with each other
  * @retval None
  */
LL_StatusETypeDef LL_HRPWM_SwapOutput(uint32_t TimerIdx, uint32_t swap)
{
    /* Check parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));

    switch (TimerIdx) {
        case HRPWM_INDEX_SLAVE_0: {
            HRPWM->Common.CR1 &= ~(HRPWM_CR1_SWP0);
            HRPWM->Common.CR1 |= ((swap << 16U) & HRPWM_CR1_SWP0);
            break;
        }

        case HRPWM_INDEX_SLAVE_1: {
            HRPWM->Common.CR1 &= ~(HRPWM_CR1_SWP1);
            HRPWM->Common.CR1 |= ((swap << 17U) & HRPWM_CR1_SWP1);
            break;
        }

        case HRPWM_INDEX_SLAVE_2: {
            HRPWM->Common.CR1 &= ~(HRPWM_CR1_SWP2);
            HRPWM->Common.CR1 |= ((swap << 18U) & HRPWM_CR1_SWP2);
            break;
        }

        case HRPWM_INDEX_SLAVE_3: {
            HRPWM->Common.CR1 &= ~(HRPWM_CR1_SWP3);
            HRPWM->Common.CR1 |= ((swap << 19U) & HRPWM_CR1_SWP3);
            break;
        }

        case HRPWM_INDEX_SLAVE_4: {
            HRPWM->Common.CR1 &= ~(HRPWM_CR1_SWP4);
            HRPWM->Common.CR1 |= ((swap << 20U) & HRPWM_CR1_SWP4);
            break;
        }

        case HRPWM_INDEX_SLAVE_5: {
            HRPWM->Common.CR1 &= ~(HRPWM_CR1_SWP5);
            HRPWM->Common.CR1 |= ((swap << 21U) & HRPWM_CR1_SWP5);
            break;
        }

        default:
            break;
    }

    return LL_OK;
}

/**
  * @brief  Software reset timer counter.
  * @param  TimerIdx Timer index
  * @retval None
  */
LL_StatusETypeDef LL_HRPWM_ResetCounter(uint32_t TimerIdx)
{
    /* Check parameters */
    assert_param(IS_HRPWM_INDEX(TimerIdx));

    switch (TimerIdx) {
        case HRPWM_INDEX_MASTER: {
            HRPWM->Common.CR1 |= HRPWM_CR1_MRST;
            break;
        }

        case HRPWM_INDEX_SLAVE_0: {
            HRPWM->Common.CR1 |= HRPWM_CR1_RST0;
            break;
        }

        case HRPWM_INDEX_SLAVE_1: {
            HRPWM->Common.CR1 |= HRPWM_CR1_RST1;
            break;
        }

        case HRPWM_INDEX_SLAVE_2: {
            HRPWM->Common.CR1 |= HRPWM_CR1_RST2;
            break;
        }

        case HRPWM_INDEX_SLAVE_3: {
            HRPWM->Common.CR1 |= HRPWM_CR1_RST3;
            break;
        }

        case HRPWM_INDEX_SLAVE_4: {
            HRPWM->Common.CR1 |= HRPWM_CR1_RST4;
            break;
        }

        case HRPWM_INDEX_SLAVE_5: {
            HRPWM->Common.CR1 |= HRPWM_CR1_RST5;
            break;
        }

        default:
            break;
    }

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup HRPWM_LL_Exported_Functions_Interrupt HRPWM Initerrupt management
  * @brief    HRPWM Initerrupt management
 *  @note  Functions called when HRPWM generates an interrupt
 *          8 interrupts can be generated by the master timer:
 *            - Master timer registers update
 *            - Synchronization event received
 *            - Master timer repetition event
 *            - Master Compare a to d event and period event
 *          11 interrupts can be generated by each timing unit:
 *            - Counter reset or roll-over event
 *            - Output A and output B reset (transition active to inactive)
 *            - Output A and output B set (transition inactive to active)
 *            - Timing unit registers update
 *            - Repetition event
 *            - Compare 1 to 4 event and period event
 *          7 global interrupts are generated for the whole HRPWM:
 *            - System fault and Fault 0 to 5 (regardless of the timing unit attribution)
@verbatim
 ===============================================================================
                      ##### HRPWM interrupts handling #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the HRPWM
    interrupts:
      (+)  HRPWM interrupt handler
      (+)  Callback function called when Fault0 interrupt occurs
      (+)  Callback function called when Fault1 interrupt occurs
      (+)  Callback function called when Fault2 interrupt occurs
      (+)  Callback function called when Fault3 interrupt occurs
      (+)  Callback function called when Fault4 interrupt occurs
      (+)  Callback function called when Fault5 interrupt occurs
      (+)  Callback function called when system Fault interrupt occurs
      (+)  Callback function called when synchronization input interrupt occurs
      (+)  Callback function called when a timer register update interrupt occurs
      (+)  Callback function called when a timer repetition interrupt occurs
      (+)  Callback function called when a compare A match interrupt occurs
      (+)  Callback function called when a compare B match interrupt occurs
      (+)  Callback function called when a compare C match interrupt occurs
      (+)  Callback function called when a compare D match interrupt occurs
      (+)  Callback function called when a timer period interrupt occurs
      (+)  Callback function called when a timer counter reset interrupt occurs
      (+)  Callback function called when a timer output A set interrupt occurs
      (+)  Callback function called when a timer output A reset interrupt occurs
      (+)  Callback function called when a timer output B set interrupt occurs
      (+)  Callback function called when a timer output B reset interrupt occurs
      (+)  HRPWM callback function registration
      (+)  HRPWM callback function unregistration
      (+)  HRPWM Timer x callback function registration
      (+)  HRPWM Timer x callback function unregistration

@endverbatim
  * @{
  */

/**
  * @brief  This function handles HRPWM interrupt request.
  * @param  TimerIdx Timer index
  *                   This parameter can be any value of HRPWM_Timer_Index
  * @retval None
  */
void LL_HRPWM_IRQHandler(uint32_t TimerIdx)
{
    /* Check parameters */
    assert_param(IS_HRPWM_INDEX_ALL(TimerIdx));

    /* HRPWM interrupts handling */
    if (TimerIdx == HRPWM_INDEX_COMMON) {
        LL_HRPWM_FLT_IRQHandler();
    } else if (TimerIdx == HRPWM_INDEX_MASTER) {
        /* Master related interrupts handling */
        LL_HRPWM_MSTR_IRQHandler();
    } else {
        /* Timing unit related interrupts handling */
        LL_HRPWM_SLAVE_IRQHandler(TimerIdx);
    }

}

/**
  * @brief  Callback function invoked when a fault 0 interrupt occurred
  * @retval None
  */
__WEAK void LL_HRPWM_Fault0Callback(void)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(HRPWM);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Fault0Callback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when a fault 1 interrupt occurred
  * @retval None
  */
__WEAK void LL_HRPWM_Fault1Callback(void)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(HRPWM);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Fault1Callback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when a fault 2 interrupt occurred
  * @retval None
  */
__WEAK void LL_HRPWM_Fault2Callback(void)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(HRPWM);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Fault2Callback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when a fault 3 interrupt occurred
  * @retval None
  */
__WEAK void LL_HRPWM_Fault3Callback(void)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(HRPWM);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Fault3Callback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when a fault 4 interrupt occurred
  * @retval None
  */
__WEAK void LL_HRPWM_Fault4Callback(void)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(HRPWM);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Fault4Callback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when a fault 5 interrupt occurred
  * @retval None
  */
__WEAK void LL_HRPWM_Fault5Callback(void)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(HRPWM);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Fault5Callback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when a system fault interrupt occurred
  * @retval None
  */
__WEAK void LL_HRPWM_SystemFaultCallback(void)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(HRPWM);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_SystemFaultCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when a synchronization input event is received
  * @retval None
  */
__WEAK void LL_HRPWM_SynchronizationEventCallback(void)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(HRPWM);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_SynchronizationEventCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when timer registers are updated
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_MASTER  for master timer
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @retval None
  */
__WEAK void LL_HRPWM_RegistersUpdateCallback(uint32_t TimerIdx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(TimerIdx);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Master_RegistersUpdateCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when timer repetition period has elapsed
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_MASTER  for master timer
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @retval None
  */
__WEAK void LL_HRPWM_RepetitionEventCallback(uint32_t TimerIdx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(TimerIdx);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Master_RepetitionEventCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when the timer counter matches the value
  *         programmed in the compare A register
  * @param  hhrpwm pointer to LL HRPWM handle
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_MASTER  for master timer
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @retval None
  */
__WEAK void LL_HRPWM_CompareAEventCallback(uint32_t TimerIdx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(TimerIdx);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Master_CompareAEventCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when the timer counter matches the value
  *         programmed in the compare B register
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_MASTER  for master timer
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @retval None
  */
__WEAK void LL_HRPWM_CompareBEventCallback(uint32_t TimerIdx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(TimerIdx);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Master_CompareBEventCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when the timer counter matches the value
  *         programmed in the compare C register
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_MASTER  for master timer
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @retval None
  */
__WEAK void LL_HRPWM_CompareCEventCallback(uint32_t TimerIdx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(TimerIdx);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Master_CompareCEventCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when the timer counter matches the value
  *         programmed in the compare D register
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_MASTER  for master timer
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @retval None
  */
__WEAK void LL_HRPWM_CompareDEventCallback(uint32_t TimerIdx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(TimerIdx);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Master_CompareDEventCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when the timer counter matches the value programmed in the period register
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_MASTER  for master timer
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @retval None
  */
__WEAK void LL_HRPWM_PeriodEventCallback(uint32_t TimerIdx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(TimerIdx);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Master_PeriodEventCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when the timer x counter reset/roll-over event occurs.
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @retval None
  */
__WEAK void LL_HRPWM_CounterResetCallback(uint32_t TimerIdx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(TimerIdx);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Timer_CounterResetCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when the timer x output A is set
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @retval None
  */
__WEAK void LL_HRPWM_OutputASetCallback(uint32_t TimerIdx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(TimerIdx);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Timer_OutputASetCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when the timer x output B is set
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @retval None
  */
__WEAK void LL_HRPWM_OutputBSetCallback(uint32_t TimerIdx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(TimerIdx);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Timer_OutputBSetCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when the timer x output A is reset
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @retval None
  */
__WEAK void LL_HRPWM_OutputAResetCallback(uint32_t TimerIdx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(TimerIdx);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Timer_OutputAResetCallback could be implemented in the user file
     */
}

/**
  * @brief  Callback function invoked when the timer x output B is reset
  * @param  TimerIdx Timer index
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_INDEX_SLAVE_0 for timer 0
  *                   @arg HRPWM_INDEX_SLAVE_1 for timer 1
  *                   @arg HRPWM_INDEX_SLAVE_2 for timer 2
  *                   @arg HRPWM_INDEX_SLAVE_3 for timer 3
  *                   @arg HRPWM_INDEX_SLAVE_4 for timer 4
  *                   @arg HRPWM_INDEX_SLAVE_5 for timer 5
  * @retval None
  */
__WEAK void LL_HRPWM_OutputBResetCallback(uint32_t TimerIdx)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(TimerIdx);

    /* NOTE : This function should not be modified, when the callback is needed,
              the LL_HRPWM_Timer_OutputBResetCallback could be implemented in the user file
     */
}


/**
  * @brief  This function handles HRPWM Master interrupts requests.
  * @return None
  */
void LL_HRPWM_MSTR_IRQHandler(void)
{
    if (__LL_HRPWM_MASTER_GET_IT(HRPWM_MASTER_IT_MREP) && __LL_HRPWM_MASTER_GET_ITFLAG(HRPWM_MASTER_FLAG_MREP)) {
        __LL_HRPWM_MASTER_CLEAR_ITFLAG(HRPWM_MASTER_FLAG_MREP);

        /*Handle something*/
        LL_HRPWM_RepetitionEventCallback(HRPWM_INDEX_MASTER);
    }

    if (__LL_HRPWM_MASTER_GET_IT(HRPWM_MASTER_IT_MUPD) && __LL_HRPWM_MASTER_GET_ITFLAG(HRPWM_MASTER_FLAG_MUPD)) {
        __LL_HRPWM_MASTER_CLEAR_ITFLAG(HRPWM_MASTER_FLAG_MUPD);

        /*Handle something*/
        LL_HRPWM_RegistersUpdateCallback(HRPWM_INDEX_MASTER);
    }

    if (__LL_HRPWM_MASTER_GET_IT(HRPWM_MASTER_IT_SYNC) && __LL_HRPWM_MASTER_GET_ITFLAG(HRPWM_MASTER_FLAG_SYNC)) {
        __LL_HRPWM_MASTER_CLEAR_ITFLAG(HRPWM_MASTER_FLAG_SYNC);

        /*Handle something*/
        LL_HRPWM_SynchronizationEventCallback();
    }

    if (__LL_HRPWM_MASTER_GET_IT(HRPWM_MASTER_IT_MPER) && __LL_HRPWM_MASTER_GET_ITFLAG(HRPWM_MASTER_FLAG_MPER)) {
        __LL_HRPWM_MASTER_CLEAR_ITFLAG(HRPWM_MASTER_FLAG_MPER);

        /*Handle something*/
        LL_HRPWM_PeriodEventCallback(HRPWM_INDEX_MASTER);
    }

    if (__LL_HRPWM_MASTER_GET_IT(HRPWM_MASTER_IT_MCMPD) && __LL_HRPWM_MASTER_GET_ITFLAG(HRPWM_MASTER_FLAG_MCMPD)) {
        __LL_HRPWM_MASTER_CLEAR_ITFLAG(HRPWM_MASTER_FLAG_MCMPD);

        /*Handle something*/
        LL_HRPWM_CompareDEventCallback(HRPWM_INDEX_MASTER);
    }

    if (__LL_HRPWM_MASTER_GET_IT(HRPWM_MASTER_IT_MCMPC) && __LL_HRPWM_MASTER_GET_ITFLAG(HRPWM_MASTER_FLAG_MCMPC)) {
        __LL_HRPWM_MASTER_CLEAR_ITFLAG(HRPWM_MASTER_FLAG_MCMPC);

        /*Handle something*/
        LL_HRPWM_CompareCEventCallback(HRPWM_INDEX_MASTER);
    }

    if (__LL_HRPWM_MASTER_GET_IT(HRPWM_MASTER_IT_MCMPB) && __LL_HRPWM_MASTER_GET_ITFLAG(HRPWM_MASTER_FLAG_MCMPB)) {
        __LL_HRPWM_MASTER_CLEAR_ITFLAG(HRPWM_MASTER_FLAG_MCMPB);

        /*Handle something*/
        LL_HRPWM_CompareBEventCallback(HRPWM_INDEX_MASTER);
    }

    if (__LL_HRPWM_MASTER_GET_IT(HRPWM_MASTER_IT_MCMPA) && __LL_HRPWM_MASTER_GET_ITFLAG(HRPWM_MASTER_FLAG_MCMPA)) {
        __LL_HRPWM_MASTER_CLEAR_ITFLAG(HRPWM_MASTER_FLAG_MCMPA);

        /*Handle something*/
        LL_HRPWM_CompareAEventCallback(HRPWM_INDEX_MASTER);
    }
}

/**
  * @brief  This function handles HRPWM Slave interrupts requests.
  * @return None
  */
void LL_HRPWM_SLAVE_IRQHandler(uint32_t TimerIdx)
{
    if (__LL_HRPWM_TIMER_GET_IT(TimerIdx, HRPWM_IT_REP) &&
        __LL_HRPWM_TIMER_GET_ITFLAG(TimerIdx, HRPWM_FLAG_REP)) {

        __LL_HRPWM_TIMER_CLEAR_ITFLAG(TimerIdx, HRPWM_FLAG_REP);

        /*Handle something*/
        LL_HRPWM_RepetitionEventCallback(TimerIdx);
    }

    if (__LL_HRPWM_TIMER_GET_IT(TimerIdx, HRPWM_IT_RST) &&
        __LL_HRPWM_TIMER_GET_ITFLAG(TimerIdx, HRPWM_FLAG_RST)) {

        __LL_HRPWM_TIMER_CLEAR_ITFLAG(TimerIdx, HRPWM_FLAG_RST);

        /*Handle something*/
        LL_HRPWM_CounterResetCallback(TimerIdx);
    }

    if (__LL_HRPWM_TIMER_GET_IT(TimerIdx, HRPWM_IT_CLRB) &&
        __LL_HRPWM_TIMER_GET_ITFLAG(TimerIdx, HRPWM_FLAG_CLRB)) {

        __LL_HRPWM_TIMER_CLEAR_ITFLAG(TimerIdx, HRPWM_FLAG_CLRB);

        /*Handle something*/
        LL_HRPWM_OutputBResetCallback(TimerIdx);
    }

    if (__LL_HRPWM_TIMER_GET_IT(TimerIdx, HRPWM_IT_SETB) &&
        __LL_HRPWM_TIMER_GET_ITFLAG(TimerIdx, HRPWM_FLAG_SETB)) {

        __LL_HRPWM_TIMER_CLEAR_ITFLAG(TimerIdx, HRPWM_FLAG_SETB);

        /*Handle something*/
        LL_HRPWM_OutputBSetCallback(TimerIdx);
    }

    if (__LL_HRPWM_TIMER_GET_IT(TimerIdx, HRPWM_IT_CLRA) &&
        __LL_HRPWM_TIMER_GET_ITFLAG(TimerIdx, HRPWM_FLAG_CLRA)) {

        __LL_HRPWM_TIMER_CLEAR_ITFLAG(TimerIdx, HRPWM_FLAG_CLRA);

        /*Handle something*/
        LL_HRPWM_OutputAResetCallback(TimerIdx);
    }

    if (__LL_HRPWM_TIMER_GET_IT(TimerIdx, HRPWM_IT_SETA) &&
        __LL_HRPWM_TIMER_GET_ITFLAG(TimerIdx, HRPWM_FLAG_SETA)) {

        __LL_HRPWM_TIMER_CLEAR_ITFLAG(TimerIdx, HRPWM_FLAG_SETA);

        /*Handle something*/
        LL_HRPWM_OutputASetCallback(TimerIdx);
    }

    if (__LL_HRPWM_TIMER_GET_IT(TimerIdx, HRPWM_IT_UPD) &&
        __LL_HRPWM_TIMER_GET_ITFLAG(TimerIdx, HRPWM_FLAG_UPD)) {

        __LL_HRPWM_TIMER_CLEAR_ITFLAG(TimerIdx, HRPWM_FLAG_UPD);

        /*Handle something*/
        LL_HRPWM_RegistersUpdateCallback(TimerIdx);
    }

    if (__LL_HRPWM_TIMER_GET_IT(TimerIdx, HRPWM_IT_PER) &&
        __LL_HRPWM_TIMER_GET_ITFLAG(TimerIdx, HRPWM_FLAG_PER)) {

        __LL_HRPWM_TIMER_CLEAR_ITFLAG(TimerIdx, HRPWM_FLAG_PER);

        /*Handle something*/
        LL_HRPWM_PeriodEventCallback(TimerIdx);
    }

    if (__LL_HRPWM_TIMER_GET_IT(TimerIdx, HRPWM_IT_CMPD) &&
        __LL_HRPWM_TIMER_GET_ITFLAG(TimerIdx, HRPWM_FLAG_CMPD)) {

        __LL_HRPWM_TIMER_CLEAR_ITFLAG(TimerIdx, HRPWM_FLAG_CMPD);

        /*Handle something*/
        LL_HRPWM_CompareDEventCallback(TimerIdx);
    }

    if (__LL_HRPWM_TIMER_GET_IT(TimerIdx, HRPWM_IT_CMPC) &&
        __LL_HRPWM_TIMER_GET_ITFLAG(TimerIdx, HRPWM_FLAG_CMPC)) {

        __LL_HRPWM_TIMER_CLEAR_ITFLAG(TimerIdx, HRPWM_FLAG_CMPC);

        /*Handle something*/
        LL_HRPWM_CompareCEventCallback(TimerIdx);
    }

    if (__LL_HRPWM_TIMER_GET_IT(TimerIdx, HRPWM_IT_CMPB) &&
        __LL_HRPWM_TIMER_GET_ITFLAG(TimerIdx, HRPWM_FLAG_CMPB)) {

        __LL_HRPWM_TIMER_CLEAR_ITFLAG(TimerIdx, HRPWM_FLAG_CMPB);

        /*Handle something*/
        LL_HRPWM_CompareBEventCallback(TimerIdx);
    }

    if (__LL_HRPWM_TIMER_GET_IT(TimerIdx, HRPWM_IT_CMPA) &&
        __LL_HRPWM_TIMER_GET_ITFLAG(TimerIdx, HRPWM_FLAG_CMPA)) {

        __LL_HRPWM_TIMER_CLEAR_ITFLAG(TimerIdx, HRPWM_FLAG_CMPA);

        /*Handle something*/
        LL_HRPWM_CompareAEventCallback(TimerIdx);
    }
}

/**
  * @brief  This function handles HRPWM Common fault interrupts requests.
  * @return None
  */
void LL_HRPWM_FLT_IRQHandler(void)
{
    if (__LL_HRPWM_GET_IT(HRPWM_IT_SYSFLT) && __LL_HRPWM_GET_ITFLAG(HRPWM_FLAG_SYSFLT)) {

        __LL_HRPWM_CLEAR_ITFLAG(HRPWM_FLAG_SYSFLT);

        /*Handle something*/
        LL_HRPWM_SystemFaultCallback();
    }

    if (__LL_HRPWM_GET_IT(HRPWM_IT_FLT5) && __LL_HRPWM_GET_ITFLAG(HRPWM_FLAG_FLT5)) {

        __LL_HRPWM_CLEAR_ITFLAG(HRPWM_FLAG_FLT5);

        /*Handle something*/
        LL_HRPWM_Fault5Callback();
    }

    if (__LL_HRPWM_GET_IT(HRPWM_IT_FLT4) && __LL_HRPWM_GET_ITFLAG(HRPWM_FLAG_FLT4)) {

        __LL_HRPWM_CLEAR_ITFLAG(HRPWM_FLAG_FLT4);

        /*Handle something*/
        LL_HRPWM_Fault4Callback();
    }

    if (__LL_HRPWM_GET_IT(HRPWM_IT_FLT3) && __LL_HRPWM_GET_ITFLAG(HRPWM_FLAG_FLT3)) {

        __LL_HRPWM_CLEAR_ITFLAG(HRPWM_FLAG_FLT3);

        /*Handle something*/
        LL_HRPWM_Fault3Callback();
    }

    if (__LL_HRPWM_GET_IT(HRPWM_IT_FLT2) && __LL_HRPWM_GET_ITFLAG(HRPWM_FLAG_FLT2)) {

        __LL_HRPWM_CLEAR_ITFLAG(HRPWM_FLAG_FLT2);

        /*Handle something*/
        LL_HRPWM_Fault2Callback();
    }

    if (__LL_HRPWM_GET_IT(HRPWM_IT_FLT1) && __LL_HRPWM_GET_ITFLAG(HRPWM_FLAG_FLT1)) {

        __LL_HRPWM_CLEAR_ITFLAG(HRPWM_FLAG_FLT1);

        /*Handle something*/
        LL_HRPWM_Fault1Callback();
    }

    if (__LL_HRPWM_GET_IT(HRPWM_IT_FLT0) && __LL_HRPWM_GET_ITFLAG(HRPWM_FLAG_FLT0)) {

        __LL_HRPWM_CLEAR_ITFLAG(HRPWM_FLAG_FLT0);

        /*Handle something*/
        LL_HRPWM_Fault0Callback();
    }
}

/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/
/** @addtogroup HRPWM_LL_Private_Functions
  * @{
  */
/**
  * @brief  Configure the master timer in waveform mode
  * @param  pTimerCompCfg pointer to the timer configuration data structure
  * @retval None
  */
static void HRPWM_MasterCompare_Config(HRPWM_TypeDef *Instance, HRPWM_TimerCompareCfgTypeDef *pTimerCompCfg)
{
    uint32_t hrpwm_mcr;

    /* Configure master timer */
    hrpwm_mcr = Instance->Master.MCR;
    /* Enable/Disable preload meachanism for timer registers */
    hrpwm_mcr &= ~(HRPWM_MCR_PREEN);
    hrpwm_mcr |= pTimerCompCfg->PreloadEnable;

    /* Update the HRPWM registers */
    Instance->Master.MCR |= hrpwm_mcr;
    /*Update Compare Value*/
    Instance->Master.MCMPAR = pTimerCompCfg->CompareValueA;
    Instance->Master.MCMPBR = pTimerCompCfg->CompareValueB;
    Instance->Master.MCMPCR = pTimerCompCfg->CompareValueC;
    Instance->Master.MCMPDR = pTimerCompCfg->CompareValueD;
}

/**
  * @brief  Configure timing unit (Timer 0 to Timer 5) in waveform mode
  * @param  TimerIdx Timer index
  * @param  pTimerCompCfg pointer to the timer configuration data structure
  * @retval None
  */
static void HRPWM_TimingUnitCompare_Config(HRPWM_TypeDef *Instance, uint32_t TimerIdx,
        HRPWM_TimerCompareCfgTypeDef *pTimerCompCfg)
{
    uint32_t hrpwm_cr0;

    /* Configure master timing unit */
    hrpwm_cr0 = Instance->PWM[TimerIdx].CR0;

    /* UPDGAT bitfield must be reset before programming a new value */
    hrpwm_cr0 &= ~(HRPWM_CR0_MUPD | HRPWM_CR0_UPD0 | HRPWM_CR0_UPD1 | HRPWM_CR0_UPD2 | HRPWM_CR0_UPD3  |
                   HRPWM_CR0_UPD4 | HRPWM_CR0_UPD5 | HRPWM_UPDATETRIGGER_REP | HRPWM_UPDATETRIGGER_RST);
    /* Set the timer update trigger */
    hrpwm_cr0 |= pTimerCompCfg->UpdateTrigger;

    /* Enable/Disable preload meachanism for timer registers */
    hrpwm_cr0 &= ~(HRPWM_CR0_PREEN);
    hrpwm_cr0 |= pTimerCompCfg->PreloadEnable;

    /* Update the HRPWM registers */
    Instance->PWM[TimerIdx].CR0 |= hrpwm_cr0;
    /* Update Compare Value */
    Instance->PWM[TimerIdx].CMPAR = pTimerCompCfg->CompareValueA;
    Instance->PWM[TimerIdx].CMPBR = pTimerCompCfg->CompareValueB;
    Instance->PWM[TimerIdx].CMPCR = pTimerCompCfg->CompareValueC;
    Instance->PWM[TimerIdx].CMPDR = pTimerCompCfg->CompareValueD;
}

/**
  * @brief  Configure the master timer time base
  * @param  pTimeBaseCfg pointer to the time base configuration structure
  * @retval None
  */
static void HRPWM_MasterBase_Config(HRPWM_TypeDef *Instance, HRPWM_TimerBaseCfgTypeDef *pTimeBaseCfg)
{
    uint32_t hrpwm_mcr;

    /* Configure master timer */
    hrpwm_mcr = Instance->Master.MCR;

    /* Set the prescaler ratio */
    hrpwm_mcr &= ~(HRPWM_MCR_CKPSC);
    hrpwm_mcr |= pTimeBaseCfg->PrescalerRatio;

    /* Set the operating mode */
    hrpwm_mcr &= ~(HRPWM_MCR_CONT | HRPWM_MCR_RETRIG);
    hrpwm_mcr |= pTimeBaseCfg->Mode;

    /* Enable/Disable the timer start upon synchronization event reception */
    hrpwm_mcr &= ~(HRPWM_MCR_SYNCSTRTM);
    hrpwm_mcr |= pTimeBaseCfg->StartOnSync;

    /* Enable/Disable the timer reset upon synchronization event reception */
    hrpwm_mcr &= ~(HRPWM_MCR_SYNCRSTM);
    hrpwm_mcr |= pTimeBaseCfg->ResetOnSync;

    /*Enable Master interrupt*/
    Instance->Master.MIER = pTimeBaseCfg->InterruptRequests;

    /* Update the HRPWM registers */
    Instance->Master.MCR   |= hrpwm_mcr;
    Instance->Master.MPER   = pTimeBaseCfg->Period;
    Instance->Master.MCNTR  = (pTimeBaseCfg->RepetitionCounter) << HRPWM_MCNTR_MREP_Pos;
}

/**
  * @brief  Configure timing unit (Timer 0 to Timer 5) time base
  * @param  TimerIdx Timer index
  * @param  pTimeBaseCfg pointer to the time base configuration structure
  * @retval None
  */
static void HRPWM_TimingUnitBase_Config(HRPWM_TypeDef *Instance, uint32_t TimerIdx, HRPWM_TimerBaseCfgTypeDef *pTimeBaseCfg)
{
    uint32_t hrpwm_cr0;
    uint32_t hrpwm_rstr;

    /* Configure timing unit (Timer 0 to Timer 5) */
    hrpwm_cr0  = Instance->PWM[TimerIdx].CR0;

    /* Enable/Disable the timer start upon synchronization event reception */
    hrpwm_cr0 &= ~(HRPWM_CR0_SYNCSTRT);
    hrpwm_cr0 |= pTimeBaseCfg->StartOnSync;

    /* Enable/Disable the timer reset upon synchronization event reception */
    hrpwm_cr0 &= ~(HRPWM_CR0_SYNCRST);
    hrpwm_cr0 |= pTimeBaseCfg->ResetOnSync;

    /* Timing unit Re-Synchronized Update */
    hrpwm_cr0 &= ~(HRPWM_CR0_RSYNCU);
    hrpwm_cr0 |= (pTimeBaseCfg->ReSyncUpdate & HRPWM_CR0_RSYNCU);

    /* Set the prescaler ratio */
    hrpwm_cr0 &= ~(HRPWM_CR0_CKPSC);
    hrpwm_cr0 |= pTimeBaseCfg->PrescalerRatio;

    /* Set the operating mode */
    hrpwm_cr0 &= ~(HRPWM_CR0_CONT | HRPWM_CR0_RETRIG);
    hrpwm_cr0 |= pTimeBaseCfg->Mode;

    /* Set the timer counter reset trigger */
    hrpwm_rstr = pTimeBaseCfg->ResetTrigger;

    /* Update the HRPWM registers */
    Instance->PWM[TimerIdx].CR0  |= hrpwm_cr0;
    Instance->PWM[TimerIdx].RSTR  = hrpwm_rstr;
    Instance->PWM[TimerIdx].PERR  = pTimeBaseCfg->Period;
    Instance->PWM[TimerIdx].CNTR  = (pTimeBaseCfg->RepetitionCounter) << HRPWM_CNTR_REP_Pos;

    /*Enable timer uint interrupt*/
    Instance->PWM[TimerIdx].IER = pTimeBaseCfg->InterruptRequests;
}

/**
  * @}
  */


#endif /* LL_HRPWM_MODULE_ENABLE */

/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

