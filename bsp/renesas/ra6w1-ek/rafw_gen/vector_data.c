/* generated vector source file - do not edit */
#include "vector_data.h"

BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_IRQ_VECTOR_MAX_ENTRIES]
/* cppcheck-suppress-begin unknownMacro */
    BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
{
    [UART_IRQn] = uart_w_isr, /* UARTW IRQ (Generic interrupt) */
#ifdef BSP_USING_UART1
    [UART2_IRQn] = uart_w_isr, /* UARTW2 IRQ (Generic interrupt) */
#endif
#ifdef BSP_USING_UART2
    [UART3_IRQn] = uart_w_isr, /* UARTW3 IRQ (Generic interrupt) */
#endif
#ifdef BSP_USING_HW_I2C0
    [I2C_IRQn] = i2c_master_w_gen_isr, /* I2CW IRQ */
#endif
#ifdef BSP_USING_HW_I2C1
    [I2C2_IRQn] = i2c_master_w_gen_isr, /* I2CW2 IRQ */
#endif
#ifdef BSP_USING_SPI0
    [SPI_IRQn] = spi_w_gen_isr, /* SPIW IRQ */
#endif
#ifdef BSP_USING_SPI1
    [SPI2_IRQn] = spi_w_gen_isr, /* SPIW2 IRQ */
#endif
#ifdef BSP_USING_TIM_W
#ifdef BSP_USING_TIM0
    [TIMER_IRQn] = r_tim_w_generic_isr, /* TIM_W1 IRQ */
#endif
#ifdef BSP_USING_TIM1
    [TIMER2_IRQn] = r_tim_w_generic_isr, /* TIM_W2 IRQ */
#endif
#ifdef BSP_USING_TIM2
    [TIMER3_IRQn] = r_tim_w_generic_isr, /* TIM_W3 IRQ */
#endif
#ifdef BSP_USING_TIM3
    [TIMER4_IRQn] = r_tim_w_generic_isr, /* TIM_W4 IRQ */
#endif
#ifdef BSP_USING_TIM4
    [TIMER5_IRQn] = r_tim_w_generic_isr, /* TIM_W5 IRQ */
#endif
#ifdef BSP_USING_TIM5
    [TIMER6_IRQn] = r_tim_w_generic_isr, /* TIM_W6 IRQ */
#endif
#ifdef BSP_USING_TIM6
    [TIMER7_IRQn] = r_tim_w_generic_isr, /* TIM_W7 IRQ */
#endif
#ifdef BSP_USING_TIM7
    [TIMER8_IRQn] = r_tim_w_generic_isr, /* TIM_W8 IRQ */
#endif
#endif /* BSP_USING_TIM_W */
    [GPIO_P0_IRQn] = r_ext_irq_w_isr, /* EXTIRQW P0 IRQ */
    [GPIO_P1_IRQn] = r_ext_irq_w_isr, /* EXTIRQW P1 IRQ */
};
/* cppcheck-suppress-end unknownMacro */
