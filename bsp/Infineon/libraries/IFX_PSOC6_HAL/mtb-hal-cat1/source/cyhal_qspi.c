/***************************************************************************//**
* \file cyhal_qspi.c
*
* Description:
* Provides a high level interface for interacting with the Infineon QSPI (SMIF).
* This is a wrapper around the lower level PDL API.
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

/**
 * \addtogroup group_hal_impl_qspi QSPI (Quad Serial Peripheral Interface)
 * \ingroup group_hal_impl
 * \{
 * \section section_hal_impl_qspi_init_cfg Configurator-generated features limitations
 * List of SMIF personality items, which are currently not supported in QSPI HAL driver on CAT1A/CAT1B devices:
 *  - XIP (eXecute In Place) mode
 *  - Memory Mode Alignment Error interrupt
 *  - RX Data FIFO Underflow interrupt
 *  - TX Command FIFO Overflow
 *  - TX Data FIFO Overflow interrupt
 *  - RX FIFO Level Trigger interrupt
 *  - TX FIFO Level Trigger interrupt
 *  - RX DMA Trigger
 *  - TX DMA Trigger
 * Note: For CAT1D devices, the QSPI SCLK connection is provided with a dedicated pin so NC should be passed for the SCLK pin when calling cyhal_qspi_init.
 *
 * \section section_hal_impl_qspi_init_clock_20829 20829 device clock limitations
 * Due to specifics of 20829 device clock tree, where multiple peripheral devices are clocked by same HF1, as
 * QSPI HW Block, QSPI HAL driver is not allowed to manipulate frequency by itself. In this case user should allocate
 * and configure their own HF1 clock and pass it as `cyhal_clock_t *clk` parameter into cyhal_qspi_init function.
 *
 * \section section_hal_impl_clock_freq Interface clock frequency
 * Starting MXSMIF HW block version 2 (checked with `CY_IP_MXSMIF_VERSION` define), QSPI interface clock frequency is
 * twice lower than configured source HF clock, so if QSPI source HF clock is configured, for instance, for 50 MHz, connected
 * memory will be accessed on 25 MHz clock. Interface clock frequency of MXSMIF block with version 1 corresponds
 * to frequency of source HF clock.
 *
 * \} group_hal_impl_qspi
 */

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "cy_smif.h"
#include "cyhal_utils.h"
#include "cyhal_irq_impl.h"
#include "cyhal_qspi.h"
#include "cyhal_hwmgr.h"
#include "cyhal_gpio.h"
#include "cyhal_interconnect.h"
#include "cyhal_system_impl.h"
#include "cyhal_syspm.h"
#include "cyhal_clock.h"

#if (CYHAL_DRIVER_AVAILABLE_QSPI)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
*       Internal
*******************************************************************************/
/* in microseconds, timeout for all blocking functions */
#define _CYHAL_QSPI_TIMEOUT_10_MS (10000UL)

#define _CYHAL_QSPI_MAX_DATA_PINS 8

#define _CYHAL_QSPI_MAX_RX_COUNT (65536UL)
#define _CYHAL_QSPI_DESELECT_DELAY (7UL)

#if (defined(SMIF_CHIP_TOP_DATA8_PRESENT) && (SMIF_CHIP_TOP_DATA8_PRESENT))   || \
    (defined(SMIF0_CHIP_TOP_DATA8_PRESENT) && (SMIF0_CHIP_TOP_DATA8_PRESENT))
    #define _CYHAL_QSPI_DATA8_PRESENT   1
#else
    #define _CYHAL_QSPI_DATA8_PRESENT   0
#endif
#if (SMIF_CHIP_TOP_SPI_SEL_NR > 1)
    #define _CYHAL_QSPI_SEL1   1
#else
    #define _CYHAL_QSPI_SEL1   0
#endif
#if (SMIF_CHIP_TOP_SPI_SEL_NR > 2)
    #define _CYHAL_QSPI_SEL2   1
#else
    #define _CYHAL_QSPI_SEL2   0
#endif
#if (SMIF_CHIP_TOP_SPI_SEL_NR > 3)
    #define _CYHAL_QSPI_SEL3   1
#else
    #define _CYHAL_QSPI_SEL3   0
#endif

static cyhal_qspi_t *_cyhal_qspi_config_structs[CY_IP_MXSMIF_INSTANCES];

/* List of available QSPI instances */

#if (CY_IP_MXSMIF_VERSION >= 4)
static SMIF_Type * const _cyhal_qspi_base_addresses[SMIF_SMIF_NR] =
{
#ifdef SMIF0_CORE0
    SMIF0_CORE0,
#endif /* ifdef SMIF0_CORE0   */
#ifdef SMIF0_CORE1
    SMIF0_CORE1,
#endif /* ifdef SMIF0_CORE1 */
};
#else
static SMIF_Type *const _cyhal_qspi_base_addresses[CY_IP_MXSMIF_INSTANCES] =
{
#ifdef SMIF0
    SMIF0,
#endif /* ifdef SMIF0 */
};
#endif

/* List of available QSPI interrupt sources */
#if (CY_IP_MXSMIF_VERSION >= 4)
static const _cyhal_system_irq_t _cyhal_qspi_irq_n[SMIF_SMIF_NR] =
{
#ifdef SMIF0_CORE0
    smif_0_smif0_interrupt_IRQn,
#endif /* ifdef SMIF0_CORE0 */

#ifdef SMIF0_CORE1
    smif_0_smif1_interrupt_IRQn,
#endif /* ifdef SMIF0_CORE1 */
};
#else
static const _cyhal_system_irq_t _cyhal_qspi_irq_n[CY_IP_MXSMIF_INSTANCES] =
{
#ifdef SMIF0
#if (CY_IP_MXSMIF_VERSION >= 3)
    smif_interrupt_normal_IRQn,
#elif (CY_IP_MXSMIF_VERSION == 2)
    smif_0_interrupt_IRQn,
#else
    smif_interrupt_IRQn,
#endif
#endif /* ifdef SMIF0 */
};
#endif

static inline uint8_t _cyhal_qspi_get_block_from_irqn(_cyhal_system_irq_t irqn)
{
    for(uint8_t i = 0; i < (sizeof(_cyhal_qspi_irq_n)/sizeof(_cyhal_qspi_irq_n[0])) ;i++ )
    {
        if (_cyhal_qspi_irq_n[i] == irqn)
        {
            return i;
        }
    }
    CY_ASSERT(false); // Should never be called with a non-SMIF IRQn
    return 0;
}

static cyhal_qspi_t *_cyhal_qspi_get_irq_obj(void)
{
    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
    uint8_t block = _cyhal_qspi_get_block_from_irqn(irqn);
    return _cyhal_qspi_config_structs[block];
}

static void _cyhal_qspi_set_pins_frozen(cyhal_qspi_t* obj, bool freeze)
{
    GPIO_PRT_Type* port;
    uint8_t pin;
    cyhal_gpio_t gpio;
    for(size_t i = 0; i < _CYHAL_QSPI_MAX_DATA_PINS; ++i)
    {
        gpio = obj->pin_io[i];
        if(NC != gpio)
        {
            port = CYHAL_GET_PORTADDR(gpio);
            pin = (uint8_t)CYHAL_GET_PIN(gpio);
            if(freeze)
            {
                obj->saved_io_hsiom[i] = Cy_GPIO_GetHSIOM(port, pin);
                Cy_GPIO_Clr(port, pin);
                Cy_GPIO_SetHSIOM(port, pin, HSIOM_SEL_GPIO);
            }
            else
            {
                Cy_GPIO_SetHSIOM(port, pin, obj->saved_io_hsiom[i]);
            }
        }
    }

    gpio = obj->pin_sclk;
    if(NC != gpio)
    {
        port = CYHAL_GET_PORTADDR(gpio);
        pin = (uint8_t)CYHAL_GET_PIN(gpio);
        if(freeze)
        {
            obj->saved_sclk_hsiom = Cy_GPIO_GetHSIOM(port, pin);
            Cy_GPIO_Clr(port, pin);
            Cy_GPIO_SetHSIOM(port, pin, HSIOM_SEL_GPIO);
        }
        else
        {
            Cy_GPIO_SetHSIOM(port, pin, obj->saved_sclk_hsiom);
        }
    }

    for(size_t i = 0; i < SMIF_CHIP_TOP_SPI_SEL_NR; ++i)
    {
        gpio = obj->pin_ssel[i];
        if(NC != gpio)
        {
            port = CYHAL_GET_PORTADDR(gpio);
            pin = (uint8_t)CYHAL_GET_PIN(gpio);
            if(freeze)
            {
                obj->saved_ssel_hsiom[i] = Cy_GPIO_GetHSIOM(port, pin);
                Cy_GPIO_Set(port, pin); // The SMIF IP requires SSEL to be active low
                Cy_GPIO_SetHSIOM(port, pin, HSIOM_SEL_GPIO);
            }
            else
            {
                Cy_GPIO_SetHSIOM(port, pin, obj->saved_ssel_hsiom[i]);
            }
        }
    }
}

static bool _cyhal_qspi_pm_callback(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void* callback_arg)
{
    CY_UNUSED_PARAMETER(state);
    cyhal_qspi_t *obj = (cyhal_qspi_t *)callback_arg;
    bool allow = true;
    switch(mode)
    {
        case CYHAL_SYSPM_CHECK_READY:
            allow &= obj->context.txBufferCounter == 0;
            allow &= obj->context.rxBufferCounter == 0;
            allow &= Cy_SMIF_GetRxFifoStatus(obj->base) == 0;
            allow &= Cy_SMIF_GetTxFifoStatus(obj->base) == 0;
            if (allow)
            {
                obj->pm_transition_pending = true;
            }
            break;
        case CYHAL_SYSPM_BEFORE_TRANSITION:
            _cyhal_qspi_set_pins_frozen(obj, true);
            break;
        case CYHAL_SYSPM_AFTER_TRANSITION:
            _cyhal_qspi_set_pins_frozen(obj, false);
            obj->pm_transition_pending = false;
            break;
        case CYHAL_SYSPM_CHECK_FAIL:
            obj->pm_transition_pending = false;
            break;
        default:
            CY_ASSERT(false);
            break;
    }
    return allow;
}

/*******************************************************************************
*       Dispatcher Interrupt Service Routine
*******************************************************************************/

/* The PDL can deassert the IRQ status during Cy_SMIF_Interrupt which prevents _cyhal_qspi_get_irq_obj()
 * from working properly in _cyhal_qspi_cb_wrapper on devices with muxed IRQs, because they can't tell
 * at that point which system IRQ caused the CPU IRQ. So we need to save this value at the beginning of the
 * IRQ handler when we are able to determine what it is */
static volatile cyhal_qspi_t* _cyhal_qspi_irq_obj = NULL;

static void _cyhal_qspi_cb_wrapper(uint32_t event)
{
    cyhal_qspi_event_t hal_event = CYHAL_QSPI_EVENT_NONE;
    if (event == CY_SMIF_SEND_CMPLT)
        hal_event = CYHAL_QSPI_IRQ_TRANSMIT_DONE;
    else if (event == CY_SMIF_REC_CMPLT)
        hal_event = CYHAL_QSPI_IRQ_RECEIVE_DONE;

    cyhal_qspi_t *obj = (cyhal_qspi_t *)_cyhal_qspi_irq_obj;

    if ((obj->irq_cause & (uint32_t)hal_event) > 0) // Make sure a user requested event is set before calling
    {
        cyhal_qspi_event_callback_t callback = (cyhal_qspi_event_callback_t) obj->callback_data.callback;
        callback(obj->callback_data.callback_arg, hal_event);
    }
}

/*******************************************************************************
*       (Internal) Interrupt Service Routines
*******************************************************************************/

/* Interrupt call, needed for SMIF Async operations */
static void _cyhal_qspi_irq_handler(void)
{
    /* Save the old value and store it aftewards in case we get into a nested IRQ situation */
    /* Safe to cast away volatile because we don't expect this pointer to be changed while we're in here, they
     * just might change where the original pointer points */
    cyhal_qspi_t* old_irq_obj = (cyhal_qspi_t*)_cyhal_qspi_irq_obj;
    _cyhal_qspi_irq_obj = (cyhal_qspi_t*) _cyhal_qspi_get_irq_obj();
    cyhal_qspi_t* obj = (cyhal_qspi_t*)_cyhal_qspi_irq_obj;

    Cy_SMIF_Interrupt(obj->base, &(obj->context));

    _cyhal_qspi_irq_obj = old_irq_obj;
}

/*******************************************************************************
*       (Internal) QSPI Pin Related Functions
*******************************************************************************/

/* Check if pin valid as resource and reserve it */
static inline cy_rslt_t _cyhal_qspi_check_pin_and_reserve(const cyhal_resource_pin_mapping_t *mapping, uint8_t drive_mode)
{
    // Mbed calls qspi_init multiple times without calling qspi_free to update the QSPI frequency/mode.
    // As a result, we can't worry about resource reservation if running through mbed.
#ifndef __MBED__
    cy_rslt_t result = _cyhal_utils_reserve_and_connect(mapping, drive_mode);
#else
    cy_rslt_t result = cyhal_connect_pin(mapping, drive_mode);
#endif

    return result;
}

/*******************************************************************************
*       (Internal) QSPI Config Related Functions
*******************************************************************************/

/* Translates HAL bus width to PDL bus width */
static cy_en_smif_txfr_width_t _cyhal_qspi_convert_bus_width(cyhal_qspi_bus_width_t bus_width)
{
    cy_en_smif_txfr_width_t cyhal_bus_width;

    switch (bus_width)
    {
        case CYHAL_QSPI_CFG_BUS_SINGLE:
            cyhal_bus_width = CY_SMIF_WIDTH_SINGLE;
            break;
        case CYHAL_QSPI_CFG_BUS_DUAL:
            cyhal_bus_width = CY_SMIF_WIDTH_DUAL;
            break;
        case CYHAL_QSPI_CFG_BUS_QUAD:
            cyhal_bus_width = CY_SMIF_WIDTH_QUAD;
            break;
        case CYHAL_QSPI_CFG_BUS_OCTAL:
            cyhal_bus_width = CY_SMIF_WIDTH_OCTAL;
            break;
        default:
            cyhal_bus_width = CY_SMIF_WIDTH_SINGLE;
    }

    return cyhal_bus_width;
}

static cy_rslt_t _cyhal_qspi_check_command_struct(const cyhal_qspi_command_t *qspi_command)
{
    #if (CY_IP_MXSMIF_VERSION < 3)
    if (((!qspi_command->instruction.disabled) && (qspi_command->instruction.data_rate == CYHAL_QSPI_DATARATE_DDR)) ||
        ((!qspi_command->address.disabled) && (qspi_command->address.data_rate == CYHAL_QSPI_DATARATE_DDR)) ||
        ((!qspi_command->mode_bits.disabled) && (qspi_command->mode_bits.data_rate == CYHAL_QSPI_DATARATE_DDR)) ||
        ((qspi_command->dummy_cycles.dummy_count != 0) && (qspi_command->dummy_cycles.data_rate == CYHAL_QSPI_DATARATE_DDR)) ||
        (qspi_command->data.data_rate == CYHAL_QSPI_DATARATE_DDR))
    {
        /* DDR datarate is not supported by used SMIF IP block */
        return CYHAL_QSPI_RSLT_ERR_DATARATE;
    }
    if (qspi_command->instruction.two_byte_cmd)
    {
        /* Two byte instuction is not supported on current SMIF IP block */
        return CYHAL_QSPI_RSLT_ERR_INSTRUCTION;
    }
    if ((qspi_command->dummy_cycles.dummy_count != 0) && (qspi_command->dummy_cycles.bus_width != CYHAL_QSPI_CFG_BUS_SINGLE))
    {
        /* Bus width parameter for dummy cycles can only be 'single' for current version of SMIF IP block */
        return CYHAL_QSPI_RSLT_ERR_DUMMY_CYCLES;
    }
    #else /* CY_IP_MXSMIF_VERSION < 3 or other */
    CY_UNUSED_PARAMETER(qspi_command);
    #endif /* CY_IP_MXSMIF_VERSION < 3 or other */
    return CY_RSLT_SUCCESS;
}

static void _cyhal_qspi_uint32_to_byte_array(uint32_t value, uint8_t *byteArray, uint32_t startPos, uint32_t size)
{
    do
    {
        size--;
        byteArray[size + startPos] = (uint8_t)(value & 0xFF);
        value >>= 0x08;
    } while (size > 0);
}

/* cyhal_qspi_size_t to number bytes */
static inline uint32_t _cyhal_qspi_get_size(cyhal_qspi_size_t hal_size)
{
    return ((uint32_t)hal_size >> 3); /* convert bits to bytes */
}

/* Sends QSPI command with certain set of data */
static cy_rslt_t _cyhal_qspi_command_transfer(cyhal_qspi_t *obj, const cyhal_qspi_command_t *command,
    uint32_t addr, bool endOfTransfer)
{
    /* max address size is 4 bytes and max mode bits size is 4 bytes */
    uint8_t cmd_param[8] = {0};
    uint32_t start_pos = 0;
    uint32_t addr_size = 0;
    uint32_t mode_bits_size = 0;
    cy_en_smif_txfr_width_t bus_width = CY_SMIF_WIDTH_SINGLE;
    #if (CY_IP_MXSMIF_VERSION >= 3)
    cy_en_smif_data_rate_t data_rate = CY_SMIF_SDR;
    #endif /* CY_IP_MXSMIF_VERSION >= 3 */

    cy_rslt_t result = _cyhal_qspi_check_command_struct(command);

    if (CY_RSLT_SUCCESS == result)
    {
        /* Does not support different bus_width for address and mode bits.
        * bus_width is selected based on what (address or mode bits) is enabled.
        * If both are enabled, bus_width of mode bits is selected
        * It is either possible to support 1 byte mode bits with different bus_width
        * by sending the mode byte as command as done in Cy_SMIF_Memslot_CmdRead()
        * in cyhal_smif_memslot.c or support multiple bytes of mode bits with same bus_width
        * as address by passing the mode bytes as cmd_param to Cy_SMIF_TransmitCommand().
        * Second approach is implemented here. This restriction is because of the way
        * PDL API is implemented.
        */

        if (!command->address.disabled && !command->mode_bits.disabled)
        {
            if (command->address.bus_width != command->mode_bits.bus_width)
            {
                result = CYHAL_QSPI_RSLT_ERR_BUS_WIDTH;
            }
            #if (CY_IP_MXSMIF_VERSION >= 3)
            else if (command->address.data_rate != command->mode_bits.data_rate)
            {
                result = CYHAL_QSPI_RSLT_ERR_DATARATE;
            }
            #endif /* CY_IP_MXSMIF_VERSION >= 3 */
        }

        if (CY_RSLT_SUCCESS == result)
        {
            if (!command->address.disabled)
            {
                addr_size = _cyhal_qspi_get_size(command->address.size);
                _cyhal_qspi_uint32_to_byte_array(addr, cmd_param, start_pos, addr_size);
                start_pos += addr_size;
                bus_width = _cyhal_qspi_convert_bus_width(command->address.bus_width);
                #if (CY_IP_MXSMIF_VERSION >= 3)
                data_rate = (cy_en_smif_data_rate_t)command->address.data_rate;
                #endif /* CY_IP_MXSMIF_VERSION >= 3 */
            }

            if (!command->mode_bits.disabled)
            {
                mode_bits_size = _cyhal_qspi_get_size(command->mode_bits.size);
                _cyhal_qspi_uint32_to_byte_array(command->mode_bits.value, cmd_param, start_pos, mode_bits_size);
                bus_width = _cyhal_qspi_convert_bus_width(command->mode_bits.bus_width);
                #if (CY_IP_MXSMIF_VERSION >= 3)
                data_rate = (cy_en_smif_data_rate_t)command->mode_bits.data_rate;
                #endif /* CY_IP_MXSMIF_VERSION >= 3 */
            }

            uint32_t cmpltTxfr = ((endOfTransfer) ? 1UL : 0UL);
            #if (CY_IP_MXSMIF_VERSION < 3)
            result = (cy_rslt_t)Cy_SMIF_TransmitCommand(obj->base, (uint8_t)(command->instruction.value & 0xFF),
                        _cyhal_qspi_convert_bus_width(command->instruction.bus_width), cmd_param,
                        (addr_size + mode_bits_size), bus_width, obj->slave_select, cmpltTxfr, &obj->context);
            #else
            result = (cy_rslt_t)Cy_SMIF_TransmitCommand_Ext(obj->base, command->instruction.value,
                        command->instruction.two_byte_cmd, _cyhal_qspi_convert_bus_width(command->instruction.bus_width),
                        (cy_en_smif_data_rate_t)command->instruction.data_rate, cmd_param, (addr_size + mode_bits_size),
                        bus_width, data_rate, obj->slave_select, cmpltTxfr, &obj->context);
            #endif /* CY_IP_MXSMIF_VERSION < 3 or other */
        }
    }
    return result;
}

static inline cy_en_smif_slave_select_t _cyhal_qspi_slave_idx_to_smif_ss(uint8_t ssel_idx)
{
    return (cy_en_smif_slave_select_t)(1 << ssel_idx);
}

/* Checks, that user provided all needed pins and returns max bus width */
static cy_rslt_t _cyhal_qspi_check_user_pins(const cyhal_qspi_slave_pin_config_t *pin_set, cyhal_qspi_bus_width_t *max_width)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

#if _CYHAL_QSPI_DATA8_PRESENT
    if (NC != pin_set->io[4])
    {
        *max_width = CYHAL_QSPI_CFG_BUS_OCTAL;
    }
    else
#endif
    if (NC != pin_set->io[2])
    {
        *max_width = CYHAL_QSPI_CFG_BUS_QUAD;
    }
    else if (NC != pin_set->io[1])
    {
        *max_width = CYHAL_QSPI_CFG_BUS_DUAL;
    }
    else
    {
        *max_width = CYHAL_QSPI_CFG_BUS_SINGLE;
    }

    for (uint8_t i = 1; i <= _CYHAL_QSPI_MAX_DATA_PINS; i++)
    {
        /* Pins with index lower than width must be provided, pins above should be NC */
        if ((NC == pin_set->io[i-1]) != (i > *max_width))
        {
            result = CYHAL_QSPI_RSLT_ERR_PIN;
        }
    }

    return result;
}

/* Based on ssel pin chosen, determines SMIF slave select parameter and pin mapping */
static const cyhal_resource_pin_mapping_t *_cyhal_qspi_get_slaveselect(cyhal_gpio_t ssel, uint8_t *ssel_idx)
{
#if _CYHAL_QSPI_SEL1 || _CYHAL_QSPI_SEL2 || _CYHAL_QSPI_SEL3
    bool pin_found = false;
#endif
    const cyhal_resource_pin_mapping_t *pin_mapping = _CYHAL_UTILS_GET_RESOURCE(ssel, cyhal_pin_map_smif_spi_select0);
    if (NULL != pin_mapping)
    {
#if _CYHAL_QSPI_SEL1 || _CYHAL_QSPI_SEL2 || _CYHAL_QSPI_SEL3
        pin_found = true;
#endif
        /* Provided by user ssel is related to Slave # 0 */
        *ssel_idx = 0;
    }
#if _CYHAL_QSPI_SEL1
    if (!pin_found)
    {
        pin_mapping = _CYHAL_UTILS_GET_RESOURCE(ssel, cyhal_pin_map_smif_spi_select1);
        if (NULL != pin_mapping)
        {
            pin_found = true;
            /* Provided by user ssel is related to Slave # 1 */
            *ssel_idx = 1;
        }
    }
#endif
#if _CYHAL_QSPI_SEL2
    if (!pin_found)
    {
        pin_mapping = _CYHAL_UTILS_GET_RESOURCE(ssel, cyhal_pin_map_smif_spi_select2);
        if (NULL != pin_mapping)
        {
            pin_found = true;
            /* Provided by user ssel is related to Slave # 2 */
            *ssel_idx = 2;
        }
    }
#endif
#if _CYHAL_QSPI_SEL3
    if (!pin_found)
    {
        pin_mapping = _CYHAL_UTILS_GET_RESOURCE(ssel, cyhal_pin_map_smif_spi_select3);
        if (NULL != pin_mapping)
        {
            pin_found = true;
            /* Provided by user ssel is related to Slave # 3 */
            *ssel_idx = 3;
        }
    }
#endif

    return pin_mapping;
}

/* Based on data pins chosen, determines SMIF data select parameter */
static const cyhal_resource_pin_mapping_t *_cyhal_qspi_get_dataselect(cyhal_gpio_t io0, cy_en_smif_data_select_t *data_select, uint8_t *offset)
{
    bool pin_found = false;
    const cyhal_resource_pin_mapping_t *pin_mapping = _CYHAL_UTILS_GET_RESOURCE(io0, cyhal_pin_map_smif_spi_data0);
    if (NULL != pin_mapping)
    {
        pin_found = true;
        *data_select = CY_SMIF_DATA_SEL0;
        *offset = 0;
    }
    if (!pin_found)
    {
        pin_mapping = _CYHAL_UTILS_GET_RESOURCE(io0, cyhal_pin_map_smif_spi_data2);
        if (NULL != pin_mapping)
        {
            pin_found = true;
            *data_select = CY_SMIF_DATA_SEL1;
            *offset = 2;
        }
    }
#if _CYHAL_QSPI_DATA8_PRESENT
    if (!pin_found)
    {
        pin_mapping = _CYHAL_UTILS_GET_RESOURCE(io0, cyhal_pin_map_smif_spi_data4);
        if (NULL != pin_mapping)
        {
            pin_found = true;
            *data_select = CY_SMIF_DATA_SEL2;
            *offset = 4;
        }
    }
    if (!pin_found)
    {
        pin_mapping = _CYHAL_UTILS_GET_RESOURCE(io0, cyhal_pin_map_smif_spi_data6);
        if (NULL != pin_mapping)
        {
            pin_found = true;
            *data_select = CY_SMIF_DATA_SEL3;
            *offset = 6;
        }
    }
#endif
    return pin_mapping;
}

/*******************************************************************************
*       Functions
*******************************************************************************/

static cy_rslt_t _cyhal_qspi_slave_select_check_reserve(cyhal_qspi_t *obj, cyhal_gpio_t ssel, uint8_t *found_idx,
                                                        bool reserve_n_connect)
{
    CY_ASSERT(NULL != obj);
    const cyhal_resource_pin_mapping_t *ssel_map = _cyhal_qspi_get_slaveselect(ssel, found_idx);
    /* Found ssel map is not null and belong to same block as obj->resource */
    if ((NULL == ssel_map) || !_cyhal_utils_map_resource_equal(&obj->resource, ssel_map, true))
    {
        return CYHAL_QSPI_RSLT_ERR_CANNOT_CONFIG_SSEL;
    }
    /* Specified SSEL is already configured, nothing to do. */
    if (NC != obj->pin_ssel[*found_idx])
    {
        return CY_RSLT_SUCCESS;
    }
    /* No problems with pins, proceeding to reservation if reserve_n_connect is true */
    /* If reserve_n_connect is false, it is assumed that pins are reserved and initialized by configurator - generated
    *   code */
    cy_rslt_t result = reserve_n_connect
        ? _cyhal_qspi_check_pin_and_reserve(ssel_map, CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_SELECT0)
        : CY_RSLT_SUCCESS;
    if (CY_RSLT_SUCCESS == result)
    {
        obj->pin_ssel[*found_idx] = ssel;
    }
    return result;
}

/* Checks that provided pins are correct, store them in the object and return data select */
static cy_rslt_t _cyhal_qspi_process_pin_set(cyhal_qspi_t *obj, const cyhal_qspi_slave_pin_config_t *pin_set,
    cy_en_smif_data_select_t *data_select, uint8_t *found_ssel_idx, bool reserve_n_connect)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != pin_set);

    cyhal_qspi_bus_width_t max_width;
    cy_rslt_t result = _cyhal_qspi_check_user_pins(pin_set, &max_width);

    uint8_t pin_offset = 0;
    const cyhal_resource_pin_mapping_t *io_maps[_CYHAL_QSPI_MAX_DATA_PINS];
    for (uint8_t i = 0; i < _CYHAL_QSPI_MAX_DATA_PINS; i++)
    {
        io_maps[i] = NULL;
    }
    const size_t data_pin_map_sizes[_CYHAL_QSPI_MAX_DATA_PINS - 1] = // Must compute sizes here since we can't get them from the map pointers
    {
        sizeof(cyhal_pin_map_smif_spi_data1) / sizeof(cyhal_resource_pin_mapping_t),
        sizeof(cyhal_pin_map_smif_spi_data2) / sizeof(cyhal_resource_pin_mapping_t),
        sizeof(cyhal_pin_map_smif_spi_data3) / sizeof(cyhal_resource_pin_mapping_t),
#if _CYHAL_QSPI_DATA8_PRESENT
        sizeof(cyhal_pin_map_smif_spi_data4) / sizeof(cyhal_resource_pin_mapping_t),
        sizeof(cyhal_pin_map_smif_spi_data5) / sizeof(cyhal_resource_pin_mapping_t),
        sizeof(cyhal_pin_map_smif_spi_data6) / sizeof(cyhal_resource_pin_mapping_t),
        sizeof(cyhal_pin_map_smif_spi_data7) / sizeof(cyhal_resource_pin_mapping_t),
#endif
    };
    const cyhal_resource_pin_mapping_t *data_pin_maps[_CYHAL_QSPI_MAX_DATA_PINS - 1] = // Not used to get the map for data pin 0
    {
        cyhal_pin_map_smif_spi_data1,
        cyhal_pin_map_smif_spi_data2,
        cyhal_pin_map_smif_spi_data3,
#if _CYHAL_QSPI_DATA8_PRESENT
        cyhal_pin_map_smif_spi_data4,
        cyhal_pin_map_smif_spi_data5,
        cyhal_pin_map_smif_spi_data6,
        cyhal_pin_map_smif_spi_data7,
#endif
    };

    if (CY_RSLT_SUCCESS == result)
    {
        const cyhal_resource_pin_mapping_t *tmp_io_map =
                _cyhal_qspi_get_dataselect(pin_set->io[0], data_select, &pin_offset);
        io_maps[pin_offset] = tmp_io_map;
        if ( NULL == io_maps[pin_offset] ||
            !_cyhal_utils_map_resource_equal(&obj->resource, io_maps[pin_offset],true))
        {
            result = CYHAL_QSPI_RSLT_ERR_PIN;
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        /* DATA_SEL 1 and DATA_SEL 3 are illegal when using Quad SPI
        *  DATA SEL 1, DATA SEL 2 and DATA SEL 3 are illegal when using Octal SPI */
        if (((CYHAL_QSPI_CFG_BUS_QUAD == max_width) &&
                ((CY_SMIF_DATA_SEL1 == *data_select) || (CY_SMIF_DATA_SEL3 == *data_select))) ||
            ((CYHAL_QSPI_CFG_BUS_OCTAL == max_width) && (*data_select >= CY_SMIF_DATA_SEL1)))
        {
            result = CYHAL_QSPI_RSLT_ERR_DATA_SEL;
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        /* Check that all data pins (but not the first one, which is covered already) are valid and belong
        *  to same instance */
        for (uint8_t i = pin_offset + 1; i < pin_offset + max_width; i++)
        {
            io_maps[i] = _cyhal_utils_get_resource(pin_set->io[i-pin_offset], data_pin_maps[i-1], data_pin_map_sizes[i-1],
                                NULL, false);
            if (NULL == io_maps[i] || !_cyhal_utils_map_resource_equal(&obj->resource, io_maps[i],true))
            {
                result = CYHAL_QSPI_RSLT_ERR_PIN;
                break;
            }
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_qspi_slave_select_check_reserve(obj, pin_set->ssel, found_ssel_idx, reserve_n_connect);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        /* reserve the io pins */
        for (uint8_t i = pin_offset; (i < pin_offset + max_width) && (result == CY_RSLT_SUCCESS); i++)
        {
            if ((NC != pin_set->io[i-pin_offset]) && (NC == obj->pin_io[i]))
            {
                if (reserve_n_connect)
                {
                    result = _cyhal_qspi_check_pin_and_reserve(io_maps[i], CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_DATA0);
                }
                if (CY_RSLT_SUCCESS == result)
                {
                    obj->pin_io[i] = pin_set->io[i-pin_offset];
                }
            }
        }
    }

    return result;
}


static cy_rslt_t _cyhal_qspi_init_common(cyhal_qspi_t *obj, const cyhal_qspi_configurator_t *cfg, uint32_t hz)
{
    /* Explicitly marked not allocated resources as invalid to prevent freeing them. */
    memset(obj, 0, sizeof(cyhal_qspi_t));
    obj->resource.type = CYHAL_RSC_INVALID;
    obj->is_clock_owned = false;

    obj->dc_configured = (NULL != cfg->resource);
    if ((obj->dc_configured) &&
        (cfg->config->mode != CY_SMIF_NORMAL ||
        /* Bits representation of interrupts (msb to lsb):
            _MEMORY_MODE_ALIGMENT_ERROR, _RX_DATA_FIFO_UNDERFLOW, _TX_COMMAND_FIFO_OVERFLOW, _TX_DATA_FIFO_OVERFLOW,
            _RX_FIFO_TRIGEER_LEVEL, _TX_FIFO_TRIGEER_LEVEL */
        ((cfg->irqs & 0x3F) != 0) ||
        /* Bits representation of activated DMA outputs (msb to lsb):
            _RX_DMA_TRIGGER_OUT_USED, _TX_DMA_TRIGGER_OUT_USED */
        (cfg->dmas & 0x3) != 0))
    {
        /* List of SMIF personality items, which are currently not supported in QSPI HAL driver:
            - XIP (eXecute In Place) mode
            - Memory Mode Alignment Error interrupt
            - RX Data FIFO Underflow interrupt
            - TX Command FIFO Overflow
            - TX Data FIFO Overflow interrupt
            - RX FIFO Level Trigger interrupt
            - TX FIFO Level Trigger interrupt
            - RX DMA Trigger
            - TX DMA Trigger
        */
        return CYHAL_QSPI_RSLT_ERR_UNSUPPORTED;
    }

    cyhal_gpio_t ssel = NC;
    size_t found_ssel_idx_cfg = 0;
    for (size_t ssel_idx = 0; ssel_idx < sizeof(cfg->gpios.ssel) / sizeof(cfg->gpios.ssel[0]); ++ssel_idx)
    {
        if (NC != cfg->gpios.ssel[ssel_idx])
        {
            ssel = cfg->gpios.ssel[ssel_idx];
            found_ssel_idx_cfg = ssel_idx;
            break;
        }
    }

    cy_rslt_t result = CY_RSLT_SUCCESS;
#if (CY_IP_MXSMIF_VERSION >= 4)
    if(cfg->gpios.sclk != NC)
    {
        result = CYHAL_QSPI_RSLT_ERR_PIN;
    }
#else
    const cyhal_resource_pin_mapping_t *sclk_map = _CYHAL_UTILS_GET_RESOURCE(cfg->gpios.sclk, cyhal_pin_map_smif_spi_clk);
    /* Can't work without sclk pin */
    if (NULL == sclk_map)
    {
        result = CYHAL_QSPI_RSLT_ERR_PIN;
    }
    if ((CY_RSLT_SUCCESS == result) && (false == obj->dc_configured))
    {
        result = _cyhal_qspi_check_pin_and_reserve(sclk_map, CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_CLK);
    }
#endif
    if (CY_RSLT_SUCCESS == result)
    {
        obj->pin_sclk = cfg->gpios.sclk;

        for (size_t i = 0; i < SMIF_CHIP_TOP_SPI_SEL_NR; ++i)
        {
            obj->pin_ssel[i] = NC;
        }
        for (size_t i = 0; i < _CYHAL_QSPI_MAX_DATA_PINS; ++i)
        {
            obj->pin_io[i] = NC;
        }
    }

    cy_en_smif_data_select_t data_select;
    uint8_t found_ssel_idx;

    cyhal_qspi_slave_pin_config_t pin_set;
    pin_set.ssel = ssel;
    memcpy(pin_set.io, cfg->gpios.io, sizeof(cfg->gpios.io));
    const cyhal_resource_pin_mapping_t *ssel_map;
    if (CY_RSLT_SUCCESS == result)
    {
        ssel_map = _cyhal_qspi_get_slaveselect(ssel, &found_ssel_idx);
        if(ssel_map == NULL)
        {
            result = CYHAL_QSPI_RSLT_ERR_PIN;
        }
    }
    if (CY_RSLT_SUCCESS == result)
    {
        if (obj->dc_configured)
        {
            obj->resource = *cfg->resource;
        }
        else
        {
            cyhal_resource_inst_t rsc = { CYHAL_RSC_SMIF, ssel_map->block_num, ssel_map->channel_num };
        #ifndef __MBED__
            // Mbed calls qspi_init multiple times without calling qspi_free to update the QSPI frequency/mode.
            // As a result, we won't worry about resource reservation if running through mbed.
            result = cyhal_hwmgr_reserve(&rsc);
            if (CY_RSLT_SUCCESS == result)
        #endif
            {
                obj->resource = rsc;
            }
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_qspi_process_pin_set(obj, &pin_set, &data_select, &found_ssel_idx, !obj->dc_configured);
    }


    if (CY_RSLT_SUCCESS == result)
    {
        obj->base = _cyhal_qspi_base_addresses[obj->resource.block_num];
    }

    if (CY_RSLT_SUCCESS == result)
    {
        if (NULL != cfg->clock)
        {
            /* Clock is provided by configuration */
            if (cfg->clock->block == CYHAL_CLOCK_BLOCK_HF)
            {
                obj->clock = *cfg->clock;
                /* obj->is_clock_owned is false already, so no need to assign it */
            }
            else
            {
                /* Incorrect shared clock was provided by user. */
                result = CYHAL_QSPI_RSLT_ERR_CLOCK;
            }
        }
        else
        {
            /* No clock was provided by configuration, so allocating it */

            // The hardware is generally going to be hardwired to an hfclk, which has very limited divider options. In the event
            // that we're hooked up a PERI divider, we don't have any particular expectations about its width - so just ask for 8-bit
            result = _cyhal_utils_allocate_clock(&(obj->clock), &(obj->resource), CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT, true);
            obj->is_clock_owned = (result == CY_RSLT_SUCCESS);
        }
    }

    if (obj->is_clock_owned)
    {
        if (CY_RSLT_SUCCESS == result)
        {
            result = cyhal_qspi_set_frequency(obj, hz);
        }

        if (CY_RSLT_SUCCESS == result)
        {
            result = cyhal_clock_set_enabled(&(obj->clock), true, true);
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        result = (cy_rslt_t) Cy_SMIF_Init(obj->base, cfg->config, _CYHAL_QSPI_TIMEOUT_10_MS, &obj->context);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        /* Configure first SSEL, that was found in cfg->gpios and make it active */
        obj->slave_select = _cyhal_qspi_slave_idx_to_smif_ss(found_ssel_idx);
        Cy_SMIF_SetDataSelect(obj->base, obj->slave_select, data_select);

        /* found_ssel_idx_cfg and below are already processed, no reason to start from index #0 */
        size_t ssel_idx = found_ssel_idx_cfg;
        /* Process rest of ssel, that are provided by cfg->gpios */
        while ((CY_RSLT_SUCCESS == result) && ((ssel_idx + 1) < (sizeof(cfg->gpios.ssel) / sizeof(cfg->gpios.ssel[0]))))
        {
            ++ssel_idx;
            if (NC != cfg->gpios.ssel[ssel_idx])
            {
                pin_set.ssel = cfg->gpios.ssel[ssel_idx];
                result = _cyhal_qspi_process_pin_set(obj, &pin_set, &data_select, &found_ssel_idx, !obj->dc_configured);
                if (result == CY_RSLT_SUCCESS)
                {
                    Cy_SMIF_SetDataSelect(obj->base, _cyhal_qspi_slave_idx_to_smif_ss(found_ssel_idx), data_select);
                }
            }
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        Cy_SMIF_Enable(obj->base, &obj->context);

        obj->callback_data.callback = NULL;
        obj->callback_data.callback_arg = NULL;
        obj->irq_cause = CYHAL_QSPI_EVENT_NONE;
        _cyhal_qspi_config_structs[obj->resource.block_num] = obj;
        obj->pm_transition_pending = false;
        obj->pm_callback.callback = &_cyhal_qspi_pm_callback;
        obj->pm_callback.states = (cyhal_syspm_callback_state_t)(CYHAL_SYSPM_CB_CPU_DEEPSLEEP | CYHAL_SYSPM_CB_SYSTEM_HIBERNATE);
        obj->pm_callback.args = obj;
        obj->pm_callback.next = NULL;
        obj->pm_callback.ignore_modes = CYHAL_SYSPM_AFTER_DS_WFI_TRANSITION;
        _cyhal_syspm_register_peripheral_callback(&(obj->pm_callback));

        _cyhal_irq_register(_cyhal_qspi_irq_n[obj->resource.block_num], CYHAL_ISR_PRIORITY_DEFAULT, _cyhal_qspi_irq_handler);
        _cyhal_irq_enable(_cyhal_qspi_irq_n[obj->resource.block_num]);
    }

    if (CY_RSLT_SUCCESS != result)
    {
        cyhal_qspi_free(obj);
    }

    return result;
}

cy_rslt_t cyhal_qspi_init(
    cyhal_qspi_t *obj, cyhal_gpio_t sclk, const cyhal_qspi_slave_pin_config_t *pin_set, uint32_t hz, uint8_t mode,
    cyhal_clock_t *clk)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != pin_set);

    /* mode (CPOL and CPHA) are not supported in CAT1 */
    CY_UNUSED_PARAMETER(mode);

#if defined(CY_DEVICE_CYW20829)
    if (NULL == clk)
    {
        /* Only user-provided clock is supported by 20829 QSPI. Please refer to device-specific
            "section_hal_impl_qspi_init_clock_20829" documentation section for details. */

        return CYHAL_QSPI_RSLT_ERR_UNSUPPORTED;
    }
#endif /* defined(CY_DEVICE_CYW20829) */

    /* Default QSPI configuration */
    const cy_stc_smif_config_t config =
    {
        .mode = (uint32_t)CY_SMIF_NORMAL,
        .deselectDelay = _CYHAL_QSPI_DESELECT_DELAY,
#if (CY_IP_MXSMIF_VERSION >= 2)
        .rxClockSel = (uint32_t)CY_SMIF_SEL_INVERTED_FEEDBACK_CLK,
#else
        .rxClockSel = (uint32_t)CY_SMIF_SEL_INV_INTERNAL_CLK,
#endif
        .blockEvent = (uint32_t)CY_SMIF_BUS_ERROR,
    };

    const cyhal_qspi_configurator_t cfg = {
        .resource = NULL,
        .config = &config,
        .clock = clk,
        .gpios = {
            .sclk = sclk,
            .ssel = { pin_set->ssel, NC, NC, NC },
            .io = { pin_set->io[0], pin_set->io[1], pin_set->io[2], pin_set->io[3],
                    pin_set->io[4], pin_set->io[5], pin_set->io[6], pin_set->io[7] }
        },
        .irqs = 0u,
        .dmas = 0u
    };

    return _cyhal_qspi_init_common(obj, &cfg, hz);
}

cy_rslt_t cyhal_qspi_init_cfg(cyhal_qspi_t *obj, const cyhal_qspi_configurator_t *cfg)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != cfg);
    CY_ASSERT(NULL != cfg->config);

    /* Frequency parameter is ignored when clock is provided (configurator flow, cyhal_qspi_init_cfg function) */
    return _cyhal_qspi_init_common(obj, cfg, 0);
}

void cyhal_qspi_free(cyhal_qspi_t *obj)
{
    if (CYHAL_RSC_SMIF == obj->resource.type)
    {
        _cyhal_system_irq_t irqn = _cyhal_qspi_irq_n[obj->resource.block_num];
        _cyhal_irq_free(irqn);
        _cyhal_syspm_unregister_peripheral_callback(&(obj->pm_callback));
        if (obj->base != NULL)
        {
            Cy_SMIF_Disable(obj->base);
            Cy_SMIF_DeInit(obj->base);
            obj->base = NULL;
        }
        if (!obj->dc_configured)
        {
            cyhal_hwmgr_free(&(obj->resource));
        }
        obj->resource.type = CYHAL_RSC_INVALID;
    }

    if (!obj->dc_configured)
    {
        _cyhal_utils_release_if_used(&(obj->pin_sclk));
        for (uint8_t i = 0; i < SMIF_CHIP_TOP_SPI_SEL_NR; i++)
        {
            _cyhal_utils_release_if_used(&(obj->pin_ssel[i]));
        }
        for (uint8_t i = 0; (i < _CYHAL_QSPI_MAX_DATA_PINS); i++)
        {
            _cyhal_utils_release_if_used(&(obj->pin_io[i]));
        }
    }

    if (obj->is_clock_owned)
    {
        cyhal_clock_free(&(obj->clock));
        obj->is_clock_owned = false;
    }
}

cy_rslt_t cyhal_qspi_set_frequency(cyhal_qspi_t *obj, uint32_t hz)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(hz != 0);

    if (obj->is_clock_owned)
    {
        const cyhal_clock_tolerance_t tolerance = { CYHAL_TOLERANCE_PERCENT, 10 };
#if (CY_IP_MXSMIF_VERSION >= 2)
        /* SMIF ver. 2 and further divides source clock by 2 internally, so we need to request 2 times more.
         * Please refer to `section_hal_impl_clock_freq` implementation-specific documentation for details.
        */
        hz <<= 1;
#endif /*  */
        return _cyhal_utils_set_clock_frequency2(&(obj->clock), hz, &tolerance);
    }
    else
    {
        /* In case of pre-configured clock, user application is responsible for configuring QSPI bus frequency.
        *  For all currently supported by this driver devices, output QSPI bus frequency is equal to frequency
        *  of provided HF clock. */
        return CYHAL_QSPI_RSLT_ERR_CLOCK;
    }
}

uint32_t cyhal_qspi_get_frequency(cyhal_qspi_t *obj)
{
    CY_ASSERT(NULL != obj);
    uint32_t freq = cyhal_clock_get_frequency(&(obj->clock));
#if (CY_IP_MXSMIF_VERSION >= 2)
    /* Please refer to `section_hal_impl_clock_freq` implementation-specific documentation for details. */
    return freq / 2;
#else
    return freq;
#endif /* (CY_IP_MXSMIF_VERSION >= 2) or other */
}

cy_rslt_t cyhal_qspi_slave_configure(cyhal_qspi_t *obj, const cyhal_qspi_slave_pin_config_t *pin_set)
{
    CY_ASSERT(NULL != obj);
    uint8_t ssel_idx = 0;
    cy_en_smif_data_select_t data_select;
    cy_rslt_t result = _cyhal_qspi_process_pin_set(obj, pin_set, &data_select, &ssel_idx, true);
    if (CY_RSLT_SUCCESS == result)
    {
        Cy_SMIF_SetDataSelect(obj->base, _cyhal_qspi_slave_idx_to_smif_ss(ssel_idx), data_select);
    }
    return result;
}

cy_rslt_t cyhal_qspi_select_active_ssel(cyhal_qspi_t *obj, cyhal_gpio_t ssel)
{
    CY_ASSERT(NULL != obj);
    for (uint8_t ssel_idx = 0; ssel_idx < SMIF_CHIP_TOP_SPI_SEL_NR; ssel_idx++)
    {
        if (ssel == obj->pin_ssel[ssel_idx])
        {
            obj->slave_select = _cyhal_qspi_slave_idx_to_smif_ss(ssel_idx);
            return CY_RSLT_SUCCESS;
        }
    }
    return CYHAL_QSPI_RSLT_ERR_CANNOT_SWITCH_SSEL;
}

static cy_rslt_t _cyhal_qspi_wait_for_cmd_fifo(cyhal_qspi_t *obj)
{
    cy_rslt_t status = CY_RSLT_SUCCESS;
    uint32_t timeout = _CYHAL_QSPI_TIMEOUT_10_MS;
    while ((Cy_SMIF_GetCmdFifoStatus(obj->base) == CY_SMIF_TX_CMD_FIFO_STATUS_RANGE) &&
                    (CY_RSLT_SUCCESS == status))
    {
        /* Waiting for 1 us per iteration */
        Cy_SysLib_DelayUs(1);
        --timeout;
        status = (0u == timeout)? CYHAL_QSPI_RSLT_ERR_TIMEOUT: CY_RSLT_SUCCESS;
    }
    return status;
}

/* no restriction on the value of length. This function splits the read into multiple chunked transfers. */
cy_rslt_t cyhal_qspi_read(cyhal_qspi_t *obj, const cyhal_qspi_command_t *command, uint32_t address, void *data, size_t *length)
{
    if (obj->pm_transition_pending)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }
    cy_rslt_t status = CY_RSLT_SUCCESS;
    uint32_t chunk = 0;
    size_t read_bytes = *length;

    /* SMIF can read only up to 65536 bytes in one go. Split the larger read into multiple chunks */
    while (read_bytes > 0)
    {
        chunk = (read_bytes > _CYHAL_QSPI_MAX_RX_COUNT) ? (_CYHAL_QSPI_MAX_RX_COUNT) : read_bytes;

        status = _cyhal_qspi_command_transfer(obj, command, address, false);

        if (CY_RSLT_SUCCESS == status)
        {
            if (command->dummy_cycles.dummy_count > 0u)
            {
                status = _cyhal_qspi_wait_for_cmd_fifo(obj);
                if (CY_RSLT_SUCCESS == status)
                {
                    #if (CY_IP_MXSMIF_VERSION < 3)
                    status = (cy_rslt_t)Cy_SMIF_SendDummyCycles(obj->base, command->dummy_cycles.dummy_count);
                    #else
                    status = (cy_rslt_t)Cy_SMIF_SendDummyCycles_Ext(obj->base,
                            _cyhal_qspi_convert_bus_width(command->dummy_cycles.bus_width),
                            (cy_en_smif_data_rate_t)command->dummy_cycles.data_rate, command->dummy_cycles.dummy_count);
                    #endif /* CY_IP_MXSMIF_VERSION < 3 or other */
                }
            }

            if (CY_RSLT_SUCCESS == status)
            {
                status = _cyhal_qspi_wait_for_cmd_fifo(obj);
                if (CY_RSLT_SUCCESS == status)
                {
                    #if (CY_IP_MXSMIF_VERSION < 3)
                    status = (cy_rslt_t)Cy_SMIF_ReceiveDataBlocking(obj->base, (uint8_t *)data, chunk,
                        _cyhal_qspi_convert_bus_width(command->data.bus_width), &obj->context);
                    #else
                    status = (cy_rslt_t)Cy_SMIF_ReceiveDataBlocking_Ext(obj->base, (uint8_t *)data, chunk,
                        _cyhal_qspi_convert_bus_width(command->data.bus_width),
                        (cy_en_smif_data_rate_t)command->data.data_rate, &obj->context);
                    #endif /* CY_IP_MXSMIF_VERSION < 3 or other */
                    if (CY_RSLT_SUCCESS != status)
                    {
                        break;
                    }
                }
            }
        }
        read_bytes -= chunk;
        address += chunk;
        data = (uint8_t *)data + chunk;
    }

    return status;
}

cy_rslt_t cyhal_qspi_read_async(cyhal_qspi_t *obj, const cyhal_qspi_command_t *command, uint32_t address, void *data, size_t *length)
{
    if (obj->pm_transition_pending)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }
    cy_rslt_t status = _cyhal_qspi_command_transfer(obj, command, address, false);

    if (CY_RSLT_SUCCESS == status)
    {
        if (command->dummy_cycles.dummy_count > 0u)
        {
            status = _cyhal_qspi_wait_for_cmd_fifo(obj);
            if (CY_RSLT_SUCCESS == status)
            {
                #if (CY_IP_MXSMIF_VERSION < 3)
                status = (cy_rslt_t)Cy_SMIF_SendDummyCycles(obj->base, command->dummy_cycles.dummy_count);
                #else
                status = (cy_rslt_t)Cy_SMIF_SendDummyCycles_Ext(obj->base,
                        _cyhal_qspi_convert_bus_width(command->dummy_cycles.bus_width),
                        (cy_en_smif_data_rate_t)command->dummy_cycles.data_rate, command->dummy_cycles.dummy_count);
                #endif /* CY_IP_MXSMIF_VERSION < 3 or other */
            }
        }

        if (CY_RSLT_SUCCESS == status)
        {
            status = _cyhal_qspi_wait_for_cmd_fifo(obj);
            if (CY_RSLT_SUCCESS == status)
            {
                #if (CY_IP_MXSMIF_VERSION < 3)
                status = (cy_rslt_t)Cy_SMIF_ReceiveData(obj->base, (uint8_t *)data, (uint32_t)*length,
                    _cyhal_qspi_convert_bus_width(command->data.bus_width), _cyhal_qspi_cb_wrapper, &obj->context);
                #else
                status = (cy_rslt_t)Cy_SMIF_ReceiveData_Ext(obj->base, (uint8_t *)data, (uint32_t)*length,
                    _cyhal_qspi_convert_bus_width(command->data.bus_width),
                    (cy_en_smif_data_rate_t)command->data.data_rate, _cyhal_qspi_cb_wrapper, &obj->context);
                #endif /* CY_IP_MXSMIF_VERSION < 3 or other */
            }
        }
    }
    return status;
}

/* length can be up to 65536. */
cy_rslt_t cyhal_qspi_write(cyhal_qspi_t *obj, const cyhal_qspi_command_t *command, uint32_t address, const void *data,
        size_t *length)
{
    if (obj->pm_transition_pending)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }
    cy_rslt_t status = _cyhal_qspi_command_transfer(obj, command, address, false);

    if (CY_RSLT_SUCCESS == status)
    {
        if (command->dummy_cycles.dummy_count > 0u)
        {
            status = _cyhal_qspi_wait_for_cmd_fifo(obj);
            if (CY_RSLT_SUCCESS == status)
            {
                #if (CY_IP_MXSMIF_VERSION < 3)
                status = (cy_rslt_t)Cy_SMIF_SendDummyCycles(obj->base, command->dummy_cycles.dummy_count);
                #else
                status = (cy_rslt_t)Cy_SMIF_SendDummyCycles_Ext(obj->base,
                        _cyhal_qspi_convert_bus_width(command->dummy_cycles.bus_width),
                        (cy_en_smif_data_rate_t)command->dummy_cycles.data_rate, command->dummy_cycles.dummy_count);
                #endif /* CY_IP_MXSMIF_VERSION < 3 or other */
            }
        }

        if ((CY_SMIF_SUCCESS == status) && (*length > 0))
        {
            status = _cyhal_qspi_wait_for_cmd_fifo(obj);
            if (CY_RSLT_SUCCESS == status)
            {
                #if (CY_IP_MXSMIF_VERSION < 3)
                status = (cy_rslt_t)Cy_SMIF_TransmitDataBlocking(obj->base, (uint8_t *)data, *length,
                    _cyhal_qspi_convert_bus_width(command->data.bus_width), &obj->context);
                #else
                status = (cy_rslt_t)Cy_SMIF_TransmitDataBlocking_Ext(obj->base, (uint8_t *)data, *length,
                    _cyhal_qspi_convert_bus_width(command->data.bus_width),
                    (cy_en_smif_data_rate_t)command->data.data_rate, &obj->context);
                #endif /* CY_IP_MXSMIF_VERSION < 3 or other */
            }
        }
    }

    return status;
}

/* length can be up to 65536. */
cy_rslt_t cyhal_qspi_write_async(cyhal_qspi_t *obj, const cyhal_qspi_command_t *command, uint32_t address, const void *data, size_t *length)
{
    if (obj->pm_transition_pending)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }
    cy_rslt_t status = _cyhal_qspi_command_transfer(obj, command, address, false);

    if (CY_RSLT_SUCCESS == status)
    {
        if (command->dummy_cycles.dummy_count > 0u)
        {
            status = _cyhal_qspi_wait_for_cmd_fifo(obj);
            if (CY_RSLT_SUCCESS == status)
            {
                #if (CY_IP_MXSMIF_VERSION < 3)
                status = (cy_rslt_t)Cy_SMIF_SendDummyCycles(obj->base, command->dummy_cycles.dummy_count);
                #else
                status = (cy_rslt_t)Cy_SMIF_SendDummyCycles_Ext(obj->base,
                        _cyhal_qspi_convert_bus_width(command->dummy_cycles.bus_width),
                        (cy_en_smif_data_rate_t)command->dummy_cycles.data_rate, command->dummy_cycles.dummy_count);
                #endif /* CY_IP_MXSMIF_VERSION < 3 or other */
            }
        }

        if ((CY_SMIF_SUCCESS == status) && (*length > 0))
        {
            status = _cyhal_qspi_wait_for_cmd_fifo(obj);
            if (CY_RSLT_SUCCESS == status)
            {
                #if (CY_IP_MXSMIF_VERSION < 3)
                status = (cy_rslt_t)Cy_SMIF_TransmitData(obj->base, (uint8_t *)data, *length,
                    _cyhal_qspi_convert_bus_width(command->data.bus_width), _cyhal_qspi_cb_wrapper, &obj->context);
                #else
                status = (cy_rslt_t)Cy_SMIF_TransmitData_Ext(obj->base, (uint8_t *)data, *length,
                    _cyhal_qspi_convert_bus_width(command->data.bus_width),
                    (cy_en_smif_data_rate_t)command->data.data_rate, _cyhal_qspi_cb_wrapper, &obj->context);
                #endif /* CY_IP_MXSMIF_VERSION < 3 or other */
            }
        }
    }
    return status;
}

cy_rslt_t cyhal_qspi_transfer(
    cyhal_qspi_t *obj, const cyhal_qspi_command_t *command, uint32_t address, const void *tx_data, size_t tx_size, void *rx_data,
    size_t rx_size)
{
    if (obj->pm_transition_pending)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }
    cy_rslt_t status = CY_RSLT_SUCCESS;

    if ((tx_data == NULL || tx_size == 0) && (rx_data == NULL || rx_size == 0))
    {
        /* only command, no rx or tx */
        status = _cyhal_qspi_command_transfer(obj, command, address, true);
    }
    else
    {
        if (tx_data != NULL && tx_size)
        {
            status = cyhal_qspi_write(obj, command, address, tx_data, &tx_size);
        }

        if (status == CY_RSLT_SUCCESS)
        {
            if (rx_data != NULL && rx_size)
            {
                status = cyhal_qspi_read(obj, command, address, rx_data, &rx_size);
            }
        }
    }
    return status;
}

void cyhal_qspi_register_callback(cyhal_qspi_t *obj, cyhal_qspi_event_callback_t callback, void *callback_arg)
{
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->callback_data.callback = (cy_israddress) callback;
    obj->callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(savedIntrStatus);

    obj->irq_cause = CYHAL_QSPI_EVENT_NONE;
}

void cyhal_qspi_enable_event(cyhal_qspi_t *obj, cyhal_qspi_event_t event, uint8_t intr_priority, bool enable)
{
    if (enable)
    {
        obj->irq_cause |= event;
    }
    else
    {
        obj->irq_cause &= ~event;
    }

    _cyhal_system_irq_t irqn = _cyhal_qspi_irq_n[obj->resource.block_num];
    _cyhal_irq_set_priority(irqn, intr_priority);
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* CYHAL_DRIVER_AVAILABLE_QSPI */
