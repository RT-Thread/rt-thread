#include "bl616_pm.h"
#include "bflb_flash.h"
#include "bl616_clock.h"
#include "bflb_rtc.h"
#include "bl616_glb.h"
#include "bl616_hbn.h"
#include "bl616_pds.h"
#include "ef_data_reg.h"

#ifndef PM_PDS_GPIO_KEEP_EN
#define PM_PDS_GPIO_KEEP_EN 0
#endif

#ifndef PM_HBN_GPIO_KEEP_EN
#define PM_HBN_GPIO_KEEP_EN 0
#endif

#ifndef PM_PDS_FLASH_POWER_OFF
#define PM_PDS_FLASH_POWER_OFF 1
#endif

#ifndef PM_PDS_PLL_POWER_OFF
#define PM_PDS_PLL_POWER_OFF 1
#endif

#ifndef PM_PDS_RF_POWER_OFF
#define PM_PDS_RF_POWER_OFF 1
#endif

#ifndef PM_PDS_LDO_LEVEL_DEFAULT
#define PM_PDS_LDO_LEVEL_DEFAULT HBN_LDO_LEVEL_1P10V
#endif

#ifndef PM_HBN_FLASH_POWER_OFF
#define PM_HBN_FLASH_POWER_OFF 1
#endif

#ifndef PM_HBN_LDO_LEVEL_DEFAULT
#define PM_HBN_LDO_LEVEL_DEFAULT HBN_LDO_LEVEL_0P90V
#endif

/* Cache Way Disable, will get from l1c register */
uint8_t cacheWayDisable = 0;

/* PSRAM IO Configuration, will get from glb register */
uint32_t psramIoCfg = 0;

/* Flash offset value, will get from sf_ctrl register */
uint32_t flash_offset = 0;

spi_flash_cfg_type *flash_cfg;

static PDS_DEFAULT_LV_CFG_Type ATTR_TCM_CONST_SECTION pdsCfgLevel1 = {
    .pdsCtl = {
        .pdsStart = 1,
        .sleepForever = 0,
        .xtalForceOff = 0,
        .saveWiFiState = 0,
        .ldo11Off = 1,
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
        .wifipllOff = 1,
        .pdsDcdc11Vsel = 0x8,
        .pdsCtlRfSel = 3,
        .pdsUseTbttSlp = 0,
        .pdsGpioIsoMod = 0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff = 0,
        .forceWbPwrOff = 0,
        .forceUsbPwrOff = 0,
        .forceCpuIso = 0,
        .forceWbIso = 0,
        .forceUsbIso = 0,
        .forceCpuPdsRst = 0,
        .forceWbPdsRst = 0,
        .forceUsbPdsRst = 0,
        .forceCpuMemStby = 0,
        .forceWbMemStby = 0,
        .forceUsbMemStby = 0,
        .forceCpuGateClk = 0,
        .forceWbGateClk = 0,
        .forceUsbGateClk = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff = 0,
        .forceMiscIsoEn = 0,
        .forceMiscPdsRst = 0,
        .forceMiscMemStby = 0,
        .forceMiscGateClk = 0,
        .cpuIsoEn = 0,
        .wbIsoEn = 1,
        .usbIsoEn = 0,
        .miscIsoEn = 0,
    },
    .pdsCtl4 = {
        .cpuPwrOff = 0,
        .cpuRst = 0,
        .cpuMemStby = 0,
        .cpuGateClk = 0,
        .wbPwrOff = 1,
        .wbRst = 1,
        .wbMemStby = 0,
        .wbGateClk = 0,
        .usbPwrOff = 0,
        .usbRst = 0,
        .usbMemStby = 0,
        .usbGateClk = 0,
        .miscPwrOff = 0,
        .miscRst = 0,
        .miscMemStby = 0,
        .miscGateClk = 0,
    },
    .pdsCtl5 = {
        .cpuWfiMask = 0,
        .pdsPadOdEn = 0,
        .ctrlUsb33 = 0,
        .ldo18ioOff = 1,
        .pdsGpioKeep = 0,
    }
};
static PDS_DEFAULT_LV_CFG_Type ATTR_TCM_CONST_SECTION pdsCfgLevel2 = {
    .pdsCtl = {
        .pdsStart = 1,
        .sleepForever = 0,
        .xtalForceOff = 0,
        .saveWiFiState = 0,
        .ldo11Off = 1,
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
        .socEnbForceOn = 1,
        .pdsRstSocEn = 0,
        .pdsRC32mOn = 0,
        .pdsDcdc11VselEn = 0,
        .usbpllOff = 1,
        .aupllOff = 1,
        .wifipllOff = 1,
        .pdsDcdc11Vsel = 0x8,
        .pdsCtlRfSel = 3,
        .pdsUseTbttSlp = 0,
        .pdsGpioIsoMod = 0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff = 0,
        .forceWbPwrOff = 0,
        .forceUsbPwrOff = 0,
        .forceCpuIso = 0,
        .forceWbIso = 0,
        .forceUsbIso = 0,
        .forceCpuPdsRst = 0,
        .forceWbPdsRst = 0,
        .forceUsbPdsRst = 0,
        .forceCpuMemStby = 0,
        .forceWbMemStby = 0,
        .forceUsbMemStby = 0,
        .forceCpuGateClk = 0,
        .forceWbGateClk = 0,
        .forceUsbGateClk = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff = 0,
        .forceMiscIsoEn = 0,
        .forceMiscPdsRst = 0,
        .forceMiscMemStby = 0,
        .forceMiscGateClk = 0,
        .cpuIsoEn = 1,
        .wbIsoEn = 0,
        .usbIsoEn = 0,
        .miscIsoEn = 0,
    },
    .pdsCtl4 = {
        .cpuPwrOff = 1,
        .cpuRst = 1,
        .cpuMemStby = 0,
        .cpuGateClk = 0,
        .wbPwrOff = 0,
        .wbRst = 0,
        .wbMemStby = 0,
        .wbGateClk = 0,
        .usbPwrOff = 0,
        .usbRst = 0,
        .usbMemStby = 0,
        .usbGateClk = 0,
        .miscPwrOff = 0,
        .miscRst = 0,
        .miscMemStby = 0,
        .miscGateClk = 0,
    },
    .pdsCtl5 = {
        .cpuWfiMask = 0,
        .pdsPadOdEn = 0,
        .ctrlUsb33 = 1,
        .ldo18ioOff = 1,
        .pdsGpioKeep = 0,
    }
};

static PDS_DEFAULT_LV_CFG_Type ATTR_TCM_CONST_SECTION pdsCfgLevel3 = {
    .pdsCtl = {
        .pdsStart = 1,
        .sleepForever = 0,
        .xtalForceOff = 0,
        .saveWiFiState = 0,
        .ldo11Off = 1,
        .bgSysOff = 1,
        .ctrlGpioIePuPd = 0,
        .dcdc18Off = 1,
        .clkOff = 1,
        .memStby = 1,
        .glbRstProtect = 0,
        .isolation = 1,
        .waitXtalRdy = 1,
        .pdsPwrOff = 1,
        .xtalOff = 1,
        .socEnbForceOn = 0,
        .pdsRstSocEn = 0,
        .pdsRC32mOn = 0,
        .pdsDcdc11VselEn = 0,
        .usbpllOff = 1,
        .aupllOff = 1,
        .wifipllOff = 1,
        .pdsDcdc11Vsel = 0x8,
        .pdsCtlRfSel = 3,
        .pdsUseTbttSlp = 0,
        .pdsGpioIsoMod = 0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff = 0,
        .forceWbPwrOff = 0,
        .forceUsbPwrOff = 0,
        .forceCpuIso = 0,
        .forceWbIso = 0,
        .forceUsbIso = 0,
        .forceCpuPdsRst = 0,
        .forceWbPdsRst = 0,
        .forceUsbPdsRst = 0,
        .forceCpuMemStby = 0,
        .forceWbMemStby = 0,
        .forceUsbMemStby = 0,
        .forceCpuGateClk = 0,
        .forceWbGateClk = 0,
        .forceUsbGateClk = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff = 0,
        .forceMiscIsoEn = 0,
        .forceMiscPdsRst = 0,
        .forceMiscMemStby = 0,
        .forceMiscGateClk = 0,
        .cpuIsoEn = 1,
        .wbIsoEn = 1,
        .usbIsoEn = 0,
        .miscIsoEn = 0,
    },
    .pdsCtl4 = {
        .cpuPwrOff = 1,
        .cpuRst = 1,
        .cpuMemStby = 0,
        .cpuGateClk = 0,
        .wbPwrOff = 1,
        .wbRst = 1,
        .wbMemStby = 0,
        .wbGateClk = 0,
        .usbPwrOff = 0,
        .usbRst = 0,
        .usbMemStby = 0,
        .usbGateClk = 0,
        .miscPwrOff = 0,
        .miscRst = 0,
        .miscMemStby = 0,
        .miscGateClk = 0,
    },
    .pdsCtl5 = {
        .cpuWfiMask = 0,
        .pdsPadOdEn = 0,
        .ctrlUsb33 = 1,
        .ldo18ioOff = 1,
        .pdsGpioKeep = 0,
    }
};

static PDS_DEFAULT_LV_CFG_Type ATTR_TCM_CONST_SECTION pdsCfgLevel7 = {
    .pdsCtl = {
        .pdsStart = 1,
        .sleepForever = 0,
        .xtalForceOff = 0,
        .saveWiFiState = 0,
        .ldo11Off = 1,
        .bgSysOff = 1,
        .ctrlGpioIePuPd = 0,
        .dcdc18Off = 1,
        .clkOff = 1,
        .memStby = 1,
        .glbRstProtect = 0,
        .isolation = 1,
        .waitXtalRdy = 1,
        .pdsPwrOff = 1,
        .xtalOff = 1,
        .socEnbForceOn = 0,
        .pdsRstSocEn = 0,
        .pdsRC32mOn = 0,
        .pdsDcdc11VselEn = 0,
        .usbpllOff = 1,
        .aupllOff = 1,
        .wifipllOff = 1,
        .pdsDcdc11Vsel = 0x8,
        .pdsCtlRfSel = 3,
        .pdsUseTbttSlp = 0,
        .pdsGpioIsoMod = 0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff = 0,
        .forceWbPwrOff = 0,
        .forceUsbPwrOff = 0,
        .forceCpuIso = 0,
        .forceWbIso = 0,
        .forceUsbIso = 0,
        .forceCpuPdsRst = 0,
        .forceWbPdsRst = 0,
        .forceUsbPdsRst = 0,
        .forceCpuMemStby = 0,
        .forceWbMemStby = 0,
        .forceUsbMemStby = 0,
        .forceCpuGateClk = 0,
        .forceWbGateClk = 0,
        .forceUsbGateClk = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff = 0,
        .forceMiscIsoEn = 0,
        .forceMiscPdsRst = 0,
        .forceMiscMemStby = 0,
        .forceMiscGateClk = 0,
        .cpuIsoEn = 1,
        .wbIsoEn = 1,
        .usbIsoEn = 1,
        .miscIsoEn = 0,
    },
    .pdsCtl4 = {
        .cpuPwrOff = 1,
        .cpuRst = 1,
        .cpuMemStby = 0,
        .cpuGateClk = 0,
        .wbPwrOff = 1,
        .wbRst = 1,
        .wbMemStby = 0,
        .wbGateClk = 0,
        .usbPwrOff = 1,
        .usbRst = 1,
        .usbMemStby = 0,
        .usbGateClk = 0,
        .miscPwrOff = 0,
        .miscRst = 0,
        .miscMemStby = 0,
        .miscGateClk = 0,
    },
    .pdsCtl5 = {
        .cpuWfiMask = 0,
        .pdsPadOdEn = 0,
        .ctrlUsb33 = 1,
        .ldo18ioOff = 1,
        .pdsGpioKeep = 0,
    }
};

static PDS_DEFAULT_LV_CFG_Type ATTR_TCM_CONST_SECTION pdsCfgLevel15 = {
    .pdsCtl = {
        .pdsStart = 1,
        .sleepForever = 0,
        .xtalForceOff = 0,
        .saveWiFiState = 0,
        .ldo11Off = 1,
        .bgSysOff = 1,
        .ctrlGpioIePuPd = 0,
        .dcdc18Off = 1,
        .clkOff = 1,
        .memStby = 1,
        .glbRstProtect = 0,
        .isolation = 1,
        .waitXtalRdy = 1,
        .pdsPwrOff = 1,
        .xtalOff = 1,
        .socEnbForceOn = 0,
        .pdsRstSocEn = 1,
        .pdsRC32mOn = 0,
        .pdsDcdc11VselEn = 0,
        .usbpllOff = 1,
        .aupllOff = 1,
        .wifipllOff = 1,
        .pdsDcdc11Vsel = 0x8,
        .pdsCtlRfSel = 3,
        .pdsUseTbttSlp = 0,
        .pdsGpioIsoMod = 0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff = 0,
        .forceWbPwrOff = 0,
        .forceUsbPwrOff = 0,
        .forceCpuIso = 0,
        .forceWbIso = 0,
        .forceUsbIso = 0,
        .forceCpuPdsRst = 0,
        .forceWbPdsRst = 0,
        .forceUsbPdsRst = 0,
        .forceCpuMemStby = 0,
        .forceWbMemStby = 0,
        .forceUsbMemStby = 0,
        .forceCpuGateClk = 0,
        .forceWbGateClk = 0,
        .forceUsbGateClk = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff = 0,
        .forceMiscIsoEn = 0,
        .forceMiscPdsRst = 0,
        .forceMiscMemStby = 0,
        .forceMiscGateClk = 0,
        .cpuIsoEn = 1,
        .wbIsoEn = 1,
        .usbIsoEn = 1,
        .miscIsoEn = 1,
    },
    .pdsCtl4 = {
        .cpuPwrOff = 1,
        .cpuRst = 1,
        .cpuMemStby = 0,
        .cpuGateClk = 0,
        .wbPwrOff = 1,
        .wbRst = 1,
        .wbMemStby = 0,
        .wbGateClk = 0,
        .usbPwrOff = 1,
        .usbRst = 1,
        .usbMemStby = 0,
        .usbGateClk = 0,
        .miscPwrOff = 1,
        .miscRst = 1,
        .miscMemStby = 0,
        .miscGateClk = 0,
    },
    .pdsCtl5 = {
        .cpuWfiMask = 0,
        .pdsPadOdEn = 0,
        .ctrlUsb33 = 1,
        .ldo18ioOff = 1,
        .pdsGpioKeep = 0,
    }
};
/******************************************************************************
 * @brief  set power down sleep VDDCORE gpio interrupt mask
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
 *******************************************************************************/
static BL_Err_Type ATTR_TCM_SECTION pm_clr_pds_gpio_int(void)
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

/******************************************************************************
 * @brief  Power on the power powered down in PDS0
 *
 * @param  delay: None
 *
 * @return SUCCESS or ERROR
 *
 *******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION AON_Set_LDO11_SOC_Sstart_Delay(uint8_t delay)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((delay <= 0x3));

    /* config ldo11soc_sstart_delay_aon */
    tmpVal = BL_RD_REG(AON_BASE, AON_DCDC_TOP_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_DCDC_SSTART_TIME_AON, delay);
    BL_WR_REG(AON_BASE, AON_DCDC_TOP_0, tmpVal);

    return SUCCESS;
}

BL_Err_Type pm_pds_wakeup_src_en(uint32_t WakeupType)
{
    if ((WakeupType < PDS_WAKEUP_BY_PDS_TIMER_EN_POS) || (WakeupType > PDS_WAKEUP_BY_WIFI_TBTT_IRQ_EN_POS)) {
        return INVALID;
    }

    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    tmpVal |= ((uint32_t)1 << WakeupType);
    BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

    return SUCCESS;
}

BL_Sts_Type pm_pds_get_wakeup_src(uint32_t WakeupType)
{
    if ((WakeupType < PDS_WAKEUP_BY_PDS_TIMER_EN_POS) || (WakeupType > PDS_WAKEUP_BY_WIFI_TBTT_IRQ_EN_POS)) {
        return INVALID;
    }

    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_RO_PDS_WAKEUP_EVENT);
    tmpVal &= ((uint32_t)1 << (WakeupType - PDS_WAKEUP_BY_PDS_TIMER_EN_POS));

    return tmpVal ? SET : RESET;
}

void pm_pds_mask_all_wakeup_src(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CR_PDS_WAKEUP_SRC_EN);
    BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CR_PDS_RF_DONE_INT_MASK);
    BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CR_PDS_WIFI_TBTT_SLEEP_IRQ_MASK);
    BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CR_PDS_WIFI_TBTT_WAKEUP_IRQ_MASK);
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
 *    PD_CORE   PD_CORE_MISC_DIG    PD_CORE_MISC_ANA   PD_CORE_CPU PD_BZ PD_USB
 *PDS0    ON           ON                   ON            ON        ON      ON
 *PDS1    ON           ON                   ON            ON        ON      OFF
 *PDS2    ON           ON                   ON            ON        OFF     ON
 *PDS3    ON           ON                   ON            ON        OFF     OFF
 *PDS4    ON           ON                   ON            OFF       ON      ON
 *PDS5    ON           ON                   ON            OFF       ON      OFF
 *PDS6    ON           ON                   ON            OFF       OFF     ON
 *PDS7    ON           ON                   ON            OFF       OFF     OFF
 */
void ATTR_TCM_SECTION pm_pds_mode_enter(enum pm_pds_sleep_level pds_level,
                                        uint32_t sleep_time)
{
    PDS_DEFAULT_LV_CFG_Type *pPdsCfg = NULL;
    uint32_t tmpVal;
    uint32_t pds_ram[4];
    PDS_RAM_CFG_Type pds_ram_ctrl = { (PDS_CTRL_RAM1_Type *)&pds_ram[0], (PDS_CTRL_RAM2_Type *)&pds_ram[1],
                                      (PDS_CTRL_RAM3_Type *)&pds_ram[2], (PDS_CTRL_RAM4_Type *)&pds_ram[3] };
    uint8_t xtal_type = 0;

    if ((sleep_time != 0) && (sleep_time <= PDS_WARMUP_LATENCY_CNT)) {
        return;
    }

    /* To make it simple and safe*/
    __ASM volatile("csrc mstatus, 8");

    /* get xtal type */
    HBN_Get_Xtal_Type(&xtal_type);

    HBN_Set_Ldo11_Rt_Vout(PM_PDS_LDO_LEVEL_DEFAULT);
    /************************ PDS INT SET ***********************/
    BL_WR_REG(HBN_BASE, HBN_IRQ_CLR, 0xffffffff);
    BL_WR_REG(HBN_BASE, HBN_IRQ_CLR, 0);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);

    if (sleep_time)
        tmpVal |= (1 << 10); // unmask pds sleep time wakeup
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
        case PM_PDS_LEVEL_15:
            pPdsCfg = &pdsCfgLevel15;
            break;
        default:
            return;
    }

#if PM_PDS_FLASH_POWER_OFF
    uint32_t flash_cfg_len;
    uint32_t sf_pin_select = 0;

    /* get sw uasge 0 */
    // EF_Ctrl_Read_Sw_Usage(0, (uint32_t *)&tmpVal);
    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_EF_SW_USAGE_0);
    /* get flash type */
    sf_pin_select = (tmpVal >> 14) & 0x3f;
    /* get flash config */
    bflb_flash_get_cfg((uint8_t **)&flash_cfg, &flash_cfg_len);

    HBN_Power_Down_Flash(flash_cfg);
    /* Turn Off Flash/PSRAM PAD IE */
    if (sf_pin_select & (1 << 2)) {
        for (uint8_t i = 4; i < 10; i++) {
            *((volatile uint32_t *)(0x200008C4 + i * 4)) = 0;
        }
    } else if (sf_pin_select & (1 << 3)) {
        for (uint8_t i = 10; i < 16; i++) {
            *((volatile uint32_t *)(0x200008C4 + i * 4)) = 0;
        }
    } else {
    }

    // psram io config
    for (uint8_t i = 35; i < 56; i++) {
        //*((volatile uint32_t *)(0x200008C4 + i * 4)) = 0;
    }

#endif

#if PM_PDS_GPIO_KEEP_EN
    pPdsCfg->pdsCtl.pdsGpioIsoMod = 1;
    pPdsCfg->pdsCtl5.pdsGpioKeep = 7;
#endif

#if PM_PDS_PLL_POWER_OFF
    /* MCU CLK SELECT RC32M */
    PDS_Pu_PLL_Enable();
    GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_RC32M);
    GLB_Power_Off_AUPLL();
    GLB_Power_Off_WIFIPLL();
    // AON_Power_Off_XTAL();
#endif

#if PM_PDS_RF_POWER_OFF == 0
    pPdsCfg->pdsCtl.pdsCtlRfSel = 0;
#endif

    if (0 != (0xF & BL_RD_REG(PDS_BASE, PDS_GPIO_I_SET))) {
        pPdsCfg->pdsCtl.ctrlGpioIePuPd = 1;
    }

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    /* if enable wakeup trigger by irrx */
    if (BL_IS_REG_BIT_SET(tmpVal, PDS_WAKEUP_BY_IRRX_EN)) {
        /* xclk selecet xtal,xtal can't power off */
        GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_XTAL);
        pPdsCfg->pdsCtl.xtalOff = 0;
        // pPdsCfg->pdsCtl.pdsRC32mOn = 1;
        // pPdsCfg->pdsCtl.clkOff = 0;
    }

    /* config  ldo11soc_sstart_delay_aon =2 , cr_pds_pd_ldo11=0 to speedup
   * ldo11soc_rdy_aon */
    AON_Set_LDO11_SOC_Sstart_Delay(0x2);

    pds_ram[0] = BL_RD_REG(PDS_BASE, PDS_RAM1);
    pds_ram[1] = BL_RD_REG(PDS_BASE, PDS_RAM2);
    pds_ram[2] = BL_RD_REG(PDS_BASE, PDS_RAM3);
    pds_ram[3] = BL_RD_REG(PDS_BASE, PDS_RAM4);

    /* Enable PDS control pd_core Sram Clock */
    pds_ram_ctrl.pds_ram1->ctlRamClk = 1;

    if (pds_level == PM_PDS_LEVEL_15) {
        /* WRAM Sleep */
        pds_ram_ctrl.pds_ram2->wramSlp &= ~0x3ff;
        /* WRAM Retention */
        pds_ram_ctrl.pds_ram2->wramRet |= 0x3ff;

        /* OCRAM Sleep */
        pds_ram_ctrl.pds_ram4->cr_ocram_slp &= ~0xfffff;
        /* OCRAM Retention */
        pds_ram_ctrl.pds_ram3->cr_ocram_ret |= 0xfffff;
    } else {
        /* WRAM Sleep */
        pds_ram_ctrl.pds_ram2->wramSlp &= ~0x3ff;
        /* OCRAM Sleep */
        pds_ram_ctrl.pds_ram4->cr_ocram_slp &= ~0xfffff;
    }

    PDS_RAM_Config(
        (PDS_CTRL_RAM1_Type *)pds_ram_ctrl.pds_ram1, (PDS_CTRL_RAM2_Type *)pds_ram_ctrl.pds_ram2,
        (PDS_CTRL_RAM3_Type *)pds_ram_ctrl.pds_ram3, (PDS_CTRL_RAM4_Type *)pds_ram_ctrl.pds_ram4);

    PDS_Default_Level_Config(pPdsCfg, sleep_time);

    __WFI();

/******************************* Wakeup Flow *******************************/
#if PM_PDS_PLL_POWER_OFF
    GLB_Power_On_XTAL_And_PLL_CLK(GLB_XTAL_40M, GLB_PLL_WIFIPLL);
    GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_TOP_WIFIPLL_320M);
#endif

#if PM_PDS_FLASH_POWER_OFF
    if (pds_level < PM_PDS_LEVEL_2) {
        /* Init flash gpio */
        bflb_sf_cfg_init_flash_gpio((uint8_t)sf_pin_select, 1);

        bflb_sf_ctrl_set_owner(SF_CTRL_OWNER_SAHB);
        bflb_sflash_restore_from_powerdown(flash_cfg, 0, SF_CTRL_FLASH_BANK0);
    }
#endif

    /* enable global interrupts */
    __asm volatile("csrs mstatus, 8");

    /*************************************************************************/
}

/**
 * @brief
 *
 * power management in hbn(hibernation) mode
 * cpu will reset after wakeup
 *
 * HBN_LEVEL PD_AON PD_AON_HBNRTC PD_AON_HBNCORE PD_CORE&...
 * HBN0        ON       ON            ON            OFF
 * HBN1        ON       ON            OFF           OFF
 * HBN2        ON       OFF           OFF           OFF
 *
 * @param hbn_level
 */
ATTR_TCM_SECTION void pm_hbn_mode_enter(enum pm_hbn_sleep_level hbn_level,
                                        uint8_t sleep_time)
{
    uint32_t tmpVal;

    /* To make it simple and safe*/
    __ASM volatile("csrc mstatus, 8");

    bflb_irq_clear_pending(HBN_OUT0_IRQn);
    bflb_irq_clear_pending(HBN_OUT1_IRQn);

    BL_WR_REG(HBN_BASE, HBN_IRQ_CLR, 0xffffffff);
    BL_WR_REG(HBN_BASE, HBN_IRQ_CLR, 0);

    if (sleep_time) {
        struct bflb_device_s *rtc_dev = NULL;
        bflb_rtc_set_time(rtc_dev,sleep_time); // sleep time,unit is second
    }

    if (hbn_level >= PM_HBN_LEVEL_2) {
        HBN_Power_Off_RC32K();
    } else {
        HBN_Keep_On_RC32K();
    }

    /* MCU CLK SELECT RC32M */
    GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_RC32M);

#if PM_HBN_FLASH_POWER_OFF
    uint32_t flash_cfg_len;

    /* get flash config */
    bflb_flash_get_cfg((uint8_t **)&flash_cfg, &flash_cfg_len);

    HBN_Power_Down_Flash(flash_cfg);
#endif

    /* HBN mode LDO level */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_LDO11_AON_VOUT_SEL, PM_HBN_LDO_LEVEL_DEFAULT);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_LDO11_RT_VOUT_SEL, PM_HBN_LDO_LEVEL_DEFAULT);
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    /* Set HBN flag */
    BL_WR_REG(HBN_BASE, HBN_RSV0, HBN_STATUS_ENTER_FLAG);

    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);

    /* Set HBN level, (HBN_PWRDN_HBN_RAM not use) */
    switch (hbn_level) {
        case PM_HBN_LEVEL_0:
            tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PWRDN_HBN_CORE);
            tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PWRDN_HBN_RTC);
            break;
        case PM_HBN_LEVEL_1:
            tmpVal = BL_SET_REG_BIT(tmpVal, HBN_PWRDN_HBN_CORE);
            tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PWRDN_HBN_RTC);
            break;
        case PM_HBN_LEVEL_2:
            tmpVal = BL_SET_REG_BIT(tmpVal, HBN_PWRDN_HBN_CORE);
            tmpVal = BL_SET_REG_BIT(tmpVal, HBN_PWRDN_HBN_RTC);
            break;
    }

    /* Set power on option:0 for por reset twice for robust 1 for reset only once*/
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PWR_ON_OPTION);
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    BL_WR_REG(HBN_BASE, HBN_IRQ_CLR, 0xffffffff);
    BL_WR_REG(HBN_BASE, HBN_IRQ_CLR, 0);

    /* Enable HBN mode */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_MODE);
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    while (1) {
        arch_delay_ms(100);
        GLB_SW_POR_Reset();
    }
}

void pm_set_wakeup_callback(void (*wakeup_callback)(void))
{
    BL_WR_REG(HBN_BASE, HBN_RSV1, (uint32_t)wakeup_callback);
    /* Set HBN flag */
    BL_WR_REG(HBN_BASE, HBN_RSV0, HBN_STATUS_ENTER_FLAG);
}

void pm_set_boot2_app_jump_para(uint32_t para)
{
    BL_WR_REG(HBN_BASE, HBN_RSV1, para);
    /* Set APP jump flag */
    BL_WR_REG(HBN_BASE, HBN_RSV0, APP_JUMP_ENTER_FLAG);
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
    if (SET == HBN_Get_INT_State(HBN_INT_GPIO16)) {
        HBN_Clear_IRQ(HBN_INT_GPIO16);
        pm_irq_callback(PM_HBN_GPIO16_WAKEUP_EVENT);
    } else if (SET == HBN_Get_INT_State(HBN_INT_GPIO17)) {
        HBN_Clear_IRQ(HBN_INT_GPIO17);
        pm_irq_callback(PM_HBN_GPIO17_WAKEUP_EVENT);
    } else if (SET == HBN_Get_INT_State(HBN_INT_GPIO18)) {
        HBN_Clear_IRQ(HBN_INT_GPIO18);
        pm_irq_callback(PM_HBN_GPIO18_WAKEUP_EVENT);
    } else if (SET == HBN_Get_INT_State(HBN_INT_GPIO19)) {
        HBN_Clear_IRQ(HBN_INT_GPIO19);
        pm_irq_callback(PM_HBN_GPIO19_WAKEUP_EVENT);
    } else {
        HBN_Clear_RTC_INT();
        HBN_Clear_IRQ(HBN_INT_RTC);
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

void hal_pm_ldo11_use_ext_dcdc(void)
{
    for (uint8_t i = 0; i < 9; i++) {
        HBN_Set_Ldo11_Rt_Vout(9 - i);
        HBN_Set_Ldo11_Soc_Vout(9 - i);
        arch_delay_ms(1);
    }
    HBN_Set_Ldo11_Rt_Vout(0);
    HBN_Set_Ldo11_Soc_Vout(0);
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
    } else {
    }

    PDS_IntClear();
}
