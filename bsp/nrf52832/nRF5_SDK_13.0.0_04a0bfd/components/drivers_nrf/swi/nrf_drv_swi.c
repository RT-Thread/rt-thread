/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#include "nrf_drv_common.h"
#include "nrf_error.h"
#include "nrf_assert.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "nrf_drv_swi.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME "SWI"

#if EGU_ENABLED
#if SWI_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       SWI_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  SWI_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR SWI_CONFIG_DEBUG_COLOR
#else //SWI_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif //SWI_CONFIG_LOG_ENABLED
#endif //EGU_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

STATIC_ASSERT(SWI_COUNT > 0);
STATIC_ASSERT(SWI_COUNT <= SWI_MAX);

#ifdef SWI_DISABLE0
 #undef SWI_DISABLE0
 #define SWI_DISABLE0  1uL
#else
 #if SWI_COUNT > 0
  #define SWI_DISABLE0 0uL
 #else
  #define SWI_DISABLE0 1uL
 #endif
#endif

#ifdef SWI_DISABLE1
 #undef SWI_DISABLE1
 #define SWI_DISABLE1  1uL
#else
 #if SWI_COUNT > 1
  #define SWI_DISABLE1 0uL
 #else
  #define SWI_DISABLE1 1uL
 #endif
#endif

#ifdef SWI_DISABLE2
 #undef SWI_DISABLE2
 #define SWI_DISABLE2  1uL
#else
 #if SWI_COUNT > 2
  #define SWI_DISABLE2 0uL
 #else
  #define SWI_DISABLE2 1uL
 #endif
#endif

#ifdef SWI_DISABLE3
 #undef SWI_DISABLE3
 #define SWI_DISABLE3  1uL
#else
 #if SWI_COUNT > 3
  #define SWI_DISABLE3 0uL
 #else
  #define SWI_DISABLE3 1uL
 #endif
#endif

#ifdef SWI_DISABLE4
 #undef SWI_DISABLE4
 #define SWI_DISABLE4  1uL
#else
 #if SWI_COUNT > 4
  #define SWI_DISABLE4 0uL
 #else
  #define SWI_DISABLE4 1uL
 #endif
#endif

#ifdef SWI_DISABLE5
 #undef SWI_DISABLE5
 #define SWI_DISABLE5  1uL
#else
 #if SWI_COUNT > 5
  #define SWI_DISABLE5 0uL
 #else
  #define SWI_DISABLE5 1uL
 #endif
#endif

#define SWI_START_NUMBER ( (SWI_DISABLE0)                                                             \
                         + (SWI_DISABLE0 * SWI_DISABLE1)                                              \
                         + (SWI_DISABLE0 * SWI_DISABLE1 * SWI_DISABLE2)                               \
                         + (SWI_DISABLE0 * SWI_DISABLE1 * SWI_DISABLE2 * SWI_DISABLE3)                \
                         + (SWI_DISABLE0 * SWI_DISABLE1 * SWI_DISABLE2 * SWI_DISABLE3 * SWI_DISABLE4) \
                         + (SWI_DISABLE0 * SWI_DISABLE1 * SWI_DISABLE2 * SWI_DISABLE3 * SWI_DISABLE4  \
                            * SWI_DISABLE5) )

#define SWI_ARRAY_SIZE   (SWI_COUNT - SWI_START_NUMBER)

#if (SWI_COUNT <= SWI_START_NUMBER)
  #undef SWI_ARRAY_SIZE
  #define SWI_ARRAY_SIZE 1
#endif

static nrf_drv_state_t   m_drv_state = NRF_DRV_STATE_UNINITIALIZED;
static nrf_swi_handler_t m_swi_handlers[SWI_ARRAY_SIZE];

#if !EGU_ENABLED
static nrf_swi_flags_t   m_swi_flags[SWI_ARRAY_SIZE];
#endif

/**@brief Function for getting max channel number of given SWI.
 *
 * @param[in]  swi                 SWI number.
 * @return     number of available channels.
 */
#if NRF_MODULE_ENABLED(EGU)
__STATIC_INLINE uint32_t swi_channel_number(nrf_swi_t swi)
{
    uint32_t retval = 0;
    switch(swi){
        case 0:
                retval = EGU0_CH_NUM;
                break;
        case 1:
                retval = EGU1_CH_NUM;
                break;
        case 2:
                retval = EGU2_CH_NUM;
                break;
        case 3:
                retval = EGU3_CH_NUM;
                break;
        case 4:
                retval = EGU4_CH_NUM;
                break;
        case 5:
                retval = EGU5_CH_NUM;
                break;
        default:
            retval = 0;
    }

    return retval;
}
#else
#define swi_channel_number(swi) SWI_MAX_FLAGS
#endif

#if NRF_MODULE_ENABLED(EGU)

/**@brief Get the specific EGU instance. */
__STATIC_INLINE NRF_EGU_Type * egu_instance_get(nrf_swi_t swi)
{
    return (NRF_EGU_Type*) (NRF_EGU0_BASE + (((uint32_t) swi) * (NRF_EGU1_BASE - NRF_EGU0_BASE)));
}

/**@brief Software interrupt handler (using EGU). */
static void nrf_drv_swi_process(nrf_swi_t swi)
{
    ASSERT(m_swi_handlers[swi - SWI_START_NUMBER]);
    nrf_swi_flags_t flags   = 0;
    NRF_EGU_Type * NRF_EGUx = egu_instance_get(swi);

    for (uint8_t i = 0; i < swi_channel_number(swi); ++i)
    {
        nrf_egu_event_t egu_event = nrf_egu_event_triggered_get(NRF_EGUx, i);
        if (nrf_egu_event_check(NRF_EGUx, egu_event))
        {
            flags |= (1u << i);
            nrf_egu_event_clear(NRF_EGUx, egu_event);
        }
    }

    m_swi_handlers[swi - SWI_START_NUMBER](swi, flags);
}

#define SWI_HANDLER_TEMPLATE(NUM)  void SWI##NUM##_EGU##NUM##_IRQHandler(void) \
                        {                                                      \
                            nrf_drv_swi_process(NUM);                          \
                        }

#else

/**@brief Software interrupt handler (without EGU). */
static void nrf_drv_swi_process(nrf_swi_t swi, nrf_swi_flags_t flags)
{
    ASSERT(m_swi_handlers[swi - SWI_START_NUMBER]);
    m_swi_flags[swi - SWI_START_NUMBER] &= ~flags;
    m_swi_handlers[swi - SWI_START_NUMBER](swi, flags);
}


#define SWI_HANDLER_TEMPLATE(NUM)  void SWI##NUM##_IRQHandler(void)                            \
                        {                                                                      \
                            nrf_drv_swi_process((NUM), m_swi_flags[(NUM) - SWI_START_NUMBER]); \
                        }

#endif

#if SWI_DISABLE0 == 0
SWI_HANDLER_TEMPLATE(0)
#endif

#if SWI_DISABLE1 == 0
SWI_HANDLER_TEMPLATE(1)
#endif

#if SWI_DISABLE2 == 0
SWI_HANDLER_TEMPLATE(2)
#endif

#if SWI_DISABLE3 == 0
SWI_HANDLER_TEMPLATE(3)
#endif

#if SWI_DISABLE4 == 0
SWI_HANDLER_TEMPLATE(4)
#endif

#if SWI_DISABLE5 == 0
SWI_HANDLER_TEMPLATE(5)
#endif

#define AVAILABLE_SWI (0x3FuL & ~(                                                       \
                         (SWI_DISABLE0 << 0) | (SWI_DISABLE1 << 1) | (SWI_DISABLE2 << 2) \
                       | (SWI_DISABLE3 << 3) | (SWI_DISABLE4 << 4) | (SWI_DISABLE5 << 5) \
                                 ))

#if (AVAILABLE_SWI == 0)
 #warning No available SWIs.
#endif

/**@brief Function for converting SWI number to system interrupt number.
 *
 * @param[in]  swi                 SWI number.
 *
 * @retval     IRQ number.
 */
__STATIC_INLINE IRQn_Type nrf_drv_swi_irq_of(nrf_swi_t swi)
{
    return (IRQn_Type)((uint32_t)SWI0_IRQn + (uint32_t)swi);
}


/**@brief Function for checking if given SWI is allocated.
 *
 * @param[in]  swi                 SWI number.
 */
__STATIC_INLINE bool swi_is_allocated(nrf_swi_t swi)
{
    ASSERT(swi < SWI_COUNT);
#if SWI_START_NUMBER > 0
    if (swi < SWI_START_NUMBER)
    {
        return false;
    }
#endif
    /*lint -e(661) out of range case handled by assert above*/
    return m_swi_handlers[swi - SWI_START_NUMBER];
}

ret_code_t nrf_drv_swi_init(void)
{
    ret_code_t err_code;

    if (m_drv_state == NRF_DRV_STATE_UNINITIALIZED)
    {
        m_drv_state = NRF_DRV_STATE_INITIALIZED;
        err_code = NRF_SUCCESS;
        NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    err_code = NRF_ERROR_MODULE_ALREADY_INITIALIZED;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}


void nrf_drv_swi_uninit(void)
{
    ASSERT(m_drv_state != NRF_DRV_STATE_UNINITIALIZED)

    for (uint32_t i = SWI_START_NUMBER; i < SWI_COUNT; ++i)
    {
        m_swi_handlers[i - SWI_START_NUMBER] = NULL;
        nrf_drv_common_irq_disable(nrf_drv_swi_irq_of((nrf_swi_t) i));
#if NRF_MODULE_ENABLED(EGU)
        NRF_EGU_Type * NRF_EGUx = egu_instance_get(i);
        nrf_egu_int_disable(NRF_EGUx, NRF_EGU_INT_ALL);
#endif
    }
    m_drv_state = NRF_DRV_STATE_UNINITIALIZED;
    return;
}


void nrf_drv_swi_free(nrf_swi_t * p_swi)
{
    ASSERT(swi_is_allocated(*p_swi));
    nrf_drv_common_irq_disable(nrf_drv_swi_irq_of(*p_swi));
    m_swi_handlers[(*p_swi) - SWI_START_NUMBER] = NULL;
    *p_swi = NRF_SWI_UNALLOCATED;
}


ret_code_t nrf_drv_swi_alloc(nrf_swi_t * p_swi, nrf_swi_handler_t event_handler, uint32_t priority)
{
#if !NRF_MODULE_ENABLED(EGU)
    ASSERT(event_handler);
#endif
    uint32_t err_code = NRF_ERROR_NO_MEM;

    for (uint32_t i = SWI_START_NUMBER; i < SWI_COUNT; i++)
    {
        CRITICAL_REGION_ENTER();
        if ((!swi_is_allocated(i)) && (AVAILABLE_SWI & (1 << i)))
        {
            m_swi_handlers[i - SWI_START_NUMBER] = event_handler;
            *p_swi = (nrf_swi_t) i;
            nrf_drv_common_irq_enable(nrf_drv_swi_irq_of(*p_swi), priority);
#if NRF_MODULE_ENABLED(EGU)
            if(event_handler != NULL)
            {
                NRF_EGU_Type * NRF_EGUx = egu_instance_get(i);
                nrf_egu_int_enable(NRF_EGUx, NRF_EGU_INT_ALL);
            }
#endif
            err_code = NRF_SUCCESS;
        }
        CRITICAL_REGION_EXIT();
        if (err_code == NRF_SUCCESS)
        {
            NRF_LOG_INFO("SWI channel allocated: %d.\r\n", (*p_swi));
            break;
        }
    }
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}


void nrf_drv_swi_trigger(nrf_swi_t swi, uint8_t flag_number)
{
    ASSERT(swi_is_allocated((uint32_t) swi));
    ASSERT(flag_number < swi_channel_number(swi));
#if NRF_MODULE_ENABLED(EGU)
    NRF_EGU_Type * NRF_EGUx = egu_instance_get(swi);
    nrf_egu_task_trigger(NRF_EGUx, nrf_egu_task_trigger_get(NRF_EGUx, flag_number));
#else
    m_swi_flags[swi - SWI_START_NUMBER] |= (1 << flag_number);
    NVIC_SetPendingIRQ(nrf_drv_swi_irq_of(swi));
#endif
}


#if NRF_MODULE_ENABLED(EGU)

uint32_t nrf_drv_swi_task_trigger_address_get(nrf_swi_t swi, uint8_t channel)
{
    NRF_EGU_Type * NRF_EGUx = egu_instance_get(swi);
    return (uint32_t) nrf_egu_task_trigger_address_get(NRF_EGUx, channel);
}

uint32_t nrf_drv_swi_event_triggered_address_get(nrf_swi_t swi, uint8_t channel)
{
    NRF_EGU_Type * NRF_EGUx = egu_instance_get(swi);
    return (uint32_t) nrf_egu_event_triggered_address_get(NRF_EGUx, channel);
}

#endif
