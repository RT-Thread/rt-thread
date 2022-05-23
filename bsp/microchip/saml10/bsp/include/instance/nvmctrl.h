/**
 * \file
 *
 * \brief Instance description for NVMCTRL
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
#ifndef _SAML10_NVMCTRL_INSTANCE_H_
#define _SAML10_NVMCTRL_INSTANCE_H_

/* ========== Register definition for NVMCTRL peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_NVMCTRL_CTRLA       (0x41004000) /**< (NVMCTRL) Control A */
#define REG_NVMCTRL_CTRLB       (0x41004004) /**< (NVMCTRL) Control B */
#define REG_NVMCTRL_CTRLC       (0x41004008) /**< (NVMCTRL) Control C */
#define REG_NVMCTRL_EVCTRL      (0x4100400A) /**< (NVMCTRL) Event Control */
#define REG_NVMCTRL_INTENCLR    (0x4100400C) /**< (NVMCTRL) Interrupt Enable Clear */
#define REG_NVMCTRL_INTENSET    (0x41004010) /**< (NVMCTRL) Interrupt Enable Set */
#define REG_NVMCTRL_INTFLAG     (0x41004014) /**< (NVMCTRL) Interrupt Flag Status and Clear */
#define REG_NVMCTRL_STATUS      (0x41004018) /**< (NVMCTRL) Status */
#define REG_NVMCTRL_ADDR        (0x4100401C) /**< (NVMCTRL) Address */
#define REG_NVMCTRL_SULCK       (0x41004020) /**< (NVMCTRL) Secure Unlock Register */
#define REG_NVMCTRL_NSULCK      (0x41004022) /**< (NVMCTRL) Non-Secure Unlock Register */
#define REG_NVMCTRL_PARAM       (0x41004024) /**< (NVMCTRL) NVM Parameter */
#define REG_NVMCTRL_DSCC        (0x41004030) /**< (NVMCTRL) Data Scramble Configuration */
#define REG_NVMCTRL_SECCTRL     (0x41004034) /**< (NVMCTRL) Security Control */
#define REG_NVMCTRL_SCFGB       (0x41004038) /**< (NVMCTRL) Secure Boot Configuration */
#define REG_NVMCTRL_SCFGAD      (0x4100403C) /**< (NVMCTRL) Secure Application and Data Configuration */
#define REG_NVMCTRL_NONSEC      (0x41004040) /**< (NVMCTRL) Non-secure Write Enable */
#define REG_NVMCTRL_NSCHK       (0x41004044) /**< (NVMCTRL) Non-secure Write Reference Value */

#else

#define REG_NVMCTRL_CTRLA       (*(__O  uint16_t*)0x41004000U) /**< (NVMCTRL) Control A */
#define REG_NVMCTRL_CTRLB       (*(__IO uint32_t*)0x41004004U) /**< (NVMCTRL) Control B */
#define REG_NVMCTRL_CTRLC       (*(__IO uint8_t*)0x41004008U) /**< (NVMCTRL) Control C */
#define REG_NVMCTRL_EVCTRL      (*(__IO uint8_t*)0x4100400AU) /**< (NVMCTRL) Event Control */
#define REG_NVMCTRL_INTENCLR    (*(__IO uint8_t*)0x4100400CU) /**< (NVMCTRL) Interrupt Enable Clear */
#define REG_NVMCTRL_INTENSET    (*(__IO uint8_t*)0x41004010U) /**< (NVMCTRL) Interrupt Enable Set */
#define REG_NVMCTRL_INTFLAG     (*(__IO uint8_t*)0x41004014U) /**< (NVMCTRL) Interrupt Flag Status and Clear */
#define REG_NVMCTRL_STATUS      (*(__I  uint16_t*)0x41004018U) /**< (NVMCTRL) Status */
#define REG_NVMCTRL_ADDR        (*(__IO uint32_t*)0x4100401CU) /**< (NVMCTRL) Address */
#define REG_NVMCTRL_SULCK       (*(__IO uint16_t*)0x41004020U) /**< (NVMCTRL) Secure Unlock Register */
#define REG_NVMCTRL_NSULCK      (*(__IO uint16_t*)0x41004022U) /**< (NVMCTRL) Non-Secure Unlock Register */
#define REG_NVMCTRL_PARAM       (*(__IO uint32_t*)0x41004024U) /**< (NVMCTRL) NVM Parameter */
#define REG_NVMCTRL_DSCC        (*(__O  uint32_t*)0x41004030U) /**< (NVMCTRL) Data Scramble Configuration */
#define REG_NVMCTRL_SECCTRL     (*(__IO uint32_t*)0x41004034U) /**< (NVMCTRL) Security Control */
#define REG_NVMCTRL_SCFGB       (*(__IO uint32_t*)0x41004038U) /**< (NVMCTRL) Secure Boot Configuration */
#define REG_NVMCTRL_SCFGAD      (*(__IO uint32_t*)0x4100403CU) /**< (NVMCTRL) Secure Application and Data Configuration */
#define REG_NVMCTRL_NONSEC      (*(__IO uint32_t*)0x41004040U) /**< (NVMCTRL) Non-secure Write Enable */
#define REG_NVMCTRL_NSCHK       (*(__IO uint32_t*)0x41004044U) /**< (NVMCTRL) Non-secure Write Reference Value */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for NVMCTRL peripheral ========== */
#define NVMCTRL_DATAFLASH_PAGES                  32         
#define NVMCTRL_PMSB                             3          
#define NVMCTRL_PSZ_BITS                         6          
#define NVMCTRL_ROW_PAGES                        4          
#define NVMCTRL_SECURE_IMPLEMENTED               1          /* Security Configuration implemented? */
#define NVMCTRL_FLASH_SIZE                       65536      
#define NVMCTRL_PAGE_SIZE                        64         
#define NVMCTRL_PAGES                            1024       
#define NVMCTRL_PAGES_PR_REGION                  64         
#define NVMCTRL_PSM_0_FRMFW_FWS_1_MAX_FREQ       12000000   
#define NVMCTRL_PSM_0_FRMLP_FWS_0_MAX_FREQ       18000000   
#define NVMCTRL_PSM_0_FRMLP_FWS_1_MAX_FREQ       36000000   
#define NVMCTRL_PSM_0_FRMHS_FWS_0_MAX_FREQ       25000000   
#define NVMCTRL_PSM_0_FRMHS_FWS_1_MAX_FREQ       50000000   
#define NVMCTRL_PSM_1_FRMFW_FWS_1_MAX_FREQ       12000000   
#define NVMCTRL_PSM_1_FRMLP_FWS_0_MAX_FREQ       8000000    
#define NVMCTRL_PSM_1_FRMLP_FWS_1_MAX_FREQ       12000000   
#define NVMCTRL_INSTANCE_ID                      34         

#endif /* _SAML10_NVMCTRL_INSTANCE_ */
