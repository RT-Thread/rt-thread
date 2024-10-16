/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : FLEXIO
*   Dependencies         : 
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 5.0.0
*   Build Version        : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
*   Copyright 2020 - 2024 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef FLEXIO_UART_IP_HWACCESS_H
#define FLEXIO_UART_IP_HWACCESS_H

/**
*   @file
*   @internal
*   @defgroup flexio_ip Flexio IPL
*   @addtogroup  flexio_ip Flexio  IPL
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Flexio_Uart_Ip_Types.h"
#include "OsIf.h"
#ifdef FLEXIO_UART_IP_IS_USING
    #if (FLEXIO_UART_IP_IS_USING == STD_ON)
        #include "Flexio_Mcl_Ip_HwAccess.h"
    #endif /* (FLEXIO_UART_IP_IS_USING == STD_ON) */
#endif /* #ifdef FLEXIO_UART_IP_IS_USING */
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLEXIO_UART_IP_HWACCESS_VENDOR_ID                    43
#define FLEXIO_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION     4
#define FLEXIO_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION     7
#define FLEXIO_UART_IP_HWACCESS_AR_RELEASE_REVISION_VERSION  0
#define FLEXIO_UART_IP_HWACCESS_SW_MAJOR_VERSION             5
#define FLEXIO_UART_IP_HWACCESS_SW_MINOR_VERSION             0
#define FLEXIO_UART_IP_HWACCESS_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Flexio_Uart_Ip_Types.h */
#if (FLEXIO_UART_IP_HWACCESS_VENDOR_ID != FLEXIO_UART_IP_TYPES_VENDOR_ID)
    #error "Flexio_Uart_Ip_HwAccess.h and Flexio_Uart_Ip_Types.h have different vendor ids"
#endif
#if ((FLEXIO_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION    != FLEXIO_UART_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION    != FLEXIO_UART_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (FLEXIO_UART_IP_HWACCESS_AR_RELEASE_REVISION_VERSION != FLEXIO_UART_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Flexio_Uart_Ip_HwAccess.h and Flexio_Uart_Ip_Types.h are different"
#endif
#if ((FLEXIO_UART_IP_HWACCESS_SW_MAJOR_VERSION != FLEXIO_UART_IP_TYPES_SW_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_HWACCESS_SW_MINOR_VERSION != FLEXIO_UART_IP_TYPES_SW_MINOR_VERSION) || \
     (FLEXIO_UART_IP_HWACCESS_SW_PATCH_VERSION != FLEXIO_UART_IP_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Flexio_Uart_Ip_HwAccess.h and Flexio_Uart_Ip_Types.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and Std_Types.h header file are of the same Autosar version */
    #if ((FLEXIO_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (FLEXIO_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION) \
        )
        #error "Flexio_Uart_Ip_HwAccess.h and Std_Types.h are different"
    #endif
    /* Check if current file and OsIf.h header file are of the same Autosar version */
    #if ((FLEXIO_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION != OSIF_AR_RELEASE_MAJOR_VERSION) || \
         (FLEXIO_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION != OSIF_AR_RELEASE_MINOR_VERSION) \
        )
        #error "Flexio_Uart_Ip_HwAccess.h and OsIf.h are different"
    #endif
#ifdef FLEXIO_UART_IP_IS_USING
    #if (FLEXIO_UART_IP_IS_USING == STD_ON)
        /* Checks against Flexio_Mcl_Ip_HwAccess.h */
        #if ((FLEXIO_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION    != FLEXIO_IP_HW_ACCESS_AR_RELEASE_MAJOR_VERSION) || \
             (FLEXIO_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION    != FLEXIO_IP_HW_ACCESS_AR_RELEASE_MINOR_VERSION) \
            )
            #error "AUTOSAR Version Numbers of Flexio_Uart_Ip_HwAccess.h and Flexio_Mcl_Ip_HwAccess.h are different"
        #endif
    #endif /* (FLEXIO_UART_IP_IS_USING == STD_ON) */
#endif /* #ifdef FLEXIO_UART_IP_IS_USING */
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#ifdef FLEXIO_UART_IP_IS_USING
#if (FLEXIO_UART_IP_IS_USING == STD_ON)
/**
* @brief          Mask used to verify the SHIFTBUF registers content.
*/

#define FLEXIO_UART_IP_SHIFTBUF_MASK_U32   ((uint32)0xFF000000UL)

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/

#define UART_START_SEC_CODE
#include "Uart_MemMap.h"

/*
 * This function sets the following configurations for the specified Shifter:
 * start bit, stop bit, input Source
 */
static inline void Flexio_Uart_Ip_SetShifterConfig(FLEXIO_Type * Base,
                                                   uint8 Shifter,
                                                   Flexio_Mcl_Ip_ShifterStartType Start,
                                                   Flexio_Mcl_Ip_ShifterStopType Stop,
                                                   Flexio_Mcl_Ip_ShifterSourceType Source
                                                  )
{
    Base->SHIFTCFG[Shifter] = FLEXIO_SHIFTCFG_SSTART(Start)
                             | FLEXIO_SHIFTCFG_SSTOP(Stop)
                             | FLEXIO_SHIFTCFG_INSRC(Source);
}

/*
 * This function configures the control settings for the specified Shifter: mode settings
 * and timer settings.
 */
static inline void Flexio_Uart_Ip_SetShifterControl(FLEXIO_Type * Base,
                                                    uint8 Shifter,
                                                    Flexio_Mcl_Ip_ShifterModeType Mode,
                                                    uint8 Timer,
                                                    Flexio_Mcl_Ip_TimerPolarityType TimerPolarity
                                                   )
{
    Base->SHIFTCTL[Shifter] = (Base->SHIFTCTL[Shifter] & ~(FLEXIO_SHIFTCTL_SMOD_MASK)) | FLEXIO_SHIFTCTL_SMOD(Mode);
    Base->SHIFTCTL[Shifter] = (Base->SHIFTCTL[Shifter] & ~(FLEXIO_SHIFTCTL_TIMPOL_MASK)) | FLEXIO_SHIFTCTL_TIMPOL(TimerPolarity);
    Base->SHIFTCTL[Shifter] = (Base->SHIFTCTL[Shifter] & ~(FLEXIO_SHIFTCTL_TIMSEL_MASK)) | FLEXIO_SHIFTCTL_TIMSEL(Timer);
}

/*
 * This function configures the control settings for the specified Shifter: pin settings.
 */
static inline void Flexio_Uart_Ip_SetPinShifterControl(FLEXIO_Type * Base,
                                                       uint8 Shifter,
                                                       uint8 Pin,
                                                       Flexio_Mcl_Ip_PinPolarityType PinPolarity,
                                                       Flexio_Mcl_Ip_PinConfigType PinConfig
                                                      )
{
    Base->SHIFTCTL[Shifter] = (Base->SHIFTCTL[Shifter] & ~(FLEXIO_SHIFTCTL_PINPOL_MASK)) | FLEXIO_SHIFTCTL_PINPOL(PinPolarity);
    Base->SHIFTCTL[Shifter] = (Base->SHIFTCTL[Shifter] & ~(FLEXIO_SHIFTCTL_PINSEL_MASK)) | FLEXIO_SHIFTCTL_PINSEL(Pin);
    Base->SHIFTCTL[Shifter] = (Base->SHIFTCTL[Shifter] & ~(FLEXIO_SHIFTCTL_PINCFG_MASK)) | FLEXIO_SHIFTCTL_PINCFG(PinConfig);
}

/*
 * This function configures the compare value for the specified timer.
 * The timer compare value is loaded into the timer counter when the timer is first enabled,
 * when the timer is reset and when the timer decrements down to zero.
 * In dual 8-bit counters baud/bit mode, the lower 8-bits configure the baud rate divider
 * and the upper 8-bits configure the number of bits in each word.
 * In dual 8-bit counters PWM mode, the lower 8-bits configure the high period of the output
 * and the upper 8-bits configure the low period.
 * In 16-bit counter mode, the compare value can be used to generate the baud rate divider
 * (if shift clock source is timer output) or the number of bits in each word (when the shift
 * clock source is a pin or trigger input).
 */
static inline void Flexio_Uart_Ip_SetTimerCompare(FLEXIO_Type * Base, uint8 Timer, uint16 Value)
{
    Base->TIMCMP[Timer] = (uint32)Value;
}

/*
 * This function sets the following configurations for the specified timer:
 * Reset condition, Decrement condition, initial output
 */
static inline void Flexio_Uart_Ip_SetTimerConfig(FLEXIO_Type * Base,
                                                 uint8 Timer,
                                                 Flexio_Mcl_Ip_TimerResetType Reset,
                                                 Flexio_Uart_Ip_TimerDecrementType Decrement,
                                                 Flexio_Mcl_Ip_TimerOutputType Output
                                                )
{
    Base->TIMCFG[Timer] = (Base->TIMCFG[Timer] & ~(FLEXIO_TIMCFG_TIMRST_MASK)) | FLEXIO_TIMCFG_TIMRST(Reset);
    Base->TIMCFG[Timer] = (Base->TIMCFG[Timer] & ~(FLEXIO_TIMCFG_TIMDEC_MASK)) | FLEXIO_TIMCFG_TIMDEC(Decrement);
    Base->TIMCFG[Timer] = (Base->TIMCFG[Timer] & ~(FLEXIO_TIMCFG_TIMOUT_MASK)) | FLEXIO_TIMCFG_TIMOUT(Output);
}

/*
 * This function sets the following configurations for the specified timer:
 * Start bit, Stop bit
 */
static inline void Flexio_Uart_Ip_SetTimerStartStopBitConfig(FLEXIO_Type * Base,
                                                             uint8 Timer,
                                                             Flexio_Mcl_Ip_TimerStartType Start,
                                                             Flexio_Mcl_Ip_TimerStopType Stop
                                                            )
{
    Base->TIMCFG[Timer] = (Base->TIMCFG[Timer] & ~(FLEXIO_TIMCFG_TSTART_MASK)) | FLEXIO_TIMCFG_TSTART(Start);
    Base->TIMCFG[Timer] = (Base->TIMCFG[Timer] & ~(FLEXIO_TIMCFG_TSTOP_MASK)) | FLEXIO_TIMCFG_TSTOP(Stop);
}

/*
 * This function sets the following configurations for the specified timer:
 * Enable condition, disable condition,
 */
static inline void Flexio_Uart_Ip_SetTimerCondition(FLEXIO_Type * Base,
                                                    uint8 Timer,
                                                    Flexio_Mcl_Ip_TimerEnableType Enable,
                                                    Flexio_Mcl_Ip_TimerDisableType Disable
                                                   )
{
    Base->TIMCFG[Timer] = (Base->TIMCFG[Timer] & ~(FLEXIO_TIMCFG_TIMENA_MASK)) | FLEXIO_TIMCFG_TIMENA(Enable);
    Base->TIMCFG[Timer] = (Base->TIMCFG[Timer] & ~(FLEXIO_TIMCFG_TIMDIS_MASK)) | FLEXIO_TIMCFG_TIMDIS(Disable);
}

/*
 * This function configures the control settings for the specified timer: mode settings.
 */
static inline void Flexio_Uart_Ip_SetTimerControl(FLEXIO_Type * Base, uint8 Timer, Flexio_Mcl_Ip_TimerModeType Mode)
{
    Base->TIMCTL[Timer] = (Base->TIMCTL[Timer] & ~(FLEXIO_TIMCTL_TIMOD_MASK)) | FLEXIO_TIMCTL_TIMOD(Mode);
}

/*
 * This function configures the control settings for the specified timer: trigger settings.
 */
static inline void Flexio_Uart_Ip_SetTimerTrigger(FLEXIO_Type * Base,
                                                  uint8 Timer,
                                                  uint8 Trigger,
                                                  Flexio_Mcl_Ip_TriggerPolarityType TriggerPolarity,
                                                  Flexio_Mcl_Ip_TriggerSourceType TriggerSource
                                                 )
{
    Base->TIMCTL[Timer] = (Base->TIMCTL[Timer] & ~(FLEXIO_TIMCTL_TRGSRC_MASK)) | FLEXIO_TIMCTL_TRGSRC(TriggerSource);
    Base->TIMCTL[Timer] = (Base->TIMCTL[Timer] & ~(FLEXIO_TIMCTL_TRGPOL_MASK)) | FLEXIO_TIMCTL_TRGPOL(TriggerPolarity);
    Base->TIMCTL[Timer] = (Base->TIMCTL[Timer] & ~(FLEXIO_TIMCTL_TRGSEL_MASK)) | FLEXIO_TIMCTL_TRGSEL(Trigger);
}

/*
 * This function configures the control settings for the specified timer:
 * pin settings.
 */
static inline void Flexio_Uart_Ip_SetPinTimerControl(FLEXIO_Type * Base,
                                                     uint8 Timer,
                                                     uint8 Pin,
                                                     Flexio_Mcl_Ip_PinPolarityType PinPolarity,
                                                     Flexio_Mcl_Ip_PinConfigType PinConfig
                                                    )
{
    Base->TIMCTL[Timer] = (Base->TIMCTL[Timer] & ~(FLEXIO_TIMCTL_PINSEL_MASK)) | FLEXIO_TIMCTL_PINSEL(Pin);
    Base->TIMCTL[Timer] = (Base->TIMCTL[Timer] & ~(FLEXIO_TIMCTL_PINPOL_MASK)) | FLEXIO_TIMCTL_PINPOL(PinPolarity);
    Base->TIMCTL[Timer] = (Base->TIMCTL[Timer] & ~(FLEXIO_TIMCTL_PINCFG_MASK)) | FLEXIO_TIMCTL_PINCFG(PinConfig);
}

/*
 * This function configures the mode for the specified timer.
 * In 8-bit counter mode, the lower 8-bits of the counter and compare register are used to
 * configure the baud rate of the timer shift clock and the upper 8-bits are used to configure
 * the shifter bit count.
 * In 8-bit PWM mode, the lower 8-bits of the counter and compare
 * register are used to configure the high period of the timer shift clock and the upper
 * 8-bits are used to configure the low period of the timer shift clock. The shifter bit count
 * is configured using another timer or external signal.
 * In 16-bit counter mode, the full 16-bits of the counter and compare register are used to
 * configure either the baud rate of the shift clock or the shifter bit count.
 */
static inline void Flexio_Uart_Ip_SetTimerMode(FLEXIO_Type * Base, uint8 Timer, Flexio_Mcl_Ip_TimerModeType Mode)
{
    Base->TIMCTL[Timer] = (Base->TIMCTL[Timer] & ~(FLEXIO_TIMCTL_TIMOD_MASK)) | FLEXIO_TIMCTL_TIMOD(Mode);
}

/*
 * This function configures the mode for the specified shifter.
 */
static inline void Flexio_Uart_Ip_SetShifterMode(FLEXIO_Type * Base, uint8 Shifter, Flexio_Mcl_Ip_ShifterModeType Mode)
{
    Base->SHIFTCTL[Shifter] = (Base->SHIFTCTL[Shifter] & ~(FLEXIO_SHIFTCTL_SMOD_MASK)) | FLEXIO_SHIFTCTL_SMOD(Mode);
}

/*
 * This function configures the sending or receiving of
 * a start bit in Transmit, Receive or Match Store modes.
 */
static inline void Flexio_Uart_Ip_SetShifterStartBit(FLEXIO_Type * Base, uint8 Shifter, Flexio_Mcl_Ip_ShifterStartType Start)
{
    Base->SHIFTCFG[Shifter] = (Base->SHIFTCFG[Shifter] & ~(FLEXIO_SHIFTCFG_SSTART_MASK)) | FLEXIO_SHIFTCFG_SSTART(Start);
}

/*
 * This function writes data in the specified shifter buffer.
 */
static inline void Flexio_Uart_Ip_WriteShifterBuffer(FLEXIO_Type * Base, uint8 Shifter, uint32 Value)
{
    Base->SHIFTBUF[Shifter] = Value;
}

/*
 * This function reads data from the specified shifter buffer.
 */
static inline uint32 Flexio_Uart_Ip_ReadShifterBuffer(const FLEXIO_Type * Base, uint8 Shifter)
{
    uint32 Data;

    Data = Base->SHIFTBUF[Shifter] & FLEXIO_UART_IP_SHIFTBUF_MASK_U32;
    return Data;
}

/*
 * Returns the state of the interrupt for corresponding timer.
 */
static inline boolean Flexio_Uart_Ip_GetTimerInterrupt(const FLEXIO_Type * Base, uint8 Timer)
{
    boolean RetStatus;
    uint32 RegValue = (uint32)Base->TIMIEN;

    RegValue = (RegValue >> Timer) & 1U;
    if (RegValue != 0U)
    {
        RetStatus = TRUE;
    }
    else
    {
        RetStatus = FALSE;
    }
    return RetStatus;
}

/*
 * Returns the state of the error interrupt for corresponding shifter.
 */
static inline boolean Flexio_Uart_Ip_GetShifterErrorInterrupt(const FLEXIO_Type * Base, uint8 Shifter)
{
    boolean RetStatus;
    uint32 RegValue = (uint32)Base->SHIFTEIEN;

    RegValue = (RegValue >> Shifter) & 1U;
    if (RegValue != 0U)
    {
        RetStatus = TRUE;
    }
    else
    {
        RetStatus = FALSE;
    }
    return RetStatus;
}

/*
 * Returns the state of the interrupt for corresponding shifter.
 */
static inline boolean Flexio_Uart_Ip_GetShifterInterrupt(const FLEXIO_Type * Base, uint8 Shifter)
{
    boolean RetStatus;
    uint32 RegValue = (uint32)Base->SHIFTSIEN;

    RegValue = (RegValue >> Shifter) & 1U;
    if (RegValue != 0U)
    {
        RetStatus = TRUE;
    }
    else
    {
        RetStatus = FALSE;
    }
    return RetStatus;
}

/**
 * @brief   : Prepare for timeout checking
 * @internal
 * @return  : None
 */
static inline void Flexio_Uart_Ip_StartTimeout(uint32 *StartTimeOut, uint32 *TimeoutTicksOut, uint32 TimeoutUs, OsIf_CounterType OsifCounter)
{
    *StartTimeOut    = OsIf_GetCounter(OsifCounter);
    *TimeoutTicksOut = OsIf_MicrosToTicks(TimeoutUs, OsifCounter);
}

/**
 * @brief   : Checks for timeout condition
 * @internal
 * @return  TRUE     Timeout occurs
 *          FALSE    Timeout does not occur
 */
static inline boolean Flexio_Uart_Ip_CheckTimeout(uint32 * StartTime, uint32 * ElapsedTicks, uint32 TimeoutTicks, OsIf_CounterType OsifCounter)
{
    boolean RetVal = FALSE;
    uint32 CurrentElapsedTicks = OsIf_GetElapsed(StartTime, OsifCounter);

    *ElapsedTicks += CurrentElapsedTicks;
    if (*ElapsedTicks >= TimeoutTicks)
    {
        RetVal = TRUE;
    }

    return RetVal;
}

#define UART_STOP_SEC_CODE
#include "Uart_MemMap.h"

#endif /* (FLEXIO_UART_IP_IS_USING == STD_ON) */
#endif /* #ifdef FLEXIO_UART_IP_IS_USING */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* FLEXIO_UART_IP_HWACCESS_H */
