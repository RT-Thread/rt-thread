# Device Driver Model (DM) Documentation Index

This directory contains comprehensive documentation for RT-Thread's Device Driver Model and related subsystems.

## Core Documentation

- **[README.md](README.md)** - Device Driver Model Overview (English)
  - DM architecture and concepts
  - Bus, driver, and platform device models
  - OFW/Device Tree integration
  - Common APIs and usage patterns
  - Migration guide

- **[README_zh.md](README_zh.md)** - 设备驱动模型概述 (中文)
  - DM 架构和概念
  - 总线、驱动和平台设备模型
  - OFW/设备树集成
  - 通用 API 和使用模式
  - 迁移指南

## Module-Specific Documentation

### Power Management

#### Regulator Framework
- **[regulator/README.md](regulator/README.md)** - Voltage/Current Regulator (English)
- **[regulator/README_zh.md](regulator/README_zh.md)** - 电压/电流调节器 (中文)

**Status**: ✅ Complete  
**Topics Covered**:
- Consumer API with complete examples
- Provider (driver) implementation guide
- Device tree bindings (fixed, GPIO, SCMI)
- Best practices and troubleshooting
- Performance considerations

#### Clock Framework
- **clk/** - Clock Management Framework

**Status**: 📝 To Be Documented  
**Planned Topics**:
- Clock consumer API
- Clock provider implementation
- Clock tree management
- Fixed-rate, PLL, mux, divider clocks
- Device tree bindings

#### Pin Control
- **pinctrl/** - Pin Multiplexing and Configuration

**Status**: 📝 To Be Documented  
**Planned Topics**:
- Pin configuration API
- Pin multiplexing
- Pin control driver implementation
- Device tree bindings

#### Reset Controller
- **reset/** - Reset Controller Framework

**Status**: 📝 To Be Documented  
**Planned Topics**:
- Reset consumer API
- Reset provider implementation
- Device tree bindings

#### Power Domain
- **pmdomain/** - Power Domain Management

**Status**: 📝 To Be Documented  
**Planned Topics**:
- Power domain consumer API
- Power domain provider implementation
- Domain hierarchy
- Device tree bindings

### Interrupt and Timing

#### Platform Interrupt Controller
- **pic/** - Platform Interrupt Controller

**Status**: 📝 To Be Documented  
**Planned Topics**:
- IRQ domain management
- IRQ mapping
- PIC driver implementation

#### Hardware Timer
- **hwtimer/** - Hardware Timer Framework (with DM support)

**Status**: 📝 To Be Documented  
**Planned Topics**:
- Timer API with DM
- Timer driver implementation
- Device tree bindings

### Storage and Memory

#### NVMEM
- **nvmem/** - Non-Volatile Memory Framework

**Status**: 📝 To Be Documented  
**Planned Topics**:
- NVMEM consumer API
- NVMEM provider implementation
- EEPROM, OTP, eFuse support
- Device tree bindings

#### Block Devices
- **block/** - Block Device Layer (with DM support)

**Status**: 📝 To Be Documented  
**Planned Topics**:
- Block device API with DM
- Partition support
- Device tree bindings

#### MTD
- **mtd/** - Memory Technology Device (with DM support)

**Status**: 📝 To Be Documented  
**Planned Topics**:
- MTD framework with DM
- NOR/NAND flash support
- Device tree bindings

### Communication

#### Mailbox
- **mailbox/** - Mailbox/Doorbell Framework

**Status**: 📝 To Be Documented  
**Planned Topics**:
- Mailbox consumer API
- Mailbox controller driver
- Inter-processor communication
- Device tree bindings

#### DMA
- **dma/** - DMA Engine Framework

**Status**: 📝 To Be Documented  
**Planned Topics**:
- DMA consumer API
- DMA controller driver
- DMA transfer types
- Device tree bindings

### Bus Controllers

#### PCI
- **pci/** - PCI Bus Support

**Status**: 📝 To Be Documented  
**Planned Topics**:
- PCI device enumeration
- PCI driver implementation
- PCIe host controller
- Device tree bindings

#### I2C (DM Extensions)
- **i2c/** - I2C with DM Support

**Status**: 📝 To Be Documented  
**Planned Topics**:
- I2C with device tree
- I2C controller driver with DM

#### SPI (DM Extensions)
- **spi/** - SPI with DM Support

**Status**: 📝 To Be Documented  
**Planned Topics**:
- SPI with device tree
- SPI controller driver with DM

### Specialized Hardware

#### Thermal Management
- **thermal/** - Thermal Management Framework

**Status**: 📝 To Be Documented  
**Planned Topics**:
- Thermal zone management
- Thermal cooling devices
- Trip points
- Device tree bindings

#### Multi-Function Device
- **mfd/** - Multi-Function Device Framework

**Status**: 📝 To Be Documented  
**Planned Topics**:
- MFD parent device
- Sub-device registration
- Shared resources
- Device tree bindings

#### Industrial I/O
- **iio/** - Industrial I/O Subsystem

**Status**: 📝 To Be Documented  
**Planned Topics**:
- IIO device framework
- Channels and attributes
- Buffered data capture
- Device tree bindings

#### PHY Framework
- **phy/** - Physical Layer Framework

**Status**: 📝 To Be Documented  
**Planned Topics**:
- PHY consumer API
- PHY provider implementation
- USB, PCIe, SATA PHY support
- Device tree bindings

#### Ethernet PHY
- **phye/** - Ethernet PHY Framework

**Status**: 📝 To Be Documented  
**Planned Topics**:
- Ethernet PHY management
- MDIO bus
- PHY drivers
- Device tree bindings

### System Support

#### Open Firmware (OFW)
- **ofw/** - Device Tree Support

**Status**: ⚠️ Partially Documented  
**Existing**: [../ofw/dtc.md](../ofw/dtc.md)  
**Additional Planned Topics**:
- FDT parsing internals
- OFW API reference
- Property reading helpers
- IRQ and address translation

#### Firmware
- **firmware/** - Firmware Framework

**Status**: 📝 To Be Documented  
**Planned Topics**:
- ARM SCMI support
- Firmware loading
- Device tree bindings

#### Hardware Cache
- **hwcache/** - Hardware Cache Management

**Status**: 📝 To Be Documented  
**Planned Topics**:
- Cache controller framework
- L2/L3 cache management

#### Hardware Spinlock
- **hwspinlock/** - Hardware Spinlock

**Status**: 📝 To Be Documented  
**Planned Topics**:
- Hardware spinlock API
- Multi-core synchronization

## Documentation Standards

All module documentation should include:

1. **Introduction**
   - General concept overview
   - RT-Thread specific implementation
   - Use cases

2. **Kconfig Configuration**
   - All configuration options
   - Menuconfig location
   - Dependencies

3. **Device Tree Bindings**
   - Standard properties
   - Example DTS nodes
   - Consumer usage examples

4. **Application Layer API**
   - Complete function reference
   - Parameter descriptions
   - Return values
   - Usage examples

5. **Driver Implementation Guide**
   - Key structures
   - Operations to implement
   - Complete driver examples
   - Best practices

6. **Comprehensive Examples**
   - Real-world use cases
   - Complete working code
   - Error handling patterns

7. **Troubleshooting**
   - Common issues
   - Debugging tips
   - Performance considerations

8. **Architecture Diagrams** (SVG)
   - Component relationships
   - Data flow
   - Clear and professional formatting

## Contributing

When adding new module documentation:

1. Follow the structure established by the regulator documentation
2. Include both English and Chinese versions
3. Provide complete, tested code examples
4. Create clear SVG diagrams
5. Cross-reference related modules
6. Update this INDEX.md file

## Status Legend

- ✅ Complete - Full documentation available
- ⚠️ Partial - Some documentation exists, needs completion
- 📝 To Be Documented - Planned but not yet created
- 🚧 In Progress - Currently being written

## Priority Modules

Based on usage frequency and importance:

1. ✅ **regulator** - Complete
2. **clk** - High priority (power management)
3. **pinctrl** - High priority (hardware configuration)
4. **reset** - High priority (hardware control)
5. **ofw** - High priority (device tree)
6. **pic** - Medium priority (interrupt handling)
7. **dma** - Medium priority (data transfer)
8. **nvmem** - Medium priority (persistent data)
9. **mailbox** - Medium priority (IPC)
10. **thermal** - Medium priority (power management)

Other modules follow based on community needs and hardware support requirements.

## Related Documentation

- [Device Driver Framework](../framework/device.md) - Basic device model
- [Device Tree Compiler](../ofw/dtc.md) - DTC tool usage
- [I2C Driver](../i2c/i2c.md) - Traditional I2C (compare with DM)
- [SPI Driver](../spi/spi.md) - Traditional SPI (compare with DM)
- [PIN Driver](../pin/pin.md) - Traditional PIN (compare with DM)

## External References

- [Device Tree Specification](https://devicetree-specification.readthedocs.io/)
- [Linux Kernel Driver Model](https://www.kernel.org/doc/html/latest/driver-api/driver-model/)
- [Linux Device Tree Bindings](https://www.kernel.org/doc/Documentation/devicetree/bindings/)
- RT-Thread Source: `components/drivers/`
