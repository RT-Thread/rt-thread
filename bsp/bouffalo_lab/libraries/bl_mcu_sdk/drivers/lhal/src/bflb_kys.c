/**
  ******************************************************************************
  * @file    bflb_kys.c
  * @version V1.0
  * @date    2022-11-17
  * @brief   This file is the low hardware abstraction layer file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2022 Bouffalo Lab</center></h2>
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
#include "bflb_core.h"
#include "bflb_kys.h"
#include "bflb_clock.h"
#include "bflb_l1c.h"
#include "hardware/kys_reg.h"

/**
 * @brief keyscan init
 *
 * @param dev
 * @param config
 */
void bflb_kys_init(struct bflb_device_s *dev, const struct bflb_kys_config_s *config)
{
    uint32_t reg_base;
    uint32_t reg_val;

    reg_base = dev->reg_base;
    /* disable kys */
    reg_val = getreg32(reg_base + KYS_KS_CTRL_OFFSET);
    reg_val &= ~(KYS_KS_EN_MASK);
    putreg32(reg_val, reg_base + KYS_KS_CTRL_OFFSET);

    /* mask all interrupt before init */
    reg_val = getreg32(reg_base + KYS_KS_INT_EN_OFFSET);
#if defined(BL702)
    reg_val &= ~(KYS_KS_INT_EN_MASK);
#else
    reg_val &= ~(KYS_KS_DONE_INT_EN_MASK |
                 KYS_KEYFIFO_FULL_INT_EN_MASK |
                 KYS_KEYFIFO_HALF_INT_EN_MASK |
                 KYS_KEYFIFO_QUARTER_INT_EN_MASK |
                 KYS_KEYFIFO_NONEMPTY_INT_EN_MASK |
                 KYS_GHOST_INT_EN_MASK);
#endif

    /* kys init */
    reg_val = getreg32(reg_base + KYS_KS_CTRL_OFFSET);

    reg_val &= ~(KYS_COL_NUM_MASK |
                 KYS_ROW_NUM_MASK |
#if defined(BL702L)
                 KYS_FIFO_MODE_MASK |
#endif
                 KYS_RC_EXT_MASK |
                 KYS_GHOST_EN_MASK |
                 KYS_DEG_EN_MASK |
                 KYS_DEG_CNT_MASK);
    reg_val |= ((config->col - 1) << KYS_COL_NUM_SHIFT);
    reg_val |= ((config->row - 1) << KYS_ROW_NUM_SHIFT);
    reg_val |= ((config->idle_duration) << KYS_RC_EXT_SHIFT);
    reg_val |= (config->ghost_en << KYS_GHOST_EN_SHIFT);
    reg_val |= (config->deglitch_en << KYS_DEG_EN_SHIFT);
    reg_val |= (config->deglitch_cnt << KYS_DEG_CNT_SHIFT);
#if defined(BL702L)
    reg_val |= (0x1 << KYS_FIFO_MODE_SHIFT);
#endif
    putreg32(reg_val, reg_base + KYS_KS_CTRL_OFFSET);
}

/**
 * @brief keyscan enable
 *
 */
void bflb_kys_enable(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t reg_val;

    reg_base = dev->reg_base;
    reg_val = getreg32(reg_base + KYS_KS_CTRL_OFFSET);
    reg_val |= (0x1 << KYS_KS_EN_SHIFT);
    putreg32(reg_val, reg_base + KYS_KS_CTRL_OFFSET);
}

/**
 * @brief keyscan disable
 *
 */
void bflb_kys_disable(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t reg_val;

    reg_base = dev->reg_base;

    reg_val = getreg32(reg_base + KYS_KS_CTRL_OFFSET);
    reg_val &= ~(KYS_KS_EN_MASK);
    putreg32(reg_val, reg_base + KYS_KS_CTRL_OFFSET);
}

/**
 * @brief keyscan interrupt enable
 *
 * @param dev
 * @param flag interrupt flag @KEYSCAN_INT_EN define
 * @param enable enable or disable interrupt
 */
void bflb_kys_int_enable(struct bflb_device_s *dev, uint32_t flag, bool enable)
{
    uint32_t reg_base;
    uint32_t reg_val_en;

    reg_base = dev->reg_base;
    reg_val_en = getreg32(reg_base + KYS_KS_INT_EN_OFFSET);

    if (enable) {
        reg_val_en |= (flag);
    } else {
        reg_val_en &= ~(flag);
    }
    putreg32(reg_val_en, reg_base + KYS_KS_INT_EN_OFFSET);
}

/**
 * @brief keyscan interrupt clear flag
 *
 * @param dev
 * @param flag
 */
void bflb_kys_int_clear(struct bflb_device_s *dev, uint32_t flag)
{
    putreg32(flag, dev->reg_base + KYS_KEYCODE_CLR_OFFSET);
}
/**
 * @brief keyscan get interrupt status
 *
 * @param dev
 * @return uint32_t
 */
uint32_t bflb_kys_get_int_status(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t reg_sts_val, reg_mask_val;

    reg_base = dev->reg_base;
    reg_sts_val = getreg32(reg_base + KYS_KS_INT_STS_OFFSET);
    reg_mask_val = getreg32(reg_base + KYS_KS_INT_EN_OFFSET);

    return (reg_sts_val & (reg_mask_val));
}

#if defined(BL702L)
/**
 * @brief get keyscan keycode index in fifo
 *
 * @param dev
 * @param fifo_head
 * @param fifo_tail
 * @param fifo_valid_cnt
 *
 */
void bflb_kys_get_fifo_info(struct bflb_device_s *dev, uint8_t *fifo_head, uint8_t *fifo_tail, uint8_t *fifo_valid_cnt)
{
    uint32_t reg_base;
    uint32_t reg_val;

    reg_base = dev->reg_base;
    reg_val = getreg32(reg_base + KYS_KEYFIFO_IDX_OFFSET);

    *fifo_head = (uint8_t)(reg_val & 0x7);
    *fifo_tail = (uint8_t)((reg_val & 0x700) >> 8);
    *fifo_valid_cnt = (uint8_t)((reg_val & 0xf0000) >> 16);
}

#endif
/**
 * @brief get keyscan keycode value
 *
 * @param dev
 * @param index
 * @return uint8_t
 */
uint8_t bflb_kys_read_keyvalue(struct bflb_device_s *dev, uint8_t index)
{
#if defined(BL702L)
    return (uint8_t)(getreg32(dev->reg_base + KYS_KEYFIFO_VALUE_OFFSET) & 0xff);
#endif
#if defined(BL702)
    return (uint8_t)((getreg32(dev->reg_base + KYS_KEYFIFO_VALUE_OFFSET) >> (index * 8)) & 0xff);
#endif
}
