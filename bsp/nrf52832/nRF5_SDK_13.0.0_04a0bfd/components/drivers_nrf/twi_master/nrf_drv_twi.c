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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(TWI)
#define ENABLED_TWI_COUNT (TWI0_ENABLED+TWI1_ENABLED)
#if ENABLED_TWI_COUNT
#include "nrf_drv_twi.h"
#include "nrf_drv_common.h"
#include "nrf_gpio.h"
#include "nrf_assert.h"
#include "app_util_platform.h"
#include "nrf_delay.h"

#include <stdio.h>

#define NRF_LOG_MODULE_NAME "TWI"

#if TWI_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       TWI_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  TWI_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR TWI_CONFIG_DEBUG_COLOR
#define EVT_TO_STR(event)   (event == NRF_DRV_TWI_EVT_DONE ? "EVT_DONE" :                            \
                            (event == NRF_DRV_TWI_EVT_ADDRESS_NACK ? "EVT_ADDRESS_NACK" :            \
                            (event == NRF_DRV_TWI_EVT_DATA_NACK ? "EVT_DATA_NACK" : "UNKNOWN ERROR")))
#define EVT_TO_STR_TWI(event)   (event == NRF_TWI_EVENT_STOPPED ? "NRF_TWI_EVENT_STOPPED" :                            \
                                (event == NRF_TWI_EVENT_RXDREADY ? "NRF_TWI_EVENT_RXDREADY" :                          \
                                (event == NRF_TWI_EVENT_TXDSENT ? "NRF_TWI_EVENT_TXDSENT" :                            \
                                (event == NRF_TWI_EVENT_ERROR ? "NRF_TWI_EVENT_ERROR" :                                \
                                (event == NRF_TWI_EVENT_BB ? "NRF_TWI_EVENT_BB" :                                      \
                                (event == NRF_TWI_EVENT_SUSPENDED ? "NRF_TWI_EVENT_SUSPENDED" : "UNKNOWN ERROR"))))))
#define EVT_TO_STR_TWIM(event)  (event == NRF_TWIM_EVENT_STOPPED ? "NRF_TWIM_EVENT_STOPPED" :                      \
                                (event == NRF_TWIM_EVENT_ERROR ? "NRF_TWIM_EVENT_ERROR" :                          \
                                (event == NRF_TWIM_EVENT_SUSPENDED ? "NRF_TWIM_EVENT_SUSPENDED" :                  \
                                (event == NRF_TWIM_EVENT_RXSTARTED ? "NRF_TWIM_EVENT_RXSTARTED" :                  \
                                (event == NRF_TWIM_EVENT_TXSTARTED ? "NRF_TWIM_EVENT_TXSTARTED" :                  \
                                (event == NRF_TWIM_EVENT_LASTRX ? "NRF_TWIM_EVENT_LASTRX" :                        \
                                (event == NRF_TWIM_EVENT_LASTTX ? "NRF_TWIM_EVENT_LASTTX" : "UNKNOWN ERROR")))))))
#define TRANSFER_TO_STR(type)   (type == NRF_DRV_TWI_XFER_TX ? "XFER_TX" :                             \
                                (type == NRF_DRV_TWI_XFER_RX ? "XFER_RX" :                             \
                                (type == NRF_DRV_TWI_XFER_TXRX ? "XFER_TXRX" :                         \
                                (type == NRF_DRV_TWI_XFER_TXTX ? "XFER_TXTX" : "UNKNOWN TRANSFER TYPE"))))
#else //TWI_CONFIG_LOG_ENABLED
#define EVT_TO_STR(event)           ""
#define EVT_TO_STR_TWI(event)       ""
#define EVT_TO_STR_TWIM(event)      ""
#define TRANSFER_TO_STR(event)      ""
#define NRF_LOG_LEVEL       0
#endif //TWI_CONFIG_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"


#define TWI0_IRQ_HANDLER    SPI0_TWI0_IRQHandler
#define TWI1_IRQ_HANDLER    SPI1_TWI1_IRQHandler

#if (defined(TWIM_IN_USE) && defined(TWI_IN_USE))
    // TWIM and TWI combined
    #define CODE_FOR_TWIM(code) if (p_instance->use_easy_dma) { code }
    #define CODE_FOR_TWI(code)  else { code }
#elif (defined(TWIM_IN_USE) && !defined(TWI_IN_USE))
    // TWIM only
    #define CODE_FOR_TWIM(code) { code }
    #define CODE_FOR_TWI(code)
#elif (!defined(TWIM_IN_USE) && defined(TWI_IN_USE))
    // TWI only
    #define CODE_FOR_TWIM(code)
    #define CODE_FOR_TWI(code)  { code }
#else
    #error "Wrong configuration."
#endif

// All interrupt flags
#define DISABLE_ALL_INT_SHORT  0xFFFFFFFF

#define SCL_PIN_INIT_CONF     ( (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos) \
                              | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
                              | (GPIO_PIN_CNF_PULL_Pullup    << GPIO_PIN_CNF_PULL_Pos)  \
                              | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
                              | (GPIO_PIN_CNF_DIR_Input      << GPIO_PIN_CNF_DIR_Pos))
#define SDA_PIN_INIT_CONF        SCL_PIN_INIT_CONF

#define SDA_PIN_UNINIT_CONF   ( (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) \
                              | (GPIO_PIN_CNF_DRIVE_H0H1       << GPIO_PIN_CNF_DRIVE_Pos) \
                              | (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  \
                              | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) \
                              | (GPIO_PIN_CNF_DIR_Input        << GPIO_PIN_CNF_DIR_Pos))
#define SCL_PIN_UNINIT_CONF      SDA_PIN_UNINIT_CONF

#define SCL_PIN_INIT_CONF_CLR ( (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos) \
                              | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
                              | (GPIO_PIN_CNF_PULL_Pullup    << GPIO_PIN_CNF_PULL_Pos)  \
                              | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
                              | (GPIO_PIN_CNF_DIR_Output     << GPIO_PIN_CNF_DIR_Pos))
#define SDA_PIN_INIT_CONF_CLR    SCL_PIN_INIT_CONF_CLR

#define HW_TIMEOUT      10000

// Control block - driver instance local data.
typedef struct
{
    nrf_drv_twi_evt_handler_t handler;
    void *                    p_context;
    volatile uint32_t         int_mask;
    nrf_drv_twi_xfer_desc_t   xfer_desc;
    uint32_t                  flags;
    uint8_t *                 p_curr_buf;
    uint8_t                   curr_length;
    bool                      curr_no_stop;
    nrf_drv_state_t           state;
    bool                      error;
    volatile bool             busy;
    bool                      repeated;
    uint8_t                   bytes_transferred;
    bool                      hold_bus_uninit;
#if NRF_MODULE_ENABLED(TWIM_NRF52_ANOMALY_109_WORKAROUND)
    nrf_twim_frequency_t      bus_frequency;
#endif
} twi_control_block_t;

static twi_control_block_t m_cb[ENABLED_TWI_COUNT];

#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    #define IRQ_HANDLER_NAME(n) irq_handler_for_instance_##n
    #define IRQ_HANDLER(n)      static void IRQ_HANDLER_NAME(n)(void)

    #if NRF_MODULE_ENABLED(TWI0)
        IRQ_HANDLER(0);
    #endif
    #if NRF_MODULE_ENABLED(TWI1)
        IRQ_HANDLER(1);
    #endif
    static nrf_drv_irq_handler_t const m_irq_handlers[ENABLED_TWI_COUNT] = {
    #if NRF_MODULE_ENABLED(TWI0)
        IRQ_HANDLER_NAME(0),
    #endif
    #if NRF_MODULE_ENABLED(TWI1)
        IRQ_HANDLER_NAME(1),
    #endif
    };
#else
    #define IRQ_HANDLER(n) void SPI##n##_TWI##n##_IRQHandler(void)
#endif // NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)

static ret_code_t twi_process_error(uint32_t errorsrc)
{
    ret_code_t ret = NRF_ERROR_INTERNAL;

    if (errorsrc & NRF_TWI_ERROR_OVERRUN)
    {
        ret = NRF_ERROR_DRV_TWI_ERR_OVERRUN;
    }

    if (errorsrc & NRF_TWI_ERROR_ADDRESS_NACK)
    {
        ret = NRF_ERROR_DRV_TWI_ERR_ANACK;
    }

    if (errorsrc & NRF_TWI_ERROR_DATA_NACK)
    {
        ret = NRF_ERROR_DRV_TWI_ERR_DNACK;
    }

    return ret;
}

static void twi_clear_bus(nrf_drv_twi_config_t const * p_config)
{
    NRF_GPIO->PIN_CNF[p_config->scl] = SCL_PIN_INIT_CONF;
    NRF_GPIO->PIN_CNF[p_config->sda] = SDA_PIN_INIT_CONF;

    nrf_gpio_pin_set(p_config->scl);
    nrf_gpio_pin_set(p_config->sda);

    NRF_GPIO->PIN_CNF[p_config->scl] = SCL_PIN_INIT_CONF_CLR;
    NRF_GPIO->PIN_CNF[p_config->sda] = SDA_PIN_INIT_CONF_CLR;

    nrf_delay_us(4);

    for (int i = 0; i < 9; i++)
    {
        if (nrf_gpio_pin_read(p_config->sda))
        {
            if (i == 0)
            {
                return;
            }
            else
            {
                break;
            }
        }
        nrf_gpio_pin_clear(p_config->scl);
        nrf_delay_us(4);
        nrf_gpio_pin_set(p_config->scl);
        nrf_delay_us(4);
    }
    nrf_gpio_pin_clear(p_config->sda);
    nrf_delay_us(4);
    nrf_gpio_pin_set(p_config->sda);
}

ret_code_t nrf_drv_twi_init(nrf_drv_twi_t const *        p_instance,
                            nrf_drv_twi_config_t const * p_config,
                            nrf_drv_twi_evt_handler_t    event_handler,
                            void *                       p_context)
{
    ASSERT(p_config);
    ASSERT(p_config->scl != p_config->sda);
    twi_control_block_t * p_cb  = &m_cb[p_instance->drv_inst_idx];
    ret_code_t err_code;

    if (p_cb->state != NRF_DRV_STATE_UNINITIALIZED)
    {
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                        (uint32_t)__func__,
                        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    if (nrf_drv_common_per_res_acquire(p_instance->reg.p_twi,
            m_irq_handlers[p_instance->drv_inst_idx]) != NRF_SUCCESS)
    {
        err_code = NRF_ERROR_BUSY;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                        (uint32_t)__func__,
                        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
#endif // NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)

    p_cb->handler         = event_handler;
    p_cb->p_context       = p_context;
    p_cb->int_mask        = 0;
    p_cb->repeated        = false;
    p_cb->busy            = false;
    p_cb->hold_bus_uninit = p_config->hold_bus_uninit;
#if NRF_MODULE_ENABLED(TWIM_NRF52_ANOMALY_109_WORKAROUND)
    p_cb->bus_frequency   = (nrf_twim_frequency_t)p_config->frequency;
#endif

    if(p_config->clear_bus_init)
    {
        /* Send clocks (max 9) until slave device back from stuck mode */
        twi_clear_bus(p_config);
    }

    /* To secure correct signal levels on the pins used by the TWI
       master when the system is in OFF mode, and when the TWI master is
       disabled, these pins must be configured in the GPIO peripheral.
    */
    NRF_GPIO->PIN_CNF[p_config->scl] = SCL_PIN_INIT_CONF;
    NRF_GPIO->PIN_CNF[p_config->sda] = SDA_PIN_INIT_CONF;

    CODE_FOR_TWIM
    (
        NRF_TWIM_Type * p_twim = p_instance->reg.p_twim;
        nrf_twim_pins_set(p_twim, p_config->scl, p_config->sda);
        nrf_twim_frequency_set(p_twim,
            (nrf_twim_frequency_t)p_config->frequency);
    )
    CODE_FOR_TWI
    (
        NRF_TWI_Type * p_twi = p_instance->reg.p_twi;
        nrf_twi_pins_set(p_twi, p_config->scl, p_config->sda);
        nrf_twi_frequency_set(p_twi,
            (nrf_twi_frequency_t)p_config->frequency);
    )

    if (p_cb->handler)
    {
        CODE_FOR_TWIM
        (
            nrf_drv_common_irq_enable(nrf_drv_get_IRQn((void *)p_instance->reg.p_twim),
                p_config->interrupt_priority);
        )
        CODE_FOR_TWI
        (
            nrf_drv_common_irq_enable(nrf_drv_get_IRQn((void *)p_instance->reg.p_twi),
                p_config->interrupt_priority);
        )
    }

    p_cb->state = NRF_DRV_STATE_INITIALIZED;

    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n",
                 (uint32_t)__func__,
                 (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}

void nrf_drv_twi_uninit(nrf_drv_twi_t const * p_instance)
{
    twi_control_block_t * p_cb = &m_cb[p_instance->drv_inst_idx];
    ASSERT(p_cb->state != NRF_DRV_STATE_UNINITIALIZED);

    if (p_cb->handler)
    {
        CODE_FOR_TWIM
        (
            nrf_drv_common_irq_disable(nrf_drv_get_IRQn((void *)p_instance->reg.p_twim));
        )
        CODE_FOR_TWI
        (
            nrf_drv_common_irq_disable(nrf_drv_get_IRQn((void *)p_instance->reg.p_twi));
        )
    }
    nrf_drv_twi_disable(p_instance);

#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    nrf_drv_common_per_res_release(p_instance->reg.p_twi);
#endif

    if (!p_cb->hold_bus_uninit)
    {
        CODE_FOR_TWIM
        (
        NRF_GPIO->PIN_CNF[p_instance->reg.p_twim->PSEL.SCL] = SCL_PIN_UNINIT_CONF;
        NRF_GPIO->PIN_CNF[p_instance->reg.p_twim->PSEL.SDA] = SDA_PIN_UNINIT_CONF;
        )
        CODE_FOR_TWI
        (
        NRF_GPIO->PIN_CNF[p_instance->reg.p_twi->PSELSCL] = SCL_PIN_UNINIT_CONF;
        NRF_GPIO->PIN_CNF[p_instance->reg.p_twi->PSELSDA] = SDA_PIN_UNINIT_CONF;
        )
    }

    p_cb->state = NRF_DRV_STATE_UNINITIALIZED;
    NRF_LOG_INFO("Instance uninitialized: %d.\r\n", p_instance->drv_inst_idx);
}

void nrf_drv_twi_enable(nrf_drv_twi_t const * p_instance)
{
    twi_control_block_t * p_cb = &m_cb[p_instance->drv_inst_idx];
    ASSERT(p_cb->state == NRF_DRV_STATE_INITIALIZED);

    CODE_FOR_TWIM
    (
        NRF_TWIM_Type * p_twim = p_instance->reg.p_twim;

        nrf_twim_enable(p_twim);
    )
    CODE_FOR_TWI
    (
        NRF_TWI_Type * p_twi = p_instance->reg.p_twi;

        nrf_twi_enable(p_twi);
    )

    p_cb->state = NRF_DRV_STATE_POWERED_ON;
    NRF_LOG_INFO("Instance enabled: %d.\r\n", p_instance->drv_inst_idx);
}

void nrf_drv_twi_disable(nrf_drv_twi_t const * p_instance)
{
    twi_control_block_t * p_cb = &m_cb[p_instance->drv_inst_idx];
    ASSERT(p_cb->state != NRF_DRV_STATE_UNINITIALIZED);

    CODE_FOR_TWIM
    (
        NRF_TWIM_Type * p_twim = p_instance->reg.p_twim;
        p_cb->int_mask = 0;
        nrf_twim_int_disable(p_twim, DISABLE_ALL_INT_SHORT);
        nrf_twim_shorts_disable(p_twim, DISABLE_ALL_INT_SHORT);
        nrf_twim_disable(p_twim);
    )
    CODE_FOR_TWI
    (
        NRF_TWI_Type * p_twi = p_instance->reg.p_twi;
        nrf_twi_int_disable(p_twi, DISABLE_ALL_INT_SHORT);
        nrf_twi_shorts_disable(p_twi, DISABLE_ALL_INT_SHORT);
        nrf_twi_disable(p_twi);
    )

    p_cb->state = NRF_DRV_STATE_INITIALIZED;
    NRF_LOG_INFO("Instance disabled: %d.\r\n", p_instance->drv_inst_idx);
}

#ifdef TWI_IN_USE
static bool twi_send_byte(NRF_TWI_Type  * p_twi,
                          uint8_t const * p_data,
                          uint8_t         length,
                          uint8_t       * p_bytes_transferred,
                          bool            no_stop)
{
    if (*p_bytes_transferred < length)
    {
        nrf_twi_txd_set(p_twi, p_data[*p_bytes_transferred]);
        ++(*p_bytes_transferred);
    }
    else
    {
        if (no_stop)
        {
            nrf_twi_task_trigger(p_twi, NRF_TWI_TASK_SUSPEND);
            return false;
        }
        else
        {
            nrf_twi_task_trigger(p_twi, NRF_TWI_TASK_STOP);
        }
    }
    return true;
}

static void twi_receive_byte(NRF_TWI_Type * p_twi,
                             uint8_t      * p_data,
                             uint8_t        length,
                             uint8_t      * p_bytes_transferred)
{
    if (*p_bytes_transferred < length)
    {
        p_data[*p_bytes_transferred] = nrf_twi_rxd_get(p_twi);

        ++(*p_bytes_transferred);

        if (*p_bytes_transferred == length - 1)
        {
            nrf_twi_shorts_set(p_twi, NRF_TWI_SHORT_BB_STOP_MASK);
        }
        else if (*p_bytes_transferred == length)
        {
            return;
        }

        nrf_twi_task_trigger(p_twi, NRF_TWI_TASK_RESUME);
    }
}

static bool twi_transfer(NRF_TWI_Type  * p_twi,
                         bool          * p_error,
                         uint8_t       * p_bytes_transferred,
                         uint8_t       * p_data,
                         uint8_t         length,
                         bool            no_stop)
{
    bool do_stop_check = ((*p_error) || ((*p_bytes_transferred) == length));

    if (*p_error)
    {
        nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_ERROR);
        nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_TXDSENT);
        nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_RXDREADY);
    }
    else if (nrf_twi_event_check(p_twi, NRF_TWI_EVENT_ERROR))
    {
        nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_ERROR);
        NRF_LOG_DEBUG("TWI: Event: %s.\r\n", (uint32_t)EVT_TO_STR_TWI(NRF_TWI_EVENT_ERROR));
        nrf_twi_task_trigger(p_twi, NRF_TWI_TASK_STOP);
        *p_error = true;
    }
    else
    {
        if (nrf_twi_event_check(p_twi, NRF_TWI_EVENT_TXDSENT))
        {
            nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_TXDSENT);
            NRF_LOG_DEBUG("TWI: Event: %s.\r\n", (uint32_t)EVT_TO_STR_TWI(NRF_TWI_EVENT_TXDSENT));
            if (nrf_twi_event_check(p_twi, NRF_TWI_EVENT_ERROR))
            {
                nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_ERROR);
                NRF_LOG_DEBUG("TWI: Event: %s.\r\n", (uint32_t)EVT_TO_STR_TWI(NRF_TWI_EVENT_ERROR));
                nrf_twi_task_trigger(p_twi, NRF_TWI_TASK_STOP);
                *p_error = true;
            }
            else
            {
                if (!twi_send_byte(p_twi, p_data, length, p_bytes_transferred, no_stop))
                {
                    return false;
                }
            }
        }
        else if (nrf_twi_event_check(p_twi, NRF_TWI_EVENT_RXDREADY))
        {
            nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_RXDREADY);
            NRF_LOG_DEBUG("TWI: Event: %s.\r\n", (uint32_t)EVT_TO_STR_TWI(NRF_TWI_EVENT_RXDREADY));
            if (nrf_twi_event_check(p_twi, NRF_TWI_EVENT_ERROR))
            {
                NRF_LOG_DEBUG("TWI: Event: %s.\r\n", (uint32_t)EVT_TO_STR_TWI(NRF_TWI_EVENT_ERROR));
                nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_ERROR);
                nrf_twi_task_trigger(p_twi, NRF_TWI_TASK_STOP);
                *p_error = true;
            }
            else
            {
                twi_receive_byte(p_twi, p_data, length, p_bytes_transferred);
            }
        }
    }

    if (do_stop_check && nrf_twi_event_check(p_twi, NRF_TWI_EVENT_STOPPED))
    {
        nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_STOPPED);
        NRF_LOG_DEBUG("TWI: Event: %s.\r\n", (uint32_t)EVT_TO_STR_TWI(NRF_TWI_EVENT_STOPPED));
        return false;
    }

    return true;
}

static ret_code_t twi_tx_start_transfer(twi_control_block_t * p_cb,
                                        NRF_TWI_Type *        p_twi,
                                        uint8_t const *       p_data,
                                        uint8_t               length,
                                        bool                  no_stop)
{
    ret_code_t ret_code = NRF_SUCCESS;
    volatile int32_t hw_timeout;

    hw_timeout = HW_TIMEOUT;

    nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_STOPPED);
    nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_ERROR);
    nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_TXDSENT);
    nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_RXDREADY);
    nrf_twi_shorts_set(p_twi, 0);

    p_cb->bytes_transferred = 0;
    p_cb->error             = false;

    // In case TWI is suspended resume its operation.
    nrf_twi_task_trigger(p_twi, NRF_TWI_TASK_RESUME);
    nrf_twi_task_trigger(p_twi, NRF_TWI_TASK_STARTTX);

    (void)twi_send_byte(p_twi, p_data, length, &p_cb->bytes_transferred, no_stop);

    if (p_cb->handler)
    {
        p_cb->int_mask = NRF_TWI_INT_STOPPED_MASK   |
                        NRF_TWI_INT_ERROR_MASK     |
                        NRF_TWI_INT_TXDSENT_MASK   |
                        NRF_TWI_INT_RXDREADY_MASK;
        nrf_twi_int_enable(p_twi, p_cb->int_mask);
    }
    else
    {
        while ((hw_timeout > 0) &&
               twi_transfer(p_twi,
                            &p_cb->error,
                            &p_cb->bytes_transferred,
                            (uint8_t *)p_data,
                            length,
                            no_stop))
        {
            hw_timeout--;
        }

        if (p_cb->error)
        {
            uint32_t errorsrc =  nrf_twi_errorsrc_get_and_clear(p_twi);

            if (errorsrc)
            {
                ret_code = twi_process_error(errorsrc);
            }
        }

        if (hw_timeout <= 0)
        {
            nrf_twi_disable(p_twi);
            nrf_twi_enable(p_twi);
            ret_code = NRF_ERROR_INTERNAL;
        }

    }
    return ret_code;
}

static ret_code_t twi_rx_start_transfer(twi_control_block_t * p_cb,
                                        NRF_TWI_Type *        p_twi,
                                        uint8_t const *       p_data,
                                        uint8_t               length)
{
    ret_code_t ret_code = NRF_SUCCESS;
    volatile int32_t hw_timeout;

    hw_timeout = HW_TIMEOUT;

    nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_STOPPED);
    nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_ERROR);
    nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_TXDSENT);
    nrf_twi_event_clear(p_twi, NRF_TWI_EVENT_RXDREADY);

    p_cb->bytes_transferred = 0;
    p_cb->error             = false;

    if (length == 1)
    {
        nrf_twi_shorts_set(p_twi, NRF_TWI_SHORT_BB_STOP_MASK);
    }
    else
    {
        nrf_twi_shorts_set(p_twi, NRF_TWI_SHORT_BB_SUSPEND_MASK);
    }
    // In case TWI is suspended resume its operation.
    nrf_twi_task_trigger(p_twi, NRF_TWI_TASK_RESUME);
    nrf_twi_task_trigger(p_twi, NRF_TWI_TASK_STARTRX);

    if (p_cb->handler)
    {
        p_cb->int_mask = NRF_TWI_INT_STOPPED_MASK   |
                        NRF_TWI_INT_ERROR_MASK     |
                        NRF_TWI_INT_TXDSENT_MASK   |
                        NRF_TWI_INT_RXDREADY_MASK;
        nrf_twi_int_enable(p_twi, p_cb->int_mask);
    }
    else
    {
        while ((hw_timeout > 0) &&
               twi_transfer(p_twi,
                            &p_cb->error,
                            &p_cb->bytes_transferred,
                            (uint8_t*)p_data,
                            length,
                            false))
        {
               hw_timeout--;
        }

        if (p_cb->error)
        {
            uint32_t errorsrc =  nrf_twi_errorsrc_get_and_clear(p_twi);

            if (errorsrc)
            {
                ret_code = twi_process_error(errorsrc);
            }
        }
        if (hw_timeout <= 0)
        {
            nrf_twi_disable(p_twi);
            nrf_twi_enable(p_twi);
            ret_code = NRF_ERROR_INTERNAL;
        }
    }
    return ret_code;
}

__STATIC_INLINE ret_code_t twi_xfer(twi_control_block_t           * p_cb,
                                    NRF_TWI_Type                  * p_twi,
                                    nrf_drv_twi_xfer_desc_t const * p_xfer_desc,
                                    uint32_t                        flags)
{

    ret_code_t err_code = NRF_SUCCESS;

    /* Block TWI interrupts to ensure that function is not interrupted by TWI interrupt. */
    nrf_twi_int_disable(p_twi, DISABLE_ALL_INT_SHORT);

    if (p_cb->busy)
    {
        nrf_twi_int_enable(p_twi, p_cb->int_mask);
        err_code = NRF_ERROR_BUSY;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                        (uint32_t)__func__,
                        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    else
    {
        p_cb->busy = (NRF_DRV_TWI_FLAG_NO_XFER_EVT_HANDLER & flags) ? false : true;
    }

    if (flags & NRF_DRV_TWI_FLAG_HOLD_XFER)
    {
        err_code = NRF_ERROR_NOT_SUPPORTED;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                        (uint32_t)__func__,
                        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    p_cb->flags       = flags;
    p_cb->xfer_desc   = *p_xfer_desc;
    p_cb->curr_length = p_xfer_desc->primary_length;
    p_cb->p_curr_buf  = p_xfer_desc->p_primary_buf;
    nrf_twi_address_set(p_twi, p_xfer_desc->address);

    if (p_xfer_desc->type != NRF_DRV_TWI_XFER_RX)
    {
        p_cb->curr_no_stop = ((p_xfer_desc->type == NRF_DRV_TWI_XFER_TX) &&
                             !(flags & NRF_DRV_TWI_FLAG_TX_NO_STOP)) ? false : true;

        err_code = twi_tx_start_transfer(p_cb,
                                         p_twi,
                                         p_xfer_desc->p_primary_buf,
                                         p_xfer_desc->primary_length,
                                         p_cb->curr_no_stop);
    }
    else
    {
        p_cb->curr_no_stop = false;

        err_code = twi_rx_start_transfer(p_cb,
                                         p_twi,
                                         p_xfer_desc->p_primary_buf,
                                         p_xfer_desc->primary_length);
    }
    if (p_cb->handler == NULL)
    {
        p_cb->busy = false;
    }
    return err_code;
}
#endif


bool nrf_drv_twi_is_busy(nrf_drv_twi_t const * p_instance)
{
    twi_control_block_t * p_cb = &m_cb[p_instance->drv_inst_idx];
    return p_cb->busy;
}


#ifdef TWIM_IN_USE
__STATIC_INLINE void twim_list_enable_handle(NRF_TWIM_Type * p_twim, uint32_t flags)
{
    if (NRF_DRV_TWI_FLAG_TX_POSTINC & flags)
    {
        nrf_twim_tx_list_enable(p_twim);
    }
    else
    {
        nrf_twim_tx_list_disable(p_twim);
    }

    if (NRF_DRV_TWI_FLAG_RX_POSTINC & flags)
    {
        nrf_twim_rx_list_enable(p_twim);
    }
    else
    {
        nrf_twim_rx_list_disable(p_twim);
    }
}
__STATIC_INLINE ret_code_t twim_xfer(twi_control_block_t           * p_cb,
                                     NRF_TWIM_Type                 * p_twim,
                                     nrf_drv_twi_xfer_desc_t const * p_xfer_desc,
                                     uint32_t                        flags)
{
    ret_code_t err_code = NRF_SUCCESS;
    nrf_twim_task_t  start_task = NRF_TWIM_TASK_STARTTX;
    nrf_twim_event_t evt_to_wait = NRF_TWIM_EVENT_STOPPED;

    if (!nrf_drv_is_in_RAM(p_xfer_desc->p_primary_buf))
    {
        err_code = NRF_ERROR_INVALID_ADDR;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                        (uint32_t)__func__,
                        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    /* Block TWI interrupts to ensure that function is not interrupted by TWI interrupt. */
    nrf_twim_int_disable(p_twim, DISABLE_ALL_INT_SHORT);
    if (p_cb->busy)
    {
        nrf_twim_int_enable(p_twim, p_cb->int_mask);
        err_code = NRF_ERROR_BUSY;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                        (uint32_t)__func__,
                        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    else
    {
        p_cb->busy = ((NRF_DRV_TWI_FLAG_NO_XFER_EVT_HANDLER & flags) ||
                      (NRF_DRV_TWI_FLAG_REPEATED_XFER & flags)) ? false: true;
    }

    p_cb->xfer_desc = *p_xfer_desc;
    p_cb->repeated = (flags & NRF_DRV_TWI_FLAG_REPEATED_XFER) ? true : false;
    nrf_twim_address_set(p_twim, p_xfer_desc->address);

    nrf_twim_event_clear(p_twim, NRF_TWIM_EVENT_STOPPED);
    nrf_twim_event_clear(p_twim, NRF_TWIM_EVENT_ERROR);

    twim_list_enable_handle(p_twim, flags);
    switch (p_xfer_desc->type)
    {
    case NRF_DRV_TWI_XFER_TXTX:
        ASSERT(!(flags & NRF_DRV_TWI_FLAG_REPEATED_XFER));
        ASSERT(!(flags & NRF_DRV_TWI_FLAG_HOLD_XFER));
        ASSERT(!(flags & NRF_DRV_TWI_FLAG_NO_XFER_EVT_HANDLER));
        if (!nrf_drv_is_in_RAM(p_xfer_desc->p_secondary_buf))
        {
            err_code = NRF_ERROR_INVALID_ADDR;
            NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                            (uint32_t)__func__,
                            (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
            return err_code;
        }
        nrf_twim_shorts_set(p_twim, NRF_TWIM_SHORT_LASTTX_SUSPEND_MASK);
        nrf_twim_tx_buffer_set(p_twim, p_xfer_desc->p_primary_buf, p_xfer_desc->primary_length);
        nrf_twim_event_clear(p_twim, NRF_TWIM_EVENT_TXSTARTED);
        nrf_twim_event_clear(p_twim, NRF_TWIM_EVENT_LASTTX);
        nrf_twim_event_clear(p_twim, NRF_TWIM_EVENT_SUSPENDED);
        nrf_twim_task_trigger(p_twim, NRF_TWIM_TASK_RESUME);
        nrf_twim_task_trigger(p_twim, NRF_TWIM_TASK_STARTTX);
        while (!nrf_twim_event_check(p_twim, NRF_TWIM_EVENT_TXSTARTED))
        {}
        NRF_LOG_DEBUG("TWIM: Event: %s.\r\n", (uint32_t)EVT_TO_STR_TWIM(NRF_TWIM_EVENT_TXSTARTED));
        nrf_twim_event_clear(p_twim, NRF_TWIM_EVENT_TXSTARTED);
        nrf_twim_tx_buffer_set(p_twim, p_xfer_desc->p_secondary_buf, p_xfer_desc->secondary_length);
        p_cb->int_mask = NRF_TWIM_INT_SUSPENDED_MASK | NRF_TWIM_INT_ERROR_MASK;
        break;
    case NRF_DRV_TWI_XFER_TXRX:
        nrf_twim_tx_buffer_set(p_twim, p_xfer_desc->p_primary_buf, p_xfer_desc->primary_length);
        if (!nrf_drv_is_in_RAM(p_xfer_desc->p_secondary_buf))
        {
            err_code = NRF_ERROR_INVALID_ADDR;
            NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                            (uint32_t)__func__,
                            (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
            return err_code;
        }
        nrf_twim_rx_buffer_set(p_twim, p_xfer_desc->p_secondary_buf, p_xfer_desc->secondary_length);
        nrf_twim_shorts_set(p_twim, NRF_TWIM_SHORT_LASTTX_STARTRX_MASK |
                                    NRF_TWIM_SHORT_LASTRX_STOP_MASK);
        p_cb->int_mask = NRF_TWIM_INT_STOPPED_MASK | NRF_TWIM_INT_ERROR_MASK;
        break;
    case NRF_DRV_TWI_XFER_TX:
        nrf_twim_tx_buffer_set(p_twim, p_xfer_desc->p_primary_buf, p_xfer_desc->primary_length);
        if (NRF_DRV_TWI_FLAG_TX_NO_STOP & flags)
        {
            nrf_twim_shorts_set(p_twim, NRF_TWIM_SHORT_LASTTX_SUSPEND_MASK);
            p_cb->int_mask = NRF_TWIM_INT_SUSPENDED_MASK | NRF_TWIM_INT_ERROR_MASK;
            nrf_twim_event_clear(p_twim, NRF_TWIM_EVENT_SUSPENDED);
            evt_to_wait = NRF_TWIM_EVENT_SUSPENDED;
        }
        else
        {
            nrf_twim_shorts_set(p_twim, NRF_TWIM_SHORT_LASTTX_STOP_MASK);
            p_cb->int_mask = NRF_TWIM_INT_STOPPED_MASK | NRF_TWIM_INT_ERROR_MASK;
        }
        nrf_twim_task_trigger(p_twim, NRF_TWIM_TASK_RESUME);
        break;
    case NRF_DRV_TWI_XFER_RX:
        nrf_twim_rx_buffer_set(p_twim, p_xfer_desc->p_primary_buf, p_xfer_desc->primary_length);
        nrf_twim_shorts_set(p_twim, NRF_TWIM_SHORT_LASTRX_STOP_MASK);
        p_cb->int_mask = NRF_TWIM_INT_STOPPED_MASK | NRF_TWIM_INT_ERROR_MASK;
        start_task = NRF_TWIM_TASK_STARTRX;
        nrf_twim_task_trigger(p_twim, NRF_TWIM_TASK_RESUME);
        break;
    default:
        err_code = NRF_ERROR_INVALID_PARAM;
        break;
    }

    if (!(flags & NRF_DRV_TWI_FLAG_HOLD_XFER) && (p_xfer_desc->type != NRF_DRV_TWI_XFER_TXTX))
    {
        nrf_twim_task_trigger(p_twim, start_task);
    }

    if (p_cb->handler)
    {
        if (flags & NRF_DRV_TWI_FLAG_NO_XFER_EVT_HANDLER)
        {
            p_cb->int_mask = NRF_TWIM_INT_ERROR_MASK;
        }
        nrf_twim_int_enable(p_twim, p_cb->int_mask);

#if NRF_MODULE_ENABLED(TWIM_NRF52_ANOMALY_109_WORKAROUND)
        if ((flags & NRF_DRV_TWI_FLAG_HOLD_XFER) && ((p_xfer_desc->type == NRF_DRV_TWI_XFER_TX) ||
                                                     (p_xfer_desc->type == NRF_DRV_TWI_XFER_TXRX)))
        {
            p_cb->flags = flags;
            twim_list_enable_handle(p_twim, 0);
            p_twim->FREQUENCY = 0;
            nrf_twim_event_clear(p_twim, NRF_TWIM_EVENT_TXSTARTED);
            nrf_twim_int_enable(p_twim, NRF_TWIM_INT_TXSTARTED_MASK);
        }
#endif
    }
    else
    {
        while (!nrf_twim_event_check(p_twim, evt_to_wait))
        {
            if (nrf_twim_event_check(p_twim, NRF_TWIM_EVENT_ERROR))
            {
                NRF_LOG_DEBUG("TWIM: Event: %s.\r\n",
                              (uint32_t)EVT_TO_STR_TWIM(NRF_TWIM_EVENT_ERROR));
                nrf_twim_event_clear(p_twim, NRF_TWIM_EVENT_ERROR);
                nrf_twim_task_trigger(p_twim, NRF_TWIM_TASK_RESUME);
                nrf_twim_task_trigger(p_twim, NRF_TWIM_TASK_STOP);
                evt_to_wait = NRF_TWIM_EVENT_STOPPED;
            }
        }

        uint32_t errorsrc =  nrf_twim_errorsrc_get_and_clear(p_twim);

        p_cb->busy = false;

        if (errorsrc)
        {
            err_code = twi_process_error(errorsrc);
        }
    }
    return err_code;
}
#endif

ret_code_t nrf_drv_twi_xfer(nrf_drv_twi_t           const * p_instance,
                            nrf_drv_twi_xfer_desc_t const * p_xfer_desc,
                            uint32_t                        flags)
{

    ret_code_t err_code = NRF_SUCCESS;
    twi_control_block_t * p_cb = &m_cb[p_instance->drv_inst_idx];

    // TXRX and TXTX transfers are support only in non-blocking mode.
    ASSERT( !((p_cb->handler == NULL) && (p_xfer_desc->type == NRF_DRV_TWI_XFER_TXRX)));
    ASSERT( !((p_cb->handler == NULL) && (p_xfer_desc->type == NRF_DRV_TWI_XFER_TXTX)));

    NRF_LOG_INFO("Transfer type: %s.\r\n", (uint32_t)TRANSFER_TO_STR(p_xfer_desc->type));
    NRF_LOG_INFO("Transfer buffers length: primary: %d, secondary: %d.\r\n",
                 p_xfer_desc->primary_length, p_xfer_desc->secondary_length);
    NRF_LOG_DEBUG("Primary buffer data:\r\n");
    NRF_LOG_HEXDUMP_DEBUG((uint8_t *)p_xfer_desc->p_primary_buf,
                          p_xfer_desc->primary_length * sizeof(p_xfer_desc->p_primary_buf));
    NRF_LOG_DEBUG("Secondary buffer data:\r\n");
    NRF_LOG_HEXDUMP_DEBUG((uint8_t *)p_xfer_desc->p_secondary_buf,
                          p_xfer_desc->secondary_length * sizeof(p_xfer_desc->p_secondary_buf));

    CODE_FOR_TWIM
    (

        err_code = twim_xfer(p_cb, (NRF_TWIM_Type *)p_instance->reg.p_twim, p_xfer_desc, flags);
    )
    CODE_FOR_TWI
    (
        if ( (NRF_DRV_TWI_FLAG_TX_POSTINC | NRF_DRV_TWI_FLAG_RX_POSTINC) & flags)
        {
            err_code = NRF_ERROR_NOT_SUPPORTED;
            NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                    (uint32_t)__func__,
                    (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
            return err_code;
        }

        err_code = twi_xfer(p_cb, (NRF_TWI_Type  *)p_instance->reg.p_twi, p_xfer_desc, flags);
    )
    NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                    (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}

ret_code_t nrf_drv_twi_tx(nrf_drv_twi_t const * p_instance,
                          uint8_t               address,
                          uint8_t const *       p_data,
                          uint8_t               length,
                          bool                  no_stop)
{
    nrf_drv_twi_xfer_desc_t xfer = NRF_DRV_TWI_XFER_DESC_TX(address, (uint8_t*)p_data, length);

    return nrf_drv_twi_xfer(p_instance, &xfer, no_stop ? NRF_DRV_TWI_FLAG_TX_NO_STOP : 0);
}

ret_code_t nrf_drv_twi_rx(nrf_drv_twi_t const * p_instance,
                          uint8_t               address,
                          uint8_t *             p_data,
                          uint8_t               length)
{
    nrf_drv_twi_xfer_desc_t xfer = NRF_DRV_TWI_XFER_DESC_RX(address, p_data, length);
    return nrf_drv_twi_xfer(p_instance, &xfer, 0);
}

uint32_t nrf_drv_twi_data_count_get(nrf_drv_twi_t const * const p_instance)
{
    CODE_FOR_TWIM
    (
        ASSERT(false);
        return 0;
    )
    CODE_FOR_TWI
    (
        return m_cb[p_instance->drv_inst_idx].bytes_transferred;
    )
}

uint32_t nrf_drv_twi_start_task_get(nrf_drv_twi_t const * p_instance,
                                    nrf_drv_twi_xfer_type_t xfer_type)
{
    CODE_FOR_TWIM
    (
        return (uint32_t)nrf_twim_task_address_get(p_instance->reg.p_twim,
            (xfer_type != NRF_DRV_TWI_XFER_RX) ? NRF_TWIM_TASK_STARTTX : NRF_TWIM_TASK_STARTRX);
    )
    CODE_FOR_TWI
    (
        return (uint32_t)nrf_twi_task_address_get(p_instance->reg.p_twi,
                (xfer_type != NRF_DRV_TWI_XFER_RX) ? NRF_TWI_TASK_STARTTX : NRF_TWI_TASK_STARTRX);
    )
}

uint32_t nrf_drv_twi_stopped_event_get(nrf_drv_twi_t const * p_instance)
{
    CODE_FOR_TWIM
    (
        return (uint32_t)nrf_twim_event_address_get(p_instance->reg.p_twim, NRF_TWIM_EVENT_STOPPED);
    )
    CODE_FOR_TWI
    (
        return (uint32_t)nrf_twi_event_address_get(p_instance->reg.p_twi, NRF_TWI_EVENT_STOPPED);
    )
}

#ifdef TWIM_IN_USE
static void irq_handler_twim(NRF_TWIM_Type * p_twim, twi_control_block_t * p_cb)
{

#if NRF_MODULE_ENABLED(TWIM_NRF52_ANOMALY_109_WORKAROUND)
    /* Handle only workaround case. Can be used without TWIM handler in IRQs. */
    if (nrf_twim_event_check(p_twim, NRF_TWIM_EVENT_TXSTARTED))
    {
        nrf_twim_event_clear(p_twim, NRF_TWIM_EVENT_TXSTARTED);
        nrf_twim_int_disable(p_twim, NRF_TWIM_INT_TXSTARTED_MASK);
        if (p_twim->FREQUENCY == 0)
        {
            // Set enable to zero to reset TWIM internal state.
            nrf_twim_disable(p_twim);
            nrf_twim_enable(p_twim);

            // Set proper frequency.
            nrf_twim_frequency_set(p_twim, p_cb->bus_frequency);
            twim_list_enable_handle(p_twim, p_cb->flags);

            // Start proper transmission.
            nrf_twim_task_trigger(p_twim, NRF_TWIM_TASK_STARTTX);
            return;
        }
    }
#endif

    ASSERT(p_cb->handler);

    if (nrf_twim_event_check(p_twim, NRF_TWIM_EVENT_ERROR))
    {
        nrf_twim_event_clear(p_twim, NRF_TWIM_EVENT_ERROR);
        NRF_LOG_DEBUG("TWIM: Event: %s.\r\n", (uint32_t)EVT_TO_STR_TWIM(NRF_TWIM_EVENT_ERROR));
        if (!nrf_twim_event_check(p_twim, NRF_TWIM_EVENT_STOPPED))
        {
            nrf_twim_int_disable(p_twim, p_cb->int_mask);
            p_cb->int_mask = NRF_TWIM_INT_STOPPED_MASK;
            nrf_twim_int_enable(p_twim, p_cb->int_mask);

            nrf_twim_task_trigger(p_twim, NRF_TWIM_TASK_RESUME);
            nrf_twim_task_trigger(p_twim, NRF_TWIM_TASK_STOP);
            return;
        }
    }

    nrf_drv_twi_evt_t event;

    if (nrf_twim_event_check(p_twim, NRF_TWIM_EVENT_STOPPED))
    {
        NRF_LOG_DEBUG("TWIM: Event: %s.\r\n", (uint32_t)EVT_TO_STR_TWIM(NRF_TWIM_EVENT_STOPPED));
        nrf_twim_event_clear(p_twim, NRF_TWIM_EVENT_STOPPED);
        event.xfer_desc = p_cb->xfer_desc;
        if (p_cb->error)
        {

            event.xfer_desc.primary_length = (p_cb->xfer_desc.type == NRF_DRV_TWI_XFER_RX) ?
                (uint8_t)nrf_twim_rxd_amount_get(p_twim) : (uint8_t)nrf_twim_txd_amount_get(p_twim);
            event.xfer_desc.secondary_length = (p_cb->xfer_desc.type == NRF_DRV_TWI_XFER_TXRX) ?
                (uint8_t)nrf_twim_rxd_amount_get(p_twim) : (uint8_t)nrf_twim_txd_amount_get(p_twim);

        }
        nrf_twim_event_clear(p_twim, NRF_TWIM_EVENT_LASTTX);
        nrf_twim_event_clear(p_twim, NRF_TWIM_EVENT_LASTRX);
        if (!p_cb->repeated || p_cb->error)
        {
            nrf_twim_shorts_set(p_twim, 0);
            p_cb->int_mask = 0;
            nrf_twim_int_disable(p_twim, DISABLE_ALL_INT_SHORT);
        }
    }
    else
    {
        nrf_twim_event_clear(p_twim, NRF_TWIM_EVENT_SUSPENDED);
        NRF_LOG_DEBUG("TWIM: Event: %s.\r\n", (uint32_t)EVT_TO_STR_TWIM(NRF_TWIM_EVENT_SUSPENDED));
        if (p_cb->xfer_desc.type == NRF_DRV_TWI_XFER_TX)
        {
            event.xfer_desc = p_cb->xfer_desc;
            if (!p_cb->repeated)
            {
                nrf_twim_shorts_set(p_twim, 0);
                p_cb->int_mask = 0;
                nrf_twim_int_disable(p_twim, DISABLE_ALL_INT_SHORT);
            }
        }
        else
        {
            nrf_twim_shorts_set(p_twim, NRF_TWIM_SHORT_LASTTX_STOP_MASK);
            p_cb->int_mask = NRF_TWIM_INT_STOPPED_MASK | NRF_TWIM_INT_ERROR_MASK;
            nrf_twim_int_disable(p_twim, DISABLE_ALL_INT_SHORT);
            nrf_twim_int_enable(p_twim, p_cb->int_mask);
            nrf_twim_task_trigger(p_twim, NRF_TWIM_TASK_STARTTX);
            nrf_twim_task_trigger(p_twim, NRF_TWIM_TASK_RESUME);
            return;
        }
    }

    uint32_t errorsrc = nrf_twim_errorsrc_get_and_clear(p_twim);
    if (errorsrc & NRF_TWIM_ERROR_ADDRESS_NACK)
    {
        event.type = NRF_DRV_TWI_EVT_ADDRESS_NACK;
        NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_DRV_TWI_EVT_ADDRESS_NACK));
    }
    else if (errorsrc & NRF_TWIM_ERROR_DATA_NACK)
    {
        event.type = NRF_DRV_TWI_EVT_DATA_NACK;
        NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_DRV_TWI_EVT_DATA_NACK));
    }
    else
    {
        event.type = NRF_DRV_TWI_EVT_DONE;
        NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_DRV_TWI_EVT_DONE));
    }

    if (!p_cb->repeated)
    {
        p_cb->busy = false;
    }
    p_cb->handler(&event, p_cb->p_context);
}
#endif // TWIM_IN_USE

#ifdef TWI_IN_USE
static void irq_handler_twi(NRF_TWI_Type * p_twi, twi_control_block_t * p_cb)
{
    ASSERT(p_cb->handler);

    if (twi_transfer(p_twi,
                     &p_cb->error,
                     &p_cb->bytes_transferred,
                     p_cb->p_curr_buf,
                     p_cb->curr_length,
                     p_cb->curr_no_stop ))
    {
        return;
    }

    if (!p_cb->error &&
        ((p_cb->xfer_desc.type == NRF_DRV_TWI_XFER_TXRX) ||
         (p_cb->xfer_desc.type == NRF_DRV_TWI_XFER_TXTX)) &&
        p_cb->p_curr_buf == p_cb->xfer_desc.p_primary_buf)
    {
        p_cb->p_curr_buf   = p_cb->xfer_desc.p_secondary_buf;
        p_cb->curr_length  = p_cb->xfer_desc.secondary_length;
        p_cb->curr_no_stop = (p_cb->flags & NRF_DRV_TWI_FLAG_TX_NO_STOP);

        if (p_cb->xfer_desc.type == NRF_DRV_TWI_XFER_TXTX)
        {
            (void)twi_tx_start_transfer(p_cb,
                                        p_twi,
                                        p_cb->p_curr_buf,
                                        p_cb->curr_length,
                                        p_cb->curr_no_stop);
        }
        else
        {
            (void)twi_rx_start_transfer(p_cb, p_twi, p_cb->p_curr_buf, p_cb->curr_length);
        }
    }
    else
    {
        nrf_drv_twi_evt_t event;
        event.xfer_desc = p_cb->xfer_desc;

        if (p_cb->error)
        {
            uint32_t errorsrc = nrf_twi_errorsrc_get_and_clear(p_twi);
            if (errorsrc & NRF_TWI_ERROR_ADDRESS_NACK)
            {
                event.type = NRF_DRV_TWI_EVT_ADDRESS_NACK;
                NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_DRV_TWI_EVT_ADDRESS_NACK));
            }
            else if (errorsrc & NRF_TWI_ERROR_DATA_NACK)
            {
                event.type = NRF_DRV_TWI_EVT_DATA_NACK;
                NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_DRV_TWI_EVT_DATA_NACK));
            }
        }
        else
        {
            event.type = NRF_DRV_TWI_EVT_DONE;
            NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_DRV_TWI_EVT_DONE));
        }

        p_cb->busy = false;

        if (!(NRF_DRV_TWI_FLAG_NO_XFER_EVT_HANDLER & p_cb->flags))
        {
            p_cb->handler(&event, p_cb->p_context);
        }
    }

}
#endif // TWI_IN_USE

#if NRF_MODULE_ENABLED(TWI0)
IRQ_HANDLER(0)
{
    #if (TWI0_USE_EASY_DMA == 1)
        irq_handler_twim(NRF_TWIM0,
    #else
        irq_handler_twi(NRF_TWI0,
    #endif
            &m_cb[TWI0_INSTANCE_INDEX]);
}
#endif // NRF_MODULE_ENABLED(TWI0)

#if NRF_MODULE_ENABLED(TWI1)
IRQ_HANDLER(1)
{
    #if (TWI1_USE_EASY_DMA == 1)
        irq_handler_twim(NRF_TWIM1,
    #else
        irq_handler_twi(NRF_TWI1,
    #endif
            &m_cb[TWI1_INSTANCE_INDEX]);
}
#endif // NRF_MODULE_ENABLED(TWI1)
#endif // TWI_COUNT
#endif // NRF_MODULE_ENABLED(TWI)
