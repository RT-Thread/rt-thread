/**************************************************************************//**
 * @file     tk.h
 * @version  V1.00
 * $Revision: 6 $
 * $Date: 15/08/24 4:52p $
 * @brief    M451 Series TK Driver Header File
 *
 * @note
 * Copyright (C) 2014~2015 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __TK_H__
#define __TK_H__

#include "M451Series.h"

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup TK_Driver TK Driver
  @{
*/

/** @addtogroup TK_EXPORTED_CONSTANTS TK Exported Constants
  @{
*/

#define TK_SCAN_MODE_SINGLE                 (0UL)  /*!< Touch key single scan mode */
#define TK_SCAN_MODE_PERIODIC               (TK_CTL_TMRTRGEN_Msk)  /*!< Touch key periodic scan mode */
#define TK_SCAN_MODE_ALL_KEY                (TK_REFCTL_SCANALL_Msk)  /*!< Touch key all keys scan mode */
#define TK_SCAN_MODE_PERIODIC_ALL_KEY       (TK_CTL_TMRTRGEN_Msk | TK_REFCTL_SCANALL_Msk)  /*!< Touch key periodic with all keys scan mode */

#define TK_SENSE_PULSE_1                    (0UL << TK_REFCTL_SENPTCTL_Pos)  /*!< Touch key sensing pulse width is 1us */
#define TK_SENSE_PULSE_2                    (1UL << TK_REFCTL_SENPTCTL_Pos)  /*!< Touch key sensing pulse width is 2us */
#define TK_SENSE_PULSE_4                    (2UL << TK_REFCTL_SENPTCTL_Pos)  /*!< Touch key sensing pulse width is 4us */
#define TK_SENSE_PULSE_8                    (3UL << TK_REFCTL_SENPTCTL_Pos)  /*!< Touch key sensing pulse width is 8us */

#define TK_SENSE_CNT_128                    (0UL << TK_REFCTL_SENTCTL_Pos)  /*!< Touch key sensing count is 128 */
#define TK_SENSE_CNT_255                    (1UL << TK_REFCTL_SENTCTL_Pos)  /*!< Touch key sensing count is 255 */
#define TK_SENSE_CNT_511                    (2UL << TK_REFCTL_SENTCTL_Pos)  /*!< Touch key sensing count is 511 */
#define TK_SENSE_CNT_1023                   (3UL << TK_REFCTL_SENTCTL_Pos)  /*!< Touch key sensing count is 1023 */

#define TK_AVCCH_1_DIV_16                   (0UL << TK_CTL_AVCCHSEL_Pos)  /*!< Touch key AVCCH voltage is 1/16 VDD */
#define TK_AVCCH_1_DIV_8                    (1UL << TK_CTL_AVCCHSEL_Pos)  /*!< Touch key AVCCH voltage is 1/8 VDD */
#define TK_AVCCH_3_DIV_16                   (2UL << TK_CTL_AVCCHSEL_Pos)  /*!< Touch key AVCCH voltage is 3/16 VDD */
#define TK_AVCCH_1_DIV_4                    (3UL << TK_CTL_AVCCHSEL_Pos)  /*!< Touch key AVCCH voltage is 1/4 VDD */
#define TK_AVCCH_5_DIV_16                   (4UL << TK_CTL_AVCCHSEL_Pos)  /*!< Touch key AVCCH voltage is 5/16 VDD */
#define TK_AVCCH_3_DIV_8                    (5UL << TK_CTL_AVCCHSEL_Pos)  /*!< Touch key AVCCH voltage is 3/8 VDD */
#define TK_AVCCH_7_DIV_16                   (6UL << TK_CTL_AVCCHSEL_Pos)  /*!< Touch key AVCCH voltage is 7/16 VDD */
#define TK_AVCCH_1_DIV_2                    (7UL << TK_CTL_AVCCHSEL_Pos)  /*!< Touch key AVCCH voltage is 1/2 VDD */

#define TK_CAP_BANK_POL_SEL_GND             (0UL << TK_POLCTL_CBPOLSEL_Pos)  /*!< Touch key capacitor bank polarity is GND */
#define TK_CAP_BANK_POL_SEL_AVCCH           (1UL << TK_POLCTL_CBPOLSEL_Pos)  /*!< Touch key capacitor bank polarity is AVCCH */
#define TK_CAP_BANK_POL_SEL_VDD             (2UL << TK_POLCTL_CBPOLSEL_Pos)  /*!< Touch key capacitor bank polarity is VDD */

#define TK_TKn_POL_SEL_GND                  (0UL)  /*!< Touch key polarity is GND */
#define TK_TKn_POL_SEL_AVCCH                (1UL)  /*!< Touch key polarity is AVCCH */
#define TK_TKn_POL_SEL_VDD                  (2UL)  /*!< Touch key polarity is VDD */

#define TK_INT_EN_SCAN_COMPLETE             (TK_INTEN_SCINTEN_Msk)  /*!< Touch key enable scan complete interrupt */
#define TK_INT_EN_SCAN_COMPLETE_EDGE_TH     (TK_INTEN_SCTHIEN_Msk)  /*!< Touch key enable scan complete with threshold interrupt of edge trigger mode */
#define TK_INT_EN_SCAN_COMPLETE_LEVEL_TH    (TK_INTEN_THIMOD_Msk | TK_INTEN_SCTHIEN_Msk)  /*!< Touch key enable scan complete with threshold interrupt of level trigger mode */

#define TK_INT_SCAN_COMPLETE                (TK_STATUS_SCIF_Msk)  /*!< Touch key scan complete interrupt */
#define TK_INT_SCAN_COMPLETE_TH_ALL         (0x1FFFF02UL)  /*!< Touch key scan complete or all touch keys threshold control interrupt */
#define TK_INT_SCAN_TH_ALL                  (0x1FFFF00UL)  /*!< ALL Touch key threshold control interrupt */
#define TK_INT_SCAN_TH_TK0                  (TK_STATUS_TKIF0_Msk)  /*!< Touch key 0 threshold control interrupt */
#define TK_INT_SCAN_TH_TK1                  (TK_STATUS_TKIF1_Msk)  /*!< Touch key 1 threshold control interrupt */
#define TK_INT_SCAN_TH_TK2                  (TK_STATUS_TKIF2_Msk)  /*!< Touch key 2 threshold control interrupt */
#define TK_INT_SCAN_TH_TK3                  (TK_STATUS_TKIF3_Msk)  /*!< Touch key 3 threshold control interrupt */
#define TK_INT_SCAN_TH_TK4                  (TK_STATUS_TKIF4_Msk)  /*!< Touch key 4 threshold control interrupt */
#define TK_INT_SCAN_TH_TK5                  (TK_STATUS_TKIF5_Msk)  /*!< Touch key 5 threshold control interrupt */
#define TK_INT_SCAN_TH_TK6                  (TK_STATUS_TKIF6_Msk)  /*!< Touch key 6 threshold control interrupt */
#define TK_INT_SCAN_TH_TK7                  (TK_STATUS_TKIF7_Msk)  /*!< Touch key 7 threshold control interrupt */
#define TK_INT_SCAN_TH_TK8                  (TK_STATUS_TKIF8_Msk)  /*!< Touch key 8 threshold control interrupt */
#define TK_INT_SCAN_TH_TK9                  (TK_STATUS_TKIF9_Msk)  /*!< Touch key 9 threshold control interrupt */
#define TK_INT_SCAN_TH_TK10                 (TK_STATUS_TKIF10_Msk)  /*!< Touch key 10 threshold control interrupt */
#define TK_INT_SCAN_TH_TK11                 (TK_STATUS_TKIF11_Msk)  /*!< Touch key 11 threshold control interrupt */
#define TK_INT_SCAN_TH_TK12                 (TK_STATUS_TKIF12_Msk)  /*!< Touch key 12 threshold control interrupt */
#define TK_INT_SCAN_TH_TK13                 (TK_STATUS_TKIF13_Msk)  /*!< Touch key 13 threshold control interrupt */
#define TK_INT_SCAN_TH_TK14                 (TK_STATUS_TKIF14_Msk)  /*!< Touch key 14 threshold control interrupt */
#define TK_INT_SCAN_TH_TK15                 (TK_STATUS_TKIF15_Msk)  /*!< Touch key 15 threshold control interrupt */
#define TK_INT_SCAN_TH_TK16                 (TK_STATUS_TKIF16_Msk)  /*!< Touch key 16 threshold control interrupt */


/*@}*/ /* end of group TK_EXPORTED_CONSTANTS */


/** @addtogroup TK_EXPORTED_FUNCTIONS TK Exported Functions
  @{
*/

/**
 * @brief Enable scan key(s)
 * @param[in] u32Mask Combination of enabled scan keys. Each bit corresponds to a touch key.
 *                           Bit 0 represents touch key 0, bit 1 represents touch key 1...
 * @return None
 * @note Touch key 16 is the default reference key, so touch key 16 is enabled.
 * \hideinitializer
 */
#define TK_ENABLE_SCAN_KEY(u32Mask) (TK->CTL |= (u32Mask))

/**
 * @brief Disable scan key(s)
 * @param[in] u32Mask Combination of disabled scan keys. Each bit corresponds to a touch key.
 *                           Bit 0 represents touch key 0, bit 1 represents touch key 1...
 * @return None
 * \hideinitializer
 */
#define TK_DISABLE_SCAN_KEY(u32Mask) (TK->CTL &= ~(u32Mask))

/**
 * @brief Enable reference key(s)
 * @param[in] u32Mask Combination of enabled reference keys. Each bit corresponds to a touch key.
 *                           Bit 0 represents touch key 0, bit 1 represents touch key 1...
 * @return None
 * @note Touch key 16 is the default reference key, so touch key 16 is enabled.
 * \hideinitializer
 */
#define TK_ENABLE_REF_KEY(u32Mask) (TK->REFCTL |= (u32Mask))

/**
 * @brief Disable reference key(s)
 * @param[in] u32Mask Combination of disabled reference keys. Each bit corresponds to a touch key.
 *                           Bit 0 represents touch key 0, bit 1 represents touch key 1...
 * @return None
 * @note It must enable a reference key and touch key 16 is the default reference key.
 *       If no any one touch key as reference key except touch key 16, then reference Touch key 16 can't be disable.
 * \hideinitializer
 */
#define TK_DISABLE_REF_KEY(u32Mask) (TK->REFCTL &= ~(u32Mask))

/**
 * @brief Initiate enabled key(s) scan immediately.
 * @param None
 * @return None
 * \hideinitializer
 */
#define TK_START_SCAN() (TK->CTL |= TK_CTL_SCAN_Msk)

/**
 * @brief Set touch key Sensing pulse width.
 * @param[in] u32PulseWidth Sensing pulse width.
 *              - \ref TK_SENSE_PULSE_1
 *              - \ref TK_SENSE_PULSE_2
 *              - \ref TK_SENSE_PULSE_4
 *              - \ref TK_SENSE_PULSE_8
 * @return None
 * \hideinitializer
 */
#define TK_SET_PULSE_WIDTH(u32PulseWidth) (TK->REFCTL = (TK->REFCTL & ~TK_REFCTL_SENPTCTL_Msk) | (u32PulseWidth))

/**
 * @brief Set touch key Sensing count.
 * @param[in] u32SenseCnt Sensing count.
 *              - \ref TK_SENSE_CNT_128
 *              - \ref TK_SENSE_CNT_255
 *              - \ref TK_SENSE_CNT_511
 *              - \ref TK_SENSE_CNT_1023
 * @return None
 * \hideinitializer
 */
#define TK_SET_SENSING_CNT(u32SenseCnt) (TK->REFCTL = (TK->REFCTL & ~TK_REFCTL_SENTCTL_Msk) | (u32SenseCnt))


/**
 * @brief Set touch key AVCCH voltage.
 * @param[in] u32AVCCHSel voltage selection.
 *              - \ref TK_AVCCH_1_DIV_16
 *              - \ref TK_AVCCH_1_DIV_8
 *              - \ref TK_AVCCH_3_DIV_16
 *              - \ref TK_AVCCH_1_DIV_4
 *              - \ref TK_AVCCH_5_DIV_16
 *              - \ref TK_AVCCH_3_DIV_8
 *              - \ref TK_AVCCH_7_DIV_16
 *              - \ref TK_AVCCH_1_DIV_2
 * @return None
 * \hideinitializer
 */
#define TK_SET_AVCCH(u32AVCCHSel) (TK->CTL = (TK->CTL & ~TK_CTL_AVCCHSEL_Msk) | (u32AVCCHSel))

/**
 * @brief Get touch key complement capacitor bank data.
 * @param[in] u32TKNum Touch key number. The valid value is 0~16.
 * @return Complement capacitor bank data
 * \hideinitializer
 */
#define TK_GET_COMP_CAP_BANK_DATA(u32TKNum) (((*(__IO uint32_t *) (&(TK->CCBDAT0) + ((u32TKNum) >> 2))) >> ((u32TKNum) % 4 * 8) & TK_CCBDAT0_CCBDAT0_Msk))

/**
 * @brief Get touch key sensing result data.
 * @param[in] u32TKNum Touch key number. The valid value is 0~16.
 * @return Sensing result data
 * \hideinitializer
 */
#define TK_GET_SENSE_DATA(u32TKNum) (((*(__IO uint32_t *) (&(TK->DAT0) + ((u32TKNum) >> 2))) >> ((u32TKNum) % 4 * 8) & TK_DAT0_TKDAT0_Msk))

/**
 * @brief Get touch key busy status.
 * @param None
 * @retval 0 Touch key is scan completed or stopped.
 * @retval 1 Touch key is busy.
 * \hideinitializer
 */
#define TK_IS_BUSY() ((TK->STATUS & TK_STATUS_BUSY_Msk) ? 1: 0)

/**
 * @brief Get touch key interrupt flag.
 * @param[in] u32Mask Interrupt flag type selection.
 *              - \ref TK_INT_SCAN_COMPLETE
 *              - \ref TK_INT_SCAN_COMPLETE_TH_ALL
 *              - \ref TK_INT_SCAN_TH_ALL
 *              - \ref TK_INT_SCAN_TH_TK0
 *              - \ref TK_INT_SCAN_TH_TK1
 *              - \ref TK_INT_SCAN_TH_TK2
 *              - \ref TK_INT_SCAN_TH_TK3
 *              - \ref TK_INT_SCAN_TH_TK4
 *              - \ref TK_INT_SCAN_TH_TK5
 *              - \ref TK_INT_SCAN_TH_TK6
 *              - \ref TK_INT_SCAN_TH_TK7
 *              - \ref TK_INT_SCAN_TH_TK8
 *              - \ref TK_INT_SCAN_TH_TK9
 *              - \ref TK_INT_SCAN_TH_TK10
 *              - \ref TK_INT_SCAN_TH_TK11
 *              - \ref TK_INT_SCAN_TH_TK12
 *              - \ref TK_INT_SCAN_TH_TK13
 *              - \ref TK_INT_SCAN_TH_TK14
 *              - \ref TK_INT_SCAN_TH_TK15
 *              - \ref TK_INT_SCAN_TH_TK16
 * @retval 0 Touch key has no interrupt.
 * @retval 1 Touch key is scan completed or threshold control event occurs.
 * \hideinitializer
 */
#define TK_GET_INT_STATUS(u32Mask) ((TK->STATUS & (u32Mask)) ? 1: 0)

/**
 * @brief Clear touch key interrupt flag.
 * @param[in] u32Mask Interrupt flag type selection.
 *              - \ref TK_INT_SCAN_COMPLETE
 *              - \ref TK_INT_SCAN_COMPLETE_TH_ALL
 *              - \ref TK_INT_SCAN_TH_ALL
 *              - \ref TK_INT_SCAN_TH_TK0
 *              - \ref TK_INT_SCAN_TH_TK1
 *              - \ref TK_INT_SCAN_TH_TK2
 *              - \ref TK_INT_SCAN_TH_TK3
 *              - \ref TK_INT_SCAN_TH_TK4
 *              - \ref TK_INT_SCAN_TH_TK5
 *              - \ref TK_INT_SCAN_TH_TK6
 *              - \ref TK_INT_SCAN_TH_TK7
 *              - \ref TK_INT_SCAN_TH_TK8
 *              - \ref TK_INT_SCAN_TH_TK9
 *              - \ref TK_INT_SCAN_TH_TK10
 *              - \ref TK_INT_SCAN_TH_TK11
 *              - \ref TK_INT_SCAN_TH_TK12
 *              - \ref TK_INT_SCAN_TH_TK13
 *              - \ref TK_INT_SCAN_TH_TK14
 *              - \ref TK_INT_SCAN_TH_TK15
 *              - \ref TK_INT_SCAN_TH_TK16
 * @return None
 * \hideinitializer
 */
#define TK_CLR_INT_FLAG(u32Mask) (TK->STATUS = (u32Mask))


/*---------------------------------------------------------------------------------------------------------*/
/* Define TK functions prototype                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
void TK_Open(void);
void TK_Close(void);
void TK_SetScanMode(uint32_t u32Mode);
void TK_ConfigSensitivity(uint32_t u32PulseWidth, uint32_t u32SenseCnt, uint32_t u32AVCCHSel);
void TK_SetCapBankPol(uint32_t u32CapBankPolSel);
void TK_EnableTkPolarity(uint32_t u32Mask);
void TK_DisableTkPolarity(uint32_t u32Mask);
void TK_SetCompCapBankData(uint32_t u32TKNum, uint32_t u32CapData);
void TK_SetTkPol(uint32_t u32Mask, uint32_t u32PolSel);
void TK_SetRefKeyCapBankData(uint32_t u32CapData);
void TK_SetScanThreshold(uint32_t u32TKNum, uint32_t u32HighLevel, uint32_t u32LowLevel);
void TK_EnableInt(uint32_t u32Msk);
void TK_DisableInt(uint32_t u32Msk);


/*@}*/ /* end of group TK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group TK_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif //__TK_H__

/*** (C) COPYRIGHT 2014~2015 Nuvoton Technology Corp. ***/
