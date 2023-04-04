/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-03-24     spaceman          the first version
 */

#ifndef __DRV_DCMI_H__
#define __DRV_DCMI_H__

#include <rtthread.h>
#include "board.h"

#ifdef BSP_USING_DCMI

#ifdef __cplusplus
extern "C" {
#endif

#define DCMI_DEVICE(dev)              (struct stm32_dcmi *)(dev)

#define DCMI_CTRL_CROP                (0x01)
#define DCMI_CTRL_TRANSMIT_CONTINUOUS (0x02)
#define DCMI_CTRL_TRANSMIT_SNAPSHOT   (0x03)
#define DCMI_CTRL_SUSPEND             (0x04)
#define DCMI_CTRL_RESUME              (0x05)
#define DCMI_CTRL_STOP                (0x06)
#define DCMI_CTRL_GET_FPS             (0x07)

struct stm32_dcmi {
    struct rt_device parent;

    DCMI_HandleTypeDef dcmi_handle;
    DMA_HandleTypeDef dma_handle;

    struct rt_semaphore cam_semaphore;
};

struct stm32_dcmi_cropsize {
    uint16_t displey_xsize;
    uint16_t displey_ysize;
    uint16_t sensor_xsize;
    uint16_t sensor_ysize;
};

struct stm32_dcmi_dma_transmitbuffer {
    uint32_t dma_buffer;
    uint32_t dma_buffersize;
};

#ifdef __cplusplus
}
#endif

#endif /* BSP_USING_DCMI */

#endif /* __DRV_DCMI_H__ */
