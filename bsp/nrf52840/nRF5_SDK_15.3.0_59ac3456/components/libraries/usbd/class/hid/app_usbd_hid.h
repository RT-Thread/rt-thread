/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
#ifndef APP_USBD_HID_H__
#define APP_USBD_HID_H__

#include <stdint.h>
#include <stdbool.h>

#include "sdk_common.h"
#include "nrf_atomic.h"
#include "app_usbd_hid_types.h"
#include "app_usbd.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup app_usbd_hid USB HID class
 * @ingroup app_usbd
 *
 * @brief @tagAPI52840 Module with generic HID event data processing.
 * @{
 */

#define APP_USBD_HID_IFACE_IDX 0    /**< @brief HID instance interface index.   */
#define APP_USBD_HID_EPIN_IDX  0    /**< @brief HID instance endpoint IN index. */
#define APP_USBD_HID_EPOUT_IDX 1    /**< @brief HID instance endpoint OUT index.*/

/**
 * @brief HID context state flags.
 *
 * Bit numbers in @ref app_usbd_hid_ctx_t::state_flags.
 */
typedef enum {
    APP_USBD_HID_STATE_FLAG_APPENDED          = 0, /**< State flag APPENDED.          */
    APP_USBD_HID_STATE_FLAG_STARTED           = 1, /**< State flag STARTED.           */
    APP_USBD_HID_STATE_FLAG_SUSPENDED         = 2, /**< State flag SUSPENDED.         */
    APP_USBD_HID_STATE_FLAG_TRANS_IN_PROGRESS = 3, /**< State flag TRANS_IN_PROGRESS. */
} app_usbd_hid_state_flag_t;

/**
 * @brief Events passed to user event handler.
 *
 * @note Example prototype of user event handler:
   @code
   void hid_user_ev_handler(app_usbd_class_inst_t const   * p_inst,
                            app_usbd_hid_mouse_user_event_t event);
   @endcode
 */
typedef enum {
    APP_USBD_HID_USER_EVT_SET_BOOT_PROTO,    /**< Event SET_BOOT_PROTOCOL.  */
    APP_USBD_HID_USER_EVT_SET_REPORT_PROTO,  /**< Event SET_REPORT_PROTOCOL.*/
    APP_USBD_HID_USER_EVT_OUT_REPORT_READY,  /**< Event OUT_REPORT_READY.   */
    APP_USBD_HID_USER_EVT_IN_REPORT_DONE,    /**< Event IN_REPORT_DONE.     */
} app_usbd_hid_user_event_t;


/**
 * @brief User event handler.
 *
 * @param[in] p_inst Class instance.
 * @param[in] event  User event.
 */
typedef void (*app_usbd_hid_user_ev_handler_t)(app_usbd_class_inst_t const * p_inst,
                                               app_usbd_hid_user_event_t event);

/**
 * @brief Idle report handler.
 *
 * @param[in] p_inst        Class instance.
 * @param[in] report_id     Number of report ID that needs idle transfer.
 */
typedef ret_code_t (*app_usbd_hid_idle_handler_t)(app_usbd_class_inst_t const * p_inst,
                                                  uint8_t report_id);

/**@brief HID unified interface*/
typedef struct {

    /**
     * @brief Function called on HID specific, GetReport request.
     *
     * This function should trigger data write to control pipe.
     *
     * @param[in] p_inst        Class instance.
     * @param[in] p_setup_ev    Setup event.
     *
     * @return                  Standard error code.
     */
    ret_code_t (*on_get_report)(app_usbd_class_inst_t const * p_inst,
                                app_usbd_setup_evt_t const * p_setup_ev);

    /**
     * @brief Function called on HID specific, SetReport request.
     *
     * This function should trigger data read from control pipe. This function is not required and
     * NULL could be pinned to this handler when output report is not defined in report descriptor.
     *
     * @param[in] p_inst        Class instance.
     * @param[in] p_setup_ev    Setup event.
     *
     * @return                  Standard error code.
     */
    ret_code_t (*on_set_report)(app_usbd_class_inst_t const * p_inst,
                                app_usbd_setup_evt_t const * p_setup_ev);

    /**
     * @brief Function called on IN endpoint transfer.
     *
     * This function should trigger next endpoint IN transfer if required.
     *
     * @param[in] p_inst        Class instance.
     *
     * @return                  Standard error code.
     */
    ret_code_t (*ep_transfer_in)(app_usbd_class_inst_t const * p_inst);

    /**
     * @brief Function called on OUT endpoint transfer.
     *
     * This function should should read data from OUT endpoint. This function is not required and
     * NULL could be pinned to this handler when class doesn't have OUT endpoint.
     *
     * @param[in] p_inst        Class instance.
     *
     * @return                  Standard error code.
     */
    ret_code_t (*ep_transfer_out)(app_usbd_class_inst_t const * p_inst);

    /**
     * @brief Function returns subclass descriptor size.
     *
     * @param[in] p_inst        Class instance.
     * @param[in] desc_num      Index of the subclass descriptor
     *
     * @return                  Size of descriptor
     */
    size_t (*subclass_length)(app_usbd_class_inst_t const * p_inst,
                              uint8_t                       desc_num);

    /**
     * @brief Function returns pointer to subclass descriptor data.
     *
     * @param[in] p_inst        Class instance.
     * @param[in] desc_num      Index of the subclass descriptor
     * @param[in] cur_byte      Index of required byte
     *
     * @return                  Pointer to requested byte in subclass descriptor
     */
    const uint8_t * (*subclass_data)(app_usbd_class_inst_t const * p_inst,
                                     uint8_t                       desc_num,
                                     uint32_t                      cur_byte);

    /**
     * @brief Function called on idle transfer
     *
     * This function should trigger next idle transfer.
     *
     * @param[in,out] p_inst        Instance of the class.
     * @param[in]     report_id     Number of report ID that needs idle transfer.
     *
     * @return  Standard error code.
     */
    ret_code_t (*on_idle)(app_usbd_class_inst_t const * p_inst, uint8_t report_id);
    
    ret_code_t (*set_idle_handler)(app_usbd_class_inst_t const * p_inst,
                                   app_usbd_hid_idle_handler_t handler);
} app_usbd_hid_methods_t;

/**
 * @brief HID report buffers.
 */
typedef struct {
    uint8_t * p_buff;
    size_t    size;
} app_usbd_hid_report_buffer_t;



/**@brief Define OUT report buffer structure @ref app_usbd_hid_report_buffer_t.
 *
 * @param name        Instance name.
 * @param rep_size    Output report size.
 */
#define APP_USBD_HID_GENERIC_GLOBAL_OUT_REP_DEF(name, rep_size)  \
    static uint8_t CONCAT_2(name, _buf)[(rep_size)];             \
    const app_usbd_hid_report_buffer_t name = {                  \
            .p_buff = CONCAT_2(name, _buf),                      \
            .size = sizeof(CONCAT_2(name, _buf)),                \
    }

/**
 * @brief HID subclass descriptor.
 */

typedef struct {
    size_t                size;
    app_usbd_descriptor_t type;
    uint8_t const * const p_data;
} app_usbd_hid_subclass_desc_t;

/**
 * @brief Initializer of HID report descriptor
 *
 * @param name  Report descriptor name
 * @param ...   Report descriptor data
 */

#define APP_USBD_HID_GENERIC_SUBCLASS_REPORT_DESC(name, ...)    \
    static uint8_t const CONCAT_2(name,  _data)[] =             \
        __VA_ARGS__                                             \
    ;                                                           \
    static const app_usbd_hid_subclass_desc_t name =            \
    {                                                           \
        sizeof(CONCAT_2(name, _data)),                          \
        APP_USBD_DESCRIPTOR_REPORT,                             \
        CONCAT_2(name,_data)                                    \
    }

/**
 * @brief Initializer of HID physical descriptor
 *
 * @param name  Physical descriptor name
 * @param ...   Physical descriptor data
 */

#define APP_USBD_HID_GENERIC_SUBCLASS_PHYSICAL_DESC(name, ...)  \
    static uint8_t const CONCAT_2(name,  _data)[] =             \
        __VA_ARGS__                                             \
    ;                                                           \
    static const app_usbd_hid_subclass_desc_t name =            \
    {                                                           \
        sizeof(CONCAT_2(name, _data)),                          \
        APP_USBD_DESCRIPTOR_PHYSICAL,                           \
        CONCAT_2(name,_data)                                    \
    }


/**
 * @brief USB HID instance.
 */
typedef struct {
    app_usbd_hid_subclass_desc_t const ** const p_subclass_desc; //!< HID subclass descriptors array.
    size_t subclass_desc_count;                                  //!< HID subclass descriptors count.

    app_usbd_hid_subclass_t subclass_boot;    //!< Boot device (see HID definition).
    app_usbd_hid_protocol_t protocol;         //!< HID protocol (see HID definition).

    app_usbd_hid_report_buffer_t       * p_rep_buffer_in;        //!< Report buffer IN.
    app_usbd_hid_report_buffer_t const * p_rep_buffer_out;       //!< Report buffer OUT (only one instance).
    app_usbd_hid_methods_t const       * p_hid_methods;          //!< Hid interface methods.
    app_usbd_hid_user_ev_handler_t       user_event_handler;     //!< User event handler.

    uint8_t * p_ep_interval;   //!< Endpoint intervals.
} app_usbd_hid_inst_t;

/**
 * @brief USB HID instance initializer @ref app_usbd_hid_inst_t.
 *
 * @param subclass_dsc      HID subclass descriptors.
 * @param sub_boot          Subclass boot. (@ref app_usbd_hid_subclass_t)
 * @param protocl           HID protocol. (@ref app_usbd_hid_protocol_t)
 * @param report_buff_in    Input report buffer list.
 * @param report_buff_out   Output report buffer.
 * @param user_ev_handler   @ref app_usbd_hid_user_ev_handler_t.
 * @param hid_methods       @ref app_usbd_hid_methods_t.
 * @param ep_list           List of endpoints and intervals
 * */

#define APP_USBD_HID_INST_CONFIG(subclass_dsc,               \
                                 sub_boot,                   \
                                 protocl,                    \
                                 report_buff_in,             \
                                 report_buff_out,            \
                                 user_ev_handler,            \
                                 hid_methods,                \
                                 ep_list)                    \
    {                                                        \
        .p_subclass_desc = subclass_dsc,                     \
        .subclass_desc_count = ARRAY_SIZE(subclass_dsc),     \
        .p_rep_buffer_in = report_buff_in,                   \
        .p_rep_buffer_out = report_buff_out,                 \
        .user_event_handler = user_ev_handler,               \
        .p_hid_methods = hid_methods,                        \
        .subclass_boot = sub_boot,                           \
        .protocol = protocl,                                 \
        .p_ep_interval = ep_list                             \
    }

/**
 * @brief HID internal context.
 * */
typedef struct {
    nrf_atomic_u32_t                state_flags;                                     //!< HID state flags @ref app_usbd_hid_state_flag_t.
    nrf_atomic_flag_t               access_lock;                                     //!< Lock flag to internal data.
    uint8_t                         idle_rate[APP_USBD_HID_REPORT_IDLE_TABLE_SIZE];  //!< HID idle rate (4ms units).
    app_usbd_hid_protocol_select_t  selected_protocol;                               //!< Currently selected HID protocol.
    app_usbd_hid_idle_handler_t     idle_handler;                                    //!< Idle report handler.
    uint32_t                        first_idle[APP_USBD_HID_REPORT_IDLE_TABLE_SIZE]; //!< Number of frame at first idle transaction.
    bool                            lock_idle[APP_USBD_HID_REPORT_IDLE_TABLE_SIZE];  //!< Lock flag to idle transactions.
    bool                            idle_on;                                         //!< Idle transactions flag.
    bool                            idle_id_report;                                  //!< Idle transactions with nonzero report id flag.
} app_usbd_hid_ctx_t;


/**
 * @brief Locks internal hid context.
 *
 * Simple semaphore functionality to prevent concurrent access from application and
 * interrupt to internal mouse data.
 *
 * @param[in] p_hid_ctx Internal hid context
 */
static inline void app_usbd_hid_access_lock(app_usbd_hid_ctx_t * p_hid_ctx)
{
    UNUSED_RETURN_VALUE(nrf_atomic_flag_set(&p_hid_ctx->access_lock));
    __DSB();
}


/**
 * @brief Unlocks internal hid context.
 *
 * Simple semaphore functionality to prevent concurrent access from application and
 * interrupt to internal mouse data.
 *
 * @param[in] p_hid_ctx Internal hid context.
 */
static inline void app_usbd_hid_access_unlock(app_usbd_hid_ctx_t * p_hid_ctx)
{
    UNUSED_RETURN_VALUE(nrf_atomic_flag_clear(&p_hid_ctx->access_lock));
    __DSB();
}

/**
 * @brief Tests whether internal lock is acquired.
 *
 * @param[in] p_hid_ctx Internal HID context.
 *
 * @retval true  Locked.
 * @retval false Unlocked.
 */
static inline bool app_usbd_hid_access_lock_test(app_usbd_hid_ctx_t * p_hid_ctx)
{
    return p_hid_ctx->access_lock != 0;
}

/**
 * @brief Set one of the HID internal state flags.
 *
 * @param[in] p_hid_ctx     Internal HID context.
 * @param[in] flag          Flag to set.
 */
static inline void app_usbd_hid_state_flag_set(app_usbd_hid_ctx_t * p_hid_ctx,
                                               app_usbd_hid_state_flag_t flag)
{
    UNUSED_RETURN_VALUE(nrf_atomic_u32_or(&p_hid_ctx->state_flags, 1u << flag));
}

/**
 * @brief Clear one of the HID internal state flags.
 *
 * @param[in] p_hid_ctx     Internal HID context.
 * @param[in] flag          Flag to clear.
 */
static inline void app_usbd_hid_state_flag_clr(app_usbd_hid_ctx_t * p_hid_ctx,
                                               app_usbd_hid_state_flag_t flag)
{
    UNUSED_RETURN_VALUE(nrf_atomic_u32_and(&p_hid_ctx->state_flags, ~(1u << flag)));
}


/**
 * @brief Test one of the HID internal state flags.
 *
 * @param[in] p_hid_ctx     Internal HID context.
 * @param[in] flag          Flag to test.
 *
 * @retval true  Flag is set.
 * @retval false Flag is not set.
 */
static inline bool app_usbd_hid_state_flag_test(app_usbd_hid_ctx_t * p_hid_ctx,
                                                app_usbd_hid_state_flag_t flag)
{
    return ((p_hid_ctx->state_flags >> flag) & 1) == 1;
}

/**
 * @brief Checks whether HID endpoint transfer required.
 *
 * @param[in] p_hid_ctx     Internal HID context.
 *
 * @retval true  Input endpoint transfer required.
 * @retval false Transfer in progress or not allowed.
 */
static inline bool app_usbd_hid_trans_required(app_usbd_hid_ctx_t * p_hid_ctx)
{
    if (app_usbd_hid_state_flag_test(p_hid_ctx, APP_USBD_HID_STATE_FLAG_SUSPENDED) != 0)
    {
        UNUSED_RETURN_VALUE(app_usbd_wakeup_req());
        return false;
    }

    return app_usbd_hid_state_flag_test(p_hid_ctx, APP_USBD_HID_STATE_FLAG_TRANS_IN_PROGRESS) == 0;
}

/**
 * @brief Validates internal hid state.
 *
 * HID Mouse has to receive some USBD events before functions from this module could be used.
 *
 * @param[in] p_hid_ctx Internal hid context.
 *
 * @retval true  State is valid.
 * @retval false State is invalid.
 */
static inline bool app_usbd_hid_state_valid(app_usbd_hid_ctx_t * p_hid_ctx)
{
    /*Check whether internal flags allow to enable mouse*/
    if ((app_usbd_hid_state_flag_test(p_hid_ctx, APP_USBD_HID_STATE_FLAG_APPENDED) == 0)  ||
        (app_usbd_hid_state_flag_test(p_hid_ctx, APP_USBD_HID_STATE_FLAG_STARTED) == 0))
    {
        return false;
    }

    return true;
}

/**
 * @brief HID generic event handler.
 *
 * This handler should process every class event after specific class handler.
 * This approach allow to handle some events in the same way in all HID sub-classes.
 *
 * @param[in] p_inst        Generic class instance.
 * @param[in] p_hinst       HID class instance.
 * @param[in] p_hid_ctx     HID context.
 * @param[in] p_event       Complex event structure.
 *
 * @return Standard error code.
 */
ret_code_t app_usbd_hid_event_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_hid_inst_t const * p_hinst,
                                      app_usbd_hid_ctx_t * p_hid_ctx,
                                      app_usbd_complex_evt_t const * p_event);


/**
 * @brief Returns IN report buffer.
 *
 * @param[in] p_hinst       HID class instance.
 *
 * @return Report buffer handle or NULL if report doesn't exist.
 */
app_usbd_hid_report_buffer_t * app_usbd_hid_rep_buff_in_get(app_usbd_hid_inst_t const * p_hinst);

/**
 * @brief Returns OUT report buffer.
 *
 * Output reports are handled in interrupt handler so only one buffer is required. Buffer returned by
 * this function has predefined size, which should be equal (maximum OUTPUT report size + 1). To receive
 * OUT report this function should be called on @ref APP_USBD_HID_USER_EVT_OUT_REPORT_READY event.
 *
 * @param[in] p_hinst       HID class instance.
 *
 * @return Report buffer handle or NULL if report doesn't exist.
 */
static inline app_usbd_hid_report_buffer_t const *
app_usbd_hid_rep_buff_out_get(app_usbd_hid_inst_t const * p_hinst)
{
    ASSERT(p_hinst);
    return p_hinst->p_rep_buffer_out;
}

/**
 * @brief Returns HID selected protocol.
 *
 * @param[in] p_hid_ctx     HID context.
 *
 * @return Currently selected protocol (@ref app_usbd_hid_protocol_select_t).
 */
static inline app_usbd_hid_protocol_select_t app_usbd_hid_selected_protocol_get(app_usbd_hid_ctx_t * p_hid_ctx)
{
    ASSERT(p_hid_ctx);
    return p_hid_ctx->selected_protocol;
}

/**
 * @brief Auxiliary function to access to HID IN endpoint address.
 *
 * @param[in] p_inst Class instance data.
 *
 * @return IN endpoint address.
 */
static inline nrf_drv_usbd_ep_t app_usbd_hid_epin_addr_get(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_class_iface_conf_t const * class_iface;
    class_iface = app_usbd_class_iface_get(p_inst, APP_USBD_HID_IFACE_IDX);

    app_usbd_class_ep_conf_t const * ep_cfg;
    ep_cfg = app_usbd_class_iface_ep_get(class_iface, APP_USBD_HID_EPIN_IDX);

    return app_usbd_class_ep_address_get(ep_cfg);
}

/**
 * @brief Auxiliary function to access to HID generic OUT endpoint address.
 *
 * @param[in] p_inst Class instance data.
 *
 * @return OUT endpoint address.
 */
static inline nrf_drv_usbd_ep_t  app_usbd_hid_epout_addr_get(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_class_iface_conf_t const * class_iface;
    class_iface = app_usbd_class_iface_get(p_inst, APP_USBD_HID_IFACE_IDX);

    app_usbd_class_ep_conf_t const * ep_cfg;
    ep_cfg = app_usbd_class_iface_ep_get(class_iface, APP_USBD_HID_EPOUT_IDX);

    return app_usbd_class_ep_address_get(ep_cfg);
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_HID_H__ */
