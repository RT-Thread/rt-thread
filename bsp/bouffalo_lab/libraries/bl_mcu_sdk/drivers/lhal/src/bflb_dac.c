#include "bflb_dac.h"
#include "hardware/dac_reg.h"

#if defined(BL702) || defined(BL602) || defined(BL702L)
#define DAC_GPIP_BASE ((uint32_t)0x40002000)
#elif defined(BL616) || defined(BL606P) || defined(BL808) || defined(BL628)
#define DAC_GPIP_BASE ((uint32_t)0x20002000)
#endif

void bflb_dac_init(struct bflb_device_s *dev, uint8_t clk_div)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    /* dac reset */
    regval = getreg32(reg_base + GLB_GPDAC_CTRL_OFFSET);
    regval &= ~GLB_GPDACA_RSTN_ANA;
    putreg32(regval, reg_base + GLB_GPDAC_CTRL_OFFSET);

    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");

    regval = getreg32(reg_base + GLB_GPDAC_CTRL_OFFSET);
    regval &= ~GLB_GPDACB_RSTN_ANA;
    putreg32(regval, reg_base + GLB_GPDAC_CTRL_OFFSET);

    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");

    regval = getreg32(reg_base + GLB_GPDAC_CTRL_OFFSET);
    regval |= (GLB_GPDACA_RSTN_ANA | GLB_GPDACB_RSTN_ANA);
    putreg32(regval, reg_base + GLB_GPDAC_CTRL_OFFSET);

    regval = getreg32(reg_base + GLB_GPDAC_CTRL_OFFSET);
    regval &= ~GLB_GPDAC_REF_SEL;
    putreg32(regval, reg_base + GLB_GPDAC_CTRL_OFFSET);

    regval = 0;
    regval |= GPIP_GPDAC_EN;
#ifdef GPIP_GPDAC_EN2
    regval |= GPIP_GPDAC_EN2;
#endif
    regval |= (clk_div << GPIP_GPDAC_MODE_SHIFT);
    putreg32(regval, DAC_GPIP_BASE + GPIP_GPDAC_CONFIG_OFFSET);

    regval = getreg32(DAC_GPIP_BASE + GPIP_GPDAC_DMA_CONFIG_OFFSET);
    regval &= ~GPIP_GPDAC_DMA_TX_EN;
    putreg32(regval, DAC_GPIP_BASE + GPIP_GPDAC_DMA_CONFIG_OFFSET);
}

void bflb_dac_channel_enable(struct bflb_device_s *dev, uint8_t ch)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    if (ch & DAC_CHANNEL_A) {
        regval = getreg32(reg_base + GLB_GPDAC_ACTRL_OFFSET);
        regval |= (GLB_GPDAC_A_EN | GLB_GPDAC_IOA_EN);
        putreg32(regval, reg_base + GLB_GPDAC_ACTRL_OFFSET);
    }

    if (ch & DAC_CHANNEL_B) {
        regval = getreg32(reg_base + GLB_GPDAC_BCTRL_OFFSET);
        regval |= (GLB_GPDAC_B_EN | GLB_GPDAC_IOB_EN);
        putreg32(regval, reg_base + GLB_GPDAC_BCTRL_OFFSET);
#ifdef GPIP_GPDAC_EN2
        regval = getreg32(reg_base + GLB_GPDAC_ACTRL_OFFSET);
        regval |= (GLB_GPDAC_A_EN | GLB_GPDAC_IOA_EN);
        putreg32(regval, reg_base + GLB_GPDAC_ACTRL_OFFSET);
#endif
    }
}

void bflb_dac_channel_disable(struct bflb_device_s *dev, uint8_t ch)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    if (ch & DAC_CHANNEL_A) {
        regval = getreg32(reg_base + GLB_GPDAC_ACTRL_OFFSET);
        regval &= ~(GLB_GPDAC_A_EN | GLB_GPDAC_IOA_EN);
        putreg32(regval, reg_base + GLB_GPDAC_ACTRL_OFFSET);
    }

    if (ch & DAC_CHANNEL_B) {
        regval = getreg32(reg_base + GLB_GPDAC_BCTRL_OFFSET);
        regval &= ~(GLB_GPDAC_B_EN | GLB_GPDAC_IOB_EN);
        putreg32(regval, reg_base + GLB_GPDAC_BCTRL_OFFSET);
    }
}

void bflb_dac_link_txdma(struct bflb_device_s *dev, bool enable)
{
    uint32_t regval1;
    uint32_t regval2;
    uint32_t reg_base;
    uint8_t flag = 0;

    reg_base = dev->reg_base;

    regval1 = getreg32(DAC_GPIP_BASE + GPIP_GPDAC_CONFIG_OFFSET);
    regval1 &= ~GPIP_GPDAC_CH_A_SEL_MASK;
    regval1 &= ~GPIP_GPDAC_CH_B_SEL_MASK;

    regval2 = getreg32(DAC_GPIP_BASE + GPIP_GPDAC_DMA_CONFIG_OFFSET);
    if (enable) {
        if (getreg32(reg_base + GLB_GPDAC_ACTRL_OFFSET) & (GLB_GPDAC_A_EN | GLB_GPDAC_IOA_EN)) {
            regval1 |= (1 << GPIP_GPDAC_CH_A_SEL_SHIFT);
            flag++;
        }

        if (getreg32(reg_base + GLB_GPDAC_BCTRL_OFFSET) & (GLB_GPDAC_B_EN | GLB_GPDAC_IOB_EN)) {
            regval1 |= (1 << GPIP_GPDAC_CH_B_SEL_SHIFT);
            flag++;
        }

        if (flag == 1) {
            regval2 |= (0 << GPIP_GPDAC_DMA_FORMAT_SHIFT);
        } else {
            regval2 |= (1 << GPIP_GPDAC_DMA_FORMAT_SHIFT);
        }
        regval2 |= GPIP_GPDAC_DMA_TX_EN;
    } else {
        regval2 &= ~GPIP_GPDAC_DMA_TX_EN;
    }
    putreg32(regval2, DAC_GPIP_BASE + GPIP_GPDAC_DMA_CONFIG_OFFSET);
    putreg32(regval1, DAC_GPIP_BASE + GPIP_GPDAC_CONFIG_OFFSET);
}

void bflb_dac_set_value(struct bflb_device_s *dev, uint8_t ch, uint16_t value)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + GLB_GPDAC_DATA_OFFSET);

    if (ch & DAC_CHANNEL_A) {
        regval &= ~GLB_GPDAC_A_DATA_MASK;
        regval |= (value << GLB_GPDAC_A_DATA_SHIFT);
    }

    if (ch & DAC_CHANNEL_B) {
        regval &= ~GLB_GPDAC_B_DATA_MASK;
        regval |= (value << GLB_GPDAC_B_DATA_SHIFT);
    }

    putreg32(regval, reg_base + GLB_GPDAC_DATA_OFFSET);
}