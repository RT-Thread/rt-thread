/***************************************************************************//**
* \file cy_device.c
* \version 2.30
*
* This file provides the definitions for core and peripheral block HW base
* addresses, versions, and parameters.
*
********************************************************************************
* \copyright
* Copyright 2018-2019 Cypress Semiconductor Corporation
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

#include "cy_device.h"

/*******************************************************************************
*                   Global Variables
*******************************************************************************/

/* This is set in Cy_PDL_Init() to the device information relevant
 * for the current target.
 */
const cy_stc_device_t * cy_device;

/* Platform and peripheral block configuration */
const cy_stc_device_t cy_deviceIpBlockCfgPSoC6_01 =
{
    /* Base HW addresses */
    /* cpussBase                 */ 0x40210000UL,
    /* flashcBase                */ 0x40250000UL,
    /* periBase                  */ 0x40010000UL,
    /* udbBase                   */ 0x40340000UL,
    /* protBase                  */ 0x40240000UL,
    /* hsiomBase                 */ 0x40310000UL,
    /* gpioBase                  */ 0x40320000UL,
    /* passBase                  */ 0x411F0000UL,
    /* ipcBase                   */ 0x40230000UL,
    /* cryptoBase                */ 0x40110000UL,
    /* sar0Base                  */ 0x411D0000UL,

    /* IP block versions [7:4] major, [3:0] minor */
    /* cpussVersion              */ 0x10U,
    /* cryptoVersion             */ 0x10U,
    /* dwVersion                 */ 0x10U,
    /* ipcVersion                */ 0x10U,
    /* periVersion               */ 0x10U,
    /* srssVersion               */ 0x10U,
    /* passVersion               */ 0x10U,

    /* Parameters  */
    /* cpussIpcNr                */ 16U,
    /* cpussIpcIrqNr             */ 16U,
    /* cpussDw0ChNr              */ 16U,
    /* cpussDw1ChNr              */ 16U,
    /* cpussFlashPaSize          */ 128U,
    /* cpussIpc0Irq              */ 25,
    /* cpussFmIrq                */ 85,
    /* cpussNotConnectedIrq      */ 240,
    /* srssNumClkpath            */ 5U,
    /* srssNumPll                */ 1U,
    /* srssNumHfroot             */ 5U,
    /* srssIsPiloPresent         */ 1U,
    /* periClockNr               */ 59U,
    /* smifDeviceNr              */ 4U,
    /* passSarChannels           */ 16U,
    /* epMonitorNr               */ 28u,
    /* udbPresent                */ 1U,
    /* sysPmSimoPresent          */ 1U,
    /* protBusMasterMask         */ 0xC00FUL,
    /* cryptoMemSize             */ 1024u,
    /* flashRwwRequired          */ 1U,
    /* flashPipeRequired         */ 1U,
    /* flashWriteDelay           */ 1U,
    /* flashProgramDelay         */ 1U,
    /* flashEraseDelay           */ 1U,
    /* flashCtlMainWs0Freq       */ 29U,
    /* flashCtlMainWs1Freq       */ 58U,
    /* flashCtlMainWs2Freq       */ 87U,
    /* flashCtlMainWs3Freq       */ 120U,
    /* flashCtlMainWs4Freq       */ 150U,
    /* tcpwmCC1Present           */ 0U,
    /* tcpwmAMCPresent           */ 0U,
    /* tcpwmSMCPrecent           */ 0U,

    /* Peripheral register offsets */

    /* DW registers */
    /* dwChOffset                */ (uint16_t)offsetof(DW_V1_Type, CH_STRUCT),
    /* dwChSize                  */ (uint16_t)sizeof(DW_CH_STRUCT_V1_Type),
    /* dwChCtlPrioPos            */ (uint8_t)DW_CH_STRUCT_CH_CTL_PRIO_Pos,
    /* dwChCtlPreemptablePos     */ (uint8_t)DW_CH_STRUCT_CH_CTL_PREEMPTABLE_Pos,
    /* dwStatusChIdxPos          */ (uint8_t)DW_STATUS_CH_IDX_Pos,
    /* dwStatusChIdxMsk          */ DW_STATUS_CH_IDX_Msk,

    /* PERI registers */
    /* periTrCmdOffset           */ (uint16_t)offsetof(PERI_V1_Type, TR_CMD),
    /* periTrCmdGrSelMsk         */ (uint16_t)PERI_TR_CMD_GROUP_SEL_Msk,
    /* periTrGrOffset            */ (uint16_t)offsetof(PERI_V1_Type, TR_GR),
    /* periTrGrSize              */ (uint16_t)sizeof(PERI_TR_GR_V1_Type),

    /* periDivCmdDivSelMsk       */ (uint8_t)PERI_DIV_CMD_DIV_SEL_Msk,
    /* periDivCmdTypeSelPos      */ (uint8_t)PERI_DIV_CMD_TYPE_SEL_Pos,
    /* periDivCmdPaDivSelPos     */ (uint8_t)PERI_DIV_CMD_PA_DIV_SEL_Pos,
    /* periDivCmdPaTypeSelPos    */ (uint8_t)PERI_DIV_CMD_PA_TYPE_SEL_Pos,

    /* periDiv8CtlOffset         */ (uint16_t)offsetof(PERI_V1_Type, DIV_8_CTL),
    /* periDiv16CtlOffset        */ (uint16_t)offsetof(PERI_V1_Type, DIV_16_CTL),
    /* periDiv16_5CtlOffset      */ (uint16_t)offsetof(PERI_V1_Type, DIV_16_5_CTL),
    /* periDiv24_5CtlOffset      */ (uint16_t)offsetof(PERI_V1_Type, DIV_24_5_CTL),

    /* GPIO registers */
    /* gpioPrtIntrCfgOffset      */ (uint8_t)offsetof(GPIO_PRT_V1_Type, INTR_CFG),
    /* gpioPrtCfgOffset          */ (uint8_t)offsetof(GPIO_PRT_V1_Type, CFG),
    /* gpioPrtCfgInOffset        */ (uint8_t)offsetof(GPIO_PRT_V1_Type, CFG_IN),
    /* gpioPrtCfgOutOffset       */ (uint8_t)offsetof(GPIO_PRT_V1_Type, CFG_OUT),
    /* gpioPrtCfgSioOffset       */ (uint8_t)offsetof(GPIO_PRT_V1_Type, CFG_SIO),

    /* CPUSS registers  */
    /* cpussCm0ClockCtlOffset    */ offsetof(CPUSS_V1_Type, CM0_CLOCK_CTL),
    /* cpussCm4ClockCtlOffset    */ offsetof(CPUSS_V1_Type, CM4_CLOCK_CTL),
    /* cpussCm4StatusOffset      */ offsetof(CPUSS_V1_Type, CM4_STATUS),
    /* cpussCm0StatusOffset      */ offsetof(CPUSS_V1_Type, CM0_STATUS),
    /* cpussCm4PwrCtlOffset      */ offsetof(CPUSS_V1_Type, CM4_PWR_CTL),
    /* cpussTrimRamCtlOffset     */ offsetof(CPUSS_V1_Type, TRIM_RAM_CTL),
    /* cpussTrimRomCtlOffset     */ offsetof(CPUSS_V1_Type, TRIM_ROM_CTL),
    /* cpussSysTickCtlOffset     */ offsetof(CPUSS_V1_Type, SYSTICK_CTL),

    /* cpussCm0NmiCtlOffset      */ (uint16_t)offsetof(CPUSS_V1_Type, CM0_NMI_CTL),
    /* cpussCm4NmiCtlOffset      */ (uint16_t)offsetof(CPUSS_V1_Type, CM4_NMI_CTL),
    /* cpussRomCtl               */ (uint16_t)offsetof(CPUSS_V1_Type, ROM_CTL),
    /* cpussRam0Ctl0             */ (uint16_t)offsetof(CPUSS_V1_Type, RAM0_CTL0),
    /* cpussRam1Ctl0             */ (uint16_t)offsetof(CPUSS_V1_Type, RAM1_CTL0),
    /* cpussRam2Ctl0             */ (uint16_t)offsetof(CPUSS_V1_Type, RAM2_CTL0),
    /* cpussRam0PwrCtl           */ (uint16_t)offsetof(CPUSS_V1_Type, RAM0_PWR_MACRO_CTL),
    /* cpussRam1PwrCtl           */ (uint16_t)offsetof(CPUSS_V1_Type, RAM1_PWR_CTL),
    /* cpussRam2PwrCtl           */ (uint16_t)offsetof(CPUSS_V1_Type, RAM2_PWR_CTL),

    /* IPC registers */
    /* ipcStructSize             */ (uint16_t)sizeof(IPC_STRUCT_V1_Type),
    /* ipcLockStatusOffset       */ offsetof(IPC_STRUCT_V1_Type, LOCK_STATUS),
};

const cy_stc_device_t cy_deviceIpBlockCfgPSoC6_02 =
{
    /* Base HW addresses */
    /* cpussBase                 */ 0x40200000UL,
    /* flashcBase                */ 0x40240000UL,
    /* periBase                  */ 0x40000000UL,
    /* udbBase                   */ 0UL,
    /* protBase                  */ 0x40230000UL,
    /* hsiomBase                 */ 0x40300000UL,
    /* gpioBase                  */ 0x40310000UL,
    /* passBase                  */ 0x409F0000UL,
    /* ipcBase                   */ 0x40220000UL,
    /* cryptoBase                */ 0x40100000UL,
    /* sar0Base                  */ 0x409D0000UL,

    /* IP block versions [7:4] major, [3:0] minor */
    /* cpussVersion              */ 0x20U,
    /* cryptoVersion             */ 0x20U,
    /* dwVersion                 */ 0x20U,
    /* ipcVersion                */ 0x20U,
    /* periVersion               */ 0x20U,
    /* srssVersion               */ 0x10U,
    /* passVersion               */ 0x10U,

    /* Parameters */
    /* cpussIpcNr                */ 16U,
    /* cpussIpcIrqNr             */ 16U,
    /* cpussDw0ChNr              */ 29U,
    /* cpussDw1ChNr              */ 29U,
    /* cpussFlashPaSize          */ 128U,
    /* cpussIpc0Irq              */ 23,
    /* cpussFmIrq                */ 117,
    /* cpussNotConnectedIrq      */ 1023,
    /* srssNumClkpath            */ 6U,
    /* srssNumPll                */ 2U,
    /* srssNumHfroot             */ 6U,
    /* srssIsPiloPresent         */ 0U,
    /* periClockNr               */ 54U,
    /* smifDeviceNr              */ 4U,
    /* passSarChannels           */ 16U,
    /* epMonitorNr               */ 32u,
    /* udbPresent                */ 0U,
    /* sysPmSimoPresent          */ 0U,
    /* protBusMasterMask         */ 0xC07FUL,
    /* cryptoMemSize             */ 1024u,
    /* flashRwwRequired          */ 0U,
    /* flashPipeRequired         */ 0U,
    /* flashWriteDelay           */ 0U,
    /* flashProgramDelay         */ 0U,
    /* flashEraseDelay           */ 0U,
    /* flashCtlMainWs0Freq       */ 25U,
    /* flashCtlMainWs1Freq       */ 50U,
    /* flashCtlMainWs2Freq       */ 75U,
    /* flashCtlMainWs3Freq       */ 100U,
    /* flashCtlMainWs4Freq       */ 125U,
    /* tcpwmCC1Present           */ 0U,
    /* tcpwmAMCPresent           */ 0U,
    /* tcpwmSMCPrecent           */ 0U,

    /* Peripheral register offsets */

    /* DW registers */
    /* dwChOffset                */ (uint16_t)offsetof(DW_V2_Type, CH_STRUCT),
    /* dwChSize                  */ (uint16_t)sizeof(DW_CH_STRUCT_V2_Type),
    /* dwChCtlPrioPos            */ (uint8_t)DW_CH_STRUCT_V2_CH_CTL_PRIO_Pos,
    /* dwChCtlPreemptablePos     */ (uint8_t)DW_CH_STRUCT_V2_CH_CTL_PREEMPTABLE_Pos,
    /* dwStatusChIdxPos          */ (uint8_t)DW_V2_STATUS_CH_IDX_Pos,
    /* dwStatusChIdxMsk          */ DW_V2_STATUS_CH_IDX_Msk,

    /* PERI registers  */
    /* periTrCmdOffset           */ (uint16_t)offsetof(PERI_V2_Type, TR_CMD),
    /* periTrCmdGrSelMsk         */ (uint16_t)PERI_V2_TR_CMD_GROUP_SEL_Msk,
    /* periTrGrOffset            */ (uint16_t)offsetof(PERI_V2_Type, TR_GR),
    /* periTrGrSize              */ (uint16_t)sizeof(PERI_TR_GR_V2_Type),

    /* periDivCmdDivSelMsk       */ (uint8_t)PERI_V2_DIV_CMD_DIV_SEL_Msk,
    /* periDivCmdTypeSelPos      */ (uint8_t)PERI_V2_DIV_CMD_TYPE_SEL_Pos,
    /* periDivCmdPaDivSelPos     */ (uint8_t)PERI_V2_DIV_CMD_PA_DIV_SEL_Pos,
    /* periDivCmdPaTypeSelPos    */ (uint8_t)PERI_V2_DIV_CMD_PA_TYPE_SEL_Pos,

    /* periDiv8CtlOffset         */ (uint16_t)offsetof(PERI_V2_Type, DIV_8_CTL),
    /* periDiv16CtlOffset        */ (uint16_t)offsetof(PERI_V2_Type, DIV_16_CTL),
    /* periDiv16_5CtlOffset      */ (uint16_t)offsetof(PERI_V2_Type, DIV_16_5_CTL),
    /* periDiv24_5CtlOffset      */ (uint16_t)offsetof(PERI_V2_Type, DIV_24_5_CTL),

    /* GPIO registers  */
    /* gpioPrtIntrCfgOffset      */ (uint8_t)offsetof(GPIO_PRT_V2_Type, INTR_CFG),
    /* gpioPrtCfgOffset          */ (uint8_t)offsetof(GPIO_PRT_V2_Type, CFG),
    /* gpioPrtCfgInOffset        */ (uint8_t)offsetof(GPIO_PRT_V2_Type, CFG_IN),
    /* gpioPrtCfgOutOffset       */ (uint8_t)offsetof(GPIO_PRT_V2_Type, CFG_OUT),
    /* gpioPrtCfgSioOffset       */ (uint8_t)offsetof(GPIO_PRT_V2_Type, CFG_SIO),

    /* CPUSS registers */
    /* cpussCm0ClockCtlOffset    */ offsetof(CPUSS_V2_Type, CM0_CLOCK_CTL),
    /* cpussCm4ClockCtlOffset    */ offsetof(CPUSS_V2_Type, CM4_CLOCK_CTL),
    /* cpussCm4StatusOffset      */ offsetof(CPUSS_V2_Type, CM4_STATUS),
    /* cpussCm0StatusOffset      */ offsetof(CPUSS_V2_Type, CM0_STATUS),
    /* cpussCm4PwrCtlOffset      */ offsetof(CPUSS_V2_Type, CM4_PWR_CTL),
    /* cpussTrimRamCtlOffset     */ offsetof(CPUSS_V2_Type, TRIM_RAM_CTL),
    /* cpussTrimRomCtlOffset     */ offsetof(CPUSS_V2_Type, TRIM_ROM_CTL),
    /* cpussSysTickCtlOffset     */ offsetof(CPUSS_V2_Type, SYSTICK_CTL),
    /* cpussCm0NmiCtlOffset      */ (uint16_t)offsetof(CPUSS_V2_Type, CM0_NMI_CTL),
    /* cpussCm4NmiCtlOffset      */ (uint16_t)offsetof(CPUSS_V2_Type, CM4_NMI_CTL),
    /* cpussRomCtl               */ (uint16_t)offsetof(CPUSS_V2_Type, ROM_CTL),
    /* cpussRam0Ctl0             */ (uint16_t)offsetof(CPUSS_V2_Type, RAM0_CTL0),
    /* cpussRam1Ctl0             */ (uint16_t)offsetof(CPUSS_V2_Type, RAM1_CTL0),
    /* cpussRam2Ctl0             */ (uint16_t)offsetof(CPUSS_V2_Type, RAM2_CTL0),
    /* cpussRam0PwrCtl           */ (uint16_t)offsetof(CPUSS_V2_Type, RAM0_PWR_MACRO_CTL),
    /* cpussRam1PwrCtl           */ (uint16_t)offsetof(CPUSS_V2_Type, RAM1_PWR_CTL),
    /* cpussRam2PwrCtl           */ (uint16_t)offsetof(CPUSS_V2_Type, RAM2_PWR_CTL),

    /* IPC registers */
    /* ipcStructSize             */ (uint16_t)sizeof(IPC_STRUCT_V2_Type),
    /* ipcLockStatusOffset       */ offsetof(IPC_STRUCT_V2_Type, LOCK_STATUS),
};

const cy_stc_device_t cy_deviceIpBlockCfgPSoC6_03 =
{
    /* Base HW addresses */
    /* cpussBase                 */ 0x40200000UL,
    /* flashcBase                */ 0x40240000UL,
    /* periBase                  */ 0x40000000UL,
    /* udbBase                   */ 0UL,
    /* protBase                  */ 0x40230000UL,
    /* hsiomBase                 */ 0x40300000UL,
    /* gpioBase                  */ 0x40310000UL,
    /* passBase                  */ 0x409F0000UL,
    /* ipcBase                   */ 0x40220000UL,
    /* cryptoBase                */ 0x40100000UL,
    /* sar0Base                  */ 0x409D0000UL,

    /* IP block versions [7:4] major, [3:0] minor */
    /* cpussVersion              */ 0x20U,
    /* cryptoVersion             */ 0x20U,
    /* dwVersion                 */ 0x20U,
    /* ipcVersion                */ 0x20U,
    /* periVersion               */ 0x20U,
    /* srssVersion               */ 0x13U,
    /* passVersion               */ 0x10U,

    /* Parameters */
    /* cpussIpcNr                */ 16U,
    /* cpussIpcIrqNr             */ 16U,
    /* cpussDw0ChNr              */ 29U,
    /* cpussDw1ChNr              */ 32U,
    /* cpussFlashPaSize          */ 128U,
    /* cpussIpc0Irq              */ 23,
    /* cpussFmIrq                */ 117,
    /* cpussNotConnectedIrq      */ 1023,
    /* srssNumClkpath            */ 5U,
    /* srssNumPll                */ 1U,
    /* srssNumHfroot             */ 5U,
    /* srssIsPiloPresent         */ 0U,
    /* periClockNr               */ 28U,
    /* smifDeviceNr              */ 3U,
    /* passSarChannels           */ 16U,
    /* epMonitorNr               */ 0u,
    /* udbPresent                */ 0U,
    /* sysPmSimoPresent          */ 0U,
    /* protBusMasterMask         */ 0xC03FUL,
    /* cryptoMemSize             */ 1024u,
    /* flashRwwRequired          */ 0U,
    /* flashPipeRequired         */ 0U,
    /* flashWriteDelay           */ 0U,
    /* flashProgramDelay         */ 0U,
    /* flashEraseDelay           */ 0U,
    /* flashCtlMainWs0Freq       */ 25U,
    /* flashCtlMainWs1Freq       */ 50U,
    /* flashCtlMainWs2Freq       */ 75U,
    /* flashCtlMainWs3Freq       */ 100U,
    /* flashCtlMainWs4Freq       */ 125U,
    /* tcpwmCC1Present           */ 0U,
    /* tcpwmAMCPresent           */ 0U,
    /* tcpwmSMCPrecent           */ 0U,

    /* Peripheral register offsets */

    /* DW registers */
    /* dwChOffset                */ (uint16_t)offsetof(DW_V2_Type, CH_STRUCT),
    /* dwChSize                  */ (uint16_t)sizeof(DW_CH_STRUCT_V2_Type),
    /* dwChCtlPrioPos            */ (uint8_t)DW_CH_STRUCT_V2_CH_CTL_PRIO_Pos,
    /* dwChCtlPreemptablePos     */ (uint8_t)DW_CH_STRUCT_V2_CH_CTL_PREEMPTABLE_Pos,
    /* dwStatusChIdxPos          */ (uint8_t)DW_V2_STATUS_CH_IDX_Pos,
    /* dwStatusChIdxMsk          */ DW_V2_STATUS_CH_IDX_Msk,

    /* PERI registers  */
    /* periTrCmdOffset           */ (uint16_t)offsetof(PERI_V2_Type, TR_CMD),
    /* periTrCmdGrSelMsk         */ (uint16_t)PERI_V2_TR_CMD_GROUP_SEL_Msk,
    /* periTrGrOffset            */ (uint16_t)offsetof(PERI_V2_Type, TR_GR),
    /* periTrGrSize              */ (uint16_t)sizeof(PERI_TR_GR_V2_Type),

    /* periDivCmdDivSelMsk       */ (uint8_t)PERI_V2_DIV_CMD_DIV_SEL_Msk,
    /* periDivCmdTypeSelPos      */ (uint8_t)PERI_V2_DIV_CMD_TYPE_SEL_Pos,
    /* periDivCmdPaDivSelPos     */ (uint8_t)PERI_V2_DIV_CMD_PA_DIV_SEL_Pos,
    /* periDivCmdPaTypeSelPos    */ (uint8_t)PERI_V2_DIV_CMD_PA_TYPE_SEL_Pos,

    /* periDiv8CtlOffset         */ (uint16_t)offsetof(PERI_V2_Type, DIV_8_CTL),
    /* periDiv16CtlOffset        */ (uint16_t)offsetof(PERI_V2_Type, DIV_16_CTL),
    /* periDiv16_5CtlOffset      */ (uint16_t)offsetof(PERI_V2_Type, DIV_16_5_CTL),
    /* periDiv24_5CtlOffset      */ (uint16_t)offsetof(PERI_V2_Type, DIV_24_5_CTL),

    /* GPIO registers  */
    /* gpioPrtIntrCfgOffset      */ (uint8_t)offsetof(GPIO_PRT_V2_Type, INTR_CFG),
    /* gpioPrtCfgOffset          */ (uint8_t)offsetof(GPIO_PRT_V2_Type, CFG),
    /* gpioPrtCfgInOffset        */ (uint8_t)offsetof(GPIO_PRT_V2_Type, CFG_IN),
    /* gpioPrtCfgOutOffset       */ (uint8_t)offsetof(GPIO_PRT_V2_Type, CFG_OUT),
    /* gpioPrtCfgSioOffset       */ (uint8_t)offsetof(GPIO_PRT_V2_Type, CFG_SIO),

    /* CPUSS registers */
    /* cpussCm0ClockCtlOffset    */ offsetof(CPUSS_V2_Type, CM0_CLOCK_CTL),
    /* cpussCm4ClockCtlOffset    */ offsetof(CPUSS_V2_Type, CM4_CLOCK_CTL),
    /* cpussCm4StatusOffset      */ offsetof(CPUSS_V2_Type, CM4_STATUS),
    /* cpussCm0StatusOffset      */ offsetof(CPUSS_V2_Type, CM0_STATUS),
    /* cpussCm4PwrCtlOffset      */ offsetof(CPUSS_V2_Type, CM4_PWR_CTL),
    /* cpussTrimRamCtlOffset     */ offsetof(CPUSS_V2_Type, TRIM_RAM_CTL),
    /* cpussTrimRomCtlOffset     */ offsetof(CPUSS_V2_Type, TRIM_ROM_CTL),
    /* cpussSysTickCtlOffset     */ offsetof(CPUSS_V2_Type, SYSTICK_CTL),
    /* cpussCm0NmiCtlOffset      */ (uint16_t)offsetof(CPUSS_V2_Type, CM0_NMI_CTL),
    /* cpussCm4NmiCtlOffset      */ (uint16_t)offsetof(CPUSS_V2_Type, CM4_NMI_CTL),
    /* cpussRomCtl               */ (uint16_t)offsetof(CPUSS_V2_Type, ROM_CTL),
    /* cpussRam0Ctl0             */ (uint16_t)offsetof(CPUSS_V2_Type, RAM0_CTL0),
    /* cpussRam1Ctl0             */ (uint16_t)offsetof(CPUSS_V2_Type, RAM1_CTL0),
    /* cpussRam2Ctl0             */ (uint16_t)offsetof(CPUSS_V2_Type, RAM2_CTL0),
    /* cpussRam0PwrCtl           */ (uint16_t)offsetof(CPUSS_V2_Type, RAM0_PWR_MACRO_CTL),
    /* cpussRam1PwrCtl           */ (uint16_t)offsetof(CPUSS_V2_Type, RAM1_PWR_CTL),
    /* cpussRam2PwrCtl           */ (uint16_t)offsetof(CPUSS_V2_Type, RAM2_PWR_CTL),

    /* IPC registers */
    /* ipcStructSize             */ (uint16_t)sizeof(IPC_STRUCT_V2_Type),
    /* ipcLockStatusOffset       */ offsetof(IPC_STRUCT_V2_Type, LOCK_STATUS),
};

const cy_stc_device_t cy_deviceIpBlockCfgPSoC6_04 =
{
    /* Base HW addresses */
    /* cpussBase                 */ 0x40200000UL,
    /* flashcBase                */ 0x40240000UL,
    /* periBase                  */ 0x40000000UL,
    /* udbBase                   */ 0UL,
    /* protBase                  */ 0x40230000UL,
    /* hsiomBase                 */ 0x40300000UL,
    /* gpioBase                  */ 0x40310000UL,
    /* passBase                  */ 0x409F0000UL,
    /* ipcBase                   */ 0x40220000UL,
    /* cryptoBase                */ 0x40100000UL,
    /* sar0Base                  */ 0x409B0000UL,

    /* IP block versions [7:4] major, [3:0] minor */
    /* cpussVersion              */ 0x20U,
    /* cryptoVersion             */ 0x20U,
    /* dwVersion                 */ 0x20U,
    /* ipcVersion                */ 0x20U,
    /* periVersion               */ 0x20U,
    /* srssVersion               */ 0x13U,
    /* passVersion               */ 0x20U,

    /* Parameters */
    /* cpussIpcNr                */ 16U,
    /* cpussIpcIrqNr             */ 16U,
    /* cpussDw0ChNr              */ 30U,
    /* cpussDw1ChNr              */ 32U,
    /* cpussFlashPaSize          */ 128U,
    /* cpussIpc0Irq              */ 23,
    /* cpussFmIrq                */ 117,
    /* cpussNotConnectedIrq      */ 1023,
    /* srssNumClkpath            */ 5U,
    /* srssNumPll                */ 1U,
    /* srssNumHfroot             */ 4U,
    /* srssIsPiloPresent         */ 0U,
    /* periClockNr               */ 28U,
    /* smifDeviceNr              */ 3U,
    /* passSarChannels           */ 16U,
    /* epMonitorNr               */ 0u,
    /* udbPresent                */ 0U,
    /* sysPmSimoPresent          */ 0U,
    /* protBusMasterMask         */ 0xC01FUL,
    /* cryptoMemSize             */ 1024u,
    /* flashRwwRequired          */ 0U,
    /* flashPipeRequired         */ 0U,
    /* flashWriteDelay           */ 0U,
    /* flashProgramDelay         */ 0U,
    /* flashEraseDelay           */ 0U,
    /* flashCtlMainWs0Freq       */ 25U,
    /* flashCtlMainWs1Freq       */ 50U,
    /* flashCtlMainWs2Freq       */ 75U,
    /* flashCtlMainWs3Freq       */ 100U,
    /* flashCtlMainWs4Freq       */ 125U,
    /* tcpwmCC1Present           */ 0x02U,
    /* tcpwmAMCPresent           */ 0x02U,
    /* tcpwmSMCPrecent           */ 0x00U,

    /* Peripheral register offsets */

    /* DW registers */
    /* dwChOffset                */ (uint16_t)offsetof(DW_V2_Type, CH_STRUCT),
    /* dwChSize                  */ (uint16_t)sizeof(DW_CH_STRUCT_V2_Type),
    /* dwChCtlPrioPos            */ (uint8_t)DW_CH_STRUCT_V2_CH_CTL_PRIO_Pos,
    /* dwChCtlPreemptablePos     */ (uint8_t)DW_CH_STRUCT_V2_CH_CTL_PREEMPTABLE_Pos,
    /* dwStatusChIdxPos          */ (uint8_t)DW_V2_STATUS_CH_IDX_Pos,
    /* dwStatusChIdxMsk          */ DW_V2_STATUS_CH_IDX_Msk,

    /* PERI registers  */
    /* periTrCmdOffset           */ (uint16_t)offsetof(PERI_V2_Type, TR_CMD),
    /* periTrCmdGrSelMsk         */ (uint16_t)PERI_V2_TR_CMD_GROUP_SEL_Msk,
    /* periTrGrOffset            */ (uint16_t)offsetof(PERI_V2_Type, TR_GR),
    /* periTrGrSize              */ (uint16_t)sizeof(PERI_TR_GR_V2_Type),

    /* periDivCmdDivSelMsk       */ (uint8_t)PERI_V2_DIV_CMD_DIV_SEL_Msk,
    /* periDivCmdTypeSelPos      */ (uint8_t)PERI_V2_DIV_CMD_TYPE_SEL_Pos,
    /* periDivCmdPaDivSelPos     */ (uint8_t)PERI_V2_DIV_CMD_PA_DIV_SEL_Pos,
    /* periDivCmdPaTypeSelPos    */ (uint8_t)PERI_V2_DIV_CMD_PA_TYPE_SEL_Pos,

    /* periDiv8CtlOffset         */ (uint16_t)offsetof(PERI_V2_Type, DIV_8_CTL),
    /* periDiv16CtlOffset        */ (uint16_t)offsetof(PERI_V2_Type, DIV_16_CTL),
    /* periDiv16_5CtlOffset      */ (uint16_t)offsetof(PERI_V2_Type, DIV_16_5_CTL),
    /* periDiv24_5CtlOffset      */ (uint16_t)offsetof(PERI_V2_Type, DIV_24_5_CTL),

    /* GPIO registers  */
    /* gpioPrtIntrCfgOffset      */ (uint8_t)offsetof(GPIO_PRT_V2_Type, INTR_CFG),
    /* gpioPrtCfgOffset          */ (uint8_t)offsetof(GPIO_PRT_V2_Type, CFG),
    /* gpioPrtCfgInOffset        */ (uint8_t)offsetof(GPIO_PRT_V2_Type, CFG_IN),
    /* gpioPrtCfgOutOffset       */ (uint8_t)offsetof(GPIO_PRT_V2_Type, CFG_OUT),
    /* gpioPrtCfgSioOffset       */ (uint8_t)offsetof(GPIO_PRT_V2_Type, CFG_SIO),

    /* CPUSS registers */
    /* cpussCm0ClockCtlOffset    */ offsetof(CPUSS_V2_Type, CM0_CLOCK_CTL),
    /* cpussCm4ClockCtlOffset    */ offsetof(CPUSS_V2_Type, CM4_CLOCK_CTL),
    /* cpussCm4StatusOffset      */ offsetof(CPUSS_V2_Type, CM4_STATUS),
    /* cpussCm0StatusOffset      */ offsetof(CPUSS_V2_Type, CM0_STATUS),
    /* cpussCm4PwrCtlOffset      */ offsetof(CPUSS_V2_Type, CM4_PWR_CTL),
    /* cpussTrimRamCtlOffset     */ offsetof(CPUSS_V2_Type, TRIM_RAM_CTL),
    /* cpussTrimRomCtlOffset     */ offsetof(CPUSS_V2_Type, TRIM_ROM_CTL),
    /* cpussSysTickCtlOffset     */ offsetof(CPUSS_V2_Type, SYSTICK_CTL),
    /* cpussCm0NmiCtlOffset      */ (uint16_t)offsetof(CPUSS_V2_Type, CM0_NMI_CTL),
    /* cpussCm4NmiCtlOffset      */ (uint16_t)offsetof(CPUSS_V2_Type, CM4_NMI_CTL),
    /* cpussRomCtl               */ (uint16_t)offsetof(CPUSS_V2_Type, ROM_CTL),
    /* cpussRam0Ctl0             */ (uint16_t)offsetof(CPUSS_V2_Type, RAM0_CTL0),
    /* cpussRam1Ctl0             */ (uint16_t)offsetof(CPUSS_V2_Type, RAM1_CTL0),
    /* cpussRam2Ctl0             */ (uint16_t)offsetof(CPUSS_V2_Type, RAM2_CTL0),
    /* cpussRam0PwrCtl           */ (uint16_t)offsetof(CPUSS_V2_Type, RAM0_PWR_MACRO_CTL),
    /* cpussRam1PwrCtl           */ (uint16_t)offsetof(CPUSS_V2_Type, RAM1_PWR_CTL),
    /* cpussRam2PwrCtl           */ (uint16_t)offsetof(CPUSS_V2_Type, RAM2_PWR_CTL),

    /* IPC registers */
    /* ipcStructSize             */ (uint16_t)sizeof(IPC_STRUCT_V2_Type),
    /* ipcLockStatusOffset       */ offsetof(IPC_STRUCT_V2_Type, LOCK_STATUS),
};


/******************************************************************************
* Function Name: Cy_PDL_Init
****************************************************************************//**
*
* \brief Initializes the platform and peripheral block configuration for the
* given target device.
*
* \param device
* Pointer to the platform and peripheral block configuration
*
* \note
* This function must be called prior calling any function in PDL.
*
*******************************************************************************/
void Cy_PDL_Init(const cy_stc_device_t * device)
{
    cy_device = device;
}


/* [] END OF FILE */
