/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "fsl_common.h"
#include "usb_kinetis_reg.h"

#define USB_OTG_DEV ((KINETIS_MCX_TypeDef *)g_usbdev_bus[busid].reg_base)

#if defined(MCXC444_H_)
#define USBD_IRQ USB0_IRQHandler
void USB_ClockInit(void)
{
    SystemCoreClockUpdate();
    CLOCK_EnableUsbfs0Clock(kCLOCK_UsbSrcIrc48M, 48000000U);
}
#elif defined(MCXA153_H_)
#define USBD_IRQ USB0_IRQHandler
void USB_ClockInit(void)
{
    RESET_PeripheralReset(kUSB0_RST_SHIFT_RSTn);
    CLOCK_EnableUsbfsClock();
}
#elif defined(MCXN947_CM33_CORE0_H_)
#define USBD_IRQ USB0_FS_IRQHandler
void USB_ClockInit(void)
{
    CLOCK_AttachClk(kCLK_48M_to_USB0);
    CLOCK_EnableClock(kCLOCK_Usb0Ram);
    CLOCK_EnableClock(kCLOCK_Usb0Fs);
    CLOCK_EnableUsbfsClock();
}
#else
#error "Unsupported MCU with Kinetis IP"
#endif

void USBD_IRQ(void)
{
    extern void USBD_IRQHandler(uint8_t busid);
    USBD_IRQHandler(0);
}

void usb_dc_low_level_init(uint8_t busid)
{
    USB_ClockInit();

    uint8_t irqNumber;

    uint8_t usbDeviceKhciIrq[] = USB_IRQS;
    irqNumber                  = usbDeviceKhciIrq[0];

    /* Install isr, set priority, and enable IRQ. */
    NVIC_SetPriority((IRQn_Type)irqNumber, 3);
    EnableIRQ((IRQn_Type)irqNumber);

    USB_OTG_DEV->USBTRC0 |= USB_USBTRC0_USBRESET_MASK;
    while (USB_OTG_DEV->USBTRC0 & USB_USBTRC0_USBRESET_MASK)
        ;

    USB_OTG_DEV->USBTRC0 |= USB_USBTRC0_VREGIN_STS(1); /* software must set this bit to 1 */
    USB_OTG_DEV->USBCTRL = 0;
    USB_OTG_DEV->CONTROL |= USB_CONTROL_DPPULLUPNONOTG_MASK;
}

void usb_dc_low_level_deinit(uint8_t busid)
{
    USB_OTG_DEV->CONTROL &= ~USB_CONTROL_DPPULLUPNONOTG_MASK;
    DisableIRQ((IRQn_Type)USB0_FS_IRQn);
}

void usbd_kinetis_delay_ms(uint8_t ms)
{
}