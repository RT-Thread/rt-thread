/***************************************************************************//**
* \file cyhal_scb_common.h
*
* \brief
* Provides a struct definitions for configuration resources in the SCB (UART, I2C, SPI).
*
********************************************************************************
* \copyright
* Copyright 2018-2021 Cypress Semiconductor Corporation (an Infineon company) or
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

/** \cond INTERNAL */
/**
 * \addtogroup group_hal_impl_scb_common SCB Common Functionality
 * \ingroup group_hal_impl
 * \{
 * Code shared between the SCB resources (UART, I2C, and SPI).
 */

#pragma once

#include "cy_device.h"
#include "cy_pdl.h"
#include "cyhal_utils.h"
#include "cyhal_irq_psoc.h"
#include "cyhal_peri_common.h"
#include "cyhal_irq_psoc.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(CY_IP_MXSCB_INSTANCES)
#if defined(CY_DEVICE_PSOC6A256K) || defined(CY8C624ALQI_S2D42)
//Special case for 256k device which has 6 SCBs numbered 0, 1, 2, 4, 5, 6
#define _SCB_ARRAY_SIZE                 (CY_IP_MXSCB_INSTANCES + 1)
#else
#define _SCB_ARRAY_SIZE                 (CY_IP_MXSCB_INSTANCES)
#endif /* CY_DEVICE_PSOC6A256K */
#elif defined(CY_IP_M0S8SCB_INSTANCES)
#define _SCB_ARRAY_SIZE                 (CY_IP_M0S8SCB_INSTANCES)
#endif /* CY_IP_MXSCB_INSTANCES */

/** \addtogroup group_hal_results_scb SCB HAL Results
 *  SCB specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**

 */
/** Bad argument */
#define CYHAL_SCB_RSLT_ERR_BAD_ARGUMENT                     \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_IMPL_SCB, 0))

/**
 * \}
 */

/** SCB FIFO type */
typedef enum
{
    CYHAL_SCB_FIFO_RX, //!< Set RX FIFO level
    CYHAL_SCB_FIFO_TX, //!< Set TX FIFO level
} cyhal_scb_fifo_type_t;

/** Enum of possible output signals from an SCB */
typedef enum
{
    CYHAL_SCB_OUTPUT_TRIGGER_RX_FIFO_LEVEL_REACHED, //!< Output the RX FIFO signal which is triggered when the receive FIFO has more entries than the configured level.
    CYHAL_SCB_OUTPUT_TRIGGER_TX_FIFO_LEVEL_REACHED, //!< Output the TX FIFO signal which is triggered when the transmit FIFO has less entries than the configured level.
} cyhal_scb_output_t;

/** The start address of the SCB blocks */
extern CySCB_Type* const _CYHAL_SCB_BASE_ADDRESSES[_SCB_ARRAY_SIZE];
/** The interrupt number of the SCB blocks. */
extern const _cyhal_system_irq_t _CYHAL_SCB_IRQ_N[_SCB_ARRAY_SIZE];


/** Get the SCB block corresponding to an IRQn.
 *
 * @param[in] irqn The IRQn to get the corresponding block from
 * @return         The corresponding SCB block
 */
uint8_t cyhal_scb_get_block_from_irqn(_cyhal_system_irq_t irqn);

/** Get the SCB object corresponding to the currently running ISR.
 *
 * @return A pointer to the SCB object corresponding to the currently running ISR.
 */
void *_cyhal_scb_get_irq_obj(void);

/** Sets the desired clocks & data rate to achieve the specified frequency. Configuration of clock is not changed if
 * driver does not own it.
 * @param[in] obj       The I2C or EZI2C object to configure the peri divider for
 * @param[in] is_i2c    Whether driver to be configured is I2C or EZI2C (I2C is true)
 * @praam[in] freq      The desired frequency
 * @param[in] is_slave  Is this an I2C slave (true) or master (false)
 * @return The achieved data rate in Hz, or 0 if there was an error.
 */
uint32_t _cyhal_i2c_set_peri_divider(void *obj, bool is_i2c, uint32_t freq, bool is_slave);

/** Find an available SCB instance that matches 'pin'.
 * @param pin Pin
 * @param pin_map Pin mapping array
 * @param count Number of entries in pin_map
 * @return Pin map pointer or NULL if none found
 */
const cyhal_resource_pin_mapping_t* _cyhal_scb_find_map(cyhal_gpio_t pin, const cyhal_resource_pin_mapping_t *pin_map,
                    size_t count, const cyhal_resource_inst_t *block_res);

/** Find all available SCB instances that matches 'pin'.
 * @param pin Pin
 * @param pin_map Pin mapping array
 * @param count Number of entries in pin_map
 * @return Bit representation of SCB blocks, that can be wired with specified pin. 1 block - 1 bit, LSB corresponds to
 * SCB0. Only free for reserve blocks are returned. Example, output value 0x00000006 means that certain pin can belong
 * to next non-reserved blocks: SCB2 and SCB1.
 */
uint32_t _cyhal_scb_check_pin_affiliation(cyhal_gpio_t pin, const cyhal_resource_pin_mapping_t *pin_map, size_t count);

/** Sets a threshold level for a FIFO that will generate an interrupt and a
 * trigger output. The RX FIFO interrupt and trigger will be activated when
 * the receive FIFO has more entries than the threshold. The TX FIFO interrupt
 * and trigger will be activated when the transmit FIFO has less entries than
 * the threshold.
 *
 * @param[in]  base       SCB base
 * @param[in]  type       FIFO type to set level for
 * @param[in]  level      Level threshold to set
 * @return The status of the level set
 * */
cy_rslt_t _cyhal_scb_set_fifo_level(CySCB_Type *base, cyhal_scb_fifo_type_t type, uint16_t level);

/** Enables the specified output signal from an scb.
 *
 * @param[in]  resource   SCB resource
 * @param[in]  output     Which output signal to enable
 * @param[out] source     Pointer to user-allocated source signal object which
 * will be initialized by enable_output. source should be passed to
 * (dis)connect_digital functions to (dis)connect the associated endpoints.
 * @return The status of the output enable
 * */
cy_rslt_t _cyhal_scb_enable_output(cyhal_resource_inst_t resource, cyhal_scb_output_t output, cyhal_source_t *source);

/** Disables the specified output signal from an scb
 *
 * @param[in]  output     Which output signal to disable
 * @return The status of the output disable
 * */
cy_rslt_t _cyhal_scb_disable_output(cyhal_scb_output_t output);

#define _CYHAL_SCB_FIND_MAP(pin, pin_map) \
                    _cyhal_scb_find_map(pin, pin_map, sizeof(pin_map)/sizeof(cyhal_resource_pin_mapping_t), NULL)
#define _CYHAL_SCB_FIND_MAP_BLOCK(pin, pin_map, block) \
                    _cyhal_scb_find_map(pin, pin_map, sizeof(pin_map)/sizeof(cyhal_resource_pin_mapping_t), block)
#define _CYHAL_SCB_CHECK_AFFILIATION(pin, pin_map) \
                    _cyhal_scb_check_pin_affiliation(pin, pin_map, sizeof(pin_map)/sizeof(cyhal_resource_pin_mapping_t))

/**
 * Function pointer to determine a specific scb instance can is ready for low power transition.
 */
typedef bool (*cyhal_scb_instance_pm_callback)(void *obj_ptr, cyhal_syspm_callback_state_t state, cy_en_syspm_callback_mode_t pdl_mode);

/** Updates data in cyhal_scb_config_structs and cyhal_scb_config_modes_t structs based on block_num proveded
 * @param[in] block_num Index of SCB block which data to be updated
 * @param[in] obj       SCB-based driver object (cyhal_uart_t, cyhal_spi_t, cyhal_i2c_t or cyhal_ezi2c_t)
 */
void _cyhal_scb_update_instance_data(uint8_t block_num, void *obj, cyhal_scb_instance_pm_callback pm_callback);

/** Whether power management transition is pending and communication should be suspended. */
bool _cyhal_scb_pm_transition_pending(void);

/** Finds the en_clk_dst_t clock connection index for provided SCB block number
 *
 * @param[in] block_num Index of SCB block
 * @return en_clk_dst_t clock connection index
 */
static inline en_clk_dst_t _cyhal_scb_get_clock_index(uint32_t block_num)
{
    en_clk_dst_t clk;
    // PSOC6A256K does not have SCB 3
    #if defined(CY_DEVICE_PSOC6A256K)
    if (block_num < 3)
        clk = (en_clk_dst_t)((uint32_t)_CYHAL_SCB0_PCLK_CLOCK + block_num);
    else
        clk = (en_clk_dst_t)((uint32_t)_CYHAL_SCB0_PCLK_CLOCK + block_num -1);
    #else
        clk = (en_clk_dst_t)((uint32_t)_CYHAL_SCB0_PCLK_CLOCK + block_num);
    #endif
    return clk;
}

#if defined(__cplusplus)
}
#endif

/** \} group_hal_impl_scb_common */
/** \endcond */
