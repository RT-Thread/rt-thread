#include "hal_clk.h"
#include "hal_reset.h"
#include "usb_sun8iw19.h"

static const struct platform_usb_config usb_hci_table[] =
{
    {//enci-0
        .name       = "sunxi-ehci0",
        .pbase      = SUNXI_USB_EHCI0_PBASE,
        .irq        = 97,
        .usb_clk    = HAL_CLK_PERIPH_USBOHCI0,
        .usb_rst    = 0,
        .phy_clk    = HAL_CLK_PERIPH_USB0,
        .phy_rst    = 0
    }
};

static const struct platform_usb_config usb_otg_table =
{
    .name       = "sunxi-otg",
    .pbase      = SUNXI_USB_OTG_PBASE,
    .irq        = 96,
    .usb_clk    = HAL_CLK_PERIPH_USB0,
    .usb_rst    = HAL_CLK_PERIPH_USB0,
    .phy_clk    = HAL_CLK_PERIPH_USBOTG,
    .phy_rst    = HAL_CLK_PERIPH_USBOTG
};

struct platform_usb_config *platform_get_hci_table(void)
{
    return (struct platform_usb_config *)usb_hci_table;
}

struct platform_usb_config *platform_get_otg_table(void)
{
    return (struct platform_usb_config *)&usb_otg_table;
}
