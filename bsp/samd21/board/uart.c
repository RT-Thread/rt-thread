// From module: SERCOM Callback API
#include <samd21.h>
#include <sercom.h>
// #include <sercom_interrupt.h>

// From module: SERCOM USART - Serial Communications (Callback APIs)
#include <usart.h>
// #include <usart_interrupt.h>

#include <rtdevice.h>

typedef struct _samd2x_uart_t
{
    struct rt_serial_device *serial;
    struct usart_module *instance;
    Sercom *com;
    enum usart_signal_mux_settings mux_setting;
    uint32_t pinmux_pad0;
    uint32_t pinmux_pad1;
    uint32_t pinmux_pad2;
    uint32_t pinmux_pad3;
    enum system_interrupt_vector vector;
} SAMD2x_UART_T;

static struct rt_serial_device _serial3;
static struct usart_module _uart3_instance;
static SAMD2x_UART_T _uart3 = {
    &_serial3,
    &_uart3_instance,
    SERCOM3,
    USART_RX_1_TX_0_XCK_1,
    PINMUX_PA22C_SERCOM3_PAD0,
    PINMUX_PA23C_SERCOM3_PAD1,
    PINMUX_UNUSED,
    PINMUX_UNUSED,
    SYSTEM_INTERRUPT_MODULE_SERCOM3
};

// static struct rt_serial_device _serial2;
// static struct rt_serial_device _serial3;
// static struct rt_serial_device _serial4;

static rt_err_t _uart_cfg(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    SAMD2x_UART_T *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (SAMD2x_UART_T *)serial->parent.user_data;
    //! [setup_config]
	struct usart_config config_usart;
    //! [setup_config]
    //! [setup_config_defaults]
    usart_get_config_defaults(&config_usart);
    //! [setup_config_defaults]
    config_usart.baudrate = cfg->baud_rate;

    switch (cfg->data_bits )
    {
    case DATA_BITS_8:
        config_usart.character_size = USART_CHARACTER_SIZE_8BIT;
        break;

    case DATA_BITS_5:
        config_usart.character_size = USART_CHARACTER_SIZE_5BIT;
        break;

    case DATA_BITS_6:
        config_usart.character_size = USART_CHARACTER_SIZE_6BIT;
        break;

    case DATA_BITS_7:
        config_usart.character_size = USART_CHARACTER_SIZE_7BIT;
        break;

    case DATA_BITS_9:
        config_usart.character_size = USART_CHARACTER_SIZE_9BIT;
        break;

    default:
        config_usart.character_size = USART_CHARACTER_SIZE_8BIT;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_NONE:
        config_usart.parity = USART_PARITY_NONE;
        break;

    case PARITY_EVEN:
        config_usart.parity = USART_PARITY_EVEN;
        break;

    case PARITY_ODD:
        config_usart.parity = USART_PARITY_ODD;
        break;

    default:
        config_usart.parity = USART_PARITY_NONE;
        break;
    }

    config_usart.stopbits = USART_STOPBITS_1;
    if (cfg->stop_bits != USART_STOPBITS_1)
    {
        config_usart.stopbits = USART_STOPBITS_2;
    }

    config_usart.data_order = USART_DATAORDER_LSB;
    if (cfg->bit_order != BIT_ORDER_LSB)
    {
        config_usart.data_order = USART_DATAORDER_MSB;
    }

    config_usart.mux_setting = uart->mux_setting;
    config_usart.pinmux_pad0 = uart->pinmux_pad0;
    config_usart.pinmux_pad1 = uart->pinmux_pad1;
    config_usart.pinmux_pad2 = uart->pinmux_pad2;
    config_usart.pinmux_pad3 = uart->pinmux_pad3;
    config_usart.receiver_enable = false;
    config_usart.transmitter_enable = true;

    while (usart_init(uart->instance, uart->com, &config_usart) != STATUS_OK) {
    }

    usart_enable(uart->instance);
    /* Wait for the synchronization to complete */
    _usart_wait_for_sync(uart->instance);

    return RT_EOK;
}

static rt_err_t _uart_ctrl(struct rt_serial_device *serial, int cmd, void *arg)
{
    SAMD2x_UART_T *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (SAMD2x_UART_T *)(serial->parent.user_data);

    switch (cmd)
    {
        /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        uart->com->USART.INTENCLR.reg = SERCOM_USART_INTFLAG_RXC;
        usart_disable_transceiver(uart->instance, USART_TRANSCEIVER_RX);
        system_interrupt_disable(uart->vector);
        /* Wait for the synchronization to complete */
	    _usart_wait_for_sync(uart->instance);
        break;
        /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* Enable RX interrupt. */
        /* Enable the RX Complete Interrupt */
        uart->com->USART.INTENSET.reg = SERCOM_USART_INTFLAG_RXC;
        usart_enable_transceiver(uart->instance, USART_TRANSCEIVER_RX);
        system_interrupt_enable(uart->vector);
        /* Wait for the synchronization to complete */
	    _usart_wait_for_sync(uart->instance);
        break;

    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

static int _uart_putc(struct rt_serial_device *serial, char c)
{
    SAMD2x_UART_T *uart;

    RT_ASSERT(serial != RT_NULL);

    // while (!(uart->com->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_DRE)) {
    // }

    uart = (SAMD2x_UART_T *)(serial->parent.user_data);

	/* Write data to USART module */
	uart->com->USART.DATA.reg = c;

	while (!(uart->com->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_TXC)) {
		/* Wait until data is sent */
    }

    return 1;
}

static int _uart_getc(struct rt_serial_device *serial)
{
    int ch;
    SAMD2x_UART_T *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (SAMD2x_UART_T *)(serial->parent.user_data);

    /* Check if USART has new data */
	if (!(uart->com->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_RXC)) {
		/* Return error code */
		return -1;
    }

    ch = uart->com->USART.DATA.reg & 0x1FF;

    return ch;
}

static struct rt_uart_ops _uart_ops = {
    _uart_cfg,
    _uart_ctrl,
    _uart_putc,
    _uart_getc
};

static void uart_int_cb(SAMD2x_UART_T *uart_handle)
{
    /* Temporary variables */
	uint16_t interrupt_status;
	uint8_t error_code;
    struct usart_module *module = uart_handle->instance;
	/* Pointer to the hardware module instance */
	SercomUsart *const usart_hw = &(module->hw->USART);

	/* Read and mask interrupt flag register */
	interrupt_status = usart_hw->INTFLAG.reg;
	interrupt_status &= usart_hw->INTENSET.reg;

	/* Check if the Receive Complete interrupt has occurred, and that
	 * there's more data to receive */
	if (interrupt_status & SERCOM_USART_INTFLAG_RXC) {
        /* Read out the status code and mask away all but the 4 LSBs*/
        error_code = (uint8_t)(usart_hw->STATUS.reg & SERCOM_USART_STATUS_MASK);
#if !SAMD20
        /* CTS status should not be considered as an error */
        if(error_code & SERCOM_USART_STATUS_CTS) {
            error_code &= ~SERCOM_USART_STATUS_CTS;
        }
#endif
#ifdef FEATURE_USART_LIN_MASTER
        /* TXE status should not be considered as an error */
        if(error_code & SERCOM_USART_STATUS_TXE) {
            error_code &= ~SERCOM_USART_STATUS_TXE;
        }
#endif
        /* Check if an error has occurred during the receiving */
        if (error_code) {
            /* Check which error occurred */
            if (error_code & SERCOM_USART_STATUS_FERR) {
                /* clear flag by writing 1 to it */
                usart_hw->STATUS.reg = SERCOM_USART_STATUS_FERR;
            } else if (error_code & SERCOM_USART_STATUS_BUFOVF) {
                /* clear flag by writing 1 to it */
                usart_hw->STATUS.reg = SERCOM_USART_STATUS_BUFOVF;
            } else if (error_code & SERCOM_USART_STATUS_PERR) {
                /* clear flag by writing 1 to it */
                usart_hw->STATUS.reg = SERCOM_USART_STATUS_PERR;
            }
#ifdef FEATURE_USART_LIN_SLAVE
            else if (error_code & SERCOM_USART_STATUS_ISF) {
                /* clear flag by writing 1 to it */
                usart_hw->STATUS.reg = SERCOM_USART_STATUS_ISF;
            }
#endif
#ifdef FEATURE_USART_COLLISION_DECTION
            else if (error_code & SERCOM_USART_STATUS_COLL) {
                /* clear flag by writing 1 to it */
                usart_hw->STATUS.reg = SERCOM_USART_STATUS_COLL;
            }
#endif
        } else {
            rt_hw_serial_isr(uart_handle->serial, RT_SERIAL_EVENT_RX_IND);
        }
	}

#ifdef FEATURE_USART_HARDWARE_FLOW_CONTROL
	if (interrupt_status & SERCOM_USART_INTFLAG_CTSIC) {
		/* Disable interrupts */
		usart_hw->INTENCLR.reg = SERCOM_USART_INTENCLR_CTSIC;
		/* Clear interrupt flag */
		usart_hw->INTFLAG.reg = SERCOM_USART_INTFLAG_CTSIC;
	}
#endif

#ifdef FEATURE_USART_LIN_SLAVE
	if (interrupt_status & SERCOM_USART_INTFLAG_RXBRK) {
		/* Disable interrupts */
		usart_hw->INTENCLR.reg = SERCOM_USART_INTENCLR_RXBRK;
		/* Clear interrupt flag */
		usart_hw->INTFLAG.reg = SERCOM_USART_INTFLAG_RXBRK;
	}
#endif

#ifdef FEATURE_USART_START_FRAME_DECTION
	if (interrupt_status & SERCOM_USART_INTFLAG_RXS) {
		/* Disable interrupts */
		usart_hw->INTENCLR.reg = SERCOM_USART_INTENCLR_RXS;
		/* Clear interrupt flag */
		usart_hw->INTFLAG.reg = SERCOM_USART_INTFLAG_RXS;
	}
#endif
}

void SERCOM3_Handler(void)
{
    uart_int_cb(&_uart3);
}

void uart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    config.bufsz = 512;
    _serial3.config = config;
    _serial3.ops = &_uart_ops;

    rt_hw_serial_register(&_serial3, "uart3", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, &_uart3);
}
