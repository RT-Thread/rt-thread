/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_display.h"
#include "fsl_rm68191.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define RM68191_DelayMs VIDEO_DelayMs

typedef struct _rm68191_setting
{
    const uint8_t *value;
    uint8_t len;
} rm68191_setting_t;

#define RM68191_MAKE_SETTING_ITEM(setting)  \
    {                                       \
        (setting), (uint8_t)sizeof(setting) \
    }

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const uint8_t s_rm68191Cmd0[]  = {0xF0, 0x55, 0xAA, 0x52, 0x08, 0x03};
static const uint8_t s_rm68191Cmd1[]  = {0x90, 0x05, 0x16, 0x09, 0x03, 0xCD, 0x00, 0x00, 0x00, 0x00};
static const uint8_t s_rm68191Cmd2[]  = {0x91, 0x05, 0x16, 0x0B, 0x03, 0xCF, 0x00, 0x00, 0x00, 0x00};
static const uint8_t s_rm68191Cmd3[]  = {0x92, 0x40, 0x0C, 0x0D, 0x0E, 0x0F, 0x00, 0x8F, 0x00, 0x00, 0x04, 0x08};
static const uint8_t s_rm68191Cmd4[]  = {0x94, 0x00, 0x08, 0x0C, 0x03, 0xD1, 0x03, 0xD2, 0x0C};
static const uint8_t s_rm68191Cmd5[]  = {0x95, 0x40, 0x10, 0x00, 0x11, 0x00, 0x12, 0x00, 0x13,
                                        0x00, 0x8F, 0x00, 0x00, 0x00, 0x04, 0x00, 0x08};
static const uint8_t s_rm68191Cmd6[]  = {0x99, 0x00, 0x00};
static const uint8_t s_rm68191Cmd7[]  = {0x9A, 0x80, 0x10, 0x03, 0xD5, 0x03, 0xD7, 0x00, 0x00, 0x00, 0x00, 0x50};
static const uint8_t s_rm68191Cmd8[]  = {0x9B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t s_rm68191Cmd9[]  = {0x9C, 0x00, 0x00};
static const uint8_t s_rm68191Cmd10[] = {0x9D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00};
static const uint8_t s_rm68191Cmd11[] = {0x9E, 0x00, 0x00};
static const uint8_t s_rm68191Cmd12[] = {0xA0, 0x84, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x08, 0x1F, 0x0A, 0x1F};
static const uint8_t s_rm68191Cmd13[] = {0xA1, 0x1F, 0x1F, 0x1F, 0x1F, 0x0C, 0x1F, 0x0E, 0x1F, 0x1F, 0x1F};
static const uint8_t s_rm68191Cmd14[] = {0xA2, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x02, 0x1F, 0x06, 0x1F};
static const uint8_t s_rm68191Cmd15[] = {0xA3, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
static const uint8_t s_rm68191Cmd16[] = {0xA4, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x07, 0x1F, 0x03, 0x1F, 0x0F};
static const uint8_t s_rm68191Cmd17[] = {0xA5, 0x1F, 0x0D, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0B, 0x1F, 0x09};
static const uint8_t s_rm68191Cmd18[] = {0xA6, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x01, 0x05};
static const uint8_t s_rm68191Cmd19[] = {0xA7, 0x03, 0x07, 0x1F, 0x1F, 0x1F, 0x1F, 0x0B, 0x1F, 0x09, 0x1F};
static const uint8_t s_rm68191Cmd20[] = {0xA8, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x1F, 0x0D, 0x1F, 0x1F, 0x1F};
static const uint8_t s_rm68191Cmd21[] = {0xA9, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x05, 0x1F, 0x01, 0x1F};
static const uint8_t s_rm68191Cmd22[] = {0xAA, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
static const uint8_t s_rm68191Cmd23[] = {0xAB, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x1F, 0x04, 0x1F, 0x0C};
static const uint8_t s_rm68191Cmd24[] = {0xAC, 0x1F, 0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x08, 0x1F, 0x0A};
static const uint8_t s_rm68191Cmd25[] = {0xAD, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x06, 0x02};
static const uint8_t s_rm68191Cmd26[] = {0xF0, 0x55, 0xAA, 0x52, 0x08, 0x02};
static const uint8_t s_rm68191Cmd27[] = {0xEA, 0x7D};
static const uint8_t s_rm68191Cmd28[] = {0xF0, 0x55, 0xAA, 0x52, 0x08, 0x00};
static const uint8_t s_rm68191Cmd29[] = {0xBC, 0x00, 0x00, 0x00};
static const uint8_t s_rm68191Cmd30[] = {0xB8, 0x01, 0xAF, 0x8F, 0x8F};
static const uint8_t s_rm68191Cmd31[] = {0xF0, 0x55, 0xAA, 0x52, 0x08, 0x01};
static const uint8_t s_rm68191Cmd32[] = {0xD1, 0x00, 0x00, 0x00, 0x26, 0x00, 0x5E, 0x00, 0x88,
                                         0x00, 0xA8, 0x00, 0xDB, 0x01, 0x02, 0x01, 0x3D};
static const uint8_t s_rm68191Cmd33[] = {0xD2, 0x01, 0x67, 0x01, 0xA6, 0x01, 0xD3, 0x02, 0x16,
                                         0x02, 0x49, 0x02, 0x4B, 0x02, 0x7B, 0x02, 0xB3};
static const uint8_t s_rm68191Cmd34[] = {0xD3, 0x02, 0xD9, 0x03, 0x0E, 0x03, 0x31, 0x03, 0x61,
                                         0x03, 0x80, 0x03, 0xA5, 0x03, 0xBD, 0x03, 0xD2};
static const uint8_t s_rm68191Cmd35[] = {0xD4, 0x03, 0xE5, 0x03, 0xFF};
static const uint8_t s_rm68191Cmd36[] = {0xD5, 0x00, 0x00, 0x00, 0x26, 0x00, 0x5E, 0x00, 0x88,
                                         0x00, 0xA8, 0x00, 0xDB, 0x01, 0x02, 0x01, 0x3D};
static const uint8_t s_rm68191Cmd37[] = {0xD6, 0x01, 0x67, 0x01, 0xA6, 0x01, 0xD3, 0x02, 0x16,
                                         0x02, 0x49, 0x02, 0x4B, 0x02, 0x7B, 0x02, 0xB3};
static const uint8_t s_rm68191Cmd38[] = {0xD7, 0x02, 0xD9, 0x03, 0x0E, 0x03, 0x31, 0x03, 0x61,
                                         0x03, 0x80, 0x03, 0xA5, 0x03, 0xBD, 0x03, 0xD2};
static const uint8_t s_rm68191Cmd39[] = {0xD8, 0x03, 0xE5, 0x03, 0xFF};
static const uint8_t s_rm68191Cmd40[] = {0xD9, 0x00, 0x00, 0x00, 0x26, 0x00, 0x5E, 0x00, 0x88,
                                         0x00, 0xA8, 0x00, 0xDB, 0x01, 0x02, 0x01, 0x3D};
static const uint8_t s_rm68191Cmd41[] = {0xDD, 0x01, 0x67, 0x01, 0xA6, 0x01, 0xD3, 0x02, 0x16,
                                         0x02, 0x49, 0x02, 0x4B, 0x02, 0x7B, 0x02, 0xB3};
static const uint8_t s_rm68191Cmd42[] = {0xDE, 0x02, 0xD9, 0x03, 0x0E, 0x03, 0x31, 0x03, 0x61,
                                         0x03, 0x80, 0x03, 0xA5, 0x03, 0xBD, 0x03, 0xD2};
static const uint8_t s_rm68191Cmd43[] = {0xDF, 0x03, 0xE5, 0x03, 0xFF};
static const uint8_t s_rm68191Cmd44[] = {0xE0, 0x00, 0x00, 0x00, 0x26, 0x00, 0x5E, 0x00, 0x88,
                                         0x00, 0xA8, 0x00, 0xDB, 0x01, 0x02, 0x01, 0x3D};
static const uint8_t s_rm68191Cmd45[] = {0xE1, 0x01, 0x67, 0x01, 0xA6, 0x01, 0xD3, 0x02, 0x16,
                                         0x02, 0x49, 0x02, 0x4B, 0x02, 0x7B, 0x02, 0xB3};
static const uint8_t s_rm68191Cmd46[] = {0xE2, 0x02, 0xD9, 0x03, 0x0E, 0x03, 0x31, 0x03, 0x61,
                                         0x03, 0x80, 0x03, 0xA5, 0x03, 0xBD, 0x03, 0xD2};
static const uint8_t s_rm68191Cmd47[] = {0xE3, 0x03, 0xE5, 0x03, 0xFF};
static const uint8_t s_rm68191Cmd48[] = {0xE4, 0x00, 0x00, 0x00, 0x26, 0x00, 0x5E, 0x00, 0x88,
                                         0x00, 0xA8, 0x00, 0xDB, 0x01, 0x02, 0x01, 0x3D};
static const uint8_t s_rm68191Cmd49[] = {0xE5, 0x01, 0x67, 0x01, 0xA6, 0x01, 0xD3, 0x02, 0x16,
                                         0x02, 0x49, 0x02, 0x4B, 0x02, 0x7B, 0x02, 0xB3};
static const uint8_t s_rm68191Cmd50[] = {0xE6, 0x02, 0xD9, 0x03, 0x0E, 0x03, 0x31, 0x03, 0x61,
                                         0x03, 0x80, 0x03, 0xA5, 0x03, 0xBD, 0x03, 0xD2};
static const uint8_t s_rm68191Cmd51[] = {0xE7, 0x03, 0xE5, 0x03, 0xFF};
static const uint8_t s_rm68191Cmd52[] = {0xE8, 0x00, 0x00, 0x00, 0x26, 0x00, 0x5E, 0x00, 0x88,
                                         0x00, 0xA8, 0x00, 0xDB, 0x01, 0x02, 0x01, 0x3D};
static const uint8_t s_rm68191Cmd53[] = {0xE9, 0x01, 0x67, 0x01, 0xA6, 0x01, 0xD3, 0x02, 0x16,
                                         0x02, 0x49, 0x02, 0x4B, 0x02, 0x7B, 0x02, 0xB3};
static const uint8_t s_rm68191Cmd54[] = {0xEA, 0x02, 0xD9, 0x03, 0x0E, 0x03, 0x31, 0x03, 0x61,
                                         0x03, 0x80, 0x03, 0xA5, 0x03, 0xBD, 0x03, 0xD2};
static const uint8_t s_rm68191Cmd55[] = {0xEB, 0x03, 0xE5, 0x03, 0xFF};
static const uint8_t s_rm68191Cmd56[] = {0xB0, 0x07, 0x07, 0x07};
static const uint8_t s_rm68191Cmd57[] = {0xB1, 0x07, 0x07, 0x07};
static const uint8_t s_rm68191Cmd58[] = {0xB3, 0x11, 0x11, 0x11};
static const uint8_t s_rm68191Cmd59[] = {0xB4, 0x09, 0x09, 0x09};
static const uint8_t s_rm68191Cmd60[] = {0xB6, 0x44, 0x44, 0x44};
static const uint8_t s_rm68191Cmd61[] = {0xB7, 0x34, 0x34, 0x34};
static const uint8_t s_rm68191Cmd62[] = {0xB9, 0x34, 0x34, 0x34};
static const uint8_t s_rm68191Cmd63[] = {0xBA, 0x14, 0x14, 0x14};
static const uint8_t s_rm68191Cmd64[] = {0xBC, 0x00, 0x98, 0x00};
static const uint8_t s_rm68191Cmd65[] = {0xBD, 0x00, 0x98, 0x00};
static const uint8_t s_rm68191Cmd66[] = {0xBE, 0x1D};
static const uint8_t s_rm68191Cmd67[] = {0x35, 0x00};

static const rm68191_setting_t s_rm68191InitSetting[] = {
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd0),  RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd1),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd2),  RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd3),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd4),  RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd5),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd6),  RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd7),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd8),  RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd9),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd10), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd11),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd12), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd13),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd14), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd15),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd16), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd17),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd18), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd19),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd20), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd21),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd22), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd23),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd24), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd25),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd26), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd27),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd28), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd29),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd30), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd31),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd32), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd33),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd34), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd35),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd36), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd37),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd38), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd39),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd40), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd41),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd42), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd43),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd44), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd45),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd46), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd47),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd48), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd49),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd50), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd51),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd52), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd53),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd54), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd55),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd56), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd57),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd58), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd59),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd60), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd61),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd62), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd63),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd64), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd65),
    RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd66), RM68191_MAKE_SETTING_ITEM(s_rm68191Cmd67),
};

const display_operations_t rm68191_ops = {
    .init   = RM68191_Init,
    .deinit = RM68191_Deinit,
    .start  = RM68191_Start,
    .stop   = RM68191_Stop,
};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t RM68191_Init(display_handle_t *handle, const display_config_t *config)
{
    uint32_t i;
    status_t status                    = kStatus_Success;
    const rm68191_resource_t *resource = (const rm68191_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice       = resource->dsiDevice;

    /* Only support 540 * 960 */
    if (config->resolution != FSL_VIDEO_RESOLUTION(540, 960))
    {
        return kStatus_InvalidArgument;
    }

    /* Power on. */
    resource->pullPowerPin(true);
    RM68191_DelayMs(1);

    /* Perform reset. */
    resource->pullResetPin(false);
    RM68191_DelayMs(1);
    resource->pullResetPin(true);
    RM68191_DelayMs(5);

    /* Set the LCM init settings. */
    for (i = 0; i < ARRAY_SIZE(s_rm68191InitSetting); i++)
    {
        status = MIPI_DSI_DCS_Write(dsiDevice, s_rm68191InitSetting[i].value, (int32_t)s_rm68191InitSetting[i].len);

        if (kStatus_Success != status)
        {
            return status;
        }
    }

    /* Exit sleep mode */
    status = MIPI_DSI_DCS_EnterSleepMode(dsiDevice, false);

    if (kStatus_Success != status)
    {
        return status;
    }

    RM68191_DelayMs(200);

    /* Set display on. */
    status = MIPI_DSI_DCS_SetDisplayOn(dsiDevice, true);

    if (kStatus_Success != status)
    {
        return status;
    }

    RM68191_DelayMs(200);

    return kStatus_Success;
}

status_t RM68191_Deinit(display_handle_t *handle)
{
    const rm68191_resource_t *resource = (const rm68191_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice       = resource->dsiDevice;

    (void)MIPI_DSI_DCS_EnterSleepMode(dsiDevice, true);

    resource->pullResetPin(false);
    resource->pullPowerPin(false);

    return kStatus_Success;
}

status_t RM68191_Start(display_handle_t *handle)
{
    const rm68191_resource_t *resource = (const rm68191_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice       = resource->dsiDevice;

    return MIPI_DSI_DCS_SetDisplayOn(dsiDevice, true);
}

status_t RM68191_Stop(display_handle_t *handle)
{
    const rm68191_resource_t *resource = (const rm68191_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice       = resource->dsiDevice;

    return MIPI_DSI_DCS_SetDisplayOn(dsiDevice, false);
}
