/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_IRQ_H_
#define _HARDWARE_IRQ_H_

// These two config items are also used by assembler, so keeping separate
// PICO_CONFIG: PICO_MAX_SHARED_IRQ_HANDLERS, Maximum Number of shared IRQ handers, default=4, advanced=true, group=hardware_irq
#ifndef PICO_MAX_SHARED_IRQ_HANDLERS
#define PICO_MAX_SHARED_IRQ_HANDLERS 4u
#endif

// PICO_CONFIG: PICO_DISABLE_SHARED_IRQ_HANDLERS, Disable shared IRQ handers, type=bool, default=0, group=hardware_irq
#ifndef PICO_DISABLE_SHARED_IRQ_HANDLERS
#define PICO_DISABLE_SHARED_IRQ_HANDLERS 0
#endif

#ifndef __ASSEMBLER__

#include "pico.h"
#include "hardware/regs/intctrl.h"
#include "hardware/regs/m0plus.h"

/** \file irq.h
 *  \defgroup hardware_irq hardware_irq
 *
 * Hardware interrupt handling
 *
 * The RP2040 uses the standard ARM nested vectored interrupt controller (NVIC).
 *
 * Interrupts are identified by a number from 0 to 31.
 *
 * On the RP2040, only the lower 26 IRQ signals are connected on the NVIC; IRQs 26 to 31 are tied to zero (never firing).
 *
 * There is one NVIC per core, and each core's NVIC has the same hardware interrupt lines routed to it, with the exception of the IO interrupts
 * where there is one IO interrupt per bank, per core. These are completely independent, so for example, processor 0 can be
 * interrupted by GPIO 0 in bank 0, and processor 1 by GPIO 1 in the same bank.
 *
 * \note That all IRQ APIs affect the executing core only (i.e. the core calling the function).
 *
 * \note You should not enable the same (shared) IRQ number on both cores, as this will lead to race conditions
 * or starvation of one of the cores. Additionally don't forget that disabling interrupts on one core does not disable interrupts
 * on the other core.
 *
 * There are three different ways to set handlers for an IRQ:
 *  - Calling irq_add_shared_handler() at runtime to add a handler for a multiplexed interrupt (e.g. GPIO bank) on the current core. Each handler, should check and clear the relevant hardware interrupt source
 *  - Calling irq_set_exclusive_handler() at runtime to install a single handler for the interrupt on the current core
 *  - Defining the interrupt handler explicitly in your application (e.g. by defining void `isr_dma_0` will make that function the handler for the DMA_IRQ_0 on core 0, and
 *    you will not be able to change it using the above APIs at runtime). Using this method can cause link conflicts at runtime, and offers no runtime performance benefit (i.e, it should not generally be used).
 *
 * \note If an IRQ is enabled and fires with no handler installed, a breakpoint will be hit and the IRQ number will
 * be in r0.
 *
 * \section interrupt_nums Interrupt Numbers
 *
 * Interrupts are numbered as follows, a set of defines is available (intctrl.h) with these names to avoid using the numbers directly.
 *
 * IRQ | Interrupt Source
 * ----|-----------------
 *  0 | TIMER_IRQ_0
 *  1 | TIMER_IRQ_1
 *  2 | TIMER_IRQ_2
 *  3 | TIMER_IRQ_3
 *  4 | PWM_IRQ_WRAP
 *  5 | USBCTRL_IRQ
 *  6 | XIP_IRQ
 *  7 | PIO0_IRQ_0
 *  8 | PIO0_IRQ_1
 *  9 | PIO1_IRQ_0
 * 10 | PIO1_IRQ_1
 * 11 | DMA_IRQ_0
 * 12 | DMA_IRQ_1
 * 13 | IO_IRQ_BANK0
 * 14 | IO_IRQ_QSPI
 * 15 | SIO_IRQ_PROC0
 * 16 | SIO_IRQ_PROC1
 * 17 | CLOCKS_IRQ
 * 18 | SPI0_IRQ
 * 19 | SPI1_IRQ
 * 20 | UART0_IRQ
 * 21 | UART1_IRQ
 * 22 | ADC0_IRQ_FIFO
 * 23 | I2C0_IRQ
 * 24 | I2C1_IRQ
 * 25 | RTC_IRQ
 *
 */

// PICO_CONFIG: PICO_DEFAULT_IRQ_PRIORITY, Define the default IRQ priority, default=0x80, group=hardware_irq
#ifndef PICO_DEFAULT_IRQ_PRIORITY
#define PICO_DEFAULT_IRQ_PRIORITY 0x80
#endif

#define PICO_LOWEST_IRQ_PRIORITY 0x01
#define PICO_HIGHEST_IRQ_PRIORITY 0xff

// PICO_CONFIG: PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY, Set default shared IRQ order priority, default=0x80, group=hardware_irq
#ifndef PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY
#define PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY 0x80
#endif

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_IRQ, Enable/disable assertions in the IRQ module, type=bool, default=0, group=hardware_irq
#ifndef PARAM_ASSERTIONS_ENABLED_IRQ
#define PARAM_ASSERTIONS_ENABLED_IRQ 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Interrupt handler function type
 *  \ingroup hardware_irq
 *
 * All interrupts handlers should be of this type, and follow normal ARM EABI register saving conventions
 */
typedef void (*irq_handler_t)();

/*! \brief Set specified interrupts priority
 *  \ingroup hardware_irq
 *
 * \param num Interrupt number
 * \param hardware_priority Priority to set. Hardware priorities range from 0 (lowest) to 255 (highest) though only
 * the top 2 bits are significant on ARM Cortex M0+. To make it easier to specify higher or lower priorities
 * than the default, all IRQ priorities are initialized to PICO_DEFAULT_IRQ_PRIORITY by the SDK runtime at startup.
 * PICO_DEFAULT_IRQ_PRIORITY defaults to 0x80
 */
void irq_set_priority(uint num, uint8_t hardware_priority);

/*! \brief Enable or disable a specific interrupt on the executing core
 *  \ingroup hardware_irq
 *
 * \param num Interrupt number \ref interrupt_nums
 * \param enabled true to enable the interrupt, false to disable
 */
void irq_set_enabled(uint num, bool enabled);

/*! \brief Determine if a specific interrupt is enabled on the executing core
 *  \ingroup hardware_irq
 *
 * \param num Interrupt number \ref interrupt_nums
 * \return true if the interrupt is enabled
 */
bool irq_is_enabled(uint num);

/*! \brief Enable/disable multiple interrupts on the executing core
 *  \ingroup hardware_irq
 *
 * \param mask 32-bit mask with one bits set for the interrupts to enable/disable
 * \param enabled true to enable the interrupts, false to disable them.
 */
void irq_set_mask_enabled(uint32_t mask, bool enabled);

/*! \brief  Set an exclusive interrupt handler for an interrupt on the executing core.
 *  \ingroup hardware_irq
 *
 * Use this method to set a handler for single IRQ source interrupts, or when
 * your code, use case or performance requirements dictate that there should
 * no other handlers for the interrupt.
 *
 * This method will assert if there is already any sort of interrupt handler installed
 * for the specified irq number.
 *
 * \param num Interrupt number \ref interrupt_nums
 * \param handler The handler to set. See \ref irq_handler_t
 * \see irq_add_shared_handler
 */
void irq_set_exclusive_handler(uint num, irq_handler_t handler);

/*! \brief  Get the exclusive interrupt handler for an interrupt on the executing core.
 *  \ingroup hardware_irq
 *
 * This method will return an exclusive IRQ handler set on this core
 * by irq_set_exclusive_handler if there is one.
 *
 * \param num Interrupt number \ref interrupt_nums
 * \see irq_set_exclusive_handler
 * \return handler The handler if an exclusive handler is set for the IRQ,
 *                 NULL if no handler is set or shared/shareable handlers are installed
 */
irq_handler_t irq_get_exclusive_handler(uint num);

/*! \brief Add a shared interrupt handler for an interrupt on the executing core
 *  \ingroup hardware_irq
 *
 * Use this method to add a handler on an irq number shared between multiple distinct hardware sources (e.g. GPIO, DMA or PIO IRQs).
 * Handlers added by this method will all be called in sequence from highest order_priority to lowest. The
 * irq_set_exclusive_handler() method should be used instead if you know there will or should only ever be one handler for the interrupt.
 *
 * This method will assert if there is an exclusive interrupt handler set for this irq number on this core, or if
 * the (total across all IRQs on both cores) maximum (configurable via PICO_MAX_SHARED_IRQ_HANDLERS) number of shared handlers
 * would be exceeded.
 *
 * \param num Interrupt number
 * \param handler The handler to set. See \ref irq_handler_t
 * \param order_priority The order priority controls the order that handlers for the same IRQ number on the core are called.
 * The shared irq handlers for an interrupt are all called when an IRQ fires, however the order of the calls is based
 * on the order_priority (higher priorities are called first, identical priorities are called in undefined order). A good
 * rule of thumb is to use PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY if you don't much care, as it is in the middle of
 * the priority range by default.
 *
 * \see irq_set_exclusive_handler
 */
void irq_add_shared_handler(uint num, irq_handler_t handler, uint8_t order_priority);

/*! \brief Remove a specific interrupt handler for the given irq number on the executing core
 *  \ingroup hardware_irq
 *
 * This method may be used to remove an irq set via either irq_set_exclusive_handler() or
 * irq_add_shared_handler(), and will assert if the handler is not currently installed for the given
 * IRQ number
 *
 * \note This method may *only* be called from user (non IRQ code) or from within the handler
 * itself (i.e. an IRQ handler may remove itself as part of handling the IRQ). Attempts to call
 * from another IRQ will cause an assertion.
 *
 * \param num Interrupt number \ref interrupt_nums
 * \param handler The handler to removed.
 * \see irq_set_exclusive_handler
 * \see irq_add_shared_handler
 */
void irq_remove_handler(uint num, irq_handler_t handler);

/*! \brief Get the current IRQ handler for the specified IRQ from the currently installed hardware vector table (VTOR)
 * of the execution core
 *  \ingroup hardware_irq
 *
 * \param num Interrupt number \ref interrupt_nums
 * \return the address stored in the VTABLE for the given irq number
 */
irq_handler_t irq_get_vtable_handler(uint num);

/*! \brief Clear a specific interrupt on the executing core
 *  \ingroup hardware_irq
 *
 * \param int_num Interrupt number \ref interrupt_nums
 */
static inline void irq_clear(uint int_num) {
    *((volatile uint32_t *) (PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET)) = (1u << ((uint32_t) (int_num & 0x1F)));
}

/*! \brief Force an interrupt to pending on the executing core
 *  \ingroup hardware_irq
 *
 * This should generally not be used for IRQs connected to hardware.
 *
 * \param num Interrupt number \ref interrupt_nums
 */
void irq_set_pending(uint num);


/*! \brief Perform IRQ priority intiialization for the current core
 *
 * \note This is an internal method and user should generally not call it.
 */
void irq_init_priorities();
#ifdef __cplusplus
}
#endif

#endif
#endif
