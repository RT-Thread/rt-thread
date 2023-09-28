/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_DIVIDER_H
#define _HARDWARE_DIVIDER_H

#include "pico.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t divmod_result_t;

static inline int __sign_of(int32_t v) {
    return v > 0 ? 1 : (v < 0 ? -1 : 0);
}

/*! \brief Do an unsigned HW divide and wait for result
 *  \ingroup hardware_divider
 *
 * Divide \p a by \p b, wait for calculation to complete, return result as a pair of 32-bit quotient/remainder values.
 *
 * \param a The dividend
 * \param b The divisor
 * \return Results of divide as a pair of 32-bit quotient/remainder values.
 */
static inline divmod_result_t hw_divider_divmod_u32(uint32_t a, uint32_t b)  {
    if (!b) return (((uint64_t)a)<<32u) | (uint32_t)(-1); // todo check this
    return (((uint64_t)(a%b))<<32u) | (a/b);
}

/*! \brief Do a signed HW divide and wait for result
 *  \ingroup hardware_divider
 *
 * Divide \p a by \p b, wait for calculation to complete, return result as a pair of 32-bit quotient/remainder values.
 *
 * \param a The dividend
 * \param b The divisor
 * \return Results of divide as a pair of 32-bit quotient/remainder values.
 */
static inline divmod_result_t hw_divider_divmod_s32(int32_t a, int32_t b) {
    if (!b) return (((uint64_t)a)<<32u) | (uint32_t)(-__sign_of(a));
    return (((uint64_t)(a%b))<<32u) | (uint32_t)(a/b);
}

extern __thread divmod_result_t hw_divider_result_threadlocal;

/*! \brief Start a signed asynchronous divide
 *  \ingroup hardware_divider
 *
 * Start a divide of the specified signed parameters. You should wait for 8 cycles (__div_pause()) or wait for the ready bit to be set
 * (hw_divider_wait_ready()) prior to reading the results.
 *
 * \param a The dividend
 * \param b The divisor
 */
static inline void hw_divider_divmod_s32_start(int32_t a, int32_t b) {
    hw_divider_result_threadlocal = hw_divider_divmod_s32(a, b);
}

/*! \brief Start an unsigned asynchronous divide
 *  \ingroup hardware_divider
 *
 * Start a divide of the specified unsigned parameters. You should wait for 8 cycles (__div_pause()) or wait for the ready bit to be set
 * (hw_divider_wait_ready()) prior to reading the results.
 *
 * \param a The dividend
 * \param b The divisor
 */
static inline void hw_divider_divmod_u32_start(uint32_t a, uint32_t b) {
    hw_divider_result_threadlocal = hw_divider_divmod_u32(a, b);
}

/*! \brief Return result of last asynchronous HW divide
 *  \ingroup hardware_divider
 *
 * This function waits for the result to be ready by calling hw_divider_wait_ready().
 *
 * \return Current result. Most significant 32 bits are the remainder, lower 32 bits are the quotient.
 */
static inline divmod_result_t hw_divider_result_wait(void) {
    return hw_divider_result_threadlocal;
}

/*! \brief Return result of HW divide, nowait
 *  \ingroup hardware_divider
 *
 * \note This is UNSAFE in that the calculation may not have been completed.
 *
 * \return Current result. Most significant 32 bits are the remainder, lower 32 bits are the quotient.
 */
static inline divmod_result_t hw_divider_result_nowait(void) {
    return hw_divider_result_threadlocal;
}

/*! \brief Wait for a divide to complete
 *  \ingroup hardware_divider
 *
 * Wait for a divide to complete
 */
static inline void hw_divider_wait_ready(void) {}


/*! \brief Efficient extraction of unsigned quotient from 32p32 fixed point
 *  \ingroup hardware_divider
 *
 * \param r A pair of 32-bit quotient/remainder values.
 * \return Unsigned quotient
 */
inline static uint32_t to_quotient_u32(divmod_result_t r) {
    return (uint32_t) r;
}

/*! \brief Efficient extraction of signed quotient from 32p32 fixed point
 *  \ingroup hardware_divider
 *
 * \param r A pair of 32-bit quotient/remainder values.
 * \return Unsigned quotient
 */
inline static int32_t to_quotient_s32(divmod_result_t r) {
    return (int32_t)(uint32_t)r;
}

/*! \brief Efficient extraction of unsigned remainder from 32p32 fixed point
 *  \ingroup hardware_divider
 *
 * \param r A pair of 32-bit quotient/remainder values.
 * \return Unsigned remainder
 *
 * \note On Arm this is just a 32 bit register move or a nop
 */
inline static uint32_t to_remainder_u32(divmod_result_t r) {
    return (uint32_t)(r >> 32u);
}

/*! \brief Efficient extraction of signed remainder from 32p32 fixed point
 *  \ingroup hardware_divider
 *
 * \param r A pair of 32-bit quotient/remainder values.
 * \return Signed remainder
 *
 * \note On arm this is just a 32 bit register move or a nop
 */
inline static int32_t to_remainder_s32(divmod_result_t r) {
    return (int32_t)(r >> 32u);
}

static inline void hw_divider_pause(void) {}

/*! \brief Do an unsigned HW divide, wait for result, return quotient
 *  \ingroup hardware_divider
 *
 * Divide \p a by \p b, wait for calculation to complete, return quotient.
 *
 * \param a The dividend
 * \param b The divisor
 * \return Quotient results of the divide
 */
static inline uint32_t hw_divider_u32_quotient(uint32_t a, uint32_t b) {
    return b ? (a / b) : (uint32_t)(-1);
}

/*! \brief Do an unsigned HW divide, wait for result, return remainder
 *  \ingroup hardware_divider
 *
 * Divide \p a by \p b, wait for calculation to complete, return remainder.
 *
 * \param a The dividend
 * \param b The divisor
 * \return Remainder results of the divide
 */
static inline uint32_t hw_divider_u32_remainder(uint32_t a, uint32_t b) {
    return b ? (a % b) : a;
}

/*! \brief Do a signed HW divide, wait for result, return quotient
 *  \ingroup hardware_divider
 *
 * Divide \p a by \p b, wait for calculation to complete, return quotient.
 *
 * \param a The dividend
 * \param b The divisor
 * \return Quotient results of the divide
 */
static inline int32_t hw_divider_quotient_s32(int32_t a, int32_t b) {
    return to_quotient_s32(hw_divider_divmod_s32(a, b));
}

/*! \brief Do a signed HW divide, wait for result, return remainder
 *  \ingroup hardware_divider
 *
 * Divide \p a by \p b, wait for calculation to complete, return remainder.
 *
 * \param a The dividend
 * \param b The divisor
 * \return Remainder results of the divide
 */
static inline int32_t hw_divider_remainder_s32(int32_t a, int32_t b) {
    return b ? (a % b) : a;
}

/*! \brief Return result of last asynchronous HW divide, unsigned quotient only
 *  \ingroup hardware_divider
 *
 * This function waits for the result to be ready by calling hw_divider_wait_ready().
 *
 * \return Current unsigned quotient result.
 */
static inline uint32_t hw_divider_u32_quotient_wait(void) {
    return to_quotient_u32(hw_divider_result_wait());
}

/*! \brief Return result of last asynchronous HW divide, signed quotient only
 *  \ingroup hardware_divider
 *
 * This function waits for the result to be ready by calling hw_divider_wait_ready().
 *
 * \return Current signed quotient result.
 */
static inline int32_t hw_divider_s32_quotient_wait(void) {
    return to_remainder_u32(hw_divider_result_wait());
}

/*! \brief Return result of last asynchronous HW divide, unsigned remainder only
 *  \ingroup hardware_divider
 *
 * This function waits for the result to be ready by calling hw_divider_wait_ready().
 *
 * \return Current unsigned remainder result.
 */
static inline uint32_t hw_divider_u32_remainder_wait(void) {
    return to_quotient_s32(hw_divider_result_wait());
}

/*! \brief Return result of last asynchronous HW divide, signed remainder only
 *  \ingroup hardware_divider
 *
 * This function waits for the result to be ready by calling hw_divider_wait_ready().
 *
 * \return Current remainder results.
 */
static inline int32_t hw_divider_s32_remainder_wait(void) {
    return to_remainder_s32(hw_divider_result_wait());
}

/*! \brief Do a hardware unsigned HW divide, wait for result, return quotient
 *  \ingroup hardware_divider
 *
 * Divide \p a by \p b, wait for calculation to complete, return quotient.
 *
 * \param a The dividend
 * \param b The divisor
 * \return Quotient result of the divide
 */
static inline uint32_t hw_divider_u32_quotient_inlined(uint32_t a, uint32_t b) {
    return hw_divider_u32_quotient(a,b);
}

/*! \brief Do a hardware unsigned HW divide, wait for result, return remainder
 *  \ingroup hardware_divider
 *
 * Divide \p a by \p b, wait for calculation to complete, return remainder.
 *
 * \param a The dividend
 * \param b The divisor
 * \return Remainder result of the divide
 */
static inline uint32_t hw_divider_u32_remainder_inlined(uint32_t a, uint32_t b) {
    return hw_divider_u32_remainder(a,b);
}

/*! \brief Do a hardware signed HW divide, wait for result, return quotient
 *  \ingroup hardware_divider
 *
 * Divide \p a by \p b, wait for calculation to complete, return quotient.
 *
 * \param a The dividend
 * \param b The divisor
 * \return Quotient result of the divide
 */
static inline int32_t hw_divider_s32_quotient_inlined(int32_t a, int32_t b) {
    return hw_divider_quotient_s32(a,b);
}

/*! \brief Do a hardware signed HW divide, wait for result, return remainder
 *  \ingroup hardware_divider
 *
 * Divide \p a by \p b, wait for calculation to complete, return remainder.
 *
 * \param a The dividend
 * \param b The divisor
 * \return Remainder result of the divide
 */
static inline int32_t hw_divider_s32_remainder_inlined(int32_t a, int32_t b) {
    return hw_divider_remainder_s32(a,b);
}

typedef uint64_t hw_divider_state_t;

/*! \brief Save the calling cores hardware divider state
 *  \ingroup hardware_divider
 *
 * Copy the current core's hardware divider state into the provided structure. This method
 * waits for the divider results to be stable, then copies them to memory.
 * They can be restored via hw_divider_restore_state()
 *
 * \param dest the location to store the divider state
 */
 static inline void hw_divider_save_state(hw_divider_state_t *dest) {
    *dest = hw_divider_result_threadlocal;
}

/*! \brief Load a saved hardware divider state into the current core's hardware divider
 *  \ingroup hardware_divider
 *
 * Copy the passed hardware divider state into the hardware divider.
 *
 * \param src the location to load the divider state from
 */
 static inline void hw_divider_restore_state(hw_divider_state_t *src) {
    hw_divider_result_threadlocal = *src;
}

#ifdef __cplusplus
}
#endif
#endif // _HARDWARE_DIVIDER_H
