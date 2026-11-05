/* generated vector source file - do not edit */
#include "vector_data.h"

void KDMA_Handler(void) __attribute__((weak));
void TDES_CBC_Handler(void) __attribute__((weak));
void PSK_SHA1_Handler(void) __attribute__((weak));
void SYSPLL_Lock_Handler(void) __attribute__((weak));
void RTC_IF_EXTWK_Handler(void) __attribute__((weak));
void RTC_IF_BLACK_Handler(void) __attribute__((weak));
void RTC_IF_BROWN_Handler(void) __attribute__((weak));
void RTC_IF_PCNT_Handler(void) __attribute__((weak));
void RTC_IF_BCF_MSR_Handler(void) __attribute__((weak));
void RTC_IF_RTC_ACC_Handler(void) __attribute__((weak));
void RTC_IF_EXP_Handler(void) __attribute__((weak));
void RTC_IF_LMR_Handler(void) __attribute__((weak));
void MRM_Handler(void) __attribute__((weak));
void DCACHE_MRM_Handler(void) __attribute__((weak));
void CC312_Handler(void) __attribute__((weak));
void FPLL_Lock_Handler(void) __attribute__((weak));
void hsu_isr(void) __attribute__((weak));
void rxl_mpdu_isr(void) __attribute__((weak));
void txl_transmit_trigger(void) __attribute__((weak));
void txl_prot_trigger(void) __attribute__((weak));
void hal_machw_gen_handler(void) __attribute__((weak));
void hal_machw_bcn_cancellation_handler(void) __attribute__((weak));
void phy_rc_isr(void) __attribute__((weak));

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

    [KDMA_IRQn] = KDMA_Handler, /* WIFI KDMA IRQ */
    [TDES_CBC_IRQn] = TDES_CBC_Handler, /* WIFI TDES CBC IRQ */
    [PSK_SHA1_IRQn] = PSK_SHA1_Handler, /* WIFI PSK SHA1 IRQ */
    [SYSPLL_LOCK_IRQn] = SYSPLL_Lock_Handler, /* WIFI SYSPLL lock IRQ */
    [RTC_IF_EXTWK_IRQn] = RTC_IF_EXTWK_Handler, /* WIFI RTC external wake IRQ */
    [RTC_IF_BLACK_IRQn] = RTC_IF_BLACK_Handler, /* WIFI RTC blackout IRQ */
    [RTC_IF_BROWN_IRQn] = RTC_IF_BROWN_Handler, /* WIFI RTC brownout IRQ */
    [RTC_IF_PCNT_IRQn] = RTC_IF_PCNT_Handler, /* WIFI RTC pulse-count IRQ */
    [RTC_IF_BCF_MSR_IRQn] = RTC_IF_BCF_MSR_Handler, /* WIFI RTC bus-clock IRQ */
    [RTC_IF_RTC_ACC_IRQn] = RTC_IF_RTC_ACC_Handler, /* WIFI RTC access IRQ */
    [RTC_IF_EXP_IRQn] = RTC_IF_EXP_Handler, /* WIFI RTC mirror IRQ */
    [RTC_IF_LMR_IRQn] = RTC_IF_LMR_Handler, /* WIFI RTC load-done IRQ */
    [MRM_IRQn] = MRM_Handler, /* WIFI MRM IRQ */
    [DCACHE_MRM_IRQn] = DCACHE_MRM_Handler, /* WIFI D-cache MRM IRQ */
    [CC312_IRQn] = CC312_Handler, /* CryptoCell-312 IRQ */
    [FPLL_LOCK_IRQn] = FPLL_Lock_Handler, /* WIFI FPLL lock IRQ */
    [WIFI_HSU_IRQn] = hsu_isr, /* WIFI HSU IRQ */
    [WIFI_MACTIMER_IRQn] = rxl_mpdu_isr, /* WIFI MAC timer IRQ */
    [WIFI_MACRX_IRQn] = rxl_mpdu_isr, /* WIFI MAC RX IRQ */
    [WIFI_MACTX_IRQn] = txl_transmit_trigger, /* WIFI MAC TX IRQ */
    [WIFI_MACPROT_IRQn] = txl_prot_trigger, /* WIFI MAC protocol IRQ */
    [WIFI_MACINTGEN_IRQn] = hal_machw_gen_handler, /* WIFI MAC general IRQ */
    [WIFI_MACBCN_IRQn] = hal_machw_bcn_cancellation_handler, /* WIFI MAC beacon IRQ */
    [WIFI_RC_IRQn] = phy_rc_isr, /* WIFI radio-controller IRQ */
};
/* cppcheck-suppress-end unknownMacro */
