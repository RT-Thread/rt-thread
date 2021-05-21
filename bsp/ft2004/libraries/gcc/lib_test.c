/*
 * @Author: hh
 * @Date: 2020-12-29 17:07:06
 * @LastEditTime: 2021-03-01 11:11:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ft\project_freertos\devices\ft2000ahk\gcc\main.c
 */

// #include <malloc.h>
// #include <string.h>

// int main(void)
// {
//     volatile char *data = 0;
//     data = malloc(1);
//     memcpy(data, data, 1);
//     free((void *)data);
//     return data;
// }

#include <stdio.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ft_types.h"
#include "ft_printf.h"

// int main(void)
// {
//     volatile char *data = 0;
//     Ft_printf("233333");
//     data = malloc(1024);
//     return (int)data;
// }

void user_fun_def(void)
{
    Ft_printf("user_fun_def \r\n");
    while (1)
    {
    }
}

void frq_debug(u32 r0, u32 r1)
{
    Ft_printf("test frq current %x ,last %x\r\n", r0, r1);
    while (1)
    {
    }
}

void irq_debug(u32 r0, u32 r1)
{
    Ft_printf("test irq current %x ,last %x\r\n", r0, r1);
    while (1)
    {
    }
}

void PrefAbort_debug(void)
{
    Ft_printf("PrefAbort_debug\r\n");
    while (1)
    {
    }
}

void Svc_debug(void)
{
    Ft_printf("Svc_debug\r\n");
    while (1)
    {
    }
}

void Undefine_debug(void)
{
    Ft_printf("Undefine_debug\r\n");
    while (1)
    {
    }
}

void data_abort_debug(void)
{
    Ft_printf("data abort\r\n");
    while (1)
    {
    }
}

int _close(int file) { return -1; }

int _fstat(int file, struct stat *st)
{
    // st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file) { return 1; }

int _lseek(int file, int ptr, int dir) { return 0; }

int _open(const char *name, int flags, int mode) { return -1; }

int _read(int file, char *ptr, int len)
{
    int todo = 0;
    // if (len == 0)
    //     return 0;
    // while (UART_FR(UART0_ADDR) & UART_FR_RXFE)
    //     ;
    // *ptr++ = UART_DR(UART0_ADDR);
    // for (todo = 1; todo < len; todo++)
    // {
    //     if (UART_FR(UART0_ADDR) & UART_FR_RXFE)
    //     {
    //         break;
    //     }
    //     *ptr++ = UART_DR(UART0_ADDR);
    // }
    return todo;
}
int _write(int file, char *ptr, int len)
{
    // int todo;

    // for (todo = 0; todo < len; todo++)
    // {
    //     UART_DR(UART0_ADDR) = *ptr++;
    // }
    return 0;
}
