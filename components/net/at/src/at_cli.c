/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-04-02     armink       first version
 */

#include <at.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>

#ifdef AT_USING_CLI

#define AT_CLI_FIFO_SIZE                      256

static struct rt_semaphore console_rx_notice;
static struct rt_ringbuffer *console_rx_fifo = RT_NULL;
static rt_err_t (*odev_rx_ind)(rt_device_t dev, rt_size_t size) = RT_NULL;

#ifdef AT_USING_CLIENT
static struct rt_semaphore client_rx_notice;
static struct rt_ringbuffer *client_rx_fifo = RT_NULL;
#endif

static char console_getchar(void)
{
    char ch;

    rt_sem_take(&console_rx_notice, RT_WAITING_FOREVER);
    rt_ringbuffer_getchar(console_rx_fifo, (rt_uint8_t *)&ch);

    return ch;
}

static rt_err_t console_getchar_rx_ind(rt_device_t dev, rt_size_t size)
{
    uint8_t ch;
    rt_size_t i;

    for (i = 0; i < size; i++)
    {
        /* read a char */
        if (rt_device_read(dev, 0, &ch, 1))
        {
            rt_ringbuffer_put_force(console_rx_fifo, &ch, 1);
            rt_sem_release(&console_rx_notice);
        }
    }

    return RT_EOK;
}

void at_cli_init(void)
{
    rt_base_t level;
    rt_device_t console;

    rt_sem_init(&console_rx_notice, "cli_c", 0, RT_IPC_FLAG_FIFO);

    /* create RX FIFO */
    console_rx_fifo = rt_ringbuffer_create(AT_CLI_FIFO_SIZE);
    /* created must success */
    RT_ASSERT(console_rx_fifo);

    level = rt_hw_interrupt_disable();
    console = rt_console_get_device();
    if (console)
    {
        /* backup RX indicate */
        odev_rx_ind = console->rx_indicate;
        rt_device_set_rx_indicate(console, console_getchar_rx_ind);
    }

    rt_hw_interrupt_enable(level);
}

void at_cli_deinit(void)
{
    rt_base_t level;
    rt_device_t console;

    level = rt_hw_interrupt_disable();
    console = rt_console_get_device();
    if (console && odev_rx_ind)
    {
        /* restore RX indicate */
        rt_device_set_rx_indicate(console, odev_rx_ind);
    }
    rt_hw_interrupt_enable(level);

    rt_sem_detach(&console_rx_notice);
    rt_ringbuffer_destroy(console_rx_fifo);
}

#ifdef AT_USING_SERVER
static rt_err_t at_server_console_getchar(struct at_server *server, char *ch, rt_int32_t timeout)
{
    *ch = console_getchar();
    return RT_EOK;
}

static void server_cli_parser(void)
{
    extern at_server_t at_get_server(void);

    at_server_t server = at_get_server();
    rt_base_t level;
    static rt_device_t device_bak;
    static rt_err_t (*getchar_bak)(struct at_server *server, char *ch, rt_int32_t timeout);

    /* backup server device and getchar function */
    {
        level = rt_hw_interrupt_disable();

        device_bak = server->device;
        getchar_bak = server->get_char;

        /* setup server device as console device */
        server->device = rt_console_get_device();
        server->get_char = at_server_console_getchar;

        rt_hw_interrupt_enable(level);
    }

    if (server)
    {
        rt_kprintf("======== Welcome to using RT-Thread AT command server cli ========\n");
        rt_kprintf("Input your at command for test server. Press 'ESC' to exit.\n");
        server->parser_entry(server);
    }
    else
    {
        rt_kprintf("AT client not initialized\n");
    }

    /* restore server device and getchar function */
    {
        level = rt_hw_interrupt_disable();

        server->device = device_bak;
        server->get_char = getchar_bak;

        rt_hw_interrupt_enable(level);
    }
}
#endif /* AT_USING_SERVER */

#ifdef AT_USING_CLIENT
static char client_getchar(void)
{
    char ch;

    rt_sem_take(&client_rx_notice, RT_WAITING_FOREVER);
    rt_ringbuffer_getchar(client_rx_fifo, (rt_uint8_t *)&ch);

    return ch;
}

static void at_client_entry(void *param)
{
    char ch;

    while(1)
    {
        ch = client_getchar();
        rt_kprintf("%c", ch);
    }
}

static rt_err_t client_getchar_rx_ind(rt_device_t dev, rt_size_t size)
{
    uint8_t ch;
    rt_size_t i;

    for (i = 0; i < size; i++)
    {
        /* read a char */
        if (rt_device_read(dev, 0, &ch, 1))
        {
            rt_ringbuffer_put_force(client_rx_fifo, &ch, 1);
            rt_sem_release(&client_rx_notice);
        }
    }

    return RT_EOK;
}
static void client_cli_parser(at_client_t  client)
{
#define ESC_KEY                 0x1B
#define BACKSPACE_KEY           0x08
#define DELECT_KEY              0x7F

    char ch;
    char cur_line[FINSH_CMD_SIZE] = { 0 };
    rt_size_t cur_line_len = 0;
    static rt_err_t (*client_odev_rx_ind)(rt_device_t dev, rt_size_t size) = RT_NULL;
    rt_base_t level;
    rt_thread_t at_client;
    at_status_t client_odev_status;

    if (client)
    {
        /* backup client status */
        {
            client_odev_status = client->status;
            client->status = AT_STATUS_CLI;
        }

        rt_sem_init(&client_rx_notice, "cli_r", 0, RT_IPC_FLAG_FIFO);
        client_rx_fifo = rt_ringbuffer_create(AT_CLI_FIFO_SIZE);

        /* backup client device RX indicate */
        {
            level = rt_hw_interrupt_disable();
            client_odev_rx_ind = client->device->rx_indicate;
            rt_device_set_rx_indicate(client->device, client_getchar_rx_ind);
            rt_hw_interrupt_enable(level);
        }

        at_client = rt_thread_create("at_cli", at_client_entry, RT_NULL, 512, 8, 8);
        if (client_rx_fifo && at_client)
        {
            rt_kprintf("======== Welcome to using RT-Thread AT command client cli ========\n");
            rt_kprintf("Cli will forward your command to server port(%s). Press 'ESC' to exit.\n", client->device->parent.name);
            rt_thread_startup(at_client);
            /* process user input */
            while (ESC_KEY != (ch = console_getchar()))
            {
                if (ch == BACKSPACE_KEY || ch == DELECT_KEY)
                {
                    if (cur_line_len)
                    {
                        cur_line[--cur_line_len] = 0;
                        rt_kprintf("\b \b");
                    }
                    continue;
                }
                else if (ch == '\r' || ch == '\n')
                {
                    /* execute a AT request */
                    if (cur_line_len)
                    {
                        rt_kprintf("\n");
                        at_obj_exec_cmd(client, RT_NULL, "%.*s", cur_line_len, cur_line);
                    }
                    cur_line_len = 0;
                }
                else
                {
                    if(cur_line_len >= FINSH_CMD_SIZE)
                    {
                        continue;
                    }
                    rt_kprintf("%c", ch);
                    cur_line[cur_line_len++] = ch;
                }
            }

            /* restore client status */
            client->status = client_odev_status;

            /* restore client device RX indicate */
            {
                level = rt_hw_interrupt_disable();
                rt_device_set_rx_indicate(client->device, client_odev_rx_ind);
                rt_hw_interrupt_enable(level);
            }

            rt_thread_delete(at_client);
            rt_sem_detach(&client_rx_notice);
            rt_ringbuffer_destroy(client_rx_fifo);
        }
        else
        {
            rt_kprintf("No mem for AT cli client\n");
        }
    }
    else
    {
        rt_kprintf("AT client not initialized\n");
    }
}
#endif /* AT_USING_CLIENT */

static void at(int argc, char **argv)
{

    if (argc != 2 && argc != 3)
    {
        rt_kprintf("Please input '<server|client [dev_name]>' \n");
        return;
    }

    at_cli_init();

    if (!strcmp(argv[1], "server"))
    {
#ifdef AT_USING_SERVER
        server_cli_parser();
#else
        rt_kprintf("Not support AT server, please check your configure!\n");
#endif /* AT_USING_SERVER */
    }
    else if (!strcmp(argv[1], "client"))
    {
#ifdef AT_USING_CLIENT
        at_client_t client = RT_NULL;

        if (argc == 2)
        {
            client_cli_parser(at_client_get_first());
        }
        else if (argc == 3)
        {
            client = at_client_get(argv[2]);
            if (client == RT_NULL)
            {
                rt_kprintf("input AT client device name(%s) error.\n", argv[2]);
            }
            else
            {
                client_cli_parser(client);
            }
        }
#else
        rt_kprintf("Not support AT client, please check your configure!\n");
#endif /* AT_USING_CLIENT */
    }
    else
    {
        rt_kprintf("Please input '<server|client [dev_name]>' \n");
    }

    at_cli_deinit();
}
MSH_CMD_EXPORT(at, RT-Thread AT component cli: at <server|client [dev_name]>);

#endif /* AT_USING_CLI */
