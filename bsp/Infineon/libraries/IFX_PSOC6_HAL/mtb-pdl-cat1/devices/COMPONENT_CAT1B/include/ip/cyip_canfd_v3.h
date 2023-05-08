/***************************************************************************//**
* \file cyip_canfd_v3.h
*
* \brief
* CANFD IP definitions
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

#ifndef _CYIP_CANFD_V3_H_
#define _CYIP_CANFD_V3_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                    CANFD
*******************************************************************************/

#define CANFD_CH_M_TTCAN_SECTION_SIZE           0x00000180UL
#define CANFD_CH_SECTION_SIZE                   0x00000200UL
#define CANFD_SECTION_SIZE                      0x00020000UL

/**
  * \brief TTCAN 3PIP, includes FD (CANFD_CH_M_TTCAN)
  */
typedef struct {
   __IM uint32_t CREL;                          /*!< 0x00000000 Core Release Register */
   __IM uint32_t ENDN;                          /*!< 0x00000004 Endian Register */
   __IM uint32_t RESERVED;
  __IOM uint32_t DBTP;                          /*!< 0x0000000C Data Bit Timing & Prescaler Register */
  __IOM uint32_t TEST;                          /*!< 0x00000010 Test Register */
  __IOM uint32_t RWD;                           /*!< 0x00000014 RAM Watchdog */
  __IOM uint32_t CCCR;                          /*!< 0x00000018 CC Control Register */
  __IOM uint32_t NBTP;                          /*!< 0x0000001C Nominal Bit Timing & Prescaler Register */
  __IOM uint32_t TSCC;                          /*!< 0x00000020 Timestamp Counter Configuration */
  __IOM uint32_t TSCV;                          /*!< 0x00000024 Timestamp Counter Value */
  __IOM uint32_t TOCC;                          /*!< 0x00000028 Timeout Counter Configuration */
  __IOM uint32_t TOCV;                          /*!< 0x0000002C Timeout Counter Value */
   __IM uint32_t RESERVED1[4];
   __IM uint32_t ECR;                           /*!< 0x00000040 Error Counter Register */
   __IM uint32_t PSR;                           /*!< 0x00000044 Protocol Status Register */
  __IOM uint32_t TDCR;                          /*!< 0x00000048 Transmitter Delay Compensation Register */
   __IM uint32_t RESERVED2;
  __IOM uint32_t IR;                            /*!< 0x00000050 Interrupt Register */
  __IOM uint32_t IE;                            /*!< 0x00000054 Interrupt Enable */
  __IOM uint32_t ILS;                           /*!< 0x00000058 Interrupt Line Select */
  __IOM uint32_t ILE;                           /*!< 0x0000005C Interrupt Line Enable */
   __IM uint32_t RESERVED3[8];
  __IOM uint32_t GFC;                           /*!< 0x00000080 Global Filter Configuration */
  __IOM uint32_t SIDFC;                         /*!< 0x00000084 Standard ID Filter Configuration */
  __IOM uint32_t XIDFC;                         /*!< 0x00000088 Extended ID Filter Configuration */
   __IM uint32_t RESERVED4;
  __IOM uint32_t XIDAM;                         /*!< 0x00000090 Extended ID AND Mask */
   __IM uint32_t HPMS;                          /*!< 0x00000094 High Priority Message Status */
  __IOM uint32_t NDAT1;                         /*!< 0x00000098 New Data 1 */
  __IOM uint32_t NDAT2;                         /*!< 0x0000009C New Data 2 */
  __IOM uint32_t RXF0C;                         /*!< 0x000000A0 Rx FIFO 0 Configuration */
   __IM uint32_t RXF0S;                         /*!< 0x000000A4 Rx FIFO 0 Status */
  __IOM uint32_t RXF0A;                         /*!< 0x000000A8 Rx FIFO 0 Acknowledge */
  __IOM uint32_t RXBC;                          /*!< 0x000000AC Rx Buffer Configuration */
  __IOM uint32_t RXF1C;                         /*!< 0x000000B0 Rx FIFO 1 Configuration */
   __IM uint32_t RXF1S;                         /*!< 0x000000B4 Rx FIFO 1 Status */
  __IOM uint32_t RXF1A;                         /*!< 0x000000B8 Rx FIFO 1 Acknowledge */
  __IOM uint32_t RXESC;                         /*!< 0x000000BC Rx Buffer / FIFO Element Size Configuration */
  __IOM uint32_t TXBC;                          /*!< 0x000000C0 Tx Buffer Configuration */
   __IM uint32_t TXFQS;                         /*!< 0x000000C4 Tx FIFO/Queue Status */
  __IOM uint32_t TXESC;                         /*!< 0x000000C8 Tx Buffer Element Size Configuration */
   __IM uint32_t TXBRP;                         /*!< 0x000000CC Tx Buffer Request Pending */
  __IOM uint32_t TXBAR;                         /*!< 0x000000D0 Tx Buffer Add Request */
  __IOM uint32_t TXBCR;                         /*!< 0x000000D4 Tx Buffer Cancellation Request */
   __IM uint32_t TXBTO;                         /*!< 0x000000D8 Tx Buffer Transmission Occurred */
   __IM uint32_t TXBCF;                         /*!< 0x000000DC Tx Buffer Cancellation Finished */
  __IOM uint32_t TXBTIE;                        /*!< 0x000000E0 Tx Buffer Transmission Interrupt Enable */
  __IOM uint32_t TXBCIE;                        /*!< 0x000000E4 Tx Buffer Cancellation Finished Interrupt Enable */
   __IM uint32_t RESERVED5[2];
  __IOM uint32_t TXEFC;                         /*!< 0x000000F0 Tx Event FIFO Configuration */
   __IM uint32_t TXEFS;                         /*!< 0x000000F4 Tx Event FIFO Status */
  __IOM uint32_t TXEFA;                         /*!< 0x000000F8 Tx Event FIFO Acknowledge */
   __IM uint32_t RESERVED6;
  __IOM uint32_t TTTMC;                         /*!< 0x00000100 TT Trigger Memory Configuration */
  __IOM uint32_t TTRMC;                         /*!< 0x00000104 TT Reference Message Configuration */
  __IOM uint32_t TTOCF;                         /*!< 0x00000108 TT Operation Configuration */
  __IOM uint32_t TTMLM;                         /*!< 0x0000010C TT Matrix Limits */
  __IOM uint32_t TURCF;                         /*!< 0x00000110 TUR Configuration */
  __IOM uint32_t TTOCN;                         /*!< 0x00000114 TT Operation Control */
  __IOM uint32_t TTGTP;                         /*!< 0x00000118 TT Global Time Preset */
  __IOM uint32_t TTTMK;                         /*!< 0x0000011C TT Time Mark */
  __IOM uint32_t TTIR;                          /*!< 0x00000120 TT Interrupt Register */
  __IOM uint32_t TTIE;                          /*!< 0x00000124 TT Interrupt Enable */
  __IOM uint32_t TTILS;                         /*!< 0x00000128 TT Interrupt Line Select */
   __IM uint32_t TTOST;                         /*!< 0x0000012C TT Operation Status */
   __IM uint32_t TURNA;                         /*!< 0x00000130 TUR Numerator Actual */
   __IM uint32_t TTLGT;                         /*!< 0x00000134 TT Local & Global Time */
   __IM uint32_t TTCTC;                         /*!< 0x00000138 TT Cycle Time & Count */
   __IM uint32_t TTCPT;                         /*!< 0x0000013C TT Capture Time */
   __IM uint32_t TTCSM;                         /*!< 0x00000140 TT Cycle Sync Mark */
   __IM uint32_t RESERVED7[15];
} CANFD_CH_M_TTCAN_Type;                        /*!< Size = 384 (0x180) */

/**
  * \brief FIFO wrapper around M_TTCAN 3PIP, to enable DMA (CANFD_CH)
  */
typedef struct {
        CANFD_CH_M_TTCAN_Type M_TTCAN;          /*!< 0x00000000 TTCAN 3PIP, includes FD */
  __IOM uint32_t RXFTOP_CTL;                    /*!< 0x00000180 Receive FIFO Top control */
   __IM uint32_t RESERVED[7];
   __IM uint32_t RXFTOP0_STAT;                  /*!< 0x000001A0 Receive FIFO 0 Top Status */
   __IM uint32_t RESERVED1;
   __IM uint32_t RXFTOP0_DATA;                  /*!< 0x000001A8 Receive FIFO 0 Top Data */
   __IM uint32_t RESERVED2;
   __IM uint32_t RXFTOP1_STAT;                  /*!< 0x000001B0 Receive FIFO 1 Top Status */
   __IM uint32_t RESERVED3;
   __IM uint32_t RXFTOP1_DATA;                  /*!< 0x000001B8 Receive FIFO 1 Top Data */
   __IM uint32_t RESERVED4[17];
} CANFD_CH_Type;                                /*!< Size = 512 (0x200) */

/**
  * \brief CAN Controller (CANFD)
  */
typedef struct {
        CANFD_CH_Type CH[8];                    /*!< 0x00000000 FIFO wrapper around M_TTCAN 3PIP, to enable DMA */
  __IOM uint32_t CTL;                           /*!< 0x00001000 Global CAN control register */
   __IM uint32_t STATUS;                        /*!< 0x00001004 Global CAN status register */
   __IM uint32_t RESERVED[2];
   __IM uint32_t INTR0_CAUSE;                   /*!< 0x00001010 Consolidated interrupt0 cause register */
   __IM uint32_t INTR1_CAUSE;                   /*!< 0x00001014 Consolidated interrupt1 cause register */
   __IM uint32_t RESERVED1[2];
  __IOM uint32_t TS_CTL;                        /*!< 0x00001020 Time Stamp control register */
  __IOM uint32_t TS_CNT;                        /*!< 0x00001024 Time Stamp counter value */
   __IM uint32_t RESERVED2[22];
  __IOM uint32_t ECC_CTL;                       /*!< 0x00001080 ECC control */
  __IOM uint32_t ECC_ERR_INJ;                   /*!< 0x00001084 ECC error injection */
} CANFD_Type;                                   /*!< Size = 4232 (0x1088) */


/* CANFD_CH_M_TTCAN.CREL */
#define CANFD_CH_M_TTCAN_CREL_DAY_Pos           0UL
#define CANFD_CH_M_TTCAN_CREL_DAY_Msk           0xFFUL
#define CANFD_CH_M_TTCAN_CREL_MON_Pos           8UL
#define CANFD_CH_M_TTCAN_CREL_MON_Msk           0xFF00UL
#define CANFD_CH_M_TTCAN_CREL_YEAR_Pos          16UL
#define CANFD_CH_M_TTCAN_CREL_YEAR_Msk          0xF0000UL
#define CANFD_CH_M_TTCAN_CREL_SUBSTEP_Pos       20UL
#define CANFD_CH_M_TTCAN_CREL_SUBSTEP_Msk       0xF00000UL
#define CANFD_CH_M_TTCAN_CREL_STEP_Pos          24UL
#define CANFD_CH_M_TTCAN_CREL_STEP_Msk          0xF000000UL
#define CANFD_CH_M_TTCAN_CREL_REL_Pos           28UL
#define CANFD_CH_M_TTCAN_CREL_REL_Msk           0xF0000000UL
/* CANFD_CH_M_TTCAN.ENDN */
#define CANFD_CH_M_TTCAN_ENDN_ETV_Pos           0UL
#define CANFD_CH_M_TTCAN_ENDN_ETV_Msk           0xFFFFFFFFUL
/* CANFD_CH_M_TTCAN.DBTP */
#define CANFD_CH_M_TTCAN_DBTP_DSJW_Pos          0UL
#define CANFD_CH_M_TTCAN_DBTP_DSJW_Msk          0xFUL
#define CANFD_CH_M_TTCAN_DBTP_DTSEG2_Pos        4UL
#define CANFD_CH_M_TTCAN_DBTP_DTSEG2_Msk        0xF0UL
#define CANFD_CH_M_TTCAN_DBTP_DTSEG1_Pos        8UL
#define CANFD_CH_M_TTCAN_DBTP_DTSEG1_Msk        0x1F00UL
#define CANFD_CH_M_TTCAN_DBTP_DBRP_Pos          16UL
#define CANFD_CH_M_TTCAN_DBTP_DBRP_Msk          0x1F0000UL
#define CANFD_CH_M_TTCAN_DBTP_TDC_Pos           23UL
#define CANFD_CH_M_TTCAN_DBTP_TDC_Msk           0x800000UL
/* CANFD_CH_M_TTCAN.TEST */
#define CANFD_CH_M_TTCAN_TEST_TAM_Pos           0UL
#define CANFD_CH_M_TTCAN_TEST_TAM_Msk           0x1UL
#define CANFD_CH_M_TTCAN_TEST_TAT_Pos           1UL
#define CANFD_CH_M_TTCAN_TEST_TAT_Msk           0x2UL
#define CANFD_CH_M_TTCAN_TEST_CAM_Pos           2UL
#define CANFD_CH_M_TTCAN_TEST_CAM_Msk           0x4UL
#define CANFD_CH_M_TTCAN_TEST_CAT_Pos           3UL
#define CANFD_CH_M_TTCAN_TEST_CAT_Msk           0x8UL
#define CANFD_CH_M_TTCAN_TEST_LBCK_Pos          4UL
#define CANFD_CH_M_TTCAN_TEST_LBCK_Msk          0x10UL
#define CANFD_CH_M_TTCAN_TEST_TX_Pos            5UL
#define CANFD_CH_M_TTCAN_TEST_TX_Msk            0x60UL
#define CANFD_CH_M_TTCAN_TEST_RX_Pos            7UL
#define CANFD_CH_M_TTCAN_TEST_RX_Msk            0x80UL
/* CANFD_CH_M_TTCAN.RWD */
#define CANFD_CH_M_TTCAN_RWD_WDC_Pos            0UL
#define CANFD_CH_M_TTCAN_RWD_WDC_Msk            0xFFUL
#define CANFD_CH_M_TTCAN_RWD_WDV_Pos            8UL
#define CANFD_CH_M_TTCAN_RWD_WDV_Msk            0xFF00UL
/* CANFD_CH_M_TTCAN.CCCR */
#define CANFD_CH_M_TTCAN_CCCR_INIT_Pos          0UL
#define CANFD_CH_M_TTCAN_CCCR_INIT_Msk          0x1UL
#define CANFD_CH_M_TTCAN_CCCR_CCE_Pos           1UL
#define CANFD_CH_M_TTCAN_CCCR_CCE_Msk           0x2UL
#define CANFD_CH_M_TTCAN_CCCR_ASM_Pos           2UL
#define CANFD_CH_M_TTCAN_CCCR_ASM_Msk           0x4UL
#define CANFD_CH_M_TTCAN_CCCR_CSA_Pos           3UL
#define CANFD_CH_M_TTCAN_CCCR_CSA_Msk           0x8UL
#define CANFD_CH_M_TTCAN_CCCR_CSR_Pos           4UL
#define CANFD_CH_M_TTCAN_CCCR_CSR_Msk           0x10UL
#define CANFD_CH_M_TTCAN_CCCR_MON__Pos          5UL
#define CANFD_CH_M_TTCAN_CCCR_MON__Msk          0x20UL
#define CANFD_CH_M_TTCAN_CCCR_DAR_Pos           6UL
#define CANFD_CH_M_TTCAN_CCCR_DAR_Msk           0x40UL
#define CANFD_CH_M_TTCAN_CCCR_TEST_Pos          7UL
#define CANFD_CH_M_TTCAN_CCCR_TEST_Msk          0x80UL
#define CANFD_CH_M_TTCAN_CCCR_FDOE_Pos          8UL
#define CANFD_CH_M_TTCAN_CCCR_FDOE_Msk          0x100UL
#define CANFD_CH_M_TTCAN_CCCR_BRSE_Pos          9UL
#define CANFD_CH_M_TTCAN_CCCR_BRSE_Msk          0x200UL
#define CANFD_CH_M_TTCAN_CCCR_PXHD_Pos          12UL
#define CANFD_CH_M_TTCAN_CCCR_PXHD_Msk          0x1000UL
#define CANFD_CH_M_TTCAN_CCCR_EFBI_Pos          13UL
#define CANFD_CH_M_TTCAN_CCCR_EFBI_Msk          0x2000UL
#define CANFD_CH_M_TTCAN_CCCR_TXP_Pos           14UL
#define CANFD_CH_M_TTCAN_CCCR_TXP_Msk           0x4000UL
#define CANFD_CH_M_TTCAN_CCCR_NISO_Pos          15UL
#define CANFD_CH_M_TTCAN_CCCR_NISO_Msk          0x8000UL
/* CANFD_CH_M_TTCAN.NBTP */
#define CANFD_CH_M_TTCAN_NBTP_NTSEG2_Pos        0UL
#define CANFD_CH_M_TTCAN_NBTP_NTSEG2_Msk        0x7FUL
#define CANFD_CH_M_TTCAN_NBTP_NTSEG1_Pos        8UL
#define CANFD_CH_M_TTCAN_NBTP_NTSEG1_Msk        0xFF00UL
#define CANFD_CH_M_TTCAN_NBTP_NBRP_Pos          16UL
#define CANFD_CH_M_TTCAN_NBTP_NBRP_Msk          0x1FF0000UL
#define CANFD_CH_M_TTCAN_NBTP_NSJW_Pos          25UL
#define CANFD_CH_M_TTCAN_NBTP_NSJW_Msk          0xFE000000UL
/* CANFD_CH_M_TTCAN.TSCC */
#define CANFD_CH_M_TTCAN_TSCC_TSS_Pos           0UL
#define CANFD_CH_M_TTCAN_TSCC_TSS_Msk           0x3UL
#define CANFD_CH_M_TTCAN_TSCC_TCP_Pos           16UL
#define CANFD_CH_M_TTCAN_TSCC_TCP_Msk           0xF0000UL
/* CANFD_CH_M_TTCAN.TSCV */
#define CANFD_CH_M_TTCAN_TSCV_TSC_Pos           0UL
#define CANFD_CH_M_TTCAN_TSCV_TSC_Msk           0xFFFFUL
/* CANFD_CH_M_TTCAN.TOCC */
#define CANFD_CH_M_TTCAN_TOCC_ETOC_Pos          0UL
#define CANFD_CH_M_TTCAN_TOCC_ETOC_Msk          0x1UL
#define CANFD_CH_M_TTCAN_TOCC_TOS_Pos           1UL
#define CANFD_CH_M_TTCAN_TOCC_TOS_Msk           0x6UL
#define CANFD_CH_M_TTCAN_TOCC_TOP_Pos           16UL
#define CANFD_CH_M_TTCAN_TOCC_TOP_Msk           0xFFFF0000UL
/* CANFD_CH_M_TTCAN.TOCV */
#define CANFD_CH_M_TTCAN_TOCV_TOC_Pos           0UL
#define CANFD_CH_M_TTCAN_TOCV_TOC_Msk           0xFFFFUL
/* CANFD_CH_M_TTCAN.ECR */
#define CANFD_CH_M_TTCAN_ECR_TEC_Pos            0UL
#define CANFD_CH_M_TTCAN_ECR_TEC_Msk            0xFFUL
#define CANFD_CH_M_TTCAN_ECR_REC_Pos            8UL
#define CANFD_CH_M_TTCAN_ECR_REC_Msk            0x7F00UL
#define CANFD_CH_M_TTCAN_ECR_RP_Pos             15UL
#define CANFD_CH_M_TTCAN_ECR_RP_Msk             0x8000UL
#define CANFD_CH_M_TTCAN_ECR_CEL_Pos            16UL
#define CANFD_CH_M_TTCAN_ECR_CEL_Msk            0xFF0000UL
/* CANFD_CH_M_TTCAN.PSR */
#define CANFD_CH_M_TTCAN_PSR_LEC_Pos            0UL
#define CANFD_CH_M_TTCAN_PSR_LEC_Msk            0x7UL
#define CANFD_CH_M_TTCAN_PSR_ACT_Pos            3UL
#define CANFD_CH_M_TTCAN_PSR_ACT_Msk            0x18UL
#define CANFD_CH_M_TTCAN_PSR_EP_Pos             5UL
#define CANFD_CH_M_TTCAN_PSR_EP_Msk             0x20UL
#define CANFD_CH_M_TTCAN_PSR_EW_Pos             6UL
#define CANFD_CH_M_TTCAN_PSR_EW_Msk             0x40UL
#define CANFD_CH_M_TTCAN_PSR_BO_Pos             7UL
#define CANFD_CH_M_TTCAN_PSR_BO_Msk             0x80UL
#define CANFD_CH_M_TTCAN_PSR_DLEC_Pos           8UL
#define CANFD_CH_M_TTCAN_PSR_DLEC_Msk           0x700UL
#define CANFD_CH_M_TTCAN_PSR_RESI_Pos           11UL
#define CANFD_CH_M_TTCAN_PSR_RESI_Msk           0x800UL
#define CANFD_CH_M_TTCAN_PSR_RBRS_Pos           12UL
#define CANFD_CH_M_TTCAN_PSR_RBRS_Msk           0x1000UL
#define CANFD_CH_M_TTCAN_PSR_RFDF_Pos           13UL
#define CANFD_CH_M_TTCAN_PSR_RFDF_Msk           0x2000UL
#define CANFD_CH_M_TTCAN_PSR_PXE_Pos            14UL
#define CANFD_CH_M_TTCAN_PSR_PXE_Msk            0x4000UL
#define CANFD_CH_M_TTCAN_PSR_TDCV_Pos           16UL
#define CANFD_CH_M_TTCAN_PSR_TDCV_Msk           0x7F0000UL
/* CANFD_CH_M_TTCAN.TDCR */
#define CANFD_CH_M_TTCAN_TDCR_TDCF_Pos          0UL
#define CANFD_CH_M_TTCAN_TDCR_TDCF_Msk          0x7FUL
#define CANFD_CH_M_TTCAN_TDCR_TDCO_Pos          8UL
#define CANFD_CH_M_TTCAN_TDCR_TDCO_Msk          0x7F00UL
/* CANFD_CH_M_TTCAN.IR */
#define CANFD_CH_M_TTCAN_IR_RF0N_Pos            0UL
#define CANFD_CH_M_TTCAN_IR_RF0N_Msk            0x1UL
#define CANFD_CH_M_TTCAN_IR_RF0W_Pos            1UL
#define CANFD_CH_M_TTCAN_IR_RF0W_Msk            0x2UL
#define CANFD_CH_M_TTCAN_IR_RF0F_Pos            2UL
#define CANFD_CH_M_TTCAN_IR_RF0F_Msk            0x4UL
#define CANFD_CH_M_TTCAN_IR_RF0L__Pos           3UL
#define CANFD_CH_M_TTCAN_IR_RF0L__Msk           0x8UL
#define CANFD_CH_M_TTCAN_IR_RF1N_Pos            4UL
#define CANFD_CH_M_TTCAN_IR_RF1N_Msk            0x10UL
#define CANFD_CH_M_TTCAN_IR_RF1W_Pos            5UL
#define CANFD_CH_M_TTCAN_IR_RF1W_Msk            0x20UL
#define CANFD_CH_M_TTCAN_IR_RF1F_Pos            6UL
#define CANFD_CH_M_TTCAN_IR_RF1F_Msk            0x40UL
#define CANFD_CH_M_TTCAN_IR_RF1L__Pos           7UL
#define CANFD_CH_M_TTCAN_IR_RF1L__Msk           0x80UL
#define CANFD_CH_M_TTCAN_IR_HPM_Pos             8UL
#define CANFD_CH_M_TTCAN_IR_HPM_Msk             0x100UL
#define CANFD_CH_M_TTCAN_IR_TC_Pos              9UL
#define CANFD_CH_M_TTCAN_IR_TC_Msk              0x200UL
#define CANFD_CH_M_TTCAN_IR_TCF_Pos             10UL
#define CANFD_CH_M_TTCAN_IR_TCF_Msk             0x400UL
#define CANFD_CH_M_TTCAN_IR_TFE_Pos             11UL
#define CANFD_CH_M_TTCAN_IR_TFE_Msk             0x800UL
#define CANFD_CH_M_TTCAN_IR_TEFN_Pos            12UL
#define CANFD_CH_M_TTCAN_IR_TEFN_Msk            0x1000UL
#define CANFD_CH_M_TTCAN_IR_TEFW_Pos            13UL
#define CANFD_CH_M_TTCAN_IR_TEFW_Msk            0x2000UL
#define CANFD_CH_M_TTCAN_IR_TEFF_Pos            14UL
#define CANFD_CH_M_TTCAN_IR_TEFF_Msk            0x4000UL
#define CANFD_CH_M_TTCAN_IR_TEFL__Pos           15UL
#define CANFD_CH_M_TTCAN_IR_TEFL__Msk           0x8000UL
#define CANFD_CH_M_TTCAN_IR_TSW_Pos             16UL
#define CANFD_CH_M_TTCAN_IR_TSW_Msk             0x10000UL
#define CANFD_CH_M_TTCAN_IR_MRAF_Pos            17UL
#define CANFD_CH_M_TTCAN_IR_MRAF_Msk            0x20000UL
#define CANFD_CH_M_TTCAN_IR_TOO_Pos             18UL
#define CANFD_CH_M_TTCAN_IR_TOO_Msk             0x40000UL
#define CANFD_CH_M_TTCAN_IR_DRX_Pos             19UL
#define CANFD_CH_M_TTCAN_IR_DRX_Msk             0x80000UL
#define CANFD_CH_M_TTCAN_IR_BEC_Pos             20UL
#define CANFD_CH_M_TTCAN_IR_BEC_Msk             0x100000UL
#define CANFD_CH_M_TTCAN_IR_BEU_Pos             21UL
#define CANFD_CH_M_TTCAN_IR_BEU_Msk             0x200000UL
#define CANFD_CH_M_TTCAN_IR_ELO_Pos             22UL
#define CANFD_CH_M_TTCAN_IR_ELO_Msk             0x400000UL
#define CANFD_CH_M_TTCAN_IR_EP__Pos             23UL
#define CANFD_CH_M_TTCAN_IR_EP__Msk             0x800000UL
#define CANFD_CH_M_TTCAN_IR_EW__Pos             24UL
#define CANFD_CH_M_TTCAN_IR_EW__Msk             0x1000000UL
#define CANFD_CH_M_TTCAN_IR_BO__Pos             25UL
#define CANFD_CH_M_TTCAN_IR_BO__Msk             0x2000000UL
#define CANFD_CH_M_TTCAN_IR_WDI_Pos             26UL
#define CANFD_CH_M_TTCAN_IR_WDI_Msk             0x4000000UL
#define CANFD_CH_M_TTCAN_IR_PEA_Pos             27UL
#define CANFD_CH_M_TTCAN_IR_PEA_Msk             0x8000000UL
#define CANFD_CH_M_TTCAN_IR_PED_Pos             28UL
#define CANFD_CH_M_TTCAN_IR_PED_Msk             0x10000000UL
#define CANFD_CH_M_TTCAN_IR_ARA_Pos             29UL
#define CANFD_CH_M_TTCAN_IR_ARA_Msk             0x20000000UL
/* CANFD_CH_M_TTCAN.IE */
#define CANFD_CH_M_TTCAN_IE_RF0NE_Pos           0UL
#define CANFD_CH_M_TTCAN_IE_RF0NE_Msk           0x1UL
#define CANFD_CH_M_TTCAN_IE_RF0WE_Pos           1UL
#define CANFD_CH_M_TTCAN_IE_RF0WE_Msk           0x2UL
#define CANFD_CH_M_TTCAN_IE_RF0FE_Pos           2UL
#define CANFD_CH_M_TTCAN_IE_RF0FE_Msk           0x4UL
#define CANFD_CH_M_TTCAN_IE_RF0LE_Pos           3UL
#define CANFD_CH_M_TTCAN_IE_RF0LE_Msk           0x8UL
#define CANFD_CH_M_TTCAN_IE_RF1NE_Pos           4UL
#define CANFD_CH_M_TTCAN_IE_RF1NE_Msk           0x10UL
#define CANFD_CH_M_TTCAN_IE_RF1WE_Pos           5UL
#define CANFD_CH_M_TTCAN_IE_RF1WE_Msk           0x20UL
#define CANFD_CH_M_TTCAN_IE_RF1FE_Pos           6UL
#define CANFD_CH_M_TTCAN_IE_RF1FE_Msk           0x40UL
#define CANFD_CH_M_TTCAN_IE_RF1LE_Pos           7UL
#define CANFD_CH_M_TTCAN_IE_RF1LE_Msk           0x80UL
#define CANFD_CH_M_TTCAN_IE_HPME_Pos            8UL
#define CANFD_CH_M_TTCAN_IE_HPME_Msk            0x100UL
#define CANFD_CH_M_TTCAN_IE_TCE_Pos             9UL
#define CANFD_CH_M_TTCAN_IE_TCE_Msk             0x200UL
#define CANFD_CH_M_TTCAN_IE_TCFE_Pos            10UL
#define CANFD_CH_M_TTCAN_IE_TCFE_Msk            0x400UL
#define CANFD_CH_M_TTCAN_IE_TFEE_Pos            11UL
#define CANFD_CH_M_TTCAN_IE_TFEE_Msk            0x800UL
#define CANFD_CH_M_TTCAN_IE_TEFNE_Pos           12UL
#define CANFD_CH_M_TTCAN_IE_TEFNE_Msk           0x1000UL
#define CANFD_CH_M_TTCAN_IE_TEFWE_Pos           13UL
#define CANFD_CH_M_TTCAN_IE_TEFWE_Msk           0x2000UL
#define CANFD_CH_M_TTCAN_IE_TEFFE_Pos           14UL
#define CANFD_CH_M_TTCAN_IE_TEFFE_Msk           0x4000UL
#define CANFD_CH_M_TTCAN_IE_TEFLE_Pos           15UL
#define CANFD_CH_M_TTCAN_IE_TEFLE_Msk           0x8000UL
#define CANFD_CH_M_TTCAN_IE_TSWE_Pos            16UL
#define CANFD_CH_M_TTCAN_IE_TSWE_Msk            0x10000UL
#define CANFD_CH_M_TTCAN_IE_MRAFE_Pos           17UL
#define CANFD_CH_M_TTCAN_IE_MRAFE_Msk           0x20000UL
#define CANFD_CH_M_TTCAN_IE_TOOE_Pos            18UL
#define CANFD_CH_M_TTCAN_IE_TOOE_Msk            0x40000UL
#define CANFD_CH_M_TTCAN_IE_DRXE_Pos            19UL
#define CANFD_CH_M_TTCAN_IE_DRXE_Msk            0x80000UL
#define CANFD_CH_M_TTCAN_IE_BECE_Pos            20UL
#define CANFD_CH_M_TTCAN_IE_BECE_Msk            0x100000UL
#define CANFD_CH_M_TTCAN_IE_BEUE_Pos            21UL
#define CANFD_CH_M_TTCAN_IE_BEUE_Msk            0x200000UL
#define CANFD_CH_M_TTCAN_IE_ELOE_Pos            22UL
#define CANFD_CH_M_TTCAN_IE_ELOE_Msk            0x400000UL
#define CANFD_CH_M_TTCAN_IE_EPE_Pos             23UL
#define CANFD_CH_M_TTCAN_IE_EPE_Msk             0x800000UL
#define CANFD_CH_M_TTCAN_IE_EWE_Pos             24UL
#define CANFD_CH_M_TTCAN_IE_EWE_Msk             0x1000000UL
#define CANFD_CH_M_TTCAN_IE_BOE_Pos             25UL
#define CANFD_CH_M_TTCAN_IE_BOE_Msk             0x2000000UL
#define CANFD_CH_M_TTCAN_IE_WDIE_Pos            26UL
#define CANFD_CH_M_TTCAN_IE_WDIE_Msk            0x4000000UL
#define CANFD_CH_M_TTCAN_IE_PEAE_Pos            27UL
#define CANFD_CH_M_TTCAN_IE_PEAE_Msk            0x8000000UL
#define CANFD_CH_M_TTCAN_IE_PEDE_Pos            28UL
#define CANFD_CH_M_TTCAN_IE_PEDE_Msk            0x10000000UL
#define CANFD_CH_M_TTCAN_IE_ARAE_Pos            29UL
#define CANFD_CH_M_TTCAN_IE_ARAE_Msk            0x20000000UL
/* CANFD_CH_M_TTCAN.ILS */
#define CANFD_CH_M_TTCAN_ILS_RF0NL_Pos          0UL
#define CANFD_CH_M_TTCAN_ILS_RF0NL_Msk          0x1UL
#define CANFD_CH_M_TTCAN_ILS_RF0WL_Pos          1UL
#define CANFD_CH_M_TTCAN_ILS_RF0WL_Msk          0x2UL
#define CANFD_CH_M_TTCAN_ILS_RF0FL_Pos          2UL
#define CANFD_CH_M_TTCAN_ILS_RF0FL_Msk          0x4UL
#define CANFD_CH_M_TTCAN_ILS_RF0LL_Pos          3UL
#define CANFD_CH_M_TTCAN_ILS_RF0LL_Msk          0x8UL
#define CANFD_CH_M_TTCAN_ILS_RF1NL_Pos          4UL
#define CANFD_CH_M_TTCAN_ILS_RF1NL_Msk          0x10UL
#define CANFD_CH_M_TTCAN_ILS_RF1WL_Pos          5UL
#define CANFD_CH_M_TTCAN_ILS_RF1WL_Msk          0x20UL
#define CANFD_CH_M_TTCAN_ILS_RF1FL_Pos          6UL
#define CANFD_CH_M_TTCAN_ILS_RF1FL_Msk          0x40UL
#define CANFD_CH_M_TTCAN_ILS_RF1LL_Pos          7UL
#define CANFD_CH_M_TTCAN_ILS_RF1LL_Msk          0x80UL
#define CANFD_CH_M_TTCAN_ILS_HPML_Pos           8UL
#define CANFD_CH_M_TTCAN_ILS_HPML_Msk           0x100UL
#define CANFD_CH_M_TTCAN_ILS_TCL_Pos            9UL
#define CANFD_CH_M_TTCAN_ILS_TCL_Msk            0x200UL
#define CANFD_CH_M_TTCAN_ILS_TCFL_Pos           10UL
#define CANFD_CH_M_TTCAN_ILS_TCFL_Msk           0x400UL
#define CANFD_CH_M_TTCAN_ILS_TFEL_Pos           11UL
#define CANFD_CH_M_TTCAN_ILS_TFEL_Msk           0x800UL
#define CANFD_CH_M_TTCAN_ILS_TEFNL_Pos          12UL
#define CANFD_CH_M_TTCAN_ILS_TEFNL_Msk          0x1000UL
#define CANFD_CH_M_TTCAN_ILS_TEFWL_Pos          13UL
#define CANFD_CH_M_TTCAN_ILS_TEFWL_Msk          0x2000UL
#define CANFD_CH_M_TTCAN_ILS_TEFFL_Pos          14UL
#define CANFD_CH_M_TTCAN_ILS_TEFFL_Msk          0x4000UL
#define CANFD_CH_M_TTCAN_ILS_TEFLL_Pos          15UL
#define CANFD_CH_M_TTCAN_ILS_TEFLL_Msk          0x8000UL
#define CANFD_CH_M_TTCAN_ILS_TSWL_Pos           16UL
#define CANFD_CH_M_TTCAN_ILS_TSWL_Msk           0x10000UL
#define CANFD_CH_M_TTCAN_ILS_MRAFL_Pos          17UL
#define CANFD_CH_M_TTCAN_ILS_MRAFL_Msk          0x20000UL
#define CANFD_CH_M_TTCAN_ILS_TOOL_Pos           18UL
#define CANFD_CH_M_TTCAN_ILS_TOOL_Msk           0x40000UL
#define CANFD_CH_M_TTCAN_ILS_DRXL_Pos           19UL
#define CANFD_CH_M_TTCAN_ILS_DRXL_Msk           0x80000UL
#define CANFD_CH_M_TTCAN_ILS_BECL_Pos           20UL
#define CANFD_CH_M_TTCAN_ILS_BECL_Msk           0x100000UL
#define CANFD_CH_M_TTCAN_ILS_BEUL_Pos           21UL
#define CANFD_CH_M_TTCAN_ILS_BEUL_Msk           0x200000UL
#define CANFD_CH_M_TTCAN_ILS_ELOL_Pos           22UL
#define CANFD_CH_M_TTCAN_ILS_ELOL_Msk           0x400000UL
#define CANFD_CH_M_TTCAN_ILS_EPL_Pos            23UL
#define CANFD_CH_M_TTCAN_ILS_EPL_Msk            0x800000UL
#define CANFD_CH_M_TTCAN_ILS_EWL_Pos            24UL
#define CANFD_CH_M_TTCAN_ILS_EWL_Msk            0x1000000UL
#define CANFD_CH_M_TTCAN_ILS_BOL_Pos            25UL
#define CANFD_CH_M_TTCAN_ILS_BOL_Msk            0x2000000UL
#define CANFD_CH_M_TTCAN_ILS_WDIL_Pos           26UL
#define CANFD_CH_M_TTCAN_ILS_WDIL_Msk           0x4000000UL
#define CANFD_CH_M_TTCAN_ILS_PEAL_Pos           27UL
#define CANFD_CH_M_TTCAN_ILS_PEAL_Msk           0x8000000UL
#define CANFD_CH_M_TTCAN_ILS_PEDL_Pos           28UL
#define CANFD_CH_M_TTCAN_ILS_PEDL_Msk           0x10000000UL
#define CANFD_CH_M_TTCAN_ILS_ARAL_Pos           29UL
#define CANFD_CH_M_TTCAN_ILS_ARAL_Msk           0x20000000UL
/* CANFD_CH_M_TTCAN.ILE */
#define CANFD_CH_M_TTCAN_ILE_EINT0_Pos          0UL
#define CANFD_CH_M_TTCAN_ILE_EINT0_Msk          0x1UL
#define CANFD_CH_M_TTCAN_ILE_EINT1_Pos          1UL
#define CANFD_CH_M_TTCAN_ILE_EINT1_Msk          0x2UL
/* CANFD_CH_M_TTCAN.GFC */
#define CANFD_CH_M_TTCAN_GFC_RRFE_Pos           0UL
#define CANFD_CH_M_TTCAN_GFC_RRFE_Msk           0x1UL
#define CANFD_CH_M_TTCAN_GFC_RRFS_Pos           1UL
#define CANFD_CH_M_TTCAN_GFC_RRFS_Msk           0x2UL
#define CANFD_CH_M_TTCAN_GFC_ANFE_Pos           2UL
#define CANFD_CH_M_TTCAN_GFC_ANFE_Msk           0xCUL
#define CANFD_CH_M_TTCAN_GFC_ANFS_Pos           4UL
#define CANFD_CH_M_TTCAN_GFC_ANFS_Msk           0x30UL
/* CANFD_CH_M_TTCAN.SIDFC */
#define CANFD_CH_M_TTCAN_SIDFC_FLSSA_Pos        2UL
#define CANFD_CH_M_TTCAN_SIDFC_FLSSA_Msk        0xFFFCUL
#define CANFD_CH_M_TTCAN_SIDFC_LSS_Pos          16UL
#define CANFD_CH_M_TTCAN_SIDFC_LSS_Msk          0xFF0000UL
/* CANFD_CH_M_TTCAN.XIDFC */
#define CANFD_CH_M_TTCAN_XIDFC_FLESA_Pos        2UL
#define CANFD_CH_M_TTCAN_XIDFC_FLESA_Msk        0xFFFCUL
#define CANFD_CH_M_TTCAN_XIDFC_LSE_Pos          16UL
#define CANFD_CH_M_TTCAN_XIDFC_LSE_Msk          0x7F0000UL
/* CANFD_CH_M_TTCAN.XIDAM */
#define CANFD_CH_M_TTCAN_XIDAM_EIDM_Pos         0UL
#define CANFD_CH_M_TTCAN_XIDAM_EIDM_Msk         0x1FFFFFFFUL
/* CANFD_CH_M_TTCAN.HPMS */
#define CANFD_CH_M_TTCAN_HPMS_BIDX_Pos          0UL
#define CANFD_CH_M_TTCAN_HPMS_BIDX_Msk          0x3FUL
#define CANFD_CH_M_TTCAN_HPMS_MSI_Pos           6UL
#define CANFD_CH_M_TTCAN_HPMS_MSI_Msk           0xC0UL
#define CANFD_CH_M_TTCAN_HPMS_FIDX_Pos          8UL
#define CANFD_CH_M_TTCAN_HPMS_FIDX_Msk          0x7F00UL
#define CANFD_CH_M_TTCAN_HPMS_FLST_Pos          15UL
#define CANFD_CH_M_TTCAN_HPMS_FLST_Msk          0x8000UL
/* CANFD_CH_M_TTCAN.NDAT1 */
#define CANFD_CH_M_TTCAN_NDAT1_ND_Pos           0UL
#define CANFD_CH_M_TTCAN_NDAT1_ND_Msk           0xFFFFFFFFUL
/* CANFD_CH_M_TTCAN.NDAT2 */
#define CANFD_CH_M_TTCAN_NDAT2_ND_Pos           0UL
#define CANFD_CH_M_TTCAN_NDAT2_ND_Msk           0xFFFFFFFFUL
/* CANFD_CH_M_TTCAN.RXF0C */
#define CANFD_CH_M_TTCAN_RXF0C_F0SA_Pos         2UL
#define CANFD_CH_M_TTCAN_RXF0C_F0SA_Msk         0xFFFCUL
#define CANFD_CH_M_TTCAN_RXF0C_F0S_Pos          16UL
#define CANFD_CH_M_TTCAN_RXF0C_F0S_Msk          0x7F0000UL
#define CANFD_CH_M_TTCAN_RXF0C_F0WM_Pos         24UL
#define CANFD_CH_M_TTCAN_RXF0C_F0WM_Msk         0x7F000000UL
#define CANFD_CH_M_TTCAN_RXF0C_F0OM_Pos         31UL
#define CANFD_CH_M_TTCAN_RXF0C_F0OM_Msk         0x80000000UL
/* CANFD_CH_M_TTCAN.RXF0S */
#define CANFD_CH_M_TTCAN_RXF0S_F0FL_Pos         0UL
#define CANFD_CH_M_TTCAN_RXF0S_F0FL_Msk         0x7FUL
#define CANFD_CH_M_TTCAN_RXF0S_F0GI_Pos         8UL
#define CANFD_CH_M_TTCAN_RXF0S_F0GI_Msk         0x3F00UL
#define CANFD_CH_M_TTCAN_RXF0S_F0PI_Pos         16UL
#define CANFD_CH_M_TTCAN_RXF0S_F0PI_Msk         0x3F0000UL
#define CANFD_CH_M_TTCAN_RXF0S_F0F_Pos          24UL
#define CANFD_CH_M_TTCAN_RXF0S_F0F_Msk          0x1000000UL
#define CANFD_CH_M_TTCAN_RXF0S_RF0L_Pos         25UL
#define CANFD_CH_M_TTCAN_RXF0S_RF0L_Msk         0x2000000UL
/* CANFD_CH_M_TTCAN.RXF0A */
#define CANFD_CH_M_TTCAN_RXF0A_F0AI_Pos         0UL
#define CANFD_CH_M_TTCAN_RXF0A_F0AI_Msk         0x3FUL
/* CANFD_CH_M_TTCAN.RXBC */
#define CANFD_CH_M_TTCAN_RXBC_RBSA_Pos          2UL
#define CANFD_CH_M_TTCAN_RXBC_RBSA_Msk          0xFFFCUL
/* CANFD_CH_M_TTCAN.RXF1C */
#define CANFD_CH_M_TTCAN_RXF1C_F1SA_Pos         2UL
#define CANFD_CH_M_TTCAN_RXF1C_F1SA_Msk         0xFFFCUL
#define CANFD_CH_M_TTCAN_RXF1C_F1S_Pos          16UL
#define CANFD_CH_M_TTCAN_RXF1C_F1S_Msk          0x7F0000UL
#define CANFD_CH_M_TTCAN_RXF1C_F1WM_Pos         24UL
#define CANFD_CH_M_TTCAN_RXF1C_F1WM_Msk         0x7F000000UL
#define CANFD_CH_M_TTCAN_RXF1C_F1OM_Pos         31UL
#define CANFD_CH_M_TTCAN_RXF1C_F1OM_Msk         0x80000000UL
/* CANFD_CH_M_TTCAN.RXF1S */
#define CANFD_CH_M_TTCAN_RXF1S_F1FL_Pos         0UL
#define CANFD_CH_M_TTCAN_RXF1S_F1FL_Msk         0x7FUL
#define CANFD_CH_M_TTCAN_RXF1S_F1GI_Pos         8UL
#define CANFD_CH_M_TTCAN_RXF1S_F1GI_Msk         0x3F00UL
#define CANFD_CH_M_TTCAN_RXF1S_F1PI_Pos         16UL
#define CANFD_CH_M_TTCAN_RXF1S_F1PI_Msk         0x3F0000UL
#define CANFD_CH_M_TTCAN_RXF1S_F1F_Pos          24UL
#define CANFD_CH_M_TTCAN_RXF1S_F1F_Msk          0x1000000UL
#define CANFD_CH_M_TTCAN_RXF1S_RF1L_Pos         25UL
#define CANFD_CH_M_TTCAN_RXF1S_RF1L_Msk         0x2000000UL
#define CANFD_CH_M_TTCAN_RXF1S_DMS_Pos          30UL
#define CANFD_CH_M_TTCAN_RXF1S_DMS_Msk          0xC0000000UL
/* CANFD_CH_M_TTCAN.RXF1A */
#define CANFD_CH_M_TTCAN_RXF1A_F1AI_Pos         0UL
#define CANFD_CH_M_TTCAN_RXF1A_F1AI_Msk         0x3FUL
/* CANFD_CH_M_TTCAN.RXESC */
#define CANFD_CH_M_TTCAN_RXESC_F0DS_Pos         0UL
#define CANFD_CH_M_TTCAN_RXESC_F0DS_Msk         0x7UL
#define CANFD_CH_M_TTCAN_RXESC_F1DS_Pos         4UL
#define CANFD_CH_M_TTCAN_RXESC_F1DS_Msk         0x70UL
#define CANFD_CH_M_TTCAN_RXESC_RBDS_Pos         8UL
#define CANFD_CH_M_TTCAN_RXESC_RBDS_Msk         0x700UL
/* CANFD_CH_M_TTCAN.TXBC */
#define CANFD_CH_M_TTCAN_TXBC_TBSA_Pos          2UL
#define CANFD_CH_M_TTCAN_TXBC_TBSA_Msk          0xFFFCUL
#define CANFD_CH_M_TTCAN_TXBC_NDTB_Pos          16UL
#define CANFD_CH_M_TTCAN_TXBC_NDTB_Msk          0x3F0000UL
#define CANFD_CH_M_TTCAN_TXBC_TFQS_Pos          24UL
#define CANFD_CH_M_TTCAN_TXBC_TFQS_Msk          0x3F000000UL
#define CANFD_CH_M_TTCAN_TXBC_TFQM_Pos          30UL
#define CANFD_CH_M_TTCAN_TXBC_TFQM_Msk          0x40000000UL
/* CANFD_CH_M_TTCAN.TXFQS */
#define CANFD_CH_M_TTCAN_TXFQS_TFFL_Pos         0UL
#define CANFD_CH_M_TTCAN_TXFQS_TFFL_Msk         0x3FUL
#define CANFD_CH_M_TTCAN_TXFQS_TFGI_Pos         8UL
#define CANFD_CH_M_TTCAN_TXFQS_TFGI_Msk         0x1F00UL
#define CANFD_CH_M_TTCAN_TXFQS_TFQPI_Pos        16UL
#define CANFD_CH_M_TTCAN_TXFQS_TFQPI_Msk        0x1F0000UL
#define CANFD_CH_M_TTCAN_TXFQS_TFQF_Pos         21UL
#define CANFD_CH_M_TTCAN_TXFQS_TFQF_Msk         0x200000UL
/* CANFD_CH_M_TTCAN.TXESC */
#define CANFD_CH_M_TTCAN_TXESC_TBDS_Pos         0UL
#define CANFD_CH_M_TTCAN_TXESC_TBDS_Msk         0x7UL
/* CANFD_CH_M_TTCAN.TXBRP */
#define CANFD_CH_M_TTCAN_TXBRP_TRP_Pos          0UL
#define CANFD_CH_M_TTCAN_TXBRP_TRP_Msk          0xFFFFFFFFUL
/* CANFD_CH_M_TTCAN.TXBAR */
#define CANFD_CH_M_TTCAN_TXBAR_AR_Pos           0UL
#define CANFD_CH_M_TTCAN_TXBAR_AR_Msk           0xFFFFFFFFUL
/* CANFD_CH_M_TTCAN.TXBCR */
#define CANFD_CH_M_TTCAN_TXBCR_CR_Pos           0UL
#define CANFD_CH_M_TTCAN_TXBCR_CR_Msk           0xFFFFFFFFUL
/* CANFD_CH_M_TTCAN.TXBTO */
#define CANFD_CH_M_TTCAN_TXBTO_TO_Pos           0UL
#define CANFD_CH_M_TTCAN_TXBTO_TO_Msk           0xFFFFFFFFUL
/* CANFD_CH_M_TTCAN.TXBCF */
#define CANFD_CH_M_TTCAN_TXBCF_CF_Pos           0UL
#define CANFD_CH_M_TTCAN_TXBCF_CF_Msk           0xFFFFFFFFUL
/* CANFD_CH_M_TTCAN.TXBTIE */
#define CANFD_CH_M_TTCAN_TXBTIE_TIE_Pos         0UL
#define CANFD_CH_M_TTCAN_TXBTIE_TIE_Msk         0xFFFFFFFFUL
/* CANFD_CH_M_TTCAN.TXBCIE */
#define CANFD_CH_M_TTCAN_TXBCIE_CFIE_Pos        0UL
#define CANFD_CH_M_TTCAN_TXBCIE_CFIE_Msk        0xFFFFFFFFUL
/* CANFD_CH_M_TTCAN.TXEFC */
#define CANFD_CH_M_TTCAN_TXEFC_EFSA_Pos         2UL
#define CANFD_CH_M_TTCAN_TXEFC_EFSA_Msk         0xFFFCUL
#define CANFD_CH_M_TTCAN_TXEFC_EFS_Pos          16UL
#define CANFD_CH_M_TTCAN_TXEFC_EFS_Msk          0x3F0000UL
#define CANFD_CH_M_TTCAN_TXEFC_EFWM_Pos         24UL
#define CANFD_CH_M_TTCAN_TXEFC_EFWM_Msk         0x3F000000UL
/* CANFD_CH_M_TTCAN.TXEFS */
#define CANFD_CH_M_TTCAN_TXEFS_EFFL_Pos         0UL
#define CANFD_CH_M_TTCAN_TXEFS_EFFL_Msk         0x3FUL
#define CANFD_CH_M_TTCAN_TXEFS_EFGI_Pos         8UL
#define CANFD_CH_M_TTCAN_TXEFS_EFGI_Msk         0x1F00UL
#define CANFD_CH_M_TTCAN_TXEFS_EFPI_Pos         16UL
#define CANFD_CH_M_TTCAN_TXEFS_EFPI_Msk         0x1F0000UL
#define CANFD_CH_M_TTCAN_TXEFS_EFF_Pos          24UL
#define CANFD_CH_M_TTCAN_TXEFS_EFF_Msk          0x1000000UL
#define CANFD_CH_M_TTCAN_TXEFS_TEFL_Pos         25UL
#define CANFD_CH_M_TTCAN_TXEFS_TEFL_Msk         0x2000000UL
/* CANFD_CH_M_TTCAN.TXEFA */
#define CANFD_CH_M_TTCAN_TXEFA_EFAI_Pos         0UL
#define CANFD_CH_M_TTCAN_TXEFA_EFAI_Msk         0x1FUL
/* CANFD_CH_M_TTCAN.TTTMC */
#define CANFD_CH_M_TTCAN_TTTMC_TMSA_Pos         2UL
#define CANFD_CH_M_TTCAN_TTTMC_TMSA_Msk         0xFFFCUL
#define CANFD_CH_M_TTCAN_TTTMC_TME_Pos          16UL
#define CANFD_CH_M_TTCAN_TTTMC_TME_Msk          0x7F0000UL
/* CANFD_CH_M_TTCAN.TTRMC */
#define CANFD_CH_M_TTCAN_TTRMC_RID_Pos          0UL
#define CANFD_CH_M_TTCAN_TTRMC_RID_Msk          0x1FFFFFFFUL
#define CANFD_CH_M_TTCAN_TTRMC_XTD_Pos          30UL
#define CANFD_CH_M_TTCAN_TTRMC_XTD_Msk          0x40000000UL
#define CANFD_CH_M_TTCAN_TTRMC_RMPS_Pos         31UL
#define CANFD_CH_M_TTCAN_TTRMC_RMPS_Msk         0x80000000UL
/* CANFD_CH_M_TTCAN.TTOCF */
#define CANFD_CH_M_TTCAN_TTOCF_OM_Pos           0UL
#define CANFD_CH_M_TTCAN_TTOCF_OM_Msk           0x3UL
#define CANFD_CH_M_TTCAN_TTOCF_GEN_Pos          3UL
#define CANFD_CH_M_TTCAN_TTOCF_GEN_Msk          0x8UL
#define CANFD_CH_M_TTCAN_TTOCF_TM_Pos           4UL
#define CANFD_CH_M_TTCAN_TTOCF_TM_Msk           0x10UL
#define CANFD_CH_M_TTCAN_TTOCF_LDSDL_Pos        5UL
#define CANFD_CH_M_TTCAN_TTOCF_LDSDL_Msk        0xE0UL
#define CANFD_CH_M_TTCAN_TTOCF_IRTO_Pos         8UL
#define CANFD_CH_M_TTCAN_TTOCF_IRTO_Msk         0x7F00UL
#define CANFD_CH_M_TTCAN_TTOCF_EECS_Pos         15UL
#define CANFD_CH_M_TTCAN_TTOCF_EECS_Msk         0x8000UL
#define CANFD_CH_M_TTCAN_TTOCF_AWL_Pos          16UL
#define CANFD_CH_M_TTCAN_TTOCF_AWL_Msk          0xFF0000UL
#define CANFD_CH_M_TTCAN_TTOCF_EGTF_Pos         24UL
#define CANFD_CH_M_TTCAN_TTOCF_EGTF_Msk         0x1000000UL
#define CANFD_CH_M_TTCAN_TTOCF_ECC_Pos          25UL
#define CANFD_CH_M_TTCAN_TTOCF_ECC_Msk          0x2000000UL
#define CANFD_CH_M_TTCAN_TTOCF_EVTP_Pos         26UL
#define CANFD_CH_M_TTCAN_TTOCF_EVTP_Msk         0x4000000UL
/* CANFD_CH_M_TTCAN.TTMLM */
#define CANFD_CH_M_TTCAN_TTMLM_CCM_Pos          0UL
#define CANFD_CH_M_TTCAN_TTMLM_CCM_Msk          0x3FUL
#define CANFD_CH_M_TTCAN_TTMLM_CSS_Pos          6UL
#define CANFD_CH_M_TTCAN_TTMLM_CSS_Msk          0xC0UL
#define CANFD_CH_M_TTCAN_TTMLM_TXEW_Pos         8UL
#define CANFD_CH_M_TTCAN_TTMLM_TXEW_Msk         0xF00UL
#define CANFD_CH_M_TTCAN_TTMLM_ENTT_Pos         16UL
#define CANFD_CH_M_TTCAN_TTMLM_ENTT_Msk         0xFFF0000UL
/* CANFD_CH_M_TTCAN.TURCF */
#define CANFD_CH_M_TTCAN_TURCF_NCL_Pos          0UL
#define CANFD_CH_M_TTCAN_TURCF_NCL_Msk          0xFFFFUL
#define CANFD_CH_M_TTCAN_TURCF_DC_Pos           16UL
#define CANFD_CH_M_TTCAN_TURCF_DC_Msk           0x3FFF0000UL
#define CANFD_CH_M_TTCAN_TURCF_ELT_Pos          31UL
#define CANFD_CH_M_TTCAN_TURCF_ELT_Msk          0x80000000UL
/* CANFD_CH_M_TTCAN.TTOCN */
#define CANFD_CH_M_TTCAN_TTOCN_SGT_Pos          0UL
#define CANFD_CH_M_TTCAN_TTOCN_SGT_Msk          0x1UL
#define CANFD_CH_M_TTCAN_TTOCN_ECS_Pos          1UL
#define CANFD_CH_M_TTCAN_TTOCN_ECS_Msk          0x2UL
#define CANFD_CH_M_TTCAN_TTOCN_SWP_Pos          2UL
#define CANFD_CH_M_TTCAN_TTOCN_SWP_Msk          0x4UL
#define CANFD_CH_M_TTCAN_TTOCN_SWS_Pos          3UL
#define CANFD_CH_M_TTCAN_TTOCN_SWS_Msk          0x18UL
#define CANFD_CH_M_TTCAN_TTOCN_RTIE_Pos         5UL
#define CANFD_CH_M_TTCAN_TTOCN_RTIE_Msk         0x20UL
#define CANFD_CH_M_TTCAN_TTOCN_TMC_Pos          6UL
#define CANFD_CH_M_TTCAN_TTOCN_TMC_Msk          0xC0UL
#define CANFD_CH_M_TTCAN_TTOCN_TTIE_Pos         8UL
#define CANFD_CH_M_TTCAN_TTOCN_TTIE_Msk         0x100UL
#define CANFD_CH_M_TTCAN_TTOCN_GCS_Pos          9UL
#define CANFD_CH_M_TTCAN_TTOCN_GCS_Msk          0x200UL
#define CANFD_CH_M_TTCAN_TTOCN_FGP_Pos          10UL
#define CANFD_CH_M_TTCAN_TTOCN_FGP_Msk          0x400UL
#define CANFD_CH_M_TTCAN_TTOCN_TMG_Pos          11UL
#define CANFD_CH_M_TTCAN_TTOCN_TMG_Msk          0x800UL
#define CANFD_CH_M_TTCAN_TTOCN_NIG_Pos          12UL
#define CANFD_CH_M_TTCAN_TTOCN_NIG_Msk          0x1000UL
#define CANFD_CH_M_TTCAN_TTOCN_ESCN_Pos         13UL
#define CANFD_CH_M_TTCAN_TTOCN_ESCN_Msk         0x2000UL
#define CANFD_CH_M_TTCAN_TTOCN_LCKC_Pos         15UL
#define CANFD_CH_M_TTCAN_TTOCN_LCKC_Msk         0x8000UL
/* CANFD_CH_M_TTCAN.TTGTP */
#define CANFD_CH_M_TTCAN_TTGTP_TP_Pos           0UL
#define CANFD_CH_M_TTCAN_TTGTP_TP_Msk           0xFFFFUL
#define CANFD_CH_M_TTCAN_TTGTP_CTP_Pos          16UL
#define CANFD_CH_M_TTCAN_TTGTP_CTP_Msk          0xFFFF0000UL
/* CANFD_CH_M_TTCAN.TTTMK */
#define CANFD_CH_M_TTCAN_TTTMK_TM__Pos          0UL
#define CANFD_CH_M_TTCAN_TTTMK_TM__Msk          0xFFFFUL
#define CANFD_CH_M_TTCAN_TTTMK_TICC_Pos         16UL
#define CANFD_CH_M_TTCAN_TTTMK_TICC_Msk         0x7F0000UL
#define CANFD_CH_M_TTCAN_TTTMK_LCKM_Pos         31UL
#define CANFD_CH_M_TTCAN_TTTMK_LCKM_Msk         0x80000000UL
/* CANFD_CH_M_TTCAN.TTIR */
#define CANFD_CH_M_TTCAN_TTIR_SBC_Pos           0UL
#define CANFD_CH_M_TTCAN_TTIR_SBC_Msk           0x1UL
#define CANFD_CH_M_TTCAN_TTIR_SMC_Pos           1UL
#define CANFD_CH_M_TTCAN_TTIR_SMC_Msk           0x2UL
#define CANFD_CH_M_TTCAN_TTIR_CSM__Pos          2UL
#define CANFD_CH_M_TTCAN_TTIR_CSM__Msk          0x4UL
#define CANFD_CH_M_TTCAN_TTIR_SOG_Pos           3UL
#define CANFD_CH_M_TTCAN_TTIR_SOG_Msk           0x8UL
#define CANFD_CH_M_TTCAN_TTIR_RTMI_Pos          4UL
#define CANFD_CH_M_TTCAN_TTIR_RTMI_Msk          0x10UL
#define CANFD_CH_M_TTCAN_TTIR_TTMI_Pos          5UL
#define CANFD_CH_M_TTCAN_TTIR_TTMI_Msk          0x20UL
#define CANFD_CH_M_TTCAN_TTIR_SWE_Pos           6UL
#define CANFD_CH_M_TTCAN_TTIR_SWE_Msk           0x40UL
#define CANFD_CH_M_TTCAN_TTIR_GTW_Pos           7UL
#define CANFD_CH_M_TTCAN_TTIR_GTW_Msk           0x80UL
#define CANFD_CH_M_TTCAN_TTIR_GTD_Pos           8UL
#define CANFD_CH_M_TTCAN_TTIR_GTD_Msk           0x100UL
#define CANFD_CH_M_TTCAN_TTIR_GTE_Pos           9UL
#define CANFD_CH_M_TTCAN_TTIR_GTE_Msk           0x200UL
#define CANFD_CH_M_TTCAN_TTIR_TXU_Pos           10UL
#define CANFD_CH_M_TTCAN_TTIR_TXU_Msk           0x400UL
#define CANFD_CH_M_TTCAN_TTIR_TXO_Pos           11UL
#define CANFD_CH_M_TTCAN_TTIR_TXO_Msk           0x800UL
#define CANFD_CH_M_TTCAN_TTIR_SE1_Pos           12UL
#define CANFD_CH_M_TTCAN_TTIR_SE1_Msk           0x1000UL
#define CANFD_CH_M_TTCAN_TTIR_SE2_Pos           13UL
#define CANFD_CH_M_TTCAN_TTIR_SE2_Msk           0x2000UL
#define CANFD_CH_M_TTCAN_TTIR_ELC_Pos           14UL
#define CANFD_CH_M_TTCAN_TTIR_ELC_Msk           0x4000UL
#define CANFD_CH_M_TTCAN_TTIR_IWT_Pos           15UL
#define CANFD_CH_M_TTCAN_TTIR_IWT_Msk           0x8000UL
#define CANFD_CH_M_TTCAN_TTIR_WT_Pos            16UL
#define CANFD_CH_M_TTCAN_TTIR_WT_Msk            0x10000UL
#define CANFD_CH_M_TTCAN_TTIR_AW_Pos            17UL
#define CANFD_CH_M_TTCAN_TTIR_AW_Msk            0x20000UL
#define CANFD_CH_M_TTCAN_TTIR_CER_Pos           18UL
#define CANFD_CH_M_TTCAN_TTIR_CER_Msk           0x40000UL
/* CANFD_CH_M_TTCAN.TTIE */
#define CANFD_CH_M_TTCAN_TTIE_SBCE_Pos          0UL
#define CANFD_CH_M_TTCAN_TTIE_SBCE_Msk          0x1UL
#define CANFD_CH_M_TTCAN_TTIE_SMCE_Pos          1UL
#define CANFD_CH_M_TTCAN_TTIE_SMCE_Msk          0x2UL
#define CANFD_CH_M_TTCAN_TTIE_CSME_Pos          2UL
#define CANFD_CH_M_TTCAN_TTIE_CSME_Msk          0x4UL
#define CANFD_CH_M_TTCAN_TTIE_SOGE_Pos          3UL
#define CANFD_CH_M_TTCAN_TTIE_SOGE_Msk          0x8UL
#define CANFD_CH_M_TTCAN_TTIE_RTMIE_Pos         4UL
#define CANFD_CH_M_TTCAN_TTIE_RTMIE_Msk         0x10UL
#define CANFD_CH_M_TTCAN_TTIE_TTMIE_Pos         5UL
#define CANFD_CH_M_TTCAN_TTIE_TTMIE_Msk         0x20UL
#define CANFD_CH_M_TTCAN_TTIE_SWEE_Pos          6UL
#define CANFD_CH_M_TTCAN_TTIE_SWEE_Msk          0x40UL
#define CANFD_CH_M_TTCAN_TTIE_GTWE_Pos          7UL
#define CANFD_CH_M_TTCAN_TTIE_GTWE_Msk          0x80UL
#define CANFD_CH_M_TTCAN_TTIE_GTDE_Pos          8UL
#define CANFD_CH_M_TTCAN_TTIE_GTDE_Msk          0x100UL
#define CANFD_CH_M_TTCAN_TTIE_GTEE_Pos          9UL
#define CANFD_CH_M_TTCAN_TTIE_GTEE_Msk          0x200UL
#define CANFD_CH_M_TTCAN_TTIE_TXUE_Pos          10UL
#define CANFD_CH_M_TTCAN_TTIE_TXUE_Msk          0x400UL
#define CANFD_CH_M_TTCAN_TTIE_TXOE_Pos          11UL
#define CANFD_CH_M_TTCAN_TTIE_TXOE_Msk          0x800UL
#define CANFD_CH_M_TTCAN_TTIE_SE1E_Pos          12UL
#define CANFD_CH_M_TTCAN_TTIE_SE1E_Msk          0x1000UL
#define CANFD_CH_M_TTCAN_TTIE_SE2E_Pos          13UL
#define CANFD_CH_M_TTCAN_TTIE_SE2E_Msk          0x2000UL
#define CANFD_CH_M_TTCAN_TTIE_ELCE_Pos          14UL
#define CANFD_CH_M_TTCAN_TTIE_ELCE_Msk          0x4000UL
#define CANFD_CH_M_TTCAN_TTIE_IWTE_Pos          15UL
#define CANFD_CH_M_TTCAN_TTIE_IWTE_Msk          0x8000UL
#define CANFD_CH_M_TTCAN_TTIE_WTE_Pos           16UL
#define CANFD_CH_M_TTCAN_TTIE_WTE_Msk           0x10000UL
#define CANFD_CH_M_TTCAN_TTIE_AWE__Pos          17UL
#define CANFD_CH_M_TTCAN_TTIE_AWE__Msk          0x20000UL
#define CANFD_CH_M_TTCAN_TTIE_CERE_Pos          18UL
#define CANFD_CH_M_TTCAN_TTIE_CERE_Msk          0x40000UL
/* CANFD_CH_M_TTCAN.TTILS */
#define CANFD_CH_M_TTCAN_TTILS_SBCL_Pos         0UL
#define CANFD_CH_M_TTCAN_TTILS_SBCL_Msk         0x1UL
#define CANFD_CH_M_TTCAN_TTILS_SMCL_Pos         1UL
#define CANFD_CH_M_TTCAN_TTILS_SMCL_Msk         0x2UL
#define CANFD_CH_M_TTCAN_TTILS_CSML_Pos         2UL
#define CANFD_CH_M_TTCAN_TTILS_CSML_Msk         0x4UL
#define CANFD_CH_M_TTCAN_TTILS_SOGL_Pos         3UL
#define CANFD_CH_M_TTCAN_TTILS_SOGL_Msk         0x8UL
#define CANFD_CH_M_TTCAN_TTILS_RTMIL_Pos        4UL
#define CANFD_CH_M_TTCAN_TTILS_RTMIL_Msk        0x10UL
#define CANFD_CH_M_TTCAN_TTILS_TTMIL_Pos        5UL
#define CANFD_CH_M_TTCAN_TTILS_TTMIL_Msk        0x20UL
#define CANFD_CH_M_TTCAN_TTILS_SWEL_Pos         6UL
#define CANFD_CH_M_TTCAN_TTILS_SWEL_Msk         0x40UL
#define CANFD_CH_M_TTCAN_TTILS_GTWL_Pos         7UL
#define CANFD_CH_M_TTCAN_TTILS_GTWL_Msk         0x80UL
#define CANFD_CH_M_TTCAN_TTILS_GTDL_Pos         8UL
#define CANFD_CH_M_TTCAN_TTILS_GTDL_Msk         0x100UL
#define CANFD_CH_M_TTCAN_TTILS_GTEL_Pos         9UL
#define CANFD_CH_M_TTCAN_TTILS_GTEL_Msk         0x200UL
#define CANFD_CH_M_TTCAN_TTILS_TXUL_Pos         10UL
#define CANFD_CH_M_TTCAN_TTILS_TXUL_Msk         0x400UL
#define CANFD_CH_M_TTCAN_TTILS_TXOL_Pos         11UL
#define CANFD_CH_M_TTCAN_TTILS_TXOL_Msk         0x800UL
#define CANFD_CH_M_TTCAN_TTILS_SE1L_Pos         12UL
#define CANFD_CH_M_TTCAN_TTILS_SE1L_Msk         0x1000UL
#define CANFD_CH_M_TTCAN_TTILS_SE2L_Pos         13UL
#define CANFD_CH_M_TTCAN_TTILS_SE2L_Msk         0x2000UL
#define CANFD_CH_M_TTCAN_TTILS_ELCL_Pos         14UL
#define CANFD_CH_M_TTCAN_TTILS_ELCL_Msk         0x4000UL
#define CANFD_CH_M_TTCAN_TTILS_IWTL_Pos         15UL
#define CANFD_CH_M_TTCAN_TTILS_IWTL_Msk         0x8000UL
#define CANFD_CH_M_TTCAN_TTILS_WTL_Pos          16UL
#define CANFD_CH_M_TTCAN_TTILS_WTL_Msk          0x10000UL
#define CANFD_CH_M_TTCAN_TTILS_AWL__Pos         17UL
#define CANFD_CH_M_TTCAN_TTILS_AWL__Msk         0x20000UL
#define CANFD_CH_M_TTCAN_TTILS_CERL_Pos         18UL
#define CANFD_CH_M_TTCAN_TTILS_CERL_Msk         0x40000UL
/* CANFD_CH_M_TTCAN.TTOST */
#define CANFD_CH_M_TTCAN_TTOST_EL_Pos           0UL
#define CANFD_CH_M_TTCAN_TTOST_EL_Msk           0x3UL
#define CANFD_CH_M_TTCAN_TTOST_MS_Pos           2UL
#define CANFD_CH_M_TTCAN_TTOST_MS_Msk           0xCUL
#define CANFD_CH_M_TTCAN_TTOST_SYS_Pos          4UL
#define CANFD_CH_M_TTCAN_TTOST_SYS_Msk          0x30UL
#define CANFD_CH_M_TTCAN_TTOST_QGTP_Pos         6UL
#define CANFD_CH_M_TTCAN_TTOST_QGTP_Msk         0x40UL
#define CANFD_CH_M_TTCAN_TTOST_QCS_Pos          7UL
#define CANFD_CH_M_TTCAN_TTOST_QCS_Msk          0x80UL
#define CANFD_CH_M_TTCAN_TTOST_RTO_Pos          8UL
#define CANFD_CH_M_TTCAN_TTOST_RTO_Msk          0xFF00UL
#define CANFD_CH_M_TTCAN_TTOST_WGTD_Pos         22UL
#define CANFD_CH_M_TTCAN_TTOST_WGTD_Msk         0x400000UL
#define CANFD_CH_M_TTCAN_TTOST_GFI_Pos          23UL
#define CANFD_CH_M_TTCAN_TTOST_GFI_Msk          0x800000UL
#define CANFD_CH_M_TTCAN_TTOST_TMP_Pos          24UL
#define CANFD_CH_M_TTCAN_TTOST_TMP_Msk          0x7000000UL
#define CANFD_CH_M_TTCAN_TTOST_GSI_Pos          27UL
#define CANFD_CH_M_TTCAN_TTOST_GSI_Msk          0x8000000UL
#define CANFD_CH_M_TTCAN_TTOST_WFE_Pos          28UL
#define CANFD_CH_M_TTCAN_TTOST_WFE_Msk          0x10000000UL
#define CANFD_CH_M_TTCAN_TTOST_AWE_Pos          29UL
#define CANFD_CH_M_TTCAN_TTOST_AWE_Msk          0x20000000UL
#define CANFD_CH_M_TTCAN_TTOST_WECS_Pos         30UL
#define CANFD_CH_M_TTCAN_TTOST_WECS_Msk         0x40000000UL
#define CANFD_CH_M_TTCAN_TTOST_SPL_Pos          31UL
#define CANFD_CH_M_TTCAN_TTOST_SPL_Msk          0x80000000UL
/* CANFD_CH_M_TTCAN.TURNA */
#define CANFD_CH_M_TTCAN_TURNA_NAV_Pos          0UL
#define CANFD_CH_M_TTCAN_TURNA_NAV_Msk          0x3FFFFUL
/* CANFD_CH_M_TTCAN.TTLGT */
#define CANFD_CH_M_TTCAN_TTLGT_LT_Pos           0UL
#define CANFD_CH_M_TTCAN_TTLGT_LT_Msk           0xFFFFUL
#define CANFD_CH_M_TTCAN_TTLGT_GT_Pos           16UL
#define CANFD_CH_M_TTCAN_TTLGT_GT_Msk           0xFFFF0000UL
/* CANFD_CH_M_TTCAN.TTCTC */
#define CANFD_CH_M_TTCAN_TTCTC_CT_Pos           0UL
#define CANFD_CH_M_TTCAN_TTCTC_CT_Msk           0xFFFFUL
#define CANFD_CH_M_TTCAN_TTCTC_CC_Pos           16UL
#define CANFD_CH_M_TTCAN_TTCTC_CC_Msk           0x3F0000UL
/* CANFD_CH_M_TTCAN.TTCPT */
#define CANFD_CH_M_TTCAN_TTCPT_CCV_Pos          0UL
#define CANFD_CH_M_TTCAN_TTCPT_CCV_Msk          0x3FUL
#define CANFD_CH_M_TTCAN_TTCPT_SWV_Pos          16UL
#define CANFD_CH_M_TTCAN_TTCPT_SWV_Msk          0xFFFF0000UL
/* CANFD_CH_M_TTCAN.TTCSM */
#define CANFD_CH_M_TTCAN_TTCSM_CSM_Pos          0UL
#define CANFD_CH_M_TTCAN_TTCSM_CSM_Msk          0xFFFFUL


/* CANFD_CH.RXFTOP_CTL */
#define CANFD_CH_RXFTOP_CTL_F0TPE_Pos           0UL
#define CANFD_CH_RXFTOP_CTL_F0TPE_Msk           0x1UL
#define CANFD_CH_RXFTOP_CTL_F1TPE_Pos           1UL
#define CANFD_CH_RXFTOP_CTL_F1TPE_Msk           0x2UL
/* CANFD_CH.RXFTOP0_STAT */
#define CANFD_CH_RXFTOP0_STAT_F0TA_Pos          0UL
#define CANFD_CH_RXFTOP0_STAT_F0TA_Msk          0xFFFFUL
/* CANFD_CH.RXFTOP0_DATA */
#define CANFD_CH_RXFTOP0_DATA_F0TD_Pos          0UL
#define CANFD_CH_RXFTOP0_DATA_F0TD_Msk          0xFFFFFFFFUL
/* CANFD_CH.RXFTOP1_STAT */
#define CANFD_CH_RXFTOP1_STAT_F1TA_Pos          0UL
#define CANFD_CH_RXFTOP1_STAT_F1TA_Msk          0xFFFFUL
/* CANFD_CH.RXFTOP1_DATA */
#define CANFD_CH_RXFTOP1_DATA_F1TD_Pos          0UL
#define CANFD_CH_RXFTOP1_DATA_F1TD_Msk          0xFFFFFFFFUL


/* CANFD.CTL */
#define CANFD_CTL_STOP_REQ_Pos                  0UL
#define CANFD_CTL_STOP_REQ_Msk                  0xFFUL
#define CANFD_CTL_MRAM_OFF_Pos                  31UL
#define CANFD_CTL_MRAM_OFF_Msk                  0x80000000UL
/* CANFD.STATUS */
#define CANFD_STATUS_STOP_ACK_Pos               0UL
#define CANFD_STATUS_STOP_ACK_Msk               0xFFUL
/* CANFD.INTR0_CAUSE */
#define CANFD_INTR0_CAUSE_INT0_Pos              0UL
#define CANFD_INTR0_CAUSE_INT0_Msk              0xFFUL
/* CANFD.INTR1_CAUSE */
#define CANFD_INTR1_CAUSE_INT1_Pos              0UL
#define CANFD_INTR1_CAUSE_INT1_Msk              0xFFUL
/* CANFD.TS_CTL */
#define CANFD_TS_CTL_PRESCALE_Pos               0UL
#define CANFD_TS_CTL_PRESCALE_Msk               0xFFFFUL
#define CANFD_TS_CTL_ENABLED_Pos                31UL
#define CANFD_TS_CTL_ENABLED_Msk                0x80000000UL
/* CANFD.TS_CNT */
#define CANFD_TS_CNT_VALUE_Pos                  0UL
#define CANFD_TS_CNT_VALUE_Msk                  0xFFFFUL
/* CANFD.ECC_CTL */
#define CANFD_ECC_CTL_ECC_EN_Pos                16UL
#define CANFD_ECC_CTL_ECC_EN_Msk                0x10000UL
/* CANFD.ECC_ERR_INJ */
#define CANFD_ECC_ERR_INJ_ERR_ADDR_Pos          2UL
#define CANFD_ECC_ERR_INJ_ERR_ADDR_Msk          0xFFFCUL
#define CANFD_ECC_ERR_INJ_ERR_EN_Pos            20UL
#define CANFD_ECC_ERR_INJ_ERR_EN_Msk            0x100000UL
#define CANFD_ECC_ERR_INJ_ERR_PAR_Pos           24UL
#define CANFD_ECC_ERR_INJ_ERR_PAR_Msk           0x7F000000UL


#endif /* _CYIP_CANFD_V3_H_ */


/* [] END OF FILE */
