/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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

#ifndef APP_USBD_TYPES_H__
#define APP_USBD_TYPES_H__

#include <stdint.h>

#include "sdk_errors.h"
#include "nrf_drv_usbd.h"
#include "app_usbd_request.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup app_usbd_types USB Device high level library variable types definition
 * @ingroup app_usbd
 *
 * @brief @tagAPI52840 All types used by @ref app_usbd are defined here.
 * This helps to avoid cross referencing into types in different files.
 * @{
 */

/**
 * @brief Change given value to 2 digits in BCD notation.
 *
 * @param[in] val The decimal value to be converted in the range from 0 to 99.
 * @return Calculated BCD value.
 */
#define APP_USBD_BCD_2_MAKE(val) (   \
    ((((val) %  100) / 10) * 0x10) + \
    ((((val) %   10) /  1) *  0x1)   \
    )

/**
 * @brief Change given decimal version values to 4 digits in BCD notation.
 *
 * USB specification uses 4 digits BCD version notation in many descriptors.
 * This macro changes 2 values to 4 BCD digits (one 16 bit value)
 * that describes version in USB standard.
 *
 * @param[in] major Major version.
 * @param[in] minor Minor version.
 *
 * @return Calculated 16 bit value with BCD representation of the version.
 */
#define APP_USBD_BCD_VER_MAKE(major, minor) \
    ((APP_USBD_BCD_2_MAKE(major) << 8) | APP_USBD_BCD_2_MAKE(minor))

/**
 * @brief Combine endpoint address and its interval.
 *
 * @param[in] address   Endpoint address
 * @param[in] interval  Endpoint interval
 * @return Combined address and interval.
 */
#define APP_USBD_EP_WITH_INTERVAL(address, interval)    \
    ((1UL << 16) | ((interval) << 8) | (address))

#define APP_USBD_EXTRACT_INTERVAL_VALUE(combined)       \
    (((combined) & 0xFF00) >> 8)

#define APP_USBD_EXTRACT_INTERVAL_FLAG(combined)        \
    (((combined) >> 16) & 0x01)

/**
 * @brief Events codes.
 *
 * Redefined application event codes.
 */
typedef enum
{
    APP_USBD_EVT_DRV_SOF        = NRF_DRV_USBD_EVT_SOF,        /**< See documentation for @ref NRF_DRV_USBD_EVT_SOF        */
    APP_USBD_EVT_DRV_RESET      = NRF_DRV_USBD_EVT_RESET,      /**< See documentation for @ref NRF_DRV_USBD_EVT_RESET      */
    APP_USBD_EVT_DRV_SUSPEND    = NRF_DRV_USBD_EVT_SUSPEND,    /**< See documentation for @ref NRF_DRV_USBD_EVT_SUSPEND    */
    APP_USBD_EVT_DRV_RESUME     = NRF_DRV_USBD_EVT_RESUME,     /**< See documentation for @ref NRF_DRV_USBD_EVT_RESUME     */
    APP_USBD_EVT_DRV_WUREQ      = NRF_DRV_USBD_EVT_WUREQ,      /**< See documentation for @ref NRF_DRV_USBD_EVT_WUREQ      */
    APP_USBD_EVT_DRV_SETUP      = NRF_DRV_USBD_EVT_SETUP,      /**< This event type has special structure. See @ref app_usbd_setup_evt_t */
    APP_USBD_EVT_DRV_EPTRANSFER = NRF_DRV_USBD_EVT_EPTRANSFER, /**< See documentation for @ref NRF_DRV_USBD_EVT_EPTRANSFER */

    APP_USBD_EVT_FIRST_POWER,                                  /**< First power event code - for internal static assert checking */

    APP_USBD_EVT_POWER_DETECTED,                               /**< See documentation for @ref NRF_DRV_POWER_USB_EVT_DETECTED        */
    APP_USBD_EVT_POWER_REMOVED,                                /**< See documentation for @ref NRF_DRV_POWER_USB_EVT_REMOVED         */
    APP_USBD_EVT_POWER_READY,                                  /**< See documentation for @ref NRF_DRV_POWER_USB_EVT_READY           */


    APP_USBD_EVT_FIRST_APP,                                    /**< First application event code - for internal static assert checking */

    APP_USBD_EVT_INST_APPEND = APP_USBD_EVT_FIRST_APP,         /**< The instance was attached to the library, any configuration action can be done now */
    APP_USBD_EVT_INST_REMOVE,                                  /**<
                                                                *   The instance is going to be removed, this event is called just before removing the instance.
                                                                *   This removing cannot be stopped.
                                                                */
    APP_USBD_EVT_STARTED,                                      /**< USBD library has just been started and functional - event passed to all instances, before USBD interrupts have been enabled */
    APP_USBD_EVT_STOPPED,                                      /**< USBD library has just been stopped and is not functional - event passed to all instances, after USBD interrupts have been disabled*/

    APP_USBD_EVT_STATE_CHANGED,                                /**<
                                                                *   Informs all the classes that base state has been changed.
                                                                *   This event is processed before setup stage that caused the state change finishes (before acknowledging it).
                                                                */

    APP_USBD_EVT_FIRST_INTERNAL = 0x80,                        /**< First internal event, used by the APP library internally. */

    APP_USBD_EVT_HFCLK_READY    = APP_USBD_EVT_FIRST_INTERNAL, /**< High frequency clock started */
    APP_USBD_EVT_START_REQ,                                    /**< Start requested */
    APP_USBD_EVT_STOP_REQ,                                     /**< Stop requested */
    APP_USBD_EVT_SUSPEND_REQ,                                  /**< Suspend request - HFCLK would be released and USBD peripheral clock would be disconnected */
    APP_USBD_EVT_WAKEUP_REQ,                                   /**< Wakeup request - start the whole wakeup generation. */
    APP_USBD_EVT_SETUP_SETADDRESS,                             /**<
                                                                *   Setup request to set address, separated from
                                                                *   regular EVT_SETUP because this request is
                                                                *   fully handled by hardware and for the software
                                                                *   it is only a notification about what happened
                                                                */

} app_usbd_event_type_t;



/**
 * @brief Specific application event structure.
 *
 * All the data required by the events that comes from the application level.
 */
typedef struct
{
    app_usbd_event_type_t type; //!< Event type
} app_usbd_evt_t;

/**
 * @brief Specific application event structure with setup structure included.
 *
 * This event structure would be used when @ref APP_USBD_EVT_DRV_SETUP
 * is passed to instance event handler.
 */
typedef struct
{
    app_usbd_event_type_t type;  //!< Event type
    app_usbd_setup_t      setup; //!< Setup structure
} app_usbd_setup_evt_t;


/**
 * @brief Complex event variable type.
 *
 * A variable that can store any kind of event.
 */
typedef union
{
    app_usbd_event_type_t type;      //!< Event type
    nrf_drv_usbd_evt_t    drv_evt;   //!< Events that comes directly from the driver.
                                     /**< Use this event structure only for event
                                      *   type < @ref APP_USBD_EVT_FIRST_APP
                                      */
    app_usbd_setup_evt_t  setup_evt; //!< Event structure with SETUP structure included.
                                     /**< This structure is used in connection with
                                      *   @ref APP_USBD_EVT_DRV_SETUP
                                      */
    app_usbd_evt_t        app_evt;   //!< Events that comes from the application driver.
                                     /**< Use this event structure only for event
                                      *   type >= @ref APP_USBD_EVT_FIRST_APP
                                      */
} app_usbd_complex_evt_t;


/**
 * @brief Internal event variable type.
 *
 * The variable type used for internal event processing.
 * This kind of event is the one that goes into the event queue.
 *
 * @note There is no setup event structure.
 *       This structure would be created when setup event is processed.
 *       The reason for that is the fact that setup event structure has high memory printout.
 */
typedef union
{
    app_usbd_event_type_t type;      //!< Event type
    nrf_drv_usbd_evt_t    drv_evt;   //!< Events that comes directly from the driver.
                                     /**< Use this event structure only for event
                                      *   type < @ref APP_USBD_EVT_FIRST_APP
                                      */
    app_usbd_evt_t        app_evt;   //!< Events that comes from the application driver.
                                     /**< Use this event structure only for event
                                      *   type >= @ref APP_USBD_EVT_FIRST_APP
                                      */
} app_usbd_internal_evt_t;


#ifdef DOXYGEN
/**
 * @brief Base instance of a USBD class.
 *
 * Any USBD class instance have to begin with this instance.
 * This may then be followed by any implementation dependent data.
 *
 * For an instance it should be possible to put whole structure into FLASH.
 *
 * @note This type is early defined as incomplete type.
 *       This is required for function declaration that takes the pointer
 *       to this structure but in second hand - it is also placed inside
 *       the instance structure.
 * @note The structure is defined in @file app_usbd_class_base.h.
 */
typedef struct {} app_usbd_class_inst_t;
#else
typedef struct app_usbd_class_inst_s app_usbd_class_inst_t;
#endif
/**
 * @brief Endpoint callback function.
 *
 * The function used by every class instance.
 * @param[in,out] p_inst  Instance of the class.
 * @param[in]     p_event Event to process.
 *
 * @note If given event is not supported by class, return @ref NRF_ERROR_NOT_SUPPORTED
 */
typedef ret_code_t (*app_usbd_ep_event_handler_t)(
        app_usbd_class_inst_t  const * const p_inst,
        app_usbd_complex_evt_t const * const p_event
    );

/**
 * @brief SOF interrupt callback function.
 *
 * @param[in]   framecnt    Number of current SOF frame.
 *
 * @sa app_usbd_class_sof_register
 */
typedef void (*app_usbd_sof_interrupt_handler_t)(uint16_t framecnt);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_TYPES_H__ */
