/***************************************************************************//**
* \file cyhal_tcpwm_common.h
*
* \brief
* Code shared between the Infineon Timer/Counter and PWM.
*
********************************************************************************
* \copyright
* Copyright 2019-2021 Cypress Semiconductor Corporation (an Infineon company) or
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
 * \addtogroup group_hal_impl_tcpwm_common TCPWM Common Functionality
 * \ingroup group_hal_impl
 * \{
 * Code shared between the Infineon Timer / Counter and PWM.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cyhal_hw_types.h"
#include "cyhal_interconnect.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

// Value comes from IP limitation
#define _CYHAL_TCPWM_MAX_GRPS_PER_IP_BLOCK  (4u)

#if defined(CY_IP_MXTCPWM_INSTANCES) || defined(CY_IP_M0S8TCPWM_INSTANCES)

#if defined(CY_IP_MXTCPWM_INSTANCES)
    #if (CY_IP_MXTCPWM_VERSION == 1)
        // Total number of TCPWM groups
        #define _CYHAL_TCPWM_INSTANCES     CY_IP_MXTCPWM_INSTANCES
        // Counter number relative to the start of the IP block
        #define _CYHAL_TCPWM_CNT_NUMBER(resource) ((resource).channel_num)
        // Cobvert driver 'block' to IP block
        #define _CYHAL_TCPWM_GET_IP_BLOCK(block) (block)
    #else // (CY_IP_MXTCPWM_VERSION >= 2)
        #define _CYHAL_TCPWM_GET_IP_BLOCK(block) ((block) / _CYHAL_TCPWM_MAX_GRPS_PER_IP_BLOCK)
        // Used to grab the group index relative to its IP block
        #define _CYHAL_TCPWM_GET_GRP(block) ((block) % _CYHAL_TCPWM_MAX_GRPS_PER_IP_BLOCK)
        #if (CY_IP_MXTCPWM_INSTANCES == 1)
            #define _CYHAL_TCPWM_INSTANCES     TCPWM_GRP_NR
            #define _CYHAL_TCPWM_CNT_NUMBER(resource) (((resource).block_num << 8) | (resource).channel_num)
        #elif (CY_IP_MXTCPWM_INSTANCES == 2)
            #define _CYHAL_TCPWM_INSTANCES     (TCPWM0_GRP_NR + TCPWM1_GRP_NR)
            // This is based on the model of 4x continuous groups mapping to x IP blocks (0-3 to 1, 4-7 to 2, etc)
            #define _CYHAL_TCPWM_CNT_NUMBER(resource) ((((resource).block_num % _CYHAL_TCPWM_MAX_GRPS_PER_IP_BLOCK) << 8) | (resource).channel_num)
        #else
            #warning Unhandled TCPWM instance count
        #endif
    #endif
#elif defined(CY_IP_M0S8TCPWM_INSTANCES)
    #define _CYHAL_TCPWM_CNT_NUMBER(resource) ((resource).channel_num)
    #define _CYHAL_TCPWM_INSTANCES     CY_IP_M0S8TCPWM_INSTANCES
    #define _CYHAL_TCPWM_GET_IP_BLOCK(block) (block)
#endif

// Used to adjust block value for indexing _CYHAL_TCPWM_DATA[] and other arrays which do not include indexes for empty blocks
#if (CY_IP_MXTCPWM_VERSION == 2)
    #if (CY_IP_MXTCPWM_INSTANCES == 1)
        #define _CYHAL_TCPWM_ADJUST_BLOCK_INDEX(block) (block)
    #elif (CY_IP_MXTCPWM_INSTANCES == 2)
        #define _CYHAL_TCPWM_ADJUST_BLOCK_INDEX(block)    ((_CYHAL_TCPWM_GET_IP_BLOCK(block) == 0) ? (block) : (_CYHAL_TCPWM_GET_GRP(block) + TCPWM0_GRP_NR))
    #else
        #warning Unhandled TCPWM instance count
    #endif
#else
    #define _CYHAL_TCPWM_ADJUST_BLOCK_INDEX(block) (block)
#endif

#if defined(CY_IP_MXTCPWM_INSTANCES)
#if (CY_IP_MXTCPWM_VERSION == 1)
    #if (CY_IP_MXTCPWM_INSTANCES == 0)
        #define _CYHAL_TCPWM_CHANNELS (0u)
    #elif (CY_IP_MXTCPWM_INSTANCES == 1)
        #define _CYHAL_TCPWM_CHANNELS (TCPWM0_CNT_NR)
    #elif (CY_IP_MXTCPWM_INSTANCES == 2)
        #define _CYHAL_TCPWM_CHANNELS (TCPWM0_CNT_NR + TCPWM1_CNT_NR)
    #else
        #warning Unhandled TCPWM instance count
    #endif
#else // (CY_IP_MXTCPWM_VERSION >= 2)
    #if (CY_IP_MXTCPWM_INSTANCES == 1)
        #if (TCPWM_GRP_NR == 0)
            #define _CYHAL_TCPWM_CHANNELS (0U)
        #elif (TCPWM_GRP_NR == 1)
            #define _CYHAL_TCPWM_CHANNELS (TCPWM_GRP_NR0_GRP_GRP_CNT_NR)
        #elif (TCPWM_GRP_NR == 2)
            #define _CYHAL_TCPWM_CHANNELS (TCPWM_GRP_NR0_GRP_GRP_CNT_NR + TCPWM_GRP_NR1_GRP_GRP_CNT_NR)
        #elif (TCPWM_GRP_NR == 3)
            #define _CYHAL_TCPWM_CHANNELS (TCPWM_GRP_NR0_GRP_GRP_CNT_NR + TCPWM_GRP_NR1_GRP_GRP_CNT_NR + TCPWM_GRP_NR2_GRP_GRP_CNT_NR)
        #elif (TCPWM_GRP_NR == 4)
            #define _CYHAL_TCPWM_CHANNELS (TCPWM_GRP_NR0_GRP_GRP_CNT_NR + TCPWM_GRP_NR1_GRP_GRP_CNT_NR + TCPWM_GRP_NR2_GRP_GRP_CNT_NR + TCPWM_GRP_NR3_GRP_GRP_CNT_NR)
        #endif
    #elif (CY_IP_MXTCPWM_INSTANCES == 2)
        #if (TCPWM0_GRP_NR == 0)
            #define _CYHAL_TCPWM0_CHANNELS (0U)
        #elif (TCPWM0_GRP_NR == 1)
            #define _CYHAL_TCPWM0_CHANNELS (TCPWM0_GRP_NR0_GRP_GRP_CNT_NR)
        #elif (TCPWM0_GRP_NR == 2)
            #define _CYHAL_TCPWM0_CHANNELS (TCPWM0_GRP_NR0_GRP_GRP_CNT_NR + TCPWM0_GRP_NR1_GRP_GRP_CNT_NR)
        #elif (TCPWM0_GRP_NR == 3)
            #define _CYHAL_TCPWM0_CHANNELS (TCPWM0_GRP_NR0_GRP_GRP_CNT_NR + TCPWM0_GRP_NR1_GRP_GRP_CNT_NR + TCPWM0_GRP_NR2_GRP_GRP_CNT_NR)
        #elif (TCPWM0_GRP_NR == 4)
            #define _CYHAL_TCPWM0_CHANNELS (TCPWM0_GRP_NR0_GRP_GRP_CNT_NR + TCPWM0_GRP_NR1_GRP_GRP_CNT_NR + TCPWM0_GRP_NR2_GRP_GRP_CNT_NR + TCPWM0_GRP_NR3_GRP_GRP_CNT_NR)
        #endif
        #ifndef _CYHAL_TCPWM0_CHANNELS
            #error "Unhandled TCPWM0_GRP_NR count"
        #endif
        #if (TCPWM1_GRP_NR == 0)
            #define _CYHAL_TCPWM1_CHANNELS (0U)
        #elif (TCPWM1_GRP_NR == 1)
            #define _CYHAL_TCPWM1_CHANNELS (TCPWM1_GRP_NR0_GRP_GRP_CNT_NR)
        #elif (TCPWM1_GRP_NR == 2)
            #define _CYHAL_TCPWM1_CHANNELS (TCPWM1_GRP_NR0_GRP_GRP_CNT_NR + TCPWM1_GRP_NR1_GRP_GRP_CNT_NR)
        #elif (TCPWM1_GRP_NR == 3)
            #define _CYHAL_TCPWM1_CHANNELS (TCPWM1_GRP_NR0_GRP_GRP_CNT_NR + TCPWM1_GRP_NR1_GRP_GRP_CNT_NR + TCPWM1_GRP_NR2_GRP_GRP_CNT_NR)
        #elif (TCPWM1_GRP_NR == 4)
            #define _CYHAL_TCPWM1_CHANNELS (TCPWM1_GRP_NR0_GRP_GRP_CNT_NR + TCPWM1_GRP_NR1_GRP_GRP_CNT_NR + TCPWM1_GRP_NR2_GRP_GRP_CNT_NR + TCPWM1_GRP_NR3_GRP_GRP_CNT_NR)
        #endif
        #ifndef _CYHAL_TCPWM1_CHANNELS
            #error "Unhandled TCPWM1_GRP_NR count"
        #endif

        #define _CYHAL_TCPWM_CHANNELS (_CYHAL_TCPWM0_CHANNELS + _CYHAL_TCPWM1_CHANNELS)
    #else
        #warning Unhandled TCPWM instance count
    #endif
#endif
#elif defined(CY_IP_M0S8TCPWM_INSTANCES)
    #if (CY_IP_M0S8TCPWM_INSTANCES == 1)
        #define _CYHAL_TCPWM_CHANNELS (TCPWM_CNT_NR)
    #else
        #warning Unhandled TCPWM instance count
    #endif
#endif

#if (CY_IP_MXTCPWM_VERSION == 1U)
    extern const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET[1];
    extern const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[1];
#elif (CY_IP_MXTCPWM_VERSION == 2U)
    // PSoC™ 6 devices with trigmux vers2 also have a number of reserved input
    // lines defined by TCPWM_TR_ONE_CNT_NR.
    #if (CY_IP_MXTCPWM_INSTANCES == 1)
    extern const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET[1];
    extern const uint16_t  _CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[1];
    #elif (CY_IP_MXTCPWM_INSTANCES == 2)
    extern const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET[2];
    extern const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[2];
    #else
    #warning Unhandled TCPWM instance count
    #endif
#else // (CY_IP_M0S8TCPWM_VERSION == 2)
    // PSoC™ 4 devices have a number of reserved input lines coming directly from
    // GPIO triggers (depending on exact architecture).
    #if defined(CY_DEVICE_PSOC4AS1)
        // 12 GPIO trigger lines reserved (but some may be unused, depending on
        // pin package)
        extern const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET[1];
        extern const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[1];
    #else
        // 7 GPIO trigger lines reserved (but some may be unused, depending on
        // pin package)
        extern const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET[1];
        extern const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[1];
    #endif
#endif

/** \addtogroup group_hal_results_tcpwm TCPWM HAL Results
 *  TCPWM specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** Bad argument. eg: null pointer */
#define CYHAL_TCPWM_RSLT_ERR_BAD_ARGUMENT                   \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_IMPL_TCPWM, 0))
/** Failed to find free input signal */
#define CYHAL_TCPWM_RSLT_ERR_NO_FREE_INPUT_SIGNALS          \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_IMPL_TCPWM, 1))
/** Failed to find free output signal */
#define CYHAL_TCPWM_RSLT_ERR_NO_FREE_OUTPUT_SIGNALS         \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_IMPL_TCPWM, 2))

/**
 * \}
 */

/** TCPWM/counter input signal */
typedef enum
{
    CYHAL_TCPWM_INPUT_START,    //!< Start signal
    CYHAL_TCPWM_INPUT_STOP,     //!< Stop signal
    CYHAL_TCPWM_INPUT_RELOAD,   //!< Reload signal
    CYHAL_TCPWM_INPUT_COUNT,    //!< Count signal
    CYHAL_TCPWM_INPUT_CAPTURE,  //!< Capture signal
} cyhal_tcpwm_input_t;

/** The number of unique TCPWM inputs as defined by cyhal_tcpwm_input_t */
#define _CYHAL_TCPWM_INPUTS     5

/** TCPWM/counter output signal */
typedef enum
{
    CYHAL_TCPWM_OUTPUT_OVERFLOW,       //!< Overflow signal
    CYHAL_TCPWM_OUTPUT_UNDERFLOW,      //!< Underflow signal
    CYHAL_TCPWM_OUTPUT_COMPARE_MATCH,  //!< Compare match signal
    CYHAL_TCPWM_OUTPUT_TERMINAL_COUNT, //!< Terminal count signal (logical OR of overflow and underflow signal)
    CYHAL_TCPWM_OUTPUT_LINE_OUT,       //!< Line out signal
} cyhal_tcpwm_output_t;

/** The number of unique TCPWM outputs as defined by cyhal_tcpwm_output_t */
#define _CYHAL_TCPWM_OUTPUTS     5

/** Handler for TCPWM interrupts */
typedef void(*_cyhal_tcpwm_event_callback_t)(void *callback_arg, int event);

/** Holds data about a single TCPWM */
typedef struct {
    TCPWM_Type*  base; //!< TCPWM base
    en_clk_dst_t clock_dst; //!< TCPWM clock connections base
    uint32_t     max_count; //!< TCPWM counter width
    uint8_t      num_channels; //!< Number of channels on the TCPWM
    uint8_t      channel_offset; //!< Offset from channels on previous TCPWM
#if !defined(COMPONENT_CAT1C)
    uint8_t      isr_offset; //!< TCPWM base IRQn (channel 0 IRQn)
#else
    /** CAT1C device has number of interrupts, which exceeds uint8_t type max. value */
    uint16_t     isr_offset; //!< TCPWM base IRQn (channel 0 IRQn)
#endif // not CAT1C or CAT1C
} _cyhal_tcpwm_data_t;

/** Contains data about all of the TCPWMs */
extern const _cyhal_tcpwm_data_t _CYHAL_TCPWM_DATA[_CYHAL_TCPWM_INSTANCES];

#ifdef CY_DEVICE_PSOC6A256K
/** Contains bitfield of in use data for all TCPWM output trigger lines. There
 * are 2 available output lines per counter */
extern uint8_t _CYHAL_OUTPUT_TRIGGERS_USED[TCPWM_GRP_NR0_GRP_GRP_CNT_NR + TCPWM_GRP_NR1_GRP_GRP_CNT_NR];
#endif

/**
 * Free a timer/counter or a PWM object's shared data
 *
 * @param[in] obj The timer/counter or the PWM resource
 */
void _cyhal_tcpwm_free(cyhal_tcpwm_t *obj);

/** Initialize a timer/counter or PWM object's callback data.
 *
 * @param[in,out] tcpwm    The shared data struct between timer/counter and PWM
 */
void _cyhal_tcpwm_init_data(cyhal_tcpwm_t *tcpwm);

/** The TCPWM interrupt handler registration
 *
 * @param[in] resource      The timer/counter or PWM resource
 * @param[in] callback      The callback handler which will be invoked when the event occurs
 * @param[in] callback_arg  Generic argument that will be provided to the callback when called
 */
void _cyhal_tcpwm_register_callback(cyhal_resource_inst_t *resource, cy_israddress callback, void *callback_arg);

/** Configure TCPWM event enablement.
 *
 * @param[in] tcpwm          The shared data struct between timer/counter and PWM
 * @param[in] resource      The timer/counter or PWM resource
 * @param[in] event         The timer/counter or PWM event type
 * @param[in] intr_priority The priority for NVIC interrupt events
 * @param[in] enable        True to turn on events, False to turn off
 */
void _cyhal_tcpwm_enable_event(cyhal_tcpwm_t *tcpwm, cyhal_resource_inst_t *resource, uint32_t event, uint8_t intr_priority, bool enable);

/** Returns whether power management transition should be allowed.
 *
 * @return true if no tcpwm is actively blocking power mode transition
 */
bool _cyhal_tcpwm_pm_transition_pending(void);

/** Connects a source signal and configures and enables a TCPWM event to be
 * triggered from that signal. These TCPWM events can be configured
 * independently and connect to the same or different source signals.
 *
 * @param[in] obj      TCPWM HAL object
 * @param[in] source   Source signal obtained from another driver's cyhal_<PERIPH>_enable_output
 * @param[in] signal   The TCPWM input signal
 * @param[in] type     The edge type of the signal to connect
 * @return The status of the connection
 * */
cy_rslt_t _cyhal_tcpwm_connect_digital(cyhal_tcpwm_t *obj, cyhal_source_t source, cyhal_tcpwm_input_t signal, cyhal_edge_type_t type);

/** Enables the specified output signal from a TCPWM that will be triggered
 * when the corresponding event occurs. Multiple output signals can be
 * configured simultaneously.
 *
 * @param[in]  obj      TCPWM HAL object
 * @param[in]  signal   The TCPWM output signal
 * @param[out] source   Pointer to user-allocated source signal object which
 * will be initialized by enable_output. source should be passed to
 * (dis)connect_digital functions to (dis)connect the associated endpoints.
 * @return The status of the output enable
 * */
cy_rslt_t _cyhal_tcpwm_enable_output(cyhal_tcpwm_t *obj, cyhal_tcpwm_output_t signal, cyhal_source_t *source);

/** Disconnects a source signal and disables the corresponding input to a TCPWM
 *
 * @param[in] obj      TCPWM HAL object
 * @param[in] source   Source signal from cyhal_<PERIPH>_enable_output to disable
 * @param[in] signal   The TCPWM input signal
 * @return The status of the disconnection
 * */
cy_rslt_t _cyhal_tcpwm_disconnect_digital(cyhal_tcpwm_t *obj, cyhal_source_t source, cyhal_tcpwm_input_t signal);

/** Disables the specified output signal from a TCPWM.
 *
 * @param[in]  obj      TCPWM HAL object
 * @param[in]  resource TCPWM resource
 * @param[in]  signal   The TCPWM output signal
 * @return The status of the output disable
 * */
cy_rslt_t _cyhal_tcpwm_disable_output(cyhal_tcpwm_t *obj, cyhal_tcpwm_output_t signal);

#if (defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI)) && \
    ((CY_IP_MXTCPWM_VERSION == 1) || (CY_IP_MXTCPWM_VERSION == 2) || (CY_IP_M0S8TCPWM_VERSION == 2))
/** Get the destination reference for the provided TCPWM block and trigger
 *
 * @param[in]  block        TCPWM block number
 * @param[in]  trig_index   The trigger index to get the destination for
 * @return A destination that a signal can be connected to for the specified TCPWM block
 * */
cyhal_dest_t _cyhal_tpwm_calculate_dest(uint8_t block, uint8_t trig_index);
#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* defined(CY_IP_MXTCPWM_INSTANCES) || defined(CY_IP_M0S8TCPWM_INSTANCES) */

/** \} group_hal_impl_tcpwm_common */
/** \endcond */
