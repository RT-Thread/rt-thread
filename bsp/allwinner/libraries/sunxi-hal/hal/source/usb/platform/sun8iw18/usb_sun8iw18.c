#include "hal_clk.h"
#include "hal_reset.h"
#include "usb_sun8iw18.h"

static const struct platform_usb_config *usb_hci_table = 0;

static const struct platform_usb_config usb_otg_table =
{
    .name       = "sunxi-otg",
    .pbase      = SUNXI_USB_OTG_PBASE,
    .irq        = 69,
    .usb_clk    = 0,
    .usb_rst    = 0,
    .phy_clk    = 0,
    .phy_rst    = 0
};

struct platform_usb_config *platform_get_hci_table(void)
{
    return (struct platform_usb_config *)usb_hci_table;
}

struct platform_usb_config *platform_get_otg_table(void)
{
    return (struct platform_usb_config *)&usb_otg_table;
}
