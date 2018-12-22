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
/**
 * @addtogroup nrf_pdm PDM HAL and driver
 * @ingroup    nrf_drivers
 * @brief      @tagAPI52 Pulse density modulation (PDM) interface APIs.
 *
 * The PDM HAL provides basic APIs for accessing the registers of the PDM interface peripheral.
 * The PDM driver provides APIs on a higher level.
 *
 * @defgroup nrf_drv_pdm PDM driver
 * @{
 * @ingroup  nrf_pdm
 *
 * @brief    @tagAPI52 Pulse density modulation (PDM) interface driver.
 */


#ifndef NRF_DRV_PDM_H__
#define NRF_DRV_PDM_H__

#include "sdk_config.h"
#include "nrf_pdm.h"
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif


#define NRF_PDM_MAX_BUFFER_SIZE 32768


/**
 * @brief PDM interface driver configuration structure.
 */
typedef struct
{
    nrf_pdm_mode_t mode;               ///< Interface operation mode.
    nrf_pdm_edge_t edge;               ///< Sampling mode.
    uint8_t        pin_clk;            ///< CLK pin.
    uint8_t        pin_din;            ///< DIN pin.
    nrf_pdm_freq_t clock_freq;         ///< Clock frequency.
    nrf_pdm_gain_t gain_l;             ///< Left channel gain.
    nrf_pdm_gain_t gain_r;             ///< Right channel gain.
    uint8_t        interrupt_priority; ///< Interrupt priority.
    uint16_t       buffer_length;      ///< Length of a single buffer (in 16-bit words).
    int16_t *      buffer_a;           ///< Sample buffer A (filled first).
    int16_t *      buffer_b;           ///< Sample buffer B (filled after buffer A).
} nrf_drv_pdm_config_t;


/**
 * @brief Macro for setting @ref nrf_drv_pdm_config_t to default settings
 *        in single ended mode.
 *
 * @param PIN_CLK  CLK output pin.
 * @param PIN_DIN  DIN input pin.
 * @param BUFF_A   Sample buffer A (filled first).
 * @param BUFF_B   Sample buffer B (filled after buffer A).
 * @param BUFF_LEN Length of a single buffer (in 16-bit words).
 */
#define NRF_DRV_PDM_DEFAULT_CONFIG(PIN_CLK, PIN_DIN, BUFF_A, BUFF_B, BUFF_LEN) \
{                                                                              \
    .mode               = (nrf_pdm_mode_t)PDM_CONFIG_MODE,                     \
    .edge               = (nrf_pdm_edge_t)PDM_CONFIG_EDGE,                     \
    .pin_clk            = PIN_CLK,                                             \
    .pin_din            = PIN_DIN,                                             \
    .clock_freq         = (nrf_pdm_freq_t)PDM_CONFIG_CLOCK_FREQ,               \
    .gain_l             = NRF_PDM_GAIN_DEFAULT,                                \
    .gain_r             = NRF_PDM_GAIN_DEFAULT,                                \
    .interrupt_priority = PDM_CONFIG_IRQ_PRIORITY,                             \
    .buffer_length      = BUFF_LEN,                                            \
    .buffer_a           = BUFF_A,                                              \
    .buffer_b           = BUFF_B                                               \
}


/**
 * @brief   Handler for PDM interface ready events.
 *
 * This event handler is called when a buffer is full and ready to be processed.
 *
 * @param[in] p_buffer Sample buffer pointer.
 * @param[in] length   Buffer length in 16-bit words.
 */
typedef void (*nrf_drv_pdm_event_handler_t)(uint32_t * buffer, uint16_t length);


/**
 * @brief Function for initializing the PDM interface.
 *
 * @param[in] p_config      Pointer to a configuration structure. If NULL, the default one is used.
 * @param[in] event_handler Event handler provided by the user.
 *
 * @retval    NRF_SUCCESS If initialization was successful.
 * @retval    NRF_ERROR_INVALID_STATE If the driver is already initialized.
 * @retval    NRF_ERROR_INVALID_PARAM If invalid parameters were specified.
 */
ret_code_t nrf_drv_pdm_init(nrf_drv_pdm_config_t const * p_config,
                            nrf_drv_pdm_event_handler_t event_handler);


/**
 * @brief Function for uninitializing the PDM interface.
 *
 * This function stops PDM sampling, if it is in progress.
 */
void nrf_drv_pdm_uninit(void);


/**
 * @brief Function for getting the address of a PDM interface task.
 *
 * @param[in]  task Task.
 *
 * @return     Task address.
 */
__STATIC_INLINE uint32_t nrf_drv_pdm_task_address_get(nrf_pdm_task_t task)
{
    return nrf_pdm_task_address_get(task);
}


/**
 * @brief Function for getting the state of the PDM interface.
 *
 * @retval TRUE  If the PDM interface is enabled.
 * @retval FALSE If the PDM interface is disabled.
 */
__STATIC_INLINE bool nrf_drv_pdm_enable_check()
{
    return nrf_pdm_enable_check();
}


/**
 * @brief Function for starting PDM sampling.
 *
 * @retval NRF_SUCCESS    If sampling was started successfully or was already in progress.
 * @retval NRF_ERROR_BUSY If a previous start/stop operation is in progress.
 */
ret_code_t nrf_drv_pdm_start(void);


/**
 * @brief   Function for stopping PDM sampling.
 *
 * When this function is called, the PDM interface is stopped after finishing
 * the current frame.
 * The event handler function might be called once more after calling this function.
 *
 * @retval NRF_SUCCESS    If sampling was stopped successfully or was already stopped before.
 * @retval NRF_ERROR_BUSY If a previous start/stop operation is in progress.
 */
ret_code_t nrf_drv_pdm_stop(void);



#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_PDM_H__

/** @} */
