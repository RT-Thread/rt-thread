/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef NRF_CSENSE_H__
#define NRF_CSENSE_H__

#include <stdint.h>
#include "nrf.h"
#include "sdk_errors.h"
#include "app_timer.h"
#include "nrf_drv_csense.h"
#include "nrf_csense_macros.h"
#include "app_util.h"

/** @file
 *
 * @defgroup nrf_csense Capacitive sensor library
 * @{
 * @ingroup app_common
 *
 * @brief Module for using the capacitive sensor library with support for many instances of sliders, wheels, and buttons.
 */

/**
 * @brief Macro for returning the address of a variable.
 */
#define NRF_CSENSE_GET_INSTANCE_ID(instance) (&instance)

/**
 * @brief Statically allocate memory for the instance of a capacitive sensor.
 *
 * @param[in,out] name          Name of the capacitive sensor instance that will be created.
 * @param[in] p1                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 */
#define NRF_CSENSE_BUTTON_DEF(name, p1) NRF_CSENSE_INTERNAL_BUTTON_DEF(name, p1)

/**
 * @brief Macro for creating a 2-pad slider instance.
 *
 * @param[in,out] name          Name of the capacitive sensor instance that will be created.
 * @param[in] steps_no          Number of relative pads. It means that the slider in its handler will give values (1, steps_no).
 * @param[in] p1                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p2                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 */
#define NRF_CSENSE_SLIDER_2_DEF(name, steps_no, p1, p2) NRF_CSENSE_INTERNAL_SLIDER_2_DEF(name, steps_no, p1, p2)

/**
 * @brief Macro for creating a 3-pad slider instance.
 *
 * @param[in,out] name          Name of the capacitive sensor instance that will be created.
 * @param[in] steps_no          Number of relative pads. It means that the slider in its handler will give values (1, steps_no).
 * @param[in] p1                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p2                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p3                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 */
#define NRF_CSENSE_SLIDER_3_DEF(name, steps_no, p1, p2, p3) NRF_CSENSE_INTERNAL_SLIDER_3_DEF(name, steps_no, p1, p2, p3)

/**
 * @brief Macro for creating a 4-pad slider instance.
 *
 * @param[in,out] name          Name of the capacitive sensor instance that will be created.
 * @param[in] steps_no          Number of relative pads. It means that the slider in its handler will give values (1, steps_no).
 * @param[in] p1                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p2                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p3                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p4                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 */
#define NRF_CSENSE_SLIDER_4_DEF(name, steps_no, p1, p2, p3, p4) NRF_CSENSE_INTERNAL_SLIDER_4_DEF(name, steps_no, p1, p2, p3, p4)

/**
 * @brief Macro for creating a 5-pad slider instance.
 *
 * @param[in,out] name          Name of the capacitive sensor instance that will be created.
 * @param[in] steps_no          Number of relative pads. It means that the slider in its handler will give values (1, steps_no).
 * @param[in] p1                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p2                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p3                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p4                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p5                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 */
#define NRF_CSENSE_SLIDER_5_DEF(name, steps_no, p1, p2, p3, p4, p5) NRF_CSENSE_INTERNAL_SLIDER_5_DEF(name, steps_no, p1, p2, p3, p4, p5)

/**
 * @brief Macro for creating a 3-pad wheel instance.
 *
 * @param[in,out] name          Name of the capacitive sensor instance that will be created.
 * @param[in] steps_no          Number of relative pads. It means that the slider in its handler will give values (1, steps_no).
 * @param[in] p1                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p2                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p3                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 */
#define NRF_CSENSE_WHEEL_3_DEF(name, steps_no, p1, p2, p3) NRF_CSENSE_INTERNAL_WHEEL_3_DEF(name, steps_no, p1, p2, p3)

/**
 * @brief Macro for creating a 4-pad wheel instance.
 *
 * @param[in,out] name          Name of the capacitive sensor instance that will be created.
 * @param[in] steps_no          Number of relative pads. It means that the slider in its handler will give values (1, steps_no).
 * @param[in] p1                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p2                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p3                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p4                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 */
#define NRF_CSENSE_WHEEL_4_DEF(name, steps_no, p1, p2, p3, p4) NRF_CSENSE_INTERNAL_WHEEL_4_DEF(name, steps_no, p1, p2, p3, p4)

/**
 * @brief Macro for creating a 5-pad wheel instance.
 *
 * @param[in,out] name          Name of the capacitive sensor instance that will be created.
 * @param[in] steps_no          Number of relative pads. It means that the slider in its handler will give values (1, steps_no).
 * @param[in] p1                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p2                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p3                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p4                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 * @param[in] p5                Pair of two arguments: threshold and analog_input_number. Must be passed as (analog_input_number, threshold).
 */
#define NRF_CSENSE_WHEEL_5_DEF(name, steps_no, p1, p2, p3, p4, p5) NRF_CSENSE_INTERNAL_WHEEL_5_DEF(name, steps_no, p1, p2, p3, p4, p5)

/**
 * @cond (NODOX)
 * @defgroup nrf_csense_internal Auxiliary internal types declarations
 * @brief Module for internal usage inside the library only.
 * @details These definitions are available to the user, but they should not
 * be accessed directly. Use the API to access them.
 * @{
 *
 */

     /*
      * @brief Forward declaration of capacitive sensor instance.
      */
    typedef struct nrf_csense_instance_s nrf_csense_instance_t;

    /*
     * @brief Forward declaration of a capacitive sensor pad.
     */
    typedef struct nrf_csense_pad_s nrf_csense_pad_t;

    /**
     * @brief Structure with pointer to min and max values measured on pads.
     */
    typedef struct
    {
        uint16_t                   max_value;                //!< Max value measured on pads.
        uint16_t                   min_value;                //!< Min value measured on pads.
    }nrf_csense_min_max_t;

    /**
     * @brief Structure with single instance parameters. This can be either a slider or a button.
     */
    struct nrf_csense_instance_s
    {
        nrf_csense_instance_t *     p_next_instance;            //!< Pointer to the next instance.
        nrf_csense_pad_t *          p_nrf_csense_pad;           //!< Pointer to the first pad of the module.
        nrf_csense_min_max_t *      min_max;                    //!< Structure with pointers to min and max values measured on pads.
        uint16_t                    steps;                      //!< Number of relative pads. It means that the slider in its handler will give values (1, steps_no).
        uint8_t                     number_of_pads;             //!< Number of pads that the instance is using.
        bool                        is_active;                  //!< Flag to indicate if the instance is active.
        bool                        is_touched;                 //!< Flag to indicate if the instance is touched.
        void *                      p_context;                  //!< General purpose pointer.
    };

    /* Structure with single pad parameters used for initialization. */
    struct nrf_csense_pad_s
    {
        nrf_csense_pad_t *          p_next_pad;                 //!< Pointer to the next pad.
        uint16_t                    threshold;                  //!< Threshold voltage on pad/time of charging to decide if the pad was touched.
        uint8_t                     pad_index;                  //!< Index of the pad.
        uint8_t                     analog_input_number;        //!< Analog input connected to the pad.
    };

/** @}
 * @endcond
 */

/**
 * @brief Enum for nrf_csense events.
 */
typedef enum
{
    NRF_CSENSE_BTN_EVT_PRESSED,                                 //!< Event for pad pressed.
    NRF_CSENSE_BTN_EVT_RELEASED,                                //!< Event for pad released.
    NRF_CSENSE_SLIDER_EVT_PRESSED,                              //!< Event for pad pressed.
    NRF_CSENSE_SLIDER_EVT_RELEASED,                             //!< Event for pad released.
    NRF_CSENSE_SLIDER_EVT_DRAGGED,                              //!< Event for pad dragged.
}nrf_csense_evt_type_t;

/**
 * @brief Structure with slider event data including the measured step.
 */
typedef struct
{
    uint16_t step;                                              //!< Measured step.
} nrf_csense_slider_evt_t;

/**
 * @brief Event data union for nrf_csense events.
 */
typedef union
{
    nrf_csense_slider_evt_t slider;                             //!< Structure with slider event data including the measured step.
} nrf_csense_evt_param_t;

/**
 * @brief Structure with event parameters.
 */
typedef struct
{
    nrf_csense_evt_type_t       nrf_csense_evt_type;            //!< Type of event.
    nrf_csense_instance_t *     p_instance;                     //!< Pointer to instance.
    nrf_csense_evt_param_t      params;                         //!< Event data union for nrf_csense events.
}nrf_csense_evt_t;

/**
 * @brief Capacitive sensor handler type.
 */
typedef void (* nrf_csense_event_handler_t)(nrf_csense_evt_t * p_evt);

/**
 * @brief Function for setting a handler of the instance.
 *
 * @param [in] p_instance                           Pointer to the instance whose steps are going to be changed.
 * @param [in] p_context                            General purpose pointer. Will be passed to the callback function.
 */
__STATIC_INLINE void nrf_csense_instance_context_set(nrf_csense_instance_t * const p_instance, void * p_context)
{
    p_instance->p_context = p_context;
}

/**
 * @brief Function for initializing the module. After initialization, no instances are enabled.
 *
 * @param [in] event_handler                          Event handler for the Capacitive Sensor module.
 * @param [in] ticks                                  Time in app_timer ticks between next conversions.
 *
 * @retval NRF_ERROR_INVALID_PARAM                    If invalid parameter was provided.
 * @retval NRF_ERROR_INVALID_STATE                    If one of the used modules is in invalid state.
 * @retval NRF_ERROR_INTERNAL                         If an error occured while initializing one of the modules used by the capacitive sensor library.
 * @retval NRF_SUCCESS                                If the module was initialized successfully.
 */
ret_code_t nrf_csense_init(nrf_csense_event_handler_t event_handler, uint32_t ticks);

/**
 * @brief Function for uninitializing the module.
 *
 * @return Values returned by @ref nrf_drv_csense_uninit and @ref app_timer_stop.
 */
ret_code_t nrf_csense_uninit(void);

/**
 * @brief Function for adding an instance of capacitive sensor to a linked list.
 *
 * The function calls @ref nrf_csense_enable to enable the instance that was added to the linked list.
 *
 * @param [in] p_instance                            Pointer to the capacitive sensor instance. It is saved by the module and is used whenever the instance is referred.
 *
 * @return Values returned by @ref nrf_csense_enable.
 */
ret_code_t nrf_csense_add(nrf_csense_instance_t * const p_instance);

/**
 * @brief Function for enabling a single instance.
 *
 * @param [in,out] p_instance                        Pointer to the capacitive sensor instance. It is saved by the module and is used whenever the instance is referred.
 *
 * @return Values returned by @ref app_timer_start.
 */
ret_code_t nrf_csense_enable(nrf_csense_instance_t * const p_instance);

/**
 * @brief Function for disabling an instance.
 *
 * @param [in] p_instance                              Pointer to the instance to be disabled.
 *
 * @retval NRF_ERROR_INVALID_PARAM                     If the instance was already disabled.
 * @retval NRF_SUCCESS                                 If the instance was disabled successfully.
 */
ret_code_t nrf_csense_disable(nrf_csense_instance_t * const p_instance);

/**
 * @brief Function for setting ticks between next measurements.
 *
 * @param [in] ticks                                 New time between conversions in app_timer ticks.
 *
 * @retval NRF_ERROR_BUSY                             If the capacitive sensor was busy.
 * @retval NRF_ERROR_INVALID_PARAM                    If an invalid parameter was provided.
 * @retval NRF_ERROR_INVALID_STATE                    If app_timer was in invalid state.
 * @retval NRF_SUCCESS                                If ticks were set successfully.
 */
ret_code_t nrf_csense_ticks_set(uint32_t ticks);

/**
 * @brief Function for setting steps of an instance.
 *
 * Note that you have do disable the instance before you can change its number of steps.
 *
 * @param [in] p_instance                           Pointer to the instance whose steps are going to be changed.
 * @param [in] steps                                New steps value.
 *
 * @retval NRF_ERROR_BUSY                           If the capacitive sensor was busy.
 * @retval NRF_SUCCESS                              If steps were set successfully.
 */
ret_code_t nrf_csense_steps_set(nrf_csense_instance_t  * const p_instance, uint16_t steps);


/** @} */

#endif //NRF_CSENSE_H__
