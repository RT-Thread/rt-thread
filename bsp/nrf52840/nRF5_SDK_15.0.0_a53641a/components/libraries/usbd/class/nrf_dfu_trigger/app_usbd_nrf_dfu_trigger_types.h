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
#ifndef APP_USBD_NRF_DFU_TRIGGER_TYPES_H__
#define APP_USBD_NRF_DFU_TRIGGER_TYPES_H__

#include "app_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup app_usbd_nrf_dfu_trigger_types USB Nordic DFU Trigger types
 * @ingroup app_usbd_nrf_dfu_trigger
 *
 * @brief @tagAPI52840 Types used in the USB Nordic DFU Trigger class.
 * @{
 */

/** @brief Nordic DFU Trigger class definition in interface descriptor
 *
 *  @ref app_usbd_descriptor_iface_t::bInterfaceClass
 * */
#define APP_USBD_NRF_DFU_TRIGGER_CLASS 0xFF

/**
 * @brief Nordic DFU Trigger subclass possible value
 */
typedef enum {
    APP_USBD_NRF_DFU_TRIGGER_SUBCLASS          = 0x01,    /**< Device Firmware Upgrade Code */
} app_usbd_nrf_dfu_trigger_subclass_t;

/**
 * @brief Nordic DFU Trigger protocol possible value
 *
 * @note Only Run-time protocol is implemented, as DFU mode is covered by Nordic DFU.
 */
typedef enum {
    APP_USBD_NRF_DFU_TRIGGER_PROTOCOL_RUNTIME  = 0x01,    /**< Run-time Protocol */
} app_usbd_nrf_dfu_trigger_protocol_t;

/**
 * @brief Nordic DFU Trigger USB requests @ref nrf_drv_usbd_setup_t::bmRequestType
 *
 * @note Requests are limited only to @ref APP_USBD_NRF_DFU_TRIGGER_PROTOCOL_RUNTIME protocol type.
 */
typedef enum {
    APP_USBD_NRF_DFU_TRIGGER_REQ_DETACH      = 0x00, /**< Switch to DFU mode */
    APP_USBD_NRF_DFU_TRIGGER_REQ_NORDIC_INFO = 0x07, /**< Request Nordic DFU information */
    APP_USBD_NRF_DFU_TRIGGER_REQ_SEM_VER     = 0x08, /**< Request semantic version information */
} app_usbd_nrf_dfu_trigger_req_t;

/**
 * @brief Nordic DFU Trigger Functional Descriptor types.
 */
typedef enum {
    APP_USBD_NRF_DFU_TRIGGER_CS_FUNCTIONAL = 0x21, /**< Functional descriptor type.*/
} app_usbd_nrf_dfu_trigger_func_type_t;

/**
 * @brief Nordic DFU Trigger functional descriptor bmAttributes bit masks.
 *
 * @note For future compatibility with DFU class.
 */
typedef enum {
    APP_USBD_NRF_DFU_TRIGGER_BIT_CAN_DNLOAD    = 0x01, /**< bitCanDnload */
    APP_USBD_NRF_DFU_TRIGGER_BIT_CAB_UPLOAD    = 0x02, /**< bitCanUpload */
    APP_USBD_NRF_DFU_TRIGGER_BIT_MANI_TOLERANT = 0x04, /**< bitManifestationTolerant */
    APP_USBD_NRF_DFU_TRIGGER_BIT_WILL_DETACH   = 0x08, /**< bitWillDetach */
} app_usbd_nrf_dfu_trigger_bm_attributes_t;

#pragma pack(push, 1)

/**
 * @brief Nordic DFU Trigger Functional Descriptor
 */
typedef struct {
    uint8_t  bFunctionLength; //!< Size of this descriptor in bytes.
    uint8_t  bDescriptorType; //!< Descriptor type.
    uint8_t  bmAttributes;    //!< Attributes bits.
    uint16_t wDetachTimeOut;  //!< Device detach timeout - left for compatibility with USB DFU spec.
    uint16_t wTransferSize;   //!< Transfer size - left for compatibility with USB DFU spec.
    uint16_t bcdDFUVersion;   //!< DFU version.
} app_usbd_nrf_dfu_trigger_desc_func_t;

/**
 * @brief Nordic custom DFU information.
 */
typedef struct {
    uint32_t wAddress;          //!< Firmware start address.
    uint32_t wFirmwareSize;     //!< Firmware size.
    uint16_t wVersionMajor;     //!< Firmware version major.
    uint16_t wVersionMinor;     //!< Firmware version minor.
    uint32_t wFirmwareID;       //!< Firmware ID.
    uint32_t wFlashSize;        //!< Flash size.
    uint32_t wFlashPageSize;    //!< Flash page size.
} app_usbd_nrf_dfu_trigger_nordic_info_t;

#pragma pack(pop)


/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_NRF_DFU_TRIGGER_TYPES_H__ */
