# PSoC 6 Cortex M0+ Crypto server prebuilt image (CM0P_CRYPTO)

### Overview
Crypto server prebuilt application image is executed on the Cortex M0+ core of the PSoC 6 dual-core MCU.
The image is provided as C array ready to be compiled as part of the Cortex M4 application.
The Cortex M0+ application code is placed to internal flash by the Cortex M4 linker script.

The Crypto server image executes the following steps:
- configures IPC channel for data exchange between client and server applications;
- configures three interrupts: an IPC notify interrupt, an IPC release interrupt, and an interrupt for error handling.
- starts CM4 core at CY_CORTEX_M4_APPL_ADDR=0x1000A000
- goes to the infinite loop that processes the crypto server events and puts the CM0+ core into Deep Sleep.

### Usage
To use this image, update the FLASH_CM0P_SIZE value in the linker script for CM4:
```
Example for the GCC compiler:
...
/* The size and start addresses of the Cortex-M0+ application image */
FLASH_CM0P_SIZE  = 0xA000;
...
```
```
Example for the IAR compiler:
...
/* The size and start addresses of the Cortex-M0+ application image */
define symbol FLASH_CM0P_SIZE  = 0xA000;
...
```
```
Example for ARMC6 compiler:
...
/* The size and start addresses of the Cortex-M0+ application image */
#define FLASH_CM0P_SIZE         0xA000
...
```

To use this image in the custom BSP, adjust the BSP target makefile to
add the COMPONENT_CM0P_CRYPTO directory to the list of components
discovered by ModusToolbox build system:

```
COMPONENTS+=CM0P_CRYPTO
```

Make sure there is a single CM0P_* component included in the COMPONENTS list
(it might be needed to remove CM0P_SLEEP from the list of standard BSP components).


### Crypto client configuration

Example configuration of the crypto client for the Cortex-M4 core
compatible with the prebuilt crypto server CM0+ application:

```
#define MY_CHAN_CRYPTO         (uint32_t)(3u)    /* IPC data channel for the Crypto */
#define MY_INTR_CRYPTO_SRV     (uint32_t)(1u)    /* IPC interrupt structure for the Crypto server */
#define MY_INTR_CRYPTO_CLI     (uint32_t)(2u)    /* IPC interrupt structure for the Crypto client */
#define MY_INTR_CRYPTO_SRV_MUX (IRQn_Type)(2u)   /* CM0+ IPC interrupt mux number the Crypto server */
#define MY_INTR_CRYPTO_CLI_MUX (IRQn_Type)(3u)   /* CM0+ IPC interrupt mux number the Crypto client */
#define MY_INTR_CRYPTO_ERR_MUX (IRQn_Type)(4u)   /* CM0+ ERROR interrupt mux number the Crypto server */

const cy_stc_crypto_config_t myCryptoConfig =
{
    /* .ipcChannel             */ MY_CHAN_CRYPTO,
    /* .acquireNotifierChannel */ MY_INTR_CRYPTO_SRV,
    /* .releaseNotifierChannel */ MY_INTR_CRYPTO_CLI,
    /* .releaseNotifierConfig */ {
        /* .cm0pSrc            */ cpuss_interrupts_ipc_2_IRQn, /* depends on selected releaseNotifierChannel value */
        /* .intrPriority       */ 2u,
    },
    /* .userCompleteCallback   */ NULL,
    /* .userGetDataHandler     */ NULL,
    /* .userErrorHandler       */ NULL,
    /* .acquireNotifierConfig */ {
        /* .cm0pSrc            */ cpuss_interrupts_ipc_1_IRQn, /* depends on selected acquireNotifierChannel value */
        /* .intrPriority       */ 2u,
    },
    /* .cryptoErrorIntrConfig */ {
        /* .cm0pSrc            */ cpuss_interrupt_crypto_IRQn,
        /* .intrPriority       */ 2u,
    }
};
```

Refer to the [PDL API Reference Guide][pdl_crypto] for more information related to the PSoC 6 Crypto client configuration.

---
Copyright (c) Cypress Semiconductor Corporation, 2019.

[pdl_crypto]: https://cypresssemiconductorco.github.io/psoc6pdl/pdl_api_reference_manual/html/group__group__crypto__cli__srv.html
