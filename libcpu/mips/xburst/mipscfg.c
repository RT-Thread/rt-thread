/*
 * File      : mipscfg.c
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
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
 * 2010-05-27     swkyer       first version
 */
#include <rtthread.h>
#include "../common/mipsregs.h"
#include "../common/mipscfg.h"

mips32_core_cfg_t g_mips_core =
{
    16,     /* icache_line_size */
    256,    /* icache_lines_per_way */
    4,      /* icache_ways */
    16,     /* dcache_line_size */
    256,    /* dcache_lines_per_way */
    4,      /* dcache_ways */
    16,     /* max_tlb_entries */
};

static rt_uint16_t m_pow(rt_uint16_t b, rt_uint16_t n)
{
    rt_uint16_t rets = 1;

    while (n--)
        rets *= b;

    return rets;
}

/**
 * read core attribute
 */
void mips32_cfg_init(void)
{
    rt_uint16_t val;
    rt_uint32_t cp0_config1;

    cp0_config1 = read_c0_config();
    if (cp0_config1 & 0x80000000)
    {
        cp0_config1 = read_c0_config1();

        val = (cp0_config1 & (7<<22))>>22;
        g_mips_core.icache_lines_per_way = 64 * m_pow(2, val);
        val = (cp0_config1 & (7<<19))>>19;
        g_mips_core.icache_line_size = 2 * m_pow(2, val);
        val = (cp0_config1 & (7<<16))>>16;
        g_mips_core.icache_ways = val + 1;

        val = (cp0_config1 & (7<<13))>>13;
        g_mips_core.dcache_lines_per_way = 64 * m_pow(2, val);
        val = (cp0_config1 & (7<<10))>>10;
        g_mips_core.dcache_line_size = 2 * m_pow(2, val);
        val = (cp0_config1 & (7<<7))>>7;
        g_mips_core.dcache_ways = val + 1;

        val = (cp0_config1 & (0x3F<<25))>>25;
        g_mips_core.max_tlb_entries = val + 1;
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>
static void CP0_status_analyze(unsigned long value)
{
    if(value & (1<<26))
        rt_kprintf(" FR");
    if(value & (1<<23))
        rt_kprintf(" PX");
    if(value & (1<<22))
        rt_kprintf(" BEV");
    if(value & (1<<20))
        rt_kprintf(" SR");
    if(value & (1<<19))
        rt_kprintf(" NMI");
    if(value & (1<<20))
        rt_kprintf(" SR");
    if(value & (0xFF<<8))
        rt_kprintf(" IM:0x%02X", (value >> 8) & 0xFF);
    if(value & (1<<7))
        rt_kprintf(" KX");
    if(value & (1<<6))
        rt_kprintf(" SX");
    if(value & (1<<5))
        rt_kprintf(" UX");
    if(value & (0x03<<3))
        rt_kprintf(" KSU:0x%02X", (value >> 3) & 0x03);
    if(value & (1<<2))
        rt_kprintf(" ERL");
    if(value & (1<<1))
        rt_kprintf(" EXL");
    if(value & (1<<0))
        rt_kprintf(" IE");
}

static void CP0_config0_analyze(unsigned long value)
{
    /* [31] M */
    if(value & (1UL<<31))
        rt_kprintf(" M");

    /* [15] BE */
    if(value & (1<<15))
        rt_kprintf(" big-endian");
    else
        rt_kprintf(" little-endian");

    /* [14:13] AT */
    {
        int AT = (value >> 13) & 0x03;

        if(AT == 0)
        {
            rt_kprintf(" MIPS32");
        }
        else if(AT == 1)
        {
            rt_kprintf(" MIPS64/A32");
        }
        else if(AT == 2)
        {
            rt_kprintf(" MIPS64/A64");
        }
        else
        {
            rt_kprintf(" unkown");
        }
    }

    /* [12:10] AR */
    {
        int AR = (value >> 10) & 0x07;

        if(AR == 0)
        {
            rt_kprintf(" R1");
        }
        else if(AR == 1)
        {
            rt_kprintf(" R2");
        }
        else
        {
            rt_kprintf(" reserve");
        }
    }

    /* [3] VI */
    if(value & (1UL<<31))
        rt_kprintf(" VI");

    /* [2:0] K0 */
    {
        int K0 = value & 0x07;

        if(K0 == 2)
        {
            rt_kprintf(" uncached");
        }
        else if(K0 == 3)
        {
            rt_kprintf(" cacheable");
        }
        else
        {
            rt_kprintf(" K0:reserve");
        }
    }
}

static void CP0_config1_analyze(unsigned long value)
{
    /* [31] M */
    if(value & (1UL<<31))
        rt_kprintf(" M");

    /* [30:25] MMU size */
    {
        int MMU_size = (value >> 25) & 0x3F;
        rt_kprintf(" TLB:%d", MMU_size + 1);
    }

    /* [24:22] IS, [21:19] IL, [18:16] IA */
    {
        int IS = (value >> 22) & 0x07;
        int IL = (value >> 19) & 0x07;
        int IA = (value >> 16) & 0x07;

        IA = IA + 1;
        IS = 64 << IS;
        IL = 2 << IL;
        rt_kprintf(" Icache-%dKB:%dway*%dset*%dbyte",
                   (IA*IS*IL) >> 10, IA, IS, IL);
    }

    /* [15:13] DS, [12:10] DL, [9:7] DA */
    {
        int DS = (value >> 13) & 0x07;
        int DL = (value >> 10) & 0x07;
        int DA = (value >> 7)  & 0x07;

        DA = DA + 1;
        DS = 64 << DS;
        DL = 2 << DL;
        rt_kprintf(" Dcache-%dKB:%dway*%dset*%dbyte",
                   (DA*DS*DL) >> 10, DA, DS, DL);
    }

    /* [6] C2 */
    if(value & (1UL<<6))
        rt_kprintf(" CP2");

    /* [5] MD */
    if(value & (1UL<<5))
        rt_kprintf(" MDMX-ASE");

    /* [4] PC */
    if(value & (1UL<<4))
        rt_kprintf(" performa-count");

    /* [3] WR */
    if(value & (1UL<<3))
        rt_kprintf(" Watch");

    /* [2] CA */
    if(value & (1UL<<2))
        rt_kprintf(" MIPS16e");

    /* [1] EP */
    if(value & (1UL<<1))
        rt_kprintf(" EJTAG");

    /* [0] FP */
    if(value & (1UL<<0))
        rt_kprintf(" FPU");
}

static void CP0_config2_analyze(unsigned long value)
{
    /* [31] M */
    if(value & (1UL<<31))
        rt_kprintf(" M");
}

static void CP0_config3_analyze(unsigned long value)
{
    /* [31] M */
    if(value & (1UL<<31))
        rt_kprintf(" M");
}

static void list_mips(void)
{
    unsigned long value;
    unsigned long num = 0;

    rt_kprintf("MIPS coprocessor register:\r\n");

    rt_kprintf("( 0,0) INDEX     : 0x%08X\r\n", read_c0_index());
    rt_kprintf("( 1,0) RANDOM    : 0x%08X\r\n", read_c0_random());
    rt_kprintf("( 2,0) ENTRYLO0  : 0x%08X\r\n", read_c0_entrylo0());
    rt_kprintf("( 3,0) ENTRYLO1  : 0x%08X\r\n", read_c0_entrylo1());
    rt_kprintf("( 4,0) CONTEXT   : 0x%08X\r\n", read_c0_context());
    rt_kprintf("( 5,0) PAGEMASK  : 0x%08X\r\n", read_c0_pagemask());
    rt_kprintf("( 6,0) WIRED     : 0x%08X\r\n", read_c0_wired());
    rt_kprintf("( 7,0) INFO      : 0x%08X\r\n", read_c0_info());
    rt_kprintf("( 8,0) BADVADDR  : 0x%08X\r\n", read_c0_badvaddr());
    rt_kprintf("( 9,0) COUNT     : 0x%08X\r\n", read_c0_count());
    rt_kprintf("(10,0) ENTRYHI   : 0x%08X\r\n", read_c0_entryhi());
    rt_kprintf("(11,0) COMPARE   : 0x%08X\r\n", read_c0_compare());

    value = read_c0_status();
    rt_kprintf("(12,0) STATUS    : 0x%08X", value);
    CP0_status_analyze(value);
    rt_kprintf("\r\n");

    /*
    rt_kprintf("(12,1) INTCTL    : 0x%08X\r\n", __read_32bit_c0_register(12, 1));
    rt_kprintf("(12,2) SRSCTL    : 0x%08X\r\n", __read_32bit_c0_register(12, 2));
    */

    rt_kprintf("(13,0) CAUSE     : 0x%08X\r\n", read_c0_cause());
    rt_kprintf("(14,0) EPC       : 0x%08X\r\n", read_c0_epc());
    rt_kprintf("(15,0) PRID      : 0x%08X\r\n", read_c0_prid());
    rt_kprintf("(15,1) EBASE     : 0x%08X\r\n", read_c0_ebase());

    value = read_c0_config();
    rt_kprintf("(16,0) CONFIG    : 0x%08X", value);
    CP0_config0_analyze(value);
    rt_kprintf("\r\n");
    if(value & (1UL << 31))
    {
        value = read_c0_config1();
        rt_kprintf("(16,1) CONFIG1   : 0x%08X", value);
        CP0_config1_analyze(value);
        rt_kprintf("\r\n");

        if(value & (1UL << 31))
        {
            value = read_c0_config2();
            rt_kprintf("(16,2) CONFIG2   : 0x%08X\r\n", value);
            CP0_config2_analyze(value);
            rt_kprintf("\r\n");

            if(value & (1UL << 31))
            {
                value = read_c0_config3();
                rt_kprintf("(16,3) CONFIG3   : 0x%08X\r\n", value);
                CP0_config3_analyze(value);
                rt_kprintf("\r\n");
            }
        }
    }

    rt_kprintf("(17,0) LLADDR    : 0x%08X\r\n", __read_32bit_c0_register($17, 0));
    rt_kprintf("(18,0) WATCHLO   : 0x%08X\r\n", __read_32bit_c0_register($18, 0));
    rt_kprintf("(19,0) WATCHHI   : 0x%08X\r\n", __read_32bit_c0_register($19, 0));
    rt_kprintf("(20,0) XCONTEXT  : 0x%08X\r\n", __read_32bit_c0_register($20, 0));
    rt_kprintf("(21,0) FRAMEMASK : 0x%08X\r\n", __read_32bit_c0_register($21, 0));
    rt_kprintf("(22,0) DIAGNOSTIC: 0x%08X\r\n", __read_32bit_c0_register($22, 0));
    rt_kprintf("(23,0) DEBUG     : 0x%08X\r\n", __read_32bit_c0_register($23, 0));
    rt_kprintf("(24,0) DEPC      : 0x%08X\r\n", __read_32bit_c0_register($24, 0));

    rt_kprintf("(25,0) PERFCTL0  : 0x%08X\r\n", __read_32bit_c0_register($25, 0));
    rt_kprintf("(26,0) ECC       : 0x%08X\r\n", __read_32bit_c0_register($26, 0));
    rt_kprintf("(27,0) CACHEERR  : 0x%08X\r\n", __read_32bit_c0_register($27, 0));
    rt_kprintf("(28,0) TAGLO     : 0x%08X\r\n", __read_32bit_c0_register($28, 0));
    rt_kprintf("(29,0) TAGHI     : 0x%08X\r\n", __read_32bit_c0_register($29, 0));

    /*
    rt_kprintf("(30,0) ERROREPC  : 0x%08X\r\n", __read_32bit_c0_register($30, 0));
    rt_kprintf("(31,0) DESAVE    : 0x%08X\r\n", __read_32bit_c0_register($31, 0));
    */


    rt_kprintf("\r\n");
}
FINSH_FUNCTION_EXPORT(list_mips, list  CPU info)
#endif /* RT_USING_FINSH */

