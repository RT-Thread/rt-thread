/**
 * drivers/usb/host/sunxi_hci.h
 * (C) Copyright 2010-2015
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * yangnaitian, 2011-5-24, create this file
 *
 * Include file for SUNXI HCI Host Controller Driver
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 */

#ifndef __SUNXI_HCI_SUNXI_H__
#define __SUNXI_HCI_SUNXI_H__

//#include <linux/delay.h>
//#include <linux/types.h>
//
//#include <linux/io.h>
//#include <linux/irq.h>
//#include <linux/of_gpio.h>
//#include <linux/sunxi-gpio.h>
//
//#include <log.h>
//
//#include <linux/pm_wakeirq.h>
//#include <linux/regulator/consumer.h>

#include <platform_usb.h>
#include <usb_os_platform.h>
#include <stdlib.h>
#include <hal_clk.h>


extern int usb_disabled(void);

#if defined(CONFIG_AW_AXP)
extern s32 axp_usb_vbus_output(int high);
#endif

#define  DMSG_ERR(format, args...)      pr_err("hci: "format, ##args)
#define  DMSG_PRINT(stuff...)           printk(stuff)

#define HCI_USBC_NO     "hci_ctrl_no"


#define HCI0_USBC_NO    0
#define HCI1_USBC_NO    1
#define HCI2_USBC_NO    2
#define HCI3_USBC_NO    3


//static uint32_t hci_irq_num[] =
//{
//  SUNXI_USB_EHCI0_IRQ,
//  SUNXI_USB_EHCI1_IRQ,
//};
#define STANDBY_TIMEOUT 30000

/*
 * Support Low-power mode USB standby.
 */
#if defined(CONFIG_ARCH_SUN8IW15) || defined(CONFIG_ARCH_SUN50IW9) \
    || defined(CONFIG_ARCH_SUN50IW10)
#define SUNXI_USB_STANDBY_LOW_POW_MODE
#endif
/*no cpus*/
#if defined(CONFIG_ARCH_SUN50IW9) || defined(CONFIG_ARCH_SUN50IW10)
#define SUNXI_USB_STANDBY_NEW_MODE
#endif

#if 0
#define DMSG_DEBUG                              DMSG_PRINT
#else
#define DMSG_DEBUG(...)
#endif

#if 1
#define DMSG_INFO                               DMSG_PRINT
#else
#define DMSG_INFO(...)
#endif

#if 1
#define DMSG_PANIC                              DMSG_ERR
#else
#define DMSG_PANIC(...)
#endif

#define  USBC_Readb(reg)                        (*((volatile unsigned char  *)(long)(reg)))
#define  USBC_Readw(reg)                        (*((volatile unsigned short *)(reg)))
#define  USBC_Readl(reg)                        (*((volatile unsigned int *)(long)(reg)))

#define  USBC_Writeb(value, reg)                (*((volatile unsigned char  *)(long)(reg)) = (unsigned char)(value))
#define  USBC_Writew(value, reg)                (*((volatile unsigned short *)(reg)) = (unsigned short)(value))
#define  USBC_Writel(value, reg)                (*((volatile unsigned int *)(long)(reg)) = (unsigned int)(value))

#define  USBC_REG_test_bit_b(bp, reg)           (USBC_Readb(reg) & (1 << (bp)))
#define  USBC_REG_test_bit_w(bp, reg)           (USBC_Readw(reg) & (1 << (bp)))
#define  USBC_REG_test_bit_l(bp, reg)           (USBC_Readl(reg) & (1 << (bp)))

#define  USBC_REG_set_bit_b(bp, reg)            (USBC_Writeb((USBC_Readb(reg) | (1 << (bp))), (reg)))
#define  USBC_REG_set_bit_w(bp, reg)            (USBC_Writew((USBC_Readw(reg) | (1 << (bp))), (reg)))
#define  USBC_REG_set_bit_l(bp, reg)            (USBC_Writel((USBC_Readl(reg) | (1 << (bp))), (reg)))

#define  USBC_REG_clear_bit_b(bp, reg)          (USBC_Writeb((USBC_Readb(reg) & (~(1 << (bp)))), (reg)))
#define  USBC_REG_clear_bit_w(bp, reg)          (USBC_Writew((USBC_Readw(reg) & (~(1 << (bp)))), (reg)))
#define  USBC_REG_clear_bit_l(bp, reg)          (USBC_Writel((USBC_Readl(reg) & (~(1 << (bp)))), (reg)))

#define SUNXI_USB_EHCI_BASE_OFFSET              0x00
#define SUNXI_USB_OHCI_BASE_OFFSET              0x400
#define SUNXI_USB_EHCI_LEN                      0x58
#define SUNXI_USB_OHCI_LEN                      0x58

#define SUNXI_USB_EHCI_TIME_INT         0x30
#define SUNXI_USB_EHCI_STANDBY_IRQ_STATUS   1
#define SUNXI_USB_EHCI_STANDBY_IRQ      2

#define SUNXI_USB_PMU_IRQ_ENABLE                0x800
#define SUNXI_HCI_CTRL_3            0X808
#define SUNXI_HCI_PHY_CTRL                      0x810
#define SUNXI_HCI_PHY_TUNE                      0x818
#define SUNXI_HCI_UTMI_PHY_STATUS               0x824
#define SUNXI_HCI_CTRL_3_REMOTE_WAKEUP      3
#define SUNXI_HCI_RC16M_CLK_ENBALE      2
#define SUNXI_HCI_PHY_CTRL_SIDDQ                3

#define SUNXI_OTG_PHY_CTRL  0x410
#define SUNXI_OTG_PHY_CFG   0x420
#define SUNXI_OTG_PHY_STATUS    0x424
#define SUNXI_USBC_REG_INTUSBE  0x0050

#define EHCI_CAP_OFFSET     (0x00)
#define EHCI_CAP_LEN        (0x10)

#define EHCI_CAP_CAPLEN     (EHCI_CAP_OFFSET + 0x00)
#define EHCI_CAP_HCIVER     (EHCI_CAP_OFFSET + 0x00)
#define EHCI_CAP_HCSPAR     (EHCI_CAP_OFFSET + 0x04)
#define EHCI_CAP_HCCPAR     (EHCI_CAP_OFFSET + 0x08)
#define EHCI_CAP_COMPRD     (EHCI_CAP_OFFSET + 0x0c)


#define EHCI_OPR_OFFSET     (EHCI_CAP_OFFSET + EHCI_CAP_LEN)

#define EHCI_OPR_USBCMD     (EHCI_OPR_OFFSET + 0x00)
#define EHCI_OPR_USBSTS     (EHCI_OPR_OFFSET + 0x04)
#define EHCI_OPR_USBINTR    (EHCI_OPR_OFFSET + 0x08)
#define EHCI_OPR_FRINDEX    (EHCI_OPR_OFFSET + 0x0c)
#define EHCI_OPR_CRTLDSS    (EHCI_OPR_OFFSET + 0x10)
#define EHCI_OPR_PDLIST     (EHCI_OPR_OFFSET + 0x14)
#define EHCI_OPR_ASLIST     (EHCI_OPR_OFFSET + 0x18)
#define EHCI_OPR_CFGFLAG    (EHCI_OPR_OFFSET + 0x40)
#define EHCI_OPR_PORTSC     (EHCI_OPR_OFFSET + 0x44)

/**
 * PORT Control and Status Register
 * port_no is 0 based, 0, 1, 2, .....
 *
 * Reg EHCI_OPR_PORTSC
 */

/* Port Test Control bits */
#define EHCI_PORTSC_PTC_MASK    (0xf<<16)
#define EHCI_PORTSC_PTC_DIS (0x0<<16)
#define EHCI_PORTSC_PTC_J   (0x1<<16)
#define EHCI_PORTSC_PTC_K   (0x2<<16)
#define EHCI_PORTSC_PTC_SE0NAK  (0x3<<16)
#define EHCI_PORTSC_PTC_PACKET  (0x4<<16)
#define EHCI_PORTSC_PTC_FORCE   (0x5<<16)

#define EHCI_PORTSC_OWNER   (0x1<<13)
#define EHCI_PORTSC_POWER   (0x1<<12)

#define EHCI_PORTSC_LS_MASK (0x3<<10)
#define EHCI_PORTSC_LS_SE0  (0x0<<10)
#define EHCI_PORTSC_LS_J    (0x2<<10)
#define EHCI_PORTSC_LS_K    (0x1<<10)
#define EHCI_PORTSC_LS_UDF  (0x3<<10)

#define EHCI_PORTSC_RESET   (0x1<<8)
#define EHCI_PORTSC_SUSPEND (0x1<<7)
#define EHCI_PORTSC_RESUME  (0x1<<6)
#define EHCI_PORTSC_OCC     (0x1<<5)
#define EHCI_PORTSC_OC      (0x1<<4)
#define EHCI_PORTSC_PEC     (0x1<<3)
#define EHCI_PORTSC_PE      (0x1<<2)
#define EHCI_PORTSC_CSC     (0x1<<1)
#define EHCI_PORTSC_CCS     (0x1<<0)

#define EHCI_PORTSC_CHANGE  (EHCI_PORTSC_OCC | EHCI_PORTSC_PEC | EHCI_PORTSC_CSC)

#define  SUNXI_USB_HCI_DEBUG

#define  KEY_USB_ENABLE                 "usb_used"
#define  KEY_USB_DRVVBUS_TYPE           "usb_drv_vbus_type"
#define  KEY_USB_DRVVBUS_GPIO           "usb_drv_vbus_gpio"
#define  KEY_USB_REGULATOR_IO           "usb_regulator_io"
#define  KEY_USB_REGULATOR_IO_VOL       "usb_regulator_vol"
#define  KEY_USB_WAKEUP_SUSPEND         "usb_wakeup_suspend"
#define  KEY_USB_HSIC_USBED             "usb_hsic_used"
#define  KEY_USB_HSIC_CTRL              "usb_hsic_ctrl"
#define  KEY_USB_HSIC_RDY_GPIO          "usb_hsic_rdy_gpio"
#define  KEY_USB_HSIC_REGULATOR_IO      "usb_hsic_regulator_io"
#define  KEY_WAKEUP_SOURCE              "wakeup-source"
#define  KEY_USB_PORT_TYPE              "usb_port_type"
#define  KEY_USB_DRIVER_LEVEL           "usbh_driver_level"
#define  KEY_USB_IRQ_FLAG               "usbh_irq_flag"

/* xHCI */
#define XHCI_RESOURCES_NUM  2
#define XHCI_REGS_START     0x0
#define XHCI_REGS_END       0x7fff

/* xHCI Operational Registers */
#define XHCI_OP_REGS_HCUSBCMD       0X0020
#define XHCI_OP_REGS_HCUSBSTS       0X0024
#define XHCI_OP_REGS_HCPORT1SC      0X0420
#define XHCI_OP_REGS_HCPORT1PMSC    0X0424

#define SUNXI_GLOBALS_REGS_START    0xc100
#define SUNXI_GLOBALS_REGS_END      0xc6ff

/* Global Registers */
#define SUNXI_GLOBALS_REGS_GCTL     0xc110
#define SUNXI_GUSB2PHYCFG(n)        (0xc200 + (n * 0x04))
#define SUNXI_GUSB3PIPECTL(n)       (0xc2c0 + (n * 0x04))

/* Interface Status and Control Register */
#define SUNXI_APP           0x10000
#define SUNXI_PIPE_CLOCK_CONTROL    0x10014
#define SUNXI_PHY_TUNE_LOW      0x10018
#define SUNXI_PHY_TUNE_HIGH     0x1001c
#define SUNXI_PHY_EXTERNAL_CONTROL  0x10020

/* Bit fields */

/* Global Configuration Register */
#define SUNXI_GCTL_PRTCAPDIR(n)     ((n) << 12)
#define SUNXI_GCTL_PRTCAP_HOST      1
#define SUNXI_GCTL_PRTCAP_DEVICE    2
#define SUNXI_GCTL_PRTCAP_OTG       3
#define SUNXI_GCTL_SOFITPSYNC       (0x01 << 10)
#define SUNXI_GCTL_CORESOFTRESET    (1 << 11)

/* Global USB2 PHY Configuration Register n */
#define SUNXI_USB2PHYCFG_SUSPHY     (0x01 << 6)
#define SUNXI_USB2PHYCFG_PHYSOFTRST (1 << 31)

/* Global USB3 PIPE Control Register */
#define SUNXI_USB3PIPECTL_PHYSOFTRST    (1 << 31)

/* USB2.0 Interface Status and Control Register */
#define SUNXI_APP_FOCE_VBUS (0x03 << 12)

/* PIPE Clock Control Register */
#define SUNXI_PPC_PIPE_CLK_OPEN (0x01 << 6)

/* PHY External Control Register */
#define SUNXI_PEC_EXTERN_VBUS   (0x03 << 1)
#define SUNXI_PEC_SSC_EN    (0x01 << 24)
#define SUNXI_PEC_REF_SSP_EN    (0x01 << 26)

/* PHY Tune High Register */
#define SUNXI_TX_DEEMPH_3P5DB(n)    ((n) << 19)
#define SUNXI_TX_DEEMPH_6DB(n)      ((n) << 13)
#define SUNXI_TX_SWING_FULL(n)      ((n) << 6)
#define SUNXI_LOS_BIAS(n)       ((n) << 3)
#define SUNXI_TXVBOOSTLVL(n)        ((n) << 0)

/* HCI UTMI PHY TUNE */
#define SUNXI_TX_VREF_TUNE_OFFSET   8
#define SUNXI_TX_RISE_TUNE_OFFSET   4
#define SUNXI_TX_RES_TUNE_OFFSET    2
#define SUNXI_TX_PREEMPAMP_TUNE_OFFSET  0
#define SUNXI_TX_VREF_TUNE      (0xf << SUNXI_TX_VREF_TUNE_OFFSET)
#define SUNXI_TX_RISE_TUNE      (0x3 << SUNXI_TX_RISE_TUNE_OFFSET)
#define SUNXI_TX_RES_TUNE       (0x3 << SUNXI_TX_RES_TUNE_OFFSET)
#define SUNXI_TX_PREEMPAMP_TUNE     (0x3 << SUNXI_TX_PREEMPAMP_TUNE_OFFSET)


enum sunxi_usbc_used {
    SUNXI_USB_DISABLE = 0,
    SUNXI_USB_ENABLE,
};

/*usb_type*/
enum sunxi_usbc_type {
    SUNXI_USB_UNKNOWN = 0,
    SUNXI_USB_EHCI,
    SUNXI_USB_OHCI,
    SUNXI_USB_XHCI,
};

enum usb_drv_vbus_type {
    USB_DRV_VBUS_TYPE_NULL = 0,
    USB_DRV_VBUS_TYPE_GIPO,
    USB_DRV_VBUS_TYPE_AXP,
};

/* 0: device only; 1: host only; 2: otg */
enum usb_port_type {
    USB_PORT_TYPE_DEVICE = 0,
    USB_PORT_TYPE_HOST,
    USB_PORT_TYPE_OTG,
};

enum usb_wakeup_source_type {
    SUPER_STANDBY = 0,
    USB_STANDBY,
    NORMAL_STANDBY,
};

// static hal_clk_id_t ehci_clk[] =
// {
    // HAL_CLK_PERIPH_USBEHCI0,
    // HAL_CLK_PERIPH_USBEHCI1,
// };

// static hal_clk_id_t phy_clk[] =
// {
    // SUNXI_CLK_USB0,
    // SUNXI_CLK_USB1,
// };

struct sunxi_hci_hcd {
    uint32_t usbc_no;                          /* usb controller number */
    uint32_t irq_no;                           /* interrupt number */
    char hci_name[32];                      /* hci name */
    int usbc_type;              /* usb controller type*/

    struct resource *usb_base_res;          /* USB  resources */
    struct resource *usb_base_req;          /* USB  resources */
    uint32_t    usb_vbase;             /* USB  base address */

    uint32_t    otg_vbase;             /* USB  base address */

    uint32_t    ehci_base;
    uint32_t ehci_reg_length;
    uint32_t    *ohci_base;
    uint32_t ohci_reg_length;

    struct resource *sram_base_res;         /* SRAM resources */
    struct resource *sram_base_req;         /* SRAM resources */
    uint32_t    *sram_vbase;            /* SRAM base address */
    uint32_t sram_reg_start;
    uint32_t sram_reg_length;

    struct resource *clock_base_res;        /* clock resources */
    struct resource *clock_base_req;        /* clock resources */
    uint32_t    *clock_vbase;           /* clock base address */
    uint32_t clock_reg_start;
    uint32_t clock_reg_length;

    struct resource *gpio_base_res;         /* gpio resources */
    struct resource *gpio_base_req;         /* gpio resources */
    uint32_t    *gpio_vbase;            /* gpio base address */
    uint32_t gpio_reg_start;
    uint32_t gpio_reg_length;

    struct resource *sdram_base_res;        /* sdram resources */
    struct resource *sdram_base_req;        /* sdram resources */
    uint32_t    *sdram_vbase;           /* sdram base address */
    uint32_t sdram_reg_start;
    uint32_t sdram_reg_length;

    struct platform_device *pdev;
    struct hc_gen_dev *hcd;

    struct clk  *ahb;                   /* ahb clock handle */
    struct clk  *mod_usb;               /* mod_usb otg clock handle */
    struct clk  *mod_usbphy;            /* PHY0 clock handle */
    struct clk  *hsic_usbphy;            /* hsic clock handle */
    struct clk  *pll_hsic;               /* pll_hsic clock handle */
    struct clk  *clk_usbhsic12m;          /* pll_hsic clock handle */

    struct clk  *clk_usbohci12m;          /* clk_usbohci12m clock handle */
    struct clk  *clk_hoscx2;              /* clk_hoscx2 clock handle */
    struct clk  *clk_hosc;                /* clk_hosc clock handle */
    struct clk  *clk_losc;            /* clk_losc clock handle */

    uint32_t clk_is_open;                      /* is usb clock open */

    hal_clk_id_t bus_clk_id;
    hal_clk_id_t phy_clk_id;
    uint32_t reset_phy_clk;
    uint32_t reset_bus_clk;
    hal_clk_id_t ohci_clk_id;

    hal_clk_t bus_clk;
    hal_clk_t phy_clk;
    hal_clk_t ohci_clk;

    struct reset_control    *reset_hci;
    struct reset_control    *reset_phy;

    //struct gpio_config drv_vbus_gpio_set;
    int drv_vbus_gpio_set;

    const char  *regulator_io;
    const char  *used_status;
    int   regulator_value;
    struct regulator *regulator_io_hdle;
    enum usb_drv_vbus_type drv_vbus_type;
    const char *drv_vbus_name;
    const char *det_vbus_name;
    int drv_vbus_gpio;
    int usb_irq_flag;
    int usb_driver_level;
    u32 drv_vbus_gpio_valid;
    u32 usb_restrict_valid;
    uint8_t power_flag;                        /* flag. power on or not */
    struct regulator *supply;

    int used;                              /* flag. in use or not */
    uint8_t probe;                             /* hc initialize */
    uint8_t no_suspend;                        /* when usb is being enable, stop system suspend */
    enum usb_port_type port_type;       /* usb port type */
    int wakeup_suspend;                       /* flag. not suspend */

    int wakeup_source_flag;

    int (*open_clock)(struct sunxi_hci_hcd *sunxi_hci, u32 ohci);
    int (*close_clock)(struct sunxi_hci_hcd *sunxi_hci, u32 ohci);
    void (*set_power)(struct sunxi_hci_hcd *sunxi_hci, int is_on);
    void (*port_configure)(struct sunxi_hci_hcd *sunxi_hci, u32 enable);
    void (*usb_passby)(struct sunxi_hci_hcd *sunxi_hci, u32 enable);
    void (*hci_phy_ctrl)(struct sunxi_hci_hcd *sunxi_hci, u32 enable);
#if 0
    /* xhci */
    struct resource xhci_resources[XHCI_RESOURCES_NUM];
    spinlock_t      lock;
    struct device       *dev;
    void            *mem;
    uint32_t    *regs;
    size_t      regs_size;
    uint32_t    *xhci_base;
    uint32_t xhci_reg_length;
#endif
    /* resume work */
    //struct work_struct resume_work;
    //struct completion standby_complete;
};

#ifdef CONFIG_PM
extern atomic_t g_sunxi_usb_super_standby;
#endif

int sunxi_hci_standby_completion(int usbc_type);
int init_sunxi_hci(int usbc_type, int hci_num);
int exit_sunxi_hci(struct sunxi_hci_hcd *sunxi_hci);
int sunxi_get_hci_num(struct platform_device *pdev);
void sunxi_set_host_hisc_rdy(struct sunxi_hci_hcd *sunxi_hci, int is_on);
void sunxi_set_host_vbus(struct sunxi_hci_hcd *sunxi_hci, int is_on);
int usb_phyx_tp_write(struct sunxi_hci_hcd *sunxi_hci,
        int addr, int data, int len);
int usb_phyx_write(struct sunxi_hci_hcd *sunxi_hci, int data);
int usb_phyx_read(struct sunxi_hci_hcd *sunxi_hci);
int usb_phyx_tp_read(struct sunxi_hci_hcd *sunxi_hci, int addr, int len);
int sunxi_usb_enable_xhci(void);
int sunxi_usb_disable_xhci(void);
#ifdef SUNXI_USB_STANDBY_LOW_POW_MODE
void sunxi_hci_set_siddq(struct sunxi_hci_hcd *sunxi_hci, int is_on);
void sunxi_hci_set_wakeup_ctrl(struct sunxi_hci_hcd *sunxi_hci, int is_on);
void sunxi_hci_set_rc_clk(struct sunxi_hci_hcd *sunxi_hci, int is_on);
void sunxi_hci_set_standby_irq(struct sunxi_hci_hcd *sunxi_hci, int is_on);
void sunxi_hci_clean_standby_irq(struct sunxi_hci_hcd *sunxi_hci);
#endif

int hci_clock_init(struct sunxi_hci_hcd *sunxi_hci);
int open_clock(struct sunxi_hci_hcd *sunxi_hci, u32 ohci);
void usb_passby(struct sunxi_hci_hcd *sunxi_hci, u32 enable);
int close_clock(struct sunxi_hci_hcd *sunxi_hci, u32 ohci);

void sunxi_set_vbus(struct sunxi_hci_hcd *sunxi_hci, int is_on);
void sunxi_hci_get_config_param(struct sunxi_hci_hcd *sunxi_hci);
void usb_new_phy_adjust(struct sunxi_hci_hcd *sunxi_hci, int driver_level);
#endif /* __SUNXI_HCI_SUNXI_H__ */

