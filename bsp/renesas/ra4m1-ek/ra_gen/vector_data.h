/* generated vector header file - do not edit */
        #ifndef VECTOR_DATA_H
        #define VECTOR_DATA_H
        #ifdef __cplusplus
        extern "C" {
        #endif
                /* Number of interrupts allocated */
        #ifndef VECTOR_DATA_IRQ_COUNT
        #define VECTOR_DATA_IRQ_COUNT    (23)
        #endif
        /* ISR prototypes */
        void sci_uart_rxi_isr(void);
        void sci_uart_txi_isr(void);
        void sci_uart_tei_isr(void);
        void sci_uart_eri_isr(void);
        void r_icu_isr(void);
        void iic_master_rxi_isr(void);
        void iic_master_txi_isr(void);
        void iic_master_tei_isr(void);
        void iic_master_eri_isr(void);
        void spi_rxi_isr(void);
        void spi_txi_isr(void);
        void spi_tei_isr(void);
        void spi_eri_isr(void);
        void rtc_carry_isr(void);
        void can_error_isr(void);
        void can_rx_isr(void);
        void can_tx_isr(void);

        /* Vector table allocations */
        #define VECTOR_NUMBER_SCI0_RXI ((IRQn_Type) 0) /* SCI0 RXI (Receive data full) */
        #define SCI0_RXI_IRQn          ((IRQn_Type) 0) /* SCI0 RXI (Receive data full) */
        #define VECTOR_NUMBER_SCI0_TXI ((IRQn_Type) 1) /* SCI0 TXI (Transmit data empty) */
        #define SCI0_TXI_IRQn          ((IRQn_Type) 1) /* SCI0 TXI (Transmit data empty) */
        #define VECTOR_NUMBER_SCI0_TEI ((IRQn_Type) 2) /* SCI0 TEI (Transmit end) */
        #define SCI0_TEI_IRQn          ((IRQn_Type) 2) /* SCI0 TEI (Transmit end) */
        #define VECTOR_NUMBER_SCI0_ERI ((IRQn_Type) 3) /* SCI0 ERI (Receive error) */
        #define SCI0_ERI_IRQn          ((IRQn_Type) 3) /* SCI0 ERI (Receive error) */
        #define VECTOR_NUMBER_ICU_IRQ0 ((IRQn_Type) 4) /* ICU IRQ0 (External pin interrupt 0) */
        #define ICU_IRQ0_IRQn          ((IRQn_Type) 4) /* ICU IRQ0 (External pin interrupt 0) */
        #define VECTOR_NUMBER_SCI1_RXI ((IRQn_Type) 5) /* SCI1 RXI (Receive data full) */
        #define SCI1_RXI_IRQn          ((IRQn_Type) 5) /* SCI1 RXI (Receive data full) */
        #define VECTOR_NUMBER_SCI1_TXI ((IRQn_Type) 6) /* SCI1 TXI (Transmit data empty) */
        #define SCI1_TXI_IRQn          ((IRQn_Type) 6) /* SCI1 TXI (Transmit data empty) */
        #define VECTOR_NUMBER_SCI1_TEI ((IRQn_Type) 7) /* SCI1 TEI (Transmit end) */
        #define SCI1_TEI_IRQn          ((IRQn_Type) 7) /* SCI1 TEI (Transmit end) */
        #define VECTOR_NUMBER_SCI1_ERI ((IRQn_Type) 8) /* SCI1 ERI (Receive error) */
        #define SCI1_ERI_IRQn          ((IRQn_Type) 8) /* SCI1 ERI (Receive error) */
        #define VECTOR_NUMBER_IIC0_RXI ((IRQn_Type) 9) /* IIC0 RXI (Receive data full) */
        #define IIC0_RXI_IRQn          ((IRQn_Type) 9) /* IIC0 RXI (Receive data full) */
        #define VECTOR_NUMBER_IIC0_TXI ((IRQn_Type) 10) /* IIC0 TXI (Transmit data empty) */
        #define IIC0_TXI_IRQn          ((IRQn_Type) 10) /* IIC0 TXI (Transmit data empty) */
        #define VECTOR_NUMBER_IIC0_TEI ((IRQn_Type) 11) /* IIC0 TEI (Transmit end) */
        #define IIC0_TEI_IRQn          ((IRQn_Type) 11) /* IIC0 TEI (Transmit end) */
        #define VECTOR_NUMBER_IIC0_ERI ((IRQn_Type) 12) /* IIC0 ERI (Transfer error) */
        #define IIC0_ERI_IRQn          ((IRQn_Type) 12) /* IIC0 ERI (Transfer error) */
        #define VECTOR_NUMBER_SPI0_RXI ((IRQn_Type) 13) /* SPI0 RXI (Receive buffer full) */
        #define SPI0_RXI_IRQn          ((IRQn_Type) 13) /* SPI0 RXI (Receive buffer full) */
        #define VECTOR_NUMBER_SPI0_TXI ((IRQn_Type) 14) /* SPI0 TXI (Transmit buffer empty) */
        #define SPI0_TXI_IRQn          ((IRQn_Type) 14) /* SPI0 TXI (Transmit buffer empty) */
        #define VECTOR_NUMBER_SPI0_TEI ((IRQn_Type) 15) /* SPI0 TEI (Transmission complete event) */
        #define SPI0_TEI_IRQn          ((IRQn_Type) 15) /* SPI0 TEI (Transmission complete event) */
        #define VECTOR_NUMBER_SPI0_ERI ((IRQn_Type) 16) /* SPI0 ERI (Error) */
        #define SPI0_ERI_IRQn          ((IRQn_Type) 16) /* SPI0 ERI (Error) */
        #define VECTOR_NUMBER_RTC_CARRY ((IRQn_Type) 17) /* RTC CARRY (Carry interrupt) */
        #define RTC_CARRY_IRQn          ((IRQn_Type) 17) /* RTC CARRY (Carry interrupt) */
        #define VECTOR_NUMBER_CAN0_ERROR ((IRQn_Type) 18) /* CAN0 ERROR (Error interrupt) */
        #define CAN0_ERROR_IRQn          ((IRQn_Type) 18) /* CAN0 ERROR (Error interrupt) */
        #define VECTOR_NUMBER_CAN0_MAILBOX_RX ((IRQn_Type) 19) /* CAN0 MAILBOX RX (Reception complete interrupt) */
        #define CAN0_MAILBOX_RX_IRQn          ((IRQn_Type) 19) /* CAN0 MAILBOX RX (Reception complete interrupt) */
        #define VECTOR_NUMBER_CAN0_MAILBOX_TX ((IRQn_Type) 20) /* CAN0 MAILBOX TX (Transmission complete interrupt) */
        #define CAN0_MAILBOX_TX_IRQn          ((IRQn_Type) 20) /* CAN0 MAILBOX TX (Transmission complete interrupt) */
        #define VECTOR_NUMBER_CAN0_FIFO_RX ((IRQn_Type) 21) /* CAN0 FIFO RX (Receive FIFO interrupt) */
        #define CAN0_FIFO_RX_IRQn          ((IRQn_Type) 21) /* CAN0 FIFO RX (Receive FIFO interrupt) */
        #define VECTOR_NUMBER_CAN0_FIFO_TX ((IRQn_Type) 22) /* CAN0 FIFO TX (Transmit FIFO interrupt) */
        #define CAN0_FIFO_TX_IRQn          ((IRQn_Type) 22) /* CAN0 FIFO TX (Transmit FIFO interrupt) */
        /* The number of entries required for the ICU vector table. */
        #define BSP_ICU_VECTOR_NUM_ENTRIES (23)

        #ifdef __cplusplus
        }
        #endif
        #endif /* VECTOR_DATA_H */