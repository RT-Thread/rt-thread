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
#ifndef NRF_DRV_COMMON_H__
#define NRF_DRV_COMMON_H__

#include <stdint.h>
#include <stdbool.h>
#include "nrf.h"
#include "sdk_errors.h"
#include "sdk_common.h"
#include "nrf_assert.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NRF51
#ifdef SOFTDEVICE_PRESENT
#define INTERRUPT_PRIORITY_IS_VALID(pri) (((pri) == 1) || ((pri) == 3))
#else
#define INTERRUPT_PRIORITY_IS_VALID(pri) ((pri) < 4)
#endif //SOFTDEVICE_PRESENT
#else
#ifdef SOFTDEVICE_PRESENT
#define INTERRUPT_PRIORITY_IS_VALID(pri) ((((pri) > 1) && ((pri) < 4)) || (((pri) > 5) && ((pri) < 8)))
#else
#define INTERRUPT_PRIORITY_IS_VALID(pri) ((pri) < 8)
#endif //SOFTDEVICE_PRESENT
#endif //NRF52

#define INTERRUPT_PRIORITY_VALIDATION(pri) STATIC_ASSERT(INTERRUPT_PRIORITY_IS_VALID((pri)))
#define INTERRUPT_PRIORITY_ASSERT(pri)     ASSERT(INTERRUPT_PRIORITY_IS_VALID((pri)))

/**
 * @defgroup nrf_drv_common Peripheral drivers common module
 * @{
 * @ingroup nrf_drivers
 */

/**
 * @brief Offset of event registers in every peripheral instance.
 *
 * This is the offset where event registers start in  every peripheral.
 */
#define NRF_DRV_COMMON_EVREGS_OFFSET 0x100U

/**
 * @brief The flag that is set when POWER_CLOCK ISR is implemented in common module
 *
 * This flag means that the function POWER_CLOCK_IRQHandler is implemented in
 * nrf_drv_common.c file. In the @c clock and @c power modules functions
 * nrf_drv_clock_onIRQ nrf_drv_power_onIRQ should be implemented
 * and they would be called from common implementation.
 *
 * None of the checking is done here.
 * The implementation functions in @c clock and @c power are required to handle
 * correctly the case when they are called without any event bit set.
 */
#define NRF_DRV_COMMON_POWER_CLOCK_ISR (NRF_MODULE_ENABLED(CLOCK) && NRF_MODULE_ENABLED(POWER))

/**
 * @brief Driver state.
 */
typedef enum
{
    NRF_DRV_STATE_UNINITIALIZED, /**< Uninitialized. */
    NRF_DRV_STATE_INITIALIZED, /**< Initialized but powered off. */
    NRF_DRV_STATE_POWERED_ON
} nrf_drv_state_t;

/**
 * @brief Driver power state selection.
 */
typedef enum
{
    NRF_DRV_PWR_CTRL_ON,   /**< Power on request. */
    NRF_DRV_PWR_CTRL_OFF   /**< Power off request. */
} nrf_drv_pwr_ctrl_t;

/**
 * @brief IRQ handler type.
 */
typedef void (*nrf_drv_irq_handler_t)(void);


#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)

/**
 * @brief Function for acquiring shared peripheral resources associated with
 *        the specified peripheral.
 *
 * Certain resources and registers are shared among peripherals that have
 * the same ID (for example: SPI0, SPIM0, SPIS0, TWI0, TWIM0, and TWIS0).
 * Only one of them can be utilized at a given time. This function reserves
 * proper resources to be used by the specified peripheral.
 * If PERIPHERAL_RESOURCE_SHARING_ENABLED is set to a non-zero value, IRQ
 * handlers for peripherals that are sharing resources with others are
 * implemented by the nrf_drv_common module instead of individual drivers.
 * The drivers must then specify their interrupt handling routines and
 * register them by using this function.
 *
 * @param[in] p_per_base Requested peripheral base pointer.
 * @param[in] handler    Interrupt handler to register. May be NULL
 *                       if interrupts are not used for the peripheral.
 *
 * @retval NRF_SUCCESS             If resources were acquired successfully.
 * @retval NRF_ERROR_BUSY          If resources were already acquired.
 * @retval NRF_ERROR_INVALID_PARAM If the specified peripheral is not enabled
 *                                 or the peripheral does not share resources
 *                                 with other peripherals.
 */
ret_code_t nrf_drv_common_per_res_acquire(void const * p_per_base,
                                          nrf_drv_irq_handler_t handler);

/**
 * @brief Function for releasing shared resources reserved previously by
 *        @ref nrf_drv_common_per_res_acquire() for the specified peripheral.
 *
 * @param[in] p_per_base Requested peripheral base pointer.
 */
void nrf_drv_common_per_res_release(void const * p_per_base);

#endif // NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)


/**
 * @brief Function sets priority and enables NVIC interrupt
 *
 * @note Function checks if correct priority is used when softdevice is present
 *
 * @param[in] IRQn     Interrupt id
 * @param[in] priority Interrupt priority
 */
void nrf_drv_common_irq_enable(IRQn_Type IRQn, uint8_t priority);

#if NRF_MODULE_ENABLED(POWER)
/**
 * @brief Disable power IRQ
 *
 * Power and clock peripheral uses the same IRQ.
 * This function disables POWER_CLOCK IRQ only if CLOCK driver
 * is uninitialized.
 *
 * @sa nrf_drv_common_power_clock_irq_init
 */
void nrf_drv_common_power_irq_disable(void);
#endif

#if NRF_MODULE_ENABLED(CLOCK)
/**
 * @brief Disable clock IRQ
 *
 * Power and clock peripheral uses the same IRQ.
 * This function disables POWER_CLOCK IRQ only if POWER driver
 * is uninitialized.
 *
 * @sa nrf_drv_common_power_clock_irq_init
 */
void nrf_drv_common_clock_irq_disable(void);
#endif

/**
 * @brief Check if interrupt is enabled
 *
 * Function that checks if selected interrupt is enabled.
 *
 * @param[in] IRQn     Interrupt id
 *
 * @retval true  Selected IRQ is enabled.
 * @retval false Selected IRQ is disabled.
 */
__STATIC_INLINE bool nrf_drv_common_irq_enable_check(IRQn_Type IRQn);

/**
 * @brief Function disables NVIC interrupt
 *
 * @param[in] IRQn     Interrupt id
 */
__STATIC_INLINE void nrf_drv_common_irq_disable(IRQn_Type IRQn);

/**
 * @brief Convert bit position to event code
 *
 * Function for converting the bit position in INTEN register to event code
 * that is equivalent to the offset of the event register from the beginning
 * of peripheral instance.
 *
 * For example the result of this function can be casted directly to
 * the types like @ref nrf_twis_event_t or @ref nrf_rng_event_t
 *
 * @param bit Bit position in INTEN register
 * @return Event code to be casted to the right enum type or to be used in functions like
 * @ref nrf_rng_event_get
 *
 * @sa nrf_drv_event_to_bitpos
 */
__STATIC_INLINE uint32_t nrf_drv_bitpos_to_event(uint32_t bit);

/**
 * @brief Convert event code to bit position
 *
 * This function can be used to get bit position in INTEN register from event code.
 *
 * @param event Event code that may be casted from enum values from types like
 * @ref nrf_twis_event_t or @ref nrf_rng_event_t
 * @return Bit position in INTEN register that corresponds to the given code.
 *
 * @sa nrf_drv_bitpos_to_event
 */
__STATIC_INLINE uint32_t nrf_drv_event_to_bitpos(uint32_t event);

/**
 * @brief Get interrupt number connected with given instance
 *
 * Function returns interrupt number for a given instance of any peripheral.
 * @param[in] pinst Pointer to peripheral registry
 * @return Interrupt number
 */
__STATIC_INLINE IRQn_Type nrf_drv_get_IRQn(void const * const pinst);

#if NRF_MODULE_ENABLED(CLOCK) || NRF_MODULE_ENABLED(POWER)
/**
 * @brief Enable and setup power clock IRQ
 *
 * This function would be called from @ref nrf_drv_clock and @ref nrf_drv_power
 * to enable related interrupt.
 * This function avoids multiple interrupt configuration.
 *
 * @note
 * This function is aviable only if @ref nrf_drv_clock or @ref nrf_drv_power
 * module is enabled.
 *
 * @note
 * If both @ref nrf_drv_clock and @ref nrf_drv_power modules are enabled,
 * during the compilation the check is made that
 * @ref CLOCK_CONFIG_IRQ_PRIORITY equals @ref POWER_CONFIG_IRQ_PRIORITY.
 *
 * @sa nrf_drv_common_power_irq_disable
 * @sa nrf_drv_common_clock_irq_disable
 */
__STATIC_INLINE void nrf_drv_common_power_clock_irq_init(void);
#endif

/**
 * @brief Check if given object is in RAM
 *
 * Function for analyzing if given location is placed in RAM.
 * This function is used to determine if we have address that can be supported by EasyDMA.
 * @param[in] ptr Pointer to the object
 * @retval true  Object is located in RAM
 * @retval false Object is not located in RAM
 */
__STATIC_INLINE bool nrf_drv_is_in_RAM(void const * const ptr);

#ifndef SUPPRESS_INLINE_IMPLEMENTATION

__STATIC_INLINE bool nrf_drv_common_irq_enable_check(IRQn_Type IRQn)
{
    return 0 != (NVIC->ISER[(((uint32_t)(int32_t)IRQn) >> 5UL)] &
        (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL)));
}

__STATIC_INLINE void nrf_drv_common_irq_disable(IRQn_Type IRQn)
{
    NVIC_DisableIRQ(IRQn);
}

__STATIC_INLINE uint32_t nrf_drv_bitpos_to_event(uint32_t bit)
{
    return NRF_DRV_COMMON_EVREGS_OFFSET + bit * sizeof(uint32_t);
}

__STATIC_INLINE uint32_t nrf_drv_event_to_bitpos(uint32_t event)
{
    return (event - NRF_DRV_COMMON_EVREGS_OFFSET) / sizeof(uint32_t);
}

__STATIC_INLINE IRQn_Type nrf_drv_get_IRQn(void const * const pinst)
{
    uint8_t ret = (uint8_t)((uint32_t)pinst>>12U);
    return (IRQn_Type) ret;
}

#if NRF_MODULE_ENABLED(CLOCK) || NRF_MODULE_ENABLED(POWER)
__STATIC_INLINE void nrf_drv_common_power_clock_irq_init(void)
{
    if(!nrf_drv_common_irq_enable_check(POWER_CLOCK_IRQn))
    {
        nrf_drv_common_irq_enable(
            POWER_CLOCK_IRQn,
#if NRF_DRV_COMMON_POWER_CLOCK_ISR
    #if CLOCK_CONFIG_IRQ_PRIORITY != POWER_CONFIG_IRQ_PRIORITY
    #error CLOCK_CONFIG_IRQ_PRIORITY and POWER_CONFIG_IRQ_PRIORITY have to be the same.
    #endif
            CLOCK_CONFIG_IRQ_PRIORITY
#elif NRF_MODULE_ENABLED(CLOCK)
            CLOCK_CONFIG_IRQ_PRIORITY
#elif NRF_MODULE_ENABLED(POWER)
            POWER_CONFIG_IRQ_PRIORITY
#endif
            );
    }
}
#endif

__STATIC_INLINE bool nrf_drv_is_in_RAM(void const * const ptr)
{
    return ((((uintptr_t)ptr) & 0xE0000000u) == 0x20000000u);
}

#endif // SUPPRESS_INLINE_IMPLEMENTATION


#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_COMMON_H__

/** @} */
