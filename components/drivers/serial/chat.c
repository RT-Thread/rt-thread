#include <rtthread.h>
#include <rtdevice.h>
#define DBG_TAG    "CHAT"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>
#include "chat.h"

#ifndef RT_CHAT_DEVICE
#error "RT_CHAT_DEVICE not defined"
#endif
#define CHAT_READ_BUF_MAX 16
#define CHAT_TX_STRING_MAX 23

// In order to match response, we need a string search algorithm
// KMP and AC algorithm both are good choice, But we need the code
// is simple, readable and use lower RAM/ROM.
// So We use a simplified search algorithm, this alg is like the KMP.
// Specifically we assume the failure vecotor is [-1, 0, 0, 0, ...]
// This assuming is not work for all pattern string. Fortunately,
// it's work  for this scene.

#define DEFINE_RESP_STRDATA_TABLE(id, str) [id] = str
#define DEFINE_RESP_STRLEN_TABLE(id, str)  [id] = (sizeof(str)-1)



static char *resp_strdata[] =
{
    CHAT_RESP_LIST(DEFINE_RESP_STRDATA_TABLE)
};

static rt_uint8_t resp_strlen[] =
{
    CHAT_RESP_LIST(DEFINE_RESP_STRLEN_TABLE)
};

static rt_device_t chat_device;
static struct rt_completion chat_rx_comp;

#if DBG_LVL < DBG_LOG
#define CHAT_DATA_FMT           "<chat_data: 0x%p>"
#define CHAT_DATA_STR(data)     data
#else

#define CHAT_DATA_FMT           "<transmit: %s, expect: %s, retries: %u>"
#define CHAT_DATA_STR(data)    transmit_tostring((data)->transmit), resp2str((data)->expect), (data)->retries

static char tostrbuf[CHAT_TX_STRING_MAX + 1];

static char* transmit_tostring_append(char *buffer, const char *append)
{
    rt_size_t remain;
    rt_size_t want;

    remain = CHAT_TX_STRING_MAX - (buffer - tostrbuf);
    want = rt_strlen(append);
    if (want >= remain)
        want = remain;

    rt_memcpy(buffer, append, want);
    buffer[want] = 0;
    return &buffer[want];
}

static char* transmit_tostring_append_char(char *buffer, char ch)
{
    rt_size_t remain;

    remain = CHAT_TX_STRING_MAX - (buffer - tostrbuf);
    if (remain > 0)
    {
        buffer[0] = ch;
        buffer[1] = 0;
        return &buffer[1];
    }
    return NULL;
}

static const char* transmit_tostring(const char *str)
{
    char tmp[8];
    char *buf;
    rt_uint8_t uc;
    char ch;

    buf = tostrbuf;
    while (*str)
    {
        ch = *str++;
        if (0x20 <= ch && ch <= 0x7e)
            buf = transmit_tostring_append_char(buf, ch);
        else if (ch == '\r')
            buf = transmit_tostring_append(buf, "<CR>");
        else if (ch == '\n')
            buf = transmit_tostring_append(buf, "<LF>");
        else
        {
            uc = (rt_uint8_t)ch;
            if (uc < 8)
                rt_sprintf(tmp, "<%d>", uc);
            else
                rt_sprintf(tmp, "<0%o>", uc);
            buf = transmit_tostring_append(buf, tmp);
        }
        if (!buf)
            break;
    }
    return tostrbuf;
}

#endif

static const char* resp2str(rt_uint8_t resp_id)
{
    RT_ASSERT(resp_id < CHAT_RESP_MAX);
    return resp_strdata[resp_id];
}

static rt_uint8_t resp_match(rt_uint8_t resp_id, rt_uint8_t state, char ch)
{
    while (1)
    {
        if (resp2str(resp_id)[state] == ch)
            return state + 1;
        if (state == 0)
            return 0;
        state = 0;
    };
}

static rt_bool_t resp_matched(rt_uint8_t resp_id, rt_uint8_t state)
{
    return state == resp_strlen[resp_id];
}

static rt_err_t chat_rx_ind(rt_device_t device, rt_size_t size)
{
    rt_completion_done(&chat_rx_comp);
    return RT_EOK;
}

static rt_size_t chat_read_until(void *buffer, rt_size_t size, rt_tick_t stop)
{
    rt_size_t rdlen;
    rt_tick_t wait;

    rt_completion_init(&chat_rx_comp);
    rdlen = rt_device_read(chat_device, 0, buffer, size);
    if (rdlen)
        return rdlen;

    wait = stop - rt_tick_get();
    if (wait > RT_TICK_MAX / 2)
        return 0;

    rt_completion_wait(&chat_rx_comp, wait);
    return rt_device_read(chat_device, 0, buffer, size);
}

static rt_err_t chat_run_one(const struct chat_data *data)
{
    rt_uint8_t resp_state[CHAT_RESP_MAX] = { 0 }, resp;
    rt_tick_t stop = rt_tick_get() + data->timeout*RT_TICK_PER_SECOND;
    rt_size_t rdlen, pos;
    char rdbuf[CHAT_READ_BUF_MAX];

    if (data->transmit)
    {
        LOG_D(CHAT_DATA_FMT" transmit --> modem", CHAT_DATA_STR(data));
        rt_device_write(chat_device, 0, data->transmit, rt_strlen(data->transmit));
    }

    if (data->expect == CHAT_RESP_NOT_NEED)
        return RT_EOK;

    do
    {
        rdlen = chat_read_until(rdbuf, CHAT_READ_BUF_MAX, stop);
        for (pos = 0; pos < rdlen; pos++)
        {
            for (resp = 0; resp < CHAT_RESP_MAX; resp++)
            {
                resp_state[resp] = resp_match(resp, resp_state[resp], rdbuf[pos]);
                if (resp_matched(resp, resp_state[resp]))
                {
                    if (resp == data->expect)
                        return RT_EOK;

                    LOG_W(CHAT_DATA_FMT" not matched, got: %s", CHAT_DATA_STR(data), resp2str(resp));
                    return -RT_ERROR;
                }
            }
        }
    } while ( stop - rt_tick_get() < RT_TICK_MAX / 2);
    LOG_W(CHAT_DATA_FMT" timeout", CHAT_DATA_STR(data));
    return -RT_ETIMEOUT;
}

static rt_err_t chat_run_internal(const struct chat_data *data, rt_size_t len)
{
    rt_err_t err = RT_EOK;
    rt_size_t i;
    rt_uint8_t retry_time;

    for (i = 0; i < len; i++)
    {
        LOG_I("chat: "CHAT_DATA_FMT, CHAT_DATA_STR(&data[i]));
        for (retry_time = 0; retry_time < data->retries; retry_time++)
        {
            err = chat_run_one(&data[i]);
            if (err == RT_EOK)
                break;
        }
        if (retry_time > 0 && retry_time == data[i].retries)
        {
            LOG_E("chat: "CHAT_DATA_FMT" execute fail", CHAT_DATA_STR(&data[i]));
            break;
        }
        LOG_I("chat: "CHAT_DATA_FMT" execute success", CHAT_DATA_STR(&data[i]));

    }
    return err;
}

rt_err_t chat_run(const struct chat_data *data, rt_size_t len)
{
    rt_err_t (*old_rx_ind)(rt_device_t dev, rt_size_t size) = NULL;
    rt_err_t err;
    rt_uint16_t open_flag, old_open_flag;

    if (chat_device)
    {
        LOG_E("chat module is busy");
        return -RT_EBUSY;
    }
    chat_device = rt_device_find(RT_CHAT_DEVICE);
    if (!chat_device)
    {
        LOG_E("cannot found: %s", RT_CHAT_DEVICE);
        return -RT_EIO;
    }

    old_rx_ind = chat_device->rx_indicate;
    old_open_flag = chat_device->open_flag;

    open_flag = RT_DEVICE_OFLAG_RDWR;
    if (chat_device->flag & RT_DEVICE_FLAG_DMA_RX)
        open_flag |= RT_DEVICE_FLAG_DMA_RX;
    else if (chat_device->flag & RT_DEVICE_FLAG_INT_RX)
        open_flag |= RT_DEVICE_FLAG_INT_RX;

    if (chat_device->flag & RT_DEVICE_FLAG_DMA_TX)
        open_flag |= RT_DEVICE_FLAG_DMA_TX;
    else if (chat_device->flag & RT_DEVICE_FLAG_INT_TX)
        open_flag |= RT_DEVICE_FLAG_INT_TX;

    err = rt_device_open(chat_device, open_flag);
    if (err)
    {
        LOG_E("open(%s, 0x%x) fail", RT_CHAT_DEVICE, open_flag);
        chat_device = NULL;
        return err;
    }

    rt_completion_init(&chat_rx_comp);
    rt_device_set_rx_indicate(chat_device, chat_rx_ind);

    err = chat_run_internal(data, len);

    if (err == RT_EOK)
        LOG_I("chat success");

    if (old_rx_ind)
        rt_device_set_rx_indicate(chat_device, old_rx_ind);

    rt_device_close(chat_device);
    chat_device->open_flag = old_open_flag;
    chat_device = NULL;
    return err;
}
