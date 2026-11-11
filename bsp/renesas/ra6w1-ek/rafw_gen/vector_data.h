/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <rtconfig.h>
#include "bsp_api.h"

void uart_w_isr(void);
void r_ext_irq_w_isr(void);

#define VECTOR_NUMBER_UARTW0_IRQ ((IRQn_Type) UART_IRQn) /* UARTW IRQ (Generic interrupt) */
#define UARTW0_IRQ_IRQn          ((IRQn_Type) UART_IRQn) /* UARTW IRQ (Generic interrupt) */

#ifdef BSP_USING_UART1
#define VECTOR_NUMBER_UARTW1_IRQ ((IRQn_Type) UART2_IRQn) /* UARTW2 IRQ (Generic interrupt) */
#define UARTW1_IRQ_IRQn          ((IRQn_Type) UART2_IRQn) /* UARTW2 IRQ (Generic interrupt) */
#endif

#ifdef BSP_USING_UART2
#define VECTOR_NUMBER_UARTW2_IRQ ((IRQn_Type) UART3_IRQn) /* UARTW3 IRQ (Generic interrupt) */
#define UARTW2_IRQ_IRQn          ((IRQn_Type) UART3_IRQn) /* UARTW3 IRQ (Generic interrupt) */
#endif

#define VECTOR_NUMBER_EXTIRQW_P0_IRQ ((IRQn_Type) GPIO_P0_IRQn) /* EXTIRQW P0 IRQ */
#define EXTIRQW_P0_IRQ_IRQn          ((IRQn_Type) GPIO_P0_IRQn) /* EXTIRQW P0 IRQ */
#define VECTOR_NUMBER_EXTIRQW_P1_IRQ ((IRQn_Type) GPIO_P1_IRQn) /* EXTIRQW P1 IRQ */
#define EXTIRQW_P1_IRQ_IRQn          ((IRQn_Type) GPIO_P1_IRQn) /* EXTIRQW P1 IRQ */

#ifdef BSP_USING_SPI
void spi_w_gen_isr(void);
#ifdef BSP_USING_SPI0
#define VECTOR_NUMBER_SPIW0_IRQ ((IRQn_Type) SPI_IRQn) /* SPIW IRQ */
#define SPIW0_IRQ_IRQn          ((IRQn_Type) SPI_IRQn) /* SPIW IRQ */
#endif  /* BSP_USING_SPI0 */

#ifdef BSP_USING_SPI1
#define VECTOR_NUMBER_SPIW1_IRQ ((IRQn_Type) SPI2_IRQn) /* SPIW2 IRQ */
#define SPIW1_IRQ_IRQn          ((IRQn_Type) SPI2_IRQn) /* SPIW2 IRQ */
#endif  /* BSP_USING_SPI1 */
#endif  /* BSP_USING_SPI */

#ifdef BSP_USING_HW_I2C
void i2c_master_w_gen_isr(void);
#ifdef BSP_USING_HW_I2C0
#define VECTOR_NUMBER_I2CW0_IRQ ((IRQn_Type) I2C_IRQn) /* I2CW IRQ */
#define I2CW0_IRQ_IRQn          ((IRQn_Type) I2C_IRQn) /* I2CW IRQ */
#endif /* BSP_USING_HW_I2C0 */

#ifdef BSP_USING_HW_I2C1
#define VECTOR_NUMBER_I2CW1_IRQ ((IRQn_Type) I2C2_IRQn) /* I2CW2 IRQ */
#define I2CW1_IRQ_IRQn          ((IRQn_Type) I2C2_IRQn) /* I2CW2 IRQ */
#endif /* BSP_USING_HW_I2C1 */
#endif /* BSP_USING_HW_I2C */

#ifdef BSP_USING_TIM_W
void r_tim_w_generic_isr(void);
#ifdef BSP_USING_TIM0
#define VECTOR_NUMBER_TIMW0_IRQ ((IRQn_Type) TIMER_IRQn)
#define TIMW0_IRQ_IRQn          ((IRQn_Type) TIMER_IRQn)
#endif
#ifdef BSP_USING_TIM1
#define VECTOR_NUMBER_TIMW1_IRQ ((IRQn_Type) TIMER2_IRQn)
#define TIMW1_IRQ_IRQn          ((IRQn_Type) TIMER2_IRQn)
#endif
#ifdef BSP_USING_TIM2
#define VECTOR_NUMBER_TIMW2_IRQ ((IRQn_Type) TIMER3_IRQn)
#define TIMW2_IRQ_IRQn          ((IRQn_Type) TIMER3_IRQn)
#endif
#ifdef BSP_USING_TIM3
#define VECTOR_NUMBER_TIMW3_IRQ ((IRQn_Type) TIMER4_IRQn)
#define TIMW3_IRQ_IRQn          ((IRQn_Type) TIMER4_IRQn)
#endif
#ifdef BSP_USING_TIM4
#define VECTOR_NUMBER_TIMW4_IRQ ((IRQn_Type) TIMER5_IRQn)
#define TIMW4_IRQ_IRQn          ((IRQn_Type) TIMER5_IRQn)
#endif
#ifdef BSP_USING_TIM5
#define VECTOR_NUMBER_TIMW5_IRQ ((IRQn_Type) TIMER6_IRQn)
#define TIMW5_IRQ_IRQn          ((IRQn_Type) TIMER6_IRQn)
#endif
#ifdef BSP_USING_TIM6
#define VECTOR_NUMBER_TIMW6_IRQ ((IRQn_Type) TIMER7_IRQn)
#define TIMW6_IRQ_IRQn          ((IRQn_Type) TIMER7_IRQn)
#endif
#ifdef BSP_USING_TIM7
#define VECTOR_NUMBER_TIMW7_IRQ ((IRQn_Type) TIMER8_IRQn)
#define TIMW7_IRQ_IRQn          ((IRQn_Type) TIMER8_IRQn)
#endif
#endif /* BSP_USING_TIM_W */

#ifdef __cplusplus
}
#endif

#endif /* VECTOR_DATA_H */
