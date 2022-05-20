/**
 * \file
 *
 * \brief Component description for RSTC
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
#ifndef _SAML10_RSTC_COMPONENT_H_
#define _SAML10_RSTC_COMPONENT_H_
#define _SAML10_RSTC_COMPONENT_         /**< \deprecated  Backward compatibility for ASF */

/** \addtogroup SAML_SAML10 Reset Controller
 *  @{
 */
/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR RSTC */
/* ========================================================================== */

#define RSTC_U2239                      /**< (RSTC) Module ID */
#define REV_RSTC 0x300                  /**< (RSTC) Module revision */

/* -------- RSTC_RCAUSE : (RSTC Offset: 0x00) (R/ 8) Reset Cause -------- */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  POR:1;                     /**< bit:      0  Power On Reset                           */
    uint8_t  BODCORE:1;                 /**< bit:      1  Brown Out CORE Detector Reset            */
    uint8_t  BODVDD:1;                  /**< bit:      2  Brown Out VDD Detector Reset             */
    uint8_t  :1;                        /**< bit:      3  Reserved */
    uint8_t  EXT:1;                     /**< bit:      4  External Reset                           */
    uint8_t  WDT:1;                     /**< bit:      5  Watchdog Reset                           */
    uint8_t  SYST:1;                    /**< bit:      6  System Reset Request                     */
    uint8_t  :1;                        /**< bit:      7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} RSTC_RCAUSE_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RSTC_RCAUSE_OFFSET                  (0x00)                                        /**<  (RSTC_RCAUSE) Reset Cause  Offset */

#define RSTC_RCAUSE_POR_Pos                 0                                              /**< (RSTC_RCAUSE) Power On Reset Position */
#define RSTC_RCAUSE_POR_Msk                 (_U_(0x1) << RSTC_RCAUSE_POR_Pos)              /**< (RSTC_RCAUSE) Power On Reset Mask */
#define RSTC_RCAUSE_POR                     RSTC_RCAUSE_POR_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use RSTC_RCAUSE_POR_Msk instead */
#define RSTC_RCAUSE_BODCORE_Pos             1                                              /**< (RSTC_RCAUSE) Brown Out CORE Detector Reset Position */
#define RSTC_RCAUSE_BODCORE_Msk             (_U_(0x1) << RSTC_RCAUSE_BODCORE_Pos)          /**< (RSTC_RCAUSE) Brown Out CORE Detector Reset Mask */
#define RSTC_RCAUSE_BODCORE                 RSTC_RCAUSE_BODCORE_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use RSTC_RCAUSE_BODCORE_Msk instead */
#define RSTC_RCAUSE_BODVDD_Pos              2                                              /**< (RSTC_RCAUSE) Brown Out VDD Detector Reset Position */
#define RSTC_RCAUSE_BODVDD_Msk              (_U_(0x1) << RSTC_RCAUSE_BODVDD_Pos)           /**< (RSTC_RCAUSE) Brown Out VDD Detector Reset Mask */
#define RSTC_RCAUSE_BODVDD                  RSTC_RCAUSE_BODVDD_Msk                         /**< \deprecated Old style mask definition for 1 bit bitfield. Use RSTC_RCAUSE_BODVDD_Msk instead */
#define RSTC_RCAUSE_EXT_Pos                 4                                              /**< (RSTC_RCAUSE) External Reset Position */
#define RSTC_RCAUSE_EXT_Msk                 (_U_(0x1) << RSTC_RCAUSE_EXT_Pos)              /**< (RSTC_RCAUSE) External Reset Mask */
#define RSTC_RCAUSE_EXT                     RSTC_RCAUSE_EXT_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use RSTC_RCAUSE_EXT_Msk instead */
#define RSTC_RCAUSE_WDT_Pos                 5                                              /**< (RSTC_RCAUSE) Watchdog Reset Position */
#define RSTC_RCAUSE_WDT_Msk                 (_U_(0x1) << RSTC_RCAUSE_WDT_Pos)              /**< (RSTC_RCAUSE) Watchdog Reset Mask */
#define RSTC_RCAUSE_WDT                     RSTC_RCAUSE_WDT_Msk                            /**< \deprecated Old style mask definition for 1 bit bitfield. Use RSTC_RCAUSE_WDT_Msk instead */
#define RSTC_RCAUSE_SYST_Pos                6                                              /**< (RSTC_RCAUSE) System Reset Request Position */
#define RSTC_RCAUSE_SYST_Msk                (_U_(0x1) << RSTC_RCAUSE_SYST_Pos)             /**< (RSTC_RCAUSE) System Reset Request Mask */
#define RSTC_RCAUSE_SYST                    RSTC_RCAUSE_SYST_Msk                           /**< \deprecated Old style mask definition for 1 bit bitfield. Use RSTC_RCAUSE_SYST_Msk instead */
#define RSTC_RCAUSE_MASK                    _U_(0x77)                                      /**< \deprecated (RSTC_RCAUSE) Register MASK  (Use RSTC_RCAUSE_Msk instead)  */
#define RSTC_RCAUSE_Msk                     _U_(0x77)                                      /**< (RSTC_RCAUSE) Register Mask  */


#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief RSTC hardware registers */
typedef struct {  /* Reset Controller */
  __I  RSTC_RCAUSE_Type               RCAUSE;         /**< Offset: 0x00 (R/    8) Reset Cause */
} Rstc;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Reset Controller */

#endif /* _SAML10_RSTC_COMPONENT_H_ */
