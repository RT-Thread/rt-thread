/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#include "utils_log.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ONE_LINE_MAX_NUM        (50)/* for print_buf log length */
#define MODULE_LOG_LOCK_LOCK    /* reserved */
#define MODULE_LOG_LOCK_UNLOCK  /* reserved */
static char log_buf[512];
int log_buf_out(const char *file, int line, const void *inbuf, int len, LOG_BUF_OUT_DATA_TYPE_T type)
{
    char *buf = (char *)inbuf;
    char *pbuffer = NULL;

#if defined(BL702) || defined(BL702L)
    pbuffer = (char *)pvPortMalloc(sizeof(log_buf));
    if(pbuffer == NULL){
        return -1;
    }
#else
    pbuffer = (char *)log_buf;
#endif
    int m = 0, n = 0;
    int j = 0, k = 0, tmp = 0;

    MODULE_LOG_LOCK_LOCK;

    tmp = (sizeof(log_buf))/3;/* 数组最大长度 */
    if ((ONE_LINE_MAX_NUM > tmp) || (len < 1))
    {
        MODULE_LOG_LOCK_UNLOCK;
        return -1;
    }

    m = len / ONE_LINE_MAX_NUM;
    n = len % ONE_LINE_MAX_NUM;
    if (n > 0) {
        m++;
    }


    if (n > 0) {
        /* 非整数倍 */
        for (k = 0; k < m; k++) {
            if ((k+1) == m) {
                /* 最后一帧数据 */
                tmp = 0;
                for (j = 0; j < n; j++) {
                    switch (type) {
                        case LOG_BUF_OUT_DATA_TYPE_INT8:
                        {
                            tmp += sprintf(pbuffer + tmp, "%3d ", (int8_t)buf[k*ONE_LINE_MAX_NUM+j]);
                        }
                        break;
                        case LOG_BUF_OUT_DATA_TYPE_UNT8:
                        {
                            tmp += sprintf(pbuffer + tmp, "%3u ", (uint8_t)buf[k*ONE_LINE_MAX_NUM+j]);
                        }
                        break;
                        case LOG_BUF_OUT_DATA_TYPE_HEX:
                        default:
                        {
                            tmp += sprintf(pbuffer + tmp, "%02x ", (uint8_t)buf[k*ONE_LINE_MAX_NUM+j]);
                        }
                    }
                }
                log_buf_pri(file, line, "%.*s\r\n", tmp, pbuffer);
            } else {
                tmp = 0;
                for (j = 0; j < ONE_LINE_MAX_NUM; j++) {
                    switch (type) {
                        case LOG_BUF_OUT_DATA_TYPE_INT8:
                        {
                            tmp += sprintf(pbuffer + tmp, "%3d ", (int8_t)buf[k*ONE_LINE_MAX_NUM+j]);
                        }
                        break;
                        case LOG_BUF_OUT_DATA_TYPE_UNT8:
                        {
                            tmp += sprintf(pbuffer + tmp, "%3u ", (uint8_t)buf[k*ONE_LINE_MAX_NUM+j]);
                        }
                        break;
                        case LOG_BUF_OUT_DATA_TYPE_HEX:
                        default:
                        {
                            tmp += sprintf(pbuffer + tmp, "%02x ", (uint8_t)buf[k*ONE_LINE_MAX_NUM+j]);
                        }
                    }
                }
                log_buf_pri(file, line, "%.*s\r\n", tmp, pbuffer);
            }
        }
    } else {
        /* 整数倍 */
        for (k = 0; k < m; k++) {
            tmp = 0;
            for (j = 0; j < ONE_LINE_MAX_NUM; j++) {
                switch (type) {
                    case LOG_BUF_OUT_DATA_TYPE_INT8:
                    {
                        tmp += sprintf(pbuffer + tmp, "%3d ", (int8_t)buf[k*ONE_LINE_MAX_NUM+j]);
                    }
                    break;
                    case LOG_BUF_OUT_DATA_TYPE_UNT8:
                    {
                        tmp += sprintf(pbuffer + tmp, "%3u ", (uint8_t)buf[k*ONE_LINE_MAX_NUM+j]);
                    }
                    break;
                    case LOG_BUF_OUT_DATA_TYPE_HEX:
                    default:
                    {
                        tmp += sprintf(pbuffer + tmp, "%02x ", (uint8_t)buf[k*ONE_LINE_MAX_NUM+j]);
                    }
                }
            }
            log_buf_pri(file, line, "%.*s\r\n", tmp, pbuffer);
        }
    }

    MODULE_LOG_LOCK_UNLOCK;

#if defined(BL702) || defined(BL702L)
    vPortFree(pbuffer);
#endif

    return 0;
}

extern void vprint(const char *fmt, va_list argp);

extern volatile bool sys_log_all_enable;

void bl_printk(const char *format, ...)
{
    va_list args;

    if (sys_log_all_enable) {
        /* args point to the first variable parameter */
        va_start(args, format);

        /* You can add your code under here. */
        vprint(format, args);

        va_end(args);
    }
}

#ifdef __cplusplus
}
#endif

