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
#ifndef NRF_LOG_BACKEND_INTERFACE_H
#define NRF_LOG_BACKEND_INTERFACE_H

/**@file
 * @addtogroup nrf_log Logger module
 * @ingroup    app_common
 *
 * @defgroup nrf_log_backend_interface Logger backend interface
 * @{
 * @ingroup  nrf_log
 * @brief    The nrf_log backend interface.
 */

#if NRF_MODULE_ENABLED(NRF_LOG)
#include "nrf_memobj.h"
#endif

#include "nrf_section.h"
#include "nordic_common.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief nrf_log entry.
 */
#if NRF_LOG_ENABLED
typedef nrf_memobj_t nrf_log_entry_t;
#else
typedef void nrf_log_entry_t;
#endif

/* Forward declaration of the nrf_log_backend_t type. */
typedef struct nrf_log_backend_s nrf_log_backend_t;

/**
 * @brief Logger backend API.
 */
typedef struct
{
    /**
     * @brief @ref nrf_log_backend_put
     */
    void (*put)(nrf_log_backend_t const * p_backend, nrf_log_entry_t * p_entry);

    /**
     * @brief @ref nrf_log_backend_panic_set
     */
    void (*panic_set)(nrf_log_backend_t const * p_backend);

    /**
     * @brief @ref nrf_log_backend_flush
     */
    void (*flush)(nrf_log_backend_t const * p_backend);
} nrf_log_backend_api_t;

/**
 * @brief Logger backend control block.
 */
typedef struct
{
    nrf_log_backend_t const * p_next;  //!< Pointer to the next backend in the logger.
    uint8_t                   id;      //!< ID of the backend.
    bool                      enabled; //!< Enable flag.
} nrf_log_backend_cb_t;

/**
 * @brief Logger backend structure.
 */
struct nrf_log_backend_s
{
    nrf_log_backend_api_t const * p_api;  //!< Pointer to interface.
    void *                        p_ctx;  //!< User context.
    char *                        p_name; //!< Name of the backend.
    nrf_log_backend_cb_t *        p_cb;   //!< Pointer to the backend control block.
};


#define NRF_LOG_BACKEND_SECTION_NAME log_backends

#define NRF_LOG_BACKEND_SUBSECTION_NAME(_name) NRF_LOG_BACKEND_SECTION_NAME

/** @brief Invalid ID value indicating that logger backend is not attached to the logger frontend.*/
#define NRF_LOG_BACKEND_INVALID_ID 0xFF

/** @brief Memory section where backends are located. */
NRF_SECTION_DEF(NRF_LOG_BACKEND_SECTION_NAME, nrf_log_backend_t);

/**
 * @brief Macro for creating a logger backend instance.
 *
 * @param _name  Name of the backend instance.
 * @param _api   Logger backend API.
 * @param _p_ctx Pointer to the user context.
 */
#define NRF_LOG_BACKEND_DEF(_name, _api, _p_ctx)                           \
    static nrf_log_backend_cb_t CONCAT_2(log_backend_cb_, _name) = {       \
            .enabled = false,                                              \
            .id      = NRF_LOG_BACKEND_INVALID_ID,                         \
            .p_next  = NULL                                                \
    };                                                                     \
    NRF_SECTION_ITEM_REGISTER(NRF_LOG_BACKEND_SUBSECTION_NAME(_name),      \
          static const nrf_log_backend_t _name) = {                        \
            .p_api = &_api,                                                \
            .p_ctx = _p_ctx,                                               \
            .p_cb = &CONCAT_2(log_backend_cb_, _name),                     \
            .p_name = (char *)STRINGIFY(_name)                             \
   }


/**
 * @brief Function for putting message with log entry to the backend.
 *
 * @param[in] p_backend  Pointer to the backend instance.
 * @param[in] p_msg      Pointer to message with log entry.
 */
__STATIC_INLINE void nrf_log_backend_put(nrf_log_backend_t const * const p_backend,
                                         nrf_log_entry_t * p_msg);

/**
 * @brief Function for reconfiguring backend to panic mode.
 *
 * @param[in] p_backend  Pointer to the backend instance.
 */
__STATIC_INLINE void nrf_log_backend_panic_set(nrf_log_backend_t const * const p_backend);

/**
 * @brief Function for flushing backend.
 *
 *        On flushing request backend should release log message(s).
 *
 * @param[in] p_backend  Pointer to the backend instance.
 */
__STATIC_INLINE void nrf_log_backend_flush(nrf_log_backend_t const * const p_backend);


/**
 * @brief Function for setting backend id.
 *
 * @note It is used internally by the logger.
 *
 * @param[in] p_backend  Pointer to the backend instance.
 * @param[in] id         Id.
 */
__STATIC_INLINE void nrf_log_backend_id_set(nrf_log_backend_t const * const p_backend, uint8_t id);

/**
 * @brief Function for getting backend id.
 *
 * @note It is used internally by the logger.
 *
 * @param[in] p_backend  Pointer to the backend instance.
 * @return    Id.
 */
__STATIC_INLINE uint8_t nrf_log_backend_id_get(nrf_log_backend_t const * const p_backend);

/**
 * @brief Function for enabling backend.
 *
 * @param[in] p_backend  Pointer to the backend instance.
 */
__STATIC_INLINE void nrf_log_backend_enable(nrf_log_backend_t const * const p_backend);

/**
 * @brief Function for disabling backend.
 *
 * @param[in] p_backend  Pointer to the backend instance.
 */
__STATIC_INLINE void nrf_log_backend_disable(nrf_log_backend_t const * const p_backend);

/**
 * @brief Function for checking state of the backend.
 *
 * @param[in] p_backend  Pointer to the backend instance.
 *
 * @return True if backend is enabled, false otherwise.
 */
__STATIC_INLINE bool nrf_log_backend_is_enabled(nrf_log_backend_t const * const p_backend);

#ifndef SUPPRESS_INLINE_IMPLEMENTATION
__STATIC_INLINE void nrf_log_backend_put(nrf_log_backend_t const * const p_backend,
                                         nrf_log_entry_t * p_msg)
{
    p_backend->p_api->put(p_backend, p_msg);
}

__STATIC_INLINE void nrf_log_backend_panic_set(nrf_log_backend_t const * const p_backend)
{
    p_backend->p_api->panic_set(p_backend);
}

__STATIC_INLINE void nrf_log_backend_flush(nrf_log_backend_t const * const p_backend)
{
    p_backend->p_api->flush(p_backend);
}

__STATIC_INLINE void nrf_log_backend_id_set(nrf_log_backend_t const * const p_backend, uint8_t id)
{
    p_backend->p_cb->id = id;
}

__STATIC_INLINE uint8_t nrf_log_backend_id_get(nrf_log_backend_t const * const p_backend)
{
    return p_backend->p_cb->id;
}

__STATIC_INLINE void nrf_log_backend_enable(nrf_log_backend_t const * const p_backend)
{
    p_backend->p_cb->enabled = true;
}

__STATIC_INLINE void nrf_log_backend_disable(nrf_log_backend_t const * const p_backend)
{
    p_backend->p_cb->enabled = false;
}

__STATIC_INLINE bool nrf_log_backend_is_enabled(nrf_log_backend_t const * const p_backend)
{
    return p_backend->p_cb->enabled;
}

#endif // SUPPRESS_INLINE_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif //NRF_LOG_BACKEND_INTERFACE_H

/** @} */
