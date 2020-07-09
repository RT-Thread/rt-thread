/**************************************************************************//**
 * @file     pwm.h
 * @version  V1.00
 * $Revision: 22 $
 * $Date: 15/11/16 2:08p $
 * @brief    NUC472/NUC442 PWM driver header file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __PWM_H__
#define __PWM_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_PWM_Driver PWM Driver
  @{
*/

/** @addtogroup NUC472_442_PWM_EXPORTED_CONSTANTS PWM Exported Constants
  @{
*/
#define PWM_CHANNEL_NUM                     (6)      /*!< PWM channel number \hideinitializer */
#define PWM_CH0                             (0UL)    /*!< PWM channel 0  \hideinitializer */
#define PWM_CH1                             (1UL)    /*!< PWM channel 1  \hideinitializer */
#define PWM_CH2                             (2UL)    /*!< PWM channel 2  \hideinitializer */
#define PWM_CH3                             (3UL)    /*!< PWM channel 3  \hideinitializer */
#define PWM_CH4                             (4UL)    /*!< PWM channel 4  \hideinitializer */
#define PWM_CH5                             (5UL)    /*!< PWM channel 5  \hideinitializer */
#define PWM_CH_0_MASK                       (1UL)    /*!< PWM channel 0 mask \hideinitializer */
#define PWM_CH_1_MASK                       (2UL)    /*!< PWM channel 1 mask \hideinitializer */
#define PWM_CH_2_MASK                       (4UL)    /*!< PWM channel 2 mask \hideinitializer */
#define PWM_CH_3_MASK                       (8UL)    /*!< PWM channel 3 mask \hideinitializer */
#define PWM_CH_4_MASK                       (16UL)   /*!< PWM channel 4 mask \hideinitializer */
#define PWM_CH_5_MASK                       (32UL)   /*!< PWM channel 5 mask \hideinitializer */
#define PWM_CLK_DIV_1                       (4UL)    /*!< PWM clock divide by 1 \hideinitializer */
#define PWM_CLK_DIV_2                       (0UL)    /*!< PWM clock divide by 2 \hideinitializer */
#define PWM_CLK_DIV_4                       (1UL)    /*!< PWM clock divide by 4 \hideinitializer */
#define PWM_CLK_DIV_8                       (2UL)    /*!< PWM clock divide by 8 \hideinitializer */
#define PWM_CLK_DIV_16                      (3UL)    /*!< PWM clock divide by 16 \hideinitializer */
#define PWM_EDGE_ALIGNED                    (0UL)    /*!< PWM working in edge aligned type \hideinitializer */
#define PWM_CENTER_ALIGNED                  (1UL)    /*!< PWM working in center aligned type \hideinitializer */
#define PWM_TRIGGER_ADC_RISING_EDGE_POINT   (0x1000000UL)     /*!< PWM trigger ADC while output rising edge is detected \hideinitializer */
#define PWM_TRIGGER_ADC_FALLING_EDGE_POINT  (0x10000UL)       /*!< PWM trigger ADC while output falling edge is detected \hideinitializer */
#define PWM_TRIGGER_ADC_CENTER_POINT        (0x100UL)         /*!< PWM trigger ADC while counter matches (CNR + 1) \hideinitializer */
#define PWM_TRIGGER_ADC_PERIOD_POINT        (0x1UL)           /*!< PWM trigger ADC while counter down count to 0  \hideinitializer */
#define PWM_BRK0_BKP0                       (PWM_BRKCTL_BRK0EN_Msk)                          /*!< Brake0 signal source from external pin BKP0 \hideinitializer */
#define PWM_BRK0_CPO0                       (PWM_BRKCTL_CPO0BKEN_Msk)      /*!< Brake0 signal source from analog comparator 0 output \hideinitializer */
#define PWM_BRK0_CPO1                       (PWM_BRKCTL_CPO1BKEN_Msk)      /*!< Brake0 signal source from analog comparator 1 output \hideinitializer */
#define PWM_BRK0_CPO2                       (PWM_BRKCTL_CPO2BKEN_Msk)      /*!< Brake0 signal source from analog comparator 2 output \hideinitializer */
#define PWM_BRK1_LVDBK                      (PWM_BRKCTL_LVDBKEN_Msk)     /*!< Brake1 signal source from level detect \hideinitializer */
#define PWM_BK1SEL_BKP1                     (0UL << PWM_BRKCTL_BK1SEL_Pos) /*!< Brake1 signal source from external pin BKP1 \hideinitializer */
#define PWM_BK1SEL_CPO0                     (1UL << PWM_BRKCTL_BK1SEL_Pos) /*!< Brake1 signal source from analog comparator 0 output \hideinitializer */
#define PWM_BK1SEL_CPO1                     (2UL << PWM_BRKCTL_BK1SEL_Pos) /*!< Brake1 signal source from analog comparator 1 output \hideinitializer */
#define PWM_PERIOD_INT_UNDERFLOW            (0)               /*!< PWM period interrupt trigger if counter underflow \hideinitializer */
#define PWM_PERIOD_INT_MATCH_CNR            (1UL)             /*!< PWM period interrupt trigger if counter match CNR \hideinitializer */
#define PWM_DUTY_INT_MATCH_CMR_DN           (0)               /*!< PWM duty interrupt if counter match CNR during down counting \hideinitializer */
#define PWM_DUTY_INT_MATCH_CMR_UP           (0x100UL)         /*!< PWM duty interrupt if counter match CNR during up counting \hideinitializer */
#define PWM_FALLING_LATCH_INT_ENABLE        (0x1000000UL)     /*!< PWM falling latch interrupt enable \hideinitializer */
#define PWM_RISING_LATCH_INT_ENABLE         (0x10000UL)       /*!< PWM rising latch interrupt enable \hideinitializer */
#define PWM_RISING_FALLING_LATCH_INT_ENABLE (0x1010000UL)     /*!< PWM rising latch interrupt enable \hideinitializer */
#define PWM_FALLING_LATCH_INT_FLAG          (PWM_FALLING_LATCH_INT_ENABLE)         /*!< PWM falling latch condition happened \hideinitializer */
#define PWM_RISING_LATCH_INT_FLAG           (PWM_RISING_LATCH_INT_ENABLE)          /*!< PWM rising latch condition happened \hideinitializer */
#define PWM_RISING_FALLING_LATCH_INT_FLAG   (PWM_RISING_FALLING_LATCH_INT_ENABLE)  /*!< PWM rising latch condition happened \hideinitializer */

/*@}*/ /* end of group NUC472_442_PWM_EXPORTED_CONSTANTS */


/** @addtogroup NUC472_442_PWM_EXPORTED_FUNCTIONS PWM Exported Functions
  @{
*/

/**
 * @brief This macro enable complementary mode
 * @param[in] pwm The base address of PWM module
 * @return None
 * \hideinitializer
 */
#define PWM_ENABLE_COMPLEMENTARY_MODE(pwm) ((pwm)->CTL = (pwm)->CTL | PWM_CTL_OUTMODE_Msk)

/**
 * @brief This macro disable complementary mode, and enable independent mode.
 * @param[in] pwm The base address of PWM module
 * @return None
 * \hideinitializer
 */
#define PWM_DISABLE_COMPLEMENTARY_MODE(pwm) ((pwm)->CTL = (pwm)->CTL & ~PWM_CTL_OUTMODE_Msk)

/**
 * @brief This macro enable group mode
 * @param[in] pwm The base address of PWM module
 * @return None
 * \hideinitializer
 */
#define PWM_ENABLE_GROUP_MODE(pwm) ((pwm)->CTL = (pwm)->CTL | PWM_CTL_GROUPEN_Msk)

/**
 * @brief This macro disable group mode
 * @param[in] pwm The base address of PWM module
 * @return None
 * \hideinitializer
 */
#define PWM_DISABLE_GROUP_MODE(pwm) ((pwm)->CTL = (pwm)->CTL & ~PWM_CTL_GROUPEN_Msk)

/**
 * @brief This macro enable synchronous mode
 * @param[in] pwm The base address of PWM module
 * @return None
 * \hideinitializer
 */
#define PWM_ENABLE_SYNC_MODE(pwm) ((pwm)->CTL = (pwm)->CTL | PWM_CTL_SYNCEN_Msk)

/**
 * @brief This macro disable synchronous mode, and enable independent mode.
 * @param[in] pwm The base address of PWM module
 * @return None
 * \hideinitializer
 */
#define PWM_DISABLE_SYNC_MODE(pwm) ((pwm)->CTL = (pwm)->CTL & ~PWM_CTL_SYNCEN_Msk)

/**
 * @brief This macro enable output inverter of specified channel(s)
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @return None
 * \hideinitializer
 */
#define PWM_ENABLE_OUTPUT_INVERTER(pwm, u32ChannelMask) ((pwm)->CTL = (((pwm)->CTL & ~PWM_CTL_PINV_Msk) | ((u32ChannelMask) << PWM_CTL_PINV_Pos)))

/**
 * @brief This macro get captured rising data
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @return None
 * \hideinitializer
 */
#define PWM_GET_CAPTURE_RISING_DATA(pwm, u32ChannelNum) (*(__IO uint32_t *) (&(pwm)->RCAPDAT0 + 2 * (u32ChannelNum)))

/**
 * @brief This macro get captured falling data
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @return None
 * \hideinitializer
 */
#define PWM_GET_CAPTURE_FALLING_DATA(pwm, u32ChannelNum) (*(__IO uint32_t *) (&(pwm)->FCAPDAT0 + 2 * (u32ChannelNum)))

/**
 * @brief This macro mask output output logic to high or low
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @param[in] u32LevelMask Output logic to high or low
 * @return None
 * \hideinitializer
 */
#define PWM_MASK_OUTPUT(pwm, u32ChannelMask, u32LevelMask) ((pwm)->MSKEN |= (u32ChannelMask))

/**
 * @brief This macro set the prescaler of the selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32Prescaler Clock prescaler of specified channel. Valid values are between 1 ~ 0xFF
 * @return None
 * @note Every even channel N, and channel (N + 1) share a prescaler. So if channel 0 prescaler changed,
 *       channel 1 will also be affected.
 * \hideinitializer
 */
#define PWM_SET_PRESCALER(pwm, u32ChannelNum, u32Prescaler) \
    (pwm->CLKPSC = ((pwm)->CLKPSC & ~(PWM_CLKPSC_CLKPSC01_Msk << (((u32ChannelNum) >> 1) * 8))) | ((u32Prescaler) << (((u32ChannelNum) >> 1) * 8)))

/**
 * @brief This macro set the divider of the selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32Divider Clock divider of specified channel. Valid values are
 *              - \ref PWM_CLK_DIV_1
 *              - \ref PWM_CLK_DIV_2
 *              - \ref PWM_CLK_DIV_4
 *              - \ref PWM_CLK_DIV_8
 *              - \ref PWM_CLK_DIV_16
 * @return None
 * \hideinitializer
 */
#define PWM_SET_DIVIDER(pwm, u32ChannelNum, u32Divider) \
    ((pwm)->CLKDIV = ((pwm)->CLKDIV & ~(PWM_CLKDIV_CLKDIV0_Msk << ((u32ChannelNum) * 4))) | ((u32Divider) << ((u32ChannelNum) * 4)))

/**
 * @brief This macro set the duty of the selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32CMR Duty of specified channel. Valid values are between 0~0xFFFF
 * @return None
 * @note This new setting will take effect on next PWM period
 * \hideinitializer
 */
#define PWM_SET_CMR(pwm, u32ChannelNum, u32CMR) ((pwm)->CMPDAT[(u32ChannelNum)] = (u32CMR))

/**
 * @brief This macro set the period of the selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32CNR Period of specified channel. Valid values are between 0~0xFFFF
 * @return None
 * @note This new setting will take effect on next PWM period
 * @note PWM counter will stop if period length set to 0
 * \hideinitializer
 */
#define PWM_SET_CNR(pwm, u32ChannelNum, u32CNR)  ((pwm)->PERIOD[(u32ChannelNum)] = (u32CNR))

/**
 * @brief This macro set the PWM aligned type
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @param[in] u32AlignedType PWM aligned type, valid values are:
 *                  - \ref PWM_EDGE_ALIGNED
 *                  - \ref PWM_CENTER_ALIGNED
 * @return None
 * \hideinitializer
 */
#define PWM_SET_ALIGNED_TYPE(pwm, u32ChannelMask, u32AlignedType) \
do { \
    (pwm)->CTL = ((pwm)->CTL & ~PWM_CTL_CNTTYPE_Msk); \
    if ((u32AlignedType) == PWM_CENTER_ALIGNED) \
      (pwm)->CTL = ((pwm)->CTL | ((u32ChannelMask) << PWM_CTL_CNTTYPE_Pos)); \
} while(0)


uint32_t PWM_ConfigOutputChannel(PWM_T *pwm,
                                 uint32_t u32ChannelNum,
                                 uint32_t u32Frequency,
                                 uint32_t u32DutyCycle);
uint32_t PWM_ConfigCaptureChannel (PWM_T *pwm,
                                   uint32_t u32ChannelNum,
                                   uint32_t u32UnitTimeNsec,
                                   uint32_t u32CaptureEdge);
void PWM_Start(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_Stop(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_ForceStop(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_EnableADCTrigger(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Condition);
void PWM_DisableADCTrigger(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_ClearADCTriggerFlag(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Condition);
uint32_t PWM_GetADCTriggerFlag(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_EnableFaultBrake(PWM_T *pwm,
                          uint32_t u32ChannelMask,
                          uint32_t u32LevelMask,
                          uint32_t u32BrakeSource);
void PWM_ClearFaultBrakeFlag(PWM_T *pwm, uint32_t u32BrakeSource);
void PWM_EnableCapture(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_DisableCapture(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_EnableOutput(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_DisableOutput(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_EnableDeadZone(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Duration);
void PWM_DisableDeadZone(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_EnableCaptureInt(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge);
void PWM_DisableCaptureInt(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge);
void PWM_ClearCaptureIntFlag(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge);
uint32_t PWM_GetCaptureIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_EnableDutyInt(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32IntDutyType);
void PWM_DisableDutyInt(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_ClearDutyIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);
uint32_t PWM_GetDutyIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_EnableFaultBrakeInt(PWM_T *pwm, uint32_t u32BrakeSource);
void PWM_DisableFaultBrakeInt(PWM_T *pwm, uint32_t u32BrakeSource);
void PWM_ClearFaultBrakeIntFlag(PWM_T *pwm, uint32_t u32BrakeSource);
uint32_t PWM_GetFaultBrakeIntFlag(PWM_T *pwm, uint32_t u32BrakeSource);
void PWM_EnablePeriodInt(PWM_T *pwm, uint32_t u32ChannelNum,  uint32_t u32IntPeriodType);
void PWM_DisablePeriodInt(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_ClearPeriodIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);
uint32_t PWM_GetPeriodIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);



/*@}*/ /* end of group NUC472_442_PWM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_PWM_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__PWM_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
