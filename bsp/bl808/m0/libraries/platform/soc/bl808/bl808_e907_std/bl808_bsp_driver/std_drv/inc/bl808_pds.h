/**
  ******************************************************************************
  * @file    bl808_pds.h
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
#ifndef __BL808_PDS_H__
#define __BL808_PDS_H__

#include "pds_reg.h"
#include "glb_reg.h"
#include "bl808_ef_ctrl.h"
#include "bl808_clock.h"
#include "bl808_aon.h"
#include "bl808_hbn.h"
#include "bl808_sflash.h"
#include "bl808_sf_ctrl.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PDS
 *  @{
 */

/** @defgroup  PDS_Public_Types
 *  @{
 */

/**
 *  @brief PDS GPIO int set type
 */
typedef enum {
    PDS_GPIO_INT_SET_1_GPIO0_GPIO7,     /*!< gpio int set 1, gpio0 - gpio7          */
    PDS_GPIO_INT_SET_2_GPIO8_16_GPIO22, /*!< gpio int set 2, gpio8, gpio16 - gpio22 */
    PDS_GPIO_INT_SET_3_GPIO23_GPIO30,   /*!< gpio int set 3, gpio23 - gpio30        */
    PDS_GPIO_INT_SET_4_GPIO31_GPIO38,   /*!< gpio int set 4, gpio31 - gpio38        */
} PDS_GPIO_INT_SET_Type;

/**
 *  @brief PDS GPIO interrupt control mode type definition
 */
typedef enum {
    PDS_GPIO_INT_SYNC_FALLING_EDGE = 0,        /*!< GPIO interrupt sync mode, GPIO negedge pulse trigger interrupt */
    PDS_GPIO_INT_SYNC_RISING_EDGE = 1,         /*!< GPIO interrupt sync mode, GPIO posedge pulse trigger interrupt */
    PDS_GPIO_INT_SYNC_LOW_LEVEL = 2,           /*!< GPIO interrupt sync mode, GPIO negedge level trigger interrupt */
    PDS_GPIO_INT_SYNC_HIGH_LEVEL = 3,          /*!< GPIO interrupt sync mode, GPIO posedge level trigger interrupt */
    PDS_GPIO_INT_SYNC_RISING_FALLING_EDGE = 4, /*!< GPIO interrupt sync mode, GPIO posedge negedge pulse trigger interrupt */
    PDS_GPIO_INT_ASYNC_FALLING_EDGE = 8,       /*!< GPIO interrupt async mode, GPIO negedge pulse trigger interrupt */
    PDS_GPIO_INT_ASYNC_RISING_EDGE = 9,        /*!< GPIO interrupt async mode, GPIO posedge pulse trigger interrupt */
    PDS_GPIO_INT_ASYNC_LOW_LEVEL = 10,         /*!< GPIO interrupt async mode, GPIO negedge level trigger interrupt */
    PDS_GPIO_INT_ASYNC_HIGH_LEVEL = 11,        /*!< GPIO interrupt async mode, GPIO posedge level trigger interrupt */
} PDS_GPIO_INT_TRIG_Type;

/**
 *  @brief PDS lp system clock type definition
 */
typedef enum {
    PDS_LP_SYS_CLK_BCLK_DIV, /*!< use bclk div as system clock frequency */
} PDS_LP_SYS_CLK_Type;

/**
 *  @brief PDS LDO level type definition
 */
typedef enum {
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
 *  @brief PDS configuration type definition
 */
typedef struct
{
    uint32_t pdsStart        : 1; /*!< [0]PDS Start */
    uint32_t sleepForever    : 1; /*!< [1]PDS sleep forever */
    uint32_t xtalForceOff    : 1; /*!< [2]Power off xtal force */
    uint32_t saveWiFiState   : 1; /*!< [3]Save WIFI State Before Enter PDS */
    uint32_t dcdc11Off       : 1; /*!< [4]power down dcdc11 during PDS */
    uint32_t bgSysOff        : 1; /*!< [5]power down bg_sys during PDS */
    uint32_t ctrlGpioIePuPd  : 1; /*!< [6]PDS control */
    uint32_t dcdc18Off       : 1; /*!< [7]power down dcdc18 during PDS */
    uint32_t clkOff          : 1; /*!< [8]gate clock during PDS (each pwr domain has its own control) */
    uint32_t memStby         : 1; /*!< [9]mem_stby during PDS (each power domain can has its own control) */
    uint32_t glbRstProtect   : 1; /*!< [10]avoid glb_reg reset by any reset */
    uint32_t isolation       : 1; /*!< [11]Isolation during PDS (each power domain can has its own control) */
    uint32_t waitXtalRdy     : 1; /*!< [12]wait XTAL Ready during before PDS Interrupt */
    uint32_t pdsPwrOff       : 1; /*!< [13]Power off during PDS (each power domain can has its own control) */
    uint32_t xtalOff         : 1; /*!< [14]xtal power down during PDS */
    uint32_t socEnbForceOn   : 1; /*!< [15]pds_soc_enb always active */
    uint32_t pdsRstSocEn     : 1; /*!< [16]pds_rst controlled by PDS */
    uint32_t pdsRC32mOn      : 1; /*!< [17]RC32M always on or RC32M on/off controlled by PDS state */
    uint32_t pdsDcdc11VselEn : 1; /*!< [18]PDS "SLEEP" control DCDC11 voltage enable */
    uint32_t usbpllOff       : 1; /*!< [19]PDS Control USB PLL off When pds_pwr_off */
    uint32_t aupllOff        : 1; /*!< [20]PDS control aupll power off */
    uint32_t cpupllOff       : 1; /*!< [21]PDS control cpupll power off */
    uint32_t wifipllOff      : 1; /*!< [22]PDS control wifipll power off */
    uint32_t pdsDcdc11Vsel   : 5; /*!< [27:23]DCDC11 voltage selection in PDS mode */
    uint32_t pdsCtlRfSel     : 2; /*!< [29:28]select the way RF controlled by PDS */
    uint32_t pdsUseTbttSlp   : 1; /*!< [30]PDS Auto Sleep When wifi_tbtt_sleep_irq detect to 1 */
    uint32_t pdsGpioIsoMod   : 1; /*!< [31]HW Keep GPIO at PDS Mode */
} PDS_CTL_Type;

/**
 *  @brief PDS force configuration type definition
 */
typedef struct
{
    uint32_t rsv0        : 1; /*!< [0] */
    uint32_t mcuRst      : 1; /*!< [1] */
    uint32_t mcuMemStby  : 1; /*!< [2] */
    uint32_t mcuGateClk  : 1; /*!< [3] */
    uint32_t rsv4_7      : 4; /*!< [7:4]reserve */
    uint32_t dspPwrOff   : 1; /*!< [8] */
    uint32_t dspRst      : 1; /*!< [9] */
    uint32_t dspMemStby  : 1; /*!< [10] */
    uint32_t dspGateClk  : 1; /*!< [11] */
    uint32_t rsv12       : 1; /*!< [12] */
    uint32_t WbRst       : 1; /*!< [13] */
    uint32_t WbMemStby   : 1; /*!< [14] */
    uint32_t WbGateClk   : 1; /*!< [15] */
    uint32_t rsv16_19    : 4; /*!< [19:16]reserve */
    uint32_t usbPwrOff   : 1; /*!< [20] */
    uint32_t usbRst      : 1; /*!< [21] */
    uint32_t usbMemStby  : 1; /*!< [22] */
    uint32_t usbGateClk  : 1; /*!< [23] */
    uint32_t MiscPwrOff  : 1; /*!< [24] */
    uint32_t MiscRst     : 1; /*!< [25] */
    uint32_t MiscMemStby : 1; /*!< [26] */
    uint32_t MiscGateClk : 1; /*!< [27] */
    uint32_t rsv28_31    : 4; /*!< [31:28]reserve */
} PDS_CTL4_Type;

/**
 *  @brief PDS interrupt type definition
 */
typedef enum {
    PDS_INT_WAKEUP = 0,           /*!< PDS wakeup interrupt(assert bit while wakeup, include PDS_Timer/...) */
    PDS_INT_RF_DONE = 1,          /*!< PDS RF done interrupt */
    PDS_INT_WIFI_TBTT_SLEEP = 2,  /*!< PDS wifi tbtt sleep interrupt */
    PDS_INT_WIFI_TBTT_WAKEUP = 3, /*!< PDS wifi tbtt wakeup interrupt */
    PDS_INT_MAX = 4,              /*!< PDS int max number */
} PDS_INT_Type;

/**
 *  @brief PDS force configuration type definition
 */
typedef struct
{
    uint32_t rsv0            : 1;  /*!< [0]manual force NP power off */
    uint32_t forceDspPwrOff  : 1;  /*!< [1]manual force MM power off */
    uint32_t rsv2            : 1;  /*!< [2]manual force WB power off */
    uint32_t forceUsbPwrOff  : 1;  /*!< [3]manual force USB power off */
    uint32_t rsv4            : 1;  /*!< [4]manual force NP isolation */
    uint32_t forceDspIso     : 1;  /*!< [5]manual force MM isolation */
    uint32_t rsv6            : 1;  /*!< [6]manual force WB isolation */
    uint32_t forceUsbIso     : 1;  /*!< [7]manual force USB isolation */
    uint32_t forceMcuPdsRst  : 1;  /*!< [8]manual force NP pds reset */
    uint32_t forceDspPdsRst  : 1;  /*!< [9]manual force MM pds reset */
    uint32_t forceWbPdsRst   : 1;  /*!< [10]manual force WB pds reset */
    uint32_t forceUsbPdsRst  : 1;  /*!< [11]manual force USB pds reset */
    uint32_t forceMcuMemStby : 1;  /*!< [12]manual force NP memory sleep */
    uint32_t forceDspMemStby : 1;  /*!< [13]manual force MM memory sleep */
    uint32_t forceWbMemStby  : 1;  /*!< [14]manual force WB memory sleep */
    uint32_t forceUsbMemStby : 1;  /*!< [15]manual force USB memory sleep */
    uint32_t forceMcuGateClk : 1;  /*!< [16]manual force NP clock gated */
    uint32_t forceDspGateClk : 1;  /*!< [17]manual force MM clock gated */
    uint32_t forceWbGateClk  : 1;  /*!< [18]manual force WB clock gated */
    uint32_t forceUsbGateClk : 1;  /*!< [19]manual force USB clock gated */
    uint32_t rsv20_31        : 12; /*!< [31:20]reserve */
} PDS_CTL2_Type;

/**
 *  @brief PDS force configuration type definition
 */
typedef struct
{
    uint32_t rsv0             : 1;  /*!< [0]reserve */
    uint32_t forceMiscPwrOff  : 1;  /*!< [1]manual force MISC pwr_off */
    uint32_t rsv2_3           : 2;  /*!< [3:2]reserve */
    uint32_t forceMiscIsoEn   : 1;  /*!< [4]manual force MISC iso_en */
    uint32_t rsv5_6           : 2;  /*!< [6:5]reserve */
    uint32_t forceMiscPdsRst  : 1;  /*!< [7]manual force MISC pds_rst */
    uint32_t rsv8_9           : 2;  /*!< [9:8]reserve */
    uint32_t forceMiscMemStby : 1;  /*!< [10]manual force MISC mem_stby */
    uint32_t rsv11_12         : 2;  /*!< [12:11]reserve */
    uint32_t forceMiscGateClk : 1;  /*!< [13]manual force MISC gate_clk */
    uint32_t rsv14_25         : 12; /*!< [25:14]reserve */
    uint32_t DspIsoEn         : 1;  /*!< [26]make MM isolated at PDS Sleep state */
    uint32_t rsv27_28         : 2;  /*!< [28:27]reserve */
    uint32_t UsbIsoEn         : 1;  /*!< [29]make USB isolated at PDS Sleep state */
    uint32_t MiscIsoEn        : 1;  /*!< [30]make misc isolated at PDS Sleep state */
    uint32_t rsv31            : 1;  /*!< [31]reserve */
} PDS_CTL3_Type;

/**
 *  @brief PDS force configuration type definition
 */
typedef struct
{
    uint32_t McuWfiMask : 1;  /*!< [0]pds start condition mask np_wfi */
    uint32_t rsv1       : 1;  /*!< [1]reserve */
    uint32_t DspWfiMask : 1;  /*!< [2]pds start condition mask mm_wfi */
    uint32_t rsv3       : 1;  /*!< [3]reserve */
    uint32_t LpWfiMask  : 1;  /*!< [4]pds start condition mask pico_wfi */
    uint32_t rsv5_7     : 3;  /*!< [7:5]reserve */
    uint32_t ctrlUsb33  : 1;  /*!< [8]enable HW control turn on&&off USB 3.3V */
    uint32_t pdLdo18io  : 1;  /*!< [9]power down ldo18io during PDS */
    uint32_t rsv10_15   : 6;  /*!< [15:10]reserve */
    uint32_t gpioKeepEn : 3;  /*!< [18:16]can use bit to enable or disable keep function */
    uint32_t rsv19_31   : 13; /*!< [31:19]reserve */
} PDS_CTL5_Type;

/**
 *  @brief PDS default level configuration type definition
 */
typedef struct
{
    PDS_CTL_Type pdsCtl;   /*!< PDS_CTL configuration */
    PDS_CTL2_Type pdsCtl2; /*!< PDS_CTL2 configuration */
    PDS_CTL3_Type pdsCtl3; /*!< PDS_CTL3 configuration */
    PDS_CTL4_Type pdsCtl4; /*!< PDS_CTL4 configuration */
    PDS_CTL5_Type pdsCtl5; /*!< PDS_CTL5 configuration */
} PDS_DEFAULT_LV_CFG_Type;

/**
 *  @brief PDS control RAM1 type definition
 */
typedef struct
{
    uint32_t ocramSlp   : 4; /*!< [3:0] cr_ocram_slp */
    uint32_t ocramRet   : 4; /*!< [7:4] cr_ocram_ret */
    uint32_t ramClkCnt  : 6; /*!< [13:8] HW Option : Assert Extra Clock Counter in  MEM_STBY */
    uint32_t rsv14_15   : 2; /*!< [15:14] reserved */
    uint32_t ramClkCnt2 : 6; /*!< [21:16] HW Option : Assert Extra Clock Counter in MEM_IDLE/LV_MEM_IDLE */
    uint32_t rsv22_23   : 2; /*!< [23:22] reserved */
    uint32_t mcuRamClk  : 1; /*!< [24] PDS Control PD_CORE_CPU SRAM Clock */
    uint32_t dspRamClk  : 1; /*!< [25] PDS Control PD_MM SRAM Clock */
    uint32_t wbRamClk   : 1; /*!< [26] PDS Control PD_WB SRAM Clock */
    uint32_t usbRamClk  : 1; /*!< [27] PDS Control PD_usb SRAM Clock */
    uint32_t miscRamClk : 1; /*!< [28] PDS Control PD_CORE_MISC SRAM Clock */
    uint32_t rsv29      : 1; /*!< [29] reserved */
    uint32_t ctlRamClk2 : 1; /*!< [30] To assert extra clock during PDS on sequence */
    uint32_t ctlRamClk  : 1; /*!< [31] Enable PDS Control PD_CORE SRAM Clock */
} PDS_CTRL_RAM1_Type;

/**
 *  @brief PDS control RAM2 type definition
 */
typedef struct
{
    uint32_t wramSlp  : 10; /*!< [9:0] cr_wram_slp */
    uint32_t wramRet  : 10; /*!< [19:10] cr_wram_ret */
    uint32_t rsv20_31 : 12; /*!< [31:20] reserved */
} PDS_CTRL_RAM2_Type;

/**
 *  @brief PDS OCRAM configuration type definition
 */
typedef struct
{
    uint32_t PDS_OCRAM_CFG_0KB_16KB_CPU_RAM_SLP  : 1;  /*!< [0]   0~16KB cpu_ram sleep */
    uint32_t PDS_OCRAM_CFG_16KB_32KB_CPU_RAM_SLP : 1;  /*!< [1]   16~32KB cpu_ram sleep */
    uint32_t PDS_OCRAM_CFG_32KB_48KB_CPU_RAM_SLP : 1;  /*!< [2]   32~48KB cpu_ram sleep */
    uint32_t PDS_OCRAM_CFG_48KB_64KB_CPU_RAM_SLP : 1;  /*!< [3]   48~64KB cpu_ram sleep */
    uint32_t PDS_OCRAM_CFG_0KB_16KB_CPU_RAM_RET  : 1;  /*!< [4]   0~16KB cpu_ram retension */
    uint32_t PDS_OCRAM_CFG_16KB_32KB_CPU_RAM_RET : 1;  /*!< [5]   16~32KB cpu_ram retension */
    uint32_t PDS_OCRAM_CFG_32KB_48KB_CPU_RAM_RET : 1;  /*!< [6]   32~48KB cpu_ram retension */
    uint32_t PDS_OCRAM_CFG_48KB_64KB_CPU_RAM_RET : 1;  /*!< [7]   48~64KB cpu_ram retension */
    uint32_t PDS_OCRAM_CFG_RSV                   : 24; /*!< [31:8]reserve */
} PDS_OCRAM_CFG_Type;

/**
 *  @brief PDS WRAM configuration type definition
 */
typedef struct
{
    uint32_t PDS_WRAM_CFG_0KB_16KB_CPU_RAM_SLP    : 1;  /*!< [0]   0~16KB cpu_ram sleep */
    uint32_t PDS_WRAM_CFG_16KB_32KB_CPU_RAM_SLP   : 1;  /*!< [1]   16~32KB cpu_ram sleep */
    uint32_t PDS_WRAM_CFG_32KB_48KB_CPU_RAM_SLP   : 1;  /*!< [2]   32~48KB cpu_ram sleep */
    uint32_t PDS_WRAM_CFG_48KB_64KB_CPU_RAM_SLP   : 1;  /*!< [3]   48~64KB cpu_ram sleep */
    uint32_t PDS_WRAM_CFG_64KB_80KB_CPU_RAM_SLP   : 1;  /*!< [4]   64~80KB cpu_ram sleep */
    uint32_t PDS_WRAM_CFG_80KB_96KB_CPU_RAM_SLP   : 1;  /*!< [5]   80~96KB cpu_ram sleep */
    uint32_t PDS_WRAM_CFG_96KB_112KB_CPU_RAM_SLP  : 1;  /*!< [6]   96~112KB cpu_ram sleep */
    uint32_t PDS_WRAM_CFG_112KB_128KB_CPU_RAM_SLP : 1;  /*!< [7]   112~128KB cpu_ram sleep */
    uint32_t PDS_WRAM_CFG_128KB_144KB_CPU_RAM_SLP : 1;  /*!< [8]   128~144KB cpu_ram sleep */
    uint32_t PDS_WRAM_CFG_144KB_160KB_CPU_RAM_SLP : 1;  /*!< [9]   144~160KB cpu_ram sleep */
    uint32_t PDS_WRAM_CFG_0KB_16KB_CPU_RAM_RET    : 1;  /*!< [10]   0~16KB cpu_ram retension */
    uint32_t PDS_WRAM_CFG_16KB_32KB_CPU_RAM_RET   : 1;  /*!< [11]   16~32KB cpu_ram retension */
    uint32_t PDS_WRAM_CFG_32KB_48KB_CPU_RAM_RET   : 1;  /*!< [12]   32~48KB cpu_ram retension */
    uint32_t PDS_WRAM_CFG_48KB_64KB_CPU_RAM_RET   : 1;  /*!< [13]   48~64KB cpu_ram retension */
    uint32_t PDS_WRAM_CFG_64KB_80KB_CPU_RAM_RET   : 1;  /*!< [14]   64~80KB cpu_ram retension */
    uint32_t PDS_WRAM_CFG_80KB_96KB_CPU_RAM_RET   : 1;  /*!< [15]   80~96KB cpu_ram retension */
    uint32_t PDS_WRAM_CFG_96KB_112KB_CPU_RAM_RET  : 1;  /*!< [16]   96~112KB cpu_ram retension */
    uint32_t PDS_WRAM_CFG_112KB_128KB_CPU_RAM_RET : 1;  /*!< [17]   112~128KB cpu_ram retension */
    uint32_t PDS_WRAM_CFG_128KB_144KB_CPU_RAM_RET : 1;  /*!< [18]   128~144KB cpu_ram retension */
    uint32_t PDS_WRAM_CFG_144KB_160KB_CPU_RAM_RET : 1;  /*!< [19]   144~160KB cpu_ram retension */
    uint32_t PDS_WRAM_CFG_RSV                     : 22; /*!< [31:20]reserve */
} PDS_WRAM_CFG_Type;

/**
 *  @brief PDS level 0/1/2/3 mode HBN GPIO interrupt trigger type definition
 */
typedef enum {
    PDS_AON_GPIO_INT_TRIGGER_SYNC_FALLING_EDGE = 0,   /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: sync falling edge trigger */
    PDS_AON_GPIO_INT_TRIGGER_SYNC_RISING_EDGE = 1,    /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: sync rising edge trigger */
    PDS_AON_GPIO_INT_TRIGGER_SYNC_LOW_LEVEL = 2,      /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: sync low level trigger */
    PDS_AON_GPIO_INT_TRIGGER_SYNC_HIGH_LEVEL = 3,     /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: sync high level trigger */
    PDS_AON_GPIO_INT_TRIGGER_SYNC_RISING_FALLING = 7, /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: sync rising+falling edge trigger */
    PDS_AON_GPIO_INT_TRIGGER_ASYNC_FALLING_EDGE = 8,  /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: async falling edge trigger */
    PDS_AON_GPIO_INT_TRIGGER_ASYNC_RISING_EDGE = 9,   /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: async rising edge trigger */
    PDS_AON_GPIO_INT_TRIGGER_ASYNC_LOW_LEVEL = 10,    /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: async low level trigger */
    PDS_AON_GPIO_INT_TRIGGER_ASYNC_HIGH_LEVEL = 11,   /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: async high level trigger */
} PDS_AON_GPIO_INT_Trigger_Type;

/**
 *  @brief PDS APP configuration type definition
 */
typedef struct
{
    uint8_t pdsLevel;                                 /*!< PDS level */
    uint8_t turnOffRF;                                /*!< Wheather turn off RF */
    uint8_t useXtal32k;                               /*!< Wheather use xtal 32K as 32K clock source,otherwise use rc32k */
    uint8_t pdsAonGpioWakeupSrc;                      /*!< PDS level 0/1/2/3 mode always on GPIO Wakeup source(HBN wakeup pin) */
    PDS_AON_GPIO_INT_Trigger_Type pdsAonGpioTrigType; /*!< PDS level 0/1/2/3 mode always on GPIO Triger type(HBN wakeup pin) */
    uint8_t powerDownFlash;                           /*!< Whether power down flash */
    uint8_t turnOffFlashPad;                          /*!< Whether turn off embedded flash pad */
    uint8_t ocramRetetion;                            /*!< Whether OCRAM Retention */
    uint8_t turnoffPLL;                               /*!< Whether trun off PLL */
    uint8_t xtalType;                                 /*!< XTal type, used when user choose turn off PLL, PDS will turn on when exit PDS mode */
    uint8_t flashContRead;                            /*!< Whether enable flash continue read */
    uint32_t sleepTime;                               /*!< PDS sleep time */
    SPI_Flash_Cfg_Type *flashCfg;                     /*!< Flash config pointer, used when power down flash */
    PDS_LDO_LEVEL_Type ldoLevel;                      /*!< LDO level */
    void (*preCbFun)(void);                           /*!< Pre callback function */
    void (*postCbFun)(void);                          /*!< Post callback function */
} PDS_APP_CFG_Type;

/*@} end of group PDS_Public_Types */

/** @defgroup  PDS_Public_Constants
 *  @{
 */

/** @defgroup  PDS_GPIO_INT_SET_TYPE
 *  @{
 */
#define IS_PDS_GPIO_INT_SET_TYPE(type) (((type) == PDS_GPIO_INT_SET_1_GPIO0_GPIO7) ||     \
                                        ((type) == PDS_GPIO_INT_SET_2_GPIO8_16_GPIO22) || \
                                        ((type) == PDS_GPIO_INT_SET_3_GPIO23_GPIO30) ||   \
                                        ((type) == PDS_GPIO_INT_SET_4_GPIO31_GPIO38))

/** @defgroup  GLB_GPIO_INT_TRIG_TYPE
 *  @{
 */
#define IS_PDS_GPIO_INT_TRIG_TYPE(type) (((type) == PDS_GPIO_INT_SYNC_FALLING_EDGE) ||        \
                                         ((type) == PDS_GPIO_INT_SYNC_RISING_EDGE) ||         \
                                         ((type) == PDS_GPIO_INT_SYNC_LOW_LEVEL) ||           \
                                         ((type) == PDS_GPIO_INT_SYNC_HIGH_LEVEL) ||          \
                                         ((type) == PDS_GPIO_INT_SYNC_RISING_FALLING_EDGE) || \
                                         ((type) == PDS_GPIO_INT_ASYNC_FALLING_EDGE) ||       \
                                         ((type) == PDS_GPIO_INT_ASYNC_RISING_EDGE) ||        \
                                         ((type) == PDS_GPIO_INT_ASYNC_LOW_LEVEL) ||          \
                                         ((type) == PDS_GPIO_INT_ASYNC_HIGH_LEVEL))

/** @defgroup  PDS_LP_SYS_CLK_TYPE
 *  @{
 */
#define IS_PDS_LP_SYS_CLK_TYPE(type) (((type) == PDS_LP_SYS_CLK_BCLK_DIV))

/** @defgroup  PDS_LDO_LEVEL_TYPE
 *  @{
 */
#define IS_PDS_LDO_LEVEL_TYPE(type) (((type) == PDS_LDO_LEVEL_0P70V) || \
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

/** @defgroup  PDS_INT_TYPE
 *  @{
 */
#define IS_PDS_INT_TYPE(type) (((type) == PDS_INT_WAKEUP) ||           \
                               ((type) == PDS_INT_RF_DONE) ||          \
                               ((type) == PDS_INT_WIFI_TBTT_SLEEP) ||  \
                               ((type) == PDS_INT_WIFI_TBTT_WAKEUP) || \
                               ((type) == PDS_INT_MAX))

/** @defgroup  PDS_AON_GPIO_INT_TRIGGER_TYPE
 *  @{
 */
#define IS_PDS_AON_GPIO_INT_TRIGGER_TYPE(type) (((type) == PDS_AON_GPIO_INT_TRIGGER_SYNC_FALLING_EDGE) ||   \
                                                ((type) == PDS_AON_GPIO_INT_TRIGGER_SYNC_RISING_EDGE) ||    \
                                                ((type) == PDS_AON_GPIO_INT_TRIGGER_SYNC_LOW_LEVEL) ||      \
                                                ((type) == PDS_AON_GPIO_INT_TRIGGER_SYNC_HIGH_LEVEL) ||     \
                                                ((type) == PDS_AON_GPIO_INT_TRIGGER_SYNC_RISING_FALLING) || \
                                                ((type) == PDS_AON_GPIO_INT_TRIGGER_ASYNC_FALLING_EDGE) ||  \
                                                ((type) == PDS_AON_GPIO_INT_TRIGGER_ASYNC_RISING_EDGE) ||   \
                                                ((type) == PDS_AON_GPIO_INT_TRIGGER_ASYNC_LOW_LEVEL) ||     \
                                                ((type) == PDS_AON_GPIO_INT_TRIGGER_ASYNC_HIGH_LEVEL))

/*@} end of group PDS_Public_Constants */

/** @defgroup  PDS_Public_Macros
 *  @{
 */
#define PDS_LDO_MIN_PU_CNT      (25) /* LDO need 25 cycles to power up */
#define PDS_WARMUP_LATENCY_CNT  (38) /* LDO hw warmup compensation latency cycles */
#define PDS_INT_MASK_BIT_OFFSET (4)

/*@} end of group PDS_Public_Macros */

/** @defgroup  PDS_Public_Functions
 *  @{
 */
/*----------*/
#ifndef BFLB_USE_HAL_DRIVER
void PDS_WAKEUP_IRQHandler(void);
#endif
BL_Err_Type PDS_Set_GPIO_Pad_Pn_Pu_Pd_Ie(GLB_GPIO_Type pad, uint8_t pu, uint8_t pd, uint8_t ie);
BL_Err_Type PDS_Set_GPIO_Pad_IntMask(GLB_GPIO_Type pad, BL_Mask_Type intMask);
BL_Err_Type PDS_Set_GPIO_Pad_IntMode(PDS_GPIO_INT_SET_Type set, PDS_GPIO_INT_TRIG_Type trig);
BL_Err_Type PDS_Set_GPIO_Pad_IntClr(PDS_GPIO_INT_SET_Type set);
BL_Sts_Type PDS_Get_GPIO_Pad_IntStatus(GLB_GPIO_Type pad);
BL_Err_Type PDS_Set_Flash_Pad_Pull_None(SF_Ctrl_Pin_Select pinCfg);
BL_Err_Type PDS_Set_Flash_Pad_Pull_None_Fast(SF_Ctrl_Pin_Select pinCfg);
BL_Err_Type PDS_Set_MCU0_Clock_Enable(void);
BL_Err_Type PDS_Set_MCU0_Clock_Disable(void);
BL_Err_Type PDS_Set_MCU0_Reset_Address(uint32_t addr);
BL_Err_Type PDS_Set_LP_Clock_Enable(void);
BL_Err_Type PDS_Set_LP_Clock_Disable(void);
BL_Err_Type PDS_Set_LP_System_CLK_Div(uint8_t div);
BL_Err_Type PDS_Set_LP_System_CLK(PDS_LP_SYS_CLK_Type clkFreq);
BL_Err_Type PDS_Reset_LP_RTC(void);
BL_Err_Type PDS_Set_LP_RTC_CLK(uint8_t enable, uint16_t div);
BL_Err_Type PDS_Set_LP_Reset_Address(uint32_t addr);
/*----------*/
BL_Sts_Type PDS_Get_MM_System_Power_On_State(void);
BL_Err_Type PDS_Power_On_MM_System(void);
/*----------*/
BL_Err_Type PDS_Enable(PDS_CTL_Type *cfg, PDS_CTL4_Type *cfg4, uint32_t pdsSleepCnt);
BL_Err_Type PDS_Force_Config(PDS_CTL2_Type *cfg2, PDS_CTL3_Type *cfg3, PDS_CTL5_Type *cfg5);
BL_Err_Type PDS_RAM_Config(PDS_CTRL_RAM1_Type *ram1Cfg, PDS_CTRL_RAM2_Type *ram2Cfg);
/*----------*/
BL_Err_Type PDS_Default_Level_Config(PDS_DEFAULT_LV_CFG_Type *defaultLvCfg, PDS_CTRL_RAM1_Type *ram1Cfg,
                                     PDS_CTRL_RAM2_Type *ram2Cfg, uint32_t pdsSleepCnt);
/*----------*/
BL_Err_Type PDS_IntMask(PDS_INT_Type intType, BL_Mask_Type intMask);
BL_Sts_Type PDS_Get_IntStatus(PDS_INT_Type intType);
BL_Err_Type PDS_IntClear(void);
BL_Err_Type PDS_Int_Callback_Install(PDS_INT_Type intType, intCallback_Type *cbFun);
/*----------*/
BL_Err_Type PDS_Trim_RC32M(void);
/*----------*/
BL_Err_Type PDS_Turn_On_USB(uint8_t waitReady);
BL_Err_Type PDS_Turn_Off_USB(void);
BL_Err_Type PDS_Set_USB_Suspend(void);
BL_Err_Type PDS_Set_USB_Resume(void);
/*----------*/

/*@} end of group PDS_Public_Functions */

/*@} end of group PDS */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_PDS_H__ */
