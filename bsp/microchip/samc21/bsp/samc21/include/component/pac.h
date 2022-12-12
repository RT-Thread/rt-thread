/**
 * \file
 *
 * \brief Component description for PAC
 *
 * Copyright (c) 2018 Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#ifndef _SAMC21_PAC_COMPONENT_
#define _SAMC21_PAC_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR PAC */
/* ========================================================================== */
/** \addtogroup SAMC21_PAC Peripheral Access Controller */
/*@{*/

#define PAC_U2120
#define REV_PAC                     0x110

/* -------- PAC_WRCTRL : (PAC Offset: 0x00) (R/W 32) Write control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t PERID:16;         /*!< bit:  0..15  Peripheral identifier              */
    uint32_t KEY:8;            /*!< bit: 16..23  Peripheral access control key      */
    uint32_t :8;               /*!< bit: 24..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} PAC_WRCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_WRCTRL_OFFSET           0x00         /**< \brief (PAC_WRCTRL offset) Write control */
#define PAC_WRCTRL_RESETVALUE       _U_(0x00000000) /**< \brief (PAC_WRCTRL reset_value) Write control */

#define PAC_WRCTRL_PERID_Pos        0            /**< \brief (PAC_WRCTRL) Peripheral identifier */
#define PAC_WRCTRL_PERID_Msk        (_U_(0xFFFF) << PAC_WRCTRL_PERID_Pos)
#define PAC_WRCTRL_PERID(value)     (PAC_WRCTRL_PERID_Msk & ((value) << PAC_WRCTRL_PERID_Pos))
#define PAC_WRCTRL_KEY_Pos          16           /**< \brief (PAC_WRCTRL) Peripheral access control key */
#define PAC_WRCTRL_KEY_Msk          (_U_(0xFF) << PAC_WRCTRL_KEY_Pos)
#define PAC_WRCTRL_KEY(value)       (PAC_WRCTRL_KEY_Msk & ((value) << PAC_WRCTRL_KEY_Pos))
#define   PAC_WRCTRL_KEY_OFF_Val          _U_(0x0)   /**< \brief (PAC_WRCTRL) No action */
#define   PAC_WRCTRL_KEY_CLR_Val          _U_(0x1)   /**< \brief (PAC_WRCTRL) Clear protection */
#define   PAC_WRCTRL_KEY_SET_Val          _U_(0x2)   /**< \brief (PAC_WRCTRL) Set protection */
#define   PAC_WRCTRL_KEY_SETLCK_Val       _U_(0x3)   /**< \brief (PAC_WRCTRL) Set and lock protection */
#define PAC_WRCTRL_KEY_OFF          (PAC_WRCTRL_KEY_OFF_Val        << PAC_WRCTRL_KEY_Pos)
#define PAC_WRCTRL_KEY_CLR          (PAC_WRCTRL_KEY_CLR_Val        << PAC_WRCTRL_KEY_Pos)
#define PAC_WRCTRL_KEY_SET          (PAC_WRCTRL_KEY_SET_Val        << PAC_WRCTRL_KEY_Pos)
#define PAC_WRCTRL_KEY_SETLCK       (PAC_WRCTRL_KEY_SETLCK_Val     << PAC_WRCTRL_KEY_Pos)
#define PAC_WRCTRL_MASK             _U_(0x00FFFFFF) /**< \brief (PAC_WRCTRL) MASK Register */

/* -------- PAC_EVCTRL : (PAC Offset: 0x04) (R/W  8) Event control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  ERREO:1;          /*!< bit:      0  Peripheral acess error event output */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} PAC_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_EVCTRL_OFFSET           0x04         /**< \brief (PAC_EVCTRL offset) Event control */
#define PAC_EVCTRL_RESETVALUE       _U_(0x00)    /**< \brief (PAC_EVCTRL reset_value) Event control */

#define PAC_EVCTRL_ERREO_Pos        0            /**< \brief (PAC_EVCTRL) Peripheral acess error event output */
#define PAC_EVCTRL_ERREO            (_U_(0x1) << PAC_EVCTRL_ERREO_Pos)
#define PAC_EVCTRL_MASK             _U_(0x01)    /**< \brief (PAC_EVCTRL) MASK Register */

/* -------- PAC_INTENCLR : (PAC Offset: 0x08) (R/W  8) Interrupt enable clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  ERR:1;            /*!< bit:      0  Peripheral access error interrupt disable */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} PAC_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_INTENCLR_OFFSET         0x08         /**< \brief (PAC_INTENCLR offset) Interrupt enable clear */
#define PAC_INTENCLR_RESETVALUE     _U_(0x00)    /**< \brief (PAC_INTENCLR reset_value) Interrupt enable clear */

#define PAC_INTENCLR_ERR_Pos        0            /**< \brief (PAC_INTENCLR) Peripheral access error interrupt disable */
#define PAC_INTENCLR_ERR            (_U_(0x1) << PAC_INTENCLR_ERR_Pos)
#define PAC_INTENCLR_MASK           _U_(0x01)    /**< \brief (PAC_INTENCLR) MASK Register */

/* -------- PAC_INTENSET : (PAC Offset: 0x09) (R/W  8) Interrupt enable set -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  ERR:1;            /*!< bit:      0  Peripheral access error interrupt enable */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} PAC_INTENSET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_INTENSET_OFFSET         0x09         /**< \brief (PAC_INTENSET offset) Interrupt enable set */
#define PAC_INTENSET_RESETVALUE     _U_(0x00)    /**< \brief (PAC_INTENSET reset_value) Interrupt enable set */

#define PAC_INTENSET_ERR_Pos        0            /**< \brief (PAC_INTENSET) Peripheral access error interrupt enable */
#define PAC_INTENSET_ERR            (_U_(0x1) << PAC_INTENSET_ERR_Pos)
#define PAC_INTENSET_MASK           _U_(0x01)    /**< \brief (PAC_INTENSET) MASK Register */

/* -------- PAC_INTFLAGAHB : (PAC Offset: 0x10) (R/W 32) Bridge interrupt flag status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t FLASH_:1;         /*!< bit:      0  FLASH                              */
    __I uint32_t HSRAMCM0P_:1;     /*!< bit:      1  HSRAMCM0P                          */
    __I uint32_t HSRAMDSU_:1;      /*!< bit:      2  HSRAMDSU                           */
    __I uint32_t HPB1_:1;          /*!< bit:      3  HPB1                               */
    __I uint32_t HPB0_:1;          /*!< bit:      4  HPB0                               */
    __I uint32_t HPB2_:1;          /*!< bit:      5  HPB2                               */
    __I uint32_t LPRAMDMAC_:1;     /*!< bit:      6  LPRAMDMAC                          */
    __I uint32_t DIVAS_:1;         /*!< bit:      7  DIVAS                              */
    __I uint32_t :24;              /*!< bit:  8..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} PAC_INTFLAGAHB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_INTFLAGAHB_OFFSET       0x10         /**< \brief (PAC_INTFLAGAHB offset) Bridge interrupt flag status */
#define PAC_INTFLAGAHB_RESETVALUE   _U_(0x00000000) /**< \brief (PAC_INTFLAGAHB reset_value) Bridge interrupt flag status */

#define PAC_INTFLAGAHB_FLASH_Pos    0            /**< \brief (PAC_INTFLAGAHB) FLASH */
#define PAC_INTFLAGAHB_FLASH        (_U_(0x1) << PAC_INTFLAGAHB_FLASH_Pos)
#define PAC_INTFLAGAHB_HSRAMCM0P_Pos 1            /**< \brief (PAC_INTFLAGAHB) HSRAMCM0P */
#define PAC_INTFLAGAHB_HSRAMCM0P    (_U_(0x1) << PAC_INTFLAGAHB_HSRAMCM0P_Pos)
#define PAC_INTFLAGAHB_HSRAMDSU_Pos 2            /**< \brief (PAC_INTFLAGAHB) HSRAMDSU */
#define PAC_INTFLAGAHB_HSRAMDSU     (_U_(0x1) << PAC_INTFLAGAHB_HSRAMDSU_Pos)
#define PAC_INTFLAGAHB_HPB1_Pos     3            /**< \brief (PAC_INTFLAGAHB) HPB1 */
#define PAC_INTFLAGAHB_HPB1         (_U_(0x1) << PAC_INTFLAGAHB_HPB1_Pos)
#define PAC_INTFLAGAHB_HPB0_Pos     4            /**< \brief (PAC_INTFLAGAHB) HPB0 */
#define PAC_INTFLAGAHB_HPB0         (_U_(0x1) << PAC_INTFLAGAHB_HPB0_Pos)
#define PAC_INTFLAGAHB_HPB2_Pos     5            /**< \brief (PAC_INTFLAGAHB) HPB2 */
#define PAC_INTFLAGAHB_HPB2         (_U_(0x1) << PAC_INTFLAGAHB_HPB2_Pos)
#define PAC_INTFLAGAHB_LPRAMDMAC_Pos 6            /**< \brief (PAC_INTFLAGAHB) LPRAMDMAC */
#define PAC_INTFLAGAHB_LPRAMDMAC    (_U_(0x1) << PAC_INTFLAGAHB_LPRAMDMAC_Pos)
#define PAC_INTFLAGAHB_DIVAS_Pos    7            /**< \brief (PAC_INTFLAGAHB) DIVAS */
#define PAC_INTFLAGAHB_DIVAS        (_U_(0x1) << PAC_INTFLAGAHB_DIVAS_Pos)
#define PAC_INTFLAGAHB_MASK         _U_(0x000000FF) /**< \brief (PAC_INTFLAGAHB) MASK Register */

/* -------- PAC_INTFLAGA : (PAC Offset: 0x14) (R/W 32) Peripheral interrupt flag status - Bridge A -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t PAC_:1;           /*!< bit:      0  PAC                                */
    __I uint32_t PM_:1;            /*!< bit:      1  PM                                 */
    __I uint32_t MCLK_:1;          /*!< bit:      2  MCLK                               */
    __I uint32_t RSTC_:1;          /*!< bit:      3  RSTC                               */
    __I uint32_t OSCCTRL_:1;       /*!< bit:      4  OSCCTRL                            */
    __I uint32_t OSC32KCTRL_:1;    /*!< bit:      5  OSC32KCTRL                         */
    __I uint32_t SUPC_:1;          /*!< bit:      6  SUPC                               */
    __I uint32_t GCLK_:1;          /*!< bit:      7  GCLK                               */
    __I uint32_t WDT_:1;           /*!< bit:      8  WDT                                */
    __I uint32_t RTC_:1;           /*!< bit:      9  RTC                                */
    __I uint32_t EIC_:1;           /*!< bit:     10  EIC                                */
    __I uint32_t FREQM_:1;         /*!< bit:     11  FREQM                              */
    __I uint32_t TSENS_:1;         /*!< bit:     12  TSENS                              */
    __I uint32_t :19;              /*!< bit: 13..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} PAC_INTFLAGA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_INTFLAGA_OFFSET         0x14         /**< \brief (PAC_INTFLAGA offset) Peripheral interrupt flag status - Bridge A */
#define PAC_INTFLAGA_RESETVALUE     _U_(0x00000000) /**< \brief (PAC_INTFLAGA reset_value) Peripheral interrupt flag status - Bridge A */

#define PAC_INTFLAGA_PAC_Pos        0            /**< \brief (PAC_INTFLAGA) PAC */
#define PAC_INTFLAGA_PAC            (_U_(0x1) << PAC_INTFLAGA_PAC_Pos)
#define PAC_INTFLAGA_PM_Pos         1            /**< \brief (PAC_INTFLAGA) PM */
#define PAC_INTFLAGA_PM             (_U_(0x1) << PAC_INTFLAGA_PM_Pos)
#define PAC_INTFLAGA_MCLK_Pos       2            /**< \brief (PAC_INTFLAGA) MCLK */
#define PAC_INTFLAGA_MCLK           (_U_(0x1) << PAC_INTFLAGA_MCLK_Pos)
#define PAC_INTFLAGA_RSTC_Pos       3            /**< \brief (PAC_INTFLAGA) RSTC */
#define PAC_INTFLAGA_RSTC           (_U_(0x1) << PAC_INTFLAGA_RSTC_Pos)
#define PAC_INTFLAGA_OSCCTRL_Pos    4            /**< \brief (PAC_INTFLAGA) OSCCTRL */
#define PAC_INTFLAGA_OSCCTRL        (_U_(0x1) << PAC_INTFLAGA_OSCCTRL_Pos)
#define PAC_INTFLAGA_OSC32KCTRL_Pos 5            /**< \brief (PAC_INTFLAGA) OSC32KCTRL */
#define PAC_INTFLAGA_OSC32KCTRL     (_U_(0x1) << PAC_INTFLAGA_OSC32KCTRL_Pos)
#define PAC_INTFLAGA_SUPC_Pos       6            /**< \brief (PAC_INTFLAGA) SUPC */
#define PAC_INTFLAGA_SUPC           (_U_(0x1) << PAC_INTFLAGA_SUPC_Pos)
#define PAC_INTFLAGA_GCLK_Pos       7            /**< \brief (PAC_INTFLAGA) GCLK */
#define PAC_INTFLAGA_GCLK           (_U_(0x1) << PAC_INTFLAGA_GCLK_Pos)
#define PAC_INTFLAGA_WDT_Pos        8            /**< \brief (PAC_INTFLAGA) WDT */
#define PAC_INTFLAGA_WDT            (_U_(0x1) << PAC_INTFLAGA_WDT_Pos)
#define PAC_INTFLAGA_RTC_Pos        9            /**< \brief (PAC_INTFLAGA) RTC */
#define PAC_INTFLAGA_RTC            (_U_(0x1) << PAC_INTFLAGA_RTC_Pos)
#define PAC_INTFLAGA_EIC_Pos        10           /**< \brief (PAC_INTFLAGA) EIC */
#define PAC_INTFLAGA_EIC            (_U_(0x1) << PAC_INTFLAGA_EIC_Pos)
#define PAC_INTFLAGA_FREQM_Pos      11           /**< \brief (PAC_INTFLAGA) FREQM */
#define PAC_INTFLAGA_FREQM          (_U_(0x1) << PAC_INTFLAGA_FREQM_Pos)
#define PAC_INTFLAGA_TSENS_Pos      12           /**< \brief (PAC_INTFLAGA) TSENS */
#define PAC_INTFLAGA_TSENS          (_U_(0x1) << PAC_INTFLAGA_TSENS_Pos)
#define PAC_INTFLAGA_MASK           _U_(0x00001FFF) /**< \brief (PAC_INTFLAGA) MASK Register */

/* -------- PAC_INTFLAGB : (PAC Offset: 0x18) (R/W 32) Peripheral interrupt flag status - Bridge B -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t PORT_:1;          /*!< bit:      0  PORT                               */
    __I uint32_t DSU_:1;           /*!< bit:      1  DSU                                */
    __I uint32_t NVMCTRL_:1;       /*!< bit:      2  NVMCTRL                            */
    __I uint32_t DMAC_:1;          /*!< bit:      3  DMAC                               */
    __I uint32_t MTB_:1;           /*!< bit:      4  MTB                                */
    __I uint32_t HMATRIXHS_:1;     /*!< bit:      5  HMATRIXHS                          */
    __I uint32_t :26;              /*!< bit:  6..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} PAC_INTFLAGB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_INTFLAGB_OFFSET         0x18         /**< \brief (PAC_INTFLAGB offset) Peripheral interrupt flag status - Bridge B */
#define PAC_INTFLAGB_RESETVALUE     _U_(0x00000000) /**< \brief (PAC_INTFLAGB reset_value) Peripheral interrupt flag status - Bridge B */

#define PAC_INTFLAGB_PORT_Pos       0            /**< \brief (PAC_INTFLAGB) PORT */
#define PAC_INTFLAGB_PORT           (_U_(0x1) << PAC_INTFLAGB_PORT_Pos)
#define PAC_INTFLAGB_DSU_Pos        1            /**< \brief (PAC_INTFLAGB) DSU */
#define PAC_INTFLAGB_DSU            (_U_(0x1) << PAC_INTFLAGB_DSU_Pos)
#define PAC_INTFLAGB_NVMCTRL_Pos    2            /**< \brief (PAC_INTFLAGB) NVMCTRL */
#define PAC_INTFLAGB_NVMCTRL        (_U_(0x1) << PAC_INTFLAGB_NVMCTRL_Pos)
#define PAC_INTFLAGB_DMAC_Pos       3            /**< \brief (PAC_INTFLAGB) DMAC */
#define PAC_INTFLAGB_DMAC           (_U_(0x1) << PAC_INTFLAGB_DMAC_Pos)
#define PAC_INTFLAGB_MTB_Pos        4            /**< \brief (PAC_INTFLAGB) MTB */
#define PAC_INTFLAGB_MTB            (_U_(0x1) << PAC_INTFLAGB_MTB_Pos)
#define PAC_INTFLAGB_HMATRIXHS_Pos  5            /**< \brief (PAC_INTFLAGB) HMATRIXHS */
#define PAC_INTFLAGB_HMATRIXHS      (_U_(0x1) << PAC_INTFLAGB_HMATRIXHS_Pos)
#define PAC_INTFLAGB_MASK           _U_(0x0000003F) /**< \brief (PAC_INTFLAGB) MASK Register */

/* -------- PAC_INTFLAGC : (PAC Offset: 0x1C) (R/W 32) Peripheral interrupt flag status - Bridge C -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t EVSYS_:1;         /*!< bit:      0  EVSYS                              */
    __I uint32_t SERCOM0_:1;       /*!< bit:      1  SERCOM0                            */
    __I uint32_t SERCOM1_:1;       /*!< bit:      2  SERCOM1                            */
    __I uint32_t SERCOM2_:1;       /*!< bit:      3  SERCOM2                            */
    __I uint32_t SERCOM3_:1;       /*!< bit:      4  SERCOM3                            */
    __I uint32_t SERCOM4_:1;       /*!< bit:      5  SERCOM4                            */
    __I uint32_t SERCOM5_:1;       /*!< bit:      6  SERCOM5                            */
    __I uint32_t CAN0_:1;          /*!< bit:      7  CAN0                               */
    __I uint32_t CAN1_:1;          /*!< bit:      8  CAN1                               */
    __I uint32_t TCC0_:1;          /*!< bit:      9  TCC0                               */
    __I uint32_t TCC1_:1;          /*!< bit:     10  TCC1                               */
    __I uint32_t TCC2_:1;          /*!< bit:     11  TCC2                               */
    __I uint32_t TC0_:1;           /*!< bit:     12  TC0                                */
    __I uint32_t TC1_:1;           /*!< bit:     13  TC1                                */
    __I uint32_t TC2_:1;           /*!< bit:     14  TC2                                */
    __I uint32_t TC3_:1;           /*!< bit:     15  TC3                                */
    __I uint32_t TC4_:1;           /*!< bit:     16  TC4                                */
    __I uint32_t ADC0_:1;          /*!< bit:     17  ADC0                               */
    __I uint32_t ADC1_:1;          /*!< bit:     18  ADC1                               */
    __I uint32_t SDADC_:1;         /*!< bit:     19  SDADC                              */
    __I uint32_t AC_:1;            /*!< bit:     20  AC                                 */
    __I uint32_t DAC_:1;           /*!< bit:     21  DAC                                */
    __I uint32_t PTC_:1;           /*!< bit:     22  PTC                                */
    __I uint32_t CCL_:1;           /*!< bit:     23  CCL                                */
    __I uint32_t :8;               /*!< bit: 24..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} PAC_INTFLAGC_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_INTFLAGC_OFFSET         0x1C         /**< \brief (PAC_INTFLAGC offset) Peripheral interrupt flag status - Bridge C */
#define PAC_INTFLAGC_RESETVALUE     _U_(0x00000000) /**< \brief (PAC_INTFLAGC reset_value) Peripheral interrupt flag status - Bridge C */

#define PAC_INTFLAGC_EVSYS_Pos      0            /**< \brief (PAC_INTFLAGC) EVSYS */
#define PAC_INTFLAGC_EVSYS          (_U_(0x1) << PAC_INTFLAGC_EVSYS_Pos)
#define PAC_INTFLAGC_SERCOM0_Pos    1            /**< \brief (PAC_INTFLAGC) SERCOM0 */
#define PAC_INTFLAGC_SERCOM0        (_U_(0x1) << PAC_INTFLAGC_SERCOM0_Pos)
#define PAC_INTFLAGC_SERCOM1_Pos    2            /**< \brief (PAC_INTFLAGC) SERCOM1 */
#define PAC_INTFLAGC_SERCOM1        (_U_(0x1) << PAC_INTFLAGC_SERCOM1_Pos)
#define PAC_INTFLAGC_SERCOM2_Pos    3            /**< \brief (PAC_INTFLAGC) SERCOM2 */
#define PAC_INTFLAGC_SERCOM2        (_U_(0x1) << PAC_INTFLAGC_SERCOM2_Pos)
#define PAC_INTFLAGC_SERCOM3_Pos    4            /**< \brief (PAC_INTFLAGC) SERCOM3 */
#define PAC_INTFLAGC_SERCOM3        (_U_(0x1) << PAC_INTFLAGC_SERCOM3_Pos)
#define PAC_INTFLAGC_SERCOM4_Pos    5            /**< \brief (PAC_INTFLAGC) SERCOM4 */
#define PAC_INTFLAGC_SERCOM4        (_U_(0x1) << PAC_INTFLAGC_SERCOM4_Pos)
#define PAC_INTFLAGC_SERCOM5_Pos    6            /**< \brief (PAC_INTFLAGC) SERCOM5 */
#define PAC_INTFLAGC_SERCOM5        (_U_(0x1) << PAC_INTFLAGC_SERCOM5_Pos)
#define PAC_INTFLAGC_CAN0_Pos       7            /**< \brief (PAC_INTFLAGC) CAN0 */
#define PAC_INTFLAGC_CAN0           (_U_(0x1) << PAC_INTFLAGC_CAN0_Pos)
#define PAC_INTFLAGC_CAN1_Pos       8            /**< \brief (PAC_INTFLAGC) CAN1 */
#define PAC_INTFLAGC_CAN1           (_U_(0x1) << PAC_INTFLAGC_CAN1_Pos)
#define PAC_INTFLAGC_TCC0_Pos       9            /**< \brief (PAC_INTFLAGC) TCC0 */
#define PAC_INTFLAGC_TCC0           (_U_(0x1) << PAC_INTFLAGC_TCC0_Pos)
#define PAC_INTFLAGC_TCC1_Pos       10           /**< \brief (PAC_INTFLAGC) TCC1 */
#define PAC_INTFLAGC_TCC1           (_U_(0x1) << PAC_INTFLAGC_TCC1_Pos)
#define PAC_INTFLAGC_TCC2_Pos       11           /**< \brief (PAC_INTFLAGC) TCC2 */
#define PAC_INTFLAGC_TCC2           (_U_(0x1) << PAC_INTFLAGC_TCC2_Pos)
#define PAC_INTFLAGC_TC0_Pos        12           /**< \brief (PAC_INTFLAGC) TC0 */
#define PAC_INTFLAGC_TC0            (_U_(0x1) << PAC_INTFLAGC_TC0_Pos)
#define PAC_INTFLAGC_TC1_Pos        13           /**< \brief (PAC_INTFLAGC) TC1 */
#define PAC_INTFLAGC_TC1            (_U_(0x1) << PAC_INTFLAGC_TC1_Pos)
#define PAC_INTFLAGC_TC2_Pos        14           /**< \brief (PAC_INTFLAGC) TC2 */
#define PAC_INTFLAGC_TC2            (_U_(0x1) << PAC_INTFLAGC_TC2_Pos)
#define PAC_INTFLAGC_TC3_Pos        15           /**< \brief (PAC_INTFLAGC) TC3 */
#define PAC_INTFLAGC_TC3            (_U_(0x1) << PAC_INTFLAGC_TC3_Pos)
#define PAC_INTFLAGC_TC4_Pos        16           /**< \brief (PAC_INTFLAGC) TC4 */
#define PAC_INTFLAGC_TC4            (_U_(0x1) << PAC_INTFLAGC_TC4_Pos)
#define PAC_INTFLAGC_ADC0_Pos       17           /**< \brief (PAC_INTFLAGC) ADC0 */
#define PAC_INTFLAGC_ADC0           (_U_(0x1) << PAC_INTFLAGC_ADC0_Pos)
#define PAC_INTFLAGC_ADC1_Pos       18           /**< \brief (PAC_INTFLAGC) ADC1 */
#define PAC_INTFLAGC_ADC1           (_U_(0x1) << PAC_INTFLAGC_ADC1_Pos)
#define PAC_INTFLAGC_SDADC_Pos      19           /**< \brief (PAC_INTFLAGC) SDADC */
#define PAC_INTFLAGC_SDADC          (_U_(0x1) << PAC_INTFLAGC_SDADC_Pos)
#define PAC_INTFLAGC_AC_Pos         20           /**< \brief (PAC_INTFLAGC) AC */
#define PAC_INTFLAGC_AC             (_U_(0x1) << PAC_INTFLAGC_AC_Pos)
#define PAC_INTFLAGC_DAC_Pos        21           /**< \brief (PAC_INTFLAGC) DAC */
#define PAC_INTFLAGC_DAC            (_U_(0x1) << PAC_INTFLAGC_DAC_Pos)
#define PAC_INTFLAGC_PTC_Pos        22           /**< \brief (PAC_INTFLAGC) PTC */
#define PAC_INTFLAGC_PTC            (_U_(0x1) << PAC_INTFLAGC_PTC_Pos)
#define PAC_INTFLAGC_CCL_Pos        23           /**< \brief (PAC_INTFLAGC) CCL */
#define PAC_INTFLAGC_CCL            (_U_(0x1) << PAC_INTFLAGC_CCL_Pos)
#define PAC_INTFLAGC_MASK           _U_(0x00FFFFFF) /**< \brief (PAC_INTFLAGC) MASK Register */

/* -------- PAC_STATUSA : (PAC Offset: 0x34) (R/  32) Peripheral write protection status - Bridge A -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t PAC_:1;           /*!< bit:      0  PAC APB Protect Enable             */
    uint32_t PM_:1;            /*!< bit:      1  PM APB Protect Enable              */
    uint32_t MCLK_:1;          /*!< bit:      2  MCLK APB Protect Enable            */
    uint32_t RSTC_:1;          /*!< bit:      3  RSTC APB Protect Enable            */
    uint32_t OSCCTRL_:1;       /*!< bit:      4  OSCCTRL APB Protect Enable         */
    uint32_t OSC32KCTRL_:1;    /*!< bit:      5  OSC32KCTRL APB Protect Enable      */
    uint32_t SUPC_:1;          /*!< bit:      6  SUPC APB Protect Enable            */
    uint32_t GCLK_:1;          /*!< bit:      7  GCLK APB Protect Enable            */
    uint32_t WDT_:1;           /*!< bit:      8  WDT APB Protect Enable             */
    uint32_t RTC_:1;           /*!< bit:      9  RTC APB Protect Enable             */
    uint32_t EIC_:1;           /*!< bit:     10  EIC APB Protect Enable             */
    uint32_t FREQM_:1;         /*!< bit:     11  FREQM APB Protect Enable           */
    uint32_t TSENS_:1;         /*!< bit:     12  TSENS APB Protect Enable           */
    uint32_t :19;              /*!< bit: 13..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} PAC_STATUSA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_STATUSA_OFFSET          0x34         /**< \brief (PAC_STATUSA offset) Peripheral write protection status - Bridge A */
#define PAC_STATUSA_RESETVALUE      _U_(0x00000000) /**< \brief (PAC_STATUSA reset_value) Peripheral write protection status - Bridge A */

#define PAC_STATUSA_PAC_Pos         0            /**< \brief (PAC_STATUSA) PAC APB Protect Enable */
#define PAC_STATUSA_PAC             (_U_(0x1) << PAC_STATUSA_PAC_Pos)
#define PAC_STATUSA_PM_Pos          1            /**< \brief (PAC_STATUSA) PM APB Protect Enable */
#define PAC_STATUSA_PM              (_U_(0x1) << PAC_STATUSA_PM_Pos)
#define PAC_STATUSA_MCLK_Pos        2            /**< \brief (PAC_STATUSA) MCLK APB Protect Enable */
#define PAC_STATUSA_MCLK            (_U_(0x1) << PAC_STATUSA_MCLK_Pos)
#define PAC_STATUSA_RSTC_Pos        3            /**< \brief (PAC_STATUSA) RSTC APB Protect Enable */
#define PAC_STATUSA_RSTC            (_U_(0x1) << PAC_STATUSA_RSTC_Pos)
#define PAC_STATUSA_OSCCTRL_Pos     4            /**< \brief (PAC_STATUSA) OSCCTRL APB Protect Enable */
#define PAC_STATUSA_OSCCTRL         (_U_(0x1) << PAC_STATUSA_OSCCTRL_Pos)
#define PAC_STATUSA_OSC32KCTRL_Pos  5            /**< \brief (PAC_STATUSA) OSC32KCTRL APB Protect Enable */
#define PAC_STATUSA_OSC32KCTRL      (_U_(0x1) << PAC_STATUSA_OSC32KCTRL_Pos)
#define PAC_STATUSA_SUPC_Pos        6            /**< \brief (PAC_STATUSA) SUPC APB Protect Enable */
#define PAC_STATUSA_SUPC            (_U_(0x1) << PAC_STATUSA_SUPC_Pos)
#define PAC_STATUSA_GCLK_Pos        7            /**< \brief (PAC_STATUSA) GCLK APB Protect Enable */
#define PAC_STATUSA_GCLK            (_U_(0x1) << PAC_STATUSA_GCLK_Pos)
#define PAC_STATUSA_WDT_Pos         8            /**< \brief (PAC_STATUSA) WDT APB Protect Enable */
#define PAC_STATUSA_WDT             (_U_(0x1) << PAC_STATUSA_WDT_Pos)
#define PAC_STATUSA_RTC_Pos         9            /**< \brief (PAC_STATUSA) RTC APB Protect Enable */
#define PAC_STATUSA_RTC             (_U_(0x1) << PAC_STATUSA_RTC_Pos)
#define PAC_STATUSA_EIC_Pos         10           /**< \brief (PAC_STATUSA) EIC APB Protect Enable */
#define PAC_STATUSA_EIC             (_U_(0x1) << PAC_STATUSA_EIC_Pos)
#define PAC_STATUSA_FREQM_Pos       11           /**< \brief (PAC_STATUSA) FREQM APB Protect Enable */
#define PAC_STATUSA_FREQM           (_U_(0x1) << PAC_STATUSA_FREQM_Pos)
#define PAC_STATUSA_TSENS_Pos       12           /**< \brief (PAC_STATUSA) TSENS APB Protect Enable */
#define PAC_STATUSA_TSENS           (_U_(0x1) << PAC_STATUSA_TSENS_Pos)
#define PAC_STATUSA_MASK            _U_(0x00001FFF) /**< \brief (PAC_STATUSA) MASK Register */

/* -------- PAC_STATUSB : (PAC Offset: 0x38) (R/  32) Peripheral write protection status - Bridge B -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t PORT_:1;          /*!< bit:      0  PORT APB Protect Enable            */
    uint32_t DSU_:1;           /*!< bit:      1  DSU APB Protect Enable             */
    uint32_t NVMCTRL_:1;       /*!< bit:      2  NVMCTRL APB Protect Enable         */
    uint32_t DMAC_:1;          /*!< bit:      3  DMAC APB Protect Enable            */
    uint32_t MTB_:1;           /*!< bit:      4  MTB APB Protect Enable             */
    uint32_t HMATRIXHS_:1;     /*!< bit:      5  HMATRIXHS APB Protect Enable       */
    uint32_t :26;              /*!< bit:  6..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} PAC_STATUSB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_STATUSB_OFFSET          0x38         /**< \brief (PAC_STATUSB offset) Peripheral write protection status - Bridge B */
#define PAC_STATUSB_RESETVALUE      _U_(0x00000002) /**< \brief (PAC_STATUSB reset_value) Peripheral write protection status - Bridge B */

#define PAC_STATUSB_PORT_Pos        0            /**< \brief (PAC_STATUSB) PORT APB Protect Enable */
#define PAC_STATUSB_PORT            (_U_(0x1) << PAC_STATUSB_PORT_Pos)
#define PAC_STATUSB_DSU_Pos         1            /**< \brief (PAC_STATUSB) DSU APB Protect Enable */
#define PAC_STATUSB_DSU             (_U_(0x1) << PAC_STATUSB_DSU_Pos)
#define PAC_STATUSB_NVMCTRL_Pos     2            /**< \brief (PAC_STATUSB) NVMCTRL APB Protect Enable */
#define PAC_STATUSB_NVMCTRL         (_U_(0x1) << PAC_STATUSB_NVMCTRL_Pos)
#define PAC_STATUSB_DMAC_Pos        3            /**< \brief (PAC_STATUSB) DMAC APB Protect Enable */
#define PAC_STATUSB_DMAC            (_U_(0x1) << PAC_STATUSB_DMAC_Pos)
#define PAC_STATUSB_MTB_Pos         4            /**< \brief (PAC_STATUSB) MTB APB Protect Enable */
#define PAC_STATUSB_MTB             (_U_(0x1) << PAC_STATUSB_MTB_Pos)
#define PAC_STATUSB_HMATRIXHS_Pos   5            /**< \brief (PAC_STATUSB) HMATRIXHS APB Protect Enable */
#define PAC_STATUSB_HMATRIXHS       (_U_(0x1) << PAC_STATUSB_HMATRIXHS_Pos)
#define PAC_STATUSB_MASK            _U_(0x0000003F) /**< \brief (PAC_STATUSB) MASK Register */

/* -------- PAC_STATUSC : (PAC Offset: 0x3C) (R/  32) Peripheral write protection status - Bridge C -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t EVSYS_:1;         /*!< bit:      0  EVSYS APB Protect Enable           */
    uint32_t SERCOM0_:1;       /*!< bit:      1  SERCOM0 APB Protect Enable         */
    uint32_t SERCOM1_:1;       /*!< bit:      2  SERCOM1 APB Protect Enable         */
    uint32_t SERCOM2_:1;       /*!< bit:      3  SERCOM2 APB Protect Enable         */
    uint32_t SERCOM3_:1;       /*!< bit:      4  SERCOM3 APB Protect Enable         */
    uint32_t SERCOM4_:1;       /*!< bit:      5  SERCOM4 APB Protect Enable         */
    uint32_t SERCOM5_:1;       /*!< bit:      6  SERCOM5 APB Protect Enable         */
    uint32_t CAN0_:1;          /*!< bit:      7  CAN0 APB Protect Enable            */
    uint32_t CAN1_:1;          /*!< bit:      8  CAN1 APB Protect Enable            */
    uint32_t TCC0_:1;          /*!< bit:      9  TCC0 APB Protect Enable            */
    uint32_t TCC1_:1;          /*!< bit:     10  TCC1 APB Protect Enable            */
    uint32_t TCC2_:1;          /*!< bit:     11  TCC2 APB Protect Enable            */
    uint32_t TC0_:1;           /*!< bit:     12  TC0 APB Protect Enable             */
    uint32_t TC1_:1;           /*!< bit:     13  TC1 APB Protect Enable             */
    uint32_t TC2_:1;           /*!< bit:     14  TC2 APB Protect Enable             */
    uint32_t TC3_:1;           /*!< bit:     15  TC3 APB Protect Enable             */
    uint32_t TC4_:1;           /*!< bit:     16  TC4 APB Protect Enable             */
    uint32_t ADC0_:1;          /*!< bit:     17  ADC0 APB Protect Enable            */
    uint32_t ADC1_:1;          /*!< bit:     18  ADC1 APB Protect Enable            */
    uint32_t SDADC_:1;         /*!< bit:     19  SDADC APB Protect Enable           */
    uint32_t AC_:1;            /*!< bit:     20  AC APB Protect Enable              */
    uint32_t DAC_:1;           /*!< bit:     21  DAC APB Protect Enable             */
    uint32_t PTC_:1;           /*!< bit:     22  PTC APB Protect Enable             */
    uint32_t CCL_:1;           /*!< bit:     23  CCL APB Protect Enable             */
    uint32_t :8;               /*!< bit: 24..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} PAC_STATUSC_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PAC_STATUSC_OFFSET          0x3C         /**< \brief (PAC_STATUSC offset) Peripheral write protection status - Bridge C */
#define PAC_STATUSC_RESETVALUE      _U_(0x02000000) /**< \brief (PAC_STATUSC reset_value) Peripheral write protection status - Bridge C */

#define PAC_STATUSC_EVSYS_Pos       0            /**< \brief (PAC_STATUSC) EVSYS APB Protect Enable */
#define PAC_STATUSC_EVSYS           (_U_(0x1) << PAC_STATUSC_EVSYS_Pos)
#define PAC_STATUSC_SERCOM0_Pos     1            /**< \brief (PAC_STATUSC) SERCOM0 APB Protect Enable */
#define PAC_STATUSC_SERCOM0         (_U_(0x1) << PAC_STATUSC_SERCOM0_Pos)
#define PAC_STATUSC_SERCOM1_Pos     2            /**< \brief (PAC_STATUSC) SERCOM1 APB Protect Enable */
#define PAC_STATUSC_SERCOM1         (_U_(0x1) << PAC_STATUSC_SERCOM1_Pos)
#define PAC_STATUSC_SERCOM2_Pos     3            /**< \brief (PAC_STATUSC) SERCOM2 APB Protect Enable */
#define PAC_STATUSC_SERCOM2         (_U_(0x1) << PAC_STATUSC_SERCOM2_Pos)
#define PAC_STATUSC_SERCOM3_Pos     4            /**< \brief (PAC_STATUSC) SERCOM3 APB Protect Enable */
#define PAC_STATUSC_SERCOM3         (_U_(0x1) << PAC_STATUSC_SERCOM3_Pos)
#define PAC_STATUSC_SERCOM4_Pos     5            /**< \brief (PAC_STATUSC) SERCOM4 APB Protect Enable */
#define PAC_STATUSC_SERCOM4         (_U_(0x1) << PAC_STATUSC_SERCOM4_Pos)
#define PAC_STATUSC_SERCOM5_Pos     6            /**< \brief (PAC_STATUSC) SERCOM5 APB Protect Enable */
#define PAC_STATUSC_SERCOM5         (_U_(0x1) << PAC_STATUSC_SERCOM5_Pos)
#define PAC_STATUSC_CAN0_Pos        7            /**< \brief (PAC_STATUSC) CAN0 APB Protect Enable */
#define PAC_STATUSC_CAN0            (_U_(0x1) << PAC_STATUSC_CAN0_Pos)
#define PAC_STATUSC_CAN1_Pos        8            /**< \brief (PAC_STATUSC) CAN1 APB Protect Enable */
#define PAC_STATUSC_CAN1            (_U_(0x1) << PAC_STATUSC_CAN1_Pos)
#define PAC_STATUSC_TCC0_Pos        9            /**< \brief (PAC_STATUSC) TCC0 APB Protect Enable */
#define PAC_STATUSC_TCC0            (_U_(0x1) << PAC_STATUSC_TCC0_Pos)
#define PAC_STATUSC_TCC1_Pos        10           /**< \brief (PAC_STATUSC) TCC1 APB Protect Enable */
#define PAC_STATUSC_TCC1            (_U_(0x1) << PAC_STATUSC_TCC1_Pos)
#define PAC_STATUSC_TCC2_Pos        11           /**< \brief (PAC_STATUSC) TCC2 APB Protect Enable */
#define PAC_STATUSC_TCC2            (_U_(0x1) << PAC_STATUSC_TCC2_Pos)
#define PAC_STATUSC_TC0_Pos         12           /**< \brief (PAC_STATUSC) TC0 APB Protect Enable */
#define PAC_STATUSC_TC0             (_U_(0x1) << PAC_STATUSC_TC0_Pos)
#define PAC_STATUSC_TC1_Pos         13           /**< \brief (PAC_STATUSC) TC1 APB Protect Enable */
#define PAC_STATUSC_TC1             (_U_(0x1) << PAC_STATUSC_TC1_Pos)
#define PAC_STATUSC_TC2_Pos         14           /**< \brief (PAC_STATUSC) TC2 APB Protect Enable */
#define PAC_STATUSC_TC2             (_U_(0x1) << PAC_STATUSC_TC2_Pos)
#define PAC_STATUSC_TC3_Pos         15           /**< \brief (PAC_STATUSC) TC3 APB Protect Enable */
#define PAC_STATUSC_TC3             (_U_(0x1) << PAC_STATUSC_TC3_Pos)
#define PAC_STATUSC_TC4_Pos         16           /**< \brief (PAC_STATUSC) TC4 APB Protect Enable */
#define PAC_STATUSC_TC4             (_U_(0x1) << PAC_STATUSC_TC4_Pos)
#define PAC_STATUSC_ADC0_Pos        17           /**< \brief (PAC_STATUSC) ADC0 APB Protect Enable */
#define PAC_STATUSC_ADC0            (_U_(0x1) << PAC_STATUSC_ADC0_Pos)
#define PAC_STATUSC_ADC1_Pos        18           /**< \brief (PAC_STATUSC) ADC1 APB Protect Enable */
#define PAC_STATUSC_ADC1            (_U_(0x1) << PAC_STATUSC_ADC1_Pos)
#define PAC_STATUSC_SDADC_Pos       19           /**< \brief (PAC_STATUSC) SDADC APB Protect Enable */
#define PAC_STATUSC_SDADC           (_U_(0x1) << PAC_STATUSC_SDADC_Pos)
#define PAC_STATUSC_AC_Pos          20           /**< \brief (PAC_STATUSC) AC APB Protect Enable */
#define PAC_STATUSC_AC              (_U_(0x1) << PAC_STATUSC_AC_Pos)
#define PAC_STATUSC_DAC_Pos         21           /**< \brief (PAC_STATUSC) DAC APB Protect Enable */
#define PAC_STATUSC_DAC             (_U_(0x1) << PAC_STATUSC_DAC_Pos)
#define PAC_STATUSC_PTC_Pos         22           /**< \brief (PAC_STATUSC) PTC APB Protect Enable */
#define PAC_STATUSC_PTC             (_U_(0x1) << PAC_STATUSC_PTC_Pos)
#define PAC_STATUSC_CCL_Pos         23           /**< \brief (PAC_STATUSC) CCL APB Protect Enable */
#define PAC_STATUSC_CCL             (_U_(0x1) << PAC_STATUSC_CCL_Pos)
#define PAC_STATUSC_MASK            _U_(0x00FFFFFF) /**< \brief (PAC_STATUSC) MASK Register */

/** \brief PAC hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
  __IO PAC_WRCTRL_Type           WRCTRL;      /**< \brief Offset: 0x00 (R/W 32) Write control */
  __IO PAC_EVCTRL_Type           EVCTRL;      /**< \brief Offset: 0x04 (R/W  8) Event control */
       RoReg8                    Reserved1[0x3];
  __IO PAC_INTENCLR_Type         INTENCLR;    /**< \brief Offset: 0x08 (R/W  8) Interrupt enable clear */
  __IO PAC_INTENSET_Type         INTENSET;    /**< \brief Offset: 0x09 (R/W  8) Interrupt enable set */
       RoReg8                    Reserved2[0x6];
  __IO PAC_INTFLAGAHB_Type       INTFLAGAHB;  /**< \brief Offset: 0x10 (R/W 32) Bridge interrupt flag status */
  __IO PAC_INTFLAGA_Type         INTFLAGA;    /**< \brief Offset: 0x14 (R/W 32) Peripheral interrupt flag status - Bridge A */
  __IO PAC_INTFLAGB_Type         INTFLAGB;    /**< \brief Offset: 0x18 (R/W 32) Peripheral interrupt flag status - Bridge B */
  __IO PAC_INTFLAGC_Type         INTFLAGC;    /**< \brief Offset: 0x1C (R/W 32) Peripheral interrupt flag status - Bridge C */
       RoReg8                    Reserved3[0x14];
  __I  PAC_STATUSA_Type          STATUSA;     /**< \brief Offset: 0x34 (R/  32) Peripheral write protection status - Bridge A */
  __I  PAC_STATUSB_Type          STATUSB;     /**< \brief Offset: 0x38 (R/  32) Peripheral write protection status - Bridge B */
  __I  PAC_STATUSC_Type          STATUSC;     /**< \brief Offset: 0x3C (R/  32) Peripheral write protection status - Bridge C */
} Pac;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/*@}*/

#endif /* _SAMC21_PAC_COMPONENT_ */
