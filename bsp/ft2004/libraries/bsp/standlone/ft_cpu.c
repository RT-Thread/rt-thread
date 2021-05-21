/*
 * @[H]: Copyright (C) 2014-2021 Phytium Technology.  All rights reserved.
 * 
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  Use of the Software is limited solely to applications:
 *  (a) running on a Phytium device, or
 *  (b) that interact with a Phytium device through a bus or interconnect.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  PHYTIUM  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 *  OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 * 
 *  Except as contained in this notice, the name of the Phytium shall not be used
 *  in advertising or otherwise to promote the sale, use or other dealings in
 *  this Software without prior written authorization from Phytium. 
 * 
 * @Date: 2021-04-20 11:32:32
 * @LastEditTime: 2021-04-20 11:32:32
 * @Description:  Description of file
 * @Modify History: 
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#include "ft_parameters.h"
#include "ft_cpu.h"
#include "ft_assert.h"
#include "ft_printf.h"

#ifdef FT_SMP_EN

typedef union
{
    u32 Slock;
    struct ArchTicket
    {
        u16 owner;
        u16 next;
    } Tickets;
} FCpu_Lock_t;

struct FCpu
{
    u32 IsReady;
    FCpu_Lock_t Clock;
};

struct FCpu FCpu_Lock = {0};

const u32 SoftAffiTable[4] = {0, 1, 0x100, 0x101};

/**
 * @name: FCpu_IdGet
 * @msg: In a multiprocessor system, provides an additional PE identification mechanism for scheduling 
            purposes.
 * @return {Aff0} Affinity level 0. The most significant affinity level field, for this PE in the system.
 */
s32 FCpu_IdGet(void)
{
    s32 cpu_id;
    __asm__ volatile(
        "mrc p15, 0, %0, c0, c0, 5"
        : "=r"(cpu_id));
    // Ft_printf("error cpu_id %x \r\n", cpu_id);
    // cpu_id &= 0xf;

    switch ((cpu_id & 0xfff))
    {
    case 1:
        return 1;
    case 0x100:
        return 2;
    case 0x101:
        return 3;
    default:
        return (cpu_id & 0xf);
    }
}

s32 FCpu_AffinityGet(void)
{
    s32 AffinityId;
    __asm__ volatile(
        "mrc p15, 0, %0, c0, c0, 5"
        : "=r"(AffinityId));
    // Ft_printf("error cpu_id %x \r\n", cpu_id);
    // cpu_id &= 0xf;
    return AffinityId & 0xfff;
}

void FCpu_SpinLockInit(void)
{
    FCpu_Lock.Clock.Slock = 0;
    FCpu_Lock.IsReady = FT_COMPONENT_IS_READLY;
}

void FCpu_SpinLock(void)
{
    u32 Tmp;
    u32 Newval;
    FCpu_Lock_t LockVal;
    Ft_assertVoid(FCpu_Lock.IsReady == FT_COMPONENT_IS_READLY);

    __asm__ __volatile__(
        "pld [%0]" ::"r"(&FCpu_Lock.Clock.Slock));

    __asm__ __volatile__(
        "1: ldrex   %0, [%3]\n"
        "   add %1, %0, %4\n"
        "   strex   %2, %1, [%3]\n"
        "   teq %2, #0\n"
        "   bne 1b"
        : "=&r"(LockVal), "=&r"(Newval), "=&r"(Tmp)
        : "r"(&FCpu_Lock.Clock.Slock), "I"(1 << 16)
        : "cc");

    while (LockVal.Tickets.next != LockVal.Tickets.owner)
    {
        __asm__ __volatile__("wfe" ::
                                 : "memory");
        LockVal.Tickets.owner = *(volatile unsigned short *)(&FCpu_Lock.Clock.Tickets.owner);
    }

    __asm__ volatile("dmb" ::
                         : "memory");
}

void FCpu_SpinUnlock(void)
{
    Ft_assertVoid(FCpu_Lock.IsReady == FT_COMPONENT_IS_READLY);
    __asm__ volatile("dmb" ::
                         : "memory");
    FCpu_Lock.Clock.Tickets.owner++;
    __asm__ volatile("dsb ishst\nsev" ::
                         : "memory");
}

#else /*RT_USING_SMP*/

s32 FCpu_IdGet(void)
{
    return 0;
}
void FCpu_SpinLockInit(void)
{
    return;
}
void FCpu_SpinLock(void)
{
    return;
}
void FCpu_SpinUnlock(void)
{
    return;
}

#endif