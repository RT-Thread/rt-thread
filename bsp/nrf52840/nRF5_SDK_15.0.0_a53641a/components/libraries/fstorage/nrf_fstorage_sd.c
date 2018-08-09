/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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

#include "sdk_common.h"

#if NRF_MODULE_ENABLED(NRF_FSTORAGE)

#include "nrf_fstorage_sd.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "nordic_common.h"
#include "nrf_soc.h"
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_atomic.h"
#include "nrf_atfifo.h"
#include "app_util_platform.h"


#if (NRF_FSTORAGE_SD_MAX_WRITE_SIZE % 4)
#error NRF_FSTORAGE_SD_MAX_WRITE_SIZE must be a multiple of the word size.
#endif


/**@brief   fstorage operation codes. */
typedef enum
{
    NRF_FSTORAGE_OP_WRITE,  //!< Write bytes to flash.
    NRF_FSTORAGE_OP_ERASE   //!< Erase flash pages.
} nrf_fstorage_sd_opcode_t;

ANON_UNIONS_ENABLE;
/**@brief   fstorage operation queue element. */
typedef struct
{
    nrf_fstorage_t           const * p_fs;     //!< The fstorage instance that requested the operation.
    nrf_fstorage_sd_opcode_t         op_code;  //!< Requested operation.
    void                           * p_param;  //!< User-defined parameter passed to the event handler.
    union
    {
        struct
        {
            void     const * p_src;     //!< Data to be written to flash.
            uint32_t         dest;      //!< Destination of the data in flash.
            uint32_t         len;       //!< Length of the data to be written (in bytes).
            uint32_t         offset;    //!< Write offset.
        } write;
        struct
        {
            uint32_t page;              //!< Physical page number.
            uint32_t progress;          //!< Number of pages erased.
            uint32_t pages_to_erase;    //!< Total number of pages to erase.
        } erase;
    };
} nrf_fstorage_sd_op_t;
ANON_UNIONS_DISABLE;

typedef enum
{
    NRF_FSTORAGE_STATE_IDLE,            //!< No operations requested to the SoftDevice.
    NRF_FSTORAGE_STATE_OP_PENDING,      //!< A non-fstorage operation is pending.
    NRF_FSTORAGE_STATE_OP_EXECUTING,    //!< An fstorage operation is executing.
} nrf_fstorage_sd_state_t;

/**@brief   Internal state. */
typedef struct
{
    nrf_atomic_flag_t       initialized;    //!< fstorage is initalized.
    nrf_atomic_flag_t       queue_running;  //!< The queue is running.
                                            /** Prevent API calls from entering queue_process(). */
    nrf_fstorage_sd_state_t state;          //!< Internal fstorage state.
    uint32_t                retries;        //!< Number of times an operation has been retried on timeout.
    bool                    sd_enabled;     //!< The SoftDevice is enabled.
    bool                    paused;         //!< A SoftDevice state change is impending.
                                            /** Do not load a new operation when the last one completes. */
} nrf_fstorage_sd_work_t;


void nrf_fstorage_sys_evt_handler(uint32_t, void *);
bool nrf_fstorage_sdh_req_handler(nrf_sdh_req_evt_t, void *);
void nrf_fstorage_sdh_state_handler(nrf_sdh_state_evt_t, void *);


/* Flash device information. */
static nrf_fstorage_info_t m_flash_info =
{
#if   defined(NRF51)
    .erase_unit   = 1024,
#elif defined(NRF52_SERIES)
    .erase_unit   = 4096,
#endif
    .program_unit = 4,
    .rmap         = true,
    .wmap         = false,
};

/* Queue of fstorage operations. */
NRF_ATFIFO_DEF(m_fifo, nrf_fstorage_sd_op_t, NRF_FSTORAGE_SD_QUEUE_SIZE);

/* Define a nrf_sdh_soc event observer to receive SoftDevice system events. */
NRF_SDH_SOC_OBSERVER(m_sys_obs, 0, nrf_fstorage_sys_evt_handler, NULL);

/* nrf_sdh request observer. */
NRF_SDH_REQUEST_OBSERVER(m_req_obs, 0) =
{
    .handler = nrf_fstorage_sdh_req_handler,
};

/* nrf_sdh state observer. */
NRF_SDH_STATE_OBSERVER(m_state_obs, 0) =
{
    .handler = nrf_fstorage_sdh_state_handler,
};

static nrf_fstorage_sd_work_t   m_flags;        /* Internal status. */
static nrf_fstorage_sd_op_t   * m_p_cur_op;     /* The current operation being executed. */
static nrf_atfifo_item_get_t    m_iget_ctx;     /* Context for nrf_atfifo_item_get() and nrf_atfifo_item_free(). */


/* Send events to the application. */
static void event_send(nrf_fstorage_sd_op_t const * p_op, ret_code_t result)
{
    if (p_op->p_fs->evt_handler == NULL)
    {
        /* Nothing to do. */
        return;
    }

    nrf_fstorage_evt_t evt =
    {
        .result  = result,
        .p_param = p_op->p_param,
    };

    switch (p_op->op_code)
    {
        case NRF_FSTORAGE_OP_WRITE:
            evt.id    = NRF_FSTORAGE_EVT_WRITE_RESULT;
            evt.addr  = p_op->write.dest;
            evt.p_src = p_op->write.p_src;
            evt.len   = p_op->write.len;
            break;

        case NRF_FSTORAGE_OP_ERASE:
            evt.id   = NRF_FSTORAGE_EVT_ERASE_RESULT;
            evt.addr = (p_op->erase.page * m_flash_info.erase_unit);
            evt.len  = p_op->erase.pages_to_erase;
            break;

        default:
            /* Should not happen. */
            break;
    }

    p_op->p_fs->evt_handler(&evt);
}


/* Write to flash. */
static uint32_t write_execute(nrf_fstorage_sd_op_t const * p_op)
{
    uint32_t chunk_len;

    chunk_len = MIN(p_op->write.len - p_op->write.offset, NRF_FSTORAGE_SD_MAX_WRITE_SIZE);
    chunk_len = MAX(1, chunk_len / m_flash_info.program_unit);

    /* Cast to p_src to uint32_t to perform arithmetic. */
    uint32_t       * p_dest = (uint32_t*)(p_op->write.dest + p_op->write.offset);
    uint32_t const * p_src  = (uint32_t*)((uint32_t)p_op->write.p_src + p_op->write.offset);

    return sd_flash_write(p_dest, p_src, chunk_len);
}


/* Erase flash page(s). */
static uint32_t erase_execute(nrf_fstorage_sd_op_t const * p_op)
{
    return sd_flash_page_erase(p_op->erase.page + p_op->erase.progress);
}


/* Free the current queue element. */
static void queue_free(void)
{
    (void) nrf_atfifo_item_free(m_fifo, &m_iget_ctx);
}


/* Load a new operation from the queue. */
static bool queue_load_next(void)
{
    m_p_cur_op = nrf_atfifo_item_get(m_fifo, &m_iget_ctx);

    return (m_p_cur_op != NULL);
}


/* Execute an operation in the queue. */
static void queue_process(void)
{
    uint32_t rc;

    if (m_flags.state == NRF_FSTORAGE_STATE_IDLE)
    {
        if (!queue_load_next())
        {
            /* No more operations, nothing to do. */
            m_flags.queue_running = false;
            return;
        }
    }

    m_flags.state = NRF_FSTORAGE_STATE_OP_EXECUTING;

    switch (m_p_cur_op->op_code)
    {
        case NRF_FSTORAGE_OP_WRITE:
            rc = write_execute(m_p_cur_op);
            break;

        case NRF_FSTORAGE_OP_ERASE:
            rc = erase_execute(m_p_cur_op);
            break;

         default:
            rc = NRF_ERROR_INTERNAL;
            break;
    }

    switch (rc)
    {
        case NRF_SUCCESS:
        {
            /* The operation was accepted by the SoftDevice.
             * If the SoftDevice is enabled, wait for a system event. Otherwise,
             * the SoftDevice call is synchronous and will not send an event so we simulate it. */
            if (!m_flags.sd_enabled)
            {
                nrf_fstorage_sys_evt_handler(NRF_EVT_FLASH_OPERATION_SUCCESS, NULL);
            }
        } break;

        case NRF_ERROR_BUSY:
        {
            /* The SoftDevice is executing a flash operation that was not requested by fstorage.
             * Stop processing the queue until a system event is received. */
            m_flags.state = NRF_FSTORAGE_STATE_OP_PENDING;
        } break;

        default:
        {
            /* An error has occurred. We cannot proceed further with this operation. */
            event_send(m_p_cur_op, NRF_ERROR_INTERNAL);
            /* Reset the internal state so we can accept other operations. */
            m_flags.state         = NRF_FSTORAGE_STATE_IDLE;
            m_flags.queue_running = false;
            /* Free the current queue element. */
            queue_free();
        } break;
    }
}


/* Start processing the queue if it is not running and fstorage is not paused. */
static void queue_start(void)
{
    if (   (!nrf_atomic_flag_set_fetch(&m_flags.queue_running))
        && (!m_flags.paused))
    {
        queue_process();
    }
}


/* Flash operation success callback. Keeps track of the progress of an operation. */
static bool on_operation_success(nrf_fstorage_sd_op_t * const p_op)
{
    /* Reset the retry counter on success. */
    m_flags.retries = 0;

    switch (p_op->op_code)
    {
        case NRF_FSTORAGE_OP_WRITE:
        {
            /* Update the offset only if the operation is successful
             * so that it can be retried in case it times out. */
            uint32_t const chunk_len = MIN(p_op->write.len - p_op->write.offset,
                                           NRF_FSTORAGE_SD_MAX_WRITE_SIZE);

            p_op->write.offset += chunk_len;

            if (p_op->write.offset == p_op->write.len)
            {
                return true;
            }
        } break;

        case NRF_FSTORAGE_OP_ERASE:
        {
            p_op->erase.progress++;

            if (p_op->erase.progress == p_op->erase.pages_to_erase)
            {
                return true;
            }
        } break;

        default:
            /* Should not happen. */
            break;
    }

    return false;
}


/* Flash operation failure callback. */
static bool on_operation_failure(nrf_fstorage_sd_op_t const * p_op)
{
    UNUSED_PARAMETER(p_op);

    m_flags.retries++;

    if (m_flags.retries > NRF_FSTORAGE_SD_MAX_RETRIES)
    {
        /* Maximum amount of retries reached. Give up. */
        m_flags.retries = 0;
        return true;
    }

    return false;
}


static ret_code_t init(nrf_fstorage_t * p_fs, void * p_param)
{
    UNUSED_PARAMETER(p_param);

    p_fs->p_flash_info = &m_flash_info;

    if (!nrf_atomic_flag_set_fetch(&m_flags.initialized))
    {
#if NRF_SDH_ENABLED
        m_flags.sd_enabled = nrf_sdh_is_enabled();
#endif
        (void) NRF_ATFIFO_INIT(m_fifo);
    }

    return NRF_SUCCESS;
}


static ret_code_t uninit(nrf_fstorage_t * p_fs, void * p_param)
{
    UNUSED_PARAMETER(p_fs);
    UNUSED_PARAMETER(p_param);

    /* The state is re-initialized upon init().
     * The common uninitialization code is run by the caller. */

    memset(&m_flags, 0x00, sizeof(m_flags));

    (void) nrf_atfifo_clear(m_fifo);

    return NRF_SUCCESS;
}


static ret_code_t write(nrf_fstorage_t const * p_fs,
                        uint32_t               dest,
                        void           const * p_src,
                        uint32_t               len,
                        void                 * p_param)
{
    nrf_fstorage_sd_op_t  * p_op;
    nrf_atfifo_item_put_t   iput_ctx;

    /* Get a free queue element. */
    p_op = nrf_atfifo_item_alloc(m_fifo, &iput_ctx);

    if (p_op == NULL)
    {
        return NRF_ERROR_NO_MEM;
    }

    /* Initialize the operation. */
    memset(p_op, 0x00, sizeof(nrf_fstorage_sd_op_t));

    p_op->op_code     = NRF_FSTORAGE_OP_WRITE;
    p_op->p_fs        = p_fs;
    p_op->p_param     = p_param;
    p_op->write.dest  = dest;
    p_op->write.p_src = p_src;
    p_op->write.len   = len;

    /* Put the operation on the queue. */
    (void) nrf_atfifo_item_put(m_fifo, &iput_ctx);

    queue_start();

    return NRF_SUCCESS;
}


static ret_code_t read(nrf_fstorage_t const * p_fs, uint32_t src, void * p_dest, uint32_t len)
{
    memcpy(p_dest, (uint32_t*)src, len);

    return NRF_SUCCESS;
}


static ret_code_t erase(nrf_fstorage_t const * p_fs,
                        uint32_t               page_addr,
                        uint32_t               len,
                        void                 * p_param)
{
    nrf_fstorage_sd_op_t  * p_op;
    nrf_atfifo_item_put_t   iput_ctx;

    /* Get a free queue element. */
    p_op = nrf_atfifo_item_alloc(m_fifo, &iput_ctx);

    if (p_op == NULL)
    {
        return NRF_ERROR_NO_MEM;
    }

    /* Initialize the operation. */
    memset(p_op, 0x00, sizeof(nrf_fstorage_sd_op_t));

    p_op->op_code              = NRF_FSTORAGE_OP_ERASE;
    p_op->p_fs                 = p_fs;
    p_op->p_param              = p_param;
    p_op->erase.page           = (page_addr / m_flash_info.erase_unit);
    p_op->erase.pages_to_erase = len;

    /* Put the operation on the queue. */
    (void) nrf_atfifo_item_put(m_fifo, &iput_ctx);

    queue_start();

    return NRF_SUCCESS;
}


static uint8_t const * rmap(nrf_fstorage_t const * p_fs, uint32_t addr)
{
    UNUSED_PARAMETER(p_fs);

    return (uint8_t*)addr;
}


static uint8_t * wmap(nrf_fstorage_t const * p_fs, uint32_t addr)
{
    UNUSED_PARAMETER(p_fs);
    UNUSED_PARAMETER(addr);

    /* Not supported. */
    return NULL;
}


static bool is_busy(nrf_fstorage_t const * p_fs)
{
    UNUSED_PARAMETER(p_fs);

    return (m_flags.state != NRF_FSTORAGE_STATE_IDLE);
}


void nrf_fstorage_sys_evt_handler(uint32_t sys_evt, void * p_context)
{
    UNUSED_PARAMETER(p_context);

    if (   (sys_evt != NRF_EVT_FLASH_OPERATION_SUCCESS)
        && (sys_evt != NRF_EVT_FLASH_OPERATION_ERROR))
    {
        /* Ignore any non-flash events. */
        return;
    }

    switch (m_flags.state)
    {
        case NRF_FSTORAGE_STATE_IDLE:
            /* Ignore flash events if no flash operation was requested. */
            return;

        case NRF_FSTORAGE_STATE_OP_PENDING:
            /* The SoftDevice has completed a flash operation that was not requested by fstorage.
             * It should be possible to request an operation now.
             * Process the queue at the end of this function. */
            break;

        case NRF_FSTORAGE_STATE_OP_EXECUTING:
        {
            /* Handle the result of a flash operation initiated by this module. */
            bool operation_finished = false;

            switch (sys_evt)
            {
                case NRF_EVT_FLASH_OPERATION_SUCCESS:
                    operation_finished = on_operation_success(m_p_cur_op);
                    break;

                case NRF_EVT_FLASH_OPERATION_ERROR:
                    operation_finished = on_operation_failure(m_p_cur_op);
                    break;

                default:
                    break;
            }

            if (operation_finished)
            {
                /* The operation has finished. Change state to NRF_FSTORAGE_STATE_IDLE
                 * so that queue_process() will fetch a new operation from the queue. */
                m_flags.state = NRF_FSTORAGE_STATE_IDLE;

                event_send(m_p_cur_op, (sys_evt == NRF_EVT_FLASH_OPERATION_SUCCESS) ?
                                        NRF_SUCCESS : NRF_ERROR_TIMEOUT);

                /* Free the queue element after sending out the event to prevent API calls made
                 * in the event context to queue elements indefinitely, without this function
                 * ever returning in case the SoftDevice calls are synchronous. */
                queue_free();
            }
        } break;
    }

    if (!m_flags.paused)
    {
        queue_process();
    }
    else
    {
        /* A flash operation has completed. Let the SoftDevice change state. */
        (void) nrf_sdh_request_continue();
    }
}


bool nrf_fstorage_sdh_req_handler(nrf_sdh_req_evt_t req, void * p_context)
{
    UNUSED_PARAMETER(req);
    UNUSED_PARAMETER(p_context);

    m_flags.paused = true;

    /* If there are any operations ongoing, pause the SoftDevice state change. */
    return (m_flags.state == NRF_FSTORAGE_STATE_IDLE);
}


void nrf_fstorage_sdh_state_handler(nrf_sdh_state_evt_t state, void * p_context)
{
    UNUSED_PARAMETER(p_context);

    if (    (state == NRF_SDH_EVT_STATE_ENABLED)
        ||  (state == NRF_SDH_EVT_STATE_DISABLED))
    {
        m_flags.paused     = false;
        m_flags.sd_enabled = (state == NRF_SDH_EVT_STATE_ENABLED);

        /* Execute any operations still in the queue. */
        queue_process();
    }
}


/* Exported API implementation. */
nrf_fstorage_api_t nrf_fstorage_sd =
{
    .init    = init,
    .uninit  = uninit,
    .read    = read,
    .write   = write,
    .erase   = erase,
    .rmap    = rmap,
    .wmap    = wmap,
    .is_busy = is_busy
};


#endif // NRF_FSTORAGE_ENABLED
