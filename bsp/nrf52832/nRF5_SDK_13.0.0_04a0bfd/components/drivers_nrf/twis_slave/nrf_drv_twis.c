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
#if NRF_MODULE_ENABLED(TWIS)
#define ENABLED_TWIS_COUNT (TWIS0_ENABLED+TWIS1_ENABLED)
#if ENABLED_TWIS_COUNT
#include "nrf_drv_twis.h"
#include "nrf_assert.h"
#include "app_util_platform.h"
#include "compiler_abstraction.h"

#define NRF_LOG_MODULE_NAME "TWIS"

#if TWIS_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       TWIS_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  TWIS_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR TWIS_CONFIG_DEBUG_COLOR
#define EVT_TO_STR(event)   (event == NRF_TWIS_EVENT_STOPPED ? "NRF_TWIS_EVENT_STOPPED" :               \
                            (event == NRF_TWIS_EVENT_ERROR ? "NRF_TWIS_EVENT_ERROR" :                   \
                            (event == NRF_TWIS_EVENT_RXSTARTED ? "NRF_TWIS_EVENT_RXSTARTED" :           \
                            (event == NRF_TWIS_EVENT_TXSTARTED ? "NRF_TWIS_EVENT_TXSTARTED" :           \
                            (event == NRF_TWIS_EVENT_WRITE ? "NRF_TWIS_EVENT_WRITE" :                   \
                            (event == NRF_TWIS_EVENT_READ ? "NRF_TWIS_EVENT_READ" : "UNKNOWN EVENT"))))))
#else //TWIS_CONFIG_LOG_ENABLED
#define EVT_TO_STR(event)   ""
#define NRF_LOG_LEVEL       0
#endif //TWIS_CONFIG_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

/**
 * @internal
 * @ingroup lib_twis_drv
 * @defgroup lib_twis_drv_ivars Software controlled TWI Slave internal variables
 *
 * Internal variables for TWIS.
 * @{
 */

/**
 * @brief Actual state of internal state machine
 *
 * Current substate of powered on state.
 */
typedef enum
{
    NRF_DRV_TWIS_SUBSTATE_IDLE,          ///< No ongoing transmission
    NRF_DRV_TWIS_SUBSTATE_READ_WAITING,  ///< Read request received, waiting for data
    NRF_DRV_TWIS_SUBSTATE_READ_PENDING,  ///< Reading is actually pending (data sending)
    NRF_DRV_TWIS_SUBSTATE_WRITE_WAITING, ///< Write request received, waiting for data buffer
    NRF_DRV_TWIS_SUBSTATE_WRITE_PENDING, ///< Writing is actually pending (data receiving)
}nrf_drv_twis_substate_t;

/**
 * @brief Constant instance part
 *
 * Instance data that have not to change.
 * It may be placed in FLASH memory.
 */
typedef struct
{
    NRF_TWIS_Type * const p_reg; ///< Peripheral registry address
} nrf_drv_twis_const_inst_t;

/**
 * @brief Variable instance part
 *
 * There are all informations for the instance that may change.
 */
typedef struct
{
    nrf_drv_state_t                  state;      ///< Actual driver state
    volatile nrf_drv_twis_substate_t substate;   ///< Actual driver substate
    nrf_drv_twis_event_handler_t     ev_handler; ///< Event handler functiomn
    volatile uint32_t                error;      ///< Internal error flags
                                                 /**< Internal copy of hardware errors flags merged
                                                  *   with specific internal driver errors flags.
                                                  *
                                                  *   @note This value can be changed in the interrupt
                                                  *   and cleared in the main program.
                                                  *   Always use Atomic load-store when updating
                                                  *   this value in main loop.
                                                  */
}nrf_drv_twis_var_inst_t;


/** The constant instance part implementation */
static const nrf_drv_twis_const_inst_t m_const_inst[ENABLED_TWIS_COUNT] =
{
    #define X(n)  { .p_reg = NRF_TWIS##n },
    #include "nrf_drv_twis_inst.def"
};

/** The variable instance part implementation */
static nrf_drv_twis_var_inst_t m_var_inst[ENABLED_TWIS_COUNT] =
{
    #define X(n) { .state      = NRF_DRV_STATE_UNINITIALIZED, \
                   .substate   = NRF_DRV_TWIS_SUBSTATE_IDLE, \
                   .ev_handler = NULL, \
                   .error      = 0 },
    #include "nrf_drv_twis_inst.def"
};

#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    #define IRQ_HANDLER_NAME(n) irq_handler_for_instance_##n
    #define IRQ_HANDLER(n)      static void IRQ_HANDLER_NAME(n)(void)

    #if NRF_MODULE_ENABLED(TWIS0)
        IRQ_HANDLER(0);
    #endif
    #if NRF_MODULE_ENABLED(TWIS1)
        IRQ_HANDLER(1);
    #endif
    static nrf_drv_irq_handler_t const m_irq_handlers[ENABLED_TWIS_COUNT] = {
    #if NRF_MODULE_ENABLED(TWIS0)
        IRQ_HANDLER_NAME(0),
    #endif
    #if NRF_MODULE_ENABLED(TWIS1)
        IRQ_HANDLER_NAME(1),
    #endif
    };
#else
    #define IRQ_HANDLER(n) \
        void SPIM##n##_SPIS##n##_TWIM##n##_TWIS##n##_SPI##n##_TWI##n##_IRQHandler(void)
#endif // NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)

/**
 * @brief State processing semaphore
 *
 * There are semaphores used when when working in synchronous mode (without interrupts activated).
 * @note
 * In synchronous mode before every state checking the state machine is executed.
 * But the situation where state checking function is called from main task and in the same from
 * interrupt task has to be considered.
 * In such a situation the @ref nrf_drv_twis_state_machine function may be interrupted by second
 * call to the same function.
 * If in this second call any event will be detected it may be lost because new substate would be
 * overwritten when interrupted function finishes.
 * In the same time information about event would be lost because it is cleared in interrupting
 * function.
 * @note
 * To make situation described above safe, simple semaphore is implemented.
 * It is just a binary flag that informs that state machine is actually executing and should not
 * be processed in any interrupting function.
 * Because of how it is used no atomic instructions are required to support this kind of semaphore.
 * It is not waitable semaphore - function executed or not depending of its state.
 */
static uint8_t m_sm_semaphore[ENABLED_TWIS_COUNT];

/**
 * @brief Used interrupts mask
 *
 * Mask for all interrupts used by this library
 */
static const uint32_t m_used_ints_mask =
        NRF_TWIS_INT_STOPPED_MASK   |
        NRF_TWIS_INT_ERROR_MASK     |
        NRF_TWIS_INT_RXSTARTED_MASK |
        NRF_TWIS_INT_TXSTARTED_MASK |
        NRF_TWIS_INT_WRITE_MASK     |
        NRF_TWIS_INT_READ_MASK;


/** @} */ /* End  of lib_driver_twis_slave_ivars */

/**
 * @internal
 * @ingroup lib_twis_drv
 * @defgroup lib_twis_drv_ifunc Software controlled TWI Slave auxiliary internal functions
 *
 * Internal variables for TWIS.
 * @{
 */

/**
 * @brief Clear all  events
 *
 * Function clears all actually pending events
 */
static void nrf_drv_twis_clear_all_events(NRF_TWIS_Type * const p_reg)
{
    /* Clear all events */
    nrf_twis_event_clear(p_reg, NRF_TWIS_EVENT_STOPPED);
    nrf_twis_event_clear(p_reg, NRF_TWIS_EVENT_ERROR);
    nrf_twis_event_clear(p_reg, NRF_TWIS_EVENT_RXSTARTED);
    nrf_twis_event_clear(p_reg, NRF_TWIS_EVENT_TXSTARTED);
    nrf_twis_event_clear(p_reg, NRF_TWIS_EVENT_WRITE);
    nrf_twis_event_clear(p_reg, NRF_TWIS_EVENT_READ);
}

/**
 * @brief Reset all the registers to known state
 *
 * This function clears all registers that requires it to known state.
 * TWIS is left disabled after this function.
 * All events are cleared.
 * @param[out] p_reg TWIS to reset register address
 */
static inline void nrf_drv_twis_swreset(NRF_TWIS_Type * const p_reg)
{
    /* Disable TWIS */
    nrf_twis_disable(p_reg);

    /* Disconnect pins */
    nrf_twis_pins_set(p_reg, ~0U, ~0U);

    /* Disable interrupt global for the instance */
    nrf_drv_common_irq_disable(nrf_drv_get_IRQn(p_reg));

    /* Disable interrupts */
    nrf_twis_int_disable(p_reg, ~0U);
}

/**
 * @brief Configure pin
 *
 * Function configures selected for work as SDA or SCL.
 * @param pin Pin number to configure
 */
static inline void nrf_drv_twis_config_pin(uint32_t pin, nrf_gpio_pin_pull_t pull)
{
    nrf_gpio_cfg(pin,
                 NRF_GPIO_PIN_DIR_INPUT,
                 NRF_GPIO_PIN_INPUT_DISCONNECT,
                 pull,
                 NRF_GPIO_PIN_S0D1,
                 NRF_GPIO_PIN_NOSENSE);
}

/**
 * @brief Call event handler
 *
 * Function that calls event handler.
 * The event handler would be only called if its value is != NULL.
 * @param     instNr Driver instance number that has called this runtime.
 * @param[in] pev    Event structure to pass to event handler
 * @note
 * Remember about possible multithreading.
 * It is acceptable to call old event function if it was already disabled.
 * What is unacceptable is jump into NULL pointer.
 */
static void nrf_drv_call_event_handler(uint8_t instNr, nrf_drv_twis_evt_t const * const pev)
{
    nrf_drv_twis_event_handler_t evh = m_var_inst[instNr].ev_handler;
    if (NULL != evh)
    {
        evh(pev);
    }
}

/**
 * @brief Auxiliary function for getting event state on right bit possition
 *
 * This function calls @ref nrf_twis_event_get function but the the result
 * is shifted to match INTEN register scheme.
 *
 * @param[in,out] p_reg TWIS to read  event from
 * @param ev  Event code
 *
 * @return Selected event state shifted by @ref nrf_drv_event_to_bitpos
 *
 * @sa nrf_twis_event_get
 * @sa nrf_drv_event_to_bitpos
 */
static inline uint32_t nrf_drv_twis_event_bit_get(NRF_TWIS_Type * const p_reg, nrf_twis_event_t ev)
{
    return (uint32_t)nrf_twis_event_get_and_clear(p_reg, ev) << nrf_drv_event_to_bitpos(ev);
}

/**
 * @brief Auxiliary function for checking event bit inside given flags value
 *
 * Function used here to check presence of the event inside given flags value.
 * It transforms given event to bit possition and then checks if in given variable it is cleared.
 *
 * @param flags Flags to test
 * @param ev Event code
 *
 * @retval true Flag for selected event is set
 * @retval false Flag for selected event is cleared
 */
static inline bool nrf_drv_twis_check_bit(uint32_t flags, nrf_twis_event_t ev)
{
    return 0 != (flags & (1U<<nrf_drv_event_to_bitpos(ev)));
}

/**
 * @brief Auxiliary function for clearing event bit in given flags value
 *
 * Function used to clear selected event bit.
 *
 * @param flags Flags to process
 * @param ev    Event code to clear
 *
 * @return Value @em flags with cleared event bit that matches given @em ev
 */
static inline uint32_t nrf_drv_twis_clear_bit(uint32_t flags, nrf_twis_event_t ev)
{
    return flags & ~(1U<<nrf_drv_event_to_bitpos(ev));
}

/**
 * @brief Auxiliary function for error processing
 *
 * Function called when in current substate the event apears and it cannot be processed.
 * It should be called also on ERROR event.
 * If given @em error parameter has zero value the @ref NRF_DRV_TWIS_ERROR_UNEXPECTED_EVENT
 * would be set.
 *
 * @param instNr Instance number
 * @param ev     What error event raport to event handler
 * @param error  Error flags
 */
static inline void nrf_drv_twis_process_error(
        uint8_t instNr,
        nrf_drv_twis_evt_type_t ev,
        uint32_t error)
{
    if (0 == error)
        error = NRF_DRV_TWIS_ERROR_UNEXPECTED_EVENT;
    nrf_drv_twis_evt_t evdata;
    evdata.type = ev;
    evdata.data.error = error;

    m_var_inst[instNr].error |= error;

    nrf_drv_call_event_handler(instNr, &evdata);
}


/**
 * @brief State machine main function
 *
 * State machine function that reacts on events.
 * This function gets all events and reacts on them only if there is any event detected.
 * It makes it possible to use it either in interrupt or in polling mode.
 * @param instNr Driver instance number that has called this runtime.
 */
static void nrf_drv_twis_state_machine(uint8_t instNr)
{
    if (!TWIS_NO_SYNC_MODE)
    {
        /* Exclude parallel processing of this function */
        if (m_sm_semaphore[instNr])
        {
            return;
        }
        m_sm_semaphore[instNr] = 1;
    }

    NRF_TWIS_Type * const p_reg = m_const_inst[instNr].p_reg;
    /* Event data structure to be passed into event handler */
    nrf_drv_twis_evt_t evdata;
    /* Current substate copy  */
    nrf_drv_twis_substate_t substate = m_var_inst[instNr].substate;
    /* Event flags */
    uint32_t ev = 0;

    /* Get all events */
    ev |= nrf_drv_twis_event_bit_get(p_reg, NRF_TWIS_EVENT_STOPPED);
    ev |= nrf_drv_twis_event_bit_get(p_reg, NRF_TWIS_EVENT_ERROR);
    ev |= nrf_drv_twis_event_bit_get(p_reg, NRF_TWIS_EVENT_RXSTARTED);
    ev |= nrf_drv_twis_event_bit_get(p_reg, NRF_TWIS_EVENT_TXSTARTED);
    ev |= nrf_drv_twis_event_bit_get(p_reg, NRF_TWIS_EVENT_WRITE);
    ev |= nrf_drv_twis_event_bit_get(p_reg, NRF_TWIS_EVENT_READ);

    /* State machine */
    while (0 != ev)
    {
        switch (substate)
        {
        case NRF_DRV_TWIS_SUBSTATE_IDLE:
            if (nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_STOPPED))
            {
                /* Stopped event is always allowed in IDLE state - just ignore */
                ev = nrf_drv_twis_clear_bit(ev, NRF_TWIS_EVENT_STOPPED);
            }
            else if (nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_READ))
            {
                evdata.type = TWIS_EVT_READ_REQ;
                if (nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_TXSTARTED))
                {
                    substate = NRF_DRV_TWIS_SUBSTATE_READ_PENDING;
                    evdata.data.buf_req = false;
                }
                else
                {
                    substate = NRF_DRV_TWIS_SUBSTATE_READ_WAITING;
                    evdata.data.buf_req = true;
                }
                nrf_drv_call_event_handler(instNr, &evdata);
                ev = nrf_drv_twis_clear_bit(ev, NRF_TWIS_EVENT_READ);
                ev = nrf_drv_twis_clear_bit(ev, NRF_TWIS_EVENT_TXSTARTED);
                ev = nrf_drv_twis_clear_bit(ev, NRF_TWIS_EVENT_WRITE);
                ev = nrf_drv_twis_clear_bit(ev, NRF_TWIS_EVENT_RXSTARTED);
            }
            else if (nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_WRITE))
            {
                evdata.type = TWIS_EVT_WRITE_REQ;
                if (nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_RXSTARTED))
                {
                    substate = NRF_DRV_TWIS_SUBSTATE_WRITE_PENDING;
                    evdata.data.buf_req = false;
                }
                else
                {
                    substate = NRF_DRV_TWIS_SUBSTATE_WRITE_WAITING;
                    evdata.data.buf_req = true;
                }
                nrf_drv_call_event_handler(instNr, &evdata);
                ev = nrf_drv_twis_clear_bit(ev, NRF_TWIS_EVENT_READ);
                ev = nrf_drv_twis_clear_bit(ev, NRF_TWIS_EVENT_TXSTARTED);
                ev = nrf_drv_twis_clear_bit(ev, NRF_TWIS_EVENT_WRITE);
                ev = nrf_drv_twis_clear_bit(ev, NRF_TWIS_EVENT_RXSTARTED);
            }
            else
            {
                nrf_drv_twis_process_error(instNr, TWIS_EVT_GENERAL_ERROR, nrf_twis_error_source_get_and_clear(p_reg));
                ev = 0;
            }
            break;
        case NRF_DRV_TWIS_SUBSTATE_READ_WAITING:
            if (nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_TXSTARTED) ||
               nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_WRITE)     ||
               nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_READ)      ||
               nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_STOPPED))
            {
                substate = NRF_DRV_TWIS_SUBSTATE_READ_PENDING;
                /* Any other bits requires further processing in PENDING substate */
                ev = nrf_drv_twis_clear_bit(ev, NRF_TWIS_EVENT_TXSTARTED);
            }
            else
            {
                nrf_drv_twis_process_error(instNr, TWIS_EVT_READ_ERROR, nrf_twis_error_source_get_and_clear(p_reg));
                substate = NRF_DRV_TWIS_SUBSTATE_IDLE;
                ev = 0;
            }
            break;
        case NRF_DRV_TWIS_SUBSTATE_READ_PENDING:
            if (nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_WRITE)||
               nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_READ) ||
               nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_STOPPED))
            {
                evdata.type = TWIS_EVT_READ_DONE;
                evdata.data.tx_amount = nrf_twis_tx_amount_get(p_reg);
                NRF_LOG_INFO("Transfer rx_len:%d\r\n", evdata.data.tx_amount);
                NRF_LOG_DEBUG("Tx data:\r\n");
                NRF_LOG_HEXDUMP_DEBUG((uint8_t *)p_reg->TXD.PTR, evdata.data.tx_amount * sizeof(p_reg->TXD.PTR));
                nrf_drv_call_event_handler(instNr, &evdata);
                /* Go to idle and repeat the state machine if READ or WRITE events detected.
                 * This time READ or WRITE would be started */
                substate = NRF_DRV_TWIS_SUBSTATE_IDLE;
                ev = nrf_drv_twis_clear_bit(ev, NRF_TWIS_EVENT_STOPPED);
            }
            else
            {
                nrf_drv_twis_process_error(instNr, TWIS_EVT_READ_ERROR, nrf_twis_error_source_get_and_clear(p_reg));
                substate = NRF_DRV_TWIS_SUBSTATE_IDLE;
                ev = 0;
            }
            break;
        case NRF_DRV_TWIS_SUBSTATE_WRITE_WAITING:
            if (nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_RXSTARTED) ||
               nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_WRITE)     ||
               nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_READ)      ||
               nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_STOPPED))
            {
                substate = NRF_DRV_TWIS_SUBSTATE_WRITE_PENDING;
                /* Any other bits requires further processing in PENDING substate */
                ev = nrf_drv_twis_clear_bit(ev, NRF_TWIS_EVENT_RXSTARTED);
            }
            else
            {
                nrf_drv_twis_process_error(instNr, TWIS_EVT_WRITE_ERROR, nrf_twis_error_source_get_and_clear(p_reg));
                substate = NRF_DRV_TWIS_SUBSTATE_IDLE;
                ev = 0;
            }
            break;
        case NRF_DRV_TWIS_SUBSTATE_WRITE_PENDING:
            if (nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_WRITE)||
               nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_READ) ||
               nrf_drv_twis_check_bit(ev, NRF_TWIS_EVENT_STOPPED))
            {
                evdata.type = TWIS_EVT_WRITE_DONE;
                evdata.data.rx_amount = nrf_twis_rx_amount_get(p_reg);
                nrf_drv_call_event_handler(instNr, &evdata);
                /* Go to idle and repeat the state machine if READ or WRITE events detected.
                 * This time READ or WRITE would be started */
                substate = NRF_DRV_TWIS_SUBSTATE_IDLE;
                ev = nrf_drv_twis_clear_bit(ev, NRF_TWIS_EVENT_STOPPED);
            }
            else
            {
                nrf_drv_twis_process_error(instNr, TWIS_EVT_WRITE_ERROR, nrf_twis_error_source_get_and_clear(p_reg));
                substate = NRF_DRV_TWIS_SUBSTATE_IDLE;
                ev = 0;
            }
            break;
        default:
            substate = NRF_DRV_TWIS_SUBSTATE_IDLE;
            /* Do not clear any events and repeat the machine */
            break;
        }
    }

    m_var_inst[instNr].substate = substate;
    if (!TWIS_NO_SYNC_MODE)
    {
        m_sm_semaphore[instNr] = 0;
    }
}

/**
 * @brief This function
 */
static inline void nrf_drv_twis_preprocess_status(uint8_t instNr)
{
    if (!TWIS_NO_SYNC_MODE)
    {
        if (NULL == m_var_inst[instNr].ev_handler)
        {
            nrf_drv_twis_state_machine(instNr);
        }
    }
}

/**
 * @brief Interrupt service
 *
 * This function is called by all interrupts runtime for instances enabled in this library.
 * @param instNr Driver instance number that has called this runtime.
 */
static inline void nrf_drv_twis_on_ISR(uint8_t instNr)
{
    nrf_drv_twis_state_machine(instNr);
}

/** @} */ /* End  of lib_driver_twis_slave_ifunc */


/* -------------------------------------------------------------------------
 * Implementation of IRQ Handlers
 */
#define X(n) \
    IRQ_HANDLER(n) \
    { \
        nrf_drv_twis_on_ISR(TWIS##n##_INSTANCE_INDEX); \
    }
#include "nrf_drv_twis_inst.def"

/* -------------------------------------------------------------------------
 * Implementation of interface functions
 *
 */


ret_code_t nrf_drv_twis_init(
        nrf_drv_twis_t          const * const p_instance,
        nrf_drv_twis_config_t   const * p_config,
        nrf_drv_twis_event_handler_t    const event_handler)
{
    ASSERT(p_config);
    ASSERT(p_config->scl != p_config->sda);
    uint8_t instNr = p_instance->instNr;
    NRF_TWIS_Type * const p_reg = m_const_inst[instNr].p_reg;
    nrf_twis_config_addr_mask_t addr_mask = (nrf_twis_config_addr_mask_t)0;
    ret_code_t err_code;

    if ( m_var_inst[instNr].state != NRF_DRV_STATE_UNINITIALIZED)
    {
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    if (nrf_drv_common_per_res_acquire(p_reg, m_irq_handlers[instNr]) !=
            NRF_SUCCESS)
    {
        err_code = NRF_ERROR_BUSY;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
#endif

    if (!TWIS_ASSUME_INIT_AFTER_RESET_ONLY)
    {
        nrf_drv_twis_swreset(p_reg);
    }

    nrf_drv_twis_config_pin(p_config->scl, p_config->scl_pull);
    nrf_drv_twis_config_pin(p_config->sda, p_config->sda_pull);

    if (0 == (p_config->addr[0] | p_config->addr[1]))
        addr_mask = NRF_TWIS_CONFIG_ADDRESS0_MASK;
    else
    {
        if (0 != p_config->addr[0])
        {
            addr_mask |= NRF_TWIS_CONFIG_ADDRESS0_MASK;
        }
        if (0 != p_config->addr[1])
        {
            addr_mask |= NRF_TWIS_CONFIG_ADDRESS1_MASK;
        }
    }

    /* Peripheral interrupt configure
     * (note - interrupts still needs to be configured in INTEN register.
     * This is done in enable function) */
    nrf_drv_common_irq_enable(nrf_drv_get_IRQn(p_reg), p_config->interrupt_priority);

    /* Configure */
    nrf_twis_pins_set          (p_reg, p_config->scl, p_config->sda);
    nrf_twis_address_set       (p_reg, 0, p_config->addr[0]);
    nrf_twis_address_set       (p_reg, 1, p_config->addr[1]);
    nrf_twis_config_address_set(p_reg, addr_mask);

    /* Clear semaphore */
    if (!TWIS_NO_SYNC_MODE)
    {
        m_sm_semaphore[instNr] = 0;
    }
    /* Set internal instance variables */
    m_var_inst[instNr].substate   = NRF_DRV_TWIS_SUBSTATE_IDLE;
    m_var_inst[instNr].ev_handler = event_handler;
    m_var_inst[instNr].state      = NRF_DRV_STATE_INITIALIZED;
    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}


void nrf_drv_twis_uninit(nrf_drv_twis_t const * const p_instance)
{
    uint8_t instNr = p_instance->instNr;
    NRF_TWIS_Type * const p_reg = m_const_inst[instNr].p_reg;
    TWIS_PSEL_Type psel = p_reg->PSEL;

    ASSERT(m_var_inst[instNr].state != NRF_DRV_STATE_UNINITIALIZED);

    nrf_drv_twis_swreset(p_reg);

    /* Clear pins state if */
    if (!(TWIS_PSEL_SCL_CONNECT_Msk & psel.SCL))
    {
        nrf_gpio_cfg_default(psel.SCL);
    }
    if (!(TWIS_PSEL_SDA_CONNECT_Msk & psel.SDA))
    {
        nrf_gpio_cfg_default(psel.SDA);
    }

#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    nrf_drv_common_per_res_release(p_reg);
#endif

    /* Clear variables */
    m_var_inst[instNr].ev_handler = NULL;
    m_var_inst[instNr].state      = NRF_DRV_STATE_UNINITIALIZED;
}


void nrf_drv_twis_enable(nrf_drv_twis_t const * const p_instance)
{
    uint8_t instNr = p_instance->instNr;
    NRF_TWIS_Type * const p_reg = m_const_inst[instNr].p_reg;
    nrf_drv_twis_var_inst_t * const p_var_inst = &m_var_inst[instNr];

    ASSERT(m_var_inst[instNr].state == NRF_DRV_STATE_INITIALIZED);

    nrf_drv_twis_clear_all_events(p_reg);

    /* Enable interrupts */
    if (NULL != p_var_inst->ev_handler)
    {
        nrf_twis_int_enable(p_reg, m_used_ints_mask);
    }

    nrf_twis_enable(p_reg);
    p_var_inst->error    = 0;
    p_var_inst->state    = NRF_DRV_STATE_POWERED_ON;
    p_var_inst->substate = NRF_DRV_TWIS_SUBSTATE_IDLE;
}


void nrf_drv_twis_disable(nrf_drv_twis_t const * const p_instance)
{
    uint8_t instNr = p_instance->instNr;
    NRF_TWIS_Type * const p_reg = m_const_inst[instNr].p_reg;

    ASSERT(m_var_inst[instNr].state != NRF_DRV_STATE_UNINITIALIZED);

    nrf_twis_int_disable(p_reg, m_used_ints_mask);

    nrf_twis_disable(p_reg);
    m_var_inst[instNr].state    = NRF_DRV_STATE_INITIALIZED;
}

/* ARM recommends not using the LDREX and STREX instructions in C code.
 * This is because the compiler might generate loads and stores between
 * LDREX and STREX, potentially clearing the exclusive monitor set by LDREX.
 * This recommendation also applies to the byte, halfword, and doubleword
 * variants LDREXB, STREXB, LDREXH, STREXH, LDREXD, and STREXD.
 *
 * This is the reason for the function below to be implemented in assembly.
 */
//lint -save -e578
#if defined (__CC_ARM )
static __ASM uint32_t nrf_drv_twis_error_get_and_clear_internal(uint32_t volatile * const perror)
{
    mov   r3, r0
    mov   r1, #0
nrf_drv_twis_error_get_and_clear_internal_try
    ldrex r0, [r3]
    strex r2, r1, [r3]
    cmp   r2, r1                                        /* did this succeed?       */
    bne   nrf_drv_twis_error_get_and_clear_internal_try /* no – try again          */
    bx    lr
}
#elif defined ( __GNUC__ )
static uint32_t nrf_drv_twis_error_get_and_clear_internal(uint32_t volatile * const perror)
{
    uint32_t ret;
    uint32_t temp;
    __ASM volatile(
        "   .syntax unified           \n"
        "nrf_drv_twis_error_get_and_clear_internal_try:         \n"
        "   ldrex %[ret], [%[perror]]                           \n"
        "   strex %[temp], %[zero], [%[perror]]                 \n"
        "   cmp   %[temp], %[zero]                              \n"
        "   bne   nrf_drv_twis_error_get_and_clear_internal_try \n"
    : /* Output */
        [ret]"=&l"(ret),
        [temp]"=&l"(temp)
    : /* Input */
        [zero]"l"(0),
        [perror]"l"(perror)
    );
    UNUSED_VARIABLE(temp);
    return ret;
}
#elif defined ( __ICCARM__ )
static uint32_t nrf_drv_twis_error_get_and_clear_internal(uint32_t volatile * const perror)
{
    uint32_t ret;
    uint32_t temp;
    __ASM volatile(
        "1:         \n"
        "   ldrex %[ret], [%[perror]]                           \n"
        "   strex %[temp], %[zero], [%[perror]]                 \n"
        "   cmp   %[temp], %[zero]                              \n"
        "   bne.n 1b \n"
    : /* Output */
        [ret]"=&l"(ret),
        [temp]"=&l"(temp)
    : /* Input */
        [zero]"l"(0),
        [perror]"l"(perror)
    );
    UNUSED_VARIABLE(temp);
    return ret;
}
#else
    #error Unknown compiler
#endif
//lint -restore

uint32_t nrf_drv_twis_error_get_and_clear(nrf_drv_twis_t const * const p_instance)
{
    nrf_drv_twis_var_inst_t * const p_var_inst = &m_var_inst[p_instance->instNr];
    nrf_drv_twis_preprocess_status(p_instance->instNr);
    /* Make sure that access to error member is atomic
     * so there is no bit that is cleared if it is not copied to local variable already. */
    return nrf_drv_twis_error_get_and_clear_internal(&p_var_inst->error);
}


ret_code_t nrf_drv_twis_tx_prepare(
        nrf_drv_twis_t const * const p_instance,
        void const * const p_buf,
        size_t size)
{
    ret_code_t err_code = NRF_SUCCESS;
    uint8_t instNr = p_instance->instNr;
    NRF_TWIS_Type * const p_reg = m_const_inst[instNr].p_reg;
    nrf_drv_twis_var_inst_t * const p_var_inst = &m_var_inst[instNr];

    /* Check power state*/
    if (p_var_inst->state != NRF_DRV_STATE_POWERED_ON)
    {
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    /* Check data address */
    if (!nrf_drv_is_in_RAM(p_buf))
    {
        err_code = NRF_ERROR_INVALID_ADDR;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    /* Check data size */
    if ((size & TWIS_TXD_MAXCNT_MAXCNT_Msk) != size)
    {
        err_code = NRF_ERROR_INVALID_LENGTH;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    nrf_twis_tx_prepare(p_reg, (uint8_t const *)p_buf, (nrf_twis_amount_t)size);
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;

}


size_t nrf_drv_twis_tx_amount(nrf_drv_twis_t const * const p_instance)
{
    uint8_t instNr = p_instance->instNr;
    NRF_TWIS_Type const * const p_reg = m_const_inst[instNr].p_reg;

    return nrf_twis_tx_amount_get(p_reg);
}


ret_code_t nrf_drv_twis_rx_prepare(
        nrf_drv_twis_t const * const p_instance,
        void * const p_buf,
        size_t size)
{
    ret_code_t err_code;
    uint8_t instNr = p_instance->instNr;
    NRF_TWIS_Type * const p_reg = m_const_inst[instNr].p_reg;
    nrf_drv_twis_var_inst_t * const p_var_inst = &m_var_inst[instNr];

    /* Check power state*/
    if (p_var_inst->state != NRF_DRV_STATE_POWERED_ON)
    {
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    /* Check data address */
    if (!nrf_drv_is_in_RAM(p_buf))
    {
        err_code = NRF_ERROR_INVALID_ADDR;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    /* Check data size */
    if ((size & TWIS_RXD_MAXCNT_MAXCNT_Msk) != size)
    {
        err_code = NRF_ERROR_INVALID_LENGTH;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    nrf_twis_rx_prepare(p_reg, (uint8_t *)p_buf, (nrf_twis_amount_t)size);
    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}


size_t nrf_drv_twis_rx_amount(nrf_drv_twis_t const * const p_instance)
{
    uint8_t instNr = p_instance->instNr;
    NRF_TWIS_Type const * const p_reg = m_const_inst[instNr].p_reg;

    return nrf_twis_rx_amount_get(p_reg);
}


bool nrf_drv_twis_is_busy(nrf_drv_twis_t const * const p_instance)
{
    nrf_drv_twis_preprocess_status(p_instance->instNr);
    return NRF_DRV_TWIS_SUBSTATE_IDLE != m_var_inst[(p_instance->instNr)].substate;
}

bool nrf_drv_twis_is_waiting_tx_buff(nrf_drv_twis_t const * const p_instance)
{
    nrf_drv_twis_preprocess_status(p_instance->instNr);
    return NRF_DRV_TWIS_SUBSTATE_READ_WAITING == m_var_inst[(p_instance->instNr)].substate;
}

bool nrf_drv_twis_is_waiting_rx_buff(nrf_drv_twis_t const * const p_instance)
{
    nrf_drv_twis_preprocess_status(p_instance->instNr);
    return NRF_DRV_TWIS_SUBSTATE_WRITE_WAITING == m_var_inst[(p_instance->instNr)].substate;
}

bool nrf_drv_twis_is_pending_tx(nrf_drv_twis_t const * const p_instance)
{
    nrf_drv_twis_preprocess_status(p_instance->instNr);
    return NRF_DRV_TWIS_SUBSTATE_READ_PENDING == m_var_inst[(p_instance->instNr)].substate;
}

bool nrf_drv_twis_is_pending_rx(nrf_drv_twis_t const * const p_instance)
{
    nrf_drv_twis_preprocess_status(p_instance->instNr);
    return NRF_DRV_TWIS_SUBSTATE_WRITE_PENDING == m_var_inst[(p_instance->instNr)].substate;
}
#endif // TWIS_COUNT
#endif // NRF_MODULE_ENABLED(TWIS)
