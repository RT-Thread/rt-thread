/**
 * drivers/usb/host/ehci_sunxi.c
 * (C) Copyright 2010-2015
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * yangnaitian, 2011-5-24, create this file
 * javen, 2011-6-26, add suspend and resume
 * javen, 2011-7-18, move clock and power operations out from driver
 *
 * SoftWinner EHCI Driver
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 */

#include <stdlib.h>
#include <string.h>
#include <usb_gen_hcd.h>
#include "sunxi-hci.h"
#include "platform_usb.h"
#include "ehci.h"
#include "hal_gpio.h"
#include "hal_cfg.h"

#if USB_MAX_CONTROLLER_COUNT
static struct sunxi_hci_hcd g_sunxi_ehci[USB_MAX_CONTROLLER_COUNT];
#else
static struct sunxi_hci_hcd *g_sunxi_ehci = 0;
#endif

static unsigned char g_sunxi_insmod_cnt = 0;

static void sunxi_ehci_insmod_count(void)
{
    g_sunxi_insmod_cnt++;
}

static void sunxi_ehci_rmmod_count(void)
{
    if (g_sunxi_insmod_cnt > 0)
    {
        g_sunxi_insmod_cnt--;
    }
    else
    {
        hal_log_err("ERR: g_sunxi_insmod_cnt = %d", g_sunxi_insmod_cnt);
    }
}

static unsigned char sunxi_ehci_count(void)
{
    return g_sunxi_insmod_cnt;
}

static void sunxi_hcd_board_set_vbus(
        struct sunxi_hci_hcd *sunxi_ehci, int is_on)
{
    sunxi_ehci->set_power(sunxi_ehci, is_on);
}

static void sunxi_hcd_board_set_passby(struct sunxi_hci_hcd *sunxi_ehci,
                        int is_on)
{
    sunxi_ehci->usb_passby(sunxi_ehci, is_on);
}

static int open_ehci_clock(struct sunxi_hci_hcd *sunxi_ehci)
{
    return sunxi_ehci->open_clock(sunxi_ehci, 0);
}

static int close_ehci_clock(struct sunxi_hci_hcd *sunxi_ehci)
{
    return sunxi_ehci->close_clock(sunxi_ehci, 0);
}

static void sunxi_start_ehci(struct sunxi_hci_hcd *sunxi_ehci)
{
    open_ehci_clock(sunxi_ehci);
    sunxi_hcd_board_set_passby(sunxi_ehci, 1);
    sunxi_hcd_board_set_vbus(sunxi_ehci, 1);
#if defined(CONFIG_ARCH_SUN8IW20) || defined(CONFIG_SOC_SUN20IW1)
    sunxi_ehci_insmod_count();
#endif
}

static void sunxi_stop_ehci(struct sunxi_hci_hcd *sunxi_ehci)
{
#if defined(CONFIG_ARCH_SUN8IW20) || defined(CONFIG_SOC_SUN20IW1)
    sunxi_ehci_rmmod_count();
    if (sunxi_ehci_count() == 0)
#endif
    {
        sunxi_hcd_board_set_vbus(sunxi_ehci, 0);
    }

    sunxi_hcd_board_set_passby(sunxi_ehci, 0);
    close_ehci_clock(sunxi_ehci);
}

static int sunxi_ehci_setup(struct hc_gen_dev *hcd)
{
    struct ehci_hcd *ehci = hcd_to_ehci(hcd);
    int ret = ehci_init(hcd);

    //ehci->need_io_watchdog = 0;

    return ret;
}

static const struct hc_driver sunxi_ehci_hc_driver = {
    .description            = "ehci_hcd",
    .product_desc           = "SW USB2.0 'Enhanced' Host Controller (EHCI) Driver",
    .hcd_priv_size          = sizeof(struct ehci_hcd),

    /**
     * generic hardware linkage
     */
    .irq                =  NULL,
    //.flags                =  HCD_MEMORY | HCD_USB2 | HCD_BH,
    .flags              =  HC_DRIVER_FLAG_HCD_USB2,

    /**
     * basic lifecycle operations
     *
     * FIXME -- ehci_init() doesn't do enough here.
     * See ehci-ppc-soc for a complete implementation.
     */
    .reset              = sunxi_ehci_setup,
    .start              = ehci_run,
    .stop               = ehci_stop,
//  .shutdown           = ehci_shutdown,

    /**
     * managing i/o requests and associated device resources
     */
    .urb_enqueue            = ehci_urb_enqueue,
    .urb_dequeue            = ehci_urb_dequeue,
    .endpoint_disable       = ehci_endpoint_disable,

//  .endpoint_reset         = ehci_endpoint_reset,

    /**
     * scheduling support
     */
    .get_frame_number       = ehci_get_frame,

    /**
     * root hub support
     */
    .hub_status_data        = ehci_hub_status_data,
    .hub_control            = ehci_hub_control,
    .hub_suspend            = ehci_bus_suspend,
    .hub_resume             = ehci_bus_resume,
//  .relinquish_port        = ehci_relinquish_port,
//  .port_handed_over       = ehci_port_handed_over,

//  .clear_tt_buffer_complete   = ehci_clear_tt_buffer_complete,
};

int sunxi_insmod_ehci(struct sunxi_hci_hcd * sunxi_ehci)
{
    /*
     * hc_gen_dev----------usb_hcd
     * hc_private----------ehci_hcd
     * usb_host_virt_dev--------usb_device
     * */
    //struct usb_hcd *hcd   = NULL;
    struct hc_gen_dev *hcd  = NULL;
    struct ehci_hcd *ehci   = NULL;

    int     mask;
    int port;
    int ret = 0;

    hal_log_info("[%s%d]: probe, sunxi_ehci: 0x%p, 0x:%p, irq_no:%d\n",
        sunxi_ehci->hci_name, sunxi_ehci->usbc_no, sunxi_ehci,
        sunxi_ehci->usb_vbase, sunxi_ehci->irq_no);

    sunxi_ehci->ehci_base       = sunxi_ehci->usb_vbase;
    sunxi_ehci->ehci_reg_length = SUNXI_USB_EHCI_LEN;

    /* creat a usb_hcd for the ehci controller*/
    hcd = usb_create_hc_gen_dev(&sunxi_ehci_hc_driver, sunxi_ehci->hci_name);
    //hcd = usb_create_hcd(&sunxi_ehci_hc_driver, sunxi_ehci->hci_name);
    sunxi_ehci->hcd = hcd;

    /* request irq */
    if (request_irq(sunxi_ehci->irq_no, ehci_irq_handler, sunxi_ehci->usb_irq_flag, "ehci", hcd) < 0) {
        hal_log_err("request irq error\n");
        return -1;
    }

    enable_irq(sunxi_ehci->irq_no);

    /* echi start to work */
    sunxi_start_ehci(sunxi_ehci);

    ehci = hcd_to_ehci(hcd);
    ehci->caps = (struct ehci_caps *)(long)sunxi_ehci->ehci_base;
    ehci->regs = (struct ehci_regs *)((long)ehci->caps +
            HC_LENGTH(ehci, hal_readl(&ehci->caps->hc_capbase)));

    /* cache this readonly data, minimize chip reads */
    ehci->hcs_params = hal_readl(&ehci->caps->hcs_params);

    hcd->state = HC_GEN_DEV_STATE_RUNNING;
    /*melis original func: usb_add_hc_gen_dev()*/
    ret = usb_add_hc_gen_dev(hcd, sunxi_ehci->irq_no, IRQF_SHARED);
    if (ret != 0) {
        hal_log_err("ERR: usb_add_hcd failed\n");
        ret = -ENOMEM;
        goto ERR3;
    }

    /* ehci_bus_suspend */
    //port = HCS_N_PORTS(ehci->hcs_params);
    //while (port--) {
    //  uint32_t *reg = &ehci->regs->port_status [port];
    //  uint32_t t1 = ehci_readl(ehci, reg) & ~PORT_RWC_BITS;
    //  uint32_t t2 = t1 & ~PORT_WAKE_BITS;

    //  t2 |= PORT_WKOC_E | PORT_WKCONN_E;

    //  ehci_writel(ehci, t2, reg);
    //}

    /* Do not halt the controller since the PM ops not supported yet. */
    //ehci_halt (ehci);

    /* allow remote wakeup */
    mask = INTR_MASK;
    //if (!hcd->self.root_hub->do_remote_wakeup)
    //  mask &= ~STS_PCD;
    ehci_writel(ehci, mask, &ehci->regs->intr_enable);
    ehci_readl(ehci, &ehci->regs->intr_enable);

    return 0;

ERR3:
    sunxi_stop_ehci(sunxi_ehci);
    //usb_put_hcd(hcd);

ERR2:
    sunxi_ehci->hcd = NULL;
    //g_sunxi_ehci[sunxi_ehci->usbc_no] = NULL;

ERR1:

    return ret;
}

int sunxi_rmmod_ehci(struct sunxi_hci_hcd * sunxi_ehci)
{


    hal_log_info("[%s%d]: remove, sunxi_ehci: 0x%p, 0x:%p, irq_no:%d\n",
        sunxi_ehci->hci_name, sunxi_ehci->usbc_no, sunxi_ehci,
        sunxi_ehci->usb_vbase, sunxi_ehci->irq_no);
    //usb_remove_hcd(hcd);

    if (sunxi_ehci->irq_no > 0)
    {
        free_irq(sunxi_ehci->irq_no, sunxi_ehci->hcd);
    }
    //usb_put_hcd(hcd);

//#if defined(CONFIG_SUNXI_REGULATOR_DT)
//  if (sunxi_ehci->supply)
//      regulator_put(sunxi_ehci->supply);
//#endif
//
    sunxi_stop_ehci(sunxi_ehci);

    sunxi_ehci->hcd = NULL;

    return 0;
}

int sunxi_ehci_hcd_init(int hci_num)
{
    int value = 0;
    char ehci_name[10] = {0};
    sprintf(ehci_name, "usbc%1d", hci_num);

    if (Hal_Cfg_GetKeyValue(ehci_name, KEY_USB_ENABLE, (int32_t *)&value, 1) == 0) {
        if (value == SUNXI_USB_DISABLE) {
            hal_log_err("ERR: ehci%d disable", hci_num);
            return -1;
        }
    }

    if(g_sunxi_ehci == 0) {
        hal_log_err("ERR: ehci%d NULL!", hci_num);
        return -1;
    }

    if (hci_num >= USB_MAX_CONTROLLER_COUNT) {
        hal_log_err("ERR: ehci%d oversize!", hci_num);
        return -1;
    }

    int ret = 0;
    struct sunxi_hci_hcd *sunxi_ehci = &g_sunxi_ehci[hci_num];

    if(!sunxi_ehci->hcd)
    {
        struct platform_usb_config *hci_table = platform_get_hci_table();
        struct platform_usb_config *otg_table = platform_get_otg_table();

        sunxi_ehci->usbc_no     = hci_num;
        sunxi_ehci->usb_vbase   = hci_table[hci_num].pbase;
        sunxi_ehci->irq_no      = hci_table[hci_num].irq;
        sunxi_ehci->otg_vbase   = otg_table->pbase;

        sprintf(sunxi_ehci->hci_name, "%s", hci_table[hci_num].name);

        hci_clock_init(sunxi_ehci);
        sunxi_hci_get_config_param(sunxi_ehci);

        sunxi_ehci->open_clock          = open_clock;
        sunxi_ehci->close_clock         = close_clock;
        sunxi_ehci->set_power           = sunxi_set_vbus;
        sunxi_ehci->usb_passby          = usb_passby;

        sunxi_insmod_ehci(sunxi_ehci);
        return 0;
    }
    else
    {
        hal_log_err("ERR: ehci%d already exist!", hci_num);
    }

    return -1;
}

int sunxi_ehci_hcd_deinit(int hci_num)
{

    struct sunxi_hci_hcd *sunxi_ehci = &g_sunxi_ehci[hci_num];
#if 0
    /* TODO */
    struct sunxi_hci_hcd *sunxi_ehci = NULL;

    int ret = 0;

    if (sunxi_ehci->probe == 1) {
        ret = sunxi_rmmod_ehci(pdev);
        if (ret == 0)
            exit_sunxi_hci(sunxi_ehci);

        return ret;
    } else
        return 0;
#endif
    if(sunxi_ehci->hcd)
        return sunxi_rmmod_ehci(sunxi_ehci);
    else
        hal_log_err("ERR: ehci%d is NULL!", hci_num);

    return 0;
}
static void  ehci_set_interrupt_enable(const struct ehci_hcd *ehci,
        uint32_t regs, u32 enable)
{
    USBC_Writel(enable & 0x3f, (regs + EHCI_OPR_USBINTR));
}
static void ehci_disable_periodic_schedule(const struct ehci_hcd *ehci,
        uint32_t regs)
{
    u32 reg_val = 0;

    reg_val =  USBC_Readl(regs + EHCI_OPR_USBCMD);
    reg_val &= ~(0x1<<4);
    USBC_Writel(reg_val, (regs + EHCI_OPR_USBCMD));
}

static void ehci_disable_async_schedule(const struct ehci_hcd *ehci,
        uint32_t regs)
{
    unsigned int reg_val = 0;

    reg_val =  USBC_Readl(regs + EHCI_OPR_USBCMD);
    reg_val &= ~(0x1<<5);
    USBC_Writel(reg_val, (regs + EHCI_OPR_USBCMD));
}

static void ehci_set_config_flag(const struct ehci_hcd *ehci,
        uint32_t regs)
{
    USBC_Writel(0x1, (regs + EHCI_OPR_CFGFLAG));
}

static void ehci_test_stop(const struct ehci_hcd *ehci,
        uint32_t regs)
{
    unsigned int reg_val = 0;

    reg_val =  USBC_Readl(regs + EHCI_OPR_USBCMD);
    reg_val &= (~0x1);
    USBC_Writel(reg_val, (regs + EHCI_OPR_USBCMD));
}

static void ehci_test_reset(const struct ehci_hcd *ehci,
        uint32_t regs)
{
    u32 reg_val = 0;

    reg_val =  USBC_Readl(regs + EHCI_OPR_USBCMD);
    reg_val |= (0x1<<1);
    USBC_Writel(reg_val, (regs + EHCI_OPR_USBCMD));
}

static unsigned int ehci_test_reset_complete(const struct ehci_hcd *ehci,
        uint32_t regs)
{

    unsigned int reg_val = 0;

    reg_val = USBC_Readl(regs + EHCI_OPR_USBCMD);
    reg_val &= (0x1<<1);

    return !reg_val;
}

static void ehci_start(const struct ehci_hcd *ehci, uint32_t regs)
{
    unsigned int reg_val = 0;

    reg_val =  USBC_Readl(regs + EHCI_OPR_USBCMD);
    reg_val |= 0x1;
    USBC_Writel(reg_val, (regs + EHCI_OPR_USBCMD));
}

static unsigned int ehci_is_halt(const struct ehci_hcd *ehci,
        uint32_t regs)
{
    unsigned int reg_val = 0;

    reg_val = USBC_Readl(regs + EHCI_OPR_USBSTS) >> 12;
    reg_val &= 0x1;
    return reg_val;
}

static void ehci_port_control(const struct ehci_hcd *ehci,
        uint32_t regs, u32 port_no, u32 control)
{
    USBC_Writel(control, (regs + EHCI_OPR_USBCMD + (port_no<<2)));
}

static void  ehci_put_port_suspend(const struct ehci_hcd *ehci,
        uint32_t regs)
{
    unsigned int reg_val = 0;

    reg_val =  USBC_Readl(regs + EHCI_OPR_PORTSC);
    reg_val |= (0x01<<7);
    USBC_Writel(reg_val, (regs + EHCI_OPR_PORTSC));
}

static void ehci_test_mode(const struct ehci_hcd *ehci,
        uint32_t regs, u32 test_mode)
{
    unsigned int reg_val = 0;

    reg_val =  USBC_Readl(regs + EHCI_OPR_PORTSC);
    reg_val &= ~(0x0f<<16);
    reg_val |= test_mode;
    USBC_Writel(reg_val, (regs + EHCI_OPR_PORTSC));
}

static void __ehci_ed_test(const struct ehci_hcd *ehci,
        uint32_t regs, __u32 test_mode)
{
    printf("regs: 0x%x\n", regs);
    ehci_set_interrupt_enable(ehci, regs, 0x00);
    ehci_disable_periodic_schedule(ehci, regs);
    ehci_disable_async_schedule(ehci, regs);

    ehci_set_config_flag(ehci, regs);

    ehci_test_stop(ehci, regs);
    ehci_test_reset(ehci, regs);

    /* Wait until EHCI reset complete. */
    while (!ehci_test_reset_complete(ehci, regs))
        ;

    if (!ehci_is_halt(ehci, regs)) {
        DMSG_ERR("%s_%d\n", __func__, __LINE__);
    }

    ehci_start(ehci, regs);
    /* Wait until EHCI to be not halt. */
    while (ehci_is_halt(ehci, regs))
        DMSG_ERR("%s_%d\n", __func__, __LINE__);
        ;

    /* Ehci start, config to test. */
    ehci_set_config_flag(ehci, regs);
    ehci_port_control(ehci, regs, 0, EHCI_PORTSC_POWER);

    ehci_disable_periodic_schedule(ehci, regs);
    ehci_disable_async_schedule(ehci, regs);

    /* Put port suspend. */
    ehci_put_port_suspend(ehci, regs);

    ehci_test_stop(ehci, regs);

    while ((!ehci_is_halt(ehci, regs)))
        DMSG_ERR("%s_%d\n", __func__, __LINE__);
        ;

    /* Test pack. */
    DMSG_INFO("Start Host Test,mode:0x%x!\n", test_mode);
    ehci_test_mode(ehci, regs, test_mode);
    DMSG_INFO("End Host Test,mode:0x%x!\n", test_mode);
}

unsigned int ehci_ed_test(int hci_num, const char *buf, unsigned int count)
{
    __u32 test_mode = 0;
    struct sunxi_hci_hcd *sunxi_ehci = &g_sunxi_ehci[hci_num];
    struct hc_gen_dev *hcd  = sunxi_ehci->hcd;
    struct ehci_hcd *ehci   = NULL;

    ehci = hcd_to_ehci(hcd);
    if (ehci == NULL) {
        DMSG_PANIC("ERR: ehci is null\n");
        return 0;
    }
    DMSG_INFO("ehci_ed_test:%s\n", buf);
    if (!strncmp(buf, "test_not_operating", 18)) {
        test_mode = EHCI_PORTSC_PTC_DIS;
        DMSG_INFO("test_mode:0x%x\n", test_mode);
    } else if (!strncmp(buf, "test_j_state", 12)) {
        test_mode = EHCI_PORTSC_PTC_J;
        DMSG_INFO("test_mode:0x%x\n", test_mode);
    } else if (!strncmp(buf, "test_k_state", 12)) {
        test_mode = EHCI_PORTSC_PTC_K;
        DMSG_INFO("test_mode:0x%x\n", test_mode);
    } else if (!strncmp(buf, "test_se0_nak", 12)) {
        test_mode = EHCI_PORTSC_PTC_SE0NAK;
        DMSG_INFO("test_mode:0x%x\n", test_mode);
    } else if (!strncmp(buf, "test_pack", 9)) {
        test_mode = EHCI_PORTSC_PTC_PACKET;
        DMSG_INFO("test_mode:0x%x\n", test_mode);
    } else if (!strncmp(buf, "test_force_enable", 17)) {
        test_mode = EHCI_PORTSC_PTC_FORCE;
        DMSG_INFO("test_mode:0x%x\n", test_mode);
    } else if (!strncmp(buf, "test_mask", 9)) {
        test_mode = EHCI_PORTSC_PTC_MASK;
        DMSG_INFO("test_mode:0x%x\n", test_mode);
    } else {
        DMSG_PANIC("ERR: test_mode Argment is invalid\n");
        return count;
    }

    printf("regs: 0x%x\n", sunxi_ehci->usb_vbase);
    __ehci_ed_test(ehci, sunxi_ehci->usb_vbase, test_mode);

    return count;
}
unsigned int ehci_usb_driverlevel_adjust(int hci_num, int driverlevel)
{
    struct sunxi_hci_hcd *sunxi_ehci = &g_sunxi_ehci[hci_num];
    usb_new_phy_adjust(sunxi_ehci, driverlevel);
    return 0;
}

