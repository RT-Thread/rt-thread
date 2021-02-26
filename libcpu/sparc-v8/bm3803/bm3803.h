/*
 * Copyright (c) 2020, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-16     Dystopia     the first version
 */

#ifndef __BM3803_H__
#define __BM3803_H__

struct lregs
{
    /* address = 0x80000000 */
    unsigned int memcfg1;           /* 0x00 */
    unsigned int memcfg2;
    unsigned int memcfg3;
    unsigned int failaddr;

    unsigned int memstatus;     /* 0x10 */
    unsigned int cachectrl;
    unsigned int powerdown;
    unsigned int writeprot1;

    unsigned int writeprot2;        /* 0x20 */
    unsigned int pcr;
    unsigned int dummy2;
    unsigned int dummy3;

    unsigned int dummy4;            /* 0x30 */
    unsigned int dummy5;
    unsigned int dummy6;
    unsigned int dummy7;

    unsigned int timercnt1;     /* 0x40 */
    unsigned int timerload1;
    unsigned int timerctrl1;
    unsigned int wdog;

    unsigned int timercnt2;        /* 0x50 */
    unsigned int timerload2;
    unsigned int timerctrl2;
    unsigned int dummy8;

    unsigned int scalercnt;        /* 0x60 */
    unsigned int scalerload;
    unsigned int dummy9;
    unsigned int dummy10;

    unsigned int uartdata1;        /* 0x70 */
    unsigned int uartstatus1;
    unsigned int uartctrl1;
    unsigned int uartscaler1;

    unsigned int uartdata2;        /* 0x80 */
    unsigned int uartstatus2;
    unsigned int uartctrl2;
    unsigned int uartscaler2;

    unsigned int irqmask;           /* 0x90 */
    unsigned int irqpend;
    unsigned int irqforce;
    unsigned int irqclear;

    unsigned int piodata;            /* 0xA0 */
    unsigned int piodir;
    unsigned int pioirq;
    unsigned int dummy11;

    unsigned int imask2;            /* 0xB0 */
    unsigned int ipend2;
    unsigned int istat2;
    unsigned int dummy12;

    unsigned int dummy13;          /* 0xC0 */
    unsigned int dcomstatus;
    unsigned int dcomctrl;
    unsigned int dcomscaler;

    unsigned int dummy14;           /* 0xD0 */
    unsigned int dummy15;
    unsigned int dummy16;
    unsigned int dummy17;

    unsigned int uartdata3;         /* 0xE0 */
    unsigned int uartstatus3;
    unsigned int uartctrl3;
    unsigned int uartscaler3;
};

#define PREGS 0x80000000

#define UART1_BASE (PREGS + 0x70)

#define TIMER2_TT 0x19
#define UART1_TT 0x13

#endif
