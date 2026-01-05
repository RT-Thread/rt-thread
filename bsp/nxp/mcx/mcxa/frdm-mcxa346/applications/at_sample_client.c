/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-07-06     chenyong     first version
 */

#include <stdlib.h>
#include <string.h>

#include <rtthread.h>
#include <at.h>

#define LOG_TAG              "at.sample"
#include <at_log.h>

#define AT_CMD_MAX_LEN	512

/* AT+CIFSR            Query local IP address and MAC */
int at_client_test(int argc, char **argv)
{
    at_response_t resp = RT_NULL;
    int result = 0;

    if (argc != 1)
    {
        LOG_E("at_client_test  - AT client send commands to AT server.");
        return -1;
    }

    resp = at_create_resp(256, 0, rt_tick_from_millisecond(5000));
    if (resp == RT_NULL)
    {
        LOG_E("No memory for response structure!");
        return -2;
    }

    /* close echo */
    at_exec_cmd(resp, "ATE0");

    result = at_exec_cmd(resp, "AT+CIFSR");
    if (result != RT_EOK)
    {
        LOG_E("AT client send commands failed or return response error!");
        goto __exit;
    }

    /* Print response line buffer */
    {
        const char *line_buffer = RT_NULL;

        LOG_D("Response buffer");

        for(rt_size_t line_num = 1; line_num <= resp->line_counts; line_num++)
        {
            if((line_buffer = at_resp_get_line(resp, line_num)) != RT_NULL)
            {
                LOG_D("line %d buffer : %s", line_num, line_buffer);
            }
            else
            {
                LOG_E("Parse line buffer error!");
            }
        }
    }

    {
        char resp_arg[AT_CMD_MAX_LEN] = { 0 };
        const char * resp_expr = "%*[^\"]\"%[^\"]\"";

        LOG_D(" Parse arguments");
        if (at_resp_parse_line_args(resp, 1, resp_expr, resp_arg) == 1)
        {
            LOG_D("Station IP  : %s", resp_arg);
            rt_memset(resp_arg, 0x00, AT_CMD_MAX_LEN);
        }
        else
        {
            LOG_E("Parse error, current line buff : %s", at_resp_get_line(resp, 4));
        }

        if (at_resp_parse_line_args(resp, 2, resp_expr, resp_arg) == 1)
        {
            LOG_D("Station MAC : %s", resp_arg);
        }
        else
        {
            LOG_E("Parse error, current line buff : %s", at_resp_get_line(resp, 5));
            goto __exit;
        }
    }
__exit:
    if(resp)
    {
        at_delete_resp(resp);
    }

    return result;
}

int at_client_test_init(int argc, char **argv)
{
#define AT_CLIENT_RECV_BUFF_LEN   1024
#define AT_CLIENT_SEND_BUFF_LEN   512
    if (argc != 2)
    {
        rt_kprintf("at_client_init <dev_name>   -- AT client initialize.\n");
        return -RT_ERROR;
    }

    at_client_init(argv[1], AT_CLIENT_RECV_BUFF_LEN, AT_CLIENT_SEND_BUFF_LEN);

    return RT_EOK;
}
#ifdef FINSH_USING_MSH
#include <finsh.h>
MSH_CMD_EXPORT(at_client_test, AT client send cmd and get response);
MSH_CMD_EXPORT_ALIAS(at_client_test_init, at_client_init, initialize AT client);
#endif