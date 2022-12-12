/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-15     Meco Man     first version
 */

#include <rtthread.h>

#define DBG_TAG    "stdlib"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

void __rt_libc_exit(int status)
{
    rt_thread_t self = rt_thread_self();

    if (self != RT_NULL)
    {
        LOG_W("thread:%s exit:%d!", self->name, status);
#ifdef RT_USING_PTHREADS
        if(self->pthread_data != RT_NULL)
        {
            extern void pthread_exit(void *value);
            pthread_exit((void *)status);
        }
        else
#endif
        {
            rt_thread_control(self, RT_THREAD_CTRL_CLOSE, RT_NULL);
        }
    }
}

#ifdef RT_USING_MSH
int system(const char *command)
{
    extern int msh_exec(char *cmd, rt_size_t length);

    if (command)
    {
        msh_exec((char *)command, rt_strlen(command));
    }

    return 0;
}
RTM_EXPORT(system);
#endif /* RT_USING_MSH */

char *ltoa(long value, char *string, int radix)
{
    char tmp[33];
    char *tp = tmp;
    long i;
    unsigned long v;
    int sign;
    char *sp;

    if (string == NULL)
    {
        return 0 ;
    }

    if (radix > 36 || radix <= 1)
    {
        return 0 ;
    }

    sign = (radix == 10 && value < 0);
    if (sign)
    {
        v = -value;
    }
    else
    {
        v = (unsigned long)value;
    }

    while (v || tp == tmp)
    {
        i = v % radix;
        v = v / radix;
        if (i < 10)
            *tp++ = (char)(i+'0');
        else
            *tp++ = (char)(i + 'a' - 10);
    }

    sp = string;

    if (sign)
        *sp++ = '-';
    while (tp > tmp)
        *sp++ = *--tp;
    *sp = 0;

    return string;
}

char *itoa(int value, char *string, int radix)
{
    return ltoa(value, string, radix) ;
}


char *ultoa(unsigned long value, char *string, int radix)
{
    char tmp[33];
    char *tp = tmp;
    long i;
    unsigned long v = value;
    char *sp;

    if (string == NULL)
    {
        return 0;
    }

    if (radix > 36 || radix <= 1)
    {
        return 0;
    }

    while (v || tp == tmp)
    {
        i = v % radix;
        v = v / radix;
        if (i < 10)
            *tp++ = (char)(i+'0');
        else
            *tp++ = (char)(i + 'a' - 10);
    }

    sp = string;

    while (tp > tmp)
        *sp++ = *--tp;
    *sp = 0;

    return string;
}

char *utoa(unsigned value, char *string, int radix)
{
    return ultoa(value, string, radix) ;
}
