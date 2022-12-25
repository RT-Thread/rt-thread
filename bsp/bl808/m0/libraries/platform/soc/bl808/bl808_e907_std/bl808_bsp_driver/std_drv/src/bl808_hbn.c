/**
  ******************************************************************************
  * @file    bl808_hbn.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
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

#include "bl808_hbn.h"
#include "bl808_glb.h"
#include "bl808_xip_sflash.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  HBN
 *  @{
 */

/** @defgroup  HBN_Private_Macros
 *  @{
 */
#define HBN_CLK_SET_DUMMY_WAIT \
    {                          \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
    }

/*@} end of group HBN_Private_Macros */

/** @defgroup  HBN_Private_Types
 *  @{
 */

/*@} end of group HBN_Private_Types */

/** @defgroup  HBN_Private_Variables
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *hbnInt0CbfArra[HBN_OUT0_INT_MAX] = { NULL };
static intCallback_Type *hbnInt1CbfArra[HBN_OUT1_INT_MAX] = { NULL };
#endif

/*@} end of group HBN_Private_Variables */

/** @defgroup  HBN_Global_Variables
 *  @{
 */

/*@} end of group HBN_Global_Variables */

/** @defgroup  HBN_Private_Fun_Declaration
 *  @{
 */

/*@} end of group HBN_Private_Fun_Declaration */

/** @defgroup  HBN_Private_Functions
 *  @{
 */

/*@} end of group HBN_Private_Functions */

/** @defgroup  HBN_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Enter HBN
 *
 * @param  cfg: HBN APP Config
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION HBN_Mode_Enter(HBN_APP_CFG_Type *cfg)
{
    uint32_t valLow = 0, valHigh = 0;
    uint64_t val;

    if (cfg->useXtal32k) {
        HBN_32K_Sel(HBN_32K_XTAL);
    } else {
        HBN_32K_Sel(HBN_32K_RC);
        HBN_Power_Off_Xtal_32K();
    }

    /* always disable HBN pin pull up/down to reduce PDS/HBN current, 0x4000F014[16]=0 */
    HBN_Hw_Pu_Pd_Cfg(DISABLE);

    HBN_Pin_WakeUp_Mask(~(cfg->gpioWakeupSrc));
    if (cfg->gpioWakeupSrc != 0) {
        HBN_GPIO_INT_Enable(cfg->gpioTrigType);
    }

    /* HBN RTC config and enable */
    HBN_Clear_RTC_Counter();
    if (cfg->sleepTime != 0) {
        HBN_Get_RTC_Timer_Val(&valLow, &valHigh);
        val = valLow + ((uint64_t)valHigh << 32);
        val += cfg->sleepTime;
        HBN_Set_RTC_Timer(HBN_RTC_INT_DELAY_0T, val & 0xffffffff, val >> 32, HBN_RTC_COMP_BIT0_39);
        HBN_Enable_RTC_Counter();
    }

    HBN_Power_Down_Flash(cfg->flashCfg);
    //HBN_Set_Embedded_Flash_Pullup(ENABLE);      /* E_ITEM_06 */

    GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_RC32M);
    GLB_Set_DSP_System_CLK(GLB_DSP_SYS_CLK_RC32M);
    GLB_Set_DSP_PBCLK(GLB_DSP_SYS_PBCLK_RC32M);

    HBN_Enable(cfg->gpioWakeupSrc, cfg->ldoLevel, cfg->hbnLevel, cfg->dcdcPuSeq);
}

/****************************************************************************/ /**
 * @brief  power down and switch clock
 *
 * @param  flashCfg: None
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION HBN_Power_Down_Flash(SPI_Flash_Cfg_Type *flashCfg)
{
    SPI_Flash_Cfg_Type bhFlashCfg;

    if (flashCfg == NULL) {
        L1C_DCache_Invalid_By_Addr(BL808_FLASH_XIP_BASE + 8 + 4, sizeof(SPI_Flash_Cfg_Type));
        XIP_SFlash_Read_Via_Cache_Need_Lock(BL808_FLASH_XIP_BASE + 8 + 4, (uint8_t *)(&bhFlashCfg),
                                            sizeof(SPI_Flash_Cfg_Type), 0, 0);
        L1C_DCache_Invalid_By_Addr(BL808_FLASH_XIP_BASE + 8 + 4, sizeof(SPI_Flash_Cfg_Type));

        SF_Ctrl_Set_Owner(SF_CTRL_OWNER_SAHB);
        SFlash_Reset_Continue_Read(&bhFlashCfg);
    } else {
        SF_Ctrl_Set_Owner(SF_CTRL_OWNER_SAHB);
        SFlash_Reset_Continue_Read(flashCfg);
    }

    SFlash_Powerdown();
}

/****************************************************************************/ /**
 * @brief  Enable HBN mode
 *
 * @param  aGPIOIeCfg: AON GPIO input enable config. Bit(s) of Wakeup GPIO(s) must not be set to
 *                     0(s),say when use GPIO7 as wake up pin,aGPIOIeCfg should be 0x01.
 * @param  ldoLevel: LDO volatge level
 * @param  hbnLevel: HBN work level
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION HBN_Enable(uint32_t aGPIOIeCfg, HBN_LDO_LEVEL_Type ldoLevel, HBN_LEVEL_Type hbnLevel, uint8_t dcdcPuSeq)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_HBN_LDO_LEVEL_TYPE(ldoLevel));
    CHECK_PARAM(IS_HBN_LEVEL_TYPE(hbnLevel));

    /* Setting from guide */
    /* HBN_SRAM Retion */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_SRAM);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_RETRAM_RET);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_RETRAM_SLP);
    BL_WR_REG(HBN_BASE, HBN_SRAM, tmpVal);

    /* AON GPIO IE */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_REG_EN_HW_PU_PD);
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    /* HBN mode LDO level */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_LDO11_AON_VOUT_SEL, ldoLevel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_LDO11_RT_VOUT_SEL, ldoLevel);
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    /* power on dcdc11&&dcdc18 sequence  */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    if (dcdcPuSeq) {
        tmpVal = BL_SET_REG_BIT(tmpVal, HBN_PU_DCDC_AON);
        tmpVal = BL_SET_REG_BIT(tmpVal, HBN_PU_DCDC18_AON);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PU_DCDC_AON);
        tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PU_DCDC18_AON);
    }
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    /* Select RC32M */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_ROOT_CLK_SEL, 0);
    BL_WR_REG(HBN_BASE, HBN_GLB, tmpVal);
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    /* Set HBN flag */
    BL_WR_REG(HBN_BASE, HBN_RSV0, HBN_STATUS_ENTER_FLAG);

    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    /* Set HBN level, (HBN_PWRDN_HBN_RAM not use) */
    switch (hbnLevel) {
        case HBN_LEVEL_0:
            tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PWRDN_HBN_CORE);
            break;

        case HBN_LEVEL_1:
            tmpVal = BL_SET_REG_BIT(tmpVal, HBN_PWRDN_HBN_CORE);
            break;

        default:
            break;
    }
    /* Set power on option:0 for por reset twice for robust 1 for reset only once*/
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PWR_ON_OPTION);
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    /* Enable HBN mode */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_MODE);
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    while (1) {
        arch_delay_ms(1000);
    }
}

/****************************************************************************/ /**
 * @brief  Reset HBN mode
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Reset(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    /* Reset HBN mode */
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_SW_RST);
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_SW_RST);
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_SW_RST);
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Enable HBN PIR
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_PIR_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_PIR_CFG);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_PIR_EN);
    BL_WR_REG(HBN_BASE, HBN_PIR_CFG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Disable HBN PIR
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_PIR_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_PIR_CFG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PIR_EN);
    BL_WR_REG(HBN_BASE, HBN_PIR_CFG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Config HBN PIR interrupt
 *
 * @param  pirIntCfg: HBN PIR interrupt configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_PIR_INT_Config(HBN_PIR_INT_CFG_Type *pirIntCfg)
{
    uint32_t tmpVal;
    uint32_t bit4 = 0;
    uint32_t bit5 = 0;
    uint32_t bitVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_PIR_CFG);

    /* low trigger interrupt */
    if (pirIntCfg->lowIntEn == ENABLE) {
        bit5 = 0;
    } else {
        bit5 = 1;
    }

    /* high trigger interrupt */
    if (pirIntCfg->highIntEn == ENABLE) {
        bit4 = 0;
    } else {
        bit4 = 1;
    }

    bitVal = bit4 | (bit5 << 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_PIR_DIS, bitVal);
    BL_WR_REG(HBN_BASE, HBN_PIR_CFG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Select HBN PIR low pass filter
 *
 * @param  lpf: HBN PIR low pass filter selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_PIR_LPF_Sel(HBN_PIR_LPF_Type lpf)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_HBN_PIR_LPF_TYPE(lpf));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_PIR_CFG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_PIR_LPF_SEL, lpf);
    BL_WR_REG(HBN_BASE, HBN_PIR_CFG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Select HBN PIR high pass filter
 *
 * @param  hpf: HBN PIR high pass filter selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_PIR_HPF_Sel(HBN_PIR_HPF_Type hpf)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_HBN_PIR_HPF_TYPE(hpf));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_PIR_CFG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_PIR_HPF_SEL, hpf);
    BL_WR_REG(HBN_BASE, HBN_PIR_CFG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set HBN PIR threshold value
 *
 * @param  threshold: HBN PIR threshold value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Set_PIR_Threshold(uint16_t threshold)
{
    uint32_t tmpVal;

    CHECK_PARAM((threshold <= 0x3FFF));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_PIR_VTH);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_PIR_VTH, threshold);
    BL_WR_REG(HBN_BASE, HBN_PIR_VTH, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get HBN PIR threshold value
 *
 * @param  None
 *
 * @return HBN PIR threshold value
 *
*******************************************************************************/
uint16_t HBN_Get_PIR_Threshold(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_PIR_VTH);

    return BL_GET_REG_BITS_VAL(tmpVal, HBN_PIR_VTH);
}

/****************************************************************************/ /**
 * @brief  Set HBN PIR interval value
 *
 * @param  interval: HBN PIR interval value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Set_PIR_Interval(uint16_t interval)
{
    uint32_t tmpVal;

    CHECK_PARAM((interval <= 0xFFF));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_PIR_INTERVAL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_PIR_INTERVAL, interval);
    BL_WR_REG(HBN_BASE, HBN_PIR_INTERVAL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get HBN PIR interval value
 *
 * @param  None
 *
 * @return HBN PIR interval value
 *
*******************************************************************************/
uint16_t HBN_Get_PIR_Interval(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_PIR_INTERVAL);

    return BL_GET_REG_BITS_VAL(tmpVal, HBN_PIR_INTERVAL);
}

/****************************************************************************/ /**
 * @brief  get HBN bod out state
 *
 * @param  None
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type HBN_Get_BOD_OUT_State(void)
{
    return BL_GET_REG_BITS_VAL(BL_RD_REG(HBN_BASE, HBN_BOR_CFG), HBN_R_BOD_OUT) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  set HBN bod config
 *
 * @param  enable: ENABLE or DISABLE, if enable, Power up Brown Out Reset
 * @param  threshold: bod threshold
 * @param  mode: bod work mode with por
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Set_BOD_Config(uint8_t enable, HBN_BOD_THRES_Type threshold, HBN_BOD_MODE_Type mode)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_HBN_BOD_THRES_TYPE(threshold));
    CHECK_PARAM(IS_HBN_BOD_MODE_TYPE(mode));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_BOR_CFG);
    if (enable) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_PU_BOD, 1);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_PU_BOD, 0);
    }
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_BOD_VTH, threshold);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_BOD_SEL, mode);
    BL_WR_REG(HBN_BASE, HBN_BOR_CFG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN set ldo11aon voltage out
 *
 * @param  ldoLevel: LDO volatge level
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Set_Ldo11_Aon_Vout(HBN_LDO_LEVEL_Type ldoLevel)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_HBN_LDO_LEVEL_TYPE(ldoLevel));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_SW_LDO11_AON_VOUT_SEL, ldoLevel);
    BL_WR_REG(HBN_BASE, HBN_GLB, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN set ldo11rt voltage out
 *
 * @param  ldoLevel: LDO volatge level
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Set_Ldo11_Rt_Vout(HBN_LDO_LEVEL_Type ldoLevel)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_HBN_LDO_LEVEL_TYPE(ldoLevel));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_SW_LDO11_RT_VOUT_SEL, ldoLevel);
    BL_WR_REG(HBN_BASE, HBN_GLB, tmpVal);

    return SUCCESS;
}

/****************************************************************************
 * @brief  HBN set ldo11_Rtc voltage out
 *
 * @param  ldoLevel: LDO11_Rtc volatge level
 *        0:0.60V  1:0.65V  2:0.70V  3:0.75V
 *        4:0.80V  5:0.85V  6:0.9V   7:0.95V
 *        8:1.0V   9:1.05V  10:1.1V  11:1.15V,
 *        12:1.2V  13:1.25V  14:1.3V 15:1.35V
 *
 * @return SUCCESS or ERROR
 *
 *******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Set_Ldo11_Rtc_Vout(HBN_LDO_LEVEL_Type ldoLevel)
{
    HBN_RTC_MISC_Type rtcMiscCfg;

    CHECK_PARAM(IS_HBN_LDO_LEVEL_TYPE(ldoLevel));

    HBN_Get_RTC_Misc_Cfg(&rtcMiscCfg);
    rtcMiscCfg.ldo11RtcVoutSelRtc = ldoLevel;
    HBN_Set_RTC_Misc_Cfg(&rtcMiscCfg);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN set ldo11 all voltage out, not include dcdc11
 *
 * @param  ldoLevel: LDO volatge level
 *
 * @return SUCCESS or ERROR
 *
 * @note not support LDO11_Rtc 0.65v & 0.6v
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Set_Ldo11_All_Vout(HBN_LDO_LEVEL_Type ldoLevel)
{
    uint32_t tmpVal;
    HBN_RTC_MISC_Type rtcMiscCfg;

    CHECK_PARAM(IS_HBN_LDO_LEVEL_TYPE(ldoLevel));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_SW_LDO11_AON_VOUT_SEL, ldoLevel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_SW_LDO11_RT_VOUT_SEL, ldoLevel);
    BL_WR_REG(HBN_BASE, HBN_GLB, tmpVal);

    HBN_Get_RTC_Misc_Cfg(&rtcMiscCfg);
    rtcMiscCfg.ldo11RtcVoutSelRtc = ldoLevel;
    HBN_Set_RTC_Misc_Cfg(&rtcMiscCfg);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN select 32K
 *
 * @param  clkType: HBN 32k clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION HBN_32K_Sel(HBN_32K_CLK_Type clkType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_HBN_32K_CLK_TYPE(clkType));

    HBN_Trim_RC32K();

    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_F32K_SEL, clkType);
    BL_WR_REG(HBN_BASE, HBN_GLB, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Select uart clock source
 *
 * @param  clkSel: uart clock type selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION HBN_Set_UART_CLK_Sel(HBN_UART_CLK_Type clkSel)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_HBN_UART_CLK_TYPE(clkSel));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);
    if ((HBN_UART_CLK_MCU_PBCLK == clkSel) || (HBN_UART_CLK_160M == clkSel)) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_UART_CLK_SEL2, 0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_UART_CLK_SEL, clkSel);
    } else {
        /* mcu_bclk as default */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_UART_CLK_SEL2, 1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_UART_CLK_SEL, 0);
    }

    BL_WR_REG(HBN_BASE, HBN_GLB, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get xclk clock source Select
 *
 * @param  None
 *
 * @return xclk clock type selection
 *
*******************************************************************************/
HBN_MCU_XCLK_Type ATTR_CLOCK_SECTION HBN_Get_MCU_XCLK_Sel(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, HBN_ROOT_CLK_SEL);

    return (HBN_MCU_XCLK_Type)(tmpVal & 0x1);
}

/****************************************************************************/ /**
 * @brief  Select xclk clock source
 *
 * @param  xclk: xclk clock type selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_Type xclk)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    CHECK_PARAM(IS_HBN_MCU_XCLK_TYPE(xclk));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, HBN_ROOT_CLK_SEL);
    switch (xclk) {
        case HBN_MCU_XCLK_RC32M:
            tmpVal2 &= (~(1 << 0));
            break;
        case HBN_MCU_XCLK_XTAL:
            tmpVal2 |= (1 << 0);
            break;
        default:
            break;
    }
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_ROOT_CLK_SEL, tmpVal2);
    BL_WR_REG(HBN_BASE, HBN_GLB, tmpVal);
    HBN_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get root clock selection
 *
 * @param  None
 *
 * @return root clock selection
 *
*******************************************************************************/
HBN_MCU_ROOT_CLK_Type ATTR_CLOCK_SECTION HBN_Get_MCU_Root_CLK_Sel(void)
{
    uint32_t tmpVal = 0;
    uint32_t rootClkSel = 0;

    /* root_clock_select = hbn_root_clk_sel[1] */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);
    rootClkSel = BL_GET_REG_BITS_VAL(tmpVal, HBN_ROOT_CLK_SEL) >> 1;
    if (0 == rootClkSel) {
        return HBN_MCU_ROOT_CLK_XCLK;
    } else {
        return HBN_MCU_ROOT_CLK_PLL;
    }
}

/****************************************************************************/ /**
 * @brief  Select root clk source
 *
 * @param  rootClk: root clock type selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_Type rootClk)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    CHECK_PARAM(IS_HBN_MCU_ROOT_CLK_TYPE(rootClk));

    /* root_clock_select = hbn_root_clk_sel[1] */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_GLB);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, HBN_ROOT_CLK_SEL);
    switch (rootClk) {
        case HBN_MCU_ROOT_CLK_XCLK:
            tmpVal2 &= 0x1; //[1]=0
            break;
        case HBN_MCU_ROOT_CLK_PLL:
            tmpVal2 |= 0x2; //[1]=1
            break;
        default:
            break;
    }
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_ROOT_CLK_SEL, tmpVal2);
    BL_WR_REG(HBN_BASE, HBN_GLB, tmpVal);
    HBN_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set HBN_RAM sleep mode
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Set_HRAM_slp(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_SRAM);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_RETRAM_SLP);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_RETRAM_RET);
    BL_WR_REG(HBN_BASE, HBN_SRAM, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set HBN_RAM retension mode
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Set_HRAM_Ret(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_SRAM);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_RETRAM_SLP);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_RETRAM_RET);
    BL_WR_REG(HBN_BASE, HBN_SRAM, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Power on XTAL 32K
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION HBN_Power_On_Xtal_32K(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_XTAL32K);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_XTAL32K_HIZ_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_PU_XTAL32K);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_PU_XTAL32K_BUF);
    BL_WR_REG(HBN_BASE, HBN_XTAL32K, tmpVal);

    /* Delay >1s */
    arch_delay_us(1100);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Power off XTAL 32K
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION HBN_Power_Off_Xtal_32K(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_XTAL32K);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_XTAL32K_HIZ_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PU_XTAL32K);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PU_XTAL32K_BUF);
    BL_WR_REG(HBN_BASE, HBN_XTAL32K, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Power on RC32K
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION HBN_Power_On_RC32K(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RC32K_CTRL0);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_PU_RC32K);
    BL_WR_REG(HBN_BASE, HBN_RC32K_CTRL0, tmpVal);

    /* Delay >800us */
    arch_delay_us(880);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Power off RC3K
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION HBN_Power_Off_RC32K(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RC32K_CTRL0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PU_RC32K);
    BL_WR_REG(HBN_BASE, HBN_RC32K_CTRL0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Trim RC32K
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION HBN_Trim_RC32K(void)
{
    Efuse_Ana_RC32K_Trim_Type trim;
    int32_t tmpVal = 0;

    EF_Ctrl_Read_RC32K_Trim(&trim);
    if (trim.trimRc32kExtCodeEn) {
        if (trim.trimRc32kCodeFrExtParity == EF_Ctrl_Get_Trim_Parity(trim.trimRc32kCodeFrExt, 10)) {
            tmpVal = BL_RD_REG(HBN_BASE, HBN_RC32K_CTRL0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_RC32K_CODE_FR_EXT, trim.trimRc32kCodeFrExt);
            tmpVal = BL_SET_REG_BIT(tmpVal, HBN_RC32K_EXT_CODE_EN);
            BL_WR_REG(HBN_BASE, HBN_RC32K_CTRL0, tmpVal);
            arch_delay_us(2);
            return SUCCESS;
        }
    }

    return ERROR;
}

/**
 * @brief Power Off RC32K in all state
 *
 * @return BL_Err_Type
 */
BL_Err_Type ATTR_CLOCK_SECTION HBN_PD_RC32K_All_State(void)
{
    int32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RTC_RST_CTRL2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_REG_EN_HW_PU_RC32K);
    BL_WR_REG(HBN_BASE, HBN_RTC_RST_CTRL2, tmpVal);
    HBN_Power_Off_RC32K();
    return SUCCESS;
}

/**
 * @brief Power Off RC32K In power off state
 *
 * @return BL_Err_Type
 */
BL_Err_Type ATTR_CLOCK_SECTION HBN_PD_RC32K_In_Poff(void)
{
    int32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RTC_RST_CTRL2);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_REG_EN_HW_PU_RC32K);
    BL_WR_REG(HBN_BASE, HBN_RTC_RST_CTRL2, tmpVal);
    HBN_Power_Off_RC32K();
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get HBN status flag
 *
 * @param  None
 *
 * @return HBN status flag value
 *
*******************************************************************************/
uint32_t HBN_Get_Status_Flag(void)
{
    return BL_RD_REG(HBN_BASE, HBN_RSV0);
}

/****************************************************************************/ /**
 * @brief  Set HBN status flag
 *
 * @param  flag: Status Flag
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Set_Status_Flag(uint32_t flag)
{
    BL_WR_REG(HBN_BASE, HBN_RSV0, flag);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get HBN wakeup address
 *
 * @param  None
 *
 * @return HBN wakeup address
 *
*******************************************************************************/
uint32_t HBN_Get_Wakeup_Addr(void)
{
    return BL_RD_REG(HBN_BASE, HBN_RSV1);
}

/****************************************************************************/ /**
 * @brief  Set HBN wakeup address
 *
 * @param  addr: HBN wakeup address
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Set_Wakeup_Addr(uint32_t addr)
{
    BL_WR_REG(HBN_BASE, HBN_RSV1, addr);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get core reboot flag
 *
 * @param  None
 *
 * @return repower flag
 *
*******************************************************************************/
uint8_t ATTR_TCM_SECTION HBN_Get_Core_Unhalt_Config(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RSV2);
    if (HBN_RELEASE_CORE_FLAG == BL_GET_REG_BITS_VAL(tmpVal, HBN_RELEASE_CORE)) {
        return BL_GET_REG_BITS_VAL(tmpVal, HBN_CORE_UNHALT);
    }

    return 0x00;
}

/****************************************************************************/ /**
 * @brief  Set core reboot flag
 *
 * @param  core: core ID
 * @param  hcfg: reboot cfg
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Set_Core_Reboot_Config(uint8_t core, uint8_t hcfg)
{
    uint32_t tmpVal = 0;
    uint8_t unhalt = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RSV2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_RELEASE_CORE, HBN_RELEASE_CORE_FLAG);
    unhalt = BL_GET_REG_BITS_VAL(tmpVal, HBN_CORE_UNHALT);
    if (hcfg) {
        unhalt |= (1 << core);
    } else {
        unhalt &= ~(1 << core);
    }
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_CORE_UNHALT, unhalt);
    BL_WR_REG(HBN_BASE, HBN_RSV2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get MM power flag
 *
 * @param  None
 *
 * @return repower flag
 *
*******************************************************************************/
uint8_t ATTR_TCM_SECTION HBN_Get_MM_Power_Config(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RSV2);
    if (HBN_RELEASE_CORE_FLAG == BL_GET_REG_BITS_VAL(tmpVal, HBN_RELEASE_CORE)) {
        return BL_GET_REG_BITS_VAL(tmpVal, HBN_POWER_ON_MM);
    }

    return 0x00;
}

/****************************************************************************/ /**
 * @brief  Set MM power flag
 *
 * @param  pcfg: power cfg
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Set_MM_Power_Config(uint8_t pcfg)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RSV2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_RELEASE_CORE, HBN_RELEASE_CORE_FLAG);
    if (pcfg) {
        tmpVal = BL_SET_REG_BIT(tmpVal, HBN_POWER_ON_MM);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_POWER_ON_MM);
    }
    BL_WR_REG(HBN_BASE, HBN_RSV2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get hand off config
 *
 * @param  None
 *
 * @return hand off config
 *
*******************************************************************************/
uint8_t HBN_Get_Hand_Off_Config(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RSV2);
    if (HBN_RELEASE_CORE_FLAG == BL_GET_REG_BITS_VAL(tmpVal, HBN_RELEASE_CORE)) {
        return BL_GET_REG_BITS_VAL(tmpVal, HBN_HAND_OFF_SEL);
    }

    return 0x00;
}

/****************************************************************************/ /**
 * @brief  Set hand off config
 *
 * @param  dcfg: hand off config
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Set_Hand_Off_Config(uint8_t dcfg)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RSV2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_RELEASE_CORE, HBN_RELEASE_CORE_FLAG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_HAND_OFF_SEL, dcfg);
    BL_WR_REG(HBN_BASE, HBN_RSV2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get ldo18flash repower flag
 *
 * @param  None
 *
 * @return repower flag
 *
*******************************************************************************/
uint16_t ATTR_TCM_SECTION HBN_Get_Ldo18flash_Repower_Config(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RSV2);
    if (HBN_REPOWER_LDO18FLASH_FLAG == BL_GET_REG_BITS_VAL(tmpVal, HBN_REPOWER_LDO18FLASH)) {
        return (uint16_t)tmpVal;
    }

    return 0x0000;
}

/****************************************************************************/ /**
 * @brief  Set ldo18flash repower flag
 *
 * @param  delay: repower delay time
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Set_Ldo18flash_Repower_Delay(uint8_t delay)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RSV2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_REPOWER_LDO18FLASH, HBN_REPOWER_LDO18FLASH_FLAG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_REPOWER_LDO18FLASH_DLY, delay);
    BL_WR_REG(HBN_BASE, HBN_RSV2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set Xtal type
 *
 * @param  xtalType:Xtal type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Set_Xtal_Type(uint8_t xtalType)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RSV3);

    tmpVal = tmpVal & 0xffff0000;
    tmpVal |= HBN_XTAL_FLAG_VALUE;
    tmpVal |= xtalType;

    BL_WR_REG(HBN_BASE, HBN_RSV3, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get Xtal type
 *
 * @param  None
 *
 * @return Xtal type
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Get_Xtal_Type(uint8_t *xtalType)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RSV3);

    if ((tmpVal & HBN_XTAL_FLAG_MASK) == HBN_XTAL_FLAG_VALUE) {
        *xtalType = (tmpVal & 0xff);
        return SUCCESS;
    } else {
        *xtalType = 0;
        return ERROR;
    }
}

/****************************************************************************/ /**
 * @brief  Get Xtal value
 *
 * @param  xtalVal:Xtal value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Get_Xtal_Value(uint32_t *xtalVal)
{
    uint32_t tmpVal = 0;
    uint8_t xtalType = 0;

    if (NULL == xtalVal) {
        return ERROR;
    }

    tmpVal = BL_RD_REG(HBN_BASE, HBN_RSV3);
    if ((tmpVal & HBN_XTAL_FLAG_MASK) == HBN_XTAL_FLAG_VALUE) {
        xtalType = (tmpVal & 0xff);
        switch(xtalType){
            case GLB_XTAL_NONE:
                *xtalVal = 0;
                break;
            case GLB_XTAL_24M:
                *xtalVal = 24000000;
                break;
            case GLB_XTAL_32M:
                *xtalVal = 32000000;
                break;
            case GLB_XTAL_38P4M:
                *xtalVal = 38400000;
                break;
            case GLB_XTAL_40M:
                *xtalVal = 40000000;
                break;
            case GLB_XTAL_26M:
                *xtalVal = 26000000;
                break;
            case GLB_XTAL_RC32M:
                *xtalVal = 32000000;
                break;
            default :
                *xtalVal = 0;
                break;
        }
        return SUCCESS;
    }

    *xtalVal = 0;
    return ERROR;
}

/****************************************************************************/ /**
 * @brief  HBN clear RTC timer counter
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Clear_RTC_Counter(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    /* Clear RTC control bit0 */
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal & 0xfffffffe);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN clear RTC timer counter
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Enable_RTC_Counter(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    /* Set RTC control bit0 */
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal | 0x01);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN set RTC timer configuration
 *
 * @param  delay: RTC interrupt delay 32 clocks
 * @param  compValLow: RTC interrupt commpare value low 32 bits
 * @param  compValHigh: RTC interrupt commpare value high 32 bits
 * @param  compMode: RTC interrupt commpare
 *                   mode:HBN_RTC_COMP_BIT0_39,HBN_RTC_COMP_BIT0_23,HBN_RTC_COMP_BIT13_39
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Set_RTC_Timer(HBN_RTC_INT_Delay_Type delay, uint32_t compValLow, uint32_t compValHigh, uint8_t compMode)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_HBN_RTC_INT_DELAY_TYPE(delay));

    BL_WR_REG(HBN_BASE, HBN_TIME_L, compValLow);
    BL_WR_REG(HBN_BASE, HBN_TIME_H, compValHigh & 0xff);

    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    /* Set interrupt delay option */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_RTC_DLY_OPTION, delay);
    /* Set RTC compare mode */
    tmpVal |= (compMode << 1);
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN get RTC timer count value
 *
 * @param  valLow: RTC count value pointer for low 32 bits
 * @param  valHigh: RTC count value pointer for high 8 bits
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Get_RTC_Timer_Val(uint32_t *valLow, uint32_t *valHigh)
{
    uint32_t tmpVal;

    /* Tigger RTC val read */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_RTC_TIME_H);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_RTC_TIME_LATCH);
    BL_WR_REG(HBN_BASE, HBN_RTC_TIME_H, tmpVal);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_RTC_TIME_LATCH);
    BL_WR_REG(HBN_BASE, HBN_RTC_TIME_H, tmpVal);

    /* Read RTC val */
    *valLow = BL_RD_REG(HBN_BASE, HBN_RTC_TIME_L);
    *valHigh = (BL_RD_REG(HBN_BASE, HBN_RTC_TIME_H) & 0xff);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN clear RTC timer interrupt,this function must be called to clear delayed rtc IRQ
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Clear_RTC_INT(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    /* Clear RTC commpare:bit1-3 for clearing Delayed RTC IRQ */
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal & 0xfffffff1);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN enable GPIO interrupt
 *
 * @param  gpioIntTrigType: HBN GPIO interrupt trigger type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_GPIO_INT_Enable(HBN_GPIO_INT_Trigger_Type gpioIntTrigType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_HBN_GPIO_INT_TRIGGER_TYPE(gpioIntTrigType));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_PIN_WAKEUP_MODE, gpioIntTrigType);
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN disable GPIO interrupt
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_GPIO_INT_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_PIN_WAKEUP_MASK, 0);
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN get interrupt status
 *
 * @param  irqType: HBN interrupt type
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type ATTR_TCM_SECTION HBN_Get_INT_State(HBN_INT_Type irqType)
{
    uint32_t tmpVal;

    /* Check the parameters */

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_STAT);

    if (tmpVal & (1 << irqType)) {
        return SET;
    } else {
        return RESET;
    }
}

/****************************************************************************/ /**
 * @brief  HBN get pin wakeup mode value
 *
 * @param  None
 *
 * @return HBN pin wakeup mode value
 *
*******************************************************************************/
uint8_t HBN_Get_Pin_Wakeup_Mode(void)
{
    return BL_GET_REG_BITS_VAL(BL_RD_REG(HBN_BASE, HBN_IRQ_MODE), HBN_PIN_WAKEUP_MODE);
}

/****************************************************************************/ /**
 * @brief  HBN clear interrupt status
 *
 * @param  irqType: HBN interrupt type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Clear_IRQ(HBN_INT_Type irqType)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_HBN_INT_TYPE(irqType));

    /* set clear bit */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_CLR);
    tmpVal |= (1 << irqType);
    BL_WR_REG(HBN_BASE, HBN_IRQ_CLR, tmpVal);

    /* unset clear bit */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_CLR);
    tmpVal &= (~(1 << irqType));
    BL_WR_REG(HBN_BASE, HBN_IRQ_CLR, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN hardware pullup or pulldown configuration
 *
 * @param  enable: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Hw_Pu_Pd_Cfg(uint8_t enable)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, HBN_REG_EN_HW_PU_PD);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_REG_EN_HW_PU_PD);
    }
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN wakeup pin mask configuration
 *
 * @param  maskVal: mask value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Pin_WakeUp_Mask(uint8_t maskVal)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_PIN_WAKEUP_MASK, maskVal);
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN aon pad ctrl configuration
 *
 * @param  aonPadCtl1: ctrl value 1
 * @param  aonpadCtl2: ctrl value 2
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Aon_Pad_Ctrl(uint32_t aonPadCtl1, uint32_t aonPadCtl2)
{
    BL_WR_REG(HBN_BASE, HBN_PAD_CTRL_0, aonPadCtl1);
    BL_WR_REG(HBN_BASE, HBN_PAD_CTRL_1, aonPadCtl2);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN aon pad cfg configuration
 *
 * @param  aonPadHwCtrlEn: HW Keep GPIO at PDS or HBN Mode
 * @param  aonGpio: aon pad number
 * @param  aonPadCfg: aon pad configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Aon_Pad_Cfg(uint8_t aonPadHwCtrlEn, HBN_AON_PAD_Type aonGpio, HBN_AON_PAD_CFG_Type *aonPadCfg)
{
    uint32_t tmpVal0;
    uint32_t tmpVal1;
    uint32_t enAonCtrlGpio;
    uint32_t aonPadIeSmt;
    uint32_t aonPadPu;
    uint32_t aonPadPd;
    uint32_t aonPadOe;
    uint8_t pu;
    uint8_t pd;

    CHECK_PARAM(IS_HBN_AON_PAD_TYPE(aonGpio));

    if (NULL == aonPadCfg) {
        return ERROR;
    }

    /* hbn_pad_ctrl_0 */
    tmpVal0 = BL_RD_REG(HBN_BASE, HBN_PAD_CTRL_0);
    enAonCtrlGpio = BL_GET_REG_BITS_VAL(tmpVal0, HBN_REG_EN_AON_CTRL_GPIO);
    if (aonPadCfg->ctrlEn) {
        enAonCtrlGpio |= (1 << aonGpio);
    } else {
        enAonCtrlGpio &= ~(1 << aonGpio);
    }
    tmpVal0 = BL_SET_REG_BITS_VAL(tmpVal0, HBN_REG_EN_AON_CTRL_GPIO, enAonCtrlGpio);
    aonPadIeSmt = BL_GET_REG_BITS_VAL(tmpVal0, HBN_REG_AON_PAD_IE_SMT);
    if (aonPadCfg->inputEn) {
        aonPadIeSmt |= (1 << aonGpio);
    } else {
        aonPadIeSmt &= ~(1 << aonGpio);
    }
    tmpVal0 = BL_SET_REG_BITS_VAL(tmpVal0, HBN_REG_AON_PAD_IE_SMT, aonPadIeSmt);
    BL_WR_REG(HBN_BASE, HBN_PAD_CTRL_0, tmpVal0);

    /* calc pu/pd */
    switch (aonPadCfg->pullCfg) {
        case HBN_GPIO_PAD_PULL_NONE:
            pu = 0;
            pd = 0;
            break;
        case HBN_GPIO_PAD_PULL_DOWN:
            pu = 0;
            pd = 1;
            break;
        case HBN_GPIO_PAD_PULL_UP:
            pu = 1;
            pd = 0;
            break;
        case HBN_GPIO_PAD_ACTIVE_IE:
            pu = 1;
            pd = 1;
            break;
        default:
            pu = 0;
            pd = 0;
            break;
    }

    /* hbn_pad_ctrl_1 */
    tmpVal1 = BL_RD_REG(HBN_BASE, HBN_PAD_CTRL_1);
    aonPadPu = BL_GET_REG_BITS_VAL(tmpVal1, HBN_REG_AON_PAD_PU);
    if (pu) {
        aonPadPu |= (1 << aonGpio);
    } else {
        aonPadPu &= ~(1 << aonGpio);
    }
    tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, HBN_REG_AON_PAD_PU, aonPadPu);
    aonPadPd = BL_GET_REG_BITS_VAL(tmpVal1, HBN_REG_AON_PAD_PD);
    if (pd) {
        aonPadPd |= (1 << aonGpio);
    } else {
        aonPadPd &= ~(1 << aonGpio);
    }
    tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, HBN_REG_AON_PAD_PD, aonPadPd);
    aonPadOe = BL_GET_REG_BITS_VAL(tmpVal1, HBN_REG_AON_PAD_OE);
    if (aonPadCfg->outputEn) {
        aonPadOe |= (1 << aonGpio);
    } else {
        aonPadOe &= ~(1 << aonGpio);
    }
    tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, HBN_REG_AON_PAD_OE, aonPadOe);
    BL_WR_REG(HBN_BASE, HBN_PAD_CTRL_1, tmpVal1);

    /* hw ctrl enable/disable */
    tmpVal0 = BL_RD_REG(HBN_BASE, HBN_PAD_CTRL_0);
    if (aonPadHwCtrlEn) {
        tmpVal0 = BL_SET_REG_BIT(tmpVal0, HBN_REG_AON_GPIO_ISO_MODE);
    } else {
        tmpVal0 = BL_CLR_REG_BIT(tmpVal0, HBN_REG_AON_GPIO_ISO_MODE);
    }
    BL_WR_REG(HBN_BASE, HBN_PAD_CTRL_0, tmpVal0);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN Set IO40&41 As Xtal_32K's IO
 *
 * @param  xtal32kIoEn:  Enable or disable IO40&41 As Xtal_32K's IO
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Set_IO4041_As_Xtal_32K_IO(uint8_t xtal32kIoEn)
{
    uint32_t tmpVal0;
    uint32_t tmpVal1;

    if (xtal32kIoEn) {
        tmpVal0 = BL_RD_REG(HBN_BASE, HBN_PAD_CTRL_0);
        tmpVal0 |= ((uint32_t)0x3 << 27);
        tmpVal0 &= ~((uint32_t)0x3 << 7);
        BL_WR_REG(HBN_BASE, HBN_PAD_CTRL_0, tmpVal0);

        tmpVal1 = BL_RD_REG(HBN_BASE, HBN_PAD_CTRL_1);
        tmpVal1 &= ~((uint32_t)0x3 << 7);
        BL_WR_REG(HBN_BASE, HBN_PAD_CTRL_1, tmpVal1);
    } else {
        tmpVal0 = BL_RD_REG(HBN_BASE, HBN_PAD_CTRL_0);
        tmpVal0 &= ~((uint32_t)0x3 << 27);
        tmpVal0 &= ~((uint32_t)0x3 << 7);
        BL_WR_REG(HBN_BASE, HBN_PAD_CTRL_0, tmpVal0);

        tmpVal1 = BL_RD_REG(HBN_BASE, HBN_PAD_CTRL_1);
        tmpVal1 |= ((uint32_t)0x3 << 7);
        BL_WR_REG(HBN_BASE, HBN_PAD_CTRL_1, tmpVal1);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN enable ACOMP0 interrupt
 *
 * @param  edge: HBN acomp interrupt edge type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Enable_AComp0_IRQ(HBN_ACOMP_INT_EDGE_Type edge)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    CHECK_PARAM(IS_HBN_ACOMP_INT_EDGE_TYPE(edge));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP0_EN);
    tmpVal2 = tmpVal2 | (1 << edge);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP0_EN, tmpVal2);
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN disable ACOMP0 interrupt
 *
 * @param  edge: HBN acomp interrupt edge type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Disable_AComp0_IRQ(HBN_ACOMP_INT_EDGE_Type edge)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    CHECK_PARAM(IS_HBN_ACOMP_INT_EDGE_TYPE(edge));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP0_EN);
    tmpVal2 = tmpVal2 & (~(1 << edge));
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP0_EN, tmpVal2);
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN enable ACOMP1 interrupt
 *
 * @param  edge: HBN acomp interrupt edge type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Enable_AComp1_IRQ(HBN_ACOMP_INT_EDGE_Type edge)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    CHECK_PARAM(IS_HBN_ACOMP_INT_EDGE_TYPE(edge));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP1_EN);
    tmpVal2 = tmpVal2 | (1 << edge);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP1_EN, tmpVal2);
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN disable ACOMP1 interrupt
 *
 * @param  edge: HBN acomp interrupt edge type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Disable_AComp1_IRQ(HBN_ACOMP_INT_EDGE_Type edge)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    CHECK_PARAM(IS_HBN_ACOMP_INT_EDGE_TYPE(edge));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP1_EN);
    tmpVal2 = tmpVal2 & (~(1 << edge));
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_IRQ_ACOMP1_EN, tmpVal2);
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN enable BOD interrupt
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Enable_BOD_IRQ(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_IRQ_BOR_EN);
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN disable BOD interrupt
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Disable_BOD_IRQ(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_IRQ_BOR_EN);
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN out0 install interrupt callback
 *
 * @param  intType: HBN out0 interrupt type
 * @param  cbFun: HBN out0 interrupt callback
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
BL_Err_Type HBN_Out0_Callback_Install(HBN_OUT0_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_HBN_OUT0_INT_TYPE(intType));

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(HBN_OUT0_IRQn, HBN_OUT0_IRQHandler);
#endif

    hbnInt0CbfArra[intType] = cbFun;

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  HBN out1 install interrupt callback
 *
 * @param  intType: HBN out1 interrupt type
 * @param  cbFun: HBN out1 interrupt callback
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
BL_Err_Type HBN_Out1_Callback_Install(HBN_OUT1_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_HBN_OUT1_INT_TYPE(intType));

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(HBN_OUT1_IRQn, HBN_OUT1_IRQHandler);
#endif

    hbnInt1CbfArra[intType] = cbFun;

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  HBN aon pad debbug pull config
 *
 * @param  puPdEn: Enable or disable aon pad pull down and pull up
 * @param  ieSmtEn: Enable or disable aon pad IE and SMT
 * @param  trigMode: trigger mode
 * @param  maskVal: int mask
 * @param  dlyEn: Enable or disable aon pad wakeup delay function
 * @param  dlySec: aon pad wakeup delay sec 1 to 7
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Aon_Pad_WakeUpCfg(BL_Fun_Type puPdEn, HBN_GPIO_INT_Trigger_Type trigMode, uint32_t maskVal, BL_Fun_Type dlyEn, uint8_t dlySec)
{
    uint32_t tmpVal;

    CHECK_PARAM(((dlySec >= 1) && (dlySec <= 7)));
    CHECK_PARAM(IS_HBN_GPIO_INT_TRIGGER_TYPE(trigMode));
    CHECK_PARAM((maskVal <= 0x3FF));

    tmpVal = BL_RD_REG(HBN_BASE, HBN_IRQ_MODE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_PIN_WAKEUP_EN, dlyEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_PIN_WAKEUP_SEL, dlySec);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_REG_EN_HW_PU_PD, puPdEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_PIN_WAKEUP_MASK, maskVal);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_PIN_WAKEUP_MODE, trigMode);
    BL_WR_REG(HBN_BASE, HBN_IRQ_MODE, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get RTC misc config
 *
 * @param  cfg: configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Get_RTC_Misc_Cfg(HBN_RTC_MISC_Type *cfg)
{
    uint32_t tmpVal = 0;
    uint32_t *pCfg = (uint32_t *)cfg;

    if (!cfg) {
        return ERROR;
    }

    /* read [31:19] */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_RTC_RST_CTRL);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, HBN_RTC_RST_CTRL_MISC);

    /* use [30:19] */
    *pCfg = tmpVal;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set RTC misc config
 *
 * @param  cfg: configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION HBN_Set_RTC_Misc_Cfg(HBN_RTC_MISC_Type *cfg)
{
    uint32_t tmpVal = 0;

    if (!cfg) {
        return ERROR;
    }

    /* read [31:19] */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_RTC_RST_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_RTC_RST_CTRL_MISC, ((*(uint32_t *)cfg)<<1));
    BL_WR_REG(HBN_BASE, HBN_RTC_RST_CTRL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set Embedded Flash Pullup enabe or disable
 *
 * @param  cfg: Enable or disable
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type HBN_Set_BOD_Cfg(HBN_BOD_CFG_Type *cfg)
{
    uint32_t tmpVal = 0;

    if (cfg->enableBodInt) {
        HBN_Enable_BOD_IRQ();
    } else {
        HBN_Disable_BOD_IRQ();
    }

    tmpVal = BL_RD_REG(HBN_BASE, HBN_BOR_CFG);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, HBN_BOD_VTH, cfg->bodThreshold);
    if (cfg->enablePorInBod) {
        tmpVal = BL_SET_REG_BIT(tmpVal, HBN_BOD_SEL);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_BOD_SEL);
    }

    if (cfg->enableBod) {
        tmpVal = BL_SET_REG_BIT(tmpVal, HBN_PU_BOD);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_PU_BOD);
    }

    BL_WR_REG(HBN_BASE, HBN_BOR_CFG, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  HBN OUT0 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void HBN_OUT0_IRQHandler(void)
{
    HBN_OUT0_INT_Type out0Int = HBN_OUT0_INT_GPIO9;

    /* GPIO and RTC */
    for (HBN_INT_Type gpioInt = HBN_INT_GPIO9; gpioInt <= HBN_INT_GPIO41; gpioInt++) {
        if (SET == HBN_Get_INT_State(gpioInt)) {
            HBN_Clear_IRQ(gpioInt);
            switch (gpioInt) {
                case HBN_INT_GPIO9:
                    out0Int = HBN_OUT0_INT_GPIO9;
                    break;
                case HBN_INT_GPIO10:
                    out0Int = HBN_OUT0_INT_GPIO10;
                    break;
                case HBN_INT_GPIO11:
                    out0Int = HBN_OUT0_INT_GPIO11;
                    break;
                case HBN_INT_GPIO12:
                    out0Int = HBN_OUT0_INT_GPIO12;
                    break;
                case HBN_INT_GPIO13:
                    out0Int = HBN_OUT0_INT_GPIO13;
                    break;
                case HBN_INT_GPIO14:
                    out0Int = HBN_OUT0_INT_GPIO14;
                    break;
                case HBN_INT_GPIO15:
                    out0Int = HBN_OUT0_INT_GPIO15;
                    break;
                case HBN_INT_GPIO40:
                    out0Int = HBN_OUT0_INT_GPIO40;
                    break;
                case HBN_INT_GPIO41:
                    out0Int = HBN_OUT0_INT_GPIO41;
                    break;
                default:
                    break;
            }
            if (hbnInt0CbfArra[out0Int] != NULL) {
                hbnInt0CbfArra[out0Int]();
            }
        }
    }
    if (SET == HBN_Get_INT_State(HBN_INT_RTC)) {
        HBN_Clear_IRQ(HBN_INT_RTC);
        if (hbnInt0CbfArra[HBN_OUT0_INT_RTC] != NULL) {
            hbnInt0CbfArra[HBN_OUT0_INT_RTC]();
        }
    }
}
#endif

/****************************************************************************/ /**
 * @brief  HBN OUT1 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void HBN_OUT1_IRQHandler(void)
{
    /* PIR */
    if (SET == HBN_Get_INT_State(HBN_INT_PIR)) {
        HBN_Clear_IRQ(HBN_INT_PIR);
        if (hbnInt1CbfArra[HBN_OUT1_INT_PIR] != NULL) {
            hbnInt1CbfArra[HBN_OUT1_INT_PIR]();
        }
    }
    /* BOD */
    if (SET == HBN_Get_INT_State(HBN_INT_BOD)) {
        HBN_Clear_IRQ(HBN_INT_BOD);
        if (hbnInt1CbfArra[HBN_OUT1_INT_BOD] != NULL) {
            hbnInt1CbfArra[HBN_OUT1_INT_BOD]();
        }
    }
    /* ACOMP0 */
    if (SET == HBN_Get_INT_State(HBN_INT_ACOMP0)) {
        HBN_Clear_IRQ(HBN_INT_ACOMP0);
        if (hbnInt1CbfArra[HBN_OUT1_INT_ACOMP0] != NULL) {
            hbnInt1CbfArra[HBN_OUT1_INT_ACOMP0]();
        }
    }
    /* ACOMP1 */
    if (SET == HBN_Get_INT_State(HBN_INT_ACOMP1)) {
        HBN_Clear_IRQ(HBN_INT_ACOMP1);
        if (hbnInt1CbfArra[HBN_OUT1_INT_ACOMP1] != NULL) {
            hbnInt1CbfArra[HBN_OUT1_INT_ACOMP1]();
        }
    }
}
#endif

/*@} end of group HBN_Public_Functions */

/*@} end of group HBN */

/*@} end of group BL808_Peripheral_Driver */
