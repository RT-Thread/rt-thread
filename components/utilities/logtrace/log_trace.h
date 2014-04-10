/*
 * File      : log_trace.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013-2014, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 *                Bernard      the first version
 * 2013-06-26     Grissiom     refactor
 */

#ifndef __LOG_TRACE_H__
#define __LOG_TRACE_H__

#include <rtthread.h>

#define LOG_TRACE_LEVEL_MASK        0x0f
#define LOG_TRACE_LEVEL_NOTRACE     0x00
#define LOG_TRACE_LEVEL_ERROR       0x01
#define LOG_TRACE_LEVEL_WARNING     0x03
#define LOG_TRACE_LEVEL_INFO        0x05
#define LOG_TRACE_LEVEL_VERBOSE     0x07
#define LOG_TRACE_LEVEL_DEBUG       0x09
#define LOG_TRACE_LEVEL_ALL         0x0f

#ifndef LOG_TRACE_LEVEL_DEFAULT
#define LOG_TRACE_LEVEL_DEFAULT LOG_TRACE_LEVEL_INFO
#endif

#define LOG_TRACE_ERROR             "<1>"
#define LOG_TRACE_WARNING           "<3>"
#define LOG_TRACE_INFO              "<5>"
#define LOG_TRACE_VERBOSE           "<7>"
#define LOG_TRACE_DEBUG             "<9>"

#define LOG_TRACE_OPT_NOTS          0x10    /* no timestamp */
#define LOG_TRACE_OPT_LN            0x20    /* terminate the current line */

#define LOG_TRACE_CTRL_FLUSH        0x10
#define LOG_TRACE_CTRL_RESET        0x11
#define LOG_TRACE_CTRL_DUMP         0x12

//#define LOG_TRACE_USE_LONGNAME

#ifndef LOG_TRACE_BUFSZ
#define LOG_TRACE_BUFSZ RT_CONSOLEBUF_SIZE
#endif

/** maximum number of sessions that can be registered to the log_trace system
 */
#ifndef LOG_TRACE_MAX_SESSION
#define LOG_TRACE_MAX_SESSION 16
#endif

#ifdef LOG_TRACE_USE_LONGNAME
typedef rt_uint64_t log_trace_idnum_t;
#else
typedef rt_uint32_t log_trace_idnum_t;
#endif

/* use a integer to represent a string to avoid strcmp. Even 4 chars
 * should be enough for most of the cases.
 * NOTE: take care when converting the name string to id number, you
 * can trapped in endianness.
 */
union log_trace_id {
    char name[sizeof(log_trace_idnum_t)];
    log_trace_idnum_t num;
};

struct log_trace_session
{
    union log_trace_id id;
    rt_uint8_t lvl;
};

/** initialize the log_trace system */
void log_trace_init(void);

/** register a session.
 *
 * @return RT_EOK on success. -RT_EFULL if there is no space for registration.
 */
rt_err_t log_trace_register_session(const struct log_trace_session *session);

/** find a session with name
 *
 * The name is not enclosed by parenthesis([]).
 *
 * @return RT_NULL if there is no such a session.
 */
struct log_trace_session* log_trace_session_find(const char *name);

/** set the log level of the default session. */
void log_trace_set_level(rt_uint8_t level);

/** set the log level of the session */
void log_trace_session_set_level(
        struct log_trace_session *session, rt_uint8_t level);

/** log according to the format
 *
 * the format of log_trace is: "<level>[name]log messages".  It will output
 * "[systick][name]log messages" When there is no session named name, the
 * default session will be used.
 *
 * We have keep the level tag before the name tag because we don't print put
 * the level tag to the output and it's easier to implement if we place the
 * level tag in the very beginning.
 */
void log_trace(const char *fmt, ...);

/** log into session.
 *
 * the format of log_trace is: "<level>log messages".  It will output
 * "[systick][name]log messages". The name is the name of the session. It is
 * faster than bare log_trace.
 */
void log_session(const struct log_trace_session *session, const char *fmt, ...);

extern void __logtrace_vfmtout(const struct log_trace_session *session,
                               const char *fmt,
                               va_list argptr);

rt_inline void __logtrace_fmtout(const struct log_trace_session *session,
                                     const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    __logtrace_vfmtout(session, fmt, args);
    va_end(args);
}

/**
 * log with numeric level
 *
 * The prototype of this function is:
 *
 * void log_session_lvl(struct log_trace_session *session,
 *                      int lvl,
 *                      const char *fmt, ...);
 *
 * If the @session is const and @level is greater than @session->lvl, the whole
 * function will be optimized out. This is suitable for performance critical
 * places where in most cases, the log is turned off by level.
 */
#define log_session_lvl(session, level, fmt, ...)       \
    do {                                                \
        if ((level) > (session)->lvl)                   \
        {                                               \
            break;                                      \
        }                                               \
        __logtrace_fmtout(session, fmt, ##__VA_ARGS__); \
    } while (0)

/* here comes the global part. All sessions share the some output backend. */

/** get the backend device */
rt_device_t log_trace_get_device(void);

/** set the backend device */
rt_err_t log_trace_set_device(const char *device_name);

void log_trace_flush(void);

#ifdef RT_USING_DFS
/** set the backend to file */
void log_trace_set_file(const char *filename);

void log_trace_file_init(const char *filename);
#endif /* RT_USING_DFS */

#endif

