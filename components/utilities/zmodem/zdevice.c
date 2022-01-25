/*
 * File      : zdevice.c
 * the implemention of zmodem protocol.
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-29     itspy
 */

#include <rtthread.h>
#include <finsh.h>
#include <shell.h>
#include <rtdef.h>
#include <dfs.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include "zdef.h"


rt_uint32_t Line_left  = 0;          /* left number of data in the read line buffer*/
rt_uint32_t Left_sizes = 0;          /* left file sizes */
rt_uint32_t Baudrate   = BITRATE;    /* console baudrate */



rt_uint32_t get_device_baud(void)
{
    return(Baudrate);
}

rt_uint32_t get_sys_time(void)
{
    return(0L);
}

void zsend_byte(rt_uint16_t ch)
{
    rt_device_write(zmodem.device, 0, &ch,1);

    return;
}

void zsend_line(rt_uint16_t c)
{
    rt_uint16_t ch;

    ch = (c & 0377);
    rt_device_write(zmodem.device, 0, &ch, 1);

    return;
}

rt_int16_t zread_line(rt_uint16_t timeout)
{
    char *str;
    static char buf[10];

    if (Line_left > 0)
    {
        Line_left -= 1;
        return (*str++ & 0377);
    }
    Line_left = 0;
    timeout/=5;
    while (1)
    {
        Line_left = rt_device_read(shell->device, 0, buf, 1);
        if (Line_left)
        {
             Line_left = Line_left;
             str = buf;
             break;
        }
    }
    if (Line_left < 1) return TIMEOUT;
    Line_left -=1;

    return (*str++ & 0377);
}

/*
 * send a string to the modem, processing for \336 (sleep 1 sec)
 *   and \335 (break signal)
 */
void zsend_break(char *cmd)
{

    while (*cmd++)
    {
        switch (*cmd)
        {
        case '\336':
             continue;
        case '\335':
             rt_thread_delay(RT_TICK_PER_SECOND);
             continue;
        default:
             zsend_line(*cmd);
             break;
        }
    }
}
/* send cancel string to get the other end to shut up */
void zsend_can(void)
{
    static char cmd[] = {24,24,24,24,24,24,24,24,24,24,0};

    zsend_break(cmd);
    rt_kprintf("\x0d");
    Line_left=0;           /* clear Line_left */

    return;
}

/* end of zdevice.c */
