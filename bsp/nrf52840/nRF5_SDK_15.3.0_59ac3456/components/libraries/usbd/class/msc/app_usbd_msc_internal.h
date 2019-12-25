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
#ifndef APP_USBD_MSC_INTERNAL_H__
#define APP_USBD_MSC_INTERNAL_H__

#include "app_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup app_usbd_msc_internals USB MSC internals
 * @ingroup app_usbd_msc
 *
 * @brief @tagAPI52840 Internals of the USB MSC class.
 * @{
 */

/**
 * @brief Minimal serial string descriptor length.
 * */
#define APP_USBD_MSC_MINIMAL_SERIAL_STRING_SIZE (12 + 1)

/**
 * @brief Number of block buffers
 *
 * Number of buffers used for the transfer.
 * The library is designed to work with double buffering.
 * Not tested with other configuration.
 */
#define APP_USBD_MSC_BUFFER_CNT 2

/**
 * @brief Create the name of the block buffer
 *
 * @param instance_name The name of the MSC instance
 *
 * @return The name of the block buffer used with the instance
 */
#define APP_USBD_MSC_BUFFER_NAME(instance_name) CONCAT_2(instance_name, _block)

/**
 * @brief Create the name of the block device list
 *
 * @param instance_name The name of the MSC instance
 *
 * @return The name of the block device list
 */
#define APP_USBD_MSC_BLKDEVS_NAME(instance_name) CONCAT_2(instance_name, _blkdevs)

/**
 * @brief Forward declaration of Mass Storage Class type.
 *
 */
APP_USBD_CLASS_FORWARD(app_usbd_msc);

/*lint -save -e165*/
/**
 * @brief Forward declaration of @ref app_usbd_msc_user_event_e
 *
 */
enum app_usbd_msc_user_event_e;

/*lint -restore*/

/**
 * @brief User event handler.
 *
 * @param[in] p_inst    Class instance.
 * @param[in] event     User event.
 *
 * */
typedef void (*app_usbd_msc_user_ev_handler_t)(app_usbd_class_inst_t const *  p_inst,
                                               enum app_usbd_msc_user_event_e event);

/**
 * @brief MSC part of class instance data.
 */
typedef struct {
    void *                         p_block_buff;     //!< Block buffer
    size_t                         block_buff_size;  //!< Block buffer size (typically 512 bytes)
    size_t                         block_buff_count; //!< Number of buffers (typically 2)

    nrf_block_dev_t const **       pp_block_devs;    //!< Block devices list
    size_t                         block_devs_count; //!< Block device list size

    app_usbd_msc_user_ev_handler_t user_ev_handler;  //!< User event handler

    app_usbd_msc_subclass_t        subclass;         //!< MSC subclass
    app_usbd_msc_protocol_t        protocol;         //!< MSC protocol
} app_usbd_msc_inst_t;

/**
 * @brief Internal module state.
 */
typedef enum {
    APP_USBD_MSC_STATE_DISABLED,      /**< Internal module state DISABLED      */
    APP_USBD_MSC_STATE_IDLE,          /**< Internal module state IDLE          */
    APP_USBD_MSC_STATE_CBW,           /**< Internal module state CBW           */
    APP_USBD_MSC_STATE_CMD_IN,        /**< Internal module state CMD_IN        */
    APP_USBD_MSC_STATE_DATA_IN,       /**< Internal module state DATA_IN       */
    APP_USBD_MSC_STATE_DATA_OUT,      /**< Internal module state DATA_OUT      */
    APP_USBD_MSC_STATE_CSW,           /**< Internal module state CSW           */
    APP_USBD_MSC_STATE_UNSUPPORTED,   /**< Internal module state UNSUPPORTED   */
    APP_USBD_MSC_STATE_CBW_INVALID,   /**< Endpoint is stalled until
                                       *   the command @ref APP_USBD_MSC_REQ_BULK_RESET */
    APP_USBD_MSC_STATE_DEVICE_ERROR,  /**< Endpoint is stalled and it is required
                                       *   to send PE error when clearing */
} app_usbd_msc_state_t;

/**
 * @brief MSC context.
 *
 * */
typedef struct {
    app_usbd_msc_state_t state; //!< Internal module state

    app_usbd_msc_cbw_t cbw;     //!< SCSI command block wrapper
    app_usbd_msc_csw_t csw;     //!< SCSI Command status wrapper

    /** @brief Currently processed command with data */
    struct
    {
        /** @brief Buffer data */
        struct
        {
            uint8_t rd_idx;     //!< Buffer read index
            uint8_t d_count;    //!< Number of blocks inside the buffer ready to process
            uint8_t a_count;    //!< Number of blocks allocated in the buffer
        } buff;
        /** @brief Currently transfered block */
        struct
        {
            size_t   size_left;    //!< Number of bytes left to transfer
            size_t   datalen_left; //!< Number of bytes left that was requested by the host
            bool     pending;      //!< The flag marking the pending transfer
            bool     abort;        //!< Something fails during reading - abort transfer and mark an error,
                                   //!< Used for read access.
        } transfer;
        /** @brief The block currently processed by block device */
        struct
        {
            uint8_t  lun;          //!< The logical unit for current transfer block
            size_t   blk_size;     //!< The size of the block of the selected lun
            size_t   size_left;    //!< Number of bytes left to be processed by block device
            size_t   datalen_left; //!< Number of bytes left that was requested by the host
            uint32_t blk_idx;      //!< Current block index
            bool     pending;      //!< The flag marking the pending transfer
            bool     abort;        //!< Something fails during transfer - abort processing and mark an error,
                                   //!< Used for write access.
        } process;
    } current;

    /** @brief SCSI response container*/
    union {
        app_usbd_scsi_cmd_inquiry_resp_t        inquiry;        //!< @ref APP_USBD_SCSI_CMD_INQUIRY response
        app_usbd_scsi_cmd_requestsense_resp_t   requestsense;   //!< @ref APP_USBD_SCSI_CMD_REQUESTSENSE response
        app_usbd_scsi_cmd_readcapacity10_resp_t readcapacity10; //!< @ref APP_USBD_SCSI_CMD_READCAPACITY10 response
        app_usbd_scsi_cmd_modesense6_resp_t     modesense6;     //!< @ref APP_USBD_SCSI_CMD_MODESENSE6 response
        app_usbd_scsi_cmd_modesense10_resp_t    modesense10;    //!< @ref APP_USBD_SCSI_CMD_MODESENSE10 response
    } scsi_resp;

    uint16_t blk_dev_init_mask;     //!< Block devices init mask
} app_usbd_msc_ctx_t;


/**
 * @brief MSC configuration macro.
 *
 * Used by @ref APP_USBD_MSC_GLOBAL_DEF
 *
 * @param iface     Interface number.
 * @param endpoints Endpoint list.
 * */
#define APP_USBD_MSC_CONFIG(iface, endpoints) ((iface, BRACKET_EXTRACT(endpoints)))


/**
 * @brief Specific class constant data for MSC.
 *
 * @ref app_usbd_msc_inst_t
 */
#define APP_USBD_MSC_INSTANCE_SPECIFIC_DEC app_usbd_msc_inst_t inst;

/**
 * @brief Configures MSC instance.
 *
 * @param p_devs             Block devices list that is array of pointers of @ref nrf_block_dev_t type.
 * @param devs_cnt           Number of block devices connected.
 * @param p_buff             Block buffer.
 * @param block_size         Total size of the single block in the buffer.
 * @param block_cnt          Number of available block buffers.
 * @param user_event_handler User event handler.
 */
#define APP_USBD_MSC_INST_CONFIG(p_devs,                        \
                                 devs_cnt,                      \
                                 p_buff,                        \
                                 block_size,                    \
                                 block_cnt,                     \
                                 user_event_handler)            \
    .inst = {                                                   \
         .pp_block_devs    = (p_devs),                          \
         .block_devs_count = (devs_cnt),                        \
         .p_block_buff     = (p_buff),                          \
         .block_buff_size  = (block_size),                      \
         .block_buff_count = (block_cnt),                       \
         .user_ev_handler  = (user_event_handler),              \
         .subclass         = APP_USBD_MSC_SUBCLASS_TRANSPARENT, \
         .protocol         = APP_USBD_MSC_PROTOCOL_BULK,        \
    }

/**
 * @brief Specific class data for MSC.
 *
 * @ref app_usbd_msc_ctx_t
 * */
#define APP_USBD_MSC_DATA_SPECIFIC_DEC app_usbd_msc_ctx_t ctx;


/**
 * @brief MSC descriptors config macro.
 *
 * @param interface_number Interface number.
 * @param ...              Extracted endpoint list.
 * */
#define APP_USBD_MSC_DSC_CONFIG(interface_number, ...) {                 \
        APP_USBD_MSC_INTERFACE_DSC(interface_number,                     \
                                   APP_USBD_MSC_SUBCLASS_TRANSPARENT,    \
                                   APP_USBD_MSC_PROTOCOL_BULK)           \
        APP_USBD_MSC_EP_DSC(GET_VA_ARG_1(__VA_ARGS__),                   \
                            GET_VA_ARG_1(GET_ARGS_AFTER_1(__VA_ARGS__)), \
                            64)                                          \
}

/**
 * @brief Public MSC class interface.
 *
 * */
extern const app_usbd_class_methods_t app_usbd_msc_class_methods;

/**
 * @brief Global definition of mass storage class instance.
 */
#define APP_USBD_MSC_GLOBAL_DEF_INTERNAL(instance_name,                                 \
                                         interface_number,                              \
                                         user_ev_handler,                               \
                                         endpoint_list,                                 \
                                         blockdev_list,                                 \
                                         workbuffer_size)                               \
    static const nrf_block_dev_t * APP_USBD_MSC_BLKDEVS_NAME(instance_name)[] =         \
                                   { BRACKET_EXTRACT(blockdev_list) };                  \
    static uint32_t APP_USBD_MSC_BUFFER_NAME(instance_name)                             \
        [APP_USBD_MSC_BUFFER_CNT * CEIL_DIV(workbuffer_size, sizeof(uint32_t))];        \
    APP_USBD_CLASS_INST_GLOBAL_DEF(                                                     \
        instance_name,                                                                  \
        app_usbd_msc,                                                                   \
        &app_usbd_msc_class_methods,                                                    \
        APP_USBD_MSC_CONFIG(interface_number, endpoint_list),                           \
        (APP_USBD_MSC_INST_CONFIG(APP_USBD_MSC_BLKDEVS_NAME(instance_name),             \
                                  ARRAY_SIZE(APP_USBD_MSC_BLKDEVS_NAME(instance_name)), \
                                  APP_USBD_MSC_BUFFER_NAME (instance_name),             \
                                  sizeof(APP_USBD_MSC_BUFFER_NAME(instance_name))       \
                                         / APP_USBD_MSC_BUFFER_CNT,                     \
                                  APP_USBD_MSC_BUFFER_CNT,                              \
                                  user_ev_handler))                                     \
    )


/** @} */


#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_MSC_INTERNAL_H__ */
