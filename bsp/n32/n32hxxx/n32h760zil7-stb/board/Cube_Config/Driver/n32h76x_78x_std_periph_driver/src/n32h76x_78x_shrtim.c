/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_shrtim.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_shrtim.h"

/**
*\*\fun  Select the SHRTIM synchronization input source.
*\*\note This function must not be called when  the concerned timer(s) is (are) enabled .
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  SyncInSrc This parameter can be one of the following values:
*\*\        - SHRTIM_SYNCIN_SRC_INTERNAL_EVENT_0    from ATIM1 trgo
*\*\        - SHRTIM_SYNCIN_SRC_INTERNAL_EVENT_1    from ATIM2 trgo
*\*\        - SHRTIM_SYNCIN_SRC_INTERNAL_EVENT_2    from ATIM3 trgo
*\*\        - SHRTIM_SYNCIN_SRC_EXTERNAL_EVENT_3    from IOM
*\*\        - SHRRIM_SYNCIN_SRC_INTERNAL_EVENT_4    from shrtim_out_sync2 of another SHRTIM
*\*\return None
**/
void SHRTIM_SetSyncInSrc(SHRTIM_Module *SHRTIMx, uint32_t SyncInSrc)
{
    MODIFY_REG(SHRTIMx->sMasterRegs.MCTRL, SHRTIM_MCTRL_SYNCIN, SyncInSrc);
}

/**
*\*\fun  Get actual SHRTIM synchronization input source.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return SyncInSrc Returned value can be one of the following values:
*\*\        - SHRTIM_SYNCIN_SRC_INTERNAL_EVENT_0    from ATIM1 trgo
*\*\        - SHRTIM_SYNCIN_SRC_INTERNAL_EVENT_1    from ATIM2 trgo
*\*\        - SHRTIM_SYNCIN_SRC_INTERNAL_EVENT_2    from ATIM3 trgo
*\*\        - SHRTIM_SYNCIN_SRC_EXTERNAL_EVENT_3    from IOM
*\*\        - SHRRIM_SYNCIN_SRC_EXTERNAL_EVENT_4    from shrtim_out_sync2 of another SHRTIM
**/
uint32_t SHRTIM_GetSyncInSrc(SHRTIM_Module *SHRTIMx)
{
    return (READ_BIT(SHRTIMx->sMasterRegs.MCTRL, SHRTIM_MCTRL_SYNCIN));
}

/**
*\*\fun  Configure the SHRTIM synchronization output.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Config This parameter can be one of the following values:
*\*\        - SHRTIM_SYNCOUT_DISABLED
*\*\        - SHRTIM_SYNCOUT_POSITIVE_PULSE
*\*\        - SHRTIM_SYNCOUT_NEGATIVE_PULSE
*\*\param  Src This parameter can be one of the following values:
*\*\        - SHRTIM_SYNCOUT_SRC_MASTER_START
*\*\        - SHRTIM_SYNCOUT_SRC_MASTER_CMP1
*\*\        - SHRTIM_SYNCOUT_SRC_TIMA_START
*\*\        - SHRTIM_SYNCOUT_SRC_TIMA_CMP1
*\*\return None
**/
void SHRTIM_ConfigSyncOut(SHRTIM_Module *SHRTIMx, uint32_t Config, uint32_t Src)
{
    MODIFY_REG(SHRTIMx->sMasterRegs.MCTRL, SHRTIM_MCTRL_SYNCOSRC, Src);
    MODIFY_REG(SHRTIMx->sMasterRegs.SYNCOUT, SHRTIM_SYNCOUT_SYNCOUTPUS, Config);
}

/**
*\*\fun  Set the routing and conditioning of the syncout event.
*\*\note This function can be called only when the master timer is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  SyncOutConfig This parameter can be one of the following values:
*\*\        - SHRTIM_SYNCOUT_DISABLED
*\*\        - SHRTIM_SYNCOUT_POSITIVE_PULSE
*\*\        - SHRTIM_SYNCOUT_NEGATIVE_PULSE
*\*\return None
**/
void SHRTIM_SetSyncOutConfig(SHRTIM_Module *SHRTIMx, uint32_t SyncOutConfig)
{
    MODIFY_REG(SHRTIMx->sMasterRegs.SYNCOUT, SHRTIM_SYNCOUT_SYNCOUTPUS, SyncOutConfig);
}

/**
*\*\fun  Get actual routing and conditioning of the syncout event.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return SyncOutConfig Returned value can be one of the following values:
*\*\        - SHRTIM_SYNCOUT_DISABLED
*\*\        - SHRTIM_SYNCOUT_POSITIVE_PULSE
*\*\        - SHRTIM_SYNCOUT_NEGATIVE_PULSE
**/
uint32_t SHRTIM_GetSyncOutConfig(SHRTIM_Module *SHRTIMx)
{
    return (READ_BIT(SHRTIMx->sMasterRegs.SYNCOUT, SHRTIM_SYNCOUT_SYNCOUTPUS));
}

/**
*\*\fun  Set the source and event to be sent on the SHRTIM synchronization output.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  SyncOutSrc This parameter can be one of the following values:
*\*\        - SHRTIM_SYNCOUT_SRC_MASTER_START
*\*\        - SHRTIM_SYNCOUT_SRC_MASTER_CMP1
*\*\        - SHRTIM_SYNCOUT_SRC_TIMA_START
*\*\        - SHRTIM_SYNCOUT_SRC_TIMA_CMP1
*\*\return None
**/
void SHRTIM_SetSyncOutSrc(SHRTIM_Module *SHRTIMx, uint32_t SyncOutSrc)
{
    MODIFY_REG(SHRTIMx->sMasterRegs.MCTRL, SHRTIM_MCTRL_SYNCOSRC, SyncOutSrc);
}

/**
*\*\fun  Get actual  source and event sent on the SHRTIM synchronization output.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return SyncOutSrc Returned value can be one of the following values:
*\*\        - SHRTIM_SYNCOUT_SRC_MASTER_START
*\*\        - SHRTIM_SYNCOUT_SRC_MASTER_CMP1
*\*\        - SHRTIM_SYNCOUT_SRC_TIMA_START
*\*\        - SHRTIM_SYNCOUT_SRC_TIMA_CMP1
**/
uint32_t SHRTIM_GetSyncOutSrc(SHRTIM_Module *SHRTIMx)
{
    return (READ_BIT(SHRTIMx->sMasterRegs.MCTRL, SHRTIM_MCTRL_SYNCOSRC));
}

/**
*\*\fun  Disable (temporarily) update event generation.
*\*\note Allow to temporarily disable the transfer from preload to active
*\*\      registers, whatever the selected update event. This allows to modify
*\*\      several registers in multiple timers.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timers This parameter can be a combination of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_SuspendUpdate(SHRTIM_Module *SHRTIMx, uint32_t Timers)
{
    /* clear register before applying the new value */
    CLEAR_BIT(SHRTIMx->sCommonRegs.CTRL1, ((SHRTIM_TIMER_ALL >> SHRTIM_MCTRL_MCNTEN_Pos) & SHRTIM_CTRL1_UDIS_MASK));
    SET_BIT(SHRTIMx->sCommonRegs.CTRL1, ((Timers >> SHRTIM_MCTRL_MCNTEN_Pos) & SHRTIM_CTRL1_UDIS_MASK));
}

/**
*\*\fun  Enable update event generation.
*\*\note The regular update event takes place.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timers This parameter can be a combination of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ResumeUpdate(SHRTIM_Module *SHRTIMx, uint32_t Timers)
{
    CLEAR_BIT(SHRTIMx->sCommonRegs.CTRL1, ((Timers >> SHRTIM_MCTRL_MCNTEN_Pos) & SHRTIM_CTRL1_UDIS_MASK));
}

/**
*\*\fun  Force an immediate transfer from the preload to the active register .
*\*\note Any pending update request is cancelled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timers This parameter can be a combination of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ForceUpdate(SHRTIM_Module *SHRTIMx, uint32_t Timers)
{
    SET_BIT(SHRTIMx->sCommonRegs.CTRL2, ((Timers >> SHRTIM_MCTRL_MCNTEN_Pos) & SHRTIM_CTRL2_SWUPD_MASK));
}

/**
*\*\fun  Reset the SHRTIM timer(s) counter.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timers This parameter can be a combination of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_CounterReset(SHRTIM_Module *SHRTIMx, uint32_t Timers)
{
    SET_BIT(SHRTIMx->sCommonRegs.CTRL2, (((Timers >> SHRTIM_MCTRL_MCNTEN_Pos) << SHRTIM_CTRL2_MSWCNTRST_Pos) & SHRTIM_CTRL2_SWRST_MASK));
}

/**
*\*\fun  enable the swap of the Timer Output.
*\*\note   the SHRTIM_TASET1 and SHRTIM_TARST1 are coding for the output A2,
*\*\        and the SHRTIM_TASET2 and SHRTIM_TARST2 are coding for the output A1
*\*\note   This bit is not significant when the Push-pull mode is enabled (PP = 1)
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableSwapOutputs(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);

    SET_BIT(SHRTIMx->sCommonRegs.CTRL2, (uint32_t)(SHRTIM_CTRL2_SWAPA) << iTimer);
}

/**
*\*\fun  disable the swap of the Timer Output.
*\*\note   the SHRTIM_TASET1 and SHRTIM_TARST1 are coding for the output A1,
*\*\        and the SHRTIM_TASET2 and SHRTIM_TARST2 are coding for the output A2
*\*\note   This bit is not significant when the Push-pull mode is enabled (PP = 1)
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableSwapOutputs(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);

    CLEAR_BIT(SHRTIMx->sCommonRegs.CTRL2, (SHRTIM_CTRL2_SWAPA << iTimer));
}

/**
*\*\fun  reports the Timer Outputs swap position.
*\*\note   This bit is not significant when the Push-pull mode is enabled (PP = 1)
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return
*\*\        1: SHRTIM_TASET1 and SHRTIM_TARST1 are coding for the output A2,
*\*\           SHRTIM_TASET2 and SHRTIM_TARST2 are coding for the output A1
*\*\        0: SHRTIM_TASET1 and SHRTIM_TARST1 are coding for the output A1,
*\*\           SHRTIM_TASET2 and SHRTIM_TARST2 are coding for the output A2
**/
uint32_t SHRTIM_IsEnabledSwapOutputs(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)((POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos) & 0x1FU);

    return (READ_BIT(SHRTIMx->sCommonRegs.CTRL2, (uint32_t)(SHRTIM_CTRL2_SWAPA) << iTimer) >> ((SHRTIM_CTRL2_SWAPA_Pos + iTimer)));
}

/**
*\*\fun  Enable the SHRTIM timer(s) output(s) .
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Outputs This parameter can be a combination of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\return None
**/
void SHRTIM_EnableOutput(SHRTIM_Module *SHRTIMx, uint32_t Outputs)
{
    SET_BIT(SHRTIMx->sCommonRegs.OEN, (Outputs & SHRTIM_OEN_OEN_MASK));
}

/**
*\*\fun  Disable the SHRTIM timer(s) output(s) .
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Outputs This parameter can be a combination of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\return None
**/
void SHRTIM_DisableOutput(SHRTIM_Module *SHRTIMx, uint32_t Outputs)
{
    SET_BIT(SHRTIMx->sCommonRegs.ODIS, (Outputs & SHRTIM_ODIS_ODIS_MASK));
}

/**
*\*\fun  Indicates whether the SHRTIM timer output is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\return State of TxyOEN bit in SHRTIM_OEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledOutput(SHRTIM_Module *SHRTIMx, uint32_t Output)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.OEN, Output) == Output) ? 1UL : 0UL);
}

/**
*\*\fun  Indicates whether the SHRTIM timer output is disabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\return State of TxyODIS bit in SHRTIM_OEN register (1 or 0).
**/
uint32_t SHRTIM_IsDisabledOutput(SHRTIM_Module *SHRTIMx, uint32_t Output)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.OEN, Output) == 0U) ? 1UL : 0UL);
}

/**
*\*\fun  Configure an ADC trigger.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  ADCTrigSrcReg This parameter can be one of the following values:
*\*\        - SHRTIM_ADCTRIG1_SOURCE_GROUP1
*\*\        - SHRTIM_ADCTRIG1_SOURCE_GROUP2
*\*\        - SHRTIM_ADCTRIG2_SOURCE_GROUP1
*\*\        - SHRTIM_ADCTRIG2_SOURCE_GROUP2
*\*\        - SHRTIM_ADCTRIG3_SOURCE_GROUP1
*\*\        - SHRTIM_ADCTRIG3_SOURCE_GROUP2
*\*\        - SHRTIM_ADCTRIG4_SOURCE_GROUP1
*\*\        - SHRTIM_ADCTRIG4_SOURCE_GROUP2
*\*\        - SHRTIM_ADCTRIG5_SOURCE
*\*\        - SHRTIM_ADCTRIG6_SOURCE
*\*\        - SHRTIM_ADCTRIG7_SOURCE
*\*\        - SHRTIM_ADCTRIG8_SOURCE
*\*\        - SHRTIM_ADCTRIG9_SOURCE
*\*\        - SHRTIM_ADCTRIG10_SOURCE
*\*\param  ADCTrig This parameter can be one of the following values:
*\*\        - SHRTIM_ADCTRIG_1
*\*\        - SHRTIM_ADCTRIG_2
*\*\        - SHRTIM_ADCTRIG_3
*\*\        - SHRTIM_ADCTRIG_4
*\*\        - SHRTIM_ADCTRIG_5
*\*\        - SHRTIM_ADCTRIG_6
*\*\        - SHRTIM_ADCTRIG_7
*\*\        - SHRTIM_ADCTRIG_8
*\*\        - SHRTIM_ADCTRIG_9
*\*\        - SHRTIM_ADCTRIG_10
*\*\param  Update This parameter can be one of the following values:
*\*\        - SHRTIM_ADCTRIG_UPDATE_MASTER
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_A
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_B
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_C
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_D
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_E
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_F
*\*\param  Src This parameter can be a combination of the following values:
*\*\        For ADC trigger 1 group 1 and ADC trigger 3 group 1:
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBRSTRO
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TARSTRO
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TAPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TACMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TACMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TACMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TACMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TACMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_MPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_MCMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_MCMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_MCMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_MCMP1
*\*\        For ADC trigger 1 group 2 and ADC trigger 3 group 2:
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_EXEV5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_EXEV4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_EXEV3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_EXEV2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_EXEV1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFRSTRO
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TEPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TECMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TECMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TECMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TECMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TECMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP1
*\*\        For ADC trigger 2 group 1 and ADC trigger 4  group 1:
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCRSTRO
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TAPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TACMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TACMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TACMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TACMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TACMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_MPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_MCMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_MCMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_MCMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_MCMP1
*\*\        For ADC trigger 2 group 2 and ADC trigger 4  group 2:
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_EXEV10
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_EXEV9
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_EXEV8
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_EXEV7
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_EXEV6
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TERSTRO
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TECMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TECMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TECMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TECMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TECMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDRSTRO
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP1
*\*\        For ADC trigger 5, ADC trigger 7 and ADC trigger 9 this parameter
*\*\        can be one of the following values:
*\*\         - SHRTIM_ADTG579_MCMP1
*\*\         - SHRTIM_ADTG579_MCMP2
*\*\         - SHRTIM_ADTG579_MCMP3
*\*\         - SHRTIM_ADTG579_MCMP4
*\*\         - SHRTIM_ADTG579_MPRD
*\*\         - SHRTIM_ADTG579_EXEV1
*\*\         - SHRTIM_ADTG579_EXEV2
*\*\         - SHRTIM_ADTG579_EXEV3
*\*\         - SHRTIM_ADTG579_EXEV4
*\*\         - SHRTIM_ADTG579_EXEV5
*\*\         - SHRTIM_ADTG579_TACMP1
*\*\         - SHRTIM_ADTG579_TACMP2
*\*\         - SHRTIM_ADTG579_TACMP3
*\*\         - SHRTIM_ADTG579_TACMP4
*\*\         - SHRTIM_ADTG579_TACMP5
*\*\         - SHRTIM_ADTG579_TAPRD
*\*\         - SHRTIM_ADTG579_TARSTRO
*\*\         - SHRTIM_ADTG579_TBCMP1
*\*\         - SHRTIM_ADTG579_TBCMP2
*\*\         - SHRTIM_ADTG579_TBCMP3
*\*\         - SHRTIM_ADTG579_TBCMP4
*\*\         - SHRTIM_ADTG579_TBCMP5
*\*\         - SHRTIM_ADTG579_TBPRD
*\*\         - SHRTIM_ADTG579_TBRSTRO
*\*\         - SHRTIM_ADTG579_TCCMP1
*\*\         - SHRTIM_ADTG579_TCCMP2
*\*\         - SHRTIM_ADTG579_TCCMP3
*\*\         - SHRTIM_ADTG579_TCCMP4
*\*\         - SHRTIM_ADTG579_TCCMP5
*\*\         - SHRTIM_ADTG579_TCPRD
*\*\         - SHRTIM_ADTG579_TDCMP1
*\*\         - SHRTIM_ADTG579_TDCMP2
*\*\         - SHRTIM_ADTG579_TDCMP3
*\*\         - SHRTIM_ADTG579_TDCMP4
*\*\         - SHRTIM_ADTG579_TDCMP5
*\*\         - SHRTIM_ADTG579_TDPRD
*\*\         - SHRTIM_ADTG579_TECMP1
*\*\         - SHRTIM_ADTG579_TECMP2
*\*\         - SHRTIM_ADTG579_TECMP3
*\*\         - SHRTIM_ADTG579_TECMP4
*\*\         - SHRTIM_ADTG579_TECMP5
*\*\         - SHRTIM_ADTG579_TEPRD
*\*\         - SHRTIM_ADTG579_TFCMP1
*\*\         - SHRTIM_ADTG579_TFCMP2
*\*\         - SHRTIM_ADTG579_TFCMP3
*\*\         - SHRTIM_ADTG579_TFCMP4
*\*\         - SHRTIM_ADTG579_TFCMP5
*\*\         - SHRTIM_ADTG579_TFPRD
*\*\         - SHRTIM_ADTG579_TFRSTRO
*\*\        For ADC trigger 6, ADC trigger 8 and ADC trigger 10 this parameter
*\*\        can be one of the following values:
*\*\         - SHRTIM_ADTG6810_MCMP1
*\*\         - SHRTIM_ADTG6810_MCMP2
*\*\         - SHRTIM_ADTG6810_MCMP3
*\*\         - SHRTIM_ADTG6810_MCMP4
*\*\         - SHRTIM_ADTG6810_MPRD
*\*\         - SHRTIM_ADTG6810_EXEV6
*\*\         - SHRTIM_ADTG6810_EXEV7
*\*\         - SHRTIM_ADTG6810_EXEV8
*\*\         - SHRTIM_ADTG6810_EXEV9
*\*\         - SHRTIM_ADTG6810_EXEV10
*\*\         - SHRTIM_ADTG6810_TACMP1
*\*\         - SHRTIM_ADTG6810_TACMP2
*\*\         - SHRTIM_ADTG6810_TACMP3
*\*\         - SHRTIM_ADTG6810_TACMP4
*\*\         - SHRTIM_ADTG6810_TACMP5
*\*\         - SHRTIM_ADTG6810_TAPRD
*\*\         - SHRTIM_ADTG6810_TBCMP1
*\*\         - SHRTIM_ADTG6810_TBCMP2
*\*\         - SHRTIM_ADTG6810_TBCMP3
*\*\         - SHRTIM_ADTG6810_TBCMP4
*\*\         - SHRTIM_ADTG6810_TBCMP5
*\*\         - SHRTIM_ADTG6810_TBPRD
*\*\         - SHRTIM_ADTG6810_TCCMP1
*\*\         - SHRTIM_ADTG6810_TCCMP2
*\*\         - SHRTIM_ADTG6810_TCCMP3
*\*\         - SHRTIM_ADTG6810_TCCMP4
*\*\         - SHRTIM_ADTG6810_TCCMP5
*\*\         - SHRTIM_ADTG6810_TCPRD
*\*\         - SHRTIM_ADTG6810_TCRSTRO
*\*\         - SHRTIM_ADTG6810_TDCMP1
*\*\         - SHRTIM_ADTG6810_TDCMP2
*\*\         - SHRTIM_ADTG6810_TDCMP3
*\*\         - SHRTIM_ADTG6810_TDCMP4
*\*\         - SHRTIM_ADTG6810_TDCMP5
*\*\         - SHRTIM_ADTG6810_TDPRD
*\*\         - SHRTIM_ADTG6810_TDRSTRO
*\*\         - SHRTIM_ADTG6810_TECMP1
*\*\         - SHRTIM_ADTG6810_TECMP2
*\*\         - SHRTIM_ADTG6810_TECMP3
*\*\         - SHRTIM_ADTG6810_TECMP4
*\*\         - SHRTIM_ADTG6810_TECMP5
*\*\         - SHRTIM_ADTG6810_TERSTRO
*\*\         - SHRTIM_ADTG6810_TFCMP1
*\*\         - SHRTIM_ADTG6810_TFCMP2
*\*\         - SHRTIM_ADTG6810_TFCMP3
*\*\         - SHRTIM_ADTG6810_TFCMP4
*\*\         - SHRTIM_ADTG6810_TFCMP5
*\*\         - SHRTIM_ADTG6810_TFPRD
*\*\return None
**/

void SHRTIM_ConfigADCTrig(SHRTIM_Module *SHRTIMx, uint32_t ADCTrigSrcReg, uint32_t ADCTrig, uint32_t Update, uint32_t Src)
{
    __IO uint32_t *padcur = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.CTRL1) +
                            REG_OFFSET_TAB_ADTGUPD[ADCTrig]));
    __IO uint32_t *padcer = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.ADTG1SRC1) +
                            REG_OFFSET_TAB_ADTGSRC[ADCTrigSrcReg]));
    MODIFY_REG(*padcur, REG_MASK_TAB_ADTGUPD[ADCTrig], (Update << REG_SHIFT_TAB_ADTGUPD[ADCTrig]));
    MODIFY_REG(*padcer, REG_MASK_TAB_ADTGSRC[ADCTrigSrcReg], (Src << REG_SHIFT_TAB_ADTGSRC[ADCTrigSrcReg]));
}

/**
*\*\fun  Associate the ADCx trigger to a timer triggering the update of the SHRTIM_ADTGxSRCy register.
*\*\note When the preload is disabled in the source timer, the SHRTIM_ADTGxSRCy
 *       registers are not preloaded either: a write access will result in an
 *       immediate update of the trigger source.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  ADCTrig This parameter can be one of the following values:
*\*\        - SHRTIM_ADCTRIG_1
*\*\        - SHRTIM_ADCTRIG_2
*\*\        - SHRTIM_ADCTRIG_3
*\*\        - SHRTIM_ADCTRIG_4
*\*\        - SHRTIM_ADCTRIG_5
*\*\        - SHRTIM_ADCTRIG_6
*\*\        - SHRTIM_ADCTRIG_7
*\*\        - SHRTIM_ADCTRIG_8
*\*\        - SHRTIM_ADCTRIG_9
*\*\        - SHRTIM_ADCTRIG_10
*\*\param  Update This parameter can be one of the following values:
*\*\        - SHRTIM_ADCTRIG_UPDATE_MASTER
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_A
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_B
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_C
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_D
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_E
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_F
*\*\return None
**/
void SHRTIM_SetADCTrigUpdate(SHRTIM_Module *SHRTIMx, uint32_t ADCTrig, uint32_t Update)
{
    __IO uint32_t *preg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.CTRL1) +
                                            REG_OFFSET_TAB_ADTGUPD[ADCTrig]));
    MODIFY_REG(*preg, REG_MASK_TAB_ADTGUPD[ADCTrig], (Update << REG_SHIFT_TAB_ADTGUPD[ADCTrig]));
}

/**
*\*\fun  Get the source timer triggering the update of the SHRTIM_ADTGxSRCy register.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  ADCTrig This parameter can be one of the following values:
*\*\        - SHRTIM_ADCTRIG_1
*\*\        - SHRTIM_ADCTRIG_2
*\*\        - SHRTIM_ADCTRIG_3
*\*\        - SHRTIM_ADCTRIG_4
*\*\        - SHRTIM_ADCTRIG_5
*\*\        - SHRTIM_ADCTRIG_6
*\*\        - SHRTIM_ADCTRIG_7
*\*\        - SHRTIM_ADCTRIG_8
*\*\        - SHRTIM_ADCTRIG_9
*\*\        - SHRTIM_ADCTRIG_10
*\*\return Update Returned value can be one of the following values:
*\*\        - SHRTIM_ADCTRIG_UPDATE_MASTER
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_A
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_B
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_C
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_D
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_E
*\*\        - SHRTIM_ADCTRIG_UPDATE_TIMER_F
**/
uint32_t SHRTIM_GetADCTrigUpdate(SHRTIM_Module *SHRTIMx, uint32_t ADCTrig)
{
    const __IO uint32_t *preg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.CTRL1) +
                                REG_OFFSET_TAB_ADTGUPD[ADCTrig]));
    return (READ_BIT(*preg, (REG_MASK_TAB_ADTGUPD[ADCTrig])) >> REG_SHIFT_TAB_ADTGUPD[ADCTrig]);
}

/**
*\*\fun  Specify which events (timer events and/or external events) are used as triggers for ADC conversion.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  ADCTrigSrcReg This parameter can be one of the following values:
*\*\         - SHRTIM_ADCTRIG1_SOURCE_GROUP1
*\*\         - SHRTIM_ADCTRIG1_SOURCE_GROUP2
*\*\         - SHRTIM_ADCTRIG2_SOURCE_GROUP1
*\*\         - SHRTIM_ADCTRIG2_SOURCE_GROUP2
*\*\         - SHRTIM_ADCTRIG3_SOURCE_GROUP1
*\*\         - SHRTIM_ADCTRIG3_SOURCE_GROUP2
*\*\         - SHRTIM_ADCTRIG4_SOURCE_GROUP1
*\*\         - SHRTIM_ADCTRIG4_SOURCE_GROUP2
*\*\         - SHRTIM_ADCTRIG5_SOURCE
*\*\         - SHRTIM_ADCTRIG6_SOURCE
*\*\         - SHRTIM_ADCTRIG7_SOURCE
*\*\         - SHRTIM_ADCTRIG8_SOURCE
*\*\         - SHRTIM_ADCTRIG9_SOURCE
*\*\         - SHRTIM_ADCTRIG10_SOURCE
*\*\param  Src This parameter can be a combination of the following values:
*\*\        For ADC trigger 1 (include group 1 and group2) and ADC trigger 3 (include group 1 and group2):
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBRSTRO
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TARSTRO
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TAPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TACMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TACMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TACMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TACMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TACMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_MPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_MCMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_MCMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_MCMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_MCMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_EXEV5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_EXEV4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_EXEV3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_EXEV2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_EXEV1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFRSTRO
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TEPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TECMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TECMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TECMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TECMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TECMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP1
*\*\        For ADC trigger 2(include group 1 and group2) and ADC trigger 4 (include group 1 and group2):
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCRSTRO
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TAPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TACMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TACMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TACMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TACMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TACMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_MPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_MCMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_MCMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_MCMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_MCMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_EXEV10
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_EXEV9
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_EXEV8
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_EXEV7
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_EXEV6
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TERSTRO
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TECMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TECMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TECMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TECMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TECMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDRSTRO
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP1
*\*\        For ADC trigger 5, ADC trigger 7 and ADC trigger 9 this parameter
*\*\        can be one of the following values:
*\*\         - SHRTIM_ADTG579_MCMP1
*\*\         - SHRTIM_ADTG579_MCMP2
*\*\         - SHRTIM_ADTG579_MCMP3
*\*\         - SHRTIM_ADTG579_MCMP4
*\*\         - SHRTIM_ADTG579_MPRD
*\*\         - SHRTIM_ADTG579_EXEV1
*\*\         - SHRTIM_ADTG579_EXEV2
*\*\         - SHRTIM_ADTG579_EXEV3
*\*\         - SHRTIM_ADTG579_EXEV4
*\*\         - SHRTIM_ADTG579_EXEV5
*\*\         - SHRTIM_ADTG579_TACMP1
*\*\         - SHRTIM_ADTG579_TACMP2
*\*\         - SHRTIM_ADTG579_TACMP3
*\*\         - SHRTIM_ADTG579_TACMP4
*\*\         - SHRTIM_ADTG579_TACMP5
*\*\         - SHRTIM_ADTG579_TAPRD
*\*\         - SHRTIM_ADTG579_TARSTRO
*\*\         - SHRTIM_ADTG579_TBCMP1
*\*\         - SHRTIM_ADTG579_TBCMP2
*\*\         - SHRTIM_ADTG579_TBCMP3
*\*\         - SHRTIM_ADTG579_TBCMP4
*\*\         - SHRTIM_ADTG579_TBCMP5
*\*\         - SHRTIM_ADTG579_TBPRD
*\*\         - SHRTIM_ADTG579_TBRSTRO
*\*\         - SHRTIM_ADTG579_TCCMP1
*\*\         - SHRTIM_ADTG579_TCCMP2
*\*\         - SHRTIM_ADTG579_TCCMP3
*\*\         - SHRTIM_ADTG579_TCCMP4
*\*\         - SHRTIM_ADTG579_TCCMP5
*\*\         - SHRTIM_ADTG579_TCPRD
*\*\         - SHRTIM_ADTG579_TDCMP1
*\*\         - SHRTIM_ADTG579_TDCMP2
*\*\         - SHRTIM_ADTG579_TDCMP3
*\*\         - SHRTIM_ADTG579_TDCMP4
*\*\         - SHRTIM_ADTG579_TDCMP5
*\*\         - SHRTIM_ADTG579_TDPRD
*\*\         - SHRTIM_ADTG579_TECMP1
*\*\         - SHRTIM_ADTG579_TECMP2
*\*\         - SHRTIM_ADTG579_TECMP3
*\*\         - SHRTIM_ADTG579_TECMP4
*\*\         - SHRTIM_ADTG579_TECMP5
*\*\         - SHRTIM_ADTG579_TEPRD
*\*\         - SHRTIM_ADTG579_TFCMP1
*\*\         - SHRTIM_ADTG579_TFCMP2
*\*\         - SHRTIM_ADTG579_TFCMP3
*\*\         - SHRTIM_ADTG579_TFCMP4
*\*\         - SHRTIM_ADTG579_TFCMP5
*\*\         - SHRTIM_ADTG579_TFPRD
*\*\         - SHRTIM_ADTG579_TFRSTRO
*\*\        For ADC trigger 6, ADC trigger 8 and ADC trigger 10 this parameter
*\*\        can be one of the following values:
*\*\         - SHRTIM_ADTG6810_MCMP1
*\*\         - SHRTIM_ADTG6810_MCMP2
*\*\         - SHRTIM_ADTG6810_MCMP3
*\*\         - SHRTIM_ADTG6810_MCMP4
*\*\         - SHRTIM_ADTG6810_MPRD
*\*\         - SHRTIM_ADTG6810_EXEV6
*\*\         - SHRTIM_ADTG6810_EXEV7
*\*\         - SHRTIM_ADTG6810_EXEV8
*\*\         - SHRTIM_ADTG6810_EXEV9
*\*\         - SHRTIM_ADTG6810_EXEV10
*\*\         - SHRTIM_ADTG6810_TACMP1
*\*\         - SHRTIM_ADTG6810_TACMP2
*\*\         - SHRTIM_ADTG6810_TACMP3
*\*\         - SHRTIM_ADTG6810_TACMP4
*\*\         - SHRTIM_ADTG6810_TACMP5
*\*\         - SHRTIM_ADTG6810_TAPRD
*\*\         - SHRTIM_ADTG6810_TBCMP1
*\*\         - SHRTIM_ADTG6810_TBCMP2
*\*\         - SHRTIM_ADTG6810_TBCMP3
*\*\         - SHRTIM_ADTG6810_TBCMP4
*\*\         - SHRTIM_ADTG6810_TBCMP5
*\*\         - SHRTIM_ADTG6810_TBPRD
*\*\         - SHRTIM_ADTG6810_TCCMP1
*\*\         - SHRTIM_ADTG6810_TCCMP2
*\*\         - SHRTIM_ADTG6810_TCCMP3
*\*\         - SHRTIM_ADTG6810_TCCMP4
*\*\         - SHRTIM_ADTG6810_TCCMP5
*\*\         - SHRTIM_ADTG6810_TCPRD
*\*\         - SHRTIM_ADTG6810_TCRSTRO
*\*\         - SHRTIM_ADTG6810_TDCMP1
*\*\         - SHRTIM_ADTG6810_TDCMP2
*\*\         - SHRTIM_ADTG6810_TDCMP3
*\*\         - SHRTIM_ADTG6810_TDCMP4
*\*\         - SHRTIM_ADTG6810_TDCMP5
*\*\         - SHRTIM_ADTG6810_TDPRD
*\*\         - SHRTIM_ADTG6810_TDRSTRO
*\*\         - SHRTIM_ADTG6810_TECMP1
*\*\         - SHRTIM_ADTG6810_TECMP2
*\*\         - SHRTIM_ADTG6810_TECMP3
*\*\         - SHRTIM_ADTG6810_TECMP4
*\*\         - SHRTIM_ADTG6810_TECMP5
*\*\         - SHRTIM_ADTG6810_TERSTRO
*\*\         - SHRTIM_ADTG6810_TFCMP1
*\*\         - SHRTIM_ADTG6810_TFCMP2
*\*\         - SHRTIM_ADTG6810_TFCMP3
*\*\         - SHRTIM_ADTG6810_TFCMP4
*\*\         - SHRTIM_ADTG6810_TFCMP5
*\*\         - SHRTIM_ADTG6810_TFPRD
*\*\return None
**/
void SHRTIM_SetADCTrigSrc(SHRTIM_Module *SHRTIMx, uint32_t ADCTrigSrcReg, uint32_t Src)
{
    __IO uint32_t *preg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.ADTG1SRC1) +
                                            REG_OFFSET_TAB_ADTGSRC[ADCTrigSrcReg]));
    MODIFY_REG(*preg, REG_MASK_TAB_ADTGSRC[ADCTrigSrcReg], (Src << REG_SHIFT_TAB_ADTGSRC[ADCTrigSrcReg]));
}

/**
*\*\fun  Indicate which events (timer events and/or external events) are currently used as triggers for ADC conversion.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  ADCTrigSrcReg This parameter can be one of the following values:
*\*\         - SHRTIM_ADCTRIG1_SOURCE_GROUP1
*\*\         - SHRTIM_ADCTRIG1_SOURCE_GROUP2
*\*\         - SHRTIM_ADCTRIG2_SOURCE_GROUP1
*\*\         - SHRTIM_ADCTRIG2_SOURCE_GROUP2
*\*\         - SHRTIM_ADCTRIG3_SOURCE_GROUP1
*\*\         - SHRTIM_ADCTRIG3_SOURCE_GROUP2
*\*\         - SHRTIM_ADCTRIG4_SOURCE_GROUP1
*\*\         - SHRTIM_ADCTRIG4_SOURCE_GROUP2
*\*\         - SHRTIM_ADCTRIG5_SOURCE
*\*\         - SHRTIM_ADCTRIG6_SOURCE
*\*\         - SHRTIM_ADCTRIG7_SOURCE
*\*\         - SHRTIM_ADCTRIG8_SOURCE
*\*\         - SHRTIM_ADCTRIG9_SOURCE
*\*\         - SHRTIM_ADCTRIG10_SOURCE
*\*\return
*\*\        For ADC trigger 1 (include group 1 and group2) and ADC trigger 3 (include group 1 and group2):
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TCCMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBRSTRO
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TBCMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TARSTRO
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TAPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TACMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TACMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TACMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TACMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_TACMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_MPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_MCMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_MCMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_MCMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP1_MCMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_EXEV5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_EXEV4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_EXEV3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_EXEV2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_EXEV1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFRSTRO
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TFCMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TEPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TECMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TECMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TECMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TECMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TECMP1
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDPRD
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP5
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP4
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP3
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP2
*\*\         - SHRTIM_ADTG13_SOURCE_GROUP2_TDCMP1
*\*\        For ADC trigger 2(include group 1 and group2) and ADC trigger 4 (include group 1 and group2):
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCRSTRO
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TCCMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TBCMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TAPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TACMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TACMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TACMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TACMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_TACMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_MPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_MCMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_MCMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_MCMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP1_MCMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_EXEV10
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_EXEV9
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_EXEV8
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_EXEV7
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_EXEV6
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TFCMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TERSTRO
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TECMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TECMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TECMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TECMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TECMP1
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDRSTRO
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDPRD
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP5
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP4
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP3
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP2
*\*\         - SHRTIM_ADTG24_SOURCE_GROUP2_TDCMP1
*\*\        For ADC trigger 5, ADC trigger 7 and ADC trigger 9
*\*\        can be one of the following values:
*\*\         - SHRTIM_ADTG579_MCMP1
*\*\         - SHRTIM_ADTG579_MCMP2
*\*\         - SHRTIM_ADTG579_MCMP3
*\*\         - SHRTIM_ADTG579_MCMP4
*\*\         - SHRTIM_ADTG579_MPRD
*\*\         - SHRTIM_ADTG579_EXEV1
*\*\         - SHRTIM_ADTG579_EXEV2
*\*\         - SHRTIM_ADTG579_EXEV3
*\*\         - SHRTIM_ADTG579_EXEV4
*\*\         - SHRTIM_ADTG579_EXEV5
*\*\         - SHRTIM_ADTG579_TACMP1
*\*\         - SHRTIM_ADTG579_TACMP2
*\*\         - SHRTIM_ADTG579_TACMP3
*\*\         - SHRTIM_ADTG579_TACMP4
*\*\         - SHRTIM_ADTG579_TACMP5
*\*\         - SHRTIM_ADTG579_TAPRD
*\*\         - SHRTIM_ADTG579_TARSTRO
*\*\         - SHRTIM_ADTG579_TBCMP1
*\*\         - SHRTIM_ADTG579_TBCMP2
*\*\         - SHRTIM_ADTG579_TBCMP3
*\*\         - SHRTIM_ADTG579_TBCMP4
*\*\         - SHRTIM_ADTG579_TBCMP5
*\*\         - SHRTIM_ADTG579_TBPRD
*\*\         - SHRTIM_ADTG579_TBRSTRO
*\*\         - SHRTIM_ADTG579_TCCMP1
*\*\         - SHRTIM_ADTG579_TCCMP2
*\*\         - SHRTIM_ADTG579_TCCMP3
*\*\         - SHRTIM_ADTG579_TCCMP4
*\*\         - SHRTIM_ADTG579_TCCMP5
*\*\         - SHRTIM_ADTG579_TCPRD
*\*\         - SHRTIM_ADTG579_TDCMP1
*\*\         - SHRTIM_ADTG579_TDCMP2
*\*\         - SHRTIM_ADTG579_TDCMP3
*\*\         - SHRTIM_ADTG579_TDCMP4
*\*\         - SHRTIM_ADTG579_TDCMP5
*\*\         - SHRTIM_ADTG579_TDPRD
*\*\         - SHRTIM_ADTG579_TECMP1
*\*\         - SHRTIM_ADTG579_TECMP2
*\*\         - SHRTIM_ADTG579_TECMP3
*\*\         - SHRTIM_ADTG579_TECMP4
*\*\         - SHRTIM_ADTG579_TECMP5
*\*\         - SHRTIM_ADTG579_TEPRD
*\*\         - SHRTIM_ADTG579_TFCMP1
*\*\         - SHRTIM_ADTG579_TFCMP2
*\*\         - SHRTIM_ADTG579_TFCMP3
*\*\         - SHRTIM_ADTG579_TFCMP4
*\*\         - SHRTIM_ADTG579_TFCMP5
*\*\         - SHRTIM_ADTG579_TFPRD
*\*\         - SHRTIM_ADTG579_TFRSTRO
*\*\        For ADC trigger 6, ADC trigger 8 and ADC trigger 10
*\*\        can be one of the following values:
*\*\         - SHRTIM_ADTG6810_MCMP1
*\*\         - SHRTIM_ADTG6810_MCMP2
*\*\         - SHRTIM_ADTG6810_MCMP3
*\*\         - SHRTIM_ADTG6810_MCMP4
*\*\         - SHRTIM_ADTG6810_MPRD
*\*\         - SHRTIM_ADTG6810_EXEV6
*\*\         - SHRTIM_ADTG6810_EXEV7
*\*\         - SHRTIM_ADTG6810_EXEV8
*\*\         - SHRTIM_ADTG6810_EXEV9
*\*\         - SHRTIM_ADTG6810_EXEV10
*\*\         - SHRTIM_ADTG6810_TACMP1
*\*\         - SHRTIM_ADTG6810_TACMP2
*\*\         - SHRTIM_ADTG6810_TACMP3
*\*\         - SHRTIM_ADTG6810_TACMP4
*\*\         - SHRTIM_ADTG6810_TACMP5
*\*\         - SHRTIM_ADTG6810_TAPRD
*\*\         - SHRTIM_ADTG6810_TBCMP1
*\*\         - SHRTIM_ADTG6810_TBCMP2
*\*\         - SHRTIM_ADTG6810_TBCMP3
*\*\         - SHRTIM_ADTG6810_TBCMP4
*\*\         - SHRTIM_ADTG6810_TBCMP5
*\*\         - SHRTIM_ADTG6810_TBPRD
*\*\         - SHRTIM_ADTG6810_TCCMP1
*\*\         - SHRTIM_ADTG6810_TCCMP2
*\*\         - SHRTIM_ADTG6810_TCCMP3
*\*\         - SHRTIM_ADTG6810_TCCMP4
*\*\         - SHRTIM_ADTG6810_TCCMP5
*\*\         - SHRTIM_ADTG6810_TCPRD
*\*\         - SHRTIM_ADTG6810_TCRSTRO
*\*\         - SHRTIM_ADTG6810_TDCMP1
*\*\         - SHRTIM_ADTG6810_TDCMP2
*\*\         - SHRTIM_ADTG6810_TDCMP3
*\*\         - SHRTIM_ADTG6810_TDCMP4
*\*\         - SHRTIM_ADTG6810_TDCMP5
*\*\         - SHRTIM_ADTG6810_TDPRD
*\*\         - SHRTIM_ADTG6810_TDRSTRO
*\*\         - SHRTIM_ADTG6810_TECMP1
*\*\         - SHRTIM_ADTG6810_TECMP2
*\*\         - SHRTIM_ADTG6810_TECMP3
*\*\         - SHRTIM_ADTG6810_TECMP4
*\*\         - SHRTIM_ADTG6810_TECMP5
*\*\         - SHRTIM_ADTG6810_TERSTRO
*\*\         - SHRTIM_ADTG6810_TFCMP1
*\*\         - SHRTIM_ADTG6810_TFCMP2
*\*\         - SHRTIM_ADTG6810_TFCMP3
*\*\         - SHRTIM_ADTG6810_TFCMP4
*\*\         - SHRTIM_ADTG6810_TFCMP5
*\*\         - SHRTIM_ADTG6810_TFPRD
**/
uint32_t SHRTIM_GetADCTrigSrc(SHRTIM_Module *SHRTIMx, uint32_t ADCTrigSrcReg)
{
    const __IO uint32_t *preg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.ADTG1SRC1) +
                                REG_OFFSET_TAB_ADTGSRC[ADCTrigSrcReg]));
    return (READ_BIT(*preg, (REG_MASK_TAB_ADTGSRC[ADCTrigSrcReg])) >> REG_SHIFT_TAB_ADTGSRC[ADCTrigSrcReg]);
}

/**
*\*\fun  Select the ADC post scaler.
*\*\note This function allows to adjust each ADC trigger rate individually.
*\*\note In center-aligned mode, the ADC trigger rate is also dependent on
 *       ADCROM[1:0] bitfield, programmed in the source timer
 *       (see function SHRTIM_TIM_SetADCRollOverMode)
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  ADCTrig This parameter can be one of the following values:
*\*\        - SHRTIM_ADCTRIG_1
*\*\        - SHRTIM_ADCTRIG_2
*\*\        - SHRTIM_ADCTRIG_3
*\*\        - SHRTIM_ADCTRIG_4
*\*\        - SHRTIM_ADCTRIG_5
*\*\        - SHRTIM_ADCTRIG_6
*\*\        - SHRTIM_ADCTRIG_7
*\*\        - SHRTIM_ADCTRIG_8
*\*\        - SHRTIM_ADCTRIG_9
*\*\        - SHRTIM_ADCTRIG_10
*\*\param  PostScaler This parameter can be a number between Min_Data=0 and Max_Data=31
*\*\return None
**/
void SHRTIM_SetADCPostScaler(SHRTIM_Module *SHRTIMx, uint32_t ADCTrig, uint32_t PostScaler)
{
    uint64_t mask = (uint64_t)(SHRTIM_ADCPSC1_ADC1PSC) << (REG_OFFSET_TAB_ADCPSx[ADCTrig]);
    uint64_t ratio = (uint64_t)(PostScaler) << (REG_OFFSET_TAB_ADCPSx[ADCTrig]);

    MODIFY_REG(SHRTIMx->sCommonRegs.ADCPSC1, (uint32_t)mask, (uint32_t)ratio);
    MODIFY_REG(SHRTIMx->sCommonRegs.ADCPSC2, (uint32_t)(mask >> 32U), (uint32_t)(ratio >> 32U));
}

/**
*\*\fun  Get the selected ADC post scaler.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  ADCTrig This parameter can be one of the following values:
*\*\        - SHRTIM_ADCTRIG_1
*\*\        - SHRTIM_ADCTRIG_2
*\*\        - SHRTIM_ADCTRIG_3
*\*\        - SHRTIM_ADCTRIG_4
*\*\        - SHRTIM_ADCTRIG_5
*\*\        - SHRTIM_ADCTRIG_6
*\*\        - SHRTIM_ADCTRIG_7
*\*\        - SHRTIM_ADCTRIG_8
*\*\        - SHRTIM_ADCTRIG_9
*\*\        - SHRTIM_ADCTRIG_10
*\*\return  PostScaler This parameter can be a number between Min_Data=0 and Max_Data=31
**/
uint32_t SHRTIM_GetADCPostScaler(SHRTIM_Module *SHRTIMx, uint32_t ADCTrig)
{

    uint32_t reg1 = READ_REG(SHRTIMx->sCommonRegs.ADCPSC1);
    uint32_t reg2 = READ_REG(SHRTIMx->sCommonRegs.ADCPSC2);

    uint64_t mask = (uint64_t)(SHRTIM_ADCPSC1_ADC1PSC) << (REG_OFFSET_TAB_ADCPSx[ADCTrig]);
    uint64_t ratio = (uint64_t)(reg1) | ((uint64_t)(reg2) << 32U);

    return (uint32_t)((ratio & mask) >> (REG_OFFSET_TAB_ADCPSx[ADCTrig]));
}

/**
*\*\fun  Enable timer(s) counter.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timers This parameter can be a combination of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_CounterEnable(SHRTIM_Module *SHRTIMx, uint32_t Timers)
{
    SET_BIT(SHRTIMx->sMasterRegs.MCTRL, Timers);
}

/**
*\*\fun  Disable timer(s) counter.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timers This parameter can be a combination of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_CounterDisable(SHRTIM_Module *SHRTIMx, uint32_t Timers)
{
    CLEAR_BIT(SHRTIMx->sMasterRegs.MCTRL, Timers);
}

/**
*\*\fun  Indicate whether the timer counter is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MCNTEN or TxCNTEN bit SHRTIM_MCTRL register (1 or 0).
**/
uint32_t SHRTIM_TIM_IsCounterEnabled(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    return ((READ_BIT(SHRTIMx->sMasterRegs.MCTRL, Timer) == (Timer)) ? 1UL : 0UL);
}

/**
*\*\fun  Set the timer clock prescaler ratio.
*\*\note The counter clock equivalent frequency (CK_CNT) is equal to fHRCK / 2^CKPSC[2:0].
*\*\note The prescaling ratio cannot be modified once the timer counter is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Prescaler This parameter can be one of the following values:
*\*\        - SHRTIM_PRESCALERRATIO_MUL32
*\*\        - SHRTIM_PRESCALERRATIO_MUL16
*\*\        - SHRTIM_PRESCALERRATIO_MUL8
*\*\        - SHRTIM_PRESCALERRATIO_MUL4
*\*\        - SHRTIM_PRESCALERRATIO_MUL2
*\*\        - SHRTIM_PRESCALERRATIO_DIV1
*\*\        - SHRTIM_PRESCALERRATIO_DIV2
*\*\        - SHRTIM_PRESCALERRATIO_DIV4
*\*\return None
**/
void SHRTIM_TIM_SetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Prescaler)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_MCTRL_CKPSC, Prescaler);
}

/**
*\*\fun  Get the timer clock prescaler ratio
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return Prescaler Returned value can be one of the following values:
*\*\        - SHRTIM_PRESCALERRATIO_MUL32
*\*\        - SHRTIM_PRESCALERRATIO_MUL16
*\*\        - SHRTIM_PRESCALERRATIO_MUL8
*\*\        - SHRTIM_PRESCALERRATIO_MUL4
*\*\        - SHRTIM_PRESCALERRATIO_MUL2
*\*\        - SHRTIM_PRESCALERRATIO_DIV1
*\*\        - SHRTIM_PRESCALERRATIO_DIV2
*\*\        - SHRTIM_PRESCALERRATIO_DIV4
**/
uint32_t SHRTIM_TIM_GetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_MCTRL_CKPSC));
}

/**
*\*\fun  Set the counter operating mode mode (single-shot, continuous or re-triggerable).
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_MODE_CONTINUOUS
*\*\        - SHRTIM_MODE_SINGLESHOT
*\*\        - SHRTIM_MODE_RETRIGGERABLE
*\*\return None
**/
void SHRTIM_TIM_SetCounterMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, (SHRTIM_TXCTRL_RTG | SHRTIM_MCTRL_CONT), Mode);
}

/**
*\*\fun  Get the counter operating mode mode
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return Mode Returned value can be one of the following values:
*\*\        - SHRTIM_MODE_CONTINUOUS
*\*\        - SHRTIM_MODE_SINGLESHOT
*\*\        - SHRTIM_MODE_RETRIGGERABLE
**/
uint32_t SHRTIM_TIM_GetCounterMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, (SHRTIM_MCTRL_RTG | SHRTIM_MCTRL_CONT)));
}

/**
*\*\fun  Enable the half duty-cycle mode.
*\*\note When the half mode is enabled, SHRTIM_MCMP1DAT (or SHRTIM_TXCMP1xDAT)
 *       active register is automatically updated with SHRTIM_MPRD/2
 *       (or SHRTIM_TXPRD/2) value when SHRTIM_MPRD (or SHRTIM_TXPRD) register is written.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_EnableHalfMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MCTRL_HLF);
}

/**
*\*\fun  Disable the half duty-cycle mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_DisableHalfMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_MCTRL_HLF);
    CLEAR_BIT(*pReg, SHRTIM_MCTRL_ILV << REG_SHIFT_TAB_ILV[iTimer]);
}

/**
*\*\fun  Indicate whether half duty-cycle mode is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of HLF bit to 1 in SHRTIM_MCTRL or SHRTIM_TxCTRL register (1 or 0).
**/
uint32_t SHRTIM_TIM_IsEnabledHalfMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MCTRL_HLF) == (SHRTIM_MCTRL_HLF)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the Re-Syncronisation Update.
*\*\note   The update coming from adjacent timers (when MUEN, TAUEN, TBUEN, TCUEN, TDUEN, TEUEN, TFUEN bit is set)
*\*\        or from a software update (TxSWUPD bit) is taken into account on the following reset/roll-over.
*\*\note   SHRTIM_ForceUpdate must be called prior programming the syncrhonization mode to force
*\*\        immediate update of the slave timer registers.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_EnableResyncUpdate(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXCTRL_RSYNCUPD);
    /* This bit is significant only when UPDGAT[3:0] = 0000, it is ignored otherwise */
}

/**
*\*\fun  Disable the Re-Syncronisation Update.
*\*\note   The update coming from adjacent timers (when MUEN, TAUEN, TBUEN, TCUEN, TDUEN, TEUEN, TFUEN bit is set)
*\*\        or from a software update (TxSWUPD bit) is taken into account immediately.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_DisableResyncUpdate(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));

    CLEAR_BIT(*pReg, SHRTIM_TXCTRL_RSYNCUPD);
    /* This bit is significant only when UPDGAT[3:0] = 0000, it is ignored otherwise */
}

/**
*\*\fun  Indicate whether the Re-Syncronisation Update is enabled.
*\*\note   This bit specifies whether update source coming outside
*\*\        from the timing unit must be synchronized
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of RSYNCUPD in SHRTIM_TxCTRL register (1 or 0).
**/
uint32_t SHRTIM_TIM_IsEnabledResyncUpdate(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXCTRL_RSYNCUPD) == (SHRTIM_TXCTRL_RSYNCUPD)) ? 1UL : 0UL);
    /* This bit is significant only when UPDGAT[3:0] = 0000, it is ignored otherwise */
}

/**
*\*\note Interleaved mode complements the Half mode and helps the implementation of interleaved topologies.
*\*\note When interleaved mode is enabled, the content of the compare registers is overridden.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_INTERLEAVED_MODE_DISABLED
*\*\        - SHRTIM_INTERLEAVED_MODE_DUAL
*\*\        - SHRTIM_INTERLEAVED_MODE_TRIPLE
*\*\        - SHRTIM_INTERLEAVED_MODE_QUAD
*\*\return None
**/
void SHRTIM_TIM_SetInterleavedMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));

    MODIFY_REG(*pReg, REG_MASK_TAB_ILV[iTimer],
               ((Mode & SHRTIM_MCTRL_HLF) | ((Mode & SHRTIM_MCTRL_ILV) << REG_SHIFT_TAB_ILV[iTimer])));
}

/**
*\*\fun  get the Interleaved configuration.
*\*\note The interleaved Mode is Triple or Quad if HLF bit is disabled
*\*\             the interleaved Mode is dual if HLF bit is set,

*\*\             SHRTIM_MCMP1DAT (or SHRTIM_TXCMP1xDAT) active register is automatically updated
*\*\             with SHRTIM_MPRD/2 or SHRTIM_MPRD/4
  *       (or SHRTIM_TXPRD/2) value when SHRTIM_MPRD (or SHRTIM_TXPRD) register is written.

*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return This parameter can be one of the following values:
*\*\        - SHRTIM_INTERLEAVED_MODE_DISABLED
*\*\        - SHRTIM_INTERLEAVED_MODE_DUAL
*\*\        - SHRTIM_INTERLEAVED_MODE_TRIPLE
*\*\        - SHRTIM_INTERLEAVED_MODE_QUAD
**/
uint32_t SHRTIM_TIM_GetInterleavedMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));

    uint32_t Mode = READ_BIT(*pReg, (REG_MASK_TAB_ILV[iTimer]));
    return ((Mode & SHRTIM_MCTRL_HLF) | ((Mode >> REG_SHIFT_TAB_ILV[iTimer]) & SHRTIM_MCTRL_ILV));
}

/**
*\*\fun  Enable the timer start when receiving a synchronization input event.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_EnableStartOnSync(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));

    if (Timer == SHRTIM_TIMER_MASTER)
    {
        SET_BIT(*pReg, SHRTIM_MCTRL_SYNCSTRT);
    }
    else
    {
        SET_BIT(*pReg, SHRTIM_TXCTRL_SYNCSTRT);
    }
}

/**
*\*\fun  Disable the timer start when receiving a synchronization input event.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_DisableStartOnSync(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));

    if (Timer == SHRTIM_TIMER_MASTER)
    {
        CLEAR_BIT(*pReg, SHRTIM_MCTRL_SYNCSTRT);
    }
    else
    {
        CLEAR_BIT(*pReg, SHRTIM_TXCTRL_SYNCSTRT);
    }
}

/**
*\*\fun  Indicate whether the timer start when receiving a synchronization input event.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of SYNCSTRT bit in SHRTIM_MCTRL or SHRTIM_TxCTRL register (1 or 0).
**/
uint32_t SHRTIM_TIM_IsEnabledStartOnSync(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));

    if (Timer == SHRTIM_TIMER_MASTER)
    {
        return ((READ_BIT(*pReg, SHRTIM_MCTRL_SYNCSTRT) == (SHRTIM_MCTRL_SYNCSTRT)) ? 1UL : 0UL);
    }
    else
    {
        return ((READ_BIT(*pReg, SHRTIM_TXCTRL_SYNCSTRT) == (SHRTIM_TXCTRL_SYNCSTRT)) ? 1UL : 0UL);
    }
}

/**
*\*\fun  Enable the timer reset when receiving a synchronization input event.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_EnableResetOnSync(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));

    if (Timer == SHRTIM_TIMER_MASTER)
    {
        SET_BIT(*pReg, SHRTIM_MCTRL_SYNCRST);
    }
    else
    {
        SET_BIT(*pReg, SHRTIM_TXCTRL_SYNCRST);
    }
}

/**
*\*\fun  Disable the timer reset when receiving a synchronization input event.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_DisableResetOnSync(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));

    if (Timer == SHRTIM_TIMER_MASTER)
    {
        CLEAR_BIT(*pReg, SHRTIM_MCTRL_SYNCRST);
    }
    else
    {
        CLEAR_BIT(*pReg, SHRTIM_TXCTRL_SYNCRST);
    }
}

/**
*\*\fun  Indicate whether the timer reset when receiving a synchronization input event.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
uint32_t SHRTIM_TIM_IsEnabledResetOnSync(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));

    if (Timer == SHRTIM_TIMER_MASTER)
    {
        return ((READ_BIT(*pReg, SHRTIM_MCTRL_SYNCRST) == (SHRTIM_MCTRL_SYNCRST)) ? 1UL : 0UL);
    }
    else
    {
        return ((READ_BIT(*pReg, SHRTIM_TXCTRL_SYNCRST) == (SHRTIM_TXCTRL_SYNCRST)) ? 1UL : 0UL);
    }
}

/**
*\*\fun  Set the SHRTIM output the DAC synchronization event is generated on (DACtrigOutx).
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  DACTrig This parameter can be one of the following values:
*\*\        - SHRTIM_DACTRIG_NONE
*\*\        - SHRTIM_DACTRIG_DACTRIGOUT_1
*\*\        - SHRTIM_DACTRIG_DACTRIGOUT_2
*\*\        - SHRTIM_DACTRIG_DACTRIGOUT_3
*\*\return None
**/
void SHRTIM_TIM_SetDACTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t DACTrig)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_MCTRL_DACTRIG, DACTrig);
}

/**
*\*\fun  Get the SHRTIM output the DAC synchronization event is generated on (DACtrigOutx).
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return DACTrig Returned value can be one of the following values:
*\*\        - SHRTIM_DACTRIG_NONE
*\*\        - SHRTIM_DACTRIG_DACTRIGOUT_1
*\*\        - SHRTIM_DACTRIG_DACTRIGOUT_2
*\*\        - SHRTIM_DACTRIG_DACTRIGOUT_3
**/
uint32_t SHRTIM_TIM_GetDACTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_MCTRL_DACTRIG));
}

/**
*\*\fun  Enable the timer registers preload mechanism.
*\*\note When the preload mode is enabled, accessed registers are shadow registers.
 *       Their content is transferred into the active register after an update request,
 *       either software or synchronized with an event.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_EnablePreload(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MCTRL_PLEN);
}

/**
*\*\fun  Disable the timer registers preload mechanism.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_DisablePreload(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_MCTRL_PLEN);
}

/**
*\*\fun  Indicate whether the timer registers preload mechanism is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of PLEN bit in SHRTIM_MCTRL or SHRTIM_TxCTRL register (1 or 0).
**/
uint32_t SHRTIM_TIM_IsEnabledPreload(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MCTRL_PLEN) == (SHRTIM_MCTRL_PLEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Set the timer register update trigger.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  UpdateTrig This parameter can be one of the following values:
*\*\        For the master timer this parameter can be one of the following values:
*\*\        - SHRTIM_UPDATETRIG_NONE
*\*\        - SHRTIM_UPDATETRIG_REPETITION
*\*\        For timer A..F this parameter can be:
*\*\        - SHRTIM_UPDATETRIG_NONE
*\*\        or a combination of the following values:
*\*\        - SHRTIM_UPDATETRIG_MASTER
*\*\        - SHRTIM_UPDATETRIG_TIMER_A
*\*\        - SHRTIM_UPDATETRIG_TIMER_B
*\*\        - SHRTIM_UPDATETRIG_TIMER_C
*\*\        - SHRTIM_UPDATETRIG_TIMER_D
*\*\        - SHRTIM_UPDATETRIG_TIMER_E
*\*\        - SHRTIM_UPDATETRIG_TIMER_F
*\*\        - SHRTIM_UPDATETRIG_REPETITION
*\*\        - SHRTIM_UPDATETRIG_RESET
*\*\return None
**/
void SHRTIM_TIM_SetUpdateTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t UpdateTrig)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, REG_MASK_TAB_UPDATETRIG[iTimer], UpdateTrig << REG_SHIFT_TAB_UPDATETRIG[iTimer]);
}

/**
*\*\fun  Get the timer register update trigger.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return UpdateTrig Returned value can be one of the following values:
 *
*\*\        For the master timer this parameter can be one of the following values:
*\*\        - SHRTIM_UPDATETRIG_NONE
*\*\        - SHRTIM_UPDATETRIG_MASTER_REPETITION
 *
*\*\        For timer A..F this parameter can be:
*\*\        - SHRTIM_UPDATETRIG_NONE
*\*\        or a combination of the following values:
*\*\        - SHRTIM_UPDATETRIG_MASTER
*\*\        - SHRTIM_UPDATETRIG_TIMER_A
*\*\        - SHRTIM_UPDATETRIG_TIMER_B
*\*\        - SHRTIM_UPDATETRIG_TIMER_C
*\*\        - SHRTIM_UPDATETRIG_TIMER_D
*\*\        - SHRTIM_UPDATETRIG_TIMER_E
*\*\        - SHRTIM_UPDATETRIG_TIMER_F
*\*\        - SHRTIM_UPDATETRIG_REPETITION
*\*\        - SHRTIM_UPDATETRIG_RESET
**/
uint32_t SHRTIM_TIM_GetUpdateTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, REG_MASK_TAB_UPDATETRIG[iTimer]) >> REG_SHIFT_TAB_UPDATETRIG[iTimer]);
}

/**
*\*\fun  Set  the timer registers update condition (how the registers update occurs relatively to the burst DMA  transaction or an external update request received on one of the update enable inputs (UPD_EN[3:1])).
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  UpdateGating This parameter can be one of the following values:
 *
*\*\        For the master timer this parameter can be one of the following values:
*\*\        - SHRTIM_UPDATEGATING_INDEPENDENT
*\*\        - SHRTIM_UPDATEGATING_DMABURST
*\*\        - SHRTIM_UPDATEGATING_DMABURST_UPDATE
 *
*\*\        For the timer A..F this parameter can be one of the following values:
*\*\        - SHRTIM_UPDATEGATING_INDEPENDENT
*\*\        - SHRTIM_UPDATEGATING_DMABURST
*\*\        - SHRTIM_UPDATEGATING_DMABURST_UPDATE
*\*\        - SHRTIM_UPDATEGATING_UPDEN1
*\*\        - SHRTIM_UPDATEGATING_UPDEN2
*\*\        - SHRTIM_UPDATEGATING_UPDEN3
*\*\        - SHRTIM_UPDATEGATING_UPDEN1_UPDATE
*\*\        - SHRTIM_UPDATEGATING_UPDEN2_UPDATE
*\*\        - SHRTIM_UPDATEGATING_UPDEN3_UPDATE
*\*\return None
**/
void SHRTIM_TIM_SetUpdateGating(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t UpdateGating)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, REG_MASK_TAB_UPDATEGATING[iTimer], (UpdateGating << REG_SHIFT_TAB_UPDATEGATING[iTimer]));
}

/**
*\*\fun  Get  the timer registers update condition.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return UpdateGating Returned value can be one of the following values:
 *
*\*\        For the master timer this parameter can be one of the following values:
*\*\        - SHRTIM_UPDATEGATING_INDEPENDENT
*\*\        - SHRTIM_UPDATEGATING_DMABURST
*\*\        - SHRTIM_UPDATEGATING_DMABURST_UPDATE
 *
*\*\        For the timer A..F this parameter can be one of the following values:
*\*\        - SHRTIM_UPDATEGATING_INDEPENDENT
*\*\        - SHRTIM_UPDATEGATING_DMABURST
*\*\        - SHRTIM_UPDATEGATING_DMABURST_UPDATE
*\*\        - SHRTIM_UPDATEGATING_UPDEN1
*\*\        - SHRTIM_UPDATEGATING_UPDEN2
*\*\        - SHRTIM_UPDATEGATING_UPDEN3
*\*\        - SHRTIM_UPDATEGATING_UPDEN1_UPDATE
*\*\        - SHRTIM_UPDATEGATING_UPDEN2_UPDATE
*\*\        - SHRTIM_UPDATEGATING_UPDEN3_UPDATE
**/
uint32_t SHRTIM_TIM_GetUpdateGating(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCTRL) + REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, REG_MASK_TAB_UPDATEGATING[iTimer]) >> REG_SHIFT_TAB_UPDATEGATING[iTimer]);
}

/**
*\*\fun  Enable the push-pull mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_EnablePushPullMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXCTRL_PP);
}

/**
*\*\fun  Disable the push-pull mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_DisablePushPullMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXCTRL_PP);
}

/**
*\*\fun  Indicate whether the push-pull mode is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of PP bit in SHRTIM_TxCTRL register (1 or 0).
**/
uint32_t SHRTIM_TIM_IsEnabledPushPullMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return ((READ_BIT(*pReg, SHRTIM_TXCTRL_PP) == (SHRTIM_TXCTRL_PP)) ? 1UL : 0UL);
}

/**
*\*\fun  Set the functioning mode of the compare unit (CMP2 or CMP4 can operate in standard mode or in auto delayed mode).
*\*\note In auto-delayed mode  the compare match occurs independently from the timer counter value.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  CompareUnit This parameter can be one of the following values:
*\*\        - SHRTIM_COMPAREUNIT_2
*\*\        - SHRTIM_COMPAREUNIT_4
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_COMPAREMODE_REGULAR
*\*\        - SHRTIM_COMPAREMODE_DELAY_NOTIMEOUT
*\*\        - SHRTIM_COMPAREMODE_DELAY_CMP1
*\*\        - SHRTIM_COMPAREMODE_DELAY_CMP3
*\*\return None
**/
void SHRTIM_TIM_SetCompareMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CompareUnit,
                               uint32_t Mode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    uint32_t shift = (((uint32_t)POSITION_VAL(CompareUnit) - (uint32_t)POSITION_VAL(SHRTIM_COMPAREUNIT_2)) & 0x1FU);
    MODIFY_REG(*pReg, (SHRTIM_TXCTRL_DELCMP2M << shift), (Mode << shift));
}

/**
*\*\fun  Get the functioning mode of the compare unit.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  CompareUnit This parameter can be one of the following values:
*\*\        - SHRTIM_COMPAREUNIT_2
*\*\        - SHRTIM_COMPAREUNIT_4
*\*\return Mode Returned value can be one of the following values:
*\*\        - SHRTIM_COMPAREMODE_REGULAR
*\*\        - SHRTIM_COMPAREMODE_DELAY_NOTIMEOUT
*\*\        - SHRTIM_COMPAREMODE_DELAY_CMP1
*\*\        - SHRTIM_COMPAREMODE_DELAY_CMP3
**/
uint32_t SHRTIM_TIM_GetCompareMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CompareUnit)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    uint32_t shift = (((uint32_t)POSITION_VAL(CompareUnit) - (uint32_t)POSITION_VAL(SHRTIM_COMPAREUNIT_2)) & 0x1FU);
    return (READ_BIT(*pReg, (SHRTIM_TXCTRL_DELCMP2M << shift)) >> shift);
}

/**
*\*\fun  Set the timer counter value.
*\*\note  This function can only be called when the timer is stopped.
*\*\note  For HR clock prescaling ratio below 32 (CKPSC[2:0] < 5), the least
 *        significant bits of the counter are not significant. They cannot be
 *        written and return 0 when read.
*\*\note The timer behavior is not guaranteed if the counter value is set above
 *       the period.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Counter Value between 0 and 0xFFFF
*\*\return None
**/
void SHRTIM_TIM_SetCounter(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Counter)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCNT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_MCNT_MCOUNT, Counter);
}

/**
*\*\fun  Get actual timer counter value.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return Counter Value between 0 and 0xFFFF
**/
uint32_t SHRTIM_TIM_GetCounter(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCNT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_MCNT_MCOUNT));
}

/**
*\*\fun  Set the timer period value.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Period Value between 0 and 0xFFFF
*\*\return None
**/
void SHRTIM_TIM_SetPeriod(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Period)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MPRD) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_MPRD_MPRD, Period);
}

/**
*\*\fun  Get actual timer period value.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return Period Value between 0 and 0xFFFF
**/
uint32_t SHRTIM_TIM_GetPeriod(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MPRD) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_MPRD_MPRD));
}

/**
*\*\fun  Set the timer repetition period value.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Repetition Value between 0 and 0xFF
*\*\return None
**/
void SHRTIM_TIM_SetRepetition(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Repetition)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MREPT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_MREPT_MREPT, Repetition);
}

/**
*\*\fun  Get actual timer repetition period value.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return Repetition Value between 0 and 0xFF
**/
uint32_t SHRTIM_TIM_GetRepetition(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MREPT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_MREPT_MREPT));
}

/**
*\*\fun  Set the compare value of the compare unit 1.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  CompareValue Compare value must be above or equal to 3
*\*\        periods of the fSHRTIM clock, that is 0x60 if CKPSC[2:0] = 0,
*\*\        0x30 if CKPSC[2:0] = 1, 0x18 if CKPSC[2:0] = 2,...
*\*\return None
**/
void SHRTIM_TIM_SetCompare1(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CompareValue)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCMP1DAT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_MCMP1DAT_MCMP1DAT, CompareValue);
}

/**
*\*\fun  Get actual compare value of the compare unit 1.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return CompareValue Compare value must be above or equal to 3
*\*\        periods of the fSHRTIM clock, that is 0x60 if CKPSC[2:0] = 0,
*\*\        0x30 if CKPSC[2:0] = 1, 0x18 if CKPSC[2:0] = 2,...
**/
uint32_t SHRTIM_TIM_GetCompare1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCMP1DAT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_MCMP1DAT_MCMP1DAT));
}

/**
*\*\fun  Set the compare value of the compare unit 2.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  CompareValue Compare value must be above or equal to 3
*\*\        periods of the fSHRTIM clock, that is 0x60 if CKPSC[2:0] = 0,
*\*\        0x30 if CKPSC[2:0] = 1, 0x18 if CKPSC[2:0] = 2,...
*\*\return None
**/
void SHRTIM_TIM_SetCompare2(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CompareValue)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCMP2DAT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_MCMP2DAT_MCMP2DAT, CompareValue);
}

/**
*\*\fun  Get actual compare value of the compare unit 2.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return CompareValue Compare value must be above or equal to 3
*\*\        periods of the fSHRTIM clock, that is 0x60 if CKPSC[2:0] = 0,
*\*\        0x30 if CKPSC[2:0] = 1, 0x18 if CKPSC[2:0] = 2,...
**/
uint32_t SHRTIM_TIM_GetCompare2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCMP2DAT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_MCMP2DAT_MCMP2DAT));
}

/**
*\*\fun  Set the compare value of the compare unit 3.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  CompareValue Compare value must be above or equal to 3
*\*\        periods of the fSHRTIM clock, that is 0x60 if CKPSC[2:0] = 0,
*\*\        0x30 if CKPSC[2:0] = 1, 0x18 if CKPSC[2:0] = 2,...
*\*\return None
**/
void SHRTIM_TIM_SetCompare3(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CompareValue)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCMP3DAT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_MCMP3DAT_MCMP3DAT, CompareValue);
}

/**
*\*\fun  Get actual compare value of the compare unit 3.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return CompareValue Compare value must be above or equal to 3
*\*\        periods of the fSHRTIM clock, that is 0x60 if CKPSC[2:0] = 0,
*\*\        0x30 if CKPSC[2:0] = 1, 0x18 if CKPSC[2:0] = 2,...
**/
uint32_t SHRTIM_TIM_GetCompare3(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCMP3DAT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_MCMP3DAT_MCMP3DAT));
}

/**
*\*\fun  Set the compare value of the compare unit 4.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  CompareValue Compare value must be above or equal to 3
*\*\        periods of the fSHRTIM clock, that is 0x60 if CKPSC[2:0] = 0,
*\*\        0x30 if CKPSC[2:0] = 1, 0x18 if CKPSC[2:0] = 2,...
*\*\return None
**/
void SHRTIM_TIM_SetCompare4(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CompareValue)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCMP4DAT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_MCMP4DAT_MCMP4DAT, CompareValue);
}

/**
*\*\fun  Get actual compare value of the compare unit 4.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return CompareValue Compare value must be above or equal to 3
*\*\        periods of the fSHRTIM clock, that is 0x60 if CKPSC[2:0] = 0,
*\*\        0x30 if CKPSC[2:0] = 1, 0x18 if CKPSC[2:0] = 2,...
**/
uint32_t SHRTIM_TIM_GetCompare4(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MCMP4DAT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_MCMP4DAT_MCMP4DAT));
}

/**
*\*\fun  Set the compare value of the compare unit 5.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  CompareValue Compare value is regular resolution, not high resolution
*\*\return None
**/
void SHRTIM_TIM_SetCompare5(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CompareValue)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCMP5DAT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCMP5DAT_CMP5DAT, CompareValue);
}

/**
*\*\fun  Get actual compare value of the compare unit 5.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return  CompareValue Compare value is regular resolution, not high resolution
**/
uint32_t SHRTIM_TIM_GetCompare5(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCMP5DAT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXCMP5DAT_CMP5DAT));
}

/**
*\*\fun  Set the reset trigger of a timer counter.
*\*\note The reset of the timer counter can be triggered by up to 30 events
 *       that can be selected among the following sources:
*\*\        - The timing unit: Compare 2, Compare 4 and Update (3 events).
*\*\        - The master timer: Reset and Compare 1..4 (5 events).
*\*\        - The external events EXTEVNT1..10 (10 events).
*\*\        - All other timing units (e.g. Timer B..F for timer A): Compare 1, 2 and 4 (12 events).
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  ResetTrig This parameter can be a combination of the following values:
*\*\        - SHRTIM_RESETTRIG_NONE
*\*\        - SHRTIM_RESETTRIG_UPDATE
*\*\        - SHRTIM_RESETTRIG_CMP2
*\*\        - SHRTIM_RESETTRIG_CMP4
*\*\        - SHRTIM_RESETTRIG_MASTER_PER
*\*\        - SHRTIM_RESETTRIG_MASTER_CMP1
*\*\        - SHRTIM_RESETTRIG_MASTER_CMP2
*\*\        - SHRTIM_RESETTRIG_MASTER_CMP3
*\*\        - SHRTIM_RESETTRIG_MASTER_CMP4
*\*\        - SHRTIM_RESETTRIG_EXEV_1
*\*\        - SHRTIM_RESETTRIG_EXEV_2
*\*\        - SHRTIM_RESETTRIG_EXEV_3
*\*\        - SHRTIM_RESETTRIG_EXEV_4
*\*\        - SHRTIM_RESETTRIG_EXEV_5
*\*\        - SHRTIM_RESETTRIG_EXEV_6
*\*\        - SHRTIM_RESETTRIG_EXEV_7
*\*\        - SHRTIM_RESETTRIG_EXEV_8
*\*\        - SHRTIM_RESETTRIG_EXEV_9
*\*\        - SHRTIM_RESETTRIG_EXEV_10
*\*\        - SHRTIM_RESETTRIG_OTHER1_CMP1
*\*\        - SHRTIM_RESETTRIG_OTHER1_CMP2
*\*\        - SHRTIM_RESETTRIG_OTHER1_CMP4
*\*\        - SHRTIM_RESETTRIG_OTHER2_CMP1
*\*\        - SHRTIM_RESETTRIG_OTHER2_CMP2
*\*\        - SHRTIM_RESETTRIG_OTHER2_CMP4
*\*\        - SHRTIM_RESETTRIG_OTHER3_CMP1
*\*\        - SHRTIM_RESETTRIG_OTHER3_CMP2
*\*\        - SHRTIM_RESETTRIG_OTHER3_CMP4
*\*\        - SHRTIM_RESETTRIG_OTHER4_CMP1
*\*\        - SHRTIM_RESETTRIG_OTHER4_CMP2
*\*\        - SHRTIM_RESETTRIG_OTHER4_CMP4
*\*\        - SHRTIM_RESETTRIG_OTHER5_CMP1
*\*\        - SHRTIM_RESETTRIG_OTHER5_CMP2
*\*\return None
**/
void SHRTIM_TIM_SetResetTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t ResetTrig)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCNTRST) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    WRITE_REG(*pReg, ResetTrig);
}

/**
*\*\fun  Get actual reset trigger of a timer counter.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return ResetTrig Returned value can be one of the following values:
*\*\        - SHRTIM_RESETTRIG_NONE
*\*\        - SHRTIM_RESETTRIG_UPDATE
*\*\        - SHRTIM_RESETTRIG_CMP2
*\*\        - SHRTIM_RESETTRIG_CMP4
*\*\        - SHRTIM_RESETTRIG_MASTER_PER
*\*\        - SHRTIM_RESETTRIG_MASTER_CMP1
*\*\        - SHRTIM_RESETTRIG_MASTER_CMP2
*\*\        - SHRTIM_RESETTRIG_MASTER_CMP3
*\*\        - SHRTIM_RESETTRIG_MASTER_CMP4
*\*\        - SHRTIM_RESETTRIG_EXEV_1
*\*\        - SHRTIM_RESETTRIG_EXEV_2
*\*\        - SHRTIM_RESETTRIG_EXEV_3
*\*\        - SHRTIM_RESETTRIG_EXEV_4
*\*\        - SHRTIM_RESETTRIG_EXEV_5
*\*\        - SHRTIM_RESETTRIG_EXEV_6
*\*\        - SHRTIM_RESETTRIG_EXEV_7
*\*\        - SHRTIM_RESETTRIG_EXEV_8
*\*\        - SHRTIM_RESETTRIG_EXEV_9
*\*\        - SHRTIM_RESETTRIG_EXEV_10
*\*\        - SHRTIM_RESETTRIG_OTHER1_CMP1
*\*\        - SHRTIM_RESETTRIG_OTHER1_CMP2
*\*\        - SHRTIM_RESETTRIG_OTHER1_CMP4
*\*\        - SHRTIM_RESETTRIG_OTHER2_CMP1
*\*\        - SHRTIM_RESETTRIG_OTHER2_CMP2
*\*\        - SHRTIM_RESETTRIG_OTHER2_CMP4
*\*\        - SHRTIM_RESETTRIG_OTHER3_CMP1
*\*\        - SHRTIM_RESETTRIG_OTHER3_CMP2
*\*\        - SHRTIM_RESETTRIG_OTHER3_CMP4
*\*\        - SHRTIM_RESETTRIG_OTHER4_CMP1
*\*\        - SHRTIM_RESETTRIG_OTHER4_CMP2
*\*\        - SHRTIM_RESETTRIG_OTHER4_CMP4
*\*\        - SHRTIM_RESETTRIG_OTHER5_CMP1
*\*\        - SHRTIM_RESETTRIG_OTHER5_CMP2
**/
uint32_t SHRTIM_TIM_GetResetTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxRST1) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_REG(*pReg));
}

/**
*\*\fun  Get captured value for capture unit 1.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return Captured value
**/
uint32_t SHRTIM_TIM_GetCapture1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCPT1) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_REG(*pReg));
}

/**
*\*\fun  Get the counting direction when capture 1 event occurred.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return Filter This parameter can be one of the following values:
*\*\        -  SHRTIM_COUNTING_MODE_UP
*\*\        -  SHRTIM_COUNTING_MODE_UP_DOWN
**/
uint32_t SHRTIM_TIM_GetCapture1Direction(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCPT1) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return ((READ_BIT(*pReg, SHRTIM_TXCPT1_UDSTS1) >> SHRTIM_TXCPT1_UDSTS1_Pos) << SHRTIM_TXCTRL2_UPDOWNM_Pos);
}

/**
*\*\fun  Get captured value for capture unit 2.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return Captured value
**/
uint32_t SHRTIM_TIM_GetCapture2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCPT2) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_REG(*pReg));
}

/**
*\*\fun  Get the counting direction when capture 2 event occurred.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return Filter This parameter can be one of the following values:
*\*\        -  SHRTIM_COUNTING_MODE_UP
*\*\        -  SHRTIM_COUNTING_MODE_UP_DOWN
**/
uint32_t SHRTIM_TIM_GetCapture2Direction(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCPT2) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return ((READ_BIT(*pReg, SHRTIM_TXCPT2_UDSTS2) >> SHRTIM_TXCPT2_UDSTS2_Pos) << SHRTIM_TXCTRL2_UPDOWNM_Pos);
}

/**
*\*\fun  Set the trigger of a capture unit for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  CaptureUnit This parameter can be one of the following values:
*\*\        - SHRTIM_CAPTUREUNIT_1
*\*\        - SHRTIM_CAPTUREUNIT_2
*\*\param  CaptureTrig This parameter can be a combination of the following values:
*\*\        - SHRTIM_CAPTURETRIG_NONE
*\*\        - SHRTIM_CAPTURETRIG_SW
*\*\        - SHRTIM_CAPTURETRIG_UPDATE
*\*\        - SHRTIM_CAPTURETRIG_EXEV_1
*\*\        - SHRTIM_CAPTURETRIG_EXEV_2
*\*\        - SHRTIM_CAPTURETRIG_EXEV_3
*\*\        - SHRTIM_CAPTURETRIG_EXEV_4
*\*\        - SHRTIM_CAPTURETRIG_EXEV_5
*\*\        - SHRTIM_CAPTURETRIG_EXEV_6
*\*\        - SHRTIM_CAPTURETRIG_EXEV_7
*\*\        - SHRTIM_CAPTURETRIG_EXEV_8
*\*\        - SHRTIM_CAPTURETRIG_EXEV_9
*\*\        - SHRTIM_CAPTURETRIG_EXEV_10
*\*\        - SHRTIM_CAPTURETRIG_TA1_SET
*\*\        - SHRTIM_CAPTURETRIG_TA1_RESET
*\*\        - SHRTIM_CAPTURETRIG_TIMA_CMP1
*\*\        - SHRTIM_CAPTURETRIG_TIMA_CMP2
*\*\        - SHRTIM_CAPTURETRIG_TB1_SET
*\*\        - SHRTIM_CAPTURETRIG_TB1_RESET
*\*\        - SHRTIM_CAPTURETRIG_TIMB_CMP1
*\*\        - SHRTIM_CAPTURETRIG_TIMB_CMP2
*\*\        - SHRTIM_CAPTURETRIG_TC1_SET
*\*\        - SHRTIM_CAPTURETRIG_TC1_RESET
*\*\        - SHRTIM_CAPTURETRIG_TIMC_CMP1
*\*\        - SHRTIM_CAPTURETRIG_TIMC_CMP2
*\*\        - SHRTIM_CAPTURETRIG_TD1_SET
*\*\        - SHRTIM_CAPTURETRIG_TD1_RESET
*\*\        - SHRTIM_CAPTURETRIG_TIMD_CMP1
*\*\        - SHRTIM_CAPTURETRIG_TIMD_CMP2
*\*\        - SHRTIM_CAPTURETRIG_TE1_SET
*\*\        - SHRTIM_CAPTURETRIG_TE1_RESET
*\*\        - SHRTIM_CAPTURETRIG_TIME_CMP1
*\*\        - SHRTIM_CAPTURETRIG_TIME_CMP2
*\*\        - SHRTIM_CAPTURETRIG_TF1_SET
*\*\        - SHRTIM_CAPTURETRIG_TF1_RESET
*\*\        - SHRTIM_CAPTURETRIG_TIMF_CMP1
*\*\        - SHRTIM_CAPTURETRIG_TIMF_CMP2
*\*\return None
**/
void SHRTIM_TIM_SetCaptureTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CaptureUnit,
                               uint64_t CaptureTrig)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0U].TxCPT1CTRL) +
                                            REG_OFFSET_TAB_TIMER[iTimer] + (CaptureUnit * 4U)));

    uint32_t cfg1 = (uint32_t)(CaptureTrig & 0x0000000000000FFFU);
    uint32_t cfg2 = (uint32_t)((CaptureTrig & 0xFFFFF00F00000000U) >> 32U);

    cfg2 = (cfg2 & REG_MASK_TAB_CPT[iTimer]) | ((cfg2 & 0x0000000FU) << (REG_SHIFT_TAB_CPT[iTimer]));

    WRITE_REG(*pReg, (cfg1 | cfg2));
}

/**
*\*\fun  Get actual trigger of a capture unit for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  CaptureUnit This parameter can be one of the following values:
*\*\        - SHRTIM_CAPTUREUNIT_1
*\*\        - SHRTIM_CAPTUREUNIT_2
*\*\return CaptureTrig This parameter can be a combination of the following values:
*\*\        - SHRTIM_CAPTURETRIG_NONE
*\*\        - SHRTIM_CAPTURETRIG_SW
*\*\        - SHRTIM_CAPTURETRIG_UPDATE
*\*\        - SHRTIM_CAPTURETRIG_EXEV_1
*\*\        - SHRTIM_CAPTURETRIG_EXEV_2
*\*\        - SHRTIM_CAPTURETRIG_EXEV_3
*\*\        - SHRTIM_CAPTURETRIG_EXEV_4
*\*\        - SHRTIM_CAPTURETRIG_EXEV_5
*\*\        - SHRTIM_CAPTURETRIG_EXEV_6
*\*\        - SHRTIM_CAPTURETRIG_EXEV_7
*\*\        - SHRTIM_CAPTURETRIG_EXEV_8
*\*\        - SHRTIM_CAPTURETRIG_EXEV_9
*\*\        - SHRTIM_CAPTURETRIG_EXEV_10
*\*\        - SHRTIM_CAPTURETRIG_TA1_SET
*\*\        - SHRTIM_CAPTURETRIG_TA1_RESET
*\*\        - SHRTIM_CAPTURETRIG_TIMA_CMP1
*\*\        - SHRTIM_CAPTURETRIG_TIMA_CMP2
*\*\        - SHRTIM_CAPTURETRIG_TB1_SET
*\*\        - SHRTIM_CAPTURETRIG_TB1_RESET
*\*\        - SHRTIM_CAPTURETRIG_TIMB_CMP1
*\*\        - SHRTIM_CAPTURETRIG_TIMB_CMP2
*\*\        - SHRTIM_CAPTURETRIG_TC1_SET
*\*\        - SHRTIM_CAPTURETRIG_TC1_RESET
*\*\        - SHRTIM_CAPTURETRIG_TIMC_CMP1
*\*\        - SHRTIM_CAPTURETRIG_TIMC_CMP2
*\*\        - SHRTIM_CAPTURETRIG_TD1_SET
*\*\        - SHRTIM_CAPTURETRIG_TD1_RESET
*\*\        - SHRTIM_CAPTURETRIG_TIMD_CMP1
*\*\        - SHRTIM_CAPTURETRIG_TIMD_CMP2
*\*\        - SHRTIM_CAPTURETRIG_TE1_SET
*\*\        - SHRTIM_CAPTURETRIG_TE1_RESET
*\*\        - SHRTIM_CAPTURETRIG_TIME_CMP1
*\*\        - SHRTIM_CAPTURETRIG_TIME_CMP2
*\*\        - SHRTIM_CAPTURETRIG_TF1_SET
*\*\        - SHRTIM_CAPTURETRIG_TF1_RESET
*\*\        - SHRTIM_CAPTURETRIG_TIMF_CMP1
*\*\        - SHRTIM_CAPTURETRIG_TIMF_CMP2
**/
uint64_t SHRTIM_TIM_GetCaptureTrig(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t CaptureUnit)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0U].TxCPT1CTRL) +
                                (uint32_t)REG_OFFSET_TAB_TIMER[iTimer & 0x7U] + (CaptureUnit * 4U)));

    uint64_t cfg;
    uint32_t CaptureTrig = READ_REG(*pReg);

    cfg = (uint64_t)(uint32_t)(((CaptureTrig & 0xFFFFF000U) & (uint32_t)REG_MASK_TAB_CPT[iTimer]) | (((CaptureTrig & 0xFFFFF000U) & (uint32_t)~REG_MASK_TAB_CPT[iTimer]) >> (REG_SHIFT_TAB_CPT[iTimer])));

    return ((uint64_t)(((uint64_t)CaptureTrig & (uint64_t)0x00000FFFU) | (uint64_t)((cfg) << 32U)));
}

/**
*\*\fun  Enable deadtime insertion for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_EnableDeadTime(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXOUT_DTEN);
}

/**
*\*\fun  Disable deadtime insertion for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_DisableDeadTime(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXOUT_DTEN);
}

/**
*\*\fun  Indicate whether deadtime insertion is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of DTEN bit in SHRTIM_TxOUT register (1 or 0).
**/
uint32_t SHRTIM_TIM_IsEnabledDeadTime(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXOUT_DTEN) == (SHRTIM_TXOUT_DTEN)) ? 1UL : 0UL);
}


/**
*\*\fun  Set the delayed protection (DP) mode.
*\*\note   This function must be called prior enabling the delayed protection
*\*\note   Balanced Idle mode is only available in push-pull mode
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  DPMode Delayed protection (DP) mode
 *
*\*\        For timers A, B and C this parameter can be one of the following values:
*\*\        - SHRTIM_DP_DELAYOUT1_EXEV6
*\*\        - SHRTIM_DP_DELAYOUT2_EXEV6
*\*\        - SHRTIM_DP_DELAYBOTH_EXEV6
*\*\        - SHRTIM_DP_DELAYOUT1_EXEV7
*\*\        - SHRTIM_DP_DELAYOUT2_EXEV7
*\*\        - SHRTIM_DP_DELAYBOTH_EXEV7
 *
*\*\        For timers D, E and F this parameter can be one of the following values:
*\*\        - SHRTIM_DP_DELAYOUT1_EXEV8
*\*\        - SHRTIM_DP_DELAYOUT2_EXEV8
*\*\        - SHRTIM_DP_DELAYBOTH_EXEV8
*\*\        - SHRTIM_DP_DELAYOUT1_EXEV9
*\*\        - SHRTIM_DP_DELAYOUT2_EXEV9
*\*\        - SHRTIM_DP_DELAYBOTH_EXEV9
*\*\return None
**/
void SHRTIM_TIM_SetDPMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t DPMode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXOUT_DP, DPMode);
}

/**
*\*\fun  Get the delayed protection (DP) mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return DPMode Delayed protection (DP) mode
 *
*\*\        For timers A, B and C this parameter can be one of the following values:
*\*\        - SHRTIM_DP_DELAYOUT1_EXEV6
*\*\        - SHRTIM_DP_DELAYOUT2_EXEV6
*\*\        - SHRTIM_DP_DELAYBOTH_EXEV6
*\*\        - SHRTIM_DP_DELAYOUT1_EXEV7
*\*\        - SHRTIM_DP_DELAYOUT2_EXEV7
*\*\        - SHRTIM_DP_DELAYBOTH_EXEV7
 *
*\*\        For timers D, E and F this parameter can be one of the following values:
*\*\        - SHRTIM_DP_DELAYOUT1_EXEV8
*\*\        - SHRTIM_DP_DELAYOUT2_EXEV8
*\*\        - SHRTIM_DP_DELAYBOTH_EXEV8
*\*\        - SHRTIM_DP_DELAYOUT1_EXEV9
*\*\        - SHRTIM_DP_DELAYOUT2_EXEV9
*\*\        - SHRTIM_DP_DELAYBOTH_EXEV9
**/
uint32_t SHRTIM_TIM_GetDPMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXOUT_DP));
}

/**
*\*\fun  Enable delayed protection (DP) for a given timer.
*\*\note   This function must not be called once the concerned timer is enabled
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_EnableDP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXOUT_DPEN);
}

/**
*\*\fun  Disable delayed protection (DP) for a given timer.
*\*\note   This function must not be called once the concerned timer is enabled
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_DisableDP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXOUT_DPEN);
}

/**
*\*\fun  Indicate whether delayed protection (DP) is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of DPEN bit in SHRTIM_TxOUT register (1 or 0).
**/
uint32_t SHRTIM_TIM_IsEnabledDP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return ((READ_BIT(*pReg, SHRTIM_TXOUT_DPEN) == (SHRTIM_TXOUT_DPEN)) ? 1UL : 0UL);
}

/**
*\*\param  Enable the Balanced Idle Automatic Resume (BIAR) for a given timer.
*\*\param  This function must not be called once the concerned timer is enabled
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_EnableBIAR(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXOUT_BIAR);
}

/**
*\*\param  Disable the Balanced Idle Automatic Resume (BIAR) for a given timer.
*\*\param  This function must not be called once the concerned timer is enabled
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_DisableBIAR(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0U].TxOUT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXOUT_BIAR);
}

/**
*\*\param  Indicate whether the Balanced Idle Automatic Resume (BIAR) is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of DPEN bit in SHRTIM_TxOUT register (1 or 0).
**/
uint32_t SHRTIM_TIM_IsEnabledBIAR(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXOUT_BIAR) == (SHRTIM_TXOUT_BIAR)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the software delay protection
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  SoftDP This parameter can be a combination of the following values:
*\*\        - SHRTIM_SOFT_DP_TA1
*\*\        - SHRTIM_SOFT_DP_TA2
*\*\        - SHRTIM_SOFT_DP_TB1
*\*\        - SHRTIM_SOFT_DP_TB2
*\*\        - SHRTIM_SOFT_DP_TC1
*\*\        - SHRTIM_SOFT_DP_TC2
*\*\        - SHRTIM_SOFT_DP_TD1
*\*\        - SHRTIM_SOFT_DP_TD2
*\*\        - SHRTIM_SOFT_DP_TE1
*\*\        - SHRTIM_SOFT_DP_TE2
*\*\        - SHRTIM_SOFT_DP_TF1
*\*\        - SHRTIM_SOFT_DP_TF2
*\*\return None
**/
void SHRTIM_TIM_EnableSoftDP(SHRTIM_Module *SHRTIMx, uint32_t SoftDP)
{
    SET_BIT(SHRTIMx->sCommonRegs.SFTDP, (SoftDP & SHRTIM_SFTDP_CONFIG_MASK));
}

/**
*\*\fun  Indicate whether the soft delay protection is enabled for a given channel.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  SoftDP This parameter can be a combination of the following values:
*\*\        - SHRTIM_SOFT_DP_TA1
*\*\        - SHRTIM_SOFT_DP_TA2
*\*\        - SHRTIM_SOFT_DP_TB1
*\*\        - SHRTIM_SOFT_DP_TB2
*\*\        - SHRTIM_SOFT_DP_TC1
*\*\        - SHRTIM_SOFT_DP_TC2
*\*\        - SHRTIM_SOFT_DP_TD1
*\*\        - SHRTIM_SOFT_DP_TD2
*\*\        - SHRTIM_SOFT_DP_TE1
*\*\        - SHRTIM_SOFT_DP_TE2
*\*\        - SHRTIM_SOFT_DP_TF1
*\*\        - SHRTIM_SOFT_DP_TF2
*\*\return State of SFTDPxy bit in SHRTIM_SFTDP register (1 or 0).
**/
uint32_t SHRTIM_TIM_IsEnabledSoftDP(SHRTIM_Module *SHRTIMx, uint32_t SoftDP)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.SFTDP, SoftDP) == (SoftDP)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the fault channel(s) for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Faults This parameter can be a combination of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return None
**/
void SHRTIM_TIM_EnableFault(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Faults)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxFALT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, Faults);
}

/**
*\*\fun  Disable the fault channel(s) for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Faults This parameter can be a combination of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return None
**/
void SHRTIM_TIM_DisableFault(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Faults)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxFALT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, Faults);
}

/**
*\*\fun  Indicate whether the fault channel is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return State of FALTxEN bit in SHRTIM_TxFALT register (1 or 0).
**/
uint32_t SHRTIM_TIM_IsEnabledFault(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Fault)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxFALT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, Fault) == (Fault)) ? 1UL : 0UL);
}

/**
*\*\fun  Lock the fault conditioning set-up for a given timer.
*\*\note Timer fault-related set-up is frozen until the next SHRTIM or system reset
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_LockFault(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxFALT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXFALT_FALTLCK);
}

/**
*\*\fun  Define how the timer behaves during a burst mode operation.
*\*\note This function must not be called when the burst mode is enabled
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  BurtsModeOption This parameter can be one of the following values:
*\*\        - SHRTIM_BURSTMODE_MAINTAINCLOCK
*\*\        - SHRTIM_BURSTMODE_RESETCOUNTER
*\*\return None
**/
void SHRTIM_TIM_SetBurstModeOption(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t BurtsModeOption)
{
    uint32_t iTimer = (uint8_t)((POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos) & 0x1FU);
    MODIFY_REG(SHRTIMx->sCommonRegs.BMCTRL, Timer, BurtsModeOption << iTimer);
}

/**
*\*\fun  Retrieve how the timer behaves during a burst mode operation.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return BurtsMode This parameter can be one of the following values:
*\*\        - SHRTIM_BURSTMODE_MAINTAINCLOCK
*\*\        - SHRTIM_BURSTMODE_RESETCOUNTER
**/
uint32_t SHRTIM_TIM_GetBurstModeOption(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)((POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos) & 0x1FU);
    return (READ_BIT(SHRTIMx->sCommonRegs.BMCTRL, Timer) >> iTimer);
}

/**
*\*\fun  Program which registers are to be written by Burst DMA transfers.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Registers Registers to be updated by the DMA request
*\*\        For Master timer this parameter can be can be a combination of the following values:
*\*\        - SHRTIM_BURSTDMA_NONE
*\*\        - SHRTIM_BURSTDMA_MCTRL
*\*\        - SHRTIM_BURSTDMA_MINTCLR
*\*\        - SHRTIM_BURSTDMA_MIDEN
*\*\        - SHRTIM_BURSTDMA_MCNT
*\*\        - SHRTIM_BURSTDMA_MPRD
*\*\        - SHRTIM_BURSTDMA_MREPT
*\*\        - SHRTIM_BURSTDMA_MCMPDAT1
*\*\        - SHRTIM_BURSTDMA_MCMPDAT2
*\*\        - SHRTIM_BURSTDMA_MCMPDAT3
*\*\        - SHRTIM_BURSTDMA_MCMPDAT4
*\*\        For Timers A..F this parameter can be can be a combination of the following values:
*\*\        - SHRTIM_BURSTDMA_TXCTRL
*\*\        - SHRTIM_BURSTDMA_TXINTCLR
*\*\        - SHRTIM_BURSTDMA_TXIDEN
*\*\        - SHRTIM_BURSTDMA_TXCNT
*\*\        - SHRTIM_BURSTDMA_TXPRD
*\*\        - SHRTIM_BURSTDMA_TXREPT
*\*\        - SHRTIM_BURSTDMA_TXCMP1DAT
*\*\        - SHRTIM_BURSTDMA_TXCMP2DAT
*\*\        - SHRTIM_BURSTDMA_TXCMP3DAT
*\*\        - SHRTIM_BURSTDMA_TXCMP4DAT
*\*\        - SHRTIM_BURSTDMA_TXDT
*\*\        - SHRTIM_BURSTDMA_TXSET1
*\*\        - SHRTIM_BURSTDMA_TXRST1
*\*\        - SHRTIM_BURSTDMA_TXSET2
*\*\        - SHRTIM_BURSTDMA_TXRST2
*\*\        - SHRTIM_BURSTDMA_TXEXEVFLT1
*\*\        - SHRTIM_BURSTDMA_TXEXEVFLT2
*\*\        - SHRTIM_BURSTDMA_TXCNTRST
*\*\        - SHRTIM_BURSTDMA_TXCHOP
*\*\        - SHRTIM_BURSTDMA_TXOUT
*\*\        - SHRTIM_BURSTDMA_TXFALT
*\*\        - SHRTIM_BURSTDMA_TXCTRL2
*\*\        - SHRTIM_BURSTDMA_TXEXEVFLT3
*\*\return None
**/
void SHRTIM_TIM_ConfigBurstDMA(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Registers)
{
    const uint8_t REG_OFFSET_TAB_BDTUPR[] =
    {
        0x00U, /* BDMUPR ; offset = 0x000 */
        0x04U, /* BDAUPR ; offset = 0x05C */
        0x08U, /* BDBUPR ; offset = 0x060 */
        0x0CU, /* BDCUPR ; offset = 0x064 */
        0x10U, /* BDDUPR ; offset = 0x068 */
        0x14U, /* BDEUPR ; offset = 0x06C */
        0x1CU  /* BDFUPR ; offset = 0x074 */
    };

    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.BDMTUPD) + REG_OFFSET_TAB_BDTUPR[iTimer]));
    WRITE_REG(*pReg, Registers);
}

/**
*\*\fun  Indicate on which output the signal is currently applied.
*\*\note Only significant when the timer operates in push-pull mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return CPPSTAT This parameter can be one of the following values:
*\*\        - SHRTIM_CPPSTAT_OUTPUT1
*\*\        - SHRTIM_CPPSTAT_OUTPUT2
**/
uint32_t SHRTIM_TIM_GetCurrentPushPullStatus(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXINTSTS_CPPSTS));
}

/**
*\*\fun  Indicate on which output the signal was applied, in push-pull mode, balanced fault mode or delayed idle mode, when the protection was triggered.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return IPPSTAT This parameter can be one of the following values:
*\*\        - SHRTIM_IPPSTAT_OUTPUT1
*\*\        - SHRTIM_IPPSTAT_OUTPUT2
**/
uint32_t SHRTIM_TIM_GetIdlePushPullStatus(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXINTSTS_IPPSTS));
}

/**
*\*\fun  Window selection when EXEVxFLT = 0b'1111.
In up-down counting mode (SHRTIM_TxCTRL2.UPDOWNM bit set): windowing from compare 2
during the up-counting phase to compare 3 during the down-counting phase.
If EXEVWINSEL = 0, compare 2 is from another timer unit(refer to Table 9-19);
if EXEVWINSEL = 1, compare 2 is from timer unit itself.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_EnableEventWindowSelection(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxEXEVFLT1) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXEXEVFLT1_EXEVWINSEL);
}

/**
*\*\fun  Window selection when EXEVxFLT = 0b'1111.
In up-down counting mode (SHRTIM_TxCTRL2.UPDOWNM bit set): windowing from compare 2
during the up-counting phase to compare 3 during the down-counting phase.
If EXEVWINSEL = 0, compare 2 is from another timer unit(refer to Table 9-19);
if EXEVWINSEL = 1, compare 2 is from timer unit itself.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_DisbleEventWindowSelection(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxEXEVFLT1) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXEXEVFLT1_EXEVWINSEL);
}

/**
*\*\fun  Set the event filter for a given timer.
*\*\note This function must not be called when the timer counter is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\param  Filter This parameter can be one of the following values:
*\*\        - SHRTIM_EXEVFLT_NONE
*\*\        - SHRTIM_EXEVFLT_BLANKINGCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKINGCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKINGCMP3
*\*\        - SHRTIM_EXEVFLT_BLANKINGCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF1_TIMBCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF2_TIMBCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF3_TIMBOUT2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF4_TIMCCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF5_TIMCCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF6_TIMFCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF7_TIMDCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF8_TIMECMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF1_TIMACMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF2_TIMACMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF3_TIMAOUT2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF4_TIMCCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF5_TIMCCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF6_TIMFCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF7_TIMDCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF8_TIMECMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF1_TIMACMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF2_TIMBCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF3_TIMBCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF4_TIMFCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF5_TIMDCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF6_TIMDCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF7_TIMDOUT2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF8_TIMECMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF1_TIMACMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF2_TIMBCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF3_TIMCCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF4_TIMCCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF5_TIMCOUT2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF6_TIMECMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF7_TIMECMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF8_TIMFCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF1_TIMACMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF2_TIMBCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF3_TIMCCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF4_TIMFCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF5_TIMFOUT2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF6_TIMDCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF7_TIMDCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF8_TIMDOUT2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF1_TIMACMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF2_TIMBCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF3_TIMCCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF4_TIMDCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF5_TIMDCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF6_TIMECMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF7_TIMECMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF8_TIMEOUT2
*\*\        - SHRTIM_EXEVFLT_WINDOWINGCMP2
*\*\        - SHRTIM_EXEVFLT_WINDOWINGCMP3
*\*\        - SHRTIM_EXEVFLT_WINDOWINGTIM
*\*\return None
**/
void SHRTIM_TIM_SetEventFilter(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Event, uint32_t Filter)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxEXEVFLT1) +
                                            REG_OFFSET_TAB_TIMER[iTimer] + REG_OFFSET_TAB_EXEVCTRL[iEvent]));
    __IO uint32_t *pRegWinSelBypass = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxEXEVFLT1) +
                                      REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, (SHRTIM_TXEXEVFLT1_EXEV1FLT << REG_SHIFT_TAB_EXEVx[iEvent]), (Filter << REG_SHIFT_TAB_EXEVx[iEvent]));
    SET_BIT(*pRegWinSelBypass, SHRTIM_TXEXEVFLT1_EXEVWINSEL);
}

/**
*\*\fun  Get actual event filter settings for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\return Filter This parameter can be one of the following values:
*\*\        - SHRTIM_EXEVFLT_NONE
*\*\        - SHRTIM_EXEVFLT_BLANKINGCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKINGCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKINGCMP3
*\*\        - SHRTIM_EXEVFLT_BLANKINGCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF1_TIMBCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF2_TIMBCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF3_TIMBOUT2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF4_TIMCCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF5_TIMCCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF6_TIMFCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF7_TIMDCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMAEEF8_TIMECMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF1_TIMACMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF2_TIMACMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF3_TIMAOUT2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF4_TIMCCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF5_TIMCCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF6_TIMFCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF7_TIMDCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMBEEF8_TIMECMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF1_TIMACMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF2_TIMBCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF3_TIMBCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF4_TIMFCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF5_TIMDCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF6_TIMDCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF7_TIMDOUT2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMCEEF8_TIMECMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF1_TIMACMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF2_TIMBCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF3_TIMCCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF4_TIMCCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF5_TIMCOUT2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF6_TIMECMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF7_TIMECMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMDEEF8_TIMFCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF1_TIMACMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF2_TIMBCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF3_TIMCCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF4_TIMFCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF5_TIMFOUT2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF6_TIMDCMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF7_TIMDCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMEEEF8_TIMDOUT2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF1_TIMACMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF2_TIMBCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF3_TIMCCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF4_TIMDCMP2
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF5_TIMDCMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF6_TIMECMP1
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF7_TIMECMP4
*\*\        - SHRTIM_EXEVFLT_BLANKING_TIMFEEF8_TIMEOUT2
*\*\        - SHRTIM_EXEVFLT_WINDOWINGCMP2
*\*\        - SHRTIM_EXEVFLT_WINDOWINGCMP3
*\*\        - SHRTIM_EXEVFLT_WINDOWINGTIM
**/
uint32_t SHRTIM_TIM_GetEventFilter(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Event)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxEXEVFLT1) +
                                REG_OFFSET_TAB_TIMER[iTimer] + REG_OFFSET_TAB_EXEVCTRL[iEvent]));
    return (READ_BIT(*pReg, (uint32_t)(SHRTIM_TXEXEVFLT1_EXEV1FLT) << (REG_SHIFT_TAB_EXEVx[iEvent])) >> (REG_SHIFT_TAB_EXEVx[iEvent]));
}

/**
*\*\fun  Enable or disable event latch mechanism for a given timer.
*\*\note This function must not be called when the timer counter is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\param  LatchStatus This parameter can be one of the following values:
*\*\        - SHRTIM_EXEVLATCH_DISABLED
*\*\        - SHRTIM_EXEVLATCH_ENABLED
*\*\return None
**/
void SHRTIM_TIM_SetEventLatchStatus(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Event,
                                    uint32_t LatchStatus)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxEXEVFLT1) +
                                            REG_OFFSET_TAB_TIMER[iTimer] + REG_OFFSET_TAB_EXEVCTRL[iEvent]));
    MODIFY_REG(*pReg, (SHRTIM_TXEXEVFLT1_EXEV1LATCH << REG_SHIFT_TAB_EXEVx[iEvent]), (LatchStatus << REG_SHIFT_TAB_EXEVx[iEvent]));
}

/**
*\*\fun  Get actual event latch status for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\return LatchStatus This parameter can be one of the following values:
*\*\        - SHRTIM_EXEVLATCH_DISABLED
*\*\        - SHRTIM_EXEVLATCH_ENABLED
**/
uint32_t SHRTIM_TIM_GetEventLatchStatus(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Event)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxEXEVFLT1) +
                                REG_OFFSET_TAB_TIMER[iTimer] + REG_OFFSET_TAB_EXEVCTRL[iEvent]));
    return (READ_BIT(*pReg, (uint32_t)(SHRTIM_TXEXEVFLT1_EXEV1LATCH) << REG_SHIFT_TAB_EXEVx[iEvent]) >> (REG_SHIFT_TAB_EXEVx[iEvent]));
}

/**
*\*\fun  Select the Trigger-Half operating mode for a given timer.
*\*\note   This bitfield defines whether the compare 2 register
*\*\note   is behaving in standard mode (compare match issued as soon as counter equal compare)
*\*\note   or in triggered-half mode
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_TRIGHALF_ENABLED
*\*\        - SHRTIM_TRIGHALF_DISABLED
*\*\return None
**/
void SHRTIM_TIM_SetTriggeredHalfMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCTRL2_TRGHLF, Mode);
}

/**
*\*\fun  Get the Trigger-Half operating mode for a given timer.
*\*\note   This bitfield reports whether the compare 2 register
*\*\note   is behaving in standard mode (compare match issued as soon as counter equal compare)
*\*\note   or in triggered-half mode
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return Mode This parameter can be one of the following values:
*\*\        - SHRTIM_TRIGHALF_ENABLED
*\*\        - SHRTIM_TRIGHALF_DISABLED
**/
uint32_t SHRTIM_TIM_GetTriggeredHalfMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXCTRL2_TRGHLF));
}

/**
*\*\fun  Select the compare 1 operating mode.
*\*\note   This bit defines the compare 1 operating mode:
*\*\note   0: the compare 1 event is generated when the counter is equal to the compare value
*\*\note   1: the compare 1 event is generated when the counter is greater than the compare value
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_GTCMP1_EQUAL
*\*\        - SHRTIM_GTCMP1_GREATER
*\*\return None
**/
void SHRTIM_TIM_SetComp1Mode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCTRL2_GTCMP1, Mode);
}

/**
*\*\fun  Get the selected compare 1 operating mode.
*\*\note   This bit reports the compare 1 operating mode:
*\*\note   0: the compare 1 event is generated when the counter is equal to the compare value
*\*\note   1: the compare 1 event is generated when the counter is greater than the compare value
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_GTCMP1_EQUAL
*\*\        - SHRTIM_GTCMP1_GREATER
**/
uint32_t SHRTIM_TIM_GetComp1Mode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXCTRL2_GTCMP1));
}

/**
*\*\fun  Select the compare 3 operating mode.
*\*\note   This bit defines the compare 3 operating mode:
*\*\note   0: the compare 3 event is generated when the counter is equal to the compare value
*\*\note   1: the compare 3 event is generated when the counter is greater than the compare value
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_GTCMP3_EQUAL
*\*\        - SHRTIM_GTCMP3_GREATER
*\*\return None
**/
void SHRTIM_TIM_SetComp3Mode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCTRL2_GTCMP3, (Mode));
}

/**
*\*\fun  Get the selected compare 3 operating mode.
*\*\note   This bit reports the compare 3 operating mode:
*\*\note   0: the compare 3 event is generated when the counter is equal to the compare value
*\*\note   1: the compare 3 event is generated when the counter is greater than the compare value
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return Mode This parameter can be one of the following values:
*\*\        - SHRTIM_GTCMP3_EQUAL
*\*\        - SHRTIM_GTCMP3_GREATER
**/
uint32_t SHRTIM_TIM_GetComp3Mode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0U].TxCTRL2) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXCTRL2_GTCMP3));
}

/**
*\*\fun  Select the roll-over mode.
*\*\note Only significant in up-down counting mode (see function SHRTIM_TIM_SetCountingMode()).
*\*\note Only concerns the Roll-over event with the following destinations: Update trigger, IRQ
 *      and DMA requests, repetition counter decrement and External Event filtering.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_ROLLOVER_MODE_PER
*\*\        - SHRTIM_ROLLOVER_MODE_RST
*\*\        - SHRTIM_ROLLOVER_MODE_BOTH
*\*\return None
**/
void SHRTIM_TIM_SetRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCTRL2_ROM, (Mode << SHRTIM_TXCTRL2_ROM_Pos));
}

/**
*\*\fun  Get selected the roll-over mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return Mode returned value can be one of the following values:
*\*\        - SHRTIM_ROLLOVER_MODE_PER
*\*\        - SHRTIM_ROLLOVER_MODE_RST
*\*\        - SHRTIM_ROLLOVER_MODE_BOTH
**/
uint32_t SHRTIM_TIM_GetRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXCTRL2_ROM) >> SHRTIM_TXCTRL2_ROM_Pos);
}

/**
*\*\fun  Select Fault and Event roll-over mode.
*\*\note Only significant in up-down counting mode (see function SHRTIM_TIM_SetCountingMode()).
*\*\note only concerns the Roll-over event used by the Fault and Event counters.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_ROLLOVER_MODE_PER
*\*\        - SHRTIM_ROLLOVER_MODE_RST
*\*\        - SHRTIM_ROLLOVER_MODE_BOTH
*\*\return None
**/
void SHRTIM_TIM_SetFaultEventRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCTRL2_FEROM, (Mode << SHRTIM_TXCTRL2_FEROM_Pos));
}

/**
*\*\fun  Get selected Fault and Event role-over mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return  Mode returned value can be one of the following values:
*\*\        - SHRTIM_ROLLOVER_MODE_PER
*\*\        - SHRTIM_ROLLOVER_MODE_RST
*\*\        - SHRTIM_ROLLOVER_MODE_BOTH
**/
uint32_t SHRTIM_TIM_GetFaultEventRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXCTRL2_FEROM) >> SHRTIM_TXCTRL2_FEROM_Pos);
}

/**
*\*\fun  Select the Burst mode roll-over mode.
*\*\note Only significant in up-down counting mode (see function SHRTIM_TIM_SetCountingMode()).
*\*\note Only concerns the Roll-over event used in the Burst mode controller, as clock as as burst mode trigger.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_ROLLOVER_MODE_PER
*\*\        - SHRTIM_ROLLOVER_MODE_RST
*\*\        - SHRTIM_ROLLOVER_MODE_BOTH
*\*\return None
**/
void SHRTIM_TIM_SetBMRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCTRL2_BMROM, (Mode << SHRTIM_TXCTRL2_BMROM_Pos));
}

/**
*\*\fun  Get selected Burst mode roll-over mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return  Mode returned value can be one of the following values:
*\*\        - SHRTIM_ROLLOVER_MODE_PER
*\*\        - SHRTIM_ROLLOVER_MODE_RST
*\*\        - SHRTIM_ROLLOVER_MODE_BOTH
**/
uint32_t SHRTIM_TIM_GetBMRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXCTRL2_BMROM) >> SHRTIM_TXCTRL2_BMROM_Pos);
}

/**
*\*\fun  Select the ADC roll-over mode.
*\*\note Only significant in up-down counting mode (see function SHRTIM_TIM_SetCountingMode()).
*\*\note Only concerns the Roll-over event used to trigger the ADC.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_ROLLOVER_MODE_PER
*\*\        - SHRTIM_ROLLOVER_MODE_RST
*\*\        - SHRTIM_ROLLOVER_MODE_BOTH
*\*\return None
**/
void SHRTIM_TIM_SetADCRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCTRL2_ADCROM, (Mode << SHRTIM_TXCTRL2_ADCROM_Pos));
}

/**
*\*\fun  Get selected ADC roll-over mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return  Mode returned value can be one of the following values:
*\*\        - SHRTIM_ROLLOVER_MODE_PER
*\*\        - SHRTIM_ROLLOVER_MODE_RST
*\*\        - SHRTIM_ROLLOVER_MODE_BOTH
**/
uint32_t SHRTIM_TIM_GetADCRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXCTRL2_ADCROM) >> SHRTIM_TXCTRL2_ADCROM_Pos);
}

/**
*\*\fun  Select the ADC roll-over mode.
*\*\note Only significant in up-down counting mode (see function SHRTIM_TIM_SetCountingMode()).
*\*\note Only concerns concerns the Roll-over event which sets and/or resets the outputs,
 *       as per SHRTIM_SETxyR and SHRTIM_RSTxyR settings (see function SHRTIM_OUT_SetOutputSetSrc()
 *       and function SHRTIM_OUT_SetOutputResetSrc() respectively).
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_ROLLOVER_MODE_PER
*\*\        - SHRTIM_ROLLOVER_MODE_RST
*\*\        - SHRTIM_ROLLOVER_MODE_BOTH
*\*\return None
**/
void SHRTIM_TIM_SetOutputRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCTRL2_OUTROM, (Mode << SHRTIM_TXCTRL2_OUTROM_Pos));
}

/**
*\*\fun  Get selected ADC roll-over mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return  Mode returned value can be one of the following values:
*\*\        - SHRTIM_ROLLOVER_MODE_PER
*\*\        - SHRTIM_ROLLOVER_MODE_RST
*\*\        - SHRTIM_ROLLOVER_MODE_BOTH
**/
uint32_t SHRTIM_TIM_GetOutputRollOverMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXCTRL2_OUTROM) >> SHRTIM_TXCTRL2_OUTROM_Pos);
}

/**
*\*\fun  Select the counting mode.
*\*\note The up-down counting mode is available for both continuous and single-shot
 *       (retriggerable and nonretriggerable) operating modes
 *       (see function SHRTIM_TIM_SetCounterMode()).
*\*\note The counter roll-over event is defined differently in-up-down counting mode to
 *       support various operating condition.
 *       See SHRTIM_TIM_SetCounterMode()
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_COUNTING_MODE_UP
*\*\        - SHRTIM_COUNTING_MODE_UP_DOWN
*\*\return None
**/
void SHRTIM_TIM_SetCountingMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCTRL2_UPDOWNM, Mode);
}

/**
*\*\fun  Get selected counting mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return  Mode returned value can be one of the following values:
*\*\        - SHRTIM_COUNTING_MODE_UP
*\*\        - SHRTIM_COUNTING_MODE_UP_DOWN
*\*\return None
**/
uint32_t SHRTIM_TIM_GetCountingMode(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXCTRL2_UPDOWNM));
}

/**
*\*\fun  Select Dual DAC Reset trigger.
*\*\note Significant only when Dual DAC trigger is enabled
 *       (see function SHRTIM_TIM_EnableDualDacTrigger()).
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_DUDACRST_COUNTER
*\*\        - SHRTIM_DUDACRST_OUT1SET
*\*\return None
**/
void SHRTIM_TIM_SetDualDacResetTrigger(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCTRL2_DUDACRST, Mode);
}

/**
*\*\fun  Get selected Dual DAC Reset trigger.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return  Trigger returned value can be one of the following values:
*\*\        - SHRTIM_DUDACRST_COUNTER
*\*\        - SHRTIM_DUDACRST_OUT1SET
**/
uint32_t SHRTIM_TIM_GetDualDacResetTrigger(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXCTRL2_DUDACRST));
}

/**
*\*\fun  Select Dual DAC Step trigger.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_DUDACSTEP_CMP2
*\*\        - SHRTIM_DUDACSTEP_OUT1RST
*\*\return None
**/
void SHRTIM_TIM_SetDualDacStepTrigger(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Mode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCTRL2_DUDACSTEP, Mode);
}

/**
*\*\fun  Get selected Dual DAC Step trigger.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return  Trigger returned value can be one of the following values:
*\*\        - SHRTIM_DUDACSTEP_CMP2
*\*\        - SHRTIM_DUDACSTEP_OUT1RST
**/
uint32_t SHRTIM_TIM_GetDualDacStepTrigger(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXCTRL2_DUDACSTEP));
}

/**
*\*\fun  Enable Dual DAC trigger.
*\*\note Only significant when balanced Idle mode is enabled (see function SHRTIM_TIM_SetDPMode()).
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_EnableDualDacTrigger(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXCTRL2_DUDACEN);
}

/**
*\*\fun  Disable Dual DAC trigger.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_TIM_DisableDualDacTrigger(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXCTRL2_DUDACEN);
}

/**
*\*\fun  Indicate whether Dual DAC trigger is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of DUDACEN bit in SHRTIM_TxCTRL2 register (1 or 0).
**/
uint32_t SHRTIM_TIM_IsEnabledDualDacTrigger(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCTRL2) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXCTRL2_DUDACEN) == (SHRTIM_TXCTRL2_DUDACEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Set the external event counter threshold.
*\*\note The external event is propagated to the timer only if the number
 *       of active edges is greater than the external event counter threshold.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  EventCounter This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_COUNTER_A
*\*\        - SHRTIM_EXEV_COUNTER_B
*\*\param  Threshold This parameter can be a number between Min_Data=0 and Max_Data=63
*\*\return None
**/
void SHRTIM_TIM_SetEventCounterThreshold(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t EventCounter,
        uint32_t Threshold)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[iTimer].TxEXEVFLT3)));

    MODIFY_REG(*pReg, (SHRTIM_TXEXEVFLT3_EXEVCNT << EventCounter), Threshold << (SHRTIM_TXEXEVFLT3_EXEVCNT_Pos + EventCounter));
}

/**
*\*\fun  Get the programmed external event counter threshold.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  EventCounter This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_COUNTER_A
*\*\        - SHRTIM_EXEV_COUNTER_B
*\*\return Threshold Value between Min_Data=0 and Max_Data=63
**/
uint32_t SHRTIM_TIM_GetEventCounterThreshold(SHRTIM_Module *SHRTIMx, uint32_t Timer,
        uint32_t EventCounter)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[iTimer].TxEXEVFLT3)));

    return ((READ_BIT(*pReg, (uint32_t)(SHRTIM_TXEXEVFLT3_EXEVCNT) << EventCounter)) >> ((SHRTIM_TXEXEVFLT3_EXEVCNT_Pos + EventCounter)));
}

/**
*\*\fun  Select the external event counter source.
*\*\note External event counting is only valid for edge-sensitive
 *       external events (See function SHRTIM_EXEV_Config() and function
 *       SHRTIM_EXEV_SetSensitivity()).
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  EventCounter This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_COUNTER_A
*\*\        - SHRTIM_EXEV_COUNTER_B
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\return None
**/
void SHRTIM_TIM_SetEventCounterSource(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t EventCounter,
                                      uint32_t Event)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[iTimer].TxEXEVFLT3)));
    uint32_t iEvent = (uint32_t)(POSITION_VAL(Event));

    /* register SEL value is 0 if SHRTIM_EVENT_1, 1 if SHRTIM_EVENT_1, etc
       and 9 if SHRTIM_EVENT_10 */
    MODIFY_REG(*pReg, (SHRTIM_TXEXEVFLT3_EXEVSEL << EventCounter), iEvent << (SHRTIM_TXEXEVFLT3_EXEVSEL_Pos + EventCounter));
}

/**
*\*\fun  get the selected external event counter source.
 *       SHRTIM_EXEV_SetSensitivity()).
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  EventCounter This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_COUNTER_A
*\*\        - SHRTIM_EXEV_COUNTER_B
*\*\return  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
**/
uint32_t SHRTIM_TIM_GetEventCounterSource(SHRTIM_Module *SHRTIMx, uint32_t Timer,
        uint32_t EventCounter)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[iTimer].TxEXEVFLT3)));

    uint32_t iEvent = (READ_BIT(*pReg, (uint32_t)(SHRTIM_TXEXEVFLT3_EXEVSEL) << (EventCounter))) >> ((SHRTIM_TXEXEVFLT3_EXEVSEL_Pos + EventCounter));

    /* returned value is 0 if SEL is SHRTIM_EVENT_1, 1 if SEL is SHRTIM_EVENT_1, etc
       and 9 if SEL is SHRTIM_EVENT_10 */
    return ((uint32_t)0x1U << iEvent);
}

/**
*\*\fun  Select the external event counter reset mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  EventCounter This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_COUNTER_A
*\*\        - SHRTIM_EXEV_COUNTER_B
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_COUNTER_RSTMODE_UNCONDITIONAL
*\*\        - SHRTIM_EXEV_COUNTER_RSTMODE_CONDITIONAL
*\*\return None
**/
void SHRTIM_TIM_SetEventCounterResetMode(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t EventCounter,
        uint32_t Mode)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[iTimer].TxEXEVFLT3)));

    MODIFY_REG(*pReg, (SHRTIM_TXEXEVFLT3_EXEVRSTM << (EventCounter)), Mode << (EventCounter));
}

/**
*\*\fun  Get selected external event counter reset mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  EventCounter This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_COUNTER_A
*\*\        - SHRTIM_EXEV_COUNTER_B
*\*\return  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_COUNTER_RSTMODE_UNCONDITIONAL
*\*\        - SHRTIM_EXEV_COUNTER_RSTMODE_CONDITIONAL
**/
uint32_t SHRTIM_TIM_GetEventCounterResetMode(SHRTIM_Module *SHRTIMx, uint32_t Timer,
        uint32_t EventCounter)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[iTimer].TxEXEVFLT3)));

    return ((READ_BIT(*pReg, (uint32_t)(SHRTIM_TXEXEVFLT3_EXEVRSTM) << (EventCounter))) >> (EventCounter));
}

/**
*\*\fun  Reset the external event counter.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  EventCounter This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_COUNTER_A
*\*\        - SHRTIM_EXEV_COUNTER_B
*\*\return None
**/
void SHRTIM_TIM_ResetEventCounter(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t EventCounter)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[iTimer].TxEXEVFLT3)));

    SET_BIT(*pReg, (uint32_t)(SHRTIM_TXEXEVFLT3_EXEVCNTRST) << EventCounter);
}

/**
*\*\fun  Enable the external event counter.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  EventCounter This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_COUNTER_A
*\*\        - SHRTIM_EXEV_COUNTER_B
*\*\return None
**/
void SHRTIM_TIM_EnableEventCounter(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t EventCounter)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[iTimer].TxEXEVFLT3)));

    SET_BIT(*pReg, (uint32_t)(SHRTIM_TXEXEVFLT3_EXEVCNTEN) << EventCounter);
}

/**
*\*\fun  Disable the external event counter.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  EventCounter This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_COUNTER_A
*\*\        - SHRTIM_EXEV_COUNTER_B
*\*\return None
**/
void SHRTIM_TIM_DisableEventCounter(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t EventCounter)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[iTimer].TxEXEVFLT3)));

    CLEAR_BIT(*pReg, (SHRTIM_TXEXEVFLT3_EXEVCNTEN << EventCounter));
}

/**
*\*\fun  Indicate whether the external event counter is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  EventCounter This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_COUNTER_A
*\*\        - SHRTIM_EXEV_COUNTER_B
*\*\return State of EXEVCNTEN bit in SHRTIM_TxEXEVFLT3 register (1 or 0).
**/
uint32_t SHRTIM_TIM_IsEnabledEventCounter(SHRTIM_Module *SHRTIMx, uint32_t Timer,
        uint32_t EventCounter)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - POSITION_VAL(SHRTIM_TIMER_A));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[iTimer].TxEXEVFLT3)));

    uint32_t temp; /* MINTSTSAC-2012 compliance */
    temp = READ_BIT(*pReg, (uint32_t)(SHRTIM_TXEXEVFLT3_EXEVCNTEN) << EventCounter);

    return ((temp == ((uint32_t)(SHRTIM_TXEXEVFLT3_EXEVCNTEN) << EventCounter)) ? 1UL : 0UL);
}

/** @defgroup SHRTIM_EF_Dead_Time_Configuration Dead_Time_Configuration
*\*\{
**/

/**
*\*\fun  Configure the dead time insertion feature for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Configuration This parameter must be a combination of all the following values:
*\*\        - SHRTIM_DT_PRESCALER_MUL8 or ... or SHRTIM_DT_PRESCALER_DIV16
*\*\        - SHRTIM_DT_RISING_POSITIVE or SHRTIM_DT_RISING_NEGATIVE
*\*\        - SHRTIM_DT_FALLING_POSITIVE or SHRTIM_DT_FALLING_NEGATIVE
*\*\return None
**/
void SHRTIM_DT_Config(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Configuration)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxDT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXDT_SDTF | SHRTIM_TXDT_DTPSC | SHRTIM_TXDT_SDTR, Configuration);
}

/**
*\*\fun  Set the deadtime prescaler value.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Prescaler This parameter can be one of the following values:
*\*\        - SHRTIM_DT_PRESCALER_MUL8
*\*\        - SHRTIM_DT_PRESCALER_MUL4
*\*\        - SHRTIM_DT_PRESCALER_MUL2
*\*\        - SHRTIM_DT_PRESCALER_DIV1
*\*\        - SHRTIM_DT_PRESCALER_DIV2
*\*\        - SHRTIM_DT_PRESCALER_DIV4
*\*\        - SHRTIM_DT_PRESCALER_DIV8
*\*\        - SHRTIM_DT_PRESCALER_DIV16
*\*\return None
**/
void SHRTIM_DT_SetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Prescaler)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxDT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXDT_DTPSC, Prescaler);
}

/**
*\*\fun  Get actual deadtime prescaler value.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return Prescaler This parameter can be one of the following values:
*\*\        - SHRTIM_DT_PRESCALER_MUL8
*\*\        - SHRTIM_DT_PRESCALER_MUL4
*\*\        - SHRTIM_DT_PRESCALER_MUL2
*\*\        - SHRTIM_DT_PRESCALER_DIV1
*\*\        - SHRTIM_DT_PRESCALER_DIV2
*\*\        - SHRTIM_DT_PRESCALER_DIV4
*\*\        - SHRTIM_DT_PRESCALER_DIV8
*\*\        - SHRTIM_DT_PRESCALER_DIV16
**/
uint32_t SHRTIM_DT_GetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxDT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXDT_DTPSC));
}

/**
*\*\fun  Set the deadtime rising value.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  RisingValue Value between 0 and 0x1FF
*\*\return None
**/
void SHRTIM_DT_SetRisingValue(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t RisingValue)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxDT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXDT_DTR, RisingValue);
}

/**
*\*\fun  Get actual deadtime rising value.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return RisingValue Value between 0 and 0x1FF
**/
uint32_t SHRTIM_DT_GetRisingValue(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxDT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXDT_DTR));
}

/**
*\*\fun  Set the deadtime sign on rising edge.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  RisingSign This parameter can be one of the following values:
*\*\        - SHRTIM_DT_RISING_POSITIVE
*\*\        - SHRTIM_DT_RISING_NEGATIVE
*\*\return None
**/
void SHRTIM_DT_SetRisingSign(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t RisingSign)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxDT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXDT_SDTR, RisingSign);
}

/**
*\*\fun  Get actual deadtime sign on rising edge.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return RisingSign This parameter can be one of the following values:
*\*\        - SHRTIM_DT_RISING_POSITIVE
*\*\        - SHRTIM_DT_RISING_NEGATIVE
**/
uint32_t SHRTIM_DT_GetRisingSign(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxDT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXDT_SDTR));
}

/**
*\*\fun  Set the deadime falling value.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  FallingValue Value between 0 and 0x1FF
*\*\return None
**/
void SHRTIM_DT_SetFallingValue(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t FallingValue)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxDT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXDT_DTF, FallingValue << SHRTIM_TXDT_DTF_Pos);
}

/**
*\*\fun  Get actual deadtime falling value
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return FallingValue Value between 0 and 0x1FF
**/
uint32_t SHRTIM_DT_GetFallingValue(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxDT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return ((READ_BIT(*pReg, SHRTIM_TXDT_DTF)) >> SHRTIM_TXDT_DTF_Pos);
}

/**
*\*\fun  Set the deadtime sign on falling edge.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  FallingSign This parameter can be one of the following values:
*\*\        - SHRTIM_DT_FALLING_POSITIVE
*\*\        - SHRTIM_DT_FALLING_NEGATIVE
*\*\return None
**/
void SHRTIM_DT_SetFallingSign(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t FallingSign)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxDT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXDT_SDTF, FallingSign);
}

/**
*\*\fun  Get actual deadtime sign on falling edge.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return FallingSign This parameter can be one of the following values:
*\*\        - SHRTIM_DT_FALLING_POSITIVE
*\*\        - SHRTIM_DT_FALLING_NEGATIVE
**/
uint32_t SHRTIM_DT_GetFallingSign(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxDT) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXDT_SDTF));
}

/**
*\*\fun  Lock the deadtime value and sign on rising edge.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DT_LockRising(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxDT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXDT_DTRLCK);
}

/**
*\*\fun  Lock the deadtime sign on rising edge.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DT_LockRisingSign(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxDT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXDT_DTRSLCK);
}

/**
*\*\fun  Lock the deadtime value and sign on falling edge.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DT_LockFalling(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxDT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXDT_DTFLCK);
}

/**
*\*\fun  Lock the deadtime sign on falling edge.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DT_LockFallingSign(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxDT) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXDT_DTFSLCK);
}

/** @defgroup SHRTIM_EF_Chopper_Mode_Configuration Chopper_Mode_Configuration
*\*\{
**/

/**
*\*\fun  Configure the chopper stage for a given timer.
*\*\note This function must not be called if the chopper mode is already
 *       enabled for one of the timer outputs.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Configuration This parameter must be a combination of all the following values:
*\*\        - SHRTIM_CHP_PRESCALER_DIV16 or ... or SHRTIM_CHP_PRESCALER_DIV256
*\*\        - SHRTIM_CHP_DUTYCYCLE_0 or ... or SHRTIM_CHP_DUTYCYCLE_875
*\*\        - SHRTIM_CHP_PULSEWIDTH_16 or ... or SHRTIM_CHP_PULSEWIDTH_256
*\*\return None
**/
void SHRTIM_CHP_Config(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Configuration)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCHOP) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCHOP_STARTPW | SHRTIM_TXCHOP_CARDCY | SHRTIM_TXCHOP_CARFRQ, Configuration);
}

/**
*\*\fun  Set prescaler determining the carrier frequency to be added on top
*\*\        of the timer output signals when chopper mode is enabled.
*\*\note This function must not be called if the chopper mode is already
 *       enabled for one of the timer outputs.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  Prescaler This parameter can be one of the following values:
*\*\        - SHRTIM_CHP_PRESCALER_DIV16
*\*\        - SHRTIM_CHP_PRESCALER_DIV32
*\*\        - SHRTIM_CHP_PRESCALER_DIV48
*\*\        - SHRTIM_CHP_PRESCALER_DIV64
*\*\        - SHRTIM_CHP_PRESCALER_DIV80
*\*\        - SHRTIM_CHP_PRESCALER_DIV96
*\*\        - SHRTIM_CHP_PRESCALER_DIV112
*\*\        - SHRTIM_CHP_PRESCALER_DIV128
*\*\        - SHRTIM_CHP_PRESCALER_DIV144
*\*\        - SHRTIM_CHP_PRESCALER_DIV160
*\*\        - SHRTIM_CHP_PRESCALER_DIV176
*\*\        - SHRTIM_CHP_PRESCALER_DIV192
*\*\        - SHRTIM_CHP_PRESCALER_DIV208
*\*\        - SHRTIM_CHP_PRESCALER_DIV224
*\*\        - SHRTIM_CHP_PRESCALER_DIV240
*\*\        - SHRTIM_CHP_PRESCALER_DIV256
*\*\return None
**/
void SHRTIM_CHP_SetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t Prescaler)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCHOP) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCHOP_CARFRQ, Prescaler);
}

/**
*\*\fun  Get actual chopper stage prescaler value.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return Prescaler This parameter can be one of the following values:
*\*\        - SHRTIM_CHP_PRESCALER_DIV16
*\*\        - SHRTIM_CHP_PRESCALER_DIV32
*\*\        - SHRTIM_CHP_PRESCALER_DIV48
*\*\        - SHRTIM_CHP_PRESCALER_DIV64
*\*\        - SHRTIM_CHP_PRESCALER_DIV80
*\*\        - SHRTIM_CHP_PRESCALER_DIV96
*\*\        - SHRTIM_CHP_PRESCALER_DIV112
*\*\        - SHRTIM_CHP_PRESCALER_DIV128
*\*\        - SHRTIM_CHP_PRESCALER_DIV144
*\*\        - SHRTIM_CHP_PRESCALER_DIV160
*\*\        - SHRTIM_CHP_PRESCALER_DIV176
*\*\        - SHRTIM_CHP_PRESCALER_DIV192
*\*\        - SHRTIM_CHP_PRESCALER_DIV208
*\*\        - SHRTIM_CHP_PRESCALER_DIV224
*\*\        - SHRTIM_CHP_PRESCALER_DIV240
*\*\        - SHRTIM_CHP_PRESCALER_DIV256
**/
uint32_t SHRTIM_CHP_GetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCHOP) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXCHOP_CARFRQ));
}

/**
*\*\fun  Set the chopper duty cycle.
*\*\note Duty cycle can be adjusted by 1/8 step (from 0/8 up to 7/8)
*\*\note This function must not be called if the chopper mode is already
 *       enabled for one of the timer outputs.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  DutyCycle This parameter can be one of the following values:
*\*\        - SHRTIM_CHP_DUTYCYCLE_0
*\*\        - SHRTIM_CHP_DUTYCYCLE_125
*\*\        - SHRTIM_CHP_DUTYCYCLE_250
*\*\        - SHRTIM_CHP_DUTYCYCLE_375
*\*\        - SHRTIM_CHP_DUTYCYCLE_500
*\*\        - SHRTIM_CHP_DUTYCYCLE_625
*\*\        - SHRTIM_CHP_DUTYCYCLE_750
*\*\        - SHRTIM_CHP_DUTYCYCLE_875
*\*\return None
**/
void SHRTIM_CHP_SetDutyCycle(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t DutyCycle)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCHOP) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCHOP_CARDCY, DutyCycle);
}

/**
*\*\fun  Get actual chopper duty cycle.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return DutyCycle This parameter can be one of the following values:
*\*\        - SHRTIM_CHP_DUTYCYCLE_0
*\*\        - SHRTIM_CHP_DUTYCYCLE_125
*\*\        - SHRTIM_CHP_DUTYCYCLE_250
*\*\        - SHRTIM_CHP_DUTYCYCLE_375
*\*\        - SHRTIM_CHP_DUTYCYCLE_500
*\*\        - SHRTIM_CHP_DUTYCYCLE_625
*\*\        - SHRTIM_CHP_DUTYCYCLE_750
*\*\        - SHRTIM_CHP_DUTYCYCLE_875
**/
uint32_t SHRTIM_CHP_GetDutyCycle(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCHOP) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXCHOP_CARDCY));
}

/**
*\*\fun  Set the start pulse width.
*\*\note This function must not be called if the chopper mode is already
 *       enabled for one of the timer outputs.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\param  PulseWidth This parameter can be one of the following values:
*\*\        - SHRTIM_CHP_PULSEWIDTH_16
*\*\        - SHRTIM_CHP_PULSEWIDTH_32
*\*\        - SHRTIM_CHP_PULSEWIDTH_48
*\*\        - SHRTIM_CHP_PULSEWIDTH_64
*\*\        - SHRTIM_CHP_PULSEWIDTH_80
*\*\        - SHRTIM_CHP_PULSEWIDTH_96
*\*\        - SHRTIM_CHP_PULSEWIDTH_112
*\*\        - SHRTIM_CHP_PULSEWIDTH_128
*\*\        - SHRTIM_CHP_PULSEWIDTH_144
*\*\        - SHRTIM_CHP_PULSEWIDTH_160
*\*\        - SHRTIM_CHP_PULSEWIDTH_176
*\*\        - SHRTIM_CHP_PULSEWIDTH_192
*\*\        - SHRTIM_CHP_PULSEWIDTH_208
*\*\        - SHRTIM_CHP_PULSEWIDTH_224
*\*\        - SHRTIM_CHP_PULSEWIDTH_240
*\*\        - SHRTIM_CHP_PULSEWIDTH_256
*\*\return None
**/
void SHRTIM_CHP_SetPulseWidth(SHRTIM_Module *SHRTIMx, uint32_t Timer, uint32_t PulseWidth)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCHOP) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    MODIFY_REG(*pReg, SHRTIM_TXCHOP_STARTPW, PulseWidth);
}

/**
*\*\fun  Get actual start pulse width.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return PulseWidth This parameter can be one of the following values:
*\*\        - SHRTIM_CHP_PULSEWIDTH_16
*\*\        - SHRTIM_CHP_PULSEWIDTH_32
*\*\        - SHRTIM_CHP_PULSEWIDTH_48
*\*\        - SHRTIM_CHP_PULSEWIDTH_64
*\*\        - SHRTIM_CHP_PULSEWIDTH_80
*\*\        - SHRTIM_CHP_PULSEWIDTH_96
*\*\        - SHRTIM_CHP_PULSEWIDTH_112
*\*\        - SHRTIM_CHP_PULSEWIDTH_128
*\*\        - SHRTIM_CHP_PULSEWIDTH_144
*\*\        - SHRTIM_CHP_PULSEWIDTH_160
*\*\        - SHRTIM_CHP_PULSEWIDTH_176
*\*\        - SHRTIM_CHP_PULSEWIDTH_192
*\*\        - SHRTIM_CHP_PULSEWIDTH_208
*\*\        - SHRTIM_CHP_PULSEWIDTH_224
*\*\        - SHRTIM_CHP_PULSEWIDTH_240
*\*\        - SHRTIM_CHP_PULSEWIDTH_256
**/
uint32_t SHRTIM_CHP_GetPulseWidth(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxCHOP) +
                                REG_OFFSET_TAB_TIMER[iTimer]));
    return (READ_BIT(*pReg, SHRTIM_TXCHOP_STARTPW));
}

/** @defgroup SHRTIM_EF_Output_Management Output_Management
*\*\{
**/

/**
*\*\fun  Set the timer output set source.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\param SetSrc This parameter can be a combination of the following values:
*\*\        - SHRTIM_OUTPUTSET_NONE
*\*\        - SHRTIM_OUTPUTSET_RESYNC
*\*\        - SHRTIM_OUTPUTSET_TIMPRD
*\*\        - SHRTIM_OUTPUTSET_TIMCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMCMP4
*\*\        - SHRTIM_OUTPUTSET_MASTERPER
*\*\        - SHRTIM_OUTPUTSET_MASTERCMP1
*\*\        - SHRTIM_OUTPUTSET_MASTERCMP2
*\*\        - SHRTIM_OUTPUTSET_MASTERCMP3
*\*\        - SHRTIM_OUTPUTSET_MASTERCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMAEV1_TIMBCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMAEV2_TIMBCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMAEV3_TIMCCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMAEV4_TIMCCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMAEV5_TIMDCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMAEV6_TIMDCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMAEV7_TIMECMP3
*\*\        - SHRTIM_OUTPUTSET_TIMAEV8_TIMECMP4
*\*\        - SHRTIM_OUTPUTSET_TIMAEV9_TIMFCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMBEV1_TIMACMP1
*\*\        - SHRTIM_OUTPUTSET_TIMBEV2_TIMACMP2
*\*\        - SHRTIM_OUTPUTSET_TIMBEV3_TIMCCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMBEV4_TIMCCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMBEV5_TIMDCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMBEV6_TIMDCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMBEV7_TIMECMP1
*\*\        - SHRTIM_OUTPUTSET_TIMBEV8_TIMECMP2
*\*\        - SHRTIM_OUTPUTSET_TIMBEV9_TIMFCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMCEV1_TIMACMP2
*\*\        - SHRTIM_OUTPUTSET_TIMCEV2_TIMACMP3
*\*\        - SHRTIM_OUTPUTSET_TIMCEV3_TIMBCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMCEV4_TIMBCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMCEV5_TIMDCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMCEV6_TIMDCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMCEV7_TIMECMP3
*\*\        - SHRTIM_OUTPUTSET_TIMCEV8_TIMECMP4
*\*\        - SHRTIM_OUTPUTSET_TIMCEV9_TIMFCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMDEV1_TIMACMP1
*\*\        - SHRTIM_OUTPUTSET_TIMDEV2_TIMACMP4
*\*\        - SHRTIM_OUTPUTSET_TIMDEV3_TIMBCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMDEV4_TIMBCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMDEV5_TIMCCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMDEV6_TIMECMP1
*\*\        - SHRTIM_OUTPUTSET_TIMDEV7_TIMECMP4
*\*\        - SHRTIM_OUTPUTSET_TIMDEV8_TIMFCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMDEV9_TIMFCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMEEV1_TIMACMP4
*\*\        - SHRTIM_OUTPUTSET_TIMEEV2_TIMBCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMEEV3_TIMBCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMEEV4_TIMCCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMEEV5_TIMCCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMEEV6_TIMDCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMEEV7_TIMDCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMEEV8_TIMFCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMEEV9_TIMFCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMFEV1_TIMACMP3
*\*\        - SHRTIM_OUTPUTSET_TIMFEV2_TIMBCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMFEV3_TIMBCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMFEV4_TIMCCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMFEV5_TIMCCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMFEV6_TIMDCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMFEV7_TIMDCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMFEV8_TIMECMP2
*\*\        - SHRTIM_OUTPUTSET_TIMFEV9_TIMECMP3
*\*\        - SHRTIM_OUTPUTSET_EXEV_1
*\*\        - SHRTIM_OUTPUTSET_EXEV_2
*\*\        - SHRTIM_OUTPUTSET_EXEV_3
*\*\        - SHRTIM_OUTPUTSET_EXEV_4
*\*\        - SHRTIM_OUTPUTSET_EXEV_5
*\*\        - SHRTIM_OUTPUTSET_EXEV_6
*\*\        - SHRTIM_OUTPUTSET_EXEV_7
*\*\        - SHRTIM_OUTPUTSET_EXEV_8
*\*\        - SHRTIM_OUTPUTSET_EXEV_9
*\*\        - SHRTIM_OUTPUTSET_EXEV_10
*\*\        - SHRTIM_OUTPUTSET_UPDATE
*\*\        (source = TIMy and destination = TIMx, Compare Unit = CMPz).
*\*\return None
**/
void SHRTIM_OUT_SetOutputSetSrc(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t SetSrc)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxSET1) +
                                            REG_OFFSET_TAB_TxSET[iOutput]));
    WRITE_REG(*pReg, SetSrc);
}

/**
*\*\fun  Get the timer output set source.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\return SetSrc This parameter can be a combination of the following values:
*\*\        - SHRTIM_OUTPUTSET_NONE
*\*\        - SHRTIM_OUTPUTSET_RESYNC
*\*\        - SHRTIM_OUTPUTSET_TIMPRD
*\*\        - SHRTIM_OUTPUTSET_TIMCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMCMP4
*\*\        - SHRTIM_OUTPUTSET_MASTERPER
*\*\        - SHRTIM_OUTPUTSET_MASTERCMP1
*\*\        - SHRTIM_OUTPUTSET_MASTERCMP2
*\*\        - SHRTIM_OUTPUTSET_MASTERCMP3
*\*\        - SHRTIM_OUTPUTSET_MASTERCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMAEV1_TIMBCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMAEV2_TIMBCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMAEV3_TIMCCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMAEV4_TIMCCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMAEV5_TIMDCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMAEV6_TIMDCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMAEV7_TIMECMP3
*\*\        - SHRTIM_OUTPUTSET_TIMAEV8_TIMECMP4
*\*\        - SHRTIM_OUTPUTSET_TIMAEV9_TIMFCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMBEV1_TIMACMP1
*\*\        - SHRTIM_OUTPUTSET_TIMBEV2_TIMACMP2
*\*\        - SHRTIM_OUTPUTSET_TIMBEV3_TIMCCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMBEV4_TIMCCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMBEV5_TIMDCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMBEV6_TIMDCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMBEV7_TIMECMP1
*\*\        - SHRTIM_OUTPUTSET_TIMBEV8_TIMECMP2
*\*\        - SHRTIM_OUTPUTSET_TIMBEV9_TIMFCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMCEV1_TIMACMP2
*\*\        - SHRTIM_OUTPUTSET_TIMCEV2_TIMACMP3
*\*\        - SHRTIM_OUTPUTSET_TIMCEV3_TIMBCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMCEV4_TIMBCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMCEV5_TIMDCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMCEV6_TIMDCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMCEV7_TIMECMP3
*\*\        - SHRTIM_OUTPUTSET_TIMCEV8_TIMECMP4
*\*\        - SHRTIM_OUTPUTSET_TIMCEV9_TIMFCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMDEV1_TIMACMP1
*\*\        - SHRTIM_OUTPUTSET_TIMDEV2_TIMACMP4
*\*\        - SHRTIM_OUTPUTSET_TIMDEV3_TIMBCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMDEV4_TIMBCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMDEV5_TIMCCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMDEV6_TIMECMP1
*\*\        - SHRTIM_OUTPUTSET_TIMDEV7_TIMECMP4
*\*\        - SHRTIM_OUTPUTSET_TIMDEV8_TIMFCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMDEV9_TIMFCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMEEV1_TIMACMP4
*\*\        - SHRTIM_OUTPUTSET_TIMEEV2_TIMBCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMEEV3_TIMBCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMEEV4_TIMCCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMEEV5_TIMCCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMEEV6_TIMDCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMEEV7_TIMDCMP2
*\*\        - SHRTIM_OUTPUTSET_TIMEEV8_TIMFCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMEEV9_TIMFCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMFEV1_TIMACMP3
*\*\        - SHRTIM_OUTPUTSET_TIMFEV2_TIMBCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMFEV3_TIMBCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMFEV4_TIMCCMP1
*\*\        - SHRTIM_OUTPUTSET_TIMFEV5_TIMCCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMFEV6_TIMDCMP3
*\*\        - SHRTIM_OUTPUTSET_TIMFEV7_TIMDCMP4
*\*\        - SHRTIM_OUTPUTSET_TIMFEV8_TIMECMP2
*\*\        - SHRTIM_OUTPUTSET_TIMFEV9_TIMECMP3
*\*\        - SHRTIM_OUTPUTSET_EXEV_1
*\*\        - SHRTIM_OUTPUTSET_EXEV_2
*\*\        - SHRTIM_OUTPUTSET_EXEV_3
*\*\        - SHRTIM_OUTPUTSET_EXEV_4
*\*\        - SHRTIM_OUTPUTSET_EXEV_5
*\*\        - SHRTIM_OUTPUTSET_EXEV_6
*\*\        - SHRTIM_OUTPUTSET_EXEV_7
*\*\        - SHRTIM_OUTPUTSET_EXEV_8
*\*\        - SHRTIM_OUTPUTSET_EXEV_9
*\*\        - SHRTIM_OUTPUTSET_EXEV_10
*\*\        - SHRTIM_OUTPUTSET_UPDATE
*\*\        (source = TIMy and destination = TIMx, Compare Unit = CMPz).
**/
uint32_t SHRTIM_OUT_GetOutputSetSrc(SHRTIM_Module *SHRTIMx, uint32_t Output)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxSET1) +
                                REG_OFFSET_TAB_TxSET[iOutput]));
    return (uint32_t)READ_REG(*pReg);
}

/**
*\*\fun  Set the timer output reset source.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\param ResetSrc This parameter can be a combination of the following values:
*\*\        - SHRTIM_OUTPUTRESET_NONE
*\*\        - SHRTIM_OUTPUTRESET_RESYNC
*\*\        - SHRTIM_OUTPUTRESET_TIMPRD
*\*\        - SHRTIM_OUTPUTRESET_TIMCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMCMP4
*\*\        - SHRTIM_OUTPUTRESET_MASTERPER
*\*\        - SHRTIM_OUTPUTRESET_MASTERCMP1
*\*\        - SHRTIM_OUTPUTRESET_MASTERCMP2
*\*\        - SHRTIM_OUTPUTRESET_MASTERCMP3
*\*\        - SHRTIM_OUTPUTRESET_MASTERCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV1_TIMBCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV2_TIMBCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV3_TIMCCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV4_TIMCCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV5_TIMDCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV6_TIMDCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV7_TIMECMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV8_TIMECMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV9_TIMFCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV1_TIMACMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV2_TIMACMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV3_TIMCCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV4_TIMCCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV5_TIMDCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV6_TIMDCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV7_TIMECMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV8_TIMECMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV9_TIMFCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV1_TIMACMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV2_TIMACMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV3_TIMBCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV4_TIMBCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV5_TIMDCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV6_TIMDCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV7_TIMECMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV8_TIMECMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV9_TIMFCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV1_TIMACMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV2_TIMACMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV3_TIMBCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV4_TIMBCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV5_TIMCCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV6_TIMECMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV7_TIMECMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV8_TIMFCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV9_TIMFCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV1_TIMACMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV2_TIMBCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV3_TIMBCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV4_TIMCCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV5_TIMCCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV6_TIMDCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV7_TIMDCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV8_TIMFCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV9_TIMFCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV1_TIMACMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV2_TIMBCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV3_TIMBCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV4_TIMCCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV5_TIMCCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV6_TIMDCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV7_TIMDCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV8_TIMECMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV9_TIMECMP3
*\*\        - SHRTIM_OUTPUTRESET_EXEV_1
*\*\        - SHRTIM_OUTPUTRESET_EXEV_2
*\*\        - SHRTIM_OUTPUTRESET_EXEV_3
*\*\        - SHRTIM_OUTPUTRESET_EXEV_4
*\*\        - SHRTIM_OUTPUTRESET_EXEV_5
*\*\        - SHRTIM_OUTPUTRESET_EXEV_6
*\*\        - SHRTIM_OUTPUTRESET_EXEV_7
*\*\        - SHRTIM_OUTPUTRESET_EXEV_8
*\*\        - SHRTIM_OUTPUTRESET_EXEV_9
*\*\        - SHRTIM_OUTPUTRESET_EXEV_10
*\*\        - SHRTIM_OUTPUTRESET_UPDATE
*\*\        (source = TIMy and destination = TIMx, Compare Unit = CMPz).
*\*\return None
**/
void SHRTIM_OUT_SetOutputResetSrc(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t ResetSrc)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxRST1) +
                                            REG_OFFSET_TAB_TxSET[iOutput]));
    WRITE_REG(*pReg, ResetSrc);
}

/**
*\*\fun  Get the timer output set source.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\return ResetSrc This parameter can be a combination of the following values:
*\*\        - SHRTIM_OUTPUTRESET_NONE
*\*\        - SHRTIM_OUTPUTRESET_RESYNC
*\*\        - SHRTIM_OUTPUTRESET_TIMPRD
*\*\        - SHRTIM_OUTPUTRESET_TIMCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMCMP4
*\*\        - SHRTIM_OUTPUTRESET_MASTERPER
*\*\        - SHRTIM_OUTPUTRESET_MASTERCMP1
*\*\        - SHRTIM_OUTPUTRESET_MASTERCMP2
*\*\        - SHRTIM_OUTPUTRESET_MASTERCMP3
*\*\        - SHRTIM_OUTPUTRESET_MASTERCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV1_TIMBCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV2_TIMBCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV3_TIMCCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV4_TIMCCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV5_TIMDCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV6_TIMDCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV7_TIMECMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV8_TIMECMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMAEV9_TIMFCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV1_TIMACMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV2_TIMACMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV3_TIMCCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV4_TIMCCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV5_TIMDCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV6_TIMDCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV7_TIMECMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV8_TIMECMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMBEV9_TIMFCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV1_TIMACMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV2_TIMACMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV3_TIMBCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV4_TIMBCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV5_TIMDCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV6_TIMDCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV7_TIMECMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV8_TIMECMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMCEV9_TIMFCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV1_TIMACMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV2_TIMACMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV3_TIMBCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV4_TIMBCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV5_TIMCCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV6_TIMECMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV7_TIMECMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV8_TIMFCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMDEV9_TIMFCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV1_TIMACMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV2_TIMBCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV3_TIMBCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV4_TIMCCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV5_TIMCCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV6_TIMDCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV7_TIMDCMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV8_TIMFCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMEEV9_TIMFCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV1_TIMACMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV2_TIMBCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV3_TIMBCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV4_TIMCCMP1
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV5_TIMCCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV6_TIMDCMP3
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV7_TIMDCMP4
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV8_TIMECMP2
*\*\        - SHRTIM_OUTPUTRESET_TIMFEV9_TIMECMP3
*\*\        - SHRTIM_OUTPUTRESET_EXEV_1
*\*\        - SHRTIM_OUTPUTRESET_EXEV_2
*\*\        - SHRTIM_OUTPUTRESET_EXEV_3
*\*\        - SHRTIM_OUTPUTRESET_EXEV_4
*\*\        - SHRTIM_OUTPUTRESET_EXEV_5
*\*\        - SHRTIM_OUTPUTRESET_EXEV_6
*\*\        - SHRTIM_OUTPUTRESET_EXEV_7
*\*\        - SHRTIM_OUTPUTRESET_EXEV_8
*\*\        - SHRTIM_OUTPUTRESET_EXEV_9
*\*\        - SHRTIM_OUTPUTRESET_EXEV_10
*\*\        - SHRTIM_OUTPUTRESET_UPDATE
*\*\        (source = TIMy and destination = TIMx, Compare Unit = CMPz).
**/
uint32_t SHRTIM_OUT_GetOutputResetSrc(SHRTIM_Module *SHRTIMx, uint32_t Output)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxRST1) +
                                REG_OFFSET_TAB_TxSET[iOutput]));
    return (uint32_t)READ_REG(*pReg);
}

/**
*\*\fun  Configure a timer output.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\param  Configuration This parameter must be a combination of all the following values:
*\*\        - SHRTIM_OUT_POSITIVE_POLARITY or SHRTIM_OUT_NEGATIVE_POLARITY
*\*\        - SHRTIM_OUT_IDLELEVEL_INACTIVE or SHRTIM_OUT_IDLELEVEL_ACTIVE
*\*\        - SHRTIM_OUT_FAULTSTATE_NO_ACTION or SHRTIM_OUT_FAULTSTATE_ACTIVE or SHRTIM_OUT_FAULTSTATE_INACTIVE or SHRTIM_OUT_FAULTSTATE_HIGHZ
*\*\        - SHRTIM_OUT_CHOPPERMODE_DISABLED or SHRTIM_OUT_CHOPPERMODE_ENABLED
*\*\        - SHRTIM_OUT_BM_ENTRYMODE_REGULAR or SHRTIM_OUT_BM_ENTRYMODE_DELAYED
*\*\return None
**/
void SHRTIM_OUT_Config(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t Configuration)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                            REG_OFFSET_TAB_TxOUT[iOutput]));
    MODIFY_REG(*pReg, (SHRTIM_OUT_CONFIG_MASK << REG_SHIFT_TAB_TxOUT[iOutput]),
               (Configuration << REG_SHIFT_TAB_TxOUT[iOutput]));
}

/**
*\*\fun  Set the polarity of a timer output.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\param  Polarity This parameter can be one of the following values:
*\*\        - SHRTIM_OUT_POSITIVE_POLARITY
*\*\        - SHRTIM_OUT_NEGATIVE_POLARITY
*\*\return None
**/
void SHRTIM_OUT_SetPolarity(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t Polarity)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                            REG_OFFSET_TAB_TxOUT[iOutput]));
    MODIFY_REG(*pReg, (SHRTIM_TXOUT_POL1 << REG_SHIFT_TAB_TxOUT[iOutput]), (Polarity << REG_SHIFT_TAB_TxOUT[iOutput]));
}

/**
*\*\fun  Get actual polarity of the timer output.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\return Polarity This parameter can be one of the following values:
*\*\        - SHRTIM_OUT_POSITIVE_POLARITY
*\*\        - SHRTIM_OUT_NEGATIVE_POLARITY
**/
uint32_t SHRTIM_OUT_GetPolarity(SHRTIM_Module *SHRTIMx, uint32_t Output)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                REG_OFFSET_TAB_TxOUT[iOutput]));
    return (READ_BIT(*pReg, (uint32_t)(SHRTIM_TXOUT_POL1) << REG_SHIFT_TAB_TxOUT[iOutput]) >> REG_SHIFT_TAB_TxOUT[iOutput]);
}

/**
*\*\fun  Set the output IDLE level.
*\*\note This function must be called prior enabling the timer.
*\*\note Idle level isn't relevant when the output idle mode is set to SHRTIM_OUT_NO_IDLE.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\param  IdleLevel This parameter can be one of the following values:
*\*\        - SHRTIM_OUT_IDLELEVEL_INACTIVE
*\*\        - SHRTIM_OUT_IDLELEVEL_ACTIVE
*\*\return None
**/
void SHRTIM_OUT_SetIdleLevel(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t IdleLevel)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                            REG_OFFSET_TAB_TxOUT[iOutput]));
    MODIFY_REG(*pReg, (SHRTIM_TXOUT_IDLES1 << REG_SHIFT_TAB_TxOUT[iOutput]), (IdleLevel << REG_SHIFT_TAB_TxOUT[iOutput]));
}

/**
*\*\fun  Get actual output IDLE level.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\return IdleLevel This parameter can be one of the following values:
*\*\        - SHRTIM_OUT_IDLELEVEL_INACTIVE
*\*\        - SHRTIM_OUT_IDLELEVEL_ACTIVE
**/
uint32_t SHRTIM_OUT_GetIdleLevel(SHRTIM_Module *SHRTIMx, uint32_t Output)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                REG_OFFSET_TAB_TxOUT[iOutput]));
    return (READ_BIT(*pReg, (uint32_t)(SHRTIM_TXOUT_IDLES1) << REG_SHIFT_TAB_TxOUT[iOutput]) >> REG_SHIFT_TAB_TxOUT[iOutput]);
}

/**
*\*\fun  Set the output FAULT state.
*\*\note This function must not called when the timer is enabled and a fault
 *       channel is enabled at timer level.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\param  FaultState This parameter can be one of the following values:
*\*\        - SHRTIM_OUT_FAULTSTATE_NO_ACTION
*\*\        - SHRTIM_OUT_FAULTSTATE_ACTIVE
*\*\        - SHRTIM_OUT_FAULTSTATE_INACTIVE
*\*\        - SHRTIM_OUT_FAULTSTATE_HIGHZ
*\*\return None
**/
void SHRTIM_OUT_SetFaultState(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t FaultState)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                            REG_OFFSET_TAB_TxOUT[iOutput]));
    MODIFY_REG(*pReg, (SHRTIM_TXOUT_FALT1 << REG_SHIFT_TAB_TxOUT[iOutput]), (FaultState << REG_SHIFT_TAB_TxOUT[iOutput]));
}

/**
*\*\fun  Get actual FAULT state.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\return FaultState This parameter can be one of the following values:
*\*\        - SHRTIM_OUT_FAULTSTATE_NO_ACTION
*\*\        - SHRTIM_OUT_FAULTSTATE_ACTIVE
*\*\        - SHRTIM_OUT_FAULTSTATE_INACTIVE
*\*\        - SHRTIM_OUT_FAULTSTATE_HIGHZ
**/
uint32_t SHRTIM_OUT_GetFaultState(SHRTIM_Module *SHRTIMx, uint32_t Output)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                REG_OFFSET_TAB_TxOUT[iOutput]));
    return (READ_BIT(*pReg, (uint32_t)(SHRTIM_TXOUT_FALT1) << REG_SHIFT_TAB_TxOUT[iOutput]) >> REG_SHIFT_TAB_TxOUT[iOutput]);
}

/**
*\*\fun  Set the output chopper mode.
*\*\note This function must not called when the timer is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\param  ChopperMode This parameter can be one of the following values:
*\*\        - SHRTIM_OUT_CHOPPERMODE_DISABLED
*\*\        - SHRTIM_OUT_CHOPPERMODE_ENABLED
*\*\return None
**/
void SHRTIM_OUT_SetChopperMode(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t ChopperMode)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                            REG_OFFSET_TAB_TxOUT[iOutput]));
    MODIFY_REG(*pReg, (SHRTIM_TXOUT_CHP1 << REG_SHIFT_TAB_TxOUT[iOutput]), (ChopperMode << REG_SHIFT_TAB_TxOUT[iOutput]));
}

/**
*\*\fun  Get actual output chopper mode
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\return ChopperMode This parameter can be one of the following values:
*\*\        - SHRTIM_OUT_CHOPPERMODE_DISABLED
*\*\        - SHRTIM_OUT_CHOPPERMODE_ENABLED
**/
uint32_t SHRTIM_OUT_GetChopperMode(SHRTIM_Module *SHRTIMx, uint32_t Output)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                REG_OFFSET_TAB_TxOUT[iOutput]));
    return (READ_BIT(*pReg, (uint32_t)(SHRTIM_TXOUT_CHP1) << REG_SHIFT_TAB_TxOUT[iOutput]) >> REG_SHIFT_TAB_TxOUT[iOutput]);
}

/**
*\*\fun  Set the output burst mode entry mode.
*\*\note This function must not called when the timer is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\param  BMEntryMode This parameter can be one of the following values:
*\*\        - SHRTIM_OUT_BM_ENTRYMODE_REGULAR
*\*\        - SHRTIM_OUT_BM_ENTRYMODE_DELAYED
*\*\return None
**/
void SHRTIM_OUT_SetBMEntryMode(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t BMEntryMode)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                            REG_OFFSET_TAB_TxOUT[iOutput]));
    MODIFY_REG(*pReg, (SHRTIM_TXOUT_DIDL1 << REG_SHIFT_TAB_TxOUT[iOutput]), (BMEntryMode << REG_SHIFT_TAB_TxOUT[iOutput]));
}

/**
*\*\fun  Get actual output burst mode entry mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\return BMEntryMode This parameter can be one of the following values:
*\*\        - SHRTIM_OUT_BM_ENTRYMODE_REGULAR
*\*\        - SHRTIM_OUT_BM_ENTRYMODE_DELAYED
**/
uint32_t SHRTIM_OUT_GetBMEntryMode(SHRTIM_Module *SHRTIMx, uint32_t Output)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxOUT) +
                                REG_OFFSET_TAB_TxOUT[iOutput]));
    return (READ_BIT(*pReg, (uint32_t)(SHRTIM_TXOUT_DIDL1) << REG_SHIFT_TAB_TxOUT[iOutput]) >> REG_SHIFT_TAB_TxOUT[iOutput]);
}

/**
*\*\fun  Get the level (active or inactive) of the designated output when the
*\*\        delayed protection was triggered.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\return OutputLevel This parameter can be one of the following values:
*\*\        - SHRTIM_OUT_LEVEL_INACTIVE
*\*\        - SHRTIM_OUT_LEVEL_ACTIVE
**/
uint32_t SHRTIM_OUT_GetDPOutStatus(SHRTIM_Module *SHRTIMx, uint32_t Output)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxINTSTS) +
                                REG_OFFSET_TAB_TxOUT[iOutput]));
    return ((READ_BIT(*pReg, (uint32_t)(SHRTIM_TXINTSTS_O1DIPSTS) << REG_SHIFT_TAB_OxSTS[iOutput]) >> REG_SHIFT_TAB_OxSTS[iOutput]) >>
            SHRTIM_TXINTSTS_O1DIPSTS_Pos);
}

/**
*\*\fun  Force the timer output to its active or inactive level.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\param  OutputLevel This parameter can be one of the following values:
*\*\        - SHRTIM_OUT_LEVEL_INACTIVE
*\*\        - SHRTIM_OUT_LEVEL_ACTIVE
*\*\return None
**/
void SHRTIM_OUT_ForceLevel(SHRTIM_Module *SHRTIMx, uint32_t Output, uint32_t OutputLevel)
{
    const uint8_t REG_OFFSET_TAB_OUT_LEVEL[] =
    {
        0x04U, /* 0: SHRTIM_OUT_LEVEL_INACTIVE**/
        0x00U  /* 1: SHRTIM_OUT_LEVEL_ACTIVE**/
    };

    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxSET1) +
                                            REG_OFFSET_TAB_TxSET[iOutput] + REG_OFFSET_TAB_OUT_LEVEL[OutputLevel]));
    SET_BIT(*pReg, SHRTIM_TXSET1_SWT);
}

/**
*\*\fun  Get actual output level, before the output stage (chopper, polarity).
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Output This parameter can be one of the following values:
*\*\        - SHRTIM_OUTPUT_TA1
*\*\        - SHRTIM_OUTPUT_TA2
*\*\        - SHRTIM_OUTPUT_TB1
*\*\        - SHRTIM_OUTPUT_TB2
*\*\        - SHRTIM_OUTPUT_TC1
*\*\        - SHRTIM_OUTPUT_TC2
*\*\        - SHRTIM_OUTPUT_TD1
*\*\        - SHRTIM_OUTPUT_TD2
*\*\        - SHRTIM_OUTPUT_TE1
*\*\        - SHRTIM_OUTPUT_TE2
*\*\        - SHRTIM_OUTPUT_TF1
*\*\        - SHRTIM_OUTPUT_TF2
*\*\return OutputLevel This parameter can be one of the following values:
*\*\        - SHRTIM_OUT_LEVEL_INACTIVE
*\*\        - SHRTIM_OUT_LEVEL_ACTIVE
**/
uint32_t SHRTIM_OUT_GetLevel(SHRTIM_Module *SHRTIMx, uint32_t Output)
{
    uint32_t iOutput = (uint8_t)(POSITION_VAL(Output) - POSITION_VAL(SHRTIM_OUTPUT_TA1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxINTSTS) +
                                REG_OFFSET_TAB_TxOUT[iOutput]));
    return ((READ_BIT(*pReg, (uint32_t)(SHRTIM_TXINTSTS_O1BCKUP) << REG_SHIFT_TAB_OxSTS[iOutput]) >> REG_SHIFT_TAB_OxSTS[iOutput]) >>
            SHRTIM_TXINTSTS_O1BCKUP_Pos);
}


/**
*\*\fun  Configure external event conditioning.
*\*\note This function must not be called when the timer counter is enabled.
*\*\note Event source (EXEVxSRC0..EXEVxSRC10) mapping depends on configured event channel.
*\*\note Fast mode is available for SHRTIM_EVENT_1..10.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\param  Src This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_SOURCE_1
*\*\        - SHRTIM_EXEV_SOURCE_2
*\*\        - SHRTIM_EXEV_SOURCE_3
*\*\        - SHRTIM_EXEV_SOURCE_4
*\*\        - SHRTIM_EXEV_SOURCE_5
*\*\param SrcCompSel This parameter can be one of the following values:
*\*\        - SHRTIM_EXEVXSRC2_COMP1_OUT
*\*\        - SHRTIM_EXEVXSRC2_COMP2_OUT
*\*\        - SHRTIM_EXEVXSRC2_COMP3_OUT
*\*\        - SHRTIM_EXEVXSRC2_COMP4_OUT
*\*\        - SHRTIM_EXEVXSRC2_COMP5_OUT
*\*\        - SHRTIM_EXEVXSRC2_COMP6_OUT
*\*\        - SHRTIM_EXEVXSRC2_COMP7_OUT
*\*\        - SHRTIM_EXEVXSRC2_COMP_NONE
*\*\param  Polarity This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_POLARITY_HIGH
*\*\        - SHRTIM_EXEV_POLARITY_LOW
*\*\param  Sensitivity This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_SENSITIVITY_LEVEL
*\*\        - SHRTIM_EXEV_SENSITIVITY_RISINGEDGE
*\*\        - SHRTIM_EXEV_SENSITIVITY_FALLINGEDGE
*\*\        - SHRTIM_EXEV_SENSITIVITY_BOTHEDGES
*\*\param  FastMode This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_FASTMODE_DISABLE
*\*\        - SHRTIM_EXEV_FASTMODE_ENABLE
*\*\param  Filter This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_FILTER_NONE
*\*\        - SHRTIM_EXEV_FILTER_1
*\*\        - SHRTIM_EXEV_FILTER_2
*\*\        - SHRTIM_EXEV_FILTER_3
*\*\        - SHRTIM_EXEV_FILTER_4
*\*\        - SHRTIM_EXEV_FILTER_5
*\*\        - SHRTIM_EXEV_FILTER_6
*\*\        - SHRTIM_EXEV_FILTER_7
*\*\        - SHRTIM_EXEV_FILTER_8
*\*\        - SHRTIM_EXEV_FILTER_9
*\*\        - SHRTIM_EXEV_FILTER_10
*\*\        - SHRTIM_EXEV_FILTER_11
*\*\        - SHRTIM_EXEV_FILTER_12
*\*\        - SHRTIM_EXEV_FILTER_13
*\*\        - SHRTIM_EXEV_FILTER_14
*\*\        - SHRTIM_EXEV_FILTER_15
*\*\param  Prescaler This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_PRESCALER_DIV1
*\*\        - SHRTIM_EXEV_PRESCALER_DIV2
*\*\        - SHRTIM_EXEV_PRESCALER_DIV4
*\*\        - SHRTIM_EXEV_PRESCALER_DIV8
*\*\return None
*\*\note Polarity configuration is only valid if sensitivity is SHRTIM_EXEV_SENSITIVITY_LEVEL
**/
void SHRTIM_EXEV_Config(SHRTIM_Module *SHRTIMx, uint32_t Event,
                        uint32_t Src, uint32_t SrcCompSel, uint32_t Polarity,
                        uint32_t Sensitivity, uint32_t FastMode,
                        uint32_t Filter, uint32_t Prescaler)
{
    SHRTIM_EXEV_SetSrc(SHRTIMx, Event, Src);
    SHRTIM_EXEV_SetSrcCompSel(SHRTIMx, Event, SrcCompSel);
    SHRTIM_EXEV_SetPolarity(SHRTIMx, Event, Polarity);
    SHRTIM_EXEV_SetSensitivity(SHRTIMx, Event, Sensitivity);
    SHRTIM_EXEV_SetFastMode(SHRTIMx, Event, FastMode);
    SHRTIM_EXEV_SetFilter(SHRTIMx, Event, Filter);
    SHRTIM_EXEV_SetPrescaler(SHRTIMx, Prescaler);
}

/**
*\*\fun  Set the external event source.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\param  Src This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_SOURCE_1
*\*\        - SHRTIM_EXEV_SOURCE_2
*\*\        - SHRTIM_EXEV_SOURCE_3
*\*\        - SHRTIM_EXEV_SOURCE_4
*\*\        - SHRTIM_EXEV_SOURCE_5
*\*\return None
**/
void SHRTIM_EXEV_SetSrc(SHRTIM_Module *SHRTIMx, uint32_t Event, uint32_t Src)
{
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.EXEVCTRL1) +
                                            REG_OFFSET_TAB_EXEVCTRL[iEvent]));
    MODIFY_REG(*pReg, (SHRTIM_EXEVCTRL1_EXEV1SRC << REG_SHIFT_TAB_EXEVx[iEvent]), (Src << REG_SHIFT_TAB_EXEVx[iEvent]));
}

/**
*\*\fun  Get actual external event source.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\return EventSrc This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_SOURCE_1
*\*\        - SHRTIM_EXEV_SOURCE_2
*\*\        - SHRTIM_EXEV_SOURCE_3
*\*\        - SHRTIM_EXEV_SOURCE_4
*\*\        - SHRTIM_EXEV_SOURCE_5
**/
uint32_t SHRTIM_EXEV_GetSrc(SHRTIM_Module *SHRTIMx, uint32_t Event)
{
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.EXEVCTRL1) +
                                REG_OFFSET_TAB_EXEVCTRL[iEvent]));
    return (READ_BIT(*pReg, (uint32_t)(SHRTIM_EXEVCTRL1_EXEV1SRC) << REG_SHIFT_TAB_EXEVx[iEvent]) >> REG_SHIFT_TAB_EXEVx[iEvent]);
}

/**
*\*\fun  Select the analog comparator of SHRTIM_EXEV_SOURCE_2.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\param  SrcCompSel This parameter can be one of the following values:
*\*\        - SHRTIM_EXEVXSRC2_COMP1_OUT
*\*\        - SHRTIM_EXEVXSRC2_COMP2_OUT
*\*\        - SHRTIM_EXEVXSRC2_COMP3_OUT
*\*\        - SHRTIM_EXEVXSRC2_COMP4_OUT
*\*\        - SHRTIM_EXEVXSRC2_COMP5_OUT
*\*\        - SHRTIM_EXEVXSRC2_COMP6_OUT
*\*\        - SHRTIM_EXEVXSRC2_COMP7_OUT
*\*\        - SHRTIM_EXEVXSRC2_COMP_NONE
*\*\return None
**/
void SHRTIM_EXEV_SetSrcCompSel(SHRTIM_Module *SHRTIMx, uint32_t Event, uint32_t SrcCompSel)
{
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)(&SHRTIMx->sCommonRegs.EXEVCTRL5));
    MODIFY_REG(*pReg, (SHRTIM_EXEVCTRL5_EXEV1CSEL << REG_SHIFT_TAB_EXEVxCSEL[iEvent]), (SrcCompSel << REG_SHIFT_TAB_EXEVxCSEL[iEvent]));
}

/**
*\*\fun  Get the the selection of analog comparator of external event source.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\return SrcCompSel  This parameter can be one of the following values:
*\*\        - 3'b000: cmp1 out
*\*\        - 3'b001: cmp2 out
*\*\        - 3'b010: cmp3 out
*\*\        - 3'b011: cmp4 out
*\*\        - 3'b100: cmp5 out
*\*\        - 3'b101: cmp6 out
*\*\        - 3'b110: cmp7 out
**/
uint32_t SHRTIM_EXEV_GetSrcCompSel(SHRTIM_Module *SHRTIMx, uint32_t Event)
{
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)(&SHRTIMx->sCommonRegs.EXEVCTRL5));
    return (READ_BIT(*pReg, (uint32_t)(SHRTIM_EXEVCTRL5_EXEV1CSEL) << REG_SHIFT_TAB_EXEVxCSEL[iEvent]) >> REG_SHIFT_TAB_EXEVxCSEL[iEvent]);
}

/**
*\*\fun  Set the polarity of an external event.
*\*\note This function must not be called when the timer counter is enabled.
*\*\note Event polarity is only significant when event detection is level-sensitive.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\param  Polarity This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_POLARITY_HIGH
*\*\        - SHRTIM_EXEV_POLARITY_LOW
*\*\return None
**/
void SHRTIM_EXEV_SetPolarity(SHRTIM_Module *SHRTIMx, uint32_t Event, uint32_t Polarity)
{
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.EXEVCTRL1) +
                                            REG_OFFSET_TAB_EXEVCTRL[iEvent]));
    MODIFY_REG(*pReg, (SHRTIM_EXEVCTRL1_EXEV1POL << REG_SHIFT_TAB_EXEVx[iEvent]), (Polarity << REG_SHIFT_TAB_EXEVx[iEvent]));
}

/**
*\*\fun  Get actual polarity setting of an external event.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\return Polarity This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_POLARITY_HIGH
*\*\        - SHRTIM_EXEV_POLARITY_LOW
**/
uint32_t SHRTIM_EXEV_GetPolarity(SHRTIM_Module *SHRTIMx, uint32_t Event)
{
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.EXEVCTRL1) +
                                REG_OFFSET_TAB_EXEVCTRL[iEvent]));
    return (READ_BIT(*pReg, (uint32_t)(SHRTIM_EXEVCTRL1_EXEV1POL) << REG_SHIFT_TAB_EXEVx[iEvent]) >> REG_SHIFT_TAB_EXEVx[iEvent]);
}

/**
*\*\fun  Set the sensitivity of an external event.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\param  Sensitivity This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_SENSITIVITY_LEVEL
*\*\        - SHRTIM_EXEV_SENSITIVITY_RISINGEDGE
*\*\        - SHRTIM_EXEV_SENSITIVITY_FALLINGEDGE
*\*\        - SHRTIM_EXEV_SENSITIVITY_BOTHEDGES
*\*\return None
**/

void SHRTIM_EXEV_SetSensitivity(SHRTIM_Module *SHRTIMx, uint32_t Event, uint32_t Sensitivity)
{
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.EXEVCTRL1) +
                                            REG_OFFSET_TAB_EXEVCTRL[iEvent]));
    MODIFY_REG(*pReg, (SHRTIM_EXEVCTRL1_EXEV1SENS << REG_SHIFT_TAB_EXEVx[iEvent]), (Sensitivity << REG_SHIFT_TAB_EXEVx[iEvent]));
}

/**
*\*\fun  Get actual sensitivity setting of an external event.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\return Polarity This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_SENSITIVITY_LEVEL
*\*\        - SHRTIM_EXEV_SENSITIVITY_RISINGEDGE
*\*\        - SHRTIM_EXEV_SENSITIVITY_FALLINGEDGE
*\*\        - SHRTIM_EXEV_SENSITIVITY_BOTHEDGES
**/
uint32_t SHRTIM_EXEV_GetSensitivity(SHRTIM_Module *SHRTIMx, uint32_t Event)
{
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.EXEVCTRL1) +
                                REG_OFFSET_TAB_EXEVCTRL[iEvent]));
    return (READ_BIT(*pReg, (uint32_t)(SHRTIM_EXEVCTRL1_EXEV1SENS) << REG_SHIFT_TAB_EXEVx[iEvent]) >> REG_SHIFT_TAB_EXEVx[iEvent]);
}

/**
*\*\fun  Set the fast mode of an external event.
*\*\note This function must not be called when the timer counter is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\param  FastMode This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_FASTMODE_DISABLE
*\*\        - SHRTIM_EXEV_FASTMODE_ENABLE
*\*\return None
**/
void SHRTIM_EXEV_SetFastMode(SHRTIM_Module *SHRTIMx, uint32_t Event, uint32_t FastMode)
{
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.EXEVCTRL3) +
                                            REG_OFFSET_TAB_EXEVCTRL[iEvent]));
    MODIFY_REG(*pReg, (SHRTIM_EXEVCTRL3_EXEV1FM << REG_SHIFT_TAB_EXEVx[iEvent]), (FastMode << REG_SHIFT_TAB_EXEVx[iEvent]));
}

/**
*\*\fun  Get actual fast mode setting of an external event.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\return FastMode This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_FASTMODE_DISABLE
*\*\        - SHRTIM_EXEV_FASTMODE_ENABLE
**/
uint32_t SHRTIM_EXEV_GetFastMode(SHRTIM_Module *SHRTIMx, uint32_t Event)
{
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.EXEVCTRL3) +
                                REG_OFFSET_TAB_EXEVCTRL[iEvent]));
    return (READ_BIT(*pReg, (uint32_t)(SHRTIM_EXEVCTRL3_EXEV1FM) << REG_SHIFT_TAB_EXEVx[iEvent]) >> REG_SHIFT_TAB_EXEVx[iEvent]);
}

/**
*\*\fun  Set the digital noise filter of a external event.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\param  Filter This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_FILTER_NONE
*\*\        - SHRTIM_EXEV_FILTER_1
*\*\        - SHRTIM_EXEV_FILTER_2
*\*\        - SHRTIM_EXEV_FILTER_3
*\*\        - SHRTIM_EXEV_FILTER_4
*\*\        - SHRTIM_EXEV_FILTER_5
*\*\        - SHRTIM_EXEV_FILTER_6
*\*\        - SHRTIM_EXEV_FILTER_7
*\*\        - SHRTIM_EXEV_FILTER_8
*\*\        - SHRTIM_EXEV_FILTER_9
*\*\        - SHRTIM_EXEV_FILTER_10
*\*\        - SHRTIM_EXEV_FILTER_11
*\*\        - SHRTIM_EXEV_FILTER_12
*\*\        - SHRTIM_EXEV_FILTER_13
*\*\        - SHRTIM_EXEV_FILTER_14
*\*\        - SHRTIM_EXEV_FILTER_15
*\*\return None
**/
void SHRTIM_EXEV_SetFilter(SHRTIM_Module *SHRTIMx, uint32_t Event, uint32_t Filter)
{
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.EXEVCTRL3) +
                                            REG_OFFSET_TAB_EXEVCTRL[iEvent]));
    MODIFY_REG(*pReg, (SHRTIM_EXEVCTRL3_EXEV1F << REG_SHIFT_TAB_EXEVx[iEvent]), (Filter << REG_SHIFT_TAB_EXEVx[iEvent]));
}

/**
*\*\fun  Get actual digital noise filter setting of a external event.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Event This parameter can be one of the following values:
*\*\        - SHRTIM_EVENT_1
*\*\        - SHRTIM_EVENT_2
*\*\        - SHRTIM_EVENT_3
*\*\        - SHRTIM_EVENT_4
*\*\        - SHRTIM_EVENT_5
*\*\        - SHRTIM_EVENT_6
*\*\        - SHRTIM_EVENT_7
*\*\        - SHRTIM_EVENT_8
*\*\        - SHRTIM_EVENT_9
*\*\        - SHRTIM_EVENT_10
*\*\return Filter This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_FILTER_NONE
*\*\        - SHRTIM_EXEV_FILTER_1
*\*\        - SHRTIM_EXEV_FILTER_2
*\*\        - SHRTIM_EXEV_FILTER_3
*\*\        - SHRTIM_EXEV_FILTER_4
*\*\        - SHRTIM_EXEV_FILTER_5
*\*\        - SHRTIM_EXEV_FILTER_6
*\*\        - SHRTIM_EXEV_FILTER_7
*\*\        - SHRTIM_EXEV_FILTER_8
*\*\        - SHRTIM_EXEV_FILTER_9
*\*\        - SHRTIM_EXEV_FILTER_10
*\*\        - SHRTIM_EXEV_FILTER_11
*\*\        - SHRTIM_EXEV_FILTER_12
*\*\        - SHRTIM_EXEV_FILTER_13
*\*\        - SHRTIM_EXEV_FILTER_14
*\*\        - SHRTIM_EXEV_FILTER_15
**/
uint32_t SHRTIM_EXEV_GetFilter(SHRTIM_Module *SHRTIMx, uint32_t Event)
{
    uint32_t iEvent = (uint8_t)(POSITION_VAL(Event) - POSITION_VAL(SHRTIM_EVENT_1));
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.EXEVCTRL3) +
                                REG_OFFSET_TAB_EXEVCTRL[iEvent]));
    return (READ_BIT(*pReg, (uint32_t)(SHRTIM_EXEVCTRL3_EXEV1F) << REG_SHIFT_TAB_EXEVx[iEvent]) >> REG_SHIFT_TAB_EXEVx[iEvent]);
}

/**
*\*\fun  Set the external event prescaler.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Prescaler This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_PRESCALER_DIV1
*\*\        - SHRTIM_EXEV_PRESCALER_DIV2
*\*\        - SHRTIM_EXEV_PRESCALER_DIV4
*\*\        - SHRTIM_EXEV_PRESCALER_DIV8
*\*\return None
**/
void SHRTIM_EXEV_SetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Prescaler)
{
    MODIFY_REG(SHRTIMx->sCommonRegs.EXEVCTRL4, SHRTIM_EXEVCTRL4_EXEVSCD, Prescaler);
}

/**
*\*\fun  Get actual external event prescaler setting.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return Prescaler This parameter can be one of the following values:
*\*\        - SHRTIM_EXEV_PRESCALER_DIV1
*\*\        - SHRTIM_EXEV_PRESCALER_DIV2
*\*\        - SHRTIM_EXEV_PRESCALER_DIV4
*\*\        - SHRTIM_EXEV_PRESCALER_DIV8
**/

uint32_t SHRTIM_EXEV_GetPrescaler(SHRTIM_Module *SHRTIMx)
{
    return (READ_BIT(SHRTIMx->sCommonRegs.EXEVCTRL4, SHRTIM_EXEVCTRL4_EXEVSCD));
}

/**
*\*\fun  Configure fault signal conditioning Polarity and Source.
*\*\note This function must not be called when the fault channel is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\param  Configuration This parameter must be a combination of all the following values:
*\*\        - SHRTIM_FALT_SRC_DIGITALINPUT..SHRTIM_FALT_SRC_INTERNAL..SHRTIM_FALT_SRC_EXEVINPUT..SHRTIM_FALT_SRC_DSMU
*\*\        - SHRTIM_FALT_POLARITY_LOW..SHRTIM_FALT_POLARITY_HIGH
*\*\param  SrcCompSel This parameter can be one of the following values:
*\*\        - SHRTIM_FALTXSRC2_COMP1_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP2_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP3_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP4_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP5_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP6_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP7_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP_NONE
*\*\return None
**/
void SHRTIM_FALT_Config(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t Configuration, uint32_t SrcCompSel)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg1 = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN1)));
    __IO uint32_t *pReg2 = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN2)));

    uint64_t cfg;
    uint64_t mask;

    cfg = ((uint64_t)((uint64_t)Configuration & (uint64_t)SHRTIM_FALT_CONFIG_MASK) << REG_SHIFT_TAB_FALTxF[iFault]) |       /* this for Source 0 and polarity bits */
          (((uint64_t)((uint64_t)Configuration & (uint64_t)SHRTIM_FALT_SRC_1_MASK) << REG_SHIFT_TAB_FALTx[iFault]) << 32U); /* this for Source 1 bit**/

    mask = ((uint64_t)(SHRTIM_FALTIN1_FALT1POL | SHRTIM_FALTIN1_FALT1SRC0) << REG_SHIFT_TAB_FALTxF[iFault]) | /* this for Source 0 and polarity bits */
           ((uint64_t)(SHRTIM_FALT_SRC_1_MASK) << 32U);                                                       /* this for Source bit 1 */

    MODIFY_REG(*pReg1, (uint32_t)(mask), (uint32_t)(cfg));
    MODIFY_REG(*pReg2, (uint32_t)(mask >> 32U), (uint32_t)(cfg >> 32U));

    SHRTIM_FALT_SetSrcCompSel(SHRTIMx, Fault, SrcCompSel);
}

/**
*\*\fun  Set the source of a fault signal.
*\*\note This function must not be called when the fault channel is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\param  Src This parameter can be one of the following values:
*\*\        - SHRTIM_FALT_SRC_DIGITALINPUT
*\*\        - SHRTIM_FALT_SRC_INTERNAL
*\*\        - SHRTIM_FALT_SRC_EXEVINPUT
*\*\        - SHRTIM_FALT_SRC_DSMU
*\*\return None
**/
void SHRTIM_FALT_SetSrc(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t Src)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg1 = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN1)));
    __IO uint32_t *pReg2 = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN2)));

    uint64_t cfg = ((uint64_t)((uint64_t)Src & (uint64_t)SHRTIM_FALTIN1_FALT1SRC0) << REG_SHIFT_TAB_FALTxF[iFault]) |      /* this for Source 0 bit */
                   (((uint64_t)((uint64_t)Src & (uint64_t)SHRTIM_FALT_SRC_1_MASK) << REG_SHIFT_TAB_FALTx[iFault]) << 32U); /* this for Source 1 bit */
    uint64_t mask = ((uint64_t)(SHRTIM_FALTIN1_FALT1SRC0) << REG_SHIFT_TAB_FALTxF[iFault]) |                               /* this for Source bit 0 */
                    (((uint64_t)(SHRTIM_FALTIN2_FALT1SRC1) << REG_SHIFT_TAB_FALTx[iFault]) << 32U);                        /* this for Source bit 1 */

    MODIFY_REG(*pReg1, (uint32_t)(mask), (uint32_t)(cfg));
    MODIFY_REG(*pReg2, (uint32_t)(mask >> 32U), (uint32_t)(cfg >> 32U));
}

/**
*\*\fun  Get actual source of a fault signal.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return Source This parameter can be one of the following values:
*\*\        - SHRTIM_FALT_SRC_DIGITALINPUT
*\*\        - SHRTIM_FALT_SRC_INTERNAL
*\*\        - SHRTIM_FALT_SRC_EXEVINPUT
*\*\        - SHRTIM_FALT_SRC_DSMU
**/
uint32_t SHRTIM_FALT_GetSrc(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg1 = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN1)));
    __IO uint32_t *pReg2 = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN2)));

    uint64_t Src0;
    uint32_t Src1;
    uint32_t temp1, temp2; /* temp variables used for MINTSTSA-C **/

    /* this for Source bit 1 */
    Src1 = READ_BIT(*pReg2, SHRTIM_FALT_SRC_1_MASK) >> REG_SHIFT_TAB_FALTx[iFault];
    temp1 = READ_BIT(*pReg2, (uint32_t)(SHRTIM_FALTIN2_FALT5SRC0 | SHRTIM_FALTIN2_FALT6SRC0));
    temp2 = READ_BIT(*pReg1, (uint32_t)(SHRTIM_FALTIN1_FALT1SRC0 | SHRTIM_FALTIN1_FALT2SRC0 | SHRTIM_FALTIN1_FALT3SRC0 | SHRTIM_FALTIN1_FALT4SRC0));

    /* this for Source bit 0 */
    Src0 = (uint64_t)temp1 << 32U;
    Src0 |= (uint64_t)temp2;
    Src0 = (Src0 >> REG_SHIFT_TAB_FALTxF[iFault]);

    return ((uint32_t)(Src0 | Src1));
}

/**
*\*\fun  Select the analog comparator of fault source 2.
*\*\note This function must not be called when the fault channel is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\param  SrcCompSel This parameter can be one of the following values:
*\*\        - SHRTIM_FALTXSRC2_COMP1_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP2_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP3_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP4_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP5_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP6_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP7_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP_NONE
**/
void SHRTIM_FALT_SetSrcCompSel(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t SrcCompSel)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN5));
    MODIFY_REG(*pReg, (SHRTIM_FALTIN5_FALT1CSEL << REG_SHIFT_TAB_FALTxCSEL[iFault]), (SrcCompSel << REG_SHIFT_TAB_FALTxCSEL[iFault]));
}

/**
*\*\fun  Get the selection the analog comparator of fault source 2.
*\*\note This function must not be called when the fault channel is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return  SrcCompSel This parameter can be one of the following values:
*\*\        - SHRTIM_FALTXSRC2_COMP1_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP2_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP3_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP4_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP5_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP6_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP7_OUT
*\*\        - SHRTIM_FALTXSRC2_COMP_NONE
**/
uint32_t SHRTIM_FALT_GetSrcCompSel(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN5));
    return (READ_BIT(*pReg, (uint32_t)(SHRTIM_FALTIN5_FALT1CSEL) << REG_SHIFT_TAB_FALTxCSEL[iFault]) >> REG_SHIFT_TAB_FALTxCSEL[iFault]);
}

/**
*\*\fun  Set the polarity of a fault signal.
*\*\note This function must not be called when the fault channel is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\param  Polarity This parameter can be one of the following values:
*\*\        - SHRTIM_FALT_POLARITY_LOW
*\*\        - SHRTIM_FALT_POLARITY_HIGH
*\*\return None
**/
void SHRTIM_FALT_SetPolarity(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t Polarity)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg1 = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN1)));
    __IO uint32_t *pReg2 = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN2)));

    uint64_t cfg = (uint64_t)((uint64_t)Polarity & (uint64_t)(SHRTIM_FALTIN1_FALT1POL)) << REG_SHIFT_TAB_FALTxF[iFault]; /* this for Polarity bit */
    uint64_t mask = (uint64_t)(SHRTIM_FALTIN1_FALT1POL) << REG_SHIFT_TAB_FALTxF[iFault];                                 /* this for Polarity bit */

    /* for Polarity bit */
    MODIFY_REG(*pReg1, (uint32_t)(mask), (uint32_t)(cfg));
    MODIFY_REG(*pReg2, (uint32_t)(mask >> 32U), (uint32_t)(cfg >> 32U));
}

/**
*\*\fun  Get actual polarity of a fault signal.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return Polarity This parameter can be one of the following values:
*\*\        - SHRTIM_FALT_POLARITY_LOW
*\*\        - SHRTIM_FALT_POLARITY_HIGH
**/
uint32_t SHRTIM_FALT_GetPolarity(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg1 = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN1)));
    __IO uint32_t *pReg2 = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN2)));
    uint32_t temp1, temp2; /* temp variables used for MINTSTSA-C**/
    uint64_t cfg;

    temp1 = READ_BIT(*pReg2, (uint32_t)(SHRTIM_FALTIN2_FALT5POL | SHRTIM_FALTIN2_FALT6POL));
    temp2 = READ_BIT(*pReg1, (uint32_t)(SHRTIM_FALTIN1_FALT1POL | SHRTIM_FALTIN1_FALT2POL | SHRTIM_FALTIN1_FALT3POL | SHRTIM_FALTIN1_FALT4POL));

    cfg = (uint64_t)temp1 << 32;
    cfg |= (uint64_t)temp2;
    cfg = (cfg >> REG_SHIFT_TAB_FALTxF[iFault]);

    return (uint32_t)(cfg);
}

/**
*\*\fun  Set the digital noise filter of a fault signal.
*\*\note This function must not be called when the fault channel is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\param  Filter This parameter can be one of the following values:
*\*\        - SHRTIM_FALT_FILTER_NONE
*\*\        - SHRTIM_FALT_FILTER_1
*\*\        - SHRTIM_FALT_FILTER_2
*\*\        - SHRTIM_FALT_FILTER_3
*\*\        - SHRTIM_FALT_FILTER_4
*\*\        - SHRTIM_FALT_FILTER_5
*\*\        - SHRTIM_FALT_FILTER_6
*\*\        - SHRTIM_FALT_FILTER_7
*\*\        - SHRTIM_FALT_FILTER_8
*\*\        - SHRTIM_FALT_FILTER_9
*\*\        - SHRTIM_FALT_FILTER_10
*\*\        - SHRTIM_FALT_FILTER_11
*\*\        - SHRTIM_FALT_FILTER_12
*\*\        - SHRTIM_FALT_FILTER_13
*\*\        - SHRTIM_FALT_FILTER_14
*\*\        - SHRTIM_FALT_FILTER_15
*\*\return None
**/
void SHRTIM_FALT_SetFilter(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t Filter)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg1 = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN1)));
    __IO uint32_t *pReg2 = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN2)));

    uint64_t flt = (uint64_t)((uint64_t)Filter & (uint64_t)SHRTIM_FALTIN1_FALT1FLT) << REG_SHIFT_TAB_FALTxF[iFault]; /* this for filter bits */
    uint64_t mask = (uint64_t)(SHRTIM_FALTIN1_FALT1FLT) << REG_SHIFT_TAB_FALTxF[iFault];                             /* this for Polarity bit */

    MODIFY_REG(*pReg1, (uint32_t)(mask), (uint32_t)(flt));
    MODIFY_REG(*pReg2, (uint32_t)(mask >> 32U), (uint32_t)(flt >> 32U));
}

/**
*\*\fun  Get actual digital noise filter setting of a fault signal.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return Filter This parameter can be one of the following values:
*\*\        - SHRTIM_FALT_FILTER_NONE
*\*\        - SHRTIM_FALT_FILTER_1
*\*\        - SHRTIM_FALT_FILTER_2
*\*\        - SHRTIM_FALT_FILTER_3
*\*\        - SHRTIM_FALT_FILTER_4
*\*\        - SHRTIM_FALT_FILTER_5
*\*\        - SHRTIM_FALT_FILTER_6
*\*\        - SHRTIM_FALT_FILTER_7
*\*\        - SHRTIM_FALT_FILTER_8
*\*\        - SHRTIM_FALT_FILTER_9
*\*\        - SHRTIM_FALT_FILTER_10
*\*\        - SHRTIM_FALT_FILTER_11
*\*\        - SHRTIM_FALT_FILTER_12
*\*\        - SHRTIM_FALT_FILTER_13
*\*\        - SHRTIM_FALT_FILTER_14
*\*\        - SHRTIM_FALT_FILTER_15
**/
uint32_t SHRTIM_FALT_GetFilter(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg1 = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN1)));
    __IO uint32_t *pReg2 = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN2)));
    uint32_t temp1, temp2; /* temp variables used for MINTSTSA-C**/
    uint64_t flt;
    temp1 = READ_BIT(*pReg2, (uint32_t)(SHRTIM_FALTIN2_FALT5FLT | SHRTIM_FALTIN2_FALT6FLT));
    temp2 = READ_BIT(*pReg1, (uint32_t)(SHRTIM_FALTIN1_FALT1FLT | SHRTIM_FALTIN1_FALT2FLT | SHRTIM_FALTIN1_FALT3FLT | SHRTIM_FALTIN1_FALT4FLT));

    flt = (uint64_t)temp1 << 32U;
    flt |= (uint64_t)temp2;
    flt = (flt >> REG_SHIFT_TAB_FALTxF[iFault]);

    return (uint32_t)(flt);
}

/**
*\*\fun  Set the fault circuitry prescaler.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Prescaler This parameter can be one of the following values:
*\*\        - SHRTIM_FALT_PRESCALER_DIV1
*\*\        - SHRTIM_FALT_PRESCALER_DIV2
*\*\        - SHRTIM_FALT_PRESCALER_DIV4
*\*\        - SHRTIM_FALT_PRESCALER_DIV8
*\*\return None
**/
void SHRTIM_FALT_SetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Prescaler)
{
    MODIFY_REG(SHRTIMx->sCommonRegs.FALTIN2, SHRTIM_FALTIN2_FALTSCD, Prescaler);
}

/**
*\*\fun  Get actual fault circuitry prescaler setting.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return Prescaler This parameter can be one of the following values:
*\*\        - SHRTIM_FALT_PRESCALER_DIV1
*\*\        - SHRTIM_FALT_PRESCALER_DIV2
*\*\        - SHRTIM_FALT_PRESCALER_DIV4
*\*\        - SHRTIM_FALT_PRESCALER_DIV8
**/
uint32_t SHRTIM_FALT_GetPrescaler(SHRTIM_Module *SHRTIMx)
{
    return (READ_BIT(SHRTIMx->sCommonRegs.FALTIN2, SHRTIM_FALTIN2_FALTSCD));
}

/**
*\*\fun  Lock the fault signal conditioning settings.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return None
**/
void SHRTIM_FALT_Lock(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN1) +
                                            REG_OFFSET_TAB_FALTIN[iFault]));
    SET_BIT(*pReg, (SHRTIM_FALTIN1_FALT1LCK << REG_SHIFT_TAB_FALTxE[iFault]));
}

/**
*\*\fun  Enable the fault circuitry for the designated fault input.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return None
**/
void SHRTIM_FALT_Enable(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN1) +
                                            REG_OFFSET_TAB_FALTIN[iFault]));
    SET_BIT(*pReg, (SHRTIM_FALTIN1_FALT1E << REG_SHIFT_TAB_FALTxE[iFault]));
}

/**
*\*\fun  Disable the fault circuitry for for the designated fault input.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return None
**/
void SHRTIM_FALT_Disable(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN1) +
                                            REG_OFFSET_TAB_FALTIN[iFault]));
    CLEAR_BIT(*pReg, (SHRTIM_FALTIN1_FALT1E << REG_SHIFT_TAB_FALTxE[iFault]));
}

/**
*\*\fun  Indicate whether the fault circuitry is enabled for a given fault input.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return State of FALTxE bit in SHRTIM_FALTINx register (1 or 0).
**/
uint32_t SHRTIM_FALT_IsEnabled(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN1) +
                                REG_OFFSET_TAB_FALTIN[iFault]));
    return (((READ_BIT(*pReg, (SHRTIM_FALTIN1_FALT1E << REG_SHIFT_TAB_FALTxE[iFault])) >> REG_SHIFT_TAB_FALTxE[iFault]) ==
             (SHRTIM_FALTIN1_FALT1E))
            ? 1UL
            : 0UL);
}

/**
*\*\fun  Enable the system fault
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  SysFault This parameter can be one of the following values:
*\*\        - SHRTIM_SYSTEM_FAULT_SHRPLLLOCKFAULT
*\*\        - SHRTIM_SYSTEM_FAULT_PVD
*\*\        - SHRTIM_SYSTEM_FAULT_LOCKUP
*\*\        - SHRTIM_SYSTEM_FAULT_SRAMPARITY
*\*\        - SHRTIM_SYSTEM_FAULT_SRAMECC
*\*\        - SHRTIM_SYSTEM_FAULT_CLOCKSECURITY
*\*\return None
**/
void SHRTIM_FALT_EnableSysFault(SHRTIM_Module *SHRTIMx, uint32_t SysFault)
{
    SET_BIT(SHRTIMx->sCommonRegs.FALTIN2, SysFault);
}

/**
*\*\fun  Indicate whether the system fault is enabled for a given system fault.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  SysFault This parameter can be one of the following values:
*\*\        - SHRTIM_SYSTEM_FAULT_SHRPLLLOCKFAULT
*\*\        - SHRTIM_SYSTEM_FAULT_PVD
*\*\        - SHRTIM_SYSTEM_FAULT_LOCKUP
*\*\        - SHRTIM_SYSTEM_FAULT_SRAMPARITY
*\*\        - SHRTIM_SYSTEM_FAULT_SRAMECC
*\*\        - SHRTIM_SYSTEM_FAULT_CLOCKSECURITY
*\*\return State of system fault enable in SHRTIM_FALTIN2 register
**/
uint32_t SHRTIM_FALT_IsEnabledSysFault(SHRTIM_Module *SHRTIMx, uint32_t SysFault)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.FALTIN2, SysFault) == (SysFault)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the Blanking of the fault circuitry for the designated fault input.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return None
**/
void SHRTIM_FALT_EnableBlanking(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN3) +
                                            REG_OFFSET_TAB_FALTIN[iFault]));
    SET_BIT(*pReg, (uint32_t)(SHRTIM_FALTIN3_FALT1BLKEN) << REG_SHIFT_TAB_FALTxE[iFault]);
}

/**
*\*\fun  Disable the Blanking of the fault circuitry for the designated fault input.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return None
**/
void SHRTIM_FALT_DisableBlanking(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN3) +
                                            REG_OFFSET_TAB_FALTIN[iFault]));
    CLEAR_BIT(*pReg, (SHRTIM_FALTIN3_FALT1BLKEN << REG_SHIFT_TAB_FALTxE[iFault]));
}

/**
*\*\fun  Indicate whether the Blanking of the fault circuitry is enabled for a given fault input.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return State of FALTxBLKEN bit in SHRTIM_FALTINx register (1 or 0).
**/
uint32_t SHRTIM_FALT_IsEnabledBlanking(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN3) +
                                            REG_OFFSET_TAB_FALTIN[iFault]));
    uint32_t temp; /* MINTSTSAC-2012 compliance */
    temp = READ_BIT(*pReg, (uint32_t)(SHRTIM_FALTIN3_FALT1BLKEN) << REG_SHIFT_TAB_FALTxE[iFault]) >> REG_SHIFT_TAB_FALTxE[iFault];

    return ((temp == (SHRTIM_FALTIN3_FALT1BLKEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Set the Blanking Source of the fault circuitry  for a given fault input.
*\*\note Fault inputs can be temporary disabled to blank spurious fault events.
*\*\note This function allows for selection amongst 2 possible blanking sources.
*\*\note Events triggering blanking window start and blanking window end depend
 *       on both the selected blanking source and the fault input.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\param  Source parameter can be one of the following values:
*\*\        - SHRTIM_FALT_BLANKING_RSTALIGNED
*\*\        - SHRTIM_FALT_BLANKING_MOVING
*\*\return None
**/
void SHRTIM_FALT_SetBlankingSrc(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t Source)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN3) +
                                            REG_OFFSET_TAB_FALTIN[iFault]));
    MODIFY_REG(*pReg, (SHRTIM_FALTIN3_FALT1BLKS << REG_SHIFT_TAB_FALTxE[iFault]), (Source << REG_SHIFT_TAB_FALTxE[iFault]));
}

/**
*\*\fun  Get the Blanking Source of the fault circuitry is enabled for a given fault input.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
**/
uint32_t SHRTIM_FALT_GetBlankingSrc(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN3) +
                                REG_OFFSET_TAB_FALTIN[iFault]));
    return ((READ_BIT(*pReg, (uint32_t)(SHRTIM_FALTIN3_FALT1BLKS) << REG_SHIFT_TAB_FALTxE[iFault]) >> REG_SHIFT_TAB_FALTxE[iFault]));
}

/**
*\*\fun  Set the Counter threshold value of a fault counter.
*\*\note This function must not be called when the fault channel is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\param  Threshold This parameter can be a number between Min_Data=0 and Max_Data=15
*\*\return None
**/
void SHRTIM_FALT_SetCounterThreshold(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t Threshold)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN3) +
                                            REG_OFFSET_TAB_FALTIN[iFault]));
    MODIFY_REG(*pReg, (SHRTIM_FALTIN3_FALT1CNT << REG_SHIFT_TAB_FALTxE[iFault]), (Threshold << REG_SHIFT_TAB_FALTxE[iFault]));
}

/**
*\*\fun  Get actual the Counter threshold value of a fault counter.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return Threshold This parameter can be a number between Min_Data=0 and Max_Data=15
**/
uint32_t SHRTIM_FALT_GetCounterThreshold(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN3) +
                                REG_OFFSET_TAB_FALTIN[iFault]));
    return (READ_BIT(*pReg, (uint32_t)(SHRTIM_FALTIN3_FALT1CNT) << REG_SHIFT_TAB_FALTxE[iFault]) >> REG_SHIFT_TAB_FALTxE[iFault]);
}

/**
*\*\fun  Enable soft fault for given fault
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return None
**/
void SHRTIM_FALT_EnableSoftFault(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    SET_BIT(SHRTIMx->sCommonRegs.SFTFALT, Fault);
}

/**
*\*\fun  Indicate whether the soft fault is enabled
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return State of SFTFALTx bit in SHRTIM_SFTFALT register (1 or 0).
**/
uint32_t SHRTIM_FALT_IsEnabledSoftFault(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.SFTFALT, Fault) == (Fault)) ? 1UL : 0UL);
}

/**
*\*\fun  Set the mode of reset of a fault counter to 'always reset'.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_FALT_COUNTERRST_UNCONDITIONAL
*\*\        - SHRTIM_FALT_COUNTERRST_CONDITIONAL
*\*\return None
**/
void SHRTIM_FALT_SetResetMode(SHRTIM_Module *SHRTIMx, uint32_t Fault, uint32_t Mode)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN3) +
                                            REG_OFFSET_TAB_FALTIN[iFault]));
    MODIFY_REG(*pReg, (SHRTIM_FALTIN3_FALT1RSTM << REG_SHIFT_TAB_FALTxE[iFault]), Mode << REG_SHIFT_TAB_FALTxE[iFault]);
}

/**
*\*\fun  Get the mode of reset of a fault counter to 'reset on event'.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_FALT_COUNTERRST_UNCONDITIONAL
*\*\        - SHRTIM_FALT_COUNTERRST_CONDITIONAL
**/
uint32_t SHRTIM_FALT_GetResetMode(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN3) +
                                REG_OFFSET_TAB_FALTIN[iFault]));
    return READ_BIT(*pReg, (uint32_t)(SHRTIM_FALTIN3_FALT1RSTM) << REG_SHIFT_TAB_FALTxE[iFault]);
}

/**
*\*\fun  Reset the fault counter for a fault circuitry
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Fault This parameter can be one of the following values:
*\*\        - SHRTIM_FAULT_1
*\*\        - SHRTIM_FAULT_2
*\*\        - SHRTIM_FAULT_3
*\*\        - SHRTIM_FAULT_4
*\*\        - SHRTIM_FAULT_5
*\*\        - SHRTIM_FAULT_6
*\*\return None
**/
void SHRTIM_FALT_ResetCounter(SHRTIM_Module *SHRTIMx, uint32_t Fault)
{
    uint32_t iFault = (uint8_t)POSITION_VAL(Fault);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sCommonRegs.FALTIN3) +
                                            REG_OFFSET_TAB_FALTIN[iFault]));
    SET_BIT(*pReg, (uint32_t)(SHRTIM_FALTIN3_FALT1CRST) << REG_SHIFT_TAB_FALTxE[iFault]);
}

/**
*\*\fun  Configure the burst mode controller.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Configuration This parameter must be a combination of all the following values:
*\*\        - SHRTIM_BM_MODE_SINGLESHOT or SHRTIM_BM_MODE_CONTINOUS
*\*\        - SHRTIM_BM_CLKSRC_MASTER or ... or SHRTIM_BM_CLKSRC_FSHRTIM
*\*\        - SHRTIM_BM_PRESCALER_DIV1 or ... SHRTIM_BM_PRESCALER_DIV32768
*\*\return None
**/
void SHRTIM_BM_Config(SHRTIM_Module *SHRTIMx, uint32_t Configuration)
{
    MODIFY_REG(SHRTIMx->sCommonRegs.BMCTRL, SHRTIM_BM_CONFIG_MASK, Configuration);
}

/**
*\*\fun  Set the burst mode controller operating mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Mode This parameter can be one of the following values:
*\*\        - SHRTIM_BM_MODE_SINGLESHOT
*\*\        - SHRTIM_BM_MODE_CONTINOUS
*\*\return None
**/
void SHRTIM_BM_SetMode(SHRTIM_Module *SHRTIMx, uint32_t Mode)
{
    MODIFY_REG(SHRTIMx->sCommonRegs.BMCTRL, SHRTIM_BMCTRL_BMOM, Mode);
}

/**
*\*\fun  Get actual burst mode controller operating mode.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return Mode This parameter can be one of the following values:
*\*\        - SHRTIM_BM_MODE_SINGLESHOT
*\*\        - SHRTIM_BM_MODE_CONTINOUS
**/
uint32_t SHRTIM_BM_GetMode(SHRTIM_Module *SHRTIMx)
{
    return (uint32_t)READ_BIT(SHRTIMx->sCommonRegs.BMCTRL, SHRTIM_BMCTRL_BMOM);
}

/**
*\*\fun  Set the burst mode controller clock source.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  ClockSrc This parameter can be one of the following values:
*\*\        - SHRTIM_BM_CLKSRC_MASTER
*\*\        - SHRTIM_BM_CLKSRC_TIMER_A
*\*\        - SHRTIM_BM_CLKSRC_TIMER_B
*\*\        - SHRTIM_BM_CLKSRC_TIMER_C
*\*\        - SHRTIM_BM_CLKSRC_TIMER_D
*\*\        - SHRTIM_BM_CLKSRC_TIMER_E
*\*\        - SHRTIM_BM_CLKSRC_TIMER_F
*\*\        - SHRTIM_BM_CLKSRC_GTIMB1_OC1
*\*\        - SHRTIM_BM_CLKSRC_GTIMB2_OC1
*\*\        - SHRTIM_BM_CLKSRC_GTIMB3_OC1
*\*\        - SHRTIM_BM_CLKSRC_BTIM1_TRGO
*\*\        - SHRTIM_BM_CLKSRC_FSHRTIM
*\*\return None
**/
void SHRTIM_BM_SetClockSrc(SHRTIM_Module *SHRTIMx, uint32_t ClockSrc)
{
    MODIFY_REG(SHRTIMx->sCommonRegs.BMCTRL, SHRTIM_BMCTRL_BMCK, ClockSrc);
}

/**
*\*\fun  Get actual burst mode controller clock source.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return ClockSrc This parameter can be one of the following values:
*\*\        - SHRTIM_BM_CLKSRC_MASTER
*\*\        - SHRTIM_BM_CLKSRC_TIMER_A
*\*\        - SHRTIM_BM_CLKSRC_TIMER_B
*\*\        - SHRTIM_BM_CLKSRC_TIMER_C
*\*\        - SHRTIM_BM_CLKSRC_TIMER_D
*\*\        - SHRTIM_BM_CLKSRC_TIMER_E
*\*\        - SHRTIM_BM_CLKSRC_TIMER_F
*\*\        - SHRTIM_BM_CLKSRC_GTIMB1_OC1
*\*\        - SHRTIM_BM_CLKSRC_GTIMB2_OC1
*\*\        - SHRTIM_BM_CLKSRC_GTIMB3_OC1
*\*\        - SHRTIM_BM_CLKSRC_BTIM1_TRGO
*\*\        - SHRTIM_BM_CLKSRC_FSHRTIM
**/
uint32_t SHRTIM_BM_GetClockSrc(SHRTIM_Module *SHRTIMx)
{
    return (uint32_t)READ_BIT(SHRTIMx->sCommonRegs.BMCTRL, SHRTIM_BMCTRL_BMCK);
}

/**
*\*\fun  Set the burst mode controller prescaler.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Prescaler This parameter can be one of the following values:
*\*\        - SHRTIM_BM_PRESCALER_DIV1
*\*\        - SHRTIM_BM_PRESCALER_DIV2
*\*\        - SHRTIM_BM_PRESCALER_DIV4
*\*\        - SHRTIM_BM_PRESCALER_DIV8
*\*\        - SHRTIM_BM_PRESCALER_DIV16
*\*\        - SHRTIM_BM_PRESCALER_DIV32
*\*\        - SHRTIM_BM_PRESCALER_DIV64
*\*\        - SHRTIM_BM_PRESCALER_DIV128
*\*\        - SHRTIM_BM_PRESCALER_DIV256
*\*\        - SHRTIM_BM_PRESCALER_DIV512
*\*\        - SHRTIM_BM_PRESCALER_DIV1024
*\*\        - SHRTIM_BM_PRESCALER_DIV2048
*\*\        - SHRTIM_BM_PRESCALER_DIV4096
*\*\        - SHRTIM_BM_PRESCALER_DIV8192
*\*\        - SHRTIM_BM_PRESCALER_DIV16384
*\*\        - SHRTIM_BM_PRESCALER_DIV32768
*\*\return None
**/
void SHRTIM_BM_SetPrescaler(SHRTIM_Module *SHRTIMx, uint32_t Prescaler)
{
    MODIFY_REG(SHRTIMx->sCommonRegs.BMCTRL, SHRTIM_BMCTRL_BMPSC, Prescaler);
}

/**
*\*\fun  Get actual burst mode controller prescaler setting.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return Prescaler This parameter can be one of the following values:
*\*\        - SHRTIM_BM_PRESCALER_DIV1
*\*\        - SHRTIM_BM_PRESCALER_DIV2
*\*\        - SHRTIM_BM_PRESCALER_DIV4
*\*\        - SHRTIM_BM_PRESCALER_DIV8
*\*\        - SHRTIM_BM_PRESCALER_DIV16
*\*\        - SHRTIM_BM_PRESCALER_DIV32
*\*\        - SHRTIM_BM_PRESCALER_DIV64
*\*\        - SHRTIM_BM_PRESCALER_DIV128
*\*\        - SHRTIM_BM_PRESCALER_DIV256
*\*\        - SHRTIM_BM_PRESCALER_DIV512
*\*\        - SHRTIM_BM_PRESCALER_DIV1024
*\*\        - SHRTIM_BM_PRESCALER_DIV2048
*\*\        - SHRTIM_BM_PRESCALER_DIV4096
*\*\        - SHRTIM_BM_PRESCALER_DIV8192
*\*\        - SHRTIM_BM_PRESCALER_DIV16384
*\*\        - SHRTIM_BM_PRESCALER_DIV32768
**/
uint32_t SHRTIM_BM_GetPrescaler(SHRTIM_Module *SHRTIMx)
{
    return (uint32_t)READ_BIT(SHRTIMx->sCommonRegs.BMCTRL, SHRTIM_BMCTRL_BMPSC);
}

/**
*\*\fun  Enable burst mode compare and period registers preload.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_BM_EnablePreload(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.BMCTRL, SHRTIM_BMCTRL_BMPLEN);
}

/**
*\*\fun  Disable burst mode compare and period registers preload.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_BM_DisablePreload(SHRTIM_Module *SHRTIMx)
{
    CLEAR_BIT(SHRTIMx->sCommonRegs.BMCTRL, SHRTIM_BMCTRL_BMPLEN);
}

/**
*\*\fun  Indicate whether burst mode compare and period registers are preloaded.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of BMPLEN bit in SHRTIM_BMCTRL register (1 or 0).
**/
uint32_t SHRTIM_BM_IsEnabledPreload(SHRTIM_Module *SHRTIMx)
{
    uint32_t temp; /* MINTSTSAC-2012 compliance */
    temp = READ_BIT(SHRTIMx->sCommonRegs.BMCTRL, SHRTIM_BMCTRL_BMPLEN);

    return ((temp == (SHRTIM_BMCTRL_BMPLEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Set the burst mode controller trigger
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Trig This parameter can be a combination of the following values:
*\*\        - SHRTIM_BM_TRIG_NONE
*\*\        - SHRTIM_BM_TRIG_MASTER_RESET
*\*\        - SHRTIM_BM_TRIG_MASTER_REPETITION
*\*\        - SHRTIM_BM_TRIG_MASTER_CMP1
*\*\        - SHRTIM_BM_TRIG_MASTER_CMP2
*\*\        - SHRTIM_BM_TRIG_MASTER_CMP3
*\*\        - SHRTIM_BM_TRIG_MASTER_CMP4
*\*\        - SHRTIM_BM_TRIG_TIMA_RESET
*\*\        - SHRTIM_BM_TRIG_TIMA_REPETITION
*\*\        - SHRTIM_BM_TRIG_TIMA_CMP1
*\*\        - SHRTIM_BM_TRIG_TIMA_CMP2
*\*\        - SHRTIM_BM_TRIG_TIMB_RESET
*\*\        - SHRTIM_BM_TRIG_TIMB_REPETITION
*\*\        - SHRTIM_BM_TRIG_TIMB_CMP1
*\*\        - SHRTIM_BM_TRIG_TIMB_CMP2
*\*\        - SHRTIM_BM_TRIG_TIMC_RESET
*\*\        - SHRTIM_BM_TRIG_TIMC_REPETITION
*\*\        - SHRTIM_BM_TRIG_TIMC_CMP1
*\*\        - SHRTIM_BM_TRIG_TIMD_RESET
*\*\        - SHRTIM_BM_TRIG_TIMD_REPETITION
*\*\        - SHRTIM_BM_TRIG_TIMD_CMP2
*\*\        - SHRTIM_BM_TRIG_TIME_REPETITION
*\*\        - SHRTIM_BM_TRIG_TIME_CMP1
*\*\        - SHRTIM_BM_TRIG_TIME_CMP2
*\*\        - SHRTIM_BM_TRIG_TIMF_RESET
*\*\        - SHRTIM_BM_TRIG_TIMF_REPETITION
*\*\        - SHRTIM_BM_TRIG_TIMF_CMP1
*\*\        - SHRTIM_BM_TRIG_TIMA_EVENT7
*\*\        - SHRTIM_BM_TRIG_TIMD_EVENT8
*\*\        - SHRTIM_BM_TRIG_EVENT_7
*\*\        - SHRTIM_BM_TRIG_EVENT_8
*\*\        - SHRTIM_BM_TRIG_EVENT_ONCHIP
*\*\return None
**/
void SHRTIM_BM_SetTrig(SHRTIM_Module *SHRTIMx, uint32_t Trig)
{
    WRITE_REG(SHRTIMx->sCommonRegs.BMTG, Trig);
}

/**
*\*\fun  Get actual burst mode controller trigger.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return Trig This parameter can be a combination of the following values:
*\*\        - SHRTIM_BM_TRIG_NONE
*\*\        - SHRTIM_BM_TRIG_MASTER_RESET
*\*\        - SHRTIM_BM_TRIG_MASTER_REPETITION
*\*\        - SHRTIM_BM_TRIG_MASTER_CMP1
*\*\        - SHRTIM_BM_TRIG_MASTER_CMP2
*\*\        - SHRTIM_BM_TRIG_MASTER_CMP3
*\*\        - SHRTIM_BM_TRIG_MASTER_CMP4
*\*\        - SHRTIM_BM_TRIG_TIMA_RESET
*\*\        - SHRTIM_BM_TRIG_TIMA_REPETITION
*\*\        - SHRTIM_BM_TRIG_TIMA_CMP1
*\*\        - SHRTIM_BM_TRIG_TIMA_CMP2
*\*\        - SHRTIM_BM_TRIG_TIMB_RESET
*\*\        - SHRTIM_BM_TRIG_TIMB_REPETITION
*\*\        - SHRTIM_BM_TRIG_TIMB_CMP1
*\*\        - SHRTIM_BM_TRIG_TIMB_CMP2
*\*\        - SHRTIM_BM_TRIG_TIMC_RESET
*\*\        - SHRTIM_BM_TRIG_TIMC_REPETITION
*\*\        - SHRTIM_BM_TRIG_TIMC_CMP1
*\*\        - SHRTIM_BM_TRIG_TIMD_RESET
*\*\        - SHRTIM_BM_TRIG_TIMD_REPETITION
*\*\        - SHRTIM_BM_TRIG_TIMD_CMP2
*\*\        - SHRTIM_BM_TRIG_TIME_REPETITION
*\*\        - SHRTIM_BM_TRIG_TIME_CMP1
*\*\        - SHRTIM_BM_TRIG_TIME_CMP2
*\*\        - SHRTIM_BM_TRIG_TIMF_RESET
*\*\        - SHRTIM_BM_TRIG_TIMF_REPETITION
*\*\        - SHRTIM_BM_TRIG_TIMF_CMP1
*\*\        - SHRTIM_BM_TRIG_TIMA_EVENT7
*\*\        - SHRTIM_BM_TRIG_TIMD_EVENT8
*\*\        - SHRTIM_BM_TRIG_EVENT_7
*\*\        - SHRTIM_BM_TRIG_EVENT_8
*\*\        - SHRTIM_BM_TRIG_EVENT_ONCHIP
**/
uint32_t SHRTIM_BM_GetTrig(SHRTIM_Module *SHRTIMx)
{
    return (uint32_t)READ_REG(SHRTIMx->sCommonRegs.BMTG);
}

/**
*\*\fun  Set the burst mode controller compare value.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  CompareValue
*\*\return None
**/
void SHRTIM_BM_SetCompare(SHRTIM_Module *SHRTIMx, uint32_t CompareValue)
{
    WRITE_REG(SHRTIMx->sCommonRegs.BMCMP, CompareValue);
}

/**
*\*\fun  Get actual burst mode controller compare value.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return CompareValue
*\*\note The IDLE time in burst mode must greater than the period of PWM output
**/
uint32_t SHRTIM_BM_GetCompare(SHRTIM_Module *SHRTIMx)
{
    return (uint32_t)READ_REG(SHRTIMx->sCommonRegs.BMCMP);
}

/**
*\*\fun  Set the burst mode controller period.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Period
*\*\return None
*\*\note The RUN time in burst mode must greater than the period of PWM output
**/
void SHRTIM_BM_SetPeriod(SHRTIM_Module *SHRTIMx, uint32_t Period)
{
    WRITE_REG(SHRTIMx->sCommonRegs.BMPRD, Period);
}

/**
*\*\fun  Get actual burst mode controller period.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return period
**/
uint32_t SHRTIM_BM_GetPeriod(SHRTIM_Module *SHRTIMx)
{
    return (uint32_t)READ_REG(SHRTIMx->sCommonRegs.BMPRD);
}

/**
*\*\fun  Enable the burst mode controller
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_BM_Enable(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.BMCTRL, SHRTIM_BMCTRL_BMEN);
}

/**
*\*\fun  Disable the burst mode controller
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_BM_Disable(SHRTIM_Module *SHRTIMx)
{
    CLEAR_BIT(SHRTIMx->sCommonRegs.BMCTRL, SHRTIM_BMCTRL_BMEN);
}

/**
*\*\fun  Indicate whether the burst mode controller is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of BMEN bit in SHRTIM_BMCTRL register (1 or 0).
**/
uint32_t SHRTIM_BM_IsEnabled(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.BMCTRL, SHRTIM_BMCTRL_BMEN) == (SHRTIM_BMCTRL_BMEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Trigger the burst operation (software trigger)
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_BM_Start(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.BMTG, SHRTIM_BMTG_SWSTRT);
}

/**
*\*\fun  Stop the burst mode operation.
*\*\note Causes a burst mode early termination.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_BM_Stop(SHRTIM_Module *SHRTIMx)
{
    CLEAR_BIT(SHRTIMx->sCommonRegs.BMCTRL, SHRTIM_BMCTRL_BMSTS);
}

/**
*\*\fun  Get actual burst mode status
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return Status This parameter can be one of the following values:
*\*\        - SHRTIM_BM_STATUS_NORMAL
*\*\        - SHRTIM_BM_STATUS_BURST_ONGOING
**/
uint32_t SHRTIM_BM_GetStatus(SHRTIM_Module *SHRTIMx)
{
    return (READ_BIT(SHRTIMx->sCommonRegs.BMCTRL, SHRTIM_BMCTRL_BMSTS));
}

/**
*\*\fun  Clear the Fault 1 interrupt flag.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_ClearFlag_FALT1(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTCLR, SHRTIM_INTCLR_FALT1IC);
}

/**
*\*\fun  Indicate whether Fault 1 interrupt occurred.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of FALT1ITF bit in SHRTIM_INTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_FALT1(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTSTS, SHRTIM_INTSTS_FALT1ITF) == (SHRTIM_INTSTS_FALT1ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the Fault 2 interrupt flag.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_ClearFlag_FALT2(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTCLR, SHRTIM_INTCLR_FALT2IC);
}

/**
*\*\fun  Indicate whether Fault 2 interrupt occurred.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of FALT2ITF bit in SHRTIM_INTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_FALT2(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTSTS, SHRTIM_INTSTS_FALT2ITF) == (SHRTIM_INTSTS_FALT2ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the Fault 3 interrupt flag.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_ClearFlag_FALT3(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTCLR, SHRTIM_INTCLR_FALT3IC);
}

/**
*\*\fun  Indicate whether Fault 3 interrupt occurred.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of FALT3ITF bit in SHRTIM_INTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_FALT3(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTSTS, SHRTIM_INTSTS_FALT3ITF) == (SHRTIM_INTSTS_FALT3ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the Fault 4 interrupt flag.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_ClearFlag_FALT4(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTCLR, SHRTIM_INTCLR_FALT4IC);
}

/**
*\*\fun  Indicate whether Fault 4 interrupt occurred.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of FALT4ITF bit in SHRTIM_INTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_FALT4(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTSTS, SHRTIM_INTSTS_FALT4ITF) == (SHRTIM_INTSTS_FALT4ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the Fault 5 interrupt flag.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_ClearFlag_FALT5(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTCLR, SHRTIM_INTCLR_FALT5IC);
}

/**
*\*\fun  Indicate whether Fault 5 interrupt occurred.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of FALT5ITF bit in SHRTIM_INTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_FALT5(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTSTS, SHRTIM_INTSTS_FALT5ITF) == (SHRTIM_INTSTS_FALT5ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the Fault 6 interrupt flag.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_ClearFlag_FALT6(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTCLR, SHRTIM_INTCLR_FALT6IC);
}

/**
*\*\fun  Indicate whether Fault 6 interrupt occurred.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of FALT6ITF bit in SHRTIM_INTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_FALT6(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTSTS, SHRTIM_INTSTS_FALT6ITF) == (SHRTIM_INTSTS_FALT6ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the System Fault interrupt flag.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_ClearFlag_SYSFALT(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTCLR, SHRTIM_INTCLR_SYSFALTIC);
}

/**
*\*\fun  Indicate whether System Fault interrupt occurred.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of SYSFALTITF bit in SHRTIM_INTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_SYSFALT(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTSTS, SHRTIM_INTSTS_SYSFALTITF) == (SHRTIM_INTSTS_SYSFALTITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the Burst Mode period interrupt flag.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_ClearFlag_BMPRD(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTCLR, SHRTIM_INTCLR_BMPRDIC);
}

/**
*\*\fun  Indicate whether Burst Mode period interrupt occurred.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of BMPRDITF bit in SHRTIM_INTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_BMPRD(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTSTS, SHRTIM_INTSTS_BMPRDITF) == (SHRTIM_INTSTS_BMPRDITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the Synchronization Input interrupt flag.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_ClearFlag_SYNC(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sMasterRegs.MINTCLR, SHRTIM_MINTCLR_SYNCINIC);
}

/**
*\*\fun  Indicate whether the Synchronization Input interrupt occurred.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of SYNCINITF bit in SHRTIM_MINTSTS register  (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_SYNC(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sMasterRegs.MINTSTS, SHRTIM_MINTSTS_SYNCINITF) == (SHRTIM_MINTSTS_SYNCINITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the update interrupt flag for a given timer (including the master timer) .
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ClearFlag_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTCLR) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MINTCLR_MUPDIC);
}

/**
*\*\fun  Indicate whether the update interrupt has occurred for a given timer (including the master timer) .
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MUPDITF/UPDITF bit in SHRTIM_MINTSTS/SHRTIM_TxINTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MINTSTS_MUPDITF) == (SHRTIM_MINTSTS_MUPDITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the repetition interrupt flag for a given timer (including the master timer) .
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
*\*\note For master timer, repetition interrupt enabled bit is bit4, for TA~TF, is bit5
**/
void SHRTIM_ClearFlag_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer;
    __IO uint32_t *pReg;

    if(Timer != SHRTIM_TIMER_MASTER)
    {
        iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
        pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxINTCLR) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
        SET_BIT(*pReg, SHRTIM_TXINTCLR_REPTIC);
    }
    else
    {
        pReg = (__IO uint32_t *)((uint32_t)(&SHRTIMx->sMasterRegs.MINTCLR));
        SET_BIT(*pReg, SHRTIM_MINTCLR_MREPTIC);
    }
}

/**
*\*\fun  Indicate whether the repetition  interrupt has occurred for a given timer (including the master timer) .
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MREPTITF/REPTITF bit in SHRTIM_MINTSTS/SHRTIM_TxINTSTS register (1 or 0).
*\*\note For master timer, repetition interrupt enabled bit is bit4, for TA~TF, is bit5
**/
uint32_t SHRTIM_IsActiveFlag_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer;
    __IO uint32_t *pReg;

    if(Timer != SHRTIM_TIMER_MASTER)
    {
        iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
        pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxINTSTS) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
        return ((READ_BIT(*pReg, SHRTIM_TXINTSTS_REPTITF) == (SHRTIM_TXINTSTS_REPTITF)) ? 1UL : 0UL);
    }
    else
    {
        pReg = (__IO uint32_t *)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS));
        return ((READ_BIT(*pReg, SHRTIM_MINTSTS_MREPTITF) == (SHRTIM_MINTSTS_MREPTITF)) ? 1UL : 0UL);
    }
}

/**
*\*\fun  Clear the compare 1 match interrupt for a given timer (including the master timer).
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ClearFlag_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTCLR) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MINTCLR_MCMP1IC);
}

/**
*\*\fun  Indicate whether the compare match 1  interrupt has occurred for a given timer (including the master timer) .
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MCMP1ITF/CMP1ITF bit in SHRTIM_MINTSTS/SHRTIM_TxINTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MINTSTS_MCMP1ITF) == (SHRTIM_MINTSTS_MCMP1ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the compare 2 match interrupt for a given timer (including the master timer).
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ClearFlag_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTCLR) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MINTCLR_MCMP2IC);
}

/**
*\*\fun  Indicate whether the compare match 2  interrupt has occurred for a given timer (including the master timer) .
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MCMP2ITF/CMP2ITF bit in SHRTIM_MINTSTS/SHRTIM_TxINTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MINTSTS_MCMP2ITF) == (SHRTIM_MINTSTS_MCMP2ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the compare 3 match interrupt for a given timer (including the master timer).
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ClearFlag_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTCLR) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MINTCLR_MCMP3IC);
}

/**
*\*\fun  Indicate whether the compare match 3  interrupt has occurred for a given timer (including the master timer) .
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MCMP3ITF/CMP3ITF bit in SHRTIM_MINTSTS/SHRTIM_TxINTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MINTSTS_MCMP3ITF) == (SHRTIM_MINTSTS_MCMP3ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the compare 4 match interrupt for a given timer (including the master timer).
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ClearFlag_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTCLR) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MINTCLR_MCMP4IC);
}

/**
*\*\fun  Indicate whether the compare match 4  interrupt has occurred for a given timer (including the master timer) .
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MCMP4ITF/CMP4ITF bit in SHRTIM_MINTSTS/SHRTIM_TxINTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MINTSTS_MCMP4ITF) == (SHRTIM_MINTSTS_MCMP4ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the compare 5 match for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ClearFlag_CMP5(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxINTCLR) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXINTCLR_CMP5IC);
}

/**
*\*\fun  Indicate whether the compare match 5 has occurred for a given timer .
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of CMP5ITF bit in SHRTIM_TXINTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_CMP5(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXINTSTS_CMP5ITF) == (SHRTIM_TXINTSTS_CMP5ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the capture 1 interrupt flag for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ClearFlag_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTCLR) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXINTCLR_CPT1IC);
}

/**
*\*\fun  Indicate whether the capture 1 interrupt occurred for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of CPT1ITF bit in SHRTIM_TxINTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXINTSTS_CPT1ITF) == (SHRTIM_TXINTSTS_CPT1ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the capture 2 interrupt flag for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ClearFlag_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTCLR) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXINTCLR_CPT2IC);
}

/**
*\*\fun  Indicate whether the capture 2 interrupt occurred for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of CPT2ITF bit in SHRTIM_TxINTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXINTSTS_CPT2ITF) == (SHRTIM_TXINTSTS_CPT2ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the output 1 set interrupt flag for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ClearFlag_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTCLR) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXINTCLR_SET1IC);
}

/**
*\*\fun  Indicate whether the output 1 set interrupt occurred for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of SET1ITF bit in SHRTIM_TxINTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXINTSTS_SET1ITF) == (SHRTIM_TXINTSTS_SET1ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the output 1 reset interrupt flag for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ClearFlag_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTCLR) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXINTCLR_RST1IC);
}

/**
*\*\fun  Indicate whether the output 1 reset interrupt occurred for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of RST1ITF bit in SHRTIM_TxINTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXINTSTS_RST1ITF) == (SHRTIM_TXINTSTS_RST1ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the output 2 set interrupt flag for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ClearFlag_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTCLR) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXINTCLR_SET2IC);
}

/**
*\*\fun  Indicate whether the output 2 set interrupt occurred for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of SET2ITF bit in SHRTIM_TxINTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXINTSTS_SET2ITF) == (SHRTIM_TXINTSTS_SET2ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the output 2reset interrupt flag for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ClearFlag_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTCLR) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXINTCLR_RST2IC);
}

/**
*\*\fun  Indicate whether the output 2 reset interrupt occurred for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of RST2ITF bit in SHRTIM_TxINTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXINTSTS_RST2ITF) == (SHRTIM_TXINTSTS_RST2ITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the reset and/or roll-over interrupt flag for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ClearFlag_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTCLR) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXINTCLR_RSTROIC);
}

/**
*\*\fun  Indicate whether the  reset and/or roll-over interrupt occurred for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of RSTROITF bit in SHRTIM_TxINTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXINTSTS_RSTROITF) == (SHRTIM_TXINTSTS_RSTROITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Clear the delayed protection interrupt flag for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_ClearFlag_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTCLR) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXINTCLR_DPIC);
}

/**
*\*\fun  Indicate whether the  delayed protection interrupt occurred for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of DPITF bit in SHRTIM_TxINTSTS register (1 or 0).
**/
uint32_t SHRTIM_IsActiveFlag_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MINTSTS) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXINTSTS_DPITF) == (SHRTIM_TXINTSTS_DPITF)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the fault 1 interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_EnableIT_FALT1(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT1IEN);
}

/**
*\*\fun  Disable the fault 1 interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_DisableIT_FALT1(SHRTIM_Module *SHRTIMx)
{
    CLEAR_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT1IEN);
}

/**
*\*\fun  Indicate whether the fault 1 interrupt is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of FALT1IEN bit in SHRTIM_INTEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_FALT1(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT1IEN) == (SHRTIM_INTEN_FALT1IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the fault 2 interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_EnableIT_FALT2(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT2IEN);
}

/**
*\*\fun  Disable the fault 2 interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_DisableIT_FALT2(SHRTIM_Module *SHRTIMx)
{
    CLEAR_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT2IEN);
}

/**
*\*\fun  Indicate whether the fault 2 interrupt is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of FALT2IEN bit in SHRTIM_INTEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_FALT2(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT2IEN) == (SHRTIM_INTEN_FALT2IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the fault 3 interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_EnableIT_FALT3(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT3IEN);
}

/**
*\*\fun  Disable the fault 3 interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_DisableIT_FALT3(SHRTIM_Module *SHRTIMx)
{
    CLEAR_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT3IEN);
}

/**
*\*\fun  Indicate whether the fault 3 interrupt is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of FALT3IEN bit in SHRTIM_INTEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_FALT3(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT3IEN) == (SHRTIM_INTEN_FALT3IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the fault 4 interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_EnableIT_FALT4(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT4IEN);
}

/**
*\*\fun  Disable the fault 4 interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_DisableIT_FALT4(SHRTIM_Module *SHRTIMx)
{
    CLEAR_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT4IEN);
}

/**
*\*\fun  Indicate whether the fault 4 interrupt is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of FALT4IEN bit in SHRTIM_INTEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_FALT4(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT4IEN) == (SHRTIM_INTEN_FALT4IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the fault 5 interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_EnableIT_FALT5(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT5IEN);
}

/**
*\*\fun  Disable the fault 5 interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_DisableIT_FALT5(SHRTIM_Module *SHRTIMx)
{
    CLEAR_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT5IEN);
}

/**
*\*\fun  Indicate whether the fault 5 interrupt is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of FALT5IEN bit in SHRTIM_INTEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_FALT5(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT5IEN) == (SHRTIM_INTEN_FALT5IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the fault 6 interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_EnableIT_FALT6(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT6IEN);
}

/**
*\*\fun  Disable the fault 6 interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_DisableIT_FALT6(SHRTIM_Module *SHRTIMx)
{
    CLEAR_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT6IEN);
}

/**
*\*\fun  Indicate whether the fault 6 interrupt is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of FALT6IEN bit in SHRTIM_INTEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_FALT6(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_FALT6IEN) == (SHRTIM_INTEN_FALT6IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the system fault interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_EnableIT_SYSFALT(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_SYSFALTIEN);
}

/**
*\*\fun  Disable the system fault interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_DisableIT_SYSFALT(SHRTIM_Module *SHRTIMx)
{
    CLEAR_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_SYSFALTIEN);
}

/**
*\*\fun  Indicate whether the system fault interrupt is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of SYSFALTIEN bit in SHRTIM_INTEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_SYSFALT(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_SYSFALTIEN) == (SHRTIM_INTEN_SYSFALTIEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the burst mode period interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_EnableIT_BMPRD(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_BMPRDIEN);
}

/**
*\*\fun  Disable the burst mode period interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_DisableIT_BMPRD(SHRTIM_Module *SHRTIMx)
{
    CLEAR_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_BMPRDIEN);
}

/**
*\*\fun  Indicate whether the burst mode period interrupt is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of BMPRDIEN bit in SHRTIM_INTEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_BMPRD(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sCommonRegs.INTEN, SHRTIM_INTEN_BMPRDIEN) == (SHRTIM_INTEN_BMPRDIEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the synchronization input interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_EnableIT_SYNC(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sMasterRegs.MIDEN, SHRTIM_MIDEN_SYNCINIEN);
}

/**
*\*\fun  Disable the synchronization input interrupt.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_DisableIT_SYNC(SHRTIM_Module *SHRTIMx)
{
    CLEAR_BIT(SHRTIMx->sMasterRegs.MIDEN, SHRTIM_MIDEN_SYNCINIEN);
}

/**
*\*\fun  Indicate whether the synchronization input interrupt is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of SYNCINIEN bit in SHRTIM_MIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_SYNC(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sMasterRegs.MIDEN, SHRTIM_MIDEN_SYNCINIEN) == (SHRTIM_MIDEN_SYNCINIEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the update interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableIT_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MIDEN_MUPDIEN);
}

/**
*\*\fun  Disable the update interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableIT_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_MIDEN_MUPDIEN);
}

/**
*\*\fun  Indicate whether the update interrupt is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MUPDIEN/UPDIEN bit in SHRTIM_MIDEN/SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MIDEN_MUPDIEN) == (SHRTIM_MIDEN_MUPDIEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the repetition interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
*\*\note For master timer, repetition interrupt enabled bit is bit4, for TA~TF, is bit5
**/
void SHRTIM_EnableIT_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer;
    __IO uint32_t *pReg;

    if(Timer != SHRTIM_TIMER_MASTER)
    {
        iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
        pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
        SET_BIT(*pReg, SHRTIM_TXIDEN_REPTIEN);
    }
    else
    {
        pReg = (__IO uint32_t *)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN));
        SET_BIT(*pReg, SHRTIM_MIDEN_MREPTIEN);
    }
}

/**
*\*\fun  Disable the repetition interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
*\*\note For master timer, repetition interrupt enabled bit is bit4, for TA~TF, is bit5
**/
void SHRTIM_DisableIT_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer;
    __IO uint32_t *pReg;

    if(Timer != SHRTIM_TIMER_MASTER)
    {
        iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
        pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
        CLEAR_BIT(*pReg, SHRTIM_TXIDEN_REPTIEN);
    }
    else
    {
        pReg = (__IO uint32_t *)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN));
        CLEAR_BIT(*pReg, SHRTIM_MIDEN_MREPTIEN);
    }
}

/**
*\*\fun  Indicate whether the repetition interrupt is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MREPTIEN/REPTIEN bit in SHRTIM_MIDEN/SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer;
    __IO uint32_t *pReg;

    if(Timer != SHRTIM_TIMER_MASTER)
    {
        iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_TACNTEN_Pos);
        pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sTimerxRegs[0].TxIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
        return ((READ_BIT(*pReg, SHRTIM_TXIDEN_REPTIEN) == (SHRTIM_TXIDEN_REPTIEN)) ? 1UL : 0UL);
    }
    else
    {
        pReg = (__IO uint32_t *)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN));
        return ((READ_BIT(*pReg, SHRTIM_MIDEN_MREPTIEN) == (SHRTIM_MIDEN_MREPTIEN)) ? 1UL : 0UL);
    }
}

/**
*\*\fun  Enable the compare 1 interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableIT_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MIDEN_MCMP1IEN);
}

/**
*\*\fun  Disable the compare 1 interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableIT_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_MIDEN_MCMP1IEN);
}

/**
*\*\fun  Indicate whether the compare 1 interrupt is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MCMP1IEN/CMP1IEN bit in SHRTIM_MIDEN/SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MIDEN_MCMP1IEN) == (SHRTIM_MIDEN_MCMP1IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the compare 2 interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableIT_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MIDEN_MCMP2IEN);
}

/**
*\*\fun  Disable the compare 2 interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableIT_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_MIDEN_MCMP2IEN);
}

/**
*\*\fun  Indicate whether the compare 2 interrupt is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MCMP2IEN/CMP2IEN bit in SHRTIM_MIDEN/SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MIDEN_MCMP2IEN) == (SHRTIM_MIDEN_MCMP2IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the compare 3 interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableIT_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MIDEN_MCMP3IEN);
}

/**
*\*\fun  Disable the compare 3 interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableIT_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_MIDEN_MCMP3IEN);
}

/**
*\*\fun  Indicate whether the compare 3 interrupt is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MCMP3IEN/CMP3IEN bit in SHRTIM_MIDEN/SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MIDEN_MCMP3IEN) == (SHRTIM_MIDEN_MCMP3IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the compare 4 interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableIT_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MIDEN_MCMP4IEN);
}

/**
*\*\fun  Disable the compare 4 interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableIT_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_MIDEN_MCMP4IEN);
}

/**
*\*\fun  Indicate whether the compare 4 interrupt is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MCMP4IEN/CMP4IEN bit in SHRTIM_MIDEN/SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MIDEN_MCMP4IEN) == (SHRTIM_MIDEN_MCMP4IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the capture 1 interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableIT_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_CPT1IEN);
}

/**
*\*\fun  Enable the capture 1 interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableIT_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_CPT1IEN);
}

/**
*\*\fun  Indicate whether the capture 1 interrupt is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of CPT1IEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_CPT1IEN) == (SHRTIM_TXIDEN_CPT1IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the capture 2 interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableIT_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_CPT2IEN);
}

/**
*\*\fun  Enable the capture 2 interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableIT_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_CPT2IEN);
}

/**
*\*\fun  Indicate whether the capture 2 interrupt is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of CPT2IEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_CPT2IEN) == (SHRTIM_TXIDEN_CPT2IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the output 1 set interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableIT_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_SET1IEN);
}

/**
*\*\fun  Disable the output 1 set interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableIT_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_SET1IEN);
}

/**
*\*\fun  Indicate whether the output 1 set interrupt is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of SET1IEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_SET1IEN) == (SHRTIM_TXIDEN_SET1IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the output 1 reset interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableIT_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_RST1IEN);
}

/**
*\*\fun  Disable the output 1 reset interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableIT_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_RST1IEN);
}

/**
*\*\fun  Indicate whether the output 1 reset interrupt is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of RST1IEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_RST1IEN) == (SHRTIM_TXIDEN_RST1IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the output 2 set interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableIT_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_SET2IEN);
}

/**
*\*\fun  Disable the output 2 set interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableIT_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_SET2IEN);
}

/**
*\*\fun  Indicate whether the output 2 set interrupt is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of SET2IEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_SET2IEN) == (SHRTIM_TXIDEN_SET2IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the output 2 reset interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableIT_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_RST2IEN);
}

/**
*\*\fun  Disable the output 2 reset interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableIT_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_RST2IEN);
}

/**
*\*\fun  Indicate whether the output 2 reset SHRTIM_IsEnabledIT_RST2 is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of RST2IEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_RST2IEN) == (SHRTIM_TXIDEN_RST2IEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the reset/roll-over interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableIT_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_RSTROIEN);
}

/**
*\*\fun  Disable the reset/roll-over interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableIT_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_RSTROIEN);
}

/**
*\*\fun  Indicate whether the reset/roll-over interrupt is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of RSTROIEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_RSTROIEN) == (SHRTIM_TXIDEN_RSTROIEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the delayed protection interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableIT_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_DPIEN);
}

/**
*\*\fun  Disable the delayed protection interrupt for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableIT_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_DPIEN);
}

/**
*\*\fun  Indicate whether the delayed protection interrupt is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of DPIEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledIT_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_DPIEN) == (SHRTIM_TXIDEN_DPIEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the synchronization input DMA request.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_EnableDMAReq_SYNC(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sMasterRegs.MIDEN, SHRTIM_MIDEN_SYNCINDEN);
}

/**
*\*\fun  Disable the synchronization input DMA request
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_DisableDMAReq_SYNC(SHRTIM_Module *SHRTIMx)
{
    CLEAR_BIT(SHRTIMx->sMasterRegs.MIDEN, SHRTIM_MIDEN_SYNCINDEN);
}

/**
*\*\fun  Indicate whether the synchronization input DMA request is enabled.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return State of SYNCINDEN bit in SHRTIM_MIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledDMAReq_SYNC(SHRTIM_Module *SHRTIMx)
{
    return ((READ_BIT(SHRTIMx->sMasterRegs.MIDEN, SHRTIM_MIDEN_SYNCINDEN) == (SHRTIM_MIDEN_SYNCINDEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the update DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableDMAReq_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MIDEN_MUPDDEN);
}

/**
*\*\fun  Disable the update DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableDMAReq_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_MIDEN_MUPDDEN);
}

/**
*\*\fun  Indicate whether the update DMA request is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MUPDDEN/UPDDEN bit in SHRTIM_MIDEN/SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledDMAReq_UPDATE(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MIDEN_MUPDDEN) == (SHRTIM_MIDEN_MUPDDEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the repetition DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableDMAReq_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MIDEN_MREPTDEN);
}

/**
*\*\fun  Disable the repetition DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableDMAReq_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_MIDEN_MREPTDEN);
}

/**
*\*\fun  Indicate whether the repetition DMA request is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MREPTDEN/REPTDEN bit in SHRTIM_MIDEN/SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledDMAReq_REP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MIDEN_MREPTDEN) == (SHRTIM_MIDEN_MREPTDEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the compare 1 DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableDMAReq_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MIDEN_MCMP1DEN);
}

/**
*\*\fun  Disable the compare 1 DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableDMAReq_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_MIDEN_MCMP1DEN);
}

/**
*\*\fun  Indicate whether the compare 1 DMA request is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MCMP1DEN/CMP1DEN bit in SHRTIM_MIDEN/SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledDMAReq_CMP1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MIDEN_MCMP1DEN) == (SHRTIM_MIDEN_MCMP1DEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the compare 2 DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableDMAReq_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MIDEN_MCMP2DEN);
}

/**
*\*\fun  Disable the compare 2 DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableDMAReq_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_MIDEN_MCMP2DEN);
}

/**
*\*\fun  Indicate whether the compare 2 DMA request is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MCMP2DEN/CMP2DEN bit in SHRTIM_MIDEN/SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledDMAReq_CMP2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MIDEN_MCMP2DEN) == (SHRTIM_MIDEN_MCMP2DEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the compare 3 DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableDMAReq_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MIDEN_MCMP3DEN);
}

/**
*\*\fun  Disable the compare 3 DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableDMAReq_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_MIDEN_MCMP3DEN);
}

/**
*\*\fun  Indicate whether the compare 3 DMA request is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MCMP3DEN/CMP3DEN bit in SHRTIM_MIDEN/SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledDMAReq_CMP3(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MIDEN_MCMP3DEN) == (SHRTIM_MIDEN_MCMP3DEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the compare 4 DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableDMAReq_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_MIDEN_MCMP4DEN);
}

/**
*\*\fun  Disable the compare 4 DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableDMAReq_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_MIDEN_MCMP4DEN);
}

/**
*\*\fun  Indicate whether the compare 4 DMA request is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of MCMP4DEN/CMP4DEN bit in SHRTIM_MIDEN/SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledDMAReq_CMP4(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_MIDEN_MCMP4DEN) == (SHRTIM_MIDEN_MCMP4DEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the capture 1 DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableDMAReq_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_CPT1DEN);
}

/**
*\*\fun  Disable the capture 1 DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableDMAReq_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_CPT1DEN);
}

/**
*\*\fun  Indicate whether the capture 1 DMA request is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of CPT1DEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledDMAReq_CPT1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_CPT1DEN) == (SHRTIM_TXIDEN_CPT1DEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the capture 2 DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableDMAReq_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_CPT2DEN);
}

/**
*\*\fun  Disable the capture 2 DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableDMAReq_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_CPT2DEN);
}

/**
*\*\fun  Indicate whether the capture 2 DMA request is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of CPT2DEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledDMAReq_CPT2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_CPT2DEN) == (SHRTIM_TXIDEN_CPT2DEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the output 1 set  DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableDMAReq_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_SET1DEN);
}

/**
*\*\fun  Disable the output 1 set  DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableDMAReq_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_SET1DEN);
}

/**
*\*\fun  Indicate whether the output 1 set  DMA request is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of SET1DEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledDMAReq_SET1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_SET1DEN) == (SHRTIM_TXIDEN_SET1DEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the output 1 reset  DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableDMAReq_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_RST1DEN);
}

/**
*\*\fun  Disable the output 1 reset  DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableDMAReq_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_RST1DEN);
}

/**
*\*\fun  Indicate whether the output 1 reset interrupt is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of RST1DEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledDMAReq_RST1(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_RST1DEN) == (SHRTIM_TXIDEN_RST1DEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the output 2 set  DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableDMAReq_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_SET2DEN);
}

/**
*\*\fun  Disable the output 2 set  DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableDMAReq_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_SET2DEN);
}

/**
*\*\fun  Indicate whether the output 2 set  DMA request is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of SET2DEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledDMAReq_SET2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_SET2DEN) == (SHRTIM_TXIDEN_SET2DEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the output 2 reset  DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableDMAReq_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_RST2DEN);
}

/**
*\*\fun  Disable the output 2 reset  DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableDMAReq_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_RST2DEN);
}

/**
*\*\fun  Indicate whether the output 2 reset  DMA request is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of RST2DEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledDMAReq_RST2(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_RST2DEN) == (SHRTIM_TXIDEN_RST2DEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the reset/roll-over DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableDMAReq_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_RSTRODEN);
}

/**
*\*\fun  Disable the reset/roll-over DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableDMAReq_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_RSTRODEN);
}

/**
*\*\fun  Indicate whether the reset/roll-over DMA request is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of RSTRODEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledDMAReq_RST(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_RSTRODEN) == (SHRTIM_TXIDEN_RSTRODEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Enable the delayed protection DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableDMAReq_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    SET_BIT(*pReg, SHRTIM_TXIDEN_DPDEN);
}

/**
*\*\fun  Disable the delayed protection DMA request for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableDMAReq_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                            REG_OFFSET_TAB_TIMER[iTimer]));
    CLEAR_BIT(*pReg, SHRTIM_TXIDEN_DPDEN);
}

/**
*\*\fun  Indicate whether the delayed protection DMA request is enabled for a given timer.
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return State of DPDEN bit in SHRTIM_TxIDEN register (1 or 0).
**/
uint32_t SHRTIM_IsEnabledDMAReq_DP(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    uint32_t iTimer = (uint8_t)(POSITION_VAL(Timer) - SHRTIM_MCTRL_MCNTEN_Pos);
    const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&SHRTIMx->sMasterRegs.MIDEN) +
                                REG_OFFSET_TAB_TIMER[iTimer]));

    return ((READ_BIT(*pReg, SHRTIM_TXIDEN_DPDEN) == (SHRTIM_TXIDEN_DPDEN)) ? 1UL : 0UL);
}

/**
*\*\fun  Disable halt all timers counter(master + slave) while in debug mode
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_DisableDebugHaltAllTimers(SHRTIM_Module *SHRTIMx)
{
    SET_BIT(SHRTIMx->sMasterRegs.FRZDIS, SHRTIM_FRZDIS_ALLTIMDBGEN);
}

/**
*\*\fun  Enable halt all timers counter(master + slave) while in debug mode
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
void SHRTIM_EnableDebugHaltAllTimers(SHRTIM_Module *SHRTIMx)
{
    CLEAR_BIT(SHRTIMx->sMasterRegs.FRZDIS, SHRTIM_FRZDIS_ALLTIMDBGEN);
}

/**
*\*\fun  Is all timers counter(master + slave) be halted while in debug mode
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return None
**/
uint32_t SHRTIM_IsEnabledDebugHaltAllTimers(SHRTIM_Module *SHRTIMx)
{
    return (READ_BIT(SHRTIMx->sMasterRegs.FRZDIS, SHRTIM_FRZDIS_ALLTIMDBGEN) == 0UL) ? 1UL : 0UL;
}
/**
*\*\fun  Enable halt a given timer counter while in debug mode
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_EnableDebugHaltTimer(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    CLEAR_BIT(SHRTIMx->sMasterRegs.FRZDIS, ((Timer >> SHRTIM_MCTRL_MCNTEN_Pos) & SHRTIM_FRZDIS_CONFIG_MASK));
}

/**
*\*\fun  Disable halt a given timer counter while in debug mode
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
void SHRTIM_DisableDebugHaltTimer(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    SET_BIT(SHRTIMx->sMasterRegs.FRZDIS, ((Timer >> SHRTIM_MCTRL_MCNTEN_Pos) & SHRTIM_FRZDIS_CONFIG_MASK));
}

/**
*\*\fun  Is a given timer counter halted while in debug mode
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  Timer This parameter can be one of the following values:
*\*\        - SHRTIM_TIMER_MASTER
*\*\        - SHRTIM_TIMER_A
*\*\        - SHRTIM_TIMER_B
*\*\        - SHRTIM_TIMER_C
*\*\        - SHRTIM_TIMER_D
*\*\        - SHRTIM_TIMER_E
*\*\        - SHRTIM_TIMER_F
*\*\return None
**/
uint32_t SHRTIM_IsEnabledDebugHaltTimer(SHRTIM_Module *SHRTIMx, uint32_t Timer)
{
    return (READ_BIT(SHRTIMx->sMasterRegs.FRZDIS, ((Timer >> SHRTIM_MCTRL_MCNTEN_Pos) & SHRTIM_FRZDIS_CONFIG_MASK)) == 0UL) ? 1UL : 0UL;
}

/**
*\*\fun  Set Auxilira output bypass
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\param  AuxBypa This parameter can be one of the following values:
*\*\        - SHRTIM_AUXOUTPUT_DEFAULT             aunxiliary output signals is follow main output
*\*\        - SHRTIM_AUXOUTPUT_FOLLOW_CROSSBAR     aunxiliary output signals is follow crossbar
*\*\        - SHRTIM_AUXOUTPUT_FOLLOW_MAINOUTPUT   aunxiliary output signals is follow main output
*\*\return None
**/
void SHRTIM_SetAuxliaryBypass(SHRTIM_Module *SHRTIMx, uint32_t AuxBypa)
{
    SET_BIT(SHRTIMx->sCommonRegs.EXTEND, AuxBypa);
}

/**
*\*\fun  get Auxilira output bypass
*\*\param  SHRTIMx Super High Resolution Timer instance
*\*\return
*\*\        - SHRTIM_AUXOUTPUT_DEFAULT             aunxiliary output signals is follow main output
*\*\        - SHRTIM_AUXOUTPUT_FOLLOW_CROSSBAR     aunxiliary output signals is follow crossbar
*\*\        - SHRTIM_AUXOUTPUT_FOLLOW_MAINOUTPUT   aunxiliary output signals is follow main output
**/
uint32_t SHRTIM_GetAuxliaryBypass(SHRTIM_Module *SHRTIMx)
{
    return READ_BIT(SHRTIMx->sCommonRegs.EXTEND, SHRITM_AUXOUTPUT_BYPASS);
}

