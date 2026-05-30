/* generated vector source file - do not edit */
        #include "bsp_api.h"
        /* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
        #if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_NUM_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = sci_b_uart_rxi_isr, /* SCI8 RXI (Receive data full) */
            [1] = sci_b_uart_txi_isr, /* SCI8 TXI (Transmit data empty) */
            [2] = sci_b_uart_tei_isr, /* SCI8 TEI (Transmit end) */
            [3] = sci_b_uart_eri_isr, /* SCI8 ERI (Receive error) */
            [4] = layer3_switch_gwdi_isr, /* ETHER GWDI0 (GWCA Data Interrupt 0) */
            [5] = layer3_switch_eaei_isr, /* ETHER EAEI0 (ETHA0 Error Interrupt) */
            [6] = layer3_switch_eaei_isr, /* ETHER EAEI1 (ETHA1 Error Interrupt) */
            [7] = adc_b_limclpi_isr, /* ADC LIMCLPI (Limiter clip interrupt with the limit table 0 to 7) */
            [8] = adc_b_err0_isr, /* ADC ERR0 (A/D converter unit 0 Error) */
            [9] = adc_b_err1_isr, /* ADC ERR1 (A/D converter unit 1 Error) */
            [10] = adc_b_resovf0_isr, /* ADC RESOVF0 (A/D conversion overflow on A/D converter unit 0) */
            [11] = adc_b_resovf1_isr, /* ADC RESOVF1 (A/D conversion overflow on A/D converter unit 1) */
            [12] = adc_b_calend0_isr, /* ADC CALEND0 (End of calibration of A/D converter unit 0) */
            [13] = adc_b_calend1_isr, /* ADC CALEND1 (End of calibration of A/D converter unit 1) */
            [14] = adc_b_adi0_isr, /* ADC ADI0 (End of A/D scanning operation(Gr.0)) */
            [15] = adc_b_adi1_isr, /* ADC ADI1 (End of A/D scanning operation(Gr.1)) */
            [16] = adc_b_adi2_isr, /* ADC ADI2 (End of A/D scanning operation(Gr.2)) */
            [17] = adc_b_adi3_isr, /* ADC ADI3 (End of A/D scanning operation(Gr.3)) */
            [18] = adc_b_adi4_isr, /* ADC ADI4 (End of A/D scanning operation(Gr.4)) */
            [19] = adc_b_fifoovf_isr, /* ADC FIFOOVF (FIFO data overflow) */
            [20] = adc_b_fiforeq0_isr, /* ADC FIFOREQ0 (FIFO data read request interrupt(Gr.0)) */
            [21] = adc_b_fiforeq1_isr, /* ADC FIFOREQ1 (FIFO data read request interrupt(Gr.1)) */
            [22] = adc_b_fiforeq2_isr, /* ADC FIFOREQ2 (FIFO data read request interrupt(Gr.2)) */
            [23] = adc_b_fiforeq3_isr, /* ADC FIFOREQ3 (FIFO data read request interrupt(Gr.3)) */
            [24] = adc_b_fiforeq4_isr, /* ADC FIFOREQ4 (FIFO data read request interrupt(Gr.4)) */
            [25] = gpt_counter_overflow_isr, /* GPT0 COUNTER OVERFLOW (Overflow) */
            [26] = canfd_error_isr, /* CAN0 CHERR (Channel  error) */
            [27] = canfd_channel_tx_isr, /* CAN0 TX (Transmit interrupt) */
            [28] = canfd_common_fifo_rx_isr, /* CAN0 COMFRX (Common FIFO receive interrupt) */
            [29] = canfd_error_isr, /* CAN GLERR (Global error) */
            [30] = canfd_rx_fifo_isr, /* CAN RXF (Global receive FIFO interrupt) */
            [31] = sdhimmc_accs_isr, /* SDHIMMC0 ACCS (Card access) */
            [32] = sdhimmc_card_isr, /* SDHIMMC0 CARD (Card detect) */
            [33] = dmac_int_isr, /* DMAC0 INT (DMAC0 transfer end) */
            [34] = rtc_alarm_periodic_isr, /* RTC ALARM (Alarm interrupt) */
            [35] = rtc_alarm_periodic_isr, /* RTC PERIOD (Periodic interrupt) */
            [36] = rtc_carry_isr, /* RTC CARRY (Carry interrupt) */
            [37] = iic_master_rxi_isr, /* IIC2 RXI (Receive data full) */
            [38] = iic_master_txi_isr, /* IIC2 TXI (Transmit data empty) */
            [39] = iic_master_tei_isr, /* IIC2 TEI (Transmit end) */
            [40] = iic_master_eri_isr, /* IIC2 ERI (Transfer error) */
            [41] = spi_b_rxi_isr, /* SPI0 RXI (Receive buffer full) */
            [42] = spi_b_txi_isr, /* SPI0 TXI (Transmit buffer empty) */
            [43] = spi_b_tei_isr, /* SPI0 TEI (Transmission complete event) */
            [44] = spi_b_eri_isr, /* SPI0 ERI (Error) */
            [45] = sci_b_uart_rxi_isr, /* SCI0 RXI (Receive data full) */
            [46] = sci_b_uart_txi_isr, /* SCI0 TXI (Transmit data empty) */
            [47] = sci_b_uart_tei_isr, /* SCI0 TEI (Transmit end) */
            [48] = sci_b_uart_eri_isr, /* SCI0 ERI (Receive error) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_NUM_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_SCI8_RXI,GROUP0), /* SCI8 RXI (Receive data full) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_SCI8_TXI,GROUP1), /* SCI8 TXI (Transmit data empty) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_SCI8_TEI,GROUP2), /* SCI8 TEI (Transmit end) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_SCI8_ERI,GROUP3), /* SCI8 ERI (Receive error) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_ETHER_GWDI0,GROUP4), /* ETHER GWDI0 (GWCA Data Interrupt 0) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_ETHER_EAEI0,GROUP5), /* ETHER EAEI0 (ETHA0 Error Interrupt) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_ETHER_EAEI1,GROUP6), /* ETHER EAEI1 (ETHA1 Error Interrupt) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_ADC_LIMCLPI,GROUP7), /* ADC LIMCLPI (Limiter clip interrupt with the limit table 0 to 7) */
            [8] = BSP_PRV_VECT_ENUM(EVENT_ADC_ERR0,GROUP0), /* ADC ERR0 (A/D converter unit 0 Error) */
            [9] = BSP_PRV_VECT_ENUM(EVENT_ADC_ERR1,GROUP1), /* ADC ERR1 (A/D converter unit 1 Error) */
            [10] = BSP_PRV_VECT_ENUM(EVENT_ADC_RESOVF0,GROUP2), /* ADC RESOVF0 (A/D conversion overflow on A/D converter unit 0) */
            [11] = BSP_PRV_VECT_ENUM(EVENT_ADC_RESOVF1,GROUP3), /* ADC RESOVF1 (A/D conversion overflow on A/D converter unit 1) */
            [12] = BSP_PRV_VECT_ENUM(EVENT_ADC_CALEND0,GROUP4), /* ADC CALEND0 (End of calibration of A/D converter unit 0) */
            [13] = BSP_PRV_VECT_ENUM(EVENT_ADC_CALEND1,GROUP5), /* ADC CALEND1 (End of calibration of A/D converter unit 1) */
            [14] = BSP_PRV_VECT_ENUM(EVENT_ADC_ADI0,GROUP6), /* ADC ADI0 (End of A/D scanning operation(Gr.0)) */
            [15] = BSP_PRV_VECT_ENUM(EVENT_ADC_ADI1,GROUP7), /* ADC ADI1 (End of A/D scanning operation(Gr.1)) */
            [16] = BSP_PRV_VECT_ENUM(EVENT_ADC_ADI2,GROUP0), /* ADC ADI2 (End of A/D scanning operation(Gr.2)) */
            [17] = BSP_PRV_VECT_ENUM(EVENT_ADC_ADI3,GROUP1), /* ADC ADI3 (End of A/D scanning operation(Gr.3)) */
            [18] = BSP_PRV_VECT_ENUM(EVENT_ADC_ADI4,GROUP2), /* ADC ADI4 (End of A/D scanning operation(Gr.4)) */
            [19] = BSP_PRV_VECT_ENUM(EVENT_ADC_FIFOOVF,GROUP3), /* ADC FIFOOVF (FIFO data overflow) */
            [20] = BSP_PRV_VECT_ENUM(EVENT_ADC_FIFOREQ0,GROUP4), /* ADC FIFOREQ0 (FIFO data read request interrupt(Gr.0)) */
            [21] = BSP_PRV_VECT_ENUM(EVENT_ADC_FIFOREQ1,GROUP5), /* ADC FIFOREQ1 (FIFO data read request interrupt(Gr.1)) */
            [22] = BSP_PRV_VECT_ENUM(EVENT_ADC_FIFOREQ2,GROUP6), /* ADC FIFOREQ2 (FIFO data read request interrupt(Gr.2)) */
            [23] = BSP_PRV_VECT_ENUM(EVENT_ADC_FIFOREQ3,GROUP7), /* ADC FIFOREQ3 (FIFO data read request interrupt(Gr.3)) */
            [24] = BSP_PRV_VECT_ENUM(EVENT_ADC_FIFOREQ4,GROUP0), /* ADC FIFOREQ4 (FIFO data read request interrupt(Gr.4)) */
            [25] = BSP_PRV_VECT_ENUM(EVENT_GPT0_COUNTER_OVERFLOW,GROUP1), /* GPT0 COUNTER OVERFLOW (Overflow) */
            [26] = BSP_PRV_VECT_ENUM(EVENT_CAN0_CHERR,GROUP2), /* CAN0 CHERR (Channel  error) */
            [27] = BSP_PRV_VECT_ENUM(EVENT_CAN0_TX,GROUP3), /* CAN0 TX (Transmit interrupt) */
            [28] = BSP_PRV_VECT_ENUM(EVENT_CAN0_COMFRX,GROUP4), /* CAN0 COMFRX (Common FIFO receive interrupt) */
            [29] = BSP_PRV_VECT_ENUM(EVENT_CAN_GLERR,GROUP5), /* CAN GLERR (Global error) */
            [30] = BSP_PRV_VECT_ENUM(EVENT_CAN_RXF,GROUP6), /* CAN RXF (Global receive FIFO interrupt) */
            [31] = BSP_PRV_VECT_ENUM(EVENT_SDHIMMC0_ACCS,GROUP7), /* SDHIMMC0 ACCS (Card access) */
            [32] = BSP_PRV_VECT_ENUM(EVENT_SDHIMMC0_CARD,FIXED), /* SDHIMMC0 CARD (Card detect) */
            [33] = BSP_PRV_VECT_ENUM(EVENT_DMAC0_INT,FIXED), /* DMAC0 INT (DMAC0 transfer end) */
            [34] = BSP_PRV_VECT_ENUM(EVENT_RTC_ALARM,FIXED), /* RTC ALARM (Alarm interrupt) */
            [35] = BSP_PRV_VECT_ENUM(EVENT_RTC_PERIOD,FIXED), /* RTC PERIOD (Periodic interrupt) */
            [36] = BSP_PRV_VECT_ENUM(EVENT_RTC_CARRY,FIXED), /* RTC CARRY (Carry interrupt) */
            [37] = BSP_PRV_VECT_ENUM(EVENT_IIC2_RXI,FIXED), /* IIC2 RXI (Receive data full) */
            [38] = BSP_PRV_VECT_ENUM(EVENT_IIC2_TXI,FIXED), /* IIC2 TXI (Transmit data empty) */
            [39] = BSP_PRV_VECT_ENUM(EVENT_IIC2_TEI,FIXED), /* IIC2 TEI (Transmit end) */
            [40] = BSP_PRV_VECT_ENUM(EVENT_IIC2_ERI,FIXED), /* IIC2 ERI (Transfer error) */
            [41] = BSP_PRV_VECT_ENUM(EVENT_SPI0_RXI,FIXED), /* SPI0 RXI (Receive buffer full) */
            [42] = BSP_PRV_VECT_ENUM(EVENT_SPI0_TXI,FIXED), /* SPI0 TXI (Transmit buffer empty) */
            [43] = BSP_PRV_VECT_ENUM(EVENT_SPI0_TEI,FIXED), /* SPI0 TEI (Transmission complete event) */
            [44] = BSP_PRV_VECT_ENUM(EVENT_SPI0_ERI,FIXED), /* SPI0 ERI (Error) */
            [45] = BSP_PRV_VECT_ENUM(EVENT_SCI0_RXI,FIXED), /* SCI0 RXI (Receive data full) */
            [46] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TXI,FIXED), /* SCI0 TXI (Transmit data empty) */
            [47] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TEI,FIXED), /* SCI0 TEI (Transmit end) */
            [48] = BSP_PRV_VECT_ENUM(EVENT_SCI0_ERI,FIXED), /* SCI0 ERI (Receive error) */
        };
        #endif
        #endif