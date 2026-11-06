/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-06     RTT          add OV7670 camera support
 * 2026-09-08     CYFS         synchronize frame capture completion and retain error checks
 */

#include <board.h>
#include <rthw.h>
#include <rtdevice.h>

#include "drv_ov7670.h"
#include "ports/camera/sensor.h"
#include "gd32h77x_78x_dci.h"
#include "gd32h77x_78x_dma.h"
#include "gd32h77x_78x_i2c.h"
#include "gd32h77x_78x_misc.h"
#include "gd32h77x_78x_rcu.h"
#include "gd32h77x_78x_timer.h"

#ifdef BSP_USING_OV7670

#define DBG_TAG                         "drv.ov7670"
#define DBG_LVL                         DBG_INFO
#include <rtdbg.h>

#define OV7670_I2C_BUS_NAME             "hwi2c2"
#define OV7670_SCCB_ADDRESS             0x21U
#define OV7670_SCCB_WIRE_ADDRESS        (OV7670_SCCB_ADDRESS << 1U)
#define OV7670_XCLK_TARGET_HZ           24000000U
#define OV7670_CAPTURE_TIMEOUT_MS       500U
#define OV7670_SCCB_PSC                 0U
#define OV7670_SCCB_SCL_DELAY           1U
#define OV7670_SCCB_SDA_DELAY           0U
#define OV7670_SCCB_SCL_HIGH            0x98U
#define OV7670_SCCB_SCL_LOW             0xF1U
#define OV7670_SCCB_RETRY_COUNT         3U
#define OV7670_SCCB_RETRY_DELAY_US      1000U
#define OV7670_SCCB_TIMEOUT_MS          20U
#define OV7670_SCCB_RECOVERY_DELAY_US   5U
#define OV7670_SCCB_RECOVERY_PULSES     9U
#define OV7670_SCCB_ERROR_FLAGS         (I2C_FLAG_NACK | I2C_FLAG_BERR | \
                                         I2C_FLAG_LOSTARB | I2C_FLAG_OUERR | \
                                         I2C_FLAG_TIMEOUT)
#define OV7670_SCCB_CLEAR_FLAGS         (OV7670_SCCB_ERROR_FLAGS | \
                                         I2C_FLAG_STPDET)
#define OV7670_CLOCK_SAMPLE_COUNT       4096U
#define OV7670_CAPTURE_LINE_WORDS       162U
#define OV7670_CAPTURE_LINE_BYTES       (OV7670_CAPTURE_LINE_WORDS * \
                                         sizeof(rt_uint32_t))
#define OV7670_CAPTURE_SIZE             (OV7670_CAPTURE_LINE_BYTES * \
                                         OV7670_HEIGHT)
#define OV7670_DMA_WORD_COUNT           (OV7670_CAPTURE_SIZE / \
                                         sizeof(rt_uint32_t))
#define OV7670_LINE_CROP_BYTES          ((OV7670_CAPTURE_LINE_BYTES - \
                                          OV7670_WIDTH * \
                                          OV7670_BYTES_PER_PIXEL) / 2U)
#define OV7670_DMA_FLAGS                (DMA_INT_FLAG_FEE | DMA_INT_FLAG_SDE | \
                                         DMA_INT_FLAG_TAE | DMA_INT_FLAG_FTF)
#define OV7670_DMA_INTERRUPTS           (DMA_INT_FEE | DMA_INT_SDE | \
                                         DMA_INT_TAE | DMA_INT_FTF)

struct ov7670_device
{
    struct rt_device parent;
    struct rt_i2c_bus_device *bus;
    struct rt_mutex lock;
    struct ov7670_info info;
    rt_bool_t initialized;
};

static struct ov7670_device ov7670;
rt_align(32) static rt_uint8_t ov7670_frame_buffer[OV7670_CAPTURE_SIZE];
static struct rt_completion ov7670_capture_completion;
static volatile rt_bool_t ov7670_capture_active;
static volatile rt_err_t ov7670_capture_result;
static volatile rt_bool_t ov7670_dma_complete;
static volatile rt_bool_t ov7670_frame_complete;
static volatile rt_uint32_t ov7670_capture_flags;

static rt_uint32_t ov7670_timer_clock_get(void)
{
    rt_uint32_t ahb_clock = rcu_clock_freq_get(CK_AHB);
    rt_uint32_t timer_clock = rcu_clock_freq_get(CK_APB2);
    rt_uint32_t multiplier;

    multiplier = (RCU_CFG1 & RCU_CFG1_TIMERSEL) ? 4U : 2U;
    timer_clock *= multiplier;
    if (timer_clock > ahb_clock)
    {
        timer_clock = ahb_clock;
    }

    return timer_clock;
}

static rt_uint32_t ov7670_xclk_divisor_get(void)
{
    return (ov7670_timer_clock_get() + OV7670_XCLK_TARGET_HZ / 2U) /
           OV7670_XCLK_TARGET_HZ;
}

static void ov7670_xclk_start(void)
{
    timer_parameter_struct timer_config;
    timer_oc_parameter_struct output_config;
    rt_uint32_t divisor = ov7670_xclk_divisor_get();

    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_TIMER0);

    gpio_af_set(GPIOE, GPIO_AF_1, GPIO_PIN_9);
    gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_9);
    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ,
                            GPIO_PIN_9);

    timer_deinit(TIMER0);
    timer_struct_para_init(&timer_config);
    timer_config.prescaler = 0U;
    timer_config.alignedmode = TIMER_COUNTER_EDGE;
    timer_config.counterdirection = TIMER_COUNTER_UP;
    timer_config.period = divisor - 1U;
    timer_config.clockdivision = TIMER_CKDIV_DIV1;
    timer_config.repetitioncounter = 0U;
    timer_init(TIMER0, &timer_config);

    timer_channel_output_struct_para_init(&output_config);
    output_config.outputstate = TIMER_CCX_ENABLE;
    output_config.outputnstate = TIMER_CCXN_DISABLE;
    output_config.ocpolarity = TIMER_OC_POLARITY_HIGH;
    output_config.ocnpolarity = TIMER_OCN_POLARITY_HIGH;
    output_config.ocidlestate = TIMER_OC_IDLE_STATE_LOW;
    output_config.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
    timer_channel_output_config(TIMER0, TIMER_CH_0, &output_config);
    timer_channel_output_mode_config(TIMER0, TIMER_CH_0, TIMER_OC_MODE_PWM0);
    timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, divisor / 2U);
    timer_channel_output_shadow_config(TIMER0, TIMER_CH_0,
                                       TIMER_OC_SHADOW_DISABLE);
    timer_channel_primary_output_config(TIMER0, TIMER_CH_0, ENABLE);
    timer_primary_output_config(TIMER0, ENABLE);
    timer_channel_output_state_config(TIMER0, TIMER_CH_0, TIMER_CCX_ENABLE);
    timer_enable(TIMER0);
}

static void ov7670_xclk_stop(void)
{
    timer_channel_output_state_config(TIMER0, TIMER_CH_0, TIMER_CCX_DISABLE);
    timer_channel_primary_output_config(TIMER0, TIMER_CH_0, DISABLE);
    timer_disable(TIMER0);
    gpio_mode_set(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_9);
}

static void ov7670_sccb_bus_config(void)
{
    /* Use the conservative SCCB timing from the GD32H77DI DCI example. */
    i2c_deinit(I2C2);
    i2c_timing_config(I2C2, OV7670_SCCB_PSC, OV7670_SCCB_SCL_DELAY,
                      OV7670_SCCB_SDA_DELAY);
    i2c_master_clock_config(I2C2, OV7670_SCCB_SCL_HIGH,
                            OV7670_SCCB_SCL_LOW);
    i2c_enable(I2C2);
}

static void ov7670_sccb_bus_recover(void)
{
    rt_uint32_t pulse;

    i2c_disable(I2C2);
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOC);

    gpio_bit_set(GPIOA, GPIO_PIN_8);
    gpio_bit_set(GPIOC, GPIO_PIN_9);
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_8);
    gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_9);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ,
                            GPIO_PIN_8);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_OD, GPIO_OSPEED_60MHZ,
                            GPIO_PIN_9);
    rt_hw_us_delay(OV7670_SCCB_RECOVERY_DELAY_US);

    for (pulse = 0U;
         (pulse < OV7670_SCCB_RECOVERY_PULSES) &&
         (gpio_input_bit_get(GPIOC, GPIO_PIN_9) == RESET);
         pulse++)
    {
        gpio_bit_reset(GPIOA, GPIO_PIN_8);
        rt_hw_us_delay(OV7670_SCCB_RECOVERY_DELAY_US);
        gpio_bit_set(GPIOA, GPIO_PIN_8);
        rt_hw_us_delay(OV7670_SCCB_RECOVERY_DELAY_US);
    }

    gpio_bit_reset(GPIOC, GPIO_PIN_9);
    rt_hw_us_delay(OV7670_SCCB_RECOVERY_DELAY_US);
    gpio_bit_set(GPIOA, GPIO_PIN_8);
    rt_hw_us_delay(OV7670_SCCB_RECOVERY_DELAY_US);
    gpio_bit_set(GPIOC, GPIO_PIN_9);
    rt_hw_us_delay(OV7670_SCCB_RECOVERY_DELAY_US);

    gpio_af_set(GPIOA, GPIO_AF_4, GPIO_PIN_8);
    gpio_af_set(GPIOC, GPIO_AF_4, GPIO_PIN_9);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_8);
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
    ov7670_sccb_bus_config();
}

static rt_err_t ov7670_sccb_wait_flag(rt_uint32_t flag)
{
    rt_tick_t start_tick = rt_tick_get();
    rt_tick_t timeout = rt_tick_from_millisecond(OV7670_SCCB_TIMEOUT_MS);

    while (i2c_flag_get(I2C2, flag) == RESET)
    {
        if ((I2C_STAT(I2C2) & OV7670_SCCB_ERROR_FLAGS) != 0U)
        {
            return -RT_EIO;
        }
        if ((rt_tick_get() - start_tick) >= timeout)
        {
            return -RT_ETIMEOUT;
        }
    }

    return RT_EOK;
}

static rt_err_t ov7670_sccb_wait_idle(void)
{
    rt_tick_t start_tick = rt_tick_get();
    rt_tick_t timeout = rt_tick_from_millisecond(OV7670_SCCB_TIMEOUT_MS);

    while (i2c_flag_get(I2C2, I2C_FLAG_I2CBSY) != RESET)
    {
        if ((rt_tick_get() - start_tick) >= timeout)
        {
            return -RT_ETIMEOUT;
        }
    }

    return RT_EOK;
}

static void ov7670_sccb_transfer_finish(void)
{
    i2c_automatic_end_disable(I2C2);
    i2c_flag_clear(I2C2, OV7670_SCCB_CLEAR_FLAGS);
}

static void ov7670_sccb_log_failure(const char *phase, rt_uint8_t reg)
{
    LOG_E("SCCB %s failed at reg 0x%02x (SCL=%u SDA=%u TIMING=%08x STAT=%08x)",
          phase, reg,
          (unsigned int)gpio_input_bit_get(GPIOA, GPIO_PIN_8),
          (unsigned int)gpio_input_bit_get(GPIOC, GPIO_PIN_9),
          (unsigned int)I2C_TIMING(I2C2), (unsigned int)I2C_STAT(I2C2));
}

static rt_uint32_t ov7670_pin_edge_count(rt_uint32_t gpio_periph,
                                         rt_uint32_t pin)
{
    rt_uint32_t previous = GPIO_ISTAT(gpio_periph) & pin;
    rt_uint32_t edges = 0U;
    rt_uint32_t index;

    for (index = 0U; index < OV7670_CLOCK_SAMPLE_COUNT; index++)
    {
        rt_uint32_t current = GPIO_ISTAT(gpio_periph) & pin;

        if (current != previous)
        {
            edges++;
            previous = current;
        }
    }
    return edges;
}

static void ov7670_clock_log_failure(void)
{
    rt_uint32_t xclk_edges;
    rt_uint32_t pclk_edges;

    gpio_af_set(GPIOE, GPIO_AF_13, GPIO_PIN_3);
    gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);
    xclk_edges = ov7670_pin_edge_count(GPIOE, GPIO_PIN_9);
    pclk_edges = ov7670_pin_edge_count(GPIOE, GPIO_PIN_3);
    LOG_E("clock diagnostic: XCLK edges=%u PCLK edges=%u CTL0=%08x CNT=%u CAR=%u CH0CV=%u",
          (unsigned int)xclk_edges, (unsigned int)pclk_edges,
          (unsigned int)TIMER_CTL0(TIMER0),
          (unsigned int)TIMER_CNT(TIMER0),
          (unsigned int)TIMER_CAR(TIMER0),
          (unsigned int)TIMER_CH0CV(TIMER0));
    LOG_E("clock gates: CHCTL0=%08x CHCTL2=%08x CCHP=%08x CHBRKCTL=%08x",
          (unsigned int)TIMER_CHCTL0(TIMER0),
          (unsigned int)TIMER_CHCTL2(TIMER0),
          (unsigned int)TIMER_CCHP(TIMER0),
          (unsigned int)TIMER_CHBRKCTL(TIMER0));
    LOG_E("PE9 mux: CTL=%08x AFSEL1=%08x OMODE=%08x ISTAT=%08x",
          (unsigned int)GPIO_CTL(GPIOE),
          (unsigned int)GPIO_AFSEL1(GPIOE),
          (unsigned int)GPIO_OMODE(GPIOE),
          (unsigned int)GPIO_ISTAT(GPIOE));
}

static rt_err_t ov7670_write_register(rt_uint8_t reg, rt_uint8_t value)
{
    rt_err_t result;
    rt_uint32_t attempt;

    for (attempt = 0U; attempt < OV7670_SCCB_RETRY_COUNT; attempt++)
    {
        result = ov7670_sccb_wait_idle();
        if (result == RT_EOK)
        {
            i2c_flag_clear(I2C2, OV7670_SCCB_CLEAR_FLAGS);
            i2c_master_addressing(I2C2, OV7670_SCCB_WIRE_ADDRESS,
                                  I2C_MASTER_TRANSMIT);
            i2c_transfer_byte_number_config(I2C2, 2U);
            i2c_automatic_end_enable(I2C2);
            i2c_start_on_bus(I2C2);

            i2c_data_transmit(I2C2, reg);
            result = ov7670_sccb_wait_flag(I2C_FLAG_TI);
        }
        if (result == RT_EOK)
        {
            i2c_data_transmit(I2C2, value);
            result = ov7670_sccb_wait_flag(I2C_FLAG_TI);
        }
        if (result == RT_EOK)
        {
            result = ov7670_sccb_wait_flag(I2C_FLAG_STPDET);
        }
        ov7670_sccb_transfer_finish();

        if (result == RT_EOK)
        {
            if (attempt != 0U)
            {
                LOG_W("SCCB write recovered at reg 0x%02x after %u retries",
                      reg, (unsigned int)attempt);
            }
            return RT_EOK;
        }

        if ((attempt + 1U) < OV7670_SCCB_RETRY_COUNT)
        {
            rt_hw_us_delay(OV7670_SCCB_RETRY_DELAY_US);
            ov7670_sccb_bus_recover();
        }
    }

    ov7670_sccb_log_failure("write", reg);
    ov7670_sccb_bus_recover();
    return result;
}

static rt_err_t ov7670_read_register(rt_uint8_t reg, rt_uint8_t *value)
{
    rt_err_t result;
    rt_uint32_t attempt;

    for (attempt = 0U; attempt < OV7670_SCCB_RETRY_COUNT; attempt++)
    {
        result = ov7670_sccb_wait_idle();
        if (result == RT_EOK)
        {
            i2c_flag_clear(I2C2, OV7670_SCCB_CLEAR_FLAGS);
            i2c_master_addressing(I2C2, OV7670_SCCB_WIRE_ADDRESS,
                                  I2C_MASTER_TRANSMIT);
            i2c_transfer_byte_number_config(I2C2, 1U);
            i2c_automatic_end_enable(I2C2);
            i2c_start_on_bus(I2C2);

            i2c_data_transmit(I2C2, reg);
            result = ov7670_sccb_wait_flag(I2C_FLAG_TI);
        }
        if (result == RT_EOK)
        {
            result = ov7670_sccb_wait_flag(I2C_FLAG_STPDET);
        }
        ov7670_sccb_transfer_finish();

        if (result == RT_EOK)
        {
            i2c_master_addressing(I2C2, OV7670_SCCB_WIRE_ADDRESS,
                                  I2C_MASTER_RECEIVE);
            i2c_transfer_byte_number_config(I2C2, 1U);
            i2c_automatic_end_enable(I2C2);
            i2c_start_on_bus(I2C2);
            result = ov7670_sccb_wait_flag(I2C_FLAG_RBNE);
        }
        if (result == RT_EOK)
        {
            *value = i2c_data_receive(I2C2);
            result = ov7670_sccb_wait_flag(I2C_FLAG_STPDET);
        }
        ov7670_sccb_transfer_finish();

        if (result == RT_EOK)
        {
            return RT_EOK;
        }

        if ((attempt + 1U) < OV7670_SCCB_RETRY_COUNT)
        {
            rt_hw_us_delay(OV7670_SCCB_RETRY_DELAY_US);
            ov7670_sccb_bus_recover();
        }
    }

    ov7670_sccb_log_failure("read", reg);
    ov7670_sccb_bus_recover();
    return result;
}

int gd32_camera_sccb_read(rt_uint8_t slv_addr, rt_uint8_t reg,
                          rt_uint8_t *value)
{
    RT_UNUSED(slv_addr);
    return ov7670_read_register(reg, value);
}

int gd32_camera_sccb_write(rt_uint8_t slv_addr, rt_uint8_t reg,
                           rt_uint8_t value)
{
    RT_UNUSED(slv_addr);
    return ov7670_write_register(reg, value);
}

static rt_err_t ov7670_sensor_init(void)
{
    rt_err_t result;
    int version;

    result = rt_i2c_bus_lock(ov7670.bus, RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        return result;
    }

    ov7670_xclk_start();
    rt_hw_us_delay(10000U);
    ov7670_sccb_bus_recover();

    result = (sensor_init() == 0) ? RT_EOK : -RT_EIO;
    if (result != RT_EOK)
    {
        ov7670_clock_log_failure();
    }
    if (result == RT_EOK)
    {
        result = sensor_reset();
    }
    if (result == RT_EOK)
    {
        result = sensor_set_pixformat(PIXFORMAT_RGB565);
    }
    if (result == RT_EOK)
    {
        result = sensor_set_framesize(FRAMESIZE_QVGA);
    }
    if (result == RT_EOK)
    {
        ov7670.info.pid = sensor.chip_id;
        version = sensor_read_reg(0x0BU);
        result = (version >= 0) ? RT_EOK : -RT_EIO;
        if (result == RT_EOK)
        {
            ov7670.info.ver = (rt_uint8_t)version;
        }
    }
    if (result == RT_EOK)
    {
        /* Window and scaling registers take effect on a frame boundary. */
        rt_hw_us_delay(100000U);
    }

    if (result != RT_EOK)
    {
        ov7670_xclk_stop();
    }
    rt_i2c_bus_unlock(ov7670.bus);
    return result;
}

static void ov7670_gpio_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOG);
    rcu_periph_clock_enable(RCU_GPIOH);

    gpio_af_set(GPIOG, GPIO_AF_13, GPIO_PIN_9);
    gpio_af_set(GPIOH, GPIO_AF_1, GPIO_PIN_15);
    gpio_af_set(GPIOE, GPIO_AF_13, GPIO_PIN_3);
    gpio_af_set(GPIOA, GPIO_AF_13, GPIO_PIN_9 | GPIO_PIN_10);
    gpio_af_set(GPIOC, GPIO_AF_13, GPIO_PIN_8);
    gpio_af_set(GPIOE, GPIO_AF_13, GPIO_PIN_1);
    gpio_af_set(GPIOH, GPIO_AF_13, GPIO_PIN_14);
    gpio_af_set(GPIOD, GPIO_AF_13, GPIO_PIN_3);
    gpio_af_set(GPIOB, GPIO_AF_13, GPIO_PIN_8 | GPIO_PIN_9);

    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_9);
    gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_NONE,
                  GPIO_PIN_14 | GPIO_PIN_15);
    gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE,
                  GPIO_PIN_1 | GPIO_PIN_3);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE,
                  GPIO_PIN_9 | GPIO_PIN_10);
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_8);
    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE,
                  GPIO_PIN_8 | GPIO_PIN_9);

    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ,
                            GPIO_PIN_9);
    gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ,
                            GPIO_PIN_14 | GPIO_PIN_15);
    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ,
                            GPIO_PIN_1 | GPIO_PIN_3);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ,
                            GPIO_PIN_9 | GPIO_PIN_10);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ,
                            GPIO_PIN_8);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ,
                            GPIO_PIN_3);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_100_220MHZ,
                            GPIO_PIN_8 | GPIO_PIN_9);
}

static void ov7670_dci_configure(void)
{
    dci_parameter_struct dci_config;

    /* Start each snapshot with an empty FIFO, including after an aborted frame. */
    dci_deinit();
    dci_config.capture_mode = DCI_CAPTURE_MODE_SNAPSHOT;
    dci_config.clock_polarity = DCI_CK_POLARITY_RISING;
    dci_config.hsync_polarity = DCI_HSYNC_POLARITY_LOW;
    dci_config.vsync_polarity = DCI_VSYNC_POLARITY_HIGH;
    dci_config.frame_rate = DCI_FRAME_RATE_ALL;
    dci_config.interface_format = DCI_INTERFACE_FORMAT_8BITS;
    dci_init(&dci_config);
    dci_interrupt_enable(DCI_INT_OVR | DCI_INT_ESE | DCI_INT_EF);
}

static void ov7670_dci_init(void)
{
    rcu_periph_clock_enable(RCU_DCI);
    rcu_periph_clock_enable(RCU_DMA1);
    rcu_periph_clock_enable(RCU_DMAMUX);
    ov7670_gpio_init();
    ov7670_dci_configure();

    nvic_irq_enable(DMA1_Channel7_IRQn, 4U, 0U);
    nvic_irq_enable(DCI_IRQn, 4U, 0U);
}

static void ov7670_dma_prepare(void)
{
    dma_single_data_parameter_struct dma_config;

    dma_channel_deinit(DMA1, DMA_CH7);
    dma_single_data_para_struct_init(&dma_config);
    dma_config.request = DMA_REQUEST_DCI;
    dma_config.periph_addr = (rt_uint32_t)&DCI_DATA;
    dma_config.memory0_addr = (rt_uint32_t)ov7670_frame_buffer;
    dma_config.direction = DMA_PERIPH_TO_MEMORY;
    dma_config.number = OV7670_DMA_WORD_COUNT;
    dma_config.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_config.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_config.periph_memory_width = DMA_PERIPH_WIDTH_32BIT;
    dma_config.circular_mode = DMA_CIRCULAR_MODE_DISABLE;
    dma_config.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_single_data_mode_init(DMA1, DMA_CH7, &dma_config);
    dma_interrupt_flag_clear(DMA1, DMA_CH7, OV7670_DMA_FLAGS);
    dma_interrupt_enable(DMA1, DMA_CH7, OV7670_DMA_INTERRUPTS);
}

static void ov7670_capture_finish(rt_err_t result)
{
    if (!ov7670_capture_active)
    {
        return;
    }

    ov7670_capture_flags |= DCI_STAT1;
    if ((result == RT_EOK) &&
        ((ov7670_capture_flags & (DCI_STAT1_OVRF | DCI_STAT1_ESEF)) != 0U))
    {
        result = -RT_EIO;
    }
    dma_channel_disable(DMA1, DMA_CH7);
    dma_interrupt_disable(DMA1, DMA_CH7, OV7670_DMA_INTERRUPTS);
    dci_capture_disable();
    dci_disable();
    dci_interrupt_disable(DCI_INT_OVR | DCI_INT_ESE | DCI_INT_EF);
    ov7670_capture_result = result;
    ov7670_capture_active = RT_FALSE;
    rt_completion_done(&ov7670_capture_completion);
}

static void ov7670_capture_update(rt_uint32_t dci_flags,
                                  rt_bool_t dma_error, rt_bool_t dma_finished)
{
    if (!ov7670_capture_active)
    {
        return;
    }

    ov7670_capture_flags |= dci_flags;
    if ((dci_flags & DCI_STAT1_EFF) != 0U)
    {
        ov7670_frame_complete = RT_TRUE;
    }
    if (dma_finished && !ov7670_dma_complete)
    {
        ov7670_dma_complete = RT_TRUE;
    }

    /* The two IRQs may arrive in either order. An overflow takes precedence
     * over completion, even when the DMA IRQ is serviced first. */
    if (dma_error || ((dci_flags & (DCI_STAT1_OVRF | DCI_STAT1_ESEF)) != 0U))
    {
        ov7670_capture_finish(-RT_EIO);
    }
    else if (ov7670_dma_complete && ov7670_frame_complete)
    {
        rt_bool_t complete = (dma_transfer_number_get(DMA1, DMA_CH7) == 0U) &&
                             ((DCI_STAT0 & DCI_STAT0_FV) == 0U);

        ov7670_capture_finish(complete ? RT_EOK : -RT_EIO);
    }
}

void DMA1_Channel7_IRQHandler(void)
{
    rt_bool_t error;
    rt_bool_t finished;

    rt_interrupt_enter();
    error = (dma_interrupt_flag_get(DMA1, DMA_CH7, DMA_INT_FLAG_FEE) != RESET) ||
            (dma_interrupt_flag_get(DMA1, DMA_CH7, DMA_INT_FLAG_SDE) != RESET) ||
            (dma_interrupt_flag_get(DMA1, DMA_CH7, DMA_INT_FLAG_TAE) != RESET);
    finished = dma_interrupt_flag_get(DMA1, DMA_CH7, DMA_INT_FLAG_FTF) != RESET;
    dma_interrupt_flag_clear(DMA1, DMA_CH7, OV7670_DMA_FLAGS);

    ov7670_capture_update(DCI_STAT1, error, finished);
    __DSB();
    rt_interrupt_leave();
}

void DCI_IRQHandler(void)
{
    rt_uint32_t flags;

    rt_interrupt_enter();
    flags = DCI_STAT1;
    dci_interrupt_flag_clear(flags & (DCI_INT_FLAG_EF | DCI_INT_FLAG_OVR |
                                     DCI_INT_FLAG_ESE));
    ov7670_capture_update(flags, RT_FALSE, RT_FALSE);
    __DSB();
    rt_interrupt_leave();
}

static void ov7670_rgb565_byte_swap(void)
{
    rt_size_t index;

    for (index = 0U; index < OV7670_FRAME_SIZE; index += 2U)
    {
        rt_uint8_t value = ov7670_frame_buffer[index];

        ov7670_frame_buffer[index] = ov7670_frame_buffer[index + 1U];
        ov7670_frame_buffer[index + 1U] = value;
    }
}

static void ov7670_compact_frame(void)
{
    rt_size_t row;

    for (row = 0U; row < OV7670_HEIGHT; row++)
    {
        rt_memmove(ov7670_frame_buffer +
                   row * OV7670_WIDTH * OV7670_BYTES_PER_PIXEL,
                   ov7670_frame_buffer +
                   row * OV7670_CAPTURE_LINE_BYTES + OV7670_LINE_CROP_BYTES,
                   OV7670_WIDTH * OV7670_BYTES_PER_PIXEL);
    }
}

static rt_err_t ov7670_capture(void)
{
    rt_tick_t timeout;
    rt_base_t level;
    rt_err_t wait_result;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH | RT_HW_CACHE_INVALIDATE,
                         ov7670_frame_buffer, OV7670_CAPTURE_SIZE);

    level = rt_hw_interrupt_disable();
    ov7670_dci_configure();
    ov7670_dma_prepare();
    ov7670_capture_result = -RT_ETIMEOUT;
    ov7670_dma_complete = RT_FALSE;
    ov7670_frame_complete = RT_FALSE;
    ov7670_capture_flags = 0U;
    rt_completion_init(&ov7670_capture_completion);
    NVIC_ClearPendingIRQ(DMA1_Channel7_IRQn);
    NVIC_ClearPendingIRQ(DCI_IRQn);
    ov7670_capture_active = RT_TRUE;
    dma_channel_enable(DMA1, DMA_CH7);
    dci_enable();
    dci_capture_enable();
    __DSB();
    rt_hw_interrupt_enable(level);

    timeout = rt_tick_from_millisecond(OV7670_CAPTURE_TIMEOUT_MS);
    wait_result = rt_completion_wait(&ov7670_capture_completion, timeout);

    level = rt_hw_interrupt_disable();
    if (ov7670_capture_active)
    {
        ov7670_capture_finish(wait_result == RT_EOK ? -RT_EIO : wait_result);
    }
    rt_hw_interrupt_enable(level);

    if (ov7670_capture_result != RT_EOK)
    {
        return ov7670_capture_result;
    }

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, ov7670_frame_buffer,
                         OV7670_CAPTURE_SIZE);
    ov7670_compact_frame();
    if (sensor.hw_flags.rgb_swap)
    {
        ov7670_rgb565_byte_swap();
    }
    return RT_EOK;
}

static rt_err_t ov7670_device_init(rt_device_t device)
{
    rt_err_t result;

    RT_UNUSED(device);
    result = rt_mutex_take(&ov7670.lock, RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        return result;
    }
    if (ov7670.initialized)
    {
        rt_mutex_release(&ov7670.lock);
        return RT_EOK;
    }

    ov7670.bus = rt_i2c_bus_device_find(OV7670_I2C_BUS_NAME);
    if (ov7670.bus == RT_NULL)
    {
        LOG_E("I2C bus %s not found", OV7670_I2C_BUS_NAME);
        rt_mutex_release(&ov7670.lock);
        return -RT_ENOSYS;
    }

    result = ov7670_sensor_init();
    if (result == RT_EOK)
    {
        ov7670_dci_init();
        ov7670.initialized = RT_TRUE;
        LOG_I("OV7670 PID=%02x VER=%02x, %ux%u RGB565, XCLK=%u Hz",
              ov7670.info.pid, ov7670.info.ver,
              ov7670.info.width, ov7670.info.height, ov7670.info.xclk_hz);
    }
    else
    {
        LOG_E("sensor initialization failed: %d (PID=%02x VER=%02x)",
              result, ov7670.info.pid, ov7670.info.ver);
    }

    rt_mutex_release(&ov7670.lock);
    return result;
}

static rt_ssize_t ov7670_device_read(rt_device_t device, rt_off_t position,
                                      void *buffer, rt_size_t size)
{
    rt_err_t result;

    RT_UNUSED(device);
    RT_UNUSED(position);
    if ((buffer == RT_NULL) || (size < OV7670_FRAME_SIZE))
    {
        return -RT_EINVAL;
    }
    if (!ov7670.initialized)
    {
        return -RT_EIO;
    }

    result = rt_mutex_take(&ov7670.lock, RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        result = ov7670_capture();
        if (result == RT_EOK)
        {
            rt_memcpy(buffer, ov7670_frame_buffer, OV7670_FRAME_SIZE);
        }
        rt_mutex_release(&ov7670.lock);
    }

    return (result == RT_EOK) ? (rt_ssize_t)OV7670_FRAME_SIZE : result;
}

static rt_err_t ov7670_device_control(rt_device_t device, int command,
                                       void *args)
{
    RT_UNUSED(device);
    if (args == RT_NULL)
    {
        return -RT_EINVAL;
    }

    if (command == OV7670_CTRL_GET_INFO)
    {
        rt_memcpy(args, &ov7670.info, sizeof(ov7670.info));
        return RT_EOK;
    }

    return -RT_EINVAL;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops ov7670_device_ops =
{
    ov7670_device_init,
    RT_NULL,
    RT_NULL,
    ov7670_device_read,
    RT_NULL,
    ov7670_device_control,
};
#endif

static int rt_hw_ov7670_register(void)
{
    rt_uint32_t divisor;
    rt_err_t result;

    rt_memset(&ov7670, 0, sizeof(ov7670));
    result = rt_mutex_init(&ov7670.lock, "ov7670", RT_IPC_FLAG_PRIO);
    if (result != RT_EOK)
    {
        return result;
    }

    divisor = ov7670_xclk_divisor_get();
    ov7670.info.width = OV7670_WIDTH;
    ov7670.info.height = OV7670_HEIGHT;
    ov7670.info.frame_size = OV7670_FRAME_SIZE;
    ov7670.info.pixel_format = OV7670_PIXEL_FORMAT_RGB565;
    ov7670.info.xclk_hz = ov7670_timer_clock_get() / divisor;
    ov7670.parent.type = RT_Device_Class_Miscellaneous;
#ifdef RT_USING_DEVICE_OPS
    ov7670.parent.ops = &ov7670_device_ops;
#else
    ov7670.parent.init = ov7670_device_init;
    ov7670.parent.read = ov7670_device_read;
    ov7670.parent.control = ov7670_device_control;
#endif
    ov7670.parent.user_data = &ov7670.info;

    return rt_device_register(&ov7670.parent, OV7670_DEVICE_NAME,
                              RT_DEVICE_FLAG_RDONLY);
}
INIT_DEVICE_EXPORT(rt_hw_ov7670_register);

#endif /* BSP_USING_OV7670 */
