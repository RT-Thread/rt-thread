/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-25     armink       the first version
 */

#include <stdarg.h>
#include "ulog.h"
#include "rthw.h"

#ifdef ULOG_USING_SYSLOG
#include <syslog.h>
#endif

#ifdef ULOG_OUTPUT_FLOAT
#include <stdio.h>
#endif

#ifdef ULOG_TIME_USING_TIMESTAMP
#include <sys/time.h>
#endif

#ifdef ULOG_USING_ASYNC_OUTPUT
#include <rtdevice.h>
#endif

#ifdef RT_USING_ULOG

/* the number which is max stored line logs */
#ifndef ULOG_ASYNC_OUTPUT_STORE_LINES
#define ULOG_ASYNC_OUTPUT_STORE_LINES  (ULOG_ASYNC_OUTPUT_BUF_SIZE * 3 / 2 / ULOG_LINE_BUF_SIZE)
#endif

#ifdef ULOG_USING_COLOR
/**
 * CSI(Control Sequence Introducer/Initiator) sign
 * more information on https://en.wikipedia.org/wiki/ANSI_escape_code
 */
#define CSI_START                      "\033["
#define CSI_END                        "\033[0m"
/* output log front color */
#define F_BLACK                        "30m"
#define F_RED                          "31m"
#define F_GREEN                        "32m"
#define F_YELLOW                       "33m"
#define F_BLUE                         "34m"
#define F_MAGENTA                      "35m"
#define F_CYAN                         "36m"
#define F_WHITE                        "37m"

/* output log default color definition */
#ifndef ULOG_COLOR_DEBUG
#define ULOG_COLOR_DEBUG               NULL
#endif
#ifndef ULOG_COLOR_INFO
#define ULOG_COLOR_INFO                (F_GREEN)
#endif
#ifndef ULOG_COLOR_WARN
#define ULOG_COLOR_WARN                (F_YELLOW)
#endif
#ifndef ULOG_COLOR_ERROR
#define ULOG_COLOR_ERROR               (F_RED)
#endif
#ifndef ULOG_COLOR_ASSERT
#define ULOG_COLOR_ASSERT              (F_MAGENTA)
#endif
#endif /* ULOG_USING_COLOR */

#if ULOG_LINE_BUF_SIZE < 80
#error "the log line buffer size must more than 80"
#endif

struct rt_ulog
{
    rt_bool_t init_ok;
    struct rt_mutex output_locker;
    /* all backends */
    rt_slist_t backend_list;
    /* the thread log's line buffer */
    char log_buf_th[ULOG_LINE_BUF_SIZE + 1];

#ifdef ULOG_USING_ISR_LOG
    /* the ISR log's line buffer */
    rt_base_t output_locker_isr_lvl;
    char log_buf_isr[ULOG_LINE_BUF_SIZE + 1];
#endif /* ULOG_USING_ISR_LOG */

#ifdef ULOG_USING_ASYNC_OUTPUT
    rt_rbb_t async_rbb;
    rt_thread_t async_th;
    struct rt_semaphore async_notice;
#endif

#ifdef ULOG_USING_FILTER
    struct
    {
        /* all tag's level filter */
        rt_slist_t tag_lvl_list;
        /* global filter level, tag and keyword */
        rt_uint32_t level;
        char tag[ULOG_FILTER_TAG_MAX_LEN + 1];
        char keyword[ULOG_FILTER_KW_MAX_LEN + 1];
    } filter;
#endif /* ULOG_USING_FILTER */
};

/* level output info */
static const char * const level_output_info[] =
{
        "A/",
        NULL,
        NULL,
        "E/",
        "W/",
        NULL,
        "I/",
        "D/",
};

#ifdef ULOG_USING_COLOR
/* color output info */
static const char * const color_output_info[] =
{
        ULOG_COLOR_ASSERT,
        NULL,
        NULL,
        ULOG_COLOR_ERROR,
        ULOG_COLOR_WARN,
        NULL,
        ULOG_COLOR_INFO,
        ULOG_COLOR_DEBUG,
};
#endif /* ULOG_USING_COLOR */

/* ulog local object */
static struct rt_ulog ulog = { 0 };

size_t ulog_strcpy(size_t cur_len, char *dst, const char *src)
{
    const char *src_old = src;

    RT_ASSERT(dst);
    RT_ASSERT(src);

    while (*src != 0)
    {
        /* make sure destination has enough space */
        if (cur_len++ < ULOG_LINE_BUF_SIZE)
        {
            *dst++ = *src++;
        }
        else
        {
            break;
        }
    }
    return src - src_old;
}

size_t ulog_ultoa(char *s, unsigned long int n)
{
    size_t i = 0, j = 0, len = 0;
    char swap;

    do
    {
        s[len++] = n % 10 + '0';
    } while (n /= 10);
    s[len] = '\0';
    /* reverse string */
    for (i = 0, j = len - 1; i < j; ++i, --j)
    {
        swap = s[i];
        s[i] = s[j];
        s[j] = swap;
    }
    return len;
}

static void output_unlock(void)
{
    /* is in thread context */
    if (rt_interrupt_get_nest() == 0)
    {
        rt_mutex_release(&ulog.output_locker);
    }
    else
    {
#ifdef ULOG_USING_ISR_LOG
        rt_hw_interrupt_enable(ulog.output_locker_isr_lvl);
#endif
    }
}

static void output_lock(void)
{
    /* is in thread context */
    if (rt_interrupt_get_nest() == 0)
    {
        rt_mutex_take(&ulog.output_locker, RT_WAITING_FOREVER);
    }
    else
    {
#ifdef ULOG_USING_ISR_LOG
        ulog.output_locker_isr_lvl = rt_hw_interrupt_disable();
#endif
    }
}

static char *get_log_buf(void)
{
    /* is in thread context */
    if (rt_interrupt_get_nest() == 0)
    {
        return ulog.log_buf_th;
    }
    else
    {
#ifdef ULOG_USING_ISR_LOG
        return ulog.log_buf_isr;
#else
        rt_kprintf("Error: Current mode not supported run in ISR. Please enable ULOG_USING_ISR_LOG.\n");
        return NULL;
#endif
    }
}

RT_WEAK rt_size_t ulog_formater(char *log_buf, rt_uint32_t level, const char *tag, rt_bool_t newline,
        const char *format, va_list args)
{
    /* the caller has locker, so it can use static variable for reduce stack usage */
    static rt_size_t log_len, newline_len;
    static int fmt_result;

    RT_ASSERT(log_buf);
    RT_ASSERT(level <= LOG_LVL_DBG);
    RT_ASSERT(tag);
    RT_ASSERT(format);

    log_len = 0;
    newline_len = rt_strlen(ULOG_NEWLINE_SIGN);

#ifdef ULOG_USING_COLOR
    /* add CSI start sign and color info */
    if (color_output_info[level])
    {
        log_len += ulog_strcpy(log_len, log_buf + log_len, CSI_START);
        log_len += ulog_strcpy(log_len, log_buf + log_len, color_output_info[level]);
    }
#endif /* ULOG_USING_COLOR */

#ifdef ULOG_OUTPUT_TIME
    /* add time info */
    {
#ifdef ULOG_TIME_USING_TIMESTAMP
        static time_t now;
        static struct tm *tm, tm_tmp;

        now = time(NULL);
        tm = gmtime_r(&now, &tm_tmp);

#ifdef RT_USING_SOFT_RTC
        rt_snprintf(log_buf + log_len, ULOG_LINE_BUF_SIZE - log_len, "%02d-%02d %02d:%02d:%02d.%03d", tm->tm_mon + 1,
                tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, rt_tick_get() % 1000);
#else
        rt_snprintf(log_buf + log_len, ULOG_LINE_BUF_SIZE - log_len, "%02d-%02d %02d:%02d:%02d", tm->tm_mon + 1,
                tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
#endif /* RT_USING_SOFT_RTC */

#else
        static rt_size_t tick_len = 0;

        log_buf[log_len] = '[';
        tick_len = ulog_ultoa(log_buf + log_len + 1, rt_tick_get());
        log_buf[log_len + 1 + tick_len] = ']';
        log_buf[log_len + 1 + tick_len + 1] = '\0';
#endif /* ULOG_TIME_USING_TIMESTAMP */

        log_len += rt_strlen(log_buf + log_len);
    }
#endif /* ULOG_OUTPUT_TIME */

#ifdef ULOG_OUTPUT_LEVEL

#ifdef ULOG_OUTPUT_TIME
    log_len += ulog_strcpy(log_len, log_buf + log_len, " ");
#endif

    /* add level info */
    log_len += ulog_strcpy(log_len, log_buf + log_len, level_output_info[level]);
#endif /* ULOG_OUTPUT_LEVEL */

#ifdef ULOG_OUTPUT_TAG

#if !defined(ULOG_OUTPUT_LEVEL) && defined(ULOG_OUTPUT_TIME)
    log_len += ulog_strcpy(log_len, log_buf + log_len, " ");
#endif

    /* add tag info */
    log_len += ulog_strcpy(log_len, log_buf + log_len, tag);
#endif /* ULOG_OUTPUT_TAG */

#ifdef ULOG_OUTPUT_THREAD_NAME
    /* add thread info */
    {

#if defined(ULOG_OUTPUT_TIME) || defined(ULOG_OUTPUT_LEVEL) || defined(ULOG_OUTPUT_TAG)
        log_len += ulog_strcpy(log_len, log_buf + log_len, " ");
#endif

        /* is not in interrupt context */
        if (rt_interrupt_get_nest() == 0)
        {
            rt_size_t name_len = rt_strnlen(rt_thread_self()->name, RT_NAME_MAX);

            rt_strncpy(log_buf + log_len, rt_thread_self()->name, name_len);
            log_len += name_len;
        }
        else
        {
            log_len += ulog_strcpy(log_len, log_buf + log_len, "ISR");
        }
    }
#endif /* ULOG_OUTPUT_THREAD_NAME */

    log_len += ulog_strcpy(log_len, log_buf + log_len, ": ");

#ifdef ULOG_OUTPUT_FLOAT
    fmt_result = vsnprintf(log_buf + log_len, ULOG_LINE_BUF_SIZE - log_len, format, args);
#else
    fmt_result = rt_vsnprintf(log_buf + log_len, ULOG_LINE_BUF_SIZE - log_len, format, args);
#endif /* ULOG_OUTPUT_FLOAT */

    /* calculate log length */
    if ((log_len + fmt_result <= ULOG_LINE_BUF_SIZE) && (fmt_result > -1))
    {
        log_len += fmt_result;
    }
    else
    {
        /* using max length */
        log_len = ULOG_LINE_BUF_SIZE;
    }

    /* overflow check and reserve some space for CSI end sign and newline sign */
#ifdef ULOG_USING_COLOR
    if (log_len + (sizeof(CSI_END) - 1) + newline_len > ULOG_LINE_BUF_SIZE)
    {
        /* using max length */
        log_len = ULOG_LINE_BUF_SIZE;
        /* reserve some space for CSI end sign */
        log_len -= (sizeof(CSI_END) - 1);
#else
    if (log_len + newline_len > ULOG_LINE_BUF_SIZE)
    {
        /* using max length */
        log_len = ULOG_LINE_BUF_SIZE;
#endif /* ULOG_USING_COLOR */
        /* reserve some space for newline sign */
        log_len -= newline_len;
    }

    /* package newline sign */
    if (newline)
    {
        log_len += ulog_strcpy(log_len, log_buf + log_len, ULOG_NEWLINE_SIGN);
    }

#ifdef ULOG_USING_COLOR
    /* add CSI end sign  */
    if (color_output_info[level])
    {
        log_len += ulog_strcpy(log_len, log_buf + log_len, CSI_END);
    }
#endif /* ULOG_USING_COLOR */

    return log_len;
}

void ulog_output_to_all_backend(rt_uint32_t level, const char *tag, rt_bool_t is_raw, const char *log, rt_size_t size)
{
    rt_slist_t *node;
    ulog_backend_t backend;

    if (!ulog.init_ok)
        return;

    /* output for all backends */
    for (node = rt_slist_first(&ulog.backend_list); node; node = rt_slist_next(node))
    {
        backend = rt_slist_entry(node, struct ulog_backend, list);
#if !defined(ULOG_USING_COLOR) || defined(ULOG_USING_SYSLOG)
        backend->output(backend, level, tag, is_raw, log, size);
#else
        if (backend->support_color || is_raw)
        {
            backend->output(backend, level, tag, is_raw, log, size);
        }
        else
        {
            /* recalculate the log start address and log size when backend not supported color */
            rt_size_t color_info_len = rt_strlen(color_output_info[level]), output_size = size;
            if (color_info_len)
            {
                rt_size_t color_hdr_len = rt_strlen(CSI_START) + color_info_len;

                log += color_hdr_len;
                output_size -= (color_hdr_len + (sizeof(CSI_END) - 1));
            }
            backend->output(backend, level, tag, is_raw, log, output_size);
        }
#endif /* !defined(ULOG_USING_COLOR) || defined(ULOG_USING_SYSLOG) */
    }
}

static void do_output(rt_uint32_t level, const char *tag, rt_bool_t is_raw, const char *log_buf, rt_size_t log_len)
{
#ifdef ULOG_USING_ASYNC_OUTPUT
    rt_rbb_blk_t log_blk;
    ulog_frame_t log_frame;

    /* allocate log frame */
    log_blk = rt_rbb_blk_alloc(ulog.async_rbb, RT_ALIGN(sizeof(struct ulog_frame) + log_len, RT_ALIGN_SIZE));
    if (log_blk)
    {
        /* package the log frame */
        log_frame = (ulog_frame_t) log_blk->buf;
        log_frame->magic = ULOG_FRAME_MAGIC;
        log_frame->is_raw = is_raw;
        log_frame->level = level;
        log_frame->log_len = log_len;
        log_frame->tag = tag;
        log_frame->log = (const char *)log_blk->buf + sizeof(struct ulog_frame);
        /* copy log data */
        rt_memcpy(log_blk->buf + sizeof(struct ulog_frame), log_buf, log_len);
        /* put the block */
        rt_rbb_blk_put(log_blk);
        /* send a notice */
        rt_sem_release(&ulog.async_notice);
    }
    else
    {
        static rt_bool_t already_output = RT_FALSE;
        if (already_output == RT_FALSE)
        {
            rt_kprintf("Warning: There is no enough buffer for saving async log,"
                    " please increase the ULOG_ASYNC_OUTPUT_BUF_SIZE option.\n");
            already_output = RT_TRUE;
        }
    }
#else
    /* is in thread context */
    if (rt_interrupt_get_nest() == 0)
    {
        /* output to all backends */
        ulog_output_to_all_backend(level, tag, is_raw, log_buf, log_len);
    }
    else
    {
#ifdef ULOG_BACKEND_USING_CONSOLE
        /* We can't ensure that all backends support ISR context output.
         * So only using rt_kprintf when context is ISR */
        extern void ulog_console_backend_output(struct ulog_backend *backend, rt_uint32_t level, const char *tag,
                rt_bool_t is_raw, const char *log, size_t len);
        ulog_console_backend_output(NULL, level, tag, is_raw, log_buf, log_len);
#endif /* ULOG_BACKEND_USING_CONSOLE */
    }
#endif /* ULOG_USING_ASYNC_OUTPUT */
}

/**
 * output the log by variable argument list
 *
 * @param level level
 * @param tag tag
 * @param newline has_newline
 * @param format output format
 * @param args variable argument list
 */
void ulog_voutput(rt_uint32_t level, const char *tag, rt_bool_t newline, const char *format, va_list args)
{
    char *log_buf = NULL;
    rt_size_t log_len = 0;

#ifndef ULOG_USING_SYSLOG
    RT_ASSERT(level <= LOG_LVL_DBG);
#else
    RT_ASSERT(LOG_PRI(level) <= LOG_DEBUG);
#endif /* ULOG_USING_SYSLOG */

    RT_ASSERT(tag);
    RT_ASSERT(format);

    if (!ulog.init_ok)
    {
        return;
    }

#ifdef ULOG_USING_FILTER
    /* level filter */
#ifndef ULOG_USING_SYSLOG
    if (level > ulog.filter.level || level > ulog_tag_lvl_filter_get(tag))
    {
        return;
    }
#else
    if (((LOG_MASK(LOG_PRI(level)) & ulog.filter.level) == 0)
            || ((LOG_MASK(LOG_PRI(level)) & ulog_tag_lvl_filter_get(tag)) == 0))
    {
        return;
    }
#endif /* ULOG_USING_SYSLOG */
    else if (!rt_strstr(tag, ulog.filter.tag))
    {
        /* tag filter */
        return;
    }
#endif /* ULOG_USING_FILTER */

    /* get log buffer */
    log_buf = get_log_buf();

    /* lock output */
    output_lock();

#ifndef ULOG_USING_SYSLOG
    log_len = ulog_formater(log_buf, level, tag, newline, format, args);
#else
    extern rt_size_t syslog_formater(char *log_buf, rt_uint8_t level, const char *tag, rt_bool_t newline, const char *format, va_list args);
    log_len = syslog_formater(log_buf, level, tag, newline, format, args);
#endif /* ULOG_USING_SYSLOG */

#ifdef ULOG_USING_FILTER
    /* keyword filter */
    if (ulog.filter.keyword[0] != '\0')
    {
        /* add string end sign */
        log_buf[log_len] = '\0';
        /* find the keyword */
        if (!rt_strstr(log_buf, ulog.filter.keyword))
        {
            /* unlock output */
            output_unlock();
            return;
        }
    }
#endif /* ULOG_USING_FILTER */
    /* do log output */
    do_output(level, tag, RT_FALSE, log_buf, log_len);

    /* unlock output */
    output_unlock();
}

/**
 * output the log
 *
 * @param level level
 * @param tag tag
 * @param newline has newline
 * @param format output format
 * @param ... args
 */
void ulog_output(rt_uint32_t level, const char *tag, rt_bool_t newline, const char *format, ...)
{
    va_list args;

    /* args point to the first variable parameter */
    va_start(args, format);

    ulog_voutput(level, tag, newline, format, args);

    va_end(args);
}

/**
 * output RAW string format log
 *
 * @param format output format
 * @param ... args
 */
void ulog_raw(const char *format, ...)
{
    rt_size_t log_len = 0;
    char *log_buf = NULL;
    va_list args;
    int fmt_result;

    RT_ASSERT(ulog.init_ok);

    /* get log buffer */
    log_buf = get_log_buf();

    /* lock output */
    output_lock();
    /* args point to the first variable parameter */
    va_start(args, format);

#ifdef ULOG_OUTPUT_FLOAT
    fmt_result = vsnprintf(log_buf, ULOG_LINE_BUF_SIZE, format, args);
#else
    fmt_result = rt_vsnprintf(log_buf, ULOG_LINE_BUF_SIZE, format, args);
#endif /* ULOG_OUTPUT_FLOAT */

    va_end(args);

    /* calculate log length */
    if ((fmt_result > -1) && (fmt_result <= ULOG_LINE_BUF_SIZE))
    {
        log_len = fmt_result;
    }
    else
    {
        log_len = ULOG_LINE_BUF_SIZE;
    }

    /* do log output */
    do_output(LOG_LVL_DBG, NULL, RT_TRUE, log_buf, log_len);

    /* unlock output */
    output_unlock();
}

/**
 * dump the hex format data to log
 *
 * @param tag name for hex object, it will show on log header
 * @param width hex number for every line, such as: 16, 32
 * @param buf hex buffer
 * @param size buffer size
 */
void ulog_hexdump(const char *tag, rt_size_t width, rt_uint8_t *buf, rt_size_t size)
{
#define __is_print(ch)       ((unsigned int)((ch) - ' ') < 127u - ' ')

    rt_size_t i, j;
    rt_size_t log_len = 0, name_len = rt_strlen(tag);
    char *log_buf = NULL, dump_string[8];
    int fmt_result;

    RT_ASSERT(ulog.init_ok);

#ifdef ULOG_USING_FILTER
    /* level filter */
#ifndef ULOG_USING_SYSLOG
    if (LOG_LVL_DBG > ulog.filter.level || LOG_LVL_DBG > ulog_tag_lvl_filter_get(tag))
    {
        return;
    }
#else
    if ((LOG_MASK(LOG_DEBUG) & ulog.filter.level) == 0)
    {
        return;
    }
#endif /* ULOG_USING_SYSLOG */
    else if (!rt_strstr(tag, ulog.filter.tag))
    {
        /* tag filter */
        return;
    }
#endif /* ULOG_USING_FILTER */

    /* get log buffer */
    log_buf = get_log_buf();

    /* lock output */
    output_lock();

    for (i = 0, log_len = 0; i < size; i += width)
    {
        /* package header */
        if (i == 0)
        {
            log_len += ulog_strcpy(log_len, log_buf + log_len, "D/HEX ");
            log_len += ulog_strcpy(log_len, log_buf + log_len, tag);
            log_len += ulog_strcpy(log_len, log_buf + log_len, ": ");
        }
        else
        {
            log_len = 6 + name_len + 2;
            rt_memset(log_buf, ' ', log_len);
        }
        fmt_result = rt_snprintf(log_buf + log_len, ULOG_LINE_BUF_SIZE, "%04X-%04X: ", i, i + width - 1);
        /* calculate log length */
        if ((fmt_result > -1) && (fmt_result <= ULOG_LINE_BUF_SIZE))
        {
            log_len += fmt_result;
        }
        else
        {
            log_len = ULOG_LINE_BUF_SIZE;
        }
        /* dump hex */
        for (j = 0; j < width; j++)
        {
            if (i + j < size)
            {
                rt_snprintf(dump_string, sizeof(dump_string), "%02X ", buf[i + j]);
            }
            else
            {
                rt_strncpy(dump_string, "   ", sizeof(dump_string));
            }
            log_len += ulog_strcpy(log_len, log_buf + log_len, dump_string);
            if ((j + 1) % 8 == 0)
            {
                log_len += ulog_strcpy(log_len, log_buf + log_len, " ");
            }
        }
        log_len += ulog_strcpy(log_len, log_buf + log_len, "  ");
        /* dump char for hex */
        for (j = 0; j < width; j++)
        {
            if (i + j < size)
            {
                rt_snprintf(dump_string, sizeof(dump_string), "%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
                log_len += ulog_strcpy(log_len, log_buf + log_len, dump_string);
            }
        }
        /* overflow check and reserve some space for newline sign */
        if (log_len + rt_strlen(ULOG_NEWLINE_SIGN) > ULOG_LINE_BUF_SIZE)
        {
            log_len = ULOG_LINE_BUF_SIZE - rt_strlen(ULOG_NEWLINE_SIGN);
        }
        /* package newline sign */
        log_len += ulog_strcpy(log_len, log_buf + log_len, ULOG_NEWLINE_SIGN);
        /*add string end sign*/
        log_buf[log_len] = '\0';
        /* do log output */
        do_output(LOG_LVL_DBG, NULL, RT_TRUE, log_buf, log_len);
    }
    /* unlock output */
    output_unlock();
}

#ifdef ULOG_USING_FILTER
/**
 * Set the filter's level by different tag.
 * The log on this tag which level is less than it will stop output.
 *
 * example:
 *     // the example tag log enter silent mode
 *     ulog_set_filter_lvl("example", LOG_FILTER_LVL_SILENT);
 *     // the example tag log which level is less than INFO level will stop output
 *     ulog_set_filter_lvl("example", LOG_LVL_INFO);
 *     // remove example tag's level filter, all level log will resume output
 *     ulog_set_filter_lvl("example", LOG_FILTER_LVL_ALL);
 *
 * @param tag log tag
 * @param level The filter level. When the level is LOG_FILTER_LVL_SILENT, the log enter silent mode.
 *        When the level is LOG_FILTER_LVL_ALL, it will remove this tag's level filer.
 *        Then all level log will resume output.
 *
 * @return  0 : success
 *         -5 : no memory
 *         -10: level is out of range
 */
int ulog_tag_lvl_filter_set(const char *tag, rt_uint32_t level)
{
    rt_slist_t *node;
    ulog_tag_lvl_filter_t tag_lvl = NULL;
    int result = RT_EOK;

    if (level > LOG_FILTER_LVL_ALL)
        return -RT_EINVAL;

    if (!ulog.init_ok)
        return result;

    /* lock output */
    output_lock();
    /* find the tag in list */
    for (node = rt_slist_first(ulog_tag_lvl_list_get()); node; node = rt_slist_next(node))
    {
        tag_lvl = rt_slist_entry(node, struct ulog_tag_lvl_filter, list);
        if (!rt_strncmp(tag_lvl->tag, tag, ULOG_FILTER_TAG_MAX_LEN))
        {
            break;
        }
        else
        {
            tag_lvl = NULL;
        }
    }
    /* find OK */
    if (tag_lvl)
    {
        if (level == LOG_FILTER_LVL_ALL)
        {
            /* remove current tag's level filter when input level is the lowest level */
            rt_slist_remove(ulog_tag_lvl_list_get(), &tag_lvl->list);
            rt_free(tag_lvl);
        }
        else
        {
            /* update level */
            tag_lvl->level = level;
        }
    }
    else
    {
        /* only add the new tag's level filer when level is not LOG_FILTER_LVL_ALL */
        if (level != LOG_FILTER_LVL_ALL)
        {
            /* new a tag's level filter */
            tag_lvl = (ulog_tag_lvl_filter_t)rt_malloc(sizeof(struct ulog_tag_lvl_filter));
            if (tag_lvl)
            {
                rt_memset(tag_lvl->tag, 0 , sizeof(tag_lvl->tag));
                rt_strncpy(tag_lvl->tag, tag, ULOG_FILTER_TAG_MAX_LEN);
                tag_lvl->level = level;
                rt_slist_append(ulog_tag_lvl_list_get(), &tag_lvl->list);
            }
            else
            {
                result = -RT_ENOMEM;
            }
        }
    }
    /* unlock output */
    output_unlock();

    return result;
}

/**
 * get the level on tag's level filer
 *
 * @param tag log tag
 *
 * @return It will return the lowest level when tag was not found.
 *         Other level will return when tag was found.
 */
rt_uint32_t ulog_tag_lvl_filter_get(const char *tag)
{
    rt_slist_t *node;
    ulog_tag_lvl_filter_t tag_lvl = NULL;
    rt_uint32_t level = LOG_FILTER_LVL_ALL;

    if (!ulog.init_ok)
        return level;

    /* lock output */
    output_lock();
    /* find the tag in list */
    for (node = rt_slist_first(ulog_tag_lvl_list_get()); node; node = rt_slist_next(node))
    {
        tag_lvl = rt_slist_entry(node, struct ulog_tag_lvl_filter, list);
        if (!rt_strncmp(tag_lvl->tag, tag, ULOG_FILTER_TAG_MAX_LEN))
        {
            level = tag_lvl->level;
            break;
        }
    }
    /* unlock output */
    output_unlock();

    return level;
}

/**
 * get the tag's level list on filter
 *
 * @return tag's level list
 */
rt_slist_t *ulog_tag_lvl_list_get(void)
{
    return &ulog.filter.tag_lvl_list;
}

/**
 * set log global filter level
 *
 * @param level log level: LOG_LVL_ASSERT, LOG_LVL_ERROR, LOG_LVL_WARNING, LOG_LVL_INFO, LOG_LVL_DBG
 *              LOG_FILTER_LVL_SILENT: disable all log output, except assert level
 *              LOG_FILTER_LVL_ALL: enable all log output
 */
void ulog_global_filter_lvl_set(rt_uint32_t level)
{
    RT_ASSERT(level <= LOG_FILTER_LVL_ALL);

    ulog.filter.level = level;
}

/**
 * get log global filter level
 *
 * @return log level: LOG_LVL_ASSERT, LOG_LVL_ERROR, LOG_LVL_WARNING, LOG_LVL_INFO, LOG_LVL_DBG
 *              LOG_FILTER_LVL_SILENT: disable all log output, except assert level
 *              LOG_FILTER_LVL_ALL: enable all log output
 */
rt_uint32_t ulog_global_filter_lvl_get(void)
{
    return ulog.filter.level;
}

/**
 * set log global filter tag
 *
 * @param tag tag
 */
void ulog_global_filter_tag_set(const char *tag)
{
    RT_ASSERT(tag);

    rt_strncpy(ulog.filter.tag, tag, ULOG_FILTER_TAG_MAX_LEN);
}

/**
 * get log global filter tag
 *
 * @return tag
 */
const char *ulog_global_filter_tag_get(void)
{
    return ulog.filter.tag;
}

/**
 * set log global filter keyword
 *
 * @param keyword keyword
 */
void ulog_global_filter_kw_set(const char *keyword)
{
    RT_ASSERT(keyword);

    rt_strncpy(ulog.filter.keyword, keyword, ULOG_FILTER_KW_MAX_LEN);
}

/**
 * get log global filter keyword
 *
 * @return keyword
 */
const char *ulog_global_filter_kw_get(void)
{
    return ulog.filter.keyword;
}

#if defined(RT_USING_FINSH) && defined(FINSH_USING_MSH)
#include <finsh.h>

static void ulog_tag_lvl(uint8_t argc, char **argv)
{
    if (argc > 2)
    {
        if ((atoi(argv[2]) <= LOG_FILTER_LVL_ALL) && (atoi(argv[2]) >= 0))
        {
            ulog_tag_lvl_filter_set(argv[1], atoi(argv[2]));
        }
        else
        {
            rt_kprintf("Please input correct level (0-%d).\n", LOG_FILTER_LVL_ALL);
        }
    }
    else
    {
        rt_kprintf("Please input: ulog_tag_lvl <tag> <level>.\n");
#ifndef ULOG_USING_SYSLOG
        rt_kprintf("Assert  : 0\n");
        rt_kprintf("Error   : 3\n");
        rt_kprintf("Warning : 4\n");
        rt_kprintf("Info    : 6\n");
        rt_kprintf("Debug   : 7\n");
#else
        rt_kprintf("EMERG   :   1 (1 << 0)\n");
        rt_kprintf("ALERT   :   2 (1 << 1)\n");
        rt_kprintf("CRIT    :   4 (1 << 2)\n");
        rt_kprintf("ERR     :   8 (1 << 3)\n");
        rt_kprintf("WARNING :  16 (1 << 4)\n");
        rt_kprintf("NOTICE  :  32 (1 << 5)\n");
        rt_kprintf("INFO    :  64 (1 << 6)\n");
        rt_kprintf("DEBUG   : 128 (1 << 7)\n");
#endif /* ULOG_USING_SYSLOG */
    }
}
MSH_CMD_EXPORT(ulog_tag_lvl, Set ulog filter level by different tag.);

static void ulog_lvl(uint8_t argc, char **argv)
{
    if (argc > 1)
    {
        if ((atoi(argv[1]) <= LOG_FILTER_LVL_ALL) && (atoi(argv[1]) >= 0))
        {
            ulog_global_filter_lvl_set(atoi(argv[1]));
        }
        else
        {
            rt_kprintf("Please input correct level (0-%d).\n", LOG_FILTER_LVL_ALL);
        }
    }
    else
    {
        rt_kprintf("Please input: ulog_lvl <level>.\n");
#ifndef ULOG_USING_SYSLOG
        rt_kprintf("Assert  : 0\n");
        rt_kprintf("Error   : 3\n");
        rt_kprintf("Warning : 4\n");
        rt_kprintf("Info    : 6\n");
        rt_kprintf("Debug   : 7\n");
#else
        rt_kprintf("EMERG   :   1 (1 << 0)\n");
        rt_kprintf("ALERT   :   2 (1 << 1)\n");
        rt_kprintf("CRIT    :   4 (1 << 2)\n");
        rt_kprintf("ERR     :   8 (1 << 3)\n");
        rt_kprintf("WARNING :  16 (1 << 4)\n");
        rt_kprintf("NOTICE  :  32 (1 << 5)\n");
        rt_kprintf("INFO    :  64 (1 << 6)\n");
        rt_kprintf("DEBUG   : 128 (1 << 7)\n");
#endif /* ULOG_USING_SYSLOG */
    }
}
MSH_CMD_EXPORT(ulog_lvl, Set ulog global filter level.);

static void ulog_tag(uint8_t argc, char **argv)
{
    if (argc > 1)
    {
        if (rt_strlen(argv[1]) <= ULOG_FILTER_TAG_MAX_LEN)
        {
            ulog_global_filter_tag_set(argv[1]);
        }
        else
        {
            rt_kprintf("The tag length is too long. Max is %d.\n", ULOG_FILTER_TAG_MAX_LEN);
        }
    }
    else
    {
        ulog_global_filter_tag_set("");
    }
}
MSH_CMD_EXPORT(ulog_tag, Set ulog global filter tag);

static void ulog_kw(uint8_t argc, char **argv)
{
    if (argc > 1)
    {
        if (rt_strlen(argv[1]) <= ULOG_FILTER_KW_MAX_LEN)
        {
            ulog_global_filter_kw_set(argv[1]);
        }
        else
        {
            rt_kprintf("The keyword length is too long. Max is %d.\n", ULOG_FILTER_KW_MAX_LEN);
        }
    }
    else
    {
        ulog_global_filter_kw_set("");
    }
}
MSH_CMD_EXPORT(ulog_kw, Set ulog global filter keyword);

static void ulog_filter(uint8_t argc, char **argv)
{
#ifndef ULOG_USING_SYSLOG
    const char *lvl_name[] = { "Assert ", "Error  ", "Error  ", "Error  ", "Warning", "Info   ", "Info   ", "Debug  " };
#endif
    const char *tag = ulog_global_filter_tag_get(), *kw = ulog_global_filter_kw_get();
    rt_slist_t *node;
    ulog_tag_lvl_filter_t tag_lvl = NULL;

    rt_kprintf("--------------------------------------\n");
    rt_kprintf("ulog global filter:\n");

#ifndef ULOG_USING_SYSLOG
    rt_kprintf("level   : %s\n", lvl_name[ulog_global_filter_lvl_get()]);
#else
    rt_kprintf("level   : %d\n", ulog_global_filter_lvl_get());
#endif

    rt_kprintf("tag     : %s\n", rt_strlen(tag) == 0 ? "NULL" : tag);
    rt_kprintf("keyword : %s\n", rt_strlen(kw) == 0 ? "NULL" : kw);

    rt_kprintf("--------------------------------------\n");
    rt_kprintf("ulog tag's level filter:\n");
    if (rt_slist_isempty(ulog_tag_lvl_list_get()))
    {
        rt_kprintf("settings not found\n");
    }
    else
    {
        /* lock output */
        output_lock();
        /* show the tag level list */
        for (node = rt_slist_first(ulog_tag_lvl_list_get()); node; node = rt_slist_next(node))
        {
            tag_lvl = rt_slist_entry(node, struct ulog_tag_lvl_filter, list);
            rt_kprintf("%-*.s: ", ULOG_FILTER_TAG_MAX_LEN, tag_lvl->tag);

#ifndef ULOG_USING_SYSLOG
            rt_kprintf("%s\n", lvl_name[tag_lvl->level]);
#else
            rt_kprintf("%d\n", tag_lvl->level);
#endif

        }
        /* unlock output */
        output_unlock();
    }
}
MSH_CMD_EXPORT(ulog_filter, Show ulog filter settings);
#endif /* defined(RT_USING_FINSH) && defined(FINSH_USING_MSH) */
#endif /* ULOG_USING_FILTER */

rt_err_t ulog_backend_register(ulog_backend_t backend, const char *name, rt_bool_t support_color)
{
    rt_base_t level;

    RT_ASSERT(backend);
    RT_ASSERT(name);
    RT_ASSERT(ulog.init_ok);
    RT_ASSERT(backend->output);

    if (backend->init)
    {
        backend->init(backend);
    }

    backend->support_color = support_color;
    rt_memcpy(backend->name, name, RT_NAME_MAX);

    level = rt_hw_interrupt_disable();
    rt_slist_append(&ulog.backend_list, &backend->list);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t ulog_backend_unregister(ulog_backend_t backend)
{
    rt_base_t level;

    RT_ASSERT(backend);
    RT_ASSERT(ulog.init_ok);

    if (backend->deinit)
    {
        backend->deinit(backend);
    }

    level = rt_hw_interrupt_disable();
    rt_slist_remove(&ulog.backend_list, &backend->list);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

#ifdef ULOG_USING_ASYNC_OUTPUT
/**
 * asynchronous output logs to all backends
 *
 * @note you must call this function when ULOG_ASYNC_OUTPUT_BY_THREAD is disable
 */
void ulog_async_output(void)
{
    rt_rbb_blk_t log_blk;
    ulog_frame_t log_frame;

    while ((log_blk = rt_rbb_blk_get(ulog.async_rbb)) != NULL)
    {
        log_frame = (ulog_frame_t) log_blk->buf;
        if (log_frame->magic == ULOG_FRAME_MAGIC)
        {
            /* output to all backends */
            ulog_output_to_all_backend(log_frame->level, log_frame->tag, log_frame->is_raw, log_frame->log,
                    log_frame->log_len);
        }
        rt_rbb_blk_free(ulog.async_rbb, log_blk);
    }
}

/**
 * waiting for get asynchronous output log
 *
 * @param time the waiting time
 */
void ulog_async_waiting_log(rt_int32_t time)
{
    rt_sem_control(&ulog.async_notice, RT_IPC_CMD_RESET, RT_NULL);
    rt_sem_take(&ulog.async_notice, time);
}

static void async_output_thread_entry(void *param)
{
    ulog_async_output();

    while (1)
    {
        ulog_async_waiting_log(RT_WAITING_FOREVER);
        ulog_async_output();
    }
}
#endif /* ULOG_USING_ASYNC_OUTPUT */

/**
 * flush all backends's log
 */
void ulog_flush(void)
{
    rt_slist_t *node;
    ulog_backend_t backend;

    if (!ulog.init_ok)
        return;

#ifdef ULOG_USING_ASYNC_OUTPUT
    ulog_async_output();
#endif

    /* flush all backends */
    for (node = rt_slist_first(&ulog.backend_list); node; node = rt_slist_next(node))
    {
        backend = rt_slist_entry(node, struct ulog_backend, list);
        if (backend->flush)
        {
            backend->flush(backend);
        }
    }
}

int ulog_init(void)
{
    if (ulog.init_ok)
        return 0;

    rt_mutex_init(&ulog.output_locker, "ulog lock", RT_IPC_FLAG_FIFO);
    rt_slist_init(&ulog.backend_list);

#ifdef ULOG_USING_FILTER
    rt_slist_init(ulog_tag_lvl_list_get());
#endif

#ifdef ULOG_USING_ASYNC_OUTPUT
    RT_ASSERT(ULOG_ASYNC_OUTPUT_STORE_LINES >= 2);
    /* async output ring block buffer */
    ulog.async_rbb = rt_rbb_create(RT_ALIGN(ULOG_ASYNC_OUTPUT_BUF_SIZE, RT_ALIGN_SIZE), ULOG_ASYNC_OUTPUT_STORE_LINES);
    if (ulog.async_rbb == NULL)
    {
        rt_kprintf("Error: ulog init failed! No memory for async rbb.\n");
        rt_mutex_detach(&ulog.output_locker);
        return -RT_ENOMEM;
    }
    /* async output thread */
    ulog.async_th = rt_thread_create("ulog_async", async_output_thread_entry, &ulog, ULOG_ASYNC_OUTPUT_THREAD_STACK,
            ULOG_ASYNC_OUTPUT_THREAD_PRIORITY, 20);
    if (ulog.async_th == NULL)
    {
        rt_kprintf("Error: ulog init failed! No memory for async output thread.\n");
        rt_mutex_detach(&ulog.output_locker);
        rt_rbb_destroy(ulog.async_rbb);
        return -RT_ENOMEM;
    }

    rt_sem_init(&ulog.async_notice, "ulog", 0, RT_IPC_FLAG_FIFO);
    /* async output thread startup */
    rt_thread_startup(ulog.async_th);

#endif /* ULOG_USING_ASYNC_OUTPUT */

#ifdef ULOG_USING_FILTER
    ulog_global_filter_lvl_set(LOG_FILTER_LVL_ALL);
#endif

    ulog.init_ok = RT_TRUE;

    return 0;
}
INIT_PREV_EXPORT(ulog_init);

void ulog_deinit(void)
{
    rt_slist_t *node;
    ulog_backend_t backend;

    if (!ulog.init_ok)
        return;

    /* deinit all backends */
    for (node = rt_slist_first(&ulog.backend_list); node; node = rt_slist_next(node))
    {
        backend = rt_slist_entry(node, struct ulog_backend, list);
        if (backend->deinit)
        {
            backend->deinit(backend);
        }
    }

#ifdef ULOG_USING_FILTER
    /* deinit tag's level filter */
    {
        ulog_tag_lvl_filter_t tag_lvl;
        for (node = rt_slist_first(ulog_tag_lvl_list_get()); node; node = rt_slist_next(node))
        {
            tag_lvl = rt_slist_entry(node, struct ulog_tag_lvl_filter, list);
            rt_free(tag_lvl);
        }
    }
#endif /* ULOG_USING_FILTER */

    rt_mutex_detach(&ulog.output_locker);

#ifdef ULOG_USING_ASYNC_OUTPUT
    rt_rbb_destroy(ulog.async_rbb);
    rt_thread_delete(ulog.async_th);
#endif

    ulog.init_ok = RT_FALSE;
}

#endif /* RT_USING_ULOG */
