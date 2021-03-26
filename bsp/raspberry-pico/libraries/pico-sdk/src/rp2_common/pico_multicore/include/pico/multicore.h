/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_MULTICORE_H
#define _PICO_MULTICORE_H

#include "pico/types.h"
#include "pico/sync.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file multicore.h
 *  \defgroup pico_multicore pico_multicore
 * Adds support for running code on the second processor core (core1)
 *
 * \subsection multicore_example Example
 * \addtogroup pico_multicore
 * \include multicore.c
*/

// PICO_CONFIG: PICO_CORE1_STACK_SIZE, Stack size for core 1, min=0x100, max=0x10000, default=PICO_STACK_SIZE/0x800, group=pico_multicore
#ifndef PICO_CORE1_STACK_SIZE
#ifdef PICO_STACK_SIZE
#define PICO_CORE1_STACK_SIZE PICO_STACK_SIZE
#else
#define PICO_CORE1_STACK_SIZE 0x800
#endif
#endif

/*! \brief  Reset Core 1
 *  \ingroup pico_multicore
 *
 */
void multicore_reset_core1();

/*! \brief  Run code on core 1
 *  \ingroup pico_multicore
 *
 * Reset core1 and enter the given function on core 1 using the default core 1 stack (below core 0 stack)
 *
 * \param entry Function entry point, this function should not return.
 */
void multicore_launch_core1(void (*entry)(void));

/*! \brief  Launch code on core 1 with stack
 *  \ingroup pico_multicore
 *
 * Reset core1 and enter the given function on core 1 using the passed stack for core 1
 */
void multicore_launch_core1_with_stack(void (*entry)(void), uint32_t *stack_bottom, size_t stack_size_bytes);

/*! \brief  Send core 1 to sleep.
 *  \ingroup pico_multicore
 *
 */
void multicore_sleep_core1();

/*! \brief  Launch code on core 1 with no stack protection
 *  \ingroup pico_multicore
 *
 * Reset core1 and enter the given function using the passed sp as the initial stack pointer.
 * This is a bare bones functions that does not provide a stack guard even if USE_STACK_GUARDS is defined
 *
 */
void multicore_launch_core1_raw(void (*entry)(void), uint32_t *sp, uint32_t vector_table);

/*!
 * \defgroup multicore_fifo fifo
 * \ingroup pico_multicore
 * \brief Functions for inter-core FIFO
 *
 * The RP2040 contains two FIFOs for passing data, messages or ordered events between the two cores. Each FIFO is 32 bits
 * wide, and 8 entries deep. One of the FIFOs can only be written by core 0, and read by core 1. The other can only be written
 * by core 1, and read by core 0.
 */


/*! \brief Check the read FIFO to see if there is data waiting
 *  \ingroup multicore_fifo
 *
 * \return true if the FIFO has data in it, false otherwise
 */
static inline bool multicore_fifo_rvalid() {
    return !!(sio_hw->fifo_st & SIO_FIFO_ST_VLD_BITS);
}

/*! \brief Check the FIFO to see if the write FIFO is full
 *  \ingroup multicore_fifo
 *
 *  @return true if the FIFO is full, false otherwise
 */
static inline bool multicore_fifo_wready() {
    return !!(sio_hw->fifo_st & SIO_FIFO_ST_RDY_BITS);
}

/*! \brief Push data on to the FIFO.
 *  \ingroup multicore_fifo
 *
 * This function will block until there is space for the data to be sent.
 * Use multicore_fifo_wready() to check if it is possible to write to the
 * FIFO if you don't want to block.
 *
 * \param data A 32 bit value to push on to the FIFO
 */
void multicore_fifo_push_blocking(uint32_t data);

bool multicore_fifo_push_timeout_us(uint32_t data, uint64_t timeout_us);

/*! \brief Pop data from the FIFO.
 *  \ingroup multicore_fifo
 *
 * This function will block until there is data ready to be read
 * Use multicore_fifo_rvalid() to check if data is ready to be read if you don't
 * want to block.
 *
 * \return 32 bit unsigned data from the FIFO.
 */
uint32_t multicore_fifo_pop_blocking();

bool multicore_fifo_pop_timeout_us(uint64_t timeout_us, uint32_t *out);

/*! \brief Flush any data in the outgoing FIFO
 *  \ingroup multicore_fifo
 *
 */
static inline void multicore_fifo_drain() {
    while (multicore_fifo_rvalid())
        (void) sio_hw->fifo_rd;
}

/*! \brief Clear FIFO interrupt
 *  \ingroup multicore_fifo
*/
static inline void multicore_fifo_clear_irq() {
    // Write any value to clear any interrupts
    sio_hw->fifo_st = 0xff;
}

/*! \brief Get FIFO status
 *  \ingroup multicore_fifo
 *
 * \return The status as a bitfield
 *
 * Bit | Description
 * ----|------------
 * 3 | Sticky flag indicating the RX FIFO was read when empty. This read was ignored by the FIFO.
 * 2 | Sticky flag indicating the TX FIFO was written when full. This write was ignored by the FIFO.
 * 1 | Value is 1 if this core’s TX FIFO is not full (i.e. if FIFO_WR is ready for more data)
 * 0 | Value is 1 if this core’s RX FIFO is not empty (i.e. if FIFO_RD is valid)
*/
static inline int32_t multicore_fifo_get_status() {
    return sio_hw->fifo_st;
}

// call this from the lockout victim thread
void multicore_lockout_victim_init();

// start locking out the other core (it will be
bool multicore_lockout_start_timeout_us(uint64_t timeout_us);
void multicore_lockout_start_blocking();

bool multicore_lockout_end_timeout_us(uint64_t timeout_us);
void multicore_lockout_end_blocking();

#ifdef __cplusplus
}
#endif
#endif
