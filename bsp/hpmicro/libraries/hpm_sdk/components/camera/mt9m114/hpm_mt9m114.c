/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_mt9m114.h"
#include "board.h"
#include "hpm_clock_drv.h"
#include <math.h>

#if defined(MT9M114_SHOW_DEBUG_INFO) && MT9M114_SHOW_DEBUG_INFO
#define DEBUG_INFO(...) printf(__VA_ARGS__)
#else
#define DEBUG_INFO(...)
#endif

#if MT9M114_ERROR_ACTION_BLOCK
#define ERROR_ACTION() do {                                    \
        DEBUG_INFO("[ERROR]:%s %d\n", __func__, __LINE__);     \
        for (;;) {                                             \
        }                                                      \
    } while (0)
#else
#define ERROR_ACTION() return (status_fail)
#endif

const mt9m114_reg_t mt9m114_vga[] = {
    {MT9M114_VAR_CAM_SENSOR_CFG_Y_ADDR_START, 2, 0x0000},     /* cam_sensor_cfg_y_addr_start = 0 */
    {MT9M114_VAR_CAM_SENSOR_CFG_X_ADDR_START, 2, 0x0000},     /* cam_sensor_cfg_x_addr_start = 0 */
    {MT9M114_VAR_CAM_SENSOR_CFG_Y_ADDR_END, 2, 0x03CD},       /* cam_sensor_cfg_y_addr_end = 973 */
    {MT9M114_VAR_CAM_SENSOR_CFG_X_ADDR_END, 2, 0x050D},       /* cam_sensor_cfg_x_addr_end = 1293 */
    {MT9M114_VAR_CAM_SENSOR_CFG_CPIPE_LAST_ROW, 2, 0x01E3},   /* cam_sensor_cfg_cpipe_last_row = 483 */
    {MT9M114_VAR_CAM_CROP_WINDOW_WIDTH, 2, 0x0280},           /* cam_crop_window_width = 640 */
    {MT9M114_VAR_CAM_CROP_WINDOW_HEIGHT, 2, 0x01E0},          /* cam_crop_window_height = 480 */
    {MT9M114_VAR_CAM_OUTPUT_WIDTH, 2, 0x0280},                /* cam_output_width = 640 */
    {MT9M114_VAR_CAM_OUTPUT_HEIGHT, 2, 0x01E0},               /* cam_output_height = 480 */
    {MT9M114_VAR_CAM_STAT_AWB_CLIP_WINDOW_XEND, 2, 0x027F},   /* cam_stat_awb_clip_window_xend = 639 */
    {MT9M114_VAR_CAM_STAT_AWB_CLIP_WINDOW_YEND, 2, 0x01DF},   /* cam_stat_awb_clip_window_yend = 479 */
    {MT9M114_VAR_CAM_STAT_AE_INITIAL_WINDOW_XEND, 2, 0x007F}, /* cam_stat_ae_initial_window_xend = 127 */
    {MT9M114_VAR_CAM_STAT_AE_INITIAL_WINDOW_YEND, 2, 0x005F}, /* cam_stat_ae_initial_window_yend = 95 */
};

const mt9m114_reg_t mt9m114_init_config[] = {
    {MT9M114_REG_LOGICAL_ADDRESS_ACCESS, 2u, 0x1000},
    /* PLL Fout = (Fin * 2 * m) / ((n + 1) * (p + 1)) */
    {MT9M114_VAR_CAM_SYSCTL_PLL_ENABLE, 1u, 0x01},        /*  cam_sysctl_pll_enable = 1 */
    {MT9M114_VAR_CAM_SYSCTL_PLL_DIVIDER_M_N, 2u, 0x0120}, /*  cam_sysctl_pll_divider_m_n = 288 */
    {MT9M114_VAR_CAM_SYSCTL_PLL_DIVIDER_P, 2u, 0x0700},   /*  cam_sysctl_pll_divider_p = 1792 */
    {MT9M114_VAR_CAM_SENSOR_CFG_PIXCLK, 4u, 0x2DC6C00},   /*  cam_sensor_cfg_pixclk = 48000000 */
    {0x316A, 2, 0x8270},                                  /*  auto txlo_row for hot pixel and linear full well optimization */
    {0x316C, 2, 0x8270},                                  /*  auto txlo for hot pixel and linear full well optimization */
    {0x3ED0, 2, 0x2305},                                  /*  eclipse setting, ecl range=1, ecl value=2, ivln=3 */
    {0x3ED2, 2, 0x77CF},                                  /*  TX_hi=12 */
    {0x316E, 2, 0x8202},                                  /*  auto ecl , threshold 2x, ecl=0 at high gain, ecl=2 for low gain */
    {0x3180, 2, 0x87FF},                                  /*  enable delta dark */
    {0x30D4, 2, 0x6080},                                  /*  disable column correction due to AE oscillation problem */
    {0xA802, 2, 0x0008},                                  /*  RESERVED_AE_TRACK_02 */
    {0x3E14, 2, 0xFF39},                                  /*  Enabling pixout clamping to VAA during ADC streaming to solve column band issue */
                                                          /* APGA */
    {0xC95E, 2u, 0x0000},

    {MT9M114_VAR_CAM_SENSOR_CFG_ROW_SPEED, 2u, 0x0001},           /*  cam_sensor_cfg_row_speed = 1 */
    {MT9M114_VAR_CAM_SENSOR_CFG_FINE_INTEG_TIME_MIN, 2u, 0x01C3}, /*  cam_sensor_cfg_fine_integ_time_min = 451 */
    {MT9M114_VAR_CAM_SENSOR_CFG_FINE_INTEG_TIME_MAX, 2u, 0x03BA}, /*  cam_sensor_cfg_fine_integ_time_max = 954 */
    {MT9M114_VAR_CAM_SENSOR_CFG_FRAME_LENGTH_LINES, 2u, 0x02DE},  /*  cam_sensor_cfg_frame_length_lines = 734 */
    {MT9M114_VAR_CAM_SENSOR_CFG_LINE_LENGTH_PCK, 2u, 0x04A5},     /*  cam_sensor_cfg_line_length_pck = 1189 */
    {MT9M114_VAR_CAM_SENSOR_CFG_FINE_CORRECTION, 2u, 0x00E0},     /*  cam_sensor_cfg_fine_correction = 224 */
    {MT9M114_VAR_CAM_SENSOR_CFG_REG_0_DATA, 2u, 0x0020},          /*  cam_sensor_cfg_reg_0_data = 32 */
    {MT9M114_VAR_CAM_SENSOR_CONTROL_READ_MODE, 2u, 0x0332},       /*  cam_sensor_control_read_mode = 816 */
    {MT9M114_VAR_CAM_CROP_WINDOW_XOFFSET, 2u, 0x0000},            /*  cam_crop_window_xoffset = 0 */
    {MT9M114_VAR_CAM_CROP_WINDOW_YOFFSET, 2u, 0x0000},            /*  cam_crop_window_yoffset = 0 */
    {MT9M114_VAR_CAM_CROP_CROPMODE, 1u, 0x03},                    /*  cam_crop_cropmode = 3 */
    {MT9M114_VAR_CAM_AET_AEMODE, 1u, 0x00},                       /*  cam_aet_aemode = 0 */
    {MT9M114_VAR_CAM_AET_MAX_FRAME_RATE, 2u, 0x3700},             /*  cam_aet_max_frame_rate = 14080 */
    {MT9M114_VAR_CAM_AET_MIN_FRAME_RATE, 2u, 0x3700},             /*  cam_aet_min_frame_rate = 14080 */

    /* Camera control module   */
    {0xC892, 2u, 0x0267},
    {0xC894, 2u, 0xFF1A},
    {0xC896, 2u, 0xFFB3},
    {0xC898, 2u, 0xFF80},
    {0xC89A, 2u, 0x0166},
    {0xC89C, 2u, 0x0003},
    {0xC89E, 2u, 0xFF9A},
    {0xC8A0, 2u, 0xFEB4},
    {0xC8A2, 2u, 0x024D},
    {0xC8A4, 2u, 0x01BF},
    {0xC8A6, 2u, 0xFF01},
    {0xC8A8, 2u, 0xFFF3},
    {0xC8AA, 2u, 0xFF75},
    {0xC8AC, 2u, 0x0198},
    {0xC8AE, 2u, 0xFFFD},
    {0xC8B0, 2u, 0xFF9A},
    {0xC8B2, 2u, 0xFEE7},
    {0xC8B4, 2u, 0x02A8},
    {0xC8B6, 2u, 0x01D9},
    {0xC8B8, 2u, 0xFF26},
    {0xC8BA, 2u, 0xFFF3},
    {0xC8BC, 2u, 0xFFB3},
    {0xC8BE, 2u, 0x0132},
    {0xC8C0, 2u, 0xFFE8},
    {0xC8C2, 2u, 0xFFDA},
    {0xC8C4, 2u, 0xFECD},
    {0xC8C6, 2u, 0x02C2},
    {0xC8C8, 2u, 0x0075},
    {0xC8CA, 2u, 0x011C},
    {0xC8CC, 2u, 0x009A},
    {0xC8CE, 2u, 0x0105},
    {0xC8D0, 2u, 0x00A4},
    {0xC8D2, 2u, 0x00AC},
    {0xC8D4, 2u, 0x0A8C},
    {0xC8D6, 2u, 0x0F0A},
    {0xC8D8, 2u, 0x1964},

    /* Automatic White balance */
    {MT9M114_VAR_CAM_AWB_AWB_XSHIFT_PRE_ADJ, 2u, 0x0033},
    {MT9M114_VAR_CAM_AWB_AWB_YSHIFT_PRE_ADJ, 2u, 0x003C},
    {MT9M114_VAR_CAM_AWB_AWB_XSCALE, 1u, 0x03},
    {MT9M114_VAR_CAM_AWB_AWB_YSCALE, 1u, 0x02},
    {0xC8F4, 2u, 0x0000},
    {0xC8F6, 2u, 0x0000},
    {0xC8F8, 2u, 0x0000},
    {0xC8FA, 2u, 0xE724},
    {0xC8FC, 2u, 0x1583},
    {0xC8FE, 2u, 0x2045},
    {0xC900, 2u, 0x03FF},
    {0xC902, 2u, 0x007C},
    {0xC90C, 1u, 0x80},
    {0xC90D, 1u, 0x80},
    {0xC90E, 1u, 0x80},
    {0xC90F, 1u, 0x88},
    {0xC910, 1u, 0x80},
    {0xC911, 1u, 0x80},

    /* CPIPE Preference */
    {0xC926, 2u, 0x0020},
    {0xC928, 2u, 0x009A},
    {0xC946, 2u, 0x0070},
    {0xC948, 2u, 0x00F3},
    {0xC944, 1u, 0x20},
    {0xC945, 1u, 0x9A},
    {0xC92A, 1u, 0x80},
    {0xC92B, 1u, 0x4B},
    {0xC92C, 1u, 0x00},
    {0xC92D, 1u, 0xFF},
    {0xC92E, 1u, 0x3C},
    {0xC92F, 1u, 0x02},
    {0xC930, 1u, 0x06},
    {0xC931, 1u, 0x64},
    {0xC932, 1u, 0x01},
    {0xC933, 1u, 0x0C},
    {0xC934, 1u, 0x3C},
    {0xC935, 1u, 0x3C},
    {0xC936, 1u, 0x3C},
    {0xC937, 1u, 0x0F},
    {0xC938, 1u, 0x64},
    {0xC939, 1u, 0x64},
    {0xC93A, 1u, 0x64},
    {0xC93B, 1u, 0x32},
    {0xC93C, 2u, 0x0020},
    {0xC93E, 2u, 0x009A},
    {0xC940, 2u, 0x00DC},
    {0xC942, 1u, 0x38},
    {0xC943, 1u, 0x30},
    {0xC944, 1u, 0x50},
    {0xC945, 1u, 0x19},
    {0xC94A, 2u, 0x0230},
    {0xC94C, 2u, 0x0010},
    {0xC94E, 2u, 0x01CD},
    {0xC950, 1u, 0x05},
    {0xC951, 1u, 0x40},
    {0xC87B, 1u, 0x1B},
    {0xC890, 2u, 0x0080},
    {0xC886, 2u, 0x0100},
    {0xC87C, 2u, 0x005A},
    {0xB42A, 1u, 0x05},
    {0xA80A, 1u, 0x20},

    {MT9M114_VAR_CAM_STAT_AWB_CLIP_WINDOW_XSTART, 2u, 0x0000},   /*  cam_stat_awb_clip_window_xstart = 0 */
    {MT9M114_VAR_CAM_STAT_AWB_CLIP_WINDOW_YSTART, 2u, 0x0000},   /*  cam_stat_awb_clip_window_ystart = 0 */
    {MT9M114_VAR_CAM_STAT_AE_INITIAL_WINDOW_XSTART, 2u, 0x0000}, /*  cam_stat_ae_initial_window_xstart = 0 */
    {MT9M114_VAR_CAM_STAT_AE_INITIAL_WINDOW_YSTART, 2u, 0x0000}, /*  cam_stat_ae_initial_window_ystart = 0 */
    {MT9M114_REG_PAD_SLEW, 2u, 0x0777},                          /*  Pad slew rate */
    {MT9M114_VAR_CAM_OUTPUT_FORMAT_YUV, 2u, 0x0038},             /*  Must set cam_output_format_yuv_clip for CSI */
};

hpm_stat_t mt9m114_read_register(camera_context_t *context, uint32_t reg, uint32_t reg_size, void *value)
{
    hpm_stat_t status;
    uint16_t subaddr = ((reg & 0xff) << 8) | ((reg & 0xff00) >> 8);
    uint8_t data[4];
    uint8_t i = 0;

    status = i2c_master_address_read(context->ptr, context->i2c_device_addr, \
                                     (uint8_t *)&subaddr, MT9M114_REG_ADDR_LEN, \
                                     data, reg_size);
    if (status_success == status) {
        while (reg_size--) {
            ((uint8_t *)value)[i++] = data[reg_size];
        }
    }
    return status;
}

hpm_stat_t mt9m114_write_register(camera_context_t *context, uint32_t reg, uint32_t reg_size, uint32_t value)
{
    uint16_t subaddr = ((reg & 0xff) << 8) | ((reg & 0xff00) >> 8);
    uint8_t data[4];
    uint8_t i;

    i = reg_size;
    while (i--) {
        data[i] = (uint8_t)value;
        value >>= 8;
    }
    return i2c_master_address_write(context->ptr, context->i2c_device_addr, \
                                      (uint8_t *)&subaddr, MT9M114_REG_ADDR_LEN, \
                                      data, reg_size);
}

hpm_stat_t mt9m114_modify_register(camera_context_t *context, uint32_t reg, uint32_t reg_size, uint32_t mask, uint32_t value)
{
    hpm_stat_t status;
    uint32_t reg_value;

    status = mt9m114_read_register(context, reg, reg_size, &reg_value);

    if (status_success != status) {
        return status;
    }

    reg_value = (reg_value & ~(mask)) | (value & mask);

    return mt9m114_write_register(context, reg, reg_size, reg_value);
}

hpm_stat_t mt9m114_multiwrite(camera_context_t *context, const mt9m114_reg_t regs[], uint32_t num)
{
    hpm_stat_t status = status_success;

    for (uint32_t i = 0; i < num; i++) {
        status = mt9m114_write_register(context, regs[i].reg, regs[i].size, regs[i].value);
        if (status_success != status) {
            ERROR_ACTION();
        }
    }

    return status;
}

hpm_stat_t mt9m114_host_command(camera_context_t *context, uint16_t command)
{
    if (mt9m114_write_register(context, MT9M114_REG_COMMAND_REGISTER, 2, (command | MT9M114_COMMAND_OK)) != 0) {
        return status_fail;
    }

    for (int i = 0; i < MT9M114_HOST_CMD_TIMEOUT; i++, context->delay_ms(1)) {
        uint16_t reg_data;

        if (mt9m114_read_register(context, MT9M114_REG_COMMAND_REGISTER, 2, &reg_data) != 0) {
            return status_fail;
        }

        if ((reg_data & command) == 0) {
            return (reg_data & MT9M114_COMMAND_OK) ? 0 : -1;
        }

        if (i == (MT9M114_HOST_CMD_TIMEOUT - 1)) {
            return status_fail;
        }
    }

    return status_success;
}

hpm_stat_t mt9m114_refresh(camera_context_t *context)
{
    hpm_stat_t ret = mt9m114_host_command(context, MT9M114_COMMAND_REFRESH);

    if (ret != status_success) {
        return ret;
    }

    uint8_t reg_data;

    if (mt9m114_read_register(context, MT9M114_VAR_SEQ_ERROR_CODE, 1, &reg_data) != 0) {
        return status_fail;
    }

    return reg_data == 0 ? status_success : status_fail;
}

hpm_stat_t mt9m114_get_current_state(camera_context_t *context, uint8_t *state)
{
    return mt9m114_read_register(context, MT9M114_VAR_SYSMGR_CURRENT_STATE, 1u, state);
}

hpm_stat_t mt9m114_software_reset(camera_context_t *context)
{
    hpm_stat_t status;
    uint16_t value;
    assert(context->delay_ms != NULL);

    mt9m114_modify_register(context, MT9M114_REG_RESET_AND_MISC_CONTROL, 2, 0x01, 0x01);
    context->delay_ms(1);
    mt9m114_modify_register(context, MT9M114_REG_RESET_AND_MISC_CONTROL, 2, 0x01, 0x00);
    context->delay_ms(50);

    /* forever loop if softreset is not done. Loop until reg 0x80's bit 1 is 0 */
    while (1) {
        status = mt9m114_read_register(context, MT9M114_REG_COMMAND_REGISTER, 2u, &value);
        if (status != status_success) {
            ERROR_ACTION();
        }
        if (!(value & MT9M114_COMMAND_SET_STATE)) {
            DEBUG_INFO("[Camera]:sw reset finish\n");
            break;
        }
    }
    return status_success;
}

hpm_stat_t mt9m114_setstate(camera_context_t *context, uint16_t next_state)
{
    uint16_t value;
    hpm_stat_t status = status_success;

    /* Set the desired next state. */
    status = mt9m114_write_register(context, MT9M114_VAR_SYSMGR_NEXT_STATE, 1, next_state);
    if (status_success != status) {
        ERROR_ACTION();
    }

    /* Check that the FW is ready to accept a new command. */
    context->delay_ms(1);
    while (1) {
        status = mt9m114_read_register(context, MT9M114_REG_COMMAND_REGISTER, 2u, &value);
        if (status_success != status) {
            ERROR_ACTION();
        }
        if (!(value & MT9M114_COMMAND_SET_STATE)) {
            break;
        }
        DEBUG_INFO("[Camera]:Set State cmd bit is already set\n");
    }
    DEBUG_INFO("[Camera]:Issue the Set State command 0x%x\n", next_state);

    /* Issue the Set State command. */
    return mt9m114_host_command(context, MT9M114_COMMAND_SET_STATE);
}

hpm_stat_t mt9m114_set_pixformat(camera_context_t *context, display_pixel_format_t pixformat)
{
    uint16_t reg = 0;

    switch (pixformat) {
    case display_pixel_format_yuv422:
        reg = MT9M114_OUTPUT_FORMAT_YUV | MT9M114_OUTPUT_FORMAT_SWAP_BYTES;
        break;
    case display_pixel_format_rgb565:
        reg = MT9M114_OUTPUT_FORMAT_RGB | MT9M114_OUTPUT_FORMAT_RGB565 | MT9M114_OUTPUT_FORMAT_SWAP_BYTES;
        break;
    default:
        return status_invalid_argument;
    }

    if (mt9m114_write_register(context, MT9M114_VAR_CAM_OUTPUT_FORMAT, 2, reg) != 0) {
        return status_fail;
    }

    return mt9m114_setstate(context, MT9M114_SYS_STATE_ENTER_CONFIG_CHANGE);
}

hpm_stat_t mt9m114_set_framerate(camera_context_t *context, int framerate)
{
    if (mt9m114_write_register(context, MT9M114_VAR_CAM_AET_MAX_FRAME_RATE, 2, framerate * 256) != 0) {
        return status_fail;
    }

    if (mt9m114_write_register(context, MT9M114_VAR_CAM_AET_MIN_FRAME_RATE, 2, framerate * 128) != 0) {
        return status_fail;
    }

    return mt9m114_setstate(context, MT9M114_SYS_STATE_ENTER_CONFIG_CHANGE);
}

hpm_stat_t mt9m114_set_brightness(camera_context_t *context, int level) /* -16 to +16 */
{
    int new_level = level * 2;

    if ((new_level < -32) || (32 < new_level)) {
        return status_fail;
    }

    if (mt9m114_write_register(context, MT9M114_VAR_UVC_BRIGHTNESS_CONTROL, 2, new_level + 55) != 0) {
        return status_fail;
    }

    return mt9m114_refresh(context);
}

hpm_stat_t mt9m114_start(camera_context_t *handle)
{
    return mt9m114_setstate(handle, MT9M114_SYS_STATE_START_STREAMING);
}

hpm_stat_t mt9m114_stop(camera_context_t *handle)
{
    return mt9m114_setstate(handle, MT9M114_SYS_STATE_ENTER_SUSPEND);
}

hpm_stat_t mt9m114_check_chip_id(camera_context_t *handle)
{
    hpm_stat_t status = status_success;
    uint16_t chip_id;

    status = mt9m114_read_register(handle, MT9M114_REG_CHIP_ID, 2u, &chip_id);
    if (status_success != status) {
        DEBUG_INFO("[ERROR] read MT9M114 chipid register failed %d\n", status);
        return status_fail;
    }
    if (MT9M114_CHIP_ID != chip_id) {
        DEBUG_INFO("[ERROR] chipid is %04x(expect %04x)\n", chip_id, MT9M114_CHIP_ID);
        return status_fail;
    }
    return status_success;
}

hpm_stat_t mt9m114_enable_mono(camera_context_t *handle, bool enable)
{
    uint16_t value = 0;
    mt9m114_read_register(handle, 0x332E, 2u, &value);
    if (enable)
        value = value | 0x0004;
    else
        value = value & 0xFFFB;
    mt9m114_write_register(handle, 0x332E, 2u, value);
    return 0;
}

hpm_stat_t mt9m114_init(camera_context_t *context, camera_config_t *camera_config)
{
    hpm_stat_t status = status_success;

    /* set init configs */
    DEBUG_INFO("[Camera]:set frame per sec ...\n");
    mt9m114_multiwrite(context, mt9m114_init_config, ARRAY_SIZE(mt9m114_init_config));

    /* Pixel format. */
    DEBUG_INFO("[Camera]:set format...\n");
    status = mt9m114_set_pixformat(context, camera_config->pixel_format);
    if (status_success != status) {
        DEBUG_INFO("[ERROR] set output format %d\n", status);
        ERROR_ACTION();
    }

    /* set cam port output control... */
    DEBUG_INFO("[Camera]:set cam port output control...\n");
    status = mt9m114_write_register(context, MT9M114_VAR_CAM_PORT_OUTPUT_CONTROL, 2, 0x8008);
    if (status_success != status) {
        DEBUG_INFO("[ERROR] set cam port output control... %d\n", status);
        ERROR_ACTION();
    }

    /* set resolution... */
    DEBUG_INFO("[Camera]:set resolution...\n");
    status = mt9m114_multiwrite(context, mt9m114_vga, ARRAY_SIZE(mt9m114_vga));
    if (status_success != status) {
        DEBUG_INFO("[ERROR] set resolution... %d\n", status);
        ERROR_ACTION();
    }

    /* set change command */
    DEBUG_INFO("[Camera]:set change command...\n");
    status = mt9m114_setstate(context, MT9M114_SYS_STATE_ENTER_CONFIG_CHANGE);
    if (status_success != status) {
        DEBUG_INFO("[ERROR] set change command... %d\n", status);
        ERROR_ACTION();
    }
    DEBUG_INFO("MT9M114 init done\n");
    return status;
}