/***************************************************************************//**
* \file cyip_efuse_data_v3_cyw20829.h
*
* \brief
* EFUSE_DATA IP definitions
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

#ifndef _CYIP_EFUSE_DATA_V3_CYW20829_H_
#define _CYIP_EFUSE_DATA_V3_CYW20829_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                  EFUSE_DATA
*******************************************************************************/

#define EFUSE_DATA_SECTION_SIZE                 0x00000200UL

/**
  * \brief eFUSE memory (EFUSE_DATA)
  */
typedef struct {
   __IM uint32_t RESERVED;
  __IOM uint32_t NUM_ZEROS;                     /*!< 0x00000004 Number of zeros for 2 OEM Keys hash */
  __IOM uint32_t ACCESS_RESTRICT;               /*!< 0x00000008 Access Restrictions for Secure/Normal_No_Secure and Dead */
   __IM uint32_t RESERVED1[9];
  __IOM uint32_t WOUNDING;                      /*!< 0x00000030 Wounding (CPUSS_RAM, LIN, CAN_FD), ICV Key Revocation, and
                                                                Number of Zeros (1,2,3) */
  __IOM uint32_t BLE_RADIO_TRIM_0;              /*!< 0x00000034 BLE Radio Trim 0 (32 bits) */
  __IOM uint32_t BLE_RADIO_TRIM_1;              /*!< 0x00000038 BLE Radio Trim 1 (32 bits) */
  __IOM uint32_t BLE_RADIO_TRIM_2;              /*!< 0x0000003C BLE Radio Trim 2 (8 bits), BLE, BLE Access, HCI Mode, BLESS Key
                                                                Revocation */
  __IOM uint32_t OEM_KEY_0_HASH[4];             /*!< 0x00000040 OEM Key 0 Hash (16 bytes Hash of OEM Public Key) */
  __IOM uint32_t OEM_KEY_1_HASH[4];             /*!< 0x00000050 OEM Key 1 Hash (16 bytes Hash of OEM Public Key) */
  __IOM uint32_t NV_COUNTER;                    /*!< 0x00000060 Anti-rollback (upto 32 updates) */
  __IOM uint32_t OEM_CONFIG;                    /*!< 0x00000064 OEM Key Revocation and SMIF Configuration */
   __IM uint32_t RESERVED2[2];
  __IOM uint32_t DEVICE_ID;                     /*!< 0x00000070 Device ID (16-bit Silicon Id and 12-bit Family Id) */
  __IOM uint32_t DIE_0;                         /*!< 0x00000074 Die Lot and Die Wafer */
  __IOM uint32_t DIE_1;                         /*!< 0x00000078 Die X, Die Y, Die Sort, and Die Day */
  __IOM uint32_t DIE_2;                         /*!< 0x0000007C Die Month, Die Year, and Silicon Revision Id */
} EFUSE_DATA_Type;                              /*!< Size = 128 (0x80) */


/* EFUSE_DATA.NUM_ZEROS */
#define EFUSE_DATA_NUM_ZEROS_KEY_0_HASH_Pos     0UL
#define EFUSE_DATA_NUM_ZEROS_KEY_0_HASH_Msk     0xFFUL
#define EFUSE_DATA_NUM_ZEROS_KEY_1_HASH_Pos     8UL
#define EFUSE_DATA_NUM_ZEROS_KEY_1_HASH_Msk     0xFF00UL
#define EFUSE_DATA_NUM_ZEROS_UNUSED_3_Pos       16UL
#define EFUSE_DATA_NUM_ZEROS_UNUSED_3_Msk       0xFFFF0000UL
/* EFUSE_DATA.ACCESS_RESTRICT */
#define EFUSE_DATA_ACCESS_RESTRICT_S_NS_AP_CTL_CM33_Pos 0UL
#define EFUSE_DATA_ACCESS_RESTRICT_S_NS_AP_CTL_CM33_Msk 0x3UL
#define EFUSE_DATA_ACCESS_RESTRICT_S_NS_AP_CTL_SYS_Pos 2UL
#define EFUSE_DATA_ACCESS_RESTRICT_S_NS_AP_CTL_SYS_Msk 0xCUL
#define EFUSE_DATA_ACCESS_RESTRICT_S_NS_AP_CTL_DBG_Pos 4UL
#define EFUSE_DATA_ACCESS_RESTRICT_S_NS_AP_CTL_DBG_Msk 0x30UL
#define EFUSE_DATA_ACCESS_RESTRICT_S_NS_AP_CTL_NID_Pos 6UL
#define EFUSE_DATA_ACCESS_RESTRICT_S_NS_AP_CTL_NID_Msk 0xC0UL
#define EFUSE_DATA_ACCESS_RESTRICT_S_NS_SYS_AP_MPC_PPC_ENABLE_Pos 8UL
#define EFUSE_DATA_ACCESS_RESTRICT_S_NS_SYS_AP_MPC_PPC_ENABLE_Msk 0x100UL
#define EFUSE_DATA_ACCESS_RESTRICT_S_NS_SRAM_Pos 9UL
#define EFUSE_DATA_ACCESS_RESTRICT_S_NS_SRAM_Msk 0xE00UL
#define EFUSE_DATA_ACCESS_RESTRICT_S_NS_MMIO_Pos 12UL
#define EFUSE_DATA_ACCESS_RESTRICT_S_NS_MMIO_Msk 0x3000UL
#define EFUSE_DATA_ACCESS_RESTRICT_DEAD_AP_CTL_CM33_Pos 14UL
#define EFUSE_DATA_ACCESS_RESTRICT_DEAD_AP_CTL_CM33_Msk 0xC000UL
#define EFUSE_DATA_ACCESS_RESTRICT_DEAD_AP_CTL_SYS_Pos 16UL
#define EFUSE_DATA_ACCESS_RESTRICT_DEAD_AP_CTL_SYS_Msk 0x30000UL
#define EFUSE_DATA_ACCESS_RESTRICT_DEAD_AP_CTL_DBG_Pos 18UL
#define EFUSE_DATA_ACCESS_RESTRICT_DEAD_AP_CTL_DBG_Msk 0xC0000UL
#define EFUSE_DATA_ACCESS_RESTRICT_DEAD_AP_CTL_NID_Pos 20UL
#define EFUSE_DATA_ACCESS_RESTRICT_DEAD_AP_CTL_NID_Msk 0x300000UL
#define EFUSE_DATA_ACCESS_RESTRICT_DEAD_SYS_AP_MPC_PPC_ENABLE_Pos 22UL
#define EFUSE_DATA_ACCESS_RESTRICT_DEAD_SYS_AP_MPC_PPC_ENABLE_Msk 0x400000UL
#define EFUSE_DATA_ACCESS_RESTRICT_DEAD_SRAM_Pos 23UL
#define EFUSE_DATA_ACCESS_RESTRICT_DEAD_SRAM_Msk 0x3800000UL
#define EFUSE_DATA_ACCESS_RESTRICT_DEAD_MMIO_Pos 26UL
#define EFUSE_DATA_ACCESS_RESTRICT_DEAD_MMIO_Msk 0xC000000UL
#define EFUSE_DATA_ACCESS_RESTRICT_UNUSED_4_Pos 28UL
#define EFUSE_DATA_ACCESS_RESTRICT_UNUSED_4_Msk 0xF0000000UL
/* EFUSE_DATA.WOUNDING */
#define EFUSE_DATA_WOUNDING_CPUSS_RAM_Pos       0UL
#define EFUSE_DATA_WOUNDING_CPUSS_RAM_Msk       0x1UL
#define EFUSE_DATA_WOUNDING_LIN_Pos             1UL
#define EFUSE_DATA_WOUNDING_LIN_Msk             0x2UL
#define EFUSE_DATA_WOUNDING_CAN_FD_Pos          2UL
#define EFUSE_DATA_WOUNDING_CAN_FD_Msk          0x4UL
#define EFUSE_DATA_WOUNDING_SRAM_REPAIRED_Pos   3UL
#define EFUSE_DATA_WOUNDING_SRAM_REPAIRED_Msk   0x8UL
#define EFUSE_DATA_WOUNDING_LISTEN_WINDOW_Pos   4UL
#define EFUSE_DATA_WOUNDING_LISTEN_WINDOW_Msk   0x30UL
#define EFUSE_DATA_WOUNDING_ICV_KEY_REVOCATION_Pos 6UL
#define EFUSE_DATA_WOUNDING_ICV_KEY_REVOCATION_Msk 0x40UL
#define EFUSE_DATA_WOUNDING_UNUSED_11_Pos       7UL
#define EFUSE_DATA_WOUNDING_UNUSED_11_Msk       0xF80UL
#define EFUSE_DATA_WOUNDING_NUM_ZEROS_1_Pos     12UL
#define EFUSE_DATA_WOUNDING_NUM_ZEROS_1_Msk     0x7F000UL
#define EFUSE_DATA_WOUNDING_NUM_ZEROS_2_Pos     19UL
#define EFUSE_DATA_WOUNDING_NUM_ZEROS_2_Msk     0x3F80000UL
#define EFUSE_DATA_WOUNDING_NUM_ZEROS_3_Pos     26UL
#define EFUSE_DATA_WOUNDING_NUM_ZEROS_3_Msk     0xFC000000UL
/* EFUSE_DATA.BLE_RADIO_TRIM_0 */
#define EFUSE_DATA_BLE_RADIO_TRIM_0_RCAL_Pos    0UL
#define EFUSE_DATA_BLE_RADIO_TRIM_0_RCAL_Msk    0xFUL
#define EFUSE_DATA_BLE_RADIO_TRIM_0_RCCAL_Pos   4UL
#define EFUSE_DATA_BLE_RADIO_TRIM_0_RCCAL_Msk   0xF0UL
#define EFUSE_DATA_BLE_RADIO_TRIM_0_TEMP_SENSOR_Pos 8UL
#define EFUSE_DATA_BLE_RADIO_TRIM_0_TEMP_SENSOR_Msk 0xFFF00UL
#define EFUSE_DATA_BLE_RADIO_TRIM_0_LOIQ_CAL_KAPPA_Pos 20UL
#define EFUSE_DATA_BLE_RADIO_TRIM_0_LOIQ_CAL_KAPPA_Msk 0x3F00000UL
#define EFUSE_DATA_BLE_RADIO_TRIM_0_LOIQ_CAL_THETA_Pos 26UL
#define EFUSE_DATA_BLE_RADIO_TRIM_0_LOIQ_CAL_THETA_Msk 0xFC000000UL
/* EFUSE_DATA.BLE_RADIO_TRIM_1 */
#define EFUSE_DATA_BLE_RADIO_TRIM_1_LOIQ_CAL_DCI_Pos 0UL
#define EFUSE_DATA_BLE_RADIO_TRIM_1_LOIQ_CAL_DCI_Msk 0x7FFUL
#define EFUSE_DATA_BLE_RADIO_TRIM_1_LOIQ_CAL_DCQ_Pos 11UL
#define EFUSE_DATA_BLE_RADIO_TRIM_1_LOIQ_CAL_DCQ_Msk 0x3FF800UL
#define EFUSE_DATA_BLE_RADIO_TRIM_1_OUTPUT_POWER_CAL_0_Pos 22UL
#define EFUSE_DATA_BLE_RADIO_TRIM_1_OUTPUT_POWER_CAL_0_Msk 0xFFC00000UL
/* EFUSE_DATA.BLE_RADIO_TRIM_2 */
#define EFUSE_DATA_BLE_RADIO_TRIM_2_OUTPUT_POWER_CAL_1_Pos 0UL
#define EFUSE_DATA_BLE_RADIO_TRIM_2_OUTPUT_POWER_CAL_1_Msk 0xFFUL
#define EFUSE_DATA_BLE_RADIO_TRIM_2_BLE_Pos     8UL
#define EFUSE_DATA_BLE_RADIO_TRIM_2_BLE_Msk     0x300UL
#define EFUSE_DATA_BLE_RADIO_TRIM_2_BLE_ACCESS_Pos 10UL
#define EFUSE_DATA_BLE_RADIO_TRIM_2_BLE_ACCESS_Msk 0x400UL
#define EFUSE_DATA_BLE_RADIO_TRIM_2_HCI_MODE_Pos 11UL
#define EFUSE_DATA_BLE_RADIO_TRIM_2_HCI_MODE_Msk 0x800UL
#define EFUSE_DATA_BLE_RADIO_TRIM_2_BLE_KEY_REVOCATION_Pos 12UL
#define EFUSE_DATA_BLE_RADIO_TRIM_2_BLE_KEY_REVOCATION_Msk 0x1000UL
#define EFUSE_DATA_BLE_RADIO_TRIM_2_OUTPUT_POWER_CAL_2_Pos 13UL
#define EFUSE_DATA_BLE_RADIO_TRIM_2_OUTPUT_POWER_CAL_2_Msk 0x6000UL
#define EFUSE_DATA_BLE_RADIO_TRIM_2_BLE_TRIM_VALID_Pos 15UL
#define EFUSE_DATA_BLE_RADIO_TRIM_2_BLE_TRIM_VALID_Msk 0x8000UL
#define EFUSE_DATA_BLE_RADIO_TRIM_2_UNUSED_12_Pos 16UL
#define EFUSE_DATA_BLE_RADIO_TRIM_2_UNUSED_12_Msk 0xFFFF0000UL
/* EFUSE_DATA.OEM_KEY_0_HASH */
#define EFUSE_DATA_OEM_KEY_0_HASH_DATA32_Pos    0UL
#define EFUSE_DATA_OEM_KEY_0_HASH_DATA32_Msk    0xFFFFFFFFUL
/* EFUSE_DATA.OEM_KEY_1_HASH */
#define EFUSE_DATA_OEM_KEY_1_HASH_DATA32_Pos    0UL
#define EFUSE_DATA_OEM_KEY_1_HASH_DATA32_Msk    0xFFFFFFFFUL
/* EFUSE_DATA.NV_COUNTER */
#define EFUSE_DATA_NV_COUNTER_ANTI_ROLLBACK_Pos 0UL
#define EFUSE_DATA_NV_COUNTER_ANTI_ROLLBACK_Msk 0xFFFFFFFFUL
/* EFUSE_DATA.OEM_CONFIG */
#define EFUSE_DATA_OEM_CONFIG_SMIF_CFG_Pos      0UL
#define EFUSE_DATA_OEM_CONFIG_SMIF_CFG_Msk      0xFFFUL
#define EFUSE_DATA_OEM_CONFIG_OEM_KEY_REVOCATION_Pos 12UL
#define EFUSE_DATA_OEM_CONFIG_OEM_KEY_REVOCATION_Msk 0x1000UL
#define EFUSE_DATA_OEM_CONFIG_UNUSED_13_Pos     13UL
#define EFUSE_DATA_OEM_CONFIG_UNUSED_13_Msk     0xFFFFE000UL
/* EFUSE_DATA.DEVICE_ID */
#define EFUSE_DATA_DEVICE_ID_SILICON_ID_Pos     0UL
#define EFUSE_DATA_DEVICE_ID_SILICON_ID_Msk     0xFFFFUL
#define EFUSE_DATA_DEVICE_ID_FAMILY_ID_Pos      16UL
#define EFUSE_DATA_DEVICE_ID_FAMILY_ID_Msk      0xFFF0000UL
#define EFUSE_DATA_DEVICE_ID_UNUSED_16_Pos      28UL
#define EFUSE_DATA_DEVICE_ID_UNUSED_16_Msk      0xF0000000UL
/* EFUSE_DATA.DIE_0 */
#define EFUSE_DATA_DIE_0_LOT_Pos                0UL
#define EFUSE_DATA_DIE_0_LOT_Msk                0xFFFFFFUL
#define EFUSE_DATA_DIE_0_WAFER_Pos              24UL
#define EFUSE_DATA_DIE_0_WAFER_Msk              0xFF000000UL
/* EFUSE_DATA.DIE_1 */
#define EFUSE_DATA_DIE_1_X_Pos                  0UL
#define EFUSE_DATA_DIE_1_X_Msk                  0xFFUL
#define EFUSE_DATA_DIE_1_Y_Pos                  8UL
#define EFUSE_DATA_DIE_1_Y_Msk                  0xFF00UL
#define EFUSE_DATA_DIE_1_SORT_Pos               16UL
#define EFUSE_DATA_DIE_1_SORT_Msk               0xFF0000UL
#define EFUSE_DATA_DIE_1_DAY_Pos                24UL
#define EFUSE_DATA_DIE_1_DAY_Msk                0xFF000000UL
/* EFUSE_DATA.DIE_2 */
#define EFUSE_DATA_DIE_2_MONTH_Pos              0UL
#define EFUSE_DATA_DIE_2_MONTH_Msk              0xFFUL
#define EFUSE_DATA_DIE_2_YEAR_Pos               8UL
#define EFUSE_DATA_DIE_2_YEAR_Msk               0xFF00UL
#define EFUSE_DATA_DIE_2_REVISION_ID_Pos        16UL
#define EFUSE_DATA_DIE_2_REVISION_ID_Msk        0xFF0000UL
#define EFUSE_DATA_DIE_2_UNUSED_17_Pos          24UL
#define EFUSE_DATA_DIE_2_UNUSED_17_Msk          0xFF000000UL


#endif /* _CYIP_EFUSE_DATA_V3_CYW20829_H_ */


/* [] END OF FILE */
