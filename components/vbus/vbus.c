/*
 * COPYRIGHT (C) 2011-2021, Real-Thread Information Technology Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-11-04     Grissiom     add comment
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "vbus.h"
#include "prio_queue.h"
#include "vbus_hw.h"

//#define RT_VBUS_STATISTICS

#define RT_VBUS_RB_LOW_TICK   (RT_VMM_RB_BLK_NR * 2 / 3)
#define RT_VBUS_RB_TICK_STEP  (100)

/* console could be run on vbus. If we log on it, there will be oops. */
#define vbus_debug(...)
#define vbus_verbose(...)
#define vbus_info(...)
#define vbus_error(...)

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(ar)     (sizeof(ar)/sizeof(ar[0]))
#endif

struct rt_vbus_ring *RT_VBUS_OUT_RING;
struct rt_vbus_ring *RT_VBUS_IN_RING;

const char *rt_vbus_chn_st2str[] = {
    "available",
    "closed",
    "establishing",
    "established",
    "suspended",
    "closing",
};

const char *rt_vbus_sess_st2str[] = {
    "available",
    "listening",
    "establishing",
};

const char *rt_vbus_cmd2str[] = {
    "ENABLE",
    "DISABLE",
    "SET",
    "ACK",
    "NAK",
    "SUSPEND",
    "RESUME",
};

static char* dump_cmd_pkt(unsigned char *dp, size_t dsize);

/* 4 bytes for the head */
#define LEN2BNR(len)    ((len + RT_VBUS_BLK_HEAD_SZ \
                          + sizeof(struct rt_vbus_blk) - 1) \
                         / sizeof(struct rt_vbus_blk))

rt_inline void _ring_add_get_bnr(struct rt_vbus_ring *ring,
                                 rt_size_t bnr)
{
    int nidx = ring->get_idx + bnr;

    if (nidx >= RT_VMM_RB_BLK_NR)
    {
        nidx -= RT_VMM_RB_BLK_NR;
    }
    rt_vbus_smp_wmb();
    ring->get_idx = nidx;
}

rt_inline int _bus_ring_space_nr(struct rt_vbus_ring *rg)
{
    int delta;

    rt_vbus_smp_rmb();
    delta = rg->get_idx - rg->put_idx;

    if (delta > 0)
    {
        /* Put is behind the get. */
        return delta - 1;
    }
    else
    {
        /* delta is negative. */
        return RT_VMM_RB_BLK_NR + delta - 1;
    }
}

struct rt_vbus_pkg {
    rt_uint8_t id;
    rt_uint8_t prio;
    rt_uint8_t finished;
    rt_uint8_t len;
    const void *data;
};

/* chn0 is always connected */
static enum rt_vbus_chn_status _chn_status[RT_VBUS_CHANNEL_NR];

rt_inline int _chn_connected(unsigned char chnr)
{
    return _chn_status[chnr] == RT_VBUS_CHN_ST_ESTABLISHED ||
           _chn_status[chnr] == RT_VBUS_CHN_ST_SUSPEND;
}

#ifdef RT_VBUS_USING_FLOW_CONTROL
#include <watermark_queue.h>
struct rt_watermark_queue _chn_wm_que[RT_VBUS_CHANNEL_NR];
void rt_vbus_set_post_wm(unsigned char chnr, unsigned int low, unsigned int high)
{
    RT_ASSERT((0 < chnr) && (chnr < ARRAY_SIZE(_chn_wm_que)));
    rt_wm_que_set_mark(&_chn_wm_que[chnr], low, high);
}

/* Threads suspended by the flow control of other side. */
rt_list_t _chn_suspended_threads[RT_VBUS_CHANNEL_NR];

struct
{
    unsigned int level;
    unsigned int high_mark;
    unsigned int low_mark;
    /* The suspend command does not have ACK. So if the other side still
     * sending pkg after SUSPEND, warn it again. Also use it as a flag that
     * tell me whether are we dropping from the high mark or not when reaching
     * the low mark. */
    unsigned int last_warn;
} _chn_recv_wm[RT_VBUS_CHANNEL_NR];

void rt_vbus_set_recv_wm(unsigned char chnr, unsigned int low, unsigned int high)
{
    RT_ASSERT((0 < chnr) && (chnr < ARRAY_SIZE(_chn_recv_wm)));
    _chn_recv_wm[chnr].low_mark = low;
    _chn_recv_wm[chnr].high_mark = high;
}
#else
void rt_vbus_set_recv_wm(unsigned char chnr, unsigned int low, unsigned int high)
{}
void rt_vbus_set_post_wm(unsigned char chnr, unsigned int low, unsigned int high)
{}
#endif

struct {
    rt_vbus_event_listener indicate;
    void *ctx;
} _vbus_rx_indi[RT_VBUS_EVENT_ID_MAX][RT_VBUS_CHANNEL_NR];

void rt_vbus_register_listener(unsigned char chnr,
                               enum rt_vbus_event_id eve,
                               rt_vbus_event_listener indi,
                               void *ctx)
{
    RT_ASSERT(chnr != 0 && chnr < RT_VBUS_CHANNEL_NR);
    RT_ASSERT(eve < sizeof(_vbus_rx_indi)/sizeof(_vbus_rx_indi[0]));

    _vbus_rx_indi[eve][chnr].indicate = indi;
    _vbus_rx_indi[eve][chnr].ctx = ctx;
}

static void _vbus_indicate(enum rt_vbus_event_id eve, unsigned char chnr)
{
    RT_ASSERT(eve < sizeof(_vbus_rx_indi)/sizeof(_vbus_rx_indi[0]));

    if (_vbus_rx_indi[eve][chnr].indicate)
        _vbus_rx_indi[eve][chnr].indicate(_vbus_rx_indi[eve][chnr].ctx);
}

#define _BUS_OUT_THRD_STACK_SZ  2048
#define _BUS_OUT_THRD_PRIO      8
#define _BUS_OUT_PKG_NR         RT_VMM_RB_BLK_NR

static struct rt_thread _bus_out_thread;
static rt_uint8_t _bus_out_thread_stack[_BUS_OUT_THRD_STACK_SZ];
struct rt_prio_queue *_bus_out_que;

static void _bus_out_entry(void *param)
{
    struct rt_vbus_pkg dpkg;

    _bus_out_que = rt_prio_queue_create("vbus",
                                        _BUS_OUT_PKG_NR,
                                        sizeof(struct rt_vbus_pkg));

    if (!_bus_out_que)
    {
        rt_kprintf("could not create vmm bus queue\n");
        return;
    }

    while (rt_prio_queue_pop(_bus_out_que, &dpkg,
                             RT_WAITING_FOREVER) == RT_EOK)
    {
        int sp;
        rt_uint32_t nxtidx;
        const int dnr = LEN2BNR(dpkg.len);

#ifdef RT_VBUS_USING_FLOW_CONTROL
        rt_wm_que_dec(&_chn_wm_que[dpkg.id]);
#endif

        if (!_chn_connected(dpkg.id))
            continue;

        sp = _bus_ring_space_nr(RT_VBUS_OUT_RING);

        vbus_debug("vmm bus out"
                   "(data: %p, len: %d, prio: %d, id: %d)\n",
                   dpkg.data, dpkg.len, dpkg.prio, dpkg.id);

        /* wait for enough space */
        while (sp < dnr)
        {
            rt_ubase_t lvl = rt_hw_interrupt_disable();

            RT_VBUS_OUT_RING->blocked = 1;
            rt_vbus_smp_wmb();

            /* kick the guest, hoping this could force it do the work */
            rt_vbus_tick(0, RT_VBUS_GUEST_VIRQ);

            rt_thread_suspend(rt_thread_self());
            rt_schedule();

            RT_VBUS_OUT_RING->blocked = 0;

            rt_hw_interrupt_enable(lvl);

            sp = _bus_ring_space_nr(RT_VBUS_OUT_RING);
        }

        nxtidx = RT_VBUS_OUT_RING->put_idx + dnr;

        RT_VBUS_OUT_RING->blks[RT_VBUS_OUT_RING->put_idx].id  = dpkg.id;
        RT_VBUS_OUT_RING->blks[RT_VBUS_OUT_RING->put_idx].qos = dpkg.prio;
        RT_VBUS_OUT_RING->blks[RT_VBUS_OUT_RING->put_idx].len = dpkg.len;

        if (nxtidx >= RT_VMM_RB_BLK_NR)
        {
            unsigned int tailsz;

            tailsz = (RT_VMM_RB_BLK_NR - RT_VBUS_OUT_RING->put_idx)
                * sizeof(RT_VBUS_OUT_RING->blks[0]) - RT_VBUS_BLK_HEAD_SZ;

            /* the remaining block is sufficient for the data */
            if (tailsz > dpkg.len)
                tailsz = dpkg.len;

            rt_memcpy(&RT_VBUS_OUT_RING->blks[RT_VBUS_OUT_RING->put_idx].data,
                      dpkg.data, tailsz);
            rt_memcpy(&RT_VBUS_OUT_RING->blks[0],
                      ((char*)dpkg.data)+tailsz,
                      dpkg.len - tailsz);

            rt_vbus_smp_wmb();
            RT_VBUS_OUT_RING->put_idx = nxtidx - RT_VMM_RB_BLK_NR;
        }
        else
        {
            rt_memcpy(&RT_VBUS_OUT_RING->blks[RT_VBUS_OUT_RING->put_idx].data,
                      dpkg.data, dpkg.len);

            rt_vbus_smp_wmb();
            RT_VBUS_OUT_RING->put_idx = nxtidx;
        }

        rt_vbus_smp_wmb();
        rt_vbus_tick(0, RT_VBUS_GUEST_VIRQ);

        if (dpkg.finished)
        {
            _vbus_indicate(RT_VBUS_EVENT_ID_TX, dpkg.id);
        }
    }
    RT_ASSERT(0);
}

void rt_vbus_resume_out_thread(void)
{
    rt_thread_resume(&_bus_out_thread);
    rt_schedule();
}

rt_err_t rt_vbus_post(rt_uint8_t id,
                      rt_uint8_t prio,
                      const void *data,
                      rt_size_t size,
                      rt_int32_t timeout)
{
    rt_err_t err = RT_EOK;
    struct rt_vbus_pkg pkg;
    unsigned int putsz;
    const unsigned char *dp;

    if (!_bus_out_que)
    {
        rt_kprintf("post (data: %p, size: %d, timeout: %d) "
                   "to bus before initialition\n",
                   data, size, timeout);
        return -RT_ERROR;
    }

    if (id >= RT_VBUS_CHANNEL_NR)
        return -RT_ERROR;

    if (timeout != 0)
    {
        RT_DEBUG_IN_THREAD_CONTEXT;
    }

#ifdef RT_VBUS_USING_FLOW_CONTROL
    while (_chn_status[id] == RT_VBUS_CHN_ST_SUSPEND)
    {
        rt_thread_t thread;

        if (timeout == 0)
        {
            return -RT_EFULL;
        }

        thread = rt_thread_self();
        thread->error = RT_EOK;
        /* We only touch the _chn_suspended_threads in thread, so lock the
         * scheduler is enough. */
        rt_enter_critical();
        rt_thread_suspend(thread);

        rt_list_insert_after(&_chn_suspended_threads[id], &thread->tlist);
        if (timeout > 0)
        {
            rt_timer_control(&(thread->thread_timer),
                             RT_TIMER_CTRL_SET_TIME,
                             &timeout);
            rt_timer_start(&(thread->thread_timer));
        }
        /* rt_exit_critical will do schedule on need. */
        rt_exit_critical();

        if (thread->error != RT_EOK)
            return thread->error;
    }
#endif

    if (_chn_status[id] != RT_VBUS_CHN_ST_ESTABLISHED)
        return -RT_ERROR;

    dp       = data;
    pkg.id   = id;
    pkg.prio = prio;
    for (putsz = 0; size; size -= putsz)
    {
        pkg.data = dp;

        if (size > RT_VBUS_MAX_PKT_SZ)
        {
            putsz = RT_VBUS_MAX_PKT_SZ;
            pkg.finished = 0;
        }
        else
        {
            putsz = size;
            pkg.finished = 1;
        }

        pkg.len = putsz;
        dp += putsz;

#ifdef RT_VBUS_USING_FLOW_CONTROL
        err = rt_wm_que_inc(&_chn_wm_que[id], timeout);
        if (err != RT_EOK)
            break;
#endif

        vbus_debug("post (data: %p(%d), size: %d, finshed: %d, timeout: %d)\n",
                   pkg.data, ((unsigned char*)pkg.data)[0],
                   pkg.len, pkg.finished, timeout);

        err = rt_prio_queue_push(_bus_out_que, prio, &pkg, timeout);
        if (err != RT_EOK)
            break;
    }

    return err;
}

struct rt_completion _chn0_post_cmp;

void _chn0_tx_listener(void *p)
{
    rt_completion_done(&_chn0_post_cmp);
}

/* Posts in channel0 should be sync. */
static rt_err_t _chn0_post(const void *data,
                               rt_size_t size,
                               int timeout)
{
    rt_err_t err;

    rt_completion_init(&_chn0_post_cmp);
    err = rt_vbus_post(0, 0, data, size, timeout);
    if (err != RT_EOK)
        return err;
    return rt_completion_wait(&_chn0_post_cmp, timeout);
}

#define _BUS_IN_THRD_STACK_SZ  1024
#define _BUS_IN_THRD_PRIO      (_BUS_OUT_THRD_PRIO+1)
#if (_BUS_IN_THRD_PRIO == RT_THREAD_PRIORITY_MAX)
#error "_BUS_OUT_THRD_PRIO too low"
#endif

static struct rt_thread _bus_in_thread;
static rt_uint8_t _bus_in_thread_stack[_BUS_OUT_THRD_STACK_SZ];
static struct rt_semaphore _bus_in_sem;
static struct rt_event     _bus_in_event;
/* {head, tail} */
#define _IN_ACT_HEAD 0
#define _IN_ACT_TAIL 1
static struct rt_vbus_data *_bus_in_action[RT_VBUS_CHANNEL_NR][2];
#ifdef RT_VBUS_STATISTICS
static unsigned int _bus_in_action_nr[RT_VBUS_CHANNEL_NR];
#endif

static void rt_vbus_notify_chn(unsigned char chnr, rt_err_t err)
{
#ifdef RT_VBUS_USING_FLOW_CONTROL
    /* TODO: get rid of this */
    /* Protect the list. */
    rt_enter_critical();
    while (!rt_list_isempty(&_chn_suspended_threads[chnr]))
    {
        rt_thread_t thread;

        thread = rt_list_entry(_chn_suspended_threads[chnr].next,
                               struct rt_thread,
                               tlist);
        thread->error = err;
        rt_thread_resume(thread);
    }
    rt_exit_critical();
#endif
    rt_event_send(&_bus_in_event, 1 << chnr);
}

static void rt_vbus_notify_set(rt_uint32_t set)
{
    rt_event_send(&_bus_in_event, set);
}

rt_err_t rt_vbus_listen_on(rt_uint8_t chnr,
                           rt_int32_t timeout)
{
    rt_uint32_t notuse;

    if (chnr == 0 || chnr >= RT_VBUS_CHANNEL_NR || !_chn_connected(chnr))
        return -RT_EIO;

    return rt_event_recv(&_bus_in_event, 1 << chnr,
                         RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                         timeout, &notuse);
}

void rt_vbus_data_push(unsigned int id, struct rt_vbus_data *act)
{
    rt_ubase_t lvl;

    RT_ASSERT(0 < id && id < RT_VBUS_CHANNEL_NR);

    lvl = rt_hw_interrupt_disable();

    if (_bus_in_action[id][_IN_ACT_HEAD] == RT_NULL)
    {
        _bus_in_action[id][_IN_ACT_HEAD] = act;
        _bus_in_action[id][_IN_ACT_TAIL] = act;
    }
    else
    {
        _bus_in_action[id][_IN_ACT_TAIL]->next = act;
        _bus_in_action[id][_IN_ACT_TAIL] = act;
    }

#ifdef RT_VBUS_STATISTICS
    _bus_in_action_nr[id]++;
#endif

    rt_hw_interrupt_enable(lvl);

#ifdef RT_VBUS_USING_FLOW_CONTROL
    _chn_recv_wm[id].level++;
    if (_chn_recv_wm[id].level == 0)
        _chn_recv_wm[id].level = ~0;
    if (_chn_recv_wm[id].level > _chn_recv_wm[id].high_mark &&
        _chn_recv_wm[id].level > _chn_recv_wm[id].last_warn)
    {
        unsigned char buf[2];

        buf[0] = RT_VBUS_CHN0_CMD_SUSPEND;
        buf[1] = id;
        vbus_debug("%s --> remote\n", dump_cmd_pkt(buf, sizeof(buf)));
        _chn0_post(buf, sizeof(buf), RT_WAITING_FOREVER);
        /* Warn the other side in 100 more pkgs. */
        _chn_recv_wm[id].last_warn = _chn_recv_wm[id].level + 100;
    }
#endif
}

struct rt_vbus_data* rt_vbus_data_pop(unsigned int id)
{
    struct rt_vbus_data *act;
    rt_ubase_t lvl;

    RT_ASSERT(0 < id && id < RT_VBUS_CHANNEL_NR);

    lvl = rt_hw_interrupt_disable();

    act = _bus_in_action[id][_IN_ACT_HEAD];
    if (act)
    {
        _bus_in_action[id][_IN_ACT_HEAD] = act->next;
    }

    rt_hw_interrupt_enable(lvl);

#ifdef RT_VBUS_USING_FLOW_CONTROL
    if (_chn_recv_wm[id].level != 0)
    {
        _chn_recv_wm[id].level--;
        if (_chn_recv_wm[id].level <= _chn_recv_wm[id].low_mark &&
            _chn_recv_wm[id].last_warn > _chn_recv_wm[id].low_mark)
        {
            unsigned char buf[2];

            buf[0] = RT_VBUS_CHN0_CMD_RESUME;
            buf[1] = id;
            vbus_debug("%s --> remote\n", dump_cmd_pkt(buf, sizeof(buf)));
            _chn0_post(buf, sizeof(buf), RT_WAITING_FOREVER);
            _chn_recv_wm[id].last_warn = 0;
        }
    }
#endif
    return act;
}

/* dump cmd that is not start with ACK/NAK */
static size_t __dump_naked_cmd(char *dst, size_t lsize,
                               unsigned char *dp, size_t dsize)
{
    size_t len;
    if (dp[0] == RT_VBUS_CHN0_CMD_DISABLE ||
        dp[0] == RT_VBUS_CHN0_CMD_SUSPEND ||
        dp[0] == RT_VBUS_CHN0_CMD_RESUME)
    {
        len = rt_snprintf(dst, lsize, "%s %d",
                          rt_vbus_cmd2str[dp[0]], dp[1]);
    }
    else if (dp[0] == RT_VBUS_CHN0_CMD_ENABLE)
    {
        len = rt_snprintf(dst, lsize, "%s %s",
                          rt_vbus_cmd2str[dp[0]], dp+1);
    }
    else if (dp[0] < RT_VBUS_CHN0_CMD_MAX)
    {
        len = rt_snprintf(dst, lsize, "%s %s %d",
                          rt_vbus_cmd2str[dp[0]],
                          dp+1, dp[2+rt_strlen((char*)dp+1)]);
    }
    else
    {
        len = rt_snprintf(dst, lsize, "(invalid)%d %d",
                          dp[0], dp[1]);
    }
    return len;
}

static char _cmd_dump_buf[64];
static char* dump_cmd_pkt(unsigned char *dp, size_t dsize)
{
    size_t len;

    if (dp[0] == RT_VBUS_CHN0_CMD_ACK || dp[0] == RT_VBUS_CHN0_CMD_NAK )
    {
        len = rt_snprintf(_cmd_dump_buf, sizeof(_cmd_dump_buf),
                          "%s ", rt_vbus_cmd2str[dp[0]]);
        len += __dump_naked_cmd(_cmd_dump_buf+len, sizeof(_cmd_dump_buf)-len,
                                dp+1, dsize-1);
    }
    else
    {
        len = __dump_naked_cmd(_cmd_dump_buf, sizeof(_cmd_dump_buf),
                               dp, dsize);
    }

    if (len > sizeof(_cmd_dump_buf) - 1)
        len = sizeof(_cmd_dump_buf) - 1;

    _cmd_dump_buf[len] = '\0';
    return _cmd_dump_buf;
}

static rt_err_t _chn0_echo_with(rt_uint8_t prefix,
                                rt_uint32_t dsize,
                                unsigned char *dp)
{
    rt_err_t err;
    unsigned char *resp;

    resp = rt_malloc(dsize+1);
    if (!resp)
        return -RT_ENOMEM;
    *resp = prefix;
    rt_memcpy(resp+1, dp, dsize);
    vbus_verbose("%s --> remote\n", dump_cmd_pkt(resp, dsize+1));

    err = _chn0_post(resp, dsize+1, RT_WAITING_FOREVER);

    rt_free(resp);

    return err;
}

static rt_err_t _chn0_nak(rt_uint32_t dsize, unsigned char *dp)
{
    return _chn0_echo_with(RT_VBUS_CHN0_CMD_NAK, dsize, dp);
}

static rt_err_t _chn0_ack(rt_uint32_t dsize, unsigned char *dp)
{
    return _chn0_echo_with(RT_VBUS_CHN0_CMD_ACK, dsize, dp);
}

enum _vbus_session_st
{
    SESSIOM_AVAILABLE,
    SESSIOM_LISTENING,
    SESSIOM_ESTABLISHING,
};

struct rt_vbus_conn_session
{
    /* negative value means error */
    int chnr;
    enum _vbus_session_st st;
    struct rt_completion cmp;
    struct rt_vbus_request *req;
};

static struct rt_vbus_conn_session _sess[RT_VBUS_CHANNEL_NR/2];

static int _sess_find(const unsigned char *name,
                      enum _vbus_session_st st)
{
    int i;

    for (i = 0; i < ARRAY_SIZE(_sess); i++)
    {
        if (_sess[i].st == st && _sess[i].req->name &&
            rt_strcmp(_sess[i].req->name, (char*)name) == 0)
            break;
    }
    return i;
}

static int _chn0_actor(unsigned char *dp, size_t dsize)
{
    if (*dp != RT_VBUS_CHN0_CMD_SUSPEND && *dp != RT_VBUS_CHN0_CMD_RESUME)
        vbus_verbose("local <-- %s\n", dump_cmd_pkt(dp, dsize));

    switch (*dp)
    {
    case RT_VBUS_CHN0_CMD_ENABLE:
        {
            int i, chnr;
            rt_err_t err;
            unsigned char *resp;

            i = _sess_find(dp+1, SESSIOM_LISTENING);
            if (i == ARRAY_SIZE(_sess))
            {
                _chn0_nak(dsize, dp);
                break;
            }

            for (chnr = 0; chnr < ARRAY_SIZE(_chn_status); chnr++)
            {
                if (_chn_status[chnr] == RT_VBUS_CHN_ST_AVAILABLE)
                    break;
            }
            if (chnr == ARRAY_SIZE(_chn_status))
            {
                _chn0_nak(dsize, dp);
                break;
            }

            resp = rt_malloc(dsize + 1);
            if (!resp)
                break;

            *resp = RT_VBUS_CHN0_CMD_SET;
            rt_memcpy(resp+1, dp+1, dsize-1);
            resp[dsize] = chnr;

            rt_vbus_set_recv_wm(chnr, _sess[i].req->recv_wm.low, _sess[i].req->recv_wm.high);
            rt_vbus_set_post_wm(chnr, _sess[i].req->post_wm.low, _sess[i].req->post_wm.high);

            vbus_verbose("%s --> remote\n", dump_cmd_pkt(resp, dsize+1));
            err = _chn0_post(resp, dsize+1, RT_WAITING_FOREVER);

            if (err == RT_EOK)
            {
                _sess[i].st   = SESSIOM_ESTABLISHING;
                vbus_debug("set sess %d st: %s\n", i,
                           rt_vbus_sess_st2str[_sess[i].st]);
                _sess[i].chnr = chnr;
                _chn_status[chnr] = RT_VBUS_CHN_ST_ESTABLISHING;
            }
            rt_free(resp);
        }
        break;
    case RT_VBUS_CHN0_CMD_SET:
        {
            int i, chnr;

            i = _sess_find(dp+1, SESSIOM_ESTABLISHING);
            if (i == ARRAY_SIZE(_sess))
            {
                vbus_verbose("drop spurious packet\n");
                break;
            }

            chnr = dp[1+rt_strlen((const char*)dp+1)+1];

            if (chnr == 0 || chnr >= RT_VBUS_CHANNEL_NR)
            {
                vbus_verbose("SET wrong chnr %d\n", chnr);
                break;
            }
            if (_chn_status[chnr] != RT_VBUS_CHN_ST_AVAILABLE)
            {
                _chn0_nak(dsize, dp);
                vbus_verbose("SET wrong chnr status %d, %s\n",
                             chnr, rt_vbus_chn_st2str[_chn_status[chnr]]);
                break;
            }

            rt_vbus_set_recv_wm(chnr, _sess[i].req->recv_wm.low, _sess[i].req->recv_wm.high);
            rt_vbus_set_post_wm(chnr, _sess[i].req->post_wm.low, _sess[i].req->post_wm.high);

            if (_chn0_ack(dsize, dp) >= 0)
            {
                _sess[i].chnr = chnr;
                _chn_status[chnr] = RT_VBUS_CHN_ST_ESTABLISHED;
                vbus_debug("chn %d %s\n", chnr,
                           rt_vbus_chn_st2str[_chn_status[chnr]]);
                rt_completion_done(&_sess[i].cmp);
            }
        }
        break;
    case RT_VBUS_CHN0_CMD_ACK:
        if (dp[1] == RT_VBUS_CHN0_CMD_SET)
        {
            int i, chnr;

            i = _sess_find(dp+2, SESSIOM_ESTABLISHING);
            if (i == ARRAY_SIZE(_sess))
                /* drop that spurious packet */
                break;

            chnr = dp[1+rt_strlen((const char*)dp+2)+2];

            _sess[i].chnr = chnr;
            _chn_status[chnr] = RT_VBUS_CHN_ST_ESTABLISHED;
            vbus_debug("chn %d %s\n", chnr,
                       rt_vbus_chn_st2str[_chn_status[chnr]]);
            rt_completion_done(&_sess[i].cmp);
        }
        else if (dp[1] == RT_VBUS_CHN0_CMD_DISABLE)
        {
            unsigned char chnr = dp[2];

            if (chnr == 0 || chnr >= RT_VBUS_CHANNEL_NR)
                break;

            /* We could only get here by sending DISABLE command, which is
             * initiated by the rt_vbus_close_chn. */
            _chn_status[chnr] = RT_VBUS_CHN_ST_AVAILABLE;

            _vbus_indicate(RT_VBUS_EVENT_ID_DISCONN, chnr);
            /* notify the thread that the channel has been closed */
            rt_vbus_notify_chn(chnr, -RT_ERROR);
        }
        else
        {
            vbus_info("invalid ACK for %d\n", dp[1]);
        }
        break;
    case RT_VBUS_CHN0_CMD_DISABLE:
        {
            unsigned char chnr = dp[1];

            if (chnr == 0 || chnr >= RT_VBUS_CHANNEL_NR)
                break;

            _chn_status[chnr] = RT_VBUS_CHN_ST_CLOSING;

            _chn0_ack(dsize, dp);

            _vbus_indicate(RT_VBUS_EVENT_ID_DISCONN, chnr);
            /* notify the thread that the channel has been closed */
            rt_vbus_notify_chn(chnr, -RT_ERROR);
        }
        break;
    case RT_VBUS_CHN0_CMD_SUSPEND:
#ifdef RT_VBUS_USING_FLOW_CONTROL
        {
            unsigned char chnr = dp[1];

            if (chnr == 0 || chnr >= RT_VBUS_CHANNEL_NR)
                break;

            if (_chn_status[chnr] != RT_VBUS_CHN_ST_ESTABLISHED)
                break;

            _chn_status[chnr] = RT_VBUS_CHN_ST_SUSPEND;
        }
#endif
        break;
    case RT_VBUS_CHN0_CMD_RESUME:
#ifdef RT_VBUS_USING_FLOW_CONTROL
        {
            unsigned char chnr = dp[1];

            if (chnr == 0 || chnr >= RT_VBUS_CHANNEL_NR)
                break;

            if (_chn_status[chnr] != RT_VBUS_CHN_ST_SUSPEND)
                break;

            _chn_status[chnr] = RT_VBUS_CHN_ST_ESTABLISHED;

            /* Protect the list. */
            rt_enter_critical();
            while (!rt_list_isempty(&_chn_suspended_threads[chnr]))
            {
                rt_thread_t thread;

                thread = rt_list_entry(_chn_suspended_threads[chnr].next,
                                       struct rt_thread,
                                       tlist);
                rt_thread_resume(thread);
            }
            rt_exit_critical();
        }
#endif
        break;
    case RT_VBUS_CHN0_CMD_NAK:
        if (dp[1] == RT_VBUS_CHN0_CMD_ENABLE)
        {
            int i;

            i = _sess_find(dp+2, SESSIOM_ESTABLISHING);
            if (i == ARRAY_SIZE(_sess))
                /* drop that spurious packet */
                break;

            _sess[i].chnr = -RT_EIO;
            rt_completion_done(&_sess[i].cmp);
        }
        else if (dp[1] == RT_VBUS_CHN0_CMD_SET)
        {
            vbus_info("NAK for %d not implemented\n", dp[1]);
        }
        else
        {
            vbus_info("invalid NAK for %d\n", dp[1]);
        }
        break;
    default:
        /* just ignore the invalid cmd */
        vbus_info("drop unknown cmd %d on chn0\n", *dp);
        break;
    };

    return RT_EOK;
}

int rt_vbus_request_chn(struct rt_vbus_request *req,
                        int timeout)
{
    int i, chnr, err;
    size_t plen = rt_strlen(req->name) + 2;
    unsigned char *pbuf;
    rt_ubase_t lvl;

    lvl = rt_hw_interrupt_disable();
    for (i = 0; i < ARRAY_SIZE(_sess); i++)
    {
        if (_sess[i].st == SESSIOM_AVAILABLE)
            break;
    }
    if (i == ARRAY_SIZE(_sess))
    {
        rt_hw_interrupt_enable(lvl);
        return -RT_ERROR;
    }

    rt_completion_init(&_sess[i].cmp);
    _sess[i].req = req;

    if (req->is_server)
    {
        _sess[i].st = SESSIOM_LISTENING;
        rt_hw_interrupt_enable(lvl);

        vbus_debug("request listening %s on %d\n", req->name, i);

        /* always wait on the condition */
        err = RT_EOK;
        goto _waitforcmp;
    }

    pbuf = rt_malloc(plen);
    if (!pbuf)
    {
        rt_hw_interrupt_enable(lvl);
        return -RT_ENOMEM;
    }

    _sess[i].st = SESSIOM_ESTABLISHING;
    rt_hw_interrupt_enable(lvl);

    pbuf[0] = RT_VBUS_CHN0_CMD_ENABLE;
    rt_memcpy(pbuf+1, req->name, plen-1);
    vbus_verbose("%s --> remote\n", dump_cmd_pkt(pbuf, plen));

    err = _chn0_post(pbuf, plen, RT_WAITING_FOREVER);
    rt_free(pbuf);

_waitforcmp:
    if (err == RT_EOK)
        err = rt_completion_wait(&_sess[i].cmp, timeout);

    vbus_debug("request wait cmp done %d, chnr %d\n", err, _sess[i].chnr);

    if (err)
    {
        /* cleanup the mass when the wait is time out but we have done some job
         */
        if (_sess[i].st == SESSIOM_ESTABLISHING)
            _chn_status[_sess[i].chnr] = RT_VBUS_CHN_ST_AVAILABLE;
        chnr = err;
        goto Out;
    }

    RT_ASSERT(_sess[i].chnr != 0);

    chnr = _sess[i].chnr;

Out:
    /* detach the sess as we finished the job */
    _sess[i].st = SESSIOM_AVAILABLE;
    _sess[i].req = RT_NULL;

    return chnr;
}

void rt_vbus_close_chn(unsigned char chnr)
{
    void *p;
    rt_err_t err;
    unsigned char buf[2];

    buf[0] = RT_VBUS_CHN0_CMD_DISABLE;
    buf[1] = chnr;

    RT_ASSERT(0 < chnr && chnr < RT_VBUS_CHANNEL_NR);

    if (_chn_status[chnr] == RT_VBUS_CHN_ST_CLOSED ||
        _chn_status[chnr] == RT_VBUS_CHN_ST_CLOSING)
    {
        _chn_status[chnr] = RT_VBUS_CHN_ST_AVAILABLE;
        return;
    }

    if (!_chn_connected(chnr))
        return;

    _chn_status[chnr] = RT_VBUS_CHN_ST_CLOSING;
    vbus_info("%s --> remote\n", dump_cmd_pkt(buf, sizeof(buf)));
    err = _chn0_post(&buf, sizeof(buf), RT_WAITING_FOREVER);
    if (err == RT_EOK)
        /* wait for the ack */
        rt_vbus_listen_on(chnr, 10 * RT_TICK_PER_SECOND);

    /* cleanup the remaining data */
    for (p = rt_vbus_data_pop(chnr); p; p = rt_vbus_data_pop(chnr))
        rt_free(p);
    /* FIXME: there is a chance that there are some data left on the send
     * buffer. So if we connect other channel with the same number immediately,
     * the new channel will receive some garbage data. However, this is highly
     * un-probable. */
}

#ifdef RT_VBUS_STATISTICS
static unsigned int _total_data_sz;
#endif

static void _bus_in_entry(void *param)
{
    rt_sem_init(&_bus_in_sem, "vbus", 0, RT_IPC_FLAG_FIFO);
    rt_event_init(&_bus_in_event, "vbus", RT_IPC_FLAG_FIFO);
    rt_memset(_bus_in_action, 0, sizeof(_bus_in_action));

    while (rt_sem_take(&_bus_in_sem,
                       RT_WAITING_FOREVER) == RT_EOK)
    {
        rt_uint32_t event_set = 0;

        /* while(not empty) */
        while (RT_VBUS_IN_RING->get_idx != RT_VBUS_IN_RING->put_idx)
        {
            unsigned int id, nxtidx;
            rt_size_t size;
            struct rt_vbus_data *act;

            rt_vbus_smp_rmb();
            size = RT_VBUS_IN_RING->blks[RT_VBUS_IN_RING->get_idx].len;
            id = RT_VBUS_IN_RING->blks[RT_VBUS_IN_RING->get_idx].id;

            vbus_debug("vmm bus in: chnr %d, size %d\n", id, size);

            /* Suspended channel can still recv data. */
            if (id > RT_VBUS_CHANNEL_NR || !_chn_connected(id))
            {
                vbus_error("drop on invalid chn %d\n", id);
                /* drop the invalid packet */
                _ring_add_get_bnr(RT_VBUS_IN_RING, LEN2BNR(size));
                continue;
            }

            if (id == 0)
            {
                if (size > 60)
                    vbus_error("too big(%d) packet on chn0\n", size);
                else
                    _chn0_actor(RT_VBUS_IN_RING->blks[RT_VBUS_IN_RING->get_idx].data, size);
                _ring_add_get_bnr(RT_VBUS_IN_RING, LEN2BNR(size));
                continue;
            }

#ifdef RT_VBUS_STATISTICS
            _total_data_sz += size;
#endif

            act = rt_malloc(sizeof(*act) + size);
            if (act == RT_NULL)
            {
                //vbus_error("drop on OOM (%d, %d)\n", id, size);
                /* drop the packet on malloc fall */
                _ring_add_get_bnr(RT_VBUS_IN_RING, LEN2BNR(size));
                continue;
            }

            act->size = size;
            act->next = RT_NULL;

            nxtidx = RT_VBUS_IN_RING->get_idx + LEN2BNR(size);
            if (nxtidx >= RT_VMM_RB_BLK_NR)
            {
                unsigned int tailsz;

                tailsz = (RT_VMM_RB_BLK_NR - RT_VBUS_IN_RING->get_idx)
                          * sizeof(RT_VBUS_IN_RING->blks[0]) - RT_VBUS_BLK_HEAD_SZ;

                /* the remaining block is sufficient for the data */
                if (tailsz > size)
                    tailsz = size;

                rt_memcpy(act+1, &RT_VBUS_IN_RING->blks[RT_VBUS_IN_RING->get_idx].data, tailsz);
                rt_memcpy((char*)(act+1) + tailsz, &RT_VBUS_IN_RING->blks[0], size - tailsz);

                /* It shall make sure the CPU has finished reading the item
                 * before it writes the new tail pointer, which will erase the
                 * item. */
                rt_vbus_smp_wmb();
                RT_VBUS_IN_RING->get_idx = nxtidx - RT_VMM_RB_BLK_NR;
            }
            else
            {
                rt_memcpy(act+1, &RT_VBUS_IN_RING->blks[RT_VBUS_IN_RING->get_idx].data, size);

                rt_vbus_smp_wmb();
                RT_VBUS_IN_RING->get_idx = nxtidx;
            }

            rt_vbus_data_push(id, act);
            _vbus_indicate(RT_VBUS_EVENT_ID_RX, id);
            event_set |= 1 << id;

            if (RT_VBUS_IN_RING->blocked)
                rt_vbus_tick(0, RT_VBUS_GUEST_VIRQ);
        }

        if (event_set != 0)
            rt_vbus_notify_set(event_set);
    }
    RT_ASSERT(0);
}

void rt_vbus_isr(int irqnr, void *param)
{
    if (RT_VBUS_OUT_RING->blocked)
        rt_vbus_resume_out_thread();

    rt_sem_release(&_bus_in_sem);
    rt_vbus_hw_eoi(irqnr, param);
}

int rt_vbus_init(void *outr, void *inr)
{
    int i;

    if (outr > inr)
    {
        RT_ASSERT((char*)outr - (char*)inr >= sizeof(struct rt_vbus_ring));
    }
    else
    {
        RT_ASSERT((char*)inr - (char*)outr >= sizeof(struct rt_vbus_ring));
    }

    RT_VBUS_OUT_RING = outr;
    RT_VBUS_IN_RING  = inr;

    rt_memset(RT_VBUS_OUT_RING, 0, sizeof(*RT_VBUS_OUT_RING));
    rt_memset(RT_VBUS_IN_RING,  0, sizeof(*RT_VBUS_IN_RING));
    _chn_status[0] = RT_VBUS_CHN_ST_ESTABLISHED;
    for (i = 1; i < ARRAY_SIZE(_chn_status); i++)
    {
        _chn_status[i] = RT_VBUS_CHN_ST_AVAILABLE;
    }
    for (i = 0; i < ARRAY_SIZE(_sess); i++)
    {
        _sess[i].req = RT_NULL;
        _sess[i].st  = SESSIOM_AVAILABLE;
    }
    _vbus_rx_indi[RT_VBUS_EVENT_ID_TX][0].indicate = _chn0_tx_listener;
    _vbus_rx_indi[RT_VBUS_EVENT_ID_TX][0].ctx = RT_NULL;

#ifdef RT_VBUS_USING_FLOW_CONTROL
    for (i = 0; i < ARRAY_SIZE(_chn_wm_que); i++)
    {
        rt_wm_que_init(&_chn_wm_que[i],
                       RT_VMM_RB_BLK_NR / 3,
                       RT_VMM_RB_BLK_NR * 2 / 3);
    }
    /* Channel 0 has the full channel. */
    rt_wm_que_set_mark(&_chn_wm_que[0], 0, ~0);

    for (i = 0; i < ARRAY_SIZE(_chn_suspended_threads); i++)
    {
        rt_list_init(&_chn_suspended_threads[i]);
    }

    for (i = 1; i < ARRAY_SIZE(_chn_recv_wm); i++)
    {
        rt_vbus_set_recv_wm(i,
                            RT_VMM_RB_BLK_NR / 3,
                            RT_VMM_RB_BLK_NR * 2 / 3);
        _chn_recv_wm[i].level = 0;
        _chn_recv_wm[i].last_warn = 0;
    }
    /* Channel 0 has the full channel. Don't suspend it. */
    _chn_recv_wm[0].low_mark = 0;
    _chn_recv_wm[0].high_mark = ~0;
    _chn_recv_wm[0].level = 0;
    _chn_recv_wm[0].last_warn = 0;
#endif

    rt_thread_init(&_bus_out_thread, "vbusout",
                   _bus_out_entry, RT_NULL,
                   _bus_out_thread_stack, sizeof(_bus_out_thread_stack),
                   _BUS_OUT_THRD_PRIO, 20);
    rt_thread_startup(&_bus_out_thread);

    rt_thread_init(&_bus_in_thread, "vbusin",
                   _bus_in_entry, RT_NULL,
                   _bus_in_thread_stack, sizeof(_bus_in_thread_stack),
                   _BUS_IN_THRD_PRIO, 20);


    rt_thread_startup(&_bus_in_thread);

    rt_vbus_hw_init();

    rt_kprintf("VBus loaded: %d out blocks, %d in blocks\n",
               RT_VMM_RB_BLK_NR, RT_VMM_RB_BLK_NR);

    rt_vbus_chnx_init();

    return 0;
}

void rt_vbus_rb_dump(void)
{
    rt_kprintf("OUT ring:(%s blocked)\n", RT_VBUS_OUT_RING->blocked ? "is" : "not");
    rt_kprintf("put idx: %8x, get idx: %8x\n",
               RT_VBUS_OUT_RING->put_idx, RT_VBUS_OUT_RING->get_idx);
    rt_kprintf("space: %d\n", _bus_ring_space_nr(RT_VBUS_OUT_RING));


    rt_kprintf("IN ring:(%s blocked)\n", RT_VBUS_IN_RING->blocked ? "is" : "not");
    rt_kprintf("put idx: %8x, get idx: %8x\n",
               RT_VBUS_IN_RING->put_idx, RT_VBUS_IN_RING->get_idx);
    rt_kprintf("space: %d\n", _bus_ring_space_nr(RT_VBUS_IN_RING));
}

void rt_vbus_chn_dump(void)
{
    int i;
    rt_kprintf("vbus channel status:\n");
    for (i = 0; i < ARRAY_SIZE(_chn_status); i++)
    {
        rt_kprintf("%2d:%s\n", i, rt_vbus_chn_st2str[_chn_status[i]]);
    }
}

void rt_vbus_sess_dump(void)
{
    int i;

    rt_kprintf("vbus conn session:\n");
    for (i = 0; i < ARRAY_SIZE(_sess); i++)
    {
        rt_kprintf("%2d(%s):%s\n", i, _sess[i].req ? _sess[i].req->name : "",
                   rt_vbus_sess_st2str[_sess[i].st]);
    }
}

void rt_vbus_que_dump(void)
{
    rt_kprintf("out que:\n");
    rt_prio_queue_dump(_bus_out_que);
}

unsigned int rt_vbus_total_data_sz(void)
{
#ifdef RT_VBUS_STATISTICS
    return _total_data_sz;
#else
    return (unsigned int)-1;
#endif
}

void rt_vbus_data_pkt_dump(void)
{
    int i;

    for (i = 0; i < ARRAY_SIZE(_bus_in_action); i++)
    {
        struct rt_vbus_data *dp;

#ifdef RT_VBUS_STATISTICS
        rt_kprintf("%2d %4d: ", i, _bus_in_action_nr[i]);
#else
        rt_kprintf("%2d: ", i);
#endif
        for (dp = _bus_in_action[i][_IN_ACT_HEAD];
             dp;
             dp = dp->next)
        {
            rt_kprintf("%p(%d) -> ", dp, dp->size);
        }
        rt_kprintf(" nil\n");
    }
}

#ifdef RT_VBUS_USING_FLOW_CONTROL
void rt_vbus_chm_wm_dump(void)
{
    int i;

    rt_kprintf("post wm:\n");
    for (i = 0; i < ARRAY_SIZE(_chn_wm_que); i++)
        rt_wm_que_dump(&_chn_wm_que[i]);

    rt_kprintf("recv wm:\n");
    rt_kprintf("     low,     high,      cur,  last warn\n");
    for (i = 0; i < ARRAY_SIZE(_chn_recv_wm); i++)
    {
        rt_kprintf("%8x, %8x, %8x, %8x\n",
                   _chn_recv_wm[i].low_mark, _chn_recv_wm[i].high_mark,
                   _chn_recv_wm[i].level, _chn_recv_wm[i].last_warn);
    }
}
#endif

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT_ALIAS(rt_vbus_rb_dump,   vbrb, dump vbus ringbuffer status);
FINSH_FUNCTION_EXPORT_ALIAS(rt_vbus_chn_dump,  vbchn, dump vbus channel status);
FINSH_FUNCTION_EXPORT_ALIAS(rt_vbus_sess_dump, vbses, dump vbus session status);
FINSH_FUNCTION_EXPORT_ALIAS(rt_vbus_que_dump,  vbque, dump vbus out queue status);
FINSH_FUNCTION_EXPORT_ALIAS(rt_vbus_total_data_sz,  vbtsz, total in data);
FINSH_FUNCTION_EXPORT_ALIAS(rt_vbus_data_pkt_dump,  vbdq, dump the data queue);
#ifdef RT_VBUS_USING_FLOW_CONTROL
FINSH_FUNCTION_EXPORT_ALIAS(rt_vbus_chm_wm_dump, vbwm, dump vbus water mark status);
#endif
#endif

