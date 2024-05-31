/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_GPIOM_SOC_DRV_H
#define HPM_GPIOM_SOC_DRV_H

/**
 * @addtogroup gpiom_interface GPIOM driver APIs
 * @{
 */

/* @brief gpiom control module */
typedef enum gpiom_gpio {
    gpiom_soc_gpio0 = 0,
    gpiom_core0_fast = 2,
} gpiom_gpio_t;

/**
 * @}
 */

#endif /* HPM_GPIOM_SOC_DRV_H */

