/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026/06/10     Tim          first version
 */
#include <rtthread.h>
#include <stdint.h>
#include <stddef.h>

#include "board.h"
#include "usb_config.h"

#ifdef CONFIG_USB_DCACHE_ENABLE
#include "fsl_cache.h"
#endif

#ifdef RT_CHERRYUSB_HOST
#include "usbh_core.h"
#endif

#define RT1180_USB_EHCI0_ID       2U
#define RT1180_USB_EHCI_COUNT     2U
#define RT1180_USB_INVALID_INDEX  0xffU
#define RT1180_USB_IRQ_PRIORITY   3U

typedef enum _usb_controller_index
{
    kUSB_ControllerEhci0 = RT1180_USB_EHCI0_ID,
    kUSB_ControllerEhci1 = RT1180_USB_EHCI0_ID + 1U,
} usb_controller_index_t;

typedef struct _usb_phy_config_struct
{
    uint8_t D_CAL;
    uint8_t TXCAL45DP;
    uint8_t TXCAL45DM;
} usb_phy_config_struct_t;

static void (*s_usb_irq_handler)(uint8_t busid);
static uint8_t s_usb_clock_initialized[RT1180_USB_EHCI_COUNT];

static uint8_t rt1180_usb_selected_index(void)
{
#if defined(BSP_CHERRYUSB_USING_OTG2)
    return 1U;
#else
    return 0U;
#endif
}

static uint8_t rt1180_usb_index_from_controller(uint8_t controller_id)
{
#if defined(BSP_CHERRYUSB_USING_OTG2)
    (void)controller_id;
    return 1U;
#else
    if ((controller_id >= RT1180_USB_EHCI0_ID) &&
        (controller_id < (RT1180_USB_EHCI0_ID + RT1180_USB_EHCI_COUNT)))
    {
        return controller_id - RT1180_USB_EHCI0_ID;
    }

    return RT1180_USB_INVALID_INDEX;
#endif
}

static usb_controller_index_t rt1180_usb_controller_id(uint8_t busid)
{
    (void)busid;
    return (usb_controller_index_t)(RT1180_USB_EHCI0_ID + rt1180_usb_selected_index());
}

#if defined(RT_CHERRYUSB_HOST) || defined(BSP_CHERRYUSB_DEVICE_CDC_ACM_ECHO) || \
    defined(RT_CHERRYUSB_DEVICE_TEMPLATE_CDC_ACM) || defined(RT_CHERRYUSB_DEVICE_TEMPLATE_MSC)
static uintptr_t rt1180_usb_base(uint8_t busid)
{
    static const uintptr_t usb_base[] = USBHS_STACK_BASE_ADDRS;

    (void)busid;
    return usb_base[rt1180_usb_selected_index()];
}
#endif

static IRQn_Type rt1180_usb_irqn(uint8_t busid)
{
    static const IRQn_Type usb_irq[] = USBHS_IRQS;

    (void)busid;
    return usb_irq[rt1180_usb_selected_index()];
}

static USBPHY_Type *rt1180_usb_phy(uint8_t index)
{
    static const uintptr_t usbphy_base[] = USBPHY_STACK_BASE_ADDRS;

    return (USBPHY_Type *)usbphy_base[index];
}

static USBNC_Type *rt1180_usb_nc(uint8_t index)
{
    static const uintptr_t usbnc_base[] = USBNC_STACK_BASE_ADDRS;

    return (USBNC_Type *)usbnc_base[index];
}

static void rt1180_usb_nc_init(uint8_t index)
{
    USBNC_Type *nc = rt1180_usb_nc(index);

#if defined(USBNC_CTRL1_OVER_CUR_DIS_MASK)
    nc->CTRL1 |= USBNC_CTRL1_OVER_CUR_DIS_MASK;
#endif

#if defined(USBNC_CTRL2_UTMI_CLK_VLD_MASK)
    nc->CTRL2 |= USBNC_CTRL2_UTMI_CLK_VLD_MASK;
#endif

#if defined(USBNC_USB_OTGn_PHY_CTRL_0_UTMI_CLK_VLD_MASK)
    nc->USB_OTGn_PHY_CTRL_0 |= USBNC_USB_OTGn_PHY_CTRL_0_UTMI_CLK_VLD_MASK;
#endif
}

static void rt1180_usb_phy_enable_vbus_override(USBPHY_Type *phy)
{
#if defined(RT_CHERRYUSB_DEVICE) && defined(USBPHY_USB1_VBUS_DETECT_SET_VBUS_OVERRIDE_EN_MASK) && \
    defined(USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_OVERRIDE_MASK) && \
    defined(USBPHY_USB1_VBUS_DETECT_SET_AVALID_OVERRIDE_MASK) && \
    defined(USBPHY_USB1_VBUS_DETECT_SET_BVALID_OVERRIDE_MASK)
    uint32_t vbus_detect =
        USBPHY_USB1_VBUS_DETECT_SET_VBUS_OVERRIDE_EN_MASK |
        USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_OVERRIDE_MASK |
        USBPHY_USB1_VBUS_DETECT_SET_AVALID_OVERRIDE_MASK |
        USBPHY_USB1_VBUS_DETECT_SET_BVALID_OVERRIDE_MASK;

#if defined(USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_EN_MASK) && \
    defined(USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_MASK)
    vbus_detect |= USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_EN_MASK |
                   USBPHY_USB1_VBUS_DETECT_SET_ID_OVERRIDE_MASK;
#endif

    phy->USB1_VBUS_DETECT_SET = vbus_detect;
#elif defined(RT_CHERRYUSB_DEVICE) && defined(USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_TO_SESSVALID_MASK)
    phy->USB1_VBUS_DETECT_SET = USBPHY_USB1_VBUS_DETECT_SET_VBUSVALID_TO_SESSVALID_MASK;
#else
    (void)phy;
#endif
}

void *USB_EhciPhyGetBase(uint8_t controller_id)
{
    uint8_t index = rt1180_usb_index_from_controller(controller_id);

    if (index >= RT1180_USB_EHCI_COUNT)
    {
        return RT_NULL;
    }

    return (void *)rt1180_usb_phy(index);
}

uint32_t USB_EhciPhyInit(uint8_t controller_id, uint32_t freq, usb_phy_config_struct_t *phy_config)
{
    uint8_t index = rt1180_usb_index_from_controller(controller_id);
    USBPHY_Type *phy;

    (void)freq;

    if (index >= RT1180_USB_EHCI_COUNT)
    {
        return (uint32_t)-1;
    }

    phy = (USBPHY_Type *)USB_EhciPhyGetBase(controller_id);
    if (phy == RT_NULL)
    {
        return (uint32_t)-1;
    }

    rt1180_usb_nc_init(index);

#if defined(FSL_FEATURE_USBPHY_HAS_TRIM_OVERRIDE_EN) && (FSL_FEATURE_USBPHY_HAS_TRIM_OVERRIDE_EN > 0U)
    phy->TRIM_OVERRIDE_EN = 0x001fU;
#endif

#if defined(USBPHY_CTRL_CLR_SFTRST_MASK)
    phy->CTRL_CLR = USBPHY_CTRL_CLR_SFTRST_MASK;
#endif
#if defined(USBPHY_CTRL_CLR_CLKGATE_MASK)
    phy->CTRL_CLR = USBPHY_CTRL_CLR_CLKGATE_MASK;
#endif

    phy->CTRL_SET = USBPHY_CTRL_SET_ENUTMILEVEL2_MASK | USBPHY_CTRL_SET_ENUTMILEVEL3_MASK;
    phy->PWD = 0U;

    if (phy_config != RT_NULL)
    {
        phy->TX = (phy->TX & ~(USBPHY_TX_D_CAL_MASK | USBPHY_TX_TXCAL45DN_MASK | USBPHY_TX_TXCAL45DP_MASK)) |
                  USBPHY_TX_D_CAL(phy_config->D_CAL) |
                  USBPHY_TX_TXCAL45DP(phy_config->TXCAL45DP) |
                  USBPHY_TX_TXCAL45DN(phy_config->TXCAL45DM);
    }

    rt1180_usb_phy_enable_vbus_override(phy);

    return 0U;
}

uint32_t USB_EhciLowPowerPhyInit(uint8_t controller_id, uint32_t freq, usb_phy_config_struct_t *phy_config)
{
    USBPHY_Type *phy;
    uint32_t status;

    status = USB_EhciPhyInit(controller_id, freq, phy_config);
    if (status != 0U)
    {
        return status;
    }

    phy = (USBPHY_Type *)USB_EhciPhyGetBase(controller_id);
    if (phy == RT_NULL)
    {
        return (uint32_t)-1;
    }

#if defined(USBPHY_CTRL_CLR_AUTORESUME_EN_MASK)
    phy->CTRL_CLR = USBPHY_CTRL_CLR_AUTORESUME_EN_MASK;
#elif defined(USBPHY_CTRL_SET_ENAUTO_PWRON_PLL_MASK)
    phy->CTRL_SET = USBPHY_CTRL_SET_ENAUTO_PWRON_PLL_MASK;
#endif
#if defined(USBPHY_CTRL_SET_ENAUTOCLR_CLKGATE_MASK)
    phy->CTRL_SET = USBPHY_CTRL_SET_ENAUTOCLR_CLKGATE_MASK;
#endif
#if defined(USBPHY_CTRL_SET_ENAUTOCLR_PHY_PWD_MASK)
    phy->CTRL_SET = USBPHY_CTRL_SET_ENAUTOCLR_PHY_PWD_MASK;
#endif

    return 0U;
}

void USB_EhciPhyDeinit(uint8_t controller_id)
{
    USBPHY_Type *phy = (USBPHY_Type *)USB_EhciPhyGetBase(controller_id);

    if (phy == RT_NULL)
    {
        return;
    }

#if defined(USBPHY_PLL_SIC_PLL_POWER_MASK)
    phy->PLL_SIC &= ~USBPHY_PLL_SIC_PLL_POWER_MASK;
#endif
#if defined(USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK)
    phy->PLL_SIC &= ~USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK;
#endif
#if defined(USBPHY_CTRL_SET_CLKGATE_MASK)
    phy->CTRL_SET = USBPHY_CTRL_SET_CLKGATE_MASK;
#endif
}

void USB_EhcihostPhyDisconnectDetectCmd(uint8_t controller_id, uint8_t enable)
{
    USBPHY_Type *phy = (USBPHY_Type *)USB_EhciPhyGetBase(controller_id);

    if (phy == RT_NULL)
    {
        return;
    }

    if (enable)
    {
#if defined(USBPHY_CTRL_SET_ENHOSTDISCONDETECT_MASK)
        phy->CTRL_SET = USBPHY_CTRL_SET_ENHOSTDISCONDETECT_MASK;
#elif defined(USBPHY_CTRL_ENHOSTDISCONDETECT_MASK)
        phy->CTRL |= USBPHY_CTRL_ENHOSTDISCONDETECT_MASK;
#endif
    }
    else
    {
#if defined(USBPHY_CTRL_CLR_ENHOSTDISCONDETECT_MASK)
        phy->CTRL_CLR = USBPHY_CTRL_CLR_ENHOSTDISCONDETECT_MASK;
#elif defined(USBPHY_CTRL_ENHOSTDISCONDETECT_MASK)
        phy->CTRL &= ~USBPHY_CTRL_ENHOSTDISCONDETECT_MASK;
#endif
    }
}

static bool USB_ClockInit(uint8_t busid)
{
    bool clock_ok;
    uint8_t index = rt1180_usb_selected_index();
    usb_controller_index_t controller_id = rt1180_usb_controller_id(busid);
    usb_phy_config_struct_t phy_config = {
        BOARD_USB_PHY_D_CAL,
        BOARD_USB_PHY_TXCAL45DP,
        BOARD_USB_PHY_TXCAL45DM,
    };

    if (s_usb_clock_initialized[index])
    {
        return true;
    }

    if (index == 0U)
    {
        clock_ok = CLOCK_EnableUsbhs0PhyPllClock(kCLOCK_Usbphy480M, BOARD_XTAL0_CLK_HZ);
        clock_ok = CLOCK_EnableUsbhs0Clock(kCLOCK_UsbSrcUnused, BOARD_XTAL0_CLK_HZ) && clock_ok;
    }
    else
    {
        clock_ok = CLOCK_EnableUsbhs1PhyPllClock(kCLOCK_Usbphy480M, BOARD_XTAL0_CLK_HZ);
        clock_ok = CLOCK_EnableUsbhs1Clock(kCLOCK_UsbSrcUnused, BOARD_XTAL0_CLK_HZ) && clock_ok;
    }

    if (!clock_ok)
    {
        rt_kprintf("RT1180 CherryUSB OTG%u clock init failed\n", (unsigned int)(index + 1U));
        return false;
    }

    if (USB_EhciPhyInit((uint8_t)controller_id, BOARD_XTAL0_CLK_HZ, &phy_config) != 0U)
    {
        rt_kprintf("RT1180 CherryUSB OTG%u PHY init failed\n", (unsigned int)(index + 1U));
        return false;
    }

    s_usb_clock_initialized[index] = 1U;
    return true;
}

static void USB_ClockDeinit(uint8_t busid)
{
    uint8_t index = rt1180_usb_selected_index();

    if (!s_usb_clock_initialized[index])
    {
        return;
    }

    USB_EhciPhyDeinit((uint8_t)rt1180_usb_controller_id(busid));

    if (index == 0U)
    {
        CLOCK_DisableUsbhs0PhyPllClock();
    }
    else
    {
        CLOCK_DisableUsbhs1PhyPllClock();
    }

    s_usb_clock_initialized[index] = 0U;
}

static void rt1180_usb_irq_enable(uint8_t busid)
{
    IRQn_Type irq = rt1180_usb_irqn(busid);

    NVIC_SetPriority(irq, RT1180_USB_IRQ_PRIORITY);
    NVIC_ClearPendingIRQ(irq);
    EnableIRQ(irq);
}

static void rt1180_usb_irq_disable(uint8_t busid)
{
    DisableIRQ(rt1180_usb_irqn(busid));
}

static void rt1180_usb_irq_dispatch(void)
{
    if (s_usb_irq_handler == RT_NULL)
    {
        return;
    }

    rt_interrupt_enter();
    s_usb_irq_handler(0);
    rt_interrupt_leave();
}

#if defined(BSP_CHERRYUSB_USING_OTG2)
void USB_OTG2_IRQHandler(void)
{
    rt1180_usb_irq_dispatch();
}
#else
void USB_OTG1_IRQHandler(void)
{
    rt1180_usb_irq_dispatch();
}
#endif

#ifdef RT_CHERRYUSB_DEVICE
void usb_dc_low_level_init(uint8_t busid)
{
    extern void USBD_IRQHandler(uint8_t busid);

    if (!USB_ClockInit(busid))
    {
        return;
    }

    s_usb_irq_handler = USBD_IRQHandler;
    rt1180_usb_irq_enable(busid);
}

void usb_dc_low_level_deinit(uint8_t busid)
{
    rt1180_usb_irq_disable(busid);
    s_usb_irq_handler = RT_NULL;
    USB_ClockDeinit(busid);
}
#endif

#ifdef RT_CHERRYUSB_HOST
static void rt1180_usb_host_mode_init(USB_Type *ptr)
{
    ptr->USBMODE &= ~USB_USBMODE_CM_MASK;
    ptr->USBMODE |= USB_USBMODE_CM(3);
    ptr->USBMODE &= ~USB_USBMODE_ES_MASK;

    ptr->PORTSC1 &= ~USB_PORTSC1_STS_MASK;
    ptr->PORTSC1 &= ~USB_PORTSC1_PTW_MASK;
    ptr->USBCMD &= ~USB_USBCMD_ITC_MASK;
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    extern void USBH_IRQHandler(uint8_t busid);

    if (!USB_ClockInit(bus->hcd.hcd_id))
    {
        return;
    }

    s_usb_irq_handler = USBH_IRQHandler;
    rt1180_usb_irq_enable(bus->hcd.hcd_id);
}

void usb_hc_low_level2_init(struct usbh_bus *bus)
{
    rt1180_usb_host_mode_init((USB_Type *)bus->hcd.reg_base);
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    rt1180_usb_irq_disable(bus->hcd.hcd_id);
    s_usb_irq_handler = RT_NULL;
    USB_ClockDeinit(bus->hcd.hcd_id);
}

uint8_t usbh_get_port_speed(struct usbh_bus *bus, const uint8_t port)
{
    uint8_t speed;
    USB_Type *ptr = (USB_Type *)bus->hcd.reg_base;

    (void)port;
    speed = (uint8_t)((ptr->PORTSC1 & USB_PORTSC1_PSPD_MASK) >> USB_PORTSC1_PSPD_SHIFT);

    if (speed == 0x00U)
    {
        return USB_SPEED_FULL;
    }
    if (speed == 0x01U)
    {
        return USB_SPEED_LOW;
    }
    if (speed == 0x02U)
    {
        USB_EhcihostPhyDisconnectDetectCmd((uint8_t)rt1180_usb_controller_id(bus->hcd.hcd_id), 1U);
        return USB_SPEED_HIGH;
    }

    return 0U;
}

static int cherryusb_hostinit(void)
{
    usbh_initialize(0, rt1180_usb_base(0), RT_NULL);
    return 0;
}
INIT_COMPONENT_EXPORT(cherryusb_hostinit);
#endif

#if defined(BSP_CHERRYUSB_DEVICE_CDC_ACM_ECHO) || defined(RT_CHERRYUSB_DEVICE_TEMPLATE_CDC_ACM)
static int cherryusb_cdc_acm_init(void)
{
    extern void rt1180_cdc_acm_init(uint8_t busid, uintptr_t reg_base);

    rt1180_cdc_acm_init(0, rt1180_usb_base(0));
    return 0;
}
INIT_COMPONENT_EXPORT(cherryusb_cdc_acm_init);
#endif

#ifdef RT_CHERRYUSB_DEVICE_TEMPLATE_MSC
static int cherryusb_msc_init(void)
{
    extern void msc_ram_init(uint8_t busid, uintptr_t reg_base);

    msc_ram_init(0, rt1180_usb_base(0));
    return 0;
}
INIT_COMPONENT_EXPORT(cherryusb_msc_init);
#endif

#ifdef CONFIG_USB_DCACHE_ENABLE
void usb_dcache_clean(uintptr_t addr, size_t size)
{
    DCACHE_CleanByRange(addr, size);
}

void usb_dcache_invalidate(uintptr_t addr, size_t size)
{
    DCACHE_InvalidateByRange(addr, size);
}

void usb_dcache_flush(uintptr_t addr, size_t size)
{
    DCACHE_CleanInvalidateByRange(addr, size);
}
#endif
