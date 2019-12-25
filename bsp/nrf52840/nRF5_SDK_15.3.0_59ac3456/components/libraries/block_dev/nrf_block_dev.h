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
#ifndef NRF_BLOCK_DEV_H__
#define NRF_BLOCK_DEV_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "sdk_common.h"
#include "nrf_assert.h"

#include <stddef.h>

/**@file
 *
 * @defgroup nrf_block_dev Block device
 * @{
 * @ingroup app_common
 *
 * @brief This module implements unified block device API. It could used as a middle layer between
 *        filesystems and memories.
 */

/**
 * @brief Block device request descriptor item.
 */
typedef struct {
    uint32_t blk_id;    //!< Block ID
    uint32_t blk_count; //!< Block count
    void * p_buff;      //!< Data buffer
} nrf_block_req_t;


/**
 * @brief Helper macro to create block device read/write request item
 *
 * @param name          Instance name
 * @param block_start   Block number start
 * @param block_count   Number of blocks
 * @param buff          Buffer to read/write
 */
#define NRF_BLOCK_DEV_REQUEST(name, block_start, block_count, buff)     \
        nrf_block_req_t name = {                                        \
            .blk_id = block_start,                                      \
            .blk_count = block_count,                                   \
            .p_buff = buff,                                             \
       }
/**
 * @brief Block device events.
 *
 * Events are propagated when event handler is defined (@ref nrf_blk_dev_init)
 *
 */
typedef enum {
    NRF_BLOCK_DEV_EVT_INIT,             /**< Passed to event handler when init is done*/
    NRF_BLOCK_DEV_EVT_UNINIT,           /**< Passed to event handler when uninit is done*/
    NRF_BLOCK_DEV_EVT_BLK_READ_DONE,    /**< Passed to event handler block read operation is done*/
    NRF_BLOCK_DEV_EVT_BLK_WRITE_DONE,   /**< Passed to event handler block write operation is done*/
} nrf_block_dev_event_type_t;

typedef enum {
    NRF_BLOCK_DEV_RESULT_SUCCESS = 0,   /**< Operation completed succsefully*/
    NRF_BLOCK_DEV_RESULT_IO_ERROR,      /**< I/O error*/
    NRF_BLOCK_DEV_RESULT_TIMEOUT,       /**< Device timeout*/
} nrf_block_dev_result_t;

/**
 * @brief Block device event
 * */
typedef struct {
    nrf_block_dev_event_type_t ev_type;     //!< Event type
    nrf_block_dev_result_t     result;      //!< Operation status
    nrf_block_req_t const *    p_blk_req;   //!< Block request
    void const *               p_context;   //!< Event context
} nrf_block_dev_event_t;

struct nrf_block_dev_s;

/**
 * @brief Block device event handler.
 *
 * @param[in] p_blk_dev   Block device handle
 * @param[in] p_event     Block device event
 */
typedef void (* nrf_block_dev_ev_handler)(struct nrf_block_dev_s const * p_blk_dev,
                                          nrf_block_dev_event_t const *  p_event);

/**
 * @brief Block device geometry
 */
typedef struct {
    uint32_t blk_count; //!< Block count
    uint32_t blk_size;  //!< Block size
} nrf_block_dev_geometry_t;

/**
 * @brief Block device information strings
 */
typedef struct {
    const char * p_vendor;    //!< Vendor string
    const char * p_product;   //!< Product string
    const char * p_revision;  //!< Revision string
} nrf_block_dev_info_strings_t;

/**
 * @brief Block device information config
 *
 * @param vendor    Vendor string
 * @param product   Product string
 * @param revision  Revision string
 * */
#define NFR_BLOCK_DEV_INFO_CONFIG(vendor, product, revision)   ( {  \
    .p_vendor = vendor,                                             \
    .p_product = product,                                           \
    .p_revision = revision,                                         \
})

/**
 * @brief Empty info string initializer
 * */
#define NFR_BLOCK_DEV_INFO_CONFIG_EMPTY             \
        NFR_BLOCK_DEV_INFO_CONFIG(NULL, NULL, NULL)

/**
 * @brief Block device IOCTL requests
 */
typedef enum {
    NRF_BLOCK_DEV_IOCTL_REQ_CACHE_FLUSH = 0, /**< Cache flush IOCTL request*/
    NRF_BLOCK_DEV_IOCTL_REQ_INFO_STRINGS,    /**< Get info strings IOCTL request*/
} nrf_block_dev_ioctl_req_t;


/**
 * @brief Helper macro to get block device address from specific instance
 *
 * @param instance Block device instance
 * @param member   Block device member name
 * */
#define NRF_BLOCKDEV_BASE_ADDR(instance, member) &(instance).member

/**
 * @brief Block device API
 * */
typedef struct nrf_block_dev_s {
    struct nrf_block_dev_ops_s {
        /**
         * @brief @ref nrf_blk_dev_init
         */
        ret_code_t (*init)(struct nrf_block_dev_s const * p_blk_dev,
                           nrf_block_dev_ev_handler ev_handler,
                           void const * p_context);

        /**
         * @brief @ref nrf_blk_dev_uninit
         */
        ret_code_t (*uninit)(struct nrf_block_dev_s const * p_blk_dev);

        /**
         * @brief @ref nrf_blk_dev_read_req
         */
        ret_code_t (*read_req)(struct nrf_block_dev_s const * p_blk_dev,
                               nrf_block_req_t const * p_blk);

        /**
         * @brief @ref nrf_blk_dev_write_req
         */
        ret_code_t (*write_req)(struct nrf_block_dev_s const * p_blk_dev,
                                nrf_block_req_t const * p_blk);

        /**
         * @brief @ref nrf_blk_dev_ioctl
         */
        ret_code_t (*ioctl)(struct nrf_block_dev_s const * p_blk_dev,
                            nrf_block_dev_ioctl_req_t req,
                            void * p_data);

        /**
         * @brief @ref nrf_blk_dev_geometry
         */
        nrf_block_dev_geometry_t const * (*geometry)(struct nrf_block_dev_s const * p_blk_dev);
    } const * p_ops;
} nrf_block_dev_t;

/**
 * @brief Internals of @ref nrf_block_dev_t
 * */
typedef struct nrf_block_dev_ops_s nrf_block_dev_ops_t;

/**
 * @brief Initializes a block device.
 *
 * @param[in] p_blk_dev  Block device handle
 * @param[in] ev_handler Event handler (pass NULL to work in synchronous mode)
 * @param[in] p_context  Context passed to event handler
 *
 * @return Standard error code
 */
static inline ret_code_t nrf_blk_dev_init(nrf_block_dev_t const * p_blk_dev,
                                          nrf_block_dev_ev_handler ev_handler,
                                          void const * p_context)
{
    ASSERT(p_blk_dev->p_ops->init);
    return p_blk_dev->p_ops->init(p_blk_dev, ev_handler, p_context);
}

/**
 * @brief Un-initializes a block device.
 *
 * @param[in] p_blk_dev Block device handle
 *
 * @return Standard error code
 */
static inline ret_code_t nrf_blk_dev_uninit(nrf_block_dev_t const * p_blk_dev)
{
    ASSERT(p_blk_dev->p_ops->uninit);
    return p_blk_dev->p_ops->uninit(p_blk_dev);
}

/**
 * @brief Block read request.
 *
 *  In synchronous mode this function will execute the read operation
 *  and wait for its completion. In asynchronous mode the function will only request
 *  the operation and return immediately. Then, the @ref NRF_BLOCK_DEV_EVT_BLK_READ_DONE
 *  event will signal that operation has been completed and the specified buffer contains
 *  valid data.
 *
 * @param[in] p_blk_dev     Block device handle
 * @param[in] p_blk         Block device request
 *
 * @return Standard error code
 */
static inline ret_code_t nrf_blk_dev_read_req(nrf_block_dev_t const * p_blk_dev,
                                              nrf_block_req_t const * p_blk)
{
    ASSERT(p_blk_dev->p_ops->read_req);
    ASSERT(p_blk_dev->p_ops->geometry);

    if (p_blk->blk_id  >= p_blk_dev->p_ops->geometry(p_blk_dev)->blk_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    return p_blk_dev->p_ops->read_req(p_blk_dev, p_blk);
}

/**
 * @brief Block write request.
 *
 *  In synchronous mode this function will execute the write operation
 *  and wait for its completion. In asynchronous mode the function will only request
 *  the operation and return immediately. Then, the @ref NRF_BLOCK_DEV_EVT_BLK_WRITE_DONE
 *  event will signal that operation has been completed and the specified buffer
 *  can be freed.
 *
 * @param[in] p_blk_dev     Block device handle
 * @param[in] p_blk         Block device request
 *
 * @return Standard error code
 */
static inline ret_code_t nrf_blk_dev_write_req(nrf_block_dev_t const * p_blk_dev,
                                               nrf_block_req_t const * p_blk)
{
    ASSERT(p_blk_dev->p_ops->write_req);
    ASSERT(p_blk_dev->p_ops->geometry);

    if (p_blk->blk_id  >= p_blk_dev->p_ops->geometry(p_blk_dev)->blk_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    return p_blk_dev->p_ops->write_req(p_blk_dev, p_blk);
}

/**
 * @brief IO control function.
 *
 * @param[in] p_blk_dev   Block device handle
 * @param[in] req         Block device ioctl request
 * @param[in] p_data      Block device ioctl data
 *
 * @return Standard error code
 * */
static inline ret_code_t nrf_blk_dev_ioctl(nrf_block_dev_t const * p_blk_dev,
                                           nrf_block_dev_ioctl_req_t req,
                                           void * p_data)
{
    ASSERT(p_blk_dev->p_ops->ioctl);
    return p_blk_dev->p_ops->ioctl(p_blk_dev, req, p_data);
}

/**
 * @brief Return a geometry of a block device.
 *
 * @param[in] p_blk_dev Block device handle
 *
 * @return Block size and count @ref nrf_block_dev_geometry_t
 */
static inline nrf_block_dev_geometry_t const *
nrf_blk_dev_geometry(nrf_block_dev_t const * p_blk_dev)
{
    ASSERT(p_blk_dev->p_ops->geometry);
    return p_blk_dev->p_ops->geometry(p_blk_dev);
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* NRF_BLOCK_DEV_H__ */


