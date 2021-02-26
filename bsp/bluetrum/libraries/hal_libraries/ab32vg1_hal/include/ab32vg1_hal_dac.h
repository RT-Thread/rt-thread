/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AB32BG1_HAL_DAC_H__
#define AB32BG1_HAL_DAC_H__

#include "ab32vg1_hal_def.h"

struct dac_init
{

};

struct dac_handle
{
    hal_sfr_t           instance;
    struct dac_init     init;
};

/* Initialization functions */
hal_error_t hal_dac_init(struct dac_handle *hdac);
void hal_dac_deinit(uint32_t dacx);
void hal_dac_mspinit(struct dac_handle *hdac);

void hal_dac_control(uint32_t dacx, uint32_t cntl, uint32_t param);
void hal_dac_write(uint32_t dacx, uint32_t data);
uint32_t hal_dac_read(uint32_t dacx);

#endif
