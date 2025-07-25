#include <stdio.h>
#include <string.h>

#include "mm32_device.h"
#include "hal_rcc.h"
#include "usbd_core.h"

void usb_dc_low_level_init(uint8_t busid)
{
    /* Select USBCLK source */
    //  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div1);
    RCC->CFGR &= ~(0x3 << 22);
    RCC->CFGR |= (0x1 << 22);

    /* Enable USB clock */
    RCC->AHB2ENR |= 0x1 << 7;

#define USB_DEVICE_INTERRUPT_PRIORITY (7U)
    NVIC_SetPriority((IRQn_Type)USB_OTGFS_IRQn, USB_DEVICE_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ(USB_OTGFS_IRQn);
}

void usb_dc_low_level_deinit(uint8_t busid)
{
    RCC->AHB2ENR &= ~(0x1 << 7);
}

void USB_OTGFS_IRQHandler(void)
{
    USBD_IRQHandler(0);
}

void usbd_kinetis_delay_ms(uint8_t ms)
{
    //delay_ms(ms);
}
