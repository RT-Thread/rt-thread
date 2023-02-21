# Hardware Abstraction Layer

## Overview

The Hardware Abstraction Layer (HAL) provides a high-level interface to configure and use hardware blocks on ModusToolbox™ MCUs. It is a generic interface that can be used across multiple product families. The focus on ease-of-use and portability means the HAL does not expose all of the low-level peripheral functionality. The HAL can be combined with platform-specific libraries (such as the PSoC™ 4/6 Peripheral Driver Library (PDL)) within a single application. You can leverage the HAL's simpler and more generic interface for most of an application, even if one portion requires finer-grained control.

To use code from the HAL, the specific driver header file can be included or the top level `cyhal.h` header can be include to allow access to any driver. Additionally, a few system wide drivers should be initialized at device startup. This includes `cyhal_hwmgr_init()` and `cyhal_syspm_init`.

## API Structure
The API functions for each HAL driver can be divided into the following categories:
* A `_init` function allocates a block (along with any dependent resources), configures it, and enables it.
* A `_free` function disables a block, releases any dependent resources, and marks it as unused.
* Additional functions provide access to block-specific functionality and, in some cases, manipulate a block's configuration after it has been initialized.

The `_init` API functions require a pointer to an instance of a driver-specific type (for example, `cyhal_uart_t`). This instance must be allocated by the application code and passed via pointer into the initialization function, which will populate its contents (this structure enables the HAL to avoid performing any dynamic memory allocation). From an application point of view, these structs function as an opaque handle. The same object must be passed to all subsequent API calls that operate on the same hardware instance. The struct definitions are defined within the platform-specific HAL implementation. Application code should not rely on the specific contents, which is an implementation detail and is subject to change between platforms and/or HAL releases.

Many `_init` functions also have an argument for a pointer to a `cyhal_clock_t` instance. This is an optional argument to enable sharing of clock dividers in large designs (via using `cyhal_clock_init` or `cyhal_clock_allocate` to allocate a shared divider). If a `NULL` value is passed, the init function will allocate a clock divider that is exclusive to that block instance.

Note: Some APIs that manipulate block timing may not be able to support as wide of a range of values when using a shared divider. When a divider is shared the driver cannot unilaterally change the divider's value because that would affect other divider clients. This is not an issue with a dedicated divider.

## Resource Identification
For peripherals, the HAL generally does not identify block instances directly (for example, by index). Instead, block instances are identified indirectly by specifying the desired pin for each function. The `_init` function selects the block instance that connects to the specified pins. If multiple block instances can connect to the specified pins, the HAL may select any available instance.

## Hardware Manager
To ensure that distinct driver instances do not attempt to manipulate the same hardware blocks, the HAL includes facilities for allocating and tracking resource use. The "Hardware Manager" component handles this. It is usually not necessary to interact directly with the Hardware Manager from application firmware. The peripheral drivers automatically reserve the resources they require (and check for conflicts) as part of the `_init` API. However, the Hardware Manager is part of the public HAL API, and the application may directly invoke it to handle advanced use cases. For example, if a block instance will be managed by a lower-level API (for example, PSoC™ 4/6 PDL), the application should call the `cyhal_hwmgr_reserve` function to ensure that no other HAL driver attempts to use the same block.

## Power Management
The System driver provides general purpose power management APIs (`cyhal_system_register_callback` and `cyhal_system_unregister_callback`) that can be used to control when the application can go to sleep at a global level. Additionally, each peripheral driver has its own default power management strategy. The strategy is:
* Peripherals that can operate as is in the requested lower power mode do so
* Peripherals that are purely input allow the lower power mode transition, but make sure they restore there state (if needed) when exiting the low power mode
* Peripherals that are actively outputting a signal, but cannot do so in the requested power mode, block the transition
* Peripherals that can output a signal, but are not currently, will allow the lower power mode transition, and restore state when it comes back

Additionally, all peripherals provide a function (`cyhal_<peripheral>_set_power_mode_strategy`) that allows changing this behavior. There are three possible modes: Default, Allow, and Custom. Default does what is described above and what all peripherals do unless overridden. Allow causes the peripheral to always accept the low power transition independent of what it is currently doing. When the power mode exits, it will attempt to resume its previous activity. Custom causes the driver to call the callback function provided in `cyhal_system_set_power_custom_callback` to allow the application to specify what to do in the case the peripheral is currently running, but cannot operate in the new mode.

## Compile Time Dependencies
The HAL public interface is consistent across all platforms that the HAL supports. However, the HAL interface does depend on types that are defined by platform-specific HAL implementations (for example, the driver-specific "handle" types). Additionally, a HAL implementation may be compile-time dependent on device-specific data structures (for example, mapping pins to peripheral instances). This means that in order to compile an application that depends on the HAL, it must build against a platform-specific implementation of the HAL, specifying a particular device. The resulting application will be source (but not binary) compatible with a HAL implementation for any other platform.

## Event Handling
Many HAL drivers provide an API for registering a callback which is invoked when certain (driver-specific) events occur. These drivers also often provide an API for enabling or disabling specific types of events. Unless otherwise documented, the callback will only be invoked for events that occur while that event type is enabled. Specifically, events that occur while a given event type is disabled are not queued and will not trigger a callback when that event type is (re)enabled.

## Error reporting
The HAL uses the `cy_rslt_t` type (from the core-lib library) in all places where a HAL function might return an error code. This provides structured error reporting and makes it easy to determine the module from which the error arose, as well as the specific error cause. Macros are provided to help extract this information from a `cy_rslt_t` value.

The HAL driver headers provide macros corresponding to codes for common error situations. Note that the errors listed in the driver header are not a comprehensive list; in less common cases a low-level, implementation-specific error code may be returned.

For more details on interacting with `cy_rslt_t` see [Result Type](docs/html/group__group__result.html).

## RTOS Integration
Some HAL driver's may have slightly different behavior when run in an RTOS environment. This is typically found in operations that need to wait for a significant period of time. In an RTOS aware environment, the function will attempt to wait using the RTOS. This allows other threads in the application to run while the current operation is waiting. In non-RTOS aware environments (eg: bare metal environments) the functions will instead rely on busy waits for operations to complete. To inform the HAL that an RTOS environment is being used the `RTOS_AWARE` component (COMPONENTS+=RTOS_AWARE) or the `CY_RTOS_AWARE` define (DEFINES+=CY_RTOS_AWARE) must be set. When set, the HAL will use the [RTOS Abstraction](https://github.com/infineon/abstraction-rtos) APIs to wait.

When using HAL in an RTOS environment with the `RTOS_AWARE` component enabled, initialization of the HAL drivers must be done after the RTOS has been initialized in order to ensure that the RTOS modules such as semaphores used by the HAL drivers are initialized properly. A temporary exception to this is the SDIO HAL driver that is initialized as a part of cybsp_init() and will be addressed in future releases.


## More information
* [API Reference Guide](https://infineon.github.io/mtb-hal-cat1/html/modules.html)
* [Cypress Semiconductor, an Infineon Technologies Company](http://www.cypress.com)
* [Infineon GitHub](https://github.com/infineon)
* [ModusToolbox™](https://www.cypress.com/products/modustoolbox-software-environment)

---
© Cypress Semiconductor Corporation (an Infineon company) or an affiliate of Cypress Semiconductor Corporation, 2019-2021.
