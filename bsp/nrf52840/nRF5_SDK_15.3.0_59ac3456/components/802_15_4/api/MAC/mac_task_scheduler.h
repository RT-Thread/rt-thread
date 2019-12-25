/**
 * Copyright (c) 2016 - 2019 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 *
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
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
#ifndef MAC_TASK_SCHEDULER_H_INCLUDED
#define MAC_TASK_SCHEDULER_H_INCLUDED

#include <stdint.h>
#include "sys_queue.h"
#include "sys_time.h"

/** @file
 *
 * @defgroup mac_task_scheduler MAC task scheduler
 * @ingroup mac_15_4
 * @{
 * @brief Module for MAC task scheduling.
 */

/**@brief Identifiers for external requests.
 */
typedef enum
{
#if (CONFIG_PURGE_ENABLED == 1)
    MAC_PURGE_REQ_ID,
#endif
#if (CONFIG_ASSOCIATE_REQ_ENABLED == 1)
    MAC_ASSOCIATE_REQ_ID,
#endif
#if (CONFIG_DISASSOCIATE_ENABLED == 1)
    MAC_DISASSOCIATE_REQ_ID,
#endif
    MAC_GET_REQ_ID,
#if (CONFIG_GTS_ENABLED == 1)
    MAC_GTS_REQ_ID,
#endif
    MAC_RESET_REQ_ID,
#if (CONFIG_RXE_ENABLED == 1)
    MAC_RX_ENABLE_REQ_ID,
#endif
    MAC_SCAN_REQ_ID,
    MAC_SET_REQ_ID,
#if (CONFIG_SYNC_REQ_ENABLED == 1)
    MAC_SYNC_REQ_ID,
#endif
    MAC_POLL_REQ_ID,
#if (CONFIG_START_ENABLED == 1)
    MAC_START_REQ_ID,
#endif
    MAC_DATA_REQ_ID,
#if (CONFIG_ORPHAN_ENABLED == 1)
    MAC_ORPHAN_RESP_ID,
#endif
    MAC_REQS_AMOUNT
} mac_req_id_t;


/**@brief Identifiers for internal handlers.
 *
 * These handlers are used for private MAC task scheduling.
 */
typedef enum
{
#if (CONFIG_FFD_DEVICE == 1) && (CONFIG_BEACON_ENABLED == 1)
    MAC_SUPERFRAME_OUT_TASK_ID,
#endif
    MAC_CSMA_CA_TASK_ID,
#if (CONFIG_START_ENABLED == 1)
    MAC_START_TASK_ID,
#endif
    MAC_FP_TX_TASK_ID,
    MAC_DATA_DIR_CONF_ID,
#if (CONFIG_INDIRECT_ENGINE_ENABLED == 1)
    MAC_INDIR_ENGINE_REQ_ID,
#endif
    MAC_FP_RX_TASK_ID,
#if (CONFIG_ORPHAN_ENABLED == 1)
    MAC_ORPHAN_IND_ID,
#endif
#if (CONFIG_DISASSOCIATE_ENABLED == 1)
    MAC_DISASSOC_IND_ID,
#endif
#if (CONFIG_SYNC_ENABLED == 1)
    MAC_SYNC_LOSS_IND_ID,
#endif
    MAC_GET_CONF_ID,
    MAC_SET_CONF_ID,
    MAC_REQ_QUEUE_TASK_ID,
    MAC_POLL_TASK_ID,
    MAC_SCAN_CONF_ID,
    MAC_MEM_ALLOCATOR_TASK_ID,
    MAC_TASKS_AMOUNT
} mac_task_id_t;


/**@brief MAC request descriptor.
 */
typedef struct
{
    sys_queue_item_t item;
    mac_req_id_t     id;
    void *           p_conf_cb; //pointer to confirmation primitive
} mac_abstract_req_t;

/**@brief scheduler memory.
 */
typedef struct
{
    sys_queue_t          outer_req_queue;
    volatile uint32_t    pending_tasks;
    bool                 mac_scheduler_busy;
} mac_scheduler_mem_t;

/**@brief MAC task handler prototype.
 *
 * @details Handler which will be called by the MAC scheduler.
 */
typedef void (* mac_task_handler_t)(void);

/**@brief MAC external requests queue task handler prototype.
 *
 * @details Handler which will be called by the MAC scheduler inside
 * corresponding task handler.
 */
typedef void (* mac_req_handler_t)(mac_abstract_req_t *);

/**@brief       Initialize MAC scheduler.
 *
 * @details     Clean up MAC request's queue.
 */
void mac_init(void);

/**@brief       MAC task handler.
 *
 * @details     Handler invokes a MAC primitives routine for a request according to
 *              the requests identification.
 */
void mac_task_handler(void);

/**@brief       Scheduler request from some MAC primitive.
 *
 * @details     Place request to MAC scheduler queue for a further handling.
 *
 * @param[in]   p_req   Pointer to a request structure.
 */
void mac_request_schedule(mac_abstract_req_t * p_req);

/**@brief       Internal function of MAC API.
 *
 *              This function is used to post tasks between MAC primitives.
 *
 * @param[in]   id   MAC task ID.
 *
 */
void mac_internal_task_post(mac_task_id_t id);

/**@brief       Internal function of MAC API.
 *
 *              Notifies mac scheduler that incoming request has been completely
 *              served and may be safely removed from MAC task queue.
 *
 * @param[in]   p_req   Pointer to a request structure.
 */
void mac_close_request(mac_abstract_req_t * p_req);

/** @} */

#endif // MAC_TASK_SCHEDULER_H_INCLUDED
