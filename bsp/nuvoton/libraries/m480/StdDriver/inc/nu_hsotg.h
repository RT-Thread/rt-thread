/**************************************************************************//**
 * @file     nu_hsotg.h
 * @version  V0.10
 * @brief    M480 Series HSOTG Driver Header File
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __NU_HSOTG_H__
#define __NU_HSOTG_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup HSOTG_Driver HSOTG Driver
  @{
*/


/** @addtogroup HSOTG_EXPORTED_CONSTANTS HSOTG Exported Constants
  @{
*/



/*---------------------------------------------------------------------------------------------------------*/
/* HSOTG constant definitions                                                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define HSOTG_VBUS_EN_ACTIVE_HIGH      (0UL) /*!< USB VBUS power switch enable signal is active high. \hideinitializer */
#define HSOTG_VBUS_EN_ACTIVE_LOW       (1UL) /*!< USB VBUS power switch enable signal is active low. \hideinitializer */
#define HSOTG_VBUS_ST_VALID_HIGH       (0UL) /*!< USB VBUS power switch valid status is high. \hideinitializer */
#define HSOTG_VBUS_ST_VALID_LOW        (1UL) /*!< USB VBUS power switch valid status is low. \hideinitializer */


/*@}*/ /* end of group HSOTG_EXPORTED_CONSTANTS */


/** @addtogroup HSOTG_EXPORTED_FUNCTIONS HSOTG Exported Functions
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  Define Macros and functions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/


/**
  * @brief This macro is used to enable HSOTG function
  * @param None
  * @return None
  * @details This macro will set OTGEN bit of HSOTG_CTL register to enable HSOTG function.
  * \hideinitializer
  */
#define HSOTG_ENABLE() (HSOTG->CTL |= HSOTG_CTL_OTGEN_Msk)

/**
  * @brief This macro is used to disable HSOTG function
  * @param None
  * @return None
  * @details This macro will clear OTGEN bit of HSOTG_CTL register to disable HSOTG function.
  * \hideinitializer
  */
#define HSOTG_DISABLE() (HSOTG->CTL &= ~HSOTG_CTL_OTGEN_Msk)

/**
  * @brief This macro is used to enable USB PHY
  * @param None
  * @return None
  * @details When the USB role is selected as HSOTG device, use this macro to enable USB PHY.
  *          This macro will set OTGPHYEN bit of HSOTG_PHYCTL register to enable USB PHY.
  * \hideinitializer
  */
#define HSOTG_ENABLE_PHY() (HSOTG->PHYCTL |= HSOTG_PHYCTL_OTGPHYEN_Msk)

/**
  * @brief This macro is used to disable USB PHY
  * @param None
  * @return None
  * @details This macro will clear OTGPHYEN bit of HSOTG_PHYCTL register to disable USB PHY.
  * \hideinitializer
  */
#define HSOTG_DISABLE_PHY() (HSOTG->PHYCTL &= ~HSOTG_PHYCTL_OTGPHYEN_Msk)

/**
  * @brief This macro is used to enable ID detection function
  * @param None
  * @return None
  * @details This macro will set IDDETEN bit of HSOTG_PHYCTL register to enable ID detection function.
  * \hideinitializer
  */
#define HSOTG_ENABLE_ID_DETECT() (HSOTG->PHYCTL |= HSOTG_PHYCTL_IDDETEN_Msk)

/**
  * @brief This macro is used to disable ID detection function
  * @param None
  * @return None
  * @details This macro will clear IDDETEN bit of HSOTG_PHYCTL register to disable ID detection function.
  * \hideinitializer
  */
#define HSOTG_DISABLE_ID_DETECT() (HSOTG->PHYCTL &= ~HSOTG_PHYCTL_IDDETEN_Msk)

/**
  * @brief This macro is used to enable HSOTG wake-up function
  * @param None
  * @return None
  * @details This macro will set WKEN bit of HSOTG_CTL register to enable HSOTG wake-up function.
  * \hideinitializer
  */
#define HSOTG_ENABLE_WAKEUP() (HSOTG->CTL |= HSOTG_CTL_WKEN_Msk)

/**
  * @brief This macro is used to disable HSOTG wake-up function
  * @param None
  * @return None
  * @details This macro will clear WKEN bit of HSOTG_CTL register to disable HSOTG wake-up function.
  * \hideinitializer
  */
#define HSOTG_DISABLE_WAKEUP() (HSOTG->CTL &= ~HSOTG_CTL_WKEN_Msk)

/**
  * @brief This macro is used to set the polarity of USB_VBUS_EN pin
  * @param[in] u32Pol The polarity selection. Valid values are listed below.
  *                    - \ref HSOTG_VBUS_EN_ACTIVE_HIGH
  *                    - \ref HSOTG_VBUS_EN_ACTIVE_LOW
  * @return None
  * @details This macro is used to set the polarity of external USB VBUS power switch enable signal.
  * \hideinitializer
  */
#define HSOTG_SET_VBUS_EN_POL(u32Pol) (HSOTG->PHYCTL = (HSOTG->PHYCTL & (~HSOTG_PHYCTL_VBENPOL_Msk)) | ((u32Pol)<<HSOTG_PHYCTL_VBENPOL_Pos))

/**
  * @brief This macro is used to set the polarity of USB_VBUS_ST pin
  * @param[in] u32Pol The polarity selection. Valid values are listed below.
  *                    - \ref HSOTG_VBUS_ST_VALID_HIGH
  *                    - \ref HSOTG_VBUS_ST_VALID_LOW
  * @return None
  * @details This macro is used to set the polarity of external USB VBUS power switch status signal.
  * \hideinitializer
  */
#define HSOTG_SET_VBUS_STS_POL(u32Pol) (HSOTG->PHYCTL = (HSOTG->PHYCTL & (~HSOTG_PHYCTL_VBSTSPOL_Msk)) | ((u32Pol)<<HSOTG_PHYCTL_VBSTSPOL_Pos))

/**
  * @brief This macro is used to enable HSOTG related interrupts
  * @param[in] u32Mask The combination of interrupt source. Each bit corresponds to a interrupt source. Valid values are listed below.
  *                    - \ref HSOTG_INTEN_ROLECHGIEN_Msk
  *                    - \ref HSOTG_INTEN_VBEIEN_Msk
  *                    - \ref HSOTG_INTEN_SRPFIEN_Msk
  *                    - \ref HSOTG_INTEN_HNPFIEN_Msk
  *                    - \ref HSOTG_INTEN_GOIDLEIEN_Msk
  *                    - \ref HSOTG_INTEN_IDCHGIEN_Msk
  *                    - \ref HSOTG_INTEN_PDEVIEN_Msk
  *                    - \ref HSOTG_INTEN_HOSTIEN_Msk
  *                    - \ref HSOTG_INTEN_BVLDCHGIEN_Msk
  *                    - \ref HSOTG_INTEN_AVLDCHGIEN_Msk
  *                    - \ref HSOTG_INTEN_VBCHGIEN_Msk
  *                    - \ref HSOTG_INTEN_SECHGIEN_Msk
  *                    - \ref HSOTG_INTEN_SRPDETIEN_Msk
  * @return None
  * @details This macro will enable HSOTG related interrupts specified by u32Mask parameter.
  * \hideinitializer
  */
#define HSOTG_ENABLE_INT(u32Mask) (HSOTG->INTEN |= (u32Mask))

/**
  * @brief This macro is used to disable HSOTG related interrupts
  * @param[in] u32Mask The combination of interrupt source. Each bit corresponds to a interrupt source. Valid values are listed below.
  *                    - \ref HSOTG_INTEN_ROLECHGIEN_Msk
  *                    - \ref HSOTG_INTEN_VBEIEN_Msk
  *                    - \ref HSOTG_INTEN_SRPFIEN_Msk
  *                    - \ref HSOTG_INTEN_HNPFIEN_Msk
  *                    - \ref HSOTG_INTEN_GOIDLEIEN_Msk
  *                    - \ref HSOTG_INTEN_IDCHGIEN_Msk
  *                    - \ref HSOTG_INTEN_PDEVIEN_Msk
  *                    - \ref HSOTG_INTEN_HOSTIEN_Msk
  *                    - \ref HSOTG_INTEN_BVLDCHGIEN_Msk
  *                    - \ref HSOTG_INTEN_AVLDCHGIEN_Msk
  *                    - \ref HSOTG_INTEN_VBCHGIEN_Msk
  *                    - \ref HSOTG_INTEN_SECHGIEN_Msk
  *                    - \ref HSOTG_INTEN_SRPDETIEN_Msk
  * @return None
  * @details This macro will disable HSOTG related interrupts specified by u32Mask parameter.
  * \hideinitializer
  */
#define HSOTG_DISABLE_INT(u32Mask) (HSOTG->INTEN &= ~(u32Mask))

/**
  * @brief This macro is used to get HSOTG related interrupt flags
  * @param[in] u32Mask The combination of interrupt source. Each bit corresponds to a interrupt source. Valid values are listed below.
  *                    - \ref HSOTG_INTSTS_ROLECHGIF_Msk
  *                    - \ref HSOTG_INTSTS_VBEIF_Msk
  *                    - \ref HSOTG_INTSTS_SRPFIF_Msk
  *                    - \ref HSOTG_INTSTS_HNPFIF_Msk
  *                    - \ref HSOTG_INTSTS_GOIDLEIF_Msk
  *                    - \ref HSOTG_INTSTS_IDCHGIF_Msk
  *                    - \ref HSOTG_INTSTS_PDEVIF_Msk
  *                    - \ref HSOTG_INTSTS_HOSTIF_Msk
  *                    - \ref HSOTG_INTSTS_BVLDCHGIF_Msk
  *                    - \ref HSOTG_INTSTS_AVLDCHGIF_Msk
  *                    - \ref HSOTG_INTSTS_VBCHGIF_Msk
  *                    - \ref HSOTG_INTSTS_SECHGIF_Msk
  *                    - \ref HSOTG_INTSTS_SRPDETIF_Msk
  * @return Interrupt flags of selected sources.
  * @details This macro will return HSOTG related interrupt flags specified by u32Mask parameter.
  * \hideinitializer
  */
#define HSOTG_GET_INT_FLAG(u32Mask) (HSOTG->INTSTS & (u32Mask))

/**
  * @brief This macro is used to clear HSOTG related interrupt flags
  * @param[in] u32Mask The combination of interrupt source. Each bit corresponds to a interrupt source. Valid values are listed below.
  *                    - \ref HSOTG_INTSTS_ROLECHGIF_Msk
  *                    - \ref HSOTG_INTSTS_VBEIF_Msk
  *                    - \ref HSOTG_INTSTS_SRPFIF_Msk
  *                    - \ref HSOTG_INTSTS_HNPFIF_Msk
  *                    - \ref HSOTG_INTSTS_GOIDLEIF_Msk
  *                    - \ref HSOTG_INTSTS_IDCHGIF_Msk
  *                    - \ref HSOTG_INTSTS_PDEVIF_Msk
  *                    - \ref HSOTG_INTSTS_HOSTIF_Msk
  *                    - \ref HSOTG_INTSTS_BVLDCHGIF_Msk
  *                    - \ref HSOTG_INTSTS_AVLDCHGIF_Msk
  *                    - \ref HSOTG_INTSTS_VBCHGIF_Msk
  *                    - \ref HSOTG_INTSTS_SECHGIF_Msk
  *                    - \ref HSOTG_INTSTS_SRPDETIF_Msk
  * @return None
  * @details This macro will clear HSOTG related interrupt flags specified by u32Mask parameter.
  * \hideinitializer
  */
#define HSOTG_CLR_INT_FLAG(u32Mask) (HSOTG->INTSTS = (u32Mask))

/**
  * @brief This macro is used to get HSOTG related status
  * @param[in] u32Mask The combination of user specified source. Valid values are listed below.
  *                    - \ref HSOTG_STATUS_OVERCUR_Msk
  *                    - \ref HSOTG_STATUS_IDSTS_Msk
  *                    - \ref HSOTG_STATUS_SESSEND_Msk
  *                    - \ref HSOTG_STATUS_BVLD_Msk
  *                    - \ref HSOTG_STATUS_AVLD_Msk
  *                    - \ref HSOTG_STATUS_VBUSVLD_Msk
  * @return The user specified status.
  * @details This macro will return HSOTG related status specified by u32Mask parameter.
  * \hideinitializer
  */
#define HSOTG_GET_STATUS(u32Mask) (HSOTG->STATUS & (u32Mask))



/*@}*/ /* end of group HSOTG_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group HSOTG_Driver */

/*@}*/ /* end of group Standard_Driver */


#ifdef __cplusplus
}
#endif


#endif /* __NU_HSOTG_H__ */

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
