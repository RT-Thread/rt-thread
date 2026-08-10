/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include <rtconfig.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_uart_w.h"
#include "r_spi_w.h"
#include "r_ospi_w.h"
#include "r_qspi_w.h"
#include "r_spi_flash_api.h"
#include "r_ext_irq_w.h"
#include "r_i2c_master_w.h"
#include "r_adc_w.h"
#include "r_tim_w.h"
#include "r_rtc_w.h"
#include "r_wdog_w.h"


FSP_HEADER
void user_uart0_callback(uart_callback_args_t * p_args);
extern const uart_instance_t g_uart0;
extern uart_w_instance_ctrl_t g_uart0_ctrl;
extern const uart_cfg_t g_uart0_cfg;
extern const uart_w_extended_cfg_t g_uart0_cfg_extend;

#ifdef BSP_USING_UART1
void user_uart1_callback(uart_callback_args_t * p_args);
extern const uart_instance_t g_uart1;
extern uart_w_instance_ctrl_t g_uart1_ctrl;
extern const uart_cfg_t g_uart1_cfg;
extern const uart_w_extended_cfg_t g_uart1_cfg_extend;
#endif

#ifdef BSP_USING_UART2
void user_uart2_callback(uart_callback_args_t * p_args);
extern const uart_instance_t g_uart2;
extern uart_w_instance_ctrl_t g_uart2_ctrl;
extern const uart_cfg_t g_uart2_cfg;
extern const uart_w_extended_cfg_t g_uart2_cfg_extend;
#endif

#ifdef BSP_USING_HW_I2C
void i2c_master_callback(i2c_master_callback_args_t *p_args);
#ifdef BSP_USING_HW_I2C0
extern const i2c_master_instance_t g_i2c_master0;
extern i2c_master_w_instance_ctrl_t g_i2c_master0_ctrl;
extern const i2c_master_cfg_t g_i2c_master0_cfg;
extern const i2c_master_w_extended_cfg_t g_i2c_master0_extend;
#endif

#ifdef BSP_USING_HW_I2C1
extern const i2c_master_instance_t g_i2c_master1;
extern i2c_master_w_instance_ctrl_t g_i2c_master1_ctrl;
extern const i2c_master_cfg_t g_i2c_master1_cfg;
extern const i2c_master_w_extended_cfg_t g_i2c_master1_extend;
#endif
#endif

#ifdef BSP_USING_ADC
extern const adc_instance_t g_adc0;
extern adc_w_instance_ctrl_t g_adc0_ctrl;
extern const adc_cfg_t g_adc0_cfg;
extern const adc_w_scan_cfg_t g_adc0_channel_cfg;
extern const adc_w_extended_cfg_t g_adc0_cfg_extend;
#endif

#ifdef BSP_USING_TIM0
void timer0_callback(timer_callback_args_t * p_args);
extern const timer_instance_t g_timer0;
extern tim_w_instance_ctrl_t g_timer0_ctrl;
extern const timer_cfg_t g_timer0_cfg;
extern const tim_w_extended_cfg_t g_timer0_extend;
#endif

#ifdef BSP_USING_TIM1
void timer1_callback(timer_callback_args_t * p_args);
extern const timer_instance_t g_timer1;
extern tim_w_instance_ctrl_t g_timer1_ctrl;
extern const timer_cfg_t g_timer1_cfg;
extern const tim_w_extended_cfg_t g_timer1_extend;
#endif

#ifdef BSP_USING_TIM2
void timer2_callback(timer_callback_args_t * p_args);
extern const timer_instance_t g_timer2;
extern tim_w_instance_ctrl_t g_timer2_ctrl;
extern const timer_cfg_t g_timer2_cfg;
extern const tim_w_extended_cfg_t g_timer2_extend;
#endif

#ifdef BSP_USING_TIM3
void timer3_callback(timer_callback_args_t * p_args);
extern const timer_instance_t g_timer3;
extern tim_w_instance_ctrl_t g_timer3_ctrl;
extern const timer_cfg_t g_timer3_cfg;
extern const tim_w_extended_cfg_t g_timer3_extend;
#endif

#ifdef BSP_USING_TIM4
void timer4_callback(timer_callback_args_t * p_args);
extern const timer_instance_t g_timer4;
extern tim_w_instance_ctrl_t g_timer4_ctrl;
extern const timer_cfg_t g_timer4_cfg;
extern const tim_w_extended_cfg_t g_timer4_extend;
#endif

#ifdef BSP_USING_TIM5
void timer5_callback(timer_callback_args_t * p_args);
extern const timer_instance_t g_timer5;
extern tim_w_instance_ctrl_t g_timer5_ctrl;
extern const timer_cfg_t g_timer5_cfg;
extern const tim_w_extended_cfg_t g_timer5_extend;
#endif

#ifdef BSP_USING_TIM6
void timer6_callback(timer_callback_args_t * p_args);
extern const timer_instance_t g_timer6;
extern tim_w_instance_ctrl_t g_timer6_ctrl;
extern const timer_cfg_t g_timer6_cfg;
extern const tim_w_extended_cfg_t g_timer6_extend;
#endif

#ifdef BSP_USING_TIM7
void timer7_callback(timer_callback_args_t * p_args);
extern const timer_instance_t g_timer7;
extern tim_w_instance_ctrl_t g_timer7_ctrl;
extern const timer_cfg_t g_timer7_cfg;
extern const tim_w_extended_cfg_t g_timer7_extend;
#endif

#ifdef BSP_USING_QSPI_PSRAM
extern const spi_flash_instance_t g_qspi_ram0;
extern qspi_w_instance_ctrl_t g_qspi_ram0_ctrl;
extern const spi_flash_cfg_t g_qspi_ram0_cfg;
#endif

#ifdef BSP_USING_SPI0
void spi0_callback(spi_callback_args_t * p_args);
extern const spi_instance_t g_spi0;
extern spi_w_instance_ctrl_t g_spi0_ctrl;
extern const spi_cfg_t g_spi0_cfg;
extern spi_w_extended_cfg_t g_spi0_cfg_extend;
#endif

#ifdef BSP_USING_SPI1
void spi1_callback(spi_callback_args_t * p_args);
extern const spi_instance_t g_spi1;
extern spi_w_instance_ctrl_t g_spi1_ctrl;
extern const spi_cfg_t g_spi1_cfg;
extern spi_w_extended_cfg_t g_spi1_cfg_extend;
#endif

#ifdef BSP_USING_OSPI_FLASH
extern ospi_w_instance_ctrl_t g_ospi_flash_ctrl;
extern spi_flash_cfg_t g_ospi_flash_cfg;
#endif

#ifdef BSP_USING_ONCHIP_RTC
extern rtc_w_instance_ctrl_t g_rtc_w_ctrl;
extern const rtc_cfg_t g_rtc_w_cfg;
extern const rtc_instance_t g_rtc_w;
#endif

#ifdef BSP_USING_WDT
extern wdog_w_instance_ctrl_t g_wdog_w_ctrl;
extern const wdt_cfg_t g_wdog_w_cfg;
extern const wdt_instance_t g_wdog_w;
#endif

void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
