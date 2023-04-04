/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-11     Wayne        the first version
 */

#ifndef __ST1663I_H__
#define __ST1663I_H__

#include <rtdevice.h>

#define ST_REGITER_LEN           1
#define ST_MAX_TOUCH             5
#define ST1663I_ADDRESS       0x55

#pragma anon_unions

typedef struct
{
    //012H*n+0 (n=0, 1, ...,4)
    union
    {
        uint8_t m_u8XY0_H;
        struct
        {
            uint8_t u8Y0_H: 3;
            uint8_t : 1;
            uint8_t u8X0_H: 3;
            uint8_t u8Valid: 1;
        };
    };

    //012H*n+1 (n=0, 1, ...,4)
    uint8_t m_u8X0_L;

    //012H*n+2 (n=0, 1, ...,4)
    uint8_t m_u8Y0_L;

    //012H*n+3 (n=0, 1, ...,4)
    uint8_t m_u8Z;

} S_ST_TP;


#pragma pack(push)
#pragma pack(4)

typedef struct
{
    union
    {
        uint8_t m_u8TouchInfo;
        struct
        {
            uint8_t u8Fingers: 4;
            uint8_t : 4;
        };
    };

    uint8_t m_u8Keys;

    S_ST_TP m_sTP[ST_MAX_TOUCH];

} S_ST_REGMAP;
#pragma pack(pop)

int rt_hw_st1663i_init(const char *name, struct rt_touch_config *cfg);

#endif /* __ST1663I_H__ */
