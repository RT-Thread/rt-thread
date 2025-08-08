/*
 * Copyright (c) 2015 - 2021, Nordic Semiconductor ASA
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <nrfx.h>
#include <drivers/pin.h>

#if NRFX_CHECK(NRFX_SPIM_ENABLED)

#if !(NRFX_CHECK(NRFX_SPIM0_ENABLED) || NRFX_CHECK(NRFX_SPIM1_ENABLED) || \
      NRFX_CHECK(NRFX_SPIM2_ENABLED) || NRFX_CHECK(NRFX_SPIM3_ENABLED) || \
      NRFX_CHECK(NRFX_SPIM4_ENABLED))
#error "No enabled SPIM instances. Check <nrfx_config.h>."
#endif

#include "drv_spim.h"

#include <nrfx_spim.h>
#include "prs/nrfx_prs.h"
#include <hal/nrf_gpio.h>

#define NRFX_LOG_MODULE SPIM
#include <nrfx_log.h>

#if NRFX_CHECK(NRFX_SPIM_EXTENDED_ENABLED) && \
    ((!NRF_SPIM_HW_CSN_PRESENT) || !(NRF_SPIM_DCX_PRESENT) || !(NRF_SPIM_RXDELAY_PRESENT))
#error "Extended options are not available in the SoC currently in use."
#endif

#define SPIMX_LENGTH_VALIDATE(peripheral, drv_inst_idx, rx_len, tx_len) \
    (((drv_inst_idx) == NRFX_CONCAT_3(NRFX_, peripheral, _INST_IDX)) && \
     NRFX_EASYDMA_LENGTH_VALIDATE(peripheral, rx_len, tx_len))

#define SPIMX_HW_CSN_PRESENT_VALIDATE(peripheral, drv_inst_idx)         \
    (((drv_inst_idx) == NRFX_CONCAT_3(NRFX_, peripheral, _INST_IDX)) && \
     NRFX_CONCAT_2(peripheral, _FEATURE_HARDWARE_CSN_PRESENT))

#define SPIMX_DCX_PRESENT_VALIDATE(peripheral, drv_inst_idx)            \
    (((drv_inst_idx) == NRFX_CONCAT_3(NRFX_, peripheral, _INST_IDX)) && \
    NRFX_CONCAT_2(peripheral, _FEATURE_DCX_PRESENT))

#define SPIMX_SUPPORTED_FREQ_VALIDATE(peripheral, drv_inst_idx, freq)                            \
    (                                                                                            \
    ((drv_inst_idx) == NRFX_CONCAT_3(NRFX_, peripheral, _INST_IDX)) &&                           \
    (                                                                                            \
        (((freq) != NRF_SPIM_FREQ_16M) && ((freq) != NRF_SPIM_FREQ_32M)) ||                      \
        (((freq) == NRF_SPIM_FREQ_16M) && ((NRFX_CONCAT_2(peripheral, _MAX_DATARATE) >= 16))) || \
        (((freq) == NRF_SPIM_FREQ_32M) && ((NRFX_CONCAT_2(peripheral, _MAX_DATARATE) >= 32)))    \
    )                                                                                            \
    )

#if NRFX_CHECK(NRFX_SPIM0_ENABLED)
#define SPIM0_LENGTH_VALIDATE(...)          SPIMX_LENGTH_VALIDATE(SPIM0, __VA_ARGS__)
#define SPIM0_HW_CSN_PRESENT_VALIDATE(...)  SPIMX_HW_CSN_PRESENT_VALIDATE(SPIM0, __VA_ARGS__)
#define SPIM0_DCX_PRESENT_VALIDATE(...)     SPIMX_DCX_PRESENT_VALIDATE(SPIM0, __VA_ARGS__)
#define SPIM0_SUPPORTED_FREQ_VALIDATE(...)  SPIMX_SUPPORTED_FREQ_VALIDATE(SPIM0, __VA_ARGS__)
#else
#define SPIM0_LENGTH_VALIDATE(...)          0
#define SPIM0_HW_CSN_PRESENT_VALIDATE(...)  0
#define SPIM0_DCX_PRESENT_VALIDATE(...)     0
#define SPIM0_SUPPORTED_FREQ_VALIDATE(...)  0
#endif

#if NRFX_CHECK(NRFX_SPIM1_ENABLED)
#define SPIM1_LENGTH_VALIDATE(...)          SPIMX_LENGTH_VALIDATE(SPIM1, __VA_ARGS__)
#define SPIM1_HW_CSN_PRESENT_VALIDATE(...)  SPIMX_HW_CSN_PRESENT_VALIDATE(SPIM1, __VA_ARGS__)
#define SPIM1_DCX_PRESENT_VALIDATE(...)     SPIMX_DCX_PRESENT_VALIDATE(SPIM1, __VA_ARGS__)
#define SPIM1_SUPPORTED_FREQ_VALIDATE(...)  SPIMX_SUPPORTED_FREQ_VALIDATE(SPIM1, __VA_ARGS__)
#else
#define SPIM1_LENGTH_VALIDATE(...)          0
#define SPIM1_HW_CSN_PRESENT_VALIDATE(...)  0
#define SPIM1_DCX_PRESENT_VALIDATE(...)     0
#define SPIM1_SUPPORTED_FREQ_VALIDATE(...)  0
#endif

#if NRFX_CHECK(NRFX_SPIM2_ENABLED)
#define SPIM2_LENGTH_VALIDATE(...)          SPIMX_LENGTH_VALIDATE(SPIM2, __VA_ARGS__)
#define SPIM2_HW_CSN_PRESENT_VALIDATE(...)  SPIMX_HW_CSN_PRESENT_VALIDATE(SPIM2, __VA_ARGS__)
#define SPIM2_DCX_PRESENT_VALIDATE(...)     SPIMX_DCX_PRESENT_VALIDATE(SPIM2, __VA_ARGS__)
#define SPIM2_SUPPORTED_FREQ_VALIDATE(...)  SPIMX_SUPPORTED_FREQ_VALIDATE(SPIM2, __VA_ARGS__)
#else
#define SPIM2_LENGTH_VALIDATE(...)          0
#define SPIM2_HW_CSN_PRESENT_VALIDATE(...)  0
#define SPIM2_DCX_PRESENT_VALIDATE(...)     0
#define SPIM2_SUPPORTED_FREQ_VALIDATE(...)  0
#endif

#if NRFX_CHECK(NRFX_SPIM3_ENABLED)
#define SPIM3_LENGTH_VALIDATE(...)          SPIMX_LENGTH_VALIDATE(SPIM3, __VA_ARGS__)
#define SPIM3_HW_CSN_PRESENT_VALIDATE(...)  SPIMX_HW_CSN_PRESENT_VALIDATE(SPIM3, __VA_ARGS__)
#define SPIM3_DCX_PRESENT_VALIDATE(...)     SPIMX_DCX_PRESENT_VALIDATE(SPIM3, __VA_ARGS__)
#define SPIM3_SUPPORTED_FREQ_VALIDATE(...)  SPIMX_SUPPORTED_FREQ_VALIDATE(SPIM3, __VA_ARGS__)
#else
#define SPIM3_LENGTH_VALIDATE(...)          0
#define SPIM3_HW_CSN_PRESENT_VALIDATE(...)  0
#define SPIM3_DCX_PRESENT_VALIDATE(...)     0
#define SPIM3_SUPPORTED_FREQ_VALIDATE(...)  0
#endif

#if NRFX_CHECK(NRFX_SPIM4_ENABLED)
#define SPIM4_LENGTH_VALIDATE(...)          SPIMX_LENGTH_VALIDATE(SPIM4, __VA_ARGS__)
#define SPIM4_HW_CSN_PRESENT_VALIDATE(...)  SPIMX_HW_CSN_PRESENT_VALIDATE(SPIM4, __VA_ARGS__)
#define SPIM4_DCX_PRESENT_VALIDATE(...)     SPIMX_DCX_PRESENT_VALIDATE(SPIM4, __VA_ARGS__)
#define SPIM4_SUPPORTED_FREQ_VALIDATE(...)  SPIMX_SUPPORTED_FREQ_VALIDATE(SPIM4, __VA_ARGS__)
#else
#define SPIM4_LENGTH_VALIDATE(...)          0
#define SPIM4_HW_CSN_PRESENT_VALIDATE(...)  0
#define SPIM4_DCX_PRESENT_VALIDATE(...)     0
#define SPIM4_SUPPORTED_FREQ_VALIDATE(...)  0
#endif

#define SPIM_LENGTH_VALIDATE(drv_inst_idx, rx_len, tx_len)  \
    (SPIM0_LENGTH_VALIDATE(drv_inst_idx, rx_len, tx_len) || \
     SPIM1_LENGTH_VALIDATE(drv_inst_idx, rx_len, tx_len) || \
     SPIM2_LENGTH_VALIDATE(drv_inst_idx, rx_len, tx_len) || \
     SPIM3_LENGTH_VALIDATE(drv_inst_idx, rx_len, tx_len) || \
     SPIM4_LENGTH_VALIDATE(drv_inst_idx, rx_len, tx_len))

#define SPIM_HW_CSN_PRESENT_VALIDATE(drv_inst_idx)  \
    (SPIM0_HW_CSN_PRESENT_VALIDATE(drv_inst_idx) || \
     SPIM1_HW_CSN_PRESENT_VALIDATE(drv_inst_idx) || \
     SPIM2_HW_CSN_PRESENT_VALIDATE(drv_inst_idx) || \
     SPIM3_HW_CSN_PRESENT_VALIDATE(drv_inst_idx) || \
     SPIM4_HW_CSN_PRESENT_VALIDATE(drv_inst_idx))

#define SPIM_DCX_PRESENT_VALIDATE(drv_inst_idx)  \
    (SPIM0_DCX_PRESENT_VALIDATE(drv_inst_idx) || \
     SPIM1_DCX_PRESENT_VALIDATE(drv_inst_idx) || \
     SPIM2_DCX_PRESENT_VALIDATE(drv_inst_idx) || \
     SPIM3_DCX_PRESENT_VALIDATE(drv_inst_idx) || \
     SPIM4_DCX_PRESENT_VALIDATE(drv_inst_idx))

#define SPIM_SUPPORTED_FREQ_VALIDATE(drv_inst_idx, freq)  \
    (SPIM0_SUPPORTED_FREQ_VALIDATE(drv_inst_idx, freq) || \
     SPIM1_SUPPORTED_FREQ_VALIDATE(drv_inst_idx, freq) || \
     SPIM2_SUPPORTED_FREQ_VALIDATE(drv_inst_idx, freq) || \
     SPIM3_SUPPORTED_FREQ_VALIDATE(drv_inst_idx, freq) || \
     SPIM4_SUPPORTED_FREQ_VALIDATE(drv_inst_idx, freq))

/* Requested pin can either match dedicated pin or be not connected at all. */
#define SPIM_DEDICATED_PIN_VALIDATE(requested_pin, supported_pin) \
    (((requested_pin) == NRFX_SPIM_PIN_NOT_USED) || ((requested_pin) == (supported_pin)))

#if !defined(USE_WORKAROUND_FOR_ANOMALY_195) && \
    defined(NRF52840_XXAA) && NRFX_CHECK(NRFX_SPIM3_ENABLED)
/* Enable workaround for nRF52840 anomaly 195 (SPIM3 continues to draw current after disable). */
#define USE_WORKAROUND_FOR_ANOMALY_195 1
#endif


/* Control block - driver instance local data. */
typedef struct
{
    nrfx_spim_evt_handler_t handler;
    void *                  p_context;
    nrfx_spim_evt_t         evt;  /* Keep the struct that is ready for event handler. Less memcpy. */
    nrfx_drv_state_t        state;
    volatile bool           transfer_in_progress;

#if NRFX_CHECK(NRFX_SPIM_EXTENDED_ENABLED)
    bool                    use_hw_ss;
#endif

    /* [no need for 'volatile' attribute for the following members, as they */
    /*  are not concurrently used in IRQ handlers and main line code] */
    bool            ss_active_high;
    uint8_t         ss_pin;
    uint8_t         orc;

#if NRFX_CHECK(NRFX_SPIM_NRF52_ANOMALY_109_WORKAROUND_ENABLED)
    size_t          tx_length;
    size_t          rx_length;
#endif
} spim_control_block_t;
static spim_control_block_t m_cb[NRFX_SPIM_ENABLED_COUNT];

#if NRFX_CHECK(NRFX_SPIM3_NRF52840_ANOMALY_198_WORKAROUND_ENABLED)

/* Workaround for nRF52840 anomaly 198: SPIM3 transmit data might be corrupted. */

static uint32_t m_anomaly_198_preserved_value;

static void anomaly_198_enable(uint8_t const * p_buffer, size_t buf_len)
{
    m_anomaly_198_preserved_value = *((volatile uint32_t *)0x40000E00);

    if (buf_len == 0)
    {
        return;
    }
    uint32_t buffer_end_addr = ((uint32_t)p_buffer) + buf_len;
    uint32_t block_addr      = ((uint32_t)p_buffer) & ~0x1FFF;
    uint32_t block_flag      = (1UL << ((block_addr >> 13) & 0xFFFF));
    uint32_t occupied_blocks = 0;

    if (block_addr >= 0x20010000)
    {
        occupied_blocks = (1UL << 8);
    }
    else
    {
        do {
            occupied_blocks |= block_flag;
            block_flag <<= 1;
            block_addr  += 0x2000;
        } while ((block_addr < buffer_end_addr) && (block_addr < 0x20012000));
    }

    *((volatile uint32_t *)0x40000E00) = occupied_blocks;
}

static void anomaly_198_disable(void)
{
    *((volatile uint32_t *)0x40000E00) = m_anomaly_198_preserved_value;
}
#endif /* NRFX_CHECK(NRFX_SPIM3_NRF52840_ANOMALY_198_WORKAROUND_ENABLED) */

static void spim_abort(NRF_SPIM_Type * p_spim, spim_control_block_t * p_cb)
{
    nrf_spim_task_trigger(p_spim, NRF_SPIM_TASK_STOP);
    bool stopped;
    NRFX_WAIT_FOR(nrf_spim_event_check(p_spim, NRF_SPIM_EVENT_STOPPED), 100, 1, stopped);
    if (!stopped)
    {
        NRFX_LOG_ERROR("Failed to stop instance with base address: %p.", (void *)p_spim);
    }
    p_cb->transfer_in_progress = false;
}

nrfx_err_t nrfx_spim_init(nrfx_spim_t const *        p_instance,
                          nrfx_spim_config_t const * p_config,
                          nrfx_spim_evt_handler_t    handler,
                          void *                     p_context)
{
    NRFX_ASSERT(p_config);
    spim_control_block_t * p_cb = &m_cb[p_instance->drv_inst_idx];
    nrfx_err_t err_code;

    if (p_cb->state != NRFX_DRV_STATE_UNINITIALIZED)
    {
        err_code = NRFX_ERROR_INVALID_STATE;
        NRFX_LOG_WARNING("Function: %s, error code: %s.",
                         __func__,
                         NRFX_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

#if NRFX_CHECK(NRFX_SPIM_EXTENDED_ENABLED)
    /* Check if SPIM instance supports the extended features. */
    if (
        (!SPIM_SUPPORTED_FREQ_VALIDATE(p_instance->drv_inst_idx, p_config->frequency)) ||
        ((p_config->use_hw_ss) &&
         !SPIM_HW_CSN_PRESENT_VALIDATE(p_instance->drv_inst_idx)) ||
        ((p_config->dcx_pin != NRFX_SPIM_PIN_NOT_USED) &&
         !SPIM_DCX_PRESENT_VALIDATE(p_instance->drv_inst_idx))
        )
    {
        err_code = NRFX_ERROR_NOT_SUPPORTED;
        NRFX_LOG_WARNING("Function: %s, error code: %s.",
                         __func__,
                         NRFX_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
#endif

    NRF_SPIM_Type * p_spim = (NRF_SPIM_Type *)p_instance->p_reg;

#if NRF_SPIM_HAS_32_MHZ_FREQ && defined(NRF5340_XXAA_APPLICATION)
    /* Check if dedicated SPIM pins are used. */
    if ((p_spim == NRF_SPIM4) && (p_config->frequency == NRF_SPIM_FREQ_32M))
    {
        enum {
            SPIM_SCK_DEDICATED  = NRF_GPIO_PIN_MAP(0, 8),
            SPIM_MOSI_DEDICATED = NRF_GPIO_PIN_MAP(0, 9),
            SPIM_MISO_DEDICATED = NRF_GPIO_PIN_MAP(0, 10),
            SPIM_CSN_DEDICATED  = NRF_GPIO_PIN_MAP(0, 11),
            SPIM_DCX_DEDICATED  = NRF_GPIO_PIN_MAP(0, 12),
        };

        if (!SPIM_DEDICATED_PIN_VALIDATE(p_config->sck_pin, SPIM_SCK_DEDICATED) ||
            !SPIM_DEDICATED_PIN_VALIDATE(p_config->ss_pin,  SPIM_CSN_DEDICATED) ||
#if NRFX_CHECK(NRFX_SPIM_EXTENDED_ENABLED)
            !SPIM_DEDICATED_PIN_VALIDATE(p_config->dcx_pin, SPIM_DCX_DEDICATED) ||
#endif
            !SPIM_DEDICATED_PIN_VALIDATE(p_config->mosi_pin, SPIM_MOSI_DEDICATED) ||
            !SPIM_DEDICATED_PIN_VALIDATE(p_config->miso_pin, SPIM_MISO_DEDICATED))
        {
            err_code = NRFX_ERROR_INVALID_PARAM;
            NRFX_LOG_WARNING("Function: %s, error code: %s.",
                             __func__,
                             NRFX_LOG_ERROR_STRING_GET(err_code));
            return err_code;
        }
    }
#endif

#if NRFX_CHECK(NRFX_PRS_ENABLED)
    static nrfx_irq_handler_t const irq_handlers[NRFX_SPIM_ENABLED_COUNT] = {
        #if NRFX_CHECK(NRFX_SPIM0_ENABLED)
        nrfx_spim_0_irq_handler,
        #endif
        #if NRFX_CHECK(NRFX_SPIM1_ENABLED)
        nrfx_spim_1_irq_handler,
        #endif
        #if NRFX_CHECK(NRFX_SPIM2_ENABLED)
        nrfx_spim_2_irq_handler,
        #endif
        #if NRFX_CHECK(NRFX_SPIM3_ENABLED)
        nrfx_spim_3_irq_handler,
        #endif
        #if NRFX_CHECK(NRFX_SPIM4_ENABLED)
        nrfx_spim_4_irq_handler,
        #endif
    };
    if (nrfx_prs_acquire(p_instance->p_reg,
            irq_handlers[p_instance->drv_inst_idx]) != NRFX_SUCCESS)
    {
        err_code = NRFX_ERROR_BUSY;
        NRFX_LOG_WARNING("Function: %s, error code: %s.",
                         __func__,
                         NRFX_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
#endif /* NRFX_CHECK(NRFX_PRS_ENABLED) */

    p_cb->handler = handler;
    p_cb->p_context = p_context;

    uint32_t mosi_pin;
    uint32_t miso_pin;
    /* Configure pins used by the peripheral: */
    /* - SCK - output with initial value corresponding with the SPI mode used: */
    /*   0 - for modes 0 and 1 (CPOL = 0), 1 - for modes 2 and 3 (CPOL = 1); */
    /*   according to the reference manual guidelines this pin and its input */
    /*   buffer must always be connected for the SPI to work. */
    if (p_config->mode <= NRF_SPIM_MODE_1)
    {
        nrf_gpio_pin_clear(p_config->sck_pin);
    }
    else
    {
        nrf_gpio_pin_set(p_config->sck_pin);
    }

    nrf_gpio_pin_drive_t pin_drive;
    /* Configure pin drive - high drive for 32 MHz clock frequency. */
#if NRF_SPIM_HAS_32_MHZ_FREQ
    pin_drive = (p_config->frequency == NRF_SPIM_FREQ_32M) ? NRF_GPIO_PIN_H0H1 : NRF_GPIO_PIN_S0S1;
#else
    pin_drive = NRF_GPIO_PIN_S0S1;
#endif

    nrf_gpio_cfg(p_config->sck_pin,
                 NRF_GPIO_PIN_DIR_OUTPUT,
                 NRF_GPIO_PIN_INPUT_CONNECT,
                 NRF_GPIO_PIN_NOPULL,
                 pin_drive,
                 NRF_GPIO_PIN_NOSENSE);
    /* - MOSI (optional) - output with initial value 0, */
    if (p_config->mosi_pin != NRFX_SPIM_PIN_NOT_USED)
    {
        mosi_pin = p_config->mosi_pin;
        nrf_gpio_pin_clear(mosi_pin);
        nrf_gpio_cfg(mosi_pin,
                     NRF_GPIO_PIN_DIR_OUTPUT,
                     NRF_GPIO_PIN_INPUT_DISCONNECT,
                     NRF_GPIO_PIN_NOPULL,
                     pin_drive,
                     NRF_GPIO_PIN_NOSENSE);
    }
    else
    {
        mosi_pin = NRF_SPIM_PIN_NOT_CONNECTED;
    }
    /* - MISO (optional) - input, */
    if (p_config->miso_pin != NRFX_SPIM_PIN_NOT_USED)
    {
        miso_pin = p_config->miso_pin;
        nrf_gpio_cfg(miso_pin,
                     NRF_GPIO_PIN_DIR_INPUT,
                     NRF_GPIO_PIN_INPUT_CONNECT,
                     p_config->miso_pull,
                     pin_drive,
                     NRF_GPIO_PIN_NOSENSE);
    }
    else
    {
        miso_pin = NRF_SPIM_PIN_NOT_CONNECTED;
    }
    /* - Slave Select (optional) - output with initial value 1 (inactive). */

    /* 'p_cb->ss_pin' variable is used during transfers to check if SS pin should be toggled, */
    /* so this field needs to be initialized even if the pin is not used. */
    p_cb->ss_pin = p_config->ss_pin;

    if (p_config->ss_pin != NRFX_SPIM_PIN_NOT_USED)
    {
        if (p_config->ss_active_high)
        {
            nrf_gpio_pin_clear(p_config->ss_pin);
        }
        else
        {
            nrf_gpio_pin_set(p_config->ss_pin);
        }
        nrf_gpio_cfg(p_config->ss_pin,
                     NRF_GPIO_PIN_DIR_OUTPUT,
                     NRF_GPIO_PIN_INPUT_DISCONNECT,
                     NRF_GPIO_PIN_NOPULL,
                     pin_drive,
                     NRF_GPIO_PIN_NOSENSE);
#if NRFX_CHECK(NRFX_SPIM_EXTENDED_ENABLED)
        if (p_config->use_hw_ss)
        {
            p_cb->use_hw_ss = p_config->use_hw_ss;
            nrf_spim_csn_configure(p_spim,
                                   p_config->ss_pin,
                                   (p_config->ss_active_high == true ?
                                        NRF_SPIM_CSN_POL_HIGH : NRF_SPIM_CSN_POL_LOW),
                                   p_config->ss_duration);
        }
#endif
        p_cb->ss_active_high = p_config->ss_active_high;
    }

#if NRFX_CHECK(NRFX_SPIM_EXTENDED_ENABLED)
    /* - DCX (optional) - output. */
    if (p_config->dcx_pin != NRFX_SPIM_PIN_NOT_USED)
    {
        nrf_gpio_pin_set(p_config->dcx_pin);
        nrf_gpio_cfg(p_config->dcx_pin,
                     NRF_GPIO_PIN_DIR_OUTPUT,
                     NRF_GPIO_PIN_INPUT_DISCONNECT,
                     NRF_GPIO_PIN_NOPULL,
                     pin_drive,
                     NRF_GPIO_PIN_NOSENSE);
        nrf_spim_dcx_pin_set(p_spim, p_config->dcx_pin);
    }

    /* Change rx delay */
    nrf_spim_iftiming_set(p_spim, p_config->rx_delay);
#endif

    nrf_spim_pins_set(p_spim, p_config->sck_pin, mosi_pin, miso_pin);
    nrf_spim_frequency_set(p_spim, p_config->frequency);
    nrf_spim_configure(p_spim, p_config->mode, p_config->bit_order);

    nrf_spim_orc_set(p_spim, p_config->orc);

    nrf_spim_enable(p_spim);

    if (p_cb->handler)
    {
        NRFX_IRQ_PRIORITY_SET(nrfx_get_irq_number(p_instance->p_reg),
            p_config->irq_priority);
        NRFX_IRQ_ENABLE(nrfx_get_irq_number(p_instance->p_reg));
    }

    p_cb->transfer_in_progress = false;
    p_cb->state = NRFX_DRV_STATE_INITIALIZED;

    err_code = NRFX_SUCCESS;
    NRFX_LOG_INFO("Function: %s, error code: %s.", __func__, NRFX_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}

static void spim_pin_uninit(uint32_t pin)
{
    if (pin == NRF_SPIM_PIN_NOT_CONNECTED)
    {
        return;
    }

    nrf_gpio_cfg_default(pin);
}

void nrfx_spim_uninit(nrfx_spim_t const * p_instance)
{
    spim_control_block_t * p_cb = &m_cb[p_instance->drv_inst_idx];
    NRFX_ASSERT(p_cb->state != NRFX_DRV_STATE_UNINITIALIZED);
    NRF_SPIM_Type * p_spim = p_instance->p_reg;

    if (p_cb->handler)
    {
        NRFX_IRQ_DISABLE(nrfx_get_irq_number(p_instance->p_reg));
        nrf_spim_int_disable(p_spim, NRF_SPIM_ALL_INTS_MASK);
        if (p_cb->transfer_in_progress)
        {
            /* Ensure that SPI is not performing any transfer. */
            spim_abort(p_spim, p_cb);
        }
    }

    nrf_spim_disable(p_spim);

    spim_pin_uninit(nrf_spim_sck_pin_get(p_spim));
    spim_pin_uninit(nrf_spim_miso_pin_get(p_spim));
    spim_pin_uninit(nrf_spim_mosi_pin_get(p_spim));
#if NRFX_CHECK(NRFX_SPIM_EXTENDED_ENABLED)
    if (SPIM_DCX_PRESENT_VALIDATE(p_instance->drv_inst_idx))
    {
        spim_pin_uninit(nrf_spim_dcx_pin_get(p_spim));
    }
#endif
    if (p_cb->ss_pin != NRFX_SPIM_PIN_NOT_USED)
    {
        nrf_gpio_cfg_default(p_cb->ss_pin);
    }

#if NRFX_CHECK(USE_WORKAROUND_FOR_ANOMALY_195)
    if (p_spim == NRF_SPIM3)
    {
        *(volatile uint32_t *)0x4002F004 = 1;
    }
#endif

#if NRFX_CHECK(NRFX_PRS_ENABLED)
    nrfx_prs_release(p_instance->p_reg);
#endif

    p_cb->state = NRFX_DRV_STATE_UNINITIALIZED;
}

#if NRFX_CHECK(NRFX_SPIM_EXTENDED_ENABLED)
nrfx_err_t nrfx_spim_xfer_dcx(nrfx_spim_t const *           p_instance,
                              nrfx_spim_xfer_desc_t const * p_xfer_desc,
                              uint32_t                      flags,
                              uint8_t                       cmd_length)
{
    (void)flags;

    NRFX_ASSERT(cmd_length <= NRF_SPIM_DCX_CNT_ALL_CMD);
    nrf_spim_dcx_cnt_set((NRF_SPIM_Type *)p_instance->p_reg, cmd_length);
    return nrfx_spim_xfer(p_instance, p_xfer_desc, 0);
}
#endif


static void spim_int_enable(NRF_SPIM_Type * p_spim, bool enable);

static void finish_transfer(spim_control_block_t * p_cb)
{

    #if USING_SPI_DMA
        struct spi_dma_message *mess = (struct spi_dma_message*)(p_cb->p_context);
        if (mess->cs_pin != PIN_NONE && mess->cs_release)
        {
        #if NRFX_CHECK(NRFX_SPIM_EXTENDED_ENABLED)
            if (!mess->use_hw_ss)
        #endif
            {
                if (mess->ss_active_high)
                {
                    nrf_gpio_pin_clear(mess->cs_pin);
                }
                else
                {
                    nrf_gpio_pin_set(mess->cs_pin);
                }
            }
        }

    #else
        /* If Slave Select signal is used, this is the time to deactivate it. */
        if (p_cb->ss_pin != NRFX_SPIM_PIN_NOT_USED)
        {
        #if NRFX_CHECK(NRFX_SPIM_EXTENDED_ENABLED)
            if (!p_cb->use_hw_ss)
        #endif
            {
                if (p_cb->ss_active_high)
                {
                    nrf_gpio_pin_clear(p_cb->ss_pin);
                }
                else
                {
                    nrf_gpio_pin_set(p_cb->ss_pin);
                }
            }
        }
    #endif


    /* By clearing this flag before calling the handler we allow subsequent */
    /* transfers to be started directly from the handler function. */
    p_cb->transfer_in_progress = false;

    p_cb->evt.type = NRFX_SPIM_EVENT_DONE;
    p_cb->handler(&p_cb->evt, p_cb->p_context);

    #if USING_SPI_DMA
        spim_int_enable(mess->spim, ((mess->flags) & NRFX_SPIM_FLAG_NO_XFER_EVT_HANDLER));
        rt_completion_done(mess->cpt);
    #endif
}

static void spim_int_enable(NRF_SPIM_Type * p_spim, bool enable)
{
    if (!enable)
    {
        nrf_spim_int_disable(p_spim, NRF_SPIM_INT_END_MASK);
    }
    else
    {
        nrf_spim_int_enable(p_spim, NRF_SPIM_INT_END_MASK);
    }
}

static void spim_list_enable_handle(NRF_SPIM_Type * p_spim, uint32_t flags)
{
    if (NRFX_SPIM_FLAG_TX_POSTINC & flags)
    {
        nrf_spim_tx_list_enable(p_spim);
    }
    else
    {
        nrf_spim_tx_list_disable(p_spim);
    }

    if (NRFX_SPIM_FLAG_RX_POSTINC & flags)
    {
        nrf_spim_rx_list_enable(p_spim);
    }
    else
    {
        nrf_spim_rx_list_disable(p_spim);
    }
}

static nrfx_err_t spim_xfer(NRF_SPIM_Type               * p_spim,
                            spim_control_block_t        * p_cb,
                            nrfx_spim_xfer_desc_t const * p_xfer_desc,
                            uint32_t                      flags)
{
    nrfx_err_t err_code;
    /* EasyDMA requires that transfer buffers are placed in Data RAM region; */
    /* signal error if they are not. */
    if ((p_xfer_desc->p_tx_buffer != NULL && !nrfx_is_in_ram(p_xfer_desc->p_tx_buffer)) ||
        (p_xfer_desc->p_rx_buffer != NULL && !nrfx_is_in_ram(p_xfer_desc->p_rx_buffer)))
    {
        p_cb->transfer_in_progress = false;
        err_code = NRFX_ERROR_INVALID_ADDR;
        NRFX_LOG_WARNING("Function: %s, error code: %s.",
                         __func__,
                         NRFX_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

#if NRFX_CHECK(NRFX_SPIM_NRF52_ANOMALY_109_WORKAROUND_ENABLED)
    p_cb->tx_length = 0;
    p_cb->rx_length = 0;
#endif

    nrf_spim_tx_buffer_set(p_spim, p_xfer_desc->p_tx_buffer, p_xfer_desc->tx_length);
    nrf_spim_rx_buffer_set(p_spim, p_xfer_desc->p_rx_buffer, p_xfer_desc->rx_length);

#if NRFX_CHECK(NRFX_SPIM3_NRF52840_ANOMALY_198_WORKAROUND_ENABLED)
    if (p_spim == NRF_SPIM3)
    {
        anomaly_198_enable(p_xfer_desc->p_tx_buffer, p_xfer_desc->tx_length);
    }
#endif

    nrf_spim_event_clear(p_spim, NRF_SPIM_EVENT_END);

    spim_list_enable_handle(p_spim, flags);

    if (!(flags & NRFX_SPIM_FLAG_HOLD_XFER))
    {
        nrf_spim_task_trigger(p_spim, NRF_SPIM_TASK_START);
    }
#if NRFX_CHECK(NRFX_SPIM_NRF52_ANOMALY_109_WORKAROUND_ENABLED)
    if (flags & NRFX_SPIM_FLAG_HOLD_XFER)
    {
        nrf_spim_event_clear(p_spim, NRF_SPIM_EVENT_STARTED);
        p_cb->tx_length = p_xfer_desc->tx_length;
        p_cb->rx_length = p_xfer_desc->rx_length;
        nrf_spim_tx_buffer_set(p_spim, p_xfer_desc->p_tx_buffer, 0);
        nrf_spim_rx_buffer_set(p_spim, p_xfer_desc->p_rx_buffer, 0);
        nrf_spim_int_enable(p_spim, NRF_SPIM_INT_STARTED_MASK);
    }
#endif

    if (!p_cb->handler)
    {
        if (!(flags & NRFX_SPIM_FLAG_HOLD_XFER))
        {
            while (!nrf_spim_event_check(p_spim, NRF_SPIM_EVENT_END))
            {}
        }

#if NRFX_CHECK(NRFX_SPIM3_NRF52840_ANOMALY_198_WORKAROUND_ENABLED)
        if (p_spim == NRF_SPIM3)
        {
            anomaly_198_disable();
        }
#endif
        if (p_cb->ss_pin != NRFX_SPIM_PIN_NOT_USED)
        {
    #if NRFX_CHECK(NRFX_SPIM_EXTENDED_ENABLED)
            if (!p_cb->use_hw_ss)
    #endif
            {
                if (p_cb->ss_active_high)
                {
                    nrf_gpio_pin_clear(p_cb->ss_pin);
                }
                else
                {
                    nrf_gpio_pin_set(p_cb->ss_pin);
                }
            }
        }
    }
    else
    {
        spim_int_enable(p_spim, !(flags & NRFX_SPIM_FLAG_NO_XFER_EVT_HANDLER));
    }
    err_code = NRFX_SUCCESS;
    NRFX_LOG_INFO("Function: %s, error code: %s.", __func__, NRFX_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}

nrfx_err_t nrfx_spim_xfer(nrfx_spim_t const *           p_instance,
                          nrfx_spim_xfer_desc_t const * p_xfer_desc,
                          uint32_t                      flags)
{
    spim_control_block_t * p_cb = &m_cb[p_instance->drv_inst_idx];
    NRFX_ASSERT(p_cb->state != NRFX_DRV_STATE_UNINITIALIZED);
    NRFX_ASSERT(p_xfer_desc->p_tx_buffer != NULL || p_xfer_desc->tx_length == 0);
    NRFX_ASSERT(p_xfer_desc->p_rx_buffer != NULL || p_xfer_desc->rx_length == 0);
    NRFX_ASSERT(SPIM_LENGTH_VALIDATE(p_instance->drv_inst_idx,
                                     p_xfer_desc->rx_length,
                                     p_xfer_desc->tx_length));
    NRFX_ASSERT(!(flags & NRFX_SPIM_FLAG_HOLD_XFER) ||
                (p_cb->ss_pin == NRFX_SPIM_PIN_NOT_USED));

    nrfx_err_t err_code = NRFX_SUCCESS;

    if (p_cb->transfer_in_progress)
    {
        err_code = NRFX_ERROR_BUSY;
        NRFX_LOG_WARNING("Function: %s, error code: %s.",
                         __func__,
                         NRFX_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    else
    {
        if (p_cb->handler && !(flags & (NRFX_SPIM_FLAG_REPEATED_XFER |
                                        NRFX_SPIM_FLAG_NO_XFER_EVT_HANDLER)))
        {
            p_cb->transfer_in_progress = true;
        }
    }

    p_cb->evt.xfer_desc = *p_xfer_desc;

    if (p_cb->ss_pin != NRFX_SPIM_PIN_NOT_USED)
    {
#if NRFX_CHECK(NRFX_SPIM_EXTENDED_ENABLED)
        if (!p_cb->use_hw_ss)
#endif
        {
            if (p_cb->ss_active_high)
            {
                nrf_gpio_pin_set(p_cb->ss_pin);
            }
            else
            {
                nrf_gpio_pin_clear(p_cb->ss_pin);
            }
        }
    }

    return spim_xfer(p_instance->p_reg, p_cb,  p_xfer_desc, flags);
}


static nrfx_err_t rtt_spim_xfer(NRF_SPIM_Type           * p_spim,
                            spim_control_block_t        * p_cb,
                            nrfx_spim_xfer_desc_t const * p_xfer_desc,
                            uint32_t                      flags,
                            struct rt_spi_message       * message,
                            struct rt_spi_device        * dev)
{
    #define DMA_TRANS_MIN_LEN  (20) /* only buffer length >= DMA_TRANS_MIN_LEN will use DMA mode */

    nrfx_err_t err_code;
    /* EasyDMA requires that transfer buffers are placed in Data RAM region; */
    /* signal error if they are not. */
    if ((p_xfer_desc->p_tx_buffer != NULL && !nrfx_is_in_ram(p_xfer_desc->p_tx_buffer)) ||
        (p_xfer_desc->p_rx_buffer != NULL && !nrfx_is_in_ram(p_xfer_desc->p_rx_buffer)))
    {
        p_cb->transfer_in_progress = false;
        err_code = NRFX_ERROR_INVALID_ADDR;
        NRFX_LOG_WARNING("Function: %s, error code: %s.",
                         __func__,
                         NRFX_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    #if USING_SPI_DMA
        struct spi_dma_message *mess = (struct spi_dma_message *)(p_cb->p_context);
        mess->cs_take = message->cs_take;
        mess->cs_release = message->cs_release;
        mess->flags = flags;
        mess->spim = p_spim;
    #endif

    nrf_spim_event_clear(p_spim, NRF_SPIM_EVENT_END);

    #if NRFX_CHECK(NRFX_SPIM_NRF52_ANOMALY_109_WORKAROUND_ENABLED)
        p_cb->tx_length = 0;
        p_cb->rx_length = 0;
    #endif

    nrf_spim_tx_buffer_set(p_spim, p_xfer_desc->p_tx_buffer, p_xfer_desc->tx_length);
    nrf_spim_rx_buffer_set(p_spim, p_xfer_desc->p_rx_buffer, p_xfer_desc->rx_length);

    #if NRFX_CHECK(NRFX_SPIM3_NRF52840_ANOMALY_198_WORKAROUND_ENABLED)
        if (p_spim == NRF_SPIM3)
        {
            anomaly_198_enable(p_xfer_desc->p_tx_buffer, p_xfer_desc->tx_length);
        }
    #endif

    spim_list_enable_handle(p_spim, flags);

    if (!(flags & NRFX_SPIM_FLAG_HOLD_XFER))
    {
        nrf_spim_task_trigger(p_spim, NRF_SPIM_TASK_START);
/*      rt_kprintf("SPIM task started.\n"); */
    }
#if NRFX_CHECK(NRFX_SPIM_NRF52_ANOMALY_109_WORKAROUND_ENABLED)
    if (flags & NRFX_SPIM_FLAG_HOLD_XFER)
    {
        nrf_spim_event_clear(p_spim, NRF_SPIM_EVENT_STARTED);
        p_cb->tx_length = p_xfer_desc->tx_length;
        p_cb->rx_length = p_xfer_desc->rx_length;
        nrf_spim_tx_buffer_set(p_spim, p_xfer_desc->p_tx_buffer, 0);
        nrf_spim_rx_buffer_set(p_spim, p_xfer_desc->p_rx_buffer, 0);
        nrf_spim_int_enable(p_spim, NRF_SPIM_INT_STARTED_MASK);
    }
#endif

    if (p_cb->handler == RT_NULL || (p_xfer_desc->rx_length<= DMA_TRANS_MIN_LEN && p_xfer_desc->tx_length<= DMA_TRANS_MIN_LEN))
    {
        /* no cb func or lenth < DMA_TRANS_MIN_LEN, wait for transfer end */
/*      spim_int_enable(p_spim, ((mess->flags) & NRFX_SPIM_FLAG_NO_XFER_EVT_HANDLER)); */
        if (!(flags & NRFX_SPIM_FLAG_HOLD_XFER))
        {
            while (!nrf_spim_event_check(p_spim, NRF_SPIM_EVENT_END))
            {

            }
/*          rt_kprintf("SPIM transfer end.\n"); */
             p_cb->transfer_in_progress = false;
        }

#if NRFX_CHECK(NRFX_SPIM3_NRF52840_ANOMALY_198_WORKAROUND_ENABLED)
        if (p_spim == NRF_SPIM3)
        {
            anomaly_198_disable();
        }
#endif

        if (dev->cs_pin != PIN_NONE && message->cs_release)
        {
        #if NRFX_CHECK(NRFX_SPIM_EXTENDED_ENABLED)
            if (!p_cb->use_hw_ss)
        #endif
            {
                if (p_cb->ss_active_high)
                    nrf_gpio_pin_clear(dev->cs_pin);
                else
                    nrf_gpio_pin_set(dev->cs_pin);
            }
        }
    }
    else
    {
        #if USING_SPI_DMA
            spim_int_enable(p_spim, !(flags & NRFX_SPIM_FLAG_NO_XFER_EVT_HANDLER));
            p_cb->transfer_in_progress = false;
            if (rt_completion_wait(mess->cpt, 5000) != RT_EOK)
                {
                    rt_kprintf("wait for DMA interrupt overtime!");
                    return NRFX_ERROR_TIMEOUT;
                }
        #else
            spim_int_enable(p_spim, !(flags & NRFX_SPIM_FLAG_NO_XFER_EVT_HANDLER));
        #endif
    }
    err_code = NRFX_SUCCESS;
    NRFX_LOG_INFO("Function: %s, error code: %s.", __func__, NRFX_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}

nrfx_err_t rtt_nrfx_spim_xfer(nrfx_spim_t const         *p_instance,
                            nrfx_spim_xfer_desc_t const *p_xfer_desc,
                            uint32_t                     flags,
                            struct rt_spi_message       *message,
                            struct rt_spi_device        *dev)
{
    spim_control_block_t * p_cb = &m_cb[p_instance->drv_inst_idx];
    NRFX_ASSERT(p_cb->state != NRFX_DRV_STATE_UNINITIALIZED);
    NRFX_ASSERT(p_xfer_desc->p_tx_buffer != NULL || p_xfer_desc->tx_length == 0);
    NRFX_ASSERT(p_xfer_desc->p_rx_buffer != NULL || p_xfer_desc->rx_length == 0);
    NRFX_ASSERT(SPIM_LENGTH_VALIDATE(p_instance->drv_inst_idx,
                                     p_xfer_desc->rx_length,
                                     p_xfer_desc->tx_length));
    NRFX_ASSERT(!(flags & NRFX_SPIM_FLAG_HOLD_XFER) ||
                (p_cb->ss_pin == NRFX_SPIM_PIN_NOT_USED));

    nrfx_err_t err_code = NRFX_SUCCESS;

    if (p_cb->transfer_in_progress)
    {
        err_code = NRFX_ERROR_BUSY;
        NRFX_LOG_WARNING("Function: %s, error code: %s.",
                         __func__,
                         NRFX_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    else
    {
        if (p_cb->handler && !(flags & (NRFX_SPIM_FLAG_REPEATED_XFER |
                                        NRFX_SPIM_FLAG_NO_XFER_EVT_HANDLER)))
        {
            p_cb->transfer_in_progress = true;
        }
    }

    p_cb->evt.xfer_desc = *p_xfer_desc;

    if (dev->cs_pin != PIN_NONE && message->cs_take)
    {
#if NRFX_CHECK(NRFX_SPIM_EXTENDED_ENABLED)
        if (!p_cb->use_hw_ss && message->cs_take)
#endif
        {
            if (p_cb->ss_active_high)
            {
                nrf_gpio_pin_set(dev->cs_pin);
            }
            else
            {
                nrf_gpio_pin_clear(dev->cs_pin);
            }
        }
    }

    return rtt_spim_xfer(p_instance->p_reg, p_cb, p_xfer_desc, flags, message, dev);
}

void nrfx_spim_abort(nrfx_spim_t const * p_instance)
{
    spim_control_block_t * p_cb = &m_cb[p_instance->drv_inst_idx];
    NRFX_ASSERT(p_cb->state != NRFX_DRV_STATE_UNINITIALIZED);

    spim_abort(p_instance->p_reg, p_cb);
}

uint32_t nrfx_spim_start_task_get(nrfx_spim_t const * p_instance)
{
    NRF_SPIM_Type * p_spim = (NRF_SPIM_Type *)p_instance->p_reg;
    return nrf_spim_task_address_get(p_spim, NRF_SPIM_TASK_START);
}

uint32_t nrfx_spim_end_event_get(nrfx_spim_t const * p_instance)
{
    NRF_SPIM_Type * p_spim = (NRF_SPIM_Type *)p_instance->p_reg;
    return nrf_spim_event_address_get(p_spim, NRF_SPIM_EVENT_END);
}

static void irq_handler(NRF_SPIM_Type * p_spim, spim_control_block_t * p_cb)
{
#if NRFX_CHECK(NRFX_SPIM_NRF52_ANOMALY_109_WORKAROUND_ENABLED)
    if ((nrf_spim_int_enable_check(p_spim, NRF_SPIM_INT_STARTED_MASK)) &&
        (nrf_spim_event_check(p_spim, NRF_SPIM_EVENT_STARTED)) )
    {
        /* Handle first, zero-length, auxiliary transmission. */
        nrf_spim_event_clear(p_spim, NRF_SPIM_EVENT_STARTED);
        nrf_spim_event_clear(p_spim, NRF_SPIM_EVENT_END);

        NRFX_ASSERT(p_spim->TXD.MAXCNT == 0);
        p_spim->TXD.MAXCNT = p_cb->tx_length;

        NRFX_ASSERT(p_spim->RXD.MAXCNT == 0);
        p_spim->RXD.MAXCNT = p_cb->rx_length;

        /* Disable STARTED interrupt, used only in auxiliary transmission. */
        nrf_spim_int_disable(p_spim, NRF_SPIM_INT_STARTED_MASK);

        /* Start the actual, glitch-free transmission. */
        nrf_spim_task_trigger(p_spim, NRF_SPIM_TASK_START);
        return;
    }
#endif

    if (nrf_spim_event_check(p_spim, NRF_SPIM_EVENT_END))
    {
#if NRFX_CHECK(NRFX_SPIM3_NRF52840_ANOMALY_198_WORKAROUND_ENABLED)
        if (p_spim == NRF_SPIM3)
        {
            anomaly_198_disable();
        }
#endif
        nrf_spim_event_clear(p_spim, NRF_SPIM_EVENT_END);
        NRFX_ASSERT(p_cb->handler);
        NRFX_LOG_DEBUG("Event: NRF_SPIM_EVENT_END.");
        finish_transfer(p_cb);
    }
}

#if NRFX_CHECK(NRFX_SPIM0_ENABLED)
void nrfx_spim_0_irq_handler(void)
{
    irq_handler(NRF_SPIM0, &m_cb[NRFX_SPIM0_INST_IDX]);
}
#endif

#if NRFX_CHECK(NRFX_SPIM1_ENABLED)
void nrfx_spim_1_irq_handler(void)
{
    rt_interrupt_enter();
    irq_handler(NRF_SPIM1, &m_cb[NRFX_SPIM1_INST_IDX]);
    rt_interrupt_leave();
}
#endif

#if NRFX_CHECK(NRFX_SPIM2_ENABLED)
void nrfx_spim_2_irq_handler(void)
{
    rt_interrupt_enter();
    irq_handler(NRF_SPIM2, &m_cb[NRFX_SPIM2_INST_IDX]);
    rt_interrupt_leave();
}
#endif

#if NRFX_CHECK(NRFX_SPIM3_ENABLED)
void nrfx_spim_3_irq_handler(void)
{
    rt_interrupt_enter();
    irq_handler(NRF_SPIM3, &m_cb[NRFX_SPIM3_INST_IDX]);
    rt_interrupt_leave();
}
#endif

#if NRFX_CHECK(NRFX_SPIM4_ENABLED)
void nrfx_spim_4_irq_handler(void)
{
    rt_interrupt_enter();
    irq_handler(NRF_SPIM4, &m_cb[NRFX_SPIM4_INST_IDX]);
    rt_interrupt_leave();
}
#endif

#endif /* NRFX_CHECK(NRFX_SPIM_ENABLED) */

