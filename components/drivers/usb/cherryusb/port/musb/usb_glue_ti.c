/*
 * Copyright (c) 2026, sakumisu
 * Copyright (c) 2026, MDLZCOOL
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbh_core.h"
#include "usb_musb_reg.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_usb.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"

#define TM4C_MUSB_RAM_SIZE 4096

// clang-format off
static struct musb_fifo_cfg musb_device_table[] = {
{ .ep_num =  0, .style = FIFO_TXRX, .maxpacket = 64,   },
{ .ep_num =  1, .style = FIFO_TXRX, .maxpacket = 1024, },
{ .ep_num =  2, .style = FIFO_TXRX, .maxpacket = 1024, },
{ .ep_num =  3, .style = FIFO_TXRX, .maxpacket = 1024, },
{ .ep_num =  4, .style = FIFO_TXRX, .maxpacket = 512,  },
{ .ep_num =  5, .style = FIFO_TXRX, .maxpacket = 256,  },
{ .ep_num =  6, .style = FIFO_TXRX, .maxpacket = 128,  },
{ .ep_num =  7, .style = FIFO_TXRX, .maxpacket = 64,   },
};

static struct musb_fifo_cfg musb_host_table[] = {
{ .ep_num =  0, .style = FIFO_TXRX, .maxpacket = 64,   },
{ .ep_num =  1, .style = FIFO_TXRX, .maxpacket = 1024, },
{ .ep_num =  2, .style = FIFO_TXRX, .maxpacket = 1024, },
{ .ep_num =  3, .style = FIFO_TXRX, .maxpacket = 1024, },
{ .ep_num =  4, .style = FIFO_TXRX, .maxpacket = 512,  },
{ .ep_num =  5, .style = FIFO_TXRX, .maxpacket = 256,  },
{ .ep_num =  6, .style = FIFO_TXRX, .maxpacket = 128,  },
{ .ep_num =  7, .style = FIFO_TXRX, .maxpacket = 64,   },
};
// clang-format on

static void (*g_usb_irq_handler)(uint8_t busid) = NULL;

extern void USBH_IRQHandler(uint8_t busid);
extern void USBD_IRQHandler(uint8_t busid);

__WEAK void USBD_IRQHandler(uint8_t busid)
{
    (void)busid;
}

__WEAK void USBH_IRQHandler(uint8_t busid)
{
    (void)busid;
}

void USB0_Handler(void)
{
    if (g_usb_irq_handler) {
        g_usb_irq_handler(0);
    }
}

uint8_t usbd_get_musb_fifo_cfg(struct musb_fifo_cfg **cfg)
{
    *cfg = musb_device_table;
    return sizeof(musb_device_table) / sizeof(musb_device_table[0]);
}

uint8_t usbh_get_musb_fifo_cfg(struct musb_fifo_cfg **cfg)
{
    *cfg = musb_host_table;
    return sizeof(musb_host_table) / sizeof(musb_host_table[0]);
}

uint32_t usb_get_musb_ram_size(void)
{
    return TM4C_MUSB_RAM_SIZE;
}

void usbd_musb_delay_ms(uint8_t ms)
{
    /* implement later */
}

void usb_dc_low_level_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_USB0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_USB0))
        ;
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
        ;
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
        ;

    SysCtlPeripheralReset(SYSCTL_PERIPH_USB0);
    for (volatile int i = 0; i < 1000; i++)
        ;

    GPIOPinTypeUSBAnalog(GPIO_PORTD_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    GPIOPinTypeUSBAnalog(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    HWREGB(USB0_BASE + USB_O_GPCS) = USB_GPCS_DEVMOD;
    SysCtlUSBPLLEnable();

    g_usb_irq_handler = USBD_IRQHandler;

    IntPrioritySet(INT_USB0, (6 << 5));
    IntEnable(INT_USB0);
}

void usb_dc_low_level_deinit(void)
{
    IntDisable(INT_USB0);
    g_usb_irq_handler = NULL;
    SysCtlPeripheralDisable(SYSCTL_PERIPH_USB0);
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_USB0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_USB0))
        ;
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
        ;
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
        ;

    SysCtlPeripheralReset(SYSCTL_PERIPH_USB0);
    for (volatile int i = 0; i < 1000; i++)
        ;

    GPIOPinTypeUSBAnalog(GPIO_PORTD_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    GPIOPinTypeUSBAnalog(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    HWREGB(USB0_BASE + USB_O_GPCS) &= ~(USB_GPCS_DEVMOD);
    SysCtlUSBPLLEnable();

    g_usb_irq_handler = USBH_IRQHandler;

    IntPrioritySet(INT_USB0, (6 << 5));
    IntEnable(INT_USB0);
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    IntDisable(INT_USB0);
    g_usb_irq_handler = NULL;
    SysCtlPeripheralDisable(SYSCTL_PERIPH_USB0);
}