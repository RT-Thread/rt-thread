/*
 * File      : dump_slcd.c
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017Äê4ÔÂ11ÈÕ     Urey         the first version
 */
#include <rtthread.h>
#include <finsh.h>
#include <x1000.h>
#include "x1000_slcdc.h"

/* SLCDC reg ops */
#define slcd_reg_write(addr,config)      writel(config,addr)
#define slcd_reg_read(addr)              readl(addr)

int dump_slcd_regs(void)
{
    int tmp;
    rt_kprintf("$$$dump_lcd_reg\n");
    rt_kprintf("LCDC_CFG:(0x%08x) \t0x%08x\n", LCDC_CFG,slcd_reg_read(LCDC_CFG));
    rt_kprintf("LCDC_CTRL:(0x%08x)\t0x%08x\n",LCDC_CTRL,slcd_reg_read(LCDC_CTRL));
    rt_kprintf("LCDC_STATE:(0x%08x)\t0x%08x\n",LCDC_STATE,slcd_reg_read(LCDC_STATE));
    rt_kprintf("LCDC_OSDC:(0x%08x)\t0x%08x\n", LCDC_OSDC,slcd_reg_read(LCDC_OSDC));
    rt_kprintf("LCDC_OSDCTRL:(0x%08x)\t0x%08x\n",LCDC_OSDCTRL,slcd_reg_read(LCDC_OSDCTRL));
    rt_kprintf("LCDC_OSDS:(0x%08x)\t0x%08x\n",LCDC_OSDS,slcd_reg_read(LCDC_OSDS));
    rt_kprintf("LCDC_BGC0:(0x%08x)\t0x%08x\n",LCDC_BGC0,slcd_reg_read(LCDC_BGC0));
    rt_kprintf("LCDC_BGC1:(0x%08x)\t0x%08x\n",LCDC_BGC1,slcd_reg_read(LCDC_BGC1));
    rt_kprintf("LCDC_KEY0:(0x%08x)\t0x%08x\n",LCDC_KEY0, slcd_reg_read(LCDC_KEY0));
    rt_kprintf("LCDC_KEY1:(0x%08x)\t0x%08x\n",LCDC_KEY1, slcd_reg_read(LCDC_KEY1));
    rt_kprintf("LCDC_ALPHA:(0x%08x)\t0x%08x\n",LCDC_ALPHA, slcd_reg_read(LCDC_ALPHA));
    rt_kprintf("==================================\n");
    tmp = slcd_reg_read(LCDC_VAT);
    rt_kprintf("LCDC_VAT:(0x%08x) \t0x%08x, HT = %d, VT = %d\n",LCDC_VAT, tmp,
           (tmp & LCDC_VAT_HT_MASK) >> LCDC_VAT_HT_BIT,
           (tmp & LCDC_VAT_VT_MASK) >> LCDC_VAT_VT_BIT);
    tmp = slcd_reg_read(LCDC_DAH);
    rt_kprintf("LCDC_DAH:(0x%08x) \t0x%08x, HDS = %d, HDE = %d\n",LCDC_DAH, tmp,
           (tmp & LCDC_DAH_HDS_MASK) >> LCDC_DAH_HDS_BIT,
           (tmp & LCDC_DAH_HDE_MASK) >> LCDC_DAH_HDE_BIT);
    tmp = slcd_reg_read(LCDC_DAV);
    rt_kprintf("LCDC_DAV:(0x%08x) \t0x%08x, VDS = %d, VDE = %d\n",LCDC_DAV, tmp,
           (tmp & LCDC_DAV_VDS_MASK) >> LCDC_DAV_VDS_BIT,
           (tmp & LCDC_DAV_VDE_MASK) >> LCDC_DAV_VDE_BIT);
    tmp = slcd_reg_read(LCDC_HSYNC);
    rt_kprintf("LCDC_HSYNC:(0x%08x)\t0x%08x, HPS = %d, HPE = %d\n",LCDC_HSYNC, tmp,
           (tmp & LCDC_HSYNC_HPS_MASK) >> LCDC_HSYNC_HPS_BIT,
           (tmp & LCDC_HSYNC_HPE_MASK) >> LCDC_HSYNC_HPE_BIT);
    tmp = slcd_reg_read(LCDC_VSYNC);
    rt_kprintf("LCDC_VSYNC:(0x%08x)\t0x%08x, VPS = %d, VPE = %d\n", LCDC_VSYNC,tmp,
           (tmp & LCDC_VSYNC_VPS_MASK) >> LCDC_VSYNC_VPS_BIT,
           (tmp & LCDC_VSYNC_VPE_MASK) >> LCDC_VSYNC_VPE_BIT);
    rt_kprintf("==================================\n");
    rt_kprintf("LCDC_XYP0:(0x%08x)\t0x%08x\n",LCDC_XYP0, slcd_reg_read(LCDC_XYP0));
    rt_kprintf("LCDC_XYP1:(0x%08x)\t0x%08x\n",LCDC_XYP1, slcd_reg_read(LCDC_XYP1));
    rt_kprintf("LCDC_SIZE0:(0x%08x)\t0x%08x\n",LCDC_SIZE0, slcd_reg_read(LCDC_SIZE0));
    rt_kprintf("LCDC_RGBC:(0x%08x) \t0x%08x\n",LCDC_RGBC, slcd_reg_read(LCDC_RGBC));
    rt_kprintf("LCDC_PS:(0x%08x)  \t0x%08x\n",LCDC_PS, slcd_reg_read(LCDC_PS));
    rt_kprintf("LCDC_CLS:(0x%08x) \t0x%08x\n", LCDC_CLS,slcd_reg_read(LCDC_CLS));
    rt_kprintf("LCDC_SPL:(0x%08x) \t0x%08x\n",LCDC_SPL, slcd_reg_read(LCDC_SPL));
    rt_kprintf("LCDC_REV:(0x%08x) \t0x%08x\n",LCDC_REV, slcd_reg_read(LCDC_REV));
    rt_kprintf("LCDC_IID:(0x%08x) \t0x%08x\n",LCDC_IID, slcd_reg_read(LCDC_IID));
    rt_kprintf("==================================\n");
    rt_kprintf("LCDC_DA0:(0x%08x) \t0x%08x\n",LCDC_DA0, slcd_reg_read(LCDC_DA0));
    rt_kprintf("LCDC_SA0:(0x%08x) \t0x%08x\n",LCDC_SA0, slcd_reg_read(LCDC_SA0));
    rt_kprintf("LCDC_FID0:(0x%08x)\t0x%08x\n",LCDC_FID0, slcd_reg_read(LCDC_FID0));
    rt_kprintf("LCDC_CMD0:(0x%08x)\t0x%08x\n",LCDC_CMD0, slcd_reg_read(LCDC_CMD0));
    rt_kprintf("LCDC_OFFS0:(0x%08x)\t0x%08x\n",LCDC_OFFS0, slcd_reg_read(LCDC_OFFS0));
    rt_kprintf("LCDC_PW0:(0x%08x) \t0x%08x\n", LCDC_PW0,slcd_reg_read(LCDC_PW0));
    rt_kprintf("LCDC_CNUM0:(0x%08x)\t0x%08x\n",LCDC_CNUM0, slcd_reg_read(LCDC_CNUM0));
    rt_kprintf("LCDC_DESSIZE0:(0x%08x)\t0x%08x\n",LCDC_DESSIZE0, slcd_reg_read(LCDC_DESSIZE0));
    rt_kprintf("==================================\n");
    rt_kprintf("LCDC_PCFG:(0x%08x)\t0x%08x\n", LCDC_PCFG,slcd_reg_read(LCDC_PCFG));
    rt_kprintf("==================================\n");
    rt_kprintf("SLCDC_CFG:(0x%08x) \t0x%08x\n", SLCDC_CFG,slcd_reg_read(SLCDC_CFG));
    rt_kprintf("SLCDC_CTRL:(0x%08x) \t0x%08x\n", SLCDC_CTRL,slcd_reg_read(SLCDC_CTRL));
    rt_kprintf("SLCDC_STATE:(0x%08x) \t0x%08x\n", SLCDC_STATE,slcd_reg_read(SLCDC_STATE));
    rt_kprintf("SLCDC_DATA:(0x%08x)\t0x%08x\n", SLCDC_DATA,slcd_reg_read(SLCDC_DATA));
    rt_kprintf("SLCDC_CFG_NEW:(0x%08x) \t0x%08x\n", SLCDC_CFG_NEW,slcd_reg_read(SLCDC_CFG_NEW));
    rt_kprintf("SLCDC_WTIME:(0x%08x) \t0x%08x\n", SLCDC_WTIME,slcd_reg_read(SLCDC_WTIME));
    rt_kprintf("SLCDC_TAS:(0x%08x) \t0x%08x\n", SLCDC_TAS,slcd_reg_read(SLCDC_TAS));
    rt_kprintf("==================================\n");
    rt_kprintf("reg:0x10000020 value=0x%08x  (24bit) Clock Gate Register0\n",
           *(uint32_t *)0xb0000020);
    rt_kprintf("reg:0x100000e4 value=0x%08x  (5bit_lcdc 21bit_lcdcs) Power Gate Register: \n",
           *(uint32_t *)0xb00000e4);
    rt_kprintf("reg:0x100000b8 value=0x%08x  (10bit) SRAM Power Control Register0 \n",
           *(uint32_t *)0xb00000b8);
    rt_kprintf("reg:0x10000064 value=0x%08x  Lcd pixclock \n",
           *(uint32_t *)0xb0000064);

    return 0;
}
MSH_CMD_EXPORT(dump_slcd_regs,dump_slcd_regs);

