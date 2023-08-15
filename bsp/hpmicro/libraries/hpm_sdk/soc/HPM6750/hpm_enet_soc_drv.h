/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_ENET_SOC_DRV_H
#define HPM_ENET_SOC_DRV_H

#include "hpm_soc.h"

#if defined __cplusplus
extern "C" {
#endif

static inline hpm_stat_t enet_intf_selection(ENET_Type *ptr, uint8_t inf_type)
{
    hpm_stat_t stat = status_success;

    if (ptr == HPM_ENET0) {
        HPM_CONCTL->CTRL2 &= ~CONCTL_CTRL2_ENET0_PHY_INTF_SEL_MASK;
        HPM_CONCTL->CTRL2 |= CONCTL_CTRL2_ENET0_PHY_INTF_SEL_SET(inf_type);
    } else if (ptr == HPM_ENET1) {
        HPM_CONCTL->CTRL3 &= ~CONCTL_CTRL3_ENET1_PHY_INTF_SEL_MASK;
        HPM_CONCTL->CTRL3 |= CONCTL_CTRL3_ENET1_PHY_INTF_SEL_SET(inf_type);
    } else {
        return status_invalid_argument;
    }

    return stat;
}

static inline hpm_stat_t enet_enable_lpi_interrupt(ENET_Type *ptr)
{
    hpm_stat_t stat = status_success;

    if (ptr == HPM_ENET0) {
        HPM_CONCTL->CTRL2 |= CONCTL_CTRL2_ENET0_LPI_IRQ_EN_MASK;
    } else if (ptr == HPM_ENET1) {
        HPM_CONCTL->CTRL3 |= CONCTL_CTRL3_ENET1_LPI_IRQ_EN_MASK;
    } else {
        return status_invalid_argument;
    }

    return stat;
}

static inline hpm_stat_t enet_disable_lpi_interrupt(ENET_Type *ptr)
{
    hpm_stat_t stat = status_success;

    if (ptr == HPM_ENET0) {
        HPM_CONCTL->CTRL2 &= ~CONCTL_CTRL2_ENET0_LPI_IRQ_EN_MASK;
    } else if (ptr == HPM_ENET1) {
        HPM_CONCTL->CTRL3 &= ~CONCTL_CTRL3_ENET1_LPI_IRQ_EN_MASK;
    } else {
        return status_invalid_argument;
    }

    return stat;
}

static inline hpm_stat_t enet_rgmii_set_clock_delay(ENET_Type *ptr, uint8_t tx_delay, uint8_t rx_delay)
{
    hpm_stat_t stat = status_success;

    if (ptr == HPM_ENET0) {
        HPM_CONCTL->CTRL0 &= ~(CONCTL_CTRL0_ENET0_TXCLK_DLY_SEL_MASK | CONCTL_CTRL0_ENET0_RXCLK_DLY_SEL_MASK);
        HPM_CONCTL->CTRL0 |= CONCTL_CTRL0_ENET0_TXCLK_DLY_SEL_SET(tx_delay) | CONCTL_CTRL0_ENET0_RXCLK_DLY_SEL_SET(rx_delay);
    } else if (ptr == HPM_ENET1) {
        HPM_CONCTL->CTRL0 &= ~(CONCTL_CTRL0_ENET1_TXCLK_DLY_SEL_MASK | CONCTL_CTRL0_ENET1_RXCLK_DLY_SEL_MASK);
        HPM_CONCTL->CTRL0 |= CONCTL_CTRL0_ENET1_TXCLK_DLY_SEL_SET(tx_delay) | CONCTL_CTRL0_ENET1_RXCLK_DLY_SEL_SET(rx_delay);
    } else {
        return status_invalid_argument;
    }

    return stat;
}

static inline hpm_stat_t enet_rmii_enable_clock(ENET_Type *ptr, bool internal)
{
    hpm_stat_t stat = status_success;

    /* use an internal PLL clock as reference clock for rmii mode */
    if (ptr == HPM_ENET0) {
        if (internal == true) {
            /* use a pll clock */
            HPM_CONCTL->CTRL2 |= CONCTL_CTRL2_ENET0_REFCLK_OE_MASK | CONCTL_CTRL2_ENET0_RMII_TXCLK_SEL_MASK;
        } else {
            /* use an external clock as reference clock for rmii mode */
            HPM_CONCTL->CTRL2 |= CONCTL_CTRL2_ENET0_RMII_TXCLK_SEL_MASK; /* use an external clock */
        }
    } else if (ptr == HPM_ENET1) {
        if (internal == true) {
            /* use a pll clock */
            HPM_CONCTL->CTRL3 |= CONCTL_CTRL3_ENET1_REFCLK_OE_MASK | CONCTL_CTRL3_ENET1_RMII_TXCLK_SEL_MASK;
        } else {
            /* use an external clock as reference clock for rmii mode */
            HPM_CONCTL->CTRL3 |= CONCTL_CTRL3_ENET1_RMII_TXCLK_SEL_MASK; /* use an external clock */
        }
    } else {
        return status_invalid_argument;
    }

    return stat;
}

static inline hpm_stat_t enet_rgmii_enable_clock(ENET_Type *ptr)
{
    hpm_stat_t stat = status_success;

    if (ptr == HPM_ENET0) {
        /* use an internal PLL clock for rgmii mode */
        HPM_CONCTL->CTRL2 &= ~CONCTL_CTRL2_ENET0_RMII_TXCLK_SEL_MASK;
    } else if (ptr == HPM_ENET1) {
        /* use an internal PLL clock for rgmii mode */
        HPM_CONCTL->CTRL3 &= ~CONCTL_CTRL3_ENET1_RMII_TXCLK_SEL_MASK;
    } else {
        return status_invalid_argument;
    }

    return stat;
}

#if defined __cplusplus
} /* __cplusplus */
#endif

#endif /* HPM_ENET_SOC_DRV_H */
