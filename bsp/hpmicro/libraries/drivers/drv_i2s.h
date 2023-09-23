/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DRV_I2S_H
#define DRV_I2S_H

#define I2S_FIFO_SIZE (2048)

//AUDIO CONCTRL的参数定义
#define AUDIO_PARM_I2S_DATA_LINE 4

int rt_hw_i2s_init(void);

#endif /* DRV_I2S_H */

