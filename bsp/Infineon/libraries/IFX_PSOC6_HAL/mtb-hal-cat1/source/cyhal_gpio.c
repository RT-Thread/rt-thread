/***************************************************************************//**
* \file cyhal_gpio.c
*
* Description:
* Provides a high level interface for interacting with the Infineon GPIO. This is
* a wrapper around the lower level PDL API.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cyhal_gpio_impl.h"
#include "cyhal_interconnect.h"
#include "cyhal_system.h"
#include "cyhal_hwmgr.h"
#include "cyhal_irq_impl.h"

#if (CYHAL_DRIVER_AVAILABLE_GPIO)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */


/*******************************************************************************
*       Internal
*******************************************************************************/
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
#define _CYHAL_GPIO_DIRECTION_OUTPUT_MASK        (0x07UL)   /**< Mask to disable the input buffer */
#elif defined(COMPONENT_CAT2)
#define _CYHAL_GPIO_DIRECTION_OUTPUT_MASK        (0x08UL)   /**< Mask to disable the input buffer */
#endif

/* Callback array for GPIO interrupts */
static bool _cyhal_gpio_arrays_initialized = false;
CY_NOINIT static cyhal_gpio_callback_data_t* _cyhal_gpio_callbacks[IOSS_GPIO_GPIO_PORT_NR];
#if defined(CY_IP_MXS40IOSS) || defined(CY_IP_MXS40SIOSS) || defined (CY_IP_MXS22IOSS)
#define _CYHAL_GPIO_SOURCE_SIGNAL_COUNT (sizeof(cyhal_pin_map_peri_tr_io_output)/sizeof(cyhal_resource_pin_mapping_t))
CY_NOINIT static cyhal_source_t _cyhal_gpio_source_signals[_CYHAL_GPIO_SOURCE_SIGNAL_COUNT];
#endif

#if defined(CY_DEVICE_PMG1S3)
/* PMG1-S3: Work-around as device does not support any GPIO port specific interrupts. */
#define ioss_interrupts_gpio_0_IRQn     (ioss_interrupt_gpio_IRQn)
#endif

/*******************************************************************************
*       Internal Interrupt Service Routine
*******************************************************************************/

static void _cyhal_gpio_irq_handler(void)
{
    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
#if !defined(COMPONENT_CAT1C)
    uint32_t port = (uint32_t)(irqn - ioss_interrupts_gpio_0_IRQn);
#else
#if defined(CY_DEVICE_TVIIBH4M) || defined(CY_DEVICE_TVIIBH8M)
    /* Port 0-23 and 28-32 (inclusive) are DeepSleep capable. Port 24-27 and 33-34
     * (inclusive) are active mode only. The interrupt numbers are grouped by power
     * domain which means the numbers are non-contiguous - and die specific */
    uint32_t port;
    if(irqn <= ioss_interrupts_gpio_dpslp_23_IRQn)
    {
        port = (uint32_t)(irqn - ioss_interrupts_gpio_dpslp_0_IRQn);
    }
    else if((irqn >= ioss_interrupts_gpio_act_24_IRQn) && (irqn <= ioss_interrupts_gpio_act_27_IRQn))
    {
        port = 24u + (uint32_t)(irqn - ioss_interrupts_gpio_act_24_IRQn);
    }
    else if((irqn >= ioss_interrupts_gpio_dpslp_28_IRQn) && (irqn <= ioss_interrupts_gpio_dpslp_32_IRQn))
    {
        port = 28u + (uint32_t)(irqn - ioss_interrupts_gpio_dpslp_28_IRQn);
    }
#if defined(CY_DEVICE_TVIIBH8M) /* Ports 33 and 34 don't exist on the 4M part */
    else if((irqn >= ioss_interrupts_gpio_act_33_IRQn) && (irqn <= ioss_interrupts_gpio_act_34_IRQn))
    {
        port = 33u + (uint32_t)(irqn - ioss_interrupts_gpio_act_33_IRQn);
    }
#endif
    else
    {
        port = 0u;
        CY_ASSERT(false); /* Unknown port */
    }
#else
    #error "Unknown base die"
#endif
#endif /* other or COMPONENT_CAT1C */
    uint32_t intr_cause = 1 << port;
#if defined(COMPONENT_CAT2)
    if (irqn == ioss_interrupt_gpio_IRQn)
    {
        intr_cause = Cy_GPIO_GetInterruptCause();
    }
#endif

    while(intr_cause != 0)
    {
        uint32_t curr_port = (uint32_t) (31U - __CLZ(intr_cause));
        GPIO_PRT_Type *portAddr = Cy_GPIO_PortToAddr(curr_port);
        cyhal_gpio_callback_data_t* cb_data = _cyhal_gpio_callbacks[curr_port];
        while (NULL != cb_data)
        {
            uint8_t pin = CYHAL_GET_PIN(cb_data->pin);
            /* Each supported architecture much have a way to check the interrupt status of a pin on a port. */
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
            if (Cy_GPIO_GetInterruptStatusMasked(portAddr, pin))
#elif defined(COMPONENT_CAT2)
            if (Cy_GPIO_GetInterruptStatus(portAddr, pin))
#else
    #error "Unsupported architecture"
#endif
            {
                /* Call registered callbacks here */
                cyhal_gpio_event_t event, edge = (cyhal_gpio_event_t)Cy_GPIO_GetInterruptEdge(portAddr, pin);
                switch (edge)
                {
                    case CYHAL_GPIO_IRQ_RISE:
                    case CYHAL_GPIO_IRQ_FALL:
                        event = edge;
                        break;
                    default:
                        event = (Cy_GPIO_Read(portAddr, pin) != 0) ? CYHAL_GPIO_IRQ_RISE : CYHAL_GPIO_IRQ_FALL;
                        break;
                }
                cb_data->callback(cb_data->callback_arg, event);
            }

            cb_data = cb_data->next;
        }
        // Since the HAL has taken over the interrupt, make sure we clear any triggers to avoid an
        // infinite loop.
        for (uint8_t i = 0; i < CY_GPIO_PINS_MAX; i++)
        {
            Cy_GPIO_ClearInterrupt(portAddr, i);
        }
        intr_cause &= ~(1 << curr_port);
    }
}

static uint32_t _cyhal_gpio_convert_drive_mode(cyhal_gpio_drive_mode_t drive_mode, cyhal_gpio_direction_t direction)
{
    uint32_t drvMode;
    switch (drive_mode)
    {
        /* For DRIVE_NONE and DRIVE_ANALOG: Return immediately so drvMode is
         * not modified after switch statement based on direction as direction
         * does not make sense for input only drive modes */
        case CYHAL_GPIO_DRIVE_NONE:
            drvMode = CY_GPIO_DM_HIGHZ;
            return drvMode;
        case CYHAL_GPIO_DRIVE_ANALOG:
            drvMode = CY_GPIO_DM_ANALOG;
            return drvMode;
        case CYHAL_GPIO_DRIVE_PULLUP:
            drvMode = CY_GPIO_DM_PULLUP;
            break;
        case CYHAL_GPIO_DRIVE_PULLDOWN:
            drvMode = CY_GPIO_DM_PULLDOWN;
            break;
        case CYHAL_GPIO_DRIVE_OPENDRAINDRIVESLOW:
            drvMode = CY_GPIO_DM_OD_DRIVESLOW;
            break;
        case CYHAL_GPIO_DRIVE_OPENDRAINDRIVESHIGH:
            drvMode = CY_GPIO_DM_OD_DRIVESHIGH;
            break;
        case CYHAL_GPIO_DRIVE_STRONG:
            drvMode = CY_GPIO_DM_STRONG;
            break;
        case CYHAL_GPIO_DRIVE_PULLUPDOWN:
            drvMode = CY_GPIO_DM_PULLUP_DOWN;
            break;
        case CYHAL_GPIO_DRIVE_PULL_NONE:
            if ((direction == CYHAL_GPIO_DIR_OUTPUT) || (direction == CYHAL_GPIO_DIR_BIDIRECTIONAL))
            {
                drvMode = CY_GPIO_DM_STRONG;
            }
            else
            {
                drvMode = CY_GPIO_DM_HIGHZ;
            }
            break;
        default:
            CY_ASSERT(false);
            drvMode = CY_GPIO_DM_HIGHZ;
    }

    if (direction == CYHAL_GPIO_DIR_OUTPUT)
    {
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
        drvMode &= _CYHAL_GPIO_DIRECTION_OUTPUT_MASK;
#elif defined(COMPONENT_CAT2)
        drvMode |= _CYHAL_GPIO_DIRECTION_OUTPUT_MASK;
#endif
    }
    return drvMode;
}

/*******************************************************************************
*       HAL Implementation
*******************************************************************************/

cy_rslt_t cyhal_gpio_init(cyhal_gpio_t pin, cyhal_gpio_direction_t direction, cyhal_gpio_drive_mode_t drive_mode, bool init_val)
{
    if (!_cyhal_gpio_arrays_initialized)
    {
        for (uint8_t i = 0; i < IOSS_GPIO_GPIO_PORT_NR; i++)
        {
            _cyhal_gpio_callbacks[i] = NULL;
        }
#if defined(CY_IP_MXS40IOSS) || defined(CY_IP_MXS40SIOSS) || defined (CY_IP_MXS22IOSS)
        for (uint8_t i = 0; i < _CYHAL_GPIO_SOURCE_SIGNAL_COUNT; i++)
        {
            _cyhal_gpio_source_signals[i] = CYHAL_TRIGGER_CPUSS_ZERO;
        }
#endif
        _cyhal_gpio_arrays_initialized = true;
    }

    /* Mbed creates GPIOs for pins that are dedicated to other peripherals in some cases. */
#ifndef __MBED__
    cyhal_resource_inst_t pinRsc = _cyhal_utils_get_gpio_resource(pin);
    cy_rslt_t status = cyhal_hwmgr_reserve(&pinRsc);
#else
    cy_rslt_t status = CY_RSLT_SUCCESS;
#endif

    if (status == CY_RSLT_SUCCESS)
    {
        uint32_t pdl_drive_mode = _cyhal_gpio_convert_drive_mode(drive_mode, direction);
        Cy_GPIO_Pin_FastInit(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin), pdl_drive_mode, init_val, HSIOM_SEL_GPIO);
    }

    return status;
}

void cyhal_gpio_free(cyhal_gpio_t pin)
{
    if(_cyhal_gpio_arrays_initialized)
    {
        if (pin != CYHAL_NC_PIN_VALUE)
        {
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
            Cy_GPIO_SetInterruptMask(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin), 0);
#elif defined(COMPONENT_CAT2)
            Cy_GPIO_SetInterruptEdge(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin), CY_GPIO_INTR_DISABLE);
#endif
            cyhal_gpio_register_callback(pin, NULL);

            (void)cyhal_gpio_disable_output(pin);
            #if defined(CY_IP_MXS40IOSS) || defined(CY_IP_MXS40SIOSS)
            for(uint8_t i = 0; i < (uint8_t)(sizeof(cyhal_pin_map_peri_tr_io_output)/sizeof(cyhal_resource_pin_mapping_t)); i++)
            {
                cyhal_resource_pin_mapping_t mapping = cyhal_pin_map_peri_tr_io_output[i];
                if(mapping.pin == pin)
                {
                    if (CYHAL_TRIGGER_CPUSS_ZERO != _cyhal_gpio_source_signals[i])
                    {
                        (void)cyhal_gpio_disconnect_digital(pin, _cyhal_gpio_source_signals[i]);
                    }
                }
            }
            #endif

            Cy_GPIO_Pin_FastInit(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin), CY_GPIO_DM_ANALOG, 0UL, HSIOM_SEL_GPIO);

            /* Do not attempt to free the resource we don't reserve in mbed. */
#ifndef __MBED__
            cyhal_resource_inst_t pinRsc = _cyhal_utils_get_gpio_resource(pin);
            cyhal_hwmgr_free(&pinRsc);
#endif
        }
    }
    else
    {
        CY_ASSERT(false); /* Should not be freeing if we never initialized anything */
    }
}

cy_rslt_t cyhal_gpio_configure(cyhal_gpio_t pin, cyhal_gpio_direction_t direction, cyhal_gpio_drive_mode_t drive_mode)
{
    uint32_t pdldrive_mode = _cyhal_gpio_convert_drive_mode(drive_mode, direction);
    Cy_GPIO_SetDrivemode(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin), pdldrive_mode);

    return CY_RSLT_SUCCESS;
}

void cyhal_gpio_register_callback(cyhal_gpio_t pin, cyhal_gpio_callback_data_t* callback_data)
{
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();

    // Remove if already registered;
    cyhal_gpio_callback_data_t** ptr = &(_cyhal_gpio_callbacks[CYHAL_GET_PORT(pin)]);
    while (NULL != *ptr)
    {
        if ((*ptr)->pin == pin)
        {
            *ptr = (*ptr)->next;
            break;
        }
        ptr = &((*ptr)->next);
    }
    // Add if requested
    if (NULL != callback_data)
    {
        CY_ASSERT(NULL != callback_data->callback);
        callback_data->pin = pin;
        callback_data->next = _cyhal_gpio_callbacks[CYHAL_GET_PORT(pin)];
        _cyhal_gpio_callbacks[CYHAL_GET_PORT(pin)] = callback_data;
    }

    cyhal_system_critical_section_exit(savedIntrStatus);
}

void cyhal_gpio_enable_event(cyhal_gpio_t pin, cyhal_gpio_event_t event, uint8_t intr_priority, bool enable)
{
#if (_CYHAL_IRQ_MUXING)
    /* We may be in a critical section. Only clear the interrupt status if there isn't a pending interrupt */
    if ((Cy_GPIO_GetInterruptStatus(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin)) == 0) || enable)
#endif
    {
        Cy_GPIO_ClearInterrupt(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin));
    }
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
    Cy_GPIO_SetInterruptEdge(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin), (uint32_t)event);
    Cy_GPIO_SetInterruptMask(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin), (uint32_t)enable);
#if !defined(COMPONENT_CAT1C)
    _cyhal_system_irq_t irqn = (_cyhal_system_irq_t)(ioss_interrupts_gpio_0_IRQn + CYHAL_GET_PORT(pin));
#else
    uint32_t port = CYHAL_GET_PORT(pin);
    /* Port 0-23 and 28-32 (inclusive) are DeepSleep capable. Port 24-27 and 33-34
     * (inclusive) are active mode only. The interrupt numbers are grouped by power
     * domain which means the numbers are non-contiguous - and die specific */
    _cyhal_system_irq_t irqn;
    if(port <= 23u)
    {
        irqn = (_cyhal_system_irq_t)(ioss_interrupts_gpio_dpslp_0_IRQn + port);
    }
    else if(port <= 27u)
    {
        irqn = (_cyhal_system_irq_t)(ioss_interrupts_gpio_act_24_IRQn + (port - 24u));
    }
    else if(port <= 32u)
    {
        irqn = (_cyhal_system_irq_t)(ioss_interrupts_gpio_dpslp_28_IRQn + (port - 28u));
    }
#if defined(CY_DEVICE_TVIIBH8M) /* Ports 33 and 34 don't exist on the 4M part */
    else if(port <= 34u)
    {
        irqn = (_cyhal_system_irq_t)(ioss_interrupts_gpio_act_33_IRQn + (port - 33u));
    }
#endif
    else
    {
        irqn = (_cyhal_system_irq_t)0u;
        CY_ASSERT(false); /* Unknown port */
    }
#endif /* other or COMPONENT_CAT1C */
#elif defined(COMPONENT_CAT2)
    uint32_t intr_val = enable ? (uint32_t)event : CY_GPIO_INTR_DISABLE;
    Cy_GPIO_SetInterruptEdge(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin), intr_val);
    _cyhal_system_irq_t irqn = ((ioss_interrupts_gpio_0_IRQn + CYHAL_GET_PORT(pin)) < ioss_interrupt_gpio_IRQn)
                    ? (_cyhal_system_irq_t)(ioss_interrupts_gpio_0_IRQn + CYHAL_GET_PORT(pin))
                    : (_cyhal_system_irq_t)(ioss_interrupt_gpio_IRQn);
#endif
    /* Only enable if it's not already enabled */
    if (false == _cyhal_irq_is_enabled(irqn))
    {
        _cyhal_irq_register(irqn, intr_priority, _cyhal_gpio_irq_handler);
        _cyhal_irq_enable(irqn);
    }
    else
    {
        _cyhal_irq_set_priority(irqn, intr_priority);
    }
}

#if defined(CY_IP_MXS40IOSS) || defined(CY_IP_MXS40SIOSS) || defined (CY_IP_MXS22IOSS)
cy_rslt_t cyhal_gpio_connect_digital(cyhal_gpio_t pin, cyhal_source_t source)
{
    // Search through cyhal_pin_map_peri_tr_io_output to determine if a trigger
    // can be routed to it. (Note: tr_io_output refers to trigger mux output,
    // not peripheral output. A trigger mux output is routed to a peripheral
    // input.)
    for(uint8_t i = 0; i < (uint8_t)(sizeof(cyhal_pin_map_peri_tr_io_output)/sizeof(cyhal_resource_pin_mapping_t)); i++)
    {
        cyhal_resource_pin_mapping_t mapping = cyhal_pin_map_peri_tr_io_output[i];
        if(mapping.pin == pin)
        {
            Cy_GPIO_SetHSIOM(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin), mapping.hsiom);

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
            cyhal_dest_t dest = (cyhal_dest_t)(CYHAL_TRIGGER_PERI_TR_IO_OUTPUT0 + mapping.channel_num);
#elif defined(COMPONENT_CAT1B)
            cyhal_dest_t dest = (cyhal_dest_t)(CYHAL_TRIGGER_IOSS_PERI_TR_IO_OUTPUT_OUT0 + mapping.channel_num);
#elif defined(COMPONENT_CAT1D)
            cyhal_dest_t dest;
            if(0u == mapping.block_num)
            {
                dest = CYHAL_TRIGGER_IOSS_PERI0_TR_IO_OUTPUT_OUT0;
            }
            else
            {
                CY_ASSERT(1u == mapping.block_num);
                dest = CYHAL_TRIGGER_IOSS_PERI1_TR_IO_OUTPUT_OUT0;
            }

            dest = (cyhal_dest_t)(dest + mapping.channel_num);
#endif

            cy_rslt_t rslt = _cyhal_connect_signal(source, dest);
            if (CY_RSLT_SUCCESS == rslt)
            {
                _cyhal_gpio_source_signals[i] = source;
            }
            return rslt;
        }
    }

    return CYHAL_GPIO_RSLT_ERR_NO_INPUT_SIGNAL;
}

cy_rslt_t cyhal_gpio_enable_output(cyhal_gpio_t pin, cyhal_signal_type_t type, cyhal_source_t *source)
{
    // Search through cyhal_pin_map_peri_tr_io_input to determine if pin can be
    // used to drive a trigger line. (Note: tr_io_input refers to trigger mux
    // input, not peripheral input. A peripheral output is routed to a trigger
    // mux input.)
    for(uint8_t i = 0; i < (uint8_t)(sizeof(cyhal_pin_map_peri_tr_io_input)/sizeof(cyhal_resource_pin_mapping_t)); i++)
    {
        cyhal_resource_pin_mapping_t mapping = cyhal_pin_map_peri_tr_io_input[i];
        if(mapping.pin == pin)
        {
            Cy_GPIO_SetHSIOM(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin), mapping.hsiom);

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
            cyhal_internal_source_t int_src = (cyhal_internal_source_t)(_CYHAL_TRIGGER_PERI_TR_IO_INPUT0 + mapping.channel_num);
#elif defined(COMPONENT_CAT1B)
            cyhal_internal_source_t int_src = (cyhal_internal_source_t)(_CYHAL_TRIGGER_IOSS_PERI_TR_IO_INPUT_IN0 + mapping.channel_num);
#elif defined(COMPONENT_CAT1D)
            cyhal_internal_source_t int_src;
            if(0u == mapping.block_num)
            {
                int_src = _CYHAL_TRIGGER_IOSS_PERI0_TR_IO_INPUT_IN0;
            }
            else
            {
                CY_ASSERT(1u == mapping.block_num);
                int_src = _CYHAL_TRIGGER_IOSS_PERI1_TR_IO_INPUT_IN0;
            }

            int_src = (cyhal_internal_source_t)(int_src + mapping.channel_num);
#endif
            *source = (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(int_src, type);

            return CY_RSLT_SUCCESS;
        }
    }

    return CYHAL_GPIO_RSLT_ERR_NO_OUTPUT_SIGNAL;
}

cy_rslt_t cyhal_gpio_disconnect_digital(cyhal_gpio_t pin, cyhal_source_t source)
{
    for(uint8_t i = 0; i < (uint8_t)(sizeof(cyhal_pin_map_peri_tr_io_output)/sizeof(cyhal_resource_pin_mapping_t)); i++)
    {
        cyhal_resource_pin_mapping_t mapping = cyhal_pin_map_peri_tr_io_output[i];
        if(mapping.pin == pin)
        {
            Cy_GPIO_SetHSIOM(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin), HSIOM_SEL_GPIO);

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
            cyhal_dest_t dest = (cyhal_dest_t)(CYHAL_TRIGGER_PERI_TR_IO_OUTPUT0 + mapping.channel_num);
#elif defined(COMPONENT_CAT1B)
            cyhal_dest_t dest = (cyhal_dest_t)(CYHAL_TRIGGER_IOSS_PERI_TR_IO_OUTPUT_OUT0 + mapping.channel_num);
#elif defined(COMPONENT_CAT1D)
            cyhal_dest_t dest;
            if(0u == mapping.block_num)
            {
                dest = CYHAL_TRIGGER_IOSS_PERI0_TR_IO_OUTPUT_OUT0;
            }
            else
            {
                CY_ASSERT(1u == mapping.block_num);
                dest = CYHAL_TRIGGER_IOSS_PERI1_TR_IO_OUTPUT_OUT0;
            }

            dest = (cyhal_dest_t)(dest + mapping.channel_num);
#endif

            cy_rslt_t rslt = _cyhal_disconnect_signal(source, dest);
            if (CY_RSLT_SUCCESS == rslt)
            {
                _cyhal_gpio_source_signals[i] = CYHAL_TRIGGER_CPUSS_ZERO;
            }
            return rslt;
        }
    }

    return CYHAL_GPIO_RSLT_ERR_NO_INPUT_SIGNAL;
}

cy_rslt_t cyhal_gpio_disable_output(cyhal_gpio_t pin)
{
    for(uint8_t i = 0; i < (uint8_t)(sizeof(cyhal_pin_map_peri_tr_io_input)/sizeof(cyhal_resource_pin_mapping_t)); i++)
    {
        cyhal_resource_pin_mapping_t mapping = cyhal_pin_map_peri_tr_io_input[i];
        if(mapping.pin == pin)
        {
            Cy_GPIO_SetHSIOM(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin), HSIOM_SEL_GPIO);

            return CY_RSLT_SUCCESS;
        }
    }

    return CYHAL_GPIO_RSLT_ERR_NO_OUTPUT_SIGNAL;
}
#elif defined(CY_IP_M0S8IOSS)
// M0S8 devices do not have gpio triggers
cy_rslt_t cyhal_gpio_connect_digital(cyhal_gpio_t pin, cyhal_source_t source)
{
    CY_UNUSED_PARAMETER(pin);
    CY_UNUSED_PARAMETER(source);
    return CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;
}

cy_rslt_t cyhal_gpio_enable_output(cyhal_gpio_t pin, cyhal_signal_type_t type, cyhal_source_t *source)
{
    CY_UNUSED_PARAMETER(pin);
    CY_UNUSED_PARAMETER(source);
    CY_UNUSED_PARAMETER(type);
    return CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;
}

cy_rslt_t cyhal_gpio_disconnect_digital(cyhal_gpio_t pin, cyhal_source_t source)
{
    CY_UNUSED_PARAMETER(pin);
    CY_UNUSED_PARAMETER(source);
    return CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;
}

cy_rslt_t cyhal_gpio_disable_output(cyhal_gpio_t pin)
{
    CY_UNUSED_PARAMETER(pin);
    return CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;
}
#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* CYHAL_DRIVER_AVAILABLE_GPIO */
