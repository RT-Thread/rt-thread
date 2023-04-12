/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-11     Wayne        the first version
 */

#ifndef __FT5446_H__
#define __FT5446_H__

#include <rtdevice.h>

#define FT_REGITER_LEN           1
#define FT_MAX_TOUCH             5
#define FT5446_ADDRESS           0x38

#pragma anon_unions

typedef struct
{
    //03H
    union
    {
        uint8_t m_u8XH;
        struct
        {
            uint8_t u8X_11_8: 4;
            uint8_t : 2;
            uint8_t u8EvtFlag: 2;
#define FT_EVENTFLAG_PRESS_DOWN   0x0
#define FT_EVENTFLAG_LIFT_UP      0x1
#define FT_EVENTFLAG_CONTACT      0x2
#define FT_EVENTFLAG_NONE         0x3
        };
    };

    //04H
    union
    {
        uint8_t m_u8XL;
        struct
        {
            uint8_t u8X_7_0;
        };
    };

    //05H
    union
    {
        uint8_t m_u8YH;
        struct
        {
            uint8_t u8Y_11_8: 4;
            uint8_t u8TouchID: 4;     /* Touch ID of Touch Point, this value is 0x0F when the ID is invalid */
        };
    };

    //06H
    union
    {
        uint8_t m_u8YL;
        struct
        {
            uint8_t u8Y_7_0;
        };
    };

    //07H
    uint8_t m_u8Weight;  /* Touch pressure value */

    //08H
    union
    {
        uint8_t m_u8Misc;
        struct
        {
            uint8_t : 4;
            uint8_t u8TouchArea: 4;  /* Touch area value */
        };
    };

} S_FT_TP;

#pragma pack(push)
#pragma pack(4)

typedef struct
{
    union
    {
        uint8_t m_u8ModeSwitch;
#define FT_DEVICE_MODE_WORKING   0x0
#define FT_DEVICE_MODE_TEST      0x4

        struct
        {
            uint8_t : 4;
            uint8_t u8DevMode: 3;
            uint8_t : 1;
        };
    };

    uint8_t m_u8Guesture;
#define FT_GESTURE_ID_MOVE_UP       0x10
#define FT_GESTURE_ID_MOVE_RIGHT    0x14
#define FT_GESTURE_ID_MOVE_DOWN     0x18
#define FT_GESTURE_ID_MOVE_LEFT     0x1C
#define FT_GESTURE_ID_MOVE_IN       0x48
#define FT_GESTURE_ID_MOVE_OUT      0x49
#define FT_GESTURE_ID_MOVE_NONE     0x00

    union
    {
        uint8_t m_u8Status;

        struct
        {
            uint8_t u8TDStatus: 4;
            uint8_t : 4;
        };
    };

    S_FT_TP m_sTP[FT_MAX_TOUCH];

} S_FT_REGMAP;
#pragma pack(pop)

int rt_hw_ft5446_init(const char *name, struct rt_touch_config *cfg);

#endif /* __FT5446_H__ */
