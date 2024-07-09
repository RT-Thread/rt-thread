#ifdef __rtems__

#include <rtems.h>
#include <rtems/pci.h>
#include <bsp/irq.h>
#include "usbh_core.h"

uint32_t echi_base;
static int ehci_bus;
static int ehci_slot;
static int ehci_function;
static int ehci_vector;

extern void USBH_IRQHandler(uint8_t busid);

void ehci_pci_scan(int bus, int slot, int fun, int vector)
{
    ehci_bus = bus;
    ehci_slot = slot;
    ehci_function = fun;
    ehci_vector = vector;
    pci_read_config_dword(bus, slot, fun, PCI_BASE_ADDRESS_0, &echi_base);
}
void usb_hc_low_level_init(struct usbh_bus *bus)
{
    //set software own ehci
    uint32_t legacy_val;
    pci_write_config_dword(ehci_bus, ehci_slot, ehci_function, 0x68, 1 << 24);
    pci_read_config_dword(ehci_bus, ehci_slot, ehci_function, 0x68, &legacy_val);
    if ((legacy_val & 0x01010000) == 0x01000000)
        printf("OS owned echi\n");
    else
        printf("BIOS owned echi\n");

    rtems_status_code sc;
    sc = rtems_interrupt_handler_install(
        ehci_vector,
        "USBirq",
        RTEMS_INTERRUPT_SHARED,
        USBH_IRQHandler,
        (void *)0);

    if (sc != RTEMS_SUCCESSFUL) {
        printf("USB install isr falied,%s\n", rtems_status_text(sc));
        return;
    }
}

uint8_t usbh_get_port_speed(struct usbh_bus *bus, const uint8_t port)
{
    printf("USB_SPEED_HIGH present\n");
    return USB_SPEED_HIGH;
}

#endif