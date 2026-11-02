/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

#ifndef BSP_IO_ISOLATION_H
#define BSP_IO_ISOLATION_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "config/bsp_memory_defaults_ra6w1.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*
 * Retention io is adjusted on a domain basis.
 * Therefore, find the block of the pin for which retention-io is specified and assign retention to that domain.
 *
 * IO_RETENTION_VBAT contains the XTAL32k port, so it cannot be retained.
 * IO_RETENTION_FDIO cannot be retained during FLASH-XIP
 */
#define IO_RETENTION_VBAT      (0x10)  ///< P0_00 ~ P0_03
#define IO_RETENTION_FDIO      (0x08)  ///< P1_00 ~ P1_09
#define IO_RETENTION_DIO2      (0x04)  ///< P1_10 ~ P1_15
#define IO_RETENTION_DIO1_2    (0x02)  ///< P0_08 ~ P0_13
#define IO_RETENTION_DIO1_1    (0x01)  ///< P0_04 ~ P0_07

/* All execpt VBAT and FDIO */
#define IO_RETENTION_MSK    (IO_RETENTION_DIO2 | IO_RETENTION_DIO1_2 | IO_RETENTION_DIO1_1)

typedef enum e_retained_type
{
    BSP_IO_REATAINED_UNUSED = 0x0,
    BSP_IO_REATAINED_INPUT  = 0x6f,
    BSP_IO_REATAINED_INPUT_PULLUP,
    BSP_IO_REATAINED_INPUT_PULLDOWN,
    BSP_IO_REATAINED_OUTPUT_HIGH,
    BSP_IO_REATAINED_OUTPUT_LOW,
    BSP_IO_REATAINED_RESERVED_STATUS = 0xff,
} bsp_io_retained_type_t;

typedef struct st_io_retained
{
    uint16_t pio0[16];
    uint16_t pio1[16];
} bsp_io_retained_t;

extern bsp_io_retained_t * g_retention_gpio;

/*******************************************************************************************************************//**
 * This function keeps the GPIO pin type during sleep.
 * Save the io-state in retention memory before sleep. so that the io-state before sleep is maintained when waking up.
 *
 * @param[in] pin the GPIO pin
 *
 * @return true/false
 **********************************************************************************************************************/
__STATIC_INLINE bool R_BSP_RetainedIoSet (bsp_io_port_pin_t pin)
{
    uint32_t pin_id = (uint8_t) pin & BSP_IO_PIN_BITS;
    uint32_t port   = ((uint16_t) pin) >> BSP_IO_PORT_OFFSET;

    if (port == BSP_IO_PORT_00)
    {
        g_retention_gpio->pio0[pin_id] = BSP_IO_REATAINED_RESERVED_STATUS;
    }
    else if (port == BSP_IO_PORT_01)
    {
        g_retention_gpio->pio1[pin_id] = BSP_IO_REATAINED_RESERVED_STATUS;
    }

    return true;
}

/*******************************************************************************************************************//**
 * This function determines which pin will keeping IO status during sleep.
 * The PIN and its status are saved in retention memory so that the specified io-state is maintained when waking up.
 *
 * @param[in] pin   the GPIO pin
 * @param[in] type  type of the GPIO PIN
 *
 * @return true/false
 **********************************************************************************************************************/
__STATIC_INLINE bool R_BSP_RetainedIoStatusSet (bsp_io_port_pin_t pin, bsp_io_retained_type_t type)
{
    uint32_t pin_id = (uint8_t) pin & BSP_IO_PIN_BITS;
    uint32_t port   = ((uint16_t) pin) >> BSP_IO_PORT_OFFSET;

    if (port == BSP_IO_PORT_00)
    {
        g_retention_gpio->pio0[pin_id] = type;
    }
    else if (port == BSP_IO_PORT_01)
    {
        g_retention_gpio->pio1[pin_id] = type;
    }

    return true;
}

void R_BSP_RetainedIoRecovery(uint16_t clear);

bool R_BSP_RetainedIoExecute();

void R_BSP_RetainedIoClear(void);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
