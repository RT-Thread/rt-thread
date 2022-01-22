/**************************************************************************//**
 * @file     nu_bpwm.h
 * @version  V1.00
 * @brief    M2354 series BPWM driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_BPWM_H__
#define __NU_BPWM_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup BPWM_Driver BPWM Driver
  @{
*/

/** @addtogroup BPWM_EXPORTED_CONSTANTS BPWM Exported Constants
  @{
*/
#define BPWM_CHANNEL_NUM                          (6UL)      /*!< BPWM channel number */
#define BPWM_CH_0_MASK                            (0x1UL)    /*!< BPWM channel 0 mask \hideinitializer */
#define BPWM_CH_1_MASK                            (0x2UL)    /*!< BPWM channel 1 mask \hideinitializer */
#define BPWM_CH_2_MASK                            (0x4UL)    /*!< BPWM channel 2 mask \hideinitializer */
#define BPWM_CH_3_MASK                            (0x8UL)    /*!< BPWM channel 3 mask \hideinitializer */
#define BPWM_CH_4_MASK                            (0x10UL)   /*!< BPWM channel 4 mask \hideinitializer */
#define BPWM_CH_5_MASK                            (0x20UL)   /*!< BPWM channel 5 mask \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Counter Type Constant Definitions                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define BPWM_UP_COUNTER                           (0UL)      /*!< Up counter type */
#define BPWM_DOWN_COUNTER                         (1UL)      /*!< Down counter type */
#define BPWM_UP_DOWN_COUNTER                      (2UL)      /*!< Up-Down counter type */

/*---------------------------------------------------------------------------------------------------------*/
/*  Aligned Type Constant Definitions                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define BPWM_EDGE_ALIGNED                         (1UL)      /*!< BPWM working in edge aligned type(down count) */
#define BPWM_CENTER_ALIGNED                       (2UL)      /*!< BPWM working in center aligned type */

/*---------------------------------------------------------------------------------------------------------*/
/*  Output Level Constant Definitions                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define BPWM_OUTPUT_NOTHING                       (0UL)      /*!< BPWM output nothing */
#define BPWM_OUTPUT_LOW                           (1UL)      /*!< BPWM output low */
#define BPWM_OUTPUT_HIGH                          (2UL)      /*!< BPWM output high */
#define BPWM_OUTPUT_TOGGLE                        (3UL)      /*!< BPWM output toggle */

/*---------------------------------------------------------------------------------------------------------*/
/*  Synchronous Start Function Control Constant Definitions                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define BPWM_SSCTL_SSRC_PWM0                      (0UL<<BPWM_SSCTL_SSRC_Pos)    /*!< Synchronous start source comes from PWM0  */
#define BPWM_SSCTL_SSRC_PWM1                      (1UL<<BPWM_SSCTL_SSRC_Pos)    /*!< Synchronous start source comes from PWM1  */
#define BPWM_SSCTL_SSRC_BPWM0                     (2UL<<BPWM_SSCTL_SSRC_Pos)    /*!< Synchronous start source comes from BPWM0 */
#define BPWM_SSCTL_SSRC_BPWM1                     (3UL<<BPWM_SSCTL_SSRC_Pos)    /*!< Synchronous start source comes from BPWM1 */

/*---------------------------------------------------------------------------------------------------------*/
/*  Trigger Source Select Constant Definitions                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define BPWM_TRIGGER_ADC_EVEN_ZERO_POINT                     (0UL)     /*!< BPWM trigger ADC while counter of even channel matches zero point \hideinitializer */
#define BPWM_TRIGGER_ADC_EVEN_PERIOD_POINT                   (1UL)     /*!< BPWM trigger ADC while counter of even channel matches period point \hideinitializer */
#define BPWM_TRIGGER_ADC_EVEN_ZERO_OR_PERIOD_POINT           (2UL)     /*!< BPWM trigger ADC while counter of even channel matches zero or period point \hideinitializer */
#define BPWM_TRIGGER_ADC_EVEN_CMP_UP_COUNT_POINT             (3UL)     /*!< BPWM trigger ADC while counter of even channel matches up count to comparator point \hideinitializer */
#define BPWM_TRIGGER_ADC_EVEN_CMP_DOWN_COUNT_POINT           (4UL)     /*!< BPWM trigger ADC while counter of even channel matches down count to comparator point \hideinitializer */
#define BPWM_TRIGGER_ADC_ODD_CMP_UP_COUNT_POINT              (8UL)     /*!< BPWM trigger ADC while counter of odd channel matches up count to comparator point \hideinitializer */
#define BPWM_TRIGGER_ADC_ODD_CMP_DOWN_COUNT_POINT            (9UL)     /*!< BPWM trigger ADC while counter of odd channel matches down count to comparator point \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Capture Control Constant Definitions                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define BPWM_CAPTURE_INT_RISING_LATCH             (1UL)        /*!< BPWM capture interrupt if channel has rising transition */
#define BPWM_CAPTURE_INT_FALLING_LATCH            (0x100UL)    /*!< BPWM capture interrupt if channel has falling transition */

/*---------------------------------------------------------------------------------------------------------*/
/*  Duty Interrupt Type Constant Definitions                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define BPWM_DUTY_INT_DOWN_COUNT_MATCH_CMP        (1 << BPWM_INTEN_CMPDIEN0_Pos)   /*!< BPWM duty interrupt triggered if down count match comparator \hideinitializer */
#define BPWM_DUTY_INT_UP_COUNT_MATCH_CMP          (1 << BPWM_INTEN_CMPUIEN0_Pos)   /*!< BPWM duty interrupt triggered if up down match comparator \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Load Mode Constant Definitions                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define BPWM_LOAD_MODE_IMMEDIATE                  (1 << BPWM_CTL0_IMMLDEN0_Pos)    /*!< BPWM immediately load mode \hideinitializer */
#define BPWM_LOAD_MODE_CENTER                     (1 << BPWM_CTL0_CTRLD0_Pos)      /*!< BPWM center load mode \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Clock Source Select Constant Definitions                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define BPWM_CLKSRC_BPWM_CLK                      (0UL)    /*!< BPWM Clock source selects to BPWM0_CLK or BPWM1_CLK \hideinitializer */
#define BPWM_CLKSRC_TIMER0                        (1UL)    /*!< BPWM Clock source selects to TIMER0 overflow \hideinitializer */
#define BPWM_CLKSRC_TIMER1                        (2UL)    /*!< BPWM Clock source selects to TIMER1 overflow \hideinitializer */
#define BPWM_CLKSRC_TIMER2                        (3UL)    /*!< BPWM Clock source selects to TIMER2 overflow \hideinitializer */
#define BPWM_CLKSRC_TIMER3                        (4UL)    /*!< BPWM Clock source selects to TIMER3 overflow \hideinitializer */

/**@}*/ /* end of group BPWM_EXPORTED_CONSTANTS */


/** @addtogroup BPWM_EXPORTED_FUNCTIONS BPWM Exported Functions
  @{
*/

/**
 * @brief Enable timer synchronous start counting function of specified channel(s)
 * @param[in] bpwm The pointer of the specified BPWM module
 * @param[in] u32ChannelMask Combination of enabled channels. This parameter is not used.
 * @param[in] u32SyncSrc Synchronous start source selection, valid values are:
 *              - \ref BPWM_SSCTL_SSRC_PWM0
 *              - \ref BPWM_SSCTL_SSRC_PWM1
 *              - \ref BPWM_SSCTL_SSRC_BPWM0
 *              - \ref BPWM_SSCTL_SSRC_BPWM1
 * @return None
 * @details This macro is used to enable timer synchronous start counting function of specified channel(s).
 * @note All channels share channel 0's setting.
 * \hideinitializer
 */
#define BPWM_ENABLE_TIMER_SYNC(bpwm, u32ChannelMask, u32SyncSrc) ((bpwm)->SSCTL = ((bpwm)->SSCTL & ~BPWM_SSCTL_SSRC_Msk) | (u32SyncSrc) | BPWM_SSCTL_SSEN0_Msk)

/**
 * @brief Disable timer synchronous start counting function of specified channel(s)
 * @param[in] bpwm The pointer of the specified BPWM module
 * @param[in] u32ChannelMask Combination of enabled channels. This parameter is not used.
 * @return None
 * @details This macro is used to disable timer synchronous start counting function of specified channel(s).
 * @note All channels share channel 0's setting.
 * \hideinitializer
 */
#define BPWM_DISABLE_TIMER_SYNC(bpwm, u32ChannelMask) ((bpwm)->SSCTL &= ~BPWM_SSCTL_SSEN0_Msk)

/**
 * @brief This macro enable BPWM counter synchronous start counting function.
 * @param[in] bpwm The pointer of the specified BPWM module
 * @return None
 * @details This macro is used to make selected BPWM0 and BPWM1 channel(s) start counting at the same time.
 *          To configure synchronous start counting channel(s) by BPWM_ENABLE_TIMER_SYNC() and BPWM_DISABLE_TIMER_SYNC().
 * \hideinitializer
 */
#define BPWM_TRIGGER_SYNC_START(bpwm) ((bpwm)->SSTRG = BPWM_SSTRG_CNTSEN_Msk)

/**
 * @brief This macro enable output inverter of specified channel(s)
 * @param[in] bpwm The pointer of the specified BPWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @return None
 * \hideinitializer
 */
#define BPWM_ENABLE_OUTPUT_INVERTER(bpwm, u32ChannelMask) ((bpwm)->POLCTL = (u32ChannelMask))

/**
 * @brief This macro get captured rising data
 * @param[in] bpwm The pointer of the specified BPWM module
 * @param[in] u32ChannelNum BPWM channel number. Valid values are between 0~5
 * @return None
 * \hideinitializer
 */
#define BPWM_GET_CAPTURE_RISING_DATA(bpwm, u32ChannelNum) ((bpwm)->CAPDAT[(u32ChannelNum)].RCAPDAT)

/**
 * @brief This macro get captured falling data
 * @param[in] bpwm The pointer of the specified BPWM module
 * @param[in] u32ChannelNum BPWM channel number. Valid values are between 0~5
 * @return None
 * \hideinitializer
 */
#define BPWM_GET_CAPTURE_FALLING_DATA(bpwm, u32ChannelNum) ((bpwm)->CAPDAT[(u32ChannelNum)].FCAPDAT)

/**
 * @brief This macro mask output logic to high or low
 * @param[in] bpwm The pointer of the specified BPWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @param[in] u32LevelMask Output logic to high or low
 * @return None
 * @details This macro is used to mask output logic to high or low of specified channel(s).
 * @note If u32ChannelMask parameter is 0, then mask function will be disabled.
 * \hideinitializer
 */
#define BPWM_MASK_OUTPUT(bpwm, u32ChannelMask, u32LevelMask) \
    { \
        (bpwm)->MSKEN = (u32ChannelMask); \
        (bpwm)->MSK = (u32LevelMask); \
    }

/**
 * @brief This macro set the prescaler of all channels
 * @param[in] bpwm The pointer of the specified BPWM module
 * @param[in] u32ChannelNum BPWM channel number. This parameter is not used.
 * @param[in] u32Prescaler Clock prescaler of specified channel. Valid values are between 1 ~ 0xFFF
 * @return None
 * \hideinitializer
 */
#define BPWM_SET_PRESCALER(bpwm, u32ChannelNum, u32Prescaler) ((bpwm)->CLKPSC = (u32Prescaler))

/**
 * @brief This macro set the duty of the selected channel
 * @param[in] bpwm The pointer of the specified BPWM module
 * @param[in] u32ChannelNum BPWM channel number. Valid values are between 0~5
 * @param[in] u32CMR Duty of specified channel. Valid values are between 0~0xFFFF
 * @return None
 * @note This new setting will take effect on next BPWM period
 * \hideinitializer
 */
#define BPWM_SET_CMR(bpwm, u32ChannelNum, u32CMR) ((bpwm)->CMPDAT[(u32ChannelNum)] = (u32CMR))

/**
 * @brief This macro get the duty of the selected channel
 * @param[in] bpwm The pointer of the specified BPWM module
 * @param[in] u32ChannelNum BPWM channel number. Valid values are between 0~5
 * @return Return the comparator of specified channel. Valid values are between 0~0xFFFF
 * @details This macro is used to get the comparator of specified channel.
 * \hideinitializer
 */
#define BPWM_GET_CMR(bpwm, u32ChannelNum) ((bpwm)->CMPDAT[(u32ChannelNum)])

/**
 * @brief This macro set the period of all channels
 * @param[in] bpwm The pointer of the specified BPWM module
 * @param[in] u32ChannelNum BPWM channel number. This parameter is not used.
 * @param[in] u32CNR Period of specified channel. Valid values are between 0~0xFFFF
 * @return None
 * @note This new setting will take effect on next BPWM period
 * @note BPWM counter will stop if period length set to 0
 * \hideinitializer
 */
#define BPWM_SET_CNR(bpwm, u32ChannelNum, u32CNR) ((bpwm)->PERIOD = (u32CNR))

/**
 * @brief This macro get the period of all channels
 * @param[in] bpwm The pointer of the specified BPWM module
 * @param[in] u32ChannelNum BPWM channel number. This parameter is not used.
 * @return None
 * \hideinitializer
 */
#define BPWM_GET_CNR(bpwm, u32ChannelNum) ((bpwm)->PERIOD)

/**
 * @brief This macro set the BPWM aligned type
 * @param[in] bpwm The pointer of the specified BPWM module
 * @param[in] u32ChannelMask Combination of enabled channels. This parameter is not used.
 * @param[in] u32AlignedType BPWM aligned type, valid values are:
 *              - \ref BPWM_EDGE_ALIGNED
 *              - \ref BPWM_CENTER_ALIGNED
 * @return None
 * @note All channels share channel 0's setting.
 * \hideinitializer
 */
#define BPWM_SET_ALIGNED_TYPE(bpwm, u32ChannelMask, u32AlignedType) ((bpwm)->CTL1 = (u32AlignedType))

/**
 * @brief Clear counter of channel 0
 * @param[in] bpwm The pointer of the specified BPWM module
 * @param[in] u32ChannelMask Combination of enabled channels. This parameter is not used.
 * @return None
 * @details This macro is used to clear counter of channel 0
 * \hideinitializer
 */
#define BPWM_CLR_COUNTER(bpwm, u32ChannelMask) ((bpwm)->CNTCLR = (BPWM_CNTCLR_CNTCLR0_Msk))

/**
 * @brief Set output level at zero, compare up, period(center) and compare down of specified channel(s)
 * @param[in] bpwm The pointer of the specified BPWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @param[in] u32ZeroLevel output level at zero point, valid values are:
 *              - \ref BPWM_OUTPUT_NOTHING
 *              - \ref BPWM_OUTPUT_LOW
 *              - \ref BPWM_OUTPUT_HIGH
 *              - \ref BPWM_OUTPUT_TOGGLE
 * @param[in] u32CmpUpLevel output level at compare up point, valid values are:
 *              - \ref BPWM_OUTPUT_NOTHING
 *              - \ref BPWM_OUTPUT_LOW
 *              - \ref BPWM_OUTPUT_HIGH
 *              - \ref BPWM_OUTPUT_TOGGLE
 * @param[in] u32PeriodLevel output level at period(center) point, valid values are:
 *              - \ref BPWM_OUTPUT_NOTHING
 *              - \ref BPWM_OUTPUT_LOW
 *              - \ref BPWM_OUTPUT_HIGH
 *              - \ref BPWM_OUTPUT_TOGGLE
 * @param[in] u32CmpDownLevel output level at compare down point, valid values are:
 *              - \ref BPWM_OUTPUT_NOTHING
 *              - \ref BPWM_OUTPUT_LOW
 *              - \ref BPWM_OUTPUT_HIGH
 *              - \ref BPWM_OUTPUT_TOGGLE
 * @return None
 * @details This macro is used to Set output level at zero, compare up, period(center) and compare down of specified channel(s)
 * \hideinitializer
 */
#define BPWM_SET_OUTPUT_LEVEL(bpwm, u32ChannelMask, u32ZeroLevel, u32CmpUpLevel, u32PeriodLevel, u32CmpDownLevel) \
   do{ \
        uint32_t i; \
        for(i = 0UL; i < 6UL; i++) { \
            if((u32ChannelMask) & (1UL << i)) { \
                (bpwm)->WGCTL0 = (((bpwm)->WGCTL0 & ~(3UL << (i << 1))) | ((u32ZeroLevel) << (i << 1))); \
                (bpwm)->WGCTL0 = (((bpwm)->WGCTL0 & ~(3UL << (BPWM_WGCTL0_PRDPCTL0_Pos + (i << 1)))) | ((u32PeriodLevel) << (BPWM_WGCTL0_PRDPCTL0_Pos + (i << 1)))); \
                (bpwm)->WGCTL1 = (((bpwm)->WGCTL1 & ~(3UL << (i << 1))) | ((u32CmpUpLevel) << (i << 1))); \
                (bpwm)->WGCTL1 = (((bpwm)->WGCTL1 & ~(3UL << (BPWM_WGCTL1_CMPDCTL0_Pos + (i << 1)))) | ((u32CmpDownLevel) << (BPWM_WGCTL1_CMPDCTL0_Pos + (i << 1)))); \
            } \
        } \
    }while(0)


/*---------------------------------------------------------------------------------------------------------*/
/* Define BPWM functions prototype                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
uint32_t BPWM_ConfigCaptureChannel(BPWM_T *bpwm, uint32_t u32ChannelNum, uint32_t u32UnitTimeNsec, uint32_t u32CaptureEdge);
uint32_t BPWM_ConfigOutputChannel(BPWM_T *bpwm, uint32_t u32ChannelNum, uint32_t u32Frequency, uint32_t u32DutyCycle);
void BPWM_Start(BPWM_T *bpwm, uint32_t u32ChannelMask);
void BPWM_Stop(BPWM_T *bpwm, uint32_t u32ChannelMask);
void BPWM_ForceStop(BPWM_T *bpwm, uint32_t u32ChannelMask);
void BPWM_EnableADCTrigger(BPWM_T *bpwm, uint32_t u32ChannelNum, uint32_t u32Condition);
void BPWM_DisableADCTrigger(BPWM_T *bpwm, uint32_t u32ChannelNum);
void BPWM_ClearADCTriggerFlag(BPWM_T *bpwm, uint32_t u32ChannelNum, uint32_t u32Condition);
uint32_t BPWM_GetADCTriggerFlag(BPWM_T *bpwm, uint32_t u32ChannelNum);
void BPWM_EnableCapture(BPWM_T *bpwm, uint32_t u32ChannelMask);
void BPWM_DisableCapture(BPWM_T *bpwm, uint32_t u32ChannelMask);
void BPWM_EnableOutput(BPWM_T *bpwm, uint32_t u32ChannelMask);
void BPWM_DisableOutput(BPWM_T *bpwm, uint32_t u32ChannelMask);
void BPWM_EnableCaptureInt(BPWM_T *bpwm, uint32_t u32ChannelNum, uint32_t u32Edge);
void BPWM_DisableCaptureInt(BPWM_T *bpwm, uint32_t u32ChannelNum, uint32_t u32Edge);
void BPWM_ClearCaptureIntFlag(BPWM_T *bpwm, uint32_t u32ChannelNum, uint32_t u32Edge);
uint32_t BPWM_GetCaptureIntFlag(BPWM_T *bpwm, uint32_t u32ChannelNum);
void BPWM_EnableDutyInt(BPWM_T *bpwm, uint32_t u32ChannelNum, uint32_t u32IntDutyType);
void BPWM_DisableDutyInt(BPWM_T *bpwm, uint32_t u32ChannelNum);
void BPWM_ClearDutyIntFlag(BPWM_T *bpwm, uint32_t u32ChannelNum);
uint32_t BPWM_GetDutyIntFlag(BPWM_T *bpwm, uint32_t u32ChannelNum);
void BPWM_EnablePeriodInt(BPWM_T *bpwm, uint32_t u32ChannelNum,  uint32_t u32IntPeriodType);
void BPWM_DisablePeriodInt(BPWM_T *bpwm, uint32_t u32ChannelNum);
void BPWM_ClearPeriodIntFlag(BPWM_T *bpwm, uint32_t u32ChannelNum);
uint32_t BPWM_GetPeriodIntFlag(BPWM_T *bpwm, uint32_t u32ChannelNum);
void BPWM_EnableZeroInt(BPWM_T *bpwm, uint32_t u32ChannelNum);
void BPWM_DisableZeroInt(BPWM_T *bpwm, uint32_t u32ChannelNum);
void BPWM_ClearZeroIntFlag(BPWM_T *bpwm, uint32_t u32ChannelNum);
uint32_t BPWM_GetZeroIntFlag(BPWM_T *bpwm, uint32_t u32ChannelNum);
void BPWM_EnableLoadMode(BPWM_T *bpwm, uint32_t u32ChannelNum, uint32_t u32LoadMode);
void BPWM_DisableLoadMode(BPWM_T *bpwm, uint32_t u32ChannelNum, uint32_t u32LoadMode);
void BPWM_SetClockSource(BPWM_T *bpwm, uint32_t u32ChannelNum, uint32_t u32ClkSrcSel);
uint32_t BPWM_GetWrapAroundFlag(BPWM_T *bpwm, uint32_t u32ChannelNum);
void BPWM_ClearWrapAroundFlag(BPWM_T *bpwm, uint32_t u32ChannelNum);

/**@}*/ /* end of group BPWM_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group BPWM_Driver */

/**@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_BPWM_H__ */

