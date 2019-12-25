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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_LOG) && NRF_MODULE_ENABLED(NRF_LOG_BACKEND_FLASH)
#include "nrf_log_backend_flash.h"
#include "nrf_log_str_formatter.h"
#include "nrf_fstorage_nvmc.h"
#include "nrf_log.h"
#include "nrf_atomic.h"
#include "nrf_queue.h"
#include "app_error.h"
#include <stdbool.h>

#if (NRF_LOG_BACKEND_FLASHLOG_ENABLED == 0) && (NRF_LOG_BACKEND_CRASHLOG_ENABLED == 0)
#error "No flash backend enabled."
#endif

/** @brief Maximum logger message payload (arguments or data in hexdump) which can be stored. */
#define FLASH_LOG_MAX_PAYLOAD_SIZE (NRF_LOG_BACKEND_FLASH_SER_BUFFER_SIZE - sizeof(nrf_log_header_t))

/** @brief Size of serialization buffer in words. */
#define FLASH_LOG_SER_BUFFER_WORDS (NRF_LOG_BACKEND_FLASH_SER_BUFFER_SIZE/sizeof(uint32_t))

/** @brief Length of logger header. */
#define LOG_HEADER_LEN             (sizeof(nrf_log_header_t))

/** @brief Length of logger header given in 32 bit words. */
#define LOG_HEADER_LEN_WORDS       (LOG_HEADER_LEN/sizeof(uint32_t))

/** @brief Maximum possible length of standard log message. */
#define STD_LOG_MSG_MAX_LEN (LOG_HEADER_LEN + NRF_LOG_MAX_NUM_OF_ARGS*sizeof(uint32_t))

/* Buffer must be multiple of 4. */
STATIC_ASSERT((NRF_LOG_BACKEND_FLASH_SER_BUFFER_SIZE % sizeof(uint32_t)) == 0);

/* Buffer must fit standard log message. */
STATIC_ASSERT(NRF_LOG_BACKEND_FLASH_SER_BUFFER_SIZE >= STD_LOG_MSG_MAX_LEN);

/** @brief Flash page size in bytes. */
#define CODE_PAGE_SIZE        4096

/** @brief Start address of the area dedicated for flash log. */
#define FLASH_LOG_START_ADDR  (NRF_LOG_BACKEND_FLASH_START_PAGE * CODE_PAGE_SIZE)

/** @brief End address of the area dedicated for flash log. */
#define FLASH_LOG_END_ADDR    (FLASH_LOG_START_ADDR + (NRF_LOG_BACKEND_PAGES * CODE_PAGE_SIZE) - 1)

/** @brief Size of the area dedicated for flash log. */
#define FLASH_LOG_SIZE        (NRF_LOG_BACKEND_PAGES * CODE_PAGE_SIZE)

/** @brief Start address determined in runtime.
 *
 * If configuration indicates that flash log should be placed after application.
 * */
#if defined ( __CC_ARM )
#define RUNTIME_START_ADDR                                                                           \
               _Pragma("diag_suppress 170")                                                          \
               ((NRF_LOG_BACKEND_FLASH_START_PAGE == 0) ?                                            \
               (CODE_PAGE_SIZE*CEIL_DIV((uint32_t)CODE_END, CODE_PAGE_SIZE)) : FLASH_LOG_START_ADDR) \
               _Pragma("diag_default 170")
#else
#define RUNTIME_START_ADDR ((NRF_LOG_BACKEND_FLASH_START_PAGE == 0) ? \
               (CODE_PAGE_SIZE*CEIL_DIV((uint32_t)CODE_END, CODE_PAGE_SIZE)) : FLASH_LOG_START_ADDR)
#endif
static void fstorage_evt_handler(nrf_fstorage_evt_t * p_evt);

/** @brief Message queue for run time flash log. */
#if NRF_LOG_BACKEND_FLASHLOG_ENABLED
NRF_QUEUE_DEF(nrf_log_entry_t *,
              m_flashlog_queue,
              NRF_LOG_BACKEND_FLASHLOG_QUEUE_SIZE,
              NRF_QUEUE_MODE_NO_OVERFLOW);
static const nrf_queue_t * mp_flashlog_queue = &m_flashlog_queue;
#else
static const nrf_queue_t * mp_flashlog_queue = NULL;
#endif


/** @brief Message FIFO for crash log. */
#if NRF_LOG_BACKEND_CRASHLOG_ENABLED
NRF_QUEUE_DEF(nrf_log_entry_t *,
              m_crashlog_queue,
              NRF_LOG_BACKEND_CRASHLOG_FIFO_SIZE,
              NRF_QUEUE_MODE_NO_OVERFLOW);
static const nrf_queue_t * mp_crashlog_queue = &m_crashlog_queue;
#else
static const nrf_queue_t * mp_crashlog_queue = NULL;
#endif


/** @brief Fstorage instance used for flash log. */
NRF_FSTORAGE_DEF(nrf_fstorage_t m_log_flash_fstorage) =
{
    /* Set a handler for fstorage events. */
    .evt_handler = fstorage_evt_handler,
    .start_addr  = FLASH_LOG_START_ADDR,
    .end_addr    = FLASH_LOG_END_ADDR,
};

/** @brief Flash log state. */
typedef enum
{
    LOG_BACKEND_FLASH_ACTIVE,   /**< Flash backend is active. */
    LOG_BACKEND_FLASH_INACTIVE, /**< Flash backend is inactive. All incoming requests are skipped. */
    LOG_BACKEND_FLASH_IN_PANIC, /**< Flash backend is in panic mode. Incoming messages are written to flash in synchronous mode. */
} log_backend_flash_state_t;

static log_backend_flash_state_t m_state;                      /**< Flash logger backend state. */
static nrf_atomic_flag_t         m_busy_flag;                  /**< Flag indicating if module performs flash writing. */
static uint32_t                  m_flash_buf[FLASH_LOG_SER_BUFFER_WORDS]; /**< Buffer used for serializing messages. */
static uint32_t                  m_curr_addr;                  /**< Address of free spot in the storage area. */
static size_t                    m_curr_len;                   /**< Length of current message being written. */
static uint32_t                  m_dropped;                    /**< Number of dropped messages. */

/** @brief Log message string injected when entering panic mode. */
static const char crashlog_str[] =  "-----------CRASHLOG------------\r\n";

/** @brief Function saturates input to maximum possible length and rounds up value to be multiple
 *         of word size.
 *
 * @param length Length value.
 *
 * @return Modified input length.
 */
static uint32_t saturate_align_length(uint32_t length)
{
    length = (length > FLASH_LOG_MAX_PAYLOAD_SIZE) ? FLASH_LOG_MAX_PAYLOAD_SIZE : length; //saturate
    length = CEIL_DIV(length, sizeof(uint32_t))*sizeof(uint32_t);
    return length;
}


/**
 * @brief Function for copying logger message to the buffer.
 *
 * @param[in]     p_msg Logger message.
 * @param[out]    p_buf Output buffer where serialized message is placed.
 * @param[in,out] p_len Buffer size as input, length of prepared data as output.
 *
 * @return True if message fits into the buffer, false otherwise
 */
static bool msg_to_buf(nrf_log_entry_t * p_msg, uint8_t * p_buf, size_t * p_len)
{
    uint32_t         data_len;
    nrf_log_header_t header = {0};
    size_t           memobj_offset = HEADER_SIZE*sizeof(uint32_t);

    nrf_memobj_read(p_msg, &header, HEADER_SIZE*sizeof(uint32_t), 0);

    memcpy(p_buf, &header, sizeof(nrf_log_header_t));
    p_buf +=  sizeof(nrf_log_header_t);

    switch (header.base.generic.type)
    {
        case HEADER_TYPE_STD:
        {
            data_len = header.base.std.nargs * sizeof(uint32_t);
            break;
        }
        case HEADER_TYPE_HEXDUMP:
        {
            data_len = saturate_align_length(header.base.hexdump.len);
            break;
        }
        default:
            *p_len = 0;
            return false;
    }
    nrf_memobj_read(p_msg, p_buf, data_len, memobj_offset);

    if (*p_len >= sizeof(nrf_log_header_t) + data_len)
    {
        *p_len = sizeof(nrf_log_header_t) + data_len;
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Function for getting logger message stored in flash.
 *
 * @param[in]  p_buf     Pointer to the location where message is stored.
 * @param[out] pp_header Pointer to the log message header.
 * @param[out] pp_data   Pointer to the log message data (arguments or data in case of hexdump).
 *
 * @return True if message was successfully fetched, false otherwise.
 */
static bool msg_from_buf(uint32_t *           p_buf,
                         nrf_log_header_t * * pp_header,
                         uint8_t * *          pp_data,
                         uint32_t *           p_len)
{
    *pp_header = (nrf_log_header_t *)p_buf;
    *pp_data = (uint8_t *)&p_buf[LOG_HEADER_LEN_WORDS];

    uint32_t data_len;

    switch ((*pp_header)->base.generic.type)
    {
        case HEADER_TYPE_STD:
        {
            data_len = ((*pp_header)->base.std.nargs)*sizeof(uint32_t);
            break;
        }
        case HEADER_TYPE_HEXDUMP:
        {

            data_len = saturate_align_length((*pp_header)->base.hexdump.len);
            break;
        }
        default:
            return false;
    }

    *p_len = LOG_HEADER_LEN + data_len;
    return true;
}

/**
 * @brief Function for processing log message queue.
 *
 * If writing to flash is synchronous then function drains the queue and writes all messages to flash.
 * If writing to flash is asynchronous then function starts single write operation. In asynchronous mode
 * function is called when new message is put into the queue from from flash operation callback.
 *
 * Function detects the situation that flash module reports attempt to write outside dedicated area.
 * In that case flash backend stops writing any new messages.
 *
 * @param p_queue           Queue will log messages
 * @param fstorage_blocking If true it indicates that flash operations are blocking, event handler is not used.
 */
static void log_msg_queue_process(nrf_queue_t const * p_queue, bool fstorage_blocking)
{
    nrf_log_entry_t * p_msg;
    bool              busy = false;
    while (nrf_queue_pop(p_queue, &p_msg) == NRF_SUCCESS)
    {
        ret_code_t err_code;

        m_curr_len = sizeof(m_flash_buf);
        if (!msg_to_buf(p_msg, (uint8_t *)m_flash_buf, &m_curr_len))
        {
            continue;
        }

        err_code = nrf_fstorage_write(&m_log_flash_fstorage, m_curr_addr, m_flash_buf, m_curr_len, p_msg);

        if (err_code == NRF_SUCCESS)
        {
            if (fstorage_blocking)
            {
                m_curr_addr += m_curr_len;

                nrf_memobj_put(p_msg);
            }
            else
            {
                busy = true;
                break;
            }
        }
        else if (!fstorage_blocking && (err_code == NRF_ERROR_NO_MEM))
        {
            // fstorage queue got full. Drop entry.
            nrf_memobj_put(p_msg);
            m_dropped++;
            break;
        }
        else if (err_code == NRF_ERROR_INVALID_ADDR)
        {
            // Trying to write outside the area, flash log is full. Skip any new writes.
            nrf_memobj_put(p_msg);
            m_state = LOG_BACKEND_FLASH_INACTIVE;
        }
        else
        {
            ASSERT(false);
        }
    }

    if (!busy)
    {
        UNUSED_RETURN_VALUE(nrf_atomic_flag_clear(&m_busy_flag));
    }
}

static void queue_element_drop(nrf_queue_t const * p_queue)
{
    nrf_log_entry_t * p_msg;
    if (nrf_queue_pop(p_queue, &p_msg) == NRF_SUCCESS)
    {
        m_dropped++;
        nrf_memobj_put(p_msg);
    }
}

static void fstorage_evt_handler(nrf_fstorage_evt_t * p_evt)
{
    if (m_state == LOG_BACKEND_FLASH_ACTIVE)
    {
        switch (p_evt->id)
        {
            case NRF_FSTORAGE_EVT_WRITE_RESULT:
            {
                if (p_evt->result == NRF_SUCCESS)
                {
                    m_curr_addr += m_curr_len;
                    m_curr_len = 0;
                    log_msg_queue_process(mp_flashlog_queue, false);
                }
                else
                {
                    m_dropped++;
                }

                if (p_evt->p_param)
                {
                    nrf_memobj_put((nrf_log_entry_t *)p_evt->p_param);
                }
                break;
            }
            default:
                break;
        }
    }
    else if ((m_state == LOG_BACKEND_FLASH_INACTIVE) &&
             (p_evt->id == NRF_FSTORAGE_EVT_ERASE_RESULT) &&
             (p_evt->addr == RUNTIME_START_ADDR))
    {
        m_state = LOG_BACKEND_FLASH_ACTIVE;
    }
}

/**
 * @brief Function for enqueueing new message.
 *
 * If queue is full then the oldest message is freed.
 *
 * @param p_queue Queue.
 * @param p_msg   Message.
 *
 * @return Number of dropped messages
 */
static uint32_t message_enqueue(nrf_queue_t const * p_queue, nrf_log_entry_t * p_msg)
{
    uint32_t dropped = 0;

    //flag was set, busy so enqueue message
    while (nrf_queue_push(p_queue, &p_msg) != NRF_SUCCESS)
    {

        nrf_log_entry_t * p_old_msg;
        if (nrf_queue_pop(p_queue, &p_old_msg) == NRF_SUCCESS)
        {
            nrf_memobj_put(p_old_msg);
            dropped++;
        }
    }

    return dropped;
}


void nrf_log_backend_flashlog_put(nrf_log_backend_t const * p_backend,
                                  nrf_log_entry_t * p_msg)
{
    if (m_state == LOG_BACKEND_FLASH_ACTIVE)
    {
        nrf_memobj_get(p_msg);

        m_dropped += message_enqueue(mp_flashlog_queue, p_msg);

        if (nrf_atomic_flag_set_fetch(&m_busy_flag) == 0)
        {
            log_msg_queue_process(mp_flashlog_queue, false);
        }
    }
}


void nrf_log_backend_crashlog_put(nrf_log_backend_t const * p_backend,
                                  nrf_log_entry_t * p_msg)
{
    if (m_state != LOG_BACKEND_FLASH_INACTIVE)
    {
        nrf_memobj_get(p_msg);

        UNUSED_RETURN_VALUE(message_enqueue(mp_crashlog_queue, p_msg));
    }

    if (m_state == LOG_BACKEND_FLASH_IN_PANIC)
    {
        log_msg_queue_process(mp_crashlog_queue, true);
    }
}

void nrf_log_backend_flashlog_flush(nrf_log_backend_t const * p_backend)
{
    queue_element_drop(mp_flashlog_queue);
}

void nrf_log_backend_crashlog_flush(nrf_log_backend_t const * p_backend)
{
    queue_element_drop(mp_crashlog_queue);
}

void nrf_log_backend_flashlog_panic_set(nrf_log_backend_t const * p_backend)
{
    /* Empty */
}

/**
 * @brief Function for injecting log message which will indicate start of crash log.
 */
static void crashlog_marker_inject(void)
{
    nrf_log_header_t crashlog_marker_hdr = {
            .base = {
                .std = {
                     .type = HEADER_TYPE_STD,
                     .severity = NRF_LOG_SEVERITY_INFO_RAW,
                     .nargs = 0,
                     .addr = (uint32_t)crashlog_str & STD_ADDR_MASK
                }
            },
            .module_id = 0,
            .timestamp = 0,
    };
    m_flash_buf[0] = crashlog_marker_hdr.base.raw;
    m_flash_buf[1] = crashlog_marker_hdr.module_id;
    m_flash_buf[2] = crashlog_marker_hdr.timestamp;
    (void)nrf_fstorage_write(&m_log_flash_fstorage, m_curr_addr, m_flash_buf, LOG_HEADER_LEN, NULL);
    m_curr_addr += LOG_HEADER_LEN;
}


void nrf_log_backend_crashlog_panic_set(nrf_log_backend_t const * p_backend)
{
    if (nrf_fstorage_init(&m_log_flash_fstorage, &nrf_fstorage_nvmc, NULL) == NRF_SUCCESS)
    {
        m_state = LOG_BACKEND_FLASH_IN_PANIC;

        /* In case of Softdevice MWU may protect access to NVMC. */
        NVIC_DisableIRQ(MWU_IRQn);

        log_msg_queue_process(mp_flashlog_queue, true);

        crashlog_marker_inject();

        log_msg_queue_process(mp_crashlog_queue, true);
    }
    else
    {
        m_state = LOG_BACKEND_FLASH_INACTIVE;
    }
}

/**
 * @brief Function for determining first empty location in area dedicated for flash logger backend.
 */
static uint32_t empty_addr_get(void)
{
    uint32_t token = 0;
    nrf_log_header_t * p_dummy_header;
    uint8_t * p_dummy_data;

    while(nrf_log_backend_flash_next_entry_get(&token, &p_dummy_header, &p_dummy_data) == NRF_SUCCESS)
    {

    }

    return token;
}


ret_code_t nrf_log_backend_flash_init(nrf_fstorage_api_t const * p_fs_api)
{
    ret_code_t err_code;


    uint32_t start_addr = RUNTIME_START_ADDR;
    uint32_t end_addr   = start_addr + FLASH_LOG_SIZE - 1;

    m_log_flash_fstorage.start_addr = start_addr;
    m_log_flash_fstorage.end_addr   = end_addr;

    err_code = nrf_fstorage_init(&m_log_flash_fstorage, p_fs_api, NULL);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    m_curr_addr = empty_addr_get();
    m_state  = LOG_BACKEND_FLASH_ACTIVE;

    return err_code;
}


ret_code_t nrf_log_backend_flash_next_entry_get(uint32_t *                p_token,
                                                nrf_log_header_t * *      pp_header,
                                                uint8_t * *               pp_data)
{
    uint32_t * p_addr = p_token;
    uint32_t   len;

    *p_addr = (*p_addr == 0) ? RUNTIME_START_ADDR : *p_addr;

    if (nrf_fstorage_rmap(&m_log_flash_fstorage, *p_addr) == NULL)
    {
        //Supports only memories which can be mapped for reading.
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if (msg_from_buf((uint32_t *)*p_addr, pp_header, pp_data, &len))
    {
        *p_addr += len;
        return NRF_SUCCESS;
    }
    else
    {
        return NRF_ERROR_NOT_FOUND;
    }
}


ret_code_t nrf_log_backend_flash_erase(void)
{
    ret_code_t err_code;

    m_state = LOG_BACKEND_FLASH_INACTIVE;
    err_code = nrf_fstorage_erase(&m_log_flash_fstorage, RUNTIME_START_ADDR, NRF_LOG_BACKEND_PAGES, NULL);
    
    m_curr_addr = RUNTIME_START_ADDR;

    return err_code;
}

#if NRF_LOG_BACKEND_FLASHLOG_ENABLED
const nrf_log_backend_api_t nrf_log_backend_flashlog_api = {
        .put       = nrf_log_backend_flashlog_put,
        .flush     = nrf_log_backend_flashlog_flush,
        .panic_set = nrf_log_backend_flashlog_panic_set,
};
#endif

#if NRF_LOG_BACKEND_CRASHLOG_ENABLED
const nrf_log_backend_api_t nrf_log_backend_crashlog_api = {
        .put       = nrf_log_backend_crashlog_put,
        .flush     = nrf_log_backend_crashlog_flush,
        .panic_set = nrf_log_backend_crashlog_panic_set,
};
#endif

#if NRF_LOG_BACKEND_FLASH_CLI_CMDS
#include "nrf_cli.h"

static uint8_t m_buffer[64];
static nrf_cli_t const * mp_cli;

static void cli_tx(void const * p_context, char const * p_buffer, size_t len);

static nrf_fprintf_ctx_t m_fprintf_ctx =
{
    .p_io_buffer    = (char *)m_buffer,
    .io_buffer_size = sizeof(m_buffer)-1,
    .io_buffer_cnt  = 0,
    .auto_flush     = true,
    .p_user_ctx     = &mp_cli,
    .fwrite         = cli_tx
};


static void flashlog_clear_cmd(nrf_cli_t const * p_cli, size_t argc, char ** argv)
{
    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
    }

    UNUSED_RETURN_VALUE(nrf_log_backend_flash_erase());
}

#include "nrf_delay.h"
static void cli_tx(void const * p_context, char const * p_buffer, size_t len)
{
    nrf_cli_t * * pp_cli = (nrf_cli_t * *)p_context;
    char * p_strbuf = (char *)&p_buffer[len];
    *p_strbuf = '\0';
    nrf_cli_fprintf((nrf_cli_t const *)*pp_cli, NRF_CLI_DEFAULT, p_buffer);
   // nrf_delay_ms(10);
}


static void entry_process(nrf_cli_t const * p_cli, nrf_log_header_t * p_header, uint8_t * p_data)
{
    mp_cli = p_cli;

    nrf_log_str_formatter_entry_params_t params =
    {
        .timestamp  = p_header->timestamp,
        .module_id  = p_header->module_id,
        .use_colors = 0,
    };

    switch (p_header->base.generic.type)
    {
        case HEADER_TYPE_STD:
        {
            params.severity = (nrf_log_severity_t)p_header->base.std.severity;
            nrf_log_std_entry_process((const char *)((uint32_t)p_header->base.std.addr),
                                      (uint32_t *)p_data,
                                      p_header->base.std.nargs,
                                      &params,
                                      &m_fprintf_ctx);
            break;
        }
        case HEADER_TYPE_HEXDUMP:
        {
            params.severity = (nrf_log_severity_t)p_header->base.hexdump.severity;

            nrf_log_hexdump_entry_process(p_data,
                                          p_header->base.hexdump.len,
                                          &params,
                                          &m_fprintf_ctx);
            break;
        }
        default:
            ASSERT(0);
    }

}


static void flashlog_read_cmd(nrf_cli_t const * p_cli, size_t argc, char ** argv)
{
    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
    }

    uint32_t           token  = 0;
    uint8_t *          p_data = NULL;
    bool               empty  = true;
    nrf_log_header_t * p_header;

    while (1)
    {
        if (nrf_log_backend_flash_next_entry_get(&token, &p_header, &p_data) == NRF_SUCCESS)
        {
            entry_process(p_cli, p_header, p_data);
            empty = false;
        }
        else
        {
            break;
        }
    }

    if (empty)
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Flash log empty\r\n");
    }
}


static void flashlog_status_cmd(nrf_cli_t const * p_cli, size_t argc, char ** argv)
{
    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
    }

    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "Flash log status:\r\n");
    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "\t\t- Location (address: 0x%08X, length: %d)\r\n",
                                                                RUNTIME_START_ADDR, FLASH_LOG_SIZE);
    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "\t\t- Current usage:%d%% (%d of %d bytes used)\r\n",
                                       100ul * (m_curr_addr - RUNTIME_START_ADDR)/FLASH_LOG_SIZE,
                                       m_curr_addr - RUNTIME_START_ADDR,
                                       FLASH_LOG_SIZE);
    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "\t\t- Dropped logs: %d\r\n", m_dropped);


}


NRF_CLI_CREATE_STATIC_SUBCMD_SET(m_flashlog_cmd)
{
    NRF_CLI_CMD(clear,   NULL, "Remove logs",      flashlog_clear_cmd),
    NRF_CLI_CMD(read,    NULL, "Read stored logs", flashlog_read_cmd),
    NRF_CLI_CMD(status,  NULL, "Flash log status", flashlog_status_cmd),
    NRF_CLI_SUBCMD_SET_END
};

NRF_CLI_CMD_REGISTER(flashlog, &m_flashlog_cmd, "Commands for reading logs stored in non-volatile memory", NULL);

#endif //NRF_LOG_BACKEND_FLASH_CLI_CMDS

#endif //NRF_MODULE_ENABLED(NRF_LOG) && NRF_MODULE_ENABLED(NRF_LOG_BACKEND_FLASH)
