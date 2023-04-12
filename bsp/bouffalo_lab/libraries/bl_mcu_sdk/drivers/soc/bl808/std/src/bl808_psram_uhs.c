/**
  ******************************************************************************
  * @file    bl808_psram_uhs.c
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

#include "bl808_psram_uhs.h"
#include "bl808_uhs_phy.h"
#include "bl808_common.h"
#include "bl808_glb.h"
#include "psram_uhs_reg.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PSRAM_UHS
 *  @{
 */

/** @defgroup  PSRAM_UHS_Private_Macros
 *  @{
 */
#define PSRAM_UHS_RW_TIMEOUT 0xffffffff
/*@} end of group PSRAM_UHS_Private_Macros */

/** @defgroup  PSRAM_UHS_Private_Types
 *  @{
 */

/*@} end of group PSRAM_UHS_Private_Types */

/** @defgroup  PSRAM_UHS_Private_Variables
 *  @{
 */

/*@} end of group PSRAM_UHS_Private_Variables */

/** @defgroup  PSRAM_UHS_Global_Variables
 *  @{
 */

/*@} end of group PSRAM_UHS_Global_Variables */

/** @defgroup  PSRAM_UHS_Private_Fun_Declaration
 *  @{
 */

/*@} end of group PSRAM_UHS_Private_Fun_Declaration */

/** @defgroup  PSRAM_UHS_Private_Functions
 *  @{
 */

/*@} end of group PSRAM_UHS_Private_Functions */

/** @defgroup  PSRAM_UHS_Public_Functions
 *  @{
 */
int config_uhs_phy(uint32_t datarate)
{
    uint32_t tmpVal = 0;

    if (datarate > 1866) {
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_30_OFFSET, 0x0F0A1323);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_34_OFFSET, 0x0b030404);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_38_OFFSET, 0x050e0419);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_3C_OFFSET, 0x0a6a1c1c);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_44_OFFSET, 0x0711070e);

        tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_PHY_WL_CEN_ANA, 1);
        BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50, tmpVal);

    } else if (datarate > 1600) {
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_30_OFFSET, 0x0F283203);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_34_OFFSET, 0x0a020303);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_38_OFFSET, 0x040d0416);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_3C_OFFSET, 0x091e1818);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_44_OFFSET, 0x0710070d);

        tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_PHY_WL_CEN_ANA, 3);
        BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50, tmpVal);

    } else if (datarate > 1066) {
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_30_OFFSET, 0x0F270212);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_34_OFFSET, 0x09020303);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_38_OFFSET, 0x040c0313);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_3C_OFFSET, 0x07d11515);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_44_OFFSET, 0x060f060c);

        tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_PHY_WL_CEN_ANA, 1);
        BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50, tmpVal);
    } else if (datarate > 800) {
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_30_OFFSET, 0x0F270212);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_34_OFFSET, 0x06010202);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_38_OFFSET, 0x0309020d);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_3C_OFFSET, 0x05360e0e);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_44_OFFSET, 0x050c0509);

        tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_PHY_WL_CEN_ANA, 1);
        BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50, tmpVal);

    } else if (datarate > 666) {
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_30_OFFSET, 0x0F041020);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_34_OFFSET, 0x05000101);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_38_OFFSET, 0x0208010a);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_3C_OFFSET, 0x03e90b0b);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_44_OFFSET, 0x040b0408);

        tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_PHY_WL_CEN_ANA, 0);
        BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50, tmpVal);
    } else if (datarate > 400) {
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_30_OFFSET, 0x0F130010);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_34_OFFSET, 0x05000101);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_38_OFFSET, 0x02080108);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_3C_OFFSET, 0x03420909);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_44_OFFSET, 0x040b0408);

        tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_PHY_WL_CEN_ANA, 0);
        BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50, tmpVal);
    } else {
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_30_OFFSET, 0x0F020010);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_34_OFFSET, 0x04000101);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_38_OFFSET, 0x02070106);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_3C_OFFSET, 0x01f50606);
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_44_OFFSET, 0x040a0407);

        tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_PHY_WL_CEN_ANA, 0);
        BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50, tmpVal);
    }
    return 0;
}

static void power_up_ldo12uhs(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(GLB_BASE, GLB_LDO12UHS);

#ifdef BL808D_REWORK
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_LDO12UHS_PULLDOWN, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_LDO12UHS_PULLDOWN_SEL, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_PU_LDO12UHS, 0);
#else
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_PU_LDO12UHS, 1);
    BL_WR_REG(GLB_BASE, GLB_LDO12UHS, tmpVal);
    arch_delay_us(300);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_LDO12UHS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_LDO12UHS_VOUT_SEL, 6);
#endif
    BL_WR_REG(GLB_BASE, GLB_LDO12UHS, tmpVal);
    arch_delay_us(1);
}

static void set_cen_ck_ckn(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_DQ_OE_MID_N_REG, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_DQ_OE_MID_P_REG, 0);
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50, tmpVal);
    arch_delay_us(1);
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_40);
    tmpVal &= 0xFFFCFFFF;
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_UHS_DMY0, 1);
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_40, tmpVal);
    arch_delay_us(1);
}

static int set_or_uhs(uint32_t datarate)
{
    uint32_t tmpVal = 0;
    uint32_t *uhs_phy_cfg_base_addr = (uint32_t *)(PSRAM_UHS_BASE + PSRAM_UHS_PHY_CFG_00_OFFSET);
    // clang-format off
    const static uint32_t uhs_phy_cfg_data[] ={
    0x802b0200, 0x60206020, 0x70027002, 0x70027002,
    0x70027002, 0x70027002, 0x70027002, 0x70027002,
    0x70027002, 0x70027002, 0x26000000, 0x26000006,
    };
    // clang-format on

    for (uint32_t i = 0; i < 12; i++) {
        uhs_phy_cfg_base_addr[i] = uhs_phy_cfg_data[i];
    }

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_30);
    tmpVal &= 0x08ffffff;
    tmpVal |= 0x07000000;
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_30, tmpVal);

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_48);
    tmpVal &= 0xfffffcff;
    tmpVal |= 0x00000200;
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_48, tmpVal);

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_4C);
    tmpVal &= 0xffe0ffff;
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_4C, tmpVal);

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50);
    tmpVal &= 0xff88ff88;
    tmpVal |= 0x00330033;
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50, tmpVal);

    arch_delay_us(1);

    return 0;
}
static void switch_to_ldo12uhs(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_40);
    tmpVal &= 0xFFCFFFFF;
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_40, tmpVal);
    arch_delay_us(1);
}

static void release_cen_ck_ckn(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_40);
    tmpVal &= 0xFFFCFEFF;
#ifdef BL808D_REWORK
    tmpVal |= 0x10000;
#else
    tmpVal |= 0x30000;
#endif
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_40, tmpVal);
    arch_delay_us(1);

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_DQ_OE_MID_N_REG, 3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_DQ_OE_MID_P_REG, 3);
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50, tmpVal);
    arch_delay_us(1);
}

static void Psram_analog_init(uint32_t pck_freq)
{
    /* power on ldo12 */
    power_up_ldo12uhs();

    /* set cen ck ckn */
    set_cen_ck_ckn();

    /*
     * overwrite default register content
     * only support 2000M and 1500MHZ
     */
    set_or_uhs(pck_freq);

    /* switch to ldo12 */
    switch_to_ldo12uhs();

    /* release cen ck */
    release_cen_ck_ckn();

    /* config phy paramater */
    config_uhs_phy(pck_freq);
}

/****************************************************************************/ /**
 * @brief  Init Psram UHS ,set auto refresh cycle
 *
 * @param  cfg: pck frequency unit is MHZ
 *
 * @return None
 *
*******************************************************************************/
void Psram_UHS_Init(PSRAM_UHS_Cfg_Type *cfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_PSRAM_UHS_MEM_SIZE_TYPE(cfg->psramMemSize));
    CHECK_PARAM(IS_PSRAM_UHS_PAGE_SIZE_TYPE(cfg->psramPageSize));

    if (cfg->pck_freq > 2300) {
        /* max support 2300MHZ */
        while (1)
            ;
    } else if (cfg->pck_freq > 1600) {
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_UHS_TIMING_CTRL_OFFSET, 0x1a03000f);
    } else {
        BL_WR_WORD(PSRAM_UHS_BASE + PSRAM_UHS_UHS_TIMING_CTRL_OFFSET, 0x1202000b);
    }

    Psram_analog_init(cfg->pck_freq);

    /* Wait 150 us */
    arch_delay_us(150);

    /* set refresh paramater */
    /* 1. auto refresh clock source is pck_t, Adjust pck_t_div so that the frequency is around ~50Mhz */
    /*     tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_MANUAL);
    tmpVal &= 0x00ffffff;

    if (cfg->pck_freq >= 2200) {
        tmpVal |= 0x05000000;
    } else if (cfg->pck_freq >= 2000) {
        tmpVal |= 0x04000000;
    } else if (cfg->pck_freq >= 1500) {
        tmpVal |= 0x03000000;
    } else if (cfg->pck_freq >= 1400) {
        tmpVal |= 0x02000000;
    } else if (cfg->pck_freq >= 666) {
        tmpVal |= 0x01000000;
    }
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_MANUAL, tmpVal); */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_MANUAL);
    tmpVal &= 0x00ffffff;

    if (cfg->pck_freq >= 2200) {
        tmpVal |= 0x05000000;
    } else if (cfg->pck_freq >= 1800) {
        tmpVal |= 0x04000000;
    } else if (cfg->pck_freq >= 1500) {
        tmpVal |= 0x03000000;
    } else if (cfg->pck_freq >= 1400) {
        tmpVal |= 0x02000000;
    } else if (cfg->pck_freq >= 666) {
        tmpVal |= 0x01000000;
    }
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_MANUAL, tmpVal);

    /* 2. setting refresh windows cycle count
     * reg_win_cycle = refresh_window / Tpck_y
     *
     * refresh_window unit is ms
     * when refresh tempotory > 85
     *      refresh_window = 16
     * elsee
     *      refresh_window = 32
     */
    if (cfg->isHighTem == PSRAM_UHS_NORMAL_TEMP) {
        BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_AUTO_FRESH_1, 0x16e360);
    } else {
        BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_AUTO_FRESH_1, 0xB71B0);
    }
    /* 3 & 4. setting refresh count in a windows fixed value 4096 in v0.2
     * calculate Average cycle between two auto-refresh
     * reg_refi_cycle = reg_win_cycle / reg_win_ref_cnt
     * */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_AUTO_FRESH_2);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_WIN_REF_CNT, 0x1000);
    if (cfg->isHighTem == PSRAM_UHS_NORMAL_TEMP) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_REFI_CYCLE, (370));
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_REFI_CYCLE, (190));
    }
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_AUTO_FRESH_2, tmpVal);

    /* 5 setting single auto refresh time */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_AUTO_FRESH_4);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_BUST_CYCLE, (uint32_t)(90 / T_pck_t));
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_BUST_CYCLE, 5);
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_AUTO_FRESH_4, tmpVal);

    /* 6 auto-refesh enable */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_AF_EN);

    /* 7&8 . set psram memory size and page size */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_ADDRMB_MSK, cfg->psramMemSize);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_LINEAR_BND_B, cfg->psramPageSize);
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC, tmpVal);

    /* 9. psram enable initial */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_INIT_EN);
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Read register for uhs
 *
 * @param  reg_addr: read addr
 * @param  regVal: regVal
 *
 * @return success or not
 *
*******************************************************************************/
int PSram_UHS_Read_Reg(uint32_t reg_addr, uint8_t *regVal)
{
    uint32_t tmpVal = 0;
    uint32_t cnt = 0;

    /* 1 generate requeset and wait authorization*/
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_CONFIG_REQ);
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC, tmpVal);

    do {
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
        cnt++;
        if (cnt > PSRAM_UHS_RW_TIMEOUT)
            return -1;
    } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_UHS_REG_CONFIG_GNT));

    /* 2 set mode reg */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_MODE_REG, reg_addr);
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC, tmpVal);

    /* 3 enable controller Rx*/
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD);
    tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_REGR_PULSE);
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD, tmpVal);

    cnt = 0;

    /* 4 wait read done */
    do {
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD);
        cnt++;
        if (cnt > PSRAM_UHS_RW_TIMEOUT)
            return -1;
    } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_UHS_STS_REGR_DONE));

    /* 5 steup up read data */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD);

    *regVal = (uint8_t)(BL_GET_REG_BITS_VAL(tmpVal, PSRAM_UHS_STS_CONFIG_READ));

    /* 6 cancel requeset singnal */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_UHS_REG_CONFIG_REQ);
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC, tmpVal);

    return 0;
}

/****************************************************************************/ /**
 * @brief  write register for winbond PSRAM
 *
 * @param  regCfg: wirte reg data
 *
 * @return None
 *
*******************************************************************************/
int PSram_UHS_Write_Reg(PSRAM_UHS_Write_Reg_Cfg_Type *regCfg)
{
    uint32_t tmpVal = 0;
    uint32_t cnt = 0;
    uint8_t regWriteList[] = { 0, 2 };
    uint8_t i = 0;

    CHECK_PARAM(IS_PSRAM_UHS_DRIVER_ST_TYPE(regCfg->driver_st));
    CHECK_PARAM(IS_PSRAM_UHS_WARP_BURST_TYPE(regCfg->burst_size));
    CHECK_PARAM(IS_PSRAM_UHS_LATENCY_TYPE(regCfg->lentency));

    /* 1 congfi write reg*/
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_PSRAM_CONFIGURE);

    switch (regCfg->burst_size) {
        case PSRAM_UHS_WARP_BURST_64:
            tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_UHS_BL_64);
            tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_UHS_REG_UHS_BL_32);
            tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_UHS_REG_UHS_BL_16);
            break;
        case PSRAM_UHS_WARP_BURST_32:
            tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_UHS_REG_UHS_BL_16);
            tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_UHS_BL_32);
            tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_UHS_REG_UHS_BL_64);
            break;
        case PSRAM_UHS_WARP_BURST_16:
            tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_UHS_BL_16);
            tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_UHS_REG_UHS_BL_32);
            tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_UHS_REG_UHS_BL_64);
            break;
        case PSRAM_UHS_WARP_BURST_NONE:
            tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_UHS_REG_UHS_BL_16);
            tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_UHS_REG_UHS_BL_32);
            tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_UHS_REG_UHS_BL_64);
            break;
        default:
            return -1;
    }
    if (regCfg->driver_st != PSRAM_UHS_DRIVER_ST_NO_CHANGE) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_UHS_DRIVE_ST, regCfg->driver_st);
    }
    if (regCfg->lentency != PSRAM_UHS_LATENCY_NO_CHANGE) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_UHS_LATENCY, regCfg->lentency);
    }

    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_PSRAM_CONFIGURE, tmpVal);

    /* 2 generate requeset and wait authorization */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_CONFIG_REQ);
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC, tmpVal);

    do {
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
        cnt++;
        if (cnt > PSRAM_UHS_RW_TIMEOUT)
            return -1;
    } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_UHS_REG_CONFIG_GNT));

    for (i = 0; i < sizeof(regWriteList) / sizeof(uint8_t); i++) {
        /* 3 set mode reg */
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_MODE_REG, regWriteList[i]);
        BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC, tmpVal);

        /* 4 enable controller */
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD);
        tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_REGW_PULSE);
        BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD, tmpVal);

        cnt = 0;

        /* 5 wait write done */
        do {
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD);
            cnt++;
            if (cnt > PSRAM_UHS_RW_TIMEOUT)
                return -1;
        } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_UHS_STS_REGW_DONE));
    }

    /* 6 cancel requeset singnal */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_UHS_REG_CONFIG_REQ);
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC, tmpVal);

    return 0;
}

/****************************************************************************/ /**
 * @brief  Timing Reset
 *
 * @param  reg_addr: reg_addr
 * @param  regCfg: wirte reg data
 *
 * @return None
 *
*******************************************************************************/
int PSram_UHS_Timing_Reset(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_40);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_UHS_DMY1, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_UHS_DMY0, 1);

    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_40, tmpVal);

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_DQ_OE_MID_N_REG, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_DQ_OE_MID_P_REG, 0);

    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50, tmpVal);

    arch_delay_us(1000);

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_40);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_UHS_DMY1, 3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_UHS_DMY0, 0);

    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_40, tmpVal);

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_DQ_OE_MID_N_REG, 4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_DQ_OE_MID_P_REG, 4);

    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_PHY_CFG_50, tmpVal);

    return 0;
}

/****************************************************************************/ /**
 * @brief  construct cmd wave for psram
 *
 * @param  reg_addr: reg_addr
 * @param  regCfg: wirte reg data
 *
 * @return None
 *
*******************************************************************************/
int PSram_UHS_Construct_Cmd(PSRAM_UHS_CMD_Type cmd)
{
    uint32_t tmpVal = 0;
    uint32_t cnt = 0;

    CHECK_PARAM(IS_PSRAM_UHS_CMD_TYPE(cmd));

    /*  generate requeset and wait authorization*/
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_CONFIG_REQ);
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC, tmpVal);

    do {
        tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
        cnt++;
        if (cnt > PSRAM_UHS_RW_TIMEOUT)
            goto exit;
    } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_UHS_REG_CONFIG_GNT));

    /*  enable cmd generate */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD);

    switch (cmd) {
        case PSRAM_UHS_CMD_SELF_REFRESH_IN:
            tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_SRFI_PULSE);
            break;
        case PSRAM_UHS_CMD_SELF_REFRESH_EXIT:
            tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_SRFO_PULSE);
            break;
        case PSRAM_UHS_CMD_GLOBAL_RESET:
            tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_GLBR_PULSE);
            /* Wait 15 us for reset */
            arch_delay_us(15);
            break;
        case PSRAM_UHS_CMD_ZQ_CAL_LONG:

            /* 3 set mode reg */
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_MODE_REG, 5);
            BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC, tmpVal);

            /* 4 enable controller */
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD);
            tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_REGW_PULSE);
            BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD, tmpVal);

            cnt = 0;

            /* 5 wait write done */
            do {
                tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD);
                cnt++;
                if (cnt > PSRAM_UHS_RW_TIMEOUT)
                    goto exit;
            } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_UHS_STS_REGW_DONE));

            break;
        case PSRAM_UHS_CMD_ZQ_CAL_SHORT:

            /* 3 set mode reg */
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_MODE_REG, 6);
            BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC, tmpVal);

            /* 4 enable controller */
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD);
            tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_REGW_PULSE);
            BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD, tmpVal);

            cnt = 0;

            /* 5 wait write done */
            do {
                tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD);
                cnt++;
                if (cnt > PSRAM_UHS_RW_TIMEOUT)
                    goto exit;
            } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_UHS_STS_REGW_DONE));
            break;
        case PSRAM_UHS_CMD_ZQ_CAL_RESET:

            /* 3 set mode reg */
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_UHS_REG_MODE_REG, 7);
            BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC, tmpVal);

            /* 4 enable controller */
            tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD);
            tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_UHS_REG_REGW_PULSE);
            BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD, tmpVal);

            cnt = 0;

            /* 5 wait write done */
            do {
                tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD);
                cnt++;
                if (cnt > PSRAM_UHS_RW_TIMEOUT)
                    goto exit;
            } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_UHS_STS_REGW_DONE));
            break;
        default:
            goto exit;
            break;
    }

    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD, tmpVal);

    cnt = 0;

    /*  wait write done */
    switch (cmd) {
        case PSRAM_UHS_CMD_SELF_REFRESH_IN:
            do {
                tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD);
                cnt++;
                if (cnt > PSRAM_UHS_RW_TIMEOUT)
                    goto exit;

            } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_UHS_STS_SRFI_DONE));
            break;
        case PSRAM_UHS_CMD_SELF_REFRESH_EXIT:
            do {
                tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD);
                cnt++;
                if (cnt > PSRAM_UHS_RW_TIMEOUT)
                    goto exit;

            } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_UHS_STS_SRFO_DONE));
            break;
        case PSRAM_UHS_CMD_GLOBAL_RESET:
            do {
                tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_CMD);
                cnt++;
                if (cnt > PSRAM_UHS_RW_TIMEOUT)
                    goto exit;

            } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_UHS_STS_GLBR_DONE));
            break;
        default:
            goto exit;
    }

    /* 6 cancel requeset singnal */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_UHS_REG_CONFIG_REQ);
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC, tmpVal);

    return 0;

exit:
    /* 6 cancel requeset singnal */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_UHS_REG_CONFIG_REQ);
    BL_WR_REG(PSRAM_UHS_BASE, PSRAM_UHS_UHS_BASIC, tmpVal);

    return -1;
}

/**
 * @brief defualt init for 64MB x16 UHS PSRAM
 *        user should enable UHS PSRAM PLL before call this function
 * @param uhs_pll_clk The uhs pll frequency used
 */
void Psram_UHS_x16_Init(uint32_t uhs_pll_clk)
{
    PSRAM_UHS_Cfg_Type psramDefaultCfg = {
        2000,
        PSRAM_MEM_SIZE_64MB,
        PSRAM_PAGE_SIZE_2KB,
        PSRAM_UHS_NORMAL_TEMP,
    };

    PSRAM_UHS_Write_Reg_Cfg_Type writeReg = {
        PSRAM_UHS_DRIVER_ST_40_PDPU,
        PSRAM_UHS_WARP_BURST_NONE,
        PSRAM_UHS_LATENCY_W18_R37_MAX_FRE_1066_MHZ,
    };

    psramDefaultCfg.pck_freq = uhs_pll_clk;

    if ((uhs_pll_clk >= 2000) && (uhs_pll_clk <= 2300)) {
        writeReg.lentency = PSRAM_UHS_LATENCY_W18_R37_MAX_FRE_1066_MHZ;
    } else if ((uhs_pll_clk <= 1600) && (uhs_pll_clk > 1066)) {
        writeReg.lentency = PSRAM_UHS_LATENCY_W14_R29_MAX_FRE_800_MHZ;
    } else if ((uhs_pll_clk < 1067) && (uhs_pll_clk > 800)) {
        writeReg.lentency = PSRAM_UHS_LATENCY_W10_R20_MAX_FRE_533_MHZ;
    } else if ((uhs_pll_clk <= 800) && (uhs_pll_clk > 667)) {
        writeReg.lentency = PSRAM_UHS_LATENCY_W6_R16_MAX_FRE_400_MHZ;
    } else if ((uhs_pll_clk < 667) && (uhs_pll_clk > 400)) {
        writeReg.lentency = PSRAM_UHS_LATENCY_W5_R13_MAX_FRE_333_MHZ;
    } else if (uhs_pll_clk <= 400) {
        writeReg.lentency = PSRAM_UHS_LATENCY_W5_R9_MAX_FRE_200_MHZ;
    }

    /* first initial psram controller*/
    Psram_UHS_Init(&psramDefaultCfg);

    /* reset psram device*/
    PSram_UHS_Construct_Cmd(PSRAM_UHS_CMD_GLOBAL_RESET);

    arch_delay_us(100);

    /* write 1GHZ configuration to psram device */
    PSram_UHS_Write_Reg(&writeReg);
}

void Psram_UHS_x16_Init_Override(PSRAM_UHS_Cfg_Type *cfg)
{
    /* first initial psram controller*/
    Psram_UHS_Init(cfg);

    uhs_phy_init(cfg);
}
/*@} end of group PSRAM_UHS_Public_Functions */

/*@} end of group PSRAM_UHS */

/*@} end of group BL808_Peripheral_Driver */
