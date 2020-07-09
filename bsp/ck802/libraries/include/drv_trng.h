/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
 * @file     drv_trng.h
 * @brief    header file for trng driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef _CSI_TRNG_H_
#define _CSI_TRNG_H_

#include "drv_common.h"
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


/// definition for trng handle.
typedef void *trng_handle_t;
/****** TRNG specific error codes *****/
typedef enum {
    TRNG_ERROR_MODE = 0,                   ///< Specified Mode not supported
} drv_trng_error_e;

/*----- TRNG Control Codes: Mode -----*/
typedef enum {
    TRNG_MODE_LOWPOWER              = 0,   ///< TRNG Low power Mode
    TRNG_MODE_NORMAL                       ///< TRNG Normal Mode
} trng_mode_e;

/**
\brief TRNG Status
*/
typedef struct {
    uint32_t busy                : 1;
    uint32_t data_valid          : 1;        ///< Data is valid flag
} trng_status_t;

/****** TRNG Event *****/
typedef enum {
    TRNG_EVENT_DATA_GENERATE_COMPLETE       = 0        ///< Get data from TRNG success
} trng_event_e;
typedef void (*trng_event_cb_t)(trng_event_e event);   ///< Pointer to \ref trng_event_cb_t : TRNG Event call back.

/**
\brief TRNG Device Driver Capabilities.
*/
typedef struct {
    uint32_t lowper_mode         : 1;        ///< supports low power mode
} trng_capabilities_t;

// Function documentation

/**
  \brief       get trng handle count.
  \return      trng handle count
*/
int32_t csi_trng_get_instance_count(void);

/**
  \brief       Initialize TRNG Interface. 1. Initializes the resources needed for the TRNG interface 2.registers event callback function
  \param[in]   idx  must not exceed return value of csi_trng_get_instance_count()
  \param[in]   cb_event  Pointer to \ref trng_event_cb_t
  \return      pointer to trng handle
*/
trng_handle_t csi_trng_initialize(int32_t idx, trng_event_cb_t cb_event);

/**
  \brief       De-initialize TRNG Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  trng handle to operate.
  \return      error code
*/
int32_t csi_trng_uninitialize(trng_handle_t handle);

/**
  \brief       Get driver capabilities.
  \param[in]   handle trng handle to operate.
  \return      \ref trng_capabilities_t
*/
trng_capabilities_t csi_trng_get_capabilities(trng_handle_t handle);

/**
  \brief       Get data from the TRNG.
  \param[in]   handle  trng handle to operate.
  \param[out]  data  Pointer to buffer with data get from TRNG
  \param[in]   num   Number of data items to obtain
  \return      error code
*/
int32_t csi_trng_get_data(trng_handle_t handle, void *data, uint32_t num);

/**
  \brief       Get TRNG status.
  \param[in]   handle  trng handle to operate.
  \return      TRNG status \ref trng_status_t
*/
trng_status_t csi_trng_get_status(trng_handle_t handle);


#ifdef __cplusplus
}
#endif

#endif /* _CSI_TRNG_H_ */
