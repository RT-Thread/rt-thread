/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if BSP_FEATURE_BSP_HAS_ICU
        #if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                [0] = uart_w_isr, /* UARTW1 IRQ (Generic interrupt) */
        };
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
                [0] = BSP_PRV_IELS_ENUM(EVENT_UARTW1_IRQ), /* UARTW1 IRQ (Generic interrupt) */
        };
        #endif
        #else
BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_IRQ_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
{
#if VECTOR_DATA_IRQ_COUNT > 0
            [2] = uart_w_isr, /* UARTW1 IRQ (Generic interrupt) */
        #endif
};
#endif
