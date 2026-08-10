/* generated pin source file - do not edit */
#include <rtthread.h>
#define DBG_TAG "pin"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>
#include "bsp_api.h"
#include "hal_data.h"
#include "r_gpio_w.h"

ioport_pin_cfg_t g_bsp_pin_cfg_data[] =
{
#ifdef BSP_USING_UART0
    {
        .pin = BSP_IO_PORT_00_PIN_00,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_UART_RX,
    },
    {
        .pin = BSP_IO_PORT_00_PIN_01,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_UART_TX,
    },
#endif
#ifdef BSP_USING_UART1
    {
        .pin = BSP_IO_PORT_00_PIN_04,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_UART2_RX,
    },
    {
        .pin = BSP_IO_PORT_00_PIN_05,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_UART2_TX,
    },
#endif
#ifdef BSP_USING_UART2
    {
        .pin = BSP_IO_PORT_01_PIN_10,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_UART3_RX,
    },
    {
        .pin = BSP_IO_PORT_01_PIN_11,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_UART3_TX,
    },
#endif

#ifdef BSP_USING_PWM0
    {
        .pin = BSP_IO_PORT_00_PIN_04,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_TIM_PWM,
    },
#endif

#ifdef BSP_USING_PWM1
    {
        .pin = BSP_IO_PORT_00_PIN_05,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_TIM2_PWM,
    },
#endif
#ifdef BSP_USING_PWM2
    {
        .pin = BSP_IO_PORT_00_PIN_06,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_TIM3_PWM,
    },
#endif
#ifdef BSP_USING_PWM3
    {
        .pin = BSP_IO_PORT_00_PIN_07,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_TIM4_PWM,
    },
#endif
#ifdef BSP_USING_PWM4
    {
        .pin = BSP_IO_PORT_01_PIN_00,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_TIM5_PWM,
    },
#endif
#ifdef BSP_USING_PWM5
    {
        .pin = BSP_IO_PORT_01_PIN_01,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_TIM6_PWM,
    },
#endif
#ifdef BSP_USING_PWM6
    {
        .pin = BSP_IO_PORT_01_PIN_02,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_TIM7_PWM,
    },
#endif
#ifdef BSP_USING_PWM7
    {
        .pin = BSP_IO_PORT_01_PIN_03,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_TIM8_PWM,
    },
#endif

#ifdef BSP_USING_HW_I2C0
    {
        .pin = BSP_IO_PORT_00_PIN_04,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_OPEN_DRAIN_ENABLE | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_I2C_SCL,
    },
    {
        .pin = BSP_IO_PORT_00_PIN_05,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_OPEN_DRAIN_ENABLE | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_I2C_SDA,
    },
#endif
#ifdef BSP_USING_HW_I2C1
    {
        .pin = BSP_IO_PORT_00_PIN_06,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_OPEN_DRAIN_ENABLE | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_I2C2_SCL,
    },
    {
        .pin = BSP_IO_PORT_00_PIN_07,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_OPEN_DRAIN_ENABLE | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_I2C2_SDA,
    },
#endif

#ifdef BSP_USING_ADC
#if BSP_USING_ADC_PIN_NUM >= 1
    {
        .pin = BSP_IO_PORT_00_PIN_04,
        .pin_cfg = GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_ANALOG_ENABLE,
    },
#endif
#if BSP_USING_ADC_PIN_NUM >= 2
    {
        .pin = BSP_IO_PORT_00_PIN_05,
        .pin_cfg = GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_ANALOG_ENABLE,
    },
#endif
#if BSP_USING_ADC_PIN_NUM >= 3
    {
        .pin = BSP_IO_PORT_00_PIN_06,
        .pin_cfg = GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_ANALOG_ENABLE,
    },
#endif
#if BSP_USING_ADC_PIN_NUM >= 4
    {
        .pin = BSP_IO_PORT_00_PIN_07,
        .pin_cfg = GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_ANALOG_ENABLE,
    },
#endif
#endif

#ifdef BSP_USING_SPI0
    {
        .pin = BSP_IO_PORT_01_PIN_00,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_SPI_CLK,
    },
    {
        .pin = BSP_IO_PORT_01_PIN_01,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_SPI_DI,
    },
    {
        .pin = BSP_IO_PORT_01_PIN_02,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_SPI_DO,
    },
    {
        .pin = BSP_IO_PORT_01_PIN_03,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_SPI_CSN0,
    },
#endif
#if defined(BSP_USING_SPI1)
    {
        .pin = BSP_IO_PORT_01_PIN_12,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_SPI2_CLK,
    },
    {
        .pin = BSP_IO_PORT_01_PIN_13,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_SPI2_DI,
    },
    {
        .pin = BSP_IO_PORT_01_PIN_14,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_SPI2_DO,
    },
    {
        .pin = BSP_IO_PORT_01_PIN_15,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST |
                   GPIO_W_PERIPHERAL_SPI2_CSN0,
    },
#endif
#ifdef BSP_USING_QSPI
    {
        .pin = BSP_IO_PORT_00_PIN_08,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST,
    },
    {
        .pin = BSP_IO_PORT_00_PIN_09,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_OUTPUT | GPIO_W_CFG_SLW_FAST,
    },
    {
        .pin = BSP_IO_PORT_00_PIN_10,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_SLW_FAST,
    },
    {
        .pin = BSP_IO_PORT_00_PIN_11,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_SLW_FAST,
    },
    {
        .pin = BSP_IO_PORT_00_PIN_12,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_SLW_FAST,
    },
    {
        .pin = BSP_IO_PORT_00_PIN_13,
        .pin_cfg = GPIO_W_CFG_DRV_8mA | GPIO_W_CFG_PERIPHERAL_PIN |
                   GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_SLW_FAST,
    },
#endif
    {
        .pin = BSP_IO_PORT_01_PIN_16,
        .pin_cfg = GPIO_W_CFG_PERIPHERAL_PIN | GPIO_W_CFG_PORT_DIRECTION_INPUT |
                   GPIO_W_PERIPHERAL_SWCLK,
    },
    {
        .pin = BSP_IO_PORT_01_PIN_17,
        .pin_cfg = GPIO_W_CFG_PERIPHERAL_PIN | GPIO_W_CFG_PORT_DIRECTION_INPUT |
                   GPIO_W_PERIPHERAL_SWDIO,
    },
};

static const char * const g_bsp_pin_cfg_name[] =
{
#ifdef BSP_USING_UART0
    "uart0.rx",
    "uart0.tx",
#endif
#ifdef BSP_USING_UART1
    "uart1.rx",
    "uart1.tx",
#endif
#ifdef BSP_USING_UART2
    "uart2.rx",
    "uart2.tx",
#endif

#ifdef BSP_USING_PWM0
    "pwm0",
#endif

#ifdef BSP_USING_PWM1
    "pwm1",
#endif
#ifdef BSP_USING_PWM2
    "pwm2",
#endif
#ifdef BSP_USING_PWM3
    "pwm3",
#endif
#ifdef BSP_USING_PWM4
    "pwm4",
#endif
#ifdef BSP_USING_PWM5
    "pwm5",
#endif
#ifdef BSP_USING_PWM6
    "pwm6",
#endif
#ifdef BSP_USING_PWM7
    "pwm7",
#endif

#ifdef BSP_USING_HW_I2C0
    "i2c0.scl",
    "i2c0.sda",
#endif
#ifdef BSP_USING_HW_I2C1
    "i2c1.scl",
    "i2c1.sda",
#endif

#ifdef BSP_USING_ADC
#if BSP_USING_ADC_PIN_NUM >= 1
    "adc0",
#endif
#if BSP_USING_ADC_PIN_NUM >= 2
    "adc1",
#endif
#if BSP_USING_ADC_PIN_NUM >= 3
    "adc2",
#endif
#if BSP_USING_ADC_PIN_NUM >= 4
    "adc3",
#endif
#endif

#ifdef BSP_USING_SPI0
    "spi0.clk",
    "spi0.di",
    "spi0.do",
    "spi0.csn0",
#endif
#if defined(BSP_USING_SPI1)
    "spi1.clk",
    "spi1.di",
    "spi1.do",
    "spi1.csn0",
#endif
#ifdef BSP_USING_QSPI
    "qspi.clk",
    "qspi.csn",
    "qspi.io0",
    "qspi.io1",
    "qspi.io2",
    "qspi.io3",
#endif
    "swd.swclk",
    "swd.swdio",
};

#define RA_W_PIN_CFG_COUNT     (sizeof(g_bsp_pin_cfg_data) / sizeof(g_bsp_pin_cfg_data[0]))
#define RA_W_PIN_NAME_COUNT    (sizeof(g_bsp_pin_cfg_name) / sizeof(g_bsp_pin_cfg_name[0]))

struct ra_w_invalid_pin_cfg
{
    const char *cfg_name;
    const char *pin_name;
    bsp_io_port_pin_t default_pin;
};

static struct ra_w_invalid_pin_cfg ra_w_invalid_pin_cfg_data[RA_W_PIN_CFG_COUNT];
static uint32_t ra_w_invalid_pin_cfg_count;
static int ra_w_pin_layout_error;

static int ra_w_pin_valid(bsp_io_port_pin_t pin)
{
    uint32_t port = ((uint32_t) pin & BSP_IO_PORT_BITS) >> BSP_IO_PORT_OFFSET;
    uint32_t pin_id = (uint32_t) pin & BSP_IO_PIN_BITS;

    return (((port == BSP_IO_PORT_00) && (pin_id < BSP_FEATURE_IO_PORT0_GPIO_COUNT)) ||
            ((port == BSP_IO_PORT_01) && (pin_id < BSP_FEATURE_IO_PORT1_GPIO_COUNT)));
}

static void ra_w_pin_to_string(bsp_io_port_pin_t pin, char *buf, uint32_t size)
{
    uint32_t port = ((uint32_t) pin & BSP_IO_PORT_BITS) >> BSP_IO_PORT_OFFSET;
    uint32_t pin_id = (uint32_t) pin & BSP_IO_PIN_BITS;

    rt_snprintf(buf, size, "P%u_%02u", port, pin_id);
}

static const char *ra_w_pin_cfg_name_get(uint32_t index)
{
    if (index < RA_W_PIN_NAME_COUNT)
    {
        return g_bsp_pin_cfg_name[index];
    }

    return "unknown";
}

static void ra_w_invalid_pin_cfg_record(const char *cfg_name,
                                        const char *pin_name,
                                        bsp_io_port_pin_t default_pin)
{
    if (ra_w_invalid_pin_cfg_count < RA_W_PIN_CFG_COUNT)
    {
        ra_w_invalid_pin_cfg_data[ra_w_invalid_pin_cfg_count].cfg_name = cfg_name;
        ra_w_invalid_pin_cfg_data[ra_w_invalid_pin_cfg_count].pin_name = pin_name;
        ra_w_invalid_pin_cfg_data[ra_w_invalid_pin_cfg_count].default_pin = default_pin;
    }

    ra_w_invalid_pin_cfg_count++;
}

static int ra_w_pin_name_parse(const char *name, bsp_io_port_pin_t *p_pin)
{
    int port = -1;
    int pin_id = -1;

    if ((name == RT_NULL) || (p_pin == RT_NULL))
    {
        return -1;
    }

    if (((name[0] == 'P') || (name[0] == 'p')) && (name[1] >= '0') && (name[1] <= '9'))
    {
        port = name[1] - '0';

        if ((name[2] == '_') && (name[3] >= '0') && (name[3] <= '9') &&
                (name[4] >= '0') && (name[4] <= '9') && (name[5] == '\0'))
        {
            pin_id = ((name[3] - '0') * 10) + (name[4] - '0');
        }
        else if ((name[2] >= '0') && (name[2] <= '9') &&
                 (name[3] >= '0') && (name[3] <= '9') && (name[4] == '\0'))
        {
            pin_id = ((name[2] - '0') * 10) + (name[3] - '0');
        }
    }

    if (((port == BSP_IO_PORT_00) && (pin_id >= 0) && (pin_id < BSP_FEATURE_IO_PORT0_GPIO_COUNT)) ||
            ((port == BSP_IO_PORT_01) && (pin_id >= 0) && (pin_id < BSP_FEATURE_IO_PORT1_GPIO_COUNT)))
    {
        *p_pin = (bsp_io_port_pin_t) ((port << BSP_IO_PORT_OFFSET) | pin_id);
        return 0;
    }

    return -1;
}

static bsp_io_port_pin_t ra_w_pin_cfg_get(const char *cfg_name, const char *name, bsp_io_port_pin_t default_pin)
{
    bsp_io_port_pin_t pin;

    if (ra_w_pin_name_parse(name, &pin) == 0)
    {
        return pin;
    }

    ra_w_invalid_pin_cfg_record(cfg_name, name, default_pin);

    return default_pin;
}

static void ra_w_pin_config_set(uint32_t *p_index, const char *cfg_name, const char *pin_name)
{
    uint32_t index = *p_index;

    if (index >= RA_W_PIN_CFG_COUNT)
    {
        ra_w_pin_layout_error = 1;
        return;
    }

    (*p_index)++;
    g_bsp_pin_cfg_data[index].pin = ra_w_pin_cfg_get(cfg_name, pin_name, g_bsp_pin_cfg_data[index].pin);
}

void ra_w_pin_config_check(void)
{
    uint32_t i;
    uint32_t j;
    int error_count = 0;

    for (i = 0; (i < ra_w_invalid_pin_cfg_count) && (i < RA_W_PIN_CFG_COUNT); i++)
    {
        char default_pin_name[8];

        ra_w_pin_to_string(ra_w_invalid_pin_cfg_data[i].default_pin,
                           default_pin_name,
                           sizeof(default_pin_name));
        LOG_E("invalid %s pin \"%s\", use default %s",
              ra_w_invalid_pin_cfg_data[i].cfg_name,
              ra_w_invalid_pin_cfg_data[i].pin_name == RT_NULL ?
              "(null)" : ra_w_invalid_pin_cfg_data[i].pin_name,
              default_pin_name);
        error_count++;
    }

    if (ra_w_invalid_pin_cfg_count > RA_W_PIN_CFG_COUNT)
    {
        LOG_E("%u invalid pin config(s) not listed",
              (unsigned int) (ra_w_invalid_pin_cfg_count - RA_W_PIN_CFG_COUNT));
        error_count++;
    }

    if (ra_w_pin_layout_error)
    {
        LOG_E("pin configuration table layout mismatch");
        error_count++;
    }

    if (RA_W_PIN_CFG_COUNT != RA_W_PIN_NAME_COUNT)
    {
        LOG_E("pin config name count mismatch, cfg=%u name=%u",
              (unsigned int) RA_W_PIN_CFG_COUNT,
              (unsigned int) RA_W_PIN_NAME_COUNT);
        error_count++;
    }

    for (i = 0; i < RA_W_PIN_CFG_COUNT; i++)
    {
        char pin_name[8];

        ra_w_pin_to_string(g_bsp_pin_cfg_data[i].pin, pin_name, sizeof(pin_name));
        if (!ra_w_pin_valid(g_bsp_pin_cfg_data[i].pin))
        {
            LOG_E("invalid config: %s uses %s",
                  ra_w_pin_cfg_name_get(i),
                  pin_name);
            error_count++;
        }

        for (j = i + 1; j < RA_W_PIN_CFG_COUNT; j++)
        {
            if (g_bsp_pin_cfg_data[i].pin == g_bsp_pin_cfg_data[j].pin)
            {
                LOG_E("conflict: %s and %s both use %s",
                      ra_w_pin_cfg_name_get(i),
                      ra_w_pin_cfg_name_get(j),
                      pin_name);
                error_count++;
            }
        }
    }

    if (error_count > 0)
    {
        LOG_E("check failed with %d error(s)", error_count);
    }
    else
    {
        LOG_I("check passed: %u pin(s)", (unsigned int) RA_W_PIN_CFG_COUNT);
    }
}

#ifdef BSP_USING_GPIO_W
static int ra_w_pin_config_check_auto(void)
{
    ra_w_pin_config_check();

    return 0;
}
INIT_COMPONENT_EXPORT(ra_w_pin_config_check_auto);
#endif

void ra_w_pin_config_init(void)
{
    uint32_t index = 0;

    ra_w_invalid_pin_cfg_count = 0;
    ra_w_pin_layout_error = 0;

#ifdef BSP_USING_UART0
    ra_w_pin_config_set(&index, "uart0.rx", BSP_UART0_RX_PIN);
    ra_w_pin_config_set(&index, "uart0.tx", BSP_UART0_TX_PIN);
#endif
#ifdef BSP_USING_UART1
    ra_w_pin_config_set(&index, "uart1.rx", BSP_UART1_RX_PIN);
    ra_w_pin_config_set(&index, "uart1.tx", BSP_UART1_TX_PIN);
#endif
#ifdef BSP_USING_UART2
    ra_w_pin_config_set(&index, "uart2.rx", BSP_UART2_RX_PIN);
    ra_w_pin_config_set(&index, "uart2.tx", BSP_UART2_TX_PIN);
#endif

#ifdef BSP_USING_PWM0
    ra_w_pin_config_set(&index, "pwm0", BSP_PWM0_PIN);
#endif
#ifdef BSP_USING_PWM1
    ra_w_pin_config_set(&index, "pwm1", BSP_PWM1_PIN);
#endif
#ifdef BSP_USING_PWM2
    ra_w_pin_config_set(&index, "pwm2", BSP_PWM2_PIN);
#endif
#ifdef BSP_USING_PWM3
    ra_w_pin_config_set(&index, "pwm3", BSP_PWM3_PIN);
#endif
#ifdef BSP_USING_PWM4
    ra_w_pin_config_set(&index, "pwm4", BSP_PWM4_PIN);
#endif
#ifdef BSP_USING_PWM5
    ra_w_pin_config_set(&index, "pwm5", BSP_PWM5_PIN);
#endif
#ifdef BSP_USING_PWM6
    ra_w_pin_config_set(&index, "pwm6", BSP_PWM6_PIN);
#endif
#ifdef BSP_USING_PWM7
    ra_w_pin_config_set(&index, "pwm7", BSP_PWM7_PIN);
#endif

#ifdef BSP_USING_HW_I2C0
    ra_w_pin_config_set(&index, "i2c0.scl", BSP_I2C0_SCL_PIN);
    ra_w_pin_config_set(&index, "i2c0.sda", BSP_I2C0_SDA_PIN);
#endif
#ifdef BSP_USING_HW_I2C1
    ra_w_pin_config_set(&index, "i2c1.scl", BSP_I2C1_SCL_PIN);
    ra_w_pin_config_set(&index, "i2c1.sda", BSP_I2C1_SDA_PIN);
#endif

#ifdef BSP_USING_ADC
    index += BSP_USING_ADC_PIN_NUM;
#endif

#ifdef BSP_USING_SPI0
    ra_w_pin_config_set(&index, "spi0.clk", BSP_SPI0_CLK_PIN);
    ra_w_pin_config_set(&index, "spi0.di", BSP_SPI0_DI_PIN);
    ra_w_pin_config_set(&index, "spi0.do", BSP_SPI0_DO_PIN);
    ra_w_pin_config_set(&index, "spi0.csn0", BSP_SPI0_CSN0_PIN);
#endif
#if defined(BSP_USING_SPI1)
    ra_w_pin_config_set(&index, "spi1.clk", BSP_SPI1_CLK_PIN);
    ra_w_pin_config_set(&index, "spi1.di", BSP_SPI1_DI_PIN);
    ra_w_pin_config_set(&index, "spi1.do", BSP_SPI1_DO_PIN);
    ra_w_pin_config_set(&index, "spi1.csn0", BSP_SPI1_CSN0_PIN);
#endif

#ifdef BSP_USING_QSPI
    index += 6;
#endif

    /* SWD pins are fixed and are always the last two entries. */
    index += 2;
    if (index != RA_W_PIN_CFG_COUNT)
    {
        ra_w_pin_layout_error = 1;
    }
}

const ioport_cfg_t g_bsp_pin_cfg =
{
    .number_of_pins = sizeof(g_bsp_pin_cfg_data) / sizeof(ioport_pin_cfg_t),
    .p_pin_cfg_data = &g_bsp_pin_cfg_data[0],
};
