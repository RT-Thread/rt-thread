/***************************************************************************//**
* \file cyip_sflash_v2.h
*
* \brief
* SFLASH IP definitions
*
********************************************************************************
* \copyright
* (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef _CYIP_SFLASH_V2_H_
#define _CYIP_SFLASH_V2_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                    SFLASH
*******************************************************************************/

#define SFLASH_SECTION_SIZE                     0x00008000UL

/**
  * \brief FLASH Supervisory Region (SFLASH)
  */
typedef struct {
   __IM uint8_t  RESERVED;
  __IOM uint8_t  SI_REVISION_ID;                /*!< 0x00000001 Indicates Silicon Revision ID of the device */
  __IOM uint16_t SILICON_ID;                    /*!< 0x00000002 Indicates Silicon ID of the device */
   __IM uint16_t RESERVED1[5];
  __IOM uint8_t  SYSCALL_ERASE_PROT;            /*!< 0x0000000E Controls the behavior for Erase All and Erase Sector system
                                                                calls */
   __IM uint8_t  RESERVED2[153];
  __IOM uint32_t SFLASH_SVN;                    /*!< 0x000000A8 SFLASH Subversion */
   __IM uint32_t RESERVED3[84];
  __IOM uint32_t FB_FLAGS;                      /*!< 0x000001FC Flash boot flags */
   __IM uint16_t RESERVED4[551];
  __IOM uint16_t EPASS_TEMP_TRIM_TEMP_ROOMSORT; /*!< 0x0000064E On Chip temperature measured using external currents and
                                                                external ADC at ROOM */
  __IOM uint16_t EPASS_TEMP_TRIM_DIODE_ROOMSORT; /*!< 0x00000650 Temperature sensor calibration data for VDDA=3.3V, Temperature
                                                                sensor diode voltage at ROOM */
  __IOM uint16_t EPASS_TEMP_TRIM_VBG_ROOMSORT;  /*!< 0x00000652 Temperature sensor calibration data for VDDA=3.3V, Bandgap
                                                                voltage at ROOM */
  __IOM uint16_t EPASS_TEMP_TRIM_TEMP_COLDSORT; /*!< 0x00000654 On Chip temperature measured using external currents and
                                                                external ADC at COLD */
  __IOM uint16_t EPASS_TEMP_TRIM_DIODE_COLDSORT; /*!< 0x00000656 Temperature sensor calibration data for VDDA=3.3V, Temperature
                                                                sensor diode voltage at COLD */
  __IOM uint16_t EPASS_TEMP_TRIM_VBG_COLDSORT;  /*!< 0x00000658 Temperature sensor calibration data for VDDA=3.3V, Bandgap
                                                                voltage at COLD */
  __IOM uint16_t EPASS_TEMP_TRIM_TEMP_HOTCLASS; /*!< 0x0000065A On Chip temperature measured using external currents and
                                                                external ADC at HOT */
  __IOM uint16_t EPASS_TEMP_TRIM_DIODE_HOTCLASS; /*!< 0x0000065C Temperature sensor calibration data for VDDA=3.3V, Temperature
                                                                sensor diode voltage at HOT */
  __IOM uint16_t EPASS_TEMP_TRIM_VBG_HOTCLASS;  /*!< 0x0000065E Temperature sensor calibration data for VDDA=3.3V, Bandgap
                                                                voltage at HOT */
   __IM uint16_t RESERVED5[5];
  __IOM uint16_t EPASS_TEMP_TRIM_DIODE_ROOMSORT_5V; /*!< 0x0000066A Temperature sensor calibration data for VDDA=5V, Temperature
                                                                sensor diode voltage at ROOM */
  __IOM uint16_t EPASS_TEMP_TRIM_VBG_ROOMSORT_5V; /*!< 0x0000066C Temperature sensor calibration data for VDDA=5V, Bandgap
                                                                voltage at ROOM */
  __IOM uint16_t EPASS_TEMP_TRIM_DIODE_COLDSORT_5V; /*!< 0x0000066E Temperature sensor calibration data for VDDA=5V, Temperature
                                                                sensor diode voltage at COLD */
  __IOM uint16_t EPASS_TEMP_TRIM_VBG_COLDSORT_5V; /*!< 0x00000670 Temperature sensor calibration data for VDDA=5V, Bandgap
                                                                voltage at COLD */
  __IOM uint16_t EPASS_TEMP_TRIM_DIODE_HOTCLASS_5V; /*!< 0x00000672 Temperature sensor calibration data for VDDA=5V, Temperature
                                                                sensor diode voltage at HOT */
  __IOM uint16_t EPASS_TEMP_TRIM_VBG_HOTCLASS_5V; /*!< 0x00000674 Temperature sensor calibration data for VDDA=5V, Bandgap
                                                                voltage at HOT */
   __IM uint16_t RESERVED6[93];
  __IOM uint32_t SRSS_PWR_OFFSET;               /*!< 0x00000730 SRSS_PWR_OFFSET */
  __IOM uint32_t SRSS_PWR_TRIM_HT_PWRSYS_INTERNAL; /*!< 0x00000734 Trim settings when the supply is intended to come from the
                                                                internal regulators */
  __IOM uint32_t SRSS_PWR_TRIM_HT_PWRSYS_EXTERNAL; /*!< 0x00000738 Trim settings for the regulators so they do not interfere with
                                                                external supply */
   __IM uint32_t RESERVED7[49];
  __IOM uint32_t USER_FREE_ROW0[128];           /*!< 0x00000800 USER_FREE_ROW0 */
  __IOM uint32_t USER_FREE_ROW1[128];           /*!< 0x00000A00 USER_FREE_ROW1 */
  __IOM uint32_t USER_FREE_ROW2[128];           /*!< 0x00000C00 USER_FREE_ROW2 */
  __IOM uint32_t USER_FREE_ROW3[128];           /*!< 0x00000E00 USER_FREE_ROW3 */
   __IM uint32_t RESERVED8[512];
  __IOM uint32_t SFLASH_UPDATE_MARKER[2];       /*!< 0x00001800 Markers for storing SFLASH programming states */
   __IM uint32_t RESERVED9[510];
  __IOM uint32_t FLASH_BOOT_OBJECT_SIZE;        /*!< 0x00002000 Flash Boot - Object Size */
  __IOM uint32_t FLASH_BOOT_APP_ID;             /*!< 0x00002004 Flash Boot - Application ID/Version */
   __IM uint32_t RESERVED10[4];
  __IOM uint32_t FLASH_BOOT_VERSION_LOW;        /*!< 0x00002018 Flash Boot - Version Low */
  __IOM uint32_t FLASH_BOOT_FAMILY_ID;          /*!< 0x0000201C Flash Boot - Family ID */
   __IM uint32_t RESERVED11[4344];
  __IOM uint8_t  PUBLIC_KEY[3072];              /*!< 0x00006400 Public key for signature verification (max RSA key size 4096) */
   __IM uint32_t RESERVED12[384];
  __IOM uint32_t APP_PROT_SETTINGS[128];        /*!< 0x00007600 Application protection settings (4*128=512 bytes) */
   __IM uint32_t RESERVED13[256];
  __IOM uint32_t TOC2_OBJECT_SIZE;              /*!< 0x00007C00 Object size in bytes for CRC calculation starting from offset
                                                                0x00 */
  __IOM uint32_t TOC2_MAGIC_NUMBER;             /*!< 0x00007C04 Magic number(0x01211220) */
  __IOM uint32_t TOC2_SMIF_CFG_STRUCT_ADDR;     /*!< 0x00007C08 Null terminated table of pointers representing the SMIF
                                                                configuration structure */
  __IOM uint32_t TOC2_FIRST_USER_APP_ADDR;      /*!< 0x00007C0C Address of First User Application Object */
  __IOM uint32_t TOC2_FIRST_USER_APP_FORMAT;    /*!< 0x00007C10 Format of First User Application Object. 0 - Basic, 1 - Cypress
                                                                standard & 2 - Simplified */
  __IOM uint32_t TOC2_SECOND_USER_APP_ADDR;     /*!< 0x00007C14 Address of Second User Application Object */
  __IOM uint32_t TOC2_SECOND_USER_APP_FORMAT;   /*!< 0x00007C18 Format of Second User Application Object. 0 - Basic, 1 -
                                                                Cypress standard & 2 - Simplified */
  __IOM uint32_t TOC2_FIRST_CMX_1_USER_APP_ADDR; /*!< 0x00007C1C Address of First CM4 or CM7 core1 User Application Object */
  __IOM uint32_t TOC2_SECOND_CMX_1_USER_APP_ADDR; /*!< 0x00007C20 Address of Second CM4 or CM7 core1 User Application Object */
  __IOM uint32_t TOC2_FIRST_CMX_2_USER_APP_ADDR; /*!< 0x00007C24 Address of First CM4 or CM7 core2 User Application Object */
  __IOM uint32_t TOC2_SECOND_CMX_2_USER_APP_ADDR; /*!< 0x00007C28 Address of Second CM4 or CM7 core2 User Application Object */
   __IM uint32_t RESERVED14[52];
  __IOM uint32_t TOC2_SECURITY_UPDATES_MARKER;  /*!< 0x00007CFC Marker for Security Updates */
  __IOM uint32_t TOC2_SHASH_OBJECTS;            /*!< 0x00007D00 Number of additional objects to be verified for SECURE_HASH */
  __IOM uint32_t TOC2_SIGNATURE_VERIF_KEY;      /*!< 0x00007D04 Address of signature verification key (0 if none).The object is
                                                                signature specific key. It is the public key in case of RSA */
  __IOM uint32_t TOC2_APP_PROTECTION_ADDR;      /*!< 0x00007D08 Address of  Application Protection */
   __IM uint32_t RESERVED15[58];
  __IOM uint32_t TOC2_REVISION;                 /*!< 0x00007DF4 Indicates TOC2 Revision. It is not used now. */
  __IOM uint32_t TOC2_FLAGS;                    /*!< 0x00007DF8 Controls default configuration */
} SFLASH_Type;                                  /*!< Size = 32252 (0x7DFC) */


/* SFLASH.SI_REVISION_ID */
#define SFLASH_SI_REVISION_ID_SI_REVISION_ID_Pos 0UL
#define SFLASH_SI_REVISION_ID_SI_REVISION_ID_Msk 0xFFUL
/* SFLASH.SILICON_ID */
#define SFLASH_SILICON_ID_ID_Pos                0UL
#define SFLASH_SILICON_ID_ID_Msk                0xFFFFUL
/* SFLASH.SYSCALL_ERASE_PROT */
#define SFLASH_SYSCALL_ERASE_PROT_DATA_Pos      0UL
#define SFLASH_SYSCALL_ERASE_PROT_DATA_Msk      0xFFUL
/* SFLASH.SFLASH_SVN */
#define SFLASH_SFLASH_SVN_DATA32_Pos            0UL
#define SFLASH_SFLASH_SVN_DATA32_Msk            0xFFFFFFFFUL
/* SFLASH.FB_FLAGS */
#define SFLASH_FB_FLAGS_FB_PIN_CTL_Pos          0UL
#define SFLASH_FB_FLAGS_FB_PIN_CTL_Msk          0x3UL
#define SFLASH_FB_FLAGS_FB_RSA3K_CTL_Pos        2UL
#define SFLASH_FB_FLAGS_FB_RSA3K_CTL_Msk        0xCUL
#define SFLASH_FB_FLAGS_FB_RSA4K_CTL_Pos        4UL
#define SFLASH_FB_FLAGS_FB_RSA4K_CTL_Msk        0x30UL
/* SFLASH.EPASS_TEMP_TRIM_TEMP_ROOMSORT */
#define SFLASH_EPASS_TEMP_TRIM_TEMP_ROOMSORT_DATA16_Pos 0UL
#define SFLASH_EPASS_TEMP_TRIM_TEMP_ROOMSORT_DATA16_Msk 0xFFFFUL
/* SFLASH.EPASS_TEMP_TRIM_DIODE_ROOMSORT */
#define SFLASH_EPASS_TEMP_TRIM_DIODE_ROOMSORT_DATA16_Pos 0UL
#define SFLASH_EPASS_TEMP_TRIM_DIODE_ROOMSORT_DATA16_Msk 0xFFFFUL
/* SFLASH.EPASS_TEMP_TRIM_VBG_ROOMSORT */
#define SFLASH_EPASS_TEMP_TRIM_VBG_ROOMSORT_DATA16_Pos 0UL
#define SFLASH_EPASS_TEMP_TRIM_VBG_ROOMSORT_DATA16_Msk 0xFFFFUL
/* SFLASH.EPASS_TEMP_TRIM_TEMP_COLDSORT */
#define SFLASH_EPASS_TEMP_TRIM_TEMP_COLDSORT_DATA16_Pos 0UL
#define SFLASH_EPASS_TEMP_TRIM_TEMP_COLDSORT_DATA16_Msk 0xFFFFUL
/* SFLASH.EPASS_TEMP_TRIM_DIODE_COLDSORT */
#define SFLASH_EPASS_TEMP_TRIM_DIODE_COLDSORT_DATA16_Pos 0UL
#define SFLASH_EPASS_TEMP_TRIM_DIODE_COLDSORT_DATA16_Msk 0xFFFFUL
/* SFLASH.EPASS_TEMP_TRIM_VBG_COLDSORT */
#define SFLASH_EPASS_TEMP_TRIM_VBG_COLDSORT_DATA16_Pos 0UL
#define SFLASH_EPASS_TEMP_TRIM_VBG_COLDSORT_DATA16_Msk 0xFFFFUL
/* SFLASH.EPASS_TEMP_TRIM_TEMP_HOTCLASS */
#define SFLASH_EPASS_TEMP_TRIM_TEMP_HOTCLASS_DATA16_Pos 0UL
#define SFLASH_EPASS_TEMP_TRIM_TEMP_HOTCLASS_DATA16_Msk 0xFFFFUL
/* SFLASH.EPASS_TEMP_TRIM_DIODE_HOTCLASS */
#define SFLASH_EPASS_TEMP_TRIM_DIODE_HOTCLASS_DATA16_Pos 0UL
#define SFLASH_EPASS_TEMP_TRIM_DIODE_HOTCLASS_DATA16_Msk 0xFFFFUL
/* SFLASH.EPASS_TEMP_TRIM_VBG_HOTCLASS */
#define SFLASH_EPASS_TEMP_TRIM_VBG_HOTCLASS_DATA16_Pos 0UL
#define SFLASH_EPASS_TEMP_TRIM_VBG_HOTCLASS_DATA16_Msk 0xFFFFUL
/* SFLASH.EPASS_TEMP_TRIM_DIODE_ROOMSORT_5V */
#define SFLASH_EPASS_TEMP_TRIM_DIODE_ROOMSORT_5V_DATA16_Pos 0UL
#define SFLASH_EPASS_TEMP_TRIM_DIODE_ROOMSORT_5V_DATA16_Msk 0xFFFFUL
/* SFLASH.EPASS_TEMP_TRIM_VBG_ROOMSORT_5V */
#define SFLASH_EPASS_TEMP_TRIM_VBG_ROOMSORT_5V_DATA16_Pos 0UL
#define SFLASH_EPASS_TEMP_TRIM_VBG_ROOMSORT_5V_DATA16_Msk 0xFFFFUL
/* SFLASH.EPASS_TEMP_TRIM_DIODE_COLDSORT_5V */
#define SFLASH_EPASS_TEMP_TRIM_DIODE_COLDSORT_5V_DATA16_Pos 0UL
#define SFLASH_EPASS_TEMP_TRIM_DIODE_COLDSORT_5V_DATA16_Msk 0xFFFFUL
/* SFLASH.EPASS_TEMP_TRIM_VBG_COLDSORT_5V */
#define SFLASH_EPASS_TEMP_TRIM_VBG_COLDSORT_5V_DATA16_Pos 0UL
#define SFLASH_EPASS_TEMP_TRIM_VBG_COLDSORT_5V_DATA16_Msk 0xFFFFUL
/* SFLASH.EPASS_TEMP_TRIM_DIODE_HOTCLASS_5V */
#define SFLASH_EPASS_TEMP_TRIM_DIODE_HOTCLASS_5V_DATA16_Pos 0UL
#define SFLASH_EPASS_TEMP_TRIM_DIODE_HOTCLASS_5V_DATA16_Msk 0xFFFFUL
/* SFLASH.EPASS_TEMP_TRIM_VBG_HOTCLASS_5V */
#define SFLASH_EPASS_TEMP_TRIM_VBG_HOTCLASS_5V_DATA16_Pos 0UL
#define SFLASH_EPASS_TEMP_TRIM_VBG_HOTCLASS_5V_DATA16_Msk 0xFFFFUL
/* SFLASH.SRSS_PWR_OFFSET */
#define SFLASH_SRSS_PWR_OFFSET_PMIC_VADJ_OFFSET_Pos 0UL
#define SFLASH_SRSS_PWR_OFFSET_PMIC_VADJ_OFFSET_Msk 0x1FUL
#define SFLASH_SRSS_PWR_OFFSET_REGHC_TRANS_VADJ_OFFSET_Pos 8UL
#define SFLASH_SRSS_PWR_OFFSET_REGHC_TRANS_VADJ_OFFSET_Msk 0x1F00UL
/* SFLASH.SRSS_PWR_TRIM_HT_PWRSYS_INTERNAL */
#define SFLASH_SRSS_PWR_TRIM_HT_PWRSYS_INTERNAL_ACT_REG_VTRIM_Pos 0UL
#define SFLASH_SRSS_PWR_TRIM_HT_PWRSYS_INTERNAL_ACT_REG_VTRIM_Msk 0x1FUL
#define SFLASH_SRSS_PWR_TRIM_HT_PWRSYS_INTERNAL_DPSLP_REG_VTRIM_Pos 24UL
#define SFLASH_SRSS_PWR_TRIM_HT_PWRSYS_INTERNAL_DPSLP_REG_VTRIM_Msk 0xF000000UL
/* SFLASH.SRSS_PWR_TRIM_HT_PWRSYS_EXTERNAL */
#define SFLASH_SRSS_PWR_TRIM_HT_PWRSYS_EXTERNAL_ACT_REG_VTRIM_Pos 0UL
#define SFLASH_SRSS_PWR_TRIM_HT_PWRSYS_EXTERNAL_ACT_REG_VTRIM_Msk 0x1FUL
#define SFLASH_SRSS_PWR_TRIM_HT_PWRSYS_EXTERNAL_DPSLP_REG_VTRIM_Pos 24UL
#define SFLASH_SRSS_PWR_TRIM_HT_PWRSYS_EXTERNAL_DPSLP_REG_VTRIM_Msk 0xF000000UL
/* SFLASH.USER_FREE_ROW0 */
#define SFLASH_USER_FREE_ROW0_DATA32_Pos        0UL
#define SFLASH_USER_FREE_ROW0_DATA32_Msk        0xFFFFFFFFUL
/* SFLASH.USER_FREE_ROW1 */
#define SFLASH_USER_FREE_ROW1_DATA32_Pos        0UL
#define SFLASH_USER_FREE_ROW1_DATA32_Msk        0xFFFFFFFFUL
/* SFLASH.USER_FREE_ROW2 */
#define SFLASH_USER_FREE_ROW2_DATA32_Pos        0UL
#define SFLASH_USER_FREE_ROW2_DATA32_Msk        0xFFFFFFFFUL
/* SFLASH.USER_FREE_ROW3 */
#define SFLASH_USER_FREE_ROW3_DATA32_Pos        0UL
#define SFLASH_USER_FREE_ROW3_DATA32_Msk        0xFFFFFFFFUL
/* SFLASH.SFLASH_UPDATE_MARKER */
#define SFLASH_SFLASH_UPDATE_MARKER_DATA32_Pos  0UL
#define SFLASH_SFLASH_UPDATE_MARKER_DATA32_Msk  0xFFFFFFFFUL
/* SFLASH.FLASH_BOOT_OBJECT_SIZE */
#define SFLASH_FLASH_BOOT_OBJECT_SIZE_DATA32_Pos 0UL
#define SFLASH_FLASH_BOOT_OBJECT_SIZE_DATA32_Msk 0xFFFFFFFFUL
/* SFLASH.FLASH_BOOT_APP_ID */
#define SFLASH_FLASH_BOOT_APP_ID_APP_ID_Pos     0UL
#define SFLASH_FLASH_BOOT_APP_ID_APP_ID_Msk     0xFFFFUL
#define SFLASH_FLASH_BOOT_APP_ID_MINOR_VERSION_Pos 16UL
#define SFLASH_FLASH_BOOT_APP_ID_MINOR_VERSION_Msk 0xFF0000UL
#define SFLASH_FLASH_BOOT_APP_ID_MAJOR_VERSION_Pos 24UL
#define SFLASH_FLASH_BOOT_APP_ID_MAJOR_VERSION_Msk 0xF000000UL
/* SFLASH.FLASH_BOOT_VERSION_LOW */
#define SFLASH_FLASH_BOOT_VERSION_LOW_DATA32_Pos 0UL
#define SFLASH_FLASH_BOOT_VERSION_LOW_DATA32_Msk 0xFFFFFFFFUL
/* SFLASH.FLASH_BOOT_FAMILY_ID */
#define SFLASH_FLASH_BOOT_FAMILY_ID_DATA32_Pos  0UL
#define SFLASH_FLASH_BOOT_FAMILY_ID_DATA32_Msk  0xFFFFFFFFUL
/* SFLASH.PUBLIC_KEY */
#define SFLASH_PUBLIC_KEY_DATA_Pos              0UL
#define SFLASH_PUBLIC_KEY_DATA_Msk              0xFFUL
/* SFLASH.APP_PROT_SETTINGS */
#define SFLASH_APP_PROT_SETTINGS_DATA32_Pos     0UL
#define SFLASH_APP_PROT_SETTINGS_DATA32_Msk     0xFFFFFFFFUL
/* SFLASH.TOC2_OBJECT_SIZE */
#define SFLASH_TOC2_OBJECT_SIZE_DATA32_Pos      0UL
#define SFLASH_TOC2_OBJECT_SIZE_DATA32_Msk      0xFFFFFFFFUL
/* SFLASH.TOC2_MAGIC_NUMBER */
#define SFLASH_TOC2_MAGIC_NUMBER_DATA32_Pos     0UL
#define SFLASH_TOC2_MAGIC_NUMBER_DATA32_Msk     0xFFFFFFFFUL
/* SFLASH.TOC2_SMIF_CFG_STRUCT_ADDR */
#define SFLASH_TOC2_SMIF_CFG_STRUCT_ADDR_DATA32_Pos 0UL
#define SFLASH_TOC2_SMIF_CFG_STRUCT_ADDR_DATA32_Msk 0xFFFFFFFFUL
/* SFLASH.TOC2_FIRST_USER_APP_ADDR */
#define SFLASH_TOC2_FIRST_USER_APP_ADDR_DATA32_Pos 0UL
#define SFLASH_TOC2_FIRST_USER_APP_ADDR_DATA32_Msk 0xFFFFFFFFUL
/* SFLASH.TOC2_FIRST_USER_APP_FORMAT */
#define SFLASH_TOC2_FIRST_USER_APP_FORMAT_DATA32_Pos 0UL
#define SFLASH_TOC2_FIRST_USER_APP_FORMAT_DATA32_Msk 0xFFFFFFFFUL
/* SFLASH.TOC2_SECOND_USER_APP_ADDR */
#define SFLASH_TOC2_SECOND_USER_APP_ADDR_DATA32_Pos 0UL
#define SFLASH_TOC2_SECOND_USER_APP_ADDR_DATA32_Msk 0xFFFFFFFFUL
/* SFLASH.TOC2_SECOND_USER_APP_FORMAT */
#define SFLASH_TOC2_SECOND_USER_APP_FORMAT_DATA32_Pos 0UL
#define SFLASH_TOC2_SECOND_USER_APP_FORMAT_DATA32_Msk 0xFFFFFFFFUL
/* SFLASH.TOC2_FIRST_CMX_1_USER_APP_ADDR */
#define SFLASH_TOC2_FIRST_CMX_1_USER_APP_ADDR_DATA32_Pos 0UL
#define SFLASH_TOC2_FIRST_CMX_1_USER_APP_ADDR_DATA32_Msk 0xFFFFFFFFUL
/* SFLASH.TOC2_SECOND_CMX_1_USER_APP_ADDR */
#define SFLASH_TOC2_SECOND_CMX_1_USER_APP_ADDR_DATA32_Pos 0UL
#define SFLASH_TOC2_SECOND_CMX_1_USER_APP_ADDR_DATA32_Msk 0xFFFFFFFFUL
/* SFLASH.TOC2_FIRST_CMX_2_USER_APP_ADDR */
#define SFLASH_TOC2_FIRST_CMX_2_USER_APP_ADDR_DATA32_Pos 0UL
#define SFLASH_TOC2_FIRST_CMX_2_USER_APP_ADDR_DATA32_Msk 0xFFFFFFFFUL
/* SFLASH.TOC2_SECOND_CMX_2_USER_APP_ADDR */
#define SFLASH_TOC2_SECOND_CMX_2_USER_APP_ADDR_DATA32_Pos 0UL
#define SFLASH_TOC2_SECOND_CMX_2_USER_APP_ADDR_DATA32_Msk 0xFFFFFFFFUL
/* SFLASH.TOC2_SECURITY_UPDATES_MARKER */
#define SFLASH_TOC2_SECURITY_UPDATES_MARKER_DATA32_Pos 0UL
#define SFLASH_TOC2_SECURITY_UPDATES_MARKER_DATA32_Msk 0xFFFFFFFFUL
/* SFLASH.TOC2_SHASH_OBJECTS */
#define SFLASH_TOC2_SHASH_OBJECTS_DATA32_Pos    0UL
#define SFLASH_TOC2_SHASH_OBJECTS_DATA32_Msk    0xFFFFFFFFUL
/* SFLASH.TOC2_SIGNATURE_VERIF_KEY */
#define SFLASH_TOC2_SIGNATURE_VERIF_KEY_DATA32_Pos 0UL
#define SFLASH_TOC2_SIGNATURE_VERIF_KEY_DATA32_Msk 0xFFFFFFFFUL
/* SFLASH.TOC2_APP_PROTECTION_ADDR */
#define SFLASH_TOC2_APP_PROTECTION_ADDR_DATA32_Pos 0UL
#define SFLASH_TOC2_APP_PROTECTION_ADDR_DATA32_Msk 0xFFFFFFFFUL
/* SFLASH.TOC2_REVISION */
#define SFLASH_TOC2_REVISION_DATA32_Pos         0UL
#define SFLASH_TOC2_REVISION_DATA32_Msk         0xFFFFFFFFUL
/* SFLASH.TOC2_FLAGS */
#define SFLASH_TOC2_FLAGS_CLOCK_CONFIG_Pos      0UL
#define SFLASH_TOC2_FLAGS_CLOCK_CONFIG_Msk      0x3UL
#define SFLASH_TOC2_FLAGS_LISTEN_WINDOW_Pos     2UL
#define SFLASH_TOC2_FLAGS_LISTEN_WINDOW_Msk     0x1CUL
#define SFLASH_TOC2_FLAGS_SWJ_PINS_CTL_Pos      5UL
#define SFLASH_TOC2_FLAGS_SWJ_PINS_CTL_Msk      0x60UL
#define SFLASH_TOC2_FLAGS_APP_AUTH_CTL_Pos      7UL
#define SFLASH_TOC2_FLAGS_APP_AUTH_CTL_Msk      0x180UL
#define SFLASH_TOC2_FLAGS_FB_BOOTLOADER_CTL_Pos 9UL
#define SFLASH_TOC2_FLAGS_FB_BOOTLOADER_CTL_Msk 0x600UL


#endif /* _CYIP_SFLASH_V2_H_ */


/* [] END OF FILE */
