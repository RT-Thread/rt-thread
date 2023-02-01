/**
 * @file hal_pm.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "hal_pm.h"
#include "bl808.h"
#include "bl808_hbn.h"
#include "bl808_pds.h"
#include "hal_flash.h"
#include "hal_rtc.h"

#define PM_PDS_GPIO_KEEP_EN       0
#define PM_HBN_GPIO_KEEP_EN       0
#define PM_PDS_FLASH_POWER_OFF    1
#define PM_PDS_DLL_POWER_OFF      1
#define PM_PDS_PLL_POWER_OFF      1
#define PM_PDS_RF_POWER_OFF       1
#define PM_PDS_LDO_LEVEL_DEFAULT  HBN_LDO_LEVEL_1P10V
#define PM_PDS_DCDC_LEVEL_DEFAULT AON_DCDC_LEVEL_1P100V
#define PM_HBN_LDO_LEVEL_DEFAULT  HBN_LDO_LEVEL_0P90V

/* Cache Way Disable, will get from l1c register */
uint8_t cacheWayDisable = 0;

/* PSRAM IO Configuration, will get from glb register */
uint32_t psramIoCfg = 0;

/* Flash offset value, will get from sf_ctrl register */
uint32_t flash_offset = 0;

SPI_Flash_Cfg_Type *flash_cfg;

static PDS_DEFAULT_LV_CFG_Type ATTR_TCM_CONST_SECTION pdsCfgLevel1 = {
    .pdsCtl = {
        .pdsStart = 1,
        .sleepForever = 0,
        .xtalForceOff = 0,
        .saveWiFiState = 0,
        .dcdc11Off = 0,
        .bgSysOff = 0,
        .ctrlGpioIePuPd = 0,
        .dcdc18Off = 1,
        .clkOff = 1,
        .memStby = 1,
        .glbRstProtect = 0,
        .isolation = 1,
        .waitXtalRdy = 0,
        .pdsPwrOff = 1,
        .xtalOff = 1,
        .socEnbForceOn = 0,
        .pdsRstSocEn = 0,
        .pdsRC32mOn = 0,
        .pdsDcdc11VselEn = 1,
        .usbpllOff = 0,
        .aupllOff = 1,
        .cpupllOff = 1,
        .wifipllOff = 1,
        .pdsDcdc11Vsel = 0x08,
        .pdsCtlRfSel = 3,
        .pdsUseTbttSlp = 0,
        .pdsGpioIsoMod = 0,
    },
    .pdsCtl2 = {
        .forceDspPwrOff = 0,
        .forceUsbPwrOff = 0,
        .forceDspIso = 0,
        .forceUsbIso = 0,
        .forceMcuPdsRst = 0,
        .forceDspPdsRst = 0,
        .forceWbPdsRst = 0,
        .forceUsbPdsRst = 0,
        .forceMcuMemStby = 0,
        .forceDspMemStby = 0,
        .forceWbMemStby = 0,
        .forceUsbMemStby = 0,
        .forceMcuGateClk = 0,
        .forceDspGateClk = 0,
        .forceWbGateClk = 0,
        .forceUsbGateClk = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff = 0,
        .forceMiscIsoEn = 0,
        .forceMiscPdsRst = 0,
        .forceMiscMemStby = 0,
        .forceMiscGateClk = 0,
        .DspIsoEn = 1,
        .UsbIsoEn = 0,
        .MiscIsoEn = 0,
    },
    .pdsCtl4 = {
        .mcuRst = 0,
        .mcuMemStby = 0,
        .mcuGateClk = 0,
        .dspPwrOff = 1,
        .dspRst = 1,
        .dspMemStby = 1,
        .dspGateClk = 1,
        .WbRst = 0,
        .WbMemStby = 0,
        .WbGateClk = 0,
        .usbPwrOff = 0,
        .usbRst = 0,
        .usbMemStby = 0,
        .usbGateClk = 0,
        .MiscPwrOff = 0,
        .MiscRst = 0,
        .MiscMemStby = 0,
        .MiscGateClk = 0,
    },
    .pdsCtl5 = {
        .McuWfiMask = 0,
        .DspWfiMask = 1,
        .LpWfiMask = 1,
        .ctrlUsb33 = 1,
        .pdLdo18io = 1,
        .gpioKeepEn = 7,
    }
};

static PDS_DEFAULT_LV_CFG_Type ATTR_TCM_CONST_SECTION pdsCfgLevel2 = {
    .pdsCtl = {
        .pdsStart = 1,
        .sleepForever = 0,
        .xtalForceOff = 0,
        .saveWiFiState = 0,
        .dcdc11Off = 0,
        .bgSysOff = 0,
        .ctrlGpioIePuPd = 0,
        .dcdc18Off = 1,
        .clkOff = 1,
        .memStby = 1,
        .glbRstProtect = 0,
        .isolation = 1,
        .waitXtalRdy = 0,
        .pdsPwrOff = 1,
        .xtalOff = 1,
        .socEnbForceOn = 0,
        .pdsRstSocEn = 0,
        .pdsRC32mOn = 0,
        .pdsDcdc11VselEn = 1,
        .usbpllOff = 1,
        .aupllOff = 1,
        .cpupllOff = 1,
        .wifipllOff = 1,
        .pdsDcdc11Vsel = 0x08,
        .pdsCtlRfSel = 3,
        .pdsUseTbttSlp = 0,
        .pdsGpioIsoMod = 0,
    },
    .pdsCtl2 = {
        .forceDspPwrOff = 0,
        .forceUsbPwrOff = 0,
        .forceDspIso = 0,
        .forceUsbIso = 0,
        .forceMcuPdsRst = 0,
        .forceDspPdsRst = 0,
        .forceWbPdsRst = 0,
        .forceUsbPdsRst = 0,
        .forceMcuMemStby = 0,
        .forceDspMemStby = 0,
        .forceWbMemStby = 0,
        .forceUsbMemStby = 0,
        .forceMcuGateClk = 0,
        .forceDspGateClk = 0,
        .forceWbGateClk = 0,
        .forceUsbGateClk = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff = 0,
        .forceMiscIsoEn = 0,
        .forceMiscPdsRst = 0,
        .forceMiscMemStby = 0,
        .forceMiscGateClk = 0,
        .DspIsoEn = 0,
        .UsbIsoEn = 1,
        .MiscIsoEn = 0,
    },
    .pdsCtl4 = {
        .mcuRst = 0,
        .mcuMemStby = 0,
        .mcuGateClk = 0,
        .dspPwrOff = 0,
        .dspRst = 0,
        .dspMemStby = 0,
        .dspGateClk = 0,
        .WbRst = 0,
        .WbMemStby = 0,
        .WbGateClk = 0,
        .usbPwrOff = 1,
        .usbRst = 1,
        .usbMemStby = 1,
        .usbGateClk = 1,
        .MiscPwrOff = 0,
        .MiscRst = 0,
        .MiscMemStby = 0,
        .MiscGateClk = 0,
    },
    .pdsCtl5 = {
        .McuWfiMask = 0,
        .DspWfiMask = 1,
        .LpWfiMask = 1,
        .ctrlUsb33 = 1,
        .pdLdo18io = 1,
        .gpioKeepEn = 7,
    }
};

static PDS_DEFAULT_LV_CFG_Type ATTR_TCM_CONST_SECTION pdsCfgLevel3 = {
    .pdsCtl = {
        .pdsStart = 1,
        .sleepForever = 0,
        .xtalForceOff = 0,
        .saveWiFiState = 0,
        .dcdc11Off = 0,
        .bgSysOff = 0,
        .ctrlGpioIePuPd = 0,
        .dcdc18Off = 1,
        .clkOff = 1,
        .memStby = 1,
        .glbRstProtect = 0,
        .isolation = 1,
        .waitXtalRdy = 0,
        .pdsPwrOff = 1,
        .xtalOff = 1,
        .socEnbForceOn = 0,
        .pdsRstSocEn = 0,
        .pdsRC32mOn = 0,
        .pdsDcdc11VselEn = 1,
        .usbpllOff = 1,
        .aupllOff = 1,
        .cpupllOff = 1,
        .wifipllOff = 1,
        .pdsDcdc11Vsel = 0x08,
        .pdsCtlRfSel = 3,
        .pdsUseTbttSlp = 0,
        .pdsGpioIsoMod = 0,
    },
    .pdsCtl2 = {
        .forceDspPwrOff = 0,
        .forceUsbPwrOff = 0,
        .forceDspIso = 0,
        .forceUsbIso = 0,
        .forceMcuPdsRst = 0,
        .forceDspPdsRst = 0,
        .forceWbPdsRst = 0,
        .forceUsbPdsRst = 0,
        .forceMcuMemStby = 0,
        .forceDspMemStby = 0,
        .forceWbMemStby = 0,
        .forceUsbMemStby = 0,
        .forceMcuGateClk = 0,
        .forceDspGateClk = 0,
        .forceWbGateClk = 0,
        .forceUsbGateClk = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff = 0,
        .forceMiscIsoEn = 0,
        .forceMiscPdsRst = 0,
        .forceMiscMemStby = 0,
        .forceMiscGateClk = 0,
        .DspIsoEn = 1,
        .UsbIsoEn = 1,
        .MiscIsoEn = 0,
    },
    .pdsCtl4 = {
        .mcuRst = 0,
        .mcuMemStby = 0,
        .mcuGateClk = 0,
        .dspPwrOff = 1,
        .dspRst = 1,
        .dspMemStby = 1,
        .dspGateClk = 1,
        .WbRst = 0,
        .WbMemStby = 0,
        .WbGateClk = 0,
        .usbPwrOff = 1,
        .usbRst = 1,
        .usbMemStby = 1,
        .usbGateClk = 1,
        .MiscPwrOff = 0,
        .MiscRst = 0,
        .MiscMemStby = 0,
        .MiscGateClk = 0,
    },
    .pdsCtl5 = {
        .McuWfiMask = 0,
        .DspWfiMask = 1,
        .LpWfiMask = 1,
        .ctrlUsb33 = 1,
        .pdLdo18io = 1,
        .gpioKeepEn = 7,
    }
};

static PDS_DEFAULT_LV_CFG_Type ATTR_TCM_CONST_SECTION pdsCfgLevel7 = {
    .pdsCtl = {
        .pdsStart = 1,
        .sleepForever = 0,
        .xtalForceOff = 1,
        .saveWiFiState = 0,
        .dcdc11Off = 1,
        .bgSysOff = 1,
        .ctrlGpioIePuPd = 0,
        .dcdc18Off = 1,
        .clkOff = 1,
        .memStby = 1,
        .glbRstProtect = 0,
        .isolation = 1,
        .waitXtalRdy = 0,
        .pdsPwrOff = 1,
        .xtalOff = 1,
        .socEnbForceOn = 0,
        .pdsRstSocEn = 0,
        .pdsRC32mOn = 0,
        .pdsDcdc11VselEn = 0,
        .usbpllOff = 1,
        .aupllOff = 1,
        .cpupllOff = 1,
        .wifipllOff = 1,
        .pdsDcdc11Vsel = 0,
        .pdsCtlRfSel = 1,
        .pdsUseTbttSlp = 0,
        .pdsGpioIsoMod = 1,
    },
    .pdsCtl2 = {
        .forceDspPwrOff = 0,
        .forceUsbPwrOff = 0,
        .forceDspIso = 0,
        .forceUsbIso = 0,
        .forceMcuPdsRst = 0,
        .forceDspPdsRst = 0,
        .forceWbPdsRst = 0,
        .forceUsbPdsRst = 0,
        .forceMcuMemStby = 0,
        .forceDspMemStby = 0,
        .forceWbMemStby = 0,
        .forceUsbMemStby = 0,
        .forceMcuGateClk = 0,
        .forceDspGateClk = 0,
        .forceWbGateClk = 0,
        .forceUsbGateClk = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff = 0,
        .forceMiscIsoEn = 0,
        .forceMiscPdsRst = 0,
        .forceMiscMemStby = 0,
        .forceMiscGateClk = 0,
        .DspIsoEn = 1,
        .UsbIsoEn = 1,
        .MiscIsoEn = 1,
    },
    .pdsCtl4 = {
        .mcuRst = 1,
        .mcuMemStby = 1,
        .mcuGateClk = 1,
        .dspPwrOff = 1,
        .dspRst = 1,
        .dspMemStby = 1,
        .dspGateClk = 1,
        .WbRst = 1,
        .WbMemStby = 1,
        .WbGateClk = 1,
        .usbPwrOff = 1,
        .usbRst = 1,
        .usbMemStby = 1,
        .usbGateClk = 1,
        .MiscPwrOff = 1,
        .MiscRst = 1,
        .MiscMemStby = 1,
        .MiscGateClk = 1,
    },
    .pdsCtl5 = {
        .McuWfiMask = 0,
        .DspWfiMask = 1,
        .LpWfiMask = 1,
        .ctrlUsb33 = 1,
        .pdLdo18io = 1,
        .gpioKeepEn = 0,
    }
};

static void pm_hbn_rtc_rst_disable(void)
{
    HBN_RTC_MISC_Type rtcMiscCfg;

    HBN_Get_RTC_Misc_Cfg(&rtcMiscCfg);
    rtcMiscCfg.rtcRstEnRtc = 0;
    HBN_Set_RTC_Misc_Cfg(&rtcMiscCfg);
}

/******************************************************************************
 * @brief  set power down sleep VDDCORE gpio interrupt mask
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
 *******************************************************************************/
static BL_Err_Type pm_clr_pds_gpio_int(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PDS_BASE, PDS_GPIO_INT);
    // PDS_GPIO_INT_SET_1_GPIO0_GPIO7:
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_GPIO_SET1_INT_CLR);
    // PDS_GPIO_INT_SET_2_GPIO8_16_GPIO22:
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_GPIO_SET2_INT_CLR);
    // PDS_GPIO_INT_SET_3_GPIO23_GPIO30:
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_GPIO_SET3_INT_CLR);
    // PDS_GPIO_INT_SET_4_GPIO31_GPIO38:
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_GPIO_SET4_INT_CLR);

    BL_WR_REG(PDS_BASE, PDS_GPIO_INT, tmpVal);
    return SUCCESS;
}

void pm_pds_mask_all_wakeup_src(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CR_PDS_WAKEUP_SRC_EN);
    BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);
}

static void pm_pds_intc_clr(void)
{
    pm_clr_pds_gpio_int();
    PDS_IntClear();
}

/**
 * @brief power management in pds(power down sleep) mode
 *
 * cpu's behavior after wakeup depend on psd level,see flow table if cpu off ,
 * cpu will reset after wakeup
 *
 *      PD_AON_RTC  PD_AON   PD_AON_HBNCORE  PD_CORE  PD_CORE_MISC PD_USB PD_DSP
 * PDS0    ON          ON         ON            ON        ON         ON     ON
 * PDS1    ON          ON         ON            ON        ON         ON     OFF
 * PDS2    ON          ON         ON            ON        ON         OFF    ON
 * PDS3    ON          ON         ON            ON        ON         OFF    OFF
 * PDS7    ON          ON         ON            ON        OFF        OFF    OFF
 */
void ATTR_TCM_SECTION pm_pds_mode_enter(enum pm_pds_sleep_level pds_level,
                                        uint32_t sleep_time)
{
    PDS_DEFAULT_LV_CFG_Type *pPdsCfg = NULL;
    uint32_t tmpVal;
    uint32_t flash_cfg_len;
    uint32_t pds_ram1;
    uint32_t pds_ram2;

    /* To make it simple and safe*/
    cpu_global_irq_disable();

    pm_hbn_rtc_rst_disable();

    flash_get_cfg((uint8_t **)&flash_cfg, &flash_cfg_len);

    HBN_Set_Ldo11_All_Vout(PM_PDS_LDO_LEVEL_DEFAULT);
    AON_Set_DCDC11_Top_Vout(PM_PDS_DCDC_LEVEL_DEFAULT);
    /************************ PDS INT SET ***********************/
    // PDS_WAKEUP_IRQHandler_Install();
    BL_WR_REG(HBN_BASE, HBN_IRQ_CLR, 0xffffffff);
    BL_WR_REG(HBN_BASE, HBN_IRQ_CLR, 0);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);

    if (sleep_time) {
        tmpVal |= (1 << 10); // unmask pds sleep time wakeup
    }

    BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

    /* clear all interrupt status */
    pm_pds_intc_clr();

    /* enable PDS interrupt to wakeup CPU (PDS1:CPU not powerdown, CPU __WFI)*/
    pm_pds_irq_register();
    /***********************************************************/

    switch (pds_level) {
        case PM_PDS_LEVEL_1:
            pPdsCfg = &pdsCfgLevel1;
            break;
        case PM_PDS_LEVEL_2:
            pPdsCfg = &pdsCfgLevel2;
            break;
        case PM_PDS_LEVEL_3:
            pPdsCfg = &pdsCfgLevel3;
            break;
        case PM_PDS_LEVEL_7:
            pPdsCfg = &pdsCfgLevel7;
            break;
        default:
            return;
    }

#if PM_PDS_FLASH_POWER_OFF
    uint32_t sw_cfg0 = 0;
    SF_Ctrl_Pin_Select sf_pin_select = 0;

    /* get sw uasge 0 */
    EF_Ctrl_Read_Sw_Usage(0, (uint32_t *)&sw_cfg0);
    sf_pin_select = (tmpVal >> 14) & 0x3f;
    flash_get_cfg((uint8_t **)&flash_cfg, &flash_cfg_len);

    HBN_Power_Down_Flash(flash_cfg);

    /* LDO_FLASH Pull down */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_LDO18FLASH);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_PU_LDO18FLASH);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_LDO18FLASH_PULLDOWN);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_LDO18FLASH_PULLDOWN_SEL);
    BL_WR_REG(GLB_BASE, GLB_LDO18FLASH, tmpVal);

    /* Turn Off Flash PAD IE */
    /* GPIO46~51 */
    for (int i = 0; i < 6; i++) {
        BL_WR_WORD(GLB_BASE + GLB_GPIO_CFG46_OFFSET + i * 4, 0);
    }

    /* Turn Off PSRAM PAD IE */
    /* GPIO52~63 */
    for (int i = 0; i < 12; i++) {
        BL_WR_WORD(GLB_BASE + GLB_GPIO_CFG52_OFFSET + i * 4, 0);
    }
#endif

#if PM_PDS_GPIO_KEEP_EN
    pPdsCfg->pdsCtl.pdsGpioIsoMod = 1;
    pPdsCfg->pdsCtl5.gpioKeepEn = 7;
#endif

#if PM_PDS_PLL_POWER_OFF
    /*************************** Clock Config **************************/
    GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_RC32M); // MCU CLK SELECT RC32M
    GLB_Set_DSP_System_CLK(GLB_DSP_SYS_CLK_RC32M);

    GLB_Power_Off_WAC_PLL(GLB_WAC_PLL_CPUPLL);
    GLB_Power_Off_WAC_PLL(GLB_WAC_PLL_WIFIPLL);
    GLB_Power_Off_WAC_PLL(GLB_WAC_PLL_AUPLL);

    /* Power Down Mipi PLL */
    GLB_Power_Off_MU_PLL(GLB_MU_PLL_MIPIPLL);
    /* Power Down UHS(PSRAM) PLL */
    GLB_Power_Off_MU_PLL(GLB_MU_PLL_UHSPLL);

    // GLB_Set_SF_CLK(1, GLB_SFLASH_CLK_BCLK, 0);
    tmpVal = BL_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal |= (0x3 << 9);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);
    /**************************************************************/
#endif

#if PM_PDS_RF_POWER_OFF == 0
    pPdsCfg->pdsCtl.pdsCtlRfSel = 0;
#endif

    if (0xFFFFFFFF != BL_RD_REG(PDS_BASE, PDS_GPIO_PD_SET)) {
        pPdsCfg->pdsCtl.ctrlGpioIePuPd = 1;
    }

    /* LDO12_UHS Pull down */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_LDO12UHS);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_PU_LDO12UHS);
    BL_WR_REG(GLB_BASE, GLB_LDO12UHS, tmpVal);

    /* LDO15_CIS Pull down */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_LDO15CIS);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_PU_LDO15CIS);
    BL_WR_REG(GLB_BASE, GLB_LDO15CIS, tmpVal);

    /* DCDC18 Pull down When disable */
    tmpVal = BL_RD_REG(AON_BASE, AON_DCDC18_TOP_1);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_DCDC18_PULLDOWN_AON);
    BL_WR_REG(AON_BASE, AON_DCDC18_TOP_1, tmpVal);

    /* LDO28_CIS Pull down */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_LDO28CIS);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_PU_LDO28CIS);
    BL_WR_REG(GLB_BASE, GLB_LDO28CIS, tmpVal);

    pds_ram1 = BL_RD_REG(PDS_BASE, PDS_RAM1);
    pds_ram2 = BL_RD_REG(PDS_BASE, PDS_RAM2);

    /* PD_CORE's SRAM Clock Gating During PDS Mode */
    pds_ram1 |= (1 << 31);

    if (pds_level == PM_PDS_LEVEL_7) {
        pds_ram1 &= ~(0xf < 4);   // ocram retention
        pds_ram1 |= 0xf;          // ocram sleep
        pds_ram2 &= ~(0x3ff < 9); // wram retention
        pds_ram2 |= (0x380 < 9);  // wram retention
        pds_ram2 &= ~0x3ff;
        pds_ram2 |= 0x7f; // wram sleep
    }

    PDS_Default_Level_Config(pPdsCfg, (PDS_CTRL_RAM1_Type *)&pds_ram1,
                             (PDS_CTRL_RAM2_Type *)&pds_ram2, sleep_time);

    __WFI();

    /****************************** Wakeup Flow *******************************/
    HBN_Set_Ldo11_All_Vout(HBN_LDO_LEVEL_1P10V);
    AON_Set_DCDC11_Top_Vout(AON_DCDC_LEVEL_1P100V);

    /* LDO28_CIS Pull On */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_LDO28CIS);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_PU_LDO28CIS);
    BL_WR_REG(GLB_BASE, GLB_LDO28CIS, tmpVal);

    /* DCDC18 Pull On*/
    tmpVal = BL_RD_REG(AON_BASE, AON_DCDC18_TOP_1);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_DCDC18_PULLDOWN_AON);
    BL_WR_REG(AON_BASE, AON_DCDC18_TOP_1, tmpVal);

    /* LDO15_CIS Pull On */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_LDO15CIS);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_PU_LDO15CIS);
    BL_WR_REG(GLB_BASE, GLB_LDO15CIS, tmpVal);

    /* LDO12_UHS Pull On */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_LDO12UHS);
    tmpVal = BL_SET_REG_BIT(tmpVal, GLB_PU_LDO12UHS);
    BL_WR_REG(GLB_BASE, GLB_LDO12UHS, tmpVal);

#if PM_PDS_PLL_POWER_OFF
    GLB_Power_On_XTAL_And_PLL_CLK(GLB_XTAL_40M, GLB_PLL_WIFIPLL);
    GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_WIFIPLL_320M);
    GLB_Set_DSP_System_CLK(GLB_DSP_SYS_CLK_CPUPLL_400M);
#endif

#if PM_PDS_FLASH_POWER_OFF
    if (pds_level <= PM_PDS_LEVEL_3) {
        /* Init flash gpio */
        SF_Cfg_Init_Ext_Flash_Gpio(0);
        SF_Cfg_Init_Flash_Gpio(sf_pin_select, 1);
        SF_Ctrl_Set_Owner(SF_CTRL_OWNER_SAHB);
        SFlash_Restore_From_Powerdown(flash_cfg, 0, SF_CTRL_FLASH_BANK0);
    }
#endif

    cpu_global_irq_enable();
}

/**
 * @brief
 *
 * power management in hbn(hibernation) mode
 * cpu will reset after wakeup
 *
 * HBN_LEVEL PD_AON_RTC PD_AON PD_AON_HBNCORE PD_CORE&PD_CORE_MISC&PD_USB&PD_MM
 * HBN0          ON       ON        ON                     OFF
 * HBN1          ON       ON        OFF                    OFF
 * HBN2          ON       OFF       OFF                    OFF
 *
 * @param hbn_level
 */
void ATTR_TCM_SECTION pm_hbn_mode_enter(enum pm_hbn_sleep_level hbn_level,
                                        uint8_t sleep_time)
{
    uint32_t tmpVal;

    /* To make it simple and safe*/
    cpu_global_irq_disable();

    CPU_Interrupt_Pending_Clear(HBN_OUT0_IRQn);
    CPU_Interrupt_Pending_Clear(HBN_OUT1_IRQn);

    BL_WR_REG(HBN_BASE, HBN_IRQ_CLR, 0xffffffff);
    BL_WR_REG(HBN_BASE, HBN_IRQ_CLR, 0);

    if (sleep_time) {
        rtc_init(sleep_time); // sleep time,unit is second
    }

    if (hbn_level >= PM_HBN_LEVEL_2) {
        HBN_PD_RC32K_In_Poff();
    }

#if PM_PDS_FLASH_POWER_OFF
    HBN_Power_Down_Flash(NULL);
#endif

#if PM_HBN_GPIO_KEEP_EN
    tmpVal = BL_RD_REG(HBN_BASE, HBN_PAD_CTRL_0);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_REG_AON_GPIO_ISO_MODE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_REG_EN_AON_CTRL_GPIO);
    BL_WR_REG(HBN_BASE, HBN_PAD_CTRL_0, tmpVal);
#endif

    /* Select RC32M */
    // GLB_Set_System_CLK(GLB_DLL_XTAL_NONE, GLB_SYS_CLK_RC32M);
    GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_RC32M);
    /* power off pll */
    GLB_Power_Off_MU_PLL(GLB_MU_PLL_MIPIPLL);
    GLB_Power_Off_MU_PLL(GLB_MU_PLL_UHSPLL);
    /* power off xtal */
    AON_Power_Off_XTAL();

    /* HBN mode LDO level */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_LDO11_AON_VOUT_SEL,
                                 PM_HBN_LDO_LEVEL_DEFAULT);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_LDO11_RT_VOUT_SEL,
                                 PM_HBN_LDO_LEVEL_DEFAULT);
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    /* Set HBN flag */
    BL_WR_REG(HBN_BASE, HBN_RSV0, HBN_STATUS_ENTER_FLAG);

    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);

    /* Set HBN level, (HBN_PWRDN_HBN_RAM not use) */
    if (hbn_level < PM_HBN_LEVEL_1) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PWRDN_HBN_CORE);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, HBN_PWRDN_HBN_CORE);
    }

    /* Set power on option:0 for por reset twice for robust 1 for reset only
   * once*/
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PWR_ON_OPTION);
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    /* Enable HBN mode */
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_MODE);
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    while (1) {
        arch_delay_ms(100);
        GLB_SW_POR_Reset();
    }
}

void pm_hbn_out0_irq_register(void)
{
    Interrupt_Handler_Register(HBN_OUT0_IRQn, HBN_OUT0_IRQ);
    CPU_Interrupt_Enable(HBN_OUT0_IRQn);
}

void pm_hbn_out1_irq_register(void)
{
    Interrupt_Handler_Register(HBN_OUT1_IRQn, HBN_OUT1_IRQ);
    CPU_Interrupt_Enable(HBN_OUT1_IRQn);
}

void HBN_OUT0_IRQ(void)
{
    if (SET == HBN_Get_INT_State(HBN_INT_GPIO9)) {
        HBN_Clear_IRQ(HBN_INT_GPIO9);
        pm_irq_callback(PM_HBN_GPIO9_WAKEUP_EVENT);
    } else if (SET == HBN_Get_INT_State(HBN_INT_GPIO10)) {
        HBN_Clear_IRQ(HBN_INT_GPIO10);
        pm_irq_callback(PM_HBN_GPIO10_WAKEUP_EVENT);
    } else if (SET == HBN_Get_INT_State(HBN_INT_GPIO11)) {
        HBN_Clear_IRQ(HBN_INT_GPIO11);
        pm_irq_callback(PM_HBN_GPIO11_WAKEUP_EVENT);
    } else if (SET == HBN_Get_INT_State(HBN_INT_GPIO12)) {
        HBN_Clear_IRQ(HBN_INT_GPIO12);
        pm_irq_callback(PM_HBN_GPIO12_WAKEUP_EVENT);
    } else if (SET == HBN_Get_INT_State(HBN_INT_GPIO13)) {
        HBN_Clear_IRQ(HBN_INT_GPIO13);
        pm_irq_callback(PM_HBN_GPIO13_WAKEUP_EVENT);
    } else if (SET == HBN_Get_INT_State(HBN_INT_GPIO14)) {
        HBN_Clear_IRQ(HBN_INT_GPIO14);
        pm_irq_callback(PM_HBN_GPIO14_WAKEUP_EVENT);
    } else if (SET == HBN_Get_INT_State(HBN_INT_GPIO15)) {
        HBN_Clear_IRQ(HBN_INT_GPIO15);
        pm_irq_callback(PM_HBN_GPIO15_WAKEUP_EVENT);
    } else if (SET == HBN_Get_INT_State(HBN_INT_GPIO40)) {
        HBN_Clear_IRQ(HBN_INT_GPIO40);
        pm_irq_callback(PM_HBN_GPIO40_WAKEUP_EVENT);
    } else if (SET == HBN_Get_INT_State(HBN_INT_GPIO41)) {
        HBN_Clear_IRQ(HBN_INT_GPIO41);
        pm_irq_callback(PM_HBN_GPIO41_WAKEUP_EVENT);
    } else {
        HBN_Clear_IRQ(HBN_INT_RTC);
        HBN_Clear_RTC_INT();
        pm_irq_callback(PM_HBN_RTC_WAKEUP_EVENT);
    }
}

void ATTR_TCM_SECTION HBN_OUT1_IRQ(void)
{
    /* PIR */
    if (SET == HBN_Get_INT_State(HBN_INT_PIR)) {
        HBN_Clear_IRQ(HBN_INT_PIR);
    }
    /* BOR */
    else if (SET == HBN_Get_INT_State(HBN_INT_BOD)) {
        HBN_Clear_IRQ(HBN_INT_BOD);
        pm_irq_callback(PM_HBN_BOD_WAKEUP_EVENT);
    }
    /* ACOMP0 */
    else if (SET == HBN_Get_INT_State(HBN_INT_ACOMP0)) {
        HBN_Clear_IRQ(HBN_INT_ACOMP0);
        pm_irq_callback(PM_HBN_ACOMP0_WAKEUP_EVENT);
    }
    /* ACOMP1 */
    else if (SET == HBN_Get_INT_State(HBN_INT_ACOMP1)) {
        HBN_Clear_IRQ(HBN_INT_ACOMP1);
        pm_irq_callback(PM_HBN_ACOMP1_WAKEUP_EVENT);
    }
}

__WEAK void pm_irq_callback(enum pm_event_type event)
{
}

void pm_pds_irq_register(void)
{
    Interrupt_Handler_Register(PDS_WAKEUP_IRQn, PDS_WAKEUP_IRQ);
    CPU_Interrupt_Enable(PDS_WAKEUP_IRQn);
}

void ATTR_TCM_SECTION PDS_WAKEUP_IRQ(void)
{
    /* WAKE INT */
    if (SET == PDS_Get_IntStatus(PDS_INT_WAKEUP)) {
    }
    /* RF DONE */
    else if (SET == PDS_Get_IntStatus(PDS_INT_RF_DONE)) {
    }
    /* WIFI_TBTT_SLEEP */
    else if (SET == PDS_Get_IntStatus(PDS_INT_WIFI_TBTT_SLEEP)) {
    }
    /* WIFI_TBTT_WAKEUP */
    else if (SET == PDS_Get_IntStatus(PDS_INT_WIFI_TBTT_WAKEUP)) {
    }

    PDS_IntClear();
}
