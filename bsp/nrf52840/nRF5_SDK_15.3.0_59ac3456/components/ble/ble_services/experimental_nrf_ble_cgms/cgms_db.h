/**
 * Copyright (c) 2012 - 2019, Nordic Semiconductor ASA
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
 * @defgroup ble_sdk_srv_cgms_db Continuous Glucose Monitoring Service database
 * @{
 * @ingroup ble_cgms
 *
 * @brief Continuous Glucose Monitoring Service database module.
 *
 * @details This module implements a database of stored glucose measurement values.
 *          This database is meant as an example of a database that the @ref ble_cgms can use.
 *          Replace this module if this implementation does not suit
 *          your application. Any replacement implementation should follow the API below to ensure
 *          that the qualification of the @ref ble_cgms is not compromised.
 */

#ifndef BLE_CGMS_DB_H__
#define BLE_CGMS_DB_H__

#include "sdk_errors.h"
#include "nrf_ble_cgms.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CGMS_DB_MAX_RECORDS 100 // !< Number of records that can be stored in the database.


/**@brief Function for initializing the glucose record database.
 *
 * @retval NRF_SUCCESS If the database was successfully initialized.
 */
ret_code_t cgms_db_init(void);


/**@brief Function for getting the number of records in the database.
 *
 * @return The number of records in the database.
 */
uint16_t cgms_db_num_records_get(void);


/**@brief Function for getting a specific record from the database.
 *
 * @param[in]  record_num Index of the record to retrieve.
 * @param[out] p_rec      Pointer to the record structure to which the retrieved record is copied.
 *
 * @retval NRF_SUCCESS If the record was successfully retrieved.
 */
ret_code_t cgms_db_record_get(uint8_t record_num, ble_cgms_rec_t * p_rec);


/**@brief Function for adding a record at the end of the database.
 *
 * @param[in] p_rec  Pointer to the record to add to the database.
 *
 * @retval NRF_SUCCESS If the record was successfully added to the database.
 */
ret_code_t cgms_db_record_add(ble_cgms_rec_t * p_rec);


/**@brief Function for deleting a database entry.
 *
 * @details This call deletes an record from the database.
 *
 * @param[in] record_num  Index of the record to delete.
 *
 * @retval NRF_SUCCESS If the record was successfully deleted from the database.
 */
ret_code_t cgms_db_record_delete(uint8_t record_num);


#ifdef __cplusplus
}
#endif

#endif // BLE_CGMS_DB_H__

/** @} */
