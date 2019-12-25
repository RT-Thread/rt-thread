/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(PEER_MANAGER) && NRF_MODULE_ENABLED(PM_RA_PROTECTION)
#include "auth_status_tracker.h"

#include "app_timer.h"
#include "id_manager.h"

#define NRF_LOG_MODULE_NAME     peer_manager_ast
#if PM_LOG_ENABLED
    #define NRF_LOG_LEVEL       PM_LOG_LEVEL
    #define NRF_LOG_INFO_COLOR  PM_LOG_INFO_COLOR
    #define NRF_LOG_DEBUG_COLOR PM_LOG_DEBUG_COLOR
#else
    #define NRF_LOG_LEVEL       0
#endif // PM_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();
#include "nrf_strerror.h"

// Assume that waiting interval doubles with each failed authentication.
//lint --emacro((647),PENALITY_LVL_TO_PENALITY_MS)
#define PAIR_REWARD_TICKS                    APP_TIMER_TICKS(PM_RA_PROTECTION_REWARD_PERIOD)
#define PENALITY_LVL_TO_PENALITY_MS(_lvl)    (PM_RA_PROTECTION_MIN_WAIT_INTERVAL * (1 << _lvl))
#define PENALITY_LVL_TO_PENALITY_TICKS(_lvl) APP_TIMER_TICKS(PENALITY_LVL_TO_PENALITY_MS(_lvl))
#define PENALITY_LVL_NEXT_SET(_lvl)                                                      \
    _lvl = (PENALITY_LVL_TO_PENALITY_MS(_lvl) >= (PM_RA_PROTECTION_MAX_WAIT_INTERVAL)) ? \
           (_lvl) : (_lvl + 1)


/**@brief Tracked peer state. */
typedef struct
{
    ble_gap_addr_t peer_addr;      /**< BLE address, used to identify peer. */
    uint32_t       reward_ticks;   /**< Accumulated reward ticks, used to decrease penality level
                                        after achieving certain threshold. */
    uint32_t       penality_ticks; /**< Accumulated penality ticks, used to determine remaining time
                                        in which pairing attempts should be rejected. */
    uint8_t        penality_lvl;   /**< Accumulated penality level, used to determine waiting interval
                                        after failed authorization attempt. */
    bool           is_active;      /**< Flag indicating that the waiting interval for this peer has not
                                        passed yet. */
    bool           is_valid;       /**< Flag indicating that this entry is valid in the peer blacklist. */
} blacklisted_peer_t;

APP_TIMER_DEF(m_pairing_attempt_timer);
static blacklisted_peer_t m_blacklisted_peers[PM_RA_PROTECTION_TRACKED_PEERS_NUM];
static uint32_t           m_ticks_cnt;


/**@brief Function for updating the state of blacklisted peers after timer has been stopped or
 *        timed out.
 *
 * @param[in]  ticks_passed  The number of ticks since the timer has started.
 */
static uint32_t blacklisted_peers_state_update(uint32_t ticks_passed)
{
    uint32_t minimal_ticks = UINT32_MAX;

    for (uint32_t id = 0; id < ARRAY_SIZE(m_blacklisted_peers); id++)
    {
        blacklisted_peer_t * p_bl_peer = &m_blacklisted_peers[id];

        if (p_bl_peer->is_valid)
        {
            if (p_bl_peer->is_active)
            {
                if (p_bl_peer->penality_ticks > ticks_passed)
                {
                    p_bl_peer->penality_ticks -= ticks_passed;
                    minimal_ticks              = MIN(minimal_ticks, p_bl_peer->penality_ticks);
                }
                else
                {
                    p_bl_peer->is_active = false;

                    if (p_bl_peer->penality_lvl == 0)
                    {
                        p_bl_peer->is_valid = false;
                        NRF_LOG_DEBUG("Peer has been removed from the blacklist, its address:");
                        NRF_LOG_HEXDUMP_DEBUG(p_bl_peer->peer_addr.addr,
                                              sizeof(p_bl_peer->peer_addr.addr));
                    }
                    else
                    {
                        minimal_ticks = MIN(minimal_ticks, PAIR_REWARD_TICKS);
                    }

                    NRF_LOG_DEBUG("Pairing waiting interval has expired for:");
                    NRF_LOG_HEXDUMP_DEBUG(p_bl_peer->peer_addr.addr,
                                          sizeof(p_bl_peer->peer_addr.addr));
                }
            }
            else
            {
                if (p_bl_peer->penality_lvl == 0)
                {
                    p_bl_peer->is_valid = false;
                    NRF_LOG_DEBUG("Peer has been removed from the blacklist, its address:");
                    NRF_LOG_HEXDUMP_DEBUG(p_bl_peer->peer_addr.addr,
                                          sizeof(p_bl_peer->peer_addr.addr));
                }
                else
                {
                    p_bl_peer->reward_ticks += ticks_passed;
                    if (p_bl_peer->reward_ticks >= PAIR_REWARD_TICKS)
                    {
                        p_bl_peer->penality_lvl--;
                        p_bl_peer->reward_ticks -= PAIR_REWARD_TICKS;
                        NRF_LOG_DEBUG("Peer penality level has decreased to %d for device:",
                                      p_bl_peer->penality_lvl);
                        NRF_LOG_HEXDUMP_DEBUG(p_bl_peer->peer_addr.addr,
                                              sizeof(p_bl_peer->peer_addr.addr));
                    }

                    minimal_ticks = MIN(minimal_ticks,
                                        (PAIR_REWARD_TICKS - p_bl_peer->reward_ticks));
                }
            }
        }
    }

    return minimal_ticks;
}


/**@brief Function for handling state transition of blacklisted peers.
 *
 * @param[in]  context  Context containing the number of ticks since the timer has started.
 */
static void blacklisted_peers_state_transition_handle(void * context)
{
    ret_code_t err_code;
    uint32_t   minimal_ticks;
    uint32_t   ticks_passed = (uint32_t) context;

    minimal_ticks = blacklisted_peers_state_update(ticks_passed);
    m_ticks_cnt   = app_timer_cnt_get();

    if (minimal_ticks != UINT32_MAX)
    {
        err_code = app_timer_start(m_pairing_attempt_timer,
                                   minimal_ticks,
                                   (void *) minimal_ticks);
        if (err_code != NRF_SUCCESS)
        {
            NRF_LOG_WARNING("app_timer_start() returned %s", nrf_strerror_get(err_code));
        }
        NRF_LOG_DEBUG("Restarting the timer");
    }
}


ret_code_t ast_init(void)
{
    ret_code_t err_code = app_timer_create(&m_pairing_attempt_timer,
                                           APP_TIMER_MODE_SINGLE_SHOT,
                                           blacklisted_peers_state_transition_handle);

    return err_code;
}


void ast_auth_error_notify(uint16_t conn_handle)
{
    ret_code_t     err_code;
    ble_gap_addr_t peer_addr;
    uint32_t       new_timeout;
    uint32_t       free_id      = ARRAY_SIZE(m_blacklisted_peers);
    bool           new_bl_entry = true;

    // Get the peer address associated with connection handle.
    err_code = im_ble_addr_get(conn_handle, &peer_addr);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_WARNING("im_ble_addr_get() returned %s. conn_handle: %d. "
                        "Link was likely disconnected.",
                        nrf_strerror_get(err_code),
                        conn_handle);
        return;
    }

    // Stop the timer and update the state of all blacklisted peers.
    err_code = app_timer_stop(m_pairing_attempt_timer);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_WARNING("app_timer_stop() returned %s", nrf_strerror_get(err_code));
        return;
    }

    new_timeout = blacklisted_peers_state_update(app_timer_cnt_diff_compute(app_timer_cnt_get(),
                                                                            m_ticks_cnt));
    m_ticks_cnt = app_timer_cnt_get();

    // Check if authorization has failed for already blacklisted peer.
    for (uint32_t id = 0; id < ARRAY_SIZE(m_blacklisted_peers); id++)
    {
        blacklisted_peer_t * p_bl_peer = &m_blacklisted_peers[id];

        if (p_bl_peer->is_valid)
        {
            if (memcmp(peer_addr.addr, p_bl_peer->peer_addr.addr, BLE_GAP_ADDR_LEN) == 0)
            {
                uint8_t lvl = p_bl_peer->penality_lvl;

                PENALITY_LVL_NEXT_SET(lvl);
                p_bl_peer->penality_lvl   = lvl;
                p_bl_peer->reward_ticks   = 0;
                p_bl_peer->penality_ticks = PENALITY_LVL_TO_PENALITY_TICKS(lvl);

                new_timeout = MIN(new_timeout, p_bl_peer->penality_ticks);

                p_bl_peer->is_active = true;
                new_bl_entry         = false;

                NRF_LOG_DEBUG("Pairing waiting interval has been renewed. "
                              "Penality level: %d for device:",
                              lvl);
                NRF_LOG_HEXDUMP_DEBUG(p_bl_peer->peer_addr.addr,
                                      sizeof(p_bl_peer->peer_addr.addr));
            }
        }
        else
        {
            free_id = id;
        }
    }

    // Add a new peer to the blacklist.
    if (new_bl_entry)
    {
        if (free_id < ARRAY_SIZE(m_blacklisted_peers))
        {
            blacklisted_peer_t * p_bl_peer = &m_blacklisted_peers[free_id];

            memcpy(&p_bl_peer->peer_addr, &peer_addr, sizeof(peer_addr));

            p_bl_peer->penality_lvl   = 0;
            p_bl_peer->reward_ticks   = 0;
            p_bl_peer->penality_ticks = PENALITY_LVL_TO_PENALITY_TICKS(p_bl_peer->penality_lvl);

            new_timeout = MIN(new_timeout, p_bl_peer->penality_ticks);

            p_bl_peer->is_active = true;
            p_bl_peer->is_valid  = true;
            NRF_LOG_DEBUG("New peer has been added to the blacklist:");
            NRF_LOG_HEXDUMP_DEBUG(p_bl_peer->peer_addr.addr, sizeof(p_bl_peer->peer_addr.addr));
        }
        else
        {
            NRF_LOG_WARNING("No space to blacklist another peer ID");
        }
    }

    // Restart the timer.
    if (new_timeout != UINT32_MAX)
    {
        err_code = app_timer_start(m_pairing_attempt_timer,
                                   new_timeout,
                                   (void *) new_timeout);
        if (err_code != NRF_SUCCESS)
        {
            NRF_LOG_WARNING("app_timer_start() returned %s", nrf_strerror_get(err_code));
        }
    }
}


bool ast_peer_blacklisted(uint16_t conn_handle)
{
    ret_code_t     err_code;
    ble_gap_addr_t peer_addr;

    err_code = im_ble_addr_get(conn_handle, &peer_addr);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_WARNING("im_ble_addr_get() returned %s. conn_handle: %d. "
                        "Link was likely disconnected.",
                        nrf_strerror_get(err_code),
                        conn_handle);
        return true;
    }

    for (uint32_t id = 0; id < ARRAY_SIZE(m_blacklisted_peers); id++)
    {
        blacklisted_peer_t * p_bl_peer = &m_blacklisted_peers[id];

        if (p_bl_peer->is_valid)
        {
            if ((memcmp(peer_addr.addr, p_bl_peer->peer_addr.addr, BLE_GAP_ADDR_LEN) == 0) &&
                (p_bl_peer->is_active))
            {
                return true;
            }
        }
    }

    return false;
}


#endif // NRF_MODULE_ENABLED(PEER_MANAGER) && NRF_MODULE_ENABLED(PM_RA_PROTECTION)
