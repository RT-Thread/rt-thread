/**
 * \file
 *
 * \brief Component description for PM
 *
 * Copyright (c) 2019 Microchip Technology Inc.
 *
 * \license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \license_stop
 *
 */

/* file generated from device description version 2019-01-31T14:29:25Z */
#ifndef _SAML10_PM_COMPONENT_H_
#define _SAML10_PM_COMPONENT_H_
#define _SAML10_PM_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Power Manager
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR PM */
/* ========================================================================== */

#define PM_U2240                      /**< (PM) Module ID */
#define REV_PM 0x310                  /**< (PM) Module revision */

/* -------- PM_SLEEPCFG : (PM Offset: 0x01) (R/W 8) Sleep Configuration -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SLEEPMODE:3;               /**< bit:   0..2  Sleep Mode                               */
    uint8_t  :5;                        /**< bit:   3..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PM_SLEEPCFG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PM_SLEEPCFG_OFFSET                  (0x01)                                        /**<  (PM_SLEEPCFG) Sleep Configuration  Offset */
#define PM_SLEEPCFG_RESETVALUE              _U_(0x02)                                     /**<  (PM_SLEEPCFG) Sleep Configuration  Reset Value */

#define PM_SLEEPCFG_SLEEPMODE_Pos           0                                              /**< (PM_SLEEPCFG) Sleep Mode Position */
#define PM_SLEEPCFG_SLEEPMODE_Msk           (_U_(0x7) << PM_SLEEPCFG_SLEEPMODE_Pos)        /**< (PM_SLEEPCFG) Sleep Mode Mask */
#define PM_SLEEPCFG_SLEEPMODE(value)        (PM_SLEEPCFG_SLEEPMODE_Msk & ((value) << PM_SLEEPCFG_SLEEPMODE_Pos))
#define   PM_SLEEPCFG_SLEEPMODE_IDLE_Val    _U_(0x2)                                       /**< (PM_SLEEPCFG) CPU, AHB, APB clocks are OFF  */
#define   PM_SLEEPCFG_SLEEPMODE_STANDBY_Val _U_(0x4)                                       /**< (PM_SLEEPCFG) All Clocks are OFF  */
#define   PM_SLEEPCFG_SLEEPMODE_OFF_Val     _U_(0x6)                                       /**< (PM_SLEEPCFG) All power domains are powered OFF  */
#define PM_SLEEPCFG_SLEEPMODE_IDLE          (PM_SLEEPCFG_SLEEPMODE_IDLE_Val << PM_SLEEPCFG_SLEEPMODE_Pos)  /**< (PM_SLEEPCFG) CPU, AHB, APB clocks are OFF Position  */
#define PM_SLEEPCFG_SLEEPMODE_STANDBY       (PM_SLEEPCFG_SLEEPMODE_STANDBY_Val << PM_SLEEPCFG_SLEEPMODE_Pos)  /**< (PM_SLEEPCFG) All Clocks are OFF Position  */
#define PM_SLEEPCFG_SLEEPMODE_OFF           (PM_SLEEPCFG_SLEEPMODE_OFF_Val << PM_SLEEPCFG_SLEEPMODE_Pos)  /**< (PM_SLEEPCFG) All power domains are powered OFF Position  */
#define PM_SLEEPCFG_MASK                    _U_(0x07)                                      /**< \deprecated (PM_SLEEPCFG) Register MASK  (Use PM_SLEEPCFG_Msk instead)  */
#define PM_SLEEPCFG_Msk                     _U_(0x07)                                      /**< (PM_SLEEPCFG) Register Mask  */


/* -------- PM_PLCFG : (PM Offset: 0x02) (R/W 8) Performance Level Configuration -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PLSEL:2;                   /**< bit:   0..1  Performance Level Select                 */
    uint8_t  :5;                        /**< bit:   2..6  Reserved */
    uint8_t  PLDIS:1;                   /**< bit:      7  Performance Level Disable                */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PM_PLCFG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PM_PLCFG_OFFSET                     (0x02)                                        /**<  (PM_PLCFG) Performance Level Configuration  Offset */
#define PM_PLCFG_RESETVALUE                 _U_(0x00)                                     /**<  (PM_PLCFG) Performance Level Configuration  Reset Value */

#define PM_PLCFG_PLSEL_Pos                  0                                              /**< (PM_PLCFG) Performance Level Select Position */
#define PM_PLCFG_PLSEL_Msk                  (_U_(0x3) << PM_PLCFG_PLSEL_Pos)               /**< (PM_PLCFG) Performance Level Select Mask */
#define PM_PLCFG_PLSEL(value)               (PM_PLCFG_PLSEL_Msk & ((value) << PM_PLCFG_PLSEL_Pos))
#define   PM_PLCFG_PLSEL_PL0_Val            _U_(0x0)                                       /**< (PM_PLCFG) Performance Level 0  */
#define   PM_PLCFG_PLSEL_PL2_Val            _U_(0x2)                                       /**< (PM_PLCFG) Performance Level 2  */
#define PM_PLCFG_PLSEL_PL0                  (PM_PLCFG_PLSEL_PL0_Val << PM_PLCFG_PLSEL_Pos)  /**< (PM_PLCFG) Performance Level 0 Position  */
#define PM_PLCFG_PLSEL_PL2                  (PM_PLCFG_PLSEL_PL2_Val << PM_PLCFG_PLSEL_Pos)  /**< (PM_PLCFG) Performance Level 2 Position  */
#define PM_PLCFG_PLDIS_Pos                  7                                              /**< (PM_PLCFG) Performance Level Disable Position */
#define PM_PLCFG_PLDIS_Msk                  (_U_(0x1) << PM_PLCFG_PLDIS_Pos)               /**< (PM_PLCFG) Performance Level Disable Mask */
#define PM_PLCFG_PLDIS                      PM_PLCFG_PLDIS_Msk                             /**< \deprecated Old style mask definition for 1 bit bitfield. Use PM_PLCFG_PLDIS_Msk instead */
#define PM_PLCFG_MASK                       _U_(0x83)                                      /**< \deprecated (PM_PLCFG) Register MASK  (Use PM_PLCFG_Msk instead)  */
#define PM_PLCFG_Msk                        _U_(0x83)                                      /**< (PM_PLCFG) Register Mask  */


/* -------- PM_PWCFG : (PM Offset: 0x03) (R/W 8) Power Configuration -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RAMPSWC:2;                 /**< bit:   0..1  RAM Power Switch Configuration           */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PM_PWCFG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PM_PWCFG_OFFSET                     (0x03)                                        /**<  (PM_PWCFG) Power Configuration  Offset */
#define PM_PWCFG_RESETVALUE                 _U_(0x00)                                     /**<  (PM_PWCFG) Power Configuration  Reset Value */

#define PM_PWCFG_RAMPSWC_Pos                0                                              /**< (PM_PWCFG) RAM Power Switch Configuration Position */
#define PM_PWCFG_RAMPSWC_Msk                (_U_(0x3) << PM_PWCFG_RAMPSWC_Pos)             /**< (PM_PWCFG) RAM Power Switch Configuration Mask */
#define PM_PWCFG_RAMPSWC(value)             (PM_PWCFG_RAMPSWC_Msk & ((value) << PM_PWCFG_RAMPSWC_Pos))
#define   PM_PWCFG_RAMPSWC_16KB_Val         _U_(0x0)                                       /**< (PM_PWCFG) 16KB Available  */
#define   PM_PWCFG_RAMPSWC_12KB_Val         _U_(0x1)                                       /**< (PM_PWCFG) 12KB Available  */
#define   PM_PWCFG_RAMPSWC_8KB_Val          _U_(0x2)                                       /**< (PM_PWCFG) 8KB Available  */
#define   PM_PWCFG_RAMPSWC_4KB_Val          _U_(0x3)                                       /**< (PM_PWCFG) 4KB Available  */
#define PM_PWCFG_RAMPSWC_16KB               (PM_PWCFG_RAMPSWC_16KB_Val << PM_PWCFG_RAMPSWC_Pos)  /**< (PM_PWCFG) 16KB Available Position  */
#define PM_PWCFG_RAMPSWC_12KB               (PM_PWCFG_RAMPSWC_12KB_Val << PM_PWCFG_RAMPSWC_Pos)  /**< (PM_PWCFG) 12KB Available Position  */
#define PM_PWCFG_RAMPSWC_8KB                (PM_PWCFG_RAMPSWC_8KB_Val << PM_PWCFG_RAMPSWC_Pos)  /**< (PM_PWCFG) 8KB Available Position  */
#define PM_PWCFG_RAMPSWC_4KB                (PM_PWCFG_RAMPSWC_4KB_Val << PM_PWCFG_RAMPSWC_Pos)  /**< (PM_PWCFG) 4KB Available Position  */
#define PM_PWCFG_MASK                       _U_(0x03)                                      /**< \deprecated (PM_PWCFG) Register MASK  (Use PM_PWCFG_Msk instead)  */
#define PM_PWCFG_Msk                        _U_(0x03)                                      /**< (PM_PWCFG) Register Mask  */


/* -------- PM_INTENCLR : (PM Offset: 0x04) (R/W 8) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PLRDY:1;                   /**< bit:      0  Performance Level Interrupt Enable       */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PM_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PM_INTENCLR_OFFSET                  (0x04)                                        /**<  (PM_INTENCLR) Interrupt Enable Clear  Offset */
#define PM_INTENCLR_RESETVALUE              _U_(0x00)                                     /**<  (PM_INTENCLR) Interrupt Enable Clear  Reset Value */

#define PM_INTENCLR_PLRDY_Pos               0                                              /**< (PM_INTENCLR) Performance Level Interrupt Enable Position */
#define PM_INTENCLR_PLRDY_Msk               (_U_(0x1) << PM_INTENCLR_PLRDY_Pos)            /**< (PM_INTENCLR) Performance Level Interrupt Enable Mask */
#define PM_INTENCLR_PLRDY                   PM_INTENCLR_PLRDY_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PM_INTENCLR_PLRDY_Msk instead */
#define PM_INTENCLR_MASK                    _U_(0x01)                                      /**< \deprecated (PM_INTENCLR) Register MASK  (Use PM_INTENCLR_Msk instead)  */
#define PM_INTENCLR_Msk                     _U_(0x01)                                      /**< (PM_INTENCLR) Register Mask  */


/* -------- PM_INTENSET : (PM Offset: 0x05) (R/W 8) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PLRDY:1;                   /**< bit:      0  Performance Level Ready interrupt Enable */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PM_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PM_INTENSET_OFFSET                  (0x05)                                        /**<  (PM_INTENSET) Interrupt Enable Set  Offset */
#define PM_INTENSET_RESETVALUE              _U_(0x00)                                     /**<  (PM_INTENSET) Interrupt Enable Set  Reset Value */

#define PM_INTENSET_PLRDY_Pos               0                                              /**< (PM_INTENSET) Performance Level Ready interrupt Enable Position */
#define PM_INTENSET_PLRDY_Msk               (_U_(0x1) << PM_INTENSET_PLRDY_Pos)            /**< (PM_INTENSET) Performance Level Ready interrupt Enable Mask */
#define PM_INTENSET_PLRDY                   PM_INTENSET_PLRDY_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PM_INTENSET_PLRDY_Msk instead */
#define PM_INTENSET_MASK                    _U_(0x01)                                      /**< \deprecated (PM_INTENSET) Register MASK  (Use PM_INTENSET_Msk instead)  */
#define PM_INTENSET_Msk                     _U_(0x01)                                      /**< (PM_INTENSET) Register Mask  */


/* -------- PM_INTFLAG : (PM Offset: 0x06) (R/W 8) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t PLRDY:1;                   /**< bit:      0  Performance Level Ready                  */
    __I uint8_t :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PM_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PM_INTFLAG_OFFSET                   (0x06)                                        /**<  (PM_INTFLAG) Interrupt Flag Status and Clear  Offset */
#define PM_INTFLAG_RESETVALUE               _U_(0x00)                                     /**<  (PM_INTFLAG) Interrupt Flag Status and Clear  Reset Value */

#define PM_INTFLAG_PLRDY_Pos                0                                              /**< (PM_INTFLAG) Performance Level Ready Position */
#define PM_INTFLAG_PLRDY_Msk                (_U_(0x1) << PM_INTFLAG_PLRDY_Pos)             /**< (PM_INTFLAG) Performance Level Ready Mask */
#define PM_INTFLAG_PLRDY                    PM_INTFLAG_PLRDY_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PM_INTFLAG_PLRDY_Msk instead */
#define PM_INTFLAG_MASK                     _U_(0x01)                                      /**< \deprecated (PM_INTFLAG) Register MASK  (Use PM_INTFLAG_Msk instead)  */
#define PM_INTFLAG_Msk                      _U_(0x01)                                      /**< (PM_INTFLAG) Register Mask  */


/* -------- PM_STDBYCFG : (PM Offset: 0x08) (R/W 16) Standby Configuration -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t PDCFG:1;                   /**< bit:      0  Power Domain Configuration               */
    uint16_t :3;                        /**< bit:   1..3  Reserved */
    uint16_t DPGPDSW:1;                 /**< bit:      4  Dynamic Power Gating for PDSW            */
    uint16_t :1;                        /**< bit:      5  Reserved */
    uint16_t VREGSMOD:2;                /**< bit:   6..7  Voltage Regulator Standby mode           */
    uint16_t :2;                        /**< bit:   8..9  Reserved */
    uint16_t BBIASHS:1;                 /**< bit:     10  Back Bias for HSRAM                      */
    uint16_t :1;                        /**< bit:     11  Reserved */
    uint16_t BBIASTR:1;                 /**< bit:     12  Back Bias for Trust RAM                  */
    uint16_t :3;                        /**< bit: 13..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} PM_STDBYCFG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PM_STDBYCFG_OFFSET                  (0x08)                                        /**<  (PM_STDBYCFG) Standby Configuration  Offset */
#define PM_STDBYCFG_RESETVALUE              _U_(0x00)                                     /**<  (PM_STDBYCFG) Standby Configuration  Reset Value */

#define PM_STDBYCFG_PDCFG_Pos               0                                              /**< (PM_STDBYCFG) Power Domain Configuration Position */
#define PM_STDBYCFG_PDCFG_Msk               (_U_(0x1) << PM_STDBYCFG_PDCFG_Pos)            /**< (PM_STDBYCFG) Power Domain Configuration Mask */
#define PM_STDBYCFG_PDCFG                   PM_STDBYCFG_PDCFG_Msk                          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PM_STDBYCFG_PDCFG_Msk instead */
#define   PM_STDBYCFG_PDCFG_DEFAULT_Val     _U_(0x0)                                       /**< (PM_STDBYCFG) PDSW power domain switching is handled by hardware.  */
#define   PM_STDBYCFG_PDCFG_PDSW_Val        _U_(0x1)                                       /**< (PM_STDBYCFG) PDSW is forced ACTIVE.  */
#define PM_STDBYCFG_PDCFG_DEFAULT           (PM_STDBYCFG_PDCFG_DEFAULT_Val << PM_STDBYCFG_PDCFG_Pos)  /**< (PM_STDBYCFG) PDSW power domain switching is handled by hardware. Position  */
#define PM_STDBYCFG_PDCFG_PDSW              (PM_STDBYCFG_PDCFG_PDSW_Val << PM_STDBYCFG_PDCFG_Pos)  /**< (PM_STDBYCFG) PDSW is forced ACTIVE. Position  */
#define PM_STDBYCFG_DPGPDSW_Pos             4                                              /**< (PM_STDBYCFG) Dynamic Power Gating for PDSW Position */
#define PM_STDBYCFG_DPGPDSW_Msk             (_U_(0x1) << PM_STDBYCFG_DPGPDSW_Pos)          /**< (PM_STDBYCFG) Dynamic Power Gating for PDSW Mask */
#define PM_STDBYCFG_DPGPDSW                 PM_STDBYCFG_DPGPDSW_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PM_STDBYCFG_DPGPDSW_Msk instead */
#define   PM_STDBYCFG_DPGPDSW_0_Val         _U_(0x0)                                       /**< (PM_STDBYCFG) Dynamic Power Gating disabled  */
#define   PM_STDBYCFG_DPGPDSW_1_Val         _U_(0x1)                                       /**< (PM_STDBYCFG) Dynamic Power Gating enabled  */
#define PM_STDBYCFG_DPGPDSW_0               (PM_STDBYCFG_DPGPDSW_0_Val << PM_STDBYCFG_DPGPDSW_Pos)  /**< (PM_STDBYCFG) Dynamic Power Gating disabled Position  */
#define PM_STDBYCFG_DPGPDSW_1               (PM_STDBYCFG_DPGPDSW_1_Val << PM_STDBYCFG_DPGPDSW_Pos)  /**< (PM_STDBYCFG) Dynamic Power Gating enabled Position  */
#define PM_STDBYCFG_VREGSMOD_Pos            6                                              /**< (PM_STDBYCFG) Voltage Regulator Standby mode Position */
#define PM_STDBYCFG_VREGSMOD_Msk            (_U_(0x3) << PM_STDBYCFG_VREGSMOD_Pos)         /**< (PM_STDBYCFG) Voltage Regulator Standby mode Mask */
#define PM_STDBYCFG_VREGSMOD(value)         (PM_STDBYCFG_VREGSMOD_Msk & ((value) << PM_STDBYCFG_VREGSMOD_Pos))
#define   PM_STDBYCFG_VREGSMOD_AUTO_Val     _U_(0x0)                                       /**< (PM_STDBYCFG) Automatic mode  */
#define   PM_STDBYCFG_VREGSMOD_PERFORMANCE_Val _U_(0x1)                                       /**< (PM_STDBYCFG) Performance oriented  */
#define   PM_STDBYCFG_VREGSMOD_LP_Val       _U_(0x2)                                       /**< (PM_STDBYCFG) Low Power oriented  */
#define PM_STDBYCFG_VREGSMOD_AUTO           (PM_STDBYCFG_VREGSMOD_AUTO_Val << PM_STDBYCFG_VREGSMOD_Pos)  /**< (PM_STDBYCFG) Automatic mode Position  */
#define PM_STDBYCFG_VREGSMOD_PERFORMANCE    (PM_STDBYCFG_VREGSMOD_PERFORMANCE_Val << PM_STDBYCFG_VREGSMOD_Pos)  /**< (PM_STDBYCFG) Performance oriented Position  */
#define PM_STDBYCFG_VREGSMOD_LP             (PM_STDBYCFG_VREGSMOD_LP_Val << PM_STDBYCFG_VREGSMOD_Pos)  /**< (PM_STDBYCFG) Low Power oriented Position  */
#define PM_STDBYCFG_BBIASHS_Pos             10                                             /**< (PM_STDBYCFG) Back Bias for HSRAM Position */
#define PM_STDBYCFG_BBIASHS_Msk             (_U_(0x1) << PM_STDBYCFG_BBIASHS_Pos)          /**< (PM_STDBYCFG) Back Bias for HSRAM Mask */
#define PM_STDBYCFG_BBIASHS                 PM_STDBYCFG_BBIASHS_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PM_STDBYCFG_BBIASHS_Msk instead */
#define PM_STDBYCFG_BBIASTR_Pos             12                                             /**< (PM_STDBYCFG) Back Bias for Trust RAM Position */
#define PM_STDBYCFG_BBIASTR_Msk             (_U_(0x1) << PM_STDBYCFG_BBIASTR_Pos)          /**< (PM_STDBYCFG) Back Bias for Trust RAM Mask */
#define PM_STDBYCFG_BBIASTR                 PM_STDBYCFG_BBIASTR_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PM_STDBYCFG_BBIASTR_Msk instead */
#define PM_STDBYCFG_MASK                    _U_(0x14D1)                                    /**< \deprecated (PM_STDBYCFG) Register MASK  (Use PM_STDBYCFG_Msk instead)  */
#define PM_STDBYCFG_Msk                     _U_(0x14D1)                                    /**< (PM_STDBYCFG) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief PM hardware registers */
typedef struct {  /* Power Manager */
  __I  uint8_t                        Reserved1[1];
  __IO PM_SLEEPCFG_Type               SLEEPCFG;       /**< Offset: 0x01 (R/W   8) Sleep Configuration */
  __IO PM_PLCFG_Type                  PLCFG;          /**< Offset: 0x02 (R/W   8) Performance Level Configuration */
  __IO PM_PWCFG_Type                  PWCFG;          /**< Offset: 0x03 (R/W   8) Power Configuration */
  __IO PM_INTENCLR_Type               INTENCLR;       /**< Offset: 0x04 (R/W   8) Interrupt Enable Clear */
  __IO PM_INTENSET_Type               INTENSET;       /**< Offset: 0x05 (R/W   8) Interrupt Enable Set */
  __IO PM_INTFLAG_Type                INTFLAG;        /**< Offset: 0x06 (R/W   8) Interrupt Flag Status and Clear */
  __I  uint8_t                        Reserved2[1];
  __IO PM_STDBYCFG_Type               STDBYCFG;       /**< Offset: 0x08 (R/W  16) Standby Configuration */
} Pm;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Power Manager */

#endif /* _SAML10_PM_COMPONENT_H_ */
