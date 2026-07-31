/* generated HAL source file - do not edit */
#include "hal_data.h"
uart_w_instance_ctrl_t g_uart1_ctrl;
/** UART_W extended configuration for UART HAL driver */
uart_w_baud_setting_t g_uart1_baud_setting = { .fra_baud = 26, .int_baud = 43 };

/** UART extended configuration for UART_W HAL driver */
const uart_w_extended_cfg_t g_uart1_cfg_extend =
		{ .fifo_enable = UART_W_FIFO_ENABLE, .rx_fifo_trigger =
				UART_W_RX_FIFO_TRIGGER_SEVEN_EIGHTHS, .tx_fifo_trigger =
				UART_W_TX_FIFO_TRIGGER_EIGHTH, .p_baud_setting =
				&g_uart1_baud_setting, .flow_control =
				UART_W_AUTO_FLOW_CONTROL_DISABLED, .loop_back_enable =
				UART_W_LOOP_BACK_DISABLE, .rs485_enable = UART_W_RS485_DISABLE, };

/** UART interface configuration */
const uart_cfg_t g_uart1_cfg = { .channel = 1 - UART_W_CHANNEL_OFFSET,
		.data_bits = UART_W_DATA_BITS_8, .parity = UART_PARITY_OFF, .stop_bits =
				UART_STOP_BITS_1, .p_callback = user_uart0_callback, .p_context =
				NULL, .p_extend = &g_uart1_cfg_extend,
#define FSP_NOT_DEFINED (1)
#if (FSP_NOT_DEFINED == FSP_NOT_DEFINED)
		.p_transfer_tx = NULL,
#else
                .p_transfer_tx       = &FSP_NOT_DEFINED,
#endif
#if (FSP_NOT_DEFINED == FSP_NOT_DEFINED)
		.p_transfer_rx = NULL,
#else
                .p_transfer_rx       = &FSP_NOT_DEFINED,
#endif
#undef FSP_NOT_DEFINED
		.rxi_ipl = (12),
#if defined(VECTOR_NUMBER_UARTW1_IRQ)
                .rxi_irq             = VECTOR_NUMBER_UARTW1_IRQ,
#else
		.rxi_irq = FSP_INVALID_VECTOR,
#endif

		};

/* Instance structure to use this module. */
const uart_instance_t g_uart1 = { .p_ctrl = &g_uart1_ctrl,
		.p_cfg = &g_uart1_cfg, .p_api = &g_uart_on_uart_w };
void g_hal_init(void) {
	g_common_init();
}
