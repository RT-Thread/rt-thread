/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usb_config.h"
#include "stdint.h"
#include "usb_dwc2_reg.h"

/* you can find this config in function: USB_DevInit, file:stm32xxx_ll_usb.c, for example:
 *
 *  USBx->GCCFG |= USB_OTG_GCCFG_PWRDWN;
 *  USBx->GCCFG |= USB_OTG_GCCFG_NOVBUSSENS;
 *  USBx->GCCFG &= ~USB_OTG_GCCFG_VBUSBSEN;
 *  USBx->GCCFG &= ~USB_OTG_GCCFG_VBUSASEN;
 * 
*/

#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F730xx) || defined(STM32F732xx) || defined(STM32F733xx)
/**
  * @brief USB_HS_PHY_Registers
  */
typedef struct
{

__IO uint32_t USB_HS_PHYC_PLL;         /*!< This register is used to control the PLL of the HS PHY.                       000h */
__IO uint32_t Reserved04;              /*!< Reserved                                                                      004h */
__IO uint32_t Reserved08;              /*!< Reserved                                                                      008h */
__IO uint32_t USB_HS_PHYC_TUNE;        /*!< This register is used to control the tuning interface of the High Speed PHY.  00Ch */
__IO uint32_t Reserved10;              /*!< Reserved                                                                      010h */
__IO uint32_t Reserved14;              /*!< Reserved                                                                      014h */
__IO uint32_t USB_HS_PHYC_LDO;         /*!< This register is used to control the regulator (LDO).                         018h */
} USB_HS_PHYC_GlobalTypeDef;

#define USB_HS_PHYC_CONTROLLER_BASE          0x40017C00UL
#define USB_HS_PHYC         ((USB_HS_PHYC_GlobalTypeDef *) USB_HS_PHYC_CONTROLLER_BASE)

/********************  Bit definition for USBPHYC_PLL1 register  ********************/
#define USB_HS_PHYC_PLL1_PLLEN_Pos                (0U)
#define USB_HS_PHYC_PLL1_PLLEN_Msk                (0x1UL << USB_HS_PHYC_PLL1_PLLEN_Pos) /*!< 0x00000001 */
#define USB_HS_PHYC_PLL1_PLLEN                    USB_HS_PHYC_PLL1_PLLEN_Msk     /*!< Enable PLL */
#define USB_HS_PHYC_PLL1_PLLSEL_Pos               (1U)
#define USB_HS_PHYC_PLL1_PLLSEL_Msk               (0x7UL << USB_HS_PHYC_PLL1_PLLSEL_Pos) /*!< 0x0000000E */
#define USB_HS_PHYC_PLL1_PLLSEL                   USB_HS_PHYC_PLL1_PLLSEL_Msk    /*!< Controls PHY frequency operation selection */
#define USB_HS_PHYC_PLL1_PLLSEL_1                 (0x1UL << USB_HS_PHYC_PLL1_PLLSEL_Pos) /*!< 0x00000002 */
#define USB_HS_PHYC_PLL1_PLLSEL_2                 (0x2UL << USB_HS_PHYC_PLL1_PLLSEL_Pos) /*!< 0x00000004 */
#define USB_HS_PHYC_PLL1_PLLSEL_3                 (0x4UL << USB_HS_PHYC_PLL1_PLLSEL_Pos) /*!< 0x00000008 */

#define USB_HS_PHYC_PLL1_PLLSEL_12MHZ             0x00000000U                                                       /*!< PHY PLL1 input clock frequency 12 MHz   */
#define USB_HS_PHYC_PLL1_PLLSEL_12_5MHZ           USB_HS_PHYC_PLL1_PLLSEL_1                                         /*!< PHY PLL1 input clock frequency 12.5 MHz */
#define USB_HS_PHYC_PLL1_PLLSEL_16MHZ             (uint32_t)(USB_HS_PHYC_PLL1_PLLSEL_1 | USB_HS_PHYC_PLL1_PLLSEL_2) /*!< PHY PLL1 input clock frequency 16 MHz   */
#define USB_HS_PHYC_PLL1_PLLSEL_24MHZ             USB_HS_PHYC_PLL1_PLLSEL_3                                         /*!< PHY PLL1 input clock frequency 24 MHz   */
#define USB_HS_PHYC_PLL1_PLLSEL_25MHZ             (uint32_t)(USB_HS_PHYC_PLL1_PLLSEL_2 | USB_HS_PHYC_PLL1_PLLSEL_3) /*!< PHY PLL1 input clock frequency 25 MHz   */

/********************  Bit definition for USBPHYC_LDO register  ********************/
#define USB_HS_PHYC_LDO_USED_Pos                 (0U)
#define USB_HS_PHYC_LDO_USED_Msk                 (0x1UL << USB_HS_PHYC_LDO_USED_Pos) /*!< 0x00000001 */
#define USB_HS_PHYC_LDO_USED                     USB_HS_PHYC_LDO_USED_Msk      /*!< Monitors the usage status of the PHY's LDO   */
#define USB_HS_PHYC_LDO_STATUS_Pos               (1U)
#define USB_HS_PHYC_LDO_STATUS_Msk               (0x1UL << USB_HS_PHYC_LDO_STATUS_Pos) /*!< 0x00000002 */
#define USB_HS_PHYC_LDO_STATUS                   USB_HS_PHYC_LDO_STATUS_Msk    /*!< Monitors the status of the PHY's LDO.        */
#define USB_HS_PHYC_LDO_DISABLE_Pos              (2U)
#define USB_HS_PHYC_LDO_DISABLE_Msk              (0x1UL << USB_HS_PHYC_LDO_DISABLE_Pos) /*!< 0x00000004 */
#define USB_HS_PHYC_LDO_DISABLE                  USB_HS_PHYC_LDO_DISABLE_Msk    /*!< Controls disable of the High Speed PHY's LDO */

/* Legacy */
#define USB_HS_PHYC_PLL_PLLEN_Pos               USB_HS_PHYC_PLL1_PLLEN_Pos
#define USB_HS_PHYC_PLL_PLLEN_Msk               USB_HS_PHYC_PLL1_PLLEN_Msk
#define USB_HS_PHYC_PLL_PLLEN                   USB_HS_PHYC_PLL1_PLLEN
#define USB_HS_PHYC_PLL_PLLSEL_Pos              USB_HS_PHYC_PLL1_PLLSEL_Pos
#define USB_HS_PHYC_PLL_PLLSEL_Msk              USB_HS_PHYC_PLL1_PLLSEL_Msk
#define USB_HS_PHYC_PLL_PLLSEL                  USB_HS_PHYC_PLL1_PLLSEL
#define USB_HS_PHYC_PLL_PLLSEL_1                USB_HS_PHYC_PLL1_PLLSEL_1
#define USB_HS_PHYC_PLL_PLLSEL_2                USB_HS_PHYC_PLL1_PLLSEL_2
#define USB_HS_PHYC_PLL_PLLSEL_3                USB_HS_PHYC_PLL1_PLLSEL_3

#define USB_HS_PHYC_LDO_ENABLE_Pos               USB_HS_PHYC_LDO_DISABLE_Pos
#define USB_HS_PHYC_LDO_ENABLE_Msk               USB_HS_PHYC_LDO_DISABLE_Msk
#define USB_HS_PHYC_LDO_ENABLE                   USB_HS_PHYC_LDO_DISABLE

#if !defined  (USB_HS_PHYC_TUNE_VALUE)
#define USB_HS_PHYC_TUNE_VALUE        0x00000F13U /*!< Value of USB HS PHY Tune */
#endif /* USB_HS_PHYC_TUNE_VALUE */
/**
  * @brief  Enables control of a High Speed USB PHY
  *         Init the low level hardware : GPIO, CLOCK, NVIC...
  * @param  USBx  Selected device
  * @retval HAL status
  */
static int usb_hsphy_init(uint32_t hse_value)
{
  __IO uint32_t count = 0U;

  /* Enable LDO */
  USB_HS_PHYC->USB_HS_PHYC_LDO |= USB_HS_PHYC_LDO_ENABLE;

  /* wait for LDO Ready */
  while ((USB_HS_PHYC->USB_HS_PHYC_LDO & USB_HS_PHYC_LDO_STATUS) == 0U)
  {
    count++;

    if (count > 200000U)
    {
      return -1;
    }
  }

  /* Controls PHY frequency operation selection */
  if (hse_value == 12000000U) /* HSE = 12MHz */
  {
    USB_HS_PHYC->USB_HS_PHYC_PLL = (0x0U << 1);
  }
  else if (hse_value == 12500000U) /* HSE = 12.5MHz */
  {
    USB_HS_PHYC->USB_HS_PHYC_PLL = (0x2U << 1);
  }
  else if (hse_value == 16000000U) /* HSE = 16MHz */
  {
    USB_HS_PHYC->USB_HS_PHYC_PLL = (0x3U << 1);
  }
  else if (hse_value == 24000000U) /* HSE = 24MHz */
  {
    USB_HS_PHYC->USB_HS_PHYC_PLL = (0x4U << 1);
  }
  else if (hse_value == 25000000U) /* HSE = 25MHz */
  {
    USB_HS_PHYC->USB_HS_PHYC_PLL = (0x5U << 1);
  }
  else if (hse_value == 32000000U) /* HSE = 32MHz */
  {
    USB_HS_PHYC->USB_HS_PHYC_PLL = (0x7U << 1);
  }
  else
  {
    /* ... */
  }

  /* Control the tuning interface of the High Speed PHY */
  USB_HS_PHYC->USB_HS_PHYC_TUNE |= USB_HS_PHYC_TUNE_VALUE;

  /* Enable PLL internal PHY */
  USB_HS_PHYC->USB_HS_PHYC_PLL |= USB_HS_PHYC_PLL_PLLEN;


  /* 2ms Delay required to get internal phy clock stable */
  HAL_Delay(2U);

  return 0;
}

#endif

uint32_t usbd_get_dwc2_gccfg_conf(uint32_t reg_base)
{
#if __has_include("stm32h7xx.h") || __has_include("stm32f7xx.h") || __has_include("stm32l4xx.h")
#define USB_OTG_GLB ((DWC2_GlobalTypeDef *)(reg_base))
    /* B-peripheral session valid override enable */
    USB_OTG_GLB->GOTGCTL |= USB_OTG_GOTGCTL_BVALOEN;
    USB_OTG_GLB->GOTGCTL |= USB_OTG_GOTGCTL_BVALOVAL;
#endif

#ifdef CONFIG_USB_HS
#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F730xx) || defined(STM32F732xx) || defined(STM32F733xx)
    USB_OTG_GLB->GCCFG = (1 << 23);
    usb_hsphy_init(25000000U);
    return (1 << 23);    /* Enable USB HS PHY USBx->GCCFG |= USB_OTG_GCCFG_PHYHSEN;*/
#else
    return 0;
#endif
#else
#if __has_include("stm32h7xx.h") || __has_include("stm32f7xx.h") || __has_include("stm32l4xx.h")
    return (1 << 16);
#else
    return ((1 << 16) | (1 << 21));
#endif
#endif
}

uint32_t usbh_get_dwc2_gccfg_conf(uint32_t reg_base)
{
#if __has_include("stm32h7xx.h") || __has_include("stm32f7xx.h") || __has_include("stm32l4xx.h")
#define USB_OTG_GLB ((DWC2_GlobalTypeDef *)(reg_base))
    /* B-peripheral session valid override enable */
    USB_OTG_GLB->GOTGCTL &= ~USB_OTG_GOTGCTL_BVALOEN;
    USB_OTG_GLB->GOTGCTL &= ~USB_OTG_GOTGCTL_BVALOVAL;
#endif

#ifdef CONFIG_USB_HS
#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F730xx) || defined(STM32F732xx) || defined(STM32F733xx)
    USB_OTG_GLB->GCCFG = (1 << 23);
    usb_hsphy_init(25000000U);
    return (1 << 23); /* Enable USB HS PHY USBx->GCCFG |= USB_OTG_GCCFG_PHYHSEN;*/
#else
    return 0;
#endif
#else
#if __has_include("stm32h7xx.h") || __has_include("stm32f7xx.h") || __has_include("stm32l4xx.h")
    return (1 << 16);
#else
    return ((1 << 16) | (1 << 21));
#endif
#endif
}
