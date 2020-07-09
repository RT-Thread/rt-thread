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
 * @file     drv_sha.h
 * @brief    header file for sha driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef _CSI_SHA_H_
#define _CSI_SHA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <drv_common.h>
#include <drv_errno.h>


/// definition for sha handle.
typedef void *sha_handle_t;

/****** SHA specific error codes *****/
typedef enum {
    SHA_ERROR_MODE  = (EDRV_SPECIFIC + 1),     ///< Specified Mode not supported
    SHA_ERROR_ENDIAN                              ///< Specified endian not supported
} drv_sha_error_e;

/*----- SHA Control Codes: Mode -----*/
typedef enum {
    SHA_MODE_1                    = 1,    ///< SHA_1 mode
    SHA_MODE_256                     ,    ///< SHA_256 mode
    SHA_MODE_224                     ,    ///< SHA_224 mode
    SHA_MODE_512                     ,    ///< SHA_512 mode
    SHA_MODE_384                     ,    ///< SHA_384 mode
    SHA_MODE_512_256                 ,    ///< SHA_512_256 mode
    SHA_MODE_512_224                      ///< SHA_512_224 mode
} sha_mode_e;

/*----- SHA Control Codes: Mode Parameters: Endian -----*/
typedef enum {
    SHA_ENDIAN_MODE_BIG             = 0,    ///< Big Endian Mode
    SHA_ENDIAN_MODE_LITTLE             ,    ///< Little Endian Mode
} sha_endian_mode_e;

/**
\brief SHA Status
*/
typedef struct {
    uint32_t busy             : 1;        ///< calculate busy flag
} sha_status_t;

/****** SHA Event *****/
typedef enum {
    SHA_EVENT_COMPLETE    = 0   ///< calculate completed
} sha_event_e;

typedef void (*sha_event_cb_t)(sha_event_e event);   ///< Pointer to \ref sha_event_cb_t : SHA Event call back.


/**
\brief SHA Device Driver Capabilities.
*/
typedef struct {
    uint32_t sha1               : 1;      ///< supports sha1 mode
    uint32_t sha224             : 1;      ///< supports sha224 mode
    uint32_t sha256             : 1;      ///< supports sha256 mode
    uint32_t sha384             : 1;      ///< supports sha384 mode
    uint32_t sha512             : 1;      ///< supports sha512 mode
    uint32_t sha512_224         : 1;      ///< supports sha512_224 mode
    uint32_t sha512_256         : 1;      ///< supports sha512_256 mode
    uint32_t endianmode         : 1;      ///< supports endian mode control
    uint32_t interruptmode      : 1;      ///< supports interrupt mode
} sha_capabilities_t;


// Function documentation

/**
  \brief       get sha handle count.
  \return      sha handle count
*/
int32_t csi_sha_get_instance_count(void);

/**
  \brief       Initialize SHA Interface. 1. Initializes the resources needed for the SHA interface 2.registers event callback function
  \param[in]   idx must not exceed return value of csi_sha_get_instance_count()
  \param[in]   cb_event  Pointer to \ref sha_event_cb_t
  \return      return sha handle if success
*/
sha_handle_t csi_sha_initialize(int32_t idx, sha_event_cb_t cb_event);

/**
  \brief       De-initialize SHA Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  sha handle to operate.
  \return      error code
*/
int32_t csi_sha_uninitialize(sha_handle_t handle);

/**
  \brief       Get driver capabilities.
  \param[in]   handle sha handle to operate.
  \return      \ref sha_capabilities_t
*/
sha_capabilities_t csi_sha_get_capabilities(sha_handle_t handle);

/**
  \brief       config sha mode.
  \param[in]   handle  sha handle to operate.
  \param[in]   mode      \ref sha_mode_e
  \param[in]   endian    \ref sha_endian_mode_e
  \return      error code
*/
int32_t csi_sha_config(sha_handle_t handle,
                       sha_mode_e mode,
                       sha_endian_mode_e endian
                      );

/**
  \brief       start the engine
  \param[in]   handle  sha handle to operate.
  \param[in]   context  Pointer to the sha context.
  \return      error code
*/
int32_t csi_sha_starts(sha_handle_t handle, void *context);

/**
  \brief       updata the engine
  \param[in]   handle  sha handle to operate.
  \param[in]   context  Pointer to the sha context.
  \param[in]   input   Pointer to the Source data
  \param[in]   len    the data len
  \return      error code
*/
int32_t csi_sha_update(sha_handle_t handle, void *context, const void *input, uint32_t len);

/**
  \brief       finish the engine
  \param[in]   handle  sha handle to operate.
  \param[in]   context  Pointer to the sha context.
  \param[out]  output   Pointer to the dest data
  \return      error code
*/
int32_t csi_sha_finish(sha_handle_t handle, void *context, void *output);

/**
  \brief       Get SHA status.
  \param[in]   handle  sha handle to operate.
  \return      SHA status \ref sha_status_t
*/
sha_status_t csi_sha_get_status(sha_handle_t handle);


#ifdef __cplusplus
}
#endif

#endif /* _CSI_SHA_H_ */
