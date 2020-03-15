/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-04     ZeroFree     first implementation
 * 2019-06-14     armink       add easyflash v4.0 support
 */

#include <rtthread.h>

#ifdef BSP_USING_WIFI

#include <wlan_mgnt.h>
#include <wlan_cfg.h>
#include <wlan_prot.h>

#include <easyflash.h>
#include <fal.h>

#include <stdio.h>
#include <stdlib.h>

#if (EF_SW_VERSION_NUM < 0x40000)

static char *str_base64_encode_len(const void *src, char *out, int input_length);
static int   str_base64_decode(const char *data, int input_length, char *decoded_data);

static const unsigned char base64_table[65] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const char base64_decode_table[256] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x3F,
    0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
    0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static char *str_base64_encode_len(const void *src, char *out, int len)
{
    unsigned char *pos;
    const unsigned char *end, *in;
    size_t olen;

    olen = len * 4 / 3 + 4; /* 3-byte blocks to 4-byte */
    olen += olen / 72; /* line feeds */
    olen++; /* nul termination */

    end = (const unsigned char *)src + len;
    in = (const unsigned char *)src;
    pos = (unsigned char *)out;
    while (end - in >= 3)
    {
        *pos++ = base64_table[in[0] >> 2];
        *pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
        *pos++ = base64_table[((in[1] & 0x0f) << 2) | (in[2] >> 6)];
        *pos++ = base64_table[in[2] & 0x3f];
        in += 3;
    }

    if (end - in)
    {
        *pos++ = base64_table[in[0] >> 2];

        if (end - in == 1)
        {
            *pos++ = base64_table[(in[0] & 0x03) << 4];
            *pos++ = '=';
        }
        else
        {
            *pos++ = base64_table[((in[0] & 0x03) << 4) |
                                                  (in[1] >> 4)];
            *pos++ = base64_table[(in[1] & 0x0f) << 2];
        }
        *pos++ = '=';
    }

    *pos = '\0';
    return (char *)out;
}

/*
 * return: length, 0 is error.
 */
static int str_base64_decode(const char *data, int input_length, char *decoded_data)
{
    int out_len;
    int i, j;

    if (input_length % 4 != 0) return 0;

    out_len = input_length / 4 * 3;

    if (data[input_length - 1] == '=') out_len--;
    if (data[input_length - 2] == '=') out_len--;

    for (i = 0, j = 0; i < input_length;)
    {
        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : base64_decode_table[data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : base64_decode_table[data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : base64_decode_table[data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : base64_decode_table[data[i++]];

        uint32_t triple = (sextet_a << 3 * 6)
                          + (sextet_b << 2 * 6)
                          + (sextet_c << 1 * 6)
                          + (sextet_d << 0 * 6);

        if (j < out_len) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < out_len) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < out_len) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }

    return out_len;
}

static int read_cfg(void *buff, int len)
{
    char *wlan_cfg_info = RT_NULL;

    wlan_cfg_info = ef_get_env("wlan_cfg_info");
    if (wlan_cfg_info != RT_NULL)
    {
        str_base64_decode(wlan_cfg_info, rt_strlen(wlan_cfg_info), buff);
        return len;
    }
    else
    {
        return 0;
    }
}

static int get_len(void)
{
    int len;
    char *wlan_cfg_len = RT_NULL;

    wlan_cfg_len = ef_get_env("wlan_cfg_len");
    if (wlan_cfg_len == RT_NULL)
    {
        len = 0;
    }
    else
    {
        len = atoi(wlan_cfg_len);
    }

    return len;
}

static int write_cfg(void *buff, int len)
{
    char wlan_cfg_len[12] = {0};
    char *base64_buf = RT_NULL;

    base64_buf = rt_malloc(len * 4 / 3 + 4); /* 3-byte blocks to 4-byte, and the end. */
    if (base64_buf == RT_NULL)
    {
        return -RT_ENOMEM;
    }
    rt_memset(base64_buf, 0, len);

    /* interger to string */
    sprintf(wlan_cfg_len, "%d", len);
    /* set and store the wlan config lengths to Env */
    ef_set_env("wlan_cfg_len", wlan_cfg_len);
    str_base64_encode_len(buff, base64_buf, len);
    /* set and store the wlan config information to Env */
    ef_set_env("wlan_cfg_info", base64_buf);
    ef_save_env();
    rt_free(base64_buf);

    return len;
}

#else

static int read_cfg(void *buff, int len)
{
    size_t saved_len;

    ef_get_env_blob("wlan_cfg_info", buff, len, &saved_len);
    if (saved_len == 0)
    {
        return 0;
    }
    
    return len;
}

static int get_len(void)
{
    int len;
    size_t saved_len;

    ef_get_env_blob("wlan_cfg_len", &len, sizeof(len), &saved_len);
    if (saved_len == 0)
    {
        return 0;
    }

    return len;
}

static int write_cfg(void *buff, int len)
{
    /* set and store the wlan config lengths to Env */
    ef_set_env_blob("wlan_cfg_len", &len, sizeof(len));

    /* set and store the wlan config information to Env */
    ef_set_env_blob("wlan_cfg_info", buff, len);

    return len;
}

#endif /* (EF_SW_VERSION_NUM < 0x40000) */

static const struct rt_wlan_cfg_ops ops =
{
    read_cfg,
    get_len,
    write_cfg
};

void wlan_autoconnect_init(void)
{
    fal_init();
    easyflash_init();

    rt_wlan_cfg_set_ops(&ops);
    rt_wlan_cfg_cache_refresh();
}

#endif
