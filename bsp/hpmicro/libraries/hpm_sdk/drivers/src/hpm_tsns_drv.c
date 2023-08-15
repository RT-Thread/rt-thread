/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_tsns_drv.h"

void tsns_configure_low_limit_event(TSNS_Type *ptr, int32_t low, tsns_event_t e)
{
    switch (e) {
    case tsns_event_irq:
        tsns_set_irq_threshold_low(ptr, low);
        ptr->CONFIG |= TSNS_CONFIG_IRQ_EN_MASK | TSNS_CONFIG_COMPARE_MIN_EN_MASK;
        break;
    case tsns_event_reset:
        tsns_set_reset_threshold_low(ptr, low);
        ptr->CONFIG |= TSNS_CONFIG_RST_EN_MASK | TSNS_CONFIG_COMPARE_MIN_EN_MASK;
        break;
    default:
        assert(NULL);
    }
}

void tsns_configure_high_limit_event(TSNS_Type *ptr, int32_t high, tsns_event_t e)
{
    switch (e) {
    case tsns_event_irq:
        tsns_set_irq_threshold_high(ptr, high);
        ptr->CONFIG |= TSNS_CONFIG_IRQ_EN_MASK | TSNS_CONFIG_COMPARE_MAX_EN_MASK;
        break;
    case tsns_event_reset:
        tsns_set_reset_threshold_high(ptr, high);
        ptr->CONFIG |= TSNS_CONFIG_RST_EN_MASK | TSNS_CONFIG_COMPARE_MAX_EN_MASK;
        break;
    default:
        assert(NULL);
    }
}

void tsns_configure_limit_event(TSNS_Type *ptr, int32_t high, int32_t low, tsns_event_t e)
{
    assert(high > low);
    switch (e) {
    case tsns_event_irq:
        tsns_config_irq_threshold(ptr, high, low);
        ptr->CONFIG |= TSNS_CONFIG_IRQ_EN_MASK | TSNS_CONFIG_COMPARE_MAX_EN_MASK | TSNS_CONFIG_COMPARE_MIN_EN_MASK;
        break;
    case tsns_event_reset:
        tsns_config_reset_threshold(ptr, high, low);
        ptr->CONFIG |= TSNS_CONFIG_RST_EN_MASK | TSNS_CONFIG_COMPARE_MAX_EN_MASK | TSNS_CONFIG_COMPARE_MIN_EN_MASK;
        break;
    default:
        assert(NULL);
    }
}

