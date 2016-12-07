/**************************************************************************//**
 * @file     tk.c
 * @version  V1.00
 * $Revision: 6 $
 * $Date: 15/08/24 4:54p $
 * @brief    M451 series TK driver source file
 *
 * @note
 * Copyright (C) 2014~2015 Nuvoton Technology Corp. All rights reserved.
 *
*****************************************************************************/
#include "M451Series.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup TK_Driver TK Driver
  @{
*/


/** @addtogroup TK_EXPORTED_FUNCTIONS TK Exported Functions
  @{
*/


/**
 * @brief Enable touch key function
 * @param None
 * @return None
 * @note This function will enable touch key function and initial idle and polarity state as GND first for all scan keys
 * \hideinitializer
 */

void TK_Open(void)
{
    TK->CTL |= TK_CTL_TKEN_Msk;
    //set idle and polarity state as GND
    TK->IDLESEL = 0;
    TK->POLSEL = 0;
    TK->POLCTL &= ~(TK_POLCTL_IDLS16_Msk | TK_POLCTL_POLSEL16_Msk);
}

/**
 * @brief Disable touch key function
 * @param None
 * @return None
 * \hideinitializer
 */
void TK_Close(void)
{
    TK->CTL &= ~TK_CTL_TKEN_Msk;
}

/**
 * @brief Set touch key scan mode
 * @param[in] u32Mode Single ,periodic or all key scan mode
 *              - \ref TK_SCAN_MODE_SINGLE
 *              - \ref TK_SCAN_MODE_PERIODIC
 *              - \ref TK_SCAN_MODE_ALL_KEY
 *              - \ref TK_SCAN_MODE_PERIODIC_ALL_KEY
 * @return None
 * @details This function is used to set touch key scan mode.
 * @note If touch key controller sets as periodic mode, touch key will be trigger scan by Timer0. So Timer0 must be enabled and operated in periodic mode.
 *       If touch key controller sets as single scan mode, touch key can be trigger scan by calling TK_START_SCAN().
 * \hideinitializer
 */
void TK_SetScanMode(uint32_t u32Mode)
{
    TK->CTL &= ~TK_CTL_TMRTRGEN_Msk;
    TK->REFCTL &= ~TK_REFCTL_SCANALL_Msk;
    if(u32Mode == TK_SCAN_MODE_PERIODIC)
    {
        TK->CTL |= u32Mode;
    }
    else if(u32Mode == TK_SCAN_MODE_ALL_KEY)
    {
        TK->REFCTL |= u32Mode;
    }
    else if(u32Mode == TK_SCAN_MODE_PERIODIC_ALL_KEY)
    {
        TK->CTL |= TK_CTL_TMRTRGEN_Msk;
        TK->REFCTL |= TK_REFCTL_SCANALL_Msk;
    }
}

/**
 * @brief Configure touch key scan sensitivity
 * @param[in] u32PulseWidth Sensing pulse width
 *              - \ref TK_SENSE_PULSE_1
 *              - \ref TK_SENSE_PULSE_2
 *              - \ref TK_SENSE_PULSE_4
 *              - \ref TK_SENSE_PULSE_8
 * @param[in] u32SenseCnt Sensing count
 *              - \ref TK_SENSE_CNT_128
 *              - \ref TK_SENSE_CNT_255
 *              - \ref TK_SENSE_CNT_511
 *              - \ref TK_SENSE_CNT_1023
 * @param[in] u32AVCCHSel voltage selection
 *              - \ref TK_AVCCH_1_DIV_16
 *              - \ref TK_AVCCH_1_DIV_8
 *              - \ref TK_AVCCH_3_DIV_16
 *              - \ref TK_AVCCH_1_DIV_4
 *              - \ref TK_AVCCH_5_DIV_16
 *              - \ref TK_AVCCH_3_DIV_8
 *              - \ref TK_AVCCH_7_DIV_16
 *              - \ref TK_AVCCH_1_DIV_2
 * @return None
 * @details This function is used to configure touch key scan sensitivity.
 * \hideinitializer
 */
void TK_ConfigSensitivity(uint32_t u32PulseWidth, uint32_t u32SenseCnt, uint32_t u32AVCCHSel)
{
    TK->REFCTL = (TK->REFCTL & ~(TK_REFCTL_SENPTCTL_Msk | TK_REFCTL_SENTCTL_Msk)) | (u32PulseWidth | u32SenseCnt);
    TK->CTL = (TK->CTL & ~TK_CTL_AVCCHSEL_Msk) | u32AVCCHSel;
}

/**
 * @brief Set touch key capacitor bank polarity
 * @param[in] u32CapBankPolSel capacitor bank polarity selection
 *              - \ref TK_CAP_BANK_POL_SEL_GND
 *              - \ref TK_CAP_BANK_POL_SEL_AVCCH
 *              - \ref TK_CAP_BANK_POL_SEL_VDD
 * @return None
 * @details This function is used to set touch key capacitor bank polarity.
 * \hideinitializer
 */
void TK_SetCapBankPol(uint32_t u32CapBankPolSel)
{
    TK->POLCTL = (TK->POLCTL & ~TK_POLCTL_CBPOLSEL_Msk) | u32CapBankPolSel;
}

/**
 * @brief Configure touch key polarity
 * @param[in] u32Mask Combination of touch keys which need to be configured
 * @param[in] u32TKnPolSel touch key polarity selection
 *              - \ref TK_TKn_POL_SEL_GND
 *              - \ref TK_TKn_POL_SEL_AVCCH
 *              - \ref TK_TKn_POL_SEL_VDD
 * @return None
 * @details This function is used to configure touch key polarity.
 * \hideinitializer
 */
void TK_SetTkPol(uint32_t u32Mask, uint32_t u32PolSel)
{
    uint32_t i;

    if((1ul << 16) & u32Mask)
        TK->POLCTL = (TK->POLCTL & ~TK_POLCTL_POLSEL16_Msk) | (u32PolSel << TK_POLCTL_POLSEL16_Pos);

    for(i = 0 ; i < 16 ; i++)
    {
        if((1ul << i) & u32Mask)
            TK->POLSEL = (TK->POLSEL & ~(TK_POLSEL_POLSELn_Msk << (i*2))) | (u32PolSel << (i*2));
    }
}

/**
 * @brief Enable the polarity of specified touch key(s)
 * @param[in] u32Mask Combination of enabled scan keys. Each bit corresponds to a touch key
 *                           Bit 0 represents touch key 0, bit 1 represents touch key 1...
 * @return None
 * @details This function is used to enable the polarity of specified touch key(s).
 * \hideinitializer
 */
void TK_EnableTkPolarity(uint32_t u32Mask)
{
    TK->POLCTL |= (u32Mask << TK_POLCTL_POLEN0_Pos);
}

/**
 * @brief Disable the polarity of specified touch key(s)
 * @param[in] u32Mask Combination of enabled scan keys. Each bit corresponds to a touch key
 *                           Bit 0 represents touch key 0, bit 1 represents touch key 1...
 * @return None
 * @details This function is used to disable the polarity of specified touch key(s).
 * \hideinitializer
 */
void TK_DisableTkPolarity(uint32_t u32Mask)
{
    TK->POLCTL &= ~(u32Mask << TK_POLCTL_POLEN0_Pos);
}

/**
 * @brief Set complement capacitor bank data of specified touch key
 * @param[in] u32TKNum Touch key number. The valid value is 0~16.
 * @param[in] u32CapData Complement capacitor bank data. The valid value is 0~0xFF.
 * @return None
 * @details This function is used to set complement capacitor bank data of specified touch key.
 * \hideinitializer
 */
void TK_SetCompCapBankData(uint32_t u32TKNum, uint32_t u32CapData)
{
    *(__IO uint32_t *)(&(TK->CCBDAT0) + (u32TKNum >> 2)) &= ~(TK_CCBDAT0_CCBDAT0_Msk << (u32TKNum % 4 * 8));
    *(__IO uint32_t *)(&(TK->CCBDAT0) + (u32TKNum >> 2)) |= (u32CapData << (u32TKNum % 4 * 8));
}

/**
 * @brief Set complement capacitor bank data of reference touch key
 * @param[in] u32CapData Complement capacitor bank data. The valid value is 0~0xFF.
 * @return None
 * @details This function is used to set complement capacitor bank data of reference touch key.
 * \hideinitializer
 */
void TK_SetRefKeyCapBankData(uint32_t u32CapData)
{
    TK->CCBDAT4 = (TK->CCBDAT4 & ~TK_CCBDAT4_REFCBDAT_Msk) | (u32CapData << TK_CCBDAT4_REFCBDAT_Pos);
}

/**
 * @brief Set high and low threshold of specified touch key for threshold control interrupt
 * @param[in] u32TKNum Touch key number. The valid value is 0~16.
 * @param[in] u32HighLevel High level for touch key threshold control. The valid value is 0~0xFF.
 * @param[in] u32LowLevel Low level for touch key threshold control. The valid value is 0~0xFF.
 * @return None
 * @details This function is used to set high and low threshold of specified touch key for threshold control interrupt.
 * \hideinitializer
 */
void TK_SetScanThreshold(uint32_t u32TKNum, uint32_t u32HighLevel, uint32_t u32LowLevel)
{
    *(__IO uint32_t *)(&(TK->TH0_1) + (u32TKNum >> 1)) &= ~((TK_TH0_1_HTH0_Msk | TK_TH0_1_LTH0_Msk) << (u32TKNum % 2 * 16));
    *(__IO uint32_t *)(&(TK->TH0_1) + (u32TKNum >> 1)) |= ((u32HighLevel << TK_TH0_1_HTH0_Pos) | (u32LowLevel << TK_TH0_1_LTH0_Pos)) << (u32TKNum % 2 * 16);
}

/**
 * @brief Enable touch key scan interrupt
 * @param[in] u32Msk Interrupt type selection.
 *              - \ref TK_INT_EN_SCAN_COMPLETE
 *              - \ref TK_INT_EN_SCAN_COMPLETE_EDGE_TH
 *              - \ref TK_INT_EN_SCAN_COMPLETE_LEVEL_TH
 * @return None
 * @details This function is used to enable touch key scan interrupt.
 * @note It need disable the enabled interrupt type first by TK_DisableInt() before to change enabled interrupt type.
 * \hideinitializer
 */
void TK_EnableInt(uint32_t u32Msk)
{
    TK->INTEN |= u32Msk;
}

/**
 * @brief Disable touch key scan interrupt
 * @param[in] u32Msk Interrupt type selection.
 *              - \ref TK_INT_EN_SCAN_COMPLETE
 *              - \ref TK_INT_EN_SCAN_COMPLETE_EDGE_TH
 *              - \ref TK_INT_EN_SCAN_COMPLETE_LEVEL_TH
 * @return None
 * @details This function is used to disable touch key scan interrupt.
* @note It need disable the enabled interrupt type first by TK_DisableInt() before to change enabled interrupt type.
 * \hideinitializer
 */
void TK_DisableInt(uint32_t u32Msk)
{
    TK->INTEN &= ~u32Msk;
}


/*@}*/ /* end of group TK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group TK_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2014~2015 Nuvoton Technology Corp. ***/
