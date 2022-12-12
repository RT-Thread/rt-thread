# PSoC 6 Cortex M0+ BLESS Controller pre-built image (CM0P_BLESS)

### Overview
Pre-compiled BLESS Controller image executed on the Cortex M0+ core of the PSoC 6 dual-core MCU.
The image is provided as C array ready to be compiled as part of the Cortex M4 application.
The Cortex M0+ application code is placed to internal flash by the Cortex M4 linker script.

This image is used only in BLE dual CPU mode. In this mode, the BLE functionality is split between
CM0+ (controller) and CM4 (host). It uses IPC for communication between two CPU cores where both the
controller and host run:

    -------------------------------          ------------------------------------
    |    CM0p (pre-built image)   |          |              CM4                 |
    | --------------------  ----- |          | -----  ------------------------  |
    | |                  |  | H | |   IPC    | |   |  |  BLE Application     |  |
    | | BLE Controller   |--| c | |<-------->| |   |  ------------------------  |
    | |       (LL)       |  | I | |(commands,| |   |          |            |    |
    | |                  |  ----- |  events) | |   |  -----------------    |    |
    | --------------------        |          | | H |  |  BLE Profiles |    |    |
    -------------------------------          | | C |  -----------------    |    |
                  |                          | | I |          |            |    |
       ------------------------              | |   |  ------------------------- |
       |       BLE HW         |              | |   |--|  BLE Host (GAP, L2CAP,| |
       ------------------------              | |   |  |  SM, ATT)             | |
                                             | |   |  ------------------------- |
                                             | -----                            |
                                             ------------------------------------


BLESS Controller pre-built image executes the following steps:
- configures BLESS interrupt
- registers IPC-pipe callback for BLE middleware; the BLE middleware uses this callback to
  initialize and enable the BLE controller when BLE middleware operates in BLE dual CPU mode
- starts CM4 core at CY_CORTEX_M4_APPL_ADDR=0x10020000
- goes to the while loop where processes BLE controller events and puts the CM0+ core into Deep Sleep.

### New in this image
- Updated the BLE Stack to version 5.0.8

### Defect Fixes
* Updated Cy_BLE_ControllerEnterLPM API for handling a scenario where wake-up is initiated by the hardware.
* Improved the handling of Cy_BLE_StackShutdown API to avoid timing-sensitive bugs.


The revision history of the PSoC 6 BLE Middleware is also available on the [API Reference Guide Changelog](https://cypresssemiconductorco.github.io/bless/ble_api_reference_manual/html/page_group_ble_changelog.html).


### Usage
To use this image, update the ram, flash, and FLASH_CM0P_SIZE values in the linker script for CM4:
```
Example for the GCC compiler:
...
MEMORY
{
	...
	ram       (rwx)   : ORIGIN = 0x08003000, LENGTH = 0x044800
	flash     (rx)    : ORIGIN = 0x10000000, LENGTH = 0x100000
	...  
}
...
/* The size and start addresses of the Cortex-M0+ application image */
FLASH_CM0P_SIZE  = 0x20000;
...
```
```
Example for the IAR compiler:
...
/* RAM */
define symbol __ICFEDIT_region_IRAM1_start__ = 0x08003000;
define symbol __ICFEDIT_region_IRAM1_end__   = 0x08047800;
/* Flash */
define symbol __ICFEDIT_region_IROM1_start__ = 0x10000000;
define symbol __ICFEDIT_region_IROM1_end__   = 0x10100000;
...
/* The size and start addresses of the Cortex-M0+ application image */
define symbol FLASH_CM0P_SIZE  = 0x20000;
...
```
```
Example for ARMC6 compiler:
...
; RAM
#define RAM_START               0x08003000
#define RAM_SIZE                0x00044800
; Flash
#define FLASH_START             0x10000000
#define FLASH_SIZE              0x00100000
...
/* The size and start addresses of the Cortex-M0+ application image */
#define FLASH_CM0P_SIZE         0x20000
...
```

To use this image in the custom BSP, adjust the BSP target makefile to
add the COMPONENT_CM0P_BLESS directory to the list of components
discovered by ModusToolbox build system:

```
COMPONENTS+=CM0P_BLESS
```

Also, to operate in Dual CPU mode, add the COMPONENT_BLESS_HOST_IPC directory to 
the list of the application level Makefile components:

```
COMPONENTS+=BLESS_HOST_IPC
```

Make sure there is a single CM0P_* component included in the COMPONENTS list
(it might be needed to remove CM0P_SLEEP from the list of standard BSP components).

---
Copyright (c) Cypress Semiconductor Corporation, 2020.
