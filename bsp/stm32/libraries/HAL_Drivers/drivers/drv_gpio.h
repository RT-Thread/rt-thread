/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018-11-06     balanceTWK        first version
 * 2020-06-16     thread-liu        add stm32mp1
 * 2020-09-01     thread-liu        add GPIOZ
 * 2020-09-18     geniusgogo        optimization design pin-index algorithm
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __STM32_PORT(port)  GPIO##port##_BASE

/**
 * @brief  Calculates the RT-Thread global pin number from an STM32-specific port and pin.
 *
 * @details
 * This macro provides a vendor-specific way to map a human-readable GPIO port
 * (e.g., 'A', 'B') and pin number (0-15) to a single integer value that RT-Thread's
 * pin device driver uses to identify a pin globally.
 *
 * The calculation is based on the memory address offset of the target GPIO port's
 * base register relative to GPIOA. It assumes a linear memory map for GPIO ports.
 *
 * It includes special compile-time handling for different STM32 series, such as the
 * STM32MP1, which have a different GPIO memory layout (e.g., 4KB stride between
 * port registers) and may include special ports like GPIOZ.
 *
 * @param[in]  PORTx The GPIO port letter (e.g., A, B, C, D). Pass the letter without
 * quotes (e.g., A, not 'A').
 * @param[in]  PIN   The pin number within the port (an integer from 0 to 15).
 *
 * @return
 * An `rt_base_t` integer representing the unique pin index for use with RT-Thread
 * pin device driver functions (e.g., rt_pin_mode(), rt_pin_write()).
 *
 * @note
 * - **STM32 & RT-Thread Specific:** This macro is highly dependent on the STM32 HAL
 *   and RT-Thread's pin numbering convention. It relies on underlying HAL macros like
 *   `__STM32_PORT()` and base address definitions like `GPIOA_BASE`.
 * - **Not Portable:** Do not use this macro in code intended to be portable across
 *   different microcontroller vendors.
 * - **Compile-Time Evaluation:** The macro is evaluated entirely at compile time. The
 *   correct implementation for the target STM32 series is selected via preprocessor
 *   directives (e.g., `SOC_SERIES_STM32MP1`).
 * - **Argument Evaluation:** As this is a preprocessor macro, its arguments are
 *   substituted directly. Avoid passing expressions with side effects (e.g., `i++`)
 *   as arguments, as they may be evaluated multiple times.
 *
 * @see rt_pin_mode()
 * @see rt_pin_write()
 * @see rt_pin_read()
 *
 * @code
 * // Usage Example 1: Configure pin PD11 as a push-pull output.
 * rt_pin_mode(GET_PIN(D, 11), PIN_MODE_OUTPUT);
 *
 * // Usage Example 2: Write a high logic level to pin PA5.
 * rt_pin_write(GET_PIN(A, 5), PIN_HIGH);
 *
 * // Usage Example 3: Read the logic level from pin PC13.
 * int level = rt_pin_read(GET_PIN(C, 13));
 * @endcode
 */
#if defined(SOC_SERIES_STM32MP1)
#define GET_PIN(PORTx,PIN) (GPIO##PORTx == GPIOZ) ? (176 + PIN) : ((rt_base_t)((16 * ( ((rt_base_t)__STM32_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x1000UL) )) + PIN))
#else
#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__STM32_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x0400UL) )) + PIN)
#endif

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};

int rt_hw_pin_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */

