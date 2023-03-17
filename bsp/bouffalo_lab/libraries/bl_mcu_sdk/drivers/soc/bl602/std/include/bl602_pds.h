/**
  ******************************************************************************
  * @file    bl602_pds.h
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
#ifndef __BL602_PDS_H__
#define __BL602_PDS_H__

#include "pds_reg.h"
#include "bl602_aon.h"
#include "bl602_hbn.h"
#include "bl602_common.h"
#include "bflb_sflash.h"

/** @addtogroup  BL602_Peripheral_Driver
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
 *  @brief PDS configuration type definition
 */
typedef struct
{
    uint32_t pdsStart      : 1; /*!< [0]PDS Start */
    uint32_t sleepForever  : 1; /*!< [1]PDS sleep forever */
    uint32_t xtalForceOff  : 1; /*!< [2]Power off xtal force */
    uint32_t saveWiFiState : 1; /*!< [3]Save WIFI State Before Enter PDS */
    uint32_t dcdc18Off     : 1; /*!< [4]power down dcdc18 during PDS */
    uint32_t bgSysOff      : 1; /*!< [5]power down bg_sys during PDS */
    uint32_t rsv6_7        : 2; /*!< [7:6]reserve */
    uint32_t clkOff        : 1; /*!< [8]gate clock during PDS (each pwr domain has its own control) */
    uint32_t memStby       : 1; /*!< [9]mem_stby during PDS (each power domain can has its own control) */
    uint32_t rsv10         : 1; /*!< [10]reserve */
    uint32_t isolation     : 1; /*!< [11]Isolation during PDS (each power domain can has its own control) */
    uint32_t waitXtalRdy   : 1; /*!< [12]wait XTAL Ready during before PDS Interrupt */
    uint32_t pdsPwrOff     : 1; /*!< [13]Power off during PDS (each power domain can has its own control) */
    uint32_t xtalOff       : 1; /*!< [14]xtal power down during PDS */
    uint32_t socEnbForceOn : 1; /*!< [15]pds_soc_enb always active */
    uint32_t pdsRstSocEn   : 1; /*!< [16]pds_rst controlled by PDS */
    uint32_t pdsRC32mOn    : 1; /*!< [17]RC32M always on or RC32M on/off controlled by PDS state */
    uint32_t pdsLdoVselEn  : 1; /*!< [18]PDS "SLEEP" control LDO voltage enable */
    uint32_t rsv19_20      : 2; /*!< [20:19]reserve */
    uint32_t wfiMask       : 1; /*!< [21]pds start condition mask np_wfi */
    uint32_t ldo11Off      : 1; /*!< [22]power down ldo11 during PDS */
    uint32_t rsv23         : 1; /*!< [23]reserve */
    uint32_t pdsLdoVol     : 4; /*!< [27:24]LDO voltage value in PDS mode */
    uint32_t pdsCtlRfSel   : 2; /*!< [29:28]select the way RF controlled by PDS */
    uint32_t pdsCtlPllSel  : 2; /*!< [31:30]select the way PLL controlled by PDS */
} PDS_CTL_Type;

/**
 *  @brief PDS force configuration type definition
 */
typedef struct
{
    uint32_t cpuPwrOff   : 1; /*!< [0] */
    uint32_t cpuRst      : 1; /*!< [1] */
    uint32_t cpuMemStby  : 1; /*!< [2] */
    uint32_t cpuGateClk  : 1; /*!< [3] */
    uint32_t rsv4_11     : 8; /*!< [11:4]reserve */
    uint32_t WbPwrOff    : 1; /*!< [12] */
    uint32_t WbRst       : 1; /*!< [13] */
    uint32_t WbMemStby   : 1; /*!< [14] */
    uint32_t WbGateClk   : 1; /*!< [15] */
    uint32_t rsv16_23    : 8; /*!< [23:16]reserve */
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
    PDS_INT_WAKEUP = 0,                 /*!< PDS wakeup interrupt(assert bit while wakeup, include PDS_Timer/...) */
    PDS_INT_HBN_GPIO_IRRX_BLE_WIFI = 1, /*!< PDS in interrupt source HBN_Wakeup_Source/All_GPIO_Wakeup/IRRX/BLE_Wakeup_Eveent/WIFI_Wakeup_Event */
    PDS_INT_RF_DONE = 2,                /*!< PDS RF done interrupt */
    PDS_INT_PLL_DONE = 3,               /*!< PDS PLL done interrupt */
    PDS_INT_MAX = 4,                    /*!< PDS int max number */
} PDS_INT_Type;

/**
 *  @brief PDS force configuration type definition
 */
typedef struct
{
    uint32_t forceCpuPwrOff    : 1;  /*!< [0]manual force NP power off */
    uint32_t rsv1              : 1;  /*!< [1]reserve */
    uint32_t forceWbPwrOff     : 1;  /*!< [2]manual force WB power off */
    uint32_t rsv3              : 1;  /*!< [3]reserve */
    uint32_t forceCpuIsoPwrOff : 1;  /*!< [4]manual force NP isolation */
    uint32_t rsv5              : 1;  /*!< [5]reserve */
    uint32_t forceWbIsoPwrOff  : 1;  /*!< [6]manual force WB isolation */
    uint32_t rsv7              : 1;  /*!< [7]reserve */
    uint32_t forceCpuPdsRst    : 1;  /*!< [8]manual force NP pds reset */
    uint32_t rsv9              : 1;  /*!< [9]reserve */
    uint32_t forceWbPdsRst     : 1;  /*!< [10]manual force WB pds reset */
    uint32_t rsv11             : 1;  /*!< [11]reserve */
    uint32_t forceCpuMemStby   : 1;  /*!< [12]manual force NP memory sleep */
    uint32_t rsv13             : 1;  /*!< [13]reserve */
    uint32_t forceWbMemStby    : 1;  /*!< [14]manual force WB memory sleep */
    uint32_t rsv15             : 1;  /*!< [15]reserve */
    uint32_t forceCpuGateClk   : 1;  /*!< [16]manual force NP clock gated */
    uint32_t rsv17             : 1;  /*!< [17]reserve */
    uint32_t forceWbGateClk    : 1;  /*!< [18]manual force WB clock gated */
    uint32_t rsv19_31          : 12; /*!< [31:19]reserve */
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
    uint32_t rsv14_23         : 10; /*!< [23:14]reserve */
    uint32_t CpuIsoEn         : 1;  /*!< [24]make NP isolated at PDS Sleep state */
    uint32_t rsv25_26         : 2;  /*!< [26:25]reserve */
    uint32_t WbIsoEn          : 1;  /*!< [27]make WB isolated at PDS Sleep state */
    uint32_t rsv28_29         : 2;  /*!< [29:28]reserve */
    uint32_t MiscIsoEn        : 1;  /*!< [30]make misc isolated at PDS Sleep state */
    uint32_t rsv31            : 1;  /*!< [31]reserve */
} PDS_CTL3_Type;

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
    PDS_RF_STS_WB_EN_AON = 15, /*!< 4'b1111 */
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
 *  @brief PDS RAM configuration type definition
 */
typedef struct
{
    uint32_t PDS_RAM_CFG_0KB_16KB_CPU_RAM_RET  : 1;  /*!< [0]   0~16KB cpu_ram RET */
    uint32_t PDS_RAM_CFG_16KB_32KB_CPU_RAM_RET : 1;  /*!< [1]   16~32KB cpu_ram RET */
    uint32_t PDS_RAM_CFG_32KB_48KB_CPU_RAM_RET : 1;  /*!< [2]   32~48KB cpu_ram RET */
    uint32_t PDS_RAM_CFG_48KB_64KB_CPU_RAM_RET : 1;  /*!< [3]   48~64KB cpu_ram RET */
    uint32_t PDS_RAM_CFG_0KB_16KB_CPU_RAM_SLP  : 1;  /*!< [4]   0~16KB cpu_ram SLP */
    uint32_t PDS_RAM_CFG_16KB_32KB_CPU_RAM_SLP : 1;  /*!< [5]   16~32KB cpu_ram SLP */
    uint32_t PDS_RAM_CFG_32KB_48KB_CPU_RAM_SLP : 1;  /*!< [6]   32~48KB cpu_ram SLP */
    uint32_t PDS_RAM_CFG_48KB_64KB_CPU_RAM_SLP : 1;  /*!< [7]   48~64KB cpu_ram SLP */
    uint32_t PDS_RAM_CFG_RSV                   : 24; /*!< [31:8]reserve */
} PDS_RAM_CFG_Type;

/**
 *  @brief PLL XTAL type definition
 */
typedef enum {
    PDS_PLL_XTAL_NONE,  /*!< XTAL is none */
    PDS_PLL_XTAL_24M,   /*!< XTAL is 24M */
    PDS_PLL_XTAL_32M,   /*!< XTAL is 32M */
    PDS_PLL_XTAL_38P4M, /*!< XTAL is 38.4M */
    PDS_PLL_XTAL_40M,   /*!< XTAL is 40M */
    PDS_PLL_XTAL_26M,   /*!< XTAL is 26M */
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
 *  @brief PDS level 0/1/2/3 mode HBN GPIO interrupt trigger type definition
 */
typedef enum {
    PDS_AON_GPIO_INT_TRIGGER_SYNC_FALLING_EDGE,  /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: sync falling edge trigger */
    PDS_AON_GPIO_INT_TRIGGER_SYNC_RISING_EDGE,   /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: sync rising edge trigger */
    PDS_AON_GPIO_INT_TRIGGER_SYNC_LOW_LEVEL,     /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: sync low level trigger */
    PDS_AON_GPIO_INT_TRIGGER_SYNC_HIGH_LEVEL,    /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: sync high level trigger */
    PDS_AON_GPIO_INT_TRIGGER_ASYNC_FALLING_EDGE, /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: async falling edge trigger */
    PDS_AON_GPIO_INT_TRIGGER_ASYNC_RISING_EDGE,  /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: async rising edge trigger */
    PDS_AON_GPIO_INT_TRIGGER_ASYNC_LOW_LEVEL,    /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: async low level trigger */
    PDS_AON_GPIO_INT_TRIGGER_ASYNC_HIGH_LEVEL,   /*!< PDS level 0/1/2/3 mode HBN GPIO INT trigger type: async high level trigger */
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
    spi_flash_cfg_type *flashCfg;                     /*!< Flash config pointer, used when power down flash */
    PDS_LDO_LEVEL_Type ldoLevel;                      /*!< LDO level */
    void (*preCbFun)(void);                           /*!< Pre callback function */
    void (*postCbFun)(void);                          /*!< Post callback function */
} PDS_APP_CFG_Type;

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

/** @defgroup  PDS_INT_TYPE
 *  @{
 */
#define IS_PDS_INT_TYPE(type) (((type) == PDS_INT_WAKEUP) ||                 \
                               ((type) == PDS_INT_HBN_GPIO_IRRX_BLE_WIFI) || \
                               ((type) == PDS_INT_RF_DONE) ||                \
                               ((type) == PDS_INT_PLL_DONE) ||               \
                               ((type) == PDS_INT_MAX))

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
                                  ((type) == PDS_RF_STS_WB_EN_AON))

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
#define IS_PDS_PLL_XTAL_TYPE(type) (((type) == PDS_PLL_XTAL_NONE) ||  \
                                    ((type) == PDS_PLL_XTAL_24M) ||   \
                                    ((type) == PDS_PLL_XTAL_32M) ||   \
                                    ((type) == PDS_PLL_XTAL_38P4M) || \
                                    ((type) == PDS_PLL_XTAL_40M) ||   \
                                    ((type) == PDS_PLL_XTAL_26M) ||   \
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

/*@} end of group PDS_Public_Constants */

/** @defgroup  PDS_Public_Macros
 *  @{
 */
#define PDS_LDO_MIN_PU_CNT        (25) /* LDO need 25 cycles to power up */
#define PDS_WARMUP_LATENCY_CNT    (38) /* LDO hw warmup compensation latency cycles */
#define PDS_FORCE_PWR_OFF_OFFSET  (0)
#define PDS_FORCE_ISO_EN_OFFSET   (4)
#define PDS_FORCE_PDS_RST_OFFSET  (8)
#define PDS_FORCE_MEM_STBY_OFFSET (12)
#define PDS_FORCE_GATE_CLK_OFFSET (16)
#define PDS_INT_MASK_BIT_OFFSET   (8)
#define PDS_AON_WAKEUP_GPIO_NONE  (0x00)
#define PDS_AON_WAKEUP_GPIO_7     (0x01)
#define PDS_AON_WAKEUP_GPIO_8     (0x02)
#define PDS_AON_WAKEUP_GPIO_ALL   (0x03)

/*@} end of group PDS_Public_Macros */

/** @defgroup  PDS_Public_Functions
 *  @{
 */
/*----------*/
#ifndef BFLB_USE_HAL_DRIVER
void PDS_WAKEUP_IRQHandler(void);
#endif
/*----------*/
BL_Err_Type PDS_Reset(void);
BL_Err_Type PDS_Enable(PDS_CTL_Type *cfg, PDS_CTL4_Type *cfg4, uint32_t pdsSleepCnt);
BL_Err_Type PDS_Force_Config(PDS_CTL2_Type *cfg2, PDS_CTL3_Type *cfg3);
BL_Err_Type PDS_RAM_Config(PDS_RAM_CFG_Type *ramCfg);
/*----------*/
BL_Err_Type PDS_Default_Level_Config(PDS_DEFAULT_LV_CFG_Type *defaultLvCfg,
                                     PDS_RAM_CFG_Type *ramCfg, uint32_t pdsSleepCnt);
/*----------*/
BL_Err_Type PDS_IntMask(PDS_INT_Type intType, BL_Mask_Type intMask);
BL_Sts_Type PDS_Get_IntStatus(PDS_INT_Type intType);
BL_Err_Type PDS_IntClear(void);
PDS_PLL_STS_Type PDS_Get_PdsPllStstus(void);
PDS_RF_STS_Type PDS_Get_PdsRfStstus(void);
PDS_STS_Type PDS_Get_PdsStstus(void);
BL_Err_Type PDS_WAKEUP_IRQHandler_Install(void);
BL_Err_Type PDS_Int_Callback_Install(PDS_INT_Type intType, intCallback_Type *cbFun);
/*----------*/
BL_Err_Type PDS_Trim_RC32M(void);
BL_Err_Type PDS_Select_RC32M_As_PLL_Ref(void);
BL_Err_Type PDS_Select_XTAL_As_PLL_Ref(void);
BL_Err_Type PDS_Power_On_PLL(PDS_PLL_XTAL_Type xtalType);
BL_Err_Type PDS_Fix_Xtal_Settig(void);
BL_Err_Type PDS_Enable_PLL_All_Clks(void);
BL_Err_Type PDS_Enable_PLL_Clk(PDS_PLL_CLK_Type pllClk);
BL_Err_Type PDS_Disable_PLL_All_Clks(void);
BL_Err_Type PDS_Disable_PLL_Clk(PDS_PLL_CLK_Type pllClk);
BL_Err_Type PDS_Power_Off_PLL(void);
/*----------*/;

/*@} end of group PDS_Public_Functions */

/*@} end of group PDS */

/*@} end of group BL602_Peripheral_Driver */

#endif /* __BL602_PDS_H__ */
