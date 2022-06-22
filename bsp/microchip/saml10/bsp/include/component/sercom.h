/**
 * \file
 *
 * \brief Component description for SERCOM
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
#ifndef _SAML10_SERCOM_COMPONENT_H_
#define _SAML10_SERCOM_COMPONENT_H_
#define _SAML10_SERCOM_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Serial Communication Interface
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR SERCOM */
/* ========================================================================== */

#define SERCOM_U2201                      /**< (SERCOM) Module ID */
#define REV_SERCOM 0x410                  /**< (SERCOM) Module revision */

/* -------- SERCOM_I2CM_CTRLA : (SERCOM Offset: 0x00) (R/W 32) I2CM Control A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint32_t MODE:3;                    /**< bit:   2..4  Operating Mode                           */
    uint32_t :2;                        /**< bit:   5..6  Reserved */
    uint32_t RUNSTDBY:1;                /**< bit:      7  Run in Standby                           */
    uint32_t :8;                        /**< bit:  8..15  Reserved */
    uint32_t PINOUT:1;                  /**< bit:     16  Pin Usage                                */
    uint32_t :3;                        /**< bit: 17..19  Reserved */
    uint32_t SDAHOLD:2;                 /**< bit: 20..21  SDA Hold Time                            */
    uint32_t MEXTTOEN:1;                /**< bit:     22  Master SCL Low Extend Timeout            */
    uint32_t SEXTTOEN:1;                /**< bit:     23  Slave SCL Low Extend Timeout             */
    uint32_t SPEED:2;                   /**< bit: 24..25  Transfer Speed                           */
    uint32_t :1;                        /**< bit:     26  Reserved */
    uint32_t SCLSM:1;                   /**< bit:     27  SCL Clock Stretch Mode                   */
    uint32_t INACTOUT:2;                /**< bit: 28..29  Inactive Time-Out                        */
    uint32_t LOWTOUTEN:1;               /**< bit:     30  SCL Low Timeout Enable                   */
    uint32_t :1;                        /**< bit:     31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_I2CM_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_CTRLA_OFFSET            (0x00)                                        /**<  (SERCOM_I2CM_CTRLA) I2CM Control A  Offset */
#define SERCOM_I2CM_CTRLA_RESETVALUE        _U_(0x00)                                     /**<  (SERCOM_I2CM_CTRLA) I2CM Control A  Reset Value */

#define SERCOM_I2CM_CTRLA_SWRST_Pos         0                                              /**< (SERCOM_I2CM_CTRLA) Software Reset Position */
#define SERCOM_I2CM_CTRLA_SWRST_Msk         (_U_(0x1) << SERCOM_I2CM_CTRLA_SWRST_Pos)      /**< (SERCOM_I2CM_CTRLA) Software Reset Mask */
#define SERCOM_I2CM_CTRLA_SWRST             SERCOM_I2CM_CTRLA_SWRST_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_CTRLA_SWRST_Msk instead */
#define SERCOM_I2CM_CTRLA_ENABLE_Pos        1                                              /**< (SERCOM_I2CM_CTRLA) Enable Position */
#define SERCOM_I2CM_CTRLA_ENABLE_Msk        (_U_(0x1) << SERCOM_I2CM_CTRLA_ENABLE_Pos)     /**< (SERCOM_I2CM_CTRLA) Enable Mask */
#define SERCOM_I2CM_CTRLA_ENABLE            SERCOM_I2CM_CTRLA_ENABLE_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_CTRLA_ENABLE_Msk instead */
#define SERCOM_I2CM_CTRLA_MODE_Pos          2                                              /**< (SERCOM_I2CM_CTRLA) Operating Mode Position */
#define SERCOM_I2CM_CTRLA_MODE_Msk          (_U_(0x7) << SERCOM_I2CM_CTRLA_MODE_Pos)       /**< (SERCOM_I2CM_CTRLA) Operating Mode Mask */
#define SERCOM_I2CM_CTRLA_MODE(value)       (SERCOM_I2CM_CTRLA_MODE_Msk & ((value) << SERCOM_I2CM_CTRLA_MODE_Pos))
#define SERCOM_I2CM_CTRLA_RUNSTDBY_Pos      7                                              /**< (SERCOM_I2CM_CTRLA) Run in Standby Position */
#define SERCOM_I2CM_CTRLA_RUNSTDBY_Msk      (_U_(0x1) << SERCOM_I2CM_CTRLA_RUNSTDBY_Pos)   /**< (SERCOM_I2CM_CTRLA) Run in Standby Mask */
#define SERCOM_I2CM_CTRLA_RUNSTDBY          SERCOM_I2CM_CTRLA_RUNSTDBY_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_CTRLA_RUNSTDBY_Msk instead */
#define SERCOM_I2CM_CTRLA_PINOUT_Pos        16                                             /**< (SERCOM_I2CM_CTRLA) Pin Usage Position */
#define SERCOM_I2CM_CTRLA_PINOUT_Msk        (_U_(0x1) << SERCOM_I2CM_CTRLA_PINOUT_Pos)     /**< (SERCOM_I2CM_CTRLA) Pin Usage Mask */
#define SERCOM_I2CM_CTRLA_PINOUT            SERCOM_I2CM_CTRLA_PINOUT_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_CTRLA_PINOUT_Msk instead */
#define SERCOM_I2CM_CTRLA_SDAHOLD_Pos       20                                             /**< (SERCOM_I2CM_CTRLA) SDA Hold Time Position */
#define SERCOM_I2CM_CTRLA_SDAHOLD_Msk       (_U_(0x3) << SERCOM_I2CM_CTRLA_SDAHOLD_Pos)    /**< (SERCOM_I2CM_CTRLA) SDA Hold Time Mask */
#define SERCOM_I2CM_CTRLA_SDAHOLD(value)    (SERCOM_I2CM_CTRLA_SDAHOLD_Msk & ((value) << SERCOM_I2CM_CTRLA_SDAHOLD_Pos))
#define SERCOM_I2CM_CTRLA_MEXTTOEN_Pos      22                                             /**< (SERCOM_I2CM_CTRLA) Master SCL Low Extend Timeout Position */
#define SERCOM_I2CM_CTRLA_MEXTTOEN_Msk      (_U_(0x1) << SERCOM_I2CM_CTRLA_MEXTTOEN_Pos)   /**< (SERCOM_I2CM_CTRLA) Master SCL Low Extend Timeout Mask */
#define SERCOM_I2CM_CTRLA_MEXTTOEN          SERCOM_I2CM_CTRLA_MEXTTOEN_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_CTRLA_MEXTTOEN_Msk instead */
#define SERCOM_I2CM_CTRLA_SEXTTOEN_Pos      23                                             /**< (SERCOM_I2CM_CTRLA) Slave SCL Low Extend Timeout Position */
#define SERCOM_I2CM_CTRLA_SEXTTOEN_Msk      (_U_(0x1) << SERCOM_I2CM_CTRLA_SEXTTOEN_Pos)   /**< (SERCOM_I2CM_CTRLA) Slave SCL Low Extend Timeout Mask */
#define SERCOM_I2CM_CTRLA_SEXTTOEN          SERCOM_I2CM_CTRLA_SEXTTOEN_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_CTRLA_SEXTTOEN_Msk instead */
#define SERCOM_I2CM_CTRLA_SPEED_Pos         24                                             /**< (SERCOM_I2CM_CTRLA) Transfer Speed Position */
#define SERCOM_I2CM_CTRLA_SPEED_Msk         (_U_(0x3) << SERCOM_I2CM_CTRLA_SPEED_Pos)      /**< (SERCOM_I2CM_CTRLA) Transfer Speed Mask */
#define SERCOM_I2CM_CTRLA_SPEED(value)      (SERCOM_I2CM_CTRLA_SPEED_Msk & ((value) << SERCOM_I2CM_CTRLA_SPEED_Pos))
#define SERCOM_I2CM_CTRLA_SCLSM_Pos         27                                             /**< (SERCOM_I2CM_CTRLA) SCL Clock Stretch Mode Position */
#define SERCOM_I2CM_CTRLA_SCLSM_Msk         (_U_(0x1) << SERCOM_I2CM_CTRLA_SCLSM_Pos)      /**< (SERCOM_I2CM_CTRLA) SCL Clock Stretch Mode Mask */
#define SERCOM_I2CM_CTRLA_SCLSM             SERCOM_I2CM_CTRLA_SCLSM_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_CTRLA_SCLSM_Msk instead */
#define SERCOM_I2CM_CTRLA_INACTOUT_Pos      28                                             /**< (SERCOM_I2CM_CTRLA) Inactive Time-Out Position */
#define SERCOM_I2CM_CTRLA_INACTOUT_Msk      (_U_(0x3) << SERCOM_I2CM_CTRLA_INACTOUT_Pos)   /**< (SERCOM_I2CM_CTRLA) Inactive Time-Out Mask */
#define SERCOM_I2CM_CTRLA_INACTOUT(value)   (SERCOM_I2CM_CTRLA_INACTOUT_Msk & ((value) << SERCOM_I2CM_CTRLA_INACTOUT_Pos))
#define SERCOM_I2CM_CTRLA_LOWTOUTEN_Pos     30                                             /**< (SERCOM_I2CM_CTRLA) SCL Low Timeout Enable Position */
#define SERCOM_I2CM_CTRLA_LOWTOUTEN_Msk     (_U_(0x1) << SERCOM_I2CM_CTRLA_LOWTOUTEN_Pos)  /**< (SERCOM_I2CM_CTRLA) SCL Low Timeout Enable Mask */
#define SERCOM_I2CM_CTRLA_LOWTOUTEN         SERCOM_I2CM_CTRLA_LOWTOUTEN_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_CTRLA_LOWTOUTEN_Msk instead */
#define SERCOM_I2CM_CTRLA_MASK              _U_(0x7BF1009F)                                /**< \deprecated (SERCOM_I2CM_CTRLA) Register MASK  (Use SERCOM_I2CM_CTRLA_Msk instead)  */
#define SERCOM_I2CM_CTRLA_Msk               _U_(0x7BF1009F)                                /**< (SERCOM_I2CM_CTRLA) Register Mask  */


/* -------- SERCOM_I2CS_CTRLA : (SERCOM Offset: 0x00) (R/W 32) I2CS Control A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint32_t MODE:3;                    /**< bit:   2..4  Operating Mode                           */
    uint32_t :2;                        /**< bit:   5..6  Reserved */
    uint32_t RUNSTDBY:1;                /**< bit:      7  Run during Standby                       */
    uint32_t :8;                        /**< bit:  8..15  Reserved */
    uint32_t PINOUT:1;                  /**< bit:     16  Pin Usage                                */
    uint32_t :3;                        /**< bit: 17..19  Reserved */
    uint32_t SDAHOLD:2;                 /**< bit: 20..21  SDA Hold Time                            */
    uint32_t :1;                        /**< bit:     22  Reserved */
    uint32_t SEXTTOEN:1;                /**< bit:     23  Slave SCL Low Extend Timeout             */
    uint32_t SPEED:2;                   /**< bit: 24..25  Transfer Speed                           */
    uint32_t :1;                        /**< bit:     26  Reserved */
    uint32_t SCLSM:1;                   /**< bit:     27  SCL Clock Stretch Mode                   */
    uint32_t :2;                        /**< bit: 28..29  Reserved */
    uint32_t LOWTOUTEN:1;               /**< bit:     30  SCL Low Timeout Enable                   */
    uint32_t :1;                        /**< bit:     31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_I2CS_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_CTRLA_OFFSET            (0x00)                                        /**<  (SERCOM_I2CS_CTRLA) I2CS Control A  Offset */
#define SERCOM_I2CS_CTRLA_RESETVALUE        _U_(0x00)                                     /**<  (SERCOM_I2CS_CTRLA) I2CS Control A  Reset Value */

#define SERCOM_I2CS_CTRLA_SWRST_Pos         0                                              /**< (SERCOM_I2CS_CTRLA) Software Reset Position */
#define SERCOM_I2CS_CTRLA_SWRST_Msk         (_U_(0x1) << SERCOM_I2CS_CTRLA_SWRST_Pos)      /**< (SERCOM_I2CS_CTRLA) Software Reset Mask */
#define SERCOM_I2CS_CTRLA_SWRST             SERCOM_I2CS_CTRLA_SWRST_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_CTRLA_SWRST_Msk instead */
#define SERCOM_I2CS_CTRLA_ENABLE_Pos        1                                              /**< (SERCOM_I2CS_CTRLA) Enable Position */
#define SERCOM_I2CS_CTRLA_ENABLE_Msk        (_U_(0x1) << SERCOM_I2CS_CTRLA_ENABLE_Pos)     /**< (SERCOM_I2CS_CTRLA) Enable Mask */
#define SERCOM_I2CS_CTRLA_ENABLE            SERCOM_I2CS_CTRLA_ENABLE_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_CTRLA_ENABLE_Msk instead */
#define SERCOM_I2CS_CTRLA_MODE_Pos          2                                              /**< (SERCOM_I2CS_CTRLA) Operating Mode Position */
#define SERCOM_I2CS_CTRLA_MODE_Msk          (_U_(0x7) << SERCOM_I2CS_CTRLA_MODE_Pos)       /**< (SERCOM_I2CS_CTRLA) Operating Mode Mask */
#define SERCOM_I2CS_CTRLA_MODE(value)       (SERCOM_I2CS_CTRLA_MODE_Msk & ((value) << SERCOM_I2CS_CTRLA_MODE_Pos))
#define SERCOM_I2CS_CTRLA_RUNSTDBY_Pos      7                                              /**< (SERCOM_I2CS_CTRLA) Run during Standby Position */
#define SERCOM_I2CS_CTRLA_RUNSTDBY_Msk      (_U_(0x1) << SERCOM_I2CS_CTRLA_RUNSTDBY_Pos)   /**< (SERCOM_I2CS_CTRLA) Run during Standby Mask */
#define SERCOM_I2CS_CTRLA_RUNSTDBY          SERCOM_I2CS_CTRLA_RUNSTDBY_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_CTRLA_RUNSTDBY_Msk instead */
#define SERCOM_I2CS_CTRLA_PINOUT_Pos        16                                             /**< (SERCOM_I2CS_CTRLA) Pin Usage Position */
#define SERCOM_I2CS_CTRLA_PINOUT_Msk        (_U_(0x1) << SERCOM_I2CS_CTRLA_PINOUT_Pos)     /**< (SERCOM_I2CS_CTRLA) Pin Usage Mask */
#define SERCOM_I2CS_CTRLA_PINOUT            SERCOM_I2CS_CTRLA_PINOUT_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_CTRLA_PINOUT_Msk instead */
#define SERCOM_I2CS_CTRLA_SDAHOLD_Pos       20                                             /**< (SERCOM_I2CS_CTRLA) SDA Hold Time Position */
#define SERCOM_I2CS_CTRLA_SDAHOLD_Msk       (_U_(0x3) << SERCOM_I2CS_CTRLA_SDAHOLD_Pos)    /**< (SERCOM_I2CS_CTRLA) SDA Hold Time Mask */
#define SERCOM_I2CS_CTRLA_SDAHOLD(value)    (SERCOM_I2CS_CTRLA_SDAHOLD_Msk & ((value) << SERCOM_I2CS_CTRLA_SDAHOLD_Pos))
#define SERCOM_I2CS_CTRLA_SEXTTOEN_Pos      23                                             /**< (SERCOM_I2CS_CTRLA) Slave SCL Low Extend Timeout Position */
#define SERCOM_I2CS_CTRLA_SEXTTOEN_Msk      (_U_(0x1) << SERCOM_I2CS_CTRLA_SEXTTOEN_Pos)   /**< (SERCOM_I2CS_CTRLA) Slave SCL Low Extend Timeout Mask */
#define SERCOM_I2CS_CTRLA_SEXTTOEN          SERCOM_I2CS_CTRLA_SEXTTOEN_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_CTRLA_SEXTTOEN_Msk instead */
#define SERCOM_I2CS_CTRLA_SPEED_Pos         24                                             /**< (SERCOM_I2CS_CTRLA) Transfer Speed Position */
#define SERCOM_I2CS_CTRLA_SPEED_Msk         (_U_(0x3) << SERCOM_I2CS_CTRLA_SPEED_Pos)      /**< (SERCOM_I2CS_CTRLA) Transfer Speed Mask */
#define SERCOM_I2CS_CTRLA_SPEED(value)      (SERCOM_I2CS_CTRLA_SPEED_Msk & ((value) << SERCOM_I2CS_CTRLA_SPEED_Pos))
#define SERCOM_I2CS_CTRLA_SCLSM_Pos         27                                             /**< (SERCOM_I2CS_CTRLA) SCL Clock Stretch Mode Position */
#define SERCOM_I2CS_CTRLA_SCLSM_Msk         (_U_(0x1) << SERCOM_I2CS_CTRLA_SCLSM_Pos)      /**< (SERCOM_I2CS_CTRLA) SCL Clock Stretch Mode Mask */
#define SERCOM_I2CS_CTRLA_SCLSM             SERCOM_I2CS_CTRLA_SCLSM_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_CTRLA_SCLSM_Msk instead */
#define SERCOM_I2CS_CTRLA_LOWTOUTEN_Pos     30                                             /**< (SERCOM_I2CS_CTRLA) SCL Low Timeout Enable Position */
#define SERCOM_I2CS_CTRLA_LOWTOUTEN_Msk     (_U_(0x1) << SERCOM_I2CS_CTRLA_LOWTOUTEN_Pos)  /**< (SERCOM_I2CS_CTRLA) SCL Low Timeout Enable Mask */
#define SERCOM_I2CS_CTRLA_LOWTOUTEN         SERCOM_I2CS_CTRLA_LOWTOUTEN_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_CTRLA_LOWTOUTEN_Msk instead */
#define SERCOM_I2CS_CTRLA_MASK              _U_(0x4BB1009F)                                /**< \deprecated (SERCOM_I2CS_CTRLA) Register MASK  (Use SERCOM_I2CS_CTRLA_Msk instead)  */
#define SERCOM_I2CS_CTRLA_Msk               _U_(0x4BB1009F)                                /**< (SERCOM_I2CS_CTRLA) Register Mask  */


/* -------- SERCOM_SPI_CTRLA : (SERCOM Offset: 0x00) (R/W 32) SPI Control A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint32_t MODE:3;                    /**< bit:   2..4  Operating Mode                           */
    uint32_t :2;                        /**< bit:   5..6  Reserved */
    uint32_t RUNSTDBY:1;                /**< bit:      7  Run during Standby                       */
    uint32_t IBON:1;                    /**< bit:      8  Immediate Buffer Overflow Notification   */
    uint32_t :7;                        /**< bit:  9..15  Reserved */
    uint32_t DOPO:2;                    /**< bit: 16..17  Data Out Pinout                          */
    uint32_t :2;                        /**< bit: 18..19  Reserved */
    uint32_t DIPO:2;                    /**< bit: 20..21  Data In Pinout                           */
    uint32_t :2;                        /**< bit: 22..23  Reserved */
    uint32_t FORM:4;                    /**< bit: 24..27  Frame Format                             */
    uint32_t CPHA:1;                    /**< bit:     28  Clock Phase                              */
    uint32_t CPOL:1;                    /**< bit:     29  Clock Polarity                           */
    uint32_t DORD:1;                    /**< bit:     30  Data Order                               */
    uint32_t :1;                        /**< bit:     31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_SPI_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_CTRLA_OFFSET             (0x00)                                        /**<  (SERCOM_SPI_CTRLA) SPI Control A  Offset */
#define SERCOM_SPI_CTRLA_RESETVALUE         _U_(0x00)                                     /**<  (SERCOM_SPI_CTRLA) SPI Control A  Reset Value */

#define SERCOM_SPI_CTRLA_SWRST_Pos          0                                              /**< (SERCOM_SPI_CTRLA) Software Reset Position */
#define SERCOM_SPI_CTRLA_SWRST_Msk          (_U_(0x1) << SERCOM_SPI_CTRLA_SWRST_Pos)       /**< (SERCOM_SPI_CTRLA) Software Reset Mask */
#define SERCOM_SPI_CTRLA_SWRST              SERCOM_SPI_CTRLA_SWRST_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_CTRLA_SWRST_Msk instead */
#define SERCOM_SPI_CTRLA_ENABLE_Pos         1                                              /**< (SERCOM_SPI_CTRLA) Enable Position */
#define SERCOM_SPI_CTRLA_ENABLE_Msk         (_U_(0x1) << SERCOM_SPI_CTRLA_ENABLE_Pos)      /**< (SERCOM_SPI_CTRLA) Enable Mask */
#define SERCOM_SPI_CTRLA_ENABLE             SERCOM_SPI_CTRLA_ENABLE_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_CTRLA_ENABLE_Msk instead */
#define SERCOM_SPI_CTRLA_MODE_Pos           2                                              /**< (SERCOM_SPI_CTRLA) Operating Mode Position */
#define SERCOM_SPI_CTRLA_MODE_Msk           (_U_(0x7) << SERCOM_SPI_CTRLA_MODE_Pos)        /**< (SERCOM_SPI_CTRLA) Operating Mode Mask */
#define SERCOM_SPI_CTRLA_MODE(value)        (SERCOM_SPI_CTRLA_MODE_Msk & ((value) << SERCOM_SPI_CTRLA_MODE_Pos))
#define SERCOM_SPI_CTRLA_RUNSTDBY_Pos       7                                              /**< (SERCOM_SPI_CTRLA) Run during Standby Position */
#define SERCOM_SPI_CTRLA_RUNSTDBY_Msk       (_U_(0x1) << SERCOM_SPI_CTRLA_RUNSTDBY_Pos)    /**< (SERCOM_SPI_CTRLA) Run during Standby Mask */
#define SERCOM_SPI_CTRLA_RUNSTDBY           SERCOM_SPI_CTRLA_RUNSTDBY_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_CTRLA_RUNSTDBY_Msk instead */
#define SERCOM_SPI_CTRLA_IBON_Pos           8                                              /**< (SERCOM_SPI_CTRLA) Immediate Buffer Overflow Notification Position */
#define SERCOM_SPI_CTRLA_IBON_Msk           (_U_(0x1) << SERCOM_SPI_CTRLA_IBON_Pos)        /**< (SERCOM_SPI_CTRLA) Immediate Buffer Overflow Notification Mask */
#define SERCOM_SPI_CTRLA_IBON               SERCOM_SPI_CTRLA_IBON_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_CTRLA_IBON_Msk instead */
#define SERCOM_SPI_CTRLA_DOPO_Pos           16                                             /**< (SERCOM_SPI_CTRLA) Data Out Pinout Position */
#define SERCOM_SPI_CTRLA_DOPO_Msk           (_U_(0x3) << SERCOM_SPI_CTRLA_DOPO_Pos)        /**< (SERCOM_SPI_CTRLA) Data Out Pinout Mask */
#define SERCOM_SPI_CTRLA_DOPO(value)        (SERCOM_SPI_CTRLA_DOPO_Msk & ((value) << SERCOM_SPI_CTRLA_DOPO_Pos))
#define SERCOM_SPI_CTRLA_DIPO_Pos           20                                             /**< (SERCOM_SPI_CTRLA) Data In Pinout Position */
#define SERCOM_SPI_CTRLA_DIPO_Msk           (_U_(0x3) << SERCOM_SPI_CTRLA_DIPO_Pos)        /**< (SERCOM_SPI_CTRLA) Data In Pinout Mask */
#define SERCOM_SPI_CTRLA_DIPO(value)        (SERCOM_SPI_CTRLA_DIPO_Msk & ((value) << SERCOM_SPI_CTRLA_DIPO_Pos))
#define SERCOM_SPI_CTRLA_FORM_Pos           24                                             /**< (SERCOM_SPI_CTRLA) Frame Format Position */
#define SERCOM_SPI_CTRLA_FORM_Msk           (_U_(0xF) << SERCOM_SPI_CTRLA_FORM_Pos)        /**< (SERCOM_SPI_CTRLA) Frame Format Mask */
#define SERCOM_SPI_CTRLA_FORM(value)        (SERCOM_SPI_CTRLA_FORM_Msk & ((value) << SERCOM_SPI_CTRLA_FORM_Pos))
#define SERCOM_SPI_CTRLA_CPHA_Pos           28                                             /**< (SERCOM_SPI_CTRLA) Clock Phase Position */
#define SERCOM_SPI_CTRLA_CPHA_Msk           (_U_(0x1) << SERCOM_SPI_CTRLA_CPHA_Pos)        /**< (SERCOM_SPI_CTRLA) Clock Phase Mask */
#define SERCOM_SPI_CTRLA_CPHA               SERCOM_SPI_CTRLA_CPHA_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_CTRLA_CPHA_Msk instead */
#define SERCOM_SPI_CTRLA_CPOL_Pos           29                                             /**< (SERCOM_SPI_CTRLA) Clock Polarity Position */
#define SERCOM_SPI_CTRLA_CPOL_Msk           (_U_(0x1) << SERCOM_SPI_CTRLA_CPOL_Pos)        /**< (SERCOM_SPI_CTRLA) Clock Polarity Mask */
#define SERCOM_SPI_CTRLA_CPOL               SERCOM_SPI_CTRLA_CPOL_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_CTRLA_CPOL_Msk instead */
#define SERCOM_SPI_CTRLA_DORD_Pos           30                                             /**< (SERCOM_SPI_CTRLA) Data Order Position */
#define SERCOM_SPI_CTRLA_DORD_Msk           (_U_(0x1) << SERCOM_SPI_CTRLA_DORD_Pos)        /**< (SERCOM_SPI_CTRLA) Data Order Mask */
#define SERCOM_SPI_CTRLA_DORD               SERCOM_SPI_CTRLA_DORD_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_CTRLA_DORD_Msk instead */
#define SERCOM_SPI_CTRLA_MASK               _U_(0x7F33019F)                                /**< \deprecated (SERCOM_SPI_CTRLA) Register MASK  (Use SERCOM_SPI_CTRLA_Msk instead)  */
#define SERCOM_SPI_CTRLA_Msk                _U_(0x7F33019F)                                /**< (SERCOM_SPI_CTRLA) Register Mask  */


/* -------- SERCOM_USART_CTRLA : (SERCOM Offset: 0x00) (R/W 32) USART Control A -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset                           */
    uint32_t ENABLE:1;                  /**< bit:      1  Enable                                   */
    uint32_t MODE:3;                    /**< bit:   2..4  Operating Mode                           */
    uint32_t :2;                        /**< bit:   5..6  Reserved */
    uint32_t RUNSTDBY:1;                /**< bit:      7  Run during Standby                       */
    uint32_t IBON:1;                    /**< bit:      8  Immediate Buffer Overflow Notification   */
    uint32_t TXINV:1;                   /**< bit:      9  Transmit Data Invert                     */
    uint32_t RXINV:1;                   /**< bit:     10  Receive Data Invert                      */
    uint32_t :2;                        /**< bit: 11..12  Reserved */
    uint32_t SAMPR:3;                   /**< bit: 13..15  Sample                                   */
    uint32_t TXPO:2;                    /**< bit: 16..17  Transmit Data Pinout                     */
    uint32_t :2;                        /**< bit: 18..19  Reserved */
    uint32_t RXPO:2;                    /**< bit: 20..21  Receive Data Pinout                      */
    uint32_t SAMPA:2;                   /**< bit: 22..23  Sample Adjustment                        */
    uint32_t FORM:4;                    /**< bit: 24..27  Frame Format                             */
    uint32_t CMODE:1;                   /**< bit:     28  Communication Mode                       */
    uint32_t CPOL:1;                    /**< bit:     29  Clock Polarity                           */
    uint32_t DORD:1;                    /**< bit:     30  Data Order                               */
    uint32_t :1;                        /**< bit:     31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_USART_CTRLA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_CTRLA_OFFSET           (0x00)                                        /**<  (SERCOM_USART_CTRLA) USART Control A  Offset */
#define SERCOM_USART_CTRLA_RESETVALUE       _U_(0x00)                                     /**<  (SERCOM_USART_CTRLA) USART Control A  Reset Value */

#define SERCOM_USART_CTRLA_SWRST_Pos        0                                              /**< (SERCOM_USART_CTRLA) Software Reset Position */
#define SERCOM_USART_CTRLA_SWRST_Msk        (_U_(0x1) << SERCOM_USART_CTRLA_SWRST_Pos)     /**< (SERCOM_USART_CTRLA) Software Reset Mask */
#define SERCOM_USART_CTRLA_SWRST            SERCOM_USART_CTRLA_SWRST_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLA_SWRST_Msk instead */
#define SERCOM_USART_CTRLA_ENABLE_Pos       1                                              /**< (SERCOM_USART_CTRLA) Enable Position */
#define SERCOM_USART_CTRLA_ENABLE_Msk       (_U_(0x1) << SERCOM_USART_CTRLA_ENABLE_Pos)    /**< (SERCOM_USART_CTRLA) Enable Mask */
#define SERCOM_USART_CTRLA_ENABLE           SERCOM_USART_CTRLA_ENABLE_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLA_ENABLE_Msk instead */
#define SERCOM_USART_CTRLA_MODE_Pos         2                                              /**< (SERCOM_USART_CTRLA) Operating Mode Position */
#define SERCOM_USART_CTRLA_MODE_Msk         (_U_(0x7) << SERCOM_USART_CTRLA_MODE_Pos)      /**< (SERCOM_USART_CTRLA) Operating Mode Mask */
#define SERCOM_USART_CTRLA_MODE(value)      (SERCOM_USART_CTRLA_MODE_Msk & ((value) << SERCOM_USART_CTRLA_MODE_Pos))
#define SERCOM_USART_CTRLA_RUNSTDBY_Pos     7                                              /**< (SERCOM_USART_CTRLA) Run during Standby Position */
#define SERCOM_USART_CTRLA_RUNSTDBY_Msk     (_U_(0x1) << SERCOM_USART_CTRLA_RUNSTDBY_Pos)  /**< (SERCOM_USART_CTRLA) Run during Standby Mask */
#define SERCOM_USART_CTRLA_RUNSTDBY         SERCOM_USART_CTRLA_RUNSTDBY_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLA_RUNSTDBY_Msk instead */
#define SERCOM_USART_CTRLA_IBON_Pos         8                                              /**< (SERCOM_USART_CTRLA) Immediate Buffer Overflow Notification Position */
#define SERCOM_USART_CTRLA_IBON_Msk         (_U_(0x1) << SERCOM_USART_CTRLA_IBON_Pos)      /**< (SERCOM_USART_CTRLA) Immediate Buffer Overflow Notification Mask */
#define SERCOM_USART_CTRLA_IBON             SERCOM_USART_CTRLA_IBON_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLA_IBON_Msk instead */
#define SERCOM_USART_CTRLA_TXINV_Pos        9                                              /**< (SERCOM_USART_CTRLA) Transmit Data Invert Position */
#define SERCOM_USART_CTRLA_TXINV_Msk        (_U_(0x1) << SERCOM_USART_CTRLA_TXINV_Pos)     /**< (SERCOM_USART_CTRLA) Transmit Data Invert Mask */
#define SERCOM_USART_CTRLA_TXINV            SERCOM_USART_CTRLA_TXINV_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLA_TXINV_Msk instead */
#define SERCOM_USART_CTRLA_RXINV_Pos        10                                             /**< (SERCOM_USART_CTRLA) Receive Data Invert Position */
#define SERCOM_USART_CTRLA_RXINV_Msk        (_U_(0x1) << SERCOM_USART_CTRLA_RXINV_Pos)     /**< (SERCOM_USART_CTRLA) Receive Data Invert Mask */
#define SERCOM_USART_CTRLA_RXINV            SERCOM_USART_CTRLA_RXINV_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLA_RXINV_Msk instead */
#define SERCOM_USART_CTRLA_SAMPR_Pos        13                                             /**< (SERCOM_USART_CTRLA) Sample Position */
#define SERCOM_USART_CTRLA_SAMPR_Msk        (_U_(0x7) << SERCOM_USART_CTRLA_SAMPR_Pos)     /**< (SERCOM_USART_CTRLA) Sample Mask */
#define SERCOM_USART_CTRLA_SAMPR(value)     (SERCOM_USART_CTRLA_SAMPR_Msk & ((value) << SERCOM_USART_CTRLA_SAMPR_Pos))
#define SERCOM_USART_CTRLA_TXPO_Pos         16                                             /**< (SERCOM_USART_CTRLA) Transmit Data Pinout Position */
#define SERCOM_USART_CTRLA_TXPO_Msk         (_U_(0x3) << SERCOM_USART_CTRLA_TXPO_Pos)      /**< (SERCOM_USART_CTRLA) Transmit Data Pinout Mask */
#define SERCOM_USART_CTRLA_TXPO(value)      (SERCOM_USART_CTRLA_TXPO_Msk & ((value) << SERCOM_USART_CTRLA_TXPO_Pos))
#define SERCOM_USART_CTRLA_RXPO_Pos         20                                             /**< (SERCOM_USART_CTRLA) Receive Data Pinout Position */
#define SERCOM_USART_CTRLA_RXPO_Msk         (_U_(0x3) << SERCOM_USART_CTRLA_RXPO_Pos)      /**< (SERCOM_USART_CTRLA) Receive Data Pinout Mask */
#define SERCOM_USART_CTRLA_RXPO(value)      (SERCOM_USART_CTRLA_RXPO_Msk & ((value) << SERCOM_USART_CTRLA_RXPO_Pos))
#define SERCOM_USART_CTRLA_SAMPA_Pos        22                                             /**< (SERCOM_USART_CTRLA) Sample Adjustment Position */
#define SERCOM_USART_CTRLA_SAMPA_Msk        (_U_(0x3) << SERCOM_USART_CTRLA_SAMPA_Pos)     /**< (SERCOM_USART_CTRLA) Sample Adjustment Mask */
#define SERCOM_USART_CTRLA_SAMPA(value)     (SERCOM_USART_CTRLA_SAMPA_Msk & ((value) << SERCOM_USART_CTRLA_SAMPA_Pos))
#define SERCOM_USART_CTRLA_FORM_Pos         24                                             /**< (SERCOM_USART_CTRLA) Frame Format Position */
#define SERCOM_USART_CTRLA_FORM_Msk         (_U_(0xF) << SERCOM_USART_CTRLA_FORM_Pos)      /**< (SERCOM_USART_CTRLA) Frame Format Mask */
#define SERCOM_USART_CTRLA_FORM(value)      (SERCOM_USART_CTRLA_FORM_Msk & ((value) << SERCOM_USART_CTRLA_FORM_Pos))
#define SERCOM_USART_CTRLA_CMODE_Pos        28                                             /**< (SERCOM_USART_CTRLA) Communication Mode Position */
#define SERCOM_USART_CTRLA_CMODE_Msk        (_U_(0x1) << SERCOM_USART_CTRLA_CMODE_Pos)     /**< (SERCOM_USART_CTRLA) Communication Mode Mask */
#define SERCOM_USART_CTRLA_CMODE            SERCOM_USART_CTRLA_CMODE_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLA_CMODE_Msk instead */
#define SERCOM_USART_CTRLA_CPOL_Pos         29                                             /**< (SERCOM_USART_CTRLA) Clock Polarity Position */
#define SERCOM_USART_CTRLA_CPOL_Msk         (_U_(0x1) << SERCOM_USART_CTRLA_CPOL_Pos)      /**< (SERCOM_USART_CTRLA) Clock Polarity Mask */
#define SERCOM_USART_CTRLA_CPOL             SERCOM_USART_CTRLA_CPOL_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLA_CPOL_Msk instead */
#define SERCOM_USART_CTRLA_DORD_Pos         30                                             /**< (SERCOM_USART_CTRLA) Data Order Position */
#define SERCOM_USART_CTRLA_DORD_Msk         (_U_(0x1) << SERCOM_USART_CTRLA_DORD_Pos)      /**< (SERCOM_USART_CTRLA) Data Order Mask */
#define SERCOM_USART_CTRLA_DORD             SERCOM_USART_CTRLA_DORD_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLA_DORD_Msk instead */
#define SERCOM_USART_CTRLA_MASK             _U_(0x7FF3E79F)                                /**< \deprecated (SERCOM_USART_CTRLA) Register MASK  (Use SERCOM_USART_CTRLA_Msk instead)  */
#define SERCOM_USART_CTRLA_Msk              _U_(0x7FF3E79F)                                /**< (SERCOM_USART_CTRLA) Register Mask  */


/* -------- SERCOM_I2CM_CTRLB : (SERCOM Offset: 0x04) (R/W 32) I2CM Control B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :8;                        /**< bit:   0..7  Reserved */
    uint32_t SMEN:1;                    /**< bit:      8  Smart Mode Enable                        */
    uint32_t QCEN:1;                    /**< bit:      9  Quick Command Enable                     */
    uint32_t :6;                        /**< bit: 10..15  Reserved */
    uint32_t CMD:2;                     /**< bit: 16..17  Command                                  */
    uint32_t ACKACT:1;                  /**< bit:     18  Acknowledge Action                       */
    uint32_t :13;                       /**< bit: 19..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_I2CM_CTRLB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_CTRLB_OFFSET            (0x04)                                        /**<  (SERCOM_I2CM_CTRLB) I2CM Control B  Offset */
#define SERCOM_I2CM_CTRLB_RESETVALUE        _U_(0x00)                                     /**<  (SERCOM_I2CM_CTRLB) I2CM Control B  Reset Value */

#define SERCOM_I2CM_CTRLB_SMEN_Pos          8                                              /**< (SERCOM_I2CM_CTRLB) Smart Mode Enable Position */
#define SERCOM_I2CM_CTRLB_SMEN_Msk          (_U_(0x1) << SERCOM_I2CM_CTRLB_SMEN_Pos)       /**< (SERCOM_I2CM_CTRLB) Smart Mode Enable Mask */
#define SERCOM_I2CM_CTRLB_SMEN              SERCOM_I2CM_CTRLB_SMEN_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_CTRLB_SMEN_Msk instead */
#define SERCOM_I2CM_CTRLB_QCEN_Pos          9                                              /**< (SERCOM_I2CM_CTRLB) Quick Command Enable Position */
#define SERCOM_I2CM_CTRLB_QCEN_Msk          (_U_(0x1) << SERCOM_I2CM_CTRLB_QCEN_Pos)       /**< (SERCOM_I2CM_CTRLB) Quick Command Enable Mask */
#define SERCOM_I2CM_CTRLB_QCEN              SERCOM_I2CM_CTRLB_QCEN_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_CTRLB_QCEN_Msk instead */
#define SERCOM_I2CM_CTRLB_CMD_Pos           16                                             /**< (SERCOM_I2CM_CTRLB) Command Position */
#define SERCOM_I2CM_CTRLB_CMD_Msk           (_U_(0x3) << SERCOM_I2CM_CTRLB_CMD_Pos)        /**< (SERCOM_I2CM_CTRLB) Command Mask */
#define SERCOM_I2CM_CTRLB_CMD(value)        (SERCOM_I2CM_CTRLB_CMD_Msk & ((value) << SERCOM_I2CM_CTRLB_CMD_Pos))
#define SERCOM_I2CM_CTRLB_ACKACT_Pos        18                                             /**< (SERCOM_I2CM_CTRLB) Acknowledge Action Position */
#define SERCOM_I2CM_CTRLB_ACKACT_Msk        (_U_(0x1) << SERCOM_I2CM_CTRLB_ACKACT_Pos)     /**< (SERCOM_I2CM_CTRLB) Acknowledge Action Mask */
#define SERCOM_I2CM_CTRLB_ACKACT            SERCOM_I2CM_CTRLB_ACKACT_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_CTRLB_ACKACT_Msk instead */
#define SERCOM_I2CM_CTRLB_MASK              _U_(0x70300)                                   /**< \deprecated (SERCOM_I2CM_CTRLB) Register MASK  (Use SERCOM_I2CM_CTRLB_Msk instead)  */
#define SERCOM_I2CM_CTRLB_Msk               _U_(0x70300)                                   /**< (SERCOM_I2CM_CTRLB) Register Mask  */


/* -------- SERCOM_I2CS_CTRLB : (SERCOM Offset: 0x04) (R/W 32) I2CS Control B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :8;                        /**< bit:   0..7  Reserved */
    uint32_t SMEN:1;                    /**< bit:      8  Smart Mode Enable                        */
    uint32_t GCMD:1;                    /**< bit:      9  PMBus Group Command                      */
    uint32_t AACKEN:1;                  /**< bit:     10  Automatic Address Acknowledge            */
    uint32_t :3;                        /**< bit: 11..13  Reserved */
    uint32_t AMODE:2;                   /**< bit: 14..15  Address Mode                             */
    uint32_t CMD:2;                     /**< bit: 16..17  Command                                  */
    uint32_t ACKACT:1;                  /**< bit:     18  Acknowledge Action                       */
    uint32_t :13;                       /**< bit: 19..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_I2CS_CTRLB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_CTRLB_OFFSET            (0x04)                                        /**<  (SERCOM_I2CS_CTRLB) I2CS Control B  Offset */
#define SERCOM_I2CS_CTRLB_RESETVALUE        _U_(0x00)                                     /**<  (SERCOM_I2CS_CTRLB) I2CS Control B  Reset Value */

#define SERCOM_I2CS_CTRLB_SMEN_Pos          8                                              /**< (SERCOM_I2CS_CTRLB) Smart Mode Enable Position */
#define SERCOM_I2CS_CTRLB_SMEN_Msk          (_U_(0x1) << SERCOM_I2CS_CTRLB_SMEN_Pos)       /**< (SERCOM_I2CS_CTRLB) Smart Mode Enable Mask */
#define SERCOM_I2CS_CTRLB_SMEN              SERCOM_I2CS_CTRLB_SMEN_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_CTRLB_SMEN_Msk instead */
#define SERCOM_I2CS_CTRLB_GCMD_Pos          9                                              /**< (SERCOM_I2CS_CTRLB) PMBus Group Command Position */
#define SERCOM_I2CS_CTRLB_GCMD_Msk          (_U_(0x1) << SERCOM_I2CS_CTRLB_GCMD_Pos)       /**< (SERCOM_I2CS_CTRLB) PMBus Group Command Mask */
#define SERCOM_I2CS_CTRLB_GCMD              SERCOM_I2CS_CTRLB_GCMD_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_CTRLB_GCMD_Msk instead */
#define SERCOM_I2CS_CTRLB_AACKEN_Pos        10                                             /**< (SERCOM_I2CS_CTRLB) Automatic Address Acknowledge Position */
#define SERCOM_I2CS_CTRLB_AACKEN_Msk        (_U_(0x1) << SERCOM_I2CS_CTRLB_AACKEN_Pos)     /**< (SERCOM_I2CS_CTRLB) Automatic Address Acknowledge Mask */
#define SERCOM_I2CS_CTRLB_AACKEN            SERCOM_I2CS_CTRLB_AACKEN_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_CTRLB_AACKEN_Msk instead */
#define SERCOM_I2CS_CTRLB_AMODE_Pos         14                                             /**< (SERCOM_I2CS_CTRLB) Address Mode Position */
#define SERCOM_I2CS_CTRLB_AMODE_Msk         (_U_(0x3) << SERCOM_I2CS_CTRLB_AMODE_Pos)      /**< (SERCOM_I2CS_CTRLB) Address Mode Mask */
#define SERCOM_I2CS_CTRLB_AMODE(value)      (SERCOM_I2CS_CTRLB_AMODE_Msk & ((value) << SERCOM_I2CS_CTRLB_AMODE_Pos))
#define SERCOM_I2CS_CTRLB_CMD_Pos           16                                             /**< (SERCOM_I2CS_CTRLB) Command Position */
#define SERCOM_I2CS_CTRLB_CMD_Msk           (_U_(0x3) << SERCOM_I2CS_CTRLB_CMD_Pos)        /**< (SERCOM_I2CS_CTRLB) Command Mask */
#define SERCOM_I2CS_CTRLB_CMD(value)        (SERCOM_I2CS_CTRLB_CMD_Msk & ((value) << SERCOM_I2CS_CTRLB_CMD_Pos))
#define SERCOM_I2CS_CTRLB_ACKACT_Pos        18                                             /**< (SERCOM_I2CS_CTRLB) Acknowledge Action Position */
#define SERCOM_I2CS_CTRLB_ACKACT_Msk        (_U_(0x1) << SERCOM_I2CS_CTRLB_ACKACT_Pos)     /**< (SERCOM_I2CS_CTRLB) Acknowledge Action Mask */
#define SERCOM_I2CS_CTRLB_ACKACT            SERCOM_I2CS_CTRLB_ACKACT_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_CTRLB_ACKACT_Msk instead */
#define SERCOM_I2CS_CTRLB_MASK              _U_(0x7C700)                                   /**< \deprecated (SERCOM_I2CS_CTRLB) Register MASK  (Use SERCOM_I2CS_CTRLB_Msk instead)  */
#define SERCOM_I2CS_CTRLB_Msk               _U_(0x7C700)                                   /**< (SERCOM_I2CS_CTRLB) Register Mask  */


/* -------- SERCOM_SPI_CTRLB : (SERCOM Offset: 0x04) (R/W 32) SPI Control B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CHSIZE:3;                  /**< bit:   0..2  Character Size                           */
    uint32_t :3;                        /**< bit:   3..5  Reserved */
    uint32_t PLOADEN:1;                 /**< bit:      6  Data Preload Enable                      */
    uint32_t :2;                        /**< bit:   7..8  Reserved */
    uint32_t SSDE:1;                    /**< bit:      9  Slave Select Low Detect Enable           */
    uint32_t :3;                        /**< bit: 10..12  Reserved */
    uint32_t MSSEN:1;                   /**< bit:     13  Master Slave Select Enable               */
    uint32_t AMODE:2;                   /**< bit: 14..15  Address Mode                             */
    uint32_t :1;                        /**< bit:     16  Reserved */
    uint32_t RXEN:1;                    /**< bit:     17  Receiver Enable                          */
    uint32_t :14;                       /**< bit: 18..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_SPI_CTRLB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_CTRLB_OFFSET             (0x04)                                        /**<  (SERCOM_SPI_CTRLB) SPI Control B  Offset */
#define SERCOM_SPI_CTRLB_RESETVALUE         _U_(0x00)                                     /**<  (SERCOM_SPI_CTRLB) SPI Control B  Reset Value */

#define SERCOM_SPI_CTRLB_CHSIZE_Pos         0                                              /**< (SERCOM_SPI_CTRLB) Character Size Position */
#define SERCOM_SPI_CTRLB_CHSIZE_Msk         (_U_(0x7) << SERCOM_SPI_CTRLB_CHSIZE_Pos)      /**< (SERCOM_SPI_CTRLB) Character Size Mask */
#define SERCOM_SPI_CTRLB_CHSIZE(value)      (SERCOM_SPI_CTRLB_CHSIZE_Msk & ((value) << SERCOM_SPI_CTRLB_CHSIZE_Pos))
#define SERCOM_SPI_CTRLB_PLOADEN_Pos        6                                              /**< (SERCOM_SPI_CTRLB) Data Preload Enable Position */
#define SERCOM_SPI_CTRLB_PLOADEN_Msk        (_U_(0x1) << SERCOM_SPI_CTRLB_PLOADEN_Pos)     /**< (SERCOM_SPI_CTRLB) Data Preload Enable Mask */
#define SERCOM_SPI_CTRLB_PLOADEN            SERCOM_SPI_CTRLB_PLOADEN_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_CTRLB_PLOADEN_Msk instead */
#define SERCOM_SPI_CTRLB_SSDE_Pos           9                                              /**< (SERCOM_SPI_CTRLB) Slave Select Low Detect Enable Position */
#define SERCOM_SPI_CTRLB_SSDE_Msk           (_U_(0x1) << SERCOM_SPI_CTRLB_SSDE_Pos)        /**< (SERCOM_SPI_CTRLB) Slave Select Low Detect Enable Mask */
#define SERCOM_SPI_CTRLB_SSDE               SERCOM_SPI_CTRLB_SSDE_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_CTRLB_SSDE_Msk instead */
#define SERCOM_SPI_CTRLB_MSSEN_Pos          13                                             /**< (SERCOM_SPI_CTRLB) Master Slave Select Enable Position */
#define SERCOM_SPI_CTRLB_MSSEN_Msk          (_U_(0x1) << SERCOM_SPI_CTRLB_MSSEN_Pos)       /**< (SERCOM_SPI_CTRLB) Master Slave Select Enable Mask */
#define SERCOM_SPI_CTRLB_MSSEN              SERCOM_SPI_CTRLB_MSSEN_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_CTRLB_MSSEN_Msk instead */
#define SERCOM_SPI_CTRLB_AMODE_Pos          14                                             /**< (SERCOM_SPI_CTRLB) Address Mode Position */
#define SERCOM_SPI_CTRLB_AMODE_Msk          (_U_(0x3) << SERCOM_SPI_CTRLB_AMODE_Pos)       /**< (SERCOM_SPI_CTRLB) Address Mode Mask */
#define SERCOM_SPI_CTRLB_AMODE(value)       (SERCOM_SPI_CTRLB_AMODE_Msk & ((value) << SERCOM_SPI_CTRLB_AMODE_Pos))
#define SERCOM_SPI_CTRLB_RXEN_Pos           17                                             /**< (SERCOM_SPI_CTRLB) Receiver Enable Position */
#define SERCOM_SPI_CTRLB_RXEN_Msk           (_U_(0x1) << SERCOM_SPI_CTRLB_RXEN_Pos)        /**< (SERCOM_SPI_CTRLB) Receiver Enable Mask */
#define SERCOM_SPI_CTRLB_RXEN               SERCOM_SPI_CTRLB_RXEN_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_CTRLB_RXEN_Msk instead */
#define SERCOM_SPI_CTRLB_MASK               _U_(0x2E247)                                   /**< \deprecated (SERCOM_SPI_CTRLB) Register MASK  (Use SERCOM_SPI_CTRLB_Msk instead)  */
#define SERCOM_SPI_CTRLB_Msk                _U_(0x2E247)                                   /**< (SERCOM_SPI_CTRLB) Register Mask  */


/* -------- SERCOM_USART_CTRLB : (SERCOM Offset: 0x04) (R/W 32) USART Control B -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CHSIZE:3;                  /**< bit:   0..2  Character Size                           */
    uint32_t :3;                        /**< bit:   3..5  Reserved */
    uint32_t SBMODE:1;                  /**< bit:      6  Stop Bit Mode                            */
    uint32_t :1;                        /**< bit:      7  Reserved */
    uint32_t COLDEN:1;                  /**< bit:      8  Collision Detection Enable               */
    uint32_t SFDE:1;                    /**< bit:      9  Start of Frame Detection Enable          */
    uint32_t ENC:1;                     /**< bit:     10  Encoding Format                          */
    uint32_t :2;                        /**< bit: 11..12  Reserved */
    uint32_t PMODE:1;                   /**< bit:     13  Parity Mode                              */
    uint32_t :2;                        /**< bit: 14..15  Reserved */
    uint32_t TXEN:1;                    /**< bit:     16  Transmitter Enable                       */
    uint32_t RXEN:1;                    /**< bit:     17  Receiver Enable                          */
    uint32_t :6;                        /**< bit: 18..23  Reserved */
    uint32_t LINCMD:2;                  /**< bit: 24..25  LIN Command                              */
    uint32_t :6;                        /**< bit: 26..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_USART_CTRLB_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_CTRLB_OFFSET           (0x04)                                        /**<  (SERCOM_USART_CTRLB) USART Control B  Offset */
#define SERCOM_USART_CTRLB_RESETVALUE       _U_(0x00)                                     /**<  (SERCOM_USART_CTRLB) USART Control B  Reset Value */

#define SERCOM_USART_CTRLB_CHSIZE_Pos       0                                              /**< (SERCOM_USART_CTRLB) Character Size Position */
#define SERCOM_USART_CTRLB_CHSIZE_Msk       (_U_(0x7) << SERCOM_USART_CTRLB_CHSIZE_Pos)    /**< (SERCOM_USART_CTRLB) Character Size Mask */
#define SERCOM_USART_CTRLB_CHSIZE(value)    (SERCOM_USART_CTRLB_CHSIZE_Msk & ((value) << SERCOM_USART_CTRLB_CHSIZE_Pos))
#define SERCOM_USART_CTRLB_SBMODE_Pos       6                                              /**< (SERCOM_USART_CTRLB) Stop Bit Mode Position */
#define SERCOM_USART_CTRLB_SBMODE_Msk       (_U_(0x1) << SERCOM_USART_CTRLB_SBMODE_Pos)    /**< (SERCOM_USART_CTRLB) Stop Bit Mode Mask */
#define SERCOM_USART_CTRLB_SBMODE           SERCOM_USART_CTRLB_SBMODE_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLB_SBMODE_Msk instead */
#define SERCOM_USART_CTRLB_COLDEN_Pos       8                                              /**< (SERCOM_USART_CTRLB) Collision Detection Enable Position */
#define SERCOM_USART_CTRLB_COLDEN_Msk       (_U_(0x1) << SERCOM_USART_CTRLB_COLDEN_Pos)    /**< (SERCOM_USART_CTRLB) Collision Detection Enable Mask */
#define SERCOM_USART_CTRLB_COLDEN           SERCOM_USART_CTRLB_COLDEN_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLB_COLDEN_Msk instead */
#define SERCOM_USART_CTRLB_SFDE_Pos         9                                              /**< (SERCOM_USART_CTRLB) Start of Frame Detection Enable Position */
#define SERCOM_USART_CTRLB_SFDE_Msk         (_U_(0x1) << SERCOM_USART_CTRLB_SFDE_Pos)      /**< (SERCOM_USART_CTRLB) Start of Frame Detection Enable Mask */
#define SERCOM_USART_CTRLB_SFDE             SERCOM_USART_CTRLB_SFDE_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLB_SFDE_Msk instead */
#define SERCOM_USART_CTRLB_ENC_Pos          10                                             /**< (SERCOM_USART_CTRLB) Encoding Format Position */
#define SERCOM_USART_CTRLB_ENC_Msk          (_U_(0x1) << SERCOM_USART_CTRLB_ENC_Pos)       /**< (SERCOM_USART_CTRLB) Encoding Format Mask */
#define SERCOM_USART_CTRLB_ENC              SERCOM_USART_CTRLB_ENC_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLB_ENC_Msk instead */
#define SERCOM_USART_CTRLB_PMODE_Pos        13                                             /**< (SERCOM_USART_CTRLB) Parity Mode Position */
#define SERCOM_USART_CTRLB_PMODE_Msk        (_U_(0x1) << SERCOM_USART_CTRLB_PMODE_Pos)     /**< (SERCOM_USART_CTRLB) Parity Mode Mask */
#define SERCOM_USART_CTRLB_PMODE            SERCOM_USART_CTRLB_PMODE_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLB_PMODE_Msk instead */
#define SERCOM_USART_CTRLB_TXEN_Pos         16                                             /**< (SERCOM_USART_CTRLB) Transmitter Enable Position */
#define SERCOM_USART_CTRLB_TXEN_Msk         (_U_(0x1) << SERCOM_USART_CTRLB_TXEN_Pos)      /**< (SERCOM_USART_CTRLB) Transmitter Enable Mask */
#define SERCOM_USART_CTRLB_TXEN             SERCOM_USART_CTRLB_TXEN_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLB_TXEN_Msk instead */
#define SERCOM_USART_CTRLB_RXEN_Pos         17                                             /**< (SERCOM_USART_CTRLB) Receiver Enable Position */
#define SERCOM_USART_CTRLB_RXEN_Msk         (_U_(0x1) << SERCOM_USART_CTRLB_RXEN_Pos)      /**< (SERCOM_USART_CTRLB) Receiver Enable Mask */
#define SERCOM_USART_CTRLB_RXEN             SERCOM_USART_CTRLB_RXEN_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLB_RXEN_Msk instead */
#define SERCOM_USART_CTRLB_LINCMD_Pos       24                                             /**< (SERCOM_USART_CTRLB) LIN Command Position */
#define SERCOM_USART_CTRLB_LINCMD_Msk       (_U_(0x3) << SERCOM_USART_CTRLB_LINCMD_Pos)    /**< (SERCOM_USART_CTRLB) LIN Command Mask */
#define SERCOM_USART_CTRLB_LINCMD(value)    (SERCOM_USART_CTRLB_LINCMD_Msk & ((value) << SERCOM_USART_CTRLB_LINCMD_Pos))
#define SERCOM_USART_CTRLB_MASK             _U_(0x3032747)                                 /**< \deprecated (SERCOM_USART_CTRLB) Register MASK  (Use SERCOM_USART_CTRLB_Msk instead)  */
#define SERCOM_USART_CTRLB_Msk              _U_(0x3032747)                                 /**< (SERCOM_USART_CTRLB) Register Mask  */


/* -------- SERCOM_USART_CTRLC : (SERCOM Offset: 0x08) (R/W 32) USART Control C -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t GTIME:3;                   /**< bit:   0..2  Guard Time                               */
    uint32_t :5;                        /**< bit:   3..7  Reserved */
    uint32_t BRKLEN:2;                  /**< bit:   8..9  LIN Master Break Length                  */
    uint32_t HDRDLY:2;                  /**< bit: 10..11  LIN Master Header Delay                  */
    uint32_t :4;                        /**< bit: 12..15  Reserved */
    uint32_t INACK:1;                   /**< bit:     16  Inhibit Not Acknowledge                  */
    uint32_t DSNACK:1;                  /**< bit:     17  Disable Successive NACK                  */
    uint32_t :2;                        /**< bit: 18..19  Reserved */
    uint32_t MAXITER:3;                 /**< bit: 20..22  Maximum Iterations                       */
    uint32_t :9;                        /**< bit: 23..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_USART_CTRLC_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_CTRLC_OFFSET           (0x08)                                        /**<  (SERCOM_USART_CTRLC) USART Control C  Offset */
#define SERCOM_USART_CTRLC_RESETVALUE       _U_(0x00)                                     /**<  (SERCOM_USART_CTRLC) USART Control C  Reset Value */

#define SERCOM_USART_CTRLC_GTIME_Pos        0                                              /**< (SERCOM_USART_CTRLC) Guard Time Position */
#define SERCOM_USART_CTRLC_GTIME_Msk        (_U_(0x7) << SERCOM_USART_CTRLC_GTIME_Pos)     /**< (SERCOM_USART_CTRLC) Guard Time Mask */
#define SERCOM_USART_CTRLC_GTIME(value)     (SERCOM_USART_CTRLC_GTIME_Msk & ((value) << SERCOM_USART_CTRLC_GTIME_Pos))
#define SERCOM_USART_CTRLC_BRKLEN_Pos       8                                              /**< (SERCOM_USART_CTRLC) LIN Master Break Length Position */
#define SERCOM_USART_CTRLC_BRKLEN_Msk       (_U_(0x3) << SERCOM_USART_CTRLC_BRKLEN_Pos)    /**< (SERCOM_USART_CTRLC) LIN Master Break Length Mask */
#define SERCOM_USART_CTRLC_BRKLEN(value)    (SERCOM_USART_CTRLC_BRKLEN_Msk & ((value) << SERCOM_USART_CTRLC_BRKLEN_Pos))
#define SERCOM_USART_CTRLC_HDRDLY_Pos       10                                             /**< (SERCOM_USART_CTRLC) LIN Master Header Delay Position */
#define SERCOM_USART_CTRLC_HDRDLY_Msk       (_U_(0x3) << SERCOM_USART_CTRLC_HDRDLY_Pos)    /**< (SERCOM_USART_CTRLC) LIN Master Header Delay Mask */
#define SERCOM_USART_CTRLC_HDRDLY(value)    (SERCOM_USART_CTRLC_HDRDLY_Msk & ((value) << SERCOM_USART_CTRLC_HDRDLY_Pos))
#define SERCOM_USART_CTRLC_INACK_Pos        16                                             /**< (SERCOM_USART_CTRLC) Inhibit Not Acknowledge Position */
#define SERCOM_USART_CTRLC_INACK_Msk        (_U_(0x1) << SERCOM_USART_CTRLC_INACK_Pos)     /**< (SERCOM_USART_CTRLC) Inhibit Not Acknowledge Mask */
#define SERCOM_USART_CTRLC_INACK            SERCOM_USART_CTRLC_INACK_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLC_INACK_Msk instead */
#define SERCOM_USART_CTRLC_DSNACK_Pos       17                                             /**< (SERCOM_USART_CTRLC) Disable Successive NACK Position */
#define SERCOM_USART_CTRLC_DSNACK_Msk       (_U_(0x1) << SERCOM_USART_CTRLC_DSNACK_Pos)    /**< (SERCOM_USART_CTRLC) Disable Successive NACK Mask */
#define SERCOM_USART_CTRLC_DSNACK           SERCOM_USART_CTRLC_DSNACK_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_CTRLC_DSNACK_Msk instead */
#define SERCOM_USART_CTRLC_MAXITER_Pos      20                                             /**< (SERCOM_USART_CTRLC) Maximum Iterations Position */
#define SERCOM_USART_CTRLC_MAXITER_Msk      (_U_(0x7) << SERCOM_USART_CTRLC_MAXITER_Pos)   /**< (SERCOM_USART_CTRLC) Maximum Iterations Mask */
#define SERCOM_USART_CTRLC_MAXITER(value)   (SERCOM_USART_CTRLC_MAXITER_Msk & ((value) << SERCOM_USART_CTRLC_MAXITER_Pos))
#define SERCOM_USART_CTRLC_MASK             _U_(0x730F07)                                  /**< \deprecated (SERCOM_USART_CTRLC) Register MASK  (Use SERCOM_USART_CTRLC_Msk instead)  */
#define SERCOM_USART_CTRLC_Msk              _U_(0x730F07)                                  /**< (SERCOM_USART_CTRLC) Register Mask  */


/* -------- SERCOM_I2CM_BAUD : (SERCOM Offset: 0x0c) (R/W 32) I2CM Baud Rate -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t BAUD:8;                    /**< bit:   0..7  Baud Rate Value                          */
    uint32_t BAUDLOW:8;                 /**< bit:  8..15  Baud Rate Value Low                      */
    uint32_t HSBAUD:8;                  /**< bit: 16..23  High Speed Baud Rate Value               */
    uint32_t HSBAUDLOW:8;               /**< bit: 24..31  High Speed Baud Rate Value Low           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_I2CM_BAUD_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_BAUD_OFFSET             (0x0C)                                        /**<  (SERCOM_I2CM_BAUD) I2CM Baud Rate  Offset */
#define SERCOM_I2CM_BAUD_RESETVALUE         _U_(0x00)                                     /**<  (SERCOM_I2CM_BAUD) I2CM Baud Rate  Reset Value */

#define SERCOM_I2CM_BAUD_BAUD_Pos           0                                              /**< (SERCOM_I2CM_BAUD) Baud Rate Value Position */
#define SERCOM_I2CM_BAUD_BAUD_Msk           (_U_(0xFF) << SERCOM_I2CM_BAUD_BAUD_Pos)       /**< (SERCOM_I2CM_BAUD) Baud Rate Value Mask */
#define SERCOM_I2CM_BAUD_BAUD(value)        (SERCOM_I2CM_BAUD_BAUD_Msk & ((value) << SERCOM_I2CM_BAUD_BAUD_Pos))
#define SERCOM_I2CM_BAUD_BAUDLOW_Pos        8                                              /**< (SERCOM_I2CM_BAUD) Baud Rate Value Low Position */
#define SERCOM_I2CM_BAUD_BAUDLOW_Msk        (_U_(0xFF) << SERCOM_I2CM_BAUD_BAUDLOW_Pos)    /**< (SERCOM_I2CM_BAUD) Baud Rate Value Low Mask */
#define SERCOM_I2CM_BAUD_BAUDLOW(value)     (SERCOM_I2CM_BAUD_BAUDLOW_Msk & ((value) << SERCOM_I2CM_BAUD_BAUDLOW_Pos))
#define SERCOM_I2CM_BAUD_HSBAUD_Pos         16                                             /**< (SERCOM_I2CM_BAUD) High Speed Baud Rate Value Position */
#define SERCOM_I2CM_BAUD_HSBAUD_Msk         (_U_(0xFF) << SERCOM_I2CM_BAUD_HSBAUD_Pos)     /**< (SERCOM_I2CM_BAUD) High Speed Baud Rate Value Mask */
#define SERCOM_I2CM_BAUD_HSBAUD(value)      (SERCOM_I2CM_BAUD_HSBAUD_Msk & ((value) << SERCOM_I2CM_BAUD_HSBAUD_Pos))
#define SERCOM_I2CM_BAUD_HSBAUDLOW_Pos      24                                             /**< (SERCOM_I2CM_BAUD) High Speed Baud Rate Value Low Position */
#define SERCOM_I2CM_BAUD_HSBAUDLOW_Msk      (_U_(0xFF) << SERCOM_I2CM_BAUD_HSBAUDLOW_Pos)  /**< (SERCOM_I2CM_BAUD) High Speed Baud Rate Value Low Mask */
#define SERCOM_I2CM_BAUD_HSBAUDLOW(value)   (SERCOM_I2CM_BAUD_HSBAUDLOW_Msk & ((value) << SERCOM_I2CM_BAUD_HSBAUDLOW_Pos))
#define SERCOM_I2CM_BAUD_MASK               _U_(0xFFFFFFFF)                                /**< \deprecated (SERCOM_I2CM_BAUD) Register MASK  (Use SERCOM_I2CM_BAUD_Msk instead)  */
#define SERCOM_I2CM_BAUD_Msk                _U_(0xFFFFFFFF)                                /**< (SERCOM_I2CM_BAUD) Register Mask  */


/* -------- SERCOM_SPI_BAUD : (SERCOM Offset: 0x0c) (R/W 8) SPI Baud Rate -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  BAUD:8;                    /**< bit:   0..7  Baud Rate Value                          */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_SPI_BAUD_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_BAUD_OFFSET              (0x0C)                                        /**<  (SERCOM_SPI_BAUD) SPI Baud Rate  Offset */
#define SERCOM_SPI_BAUD_RESETVALUE          _U_(0x00)                                     /**<  (SERCOM_SPI_BAUD) SPI Baud Rate  Reset Value */

#define SERCOM_SPI_BAUD_BAUD_Pos            0                                              /**< (SERCOM_SPI_BAUD) Baud Rate Value Position */
#define SERCOM_SPI_BAUD_BAUD_Msk            (_U_(0xFF) << SERCOM_SPI_BAUD_BAUD_Pos)        /**< (SERCOM_SPI_BAUD) Baud Rate Value Mask */
#define SERCOM_SPI_BAUD_BAUD(value)         (SERCOM_SPI_BAUD_BAUD_Msk & ((value) << SERCOM_SPI_BAUD_BAUD_Pos))
#define SERCOM_SPI_BAUD_MASK                _U_(0xFF)                                      /**< \deprecated (SERCOM_SPI_BAUD) Register MASK  (Use SERCOM_SPI_BAUD_Msk instead)  */
#define SERCOM_SPI_BAUD_Msk                 _U_(0xFF)                                      /**< (SERCOM_SPI_BAUD) Register Mask  */


/* -------- SERCOM_USART_BAUD : (SERCOM Offset: 0x0c) (R/W 16) USART Baud Rate -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t BAUD:16;                   /**< bit:  0..15  Baud Rate Value                          */
  } bit;                                /**< Structure used for bit  access */
  struct { // FRAC mode
    uint16_t BAUD:13;                   /**< bit:  0..12  Baud Rate Value                          */
    uint16_t FP:3;                      /**< bit: 13..15  Fractional Part                          */
  } FRAC;                                /**< Structure used for FRAC mode access */
  struct { // FRACFP mode
    uint16_t BAUD:13;                   /**< bit:  0..12  Baud Rate Value                          */
    uint16_t FP:3;                      /**< bit: 13..15  Fractional Part                          */
  } FRACFP;                                /**< Structure used for FRACFP mode access */
  struct { // USARTFP mode
    uint16_t BAUD:16;                   /**< bit:  0..15  Baud Rate Value                          */
  } USARTFP;                                /**< Structure used for USARTFP mode access */
  uint16_t reg;                         /**< Type used for register access */
} SERCOM_USART_BAUD_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_BAUD_OFFSET            (0x0C)                                        /**<  (SERCOM_USART_BAUD) USART Baud Rate  Offset */
#define SERCOM_USART_BAUD_RESETVALUE        _U_(0x00)                                     /**<  (SERCOM_USART_BAUD) USART Baud Rate  Reset Value */

#define SERCOM_USART_BAUD_BAUD_Pos          0                                              /**< (SERCOM_USART_BAUD) Baud Rate Value Position */
#define SERCOM_USART_BAUD_BAUD_Msk          (_U_(0xFFFF) << SERCOM_USART_BAUD_BAUD_Pos)    /**< (SERCOM_USART_BAUD) Baud Rate Value Mask */
#define SERCOM_USART_BAUD_BAUD(value)       (SERCOM_USART_BAUD_BAUD_Msk & ((value) << SERCOM_USART_BAUD_BAUD_Pos))
#define SERCOM_USART_BAUD_MASK              _U_(0xFFFF)                                    /**< \deprecated (SERCOM_USART_BAUD) Register MASK  (Use SERCOM_USART_BAUD_Msk instead)  */
#define SERCOM_USART_BAUD_Msk               _U_(0xFFFF)                                    /**< (SERCOM_USART_BAUD) Register Mask  */

/* FRAC mode */
#define SERCOM_USART_BAUD_FRAC_BAUD_Pos     0                                              /**< (SERCOM_USART_BAUD) Baud Rate Value Position */
#define SERCOM_USART_BAUD_FRAC_BAUD_Msk     (_U_(0x1FFF) << SERCOM_USART_BAUD_FRAC_BAUD_Pos)  /**< (SERCOM_USART_BAUD) Baud Rate Value Mask */
#define SERCOM_USART_BAUD_FRAC_BAUD(value)  (SERCOM_USART_BAUD_FRAC_BAUD_Msk & ((value) << SERCOM_USART_BAUD_FRAC_BAUD_Pos))
#define SERCOM_USART_BAUD_FRAC_FP_Pos       13                                             /**< (SERCOM_USART_BAUD) Fractional Part Position */
#define SERCOM_USART_BAUD_FRAC_FP_Msk       (_U_(0x7) << SERCOM_USART_BAUD_FRAC_FP_Pos)    /**< (SERCOM_USART_BAUD) Fractional Part Mask */
#define SERCOM_USART_BAUD_FRAC_FP(value)    (SERCOM_USART_BAUD_FRAC_FP_Msk & ((value) << SERCOM_USART_BAUD_FRAC_FP_Pos))
#define SERCOM_USART_BAUD_FRAC_MASK         _U_(0xFFFF)                                    /**< \deprecated (SERCOM_USART_BAUD_FRAC) Register MASK  (Use SERCOM_USART_BAUD_FRAC_Msk instead)  */
#define SERCOM_USART_BAUD_FRAC_Msk          _U_(0xFFFF)                                    /**< (SERCOM_USART_BAUD_FRAC) Register Mask  */

/* FRACFP mode */
#define SERCOM_USART_BAUD_FRACFP_BAUD_Pos   0                                              /**< (SERCOM_USART_BAUD) Baud Rate Value Position */
#define SERCOM_USART_BAUD_FRACFP_BAUD_Msk   (_U_(0x1FFF) << SERCOM_USART_BAUD_FRACFP_BAUD_Pos)  /**< (SERCOM_USART_BAUD) Baud Rate Value Mask */
#define SERCOM_USART_BAUD_FRACFP_BAUD(value) (SERCOM_USART_BAUD_FRACFP_BAUD_Msk & ((value) << SERCOM_USART_BAUD_FRACFP_BAUD_Pos))
#define SERCOM_USART_BAUD_FRACFP_FP_Pos     13                                             /**< (SERCOM_USART_BAUD) Fractional Part Position */
#define SERCOM_USART_BAUD_FRACFP_FP_Msk     (_U_(0x7) << SERCOM_USART_BAUD_FRACFP_FP_Pos)  /**< (SERCOM_USART_BAUD) Fractional Part Mask */
#define SERCOM_USART_BAUD_FRACFP_FP(value)  (SERCOM_USART_BAUD_FRACFP_FP_Msk & ((value) << SERCOM_USART_BAUD_FRACFP_FP_Pos))
#define SERCOM_USART_BAUD_FRACFP_MASK       _U_(0xFFFF)                                    /**< \deprecated (SERCOM_USART_BAUD_FRACFP) Register MASK  (Use SERCOM_USART_BAUD_FRACFP_Msk instead)  */
#define SERCOM_USART_BAUD_FRACFP_Msk        _U_(0xFFFF)                                    /**< (SERCOM_USART_BAUD_FRACFP) Register Mask  */

/* USARTFP mode */
#define SERCOM_USART_BAUD_USARTFP_BAUD_Pos  0                                              /**< (SERCOM_USART_BAUD) Baud Rate Value Position */
#define SERCOM_USART_BAUD_USARTFP_BAUD_Msk  (_U_(0xFFFF) << SERCOM_USART_BAUD_USARTFP_BAUD_Pos)  /**< (SERCOM_USART_BAUD) Baud Rate Value Mask */
#define SERCOM_USART_BAUD_USARTFP_BAUD(value) (SERCOM_USART_BAUD_USARTFP_BAUD_Msk & ((value) << SERCOM_USART_BAUD_USARTFP_BAUD_Pos))
#define SERCOM_USART_BAUD_USARTFP_MASK      _U_(0xFFFF)                                    /**< \deprecated (SERCOM_USART_BAUD_USARTFP) Register MASK  (Use SERCOM_USART_BAUD_USARTFP_Msk instead)  */
#define SERCOM_USART_BAUD_USARTFP_Msk       _U_(0xFFFF)                                    /**< (SERCOM_USART_BAUD_USARTFP) Register Mask  */


/* -------- SERCOM_USART_RXPL : (SERCOM Offset: 0x0e) (R/W 8) USART Receive Pulse Length -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RXPL:8;                    /**< bit:   0..7  Receive Pulse Length                     */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_USART_RXPL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_RXPL_OFFSET            (0x0E)                                        /**<  (SERCOM_USART_RXPL) USART Receive Pulse Length  Offset */
#define SERCOM_USART_RXPL_RESETVALUE        _U_(0x00)                                     /**<  (SERCOM_USART_RXPL) USART Receive Pulse Length  Reset Value */

#define SERCOM_USART_RXPL_RXPL_Pos          0                                              /**< (SERCOM_USART_RXPL) Receive Pulse Length Position */
#define SERCOM_USART_RXPL_RXPL_Msk          (_U_(0xFF) << SERCOM_USART_RXPL_RXPL_Pos)      /**< (SERCOM_USART_RXPL) Receive Pulse Length Mask */
#define SERCOM_USART_RXPL_RXPL(value)       (SERCOM_USART_RXPL_RXPL_Msk & ((value) << SERCOM_USART_RXPL_RXPL_Pos))
#define SERCOM_USART_RXPL_MASK              _U_(0xFF)                                      /**< \deprecated (SERCOM_USART_RXPL) Register MASK  (Use SERCOM_USART_RXPL_Msk instead)  */
#define SERCOM_USART_RXPL_Msk               _U_(0xFF)                                      /**< (SERCOM_USART_RXPL) Register Mask  */


/* -------- SERCOM_I2CM_INTENCLR : (SERCOM Offset: 0x14) (R/W 8) I2CM Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  MB:1;                      /**< bit:      0  Master On Bus Interrupt Disable          */
    uint8_t  SB:1;                      /**< bit:      1  Slave On Bus Interrupt Disable           */
    uint8_t  :5;                        /**< bit:   2..6  Reserved */
    uint8_t  ERROR:1;                   /**< bit:      7  Combined Error Interrupt Disable         */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_I2CM_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_INTENCLR_OFFSET         (0x14)                                        /**<  (SERCOM_I2CM_INTENCLR) I2CM Interrupt Enable Clear  Offset */
#define SERCOM_I2CM_INTENCLR_RESETVALUE     _U_(0x00)                                     /**<  (SERCOM_I2CM_INTENCLR) I2CM Interrupt Enable Clear  Reset Value */

#define SERCOM_I2CM_INTENCLR_MB_Pos         0                                              /**< (SERCOM_I2CM_INTENCLR) Master On Bus Interrupt Disable Position */
#define SERCOM_I2CM_INTENCLR_MB_Msk         (_U_(0x1) << SERCOM_I2CM_INTENCLR_MB_Pos)      /**< (SERCOM_I2CM_INTENCLR) Master On Bus Interrupt Disable Mask */
#define SERCOM_I2CM_INTENCLR_MB             SERCOM_I2CM_INTENCLR_MB_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_INTENCLR_MB_Msk instead */
#define SERCOM_I2CM_INTENCLR_SB_Pos         1                                              /**< (SERCOM_I2CM_INTENCLR) Slave On Bus Interrupt Disable Position */
#define SERCOM_I2CM_INTENCLR_SB_Msk         (_U_(0x1) << SERCOM_I2CM_INTENCLR_SB_Pos)      /**< (SERCOM_I2CM_INTENCLR) Slave On Bus Interrupt Disable Mask */
#define SERCOM_I2CM_INTENCLR_SB             SERCOM_I2CM_INTENCLR_SB_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_INTENCLR_SB_Msk instead */
#define SERCOM_I2CM_INTENCLR_ERROR_Pos      7                                              /**< (SERCOM_I2CM_INTENCLR) Combined Error Interrupt Disable Position */
#define SERCOM_I2CM_INTENCLR_ERROR_Msk      (_U_(0x1) << SERCOM_I2CM_INTENCLR_ERROR_Pos)   /**< (SERCOM_I2CM_INTENCLR) Combined Error Interrupt Disable Mask */
#define SERCOM_I2CM_INTENCLR_ERROR          SERCOM_I2CM_INTENCLR_ERROR_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_INTENCLR_ERROR_Msk instead */
#define SERCOM_I2CM_INTENCLR_MASK           _U_(0x83)                                      /**< \deprecated (SERCOM_I2CM_INTENCLR) Register MASK  (Use SERCOM_I2CM_INTENCLR_Msk instead)  */
#define SERCOM_I2CM_INTENCLR_Msk            _U_(0x83)                                      /**< (SERCOM_I2CM_INTENCLR) Register Mask  */


/* -------- SERCOM_I2CS_INTENCLR : (SERCOM Offset: 0x14) (R/W 8) I2CS Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PREC:1;                    /**< bit:      0  Stop Received Interrupt Disable          */
    uint8_t  AMATCH:1;                  /**< bit:      1  Address Match Interrupt Disable          */
    uint8_t  DRDY:1;                    /**< bit:      2  Data Interrupt Disable                   */
    uint8_t  :4;                        /**< bit:   3..6  Reserved */
    uint8_t  ERROR:1;                   /**< bit:      7  Combined Error Interrupt Disable         */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_I2CS_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_INTENCLR_OFFSET         (0x14)                                        /**<  (SERCOM_I2CS_INTENCLR) I2CS Interrupt Enable Clear  Offset */
#define SERCOM_I2CS_INTENCLR_RESETVALUE     _U_(0x00)                                     /**<  (SERCOM_I2CS_INTENCLR) I2CS Interrupt Enable Clear  Reset Value */

#define SERCOM_I2CS_INTENCLR_PREC_Pos       0                                              /**< (SERCOM_I2CS_INTENCLR) Stop Received Interrupt Disable Position */
#define SERCOM_I2CS_INTENCLR_PREC_Msk       (_U_(0x1) << SERCOM_I2CS_INTENCLR_PREC_Pos)    /**< (SERCOM_I2CS_INTENCLR) Stop Received Interrupt Disable Mask */
#define SERCOM_I2CS_INTENCLR_PREC           SERCOM_I2CS_INTENCLR_PREC_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_INTENCLR_PREC_Msk instead */
#define SERCOM_I2CS_INTENCLR_AMATCH_Pos     1                                              /**< (SERCOM_I2CS_INTENCLR) Address Match Interrupt Disable Position */
#define SERCOM_I2CS_INTENCLR_AMATCH_Msk     (_U_(0x1) << SERCOM_I2CS_INTENCLR_AMATCH_Pos)  /**< (SERCOM_I2CS_INTENCLR) Address Match Interrupt Disable Mask */
#define SERCOM_I2CS_INTENCLR_AMATCH         SERCOM_I2CS_INTENCLR_AMATCH_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_INTENCLR_AMATCH_Msk instead */
#define SERCOM_I2CS_INTENCLR_DRDY_Pos       2                                              /**< (SERCOM_I2CS_INTENCLR) Data Interrupt Disable Position */
#define SERCOM_I2CS_INTENCLR_DRDY_Msk       (_U_(0x1) << SERCOM_I2CS_INTENCLR_DRDY_Pos)    /**< (SERCOM_I2CS_INTENCLR) Data Interrupt Disable Mask */
#define SERCOM_I2CS_INTENCLR_DRDY           SERCOM_I2CS_INTENCLR_DRDY_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_INTENCLR_DRDY_Msk instead */
#define SERCOM_I2CS_INTENCLR_ERROR_Pos      7                                              /**< (SERCOM_I2CS_INTENCLR) Combined Error Interrupt Disable Position */
#define SERCOM_I2CS_INTENCLR_ERROR_Msk      (_U_(0x1) << SERCOM_I2CS_INTENCLR_ERROR_Pos)   /**< (SERCOM_I2CS_INTENCLR) Combined Error Interrupt Disable Mask */
#define SERCOM_I2CS_INTENCLR_ERROR          SERCOM_I2CS_INTENCLR_ERROR_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_INTENCLR_ERROR_Msk instead */
#define SERCOM_I2CS_INTENCLR_MASK           _U_(0x87)                                      /**< \deprecated (SERCOM_I2CS_INTENCLR) Register MASK  (Use SERCOM_I2CS_INTENCLR_Msk instead)  */
#define SERCOM_I2CS_INTENCLR_Msk            _U_(0x87)                                      /**< (SERCOM_I2CS_INTENCLR) Register Mask  */


/* -------- SERCOM_SPI_INTENCLR : (SERCOM Offset: 0x14) (R/W 8) SPI Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DRE:1;                     /**< bit:      0  Data Register Empty Interrupt Disable    */
    uint8_t  TXC:1;                     /**< bit:      1  Transmit Complete Interrupt Disable      */
    uint8_t  RXC:1;                     /**< bit:      2  Receive Complete Interrupt Disable       */
    uint8_t  SSL:1;                     /**< bit:      3  Slave Select Low Interrupt Disable       */
    uint8_t  :3;                        /**< bit:   4..6  Reserved */
    uint8_t  ERROR:1;                   /**< bit:      7  Combined Error Interrupt Disable         */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_SPI_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_INTENCLR_OFFSET          (0x14)                                        /**<  (SERCOM_SPI_INTENCLR) SPI Interrupt Enable Clear  Offset */
#define SERCOM_SPI_INTENCLR_RESETVALUE      _U_(0x00)                                     /**<  (SERCOM_SPI_INTENCLR) SPI Interrupt Enable Clear  Reset Value */

#define SERCOM_SPI_INTENCLR_DRE_Pos         0                                              /**< (SERCOM_SPI_INTENCLR) Data Register Empty Interrupt Disable Position */
#define SERCOM_SPI_INTENCLR_DRE_Msk         (_U_(0x1) << SERCOM_SPI_INTENCLR_DRE_Pos)      /**< (SERCOM_SPI_INTENCLR) Data Register Empty Interrupt Disable Mask */
#define SERCOM_SPI_INTENCLR_DRE             SERCOM_SPI_INTENCLR_DRE_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_INTENCLR_DRE_Msk instead */
#define SERCOM_SPI_INTENCLR_TXC_Pos         1                                              /**< (SERCOM_SPI_INTENCLR) Transmit Complete Interrupt Disable Position */
#define SERCOM_SPI_INTENCLR_TXC_Msk         (_U_(0x1) << SERCOM_SPI_INTENCLR_TXC_Pos)      /**< (SERCOM_SPI_INTENCLR) Transmit Complete Interrupt Disable Mask */
#define SERCOM_SPI_INTENCLR_TXC             SERCOM_SPI_INTENCLR_TXC_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_INTENCLR_TXC_Msk instead */
#define SERCOM_SPI_INTENCLR_RXC_Pos         2                                              /**< (SERCOM_SPI_INTENCLR) Receive Complete Interrupt Disable Position */
#define SERCOM_SPI_INTENCLR_RXC_Msk         (_U_(0x1) << SERCOM_SPI_INTENCLR_RXC_Pos)      /**< (SERCOM_SPI_INTENCLR) Receive Complete Interrupt Disable Mask */
#define SERCOM_SPI_INTENCLR_RXC             SERCOM_SPI_INTENCLR_RXC_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_INTENCLR_RXC_Msk instead */
#define SERCOM_SPI_INTENCLR_SSL_Pos         3                                              /**< (SERCOM_SPI_INTENCLR) Slave Select Low Interrupt Disable Position */
#define SERCOM_SPI_INTENCLR_SSL_Msk         (_U_(0x1) << SERCOM_SPI_INTENCLR_SSL_Pos)      /**< (SERCOM_SPI_INTENCLR) Slave Select Low Interrupt Disable Mask */
#define SERCOM_SPI_INTENCLR_SSL             SERCOM_SPI_INTENCLR_SSL_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_INTENCLR_SSL_Msk instead */
#define SERCOM_SPI_INTENCLR_ERROR_Pos       7                                              /**< (SERCOM_SPI_INTENCLR) Combined Error Interrupt Disable Position */
#define SERCOM_SPI_INTENCLR_ERROR_Msk       (_U_(0x1) << SERCOM_SPI_INTENCLR_ERROR_Pos)    /**< (SERCOM_SPI_INTENCLR) Combined Error Interrupt Disable Mask */
#define SERCOM_SPI_INTENCLR_ERROR           SERCOM_SPI_INTENCLR_ERROR_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_INTENCLR_ERROR_Msk instead */
#define SERCOM_SPI_INTENCLR_MASK            _U_(0x8F)                                      /**< \deprecated (SERCOM_SPI_INTENCLR) Register MASK  (Use SERCOM_SPI_INTENCLR_Msk instead)  */
#define SERCOM_SPI_INTENCLR_Msk             _U_(0x8F)                                      /**< (SERCOM_SPI_INTENCLR) Register Mask  */


/* -------- SERCOM_USART_INTENCLR : (SERCOM Offset: 0x14) (R/W 8) USART Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DRE:1;                     /**< bit:      0  Data Register Empty Interrupt Disable    */
    uint8_t  TXC:1;                     /**< bit:      1  Transmit Complete Interrupt Disable      */
    uint8_t  RXC:1;                     /**< bit:      2  Receive Complete Interrupt Disable       */
    uint8_t  RXS:1;                     /**< bit:      3  Receive Start Interrupt Disable          */
    uint8_t  CTSIC:1;                   /**< bit:      4  Clear To Send Input Change Interrupt Disable */
    uint8_t  RXBRK:1;                   /**< bit:      5  Break Received Interrupt Disable         */
    uint8_t  :1;                        /**< bit:      6  Reserved */
    uint8_t  ERROR:1;                   /**< bit:      7  Combined Error Interrupt Disable         */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_USART_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_INTENCLR_OFFSET        (0x14)                                        /**<  (SERCOM_USART_INTENCLR) USART Interrupt Enable Clear  Offset */
#define SERCOM_USART_INTENCLR_RESETVALUE    _U_(0x00)                                     /**<  (SERCOM_USART_INTENCLR) USART Interrupt Enable Clear  Reset Value */

#define SERCOM_USART_INTENCLR_DRE_Pos       0                                              /**< (SERCOM_USART_INTENCLR) Data Register Empty Interrupt Disable Position */
#define SERCOM_USART_INTENCLR_DRE_Msk       (_U_(0x1) << SERCOM_USART_INTENCLR_DRE_Pos)    /**< (SERCOM_USART_INTENCLR) Data Register Empty Interrupt Disable Mask */
#define SERCOM_USART_INTENCLR_DRE           SERCOM_USART_INTENCLR_DRE_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTENCLR_DRE_Msk instead */
#define SERCOM_USART_INTENCLR_TXC_Pos       1                                              /**< (SERCOM_USART_INTENCLR) Transmit Complete Interrupt Disable Position */
#define SERCOM_USART_INTENCLR_TXC_Msk       (_U_(0x1) << SERCOM_USART_INTENCLR_TXC_Pos)    /**< (SERCOM_USART_INTENCLR) Transmit Complete Interrupt Disable Mask */
#define SERCOM_USART_INTENCLR_TXC           SERCOM_USART_INTENCLR_TXC_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTENCLR_TXC_Msk instead */
#define SERCOM_USART_INTENCLR_RXC_Pos       2                                              /**< (SERCOM_USART_INTENCLR) Receive Complete Interrupt Disable Position */
#define SERCOM_USART_INTENCLR_RXC_Msk       (_U_(0x1) << SERCOM_USART_INTENCLR_RXC_Pos)    /**< (SERCOM_USART_INTENCLR) Receive Complete Interrupt Disable Mask */
#define SERCOM_USART_INTENCLR_RXC           SERCOM_USART_INTENCLR_RXC_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTENCLR_RXC_Msk instead */
#define SERCOM_USART_INTENCLR_RXS_Pos       3                                              /**< (SERCOM_USART_INTENCLR) Receive Start Interrupt Disable Position */
#define SERCOM_USART_INTENCLR_RXS_Msk       (_U_(0x1) << SERCOM_USART_INTENCLR_RXS_Pos)    /**< (SERCOM_USART_INTENCLR) Receive Start Interrupt Disable Mask */
#define SERCOM_USART_INTENCLR_RXS           SERCOM_USART_INTENCLR_RXS_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTENCLR_RXS_Msk instead */
#define SERCOM_USART_INTENCLR_CTSIC_Pos     4                                              /**< (SERCOM_USART_INTENCLR) Clear To Send Input Change Interrupt Disable Position */
#define SERCOM_USART_INTENCLR_CTSIC_Msk     (_U_(0x1) << SERCOM_USART_INTENCLR_CTSIC_Pos)  /**< (SERCOM_USART_INTENCLR) Clear To Send Input Change Interrupt Disable Mask */
#define SERCOM_USART_INTENCLR_CTSIC         SERCOM_USART_INTENCLR_CTSIC_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTENCLR_CTSIC_Msk instead */
#define SERCOM_USART_INTENCLR_RXBRK_Pos     5                                              /**< (SERCOM_USART_INTENCLR) Break Received Interrupt Disable Position */
#define SERCOM_USART_INTENCLR_RXBRK_Msk     (_U_(0x1) << SERCOM_USART_INTENCLR_RXBRK_Pos)  /**< (SERCOM_USART_INTENCLR) Break Received Interrupt Disable Mask */
#define SERCOM_USART_INTENCLR_RXBRK         SERCOM_USART_INTENCLR_RXBRK_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTENCLR_RXBRK_Msk instead */
#define SERCOM_USART_INTENCLR_ERROR_Pos     7                                              /**< (SERCOM_USART_INTENCLR) Combined Error Interrupt Disable Position */
#define SERCOM_USART_INTENCLR_ERROR_Msk     (_U_(0x1) << SERCOM_USART_INTENCLR_ERROR_Pos)  /**< (SERCOM_USART_INTENCLR) Combined Error Interrupt Disable Mask */
#define SERCOM_USART_INTENCLR_ERROR         SERCOM_USART_INTENCLR_ERROR_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTENCLR_ERROR_Msk instead */
#define SERCOM_USART_INTENCLR_MASK          _U_(0xBF)                                      /**< \deprecated (SERCOM_USART_INTENCLR) Register MASK  (Use SERCOM_USART_INTENCLR_Msk instead)  */
#define SERCOM_USART_INTENCLR_Msk           _U_(0xBF)                                      /**< (SERCOM_USART_INTENCLR) Register Mask  */


/* -------- SERCOM_I2CM_INTENSET : (SERCOM Offset: 0x16) (R/W 8) I2CM Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  MB:1;                      /**< bit:      0  Master On Bus Interrupt Enable           */
    uint8_t  SB:1;                      /**< bit:      1  Slave On Bus Interrupt Enable            */
    uint8_t  :5;                        /**< bit:   2..6  Reserved */
    uint8_t  ERROR:1;                   /**< bit:      7  Combined Error Interrupt Enable          */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_I2CM_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_INTENSET_OFFSET         (0x16)                                        /**<  (SERCOM_I2CM_INTENSET) I2CM Interrupt Enable Set  Offset */
#define SERCOM_I2CM_INTENSET_RESETVALUE     _U_(0x00)                                     /**<  (SERCOM_I2CM_INTENSET) I2CM Interrupt Enable Set  Reset Value */

#define SERCOM_I2CM_INTENSET_MB_Pos         0                                              /**< (SERCOM_I2CM_INTENSET) Master On Bus Interrupt Enable Position */
#define SERCOM_I2CM_INTENSET_MB_Msk         (_U_(0x1) << SERCOM_I2CM_INTENSET_MB_Pos)      /**< (SERCOM_I2CM_INTENSET) Master On Bus Interrupt Enable Mask */
#define SERCOM_I2CM_INTENSET_MB             SERCOM_I2CM_INTENSET_MB_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_INTENSET_MB_Msk instead */
#define SERCOM_I2CM_INTENSET_SB_Pos         1                                              /**< (SERCOM_I2CM_INTENSET) Slave On Bus Interrupt Enable Position */
#define SERCOM_I2CM_INTENSET_SB_Msk         (_U_(0x1) << SERCOM_I2CM_INTENSET_SB_Pos)      /**< (SERCOM_I2CM_INTENSET) Slave On Bus Interrupt Enable Mask */
#define SERCOM_I2CM_INTENSET_SB             SERCOM_I2CM_INTENSET_SB_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_INTENSET_SB_Msk instead */
#define SERCOM_I2CM_INTENSET_ERROR_Pos      7                                              /**< (SERCOM_I2CM_INTENSET) Combined Error Interrupt Enable Position */
#define SERCOM_I2CM_INTENSET_ERROR_Msk      (_U_(0x1) << SERCOM_I2CM_INTENSET_ERROR_Pos)   /**< (SERCOM_I2CM_INTENSET) Combined Error Interrupt Enable Mask */
#define SERCOM_I2CM_INTENSET_ERROR          SERCOM_I2CM_INTENSET_ERROR_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_INTENSET_ERROR_Msk instead */
#define SERCOM_I2CM_INTENSET_MASK           _U_(0x83)                                      /**< \deprecated (SERCOM_I2CM_INTENSET) Register MASK  (Use SERCOM_I2CM_INTENSET_Msk instead)  */
#define SERCOM_I2CM_INTENSET_Msk            _U_(0x83)                                      /**< (SERCOM_I2CM_INTENSET) Register Mask  */


/* -------- SERCOM_I2CS_INTENSET : (SERCOM Offset: 0x16) (R/W 8) I2CS Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PREC:1;                    /**< bit:      0  Stop Received Interrupt Enable           */
    uint8_t  AMATCH:1;                  /**< bit:      1  Address Match Interrupt Enable           */
    uint8_t  DRDY:1;                    /**< bit:      2  Data Interrupt Enable                    */
    uint8_t  :4;                        /**< bit:   3..6  Reserved */
    uint8_t  ERROR:1;                   /**< bit:      7  Combined Error Interrupt Enable          */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_I2CS_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_INTENSET_OFFSET         (0x16)                                        /**<  (SERCOM_I2CS_INTENSET) I2CS Interrupt Enable Set  Offset */
#define SERCOM_I2CS_INTENSET_RESETVALUE     _U_(0x00)                                     /**<  (SERCOM_I2CS_INTENSET) I2CS Interrupt Enable Set  Reset Value */

#define SERCOM_I2CS_INTENSET_PREC_Pos       0                                              /**< (SERCOM_I2CS_INTENSET) Stop Received Interrupt Enable Position */
#define SERCOM_I2CS_INTENSET_PREC_Msk       (_U_(0x1) << SERCOM_I2CS_INTENSET_PREC_Pos)    /**< (SERCOM_I2CS_INTENSET) Stop Received Interrupt Enable Mask */
#define SERCOM_I2CS_INTENSET_PREC           SERCOM_I2CS_INTENSET_PREC_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_INTENSET_PREC_Msk instead */
#define SERCOM_I2CS_INTENSET_AMATCH_Pos     1                                              /**< (SERCOM_I2CS_INTENSET) Address Match Interrupt Enable Position */
#define SERCOM_I2CS_INTENSET_AMATCH_Msk     (_U_(0x1) << SERCOM_I2CS_INTENSET_AMATCH_Pos)  /**< (SERCOM_I2CS_INTENSET) Address Match Interrupt Enable Mask */
#define SERCOM_I2CS_INTENSET_AMATCH         SERCOM_I2CS_INTENSET_AMATCH_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_INTENSET_AMATCH_Msk instead */
#define SERCOM_I2CS_INTENSET_DRDY_Pos       2                                              /**< (SERCOM_I2CS_INTENSET) Data Interrupt Enable Position */
#define SERCOM_I2CS_INTENSET_DRDY_Msk       (_U_(0x1) << SERCOM_I2CS_INTENSET_DRDY_Pos)    /**< (SERCOM_I2CS_INTENSET) Data Interrupt Enable Mask */
#define SERCOM_I2CS_INTENSET_DRDY           SERCOM_I2CS_INTENSET_DRDY_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_INTENSET_DRDY_Msk instead */
#define SERCOM_I2CS_INTENSET_ERROR_Pos      7                                              /**< (SERCOM_I2CS_INTENSET) Combined Error Interrupt Enable Position */
#define SERCOM_I2CS_INTENSET_ERROR_Msk      (_U_(0x1) << SERCOM_I2CS_INTENSET_ERROR_Pos)   /**< (SERCOM_I2CS_INTENSET) Combined Error Interrupt Enable Mask */
#define SERCOM_I2CS_INTENSET_ERROR          SERCOM_I2CS_INTENSET_ERROR_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_INTENSET_ERROR_Msk instead */
#define SERCOM_I2CS_INTENSET_MASK           _U_(0x87)                                      /**< \deprecated (SERCOM_I2CS_INTENSET) Register MASK  (Use SERCOM_I2CS_INTENSET_Msk instead)  */
#define SERCOM_I2CS_INTENSET_Msk            _U_(0x87)                                      /**< (SERCOM_I2CS_INTENSET) Register Mask  */


/* -------- SERCOM_SPI_INTENSET : (SERCOM Offset: 0x16) (R/W 8) SPI Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DRE:1;                     /**< bit:      0  Data Register Empty Interrupt Enable     */
    uint8_t  TXC:1;                     /**< bit:      1  Transmit Complete Interrupt Enable       */
    uint8_t  RXC:1;                     /**< bit:      2  Receive Complete Interrupt Enable        */
    uint8_t  SSL:1;                     /**< bit:      3  Slave Select Low Interrupt Enable        */
    uint8_t  :3;                        /**< bit:   4..6  Reserved */
    uint8_t  ERROR:1;                   /**< bit:      7  Combined Error Interrupt Enable          */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_SPI_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_INTENSET_OFFSET          (0x16)                                        /**<  (SERCOM_SPI_INTENSET) SPI Interrupt Enable Set  Offset */
#define SERCOM_SPI_INTENSET_RESETVALUE      _U_(0x00)                                     /**<  (SERCOM_SPI_INTENSET) SPI Interrupt Enable Set  Reset Value */

#define SERCOM_SPI_INTENSET_DRE_Pos         0                                              /**< (SERCOM_SPI_INTENSET) Data Register Empty Interrupt Enable Position */
#define SERCOM_SPI_INTENSET_DRE_Msk         (_U_(0x1) << SERCOM_SPI_INTENSET_DRE_Pos)      /**< (SERCOM_SPI_INTENSET) Data Register Empty Interrupt Enable Mask */
#define SERCOM_SPI_INTENSET_DRE             SERCOM_SPI_INTENSET_DRE_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_INTENSET_DRE_Msk instead */
#define SERCOM_SPI_INTENSET_TXC_Pos         1                                              /**< (SERCOM_SPI_INTENSET) Transmit Complete Interrupt Enable Position */
#define SERCOM_SPI_INTENSET_TXC_Msk         (_U_(0x1) << SERCOM_SPI_INTENSET_TXC_Pos)      /**< (SERCOM_SPI_INTENSET) Transmit Complete Interrupt Enable Mask */
#define SERCOM_SPI_INTENSET_TXC             SERCOM_SPI_INTENSET_TXC_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_INTENSET_TXC_Msk instead */
#define SERCOM_SPI_INTENSET_RXC_Pos         2                                              /**< (SERCOM_SPI_INTENSET) Receive Complete Interrupt Enable Position */
#define SERCOM_SPI_INTENSET_RXC_Msk         (_U_(0x1) << SERCOM_SPI_INTENSET_RXC_Pos)      /**< (SERCOM_SPI_INTENSET) Receive Complete Interrupt Enable Mask */
#define SERCOM_SPI_INTENSET_RXC             SERCOM_SPI_INTENSET_RXC_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_INTENSET_RXC_Msk instead */
#define SERCOM_SPI_INTENSET_SSL_Pos         3                                              /**< (SERCOM_SPI_INTENSET) Slave Select Low Interrupt Enable Position */
#define SERCOM_SPI_INTENSET_SSL_Msk         (_U_(0x1) << SERCOM_SPI_INTENSET_SSL_Pos)      /**< (SERCOM_SPI_INTENSET) Slave Select Low Interrupt Enable Mask */
#define SERCOM_SPI_INTENSET_SSL             SERCOM_SPI_INTENSET_SSL_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_INTENSET_SSL_Msk instead */
#define SERCOM_SPI_INTENSET_ERROR_Pos       7                                              /**< (SERCOM_SPI_INTENSET) Combined Error Interrupt Enable Position */
#define SERCOM_SPI_INTENSET_ERROR_Msk       (_U_(0x1) << SERCOM_SPI_INTENSET_ERROR_Pos)    /**< (SERCOM_SPI_INTENSET) Combined Error Interrupt Enable Mask */
#define SERCOM_SPI_INTENSET_ERROR           SERCOM_SPI_INTENSET_ERROR_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_INTENSET_ERROR_Msk instead */
#define SERCOM_SPI_INTENSET_MASK            _U_(0x8F)                                      /**< \deprecated (SERCOM_SPI_INTENSET) Register MASK  (Use SERCOM_SPI_INTENSET_Msk instead)  */
#define SERCOM_SPI_INTENSET_Msk             _U_(0x8F)                                      /**< (SERCOM_SPI_INTENSET) Register Mask  */


/* -------- SERCOM_USART_INTENSET : (SERCOM Offset: 0x16) (R/W 8) USART Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DRE:1;                     /**< bit:      0  Data Register Empty Interrupt Enable     */
    uint8_t  TXC:1;                     /**< bit:      1  Transmit Complete Interrupt Enable       */
    uint8_t  RXC:1;                     /**< bit:      2  Receive Complete Interrupt Enable        */
    uint8_t  RXS:1;                     /**< bit:      3  Receive Start Interrupt Enable           */
    uint8_t  CTSIC:1;                   /**< bit:      4  Clear To Send Input Change Interrupt Enable */
    uint8_t  RXBRK:1;                   /**< bit:      5  Break Received Interrupt Enable          */
    uint8_t  :1;                        /**< bit:      6  Reserved */
    uint8_t  ERROR:1;                   /**< bit:      7  Combined Error Interrupt Enable          */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_USART_INTENSET_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_INTENSET_OFFSET        (0x16)                                        /**<  (SERCOM_USART_INTENSET) USART Interrupt Enable Set  Offset */
#define SERCOM_USART_INTENSET_RESETVALUE    _U_(0x00)                                     /**<  (SERCOM_USART_INTENSET) USART Interrupt Enable Set  Reset Value */

#define SERCOM_USART_INTENSET_DRE_Pos       0                                              /**< (SERCOM_USART_INTENSET) Data Register Empty Interrupt Enable Position */
#define SERCOM_USART_INTENSET_DRE_Msk       (_U_(0x1) << SERCOM_USART_INTENSET_DRE_Pos)    /**< (SERCOM_USART_INTENSET) Data Register Empty Interrupt Enable Mask */
#define SERCOM_USART_INTENSET_DRE           SERCOM_USART_INTENSET_DRE_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTENSET_DRE_Msk instead */
#define SERCOM_USART_INTENSET_TXC_Pos       1                                              /**< (SERCOM_USART_INTENSET) Transmit Complete Interrupt Enable Position */
#define SERCOM_USART_INTENSET_TXC_Msk       (_U_(0x1) << SERCOM_USART_INTENSET_TXC_Pos)    /**< (SERCOM_USART_INTENSET) Transmit Complete Interrupt Enable Mask */
#define SERCOM_USART_INTENSET_TXC           SERCOM_USART_INTENSET_TXC_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTENSET_TXC_Msk instead */
#define SERCOM_USART_INTENSET_RXC_Pos       2                                              /**< (SERCOM_USART_INTENSET) Receive Complete Interrupt Enable Position */
#define SERCOM_USART_INTENSET_RXC_Msk       (_U_(0x1) << SERCOM_USART_INTENSET_RXC_Pos)    /**< (SERCOM_USART_INTENSET) Receive Complete Interrupt Enable Mask */
#define SERCOM_USART_INTENSET_RXC           SERCOM_USART_INTENSET_RXC_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTENSET_RXC_Msk instead */
#define SERCOM_USART_INTENSET_RXS_Pos       3                                              /**< (SERCOM_USART_INTENSET) Receive Start Interrupt Enable Position */
#define SERCOM_USART_INTENSET_RXS_Msk       (_U_(0x1) << SERCOM_USART_INTENSET_RXS_Pos)    /**< (SERCOM_USART_INTENSET) Receive Start Interrupt Enable Mask */
#define SERCOM_USART_INTENSET_RXS           SERCOM_USART_INTENSET_RXS_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTENSET_RXS_Msk instead */
#define SERCOM_USART_INTENSET_CTSIC_Pos     4                                              /**< (SERCOM_USART_INTENSET) Clear To Send Input Change Interrupt Enable Position */
#define SERCOM_USART_INTENSET_CTSIC_Msk     (_U_(0x1) << SERCOM_USART_INTENSET_CTSIC_Pos)  /**< (SERCOM_USART_INTENSET) Clear To Send Input Change Interrupt Enable Mask */
#define SERCOM_USART_INTENSET_CTSIC         SERCOM_USART_INTENSET_CTSIC_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTENSET_CTSIC_Msk instead */
#define SERCOM_USART_INTENSET_RXBRK_Pos     5                                              /**< (SERCOM_USART_INTENSET) Break Received Interrupt Enable Position */
#define SERCOM_USART_INTENSET_RXBRK_Msk     (_U_(0x1) << SERCOM_USART_INTENSET_RXBRK_Pos)  /**< (SERCOM_USART_INTENSET) Break Received Interrupt Enable Mask */
#define SERCOM_USART_INTENSET_RXBRK         SERCOM_USART_INTENSET_RXBRK_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTENSET_RXBRK_Msk instead */
#define SERCOM_USART_INTENSET_ERROR_Pos     7                                              /**< (SERCOM_USART_INTENSET) Combined Error Interrupt Enable Position */
#define SERCOM_USART_INTENSET_ERROR_Msk     (_U_(0x1) << SERCOM_USART_INTENSET_ERROR_Pos)  /**< (SERCOM_USART_INTENSET) Combined Error Interrupt Enable Mask */
#define SERCOM_USART_INTENSET_ERROR         SERCOM_USART_INTENSET_ERROR_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTENSET_ERROR_Msk instead */
#define SERCOM_USART_INTENSET_MASK          _U_(0xBF)                                      /**< \deprecated (SERCOM_USART_INTENSET) Register MASK  (Use SERCOM_USART_INTENSET_Msk instead)  */
#define SERCOM_USART_INTENSET_Msk           _U_(0xBF)                                      /**< (SERCOM_USART_INTENSET) Register Mask  */


/* -------- SERCOM_I2CM_INTFLAG : (SERCOM Offset: 0x18) (R/W 8) I2CM Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t MB:1;                      /**< bit:      0  Master On Bus Interrupt                  */
    __I uint8_t SB:1;                      /**< bit:      1  Slave On Bus Interrupt                   */
    __I uint8_t :5;                        /**< bit:   2..6  Reserved */
    __I uint8_t ERROR:1;                   /**< bit:      7  Combined Error Interrupt                 */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_I2CM_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_INTFLAG_OFFSET          (0x18)                                        /**<  (SERCOM_I2CM_INTFLAG) I2CM Interrupt Flag Status and Clear  Offset */
#define SERCOM_I2CM_INTFLAG_RESETVALUE      _U_(0x00)                                     /**<  (SERCOM_I2CM_INTFLAG) I2CM Interrupt Flag Status and Clear  Reset Value */

#define SERCOM_I2CM_INTFLAG_MB_Pos          0                                              /**< (SERCOM_I2CM_INTFLAG) Master On Bus Interrupt Position */
#define SERCOM_I2CM_INTFLAG_MB_Msk          (_U_(0x1) << SERCOM_I2CM_INTFLAG_MB_Pos)       /**< (SERCOM_I2CM_INTFLAG) Master On Bus Interrupt Mask */
#define SERCOM_I2CM_INTFLAG_MB              SERCOM_I2CM_INTFLAG_MB_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_INTFLAG_MB_Msk instead */
#define SERCOM_I2CM_INTFLAG_SB_Pos          1                                              /**< (SERCOM_I2CM_INTFLAG) Slave On Bus Interrupt Position */
#define SERCOM_I2CM_INTFLAG_SB_Msk          (_U_(0x1) << SERCOM_I2CM_INTFLAG_SB_Pos)       /**< (SERCOM_I2CM_INTFLAG) Slave On Bus Interrupt Mask */
#define SERCOM_I2CM_INTFLAG_SB              SERCOM_I2CM_INTFLAG_SB_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_INTFLAG_SB_Msk instead */
#define SERCOM_I2CM_INTFLAG_ERROR_Pos       7                                              /**< (SERCOM_I2CM_INTFLAG) Combined Error Interrupt Position */
#define SERCOM_I2CM_INTFLAG_ERROR_Msk       (_U_(0x1) << SERCOM_I2CM_INTFLAG_ERROR_Pos)    /**< (SERCOM_I2CM_INTFLAG) Combined Error Interrupt Mask */
#define SERCOM_I2CM_INTFLAG_ERROR           SERCOM_I2CM_INTFLAG_ERROR_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_INTFLAG_ERROR_Msk instead */
#define SERCOM_I2CM_INTFLAG_MASK            _U_(0x83)                                      /**< \deprecated (SERCOM_I2CM_INTFLAG) Register MASK  (Use SERCOM_I2CM_INTFLAG_Msk instead)  */
#define SERCOM_I2CM_INTFLAG_Msk             _U_(0x83)                                      /**< (SERCOM_I2CM_INTFLAG) Register Mask  */


/* -------- SERCOM_I2CS_INTFLAG : (SERCOM Offset: 0x18) (R/W 8) I2CS Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t PREC:1;                    /**< bit:      0  Stop Received Interrupt                  */
    __I uint8_t AMATCH:1;                  /**< bit:      1  Address Match Interrupt                  */
    __I uint8_t DRDY:1;                    /**< bit:      2  Data Interrupt                           */
    __I uint8_t :4;                        /**< bit:   3..6  Reserved */
    __I uint8_t ERROR:1;                   /**< bit:      7  Combined Error Interrupt                 */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_I2CS_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_INTFLAG_OFFSET          (0x18)                                        /**<  (SERCOM_I2CS_INTFLAG) I2CS Interrupt Flag Status and Clear  Offset */
#define SERCOM_I2CS_INTFLAG_RESETVALUE      _U_(0x00)                                     /**<  (SERCOM_I2CS_INTFLAG) I2CS Interrupt Flag Status and Clear  Reset Value */

#define SERCOM_I2CS_INTFLAG_PREC_Pos        0                                              /**< (SERCOM_I2CS_INTFLAG) Stop Received Interrupt Position */
#define SERCOM_I2CS_INTFLAG_PREC_Msk        (_U_(0x1) << SERCOM_I2CS_INTFLAG_PREC_Pos)     /**< (SERCOM_I2CS_INTFLAG) Stop Received Interrupt Mask */
#define SERCOM_I2CS_INTFLAG_PREC            SERCOM_I2CS_INTFLAG_PREC_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_INTFLAG_PREC_Msk instead */
#define SERCOM_I2CS_INTFLAG_AMATCH_Pos      1                                              /**< (SERCOM_I2CS_INTFLAG) Address Match Interrupt Position */
#define SERCOM_I2CS_INTFLAG_AMATCH_Msk      (_U_(0x1) << SERCOM_I2CS_INTFLAG_AMATCH_Pos)   /**< (SERCOM_I2CS_INTFLAG) Address Match Interrupt Mask */
#define SERCOM_I2CS_INTFLAG_AMATCH          SERCOM_I2CS_INTFLAG_AMATCH_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_INTFLAG_AMATCH_Msk instead */
#define SERCOM_I2CS_INTFLAG_DRDY_Pos        2                                              /**< (SERCOM_I2CS_INTFLAG) Data Interrupt Position */
#define SERCOM_I2CS_INTFLAG_DRDY_Msk        (_U_(0x1) << SERCOM_I2CS_INTFLAG_DRDY_Pos)     /**< (SERCOM_I2CS_INTFLAG) Data Interrupt Mask */
#define SERCOM_I2CS_INTFLAG_DRDY            SERCOM_I2CS_INTFLAG_DRDY_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_INTFLAG_DRDY_Msk instead */
#define SERCOM_I2CS_INTFLAG_ERROR_Pos       7                                              /**< (SERCOM_I2CS_INTFLAG) Combined Error Interrupt Position */
#define SERCOM_I2CS_INTFLAG_ERROR_Msk       (_U_(0x1) << SERCOM_I2CS_INTFLAG_ERROR_Pos)    /**< (SERCOM_I2CS_INTFLAG) Combined Error Interrupt Mask */
#define SERCOM_I2CS_INTFLAG_ERROR           SERCOM_I2CS_INTFLAG_ERROR_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_INTFLAG_ERROR_Msk instead */
#define SERCOM_I2CS_INTFLAG_MASK            _U_(0x87)                                      /**< \deprecated (SERCOM_I2CS_INTFLAG) Register MASK  (Use SERCOM_I2CS_INTFLAG_Msk instead)  */
#define SERCOM_I2CS_INTFLAG_Msk             _U_(0x87)                                      /**< (SERCOM_I2CS_INTFLAG) Register Mask  */


/* -------- SERCOM_SPI_INTFLAG : (SERCOM Offset: 0x18) (R/W 8) SPI Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t DRE:1;                     /**< bit:      0  Data Register Empty Interrupt            */
    __I uint8_t TXC:1;                     /**< bit:      1  Transmit Complete Interrupt              */
    __I uint8_t RXC:1;                     /**< bit:      2  Receive Complete Interrupt               */
    __I uint8_t SSL:1;                     /**< bit:      3  Slave Select Low Interrupt Flag          */
    __I uint8_t :3;                        /**< bit:   4..6  Reserved */
    __I uint8_t ERROR:1;                   /**< bit:      7  Combined Error Interrupt                 */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_SPI_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_INTFLAG_OFFSET           (0x18)                                        /**<  (SERCOM_SPI_INTFLAG) SPI Interrupt Flag Status and Clear  Offset */
#define SERCOM_SPI_INTFLAG_RESETVALUE       _U_(0x00)                                     /**<  (SERCOM_SPI_INTFLAG) SPI Interrupt Flag Status and Clear  Reset Value */

#define SERCOM_SPI_INTFLAG_DRE_Pos          0                                              /**< (SERCOM_SPI_INTFLAG) Data Register Empty Interrupt Position */
#define SERCOM_SPI_INTFLAG_DRE_Msk          (_U_(0x1) << SERCOM_SPI_INTFLAG_DRE_Pos)       /**< (SERCOM_SPI_INTFLAG) Data Register Empty Interrupt Mask */
#define SERCOM_SPI_INTFLAG_DRE              SERCOM_SPI_INTFLAG_DRE_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_INTFLAG_DRE_Msk instead */
#define SERCOM_SPI_INTFLAG_TXC_Pos          1                                              /**< (SERCOM_SPI_INTFLAG) Transmit Complete Interrupt Position */
#define SERCOM_SPI_INTFLAG_TXC_Msk          (_U_(0x1) << SERCOM_SPI_INTFLAG_TXC_Pos)       /**< (SERCOM_SPI_INTFLAG) Transmit Complete Interrupt Mask */
#define SERCOM_SPI_INTFLAG_TXC              SERCOM_SPI_INTFLAG_TXC_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_INTFLAG_TXC_Msk instead */
#define SERCOM_SPI_INTFLAG_RXC_Pos          2                                              /**< (SERCOM_SPI_INTFLAG) Receive Complete Interrupt Position */
#define SERCOM_SPI_INTFLAG_RXC_Msk          (_U_(0x1) << SERCOM_SPI_INTFLAG_RXC_Pos)       /**< (SERCOM_SPI_INTFLAG) Receive Complete Interrupt Mask */
#define SERCOM_SPI_INTFLAG_RXC              SERCOM_SPI_INTFLAG_RXC_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_INTFLAG_RXC_Msk instead */
#define SERCOM_SPI_INTFLAG_SSL_Pos          3                                              /**< (SERCOM_SPI_INTFLAG) Slave Select Low Interrupt Flag Position */
#define SERCOM_SPI_INTFLAG_SSL_Msk          (_U_(0x1) << SERCOM_SPI_INTFLAG_SSL_Pos)       /**< (SERCOM_SPI_INTFLAG) Slave Select Low Interrupt Flag Mask */
#define SERCOM_SPI_INTFLAG_SSL              SERCOM_SPI_INTFLAG_SSL_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_INTFLAG_SSL_Msk instead */
#define SERCOM_SPI_INTFLAG_ERROR_Pos        7                                              /**< (SERCOM_SPI_INTFLAG) Combined Error Interrupt Position */
#define SERCOM_SPI_INTFLAG_ERROR_Msk        (_U_(0x1) << SERCOM_SPI_INTFLAG_ERROR_Pos)     /**< (SERCOM_SPI_INTFLAG) Combined Error Interrupt Mask */
#define SERCOM_SPI_INTFLAG_ERROR            SERCOM_SPI_INTFLAG_ERROR_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_INTFLAG_ERROR_Msk instead */
#define SERCOM_SPI_INTFLAG_MASK             _U_(0x8F)                                      /**< \deprecated (SERCOM_SPI_INTFLAG) Register MASK  (Use SERCOM_SPI_INTFLAG_Msk instead)  */
#define SERCOM_SPI_INTFLAG_Msk              _U_(0x8F)                                      /**< (SERCOM_SPI_INTFLAG) Register Mask  */


/* -------- SERCOM_USART_INTFLAG : (SERCOM Offset: 0x18) (R/W 8) USART Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t DRE:1;                     /**< bit:      0  Data Register Empty Interrupt            */
    __I uint8_t TXC:1;                     /**< bit:      1  Transmit Complete Interrupt              */
    __I uint8_t RXC:1;                     /**< bit:      2  Receive Complete Interrupt               */
    __I uint8_t RXS:1;                     /**< bit:      3  Receive Start Interrupt                  */
    __I uint8_t CTSIC:1;                   /**< bit:      4  Clear To Send Input Change Interrupt     */
    __I uint8_t RXBRK:1;                   /**< bit:      5  Break Received Interrupt                 */
    __I uint8_t :1;                        /**< bit:      6  Reserved */
    __I uint8_t ERROR:1;                   /**< bit:      7  Combined Error Interrupt                 */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_USART_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_INTFLAG_OFFSET         (0x18)                                        /**<  (SERCOM_USART_INTFLAG) USART Interrupt Flag Status and Clear  Offset */
#define SERCOM_USART_INTFLAG_RESETVALUE     _U_(0x00)                                     /**<  (SERCOM_USART_INTFLAG) USART Interrupt Flag Status and Clear  Reset Value */

#define SERCOM_USART_INTFLAG_DRE_Pos        0                                              /**< (SERCOM_USART_INTFLAG) Data Register Empty Interrupt Position */
#define SERCOM_USART_INTFLAG_DRE_Msk        (_U_(0x1) << SERCOM_USART_INTFLAG_DRE_Pos)     /**< (SERCOM_USART_INTFLAG) Data Register Empty Interrupt Mask */
#define SERCOM_USART_INTFLAG_DRE            SERCOM_USART_INTFLAG_DRE_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTFLAG_DRE_Msk instead */
#define SERCOM_USART_INTFLAG_TXC_Pos        1                                              /**< (SERCOM_USART_INTFLAG) Transmit Complete Interrupt Position */
#define SERCOM_USART_INTFLAG_TXC_Msk        (_U_(0x1) << SERCOM_USART_INTFLAG_TXC_Pos)     /**< (SERCOM_USART_INTFLAG) Transmit Complete Interrupt Mask */
#define SERCOM_USART_INTFLAG_TXC            SERCOM_USART_INTFLAG_TXC_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTFLAG_TXC_Msk instead */
#define SERCOM_USART_INTFLAG_RXC_Pos        2                                              /**< (SERCOM_USART_INTFLAG) Receive Complete Interrupt Position */
#define SERCOM_USART_INTFLAG_RXC_Msk        (_U_(0x1) << SERCOM_USART_INTFLAG_RXC_Pos)     /**< (SERCOM_USART_INTFLAG) Receive Complete Interrupt Mask */
#define SERCOM_USART_INTFLAG_RXC            SERCOM_USART_INTFLAG_RXC_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTFLAG_RXC_Msk instead */
#define SERCOM_USART_INTFLAG_RXS_Pos        3                                              /**< (SERCOM_USART_INTFLAG) Receive Start Interrupt Position */
#define SERCOM_USART_INTFLAG_RXS_Msk        (_U_(0x1) << SERCOM_USART_INTFLAG_RXS_Pos)     /**< (SERCOM_USART_INTFLAG) Receive Start Interrupt Mask */
#define SERCOM_USART_INTFLAG_RXS            SERCOM_USART_INTFLAG_RXS_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTFLAG_RXS_Msk instead */
#define SERCOM_USART_INTFLAG_CTSIC_Pos      4                                              /**< (SERCOM_USART_INTFLAG) Clear To Send Input Change Interrupt Position */
#define SERCOM_USART_INTFLAG_CTSIC_Msk      (_U_(0x1) << SERCOM_USART_INTFLAG_CTSIC_Pos)   /**< (SERCOM_USART_INTFLAG) Clear To Send Input Change Interrupt Mask */
#define SERCOM_USART_INTFLAG_CTSIC          SERCOM_USART_INTFLAG_CTSIC_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTFLAG_CTSIC_Msk instead */
#define SERCOM_USART_INTFLAG_RXBRK_Pos      5                                              /**< (SERCOM_USART_INTFLAG) Break Received Interrupt Position */
#define SERCOM_USART_INTFLAG_RXBRK_Msk      (_U_(0x1) << SERCOM_USART_INTFLAG_RXBRK_Pos)   /**< (SERCOM_USART_INTFLAG) Break Received Interrupt Mask */
#define SERCOM_USART_INTFLAG_RXBRK          SERCOM_USART_INTFLAG_RXBRK_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTFLAG_RXBRK_Msk instead */
#define SERCOM_USART_INTFLAG_ERROR_Pos      7                                              /**< (SERCOM_USART_INTFLAG) Combined Error Interrupt Position */
#define SERCOM_USART_INTFLAG_ERROR_Msk      (_U_(0x1) << SERCOM_USART_INTFLAG_ERROR_Pos)   /**< (SERCOM_USART_INTFLAG) Combined Error Interrupt Mask */
#define SERCOM_USART_INTFLAG_ERROR          SERCOM_USART_INTFLAG_ERROR_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_INTFLAG_ERROR_Msk instead */
#define SERCOM_USART_INTFLAG_MASK           _U_(0xBF)                                      /**< \deprecated (SERCOM_USART_INTFLAG) Register MASK  (Use SERCOM_USART_INTFLAG_Msk instead)  */
#define SERCOM_USART_INTFLAG_Msk            _U_(0xBF)                                      /**< (SERCOM_USART_INTFLAG) Register Mask  */


/* -------- SERCOM_I2CM_STATUS : (SERCOM Offset: 0x1a) (R/W 16) I2CM Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t BUSERR:1;                  /**< bit:      0  Bus Error                                */
    uint16_t ARBLOST:1;                 /**< bit:      1  Arbitration Lost                         */
    uint16_t RXNACK:1;                  /**< bit:      2  Received Not Acknowledge                 */
    uint16_t :1;                        /**< bit:      3  Reserved */
    uint16_t BUSSTATE:2;                /**< bit:   4..5  Bus State                                */
    uint16_t LOWTOUT:1;                 /**< bit:      6  SCL Low Timeout                          */
    uint16_t CLKHOLD:1;                 /**< bit:      7  Clock Hold                               */
    uint16_t MEXTTOUT:1;                /**< bit:      8  Master SCL Low Extend Timeout            */
    uint16_t SEXTTOUT:1;                /**< bit:      9  Slave SCL Low Extend Timeout             */
    uint16_t LENERR:1;                  /**< bit:     10  Length Error                             */
    uint16_t :5;                        /**< bit: 11..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} SERCOM_I2CM_STATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_STATUS_OFFSET           (0x1A)                                        /**<  (SERCOM_I2CM_STATUS) I2CM Status  Offset */
#define SERCOM_I2CM_STATUS_RESETVALUE       _U_(0x00)                                     /**<  (SERCOM_I2CM_STATUS) I2CM Status  Reset Value */

#define SERCOM_I2CM_STATUS_BUSERR_Pos       0                                              /**< (SERCOM_I2CM_STATUS) Bus Error Position */
#define SERCOM_I2CM_STATUS_BUSERR_Msk       (_U_(0x1) << SERCOM_I2CM_STATUS_BUSERR_Pos)    /**< (SERCOM_I2CM_STATUS) Bus Error Mask */
#define SERCOM_I2CM_STATUS_BUSERR           SERCOM_I2CM_STATUS_BUSERR_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_STATUS_BUSERR_Msk instead */
#define SERCOM_I2CM_STATUS_ARBLOST_Pos      1                                              /**< (SERCOM_I2CM_STATUS) Arbitration Lost Position */
#define SERCOM_I2CM_STATUS_ARBLOST_Msk      (_U_(0x1) << SERCOM_I2CM_STATUS_ARBLOST_Pos)   /**< (SERCOM_I2CM_STATUS) Arbitration Lost Mask */
#define SERCOM_I2CM_STATUS_ARBLOST          SERCOM_I2CM_STATUS_ARBLOST_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_STATUS_ARBLOST_Msk instead */
#define SERCOM_I2CM_STATUS_RXNACK_Pos       2                                              /**< (SERCOM_I2CM_STATUS) Received Not Acknowledge Position */
#define SERCOM_I2CM_STATUS_RXNACK_Msk       (_U_(0x1) << SERCOM_I2CM_STATUS_RXNACK_Pos)    /**< (SERCOM_I2CM_STATUS) Received Not Acknowledge Mask */
#define SERCOM_I2CM_STATUS_RXNACK           SERCOM_I2CM_STATUS_RXNACK_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_STATUS_RXNACK_Msk instead */
#define SERCOM_I2CM_STATUS_BUSSTATE_Pos     4                                              /**< (SERCOM_I2CM_STATUS) Bus State Position */
#define SERCOM_I2CM_STATUS_BUSSTATE_Msk     (_U_(0x3) << SERCOM_I2CM_STATUS_BUSSTATE_Pos)  /**< (SERCOM_I2CM_STATUS) Bus State Mask */
#define SERCOM_I2CM_STATUS_BUSSTATE(value)  (SERCOM_I2CM_STATUS_BUSSTATE_Msk & ((value) << SERCOM_I2CM_STATUS_BUSSTATE_Pos))
#define SERCOM_I2CM_STATUS_LOWTOUT_Pos      6                                              /**< (SERCOM_I2CM_STATUS) SCL Low Timeout Position */
#define SERCOM_I2CM_STATUS_LOWTOUT_Msk      (_U_(0x1) << SERCOM_I2CM_STATUS_LOWTOUT_Pos)   /**< (SERCOM_I2CM_STATUS) SCL Low Timeout Mask */
#define SERCOM_I2CM_STATUS_LOWTOUT          SERCOM_I2CM_STATUS_LOWTOUT_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_STATUS_LOWTOUT_Msk instead */
#define SERCOM_I2CM_STATUS_CLKHOLD_Pos      7                                              /**< (SERCOM_I2CM_STATUS) Clock Hold Position */
#define SERCOM_I2CM_STATUS_CLKHOLD_Msk      (_U_(0x1) << SERCOM_I2CM_STATUS_CLKHOLD_Pos)   /**< (SERCOM_I2CM_STATUS) Clock Hold Mask */
#define SERCOM_I2CM_STATUS_CLKHOLD          SERCOM_I2CM_STATUS_CLKHOLD_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_STATUS_CLKHOLD_Msk instead */
#define SERCOM_I2CM_STATUS_MEXTTOUT_Pos     8                                              /**< (SERCOM_I2CM_STATUS) Master SCL Low Extend Timeout Position */
#define SERCOM_I2CM_STATUS_MEXTTOUT_Msk     (_U_(0x1) << SERCOM_I2CM_STATUS_MEXTTOUT_Pos)  /**< (SERCOM_I2CM_STATUS) Master SCL Low Extend Timeout Mask */
#define SERCOM_I2CM_STATUS_MEXTTOUT         SERCOM_I2CM_STATUS_MEXTTOUT_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_STATUS_MEXTTOUT_Msk instead */
#define SERCOM_I2CM_STATUS_SEXTTOUT_Pos     9                                              /**< (SERCOM_I2CM_STATUS) Slave SCL Low Extend Timeout Position */
#define SERCOM_I2CM_STATUS_SEXTTOUT_Msk     (_U_(0x1) << SERCOM_I2CM_STATUS_SEXTTOUT_Pos)  /**< (SERCOM_I2CM_STATUS) Slave SCL Low Extend Timeout Mask */
#define SERCOM_I2CM_STATUS_SEXTTOUT         SERCOM_I2CM_STATUS_SEXTTOUT_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_STATUS_SEXTTOUT_Msk instead */
#define SERCOM_I2CM_STATUS_LENERR_Pos       10                                             /**< (SERCOM_I2CM_STATUS) Length Error Position */
#define SERCOM_I2CM_STATUS_LENERR_Msk       (_U_(0x1) << SERCOM_I2CM_STATUS_LENERR_Pos)    /**< (SERCOM_I2CM_STATUS) Length Error Mask */
#define SERCOM_I2CM_STATUS_LENERR           SERCOM_I2CM_STATUS_LENERR_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_STATUS_LENERR_Msk instead */
#define SERCOM_I2CM_STATUS_MASK             _U_(0x7F7)                                     /**< \deprecated (SERCOM_I2CM_STATUS) Register MASK  (Use SERCOM_I2CM_STATUS_Msk instead)  */
#define SERCOM_I2CM_STATUS_Msk              _U_(0x7F7)                                     /**< (SERCOM_I2CM_STATUS) Register Mask  */


/* -------- SERCOM_I2CS_STATUS : (SERCOM Offset: 0x1a) (R/W 16) I2CS Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t BUSERR:1;                  /**< bit:      0  Bus Error                                */
    uint16_t COLL:1;                    /**< bit:      1  Transmit Collision                       */
    uint16_t RXNACK:1;                  /**< bit:      2  Received Not Acknowledge                 */
    uint16_t DIR:1;                     /**< bit:      3  Read/Write Direction                     */
    uint16_t SR:1;                      /**< bit:      4  Repeated Start                           */
    uint16_t :1;                        /**< bit:      5  Reserved */
    uint16_t LOWTOUT:1;                 /**< bit:      6  SCL Low Timeout                          */
    uint16_t CLKHOLD:1;                 /**< bit:      7  Clock Hold                               */
    uint16_t :1;                        /**< bit:      8  Reserved */
    uint16_t SEXTTOUT:1;                /**< bit:      9  Slave SCL Low Extend Timeout             */
    uint16_t HS:1;                      /**< bit:     10  High Speed                               */
    uint16_t :5;                        /**< bit: 11..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} SERCOM_I2CS_STATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_STATUS_OFFSET           (0x1A)                                        /**<  (SERCOM_I2CS_STATUS) I2CS Status  Offset */
#define SERCOM_I2CS_STATUS_RESETVALUE       _U_(0x00)                                     /**<  (SERCOM_I2CS_STATUS) I2CS Status  Reset Value */

#define SERCOM_I2CS_STATUS_BUSERR_Pos       0                                              /**< (SERCOM_I2CS_STATUS) Bus Error Position */
#define SERCOM_I2CS_STATUS_BUSERR_Msk       (_U_(0x1) << SERCOM_I2CS_STATUS_BUSERR_Pos)    /**< (SERCOM_I2CS_STATUS) Bus Error Mask */
#define SERCOM_I2CS_STATUS_BUSERR           SERCOM_I2CS_STATUS_BUSERR_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_STATUS_BUSERR_Msk instead */
#define SERCOM_I2CS_STATUS_COLL_Pos         1                                              /**< (SERCOM_I2CS_STATUS) Transmit Collision Position */
#define SERCOM_I2CS_STATUS_COLL_Msk         (_U_(0x1) << SERCOM_I2CS_STATUS_COLL_Pos)      /**< (SERCOM_I2CS_STATUS) Transmit Collision Mask */
#define SERCOM_I2CS_STATUS_COLL             SERCOM_I2CS_STATUS_COLL_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_STATUS_COLL_Msk instead */
#define SERCOM_I2CS_STATUS_RXNACK_Pos       2                                              /**< (SERCOM_I2CS_STATUS) Received Not Acknowledge Position */
#define SERCOM_I2CS_STATUS_RXNACK_Msk       (_U_(0x1) << SERCOM_I2CS_STATUS_RXNACK_Pos)    /**< (SERCOM_I2CS_STATUS) Received Not Acknowledge Mask */
#define SERCOM_I2CS_STATUS_RXNACK           SERCOM_I2CS_STATUS_RXNACK_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_STATUS_RXNACK_Msk instead */
#define SERCOM_I2CS_STATUS_DIR_Pos          3                                              /**< (SERCOM_I2CS_STATUS) Read/Write Direction Position */
#define SERCOM_I2CS_STATUS_DIR_Msk          (_U_(0x1) << SERCOM_I2CS_STATUS_DIR_Pos)       /**< (SERCOM_I2CS_STATUS) Read/Write Direction Mask */
#define SERCOM_I2CS_STATUS_DIR              SERCOM_I2CS_STATUS_DIR_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_STATUS_DIR_Msk instead */
#define SERCOM_I2CS_STATUS_SR_Pos           4                                              /**< (SERCOM_I2CS_STATUS) Repeated Start Position */
#define SERCOM_I2CS_STATUS_SR_Msk           (_U_(0x1) << SERCOM_I2CS_STATUS_SR_Pos)        /**< (SERCOM_I2CS_STATUS) Repeated Start Mask */
#define SERCOM_I2CS_STATUS_SR               SERCOM_I2CS_STATUS_SR_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_STATUS_SR_Msk instead */
#define SERCOM_I2CS_STATUS_LOWTOUT_Pos      6                                              /**< (SERCOM_I2CS_STATUS) SCL Low Timeout Position */
#define SERCOM_I2CS_STATUS_LOWTOUT_Msk      (_U_(0x1) << SERCOM_I2CS_STATUS_LOWTOUT_Pos)   /**< (SERCOM_I2CS_STATUS) SCL Low Timeout Mask */
#define SERCOM_I2CS_STATUS_LOWTOUT          SERCOM_I2CS_STATUS_LOWTOUT_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_STATUS_LOWTOUT_Msk instead */
#define SERCOM_I2CS_STATUS_CLKHOLD_Pos      7                                              /**< (SERCOM_I2CS_STATUS) Clock Hold Position */
#define SERCOM_I2CS_STATUS_CLKHOLD_Msk      (_U_(0x1) << SERCOM_I2CS_STATUS_CLKHOLD_Pos)   /**< (SERCOM_I2CS_STATUS) Clock Hold Mask */
#define SERCOM_I2CS_STATUS_CLKHOLD          SERCOM_I2CS_STATUS_CLKHOLD_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_STATUS_CLKHOLD_Msk instead */
#define SERCOM_I2CS_STATUS_SEXTTOUT_Pos     9                                              /**< (SERCOM_I2CS_STATUS) Slave SCL Low Extend Timeout Position */
#define SERCOM_I2CS_STATUS_SEXTTOUT_Msk     (_U_(0x1) << SERCOM_I2CS_STATUS_SEXTTOUT_Pos)  /**< (SERCOM_I2CS_STATUS) Slave SCL Low Extend Timeout Mask */
#define SERCOM_I2CS_STATUS_SEXTTOUT         SERCOM_I2CS_STATUS_SEXTTOUT_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_STATUS_SEXTTOUT_Msk instead */
#define SERCOM_I2CS_STATUS_HS_Pos           10                                             /**< (SERCOM_I2CS_STATUS) High Speed Position */
#define SERCOM_I2CS_STATUS_HS_Msk           (_U_(0x1) << SERCOM_I2CS_STATUS_HS_Pos)        /**< (SERCOM_I2CS_STATUS) High Speed Mask */
#define SERCOM_I2CS_STATUS_HS               SERCOM_I2CS_STATUS_HS_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_STATUS_HS_Msk instead */
#define SERCOM_I2CS_STATUS_MASK             _U_(0x6DF)                                     /**< \deprecated (SERCOM_I2CS_STATUS) Register MASK  (Use SERCOM_I2CS_STATUS_Msk instead)  */
#define SERCOM_I2CS_STATUS_Msk              _U_(0x6DF)                                     /**< (SERCOM_I2CS_STATUS) Register Mask  */


/* -------- SERCOM_SPI_STATUS : (SERCOM Offset: 0x1a) (R/W 16) SPI Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t :2;                        /**< bit:   0..1  Reserved */
    uint16_t BUFOVF:1;                  /**< bit:      2  Buffer Overflow                          */
    uint16_t :13;                       /**< bit:  3..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} SERCOM_SPI_STATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_STATUS_OFFSET            (0x1A)                                        /**<  (SERCOM_SPI_STATUS) SPI Status  Offset */
#define SERCOM_SPI_STATUS_RESETVALUE        _U_(0x00)                                     /**<  (SERCOM_SPI_STATUS) SPI Status  Reset Value */

#define SERCOM_SPI_STATUS_BUFOVF_Pos        2                                              /**< (SERCOM_SPI_STATUS) Buffer Overflow Position */
#define SERCOM_SPI_STATUS_BUFOVF_Msk        (_U_(0x1) << SERCOM_SPI_STATUS_BUFOVF_Pos)     /**< (SERCOM_SPI_STATUS) Buffer Overflow Mask */
#define SERCOM_SPI_STATUS_BUFOVF            SERCOM_SPI_STATUS_BUFOVF_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_STATUS_BUFOVF_Msk instead */
#define SERCOM_SPI_STATUS_MASK              _U_(0x04)                                      /**< \deprecated (SERCOM_SPI_STATUS) Register MASK  (Use SERCOM_SPI_STATUS_Msk instead)  */
#define SERCOM_SPI_STATUS_Msk               _U_(0x04)                                      /**< (SERCOM_SPI_STATUS) Register Mask  */


/* -------- SERCOM_USART_STATUS : (SERCOM Offset: 0x1a) (R/W 16) USART Status -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t PERR:1;                    /**< bit:      0  Parity Error                             */
    uint16_t FERR:1;                    /**< bit:      1  Frame Error                              */
    uint16_t BUFOVF:1;                  /**< bit:      2  Buffer Overflow                          */
    uint16_t CTS:1;                     /**< bit:      3  Clear To Send                            */
    uint16_t ISF:1;                     /**< bit:      4  Inconsistent Sync Field                  */
    uint16_t COLL:1;                    /**< bit:      5  Collision Detected                       */
    uint16_t TXE:1;                     /**< bit:      6  Transmitter Empty                        */
    uint16_t ITER:1;                    /**< bit:      7  Maximum Number of Repetitions Reached    */
    uint16_t :8;                        /**< bit:  8..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} SERCOM_USART_STATUS_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_STATUS_OFFSET          (0x1A)                                        /**<  (SERCOM_USART_STATUS) USART Status  Offset */
#define SERCOM_USART_STATUS_RESETVALUE      _U_(0x00)                                     /**<  (SERCOM_USART_STATUS) USART Status  Reset Value */

#define SERCOM_USART_STATUS_PERR_Pos        0                                              /**< (SERCOM_USART_STATUS) Parity Error Position */
#define SERCOM_USART_STATUS_PERR_Msk        (_U_(0x1) << SERCOM_USART_STATUS_PERR_Pos)     /**< (SERCOM_USART_STATUS) Parity Error Mask */
#define SERCOM_USART_STATUS_PERR            SERCOM_USART_STATUS_PERR_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_STATUS_PERR_Msk instead */
#define SERCOM_USART_STATUS_FERR_Pos        1                                              /**< (SERCOM_USART_STATUS) Frame Error Position */
#define SERCOM_USART_STATUS_FERR_Msk        (_U_(0x1) << SERCOM_USART_STATUS_FERR_Pos)     /**< (SERCOM_USART_STATUS) Frame Error Mask */
#define SERCOM_USART_STATUS_FERR            SERCOM_USART_STATUS_FERR_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_STATUS_FERR_Msk instead */
#define SERCOM_USART_STATUS_BUFOVF_Pos      2                                              /**< (SERCOM_USART_STATUS) Buffer Overflow Position */
#define SERCOM_USART_STATUS_BUFOVF_Msk      (_U_(0x1) << SERCOM_USART_STATUS_BUFOVF_Pos)   /**< (SERCOM_USART_STATUS) Buffer Overflow Mask */
#define SERCOM_USART_STATUS_BUFOVF          SERCOM_USART_STATUS_BUFOVF_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_STATUS_BUFOVF_Msk instead */
#define SERCOM_USART_STATUS_CTS_Pos         3                                              /**< (SERCOM_USART_STATUS) Clear To Send Position */
#define SERCOM_USART_STATUS_CTS_Msk         (_U_(0x1) << SERCOM_USART_STATUS_CTS_Pos)      /**< (SERCOM_USART_STATUS) Clear To Send Mask */
#define SERCOM_USART_STATUS_CTS             SERCOM_USART_STATUS_CTS_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_STATUS_CTS_Msk instead */
#define SERCOM_USART_STATUS_ISF_Pos         4                                              /**< (SERCOM_USART_STATUS) Inconsistent Sync Field Position */
#define SERCOM_USART_STATUS_ISF_Msk         (_U_(0x1) << SERCOM_USART_STATUS_ISF_Pos)      /**< (SERCOM_USART_STATUS) Inconsistent Sync Field Mask */
#define SERCOM_USART_STATUS_ISF             SERCOM_USART_STATUS_ISF_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_STATUS_ISF_Msk instead */
#define SERCOM_USART_STATUS_COLL_Pos        5                                              /**< (SERCOM_USART_STATUS) Collision Detected Position */
#define SERCOM_USART_STATUS_COLL_Msk        (_U_(0x1) << SERCOM_USART_STATUS_COLL_Pos)     /**< (SERCOM_USART_STATUS) Collision Detected Mask */
#define SERCOM_USART_STATUS_COLL            SERCOM_USART_STATUS_COLL_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_STATUS_COLL_Msk instead */
#define SERCOM_USART_STATUS_TXE_Pos         6                                              /**< (SERCOM_USART_STATUS) Transmitter Empty Position */
#define SERCOM_USART_STATUS_TXE_Msk         (_U_(0x1) << SERCOM_USART_STATUS_TXE_Pos)      /**< (SERCOM_USART_STATUS) Transmitter Empty Mask */
#define SERCOM_USART_STATUS_TXE             SERCOM_USART_STATUS_TXE_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_STATUS_TXE_Msk instead */
#define SERCOM_USART_STATUS_ITER_Pos        7                                              /**< (SERCOM_USART_STATUS) Maximum Number of Repetitions Reached Position */
#define SERCOM_USART_STATUS_ITER_Msk        (_U_(0x1) << SERCOM_USART_STATUS_ITER_Pos)     /**< (SERCOM_USART_STATUS) Maximum Number of Repetitions Reached Mask */
#define SERCOM_USART_STATUS_ITER            SERCOM_USART_STATUS_ITER_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_STATUS_ITER_Msk instead */
#define SERCOM_USART_STATUS_MASK            _U_(0xFF)                                      /**< \deprecated (SERCOM_USART_STATUS) Register MASK  (Use SERCOM_USART_STATUS_Msk instead)  */
#define SERCOM_USART_STATUS_Msk             _U_(0xFF)                                      /**< (SERCOM_USART_STATUS) Register Mask  */


/* -------- SERCOM_I2CM_SYNCBUSY : (SERCOM Offset: 0x1c) (R/ 32) I2CM Synchronization Busy -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset Synchronization Busy      */
    uint32_t ENABLE:1;                  /**< bit:      1  SERCOM Enable Synchronization Busy       */
    uint32_t SYSOP:1;                   /**< bit:      2  System Operation Synchronization Busy    */
    uint32_t :29;                       /**< bit:  3..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_I2CM_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_SYNCBUSY_OFFSET         (0x1C)                                        /**<  (SERCOM_I2CM_SYNCBUSY) I2CM Synchronization Busy  Offset */
#define SERCOM_I2CM_SYNCBUSY_RESETVALUE     _U_(0x00)                                     /**<  (SERCOM_I2CM_SYNCBUSY) I2CM Synchronization Busy  Reset Value */

#define SERCOM_I2CM_SYNCBUSY_SWRST_Pos      0                                              /**< (SERCOM_I2CM_SYNCBUSY) Software Reset Synchronization Busy Position */
#define SERCOM_I2CM_SYNCBUSY_SWRST_Msk      (_U_(0x1) << SERCOM_I2CM_SYNCBUSY_SWRST_Pos)   /**< (SERCOM_I2CM_SYNCBUSY) Software Reset Synchronization Busy Mask */
#define SERCOM_I2CM_SYNCBUSY_SWRST          SERCOM_I2CM_SYNCBUSY_SWRST_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_SYNCBUSY_SWRST_Msk instead */
#define SERCOM_I2CM_SYNCBUSY_ENABLE_Pos     1                                              /**< (SERCOM_I2CM_SYNCBUSY) SERCOM Enable Synchronization Busy Position */
#define SERCOM_I2CM_SYNCBUSY_ENABLE_Msk     (_U_(0x1) << SERCOM_I2CM_SYNCBUSY_ENABLE_Pos)  /**< (SERCOM_I2CM_SYNCBUSY) SERCOM Enable Synchronization Busy Mask */
#define SERCOM_I2CM_SYNCBUSY_ENABLE         SERCOM_I2CM_SYNCBUSY_ENABLE_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_SYNCBUSY_ENABLE_Msk instead */
#define SERCOM_I2CM_SYNCBUSY_SYSOP_Pos      2                                              /**< (SERCOM_I2CM_SYNCBUSY) System Operation Synchronization Busy Position */
#define SERCOM_I2CM_SYNCBUSY_SYSOP_Msk      (_U_(0x1) << SERCOM_I2CM_SYNCBUSY_SYSOP_Pos)   /**< (SERCOM_I2CM_SYNCBUSY) System Operation Synchronization Busy Mask */
#define SERCOM_I2CM_SYNCBUSY_SYSOP          SERCOM_I2CM_SYNCBUSY_SYSOP_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_SYNCBUSY_SYSOP_Msk instead */
#define SERCOM_I2CM_SYNCBUSY_MASK           _U_(0x07)                                      /**< \deprecated (SERCOM_I2CM_SYNCBUSY) Register MASK  (Use SERCOM_I2CM_SYNCBUSY_Msk instead)  */
#define SERCOM_I2CM_SYNCBUSY_Msk            _U_(0x07)                                      /**< (SERCOM_I2CM_SYNCBUSY) Register Mask  */


/* -------- SERCOM_I2CS_SYNCBUSY : (SERCOM Offset: 0x1c) (R/ 32) I2CS Synchronization Busy -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset Synchronization Busy      */
    uint32_t ENABLE:1;                  /**< bit:      1  SERCOM Enable Synchronization Busy       */
    uint32_t :30;                       /**< bit:  2..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_I2CS_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_SYNCBUSY_OFFSET         (0x1C)                                        /**<  (SERCOM_I2CS_SYNCBUSY) I2CS Synchronization Busy  Offset */
#define SERCOM_I2CS_SYNCBUSY_RESETVALUE     _U_(0x00)                                     /**<  (SERCOM_I2CS_SYNCBUSY) I2CS Synchronization Busy  Reset Value */

#define SERCOM_I2CS_SYNCBUSY_SWRST_Pos      0                                              /**< (SERCOM_I2CS_SYNCBUSY) Software Reset Synchronization Busy Position */
#define SERCOM_I2CS_SYNCBUSY_SWRST_Msk      (_U_(0x1) << SERCOM_I2CS_SYNCBUSY_SWRST_Pos)   /**< (SERCOM_I2CS_SYNCBUSY) Software Reset Synchronization Busy Mask */
#define SERCOM_I2CS_SYNCBUSY_SWRST          SERCOM_I2CS_SYNCBUSY_SWRST_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_SYNCBUSY_SWRST_Msk instead */
#define SERCOM_I2CS_SYNCBUSY_ENABLE_Pos     1                                              /**< (SERCOM_I2CS_SYNCBUSY) SERCOM Enable Synchronization Busy Position */
#define SERCOM_I2CS_SYNCBUSY_ENABLE_Msk     (_U_(0x1) << SERCOM_I2CS_SYNCBUSY_ENABLE_Pos)  /**< (SERCOM_I2CS_SYNCBUSY) SERCOM Enable Synchronization Busy Mask */
#define SERCOM_I2CS_SYNCBUSY_ENABLE         SERCOM_I2CS_SYNCBUSY_ENABLE_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_SYNCBUSY_ENABLE_Msk instead */
#define SERCOM_I2CS_SYNCBUSY_MASK           _U_(0x03)                                      /**< \deprecated (SERCOM_I2CS_SYNCBUSY) Register MASK  (Use SERCOM_I2CS_SYNCBUSY_Msk instead)  */
#define SERCOM_I2CS_SYNCBUSY_Msk            _U_(0x03)                                      /**< (SERCOM_I2CS_SYNCBUSY) Register Mask  */


/* -------- SERCOM_SPI_SYNCBUSY : (SERCOM Offset: 0x1c) (R/ 32) SPI Synchronization Busy -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset Synchronization Busy      */
    uint32_t ENABLE:1;                  /**< bit:      1  SERCOM Enable Synchronization Busy       */
    uint32_t CTRLB:1;                   /**< bit:      2  CTRLB Synchronization Busy               */
    uint32_t :29;                       /**< bit:  3..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_SPI_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_SYNCBUSY_OFFSET          (0x1C)                                        /**<  (SERCOM_SPI_SYNCBUSY) SPI Synchronization Busy  Offset */
#define SERCOM_SPI_SYNCBUSY_RESETVALUE      _U_(0x00)                                     /**<  (SERCOM_SPI_SYNCBUSY) SPI Synchronization Busy  Reset Value */

#define SERCOM_SPI_SYNCBUSY_SWRST_Pos       0                                              /**< (SERCOM_SPI_SYNCBUSY) Software Reset Synchronization Busy Position */
#define SERCOM_SPI_SYNCBUSY_SWRST_Msk       (_U_(0x1) << SERCOM_SPI_SYNCBUSY_SWRST_Pos)    /**< (SERCOM_SPI_SYNCBUSY) Software Reset Synchronization Busy Mask */
#define SERCOM_SPI_SYNCBUSY_SWRST           SERCOM_SPI_SYNCBUSY_SWRST_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_SYNCBUSY_SWRST_Msk instead */
#define SERCOM_SPI_SYNCBUSY_ENABLE_Pos      1                                              /**< (SERCOM_SPI_SYNCBUSY) SERCOM Enable Synchronization Busy Position */
#define SERCOM_SPI_SYNCBUSY_ENABLE_Msk      (_U_(0x1) << SERCOM_SPI_SYNCBUSY_ENABLE_Pos)   /**< (SERCOM_SPI_SYNCBUSY) SERCOM Enable Synchronization Busy Mask */
#define SERCOM_SPI_SYNCBUSY_ENABLE          SERCOM_SPI_SYNCBUSY_ENABLE_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_SYNCBUSY_ENABLE_Msk instead */
#define SERCOM_SPI_SYNCBUSY_CTRLB_Pos       2                                              /**< (SERCOM_SPI_SYNCBUSY) CTRLB Synchronization Busy Position */
#define SERCOM_SPI_SYNCBUSY_CTRLB_Msk       (_U_(0x1) << SERCOM_SPI_SYNCBUSY_CTRLB_Pos)    /**< (SERCOM_SPI_SYNCBUSY) CTRLB Synchronization Busy Mask */
#define SERCOM_SPI_SYNCBUSY_CTRLB           SERCOM_SPI_SYNCBUSY_CTRLB_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_SYNCBUSY_CTRLB_Msk instead */
#define SERCOM_SPI_SYNCBUSY_MASK            _U_(0x07)                                      /**< \deprecated (SERCOM_SPI_SYNCBUSY) Register MASK  (Use SERCOM_SPI_SYNCBUSY_Msk instead)  */
#define SERCOM_SPI_SYNCBUSY_Msk             _U_(0x07)                                      /**< (SERCOM_SPI_SYNCBUSY) Register Mask  */


/* -------- SERCOM_USART_SYNCBUSY : (SERCOM Offset: 0x1c) (R/ 32) USART Synchronization Busy -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SWRST:1;                   /**< bit:      0  Software Reset Synchronization Busy      */
    uint32_t ENABLE:1;                  /**< bit:      1  SERCOM Enable Synchronization Busy       */
    uint32_t CTRLB:1;                   /**< bit:      2  CTRLB Synchronization Busy               */
    uint32_t RXERRCNT:1;                /**< bit:      3  RXERRCNT Synchronization Busy            */
    uint32_t :28;                       /**< bit:  4..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_USART_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_SYNCBUSY_OFFSET        (0x1C)                                        /**<  (SERCOM_USART_SYNCBUSY) USART Synchronization Busy  Offset */
#define SERCOM_USART_SYNCBUSY_RESETVALUE    _U_(0x00)                                     /**<  (SERCOM_USART_SYNCBUSY) USART Synchronization Busy  Reset Value */

#define SERCOM_USART_SYNCBUSY_SWRST_Pos     0                                              /**< (SERCOM_USART_SYNCBUSY) Software Reset Synchronization Busy Position */
#define SERCOM_USART_SYNCBUSY_SWRST_Msk     (_U_(0x1) << SERCOM_USART_SYNCBUSY_SWRST_Pos)  /**< (SERCOM_USART_SYNCBUSY) Software Reset Synchronization Busy Mask */
#define SERCOM_USART_SYNCBUSY_SWRST         SERCOM_USART_SYNCBUSY_SWRST_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_SYNCBUSY_SWRST_Msk instead */
#define SERCOM_USART_SYNCBUSY_ENABLE_Pos    1                                              /**< (SERCOM_USART_SYNCBUSY) SERCOM Enable Synchronization Busy Position */
#define SERCOM_USART_SYNCBUSY_ENABLE_Msk    (_U_(0x1) << SERCOM_USART_SYNCBUSY_ENABLE_Pos)  /**< (SERCOM_USART_SYNCBUSY) SERCOM Enable Synchronization Busy Mask */
#define SERCOM_USART_SYNCBUSY_ENABLE        SERCOM_USART_SYNCBUSY_ENABLE_Msk               /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_SYNCBUSY_ENABLE_Msk instead */
#define SERCOM_USART_SYNCBUSY_CTRLB_Pos     2                                              /**< (SERCOM_USART_SYNCBUSY) CTRLB Synchronization Busy Position */
#define SERCOM_USART_SYNCBUSY_CTRLB_Msk     (_U_(0x1) << SERCOM_USART_SYNCBUSY_CTRLB_Pos)  /**< (SERCOM_USART_SYNCBUSY) CTRLB Synchronization Busy Mask */
#define SERCOM_USART_SYNCBUSY_CTRLB         SERCOM_USART_SYNCBUSY_CTRLB_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_SYNCBUSY_CTRLB_Msk instead */
#define SERCOM_USART_SYNCBUSY_RXERRCNT_Pos  3                                              /**< (SERCOM_USART_SYNCBUSY) RXERRCNT Synchronization Busy Position */
#define SERCOM_USART_SYNCBUSY_RXERRCNT_Msk  (_U_(0x1) << SERCOM_USART_SYNCBUSY_RXERRCNT_Pos)  /**< (SERCOM_USART_SYNCBUSY) RXERRCNT Synchronization Busy Mask */
#define SERCOM_USART_SYNCBUSY_RXERRCNT      SERCOM_USART_SYNCBUSY_RXERRCNT_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_SYNCBUSY_RXERRCNT_Msk instead */
#define SERCOM_USART_SYNCBUSY_MASK          _U_(0x0F)                                      /**< \deprecated (SERCOM_USART_SYNCBUSY) Register MASK  (Use SERCOM_USART_SYNCBUSY_Msk instead)  */
#define SERCOM_USART_SYNCBUSY_Msk           _U_(0x0F)                                      /**< (SERCOM_USART_SYNCBUSY) Register Mask  */


/* -------- SERCOM_USART_RXERRCNT : (SERCOM Offset: 0x20) (R/ 8) USART Receive Error Count -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_USART_RXERRCNT_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_RXERRCNT_OFFSET        (0x20)                                        /**<  (SERCOM_USART_RXERRCNT) USART Receive Error Count  Offset */
#define SERCOM_USART_RXERRCNT_RESETVALUE    _U_(0x00)                                     /**<  (SERCOM_USART_RXERRCNT) USART Receive Error Count  Reset Value */

#define SERCOM_USART_RXERRCNT_MASK          _U_(0x00)                                      /**< \deprecated (SERCOM_USART_RXERRCNT) Register MASK  (Use SERCOM_USART_RXERRCNT_Msk instead)  */
#define SERCOM_USART_RXERRCNT_Msk           _U_(0x00)                                      /**< (SERCOM_USART_RXERRCNT) Register Mask  */


/* -------- SERCOM_I2CM_ADDR : (SERCOM Offset: 0x24) (R/W 32) I2CM Address -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t ADDR:11;                   /**< bit:  0..10  Address Value                            */
    uint32_t :2;                        /**< bit: 11..12  Reserved */
    uint32_t LENEN:1;                   /**< bit:     13  Length Enable                            */
    uint32_t HS:1;                      /**< bit:     14  High Speed Mode                          */
    uint32_t TENBITEN:1;                /**< bit:     15  Ten Bit Addressing Enable                */
    uint32_t LEN:8;                     /**< bit: 16..23  Length                                   */
    uint32_t :8;                        /**< bit: 24..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_I2CM_ADDR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_ADDR_OFFSET             (0x24)                                        /**<  (SERCOM_I2CM_ADDR) I2CM Address  Offset */
#define SERCOM_I2CM_ADDR_RESETVALUE         _U_(0x00)                                     /**<  (SERCOM_I2CM_ADDR) I2CM Address  Reset Value */

#define SERCOM_I2CM_ADDR_ADDR_Pos           0                                              /**< (SERCOM_I2CM_ADDR) Address Value Position */
#define SERCOM_I2CM_ADDR_ADDR_Msk           (_U_(0x7FF) << SERCOM_I2CM_ADDR_ADDR_Pos)      /**< (SERCOM_I2CM_ADDR) Address Value Mask */
#define SERCOM_I2CM_ADDR_ADDR(value)        (SERCOM_I2CM_ADDR_ADDR_Msk & ((value) << SERCOM_I2CM_ADDR_ADDR_Pos))
#define SERCOM_I2CM_ADDR_LENEN_Pos          13                                             /**< (SERCOM_I2CM_ADDR) Length Enable Position */
#define SERCOM_I2CM_ADDR_LENEN_Msk          (_U_(0x1) << SERCOM_I2CM_ADDR_LENEN_Pos)       /**< (SERCOM_I2CM_ADDR) Length Enable Mask */
#define SERCOM_I2CM_ADDR_LENEN              SERCOM_I2CM_ADDR_LENEN_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_ADDR_LENEN_Msk instead */
#define SERCOM_I2CM_ADDR_HS_Pos             14                                             /**< (SERCOM_I2CM_ADDR) High Speed Mode Position */
#define SERCOM_I2CM_ADDR_HS_Msk             (_U_(0x1) << SERCOM_I2CM_ADDR_HS_Pos)          /**< (SERCOM_I2CM_ADDR) High Speed Mode Mask */
#define SERCOM_I2CM_ADDR_HS                 SERCOM_I2CM_ADDR_HS_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_ADDR_HS_Msk instead */
#define SERCOM_I2CM_ADDR_TENBITEN_Pos       15                                             /**< (SERCOM_I2CM_ADDR) Ten Bit Addressing Enable Position */
#define SERCOM_I2CM_ADDR_TENBITEN_Msk       (_U_(0x1) << SERCOM_I2CM_ADDR_TENBITEN_Pos)    /**< (SERCOM_I2CM_ADDR) Ten Bit Addressing Enable Mask */
#define SERCOM_I2CM_ADDR_TENBITEN           SERCOM_I2CM_ADDR_TENBITEN_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_ADDR_TENBITEN_Msk instead */
#define SERCOM_I2CM_ADDR_LEN_Pos            16                                             /**< (SERCOM_I2CM_ADDR) Length Position */
#define SERCOM_I2CM_ADDR_LEN_Msk            (_U_(0xFF) << SERCOM_I2CM_ADDR_LEN_Pos)        /**< (SERCOM_I2CM_ADDR) Length Mask */
#define SERCOM_I2CM_ADDR_LEN(value)         (SERCOM_I2CM_ADDR_LEN_Msk & ((value) << SERCOM_I2CM_ADDR_LEN_Pos))
#define SERCOM_I2CM_ADDR_MASK               _U_(0xFFE7FF)                                  /**< \deprecated (SERCOM_I2CM_ADDR) Register MASK  (Use SERCOM_I2CM_ADDR_Msk instead)  */
#define SERCOM_I2CM_ADDR_Msk                _U_(0xFFE7FF)                                  /**< (SERCOM_I2CM_ADDR) Register Mask  */


/* -------- SERCOM_I2CS_ADDR : (SERCOM Offset: 0x24) (R/W 32) I2CS Address -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t GENCEN:1;                  /**< bit:      0  General Call Address Enable              */
    uint32_t ADDR:10;                   /**< bit:  1..10  Address Value                            */
    uint32_t :4;                        /**< bit: 11..14  Reserved */
    uint32_t TENBITEN:1;                /**< bit:     15  Ten Bit Addressing Enable                */
    uint32_t :1;                        /**< bit:     16  Reserved */
    uint32_t ADDRMASK:10;               /**< bit: 17..26  Address Mask                             */
    uint32_t :5;                        /**< bit: 27..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_I2CS_ADDR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_ADDR_OFFSET             (0x24)                                        /**<  (SERCOM_I2CS_ADDR) I2CS Address  Offset */
#define SERCOM_I2CS_ADDR_RESETVALUE         _U_(0x00)                                     /**<  (SERCOM_I2CS_ADDR) I2CS Address  Reset Value */

#define SERCOM_I2CS_ADDR_GENCEN_Pos         0                                              /**< (SERCOM_I2CS_ADDR) General Call Address Enable Position */
#define SERCOM_I2CS_ADDR_GENCEN_Msk         (_U_(0x1) << SERCOM_I2CS_ADDR_GENCEN_Pos)      /**< (SERCOM_I2CS_ADDR) General Call Address Enable Mask */
#define SERCOM_I2CS_ADDR_GENCEN             SERCOM_I2CS_ADDR_GENCEN_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_ADDR_GENCEN_Msk instead */
#define SERCOM_I2CS_ADDR_ADDR_Pos           1                                              /**< (SERCOM_I2CS_ADDR) Address Value Position */
#define SERCOM_I2CS_ADDR_ADDR_Msk           (_U_(0x3FF) << SERCOM_I2CS_ADDR_ADDR_Pos)      /**< (SERCOM_I2CS_ADDR) Address Value Mask */
#define SERCOM_I2CS_ADDR_ADDR(value)        (SERCOM_I2CS_ADDR_ADDR_Msk & ((value) << SERCOM_I2CS_ADDR_ADDR_Pos))
#define SERCOM_I2CS_ADDR_TENBITEN_Pos       15                                             /**< (SERCOM_I2CS_ADDR) Ten Bit Addressing Enable Position */
#define SERCOM_I2CS_ADDR_TENBITEN_Msk       (_U_(0x1) << SERCOM_I2CS_ADDR_TENBITEN_Pos)    /**< (SERCOM_I2CS_ADDR) Ten Bit Addressing Enable Mask */
#define SERCOM_I2CS_ADDR_TENBITEN           SERCOM_I2CS_ADDR_TENBITEN_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CS_ADDR_TENBITEN_Msk instead */
#define SERCOM_I2CS_ADDR_ADDRMASK_Pos       17                                             /**< (SERCOM_I2CS_ADDR) Address Mask Position */
#define SERCOM_I2CS_ADDR_ADDRMASK_Msk       (_U_(0x3FF) << SERCOM_I2CS_ADDR_ADDRMASK_Pos)  /**< (SERCOM_I2CS_ADDR) Address Mask Mask */
#define SERCOM_I2CS_ADDR_ADDRMASK(value)    (SERCOM_I2CS_ADDR_ADDRMASK_Msk & ((value) << SERCOM_I2CS_ADDR_ADDRMASK_Pos))
#define SERCOM_I2CS_ADDR_Msk                _U_(0x7FE87FF)                                 /**< (SERCOM_I2CS_ADDR) Register Mask  */


/* -------- SERCOM_SPI_ADDR : (SERCOM Offset: 0x24) (R/W 32) SPI Address -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t ADDR:8;                    /**< bit:   0..7  Address Value                            */
    uint32_t :8;                        /**< bit:  8..15  Reserved */
    uint32_t ADDRMASK:8;                /**< bit: 16..23  Address Mask                             */
    uint32_t :8;                        /**< bit: 24..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_SPI_ADDR_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_ADDR_OFFSET              (0x24)                                        /**<  (SERCOM_SPI_ADDR) SPI Address  Offset */
#define SERCOM_SPI_ADDR_RESETVALUE          _U_(0x00)                                     /**<  (SERCOM_SPI_ADDR) SPI Address  Reset Value */

#define SERCOM_SPI_ADDR_ADDR_Pos            0                                              /**< (SERCOM_SPI_ADDR) Address Value Position */
#define SERCOM_SPI_ADDR_ADDR_Msk            (_U_(0xFF) << SERCOM_SPI_ADDR_ADDR_Pos)        /**< (SERCOM_SPI_ADDR) Address Value Mask */
#define SERCOM_SPI_ADDR_ADDR(value)         (SERCOM_SPI_ADDR_ADDR_Msk & ((value) << SERCOM_SPI_ADDR_ADDR_Pos))
#define SERCOM_SPI_ADDR_ADDRMASK_Pos        16                                             /**< (SERCOM_SPI_ADDR) Address Mask Position */
#define SERCOM_SPI_ADDR_ADDRMASK_Msk        (_U_(0xFF) << SERCOM_SPI_ADDR_ADDRMASK_Pos)    /**< (SERCOM_SPI_ADDR) Address Mask Mask */
#define SERCOM_SPI_ADDR_ADDRMASK(value)     (SERCOM_SPI_ADDR_ADDRMASK_Msk & ((value) << SERCOM_SPI_ADDR_ADDRMASK_Pos))
#define SERCOM_SPI_ADDR_Msk                 _U_(0xFF00FF)                                  /**< (SERCOM_SPI_ADDR) Register Mask  */


/* -------- SERCOM_I2CM_DATA : (SERCOM Offset: 0x28) (R/W 8) I2CM Data -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DATA:8;                    /**< bit:   0..7  Data Value                               */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_I2CM_DATA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_DATA_OFFSET             (0x28)                                        /**<  (SERCOM_I2CM_DATA) I2CM Data  Offset */
#define SERCOM_I2CM_DATA_RESETVALUE         _U_(0x00)                                     /**<  (SERCOM_I2CM_DATA) I2CM Data  Reset Value */

#define SERCOM_I2CM_DATA_DATA_Pos           0                                              /**< (SERCOM_I2CM_DATA) Data Value Position */
#define SERCOM_I2CM_DATA_DATA_Msk           (_U_(0xFF) << SERCOM_I2CM_DATA_DATA_Pos)       /**< (SERCOM_I2CM_DATA) Data Value Mask */
#define SERCOM_I2CM_DATA_DATA(value)        (SERCOM_I2CM_DATA_DATA_Msk & ((value) << SERCOM_I2CM_DATA_DATA_Pos))
#define SERCOM_I2CM_DATA_MASK               _U_(0xFF)                                      /**< \deprecated (SERCOM_I2CM_DATA) Register MASK  (Use SERCOM_I2CM_DATA_Msk instead)  */
#define SERCOM_I2CM_DATA_Msk                _U_(0xFF)                                      /**< (SERCOM_I2CM_DATA) Register Mask  */


/* -------- SERCOM_I2CS_DATA : (SERCOM Offset: 0x28) (R/W 8) I2CS Data -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DATA:8;                    /**< bit:   0..7  Data Value                               */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_I2CS_DATA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_DATA_OFFSET             (0x28)                                        /**<  (SERCOM_I2CS_DATA) I2CS Data  Offset */
#define SERCOM_I2CS_DATA_RESETVALUE         _U_(0x00)                                     /**<  (SERCOM_I2CS_DATA) I2CS Data  Reset Value */

#define SERCOM_I2CS_DATA_DATA_Pos           0                                              /**< (SERCOM_I2CS_DATA) Data Value Position */
#define SERCOM_I2CS_DATA_DATA_Msk           (_U_(0xFF) << SERCOM_I2CS_DATA_DATA_Pos)       /**< (SERCOM_I2CS_DATA) Data Value Mask */
#define SERCOM_I2CS_DATA_DATA(value)        (SERCOM_I2CS_DATA_DATA_Msk & ((value) << SERCOM_I2CS_DATA_DATA_Pos))
#define SERCOM_I2CS_DATA_MASK               _U_(0xFF)                                      /**< \deprecated (SERCOM_I2CS_DATA) Register MASK  (Use SERCOM_I2CS_DATA_Msk instead)  */
#define SERCOM_I2CS_DATA_Msk                _U_(0xFF)                                      /**< (SERCOM_I2CS_DATA) Register Mask  */


/* -------- SERCOM_SPI_DATA : (SERCOM Offset: 0x28) (R/W 32) SPI Data -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DATA:9;                    /**< bit:   0..8  Data Value                               */
    uint32_t :23;                       /**< bit:  9..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SERCOM_SPI_DATA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_DATA_OFFSET              (0x28)                                        /**<  (SERCOM_SPI_DATA) SPI Data  Offset */
#define SERCOM_SPI_DATA_RESETVALUE          _U_(0x00)                                     /**<  (SERCOM_SPI_DATA) SPI Data  Reset Value */

#define SERCOM_SPI_DATA_DATA_Pos            0                                              /**< (SERCOM_SPI_DATA) Data Value Position */
#define SERCOM_SPI_DATA_DATA_Msk            (_U_(0x1FF) << SERCOM_SPI_DATA_DATA_Pos)       /**< (SERCOM_SPI_DATA) Data Value Mask */
#define SERCOM_SPI_DATA_DATA(value)         (SERCOM_SPI_DATA_DATA_Msk & ((value) << SERCOM_SPI_DATA_DATA_Pos))
#define SERCOM_SPI_DATA_MASK                _U_(0x1FF)                                     /**< \deprecated (SERCOM_SPI_DATA) Register MASK  (Use SERCOM_SPI_DATA_Msk instead)  */
#define SERCOM_SPI_DATA_Msk                 _U_(0x1FF)                                     /**< (SERCOM_SPI_DATA) Register Mask  */


/* -------- SERCOM_USART_DATA : (SERCOM Offset: 0x28) (R/W 16) USART Data -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t DATA:9;                    /**< bit:   0..8  Data Value                               */
    uint16_t :7;                        /**< bit:  9..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} SERCOM_USART_DATA_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_DATA_OFFSET            (0x28)                                        /**<  (SERCOM_USART_DATA) USART Data  Offset */
#define SERCOM_USART_DATA_RESETVALUE        _U_(0x00)                                     /**<  (SERCOM_USART_DATA) USART Data  Reset Value */

#define SERCOM_USART_DATA_DATA_Pos          0                                              /**< (SERCOM_USART_DATA) Data Value Position */
#define SERCOM_USART_DATA_DATA_Msk          (_U_(0x1FF) << SERCOM_USART_DATA_DATA_Pos)     /**< (SERCOM_USART_DATA) Data Value Mask */
#define SERCOM_USART_DATA_DATA(value)       (SERCOM_USART_DATA_DATA_Msk & ((value) << SERCOM_USART_DATA_DATA_Pos))
#define SERCOM_USART_DATA_MASK              _U_(0x1FF)                                     /**< \deprecated (SERCOM_USART_DATA) Register MASK  (Use SERCOM_USART_DATA_Msk instead)  */
#define SERCOM_USART_DATA_Msk               _U_(0x1FF)                                     /**< (SERCOM_USART_DATA) Register Mask  */


/* -------- SERCOM_I2CM_DBGCTRL : (SERCOM Offset: 0x30) (R/W 8) I2CM Debug Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DBGSTOP:1;                 /**< bit:      0  Debug Mode                               */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_I2CM_DBGCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_DBGCTRL_OFFSET          (0x30)                                        /**<  (SERCOM_I2CM_DBGCTRL) I2CM Debug Control  Offset */
#define SERCOM_I2CM_DBGCTRL_RESETVALUE      _U_(0x00)                                     /**<  (SERCOM_I2CM_DBGCTRL) I2CM Debug Control  Reset Value */

#define SERCOM_I2CM_DBGCTRL_DBGSTOP_Pos     0                                              /**< (SERCOM_I2CM_DBGCTRL) Debug Mode Position */
#define SERCOM_I2CM_DBGCTRL_DBGSTOP_Msk     (_U_(0x1) << SERCOM_I2CM_DBGCTRL_DBGSTOP_Pos)  /**< (SERCOM_I2CM_DBGCTRL) Debug Mode Mask */
#define SERCOM_I2CM_DBGCTRL_DBGSTOP         SERCOM_I2CM_DBGCTRL_DBGSTOP_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_I2CM_DBGCTRL_DBGSTOP_Msk instead */
#define SERCOM_I2CM_DBGCTRL_MASK            _U_(0x01)                                      /**< \deprecated (SERCOM_I2CM_DBGCTRL) Register MASK  (Use SERCOM_I2CM_DBGCTRL_Msk instead)  */
#define SERCOM_I2CM_DBGCTRL_Msk             _U_(0x01)                                      /**< (SERCOM_I2CM_DBGCTRL) Register Mask  */


/* -------- SERCOM_SPI_DBGCTRL : (SERCOM Offset: 0x30) (R/W 8) SPI Debug Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DBGSTOP:1;                 /**< bit:      0  Debug Mode                               */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_SPI_DBGCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_DBGCTRL_OFFSET           (0x30)                                        /**<  (SERCOM_SPI_DBGCTRL) SPI Debug Control  Offset */
#define SERCOM_SPI_DBGCTRL_RESETVALUE       _U_(0x00)                                     /**<  (SERCOM_SPI_DBGCTRL) SPI Debug Control  Reset Value */

#define SERCOM_SPI_DBGCTRL_DBGSTOP_Pos      0                                              /**< (SERCOM_SPI_DBGCTRL) Debug Mode Position */
#define SERCOM_SPI_DBGCTRL_DBGSTOP_Msk      (_U_(0x1) << SERCOM_SPI_DBGCTRL_DBGSTOP_Pos)   /**< (SERCOM_SPI_DBGCTRL) Debug Mode Mask */
#define SERCOM_SPI_DBGCTRL_DBGSTOP          SERCOM_SPI_DBGCTRL_DBGSTOP_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_SPI_DBGCTRL_DBGSTOP_Msk instead */
#define SERCOM_SPI_DBGCTRL_MASK             _U_(0x01)                                      /**< \deprecated (SERCOM_SPI_DBGCTRL) Register MASK  (Use SERCOM_SPI_DBGCTRL_Msk instead)  */
#define SERCOM_SPI_DBGCTRL_Msk              _U_(0x01)                                      /**< (SERCOM_SPI_DBGCTRL) Register Mask  */


/* -------- SERCOM_USART_DBGCTRL : (SERCOM Offset: 0x30) (R/W 8) USART Debug Control -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DBGSTOP:1;                 /**< bit:      0  Debug Mode                               */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SERCOM_USART_DBGCTRL_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_DBGCTRL_OFFSET         (0x30)                                        /**<  (SERCOM_USART_DBGCTRL) USART Debug Control  Offset */
#define SERCOM_USART_DBGCTRL_RESETVALUE     _U_(0x00)                                     /**<  (SERCOM_USART_DBGCTRL) USART Debug Control  Reset Value */

#define SERCOM_USART_DBGCTRL_DBGSTOP_Pos    0                                              /**< (SERCOM_USART_DBGCTRL) Debug Mode Position */
#define SERCOM_USART_DBGCTRL_DBGSTOP_Msk    (_U_(0x1) << SERCOM_USART_DBGCTRL_DBGSTOP_Pos)  /**< (SERCOM_USART_DBGCTRL) Debug Mode Mask */
#define SERCOM_USART_DBGCTRL_DBGSTOP        SERCOM_USART_DBGCTRL_DBGSTOP_Msk               /**< \deprecated Old style mask definition for 1 bit bitfield. Use SERCOM_USART_DBGCTRL_DBGSTOP_Msk instead */
#define SERCOM_USART_DBGCTRL_MASK           _U_(0x01)                                      /**< \deprecated (SERCOM_USART_DBGCTRL) Register MASK  (Use SERCOM_USART_DBGCTRL_Msk instead)  */
#define SERCOM_USART_DBGCTRL_Msk            _U_(0x01)                                      /**< (SERCOM_USART_DBGCTRL) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief SERCOM hardware registers */
typedef struct {  /* Serial Communication Interface */
  __IO SERCOM_I2CM_CTRLA_Type         CTRLA;          /**< Offset: 0x00 (R/W  32) I2CM Control A */
  __IO SERCOM_I2CM_CTRLB_Type         CTRLB;          /**< Offset: 0x04 (R/W  32) I2CM Control B */
  __I  uint8_t                        Reserved1[4];
  __IO SERCOM_I2CM_BAUD_Type          BAUD;           /**< Offset: 0x0C (R/W  32) I2CM Baud Rate */
  __I  uint8_t                        Reserved2[4];
  __IO SERCOM_I2CM_INTENCLR_Type      INTENCLR;       /**< Offset: 0x14 (R/W   8) I2CM Interrupt Enable Clear */
  __I  uint8_t                        Reserved3[1];
  __IO SERCOM_I2CM_INTENSET_Type      INTENSET;       /**< Offset: 0x16 (R/W   8) I2CM Interrupt Enable Set */
  __I  uint8_t                        Reserved4[1];
  __IO SERCOM_I2CM_INTFLAG_Type       INTFLAG;        /**< Offset: 0x18 (R/W   8) I2CM Interrupt Flag Status and Clear */
  __I  uint8_t                        Reserved5[1];
  __IO SERCOM_I2CM_STATUS_Type        STATUS;         /**< Offset: 0x1A (R/W  16) I2CM Status */
  __I  SERCOM_I2CM_SYNCBUSY_Type      SYNCBUSY;       /**< Offset: 0x1C (R/   32) I2CM Synchronization Busy */
  __I  uint8_t                        Reserved6[4];
  __IO SERCOM_I2CM_ADDR_Type          ADDR;           /**< Offset: 0x24 (R/W  32) I2CM Address */
  __IO SERCOM_I2CM_DATA_Type          DATA;           /**< Offset: 0x28 (R/W   8) I2CM Data */
  __I  uint8_t                        Reserved7[7];
  __IO SERCOM_I2CM_DBGCTRL_Type       DBGCTRL;        /**< Offset: 0x30 (R/W   8) I2CM Debug Control */
} SercomI2cm;

/** \brief SERCOM hardware registers */
typedef struct {  /* Serial Communication Interface */
  __IO SERCOM_I2CS_CTRLA_Type         CTRLA;          /**< Offset: 0x00 (R/W  32) I2CS Control A */
  __IO SERCOM_I2CS_CTRLB_Type         CTRLB;          /**< Offset: 0x04 (R/W  32) I2CS Control B */
  __I  uint8_t                        Reserved1[12];
  __IO SERCOM_I2CS_INTENCLR_Type      INTENCLR;       /**< Offset: 0x14 (R/W   8) I2CS Interrupt Enable Clear */
  __I  uint8_t                        Reserved2[1];
  __IO SERCOM_I2CS_INTENSET_Type      INTENSET;       /**< Offset: 0x16 (R/W   8) I2CS Interrupt Enable Set */
  __I  uint8_t                        Reserved3[1];
  __IO SERCOM_I2CS_INTFLAG_Type       INTFLAG;        /**< Offset: 0x18 (R/W   8) I2CS Interrupt Flag Status and Clear */
  __I  uint8_t                        Reserved4[1];
  __IO SERCOM_I2CS_STATUS_Type        STATUS;         /**< Offset: 0x1A (R/W  16) I2CS Status */
  __I  SERCOM_I2CS_SYNCBUSY_Type      SYNCBUSY;       /**< Offset: 0x1C (R/   32) I2CS Synchronization Busy */
  __I  uint8_t                        Reserved5[4];
  __IO SERCOM_I2CS_ADDR_Type          ADDR;           /**< Offset: 0x24 (R/W  32) I2CS Address */
  __IO SERCOM_I2CS_DATA_Type          DATA;           /**< Offset: 0x28 (R/W   8) I2CS Data */
} SercomI2cs;

/** \brief SERCOM hardware registers */
typedef struct {  /* Serial Communication Interface */
  __IO SERCOM_SPI_CTRLA_Type          CTRLA;          /**< Offset: 0x00 (R/W  32) SPI Control A */
  __IO SERCOM_SPI_CTRLB_Type          CTRLB;          /**< Offset: 0x04 (R/W  32) SPI Control B */
  __I  uint8_t                        Reserved1[4];
  __IO SERCOM_SPI_BAUD_Type           BAUD;           /**< Offset: 0x0C (R/W   8) SPI Baud Rate */
  __I  uint8_t                        Reserved2[7];
  __IO SERCOM_SPI_INTENCLR_Type       INTENCLR;       /**< Offset: 0x14 (R/W   8) SPI Interrupt Enable Clear */
  __I  uint8_t                        Reserved3[1];
  __IO SERCOM_SPI_INTENSET_Type       INTENSET;       /**< Offset: 0x16 (R/W   8) SPI Interrupt Enable Set */
  __I  uint8_t                        Reserved4[1];
  __IO SERCOM_SPI_INTFLAG_Type        INTFLAG;        /**< Offset: 0x18 (R/W   8) SPI Interrupt Flag Status and Clear */
  __I  uint8_t                        Reserved5[1];
  __IO SERCOM_SPI_STATUS_Type         STATUS;         /**< Offset: 0x1A (R/W  16) SPI Status */
  __I  SERCOM_SPI_SYNCBUSY_Type       SYNCBUSY;       /**< Offset: 0x1C (R/   32) SPI Synchronization Busy */
  __I  uint8_t                        Reserved6[4];
  __IO SERCOM_SPI_ADDR_Type           ADDR;           /**< Offset: 0x24 (R/W  32) SPI Address */
  __IO SERCOM_SPI_DATA_Type           DATA;           /**< Offset: 0x28 (R/W  32) SPI Data */
  __I  uint8_t                        Reserved7[4];
  __IO SERCOM_SPI_DBGCTRL_Type        DBGCTRL;        /**< Offset: 0x30 (R/W   8) SPI Debug Control */
} SercomSpi;

/** \brief SERCOM hardware registers */
typedef struct {  /* Serial Communication Interface */
  __IO SERCOM_USART_CTRLA_Type        CTRLA;          /**< Offset: 0x00 (R/W  32) USART Control A */
  __IO SERCOM_USART_CTRLB_Type        CTRLB;          /**< Offset: 0x04 (R/W  32) USART Control B */
  __IO SERCOM_USART_CTRLC_Type        CTRLC;          /**< Offset: 0x08 (R/W  32) USART Control C */
  __IO SERCOM_USART_BAUD_Type         BAUD;           /**< Offset: 0x0C (R/W  16) USART Baud Rate */
  __IO SERCOM_USART_RXPL_Type         RXPL;           /**< Offset: 0x0E (R/W   8) USART Receive Pulse Length */
  __I  uint8_t                        Reserved1[5];
  __IO SERCOM_USART_INTENCLR_Type     INTENCLR;       /**< Offset: 0x14 (R/W   8) USART Interrupt Enable Clear */
  __I  uint8_t                        Reserved2[1];
  __IO SERCOM_USART_INTENSET_Type     INTENSET;       /**< Offset: 0x16 (R/W   8) USART Interrupt Enable Set */
  __I  uint8_t                        Reserved3[1];
  __IO SERCOM_USART_INTFLAG_Type      INTFLAG;        /**< Offset: 0x18 (R/W   8) USART Interrupt Flag Status and Clear */
  __I  uint8_t                        Reserved4[1];
  __IO SERCOM_USART_STATUS_Type       STATUS;         /**< Offset: 0x1A (R/W  16) USART Status */
  __I  SERCOM_USART_SYNCBUSY_Type     SYNCBUSY;       /**< Offset: 0x1C (R/   32) USART Synchronization Busy */
  __I  SERCOM_USART_RXERRCNT_Type     RXERRCNT;       /**< Offset: 0x20 (R/    8) USART Receive Error Count */
  __I  uint8_t                        Reserved5[7];
  __IO SERCOM_USART_DATA_Type         DATA;           /**< Offset: 0x28 (R/W  16) USART Data */
  __I  uint8_t                        Reserved6[6];
  __IO SERCOM_USART_DBGCTRL_Type      DBGCTRL;        /**< Offset: 0x30 (R/W   8) USART Debug Control */
} SercomUsart;

/** \brief SERCOM hardware registers */
typedef union {  /* Serial Communication Interface */
       SercomI2cm                     I2CM;           /**< I2C Master Mode */
       SercomI2cs                     I2CS;           /**< I2C Slave Mode */
       SercomSpi                      SPI;            /**< SPI Mode */
       SercomUsart                    USART;          /**< USART Mode */
} Sercom;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Serial Communication Interface */

#endif /* _SAML10_SERCOM_COMPONENT_H_ */
