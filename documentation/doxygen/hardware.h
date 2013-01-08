/*
 * This file is only used for doxygen document generation.
 */

/**
 * @defgroup bsp Hardware Related Package
 *
 * @brief Hardware Related Package includes board support package(BSP) and CSP(Chip
 * Support Package).
 *
 * Board Support Package(BSP) is the hardware related wrapper, for example, peripherals
 * in board, the pinmux setting etc. In RT-Thread RTOS, the bsp is placed under bsp
 * directory.
 *
 * Chip Support Package (CSP) is a software set that contains chip specific software.
 * A CSP usually includes operating system porting and peripheral device drivers inside
 * chip. In RT-Thread RTOS, the csp is placed under libcpu directory.
 */

/**
 * @addtogroup bsp
 */
/*@{*/

/**
 * This function will return current system interrupt status and disable system
 * interrupt.
 *
 * @return the current system interrupt status
 */
rt_base_t rt_hw_interrupt_disable(void);

/**
 * This function will set the specified interrupt status, which shall saved by
 * rt_hw_intterrupt_disable function. If the saved interrupt status is interrupt
 * opened, this function will open system interrupt status.
 */
void rt_hw_interrupt_enable(rt_base_t level);

/**
 * This function initializes interrupt.
 */
void rt_hw_interrupt_init(void);

/**
 * This function masks the specified interrupt.
 *
 * @param vector the interrupt number to be masked.
 *
 * @note not all of platform provide this function.
 */
void rt_hw_interrupt_mask(int vector);

/**
 * This function umasks the specified interrupt.
 *
 * @param vector the interrupt number to be unmasked.
 *
 * @note not all of platform provide this function.
 */
void rt_hw_interrupt_umask(int vector);

/**
 * This function will install specified interrupt handler.
 *
 * @param vector the interrupt number to be installed.
 * @param new_handler the new interrupt handler.
 * @param old_handler the old interrupt handler. This parameter can be RT_NULL.
 *
 * @note not all of platform provide this function.
 */
void rt_hw_interrupt_install(int vector, rt_isr_handler_t new_handler,
		rt_isr_handler_t *old_handler);

/**
 * This function will reset whole platform.
 */
void rt_hw_cpu_reset(void);

/**
 * This function will halt whole platform.
 */
void rt_hw_cpu_shutdown(void);

/*@}*/
