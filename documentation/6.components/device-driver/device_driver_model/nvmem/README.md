# NVMEM (Non-Volatile Memory) Framework

## Overview

### What is NVMEM?

Non-Volatile Memory (NVMEM) refers to computer memory that can retain stored information even when power is removed. Common examples include:

- **EEPROM** (Electrically Erasable Programmable Read-Only Memory)
- **OTP** (One-Time Programmable memory)
- **eFuse** (Electronic fuse)
- **Battery-backed SRAM**
- **Flash memory regions** (for configuration storage)

NVMEM devices are commonly used to store:
- Device configuration and calibration data
- MAC addresses and serial numbers
- Hardware identifiers and unique IDs
- Manufacturing test data
- Secure key storage

### NVMEM Framework in RT-Thread

RT-Thread's NVMEM framework provides a unified abstraction layer for accessing various types of non-volatile memory devices. The framework supports:

- **Unified Access Interface**: Common APIs for reading/writing NVMEM regardless of underlying hardware
- **Cell-Based Organization**: NVMEM data organized into named cells (regions)
- **Device Tree Integration**: Hardware description through device tree
- **Write Protection**: Hardware write-protect pin support
- **Bit-Level Access**: Support for bit-addressable memory regions
- **Reference Counting**: Automatic resource management

The framework is located in:
- Header: `components/drivers/include/drivers/nvmem.h`
- Implementation: `components/drivers/nvmem/nvmem.c`

## Kconfig Configuration

### Enable NVMEM Framework

```
RT-Thread Components
    → Device Drivers
        → Using Device Driver Model (RT_USING_DM)
            → Using Open Firmware (OF) API (RT_USING_OFW)
                → Using Non Volatile Memory (NVMEM) device drivers (RT_USING_NVMEM)
```

### Configuration Options

#### RT_USING_NVMEM

```kconfig
menuconfig RT_USING_NVMEM
    bool "Using Non Volatile Memory (NVMEM) device drivers"
    depends on RT_USING_DM
    depends on RT_USING_OFW
    depends on RT_USING_PIN
    select RT_USING_ADT
    select RT_USING_ADT_REF
    default n
```

**Dependencies**:
- `RT_USING_DM`: Device Driver Model must be enabled
- `RT_USING_OFW`: Open Firmware (Device Tree) support required
- `RT_USING_PIN`: PIN driver framework for write-protect pins

**Description**: Enables the NVMEM framework providing unified access to non-volatile memory devices like EEPROM, OTP, eFuse, etc.

#### SOC-Specific NVMEM Drivers

```kconfig
if RT_USING_NVMEM
    osource "$(SOC_DM_NVMEM_DIR)/Kconfig"
endif
```

SoC vendors can provide their specific NVMEM driver configurations through the `SOC_DM_NVMEM_DIR` directory.

## Device Tree Bindings

### NVMEM Provider Node

```dts
eeprom: eeprom@50 {
    compatible = "atmel,24c256";
    reg = <0x50>;
    
    #address-cells = <1>;
    #size-cells = <1>;
    
    /* Optional properties */
    read-only;                  /* Memory is read-only */
    wp-gpios = <&gpio 10 GPIO_ACTIVE_HIGH>;  /* Write protect pin */
    
    /* Define memory cells */
    mac_address: mac@0 {
        reg = <0x00 6>;        /* Offset 0x00, 6 bytes */
    };
    
    serial_number: serial@10 {
        reg = <0x10 16>;       /* Offset 0x10, 16 bytes */
    };
    
    calibration: calib@100 {
        reg = <0x100 32>;      /* Offset 0x100, 32 bytes */
        bits = <4 12>;         /* Bit offset 4, 12 bits wide */
    };
};
```

### NVMEM Consumer Node

```dts
ethernet@40000000 {
    compatible = "vendor,ethernet";
    reg = <0x40000000 0x10000>;
    
    /* Reference NVMEM cells */
    nvmem-cells = <&mac_address>;
    nvmem-cell-names = "mac-address";
};

device@50000000 {
    compatible = "vendor,device";
    reg = <0x50000000 0x1000>;
    
    /* Multiple NVMEM references */
    nvmem-cells = <&serial_number>, <&calibration>;
    nvmem-cell-names = "serial", "calibration-data";
};
```

### Device Tree Properties

#### NVMEM Provider Properties

| Property | Type | Description |
|----------|------|-------------|
| `#address-cells` | u32 | Number of cells for cell address (usually 1) |
| `#size-cells` | u32 | Number of cells for cell size (usually 1) |
| `read-only` | bool | Memory is read-only, writes not allowed |
| `wp-gpios` | phandle | GPIO for hardware write protection |

#### NVMEM Cell Properties

| Property | Type | Description |
|----------|------|-------------|
| `reg` | u32 array | `<offset size>` - Memory region for this cell |
| `bits` | u32 array | `<bit_offset nbits>` - Bit-level addressing |

#### NVMEM Consumer Properties

| Property | Type | Description |
|----------|------|-------------|
| `nvmem-cells` | phandle | Reference to NVMEM cells |
| `nvmem-cell-names` | string array | Names for referenced cells |

## Application Layer API

### Data Structures

#### struct rt_nvmem_device

```c
struct rt_nvmem_device {
    struct rt_device parent;            /* Parent device */
    
    int cells_nr;                       /* Number of cells */
    rt_list_t cell_nodes;              /* List of cells */
    
    /* Read/Write callbacks */
    rt_ssize_t (*reg_read)(struct rt_nvmem_device *, int offset, 
                           void *val, rt_size_t bytes);
    rt_ssize_t (*reg_write)(struct rt_nvmem_device *, int offset, 
                            void *val, rt_size_t bytes);
    
    rt_ssize_t size;                   /* Total size in bytes */
    int word_size;                     /* Word size (1, 2, 4 bytes) */
    int stride;                        /* Minimum access stride */
    
    rt_bool_t read_only;               /* Read-only flag */
    rt_bool_t ignore_wp;               /* Ignore WP pin */
    rt_base_t wp_pin;                  /* Write protect GPIO */
    rt_uint8_t wp_pin_active;          /* WP active level */
    
    struct rt_ref ref;                 /* Reference counter */
    struct rt_spinlock spinlock;       /* Spinlock for protection */
    
    void *priv;                        /* Private data */
};
```

#### struct rt_nvmem_cell

```c
struct rt_nvmem_cell {
    rt_list_t list;                    /* List node */
    
    int index;                         /* Cell index */
    const char *id;                    /* Cell identifier */
    const rt_bool_t free_able;         /* Can be freed */
    
    rt_uint32_t offset;                /* Offset in bytes */
    rt_uint32_t bytes;                 /* Size in bytes */
    rt_uint32_t bit_offset;            /* Bit offset within byte */
    rt_uint32_t nbits;                 /* Number of bits */
    
    struct rt_ref ref;                 /* Reference counter */
    
    struct rt_ofw_node *np;            /* Device tree node */
    struct rt_nvmem_device *nvmem;     /* Parent NVMEM device */
};
```

### Consumer APIs

#### Get NVMEM Cell

```c
struct rt_nvmem_cell *rt_nvmem_get_cell_by_name(struct rt_device *dev, 
                                                 const char *id);
struct rt_nvmem_cell *rt_nvmem_get_cell_by_index(struct rt_device *dev, 
                                                  int index);
```

**Parameters**:
- `dev`: Consumer device
- `id`: Cell name from device tree `nvmem-cell-names`
- `index`: Cell index (0-based)

**Returns**: Pointer to `rt_nvmem_cell` on success, NULL on failure

**Description**: Obtain a reference to an NVMEM cell for reading/writing. Must be released with `rt_nvmem_put_cell()`.

**Example**:
```c
struct rt_nvmem_cell *cell;

/* Get by name */
cell = rt_nvmem_get_cell_by_name(dev, "mac-address");
if (!cell) {
    rt_kprintf("Failed to get MAC address cell\n");
    return -RT_ERROR;
}

/* Get by index */
cell = rt_nvmem_get_cell_by_index(dev, 0);
```

#### Release NVMEM Cell

```c
void rt_nvmem_put_cell(struct rt_nvmem_cell *cell);
```

**Parameters**:
- `cell`: NVMEM cell to release

**Description**: Release a reference to an NVMEM cell obtained with `rt_nvmem_get_cell_*()`.

#### Read NVMEM Cell

```c
rt_ssize_t rt_nvmem_cell_read(struct rt_nvmem_cell *cell, 
                              void *buffer, rt_size_t len);
```

**Parameters**:
- `cell`: NVMEM cell to read
- `buffer`: Buffer to store read data
- `len`: Number of bytes to read

**Returns**: Number of bytes read on success, negative error code on failure

**Description**: Read data from an NVMEM cell. Supports bit-level access if configured.

#### Write NVMEM Cell

```c
rt_ssize_t rt_nvmem_cell_write(struct rt_nvmem_cell *cell, 
                               void *buffer, rt_size_t len);
```

**Parameters**:
- `cell`: NVMEM cell to write
- `buffer`: Data to write
- `len`: Number of bytes to write

**Returns**: Number of bytes written on success, negative error code on failure

**Description**: Write data to an NVMEM cell. Returns error if memory is read-only.

#### Typed Read Functions

```c
rt_ssize_t rt_nvmem_cell_read_u8(struct rt_nvmem_cell *cell, 
                                 rt_uint8_t *out_val);
rt_ssize_t rt_nvmem_cell_read_u16(struct rt_nvmem_cell *cell, 
                                  rt_uint16_t *out_val);
rt_ssize_t rt_nvmem_cell_read_u32(struct rt_nvmem_cell *cell, 
                                  rt_uint32_t *out_val);
rt_ssize_t rt_nvmem_cell_read_u64(struct rt_nvmem_cell *cell, 
                                  rt_uint64_t *out_val);
```

**Parameters**:
- `cell`: NVMEM cell to read
- `out_val`: Pointer to store the value

**Returns**: Number of bytes read on success, negative error code on failure

**Description**: Convenience functions to read specific integer types from NVMEM cells.

### Provider APIs

#### Register NVMEM Device

```c
rt_err_t rt_nvmem_device_register(struct rt_nvmem_device *ndev);
```

**Parameters**:
- `ndev`: NVMEM device to register

**Returns**: `RT_EOK` on success, negative error code on failure

**Description**: Register an NVMEM device with the framework. Initializes reference counting, parses device tree, and configures write-protect pin if present.

#### Unregister NVMEM Device

```c
rt_err_t rt_nvmem_device_unregister(struct rt_nvmem_device *ndev);
```

**Parameters**:
- `ndev`: NVMEM device to unregister

**Returns**: `RT_EOK` on success, `-RT_EBUSY` if device is still in use

**Description**: Unregister an NVMEM device. Fails if there are outstanding references.

#### Append Cell to Device

```c
rt_err_t rt_nvmem_device_append_cell(struct rt_nvmem_device *ndev, 
                                     struct rt_nvmem_cell *cell);
```

**Parameters**:
- `ndev`: NVMEM device
- `cell`: Cell to append

**Returns**: `RT_EOK` on success, negative error code on failure

**Description**: Add a cell to an NVMEM device. Used for runtime cell registration.

## Complete Example: Ethernet Driver with MAC Address

### Device Tree

```dts
/* EEPROM device with MAC address storage */
i2c0: i2c@40000000 {
    compatible = "vendor,i2c";
    reg = <0x40000000 0x1000>;
    
    eeprom@50 {
        compatible = "atmel,24c32";
        reg = <0x50>;
        
        #address-cells = <1>;
        #size-cells = <1>;
        
        /* MAC address cell */
        eth_mac: mac@0 {
            reg = <0x00 6>;
        };
        
        /* Device configuration */
        eth_config: config@10 {
            reg = <0x10 16>;
        };
    };
};

/* Ethernet controller referencing MAC address */
ethernet@50000000 {
    compatible = "vendor,ethernet";
    reg = <0x50000000 0x10000>;
    interrupts = <32 IRQ_TYPE_LEVEL_HIGH>;
    
    clocks = <&cru CLK_EMAC>;
    clock-names = "stmmaceth";
    
    /* Reference NVMEM for MAC address */
    nvmem-cells = <&eth_mac>;
    nvmem-cell-names = "mac-address";
};
```

### Ethernet Driver Implementation

```c
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/nvmem.h>

struct ethernet_device {
    struct rt_device parent;
    void *base;
    int irq;
    rt_uint8_t mac_addr[6];
    /* Other fields... */
};

static rt_err_t ethernet_load_mac_address(struct ethernet_device *eth_dev)
{
    struct rt_nvmem_cell *cell;
    rt_ssize_t ret;
    
    /* Get MAC address cell from device tree */
    cell = rt_nvmem_get_cell_by_name(&eth_dev->parent, "mac-address");
    if (!cell) {
        rt_kprintf("[ETH] No MAC address in NVMEM, using default\n");
        /* Use default or random MAC */
        eth_dev->mac_addr[0] = 0x00;
        eth_dev->mac_addr[1] = 0x11;
        eth_dev->mac_addr[2] = 0x22;
        eth_dev->mac_addr[3] = 0x33;
        eth_dev->mac_addr[4] = 0x44;
        eth_dev->mac_addr[5] = 0x55;
        return RT_EOK;
    }
    
    /* Read MAC address from NVMEM */
    ret = rt_nvmem_cell_read(cell, eth_dev->mac_addr, 6);
    if (ret != 6) {
        rt_kprintf("[ETH] Failed to read MAC address: %d\n", ret);
        rt_nvmem_put_cell(cell);
        return -RT_ERROR;
    }
    
    /* Release cell */
    rt_nvmem_put_cell(cell);
    
    rt_kprintf("[ETH] MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
               eth_dev->mac_addr[0], eth_dev->mac_addr[1],
               eth_dev->mac_addr[2], eth_dev->mac_addr[3],
               eth_dev->mac_addr[4], eth_dev->mac_addr[5]);
    
    return RT_EOK;
}

static rt_err_t ethernet_write_mac_address(struct ethernet_device *eth_dev, 
                                            const rt_uint8_t *mac)
{
    struct rt_nvmem_cell *cell;
    rt_ssize_t ret;
    
    /* Get MAC address cell */
    cell = rt_nvmem_get_cell_by_name(&eth_dev->parent, "mac-address");
    if (!cell) {
        rt_kprintf("[ETH] No MAC address cell available\n");
        return -RT_ERROR;
    }
    
    /* Write new MAC address */
    ret = rt_nvmem_cell_write(cell, (void *)mac, 6);
    if (ret != 6) {
        rt_kprintf("[ETH] Failed to write MAC address: %d\n", ret);
        rt_nvmem_put_cell(cell);
        return -RT_ERROR;
    }
    
    rt_nvmem_put_cell(cell);
    
    /* Update local copy */
    rt_memcpy(eth_dev->mac_addr, mac, 6);
    
    rt_kprintf("[ETH] MAC Address updated successfully\n");
    
    return RT_EOK;
}

static rt_err_t ethernet_probe(struct rt_platform_device *pdev)
{
    struct ethernet_device *eth_dev;
    rt_err_t ret;
    
    eth_dev = rt_calloc(1, sizeof(*eth_dev));
    if (!eth_dev) {
        return -RT_ENOMEM;
    }
    
    /* Initialize device */
    eth_dev->parent.ofw_node = pdev->parent.ofw_node;
    
    /* Get hardware resources */
    eth_dev->base = rt_dm_dev_get_address(&pdev->parent);
    if (!eth_dev->base) {
        rt_free(eth_dev);
        return -RT_ERROR;
    }
    
    /* Load MAC address from NVMEM */
    ret = ethernet_load_mac_address(eth_dev);
    if (ret != RT_EOK) {
        rt_kprintf("[ETH] Warning: MAC address load failed\n");
    }
    
    /* Configure hardware with MAC address */
    /* ... hardware initialization ... */
    
    rt_kprintf("[ETH] Ethernet initialized\n");
    
    return RT_EOK;
}

static const struct rt_ofw_node_id ethernet_ofw_match[] = {
    { .compatible = "vendor,ethernet" },
    { /* sentinel */ }
};

static struct rt_platform_driver ethernet_driver = {
    .name = "vendor-ethernet",
    .ids = ethernet_ofw_match,
    .probe = ethernet_probe,
};
RT_PLATFORM_DRIVER_EXPORT(ethernet_driver);
```

## NVMEM Provider Driver Example

### I2C EEPROM Driver

```c
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/nvmem.h>
#include <drivers/i2c.h>

struct eeprom_device {
    struct rt_nvmem_device nvmem;
    struct rt_i2c_bus_device *i2c_bus;
    rt_uint16_t i2c_addr;
    rt_size_t size;
    rt_uint32_t page_size;
};

static rt_ssize_t eeprom_reg_read(struct rt_nvmem_device *ndev, 
                                  int offset, void *val, rt_size_t bytes)
{
    struct eeprom_device *eeprom;
    struct rt_i2c_msg msgs[2];
    rt_uint8_t addr_buf[2];
    rt_ssize_t ret;
    
    eeprom = rt_container_of(ndev, struct eeprom_device, nvmem);
    
    /* Check bounds */
    if (offset + bytes > eeprom->size) {
        return -RT_EINVAL;
    }
    
    /* Prepare address (big-endian) */
    addr_buf[0] = (offset >> 8) & 0xFF;
    addr_buf[1] = offset & 0xFF;
    
    /* Write address */
    msgs[0].addr = eeprom->i2c_addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = addr_buf;
    msgs[0].len = 2;
    
    /* Read data */
    msgs[1].addr = eeprom->i2c_addr;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf = val;
    msgs[1].len = bytes;
    
    ret = rt_i2c_transfer(eeprom->i2c_bus, msgs, 2);
    if (ret != 2) {
        return -RT_ERROR;
    }
    
    return bytes;
}

static rt_ssize_t eeprom_reg_write(struct rt_nvmem_device *ndev, 
                                   int offset, void *val, rt_size_t bytes)
{
    struct eeprom_device *eeprom;
    struct rt_i2c_msg msg;
    rt_uint8_t *write_buf;
    rt_size_t written = 0;
    rt_ssize_t ret;
    
    eeprom = rt_container_of(ndev, struct eeprom_device, nvmem);
    
    /* Check bounds */
    if (offset + bytes > eeprom->size) {
        return -RT_EINVAL;
    }
    
    write_buf = rt_malloc(eeprom->page_size + 2);
    if (!write_buf) {
        return -RT_ENOMEM;
    }
    
    /* Write page by page */
    while (written < bytes) {
        rt_uint32_t page_offset = offset % eeprom->page_size;
        rt_size_t chunk = RT_MIN(bytes - written, 
                                 eeprom->page_size - page_offset);
        
        /* Prepare write buffer: address + data */
        write_buf[0] = (offset >> 8) & 0xFF;
        write_buf[1] = offset & 0xFF;
        rt_memcpy(&write_buf[2], (rt_uint8_t *)val + written, chunk);
        
        msg.addr = eeprom->i2c_addr;
        msg.flags = RT_I2C_WR;
        msg.buf = write_buf;
        msg.len = chunk + 2;
        
        ret = rt_i2c_transfer(eeprom->i2c_bus, &msg, 1);
        if (ret != 1) {
            rt_free(write_buf);
            return -RT_ERROR;
        }
        
        /* Wait for write cycle to complete (typ. 5ms for EEPROM) */
        rt_thread_mdelay(5);
        
        written += chunk;
        offset += chunk;
    }
    
    rt_free(write_buf);
    
    return written;
}

static rt_err_t eeprom_probe(struct rt_platform_device *pdev)
{
    struct eeprom_device *eeprom;
    struct rt_device *dev = &pdev->parent;
    rt_err_t ret;
    rt_uint32_t size;
    
    eeprom = rt_calloc(1, sizeof(*eeprom));
    if (!eeprom) {
        return -RT_ENOMEM;
    }
    
    /* Get I2C bus */
    eeprom->i2c_bus = rt_i2c_bus_device_find(
        rt_dm_dev_get_name_id(dev, NULL, 0, "i2c-bus"));
    if (!eeprom->i2c_bus) {
        rt_kprintf("[EEPROM] I2C bus not found\n");
        rt_free(eeprom);
        return -RT_ERROR;
    }
    
    /* Get I2C address */
    if (rt_dm_dev_prop_read_u32(dev, "reg", &eeprom->i2c_addr) != RT_EOK) {
        rt_kprintf("[EEPROM] No I2C address specified\n");
        rt_free(eeprom);
        return -RT_ERROR;
    }
    
    /* Get EEPROM size (default 4KB for AT24C32) */
    if (rt_dm_dev_prop_read_u32(dev, "size", &size) != RT_EOK) {
        size = 4096;  /* Default 4KB */
    }
    eeprom->size = size;
    
    /* Get page size (default 32 bytes) */
    if (rt_dm_dev_prop_read_u32(dev, "pagesize", 
                                &eeprom->page_size) != RT_EOK) {
        eeprom->page_size = 32;
    }
    
    /* Initialize NVMEM device */
    eeprom->nvmem.parent.ofw_node = dev->ofw_node;
    eeprom->nvmem.reg_read = eeprom_reg_read;
    eeprom->nvmem.reg_write = eeprom_reg_write;
    eeprom->nvmem.size = eeprom->size;
    eeprom->nvmem.word_size = 1;
    eeprom->nvmem.stride = 1;
    eeprom->nvmem.priv = eeprom;
    
    /* Register NVMEM device */
    ret = rt_nvmem_device_register(&eeprom->nvmem);
    if (ret != RT_EOK) {
        rt_kprintf("[EEPROM] Failed to register NVMEM device\n");
        rt_free(eeprom);
        return ret;
    }
    
    rt_kprintf("[EEPROM] Registered %d bytes at I2C address 0x%02X\n",
               eeprom->size, eeprom->i2c_addr);
    
    return RT_EOK;
}

static const struct rt_ofw_node_id eeprom_ofw_match[] = {
    { .compatible = "atmel,24c32" },
    { .compatible = "atmel,24c64" },
    { .compatible = "atmel,24c256" },
    { /* sentinel */ }
};

static struct rt_platform_driver eeprom_driver = {
    .name = "atmel-eeprom",
    .ids = eeprom_ofw_match,
    .probe = eeprom_probe,
};
RT_PLATFORM_DRIVER_EXPORT(eeprom_driver);
```

## Best Practices

### For Consumers

1. **Always Check Return Values**
   ```c
   cell = rt_nvmem_get_cell_by_name(dev, "calibration");
   if (!cell) {
       /* Handle error - use default values */
   }
   ```

2. **Release Resources**
   ```c
   cell = rt_nvmem_get_cell_by_name(dev, "data");
   if (cell) {
       rt_nvmem_cell_read(cell, buffer, size);
       rt_nvmem_put_cell(cell);  /* Always release */
   }
   ```

3. **Handle Read-Only Memory**
   ```c
   ret = rt_nvmem_cell_write(cell, data, len);
   if (ret < 0) {
       if (ret == -RT_ENOSYS) {
           rt_kprintf("Memory is read-only\n");
       }
   }
   ```

4. **Use Typed Reads for Simple Values**
   ```c
   rt_uint32_t serial_number;
   
   cell = rt_nvmem_get_cell_by_name(dev, "serial");
   if (cell) {
       rt_nvmem_cell_read_u32(cell, &serial_number);
       rt_nvmem_put_cell(cell);
   }
   ```

### For Providers

1. **Implement Proper Bounds Checking**
   ```c
   if (offset + bytes > nvmem->size) {
       return -RT_EINVAL;
   }
   ```

2. **Support Write Protection**
   ```c
   /* Framework handles wp-gpios automatically */
   /* Just don't set ignore_wp flag */
   nvmem->ignore_wp = RT_FALSE;
   ```

3. **Handle Page-Based Writes**
   ```c
   /* For devices with page write limits */
   /* Write in page-sized chunks and wait for completion */
   rt_thread_mdelay(write_cycle_time_ms);
   ```

4. **Initialize All Fields**
   ```c
   nvmem->size = total_size;
   nvmem->word_size = 1;  /* Byte-addressable */
   nvmem->stride = 1;     /* Minimum access unit */
   nvmem->reg_read = my_read;
   nvmem->reg_write = my_write;
   ```

## Troubleshooting

### Cell Not Found

**Problem**: `rt_nvmem_get_cell_by_name()` returns NULL

**Solutions**:
1. Check device tree `nvmem-cells` and `nvmem-cell-names` properties match
2. Verify NVMEM provider device is probed before consumer
3. Check `#address-cells` and `#size-cells` in provider node

### Write Fails

**Problem**: `rt_nvmem_cell_write()` returns error

**Solutions**:
1. Check if memory is marked `read-only` in device tree
2. Verify write-protect pin is not active
3. Check provider's `reg_write` callback is implemented
4. Verify offset and size are within bounds

### Data Corruption

**Problem**: Read data doesn't match written data

**Solutions**:
1. Check page-write boundaries for page-based devices
2. Verify write cycle delays are sufficient
3. Add proper synchronization if accessing from multiple threads
4. Check bit-offset calculations for bit-addressable cells

## Performance Considerations

### Read Performance

- **Caching**: Cache frequently-read values (e.g., MAC address) after first read
- **Batch Reads**: Read multiple cells in one operation if possible
- **Async Access**: Use separate thread for slow NVMEM operations

### Write Performance

- **Write Caching**: Buffer writes and flush periodically
- **Wear Leveling**: Distribute writes across memory for EEPROMs
- **Write Coalescing**: Combine multiple small writes into larger operations

### Resource Usage

- **Cell References**: Release cells promptly with `rt_nvmem_put_cell()`
- **Memory**: Consider memory cost of buffering for page-based devices
- **I/O**: EEPROM writes can take several milliseconds per page

## Related Modules

- **OFW (Open Firmware)**: Device tree parsing for NVMEM configuration
- **PIN**: Write-protect GPIO handling
- **I2C/SPI**: Common buses for NVMEM devices

## References

- NVMEM header: `components/drivers/include/drivers/nvmem.h`
- NVMEM implementation: `components/drivers/nvmem/nvmem.c`
- Linux NVMEM framework: Documentation reference for compatible design
