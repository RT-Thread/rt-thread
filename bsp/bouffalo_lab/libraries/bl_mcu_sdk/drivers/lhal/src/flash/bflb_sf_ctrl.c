/**
  ******************************************************************************
  * @file    bl628_sf_ctrl.c
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

#include "bflb_sf_ctrl.h"
#include "include/hardware/sf_ctrl_reg.h"
#if defined(BL602) || defined(BL702) || defined(BL702L)
#include <risc-v/e24/clic.h>
#else
#include <csi_core.h>
#endif

/** @addtogroup  BL628_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SF_CTRL
 *  @{
 */

/** @defgroup  SF_CTRL_Private_Macros
 *  @{
 */

/*@} end of group SF_CTRL_Private_Macros */

/** @defgroup  SF_CTRL_Private_Types
 *  @{
 */

/*@} end of group SF_CTRL_Private_Types */

/** @defgroup  SF_CTRL_Private_Variables
 *  @{
 */

#if defined(BL702) || defined(BL702L)
#define bflb_sf_ctrl_get_aes_region(addr, r) (addr + SF_CTRL_AES_REGION_OFFSET + (r)*0x100)
#else
#define bflb_sf_ctrl_get_aes_region(addr, r) (addr + SF_CTRL_AES_REGION_OFFSET + (r)*0x80)
#endif
#define BL_RDWD_FRM_BYTEP(p)                 ((p[3] << 24) | (p[2] << 16) | (p[1] << 8) | (p[0]))

/*@} end of group SF_CTRL_Private_Variables */

/** @defgroup  SF_CTRL_Global_Variables
 *  @{
 */

/*@} end of group SF_CTRL_Global_Variables */

/** @defgroup  SF_CTRL_Private_Fun_Declaration
 *  @{
 */

/*@} end of group SF_CTRL_Private_Fun_Declaration */

/** @defgroup  SF_CTRL_Private_Functions
 *  @{
 */

/*@} end of group SF_CTRL_Private_Functions */

/** @defgroup  SF_CTRL_Public_Functions
 *  @{
 */

#if defined(BL702L) || defined(BL702) || defined(BL602)
__attribute__((always_inline)) __STATIC_INLINE uint32_t __REV(uint32_t value)
{
    //return __builtin_bswap32(value);
    uint32_t res = 0;

    res = (value << 24) | (value >> 24);
    res &= 0xFF0000FF; /* only for sure */
    res |= ((value >> 8) & 0x0000FF00) | ((value << 8) & 0x00FF0000);

    return res;
}
#endif

/****************************************************************************/ /**
 * @brief  Enable serail flash controller
 *
 * @param  cfg: serial flash controller config
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_enable(const struct sf_ctrl_cfg_type *cfg)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;
    uint32_t time_out = 0;

    if (cfg == NULL) {
        return;
    }

    reg_base = BFLB_SF_CTRL_BASE;
    time_out = SF_CTRL_BUSY_STATE_TIMEOUT;

    while (bflb_sf_ctrl_get_busy_state()) {
        time_out--;

        if (time_out == 0) {
            return;
        }
    }

    regval = getreg32(reg_base + SF_CTRL_0_OFFSET);
#ifdef BFLB_SF_CTRL_32BITS_ADDR_ENABLE
    if (cfg->en32b_addr) {
        regval |= SF_CTRL_SF_IF_32B_ADR_EN;
    } else {
        regval &= ~SF_CTRL_SF_IF_32B_ADR_EN;
    }
#endif

    if (cfg->clk_delay > 0) {
        regval |= SF_CTRL_SF_IF_READ_DLY_EN;
        regval &= ~SF_CTRL_SF_IF_READ_DLY_N_MASK;
        regval |= ((cfg->clk_delay-1) << SF_CTRL_SF_IF_READ_DLY_N_SHIFT);
    } else {
        regval &= ~SF_CTRL_SF_IF_READ_DLY_EN;
    }

    /* Serail out inverted, so sf ctrl send on negative edge */
    if (cfg->clk_invert) {
        regval |= SF_CTRL_SF_CLK_OUT_INV_SEL;
    } else {
        regval &= ~SF_CTRL_SF_CLK_OUT_INV_SEL;
    }
    if (cfg->rx_clk_invert) {
        regval |= SF_CTRL_SF_CLK_SF_RX_INV_SEL;
    } else {
        regval &= ~SF_CTRL_SF_CLK_SF_RX_INV_SEL;
    }
    putreg32(regval, reg_base+SF_CTRL_0_OFFSET);

#if defined(BL602) ||defined(BL702) || defined(BL702L)
    bflb_sf_ctrl_set_io_delay(0, cfg->do_delay, cfg->di_delay, cfg->oe_delay);
    bflb_sf_ctrl_set_io_delay(1, cfg->do_delay, cfg->di_delay, cfg->oe_delay);
    bflb_sf_ctrl_set_io_delay(2, cfg->do_delay, cfg->di_delay, cfg->oe_delay);
#endif

    /* Enable AHB access sram buffer and enable sf interface */
    regval = getreg32(reg_base + SF_CTRL_1_OFFSET);
    regval |= SF_CTRL_SF_AHB2SRAM_EN;
    regval |= SF_CTRL_SF_IF_EN;
    putreg32(regval, reg_base+SF_CTRL_1_OFFSET);

    bflb_sf_ctrl_set_owner(cfg->owner);
}

/****************************************************************************/ /**
 * @brief  SF Ctrl set io delay
 *
 * @param  pad: Pad select
 * @param  do_delay: DO delay select
 * @param  di_delay: DI delay select
 * @param  oe_delay: OE delay select
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_set_io_delay(uint8_t pad, uint8_t do_delay, uint8_t di_delay, uint8_t oe_delay)
{
    uint32_t offset = 0;
    uint32_t regval = 0;

    if (pad == SF_CTRL_PAD1) {
        offset = BFLB_SF_CTRL_BASE + SF_CTRL_IF_IO_DLY_1_OFFSET;
    } else if (pad == SF_CTRL_PAD2) {
        offset = BFLB_SF_CTRL_BASE + SF_CTRL_IF_IO_DLY_2_OFFSET;
    } else {
        offset = BFLB_SF_CTRL_BASE + SF_CTRL_IF_IO_DLY_3_OFFSET;
    }

    /* Set do di and oe delay */
    regval = getreg32(offset + SF_CTRL_IO_DLY_1_OFFSET);
    regval &= ~SF_CTRL_IO_0_DO_DLY_SEL_MASK;
    regval |= (do_delay << SF_CTRL_IO_0_DO_DLY_SEL_SHIFT);
    regval &= ~SF_CTRL_IO_0_DI_DLY_SEL_MASK;
    regval |= (di_delay << SF_CTRL_IO_0_DI_DLY_SEL_SHIFT);
    regval &= ~SF_CTRL_IO_0_OE_DLY_SEL_MASK;
    regval |= (oe_delay << SF_CTRL_IO_0_OE_DLY_SEL_SHIFT);
    putreg32(regval, offset + SF_CTRL_IO_DLY_1_OFFSET);

    regval = getreg32(offset + SF_CTRL_IO_DLY_2_OFFSET);
    regval &= ~SF_CTRL_IO_1_DO_DLY_SEL_MASK;
    regval |= (do_delay << SF_CTRL_IO_1_DO_DLY_SEL_SHIFT);
    regval &= ~SF_CTRL_IO_1_DI_DLY_SEL_MASK;
    regval |= (di_delay << SF_CTRL_IO_1_DI_DLY_SEL_SHIFT);
    regval &= ~SF_CTRL_IO_1_OE_DLY_SEL_MASK;
    regval |= (oe_delay << SF_CTRL_IO_1_OE_DLY_SEL_SHIFT);
    putreg32(regval, offset + SF_CTRL_IO_DLY_2_OFFSET);

    regval = getreg32(offset + SF_CTRL_IO_DLY_3_OFFSET);
    regval &= ~SF_CTRL_IO_2_DO_DLY_SEL_MASK;
    regval |= (do_delay << SF_CTRL_IO_2_DO_DLY_SEL_SHIFT);
    regval &= ~SF_CTRL_IO_2_DI_DLY_SEL_MASK;
    regval |= (di_delay << SF_CTRL_IO_2_DI_DLY_SEL_SHIFT);
    regval &= ~SF_CTRL_IO_2_OE_DLY_SEL_MASK;
    regval |= (oe_delay << SF_CTRL_IO_2_OE_DLY_SEL_SHIFT);
    putreg32(regval, offset + SF_CTRL_IO_DLY_3_OFFSET);

    regval = getreg32(offset + SF_CTRL_IO_DLY_4_OFFSET);
    regval &= ~SF_CTRL_IO_3_DO_DLY_SEL_MASK;
    regval |= (do_delay << SF_CTRL_IO_3_DO_DLY_SEL_SHIFT);
    regval &= ~SF_CTRL_IO_3_DI_DLY_SEL_MASK;
    regval |= (di_delay << SF_CTRL_IO_3_DI_DLY_SEL_SHIFT);
    regval &= ~SF_CTRL_IO_3_OE_DLY_SEL_MASK;
    regval |= (oe_delay << SF_CTRL_IO_3_OE_DLY_SEL_SHIFT);
    putreg32(regval, offset + SF_CTRL_IO_DLY_4_OFFSET);
}

#ifdef BFLB_SF_CTRL_SBUS2_ENABLE
/****************************************************************************/ /**
 * @brief  Enable serail bank2 controller
 *
 * @param  bank2_cfg: serial bank2 controller config
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_bank2_enable(const struct sf_ctrl_bank2_cfg *bank2_cfg)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    if (bank2_cfg == NULL) {
        return;
    }

    reg_base = BFLB_SF_CTRL_BASE;

    /* Select if1 bank2 clock delay */
    regval = getreg32(reg_base + SF_CTRL_SF_IF_IAHB_12_OFFSET);
    if (bank2_cfg->bank2_rx_clk_invert_src) {
        regval |= SF_CTRL_SF2_CLK_SF_RX_INV_SRC;

        if (bank2_cfg->bank2_rx_clk_invert_sel) {
            regval |= SF_CTRL_SF2_CLK_SF_RX_INV_SEL;
        } else {
            regval &= ~SF_CTRL_SF2_CLK_SF_RX_INV_SEL;
        }
    } else {
        regval &= ~SF_CTRL_SF2_CLK_SF_RX_INV_SRC;
    }

    if (bank2_cfg->bank2_delay_src) {
        regval |= SF_CTRL_SF2_IF_READ_DLY_SRC;

        if (bank2_cfg->bank2_clk_delay > 0) {
            regval |= SF_CTRL_SF2_IF_READ_DLY_EN;
            regval &= ~SF_CTRL_SF2_IF_READ_DLY_N_MASK;
            regval |= ((bank2_cfg->bank2_clk_delay - 1) << SF_CTRL_SF2_IF_READ_DLY_N_SHIFT);
        } else {
            regval &= ~SF_CTRL_SF2_IF_READ_DLY_EN;
        }
    } else {
        regval &= ~SF_CTRL_SF2_IF_READ_DLY_SRC;
    }
    putreg32(regval, reg_base+SF_CTRL_SF_IF_IAHB_12_OFFSET);

    /* Select sbus2 clock delay */
    regval = getreg32(reg_base + SF_CTRL_SF_IF2_CTRL_0_OFFSET);
    if (bank2_cfg->bank2_rx_clk_invert_sel) {
        regval |= SF_CTRL_SF_CLK_SF_IF2_RX_INV_SEL;
    } else {
        regval &= ~SF_CTRL_SF_CLK_SF_IF2_RX_INV_SEL;
    }

    if (bank2_cfg->bank2_clk_delay > 0) {
        regval |= SF_CTRL_SF_IF2_READ_DLY_EN;
        regval &= ~SF_CTRL_SF_IF2_READ_DLY_N_MASK;
        regval |= ((bank2_cfg->bank2_clk_delay - 1) << SF_CTRL_SF_IF2_READ_DLY_N_SHIFT);
    } else {
        regval &= ~SF_CTRL_SF_IF2_READ_DLY_EN;
    }
    putreg32(regval, reg_base+SF_CTRL_SF_IF2_CTRL_0_OFFSET);

    /* Dual flash mode, enable bank2, select pad1 and pad2 */
    regval = getreg32(reg_base + SF_CTRL_SF_IF2_CTRL_0_OFFSET);
    regval |= SF_CTRL_SF_IF_BK2_EN;
    regval |= SF_CTRL_SF_IF_BK2_MODE;
    regval &= ~SF_CTRL_SF_IF_PAD_SEL_MASK;
    putreg32(regval, reg_base+SF_CTRL_2_OFFSET);
}

/****************************************************************************/ /**
 * @brief  Flash controller sbus2 hold sram
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_sbus2_hold_sram(void)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    /* Sbus2 hold sram */
    regval = getreg32(reg_base + SF_CTRL_SF_IF2_CTRL_1_OFFSET);
    regval |= SF_CTRL_SF_IF2_FN_SEL;
    putreg32(regval, reg_base+SF_CTRL_SF_IF2_CTRL_1_OFFSET);
}

/****************************************************************************/ /**
 * @brief  Flash controller sbus2 release sram
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_sbus2_release_sram(void)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    /* Sbus2 release sram */
    regval = getreg32(reg_base + SF_CTRL_SF_IF2_CTRL_1_OFFSET);
    regval &= ~SF_CTRL_SF_IF2_FN_SEL;
    putreg32(regval, reg_base+SF_CTRL_SF_IF2_CTRL_1_OFFSET);
}

/****************************************************************************/ /**
 * @brief  Get flash controller sbus2 status
 *
 * @param  None
 *
 * @return Wether if2 is enable
 *
*******************************************************************************/
__WEAK
uint8_t ATTR_TCM_SECTION bflb_sf_ctrl_is_sbus2_enable(void)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_SF_IF2_CTRL_1_OFFSET);
    if (regval & SF_CTRL_SF_IF2_EN) {
        if (regval & SF_CTRL_SF_IF2_FN_SEL) {
            return 1;
        } else {
            return 0;
        }
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  SF Ctrl set sbus2 repalce
 *
 * @param  pad: SF pad to replace
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_sbus2_replace(uint8_t pad)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    /* Sbus2 enable */
    regval = getreg32(reg_base + SF_CTRL_SF_IF2_CTRL_1_OFFSET);
    regval |= SF_CTRL_SF_IF2_EN;
    putreg32(regval, reg_base+SF_CTRL_SF_IF2_CTRL_1_OFFSET);

    bflb_sf_ctrl_sbus2_hold_sram();

    /* Sbus2 repalce pad */
    regval = getreg32(reg_base + SF_CTRL_SF_IF2_CTRL_0_OFFSET);
    regval &= ~SF_CTRL_SF_IF2_REPLACE_SF1;
    regval &= ~SF_CTRL_SF_IF2_REPLACE_SF2;
    regval &= ~SF_CTRL_SF_IF2_REPLACE_SF3;

    if (pad == SF_CTRL_PAD1) {
        regval |= SF_CTRL_SF_IF2_REPLACE_SF1;
    } else if (pad == SF_CTRL_PAD2) {
        regval |= SF_CTRL_SF_IF2_REPLACE_SF2;
    } else {
        regval |= SF_CTRL_SF_IF2_REPLACE_SF3;
    }

    regval &= ~SF_CTRL_SF_IF2_PAD_SEL_MASK;
    regval |= (pad << SF_CTRL_SF_IF2_PAD_SEL_SHIFT);
    putreg32(regval, reg_base+SF_CTRL_SF_IF2_CTRL_0_OFFSET);
}

/****************************************************************************/ /**
 * @brief  SF Ctrl sbus2 revoke replace
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_sbus2_revoke_replace(void)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    bflb_sf_ctrl_sbus2_release_sram();

    /* Sbus2 clear repalce pad */
    regval = getreg32(reg_base + SF_CTRL_SF_IF2_CTRL_0_OFFSET);
    regval &= ~SF_CTRL_SF_IF2_REPLACE_SF1;
    regval &= ~SF_CTRL_SF_IF2_REPLACE_SF2;
    regval &= ~SF_CTRL_SF_IF2_REPLACE_SF3;
    putreg32(regval, reg_base+SF_CTRL_SF_IF2_CTRL_0_OFFSET);

    /* Sbus2 disable */
    regval = getreg32(reg_base + SF_CTRL_SF_IF2_CTRL_1_OFFSET);
    regval &= ~SF_CTRL_SF_IF2_EN;
    putreg32(regval, reg_base+SF_CTRL_SF_IF2_CTRL_1_OFFSET);
}

/****************************************************************************/ /**
 * @brief  SF Ctrl set sbus2 clock delay
 *
 * @param  clk_delay: Sbus2 clock delay
 * @param  rx_clk_invert: Sbus2 rx clock invert
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_sbus2_set_delay(uint8_t clk_delay, uint8_t rx_clk_invert)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_SF_IF2_CTRL_0_OFFSET);

    if (clk_delay > 0) {
        regval |= SF_CTRL_SF_IF2_READ_DLY_EN;
        regval &= ~SF_CTRL_SF_IF2_READ_DLY_N_MASK;
        regval |= ((clk_delay-1) << SF_CTRL_SF_IF2_READ_DLY_N_SHIFT);
    } else {
        regval &= ~SF_CTRL_SF_IF2_READ_DLY_EN;
    }

    if (rx_clk_invert) {
        regval |= SF_CTRL_SF_CLK_SF_IF2_RX_INV_SEL;
    } else {
        regval &= ~SF_CTRL_SF_CLK_SF_IF2_RX_INV_SEL;
    }
    putreg32(regval, reg_base+SF_CTRL_SF_IF2_CTRL_0_OFFSET);
}

/****************************************************************************/ /**
 * @brief  SF Ctrl dual flash memory remap set
 *
 * @param  remap: Memory remap set type
 * @param  lock: Memory remap lock
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_remap_set(uint8_t remap, uint8_t lock)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_2_OFFSET);
    regval &= ~SF_CTRL_SF_AHB2SIF_REMAP_MASK;
    regval |= (remap << SF_CTRL_SF_AHB2SIF_REMAP_SHIFT);
    putreg32(regval, reg_base+SF_CTRL_2_OFFSET);

    regval = getreg32(reg_base + SF_CTRL_2_OFFSET);
    if (lock) {
        regval |= SF_CTRL_SF_AHB2SIF_REMAP_LOCK;
    } else {
        regval &= ~SF_CTRL_SF_AHB2SIF_REMAP_LOCK;
    }
    putreg32(regval, reg_base+SF_CTRL_2_OFFSET);
}
#endif

#ifdef BFLB_SF_CTRL_32BITS_ADDR_ENABLE
/****************************************************************************/ /**
 * @brief  Get flash controller clock delay value
 *
 * @param  en32_bits_addr: Serial flash enable or disable 32-bits addr
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_32bits_addr_en(uint8_t en32_bits_addr)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_0_OFFSET);
    if (en32_bits_addr) {
        regval |= SF_CTRL_SF_IF_32B_ADR_EN;
    } else {
        regval &= ~SF_CTRL_SF_IF_32B_ADR_EN;
    }
    putreg32(regval, reg_base+SF_CTRL_0_OFFSET);
}
#endif

#ifdef BFLB_SF_CTRL_PSRAM_ENABLE
/****************************************************************************/ /**
 * @brief  Enable serail psram controller
 *
 * @param  psram_cfg: serial psram controller config
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_psram_init(struct sf_ctrl_psram_cfg *psram_cfg)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

#if defined(BL702L)
    /* Enable psram dual bank mode */
    regval = getreg32(reg_base + SF_CTRL_2_OFFSET);
    regval |= SF_CTRL_SF_IF_BK2_EN;
    regval |= SF_CTRL_SF_IF_BK2_MODE;
    putreg32(regval, reg_base+SF_CTRL_2_OFFSET);
#endif

    /* Select psram clock delay */
    regval = getreg32(reg_base + SF_CTRL_SF_IF_IAHB_12_OFFSET);
    if (psram_cfg->psram_rx_clk_invert_src) {
        regval |= SF_CTRL_SF2_CLK_SF_RX_INV_SRC;

        if (psram_cfg->psram_rx_clk_invert_sel) {
            regval |= SF_CTRL_SF2_CLK_SF_RX_INV_SEL;
        } else {
            regval &= ~SF_CTRL_SF2_CLK_SF_RX_INV_SEL;
        }
    } else {
        regval &= ~SF_CTRL_SF2_CLK_SF_RX_INV_SRC;
    }

    if (psram_cfg->psram_delay_src) {
        regval |= SF_CTRL_SF2_IF_READ_DLY_SRC;

        if (psram_cfg->psram_clk_delay > 0) {
            regval |= SF_CTRL_SF2_IF_READ_DLY_EN;
            regval &= ~SF_CTRL_SF2_IF_READ_DLY_N_MASK;
            regval |= ((psram_cfg->psram_clk_delay - 1) << SF_CTRL_SF2_IF_READ_DLY_N_SHIFT);
        } else {
            regval &= ~SF_CTRL_SF2_IF_READ_DLY_EN;
        }
    } else {
        regval &= ~SF_CTRL_SF2_IF_READ_DLY_SRC;
    }
    putreg32(regval, reg_base+SF_CTRL_SF_IF_IAHB_12_OFFSET);

    /* Enable AHB access sram buffer and enable sf interface */
    regval = getreg32(reg_base + SF_CTRL_1_OFFSET);
    regval |= SF_CTRL_SF_AHB2SRAM_EN;
    regval |= SF_CTRL_SF_IF_EN;
    putreg32(regval, reg_base+SF_CTRL_1_OFFSET);

    bflb_sf_ctrl_set_owner(psram_cfg->owner);
}
#endif

/****************************************************************************/ /**
 * @brief  Get flash controller clock delay value
 *
 * @param  None
 *
 * @return Clock delay value
 *
*******************************************************************************/
__WEAK
uint8_t ATTR_TCM_SECTION bflb_sf_ctrl_get_clock_delay(void)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_0_OFFSET);
    if ((regval&SF_CTRL_SF_IF_READ_DLY_EN) == 0) {
        return 0;
    }

    return ((regval&SF_CTRL_SF_IF_READ_DLY_N_MASK)>>SF_CTRL_SF_IF_READ_DLY_N_SHIFT) + 1;
}

/****************************************************************************/ /**
 * @brief  Set flash controller clock delay value
 *
 * @param  delay: Clock delay value
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_set_clock_delay(uint8_t delay)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_0_OFFSET);
    if (delay > 0) {
        regval |= SF_CTRL_SF_IF_READ_DLY_EN;
        regval &= ~SF_CTRL_SF_IF_READ_DLY_N_MASK;
        regval |= ((delay-1) << SF_CTRL_SF_IF_READ_DLY_N_SHIFT);
    } else {
        regval &= ~SF_CTRL_SF_IF_READ_DLY_EN;
    }
    putreg32(regval, reg_base+SF_CTRL_0_OFFSET);
}

/****************************************************************************/ /**
 * @brief  SF Ctrl get wrap queue value
 *
 * @param  None
 *
 * @return Wrap queue value
 *
*******************************************************************************/
__WEAK
uint8_t ATTR_TCM_SECTION bflb_sf_ctrl_get_wrap_queue_value(void)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_3_OFFSET);
    return (regval&SF_CTRL_SF_CMDS_2_WRAP_Q) ? 1:0;
}

#if defined(BL628) || defined(BL616) || defined(BL808) || defined(BL606P)
/****************************************************************************/ /**
 * @brief  SF Ctrl set cmds config
 *
 * @param  cmds_cfg: SF Ctrl cmds config
 * @param  bank: bank select type
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_cmds_set(struct sf_ctrl_cmds_cfg *cmds_cfg, uint8_t bank)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_3_OFFSET);
    regval &= ~SF_CTRL_SF_IF_1_ACK_LAT_MASK;
    regval |= ((cmds_cfg->ack_latency) << SF_CTRL_SF_IF_1_ACK_LAT_SHIFT);

    if (cmds_cfg->cmds_core_en) {
        regval |= SF_CTRL_SF_CMDS_CORE_EN;
    } else {
        regval &= ~SF_CTRL_SF_CMDS_CORE_EN;
    }

    if (bank == SF_CTRL_FLASH_BANK1) {
        if (cmds_cfg->cmds_en) {
            regval |= SF_CTRL_SF_CMDS_2_EN;
        } else {
            regval &= ~SF_CTRL_SF_CMDS_2_EN;
        }

        regval &= ~SF_CTRL_SF_CMDS_2_WRAP_MODE_MASK;
        regval |= ((cmds_cfg->cmds_wrap_mode) << SF_CTRL_SF_CMDS_2_WRAP_MODE_SHIFT);
        regval &= ~SF_CTRL_SF_CMDS_2_WRAP_LEN_MASK;
        regval |= ((cmds_cfg->cmds_wrap_len) << SF_CTRL_SF_CMDS_2_WRAP_LEN_SHIFT);
    } else {
        if (cmds_cfg->cmds_en) {
            regval |= SF_CTRL_SF_CMDS_1_EN;
        } else {
            regval &= ~SF_CTRL_SF_CMDS_1_EN;
        }

        regval &= ~SF_CTRL_SF_CMDS_1_WRAP_MODE_MASK;
        regval |= ((cmds_cfg->cmds_wrap_mode) << SF_CTRL_SF_CMDS_1_WRAP_MODE_SHIFT);
        regval &= ~SF_CTRL_SF_CMDS_1_WRAP_LEN_MASK;
        regval |= ((cmds_cfg->cmds_wrap_len) << SF_CTRL_SF_CMDS_1_WRAP_LEN_SHIFT);
    }
    putreg32(regval, reg_base+SF_CTRL_3_OFFSET);
}
#elif defined(BL702L)
/****************************************************************************/ /**
 * @brief  SF Ctrl set cmds config
 *
 * @param  cmds_cfg: SF Ctrl cmds config
 * @param  sel: select set flash or psram cmds
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_cmds_set(struct sf_ctrl_cmds_cfg *cmds_cfg, uint8_t sel)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_3_OFFSET);
    if (sel == SF_CTRL_SEL_FLASH) {
        if (cmds_cfg->cmds_en) {
            regval |= SF_CTRL_SF_CMDS_1_EN;
        } else {
            regval &= ~SF_CTRL_SF_CMDS_1_EN;
        }
        regval &= ~SF_CTRL_SF_CMDS_1_WRAP_MODE_MASK;
        regval |= ((cmds_cfg->cmds_wrap_mode) << SF_CTRL_SF_CMDS_1_WRAP_MODE_SHIFT);
        regval &= ~SF_CTRL_SF_CMDS_1_WRAP_LEN_MASK;
        regval |= ((cmds_cfg->cmds_wrap_len) << SF_CTRL_SF_CMDS_1_WRAP_LEN_SHIFT);
    } else {
        if (cmds_cfg->cmds_en) {
            regval |= SF_CTRL_SF_CMDS_2_EN;
        } else {
            regval &= ~SF_CTRL_SF_CMDS_2_EN;
        }
        regval &= ~SF_CTRL_SF_CMDS_2_WRAP_MODE_MASK;
        regval |= ((cmds_cfg->cmds_wrap_mode) << SF_CTRL_SF_CMDS_2_WRAP_MODE_SHIFT);
        regval &= ~SF_CTRL_SF_CMDS_2_WRAP_LEN_MASK;
        regval |= ((cmds_cfg->cmds_wrap_len) << SF_CTRL_SF_CMDS_2_WRAP_LEN_SHIFT);
    }
    putreg32(regval, reg_base+SF_CTRL_3_OFFSET);
}

/****************************************************************************/ /**
 * @brief  SF Ctrl burst toggle select
 *
 * @param  burst_toggle_en: burst toggle enable or not
 * @param  mode: SPI or QPI mode
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_burst_toggle_set(uint8_t burst_toggle_en, uint8_t mode)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_3_OFFSET);
    if (burst_toggle_en) {
        regval |= SF_CTRL_SF_CMDS_2_BT_EN;
    } else {
        regval &= ~SF_CTRL_SF_CMDS_2_BT_EN;
    }
    putreg32(regval, reg_base+SF_CTRL_3_OFFSET);

    regval = getreg32(reg_base + SF_CTRL_SF_IF_IAHB_6_OFFSET);
    if (mode) {
        regval |= SF_CTRL_SF_IF_3_QPI_MODE_EN;
    } else {
        regval &= ~SF_CTRL_SF_IF_3_QPI_MODE_EN;
    }
    putreg32(regval, reg_base+SF_CTRL_SF_IF_IAHB_6_OFFSET);
}
#elif defined(BL702) || defined(BL602)
/****************************************************************************/ /**
 * @brief  SF Ctrl set cmds config
 *
 * @param  cmds_cfg: SF Ctrl cmds config
 * @param  sel: select bank0 or bank1
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_cmds_set(struct sf_ctrl_cmds_cfg *cmds_cfg, uint8_t sel)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_3_OFFSET);

    if (cmds_cfg->cmds_en) {
        regval |= SF_CTRL_SF_CMDS_2_EN;
    } else {
        regval &= ~SF_CTRL_SF_CMDS_2_EN;
    }

#if defined(BL702)
    if (cmds_cfg->burst_toggle_en) {
        regval |= SF_CTRL_SF_CMDS_2_BT_EN;
    } else {
        regval &= ~SF_CTRL_SF_CMDS_2_BT_EN;
    }
#endif

    regval &= ~SF_CTRL_SF_CMDS_2_WRAP_MODE_MASK;
    regval |= (cmds_cfg->cmds_wrap_mode << SF_CTRL_SF_CMDS_2_WRAP_MODE_SHIFT);

    regval &= ~SF_CTRL_SF_CMDS_2_WRAP_LEN_MASK;
    regval |= (cmds_cfg->cmds_wrap_len << SF_CTRL_SF_CMDS_2_WRAP_LEN_SHIFT);
    putreg32(regval, reg_base+SF_CTRL_3_OFFSET);
}
#endif

/****************************************************************************/ /**
 * @brief  SF Ctrl pad select
 *
 * @param  sel: Pin select type
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_select_pad(uint8_t sel)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_2_OFFSET);
#if defined(BL628) || defined(BL616)
    if (sel <= SF_IO_EXT_SF3 || sel == SF_IO_EXT_SF2) {
        /* Single flash mode, disable bank2 */
        regval &= ~SF_CTRL_SF_IF_BK2_EN;

        if (sel <= SF_IO_EMB_SWAP_IO2CS) {
            /* Select embedded pad1 */
            regval &= ~SF_CTRL_SF_IF_PAD_SEL_MASK;
        } else {
            /* Select pad2 or pad3 */
            regval &= ~SF_CTRL_SF_IF_PAD_SEL_MASK;
            regval |= (((sel&0xf) >> 2) << SF_CTRL_SF_IF_PAD_SEL_SHIFT);
        }
    } else if ((sel >= SF_IO_EMB_SWAP_IO3IO0_AND_SF2_SWAP_IO3IO0 && sel <= SF_IO_EMB_SWAP_IO2CS_AND_SF2_SWAP_IO3IO0)
             ||(sel >= SF_IO_EMB_SWAP_IO3IO0_AND_SF2 && sel <= SF_IO_EMB_SWAP_IO2CS_AND_SF2)) {
        /* Dual flash mode, enable bank2, select pad1 and pad2 */
        regval |= SF_CTRL_SF_IF_BK2_EN;
        regval |= SF_CTRL_SF_IF_BK2_MODE;
        regval &= ~SF_CTRL_SF_IF_PAD_SEL_MASK;
    }
#elif defined(BL808) || defined(BL606P)
    if (sel <= SF_IO_EXT_SF2) {
        /* Single flash mode, disable bank2 */
        regval &= ~SF_CTRL_SF_IF_BK2_EN;

        if (sel <= SF_IO_EMB_SWAP_NONE_DUAL_IO0) {
            /* Select embedded pad1 */
            regval &= ~SF_CTRL_SF_IF_PAD_SEL_MASK;
        } else {
            /* Select pad2 or pad3 */
            regval &= ~SF_CTRL_SF_IF_PAD_SEL_MASK;
            regval |= (((sel&0xf) >> 2) << SF_CTRL_SF_IF_PAD_SEL_SHIFT);
        }
    } else if (sel >= SF_IO_EMB_SWAP_IO0_IO3_AND_EXT_SF2 && sel <= SF_IO_EMB_SWAP_NONE_DUAL_IO0_AND_EXT_SF2) {
        /* Dual flash mode, enable bank2, select pad1 and pad2 */
        regval |= SF_CTRL_SF_IF_BK2_EN;
        regval |= SF_CTRL_SF_IF_BK2_MODE;
        regval &= ~SF_CTRL_SF_IF_PAD_SEL_MASK;
    }
#elif defined(BL702)
    if (sel <= SF_CTRL_SEL_SF3) {
        regval &= ~SF_CTRL_SF_IF_BK2_EN;
        regval &= ~SF_CTRL_SF_IF_PAD_SEL_MASK;
        regval |= (sel << SF_CTRL_SF_IF_PAD_SEL_SHIFT);
    } else if (sel >= SF_CTRL_SEL_DUAL_BANK_SF1_SF2 && sel <= SF_CTRL_SEL_DUAL_BANK_SF3_SF1) {
        regval |= SF_CTRL_SF_IF_BK2_EN;
        regval |= SF_CTRL_SF_IF_BK2_MODE;
        regval &= ~SF_CTRL_SF_IF_PAD_SEL_MASK;
        regval |= ((sel - SF_CTRL_SEL_DUAL_BANK_SF1_SF2) << SF_CTRL_SF_IF_PAD_SEL_SHIFT);
    } else if (sel == SF_CTRL_SEL_DUAL_CS_SF2) {
        regval |= SF_CTRL_SF_IF_BK2_EN;
        regval &= ~SF_CTRL_SF_IF_BK2_MODE;
        regval &= ~SF_CTRL_SF_IF_PAD_SEL_MASK;
        regval |= (1 << SF_CTRL_SF_IF_PAD_SEL_SHIFT);
    } else if (sel == SF_CTRL_SEL_DUAL_CS_SF3) {
        regval |= SF_CTRL_SF_IF_BK2_EN;
        regval &= ~SF_CTRL_SF_IF_BK2_MODE;
        regval &= ~SF_CTRL_SF_IF_PAD_SEL_MASK;
        regval |= (2 << SF_CTRL_SF_IF_PAD_SEL_SHIFT);
    }
#else
    regval &= ~SF_CTRL_SF_IF_PAD_SEL_MASK;
    regval |= (sel << SF_CTRL_SF_IF_PAD_SEL_SHIFT);
#endif
    putreg32(regval, reg_base+SF_CTRL_2_OFFSET);
}

/****************************************************************************/ /**
 * @brief  SF Ctrl select bank on system bus
 *
 * @param  bank: bank select type
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_sbus_select_bank(uint8_t bank)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_2_OFFSET);
    if (bank) {
        regval |= SF_CTRL_SF_IF_0_BK_SEL;
    } else {
        regval &= ~SF_CTRL_SF_IF_0_BK_SEL;
    }
    putreg32(regval, reg_base+SF_CTRL_2_OFFSET);
}

/****************************************************************************/ /**
 * @brief  Set flash controller owner:I/D AHB or system AHB
 *
 * @param  owner: owner type
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_set_owner(uint8_t owner)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;
    uint32_t time_out = 0;

    reg_base = BFLB_SF_CTRL_BASE;
    time_out = SF_CTRL_BUSY_STATE_TIMEOUT;

    while (bflb_sf_ctrl_get_busy_state()) {
        time_out--;

        if (time_out == 0) {
            return;
        }
    }

    regval = getreg32(reg_base + SF_CTRL_1_OFFSET);
    /* Set owner */
    if (owner) {
        regval |= SF_CTRL_SF_IF_FN_SEL;
    } else {
        regval &= ~SF_CTRL_SF_IF_FN_SEL;
    }

    /* Set iahb to flash interface */
    if (owner == SF_CTRL_OWNER_IAHB) {
        regval |= SF_CTRL_SF_AHB2SIF_EN;
    } else {
        regval &= ~SF_CTRL_SF_AHB2SIF_EN;
    }
    putreg32(regval, reg_base+SF_CTRL_1_OFFSET);
}

/****************************************************************************/ /**
 * @brief  Disable flash controller
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_disable(void)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_1_OFFSET);
    regval &= ~SF_CTRL_SF_IF_EN;
    putreg32(regval, reg_base+SF_CTRL_1_OFFSET);
}

/****************************************************************************/ /**
 * @brief  Enable flash controller AES with big indian
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_enable_be(void)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_0_OFFSET);
    regval |= SF_CTRL_SF_AES_KEY_ENDIAN;
    regval |= SF_CTRL_SF_AES_IV_ENDIAN;
    regval |= SF_CTRL_SF_AES_DIN_ENDIAN;
    regval |= SF_CTRL_SF_AES_DOUT_ENDIAN;
    putreg32(regval, reg_base+SF_CTRL_0_OFFSET);
}

/****************************************************************************/ /**
 * @brief  Enable flash controller AES with little indian
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_enable_le(void)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_0_OFFSET);
    regval &= ~SF_CTRL_SF_AES_KEY_ENDIAN;
    regval &= ~SF_CTRL_SF_AES_IV_ENDIAN;
    regval &= ~SF_CTRL_SF_AES_DIN_ENDIAN;
    regval &= ~SF_CTRL_SF_AES_DOUT_ENDIAN;
    putreg32(regval, reg_base+SF_CTRL_0_OFFSET);
}

/****************************************************************************/ /**
 * @brief  Serial flash controller set AES region
 *
 * @param  region: region number
 * @param  enable: enable or not
 * @param  hw_key: hardware key or software key
 * @param  start_addr: region start address
 * @param  end_addr: region end address
 * @param  locked: lock this region or not
 *
 * @return None
 *
*******************************************************************************/
__WEAK
#if defined (BL702) || defined(BL602)
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_set_region(uint8_t region, uint8_t enable, uint8_t hw_key,
                                          uint32_t start_addr, uint32_t end_addr, uint8_t locked)
{
    /* 0x30 : sf_aes_cfg */
    #define SF_CTRL_SF_AES_REGION_CFG_END_SHIFT   (0U)
    #define SF_CTRL_SF_AES_REGION_CFG_END_MASK    (0x3fff<<SF_CTRL_SF_AES_REGION_END_SHIFT)
    #define SF_CTRL_SF_AES_REGION_CFG_START_SHIFT (14U)
    #define SF_CTRL_SF_AES_REGION_CFG_START_MASK  (0x3fff<<SF_CTRL_SF_AES_REGION_START_SHIFT)
    #define SF_CTRL_SF_AES_REGION_CFG_HW_KEY_EN   (1<<29U)
    #define SF_CTRL_SF_AES_REGION_CFG_EN          (1<<30U)
    #define SF_CTRL_SF_AES_REGION_CFG_LOCK        (1<<31U)

#if defined(BL602)
    uint32_t region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, !region);
#else
    uint32_t region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, region);
#endif
    uint32_t regval = 0;

    if (!hw_key) {
#if defined(BL602)
        region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, !region);
#else
        region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, region);
#endif
    }

    regval = getreg32(region_reg_base + SF_CTRL_SF_AES_START_OFFSET);
    if (hw_key) {
        regval |= SF_CTRL_SF_AES_REGION_CFG_HW_KEY_EN;
    } else {
        regval &= ~SF_CTRL_SF_AES_REGION_CFG_HW_KEY_EN;
    }
    if (enable) {
        regval |= SF_CTRL_SF_AES_REGION_CFG_EN;
    } else {
        regval &= ~SF_CTRL_SF_AES_REGION_CFG_EN;
    }
    if (locked) {
        regval |= SF_CTRL_SF_AES_REGION_CFG_LOCK;
    } else {
        regval &= ~SF_CTRL_SF_AES_REGION_CFG_LOCK;
    }
    regval &= ~SF_CTRL_SF_AES_REGION_CFG_START_MASK;
    regval |= ((start_addr/1024) << SF_CTRL_SF_AES_REGION_CFG_START_SHIFT);
    /* sf_aes_end =1 means 1,11,1111,1111 */
    regval &= ~SF_CTRL_SF_AES_REGION_CFG_END_MASK;
    regval |= ((end_addr/1024) << SF_CTRL_SF_AES_REGION_CFG_END_SHIFT);
    putreg32(regval, region_reg_base+SF_CTRL_SF_AES_START_OFFSET);
}
#else
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_set_region(uint8_t region, uint8_t enable, uint8_t hw_key,
                                          uint32_t start_addr, uint32_t end_addr, uint8_t locked)
{
    uint32_t region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, region);
    uint32_t regval = 0;

    if (!hw_key) {
        region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, region);
    }

    regval = getreg32(region_reg_base + SF_CTRL_SF_AES_END_OFFSET);
    /* sf_aes_end =1 means 1,11,1111,1111 */
    regval &= ~SF_CTRL_SF_AES_REGION_END_MASK;
    regval |= ((end_addr/1024) << SF_CTRL_SF_AES_REGION_END_SHIFT);
    putreg32(regval, region_reg_base+SF_CTRL_SF_AES_END_OFFSET);

    regval = getreg32(region_reg_base + SF_CTRL_SF_AES_START_OFFSET);
    if (hw_key) {
        regval |= SF_CTRL_SF_AES_REGION_HW_KEY_EN;
    } else {
        regval &= ~SF_CTRL_SF_AES_REGION_HW_KEY_EN;
    }
    if (enable) {
        regval |= SF_CTRL_SF_AES_REGION_EN;
    } else {
        regval &= ~SF_CTRL_SF_AES_REGION_EN;
    }
    if (locked) {
        regval |= SF_CTRL_SF_AES_REGION_LOCK;
    } else {
        regval &= ~SF_CTRL_SF_AES_REGION_LOCK;
    }
    regval &= ~SF_CTRL_SF_AES_REGION_START_MASK;
    regval |= ((start_addr/1024) << SF_CTRL_SF_AES_REGION_START_SHIFT);
    putreg32(regval, region_reg_base+SF_CTRL_SF_AES_START_OFFSET);
}
#endif

/****************************************************************************/ /**
 * @brief  Serial flash controller set AES key
 *
 * @param  region: region number
 * @param  key: key data pointer
 * @param  key_type: flash controller AES key type:128 bits,192 bits or 256 bits
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_set_key(uint8_t region, uint8_t *key, uint8_t key_type)
{
    uint32_t reg_base = 0;
#if defined(BL602)
    uint32_t region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, !region);
#else
    uint32_t region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, region);
#endif
    uint32_t regval = 0;
    uint32_t i = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_SF_AES_OFFSET);
    regval &= ~SF_CTRL_SF_AES_MODE_MASK;
    regval |= ((key_type) << SF_CTRL_SF_AES_MODE_SHIFT);
    putreg32(regval, reg_base+SF_CTRL_SF_AES_OFFSET);

    if (NULL != key) {
        if (key_type == SF_CTRL_AES_128BITS) {
            i = 4;
        } else if (key_type == SF_CTRL_AES_256BITS) {
            i = 8;
        } else if (key_type == SF_CTRL_AES_192BITS) {
            i = 6;
        }

        regval = SF_CTRL_SF_AES_KEY_7_OFFSET;
        while (i--) {
            putreg32(__REV(BL_RDWD_FRM_BYTEP(key)), region_reg_base+regval);
            key += 4;
            regval -= 4;
        }
    }
}

/****************************************************************************/ /**
 * @brief  Serial flash controller set AES key with big endian
 *
 * @param  region: region number
 * @param  key: key data pointer
 * @param  key_type: flash controller AES key type:128 bits,192 bits or 256 bits
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_set_key_be(uint8_t region, uint8_t *key, uint8_t key_type)
{
    uint32_t reg_base = 0;
#if defined(BL602)
    uint32_t region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, !region);
#else
    uint32_t region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, region);
#endif
    uint32_t regval = 0;
    uint32_t i = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_SF_AES_OFFSET);
    regval &= ~SF_CTRL_SF_AES_MODE_MASK;
    regval |= ((key_type) << SF_CTRL_SF_AES_MODE_SHIFT);
    putreg32(regval, reg_base+SF_CTRL_SF_AES_OFFSET);

    if (NULL != key) {
        if (key_type == SF_CTRL_AES_128BITS) {
            i = 4;
        } else if (key_type == SF_CTRL_AES_256BITS) {
            i = 8;
        } else if (key_type == SF_CTRL_AES_192BITS) {
            i = 6;
        }

        regval = SF_CTRL_SF_AES_KEY_0_OFFSET;
        while (i--) {
            putreg32(BL_RDWD_FRM_BYTEP(key), region_reg_base+regval);
            key += 4;
            regval += 4;
        }
    }
}

/****************************************************************************/ /**
 * @brief  Serial flash controller set AES iv
 *
 * @param  region: region number
 * @param  iv: iv data pointer
 * @param  addr_offset: flash address offset
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_set_iv(uint8_t region, uint8_t *iv, uint32_t addr_offset)
{
#if defined(BL602)
    uint32_t region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, !region);
#else
    uint32_t region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, region);
#endif
    uint32_t regval = 0;
    uint32_t i = 3;

    if (iv != NULL) {
        regval = SF_CTRL_SF_AES_IV_W3_OFFSET;

        while (i--) {
            putreg32(__REV(BL_RDWD_FRM_BYTEP(iv)), region_reg_base+regval);
            iv += 4;
            regval -= 4;
        }

        putreg32(addr_offset, region_reg_base+SF_CTRL_SF_AES_IV_W0_OFFSET);
        iv += 4;
    }
}

/****************************************************************************/ /**
 * @brief  Serial flash controller set AES iv with big endian
 *
 * @param  region: region number
 * @param  iv: iv data pointer
 * @param  addr_offset: flash address offset
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_set_iv_be(uint8_t region, uint8_t *iv, uint32_t addr_offset)
{
#if defined(BL602)
    uint32_t region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, !region);
#else
    uint32_t region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, region);
#endif
    uint32_t regval = 0;
    uint32_t i = 3;

    if (iv != NULL) {
        regval = SF_CTRL_SF_AES_IV_W0_OFFSET;

        while (i--) {
            putreg32(BL_RDWD_FRM_BYTEP(iv), region_reg_base+regval);
            iv += 4;
            regval += 4;
        }

        putreg32(__REV(addr_offset), region_reg_base+SF_CTRL_SF_AES_IV_W3_OFFSET);
        iv += 4;
    }
}

#ifdef BFLB_SF_CTRL_AES_XTS_ENABLE
/****************************************************************************/ /**
 * @brief  Serial flash controller set AES XTS mode key
 *
 * @param  region: region number
 * @param  key: key data pointer
 * @param  key_type: flash controller AES key type:128 bits,192 bits or 256 bits
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_xts_set_key(uint8_t region, uint8_t *key, uint8_t key_type)
{
    uint32_t reg_base = 0;
    uint32_t region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, region);
    uint32_t regval = 0;
    uint32_t i = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_SF_AES_OFFSET);
    regval &= ~SF_CTRL_SF_AES_MODE_MASK;
    regval |= ((key_type) << SF_CTRL_SF_AES_MODE_SHIFT);
    putreg32(regval, reg_base+SF_CTRL_SF_AES_OFFSET);

    if (NULL != key) {
        i = 8;
        regval = SF_CTRL_SF_AES_KEY_7_OFFSET;

        while (i--) {
            putreg32(__REV(BL_RDWD_FRM_BYTEP(key)), region_reg_base+regval);
            key += 4;
            regval -= 4;
        }
    }
}

/****************************************************************************/ /**
 * @brief  Serial flash controller set AES XTS mode key with big endian
 *
 * @param  region: region number
 * @param  key: key data pointer
 * @param  key_type: flash controller AES key type:128 bits,192 bits or 256 bits
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_xts_set_key_be(uint8_t region, uint8_t *key, uint8_t key_type)
{
    uint32_t reg_base = 0;
    uint32_t region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, region);
    uint32_t regval = 0;
    uint32_t i = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_SF_AES_OFFSET);
    regval &= ~SF_CTRL_SF_AES_MODE_MASK;
    regval |= ((key_type) << SF_CTRL_SF_AES_MODE_SHIFT);
    putreg32(regval, reg_base+SF_CTRL_SF_AES_OFFSET);

    if (NULL != key) {
        i = 8;
        regval = SF_CTRL_SF_AES_KEY_0_OFFSET;

        while (i--) {
            putreg32(BL_RDWD_FRM_BYTEP(key), region_reg_base+regval);
            key += 4;
            regval += 4;
        }
    }
}

/****************************************************************************/ /**
 * @brief  Serial flash controller set AES XTS iv
 *
 * @param  region: region number
 * @param  iv: iv data pointer
 * @param  addr_offset: flash address offset
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_xts_set_iv(uint8_t region, uint8_t *iv, uint32_t addr_offset)
{
    uint32_t region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, region);
    uint32_t regval = 0;
    uint32_t i = 3;

    if (iv != NULL) {
        regval = SF_CTRL_SF_AES_IV_W1_OFFSET;

        while (i--) {
            iv += 4;
            putreg32(BL_RDWD_FRM_BYTEP(iv), region_reg_base+regval);
            regval += 4;
        }

        putreg32(addr_offset, region_reg_base+SF_CTRL_SF_AES_IV_W0_OFFSET);
        iv += 4;
    }
}

/****************************************************************************/ /**
 * @brief  Serial flash controller set AES XTS iv with big endian
 *
 * @param  region: region number
 * @param  iv: iv data pointer
 * @param  addr_offset: flash address offset
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_xts_set_iv_be(uint8_t region, uint8_t *iv, uint32_t addr_offset)
{
    uint32_t region_reg_base = bflb_sf_ctrl_get_aes_region(BFLB_SF_CTRL_BASE, region);
    uint32_t regval = 0;
    uint32_t i = 3;

    if (iv != NULL) {
        regval = SF_CTRL_SF_AES_IV_W2_OFFSET;

        while (i--) {
            iv += 4;
            putreg32(__REV(BL_RDWD_FRM_BYTEP(iv)), region_reg_base+regval);
            regval -= 4;
        }

        putreg32(__REV(addr_offset), region_reg_base+SF_CTRL_SF_AES_IV_W3_OFFSET);
        iv += 4;
    }
}
#endif

/****************************************************************************/ /**
 * @brief  Set serial flash controller AES mode
 *
 * @param  mode: AES mode select
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_set_mode(uint8_t mode)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_SF_AES_OFFSET);
    if (mode == SF_CTRL_AES_CTR_MODE) {
        regval &= ~SF_CTRL_SF_AES_BLK_MODE;
    } else {
        regval |= SF_CTRL_SF_AES_BLK_MODE;
    }
    putreg32(regval, reg_base+SF_CTRL_SF_AES_OFFSET);
}

/****************************************************************************/ /**
 * @brief  Enable serial flash controller AES
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_enable(void)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_SF_AES_OFFSET);
    regval |= SF_CTRL_SF_AES_EN;
    putreg32(regval, reg_base+SF_CTRL_SF_AES_OFFSET);
}

/****************************************************************************/ /**
 * @brief  Disable serial flash controller AES
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_aes_disable(void)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_SF_AES_OFFSET);
    regval &= ~SF_CTRL_SF_AES_EN;
    putreg32(regval, reg_base+SF_CTRL_SF_AES_OFFSET);
}

/****************************************************************************/ /**
 * @brief  Check is serial flash controller AES enable
 *
 * @param  None
 *
 * @return Wether AES is enable
 *
*******************************************************************************/
__WEAK
uint8_t ATTR_TCM_SECTION bflb_sf_ctrl_is_aes_enable(void)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_SF_AES_OFFSET);
    if (regval & SF_CTRL_SF_AES_EN) {
        return 1;
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  Set flash image offset
 *
 * @param  addr_offset: Address offset value
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_set_flash_image_offset(uint32_t addr_offset, uint8_t group, uint8_t bank)
{
    uint32_t reg_base = 0;

    reg_base = BFLB_SF_CTRL_BASE;

#ifdef BFLB_SF_CTRL_SBUS2_ENABLE
    if (group) {
        if (bank == SF_CTRL_FLASH_BANK0) {
            putreg32(addr_offset, reg_base+SF_CTRL_SF_ID1_OFFSET_OFFSET);
        } else {
            putreg32(addr_offset, reg_base+SF_CTRL_SF_BK2_ID1_OFFSET_OFFSET);
        }
    } else {
        if (bank == SF_CTRL_FLASH_BANK0) {
            putreg32(addr_offset, reg_base+SF_CTRL_SF_ID0_OFFSET_OFFSET);
        } else {
            putreg32(addr_offset, reg_base+SF_CTRL_SF_BK2_ID0_OFFSET_OFFSET);
        }
    }
#else
    putreg32(addr_offset, reg_base+SF_CTRL_SF_ID0_OFFSET_OFFSET);
#endif
}

/****************************************************************************/ /**
 * @brief  Get flash image offset
 *
 * @param  group: CPU group id 0 or 1
 * @param  bank: Flash bank select
 *
 * @return :Address offset value
 *
*******************************************************************************/
__WEAK
uint32_t ATTR_TCM_SECTION bflb_sf_ctrl_get_flash_image_offset(uint8_t group, uint8_t bank)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

#ifdef BFLB_SF_CTRL_SBUS2_ENABLE
    if (group) {
        if (bank == SF_CTRL_FLASH_BANK0) {
            regval = getreg32(reg_base + SF_CTRL_SF_ID1_OFFSET_OFFSET);
        } else {
            regval = getreg32(reg_base + SF_CTRL_SF_BK2_ID1_OFFSET_OFFSET);
        }
    } else {
        if (bank == SF_CTRL_FLASH_BANK0) {
            regval = getreg32(reg_base + SF_CTRL_SF_ID0_OFFSET_OFFSET);
        } else {
            regval = getreg32(reg_base + SF_CTRL_SF_BK2_ID0_OFFSET_OFFSET);
        }
    }
#else
    regval = getreg32(reg_base + SF_CTRL_SF_ID0_OFFSET_OFFSET);
#endif

    return regval;
}

/****************************************************************************/ /**
 * @brief  Lock/unlock sf_id0/sf_id1/sf_bk2_id0/sf_bk2_id1 offset
 *
 * @param  lock: lock or unlock
 *
 * @return :None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_lock_flash_image_offset(uint8_t lock)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_2_OFFSET);
    if (lock) {
        regval |= SF_CTRL_SF_ID_OFFSET_LOCK;
    } else {
        regval &= ~SF_CTRL_SF_ID_OFFSET_LOCK;
    }
    putreg32(regval, reg_base+SF_CTRL_2_OFFSET);
}

#if defined(BL702) || defined(BL602)
/****************************************************************************/ /**
 * @brief  SF controller send one command
 *
 * @param  sahb_sram_sel: Serial flash controller clock sahb sram select
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_select_clock(uint8_t sahb_sram_sel)
{
    #define SF_CTRL_SF_CLK_SAHB_SRAM_SEL    (1<<5U)

    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_0_OFFSET);

    if (sahb_sram_sel) {
        regval |= SF_CTRL_SF_CLK_SAHB_SRAM_SEL;
    } else {
        regval &= ~SF_CTRL_SF_CLK_SAHB_SRAM_SEL;
    }

    putreg32(regval, reg_base+SF_CTRL_0_OFFSET);
}
#else
void ATTR_TCM_SECTION bflb_sf_ctrl_select_clock(uint8_t sahb_sram_sel)
{

}
#endif

/****************************************************************************/ /**
 * @brief  SF controller send one command
 *
 * @param  cfg: Serial flash controller command configuration pointer
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_sendcmd(struct sf_ctrl_cmd_cfg_type *cfg)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;
    uint32_t time_out = 0;
    uint32_t cmd_offset = 0;

    reg_base = BFLB_SF_CTRL_BASE;
    time_out = SF_CTRL_BUSY_STATE_TIMEOUT;

    while (bflb_sf_ctrl_get_busy_state()) {
        time_out--;

        if (time_out == 0) {
            return;
        }
    }

#if defined(BFLB_SF_CTRL_SBUS2_ENABLE)
    if (bflb_sf_ctrl_is_sbus2_enable() == 0) {
        regval = getreg32(reg_base + SF_CTRL_1_OFFSET);
        if (regval & SF_CTRL_SF_IF_FN_SEL) {
            return;
        }

        cmd_offset = reg_base + SF_CTRL_IF1_SAHB_OFFSET;
    } else {
        cmd_offset = reg_base + SF_CTRL_IF2_SAHB_OFFSET;
    }
#else
    regval = getreg32(reg_base + SF_CTRL_1_OFFSET);
    if (regval & SF_CTRL_SF_IF_FN_SEL) {
        return;
    }
    cmd_offset = reg_base + SF_CTRL_IF1_SAHB_OFFSET;
#endif

    /* Clear trigger */
    regval = getreg32(cmd_offset + SF_CTRL_IF_SAHB_0_OFFSET);
    regval &= ~SF_CTRL_IF_0_TRIG;
    putreg32(regval, cmd_offset+SF_CTRL_IF_SAHB_0_OFFSET);

    /* Copy command buffer */
    putreg32(cfg->cmd_buf[0], cmd_offset+SF_CTRL_IF_SAHB_1_OFFSET);
    putreg32(cfg->cmd_buf[1], cmd_offset+SF_CTRL_IF_SAHB_2_OFFSET);

    regval = getreg32(cmd_offset + SF_CTRL_IF_SAHB_0_OFFSET);
    /* Configure SPI and IO mode*/
    if (SF_CTRL_CMD_1_LINE == cfg->cmd_mode) {
        regval &= ~SF_CTRL_IF_0_QPI_MODE_EN;
    } else {
        regval |= SF_CTRL_IF_0_QPI_MODE_EN;
    }

    regval &= ~SF_CTRL_IF_0_SPI_MODE_MASK;
    if (SF_CTRL_ADDR_1_LINE == cfg->addr_mode) {
        if (SF_CTRL_DATA_1_LINE == cfg->data_mode) {
            regval |= (SF_CTRL_NIO_MODE << SF_CTRL_IF_0_SPI_MODE_SHIFT);
        } else if (SF_CTRL_DATA_2_LINES == cfg->data_mode) {
            regval |= (SF_CTRL_DO_MODE << SF_CTRL_IF_0_SPI_MODE_SHIFT);
        } else if (SF_CTRL_DATA_4_LINES == cfg->data_mode) {
            regval |= (SF_CTRL_QO_MODE << SF_CTRL_IF_0_SPI_MODE_SHIFT);
        }
    } else if (SF_CTRL_ADDR_2_LINES == cfg->addr_mode) {
        regval |= (SF_CTRL_DIO_MODE << SF_CTRL_IF_0_SPI_MODE_SHIFT);
    } else if (SF_CTRL_ADDR_4_LINES == cfg->addr_mode) {
        regval |= (SF_CTRL_QIO_MODE << SF_CTRL_IF_0_SPI_MODE_SHIFT);
    }

    /* Configure cmd */
    regval |= SF_CTRL_IF_0_CMD_EN;
    regval &= ~SF_CTRL_IF_0_CMD_BYTE_MASK;

    /* Configure address */
    regval &= ~SF_CTRL_IF_0_ADR_BYTE_MASK;
    if (cfg->addr_size != 0) {
        regval |= SF_CTRL_IF_0_ADR_EN;
        regval |= ((cfg->addr_size-1) << SF_CTRL_IF_0_ADR_BYTE_SHIFT);
    } else {
        regval &= ~SF_CTRL_IF_0_ADR_EN;
    }

    /* Configure dummy */
    regval &= ~SF_CTRL_IF_0_DMY_BYTE_MASK;
    if (cfg->dummy_clks != 0) {
        regval |= SF_CTRL_IF_0_DMY_EN;
        regval |= ((cfg->dummy_clks-1) << SF_CTRL_IF_0_DMY_BYTE_SHIFT);
    } else {
        regval &= ~SF_CTRL_IF_0_DMY_EN;
    }

    /* Configure data */
    regval &= ~SF_CTRL_IF_0_DAT_BYTE_MASK;
    if (cfg->nb_data != 0) {
        regval |= SF_CTRL_IF_0_DAT_EN;
        regval |= ((cfg->nb_data-1) << SF_CTRL_IF_0_DAT_BYTE_SHIFT);
    } else {
        regval &= ~SF_CTRL_IF_0_DAT_EN;
    }

    /* Set read write flag */
    if (cfg->rw_flag) {
        regval |= SF_CTRL_IF_0_DAT_RW;
    } else {
        regval &= ~SF_CTRL_IF_0_DAT_RW;
    }
    putreg32(regval, cmd_offset+SF_CTRL_IF_SAHB_0_OFFSET);

    //switch sf_clk_sahb_sram_sel = 0
    bflb_sf_ctrl_select_clock(1);

    /* Trigger */
    regval |= SF_CTRL_IF_0_TRIG;
    putreg32(regval, cmd_offset+SF_CTRL_IF_SAHB_0_OFFSET);

    time_out = SF_CTRL_BUSY_STATE_TIMEOUT;
    while (bflb_sf_ctrl_get_busy_state()) {
        time_out--;

        if (time_out == 0) {
            bflb_sf_ctrl_select_clock(0);
            return;
        }
    }

    //switch sf_clk_sahb_sram_sel = 0
    bflb_sf_ctrl_select_clock(0);
}

/****************************************************************************/ /**
 * @brief  SF Ctrl disable iahb to flash wrap access for XTS mode
 *
 * @param  disable: Disable for 1 and enable for 0
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_disable_wrap_access(uint8_t disable)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;

    reg_base = BFLB_SF_CTRL_BASE;

    regval = getreg32(reg_base + SF_CTRL_1_OFFSET);
    if (disable) {
        regval &= ~SF_CTRL_SF_AHB2SIF_DISWRAP;
    } else {
        regval |= SF_CTRL_SF_AHB2SIF_DISWRAP;
    }
    putreg32(regval, reg_base+SF_CTRL_1_OFFSET);
}

/****************************************************************************/ /**
 * @brief  Config SF controller for xip read
 *
 * @param  cfg: Serial flash controller command configuration pointer
 * @param  cmd_valid: command valid or not, for continous read, cache may need no command
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_xip_set(struct sf_ctrl_cmd_cfg_type *cfg, uint8_t cmd_valid)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;
    uint32_t time_out = 0;

    reg_base = BFLB_SF_CTRL_BASE;
    time_out = SF_CTRL_BUSY_STATE_TIMEOUT;

    while (bflb_sf_ctrl_get_busy_state()) {
        time_out--;

        if (time_out == 0) {
            return;
        }
    }

    regval = getreg32(reg_base + SF_CTRL_1_OFFSET);
    if ((regval & SF_CTRL_SF_IF_FN_SEL) == 0) {
        return;
    }

    /* Copy command buffer */
    putreg32(cfg->cmd_buf[0], reg_base+SF_CTRL_SF_IF_IAHB_1_OFFSET);
    putreg32(cfg->cmd_buf[1], reg_base+SF_CTRL_SF_IF_IAHB_2_OFFSET);

    regval = getreg32(reg_base + SF_CTRL_SF_IF_IAHB_0_OFFSET);
    /* Configure SPI and IO mode*/
    if (SF_CTRL_CMD_1_LINE == cfg->cmd_mode) {
        regval &= ~SF_CTRL_SF_IF_1_QPI_MODE_EN;
    } else {
        regval |= SF_CTRL_SF_IF_1_QPI_MODE_EN;
    }

    regval &= ~SF_CTRL_SF_IF_1_SPI_MODE_MASK;
    if (SF_CTRL_ADDR_1_LINE == cfg->addr_mode) {
        if (SF_CTRL_DATA_1_LINE == cfg->data_mode) {
            regval |= (SF_CTRL_NIO_MODE << SF_CTRL_SF_IF_1_SPI_MODE_SHIFT);
        } else if (SF_CTRL_DATA_2_LINES == cfg->data_mode) {
            regval |= (SF_CTRL_DO_MODE << SF_CTRL_SF_IF_1_SPI_MODE_SHIFT);
        } else if (SF_CTRL_DATA_4_LINES == cfg->data_mode) {
            regval |= (SF_CTRL_QO_MODE << SF_CTRL_SF_IF_1_SPI_MODE_SHIFT);
        }
    } else if (SF_CTRL_ADDR_2_LINES == cfg->addr_mode) {
        regval |= (SF_CTRL_DIO_MODE << SF_CTRL_SF_IF_1_SPI_MODE_SHIFT);
    } else if (SF_CTRL_ADDR_4_LINES == cfg->addr_mode) {
        regval |= (SF_CTRL_QIO_MODE << SF_CTRL_SF_IF_1_SPI_MODE_SHIFT);
    }

    regval &= ~SF_CTRL_SF_IF_1_CMD_BYTE_MASK;
    if (cmd_valid) {
        regval |= SF_CTRL_SF_IF_1_CMD_EN;
    } else {
        regval &= ~SF_CTRL_SF_IF_1_CMD_EN;
    }

    /* Configure address */
    regval &= ~SF_CTRL_SF_IF_1_ADR_BYTE_MASK;
    if (cfg->addr_size != 0) {
        regval |= SF_CTRL_SF_IF_1_ADR_EN;
        regval |= ((cfg->addr_size-1) << SF_CTRL_SF_IF_1_ADR_BYTE_SHIFT);
    } else {
        regval &= ~SF_CTRL_SF_IF_1_ADR_EN;
    }

    /* configure dummy */
    regval &= ~SF_CTRL_SF_IF_1_DMY_BYTE_MASK;
    if (cfg->dummy_clks != 0) {
        regval |= SF_CTRL_SF_IF_1_DMY_EN;
        regval |= ((cfg->dummy_clks-1) << SF_CTRL_SF_IF_1_DMY_BYTE_SHIFT);
    } else {
        regval &= ~SF_CTRL_SF_IF_1_DMY_EN;
    }

    /* Configure data */
    if (cfg->nb_data != 0) {
        regval |= SF_CTRL_SF_IF_1_DAT_EN;
    } else {
        regval &= ~SF_CTRL_SF_IF_1_DAT_EN;
    }

    /* Set read write flag */
    if (cfg->rw_flag) {
        regval |= SF_CTRL_SF_IF_1_DAT_RW;
    } else {
        regval &= ~SF_CTRL_SF_IF_1_DAT_RW;
    }
    putreg32(regval, reg_base+SF_CTRL_SF_IF_IAHB_0_OFFSET);
}

#ifdef BFLB_SF_CTRL_PSRAM_ENABLE
/****************************************************************************/ /**
 * @brief  Config psram controller for psram I/D cache write
 *
 * @param  cfg: Serial flash controller command configuration pointer
 * @param  cmd_valid: command valid or not, cache may need no command
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION bflb_sf_ctrl_psram_write_set(struct sf_ctrl_cmd_cfg_type *cfg, uint8_t cmd_valid)
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;
    uint32_t time_out = 0;

    reg_base = BFLB_SF_CTRL_BASE;
    time_out = SF_CTRL_BUSY_STATE_TIMEOUT;

    while (bflb_sf_ctrl_get_busy_state()) {
        time_out--;

        if (time_out == 0) {
            return;
        }
    }

    regval = getreg32(reg_base + SF_CTRL_1_OFFSET);
    if ((regval & SF_CTRL_SF_IF_FN_SEL) == 0) {
        return;
    }

    /* Copy command buffer */
    putreg32(cfg->cmd_buf[0], reg_base+SF_CTRL_SF_IF_IAHB_4_OFFSET);
    putreg32(cfg->cmd_buf[1], reg_base+SF_CTRL_SF_IF_IAHB_5_OFFSET);

    getreg32(reg_base + SF_CTRL_SF_IF_IAHB_3_OFFSET);
    /* Configure SPI and IO mode*/
    if (SF_CTRL_CMD_1_LINE == cfg->cmd_mode) {
        regval &= ~SF_CTRL_SF_IF_2_QPI_MODE_EN;
    } else {
        regval |= SF_CTRL_SF_IF_2_QPI_MODE_EN;
    }

    regval &= ~SF_CTRL_SF_IF_2_SPI_MODE_MASK;
    if (SF_CTRL_ADDR_1_LINE == cfg->addr_mode) {
        if (SF_CTRL_DATA_1_LINE == cfg->data_mode) {
            regval |= (SF_CTRL_NIO_MODE << SF_CTRL_SF_IF_2_SPI_MODE_SHIFT);
        } else if (SF_CTRL_DATA_2_LINES == cfg->data_mode) {
            regval |= (SF_CTRL_DO_MODE << SF_CTRL_SF_IF_2_SPI_MODE_SHIFT);
        } else if (SF_CTRL_DATA_4_LINES == cfg->data_mode) {
            regval |= (SF_CTRL_QO_MODE << SF_CTRL_SF_IF_2_SPI_MODE_SHIFT);
        }
    } else if (SF_CTRL_ADDR_2_LINES == cfg->addr_mode) {
        regval |= (SF_CTRL_DIO_MODE << SF_CTRL_SF_IF_2_SPI_MODE_SHIFT);
    } else if (SF_CTRL_ADDR_4_LINES == cfg->addr_mode) {
        regval |= (SF_CTRL_QIO_MODE << SF_CTRL_SF_IF_2_SPI_MODE_SHIFT);
    }

    regval &= ~SF_CTRL_SF_IF_2_CMD_BYTE_MASK;
    if (cmd_valid) {
        regval |= SF_CTRL_SF_IF_2_CMD_EN;
    } else {
        regval &= ~SF_CTRL_SF_IF_2_CMD_EN;
    }

    /* Configure address */
    regval &= ~SF_CTRL_SF_IF_2_ADR_BYTE_MASK;
    if (cfg->addr_size != 0) {
        regval |= SF_CTRL_SF_IF_2_ADR_EN;
        regval |= ((cfg->addr_size-1) << SF_CTRL_SF_IF_2_ADR_BYTE_SHIFT);
    } else {
        regval &= ~SF_CTRL_SF_IF_2_ADR_EN;
    }

    /* configure dummy */
    regval &= ~SF_CTRL_SF_IF_2_DMY_BYTE_MASK;
    if (cfg->dummy_clks != 0) {
        regval |= SF_CTRL_SF_IF_2_DMY_EN;
        regval |= ((cfg->dummy_clks-1) << SF_CTRL_SF_IF_2_DMY_BYTE_SHIFT);
    } else {
        regval &= ~SF_CTRL_SF_IF_2_DMY_EN;
    }

    /* Configure data */
    if (cfg->nb_data != 0) {
        regval |= SF_CTRL_SF_IF_2_DAT_EN;
    } else {
        regval &= ~SF_CTRL_SF_IF_2_DAT_EN;
    }

    /* Set read write flag */
    if (cfg->rw_flag) {
        regval |= SF_CTRL_SF_IF_2_DAT_RW;
    } else {
        regval &= ~SF_CTRL_SF_IF_2_DAT_RW;
    }
    putreg32(regval, reg_base+SF_CTRL_SF_IF_IAHB_3_OFFSET);
}
#endif

/****************************************************************************/ /**
 * @brief  Config bank2 controller for flash2 I/D cache read
 *
 * @param  cfg: Serial flash controller command configuration pointer
 * @param  cmd_valid: command valid or not, for continous read, cache may need no command
 *
 * @return None
 *
*******************************************************************************/
__WEAK
#ifdef BFLB_SF_CTRL_PSRAM_ENABLE
void ATTR_TCM_SECTION bflb_sf_ctrl_psram_read_set(struct sf_ctrl_cmd_cfg_type *cfg, uint8_t cmd_valid)
#else
void ATTR_TCM_SECTION bflb_sf_ctrl_xip2_set(struct sf_ctrl_cmd_cfg_type *cfg, uint8_t cmd_valid)
#endif
{
    uint32_t reg_base = 0;
    uint32_t regval = 0;
    uint32_t time_out = 0;

    reg_base = BFLB_SF_CTRL_BASE;
    time_out = SF_CTRL_BUSY_STATE_TIMEOUT;

    while (bflb_sf_ctrl_get_busy_state()) {
        time_out--;

        if (time_out == 0) {
            return;
        }
    }

    regval = getreg32(reg_base + SF_CTRL_1_OFFSET);
    if ((regval & SF_CTRL_SF_IF_FN_SEL) == 0) {
        return;
    }

    /* Copy command buffer */
    putreg32(cfg->cmd_buf[0], reg_base+SF_CTRL_SF_IF_IAHB_10_OFFSET);
    putreg32(cfg->cmd_buf[1], reg_base+SF_CTRL_SF_IF_IAHB_11_OFFSET);

    regval = getreg32(reg_base + SF_CTRL_SF_IF_IAHB_9_OFFSET);
    /* Configure SPI and IO mode*/
    if (SF_CTRL_CMD_1_LINE == cfg->cmd_mode) {
        regval &= ~SF_CTRL_SF_IF_4_QPI_MODE_EN;
    } else {
        regval |= SF_CTRL_SF_IF_4_QPI_MODE_EN;
    }

    regval &= ~SF_CTRL_SF_IF_4_SPI_MODE_MASK;
    if (SF_CTRL_ADDR_1_LINE == cfg->addr_mode) {
        if (SF_CTRL_DATA_1_LINE == cfg->data_mode) {
            regval |= (SF_CTRL_NIO_MODE << SF_CTRL_SF_IF_4_SPI_MODE_SHIFT);
        } else if (SF_CTRL_DATA_2_LINES == cfg->data_mode) {
            regval |= (SF_CTRL_DO_MODE << SF_CTRL_SF_IF_4_SPI_MODE_SHIFT);
        } else if (SF_CTRL_DATA_4_LINES == cfg->data_mode) {
            regval |= (SF_CTRL_QO_MODE << SF_CTRL_SF_IF_4_SPI_MODE_SHIFT);
        }
    } else if (SF_CTRL_ADDR_2_LINES == cfg->addr_mode) {
        regval |= (SF_CTRL_DIO_MODE << SF_CTRL_SF_IF_4_SPI_MODE_SHIFT);
    } else if (SF_CTRL_ADDR_4_LINES == cfg->addr_mode) {
        regval |= (SF_CTRL_QIO_MODE << SF_CTRL_SF_IF_4_SPI_MODE_SHIFT);
    }

    regval &= ~SF_CTRL_SF_IF_4_CMD_BYTE_MASK;
    if (cmd_valid) {
        regval |= SF_CTRL_SF_IF_4_CMD_EN;
    } else {
        regval &= ~SF_CTRL_SF_IF_4_CMD_EN;
    }

    /* Configure address */
    regval &= ~SF_CTRL_SF_IF_4_ADR_BYTE_MASK;
    if (cfg->addr_size != 0) {
        regval |= SF_CTRL_SF_IF_4_ADR_EN;
        regval |= ((cfg->addr_size-1) << SF_CTRL_SF_IF_4_ADR_BYTE_SHIFT);
    } else {
        regval &= ~SF_CTRL_SF_IF_4_ADR_EN;
    }

    /* configure dummy */
    regval &= ~SF_CTRL_SF_IF_4_DMY_BYTE_MASK;
    if (cfg->dummy_clks != 0) {
        regval |= SF_CTRL_SF_IF_4_DMY_EN;
        regval |= ((cfg->dummy_clks-1) << SF_CTRL_SF_IF_4_DMY_BYTE_SHIFT);
    } else {
        regval &= ~SF_CTRL_SF_IF_4_DMY_EN;
    }

    /* Configure data */
    if (cfg->nb_data != 0) {
        regval |= SF_CTRL_SF_IF_4_DAT_EN;
    } else {
        regval &= ~SF_CTRL_SF_IF_4_DAT_EN;
    }

    /* Set read write flag */
    if (cfg->rw_flag) {
        regval |= SF_CTRL_SF_IF_4_DAT_RW;
    } else {
        regval &= ~SF_CTRL_SF_IF_4_DAT_RW;
    }
    putreg32(regval, reg_base+SF_CTRL_SF_IF_IAHB_9_OFFSET);
}

/****************************************************************************/ /**
 * @brief  Get SF Ctrl busy state
 *
 * @param  None
 *
 * @return 1 means SF ctrl busy or 0 means SF ctrl not busy
 *
*******************************************************************************/
__WEAK
uint8_t ATTR_TCM_SECTION bflb_sf_ctrl_get_busy_state(void)
{
    uint32_t regval = 0;
    uint32_t cmd_offset = 0;

#ifdef BFLB_SF_CTRL_SBUS2_ENABLE
    if (bflb_sf_ctrl_is_sbus2_enable() == 0) {
        cmd_offset = BFLB_SF_CTRL_BASE + SF_CTRL_IF1_SAHB_OFFSET;
    } else {
        cmd_offset = BFLB_SF_CTRL_BASE + SF_CTRL_IF2_SAHB_OFFSET;
    }
#else
    cmd_offset = BFLB_SF_CTRL_BASE + SF_CTRL_IF1_SAHB_OFFSET;
#endif

    regval = getreg32(cmd_offset + SF_CTRL_IF_SAHB_0_OFFSET);
    if (regval & SF_CTRL_IF_BUSY) {
        return 1;
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  SF Controller interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void bflb_sf_ctrl_irqhandler(void)
{
    /* TODO: Not implemented */
}

/*@} end of group SF_CTRL_Public_Functions */

/*@} end of group SF_CTRL */

/*@} end of group BL628_Peripheral_Driver */
