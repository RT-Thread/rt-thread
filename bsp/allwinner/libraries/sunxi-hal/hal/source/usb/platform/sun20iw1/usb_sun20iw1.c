#include "hal_clk.h"
#include "hal_reset.h"
#include "usb_sun20iw1.h"

#define USB_RISCV_GIC_OFFSET 16

static const struct platform_usb_config usb_hci_table[] =
{
    {//enci-0
        .name       = "sunxi-ehci0",
        .pbase      = SUNXI_USB_EHCI0_PBASE,
        .irq        = 62 - USB_RISCV_GIC_OFFSET,
        .usb_clk    = CLK_BUS_EHCI0,
        .usb_rst    = RST_BUS_EHCI0,
        .phy_clk    = 0,
        .phy_rst    = RST_USB_PHY0
    },

    {//enci-1
        .name       = "sunxi-ehci1",
        .pbase      = SUNXI_USB_EHCI1_PBASE,
        .irq        = 65 - USB_RISCV_GIC_OFFSET,
        .usb_clk    = CLK_BUS_EHCI1,
        .usb_rst    = RST_BUS_EHCI1,
        .phy_clk    = 0,
        .phy_rst    = RST_USB_PHY1
    }
};

static const struct platform_usb_config usb_otg_table =
{
    .name       = "sunxi-otg",
    .pbase      = SUNXI_USB_OTG_PBASE,
    .irq        = 61 - USB_RISCV_GIC_OFFSET,
    .usb_clk    = CLK_BUS_OTG,
    .usb_rst    = RST_BUS_OTG,
    .phy_clk    = 0,
    .phy_rst    = RST_USB_PHY0
};

struct platform_usb_config *platform_get_hci_table(void)
{
    return (struct platform_usb_config *)usb_hci_table;
}

struct platform_usb_config *platform_get_otg_table(void)
{
    return (struct platform_usb_config *)&usb_otg_table;
}
