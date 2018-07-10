/*
 * File      : log_trace.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013, RT-Thread Development Team
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

#include <rtthread.h>
#include <rthw.h>
#include <stdio.h>
#include "log_trace.h"

#ifdef RT_USING_FINSH
#include <finsh.h>
#else
#define FINSH_FUNCTION_EXPORT(...)
#define FINSH_FUNCTION_EXPORT_ALIAS(...)
#endif

/* log pseudo device */
static struct rt_device _log_device;

static rt_device_t _traceout_device = RT_NULL;

/* define a default lg session. The name is empty. */
static struct log_trace_session _def_session = {{"\0"}, LOG_TRACE_LEVEL_DEFAULT};
static const struct log_trace_session *_the_sessions[LOG_TRACE_MAX_SESSION] = {&_def_session};
/* there is a default session at least */
static rt_uint16_t _the_sess_nr = 1;

rt_inline int _idname_len(log_trace_idnum_t id)
{
    /* little endian */
    if ((id & 0x000000FF) == 0)
        return 0;
    if ((id & 0x0000FF00) == 0)
        return 1;
    if ((id & 0x00FF0000) == 0)
        return 2;
    if ((id & 0xFF000000) == 0)
        return 3;
#ifndef LOG_TRACE_USE_LONGNAME
    return 4;
#else
    {
        rt_uint32_t id2 = id >> 32;
        if ((id2 & 0x000000FF) == 0)
            return 4;
        if ((id2 & 0x0000FF00) == 0)
            return 5;
        if ((id2 & 0x00FF0000) == 0)
            return 6;
        if ((id2 & 0xFF000000) == 0)
            return 7;
        return 8;
    }
#endif
}

/* lookup the session according to name.
 *
 * @param len is the length of the name
 * @return the pointer to the named session. RT_NULL when there is no such a
 * session.
 */
static struct log_trace_session* _lg_lookup_session(log_trace_idnum_t num)
{
    static const struct log_trace_session *_cache = &_def_session;
    rt_uint16_t first, last;

    if (_cache->id.num == num)
        return (struct log_trace_session *)_cache;

    first = 0;
    last  = _the_sess_nr;
    do {
        unsigned int i = (first + last)/2;

        RT_ASSERT(_the_sessions[i]);

        if (_the_sessions[i]->id.num == num)
        {
            /* there is no need to protect the _cache because write a pointer
             * is atomic. So we cannot get a invalid pointer. The worst thing
             * could happen is there is an interrupt in the read/modify/write
             * process and we wrote the old one to _cache. But it doesn't harm
             * a lot because it will be flushed in the next time. */
            _cache = _the_sessions[i];
            return (struct log_trace_session *)_the_sessions[i];
        }
        else if (_the_sessions[i]->id.num > num)
        {
            last = i;
        }
        else // _the_sessions[i]->id.num < num
        {
            first = i;
        }
    } while (first != last-1);

    return RT_NULL;
}

rt_err_t log_trace_register_session(const struct log_trace_session *session)
{
    unsigned int lvl, i;

    if (_the_sess_nr == LOG_TRACE_MAX_SESSION)
        return -RT_EFULL;

    if (session == RT_NULL)
        return RT_EOK;

    lvl = rt_hw_interrupt_disable();
    /* inserting the sessions in ascending order.
     *
     * this might take relatively long time. But since the register should only
     * happen when initialize the whole system, this should not be a matter. */
    for (i = 0; i < _the_sess_nr; i++)
    {
        if (_the_sessions[i]->id.num > session->id.num)
        {
            rt_memmove(_the_sessions+i+1, _the_sessions+i,
                       (_the_sess_nr-i)*sizeof(&_the_sessions[0]));
            _the_sessions[i] = session;
            break;
        }
        else if (_the_sessions[i]->id.num == session->id.num)
        {
            rt_kprintf("registering session 0x%p twice\n", session);
            rt_hw_interrupt_enable(lvl);
            return -RT_ERROR;
        }
    }
    if (i == _the_sess_nr)
        _the_sessions[i] = session;
    _the_sess_nr++;
    rt_hw_interrupt_enable(lvl);

    return RT_EOK;
}

struct log_trace_session* log_trace_session_find(const char *name)
{
    union log_trace_id *idp;

    RT_ASSERT(name);
    idp = (union log_trace_id*)name;
    return _lg_lookup_session(idp->num);
}

void log_trace_set_level(rt_uint8_t level)
{
    _def_session.lvl = level;
}
FINSH_FUNCTION_EXPORT_ALIAS(log_trace_set_level, log_level, set the filter level of log trace);

void log_trace_session_set_level(struct log_trace_session *sess, rt_uint8_t level)
{
    RT_ASSERT(sess);
    sess->lvl = level;
}

/* parse the level info in fmt
 *
 * @param flen the length of the format.
 * @param lvlp the pointer to level. It will store the level in the memory the
 *        lvlp points to. The default value is LOG_TRACE_LEVEL_DEFAULT.
 * @return the number of char it scaned.
 */
static rt_size_t _lg_parse_lvl(const char *fmt, rt_size_t flen, int *lvlp)
{
    RT_ASSERT(fmt);
    RT_ASSERT(lvlp);

    /* setup default value */
    *lvlp = LOG_TRACE_LEVEL_DEFAULT;

    if (flen < 3)
    {
        return 0;
    }

    if (fmt[0] == '<' && fmt[2] == '>')
    {
        *lvlp = fmt[1] - '0';
        return 3;
    }
    return 0;
}

/* parse the header in fmt
 *
 * @param flen the length of the format.
 * @param sessp the pointer of pointer to the session. It will store the
 *        session pointer in the memory the sessp points to. When failed to
 *        find the session, it will be setted to the default session.
 * @return the number of char it scaned, i.e., the length of header.
 */
static rt_size_t _lg_parse_session(
        const char *fmt, rt_size_t flen, struct log_trace_session **sessp)
{
    unsigned int i;
    struct log_trace_session *tmpsess;
    union log_trace_id id;

    RT_ASSERT(fmt);
    RT_ASSERT(sessp);

    /* setup default value */
    *sessp = &_def_session;

    /* no name space left */
    if (flen < sizeof(id) + 2)
        return 0;

    if (fmt[0] != '[')
        return 0;

    id.num = 0;
    /* skip '[' and convert the string to id number. */
    for (i = 1; fmt[i] != ']'; i++)
    {
        if (i - 1 == sizeof(id))
            return 0;
        id.name[i-1] = fmt[i];
    }
    tmpsess = _lg_lookup_session(id.num);
    if (tmpsess != RT_NULL)
    {
        *sessp = tmpsess;
        /* only count the header length when we found the session. So
         * the wrong [name] will be printed out. */
        return i + 1;
    }

    return 0;
}

void __logtrace_vfmtout(const struct log_trace_session *session,
                        const char *fmt,
                        va_list argptr)
{
    /* 1 for ']' */
    static char _trace_buf[1+LOG_TRACE_BUFSZ];
    char *ptr;
    rt_size_t length;

    RT_ASSERT(session);
    RT_ASSERT(fmt);

    /* it's default session */
    if (session->id.name[0] == '\0')
    {
        rt_snprintf(_trace_buf, sizeof(_trace_buf), "[%08x]", rt_tick_get());
        if (_traceout_device != RT_NULL)
        {
            rt_device_write(_traceout_device, -1, _trace_buf, 10);
        }

        ptr = &_trace_buf[0];
    }
    else
    {
        rt_snprintf(_trace_buf, sizeof(_trace_buf), "[%08x][", rt_tick_get());
        if (_traceout_device != RT_NULL)
        {
            rt_device_write(_traceout_device, -1, _trace_buf, 11);
            rt_device_write(_traceout_device, -1,
                    session->id.name, _idname_len(session->id.num));
        }

        _trace_buf[0] = ']';
        ptr = &_trace_buf[1];
    }

    length = rt_vsnprintf(ptr, LOG_TRACE_BUFSZ, fmt, argptr);

    if (length >= LOG_TRACE_BUFSZ)
        length = LOG_TRACE_BUFSZ - 1;

    if (_traceout_device != RT_NULL)
    {
        rt_device_write(_traceout_device, -1, _trace_buf, length + 1);
    }
}

void log_trace(const char *fmt, ...)
{
    va_list args;
    int level;
    struct log_trace_session *session;

    RT_ASSERT(fmt);

    fmt += _lg_parse_lvl(fmt, strlen(fmt), &level);
    fmt += _lg_parse_session(fmt, strlen(fmt), &session);

    /* filter by level */
    if (level > session->lvl)
        return;

    va_start(args, fmt);
    __logtrace_vfmtout(session, fmt, args);
    va_end(args);
}
FINSH_FUNCTION_EXPORT(log_trace, log trace);

void log_session(const struct log_trace_session *session, const char *fmt, ...)
{
    va_list args;
    int level;

    RT_ASSERT(session);
    RT_ASSERT(fmt);

    fmt += _lg_parse_lvl(fmt, strlen(fmt), &level);
    if (level > session->lvl)
        return;

    va_start(args, fmt);
    __logtrace_vfmtout(session, fmt, args);
    va_end(args);
}

void log_trace_flush(void)
{
    rt_device_control(_traceout_device, LOG_TRACE_CTRL_FLUSH, RT_NULL);
}
FINSH_FUNCTION_EXPORT_ALIAS(log_trace_flush, log_flush, flush log on the buffer);

/* RT-Thread common device interface */
static rt_size_t _log_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    char c;
    int level;
    rt_size_t head_len;
    const char *ptr = buffer;
    struct log_trace_session *session;

    head_len = _lg_parse_lvl(ptr, size, &level);
    head_len += _lg_parse_session(ptr+head_len, size-head_len, &session);

    /* filter by level */
    if (level > session->lvl)
        return size;

    if (_traceout_device != RT_NULL)
    {
        c = '[';
        rt_device_write(_traceout_device, -1, &c, 1);
        rt_device_write(_traceout_device, -1, session->id.name, _idname_len(session->id.num));
        c = ']';
        rt_device_write(_traceout_device, -1, &c, 1);
        rt_device_write(_traceout_device, -1, ((char*)buffer)+head_len, size - head_len);
    }

    return size;
}

static rt_err_t _log_control(rt_device_t dev, int cmd, void *arg)
{
    if (_traceout_device == RT_NULL) return -RT_ERROR;

    return rt_device_control(_traceout_device, cmd, arg);
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops log_device_ops = 
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _log_write,
    _log_control
};
#endif

int log_trace_init(void)
{
    rt_memset(&_log_device, 0x00, sizeof(_log_device));

    _log_device.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    _log_device.ops     = &log_device_ops;
#else
    _log_device.init    = RT_NULL;
    _log_device.open    = RT_NULL;
    _log_device.close   = RT_NULL;
    _log_device.read    = RT_NULL;
    _log_device.write   = _log_write;
    _log_device.control = _log_control;
#endif

    /* no indication and complete callback */
    _log_device.rx_indicate = RT_NULL;
    _log_device.tx_complete = RT_NULL;

    rt_device_register(&_log_device, "log", RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_RDWR);

	/* set console as default device */
	_traceout_device = rt_console_get_device();

    return 0;
}
INIT_DEVICE_EXPORT(log_trace_init);

rt_device_t log_trace_get_device(void)
{
    return _traceout_device;
}

rt_err_t log_trace_set_device(const char *device_name)
{
    struct rt_device *output_device;

    /* find out output device */
    output_device = rt_device_find(device_name);
    if (output_device != RT_NULL)
    {
        rt_err_t result;

        /* open device */
        result = rt_device_open(output_device, RT_DEVICE_FLAG_STREAM | RT_DEVICE_OFLAG_RDWR);
        if (result != RT_EOK)
        {
            rt_kprintf("Open trace device failed.\n");
            return -RT_ERROR;
        }
    }

    /* set trace out device */
    if (_traceout_device != RT_NULL)
        rt_device_close(_traceout_device);
    _traceout_device = output_device;

    return RT_EOK;
}
FINSH_FUNCTION_EXPORT_ALIAS(log_trace_set_device, log_device, set device of log trace);

