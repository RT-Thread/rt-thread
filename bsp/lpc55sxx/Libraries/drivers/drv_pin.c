/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-13     Liuguang     the first version.
 * 2018-03-19     Liuguang     add GPIO interrupt mode support.
 * 2018-11-30     yangjie      The first version for LPC54114
 * 2019-07-20     Magicoe      The first version for LPC55S6x
 */
#include "drv_pin.h"

#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_gpio.h"
#include "fsl_gint.h"
#include "fsl_pint.h"
#include "fsl_inputmux.h"

#ifdef RT_USING_PIN

#if defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL
#error "Please don't define 'FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL'!"
#endif

#define get_port(x)      ((x-1) / 32)
#define get_pin(x)       ((x-1) % 32)

#define PIN_MAX_VAL                64
#define IRQ_MAX_VAL                 8

struct lpc_pin
{
    rt_uint16_t   pin;
    GPIO_Type    *gpio;
    rt_uint8_t    gpio_port;
    rt_uint32_t   gpio_pin;
};


#define __ARRAY_LEN(array) (sizeof(array)/sizeof(array[0]))
#define __LPC55S69_PIN_DEFAULT {0, 0, 0, 0}
#define __LPC55S69_PIN(INDEX, REG, PORT, PIN) {INDEX, REG, PORT, PIN}

static struct rt_pin_ops lpc_pin_ops;

static struct lpc_pin lpc_pin_map[] =
{
    __LPC55S69_PIN_DEFAULT,

    /* PIO0 / GPIO0 */
    __LPC55S69_PIN( 1, GPIO, 0,  0),    /* PIO0_00 */
    __LPC55S69_PIN( 2, GPIO, 0,  1),    /* PIO0_01 */
    __LPC55S69_PIN( 3, GPIO, 0,  2),    /* PIO0_02 */
    __LPC55S69_PIN( 4, GPIO, 0,  3),    /* PIO0_04 */
    __LPC55S69_PIN( 5, GPIO, 0,  4),    /* PIO0_04 */
    __LPC55S69_PIN( 6, GPIO, 0,  5),    /* PIO0_05 */
    __LPC55S69_PIN( 7, GPIO, 0,  6),    /* PIO0_06 */
    __LPC55S69_PIN( 8, GPIO, 0,  7),    /* PIO0_07 */
    __LPC55S69_PIN( 9, GPIO, 0,  8),    /* PIO0_08 */
    __LPC55S69_PIN(10, GPIO, 0,  9),    /* PIO0_09 */
    __LPC55S69_PIN(11, GPIO, 0, 10),    /* PIO0_10 */
    __LPC55S69_PIN(12, GPIO, 0, 11),    /* PIO0_11 */
    __LPC55S69_PIN(13, GPIO, 0, 12),    /* PIO0_12 */
    __LPC55S69_PIN(14, GPIO, 0, 13),    /* PIO0_13 */
    __LPC55S69_PIN(15, GPIO, 0, 14),    /* PIO0_14 */
    __LPC55S69_PIN(16, GPIO, 0, 15),    /* PIO0_15 */
    __LPC55S69_PIN(17, GPIO, 0, 16),    /* PIO0_16 */
    __LPC55S69_PIN(18, GPIO, 0, 17),    /* PIO0_17 */
    __LPC55S69_PIN(19, GPIO, 0, 18),    /* PIO0_18 */
    __LPC55S69_PIN(20, GPIO, 0, 19),    /* PIO0_19 */
    __LPC55S69_PIN(21, GPIO, 0, 20),    /* PIO0_20 */
    __LPC55S69_PIN(22, GPIO, 0, 21),    /* PIO0_21 */
    __LPC55S69_PIN(23, GPIO, 0, 22),    /* PIO0_22 */
    __LPC55S69_PIN(24, GPIO, 0, 23),    /* PIO0_23 */
    __LPC55S69_PIN(25, GPIO, 0, 24),    /* PIO0_24 */
    __LPC55S69_PIN(26, GPIO, 0, 25),    /* PIO0_25 */
    __LPC55S69_PIN(27, GPIO, 0, 26),    /* PIO0_26 */
    __LPC55S69_PIN(28, GPIO, 0, 27),    /* PIO0_27 */
    __LPC55S69_PIN(29, GPIO, 0, 28),    /* PIO0_28 */
    __LPC55S69_PIN(30, GPIO, 0, 29),    /* PIO0_29 */
    __LPC55S69_PIN(31, GPIO, 0, 30),    /* PIO0_30 */
    __LPC55S69_PIN(32, GPIO, 0, 31),    /* PIO0_31 */


    /* PIO1 / GPIO, 1 */
    __LPC55S69_PIN(33, GPIO, 1,  0),    /* PIO1_00 */
    __LPC55S69_PIN(34, GPIO, 1,  1),    /* PIO1_01 */
    __LPC55S69_PIN(35, GPIO, 1,  2),    /* PIO1_02 */
    __LPC55S69_PIN(36, GPIO, 1,  3),    /* PIO1_03 */
    __LPC55S69_PIN(37, GPIO, 1,  4),    /* PIO1_04 */
    __LPC55S69_PIN(38, GPIO, 1,  5),    /* PIO1_05 */
    __LPC55S69_PIN(39, GPIO, 1,  6),    /* PIO1_06 */
    __LPC55S69_PIN(40, GPIO, 1,  7),    /* PIO1_07 */
    __LPC55S69_PIN(41, GPIO, 1,  8),    /* PIO1_08 */
    __LPC55S69_PIN(42, GPIO, 1,  9),    /* PIO1_09 */
    __LPC55S69_PIN(43, GPIO, 1, 10),    /* PIO1_10 */
    __LPC55S69_PIN(44, GPIO, 1, 11),    /* PIO1_11 */
    __LPC55S69_PIN(45, GPIO, 1, 12),    /* PIO1_12 */
    __LPC55S69_PIN(46, GPIO, 1, 13),    /* PIO1_13 */
    __LPC55S69_PIN(47, GPIO, 1, 14),    /* PIO1_14 */
    __LPC55S69_PIN(48, GPIO, 1, 15),    /* PIO1_15 */
    __LPC55S69_PIN(49, GPIO, 1, 16),    /* PIO1_16 */
    __LPC55S69_PIN(50, GPIO, 1, 17),    /* PIO1_17 */
    __LPC55S69_PIN(51, GPIO, 1, 18),    /* PIO1_18 */
    __LPC55S69_PIN(52, GPIO, 1, 19),    /* PIO1_19 */
    __LPC55S69_PIN(53, GPIO, 1, 20),    /* PIO1_20 */
    __LPC55S69_PIN(54, GPIO, 1, 21),    /* PIO1_21 */
    __LPC55S69_PIN(55, GPIO, 1, 22),    /* PIO1_22 */
    __LPC55S69_PIN(56, GPIO, 1, 23),    /* PIO1_23 */
    __LPC55S69_PIN(57, GPIO, 1, 24),    /* PIO1_24 */
    __LPC55S69_PIN(58, GPIO, 1, 25),    /* PIO1_25 */
    __LPC55S69_PIN(59, GPIO, 1, 26),    /* PIO1_26 */
    __LPC55S69_PIN(60, GPIO, 1, 27),    /* PIO1_27 */
    __LPC55S69_PIN(61, GPIO, 1, 28),    /* PIO1_28 */
    __LPC55S69_PIN(62, GPIO, 1, 29),    /* PIO1_29 */
    __LPC55S69_PIN(63, GPIO, 1, 30),    /* PIO1_30 */
    __LPC55S69_PIN(64, GPIO, 1, 31),    /* PIO1_31 */
};

struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
{
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
};

static void lpc_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    int dir;
    uint32_t pin_cfg;

    if ((pin > __ARRAY_LEN(lpc_pin_map)) || (pin == 0))
    {
        return;
    }

    switch (mode)
    {
        case PIN_MODE_OUTPUT:
        {
            dir = kGPIO_DigitalOutput;
            pin_cfg = IOCON_FUNC0 | IOCON_DIGITAL_EN | IOCON_MODE_PULLUP;
        }
        break;

        case PIN_MODE_INPUT:
        {
            dir = kGPIO_DigitalInput;
            pin_cfg = IOCON_FUNC0 | IOCON_INPFILT_OFF | IOCON_DIGITAL_EN;
        }
        break;

        case PIN_MODE_INPUT_PULLDOWN:
        {
            dir = kGPIO_DigitalInput;
            pin_cfg = IOCON_FUNC0 | IOCON_INPFILT_OFF | IOCON_DIGITAL_EN | IOCON_MODE_PULLDOWN;
        }
        break;

        case PIN_MODE_INPUT_PULLUP:
        {
            dir = kGPIO_DigitalInput;
            pin_cfg = IOCON_FUNC0 | IOCON_INPFILT_OFF | IOCON_DIGITAL_EN | IOCON_MODE_PULLUP;
        }
        break;

        case PIN_MODE_OUTPUT_OD:
        {
            dir = kGPIO_DigitalOutput;
            pin_cfg = IOCON_FUNC0 | IOCON_OPENDRAIN_EN | IOCON_DIGITAL_EN;
        }
        break;
    }

    /* Enable IOCON Clock */
    CLOCK_EnableClock(kCLOCK_Iocon);
    IOCON->PIO[lpc_pin_map[pin].gpio_port][lpc_pin_map[pin].gpio_pin] = pin_cfg;
    /* Disable IOCON Clock -- To Save Power */
    CLOCK_DisableClock(kCLOCK_Iocon);

    gpio_pin_config_t pin_config = {(gpio_pin_direction_t)dir, 1};
    GPIO_PinInit(GPIO, lpc_pin_map[pin].gpio_port, lpc_pin_map[pin].gpio_pin, &pin_config);
}


static void lpc_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    if ((pin > __ARRAY_LEN(lpc_pin_map)) || (pin == 0))
    {
        return;
    }

    GPIO_PinWrite(lpc_pin_map[pin].gpio, lpc_pin_map[pin].gpio_port, lpc_pin_map[pin].gpio_pin, value);
}

static int lpc_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    if ((pin > __ARRAY_LEN(lpc_pin_map)) || (pin == 0))
    {
        return RT_ERROR;
    }

    value = GPIO_PinRead(lpc_pin_map[pin].gpio, lpc_pin_map[pin].gpio_port, lpc_pin_map[pin].gpio_pin);

    return value;
}


static void pin_irq_hdr(pint_pin_int_t pintr, uint32_t pmatch_status)
{
    int irqno = 0;
    for(irqno = 0; irqno < IRQ_MAX_VAL; irqno ++)
    {
        if((irqno) == pintr)
        {
            break;
        }
    }

    if(irqno >= IRQ_MAX_VAL)
        return;

    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}


void callback(pint_pin_int_t pintr, uint32_t pmatch_status)
{
    pin_irq_hdr(pintr, pmatch_status);
}

/* IRQ handler functions overloading weak symbols in the startup */
void PIN_INT0_IRQHandler(void)
{
    uint32_t pmstatus;

    /* Reset pattern match detection */
    pmstatus = PINT_PatternMatchResetDetectLogic(PINT);

    pin_irq_hdr(kPINT_PinInt0, pmstatus);

    if ((PINT->ISEL & 0x1U) == 0x0U)
    {
        /* Edge sensitive: clear Pin interrupt after callback */
        PINT_PinInterruptClrStatus(PINT, kPINT_PinInt0);
    }
}

static rt_err_t lpc_pin_attach_irq(struct rt_device *device,
                                   rt_int32_t pin,
                                   rt_uint32_t mode,
                                   void (*hdr)(void *args),
                                   void *args)
{
    int trigger_mode, pin_initx, pintsel, pin_cfg, i;

    if ((pin > __ARRAY_LEN(lpc_pin_map)) || (pin == 0))
    {
        return RT_ERROR;
    }

    switch (mode)
    {
        case PIN_IRQ_MODE_RISING:
            trigger_mode = kPINT_PinIntEnableRiseEdge;
            break;
        case PIN_IRQ_MODE_FALLING:
            trigger_mode = kPINT_PinIntEnableFallEdge;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            trigger_mode = kPINT_PinIntEnableBothEdges;
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            trigger_mode = kPINT_PinIntEnableHighLevel;
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            trigger_mode = kPINT_PinIntEnableLowLevel;
            break;
    }

    /* Get inputmux_connection_t */
    pintsel = (pin - 1 + (0xC0U << 20));

    for(i = 0; i < IRQ_MAX_VAL; i++)
    {
        if(pin_irq_hdr_tab[i].pin == -1)
        {
            pin_initx = kPINT_PinInt0 + i;
            pin_irq_hdr_tab[i].pin = pin;
            pin_irq_hdr_tab[i].mode = trigger_mode;
            pin_irq_hdr_tab[i].hdr = hdr;
            pin_irq_hdr_tab[i].args = args;
            break;
        }
    }

    if(i >= IRQ_MAX_VAL)
        return RT_ERROR;

    /* Initialize PINT */
    PINT_Init(PINT);

    /* Enable Input and IOCon clk */
    /* AttachSignal */
    /* Connect trigger sources to PINT */
    INPUTMUX_Init(INPUTMUX);
    INPUTMUX_AttachSignal(INPUTMUX, i, (inputmux_connection_t)pintsel);
    /* Turnoff clock to inputmux to save power. Clock is only needed to make changes */
    INPUTMUX_Deinit(INPUTMUX);

    pin_cfg = ((IOCON->PIO[lpc_pin_map[pin].gpio_port][lpc_pin_map[pin].gpio_pin] &
              (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK | IOCON_PIO_FILTEROFF_MASK))) /* Mask bits to zero which are setting */
              | IOCON_PIO_FUNC(0)                /* Selects pin function.: PORT18 (pin 28) is configured as PIO1_8 */
              | IOCON_PIO_DIGIMODE(1)            /* Select Analog/Digital mode.: Digital mode. */
              | IOCON_PIO_FILTEROFF(0));         /* Controls input glitch filter.: Filter enabled. Noise pulses below approximately 10 ns are filtered out. */

    IOCON_PinMuxSet(IOCON, lpc_pin_map[pin].gpio_port, lpc_pin_map[pin].gpio_pin, pin_cfg);

    /* PINT_PinInterruptConfig */
    PINT_PinInterruptConfig(PINT, (pint_pin_int_t)pin_initx, (pint_pin_enable_t)(pin_irq_hdr_tab[i].mode), callback);
    /* Enable callbacks for PINTx by Index */
    PINT_EnableCallbackByIndex(PINT, (pint_pin_int_t)pin_initx);

    return RT_EOK;
}

static rt_err_t lpc_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    int i;

    if ((pin > __ARRAY_LEN(lpc_pin_map)) || (pin == 0))
    {
        return RT_ERROR;
    }

    for(i = 0; i < IRQ_MAX_VAL; i++)
    {
        if(pin_irq_hdr_tab[i].pin == pin)
        {
            pin_irq_hdr_tab[i].pin = -1;
            pin_irq_hdr_tab[i].hdr = RT_NULL;
            pin_irq_hdr_tab[i].mode = 0;
            pin_irq_hdr_tab[i].args = RT_NULL;
            break;
        }
    }
    return RT_EOK;
}

static rt_err_t lpc_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{
    int irqn_type, i;

    if ((pin > __ARRAY_LEN(lpc_pin_map)) || (pin == 0))
    {
        return RT_ERROR;
    }

    for(i = 0; i < IRQ_MAX_VAL; i++)
    {
        if(pin_irq_hdr_tab[i].pin == pin)
        {
            switch(i)
            {
                case 0: irqn_type = PIN_INT0_IRQn; break;
                case 1: irqn_type = PIN_INT1_IRQn; break;
                case 2: irqn_type = PIN_INT2_IRQn; break;
                case 3: irqn_type = PIN_INT3_IRQn; break;
                case 4: irqn_type = PIN_INT4_IRQn; break;
                case 5: irqn_type = PIN_INT5_IRQn; break;
                case 6: irqn_type = PIN_INT6_IRQn; break;
                case 7: irqn_type = PIN_INT7_IRQn; break;
                default:break;
            }
            if(enabled)
            {
                /* PINT_EnableCallback */
                PINT_PinInterruptClrStatusAll(PINT);
                NVIC_ClearPendingIRQ((IRQn_Type)irqn_type);
                PINT_PinInterruptClrStatus(PINT, (pint_pin_int_t)(kPINT_PinInt0 + i));
                EnableIRQ((IRQn_Type)irqn_type);
            }
            else
            {
                /* PINT_DisableCallback */
                DisableIRQ((IRQn_Type)irqn_type);
                PINT_PinInterruptClrStatus(PINT, (pint_pin_int_t)(kPINT_PinInt0 + i));
                NVIC_ClearPendingIRQ((IRQn_Type)irqn_type);
            }
            break;
        }
    }

    if(i >= IRQ_MAX_VAL)
        return RT_ERROR;

    return RT_EOK;
}

int rt_hw_pin_init(void)
{
    int ret = RT_EOK;

    lpc_pin_ops.pin_mode        = lpc_pin_mode;
    lpc_pin_ops.pin_read        = lpc_pin_read;
    lpc_pin_ops.pin_write       = lpc_pin_write;
    lpc_pin_ops.pin_attach_irq  = lpc_pin_attach_irq;
    lpc_pin_ops.pin_detach_irq  = lpc_pin_detach_irq;
    lpc_pin_ops.pin_irq_enable  = lpc_pin_irq_enable;
    lpc_pin_ops.pin_get         = RT_NULL,

    ret = rt_device_pin_register("pin", &lpc_pin_ops, RT_NULL);

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /*RT_USING_PIN */

// end file
