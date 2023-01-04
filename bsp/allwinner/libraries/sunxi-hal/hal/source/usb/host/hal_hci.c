#include "ehci.h"
#include  <usb_core_init.h>
#include <platform_usb.h>

int hal_usb_core_init(void)
{
    return usb_core_init();
}

int hal_usb_core_exit(void)
{
    return usb_core_exit();
}

int hal_usb_hcd_init(int hci_num)
{
    return sunxi_ehci_hcd_init(hci_num);
}

void hal_usb_hci_init(void)
{
    /*except for usb0ï¼Œ other usb hci should be init in OS.
     *usb0 hci depends on otg.
     */
    for (int hci_num = 1; hci_num < USB_MAX_CONTROLLER_COUNT; hci_num++)
    {
        sunxi_ehci_hcd_init(hci_num);
    }
}

int hal_usb_hcd_deinit(int hci_num)
{
    return sunxi_ehci_hcd_deinit(hci_num);
}
