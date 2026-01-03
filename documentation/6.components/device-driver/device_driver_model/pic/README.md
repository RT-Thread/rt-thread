# Platform Interrupt Controller (PIC) Framework

## Introduction

The Platform Interrupt Controller (PIC) framework provides a unified abstraction layer for managing hardware interrupts in RT-Thread's Device Driver Model. It supports various interrupt controllers including ARM GIC (Generic Interrupt Controller) v1/v2/v3, and provides comprehensive interrupt management capabilities including cascading, MSI support, and inter-processor interrupts (IPI).

### Key Features

- **Unified Interrupt Management**: Abstract interface for all interrupt controllers
- **Interrupt Cascading**: Support for hierarchical interrupt routing
- **CPU Affinity**: Configure which CPUs can handle specific interrupts
- **Priority Control**: Set interrupt priorities for different IRQ sources
- **Trigger Modes**: Support edge/level triggered interrupts
- **IPI Support**: Inter-processor interrupt mechanisms for multi-core systems
- **MSI/MSI-X**: Message Signaled Interrupts for PCIe devices
- **Statistics**: Optional ISR execution time tracking

### Architecture

The PIC framework consists of:

1. **PIC Core** (`pic.c`): Central interrupt management and routing
2. **PIC IRQ** (`struct rt_pic_irq`): Individual interrupt descriptor
3. **PIC Operations** (`struct rt_pic_ops`): Hardware-specific callbacks
4. **ISR Management**: Interrupt Service Routine registration and execution

```
┌──────────────────────────────────────────┐
│         Application/Drivers              │
│  (Call rt_pic_attach_irq, enable, etc.) │
└──────────────────┬───────────────────────┘
                   │
┌──────────────────▼───────────────────────┐
│       PIC Framework (pic.c)              │
│  - IRQ allocation & management           │
│  - ISR dispatch                          │
│  - Cascading support                     │
│  - Affinity & priority management        │
└──────────────────┬───────────────────────┘
                   │
┌──────────────────▼───────────────────────┐
│     PIC Operations (rt_pic_ops)          │
│  - irq_enable/disable                    │
│  - irq_mask/unmask                       │
│  - irq_set_priority                      │
│  - irq_set_affinity                      │
│  - irq_send_ipi (for multi-core)         │
└──────────────────┬───────────────────────┘
                   │
┌──────────────────▼───────────────────────┐
│   Hardware Interrupt Controller          │
│   (GICv2, GICv3, etc.)                   │
└──────────────────────────────────────────┘
```

## Kconfig Configuration

### Location in menuconfig

```
RT-Thread Components
    └── Device Drivers
        └── Using Device Driver Model with DeviceTree (RT_USING_DM)
            └── Using Programmable Interrupt Controller (PIC) (RT_USING_PIC)
```

### Configuration Options

#### RT_USING_PIC
- **Type**: bool
- **Default**: n
- **Description**: Enable the Platform Interrupt Controller framework
- **Dependencies**: RT_USING_DM, RT_USING_ADT, RT_USING_ADT_BITMAP
- **Purpose**: Main switch for PIC support

#### RT_USING_PIC_STATISTICS
- **Type**: bool
- **Default**: n
- **Description**: Enable ISR execution time statistics
- **Dependencies**: RT_USING_PIC, RT_USING_KTIME, RT_USING_INTERRUPT_INFO
- **Purpose**: Track min/max/average IRQ handling times for profiling

#### MAX_HANDLERS
- **Type**: int
- **Range**: 1-4294967294
- **Default**: 256
- **Description**: Maximum number of interrupt handlers the system can register
- **Purpose**: Defines the size of the global IRQ hash table

#### RT_PIC_ARM_GIC
- **Type**: bool
- **Default**: n
- **Description**: Enable ARM Generic Interrupt Controller v1/v2 support
- **Dependencies**: RT_USING_PIC, RT_USING_OFW
- **Purpose**: Support for ARM GICv1/v2 hardware

#### RT_PIC_ARM_GIC_V2M
- **Type**: bool
- **Default**: n
- **Description**: Enable ARM GIC V2M (MSI support for GICv2)
- **Dependencies**: RT_PIC_ARM_GIC, RT_PCI_MSI, RT_USING_OFW
- **Purpose**: Message Signaled Interrupts on GICv2

#### RT_PIC_ARM_GIC_V3
- **Type**: bool
- **Default**: n
- **Description**: Enable ARM Generic Interrupt Controller v3 support
- **Dependencies**: RT_USING_PIC, RT_USING_OFW
- **Purpose**: Support for ARM GICv3 hardware

#### RT_PIC_ARM_GIC_V3_ITS
- **Type**: bool
- **Default**: n
- **Description**: Enable ARM GICv3 ITS (Interrupt Translation Service)
- **Dependencies**: RT_PIC_ARM_GIC_V3, RT_PCI_MSI, RT_USING_OFW, RT_USING_ADT_REF
- **Purpose**: MSI/MSI-X support for GICv3 via ITS

#### RT_PIC_ARM_GIC_V3_ITS_IRQ_MAX
- **Type**: int
- **Default**: 127 (64-bit), 63 (32-bit)
- **Description**: Maximum IRQ number for GICv3 ITS
- **Dependencies**: RT_PIC_ARM_GIC_V3_ITS
- **Purpose**: Limit ITS-managed interrupt range

## Device Tree Bindings

### GICv2 Example

```dts
gic: interrupt-controller@08000000 {
    compatible = "arm,cortex-a15-gic", "arm,cortex-a9-gic";
    #interrupt-cells = <3>;
    #address-cells = <1>;
    interrupt-controller;
    reg = <0x08000000 0x1000>,  /* Distributor */
          <0x08010000 0x1000>;  /* CPU interface */
};

/* Consumer example: UART using GIC */
uart0: serial@09000000 {
    compatible = "arm,pl011", "arm,primecell";
    reg = <0x09000000 0x1000>;
    interrupts = <0 5 4>;  /* SPI, IRQ 5, IRQ_TYPE_LEVEL_HIGH */
    interrupt-parent = <&gic>;
};
```

### GICv3 Example

```dts
gic: interrupt-controller@08000000 {
    compatible = "arm,gic-v3";
    #interrupt-cells = <3>;
    #address-cells = <2>;
    #size-cells = <2>;
    interrupt-controller;
    reg = <0x0 0x08000000 0 0x10000>,  /* Distributor */
          <0x0 0x080A0000 0 0xF60000>; /* Redistributor */
    
    gic_its: msi-controller@08020000 {
        compatible = "arm,gic-v3-its";
        msi-controller;
        #msi-cells = <1>;
        reg = <0x0 0x08020000 0 0x20000>;
    };
};

/* Consumer with interrupts */
timer {
    compatible = "arm,armv8-timer";
    interrupts = <1 13 0xff08>,  /* Physical Secure PPI */
                 <1 14 0xff08>,  /* Physical Non-Secure PPI */
                 <1 11 0xff08>,  /* Virtual PPI */
                 <1 10 0xff08>;  /* Hypervisor PPI */
    interrupt-parent = <&gic>;
};
```

### Interrupt Cells Explanation

For ARM GIC, `interrupts` property has 3 cells:
1. **Type**: 0 = SPI (Shared Peripheral Interrupt), 1 = PPI (Private Peripheral Interrupt)
2. **Number**: IRQ number within the type (SPI: 0-987, PPI: 0-15)
3. **Flags**: Trigger type and priority
   - `IRQ_TYPE_EDGE_RISING` = 1
   - `IRQ_TYPE_EDGE_FALLING` = 2
   - `IRQ_TYPE_LEVEL_HIGH` = 4
   - `IRQ_TYPE_LEVEL_LOW` = 8

## Application API

### IRQ Attachment

#### rt_pic_attach_irq

```c
rt_err_t rt_pic_attach_irq(int irq, rt_isr_handler_t handler, void *uid, 
                            const char *name, int flags);
```

Attach an interrupt service routine to an IRQ.

**Parameters:**
- `irq`: IRQ number to attach to
- `handler`: ISR function pointer `void (*handler)(int irq, void *param)`
- `uid`: User-defined parameter passed to the handler
- `name`: Descriptive name for the interrupt (for debugging)
- `flags`: Interrupt flags (currently unused, pass 0)

**Returns:**
- `RT_EOK`: Success
- `-RT_EINVAL`: Invalid IRQ number
- `-RT_ENOMEM`: Out of memory

**Example:**
```c
void uart_isr(int irq, void *param)
{
    struct uart_device *uart = (struct uart_device *)param;
    /* Handle interrupt */
    rt_kprintf("UART interrupt occurred\n");
}

/* In driver probe function */
static rt_err_t uart_probe(struct rt_platform_device *pdev)
{
    struct uart_device *uart;
    int irq;
    
    /* Get IRQ from device tree */
    irq = rt_platform_get_irq(pdev, 0);
    if (irq < 0)
        return irq;
    
    /* Attach ISR */
    rt_err_t ret = rt_pic_attach_irq(irq, uart_isr, uart, "uart0", 0);
    if (ret != RT_EOK)
        return ret;
    
    /* Enable the interrupt */
    rt_pic_irq_enable(irq);
    
    return RT_EOK;
}
```

#### rt_pic_detach_irq

```c
rt_err_t rt_pic_detach_irq(int irq, void *uid);
```

Detach an interrupt service routine from an IRQ.

**Parameters:**
- `irq`: IRQ number
- `uid`: Must match the `uid` passed to `rt_pic_attach_irq`

**Returns:**
- `RT_EOK`: Success
- `-RT_EINVAL`: Invalid IRQ or UID mismatch

### IRQ Control

#### rt_pic_irq_enable / rt_pic_irq_disable

```c
void rt_pic_irq_enable(int irq);
void rt_pic_irq_disable(int irq);
```

Enable or disable an interrupt at the PIC level.

**Parameters:**
- `irq`: IRQ number

**Example:**
```c
/* Enable interrupt before starting operation */
rt_pic_irq_enable(uart_irq);

/* Disable during critical sections */
rt_pic_irq_disable(uart_irq);
/* ... critical code ... */
rt_pic_irq_enable(uart_irq);
```

#### rt_pic_irq_mask / rt_pic_irq_unmask

```c
void rt_pic_irq_mask(int irq);
void rt_pic_irq_unmask(int irq);
```

Mask or unmask an interrupt (similar to enable/disable but may have different semantics on some hardware).

**Parameters:**
- `irq`: IRQ number

#### rt_pic_irq_ack

```c
void rt_pic_irq_ack(int irq);
```

Acknowledge an interrupt (required for some edge-triggered interrupts).

**Parameters:**
- `irq`: IRQ number

#### rt_pic_irq_eoi

```c
void rt_pic_irq_eoi(int irq);
```

Signal End-Of-Interrupt to the PIC.

**Parameters:**
- `irq`: IRQ number

### Priority Management

#### rt_pic_irq_set_priority

```c
rt_err_t rt_pic_irq_set_priority(int irq, rt_uint32_t priority);
```

Set the priority of an interrupt.

**Parameters:**
- `irq`: IRQ number
- `priority`: Priority value (lower = higher priority typically)

**Returns:**
- `RT_EOK`: Success
- `-RT_ENOSYS`: Not supported by hardware

**Example:**
```c
/* Set high priority for critical timer interrupt */
rt_pic_irq_set_priority(timer_irq, 0);

/* Set lower priority for UART */
rt_pic_irq_set_priority(uart_irq, 128);
```

#### rt_pic_irq_get_priority

```c
rt_uint32_t rt_pic_irq_get_priority(int irq);
```

Get the current priority of an interrupt.

**Parameters:**
- `irq`: IRQ number

**Returns:** Current priority value

### CPU Affinity (Multi-core)

#### rt_pic_irq_set_affinity

```c
rt_err_t rt_pic_irq_set_affinity(int irq, rt_bitmap_t *affinity);
```

Set which CPUs can handle a specific interrupt.

**Parameters:**
- `irq`: IRQ number
- `affinity`: Bitmap of allowed CPUs

**Returns:**
- `RT_EOK`: Success
- `-RT_ENOSYS`: Not supported

**Example:**
```c
RT_IRQ_AFFINITY_DECLARE(cpumask);

/* Route interrupt to CPU 0 and CPU 2 */
rt_bitmap_clear(cpumask, RT_BITMAP_LEN(RT_CPUS_NR));
RT_IRQ_AFFINITY_SET(cpumask, 0);
RT_IRQ_AFFINITY_SET(cpumask, 2);
rt_pic_irq_set_affinity(eth_irq, cpumask);
```

#### rt_pic_irq_get_affinity

```c
rt_err_t rt_pic_irq_get_affinity(int irq, rt_bitmap_t *out_affinity);
```

Get the current CPU affinity for an interrupt.

**Parameters:**
- `irq`: IRQ number
- `out_affinity`: Output bitmap

**Returns:**
- `RT_EOK`: Success
- `-RT_EINVAL`: Invalid IRQ

### Trigger Mode

#### rt_pic_irq_set_triger_mode

```c
rt_err_t rt_pic_irq_set_triger_mode(int irq, rt_uint32_t mode);
```

Set the trigger mode for an interrupt.

**Parameters:**
- `irq`: IRQ number
- `mode`: Trigger mode
  - `RT_IRQ_MODE_EDGE_RISING`: Rising edge
  - `RT_IRQ_MODE_EDGE_FALLING`: Falling edge
  - `RT_IRQ_MODE_EDGE_BOTH`: Both edges
  - `RT_IRQ_MODE_LEVEL_HIGH`: High level
  - `RT_IRQ_MODE_LEVEL_LOW`: Low level

**Returns:**
- `RT_EOK`: Success
- `-RT_ENOSYS`: Not supported

#### rt_pic_irq_get_triger_mode

```c
rt_uint32_t rt_pic_irq_get_triger_mode(int irq);
```

Get the current trigger mode.

**Parameters:**
- `irq`: IRQ number

**Returns:** Current trigger mode

### Inter-Processor Interrupts (IPI)

#### rt_pic_irq_send_ipi

```c
void rt_pic_irq_send_ipi(int irq, rt_bitmap_t *cpumask);
```

Send an inter-processor interrupt to specified CPUs.

**Parameters:**
- `irq`: IPI number (typically in range 0-15)
- `cpumask`: Bitmap of target CPUs

**Example:**
```c
RT_IRQ_AFFINITY_DECLARE(targets);

/* Send IPI to CPU 1 */
rt_bitmap_clear(targets, RT_BITMAP_LEN(RT_CPUS_NR));
RT_IRQ_AFFINITY_SET(targets, 1);
rt_pic_irq_send_ipi(0, targets);  /* IPI 0 */
```

### State Management

#### rt_pic_irq_set_state / rt_pic_irq_get_state

```c
rt_err_t rt_pic_irq_set_state(int irq, int type, rt_bool_t state);
rt_err_t rt_pic_irq_get_state(int irq, int type, rt_bool_t *out_state);
```

Set or get interrupt state (pending, active, masked).

**Parameters:**
- `irq`: IRQ number
- `type`: State type
  - `RT_IRQ_STATE_PENDING`: Interrupt is pending
  - `RT_IRQ_STATE_ACTIVE`: Interrupt is being serviced
  - `RT_IRQ_STATE_MASKED`: Interrupt is masked
- `state` / `out_state`: State value

**Returns:**
- `RT_EOK`: Success
- `-RT_ENOSYS`: Not supported

## Complete Driver Example: GPIO Interrupt Handler

```c
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/pic.h>
#include <drivers/platform.h>

struct gpio_int_device
{
    struct rt_device parent;
    void *base;
    int irq;
    rt_uint32_t pin_mask;
};

/* GPIO interrupt service routine */
static void gpio_isr(int irq, void *param)
{
    struct gpio_int_device *gpio = (struct gpio_int_device *)param;
    rt_uint32_t status;
    
    /* Read interrupt status register */
    status = readl(gpio->base + GPIO_INT_STATUS);
    
    /* Clear interrupt */
    writel(status, gpio->base + GPIO_INT_CLEAR);
    
    /* Handle each pin */
    for (int i = 0; i < 32; i++)
    {
        if (status & (1 << i))
        {
            rt_kprintf("GPIO pin %d triggered\n", i);
            /* Notify application or trigger event */
        }
    }
    
    /* Send EOI to PIC */
    rt_pic_irq_eoi(irq);
}

static rt_err_t gpio_int_probe(struct rt_platform_device *pdev)
{
    struct gpio_int_device *gpio;
    struct rt_device *dev = &pdev->parent;
    int irq;
    rt_err_t ret;
    
    gpio = rt_calloc(1, sizeof(*gpio));
    if (!gpio)
        return -RT_ENOMEM;
    
    /* Map registers */
    gpio->base = rt_dm_dev_iomap(dev, 0);
    if (!gpio->base)
    {
        ret = -RT_ERROR;
        goto err_free;
    }
    
    /* Get IRQ from device tree */
    irq = rt_platform_get_irq(pdev, 0);
    if (irq < 0)
    {
        ret = irq;
        goto err_iounmap;
    }
    gpio->irq = irq;
    
    /* Set interrupt trigger mode - rising edge */
    ret = rt_pic_irq_set_triger_mode(irq, RT_IRQ_MODE_EDGE_RISING);
    if (ret != RT_EOK && ret != -RT_ENOSYS)
    {
        rt_kprintf("Failed to set trigger mode: %d\n", ret);
        goto err_iounmap;
    }
    
    /* Set interrupt priority (high priority) */
    ret = rt_pic_irq_set_priority(irq, 32);
    if (ret != RT_EOK && ret != -RT_ENOSYS)
    {
        rt_kprintf("Failed to set priority: %d\n", ret);
    }
    
    /* Attach interrupt handler */
    ret = rt_pic_attach_irq(irq, gpio_isr, gpio, "gpio-int", 0);
    if (ret != RT_EOK)
    {
        rt_kprintf("Failed to attach IRQ: %d\n", ret);
        goto err_iounmap;
    }
    
    /* Configure GPIO pins for interrupt */
    writel(0xFFFFFFFF, gpio->base + GPIO_INT_ENABLE);  /* Enable all pins */
    writel(0x00000000, gpio->base + GPIO_INT_MASK);    /* Unmask all */
    
    /* Enable interrupt at PIC level */
    rt_pic_irq_enable(irq);
    
    /* Store device data */
    rt_platform_set_drvdata(pdev, gpio);
    
    rt_kprintf("GPIO interrupt controller probed successfully (IRQ %d)\n", irq);
    return RT_EOK;
    
err_iounmap:
    rt_dm_dev_iounmap(dev, gpio->base);
err_free:
    rt_free(gpio);
    return ret;
}

static rt_err_t gpio_int_remove(struct rt_platform_device *pdev)
{
    struct gpio_int_device *gpio = rt_platform_get_drvdata(pdev);
    
    /* Disable interrupt */
    rt_pic_irq_disable(gpio->irq);
    
    /* Detach handler */
    rt_pic_detach_irq(gpio->irq, gpio);
    
    /* Disable GPIO interrupts */
    writel(0x00000000, gpio->base + GPIO_INT_ENABLE);
    
    /* Cleanup */
    rt_dm_dev_iounmap(&pdev->parent, gpio->base);
    rt_free(gpio);
    
    return RT_EOK;
}

static const struct rt_ofw_node_id gpio_int_ofw_ids[] =
{
    { .compatible = "myvendor,gpio-interrupt-controller" },
    { /* sentinel */ }
};

static struct rt_platform_driver gpio_int_driver =
{
    .name = "gpio-int",
    .ids = gpio_int_ofw_ids,
    .probe = gpio_int_probe,
    .remove = gpio_int_remove,
};

static int gpio_int_drv_register(void)
{
    rt_platform_driver_register(&gpio_int_driver);
    return 0;
}
INIT_DEVICE_EXPORT(gpio_int_drv_register);
```

## PIC Provider Implementation

For implementing a custom interrupt controller driver:

```c
#include <rtthread.h>
#include <drivers/pic.h>

struct my_pic_data
{
    void *base;
    struct rt_pic pic;
};

static void my_pic_irq_enable(struct rt_pic_irq *pirq)
{
    struct rt_pic *pic = pirq->pic;
    struct my_pic_data *priv = pic->priv_data;
    
    /* Enable interrupt in hardware */
    writel(1 << pirq->hwirq, priv->base + MY_PIC_ENABLE_REG);
}

static void my_pic_irq_disable(struct rt_pic_irq *pirq)
{
    struct rt_pic *pic = pirq->pic;
    struct my_pic_data *priv = pic->priv_data;
    
    /* Disable interrupt in hardware */
    writel(1 << pirq->hwirq, priv->base + MY_PIC_DISABLE_REG);
}

static void my_pic_irq_ack(struct rt_pic_irq *pirq)
{
    struct rt_pic *pic = pirq->pic;
    struct my_pic_data *priv = pic->priv_data;
    
    /* Acknowledge interrupt */
    writel(1 << pirq->hwirq, priv->base + MY_PIC_ACK_REG);
}

static void my_pic_irq_eoi(struct rt_pic_irq *pirq)
{
    struct rt_pic *pic = pirq->pic;
    struct my_pic_data *priv = pic->priv_data;
    
    /* Send EOI signal */
    writel(1 << pirq->hwirq, priv->base + MY_PIC_EOI_REG);
}

static rt_err_t my_pic_irq_set_priority(struct rt_pic_irq *pirq, rt_uint32_t priority)
{
    struct rt_pic *pic = pirq->pic;
    struct my_pic_data *priv = pic->priv_data;
    
    /* Set priority in hardware register */
    writel(priority, priv->base + MY_PIC_PRIORITY_REG(pirq->hwirq));
    
    return RT_EOK;
}

static int my_pic_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    int irq;
    
    /* Allocate software IRQ number */
    irq = pic->irq_start + hwirq;
    
    /* Configure trigger mode in hardware */
    /* ... */
    
    return irq;
}

static rt_err_t my_pic_irq_parse(struct rt_pic *pic, struct rt_ofw_cell_args *args,
                                  struct rt_pic_irq *out_pirq)
{
    if (args->args_count != 2)
        return -RT_EINVAL;
    
    /* Parse: <hwirq trigger_type> */
    out_pirq->hwirq = args->args[0];
    out_pirq->mode = args->args[1];
    
    return RT_EOK;
}

static const struct rt_pic_ops my_pic_ops =
{
    .name = "my-pic",
    .irq_enable = my_pic_irq_enable,
    .irq_disable = my_pic_irq_disable,
    .irq_ack = my_pic_irq_ack,
    .irq_eoi = my_pic_irq_eoi,
    .irq_set_priority = my_pic_irq_set_priority,
    .irq_map = my_pic_irq_map,
    .irq_parse = my_pic_irq_parse,
};

static rt_err_t my_pic_probe(struct rt_platform_device *pdev)
{
    struct my_pic_data *priv;
    rt_err_t ret;
    
    priv = rt_calloc(1, sizeof(*priv));
    if (!priv)
        return -RT_ENOMEM;
    
    /* Map registers */
    priv->base = rt_dm_dev_iomap(&pdev->parent, 0);
    if (!priv->base)
    {
        ret = -RT_ERROR;
        goto err_free;
    }
    
    /* Initialize PIC structure */
    priv->pic.ops = &my_pic_ops;
    priv->pic.priv_data = priv;
    
    /* Allocate IRQ range (32 interrupts) */
    ret = rt_pic_linear_irq(&priv->pic, 32);
    if (ret != RT_EOK)
    {
        rt_kprintf("Failed to allocate IRQs\n");
        goto err_iounmap;
    }
    
    /* Configure each IRQ */
    for (int i = 0; i < 32; i++)
    {
        rt_pic_config_irq(&priv->pic, i, i);  /* Map 1:1 */
    }
    
    /* Call user extensions if needed */
    rt_pic_user_extends(&priv->pic);
    
    /* Initialize hardware */
    writel(0xFFFFFFFF, priv->base + MY_PIC_DISABLE_REG);  /* Disable all */
    writel(0xFFFFFFFF, priv->base + MY_PIC_CLEAR_REG);    /* Clear pending */
    
    rt_platform_set_drvdata(pdev, priv);
    rt_kprintf("My PIC initialized with %d IRQs\n", 32);
    
    return RT_EOK;
    
err_iounmap:
    rt_dm_dev_iounmap(&pdev->parent, priv->base);
err_free:
    rt_free(priv);
    return ret;
}

static const struct rt_ofw_node_id my_pic_ofw_ids[] =
{
    { .compatible = "myvendor,my-pic" },
    { /* sentinel */ }
};

static struct rt_platform_driver my_pic_driver =
{
    .name = "my-pic",
    .ids = my_pic_ofw_ids,
    .probe = my_pic_probe,
};

RT_PIC_OFW_DECLARE(my_pic, my_pic_ofw_ids, my_pic_probe);
```

## Best Practices

### For Interrupt Consumers

1. **Always disable interrupts during cleanup**:
   ```c
   rt_pic_irq_disable(irq);
   rt_pic_detach_irq(irq, uid);
   ```

2. **Handle spurious interrupts**:
   ```c
   static void my_isr(int irq, void *param)
   {
       if (!check_interrupt_source())
           return;  /* Spurious interrupt */
       
       /* Handle interrupt */
   }
   ```

3. **Use EOI for level-triggered interrupts**:
   ```c
   static void my_isr(int irq, void *param)
   {
       handle_interrupt();
       clear_interrupt_source();  /* Clear in device first */
       rt_pic_irq_eoi(irq);       /* Then send EOI to PIC */
   }
   ```

4. **Set appropriate priorities**:
   - Critical real-time interrupts: 0-31 (highest)
   - Normal device interrupts: 32-127
   - Low-priority interrupts: 128-255

5. **Consider CPU affinity on multi-core systems**:
   ```c
   /* Pin network interrupt to CPU 0 for better cache locality */
   RT_IRQ_AFFINITY_DECLARE(mask);
   rt_bitmap_clear(mask, RT_BITMAP_LEN(RT_CPUS_NR));
   RT_IRQ_AFFINITY_SET(mask, 0);
   rt_pic_irq_set_affinity(net_irq, mask);
   ```

### For PIC Providers

1. **Implement minimum required operations**:
   - `irq_enable`, `irq_disable`
   - `irq_ack` or `irq_eoi`
   - `irq_map`, `irq_parse`

2. **Use `rt_pic_linear_irq` for simple IRQ allocation**:
   ```c
   ret = rt_pic_linear_irq(pic, num_irqs);
   ```

3. **Support cascading for hierarchical interrupt controllers**:
   ```c
   struct rt_pic_irq *parent_pirq = rt_pic_find_pirq(parent_pic, parent_irq);
   rt_pic_cascade(child_pirq, parent_irq);
   ```

4. **Implement statistics support** (optional):
   ```c
   #ifdef RT_USING_PIC_STATISTICS
   /* Framework tracks this automatically */
   #endif
   ```

## Troubleshooting

### Interrupt Not Firing

1. **Check interrupt is enabled**:
   ```c
   rt_pic_irq_enable(irq);
   ```

2. **Verify device interrupt is not masked**:
   - Check device-specific interrupt enable registers
   - Ensure interrupt source is configured correctly

3. **Confirm device tree configuration**:
   - Verify `interrupts` property
   - Check `interrupt-parent` is correct

4. **Check trigger mode**:
   - Edge vs. level triggered
   - Active high vs. active low

### Interrupt Storms

1. **Always acknowledge/clear interrupts**:
   ```c
   /* Clear source BEFORE EOI */
   clear_device_interrupt();
   rt_pic_irq_eoi(irq);
   ```

2. **For level-triggered, clear condition**:
   - Level-triggered interrupts re-assert if condition persists
   - Must clear the underlying condition in the device

### ISR Not Called

1. **Verify IRQ number**:
   ```c
   rt_kprintf("Attached to IRQ %d\n", irq);
   ```

2. **Check MAX_HANDLERS**:
   - Ensure IRQ < MAX_HANDLERS

3. **Confirm attachment succeeded**:
   ```c
   ret = rt_pic_attach_irq(irq, isr, param, "name", 0);
   if (ret != RT_EOK)
       rt_kprintf("Attach failed: %d\n", ret);
   ```

### Priority/Affinity Not Working

- Some PICs don't support priority or affinity
- Check return value for `-RT_ENOSYS`
- Verify hardware capabilities

## Performance Considerations

1. **Keep ISRs short**: Defer heavy processing to threads
2. **Minimize register access**: Cache PIC state when possible
3. **Use shared interrupts carefully**: Check device status first
4. **Consider IRQ coalescing**: For high-rate interrupt sources
5. **Profile with statistics**:
   ```c
   /* Enable RT_USING_PIC_STATISTICS */
   /* Check /proc or debug output for timing data */
   ```

## Related Modules

- **OFW (Device Tree)**: IRQ parsing and `interrupt-parent` resolution
- **Platform Device**: `rt_platform_get_irq` for IRQ retrieval
- **PCI**: MSI/MSI-X interrupt support via PIC
- **Pinctrl**: GPIO interrupt configuration

## References

- ARM GIC Architecture Specification
- Device Tree Interrupt Mapping Specification
- RT-Thread Interrupt Management Documentation
- `components/drivers/pic/pic.c` - Core implementation
- `components/drivers/include/drivers/pic.h` - API header
