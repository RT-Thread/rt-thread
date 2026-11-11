@page page_device_pic_examples PIC platform examples

# Rockchip & Raspberry Pi DM patterns

Concrete BSP references (paths under **`rt-thread/bsp/`**).

---

## Raspberry Pi 4 — GIC root (`dm/dts/bcm2711-rpi-4-b.dts`)

```dts
gicv2: interrupt-controller@40041000 {
    compatible = "arm,gic-400";
    interrupt-controller;
    #interrupt-cells = <3>;
    reg = <0x40041000 0x1000>, <0x40042000 0x2000>;
};
```

- Probed by in-tree **`pic-gicv2.c`** during **`rt_pic_init`**
- All devices: **`interrupt-parent = <&gicv2>`** + **`GIC_SPI n type`**
- Drivers: **`rt_dm_dev_get_irq`** → virtual IRQ → **`rt_pic_attach_irq`**

PCIe **`interrupt-map`** on host points at **`&gicv2 GIC_SPI 143…`**.

---

## Raspberry Pi — BCM2835 mailbox (`dm/mailbox/mailbox-bcm2835.c`)

```c
bcm_mbox->irq = rt_dm_dev_get_irq(dev, 0);
rt_hw_interrupt_install(bcm_mbox->irq, bcm2835_mbox_isr, …);
rt_hw_interrupt_umask(bcm_mbox->irq);
```

Single interrupt line from GIC — no cascade. Shows standard DM consumer pattern.

---

## Rockchip — RK8xx PMIC IRQ (`dm/mfd/rk8xx.c`)

| Piece | Detail |
| --- | --- |
| **Root** | PMIC **`rk8xx->irq`** from SoC GPIO |
| **Child PIC** | **`rk8xx_irqchip`**, **`rt_pic_linear_irq`** |
| **Cascade** | **`rt_pic_cascade(pirq, rk8xx->irq)`** in **`rk8xx_irq_map`** |
| **Demux** | Thread reads **`status_base`** regs → **`rt_pic_handle_isr`** |
| **DT** | **`interrupts = <&rk8xx_intc 0>`** on sub-devices |

Template for **GPIO/PMIC expander** IRQ chips.

---

## Rockchip — PCIe DW INTx (`dm/pci/pcie-dw-rockchip.c`)

| Piece | Detail |
| --- | --- |
| **Child node** | **`legacy-interrupt-controller`** (OFW child) |
| **Child PIC** | **`rockchip_intx_ops`**, 4 lines (**`RT_PCI_INTX_PIN_MAX`**) |
| **`rt_ofw_data(intx_np) = &intx_pic`** | PCI **`interrupt-map`** targets this |
| **Parent ISR** | **`rockchip_pcie_legacy_isr`** on **`legacy`** GIC IRQ |
| **No `RT_PIC_F_IRQ_ROUTING`** | Software poll of legacy status register |

PCI function drivers use **`rt_pci_ofw_irq_parse_and_map`** → maps through **`intx_pic`** → GIC.

---

## Rockchip DM consumers (simple)

Many drivers only use allocated virtual IRQ:

```c
i2c->irq = rt_dm_dev_get_irq(dev, 0);
rt_pic_attach_irq(i2c->irq, handler, i2c, name, flags);
rt_pic_irq_unmask(i2c->irq);
```

Examples: **`i2c-rk3x.c`**, **`spi-rockchip.c`**, **`mailbox-rockchip.c`**.

---

## Choosing a pattern

| Hardware | Pattern | Example |
| --- | --- | --- |
| Single GIC line per device | **`get_irq` + attach** | UART, I2C |
| Aggregated status register | Child PIC + parent ISR poll | RK PCIe INTx |
| Many lines behind one pin | Child PIC + **cascade** | RK8xx PMIC |
| Message-signalled | MSI PIC + PCI | See @ref page_device_pic_msi |

---

## See also

- @ref page_device_pic_cascade
- @ref page_device_pci_ofw
