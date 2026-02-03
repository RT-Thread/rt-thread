/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g4fr_pwr.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32G4FR_PWR_H__
#define __N32G4FR_PWR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g4fr.h"

/** @addtogroup N32G4FR_StdPeriph_Driver
 * @{
 */

/** @addtogroup PWR
 * @{
 */

/** @addtogroup PWR_Exported_Types
 * @{
 */

/**
 * @}
 */

/** @addtogroup PWR_Exported_Constants
 * @{
 */

/** @addtogroup PVD_detection_level
 * @{
 */

#define PWR_PVDRANGRE_2V2 ((uint32_t)0x00000000)
#define PWR_PVDRANGRE_2V3 ((uint32_t)0x00000020)
#define PWR_PVDRANGRE_2V4 ((uint32_t)0x00000040)
#define PWR_PVDRANGRE_2V5 ((uint32_t)0x00000060)
#define PWR_PVDRANGRE_2V6 ((uint32_t)0x00000080)
#define PWR_PVDRANGRE_2V7 ((uint32_t)0x000000A0)
#define PWR_PVDRANGRE_2V8 ((uint32_t)0x000000C0)
#define PWR_PVDRANGRE_2V9 ((uint32_t)0x000000E0)

#define PWR_PVDRANGE_1V78 ((uint32_t)0x00000200)
#define PWR_PVDRANGE_1V88 ((uint32_t)0x00000220)
#define PWR_PVDRANGE_1V98 ((uint32_t)0x00000240)
#define PWR_PVDRANGE_2V08 ((uint32_t)0x00000260)
#define PWR_PVDRANGE_3V06 ((uint32_t)0x00000280)
#define PWR_PVDRANGE_3V24 ((uint32_t)0x000002A0)
#define PWR_PVDRANGE_3V42 ((uint32_t)0x000002C0)
#define PWR_PVDRANGE_3V60 ((uint32_t)0x000002E0)
#define IS_PWR_PVD_LEVEL(LEVEL)                                                                                        \
    (((LEVEL) == PWR_PVDRANGRE_2V2) || ((LEVEL) == PWR_PVDRANGRE_2V3) || ((LEVEL) == PWR_PVDRANGRE_2V4)                \
     || ((LEVEL) == PWR_PVDRANGRE_2V5) || ((LEVEL) == PWR_PVDRANGRE_2V6) || ((LEVEL) == PWR_PVDRANGRE_2V7)             \
     || ((LEVEL) == PWR_PVDRANGRE_2V8) || ((LEVEL) == PWR_PVDRANGRE_2V9) || ((LEVEL) == PWR_PVDRANGE_1V78)             \
     || ((LEVEL) == PWR_PVDRANGE_1V88) || ((LEVEL) == PWR_PVDRANGE_1V98) || ((LEVEL) == PWR_PVDRANGE_2V08)             \
     || ((LEVEL) == PWR_PVDRANGE_3V06) || ((LEVEL) == PWR_PVDRANGE_3V24) || ((LEVEL) == PWR_PVDRANGE_3V42)             \
     || ((LEVEL) == PWR_PVDRANGE_3V60))

/**
 * @}
 */

/** @addtogroup Regulator_state_is_STOP_mode
 * @{
 */

#define PWR_REGULATOR_ON            ((uint32_t)0x00000000)
#define PWR_REGULATOR_LOWPOWER      ((uint32_t)0x00000001)
#define IS_PWR_REGULATOR(REGULATOR) (((REGULATOR) == PWR_REGULATOR_ON) || ((REGULATOR) == PWR_REGULATOR_LOWPOWER))
/**
 * @}
 */

/** @addtogroup STOP_mode_entry
 * @{
 */

#define PWR_STOPENTRY_WFI        ((uint8_t)0x01)
#define PWR_STOPENTRY_WFE        ((uint8_t)0x02)
#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPENTRY_WFI) || ((ENTRY) == PWR_STOPENTRY_WFE))

/**
 * @}
 */

/** @addtogroup PWR_Flag
 * @{
 */

#define PWR_WU_FLAG    ((uint32_t)0x00000001)
#define PWR_SB_FLAG    ((uint32_t)0x00000002)
#define PWR_PVDO_FLAG  ((uint32_t)0x00000004)
#define PWR_VBATF_FLAG ((uint32_t)0x00000008)
#define IS_PWR_GET_FLAG(FLAG)                                                                                          \
    (((FLAG) == PWR_WU_FLAG) || ((FLAG) == PWR_SB_FLAG) || ((FLAG) == PWR_PVDO_FLAG) || ((FLAG) == PWR_VBATF_FLAG))

#define IS_PWR_CLEAR_FLAG(FLAG) (((FLAG) == PWR_WU_FLAG) || ((FLAG) == PWR_SB_FLAG) || ((FLAG) == PWR_VBATF_FLAG))
/**
 * @}
 */

/**
 * @}
 */

/** @addtogroup PWR_Exported_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup PWR_Exported_Functions
 * @{
 */

void PWR_DeInit(void);
void PWR_BackupAccessEnable(FunctionalState Cmd);
void PWR_PvdEnable(FunctionalState Cmd);
void PWR_PvdRangeConfig(uint32_t PWR_PVDLevel);
void PWR_WakeUpPinEnable(FunctionalState Cmd);
void PWR_EnterStopState(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
void PWR_EnterSLEEPMode(uint8_t SLEEPONEXIT, uint8_t PWR_STOPEntry);
void PWR_EnterSTOP2Mode(uint8_t PWR_STOPEntry);
void PWR_EnterStandbyState(void);
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __N32G4FR_PWR_H__ */
       /**
        * @}
        */

/**
 * @}
 */

/**
 * @}
 */
