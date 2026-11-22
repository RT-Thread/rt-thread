#!/usr/bin/env python3
"""Generate Avaota F2 board.dtb (UART0 + MMC0 from SyterKit board.dts)."""

from pathlib import Path

import fdt

OUT = Path(__file__).with_name("board.dtb")

SUNXI_GPIO_BASE = 0x02000000
SUNXI_CCU_BASE = 0x02001000
SUNXI_UART0_BASE = 0x02500000
SUNXI_SMHC0_BASE = 0x04020000
SUNXI_GPIO_PORT_F = 5
SUNXI_GPIO_PORT_H = 7

tree = fdt.FDT()
tree.add_item(fdt.PropWords("#address-cells", 1))
tree.add_item(fdt.PropWords("#size-cells", 1))
tree.add_item(fdt.PropStrings("compatible", "syterkit,avaota-f2"))
tree.add_item(fdt.PropStrings("model", "Avaota F2"))

tree.add_item(fdt.Node("chosen"), create=True)
tree.add_item(fdt.PropStrings("stdout-path", "/soc/serial@2500000"), path="chosen")

# reserved-memory / mmc0_dma (phandle not wired; reg kept for DT print)
tree.add_item(fdt.Node("reserved-memory"), create=True)
tree.add_item(fdt.PropWords("#address-cells", 1), path="reserved-memory")
tree.add_item(fdt.PropWords("#size-cells", 1), path="reserved-memory")
dma_path = "reserved-memory/dma-descriptors@43600000"
tree.add_item(fdt.Node("dma-descriptors@43600000"), path="reserved-memory", create=True)
tree.add_item(fdt.PropWords("reg", 0x43600000, 0x00100000), path=dma_path)

tree.add_item(fdt.Node("soc"), create=True)
tree.add_item(fdt.PropWords("#address-cells", 1), path="soc")
tree.add_item(fdt.PropWords("#size-cells", 1), path="soc")

uart_path = "soc/serial@2500000"
tree.add_item(fdt.Node("serial@2500000"), path="soc", create=True)
tree.add_item(fdt.PropStrings("compatible", "allwinner,sunxi-uart"), path=uart_path)
tree.add_item(fdt.PropWords("reg", SUNXI_UART0_BASE, 0x400), path=uart_path)
tree.add_item(fdt.PropWords("current-speed", 115200), path=uart_path)
tree.add_item(fdt.PropWords("clock-frequency", 24000000), path=uart_path)
tree.add_item(fdt.PropWords("allwinner,uart-id", 0), path=uart_path)
tree.add_item(fdt.PropWords("allwinner,clock-gate", SUNXI_CCU_BASE + 0x90C, 0), path=uart_path)
tree.add_item(fdt.PropWords("allwinner,reset", SUNXI_CCU_BASE + 0x90C, 16), path=uart_path)
tree.add_item(
    fdt.PropWords("allwinner,pins", SUNXI_GPIO_PORT_H, 9, 5, SUNXI_GPIO_PORT_H, 10, 5),
    path=uart_path,
)
tree.add_item(fdt.PropStrings("status", "okay"), path=uart_path)

mmc_path = "soc/mmc@4020000"
tree.add_item(fdt.Node("mmc@4020000"), path="soc", create=True)
tree.add_item(fdt.PropStrings("compatible", "allwinner,sunxi-mmc"), path=mmc_path)
tree.add_item(fdt.PropWords("reg", SUNXI_SMHC0_BASE, 0x1000), path=mmc_path)
tree.add_item(fdt.PropStrings("label", "sdhci0"), path=mmc_path)
tree.add_item(fdt.PropWords("allwinner,mmc-id", 0), path=mmc_path)
tree.add_item(fdt.PropWords("bus-width", 4), path=mmc_path)
tree.add_item(fdt.PropWords("max-frequency", 50000000), path=mmc_path)
tree.add_item(fdt.PropWords("allwinner,clock-gate", SUNXI_CCU_BASE + 0x84C, 0), path=mmc_path)
tree.add_item(fdt.PropWords("allwinner,reset", SUNXI_CCU_BASE + 0x84C, 16), path=mmc_path)
tree.add_item(
    fdt.PropWords("allwinner,module-clock", SUNXI_CCU_BASE + 0x830, 8, 0, 1),
    path=mmc_path,
)
tree.add_item(
    fdt.PropWords("allwinner,clock-source-rates", 24000000, 400000000, 300000000, 0),
    path=mmc_path,
)
# mmc0_pins: PF0-5 func 2
pins = []
for pin in (2, 3, 1, 0, 5, 4):
    pins.extend([SUNXI_GPIO_PORT_F, pin, 2])
tree.add_item(fdt.PropWords("allwinner,pins", *pins), path=mmc_path)
tree.add_item(fdt.PropWords("dma-region", 0x43600000, 0x00100000), path=mmc_path)
tree.add_item(fdt.PropStrings("status", "okay"), path=mmc_path)

pio_path = "soc/pinctrl@2000000"
tree.add_item(fdt.Node("pinctrl@2000000"), path="soc", create=True)
tree.add_item(fdt.PropStrings("compatible", "allwinner,sunxi-pinctrl"), path=pio_path)
tree.add_item(fdt.PropWords("reg", SUNXI_GPIO_BASE, 0x1000), path=pio_path)

data = tree.to_dtb(version=17)
OUT.write_bytes(data)
print(f"wrote {OUT} ({len(data)} bytes)")
