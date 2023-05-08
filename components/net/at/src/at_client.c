/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-30     chenyong     first version
 * 2018-04-12     chenyong     add client implement
 * 2018-08-17     chenyong     multiple client support
 * 2021-03-17     Meco Man     fix a buf of leaking memory
 * 2021-07-14     Sszl         fix a buf of leaking memory
 */

#include <at.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_TAG              "at.clnt"
#include <at_log.h>

#ifdef AT_USING_CLIENT

#define AT_RESP_END_OK                 "OK"
#define AT_RESP_END_ERROR              "ERROR"
#define AT_RESP_END_FAIL               "FAIL"
#define AT_END_CR_LF                   "\r\n"

static struct at_client at_client_table[AT_CLIENT_NUM_MAX] = { 0 };

extern rt_size_t at_utils_send(rt_device_t dev,
                               rt_off_t    pos,
                               const void *buffer,
                               rt_size_t   size);
extern rt_size_t at_vprintfln(rt_device_t device, const char *format, va_list args);
extern void at_print_raw_cmd(const char *type, const char *cmd, rt_size_t size);
extern const char *at_get_last_cmd(rt_size_t *cmd_size);

/**
 * Create response object.
 *
 * @param buf_size the maximum response buffer size
 * @param line_num the number of setting response lines
 *         = 0: the response data will auto return when received 'OK' or 'ERROR'
 *        != 0: the response data will return when received setting lines number data
 * @param timeout the maximum response time
 *
 * @return != RT_NULL: response object
 *          = RT_NULL: no memory
 */
at_response_t at_create_resp(rt_size_t buf_size, rt_size_t line_num, rt_int32_t timeout)
{
    at_response_t resp = RT_NULL;

    resp = (at_response_t) rt_calloc(1, sizeof(struct at_response));
    if (resp == RT_NULL)
    {
        LOG_E("AT create response object failed! No memory for response object!");
        return RT_NULL;
    }

    resp->buf = (char *) rt_calloc(1, buf_size);
    if (resp->buf == RT_NULL)
    {
        LOG_E("AT create response object failed! No memory for response buffer!");
        rt_free(resp);
        return RT_NULL;
    }

    resp->buf_size = buf_size;
    resp->line_num = line_num;
    resp->line_counts = 0;
    resp->timeout = timeout;

    return resp;
}

/**
 * Delete and free response object.
 *
 * @param resp response object
 */
void at_delete_resp(at_response_t resp)
{
    if (resp && resp->buf)
    {
        rt_free(resp->buf);
    }

    if (resp)
    {
        rt_free(resp);
        resp = RT_NULL;
    }
}

/**
 * Set response object information
 *
 * @param resp response object
 * @param buf_size the maximum response buffer size
 * @param line_num the number of setting response lines
 *         = 0: the response data will auto return when received 'OK' or 'ERROR'
 *        != 0: the response data will return when received setting lines number data
 * @param timeout the maximum response time
 *
 * @return  != RT_NULL: response object
 *           = RT_NULL: no memory
 */
at_response_t at_resp_set_info(at_response_t resp, rt_size_t buf_size, rt_size_t line_num, rt_int32_t timeout)
{
    char *p_temp;
    RT_ASSERT(resp);

    if (resp->buf_size != buf_size)
    {
        resp->buf_size = buf_size;

        p_temp = (char *) rt_realloc(resp->buf, buf_size);
        if (p_temp == RT_NULL)
        {
            LOG_D("No memory for realloc response buffer size(%d).", buf_size);
            return RT_NULL;
        }
        else
        {
            resp->buf = p_temp;
        }
    }

    resp->line_num = line_num;
    resp->timeout = timeout;

    return resp;
}

/**
 * Get one line AT response buffer by line number.
 *
 * @param resp response object
 * @param resp_line line number, start from '1'
 *
 * @return != RT_NULL: response line buffer
 *          = RT_NULL: input response line error
 */
const char *at_resp_get_line(at_response_t resp, rt_size_t resp_line)
{
    char *resp_buf = resp->buf;
    char *resp_line_buf = RT_NULL;
    rt_size_t line_num = 1;

    RT_ASSERT(resp);

    if (resp_line > resp->line_counts || resp_line <= 0)
    {
        LOG_E("AT response get line failed! Input response line(%d) error!", resp_line);
        return RT_NULL;
    }

    for (line_num = 1; line_num <= resp->line_counts; line_num++)
    {
        if (resp_line == line_num)
        {
            resp_line_buf = resp_buf;

            return resp_line_buf;
        }

        resp_buf += strlen(resp_buf) + 1;
    }

    return RT_NULL;
}

/**
 * Get one line AT response buffer by keyword
 *
 * @param resp response object
 * @param keyword query keyword
 *
 * @return != RT_NULL: response line buffer
 *          = RT_NULL: no matching data
 */
const char *at_resp_get_line_by_kw(at_response_t resp, const char *keyword)
{
    char *resp_buf = resp->buf;
    char *resp_line_buf = RT_NULL;
    rt_size_t line_num = 1;

    RT_ASSERT(resp);
    RT_ASSERT(keyword);

    for (line_num = 1; line_num <= resp->line_counts; line_num++)
    {
        if (strstr(resp_buf, keyword))
        {
            resp_line_buf = resp_buf;

            return resp_line_buf;
        }

        resp_buf += strlen(resp_buf) + 1;
    }

    return RT_NULL;
}

/**
 * Get and parse AT response buffer arguments by line number.
 *
 * @param resp response object
 * @param resp_line line number, start from '1'
 * @param resp_expr response buffer expression
 *
 * @return -1 : input response line number error or get line buffer error
 *          0 : parsed without match
 *         >0 : the number of arguments successfully parsed
 */
int at_resp_parse_line_args(at_response_t resp, rt_size_t resp_line, const char *resp_expr, ...)
{
    va_list args;
    int resp_args_num = 0;
    const char *resp_line_buf = RT_NULL;

    RT_ASSERT(resp);
    RT_ASSERT(resp_expr);

    if ((resp_line_buf = at_resp_get_line(resp, resp_line)) == RT_NULL)
    {
        return -1;
    }

    va_start(args, resp_expr);

    resp_args_num = vsscanf(resp_line_buf, resp_expr, args);

    va_end(args);

    return resp_args_num;
}

/**
 * Get and parse AT response buffer arguments by keyword.
 *
 * @param resp response object
 * @param keyword query keyword
 * @param resp_expr response buffer expression
 *
 * @return -1 : input keyword error or get line buffer error
 *          0 : parsed without match
 *         >0 : the number of arguments successfully parsed
 */
int at_resp_parse_line_args_by_kw(at_response_t resp, const char *keyword, const char *resp_expr, ...)
{
    va_list args;
    int resp_args_num = 0;
    const char *resp_line_buf = RT_NULL;

    RT_ASSERT(resp);
    RT_ASSERT(resp_expr);

    if ((resp_line_buf = at_resp_get_line_by_kw(resp, keyword)) == RT_NULL)
    {
        return -1;
    }

    va_start(args, resp_expr);

    resp_args_num = vsscanf(resp_line_buf, resp_expr, args);

    va_end(args);

    return resp_args_num;
}

/**
 * Send commands to AT server and wait response.
 *
 * @param client current AT client object
 * @param resp AT response object, using RT_NULL when you don't care response
 * @param cmd_expr AT commands expression
 *
 * @return 0 : success
 *        -1 : response status error
 *        -2 : wait timeout
 *        -7 : enter AT CLI mode
 */
int at_obj_exec_cmd(at_client_t client, at_response_t resp, const char *cmd_expr, ...)
{
    va_list args;
    rt_size_t cmd_size = 0;
    rt_err_t result = RT_EOK;
    const char *cmd = RT_NULL;

    RT_ASSERT(cmd_expr);

    if (client == RT_NULL)
    {
        LOG_E("input AT Client object is NULL, please create or get AT Client object!");
        return -RT_ERROR;
    }

    /* check AT CLI mode */
    if (client->status == AT_STATUS_CLI && resp)
    {
        return -RT_EBUSY;
    }

    rt_mutex_take(client->lock, RT_WAITING_FOREVER);

    client->resp_status = AT_RESP_OK;

    if (resp != RT_NULL)
    {
        resp->buf_len = 0;
        resp->line_counts = 0;
    }

    client->resp = resp;
    rt_sem_control(client->resp_notice, RT_IPC_CMD_RESET, RT_NULL);

    va_start(args, cmd_expr);
    at_vprintfln(client->device, cmd_expr, args);
    va_end(args);

    if (resp != RT_NULL)
    {
        if (rt_sem_take(client->resp_notice, resp->timeout) != RT_EOK)
        {
            cmd = at_get_last_cmd(&cmd_size);
            LOG_W("execute command (%.*s) timeout (%d ticks)!", cmd_size, cmd, resp->timeout);
            client->resp_status = AT_RESP_TIMEOUT;
            result = -RT_ETIMEOUT;
            goto __exit;
        }
        if (client->resp_status != AT_RESP_OK)
        {
            cmd = at_get_last_cmd(&cmd_size);
            LOG_E("execute command (%.*s) failed!", cmd_size, cmd);
            result = -RT_ERROR;
            goto __exit;
        }
    }

__exit:
    client->resp = RT_NULL;

    rt_mutex_release(client->lock);

    return result;
}

/**
 * Waiting for connection to external devices.
 *
 * @param client current AT client object
 * @param timeout millisecond for timeout
 *
 * @return 0 : success
 *        -2 : timeout
 *        -5 : no memory
 */
int at_client_obj_wait_connect(at_client_t client, rt_uint32_t timeout)
{
    rt_err_t result = RT_EOK;
    at_response_t resp = RT_NULL;
    rt_tick_t start_time = 0;
    char *client_name = client->device->parent.name;

    if (client == RT_NULL)
    {
        LOG_E("input AT client object is NULL, please create or get AT Client object!");
        return -RT_ERROR;
    }

    resp = at_create_resp(64, 0, rt_tick_from_millisecond(300));
    if (resp == RT_NULL)
    {
        LOG_E("no memory for AT client(%s) response object.", client_name);
        return -RT_ENOMEM;
    }

    rt_mutex_take(client->lock, RT_WAITING_FOREVER);
    client->resp = resp;
    rt_sem_control(client->resp_notice, RT_IPC_CMD_RESET, RT_NULL);

    start_time = rt_tick_get();

    while (1)
    {
        /* Check whether it is timeout */
        if (rt_tick_get() - start_time > rt_tick_from_millisecond(timeout))
        {
            LOG_E("wait AT client(%s) connect timeout(%d tick).", client_name, timeout);
            result = -RT_ETIMEOUT;
            break;
        }

        /* Check whether it is already connected */
        resp->buf_len = 0;
        resp->line_counts = 0;
        at_utils_send(client->device, 0, "AT\r\n", 4);

        if (rt_sem_take(client->resp_notice, resp->timeout) != RT_EOK)
            continue;
        else
            break;
    }

    at_delete_resp(resp);

    client->resp = RT_NULL;

    rt_mutex_release(client->lock);

    return result;
}

/**
 * Send data to AT server, send data don't have end sign(eg: \r\n).
 *
 * @param client current AT client object
 * @param buf   send data buffer
 * @param size  send fixed data size
 *
 * @return >0: send data size
 *         =0: send failed
 */
rt_size_t at_client_obj_send(at_client_t client, const char *buf, rt_size_t size)
{
    rt_size_t len;

    RT_ASSERT(buf);

    if (client == RT_NULL)
    {
        LOG_E("input AT Client object is NULL, please create or get AT Client object!");
        return 0;
    }

#ifdef AT_PRINT_RAW_CMD
    at_print_raw_cmd("sendline", buf, size);
#endif

    rt_mutex_take(client->lock, RT_WAITING_FOREVER);

    len = at_utils_send(client->device, 0, buf, size);

    rt_mutex_release(client->lock);

    return len;
}

static rt_err_t at_client_getchar(at_client_t client, char *ch, rt_int32_t timeout)
{
    rt_err_t result = RT_EOK;

    while (rt_device_read(client->device, 0, ch, 1) == 0)
    {
        result = rt_sem_take(client->rx_notice, rt_tick_from_millisecond(timeout));
        if (result != RT_EOK)
        {
            return result;
        }

        rt_sem_control(client->rx_notice, RT_IPC_CMD_RESET, RT_NULL);
    }

    return RT_EOK;
}

/**
 * AT client receive fixed-length data.
 *
 * @param client current AT client object
 * @param buf   receive data buffer
 * @param size  receive fixed data size
 * @param timeout  receive data timeout (ms)
 *
 * @note this function can only be used in execution function of URC data
 *
 * @return >0: receive data size
 *         =0: receive failed
 */
rt_size_t at_client_obj_recv(at_client_t client, char *buf, rt_size_t size, rt_int32_t timeout)
{
    rt_size_t len = 0;

    RT_ASSERT(buf);

    if (client == RT_NULL)
    {
        LOG_E("input AT Client object is NULL, please create or get AT Client object!");
        return 0;
    }

    while (1)
    {
        rt_size_t read_len;

        rt_sem_control(client->rx_notice, RT_IPC_CMD_RESET, RT_NULL);

        read_len = rt_device_read(client->device, 0, buf + len, size);
        if(read_len > 0)
        {
            len += read_len;
            size -= read_len;
            if(size == 0)
                break;

            continue;
        }

        if(rt_sem_take(client->rx_notice, rt_tick_from_millisecond(timeout)) != RT_EOK)
            break;
    }

#ifdef AT_PRINT_RAW_CMD
    at_print_raw_cmd("urc_recv", buf, len);
#endif

    return len;
}

/**
 *  AT client set end sign.
 *
 * @param client current AT client object
 * @param ch the end sign, can not be used when it is '\0'
 */
void at_obj_set_end_sign(at_client_t client, char ch)
{
    if (client == RT_NULL)
    {
        LOG_E("input AT Client object is NULL, please create or get AT Client object!");
        return;
    }

    client->end_sign = ch;
}

/**
 * set URC(Unsolicited Result Code) table
 *
 * @param client current AT client object
 * @param table URC table
 * @param size table size
 */
int at_obj_set_urc_table(at_client_t client, const struct at_urc *urc_table, rt_size_t table_sz)
{
    rt_size_t idx;

    if (client == RT_NULL)
    {
        LOG_E("input AT Client object is NULL, please create or get AT Client object!");
        return -RT_ERROR;
    }

    for (idx = 0; idx < table_sz; idx++)
    {
        RT_ASSERT(urc_table[idx].cmd_prefix);
        RT_ASSERT(urc_table[idx].cmd_suffix);
    }

    if (client->urc_table_size == 0)
    {
        client->urc_table = (struct at_urc_table *) rt_calloc(1, sizeof(struct at_urc_table));
        if (client->urc_table == RT_NULL)
        {
            return -RT_ENOMEM;
        }

        client->urc_table[0].urc = urc_table;
        client->urc_table[0].urc_size = table_sz;
        client->urc_table_size++;
    }
    else
    {
        struct at_urc_table *new_urc_table = RT_NULL;

        /* realloc urc table space */
        new_urc_table = (struct at_urc_table *) rt_realloc(client->urc_table,client->urc_table_size * sizeof(struct at_urc_table) + sizeof(struct at_urc_table));
        if (new_urc_table == RT_NULL)
        {
            return -RT_ENOMEM;
        }
        client->urc_table = new_urc_table;
        client->urc_table[client->urc_table_size].urc = urc_table;
        client->urc_table[client->urc_table_size].urc_size = table_sz;
        client->urc_table_size++;

    }

    return RT_EOK;
}

/**
 * get AT client object by AT device name.
 *
 * @dev_name AT client device name
 *
 * @return AT client object
 */
at_client_t at_client_get(const char *dev_name)
{
    int idx = 0;

    RT_ASSERT(dev_name);

    for (idx = 0; idx < AT_CLIENT_NUM_MAX; idx++)
    {
        if (at_client_table[idx].device &&
        (rt_strcmp(at_client_table[idx].device->parent.name, dev_name) == 0))
        {
            return &at_client_table[idx];
        }
    }

    return RT_NULL;
}

/**
 * get first AT client object in the table.
 *
 * @return AT client object
 */
at_client_t at_client_get_first(void)
{
    if (at_client_table[0].device == RT_NULL)
    {
        return RT_NULL;
    }

    return &at_client_table[0];
}

static const struct at_urc *get_urc_obj(at_client_t client)
{
    rt_size_t i, j, prefix_len, suffix_len;
    rt_size_t bufsz;
    char *buffer = RT_NULL;
    const struct at_urc *urc = RT_NULL;
    struct at_urc_table *urc_table = RT_NULL;

    if (client->urc_table == RT_NULL)
    {
        return RT_NULL;
    }

    buffer = client->recv_line_buf;
    bufsz = client->recv_line_len;

    for (i = 0; i < client->urc_table_size; i++)
    {
        for (j = 0; j < client->urc_table[i].urc_size; j++)
        {
            urc_table = client->urc_table + i;
            urc = urc_table->urc + j;

            prefix_len = rt_strlen(urc->cmd_prefix);
            suffix_len = rt_strlen(urc->cmd_suffix);
            if (bufsz < prefix_len + suffix_len)
            {
                continue;
            }
            if ((prefix_len ? !rt_strncmp(buffer, urc->cmd_prefix, prefix_len) : 1)
                    && (suffix_len ? !rt_strncmp(buffer + bufsz - suffix_len, urc->cmd_suffix, suffix_len) : 1))
            {
                return urc;
            }
        }
    }

    return RT_NULL;
}

static int at_recv_readline(at_client_t client)
{
    rt_size_t read_len = 0;
    char ch = 0, last_ch = 0;
    rt_bool_t is_full = RT_FALSE;

    rt_memset(client->recv_line_buf, 0x00, client->recv_bufsz);
    client->recv_line_len = 0;

    while (1)
    {
        at_client_getchar(client, &ch, RT_WAITING_FOREVER);

        if (read_len < client->recv_bufsz)
        {
            client->recv_line_buf[read_len++] = ch;
            client->recv_line_len = read_len;
        }
        else
        {
            is_full = RT_TRUE;
        }

        /* is newline or URC data */
        if ((ch == '\n' && last_ch == '\r') || (client->end_sign != 0 && ch == client->end_sign)
                || get_urc_obj(client))
        {
            if (is_full)
            {
                LOG_E("read line failed. The line data length is out of buffer size(%d)!", client->recv_bufsz);
                rt_memset(client->recv_line_buf, 0x00, client->recv_bufsz);
                client->recv_line_len = 0;
                return -RT_EFULL;
            }
            break;
        }
        last_ch = ch;
    }

#ifdef AT_PRINT_RAW_CMD
    at_print_raw_cmd("recvline", client->recv_line_buf, read_len);
#endif

    return read_len;
}

static void client_parser(at_client_t client)
{
    const struct at_urc *urc;

    while(1)
    {
        if (at_recv_readline(client) > 0)
        {
            if ((urc = get_urc_obj(client)) != RT_NULL)
            {
                /* current receive is request, try to execute related operations */
                if (urc->func != RT_NULL)
                {
                    urc->func(client, client->recv_line_buf, client->recv_line_len);
                }
            }
            else if (client->resp != RT_NULL)
            {
                at_response_t resp = client->resp;

                char end_ch = client->recv_line_buf[client->recv_line_len - 1];

                /* current receive is response */
                client->recv_line_buf[client->recv_line_len - 1] = '\0';
                if (resp->buf_len + client->recv_line_len < resp->buf_size)
                {
                    /* copy response lines, separated by '\0' */
                    rt_memcpy(resp->buf + resp->buf_len, client->recv_line_buf, client->recv_line_len);

                    /* update the current response information */
                    resp->buf_len += client->recv_line_len;
                    resp->line_counts++;
                }
                else
                {
                    client->resp_status = AT_RESP_BUFF_FULL;
                    LOG_E("Read response buffer failed. The Response buffer size is out of buffer size(%d)!", resp->buf_size);
                }
                /* check response result */
                if ((client->end_sign != 0) && (end_ch == client->end_sign) && (resp->line_num == 0))
                {
                    /* get the end sign, return response state END_OK.*/
                    client->resp_status = AT_RESP_OK;
                }
                else if (rt_memcmp(client->recv_line_buf, AT_RESP_END_OK, rt_strlen(AT_RESP_END_OK)) == 0
                        && resp->line_num == 0)
                {
                    /* get the end data by response result, return response state END_OK. */
                    client->resp_status = AT_RESP_OK;
                }
                else if (rt_strstr(client->recv_line_buf, AT_RESP_END_ERROR)
                        || (rt_memcmp(client->recv_line_buf, AT_RESP_END_FAIL, rt_strlen(AT_RESP_END_FAIL)) == 0))
                {
                    client->resp_status = AT_RESP_ERROR;
                }
                else if (resp->line_counts == resp->line_num && resp->line_num)
                {
                    /* get the end data by response line, return response state END_OK.*/
                    client->resp_status = AT_RESP_OK;
                }
                else
                {
                    continue;
                }

                client->resp = RT_NULL;
                rt_sem_release(client->resp_notice);
            }
            else
            {
//                log_d("unrecognized line: %.*s", client->recv_line_len, client->recv_line_buf);
            }
        }
    }
}

static rt_err_t at_client_rx_ind(rt_device_t dev, rt_size_t size)
{
    int idx = 0;

    for (idx = 0; idx < AT_CLIENT_NUM_MAX; idx++)
    {
        if (at_client_table[idx].device == dev && size > 0)
        {
            rt_sem_release(at_client_table[idx].rx_notice);
        }
    }

    return RT_EOK;
}

/* initialize the client object parameters */
static int at_client_para_init(at_client_t client)
{
#define AT_CLIENT_LOCK_NAME            "at_c"
#define AT_CLIENT_SEM_NAME             "at_cs"
#define AT_CLIENT_RESP_NAME            "at_cr"
#define AT_CLIENT_THREAD_NAME          "at_clnt"

    int result = RT_EOK;
    static int at_client_num = 0;
    char name[RT_NAME_MAX];

    client->status = AT_STATUS_UNINITIALIZED;

    client->recv_line_len = 0;
    client->recv_line_buf = (char *) rt_calloc(1, client->recv_bufsz);
    if (client->recv_line_buf == RT_NULL)
    {
        LOG_E("AT client initialize failed! No memory for receive buffer.");
        result = -RT_ENOMEM;
        goto __exit;
    }

    rt_snprintf(name, RT_NAME_MAX, "%s%d", AT_CLIENT_LOCK_NAME, at_client_num);
    client->lock = rt_mutex_create(name, RT_IPC_FLAG_PRIO);
    if (client->lock == RT_NULL)
    {
        LOG_E("AT client initialize failed! at_client_recv_lock create failed!");
        result = -RT_ENOMEM;
        goto __exit;
    }

    rt_snprintf(name, RT_NAME_MAX, "%s%d", AT_CLIENT_SEM_NAME, at_client_num);
    client->rx_notice = rt_sem_create(name, 0, RT_IPC_FLAG_FIFO);
    if (client->rx_notice == RT_NULL)
    {
        LOG_E("AT client initialize failed! at_client_notice semaphore create failed!");
        result = -RT_ENOMEM;
        goto __exit;
    }

    rt_snprintf(name, RT_NAME_MAX, "%s%d", AT_CLIENT_RESP_NAME, at_client_num);
    client->resp_notice = rt_sem_create(name, 0, RT_IPC_FLAG_FIFO);
    if (client->resp_notice == RT_NULL)
    {
        LOG_E("AT client initialize failed! at_client_resp semaphore create failed!");
        result = -RT_ENOMEM;
        goto __exit;
    }

    client->urc_table = RT_NULL;
    client->urc_table_size = 0;

    rt_snprintf(name, RT_NAME_MAX, "%s%d", AT_CLIENT_THREAD_NAME, at_client_num);
    client->parser = rt_thread_create(name,
                                     (void (*)(void *parameter))client_parser,
                                     client,
                                     1024 + 512,
                                     RT_THREAD_PRIORITY_MAX / 3 - 1,
                                     5);
    if (client->parser == RT_NULL)
    {
        result = -RT_ENOMEM;
        goto __exit;
    }

__exit:
    if (result != RT_EOK)
    {
        if (client->lock)
        {
            rt_mutex_delete(client->lock);
        }

        if (client->rx_notice)
        {
            rt_sem_delete(client->rx_notice);
        }

        if (client->resp_notice)
        {
            rt_sem_delete(client->resp_notice);
        }

        if (client->device)
        {
            rt_device_close(client->device);
        }

        if (client->recv_line_buf)
        {
            rt_free(client->recv_line_buf);
        }

        rt_memset(client, 0x00, sizeof(struct at_client));
    }
    else
    {
        at_client_num++;
    }

    return result;
}

/**
 * AT client initialize.
 *
 * @param dev_name AT client device name
 * @param recv_bufsz the maximum number of receive buffer length
 *
 * @return 0 : initialize success
 *        -1 : initialize failed
 *        -5 : no memory
 */
int at_client_init(const char *dev_name,  rt_size_t recv_bufsz)
{
    int idx = 0;
    int result = RT_EOK;
    rt_err_t open_result = RT_EOK;
    at_client_t client = RT_NULL;

    RT_ASSERT(dev_name);
    RT_ASSERT(recv_bufsz > 0);

    if (at_client_get(dev_name) != RT_NULL)
    {
        return result;
    }

    for (idx = 0; idx < AT_CLIENT_NUM_MAX && at_client_table[idx].device; idx++);

    if (idx >= AT_CLIENT_NUM_MAX)
    {
        LOG_E("AT client initialize failed! Check the maximum number(%d) of AT client.", AT_CLIENT_NUM_MAX);
        result = -RT_EFULL;
        goto __exit;
    }

    client = &at_client_table[idx];
    client->recv_bufsz = recv_bufsz;

    result = at_client_para_init(client);
    if (result != RT_EOK)
    {
        goto __exit;
    }

    /* find and open command device */
    client->device = rt_device_find(dev_name);
    if (client->device)
    {
        RT_ASSERT(client->device->type == RT_Device_Class_Char);

        /* using DMA mode first */
        open_result = rt_device_open(client->device, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_DMA_RX);
        /* using interrupt mode when DMA mode not supported */
        if (open_result == -RT_EIO)
        {
            open_result = rt_device_open(client->device, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
        }
        RT_ASSERT(open_result == RT_EOK);

        rt_device_set_rx_indicate(client->device, at_client_rx_ind);
    }
    else
    {
        LOG_E("AT client initialize failed! Not find the device(%s).", dev_name);
        result = -RT_ERROR;
        goto __exit;
    }

__exit:
    if (result == RT_EOK)
    {
        client->status = AT_STATUS_INITIALIZED;

        rt_thread_startup(client->parser);

        LOG_I("AT client(V%s) on device %s initialize success.", AT_SW_VERSION, dev_name);
    }
    else
    {
        LOG_E("AT client(V%s) on device %s initialize failed(%d).", AT_SW_VERSION, dev_name, result);
    }

    return result;
}
#endif /* AT_USING_CLIENT */
