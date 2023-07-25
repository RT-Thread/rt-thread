/* generated HAL source file - do not edit */
#include "hal_data.h"
dtc_instance_ctrl_t g_transfer1_ctrl;

transfer_info_t g_transfer1_info =
{
    .dest_addr_mode      = TRANSFER_ADDR_MODE_INCREMENTED,
    .repeat_area         = TRANSFER_REPEAT_AREA_DESTINATION,
    .irq                 = TRANSFER_IRQ_END,
    .chain_mode          = TRANSFER_CHAIN_MODE_DISABLED,
    .src_addr_mode       = TRANSFER_ADDR_MODE_FIXED,
    .size                = TRANSFER_SIZE_2_BYTE,
    .mode                = TRANSFER_MODE_NORMAL,
    .p_dest              = (void *) NULL,
    .p_src               = (void const *) NULL,
    .num_blocks          = 0,
    .length              = 0,
};
const dtc_extended_cfg_t g_transfer1_cfg_extend =
{
    .activation_source   = VECTOR_NUMBER_SPI0_RXI,
};
const transfer_cfg_t g_transfer1_cfg =
{
    .p_info              = &g_transfer1_info,
    .p_extend            = &g_transfer1_cfg_extend,
};

/* Instance structure to use this module. */
const transfer_instance_t g_transfer1 =
{
    .p_ctrl        = &g_transfer1_ctrl,
    .p_cfg         = &g_transfer1_cfg,
    .p_api         = &g_transfer_on_dtc
};
dtc_instance_ctrl_t g_transfer0_ctrl;

transfer_info_t g_transfer0_info =
{
    .dest_addr_mode      = TRANSFER_ADDR_MODE_FIXED,
    .repeat_area         = TRANSFER_REPEAT_AREA_SOURCE,
    .irq                 = TRANSFER_IRQ_END,
    .chain_mode          = TRANSFER_CHAIN_MODE_DISABLED,
    .src_addr_mode       = TRANSFER_ADDR_MODE_INCREMENTED,
    .size                = TRANSFER_SIZE_2_BYTE,
    .mode                = TRANSFER_MODE_NORMAL,
    .p_dest              = (void *) NULL,
    .p_src               = (void const *) NULL,
    .num_blocks          = 0,
    .length              = 0,
};
const dtc_extended_cfg_t g_transfer0_cfg_extend =
{
    .activation_source   = VECTOR_NUMBER_SPI0_TXI,
};
const transfer_cfg_t g_transfer0_cfg =
{
    .p_info              = &g_transfer0_info,
    .p_extend            = &g_transfer0_cfg_extend,
};

/* Instance structure to use this module. */
const transfer_instance_t g_transfer0 =
{
    .p_ctrl        = &g_transfer0_ctrl,
    .p_cfg         = &g_transfer0_cfg,
    .p_api         = &g_transfer_on_dtc
};
spi_instance_ctrl_t g_spi0_ctrl;

/** SPI extended configuration for SPI HAL driver */
const spi_extended_cfg_t g_spi0_ext_cfg =
{
    .spi_clksyn         = SPI_SSL_MODE_CLK_SYN,
    .spi_comm           = SPI_COMMUNICATION_FULL_DUPLEX,
    .ssl_polarity        = SPI_SSLP_LOW,
    .ssl_select          = SPI_SSL_SELECT_SSL0,
    .mosi_idle           = SPI_MOSI_IDLE_VALUE_FIXING_DISABLE,
    .parity              = SPI_PARITY_MODE_DISABLE,
    .byte_swap           = SPI_BYTE_SWAP_DISABLE,
    .spck_div            = {
        /* Actual calculated bitrate: 12500000. */ .spbr = 3, .brdv = 0
    },
    .spck_delay          = SPI_DELAY_COUNT_1,
    .ssl_negation_delay  = SPI_DELAY_COUNT_1,
    .next_access_delay   = SPI_DELAY_COUNT_1
 };

/** SPI configuration for SPI HAL driver */
const spi_cfg_t g_spi0_cfg =
{
    .channel             = 0,

#if defined(VECTOR_NUMBER_SPI0_RXI)
    .rxi_irq             = VECTOR_NUMBER_SPI0_RXI,
#else
    .rxi_irq             = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SPI0_TXI)
    .txi_irq             = VECTOR_NUMBER_SPI0_TXI,
#else
    .txi_irq             = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SPI0_TEI)
    .tei_irq             = VECTOR_NUMBER_SPI0_TEI,
#else
    .tei_irq             = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SPI0_ERI)
    .eri_irq             = VECTOR_NUMBER_SPI0_ERI,
#else
    .eri_irq             = FSP_INVALID_VECTOR,
#endif

    .rxi_ipl             = (12),
    .txi_ipl             = (12),
    .tei_ipl             = (12),
    .eri_ipl             = (12),

    .operating_mode      = SPI_MODE_MASTER,

    .clk_phase           = SPI_CLK_PHASE_EDGE_ODD,
    .clk_polarity        = SPI_CLK_POLARITY_LOW,

    .mode_fault          = SPI_MODE_FAULT_ERROR_DISABLE,
    .bit_order           = SPI_BIT_ORDER_MSB_FIRST,
    .p_transfer_tx       = g_spi0_P_TRANSFER_TX,
    .p_transfer_rx       = g_spi0_P_TRANSFER_RX,
    .p_callback          = spi0_callback,

    .p_context           = NULL,
    .p_extend            = (void *)&g_spi0_ext_cfg,
};

/* Instance structure to use this module. */
const spi_instance_t g_spi0 =
{
    .p_ctrl        = &g_spi0_ctrl,
    .p_cfg         = &g_spi0_cfg,
    .p_api         = &g_spi_on_spi
};
icu_instance_ctrl_t g_external_irq0_ctrl;
const external_irq_cfg_t g_external_irq0_cfg =
{
    .channel             = 0,
    .trigger             = EXTERNAL_IRQ_TRIG_RISING,
    .filter_enable       = false,
    .pclk_div            = EXTERNAL_IRQ_PCLK_DIV_BY_64,
    .p_callback          = irq_callback,
    /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
    .p_context           = &NULL,
#endif
    .p_extend            = NULL,
    .ipl                 = (12),
#if defined(VECTOR_NUMBER_ICU_IRQ0)
    .irq                 = VECTOR_NUMBER_ICU_IRQ0,
#else
    .irq                 = FSP_INVALID_VECTOR,
#endif
};
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irq0 =
{
    .p_ctrl        = &g_external_irq0_ctrl,
    .p_cfg         = &g_external_irq0_cfg,
    .p_api         = &g_external_irq_on_icu
};
sci_uart_instance_ctrl_t     g_uart7_ctrl;

            baud_setting_t               g_uart7_baud_setting =
            {
                /* Baud rate calculated with 0.469% error. */ .abcse = 0, .abcs = 0, .bgdm = 1, .cks = 0, .brr = 53, .mddr = (uint8_t) 256, .brme = false
            };

            /** UART extended configuration for UARTonSCI HAL driver */
            const sci_uart_extended_cfg_t g_uart7_cfg_extend =
            {
                .clock                = SCI_UART_CLOCK_INT,
                .rx_edge_start          = SCI_UART_START_BIT_FALLING_EDGE,
                .noise_cancel         = SCI_UART_NOISE_CANCELLATION_DISABLE,
                .rx_fifo_trigger        = SCI_UART_RX_FIFO_TRIGGER_MAX,
                .p_baud_setting         = &g_uart7_baud_setting,
                .flow_control           = SCI_UART_FLOW_CONTROL_RTS,
                #if 0xFF != 0xFF
                .flow_control_pin       = BSP_IO_PORT_FF_PIN_0xFF,
                #else
                .flow_control_pin       = (bsp_io_port_pin_t) UINT16_MAX,
                #endif
            };

            /** UART interface configuration */
            const uart_cfg_t g_uart7_cfg =
            {
                .channel             = 7,
                .data_bits           = UART_DATA_BITS_8,
                .parity              = UART_PARITY_OFF,
                .stop_bits           = UART_STOP_BITS_1,
                .p_callback          = user_uart7_callback,
                .p_context           = NULL,
                .p_extend            = &g_uart7_cfg_extend,
#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
                .p_transfer_tx       = NULL,
#else
                .p_transfer_tx       = &RA_NOT_DEFINED,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
                .p_transfer_rx       = NULL,
#else
                .p_transfer_rx       = &RA_NOT_DEFINED,
#endif
#undef RA_NOT_DEFINED
                .rxi_ipl             = (12),
                .txi_ipl             = (12),
                .tei_ipl             = (12),
                .eri_ipl             = (12),
#if defined(VECTOR_NUMBER_SCI7_RXI)
                .rxi_irq             = VECTOR_NUMBER_SCI7_RXI,
#else
                .rxi_irq             = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI7_TXI)
                .txi_irq             = VECTOR_NUMBER_SCI7_TXI,
#else
                .txi_irq             = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI7_TEI)
                .tei_irq             = VECTOR_NUMBER_SCI7_TEI,
#else
                .tei_irq             = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI7_ERI)
                .eri_irq             = VECTOR_NUMBER_SCI7_ERI,
#else
                .eri_irq             = FSP_INVALID_VECTOR,
#endif
            };

/* Instance structure to use this module. */
const uart_instance_t g_uart7 =
{
    .p_ctrl        = &g_uart7_ctrl,
    .p_cfg         = &g_uart7_cfg,
    .p_api         = &g_uart_on_sci
};
void g_hal_init(void) {
g_common_init();
}
