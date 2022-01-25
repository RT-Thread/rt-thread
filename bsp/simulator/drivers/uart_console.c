/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <stdio.h>
#include <rthw.h>
#include <rtdevice.h>
#include <rtthread.h>
#include <rtdevice.h>

/* uart driver */
struct console_uart
{
    int rx_ready;

    struct rt_ringbuffer rb;
    rt_uint8_t rx_buffer[256];
} _console_uart;
static struct rt_serial_device _serial;

#define SAVEKEY(key)  do { char ch = key; rt_ringbuffer_put_force(&(_console_uart.rb), &ch, 1); } while (0)

#ifdef _WIN32
#include  <windows.h>
#include  <mmsystem.h>
#include  <conio.h>

/*
 * Handler for OSKey Thread
 */
static HANDLE       OSKey_Thread;
static DWORD        OSKey_ThreadID;

static DWORD WINAPI ThreadforKeyGet(LPVOID lpParam);
void console_lowlevel_init(void)
{
    /*
     * create serial thread that receive key input from keyboard
     */

    OSKey_Thread = CreateThread(NULL,
                                0,
                                (LPTHREAD_START_ROUTINE)ThreadforKeyGet,
                                0,
                                CREATE_SUSPENDED,
                                &OSKey_ThreadID);
    if (OSKey_Thread == NULL)
    {
        //Display Error Message
        return;
    }

    SetThreadPriority(OSKey_Thread,
                      THREAD_PRIORITY_NORMAL);
    SetThreadPriorityBoost(OSKey_Thread,
                           TRUE);
    SetThreadAffinityMask(OSKey_Thread,
                          0x01);
    /*
     * Start OS get key Thread
     */
    ResumeThread(OSKey_Thread);
}

static DWORD WINAPI ThreadforKeyGet(LPVOID lpParam)
#else /* POSIX version */

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h> /* for tcxxxattr, ECHO, etc */
#include <unistd.h> /* for STDIN_FILENO */

static void * ThreadforKeyGet(void * lpParam);
static pthread_t OSKey_Thread;

void console_lowlevel_init(void)
{
    int res;

    res = pthread_create(&OSKey_Thread, NULL, &ThreadforKeyGet, NULL);
    if (res)
    {
        printf("pthread create faild, <%d>\n", res);
        exit(EXIT_FAILURE);
    }
}

static struct termios oldt, newt;
/*simulate windows' getch(), it works!!*/
static void set_stty(void)
{
    /* get terminal input's attribute */
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    /* set termios' local mode */
    newt.c_lflag &= ~(ECHO|ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void restore_stty(void)
{
   /* recover terminal's attribute */
   tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

#define getch  getchar
static void * ThreadforKeyGet(void * lpParam)
#endif /* not _WIN32*/
{
 /*
 * left  key(��)�� 0xe04b
 * up    key(��)�� 0xe048
 * right key(��)�� 0xe04d
 * down  key(��)�� 0xe050
 */
    unsigned char key;

#ifndef _WIN32
    sigset_t  sigmask, oldmask;
    /* set the getchar without buffer */
    sigfillset(&sigmask);
    pthread_sigmask(SIG_BLOCK, &sigmask, &oldmask);
    set_stty();
#endif

    (void)lpParam;              //prevent compiler warnings

    for (;;)
    {
        key = getch();
#ifdef _WIN32
        if (key == 0xE0)
        {
            key = getch();

            if (key == 0x48) //up key , 0x1b 0x5b 0x41
            {
                SAVEKEY(0x1b);
                SAVEKEY(0x5b);
                SAVEKEY(0x41);
            }
            else if (key == 0x50)//0x1b 0x5b 0x42
            {
                SAVEKEY(0x1b);
                SAVEKEY(0x5b);
                SAVEKEY(0x42);
            }
            else if (key == 0x4b)//<- 0x1b 0x5b 0x44
            {
                SAVEKEY(0x1b);
                SAVEKEY(0x5b);
                SAVEKEY(0x44);
            }
            else if (key == 0x4d)//<- 0x1b 0x5b 0x43
            {
                SAVEKEY(0x1b);
                SAVEKEY(0x5b);
                SAVEKEY(0x43);
            }

            continue;
        }
#endif
        SAVEKEY(key);

        /* Notfiy serial ISR */
        rt_hw_serial_isr(&_serial, RT_SERIAL_EVENT_RX_IND);
    }
} /*** ThreadforKeyGet ***/

static rt_err_t console_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    /* no baudrate, nothing */

    return RT_EOK;
}

static rt_err_t console_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct console_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct console_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        uart->rx_ready = 0;
        break;
    case RT_DEVICE_CTRL_SET_INT:
        uart->rx_ready = 1;
        break;
    }

    return RT_EOK;
}

static int console_putc(struct rt_serial_device *serial, char c)
{
    int level;
    struct console_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct console_uart *)serial->parent.user_data;

#if 0 /* Enable it if you want to save the console log */
    {
        static FILE* fp = NULL;

        if (fp == NULL)
            fp = fopen("log.txt", "wb+");

        if (fp != NULL)
            fwrite(buffer, size, 1, fp);
    }
#endif

    level = rt_hw_interrupt_disable();
    fwrite(&c, 1, 1, stdout);
    fflush(stdout);
    rt_hw_interrupt_enable(level);
    return 1;
}

static int console_getc(struct rt_serial_device *serial)
{
    char ch;
    struct console_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct console_uart *)serial->parent.user_data;

    if (rt_ringbuffer_getchar(&(uart->rb), &ch)) return ch;

    return -1;
}

static const struct rt_uart_ops console_uart_ops =
{
    console_configure,
    console_control,
    console_putc,
    console_getc,
};

int uart_console_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    struct console_uart* uart;
    struct rt_serial_device* serial;

    uart = &_console_uart;
    serial = &_serial;

    uart->rx_ready = 0;

    serial->ops    = &console_uart_ops;
    serial->config = config;
    /* initialize ring buffer */
    rt_ringbuffer_init(&uart->rb, uart->rx_buffer, sizeof(uart->rx_buffer));

    /* register UART device */
    rt_hw_serial_register(serial, "console",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);

    console_lowlevel_init();

    return 0;
}
