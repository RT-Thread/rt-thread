/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fdcdp_param.h
 * Date: 2022-09-05 17:31:47
 * LastEditTime: 2022-09-05 17:31:47
 * Description:  This file is for providing some general config and params of dc and dp
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------  -------- --------------------------------------
 *  1.0  Wangzq     2022/12/20   Modify the format and establish the version
 */

#ifndef FDCDP_PARAM_H
#define FDCDP_PARAM_H

#include "ftypes.h"
#include "fparameters.h"
#include "ferror_code.h"

#define FMEDIA_DEFAULT_PARAM_ERR FT_MAKE_ERRCODE(ErrModBsp, ErrBspMEDIA, 1)
#define FMEDIA_ERR_PIXEL FT_MAKE_ERRCODE(ErrModBsp, ErrBspMEDIA, 3)
#define FMEDIA_ERR_EDID FT_MAKE_ERRCODE(ErrModBsp, ErrBspMEDIA, 4)
#define FMEDIA_ERR_HPD_DISCONNECTED  FT_MAKE_ERRCODE(ErrModBsp, ErrBspMEDIA, 5)
#define FMEDIA_AUX_CONNECT_FAILED FT_MAKE_ERRCODE(ErrModBsp, ErrBspMEDIA, 7)
#define FMEDIA_TRAIN_TIME_ERR FT_MAKE_ERRCODE(ErrModBsp, ErrBspMEDIA, 8)
#define FMEDIA_REACH_MAX_VOLTAGE FT_MAKE_ERRCODE(ErrModBsp, ErrBspMEDIA, 9)

typedef enum
{
    FDCDP_DISPLAY_ID_640_480 = 0,
    FDCDP_DISPLAY_ID_800_600,
    FDCDP_DISPLAY_ID_1024_768,
    FDCDP_DISPLAY_ID_1280_720,
    FDCDP_DISPLAY_ID_1366_768,
    FDCDP_DISPLAY_ID_1920_1080,
    FDCDP_DISPLAY_ID_1600_1200,
    FDCDP_DISPLAY_ID_1280_800,
    FDCDP_DISPLAY_ID_800_480,
    FDCDP_DISPLAY_ID_1280_768,
    FDCDP_DISPLAY_ID_1280_1024,
    FDCDP_DISPLAY_ID_MAX_NUM

} FDcDpDisplayId;
typedef struct
{
    u32 width;
    u32 height;
    u32 color_depth;  /*  value follow the  DISPLAY_REFRESH_RATE_XX */
    u32 refresh_rate; /*  value follow the  DISPLAY_COLOR_DEPTH_XX */
    FDcDpDisplayId id;
} FDcDpDisplaySetting;


#endif