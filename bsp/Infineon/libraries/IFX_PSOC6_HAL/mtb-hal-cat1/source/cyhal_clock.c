/*******************************************************************************
* File Name: cyhal_clock.c
*
* Description:
* Provides an implementation for high level interface for interacting with the
* Cypress Clocks. This is a wrapper around the lower level PDL API.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
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

#include <stdlib.h>
#include <string.h>
#include "cy_sysclk.h"
#include "cy_utils.h"
#include "cyhal_clock.h"
#include "cyhal_system.h"
#include "cyhal_utils.h"
#include "cyhal_hwmgr.h"

#if (CYHAL_DRIVER_AVAILABLE_CLOCK)

#if defined(__cplusplus)
extern "C"
{
#endif

#define _CYHAL_CLOCK_FLL_LOCK_TIME (20000UL)
#define _CYHAL_CLOCK_PLL_LOCK_TIME (10000UL)

#if defined(PERI_PCLK_GR_NUM_Pos)
#define _CYHAL_CLOCK_GET_PCLK_GR_NUM(block) ((en_clk_dst_t)(_CYHAL_PERIPHERAL_GROUP_GET_GROUP(block) << PERI_PCLK_GR_NUM_Pos))
#else
#define _CYHAL_CLOCK_GET_PCLK_GR_NUM(block) ((en_clk_dst_t)0) /* Value is not used for devices that don't have PCLK groups. */
#endif

/* We can't use the PDL-defined _CYHAL_SRSS_PILO_PRESENT because on CAT1A devices it performs a struct lookup
 * which won't work in preprocessor expressions */
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
    #define _CYHAL_SRSS_PILO_PRESENT (SRSS_PILO_PRESENT)
#elif defined(COMPONENT_CAT1B)
    #define _CYHAL_SRSS_PILO_PRESENT (SRSS_S40S_PILO_PRESENT)
#endif

/******************************************************************************
 ****************************** Clock Resources *******************************
 *****************************************************************************/
const cyhal_clock_tolerance_t CYHAL_CLOCK_TOLERANCE_0_P = {CYHAL_TOLERANCE_PERCENT, 0};
const cyhal_clock_tolerance_t CYHAL_CLOCK_TOLERANCE_1_P = {CYHAL_TOLERANCE_PERCENT, 1};
const cyhal_clock_tolerance_t CYHAL_CLOCK_TOLERANCE_5_P = {CYHAL_TOLERANCE_PERCENT, 5};

const cyhal_resource_inst_t CYHAL_CLOCK_RSC_IMO = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_IMO, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_EXT = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_EXT, 0 };
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ILO = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_ILO, 0 };
#elif defined(COMPONENT_CAT1C)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ILO[_CYHAL_SRSS_NUM_ILO] =
{
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_ILO, 0 },
    #if (SRSS_HT_VARIANT > 0)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_ILO, 1 },
    #endif
};
#endif
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_LF = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_LF, 0 };
/* PUMP clock is only available on CAT1A and CAT1B devices */
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PUMP = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PUMP, 0 };
#endif /* defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) */
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_BAK = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_BAK, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ALT_SYS_TICK = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_ALT_SYS_TICK, 0 };

#if defined(COMPONENT_CAT1C)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_MEM = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_MEM, 0 };
#endif

const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PATHMUX[SRSS_NUM_CLKPATH] =
{
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 0 },
#if (SRSS_NUM_CLKPATH > 1)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 1 },
#endif
#if (SRSS_NUM_CLKPATH > 2)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 2 },
#endif
#if (SRSS_NUM_CLKPATH > 3)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 3 },
#endif
#if (SRSS_NUM_CLKPATH > 4)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 4 },
#endif
#if (SRSS_NUM_CLKPATH > 5)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 5 },
#endif
#if (SRSS_NUM_CLKPATH > 6)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 6 },
#endif
#if (SRSS_NUM_CLKPATH > 7)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 7 },
#endif
#if (SRSS_NUM_CLKPATH > 8)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 8 },
#endif
#if (SRSS_NUM_CLKPATH > 9)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 9 },
#endif
#if (SRSS_NUM_CLKPATH > 10)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 10 },
#endif
#if (SRSS_NUM_CLKPATH > 11)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 11 },
#endif
#if (SRSS_NUM_CLKPATH > 12)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 12 },
#endif
#if (SRSS_NUM_CLKPATH > 13)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 13 },
#endif
#if (SRSS_NUM_CLKPATH > 14)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 14 },
#endif
#if (SRSS_NUM_CLKPATH > 15)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PATHMUX, 15 },
#endif
};

const cyhal_resource_inst_t CYHAL_CLOCK_RSC_HF[SRSS_NUM_HFROOT] =
{
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 0 },
#if (SRSS_NUM_HFROOT > 1)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 1 },
#endif
#if (SRSS_NUM_HFROOT > 2)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 2 },
#endif
#if (SRSS_NUM_HFROOT > 3)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 3 },
#endif
#if (SRSS_NUM_HFROOT > 4)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 4 },
#endif
#if (SRSS_NUM_HFROOT > 5)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 5 },
#endif
#if (SRSS_NUM_HFROOT > 6)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 6 },
#endif
#if (SRSS_NUM_HFROOT > 7)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 7 },
#endif
#if (SRSS_NUM_HFROOT > 8)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 8 },
#endif
#if (SRSS_NUM_HFROOT > 9)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 9 },
#endif
#if (SRSS_NUM_HFROOT > 10)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 10 },
#endif
#if (SRSS_NUM_HFROOT > 11)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 11 },
#endif
#if (SRSS_NUM_HFROOT > 12)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 12 },
#endif
#if (SRSS_NUM_HFROOT > 13)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 13 },
#endif
#if (SRSS_NUM_HFROOT > 14)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 14 },
#endif
#if (SRSS_NUM_HFROOT > 15)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_HF, 15 },
#endif
};

#if SRSS_ECO_PRESENT
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ECO = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_ECO, 0 };
#endif
#if SRSS_ALTHF_PRESENT
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ALTHF = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_ALTHF, 0 };
#endif
#if SRSS_ALTLF_PRESENT
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ALTLF = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_ALTLF, 0 };
#endif
#if _CYHAL_SRSS_PILO_PRESENT
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PILO = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PILO, 0 };
#endif
#if SRSS_BACKUP_PRESENT
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_WCO = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_WCO, 0 };
#endif
#if defined(COMPONENT_CAT1B) || (SRSS_MFO_PRESENT)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_MFO = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_MFO, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_MF = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_MF, 0 };
#endif

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C) || (SRSS_FLL_PRESENT)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_FLL = { CYHAL_RSC_CLOCK, CYHAL_CLOCK_BLOCK_FLL, 0 };
#endif

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
#if defined(COMPONENT_CAT1A)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_FAST = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_FAST, 0 };
#else
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_FAST[_CYHAL_SRSS_NUM_FAST] =
{
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_FAST, 0 },
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_FAST, 1 },
};
#endif
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_SLOW = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_SLOW, 0 };
#endif

#if defined(COMPONENT_CAT1A)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PERI = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 0 };
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_TIMER = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_TIMER, 0 };
#if (_CYHAL_SRSS_NUM_PLL > 0)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PLL[_CYHAL_SRSS_NUM_PLL] =
{
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 0 },
#if (_CYHAL_SRSS_NUM_PLL > 1)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 1 },
#endif
#if (_CYHAL_SRSS_NUM_PLL > 2)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 2 },
#endif
#if (_CYHAL_SRSS_NUM_PLL > 3)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 3 },
#endif
#if (_CYHAL_SRSS_NUM_PLL > 4)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 4 },
#endif
#if (_CYHAL_SRSS_NUM_PLL > 5)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 5 },
#endif
#if (_CYHAL_SRSS_NUM_PLL > 6)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 6 },
#endif
#if (_CYHAL_SRSS_NUM_PLL > 7)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 7 },
#endif
#if (_CYHAL_SRSS_NUM_PLL > 8)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 8 },
#endif
#if (_CYHAL_SRSS_NUM_PLL > 9)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 9 },
#endif
#if (_CYHAL_SRSS_NUM_PLL > 10)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 10 },
#endif
#if (_CYHAL_SRSS_NUM_PLL > 11)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 11 },
#endif
#if (_CYHAL_SRSS_NUM_PLL > 12)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 12 },
#endif
#if (_CYHAL_SRSS_NUM_PLL > 13)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 13 },
#endif
#if (_CYHAL_SRSS_NUM_PLL > 14)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL, 14 },
#endif
};
#endif
#endif

#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_IHO = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_IHO, 0 };
#if SRSS_ECO_PRESENT
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_ECO_PRESCALER = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_ECO_PRESCALER, 0 };
#endif
#if SRSS_BACKUP_S40E_LPECO_PRESENT
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_LPECO_PRESCALER = { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_LPECO_PRESCALER, 0 };
#endif
#endif

/* COMPONENT_CAT1C uses a hybrid approach from what was done on CAT1A and CAT1B. Facelift CAT1C supports ClkPeri as well
as Peripheral Clock Groups. For CAT1C, ClkPeri is used to source everything in Peripheral Clock Group 0 (HF0) and other
Peripheral Clock Groups derive from one of the HFClks and have their own group divider. Thus we declare RSC_PERI Peri array for CAT1C */

const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PERI[CY_PERI_GROUP_NR] =
{
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 0 },
#if (CY_PERI_GROUP_NR > 1)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 1 },
#endif
#if (CY_PERI_GROUP_NR > 2)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 2 },
#endif
#if (CY_PERI_GROUP_NR > 3)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 3 },
#endif
#if (CY_PERI_GROUP_NR > 4)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 4 },
#endif
#if (CY_PERI_GROUP_NR > 5)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 5 },
#endif
#if (CY_PERI_GROUP_NR > 6)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 6 },
#endif
#if (CY_PERI_GROUP_NR > 7)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 7 },
#endif
#if (CY_PERI_GROUP_NR > 8)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 8 },
#endif
#if (CY_PERI_GROUP_NR > 9)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 9 },
#endif
#if (CY_PERI_GROUP_NR > 10)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 10 },
#endif
#if (CY_PERI_GROUP_NR > 11)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 11 },
#endif
#if (CY_PERI_GROUP_NR > 12)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 12 },
#endif
#if (CY_PERI_GROUP_NR > 13)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 13 },
#endif
#if (CY_PERI_GROUP_NR > 14)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 14 },
#endif
#if (CY_PERI_GROUP_NR > 15)
    { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PERI, 15 },
#endif
};

#if (SRSS_NUM_PLL200M > 0)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PLL200M[SRSS_NUM_PLL200M] =
{
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL200, 0 },
#if (SRSS_NUM_PLL200M > 1)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL200, 1 },
#endif
#if (SRSS_NUM_PLL200M > 2)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL200, 2 },
#endif
#if (SRSS_NUM_PLL200M > 3)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL200, 3 },
#endif
#if (SRSS_NUM_PLL200M > 4)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL200, 4 },
#endif
#if (SRSS_NUM_PLL200M > 5)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL200, 5 },
#endif
#if (SRSS_NUM_PLL200M > 6)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL200, 6 },
#endif
#if (SRSS_NUM_PLL200M > 7)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL200, 7 },
#endif
#if (SRSS_NUM_PLL200M > 8)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL200, 8 },
#endif
#if (SRSS_NUM_PLL200M > 9)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL200, 9 },
#endif
#if (SRSS_NUM_PLL200M > 10)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL200, 10 },
#endif
#if (SRSS_NUM_PLL200M > 11)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL200, 11 },
#endif
#if (SRSS_NUM_PLL200M > 12)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL200, 12 },
#endif
#if (SRSS_NUM_PLL200M > 13)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL200, 13 },
#endif
#if (SRSS_NUM_PLL200M > 14)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL200, 14 },
#endif
};
#endif

#if (SRSS_NUM_PLL400M > 0)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_PLL400M[SRSS_NUM_PLL400M] =
{
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL400, 0 },
#if (SRSS_NUM_PLL400M > 1)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL400, 1 },
#endif
#if (SRSS_NUM_PLL400M > 2)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL400, 2 },
#endif
#if (SRSS_NUM_PLL400M > 3)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL400, 3 },
#endif
#if (SRSS_NUM_PLL400M > 4)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL400, 4 },
#endif
#if (SRSS_NUM_PLL400M > 5)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL400, 5 },
#endif
#if (SRSS_NUM_PLL400M > 6)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL400, 6 },
#endif
#if (SRSS_NUM_PLL400M > 7)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL400, 7 },
#endif
#if (SRSS_NUM_PLL400M > 8)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL400, 8 },
#endif
#if (SRSS_NUM_PLL400M > 9)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL400, 9 },
#endif
#if (SRSS_NUM_PLL400M > 10)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL400, 10 },
#endif
#if (SRSS_NUM_PLL400M > 11)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL400, 11 },
#endif
#if (SRSS_NUM_PLL400M > 12)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL400, 12 },
#endif
#if (SRSS_NUM_PLL400M > 13)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL400, 13 },
#endif
#if (SRSS_NUM_PLL400M > 14)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_PLL400, 14 },
#endif
};
#endif

#if (SRSS_NUM_DPLL_LP > 0)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_DPLL_LP[SRSS_NUM_DPLL_LP] =
{
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_LP, 0 },
#if (SRSS_NUM_DPLL_LP > 1)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_LP, 1 },
#endif
#if (SRSS_NUM_DPLL_LP > 2)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_LP, 2 },
#endif
#if (SRSS_NUM_DPLL_LP > 3)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_LP, 3 },
#endif
#if (SRSS_NUM_DPLL_LP > 4)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_LP, 4 },
#endif
#if (SRSS_NUM_DPLL_LP > 5)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_LP, 5 },
#endif
#if (SRSS_NUM_DPLL_LP > 6)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_LP, 6 },
#endif
#if (SRSS_NUM_DPLL_LP > 7)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_LP, 7 },
#endif
#if (SRSS_NUM_DPLL_LP > 8)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_LP, 8 },
#endif
#if (SRSS_NUM_DPLL_LP > 9)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_LP, 9 },
#endif
#if (SRSS_NUM_DPLL_LP > 10)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_LP, 10 },
#endif
#if (SRSS_NUM_DPLL_LP > 11)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_LP, 11 },
#endif
#if (SRSS_NUM_DPLL_LP > 12)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_LP, 12 },
#endif
#if (SRSS_NUM_DPLL_LP > 13)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_LP, 13 },
#endif
#if (SRSS_NUM_DPLL_LP > 14)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_LP, 14 },
#endif
};
#endif

#if (SRSS_NUM_DPLL_HP > 0)
const cyhal_resource_inst_t CYHAL_CLOCK_RSC_DPLL_HP[SRSS_NUM_DPLL_HP] =
{
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_HP, 0 },
#if (SRSS_NUM_DPLL_HP > 1)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_HP, 1 },
#endif
#if (SRSS_NUM_DPLL_HP > 2)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_HP, 2 },
#endif
#if (SRSS_NUM_DPLL_HP > 3)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_HP, 3 },
#endif
#if (SRSS_NUM_DPLL_HP > 4)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_HP, 4 },
#endif
#if (SRSS_NUM_DPLL_HP > 5)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_HP, 5 },
#endif
#if (SRSS_NUM_DPLL_HP > 6)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_HP, 6 },
#endif
#if (SRSS_NUM_DPLL_HP > 7)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_HP, 7 },
#endif
#if (SRSS_NUM_DPLL_HP > 8)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_HP, 8 },
#endif
#if (SRSS_NUM_DPLL_HP > 9)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_HP, 9 },
#endif
#if (SRSS_NUM_DPLL_HP > 10)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_HP, 10 },
#endif
#if (SRSS_NUM_DPLL_HP > 11)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_HP, 11 },
#endif
#if (SRSS_NUM_DPLL_HP > 12)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_HP, 12 },
#endif
#if (SRSS_NUM_DPLL_HP > 13)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_HP, 13 },
#endif
#if (SRSS_NUM_DPLL_HP > 14)
   { CYHAL_RSC_CLOCK, (uint8_t)CYHAL_CLOCK_BLOCK_DPLL_HP, 14 },
#endif
};
#endif

#if ((SRSS_NUM_PLL400M > 0) && (SRSS_NUM_PLL200M == 0))
#define CYHAL_CLOCK_RSC_PLL CYHAL_CLOCK_RSC_PLL400M
#elif ((SRSS_NUM_PLL400M == 0) && (SRSS_NUM_PLL200M > 0))
#define CYHAL_CLOCK_RSC_PLL CYHAL_CLOCK_RSC_PLL200M
#endif
#endif



/******************************************************************************
 ***************************** Support Functions*******************************
 *****************************************************************************/

static cy_rslt_t _cyhal_clock_compute_div(uint64_t input_hz, uint32_t desired_hz, uint32_t divider_bits, const cyhal_clock_tolerance_t *tolerance, uint32_t *div)
{
    uint32_t max_div = (1 << divider_bits);
    *div = (input_hz + (desired_hz / 2)) / desired_hz;
    if (*div > max_div)
        *div = max_div;

    uint32_t diff = (tolerance != NULL)
        ? (uint32_t)abs(_cyhal_utils_calculate_tolerance(tolerance->type, desired_hz, input_hz / *div))
        : 0;

    return ((tolerance != NULL) && (diff > tolerance->value))
        ? CYHAL_CLOCK_RSLT_ERR_FREQ
        : CY_RSLT_SUCCESS;
}

static uint32_t _cyhal_clock_get_lf_frequency(void)
{
    cy_en_clklf_in_sources_t source = Cy_SysClk_ClkLfGetSource();
    switch (source)
    {
        case CY_SYSCLK_CLKLF_IN_ILO:
#if defined(COMPONENT_CAT1C)
        case CY_SYSCLK_CLKLF_IN_ILO1:
#endif
            return CY_SYSCLK_ILO_FREQ;
#if _CYHAL_SRSS_PILO_PRESENT
        case CY_SYSCLK_CLKLF_IN_PILO:
            return CY_SYSCLK_PILO_FREQ;
#endif
#if SRSS_BACKUP_PRESENT
        case CY_SYSCLK_CLKLF_IN_WCO:
            return CY_SYSCLK_WCO_FREQ;
#endif
#if SRSS_ALTLF_PRESENT
        case CY_SYSCLK_CLKLF_IN_ALTLF:
            return Cy_SysClk_AltLfGetFrequency();
#endif
#if defined(COMPONENT_CAT1B)
#if SRSS_ECO_PRESENT
        case CY_SYSCLK_CLKLF_IN_ECO_PRESCALER:
            //return Cy_SysClk_EcoPrescalerGetFrequency();
            return 0;
#endif
#if SRSS_BACKUP_S40E_LPECO_PRESENT
        case CY_SYSCLK_CLKLF_IN_LPECO_PRESCALER:
            return Cy_SysClk_LpEcoPrescalerGetFrequency();
#endif
#endif
        default:
            CY_ASSERT(false);
            return 0;
    }
}

static void _cyhal_clock_update_system_state(bool before_change, uint32_t old_sysclk_freq_hz, uint32_t new_sysclk_freq_hz)
{
    // If increasing the clock frequency we need to update the speeds
    // before the change. If decreasing the frequency we need to update
    // after the change.
    if ((before_change == (bool)(new_sysclk_freq_hz > old_sysclk_freq_hz)) ||
        (!before_change == (new_sysclk_freq_hz < old_sysclk_freq_hz)))
    {
#if defined(COMPONENT_CAT1A)
        bool is_ulp = Cy_SysPm_IsSystemUlp();
#elif defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
        bool is_ulp = true;
#elif defined(COMPONENT_CAT1C)
        bool is_ulp = false;
#endif
        Cy_SysLib_SetWaitStates(is_ulp, new_sysclk_freq_hz / 1000000);
    }

    // If after the change, update the clock
    if (!before_change)
        SystemCoreClockUpdate();
}


static cy_rslt_t _cyhal_clock_set_enabled_unsupported(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(enabled);
    CY_UNUSED_PARAMETER(wait_for_lock);
    CY_ASSERT(false); // Unhandled clock
    return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
}
static cy_rslt_t _cyhal_clock_set_frequency_unsupported(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(hz);
    CY_UNUSED_PARAMETER(tolerance);
    CY_ASSERT(false); // Unhandled clock
    return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
}
static cy_rslt_t _cyhal_clock_set_divider_unsupported(cyhal_clock_t *clock, uint32_t divider)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(divider);
    CY_ASSERT(false); // Unhandled clock
    return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
}
static cy_rslt_t _cyhal_clock_set_source_unsupported(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(source);
    CY_ASSERT(false); // Unhandled clock
    return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
}
static bool _cyhal_clock_is_enabled_true(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return true;
}
static cy_rslt_t _cyhal_clock_get_sources_none(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(sources);
    *count = 0;
    return CY_RSLT_SUCCESS;
}


static const cyhal_resource_inst_t *_CYHAL_CLOCK_SOURCE_HF[] =
{
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C) || (SRSS_FLL_PRESENT)
    &CYHAL_CLOCK_RSC_FLL,
#endif
#if defined(COMPONENT_CAT1A)
#if (_CYHAL_SRSS_NUM_PLL > 0)
    &CYHAL_CLOCK_RSC_PLL[0],
#endif
#if (_CYHAL_SRSS_NUM_PLL > 1)
    &CYHAL_CLOCK_RSC_PLL[1],
#endif
#if (_CYHAL_SRSS_NUM_PLL > 2)
    &CYHAL_CLOCK_RSC_PLL[2],
#endif
#if (_CYHAL_SRSS_NUM_PLL > 3)
    &CYHAL_CLOCK_RSC_PLL[3],
#endif
#if (_CYHAL_SRSS_NUM_PLL > 4)
    &CYHAL_CLOCK_RSC_PLL[4],
#endif
#if (_CYHAL_SRSS_NUM_PLL > 5)
    &CYHAL_CLOCK_RSC_PLL[5],
#endif
#if (_CYHAL_SRSS_NUM_PLL > 6)
    &CYHAL_CLOCK_RSC_PLL[6],
#endif
#if (_CYHAL_SRSS_NUM_PLL > 7)
    &CYHAL_CLOCK_RSC_PLL[7],
#endif
#if (_CYHAL_SRSS_NUM_PLL > 8)
    &CYHAL_CLOCK_RSC_PLL[8],
#endif
#if (_CYHAL_SRSS_NUM_PLL > 9)
    &CYHAL_CLOCK_RSC_PLL[9],
#endif
#if (_CYHAL_SRSS_NUM_PLL > 10)
    &CYHAL_CLOCK_RSC_PLL[10],
#endif
#if (_CYHAL_SRSS_NUM_PLL > 11)
    &CYHAL_CLOCK_RSC_PLL[11],
#endif
#if (_CYHAL_SRSS_NUM_PLL > 12)
    &CYHAL_CLOCK_RSC_PLL[12],
#endif
#if (_CYHAL_SRSS_NUM_PLL > 13)
    &CYHAL_CLOCK_RSC_PLL[13],
#endif
#elif defined(COMPONENT_CAT1C)
#if (SRSS_NUM_PLL200M > 0)
    &CYHAL_CLOCK_RSC_PLL200M[0],
#endif
#if (SRSS_NUM_PLL200M > 1)
    &CYHAL_CLOCK_RSC_PLL200M[1],
#endif
#if (SRSS_NUM_PLL200M > 2)
    &CYHAL_CLOCK_RSC_PLL200M[2],
#endif
#if (SRSS_NUM_PLL200M > 3)
    &CYHAL_CLOCK_RSC_PLL200M[3],
#endif
#if (SRSS_NUM_PLL200M > 4)
    &CYHAL_CLOCK_RSC_PLL200M[4],
#endif
#if (SRSS_NUM_PLL200M > 5)
    &CYHAL_CLOCK_RSC_PLL200M[5],
#endif
#if (SRSS_NUM_PLL200M > 6)
    &CYHAL_CLOCK_RSC_PLL200M[6],
#endif
#if (SRSS_NUM_PLL200M > 7)
    &CYHAL_CLOCK_RSC_PLL200M[7],
#endif
#if (SRSS_NUM_PLL200M > 8)
    &CYHAL_CLOCK_RSC_PLL200M[8],
#endif
#if (SRSS_NUM_PLL200M > 9)
    &CYHAL_CLOCK_RSC_PLL200M[9],
#endif
#if (SRSS_NUM_PLL200M > 10)
    &CYHAL_CLOCK_RSC_PLL200M[10],
#endif
#if (SRSS_NUM_PLL200M > 11)
    &CYHAL_CLOCK_RSC_PLL200M[11],
#endif
#if (SRSS_NUM_PLL200M > 12)
    &CYHAL_CLOCK_RSC_PLL200M[12],
#endif
#if (SRSS_NUM_PLL200M > 13)
    &CYHAL_CLOCK_RSC_PLL200M[13],
#endif
#if (SRSS_NUM_PLL200M > 14)
    &CYHAL_CLOCK_RSC_PLL200M[14],
#endif
#if (SRSS_NUM_PLL200M > 15)
    &CYHAL_CLOCK_RSC_PLL200M[15],
#endif
#if (SRSS_NUM_PLL400M > 0)
    &CYHAL_CLOCK_RSC_PLL400M[0],
#endif
#if (SRSS_NUM_PLL400M > 1)
    &CYHAL_CLOCK_RSC_PLL400M[1],
#endif
#if (SRSS_NUM_PLL400M > 2)
    &CYHAL_CLOCK_RSC_PLL400M[2],
#endif
#if (SRSS_NUM_PLL400M > 3)
    &CYHAL_CLOCK_RSC_PLL400M[3],
#endif
#if (SRSS_NUM_PLL400M > 4)
    &CYHAL_CLOCK_RSC_PLL400M[4],
#endif
#if (SRSS_NUM_PLL400M > 5)
    &CYHAL_CLOCK_RSC_PLL400M[5],
#endif
#if (SRSS_NUM_PLL400M > 6)
    &CYHAL_CLOCK_RSC_PLL400M[6],
#endif
#if (SRSS_NUM_PLL400M > 7)
    &CYHAL_CLOCK_RSC_PLL400M[7],
#endif
#if (SRSS_NUM_PLL400M > 8)
    &CYHAL_CLOCK_RSC_PLL400M[8],
#endif
#if (SRSS_NUM_PLL400M > 9)
    &CYHAL_CLOCK_RSC_PLL400M[9],
#endif
#if (SRSS_NUM_PLL400M > 10)
    &CYHAL_CLOCK_RSC_PLL400M[10],
#endif
#if (SRSS_NUM_PLL400M > 11)
    &CYHAL_CLOCK_RSC_PLL400M[11],
#endif
#if (SRSS_NUM_PLL400M > 12)
    &CYHAL_CLOCK_RSC_PLL400M[12],
#endif
#if (SRSS_NUM_PLL400M > 13)
    &CYHAL_CLOCK_RSC_PLL400M[13],
#endif
#if (SRSS_NUM_PLL400M > 14)
    &CYHAL_CLOCK_RSC_PLL400M[14],
#endif
#if (SRSS_NUM_PLL400M > 15)
    &CYHAL_CLOCK_RSC_PLL400M[15],
#endif
#elif defined(COMPONENT_CAT1D)
#if (SRSS_NUM_DPLL_LP > 0)
    &CYHAL_CLOCK_RSC_DPLL_LP[0],
#endif
#if (SRSS_NUM_DPLL_LP > 1)
    &CYHAL_CLOCK_RSC_DPLL_LP[1],
#endif
#if (SRSS_NUM_DPLL_LP > 2)
    &CYHAL_CLOCK_RSC_DPLL_LP[2],
#endif
#if (SRSS_NUM_DPLL_LP > 3)
    &CYHAL_CLOCK_RSC_DPLL_LP[3],
#endif
#if (SRSS_NUM_DPLL_LP > 4)
    &CYHAL_CLOCK_RSC_DPLL_LP[4],
#endif
#if (SRSS_NUM_DPLL_LP > 5)
    &CYHAL_CLOCK_RSC_DPLL_LP[5],
#endif
#if (SRSS_NUM_DPLL_LP > 6)
    &CYHAL_CLOCK_RSC_DPLL_LP[6],
#endif
#if (SRSS_NUM_DPLL_LP > 7)
    &CYHAL_CLOCK_RSC_DPLL_LP[7],
#endif
#if (SRSS_NUM_DPLL_LP > 8)
    &CYHAL_CLOCK_RSC_DPLL_LP[8],
#endif
#if (SRSS_NUM_DPLL_LP > 9)
    &CYHAL_CLOCK_RSC_DPLL_LP[9],
#endif
#if (SRSS_NUM_DPLL_LP > 10)
    &CYHAL_CLOCK_RSC_DPLL_LP[10],
#endif
#if (SRSS_NUM_DPLL_LP > 11)
    &CYHAL_CLOCK_RSC_DPLL_LP[11],
#endif
#if (SRSS_NUM_DPLL_LP > 12)
    &CYHAL_CLOCK_RSC_DPLL_LP[12],
#endif
#if (SRSS_NUM_DPLL_LP > 13)
    &CYHAL_CLOCK_RSC_DPLL_LP[13],
#endif
#if (SRSS_NUM_DPLL_LP > 14)
    &CYHAL_CLOCK_RSC_DPLL_LP[14],
#endif
#if (SRSS_NUM_DPLL_LP > 15)
    &CYHAL_CLOCK_RSC_DPLL_LP[15],
#endif
#if (SRSS_NUM_DPLL_HP > 0)
    &CYHAL_CLOCK_RSC_DPLL_HP[0],
#endif
#if (SRSS_NUM_DPLL_HP > 1)
    &CYHAL_CLOCK_RSC_DPLL_HP[1],
#endif
#if (SRSS_NUM_DPLL_HP > 2)
    &CYHAL_CLOCK_RSC_DPLL_HP[2],
#endif
#if (SRSS_NUM_DPLL_HP > 3)
    &CYHAL_CLOCK_RSC_DPLL_HP[3],
#endif
#if (SRSS_NUM_DPLL_HP > 4)
    &CYHAL_CLOCK_RSC_DPLL_HP[4],
#endif
#if (SRSS_NUM_DPLL_HP > 5)
    &CYHAL_CLOCK_RSC_DPLL_HP[5],
#endif
#if (SRSS_NUM_DPLL_HP > 6)
    &CYHAL_CLOCK_RSC_DPLL_HP[6],
#endif
#if (SRSS_NUM_DPLL_HP > 7)
    &CYHAL_CLOCK_RSC_DPLL_HP[7],
#endif
#if (SRSS_NUM_DPLL_HP > 8)
    &CYHAL_CLOCK_RSC_DPLL_HP[8],
#endif
#if (SRSS_NUM_DPLL_HP > 9)
    &CYHAL_CLOCK_RSC_DPLL_HP[9],
#endif
#if (SRSS_NUM_DPLL_HP > 10)
    &CYHAL_CLOCK_RSC_DPLL_HP[10],
#endif
#if (SRSS_NUM_DPLL_HP > 11)
    &CYHAL_CLOCK_RSC_DPLL_HP[11],
#endif
#if (SRSS_NUM_DPLL_HP > 12)
    &CYHAL_CLOCK_RSC_DPLL_HP[12],
#endif
#if (SRSS_NUM_DPLL_HP > 13)
    &CYHAL_CLOCK_RSC_DPLL_HP[13],
#endif
#if (SRSS_NUM_DPLL_HP > 14)
    &CYHAL_CLOCK_RSC_DPLL_HP[14],
#endif
#if (SRSS_NUM_DPLL_HP > 15)
    &CYHAL_CLOCK_RSC_DPLL_HP[15],
#endif
#endif
    &CYHAL_CLOCK_RSC_PATHMUX[0],
#if (SRSS_NUM_CLKPATH > 1)
    &CYHAL_CLOCK_RSC_PATHMUX[1],
#endif
#if (SRSS_NUM_CLKPATH > 2)
    &CYHAL_CLOCK_RSC_PATHMUX[2],
#endif
#if (SRSS_NUM_CLKPATH > 3)
    &CYHAL_CLOCK_RSC_PATHMUX[3],
#endif
#if (SRSS_NUM_CLKPATH > 4)
    &CYHAL_CLOCK_RSC_PATHMUX[4],
#endif
#if (SRSS_NUM_CLKPATH > 5)
    &CYHAL_CLOCK_RSC_PATHMUX[5],
#endif
#if (SRSS_NUM_CLKPATH > 6)
    &CYHAL_CLOCK_RSC_PATHMUX[6],
#endif
#if (SRSS_NUM_CLKPATH > 7)
    &CYHAL_CLOCK_RSC_PATHMUX[7],
#endif
#if (SRSS_NUM_CLKPATH > 8)
    &CYHAL_CLOCK_RSC_PATHMUX[8],
#endif
#if (SRSS_NUM_CLKPATH > 9)
    &CYHAL_CLOCK_RSC_PATHMUX[9],
#endif
#if (SRSS_NUM_CLKPATH > 10)
    &CYHAL_CLOCK_RSC_PATHMUX[10],
#endif
#if (SRSS_NUM_CLKPATH > 11)
    &CYHAL_CLOCK_RSC_PATHMUX[11],
#endif
#if (SRSS_NUM_CLKPATH > 12)
    &CYHAL_CLOCK_RSC_PATHMUX[12],
#endif
#if (SRSS_NUM_CLKPATH > 13)
    &CYHAL_CLOCK_RSC_PATHMUX[13],
#endif
#if (SRSS_NUM_CLKPATH > 14)
    &CYHAL_CLOCK_RSC_PATHMUX[14],
#endif
#if (SRSS_NUM_CLKPATH > 15)
    &CYHAL_CLOCK_RSC_PATHMUX[15],
#endif
};

#if defined (COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
static cy_rslt_t _cyhal_clock_get_sources_peri_peripheral(uint8_t idx, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    static const cyhal_resource_inst_t *_CYHAL_CLOCK_SOURCE_PERI[SRSS_NUM_HFROOT] =
    {
        &CYHAL_CLOCK_RSC_HF[0],
    #if (SRSS_NUM_HFROOT > 1)
        &CYHAL_CLOCK_RSC_HF[1],
    #endif
    #if (SRSS_NUM_HFROOT > 2)
        &CYHAL_CLOCK_RSC_HF[2],
    #endif
    #if (SRSS_NUM_HFROOT > 3)
        &CYHAL_CLOCK_RSC_HF[3],
    #endif
    #if (SRSS_NUM_HFROOT > 4)
        &CYHAL_CLOCK_RSC_HF[4],
    #endif
    #if (SRSS_NUM_HFROOT > 5)
        &CYHAL_CLOCK_RSC_HF[5],
    #endif
    #if (SRSS_NUM_HFROOT > 6)
        &CYHAL_CLOCK_RSC_HF[6],
    #endif
    #if (SRSS_NUM_HFROOT > 7)
        &CYHAL_CLOCK_RSC_HF[7],
    #endif
    #if (SRSS_NUM_HFROOT > 8)
        &CYHAL_CLOCK_RSC_HF[8],
    #endif
    #if (SRSS_NUM_HFROOT > 9)
        &CYHAL_CLOCK_RSC_HF[9],
    #endif
    #if (SRSS_NUM_HFROOT > 10)
        &CYHAL_CLOCK_RSC_HF[10],
    #endif
    #if (SRSS_NUM_HFROOT > 11)
        &CYHAL_CLOCK_RSC_HF[11],
    #endif
    #if (SRSS_NUM_HFROOT > 12)
        &CYHAL_CLOCK_RSC_HF[12],
    #endif
    #if (SRSS_NUM_HFROOT > 13)
        &CYHAL_CLOCK_RSC_HF[13],
    #endif
    #if (SRSS_NUM_HFROOT > 14)
        &CYHAL_CLOCK_RSC_HF[14],
    #endif
    #if (SRSS_NUM_HFROOT > 15)
        &CYHAL_CLOCK_RSC_HF[15],
    #endif
    };

    *sources = &(_CYHAL_CLOCK_SOURCE_PERI[idx]);
    *count = 1;
    return CY_RSLT_SUCCESS;
}
#endif


// IMO
static uint32_t _cyhal_clock_get_frequency_imo(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return CY_SYSCLK_IMO_FREQ;
}


// ECO
#if SRSS_ECO_PRESENT
static bool _cyhal_clock_is_enabled_eco(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return 0u != (SRSS_CLK_ECO_CONFIG & SRSS_CLK_ECO_CONFIG_ECO_EN_Msk);
}
static cy_rslt_t _cyhal_clock_set_enabled_eco(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);

    if (enabled)
    {
        if (0u != (SRSS_CLK_ECO_CONFIG & SRSS_CLK_ECO_CONFIG_ECO_EN_Msk))
        {
            // Already enabled
            if (wait_for_lock)
            {
                for (int t = 0; t < 3 && Cy_SysClk_EcoGetStatus() != CY_SYSCLK_ECOSTAT_STABLE; ++t)
                {
                    cyhal_system_delay_us(1000UL);
                }
                return Cy_SysClk_EcoGetStatus() == CY_SYSCLK_ECOSTAT_STABLE
                    ? CY_RSLT_SUCCESS
                    : CY_SYSCLK_TIMEOUT;
            }
            return CY_RSLT_SUCCESS;
        }
        else
        {
            return Cy_SysClk_EcoEnable(wait_for_lock ? 3000UL : 0UL);
        }
    }
    else
    {
        Cy_SysClk_EcoDisable();
        return CY_RSLT_SUCCESS;
    }
}
static uint32_t _cyhal_clock_get_frequency_eco(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_EcoGetFrequency();
}
#endif

// EXT
static bool _cyhal_clock_is_enabled_ext(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return (Cy_SysClk_ExtClkGetFrequency() > 0);
}
static uint32_t _cyhal_clock_get_frequency_ext(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_ExtClkGetFrequency();
}
static cy_rslt_t _cyhal_clock_set_frequency_ext(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(tolerance);

    Cy_SysClk_ExtClkSetFrequency(hz);
    return CY_RSLT_SUCCESS;
}

// ALTHF
#if SRSS_ALTHF_PRESENT
static bool _cyhal_clock_is_enabled_althf(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return (Cy_SysClk_AltHfGetFrequency() > 0);
}
static uint32_t _cyhal_clock_get_frequency_althf(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_AltHfGetFrequency();
}
#endif

// ALTLF
#if SRSS_ALTLF_PRESENT
static bool _cyhal_clock_is_enabled_altlf(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_AltLfIsEnabled();
}
static uint32_t _cyhal_clock_get_frequency_altlf(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_AltLfGetFrequency();
}
#endif

// IHO
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
static bool _cyhal_clock_is_enabled_iho(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_IhoIsEnabled();
}
static cy_rslt_t _cyhal_clock_set_enabled_iho(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(wait_for_lock);

    if (enabled)
        Cy_SysClk_IhoEnable();
    else
        Cy_SysClk_IhoDisable();
    return CY_RSLT_SUCCESS;
}
static uint32_t _cyhal_clock_get_frequency_iho(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return CY_SYSCLK_IHO_FREQ;
}
#endif

// ILO
static bool _cyhal_clock_is_enabled_ilo(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    #if defined(COMPONENT_CAT1C)
    return Cy_SysClk_IloSrcIsEnabled(clock->channel);
    #else
    return Cy_SysClk_IloIsEnabled();
    #endif
}
static cy_rslt_t _cyhal_clock_set_enabled_ilo(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(wait_for_lock);
    #if defined(COMPONENT_CAT1C)
    if (enabled)
    {
        Cy_SysPm_BgRefCtrl(true);
        Cy_WDT_Unlock();
        Cy_SysClk_IloSrcEnable(clock->channel);
        Cy_WDT_Lock();
    }
    else
    {
        Cy_SysPm_BgRefCtrl(false);
        Cy_WDT_Unlock();
        Cy_SysClk_IloSrcDisable(clock->channel);
        Cy_WDT_Lock();
    }
    #else
    if (enabled)
        Cy_SysClk_IloEnable();
    else
        Cy_SysClk_IloDisable();
    #endif
    return CY_RSLT_SUCCESS;
}
static uint32_t _cyhal_clock_get_frequency_ilo(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return CY_SYSCLK_ILO_FREQ;
}

// PILO
#if _CYHAL_SRSS_PILO_PRESENT
static bool _cyhal_clock_is_enabled_pilo(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_PiloIsEnabled();
}
static cy_rslt_t _cyhal_clock_set_enabled_pilo(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(wait_for_lock);

    if (enabled)
        Cy_SysClk_PiloEnable();
    else
        Cy_SysClk_PiloDisable();
    return CY_RSLT_SUCCESS;
}
static uint32_t _cyhal_clock_get_frequency_pilo(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return CY_SYSCLK_PILO_FREQ;
}
#endif

// WCO
#if SRSS_BACKUP_PRESENT
static bool _cyhal_clock_is_enabled_wco(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
#if defined(CY_IP_MXS28SRSS)
    return 0u != (BACKUP_CTL & BACKUP_WCO_CTL_WCO_EN_Msk);
#else
    return 0u != (BACKUP_CTL & BACKUP_CTL_WCO_EN_Msk);
#endif
}
static cy_rslt_t _cyhal_clock_set_enabled_wco(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);

    if (enabled)
    {
        cy_rslt_t rslt = Cy_SysClk_WcoEnable(wait_for_lock ? 1000000UL : 0UL);
        // Ignore CY_SYSCLK_TIMEOUT unless wait_for_lock is true
        return wait_for_lock ? rslt : CY_RSLT_SUCCESS;
    }
    else
    {
        Cy_SysClk_WcoDisable();
        return CY_RSLT_SUCCESS;
    }
}
static uint32_t _cyhal_clock_get_frequency_wco(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return CY_SYSCLK_WCO_FREQ;
}
#endif

// MFO
#if defined(COMPONENT_CAT1B) || (SRSS_MFO_PRESENT)
static bool _cyhal_clock_is_enabled_mfo(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_MfoIsEnabled();
}
static cy_rslt_t _cyhal_clock_set_enabled_mfo(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(wait_for_lock);

    if (enabled)
        Cy_SysClk_MfoEnable(true);
    else
        Cy_SysClk_MfoDisable();
    return CY_RSLT_SUCCESS;
}
static uint32_t _cyhal_clock_get_frequency_mfo(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return CY_SYSCLK_MFO_FREQ;
}
static cy_rslt_t _cyhal_clock_get_sources_mfo(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);

    static const cyhal_resource_inst_t *_CYHAL_CLOCK_SOURCE_MFO[] =
    {
        &CYHAL_CLOCK_RSC_IMO,
    };

    *sources = _CYHAL_CLOCK_SOURCE_MFO;
    *count = sizeof(_CYHAL_CLOCK_SOURCE_MFO) / sizeof(_CYHAL_CLOCK_SOURCE_MFO[0]);
    return CY_RSLT_SUCCESS;
}
#endif

// PathMux
static uint32_t _cyhal_clock_get_frequency_pathmux(const cyhal_clock_t *clock)
{
    return Cy_SysClk_ClkPathMuxGetFrequency(clock->channel);
}
static cy_rslt_t _cyhal_clock_get_sources_pathmux(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);

    static const cyhal_resource_inst_t *_CYHAL_CLOCK_SOURCE_PATHMUX[] =
    {
        &CYHAL_CLOCK_RSC_IMO,
    #if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
        &CYHAL_CLOCK_RSC_IHO,
    #endif
    #if SRSS_ECO_PRESENT
        &CYHAL_CLOCK_RSC_ECO,
    #endif
        &CYHAL_CLOCK_RSC_EXT,
    #if SRSS_ALTHF_PRESENT
        &CYHAL_CLOCK_RSC_ALTHF,
    #endif
    #if defined(COMPONENT_CAT1C)
        &CYHAL_CLOCK_RSC_ILO[0],
        #if (SRSS_HT_VARIANT > 0)
        &CYHAL_CLOCK_RSC_ILO[1],
        #endif
    /* There are no ILO clock available on CAT1D */
    #elif !defined(COMPONENT_CAT1D)
        &CYHAL_CLOCK_RSC_ILO,
    #endif
    #if _CYHAL_SRSS_PILO_PRESENT
        &CYHAL_CLOCK_RSC_PILO,
    #endif
    #if SRSS_BACKUP_PRESENT
        &CYHAL_CLOCK_RSC_WCO,
    #endif
    #if SRSS_ALTLF_PRESENT
        &CYHAL_CLOCK_RSC_ALTLF,
    #endif
    };

    *sources = _CYHAL_CLOCK_SOURCE_PATHMUX;
    *count = sizeof(_CYHAL_CLOCK_SOURCE_PATHMUX) / sizeof(_CYHAL_CLOCK_SOURCE_PATHMUX[0]);
    return CY_RSLT_SUCCESS;
}

static cy_rslt_t _cyhal_clock_set_source_pathmux(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    uint32_t new_freq;
    cy_en_clkpath_in_sources_t clkpath_src;
    switch (source->block)
    {
        case CYHAL_CLOCK_BLOCK_IMO:
            clkpath_src = CY_SYSCLK_CLKPATH_IN_IMO;
            new_freq = CY_SYSCLK_IMO_FREQ;
            break;
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
        case CYHAL_CLOCK_BLOCK_IHO:
            clkpath_src = CY_SYSCLK_CLKPATH_IN_IHO;
            new_freq = CY_SYSCLK_IHO_FREQ;
            break;
#endif
        case CYHAL_CLOCK_BLOCK_EXT:
            clkpath_src = CY_SYSCLK_CLKPATH_IN_EXT;
            new_freq = Cy_SysClk_ExtClkGetFrequency();
            break;
#if SRSS_ECO_PRESENT
        case CYHAL_CLOCK_BLOCK_ECO:
            clkpath_src = CY_SYSCLK_CLKPATH_IN_ECO;
            new_freq = Cy_SysClk_EcoGetFrequency();
            break;
#endif
#if SRSS_ALTHF_PRESENT
        case CYHAL_CLOCK_BLOCK_ALTHF:
            clkpath_src = CY_SYSCLK_CLKPATH_IN_ALTHF;
            new_freq = Cy_SysClk_AltHfGetFrequency();
            break;
#endif
        case CYHAL_CLOCK_BLOCK_ILO:
        #if defined(COMPONENT_CAT1C)
            if (1 == source->channel)
            {
                clkpath_src = CY_SYSCLK_CLKPATH_IN_ILO1;
                new_freq = CY_SYSCLK_ILO_FREQ;
            }
            else
        #endif
            {
                clkpath_src = CY_SYSCLK_CLKPATH_IN_ILO;
                new_freq = CY_SYSCLK_ILO_FREQ;
            }
            break;
#if SRSS_BACKUP_PRESENT
        case CYHAL_CLOCK_BLOCK_WCO:
            clkpath_src = CY_SYSCLK_CLKPATH_IN_WCO;
            new_freq = CY_SYSCLK_WCO_FREQ;
            break;
#endif
#if SRSS_ALTLF_PRESENT
        case CYHAL_CLOCK_BLOCK_ALTLF:
            clkpath_src = CY_SYSCLK_CLKPATH_IN_ALTLF;
            new_freq = Cy_SysClk_AltLfGetFrequency();
            break;
#endif
#if _CYHAL_SRSS_PILO_PRESENT
        case CYHAL_CLOCK_BLOCK_PILO:
            clkpath_src = CY_SYSCLK_CLKPATH_IN_PILO;
            new_freq = CY_SYSCLK_PILO_FREQ;
            break;
#endif
        default:
            CY_ASSERT(false); //Unhandled clock
            return CYHAL_CLOCK_RSLT_ERR_SOURCE;
    }

    uint32_t old_hf_freq = Cy_SysClk_ClkHfGetFrequency(0);
    uint32_t new_hf_freq = new_freq >> ((uint8_t)Cy_SysClk_ClkHfGetDivider(0));
    bool is_sysclk_path = (clock->channel == (uint32_t)Cy_SysClk_ClkHfGetSource(0));

    if (is_sysclk_path)
        _cyhal_clock_update_system_state(true, old_hf_freq, new_hf_freq);

    cy_rslt_t rslt = Cy_SysClk_ClkPathSetSource(clock->channel, clkpath_src);

    if (is_sysclk_path)
    {
        if (CY_RSLT_SUCCESS == rslt)
            _cyhal_clock_update_system_state(false, old_hf_freq, new_hf_freq);
        else // revert the change if there was one
            _cyhal_clock_update_system_state(false, new_hf_freq, old_hf_freq);
    }

    return rslt;
}


// FLL
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C) || (SRSS_FLL_PRESENT)
static bool _cyhal_clock_is_enabled_fll(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_FllIsEnabled();
}
static cy_rslt_t _cyhal_clock_set_enabled_fll(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(wait_for_lock);

    cy_stc_fll_manual_config_t cfg;
    Cy_SysClk_FllGetConfiguration(&cfg);
    uint32_t new_freq, old_freq;
    uint32_t div = (uint32_t)Cy_SysClk_ClkHfGetDivider(0);
    uint32_t src_freq = Cy_SysClk_ClkPathMuxGetFrequency(0);
    uint32_t fll_freq = CY_SYSLIB_DIV_ROUND((uint64_t)src_freq * (uint64_t)cfg.fllMult, (uint32_t)cfg.refDiv * ((cfg.enableOutputDiv) ? 2UL : 1UL));
    if (enabled)
    {
        new_freq = fll_freq >> div;
        old_freq = src_freq >> div;
    }
    else
    {
        new_freq = src_freq >> div;
        old_freq = fll_freq >> div;
    }

    bool fll_sources_hf0 = (0 == (uint32_t)Cy_SysClk_ClkHfGetSource(0));
    if (fll_sources_hf0)
        _cyhal_clock_update_system_state(true, old_freq, new_freq);

    cy_rslt_t rslt = (enabled)
        ? Cy_SysClk_FllEnable(wait_for_lock ? _CYHAL_CLOCK_FLL_LOCK_TIME : 0UL)
        : Cy_SysClk_FllDisable();

    if (fll_sources_hf0)
    {
        if (CY_RSLT_SUCCESS == rslt)
            _cyhal_clock_update_system_state(false, old_freq, new_freq);
        else // revert the change if there was one
            _cyhal_clock_update_system_state(false, new_freq, old_freq);
    }

    return rslt;
}
static uint32_t _cyhal_clock_get_frequency_fll(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_ClkPathGetFrequency(0);
}
static cy_rslt_t _cyhal_clock_set_frequency_fll(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(tolerance);

    cy_rslt_t rslt = CY_RSLT_SUCCESS;
    cy_stc_fll_manual_config_t cfg;
    Cy_SysClk_FllGetConfiguration(&cfg);
    uint32_t src_freq = Cy_SysClk_ClkPathMuxGetFrequency(0);

    if (0 == src_freq)
        rslt = CYHAL_CLOCK_RSLT_ERR_SOURCE;
    else
    {
        uint32_t old_freq = CY_SYSLIB_DIV_ROUND((uint64_t)src_freq * (uint64_t)cfg.fllMult, (uint32_t)cfg.refDiv * ((cfg.enableOutputDiv) ? 2UL : 1UL));
        uint32_t div = (uint32_t)Cy_SysClk_ClkHfGetDivider(0);
        uint32_t old_hf_freq = old_freq >> div;
        uint32_t new_hf_freq = hz /*new_freq*/ >> div;

        bool fll_sources_hf0 = (0 == (uint32_t)Cy_SysClk_ClkHfGetSource(0));
        if (fll_sources_hf0)
            _cyhal_clock_update_system_state(true, old_hf_freq, new_hf_freq);

        bool enabled = Cy_SysClk_FllIsEnabled();
        if (enabled)
            rslt = Cy_SysClk_FllDisable();
        if (CY_RSLT_SUCCESS == rslt)
        {
            rslt = Cy_SysClk_FllConfigure(src_freq, hz/*new_freq*/, CY_SYSCLK_FLLPLL_OUTPUT_AUTO);

            if (enabled)
            {
                cy_rslt_t rslt2 = Cy_SysClk_FllEnable(_CYHAL_CLOCK_FLL_LOCK_TIME);
                if (CY_RSLT_SUCCESS == rslt)
                    rslt = rslt2;
            }
        }

        if (fll_sources_hf0)
        {
            if (CY_RSLT_SUCCESS == rslt)
                _cyhal_clock_update_system_state(false, old_hf_freq, new_hf_freq);
            else // revert the change if there was one
                _cyhal_clock_update_system_state(false, new_hf_freq, old_hf_freq);
        }
    }

    return rslt;
}
static cy_rslt_t _cyhal_clock_get_sources_fll(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);
    *sources = &(_CYHAL_CLOCK_SOURCE_HF[1 + _CYHAL_SRSS_NUM_PLL]);
    *count = 1;
    return CY_RSLT_SUCCESS;
}
#endif

// PLL
#if (_CYHAL_SRSS_NUM_PLL > 0)
static bool _cyhal_clock_is_enabled_pll(const cyhal_clock_t *clock)
{
    #if defined(COMPONENT_CAT1C)
    if (clock->block == CYHAL_CLOCK_BLOCK_PLL200)
    {
        return Cy_SysClk_PllIsEnabled(clock->channel + 1 + SRSS_NUM_PLL400M);
    }
    #endif
    return Cy_SysClk_PllIsEnabled(clock->channel + 1);
}

static void _cyhal_clock_extract_pll_params(cyhal_clock_t *clock, cy_stc_pll_manual_config_t *cfg, uint64_t *feedbackDiv,
        uint32_t *referenceDiv, uint32_t *outputDiv)
{
    #if defined (CY_IP_MXS40SRSS)
    *feedbackDiv = cfg->feedbackDiv;
    *referenceDiv = cfg->referenceDiv;
    *outputDiv = cfg->outputDiv;
    CY_UNUSED_PARAMETER(clock);
    #elif defined (CY_IP_MXS22SRSS)
    if (clock->block == CYHAL_CLOCK_BLOCK_DPLL_LP)
    {
        *feedbackDiv = cfg->lpPllCfg->feedbackDiv;
        *referenceDiv = cfg->lpPllCfg->referenceDiv;
        *outputDiv = cfg->lpPllCfg->outputDiv;
    }
    else if (clock->block == CYHAL_CLOCK_BLOCK_DPLL_HP)
    {
        /* Per IP block documentation, each divider requires +1 for correct output clock calculation */
        *feedbackDiv = cfg->hpPllCfg->nDiv + 1;
        *referenceDiv = cfg->hpPllCfg->pDiv + 1;
        *outputDiv = cfg->hpPllCfg->kDiv + 1;
    }
    #else
        #error "Unhandled SRSS block type"
    #endif /* defined (CY_IP_MXS40SRSS) or defined (CY_IP_MXS22SRSS) or other (error) */
}

static cy_rslt_t _cyhal_clock_set_enabled_pll(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(wait_for_lock);

    //pll_idx is the path mux index (eg PLL number + 1) as used by PDL APIs
    uint32_t pll_idx = clock->channel + 1;
    #if defined(COMPONENT_CAT1C)
    if (clock->block == CYHAL_CLOCK_BLOCK_PLL200)
    {
        pll_idx = pll_idx + SRSS_NUM_PLL400M;
    }
    #endif
    cy_stc_pll_manual_config_t cfg;
    cy_rslt_t rslt = Cy_SysClk_PllGetConfiguration(pll_idx, &cfg);
    if (CY_RSLT_SUCCESS == rslt)
    {
        uint32_t new_freq, old_freq;
        uint32_t div = (uint32_t)Cy_SysClk_ClkHfGetDivider(0);
        uint32_t src_freq = Cy_SysClk_ClkPathMuxGetFrequency(pll_idx);

        uint64_t feedbackDiv = 0;
        uint32_t referenceDiv = 0;
        uint32_t outputDiv = 0;
        _cyhal_clock_extract_pll_params(clock, &cfg, &feedbackDiv, &referenceDiv, &outputDiv);

        uint32_t pll_freq = CY_SYSLIB_DIV_ROUND((uint64_t)src_freq * feedbackDiv, referenceDiv * outputDiv);

        if (enabled)
        {
            new_freq = pll_freq >> div;
            old_freq = src_freq >> div;
        }
        else
        {
            new_freq = src_freq >> div;
            old_freq = pll_freq >> div;
        }

        bool pll_sources_hf0 = (pll_idx == (uint32_t)Cy_SysClk_ClkHfGetSource(0));
        if (pll_sources_hf0)
            _cyhal_clock_update_system_state(true, old_freq, new_freq);

        rslt = (enabled)
            ? Cy_SysClk_PllEnable(pll_idx, wait_for_lock ? _CYHAL_CLOCK_PLL_LOCK_TIME : 0UL)
            : Cy_SysClk_PllDisable(pll_idx);

        if (pll_sources_hf0)
        {
            if (CY_RSLT_SUCCESS == rslt)
                _cyhal_clock_update_system_state(false, old_freq, new_freq);
            else // revert the change if there was one
                _cyhal_clock_update_system_state(false, new_freq, old_freq);
        }
    }

    return rslt;
}
static uint32_t _cyhal_clock_get_frequency_pll(const cyhal_clock_t *clock)
{
    #if defined(COMPONENT_CAT1C)
    if (clock->block == CYHAL_CLOCK_BLOCK_PLL200)
    {
        return Cy_SysClk_ClkPathGetFrequency(clock->channel + 1 + SRSS_NUM_PLL400M);
    }
    #endif
    return Cy_SysClk_ClkPathGetFrequency(clock->channel + 1);
}
static cy_rslt_t _cyhal_clock_set_frequency_pll(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_UNUSED_PARAMETER(tolerance);

    cy_stc_pll_manual_config_t cfg;
    uint8_t pll_idx = clock->channel + 1;
    #if defined(COMPONENT_CAT1C)
    if (clock->block == CYHAL_CLOCK_BLOCK_PLL200)
    {
        pll_idx = pll_idx + SRSS_NUM_PLL400M;
    }
    #endif
    cy_rslt_t rslt = Cy_SysClk_PllGetConfiguration(pll_idx, &cfg);
    if (CY_RSLT_SUCCESS == rslt)
    {
        bool enabled = Cy_SysClk_PllIsEnabled(pll_idx);
        if (enabled)
            rslt = Cy_SysClk_PllDisable(pll_idx);
        if (CY_RSLT_SUCCESS == rslt)
        {
            uint32_t src_freq = Cy_SysClk_ClkPathMuxGetFrequency(pll_idx);

            uint64_t feedbackDiv = 0;
            uint32_t referenceDiv = 0;
            uint32_t outputDiv = 0;
            _cyhal_clock_extract_pll_params(clock, &cfg, &feedbackDiv, &referenceDiv, &outputDiv);

            uint32_t old_freq = CY_SYSLIB_DIV_ROUND((uint64_t)src_freq * feedbackDiv, referenceDiv * outputDiv);

            uint32_t div = (uint32_t)Cy_SysClk_ClkHfGetDivider(0);
            uint32_t old_hf_freq = old_freq >> div;
            uint32_t new_hf_freq = hz/*new_freq*/ >> div;

            bool pll_sources_hf0 = (pll_idx == (uint32_t)Cy_SysClk_ClkHfGetSource(0));
            if (pll_sources_hf0)
                _cyhal_clock_update_system_state(true, old_hf_freq, new_hf_freq);

            uint32_t input_hz = Cy_SysClk_ClkPathMuxGetFrequency(pll_idx);
            cy_stc_pll_config_t cfg2 =
            {
                .inputFreq = input_hz,
                .outputFreq = hz/*new_freq*/,
                .lfMode = false,
                .outputMode = CY_SYSCLK_FLLPLL_OUTPUT_AUTO,
            };
            rslt = Cy_SysClk_PllConfigure(pll_idx, &cfg2);

            if (enabled)
            {
                cy_rslt_t rslt2 = Cy_SysClk_PllEnable(pll_idx, _CYHAL_CLOCK_PLL_LOCK_TIME);
                if (CY_RSLT_SUCCESS == rslt)
                    rslt = rslt2;
            }

            if (pll_sources_hf0)
            {
                if (CY_RSLT_SUCCESS == rslt)
                    _cyhal_clock_update_system_state(false, old_hf_freq, new_hf_freq);
                else // revert the change if there was one
                    _cyhal_clock_update_system_state(false, new_hf_freq, old_hf_freq);
            }
        }
    }

    return rslt;
}
static cy_rslt_t _cyhal_clock_get_sources_pll(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    // _CYHAL_CLOCK_SOURCE_HF has entries for FLL, PLL[n], PathMux[m]
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C) || (SRSS_FLL_PRESENT)
    #if defined(COMPONENT_CAT1C)
    uint8_t channel = clock->channel;
    if (clock->block == CYHAL_CLOCK_BLOCK_PLL200)
    {
        channel = channel + SRSS_NUM_PLL400M;
    }
    *sources = &(_CYHAL_CLOCK_SOURCE_HF[2 + _CYHAL_SRSS_NUM_PLL + channel]);
    #endif
    *sources = &(_CYHAL_CLOCK_SOURCE_HF[2 + _CYHAL_SRSS_NUM_PLL + clock->channel]); /* PATHMUX[n] entry is after the FLL (+1), PLLs (+num) and FLL path mux (+1) */
#else
    *sources = &(_CYHAL_CLOCK_SOURCE_HF[_CYHAL_SRSS_NUM_PLL + clock->channel]); /* PATHMUX[n] entry is after the PLLs (+num) */
#endif
    *count = 1;
    return CY_RSLT_SUCCESS;
}
#endif

// MF
#if defined(COMPONENT_CAT1B) || (SRSS_MFO_PRESENT)
static bool _cyhal_clock_is_enabled_mf(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_ClkMfIsEnabled();
}
static cy_rslt_t _cyhal_clock_set_enabled_mf(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(wait_for_lock);

    if (enabled)
        Cy_SysClk_ClkMfEnable();
    else
        Cy_SysClk_ClkMfDisable();
    return CY_RSLT_SUCCESS;
}
static uint32_t _cyhal_clock_get_frequency_mf(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_ClkMfGetFrequency();
}
static cy_rslt_t _cyhal_clock_set_frequency_mf(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_UNUSED_PARAMETER(clock);

    uint32_t div;
    cy_rslt_t rslt = _cyhal_clock_compute_div(CY_SYSCLK_MFO_FREQ, hz, 8, tolerance, &div);

    if(false == CY_SYSCLK_IS_MF_DIVIDER_VALID(div))
        rslt = CYHAL_CLOCK_RSLT_ERR_FREQ;

    if (CY_RSLT_SUCCESS == rslt)
        Cy_SysClk_ClkMfSetDivider(div);

    return rslt;
}
static cy_rslt_t _cyhal_clock_set_divider_mf(cyhal_clock_t *clock, uint32_t divider)
{
    CY_UNUSED_PARAMETER(clock);

    if (divider <= 256)
    {
        Cy_SysClk_ClkMfSetDivider(divider);
        return CY_RSLT_SUCCESS;
    }
    return CYHAL_CLOCK_RSLT_ERR_FREQ;
}
static cy_rslt_t _cyhal_clock_get_sources_mf(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);

    static const cyhal_resource_inst_t *_CYHAL_CLOCK_SOURCE_MF[] =
    {
        &CYHAL_CLOCK_RSC_MFO,
    #if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D) /* CAT1A only supports driving from the MFO */
        &CYHAL_CLOCK_RSC_ILO,
    #if SRSS_BACKUP_PRESENT
        &CYHAL_CLOCK_RSC_WCO,
    #endif
    #if _CYHAL_SRSS_PILO_PRESENT
        &CYHAL_CLOCK_RSC_PILO,
    #endif
    #if SRSS_ALTLF_PRESENT
        &CYHAL_CLOCK_RSC_ALTLF,
    #endif
    #if SRSS_ECO_PRESENT
        &CYHAL_CLOCK_RSC_ECO_PRESCALER,
    #endif
    #if SRSS_BACKUP_S40E_LPECO_PRESENT
        &CYHAL_CLOCK_RSC_LPECO_PRESCALER,
    #endif
    #endif /* defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D) */
    };

    *sources = _CYHAL_CLOCK_SOURCE_MF;
    *count = sizeof(_CYHAL_CLOCK_SOURCE_MF) / sizeof(_CYHAL_CLOCK_SOURCE_MF[0]);
    return CY_RSLT_SUCCESS;
}
static cy_rslt_t _cyhal_clock_set_source_mf(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    CY_UNUSED_PARAMETER(clock);

    switch(source->block)
    {
        case CYHAL_CLOCK_BLOCK_MFO:
            Cy_SysClk_ClkMfSetSource(CY_SYSCLK_CLKMF_IN_MFO);
            return CY_RSLT_SUCCESS;
        case CYHAL_CLOCK_BLOCK_ILO:
            Cy_SysClk_ClkMfSetSource(CY_SYSCLK_CLKMF_IN_ILO);
            return CY_RSLT_SUCCESS;
#if SRSS_BACKUP_PRESENT
        case CYHAL_CLOCK_BLOCK_WCO:
            Cy_SysClk_ClkMfSetSource(CY_SYSCLK_CLKMF_IN_WCO);
            return CY_RSLT_SUCCESS;
#endif
#if _CYHAL_SRSS_PILO_PRESENT
        case CYHAL_CLOCK_BLOCK_PILO:
            Cy_SysClk_ClkMfSetSource(CY_SYSCLK_CLKMF_IN_PILO);
            return CY_RSLT_SUCCESS;
#endif
#if SRSS_ALTLF_PRESENT
        case CYHAL_CLOCK_BLOCK_ALTLF:
            Cy_SysClk_ClkMfSetSource(CY_SYSCLK_CLKMF_IN_ALTLF);
            return CY_RSLT_SUCCESS;
#endif
#if SRSS_ECO_PRESENT
        case CYHAL_CLOCK_BLOCK_ECO_PRESCALER:
            Cy_SysClk_ClkMfSetSource(CY_SYSCLK_CLKMF_IN_ECO_PRESCALER);
            return CY_RSLT_SUCCESS;
#endif
#if SRSS_BACKUP_S40E_LPECO_PRESENT
        case CYHAL_CLOCK_BLOCK_LPECO_PRESCALER:
            Cy_SysClk_ClkMfSetSource(CY_SYSCLK_CLKMF_IN_LPECO);
            return CY_RSLT_SUCCESS;
#endif
        default:
            CY_ASSERT(false); //Unhandled clock
            return CYHAL_CLOCK_RSLT_ERR_SOURCE;
    }
}
#endif

// HF
static bool _cyhal_clock_is_enabled_hf(const cyhal_clock_t *clock)
{
    return Cy_SysClk_ClkHfIsEnabled(clock->channel);
}
static cy_rslt_t _cyhal_clock_set_enabled_hf(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(wait_for_lock);

    return (enabled)
        ? Cy_SysClk_ClkHfEnable(clock->channel)
        : Cy_SysClk_ClkHfDisable(clock->channel);
}
static uint32_t _cyhal_clock_get_frequency_hf(const cyhal_clock_t *clock)
{
    return Cy_SysClk_ClkHfGetFrequency(clock->channel);
}
static cy_rslt_t _cyhal_clock_set_divider_hf(cyhal_clock_t *clock, uint32_t divider)
{
    cy_en_clkhf_dividers_t new_div;
    switch (divider)
    {
        case 1:
            new_div = CY_SYSCLK_CLKHF_NO_DIVIDE;
            break;
        case 2:
            new_div = CY_SYSCLK_CLKHF_DIVIDE_BY_2;
            break;
        case 4:
            new_div = CY_SYSCLK_CLKHF_DIVIDE_BY_4;
            break;
        case 8:
            new_div = CY_SYSCLK_CLKHF_DIVIDE_BY_8;
            break;
        default:
            return CYHAL_CLOCK_RSLT_ERR_FREQ;
    }

    /* Only used if updating HFClk 0 */
    uint32_t old_div = (uint32_t)Cy_SysClk_ClkHfGetDivider(0);
    uint32_t src = (uint32_t)Cy_SysClk_ClkHfGetSource(0);
    uint32_t path_freq = Cy_SysClk_ClkPathGetFrequency(src);
    uint32_t old_freq = path_freq >> old_div;
    uint32_t new_freq = path_freq >> ((uint32_t)new_div);

    if (0 == clock->channel)
        _cyhal_clock_update_system_state(true, old_freq, new_freq);

    cy_rslt_t rslt = (cy_rslt_t)Cy_SysClk_ClkHfSetDivider(clock->channel, new_div);

    if (0 == clock->channel)
    {
        if (CY_RSLT_SUCCESS == rslt)
            _cyhal_clock_update_system_state(false, old_freq, new_freq);
        else // revert the change if there was one
            _cyhal_clock_update_system_state(false, new_freq, old_freq);
    }

    return rslt;
}
static cy_rslt_t _cyhal_clock_get_sources_hf(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);
    *sources = _CYHAL_CLOCK_SOURCE_HF;
    *count = sizeof(_CYHAL_CLOCK_SOURCE_HF) / sizeof(_CYHAL_CLOCK_SOURCE_HF[0]);
    return CY_RSLT_SUCCESS;
}
static cy_rslt_t _cyhal_clock_set_source_hf(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    uint32_t new_src;
    if (source->block == CYHAL_CLOCK_BLOCK_PATHMUX || source->block == CYHAL_CLOCK_BLOCK_FLL)
        new_src = source->channel;
#if defined(COMPONENT_CAT1A)
    else if (source->block == CYHAL_CLOCK_BLOCK_PLL)
#elif defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
    else if ((source->block == CYHAL_CLOCK_BLOCK_PLL200) || (source->block == CYHAL_CLOCK_BLOCK_PLL400))
#elif defined(COMPONENT_CAT1D)
    else if ((source->block == CYHAL_CLOCK_BLOCK_DPLL_LP) || (source->block == CYHAL_CLOCK_BLOCK_DPLL_HP))
#endif
    {
        new_src = source->channel + 1;
#if defined(SRSS_NUM_PLL400M) && (defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C))
        if (source->block == CYHAL_CLOCK_BLOCK_PLL200)
        {
            /* As PLL200 and PLL400 has their own channels and PLL400 sits on lower PATH_MUX numbers
             * we need to increase calculated source num with respect to number of PLL400's */
            new_src += SRSS_NUM_PLL400M;
        }
#endif /* defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) */
    }
    else
        return CYHAL_CLOCK_RSLT_ERR_SOURCE;

    /* Only used if updating HFClk 0 */
    uint32_t div_hf0 = (uint32_t)Cy_SysClk_ClkHfGetDivider(0);
    uint32_t old_src_hf0 = (uint32_t)Cy_SysClk_ClkHfGetSource(0);
    uint32_t old_freq_hf0 = Cy_SysClk_ClkPathGetFrequency(old_src_hf0) >> div_hf0;
    uint32_t new_freq_hf0 = Cy_SysClk_ClkPathGetFrequency(new_src) >> div_hf0;

    if (0 == clock->channel)
        _cyhal_clock_update_system_state(true, old_freq_hf0, new_freq_hf0);

    cy_rslt_t rslt = Cy_SysClk_ClkHfSetSource(clock->channel, (cy_en_clkhf_in_sources_t)new_src);

    if (0 == clock->channel)
    {
        if (CY_RSLT_SUCCESS == rslt)
            _cyhal_clock_update_system_state(false, old_freq_hf0, new_freq_hf0);
        else // revert the change if there was one
            _cyhal_clock_update_system_state(false, new_freq_hf0, old_freq_hf0);
    }

    return rslt;
}

// LF
static uint32_t _cyhal_clock_get_frequency_lf(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return _cyhal_clock_get_lf_frequency();
}
static cy_rslt_t _cyhal_clock_get_sources_lf(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);

    static const cyhal_resource_inst_t *_CYHAL_CLOCK_SOURCE_LF[] =
    {
    #if defined(COMPONENT_CAT1C)
        &CYHAL_CLOCK_RSC_ILO[0],
        #if (SRSS_HT_VARIANT > 0)
        &CYHAL_CLOCK_RSC_ILO[1],
        #endif
    /* There are no ILO clock available on CAT1D */
    #elif !defined(COMPONENT_CAT1D)
        &CYHAL_CLOCK_RSC_ILO,
    #endif
    #if _CYHAL_SRSS_PILO_PRESENT
        &CYHAL_CLOCK_RSC_PILO,
    #endif
    #if SRSS_BACKUP_PRESENT
        &CYHAL_CLOCK_RSC_WCO,
    #endif
    #if SRSS_ALTLF_PRESENT
        &CYHAL_CLOCK_RSC_ALTLF,
    #endif
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
#if SRSS_ECO_PRESENT
        &CYHAL_CLOCK_RSC_ECO_PRESCALER,
#endif
#if SRSS_BACKUP_S40E_LPECO_PRESENT
        &CYHAL_CLOCK_RSC_LPECO_PRESCALER,
#endif
#endif
    };

    *sources = _CYHAL_CLOCK_SOURCE_LF;
    *count = sizeof(_CYHAL_CLOCK_SOURCE_LF) / sizeof(_CYHAL_CLOCK_SOURCE_LF[0]);
    return CY_RSLT_SUCCESS;
}
static cy_rslt_t _cyhal_clock_set_source_lf(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    CY_UNUSED_PARAMETER(clock);
    cy_rslt_t result = CY_RSLT_SUCCESS;
    #if defined(COMPONENT_CAT1C)
    Cy_WDT_Unlock();
    #endif
    switch (source->block)
    {
        case CYHAL_CLOCK_BLOCK_ILO:
        #if defined(COMPONENT_CAT1C)
            if(1 == source->channel)
            {
                Cy_SysClk_ClkLfSetSource(CY_SYSCLK_CLKLF_IN_ILO1);
            }
            else
        #endif
            {
                Cy_SysClk_ClkLfSetSource(CY_SYSCLK_CLKLF_IN_ILO);
            }
            break;
#if SRSS_BACKUP_PRESENT
        case CYHAL_CLOCK_BLOCK_WCO:
            Cy_SysClk_ClkLfSetSource(CY_SYSCLK_CLKLF_IN_WCO);
            break;
#endif
#if SRSS_ALTLF_PRESENT
        case CYHAL_CLOCK_BLOCK_ALTLF:
            Cy_SysClk_ClkLfSetSource(CY_SYSCLK_CLKLF_IN_ALTLF);
            break;
#endif
#if _CYHAL_SRSS_PILO_PRESENT
        case CYHAL_CLOCK_BLOCK_PILO:
            Cy_SysClk_ClkLfSetSource(CY_SYSCLK_CLKLF_IN_PILO);
            break;
#endif
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
#if SRSS_ECO_PRESENT
        case CYHAL_CLOCK_BLOCK_ECO_PRESCALER:
            Cy_SysClk_ClkLfSetSource(CY_SYSCLK_CLKLF_IN_ECO_PRESCALER);
            break;
#endif
#if SRSS_BACKUP_S40E_LPECO_PRESENT
        case CYHAL_CLOCK_BLOCK_LPECO_PRESCALER:
            Cy_SysClk_ClkLfSetSource(CY_SYSCLK_CLKLF_IN_LPECO_PRESCALER);
            break;
#endif
#endif
        default:
            CY_ASSERT(false); //Unhandled clock
            result = CYHAL_CLOCK_RSLT_ERR_SOURCE;
    }
    #if defined(COMPONENT_CAT1C)
    Cy_WDT_Lock();
    #endif
    return result;
}

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
// FAST
static uint32_t _cyhal_clock_get_frequency_fast(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    #if defined(COMPONENT_CAT1A)
    return Cy_SysClk_ClkFastGetFrequency();
    #else
    return Cy_SysClk_ClkFastSrcGetFrequency(clock->channel);
    #endif
}
static cy_rslt_t _cyhal_clock_set_frequency_fast(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_UNUSED_PARAMETER(clock);

    uint32_t div;
    cy_rslt_t rslt;
    #if defined(COMPONENT_CAT1A)
    uint32_t input_hz = Cy_SysClk_ClkHfGetFrequency(0);
    rslt = _cyhal_clock_compute_div((uint64_t)input_hz, hz, 8, tolerance, &div);
    #else
    uint32_t input_hz = Cy_SysClk_ClkHfGetFrequency(1);
    rslt = _cyhal_clock_compute_div(((uint64_t)input_hz) << 5, hz, 13, tolerance, &div);
    #endif

    if (CY_RSLT_SUCCESS == rslt)
    {
        #if defined(COMPONENT_CAT1A)
        Cy_SysClk_ClkFastSetDivider((uint8_t)(div - 1));
        #else
        uint32_t div_int = (div >> 5) - 1;
        uint32_t div_frac = div & 0x1F;
        Cy_SysClk_ClkFastSrcSetDivider(clock->channel, (uint8_t)div_int, (uint8_t)div_frac);
        Cy_SysLib_SetWaitStates(false, 340);
        #endif
        SystemCoreClockUpdate();
    }
    return rslt;
}
static cy_rslt_t _cyhal_clock_set_divider_fast(cyhal_clock_t *clock, uint32_t divider)
{
    CY_UNUSED_PARAMETER(clock);

    if (divider <= 256)
    {
        uint32_t divVal = divider - 1;
        #if defined(COMPONENT_CAT1A)
        Cy_SysClk_ClkFastSetDivider((uint8_t)divVal);
        #else
        Cy_SysClk_ClkFastSrcSetDivider(clock->channel, (uint8_t)divVal, 0);
        #endif
        SystemCoreClockUpdate();
        return CY_RSLT_SUCCESS;
    }
    return CYHAL_CLOCK_RSLT_ERR_FREQ;
}
static cy_rslt_t _cyhal_clock_get_sources_fast(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);

    static const cyhal_resource_inst_t *_CYHAL_CLOCK_SOURCE_FAST[] =
    {
        #if defined(COMPONENT_CAT1C)
        &CYHAL_CLOCK_RSC_HF[1],
        #else
        &CYHAL_CLOCK_RSC_HF[0],
        #endif
    };

    *sources = _CYHAL_CLOCK_SOURCE_FAST;
    *count = sizeof(_CYHAL_CLOCK_SOURCE_FAST) / sizeof(_CYHAL_CLOCK_SOURCE_FAST[0]);
    return CY_RSLT_SUCCESS;
}

// SLOW
static uint32_t _cyhal_clock_get_frequency_slow(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_ClkSlowGetFrequency();
}
static cy_rslt_t _cyhal_clock_set_frequency_slow(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_UNUSED_PARAMETER(clock);

    uint32_t div;
    uint32_t input_hz = Cy_SysClk_ClkPeriGetFrequency();
    cy_rslt_t rslt = _cyhal_clock_compute_div((uint64_t)input_hz, hz, 8, tolerance, &div);

    if (CY_RSLT_SUCCESS == rslt)
    {
        Cy_SysClk_ClkSlowSetDivider((uint8_t)(div - 1));
        SystemCoreClockUpdate();
    }

    return rslt;
}
static cy_rslt_t _cyhal_clock_set_divider_slow(cyhal_clock_t *clock, uint32_t divider)
{
    CY_UNUSED_PARAMETER(clock);

    if (divider <= 256)
    {
        uint32_t divVal = divider - 1;
        Cy_SysClk_ClkSlowSetDivider((uint8_t)divVal);
        SystemCoreClockUpdate();
        return CY_RSLT_SUCCESS;
    }
    return CYHAL_CLOCK_RSLT_ERR_FREQ;
}
static cy_rslt_t _cyhal_clock_get_sources_slow(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);
    static const cyhal_resource_inst_t *_CYHAL_CLOCK_SOURCE_SLOW[] =
    {
        #if defined(COMPONENT_CAT1A)
        &CYHAL_CLOCK_RSC_PERI,
        #else
        &CYHAL_CLOCK_RSC_MEM,
        #endif
    };

    *sources = _CYHAL_CLOCK_SOURCE_SLOW;
    *count = sizeof(_CYHAL_CLOCK_SOURCE_SLOW) / sizeof(_CYHAL_CLOCK_SOURCE_SLOW[0]);
    return CY_RSLT_SUCCESS;
}
#endif
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
#if SRSS_ECO_PRESENT
// ECO_PRESCALER - NOTE: This clock is not supported on any device yet
static uint32_t _cyhal_clock_get_frequency_eco_prescaler(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    //return Cy_SysClk_EcoPrescalerGetFrequency();
    return 0;
}
static cy_rslt_t _cyhal_clock_set_divider_eco_prescaler(cyhal_clock_t *clock, uint32_t divider)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(divider);

    return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
}
static cy_rslt_t _cyhal_clock_get_sources_eco_prescaler(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(sources);
    CY_UNUSED_PARAMETER(count);

    return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
}
#endif

#if SRSS_BACKUP_S40E_LPECO_PRESENT
// LPECO_PRESCALER - NOTE: This clock is not supported on any device yet
static uint32_t _cyhal_clock_get_frequency_lpeco_prescaler(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_LpEcoPrescalerGetFrequency();
}
static cy_rslt_t _cyhal_clock_set_divider_lpeco_prescaler(cyhal_clock_t *clock, uint32_t divider)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(divider);

    return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
}
static cy_rslt_t _cyhal_clock_get_sources_lpeco_prescaler(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(sources);
    CY_UNUSED_PARAMETER(count);

    return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
}
#endif
#endif

// MEM
#if defined(COMPONENT_CAT1C)
static cy_rslt_t _cyhal_clock_set_divider_mem(cyhal_clock_t *clock, uint32_t divider)
{
    CY_UNUSED_PARAMETER(clock);
    if (divider <= 256)
    {
        uint32_t divVal = divider - 1;
        Cy_SysClk_ClkMemSetDivider((uint8_t)divVal);
        SystemCoreClockUpdate();
        return CY_RSLT_SUCCESS;
    }
    return CYHAL_CLOCK_RSLT_ERR_FREQ;
}
static uint32_t _cyhal_clock_get_frequency_mem(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_ClkMemGetFrequency();
}
static cy_rslt_t _cyhal_clock_set_frequency_mem(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_UNUSED_PARAMETER(clock);

    uint32_t div;
    uint32_t input_hz = Cy_SysClk_ClkHfGetFrequency(0);
    cy_rslt_t rslt = _cyhal_clock_compute_div((uint64_t)input_hz, hz, 8, tolerance, &div);
    if (CY_RSLT_SUCCESS == rslt)
    {
        Cy_SysClk_ClkMemSetDivider((uint8_t)(div - 1));
        SystemCoreClockUpdate();
    }
    return rslt;
}
static cy_rslt_t _cyhal_clock_get_sources_mem(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);

    static const cyhal_resource_inst_t *_CYHAL_CLOCK_SOURCE_MEM[] =
    {
        &CYHAL_CLOCK_RSC_HF[0],
    };
    *sources = _CYHAL_CLOCK_SOURCE_MEM;
    *count = 1;
    return CY_RSLT_SUCCESS;
}
#endif

// PERI
static uint32_t _cyhal_clock_get_frequency_peri(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
#if defined(COMPONENT_CAT1C)
    if(clock->channel == 0)
#endif
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
    {
        return Cy_SysClk_ClkPeriGetFrequency();
    }
#endif
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
    #if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
    uint8_t hfclk = _cyhal_utils_get_hfclk_for_peri_group(clock->channel);
    #elif defined(COMPONENT_CAT1D)
    uint8_t instance = _CYHAL_PERIPHERAL_CLOCK_GET_INSTANCE(clock->block);
    uint8_t group = _CYHAL_PERIPHERAL_CLOCK_GET_GROUP(clock->block);
    uint8_t hfclk = _cyhal_utils_get_hfclk_for_peri_group(_CYHAL_UTILS_PACK_INSTANCE_GROUP(instance, group));
    #endif /* defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) or defined(COMPONENT_CAT1D) or other */
    return Cy_SysClk_ClkHfGetFrequency(hfclk) / (Cy_SysClk_PeriGroupGetDivider(clock->channel) + 1);
#endif /* defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D) */
}
static cy_rslt_t _cyhal_clock_set_frequency_peri(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_UNUSED_PARAMETER(clock);

    uint32_t div;
    cy_rslt_t rslt;
#if defined(COMPONENT_CAT1C)
    if(clock->channel == 0)
#endif
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
    {
        uint32_t input_hz = Cy_SysClk_ClkHfGetFrequency(0);
        rslt = _cyhal_clock_compute_div((uint64_t)input_hz, hz, 8, tolerance, &div);

        if (CY_RSLT_SUCCESS == rslt)
        {
            Cy_SysClk_ClkPeriSetDivider((uint8_t)(div - 1));
            SystemCoreClockUpdate();
        }
        return rslt;
    }
#endif
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
    #if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
    uint32_t input_hz = Cy_SysClk_ClkHfGetFrequency(clock->channel == 1 ? 1 : 0);
    #elif defined(COMPONENT_CAT1D)
    uint8_t instance = _CYHAL_PERIPHERAL_CLOCK_GET_INSTANCE(clock->block);
    uint8_t group = _CYHAL_PERIPHERAL_CLOCK_GET_GROUP(clock->block);
    uint32_t input_hz = Cy_SysClk_ClkHfGetFrequency(_cyhal_utils_get_hfclk_for_peri_group(_CYHAL_UTILS_PACK_INSTANCE_GROUP(instance, group)));
    #endif /* defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) or defined(COMPONENT_CAT1D) */
    rslt = _cyhal_clock_compute_div((uint64_t)input_hz, hz, 8, tolerance, &div);


    if (CY_RSLT_SUCCESS == rslt)
    {
        uint32_t group_num = clock->channel;
        #if defined(COMPONENT_CAT1D)
        /* I'm not completely confident in line below */
        group_num += _VAL2FLD(PERI_GR_INST_NUM, instance);
        #endif /* defined(COMPONENT_CAT1D) or other */
        Cy_SysClk_PeriGroupSetDivider(group_num, (uint8_t)(div - 1));
    }
    return rslt;
#endif /* defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D) */
}
static cy_rslt_t _cyhal_clock_set_divider_peri(cyhal_clock_t *clock, uint32_t divider)
{
    CY_UNUSED_PARAMETER(clock);
    if (divider <= 256)
    {
        uint32_t divVal = divider - 1;
    #if defined(COMPONENT_CAT1C)
        if (clock->channel == 0)
    #endif
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
        {
            Cy_SysClk_ClkPeriSetDivider((uint8_t)divVal);
            SystemCoreClockUpdate();
            return CY_RSLT_SUCCESS;
        }
#endif
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
        Cy_SysClk_PeriGroupSetDivider(clock->channel, (uint8_t)divVal);
        SystemCoreClockUpdate();
        return CY_RSLT_SUCCESS;
#endif
    }
    return CYHAL_CLOCK_RSLT_ERR_FREQ;
}
static cy_rslt_t _cyhal_clock_get_sources_peri(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
#if defined(COMPONENT_CAT1A)
    CY_UNUSED_PARAMETER(clock);
#endif
#if defined(COMPONENT_CAT1C)
    if (clock->channel == 0)
#endif
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
    {
        static const cyhal_resource_inst_t *_CYHAL_CLOCK_SOURCE_PERI[] =
        {
            &CYHAL_CLOCK_RSC_HF[0],
        };

        *sources = _CYHAL_CLOCK_SOURCE_PERI;
        *count = 1;
        return CY_RSLT_SUCCESS;
    }
#endif

#if defined (COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
#if !defined(COMPONENT_CAT1D)
    uint8_t hfclk = _cyhal_utils_get_hfclk_for_peri_group(clock->channel);
#else /* defined(COMPONENT_CAT1D) */
    uint8_t instance = _CYHAL_PERIPHERAL_CLOCK_GET_INSTANCE(clock->block);
    uint8_t group = _CYHAL_PERIPHERAL_CLOCK_GET_GROUP(clock->block);
    uint8_t hfclk = _cyhal_utils_get_hfclk_for_peri_group(_CYHAL_UTILS_PACK_INSTANCE_GROUP(instance, group));
#endif /* !defined(COMPONENT_CAT1D) or other */
    return _cyhal_clock_get_sources_peri_peripheral(hfclk, sources, count);
#endif
}

// PUMP (only available on CAT1A and CAT1B devices)
#if defined (COMPONENT_CAT1A) || defined (COMPONENT_CAT1B)
static bool _cyhal_clock_is_enabled_pump(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_ClkPumpIsEnabled();
}
static cy_rslt_t _cyhal_clock_set_enabled_pump(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(wait_for_lock);

    if (enabled)
        Cy_SysClk_ClkPumpEnable();
    else
        Cy_SysClk_ClkPumpDisable();
    return CY_RSLT_SUCCESS;
}
static uint32_t _cyhal_clock_get_frequency_pump(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_ClkPumpGetFrequency();
}
static cy_rslt_t _cyhal_clock_set_divider_pump(cyhal_clock_t *clock, uint32_t divider)
{
    CY_UNUSED_PARAMETER(clock);

    cy_en_clkpump_divide_t divVal;
    switch (divider)
    {
        case 1:
            divVal = CY_SYSCLK_PUMP_NO_DIV;
            break;
        case 2:
            divVal = CY_SYSCLK_PUMP_DIV_2;
            break;
        case 4:
            divVal = CY_SYSCLK_PUMP_DIV_4;
            break;
        case 8:
            divVal = CY_SYSCLK_PUMP_DIV_8;
            break;
        case 16:
            divVal = CY_SYSCLK_PUMP_DIV_16;
            break;
        default:
            return CYHAL_CLOCK_RSLT_ERR_FREQ;
    }
    Cy_SysClk_ClkPumpSetDivider(divVal);
    return CY_RSLT_SUCCESS;
}
#define _cyhal_clock_get_sources_pump   _cyhal_clock_get_sources_hf
static cy_rslt_t _cyhal_clock_set_source_pump(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    CY_UNUSED_PARAMETER(clock);

    if (source->block == CYHAL_CLOCK_BLOCK_PATHMUX || source->block == CYHAL_CLOCK_BLOCK_FLL)
    {
        Cy_SysClk_ClkPumpSetSource((cy_en_clkpump_in_sources_t)source->channel);
        return CY_RSLT_SUCCESS;
    }
#if defined(COMPONENT_CAT1A)
    else if (source->block == CYHAL_CLOCK_BLOCK_PLL)
#elif defined(COMPONENT_CAT1B)
    else if ((source->block == CYHAL_CLOCK_BLOCK_PLL200) || (source->block == CYHAL_CLOCK_BLOCK_PLL400))
#endif
    {
        Cy_SysClk_ClkPumpSetSource((cy_en_clkpump_in_sources_t)(source->channel + 1));
        return CY_RSLT_SUCCESS;
    }
    else
        return CYHAL_CLOCK_RSLT_ERR_SOURCE;
}
#endif /* defined (COMPONENT_CAT1A) || defined (COMPONENT_CAT1B) */

// TIMER
// TODO: Need to enable timer functionality for CAT1C once PDL team updates clk_timer API's
#if defined(COMPONENT_CAT1A)
static bool _cyhal_clock_is_enabled_timer(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_ClkTimerIsEnabled();
}
static cy_rslt_t _cyhal_clock_set_enabled_timer(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(wait_for_lock);

    if (enabled)
        Cy_SysClk_ClkTimerEnable();
    else
        Cy_SysClk_ClkTimerDisable();
    return CY_RSLT_SUCCESS;
}
static uint32_t _cyhal_clock_get_frequency_timer(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    return Cy_SysClk_ClkTimerGetFrequency();
}
static cy_rslt_t _cyhal_clock_set_divider_timer(cyhal_clock_t *clock, uint32_t divider)
{
    CY_UNUSED_PARAMETER(clock);

    if (divider <= 256)
    {
        uint32_t divVal = divider - 1;
        Cy_SysClk_ClkTimerSetDivider((uint8_t)divVal);
        return CY_RSLT_SUCCESS;
    }
    return CYHAL_CLOCK_RSLT_ERR_FREQ;
}
static cy_rslt_t _cyhal_clock_get_sources_timer(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);
    static const cyhal_resource_inst_t *_CYHAL_CLOCK_SOURCE_TIMER[] =
    {
        &CYHAL_CLOCK_RSC_IMO,
        &CYHAL_CLOCK_RSC_HF[0],
    };

    *sources = _CYHAL_CLOCK_SOURCE_TIMER;
    *count = sizeof(_CYHAL_CLOCK_SOURCE_TIMER) / sizeof(_CYHAL_CLOCK_SOURCE_TIMER[0]);
    return CY_RSLT_SUCCESS;
}
static cy_rslt_t _cyhal_clock_set_source_timer(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    CY_UNUSED_PARAMETER(clock);

    if (source->block == CYHAL_CLOCK_BLOCK_IMO)
    {
        Cy_SysClk_ClkTimerSetSource(CY_SYSCLK_CLKTIMER_IN_IMO);
        return CY_RSLT_SUCCESS;
    }
    else if (source->block == CYHAL_CLOCK_BLOCK_HF && source->channel == 0)
    {
        Cy_SysClk_ClkTimerSetSource(CY_SYSCLK_CLKTIMER_IN_HF0_NODIV);
        return CY_RSLT_SUCCESS;
    }
    return CYHAL_CLOCK_RSLT_ERR_SOURCE;
}
#endif

// BAK
static uint32_t _cyhal_clock_get_frequency_bak(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    cy_en_clkbak_in_sources_t src = Cy_SysClk_ClkBakGetSource();
#if SRSS_BACKUP_PRESENT
    if (src == CY_SYSCLK_BAK_IN_WCO)
        return CY_SYSCLK_WCO_FREQ;
#else
    (void)src;
#endif
    return _cyhal_clock_get_lf_frequency();
}
static cy_rslt_t _cyhal_clock_get_sources_bak(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);
    static const cyhal_resource_inst_t *_CYHAL_CLOCK_SOURCE_BAK[] =
    {
        &CYHAL_CLOCK_RSC_LF,
    #if SRSS_BACKUP_PRESENT
        &CYHAL_CLOCK_RSC_WCO,
    #endif
    #if defined(COMPONENT_CAT1C)
        &CYHAL_CLOCK_RSC_ILO[0],
    #elif defined(COMPONENT_CAT1B)
        &CYHAL_CLOCK_RSC_ILO,
    #endif
    #if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
    #if _CYHAL_SRSS_PILO_PRESENT
        &CYHAL_CLOCK_RSC_PILO,
    #endif
    #endif
    #if defined(COMPONENT_CAT1B)
    #if SRSS_BACKUP_S40E_LPECO_PRESENT
        &CYHAL_CLOCK_RSC_LPECO_PRESCALER,
    #endif
    #endif
    };

    *sources = _CYHAL_CLOCK_SOURCE_BAK;
    *count = sizeof(_CYHAL_CLOCK_SOURCE_BAK) / sizeof(_CYHAL_CLOCK_SOURCE_BAK[0]);
    return CY_RSLT_SUCCESS;
}
static cy_rslt_t _cyhal_clock_set_source_bak(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    CY_UNUSED_PARAMETER(clock);

    switch (source->block)
    {
        case CYHAL_CLOCK_BLOCK_WCO:
            Cy_SysClk_ClkBakSetSource(CY_SYSCLK_BAK_IN_WCO);
            return CY_RSLT_SUCCESS;
        case CYHAL_CLOCK_BLOCK_LF:
            Cy_SysClk_ClkBakSetSource(CY_SYSCLK_BAK_IN_CLKLF);
            return CY_RSLT_SUCCESS;
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
        case CYHAL_CLOCK_BLOCK_ILO:
            if(1 == source->channel)
            {
                return CYHAL_CLOCK_RSLT_ERR_SOURCE;
            }
            Cy_SysClk_ClkBakSetSource(CY_SYSCLK_BAK_IN_ILO);
            return CY_RSLT_SUCCESS;
#if _CYHAL_SRSS_PILO_PRESENT
        case CYHAL_CLOCK_BLOCK_PILO:
            Cy_SysClk_ClkBakSetSource(CY_SYSCLK_BAK_IN_PILO);
            return CY_RSLT_SUCCESS;
#endif
#if SRSS_BACKUP_S40E_LPECO_PRESENT
        case CYHAL_CLOCK_BLOCK_LPECO_PRESCALER:
            Cy_SysClk_ClkBakSetSource(CY_SYSCLK_BAK_IN_LPECO_PRESCALER);
            return CY_RSLT_SUCCESS;
#endif
#endif
        default:
            CY_ASSERT(false); //Unhandled clock
            return CYHAL_CLOCK_RSLT_ERR_SOURCE;
    }
}

// ALT_SYS_TICK
static uint32_t _cyhal_clock_get_frequency_alt_sys_tick(const cyhal_clock_t *clock)
{
    CY_UNUSED_PARAMETER(clock);
    CY_ASSERT(false); // This is not supported at this time
    return 0;
}
static cy_rslt_t _cyhal_clock_get_sources_alt_sys_tick(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_UNUSED_PARAMETER(clock);
    static const cyhal_resource_inst_t *_CYHAL_CLOCK_SOURCE_ALT_SYS_TICK[] =
    {
        &CYHAL_CLOCK_RSC_IMO,
    #if SRSS_ECO_PRESENT
        &CYHAL_CLOCK_RSC_ECO,
    #endif
        &CYHAL_CLOCK_RSC_LF,
#if defined(COMPONENT_CAT1A)
        &CYHAL_CLOCK_RSC_TIMER, /* Technically present on CAT1B and CAT1C, but deprecated */
#endif
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
#if defined(COMPONENT_CAT1C)
        &CYHAL_CLOCK_RSC_FAST[0],
        &CYHAL_CLOCK_RSC_FAST[1],
#else
        &CYHAL_CLOCK_RSC_FAST,
#endif
        &CYHAL_CLOCK_RSC_SLOW,
#elif defined(COMPONENT_CAT1B)
        &CYHAL_CLOCK_RSC_HF[0], /* CPU clock */
#endif
    };

    *sources = _CYHAL_CLOCK_SOURCE_ALT_SYS_TICK;
    *count = sizeof(_CYHAL_CLOCK_SOURCE_ALT_SYS_TICK) / sizeof(_CYHAL_CLOCK_SOURCE_ALT_SYS_TICK[0]);
    return CY_RSLT_SUCCESS;
}
static cy_rslt_t _cyhal_clock_set_source_alt_sys_tick(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    CY_UNUSED_PARAMETER(clock);

    switch (source->block)
    {
        case CYHAL_CLOCK_BLOCK_LF:
            Cy_SysTick_SetClockSource(CY_SYSTICK_CLOCK_SOURCE_CLK_LF);
            return CY_RSLT_SUCCESS;
        case CYHAL_CLOCK_BLOCK_IMO:
            Cy_SysTick_SetClockSource(CY_SYSTICK_CLOCK_SOURCE_CLK_IMO);
            return CY_RSLT_SUCCESS;
#if SRSS_ECO_PRESENT
        case CYHAL_CLOCK_BLOCK_ECO:
            Cy_SysTick_SetClockSource(CY_SYSTICK_CLOCK_SOURCE_CLK_ECO);
            return CY_RSLT_SUCCESS;
#endif
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
#if defined(COMPONENT_CAT1A)
        case CYHAL_CLOCK_BLOCK_TIMER:
            Cy_SysTick_SetClockSource(CY_SYSTICK_CLOCK_SOURCE_CLK_TIMER);
            return CY_RSLT_SUCCESS;
#endif
        case CYHAL_CLOCK_BLOCK_FAST:
        case CYHAL_CLOCK_BLOCK_SLOW:
            Cy_SysTick_SetClockSource(CY_SYSTICK_CLOCK_SOURCE_CLK_CPU);
            return CY_RSLT_SUCCESS;
#endif
        default:
            CY_ASSERT(false); //Unhandled clock
            return CYHAL_CLOCK_RSLT_ERR_SOURCE;
    }
}

// Peripheral
static bool _cyhal_clock_is_enabled_peripheral(const cyhal_clock_t *clock)
{
    return _cyhal_utils_peri_pclk_is_divider_enabled(_CYHAL_CLOCK_GET_PCLK_GR_NUM(clock->block), clock);
}
static cy_rslt_t _cyhal_clock_set_enabled_peripheral(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_UNUSED_PARAMETER(wait_for_lock);

    return (enabled)
        ? _cyhal_utils_peri_pclk_enable_divider(_CYHAL_CLOCK_GET_PCLK_GR_NUM(clock->block), clock)
        : _cyhal_utils_peri_pclk_disable_divider(_CYHAL_CLOCK_GET_PCLK_GR_NUM(clock->block), clock);
}
static uint32_t _cyhal_clock_get_frequency_peripheral(const cyhal_clock_t *clock)
{
    return _cyhal_utils_peri_pclk_get_frequency(_CYHAL_CLOCK_GET_PCLK_GR_NUM(clock->block), clock);
}
static cy_rslt_t _cyhal_clock_set_frequency_peripheral(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_UNUSED_PARAMETER(clock);
    CY_UNUSED_PARAMETER(tolerance);

    // blocks 0b00 & 0b01 are integer, 0b10 & 0b11 are fractional
    uint32_t div;

#if defined(COMPONENT_CAT1A)
    uint32_t input_hz = Cy_SysClk_ClkPeriGetFrequency();
#elif defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
    #if defined(COMPONENT_CAT1D)
    uint8_t instance = _CYHAL_PERIPHERAL_CLOCK_GET_INSTANCE(clock->block);
    uint8_t group = _CYHAL_PERIPHERAL_CLOCK_GET_GROUP(clock->block);
    uint8_t hfclk = _cyhal_utils_get_hfclk_for_peri_group(_CYHAL_UTILS_PACK_INSTANCE_GROUP(instance, group));
    #else /* !defined(COMPONENT_CAT1D) */
    uint8_t group = _CYHAL_PERIPHERAL_GROUP_GET_GROUP(clock->block);
    uint8_t hfclk = _cyhal_utils_get_hfclk_for_peri_group(group);
    #endif /* defined(COMPONENT_CAT1D) or other */
    uint32_t input_hz = Cy_SysClk_ClkHfGetFrequency(hfclk);
#endif

    if ((clock->block & 0x02) == 0) // Integer (8 or 16)
    {
        uint32_t bits = (clock->block & 0x01) ? 16 : 8;
        cy_rslt_t rslt = _cyhal_clock_compute_div((uint64_t)input_hz, hz, bits, tolerance, &div);
        return (CY_RSLT_SUCCESS == rslt)
            ? _cyhal_utils_peri_pclk_set_divider(_CYHAL_CLOCK_GET_PCLK_GR_NUM(clock->block), clock, (div - 1))
            : rslt;
    }
    else //Fractional (16.5 or 24.5)
    {
        // Multiply input by 32 so we can treat the 5 fractional bits as though they are extentions of the integer divider
        // Leave the the desired frequency alone, so we can just strip out the integer & fractional bits at the end.
        uint32_t bits = (clock->block & 0x01) ? 29 : 21; // Integer bits + 5
        cy_rslt_t rslt = _cyhal_clock_compute_div(((uint64_t)input_hz) << 5, hz, bits, tolerance, &div);
        if (CY_RSLT_SUCCESS == rslt)
        {
            uint32_t div_int = (div >> 5) - 1;
            uint32_t div_frac = div & 0x1F;
            return _cyhal_utils_peri_pclk_set_frac_divider(_CYHAL_CLOCK_GET_PCLK_GR_NUM(clock->block), clock, div_int, div_frac);
        }
        else
            return rslt;
    }
}
static cy_rslt_t _cyhal_clock_set_divider_peripheral(cyhal_clock_t *clock, uint32_t divider)
{
    CY_UNUSED_PARAMETER(clock);

    // blocks 0b00 & 0b01 are integer, 0b10 & 0b11 are fractional
    return ((clock->block & 0x02) == 0)
        ? _cyhal_utils_peri_pclk_set_divider(_CYHAL_CLOCK_GET_PCLK_GR_NUM(clock->block), clock, divider - 1)
        : _cyhal_utils_peri_pclk_set_frac_divider(_CYHAL_CLOCK_GET_PCLK_GR_NUM(clock->block), clock, divider - 1, 0);
}
static cy_rslt_t _cyhal_clock_get_sources_peripheral(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
#if defined(COMPONENT_CAT1A)
    return _cyhal_clock_get_sources_slow(clock, sources, count);
#elif defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
    #if defined(COMPONENT_CAT1D)
    uint8_t instance = _CYHAL_PERIPHERAL_CLOCK_GET_INSTANCE(clock->block);
    uint8_t group = _CYHAL_PERIPHERAL_CLOCK_GET_GROUP(clock->block);
    uint8_t hfclk = _cyhal_utils_get_hfclk_for_peri_group(_CYHAL_UTILS_PACK_INSTANCE_GROUP(instance, group));
    #else /* !defined(COMPONENT_CAT1D) */
    uint8_t group = _CYHAL_PERIPHERAL_GROUP_GET_GROUP(clock->block);
    uint8_t hfclk = _cyhal_utils_get_hfclk_for_peri_group(group);
    #endif /* defined(COMPONENT_CAT1D) or other */
    return _cyhal_clock_get_sources_peri_peripheral(hfclk, sources, count);
#endif
}



/******************************************************************************
 ******************************* Clock Structs ********************************
 *****************************************************************************/

/* Use a structure with function pointers to allow the driver to optimize out entire clocks if they
 * are not used. We make two exceptions to this. HF and peripheral clocks are called directly by
 * the public functions. This allows those clocks to be optimized based on what the user actually
 * calls. This distinction is done based on what the user is most likely to do with the HAL driver.
 * HF & peripheral clocks are likely to be configured at runtime based on setting up different
 * peripherals. Other system clocks are likely to be be set once at startup and never modified.
 * Based on this, we design the code so the compiler can optimize out the unused items most
 * efficiently.
 */

typedef struct
{
    bool (*is_enabled)(const cyhal_clock_t *clock);
    cy_rslt_t (*set_enabled)(cyhal_clock_t *clock, bool enabled, bool wait_for_lock);
    uint32_t (*get_frequency)(const cyhal_clock_t *clock);
    cy_rslt_t (*set_frequency)(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance);
    cy_rslt_t (*set_divider)(cyhal_clock_t *clock, uint32_t divider);
    cy_rslt_t (*get_sources)(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count);
    cy_rslt_t (*set_source)(cyhal_clock_t *clock, const cyhal_clock_t *source);
    cyhal_clock_feature_t features;
} cyhal_clock_funcs_t;

static const cyhal_clock_funcs_t FUNCS_IMO =
{
    .features = CYHAL_CLOCK_FEATURE_NONE,
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_imo,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_none,
    .set_source = _cyhal_clock_set_source_unsupported,
};

#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
static const cyhal_clock_funcs_t FUNCS_IHO =
{
    .features = CYHAL_CLOCK_FEATURE_ENABLE,
    .is_enabled = _cyhal_clock_is_enabled_iho,
    .set_enabled = _cyhal_clock_set_enabled_iho,
    .get_frequency = _cyhal_clock_get_frequency_iho,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_none,
    .set_source = _cyhal_clock_set_source_unsupported,
};
#endif

#if defined(COMPONENT_CAT1C)
static const cyhal_clock_funcs_t FUNCS_MEM =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_DIVIDER | CYHAL_CLOCK_FEATURE_FREQUENCY),
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_mem,
    .set_frequency = _cyhal_clock_set_frequency_mem,
    .set_divider = _cyhal_clock_set_divider_mem,
    .get_sources = _cyhal_clock_get_sources_mem,
    .set_source = _cyhal_clock_set_source_unsupported,
};
#endif

#if SRSS_ECO_PRESENT
static const cyhal_clock_funcs_t FUNCS_ECO =
{
    .features = CYHAL_CLOCK_FEATURE_ENABLE,
    .is_enabled = _cyhal_clock_is_enabled_eco,
    .set_enabled = _cyhal_clock_set_enabled_eco,
    .get_frequency = _cyhal_clock_get_frequency_eco,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_none,
    .set_source = _cyhal_clock_set_source_unsupported,
};
#endif

static const cyhal_clock_funcs_t FUNCS_EXT =
{
    .features = CYHAL_CLOCK_FEATURE_FREQUENCY,
    .is_enabled = _cyhal_clock_is_enabled_ext,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_ext,
    .set_frequency = _cyhal_clock_set_frequency_ext,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_none,
    .set_source = _cyhal_clock_set_source_unsupported,
};

#if SRSS_ALTHF_PRESENT
static const cyhal_clock_funcs_t FUNCS_ALTHF =
{
    .features = CYHAL_CLOCK_FEATURE_NONE,
    .is_enabled = _cyhal_clock_is_enabled_althf,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_althf,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_none,
    .set_source = _cyhal_clock_set_source_unsupported,
};
#endif

#if SRSS_ALTLF_PRESENT
static const cyhal_clock_funcs_t FUNCS_ALTLF =
{
    .features = CYHAL_CLOCK_FEATURE_NONE,
    .is_enabled = _cyhal_clock_is_enabled_altlf,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_altlf,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_none,
    .set_source = _cyhal_clock_set_source_unsupported,
};
#endif

static const cyhal_clock_funcs_t FUNCS_ILO =
{
    .features = CYHAL_CLOCK_FEATURE_ENABLE,
    .is_enabled = _cyhal_clock_is_enabled_ilo,
    .set_enabled = _cyhal_clock_set_enabled_ilo,
    .get_frequency = _cyhal_clock_get_frequency_ilo,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_none,
    .set_source = _cyhal_clock_set_source_unsupported,
};

#if _CYHAL_SRSS_PILO_PRESENT
static const cyhal_clock_funcs_t FUNCS_PILO =
{
    .features = CYHAL_CLOCK_FEATURE_ENABLE,
    .is_enabled = _cyhal_clock_is_enabled_pilo,
    .set_enabled = _cyhal_clock_set_enabled_pilo,
    .get_frequency = _cyhal_clock_get_frequency_pilo,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_none,
    .set_source = _cyhal_clock_set_source_unsupported,
};
#endif

#if SRSS_BACKUP_PRESENT
static const cyhal_clock_funcs_t FUNCS_WCO =
{
    .features = CYHAL_CLOCK_FEATURE_ENABLE,
    .is_enabled = _cyhal_clock_is_enabled_wco,
    .set_enabled = _cyhal_clock_set_enabled_wco,
    .get_frequency = _cyhal_clock_get_frequency_wco,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_none,
    .set_source = _cyhal_clock_set_source_unsupported,
};
#endif

#if defined(COMPONENT_CAT1B) || (SRSS_MFO_PRESENT)
static const cyhal_clock_funcs_t FUNCS_MFO =
{
    .features = CYHAL_CLOCK_FEATURE_ENABLE,
    .is_enabled = _cyhal_clock_is_enabled_mfo,
    .set_enabled = _cyhal_clock_set_enabled_mfo,
    .get_frequency = _cyhal_clock_get_frequency_mfo,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_mfo,
    .set_source = _cyhal_clock_set_source_unsupported,
};
#endif

static const cyhal_clock_funcs_t FUNCS_PATHMUX =
{
    .features = CYHAL_CLOCK_FEATURE_SOURCE,
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_pathmux,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_pathmux,
    .set_source = _cyhal_clock_set_source_pathmux,
};

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C) || (SRSS_FLL_PRESENT)
static const cyhal_clock_funcs_t FUNCS_FLL =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_FREQUENCY),
    .is_enabled = _cyhal_clock_is_enabled_fll,
    .set_enabled = _cyhal_clock_set_enabled_fll,
    .get_frequency = _cyhal_clock_get_frequency_fll,
    .set_frequency = _cyhal_clock_set_frequency_fll,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_fll,
    .set_source = _cyhal_clock_set_source_unsupported,
};
#endif

#if (_CYHAL_SRSS_NUM_PLL > 0)
static const cyhal_clock_funcs_t FUNCS_PLL =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_FREQUENCY),
    .is_enabled = _cyhal_clock_is_enabled_pll,
    .set_enabled = _cyhal_clock_set_enabled_pll,
    .get_frequency = _cyhal_clock_get_frequency_pll,
    .set_frequency = _cyhal_clock_set_frequency_pll,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_pll,
    .set_source = _cyhal_clock_set_source_unsupported,
};
#endif

#if defined(COMPONENT_CAT1C)
#if (SRSS_NUM_PLL > 0)
#define FUNCS_PLL200 FUNCS_PLL
#endif
#if (SRSS_NUM_PLL400M > 0)
#define FUNCS_PLL400 FUNCS_PLL
#endif
#endif /* defined(COMPONENT_CAT1C) */

#if defined(COMPONENT_CAT1D)
#if (SRSS_NUM_DPLL_LP > 0)
#define FUNCS_DPLL_LP FUNCS_PLL
#endif
#if (SRSS_NUM_DPLL_HP > 0)
#define FUNCS_DPLL_HP FUNCS_PLL
#endif
#endif /* defined(COMPONENT_CAT1D) */

static const cyhal_clock_funcs_t FUNCS_LF =
{
    .features = CYHAL_CLOCK_FEATURE_SOURCE,
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_lf,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_lf,
    .set_source = _cyhal_clock_set_source_lf,
};

#if defined(COMPONENT_CAT1B) || (SRSS_MFO_PRESENT)
static const cyhal_clock_funcs_t FUNCS_MF =
{
#if defined(COMPONENT_CAT1A) /* CAT1A only supports driving clk_mf from the MFO */
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_DIVIDER | CYHAL_CLOCK_FEATURE_FREQUENCY),
#else
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_DIVIDER | CYHAL_CLOCK_FEATURE_FREQUENCY | CYHAL_CLOCK_FEATURE_SOURCE),
#endif
    .is_enabled = _cyhal_clock_is_enabled_mf,
    .set_enabled = _cyhal_clock_set_enabled_mf,
    .get_frequency = _cyhal_clock_get_frequency_mf,
    .set_frequency = _cyhal_clock_set_frequency_mf,
    .set_divider = _cyhal_clock_set_divider_mf,
    .get_sources = _cyhal_clock_get_sources_mf,
    .set_source = _cyhal_clock_set_source_mf,
};
#endif

static const cyhal_clock_funcs_t FUNCS_HF =
{
    // NOTE: HF0 cannot be disabled, it would stop the MCUs. Ideally HF0 would not support
    // CYHAL_CLOCK_FEATURE_ENABLE, but this struct is never actually used in practice so it doesn't
    // matter.
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_SOURCE | CYHAL_CLOCK_FEATURE_DIVIDER),
    .is_enabled = _cyhal_clock_is_enabled_hf,
    .set_enabled = _cyhal_clock_set_enabled_hf,
    .get_frequency = _cyhal_clock_get_frequency_hf,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_hf,
    .get_sources = _cyhal_clock_get_sources_hf,
    .set_source = _cyhal_clock_set_source_hf,
};

// PUMP clock is only available on CAT1A and CAT1B devices
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B)
static const cyhal_clock_funcs_t FUNCS_PUMP =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_SOURCE | CYHAL_CLOCK_FEATURE_DIVIDER),
    .is_enabled = _cyhal_clock_is_enabled_pump,
    .set_enabled = _cyhal_clock_set_enabled_pump,
    .get_frequency = _cyhal_clock_get_frequency_pump,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_pump,
    .get_sources = _cyhal_clock_get_sources_pump,
    .set_source = _cyhal_clock_set_source_pump,
};
#endif /* defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) */

#if defined(COMPONENT_CAT1A)
static const cyhal_clock_funcs_t FUNCS_TIMER =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_SOURCE | CYHAL_CLOCK_FEATURE_DIVIDER),
    .is_enabled = _cyhal_clock_is_enabled_timer,
    .set_enabled = _cyhal_clock_set_enabled_timer,
    .get_frequency = _cyhal_clock_get_frequency_timer,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_timer,
    .get_sources = _cyhal_clock_get_sources_timer,
    .set_source = _cyhal_clock_set_source_timer,
};
#endif

static const cyhal_clock_funcs_t FUNCS_BAK =
{
    .features = CYHAL_CLOCK_FEATURE_SOURCE,
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_bak,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_bak,
    .set_source = _cyhal_clock_set_source_bak,
};

static const cyhal_clock_funcs_t FUNCS_ALT_SYS_TICK =
{
    .features = CYHAL_CLOCK_FEATURE_SOURCE,
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_alt_sys_tick,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_unsupported,
    .get_sources = _cyhal_clock_get_sources_alt_sys_tick,
    .set_source = _cyhal_clock_set_source_alt_sys_tick,
};

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
static const cyhal_clock_funcs_t FUNCS_FAST =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_DIVIDER | CYHAL_CLOCK_FEATURE_FREQUENCY),
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_fast,
    .set_frequency = _cyhal_clock_set_frequency_fast,
    .set_divider = _cyhal_clock_set_divider_fast,
    .get_sources = _cyhal_clock_get_sources_fast,
    .set_source = _cyhal_clock_set_source_unsupported,
};

static const cyhal_clock_funcs_t FUNCS_SLOW =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_DIVIDER | CYHAL_CLOCK_FEATURE_FREQUENCY),
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_slow,
    .set_frequency = _cyhal_clock_set_frequency_slow,
    .set_divider = _cyhal_clock_set_divider_slow,
    .get_sources = _cyhal_clock_get_sources_slow,
    .set_source = _cyhal_clock_set_source_unsupported,
};
#endif
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
#if SRSS_ECO_PRESENT
static const cyhal_clock_funcs_t FUNCS_ECO_PRESCALER =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_DIVIDER),
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_eco_prescaler,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_eco_prescaler,
    .get_sources = _cyhal_clock_get_sources_eco_prescaler,
    .set_source = _cyhal_clock_set_source_unsupported,
};
#endif

#if SRSS_BACKUP_S40E_LPECO_PRESENT
static const cyhal_clock_funcs_t FUNCS_LPECO_PRESCALER =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_DIVIDER),
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_lpeco_prescaler,
    .set_frequency = _cyhal_clock_set_frequency_unsupported,
    .set_divider = _cyhal_clock_set_divider_lpeco_prescaler,
    .get_sources = _cyhal_clock_get_sources_lpeco_prescaler,
    .set_source = _cyhal_clock_set_source_unsupported,
};
#endif
#endif

static const cyhal_clock_funcs_t FUNCS_PERI =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_DIVIDER | CYHAL_CLOCK_FEATURE_FREQUENCY),
    .is_enabled = _cyhal_clock_is_enabled_true,
    .set_enabled = _cyhal_clock_set_enabled_unsupported,
    .get_frequency = _cyhal_clock_get_frequency_peri,
    .set_frequency = _cyhal_clock_set_frequency_peri,
    .set_divider = _cyhal_clock_set_divider_peri,
    .get_sources = _cyhal_clock_get_sources_peri,
    .set_source = _cyhal_clock_set_source_unsupported,
};

static const cyhal_clock_funcs_t FUNCS_PERIPHERAL =
{
    .features = (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_DIVIDER | CYHAL_CLOCK_FEATURE_FREQUENCY),
    .is_enabled = _cyhal_clock_is_enabled_peripheral,
    .set_enabled = _cyhal_clock_set_enabled_peripheral,
    .get_frequency = _cyhal_clock_get_frequency_peripheral,
    .set_frequency = _cyhal_clock_set_frequency_peripheral,
    .set_divider = _cyhal_clock_set_divider_peripheral,
    .get_sources = _cyhal_clock_get_sources_peripheral,
    .set_source = _cyhal_clock_set_source_unsupported,
};


static const cyhal_clock_funcs_t FUNCS_EMPTY =
{
    .features = CYHAL_CLOCK_FEATURE_NONE,
    .is_enabled = NULL,
    .set_enabled = NULL,
    .get_frequency = NULL,
    .set_frequency = NULL,
    .set_divider = NULL,
    .get_sources = NULL,
    .set_source = NULL,
};

const void* _cyhal_clock_get_funcs_pathmux(void) { return &FUNCS_PATHMUX; }
#if (_CYHAL_SRSS_NUM_PLL > 0)
const void* _cyhal_clock_get_funcs_pll(void) { return &FUNCS_PLL; }
#endif
// HF and peripheral functions are called directly from the public APIs and do not go through
// the struct lookup. This allows them to get optimized out based on what the user calls. We
// return FUNCS_EMPTY here so as to avoid unnecessarily pulling in all functions for those clocks.
const void* _cyhal_clock_get_funcs_hf(void) { return &FUNCS_EMPTY/*FUNCS_HF*/; }
const void* _cyhal_clock_get_funcs_peripheral(void) { return &FUNCS_EMPTY/*FUNCS_PERIPHERAL*/; }

static const cyhal_clock_funcs_t* _cyhal_clock_get_funcs_all(cyhal_clock_block_t block)
{
    switch (block)
    {
        case CYHAL_CLOCK_BLOCK_IMO:
            return &FUNCS_IMO;
#if SRSS_ECO_PRESENT
        case CYHAL_CLOCK_BLOCK_ECO:
            return &FUNCS_ECO;
#endif
        case CYHAL_CLOCK_BLOCK_EXT:
            return &FUNCS_EXT;
#if SRSS_ALTHF_PRESENT
        case CYHAL_CLOCK_BLOCK_ALTHF:
            return &FUNCS_ALTHF;
#endif
#if SRSS_ALTLF_PRESENT
        case CYHAL_CLOCK_BLOCK_ALTLF:
            return &FUNCS_ALTLF;
#endif
        case CYHAL_CLOCK_BLOCK_ILO:
            return &FUNCS_ILO;
#if _CYHAL_SRSS_PILO_PRESENT
        case CYHAL_CLOCK_BLOCK_PILO:
            return &FUNCS_PILO;
#endif
#if SRSS_BACKUP_PRESENT
        case CYHAL_CLOCK_BLOCK_WCO:
            return &FUNCS_WCO;
#endif
#if defined(COMPONENT_CAT1B) || (SRSS_MFO_PRESENT)
        case CYHAL_CLOCK_BLOCK_MFO:
            return &FUNCS_MFO;
#endif
        case CYHAL_CLOCK_BLOCK_PATHMUX:
            return &FUNCS_PATHMUX;
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C) || (SRSS_FLL_PRESENT)
        case CYHAL_CLOCK_BLOCK_FLL:
            return &FUNCS_FLL;
#endif
        case CYHAL_CLOCK_BLOCK_LF:
            return &FUNCS_LF;
#if defined(COMPONENT_CAT1B) || (SRSS_MFO_PRESENT)
        case CYHAL_CLOCK_BLOCK_MF:
            return &FUNCS_MF;
#endif
        case CYHAL_CLOCK_BLOCK_HF:
            return &FUNCS_HF;
// PUMP clock is only available on CAT1A and CAT1B devices
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B)
        case CYHAL_CLOCK_BLOCK_PUMP:
            return &FUNCS_PUMP;
#endif /* defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) */
        case CYHAL_CLOCK_BLOCK_BAK:
            return &FUNCS_BAK;
        case CYHAL_CLOCK_BLOCK_ALT_SYS_TICK:
            return &FUNCS_ALT_SYS_TICK;
        case CYHAL_CLOCK_BLOCK_PERI:
            return &FUNCS_PERI;
#if defined(COMPONENT_CAT1A)
#if (_CYHAL_SRSS_NUM_PLL > 0)
        case CYHAL_CLOCK_BLOCK_PLL:
            return &FUNCS_PLL;
#endif
#endif
#if defined(COMPONENT_CAT1C)
        case CYHAL_CLOCK_BLOCK_MEM:
            return &FUNCS_MEM;
#endif
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
#if defined(COMPONENT_CAT1A)
        case CYHAL_CLOCK_BLOCK_TIMER:
            return &FUNCS_TIMER;
#endif
        case CYHAL_CLOCK_BLOCK_FAST:
            return &FUNCS_FAST;
        case CYHAL_CLOCK_BLOCK_SLOW:
            return &FUNCS_SLOW;
#endif
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
#if (_CYHAL_SRSS_NUM_PLL > 0)
        case CYHAL_CLOCK_BLOCK_PLL200:
            return &FUNCS_PLL200;
        case CYHAL_CLOCK_BLOCK_PLL400:
            return &FUNCS_PLL400;
#endif
#endif
#if defined(COMPONENT_CAT1D)
#if (_CYHAL_SRSS_NUM_PLL > 0)
        case CYHAL_CLOCK_BLOCK_DPLL_LP:
            return &FUNCS_DPLL_LP;
        case CYHAL_CLOCK_BLOCK_DPLL_HP:
            return &FUNCS_DPLL_HP;
#endif
#endif
#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
        case CYHAL_CLOCK_BLOCK_IHO:
            return &FUNCS_IHO;
#if SRSS_ECO_PRESENT
        case CYHAL_CLOCK_BLOCK_ECO_PRESCALER:
            return &FUNCS_ECO_PRESCALER;
#endif
#if SRSS_BACKUP_S40E_LPECO_PRESENT
        case CY_SYSCLK_CLKLF_IN_LPECO_PRESCALER:
            return &FUNCS_LPECO_PRESCALER;
#endif
#endif
        default:
            return &FUNCS_PERIPHERAL;
    }
}

#define _CYHAL_CLOCK_CREATE(x,y)    { .block = (CYHAL_CLOCK_BLOCK_##x), .channel = (y), .reserved = false, .funcs = &(FUNCS_##x) }

const cyhal_clock_t CYHAL_CLOCK_IMO = _CYHAL_CLOCK_CREATE(IMO, 0);
const cyhal_clock_t CYHAL_CLOCK_EXT = _CYHAL_CLOCK_CREATE(EXT, 0);
#if defined(COMPONENT_CAT1C)
const cyhal_clock_t CYHAL_CLOCK_ILO[_CYHAL_SRSS_NUM_ILO] =
{
    _CYHAL_CLOCK_CREATE(ILO, 0),
    #if (SRSS_HT_VARIANT > 0)
    _CYHAL_CLOCK_CREATE(ILO, 1),
    #endif
};
#else
const cyhal_clock_t CYHAL_CLOCK_ILO = _CYHAL_CLOCK_CREATE(ILO, 0);
#endif
const cyhal_clock_t CYHAL_CLOCK_LF = _CYHAL_CLOCK_CREATE(LF, 0);
// PUMP clock is only available on CAT1A and CAT1B devices
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B)
const cyhal_clock_t CYHAL_CLOCK_PUMP = _CYHAL_CLOCK_CREATE(PUMP, 0);
#endif /* defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) */
const cyhal_clock_t CYHAL_CLOCK_BAK = _CYHAL_CLOCK_CREATE(BAK, 0);
const cyhal_clock_t CYHAL_CLOCK_ALT_SYS_TICK = _CYHAL_CLOCK_CREATE(ALT_SYS_TICK, 0);

const cyhal_clock_t CYHAL_CLOCK_PATHMUX[SRSS_NUM_CLKPATH] =
{
    _CYHAL_CLOCK_CREATE(PATHMUX, 0),
#if (SRSS_NUM_CLKPATH > 1)
    _CYHAL_CLOCK_CREATE(PATHMUX, 1),
#endif
#if (SRSS_NUM_CLKPATH > 2)
    _CYHAL_CLOCK_CREATE(PATHMUX, 2),
#endif
#if (SRSS_NUM_CLKPATH > 3)
    _CYHAL_CLOCK_CREATE(PATHMUX, 3),
#endif
#if (SRSS_NUM_CLKPATH > 4)
    _CYHAL_CLOCK_CREATE(PATHMUX, 4),
#endif
#if (SRSS_NUM_CLKPATH > 5)
    _CYHAL_CLOCK_CREATE(PATHMUX, 5),
#endif
#if (SRSS_NUM_CLKPATH > 6)
    _CYHAL_CLOCK_CREATE(PATHMUX, 6),
#endif
#if (SRSS_NUM_CLKPATH > 7)
    _CYHAL_CLOCK_CREATE(PATHMUX, 7),
#endif
#if (SRSS_NUM_CLKPATH > 8)
    _CYHAL_CLOCK_CREATE(PATHMUX, 8),
#endif
#if (SRSS_NUM_CLKPATH > 9)
    _CYHAL_CLOCK_CREATE(PATHMUX, 9),
#endif
#if (SRSS_NUM_CLKPATH > 10)
    _CYHAL_CLOCK_CREATE(PATHMUX, 10),
#endif
#if (SRSS_NUM_CLKPATH > 11)
    _CYHAL_CLOCK_CREATE(PATHMUX, 11),
#endif
#if (SRSS_NUM_CLKPATH > 12)
    _CYHAL_CLOCK_CREATE(PATHMUX, 12),
#endif
#if (SRSS_NUM_CLKPATH > 13)
    _CYHAL_CLOCK_CREATE(PATHMUX, 13),
#endif
#if (SRSS_NUM_CLKPATH > 14)
    _CYHAL_CLOCK_CREATE(PATHMUX, 14),
#endif
#if (SRSS_NUM_CLKPATH > 15)
    _CYHAL_CLOCK_CREATE(PATHMUX, 15),
#endif
};

const cyhal_clock_t CYHAL_CLOCK_HF[SRSS_NUM_HFROOT] =
{
    _CYHAL_CLOCK_CREATE(HF, 0),
#if (SRSS_NUM_HFROOT > 1)
    _CYHAL_CLOCK_CREATE(HF, 1),
#endif
#if (SRSS_NUM_HFROOT > 2)
    _CYHAL_CLOCK_CREATE(HF, 2),
#endif
#if (SRSS_NUM_HFROOT > 3)
    _CYHAL_CLOCK_CREATE(HF, 3),
#endif
#if (SRSS_NUM_HFROOT > 4)
    _CYHAL_CLOCK_CREATE(HF, 4),
#endif
#if (SRSS_NUM_HFROOT > 5)
    _CYHAL_CLOCK_CREATE(HF, 5),
#endif
#if (SRSS_NUM_HFROOT > 6)
    _CYHAL_CLOCK_CREATE(HF, 6),
#endif
#if (SRSS_NUM_HFROOT > 7)
    _CYHAL_CLOCK_CREATE(HF, 7),
#endif
#if (SRSS_NUM_HFROOT > 8)
    _CYHAL_CLOCK_CREATE(HF, 8),
#endif
#if (SRSS_NUM_HFROOT > 9)
    _CYHAL_CLOCK_CREATE(HF, 9),
#endif
#if (SRSS_NUM_HFROOT > 10)
    _CYHAL_CLOCK_CREATE(HF, 10),
#endif
#if (SRSS_NUM_HFROOT > 11)
    _CYHAL_CLOCK_CREATE(HF, 11),
#endif
#if (SRSS_NUM_HFROOT > 12)
    _CYHAL_CLOCK_CREATE(HF, 12),
#endif
#if (SRSS_NUM_HFROOT > 13)
    _CYHAL_CLOCK_CREATE(HF, 13),
#endif
#if (SRSS_NUM_HFROOT > 14)
    _CYHAL_CLOCK_CREATE(HF, 14),
#endif
#if (SRSS_NUM_HFROOT > 15)
    _CYHAL_CLOCK_CREATE(HF, 15),
#endif
};

#if SRSS_ECO_PRESENT
const cyhal_clock_t CYHAL_CLOCK_ECO = _CYHAL_CLOCK_CREATE(ECO, 0);
#endif
#if SRSS_ALTHF_PRESENT
const cyhal_clock_t CYHAL_CLOCK_ALTHF = _CYHAL_CLOCK_CREATE(ALTHF, 0);
#endif
#if SRSS_ALTLF_PRESENT
const cyhal_clock_t CYHAL_CLOCK_ALTLF = _CYHAL_CLOCK_CREATE(ALTLF, 0);
#endif
#if _CYHAL_SRSS_PILO_PRESENT
const cyhal_clock_t CYHAL_CLOCK_PILO = _CYHAL_CLOCK_CREATE(PILO, 0);
#endif
#if SRSS_BACKUP_PRESENT
const cyhal_clock_t CYHAL_CLOCK_WCO = _CYHAL_CLOCK_CREATE(WCO, 0);
#endif
#if defined(COMPONENT_CAT1B) || (SRSS_MFO_PRESENT)
const cyhal_clock_t CYHAL_CLOCK_MFO = _CYHAL_CLOCK_CREATE(MFO, 0);
const cyhal_clock_t CYHAL_CLOCK_MF = _CYHAL_CLOCK_CREATE(MF, 0);
#endif
#if defined(COMPONENT_CAT1C)
const cyhal_clock_t CYHAL_CLOCK_MEM = _CYHAL_CLOCK_CREATE(MEM, 0);
#endif

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C) || (SRSS_FLL_PRESENT)
const cyhal_clock_t CYHAL_CLOCK_FLL = _CYHAL_CLOCK_CREATE(FLL, 0);
#endif

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
#if defined(COMPONENT_CAT1C)
const cyhal_clock_t CYHAL_CLOCK_FAST[2] =
{
    _CYHAL_CLOCK_CREATE(FAST, 0),
    _CYHAL_CLOCK_CREATE(FAST, 1),
};
#else
const cyhal_clock_t CYHAL_CLOCK_FAST = _CYHAL_CLOCK_CREATE(FAST, 0);
#endif
const cyhal_clock_t CYHAL_CLOCK_SLOW = _CYHAL_CLOCK_CREATE(SLOW, 0);
#if defined(COMPONENT_CAT1A)
const cyhal_clock_t CYHAL_CLOCK_PERI = _CYHAL_CLOCK_CREATE(PERI, 0);
const cyhal_clock_t CYHAL_CLOCK_TIMER = _CYHAL_CLOCK_CREATE(TIMER, 0);
#endif

#if (_CYHAL_SRSS_NUM_PLL > 0) && defined(COMPONENT_CAT1A)
const cyhal_clock_t CYHAL_CLOCK_PLL[_CYHAL_SRSS_NUM_PLL] =
{
    _CYHAL_CLOCK_CREATE(PLL, 0),
#if (_CYHAL_SRSS_NUM_PLL > 1)
    _CYHAL_CLOCK_CREATE(PLL, 1),
#endif
#if (_CYHAL_SRSS_NUM_PLL > 2)
    _CYHAL_CLOCK_CREATE(PLL, 2),
#endif
#if (_CYHAL_SRSS_NUM_PLL > 3)
    _CYHAL_CLOCK_CREATE(PLL, 3),
#endif
#if (_CYHAL_SRSS_NUM_PLL > 4)
    _CYHAL_CLOCK_CREATE(PLL, 4),
#endif
#if (_CYHAL_SRSS_NUM_PLL > 5)
    _CYHAL_CLOCK_CREATE(PLL, 5),
#endif
#if (_CYHAL_SRSS_NUM_PLL > 6)
    _CYHAL_CLOCK_CREATE(PLL, 6),
#endif
#if (_CYHAL_SRSS_NUM_PLL > 7)
    _CYHAL_CLOCK_CREATE(PLL, 7),
#endif
#if (_CYHAL_SRSS_NUM_PLL > 8)
    _CYHAL_CLOCK_CREATE(PLL, 8),
#endif
#if (_CYHAL_SRSS_NUM_PLL > 9)
    _CYHAL_CLOCK_CREATE(PLL, 9),
#endif
#if (_CYHAL_SRSS_NUM_PLL > 10)
    _CYHAL_CLOCK_CREATE(PLL, 10),
#endif
#if (_CYHAL_SRSS_NUM_PLL > 11)
    _CYHAL_CLOCK_CREATE(PLL, 11),
#endif
#if (_CYHAL_SRSS_NUM_PLL > 12)
    _CYHAL_CLOCK_CREATE(PLL, 12),
#endif
#if (_CYHAL_SRSS_NUM_PLL > 13)
    _CYHAL_CLOCK_CREATE(PLL, 13),
#endif
#if (_CYHAL_SRSS_NUM_PLL > 14)
    _CYHAL_CLOCK_CREATE(PLL, 14),
#endif
};
#endif
#endif

#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
#if defined(COMPONENT_CAT1B)
const cyhal_clock_t CYHAL_CLOCK_IHO = _CYHAL_CLOCK_CREATE(IHO, 0);
#if SRSS_ECO_PRESENT
const cyhal_clock_t CYHAL_CLOCK_ECO_PRESCALER = _CYHAL_CLOCK_CREATE(ECO_PRESCALER, 0);
#endif
#if SRSS_BACKUP_S40E_LPECO_PRESENT
const cyhal_clock_t CYHAL_CLOCK_LPECO_PRESCALER = _CYHAL_CLOCK_CREATE(LPECO_PRESCALER, 0);
#endif
#endif

const cyhal_clock_t CYHAL_CLOCK_PERI[CY_PERI_GROUP_NR] =
{
    _CYHAL_CLOCK_CREATE(PERI, 0),
#if (CY_PERI_GROUP_NR > 1)
    _CYHAL_CLOCK_CREATE(PERI, 1),
#endif
#if (CY_PERI_GROUP_NR > 2)
    _CYHAL_CLOCK_CREATE(PERI, 2),
#endif
#if (CY_PERI_GROUP_NR > 3)
    _CYHAL_CLOCK_CREATE(PERI, 3),
#endif
#if (CY_PERI_GROUP_NR > 4)
    _CYHAL_CLOCK_CREATE(PERI, 4),
#endif
#if (CY_PERI_GROUP_NR > 5)
    _CYHAL_CLOCK_CREATE(PERI, 5),
#endif
#if (CY_PERI_GROUP_NR > 6)
    _CYHAL_CLOCK_CREATE(PERI, 6),
#endif
#if (CY_PERI_GROUP_NR > 7)
    _CYHAL_CLOCK_CREATE(PERI, 7),
#endif
#if (CY_PERI_GROUP_NR > 8)
    _CYHAL_CLOCK_CREATE(PERI, 8),
#endif
#if (CY_PERI_GROUP_NR > 9)
    _CYHAL_CLOCK_CREATE(PERI, 9),
#endif
#if (CY_PERI_GROUP_NR > 10)
    _CYHAL_CLOCK_CREATE(PERI, 10),
#endif
#if (CY_PERI_GROUP_NR > 11)
    _CYHAL_CLOCK_CREATE(PERI, 11),
#endif
#if (CY_PERI_GROUP_NR > 12)
    _CYHAL_CLOCK_CREATE(PERI, 12),
#endif
#if (CY_PERI_GROUP_NR > 13)
    _CYHAL_CLOCK_CREATE(PERI, 13),
#endif
#if (CY_PERI_GROUP_NR > 14)
    _CYHAL_CLOCK_CREATE(PERI, 14),
#endif
#if (CY_PERI_GROUP_NR > 15)
    _CYHAL_CLOCK_CREATE(PERI, 15),
#endif
};

#if (SRSS_NUM_PLL200M > 0)
#if defined(COMPONENT_CAT1B)
const cyhal_clock_t CYHAL_CLOCK_PLL[SRSS_NUM_PLL200M] =
{
#else
const cyhal_clock_t CYHAL_CLOCK_PLL200[SRSS_NUM_PLL200M] =
{
#endif
    _CYHAL_CLOCK_CREATE(PLL200, 0),
#if (SRSS_NUM_PLL200M > 1)
    _CYHAL_CLOCK_CREATE(PLL200, 1),
#endif
#if (SRSS_NUM_PLL200M > 2)
    _CYHAL_CLOCK_CREATE(PLL200, 2),
#endif
#if (SRSS_NUM_PLL200M > 3)
    _CYHAL_CLOCK_CREATE(PLL200, 3),
#endif
#if (SRSS_NUM_PLL200M > 4)
    _CYHAL_CLOCK_CREATE(PLL200, 4),
#endif
#if (SRSS_NUM_PLL200M > 5)
    _CYHAL_CLOCK_CREATE(PLL200, 5),
#endif
#if (SRSS_NUM_PLL200M > 6)
    _CYHAL_CLOCK_CREATE(PLL200, 6),
#endif
#if (SRSS_NUM_PLL200M > 7)
    _CYHAL_CLOCK_CREATE(PLL200, 7),
#endif
#if (SRSS_NUM_PLL200M > 8)
    _CYHAL_CLOCK_CREATE(PLL200, 8),
#endif
#if (SRSS_NUM_PLL200M > 9)
    _CYHAL_CLOCK_CREATE(PLL200, 9),
#endif
#if (SRSS_NUM_PLL200M > 10)
    _CYHAL_CLOCK_CREATE(PLL200, 10),
#endif
#if (SRSS_NUM_PLL200M > 11)
    _CYHAL_CLOCK_CREATE(PLL200, 11),
#endif
#if (SRSS_NUM_PLL200M > 12)
    _CYHAL_CLOCK_CREATE(PLL200, 12),
#endif
#if (SRSS_NUM_PLL200M > 13)
    _CYHAL_CLOCK_CREATE(PLL200, 13),
#endif
#if (SRSS_NUM_PLL200M > 14)
    _CYHAL_CLOCK_CREATE(PLL200, 14),
#endif
};
#endif

#if (SRSS_NUM_PLL400M > 0)
#if defined(COMPONENT_CAT1B)
const cyhal_clock_t CYHAL_CLOCK_PLL[SRSS_NUM_PLL400M] =
{
#else
const cyhal_clock_t CYHAL_CLOCK_PLL400[SRSS_NUM_PLL400M] =
{
#endif
    _CYHAL_CLOCK_CREATE(PLL400, 0),
#if (SRSS_NUM_PLL400M > 1)
    _CYHAL_CLOCK_CREATE(PLL400, 1),
#endif
#if (SRSS_NUM_PLL400M > 2)
    _CYHAL_CLOCK_CREATE(PLL400, 2),
#endif
#if (SRSS_NUM_PLL400M > 3)
    _CYHAL_CLOCK_CREATE(PLL400, 3),
#endif
#if (SRSS_NUM_PLL400M > 4)
    _CYHAL_CLOCK_CREATE(PLL400, 4),
#endif
#if (SRSS_NUM_PLL400M > 5)
    _CYHAL_CLOCK_CREATE(PLL400, 5),
#endif
#if (SRSS_NUM_PLL400M > 6)
    _CYHAL_CLOCK_CREATE(PLL400, 6),
#endif
#if (SRSS_NUM_PLL400M > 7)
    _CYHAL_CLOCK_CREATE(PLL400, 7),
#endif
#if (SRSS_NUM_PLL400M > 8)
    _CYHAL_CLOCK_CREATE(PLL400, 8),
#endif
#if (SRSS_NUM_PLL400M > 9)
    _CYHAL_CLOCK_CREATE(PLL400, 9),
#endif
#if (SRSS_NUM_PLL400M > 10)
    _CYHAL_CLOCK_CREATE(PLL400, 10),
#endif
#if (SRSS_NUM_PLL400M > 11)
    _CYHAL_CLOCK_CREATE(PLL400, 11),
#endif
#if (SRSS_NUM_PLL400M > 12)
    _CYHAL_CLOCK_CREATE(PLL400, 12),
#endif
#if (SRSS_NUM_PLL400M > 13)
    _CYHAL_CLOCK_CREATE(PLL400, 13),
#endif
#if (SRSS_NUM_PLL400M > 14)
    _CYHAL_CLOCK_CREATE(PLL400, 14),
#endif
};
#endif
#endif

#if defined(COMPONENT_CAT1D)
const cyhal_clock_t CYHAL_CLOCK_DPLL_LP[SRSS_NUM_DPLL_LP] =
{
#if (SRSS_NUM_DPLL_LP > 0)
    _CYHAL_CLOCK_CREATE(DPLL_LP, 0),
#endif
#if (SRSS_NUM_DPLL_LP > 1)
    _CYHAL_CLOCK_CREATE(DPLL_LP, 1),
#endif
#if (SRSS_NUM_DPLL_LP > 2)
    _CYHAL_CLOCK_CREATE(DPLL_LP, 2),
#endif
#if (SRSS_NUM_DPLL_LP > 3)
    _CYHAL_CLOCK_CREATE(DPLL_LP, 4),
#endif
#if (SRSS_NUM_DPLL_LP > 4)
    _CYHAL_CLOCK_CREATE(DPLL_LP, 4),
#endif
};
const cyhal_clock_t CYHAL_CLOCK_DPLL_HP[SRSS_NUM_DPLL_HP] =
{
#if (SRSS_NUM_DPLL_HP > 0)
    _CYHAL_CLOCK_CREATE(DPLL_HP, 0),
#endif
#if (SRSS_NUM_DPLL_HP > 1)
    _CYHAL_CLOCK_CREATE(DPLL_HP, 1),
#endif
#if (SRSS_NUM_DPLL_HP > 2)
    _CYHAL_CLOCK_CREATE(DPLL_HP, 2),
#endif
#if (SRSS_NUM_DPLL_HP > 3)
    _CYHAL_CLOCK_CREATE(DPLL_HP, 4),
#endif
#if (SRSS_NUM_DPLL_HP > 4)
    _CYHAL_CLOCK_CREATE(DPLL_HP, 4),
#endif
};
#endif /* defined(COMPONENT_CAT1D) */



/******************************************************************************
 **************************** Public API (clocks) *****************************
 *****************************************************************************/

cy_rslt_t _cyhal_clock_allocate_channel(cyhal_clock_t *clock, cyhal_clock_block_t block, const void* funcs)
{
    uint8_t maxChannels = (uint8_t)_cyhal_utils_get_clock_count(block);
    for (uint8_t i = 0; i < maxChannels; i++)
    {
        cyhal_resource_inst_t clock_resource = { CYHAL_RSC_CLOCK, block, i };
        if (CY_RSLT_SUCCESS == cyhal_hwmgr_reserve(&clock_resource))
        {
            clock->block = block;
            clock->channel = i;
            clock->reserved = true;
            clock->funcs = funcs;
            return CY_RSLT_SUCCESS;
        }
    }
    return CYHAL_HWMGR_RSLT_ERR_NONE_FREE;
}

cy_rslt_t cyhal_clock_get(cyhal_clock_t *clock, const cyhal_resource_inst_t *resource)
{
    CY_ASSERT(NULL != clock);
    CY_ASSERT(NULL != resource);
    CY_ASSERT(CYHAL_RSC_CLOCK == resource->type);

    clock->block = (cyhal_clock_block_t)resource->block_num;
    clock->channel = resource->channel_num;
    clock->reserved = false;
    clock->funcs = _cyhal_clock_get_funcs_all((cyhal_clock_block_t)resource->block_num);

    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_clock_reserve(cyhal_clock_t *clock, const cyhal_clock_t *clock_)
{
    CY_ASSERT(NULL != clock);
    CY_ASSERT(NULL != clock_);

    cyhal_resource_inst_t clock_resource = { CYHAL_RSC_CLOCK, clock_->block, clock_->channel };
    cy_rslt_t rslt = cyhal_hwmgr_reserve(&clock_resource);
    if (CY_RSLT_SUCCESS == rslt)
    {
        memcpy(clock, clock_, sizeof(cyhal_clock_t));
        clock->reserved = true;
    }
    return rslt;
}

cyhal_clock_feature_t cyhal_clock_get_features(const cyhal_clock_t *clock)
{
    CY_ASSERT(NULL != clock);

    if (clock->block == CYHAL_CLOCK_BLOCK_HF)
    {
        return (clock->channel == 0)    // HF0 cannot be disabled
            ? (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_SOURCE | CYHAL_CLOCK_FEATURE_DIVIDER)
            : (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_SOURCE | CYHAL_CLOCK_FEATURE_DIVIDER);
    }
    else if (clock->block < 4 * _CYHAL_CLOCK_PERI_GROUPS)
        return (cyhal_clock_feature_t)(CYHAL_CLOCK_FEATURE_ENABLE | CYHAL_CLOCK_FEATURE_DIVIDER | CYHAL_CLOCK_FEATURE_FREQUENCY);
    else
        return ((cyhal_clock_funcs_t*)clock->funcs)->features;
}

bool cyhal_clock_is_enabled(const cyhal_clock_t *clock)
{
    CY_ASSERT(NULL != clock);

    if (clock->block == CYHAL_CLOCK_BLOCK_HF)
        return _cyhal_clock_is_enabled_hf(clock);
    else if (clock->block < 4 * _CYHAL_CLOCK_PERI_GROUPS)
        return _cyhal_clock_is_enabled_peripheral(clock);
    else
        return ((cyhal_clock_funcs_t*)clock->funcs)->is_enabled(clock);
}

cy_rslt_t cyhal_clock_set_enabled(cyhal_clock_t *clock, bool enabled, bool wait_for_lock)
{
    CY_ASSERT(NULL != clock);

    if (clock->block == CYHAL_CLOCK_BLOCK_HF)
        return _cyhal_clock_set_enabled_hf(clock, enabled, wait_for_lock);
    else if (clock->block < 4 * _CYHAL_CLOCK_PERI_GROUPS)
        return _cyhal_clock_set_enabled_peripheral(clock, enabled, wait_for_lock);
    else
        return ((cyhal_clock_funcs_t*)clock->funcs)->set_enabled(clock, enabled, wait_for_lock);
}

uint32_t cyhal_clock_get_frequency(const cyhal_clock_t *clock)
{
    CY_ASSERT(NULL != clock);

    if (cyhal_clock_is_enabled(clock))
    {
        if (clock->block == CYHAL_CLOCK_BLOCK_HF)
            return _cyhal_clock_get_frequency_hf(clock);
        else if (clock->block < 4 * _CYHAL_CLOCK_PERI_GROUPS)
            return _cyhal_clock_get_frequency_peripheral(clock);
        else
            return ((cyhal_clock_funcs_t*)clock->funcs)->get_frequency(clock);
    }
    return 0;
}

cy_rslt_t cyhal_clock_set_frequency(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_ASSERT(NULL != clock);

    if (clock->block == CYHAL_CLOCK_BLOCK_HF)
        return _cyhal_clock_set_frequency_unsupported(clock, hz, tolerance);
    else if (clock->block < 4 * _CYHAL_CLOCK_PERI_GROUPS)
        return _cyhal_clock_set_frequency_peripheral(clock, hz, tolerance);
    else
        return ((cyhal_clock_funcs_t*)clock->funcs)->set_frequency(clock, hz, tolerance);
}

cy_rslt_t cyhal_clock_set_divider(cyhal_clock_t *clock, uint32_t divider)
{
    CY_ASSERT(NULL != clock);

    if (clock->block == CYHAL_CLOCK_BLOCK_HF)
        return _cyhal_clock_set_divider_hf(clock, divider);
    else if (clock->block < 4 * _CYHAL_CLOCK_PERI_GROUPS)
        return _cyhal_clock_set_divider_peripheral(clock, divider);
    else
        return ((cyhal_clock_funcs_t*)clock->funcs)->set_divider(clock, divider);
}

cy_rslt_t cyhal_clock_get_sources(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count)
{
    CY_ASSERT(NULL != clock);

    if (clock->block == CYHAL_CLOCK_BLOCK_HF)
        return _cyhal_clock_get_sources_hf(clock, sources, count);
    else if (clock->block < 4 * _CYHAL_CLOCK_PERI_GROUPS)
        return _cyhal_clock_get_sources_peripheral(clock, sources, count);
    else
        return ((cyhal_clock_funcs_t*)clock->funcs)->get_sources(clock, sources, count);
}

cy_rslt_t cyhal_clock_set_source(cyhal_clock_t *clock, const cyhal_clock_t *source)
{
    CY_ASSERT(NULL != clock && NULL != source);

    if (clock->block == CYHAL_CLOCK_BLOCK_HF)
        return _cyhal_clock_set_source_hf(clock, source);
    else if (clock->block < 4 * _CYHAL_CLOCK_PERI_GROUPS)
        return _cyhal_clock_set_source_unsupported(clock, source);
    else
        return ((cyhal_clock_funcs_t*)clock->funcs)->set_source(clock, source);
}

void cyhal_clock_free(cyhal_clock_t *clock)
{
    CY_ASSERT(NULL != clock);
    CY_ASSERT(clock->reserved);

    cyhal_resource_inst_t rsc = { CYHAL_RSC_CLOCK, clock->block, clock->channel };
    cyhal_hwmgr_free(&rsc);
    clock->reserved = false;
}

#if defined(__cplusplus)
}
#endif

#endif // CYHAL_DRIVER_AVAILABLE_CLOCK
