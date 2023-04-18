/***************************************************************************//**
* \file cy_device.h
* \version 2.30
*
* This file specifies the structure for core and peripheral block HW base
* addresses, versions, and parameters.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation
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

#ifndef CY_DEVICE_H_
#define CY_DEVICE_H_

#include <stdint.h>
#include <stddef.h>

#include "ip/cyip_cpuss.h"
#include "ip/cyip_cpuss_v2.h"
#include "ip/cyip_flashc.h"
#include "ip/cyip_flashc_v2.h"
#include "ip/cyip_gpio.h"
#include "ip/cyip_gpio_v2.h"
#include "ip/cyip_hsiom.h"
#include "ip/cyip_hsiom_v2.h"
#include "ip/cyip_sflash.h"
#include "ip/cyip_srss.h"
#include "ip/cyip_backup.h"
#include "ip/cyip_peri.h"
#include "ip/cyip_peri_v2.h"
#include "ip/cyip_peri_ms_v2.h"
#include "ip/cyip_profile.h"
#include "ip/cyip_prot.h"
#include "ip/cyip_prot_v2.h"
#include "ip/cyip_ipc.h"
#include "ip/cyip_ipc_v2.h"
#include "ip/cyip_udb.h"
#include "ip/cyip_dw.h"
#include "ip/cyip_dw_v2.h"
#include "ip/cyip_dmac_v2.h"
#include "ip/cyip_i2s.h"
#include "ip/cyip_pdm.h"
#include "ip/cyip_lcd.h"
#include "ip/cyip_lcd_v2.h"
#include "ip/cyip_sdhc.h"
#include "ip/cyip_canfd.h"
#include "ip/cyip_smartio.h"
#include "ip/cyip_tcpwm.h"
#include "ip/cyip_tcpwm_v2.h"
#include "ip/cyip_ctbm.h"
#include "ip/cyip_ctbm_v2.h"
#include "ip/cyip_ctdac.h"
#include "ip/cyip_ctdac_v2.h"
#include "ip/cyip_sar.h"
#include "ip/cyip_sar_v2.h"
#include "ip/cyip_pass.h"
#include "ip/cyip_pass_v2.h"
#include "cy_device_headers.h"

/* Device descriptor type */
typedef struct
{
    /* Base HW addresses */
    uint32_t cpussBase;
    uint32_t flashcBase;
    uint32_t periBase;
    uint32_t udbBase;
    uint32_t protBase;
    uint32_t hsiomBase;
    uint32_t gpioBase;
    uint32_t passBase;
    uint32_t ipcBase;
    uint32_t cryptoBase;
    uint32_t sar0Base;

    /* IP block versions: [7:4] major, [3:0] minor */
    uint8_t  cpussVersion;
    uint8_t  cryptoVersion;
    uint8_t  dwVersion;
    uint8_t  ipcVersion;
    uint8_t  periVersion;
    uint8_t  srssVersion;
    uint8_t  passVersion;

    /* Parameters */
    uint8_t  cpussIpcNr;
    uint8_t  cpussIpcIrqNr;
    uint8_t  cpussDw0ChNr;
    uint8_t  cpussDw1ChNr;
    uint8_t  cpussFlashPaSize;
    int16_t  cpussIpc0Irq;
    int16_t  cpussFmIrq;
    int16_t  cpussNotConnectedIrq;
    uint8_t  srssNumClkpath;
    uint8_t  srssNumPll;
    uint8_t  srssNumHfroot;
    uint8_t  srssIsPiloPresent;
    uint8_t  periClockNr;
    uint8_t  smifDeviceNr;
    uint8_t  passSarChannels;
    uint8_t  epMonitorNr;
    uint8_t  udbPresent;
    uint8_t  sysPmSimoPresent;
    uint32_t protBusMasterMask;
    uint32_t cryptoMemSize;
    uint8_t  flashRwwRequired;
    uint8_t  flashPipeRequired;
    uint8_t  flashWriteDelay;
    uint8_t  flashProgramDelay;
    uint8_t  flashEraseDelay;
    uint8_t  flashCtlMainWs0Freq;
    uint8_t  flashCtlMainWs1Freq;
    uint8_t  flashCtlMainWs2Freq;
    uint8_t  flashCtlMainWs3Freq;
    uint8_t  flashCtlMainWs4Freq;
    uint8_t  tcpwmCC1Present;
    uint8_t  tcpwmAMCPresent;
    uint8_t  tcpwmSMCPrecent;

    /* Peripheral register offsets */

    /* DW registers */
    uint16_t dwChOffset;
    uint16_t dwChSize;
    uint8_t  dwChCtlPrioPos;
    uint8_t  dwChCtlPreemptablePos;
    uint8_t  dwStatusChIdxPos;
    uint32_t dwStatusChIdxMsk;

    /* PERI registers */
    uint16_t periTrCmdOffset;
    uint16_t periTrCmdGrSelMsk;
    uint16_t periTrGrOffset;
    uint16_t periTrGrSize;

    uint8_t  periDivCmdDivSelMsk;
    uint8_t  periDivCmdTypeSelPos;
    uint8_t  periDivCmdPaDivSelPos;
    uint8_t  periDivCmdPaTypeSelPos;

    uint16_t periDiv8CtlOffset;
    uint16_t periDiv16CtlOffset;
    uint16_t periDiv16_5CtlOffset;
    uint16_t periDiv24_5CtlOffset;

    /* GPIO registers */
    uint8_t  gpioPrtIntrCfgOffset;
    uint8_t  gpioPrtCfgOffset;
    uint8_t  gpioPrtCfgInOffset;
    uint8_t  gpioPrtCfgOutOffset;
    uint8_t  gpioPrtCfgSioOffset;

    /* CPUSS registers */
    uint32_t cpussCm0ClockCtlOffset;
    uint32_t cpussCm4ClockCtlOffset;
    uint32_t cpussCm4StatusOffset;
    uint32_t cpussCm0StatusOffset;
    uint32_t cpussCm4PwrCtlOffset;
    uint32_t cpussTrimRamCtlOffset;
    uint32_t cpussTrimRomCtlOffset;
    uint32_t cpussSysTickCtlOffset;
    uint16_t cpussCm0NmiCtlOffset;
    uint16_t cpussCm4NmiCtlOffset;
    uint16_t cpussRomCtl;
    uint16_t cpussRam0Ctl0;
    uint16_t cpussRam1Ctl0;
    uint16_t cpussRam2Ctl0;
    uint16_t cpussRam0PwrCtl;
    uint16_t cpussRam1PwrCtl;
    uint16_t cpussRam2PwrCtl;

    /* IPC registers */
    uint16_t ipcStructSize;
    uint32_t ipcLockStatusOffset;
} cy_stc_device_t;

/*******************************************************************************
*                   Global Variables
*******************************************************************************/

extern const cy_stc_device_t   cy_deviceIpBlockCfgPSoC6_01;
extern const cy_stc_device_t   cy_deviceIpBlockCfgPSoC6_02;
extern const cy_stc_device_t   cy_deviceIpBlockCfgPSoC6_03;
extern const cy_stc_device_t   cy_deviceIpBlockCfgPSoC6_04;
extern const cy_stc_device_t * cy_device;


/*******************************************************************************
*                   Function Prototypes
*******************************************************************************/

void Cy_PDL_Init(const cy_stc_device_t * device);


/*******************************************************************************
*               Register Access Helper Macros
*******************************************************************************/
#define CY_DEVICE_CAT1A            /* Device Category */
#define CY_CRYPTO_V1                        (0x20U > cy_device->cryptoVersion) /* true if the mxcrypto version is 1.x */

#define CY_SRSS_V1_3                        (0x13U == cy_device->srssVersion)
#define CY_SRSS_MFO_PRESENT                 (CY_SRSS_V1_3)

#define CY_SRSS_PILO_PRESENT                 (1U == cy_device->srssIsPiloPresent)

#define CY_SRSS_NUM_CLKPATH                 ((uint32_t)(cy_device->srssNumClkpath))
#define CY_SRSS_NUM_PLL                     ((uint32_t)(cy_device->srssNumPll))
#define CY_SRSS_NUM_HFROOT                  ((uint32_t)(cy_device->srssNumHfroot))
#define CY_SRSS_PLL400M_PRESENT             0

#define SRSS_PWR_CTL                        (((SRSS_V1_Type *) SRSS)->PWR_CTL)
#define SRSS_PWR_HIBERNATE                  (((SRSS_V1_Type *) SRSS)->PWR_HIBERNATE)
#define SRSS_PWR_TRIM_PWRSYS_CTL            (((SRSS_V1_Type *) SRSS)->PWR_TRIM_PWRSYS_CTL)
#define SRSS_PWR_BUCK_CTL                   (((SRSS_V1_Type *) SRSS)->PWR_BUCK_CTL)
#define SRSS_PWR_BUCK_CTL2                  (((SRSS_V1_Type *) SRSS)->PWR_BUCK_CTL2)
#define SRSS_PWR_TRIM_WAKE_CTL              (((SRSS_V1_Type *) SRSS)->PWR_TRIM_WAKE_CTL)
#define SRSS_PWR_LVD_CTL                    (((SRSS_V1_Type *) SRSS)->PWR_LVD_CTL)
#define SRSS_PWR_LVD_STATUS                 (((SRSS_V1_Type *) SRSS)->PWR_LVD_STATUS)
#define SRSS_WDT_CTL                        (((SRSS_V1_Type *) SRSS)->WDT_CTL)
#define SRSS_WDT_CNT                        (((SRSS_V1_Type *) SRSS)->WDT_CNT)
#define SRSS_WDT_MATCH                      (((SRSS_V1_Type *) SRSS)->WDT_MATCH)
#define SRSS_CLK_DSI_SELECT                 (((SRSS_V1_Type *) SRSS)->CLK_DSI_SELECT)
#define SRSS_CLK_PATH_SELECT                (((SRSS_V1_Type *) SRSS)->CLK_PATH_SELECT)
#define SRSS_CLK_ROOT_SELECT                (((SRSS_V1_Type *) SRSS)->CLK_ROOT_SELECT)
#define SRSS_CLK_CSV_HF_LIMIT(clk)          (((SRSS_V1_Type *) SRSS)->CLK_CSV[(clk)].HF_LIMIT)
#define SRSS_CLK_CSV_HF_CTL(clk)            (((SRSS_V1_Type *) SRSS)->CLK_CSV[(clk)].HF_CTL)
#define SRSS_CLK_SELECT                     (((SRSS_V1_Type *) SRSS)->CLK_SELECT)
#define SRSS_CLK_TIMER_CTL                  (((SRSS_V1_Type *) SRSS)->CLK_TIMER_CTL)
#define SRSS_CLK_CSV_WCO_CTL                (((SRSS_V1_Type *) SRSS)->CLK_CSV_WCO_CTL)
#define SRSS_CLK_ILO_CONFIG                 (((SRSS_V1_Type *) SRSS)->CLK_ILO_CONFIG)
#define SRSS_CLK_OUTPUT_SLOW                (((SRSS_V1_Type *) SRSS)->CLK_OUTPUT_SLOW)
#define SRSS_CLK_OUTPUT_FAST                (((SRSS_V1_Type *) SRSS)->CLK_OUTPUT_FAST)
#define SRSS_CLK_CAL_CNT1                   (((SRSS_V1_Type *) SRSS)->CLK_CAL_CNT1)
#define SRSS_CLK_CAL_CNT2                   (((SRSS_V1_Type *) SRSS)->CLK_CAL_CNT2)
#define SRSS_CLK_ECO_CONFIG                 (((SRSS_V1_Type *) SRSS)->CLK_ECO_CONFIG)
#define SRSS_CLK_ECO_STATUS                 (((SRSS_V1_Type *) SRSS)->CLK_ECO_STATUS)
#define SRSS_CLK_PILO_CONFIG                (((SRSS_V1_Type *) SRSS)->CLK_PILO_CONFIG)
#define SRSS_CLK_MF_SELECT                  (((SRSS_V1_Type *) SRSS)->CLK_MF_SELECT)  /* for CY_SRSS_V1_3 only */
#define SRSS_CLK_MFO_CONFIG                 (((SRSS_V1_Type *) SRSS)->CLK_MFO_CONFIG) /* for CY_SRSS_V1_3 only */
#define SRSS_CLK_FLL_CONFIG                 (((SRSS_V1_Type *) SRSS)->CLK_FLL_CONFIG)
#define SRSS_CLK_FLL_CONFIG2                (((SRSS_V1_Type *) SRSS)->CLK_FLL_CONFIG2)
#define SRSS_CLK_FLL_CONFIG3                (((SRSS_V1_Type *) SRSS)->CLK_FLL_CONFIG3)
#define SRSS_CLK_FLL_CONFIG4                (((SRSS_V1_Type *) SRSS)->CLK_FLL_CONFIG4)
#define SRSS_CLK_FLL_STATUS                 (((SRSS_V1_Type *) SRSS)->CLK_FLL_STATUS)
#define SRSS_CLK_PLL_CONFIG                 (((SRSS_V1_Type *) SRSS)->CLK_PLL_CONFIG)
#define SRSS_CLK_PLL_STATUS                 (((SRSS_V1_Type *) SRSS)->CLK_PLL_STATUS)
#define SRSS_SRSS_INTR                      (((SRSS_V1_Type *) SRSS)->SRSS_INTR)
#define SRSS_SRSS_INTR_SET                  (((SRSS_V1_Type *) SRSS)->SRSS_INTR_SET)
#define SRSS_SRSS_INTR_CFG                  (((SRSS_V1_Type *) SRSS)->SRSS_INTR_CFG)
#define SRSS_SRSS_INTR_MASK                 (((SRSS_V1_Type *) SRSS)->SRSS_INTR_MASK)
#define SRSS_SRSS_INTR_MASKED               (((SRSS_V1_Type *) SRSS)->SRSS_INTR_MASKED)
#define SRSS_CLK_TRIM_ILO_CTL               (((SRSS_V1_Type *) SRSS)->CLK_TRIM_ILO_CTL)
#define SRSS_CLK_TRIM_ECO_CTL               (((SRSS_V1_Type *) SRSS)->CLK_TRIM_ECO_CTL)

#define SRSS_RES_CAUSE                      (((SRSS_V1_Type *) SRSS)->RES_CAUSE)
#define SRSS_RES_CAUSE2                     (((SRSS_V1_Type *) SRSS)->RES_CAUSE2)

#define SRSS_TST_DDFT_SLOW_CTL_REG          (*(volatile uint32_t *) 0x40260108U)
#define SRSS_TST_DDFT_FAST_CTL_REG          (*(volatile uint32_t *) 0x40260104U)

#define SRSS_TST_DDFT_SLOW_CTL_MASK         (0x00001F1EU)
#define SRSS_TST_DDFT_FAST_CTL_MASK         (62U)

/*******************************************************************************
*                CRYPTO
*******************************************************************************/

/* The CRYPTO internal-memory buffer-size in 32-bit words. */
#define CY_CRYPTO_MEM_BUFF_SIZE_U32         (1024U)

/*******************************************************************************
*                BACKUP
*******************************************************************************/

#define BACKUP_PMIC_CTL                     (((BACKUP_V1_Type *) BACKUP)->PMIC_CTL)
#define BACKUP_CTL                          (((BACKUP_V1_Type *) BACKUP)->CTL)
#define BACKUP_RTC_TIME                     (((BACKUP_V1_Type *) BACKUP)->RTC_TIME)
#define BACKUP_RTC_DATE                     (((BACKUP_V1_Type *) BACKUP)->RTC_DATE)
#define BACKUP_RTC_RW                       (((BACKUP_V1_Type *) BACKUP)->RTC_RW)
#define BACKUP_CAL_CTL                      (((BACKUP_V1_Type *) BACKUP)->CAL_CTL)
#define BACKUP_ALM1_TIME                    (((BACKUP_V1_Type *) BACKUP)->ALM1_TIME)
#define BACKUP_ALM1_DATE                    (((BACKUP_V1_Type *) BACKUP)->ALM1_DATE)
#define BACKUP_ALM2_TIME                    (((BACKUP_V1_Type *) BACKUP)->ALM2_TIME)
#define BACKUP_ALM2_DATE                    (((BACKUP_V1_Type *) BACKUP)->ALM2_DATE)
#define BACKUP_STATUS                       (((BACKUP_V1_Type *) BACKUP)->STATUS)
#define BACKUP_INTR                         (((BACKUP_V1_Type *) BACKUP)->INTR)
#define BACKUP_INTR_SET                     (((BACKUP_V1_Type *) BACKUP)->INTR_SET)
#define BACKUP_INTR_MASK                    (((BACKUP_V1_Type *) BACKUP)->INTR_MASK)
#define BACKUP_INTR_MASKED                  (((BACKUP_V1_Type *) BACKUP)->INTR_MASKED)
#define BACKUP_RESET                        (((BACKUP_V1_Type *) BACKUP)->RESET)
#define BACKUP_TRIM                         (((BACKUP_V1_Type *) BACKUP)->TRIM)

/*******************************************************************************
*                CANFD
*******************************************************************************/

#define CANFD_CTL(base)                     (((CANFD_V1_Type *)(base))->CTL)
#define CANFD_STATUS(base)                  (((CANFD_V1_Type *)(base))->STATUS)
#define CANFD_NBTP(base, chan)                    (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.NBTP)
#define CANFD_IR(base, chan)                      (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.IR)
#define CANFD_IE(base, chan)                      (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.IE)
#define CANFD_ILS(base, chan)                     (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.ILS)
#define CANFD_ILE(base, chan)                     (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.ILE)
#define CANFD_CCCR(base, chan)                    (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.CCCR)
#define CANFD_SIDFC(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.SIDFC)
#define CANFD_XIDFC(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.XIDFC)
#define CANFD_XIDAM(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.XIDAM)
#define CANFD_RXESC(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.RXESC)
#define CANFD_RXF0C(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.RXF0C)
#define CANFD_RXF1C(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.RXF1C)
#define CANFD_RXFTOP_CTL(base, chan)              (((CANFD_V1_Type *)(base))->CH[chan].RXFTOP_CTL)
#define CANFD_RXBC(base, chan)                    (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.RXBC)
#define CANFD_TXESC(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.TXESC)
#define CANFD_TXEFC(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.TXEFC)
#define CANFD_TXBC(base, chan)                    (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.TXBC)
#define CANFD_DBTP(base, chan)                    (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.DBTP)
#define CANFD_TDCR(base, chan)                    (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.TDCR)
#define CANFD_GFC(base, chan)                     (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.GFC)
#define CANFD_TXBRP(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.TXBRP)
#define CANFD_TXBAR(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.TXBAR)
#define CANFD_TXBCR(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.TXBCR)
#define CANFD_TXBTO(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.TXBTO)
#define CANFD_TXBCF(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.TXBCF)
#define CANFD_TXBTIE(base, chan)                  (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.TXBTIE)
#define CANFD_TXBCIE(base, chan)                  (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.TXBCIE)
#define CANFD_NDAT1(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.NDAT1)
#define CANFD_NDAT2(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.NDAT2)
#define CANFD_RXF0S(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.RXF0S)
#define CANFD_RXFTOP0_DATA(base, chan)            (((CANFD_V1_Type *)(base))->CH[chan].RXFTOP0_DATA)
#define CANFD_RXFTOP1_DATA(base, chan)            (((CANFD_V1_Type *)(base))->CH[chan].RXFTOP1_DATA)
#define CANFD_RXF0A(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.RXF0A)
#define CANFD_RXF1S(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.RXF1S)
#define CANFD_RXF1A(base, chan)                   (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.RXF1A)
#define CANFD_PSR(base, chan)                     (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.PSR)
#define CANFD_TEST(base, chan)                    (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.TEST)
#define CANFD_CREL(base, chan)                    (((CANFD_V1_Type *)(base))->CH[chan].M_TTCAN.CREL)

#define CY_CANFD_CHANNELS_NUM               (0x1UL)


/*******************************************************************************
*                FLASHC
*******************************************************************************/

#define FLASHC_FM_CTL_ANA_CTL0              (((FLASHC_V1_Type *) cy_device->flashcBase)->FM_CTL.ANA_CTL0)
#define FLASHC_FM_CTL_BOOKMARK              (((FLASHC_V1_Type *) cy_device->flashcBase)->FM_CTL.BOOKMARK)
#define FLASHC_FLASH_CMD                    (((FLASHC_V1_Type *) cy_device->flashcBase)->FLASH_CMD)
#define FLASHC_FLASH_CTL                    (((FLASHC_V1_Type *) cy_device->flashcBase)->FLASH_CTL)
#define FLASHC_BIST_DATA_0                  (((FLASHC_V1_Type *) cy_device->flashcBase)->BIST_DATA[0U])
#define FLASHC_BIST_STATUS                  (((FLASHC_V1_Type *) cy_device->flashcBase)->BIST_STATUS)


/*******************************************************************************
*                SFLASH
*******************************************************************************/

#define SFLASH_DIE_YEAR                     (((SFLASH_V1_Type *) SFLASH)->DIE_YEAR)
#define SFLASH_DIE_MINOR                    (((SFLASH_V1_Type *) SFLASH)->DIE_MINOR)
#define SFLASH_DIE_SORT                     (((SFLASH_V1_Type *) SFLASH)->DIE_SORT)
#define SFLASH_DIE_Y                        (((SFLASH_V1_Type *) SFLASH)->DIE_Y)
#define SFLASH_DIE_X                        (((SFLASH_V1_Type *) SFLASH)->DIE_X)
#define SFLASH_DIE_WAFER                    (((SFLASH_V1_Type *) SFLASH)->DIE_WAFER)
#define SFLASH_DIE_LOT(val)                 (((SFLASH_V1_Type *) SFLASH)->DIE_LOT[(val)])
#define SFLASH_FAMILY_ID                    (((SFLASH_V1_Type *) SFLASH)->FAMILY_ID)
#define SFLASH_SI_REVISION_ID               (((SFLASH_V1_Type *) SFLASH)->SI_REVISION_ID)
#define SFLASH_PWR_TRIM_WAKE_CTL            (((SFLASH_V1_Type *) SFLASH)->PWR_TRIM_WAKE_CTL)
#define SFLASH_LDO_0P9V_TRIM                (((SFLASH_V1_Type *) SFLASH)->LDO_0P9V_TRIM)
#define SFLASH_LDO_1P1V_TRIM                (((SFLASH_V1_Type *) SFLASH)->LDO_1P1V_TRIM)
#define SFLASH_BLE_DEVICE_ADDRESS           (((SFLASH_V1_Type *) SFLASH)->BLE_DEVICE_ADDRESS)
#define SFLASH_SILICON_ID                   (((SFLASH_V1_Type *) SFLASH)->SILICON_ID)
#define SFLASH_SINGLE_CORE                  (*(volatile uint8_t *) (SFLASH_BASE + 0xBU))


#define SFLASH_CPUSS_TRIM_ROM_CTL_LP        (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_ROM_CTL_LP)
#define SFLASH_CPUSS_TRIM_RAM_CTL_LP        (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_RAM_CTL_LP)
#define SFLASH_CPUSS_TRIM_ROM_CTL_ULP       (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_ROM_CTL_ULP)
#define SFLASH_CPUSS_TRIM_RAM_CTL_ULP       (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_RAM_CTL_ULP)
#define SFLASH_CPUSS_TRIM_ROM_CTL_HALF_LP   (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_ROM_CTL_HALF_LP)
#define SFLASH_CPUSS_TRIM_RAM_CTL_HALF_LP   (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_RAM_CTL_HALF_LP)
#define SFLASH_CPUSS_TRIM_ROM_CTL_HALF_ULP  (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_ROM_CTL_HALF_ULP)
#define SFLASH_CPUSS_TRIM_RAM_CTL_HALF_ULP  (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_RAM_CTL_HALF_ULP)


#define SFLASH_CSD0_ADC_VREF0_TRIM          (((SFLASH_V1_Type *) SFLASH)->CSDV2_CSD0_ADC_VREF0)
#define SFLASH_CSD0_ADC_VREF1_TRIM          (((SFLASH_V1_Type *) SFLASH)->CSDV2_CSD0_ADC_VREF1)
#define SFLASH_CSD0_ADC_VREF2_TRIM          (((SFLASH_V1_Type *) SFLASH)->CSDV2_CSD0_ADC_VREF2)


/*******************************************************************************
*                CPUSS
*******************************************************************************/

#define CY_CPUSS_V1                         (0x20U > cy_device->cpussVersion)

#define CY_CPUSS_NOT_CONNECTED_IRQN         ((uint32_t)(cy_device->cpussNotConnectedIrq))
#define CY_CPUSS_DISCONNECTED_IRQN          ((cy_en_intr_t)CY_CPUSS_NOT_CONNECTED_IRQN)
#define CY_CPUSS_UNCONNECTED_IRQN           ((IRQn_Type)CY_CPUSS_NOT_CONNECTED_IRQN)

#define CPUSS_CM0_CLOCK_CTL                 (*(volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussCm0ClockCtlOffset))
#define CPUSS_CM4_CLOCK_CTL                 (*(volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussCm4ClockCtlOffset))
#define CPUSS_CM4_STATUS                    (*(volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussCm4StatusOffset))
#define CPUSS_CM0_STATUS                    (*(volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussCm0StatusOffset))
#define CPUSS_CM4_PWR_CTL                   (*(volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussCm4PwrCtlOffset))
#define CPUSS_TRIM_RAM_CTL                  (*(volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussTrimRamCtlOffset))
#define CPUSS_TRIM_ROM_CTL                  (*(volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussTrimRomCtlOffset))
#define CPUSS_SYSTICK_CTL                   (*(volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussSysTickCtlOffset))

#define CPUSS_ROM_CTL                       (*(volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussRomCtl))
#define CPUSS_RAM0_CTL0                     (*(volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussRam0Ctl0))
#define CPUSS_RAM1_CTL0                     (*(volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussRam1Ctl0))
#define CPUSS_RAM2_CTL0                     (*(volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussRam2Ctl0))
#define CPUSS_RAM0_PWR_CTL(macroIdx)        (((volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussRam0PwrCtl))[(macroIdx)])
#define CPUSS_RAM1_PWR_CTL                  (*(volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussRam1PwrCtl))
#define CPUSS_RAM2_PWR_CTL                  (*(volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussRam2PwrCtl))

#define CPUSS_CM0_NMI_CTL(nmi)              (((volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussCm0NmiCtlOffset))[(nmi)])
#define CPUSS_CM4_NMI_CTL(nmi)              (((volatile uint32_t *) (cy_device->cpussBase + cy_device->cpussCm4NmiCtlOffset))[(nmi)])

/* used in V1 code only */
#define CPUSS_CM0_INT_CTL                   ((volatile uint32_t *) &(((CPUSS_V1_Type *)(cy_device->cpussBase))->CM0_INT_CTL0))

/* used in V2 code only */
#define CPUSS_CM0_SYSTEM_INT_CTL            (((CPUSS_V2_Type *)(cy_device->cpussBase))->CM0_SYSTEM_INT_CTL)
#define CPUSS_CM0_INT_STATUS                ((volatile const uint32_t *) &(((CPUSS_V2_Type *)(cy_device->cpussBase))->CM0_INT0_STATUS))

#define CPUSS_SRAM_COUNT                    (1u + CPUSS_RAMC1_PRESENT + CPUSS_RAMC2_PRESENT)

/* ARM core registers */
#define SYSTICK_CTRL                        (((SysTick_Type *)SysTick)->CTRL)
#define SYSTICK_LOAD                        (((SysTick_Type *)SysTick)->LOAD)
#define SYSTICK_VAL                         (((SysTick_Type *)SysTick)->VAL)
#define SCB_SCR                             (((SCB_Type *)SCB)->SCR)

#define UDB_UDBIF_BANK_CTL                  (((UDB_V1_Type *) cy_device->udbBase)->UDBIF.BANK_CTL)
#define UDB_BCTL_MDCLK_EN                   (((UDB_V1_Type *) cy_device->udbBase)->BCTL.MDCLK_EN)
#define UDB_BCTL_MBCLK_EN                   (((UDB_V1_Type *) cy_device->udbBase)->BCTL.MBCLK_EN)
#define UDB_BCTL_BOTSEL_L                   (((UDB_V1_Type *) cy_device->udbBase)->BCTL.BOTSEL_L)
#define UDB_BCTL_BOTSEL_U                   (((UDB_V1_Type *) cy_device->udbBase)->BCTL.BOTSEL_U)
#define UDB_BCTL_QCLK_EN_0                  (((UDB_V1_Type *) cy_device->udbBase)->BCTL.QCLK_EN[0U])
#define UDB_BCTL_QCLK_EN_1                  (((UDB_V1_Type *) cy_device->udbBase)->BCTL.QCLK_EN[1U])
#define UDB_BCTL_QCLK_EN_2                  (((UDB_V1_Type *) cy_device->udbBase)->BCTL.QCLK_EN[2U])


/*******************************************************************************
*                LPCOMP
*******************************************************************************/

#define LPCOMP_CMP0_CTRL(base)              (((LPCOMP_V1_Type *)(base))->CMP0_CTRL)
#define LPCOMP_CMP1_CTRL(base)              (((LPCOMP_V1_Type *)(base))->CMP1_CTRL)
#define LPCOMP_CMP0_SW_CLEAR(base)          (((LPCOMP_V1_Type *)(base))->CMP0_SW_CLEAR)
#define LPCOMP_CMP1_SW_CLEAR(base)          (((LPCOMP_V1_Type *)(base))->CMP1_SW_CLEAR)
#define LPCOMP_CMP0_SW(base)                (((LPCOMP_V1_Type *)(base))->CMP0_SW)
#define LPCOMP_CMP1_SW(base)                (((LPCOMP_V1_Type *)(base))->CMP1_SW)
#define LPCOMP_STATUS(base)                 (((LPCOMP_V1_Type *)(base))->STATUS)
#define LPCOMP_CONFIG(base)                 (((LPCOMP_V1_Type *)(base))->CONFIG)
#define LPCOMP_INTR(base)                   (((LPCOMP_V1_Type *)(base))->INTR)
#define LPCOMP_INTR_SET(base)               (((LPCOMP_V1_Type *)(base))->INTR_SET)
#define LPCOMP_INTR_MASK(base)              (((LPCOMP_V1_Type *)(base))->INTR_MASK)
#define LPCOMP_INTR_MASKED(base)            (((LPCOMP_V1_Type *)(base))->INTR_MASKED)


/*******************************************************************************
*                MCWDT
*******************************************************************************/

#define MCWDT_CNTLOW(base)      (((MCWDT_STRUCT_V1_Type *)(base))->MCWDT_CNTLOW)
#define MCWDT_CNTHIGH(base)     (((MCWDT_STRUCT_V1_Type *)(base))->MCWDT_CNTHIGH)
#define MCWDT_MATCH(base)       (((MCWDT_STRUCT_V1_Type *)(base))->MCWDT_MATCH)
#define MCWDT_CONFIG(base)      (((MCWDT_STRUCT_V1_Type *)(base))->MCWDT_CONFIG)
#define MCWDT_LOCK(base)        (((MCWDT_STRUCT_V1_Type *)(base))->MCWDT_LOCK)
#define MCWDT_CTL(base)         (((MCWDT_STRUCT_V1_Type *)(base))->MCWDT_CTL)
#define MCWDT_INTR(base)        (((MCWDT_STRUCT_V1_Type *)(base))->MCWDT_INTR)
#define MCWDT_INTR_SET(base)    (((MCWDT_STRUCT_V1_Type *)(base))->MCWDT_INTR_SET)
#define MCWDT_INTR_MASK(base)   (((MCWDT_STRUCT_V1_Type *)(base))->MCWDT_INTR_MASK)
#define MCWDT_INTR_MASKED(base) (((MCWDT_STRUCT_V1_Type *)(base))->MCWDT_INTR_MASKED)


/*******************************************************************************
*                TCPWM
*******************************************************************************/

#define TCPWM_CTRL_SET(base)                (((TCPWM_V1_Type *)(base))->CTRL_SET)
#define TCPWM_CTRL_CLR(base)                (((TCPWM_V1_Type *)(base))->CTRL_CLR)
#define TCPWM_CMD_START(base)               (((TCPWM_V1_Type *)(base))->CMD_START)
#define TCPWM_CMD_RELOAD(base)              (((TCPWM_V1_Type *)(base))->CMD_RELOAD)
#define TCPWM_CMD_STOP(base)                (((TCPWM_V1_Type *)(base))->CMD_STOP)
#define TCPWM_CMD_CAPTURE(base)             (((TCPWM_V1_Type *)(base))->CMD_CAPTURE)

#define TCPWM_CNT_CTRL(base, cntNum)         (((TCPWM_V1_Type *)(base))->CNT[cntNum].CTRL)
#define TCPWM_CNT_CC(base, cntNum)           (((TCPWM_V1_Type *)(base))->CNT[cntNum].CC)
#define TCPWM_CNT_CC_BUFF(base, cntNum)      (((TCPWM_V1_Type *)(base))->CNT[cntNum].CC_BUFF)
#define TCPWM_CNT_COUNTER(base, cntNum)      (((TCPWM_V1_Type *)(base))->CNT[cntNum].COUNTER)
#define TCPWM_CNT_PERIOD(base, cntNum)       (((TCPWM_V1_Type *)(base))->CNT[cntNum].PERIOD)
#define TCPWM_CNT_PERIOD_BUFF(base, cntNum)  (((TCPWM_V1_Type *)(base))->CNT[cntNum].PERIOD_BUFF)
#define TCPWM_CNT_STATUS(base, cntNum)       (((TCPWM_V1_Type *)(base))->CNT[cntNum].STATUS)
#define TCPWM_CNT_INTR(base, cntNum)         (((TCPWM_V1_Type *)(base))->CNT[cntNum].INTR)
#define TCPWM_CNT_INTR_SET(base, cntNum)     (((TCPWM_V1_Type *)(base))->CNT[cntNum].INTR_SET)
#define TCPWM_CNT_INTR_MASK(base, cntNum)    (((TCPWM_V1_Type *)(base))->CNT[cntNum].INTR_MASK)
#define TCPWM_CNT_INTR_MASKED(base, cntNum)  (((TCPWM_V1_Type *)(base))->CNT[cntNum].INTR_MASKED)
#define TCPWM_CNT_TR_CTRL0(base, cntNum)     (((TCPWM_V1_Type *)(base))->CNT[cntNum].TR_CTRL0)
#define TCPWM_CNT_TR_CTRL1(base, cntNum)     (((TCPWM_V1_Type *)(base))->CNT[cntNum].TR_CTRL1)
#define TCPWM_CNT_TR_CTRL2(base, cntNum)     (((TCPWM_V1_Type *)(base))->CNT[cntNum].TR_CTRL2)

#define TCPWM_GRP_CC1(base, grp)                   ((((cy_device->tcpwmCC1Present) >> (grp)) & 0x01U) != 0U)
#define TCPWM_GRP_AMC(base, grp)                   ((((cy_device->tcpwmAMCPresent) >> (grp)) & 0x01U) != 0U)
#define TCPWM_GRP_SMC(base, grp)                   ((((cy_device->tcpwmSMCPrecent) >> (grp)) & 0x01U) != 0U)

#define TCPWM_GRP_CNT_GET_GRP(cntNum)        ((cntNum )/ 256U)

#define TCPWM_GRP_CNT_CTRL(base, grp, cntNum)           (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].CTRL)
#define TCPWM_GRP_CNT_STATUS(base, grp, cntNum)         (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].STATUS)
#define TCPWM_GRP_CNT_COUNTER(base, grp, cntNum)        (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].COUNTER)
#define TCPWM_GRP_CNT_CC0(base, grp, cntNum)            (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].CC0)
#define TCPWM_GRP_CNT_CC0_BUFF(base, grp, cntNum)       (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].CC0_BUFF)
#define TCPWM_GRP_CNT_CC1(base, grp, cntNum)            (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].CC1)
#define TCPWM_GRP_CNT_CC1_BUFF(base, grp, cntNum)       (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].CC1_BUFF)
#define TCPWM_GRP_CNT_PERIOD(base, grp, cntNum)         (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].PERIOD)
#define TCPWM_GRP_CNT_PERIOD_BUFF(base, grp, cntNum)    (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].PERIOD_BUFF)
#define TCPWM_GRP_CNT_LINE_SEL(base, grp, cntNum)       (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].LINE_SEL)
#define TCPWM_GRP_CNT_LINE_SEL_BUFF(base, grp, cntNum)  (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].LINE_SEL_BUFF)
#define TCPWM_GRP_CNT_DT(base, grp, cntNum)             (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].DT)
#define TCPWM_GRP_CNT_TR_CMD(base, grp, cntNum)         (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_CMD)
#define TCPWM_GRP_CNT_TR_IN_SEL0(base, grp, cntNum)     (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_IN_SEL0)
#define TCPWM_GRP_CNT_TR_IN_SEL1(base, grp, cntNum)     (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_IN_SEL1)
#define TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_IN_EDGE_SEL)
#define TCPWM_GRP_CNT_TR_PWM_CTRL(base, grp, cntNum)    (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_PWM_CTRL)
#define TCPWM_GRP_CNT_TR_OUT_SEL(base, grp, cntNum)     (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_OUT_SEL)
#define TCPWM_GRP_CNT_INTR(base, grp, cntNum)           (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].INTR)
#define TCPWM_GRP_CNT_INTR_SET(base, grp, cntNum)       (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].INTR_SET)
#define TCPWM_GRP_CNT_INTR_MASK(base, grp, cntNum)      (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].INTR_MASK)
#define TCPWM_GRP_CNT_INTR_MASKED(base, grp, cntNum)    (((TCPWM_V2_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].INTR_MASKED)


/*******************************************************************************
*                SAR
*******************************************************************************/

#define CY_SAR_INSTANCES                    (2UL)
#define CY_SAR0_BASE                        ((SAR_Type*)(cy_device->sar0Base))
#define CY_SAR_INSTANCE(base)               ((CY_SAR0_BASE == (base)) ? 0UL : 1UL)

#define SAR_SAMPLE_CTRL(base)               (((SAR_V1_Type *)(base))->SAMPLE_CTRL)
#define SAR_SAMPLE_TIME01(base)             (((SAR_V1_Type *)(base))->SAMPLE_TIME01)
#define SAR_SAMPLE_TIME23(base)             (((SAR_V1_Type *)(base))->SAMPLE_TIME23)

#define SAR_RANGE_THRES(base)               (((SAR_V1_Type *)(base))->RANGE_THRES)
#define SAR_RANGE_COND(base)                (((SAR_V1_Type *)(base))->RANGE_COND)
#define SAR_RANGE_INTR(base)                (((SAR_V1_Type *)(base))->RANGE_INTR)
#define SAR_RANGE_INTR_SET(base)            (((SAR_V1_Type *)(base))->RANGE_INTR_SET)

#define SAR_RANGE_INTR_MASK(base)           (((SAR_V1_Type *)(base))->RANGE_INTR_MASK)
#define SAR_RANGE_INTR_MASKED(base)         (((SAR_V1_Type *)(base))->RANGE_INTR_MASKED)

#define SAR_CHAN_EN(base)                   (((SAR_V1_Type *)(base))->CHAN_EN)
#define SAR_CHAN_CONFIG(base, chan)         (((SAR_V1_Type *)(base))->CHAN_CONFIG[(chan)])
#define SAR_CHAN_RESULT(base, chan )        (((SAR_V1_Type *)(base))->CHAN_RESULT[(chan)])
#define SAR_CHAN_RESULT_UPDATED(base)       (((SAR_V1_Type *)(base))->CHAN_RESULT_UPDATED)

#define SAR_INTR(base)                      (((SAR_V1_Type *)(base))->INTR)
#define SAR_INTR_MASK(base)                 (((SAR_V1_Type *)(base))->INTR_MASK)
#define SAR_INTR_MASKED(base)               (((SAR_V1_Type *)(base))->INTR_MASKED)
#define SAR_INTR_SET(base)                  (((SAR_V1_Type *)(base))->INTR_SET)
#define SAR_INTR_CAUSE(base)                (((SAR_V1_Type *)(base))->INTR_CAUSE)

#define SAR_MUX_SWITCH_CLEAR0(base)         (((SAR_V1_Type *)(base))->MUX_SWITCH_CLEAR0)
#define SAR_MUX_SWITCH0(base)               (((SAR_V1_Type *)(base))->MUX_SWITCH0)
#define SAR_MUX_SWITCH_SQ_CTRL(base)        (((SAR_V1_Type *)(base))->MUX_SWITCH_SQ_CTRL)
#define SAR_MUX_SWITCH_DS_CTRL(base)        (((SAR_V1_Type *)(base))->MUX_SWITCH_DS_CTRL)

#define SAR_ANA_TRIM0(base)                 (((SAR_V1_Type *)(base))->ANA_TRIM0)
#define SAR_CTRL(base)                      (((SAR_V1_Type *)(base))->CTRL)
#define SAR_STATUS(base)                    (((SAR_V1_Type *)(base))->STATUS)
#define SAR_START_CTRL(base)                (((SAR_V1_Type *)(base))->START_CTRL)

#define SAR_SATURATE_INTR(base)             (((SAR_V1_Type *)(base))->SATURATE_INTR)
#define SAR_SATURATE_INTR_MASK(base)        (((SAR_V1_Type *)(base))->SATURATE_INTR_MASK)
#define SAR_SATURATE_INTR_MASKED(base)      (((SAR_V1_Type *)(base))->SATURATE_INTR_MASKED)
#define SAR_SATURATE_INTR_SET(base)         (((SAR_V1_Type *)(base))->SATURATE_INTR_SET)

#define SAR_INJ_CHAN_CONFIG(base)           (((SAR_V1_Type *)(base))->INJ_CHAN_CONFIG)
#define SAR_INJ_RESULT(base)                (((SAR_V1_Type *)(base))->INJ_RESULT)


/*******************************************************************************
*                SDHC
*******************************************************************************/

#define SDHC_WRAP_CTL(base)                     (((SDHC_V1_Type *)(base))->WRAP.CTL)
#define SDHC_CORE_SDMASA_R(base)                (((SDHC_V1_Type *)(base))->CORE.SDMASA_R)
#define SDHC_CORE_BLOCKSIZE_R(base)             (((SDHC_V1_Type *)(base))->CORE.BLOCKSIZE_R)
#define SDHC_CORE_BLOCKCOUNT_R(base)            (((SDHC_V1_Type *)(base))->CORE.BLOCKCOUNT_R)
#define SDHC_CORE_ARGUMENT_R(base)              (((SDHC_V1_Type *)(base))->CORE.ARGUMENT_R)
#define SDHC_CORE_XFER_MODE_R(base)             (((SDHC_V1_Type *)(base))->CORE.XFER_MODE_R)
#define SDHC_CORE_CMD_R(base)                   (((SDHC_V1_Type *)(base))->CORE.CMD_R)
#define SDHC_CORE_RESP01_R(base)                (((SDHC_V1_Type *)(base))->CORE.RESP01_R)
#define SDHC_CORE_RESP23_R(base)                (((SDHC_V1_Type *)(base))->CORE.RESP23_R)
#define SDHC_CORE_RESP45_R(base)                (((SDHC_V1_Type *)(base))->CORE.RESP45_R)
#define SDHC_CORE_RESP67_R(base)                (((SDHC_V1_Type *)(base))->CORE.RESP67_R)
#define SDHC_CORE_BUF_DATA_R(base)              (((SDHC_V1_Type *)(base))->CORE.BUF_DATA_R)
#define SDHC_CORE_PSTATE_REG(base)              (((SDHC_V1_Type *)(base))->CORE.PSTATE_REG)
#define SDHC_CORE_HOST_CTRL1_R(base)            (((SDHC_V1_Type *)(base))->CORE.HOST_CTRL1_R)
#define SDHC_CORE_PWR_CTRL_R(base)              (((SDHC_V1_Type *)(base))->CORE.PWR_CTRL_R)
#define SDHC_CORE_BGAP_CTRL_R(base)             (((SDHC_V1_Type *)(base))->CORE.BGAP_CTRL_R)
#define SDHC_CORE_WUP_CTRL_R(base)              (((SDHC_V1_Type *)(base))->CORE.WUP_CTRL_R)
#define SDHC_CORE_CLK_CTRL_R(base)              (((SDHC_V1_Type *)(base))->CORE.CLK_CTRL_R)
#define SDHC_CORE_TOUT_CTRL_R(base)             (((SDHC_V1_Type *)(base))->CORE.TOUT_CTRL_R)
#define SDHC_CORE_SW_RST_R(base)                (((SDHC_V1_Type *)(base))->CORE.SW_RST_R)
#define SDHC_CORE_NORMAL_INT_STAT_R(base)       (((SDHC_V1_Type *)(base))->CORE.NORMAL_INT_STAT_R)
#define SDHC_CORE_ERROR_INT_STAT_R(base)        (((SDHC_V1_Type *)(base))->CORE.ERROR_INT_STAT_R)
#define SDHC_CORE_NORMAL_INT_STAT_EN_R(base)    (((SDHC_V1_Type *)(base))->CORE.NORMAL_INT_STAT_EN_R)
#define SDHC_CORE_ERROR_INT_STAT_EN_R(base)     (((SDHC_V1_Type *)(base))->CORE.ERROR_INT_STAT_EN_R)
#define SDHC_CORE_NORMAL_INT_SIGNAL_EN_R(base)  (((SDHC_V1_Type *)(base))->CORE.NORMAL_INT_SIGNAL_EN_R)
#define SDHC_CORE_ERROR_INT_SIGNAL_EN_R(base)   (((SDHC_V1_Type *)(base))->CORE.ERROR_INT_SIGNAL_EN_R)
#define SDHC_CORE_AUTO_CMD_STAT_R(base)         (((SDHC_V1_Type *)(base))->CORE.AUTO_CMD_STAT_R)
#define SDHC_CORE_HOST_CTRL2_R(base)            (((SDHC_V1_Type *)(base))->CORE.HOST_CTRL2_R)
#define SDHC_CORE_CAPABILITIES1_R(base)         (((SDHC_V1_Type *)(base))->CORE.CAPABILITIES1_R)
#define SDHC_CORE_CAPABILITIES2_R(base)         (((SDHC_V1_Type *)(base))->CORE.CAPABILITIES2_R)
#define SDHC_CORE_CURR_CAPABILITIES1_R(base)    (((SDHC_V1_Type *)(base))->CORE.CURR_CAPABILITIES1_R)
#define SDHC_CORE_CURR_CAPABILITIES2_R(base)    (((SDHC_V1_Type *)(base))->CORE.CURR_CAPABILITIES2_R)
#define SDHC_CORE_ADMA_ERR_STAT_R(base)         (((SDHC_V1_Type *)(base))->CORE.ADMA_ERR_STAT_R)
#define SDHC_CORE_ADMA_SA_LOW_R(base)           (((SDHC_V1_Type *)(base))->CORE.ADMA_SA_LOW_R)
#define SDHC_CORE_ADMA_ID_LOW_R(base)           (((SDHC_V1_Type *)(base))->CORE.ADMA_ID_LOW_R)
#define SDHC_CORE_EMMC_CTRL_R(base)             (((SDHC_V1_Type *)(base))->CORE.EMMC_CTRL_R)
#define SDHC_CORE_GP_OUT_R(base)                (((SDHC_V1_Type *)(base))->CORE.GP_OUT_R)


/*******************************************************************************
*                SMARTIO
*******************************************************************************/

#define SMARTIO_PRT_CTL(base)               (((SMARTIO_PRT_Type *)(base))->CTL)
#define SMARTIO_PRT_SYNC_CTL(base)          (((SMARTIO_PRT_Type *)(base))->SYNC_CTL)
#define SMARTIO_PRT_LUT_SEL(base, idx)      (((SMARTIO_PRT_Type *)(base))->LUT_SEL[idx])
#define SMARTIO_PRT_LUT_CTL(base, idx)      (((SMARTIO_PRT_Type *)(base))->LUT_CTL[idx])
#define SMARTIO_PRT_DU_SEL(base)            (((SMARTIO_PRT_Type *)(base))->DU_SEL)
#define SMARTIO_PRT_DU_CTL(base)            (((SMARTIO_PRT_Type *)(base))->DU_CTL)
#define SMARTIO_PRT_DATA(base)              (((SMARTIO_PRT_Type *)(base))->DATA)


/*******************************************************************************
*                SMIF
*******************************************************************************/

#define SMIF_DEVICE_CTL(base)               (((SMIF_DEVICE_V1_Type *)(base))->CTL)
#define SMIF_DEVICE_ADDR(base)              (((SMIF_DEVICE_V1_Type *)(base))->ADDR)
#define SMIF_DEVICE_ADDR_CTL(base)          (((SMIF_DEVICE_V1_Type *)(base))->ADDR_CTL)
#define SMIF_DEVICE_MASK(base)              (((SMIF_DEVICE_V1_Type *)(base))->MASK)
#define SMIF_DEVICE_RD_CMD_CTL(base)        (((SMIF_DEVICE_V1_Type *)(base))->RD_CMD_CTL)
#define SMIF_DEVICE_RD_ADDR_CTL(base)       (((SMIF_DEVICE_V1_Type *)(base))->RD_ADDR_CTL)
#define SMIF_DEVICE_RD_MODE_CTL(base)       (((SMIF_DEVICE_V1_Type *)(base))->RD_MODE_CTL)
#define SMIF_DEVICE_RD_DUMMY_CTL(base)      (((SMIF_DEVICE_V1_Type *)(base))->RD_DUMMY_CTL)
#define SMIF_DEVICE_RD_DATA_CTL(base)       (((SMIF_DEVICE_V1_Type *)(base))->RD_DATA_CTL)
#define SMIF_DEVICE_WR_CMD_CTL(base)        (((SMIF_DEVICE_V1_Type *)(base))->WR_CMD_CTL)
#define SMIF_DEVICE_WR_ADDR_CTL(base)       (((SMIF_DEVICE_V1_Type *)(base))->WR_ADDR_CTL)
#define SMIF_DEVICE_WR_MODE_CTL(base)       (((SMIF_DEVICE_V1_Type *)(base))->WR_MODE_CTL)
#define SMIF_DEVICE_WR_DUMMY_CTL(base)      (((SMIF_DEVICE_V1_Type *)(base))->WR_DUMMY_CTL)
#define SMIF_DEVICE_WR_DATA_CTL(base)       (((SMIF_DEVICE_V1_Type *)(base))->WR_DATA_CTL)

#define SMIF_DEVICE_IDX(base, deviceIndex)                 (((SMIF_V1_Type *)(base))->DEVICE[deviceIndex])

#define SMIF_DEVICE_IDX_CTL(base, deviceIndex)             (SMIF_DEVICE_IDX(base, deviceIndex).CTL)
#define SMIF_DEVICE_IDX_ADDR(base, deviceIndex)            (SMIF_DEVICE_IDX(base, deviceIndex).ADDR)
#define SMIF_DEVICE_IDX_ADDR_CTL(base, deviceIndex)        (SMIF_DEVICE_IDX(base, deviceIndex).ADDR_CTL)
#define SMIF_DEVICE_IDX_MASK(base, deviceIndex)            (SMIF_DEVICE_IDX(base, deviceIndex).MASK)
#define SMIF_DEVICE_IDX_RD_CMD_CTL(base, deviceIndex)      (SMIF_DEVICE_IDX(base, deviceIndex).RD_CMD_CTL)
#define SMIF_DEVICE_IDX_RD_ADDR_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).RD_ADDR_CTL)
#define SMIF_DEVICE_IDX_RD_MODE_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).RD_MODE_CTL)
#define SMIF_DEVICE_IDX_RD_DUMMY_CTL(base, deviceIndex)    (SMIF_DEVICE_IDX(base, deviceIndex).RD_DUMMY_CTL)
#define SMIF_DEVICE_IDX_RD_DATA_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).RD_DATA_CTL)
#define SMIF_DEVICE_IDX_WR_CMD_CTL(base, deviceIndex)      (SMIF_DEVICE_IDX(base, deviceIndex).WR_CMD_CTL)
#define SMIF_DEVICE_IDX_WR_ADDR_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).WR_ADDR_CTL)
#define SMIF_DEVICE_IDX_WR_MODE_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).WR_MODE_CTL)
#define SMIF_DEVICE_IDX_WR_DUMMY_CTL(base, deviceIndex)    (SMIF_DEVICE_IDX(base, deviceIndex).WR_DUMMY_CTL)
#define SMIF_DEVICE_IDX_WR_DATA_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).WR_DATA_CTL)

#define SMIF_CTL(base)                      (((SMIF_V1_Type *)(base))->CTL)
#define SMIF_STATUS(base)                   (((SMIF_V1_Type *)(base))->STATUS)
#define SMIF_TX_DATA_FIFO_CTL(base)         (((SMIF_V1_Type *)(base))->TX_DATA_FIFO_CTL)
#define SMIF_RX_DATA_FIFO_CTL(base)         (((SMIF_V1_Type *)(base))->RX_DATA_FIFO_CTL)
#define SMIF_TX_DATA_FIFO_WR1(base)         (((SMIF_V1_Type *)(base))->TX_DATA_FIFO_WR1)
#define SMIF_TX_DATA_FIFO_WR2(base)         (((SMIF_V1_Type *)(base))->TX_DATA_FIFO_WR2)
#define SMIF_TX_DATA_FIFO_WR4(base)         (((SMIF_V1_Type *)(base))->TX_DATA_FIFO_WR4)
#define SMIF_RX_DATA_FIFO_RD1(base)         (((SMIF_V1_Type *)(base))->RX_DATA_FIFO_RD1)
#define SMIF_RX_DATA_FIFO_RD2(base)         (((SMIF_V1_Type *)(base))->RX_DATA_FIFO_RD2)
#define SMIF_RX_DATA_FIFO_RD4(base)         (((SMIF_V1_Type *)(base))->RX_DATA_FIFO_RD4)
#define SMIF_TX_CMD_FIFO_WR(base)           (((SMIF_V1_Type *)(base))->TX_CMD_FIFO_WR)
#define SMIF_TX_CMD_FIFO_STATUS(base)       (((SMIF_V1_Type *)(base))->TX_CMD_FIFO_STATUS)
#define SMIF_RX_DATA_FIFO_STATUS(base)      (((SMIF_V1_Type *)(base))->RX_DATA_FIFO_STATUS)
#define SMIF_TX_DATA_FIFO_STATUS(base)      (((SMIF_V1_Type *)(base))->TX_DATA_FIFO_STATUS)
#define SMIF_INTR(base)                     (((SMIF_V1_Type *)(base))->INTR)
#define SMIF_INTR_SET(base)                 (((SMIF_V1_Type *)(base))->INTR_SET)
#define SMIF_INTR_MASK(base)                (((SMIF_V1_Type *)(base))->INTR_MASK)
#define SMIF_INTR_MASKED(base)              (((SMIF_V1_Type *)(base))->INTR_MASKED)
#define SMIF_CRYPTO_INPUT0(base)            (((SMIF_V1_Type *)(base))->CRYPTO_INPUT0)
#define SMIF_CRYPTO_INPUT1(base)            (((SMIF_V1_Type *)(base))->CRYPTO_INPUT1)
#define SMIF_CRYPTO_INPUT2(base)            (((SMIF_V1_Type *)(base))->CRYPTO_INPUT2)
#define SMIF_CRYPTO_INPUT3(base)            (((SMIF_V1_Type *)(base))->CRYPTO_INPUT3)
#define SMIF_CRYPTO_KEY0(base)              (((SMIF_V1_Type *)(base))->CRYPTO_KEY0)
#define SMIF_CRYPTO_KEY1(base)              (((SMIF_V1_Type *)(base))->CRYPTO_KEY1)
#define SMIF_CRYPTO_KEY2(base)              (((SMIF_V1_Type *)(base))->CRYPTO_KEY2)
#define SMIF_CRYPTO_KEY3(base)              (((SMIF_V1_Type *)(base))->CRYPTO_KEY3)
#define SMIF_CRYPTO_OUTPUT0(base)           (((SMIF_V1_Type *)(base))->CRYPTO_OUTPUT0)
#define SMIF_CRYPTO_OUTPUT1(base)           (((SMIF_V1_Type *)(base))->CRYPTO_OUTPUT1)
#define SMIF_CRYPTO_OUTPUT2(base)           (((SMIF_V1_Type *)(base))->CRYPTO_OUTPUT2)
#define SMIF_CRYPTO_OUTPUT3(base)           (((SMIF_V1_Type *)(base))->CRYPTO_OUTPUT3)
#define SMIF_CRYPTO_CMD(base)               (((SMIF_V1_Type *)(base))->CRYPTO_CMD)
#define SMIF_SLOW_CA_CTL(base)              (((SMIF_V1_Type *)(base))->SLOW_CA_CTL)
#define SMIF_FAST_CA_CTL(base)              (((SMIF_V1_Type *)(base))->FAST_CA_CTL)
#define SMIF_SLOW_CA_CMD(base)              (((SMIF_V1_Type *)(base))->SLOW_CA_CMD)
#define SMIF_FAST_CA_CMD(base)              (((SMIF_V1_Type *)(base))->FAST_CA_CMD)


/*******************************************************************************
*                DW
*******************************************************************************/

#define CY_DW_V1                            (0x20U > cy_device->dwVersion)
#define CY_DW_CRC                           ((uint32_t)(0x20U <= cy_device->dwVersion))
#define CY_DW0_BASE                         ((DW_Type*) 0x40280000UL)
#define CY_DW0_CH_NR                        (cy_device->cpussDw0ChNr)
#define CY_DW1_CH_NR                        (cy_device->cpussDw1ChNr)

#define CY_DW_CH_CTL_PRIO_Pos               ((uint32_t)(cy_device->dwChCtlPrioPos))
#define CY_DW_CH_CTL_PRIO_Msk               ((uint32_t)(0x3UL << CY_DW_CH_CTL_PRIO_Pos))
#define CY_DW_CH_CTL_PREEMPTABLE_Pos        ((uint32_t)(cy_device->dwChCtlPreemptablePos))
#define CY_DW_CH_CTL_PREEMPTABLE_Msk        ((uint32_t)(0x1UL << CY_DW_CH_CTL_PREEMPTABLE_Pos))
#define CY_DW_STATUS_CH_IDX_Pos             ((uint32_t)(cy_device->dwStatusChIdxPos))
#define CY_DW_STATUS_CH_IDX_Msk             (cy_device->dwStatusChIdxMsk)

#define DW_CTL(base)                        (((DW_Type*)(base))->CTL)
#define DW_STATUS(base)                     (((DW_Type const*)(base))->STATUS)
#define DW_DESCR_SRC(base)                  (((DW_Type*)(base))->ACT_DESCR_SRC)
#define DW_DESCR_DST(base)                  (((DW_Type*)(base))->ACT_DESCR_DST)

#define DW_CRC_CTL(base)                    (((DW_V2_Type*)(base))->CRC_CTL)
#define DW_CRC_DATA_CTL(base)               (((DW_V2_Type*)(base))->CRC_DATA_CTL)
#define DW_CRC_REM_CTL(base)                (((DW_V2_Type*)(base))->CRC_REM_CTL)
#define DW_CRC_POL_CTL(base)                (((DW_V2_Type*)(base))->CRC_POL_CTL)
#define DW_CRC_LFSR_CTL(base)               (((DW_V2_Type*)(base))->CRC_LFSR_CTL)

#define DW_CH(base, chan)                   ((DW_CH_STRUCT_V2_Type*)((uint32_t)(base) + cy_device->dwChOffset + ((chan) * cy_device->dwChSize)))
#define DW_CH_CTL(base, chan)               (DW_CH(base, chan)->CH_CTL)
#define DW_CH_STATUS(base, chan)            (DW_CH(base, chan)->CH_STATUS)
#define DW_CH_IDX(base, chan)               (DW_CH(base, chan)->CH_IDX)
#define DW_CH_CURR_PTR(base, chan)          (DW_CH(base, chan)->CH_CURR_PTR)

#define DW_CH_INTR(base, chan)              (DW_CH(base, chan)->INTR)
#define DW_CH_INTR_SET(base, chan)          (DW_CH(base, chan)->INTR_SET)
#define DW_CH_INTR_MASK(base, chan)         (DW_CH(base, chan)->INTR_MASK)
#define DW_CH_INTR_MASKED(base, chan)       (DW_CH(base, chan)->INTR_MASKED)


/*******************************************************************************
*                DMAC
*******************************************************************************/

#define CY_DMAC_CH_NR                       CPUSS_DMAC_CH_NR
#define DMAC_CTL(base)                      (((DMAC_V2_Type*)(base))->CTL)
#define DMAC_ACTIVE(base)                   (((DMAC_V2_Type const*)(base))->ACTIVE)
#define DMAC_CH(base, chan)                 (&(((DMAC_V2_Type*)(base))->CH[(chan)]))
#define DMAC_CH_CTL(base, chan)             (DMAC_CH(base, chan)->CTL)
#define DMAC_CH_IDX(base, chan)             (DMAC_CH(base, chan)->IDX)
#define DMAC_CH_CURR(base, chan)            (DMAC_CH(base, chan)->CURR)
#define DMAC_CH_DESCR_SRC(base, chan)       (DMAC_CH(base, chan)->DESCR_SRC)
#define DMAC_CH_DESCR_DST(base, chan)       (DMAC_CH(base, chan)->DESCR_DST)
#define DMAC_CH_INTR(base, chan)            (DMAC_CH(base, chan)->INTR)
#define DMAC_CH_INTR_SET(base, chan)        (DMAC_CH(base, chan)->INTR_SET)
#define DMAC_CH_INTR_MASK(base, chan)       (DMAC_CH(base, chan)->INTR_MASK)
#define DMAC_CH_INTR_MASKED(base, chan)     (DMAC_CH(base, chan)->INTR_MASKED)


/*******************************************************************************
*                PERI
*******************************************************************************/
#define CY_PERI_BASE                        ((PERI_V1_Type *) cy_device->periBase)

#define CY_PERI_V1                          ((uint32_t)(0x20U > cy_device->periVersion)) /* true if the mxperi version is 1.x */
#define CY_PERI_V2_TR_GR_SIZE               (sizeof(PERI_TR_GR_V2_Type))
#define CY_PERI_TR_CTL_NUM                  ((uint32_t)cy_device->periTrGrSize / sizeof(uint32_t))
#define CY_PERI_TR_CTL_SEL_Pos              (0UL)
#define CY_PERI_TR_CTL_SEL_Msk              ((uint32_t)CY_PERI_TR_CTL_NUM - 1UL)
#define CY_PERI_TR_CMD_GROUP_SEL_Pos        (PERI_TR_CMD_GROUP_SEL_Pos)
#define CY_PERI_TR_CMD_GROUP_SEL_Msk        ((uint32_t)cy_device->periTrCmdGrSelMsk)

#define PERI_TR_CMD                         (*(volatile uint32_t*)((uint32_t)cy_device->periBase + \
                                                                   (uint32_t)cy_device->periTrCmdOffset))
#define PERI_TR_GR_TR_CTL(group, trCtl)     (*(volatile uint32_t*)((uint32_t)cy_device->periBase + \
                                                                   (uint32_t)cy_device->periTrGrOffset + \
                                                        ((group) * (uint32_t)cy_device->periTrGrSize) + \
                                                        ((trCtl) * (uint32_t)sizeof(uint32_t))))

#define CY_PERI_CLOCK_NR                    ((uint32_t)(cy_device->periClockNr))

#define PERI_DIV_CMD                        ((CY_PERI_BASE)->DIV_CMD)

#define CY_PERI_DIV_CMD_DIV_SEL_Pos         (PERI_DIV_CMD_DIV_SEL_Pos)
#define CY_PERI_DIV_CMD_DIV_SEL_Msk         ((uint32_t)(cy_device->periDivCmdDivSelMsk))
#define CY_PERI_DIV_CMD_TYPE_SEL_Pos        ((uint32_t)(cy_device->periDivCmdTypeSelPos))
#define CY_PERI_DIV_CMD_TYPE_SEL_Msk        ((uint32_t)(0x3UL << CY_PERI_DIV_CMD_TYPE_SEL_Pos))
#define CY_PERI_DIV_CMD_PA_DIV_SEL_Pos      ((uint32_t)(cy_device->periDivCmdPaDivSelPos))
#define CY_PERI_DIV_CMD_PA_DIV_SEL_Msk      ((uint32_t)(CY_PERI_DIV_CMD_DIV_SEL_Msk << CY_PERI_DIV_CMD_PA_DIV_SEL_Pos))
#define CY_PERI_DIV_CMD_PA_TYPE_SEL_Pos     ((uint32_t)(cy_device->periDivCmdPaTypeSelPos))
#define CY_PERI_DIV_CMD_PA_TYPE_SEL_Msk     ((uint32_t)(0x3UL << CY_PERI_DIV_CMD_PA_TYPE_SEL_Pos))

#define PERI_CLOCK_CTL                      ((CY_PERI_BASE)->CLOCK_CTL)

#define CY_PERI_CLOCK_CTL_DIV_SEL_Pos       (PERI_CLOCK_CTL_DIV_SEL_Pos)
#define CY_PERI_CLOCK_CTL_DIV_SEL_Msk       (CY_PERI_DIV_CMD_DIV_SEL_Msk)
#define CY_PERI_CLOCK_CTL_TYPE_SEL_Pos      (CY_PERI_DIV_CMD_TYPE_SEL_Pos)
#define CY_PERI_CLOCK_CTL_TYPE_SEL_Msk      (CY_PERI_DIV_CMD_TYPE_SEL_Msk)

#define PERI_DIV_8_CTL                      ((volatile uint32_t *)((uint32_t)(cy_device->periBase) + (uint32_t)(cy_device->periDiv8CtlOffset)))
#define PERI_DIV_16_CTL                     ((volatile uint32_t *)((uint32_t)(cy_device->periBase) + (uint32_t)(cy_device->periDiv16CtlOffset)))
#define PERI_DIV_16_5_CTL                   ((volatile uint32_t *)((uint32_t)(cy_device->periBase) + (uint32_t)(cy_device->periDiv16_5CtlOffset)))
#define PERI_DIV_24_5_CTL                   ((volatile uint32_t *)((uint32_t)(cy_device->periBase) + (uint32_t)(cy_device->periDiv24_5CtlOffset)))

#define PERI_GR_SL_CTL(udbGroupNr)          ((CY_PERI_BASE)->GR[udbGroupNr].SL_CTL)

#define PERI_PPU_PR_ADDR0(base)             (((PERI_PPU_PR_V1_Type *) (base))->ADDR0)
#define PERI_PPU_PR_ATT0(base)              (((PERI_PPU_PR_V1_Type *) (base))->ATT0)
#define PERI_PPU_PR_ATT1(base)              (((PERI_PPU_PR_V1_Type *) (base))->ATT1)

#define PERI_PPU_GR_ADDR0(base)             (((PERI_PPU_GR_V1_Type *) (base))->ADDR0)
#define PERI_PPU_GR_ATT0(base)              (((PERI_PPU_GR_V1_Type *) (base))->ATT0)
#define PERI_PPU_GR_ATT1(base)              (((PERI_PPU_GR_V1_Type *) (base))->ATT1)

#define PERI_GR_PPU_SL_ADDR0(base)          (((PERI_GR_PPU_SL_V1_Type *) (base))->ADDR0)
#define PERI_GR_PPU_SL_ATT0(base)           (((PERI_GR_PPU_SL_V1_Type *) (base))->ATT0)
#define PERI_GR_PPU_SL_ATT1(base)           (((PERI_GR_PPU_SL_V1_Type *) (base))->ATT1)

#define PERI_GR_PPU_RG_ADDR0(base)          (((PERI_GR_PPU_RG_V1_Type *) (base))->ADDR0)
#define PERI_GR_PPU_RG_ATT0(base)           (((PERI_GR_PPU_RG_V1_Type *) (base))->ATT0)
#define PERI_GR_PPU_RG_ATT1(base)           (((PERI_GR_PPU_RG_V1_Type *) (base))->ATT1)

#define PERI_MS_PPU_PR_SL_ADDR(base)        (((PERI_MS_PPU_PR_V2_Type *) (base))->SL_ADDR)
#define PERI_MS_PPU_PR_SL_SIZE(base)        (((PERI_MS_PPU_PR_V2_Type *) (base))->SL_SIZE)
#define PERI_MS_PPU_PR_MS_ATT(base)         ((volatile uint32_t *) &(((PERI_MS_PPU_PR_V2_Type *)(base))->MS_ATT0))
#define PERI_MS_PPU_PR_SL_ATT(base)         ((volatile uint32_t *) &(((PERI_MS_PPU_PR_V2_Type *)(base))->SL_ATT0))
#define PERI_MS_PPU_FX_MS_ATT(base)         ((volatile uint32_t *) &(((PERI_MS_PPU_FX_V2_Type *)(base))->MS_ATT0))
#define PERI_MS_PPU_FX_SL_ATT(base)         ((volatile uint32_t *) &(((PERI_MS_PPU_FX_V2_Type *)(base))->SL_ATT0))

#define PROT_PERI_PPU_PR_STRUCT_IDX_ATT0(stcIdx)    ((CY_PERI_BASE)->PPU_PR[(stcIdx)].ATT0)
#define PROT_PERI_PPU_PR_STRUCT_IDX_ATT1(stcIdx)    ((CY_PERI_BASE)->PPU_PR[(stcIdx)].ATT1)

#define PROT_PERI_PPU_PR_STRUCT_IDX(stcIdx)         ((PERI_PPU_PR_Type*) &(CY_PERI_BASE)->PPU_PR[(stcIdx)])


/*******************************************************************************
*                PROT
*******************************************************************************/
#define CY_PROT_BASE                        (cy_device->protBase)

#define CY_PROT_PC_MAX                      (8UL)
#define CY_PROT_BUS_MASTER_MASK             (cy_device->protBusMasterMask)
#define PROT_MPU_MS_CTL(mpu)                (((PROT_Type*)CY_PROT_BASE)->CYMPU[(mpu)].MS_CTL)
#define PROT_MPU_MPU_STRUCT_ADDR(base)      (((PROT_MPU_MPU_STRUCT_Type *) (base))->ADDR)
#define PROT_MPU_MPU_STRUCT_ATT(base)       (((PROT_MPU_MPU_STRUCT_Type *) (base))->ATT)

#define PROT_SMPU_SMPU_STRUCT_ADDR0(base)   (((PROT_SMPU_SMPU_STRUCT_Type *) (base))->ADDR0)
#define PROT_SMPU_SMPU_STRUCT_ADDR1(base)   (((PROT_SMPU_SMPU_STRUCT_Type *) (base))->ADDR1)
#define PROT_SMPU_SMPU_STRUCT_ATT0(base)    (((PROT_SMPU_SMPU_STRUCT_Type *) (base))->ATT0)
#define PROT_SMPU_SMPU_STRUCT_ATT1(base)    (((PROT_SMPU_SMPU_STRUCT_Type *) (base))->ATT1)

#define PROT_SMPU_SMPU_STRUCT_IDX_ATT0(stcIdx)    (((PROT_SMPU_Type *) CY_PROT_BASE)->SMPU_STRUCT[(stcIdx)].ATT0)
#define PROT_SMPU_SMPU_STRUCT_IDX_ATT1(stcIdx)    (((PROT_SMPU_Type *) CY_PROT_BASE)->SMPU_STRUCT[(stcIdx)].ATT1)
#define PROT_SMPU_SMPU_STRUCT_IDX(stcIdx)         (((PROT_SMPU_SMPU_STRUCT_Type *) &((PROT_SMPU_Type *) CY_PROT_BASE)->SMPU_STRUCT[(stcIdx)]))


/*******************************************************************************
*                IOSS
*******************************************************************************/

#define CY_GPIO_BASE                       ((uint32_t)(cy_device->gpioBase))

#define GPIO_INTR_CAUSE0                   (((GPIO_V1_Type*)(cy_device->gpioBase))->INTR_CAUSE0)
#define GPIO_INTR_CAUSE1                   (((GPIO_V1_Type*)(cy_device->gpioBase))->INTR_CAUSE1)
#define GPIO_INTR_CAUSE2                   (((GPIO_V1_Type*)(cy_device->gpioBase))->INTR_CAUSE2)
#define GPIO_INTR_CAUSE3                   (((GPIO_V1_Type*)(cy_device->gpioBase))->INTR_CAUSE3)

#define GPIO_PRT_OUT(base)                 (((GPIO_PRT_Type*)(base))->OUT)
#define GPIO_PRT_OUT_CLR(base)             (((GPIO_PRT_Type*)(base))->OUT_CLR)
#define GPIO_PRT_OUT_SET(base)             (((GPIO_PRT_Type*)(base))->OUT_SET)
#define GPIO_PRT_OUT_INV(base)             (((GPIO_PRT_Type*)(base))->OUT_INV)
#define GPIO_PRT_IN(base)                  (((GPIO_PRT_Type*)(base))->IN)
#define GPIO_PRT_INTR(base)                (((GPIO_PRT_Type*)(base))->INTR)
#define GPIO_PRT_INTR_MASK(base)           (((GPIO_PRT_Type*)(base))->INTR_MASK)
#define GPIO_PRT_INTR_MASKED(base)         (((GPIO_PRT_Type*)(base))->INTR_MASKED)
#define GPIO_PRT_INTR_SET(base)            (((GPIO_PRT_Type*)(base))->INTR_SET)

#define GPIO_PRT_INTR_CFG(base)            (*(volatile uint32_t *)((uint32_t)(base) + (uint32_t)(cy_device->gpioPrtIntrCfgOffset)))
#define GPIO_PRT_CFG(base)                 (*(volatile uint32_t *)((uint32_t)(base) + (uint32_t)(cy_device->gpioPrtCfgOffset)))
#define GPIO_PRT_CFG_IN(base)              (*(volatile uint32_t *)((uint32_t)(base) + (uint32_t)(cy_device->gpioPrtCfgInOffset)))
#define GPIO_PRT_CFG_OUT(base)             (*(volatile uint32_t *)((uint32_t)(base) + (uint32_t)(cy_device->gpioPrtCfgOutOffset)))
#define GPIO_PRT_CFG_SIO(base)             (*(volatile uint32_t *)((uint32_t)(base) + (uint32_t)(cy_device->gpioPrtCfgSioOffset)))

#define CY_HSIOM_BASE                      ((uint32_t)(cy_device->hsiomBase))

#define HSIOM_PRT_PORT_SEL0(base)          (((HSIOM_PRT_V1_Type *)(base))->PORT_SEL0)
#define HSIOM_PRT_PORT_SEL1(base)          (((HSIOM_PRT_V1_Type *)(base))->PORT_SEL1)

#define HSIOM_AMUX_SPLIT_CTL(switchCtrl)    (((HSIOM_V1_Type *) CY_HSIOM_BASE)->AMUX_SPLIT_CTL[switchCtrl])


/*******************************************************************************
*                I2S
*******************************************************************************/
#if (defined(AUDIOSS_I2S) || defined(AUDIOSS0_I2S))
#define AUDIOSS_I2S_PRESENT
#endif

#define REG_I2S_CTL(base)                   (((I2S_V1_Type*)(base))->CTL)
#define REG_I2S_CMD(base)                   (((I2S_V1_Type*)(base))->CMD)
#define REG_I2S_CLOCK_CTL(base)             (((I2S_V1_Type*)(base))->CLOCK_CTL)
#define REG_I2S_TR_CTL(base)                (((I2S_V1_Type*)(base))->TR_CTL)
#define REG_I2S_TX_CTL(base)                (((I2S_V1_Type*)(base))->TX_CTL)
#define REG_I2S_TX_FIFO_CTL(base)           (((I2S_V1_Type*)(base))->TX_FIFO_CTL)
#define REG_I2S_TX_FIFO_STATUS(base)        (((I2S_V1_Type*)(base))->TX_FIFO_STATUS)
#define REG_I2S_TX_FIFO_WR(base)            (((I2S_V1_Type*)(base))->TX_FIFO_WR)
#define REG_I2S_TX_WATCHDOG(base)           (((I2S_V1_Type*)(base))->TX_WATCHDOG)
#define REG_I2S_RX_CTL(base)                (((I2S_V1_Type*)(base))->RX_CTL)
#define REG_I2S_RX_FIFO_CTL(base)           (((I2S_V1_Type*)(base))->RX_FIFO_CTL)
#define REG_I2S_RX_FIFO_STATUS(base)        (((I2S_V1_Type*)(base))->RX_FIFO_STATUS)
#define REG_I2S_RX_FIFO_RD(base)            (((I2S_V1_Type*)(base))->RX_FIFO_RD)
#define REG_I2S_RX_FIFO_RD_SILENT(base)     (((I2S_V1_Type*)(base))->RX_FIFO_RD_SILENT)
#define REG_I2S_RX_WATCHDOG(base)           (((I2S_V1_Type*)(base))->RX_WATCHDOG)
#define REG_I2S_INTR(base)                  (((I2S_V1_Type*)(base))->INTR)
#define REG_I2S_INTR_SET(base)              (((I2S_V1_Type*)(base))->INTR_SET)
#define REG_I2S_INTR_MASK(base)             (((I2S_V1_Type*)(base))->INTR_MASK)
#define REG_I2S_INTR_MASKED(base)           (((I2S_V1_Type*)(base))->INTR_MASKED)


/*******************************************************************************
*                PDM
*******************************************************************************/
#if (defined(AUDIOSS_PDM) || defined(AUDIOSS0_PDM))
#define AUDIOSS_PDM_PRESENT
#endif

#define PDM_PCM_CTL(base)                   (((PDM_V1_Type*)(base))->CTL)
#define PDM_PCM_CMD(base)                   (((PDM_V1_Type*)(base))->CMD)
#define PDM_PCM_CLOCK_CTL(base)             (((PDM_V1_Type*)(base))->CLOCK_CTL)
#define PDM_PCM_MODE_CTL(base)              (((PDM_V1_Type*)(base))->MODE_CTL)
#define PDM_PCM_DATA_CTL(base)              (((PDM_V1_Type*)(base))->DATA_CTL)
#define PDM_PCM_TR_CTL(base)                (((PDM_V1_Type*)(base))->TR_CTL)
#define PDM_PCM_INTR_MASK(base)             (((PDM_V1_Type*)(base))->INTR_MASK)
#define PDM_PCM_INTR_MASKED(base)           (((PDM_V1_Type*)(base))->INTR_MASKED)
#define PDM_PCM_INTR(base)                  (((PDM_V1_Type*)(base))->INTR)
#define PDM_PCM_INTR_SET(base)              (((PDM_V1_Type*)(base))->INTR_SET)
#define PDM_PCM_RX_FIFO_STATUS(base)        (((PDM_V1_Type*)(base))->RX_FIFO_STATUS)
#define PDM_PCM_RX_FIFO_CTL(base)           (((PDM_V1_Type*)(base))->RX_FIFO_CTL)
#define PDM_PCM_RX_FIFO_RD(base)            (((PDM_V1_Type*)(base))->RX_FIFO_RD)
#define PDM_PCM_RX_FIFO_RD_SILENT(base)     (((PDM_V1_Type*)(base))->RX_FIFO_RD_SILENT)


/*******************************************************************************
*                LCD
*******************************************************************************/

#define LCD_OCTET_NUM                       (8U) /* LCD_NUMPORTS - number of octets supporting up to 4 COMs */
#define LCD_OCTET_NUM_8                     (8U) /* LCD_NUMPORTS8 - number of octets supporting up to 8 COMs */
#define LCD_OCTET_NUM_16                    (0U) /* LCD_NUMPORTS16 - number of octets supporting up to 16 COMs */
#define LCD_COM_NUM                         (8U) /* LCD_CHIP_TOP_COM_NR - maximum number of commons */

#define LCD_ID(base)                        (((LCD_V1_Type*)(base))->ID)
#define LCD_CONTROL(base)                   (((LCD_V1_Type*)(base))->CONTROL)
#define LCD_DIVIDER(base)                   (((LCD_V1_Type*)(base))->DIVIDER)
#define LCD_DATA0(base)                     (((LCD_V1_Type*)(base))->DATA0)
#define LCD_DATA1(base)                     (((LCD_V1_Type*)(base))->DATA1)
#define LCD_DATA2(base)                     (((LCD_V1_Type*)(base))->DATA2)
#define LCD_DATA3(base)                     (((LCD_V1_Type*)(base))->DATA3)


/*******************************************************************************
*                IPC
*******************************************************************************/

#define CY_IPC_V1                              (0x20u > cy_device->ipcVersion) /* true if the IPC version is 1.x */

#define REG_IPC_STRUCT_ACQUIRE(base)           (((IPC_STRUCT_Type*)(base))->ACQUIRE)
#define REG_IPC_STRUCT_RELEASE(base)           (((IPC_STRUCT_Type*)(base))->RELEASE)
#define REG_IPC_STRUCT_NOTIFY(base)            (((IPC_STRUCT_Type*)(base))->NOTIFY)
#if (CY_IP_M4CPUSS_VERSION == 1U)
#define REG_IPC_STRUCT_DATA(base)              (((IPC_STRUCT_V1_Type*)(base))->DATA)
#else
#define REG_IPC_STRUCT_DATA(base)              (((IPC_STRUCT_V2_Type*)(base))->DATA0)
#endif
#define REG_IPC_STRUCT_DATA1(base)             (((IPC_STRUCT_V2_Type*)(base))->DATA1)
#define REG_IPC_STRUCT_LOCK_STATUS(base)       (*(volatile uint32_t*)((uint32_t)(base) + cy_device->ipcLockStatusOffset))

#define REG_IPC_INTR_STRUCT_INTR(base)         (((IPC_INTR_STRUCT_Type*)(base))->INTR)
#define REG_IPC_INTR_STRUCT_INTR_SET(base)     (((IPC_INTR_STRUCT_Type*)(base))->INTR_SET)
#define REG_IPC_INTR_STRUCT_INTR_MASK(base)    (((IPC_INTR_STRUCT_Type*)(base))->INTR_MASK)
#define REG_IPC_INTR_STRUCT_INTR_MASKED(base)  (((IPC_INTR_STRUCT_Type*)(base))->INTR_MASKED)

#define CY_IPC_STRUCT_PTR(ipcIndex)            ((IPC_STRUCT_Type*)(cy_device->ipcBase + (cy_device->ipcStructSize * (ipcIndex))))
#define CY_IPC_INTR_STRUCT_PTR(ipcIntrIndex)   &(((IPC_Type *)cy_device->ipcBase)->INTR_STRUCT[ipcIntrIndex])

#define CY_IPC_STRUCT_PTR_FOR_IP(ipcIndex, base)            ((IPC_STRUCT_Type*)((uint32_t)(base) + (sizeof(IPC_STRUCT_Type) * (ipcIndex))))
#define CY_IPC_INTR_STRUCT_PTR_FOR_IP(ipcIntrIndex, base)   &(((IPC_Type *)base)->INTR_STRUCT[ipcIntrIndex])

#define CY_IPC_CHANNELS                        (uint32_t)(cy_device->cpussIpcNr)
#define CY_IPC_INTERRUPTS                      (uint32_t)(cy_device->cpussIpcIrqNr)

/* IPC channel definitions  */
#define CY_IPC_CHAN_SYSCALL_CM0             (0U)  /* System calls for the CM0 processor */
#define CY_IPC_CHAN_SYSCALL_CM4             (1U)  /* System calls for the 1st non-CM0 processor */
#define CY_IPC_CHAN_SYSCALL_DAP             (2UL) /* System calls for the DAP */
#define CY_IPC_CHAN_SEMA                    (3UL) /* IPC data channel for the Semaphores */
#define CY_IPC_CHAN_PRA                     (4UL) /* IPC data channel for PRA */
#define CY_IPC_CHAN_CYPIPE_EP0              (5UL) /* IPC data channel for CYPIPE EP0 */
#define CY_IPC_CHAN_CYPIPE_EP1              (6UL) /* IPC data channel for CYPIPE EP1 */
#define CY_IPC_CHAN_DDFT                    (7UL) /* IPC data channel for DDFT */

/* IPC Notify interrupts definitions */
#define CY_IPC_INTR_SYSCALL1                (0UL)
#define CY_IPC_INTR_CYPIPE_EP0              (3UL)
#define CY_IPC_INTR_CYPIPE_EP1              (4UL)
#define CY_IPC_INTR_PRA                     (5UL)
#define CY_IPC_INTR_SPARE                   (7UL)

/* Endpoint indexes in the pipe array */
#define CY_IPC_EP_CYPIPE_CM0_ADDR           (0UL)
#define CY_IPC_EP_CYPIPE_CM4_ADDR           (1UL)


/*******************************************************************************
*                CTB
*******************************************************************************/

#define CTBM_CTB_CTRL(base)                 (((CTBM_V1_Type *) (base))->CTB_CTRL)
#define CTBM_CTB_SW_DS_CTRL(base)           (((CTBM_V1_Type *) (base))->CTB_SW_DS_CTRL)
#define CTBM_CTB_SW_SQ_CTRL(base)           (((CTBM_V1_Type *) (base))->CTB_SW_SQ_CTRL)
#define CTBM_CTD_SW(base)                   (((CTBM_V1_Type *) (base))->CTD_SW)
#define CTBM_CTD_SW_CLEAR(base)             (((CTBM_V1_Type *) (base))->CTD_SW_CLEAR)
#define CTBM_COMP_STAT(base)                (((CTBM_V1_Type *) (base))->COMP_STAT)
#define CTBM_OA0_SW_CLEAR(base)             (((CTBM_V1_Type *) (base))->OA0_SW_CLEAR)
#define CTBM_OA1_SW_CLEAR(base)             (((CTBM_V1_Type *) (base))->OA1_SW_CLEAR)
#define CTBM_OA0_SW(base)                   (((CTBM_V1_Type *) (base))->OA0_SW)
#define CTBM_OA1_SW(base)                   (((CTBM_V1_Type *) (base))->OA1_SW)
#define CTBM_OA_RES0_CTRL(base)             (((CTBM_V1_Type *) (base))->OA_RES0_CTRL)
#define CTBM_OA_RES1_CTRL(base)             (((CTBM_V1_Type *) (base))->OA_RES1_CTRL)
#define CTBM_OA0_COMP_TRIM(base)            (((CTBM_V1_Type *) (base))->OA0_COMP_TRIM)
#define CTBM_OA1_COMP_TRIM(base)            (((CTBM_V1_Type *) (base))->OA1_COMP_TRIM)
#define CTBM_OA0_OFFSET_TRIM(base)          (((CTBM_V1_Type *) (base))->OA0_OFFSET_TRIM)
#define CTBM_OA1_OFFSET_TRIM(base)          (((CTBM_V1_Type *) (base))->OA1_OFFSET_TRIM)
#define CTBM_OA0_SLOPE_OFFSET_TRIM(base)    (((CTBM_V1_Type *) (base))->OA0_SLOPE_OFFSET_TRIM)
#define CTBM_OA1_SLOPE_OFFSET_TRIM(base)    (((CTBM_V1_Type *) (base))->OA1_SLOPE_OFFSET_TRIM)
#define CTBM_INTR(base)                     (((CTBM_V1_Type *) (base))->INTR)
#define CTBM_INTR_SET(base)                 (((CTBM_V1_Type *) (base))->INTR_SET)
#define CTBM_INTR_MASK(base)                (((CTBM_V1_Type *) (base))->INTR_MASK)
#define CTBM_INTR_MASKED(base)              (((CTBM_V1_Type *) (base))->INTR_MASKED)


/*******************************************************************************
*                CTDAC
*******************************************************************************/

#define CTDAC_CTDAC_CTRL(base)              (((CTDAC_V1_Type *) (base))->CTDAC_CTRL)
#define CTDAC_CTDAC_SW(base)                (((CTDAC_V1_Type *) (base))->CTDAC_SW)
#define CTDAC_CTDAC_SW_CLEAR(base)          (((CTDAC_V1_Type *) (base))->CTDAC_SW_CLEAR)
#define CTDAC_CTDAC_VAL(base)               (((CTDAC_V1_Type *) (base))->CTDAC_VAL)
#define CTDAC_CTDAC_VAL_NXT(base)           (((CTDAC_V1_Type *) (base))->CTDAC_VAL_NXT)
#define CTDAC_INTR(base)                    (((CTDAC_V1_Type *) (base))->INTR)
#define CTDAC_INTR_SET(base)                (((CTDAC_V1_Type *) (base))->INTR_SET)
#define CTDAC_INTR_MASK(base)               (((CTDAC_V1_Type *) (base))->INTR_MASK)
#define CTDAC_INTR_MASKED(base)             (((CTDAC_V1_Type *) (base))->INTR_MASKED)


/*******************************************************************************
*                SYSANALOG
*******************************************************************************/

#define CY_PASS_V1                          (0x20U > cy_device->passVersion)
#define CY_PASS_ADDR                        ((PASS_Type*)cy_device->passBase)
#define CY_PASS_V2_ADDR                     ((PASS_V2_Type*)cy_device->passBase)

#define CY_SAR_PASS_BASE(sarBase)           ((NULL != (sarBase)) ? ((PASS_V2_Type*) cy_device->passBase) : NULL) /* temporary solution for single pass instance */
#define CY_CTB_PASS_BASE(ctbBase)           ((NULL != (ctbBase)) ? ((PASS_V2_Type*) cy_device->passBase) : NULL) /* temporary solution for single ctb instance */
#define CY_CTB_INST(ctbBase)                ((NULL != (ctbBase)) ? 0UL : 0UL) /* temporary solution for single ctb instance */

#define PASS_AREF_AREF_CTRL                 (((PASS_V1_Type*) CY_PASS_ADDR)->AREF.AREF_CTRL)
#define PASS_INTR_CAUSE(passBase)           (((PASS_V1_Type*) (passBase))->INTR_CAUSE)

#define PASS_CTBM_CLOCK_SEL(ctbBase)        (CY_CTB_PASS_BASE(ctbBase)->CTBM_CLOCK_SEL[CY_CTB_INST(ctbBase)])

#define PASS_DPSLP_CLOCK_SEL(passBase)      (((PASS_V2_Type*) (passBase))->DPSLP_CLOCK_SEL)
#define PASS_LPOSC_CTRL(passBase)           (((PASS_V2_Type*) (passBase))->LPOSC.CTRL)
#define PASS_LPOSC_CONFIG(passBase)         (((PASS_V2_Type*) (passBase))->LPOSC.CONFIG)
#define PASS_TIMER_CTRL(passBase)           (((PASS_V2_Type*) (passBase))->TIMER.CTRL)
#define PASS_TIMER_CONFIG(passBase)         (((PASS_V2_Type*) (passBase))->TIMER.CONFIG)
#define PASS_TIMER_PERIOD(passBase)         (((PASS_V2_Type*) (passBase))->TIMER.PERIOD)

#define PASS_SAR_SIMULT_CTRL(passBase)      (((PASS_V2_Type*) (passBase))->SAR_SIMULT_CTRL)
#define PASS_SAR_TR_SCAN_CNT(passBase)      (((PASS_V2_Type*) (passBase))->SAR_TR_SCAN_CNT)
#define PASS_SAR_OVR_CTRL(passBase)         (((PASS_V2_Type*) (passBase))->SAR_OVR_CTRL)
#define PASS_SAR_SIMULT_FW_START_CTRL(passBase) (((PASS_V2_Type*) (passBase))->SAR_SIMULT_FW_START_CTRL)
#define PASS_ANA_PWR_CFG(passBase)          (((PASS_V2_Type*) (passBase))->ANA_PWR_CFG)
#define PASS_SAR_TR_OUT_CTRL(passBase)      (((PASS_V2_Type*) (passBase))->SAR_TR_OUT_CTRL)

#define PASS_SAR_DPSLP_CTRL(sarBase)        (((PASS_V2_Type*) cy_device->passBase)->SAR_DPSLP_CTRL[CY_SAR_INSTANCE(sarBase)])
#define PASS_SAR_CLOCK_SEL(sarBase)         (((PASS_V2_Type*) cy_device->passBase)->SAR_CLOCK_SEL[CY_SAR_INSTANCE(sarBase)])

#define PASS_FIFO_BASE(sarBase)             ((PASS_FIFO_V2_Type*)&(((PASS_V2_Type*)cy_device->passBase)->FIFO[CY_SAR_INSTANCE(sarBase)]))
#define PASS_FIFO_CTRL(sarBase)             (PASS_FIFO_BASE(sarBase)->CTRL)
#define PASS_FIFO_CONFIG(sarBase)           (PASS_FIFO_BASE(sarBase)->CONFIG)
#define PASS_FIFO_LEVEL(sarBase)            (PASS_FIFO_BASE(sarBase)->LEVEL)
#define PASS_FIFO_USED(sarBase)             (PASS_FIFO_BASE(sarBase)->USED)
#define PASS_FIFO_RD_DATA(sarBase)          (PASS_FIFO_BASE(sarBase)->RD_DATA)
#define PASS_FIFO_INTR(sarBase)             (PASS_FIFO_BASE(sarBase)->INTR)
#define PASS_FIFO_INTR_SET(sarBase)         (PASS_FIFO_BASE(sarBase)->INTR_SET)
#define PASS_FIFO_INTR_MASK(sarBase)        (PASS_FIFO_BASE(sarBase)->INTR_MASK)
#define PASS_FIFO_INTR_MASKED(sarBase)      (PASS_FIFO_BASE(sarBase)->INTR_MASKED)

/*******************************************************************************
*                SCB
*******************************************************************************/

#define SCB_CTRL(base)                      (((CySCB_V1_Type*) (base))->CTRL)
#define SCB_SPI_CTRL(base)                  (((CySCB_V1_Type*) (base))->SPI_CTRL)
#define SCB_SPI_STATUS(base)                (((CySCB_V1_Type*) (base))->SPI_STATUS)
#define SCB_UART_CTRL(base)                 (((CySCB_V1_Type*) (base))->UART_CTRL)
#define SCB_UART_TX_CTRL(base)              (((CySCB_V1_Type*) (base))->UART_TX_CTRL)
#define SCB_UART_RX_CTRL(base)              (((CySCB_V1_Type*) (base))->UART_RX_CTRL)
#define SCB_UART_FLOW_CTRL(base)            (((CySCB_V1_Type*) (base))->UART_FLOW_CTRL)
#define SCB_I2C_CTRL(base)                  (((CySCB_V1_Type*) (base))->I2C_CTRL)
#define SCB_I2C_STATUS(base)                (((CySCB_V1_Type*) (base))->I2C_STATUS)
#define SCB_I2C_M_CMD(base)                 (((CySCB_V1_Type*) (base))->I2C_M_CMD)
#define SCB_I2C_S_CMD(base)                 (((CySCB_V1_Type*) (base))->I2C_S_CMD)
#define SCB_I2C_CFG(base)                   (((CySCB_V1_Type*) (base))->I2C_CFG)
#define SCB_TX_CTRL(base)                   (((CySCB_V1_Type*) (base))->TX_CTRL)
#define SCB_TX_FIFO_CTRL(base)              (((CySCB_V1_Type*) (base))->TX_FIFO_CTRL)
#define SCB_TX_FIFO_STATUS(base)            (((CySCB_V1_Type*) (base))->TX_FIFO_STATUS)
#define SCB_TX_FIFO_WR(base)                (((CySCB_V1_Type*) (base))->TX_FIFO_WR)
#define SCB_RX_CTRL(base)                   (((CySCB_V1_Type*) (base))->RX_CTRL)
#define SCB_RX_FIFO_CTRL(base)              (((CySCB_V1_Type*) (base))->RX_FIFO_CTRL)
#define SCB_RX_FIFO_STATUS(base)            (((CySCB_V1_Type*) (base))->RX_FIFO_STATUS)
#define SCB_RX_MATCH(base)                  (((CySCB_V1_Type*) (base))->RX_MATCH)
#define SCB_RX_FIFO_RD(base)                (((CySCB_V1_Type*) (base))->RX_FIFO_RD)
#define SCB_INTR_CAUSE(base)                (((CySCB_V1_Type*) (base))->INTR_CAUSE)
#define SCB_INTR_I2C_EC(base)               (((CySCB_V1_Type*) (base))->INTR_I2C_EC)
#define SCB_INTR_I2C_EC_MASK(base)          (((CySCB_V1_Type*) (base))->INTR_I2C_EC_MASK)
#define SCB_INTR_I2C_EC_MASKED(base)        (((CySCB_V1_Type*) (base))->INTR_I2C_EC_MASKED)
#define SCB_INTR_SPI_EC(base)               (((CySCB_V1_Type*) (base))->INTR_SPI_EC)
#define SCB_INTR_SPI_EC_MASK(base)          (((CySCB_V1_Type*) (base))->INTR_SPI_EC_MASK)
#define SCB_INTR_SPI_EC_MASKED(base)        (((CySCB_V1_Type*) (base))->INTR_SPI_EC_MASKED)
#define SCB_INTR_M(base)                    (((CySCB_V1_Type*) (base))->INTR_M)
#define SCB_INTR_M_SET(base)                (((CySCB_V1_Type*) (base))->INTR_M_SET)
#define SCB_INTR_M_MASK(base)               (((CySCB_V1_Type*) (base))->INTR_M_MASK)
#define SCB_INTR_M_MASKED(base)             (((CySCB_V1_Type*) (base))->INTR_M_MASKED)
#define SCB_INTR_S(base)                    (((CySCB_V1_Type*) (base))->INTR_S)
#define SCB_INTR_S_SET(base)                (((CySCB_V1_Type*) (base))->INTR_S_SET)
#define SCB_INTR_S_MASK(base)               (((CySCB_V1_Type*) (base))->INTR_S_MASK)
#define SCB_INTR_S_MASKED(base)             (((CySCB_V1_Type*) (base))->INTR_S_MASKED)
#define SCB_INTR_TX(base)                   (((CySCB_V1_Type*) (base))->INTR_TX)
#define SCB_INTR_TX_SET(base)               (((CySCB_V1_Type*) (base))->INTR_TX_SET)
#define SCB_INTR_TX_MASK(base)              (((CySCB_V1_Type*) (base))->INTR_TX_MASK)
#define SCB_INTR_TX_MASKED(base)            (((CySCB_V1_Type*) (base))->INTR_TX_MASKED)
#define SCB_INTR_RX(base)                   (((CySCB_V1_Type*) (base))->INTR_RX)
#define SCB_INTR_RX_SET(base)               (((CySCB_V1_Type*) (base))->INTR_RX_SET)
#define SCB_INTR_RX_MASK(base)              (((CySCB_V1_Type*) (base))->INTR_RX_MASK)
#define SCB_INTR_RX_MASKED(base)            (((CySCB_V1_Type*) (base))->INTR_RX_MASKED)


/*******************************************************************************
*                PROFILE
*******************************************************************************/

#define CY_EP_MONITOR_COUNT                 ((uint32_t)(cy_device->epMonitorNr))
#define CY_EP_CNT_NR                        (8UL)
#define PROFILE_CTL                         (((PROFILE_V1_Type*) PROFILE_BASE)->CTL)
#define PROFILE_STATUS                      (((PROFILE_V1_Type*) PROFILE_BASE)->STATUS)
#define PROFILE_CMD                         (((PROFILE_V1_Type*) PROFILE_BASE)->CMD)
#define PROFILE_INTR                        (((PROFILE_V1_Type*) PROFILE_BASE)->INTR)
#define PROFILE_INTR_MASK                   (((PROFILE_V1_Type*) PROFILE_BASE)->INTR_MASK)
#define PROFILE_INTR_MASKED                 (((PROFILE_V1_Type*) PROFILE_BASE)->INTR_MASKED)
#define PROFILE_CNT_STRUCT                  (((PROFILE_V1_Type*) PROFILE_BASE)->CNT_STRUCT)


/*******************************************************************************
*                BLE
*******************************************************************************/

#define BLE_RCB_INTR                        (((BLE_V1_Type *) BLE_BASE)->RCB.INTR)
#define BLE_RCB_TX_FIFO_WR                  (((BLE_V1_Type *) BLE_BASE)->RCB.TX_FIFO_WR)
#define BLE_RCB_RX_FIFO_RD                  (((BLE_V1_Type *) BLE_BASE)->RCB.RX_FIFO_RD)
#define BLE_RCB_CTRL                        (((BLE_V1_Type *) BLE_BASE)->RCB.CTRL)
#define BLE_RCB_RCBLL_CTRL                  (((BLE_V1_Type *) BLE_BASE)->RCB.RCBLL.CTRL)
#define BLE_BLESS_XTAL_CLK_DIV_CONFIG       (((BLE_V1_Type *) BLE_BASE)->BLESS.XTAL_CLK_DIV_CONFIG)
#define BLE_BLESS_MT_CFG                    (((BLE_V1_Type *) BLE_BASE)->BLESS.MT_CFG)
#define BLE_BLESS_MT_STATUS                 (((BLE_V1_Type *) BLE_BASE)->BLESS.MT_STATUS)
#define BLE_BLESS_MT_DELAY_CFG              (((BLE_V1_Type *) BLE_BASE)->BLESS.MT_DELAY_CFG)
#define BLE_BLESS_MT_DELAY_CFG2             (((BLE_V1_Type *) BLE_BASE)->BLESS.MT_DELAY_CFG2)
#define BLE_BLESS_MT_DELAY_CFG3             (((BLE_V1_Type *) BLE_BASE)->BLESS.MT_DELAY_CFG3)
#define BLE_BLESS_MT_VIO_CTRL               (((BLE_V1_Type *) BLE_BASE)->BLESS.MT_VIO_CTRL)
#define BLE_BLESS_LL_CLK_EN                 (((BLE_V1_Type *) BLE_BASE)->BLESS.LL_CLK_EN)
#define BLE_BLESS_MISC_EN_CTRL              (((BLE_V1_Type *) BLE_BASE)->BLESS.MISC_EN_CTRL)
#define BLE_BLESS_INTR_STAT                 (((BLE_V1_Type *) BLE_BASE)->BLESS.INTR_STAT)
#define BLE_BLELL_EVENT_INTR                (((BLE_V1_Type *) BLE_BASE)->BLELL.EVENT_INTR)
#define BLE_BLELL_CONN_INTR                 (((BLE_V1_Type *) BLE_BASE)->BLELL.CONN_INTR)
#define BLE_BLELL_CONN_EXT_INTR             (((BLE_V1_Type *) BLE_BASE)->BLELL.CONN_EXT_INTR)
#define BLE_BLELL_SCAN_INTR                 (((BLE_V1_Type *) BLE_BASE)->BLELL.SCAN_INTR)
#define BLE_BLELL_ADV_INTR                  (((BLE_V1_Type *) BLE_BASE)->BLELL.ADV_INTR)


/*******************************************************************************
*                USBFS Device
*******************************************************************************/

#define USBFS_DEV_CR0(base)             (((USBFS_V1_Type *)(base))->USBDEV.CR0)
#define USBFS_DEV_CR1(base)             (((USBFS_V1_Type *)(base))->USBDEV.CR1)
#define USBFS_DEV_USBIO_CR0(base)       (((USBFS_V1_Type *)(base))->USBDEV.USBIO_CR0)
#define USBFS_DEV_USBIO_CR2(base)       (((USBFS_V1_Type *)(base))->USBDEV.USBIO_CR2)
#define USBFS_DEV_USBIO_CR1(base)       (((USBFS_V1_Type *)(base))->USBDEV.USBIO_CR1)
#define USBFS_DEV_USB_CLK_EN(base)      (((USBFS_V1_Type *)(base))->USBDEV.USB_CLK_EN)
#define USBFS_DEV_BUS_RST_CNT(base)     (((USBFS_V1_Type *)(base))->USBDEV.BUS_RST_CNT)
#define USBFS_DEV_OSCLK_DR0(base)       (((USBFS_V1_Type *)(base))->USBDEV.EP_TYPE)
#define USBFS_DEV_OSCLK_DR1(base)       (((USBFS_V1_Type *)(base))->USBDEV.OSCLK_DR0)
#define USBFS_DEV_SOF0(base)            (((USBFS_V1_Type *)(base))->USBDEV.SOF0)
#define USBFS_DEV_SOF1(base)            (((USBFS_V1_Type *)(base))->USBDEV.SOF1)
#define USBFS_DEV_SOF16(base)           (((USBFS_V1_Type *)(base))->USBDEV.OSCLK_DR1)
#define USBFS_DEV_OSCLK_DR16(base)      (((USBFS_V1_Type *)(base))->USBDEV.SOF16)
#define USBFS_DEV_ARB_CFG(base)         (((USBFS_V1_Type *)(base))->USBDEV.ARB_CFG)
#define USBFS_DEV_DYN_RECONFIG(base)    (((USBFS_V1_Type *)(base))->USBDEV.DYN_RECONFIG)
#define USBFS_DEV_BUF_SIZE(base)        (((USBFS_V1_Type *)(base))->USBDEV.BUF_SIZE)
#define USBFS_DEV_EP_ACTIVE(base)       (((USBFS_V1_Type *)(base))->USBDEV.EP_ACTIVE)
#define USBFS_DEV_EP_TYPE(base)         (((USBFS_V1_Type *)(base))->USBDEV.EP_TYPE)
#define USBFS_DEV_CWA16(base)           (((USBFS_V1_Type *)(base))->USBDEV.CWA16)
#define USBFS_DEV_CWA(base)             (((USBFS_V1_Type *)(base))->USBDEV.CWA)
#define USBFS_DEV_CWA_MSB(base)         (((USBFS_V1_Type *)(base))->USBDEV.CWA_MSB)
#define USBFS_DEV_DMA_THRES16(base)     (((USBFS_V1_Type *)(base))->USBDEV.DMA_THRES16)
#define USBFS_DEV_DMA_THRES(base)       (((USBFS_V1_Type *)(base))->USBDEV.DMA_THRES)
#define USBFS_DEV_DMA_THRES_MSB(base)   (((USBFS_V1_Type *)(base))->USBDEV.DMA_THRES_MSB)

#define USBFS_DEV_SIE_EP_INT_EN(base)   (((USBFS_V1_Type *)(base))->USBDEV.SIE_EP_INT_EN)
#define USBFS_DEV_SIE_EP_INT_SR(base)   (((USBFS_V1_Type *)(base))->USBDEV.SIE_EP_INT_SR)
#define USBFS_DEV_ARB_INT_EN(base)      (((USBFS_V1_Type *)(base))->USBDEV.ARB_INT_EN)
#define USBFS_DEV_ARB_INT_SR(base)      (((USBFS_V1_Type *)(base))->USBDEV.ARB_INT_SR)

#define USBFS_DEV_EP0_CR(base)          (((USBFS_V1_Type *)(base))->USBDEV.EP0_CR)
#define USBFS_DEV_EP0_CNT(base)         (((USBFS_V1_Type *)(base))->USBDEV.EP0_CNT)
#define USBFS_DEV_EP0_DR(base, idx)     (((USBFS_V1_Type *)(base))->USBDEV.EP0_DR[idx])

#define USBFS_DEV_MEM_DATA(base, idx)   (((USBFS_V1_Type *)(base))->USBDEV.MEM[idx])

#define USBFS_DEV_SIE_REGS_BASE        (0x30U)
#define USBFS_DEV_SIE_REGS_SIZE        (0x40U)
#define USBFS_DEV_SIE_EP_CNT0_OFFSET   (0x00U)
#define USBFS_DEV_SIE_EP_CNT1_OFFSET   (0x04U)
#define USBFS_DEV_SIE_EP_CR0_OFFSET    (0x08U)
#define USBFS_DEV_SIE_REGS(base, endpoint) ((uint32_t)(base) + USBFS_DEV_SIE_REGS_BASE + ((endpoint) * USBFS_DEV_SIE_REGS_SIZE))

#define USBFS_DEV_SIE_EP_CNT0(base, endpoint)  (*(volatile uint32_t *) (USBFS_DEV_SIE_REGS(base, endpoint) + \
                                                                        USBFS_DEV_SIE_EP_CNT0_OFFSET))
#define USBFS_DEV_SIE_EP_CNT1(base, endpoint)  (*(volatile uint32_t *) (USBFS_DEV_SIE_REGS(base, endpoint) + \
                                                                        USBFS_DEV_SIE_EP_CNT1_OFFSET))
#define USBFS_DEV_SIE_EP_CR0(base, endpoint)   (*(volatile uint32_t *) (USBFS_DEV_SIE_REGS(base, endpoint) + \
                                                                        USBFS_DEV_SIE_EP_CR0_OFFSET))

#define USBFS_DEV_ARB_REGS_BASE         (0x200U)
#define USBFS_DEV_ARB_REGS_SIZE         (0x40U)
#define USBFS_DEV_ARB_EP_CFG_OFFSET     (0x00U)
#define USBFS_DEV_ARB_EP_INT_EN_OFFSET  (0x04U)
#define USBFS_DEV_ARB_EP_SR_OFFSET      (0x08U)
#define USBFS_DEV_ARB_RW_WA_OFFSET      (0x10U)
#define USBFS_DEV_ARB_RW_WA_MSB_OFFSET  (0x14U)
#define USBFS_DEV_ARB_RW_RA_OFFSET      (0x18U)
#define USBFS_DEV_ARB_RW_RA_MSB_OFFSET  (0x1CU)
#define USBFS_DEV_ARB_RW_DR_OFFSET      (0x20U)
#define USBFS_DEV_ARB_REGS(base, endpoint) ((uint32_t)(base) + USBFS_DEV_ARB_REGS_BASE + ((endpoint) * USBFS_DEV_ARB_REGS_SIZE))

#define USBFS_DEV_ARB_EP_CFG(base, endpoint)       (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_EP_CFG_OFFSET))
#define USBFS_DEV_ARB_EP_INT_EN(base, endpoint)    (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_EP_INT_EN_OFFSET))
#define USBFS_DEV_ARB_EP_SR(base, endpoint)        (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_EP_SR_OFFSET))
#define USBFS_DEV_ARB_RW_WA(base, endpoint)        (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_WA_OFFSET))
#define USBFS_DEV_ARB_RW_WA_MSB(base, endpoint)    (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_WA_MSB_OFFSET))
#define USBFS_DEV_ARB_RW_RA(base, endpoint)        (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_RA_OFFSET))
#define USBFS_DEV_ARB_RW_RA_MSB(base, endpoint)    (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_RA_MSB_OFFSET))
#define USBFS_DEV_ARB_RW_DR(base, endpoint)        (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_DR_OFFSET))

#define USBFS_DEV_ARB_REGS16_BASE       (0x1210U)
#define USBFS_DEV_ARB_REGS16_SIZE       (0x40U)
#define USBFS_DEV_ARB_RW_WA16_OFFSET    (0x00U)
#define USBFS_DEV_ARB_RW_RA16_OFFSET    (0x08U)
#define USBFS_DEV_ARB_RW_DR16_OFFSET    (0x10U)
#define USBFS_DEV_ARB_REGS_16(base, endpoint) ((uint32_t)(base) + USBFS_DEV_ARB_REGS16_BASE + ((endpoint) * USBFS_DEV_ARB_REGS16_SIZE))

#define USBFS_DEV_ARB_RW_WA16(base, endpoint)      (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS_16(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_WA16_OFFSET))
#define USBFS_DEV_ARB_RW_RA16(base, endpoint)      (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS_16(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_RA16_OFFSET))
#define USBFS_DEV_ARB_RW_DR16(base, endpoint)      (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS_16(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_DR16_OFFSET))

#define USBFS_DEV_LPM_POWER_CTL(base)       (((USBFS_V1_Type *)(base))->USBLPM.POWER_CTL)
#define USBFS_DEV_LPM_USBIO_CTL(base)       (((USBFS_V1_Type *)(base))->USBLPM.USBIO_CTL)
#define USBFS_DEV_LPM_FLOW_CTL(base)        (((USBFS_V1_Type *)(base))->USBLPM.FLOW_CTL)
#define USBFS_DEV_LPM_LPM_CTL(base)         (((USBFS_V1_Type *)(base))->USBLPM.LPM_CTL)
#define USBFS_DEV_LPM_LPM_STAT(base)        (((USBFS_V1_Type const *)(base))->USBLPM.LPM_STAT)
#define USBFS_DEV_LPM_INTR_SIE(base)        (((USBFS_V1_Type *)(base))->USBLPM.INTR_SIE)
#define USBFS_DEV_LPM_INTR_SIE_SET(base)    (((USBFS_V1_Type *)(base))->USBLPM.INTR_SIE_SET)
#define USBFS_DEV_LPM_INTR_SIE_MASK(base)   (((USBFS_V1_Type *)(base))->USBLPM.INTR_SIE_MASK)
#define USBFS_DEV_LPM_INTR_SIE_MASKED(base) (((USBFS_V1_Type *)(base))->USBLPM.INTR_SIE_MASKED)
#define USBFS_DEV_LPM_INTR_LVL_SEL(base)    (((USBFS_V1_Type *)(base))->USBLPM.INTR_LVL_SEL)
#define USBFS_DEV_LPM_INTR_CAUSE_HI(base)   (((USBFS_V1_Type const *)(base))->USBLPM.INTR_CAUSE_HI)
#define USBFS_DEV_LPM_INTR_CAUSE_MED(base)  (((USBFS_V1_Type const *)(base))->USBLPM.INTR_CAUSE_MED)
#define USBFS_DEV_LPM_INTR_CAUSE_LO(base)   (((USBFS_V1_Type const *)(base))->USBLPM.INTR_CAUSE_LO)
#define USBFS_DEV_LPM_DFT_CTL(base)         (((USBFS_V1_Type *)(base))->USBLPM.DFT_CTL)

#define USBFS_HOST_CTL0(base)               (((USBFS_V1_Type *)(base))->USBHOST.HOST_CTL0)
#define USBFS_HOST_CTL1(base)               (((USBFS_V1_Type *)(base))->USBHOST.HOST_CTL1)
#define USBFS_HOST_CTL2(base)               (((USBFS_V1_Type *)(base))->USBHOST.HOST_CTL2)
#define USBFS_HOST_ERR(base)                (((USBFS_V1_Type *)(base))->USBHOST.HOST_ERR)
#define USBFS_HOST_STATUS(base)             (((USBFS_V1_Type *)(base))->USBHOST.HOST_STATUS)
#define USBFS_HOST_FCOMP(base)              (((USBFS_V1_Type *)(base))->USBHOST.HOST_FCOMP)
#define USBFS_HOST_RTIMER(base)             (((USBFS_V1_Type *)(base))->USBHOST.HOST_RTIMER)
#define USBFS_HOST_ADDR(base)               (((USBFS_V1_Type *)(base))->USBHOST.HOST_ADDR)
#define USBFS_HOST_EOF(base)                (((USBFS_V1_Type *)(base))->USBHOST.HOST_EOF)
#define USBFS_HOST_FRAME(base)              (((USBFS_V1_Type *)(base))->USBHOST.HOST_FRAME)
#define USBFS_HOST_TOKEN(base)              (((USBFS_V1_Type *)(base))->USBHOST.HOST_TOKEN)
#define USBFS_HOST_EP1_CTL(base)            (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP1_CTL)
#define USBFS_HOST_EP1_STATUS(base)         (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP1_STATUS)
#define USBFS_HOST_EP1_RW1_DR(base)         (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP1_RW1_DR)
#define USBFS_HOST_EP1_RW2_DR(base)         (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP1_RW2_DR)
#define USBFS_HOST_EP2_CTL(base)            (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP2_CTL)
#define USBFS_HOST_EP2_STATUS(base)         (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP2_STATUS)
#define USBFS_HOST_EP2_RW1_DR(base)         (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP2_RW1_DR)
#define USBFS_HOST_EP2_RW2_DR(base)         (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP2_RW2_DR)
#define USBFS_HOST_LVL1_SEL(base)           (((USBFS_V1_Type *)(base))->USBHOST.HOST_LVL1_SEL)
#define USBFS_HOST_LVL2_SEL(base)           (((USBFS_V1_Type *)(base))->USBHOST.HOST_LVL2_SEL)
#define USBFS_INTR_USBHOST_CAUSE_HI(base)   (((USBFS_V1_Type *)(base))->USBHOST.INTR_USBHOST_CAUSE_HI)
#define USBFS_INTR_USBHOST_CAUSE_MED(base)  (((USBFS_V1_Type *)(base))->USBHOST.INTR_USBHOST_CAUSE_MED)
#define USBFS_INTR_USBHOST_CAUSE_LO(base)   (((USBFS_V1_Type *)(base))->USBHOST.INTR_USBHOST_CAUSE_LO)
#define USBFS_INTR_HOST_EP_CAUSE_HI(base)   (((USBFS_V1_Type *)(base))->USBHOST.INTR_HOST_EP_CAUSE_HI)
#define USBFS_INTR_HOST_EP_CAUSE_MED(base)  (((USBFS_V1_Type *)(base))->USBHOST.INTR_HOST_EP_CAUSE_MED)
#define USBFS_INTR_HOST_EP_CAUSE_LO(base)   (((USBFS_V1_Type *)(base))->USBHOST.INTR_HOST_EP_CAUSE_LO)
#define USBFS_INTR_USBHOST(base)            (((USBFS_V1_Type *)(base))->USBHOST.INTR_USBHOST)
#define USBFS_INTR_USBHOST_SET(base)        (((USBFS_V1_Type *)(base))->USBHOST.INTR_USBHOST_SET)
#define USBFS_INTR_USBHOST_MASK(base)       (((USBFS_V1_Type *)(base))->USBHOST.INTR_USBHOST_MASK)
#define USBFS_INTR_USBHOST_MASKED(base)     (((USBFS_V1_Type *)(base))->USBHOST.INTR_USBHOST_MASKED)
#define USBFS_INTR_HOST_EP(base)            (((USBFS_V1_Type *)(base))->USBHOST.INTR_HOST_EP)
#define USBFS_INTR_HOST_EP_SET(base)        (((USBFS_V1_Type *)(base))->USBHOST.INTR_HOST_EP_SET)
#define USBFS_INTR_HOST_EP_MASK(base)       (((USBFS_V1_Type *)(base))->USBHOST.INTR_HOST_EP_MASK)
#define USBFS_INTR_HOST_EP_MASKED(base)     (((USBFS_V1_Type *)(base))->USBHOST.INTR_HOST_EP_MASKED)
#define USBFS_HOST_DMA_ENBL(base)           (((USBFS_V1_Type *)(base))->USBHOST.HOST_DMA_ENBL)
#define USBFS_HOST_EP1_BLK(base)            (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP1_BLK)
#define USBFS_HOST_EP2_BLK(base)            (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP2_BLK)

#endif /* CY_DEVICE_H_ */

/* [] END OF FILE */
