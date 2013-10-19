/*
 * File      : serial.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-09-25     prife        first implementation
 * 2013-01-15     prife        support linux
 * 2013-02-6      prife        rewrite to fit the new serial.c
 */
#include  <rthw.h>
#include  <rtthread.h>

#ifdef _WIN32
#include  <windows.h>
#include  <mmsystem.h>
#include  <conio.h>
#endif

#include  <stdio.h>
#include "serial.h"

struct serial_device serial1;

#define SAVEKEY(key)  seial_save_byte(key, &serial1)
#ifdef _WIN32
/*
 * Handler for OSKey Thread
 */
static HANDLE       OSKey_Thread;
static DWORD        OSKey_ThreadID;

static DWORD WINAPI ThreadforKeyGet(LPVOID lpParam);
void rt_hw_usart_init(void)
{
    rt_hw_serial_init(&serial1, RT_CONSOLE_DEVICE_NAME);
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

#else /* POSIX version */

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h> /* for tcxxxattr, ECHO, etc */
#include <unistd.h> /* for STDIN_FILENO */

static void * ThreadforKeyGet(void * lpParam);
static pthread_t OSKey_Thread;
void rt_hw_usart_init(void)
{
    int res;

    rt_hw_serial_init(&serial1, RT_CONSOLE_DEVICE_NAME);
    res = pthread_create(&OSKey_Thread, NULL, &ThreadforKeyGet, NULL);
    if (res)
    {
        printf("pthread create faild, <%d>\n", res);
        exit(EXIT_FAILURE);
    }
}
#endif

#ifdef _WIN32
static DWORD WINAPI ThreadforKeyGet(LPVOID lpParam)
#else

static struct termios oldt, newt;
/*simulate windows' getch(), it works!!*/
void set_stty(void)
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
 * 方向键(←)： 0xe04b
 * 方向键(↑)： 0xe048
 * 方向键(→)： 0xe04d
 * 方向键(↓)： 0xe050
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
    }
} /*** ThreadforKeyGet ***/
