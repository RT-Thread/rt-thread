/* generated HAL source file - do not edit */
#include "hal_data.h"
#include "vector_data.h"

uart_w_instance_ctrl_t g_uart0_ctrl;

uart_w_baud_setting_t g_uart0_baud_setting =
{
    .fra_baud = 26,
    .int_baud = 43,
};

const uart_w_extended_cfg_t g_uart0_cfg_extend =
{
    .p_baud_setting = &g_uart0_baud_setting,
    .loop_back_enable = UART_W_LOOP_BACK_DISABLE,
    .fifo_enable = UART_W_FIFO_ENABLE,
    .rx_fifo_trigger = UART_W_RX_FIFO_TRIGGER_SEVEN_EIGHTHS,
    .tx_fifo_trigger = UART_W_TX_FIFO_TRIGGER_EIGHTH,
    .flow_control = UART_W_AUTO_FLOW_CONTROL_DISABLED,
    .rs485_enable = UART_W_RS485_DISABLE,
};

const uart_cfg_t g_uart0_cfg =
{
    .channel = 1 - UART_W_CHANNEL_OFFSET,
    .data_bits = UART_W_DATA_BITS_8,
    .parity = UART_PARITY_OFF,
    .stop_bits = UART_STOP_BITS_1,
    .p_callback = user_uart0_callback,
    .p_context = NULL,
    .p_extend = &g_uart0_cfg_extend,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = DEFAULT_UART_W_IRQ_PRIORITY,
#if defined(VECTOR_NUMBER_UARTW0_IRQ)
    .rxi_irq = VECTOR_NUMBER_UARTW0_IRQ,
#else
    .rxi_irq = FSP_INVALID_VECTOR,
#endif
};

const uart_instance_t g_uart0 =
{
    .p_ctrl = &g_uart0_ctrl,
    .p_cfg = &g_uart0_cfg,
    .p_api = &g_uart_on_uart_w,
};

#ifdef BSP_USING_UART1
uart_w_instance_ctrl_t g_uart1_ctrl;

uart_w_baud_setting_t g_uart1_baud_setting =
{
    .fra_baud = 26,
    .int_baud = 43,
};

const uart_w_extended_cfg_t g_uart1_cfg_extend =
{
    .p_baud_setting = &g_uart1_baud_setting,
    .loop_back_enable = UART_W_LOOP_BACK_DISABLE,
    .fifo_enable = UART_W_FIFO_ENABLE,
    .rx_fifo_trigger = UART_W_RX_FIFO_TRIGGER_SEVEN_EIGHTHS,
    .tx_fifo_trigger = UART_W_TX_FIFO_TRIGGER_EIGHTH,
    .flow_control = UART_W_AUTO_FLOW_CONTROL_DISABLED,
    .rs485_enable = UART_W_RS485_DISABLE,
};

const uart_cfg_t g_uart1_cfg =
{
    .channel = 2 - UART_W_CHANNEL_OFFSET,
    .data_bits = UART_W_DATA_BITS_8,
    .parity = UART_PARITY_OFF,
    .stop_bits = UART_STOP_BITS_1,
    .p_callback = user_uart1_callback,
    .p_context = NULL,
    .p_extend = &g_uart1_cfg_extend,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = DEFAULT_UART_W_IRQ_PRIORITY,
#if defined(VECTOR_NUMBER_UARTW1_IRQ)
    .rxi_irq = VECTOR_NUMBER_UARTW1_IRQ,
#else
    .rxi_irq = FSP_INVALID_VECTOR,
#endif
};

const uart_instance_t g_uart1 =
{
    .p_ctrl = &g_uart1_ctrl,
    .p_cfg = &g_uart1_cfg,
    .p_api = &g_uart_on_uart_w,
};
#endif

#ifdef BSP_USING_UART2

#define RA6W1_UART2_CALLBACK       user_uart2_callback
#define RA6W1_UART2_FLOW_CONTROL   UART_W_AUTO_FLOW_CONTROL_DISABLED
#define RA6W1_UART2_RXI_IPL        DEFAULT_UART_W_IRQ_PRIORITY

uart_w_instance_ctrl_t g_uart2_ctrl;

uart_w_baud_setting_t g_uart2_baud_setting =
{
    .fra_baud = 26,
    .int_baud = 43,
};

const uart_w_extended_cfg_t g_uart2_cfg_extend =
{
    .p_baud_setting = &g_uart2_baud_setting,
    .loop_back_enable = UART_W_LOOP_BACK_DISABLE,
    .fifo_enable = UART_W_FIFO_ENABLE,
    .rx_fifo_trigger = UART_W_RX_FIFO_TRIGGER_SEVEN_EIGHTHS,
    .tx_fifo_trigger = UART_W_TX_FIFO_TRIGGER_EIGHTH,
    .flow_control = RA6W1_UART2_FLOW_CONTROL,
    .rs485_enable = UART_W_RS485_DISABLE,
};

const uart_cfg_t g_uart2_cfg =
{
    .channel = 3 - UART_W_CHANNEL_OFFSET,
    .data_bits = UART_W_DATA_BITS_8,
    .parity = UART_PARITY_OFF,
    .stop_bits = UART_STOP_BITS_1,
    .p_callback = RA6W1_UART2_CALLBACK,
    .p_context = NULL,
    .p_extend = &g_uart2_cfg_extend,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = RA6W1_UART2_RXI_IPL,
#if defined(VECTOR_NUMBER_UARTW2_IRQ)
    .rxi_irq = VECTOR_NUMBER_UARTW2_IRQ,
#else
    .rxi_irq = FSP_INVALID_VECTOR,
#endif
};

const uart_instance_t g_uart2 =
{
    .p_ctrl = &g_uart2_ctrl,
    .p_cfg = &g_uart2_cfg,
    .p_api = &g_uart_on_uart_w,
};
#undef RA6W1_UART2_CALLBACK
#undef RA6W1_UART2_FLOW_CONTROL
#undef RA6W1_UART2_RXI_IPL
#endif

#ifdef BSP_USING_ADC
#define RA6W1_ADC_SCAN_MASK    ((1U << BSP_USING_ADC_PIN_NUM) - 1U)

adc_w_instance_ctrl_t g_adc0_ctrl;

static const adc_w_channel_cfg_t g_adc0_channel_cfg_default =
{
    .interrupt_mode_fifo = ADC_W_INTERRUPT_FIFO_NONE,
    .interrupt_mode_thd = ADC_W_INTERRUPT_THD_NONE,
    .dma_en = ADC_W_DMA_DISABLED,
    .sensorwakeup_en = ADC_W_SENSOR_WAKEUP_DISABLED,
    .thd_value = 0,
    .threshold_mode = ADC_W_SENSOR_WAKEUP_THD_OVER,
};

const adc_w_extended_cfg_t g_adc0_cfg_extend =
{
    .conversion_clockdiv = 3,
    .upper_bound_limit = 0x0FFF,
    .lower_bound_limit = 0,
    .p_channel_cfgs =
    {
        &g_adc0_channel_cfg_default,
        &g_adc0_channel_cfg_default,
        &g_adc0_channel_cfg_default,
        &g_adc0_channel_cfg_default,
    },
    .timer_count_clock_source = ADC_W_TIMER_COUNT_SOURCE_1000,
    .timer_value = 1,
    .sample_average = ADC_W_SAMPLE_AVERAGE_4,
};

const adc_w_scan_cfg_t g_adc0_channel_cfg =
{
    .scan_mask = RA6W1_ADC_SCAN_MASK,
};

const adc_cfg_t g_adc0_cfg =
{
    .unit = 0,
    .mode = ADC_MODE_CONTINUOUS_SCAN,
    .resolution = ADC_RESOLUTION_12_BIT,
    .alignment = ADC_ALIGNMENT_RIGHT,
    .trigger = ADC_TRIGGER_SOFTWARE,
    .scan_end_irq = FSP_INVALID_VECTOR,
    .scan_end_b_irq = FSP_INVALID_VECTOR,
    .scan_end_c_irq = FSP_INVALID_VECTOR,
    .scan_end_ipl = BSP_IRQ_DISABLED,
    .scan_end_b_ipl = BSP_IRQ_DISABLED,
    .scan_end_c_ipl = BSP_IRQ_DISABLED,
    .p_callback = NULL,
    .p_context = NULL,
    .p_extend = &g_adc0_cfg_extend,
};

const adc_instance_t g_adc0 =
{
    .p_ctrl = &g_adc0_ctrl,
    .p_cfg = &g_adc0_cfg,
    .p_channel_cfg = &g_adc0_channel_cfg,
    .p_api = &g_adc_on_adc_w,
};
#endif

#ifdef BSP_USING_TIM_W
#define RA6W1_TIM_DEFAULT_SOURCE_DIV         TIMER_SOURCE_DIV_32
#define RA6W1_TIM_DEFAULT_PERIOD_COUNTS     ((BSP_CFG_XTALM_HZ / 32U) / 1000U)
#define RA6W1_TIM_PWM_PERIOD_COUNTS         (1000U)
#define RA6W1_TIM_PWM_DUTY_COUNTS           (500U)

#define RA6W1_TIM_MODE(num)                 RA6W1_TIM_MODE_I(num)
#define RA6W1_TIM_MODE_I(num)               RA6W1_TIM_MODE_##num
#define RA6W1_TIM_PERIOD(num)               RA6W1_TIM_PERIOD_I(num)
#define RA6W1_TIM_PERIOD_I(num)             RA6W1_TIM_PERIOD_##num
#define RA6W1_TIM_DUTY(num)                 RA6W1_TIM_DUTY_I(num)
#define RA6W1_TIM_DUTY_I(num)               RA6W1_TIM_DUTY_##num
#define RA6W1_TIM_IRQ(num)                  RA6W1_TIM_IRQ_I(num)
#define RA6W1_TIM_IRQ_I(num)                RA6W1_TIM_IRQ_##num
#define RA6W1_TIM_CALLBACK(num)             RA6W1_TIM_CALLBACK_I(num)
#define RA6W1_TIM_CALLBACK_I(num)           RA6W1_TIM_CALLBACK_##num

#ifdef BSP_USING_PWM0
#define RA6W1_TIM_MODE_0                   TIMER_MODE_PWM
#define RA6W1_TIM_PERIOD_0                 RA6W1_TIM_PWM_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_0                   RA6W1_TIM_PWM_DUTY_COUNTS
#define RA6W1_TIM_IRQ_0                    FSP_INVALID_VECTOR
#define RA6W1_TIM_CALLBACK_0               NULL
#else
#define RA6W1_TIM_MODE_0                   TIMER_MODE_PERIODIC
#define RA6W1_TIM_PERIOD_0                 RA6W1_TIM_DEFAULT_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_0                   0U
#define RA6W1_TIM_IRQ_0                    VECTOR_NUMBER_TIMW0_IRQ
#define RA6W1_TIM_CALLBACK_0               timer0_callback
#endif

#ifdef BSP_USING_PWM1
#define RA6W1_TIM_MODE_1                   TIMER_MODE_PWM
#define RA6W1_TIM_PERIOD_1                 RA6W1_TIM_PWM_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_1                   RA6W1_TIM_PWM_DUTY_COUNTS
#define RA6W1_TIM_IRQ_1                    FSP_INVALID_VECTOR
#define RA6W1_TIM_CALLBACK_1               NULL
#else
#define RA6W1_TIM_MODE_1                   TIMER_MODE_PERIODIC
#define RA6W1_TIM_PERIOD_1                 RA6W1_TIM_DEFAULT_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_1                   0U
#define RA6W1_TIM_IRQ_1                    VECTOR_NUMBER_TIMW1_IRQ
#define RA6W1_TIM_CALLBACK_1               timer1_callback
#endif

#ifdef BSP_USING_PWM2
#define RA6W1_TIM_MODE_2                   TIMER_MODE_PWM
#define RA6W1_TIM_PERIOD_2                 RA6W1_TIM_PWM_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_2                   RA6W1_TIM_PWM_DUTY_COUNTS
#define RA6W1_TIM_IRQ_2                    FSP_INVALID_VECTOR
#define RA6W1_TIM_CALLBACK_2               NULL
#else
#define RA6W1_TIM_MODE_2                   TIMER_MODE_PERIODIC
#define RA6W1_TIM_PERIOD_2                 RA6W1_TIM_DEFAULT_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_2                   0U
#define RA6W1_TIM_IRQ_2                    VECTOR_NUMBER_TIMW2_IRQ
#define RA6W1_TIM_CALLBACK_2               timer2_callback
#endif

#ifdef BSP_USING_PWM3
#define RA6W1_TIM_MODE_3                   TIMER_MODE_PWM
#define RA6W1_TIM_PERIOD_3                 RA6W1_TIM_PWM_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_3                   RA6W1_TIM_PWM_DUTY_COUNTS
#define RA6W1_TIM_IRQ_3                    FSP_INVALID_VECTOR
#define RA6W1_TIM_CALLBACK_3               NULL
#else
#define RA6W1_TIM_MODE_3                   TIMER_MODE_PERIODIC
#define RA6W1_TIM_PERIOD_3                 RA6W1_TIM_DEFAULT_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_3                   0U
#define RA6W1_TIM_IRQ_3                    VECTOR_NUMBER_TIMW3_IRQ
#define RA6W1_TIM_CALLBACK_3               timer3_callback
#endif

#ifdef BSP_USING_PWM4
#define RA6W1_TIM_MODE_4                   TIMER_MODE_PWM
#define RA6W1_TIM_PERIOD_4                 RA6W1_TIM_PWM_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_4                   RA6W1_TIM_PWM_DUTY_COUNTS
#define RA6W1_TIM_IRQ_4                    FSP_INVALID_VECTOR
#define RA6W1_TIM_CALLBACK_4               NULL
#else
#define RA6W1_TIM_MODE_4                   TIMER_MODE_PERIODIC
#define RA6W1_TIM_PERIOD_4                 RA6W1_TIM_DEFAULT_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_4                   0U
#define RA6W1_TIM_IRQ_4                    VECTOR_NUMBER_TIMW4_IRQ
#define RA6W1_TIM_CALLBACK_4               timer4_callback
#endif

#ifdef BSP_USING_PWM5
#define RA6W1_TIM_MODE_5                   TIMER_MODE_PWM
#define RA6W1_TIM_PERIOD_5                 RA6W1_TIM_PWM_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_5                   RA6W1_TIM_PWM_DUTY_COUNTS
#define RA6W1_TIM_IRQ_5                    FSP_INVALID_VECTOR
#define RA6W1_TIM_CALLBACK_5               NULL
#else
#define RA6W1_TIM_MODE_5                   TIMER_MODE_PERIODIC
#define RA6W1_TIM_PERIOD_5                 RA6W1_TIM_DEFAULT_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_5                   0U
#define RA6W1_TIM_IRQ_5                    VECTOR_NUMBER_TIMW5_IRQ
#define RA6W1_TIM_CALLBACK_5               timer5_callback
#endif

#ifdef BSP_USING_PWM6
#define RA6W1_TIM_MODE_6                   TIMER_MODE_PWM
#define RA6W1_TIM_PERIOD_6                 RA6W1_TIM_PWM_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_6                   RA6W1_TIM_PWM_DUTY_COUNTS
#define RA6W1_TIM_IRQ_6                    FSP_INVALID_VECTOR
#define RA6W1_TIM_CALLBACK_6               NULL
#else
#define RA6W1_TIM_MODE_6                   TIMER_MODE_PERIODIC
#define RA6W1_TIM_PERIOD_6                 RA6W1_TIM_DEFAULT_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_6                   0U
#define RA6W1_TIM_IRQ_6                    VECTOR_NUMBER_TIMW6_IRQ
#define RA6W1_TIM_CALLBACK_6               timer6_callback
#endif

#ifdef BSP_USING_PWM7
#define RA6W1_TIM_MODE_7                   TIMER_MODE_PWM
#define RA6W1_TIM_PERIOD_7                 RA6W1_TIM_PWM_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_7                   RA6W1_TIM_PWM_DUTY_COUNTS
#define RA6W1_TIM_IRQ_7                    FSP_INVALID_VECTOR
#define RA6W1_TIM_CALLBACK_7               NULL
#else
#define RA6W1_TIM_MODE_7                   TIMER_MODE_PERIODIC
#define RA6W1_TIM_PERIOD_7                 RA6W1_TIM_DEFAULT_PERIOD_COUNTS
#define RA6W1_TIM_DUTY_7                   0U
#define RA6W1_TIM_IRQ_7                    VECTOR_NUMBER_TIMW7_IRQ
#define RA6W1_TIM_CALLBACK_7               timer7_callback
#endif

#define RA6W1_TIM_INSTANCE_DEFINE(num, tim_channel, irq_vector)             \
    tim_w_instance_ctrl_t g_timer##num##_ctrl;                              \
                                                                            \
    const tim_w_extended_cfg_t g_timer##num##_extend =                      \
    {                                                                       \
        .free_run = false,                                                  \
        .count_source = TIM_W_CLOCK_DIVN,                                   \
        .direction = TIMER_DIRECTION_UP,                                    \
        .pwm_sync_map = 0,                                                  \
        .gpio_source = BSP_IO_PORT_00_PIN_00,                               \
        .gpio_trigger = TIM_W_GPIO_TRIGGER_DISABLED,                        \
        .oneshot_switch_to_periodic = false,                                \
        .oneshot_delay = 0,                                                 \
        .p_ccm_cfg = NULL,                                                  \
    };                                                                      \
                                                                            \
    const timer_cfg_t g_timer##num##_cfg =                                  \
    {                                                                       \
        .mode = RA6W1_TIM_MODE(num),                                        \
        .period_counts = RA6W1_TIM_PERIOD(num),                             \
        .source_div = (timer_source_div_t) RA6W1_TIM_DEFAULT_SOURCE_DIV,     \
        .duty_cycle_counts = RA6W1_TIM_DUTY(num),                           \
        .channel = (tim_channel),                                           \
        .cycle_end_ipl = 12,                                                \
        .cycle_end_irq = RA6W1_TIM_IRQ(num),                                \
        .p_callback = RA6W1_TIM_CALLBACK(num),                              \
        .p_context = NULL,                                                  \
        .p_extend = &g_timer##num##_extend,                                 \
    };                                                                      \
                                                                            \
    const timer_instance_t g_timer##num =                                   \
    {                                                                       \
        .p_ctrl = &g_timer##num##_ctrl,                                     \
        .p_cfg = &g_timer##num##_cfg,                                       \
        .p_api = &g_timer_on_tim_w,                                         \
    };

#ifdef BSP_USING_TIM0
RA6W1_TIM_INSTANCE_DEFINE(0, TIM_W_TIM1, VECTOR_NUMBER_TIMW0_IRQ)
#endif
#ifdef BSP_USING_TIM1
RA6W1_TIM_INSTANCE_DEFINE(1, TIM_W_TIM2, VECTOR_NUMBER_TIMW1_IRQ)
#endif
#ifdef BSP_USING_TIM2
RA6W1_TIM_INSTANCE_DEFINE(2, TIM_W_TIM3, VECTOR_NUMBER_TIMW2_IRQ)
#endif
#ifdef BSP_USING_TIM3
RA6W1_TIM_INSTANCE_DEFINE(3, TIM_W_TIM4, VECTOR_NUMBER_TIMW3_IRQ)
#endif
#ifdef BSP_USING_TIM4
RA6W1_TIM_INSTANCE_DEFINE(4, TIM_W_TIM5, VECTOR_NUMBER_TIMW4_IRQ)
#endif
#ifdef BSP_USING_TIM5
RA6W1_TIM_INSTANCE_DEFINE(5, TIM_W_TIM6, VECTOR_NUMBER_TIMW5_IRQ)
#endif
#ifdef BSP_USING_TIM6
RA6W1_TIM_INSTANCE_DEFINE(6, TIM_W_TIM7, VECTOR_NUMBER_TIMW6_IRQ)
#endif
#ifdef BSP_USING_TIM7
RA6W1_TIM_INSTANCE_DEFINE(7, TIM_W_TIM8, VECTOR_NUMBER_TIMW7_IRQ)
#endif

#undef RA6W1_TIM_INSTANCE_DEFINE
#undef RA6W1_TIM_MODE
#undef RA6W1_TIM_MODE_I
#undef RA6W1_TIM_PERIOD
#undef RA6W1_TIM_PERIOD_I
#undef RA6W1_TIM_DUTY
#undef RA6W1_TIM_DUTY_I
#undef RA6W1_TIM_IRQ
#undef RA6W1_TIM_IRQ_I
#undef RA6W1_TIM_CALLBACK
#undef RA6W1_TIM_CALLBACK_I
#undef RA6W1_TIM_PWM_PERIOD_COUNTS
#undef RA6W1_TIM_PWM_DUTY_COUNTS
#undef RA6W1_TIM_DEFAULT_SOURCE_DIV
#undef RA6W1_TIM_DEFAULT_PERIOD_COUNTS
#endif /* BSP_USING_TIM_W */

#ifdef BSP_USING_HW_I2C0

#if defined(BSP_I2C0_RATE_STANDARD)
/* 100 kHz: tLOW=4.77 us, tHIGH=5.22 us */
#define I2C0_MASTER_RATE       I2C_MASTER_RATE_STANDARD
#define I2C0_MASTER_SCL_LCNT   187
#define I2C0_MASTER_SCL_HCNT   205

#elif defined(BSP_I2C0_RATE_FAST)
/* 400 kHz: tLOW=1.38 us, tHIGH=1.14 us */
#define I2C0_MASTER_RATE       I2C_MASTER_RATE_FAST
#define I2C0_MASTER_SCL_LCNT   51
#define I2C0_MASTER_SCL_HCNT   41

#elif defined(BSP_I2C0_RATE_FASTPLUS)
/* 1 MHz: tLOW=580 ns, tHIGH=448 ns */
#define I2C0_MASTER_RATE       I2C_MASTER_RATE_FASTPLUS
#define I2C0_MASTER_SCL_LCNT   19
#define I2C0_MASTER_SCL_HCNT   13

#elif defined(BSP_I2C0_RATE_HIGHSPEED)
#error "40 MHz I2C source cannot generate 3.4 MHz with the minimum HCNT/LCNT"
#else
#error "Select one BSP_I2C0_RATE_xxx option"
#endif

i2c_master_w_instance_ctrl_t g_i2c_master0_ctrl;

const i2c_master_w_extended_cfg_t g_i2c_master0_extend =
{
#if (I2C_MASTER_W_CFG_DMA_ENABLE)
    .enable_dma_bursts_tx = 0,
    .enable_dma_bursts_rx = 0,
#endif
    .select_divn = BSP_CFG_I2C1CLK_SOURCE,
#if defined(VECTOR_NUMBER_I2CW0_IRQ)
    .gen_irq = VECTOR_NUMBER_I2CW0_IRQ,
#else
    .gen_irq = FSP_INVALID_VECTOR,
#endif
    .gen_ipl = 12,

    .clock_settings.scl_lcnt = I2C0_MASTER_SCL_LCNT,
    .clock_settings.scl_hcnt = I2C0_MASTER_SCL_HCNT,
};

const i2c_master_cfg_t g_i2c_master0_cfg =
{
    .channel = 1 - I2C_MASTER_W_CHANNEL_OFFSET,
    .rate = I2C0_MASTER_RATE,
    .slave = 0x1D,
    .addr_mode = I2C_MASTER_ADDR_MODE_7BIT,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .p_callback = i2c_master_callback,
    .p_context = NULL,
#if defined(VECTOR_NUMBER_I2CW0_RX_IRQ)
    .rxi_irq = VECTOR_NUMBER_I2CW0_RX_IRQ,
#else
    .rxi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_I2CW0_TXE_IRQ)
    .txi_irq = VECTOR_NUMBER_I2CW0_TXE_IRQ,
#else
    .txi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_I2CW0_TXR_IRQ)
    .tei_irq = VECTOR_NUMBER_I2CW0_TXR_IRQ,
#else
    .tei_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_I2CW0_ERR_IRQ)
    .eri_irq = VECTOR_NUMBER_I2CW0_ERR_IRQ,
#else
    .eri_irq = FSP_INVALID_VECTOR,
#endif
    .ipl = BSP_IRQ_DISABLED,
    .p_extend = &g_i2c_master0_extend,
};

const i2c_master_instance_t g_i2c_master0 =
{
    .p_ctrl = &g_i2c_master0_ctrl,
    .p_cfg = &g_i2c_master0_cfg,
    .p_api = &g_i2c_master_on_i2c_w,
};
#endif

#ifdef BSP_USING_HW_I2C1

#if defined(BSP_I2C1_RATE_STANDARD)
/* 100 kHz: tLOW=4.77 us, tHIGH=5.22 us */
#define I2C1_MASTER_RATE       I2C_MASTER_RATE_STANDARD
#define I2C1_MASTER_SCL_LCNT   187
#define I2C1_MASTER_SCL_HCNT   205

#elif defined(BSP_I2C1_RATE_FAST)
/* 400 kHz: tLOW=1.38 us, tHIGH=1.14 us */
#define I2C1_MASTER_RATE       I2C_MASTER_RATE_FAST
#define I2C1_MASTER_SCL_LCNT   51
#define I2C1_MASTER_SCL_HCNT   41

#elif defined(BSP_I2C1_RATE_FASTPLUS)
/* 1 MHz: tLOW=580 ns, tHIGH=448 ns */
#define I2C1_MASTER_RATE       I2C_MASTER_RATE_FASTPLUS
#define I2C1_MASTER_SCL_LCNT   19
#define I2C1_MASTER_SCL_HCNT   13

#elif defined(BSP_I2C1_RATE_HIGHSPEED)
#error "40 MHz I2C source cannot generate 3.4 MHz with the minimum HCNT/LCNT"
#else
#error "Select one BSP_I2C1_RATE_xxx option"
#endif

i2c_master_w_instance_ctrl_t g_i2c_master1_ctrl;

const i2c_master_w_extended_cfg_t g_i2c_master1_extend =
{
#if (I2C_MASTER_W_CFG_DMA_ENABLE)
    .enable_dma_bursts_tx = 0,
    .enable_dma_bursts_rx = 0,
#endif
    .select_divn = BSP_CFG_I2C2CLK_SOURCE,
#if defined(VECTOR_NUMBER_I2CW1_IRQ)
    .gen_irq = VECTOR_NUMBER_I2CW1_IRQ,
#else
    .gen_irq = FSP_INVALID_VECTOR,
#endif
    .gen_ipl = 12,

    .clock_settings.scl_lcnt = I2C1_MASTER_SCL_LCNT,
    .clock_settings.scl_hcnt = I2C1_MASTER_SCL_HCNT,
};

const i2c_master_cfg_t g_i2c_master1_cfg =
{
    .channel = 2 - I2C_MASTER_W_CHANNEL_OFFSET,
    .rate = I2C1_MASTER_RATE,
    .slave = 0x1D,
    .addr_mode = I2C_MASTER_ADDR_MODE_7BIT,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .p_callback = i2c_master_callback,
    .p_context = NULL,
#if defined(VECTOR_NUMBER_I2CW1_RX_IRQ)
    .rxi_irq = VECTOR_NUMBER_I2CW1_RX_IRQ,
#else
    .rxi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_I2CW1_TXE_IRQ)
    .txi_irq = VECTOR_NUMBER_I2CW1_TXE_IRQ,
#else
    .txi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_I2CW1_TXR_IRQ)
    .tei_irq = VECTOR_NUMBER_I2CW1_TXR_IRQ,
#else
    .tei_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_I2CW1_ERR_IRQ)
    .eri_irq = VECTOR_NUMBER_I2CW1_ERR_IRQ,
#else
    .eri_irq = FSP_INVALID_VECTOR,
#endif
    .ipl = BSP_IRQ_DISABLED,
    .p_extend = &g_i2c_master1_extend,
};

const i2c_master_instance_t g_i2c_master1 =
{
    .p_ctrl = &g_i2c_master1_ctrl,
    .p_cfg = &g_i2c_master1_cfg,
    .p_api = &g_i2c_master_on_i2c_w,
};
#endif

#ifdef BSP_USING_SPI0
spi_w_instance_ctrl_t g_spi0_ctrl;

spi_w_extended_cfg_t g_spi0_cfg_extend =
{
    .spck_div = 0,
    .byte_swap = SPI_W_BYTE_SWAP_DISABLE,
    .cap_edge = SPI_W_CAPTURE_CURRENT_EDGE,
    .cs_select = SPI_W_CS_SELECT_CS0,
    .rx_fifo_lvl_thres = 1,
    .tx_fifo_lvl_thres = 1,
#if defined(VECTOR_NUMBER_SPIW0_IRQ)
    .gen_irq = VECTOR_NUMBER_SPIW0_IRQ,
#else
    .gen_irq = FSP_INVALID_VECTOR,
#endif
    .gen_ipl = 4,
#if SPI_W_CFG_FAST_MODE_ENABLE
    .skip_disable = false,
#endif
    .skip_busy_check = false,
};

const spi_cfg_t g_spi0_cfg =
{
    .channel = 0,
    .rxi_irq = FSP_INVALID_VECTOR,
    .txi_irq = FSP_INVALID_VECTOR,
    .tei_irq = FSP_INVALID_VECTOR,
    .eri_irq = FSP_INVALID_VECTOR,
    .rxi_ipl = BSP_IRQ_DISABLED,
    .txi_ipl = BSP_IRQ_DISABLED,
    .tei_ipl = BSP_IRQ_DISABLED,
    .eri_ipl = BSP_IRQ_DISABLED,
    .operating_mode = SPI_MODE_MASTER,
    .clk_phase = SPI_CLK_PHASE_EDGE_ODD,
    .clk_polarity = SPI_CLK_POLARITY_LOW,
    .mode_fault = SPI_MODE_FAULT_ERROR_DISABLE,
    .bit_order = SPI_BIT_ORDER_MSB_FIRST,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .p_callback = spi0_callback,
    .p_context = NULL,
    .p_extend = &g_spi0_cfg_extend,
};

const spi_instance_t g_spi0 =
{
    .p_ctrl = &g_spi0_ctrl,
    .p_cfg = &g_spi0_cfg,
    .p_api = &g_spi_on_spi_w,
};
#endif

#ifdef BSP_USING_SPI1
spi_w_instance_ctrl_t g_spi1_ctrl;

spi_w_extended_cfg_t g_spi1_cfg_extend =
{
    .spck_div = 0,
    .byte_swap = SPI_W_BYTE_SWAP_DISABLE,
    .cap_edge = SPI_W_CAPTURE_CURRENT_EDGE,
    .cs_select = SPI_W_CS_SELECT_CS0,
    .rx_fifo_lvl_thres = 1,
    .tx_fifo_lvl_thres = 1,
#if defined(VECTOR_NUMBER_SPIW1_IRQ)
    .gen_irq = VECTOR_NUMBER_SPIW1_IRQ,
#else
    .gen_irq = FSP_INVALID_VECTOR,
#endif
    .gen_ipl = 4,
#if SPI_W_CFG_FAST_MODE_ENABLE
    .skip_disable = false,
#endif
    .skip_busy_check = false,
};

const spi_cfg_t g_spi1_cfg =
{
    .channel = 1,
    .rxi_irq = FSP_INVALID_VECTOR,
    .txi_irq = FSP_INVALID_VECTOR,
    .tei_irq = FSP_INVALID_VECTOR,
    .eri_irq = FSP_INVALID_VECTOR,
    .rxi_ipl = BSP_IRQ_DISABLED,
    .txi_ipl = BSP_IRQ_DISABLED,
    .tei_ipl = BSP_IRQ_DISABLED,
    .eri_ipl = BSP_IRQ_DISABLED,
    .operating_mode = SPI_MODE_MASTER,
    .clk_phase = SPI_CLK_PHASE_EDGE_ODD,
    .clk_polarity = SPI_CLK_POLARITY_LOW,
    .mode_fault = SPI_MODE_FAULT_ERROR_DISABLE,
    .bit_order = SPI_BIT_ORDER_MSB_FIRST,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .p_callback = spi1_callback,
    .p_context = NULL,
    .p_extend = &g_spi1_cfg_extend,
};

const spi_instance_t g_spi1 =
{
    .p_ctrl = &g_spi1_ctrl,
    .p_cfg = &g_spi1_cfg,
    .p_api = &g_spi_on_spi_w,
};
#endif


#ifdef BSP_USING_QSPI_PSRAM
qspi_w_instance_ctrl_t g_qspi_ram0_ctrl;

static qspi_w_write_instr_cfg_t g_qspi_ram0_write_cfg =
{
    .write_opcode = 0x38,
    .write_opcode_wb = 0,
    .opcode_bus_mode = QSPI_W_BUS_MODE_QUAD,
    .addr_bus_mode = QSPI_W_BUS_MODE_QUAD,
    .data_bus_mode = QSPI_W_BUS_MODE_QUAD,
    .dummy_bus_mode = QSPI_W_BUS_MODE_QUAD,
    .dummy_en = false,
    .dummy_bytes = 0,
    .wdex_en = 0,
    .cs_hi_min_clk_cycles = 0x01,
    .send_wen_req = 0,
};

static qspi_w_read_instr_cfg_t g_qspi_ram0_read_cfg =
{
    .opcode = 0xEB,
    .opcode_wb = 0,
    .extra_byte_value = 0xFF,
    .opcode_bus_mode = QSPI_W_BUS_MODE_QUAD,
    .addr_bus_mode = QSPI_W_BUS_MODE_QUAD,
    .extra_byte_bus_mode = QSPI_W_BUS_MODE_QUAD,
    .dummy_bus_mode = QSPI_W_BUS_MODE_QUAD,
    .data_bus_mode = QSPI_W_BUS_MODE_QUAD,
    .extra_byte_en = QSPI_W_EXTRA_BYTE_ENABLE,
    .extra_byte_half_cfg = QSPI_W_EXTRA_BYTE_HALF_DISABLE,
    .dummy_bytes = 2,
    .dummy_en = true,
    .dummy_force = false,
    .instr_md = QSPI_W_INSTR_MD_TX_AT_ANY_BURST_ACCESS,
    .wrap_md = QSPI_W_WRAP_MD_SEL_INSTR,
    .wrap_blen = 0,
    .wrap_size = 0,
    .wrap_wr_en = QSPI_W_WRAP_WR_EN_INST,
    .cs_high_min_cycles = 0x01,
    .rd_bend_md = QSPI_W_RD_BEND_MD_TERMINATE_ASAP,
    .rd_rdb_en = QSPI_W_RD_RDB_EN_MIN_CLK_PULSES,
};

static qspi_w_break_instr_cfg_t g_qspi_ram0_break_cfg =
{
    .break_opcode = 0xffff,
    .break_sz = 0,
    .break_tx_md = QSPI_W_BUS_MODE_QUAD,
    .break_sec_hf = QSPI_W_BREAK_SEC_HF_DRIVE,
    .break_en = QSPI_W_BREAK_DISABLE,  /* APS6404L PSRAM does not require read-break */
};

static qspi_w_memblen_cfg_t g_qspi_ram0_memblen_cfg =
{
    .memblen = QSPI_W_MEMBLEN_BURST_INCR_UNSPECIFIED,
    .tcem_cc = 0,
    .tcem_en = QSPI_W_T_CEM_DISABLE,
    .rd_lin_en = false,
    .keep_active = false,   /* Must be false for PSRAM: tCEM limits max CS low time */
    .wcmd_hybrid = false,
    .dielen = 0,
    .active_thr = 0,
};

static qspi_w_ctrl_ddr_cfg_t g_qspi_ram0_ddr_cfg =
{
    .ctrl_ddra = 0,
    .ctrl_ddrb = 0,
};

static qspi_w_extra_registers_cfg_t g_qspi_ram0_extra_regs_cfg =
{
    .ctrl_mr_reg = 0,
    .drst_cmd_reg = 0,
};

static qspi_w_flash_cfg_t g_qspi_ram0_flash_cfg =
{
    .is_ram = true,
    .clk_mode = QSPI_W_CLK_MODE_LOW,
    .p_read_instr_cfg = &g_qspi_ram0_read_cfg,
    .p_write_instr_cfg = &g_qspi_ram0_write_cfg,
    .p_break_instr_cfg = &g_qspi_ram0_break_cfg,
    .p_memblen_cfg = &g_qspi_ram0_memblen_cfg,
    .p_ctrl_ddr = &g_qspi_ram0_ddr_cfg,
    .p_extra_regs = &g_qspi_ram0_extra_regs_cfg,
};

static qspi_w_extended_cfg_t g_qspi_ram0_extended_cfg =
{
    .channel = 0,
    .qspi_mode = QSPI_W_MODE_SDR,
    .qspclk_div = (qspi_w_qspclk_div_t) BSP_CFG_QSPICLK_DIV,
    .qspi_drive_current = QSPI_W_DRIVE_CURRENT_4,
    .qspi_slew_rate = QSPI_W_SLEW_RATE_FAST,
    .p_qspi_flash_cfg = &g_qspi_ram0_flash_cfg,
    .qspi_dcache = QSPI_W_DCACHE_DISABLE,  /* PSRAM is read-write; dcache is for flash only */
};

const spi_flash_cfg_t g_qspi_ram0_cfg =
{
    .spi_protocol = 0,
    .read_mode = 0,
    .dummy_clocks = 0,
    .page_program_address_lines = 0,
    .page_program_command = 0,
    .address_bytes = SPI_FLASH_ADDRESS_BYTES_3,
    .page_size_bytes = 256,
    .p_extend = &g_qspi_ram0_extended_cfg,
};

const spi_flash_instance_t g_qspi_ram0 =
{
    .p_ctrl = &g_qspi_ram0_ctrl,
    .p_cfg = &g_qspi_ram0_cfg,
    .p_api = &g_spi_flash_on_qspi_w,
};
#endif


#ifdef BSP_USING_OSPI_FLASH
/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

static spi_flash_erase_command_t g_ospi_flash_erase_command_list[] =
{
#if ((0x20 > 0) && (4096 > 0))
    {.command = 0x20, .size = 4096 },
#endif
#if ((0x52 > 0) && (32768 > 0))
    {.command = 0x52, .size = 32768},
#endif
#if (0xD8 > 0)
    {.command = 0xD8, .size = 65536},
#endif
};

ospi_w_xspi_command_set_t g_ospi_flash_high_speed_command_set =
{
    .protocol             = SPI_FLASH_PROTOCOL_1S_4S_4S,
    .command_bytes        = OSPI_W_COMMAND_BYTES_1,
    .read_command         = 0xEB,
    .page_program_command = 0x32,
    .write_enable_command = 0x06,
    .status_command       = 0x05,
    .read_dummy_cycles    = 0x02,
    .program_dummy_cycles = 0,
    .status_dummy_cycles  = 0,

    /* Use the default commands spi_flash_cfg_t */
    .p_erase_command_list      = NULL,
    .erase_command_list_length = 0,
};

ospi_w_device_config_t g_ospi_flash_hw_cfg =
{
    .clk_div         = OSPI_W_DEVICE_CLK_DIV_2,
    .bus_mode        = OSPI_W_DEVICE_BUS_MODE_SINGLE,
    .access_mode     = OSPI_W_DEVICE_ACCESS_MODE_AUTO,
    .clock_mode      = OSPI_W_DEVICE_CLK_MODE_HIGH,
    .io2_dir         = OSPI_W_DEVICE_IO_DIR_AUTO_SEL,
    .io2_value       = OSPI_W_DEVICE_IO_VALUE_LOW,
    .io3_dir         = OSPI_W_DEVICE_IO_DIR_AUTO_SEL,
    .io3_value       = OSPI_W_DEVICE_IO_VALUE_LOW,
    .io4_7_dir       = OSPI_W_DEVICE_IO_DIR_AUTO_SEL,
    .io4_7_value     = OSPI_W_DEVICE_IO4_7_VALUE_0000,
    .hready_mode     = OSPI_W_DEVICE_HREADY_MODE_WAIT,
    .sampling_edge   = OSPI_W_DEVICE_SAMPLING_EDGE_NEG,
    .read_pipe       = OSPI_W_DEVICE_READ_PIPE_ENABLE,
    .read_pipe_delay = OSPI_W_DEVICE_READ_PIPE_DELAY_7,
    .address_size    = OSPI_W_DEVICE_ADDR_SIZE_24,
    .dummy_mode      = OSPI_W_DEVICE_DUMMY_MODE_LAST_2_CLK,
    .slew_rate       = OSPI_W_DEVICE_SLEW_RATE_0,
    .drive_current   = OSPI_W_DEVICE_DRIVE_CURRENT_12,
    .manualmode_config.dir_change_mode             = OSPI_W_DEVICE_DIR_CHANGE_MODE_DUMMY_ACCESS,
    .manualmode_config.mapped_addr_rd_acc_response = OSPI_W_DEVICE_MAPPED_ADDR_RD_ACC_RESPONSE_IGNORE,
    .automode_config.full_buffer_mode              = OSPI_W_DEVICE_FULL_BUFFER_MODE_BLOCK,
    .automode_config.instruct_size                 = OSPI_W_DEVICE_INSTRUCT_SZ_1_BYTE,
    .automode_config.burst_len_limit               = OSPI_W_DEVICE_BURST_LEN_LIMIT_UNSPECIFIED,
};

ospi_w_device_read_instr_config_t g_ospi_flash_read_instr_config =
{
    .enable              = 1,
    .instr               = 0xEB,
    .instr_extra_byte    = 0xA0,
    .instr_bus_mode      = OSPI_W_DEVICE_BUS_MODE_SINGLE,
    .addr_bus_mode       = OSPI_W_DEVICE_BUS_MODE_QUAD,
    .extra_byte_bus_mode = OSPI_W_DEVICE_BUS_MODE_QUAD,
    .dummy_bus_mode      = OSPI_W_DEVICE_BUS_MODE_QUAD,
    .data_bus_mode       = OSPI_W_DEVICE_BUS_MODE_QUAD,
    .extra_byte_cfg      = OSPI_W_DEVICE_EXTRA_BYTE_ENABLE,
    .extra_byte_half_cfg = OSPI_W_DEVICE_EXTRA_BYTE_HALF_DISABLE,
    .dummy_bytes         = 2,
    .instr_mode          = OSPI_W_DEVICE_INSTR_MODE_SEND_ONCE,
    .idle_state_duration = OSPI_W_DEVICE_IDLE_STATE_DURATION_3,
};

ospi_w_device_wrap_burst_instr_config_t g_ospi_flash_wrap_burst_instr_config =
{
    .enable = 0,
};

ospi_w_device_read_status_config_t g_ospi_flash_read_status_config =
{
    .enable           = 1,
    .instr            = 0x05,
    .instr_bus_mode   = OSPI_W_DEVICE_BUS_MODE_SINGLE,
    .receive_bus_mode = OSPI_W_DEVICE_BUS_MODE_SINGLE,
    .dummy_bus_mode   = OSPI_W_DEVICE_BUS_MODE_SINGLE,
    .busy_pos         = 0,
    .busy_val         = OSPI_W_DEVICE_BUSY_HIGH,
    .read_stat_del    = 0,

    .read_stat_reg_cnt = OSPI_W_DEVICE_READ_STATUS_REG_CNT_RESSTS,
    .dummy_bytes       = 0,
    .dummy_val         = 0,
};

ospi_w_device_erase_instr_config_t g_ospi_flash_erase_instr_config =
{
    .enable         = 1,
    .instr          = 0x20,
    .instr_bus_mode = OSPI_W_DEVICE_BUS_MODE_SINGLE,
    .addr_bus_mode  = OSPI_W_DEVICE_BUS_MODE_SINGLE,
    .hclk_cycles    = 14,
    .cs_hi_cycles   = 30,
};

ospi_w_device_write_enable_instr_config_t g_ospi_flash_write_enable_instr_config =
{
    .enable         = 1,
    .instr          = 0x06,
    .instr_bus_mode = OSPI_W_DEVICE_BUS_MODE_SINGLE,
};

ospi_w_device_suspend_resume_instr_config_t g_ospi_flash_suspend_resume_instr_config =
{
    .enable           = 1,
    .suspend_instr    = 0x75,
    .resume_instr     = 0x7A,
    .suspend_bus_mode = OSPI_W_DEVICE_BUS_MODE_SINGLE,
    .resume_bus_mode  = OSPI_W_DEVICE_BUS_MODE_SINGLE,
    .read_stat_del    = 128,
};

ospi_w_extended_cfg_t g_ospi_flash_extended_cfg =
{
    .channel                                 = 0,
    .p_timing_settings                       = NULL,
    .p_xspi_command_set_list                 = &g_ospi_flash_high_speed_command_set,
    .xspi_command_set_list_length            = 1,
    .p_autocalibration_preamble_pattern_addr = NULL,
    .data_latch_delay_clocks                 = 0,
#if OSPI_W_CFG_DMAC_SUPPORT_ENABLE

    /* DMA Transfer instance used for data transmission */
    transfer_instance_t const * p_lower_lvl_transfer;
#endif
    .p_ospi_w_device_cfg        = &g_ospi_flash_hw_cfg,
    .p_read_instr_cfg           = &g_ospi_flash_read_instr_config,
    .p_wrap_burst_instr_cfg     = &g_ospi_flash_wrap_burst_instr_config,
    .p_read_status_instr_cfg    = &g_ospi_flash_read_status_config,
    .p_write_enable_instr_cfg   = &g_ospi_flash_write_enable_instr_config,
    .p_erase_instr_cfg          = &g_ospi_flash_erase_instr_config,
    .p_suspend_resume_instr_cfg = &g_ospi_flash_suspend_resume_instr_config,
};
spi_flash_cfg_t g_ospi_flash_cfg =
{
    .spi_protocol               = SPI_FLASH_PROTOCOL_1S_1S_1S,
    .read_mode                  = SPI_FLASH_READ_MODE_FAST_READ_QUAD_IO,
    .address_bytes              = SPI_FLASH_ADDRESS_BYTES_3,
    .dummy_clocks               = SPI_FLASH_DUMMY_CLOCKS_2,
    .page_program_address_lines = SPI_FLASH_DATA_LINES_4,
    .page_size_bytes            = 256,
    .write_status_bit           = 0,
    .write_enable_bit           = 1,
    .page_program_command       = 0x32,
    .write_enable_command       = 0x06,
    .status_command             = 0x05,
    .read_command               = 0xEB,
    .xip_enter_command          = 0U,
    .xip_exit_command           = 0U,
    .erase_command_list_length  = sizeof(g_ospi_flash_erase_command_list) /
                                  sizeof(g_ospi_flash_erase_command_list[0]),
    .p_erase_command_list = &g_ospi_flash_erase_command_list[0],
    .p_extend             = &g_ospi_flash_extended_cfg,
};

/** This structure encompasses everything that is needed to use an instance of this interface. */
ospi_w_instance_ctrl_t g_ospi_flash_ctrl;
#endif

#ifdef BSP_USING_ONCHIP_RTC
rtc_w_instance_ctrl_t g_rtc_w_ctrl;

static const rtc_extended_cfg_t g_rtc_w_cfg_extend =
{
    .reserved = 0U,
};

const rtc_cfg_t g_rtc_w_cfg =
{
    .clock_source       = RTC_CLOCK_SOURCE_SUBCLK,
    .freq_compare_value = 0U,
    .p_err_cfg          = NULL,
    .alarm_ipl          = BSP_IRQ_DISABLED,
    .alarm_irq          = FSP_INVALID_VECTOR,
    .periodic_ipl       = BSP_IRQ_DISABLED,
    .periodic_irq       = FSP_INVALID_VECTOR,
    .carry_ipl          = BSP_IRQ_DISABLED,
    .carry_irq          = FSP_INVALID_VECTOR,
    .p_callback         = NULL,
    .p_context          = NULL,
    .p_extend           = &g_rtc_w_cfg_extend,
};

const rtc_instance_t g_rtc_w =
{
    .p_ctrl = &g_rtc_w_ctrl,
    .p_cfg  = &g_rtc_w_cfg,
    .p_api  = &g_rtc_on_rtc_w,
};
#endif

#ifdef BSP_USING_WDT
#ifndef BSP_WDOG_TIMEOUT_CLOCKS
#define BSP_WDOG_TIMEOUT_CLOCKS (1000U) /* 10 seconds at the 100 Hz WDT clock. */
#endif

wdog_w_instance_ctrl_t g_wdog_w_ctrl;

static const wdog_w_extended_cfg_t g_wdog_w_cfg_extend =
{
    .wdt_clk_src = WDOG_W_CLK_SRC_RCLP,
};

const wdt_cfg_t g_wdog_w_cfg =
{
    .timeout          = BSP_WDOG_TIMEOUT_CLOCKS,
    .clock_division   = WDT_CLOCK_DIVISION_1,
    .window_start     = WDT_WINDOW_START_100,
    .window_end       = WDT_WINDOW_END_0,
    .reset_control    = WDT_RESET_CONTROL_RESET,
    .stop_control     = WDT_STOP_CONTROL_DISABLE,
    .p_callback       = NULL,
    .p_context        = NULL,
    .p_extend         = &g_wdog_w_cfg_extend,
};

const wdt_instance_t g_wdog_w =
{
    .p_ctrl = &g_wdog_w_ctrl,
    .p_cfg  = &g_wdog_w_cfg,
    .p_api  = &g_wdt_on_wdog_w,
};
#endif

void g_hal_init(void)
{
    g_common_init();
}
