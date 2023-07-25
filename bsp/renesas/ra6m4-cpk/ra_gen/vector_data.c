/* generated vector source file - do not edit */
        #include "bsp_api.h"
        /* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
        #if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = sci_uart_rxi_isr, /* SCI7 RXI (Received data full) */
            [1] = sci_uart_txi_isr, /* SCI7 TXI (Transmit data empty) */
            [2] = sci_uart_tei_isr, /* SCI7 TEI (Transmit end) */
            [3] = sci_uart_eri_isr, /* SCI7 ERI (Receive error) */
            [4] = r_icu_isr, /* ICU IRQ0 (External pin interrupt 0) */
            [5] = spi_rxi_isr, /* SPI0 RXI (Receive buffer full) */
            [6] = spi_txi_isr, /* SPI0 TXI (Transmit buffer empty) */
            [7] = spi_tei_isr, /* SPI0 TEI (Transmission complete event) */
            [8] = spi_eri_isr, /* SPI0 ERI (Error) */
        };
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_IELS_ENUM(EVENT_SCI7_RXI), /* SCI7 RXI (Received data full) */
            [1] = BSP_PRV_IELS_ENUM(EVENT_SCI7_TXI), /* SCI7 TXI (Transmit data empty) */
            [2] = BSP_PRV_IELS_ENUM(EVENT_SCI7_TEI), /* SCI7 TEI (Transmit end) */
            [3] = BSP_PRV_IELS_ENUM(EVENT_SCI7_ERI), /* SCI7 ERI (Receive error) */
            [4] = BSP_PRV_IELS_ENUM(EVENT_ICU_IRQ0), /* ICU IRQ0 (External pin interrupt 0) */
            [5] = BSP_PRV_IELS_ENUM(EVENT_SPI0_RXI), /* SPI0 RXI (Receive buffer full) */
            [6] = BSP_PRV_IELS_ENUM(EVENT_SPI0_TXI), /* SPI0 TXI (Transmit buffer empty) */
            [7] = BSP_PRV_IELS_ENUM(EVENT_SPI0_TEI), /* SPI0 TEI (Transmission complete event) */
            [8] = BSP_PRV_IELS_ENUM(EVENT_SPI0_ERI), /* SPI0 ERI (Error) */
        };
        #endif