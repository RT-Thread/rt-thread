/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
#ifndef APP_USBD_NRF_DFU_TRIGGER_INTERNAL_H__
#define APP_USBD_NRF_DFU_TRIGGER_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup app_usbd_nrf_dfu_trigger_internals USB Nordic DFU Trigger internals
 * @ingroup app_usbd_nrf_dfu_trigger
 *
 * @brief @tagAPI52840 Internals of the USB Nordic DFU Trigger class.
 * @{
 */

/**
 * @brief Forward declaration of Nordic DFU Trigger Class type
 *
 */
APP_USBD_CLASS_FORWARD(app_usbd_nrf_dfu_trigger);

/*lint -save -e165*/
/**
 * @brief Forward declaration of @ref app_usbd_nrf_dfu_trigger_user_event_e
 *
 */
enum app_usbd_nrf_dfu_trigger_user_event_e;

/*lint -restore*/

/**
 * @brief User event handler
 *
 * @param[in] p_inst    Class instance
 * @param[in] event     User event
 *
 * */
typedef void (*app_usbd_nrf_dfu_trigger_user_ev_handler_t)(
        app_usbd_class_inst_t const *              p_inst,
        enum app_usbd_nrf_dfu_trigger_user_event_e event);

/**
 * @brief Nordic DFU Trigger part of class instance data
 */
typedef struct {
    size_t const    sem_ver_size;   //!< Semantic string size
    uint16_t const  detach_timeout; //!< Detach timeout in ms - for compatibility with DFU spec.
    uint16_t const  transfer_size;  //!< Transfer size - for compatibility with DFU spec.
    uint16_t const  bcd_dfu;        //!< DFU spec version.
    uint8_t const * p_sem_ver;      //!< Pointer to semantic version string

    app_usbd_nrf_dfu_trigger_nordic_info_t const * p_dfu_info; //!< Pointer to Nordic DFU Info

    app_usbd_nrf_dfu_trigger_user_ev_handler_t user_ev_handler; //!< User event handler
} app_usbd_nrf_dfu_trigger_inst_t;

/**
 * @brief Internal module state
 *
 * @note For future compatibility with DFU class.
 */
typedef enum {
    APP_USBD_NRF_DFU_TRIGGER_STATE_IDLE,          /**< Internal module state IDLE          */
    APP_USBD_NRF_DFU_TRIGGER_STATE_DETACH,        /**< Internal module state DETACH        */
} app_usbd_nrf_dfu_trigger_state_t;

/**
 * @brief Nordic DFU Trigger context
 *
 * */
typedef struct {
    app_usbd_nrf_dfu_trigger_state_t state; //!< Internal module state
} app_usbd_nrf_dfu_trigger_ctx_t;


/**
 * @brief Nordic DFU Trigger configuration macro
 *
 * Used by @ref APP_USBD_NRF_DFU_TRIGGER_GLOBAL_DEF
 *
 * @param iface Interface number
 * */
#define APP_USBD_NRF_DFU_TRIGGER_CONFIG(iface) (iface)


/**
 * @brief Specific class constant data for Nordic DFU Trigger
 *
 * @ref app_usbd_nrf_dfu_trigger_inst_t
 */
#define APP_USBD_NRF_DFU_TRIGGER_INSTANCE_SPECIFIC_DEC app_usbd_nrf_dfu_trigger_inst_t inst;


/**
 * @brief Configures Nordic DFU Trigger instance
 *
 * @param user_event_handler    User event handler
 * @param p_nordic_dfu          Pointer to @ref app_usbd_nrf_dfu_trigger_nordic_info_t structure
 * @param sem_ver_str           Semantic version string
 * @param timeout               Detach timeout in ms - left for compatibility with USB DFU spec.
 * @param size                  Transfer size in bytes - left for compatibility with USB DFU spec.
 * @param bcd                   USB DFU specification version.
 */
#define APP_USBD_NRF_DFU_TRIGGER_INST_CONFIG(user_event_handler,                                   \
                                             p_nordic_dfu,                                         \
                                             sem_ver_str,                                          \
                                             timeout,                                              \
                                             size,                                                 \
                                             bcd)                                                  \
    .inst = {                                                                                      \
         .user_ev_handler   = user_event_handler,                                                  \
         .p_dfu_info        = p_nordic_dfu,                                                        \
         .p_sem_ver         = sem_ver_str,                                                         \
         .sem_ver_size      = sizeof(sem_ver_str),                                                 \
         .transfer_size     = size,                                                                \
         .detach_timeout    = timeout,                                                             \
         .bcd_dfu           = bcd,                                                                 \
    }

/**
 * @brief Specific class data for Nordic DFU Trigger
 *
 * @ref app_usbd_nrf_dfu_trigger_ctx_t
 * */
#define APP_USBD_NRF_DFU_TRIGGER_DATA_SPECIFIC_DEC app_usbd_nrf_dfu_trigger_ctx_t ctx;


/**
 * @brief Public Nordic DFU Trigger class interface
 */
extern const app_usbd_class_methods_t app_usbd_nrf_dfu_trigger_class_methods;

/**
 * @brief Global definition of Nordic DFU Trigger instance
 */
#define APP_USBD_NRF_DFU_TRIGGER_GLOBAL_DEF_INTERNAL(instance_name,                                \
                                                     interface_number,                             \
                                                     detach_timeout,                               \
                                                     transfer_size,                                \
                                                     p_nordic_dfu,                                 \
                                                     sem_ver_str,                                  \
                                                     user_ev_handler)                              \
    APP_USBD_CLASS_INST_NO_EP_GLOBAL_DEF(                                                          \
        instance_name,                                                                             \
        app_usbd_nrf_dfu_trigger,                                                                  \
        &app_usbd_nrf_dfu_trigger_class_methods,                                                   \
        APP_USBD_NRF_DFU_TRIGGER_CONFIG((interface_number)),                                       \
        (APP_USBD_NRF_DFU_TRIGGER_INST_CONFIG(user_ev_handler,                                     \
                                              p_nordic_dfu,                                        \
                                              sem_ver_str,                                         \
                                              detach_timeout,                                      \
                                              transfer_size,                                       \
                                              0x0110))                                             \
    )


/** @} */


#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_NRF_DFU_TRIGGER_INTERNAL_H__ */
