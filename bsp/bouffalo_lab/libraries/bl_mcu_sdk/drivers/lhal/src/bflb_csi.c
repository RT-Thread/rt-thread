#include "bflb_csi.h"
#include "hardware/csi_reg.h"
#include "hardware/dtsrc_reg.h"

#define DTSRC_BASE 0x30012800

static void bflb_csi_phy_config(struct bflb_device_s *dev, uint32_t tx_clk_escape, uint32_t data_rate)
{
    uint32_t reg_base;
    uint32_t regval;
    
    /* Unit: ns */
    float TD_TERM_EN_MAX = 35 + 4 * (1e3) / data_rate; 
    uint32_t TD_TERM_EN = (TD_TERM_EN_MAX * data_rate / 2 / (1e3)) - 1;
    float THS_SETTLE_MAX = 145 + 10 * (1e3) / data_rate;
    /* THS_SETTLE = reg_time_hs_settle + reg_time_hs_term_en */
    uint32_t THS_SETTLE = ((THS_SETTLE_MAX - TD_TERM_EN * 2 * (1e3) / data_rate) * data_rate / 2 / (1e3)) - 1;
    uint32_t TCLK_TERM_EN_MAX = 38;
    uint32_t TCLK_TERM_EN = (tx_clk_escape * TCLK_TERM_EN_MAX) / (1e3);
    uint32_t TCLK_SETTLE_MAX = 300;
    /* TCLK_SETTLE = reg_time_ck_settle + reg_time_ck_term_en */
    uint32_t TCLK_SETTLE = ((TCLK_SETTLE_MAX - TCLK_TERM_EN * (1e3) / tx_clk_escape) * tx_clk_escape / (1e3)) - 1;

    uint32_t ANA_TERM_EN = 0x8;
    
    reg_base = dev->reg_base;
    regval = TD_TERM_EN  << CSI_REG_TIME_HS_TERM_EN_SHIFT & CSI_REG_TIME_HS_TERM_EN_MASK;
    regval |= THS_SETTLE << CSI_REG_TIME_HS_SETTLE_SHIFT & CSI_REG_TIME_HS_SETTLE_MASK;
    regval |= TCLK_TERM_EN << CSI_REG_TIME_CK_TERM_EN_SHIFT & CSI_REG_TIME_CK_TERM_EN_MASK;
    regval |= TCLK_SETTLE << CSI_REG_TIME_CK_SETTLE_SHIFT & CSI_REG_TIME_CK_SETTLE_MASK;
    putreg32(regval, reg_base + CSI_DPHY_CONFIG_1_OFFSET);
    
    regval = getreg32(DTSRC_BASE + CSI_DPHY_CONFIG_2_OFFSET);
    regval &= ~CSI_REG_ANA_TERM_EN_MASK;
    regval |= ANA_TERM_EN << CSI_REG_ANA_TERM_EN_SHIFT & CSI_REG_ANA_TERM_EN_MASK;
    putreg32(regval, reg_base + CSI_DPHY_CONFIG_2_OFFSET);
}

void bflb_csi_init(struct bflb_device_s *dev, const struct bflb_csi_config_s *config)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(DTSRC_BASE + DTSRC_CONFIG_OFFSET);
    regval |= DTSRC_CR_SNSR_EN;
    putreg32(regval, DTSRC_BASE + DTSRC_CONFIG_OFFSET);
    
    regval = getreg32(reg_base + CSI_DPHY_CONFIG_0_OFFSET);
    regval &= ~(CSI_DL0_ENABLE | CSI_DL1_ENABLE | CSI_CL_ENABLE | CSI_DL0_FORCERXMODE | CSI_DL1_FORCERXMODE | CSI_RESET_N);
    putreg32(regval, reg_base + CSI_DPHY_CONFIG_0_OFFSET);
    regval |= CSI_RESET_N;
    putreg32(regval, reg_base + CSI_DPHY_CONFIG_0_OFFSET);
    
    regval = getreg32(reg_base + CSI_MIPI_CONFIG_OFFSET);
    if (config->lane_number) {
        regval |= CSI_CR_LANE_NUM;
    } else {
        regval &= ~CSI_CR_LANE_NUM;
    }
    regval |= CSI_CR_UNPACK_EN | CSI_CR_SYNC_SP_EN;
    putreg32(regval, reg_base + CSI_MIPI_CONFIG_OFFSET);
    
    bflb_csi_phy_config(dev, config->tx_clk_escape / 1000000, config->data_rate / 1000000);
    
    regval = getreg32(reg_base + CSI_DPHY_CONFIG_0_OFFSET);
    regval |= CSI_DL0_ENABLE | CSI_CL_ENABLE | CSI_DL0_FORCERXMODE;
    if (config->lane_number) {
        regval |= CSI_DL1_ENABLE | CSI_DL1_FORCERXMODE;
    }
    putreg32(regval, reg_base + CSI_DPHY_CONFIG_0_OFFSET);
    
    regval = getreg32(DTSRC_BASE + DTSRC_CONFIG_OFFSET);
    regval |= DTSRC_CR_ENABLE;
    putreg32(regval, DTSRC_BASE + DTSRC_CONFIG_OFFSET);
}

void bflb_csi_start(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + CSI_MIPI_CONFIG_OFFSET);
    regval |= CSI_CR_CSI_EN;
    putreg32(regval, reg_base + CSI_MIPI_CONFIG_OFFSET);
}

void bflb_csi_stop(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + CSI_MIPI_CONFIG_OFFSET);
    regval &= ~CSI_CR_CSI_EN;
    putreg32(regval, reg_base + CSI_MIPI_CONFIG_OFFSET);
}

void bflb_csi_set_line_threshold(struct bflb_device_s *dev, uint16_t resolution_x, uint32_t pixel_clock, uint32_t dsp_clock)
{
    uint32_t threshold;
    
    threshold = (dsp_clock - pixel_clock) / 1000 * resolution_x / (dsp_clock / 1000) + 10;
    putreg32(threshold, DTSRC_BASE + DTSRC_SNSR2DVP_WAIT_POS_OFFSET);
}

void bflb_csi_int_mask(struct bflb_device_s *dev, uint32_t int_type, bool mask)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + CSI_INT_MASK_OFFSET);
    if (mask) {
        regval |= int_type;
    } else {
        regval &= ~int_type;
    }
    putreg32(regval, reg_base + CSI_INT_MASK_OFFSET);
}

void bflb_csi_int_clear(struct bflb_device_s *dev, uint32_t int_type)
{
    putreg32(int_type, dev->reg_base + CSI_INT_CLEAR_OFFSET);
}

uint32_t bflb_csi_get_intstatus(struct bflb_device_s *dev)
{
    return(getreg32(dev->reg_base + CSI_INT_STATUS_OFFSET));
}

int bflb_csi_feature_control(struct bflb_device_s *dev, int cmd, size_t arg)
{
    int ret = 0;

    switch (cmd) {
        default:
            ret = -EPERM;
            break;
    }
    return ret;
}
