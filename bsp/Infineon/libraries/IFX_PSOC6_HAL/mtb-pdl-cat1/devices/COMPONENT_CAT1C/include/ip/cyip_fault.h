/***************************************************************************//**
* \file cyip_fault.h
*
* \brief
* FAULT IP definitions
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

#ifndef _CYIP_FAULT_H_
#define _CYIP_FAULT_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                    FAULT
*******************************************************************************/

#define FAULT_STRUCT_SECTION_SIZE               0x00000100UL
#define FAULT_SECTION_SIZE                      0x00010000UL

/**
  * \brief Fault structure (FAULT_STRUCT)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 Fault control */
   __IM uint32_t RESERVED[2];
  __IOM uint32_t STATUS;                        /*!< 0x0000000C Fault status */
  __IOM uint32_t DATA[4];                       /*!< 0x00000010 Fault data */
   __IM uint32_t RESERVED1[8];
   __IM uint32_t PENDING0;                      /*!< 0x00000040 Fault pending 0 */
   __IM uint32_t PENDING1;                      /*!< 0x00000044 Fault pending 1 */
   __IM uint32_t PENDING2;                      /*!< 0x00000048 Fault pending 2 */
   __IM uint32_t RESERVED2;
  __IOM uint32_t MASK0;                         /*!< 0x00000050 Fault mask 0 */
  __IOM uint32_t MASK1;                         /*!< 0x00000054 Fault mask 1 */
  __IOM uint32_t MASK2;                         /*!< 0x00000058 Fault mask 2 */
   __IM uint32_t RESERVED3[25];
  __IOM uint32_t INTR;                          /*!< 0x000000C0 Interrupt */
  __IOM uint32_t INTR_SET;                      /*!< 0x000000C4 Interrupt set */
  __IOM uint32_t INTR_MASK;                     /*!< 0x000000C8 Interrupt mask */
   __IM uint32_t INTR_MASKED;                   /*!< 0x000000CC Interrupt masked */
   __IM uint32_t RESERVED4[12];
} FAULT_STRUCT_Type;                            /*!< Size = 256 (0x100) */

/**
  * \brief Fault structures (FAULT)
  */
typedef struct {
        FAULT_STRUCT_Type STRUCT[4];            /*!< 0x00000000 Fault structure */
} FAULT_Type;                                   /*!< Size = 1024 (0x400) */


/* FAULT_STRUCT.CTL */
#define FAULT_STRUCT_CTL_TR_EN_Pos              0UL
#define FAULT_STRUCT_CTL_TR_EN_Msk              0x1UL
#define FAULT_STRUCT_CTL_OUT_EN_Pos             1UL
#define FAULT_STRUCT_CTL_OUT_EN_Msk             0x2UL
#define FAULT_STRUCT_CTL_RESET_REQ_EN_Pos       2UL
#define FAULT_STRUCT_CTL_RESET_REQ_EN_Msk       0x4UL
/* FAULT_STRUCT.STATUS */
#define FAULT_STRUCT_STATUS_IDX_Pos             0UL
#define FAULT_STRUCT_STATUS_IDX_Msk             0x7FUL
#define FAULT_STRUCT_STATUS_VALID_Pos           31UL
#define FAULT_STRUCT_STATUS_VALID_Msk           0x80000000UL
/* FAULT_STRUCT.DATA */
#define FAULT_STRUCT_DATA_DATA_Pos              0UL
#define FAULT_STRUCT_DATA_DATA_Msk              0xFFFFFFFFUL
/* FAULT_STRUCT.PENDING0 */
#define FAULT_STRUCT_PENDING0_SOURCE_Pos        0UL
#define FAULT_STRUCT_PENDING0_SOURCE_Msk        0xFFFFFFFFUL
/* FAULT_STRUCT.PENDING1 */
#define FAULT_STRUCT_PENDING1_SOURCE_Pos        0UL
#define FAULT_STRUCT_PENDING1_SOURCE_Msk        0xFFFFFFFFUL
/* FAULT_STRUCT.PENDING2 */
#define FAULT_STRUCT_PENDING2_SOURCE_Pos        0UL
#define FAULT_STRUCT_PENDING2_SOURCE_Msk        0xFFFFFFFFUL
/* FAULT_STRUCT.MASK0 */
#define FAULT_STRUCT_MASK0_SOURCE_Pos           0UL
#define FAULT_STRUCT_MASK0_SOURCE_Msk           0xFFFFFFFFUL
/* FAULT_STRUCT.MASK1 */
#define FAULT_STRUCT_MASK1_SOURCE_Pos           0UL
#define FAULT_STRUCT_MASK1_SOURCE_Msk           0xFFFFFFFFUL
/* FAULT_STRUCT.MASK2 */
#define FAULT_STRUCT_MASK2_SOURCE_Pos           0UL
#define FAULT_STRUCT_MASK2_SOURCE_Msk           0xFFFFFFFFUL
/* FAULT_STRUCT.INTR */
#define FAULT_STRUCT_INTR_FAULT_Pos             0UL
#define FAULT_STRUCT_INTR_FAULT_Msk             0x1UL
/* FAULT_STRUCT.INTR_SET */
#define FAULT_STRUCT_INTR_SET_FAULT_Pos         0UL
#define FAULT_STRUCT_INTR_SET_FAULT_Msk         0x1UL
/* FAULT_STRUCT.INTR_MASK */
#define FAULT_STRUCT_INTR_MASK_FAULT_Pos        0UL
#define FAULT_STRUCT_INTR_MASK_FAULT_Msk        0x1UL
/* FAULT_STRUCT.INTR_MASKED */
#define FAULT_STRUCT_INTR_MASKED_FAULT_Pos      0UL
#define FAULT_STRUCT_INTR_MASKED_FAULT_Msk      0x1UL


/**
  * \brief Instances of Fault data register.
  */
typedef enum
{
    CY_SYSFAULT_MPU_0                =   0,     /* Bus master 0 MPU/SMPU. */
    CY_SYSFAULT_MPU_1                =   1,     /* Bus master 1 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_2                =   2,     /* Bus master 2 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_3                =   3,     /* Bus master 3 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_4                =   4,     /* Bus master 4 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_5                =   5,     /* Bus master 5 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_6                =   6,     /* Bus master 6 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_7                =   7,     /* Bus master 7 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_8                =   8,     /* Bus master 8 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_9                =   9,     /* Bus master 9 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_10               =  10,     /* Bus master 10 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_11               =  11,     /* Bus master 11 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_12               =  12,     /* Bus master 12 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_13               =  13,     /* Bus master 13 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_14               =  14,     /* Bus master 14 MPU. See MPU_0 description. */
    CY_SYSFAULT_MPU_15               =  15,     /* Bus master 15 MPU. See MPU_0 description. */
    CY_SYSFAULT_CM7_1_TCM_C_ECC      =  16,     /* Correctable ECC error in CM7_1 TCM memory. See CM7_0_TCM_C_ECC description. */
    CY_SYSFAULT_CM7_1_TCM_NC_ECC     =  17,     /* Non Correctable ECC error in CM7_1 TCM memory. See CM7_0_TCM_C_ECC description. */
    CY_SYSFAULT_CM7_0_CACHE_C_ECC    =  18,     /* Correctable ECC error in CM7_0 Cache memories */
    CY_SYSFAULT_CM7_0_CACHE_NC_ECC   =  19,     /* Non Correctable ECC error in CM7_0 Cache memories. See CM7_0_CACHE_C_ECC description */
    CY_SYSFAULT_CM7_1_CACHE_C_ECC    =  20,     /* Correctable ECC error in CM7_1 Cache memories. See CM7_0_CACHE_C_ECC description. */
    CY_SYSFAULT_CM7_1_CACHE_NC_ECC   =  21,     /* Non Correctable ECC error in CM7_1 Cache memories. See CM7_0_CACHE_C_ECC description. */
    CY_SYSFAULT_MS_PPU_4             =  25,     /* Peripheral interconnect, master interface 4 PPU. See MS_PPU_0 description. */
    CY_SYSFAULT_PERI_ECC             =  26,     /* Peripheral interconnect, protection structures SRAM, correctable ECC error: */
    CY_SYSFAULT_PERI_NC_ECC          =  27,     /* Peripheral interconnect, protection structures SRAM, non-correctable ECC error. */
    CY_SYSFAULT_MS_PPU_0             =  28,     /* Peripheral interconnect, master interface 0 PPU. */
    CY_SYSFAULT_MS_PPU_1             =  29,     /* Peripheral interconnect, master interface 1 PPU. See MS_PPU_0 description. */
    CY_SYSFAULT_MS_PPU_2             =  30,     /* Peripheral interconnect, master interface 2 PPU. See MS_PPU_0 description. */
    CY_SYSFAULT_MS_PPU_3             =  31,     /* Peripheral interconnect, master interface 3 PPU. See MS_PPU_0 description. */
    CY_SYSFAULT_GROUP_FAULT_0        =  32,     /* Peripheral group 0 fault detection. */
    CY_SYSFAULT_GROUP_FAULT_1        =  33,     /* Peripheral group 1 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_2        =  34,     /* Peripheral group 2 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_3        =  35,     /* Peripheral group 3 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_4        =  36,     /* Peripheral group 4 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_5        =  37,     /* Peripheral group 5 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_6        =  38,     /* Peripheral group 6 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_7        =  39,     /* Peripheral group 7 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_8        =  40,     /* Peripheral group 8 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_9        =  41,     /* Peripheral group 9 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_10       =  42,     /* Peripheral group 10 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_11       =  43,     /* Peripheral group 11 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_12       =  44,     /* Peripheral group 12 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_13       =  45,     /* Peripheral group 13 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_14       =  46,     /* Peripheral group 14 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_GROUP_FAULT_15       =  47,     /* Peripheral group 15 fault detection. See GROUP_FAULT_0 description. */
    CY_SYSFAULT_FLASHC_MAIN_BUS_ERROR  =  48,   /* Flash controller, main interface, bus error: */
    CY_SYSFAULT_FLASHC_MAIN_C_ECC    =  49,     /* Flash controller, main interface, correctable ECC error: */
    CY_SYSFAULT_FLASHC_MAIN_NC_ECC   =  50,     /* Flash controller, main interface, non-correctable ECC error.  See FLASHC_MAIN_C_ECC description. */
    CY_SYSFAULT_FLASHC_WORK_BUS_ERROR  =  51,   /* Flash controller, work interface, bus error. See FLASHC_MAIN_BUS_ERROR description. */
    CY_SYSFAULT_FLASHC_WORK_C_ECC    =  52,     /* Flash controller, work interface, correctable ECC error: */
    CY_SYSFAULT_FLASHC_WORK_NC_ECC   =  53,     /* Flash controller, work interface, non-correctable ECC error. See FLASHC_WORK_C_ECC description. */
    CY_SYSFAULT_FLASHC_CM0_CA_C_ECC  =  54,     /* Flash controller, CM0+ cache, correctable ECC error: */
    CY_SYSFAULT_FLASHC_CM0_CA_NC_ECC  =  55,    /* Flash controller, CM0+ cache, non-correctable ECC error.  See FLASHC_CM0_CA_C_ECC description. */
    CY_SYSFAULT_CM7_0_TCM_C_ECC      =  56,     /* Correctable ECC error in CM7_0 TCM memory */
    CY_SYSFAULT_CM7_0_TCM_NC_ECC     =  57,     /* Non Correctable ECC error in CM7_0 TCM memory. See CM7_0_TCM_C_ECC description. */
    CY_SYSFAULT_RAMC0_C_ECC          =  58,     /* System SRAM 0 correctable ECC error: */
    CY_SYSFAULT_RAMC0_NC_ECC         =  59,     /* System SRAM 0 non-correctable ECC error.  See RAMC0_C_ECC description. */
    CY_SYSFAULT_RAMC1_C_ECC          =  60,     /* System SRAM 1 correctable ECC error. See RAMC0_C_ECC description. */
    CY_SYSFAULT_RAMC1_NC_ECC         =  61,     /* System SRAM 1 non-correctable ECC error. See RAMC0_C_ECC description. */
    CY_SYSFAULT_RAMC2_C_ECC          =  62,     /* System SRAM 2 correctable ECC error. See RAMC0_C_ECC description. */
    CY_SYSFAULT_RAMC2_NC_ECC         =  63,     /* System SRAM 2 non-correctable ECC error. See RAMC0_C_ECC description. */
    CY_SYSFAULT_CRYPTO_C_ECC         =  64,     /* Cryptography SRAM correctable ECC error. */
    CY_SYSFAULT_CRYPTO_NC_ECC        =  65,     /* Cryptography SRAM non-correctable ECC error. See CRYPTO_C_ECC description. */
    CY_SYSFAULT_DW0_C_ECC            =  70,     /* DataWire 0 SRAM 1 correctable ECC error: */
    CY_SYSFAULT_DW0_NC_ECC           =  71,     /* DataWire 0 SRAM 1 non-correctable ECC error. See DW0_C_ECC description. */
    CY_SYSFAULT_DW1_C_ECC            =  72,     /* DataWire 1 SRAM 1 correctable ECC error. See DW0_C_ECC description. */
    CY_SYSFAULT_DW1_NC_ECC           =  73,     /* DataWire 1 SRAM 1 non-correctable ECC error. See DW0_C_ECC description. */
    CY_SYSFAULT_FM_SRAM_C_ECC        =  74,     /* eCT Flash SRAM (for embedded operations) correctable ECC error: */
    CY_SYSFAULT_FM_SRAM_NC_ECC       =  75,     /* eCT Flash SRAM non-correctable ECC error: See FM_SRAM_C_ECC description. */
    CY_SYSFAULT_CAN0_C_ECC           =  80,     /* CAN controller 0 MRAM correctable ECC error: */
    CY_SYSFAULT_CAN0_NC_ECC          =  81,     /* CAN controller 0 MRAM non-correctable ECC error: */
    CY_SYSFAULT_CAN1_C_ECC           =  82,     /* CAN controller 1 MRAM correctable ECC error. See CAN0_C_ECC description. */
    CY_SYSFAULT_CAN1_NC_ECC          =  83,     /* CAN controller 1 MRAM non-correctable ECC error. See CAN0_NC_ECC description. */
    CY_SYSFAULT_VIDEOSS_VRPU0        =  84,     /* Video Ram Protection Unit 0 fault detection. */
    CY_SYSFAULT_VIDEOSS_VRPU1        =  85,     /* Video Ram Protection Unit 1 fault detection.  See VIDEOSS_VRPU0 description. */
    CY_SYSFAULT_VIDEOSS_VRPU2        =  86,     /* Video Ram Protection Unit 2 fault detection.  See VIDEOSS_VRPU0 description. */
    CY_SYSFAULT_VIDEOSS_VRPU3        =  87,     /* Video Ram Protection Unit 3 fault detection.  See VIDEOSS_VRPU0 description. */
    CY_SYSFAULT_VIDEOSS_VRPU4        =  88,     /* Video Ram Protection Unit 4 fault detection.  See VIDEOSS_VRPU0 description. */
    CY_SYSFAULT_VIDEOSS_VRPU5        =  89,     /* Video Ram Protection Unit 5 fault detection.  See VIDEOSS_VRPU0 description. */
    CY_SYSFAULT_SRSS_CSV             =  90,     /* SRSS Clock SuperVisor (CSV) violation detected. Multiple CSV can detect a violation at the same time. */
    CY_SYSFAULT_SRSS_SSV             =  91,     /* SRSS Clock SuperVisor (CSV) violation detected. Multiple CSV can detect a violation at the same time. */
    CY_SYSFAULT_SRSS_MCWDT0          =  92,     /* SRSS Multi-Counter Watch Dog Timer (MCWDT) #0 violation detected. Multiple counters can detect a violation at the same time. */
    CY_SYSFAULT_SRSS_MCWDT1          =  93,     /* SRSS Multi-Counter Watch Dog Timer (MCWDT) #1 violation detected. See SRSS_MCWDT0 description. */
    CY_SYSFAULT_SRSS_MCWDT2          =  94,     /* SRSS Multi-Counter Watch Dog Timer (MCWDT) #2 violation detected. See SRSS_MCWDT0 description. */
    CY_SYSFAULT_SRSS_MCWDT3          =  95,     /* SRSS Multi-Counter Watch Dog Timer (MCWDT) #3 violation detected. See SRSS_MCWDT0 description. */
    CY_SYSFAULT_NO_FAULT             =  96
} cy_en_SysFault_source_t;

#endif /* _CYIP_FAULT_H_ */


/* [] END OF FILE */
