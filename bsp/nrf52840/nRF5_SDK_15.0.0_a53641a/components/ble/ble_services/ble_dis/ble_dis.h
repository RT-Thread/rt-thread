/**
 * Copyright (c) 2012 - 2018, Nordic Semiconductor ASA
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
/** @file
 *
 * @defgroup ble_dis Device Information Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief Device Information Service module.
 *
 * @details This module implements the Device Information Service.
 *          During initialization it adds the Device Information Service to the BLE stack database.
 *          It then encodes the supplied information, and adds the corresponding characteristics.
 *
 * @note Attention!
 *  To maintain compliance with Nordic Semiconductor ASA Bluetooth profile
 *  qualification listings, this section of source code must not be modified.
 */

#ifndef BLE_DIS_H__
#define BLE_DIS_H__

#include <stdint.h>
#include "ble_srv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup DIS_VENDOR_ID_SRC_VALUES Vendor ID Source values
 * @{
 */
#define BLE_DIS_VENDOR_ID_SRC_BLUETOOTH_SIG   1                 /**< Vendor ID assigned by Bluetooth SIG. */
#define BLE_DIS_VENDOR_ID_SRC_USB_IMPL_FORUM  2                 /**< Vendor ID assigned by USB Implementer's Forum. */
/** @} */

/**@brief System ID parameters */
typedef struct
{
    uint64_t manufacturer_id;                                   /**< Manufacturer ID. Only 5 LSOs shall be used. */
    uint32_t organizationally_unique_id;                        /**< Organizationally unique ID. Only 3 LSOs shall be used. */
} ble_dis_sys_id_t;

/**@brief IEEE 11073-20601 Regulatory Certification Data List Structure */
typedef struct
{
    uint8_t *  p_list;                                          /**< Pointer the byte array containing the encoded opaque structure based on IEEE 11073-20601 specification. */
    uint8_t    list_len;                                        /**< Length of the byte array. */
} ble_dis_reg_cert_data_list_t;

/**@brief PnP ID parameters */
typedef struct
{
    uint8_t  vendor_id_source;                                  /**< Vendor ID Source. see @ref DIS_VENDOR_ID_SRC_VALUES. */
    uint16_t vendor_id;                                         /**< Vendor ID. */
    uint16_t product_id;                                        /**< Product ID. */
    uint16_t product_version;                                   /**< Product Version. */
} ble_dis_pnp_id_t;

/**@brief Device Information Service init structure. This contains all possible characteristics
 *        needed for initialization of the service.
 */
typedef struct
{
    ble_srv_utf8_str_t             manufact_name_str;           /**< Manufacturer Name String. */
    ble_srv_utf8_str_t             model_num_str;               /**< Model Number String. */
    ble_srv_utf8_str_t             serial_num_str;              /**< Serial Number String. */
    ble_srv_utf8_str_t             hw_rev_str;                  /**< Hardware Revision String. */
    ble_srv_utf8_str_t             fw_rev_str;                  /**< Firmware Revision String. */
    ble_srv_utf8_str_t             sw_rev_str;                  /**< Software Revision String. */
    ble_dis_sys_id_t *             p_sys_id;                    /**< System ID. */
    ble_dis_reg_cert_data_list_t * p_reg_cert_data_list;        /**< IEEE 11073-20601 Regulatory Certification Data List. */
    ble_dis_pnp_id_t *             p_pnp_id;                    /**< PnP ID. */
    ble_srv_security_mode_t        dis_attr_md;                 /**< Initial Security Setting for Device Information Characteristics. */
} ble_dis_init_t;

/**@brief Function for initializing the Device Information Service.
 *
 * @details This call allows the application to initialize the device information service.
 *          It adds the DIS service and DIS characteristics to the database, using the initial
 *          values supplied through the p_dis_init parameter. Characteristics which are not to be
 *          added, shall be set to NULL in p_dis_init.
 *
 * @param[in]   p_dis_init   The structure containing the values of characteristics needed by the
 *                           service.
 *
 * @return      NRF_SUCCESS on successful initialization of service.
 */
uint32_t ble_dis_init(ble_dis_init_t const * p_dis_init);


#ifdef __cplusplus
}
#endif

#endif // BLE_DIS_H__

/** @} */
