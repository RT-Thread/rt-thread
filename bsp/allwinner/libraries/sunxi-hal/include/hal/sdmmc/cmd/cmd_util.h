/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _CMD_UTIL_H_
#define _CMD_UTIL_H_

#include <stdlib.h>
#include <string.h>
#include "sys/param.h"
#include "cmd_defs.h"
#include "cmd_debug.h"
//#include "console/console.h"
#include "os.h"

#ifdef __cplusplus
extern "C" {
#endif

/* command format: <command-name> <arg>... */
struct cmd_data {
    char *name;
    enum cmd_status (*exec)(char *);
};

/* command2 format: <command-name>[ <arg>...] */
struct cmd2_data {
    char *name;
    int name_len;
    enum cmd_status (*exec)(char *);
};

enum cmd_status cmd_exec(char *cmd, const struct cmd_data *cdata, int count);
enum cmd_status cmd2_exec(char *cmd, const struct cmd2_data *cdata, int count);

int cmd_parse_argv(char *cmd, char *argv[], int size);

const char *cmd_get_status_desc(enum cmd_status status);
//const char *cmd_get_event_desc(enum cmd_event event);

int cmd_write(enum cmd_code_type type, int code, const char *fmt, ...);

#define cmd_write_respond(status, fmt, arg...) \
    cmd_write(CMD_CODE_TYEP_STATUS, (int)status, fmt, ##arg)

#define cmd_write_event(event, fmt, arg...) \
    cmd_write(CMD_CODE_TYEP_EVENT, (int)event, fmt, ##arg)

int32_t cmd_raw_mode_read(uint8_t *buf, int32_t size, uint32_t msec);
int32_t cmd_raw_mode_write(uint8_t *buf, int32_t size);

#define cmd_raw_mode_enable()   console_disable();
#define cmd_raw_mode_disable()  console_enable();


#define cmd_malloc(l)               malloc(l)
#define cmd_free(p)                 free(p)

#define cmd_memcpy(d, s, n)         memcpy(d, s, n)
#define cmd_memset(s, c, n)         memset(s, c, n)
#define cmd_memcmp(s1, s2, n)       memcmp(s1, s2, n)

#define cmd_strlen(s)               strlen(s)
#define cmd_strcmp(s1, s2)          strcmp(s1, s2)
#define cmd_strncmp(s1, s2, n)      strncmp(s1, s2, n)
#define cmd_strcasecmp(s1, s2)      strcasecmp(s1, s2)
#define cmd_strncasecmp(s1, s2, n)  strncasecmp(s1, s2, n)
#define cmd_strchr(s, c)            strchr(s, c)
#define cmd_strrchr(s, c)           strrchr(s, c)
#define cmd_strstr(s1, s2)          strstr(s1, s2)
#define cmd_strtol(s, p, b)         strtol(s, p, b)
#define cmd_strdup(s)               strdup(s)
#define cmd_strlcpy(d, s, n)        strlcpy(d, s, n)

#define cmd_atoi(s)                 atoi(s)
#define cmd_atol(s)                 atol(s)

#define cmd_sscanf(s, f, a...)      sscanf(s, f, ##a)
#define cmd_sprintf(s, f, a...)     sprintf(s, f, ##a)
#define cmd_snprintf(s, n, f, a...) snprintf(s, n, f, ##a)

#define cmd_nitems(a)               nitems(a)

#define cmd_msleep(msec)            OS_MSleep(msec)

#ifdef __cplusplus
}
#endif

#endif /* _CMD_UTIL_H_ */
