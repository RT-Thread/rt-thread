/***************************************************************************//**
* \file cy_device.c
* \version 1.0
*
* This file provides the definitions for core and peripheral block HW base
* addresses, versions, and parameters.
*
********************************************************************************
* \copyright
* Copyright 2018, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
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

    /* IP block versions */
    /* cpussVersion              */ 1U,
    /* cryptoVersion             */ 1U,
    /* dwVersion                 */ 1U,
    /* flashcVersion             */ 1U,
    /* gpioVersion               */ 1U,
    /* hsiomVersion              */ 1U,
    /* ipcVersion                */ 1U,
    /* periVersion               */ 1U,
    /* protVersion               */ 1U,

    /* Parameters  */
    /* cpussIpcNr                */ 16U,
    /* cpussIpcIrqNr             */ 16U,
    /* cpussDwChNr               */ 16U,
    /* cpussFlashPaSize          */ 128U,
    /* cpussIpc0Irq              */ 25,
    /* cpussFmIrq                */ 85,
    /* cpussNotConnectedIrq      */ 240,
    /* srssNumClkpath            */ 5U,
    /* srssNumPll                */ 1U,
    /* srssNumHfroot             */ 5U,
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

    /* Peripheral register offsets */

    /* DW registers */
    /* dwChOffset                */ offsetof(DW_V1_Type, CH_STRUCT),
    /* dwChSize                  */ sizeof(DW_CH_STRUCT_V1_Type),
    /* dwChCtlPrioPos            */ (uint8_t)DW_CH_STRUCT_CH_CTL_PRIO_Pos,
    /* dwChCtlPreemptablePos     */ (uint8_t)DW_CH_STRUCT_CH_CTL_PREEMPTABLE_Pos,
    /* dwStatusChIdxPos          */ (uint8_t)DW_STATUS_CH_IDX_Pos,
    /* dwStatusChIdxMsk          */ DW_STATUS_CH_IDX_Msk,

    /* PERI registers */
    /* periTrCmdOffset           */ offsetof(PERI_V1_Type, TR_CMD),
    /* periTrCmdGrSelMsk         */ PERI_TR_CMD_GROUP_SEL_Msk,
    /* periTrGrOffset            */ offsetof(PERI_V1_Type, TR_GR),
    /* periTrGrSize              */ sizeof(PERI_TR_GR_V1_Type),

    /* periDivCmdDivSelMsk       */ PERI_DIV_CMD_DIV_SEL_Msk,
    /* periDivCmdTypeSelPos      */ PERI_DIV_CMD_TYPE_SEL_Pos,
    /* periDivCmdPaDivSelPos     */ PERI_DIV_CMD_PA_DIV_SEL_Pos,
    /* periDivCmdPaTypeSelPos    */ PERI_DIV_CMD_PA_TYPE_SEL_Pos,

    /* periDiv8CtlOffset         */ offsetof(PERI_V1_Type, DIV_8_CTL),
    /* periDiv16CtlOffset        */ offsetof(PERI_V1_Type, DIV_16_CTL),
    /* periDiv16_5CtlOffset      */ offsetof(PERI_V1_Type, DIV_16_5_CTL),
    /* periDiv24_5CtlOffset      */ offsetof(PERI_V1_Type, DIV_24_5_CTL),

    /* GPIO registers */
    /* gpioPrtIntrCfgOffset      */ offsetof(GPIO_PRT_V1_Type, INTR_CFG),
    /* gpioPrtCfgOffset          */ offsetof(GPIO_PRT_V1_Type, CFG),
    /* gpioPrtCfgInOffset        */ offsetof(GPIO_PRT_V1_Type, CFG_IN),
    /* gpioPrtCfgOutOffset       */ offsetof(GPIO_PRT_V1_Type, CFG_OUT),
    /* gpioPrtCfgSioOffset       */ offsetof(GPIO_PRT_V1_Type, CFG_SIO),

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

    /* IPC registers */
    /* ipcStructSize             */ sizeof(IPC_STRUCT_V1_Type),
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

    /* IP block versions */
    /* cpussVersion              */ 2U,
    /* cryptoVersion             */ 2U,
    /* dwVersion                 */ 2U,
    /* flashcVersion             */ 2U,
    /* gpioVersion               */ 2U,
    /* hsiomVersion              */ 2U,
    /* ipcVersion                */ 2U,
    /* periVersion               */ 2U,
    /* protVersion               */ 2U,

    /* Parameters */
    /* cpussIpcNr                */ 16U,
    /* cpussIpcIrqNr             */ 16U,
    /* cpussDwChNr               */ 29U,
    /* cpussFlashPaSize          */ 128U,
    /* cpussIpc0Irq              */ 23,
    /* cpussFmIrq                */ 117,
    /* cpussNotConnectedIrq      */ 1023,
    /* srssNumClkpath            */ 6U,
    /* srssNumPll                */ 2U,
    /* srssNumHfroot             */ 6U,
    /* periClockNr               */ 54U,
    /* smifDeviceNr              */ 4,
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

    /* Peripheral register offsets */

    /* DW registers */
    /* dwChOffset                */ offsetof(DW_V2_Type, CH_STRUCT),
    /* dwChSize                  */ sizeof(DW_CH_STRUCT_V2_Type),
    /* dwChCtlPrioPos            */ (uint8_t)DW_CH_STRUCT_V2_CH_CTL_PRIO_Pos,
    /* dwChCtlPreemptablePos     */ (uint8_t)DW_CH_STRUCT_V2_CH_CTL_PREEMPTABLE_Pos,
    /* dwStatusChIdxPos          */ (uint8_t)DW_V2_STATUS_CH_IDX_Pos,
    /* dwStatusChIdxMsk          */ DW_V2_STATUS_CH_IDX_Msk,

    /* PERI registers  */
    /* periTrCmdOffset           */ offsetof(PERI_V2_Type, TR_CMD),
    /* periTrCmdGrSelMsk         */ PERI_V2_TR_CMD_GROUP_SEL_Msk,
    /* periTrGrOffset            */ offsetof(PERI_V2_Type, TR_GR),
    /* periTrGrSize              */ sizeof(PERI_TR_GR_V2_Type),

    /* periDivCmdDivSelMsk       */ (uint8_t)PERI_V2_DIV_CMD_DIV_SEL_Msk,
    /* periDivCmdTypeSelPos      */ (uint8_t)PERI_V2_DIV_CMD_TYPE_SEL_Pos,
    /* periDivCmdPaDivSelPos     */ (uint8_t)PERI_V2_DIV_CMD_PA_DIV_SEL_Pos,
    /* periDivCmdPaTypeSelPos    */ (uint8_t)PERI_V2_DIV_CMD_PA_TYPE_SEL_Pos,

    /* periDiv8CtlOffset         */ offsetof(PERI_V2_Type, DIV_8_CTL),
    /* periDiv16CtlOffset        */ offsetof(PERI_V2_Type, DIV_16_CTL),
    /* periDiv16_5CtlOffset      */ offsetof(PERI_V2_Type, DIV_16_5_CTL),
    /* periDiv24_5CtlOffset      */ offsetof(PERI_V2_Type, DIV_24_5_CTL),

    /* GPIO registers  */
    /* gpioPrtIntrCfgOffset      */ offsetof(GPIO_PRT_V2_Type, INTR_CFG),
    /* gpioPrtCfgOffset          */ offsetof(GPIO_PRT_V2_Type, CFG),
    /* gpioPrtCfgInOffset        */ offsetof(GPIO_PRT_V2_Type, CFG_IN),
    /* gpioPrtCfgOutOffset       */ offsetof(GPIO_PRT_V2_Type, CFG_OUT),
    /* gpioPrtCfgSioOffset       */ offsetof(GPIO_PRT_V2_Type, CFG_SIO),

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

    /* IPC registers */
    /* ipcStructSize             */ sizeof(IPC_STRUCT_V2_Type),
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
