/*
 * Copyright (c) 2022-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_BOARD_H
#define _HPM_BOARD_H
#include <stdio.h>
#include "hpm_common.h"
#include "hpm_clock_drv.h"
#include "hpm_soc.h"
#include "hpm_soc_feature.h"
#include "pinmux.h"

#define BOARD_NAME "hpm6300evk"
#define BOARD_UF2_SIGNATURE (0x0A4D5048UL)

/* dma section */
#define BOARD_APP_XDMA HPM_XDMA
#define BOARD_APP_HDMA HPM_HDMA
#define BOARD_APP_XDMA_IRQ IRQn_XDMA
#define BOARD_APP_HDMA_IRQ IRQn_HDMA
#define BOARD_APP_DMAMUX HPM_DMAMUX

/* uart section */
#ifndef BOARD_RUNNING_CORE
#define BOARD_RUNNING_CORE HPM_CORE0
#endif
#ifndef BOARD_APP_UART_BASE
#define BOARD_APP_UART_BASE HPM_UART0
#define BOARD_APP_UART_IRQ  IRQn_UART0
#else
#ifndef BOARD_APP_UART_IRQ
#warning no IRQ specified for applicaiton uart
#endif
#endif

#define BOARD_APP_UART_BAUDRATE (115200UL)
#define BOARD_APP_UART_CLK_NAME clock_uart0

#ifndef BOARD_CONSOLE_TYPE
#define BOARD_CONSOLE_TYPE CONSOLE_TYPE_UART
#endif

#if BOARD_CONSOLE_TYPE == CONSOLE_TYPE_UART
#ifndef BOARD_CONSOLE_BASE
#if BOARD_RUNNING_CORE == HPM_CORE0
#define BOARD_CONSOLE_BASE HPM_UART0
#define BOARD_CONSOLE_CLK_NAME clock_uart0
#else
#define BOARD_CONSOLE_BASE HPM_UART13
#define BOARD_CONSOLE_CLK_NAME clock_uart13
#endif
#endif
#define BOARD_CONSOLE_BAUDRATE (115200UL)
#endif

#define BOARD_FREEMASTER_UART_BASE HPM_UART0
#define BOARD_FREEMASTER_UART_IRQ IRQn_UART0
#define BOARD_FREEMASTER_UART_CLK_NAME clock_uart0

/* uart rx idle demo section */
#define BOARD_UART_IDLE HPM_UART2
#define BOARD_UART_IDLE_DMA_SRC HPM_DMA_SRC_UART2_RX

#define BOARD_UART_IDLE_TRGM HPM_TRGM1
#define BOARD_UART_IDLE_TRGM_PIN IOC_PAD_PA24
#define BOARD_UART_IDLE_TRGM_INPUT_SRC HPM_TRGM1_INPUT_SRC_TRGM1_P4
#define BOARD_UART_IDLE_TRGM_OUTPUT_GPTMR_IN HPM_TRGM1_OUTPUT_SRC_GPTMR2_IN2
#define BOARD_UART_IDLE_TRGM_OUTPUT_GPTMR_SYNCI HPM_TRGM1_OUTPUT_SRC_GPTMR2_SYNCI

#define BOARD_UART_IDLE_GPTMR HPM_GPTMR2
#define BOARD_UART_IDLE_GPTMR_CLK_NAME clock_gptmr2
#define BOARD_UART_IDLE_GPTMR_IRQ IRQn_GPTMR2
#define BOARD_UART_IDLE_GPTMR_CMP_CH 0
#define BOARD_UART_IDLE_GPTMR_CAP_CH 2

/* sdram section */
#define BOARD_SDRAM_ADDRESS  (0x40000000UL)
#define BOARD_SDRAM_SIZE     (32*SIZE_1MB)
#define BOARD_SDRAM_CS       FEMC_SDRAM_CS0
#define BOARD_SDRAM_PORT_SIZE FEMC_SDRAM_PORT_SIZE_16_BITS
#define BOARD_SDRAM_REFRESH_COUNT (8192UL)
#define BOARD_SDRAM_REFRESH_IN_MS (64UL)
#define BOARD_SDRAM_DATA_WIDTH_IN_BYTE (4UL)


/* nor flash section */
#define BOARD_FLASH_BASE_ADDRESS (0x80000000UL)
#define BOARD_FLASH_SIZE (16 * SIZE_1MB)

/* i2c section */
#define BOARD_APP_I2C_BASE HPM_I2C0
#define BOARD_APP_I2C_CLK_NAME clock_i2c0
#define BOARD_APP_I2C_DMA HPM_HDMA
#define BOARD_APP_I2C_DMAMUX HPM_DMAMUX
#define BOARD_APP_I2C_DMA_SRC HPM_DMA_SRC_I2C0
#define BOARD_APP_I2C_DMAMUX_CH DMAMUX_MUXCFG_HDMA_MUX0

/* ACMP desction */
#define BOARD_ACMP HPM_ACMP
#define BOARD_ACMP_CHANNEL ACMP_CHANNEL_CHN1
#define BOARD_ACMP_IRQ IRQn_ACMP_1
#define BOARD_ACMP_PLUS_INPUT ACMP_INPUT_DAC_OUT /* use internal DAC */
#define BOARD_ACMP_MINUS_INPUT ACMP_INPUT_ANALOG_5 /* align with used pin */

/* dma section */
#define BOARD_APP_XDMA HPM_XDMA
#define BOARD_APP_HDMA HPM_HDMA
#define BOARD_APP_XDMA_IRQ IRQn_XDMA
#define BOARD_APP_HDMA_IRQ IRQn_HDMA
#define BOARD_APP_DMAMUX HPM_DMAMUX

/* gptmr section */
#define BOARD_GPTMR HPM_GPTMR2
#define BOARD_GPTMR_IRQ IRQn_GPTMR2
#define BOARD_GPTMR_CHANNEL 0
#define BOARD_GPTMR_PWM HPM_GPTMR2
#define BOARD_GPTMR_PWM_CHANNEL 0

/* gpio section */
#define BOARD_APP_GPIO_INDEX GPIO_DI_GPIOZ
#define BOARD_APP_GPIO_PIN 2

/* pinmux section */
#define USING_GPIO0_FOR_GPIOZ
#ifndef USING_GPIO0_FOR_GPIOZ
#define BOARD_APP_GPIO_CTRL HPM_BGPIO
#define BOARD_APP_GPIO_IRQ IRQn_BGPIO
#else
#define BOARD_APP_GPIO_CTRL HPM_GPIO0
#define BOARD_APP_GPIO_IRQ IRQn_GPIO0_Z
#endif

/* gpiom section */
#define BOARD_APP_GPIOM_BASE            HPM_GPIOM
#define BOARD_APP_GPIOM_USING_CTRL      HPM_FGPIO
#define BOARD_APP_GPIOM_USING_CTRL_NAME gpiom_core0_fast

/* spi section */
#define BOARD_APP_SPI_BASE HPM_SPI3
#define BOARD_APP_SPI_CLK_SRC_FREQ      (24000000UL)
#define BOARD_APP_SPI_SCLK_FREQ         (1562500UL)
#define BOARD_APP_SPI_ADDR_LEN_IN_BYTES (1U)
#define BOARD_APP_SPI_DATA_LEN_IN_BITS  (8U)
#define BOARD_APP_SPI_RX_DMA HPM_DMA_SRC_SPI3_RX
#define BOARD_APP_SPI_RX_DMAMUX_CH DMAMUX_MUXCFG_HDMA_MUX0
#define BOARD_APP_SPI_TX_DMA HPM_DMA_SRC_SPI3_TX
#define BOARD_APP_SPI_TX_DMAMUX_CH DMAMUX_MUXCFG_HDMA_MUX1


/* Flash section */
#define BOARD_APP_XPI_NOR_XPI_BASE            (HPM_XPI0)
#define BOARD_APP_XPI_NOR_CFG_OPT_HDR         (0xfcf90001U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT0        (0x00000007U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT1        (0x00001000U)

/* i2s section */
#define BOARD_APP_I2S_BASE HPM_I2S0
#define BOARD_APP_I2S_DATA_LINE      (2U)
#define BOARD_APP_I2S_CLK_NAME clock_i2s0

/* enet section */
#define BOARD_ENET_RMII                 HPM_ENET0
#define BOARD_ENET_RMII_RST_GPIO
#define BOARD_ENET_RMII_RST_GPIO_INDEX
#define BOARD_ENET_RMII_RST_GPIO_PIN
#define BOARD_ENET_RMII                 HPM_ENET0
#define BOARD_ENET_RMII_INT_REF_CLK     (1U)
#define BOARD_ENET_RMII_PTP_CLOCK       (clock_ptp0)
#define BOARD_ENET0_INF             (0U)  /* 0: RMII, 1: RGMII */
#define BOARD_ENET0_INT_REF_CLK     (0U)
#define BOARD_ENET0_PHY_RST_TIME    (30)


#if BOARD_ENET0_INF
#define BOARD_ENET0_TX_DLY          (0U)
#define BOARD_ENET0_RX_DLY          (0U)
#endif

#if __USE_ENET_PTP
#define BOARD_ENET0_PTP_CLOCK       (clock_ptp0)
#endif


/* ADC section */
#define BOARD_APP_ADC16_NAME "ADC0"
#define BOARD_APP_ADC16_BASE HPM_ADC0
#define BOARD_APP_ADC16_IRQn IRQn_ADC0
#define BOARD_APP_ADC16_CH                       (13U)
#define BOARD_APP_ADC_SEQ_DMA_SIZE_IN_4BYTES     (1024U)
#define BOARD_APP_ADC_PMT_DMA_SIZE_IN_4BYTES     (192U)
#define BOARD_APP_ADC_PREEMPT_TRIG_LEN           (1U)
#define BOARD_APP_ADC_SINGLE_CONV_CNT            (6)
#define BOARD_APP_ADC_TRIG_PWMT0                 HPM_PWM0
#define BOARD_APP_ADC_TRIG_PWMT1                 HPM_PWM1
#define BOARD_APP_ADC_TRIG_TRGM0                 HPM_TRGM0
#define BOARD_APP_ADC_TRIG_TRGM1                 HPM_TRGM1
#define BOARD_APP_ADC_TRIG_PWM_SYNC              HPM_SYNT

/* DAC section */
#define BOARD_DAC_BASE       HPM_DAC
#define BOARD_DAC_IRQn       IRQn_DAC
#define BOARD_DAC_CLOCK_NAME clock_dac0

/* CAN section */
#define BOARD_APP_CAN_BASE                       HPM_CAN1
#define BOARD_APP_CAN_IRQn                       IRQn_CAN1

/*
 * timer for board delay
 */
#define BOARD_DELAY_TIMER (HPM_GPTMR3)
#define BOARD_DELAY_TIMER_CH 0
#define BOARD_DELAY_TIMER_CLK_NAME (clock_gptmr3)

#define BOARD_CALLBACK_TIMER (HPM_GPTMR3)
#define BOARD_CALLBACK_TIMER_CH 1
#define BOARD_CALLBACK_TIMER_IRQ IRQn_GPTMR3
#define BOARD_CALLBACK_TIMER_CLK_NAME (clock_gptmr3)

/* SDXC section */
#define BOARD_APP_SDCARD_SDXC_BASE            (HPM_SDXC0)
#define BOARD_APP_SDCARD_CDN_GPIO_CTRL        (HPM_GPIO0)
#define BOARD_APP_SDCARD_CDN_GPIO_PIN         (15UL)
#define BOARD_APP_SDCARD_SUPPORT_1V8          (0)

/* USB section */
#define BOARD_USB0_ID_PORT       (HPM_GPIO0)
#define BOARD_USB0_ID_GPIO_INDEX (GPIO_DO_GPIOC)
#define BOARD_USB0_ID_GPIO_PIN   (23)

/*BLDC pwm*/

/*PWM define*/
#define BOARD_BLDCPWM                     HPM_PWM0
#define BOARD_BLDC_UH_PWM_OUTPIN         (0U)
#define BOARD_BLDC_UL_PWM_OUTPIN         (1U)
#define BOARD_BLDC_VH_PWM_OUTPIN         (2U)
#define BOARD_BLDC_VL_PWM_OUTPIN         (3U)
#define BOARD_BLDC_WH_PWM_OUTPIN         (4U)
#define BOARD_BLDC_WL_PWM_OUTPIN         (5U)
#define BOARD_BLDCPWM_TRGM                HPM_TRGM0
#define BOARD_BLDCAPP_PWM_IRQ             IRQn_PWM0
#define BOARD_BLDCPWM_CMP_INDEX_0         (0U)
#define BOARD_BLDCPWM_CMP_INDEX_1         (1U)
#define BOARD_BLDCPWM_CMP_INDEX_2         (2U)
#define BOARD_BLDCPWM_CMP_INDEX_3         (3U)
#define BOARD_BLDCPWM_CMP_INDEX_4         (4U)
#define BOARD_BLDCPWM_CMP_INDEX_5         (5U)

/*HALL define*/

#define BOARD_BLDC_HALL_BASE                 HPM_HALL0
#define BOARD_BLDC_HALL_TRGM                 HPM_TRGM0
#define BOARD_BLDC_HALL_IRQ                  IRQn_HALL0
#define BOARD_BLDC_HALL_TRGM_HALL_U_SRC      HPM_TRGM0_INPUT_SRC_TRGM0_IN8
#define BOARD_BLDC_HALL_TRGM_HALL_V_SRC      HPM_TRGM0_INPUT_SRC_TRGM0_IN7
#define BOARD_BLDC_HALL_TRGM_HALL_W_SRC      HPM_TRGM0_INPUT_SRC_TRGM0_IN6
#define BOARD_BLDC_HALL_MOTOR_PHASE_COUNT_PER_REV        (1000U)



/*QEI*/

#define BOARD_BLDC_QEI_BASE              HPM_QEI0
#define BOARD_BLDC_QEI_IRQ               IRQn_QEI0
#define BOARD_BLDC_QEI_TRGM              HPM_TRGM0
#define BOARD_BLDC_QEI_TRGM_QEI_A_SRC    HPM_TRGM0_INPUT_SRC_TRGM0_IN9
#define BOARD_BLDC_QEI_TRGM_QEI_B_SRC    HPM_TRGM0_INPUT_SRC_TRGM0_IN10
#define BOARD_BLDC_QEI_MOTOR_PHASE_COUNT_PER_REV     (16U)
#define BOARD_BLDC_QEI_CLOCK_SOURCE      clock_mot0
#define BOARD_BLDC_QEI_FOC_PHASE_COUNT_PER_REV       (4000U)

/*Timer define*/

#define BOARD_BLDC_TMR_1MS                       HPM_GPTMR2
#define BOARD_BLDC_TMR_CH                        0
#define BOARD_BLDC_TMR_CMP                       0
#define BOARD_BLDC_TMR_IRQ                       IRQn_GPTMR2
#define BOARD_BLDC_TMR_RELOAD                    (100000U)

/*adc*/
#define BOARD_BLDC_ADC_MODULE                  ADCX_MODULE_ADC16
#define BOARD_BLDC_ADC_U_BASE                  HPM_ADC1
#define BOARD_BLDC_ADC_V_BASE                  HPM_ADC0
#define BOARD_BLDC_ADC_W_BASE                  HPM_ADC2
#define BOARD_BLDC_ADC_TRIG_FLAG               adc16_event_trig_complete

#define BOARD_BLDC_ADC_CH_U                    (14U)
#define BOARD_BLDC_ADC_CH_V                    (12U)
#define BOARD_BLDC_ADC_CH_W                    (5U)
#define BOARD_BLDC_ADC_IRQn                    IRQn_ADC1
#define BOARD_BLDC_ADC_SEQ_DMA_SIZE_IN_4BYTES  (40U)
#define BOARD_BLDC_ADC_TRG                    ADC16_CONFIG_TRG0A
#define BOARD_BLDC_ADC_PREEMPT_TRIG_LEN        (1U)
#define BOARD_BLDC_PWM_TRIG_CMP_INDEX          (8U)
#define BOARD_BLDC_TRIGMUX_IN_NUM              HPM_TRGM0_INPUT_SRC_PWM0_CH8REF
#define BOARD_BLDC_TRG_NUM                     TRGM_TRGOCFG_ADCX_PTRGI0A

/* APP PWM */
#define BOARD_APP_PWM HPM_PWM0
#define BOARD_APP_PWM_CLOCK_NAME clock_mot0
#define BOARD_APP_PWM_OUT1 0
#define BOARD_APP_PWM_OUT2 1
#define BOARD_APP_TRGM HPM_TRGM0

#define BOARD_CPU_FREQ (480000000UL)

/* LED */
#define BOARD_LED_GPIO_CTRL HPM_GPIO0
#define BOARD_LED_GPIO_INDEX GPIO_DI_GPIOA
#define BOARD_LED_GPIO_PIN 7
#define BOARD_LED_OFF_LEVEL 1
#define BOARD_LED_ON_LEVEL 0

#ifndef BOARD_SHOW_CLOCK
#define BOARD_SHOW_CLOCK 1
#endif
#ifndef BOARD_SHOW_BANNER
#define BOARD_SHOW_BANNER 1
#endif

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

typedef void (*board_timer_cb)(void);

void board_init(void);
void board_init_console(void);

void board_init_uart(UART_Type *ptr);
void board_init_i2c(I2C_Type *ptr);

void board_init_can(CAN_Type *ptr);

uint32_t board_init_femc_clock(void);

void board_init_sdram_pins(void);
void board_init_gpio_pins(void);
void board_init_spi_pins(SPI_Type *ptr);
void board_init_led_pins(void);

void board_led_write(uint8_t state);
void board_led_toggle(void);

/* Initialize SoC overall clocks */
void board_init_clock(void);

uint32_t board_init_spi_clock(SPI_Type *ptr);

uint32_t board_init_adc16_clock(ADC16_Type *ptr);

uint32_t board_init_dac_clock(DAC_Type *ptr, bool clk_src_ahb);

void board_init_adc16_pins(void);

void board_init_dac_pins(DAC_Type *ptr);

uint32_t board_init_can_clock(CAN_Type *ptr);
uint32_t board_init_gptmr_clock(GPTMR_Type *ptr);
uint32_t board_init_i2s_clock(I2S_Type *ptr);
uint32_t board_init_pdm_clock(void);
uint32_t board_init_dao_clock(void);

void board_init_sd_pins(SDXC_Type *ptr);
uint32_t board_sd_configure_clock(SDXC_Type *ptr, uint32_t freq);
void board_sd_switch_pins_to_1v8(SDXC_Type *ptr);
bool board_sd_detect_card(SDXC_Type *ptr);
void board_sd_power_switch(SDXC_Type *ptr, bool on_off);

void board_init_usb_pins(void);
void board_usb_vbus_ctrl(uint8_t usb_index, uint8_t level);
uint8_t board_get_usb_id_status(void);

uint8_t    board_enet_get_dma_pbl(ENET_Type *ptr);
hpm_stat_t board_reset_enet_phy(ENET_Type *ptr);
hpm_stat_t board_init_enet_pins(ENET_Type *ptr);
hpm_stat_t board_init_enet_rmii_reference_clock(ENET_Type *ptr, bool internal);
hpm_stat_t board_init_enet_ptp_clock(ENET_Type *ptr);
hpm_stat_t board_enet_enable_irq(ENET_Type *ptr);
hpm_stat_t board_enet_disable_irq(ENET_Type *ptr);
/*
 * @brief Initialize PMP and PMA for but not limited to the following purposes:
 *      -- non-cacheable memory initialization
 */
void board_init_pmp(void);

void board_delay_us(uint32_t us);
void board_delay_ms(uint32_t ms);

void board_timer_create(uint32_t ms, board_timer_cb cb);
void board_ungate_mchtmr_at_lp_mode(void);

/* Initialize the UART clock */
uint32_t board_init_uart_clock(UART_Type *ptr);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _HPM_BOARD_H */
