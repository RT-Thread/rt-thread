/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (1)
#endif
/* ISR prototypes */
void uart_w_isr(void);
#if defined(BSP_MCU_GROUP_RA6B1) || defined(BSP_MCU_GROUP_RA6U1) //BROMINE-TODO
        /* Vector table allocations */
        #define VECTOR_NUMBER_UARTW1_IRQ ((IRQn_Type) 0) /* UARTW1 IRQ (Generic interrupt) */
        #define UARTW1_IRQ_IRQn          ((IRQn_Type) 0) /* UARTW1 IRQ (Generic interrupt) */
#else
/* Vector table allocations */
#define VECTOR_NUMBER_UARTW1_IRQ ((IRQn_Type) 2) /* UARTW1 IRQ (Generic interrupt) */
#define UARTW1_IRQ_IRQn          ((IRQn_Type) 2) /* UARTW1 IRQ (Generic interrupt) */
#endif
#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
