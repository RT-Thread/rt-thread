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
#ifndef APP_USBD_MSC_TYPES_H__
#define APP_USBD_MSC_TYPES_H__

#include "app_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup app_usbd_msc_types USB MSC types
 * @ingroup app_usbd_msc
 *
 * @brief @tagAPI52840 Types used in the USB MSC class.
 * @{
 */

/** @brief MSC class definition in interface descriptor
 *
 *  @ref app_usbd_descriptor_iface_t::bInterfaceClass
 * */
#define  APP_USBD_MSC_CLASS                  0x08

/**
 * @brief MSC subclass possible value.
 */
typedef enum {
    APP_USBD_MSC_SUBCLASS_RBC          = 0x01,    /**< Reduced Block Commands */
    APP_USBD_MSC_SUBCLASS_ATAPI        = 0x02,    /**< CD/DVD devices         */
    APP_USBD_MSC_SUBCLASS_QIC_157      = 0x03,    /**< Tape devices           */
    APP_USBD_MSC_SUBCLASS_UFI          = 0x04,    /**< Floppy disk drives     */
    APP_USBD_MSC_SUBCLASS_SFF_8070I    = 0x05,    /**< Floppy disk drives     */
    APP_USBD_MSC_SUBCLASS_TRANSPARENT  = 0x06,    /**< Determined by INQUIRY  */
} app_usbd_msc_subclass_t;

/**
 * @brief MSC protocol possible value.
 *
 * @note The USB Mass Storage Class Control/Bulk/Interrupt (CBI) Transport specification is approved
 *       for use only with full-speed floppy disk drives. CBI shall not be used in high-speed
 *       capable devices.
 */
typedef enum {
    APP_USBD_MSC_PROTOCOL_CBI      = 0x00,    /**< Command/Bulk/Interrupt */
    APP_USBD_MSC_PROTOCOL_CBI_ALT  = 0x01,    /**< W/o command completion */
    APP_USBD_MSC_PROTOCOL_BULK     = 0x50,    /**< Bulk-only              */
} app_usbd_msc_protocol_t;

/**
 * @brief MSC USB requests @ref nrf_drv_usbd_setup_t::bmRequestType
 *
 * @note Requests are limited only to @ref APP_USBD_MSC_PROTOCOL_BULK protocol type.
 */
typedef enum {
    APP_USBD_MSC_REQ_BULK_RESET  = 0xFF, /**< Mass Storage Reset */
    APP_USBD_MSC_REQ_GET_MAX_LUN = 0xFE, /**< Get Max LUN        */
} app_usbd_msc_req_t;

#pragma pack(push, 1)

#define  APP_USBD_MSC_CBW_SIGNATURE     {'U', 'S', 'B', 'C'} /**< CBW signature      */
#define  APP_USBD_MSC_CBW_DIRECTION_IN  (1u <<7)             /**< CBW direction flag */

/**
 * @brief Command Block Wrapper (CBW).
 */
typedef struct {
    uint8_t signature[4];           /**< "USBC" (hex: 0x43425355 little-endian)        */
    uint8_t tag[4];                 /**< Unique command tag                            */
    uint8_t datlen[4];              /**< Number of bytes that host expects to transfer */
    uint8_t flags;                  /**< Bit 7: Direction=IN                           */
    uint8_t lun;                    /**< Logical Unit Number, equals to @ref app_usbd_msc_inst_t :: block_devs_count*/
    uint8_t cdb_length;             /**< Length of cdb field                           */
    uint8_t cdb[16];                /**< Command Data Block payload                    */
} app_usbd_msc_cbw_t;

#define  APP_USBD_MSC_CSW_SIGNATURE     {'U', 'S', 'B', 'S'} /**< CSW signature              */

#define  APP_USBD_MSC_CSW_STATUS_PASS   0x00                 /**< CSW status: Command Passed */
#define  APP_USBD_MSC_CSW_STATUS_FAIL   0x01                 /**< CSW status: Command Failed */
#define  APP_USBD_MSC_CSW_STATUS_PE     0x02                 /**< CSW status: Phase Error    */

/**
 * @brief Command Status Wrapper (CSW).
 */
typedef struct  {
    uint8_t signature[4];           /**< "USBS" (hex: 0x53425355 little-endian)               */
    uint8_t tag[4];                 /**< Unique command tag (@ref app_usbd_msc_cbw_t :: tag)  */
    uint8_t residue[4];             /**< Amount not transferred                               */
    uint8_t status;                 /**< Status of transfer                                   */
} app_usbd_msc_csw_t;

#pragma pack(pop)


/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_MSC_TYPES_H__ */
