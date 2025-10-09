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
            [5] = iic_master_rxi_isr, /* IIC0 RXI (Receive data full) */
            [6] = iic_master_txi_isr, /* IIC0 TXI (Transmit data empty) */
            [7] = iic_master_tei_isr, /* IIC0 TEI (Transmit end) */
            [8] = iic_master_eri_isr, /* IIC0 ERI (Transfer error) */
            [9] = rtc_carry_isr, /* RTC CARRY (Carry interrupt) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_NUM_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_SCI0_RXI,GROUP0), /* SCI0 RXI (Receive data full) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TXI,GROUP1), /* SCI0 TXI (Transmit data empty) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TEI,GROUP2), /* SCI0 TEI (Transmit end) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_SCI0_ERI,GROUP3), /* SCI0 ERI (Receive error) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ0,GROUP4), /* ICU IRQ0 (External pin interrupt 0) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_IIC0_RXI,GROUP5), /* IIC0 RXI (Receive data full) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_IIC0_TXI,GROUP6), /* IIC0 TXI (Transmit data empty) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_IIC0_TEI,GROUP7), /* IIC0 TEI (Transmit end) */
            [8] = BSP_PRV_VECT_ENUM(EVENT_IIC0_ERI,GROUP0), /* IIC0 ERI (Transfer error) */
            [9] = BSP_PRV_VECT_ENUM(EVENT_RTC_CARRY,GROUP1), /* RTC CARRY (Carry interrupt) */
        };
        #endif
        #endif