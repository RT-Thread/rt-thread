/**************************************************************************//**
 * @file     epwm.h
 * @version  V1.00
 * $Revision: 3 $
 * $Date: 15/12/02 5:23p $
 * @brief    NUC472/NUC442 EPWM driver header file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __EPWM_H__
#define __EPWM_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_EPWM_Driver EPWM Driver
  @{
*/

/** @addtogroup NUC472_442_EPWM_EXPORTED_CONSTANTS EPWM Exported Constants
  @{
*/
#define EPWM_CHANNEL_NUM                     (6)      /*!< EPWM channel number \hideinitializer */
#define EPWM_CH0                             (0UL)    /*!< EPWM channel 0  \hideinitializer */
#define EPWM_CH1                             (1UL)    /*!< EPWM channel 1  \hideinitializer */
#define EPWM_CH2                             (2UL)    /*!< EPWM channel 2  \hideinitializer */
#define EPWM_CH3                             (3UL)    /*!< EPWM channel 3  \hideinitializer */
#define EPWM_CH4                             (4UL)    /*!< EPWM channel 4  \hideinitializer */
#define EPWM_CH5                             (5UL)    /*!< EPWM channel 5  \hideinitializer */
#define EPWM_CH_0_MASK                       (1UL)    /*!< EPWM channel 0 mask \hideinitializer */
#define EPWM_CH_1_MASK                       (2UL)    /*!< EPWM channel 1 mask \hideinitializer */
#define EPWM_CH_2_MASK                       (4UL)    /*!< EPWM channel 2 mask \hideinitializer */
#define EPWM_CH_3_MASK                       (8UL)    /*!< EPWM channel 3 mask \hideinitializer */
#define EPWM_CH_4_MASK                       (16UL)   /*!< EPWM channel 4 mask \hideinitializer */
#define EPWM_CH_5_MASK                       (32UL)   /*!< EPWM channel 5 mask \hideinitializer */
#define EPWM_CH_6_MASK                       (64UL)   /*!< EPWM channel 6 mask \hideinitializer */
#define EPWM_CLK_DIV_1                       (0UL)    /*!< EPWM clock divide by 1 \hideinitializer */
#define EPWM_CLK_DIV_2                       (1UL)    /*!< EPWM clock divide by 2 \hideinitializer */
#define EPWM_CLK_DIV_4                       (2UL)    /*!< EPWM clock divide by 4 \hideinitializer */
#define EPWM_CLK_DIV_16                      (3UL)    /*!< EPWM clock divide by 16 \hideinitializer */
#define EPWM_EDGE_ALIGNED                    (0UL)                   /*!< EPWM working in edge aligned type \hideinitializer */
#define EPWM_CENTER_ALIGNED                  (EPWM_CTL_CNTTYPE_Msk)  /*!< EPWM working in center aligned type \hideinitializer */
#define EPWM_BRK0_BKP0                       (EPWM_CTL_BRKP0EN_Msk)  /*!< Brake0 signal source from external pin BKP0 \hideinitializer */
#define EPWM_BRK0_CPO0                       (EPWM_CTL_CPO0BKEN_Msk) /*!< Brake0 signal source from analog comparator 0 output \hideinitializer */
#define EPWM_BRK0_CPO1                       (EPWM_CTL_CPO1BKEN_Msk) /*!< Brake0 signal source from analog comparator 1 output \hideinitializer */
#define EPWM_BRK0_CPO2                       (EPWM_CTL_CPO2BKEN_Msk) /*!< Brake0 signal source from analog comparator 2 output \hideinitializer */
#define EPWM_BRK1_LVDBKEN                    (EPWM_CTL_LVDBKEN_Msk)         /*!< Brake1 signal source from low level detection \hideinitializer */
#define EPWM_BK1SEL_BKP1                     (0UL << EPWM_CTL_BRK1SEL_Pos)  /*!< Brake1 signal source from external pin BKP1 \hideinitializer */
#define EPWM_BK1SEL_CPO0                     (1UL << EPWM_CTL_BRK1SEL_Pos)  /*!< Brake1 signal source from analog comparator 0 output \hideinitializer */
#define EPWM_BK1SEL_CPO1                     (2UL << EPWM_CTL_BRK1SEL_Pos)  /*!< Brake1 signal source from analog comparator 1 output \hideinitializer */
#define EPWM_BK1SEL_CPO2                     (3UL << EPWM_CTL_BRK1SEL_Pos)  /*!< Brake1 signal source from analog comparator 2 output \hideinitializer */
#define EPWM_PERIOD_INT_UNDERFLOW            (0)                     /*!< EPWM period interrupt trigger if counter underflow \hideinitializer */
#define EPWM_PERIOD_INT_MATCH_CNR            (EPWM_CTL_INTTYPE_Msk)  /*!< EPWM period interrupt trigger if counter match CNR \hideinitializer */
#define EPWM_MODE_INDEPENDENT                (0UL)     /*!< EPWM independent mode \hideinitializer */
#define EPWM_MODE_COMPLEMENTARY              (1UL)     /*!< EPWM complementary mode \hideinitializer */
#define EPWM_MODE_SYNCHRONIZED               (2UL)     /*!< EPWM synchronized mode \hideinitializer */

/*@}*/ /* end of group NUC472_442_EPWM_EXPORTED_CONSTANTS */


/** @addtogroup NUC472_442_EPWM_EXPORTED_FUNCTIONS EPWM Exported Functions
  @{
*/

/**
 * @brief This macro enable complementary mode
 * @param[in] pwm The base address of PWM module
 * @return None
 * \hideinitializer
 */
#define EPWM_ENABLE_COMPLEMENTARY_MODE(pwm) ((pwm)->CTL = ((pwm)->CTL & ~EPWM_CTL_MODE_Msk) | (EPWM_MODE_COMPLEMENTARY << EPWM_CTL_MODE_Pos))

/**
 * @brief This macro disable complementary mode, and enable independent mode.
 * @param[in] pwm The base address of PWM module
 * @return None
 * \hideinitializer
 */
#define EPWM_DISABLE_COMPLEMENTARY_MODE(pwm) ((pwm)->CTL &= ~EPWM_CTL_MODE_Msk)

/**
 * @brief This macro enable group mode
 * @param[in] pwm The base address of PWM module
 * @return None
 * \hideinitializer
 */
#define EPWM_ENABLE_GROUP_MODE(pwm) ((pwm)->CTL |= EPWM_CTL_GROUPEN_Msk)

/**
 * @brief This macro disable group mode
 * @param[in] pwm The base address of PWM module
 * @return None
 * \hideinitializer
 */
#define EPWM_DISABLE_GROUP_MODE(pwm) ((pwm)->CTL &= ~EPWM_CTL_GROUPEN_Msk)

/**
 * @brief This macro enable synchronous mode
 * @param[in] pwm The base address of PWM module
 * @return None
 * \hideinitializer
 */
#define EPWM_ENABLE_SYNC_MODE(pwm) ((pwm)->CTL = ((pwm)->CTL & ~EPWM_CTL_MODE_Msk) | (EPWM_MODE_SYNCHRONIZED << EPWM_CTL_MODE_Pos))

/**
 * @brief This macro disable synchronous mode, and enable independent mode.
 * @param[in] pwm The base address of PWM module
 * @return None
 * \hideinitializer
 */
#define EPWM_DISABLE_SYNC_MODE(pwm) ((pwm)->CTL = ((pwm)->CTL & ~EPWM_CTL_MODE_Msk))

/**
 * @brief This macro enable output inverter of specified channel(s)
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @return None
 * \hideinitializer
 */
#define EPWM_ENABLE_OUTPUT_INVERTER(pwm, u32ChannelMask) \
do { \
    if ((u32ChannelMask)) \
        ((pwm)->CTL |= EPWM_CTL_PINV_Msk); \
    else \
        ((pwm)->CTL &= ~EPWM_CTL_PINV_Msk); \
}while(0)

/**
 * @brief This macro mask output output logic to high or low
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @param[in] u32LevelMask Output logic to high or low
 * @return None
 * \hideinitializer
 */
#define EPWM_MASK_OUTPUT(pwm, u32ChannelMask, u32LevelMask) \
do { \
    (pwm)->MSKEN = u32ChannelMask; \
    (pwm)->MSK = u32ChannelMask; \
}while(0)

/**
 * @brief This macro set the divider of the selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32Divider Clock divider of specified channel. Valid values are
 *              - \ref EPWM_CLK_DIV_1
 *              - \ref EPWM_CLK_DIV_2
 *              - \ref EPWM_CLK_DIV_4
 *              - \ref EPWM_CLK_DIV_16
 * @return None
 * \hideinitializer
 */
#define EPWM_SET_DIVIDER(pwm, u32ChannelNum, u32Divider) \
    ((pwm)->CTL = ((pwm)->CTL & ~EPWM_CTL_CLKDIV_Msk) | ((u32Divider) << EPWM_CTL_CLKDIV_Pos))

/**
 * @brief This macro set the duty of the selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32CMR Duty of specified channel. Valid values are between 0~0xFFFF
 * @return None
 * @note This new setting will take effect on next PWM period
 * \hideinitializer
 */
#define EPWM_SET_CMR(pwm, u32ChannelNum, u32CMR) \
do { \
    (pwm)->CMPDAT[(u32ChannelNum) >> 1] = (u32CMR); \
    (pwm)->CTL |= EPWM_CTL_LOAD_Msk; \
}while(0)

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
#define EPWM_SET_CNR(pwm, u32ChannelNum, u32CNR) \
do { \
    (pwm)->PERIOD = (u32CNR); \
    (pwm)->CTL |= EPWM_CTL_LOAD_Msk; \
}while(0)

/**
 * @brief This macro set the PWM aligned type
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask This parameter is not used
 * @param[in] u32AlignedType PWM aligned type, valid values are:
 *                  - \ref EPWM_EDGE_ALIGNED
 *                  - \ref EPWM_CENTER_ALIGNED
 * @return None
 * \hideinitializer
 */
#define EPWM_SET_ALIGNED_TYPE(pwm, u32ChannelMask, u32AlignedType) \
    ((pwm)->CTL = ((pwm)->CTL & ~EPWM_CTL_CNTTYPE_Msk) | (u32AlignedType))


uint32_t EPWM_ConfigOutputChannel(EPWM_T *pwm,
                                 uint32_t u32ChannelNum,
                                 uint32_t u32Frequency,
                                 uint32_t u32DutyCycle);
void EPWM_Start (EPWM_T *pwm, uint32_t u32ChannelMask);
void EPWM_Stop(EPWM_T *pwm, uint32_t u32ChannelMask);
void EPWM_ForceStop(EPWM_T *pwm, uint32_t u32ChannelMask);
void EPWM_EnableFaultBrake(EPWM_T *pwm,
                          uint32_t u32ChannelMask,
                          uint32_t u32LevelMask,
                          uint32_t u32BrakeSource);
void EPWM_ClearFaultBrakeFlag(EPWM_T *pwm, uint32_t u32BrakeSource);
void EPWM_EnableOutput(EPWM_T *pwm, uint32_t u32ChannelMask);
void EPWM_DisableOutput(EPWM_T *pwm, uint32_t u32ChannelMask);
void EPWM_EnableDeadZone(EPWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Duration);
void EPWM_DisableDeadZone(EPWM_T *pwm, uint32_t u32ChannelNum);
void EPWM_EnableDutyInt(EPWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32IntDutyType);
void EPWM_DisableDutyInt(EPWM_T *pwm, uint32_t u32ChannelNum);
void EPWM_ClearDutyIntFlag(EPWM_T *pwm, uint32_t u32ChannelNum);
uint32_t EPWM_GetDutyIntFlag(EPWM_T *pwm, uint32_t u32ChannelNum);
void EPWM_EnableFaultBrakeInt(EPWM_T *pwm, uint32_t u32BrakeSource);
void EPWM_DisableFaultBrakeInt(EPWM_T *pwm, uint32_t u32BrakeSource);
void EPWM_ClearFaultBrakeIntFlag(EPWM_T *pwm, uint32_t u32BrakeSource);
uint32_t EPWM_GetFaultBrakeIntFlag(EPWM_T *pwm, uint32_t u32BrakeSource);
void EPWM_EnablePeriodInt(EPWM_T *pwm, uint32_t u32ChannelNum,  uint32_t u32IntPeriodType);
void EPWM_DisablePeriodInt(EPWM_T *pwm, uint32_t u32ChannelNum);
void EPWM_ClearPeriodIntFlag(EPWM_T *pwm, uint32_t u32ChannelNum);
uint32_t EPWM_GetPeriodIntFlag(EPWM_T *pwm, uint32_t u32ChannelNum);



/*@}*/ /* end of group NUC472_442_EPWM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_EPWM_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__EPWM_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
