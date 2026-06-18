/*
 * Copyright (C) 2022, Phytium Technology Co., Ltd.   All Rights Reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 * FilePath: helper.c
 * Date: 2022-01-03 13:04:02
 * LastEditTime: 2022-01-06 21:51:08
 * Description:  This file is for helper
 *
 * Modify History:
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 * 1.0	 huanghe	2022/03/06   first release
 */

#include <metal/sys.h>
#include "platform_info.h"
#include "stdio.h"
#include "fcache.h"

static void system_metal_logger(enum metal_log_level level,
                const char *format, ...)
{
    char msg[1024];
    va_list args;
    static const char * const level_strs[] = {
        "metal: emergency: ",
        "metal: alert:     ",
        "metal: critical:  ",
        "metal: error:     ",
        "metal: warning:   ",
        "metal: notice:    ",
        "metal: info:      ",
        "metal: debug:     ",
    };

    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    if (level <= METAL_LOG_EMERGENCY || level > METAL_LOG_DEBUG)
        level = METAL_LOG_EMERGENCY;

    printf("%s%s", level_strs[level], msg);
}

/* Main hw machinery initialization entry point, called from main()*/
/* return 0 on success */
int init_system(void)
{
    int ret;
    struct metal_init_params metal_param = {
        .log_handler = system_metal_logger,
        .log_level = METAL_LOG_INFO,
    };

    /* Low level abstraction layer for openamp initialization */
    ret = metal_init(&metal_param);
    return ret;
}

void cleanup_system(void)
{
    metal_finish();
    __asm_invalidate_icache_all();
}
