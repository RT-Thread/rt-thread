/*******************************************************************************
*
* Copyright [2014-]2014 Freescale Semiconductor, Inc.

*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale License
* distributed with this Material.
* See the LICENSE file distributed for more details.
* 
*
*******************************************************************************/

#include <assert.h>
#include <string.h>
#include "fsl_enc_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#if FSL_FEATURE_SOC_ENC_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION*********************************************************************
 *
 * Function Name : ENC_DRV_StructInitUserConfigNormal
 * Description   : This function  fills the initial user configuration. 
 * Calling the initialization function with the filled parameter configures 
 * the ENC module to function as a simple Quadrature Encoder.
 *
 *END*************************************************************************/
enc_status_t ENC_DRV_StructInitUserConfigNormal(enc_user_config_t * userConfigPtr)
{
    /* Test structure pointer. */
    if (!userConfigPtr)
    {
        return kStatus_ENC_InvalidArgument;
    }
    
    /* Normal Encoder mode. */
    userConfigPtr->operationMode = kEncNormalMode;
    
    /* Reverse counting disabled. */
    userConfigPtr->reverseCounting = false;
    
    /* Positive edge of INDEX pulse. */
    userConfigPtr->indexInputNegativeEdge = false;
    
    /* Positive edge of HOME signal. */
    userConfigPtr->homeInputNegativeEdge = false;
    
    /* Init position register by INDEX pulse. */
    userConfigPtr->indexPulsePosInit = true;
    
    /* Initialization register value set to 0U. */
    userConfigPtr->posCntInitValue = 0U;
    
    /* Position compare register value set to 0xFFFFU. */
    userConfigPtr->posCmpValue = 0xFFFFU;
    
    /* Modulus register value set to 0U. */
    userConfigPtr->moduloValue = 0U;
    
    /* Update HOLD registers on trigger input disabled. */
    userConfigPtr->triggerUpdateHoldRegEnable = false;
    
    /* Clear position counter on trigger input disabled. */
    userConfigPtr->triggerClearPosRegEnable = false;
    
    /* Modulo counting revolution register disabled. */
    userConfigPtr->moduloRevolutionCounting = false;
    
    /* POSMATCH pulses when match occurs between position register and compare register value. */
    userConfigPtr->outputControlOnReading = false;
    
    /* Watchdog disabled. */
    userConfigPtr->watchdogTimeout = 0U;
    
    /* Filter number of counts set to 0. */
    userConfigPtr->filterCount = 0U;
    
    /* Filter period set to 0U. */
    userConfigPtr->filterPeriod = 0U;
    
    /* Return success status code. */
    return kStatus_ENC_Success;
}
   
/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_DRV_Init
 * Description   : This function initializes a ENC instance for operation.
 * This function initializes the run-time state structure to ungate the clock to the ENC module,
 * initializes the module to user-defined settings and default settings,
 * configures the IRQ state structure and enables the module-level interrupt to the core.
 * This example shows how to set up the enc_state_t and the
 * enc_user_config_t parameters and how to call the ENC_DRV_Init function by passing
 * in these parameters:
    enc_user_config_t encUserConfig;
    encUserConfig.operationMode = kEncNormalMode;
    encUserConfig.reverseCounting = false;
    encUserConfig.indexInputNegativeEdge = false;
    encUserConfig.homeInputNegativeEdge = false;
    encUserConfig.indexPulsePosInit = true;
    encUserConfig.posCntInitValue = 0U;
    encUserConfig.posCmpValue = 0xFFFFU;
    encUserConfig.moduloValue = 0U;
    encUserConfig.triggerUpdateHoldRegEnable = false;
    encUserConfig.triggerClearPosRegEnable = false;
    encUserConfig.moduloRevolutionCounting = false;
    encUserConfig.outputControlOnReading = false;
    encUserConfig.watchdogTimeout = 0U;
    encUserConfig.filterCount = 0U;
    encUserConfig.filterPeriod = 0U;
    ENC_DRV_Init(instance, &encUserConfig);
 *
 *END**************************************************************************/
enc_status_t ENC_DRV_Init(uint32_t instance, const enc_user_config_t *userConfigPtr)
{    
    assert(instance < ENC_INSTANCE_COUNT); 
    ENC_Type* base = g_encBase[instance];
    bool mEnable;
    
    /* Test structure pointer. */
    if (!userConfigPtr)
    {
        return kStatus_ENC_InvalidArgument;
    }
    
    /* Enable Clock to Quadrature Encoder peripheral. */
    mEnable = CLOCK_SYS_GetEncGateCmd(instance);
    if (!mEnable)
    {
        CLOCK_SYS_EnableEncClock(instance);
    }
  
    /* Reset the registers for ENC module to reset state. */
    ENC_HAL_Init(base);
    
    /* Set operation mode. */
    switch(userConfigPtr->operationMode)
    {
    case kEncModuloCountingMode:
        ENC_HAL_SetModuloCountingCmd(base, true);
        break;
        
    case kEncSignalPhaseCountMode:
        ENC_HAL_SetSignalPhaseCountModeCmd(base, true);
        break;
        
    case kEncNormalMode:
        ENC_HAL_SetModuloCountingCmd(base, false);
        ENC_HAL_SetSignalPhaseCountModeCmd(base, false);
        break;
        
    default:
        return kStatus_ENC_Error;
    }
    
    /* Set directiong of counting. */
    ENC_HAL_SetReverseCountingCmd(base, userConfigPtr->reverseCounting);
        
    /* INDEX input transition edge setting. */
    ENC_HAL_SetIndexPulseNegativeEdgeCmd(base, userConfigPtr->indexInputNegativeEdge);
    
    /* HOME input transition edge setting. */
    ENC_HAL_SetHomeSignalNegativeEdgeCmd(base, userConfigPtr->homeInputNegativeEdge);
    
    /* Position counter init signal. */
    ENC_HAL_SetIndexInitPosCmd(base, userConfigPtr->indexPulsePosInit);
    ENC_HAL_SetHomeInitPosCmd(base, !userConfigPtr->indexPulsePosInit);
        
    /* Position counter init value. */
    ENC_HAL_SetInitReg(base, userConfigPtr->posCntInitValue);
    
    /* Position compare init value. */
    ENC_HAL_SetCmpReg(base, userConfigPtr->posCmpValue);
    
    /* Modulo value. */
    ENC_HAL_SetModulusReg(base, userConfigPtr->moduloValue);
    
    /* Enable/disable update hold registers on input trigger. */
    ENC_HAL_SetTriggerUpdateHoldRegCmd(base, userConfigPtr->triggerUpdateHoldRegEnable);
        
    /* Enable/disable clear position registers on input trigger. */
    ENC_HAL_SetTriggerClearPosRegCmd(base, userConfigPtr->triggerClearPosRegEnable);
    
    /* Set revolution counting type - Index pulse or Modulus counting rollover, rollunder. */
    ENC_HAL_SetModulusRevCounterCmd(base, userConfigPtr->moduloRevolutionCounting); 
        
    /* POSMATCH output control. */
    ENC_HAL_SetPosmatchOnReadingCmd(base, userConfigPtr->outputControlOnReading);
        
    /* Setting watchdog timeout. */
    if (userConfigPtr->watchdogTimeout == 0)
    {
        ENC_HAL_SetWatchdogCmd(base, false);
    }
    else
    {
        ENC_HAL_SetWatchdogCmd(base, true);
        ENC_HAL_SetWatchdogTimeout(base, userConfigPtr->watchdogTimeout);
    }
    
    /* Set Filter values. */
    ENC_HAL_SetInputFilterSampleCount(base, userConfigPtr->filterCount);
    ENC_HAL_SetInputFilterSamplePeriod(base, userConfigPtr->filterPeriod);
    
    /* Clear position difference and revolution counter. */
    ENC_HAL_SetRevolutionCounterReg(base, 0);
    ENC_HAL_SetPosDiffCounterReg(base, 0);
    ENC_HAL_SetPosCounterReg(base, 0);
    
    /* Enable ENC interrupt on NVIC level. */
    INT_SYS_EnableIRQ(g_encCmpIrqId[instance]);
    INT_SYS_EnableIRQ(g_encWdtIrqId[instance]);
    INT_SYS_EnableIRQ(g_encHomeIrqId[instance]);
    INT_SYS_EnableIRQ(g_encIndexIrqId[instance]);
    
    /* Return succes status code. */
    return kStatus_ENC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_DRV_Deinit
 * Description   : De-initialize the Quadrature Encoder module. It will
 * shut down its clock to reduce the power consumption. 
 *
 *END**************************************************************************/
void ENC_DRV_Deinit(uint32_t instance)
{
    assert(instance < ENC_INSTANCE_COUNT);

    /* Disables Clock to Quadrature Encoder peripheral. */
    CLOCK_SYS_DisableEncClock(instance);
    
    /* Disable ENC interrupt on NVIC level. */
    INT_SYS_DisableIRQ(g_encCmpIrqId[instance]);
    INT_SYS_DisableIRQ(g_encWdtIrqId[instance]);
    INT_SYS_DisableIRQ(g_encHomeIrqId[instance]);
    INT_SYS_DisableIRQ(g_encIndexIrqId[instance]);
}
  
/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_DRV_TestInit
 * Description   : This function initializes a Test Module of ENC.
 * This function initializes the run-time state structure to enable Test Module,
 * and sets the test period and test count values.
 * This example shows how to set up the enc_test_config_t parameters and 
 * how to call the ENC_DRV_TestInit function by passing
 * in these parameters:
    enc_test_config_t encTestConfig;
    encTestConfig.testNegativeSignalEnable = false;
    encTestConfig.testCount = 100;
    encTestConfig.testPeriod = 10;
    ENC_DRV_TestInit(&encTestConfig);
 *
 *END**************************************************************************/
enc_status_t ENC_DRV_TestInit(uint32_t instance, const enc_test_config_t * userConfigPtr)
{
    assert(instance < ENC_INSTANCE_COUNT); 
    ENC_Type* base = g_encBase[instance];
    
    /* Test structure pointer. */
    if (!userConfigPtr)
    {
        return kStatus_ENC_InvalidArgument;
    }

    /* Enable settings of Test Module. */
    ENC_HAL_SetNegativeTestSignalCmd(base, userConfigPtr->testNegativeSignalEnable);
    ENC_HAL_SetTestPeriod(base, userConfigPtr->testPeriod);
    ENC_HAL_SetTestCount(base, userConfigPtr->testCount);
    
    /* Enable Test Module. */
    ENC_HAL_SetTestModuleCmd(base, true);
    ENC_HAL_SetTestCounterCmd(base, true);
    
    /* Return succes status code. */
    return kStatus_ENC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_DRV_TestDeinit
 * Description   : This function shuts down the ENC test module, disable test counter
 *                 and clears the test period and test count.
 *
 *END**************************************************************************/
void ENC_DRV_TestDeinit(uint32_t instance)
{
    assert(instance < ENC_INSTANCE_COUNT); 
    ENC_Type* base = g_encBase[instance];
  
    /* Disable Test Module. */
    ENC_HAL_SetTestModuleCmd(base, false);
    ENC_HAL_SetTestCounterCmd(base, false);
  
    /* Clear settings of Test Module. */
    ENC_HAL_SetTestPeriod(base, 0);
    ENC_HAL_SetTestCount(base, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_DRV_SetIntMode
 * Description   : This function enables any ENC interrupt.
 *
 *END**************************************************************************/
enc_status_t ENC_DRV_SetIntMode(uint32_t instance, enc_int_source_t intSrc, bool enable)
{  
    assert(instance < ENC_INSTANCE_COUNT); 
    ENC_Type* base = g_encBase[instance];
  
    /* Switch to relevant ENC interrupt source. */
    switch(intSrc)
    {
      /* Encoder Compare interrupt enable/disable. */
    case kEncIntCmp:
      ENC_HAL_SetCmpIntCmd(base, enable); 
      break;
      
      /* Encoder Watchdog timeout enable/disable. */
    case kEncIntWatchdogTimeout:
      ENC_HAL_SetWatchdogIntCmd(base, enable);
      break;
      
      /* Encoder Home Signal interrupt enable/disable. */
    case kEncIntHomeSignal:
      ENC_HAL_SetHomeSignalIntCmd(base, enable);
      break;
      
      /* Encoder Index Pulse interrupt enable/disable. */
    case kEncIntIndexPulse:
      ENC_HAL_SetIndexPulseIntCmd(base, enable);
      break;
      
      /* Encoder Roll-under interrupt enable/disable. */
    case kEncIntRollunder:
      ENC_HAL_SetRollunderIntCmd(base, enable);
      break;
      
      /* Encoder Roll-over interrupt enable/disable. */
    case kEncIntRollover:
      ENC_HAL_SetRolloverIntCmd(base, enable);
      break;
      
      /* Encoder Simultaneous interrupt enable/disable. */
    case kEncIntSimultaneous:
      ENC_HAL_SetSimultaneousIntCmd(base, enable);
      break;
      
      /* Default. */
    default: return kStatus_ENC_Error;
    }
    
    /* Return succes status code. */
    return kStatus_ENC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_DRV_GetIntMode
 * Description   : This function gets configuration of any ENC interrupt.
 *
 *END**************************************************************************/
bool ENC_DRV_GetIntMode(uint32_t instance, enc_int_source_t intSrc)
{
    assert(instance < ENC_INSTANCE_COUNT); 
    ENC_Type* base = g_encBase[instance];
    bool bRet;
  
    /* Switch to relevant ENC interrupt source. */
    switch(intSrc)
    {
      /* Encoder Compare interrupt enable/disable. */
    case kEncIntCmp:
      bRet = ENC_HAL_GetCmpIntCmd(base);
      break;
      
      /* Encoder Watchdog timeout enable/disable. */
    case kEncIntWatchdogTimeout:
      bRet = ENC_HAL_GetWatchdogIntCmd(base);
      break;
      
      /* Encoder Home Signal interrupt enable/disable. */
    case kEncIntHomeSignal:
      bRet = ENC_HAL_GetHomeSignalIntCmd(base);
      break;
      
      /* Encoder Index Pulse interrupt enable/disable. */
    case kEncIntIndexPulse:
      bRet = ENC_HAL_GetIndexPulseIntCmd(base);
      break;
      
      /* Encoder Roll-under interrupt enable/disable. */
    case kEncIntRollunder:
      bRet = ENC_HAL_GetRollunderIntCmd(base);
      break;
      
      /* Encoder Roll-over interrupt enable/disable. */
    case kEncIntRollover:
      bRet = ENC_HAL_GetRolloverIntCmd(base);
      break;
      
      /* Encoder Simultaneous interrupt enable/disable. */
    case kEncIntSimultaneous:
      bRet = ENC_HAL_GetSimultaneousIntCmd(base);
      break;
      
      /* Default. */
    default:
      bRet = false;
      break;
    }
    
    /* Return value of interrupt status. */
    return bRet;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_DRV_GetStatusFlag
 * Description   : This function gets status flag of selected status.
 *
 *END**************************************************************************/
bool ENC_DRV_GetStatusFlag(uint32_t instance, enc_status_flag_t flag)
{
    assert(instance < ENC_INSTANCE_COUNT);
    ENC_Type* base = g_encBase[instance];
    bool bRet;
    
    /* Switch to relevant ENC interrupt source. */
    switch(flag)
    {
      /* Encoder Compare interrupt flag. */
    case kEncCmpFlag:
      bRet = ENC_HAL_GetCmpIntFlag(base);
      break;
      
      /* Encoder Watchdog timeout flag. */
    case kEncWatchdogTimeoutFlag:
      bRet = ENC_HAL_GetWatchdogIntFlag(base);
      break;
      
      /* Encoder Home Signal interrupt flag. */
    case kEncHomeSignalFlag:
      bRet = ENC_HAL_GetHomeSignalIntFlag(base);
      break;
      
      /* Encoder Index Pulse interrupt flag. */
    case kEncIndexPulseFlag:
      bRet = ENC_HAL_GetIndexPulseIntFlag(base);
      break;
      
      /* Encoder Roll-under interrupt flag. */
    case kEncRollunderFlag:
      bRet = ENC_HAL_GetRollunderIntFlag(base);
      break;
      
      /* Encoder Roll-over interrupt flag. */
    case kEncRolloverFlag:
      bRet = ENC_HAL_GetRolloverIntFlag(base);
      break;
      
      /* Encoder Simultaneous interrupt flag. */
    case kEncSimultaneousFlag:
      bRet = ENC_HAL_GetSimultaneousIntFlag(base);
      break;
      
      /* Encoder last count direction flag. */
    case kEncCountDirectionFlag:
      bRet = ENC_HAL_GetLastCountDirectionFlag(base);
      break;
      
    default: 
      bRet = false;
      break;
    }
    
    /* Return value of interrupt status flag. */
    return bRet;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_DRV_ClearStatusFlag
 * Description   : This function clears status flag of selected status.
 *
 *END**************************************************************************/
void ENC_DRV_ClearStatusFlag(uint32_t instance, enc_status_flag_t flag)
{
    assert(instance < ENC_INSTANCE_COUNT); 
    ENC_Type* base = g_encBase[instance];
    
    /* Switch to relevant ENC interrupt source. */
    switch(flag)
    {
      /* Encoder Compare interrupt flag. */
    case kEncCmpFlag:
      ENC_HAL_ClearCmpIntFlag(base); 
      break;
      
      /* Encoder Watchdog timeout flag. */
    case kEncWatchdogTimeoutFlag:
      ENC_HAL_ClearWatchdogIntFlag(base);
      break;
      
      /* Encoder Home Signal interrupt flag. */
    case kEncHomeSignalFlag:
      ENC_HAL_ClearHomeSignalIntFlag(base);
      break;
      
      /* Encoder Index Pulse interrupt flag. */
    case kEncIndexPulseFlag:
      ENC_HAL_ClearIndexPulseIntFlag(base);
      break;
      
      /* Encoder Roll-under interrupt flag. */
    case kEncRollunderFlag:
      ENC_HAL_ClearRollunderIntFlag(base);
      break;
      
      /* Encoder Roll-over interrupt flag. */
    case kEncRolloverFlag:
      ENC_HAL_ClearRolloverIntFlag(base);
      break;
      
      /* Encoder Simultaneous interrupt flag. */
    case kEncSimultaneousFlag:
      ENC_HAL_ClearSimultaneousIntFlag(base);
      break;
      
    default: 
      break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_DRV_ReadCounters
 * Description   : This function reads the ENC Registers of Counters.
 *
 *END**************************************************************************/
enc_status_t ENC_DRV_ReadCounters(uint32_t instance, enc_counter_t * countRegPtr)
{
    assert(instance < ENC_INSTANCE_COUNT); 
    ENC_Type* base = g_encBase[instance];
    
    /* Test structure pointer. */
    if (!countRegPtr)
    {
        return kStatus_ENC_InvalidArgument;
    }
  
    /* At first read position difference COUNTER register. */
    countRegPtr->posDiff = ENC_HAL_GetPosDiffCounterReg(base);
    
    /* Other counter registers are automatically triggered to HOLD registers. */
    countRegPtr->position = ENC_HAL_GetPosHoldReg(base);
    countRegPtr->revolution = ENC_HAL_GetRevolutionHoldReg(base);
    
    /* Return succes status code. */
    return kStatus_ENC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_DRV_ReadHoldReg
 * Description   : This function reads the ENC Hold Registers of counters.
 *
 *END**************************************************************************/
enc_status_t ENC_DRV_ReadHoldReg(uint32_t instance, enc_counter_t * holdRegPtr)
{
    assert(instance < ENC_INSTANCE_COUNT); 
    ENC_Type* base = g_encBase[instance];
    
    /* Test structure pointer. */
    if (!holdRegPtr)
    {
        return kStatus_ENC_InvalidArgument;
    }
  
    /* Read Hold registers. */
    holdRegPtr->position = ENC_HAL_GetPosHoldReg(base);
    holdRegPtr->posDiff = ENC_HAL_GetPosDiffHoldReg(base);
    holdRegPtr->revolution = ENC_HAL_GetRevolutionHoldReg(base);
    
    /* Return succes status code. */
    return kStatus_ENC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_DRV_ResetCounters
 * Description   : This function resets the ENC Position registers.
 *
 *END**************************************************************************/
void ENC_DRV_ResetCounters(uint32_t instance)
{
    assert(instance < ENC_INSTANCE_COUNT); 
    ENC_Type* base = g_encBase[instance];
    
    /* Re-init position counter. */
    ENC_HAL_InitPosCounter(base);
    
    /* Clear position difference and revolution counter. */
    ENC_HAL_SetRevolutionCounterReg(base, 0);
    ENC_HAL_SetPosDiffCounterReg(base, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ENC_DRV_ReadInputMonitor
 * Description   : This function reads the ENC Input Monitor register.
 *
 *END**************************************************************************/
enc_status_t ENC_DRV_ReadInputMonitor
  (uint32_t instance, bool inputMonitorRaw, enc_input_monitor_t * inputMonitorPtr)
{
    assert(instance < ENC_INSTANCE_COUNT); 
    ENC_Type* base = g_encBase[instance];
    
    /* Test structure pointer. */
    if (!inputMonitorPtr)
    {
        return kStatus_ENC_InvalidArgument;
    }
    
    /* Switch to raw or filtered type of input monitor. */
    if (inputMonitorRaw)
    {
        /* Get raw inputs. */
        inputMonitorPtr->phaseA = ENC_HAL_GetRawPhaseAInput(base);
        inputMonitorPtr->phaseB = ENC_HAL_GetRawPhaseBInput(base);
        inputMonitorPtr->index = ENC_HAL_GetRawIndexInput(base);
        inputMonitorPtr->home = ENC_HAL_GetRawHomeInput(base);
    }
    else
    {
        /* Get filtered inputs. */
        inputMonitorPtr->phaseA = ENC_HAL_GetFilteredPhaseAInput(base);
        inputMonitorPtr->phaseB = ENC_HAL_GetFilteredPhaseBInput(base);
        inputMonitorPtr->index = ENC_HAL_GetFilteredIndexInput(base);
        inputMonitorPtr->home = ENC_HAL_GetFilteredHomeInput(base);
    }

    /* Return succes status code. */
    return kStatus_ENC_Success;
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
