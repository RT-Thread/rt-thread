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
#include <string.h>

#ifdef CONFIG_CLI_CMD_ENABLE
#include <cli.h>
#endif

#include "blog_type.h"
#include "blog_cfg.h"

#include <utils_log.h>

#if BLOG_TEST
#include <blog_testc.h>
#endif

/* every line log's buffer */
static char log_buf[BLOG_LINE_BUF_SIZE] = { 0 };

static int findch_sum(const char *str, char ch)
{
    int i = 0;
    int len = strlen(str);
    int ret = 0;

    for (i = 0; i < len; i++) {
        if (str[i] == ch) {
            ret++;
        }
    }

    return ret;
}
static int set_level(int argc, char **argv)
{
    extern char _ld_bl_static_blogcomponent_code_start;
    extern char _ld_bl_static_blogcomponent_code_end;
    extern char _ld_bl_static_blogfile_code_start;
    extern char _ld_bl_static_blogfile_code_end;
    extern char _ld_bl_static_blogpri_code_start;
    extern char _ld_bl_static_blogpri_code_end;

    blog_info_t *start;
    blog_info_t *end;
    blog_info_t *info;

    int          left;
    int          right;
    uint32_t     mid;
    int          cmp_val;
    blog_level_t level;

    int ch_sum;

    if (argc != 3) {
        __blog_printf("arg error.\r\n");
        return -1;
    }

    /* get component level */
    if (0 == strcmp(argv[1], "all")) {
        level = BLOG_LEVEL_ALL;
    } else if (0 == strcmp(argv[1], "debug")) {
        level = BLOG_LEVEL_DEBUG;
    } else if (0 == strcmp(argv[1], "info")) {
        level = BLOG_LEVEL_INFO;
    } else if (0 == strcmp(argv[1], "warn")) {
        level = BLOG_LEVEL_WARN;
    } else if (0 == strcmp(argv[1], "error")) {
        level = BLOG_LEVEL_ERROR;
    } else if (0 == strcmp(argv[1], "assert")) {
        level = BLOG_LEVEL_ASSERT;
    } else if (0 == strcmp(argv[1], "never")) {
        level = BLOG_LEVEL_NEVER;
    } else {
        __blog_printf("input level = %s not support.\r\n", argv[1]);
        return -1;
    }

    /* component_name.file_name.pri_name */
    ch_sum = findch_sum(argv[2], '.');

    if (0 == ch_sum) {
        start = (blog_info_t *)(&_ld_bl_static_blogcomponent_code_start);
        end = (blog_info_t *)(&_ld_bl_static_blogcomponent_code_end);
    } else if (1 == ch_sum) {
        start = (blog_info_t *)(&_ld_bl_static_blogfile_code_start);
        end = (blog_info_t *)(&_ld_bl_static_blogfile_code_end);
    } else if (2 == ch_sum) {
        start = (blog_info_t *)(&_ld_bl_static_blogpri_code_start);
        end = (blog_info_t *)(&_ld_bl_static_blogpri_code_end);
    } else {
        __blog_printf("input name = %s not support.\r\n", argv[2]);
        return -1;
    }

    left  = 0;
    right = end - start - 1;
    while (left <= right) {
        mid = (left + right) >> 1;
        cmp_val = strcmp(start[mid].name, argv[2]);
        if (cmp_val < 0) {
            left = mid + 1;
        } else if (cmp_val > 0) {
            right = mid - 1;
        } else {
            info = &start[mid];
            break;
        }
    }

    if (left > right) {
        __blog_printf("input name = %s not find.\r\n", argv[2]);
        return -1;
    }

    /* set level */
    *(info->level) = level;
    __blog_printf("set %s = %d\r\n", info->name, *(info->level));
    return 0;
}

void cmd_blog_set_level(char *buf, int len, int argc, char **argv)
{
    if (0 != set_level(argc, argv)) {
        __blog_printf("set blog error.\r\n");
    }
}

void cmd_blog_info_dump(char *buf, int len, int argc, char **argv)
{
    blog_info_t *info_c, *info_f, *info_p;
    char         name_buf[BLOG_NAMELEN_MAX] = {0};
    
    extern char _ld_bl_static_blogcomponent_code_start;
    extern char _ld_bl_static_blogcomponent_code_end;
    extern char _ld_bl_static_blogfile_code_start;
    extern char _ld_bl_static_blogfile_code_end;
    extern char _ld_bl_static_blogpri_code_start;
    extern char _ld_bl_static_blogpri_code_end;

    __blog_printf("blog code1 = %p - %p\r\n", &_ld_bl_static_blogcomponent_code_start, &_ld_bl_static_blogcomponent_code_end);
    __blog_printf("blog code2 = %p - %p\r\n", &_ld_bl_static_blogfile_code_start, &_ld_bl_static_blogfile_code_end);
    __blog_printf("blog code3 = %p - %p\r\n", &_ld_bl_static_blogpri_code_start, &_ld_bl_static_blogpri_code_end);

    for (info_c = (blog_info_t *)&_ld_bl_static_blogcomponent_code_start;
         (uint32_t)info_c < (uint32_t)&_ld_bl_static_blogcomponent_code_end; info_c++) {
        if (strlen(info_c->name) > BLOG_NAMELEN_MAX) {
            __blog_printf("name too long.\r\n");
            return;
        }
        if (name_buf[0] != 0) {
            if (0 == strcmp(name_buf, info_c->name)) {
#if BLOG_DUMP_DEDUPLICATE
              continue;
#endif              
            } else {
                memset(name_buf, 0, strlen(name_buf));
            }
        }
        
        __blog_printf("[%-48s] = [%d]\r\n", info_c->name, *(info_c->level));
        
        if ((name_buf[0] != 0) && (strcmp(info_c->name, name_buf) == 0)) {
            continue;
        }
        strcpy(name_buf, info_c->name);

        for (info_f = (blog_info_t *)&_ld_bl_static_blogfile_code_start;
            (uint32_t)info_f < (uint32_t)&_ld_bl_static_blogfile_code_end; info_f++) {

            if (strstr(info_f->name, info_c->name) == info_f->name) {

                __blog_printf("[%-48s] = [%d]\r\n", info_f->name, *(info_f->level));

                for (info_p = (blog_info_t *)&_ld_bl_static_blogpri_code_start;
                    (uint32_t)info_p < (uint32_t)&_ld_bl_static_blogpri_code_end; info_p++) {

                    if (strstr(info_p->name, info_f->name) == info_p->name) {
                        __blog_printf("[%-48s] = [%d]\r\n", info_p->name, *(info_p->level));
                    }
                }
            }
        }
    }
}

#if BLOG_TEST
void cmd_blog_test(char *buf, int len, int argc, char **argv)
{
    blog_testc_init();
}
#endif

static void blog_set_poweron_softlevel(void)
{
    blog_info_t *info;

    extern char _ld_bl_static_blogcomponent_code_start;
    extern char _ld_bl_static_blogcomponent_code_end;
    extern char _ld_bl_static_blogfile_code_start;
    extern char _ld_bl_static_blogfile_code_end;
    extern char _ld_bl_static_blogpri_code_start;
    extern char _ld_bl_static_blogpri_code_end;

    __blog_printf("\r\nblog init set power on level %d, %d, %d.\r\n", BLOG_POWERON_SOFTLEVEL_COMPONENT,
            BLOG_POWERON_SOFTLEVEL_FILE, BLOG_POWERON_SOFTLEVEL_PRI);
    for ( info = (blog_info_t *)&_ld_bl_static_blogcomponent_code_start;
          (uint32_t)info < (uint32_t)&_ld_bl_static_blogcomponent_code_end; info++ ) {
        *(info->level) = BLOG_POWERON_SOFTLEVEL_COMPONENT;
    }

    for ( info = (blog_info_t *)&_ld_bl_static_blogfile_code_start;
          (uint32_t)info < (uint32_t)&_ld_bl_static_blogfile_code_end; info++ ) {
        *(info->level) = BLOG_POWERON_SOFTLEVEL_FILE;
    }

    for ( info = (blog_info_t *)&_ld_bl_static_blogpri_code_start;
          (uint32_t)info < (uint32_t)&_ld_bl_static_blogpri_code_end; info++ ) {
        *(info->level) = BLOG_POWERON_SOFTLEVEL_PRI;
    }
}

/**
 * output log port interface
 *
 * @param log output of log
 * @param size log size
 */
void blog_port_output(const char *log, size_t size) {
    /* output to terminal */
    __blog_printf("%.*s", size, log);
    //TODO output to flash
}

/**
 * another copy string function
 *
 * @param cur_len current copied log length, max size is BLOG_LINE_BUF_SIZE
 * @param dst destination
 * @param src source
 *
 * @return copied length
 */
size_t blog_strcpy(size_t cur_len, char *dst, const char *src) {
    const char *src_old = src;

    if ((!dst) || (!src)) {
        __blog_printf("assert.\r\n");
        return 0;
    }

    while (*src != 0) {
        /* make sure destination has enough space */
        if (cur_len++ < BLOG_LINE_BUF_SIZE) {
            *dst++ = *src++;
        } else {
            break;
        }
    }
    return src - src_old;
}
/**
 * dump the hex format data to log
 *
 * @param name name for hex object, it will show on log header
 * @param width hex number for every line, such as: 16, 32
 * @param buf hex buffer
 * @param size buffer size
 */
void blog_hexdump_out(const char *name, uint8_t width, const uint8_t *buf, uint16_t size)
{
#define __is_print(ch)       ((unsigned int)((ch) - ' ') < 127u - ' ')

    uint16_t i, j;
    uint16_t log_len = 0;
    char dump_string[8] = {0};
    int fmt_result;

    /* lock output */

    for (i = 0; i < size; i += width) {
        /* package header */
        fmt_result = snprintf(log_buf, BLOG_LINE_BUF_SIZE, "[%s]: %04X-%04X: ", name, i, i + width - 1);
        /* calculate log length */
        if ((fmt_result > -1) && (fmt_result <= BLOG_LINE_BUF_SIZE)) {
            log_len = fmt_result;
        } else {
            log_len = BLOG_LINE_BUF_SIZE;
        }
        /* dump hex */
        for (j = 0; j < width; j++) {
            if (i + j < size) {
                snprintf(dump_string, sizeof(dump_string), "%02X ", buf[i + j]);
            } else {
                strncpy(dump_string, "   ", sizeof(dump_string));
            }
            log_len += blog_strcpy(log_len, log_buf + log_len, dump_string);
            if ((j + 1) % 8 == 0) {
                log_len += blog_strcpy(log_len, log_buf + log_len, " ");
            }
        }
        log_len += blog_strcpy(log_len, log_buf + log_len, "  ");
        /* dump char for hex */
        for (j = 0; j < width; j++) {
            if (i + j < size) {
                snprintf(dump_string, sizeof(dump_string), "%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
                log_len += blog_strcpy(log_len, log_buf + log_len, dump_string);
            }
        }
        /* overflow check and reserve some space for newline sign */
        if (log_len + strlen("\r\n") > BLOG_LINE_BUF_SIZE) {
            log_len = BLOG_LINE_BUF_SIZE - strlen("\r\n");
        }
        /* package newline sign */
        log_len += blog_strcpy(log_len, log_buf + log_len, "\r\n");

        /* do log output */
        blog_port_output(log_buf, log_len);
    }

    /* unlock output */
}

void blog_init(void)
{
    blog_set_poweron_softlevel();
}

#ifdef CONFIG_CLI_CMD_ENABLE
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "blogset", "blog pri set level", cmd_blog_set_level},
    { "blogdump", "blog info dump", cmd_blog_info_dump},
#if BLOG_TEST
    { "blogtest", "blog test", cmd_blog_test},
#endif
};
#endif

