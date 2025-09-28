/* generated vector source file - do not edit */
        #include "bsp_api.h"
        /* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
        #if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_NUM_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = sci_uart_rxi_isr, /* SCI0 RXI (Receive data full) */
            [1] = sci_uart_txi_isr, /* SCI0 TXI (Transmit data empty) */
            [2] = sci_uart_tei_isr, /* SCI0 TEI (Transmit end) */
            [3] = sci_uart_eri_isr, /* SCI0 ERI (Receive error) */
            [4] = r_icu_isr, /* ICU IRQ0 (External pin interrupt 0) */
            [5] = sci_uart_rxi_isr, /* SCI1 RXI (Receive data full) */
            [6] = sci_uart_txi_isr, /* SCI1 TXI (Transmit data empty) */
            [7] = sci_uart_tei_isr, /* SCI1 TEI (Transmit end) */
            [8] = sci_uart_eri_isr, /* SCI1 ERI (Receive error) */
            [9] = iic_master_rxi_isr, /* IIC0 RXI (Receive data full) */
            [10] = iic_master_txi_isr, /* IIC0 TXI (Transmit data empty) */
            [11] = iic_master_tei_isr, /* IIC0 TEI (Transmit end) */
            [12] = iic_master_eri_isr, /* IIC0 ERI (Transfer error) */
            [13] = spi_rxi_isr, /* SPI0 RXI (Receive buffer full) */
            [14] = spi_txi_isr, /* SPI0 TXI (Transmit buffer empty) */
            [15] = spi_tei_isr, /* SPI0 TEI (Transmission complete event) */
            [16] = spi_eri_isr, /* SPI0 ERI (Error) */
            [17] = rtc_carry_isr, /* RTC CARRY (Carry interrupt) */
            [18] = can_error_isr, /* CAN0 ERROR (Error interrupt) */
            [19] = can_rx_isr, /* CAN0 MAILBOX RX (Reception complete interrupt) */
            [20] = can_tx_isr, /* CAN0 MAILBOX TX (Transmission complete interrupt) */
            [21] = can_rx_isr, /* CAN0 FIFO RX (Receive FIFO interrupt) */
            [22] = can_tx_isr, /* CAN0 FIFO TX (Transmit FIFO interrupt) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_NUM_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_SCI0_RXI,GROUP0), /* SCI0 RXI (Receive data full) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TXI,GROUP1), /* SCI0 TXI (Transmit data empty) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TEI,GROUP2), /* SCI0 TEI (Transmit end) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_SCI0_ERI,GROUP3), /* SCI0 ERI (Receive error) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ0,GROUP4), /* ICU IRQ0 (External pin interrupt 0) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_SCI1_RXI,GROUP5), /* SCI1 RXI (Receive data full) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_SCI1_TXI,GROUP6), /* SCI1 TXI (Transmit data empty) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_SCI1_TEI,GROUP7), /* SCI1 TEI (Transmit end) */
            [8] = BSP_PRV_VECT_ENUM(EVENT_SCI1_ERI,GROUP0), /* SCI1 ERI (Receive error) */
            [9] = BSP_PRV_VECT_ENUM(EVENT_IIC0_RXI,GROUP1), /* IIC0 RXI (Receive data full) */
            [10] = BSP_PRV_VECT_ENUM(EVENT_IIC0_TXI,GROUP2), /* IIC0 TXI (Transmit data empty) */
            [11] = BSP_PRV_VECT_ENUM(EVENT_IIC0_TEI,GROUP3), /* IIC0 TEI (Transmit end) */
            [12] = BSP_PRV_VECT_ENUM(EVENT_IIC0_ERI,GROUP4), /* IIC0 ERI (Transfer error) */
            [13] = BSP_PRV_VECT_ENUM(EVENT_SPI0_RXI,GROUP5), /* SPI0 RXI (Receive buffer full) */
            [14] = BSP_PRV_VECT_ENUM(EVENT_SPI0_TXI,GROUP6), /* SPI0 TXI (Transmit buffer empty) */
            [15] = BSP_PRV_VECT_ENUM(EVENT_SPI0_TEI,GROUP7), /* SPI0 TEI (Transmission complete event) */
            [16] = BSP_PRV_VECT_ENUM(EVENT_SPI0_ERI,GROUP0), /* SPI0 ERI (Error) */
            [17] = BSP_PRV_VECT_ENUM(EVENT_RTC_CARRY,GROUP1), /* RTC CARRY (Carry interrupt) */
            [18] = BSP_PRV_VECT_ENUM(EVENT_CAN0_ERROR,GROUP2), /* CAN0 ERROR (Error interrupt) */
            [19] = BSP_PRV_VECT_ENUM(EVENT_CAN0_MAILBOX_RX,GROUP3), /* CAN0 MAILBOX RX (Reception complete interrupt) */
            [20] = BSP_PRV_VECT_ENUM(EVENT_CAN0_MAILBOX_TX,GROUP4), /* CAN0 MAILBOX TX (Transmission complete interrupt) */
            [21] = BSP_PRV_VECT_ENUM(EVENT_CAN0_FIFO_RX,GROUP5), /* CAN0 FIFO RX (Receive FIFO interrupt) */
            [22] = BSP_PRV_VECT_ENUM(EVENT_CAN0_FIFO_TX,GROUP6), /* CAN0 FIFO TX (Transmit FIFO interrupt) */
        };
        #endif
        #endif
