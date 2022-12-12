/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-15 11:27:14
 * @LastEditTime: 2021-04-16 13:40:55
 * @Description:  This files is for
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef _FT_TRACE_H_
#define _FT_TRACE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_debug.h"

/* define debug log function */
#define FT_MEM_TRACE_ENABLED
#define FT_MEM_TRACE_TAG "FT_MEM"
#ifdef FT_MEM_TRACE_ENABLED
#define FT_MEM_TRACE(format, ...) FT_DEBUG_PRINT_I(FT_MEM_TRACE_TAG, format, ##__VA_ARGS__)
#else
#define FT_MEM_TRACE(format, ...)
#endif

#define FT_LOGIC_TRACE_ENABLED
#define FT_LOGIC_TRACE_TAG "FT_LOGIC"
#ifdef FT_LOGIC_TRACE_ENABLED
#define FT_LOGIC_TRACE(format, ...) FT_DEBUG_PRINT_I(FT_LOGIC_TRACE_TAG, format, ##__VA_ARGS__)
#define FT_MEM_TRACE_DUMP(buf, buflen, tag) dump_hex((buf), (buflen), (tag))
#else
#define FT_LOGIC_TRACE(format, ...)
#define FT_MEM_TRACE_DUMP(buf, buflen, tag)
#endif

#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
    void dump_hex(const u8 *ptr, u32 buflen, const char *tag);
    void Sdmmc_TraceHeapAlloc(const char *tag);

#ifdef __cplusplus
}
#endif

#endif
