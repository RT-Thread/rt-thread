/*
 * Copyright (c) 2023 HPMicro
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
        ptr->CTRL2 &= ~ENET_CTRL2_ENET0_PHY_INF_SEL_MASK;
        ptr->CTRL2 |= ENET_CTRL2_ENET0_PHY_INF_SEL_SET(inf_type);
    }  else {
        return status_invalid_argument;
    }

    return stat;
}

static inline hpm_stat_t enet_enable_lpi_interrupt(ENET_Type *ptr)
{
    hpm_stat_t stat = status_success;

    if (ptr == HPM_ENET0) {
        ptr->CTRL2 |= ENET_CTRL2_ENET0_LPI_IRQ_EN_MASK;
    } else {
        return status_invalid_argument;
    }

    return stat;
}

static inline hpm_stat_t enet_disable_lpi_interrupt(ENET_Type *ptr)
{
    hpm_stat_t stat = status_success;

    if (ptr == HPM_ENET0) {
        ptr->CTRL2 &= ~ENET_CTRL2_ENET0_LPI_IRQ_EN_MASK;
    } else {
        return status_invalid_argument;
    }

    return stat;
}

static inline hpm_stat_t enet_rgmii_set_clock_delay(ENET_Type *ptr, uint8_t tx_delay, uint8_t rx_delay)
{
    hpm_stat_t stat = status_success;

    if (ptr == HPM_ENET0) {
        ptr->CTRL0 &= ~(ENET_CTRL0_ENET0_TXCLK_DLY_SEL_MASK | ENET_CTRL0_ENET0_RXCLK_DLY_SEL_MASK);
        ptr->CTRL0 |= ENET_CTRL0_ENET0_TXCLK_DLY_SEL_SET(tx_delay) | ENET_CTRL0_ENET0_RXCLK_DLY_SEL_SET(rx_delay);
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
            ptr->CTRL2 |= ENET_CTRL2_ENET0_REFCLK_OE_MASK | ENET_CTRL2_ENET0_RMII_TXCLK_SEL_MASK;
        } else {
            /* use an external clock as reference clock for rmii mode */
            ptr->CTRL2 |= ENET_CTRL2_ENET0_RMII_TXCLK_SEL_MASK; /* use an external clock */
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
        ptr->CTRL2 &= ~ENET_CTRL2_ENET0_RMII_TXCLK_SEL_MASK;
    } else {
        return status_invalid_argument;
    }

    return stat;
}

#if defined __cplusplus
} /* __cplusplus */
#endif

#endif /* HPM_ENET_SOC_DRV_H */
