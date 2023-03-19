/**
  ******************************************************************************
  * @file    bl702_pds.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __BL702_PDS_H__
#define __BL702_PDS_H__

#include "pds_reg.h"
#include "bl702_ef_ctrl.h"
#include "bl702_aon.h"
#include "bl702_hbn.h"
#include "bl702_common.h"
#include "bflb_sflash.h"

/** @addtogroup  BL702_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PDS
 *  @{
 */

/** @defgroup  PDS_Public_Types
 *  @{
 */

/**
 *  @brief PDS LDO level type definition
 */
typedef enum {
    PDS_LDO_LEVEL_0P60V = 0,  /*!< PDS LDO voltage 0.60V */
    PDS_LDO_LEVEL_0P65V = 1,  /*!< PDS LDO voltage 0.65V */
    PDS_LDO_LEVEL_0P70V = 2,  /*!< PDS LDO voltage 0.70V */
    PDS_LDO_LEVEL_0P75V = 3,  /*!< PDS LDO voltage 0.75V */
    PDS_LDO_LEVEL_0P80V = 4,  /*!< PDS LDO voltage 0.80V */
    PDS_LDO_LEVEL_0P85V = 5,  /*!< PDS LDO voltage 0.85V */
    PDS_LDO_LEVEL_0P90V = 6,  /*!< PDS LDO voltage 0.90V */
    PDS_LDO_LEVEL_0P95V = 7,  /*!< PDS LDO voltage 0.95V */
    PDS_LDO_LEVEL_1P00V = 8,  /*!< PDS LDO voltage 1.00V */
    PDS_LDO_LEVEL_1P05V = 9,  /*!< PDS LDO voltage 1.05V */
    PDS_LDO_LEVEL_1P10V = 10, /*!< PDS LDO voltage 1.10V */
    PDS_LDO_LEVEL_1P15V = 11, /*!< PDS LDO voltage 1.15V */
    PDS_LDO_LEVEL_1P20V = 12, /*!< PDS LDO voltage 1.20V */
    PDS_LDO_LEVEL_1P25V = 13, /*!< PDS LDO voltage 1.25V */
    PDS_LDO_LEVEL_1P30V = 14, /*!< PDS LDO voltage 1.30V */
    PDS_LDO_LEVEL_1P35V = 15, /*!< PDS LDO voltage 1.35V */
} PDS_LDO_LEVEL_Type;

/**
 *  @brief PDS RAM configuration type definition
 */
typedef struct
{
    uint32_t PDS_RAM_CFG_0KB_16KB_CPU_RAM_RET1N  : 1;  /*!< [0] 0~16KB cpu_ram RET1N */
    uint32_t PDS_RAM_CFG_16KB_32KB_CPU_RAM_RET1N : 1;  /*!< [1] 16~32KB cpu_ram RET1N */
    uint32_t PDS_RAM_CFG_32KB_48KB_CPU_RAM_RET1N : 1;  /*!< [2] 32~48KB cpu_ram RET1N */
    uint32_t PDS_RAM_CFG_48KB_64KB_CPU_RAM_RET1N : 1;  /*!< [3] 48~64KB cpu_ram RET1N */
    uint32_t PDS_RAM_CFG_0KB_16KB_CPU_RAM_RET2N  : 1;  /*!< [4] 0~16KB cpu_ram RET2N */
    uint32_t PDS_RAM_CFG_16KB_32KB_CPU_RAM_RET2N : 1;  /*!< [5] 16~32KB cpu_ram RET2N */
    uint32_t PDS_RAM_CFG_32KB_48KB_CPU_RAM_RET2N : 1;  /*!< [6] 32~48KB cpu_ram RET2N */
    uint32_t PDS_RAM_CFG_48KB_64KB_CPU_RAM_RET2N : 1;  /*!< [7] 48~64KB cpu_ram RET2N */
    uint32_t PDS_RAM_CFG_0KB_16KB_CPU_RAM_PGEN   : 1;  /*!< [8] 0~16KB cpu_ram PGEN */
    uint32_t PDS_RAM_CFG_16KB_32KB_CPU_RAM_PGEN  : 1;  /*!< [9] 16~32KB cpu_ram PGEN */
    uint32_t PDS_RAM_CFG_32KB_48KB_CPU_RAM_PGEN  : 1;  /*!< [10] 32~48KB cpu_ram PGEN */
    uint32_t PDS_RAM_CFG_48KB_64KB_CPU_RAM_PGEN  : 1;  /*!< [11] 48~64KB cpu_ram PGEN */
    uint32_t PDS_RAM_CFG_RSV                     : 20; /*!< [31:12]reserve */
} PDS_RAM_CFG_Type;

/**
 *  @brief PDS PAD pin configuration type definition
 */
typedef enum {
    PDS_PAD_PIN_GPIO_17, /*!< PAD GPIO 17 */
    PDS_PAD_PIN_GPIO_18, /*!< PAD GPIO 18 */
    PDS_PAD_PIN_GPIO_19, /*!< PAD GPIO 19 */
    PDS_PAD_PIN_GPIO_20, /*!< PAD GPIO 20 */
    PDS_PAD_PIN_GPIO_21, /*!< PAD GPIO 21 */
    PDS_PAD_PIN_GPIO_22, /*!< PAD GPIO 22 */
    PDS_PAD_PIN_GPIO_23, /*!< PAD GPIO 23 */
    PDS_PAD_PIN_GPIO_24, /*!< PAD GPIO 24 */
    PDS_PAD_PIN_GPIO_25, /*!< PAD GPIO 25 */
    PDS_PAD_PIN_GPIO_26, /*!< PAD GPIO 26 */
    PDS_PAD_PIN_GPIO_27, /*!< PAD GPIO 27 */
    PDS_PAD_PIN_GPIO_28, /*!< PAD GPIO 28 */
} PDS_PAD_PIN_Type;

/**
 *  @brief PDS PAD configuration type definition
 */
typedef enum {
    PDS_PAD_CFG_PULL_NONE, /*!< no PD/PU/IE on PAD */
    PDS_PAD_CFG_PULL_DOWN, /*!< Pulldown PAD */
    PDS_PAD_CFG_PULL_UP,   /*!< Pullup PAD */
    PDS_PAD_CFG_ACTIVE_IE, /*!< Active IE */
} PDS_PAD_CFG_Type;

/**
 *  @brief PDS configuration type definition
 */
typedef struct
{
    uint32_t pdsStart                : 1; /*!< [0]PDS Start */
    uint32_t sleepForever            : 1; /*!< [1]PDS sleep forever */
    uint32_t xtalForceOff            : 1; /*!< [2]Power off xtal force */
    uint32_t saveWifiState           : 1; /*!< [3]Save WIFI State Before Enter PDS */
    uint32_t dcdc18Off               : 1; /*!< [4]power down dcdc18 during PDS */
    uint32_t bgSysOff                : 1; /*!< [5]power down bg_sys during PDS */
    uint32_t gpioIePuPd              : 1; /*!< [6]allow PDS Control the GPIO IE/PU/PD at Sleep Mode */
    uint32_t puFlash                 : 1; /*!< [7]turn off Flash Power During PDS */
    uint32_t clkOff                  : 1; /*!< [8]gate clock during PDS (each pwr domain has its own control) */
    uint32_t memStby                 : 1; /*!< [9]mem_stby during PDS (each power domain can has its own control) */
    uint32_t swPuFlash               : 1; /*!< [10]SW Turn on Flash */
    uint32_t isolation               : 1; /*!< [11]Isolation during PDS (each power domain can has its own control) */
    uint32_t waitXtalRdy             : 1; /*!< [12]wait XTAL Ready during before PDS Interrupt */
    uint32_t pdsPwrOff               : 1; /*!< [13]Power off during PDS (each power domain can has its own control) */
    uint32_t xtalOff                 : 1; /*!< [14]xtal power down during PDS */
    uint32_t socEnbForceOn           : 1; /*!< [15]pds_soc_enb always active */
    uint32_t pdsRstSocEn             : 1; /*!< [16]pds_rst controlled by PDS */
    uint32_t pdsRC32mOn              : 1; /*!< [17]RC32M always on or RC32M on/off controlled by PDS state */
    uint32_t pdsLdoVselEn            : 1; /*!< [18]PDS "SLEEP" control LDO voltage enable */
    uint32_t pdsRamLowPowerWithClkEn : 1; /*!< [19]Control SRAM Low Power with CLK (Sync) */
    uint32_t reserved20              : 1; /*!< [20]Reserved */
    uint32_t cpu0WfiMask             : 1; /*!< [21]pds start condition mask np_wfi */
    uint32_t ldo11Off                : 1; /*!< [22]power down ldo11 during PDS */
    uint32_t pdsForceRamClkEn        : 1; /*!< [23]Force SRAM CLK Enable */
    uint32_t pdsLdoVol               : 4; /*!< [27:24]LDO voltage value in PDS mode */
    uint32_t pdsCtlRfSel             : 2; /*!< [29:28]select the way RF controlled by PDS */
    uint32_t pdsCtlPllSel            : 2; /*!< [31:30]select the way PLL controlled by PDS */
} PDS_CFG_Type;

/**
 *  @brief PDS configuration type definition
 */
typedef struct
{
    uint32_t pdsStart                : 1; /*!< [0]PDS Start */
    uint32_t sleepForever            : 1; /*!< [1]PDS sleep forever */
    uint32_t xtalForceOff            : 1; /*!< [2]Power off xtal force */
    uint32_t saveWifiState           : 1; /*!< [3]Save WIFI State Before Enter PDS */
    uint32_t dcdc18Off               : 1; /*!< [4]power down dcdc18 during PDS */
    uint32_t bgSysOff                : 1; /*!< [5]power down bg_sys during PDS */
    uint32_t gpioIePuPd              : 1; /*!< [6]allow PDS Control the GPIO IE/PU/PD at Sleep Mode */
    uint32_t puFlash                 : 1; /*!< [7]turn off Flash Power During PDS */
    uint32_t clkOff                  : 1; /*!< [8]gate clock during PDS (each pwr domain has its own control) */
    uint32_t memStby                 : 1; /*!< [9]mem_stby during PDS (each power domain can has its own control) */
    uint32_t swPuFlash               : 1; /*!< [10]SW Turn on Flash */
    uint32_t isolation               : 1; /*!< [11]Isolation during PDS (each power domain can has its own control) */
    uint32_t waitXtalRdy             : 1; /*!< [12]wait XTAL Ready during before PDS Interrupt */
    uint32_t pdsPwrOff               : 1; /*!< [13]Power off during PDS (each power domain can has its own control) */
    uint32_t xtalOff                 : 1; /*!< [14]xtal power down during PDS */
    uint32_t socEnbForceOn           : 1; /*!< [15]pds_soc_enb always active */
    uint32_t pdsRstSocEn             : 1; /*!< [16]pds_rst controlled by PDS */
    uint32_t pdsRC32mOn              : 1; /*!< [17]RC32M always on or RC32M on/off controlled by PDS state */
    uint32_t pdsLdoVselEn            : 1; /*!< [18]PDS "SLEEP" control LDO voltage enable */
    uint32_t pdsRamLowPowerWithClkEn : 1; /*!< [19]Control SRAM Low Power with CLK (Sync) */
    uint32_t reserved20              : 1; /*!< [20]Reserved */
    uint32_t cpu0WfiMask             : 1; /*!< [21]pds start condition mask np_wfi */
    uint32_t ldo11Off                : 1; /*!< [22]power down ldo11 during PDS */
    uint32_t pdsForceRamClkEn        : 1; /*!< [23]Force SRAM CLK Enable */
    uint32_t pdsLdoVol               : 4; /*!< [27:24]LDO voltage value in PDS mode */
    uint32_t pdsCtlRfSel             : 2; /*!< [29:28]select the way RF controlled by PDS */
    uint32_t pdsCtlPllSel            : 2; /*!< [31:30]select the way PLL controlled by PDS */
} PDS_CTL_Type;

/**
 *  @brief PDS force configuration type definition
 */
typedef struct
{
    uint32_t forceCpuPwrOff  : 1;  /*!< [0]manual force NP power off */
    uint32_t rsv1            : 1;  /*!< [1]reserve */
    uint32_t forceBzPwrOff   : 1;  /*!< [2]manual force BZ power off */
    uint32_t forceUsbPwrOff  : 1;  /*!< [3]manual force USB power off */
    uint32_t forceCpuIsoEn   : 1;  /*!< [4]manual force NP isolation */
    uint32_t rsv5            : 1;  /*!< [5]reserve */
    uint32_t forceBzIsoEn    : 1;  /*!< [6]manual force BZ isolation */
    uint32_t forceUsbIsoEn   : 1;  /*!< [7]manual force USB isolation */
    uint32_t forceCpuPdsRst  : 1;  /*!< [8]manual force NP pds reset */
    uint32_t rsv9            : 1;  /*!< [9]reserve */
    uint32_t forceBzPdsRst   : 1;  /*!< [10]manual force BZ pds reset */
    uint32_t forceUsbPdsRst  : 1;  /*!< [11]manual force USB pds reset */
    uint32_t forceCpuMemStby : 1;  /*!< [12]manual force NP memory sleep */
    uint32_t rsv13           : 1;  /*!< [13]reserve */
    uint32_t forceBzMemStby  : 1;  /*!< [14]manual force BZ memory sleep */
    uint32_t forceUsbMemStby : 1;  /*!< [15]manual force USB memory sleep */
    uint32_t forceCpuGateClk : 1;  /*!< [16]manual force NP clock gated */
    uint32_t rsv17           : 1;  /*!< [17]reserve */
    uint32_t forceBzGateClk  : 1;  /*!< [18]manual force BZ clock gated */
    uint32_t forceUsbGateClk : 1;  /*!< [19]manual force USB clock gated */
    uint32_t rsv20_31        : 12; /*!< [31:20]reserve */
} PDS_CTL2_Type;

/**
 *  @brief PDS force configuration type definition
 */
typedef struct
{
    uint32_t rsv0             : 1; /*!< [0]reserve */
    uint32_t forceMiscPwrOff  : 1; /*!< [1]manual force MISC pwr_off */
    uint32_t forceBlePwrOff   : 1; /*!< [2]manual force BZ_BLE pwr_off */
    uint32_t rsv3_4           : 2; /*!< [4:3]reserve */
    uint32_t forceBleIsoEn    : 1; /*!< [5]manual force BZ_BLE iso_en */
    uint32_t rsv6             : 1; /*!< [6]reserve */
    uint32_t forceMiscPdsRst  : 1; /*!< [7]manual force MISC pds_rst */
    uint32_t forceBlePdsRst   : 1; /*!< [8]manual force BZ_BLE pds_rst */
    uint32_t rsv9             : 1; /*!< [9]reserve */
    uint32_t forceMiscMemStby : 1; /*!< [10]manual force MISC mem_stby */
    uint32_t forceBleMemStby  : 1; /*!< [11]manual force BZ_BLE mem_stby */
    uint32_t rsv12            : 1; /*!< [12]reserve */
    uint32_t forceMiscGateClk : 1; /*!< [13]manual force MISC gate_clk */
    uint32_t forceBleGateClk  : 1; /*!< [14]manual force BZ_BLE gate_clk */
    uint32_t rsv15_23         : 9; /*!< [23:15]reserve */
    uint32_t CpuIsoEn         : 1; /*!< [24]make NP isolated at PDS Sleep state */
    uint32_t rsv25_26         : 2; /*!< [26:25]reserve */
    uint32_t BzIsoEn          : 1; /*!< [27]make BZ isolated at PDS Sleep state */
    uint32_t BleIsoEn         : 1; /*!< [28]make Ble isolated at PDS Sleep state */
    uint32_t UsbIsoEn         : 1; /*!< [29]make USB isolated at PDS Sleep state */
    uint32_t MiscIsoEn        : 1; /*!< [30]make misc isolated at PDS Sleep state */
    uint32_t rsv31            : 1; /*!< [31]reserve */
} PDS_CTL3_Type;

/**
 *  @brief PDS force configuration type definition
 */
typedef struct
{
    uint32_t cpuPwrOff     : 1; /*!< [0] */
    uint32_t cpuRst        : 1; /*!< [1] */
    uint32_t cpuMemStby    : 1; /*!< [2] */
    uint32_t cpuGateClk    : 1; /*!< [3] */
    uint32_t rsv4_11       : 8; /*!< [11:4]reserve */
    uint32_t BzPwrOff      : 1; /*!< [12] */
    uint32_t BzRst         : 1; /*!< [13] */
    uint32_t BzMemStby     : 1; /*!< [14] */
    uint32_t BzGateClk     : 1; /*!< [15] */
    uint32_t BlePwrOff     : 1; /*!< [16] */
    uint32_t BleRst        : 1; /*!< [17] */
    uint32_t BleMemStby    : 1; /*!< [18] */
    uint32_t BleGateClk    : 1; /*!< [19] */
    uint32_t UsbPwrOff     : 1; /*!< [20] */
    uint32_t UsbRst        : 1; /*!< [21] */
    uint32_t UsbMemStby    : 1; /*!< [22] */
    uint32_t UsbGateClk    : 1; /*!< [23] */
    uint32_t MiscPwrOff    : 1; /*!< [24] */
    uint32_t MiscRst       : 1; /*!< [25] */
    uint32_t MiscMemStby   : 1; /*!< [26] */
    uint32_t MiscGateClk   : 1; /*!< [27] */
    uint32_t rsv28_29      : 2; /*!< [29:28]reserve */
    uint32_t MiscAnaPwrOff : 1; /*!< [30] */
    uint32_t MiscDigPwrOff : 1; /*!< [31] */
} PDS_CTL4_Type;

/**
 *  @brief PDS default level configuration type definition
 */
typedef struct
{
    PDS_CTL_Type pdsCtl;   /*!< PDS_CTL configuration */
    PDS_CTL2_Type pdsCtl2; /*!< PDS_CTL2 configuration */
    PDS_CTL3_Type pdsCtl3; /*!< PDS_CTL3 configuration */
    PDS_CTL4_Type pdsCtl4; /*!< PDS_CTL4 configuration */
} PDS_DEFAULT_LV_CFG_Type;

/**
 *  @brief PDS interrupt type definition
 */
typedef enum {
    PDS_INT_WAKEUP = 0,    /*!< PDS wakeup interrupt(assert bit while wakeup, include PDS_Timer/...) */
    PDS_INT_RF_DONE,       /*!< PDS RF done interrupt */
    PDS_INT_PLL_DONE,      /*!< PDS PLL done interrupt */
    PDS_INT_PDS_SLEEP_CNT, /*!< wakeup trigger by pds_sleep_cnt=0 */
    PDS_INT_HBN_IRQ_OUT0,  /*!< wakeup trigger by hbn_irq_out[0] */
    PDS_INT_HBN_IRQ_OUT1,  /*!< wakeup trigger by hbn_irq_out[1] */
    PDS_INT_GPIO_IRQ,      /*!< wakeup trigger by gpio_irq */
    PDS_INT_IRRX,          /*!< wakeup trigger by irrx_int */
    PDS_INT_BLE_SLP_IRQ,   /*!< wakeup trigger by ble_slp_irq */
    PDS_INT_USB_WKUP,      /*!< wakeup trigger by usb_wkup */
    PDS_INT_KYS_QDEC,      /*!< wakeup trigger by kys_int or qdec */
    PDS_INT_MAX,           /*!< PDS int max number */
} PDS_INT_Type;

/**
 *  @brief PDS vddcore GPIO interrupt type definition
 */
typedef enum {
    PDS_VDDCORE_GPIO_SRC_GPIO_0, /*!< PDS VDDCORE GPIO0 as PDS interrupt source */
    PDS_VDDCORE_GPIO_SRC_GPIO_1, /*!< PDS VDDCORE GPIO1 as PDS interrupt source */
    PDS_VDDCORE_GPIO_SRC_GPIO_2, /*!< PDS VDDCORE GPIO2 as PDS interrupt source */
    PDS_VDDCORE_GPIO_SRC_GPIO_3, /*!< PDS VDDCORE GPIO3 as PDS interrupt source */
    PDS_VDDCORE_GPIO_SRC_GPIO_4, /*!< PDS VDDCORE GPIO4 as PDS interrupt source */
    PDS_VDDCORE_GPIO_SRC_GPIO_5, /*!< PDS VDDCORE GPIO5 as PDS interrupt source */
    PDS_VDDCORE_GPIO_SRC_GPIO_6, /*!< PDS VDDCORE GPIO6 as PDS interrupt source */
    PDS_VDDCORE_GPIO_SRC_GPIO_7, /*!< PDS VDDCORE GPIO7 as PDS interrupt source */
} PDS_VDDCORE_GPIO_SRC_Type;

/**
 *  @brief PDS reset event type definition
 */
typedef enum {
    PDS_RST_EVENT_BUS_RST,        /*!< hreset_n (Bus Reset) */
    PDS_RST_EVENT_HBN_PWR_ON_RST, /*!< pwr_rst_n (hbn power on reset) */
    PDS_RST_EVENT_PDS_RST,        /*!< pds_rst_n (pds reset) */
    PDS_RST_EVENT_MAX,            /*!< PDS rst event max number */
} PDS_RST_EVENT_Type;

/**
 *  @brief PDS PLL status type definition
 */
typedef enum {
    PDS_PLL_STS_OFF = 0,   /*!< 2'b00 */
    PDS_PLL_STS_SFREG = 1, /*!< 2'b01 */
    PDS_PLL_STS_PU = 2,    /*!< 2'b10 */
    PDS_PLL_STS_RDY = 3,   /*!< 2'b11 */
} PDS_PLL_STS_Type;

/**
 *  @brief PDS RF status type definition
 */
typedef enum {
    PDS_RF_STS_OFF = 0,        /*!< 4'b0000 */
    PDS_RF_STS_PU_MBG = 1,     /*!< 4'b0001 */
    PDS_RF_STS_PU_LDO15RF = 3, /*!< 4'b0011 */
    PDS_RF_STS_PU_SFREG = 7,   /*!< 4'b0111 */
    PDS_RF_STS_BZ_EN_AON = 15, /*!< 4'b1111 */
} PDS_RF_STS_Type;

/**
 *  @brief PDS status type definition
 */
typedef enum {
    PDS_STS_IDLE = 0,            /*!< 4'b0000 */
    PDS_STS_ECG = 8,             /*!< 4'b1000 */
    PDS_STS_ERST = 12,           /*!< 4'b1100 */
    PDS_STS_EISO = 15,           /*!< 4'b1111 */
    PDS_STS_POFF = 7,            /*!< 4'b0111 */
    PDS_STS_PRE_BGON = 3,        /*!< 4'b0011 */
    PDS_STS_PRE_BGON1 = 1,       /*!< 4'b0001 */
    PDS_STS_BGON = 5,            /*!< 4'b0101 */
    PDS_STS_CLK_SW_32M = 4,      /*!< 4'b0100 */
    PDS_STS_PON_DCDC = 6,        /*!< 4'b0110 */
    PDS_STS_PON_LDO11_MISC = 14, /*!< 4'b1110 */
    PDS_STS_PON = 10,            /*!< 4'b1010 */
    PDS_STS_DISO = 2,            /*!< 4'b0010 */
    PDS_STS_DCG = 13,            /*!< 4'b1101 */
    PDS_STS_DRST = 11,           /*!< 4'b1011 */
    PDS_STS_WAIT_EFUSE = 9,      /*!< 4'b1001 */
} PDS_STS_Type;

/**
 *  @brief PLL XTAL type definition
 */
typedef enum {
    PDS_PLL_XTAL_NONE,  /*!< XTAL is none */
    PDS_PLL_XTAL_32M,   /*!< XTAL is 32M */
    PDS_PLL_XTAL_RC32M, /*!< XTAL is RC32M */
} PDS_PLL_XTAL_Type;

/**
 *  @brief PLL output clock type definition
 */
typedef enum {
    PDS_PLL_CLK_480M, /*!< PLL output clock:480M */
    PDS_PLL_CLK_240M, /*!< PLL output clock:240M */
    PDS_PLL_CLK_192M, /*!< PLL output clock:192M */
    PDS_PLL_CLK_160M, /*!< PLL output clock:160M */
    PDS_PLL_CLK_120M, /*!< PLL output clock:120M */
    PDS_PLL_CLK_96M,  /*!< PLL output clock:96M */
    PDS_PLL_CLK_80M,  /*!< PLL output clock:80M */
    PDS_PLL_CLK_48M,  /*!< PLL output clock:48M */
    PDS_PLL_CLK_32M,  /*!< PLL output clock:32M */
} PDS_PLL_CLK_Type;

/**
 *  @brief PDS level 0-7 mode HBN GPIO interrupt trigger type definition
 */
typedef enum {
    PDS_AON_GPIO_INT_TRIGGER_SYNC_FALLING_EDGE,  /*!< PDS level 0-7 mode HBN GPIO INT trigger type: sync falling edge trigger */
    PDS_AON_GPIO_INT_TRIGGER_SYNC_RISING_EDGE,   /*!< PDS level 0-7 mode HBN GPIO INT trigger type: sync rising edge trigger */
    PDS_AON_GPIO_INT_TRIGGER_SYNC_LOW_LEVEL,     /*!< PDS level 0-7 mode HBN GPIO INT trigger type: sync low level trigger */
    PDS_AON_GPIO_INT_TRIGGER_SYNC_HIGH_LEVEL,    /*!< PDS level 0-7 mode HBN GPIO INT trigger type: sync high level trigger */
    PDS_AON_GPIO_INT_TRIGGER_ASYNC_FALLING_EDGE, /*!< PDS level 0-7 mode HBN GPIO INT trigger type: async falling edge trigger */
    PDS_AON_GPIO_INT_TRIGGER_ASYNC_RISING_EDGE,  /*!< PDS level 0-7 mode HBN GPIO INT trigger type: async rising edge trigger */
    PDS_AON_GPIO_INT_TRIGGER_ASYNC_LOW_LEVEL,    /*!< PDS level 0-7 mode HBN GPIO INT trigger type: async low level trigger */
    PDS_AON_GPIO_INT_TRIGGER_ASYNC_HIGH_LEVEL,   /*!< PDS level 0-7 mode HBN GPIO INT trigger type: async high level trigger */
} PDS_AON_GPIO_INT_Trigger_Type;

/**
 *  @brief PDS APP configuration type definition
 */
typedef struct
{
    uint8_t pdsLevel;                                 /*!< PDS level */
    uint8_t turnOffXtal32m;                           /*!< Wheather turn off XTAL32M */
    uint8_t turnOffDll;                               /*!< Wheather turn off DLL */
    uint8_t turnOffRF;                                /*!< Wheather turn off RF */
    uint8_t useXtal32k;                               /*!< Wheather use xtal 32K as 32K clock source,otherwise use rc32k */
    uint8_t pdsAonGpioWakeupSrc;                      /*!< PDS level 0-7,31 mode aon GPIO Wakeup source(HBN wakeup pin) */
    PDS_AON_GPIO_INT_Trigger_Type pdsAonGpioTrigType; /*!< PDS level 0-7,31 mode aon GPIO Triger type(HBN wakeup pin) */
    uint8_t powerDownFlash;                           /*!< Whether power down flash */
    uint8_t pdsHoldGpio;                              /*!< Whether pds hold gpio level */
    uint8_t turnOffFlashPad;                          /*!< Whether turn off flash pad(GPIO17-GPIO22, GPIO23-GPIO28) */
    uint8_t flashPinCfg;                              /*!< 0 ext flash 23-28, 1 internal flash 23-28, 2 internal flash 23-28, 3 ext flash 17-22 */
    uint8_t turnoffPLL;                               /*!< Whether trun off PLL */
    uint8_t xtalType;                                 /*!< XTal type, used when user choose turn off PLL, PDS will turn on when exit PDS mode */
    uint8_t flashContRead;                            /*!< Whether enable flash continue read */
    uint32_t sleepTime;                               /*!< PDS sleep time */
    spi_flash_cfg_type *flashCfg;                     /*!< Flash config pointer, used when power down flash */
    HBN_LDO_LEVEL_Type ldoLevel;                      /*!< LDO level */
    void (*preCbFun)(void);                           /*!< Pre callback function */
    void (*postCbFun)(void);                          /*!< Post callback function */
} PDS_APP_CFG_Type;

/**
 *  @brief PDS LDO voltage type definition
 */
typedef enum {
    PDS_LDO_VOLTAGE_0P60V, /*!< PDS LDO voltage 0.60V */
    PDS_LDO_VOLTAGE_0P65V, /*!< PDS LDO voltage 0.65V */
    PDS_LDO_VOLTAGE_0P70V, /*!< PDS LDO voltage 0.70V */
    PDS_LDO_VOLTAGE_0P75V, /*!< PDS LDO voltage 0.75V */
    PDS_LDO_VOLTAGE_0P80V, /*!< PDS LDO voltage 0.80V */
    PDS_LDO_VOLTAGE_0P85V, /*!< PDS LDO voltage 0.85V */
    PDS_LDO_VOLTAGE_0P90V, /*!< PDS LDO voltage 0.9V */
    PDS_LDO_VOLTAGE_0P95V, /*!< PDS LDO voltage 0.95V */
    PDS_LDO_VOLTAGE_1P00V, /*!< PDS LDO voltage 1.0V */
    PDS_LDO_VOLTAGE_1P05V, /*!< PDS LDO voltage 1.05V */
    PDS_LDO_VOLTAGE_1P10V, /*!< PDS LDO voltage 1.1V */
    PDS_LDO_VOLTAGE_1P15V, /*!< PDS LDO voltage 1.15V */
    PDS_LDO_VOLTAGE_1P20V, /*!< PDS LDO voltage 1.2V */
    PDS_LDO_VOLTAGE_1P25V, /*!< PDS LDO voltage 1.25V */
    PDS_LDO_VOLTAGE_1P30V, /*!< PDS LDO voltage 1.3V */
    PDS_LDO_VOLTAGE_1P35V, /*!< PDS LDO voltage 1.35V */
} PDS_LDO_VOLTAGE_Type;

/**
 *  @brief PDS auto power down configuration type definition
 */
typedef struct
{
    BL_Fun_Type mbgPower;      /*!< PDS auto [31] MBG power */
    BL_Fun_Type ldo18rfPower;  /*!< PDS auto [30] LDO18RF power */
    BL_Fun_Type sfregPower;    /*!< PDS auto [29] SF_REG power */
    BL_Fun_Type pllPower;      /*!< PDS auto [28] PLL power */
    BL_Fun_Type cpu0Power;     /*!< PDS auto [19] NP power */
    BL_Fun_Type rc32mPower;    /*!< PDS auto [17] RC32M power */
    BL_Fun_Type xtalPower;     /*!< PDS auto [14] XTAL power */
    BL_Fun_Type allPower;      /*!< PDS auto [13] all power */
    BL_Fun_Type isoPower;      /*!< PDS auto [11] ISO power */
    BL_Fun_Type bzPower;       /*!< PDS auto [10] BZ power */
    BL_Fun_Type sramDisStanby; /*!< PDS auto [9] SRAM memory stanby disable */
    BL_Fun_Type cgPower;       /*!< PDS auto [8] CG power */
    BL_Fun_Type cpu1Power;     /*!< PDS auto [7] AP power */
    BL_Fun_Type usbPower;      /*!< PDS auto [3] USB power */
} PDS_AUTO_POWER_DOWN_CFG_Type;

/**
 *  @brief PDS auto configuration type definition
 */
typedef struct
{
    PDS_LDO_VOLTAGE_Type vddcoreVol; /*!< PDS auto [27:24] VDDCORE voltage, reference 0x4001F80C[27:24], recommended 0xA */
    BL_Fun_Type vddcoreVolEn;        /*!< PDS auto [18] VDDCORE voltage enable bit */
    BL_Fun_Type cpu0NotNeedWFI;      /*!< PDS auto [21] NP not need WFI to get in PDS mode */
    BL_Fun_Type cpu1NotNeedWFI;      /*!< PDS auto [20] AP not need WFI to get in PDS mode */
    BL_Fun_Type busReset;            /*!< PDS auto [16] bus reset bit, reset after wake up from PDS mode */
    BL_Fun_Type disIrqWakeUp;        /*!< PDS auto [15] disable IRQ request to wake up from PDS mode, except PDS counter IRQ */
    BL_Fun_Type powerOffXtalForever; /*!< PDS auto [2] power off xtal after get in PDS mode, and never power on xtal after wake up */
    BL_Fun_Type sleepForever;        /*!< PDS auto [1] sleep forever after get in PDS mode, need reset system to restart */
} PDS_AUTO_NORMAL_CFG_Type;

/**
 *  @brief PDS force type definition
 */
typedef enum {
    PDS_FORCE_NP,  /*!< PDS force NP */
    PDS_FORCE_RSV, /*!< rsv */
    PDS_FORCE_BZ,  /*!< PDS force BZ */
    PDS_FORCE_USB, /*!< PDS force USB */
} PDS_FORCE_Type;

/**
 *  @brief PDS force type definition
 */
typedef enum {
    AUDIO_PLL_12288000_HZ, /*!< PDS AUDIO PLL SET AS 12.288MHZ */
    AUDIO_PLL_11289600_HZ, /*!< PDS AUDIO PLL SET AS 11.2896HZ */
    AUDIO_PLL_5644800_HZ,  /*!< PDS AUDIO PLL SET AS 2.822400HZ */
    AUDIO_PLL_24576000_HZ, /*!< PDS AUDIO PLL SET AS 24.576000MHZ */
    AUDIO_PLL_24000000_HZ, /*!< PDS AUDIO PLL SET AS 24.000000MHZ */
    AUDIO_PLL_50000000_HZ, /*!< PDS AUDIO PLL SET AS 50.000000MHZ */
} PDS_AUDIO_PLL_Type;

/*@} end of group PDS_Public_Types */

/** @defgroup  PDS_Public_Constants
 *  @{
 */

/** @defgroup  PDS_LDO_LEVEL_TYPE
 *  @{
 */
#define IS_PDS_LDO_LEVEL_TYPE(type) (((type) == PDS_LDO_LEVEL_0P60V) || \
                                     ((type) == PDS_LDO_LEVEL_0P65V) || \
                                     ((type) == PDS_LDO_LEVEL_0P70V) || \
                                     ((type) == PDS_LDO_LEVEL_0P75V) || \
                                     ((type) == PDS_LDO_LEVEL_0P80V) || \
                                     ((type) == PDS_LDO_LEVEL_0P85V) || \
                                     ((type) == PDS_LDO_LEVEL_0P90V) || \
                                     ((type) == PDS_LDO_LEVEL_0P95V) || \
                                     ((type) == PDS_LDO_LEVEL_1P00V) || \
                                     ((type) == PDS_LDO_LEVEL_1P05V) || \
                                     ((type) == PDS_LDO_LEVEL_1P10V) || \
                                     ((type) == PDS_LDO_LEVEL_1P15V) || \
                                     ((type) == PDS_LDO_LEVEL_1P20V) || \
                                     ((type) == PDS_LDO_LEVEL_1P25V) || \
                                     ((type) == PDS_LDO_LEVEL_1P30V) || \
                                     ((type) == PDS_LDO_LEVEL_1P35V))

/** @defgroup  PDS_PAD_PIN_TYPE
 *  @{
 */
#define IS_PDS_PAD_PIN_TYPE(type) (((type) == PDS_PAD_PIN_GPIO_17) || \
                                   ((type) == PDS_PAD_PIN_GPIO_18) || \
                                   ((type) == PDS_PAD_PIN_GPIO_19) || \
                                   ((type) == PDS_PAD_PIN_GPIO_20) || \
                                   ((type) == PDS_PAD_PIN_GPIO_21) || \
                                   ((type) == PDS_PAD_PIN_GPIO_22) || \
                                   ((type) == PDS_PAD_PIN_GPIO_23) || \
                                   ((type) == PDS_PAD_PIN_GPIO_24) || \
                                   ((type) == PDS_PAD_PIN_GPIO_25) || \
                                   ((type) == PDS_PAD_PIN_GPIO_26) || \
                                   ((type) == PDS_PAD_PIN_GPIO_27) || \
                                   ((type) == PDS_PAD_PIN_GPIO_28))

/** @defgroup  PDS_PAD_CFG_TYPE
 *  @{
 */
#define IS_PDS_PAD_CFG_TYPE(type) (((type) == PDS_PAD_CFG_PULL_NONE) || \
                                   ((type) == PDS_PAD_CFG_PULL_DOWN) || \
                                   ((type) == PDS_PAD_CFG_PULL_UP) ||   \
                                   ((type) == PDS_PAD_CFG_ACTIVE_IE))

/** @defgroup  PDS_INT_TYPE
 *  @{
 */
#define IS_PDS_INT_TYPE(type) (((type) == PDS_INT_WAKEUP) ||        \
                               ((type) == PDS_INT_RF_DONE) ||       \
                               ((type) == PDS_INT_PLL_DONE) ||      \
                               ((type) == PDS_INT_PDS_SLEEP_CNT) || \
                               ((type) == PDS_INT_HBN_IRQ_OUT0) ||  \
                               ((type) == PDS_INT_HBN_IRQ_OUT1) ||  \
                               ((type) == PDS_INT_GPIO_IRQ) ||      \
                               ((type) == PDS_INT_IRRX) ||          \
                               ((type) == PDS_INT_BLE_SLP_IRQ) ||   \
                               ((type) == PDS_INT_USB_WKUP) ||      \
                               ((type) == PDS_INT_KYS_QDEC) ||      \
                               ((type) == PDS_INT_MAX))

/** @defgroup  PDS_VDDCORE_GPIO_SRC_TYPE
 *  @{
 */
#define IS_PDS_VDDCORE_GPIO_SRC_TYPE(type) (((type) == PDS_VDDCORE_GPIO_SRC_GPIO_0) || \
                                            ((type) == PDS_VDDCORE_GPIO_SRC_GPIO_1) || \
                                            ((type) == PDS_VDDCORE_GPIO_SRC_GPIO_2) || \
                                            ((type) == PDS_VDDCORE_GPIO_SRC_GPIO_3) || \
                                            ((type) == PDS_VDDCORE_GPIO_SRC_GPIO_4) || \
                                            ((type) == PDS_VDDCORE_GPIO_SRC_GPIO_5) || \
                                            ((type) == PDS_VDDCORE_GPIO_SRC_GPIO_6) || \
                                            ((type) == PDS_VDDCORE_GPIO_SRC_GPIO_7))

/** @defgroup  PDS_RST_EVENT_TYPE
 *  @{
 */
#define IS_PDS_RST_EVENT_TYPE(type) (((type) == PDS_RST_EVENT_BUS_RST) ||        \
                                     ((type) == PDS_RST_EVENT_HBN_PWR_ON_RST) || \
                                     ((type) == PDS_RST_EVENT_PDS_RST) ||        \
                                     ((type) == PDS_RST_EVENT_MAX))

/** @defgroup  PDS_PLL_STS_TYPE
 *  @{
 */
#define IS_PDS_PLL_STS_TYPE(type) (((type) == PDS_PLL_STS_OFF) ||   \
                                   ((type) == PDS_PLL_STS_SFREG) || \
                                   ((type) == PDS_PLL_STS_PU) ||    \
                                   ((type) == PDS_PLL_STS_RDY))

/** @defgroup  PDS_RF_STS_TYPE
 *  @{
 */
#define IS_PDS_RF_STS_TYPE(type) (((type) == PDS_RF_STS_OFF) ||        \
                                  ((type) == PDS_RF_STS_PU_MBG) ||     \
                                  ((type) == PDS_RF_STS_PU_LDO15RF) || \
                                  ((type) == PDS_RF_STS_PU_SFREG) ||   \
                                  ((type) == PDS_RF_STS_BZ_EN_AON))

/** @defgroup  PDS_STS_TYPE
 *  @{
 */
#define IS_PDS_STS_TYPE(type) (((type) == PDS_STS_IDLE) ||           \
                               ((type) == PDS_STS_ECG) ||            \
                               ((type) == PDS_STS_ERST) ||           \
                               ((type) == PDS_STS_EISO) ||           \
                               ((type) == PDS_STS_POFF) ||           \
                               ((type) == PDS_STS_PRE_BGON) ||       \
                               ((type) == PDS_STS_PRE_BGON1) ||      \
                               ((type) == PDS_STS_BGON) ||           \
                               ((type) == PDS_STS_CLK_SW_32M) ||     \
                               ((type) == PDS_STS_PON_DCDC) ||       \
                               ((type) == PDS_STS_PON_LDO11_MISC) || \
                               ((type) == PDS_STS_PON) ||            \
                               ((type) == PDS_STS_DISO) ||           \
                               ((type) == PDS_STS_DCG) ||            \
                               ((type) == PDS_STS_DRST) ||           \
                               ((type) == PDS_STS_WAIT_EFUSE))

/** @defgroup  PDS_PLL_XTAL_TYPE
 *  @{
 */
#define IS_PDS_PLL_XTAL_TYPE(type) (((type) == PDS_PLL_XTAL_NONE) || \
                                    ((type) == PDS_PLL_XTAL_32M) ||  \
                                    ((type) == PDS_PLL_XTAL_RC32M))

/** @defgroup  PDS_PLL_CLK_TYPE
 *  @{
 */
#define IS_PDS_PLL_CLK_TYPE(type) (((type) == PDS_PLL_CLK_480M) || \
                                   ((type) == PDS_PLL_CLK_240M) || \
                                   ((type) == PDS_PLL_CLK_192M) || \
                                   ((type) == PDS_PLL_CLK_160M) || \
                                   ((type) == PDS_PLL_CLK_120M) || \
                                   ((type) == PDS_PLL_CLK_96M) ||  \
                                   ((type) == PDS_PLL_CLK_80M) ||  \
                                   ((type) == PDS_PLL_CLK_48M) ||  \
                                   ((type) == PDS_PLL_CLK_32M))

/** @defgroup  PDS_AON_GPIO_INT_TRIGGER_TYPE
 *  @{
 */
#define IS_PDS_AON_GPIO_INT_TRIGGER_TYPE(type) (((type) == PDS_AON_GPIO_INT_TRIGGER_SYNC_FALLING_EDGE) ||  \
                                                ((type) == PDS_AON_GPIO_INT_TRIGGER_SYNC_RISING_EDGE) ||   \
                                                ((type) == PDS_AON_GPIO_INT_TRIGGER_SYNC_LOW_LEVEL) ||     \
                                                ((type) == PDS_AON_GPIO_INT_TRIGGER_SYNC_HIGH_LEVEL) ||    \
                                                ((type) == PDS_AON_GPIO_INT_TRIGGER_ASYNC_FALLING_EDGE) || \
                                                ((type) == PDS_AON_GPIO_INT_TRIGGER_ASYNC_RISING_EDGE) ||  \
                                                ((type) == PDS_AON_GPIO_INT_TRIGGER_ASYNC_LOW_LEVEL) ||    \
                                                ((type) == PDS_AON_GPIO_INT_TRIGGER_ASYNC_HIGH_LEVEL))

/** @defgroup  PDS_LDO_VOLTAGE_TYPE
 *  @{
 */
#define IS_PDS_LDO_VOLTAGE_TYPE(type) (((type) == PDS_LDO_VOLTAGE_0P60V) || \
                                       ((type) == PDS_LDO_VOLTAGE_0P65V) || \
                                       ((type) == PDS_LDO_VOLTAGE_0P70V) || \
                                       ((type) == PDS_LDO_VOLTAGE_0P75V) || \
                                       ((type) == PDS_LDO_VOLTAGE_0P80V) || \
                                       ((type) == PDS_LDO_VOLTAGE_0P85V) || \
                                       ((type) == PDS_LDO_VOLTAGE_0P90V) || \
                                       ((type) == PDS_LDO_VOLTAGE_0P95V) || \
                                       ((type) == PDS_LDO_VOLTAGE_1P00V) || \
                                       ((type) == PDS_LDO_VOLTAGE_1P05V) || \
                                       ((type) == PDS_LDO_VOLTAGE_1P10V) || \
                                       ((type) == PDS_LDO_VOLTAGE_1P15V) || \
                                       ((type) == PDS_LDO_VOLTAGE_1P20V) || \
                                       ((type) == PDS_LDO_VOLTAGE_1P25V) || \
                                       ((type) == PDS_LDO_VOLTAGE_1P30V) || \
                                       ((type) == PDS_LDO_VOLTAGE_1P35V))

/** @defgroup  PDS_FORCE_TYPE
 *  @{
 */
#define IS_PDS_FORCE_TYPE(type) (((type) == PDS_FORCE_NP) ||  \
                                 ((type) == PDS_FORCE_RSV) || \
                                 ((type) == PDS_FORCE_BZ) ||  \
                                 ((type) == PDS_FORCE_USB))

/** @defgroup  PDS_AUDIO_PLL_TYPE
 *  @{
 */
#define IS_PDS_AUDIO_PLL_TYPE(type) (((type) == AUDIO_PLL_12288000_HZ) || \
                                     ((type) == AUDIO_PLL_11289600_HZ) || \
                                     ((type) == AUDIO_PLL_5644800_HZ)  || \
                                     ((type) == AUDIO_PLL_24576000_HZ) || \
                                     ((type) == AUDIO_PLL_24000000_HZ) || \
                                     ((type) == AUDIO_PLL_50000000_HZ))

/*@} end of group PDS_Public_Constants */

/** @defgroup  PDS_Public_Macros
 *  @{
 */
#define PDS_LDO_MIN_PU_CNT        (25) /* LDO need 25 cycles to power up */
#define PDS_WARMUP_CNT            (38) /* LDO hw warmup compensation latency cycles */
#define PDS_WARMUP_LATENCY_CNT    (38) /* LDO hw warmup compensation latency cycles */
#define PDS_FORCE_PWR_OFF_OFFSET  (0)
#define PDS_FORCE_ISO_EN_OFFSET   (4)
#define PDS_FORCE_PDS_RST_OFFSET  (8)
#define PDS_FORCE_MEM_STBY_OFFSET (12)
#define PDS_FORCE_GATE_CLK_OFFSET (16)
#define PDS_INT_MASK_BIT_OFFSET   (8)
#define PDS_AON_WAKEUP_GPIO_NONE  (0x00)
#define PDS_AON_WAKEUP_GPIO_9     (0x01)
#define PDS_AON_WAKEUP_GPIO_10    (0x02)
#define PDS_AON_WAKEUP_GPIO_11    (0x04)
#define PDS_AON_WAKEUP_GPIO_12    (0x08)
#define PDS_AON_WAKEUP_GPIO_13    (0x10)
#define PDS_AON_WAKEUP_GPIO_ALL   (0x1E)

/*@} end of group PDS_Public_Macros */

/** @defgroup  PDS_Public_Functions
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
void PDS_WAKEUP_IRQHandler(void);
#endif
/*----------*/
BL_Err_Type PDS_RAM_Config(PDS_RAM_CFG_Type *ramCfg);
BL_Err_Type PDS_Set_Pad_Config(PDS_PAD_PIN_Type pin, PDS_PAD_CFG_Type cfg);
/*----------*/
BL_Err_Type PDS_App_Enable(PDS_CTL_Type *cfg, PDS_CTL4_Type *cfg4, uint32_t pdsSleepCnt);
BL_Err_Type PDS_Force_Config(PDS_CTL2_Type *cfg2, PDS_CTL3_Type *cfg3);
BL_Err_Type PDS_Default_Level_Config(PDS_DEFAULT_LV_CFG_Type *defaultLvCfg, uint32_t pdsSleepCnt);
/*----------*/
BL_Err_Type PDS_IntEn(PDS_INT_Type intType, BL_Fun_Type enable);
BL_Err_Type PDS_IntMask(PDS_INT_Type intType, BL_Mask_Type intMask);
BL_Sts_Type PDS_Get_IntStatus(PDS_INT_Type intType);
BL_Err_Type PDS_IntClear(void);
PDS_PLL_STS_Type PDS_Get_PdsPllStstus(void);
PDS_RF_STS_Type PDS_Get_PdsRfStstus(void);
PDS_STS_Type PDS_Get_PdsStstus(void);
/*----------*/
BL_Err_Type PDS_Clear_Reset_Event(void);
BL_Sts_Type PDS_Get_Reset_Event(PDS_RST_EVENT_Type event);
/*----------*/
BL_Err_Type PDS_Set_Vddcore_GPIO_IntCfg(PDS_VDDCORE_GPIO_SRC_Type src,
                                        PDS_AON_GPIO_INT_Trigger_Type mode);
BL_Err_Type PDS_Set_Vddcore_GPIO_IntMask(BL_Mask_Type intMask);
BL_Sts_Type PDS_Get_Vddcore_GPIO_IntStatus(void);
BL_Err_Type PDS_Set_Vddcore_GPIO_IntClear(void);
/*----------*/
BL_Err_Type PDS_WAKEUP_IRQHandler_Install(void);
BL_Err_Type PDS_Int_Callback_Install(PDS_INT_Type intType, intCallback_Type *cbFun);
/*----------*/
BL_Err_Type PDS_Trim_RC32M(void);
BL_Err_Type PDS_Select_RC32M_As_PLL_Ref(void);
BL_Err_Type PDS_Select_XTAL_As_PLL_Ref(void);
BL_Err_Type PDS_Power_On_PLL(PDS_PLL_XTAL_Type xtalType);
BL_Err_Type PDS_Enable_PLL_All_Clks(void);
BL_Err_Type PDS_Enable_PLL_Clk(PDS_PLL_CLK_Type pllClk);
BL_Err_Type PDS_Disable_PLL_All_Clks(void);
BL_Err_Type PDS_Disable_PLL_Clk(PDS_PLL_CLK_Type pllClk);
BL_Err_Type PDS_Power_Off_PLL(void);
BL_Err_Type PDS_Set_Audio_PLL_Freq(PDS_AUDIO_PLL_Type audioPLLFreq);
/*----------*/
void PDS_Reset(void);
void PDS_Enable(PDS_CFG_Type *cfg, uint32_t pdsSleepCnt);
void PDS_Auto_Time_Config(uint32_t sleepDuration);
void PDS_Auto_Enable(PDS_AUTO_POWER_DOWN_CFG_Type *powerCfg, PDS_AUTO_NORMAL_CFG_Type *normalCfg, BL_Fun_Type enable);
void PDS_Manual_Force_Turn_Off(PDS_FORCE_Type domain);
void PDS_Manual_Force_Turn_On(PDS_FORCE_Type domain);
/*----------*/
BL_Err_Type PDS_Set_Clkpll_Top_Ctrl(uint8_t vg11Sel);
/*----------*/

/*@} end of group PDS_Public_Functions */

/*@} end of group PDS */

/*@} end of group BL702_Peripheral_Driver */

#endif /* __BL702_PDS_H__ */
