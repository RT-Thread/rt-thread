/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_io_isolation.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RTM_RETENTION_IO_ADDR                    (dg_configBOOTER_RTM_ADDR + 0x60)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
bsp_io_retained_t * g_retention_gpio = (bsp_io_retained_t *) RTM_RETENTION_IO_ADDR;

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

__STATIC_INLINE uint32_t bsp_check_gpio_retention_domain (bsp_io_port_pin_t pin, uint32_t * domain)
{
    if (pin <= BSP_IO_PORT_00_PIN_03)
    {
        *domain |= IO_RETENTION_VBAT;
    }
    else if ((pin >= BSP_IO_PORT_00_PIN_04) && (pin <= BSP_IO_PORT_00_PIN_07))
    {
        *domain |= IO_RETENTION_DIO1_1;
    }
    else if ((pin >= BSP_IO_PORT_00_PIN_08) && (pin <= BSP_IO_PORT_00_PIN_13))
    {
        *domain |= IO_RETENTION_DIO1_2;
    }
    else if ((pin >= BSP_IO_PORT_01_PIN_00) && (pin <= BSP_IO_PORT_01_PIN_09))
    {
        *domain |= IO_RETENTION_FDIO;
    }
    else if ((pin >= BSP_IO_PORT_01_PIN_10) && (pin <= BSP_IO_PORT_01_PIN_15))
    {
        *domain |= IO_RETENTION_DIO2;
    }

    return true;
}

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
__STATIC_INLINE void bsp_pio_function_set (bsp_io_port_pin_t pin, bsp_io_retained_type_t type)
{
    switch (type)
    {
        case BSP_IO_REATAINED_INPUT:
        {
            R_BSP_PinCfg(pin, GPIO_W_CFG_PERIPHERAL_PIN | GPIO_W_CFG_PORT_DIRECTION_INPUT);
            break;
        }

        case BSP_IO_REATAINED_INPUT_PULLUP:
        {
            R_BSP_PinCfg(pin, GPIO_W_CFG_PERIPHERAL_PIN | GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_PULLUP_ENABLE);
            break;
        }

        case BSP_IO_REATAINED_INPUT_PULLDOWN:
        {
            R_BSP_PinCfg(pin, GPIO_W_CFG_PERIPHERAL_PIN | GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_PULLDOWN_ENABLE);
            break;
        }

        case BSP_IO_REATAINED_OUTPUT_HIGH:
        {
            R_BSP_PinCfg(pin, GPIO_W_CFG_PERIPHERAL_PIN | GPIO_W_CFG_PORT_DIRECTION_OUTPUT);
            R_BSP_PinWrite(pin, BSP_IO_LEVEL_HIGH);
            break;
        }

        case BSP_IO_REATAINED_OUTPUT_LOW:
        {
            R_BSP_PinCfg(pin, GPIO_W_CFG_PERIPHERAL_PIN | GPIO_W_CFG_PORT_DIRECTION_OUTPUT);
            R_BSP_PinWrite(pin, BSP_IO_LEVEL_LOW);
            break;
        }

        default:
        {
            break;
        }
    }
}

static void r_bsp_RetainedIo_config_pin_from_ret (uint32_t pin, uint8_t port)
{
    uint8_t pin_id = (uint8_t) pin & BSP_IO_PIN_BITS;

    if (port == 0)
    {
        R_BSP_PinCfg(pin, (g_retention_gpio->pio0[pin_id] & ~(1U << 15)));
        R_BSP_PinWrite((bsp_io_port_pin_t)pin,
                       (uint32_t)g_retention_gpio->pio0[pin_id] >> 15 ? BSP_IO_LEVEL_HIGH : BSP_IO_LEVEL_LOW);
    }
    else
    {
        R_BSP_PinCfg(pin, (g_retention_gpio->pio1[pin_id] & ~(1U << 15)));
        R_BSP_PinWrite((bsp_io_port_pin_t)pin,
                       (uint32_t)g_retention_gpio->pio1[pin_id] >> 15 ? BSP_IO_LEVEL_HIGH : BSP_IO_LEVEL_LOW);
    }
}

/*******************************************************************************************************************//**
 * This function release setting retain pio and recovery pio status by setting user
 *
 * @param [in] clear clear retention information in retain memory.
 * @return true/false
 **********************************************************************************************************************/
void R_BSP_RetainedIoRecovery (uint16_t clear)
{
    uint32_t pin;
    uint32_t pin_id = 0;

    /* Loop through the PORT0 */
    for (pin = BSP_IO_PORT_00_PIN_00; pin <= BSP_IO_PORT_00_PIN_13; pin++)
    {
        pin_id = (uint8_t) pin & BSP_IO_PIN_BITS;

        if ((g_retention_gpio->pio0[pin_id] >= BSP_IO_REATAINED_INPUT) &&
            (g_retention_gpio->pio0[pin_id] <= BSP_IO_REATAINED_OUTPUT_LOW))
        {
            bsp_pio_function_set((bsp_io_port_pin_t) pin, (bsp_io_retained_type_t) g_retention_gpio->pio0[pin_id]);
        }
        else if (g_retention_gpio->pio0[pin_id] != BSP_IO_REATAINED_RESERVED_STATUS && g_retention_gpio->pio0[pin_id])
        {
            /* Restore the pin mode and state and saved again as retain */
            r_bsp_RetainedIo_config_pin_from_ret(pin, 0);
            R_BSP_RetainedIoSet(pin);
        }
        else
        {
            /* Restore the pin mode and state */
            r_bsp_RetainedIo_config_pin_from_ret(pin, 0);        
        }

        if (clear)
        {
            g_retention_gpio->pio0[pin_id] = BSP_IO_REATAINED_UNUSED;
        }
    }

    /* Loop through the PORT1 */
    for (pin = BSP_IO_PORT_01_PIN_00; pin <= BSP_IO_PORT_01_PIN_15; pin++)
    {
        pin_id = (uint8_t) pin & BSP_IO_PIN_BITS;

        if ((g_retention_gpio->pio1[pin_id] >= BSP_IO_REATAINED_INPUT) &&
            (g_retention_gpio->pio1[pin_id] <= BSP_IO_REATAINED_OUTPUT_LOW))
        {
            bsp_pio_function_set((bsp_io_port_pin_t) pin, (bsp_io_retained_type_t) g_retention_gpio->pio1[pin_id]);
        }
        else if (g_retention_gpio->pio1[pin_id] != BSP_IO_REATAINED_RESERVED_STATUS && g_retention_gpio->pio1[pin_id])
        {
            /* Restore the pin mode and state and saved again as retain */
            r_bsp_RetainedIo_config_pin_from_ret(pin, 1); 
            R_BSP_RetainedIoSet(pin);
        }
        else
        {
            /* Restore the pin mode and state */
            r_bsp_RetainedIo_config_pin_from_ret(pin, 1);
        }

        if (clear)
        {
            g_retention_gpio->pio1[pin_id] = BSP_IO_REATAINED_UNUSED;
        }
    }

    RTC->RTM_CONTROL_REG_b.RTM_CTRL_IO_RETEN_CTRL = 0;
}

/*******************************************************************************************************************//**
 * This function execute to retain GPIO as using hw_gpio_retention_pin_set.
 *
 * @return true/false
 **********************************************************************************************************************/
bool R_BSP_RetainedIoExecute (void)
{
    uint32_t pin;
    uint16_t pin_id;
    uint32_t domain = 0;

    for (pin = BSP_IO_PORT_00_PIN_00; pin <= BSP_IO_PORT_00_PIN_13; pin++)
    {
        pin_id = (uint8_t) pin & BSP_IO_PIN_BITS;

        if (g_retention_gpio->pio0[pin_id] == BSP_IO_REATAINED_RESERVED_STATUS)
        {
            bsp_check_gpio_retention_domain((bsp_io_port_pin_t)pin, &domain);
            g_retention_gpio->pio0[pin_id] = (uint16_t) (BSP_IO_PXX_MODE_REG(BSP_IO_PORT_00, pin_id) | (R_BSP_PinRead((bsp_io_port_pin_t)pin) << 15));
        }
        else if (g_retention_gpio->pio0[pin_id] >= BSP_IO_REATAINED_INPUT && g_retention_gpio->pio0[pin_id] <= BSP_IO_REATAINED_OUTPUT_LOW)
        {
            /* For legacy compatible define */
            bsp_pio_function_set((bsp_io_port_pin_t) pin, (bsp_io_retained_type_t) g_retention_gpio->pio0[pin_id]);
            bsp_check_gpio_retention_domain((bsp_io_port_pin_t) pin, &domain);
        }
        else
        {
            g_retention_gpio->pio0[pin_id] = (uint16_t) (BSP_IO_PXX_MODE_REG(BSP_IO_PORT_00, pin_id) | (R_BSP_PinRead((bsp_io_port_pin_t)pin) << 15));
        }
    }

    for (pin = BSP_IO_PORT_01_PIN_00; pin <= BSP_IO_PORT_01_PIN_15; pin++)
    {
        pin_id = (uint8_t) pin & BSP_IO_PIN_BITS;

        if (g_retention_gpio->pio1[pin_id] == BSP_IO_REATAINED_RESERVED_STATUS)
        {
            bsp_check_gpio_retention_domain((bsp_io_port_pin_t)pin, &domain);
            g_retention_gpio->pio1[pin_id] = (uint16_t) (BSP_IO_PXX_MODE_REG(BSP_IO_PORT_01, pin_id) | (R_BSP_PinRead((bsp_io_port_pin_t)pin) << 15));
        }
        else if (g_retention_gpio->pio1[pin_id] >= BSP_IO_REATAINED_INPUT && g_retention_gpio->pio1[pin_id] <= BSP_IO_REATAINED_OUTPUT_LOW)
        {
            /* For legacy compatible define */
            bsp_pio_function_set((bsp_io_port_pin_t) pin, (bsp_io_retained_type_t) g_retention_gpio->pio1[pin_id]);
            bsp_check_gpio_retention_domain((bsp_io_port_pin_t) pin, &domain);
        }
        else
        {
            g_retention_gpio->pio1[pin_id] = (uint16_t) (BSP_IO_PXX_MODE_REG(BSP_IO_PORT_01, pin_id) | (R_BSP_PinRead((bsp_io_port_pin_t)pin) << 15));
        }
    }

    RTC->RTM_CONTROL_REG_b.RTM_CTRL_IO_RETEN_CTRL = domain & IO_RETENTION_MSK;

    return true;
}

void R_BSP_RetainedIoClear (void)
{
    memset(g_retention_gpio, 0, sizeof(bsp_io_retained_t));
}

/** @} (end addtogroup BSP_MCU) */
