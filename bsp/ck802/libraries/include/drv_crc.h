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
 * @file     drv_crc.h
 * @brief    Header File for CRC Driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef _CSI_CRC_H_
#define _CSI_CRC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <drv_errno.h>
#include <drv_common.h>


/****** CRC specific error codes *****/
#define CRC_ERROR_MODE                (EDRV_SPECIFIC + 1)     ///< Specified Mode not supported

/// definition for crc handle.
typedef void *crc_handle_t;

/*----- CRC Control Codes: Mode -----*/
typedef enum {
    CRC_MODE_CRC8                   = 0,   ///< Mode CRC8
    CRC_MODE_CRC16                     ,   ///< Mode CRC16
    CRC_MODE_CRC32                         ///< Mode CRC32
} crc_mode_e;

/*----- CRC Control Codes: Mode Parameters: Key length -----*/
typedef enum {
    CRC_STANDARD_CRC_ROHC         = 0,    ///< Standard CRC RHOC
    CRC_STANDARD_CRC_MAXIM           ,    ///< Standard CRC MAXIAM
    CRC_STANDARD_CRC_X25             ,    ///< Standard CRC X25
    CRC_STANDARD_CRC_CCITT           ,    ///< Standard CRC CCITT
    CRC_STANDARD_CRC_USB             ,    ///< Standard CRC USB
    CRC_STANDARD_CRC_IBM             ,    ///< Standard CRC IBM
    CRC_STANDARD_CRC_MODBUS               ///< Standard CRC MODBUS
} crc_standard_crc_e;

/**
\brief CRC Status
*/
typedef struct {
    uint32_t busy             : 1;        ///< busy flag
} crc_status_t;

/****** CRC Event *****/
typedef enum {
    CRC_EVENT_CALCULATE_COMPLETE  = 0,  ///< Calculate completed
} crc_event_e;

typedef void (*crc_event_cb_t)(crc_event_e event);   ///< Pointer to \ref crc_event_cb_t : CRC Event call back.

/**
\brief CRC Device Driver Capabilities.
*/
typedef struct {
    uint32_t ROHC               : 1;      ///< supports ROHC mode
    uint32_t MAXIM              : 1;      ///< supports MAXIM mode
    uint32_t X25                : 1;      ///< supports X25 mode
    uint32_t CCITT              : 1;      ///< supports CCITT mode
    uint32_t USB                : 1;      ///< supports USB mode
    uint32_t IBM                : 1;      ///< supports IBM mode
    uint32_t MODBUS             : 1;      ///< supports MODBUS mode
} crc_capabilities_t;

// Function documentation

/**
  \brief       get crc handle count.
  \return      crc handle count
*/
int32_t csi_crc_get_instance_count(void);

/**
  \brief       Initialize CRC Interface. 1. Initializes the resources needed for the CRC interface 2.registers event callback function
  \param[in]   idx must not exceed return value of csi_crc_get_handle_count()
  \param[in]   cb_event  Pointer to \ref crc_event_cb_t
  \return      return crc handle if success
*/
crc_handle_t csi_crc_initialize(int32_t idx, crc_event_cb_t cb_event);

/**
  \brief       De-initialize CRC Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  crc handle to operate.
  \return      error code
*/
int32_t csi_crc_uninitialize(crc_handle_t handle);

/**
  \brief       Get driver capabilities.
  \param[in]   handle crc handle to operate.
  \return      \ref crc_capabilities_t
*/
crc_capabilities_t csi_crc_get_capabilities(crc_handle_t handle);

/**
  \brief       config crc mode.
  \param[in]   handle  crc handle to operate.
  \param[in]   mode      \ref crc_mode_e
  \param[in]   standard  \ref crc_standard_crc_e
  \return      error code
*/
int32_t csi_crc_config(crc_handle_t handle,
                       crc_mode_e mode,
                       crc_standard_crc_e standard
                      );

/**
  \brief       calculate crc.
  \param[in]   handle  crc handle to operate.
  \param[in]   in      Pointer to the input data
  \param[out]  out     Pointer to the result.
  \param[in]   len     intpu data len.
  \return      error code
*/
int32_t csi_crc_calculate(crc_handle_t handle, const void *in, void *out, uint32_t len);

/**
  \brief       Get CRC status.
  \param[in]   handle  crc handle to operate.
  \return      CRC status \ref crc_status_t
*/
crc_status_t csi_crc_get_status(crc_handle_t handle);


#ifdef __cplusplus
}
#endif

#endif /* _CSI_CRC_H_ */
