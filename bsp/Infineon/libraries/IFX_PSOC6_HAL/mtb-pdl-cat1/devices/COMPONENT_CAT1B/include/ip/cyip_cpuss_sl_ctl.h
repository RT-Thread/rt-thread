/***************************************************************************//**
* \file cyip_cpuss_sl_ctl.h
*
* \brief
* CPUSS_SL_CTL IP definitions
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

#ifndef _CYIP_CPUSS_SL_CTL_H_
#define _CYIP_CPUSS_SL_CTL_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                 CPUSS_SL_CTL
*******************************************************************************/

#define CPUSS_SL_CTL_SECTION_SIZE               0x00000010UL

/**
  * \brief SYSCPUSS Internal slave control registers (CPUSS_SL_CTL)
  */
typedef struct {
  __IOM uint32_t SL_CTL;                        /*!< 0x00000000 Slave control (Clock enables) */
  __IOM uint32_t SL_CTL2;                       /*!< 0x00000004 Slave control2 (Reset enables) */
} CPUSS_SL_CTL_Type;                            /*!< Size = 8 (0x8) */


/* CPUSS_SL_CTL.SL_CTL */
#define CPUSS_SL_CTL_SL_CTL_PROMC_ENABLED_Pos   0UL
#define CPUSS_SL_CTL_SL_CTL_PROMC_ENABLED_Msk   0x1UL
#define CPUSS_SL_CTL_SL_CTL_FLASHC_ENABLED_Pos  1UL
#define CPUSS_SL_CTL_SL_CTL_FLASHC_ENABLED_Msk  0x2UL
#define CPUSS_SL_CTL_SL_CTL_RAMC0_ENABLED_Pos   3UL
#define CPUSS_SL_CTL_SL_CTL_RAMC0_ENABLED_Msk   0x8UL
#define CPUSS_SL_CTL_SL_CTL_RAMC1_ENABLED_Pos   4UL
#define CPUSS_SL_CTL_SL_CTL_RAMC1_ENABLED_Msk   0x10UL
#define CPUSS_SL_CTL_SL_CTL_RAMC2_ENABLED_Pos   5UL
#define CPUSS_SL_CTL_SL_CTL_RAMC2_ENABLED_Msk   0x20UL
#define CPUSS_SL_CTL_SL_CTL_DW0_ENABLED_Pos     6UL
#define CPUSS_SL_CTL_SL_CTL_DW0_ENABLED_Msk     0x40UL
#define CPUSS_SL_CTL_SL_CTL_DW1_ENABLED_Pos     7UL
#define CPUSS_SL_CTL_SL_CTL_DW1_ENABLED_Msk     0x80UL
#define CPUSS_SL_CTL_SL_CTL_DMAC0_ENABLED_Pos   8UL
#define CPUSS_SL_CTL_SL_CTL_DMAC0_ENABLED_Msk   0x100UL
#define CPUSS_SL_CTL_SL_CTL_DMAC1_ENABLED_Pos   9UL
#define CPUSS_SL_CTL_SL_CTL_DMAC1_ENABLED_Msk   0x200UL
#define CPUSS_SL_CTL_SL_CTL_IPC_ENABLED_Pos     10UL
#define CPUSS_SL_CTL_SL_CTL_IPC_ENABLED_Msk     0x400UL
/* CPUSS_SL_CTL.SL_CTL2 */
#define CPUSS_SL_CTL_SL_CTL2_PROMC_RST_Pos      0UL
#define CPUSS_SL_CTL_SL_CTL2_PROMC_RST_Msk      0x1UL
#define CPUSS_SL_CTL_SL_CTL2_FLASHC_RST_Pos     1UL
#define CPUSS_SL_CTL_SL_CTL2_FLASHC_RST_Msk     0x2UL
#define CPUSS_SL_CTL_SL_CTL2_RAMC0_RST_Pos      3UL
#define CPUSS_SL_CTL_SL_CTL2_RAMC0_RST_Msk      0x8UL
#define CPUSS_SL_CTL_SL_CTL2_RAMC1_RST_Pos      4UL
#define CPUSS_SL_CTL_SL_CTL2_RAMC1_RST_Msk      0x10UL
#define CPUSS_SL_CTL_SL_CTL2_RAMC2_RST_Pos      5UL
#define CPUSS_SL_CTL_SL_CTL2_RAMC2_RST_Msk      0x20UL
#define CPUSS_SL_CTL_SL_CTL2_DW0_RST_Pos        6UL
#define CPUSS_SL_CTL_SL_CTL2_DW0_RST_Msk        0x40UL
#define CPUSS_SL_CTL_SL_CTL2_DW1_RST_Pos        7UL
#define CPUSS_SL_CTL_SL_CTL2_DW1_RST_Msk        0x80UL
#define CPUSS_SL_CTL_SL_CTL2_DMAC0_RST_Pos      8UL
#define CPUSS_SL_CTL_SL_CTL2_DMAC0_RST_Msk      0x100UL
#define CPUSS_SL_CTL_SL_CTL2_DMAC1_RST_Pos      9UL
#define CPUSS_SL_CTL_SL_CTL2_DMAC1_RST_Msk      0x200UL
#define CPUSS_SL_CTL_SL_CTL2_IPC_RST_Pos        10UL
#define CPUSS_SL_CTL_SL_CTL2_IPC_RST_Msk        0x400UL


#endif /* _CYIP_CPUSS_SL_CTL_H_ */


/* [] END OF FILE */
