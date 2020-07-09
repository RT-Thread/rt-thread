/**************************************************************************//**
 * @file     pwm.h
 * @version  V1.00
 * $Revision: 26 $
 * $Date: 15/08/11 10:26a $
 * @brief    M451 series PWM driver header file
 *
 * @note
 * Copyright (C) 2014~2015 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __PWM_H__
#define __PWM_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup PWM_Driver PWM Driver
  @{
*/

/** @addtogroup PWM_EXPORTED_CONSTANTS PWM Exported Constants
  @{
*/
#define PWM_CHANNEL_NUM                          (6)        /*!< PWM channel number */
#define PWM_CH_0_MASK                            (0x1UL)    /*!< PWM channel 0 mask \hideinitializer */
#define PWM_CH_1_MASK                            (0x2UL)    /*!< PWM channel 1 mask \hideinitializer */
#define PWM_CH_2_MASK                            (0x4UL)    /*!< PWM channel 2 mask \hideinitializer */
#define PWM_CH_3_MASK                            (0x8UL)    /*!< PWM channel 3 mask \hideinitializer */
#define PWM_CH_4_MASK                            (0x10UL)   /*!< PWM channel 4 mask \hideinitializer */
#define PWM_CH_5_MASK                            (0x20UL)   /*!< PWM channel 5 mask \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Counter Type Constant Definitions                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define PWM_UP_COUNTER                           (0UL)      /*!< Up counter type */
#define PWM_DOWN_COUNTER                         (1UL)      /*!< Down counter type */
#define PWM_UP_DOWN_COUNTER                      (2UL)      /*!< Up-Down counter type */

/*---------------------------------------------------------------------------------------------------------*/
/*  Aligned Type Constant Definitions                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define PWM_EDGE_ALIGNED                         (1UL)      /*!< PWM working in edge aligned type(down count) */
#define PWM_CENTER_ALIGNED                       (2UL)      /*!< PWM working in center aligned type */

/*---------------------------------------------------------------------------------------------------------*/
/*  Output Level Constant Definitions                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define PWM_OUTPUT_NOTHING                       (0UL)      /*!< PWM output nothing */
#define PWM_OUTPUT_LOW                           (1UL)      /*!< PWM output low */
#define PWM_OUTPUT_HIGH                          (2UL)      /*!< PWM output high */
#define PWM_OUTPUT_TOGGLE                        (3UL)      /*!< PWM output toggle */

/*---------------------------------------------------------------------------------------------------------*/
/*  Trigger Source Select Constant Definitions                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define PWM_TRIGGER_ADC_EVEN_ZERO_POINT                     (0UL)     /*!< PWM trigger ADC while counter of even channel matches zero point */
#define PWM_TRIGGER_ADC_EVEN_PERIOD_POINT                   (1UL)     /*!< PWM trigger ADC while counter of even channel matches period point */
#define PWM_TRIGGER_ADC_EVEN_ZERO_OR_PERIOD_POINT           (2UL)     /*!< PWM trigger ADC while counter of even channel matches zero or period point */
#define PWM_TRIGGER_ADC_EVEN_COMPARE_UP_COUNT_POINT         (3UL)     /*!< PWM trigger ADC while counter of even channel matches up count to comparator point */
#define PWM_TRIGGER_ADC_EVEN_COMPARE_DOWN_COUNT_POINT       (4UL)     /*!< PWM trigger ADC while counter of even channel matches down count to comparator point */
#define PWM_TRIGGER_ADC_ODD_ZERO_POINT                      (5UL)     /*!< PWM trigger ADC while counter of odd channel matches zero point */
#define PWM_TRIGGER_ADC_ODD_PERIOD_POINT                    (6UL)     /*!< PWM trigger ADC while counter of odd channel matches period point */
#define PWM_TRIGGER_ADC_ODD_ZERO_OR_PERIOD_POINT            (7UL)     /*!< PWM trigger ADC while counter of odd channel matches zero or period point */
#define PWM_TRIGGER_ADC_ODD_COMPARE_UP_COUNT_POINT          (8UL)     /*!< PWM trigger ADC while counter of odd channel matches up count to comparator point */
#define PWM_TRIGGER_ADC_ODD_COMPARE_DOWN_COUNT_POINT        (9UL)     /*!< PWM trigger ADC while counter of odd channel matches down count to comparator point */
#define PWM_TRIGGER_ADC_CH_0_FREE_COMPARE_UP_COUNT_POINT    (10UL)    /*!< PWM trigger ADC while counter of channel 0 matches up count to free comparator point */
#define PWM_TRIGGER_ADC_CH_0_FREE_COMPARE_DOWN_COUNT_POINT  (11UL)    /*!< PWM trigger ADC while counter of channel 0 matches down count to free comparator point */
#define PWM_TRIGGER_ADC_CH_2_FREE_COMPARE_UP_COUNT_POINT    (12UL)    /*!< PWM trigger ADC while counter of channel 2 matches up count to free comparator point */
#define PWM_TRIGGER_ADC_CH_2_FREE_COMPARE_DOWN_COUNT_POINT  (13UL)    /*!< PWM trigger ADC while counter of channel 2 matches down count to free comparator point */
#define PWM_TRIGGER_ADC_CH_4_FREE_COMPARE_UP_COUNT_POINT    (14UL)    /*!< PWM trigger ADC while counter of channel 4 matches up count to free comparator point */
#define PWM_TRIGGER_ADC_CH_4_FREE_COMPARE_DOWN_COUNT_POINT  (15UL)    /*!< PWM trigger ADC while counter of channel 4 matches down count to free comparator point */

#define PWM_TRIGGER_DAC_ZERO_POINT                          (0x1UL)           /*!< PWM trigger ADC while counter down count to 0  \hideinitializer */
#define PWM_TRIGGER_DAC_PERIOD_POINT                        (0x100UL)         /*!< PWM trigger ADC while counter matches (PERIOD + 1) \hideinitializer */
#define PWM_TRIGGER_DAC_COMPARE_UP_COUNT_POINT              (0x10000UL)       /*!< PWM trigger ADC while counter up count to CMPDAT \hideinitializer */
#define PWM_TRIGGER_DAC_COMPARE_DOWN_COUNT_POINT            (0x1000000UL)     /*!< PWM trigger ADC while counter down count to CMPDAT \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Fail brake Control Constant Definitions                                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define PWM_FB_EDGE_ACMP0                        (PWM_BRKCTL0_1_CPO0EBEN_Msk)    /*!< Comparator 0 as edge-detect fault brake source */
#define PWM_FB_EDGE_ACMP1                        (PWM_BRKCTL0_1_CPO1EBEN_Msk)    /*!< Comparator 1 as edge-detect fault brake source */
#define PWM_FB_EDGE_BKP0                         (PWM_BRKCTL0_1_BRKP0EEN_Msk)    /*!< BKP0 pin as edge-detect fault brake source */
#define PWM_FB_EDGE_BKP1                         (PWM_BRKCTL0_1_BRKP1EEN_Msk)    /*!< BKP1 pin as edge-detect fault brake source */
#define PWM_FB_EDGE_SYS_CSS                      (PWM_BRKCTL0_1_SYSEBEN_Msk | PWM_FAILBRK_CSSBRKEN_Msk)    /*!< System fail condition: clock security system detection as edge-detect fault brake source */
#define PWM_FB_EDGE_SYS_BOD                      (PWM_BRKCTL0_1_SYSEBEN_Msk | PWM_FAILBRK_BODBRKEN_Msk)    /*!< System fail condition: brown-out detection as edge-detect fault brake source */
#define PWM_FB_EDGE_SYS_RAM                      (PWM_BRKCTL0_1_SYSEBEN_Msk | PWM_FAILBRK_RAMBRKEN_Msk)    /*!< System fail condition: SRAM parity error detection as edge-detect fault brake source */
#define PWM_FB_EDGE_SYS_COR                      (PWM_BRKCTL0_1_SYSEBEN_Msk | PWM_FAILBRK_CORBRKEN_Msk)    /*!< System fail condition: core lockup detection as edge-detect fault brake source */

#define PWM_FB_LEVEL_ACMP0                       (PWM_BRKCTL0_1_CPO0LBEN_Msk)    /*!< Comparator 0 as level-detect fault brake source */
#define PWM_FB_LEVEL_ACMP1                       (PWM_BRKCTL0_1_CPO1LBEN_Msk)    /*!< Comparator 1 as level-detect fault brake source */
#define PWM_FB_LEVEL_BKP0                        (PWM_BRKCTL0_1_BRKP0LEN_Msk)    /*!< BKP0 pin as level-detect fault brake source */
#define PWM_FB_LEVEL_BKP1                        (PWM_BRKCTL0_1_BRKP1LEN_Msk)    /*!< BKP1 pin as level-detect fault brake source */
#define PWM_FB_LEVEL_SYS_CSS                     (PWM_BRKCTL0_1_SYSLBEN_Msk | PWM_FAILBRK_CSSBRKEN_Msk)    /*!< System fail condition: clock security system detection as level-detect fault brake source */
#define PWM_FB_LEVEL_SYS_BOD                     (PWM_BRKCTL0_1_SYSLBEN_Msk | PWM_FAILBRK_BODBRKEN_Msk)    /*!< System fail condition: brown-out detection as level-detect fault brake source */
#define PWM_FB_LEVEL_SYS_RAM                     (PWM_BRKCTL0_1_SYSLBEN_Msk | PWM_FAILBRK_RAMBRKEN_Msk)    /*!< System fail condition: SRAM parity error detection as level-detect fault brake source */
#define PWM_FB_LEVEL_SYS_COR                     (PWM_BRKCTL0_1_SYSLBEN_Msk | PWM_FAILBRK_CORBRKEN_Msk)    /*!< System fail condition: core lockup detection as level-detect fault brake source */

#define PWM_FB_EDGE                              (0UL)    /*!< edge-detect fault brake */
#define PWM_FB_LEVEL                             (8UL)    /*!< level-detect fault brake */

/*---------------------------------------------------------------------------------------------------------*/
/*  Capture Control Constant Definitions                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define PWM_CAPTURE_INT_RISING_LATCH             (1UL)        /*!< PWM capture interrupt if channel has rising transition */
#define PWM_CAPTURE_INT_FALLING_LATCH            (0x100UL)    /*!< PWM capture interrupt if channel has falling transition */

#define PWM_CAPTURE_PDMA_RISING_LATCH            (0x2UL)      /*!< PWM capture rising latched data transfer by PDMA */
#define PWM_CAPTURE_PDMA_FALLING_LATCH           (0x4UL)      /*!< PWM capture falling latched data transfer by PDMA */
#define PWM_CAPTURE_PDMA_RISING_FALLING_LATCH    (0x6UL)      /*!< PWM capture rising and falling latched data transfer by PDMA */

/*---------------------------------------------------------------------------------------------------------*/
/*  Duty Interrupt Type Constant Definitions                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define PWM_DUTY_INT_DOWN_COUNT_MATCH_CMP        (PWM_INTEN0_CMPDIEN0_Msk)   /*!< PWM duty interrupt triggered if down count match comparator */
#define PWM_DUTY_INT_UP_COUNT_MATCH_CMP          (PWM_INTEN0_CMPUIEN0_Msk)   /*!< PWM duty interrupt triggered if up down match comparator */

/*---------------------------------------------------------------------------------------------------------*/
/*  Interrupt Flag Accumulator Constant Definitions                                                        */
/*---------------------------------------------------------------------------------------------------------*/
#define PWM_IFA_EVEN_ZERO_POINT                  (0UL)         /*!< PWM counter equal to zero in even channel  \hideinitializer */
#define PWM_IFA_EVEN_PERIOD_POINT                (1UL)         /*!< PWM counter equal to period in even channel \hideinitializer */
#define PWM_IFA_EVEN_COMPARE_UP_COUNT_POINT      (2UL)         /*!< PWM counter up count to comparator value in even channel \hideinitializer */
#define PWM_IFA_EVEN_COMPARE_DOWN_COUNT_POINT    (3UL)         /*!< PWM counter down count to comparator value in even channel \hideinitializer */
#define PWM_IFA_ODD_ZERO_POINT                   (4UL)         /*!< PWM counter equal to zero in odd channel  \hideinitializer */
#define PWM_IFA_ODD_PERIOD_POINT                 (5UL)         /*!< PWM counter equal to period in odd channel \hideinitializer */
#define PWM_IFA_ODD_COMPARE_UP_COUNT_POINT       (6UL)         /*!< PWM counter up count to comparator value in odd channel \hideinitializer */
#define PWM_IFA_ODD_COMPARE_DOWN_COUNT_POINT     (7UL)         /*!< PWM counter down count to comparator value in odd channel \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Load Mode Constant Definitions                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define PWM_LOAD_MODE_IMMEDIATE                  (PWM_CTL0_IMMLDEN0_Msk)    /*!< PWM immediately load mode \hideinitializer */
#define PWM_LOAD_MODE_WINDOW                     (PWM_CTL0_WINLDEN0_Msk)    /*!< PWM window load mode \hideinitializer */
#define PWM_LOAD_MODE_CENTER                     (PWM_CTL0_CTRLD0_Msk)      /*!< PWM center load mode \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Synchronize Control Constant Definitions                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define PWM_SYNC_OUT_FROM_SYNCIN_SWSYNC          (0UL)    /*!< Synchronize source from SYNC_IN or SWSYNC  \hideinitializer */
#define PWM_SYNC_OUT_FROM_COUNT_TO_ZERO          (1UL)    /*!< Synchronize source from counter equal to 0  \hideinitializer */
#define PWM_SYNC_OUT_FROM_COUNT_TO_COMPARATOR    (2UL)    /*!< Synchronize source from counter equal to CMPDAT1, CMPDAT3, CMPDAT5 \hideinitializer */
#define PWM_SYNC_OUT_DISABLE                     (3UL)    /*!< SYNC_OUT will not be generated \hideinitializer */
#define PWM_PHS_DIR_DECREMENT                    (0UL)    /*!< PWM counter count decrement  \hideinitializer */
#define PWM_PHS_DIR_INCREMENT                    (1UL)    /*!< PWM counter count increment  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Noise Filter Clock Divide Select Constant Definitions                                                  */
/*---------------------------------------------------------------------------------------------------------*/
#define PWM_NF_CLK_DIV_1                         (0UL)    /*!< Noise filter clock is HCLK divide by 1 \hideinitializer */
#define PWM_NF_CLK_DIV_2                         (1UL)    /*!< Noise filter clock is HCLK divide by 2 \hideinitializer */
#define PWM_NF_CLK_DIV_4                         (2UL)    /*!< Noise filter clock is HCLK divide by 4 \hideinitializer */
#define PWM_NF_CLK_DIV_8                         (3UL)    /*!< Noise filter clock is HCLK divide by 8 \hideinitializer */
#define PWM_NF_CLK_DIV_16                        (4UL)    /*!< Noise filter clock is HCLK divide by 16 \hideinitializer */
#define PWM_NF_CLK_DIV_32                        (5UL)    /*!< Noise filter clock is HCLK divide by 32 \hideinitializer */
#define PWM_NF_CLK_DIV_64                        (6UL)    /*!< Noise filter clock is HCLK divide by 64 \hideinitializer */
#define PWM_NF_CLK_DIV_128                       (7UL)    /*!< Noise filter clock is HCLK divide by 128 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Clock Source Select Constant Definitions                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define PWM_CLKSRC_PWM_CLK                       (0UL)    /*!< PWM Clock source selects to PWM0_CLK or PWM1_CLK \hideinitializer */
#define PWM_CLKSRC_TIMER0                        (1UL)    /*!< PWM Clock source selects to TIMER0 overflow \hideinitializer */
#define PWM_CLKSRC_TIMER1                        (2UL)    /*!< PWM Clock source selects to TIMER1 overflow \hideinitializer */
#define PWM_CLKSRC_TIMER2                        (3UL)    /*!< PWM Clock source selects to TIMER2 overflow \hideinitializer */
#define PWM_CLKSRC_TIMER3                        (4UL)    /*!< PWM Clock source selects to TIMER3 overflow \hideinitializer */


/*@}*/ /* end of group PWM_EXPORTED_CONSTANTS */


/** @addtogroup PWM_EXPORTED_FUNCTIONS PWM Exported Functions
  @{
*/

/**
 * @brief This macro enable complementary mode
 * @param[in] pwm The pointer of the specified PWM module
 * @return None
 * @details This macro is used to enable complementary mode of PWM module.
 * \hideinitializer
 */
#define PWM_ENABLE_COMPLEMENTARY_MODE(pwm) ((pwm)->CTL1 = (pwm)->CTL1 | PWM_CTL1_OUTMODEn_Msk)

/**
 * @brief This macro disable complementary mode, and enable independent mode.
 * @param[in] pwm The pointer of the specified PWM module
 * @return None
 * @details This macro is used to disable complementary mode of PWM module.
 * \hideinitializer
 */
#define PWM_DISABLE_COMPLEMENTARY_MODE(pwm) ((pwm)->CTL1 = (pwm)->CTL1 & ~PWM_CTL1_OUTMODEn_Msk)

/**
 * @brief This macro enable group mode
 * @param[in] pwm The pointer of the specified PWM module
 * @return None
 * @details This macro is used to enable group mode of PWM module.
 * \hideinitializer
 */
#define PWM_ENABLE_GROUP_MODE(pwm) ((pwm)->CTL0 = (pwm)->CTL0 | PWM_CTL0_GROUPEN_Msk)

/**
 * @brief This macro disable group mode
 * @param[in] pwm The pointer of the specified PWM module
 * @return None
 * @details This macro is used to disable group mode of PWM module.
 * \hideinitializer
 */
#define PWM_DISABLE_GROUP_MODE(pwm) ((pwm)->CTL0 = (pwm)->CTL0 & ~PWM_CTL0_GROUPEN_Msk)

/**
 * @brief Enable timer synchronous mode of specified channel(s)
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @return None
 * @details This macro is used to enable timer synchronous mode of specified channel(s).
 * \hideinitializer
 */
#define PWM_ENABLE_TIMER_SYNC(pwm, u32ChannelMask) ((pwm)->SSCTL |= (u32ChannelMask))

/**
 * @brief Disable timer synchronous mode of specified channel(s)
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @return None
 * @details This macro is used to disable timer synchronous mode of specified channel(s).
 * \hideinitializer
 */
#define PWM_DISABLE_TIMER_SYNC(pwm, u32ChannelMask) \
    do{ \
        int i;\
        for(i = 0; i < 6; i++) { \
            if((u32ChannelMask) & (1 << i)) \
                (pwm)->SSCTL &= ~(1UL << i); \
        } \
    }while(0)

/**
 * @brief This macro enable output inverter of specified channel(s)
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @return None
 * @details This macro is used to enable output inverter of specified channel(s).
 * \hideinitializer
 */
#define PWM_ENABLE_OUTPUT_INVERTER(pwm, u32ChannelMask) ((pwm)->POLCTL = (u32ChannelMask))

/**
 * @brief This macro get captured rising data
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @return None
 * @details This macro is used to get captured rising data of specified channel.
 * \hideinitializer
 */
#define PWM_GET_CAPTURE_RISING_DATA(pwm, u32ChannelNum) (*(__IO uint32_t *) (&((pwm)->RCAPDAT0) + 2 * (u32ChannelNum)))

/**
 * @brief This macro get captured falling data
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @return None
 * @details This macro is used to get captured falling data of specified channel.
 * \hideinitializer
 */
#define PWM_GET_CAPTURE_FALLING_DATA(pwm, u32ChannelNum) (*(__IO uint32_t *) (&((pwm)->FCAPDAT0) + 2 * (u32ChannelNum)))

/**
 * @brief This macro mask output logic to high or low
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @param[in] u32LevelMask Output logic to high or low
 * @return None
 * @details This macro is used to mask output logic to high or low of specified channel(s).
 * @note If u32ChannelMask parameter is 0, then mask function will be disabled.
 * \hideinitializer
 */
#define PWM_MASK_OUTPUT(pwm, u32ChannelMask, u32LevelMask) \
    { \
        (pwm)->MSKEN = (u32ChannelMask); \
        (pwm)->MSK = (u32LevelMask); \
    }

/**
 * @brief This macro set the prescaler of the selected channel
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32Prescaler Clock prescaler of specified channel. Valid values are between 1 ~ 0xFFF
 * @return None
 * @details This macro is used to set the prescaler of specified channel.
 * @note Every even channel N, and channel (N + 1) share a prescaler. So if channel 0 prescaler changed,
 *       channel 1 will also be affected.
 * \hideinitializer
 */
#define PWM_SET_PRESCALER(pwm, u32ChannelNum, u32Prescaler) (*(__IO uint32_t *) (&((pwm)->CLKPSC0_1) + ((u32ChannelNum) >> 1)) = (u32Prescaler))

/**
 * @brief This macro set the comparator of the selected channel
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32CMR Comparator of specified channel. Valid values are between 0~0xFFFF
 * @return None
 * @details This macro is used to set the comparator of specified channel.
 * @note This new setting will take effect on next PWM period.
 * \hideinitializer
 */
#define PWM_SET_CMR(pwm, u32ChannelNum, u32CMR) ((pwm)->CMPDAT[(u32ChannelNum)]= (u32CMR))

/**
 * @brief This macro set the free trigger comparator of the selected channel
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32FTCMR Free trigger comparator of specified channel. Valid values are between 0~0xFFFF
 * @return None
 * @details This macro is used to set the free trigger comparator of specified channel.
 * @note This new setting will take effect on next PWM period.
 * \hideinitializer
 */
#define PWM_SET_FTCMR(pwm, u32ChannelNum, u32FTCMR) (*(__IO uint32_t *) (&((pwm)->FTCMPDAT0_1) + ((u32ChannelNum) >> 1)) = (u32FTCMR))

/**
 * @brief This macro set the period of the selected channel
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32CNR Period of specified channel. Valid values are between 0~0xFFFF
 * @return None
 * @details This macro is used to set the period of specified channel.
 * @note This new setting will take effect on next PWM period.
 * @note PWM counter will stop if period length set to 0.
 * \hideinitializer
 */
#define PWM_SET_CNR(pwm, u32ChannelNum, u32CNR)  ((pwm)->PERIOD[(u32ChannelNum)] = (u32CNR))

/**
 * @brief This macro set the PWM aligned type
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @param[in] u32AlignedType PWM aligned type, valid values are:
 *              - \ref PWM_EDGE_ALIGNED
 *              - \ref PWM_CENTER_ALIGNED
 * @return None
 * @details This macro is used to set the PWM aligned type of specified channel(s).
 * \hideinitializer
 */
#define PWM_SET_ALIGNED_TYPE(pwm, u32ChannelMask, u32AlignedType) \
   do{ \
        int i; \
        for(i = 0; i < 6; i++) { \
            if((u32ChannelMask) & (1 << i)) \
                (pwm)->CTL1 = (((pwm)->CTL1 & ~(3UL << (2 * i))) | ((u32AlignedType) << ( 2 * i))); \
        } \
    }while(0)

/**
 * @brief Set load window of window loading mode for specified channel(s)
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @return None
 * @details This macro is used to set load window of window loading mode for specified channel(s).
 * \hideinitializer
 */
#define PWM_SET_LOAD_WINDOW(pwm, u32ChannelMask) ((pwm)->LOAD |= (u32ChannelMask))

/**
 * @brief Trigger synchronous event from specified channel(s)
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are 0, 2, 4
 *                           Bit 0 represents channel 0, bit 1 represents channel 2 and bit 2 represents channel 4
 * @return None
 * @details This macro is used to trigger synchronous event from specified channel(s).
 * \hideinitializer
 */
#define PWM_TRIGGER_SYNC(pwm, u32ChannelNum) ((pwm)->SWSYNC |= (1 << ((u32ChannelNum) >> 1)))

/**
 * @brief Clear counter of specified channel(s)
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @return None
 * @details This macro is used to clear counter of specified channel(s).
 * \hideinitializer
 */
#define PWM_CLR_COUNTER(pwm, u32ChannelMask) ((pwm)->CNTCLR |= (u32ChannelMask))

/**
 * @brief Set output level at zero, compare up, period(center) and compare down of specified channel(s)
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @param[in] u32ZeroLevel output level at zero point, valid values are:
 *              - \ref PWM_OUTPUT_NOTHING
 *              - \ref PWM_OUTPUT_LOW
 *              - \ref PWM_OUTPUT_HIGH
 *              - \ref PWM_OUTPUT_TOGGLE
 * @param[in] u32CmpUpLevel output level at compare up point, valid values are:
 *              - \ref PWM_OUTPUT_NOTHING
 *              - \ref PWM_OUTPUT_LOW
 *              - \ref PWM_OUTPUT_HIGH
 *              - \ref PWM_OUTPUT_TOGGLE
 * @param[in] u32PeriodLevel output level at period(center) point, valid values are:
 *              - \ref PWM_OUTPUT_NOTHING
 *              - \ref PWM_OUTPUT_LOW
 *              - \ref PWM_OUTPUT_HIGH
 *              - \ref PWM_OUTPUT_TOGGLE
 * @param[in] u32CmpDownLevel output level at compare down point, valid values are:
 *              - \ref PWM_OUTPUT_NOTHING
 *              - \ref PWM_OUTPUT_LOW
 *              - \ref PWM_OUTPUT_HIGH
 *              - \ref PWM_OUTPUT_TOGGLE
 * @return None
 * @details This macro is used to Set output level at zero, compare up, period(center) and compare down of specified channel(s).
 * \hideinitializer
 */
#define PWM_SET_OUTPUT_LEVEL(pwm, u32ChannelMask, u32ZeroLevel, u32CmpUpLevel, u32PeriodLevel, u32CmpDownLevel) \
   do{ \
        int i; \
        for(i = 0; i < 6; i++) { \
            if((u32ChannelMask) & (1 << i)) { \
                (pwm)->WGCTL0 = (((pwm)->WGCTL0 & ~(3UL << (2 * i))) | ((u32ZeroLevel) << (2 * i))); \
                (pwm)->WGCTL0 = (((pwm)->WGCTL0 & ~(3UL << (PWM_WGCTL0_PRDPCTLn_Pos + (2 * i)))) | ((u32PeriodLevel) << (PWM_WGCTL0_PRDPCTLn_Pos + (2 * i)))); \
                (pwm)->WGCTL1 = (((pwm)->WGCTL1 & ~(3UL << (2 * i))) | ((u32CmpUpLevel) << (2 * i))); \
                (pwm)->WGCTL1 = (((pwm)->WGCTL1 & ~(3UL << (PWM_WGCTL1_CMPDCTLn_Pos + (2 * i)))) | ((u32CmpDownLevel) << (PWM_WGCTL1_CMPDCTLn_Pos + (2 * i)))); \
            } \
        } \
    }while(0)

/**
 * @brief Trigger brake event from specified channel(s)
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 2 and bit 2 represents channel 4
 * @param[in] u32BrakeType Type of brake trigger. PWM_FB_EDGE of this macro is only supported in M45xD/M45xC.
 *              - \ref PWM_FB_EDGE
 *              - \ref PWM_FB_LEVEL
 * @return None
 * @details This macro is used to trigger brake event from specified channel(s).
 * \hideinitializer
 */
#define PWM_TRIGGER_BRAKE(pwm, u32ChannelMask, u32BrakeType) ((pwm)->SWBRK |= ((u32ChannelMask) << (u32BrakeType)))

/**
 * @brief Set Dead zone clock source
 * @param[in] pwm The pointer of the specified PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5
 * @param[in] u32AfterPrescaler Dead zone clock source is from prescaler output. Valid values are TRUE (after prescaler) or FALSE (before prescaler).
 * @return None
 * @details This macro is used to set Dead zone clock source. Every two channels share the same setting.
 * @note The write-protection function should be disabled before using this function.
 * @note This function is only supported in M45xD/M45xC.
 * \hideinitializer
 */
#define PWM_SET_DEADZONE_CLK_SRC(pwm, u32ChannelNum, u32AfterPrescaler) \
    (*(__IO uint32_t *) (&((pwm)->DTCTL0_1) + ((u32ChannelNum) >> 1)) = (*(__IO uint32_t *) (&((pwm)->DTCTL0_1) + ((u32ChannelNum) >> 1)) & ~PWM_DTCTL0_1_DTCKSEL_Msk) | \
    ((u32AfterPrescaler) << PWM_DTCTL0_1_DTCKSEL_Pos))

/*---------------------------------------------------------------------------------------------------------*/
/* Define PWM functions prototype                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
uint32_t PWM_ConfigCaptureChannel(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32UnitTimeNsec, uint32_t u32CaptureEdge);
uint32_t PWM_ConfigOutputChannel(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Frequency, uint32_t u32DutyCycle);
void PWM_Start(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_Stop(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_ForceStop(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_EnableADCTrigger(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Condition);
void PWM_DisableADCTrigger(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_ClearADCTriggerFlag(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Condition);
uint32_t PWM_GetADCTriggerFlag(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_EnableDACTrigger(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Condition);
void PWM_DisableDACTrigger(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_ClearDACTriggerFlag(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Condition);
uint32_t PWM_GetDACTriggerFlag(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_EnableFaultBrake(PWM_T *pwm, uint32_t u32ChannelMask, uint32_t u32LevelMask, uint32_t u32BrakeSource);
void PWM_EnableCapture(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_DisableCapture(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_EnableOutput(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_DisableOutput(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_EnablePDMA(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32RisingFirst, uint32_t u32Mode);
void PWM_DisablePDMA(PWM_T *pwm, uint32_t u32ChannelNum);
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
void PWM_EnableZeroInt(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_DisableZeroInt(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_ClearZeroIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);
uint32_t PWM_GetZeroIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_EnableAcc(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32IntFlagCnt, uint32_t u32IntAccSrc);
void PWM_DisableAcc(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_EnableAccInt(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_DisableAccInt(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_ClearAccInt(PWM_T *pwm, uint32_t u32ChannelNum);
uint32_t PWM_GetAccInt(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_ClearFTDutyIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);
uint32_t PWM_GetFTDutyIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_EnableLoadMode(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32LoadMode);
void PWM_DisableLoadMode(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32LoadMode);
void PWM_ConfigSyncPhase(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32SyncSrc, uint32_t u32Direction, uint32_t u32StartPhase);
void PWM_EnableSyncPhase(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_DisableSyncPhase(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_EnableSyncNoiseFilter(PWM_T *pwm, uint32_t u32ClkCnt, uint32_t u32ClkDivSel);
void PWM_DisableSyncNoiseFilter(PWM_T *pwm);
void PWM_EnableSyncPinInverse(PWM_T *pwm);
void PWM_DisableSyncPinInverse(PWM_T *pwm);
void PWM_SetClockSource(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32ClkSrcSel);
void PWM_EnableBrakeNoiseFilter(PWM_T *pwm, uint32_t u32BrakePinNum, uint32_t u32ClkCnt, uint32_t u32ClkDivSel);
void PWM_DisableBrakeNoiseFilter(PWM_T *pwm, uint32_t u32BrakePinNum);
void PWM_EnableBrakePinInverse(PWM_T *pwm, uint32_t u32BrakePinNum);
void PWM_DisableBrakePinInverse(PWM_T *pwm, uint32_t u32BrakePinNum);
void PWM_SetBrakePinSource(PWM_T *pwm, uint32_t u32BrakePinNum, uint32_t u32SelAnotherModule);
uint32_t PWM_GetWrapAroundFlag(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_ClearWrapAroundFlag(PWM_T *pwm, uint32_t u32ChannelNum);


/*@}*/ /* end of group PWM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group PWM_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif //__PWM_H__

/*** (C) COPYRIGHT 2014~2015 Nuvoton Technology Corp. ***/
