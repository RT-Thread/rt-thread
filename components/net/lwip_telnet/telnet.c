/*
 * File      : telnet.c
 *             A simple telnet server implementation
 *
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013-2015, Shanghai Real-Thread Technology Co., Ltd
 * http://www.rt-thread.com
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
 */
#include "lwip/sockets.h"
#include <finsh.h>
#include <shell.h>
#include "telnet.h"

#define TELNET_PORT         23
#define TELNET_RX_BUFFER    256
#define TELNET_TX_BUFFER    1500

#define ISO_nl              0x0a
#define ISO_cr              0x0d

#define STATE_NORMAL        0
#define STATE_IAC           1
#define STATE_WILL          2
#define STATE_WONT          3
#define STATE_DO            4
#define STATE_DONT          5
#define STATE_CLOSE         6

#define TELNET_IAC          255
#define TELNET_WILL         251
#define TELNET_WONT         252
#define TELNET_DO           253
#define TELNET_DONT         254

#define MAX_CMD_LENS        40

struct telnet_session
{
    struct rt_ringbuffer rx_ringbuffer;
    struct rt_ringbuffer tx_ringbuffer;

    rt_sem_t rx_ringbuffer_lock;
    rt_sem_t tx_ringbuffer_lock;

    struct rt_device device;
    rt_device_t      default_console;
  
    /* telnet protocol */
    rt_uint8_t state;
    rt_uint8_t echo_mode;
};
struct telnet_session* telnet;

/*******************RT-Thread Device Driver Interface***************************/
static rt_err_t telnet_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t telnet_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t telnet_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t telnet_read(rt_device_t dev, rt_off_t pos, void* buffer,
                             rt_size_t size)
{
    rt_size_t result;

    /* read from rx ring buffer */
    rt_sem_take(telnet->rx_ringbuffer_lock, RT_WAITING_FOREVER);
    result = rt_ringbuffer_get(&(telnet->rx_ringbuffer), buffer, size);
    rt_sem_release(telnet->rx_ringbuffer_lock);

    return result;
}

static rt_size_t telnet_write (rt_device_t dev, rt_off_t pos,
                               const void* buffer, rt_size_t size)
{
    const rt_uint8_t *ptr;

    ptr = (rt_uint8_t*)buffer;

    rt_sem_take(telnet->tx_ringbuffer_lock, RT_WAITING_FOREVER);

    while (size)
    {
        if (*ptr == '\n')
            rt_ringbuffer_putchar(&telnet->tx_ringbuffer, '\r');

        if (rt_ringbuffer_putchar(&telnet->tx_ringbuffer, *ptr) == 0)  /* overflow */
            break;
        ptr ++;
        size --;
    }
    rt_sem_release(telnet->tx_ringbuffer_lock);

    return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static rt_err_t telnet_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    return RT_EOK;
}

static void telnet_device_init(void)
{
    if (telnet == RT_NULL)
    {
        rt_uint8_t *ptr;

        telnet = rt_malloc (sizeof(struct telnet_session));
        if (telnet == RT_NULL)
        {
            rt_kprintf("telnet: no memory\n");
            return;
        }

        /* init ringbuffer */
        ptr = rt_malloc (TELNET_RX_BUFFER);
        rt_ringbuffer_init(&telnet->rx_ringbuffer, ptr, TELNET_RX_BUFFER);
        /* create rx ringbuffer lock */
        telnet->rx_ringbuffer_lock = rt_sem_create("rxrb", 1, RT_IPC_FLAG_FIFO);
        ptr = rt_malloc (TELNET_TX_BUFFER);
        rt_ringbuffer_init(&telnet->tx_ringbuffer, ptr, TELNET_TX_BUFFER);
        /* create tx ringbuffer lock */
        telnet->tx_ringbuffer_lock = rt_sem_create("txrb", 1, RT_IPC_FLAG_FIFO);
    }

    /* register telnet device */
    telnet->device.type     = RT_Device_Class_Char;
    telnet->device.init     = telnet_init;
    telnet->device.open     = telnet_open;
    telnet->device.close    = telnet_close;
    telnet->device.read     = telnet_read;
    telnet->device.write    = telnet_write;
    telnet->device.control  = telnet_control;

    /* no private */
    telnet->device.user_data = RT_NULL;

    /* register telnet device */
    rt_device_register(&telnet->device, "telnet",
                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STREAM);
}

/****************************************************************************/
static void telnet_send_option(struct telnet_session* telnet, rt_uint8_t option,
                               rt_uint8_t value)
{
    rt_uint8_t optbuf[4];

    optbuf[0] = TELNET_IAC;
    optbuf[1] = option;
    optbuf[2] = value;
    optbuf[3] = 0;

    rt_sem_take(telnet->tx_ringbuffer_lock, RT_WAITING_FOREVER);
    rt_ringbuffer_put(&telnet->tx_ringbuffer, optbuf, 3);
    rt_sem_release(telnet->tx_ringbuffer_lock);
}

static void telnet_process_tx(struct telnet_session* telnet, int socket)
{
    rt_size_t length;
    rt_uint8_t tx_buffer[256];

    while (1)
    {
        rt_memset(tx_buffer, 0, sizeof(tx_buffer));
        rt_sem_take(telnet->tx_ringbuffer_lock, RT_WAITING_FOREVER);
        /* get buffer from ringbuffer */
        length = rt_ringbuffer_get(&(telnet->tx_ringbuffer), tx_buffer,
                                   sizeof(tx_buffer));
        rt_sem_release(telnet->tx_ringbuffer_lock);

        /* do a tx procedure */
        if (length > 0)
        {
            send(socket, tx_buffer, length, 0);
        }
        else break;
    }
}

static void telnet_process_rx(struct telnet_session* telnet, rt_uint8_t *data,
                       rt_size_t length)
{
    rt_size_t rx_length, index;

    for (index = 0; index < length; index ++)
    {
        switch(telnet->state)
        {
            case STATE_IAC:
                if (*data == TELNET_IAC)
                {
                    /* take semaphore */
                    rt_sem_take(telnet->rx_ringbuffer_lock, RT_WAITING_FOREVER);
                    /* put buffer to ringbuffer */
                    rt_ringbuffer_putchar(&(telnet->rx_ringbuffer), *data);
                    /* release semaphore */
                    rt_sem_release(telnet->rx_ringbuffer_lock);

                    telnet->state = STATE_NORMAL;
                }
                else
                {
                    /* set telnet state according to received package */
                    switch (*data)
                    {
                        case TELNET_WILL:
                            telnet->state = STATE_WILL;
                            break;
                        case TELNET_WONT:
                            telnet->state = STATE_WONT;
                            break;
                        case TELNET_DO:
                            telnet->state = STATE_DO;
                            break;
                        case TELNET_DONT:
                            telnet->state = STATE_DONT;
                            break;
                        default:
                            telnet->state = STATE_NORMAL;
                            break;
                    }
                }
                break;

            /* don't option */
            case STATE_WILL:
            case STATE_WONT:
                telnet_send_option(telnet, TELNET_DONT, *data);
                telnet->state = STATE_NORMAL;
                break;

            /* won't option */
            case STATE_DO:
            case STATE_DONT:
                telnet_send_option(telnet, TELNET_WONT, *data);
                telnet->state = STATE_NORMAL;
                break;

            case STATE_NORMAL:
                if (*data == TELNET_IAC) telnet->state = STATE_IAC;
                else if (*data != '\r') /* ignore '\r' */
                {
                    rt_sem_take(telnet->rx_ringbuffer_lock, RT_WAITING_FOREVER);
                    /* put buffer to ringbuffer */
                    rt_ringbuffer_putchar(&(telnet->rx_ringbuffer), *data);
                    rt_sem_release(telnet->rx_ringbuffer_lock);
                }
                break;
        }

        data ++;
    }

    rt_sem_take(telnet->rx_ringbuffer_lock, RT_WAITING_FOREVER);
    /* get total size */
    rx_length = rt_ringbuffer_data_len(&telnet->rx_ringbuffer);
    rt_sem_release(telnet->rx_ringbuffer_lock);

    /* indicate there are reception data */
    if ((rx_length > 0) && (telnet->device.rx_indicate != RT_NULL))
        telnet->device.rx_indicate(&telnet->device,
                                   rx_length);

    return;
}

static rt_int32_t rtu_telnet_srv_tcp_init(const rt_int16_t local_port ,
                                   rt_int32_t nb_connection)
{
    rt_uint8_t data_buffer[MAX_CMD_LENS] = {0};
    struct sockaddr_in  server_addr;
    socklen_t addr_len;
    struct sockaddr_in conn_addr;

    int rc           = 0 ;
    int optval       = 1;
    int sock_fd      = -1  ;
    int sock_conn    = -1  ;

    fd_set readset;
    struct timeval timeout;

    timeout.tv_sec = 0;         // second.
    timeout.tv_usec = 50 * 1000; //wait micro second.

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd == -1 )
    {
        return -RT_ERROR;
    }

    setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(sock_fd, SOL_SOCKET , SO_KEEPALIVE, &optval, sizeof(optval));

    rt_memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(local_port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    if (bind(sock_fd, (struct sockaddr *)&server_addr,
             sizeof(struct sockaddr)) == -1)
    {
        closesocket(sock_fd);

        return -RT_ERROR;
    }

    if ((listen(sock_fd, nb_connection)) == -1)
    {
        closesocket(sock_fd);

        return -RT_ERROR;
    }

    addr_len = sizeof(struct sockaddr_in);

    while(1)
    {
        sock_conn = accept(sock_fd, (struct sockaddr *)&conn_addr, &addr_len);

        if(sock_conn > 0)
        {
            telnet->default_console = rt_console_get_device();
          
            rt_console_set_device("telnet");
            finsh_set_device("telnet");
            
            /* set init state */
            telnet->state = STATE_NORMAL;

            /* disable echo mode */
            finsh_set_echo(1);

            telnet->echo_mode = finsh_get_echo();

            while (1)
            {
                telnet_process_tx(telnet , sock_conn);

                FD_ZERO(&readset);
                FD_SET(sock_conn , &readset);

                if( (rc = lwip_select(sock_conn + 1 , &readset , NULL , 0 , &timeout)) == 0 )
                    continue;

                if(rc < 0) break;

                rc = recv(sock_conn, data_buffer, MAX_CMD_LENS , MSG_DONTWAIT);

                if(rc > 0)
                {
                    telnet_process_rx(telnet, data_buffer, rc);
                }
                else
                {
                    rt_console_set_device(telnet->default_console->parent.name);
                    finsh_set_device(telnet->default_console->parent.name);
                  
                    break;
                }

                rt_thread_delay(1);
            }

            closesocket(sock_conn);
            sock_conn = -1;
        }

        rt_thread_delay(10);
    }
}


static void rtu_telnet_thread_entry(void* parm)
{
    rtu_telnet_srv_tcp_init(TELNET_PORT , 1);
}

rt_err_t rtu_telnet_init(void)
{
    rt_thread_t tid = RT_NULL;

    telnet_device_init();

    tid = rt_thread_create("telnet",
                           rtu_telnet_thread_entry, RT_NULL,
                           1024, 24 , 20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);
    else
        return RT_ERROR;

    return RT_EOK;
}

#ifdef FINSH_USING_MSH
#include <finsh.h>
MSH_CMD_EXPORT(rtu_telnet_init               , rtu_telnet_init.);
#endif
