/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_display.h"
#include "fsl_hx8394.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define HX8394_DelayMs VIDEO_DelayMs

typedef struct
{
    const uint8_t *cmd;
    uint8_t cmdLen;
} hx8394_cmd_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
const display_operations_t hx8394_ops = {
    .init   = HX8394_Init,
    .deinit = HX8394_Deinit,
    .start  = HX8394_Start,
    .stop   = HX8394_Stop,
};

static const hx8394_cmd_t s_hx8394Cmds[] = {
    {(const uint8_t[]){0x36U, 0x02U}, 2U},

    {(const uint8_t[]){0xB1U, 0x48U, 0x12U, 0x72U, 0x09U, 0x32U, 0x54U, 0x71U, 0x71U, 0x57U, 0x47U}, 11U},

    {(const uint8_t[]){0xB2U, 0x00U, 0x80U, 0x64U, 0x0CU, 0x0DU, 0x2FU}, 7U},

    {(const uint8_t[]){0xB4U, 0x73U, 0x74U, 0x73U, 0x74U, 0x73U, 0x74U, 0x01U, 0x0CU, 0x86U, /* 10 */
                       0x75U, 0x00U, 0x3FU, 0x73U, 0x74U, 0x73U, 0x74U, 0x73U, 0x74U, 0x01U, /* 20 */
                       0x0CU, 0x86U},
     22U},

    {(const uint8_t[]){0xD3U, 0x00U, 0x00U, 0x07U, 0x07U, 0x40U, 0x07U, 0x0CU, 0x00U, 0x08U, /* 10 */
                       0x10U, 0x08U, 0x00U, 0x08U, 0x54U, 0x15U, 0x0AU, 0x05U, 0x0AU, 0x02U, /* 20 */
                       0x15U, 0x06U, 0x05U, 0x06U, 0x47U, 0x44U, 0x0AU, 0x0AU, 0x4BU, 0x10U, /* 30 */
                       0x07U, 0x07U, 0x0CU, 0x40U},
     34U},

    {(const uint8_t[]){0xD5U, 0x1CU, 0x1CU, 0x1DU, 0x1DU, 0x00U, 0x01U, 0x02U, 0x03U, 0x04U, /* 10 */
                       0x05U, 0x06U, 0x07U, 0x08U, 0x09U, 0x0AU, 0x0BU, 0x24U, 0x25U, 0x18U, /* 20 */
                       0x18U, 0x26U, 0x27U, 0x18U, 0x18U, 0x18U, 0x18U, 0x18U, 0x18U, 0x18U, /* 30 */
                       0x18U, 0x18U, 0x18U, 0x18U, 0x18U, 0x18U, 0x18U, 0x18U, 0x18U, 0x20U, /* 40 */
                       0x21U, 0x18U, 0x18U, 0x18U, 0x18U},
     45U},

    {(const uint8_t[]){0xD6U, 0x1CU, 0x1CU, 0x1DU, 0x1DU, 0x07U, 0x06U, 0x05U, 0x04U, 0x03U, /* 10 */
                       0x02U, 0x01U, 0x00U, 0x0BU, 0x0AU, 0x09U, 0x08U, 0x21U, 0x20U, 0x18U, /* 20 */
                       0x18U, 0x27U, 0x26U, 0x18U, 0x18U, 0x18U, 0x18U, 0x18U, 0x18U, 0x18U, /* 30 */
                       0x18U, 0x18U, 0x18U, 0x18U, 0x18U, 0x18U, 0x18U, 0x18U, 0x18U, 0x25U, /* 40 */
                       0x24U, 0x18U, 0x18U, 0x18U, 0x18U},
     45U},

    {(const uint8_t[]){0xB6U, 0x92U, 0x92U}, 3U},

    {(const uint8_t[]){0xE0U, 0x00U, 0x0AU, 0x15U, 0x1BU, 0x1EU, 0x21U, 0x24U, 0x22U, 0x47U, /* 10 */
                       0x56U, 0x65U, 0x66U, 0x6EU, 0x82U, 0x88U, 0x8BU, 0x9AU, 0x9DU, 0x98U, /* 20 */
                       0xA8U, 0xB9U, 0x5DU, 0x5CU, 0x61U, 0x66U, 0x6AU, 0x6FU, 0x7FU, 0x7FU, /* 30 */
                       0x00U, 0x0AU, 0x15U, 0x1BU, 0x1EU, 0x21U, 0x24U, 0x22U, 0x47U, 0x56U, /* 40 */
                       0x65U, 0x65U, 0x6EU, 0x81U, 0x87U, 0x8BU, 0x98U, 0x9DU, 0x99U, 0xA8U, /* 50 */
                       0xBAU, 0x5DU, 0x5DU, 0x62U, 0x67U, 0x6BU, 0x72U, 0x7FU, 0x7FU},
     59U},

    {(const uint8_t[]){0xC0U, 0x1FU, 0x31U}, 3U},
    {(const uint8_t[]){0xCCU, 0x03U}, 2U},
    {(const uint8_t[]){0xD4U, 0x02U}, 2U},
    {(const uint8_t[]){0xBDU, 0x02U}, 2U},

    {(const uint8_t[]){0xD8U, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, /* 10 */
                       0xFFU, 0xFFU, 0xFFU},
     13U},

    {(const uint8_t[]){0xBDU, 0x00U}, 2U},
    {(const uint8_t[]){0xBDU, 0x01U}, 2U},
    {(const uint8_t[]){0xB1U, 0x00U}, 2U},
    {(const uint8_t[]){0xBDU, 0x00U}, 2U},

    {(const uint8_t[]){0xBFU, 0x40U, 0x81U, 0x50U, 0x00U, 0x1AU, 0xFCU, 0x01}, 8U},

    {(const uint8_t[]){0xC6U, 0xEDU}, 2U},

    {(const uint8_t[]){0x35U, 0x00U}, 2U},
};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t HX8394_Init(display_handle_t *handle, const display_config_t *config)
{
    uint8_t i;
    status_t status                   = kStatus_Success;
    const hx8394_resource_t *resource = (const hx8394_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice      = resource->dsiDevice;
    uint8_t setmipi[7]                = {0xBAU, 0x60U, 0x03U, 0x68U, 0x6BU, 0xB2U, 0xC0U};

    /* Only support 720 * 1280 */
    if (config->resolution != FSL_VIDEO_RESOLUTION(720, 1280))
    {
        return kStatus_InvalidArgument;
    }

    /* Power on. */
    resource->pullPowerPin(true);
    HX8394_DelayMs(1);

    /* Perform reset. */
    resource->pullResetPin(false);
    HX8394_DelayMs(1);
    resource->pullResetPin(true);
    HX8394_DelayMs(50U);

    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0xB9U, 0xFFU, 0x83U, 0x94U}, 4);

    setmipi[1] |= (config->dsiLanes - 1U);

    if (kStatus_Success == status)
    {
        status = MIPI_DSI_GenericWrite(dsiDevice, setmipi, 7);
    }

    if (kStatus_Success == status)
    {
        for (i = 0; i < ARRAY_SIZE(s_hx8394Cmds); i++)
        {
            status = MIPI_DSI_GenericWrite(dsiDevice, s_hx8394Cmds[i].cmd, (int32_t)s_hx8394Cmds[i].cmdLen);

            if (kStatus_Success != status)
            {
                break;
            }
        }
    }

    if (kStatus_Success == status)
    {
        status = MIPI_DSI_DCS_EnterSleepMode(dsiDevice, false);
    }

    if (kStatus_Success == status)
    {
        HX8394_DelayMs(120U);

        status = MIPI_DSI_DCS_SetDisplayOn(dsiDevice, true);
    }

    return status;
}

status_t HX8394_Deinit(display_handle_t *handle)
{
    const hx8394_resource_t *resource = (const hx8394_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice      = resource->dsiDevice;

    (void)MIPI_DSI_DCS_EnterSleepMode(dsiDevice, true);

    resource->pullResetPin(false);
    resource->pullPowerPin(false);

    return kStatus_Success;
}

status_t HX8394_Start(display_handle_t *handle)
{
    const hx8394_resource_t *resource = (const hx8394_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice      = resource->dsiDevice;

    return MIPI_DSI_DCS_SetDisplayOn(dsiDevice, true);
}

status_t HX8394_Stop(display_handle_t *handle)
{
    const hx8394_resource_t *resource = (const hx8394_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice      = resource->dsiDevice;

    return MIPI_DSI_DCS_SetDisplayOn(dsiDevice, false);
}
