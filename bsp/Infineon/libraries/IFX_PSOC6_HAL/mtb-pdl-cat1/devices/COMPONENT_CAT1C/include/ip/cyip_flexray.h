/***************************************************************************//**
* \file cyip_flexray.h
*
* \brief
* FLEXRAY IP definitions
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

#ifndef _CYIP_FLEXRAY_H_
#define _CYIP_FLEXRAY_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                   FLEXRAY
*******************************************************************************/

#define FLEXRAY_SECTION_SIZE                    0x00001000UL

/**
  * \brief FlexRay Bus Interface (FLEXRAY)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 Control Register */
  __IOM uint32_t DMA_CTL;                       /*!< 0x00000004 DMA Control Register */
   __IM uint32_t RESERVED[2];
  __IOM uint32_t TEST1;                         /*!< 0x00000010 Test Register 1 */
  __IOM uint32_t TEST2;                         /*!< 0x00000014 Test Register 2 */
   __IM uint32_t RESERVED1;
   __OM uint32_t LCK;                           /*!< 0x0000001C Lock Register */
  __IOM uint32_t EIR;                           /*!< 0x00000020 Error Interrupt Register */
  __IOM uint32_t SIR;                           /*!< 0x00000024 Status Interrupt Register */
  __IOM uint32_t EILS;                          /*!< 0x00000028 Error Interrupt Line Select */
  __IOM uint32_t SILS;                          /*!< 0x0000002C Status Interrupt Line Select */
  __IOM uint32_t EIES;                          /*!< 0x00000030 Error Interrupt Enable Set */
  __IOM uint32_t EIER;                          /*!< 0x00000034 Error Interrupt Enable Reset */
  __IOM uint32_t SIES;                          /*!< 0x00000038 Status Interrupt Enable Set */
  __IOM uint32_t SIER;                          /*!< 0x0000003C Status Interrupt Enable Reset */
  __IOM uint32_t ILE;                           /*!< 0x00000040 Interrupt Line Enable */
  __IOM uint32_t T0C;                           /*!< 0x00000044 Timer 0 Configuration */
  __IOM uint32_t T1C;                           /*!< 0x00000048 Timer 1 Configuration */
  __IOM uint32_t STPW1;                         /*!< 0x0000004C Stop Watch Register 1 */
   __IM uint32_t STPW2;                         /*!< 0x00000050 Stop Watch Register 2 */
   __IM uint32_t RESERVED2[11];
  __IOM uint32_t SUCC1;                         /*!< 0x00000080 SUC Configuration Register 1 */
  __IOM uint32_t SUCC2;                         /*!< 0x00000084 SUC Configuration Register 2 */
  __IOM uint32_t SUCC3;                         /*!< 0x00000088 SUC Configuration Register 3 */
  __IOM uint32_t NEMC;                          /*!< 0x0000008C NEM Configuration Register */
  __IOM uint32_t PRTC1;                         /*!< 0x00000090 PRT Configuration Register 1 */
  __IOM uint32_t PRTC2;                         /*!< 0x00000094 PRT Configuration Register 2 */
  __IOM uint32_t MHDC;                          /*!< 0x00000098 MHD Configuration Register */
   __IM uint32_t RESERVED3;
  __IOM uint32_t GTUC1;                         /*!< 0x000000A0 GTU Configuration Register 1 */
  __IOM uint32_t GTUC2;                         /*!< 0x000000A4 GTU Configuration Register 2 */
  __IOM uint32_t GTUC3;                         /*!< 0x000000A8 GTU Configuration Register 3 */
  __IOM uint32_t GTUC4;                         /*!< 0x000000AC GTU Configuration Register 4 */
  __IOM uint32_t GTUC5;                         /*!< 0x000000B0 GTU Configuration Register 5 */
  __IOM uint32_t GTUC6;                         /*!< 0x000000B4 GTU Configuration Register 6 */
  __IOM uint32_t GTUC7;                         /*!< 0x000000B8 GTU Configuration Register 7 */
  __IOM uint32_t GTUC8;                         /*!< 0x000000BC GTU Configuration Register 8 */
  __IOM uint32_t GTUC9;                         /*!< 0x000000C0 GTU Configuration Register 9 */
  __IOM uint32_t GTUC10;                        /*!< 0x000000C4 GTU Configuration Register 10 */
  __IOM uint32_t GTUC11;                        /*!< 0x000000C8 GTU Configuration Register 11 */
   __IM uint32_t RESERVED4[13];
   __IM uint32_t CCSV;                          /*!< 0x00000100 CC Status Vector */
   __IM uint32_t CCEV;                          /*!< 0x00000104 CC Error Vector */
   __IM uint32_t RESERVED5[2];
   __IM uint32_t SCV;                           /*!< 0x00000110 Slot Counter Value */
   __IM uint32_t MTCCV;                         /*!< 0x00000114 Macrotick and Cycle Counter Value */
   __IM uint32_t RCV;                           /*!< 0x00000118 Rate Correction Value */
   __IM uint32_t OCV;                           /*!< 0x0000011C Offset Correction Value */
   __IM uint32_t SFS;                           /*!< 0x00000120 Sync Frame Status */
   __IM uint32_t SWNIT;                         /*!< 0x00000124 Symbol Window and NIT Status */
  __IOM uint32_t ACS;                           /*!< 0x00000128 Aggregated Channel Status */
   __IM uint32_t RESERVED6;
   __IM uint32_t ESID[15];                      /*!< 0x00000130 Even Sync ID [1...15] */
   __IM uint32_t RESERVED7;
   __IM uint32_t OSID[15];                      /*!< 0x00000170 Odd Sync ID [1...15] */
   __IM uint32_t RESERVED8;
   __IM uint32_t NMV1;                          /*!< 0x000001B0 Network Management Vector 1 */
   __IM uint32_t NMV2;                          /*!< 0x000001B4 Network Management Vector 2 */
   __IM uint32_t NMV3;                          /*!< 0x000001B8 Network Management Vector 3 */
   __IM uint32_t RESERVED9[81];
  __IOM uint32_t MRC;                           /*!< 0x00000300 Message RAM Configuration */
  __IOM uint32_t FRF;                           /*!< 0x00000304 FIFO Rejection Filter */
  __IOM uint32_t FRFM;                          /*!< 0x00000308 FIFO Rejection Filter Mask */
  __IOM uint32_t FCL;                           /*!< 0x0000030C FIFO Critical Level */
  __IOM uint32_t MHDS;                          /*!< 0x00000310 Message Handler Status */
   __IM uint32_t LDTS;                          /*!< 0x00000314 Last Dynamic Transmit Slot */
   __IM uint32_t FSR;                           /*!< 0x00000318 FIFO Status Register */
  __IOM uint32_t MHDF;                          /*!< 0x0000031C Message Handler Constraints Flags */
   __IM uint32_t TXRQ1;                         /*!< 0x00000320 Transmission Request 1 */
   __IM uint32_t TXRQ2;                         /*!< 0x00000324 Transmission Request 2 */
   __IM uint32_t TXRQ3;                         /*!< 0x00000328 Transmission Request 3 */
   __IM uint32_t TXRQ4;                         /*!< 0x0000032C Transmission Request 4 */
   __IM uint32_t NDAT1;                         /*!< 0x00000330 New Data 1 */
   __IM uint32_t NDAT2;                         /*!< 0x00000334 New Data 2 */
   __IM uint32_t NDAT3;                         /*!< 0x00000338 New Data 3 */
   __IM uint32_t NDAT4;                         /*!< 0x0000033C New Data 4 */
   __IM uint32_t MBSC1;                         /*!< 0x00000340 Message Buffer Status Changed 1 */
   __IM uint32_t MBSC2;                         /*!< 0x00000344 Message Buffer Status Changed 2 */
   __IM uint32_t MBSC3;                         /*!< 0x00000348 Message Buffer Status Changed 3 */
   __IM uint32_t MBSC4;                         /*!< 0x0000034C Message Buffer Status Changed 4 */
   __IM uint32_t RESERVED10[40];
   __IM uint32_t CREL;                          /*!< 0x000003F0 Core Release Register */
   __IM uint32_t ENDN;                          /*!< 0x000003F4 Endian Register */
   __IM uint32_t RESERVED11[2];
  __IOM uint32_t WRDS[64];                      /*!< 0x00000400 Write Data Section [1...64] */
  __IOM uint32_t WRHS1;                         /*!< 0x00000500 Write Header Section 1 */
  __IOM uint32_t WRHS2;                         /*!< 0x00000504 Write Header Section 2 */
  __IOM uint32_t WRHS3;                         /*!< 0x00000508 Write Header Section 3 */
   __IM uint32_t RESERVED12;
  __IOM uint32_t IBCM;                          /*!< 0x00000510 Input Buffer Command Mask */
  __IOM uint32_t IBCR;                          /*!< 0x00000514 Input Buffer Command Request */
   __IM uint32_t RESERVED13[58];
   __IM uint32_t RDDS[64];                      /*!< 0x00000600 Read Data Section [1...64] */
   __IM uint32_t RDHS1;                         /*!< 0x00000700 Read Header Section 1 */
   __IM uint32_t RDHS2;                         /*!< 0x00000704 Read Header Section 2 */
   __IM uint32_t RDHS3;                         /*!< 0x00000708 Read Header Section 3 */
   __IM uint32_t MBS;                           /*!< 0x0000070C Message Buffer Status */
  __IOM uint32_t OBCM;                          /*!< 0x00000710 Output Buffer Command Mask */
  __IOM uint32_t OBCR;                          /*!< 0x00000714 Output Buffer Command Request */
   __IM uint32_t RESERVED14[310];
  __IOM uint32_t WRHS1_MIR2;                    /*!< 0x00000BF0 Write Header Section 1 (2nd mirror) */
  __IOM uint32_t WRHS2_MIR2;                    /*!< 0x00000BF4 Write Header Section 2 (2nd mirror) */
  __IOM uint32_t WRHS3_MIR2;                    /*!< 0x00000BF8 Write Header Section 3 (2nd mirror) */
   __IM uint32_t RESERVED15;
  __IOM uint32_t WRDS_MIR[64];                  /*!< 0x00000C00 Write Data Section [1...64] (mirror) */
  __IOM uint32_t WRHS1_MIR;                     /*!< 0x00000D00 Write Header Section 1 (mirror) */
  __IOM uint32_t WRHS2_MIR;                     /*!< 0x00000D04 Write Header Section 2 (mirror) */
  __IOM uint32_t WRHS3_MIR;                     /*!< 0x00000D08 Write Header Section 3 (mirror) */
   __IM uint32_t RESERVED16;
  __IOM uint32_t IBCM_MIR;                      /*!< 0x00000D10 Input Buffer Command Mask (mirror) */
  __IOM uint32_t IBCR_MIR;                      /*!< 0x00000D14 Input Buffer Command Request (mirror) */
   __IM uint32_t RESERVED17[54];
   __IM uint32_t RDHS1_MIR2;                    /*!< 0x00000DF0 Read Header Section 1 (2nd mirror) */
   __IM uint32_t RDHS2_MIR2;                    /*!< 0x00000DF4 Read Header Section 2 (2nd mirror) */
   __IM uint32_t RDHS3_MIR2;                    /*!< 0x00000DF8 Read Header Section 3 (2nd mirror) */
   __IM uint32_t MBS_MIR2;                      /*!< 0x00000DFC Message Buffer Status  (2nd mirror) */
   __IM uint32_t RDDS_MIR[64];                  /*!< 0x00000E00 Read Data Section [1...64] (mirror) */
   __IM uint32_t RDHS1_MIR;                     /*!< 0x00000F00 Read Header Section 1 (mirror) */
   __IM uint32_t RDHS2_MIR;                     /*!< 0x00000F04 Read Header Section 2 (mirror) */
   __IM uint32_t RDHS3_MIR;                     /*!< 0x00000F08 Read Header Section 3 (mirror) */
   __IM uint32_t MBS_MIR;                       /*!< 0x00000F0C Message Buffer Status (mirror) */
  __IOM uint32_t OBCM_MIR;                      /*!< 0x00000F10 Output Buffer Command Mask (mirror) */
  __IOM uint32_t OBCR_MIR;                      /*!< 0x00000F14 Output Buffer Command Request (mirror) */
} FLEXRAY_Type;                                 /*!< Size = 3864 (0xF18) */


/* FLEXRAY.CTL */
#define FLEXRAY_CTL_ENABLED_Pos                 31UL
#define FLEXRAY_CTL_ENABLED_Msk                 0x80000000UL
/* FLEXRAY.DMA_CTL */
#define FLEXRAY_DMA_CTL_IDMATOE_Pos             0UL
#define FLEXRAY_DMA_CTL_IDMATOE_Msk             0x1UL
#define FLEXRAY_DMA_CTL_ODMATOE_Pos             1UL
#define FLEXRAY_DMA_CTL_ODMATOE_Msk             0x2UL
#define FLEXRAY_DMA_CTL_ODMAFFE_Pos             2UL
#define FLEXRAY_DMA_CTL_ODMAFFE_Msk             0x4UL
/* FLEXRAY.TEST1 */
#define FLEXRAY_TEST1_WRTEN_Pos                 0UL
#define FLEXRAY_TEST1_WRTEN_Msk                 0x1UL
#define FLEXRAY_TEST1_ELBE_Pos                  1UL
#define FLEXRAY_TEST1_ELBE_Msk                  0x2UL
#define FLEXRAY_TEST1_TMC_Pos                   4UL
#define FLEXRAY_TEST1_TMC_Msk                   0x30UL
#define FLEXRAY_TEST1_AOA_Pos                   8UL
#define FLEXRAY_TEST1_AOA_Msk                   0x100UL
#define FLEXRAY_TEST1_AOB_Pos                   9UL
#define FLEXRAY_TEST1_AOB_Msk                   0x200UL
#define FLEXRAY_TEST1_RXA_Pos                   16UL
#define FLEXRAY_TEST1_RXA_Msk                   0x10000UL
#define FLEXRAY_TEST1_RXB_Pos                   17UL
#define FLEXRAY_TEST1_RXB_Msk                   0x20000UL
#define FLEXRAY_TEST1_TXA_Pos                   18UL
#define FLEXRAY_TEST1_TXA_Msk                   0x40000UL
#define FLEXRAY_TEST1_TXB_Pos                   19UL
#define FLEXRAY_TEST1_TXB_Msk                   0x80000UL
#define FLEXRAY_TEST1_TXENA_Pos                 20UL
#define FLEXRAY_TEST1_TXENA_Msk                 0x100000UL
#define FLEXRAY_TEST1_TXENB_Pos                 21UL
#define FLEXRAY_TEST1_TXENB_Msk                 0x200000UL
#define FLEXRAY_TEST1_CERA_Pos                  24UL
#define FLEXRAY_TEST1_CERA_Msk                  0xF000000UL
#define FLEXRAY_TEST1_CERB_Pos                  28UL
#define FLEXRAY_TEST1_CERB_Msk                  0xF0000000UL
/* FLEXRAY.TEST2 */
#define FLEXRAY_TEST2_RS_Pos                    0UL
#define FLEXRAY_TEST2_RS_Msk                    0x7UL
#define FLEXRAY_TEST2_SSEL_Pos                  4UL
#define FLEXRAY_TEST2_SSEL_Msk                  0x70UL
#define FLEXRAY_TEST2_WRPB_Pos                  14UL
#define FLEXRAY_TEST2_WRPB_Msk                  0x4000UL
#define FLEXRAY_TEST2_RDPB_Pos                  15UL
#define FLEXRAY_TEST2_RDPB_Msk                  0x8000UL
/* FLEXRAY.LCK */
#define FLEXRAY_LCK_CLK_Pos                     0UL
#define FLEXRAY_LCK_CLK_Msk                     0xFFUL
#define FLEXRAY_LCK_TMK_Pos                     8UL
#define FLEXRAY_LCK_TMK_Msk                     0xFF00UL
/* FLEXRAY.EIR */
#define FLEXRAY_EIR_PEMC_Pos                    0UL
#define FLEXRAY_EIR_PEMC_Msk                    0x1UL
#define FLEXRAY_EIR_CNA_Pos                     1UL
#define FLEXRAY_EIR_CNA_Msk                     0x2UL
#define FLEXRAY_EIR_SFBM_Pos                    2UL
#define FLEXRAY_EIR_SFBM_Msk                    0x4UL
#define FLEXRAY_EIR_SFO_Pos                     3UL
#define FLEXRAY_EIR_SFO_Msk                     0x8UL
#define FLEXRAY_EIR_CCF_Pos                     4UL
#define FLEXRAY_EIR_CCF_Msk                     0x10UL
#define FLEXRAY_EIR_CCL_Pos                     5UL
#define FLEXRAY_EIR_CCL_Msk                     0x20UL
#define FLEXRAY_EIR_PERR_Pos                    6UL
#define FLEXRAY_EIR_PERR_Msk                    0x40UL
#define FLEXRAY_EIR_RFO_Pos                     7UL
#define FLEXRAY_EIR_RFO_Msk                     0x80UL
#define FLEXRAY_EIR_EFA_Pos                     8UL
#define FLEXRAY_EIR_EFA_Msk                     0x100UL
#define FLEXRAY_EIR_IIBA_Pos                    9UL
#define FLEXRAY_EIR_IIBA_Msk                    0x200UL
#define FLEXRAY_EIR_IOBA_Pos                    10UL
#define FLEXRAY_EIR_IOBA_Msk                    0x400UL
#define FLEXRAY_EIR_MHF_Pos                     11UL
#define FLEXRAY_EIR_MHF_Msk                     0x800UL
#define FLEXRAY_EIR_EDA_Pos                     16UL
#define FLEXRAY_EIR_EDA_Msk                     0x10000UL
#define FLEXRAY_EIR_LTVA_Pos                    17UL
#define FLEXRAY_EIR_LTVA_Msk                    0x20000UL
#define FLEXRAY_EIR_TABA_Pos                    18UL
#define FLEXRAY_EIR_TABA_Msk                    0x40000UL
#define FLEXRAY_EIR_EDB_Pos                     24UL
#define FLEXRAY_EIR_EDB_Msk                     0x1000000UL
#define FLEXRAY_EIR_LTVB_Pos                    25UL
#define FLEXRAY_EIR_LTVB_Msk                    0x2000000UL
#define FLEXRAY_EIR_TABB_Pos                    26UL
#define FLEXRAY_EIR_TABB_Msk                    0x4000000UL
/* FLEXRAY.SIR */
#define FLEXRAY_SIR_WST_Pos                     0UL
#define FLEXRAY_SIR_WST_Msk                     0x1UL
#define FLEXRAY_SIR_CAS_Pos                     1UL
#define FLEXRAY_SIR_CAS_Msk                     0x2UL
#define FLEXRAY_SIR_CYCS_Pos                    2UL
#define FLEXRAY_SIR_CYCS_Msk                    0x4UL
#define FLEXRAY_SIR_TXI_Pos                     3UL
#define FLEXRAY_SIR_TXI_Msk                     0x8UL
#define FLEXRAY_SIR_RXI_Pos                     4UL
#define FLEXRAY_SIR_RXI_Msk                     0x10UL
#define FLEXRAY_SIR_RFNE_Pos                    5UL
#define FLEXRAY_SIR_RFNE_Msk                    0x20UL
#define FLEXRAY_SIR_RFCL_Pos                    6UL
#define FLEXRAY_SIR_RFCL_Msk                    0x40UL
#define FLEXRAY_SIR_NMVC_Pos                    7UL
#define FLEXRAY_SIR_NMVC_Msk                    0x80UL
#define FLEXRAY_SIR_TI0_Pos                     8UL
#define FLEXRAY_SIR_TI0_Msk                     0x100UL
#define FLEXRAY_SIR_TI1_Pos                     9UL
#define FLEXRAY_SIR_TI1_Msk                     0x200UL
#define FLEXRAY_SIR_TIBC_Pos                    10UL
#define FLEXRAY_SIR_TIBC_Msk                    0x400UL
#define FLEXRAY_SIR_TOBC_Pos                    11UL
#define FLEXRAY_SIR_TOBC_Msk                    0x800UL
#define FLEXRAY_SIR_SWE_Pos                     12UL
#define FLEXRAY_SIR_SWE_Msk                     0x1000UL
#define FLEXRAY_SIR_SUCS_Pos                    13UL
#define FLEXRAY_SIR_SUCS_Msk                    0x2000UL
#define FLEXRAY_SIR_MBSI_Pos                    14UL
#define FLEXRAY_SIR_MBSI_Msk                    0x4000UL
#define FLEXRAY_SIR_SDS_Pos                     15UL
#define FLEXRAY_SIR_SDS_Msk                     0x8000UL
#define FLEXRAY_SIR_WUPA_Pos                    16UL
#define FLEXRAY_SIR_WUPA_Msk                    0x10000UL
#define FLEXRAY_SIR_MTSA_Pos                    17UL
#define FLEXRAY_SIR_MTSA_Msk                    0x20000UL
#define FLEXRAY_SIR_WUPB_Pos                    24UL
#define FLEXRAY_SIR_WUPB_Msk                    0x1000000UL
#define FLEXRAY_SIR_MTSB_Pos                    25UL
#define FLEXRAY_SIR_MTSB_Msk                    0x2000000UL
/* FLEXRAY.EILS */
#define FLEXRAY_EILS_PEMCL_Pos                  0UL
#define FLEXRAY_EILS_PEMCL_Msk                  0x1UL
#define FLEXRAY_EILS_CNAL_Pos                   1UL
#define FLEXRAY_EILS_CNAL_Msk                   0x2UL
#define FLEXRAY_EILS_SFBML_Pos                  2UL
#define FLEXRAY_EILS_SFBML_Msk                  0x4UL
#define FLEXRAY_EILS_SFOL_Pos                   3UL
#define FLEXRAY_EILS_SFOL_Msk                   0x8UL
#define FLEXRAY_EILS_CCFL_Pos                   4UL
#define FLEXRAY_EILS_CCFL_Msk                   0x10UL
#define FLEXRAY_EILS_CCLL_Pos                   5UL
#define FLEXRAY_EILS_CCLL_Msk                   0x20UL
#define FLEXRAY_EILS_PERRL_Pos                  6UL
#define FLEXRAY_EILS_PERRL_Msk                  0x40UL
#define FLEXRAY_EILS_RFOL_Pos                   7UL
#define FLEXRAY_EILS_RFOL_Msk                   0x80UL
#define FLEXRAY_EILS_EFAL_Pos                   8UL
#define FLEXRAY_EILS_EFAL_Msk                   0x100UL
#define FLEXRAY_EILS_IIBAL_Pos                  9UL
#define FLEXRAY_EILS_IIBAL_Msk                  0x200UL
#define FLEXRAY_EILS_IOBAL_Pos                  10UL
#define FLEXRAY_EILS_IOBAL_Msk                  0x400UL
#define FLEXRAY_EILS_MHFL_Pos                   11UL
#define FLEXRAY_EILS_MHFL_Msk                   0x800UL
#define FLEXRAY_EILS_EDAL_Pos                   16UL
#define FLEXRAY_EILS_EDAL_Msk                   0x10000UL
#define FLEXRAY_EILS_LTVAL_Pos                  17UL
#define FLEXRAY_EILS_LTVAL_Msk                  0x20000UL
#define FLEXRAY_EILS_TABAL_Pos                  18UL
#define FLEXRAY_EILS_TABAL_Msk                  0x40000UL
#define FLEXRAY_EILS_EDBL_Pos                   24UL
#define FLEXRAY_EILS_EDBL_Msk                   0x1000000UL
#define FLEXRAY_EILS_LTVBL_Pos                  25UL
#define FLEXRAY_EILS_LTVBL_Msk                  0x2000000UL
#define FLEXRAY_EILS_TABBL_Pos                  26UL
#define FLEXRAY_EILS_TABBL_Msk                  0x4000000UL
/* FLEXRAY.SILS */
#define FLEXRAY_SILS_WSTL_Pos                   0UL
#define FLEXRAY_SILS_WSTL_Msk                   0x1UL
#define FLEXRAY_SILS_CASL_Pos                   1UL
#define FLEXRAY_SILS_CASL_Msk                   0x2UL
#define FLEXRAY_SILS_CYCSL_Pos                  2UL
#define FLEXRAY_SILS_CYCSL_Msk                  0x4UL
#define FLEXRAY_SILS_TXIL_Pos                   3UL
#define FLEXRAY_SILS_TXIL_Msk                   0x8UL
#define FLEXRAY_SILS_RXIL_Pos                   4UL
#define FLEXRAY_SILS_RXIL_Msk                   0x10UL
#define FLEXRAY_SILS_RFNEL_Pos                  5UL
#define FLEXRAY_SILS_RFNEL_Msk                  0x20UL
#define FLEXRAY_SILS_RFCLL_Pos                  6UL
#define FLEXRAY_SILS_RFCLL_Msk                  0x40UL
#define FLEXRAY_SILS_NMVCL_Pos                  7UL
#define FLEXRAY_SILS_NMVCL_Msk                  0x80UL
#define FLEXRAY_SILS_TI0L_Pos                   8UL
#define FLEXRAY_SILS_TI0L_Msk                   0x100UL
#define FLEXRAY_SILS_TI1L_Pos                   9UL
#define FLEXRAY_SILS_TI1L_Msk                   0x200UL
#define FLEXRAY_SILS_TIBCL_Pos                  10UL
#define FLEXRAY_SILS_TIBCL_Msk                  0x400UL
#define FLEXRAY_SILS_TOBCL_Pos                  11UL
#define FLEXRAY_SILS_TOBCL_Msk                  0x800UL
#define FLEXRAY_SILS_SWEL_Pos                   12UL
#define FLEXRAY_SILS_SWEL_Msk                   0x1000UL
#define FLEXRAY_SILS_SUCSL_Pos                  13UL
#define FLEXRAY_SILS_SUCSL_Msk                  0x2000UL
#define FLEXRAY_SILS_MBSIL_Pos                  14UL
#define FLEXRAY_SILS_MBSIL_Msk                  0x4000UL
#define FLEXRAY_SILS_SDSL_Pos                   15UL
#define FLEXRAY_SILS_SDSL_Msk                   0x8000UL
#define FLEXRAY_SILS_WUPAL_Pos                  16UL
#define FLEXRAY_SILS_WUPAL_Msk                  0x10000UL
#define FLEXRAY_SILS_MTSAL_Pos                  17UL
#define FLEXRAY_SILS_MTSAL_Msk                  0x20000UL
#define FLEXRAY_SILS_WUPBL_Pos                  24UL
#define FLEXRAY_SILS_WUPBL_Msk                  0x1000000UL
#define FLEXRAY_SILS_MTSBL_Pos                  25UL
#define FLEXRAY_SILS_MTSBL_Msk                  0x2000000UL
/* FLEXRAY.EIES */
#define FLEXRAY_EIES_PEMCE_Pos                  0UL
#define FLEXRAY_EIES_PEMCE_Msk                  0x1UL
#define FLEXRAY_EIES_CNAE_Pos                   1UL
#define FLEXRAY_EIES_CNAE_Msk                   0x2UL
#define FLEXRAY_EIES_SFBME_Pos                  2UL
#define FLEXRAY_EIES_SFBME_Msk                  0x4UL
#define FLEXRAY_EIES_SFOE_Pos                   3UL
#define FLEXRAY_EIES_SFOE_Msk                   0x8UL
#define FLEXRAY_EIES_CCFE_Pos                   4UL
#define FLEXRAY_EIES_CCFE_Msk                   0x10UL
#define FLEXRAY_EIES_CCLE_Pos                   5UL
#define FLEXRAY_EIES_CCLE_Msk                   0x20UL
#define FLEXRAY_EIES_PERRE_Pos                  6UL
#define FLEXRAY_EIES_PERRE_Msk                  0x40UL
#define FLEXRAY_EIES_RFOE_Pos                   7UL
#define FLEXRAY_EIES_RFOE_Msk                   0x80UL
#define FLEXRAY_EIES_EFAE_Pos                   8UL
#define FLEXRAY_EIES_EFAE_Msk                   0x100UL
#define FLEXRAY_EIES_IIBAE_Pos                  9UL
#define FLEXRAY_EIES_IIBAE_Msk                  0x200UL
#define FLEXRAY_EIES_IOBAE_Pos                  10UL
#define FLEXRAY_EIES_IOBAE_Msk                  0x400UL
#define FLEXRAY_EIES_MHFE_Pos                   11UL
#define FLEXRAY_EIES_MHFE_Msk                   0x800UL
#define FLEXRAY_EIES_EDAE_Pos                   16UL
#define FLEXRAY_EIES_EDAE_Msk                   0x10000UL
#define FLEXRAY_EIES_LTVAE_Pos                  17UL
#define FLEXRAY_EIES_LTVAE_Msk                  0x20000UL
#define FLEXRAY_EIES_TABAE_Pos                  18UL
#define FLEXRAY_EIES_TABAE_Msk                  0x40000UL
#define FLEXRAY_EIES_EDBE_Pos                   24UL
#define FLEXRAY_EIES_EDBE_Msk                   0x1000000UL
#define FLEXRAY_EIES_LTVBE_Pos                  25UL
#define FLEXRAY_EIES_LTVBE_Msk                  0x2000000UL
#define FLEXRAY_EIES_TABBE_Pos                  26UL
#define FLEXRAY_EIES_TABBE_Msk                  0x4000000UL
/* FLEXRAY.EIER */
#define FLEXRAY_EIER_PEMCE_Pos                  0UL
#define FLEXRAY_EIER_PEMCE_Msk                  0x1UL
#define FLEXRAY_EIER_CNAE_Pos                   1UL
#define FLEXRAY_EIER_CNAE_Msk                   0x2UL
#define FLEXRAY_EIER_SFBME_Pos                  2UL
#define FLEXRAY_EIER_SFBME_Msk                  0x4UL
#define FLEXRAY_EIER_SFOE_Pos                   3UL
#define FLEXRAY_EIER_SFOE_Msk                   0x8UL
#define FLEXRAY_EIER_CCFE_Pos                   4UL
#define FLEXRAY_EIER_CCFE_Msk                   0x10UL
#define FLEXRAY_EIER_CCLE_Pos                   5UL
#define FLEXRAY_EIER_CCLE_Msk                   0x20UL
#define FLEXRAY_EIER_PERRE_Pos                  6UL
#define FLEXRAY_EIER_PERRE_Msk                  0x40UL
#define FLEXRAY_EIER_RFOE_Pos                   7UL
#define FLEXRAY_EIER_RFOE_Msk                   0x80UL
#define FLEXRAY_EIER_EFAE_Pos                   8UL
#define FLEXRAY_EIER_EFAE_Msk                   0x100UL
#define FLEXRAY_EIER_IIBAE_Pos                  9UL
#define FLEXRAY_EIER_IIBAE_Msk                  0x200UL
#define FLEXRAY_EIER_IOBAE_Pos                  10UL
#define FLEXRAY_EIER_IOBAE_Msk                  0x400UL
#define FLEXRAY_EIER_MHFE_Pos                   11UL
#define FLEXRAY_EIER_MHFE_Msk                   0x800UL
#define FLEXRAY_EIER_EDAE_Pos                   16UL
#define FLEXRAY_EIER_EDAE_Msk                   0x10000UL
#define FLEXRAY_EIER_LTVAE_Pos                  17UL
#define FLEXRAY_EIER_LTVAE_Msk                  0x20000UL
#define FLEXRAY_EIER_TABAE_Pos                  18UL
#define FLEXRAY_EIER_TABAE_Msk                  0x40000UL
#define FLEXRAY_EIER_EDBE_Pos                   24UL
#define FLEXRAY_EIER_EDBE_Msk                   0x1000000UL
#define FLEXRAY_EIER_LTVBE_Pos                  25UL
#define FLEXRAY_EIER_LTVBE_Msk                  0x2000000UL
#define FLEXRAY_EIER_TABBE_Pos                  26UL
#define FLEXRAY_EIER_TABBE_Msk                  0x4000000UL
/* FLEXRAY.SIES */
#define FLEXRAY_SIES_WSTE_Pos                   0UL
#define FLEXRAY_SIES_WSTE_Msk                   0x1UL
#define FLEXRAY_SIES_CASE_Pos                   1UL
#define FLEXRAY_SIES_CASE_Msk                   0x2UL
#define FLEXRAY_SIES_CYCSE_Pos                  2UL
#define FLEXRAY_SIES_CYCSE_Msk                  0x4UL
#define FLEXRAY_SIES_TXIE_Pos                   3UL
#define FLEXRAY_SIES_TXIE_Msk                   0x8UL
#define FLEXRAY_SIES_RXIE_Pos                   4UL
#define FLEXRAY_SIES_RXIE_Msk                   0x10UL
#define FLEXRAY_SIES_RFNEE_Pos                  5UL
#define FLEXRAY_SIES_RFNEE_Msk                  0x20UL
#define FLEXRAY_SIES_RFCLE_Pos                  6UL
#define FLEXRAY_SIES_RFCLE_Msk                  0x40UL
#define FLEXRAY_SIES_NMVCE_Pos                  7UL
#define FLEXRAY_SIES_NMVCE_Msk                  0x80UL
#define FLEXRAY_SIES_TI0E_Pos                   8UL
#define FLEXRAY_SIES_TI0E_Msk                   0x100UL
#define FLEXRAY_SIES_TI1E_Pos                   9UL
#define FLEXRAY_SIES_TI1E_Msk                   0x200UL
#define FLEXRAY_SIES_TIBCE_Pos                  10UL
#define FLEXRAY_SIES_TIBCE_Msk                  0x400UL
#define FLEXRAY_SIES_TOBCE_Pos                  11UL
#define FLEXRAY_SIES_TOBCE_Msk                  0x800UL
#define FLEXRAY_SIES_SWEE_Pos                   12UL
#define FLEXRAY_SIES_SWEE_Msk                   0x1000UL
#define FLEXRAY_SIES_SUCSE_Pos                  13UL
#define FLEXRAY_SIES_SUCSE_Msk                  0x2000UL
#define FLEXRAY_SIES_MBSIE_Pos                  14UL
#define FLEXRAY_SIES_MBSIE_Msk                  0x4000UL
#define FLEXRAY_SIES_SDSE_Pos                   15UL
#define FLEXRAY_SIES_SDSE_Msk                   0x8000UL
#define FLEXRAY_SIES_WUPAE_Pos                  16UL
#define FLEXRAY_SIES_WUPAE_Msk                  0x10000UL
#define FLEXRAY_SIES_MTSAE_Pos                  17UL
#define FLEXRAY_SIES_MTSAE_Msk                  0x20000UL
#define FLEXRAY_SIES_WUPBE_Pos                  24UL
#define FLEXRAY_SIES_WUPBE_Msk                  0x1000000UL
#define FLEXRAY_SIES_MTSBE_Pos                  25UL
#define FLEXRAY_SIES_MTSBE_Msk                  0x2000000UL
/* FLEXRAY.SIER */
#define FLEXRAY_SIER_WSTE_Pos                   0UL
#define FLEXRAY_SIER_WSTE_Msk                   0x1UL
#define FLEXRAY_SIER_CASE_Pos                   1UL
#define FLEXRAY_SIER_CASE_Msk                   0x2UL
#define FLEXRAY_SIER_CYCSE_Pos                  2UL
#define FLEXRAY_SIER_CYCSE_Msk                  0x4UL
#define FLEXRAY_SIER_TXIE_Pos                   3UL
#define FLEXRAY_SIER_TXIE_Msk                   0x8UL
#define FLEXRAY_SIER_RXIE_Pos                   4UL
#define FLEXRAY_SIER_RXIE_Msk                   0x10UL
#define FLEXRAY_SIER_RFNEE_Pos                  5UL
#define FLEXRAY_SIER_RFNEE_Msk                  0x20UL
#define FLEXRAY_SIER_RFCLE_Pos                  6UL
#define FLEXRAY_SIER_RFCLE_Msk                  0x40UL
#define FLEXRAY_SIER_NMVCE_Pos                  7UL
#define FLEXRAY_SIER_NMVCE_Msk                  0x80UL
#define FLEXRAY_SIER_TI0E_Pos                   8UL
#define FLEXRAY_SIER_TI0E_Msk                   0x100UL
#define FLEXRAY_SIER_TI1E_Pos                   9UL
#define FLEXRAY_SIER_TI1E_Msk                   0x200UL
#define FLEXRAY_SIER_TIBCE_Pos                  10UL
#define FLEXRAY_SIER_TIBCE_Msk                  0x400UL
#define FLEXRAY_SIER_TOBCE_Pos                  11UL
#define FLEXRAY_SIER_TOBCE_Msk                  0x800UL
#define FLEXRAY_SIER_SWEE_Pos                   12UL
#define FLEXRAY_SIER_SWEE_Msk                   0x1000UL
#define FLEXRAY_SIER_SUCSE_Pos                  13UL
#define FLEXRAY_SIER_SUCSE_Msk                  0x2000UL
#define FLEXRAY_SIER_MBSIE_Pos                  14UL
#define FLEXRAY_SIER_MBSIE_Msk                  0x4000UL
#define FLEXRAY_SIER_SDSE_Pos                   15UL
#define FLEXRAY_SIER_SDSE_Msk                   0x8000UL
#define FLEXRAY_SIER_WUPAE_Pos                  16UL
#define FLEXRAY_SIER_WUPAE_Msk                  0x10000UL
#define FLEXRAY_SIER_MTSAE_Pos                  17UL
#define FLEXRAY_SIER_MTSAE_Msk                  0x20000UL
#define FLEXRAY_SIER_WUPBE_Pos                  24UL
#define FLEXRAY_SIER_WUPBE_Msk                  0x1000000UL
#define FLEXRAY_SIER_MTSBE_Pos                  25UL
#define FLEXRAY_SIER_MTSBE_Msk                  0x2000000UL
/* FLEXRAY.ILE */
#define FLEXRAY_ILE_EINT0__Pos                  0UL
#define FLEXRAY_ILE_EINT0__Msk                  0x1UL
#define FLEXRAY_ILE_EINT1__Pos                  1UL
#define FLEXRAY_ILE_EINT1__Msk                  0x2UL
/* FLEXRAY.T0C */
#define FLEXRAY_T0C_T0RC_Pos                    0UL
#define FLEXRAY_T0C_T0RC_Msk                    0x1UL
#define FLEXRAY_T0C_T0MS_Pos                    1UL
#define FLEXRAY_T0C_T0MS_Msk                    0x2UL
#define FLEXRAY_T0C_T0CC_Pos                    8UL
#define FLEXRAY_T0C_T0CC_Msk                    0x7F00UL
#define FLEXRAY_T0C_T0MO_Pos                    16UL
#define FLEXRAY_T0C_T0MO_Msk                    0x3FFF0000UL
/* FLEXRAY.T1C */
#define FLEXRAY_T1C_T1RC_Pos                    0UL
#define FLEXRAY_T1C_T1RC_Msk                    0x1UL
#define FLEXRAY_T1C_T1MS_Pos                    1UL
#define FLEXRAY_T1C_T1MS_Msk                    0x2UL
#define FLEXRAY_T1C_T1MC_Pos                    16UL
#define FLEXRAY_T1C_T1MC_Msk                    0x3FFF0000UL
/* FLEXRAY.STPW1 */
#define FLEXRAY_STPW1_ESWT_Pos                  0UL
#define FLEXRAY_STPW1_ESWT_Msk                  0x1UL
#define FLEXRAY_STPW1_SWMS_Pos                  1UL
#define FLEXRAY_STPW1_SWMS_Msk                  0x2UL
#define FLEXRAY_STPW1_EDGE_Pos                  2UL
#define FLEXRAY_STPW1_EDGE_Msk                  0x4UL
#define FLEXRAY_STPW1_SSWT_Pos                  3UL
#define FLEXRAY_STPW1_SSWT_Msk                  0x8UL
#define FLEXRAY_STPW1_EETP_Pos                  4UL
#define FLEXRAY_STPW1_EETP_Msk                  0x10UL
#define FLEXRAY_STPW1_EINT0_Pos                 5UL
#define FLEXRAY_STPW1_EINT0_Msk                 0x20UL
#define FLEXRAY_STPW1_EINT1_Pos                 6UL
#define FLEXRAY_STPW1_EINT1_Msk                 0x40UL
#define FLEXRAY_STPW1_SCCV_Pos                  8UL
#define FLEXRAY_STPW1_SCCV_Msk                  0x3F00UL
#define FLEXRAY_STPW1_SMTV_Pos                  16UL
#define FLEXRAY_STPW1_SMTV_Msk                  0x3FFF0000UL
/* FLEXRAY.STPW2 */
#define FLEXRAY_STPW2_SSCVA_Pos                 0UL
#define FLEXRAY_STPW2_SSCVA_Msk                 0x7FFUL
#define FLEXRAY_STPW2_SSCVB_Pos                 16UL
#define FLEXRAY_STPW2_SSCVB_Msk                 0x7FF0000UL
/* FLEXRAY.SUCC1 */
#define FLEXRAY_SUCC1_CMD_Pos                   0UL
#define FLEXRAY_SUCC1_CMD_Msk                   0xFUL
#define FLEXRAY_SUCC1_PBSY_Pos                  7UL
#define FLEXRAY_SUCC1_PBSY_Msk                  0x80UL
#define FLEXRAY_SUCC1_TXST_Pos                  8UL
#define FLEXRAY_SUCC1_TXST_Msk                  0x100UL
#define FLEXRAY_SUCC1_TXSY_Pos                  9UL
#define FLEXRAY_SUCC1_TXSY_Msk                  0x200UL
#define FLEXRAY_SUCC1_CSA_Pos                   11UL
#define FLEXRAY_SUCC1_CSA_Msk                   0xF800UL
#define FLEXRAY_SUCC1_PTA_Pos                   16UL
#define FLEXRAY_SUCC1_PTA_Msk                   0x1F0000UL
#define FLEXRAY_SUCC1_WUCS_Pos                  21UL
#define FLEXRAY_SUCC1_WUCS_Msk                  0x200000UL
#define FLEXRAY_SUCC1_TSM_Pos                   22UL
#define FLEXRAY_SUCC1_TSM_Msk                   0x400000UL
#define FLEXRAY_SUCC1_HCSE_Pos                  23UL
#define FLEXRAY_SUCC1_HCSE_Msk                  0x800000UL
#define FLEXRAY_SUCC1_MTSA__Pos                 24UL
#define FLEXRAY_SUCC1_MTSA__Msk                 0x1000000UL
#define FLEXRAY_SUCC1_MTSB__Pos                 25UL
#define FLEXRAY_SUCC1_MTSB__Msk                 0x2000000UL
#define FLEXRAY_SUCC1_CCHA_Pos                  26UL
#define FLEXRAY_SUCC1_CCHA_Msk                  0x4000000UL
#define FLEXRAY_SUCC1_CCHB_Pos                  27UL
#define FLEXRAY_SUCC1_CCHB_Msk                  0x8000000UL
/* FLEXRAY.SUCC2 */
#define FLEXRAY_SUCC2_LT_Pos                    0UL
#define FLEXRAY_SUCC2_LT_Msk                    0x1FFFFFUL
#define FLEXRAY_SUCC2_LTN_Pos                   24UL
#define FLEXRAY_SUCC2_LTN_Msk                   0xF000000UL
/* FLEXRAY.SUCC3 */
#define FLEXRAY_SUCC3_WCP_Pos                   0UL
#define FLEXRAY_SUCC3_WCP_Msk                   0xFUL
#define FLEXRAY_SUCC3_WCF_Pos                   4UL
#define FLEXRAY_SUCC3_WCF_Msk                   0xF0UL
/* FLEXRAY.NEMC */
#define FLEXRAY_NEMC_NML_Pos                    0UL
#define FLEXRAY_NEMC_NML_Msk                    0xFUL
/* FLEXRAY.PRTC1 */
#define FLEXRAY_PRTC1_TSST_Pos                  0UL
#define FLEXRAY_PRTC1_TSST_Msk                  0xFUL
#define FLEXRAY_PRTC1_CASM_Pos                  4UL
#define FLEXRAY_PRTC1_CASM_Msk                  0x3F0UL
#define FLEXRAY_PRTC1_CASM6_Pos                 10UL
#define FLEXRAY_PRTC1_CASM6_Msk                 0x400UL
#define FLEXRAY_PRTC1_SPP_Pos                   12UL
#define FLEXRAY_PRTC1_SPP_Msk                   0x3000UL
#define FLEXRAY_PRTC1_BRP_Pos                   14UL
#define FLEXRAY_PRTC1_BRP_Msk                   0xC000UL
#define FLEXRAY_PRTC1_RXW_Pos                   16UL
#define FLEXRAY_PRTC1_RXW_Msk                   0x1FF0000UL
#define FLEXRAY_PRTC1_RWP_Pos                   26UL
#define FLEXRAY_PRTC1_RWP_Msk                   0xFC000000UL
/* FLEXRAY.PRTC2 */
#define FLEXRAY_PRTC2_RXI__Pos                  0UL
#define FLEXRAY_PRTC2_RXI__Msk                  0x3FUL
#define FLEXRAY_PRTC2_RXL_Pos                   8UL
#define FLEXRAY_PRTC2_RXL_Msk                   0x3F00UL
#define FLEXRAY_PRTC2_TXI__Pos                  16UL
#define FLEXRAY_PRTC2_TXI__Msk                  0xFF0000UL
#define FLEXRAY_PRTC2_TXL_Pos                   24UL
#define FLEXRAY_PRTC2_TXL_Msk                   0x3F000000UL
/* FLEXRAY.MHDC */
#define FLEXRAY_MHDC_SFDL_Pos                   0UL
#define FLEXRAY_MHDC_SFDL_Msk                   0x7FUL
#define FLEXRAY_MHDC_SLT_Pos                    16UL
#define FLEXRAY_MHDC_SLT_Msk                    0x1FFF0000UL
/* FLEXRAY.GTUC1 */
#define FLEXRAY_GTUC1_UT_Pos                    0UL
#define FLEXRAY_GTUC1_UT_Msk                    0xFFFFFUL
/* FLEXRAY.GTUC2 */
#define FLEXRAY_GTUC2_MPC_Pos                   0UL
#define FLEXRAY_GTUC2_MPC_Msk                   0x3FFFUL
#define FLEXRAY_GTUC2_SNM_Pos                   16UL
#define FLEXRAY_GTUC2_SNM_Msk                   0xF0000UL
/* FLEXRAY.GTUC3 */
#define FLEXRAY_GTUC3_UIOA_Pos                  0UL
#define FLEXRAY_GTUC3_UIOA_Msk                  0xFFUL
#define FLEXRAY_GTUC3_UIOB_Pos                  8UL
#define FLEXRAY_GTUC3_UIOB_Msk                  0xFF00UL
#define FLEXRAY_GTUC3_MIOA_Pos                  16UL
#define FLEXRAY_GTUC3_MIOA_Msk                  0x7F0000UL
#define FLEXRAY_GTUC3_MIOB_Pos                  24UL
#define FLEXRAY_GTUC3_MIOB_Msk                  0x7F000000UL
/* FLEXRAY.GTUC4 */
#define FLEXRAY_GTUC4_NIT_Pos                   0UL
#define FLEXRAY_GTUC4_NIT_Msk                   0x3FFFUL
#define FLEXRAY_GTUC4_OCS_Pos                   16UL
#define FLEXRAY_GTUC4_OCS_Msk                   0x3FFF0000UL
/* FLEXRAY.GTUC5 */
#define FLEXRAY_GTUC5_DCA_Pos                   0UL
#define FLEXRAY_GTUC5_DCA_Msk                   0xFFUL
#define FLEXRAY_GTUC5_DCB_Pos                   8UL
#define FLEXRAY_GTUC5_DCB_Msk                   0xFF00UL
#define FLEXRAY_GTUC5_CDD_Pos                   16UL
#define FLEXRAY_GTUC5_CDD_Msk                   0x1F0000UL
#define FLEXRAY_GTUC5_DEC_Pos                   24UL
#define FLEXRAY_GTUC5_DEC_Msk                   0xFF000000UL
/* FLEXRAY.GTUC6 */
#define FLEXRAY_GTUC6_ASR_Pos                   0UL
#define FLEXRAY_GTUC6_ASR_Msk                   0x7FFUL
#define FLEXRAY_GTUC6_MOD_Pos                   16UL
#define FLEXRAY_GTUC6_MOD_Msk                   0x7FF0000UL
/* FLEXRAY.GTUC7 */
#define FLEXRAY_GTUC7_SSL_Pos                   0UL
#define FLEXRAY_GTUC7_SSL_Msk                   0x3FFUL
#define FLEXRAY_GTUC7_NSS_Pos                   16UL
#define FLEXRAY_GTUC7_NSS_Msk                   0x3FF0000UL
/* FLEXRAY.GTUC8 */
#define FLEXRAY_GTUC8_MSL_Pos                   0UL
#define FLEXRAY_GTUC8_MSL_Msk                   0x3FUL
#define FLEXRAY_GTUC8_NMS_Pos                   16UL
#define FLEXRAY_GTUC8_NMS_Msk                   0x1FFF0000UL
/* FLEXRAY.GTUC9 */
#define FLEXRAY_GTUC9_APO_Pos                   0UL
#define FLEXRAY_GTUC9_APO_Msk                   0x3FUL
#define FLEXRAY_GTUC9_MAPO_Pos                  8UL
#define FLEXRAY_GTUC9_MAPO_Msk                  0x1F00UL
#define FLEXRAY_GTUC9_DSI_Pos                   16UL
#define FLEXRAY_GTUC9_DSI_Msk                   0x30000UL
/* FLEXRAY.GTUC10 */
#define FLEXRAY_GTUC10_MOC_Pos                  0UL
#define FLEXRAY_GTUC10_MOC_Msk                  0x3FFFUL
#define FLEXRAY_GTUC10_MRC_Pos                  16UL
#define FLEXRAY_GTUC10_MRC_Msk                  0x7FF0000UL
/* FLEXRAY.GTUC11 */
#define FLEXRAY_GTUC11_EOCC_Pos                 0UL
#define FLEXRAY_GTUC11_EOCC_Msk                 0x3UL
#define FLEXRAY_GTUC11_ERCC_Pos                 8UL
#define FLEXRAY_GTUC11_ERCC_Msk                 0x300UL
#define FLEXRAY_GTUC11_EOC_Pos                  16UL
#define FLEXRAY_GTUC11_EOC_Msk                  0x70000UL
#define FLEXRAY_GTUC11_ERC_Pos                  24UL
#define FLEXRAY_GTUC11_ERC_Msk                  0x7000000UL
/* FLEXRAY.CCSV */
#define FLEXRAY_CCSV_POCS_Pos                   0UL
#define FLEXRAY_CCSV_POCS_Msk                   0x3FUL
#define FLEXRAY_CCSV_FSI_Pos                    6UL
#define FLEXRAY_CCSV_FSI_Msk                    0x40UL
#define FLEXRAY_CCSV_HRQ_Pos                    7UL
#define FLEXRAY_CCSV_HRQ_Msk                    0x80UL
#define FLEXRAY_CCSV_SLM_Pos                    8UL
#define FLEXRAY_CCSV_SLM_Msk                    0x300UL
#define FLEXRAY_CCSV_CSNI_Pos                   12UL
#define FLEXRAY_CCSV_CSNI_Msk                   0x1000UL
#define FLEXRAY_CCSV_CSAI_Pos                   13UL
#define FLEXRAY_CCSV_CSAI_Msk                   0x2000UL
#define FLEXRAY_CCSV_CSI_Pos                    14UL
#define FLEXRAY_CCSV_CSI_Msk                    0x4000UL
#define FLEXRAY_CCSV_WSV_Pos                    16UL
#define FLEXRAY_CCSV_WSV_Msk                    0x70000UL
#define FLEXRAY_CCSV_RCA_Pos                    19UL
#define FLEXRAY_CCSV_RCA_Msk                    0xF80000UL
#define FLEXRAY_CCSV_PSL_Pos                    24UL
#define FLEXRAY_CCSV_PSL_Msk                    0x3F000000UL
/* FLEXRAY.CCEV */
#define FLEXRAY_CCEV_CCFC_Pos                   0UL
#define FLEXRAY_CCEV_CCFC_Msk                   0xFUL
#define FLEXRAY_CCEV_ERRM_Pos                   6UL
#define FLEXRAY_CCEV_ERRM_Msk                   0xC0UL
#define FLEXRAY_CCEV_PTAC_Pos                   8UL
#define FLEXRAY_CCEV_PTAC_Msk                   0x1F00UL
/* FLEXRAY.SCV */
#define FLEXRAY_SCV_SCCA_Pos                    0UL
#define FLEXRAY_SCV_SCCA_Msk                    0x7FFUL
#define FLEXRAY_SCV_SCCB_Pos                    16UL
#define FLEXRAY_SCV_SCCB_Msk                    0x7FF0000UL
/* FLEXRAY.MTCCV */
#define FLEXRAY_MTCCV_MTV_Pos                   0UL
#define FLEXRAY_MTCCV_MTV_Msk                   0x3FFFUL
#define FLEXRAY_MTCCV_CCV_Pos                   16UL
#define FLEXRAY_MTCCV_CCV_Msk                   0x3F0000UL
/* FLEXRAY.RCV */
#define FLEXRAY_RCV_RCV_Pos                     0UL
#define FLEXRAY_RCV_RCV_Msk                     0xFFFUL
/* FLEXRAY.OCV */
#define FLEXRAY_OCV_OCV_Pos                     0UL
#define FLEXRAY_OCV_OCV_Msk                     0x7FFFFUL
/* FLEXRAY.SFS */
#define FLEXRAY_SFS_VSAE_Pos                    0UL
#define FLEXRAY_SFS_VSAE_Msk                    0xFUL
#define FLEXRAY_SFS_VSAO_Pos                    4UL
#define FLEXRAY_SFS_VSAO_Msk                    0xF0UL
#define FLEXRAY_SFS_VSBE_Pos                    8UL
#define FLEXRAY_SFS_VSBE_Msk                    0xF00UL
#define FLEXRAY_SFS_VSBO_Pos                    12UL
#define FLEXRAY_SFS_VSBO_Msk                    0xF000UL
#define FLEXRAY_SFS_MOCS_Pos                    16UL
#define FLEXRAY_SFS_MOCS_Msk                    0x10000UL
#define FLEXRAY_SFS_OCLR_Pos                    17UL
#define FLEXRAY_SFS_OCLR_Msk                    0x20000UL
#define FLEXRAY_SFS_MRCS_Pos                    18UL
#define FLEXRAY_SFS_MRCS_Msk                    0x40000UL
#define FLEXRAY_SFS_RCLR_Pos                    19UL
#define FLEXRAY_SFS_RCLR_Msk                    0x80000UL
/* FLEXRAY.SWNIT */
#define FLEXRAY_SWNIT_SESA_Pos                  0UL
#define FLEXRAY_SWNIT_SESA_Msk                  0x1UL
#define FLEXRAY_SWNIT_SBSA_Pos                  1UL
#define FLEXRAY_SWNIT_SBSA_Msk                  0x2UL
#define FLEXRAY_SWNIT_TCSA_Pos                  2UL
#define FLEXRAY_SWNIT_TCSA_Msk                  0x4UL
#define FLEXRAY_SWNIT_SESB_Pos                  3UL
#define FLEXRAY_SWNIT_SESB_Msk                  0x8UL
#define FLEXRAY_SWNIT_SBSB_Pos                  4UL
#define FLEXRAY_SWNIT_SBSB_Msk                  0x10UL
#define FLEXRAY_SWNIT_TCSB_Pos                  5UL
#define FLEXRAY_SWNIT_TCSB_Msk                  0x20UL
#define FLEXRAY_SWNIT_MTSA___Pos                6UL
#define FLEXRAY_SWNIT_MTSA___Msk                0x40UL
#define FLEXRAY_SWNIT_MTSB___Pos                7UL
#define FLEXRAY_SWNIT_MTSB___Msk                0x80UL
#define FLEXRAY_SWNIT_SENA_Pos                  8UL
#define FLEXRAY_SWNIT_SENA_Msk                  0x100UL
#define FLEXRAY_SWNIT_SBNA_Pos                  9UL
#define FLEXRAY_SWNIT_SBNA_Msk                  0x200UL
#define FLEXRAY_SWNIT_SENB_Pos                  10UL
#define FLEXRAY_SWNIT_SENB_Msk                  0x400UL
#define FLEXRAY_SWNIT_SBNB_Pos                  11UL
#define FLEXRAY_SWNIT_SBNB_Msk                  0x800UL
/* FLEXRAY.ACS */
#define FLEXRAY_ACS_VFRA__Pos                   0UL
#define FLEXRAY_ACS_VFRA__Msk                   0x1UL
#define FLEXRAY_ACS_SEDA_Pos                    1UL
#define FLEXRAY_ACS_SEDA_Msk                    0x2UL
#define FLEXRAY_ACS_CEDA_Pos                    2UL
#define FLEXRAY_ACS_CEDA_Msk                    0x4UL
#define FLEXRAY_ACS_CIA_Pos                     3UL
#define FLEXRAY_ACS_CIA_Msk                     0x8UL
#define FLEXRAY_ACS_SBVA_Pos                    4UL
#define FLEXRAY_ACS_SBVA_Msk                    0x10UL
#define FLEXRAY_ACS_VFRB__Pos                   8UL
#define FLEXRAY_ACS_VFRB__Msk                   0x100UL
#define FLEXRAY_ACS_SEDB_Pos                    9UL
#define FLEXRAY_ACS_SEDB_Msk                    0x200UL
#define FLEXRAY_ACS_CEDB_Pos                    10UL
#define FLEXRAY_ACS_CEDB_Msk                    0x400UL
#define FLEXRAY_ACS_CIB_Pos                     11UL
#define FLEXRAY_ACS_CIB_Msk                     0x800UL
#define FLEXRAY_ACS_SBVB_Pos                    12UL
#define FLEXRAY_ACS_SBVB_Msk                    0x1000UL
/* FLEXRAY.ESID */
#define FLEXRAY_ESID_EID_Pos                    0UL
#define FLEXRAY_ESID_EID_Msk                    0x3FFUL
#define FLEXRAY_ESID_RXEA_Pos                   14UL
#define FLEXRAY_ESID_RXEA_Msk                   0x4000UL
#define FLEXRAY_ESID_RXEB_Pos                   15UL
#define FLEXRAY_ESID_RXEB_Msk                   0x8000UL
/* FLEXRAY.OSID */
#define FLEXRAY_OSID_OID_Pos                    0UL
#define FLEXRAY_OSID_OID_Msk                    0x3FFUL
#define FLEXRAY_OSID_RXOA_Pos                   14UL
#define FLEXRAY_OSID_RXOA_Msk                   0x4000UL
#define FLEXRAY_OSID_RXOB_Pos                   15UL
#define FLEXRAY_OSID_RXOB_Msk                   0x8000UL
/* FLEXRAY.NMV1 */
#define FLEXRAY_NMV1_DATA0_Pos                  0UL
#define FLEXRAY_NMV1_DATA0_Msk                  0xFFUL
#define FLEXRAY_NMV1_DATA1_Pos                  8UL
#define FLEXRAY_NMV1_DATA1_Msk                  0xFF00UL
#define FLEXRAY_NMV1_DATA2_Pos                  16UL
#define FLEXRAY_NMV1_DATA2_Msk                  0xFF0000UL
#define FLEXRAY_NMV1_DATA3_Pos                  24UL
#define FLEXRAY_NMV1_DATA3_Msk                  0xFF000000UL
/* FLEXRAY.NMV2 */
#define FLEXRAY_NMV2_DATA4_Pos                  0UL
#define FLEXRAY_NMV2_DATA4_Msk                  0xFFUL
#define FLEXRAY_NMV2_DATA5_Pos                  8UL
#define FLEXRAY_NMV2_DATA5_Msk                  0xFF00UL
#define FLEXRAY_NMV2_DATA6_Pos                  16UL
#define FLEXRAY_NMV2_DATA6_Msk                  0xFF0000UL
#define FLEXRAY_NMV2_DATA7_Pos                  24UL
#define FLEXRAY_NMV2_DATA7_Msk                  0xFF000000UL
/* FLEXRAY.NMV3 */
#define FLEXRAY_NMV3_DATA8_Pos                  0UL
#define FLEXRAY_NMV3_DATA8_Msk                  0xFFUL
#define FLEXRAY_NMV3_DATA9_Pos                  8UL
#define FLEXRAY_NMV3_DATA9_Msk                  0xFF00UL
#define FLEXRAY_NMV3_DATA10_Pos                 16UL
#define FLEXRAY_NMV3_DATA10_Msk                 0xFF0000UL
#define FLEXRAY_NMV3_DATA11_Pos                 24UL
#define FLEXRAY_NMV3_DATA11_Msk                 0xFF000000UL
/* FLEXRAY.MRC */
#define FLEXRAY_MRC_FDB_Pos                     0UL
#define FLEXRAY_MRC_FDB_Msk                     0xFFUL
#define FLEXRAY_MRC_FFB_Pos                     8UL
#define FLEXRAY_MRC_FFB_Msk                     0xFF00UL
#define FLEXRAY_MRC_LCB_Pos                     16UL
#define FLEXRAY_MRC_LCB_Msk                     0xFF0000UL
#define FLEXRAY_MRC_SEC_Pos                     24UL
#define FLEXRAY_MRC_SEC_Msk                     0x3000000UL
#define FLEXRAY_MRC_SPLM_Pos                    26UL
#define FLEXRAY_MRC_SPLM_Msk                    0x4000000UL
/* FLEXRAY.FRF */
#define FLEXRAY_FRF_CH_Pos                      0UL
#define FLEXRAY_FRF_CH_Msk                      0x3UL
#define FLEXRAY_FRF_FID__Pos                    2UL
#define FLEXRAY_FRF_FID__Msk                    0x1FFCUL
#define FLEXRAY_FRF_CYF_Pos                     16UL
#define FLEXRAY_FRF_CYF_Msk                     0x7F0000UL
#define FLEXRAY_FRF_RSS_Pos                     23UL
#define FLEXRAY_FRF_RSS_Msk                     0x800000UL
#define FLEXRAY_FRF_RNF_Pos                     24UL
#define FLEXRAY_FRF_RNF_Msk                     0x1000000UL
/* FLEXRAY.FRFM */
#define FLEXRAY_FRFM_MFID_Pos                   2UL
#define FLEXRAY_FRFM_MFID_Msk                   0x1FFCUL
/* FLEXRAY.FCL */
#define FLEXRAY_FCL_CL_Pos                      0UL
#define FLEXRAY_FCL_CL_Msk                      0xFFUL
/* FLEXRAY.MHDS */
#define FLEXRAY_MHDS_PIBF_Pos                   0UL
#define FLEXRAY_MHDS_PIBF_Msk                   0x1UL
#define FLEXRAY_MHDS_POBF_Pos                   1UL
#define FLEXRAY_MHDS_POBF_Msk                   0x2UL
#define FLEXRAY_MHDS_PMR_Pos                    2UL
#define FLEXRAY_MHDS_PMR_Msk                    0x4UL
#define FLEXRAY_MHDS_PTBF1_Pos                  3UL
#define FLEXRAY_MHDS_PTBF1_Msk                  0x8UL
#define FLEXRAY_MHDS_PTBF2_Pos                  4UL
#define FLEXRAY_MHDS_PTBF2_Msk                  0x10UL
#define FLEXRAY_MHDS_FMBD_Pos                   5UL
#define FLEXRAY_MHDS_FMBD_Msk                   0x20UL
#define FLEXRAY_MHDS_MFMB_Pos                   6UL
#define FLEXRAY_MHDS_MFMB_Msk                   0x40UL
#define FLEXRAY_MHDS_CRAM_Pos                   7UL
#define FLEXRAY_MHDS_CRAM_Msk                   0x80UL
#define FLEXRAY_MHDS_FMB_Pos                    8UL
#define FLEXRAY_MHDS_FMB_Msk                    0x7F00UL
#define FLEXRAY_MHDS_MBT_Pos                    16UL
#define FLEXRAY_MHDS_MBT_Msk                    0x7F0000UL
#define FLEXRAY_MHDS_MBU_Pos                    24UL
#define FLEXRAY_MHDS_MBU_Msk                    0x7F000000UL
/* FLEXRAY.LDTS */
#define FLEXRAY_LDTS_LDTA_Pos                   0UL
#define FLEXRAY_LDTS_LDTA_Msk                   0x7FFUL
#define FLEXRAY_LDTS_LDTB_Pos                   16UL
#define FLEXRAY_LDTS_LDTB_Msk                   0x7FF0000UL
/* FLEXRAY.FSR */
#define FLEXRAY_FSR_RFNE__Pos                   0UL
#define FLEXRAY_FSR_RFNE__Msk                   0x1UL
#define FLEXRAY_FSR_RFCL__Pos                   1UL
#define FLEXRAY_FSR_RFCL__Msk                   0x2UL
#define FLEXRAY_FSR_RFO__Pos                    2UL
#define FLEXRAY_FSR_RFO__Msk                    0x4UL
#define FLEXRAY_FSR_RFFL_Pos                    8UL
#define FLEXRAY_FSR_RFFL_Msk                    0xFF00UL
/* FLEXRAY.MHDF */
#define FLEXRAY_MHDF_SNUA_Pos                   0UL
#define FLEXRAY_MHDF_SNUA_Msk                   0x1UL
#define FLEXRAY_MHDF_SNUB_Pos                   1UL
#define FLEXRAY_MHDF_SNUB_Msk                   0x2UL
#define FLEXRAY_MHDF_FNFA_Pos                   2UL
#define FLEXRAY_MHDF_FNFA_Msk                   0x4UL
#define FLEXRAY_MHDF_FNFB_Pos                   3UL
#define FLEXRAY_MHDF_FNFB_Msk                   0x8UL
#define FLEXRAY_MHDF_TBFA_Pos                   4UL
#define FLEXRAY_MHDF_TBFA_Msk                   0x10UL
#define FLEXRAY_MHDF_TBFB_Pos                   5UL
#define FLEXRAY_MHDF_TBFB_Msk                   0x20UL
#define FLEXRAY_MHDF_TNSA_Pos                   6UL
#define FLEXRAY_MHDF_TNSA_Msk                   0x40UL
#define FLEXRAY_MHDF_TNSB_Pos                   7UL
#define FLEXRAY_MHDF_TNSB_Msk                   0x80UL
#define FLEXRAY_MHDF_WAHP_Pos                   8UL
#define FLEXRAY_MHDF_WAHP_Msk                   0x100UL
/* FLEXRAY.TXRQ1 */
#define FLEXRAY_TXRQ1_TXR_Pos                   0UL
#define FLEXRAY_TXRQ1_TXR_Msk                   0xFFFFFFFFUL
/* FLEXRAY.TXRQ2 */
#define FLEXRAY_TXRQ2_TXR_Pos                   0UL
#define FLEXRAY_TXRQ2_TXR_Msk                   0xFFFFFFFFUL
/* FLEXRAY.TXRQ3 */
#define FLEXRAY_TXRQ3_TXR_Pos                   0UL
#define FLEXRAY_TXRQ3_TXR_Msk                   0xFFFFFFFFUL
/* FLEXRAY.TXRQ4 */
#define FLEXRAY_TXRQ4_TXR_Pos                   0UL
#define FLEXRAY_TXRQ4_TXR_Msk                   0xFFFFFFFFUL
/* FLEXRAY.NDAT1 */
#define FLEXRAY_NDAT1_ND_Pos                    0UL
#define FLEXRAY_NDAT1_ND_Msk                    0xFFFFFFFFUL
/* FLEXRAY.NDAT2 */
#define FLEXRAY_NDAT2_ND_Pos                    0UL
#define FLEXRAY_NDAT2_ND_Msk                    0xFFFFFFFFUL
/* FLEXRAY.NDAT3 */
#define FLEXRAY_NDAT3_ND_Pos                    0UL
#define FLEXRAY_NDAT3_ND_Msk                    0xFFFFFFFFUL
/* FLEXRAY.NDAT4 */
#define FLEXRAY_NDAT4_ND_Pos                    0UL
#define FLEXRAY_NDAT4_ND_Msk                    0xFFFFFFFFUL
/* FLEXRAY.MBSC1 */
#define FLEXRAY_MBSC1_MBC_Pos                   0UL
#define FLEXRAY_MBSC1_MBC_Msk                   0xFFFFFFFFUL
/* FLEXRAY.MBSC2 */
#define FLEXRAY_MBSC2_MBC_Pos                   0UL
#define FLEXRAY_MBSC2_MBC_Msk                   0xFFFFFFFFUL
/* FLEXRAY.MBSC3 */
#define FLEXRAY_MBSC3_MBC_Pos                   0UL
#define FLEXRAY_MBSC3_MBC_Msk                   0xFFFFFFFFUL
/* FLEXRAY.MBSC4 */
#define FLEXRAY_MBSC4_MBC_Pos                   0UL
#define FLEXRAY_MBSC4_MBC_Msk                   0xFFFFFFFFUL
/* FLEXRAY.CREL */
#define FLEXRAY_CREL_DAY_Pos                    0UL
#define FLEXRAY_CREL_DAY_Msk                    0xFFUL
#define FLEXRAY_CREL_MON_Pos                    8UL
#define FLEXRAY_CREL_MON_Msk                    0xFF00UL
#define FLEXRAY_CREL_YEAR_Pos                   16UL
#define FLEXRAY_CREL_YEAR_Msk                   0xF0000UL
#define FLEXRAY_CREL_STEP_Pos                   20UL
#define FLEXRAY_CREL_STEP_Msk                   0xFF00000UL
#define FLEXRAY_CREL_REL_Pos                    28UL
#define FLEXRAY_CREL_REL_Msk                    0xF0000000UL
/* FLEXRAY.ENDN */
#define FLEXRAY_ENDN_ETV_Pos                    0UL
#define FLEXRAY_ENDN_ETV_Msk                    0xFFFFFFFFUL
/* FLEXRAY.WRDS */
#define FLEXRAY_WRDS_MD_Pos                     0UL
#define FLEXRAY_WRDS_MD_Msk                     0xFFFFFFFFUL
/* FLEXRAY.WRHS1 */
#define FLEXRAY_WRHS1_FID_Pos                   0UL
#define FLEXRAY_WRHS1_FID_Msk                   0x7FFUL
#define FLEXRAY_WRHS1_CYC_Pos                   16UL
#define FLEXRAY_WRHS1_CYC_Msk                   0x7F0000UL
#define FLEXRAY_WRHS1_CHA_Pos                   24UL
#define FLEXRAY_WRHS1_CHA_Msk                   0x1000000UL
#define FLEXRAY_WRHS1_CHB_Pos                   25UL
#define FLEXRAY_WRHS1_CHB_Msk                   0x2000000UL
#define FLEXRAY_WRHS1_CFG_Pos                   26UL
#define FLEXRAY_WRHS1_CFG_Msk                   0x4000000UL
#define FLEXRAY_WRHS1_PPIT_Pos                  27UL
#define FLEXRAY_WRHS1_PPIT_Msk                  0x8000000UL
#define FLEXRAY_WRHS1_TXM_Pos                   28UL
#define FLEXRAY_WRHS1_TXM_Msk                   0x10000000UL
#define FLEXRAY_WRHS1_MBI_Pos                   29UL
#define FLEXRAY_WRHS1_MBI_Msk                   0x20000000UL
/* FLEXRAY.WRHS2 */
#define FLEXRAY_WRHS2_CRC_Pos                   0UL
#define FLEXRAY_WRHS2_CRC_Msk                   0x7FFUL
#define FLEXRAY_WRHS2_PLC_Pos                   16UL
#define FLEXRAY_WRHS2_PLC_Msk                   0x7F0000UL
/* FLEXRAY.WRHS3 */
#define FLEXRAY_WRHS3_DP_Pos                    0UL
#define FLEXRAY_WRHS3_DP_Msk                    0x7FFUL
/* FLEXRAY.IBCM */
#define FLEXRAY_IBCM_LHSH_Pos                   0UL
#define FLEXRAY_IBCM_LHSH_Msk                   0x1UL
#define FLEXRAY_IBCM_LDSH_Pos                   1UL
#define FLEXRAY_IBCM_LDSH_Msk                   0x2UL
#define FLEXRAY_IBCM_STXRH_Pos                  2UL
#define FLEXRAY_IBCM_STXRH_Msk                  0x4UL
#define FLEXRAY_IBCM_LHSS_Pos                   16UL
#define FLEXRAY_IBCM_LHSS_Msk                   0x10000UL
#define FLEXRAY_IBCM_LDSS_Pos                   17UL
#define FLEXRAY_IBCM_LDSS_Msk                   0x20000UL
#define FLEXRAY_IBCM_STXRS_Pos                  18UL
#define FLEXRAY_IBCM_STXRS_Msk                  0x40000UL
/* FLEXRAY.IBCR */
#define FLEXRAY_IBCR_IBRH_Pos                   0UL
#define FLEXRAY_IBCR_IBRH_Msk                   0x7FUL
#define FLEXRAY_IBCR_IBSYH_Pos                  15UL
#define FLEXRAY_IBCR_IBSYH_Msk                  0x8000UL
#define FLEXRAY_IBCR_IBRS_Pos                   16UL
#define FLEXRAY_IBCR_IBRS_Msk                   0x7F0000UL
#define FLEXRAY_IBCR_IBSYS_Pos                  31UL
#define FLEXRAY_IBCR_IBSYS_Msk                  0x80000000UL
/* FLEXRAY.RDDS */
#define FLEXRAY_RDDS_MD_Pos                     0UL
#define FLEXRAY_RDDS_MD_Msk                     0xFFFFFFFFUL
/* FLEXRAY.RDHS1 */
#define FLEXRAY_RDHS1_FID_Pos                   0UL
#define FLEXRAY_RDHS1_FID_Msk                   0x7FFUL
#define FLEXRAY_RDHS1_CYC_Pos                   16UL
#define FLEXRAY_RDHS1_CYC_Msk                   0x7F0000UL
#define FLEXRAY_RDHS1_CHA_Pos                   24UL
#define FLEXRAY_RDHS1_CHA_Msk                   0x1000000UL
#define FLEXRAY_RDHS1_CHB_Pos                   25UL
#define FLEXRAY_RDHS1_CHB_Msk                   0x2000000UL
#define FLEXRAY_RDHS1_CFG_Pos                   26UL
#define FLEXRAY_RDHS1_CFG_Msk                   0x4000000UL
#define FLEXRAY_RDHS1_PPIT_Pos                  27UL
#define FLEXRAY_RDHS1_PPIT_Msk                  0x8000000UL
#define FLEXRAY_RDHS1_TXM_Pos                   28UL
#define FLEXRAY_RDHS1_TXM_Msk                   0x10000000UL
#define FLEXRAY_RDHS1_MBI_Pos                   29UL
#define FLEXRAY_RDHS1_MBI_Msk                   0x20000000UL
/* FLEXRAY.RDHS2 */
#define FLEXRAY_RDHS2_CRC_Pos                   0UL
#define FLEXRAY_RDHS2_CRC_Msk                   0x7FFUL
#define FLEXRAY_RDHS2_PLC_Pos                   16UL
#define FLEXRAY_RDHS2_PLC_Msk                   0x7F0000UL
#define FLEXRAY_RDHS2_PLR_Pos                   24UL
#define FLEXRAY_RDHS2_PLR_Msk                   0x7F000000UL
/* FLEXRAY.RDHS3 */
#define FLEXRAY_RDHS3_DP_Pos                    0UL
#define FLEXRAY_RDHS3_DP_Msk                    0x7FFUL
#define FLEXRAY_RDHS3_RCC_Pos                   16UL
#define FLEXRAY_RDHS3_RCC_Msk                   0x3F0000UL
#define FLEXRAY_RDHS3_RCI_Pos                   24UL
#define FLEXRAY_RDHS3_RCI_Msk                   0x1000000UL
#define FLEXRAY_RDHS3_SFI_Pos                   25UL
#define FLEXRAY_RDHS3_SFI_Msk                   0x2000000UL
#define FLEXRAY_RDHS3_SYN_Pos                   26UL
#define FLEXRAY_RDHS3_SYN_Msk                   0x4000000UL
#define FLEXRAY_RDHS3_NFI_Pos                   27UL
#define FLEXRAY_RDHS3_NFI_Msk                   0x8000000UL
#define FLEXRAY_RDHS3_PPI_Pos                   28UL
#define FLEXRAY_RDHS3_PPI_Msk                   0x10000000UL
#define FLEXRAY_RDHS3_RES_Pos                   29UL
#define FLEXRAY_RDHS3_RES_Msk                   0x20000000UL
/* FLEXRAY.MBS */
#define FLEXRAY_MBS_VFRA_Pos                    0UL
#define FLEXRAY_MBS_VFRA_Msk                    0x1UL
#define FLEXRAY_MBS_VFRB_Pos                    1UL
#define FLEXRAY_MBS_VFRB_Msk                    0x2UL
#define FLEXRAY_MBS_SEOA_Pos                    2UL
#define FLEXRAY_MBS_SEOA_Msk                    0x4UL
#define FLEXRAY_MBS_SEOB_Pos                    3UL
#define FLEXRAY_MBS_SEOB_Msk                    0x8UL
#define FLEXRAY_MBS_CEOA_Pos                    4UL
#define FLEXRAY_MBS_CEOA_Msk                    0x10UL
#define FLEXRAY_MBS_CEOB_Pos                    5UL
#define FLEXRAY_MBS_CEOB_Msk                    0x20UL
#define FLEXRAY_MBS_SVOA_Pos                    6UL
#define FLEXRAY_MBS_SVOA_Msk                    0x40UL
#define FLEXRAY_MBS_SVOB_Pos                    7UL
#define FLEXRAY_MBS_SVOB_Msk                    0x80UL
#define FLEXRAY_MBS_TCIA_Pos                    8UL
#define FLEXRAY_MBS_TCIA_Msk                    0x100UL
#define FLEXRAY_MBS_TCIB_Pos                    9UL
#define FLEXRAY_MBS_TCIB_Msk                    0x200UL
#define FLEXRAY_MBS_ESA_Pos                     10UL
#define FLEXRAY_MBS_ESA_Msk                     0x400UL
#define FLEXRAY_MBS_ESB_Pos                     11UL
#define FLEXRAY_MBS_ESB_Msk                     0x800UL
#define FLEXRAY_MBS_MLST_Pos                    12UL
#define FLEXRAY_MBS_MLST_Msk                    0x1000UL
#define FLEXRAY_MBS_FTA_Pos                     14UL
#define FLEXRAY_MBS_FTA_Msk                     0x4000UL
#define FLEXRAY_MBS_FTB_Pos                     15UL
#define FLEXRAY_MBS_FTB_Msk                     0x8000UL
#define FLEXRAY_MBS_CCS_Pos                     16UL
#define FLEXRAY_MBS_CCS_Msk                     0x3F0000UL
#define FLEXRAY_MBS_RCIS_Pos                    24UL
#define FLEXRAY_MBS_RCIS_Msk                    0x1000000UL
#define FLEXRAY_MBS_SFIS_Pos                    25UL
#define FLEXRAY_MBS_SFIS_Msk                    0x2000000UL
#define FLEXRAY_MBS_SYNS_Pos                    26UL
#define FLEXRAY_MBS_SYNS_Msk                    0x4000000UL
#define FLEXRAY_MBS_NFIS_Pos                    27UL
#define FLEXRAY_MBS_NFIS_Msk                    0x8000000UL
#define FLEXRAY_MBS_PPIS_Pos                    28UL
#define FLEXRAY_MBS_PPIS_Msk                    0x10000000UL
#define FLEXRAY_MBS_RESS_Pos                    29UL
#define FLEXRAY_MBS_RESS_Msk                    0x20000000UL
/* FLEXRAY.OBCM */
#define FLEXRAY_OBCM_RHSS_Pos                   0UL
#define FLEXRAY_OBCM_RHSS_Msk                   0x1UL
#define FLEXRAY_OBCM_RDSS_Pos                   1UL
#define FLEXRAY_OBCM_RDSS_Msk                   0x2UL
#define FLEXRAY_OBCM_RHSH_Pos                   16UL
#define FLEXRAY_OBCM_RHSH_Msk                   0x10000UL
#define FLEXRAY_OBCM_RDSH_Pos                   17UL
#define FLEXRAY_OBCM_RDSH_Msk                   0x20000UL
/* FLEXRAY.OBCR */
#define FLEXRAY_OBCR_OBRS_Pos                   0UL
#define FLEXRAY_OBCR_OBRS_Msk                   0x7FUL
#define FLEXRAY_OBCR_VIEW_Pos                   8UL
#define FLEXRAY_OBCR_VIEW_Msk                   0x100UL
#define FLEXRAY_OBCR_REQ_Pos                    9UL
#define FLEXRAY_OBCR_REQ_Msk                    0x200UL
#define FLEXRAY_OBCR_OBSYS_Pos                  15UL
#define FLEXRAY_OBCR_OBSYS_Msk                  0x8000UL
#define FLEXRAY_OBCR_OBRH_Pos                   16UL
#define FLEXRAY_OBCR_OBRH_Msk                   0x7F0000UL
/* FLEXRAY.WRHS1_MIR2 */
#define FLEXRAY_WRHS1_MIR2_FID_Pos              0UL
#define FLEXRAY_WRHS1_MIR2_FID_Msk              0x7FFUL
#define FLEXRAY_WRHS1_MIR2_CYC_Pos              16UL
#define FLEXRAY_WRHS1_MIR2_CYC_Msk              0x7F0000UL
#define FLEXRAY_WRHS1_MIR2_CHA_Pos              24UL
#define FLEXRAY_WRHS1_MIR2_CHA_Msk              0x1000000UL
#define FLEXRAY_WRHS1_MIR2_CHB_Pos              25UL
#define FLEXRAY_WRHS1_MIR2_CHB_Msk              0x2000000UL
#define FLEXRAY_WRHS1_MIR2_CFG_Pos              26UL
#define FLEXRAY_WRHS1_MIR2_CFG_Msk              0x4000000UL
#define FLEXRAY_WRHS1_MIR2_PPIT_Pos             27UL
#define FLEXRAY_WRHS1_MIR2_PPIT_Msk             0x8000000UL
#define FLEXRAY_WRHS1_MIR2_TXM_Pos              28UL
#define FLEXRAY_WRHS1_MIR2_TXM_Msk              0x10000000UL
#define FLEXRAY_WRHS1_MIR2_MBI_Pos              29UL
#define FLEXRAY_WRHS1_MIR2_MBI_Msk              0x20000000UL
/* FLEXRAY.WRHS2_MIR2 */
#define FLEXRAY_WRHS2_MIR2_CRC_Pos              0UL
#define FLEXRAY_WRHS2_MIR2_CRC_Msk              0x7FFUL
#define FLEXRAY_WRHS2_MIR2_PLC_Pos              16UL
#define FLEXRAY_WRHS2_MIR2_PLC_Msk              0x7F0000UL
/* FLEXRAY.WRHS3_MIR2 */
#define FLEXRAY_WRHS3_MIR2_DP_Pos               0UL
#define FLEXRAY_WRHS3_MIR2_DP_Msk               0x7FFUL
/* FLEXRAY.WRDS_MIR */
#define FLEXRAY_WRDS_MIR_MD_Pos                 0UL
#define FLEXRAY_WRDS_MIR_MD_Msk                 0xFFFFFFFFUL
/* FLEXRAY.WRHS1_MIR */
#define FLEXRAY_WRHS1_MIR_FID_Pos               0UL
#define FLEXRAY_WRHS1_MIR_FID_Msk               0x7FFUL
#define FLEXRAY_WRHS1_MIR_CYC_Pos               16UL
#define FLEXRAY_WRHS1_MIR_CYC_Msk               0x7F0000UL
#define FLEXRAY_WRHS1_MIR_CHA_Pos               24UL
#define FLEXRAY_WRHS1_MIR_CHA_Msk               0x1000000UL
#define FLEXRAY_WRHS1_MIR_CHB_Pos               25UL
#define FLEXRAY_WRHS1_MIR_CHB_Msk               0x2000000UL
#define FLEXRAY_WRHS1_MIR_CFG_Pos               26UL
#define FLEXRAY_WRHS1_MIR_CFG_Msk               0x4000000UL
#define FLEXRAY_WRHS1_MIR_PPIT_Pos              27UL
#define FLEXRAY_WRHS1_MIR_PPIT_Msk              0x8000000UL
#define FLEXRAY_WRHS1_MIR_TXM_Pos               28UL
#define FLEXRAY_WRHS1_MIR_TXM_Msk               0x10000000UL
#define FLEXRAY_WRHS1_MIR_MBI_Pos               29UL
#define FLEXRAY_WRHS1_MIR_MBI_Msk               0x20000000UL
/* FLEXRAY.WRHS2_MIR */
#define FLEXRAY_WRHS2_MIR_CRC_Pos               0UL
#define FLEXRAY_WRHS2_MIR_CRC_Msk               0x7FFUL
#define FLEXRAY_WRHS2_MIR_PLC_Pos               16UL
#define FLEXRAY_WRHS2_MIR_PLC_Msk               0x7F0000UL
/* FLEXRAY.WRHS3_MIR */
#define FLEXRAY_WRHS3_MIR_DP_Pos                0UL
#define FLEXRAY_WRHS3_MIR_DP_Msk                0x7FFUL
/* FLEXRAY.IBCM_MIR */
#define FLEXRAY_IBCM_MIR_LHSH_Pos               0UL
#define FLEXRAY_IBCM_MIR_LHSH_Msk               0x1UL
#define FLEXRAY_IBCM_MIR_LDSH_Pos               1UL
#define FLEXRAY_IBCM_MIR_LDSH_Msk               0x2UL
#define FLEXRAY_IBCM_MIR_STXRH_Pos              2UL
#define FLEXRAY_IBCM_MIR_STXRH_Msk              0x4UL
#define FLEXRAY_IBCM_MIR_LHSS_Pos               16UL
#define FLEXRAY_IBCM_MIR_LHSS_Msk               0x10000UL
#define FLEXRAY_IBCM_MIR_LDSS_Pos               17UL
#define FLEXRAY_IBCM_MIR_LDSS_Msk               0x20000UL
#define FLEXRAY_IBCM_MIR_STXRS_Pos              18UL
#define FLEXRAY_IBCM_MIR_STXRS_Msk              0x40000UL
/* FLEXRAY.IBCR_MIR */
#define FLEXRAY_IBCR_MIR_IBRH_Pos               0UL
#define FLEXRAY_IBCR_MIR_IBRH_Msk               0x7FUL
#define FLEXRAY_IBCR_MIR_IBSYH_Pos              15UL
#define FLEXRAY_IBCR_MIR_IBSYH_Msk              0x8000UL
#define FLEXRAY_IBCR_MIR_IBRS_Pos               16UL
#define FLEXRAY_IBCR_MIR_IBRS_Msk               0x7F0000UL
#define FLEXRAY_IBCR_MIR_IBSYS_Pos              31UL
#define FLEXRAY_IBCR_MIR_IBSYS_Msk              0x80000000UL
/* FLEXRAY.RDHS1_MIR2 */
#define FLEXRAY_RDHS1_MIR2_FID_Pos              0UL
#define FLEXRAY_RDHS1_MIR2_FID_Msk              0x7FFUL
#define FLEXRAY_RDHS1_MIR2_CYC_Pos              16UL
#define FLEXRAY_RDHS1_MIR2_CYC_Msk              0x7F0000UL
#define FLEXRAY_RDHS1_MIR2_CHA_Pos              24UL
#define FLEXRAY_RDHS1_MIR2_CHA_Msk              0x1000000UL
#define FLEXRAY_RDHS1_MIR2_CHB_Pos              25UL
#define FLEXRAY_RDHS1_MIR2_CHB_Msk              0x2000000UL
#define FLEXRAY_RDHS1_MIR2_CFG_Pos              26UL
#define FLEXRAY_RDHS1_MIR2_CFG_Msk              0x4000000UL
#define FLEXRAY_RDHS1_MIR2_PPIT_Pos             27UL
#define FLEXRAY_RDHS1_MIR2_PPIT_Msk             0x8000000UL
#define FLEXRAY_RDHS1_MIR2_TXM_Pos              28UL
#define FLEXRAY_RDHS1_MIR2_TXM_Msk              0x10000000UL
#define FLEXRAY_RDHS1_MIR2_MBI_Pos              29UL
#define FLEXRAY_RDHS1_MIR2_MBI_Msk              0x20000000UL
/* FLEXRAY.RDHS2_MIR2 */
#define FLEXRAY_RDHS2_MIR2_CRC_Pos              0UL
#define FLEXRAY_RDHS2_MIR2_CRC_Msk              0x7FFUL
#define FLEXRAY_RDHS2_MIR2_PLC_Pos              16UL
#define FLEXRAY_RDHS2_MIR2_PLC_Msk              0x7F0000UL
#define FLEXRAY_RDHS2_MIR2_PLR_Pos              24UL
#define FLEXRAY_RDHS2_MIR2_PLR_Msk              0x7F000000UL
/* FLEXRAY.RDHS3_MIR2 */
#define FLEXRAY_RDHS3_MIR2_DP_Pos               0UL
#define FLEXRAY_RDHS3_MIR2_DP_Msk               0x7FFUL
#define FLEXRAY_RDHS3_MIR2_RCC_Pos              16UL
#define FLEXRAY_RDHS3_MIR2_RCC_Msk              0x3F0000UL
#define FLEXRAY_RDHS3_MIR2_RCI_Pos              24UL
#define FLEXRAY_RDHS3_MIR2_RCI_Msk              0x1000000UL
#define FLEXRAY_RDHS3_MIR2_SFI_Pos              25UL
#define FLEXRAY_RDHS3_MIR2_SFI_Msk              0x2000000UL
#define FLEXRAY_RDHS3_MIR2_SYN_Pos              26UL
#define FLEXRAY_RDHS3_MIR2_SYN_Msk              0x4000000UL
#define FLEXRAY_RDHS3_MIR2_NFI_Pos              27UL
#define FLEXRAY_RDHS3_MIR2_NFI_Msk              0x8000000UL
#define FLEXRAY_RDHS3_MIR2_PPI_Pos              28UL
#define FLEXRAY_RDHS3_MIR2_PPI_Msk              0x10000000UL
#define FLEXRAY_RDHS3_MIR2_RES_Pos              29UL
#define FLEXRAY_RDHS3_MIR2_RES_Msk              0x20000000UL
/* FLEXRAY.MBS_MIR2 */
#define FLEXRAY_MBS_MIR2_VFRA_Pos               0UL
#define FLEXRAY_MBS_MIR2_VFRA_Msk               0x1UL
#define FLEXRAY_MBS_MIR2_VFRB_Pos               1UL
#define FLEXRAY_MBS_MIR2_VFRB_Msk               0x2UL
#define FLEXRAY_MBS_MIR2_SEOA_Pos               2UL
#define FLEXRAY_MBS_MIR2_SEOA_Msk               0x4UL
#define FLEXRAY_MBS_MIR2_SEOB_Pos               3UL
#define FLEXRAY_MBS_MIR2_SEOB_Msk               0x8UL
#define FLEXRAY_MBS_MIR2_CEOA_Pos               4UL
#define FLEXRAY_MBS_MIR2_CEOA_Msk               0x10UL
#define FLEXRAY_MBS_MIR2_CEOB_Pos               5UL
#define FLEXRAY_MBS_MIR2_CEOB_Msk               0x20UL
#define FLEXRAY_MBS_MIR2_SVOA_Pos               6UL
#define FLEXRAY_MBS_MIR2_SVOA_Msk               0x40UL
#define FLEXRAY_MBS_MIR2_SVOB_Pos               7UL
#define FLEXRAY_MBS_MIR2_SVOB_Msk               0x80UL
#define FLEXRAY_MBS_MIR2_TCIA_Pos               8UL
#define FLEXRAY_MBS_MIR2_TCIA_Msk               0x100UL
#define FLEXRAY_MBS_MIR2_TCIB_Pos               9UL
#define FLEXRAY_MBS_MIR2_TCIB_Msk               0x200UL
#define FLEXRAY_MBS_MIR2_ESA_Pos                10UL
#define FLEXRAY_MBS_MIR2_ESA_Msk                0x400UL
#define FLEXRAY_MBS_MIR2_ESB_Pos                11UL
#define FLEXRAY_MBS_MIR2_ESB_Msk                0x800UL
#define FLEXRAY_MBS_MIR2_MLST_Pos               12UL
#define FLEXRAY_MBS_MIR2_MLST_Msk               0x1000UL
#define FLEXRAY_MBS_MIR2_FTA_Pos                14UL
#define FLEXRAY_MBS_MIR2_FTA_Msk                0x4000UL
#define FLEXRAY_MBS_MIR2_FTB_Pos                15UL
#define FLEXRAY_MBS_MIR2_FTB_Msk                0x8000UL
#define FLEXRAY_MBS_MIR2_CCS_Pos                16UL
#define FLEXRAY_MBS_MIR2_CCS_Msk                0x3F0000UL
#define FLEXRAY_MBS_MIR2_RCIS_Pos               24UL
#define FLEXRAY_MBS_MIR2_RCIS_Msk               0x1000000UL
#define FLEXRAY_MBS_MIR2_SFIS_Pos               25UL
#define FLEXRAY_MBS_MIR2_SFIS_Msk               0x2000000UL
#define FLEXRAY_MBS_MIR2_SYNS_Pos               26UL
#define FLEXRAY_MBS_MIR2_SYNS_Msk               0x4000000UL
#define FLEXRAY_MBS_MIR2_NFIS_Pos               27UL
#define FLEXRAY_MBS_MIR2_NFIS_Msk               0x8000000UL
#define FLEXRAY_MBS_MIR2_PPIS_Pos               28UL
#define FLEXRAY_MBS_MIR2_PPIS_Msk               0x10000000UL
#define FLEXRAY_MBS_MIR2_RESS_Pos               29UL
#define FLEXRAY_MBS_MIR2_RESS_Msk               0x20000000UL
/* FLEXRAY.RDDS_MIR */
#define FLEXRAY_RDDS_MIR_MD_Pos                 0UL
#define FLEXRAY_RDDS_MIR_MD_Msk                 0xFFFFFFFFUL
/* FLEXRAY.RDHS1_MIR */
#define FLEXRAY_RDHS1_MIR_FID_Pos               0UL
#define FLEXRAY_RDHS1_MIR_FID_Msk               0x7FFUL
#define FLEXRAY_RDHS1_MIR_CYC_Pos               16UL
#define FLEXRAY_RDHS1_MIR_CYC_Msk               0x7F0000UL
#define FLEXRAY_RDHS1_MIR_CHA_Pos               24UL
#define FLEXRAY_RDHS1_MIR_CHA_Msk               0x1000000UL
#define FLEXRAY_RDHS1_MIR_CHB_Pos               25UL
#define FLEXRAY_RDHS1_MIR_CHB_Msk               0x2000000UL
#define FLEXRAY_RDHS1_MIR_CFG_Pos               26UL
#define FLEXRAY_RDHS1_MIR_CFG_Msk               0x4000000UL
#define FLEXRAY_RDHS1_MIR_PPIT_Pos              27UL
#define FLEXRAY_RDHS1_MIR_PPIT_Msk              0x8000000UL
#define FLEXRAY_RDHS1_MIR_TXM_Pos               28UL
#define FLEXRAY_RDHS1_MIR_TXM_Msk               0x10000000UL
#define FLEXRAY_RDHS1_MIR_MBI_Pos               29UL
#define FLEXRAY_RDHS1_MIR_MBI_Msk               0x20000000UL
/* FLEXRAY.RDHS2_MIR */
#define FLEXRAY_RDHS2_MIR_CRC_Pos               0UL
#define FLEXRAY_RDHS2_MIR_CRC_Msk               0x7FFUL
#define FLEXRAY_RDHS2_MIR_PLC_Pos               16UL
#define FLEXRAY_RDHS2_MIR_PLC_Msk               0x7F0000UL
#define FLEXRAY_RDHS2_MIR_PLR_Pos               24UL
#define FLEXRAY_RDHS2_MIR_PLR_Msk               0x7F000000UL
/* FLEXRAY.RDHS3_MIR */
#define FLEXRAY_RDHS3_MIR_DP_Pos                0UL
#define FLEXRAY_RDHS3_MIR_DP_Msk                0x7FFUL
#define FLEXRAY_RDHS3_MIR_RCC_Pos               16UL
#define FLEXRAY_RDHS3_MIR_RCC_Msk               0x3F0000UL
#define FLEXRAY_RDHS3_MIR_RCI_Pos               24UL
#define FLEXRAY_RDHS3_MIR_RCI_Msk               0x1000000UL
#define FLEXRAY_RDHS3_MIR_SFI_Pos               25UL
#define FLEXRAY_RDHS3_MIR_SFI_Msk               0x2000000UL
#define FLEXRAY_RDHS3_MIR_SYN_Pos               26UL
#define FLEXRAY_RDHS3_MIR_SYN_Msk               0x4000000UL
#define FLEXRAY_RDHS3_MIR_NFI_Pos               27UL
#define FLEXRAY_RDHS3_MIR_NFI_Msk               0x8000000UL
#define FLEXRAY_RDHS3_MIR_PPI_Pos               28UL
#define FLEXRAY_RDHS3_MIR_PPI_Msk               0x10000000UL
#define FLEXRAY_RDHS3_MIR_RES_Pos               29UL
#define FLEXRAY_RDHS3_MIR_RES_Msk               0x20000000UL
/* FLEXRAY.MBS_MIR */
#define FLEXRAY_MBS_MIR_VFRA_Pos                0UL
#define FLEXRAY_MBS_MIR_VFRA_Msk                0x1UL
#define FLEXRAY_MBS_MIR_VFRB_Pos                1UL
#define FLEXRAY_MBS_MIR_VFRB_Msk                0x2UL
#define FLEXRAY_MBS_MIR_SEOA_Pos                2UL
#define FLEXRAY_MBS_MIR_SEOA_Msk                0x4UL
#define FLEXRAY_MBS_MIR_SEOB_Pos                3UL
#define FLEXRAY_MBS_MIR_SEOB_Msk                0x8UL
#define FLEXRAY_MBS_MIR_CEOA_Pos                4UL
#define FLEXRAY_MBS_MIR_CEOA_Msk                0x10UL
#define FLEXRAY_MBS_MIR_CEOB_Pos                5UL
#define FLEXRAY_MBS_MIR_CEOB_Msk                0x20UL
#define FLEXRAY_MBS_MIR_SVOA_Pos                6UL
#define FLEXRAY_MBS_MIR_SVOA_Msk                0x40UL
#define FLEXRAY_MBS_MIR_SVOB_Pos                7UL
#define FLEXRAY_MBS_MIR_SVOB_Msk                0x80UL
#define FLEXRAY_MBS_MIR_TCIA_Pos                8UL
#define FLEXRAY_MBS_MIR_TCIA_Msk                0x100UL
#define FLEXRAY_MBS_MIR_TCIB_Pos                9UL
#define FLEXRAY_MBS_MIR_TCIB_Msk                0x200UL
#define FLEXRAY_MBS_MIR_ESA_Pos                 10UL
#define FLEXRAY_MBS_MIR_ESA_Msk                 0x400UL
#define FLEXRAY_MBS_MIR_ESB_Pos                 11UL
#define FLEXRAY_MBS_MIR_ESB_Msk                 0x800UL
#define FLEXRAY_MBS_MIR_MLST_Pos                12UL
#define FLEXRAY_MBS_MIR_MLST_Msk                0x1000UL
#define FLEXRAY_MBS_MIR_FTA_Pos                 14UL
#define FLEXRAY_MBS_MIR_FTA_Msk                 0x4000UL
#define FLEXRAY_MBS_MIR_FTB_Pos                 15UL
#define FLEXRAY_MBS_MIR_FTB_Msk                 0x8000UL
#define FLEXRAY_MBS_MIR_CCS_Pos                 16UL
#define FLEXRAY_MBS_MIR_CCS_Msk                 0x3F0000UL
#define FLEXRAY_MBS_MIR_RCIS_Pos                24UL
#define FLEXRAY_MBS_MIR_RCIS_Msk                0x1000000UL
#define FLEXRAY_MBS_MIR_SFIS_Pos                25UL
#define FLEXRAY_MBS_MIR_SFIS_Msk                0x2000000UL
#define FLEXRAY_MBS_MIR_SYNS_Pos                26UL
#define FLEXRAY_MBS_MIR_SYNS_Msk                0x4000000UL
#define FLEXRAY_MBS_MIR_NFIS_Pos                27UL
#define FLEXRAY_MBS_MIR_NFIS_Msk                0x8000000UL
#define FLEXRAY_MBS_MIR_PPIS_Pos                28UL
#define FLEXRAY_MBS_MIR_PPIS_Msk                0x10000000UL
#define FLEXRAY_MBS_MIR_RESS_Pos                29UL
#define FLEXRAY_MBS_MIR_RESS_Msk                0x20000000UL
/* FLEXRAY.OBCM_MIR */
#define FLEXRAY_OBCM_MIR_RHSS_Pos               0UL
#define FLEXRAY_OBCM_MIR_RHSS_Msk               0x1UL
#define FLEXRAY_OBCM_MIR_RDSS_Pos               1UL
#define FLEXRAY_OBCM_MIR_RDSS_Msk               0x2UL
#define FLEXRAY_OBCM_MIR_RHSH_Pos               16UL
#define FLEXRAY_OBCM_MIR_RHSH_Msk               0x10000UL
#define FLEXRAY_OBCM_MIR_RDSH_Pos               17UL
#define FLEXRAY_OBCM_MIR_RDSH_Msk               0x20000UL
/* FLEXRAY.OBCR_MIR */
#define FLEXRAY_OBCR_MIR_OBRS_Pos               0UL
#define FLEXRAY_OBCR_MIR_OBRS_Msk               0x7FUL
#define FLEXRAY_OBCR_MIR_VIEW_Pos               8UL
#define FLEXRAY_OBCR_MIR_VIEW_Msk               0x100UL
#define FLEXRAY_OBCR_MIR_REQ_Pos                9UL
#define FLEXRAY_OBCR_MIR_REQ_Msk                0x200UL
#define FLEXRAY_OBCR_MIR_OBSYS_Pos              15UL
#define FLEXRAY_OBCR_MIR_OBSYS_Msk              0x8000UL
#define FLEXRAY_OBCR_MIR_OBRH_Pos               16UL
#define FLEXRAY_OBCR_MIR_OBRH_Msk               0x7F0000UL


#endif /* _CYIP_FLEXRAY_H_ */


/* [] END OF FILE */
