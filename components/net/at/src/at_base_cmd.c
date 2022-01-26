/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-04-01     armink       first version
 * 2018-04-04     chenyong     add base commands
 */

#include <at.h>
#include <stdlib.h>
#include <string.h>

#include <rtdevice.h>

#ifdef AT_USING_SERVER

#define AT_ECHO_MODE_CLOSE             0
#define AT_ECHO_MODE_OPEN              1

extern at_server_t at_get_server(void);

static at_result_t at_exec(void)
{
    return AT_RESULT_OK;
}
AT_CMD_EXPORT("AT", RT_NULL, RT_NULL, RT_NULL, RT_NULL, at_exec);

static at_result_t atz_exec(void)
{
    at_server_printfln("OK");

    at_port_factory_reset();

    return AT_RESULT_NULL;
}
AT_CMD_EXPORT("ATZ", RT_NULL, RT_NULL, RT_NULL, RT_NULL, atz_exec);

static at_result_t at_rst_exec(void)
{
    at_server_printfln("OK");

    at_port_reset();

    return AT_RESULT_NULL;
}
AT_CMD_EXPORT("AT+RST", RT_NULL, RT_NULL, RT_NULL, RT_NULL, at_rst_exec);

static at_result_t ate_setup(const char *args)
{
    int echo_mode = atoi(args);

    if(echo_mode == AT_ECHO_MODE_CLOSE || echo_mode == AT_ECHO_MODE_OPEN)
    {
        at_get_server()->echo_mode = echo_mode;
    }
    else
    {
        return AT_RESULT_FAILE;
    }

    return AT_RESULT_OK;
}
AT_CMD_EXPORT("ATE", "<value>", RT_NULL, RT_NULL, ate_setup, RT_NULL);

static at_result_t at_show_cmd_exec(void)
{
    extern void rt_at_server_print_all_cmd(void);

    rt_at_server_print_all_cmd();

    return AT_RESULT_OK;
}
AT_CMD_EXPORT("AT&L", RT_NULL, RT_NULL, RT_NULL, RT_NULL, at_show_cmd_exec);

static at_result_t at_uart_query(void)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)at_get_server()->device;

    at_server_printfln("AT+UART=%d,%d,%d,%d,%d", serial->config.baud_rate, serial->config.data_bits,
            serial->config.stop_bits, serial->config.parity, 1);

    return AT_RESULT_OK;
}

static at_result_t at_uart_setup(const char *args)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    int baudrate, databits, stopbits, parity, flow_control, argc;
    const char *req_expr = "=%d,%d,%d,%d,%d";

    argc = at_req_parse_args(args, req_expr, &baudrate, &databits, &stopbits, &parity, &flow_control);
    if (argc != 5)
    {
        return AT_RESULT_PARSE_FAILE;
    }

    at_server_printfln("UART baudrate : %d", baudrate);
    at_server_printfln("UART databits : %d", databits);
    at_server_printfln("UART stopbits : %d", stopbits);
    at_server_printfln("UART parity   : %d", parity);
    at_server_printfln("UART control  : %d", flow_control);

    config.baud_rate = baudrate;
    config.data_bits = databits;
    config.stop_bits = stopbits;
    config.parity = parity;

    if(rt_device_control(at_get_server()->device, RT_DEVICE_CTRL_CONFIG, &config) != RT_EOK)
    {
        return AT_RESULT_FAILE;
    }

    return AT_RESULT_OK;
}

AT_CMD_EXPORT("AT+UART", "=<baudrate>,<databits>,<stopbits>,<parity>,<flow_control>", RT_NULL, at_uart_query, at_uart_setup, RT_NULL);

#endif /* AT_USING_SERVER */
