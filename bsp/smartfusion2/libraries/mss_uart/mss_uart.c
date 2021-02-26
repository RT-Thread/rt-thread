/*******************************************************************************
 * (c) Copyright 2011-2013 Microsemi SoC Products Group.  All rights reserved.
 *
 * SmartFusion2 Microcontroller Subsystem MMUART bare metal software driver
 * implementation.
 *
 * SVN $Revision: 5610 $
 * SVN $Date: 2013-04-05 18:49:30 +0530 (Fri, 05 Apr 2013) $
 */
#include "mss_uart.h"
#include "mss_uart_regs.h"
#include "../../CMSIS/mss_assert.h"
#include "../../CMSIS/hw_reg_io.h"
#include "../../CMSIS/system_m2sxxx.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*******************************************************************************
 * Defines
 */
#define TX_COMPLETE            0u
#define TX_FIFO_SIZE           16u

#define FCR_TRIG_LEVEL_MASK    0xC0u

#define IIRF_MASK              0x0Fu

#define INVALID_INTERRUPT      0u
#define INVALID_IRQ_HANDLER    ((mss_uart_irq_handler_t) 0)
#define NULL_HANDLER           ((mss_uart_irq_handler_t) 0)

#define MSS_UART_DATA_READY    ((uint8_t) 0x01)

#define SYNC_ASYNC_MODE_MASK   (0x7u)

/*******************************************************************************
 * Possible values for Interrupt Identification Register Field.
 */
#define IIRF_MODEM_STATUS   0x00u
#define IIRF_THRE           0x02u
#define IIRF_MMI            0x03u
#define IIRF_RX_DATA        0x04u
#define IIRF_RX_LINE_STATUS 0x06u
#define IIRF_DATA_TIMEOUT   0x0Cu

/*******************************************************************************
 * Receiver error status mask.
 */
#define STATUS_ERROR_MASK    ( MSS_UART_OVERUN_ERROR | MSS_UART_PARITY_ERROR | \
                               MSS_UART_FRAMING_ERROR  | MSS_UART_BREAK_ERROR | \
                               MSS_UART_FIFO_ERROR)

/*******************************************************************************
 * Cortex-M3 interrupt handler functions implemented as part of the MSS UART
 * driver.
 */
#if defined(__GNUC__)
__attribute__((__interrupt__)) void UART0_IRQHandler(void);
#else
void UART0_IRQHandler(void);
#endif

#if defined(__GNUC__)
__attribute__((__interrupt__)) void UART1_IRQHandler(void);
#else
void UART1_IRQHandler(void);
#endif

/*******************************************************************************
 * Local functions.
 */
static void global_init(mss_uart_instance_t * this_uart, uint32_t baud_rate, 
                        uint8_t line_config);
static void MSS_UART_isr(mss_uart_instance_t * this_uart);
static void default_tx_handler(mss_uart_instance_t * this_uart);

static void config_baud_divisors
(
    mss_uart_instance_t * this_uart,
    uint32_t baudrate    
);

/*******************************************************************************
 * Instance definitions
 */
mss_uart_instance_t g_mss_uart0;
mss_uart_instance_t g_mss_uart1;


/*******************************************************************************
 * Public Functions
 *******************************************************************************/
/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void 
MSS_UART_init
(
    mss_uart_instance_t* this_uart, 
    uint32_t baud_rate,
    uint8_t line_config
)
{
    /* The driver expects g_mss_uart0 and g_mss_uart1 to be the only
     * mss_uart_instance_t instances used to identify UART0 and UART1. */
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    /* Perform generic initialization */
    global_init(this_uart, baud_rate, line_config);

    /* Disable LIN mode */
    clear_bit_reg8(&this_uart->hw_reg->MM0, ELIN);

    /* Disable IrDA mode */
    clear_bit_reg8(&this_uart->hw_reg->MM1, EIRD);

    /* Disable SmartCard Mode */
    clear_bit_reg8(&this_uart->hw_reg->MM2, EERR);

    /* set default tx handler for automated TX using interrupt in USART mode */
    this_uart->tx_handler = default_tx_handler;
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void MSS_UART_lin_init
(
    mss_uart_instance_t* this_uart, 
    uint32_t baud_rate,
    uint8_t line_config
)
{
    /* The driver expects g_mss_uart0 and g_mss_uart1 to be the only
     * mss_uart_instance_t instances used to identify UART0 and UART1. */
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    /* Perform generic initialization */
    global_init(this_uart, baud_rate, line_config);

     /* Enable LIN mode */
    set_bit_reg8(&this_uart->hw_reg->MM0, ELIN);

    /* Disable IrDA mode */
    clear_bit_reg8(&this_uart->hw_reg->MM1, EIRD);

    /* Disable SmartCard Mode */
    clear_bit_reg8(&this_uart->hw_reg->MM2, EERR);
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void 
MSS_UART_irda_init
(
    mss_uart_instance_t* this_uart, 
    uint32_t baud_rate,
    uint8_t line_config,
    mss_uart_rzi_polarity_t rxpol,
    mss_uart_rzi_polarity_t txpol,
    mss_uart_rzi_pulsewidth_t pw
)
{
    /* The driver expects g_mss_uart0 and g_mss_uart1 to be the only
     * mss_uart_instance_t instances used to identify UART0 and UART1. */
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    /* Perform generic initialization */
    global_init(this_uart, baud_rate, line_config);

     /* Enable LIN mode */
    clear_bit_reg8(&this_uart->hw_reg->MM0, ELIN);

    /* Disable IrDA mode */
    set_bit_reg8(&this_uart->hw_reg->MM1, EIRD);
    ((rxpol == MSS_UART_ACTIVE_LOW) ? clear_bit_reg8(&this_uart->hw_reg->MM1,EIRX) : 
                                      set_bit_reg8(&this_uart->hw_reg->MM1,EIRX));
                                      
    ((txpol == MSS_UART_ACTIVE_LOW) ? clear_bit_reg8(&this_uart->hw_reg->MM1,EITX) : 
                                      set_bit_reg8(&this_uart->hw_reg->MM1,EITX));
                                      
    ((pw == MSS_UART_3_BY_16) ? clear_bit_reg8(&this_uart->hw_reg->MM1,EITP) : 
                                      set_bit_reg8(&this_uart->hw_reg->MM1,EITP));
    /* Disable SmartCard Mode */
    clear_bit_reg8(&this_uart->hw_reg->MM2, EERR);
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void 
MSS_UART_smartcard_init
(
    mss_uart_instance_t* this_uart, 
    uint32_t baud_rate,
    uint8_t line_config
)
{
    /* The driver expects g_mss_uart0 and g_mss_uart1 to be the only
     * mss_uart_instance_t instances used to identify UART0 and UART1. */
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    /* Perform generic initialization */
    global_init(this_uart, baud_rate, line_config);
    
    /* Disable LIN mode */
    clear_bit_reg8(&this_uart->hw_reg->MM0, ELIN);

    /* Disable IrDA mode */
    clear_bit_reg8(&this_uart->hw_reg->MM1, EIRD);

    /* Enable SmartCard Mode : Only when data is 8-bit and 2 stop bits*/
    if( ( MSS_UART_DATA_8_BITS | MSS_UART_TWO_STOP_BITS) == 
        (line_config & (MSS_UART_DATA_8_BITS | MSS_UART_TWO_STOP_BITS)))
    {
        set_bit_reg8(&this_uart->hw_reg->MM2, EERR);    
        /* Enable single wire half-duplex mode */
        set_bit_reg8(&this_uart->hw_reg->MM2,ESWM);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_polled_tx
(
    mss_uart_instance_t * this_uart,
    const uint8_t * pbuff,
    uint32_t tx_size
)
{
    uint32_t char_idx = 0u;
    uint32_t size_sent;
    uint8_t status;

    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(pbuff != ( (uint8_t *)0));
    ASSERT(tx_size > 0u);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
        (pbuff != ((uint8_t *)0)) && (tx_size > 0u))
    {
         /* Remain in this loop until the entire input buffer
          * has been transferred to the UART.
          */
        do {
            /* Read the Line Status Register and update the sticky record */
            status = this_uart->hw_reg->LSR;
            this_uart->status |= status;

            /* Check if TX FIFO is empty. */
            if(status & MSS_UART_THRE)
            {
                uint32_t fill_size = TX_FIFO_SIZE;

                /* Calculate the number of bytes to transmit. */
                if(tx_size < TX_FIFO_SIZE)
                {
                    fill_size = tx_size;
                }

                /* Fill the TX FIFO with the calculated the number of bytes. */
                for(size_sent = 0u; size_sent < fill_size; ++size_sent)
                {
                    /* Send next character in the buffer. */
                    this_uart->hw_reg->THR = pbuff[char_idx];
                    char_idx++;
                }

                /* Calculate the number of untransmitted bytes remaining. */
                tx_size -= size_sent;
            }
        } while(tx_size);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_polled_tx_string
(
    mss_uart_instance_t * this_uart,
    const uint8_t * p_sz_string
)
{
    uint32_t char_idx = 0u;
    uint32_t fill_size;
    uint8_t data_byte;
    uint8_t status;

    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(p_sz_string != ((uint8_t *)0));

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
       (p_sz_string != ((uint8_t *)0)))
    {
        /* Get the first data byte from the input buffer */
        data_byte = p_sz_string[char_idx];

        /* First check for the NULL terminator byte.
         * Then remain in this loop until the entire string in the input buffer
         * has been transferred to the UART.
         */
        while(0u != data_byte)
        {
            /* Wait until TX FIFO is empty. */
            do {
                status = this_uart->hw_reg->LSR;
                this_uart->status |= status;
            } while (0u == (status & MSS_UART_THRE));

            /* Send bytes from the input buffer until the TX FIFO is full
             * or we reach the NULL terminator byte.
             */
            fill_size = 0u;
            while((0u != data_byte) && (fill_size < TX_FIFO_SIZE))
            {
                /* Send the data byte */
                this_uart->hw_reg->THR = data_byte;
                ++fill_size;
                char_idx++;
                /* Get the next data byte from the input buffer */
                data_byte = p_sz_string[char_idx];
            }
        }
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_irq_tx
(
    mss_uart_instance_t * this_uart,
    const uint8_t * pbuff,
    uint32_t tx_size
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(pbuff != ((uint8_t *)0));
    ASSERT(tx_size > 0u);

    if((tx_size > 0u) && ( pbuff != ((uint8_t *)0)) &&
      ((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)))
    {
        /*Initialise the transmit info for the UART instance with the arguments.*/
        this_uart->tx_buffer = pbuff;
        this_uart->tx_buff_size = tx_size;
        this_uart->tx_idx = (uint16_t)0;

        /* Clear any previously pended interrupts */
        NVIC_ClearPendingIRQ(this_uart->irqn);

        /* assign default handler for data transfer */
        this_uart->tx_handler = default_tx_handler;

        /* enables TX interrupt */
        set_bit_reg8(&this_uart->hw_reg->IER,ETBEI);

        /* Enable UART instance interrupt in Cortex-M3 NVIC. */
        NVIC_EnableIRQ(this_uart->irqn);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
int8_t
MSS_UART_tx_complete
(
    mss_uart_instance_t * this_uart
)
{
    int8_t ret_value = 0;
    uint8_t status = 0u;

    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /* Read the Line Status Register and update the sticky record. */
        status = this_uart->hw_reg->LSR;
        this_uart->status |= status;

        if((TX_COMPLETE == this_uart->tx_buff_size) &&
           ((status & MSS_UART_TEMT) != 0u))
        {
            ret_value = (int8_t)1;
        }
    }
    return ret_value;
}


/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
size_t
MSS_UART_get_rx
(
    mss_uart_instance_t * this_uart,
    uint8_t * rx_buff,
    size_t buff_size
)
{
    size_t rx_size = 0u;
    uint8_t status = 0u;

    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(rx_buff != ((uint8_t *)0));
    ASSERT(buff_size > 0u);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
       (rx_buff != ((uint8_t *)0)) && (buff_size > 0u))
    {
        status = this_uart->hw_reg->LSR;
        this_uart->status |= status;

        while(((status & MSS_UART_DATA_READY) != 0u) &&
              (rx_size < buff_size))
        {
            rx_buff[rx_size] = this_uart->hw_reg->RBR;
            ++rx_size;
            status = this_uart->hw_reg->LSR;
            this_uart->status |= status;
        }
    }
    return rx_size;
}
/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_enable_irq
(
    mss_uart_instance_t * this_uart,
    mss_uart_irq_t irq_mask
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(MSS_UART_INVALID_IRQ > irq_mask);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) && 
       (MSS_UART_INVALID_IRQ > irq_mask))
    {
        /* Clear any previously pended interrupts */
        NVIC_ClearPendingIRQ(this_uart->irqn);

        /* irq_mask encoding: 1- enable
         * bit 0 - Receive Data Available Interrupt
         * bit 1 - Transmitter Holding  Register Empty Interrupt
         * bit 2 - Receiver Line Status Interrupt
         * bit 3 - Modem Status Interrupt
         */
        this_uart->hw_reg->IER |= (uint8_t)irq_mask & IIRF_MASK;

        /* 
         * bit 4 - Receiver time-out interrupt
         * bit 5 - NACK / ERR signal interrupt
         * bit 6 - PID parity error interrupt 
         * bit 7 - LIN break detection interrupt
         * bit 8 - LIN Sync detection interrupt
         */
        this_uart->hw_reg->IEM |= (uint8_t)(((uint32_t)irq_mask & ~((uint32_t)IIRF_MASK)) >> 4u);

        /* Enable UART instance interrupt in Cortex-M3 NVIC. */
        NVIC_EnableIRQ(this_uart->irqn);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_disable_irq
(
    mss_uart_instance_t * this_uart,
    mss_uart_irq_t irq_mask
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /* irq_mask encoding: 1 - disable
         * bit 0 - Receive Data Available Interrupt
         * bit 1 - Transmitter Holding  Register Empty Interrupt
         * bit 2 - Receiver Line Status Interrupt
         * bit 3 - Modem Status Interrupt
         */
        this_uart->hw_reg->IER &= ((uint8_t)(~((uint32_t)irq_mask & (uint32_t)IIRF_MASK)));

        /* 
         * bit 4 - Receiver time-out interrupt
         * bit 5 - NACK / ERR signal interrupt
         * bit 6 - PID parity error interrupt 
         * bit 7 - LIN break detection interrupt
         * bit 8 - LIN Sync detection interrupt
         */
        this_uart->hw_reg->IEM |= (uint8_t)(~(((uint32_t)irq_mask & ~((uint32_t)IIRF_MASK)) >> 8u));

        /* Clear any previously pended interrupts */
        NVIC_ClearPendingIRQ(this_uart->irqn);

        if(irq_mask == IIRF_MASK)
        {
            /* Disable UART instance interrupt in Cortex-M3 NVIC. */
            NVIC_DisableIRQ(this_uart->irqn);

        }
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_set_rx_handler
(
    mss_uart_instance_t *       this_uart,
    mss_uart_irq_handler_t      handler,
    mss_uart_rx_trig_level_t    trigger_level
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(handler != INVALID_IRQ_HANDLER );
    ASSERT(trigger_level < MSS_UART_FIFO_INVALID_TRIG_LEVEL);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
       (handler != INVALID_IRQ_HANDLER) &&
       (trigger_level < MSS_UART_FIFO_INVALID_TRIG_LEVEL))
    {
        this_uart->rx_handler = handler;

        /* Set the receive interrupt trigger level. */
        this_uart->hw_reg->FCR = (this_uart->hw_reg->FCR &
                                 (uint8_t)(~((uint8_t)FCR_TRIG_LEVEL_MASK))) |
                                 (uint8_t)trigger_level;
        /* Clear any previously pended interrupts */
        NVIC_ClearPendingIRQ(this_uart->irqn);

        /* Enable receive interrupt. */
        set_bit_reg8(&this_uart->hw_reg->IER,ERBFI);

        /* Enable UART instance interrupt in Cortex-M3 NVIC. */
        NVIC_EnableIRQ(this_uart->irqn);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_set_loopback
(
    mss_uart_instance_t *   this_uart,
    mss_uart_loopback_t     loopback
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(MSS_UART_INVALID_LOOPBACK > loopback);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) ||
       (MSS_UART_INVALID_LOOPBACK > loopback))
    {
        switch(loopback)
        {
            case MSS_UART_LOCAL_LOOPBACK_OFF:
                /* Disable local loopback */
                clear_bit_reg8(&this_uart->hw_reg->MCR,LOOP);
                break;
                
            case MSS_UART_LOCAL_LOOPBACK_ON:
                /* Enable local loopback */
                set_bit_reg8(&this_uart->hw_reg->MCR,LOOP);
                break;
            
            case MSS_UART_REMOTE_LOOPBACK_OFF:
            case MSS_UART_AUTO_ECHO_OFF:
                /* Disable remote loopback & automatic echo*/
                this_uart->hw_reg->MCR &= ~RLOOP_MASK;
                break;
            
            case MSS_UART_REMOTE_LOOPBACK_ON:
                /* Enable remote loopback */
                this_uart->hw_reg->MCR |= (1u << RLOOP);
                break;
                
            case MSS_UART_AUTO_ECHO_ON:
                /* Enable automatic echo */
                this_uart->hw_reg->MCR |= (1u << ECHO);
                break;
                
            case MSS_UART_INVALID_LOOPBACK:
                /* Fall through to default. */
            default:
                ASSERT(0);
                break;
        }
    }
}

/***************************************************************************//**
 * UART0 interrupt service routine.
 * UART0_IRQHandler is included within the Cortex-M3 vector table as part of the
 * Fusion 2 CMSIS.
 */
#if defined(__GNUC__)
__attribute__((__interrupt__)) void UART0_IRQHandler(void)
#else
void UART0_IRQHandler(void)
#endif
{
    MSS_UART_isr(&g_mss_uart0);
}

/***************************************************************************//**
 * UART1 interrupt service routine.
 * UART2_IRQHandler is included within the Cortex-M3 vector table as part of the
 * Fusion 2 CMSIS.
 */
#if defined(__GNUC__)
__attribute__((__interrupt__)) void UART1_IRQHandler(void)
#else
void UART1_IRQHandler(void)
#endif
{
    MSS_UART_isr(&g_mss_uart1);
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_set_rxstatus_handler
(
    mss_uart_instance_t * this_uart,
    mss_uart_irq_handler_t handler
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(handler != INVALID_IRQ_HANDLER);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
       (handler != INVALID_IRQ_HANDLER))
    {
        this_uart->linests_handler = handler;

        /* Clear any previously pended interrupts */
        NVIC_ClearPendingIRQ(this_uart->irqn);

        /* Enable receiver line status interrupt. */
        set_bit_reg8(&this_uart->hw_reg->IER,ELSI);

        /* Enable UART instance interrupt in Cortex-M3 NVIC. */
        NVIC_EnableIRQ(this_uart->irqn);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_set_tx_handler
(
    mss_uart_instance_t * this_uart,
    mss_uart_irq_handler_t handler
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(handler != INVALID_IRQ_HANDLER);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
       (handler != INVALID_IRQ_HANDLER))
    {
        this_uart->tx_handler = handler;

        /* Make TX buffer info invalid */
        this_uart->tx_buffer = (const uint8_t *)0;
        this_uart->tx_buff_size = 0u;

        /* Clear any previously pended interrupts */
        NVIC_ClearPendingIRQ(this_uart->irqn);

        /* Enable transmitter holding register Empty interrupt. */
        set_bit_reg8(&this_uart->hw_reg->IER,ETBEI);

        /* Enable UART instance interrupt in Cortex-M3 NVIC. */
        NVIC_EnableIRQ(this_uart->irqn);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_set_modemstatus_handler
(
    mss_uart_instance_t * this_uart,
    mss_uart_irq_handler_t handler
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(handler != INVALID_IRQ_HANDLER);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
       (handler != INVALID_IRQ_HANDLER))
    {
        this_uart->modemsts_handler = handler;

        /* Clear any previously pended interrupts */
        NVIC_ClearPendingIRQ(this_uart->irqn);

        /* Enable modem status interrupt. */
        set_bit_reg8(&this_uart->hw_reg->IER,EDSSI);

        /* Enable UART instance interrupt in Cortex-M3 NVIC. */
        NVIC_EnableIRQ(this_uart->irqn);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
size_t
MSS_UART_fill_tx_fifo
(
    mss_uart_instance_t * this_uart,
    const uint8_t * tx_buffer,
    size_t tx_size
)
{
    uint8_t status = 0u;
    size_t size_sent = 0u;

    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(tx_buffer != ( (uint8_t *)0));
    ASSERT(tx_size > 0);

    /* Fill the UART's Tx FIFO until the FIFO is full or the complete input
     * buffer has been written. */
    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
       (tx_buffer != ((uint8_t *)0))   &&
       (tx_size > 0u))
    {
        status = this_uart->hw_reg->LSR;
        this_uart->status |= status;

        if(status & MSS_UART_THRE)
        {
            uint32_t fill_size = TX_FIFO_SIZE;

            if(tx_size < TX_FIFO_SIZE)
            {
                fill_size = tx_size;
            }
            /* Fill up FIFO */
            for(size_sent = 0u; size_sent < fill_size; ++size_sent)
            {

                /* Send next character in the buffer. */
                this_uart->hw_reg->THR = tx_buffer[size_sent];
            }
        }
    }
    return size_sent;
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
uint8_t
MSS_UART_get_rx_status
(
    mss_uart_instance_t * this_uart
)
{
    uint8_t status = MSS_UART_INVALID_PARAM;

    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /*
         * Extract UART receive error status.
         * Bit 1 - Overflow error status
         * Bit 2 - Parity error status
         * Bit 3 - Frame error status
         * Bit 4 - Break interrupt indicator
         * Bit 7 - FIFO data error status
         */
        this_uart->status |= (this_uart->hw_reg->LSR);
        status = (this_uart->status & STATUS_ERROR_MASK);
        /* Clear the sticky status after reading */
        this_uart->status = 0u;
    }
    return status;
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
uint8_t
MSS_UART_get_modem_status
(
    mss_uart_instance_t * this_uart
)
{
    uint8_t status = MSS_UART_INVALID_PARAM;

    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /*
         * Extract UART modem status and place in lower bits of "status".
         * Bit 0 - Delta Clear to Send Indicator
         * Bit 1 - Delta Clear to Receive Indicator
         * Bit 2 - Trailing edge of Ring Indicator detector
         * Bit 3 - Delta Data Carrier Detect indicator
         * Bit 4 - Clear To Send
         * Bit 5 - Data Set Ready
         * Bit 6 - Ring Indicator
         * Bit 7 - Data Carrier Detect
         */
        status = this_uart->hw_reg->MSR;
    }
    return status;
}

/***************************************************************************//**
 * MSS_UART_get_tx_status.
 * See mss_uart.h for details of how to use this function.
 */
uint8_t
MSS_UART_get_tx_status
(
    mss_uart_instance_t * this_uart
)
{
    uint8_t status = MSS_UART_TX_BUSY;

    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /* Read the Line Status Register and update the sticky record. */
        status = this_uart->hw_reg->LSR;
        this_uart->status |= status;
        /*
         * Extract the transmit status bits from the UART's Line Status Register.
         * Bit 5 - Transmitter Holding Register/FIFO Empty (THRE) status. (If = 1, TX FIFO is empty)
         * Bit 6 - Transmitter Empty (TEMT) status. (If = 1, both TX FIFO and shift register are empty)
         */
        status &= (MSS_UART_THRE | MSS_UART_TEMT);
    }
    return status;
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_set_break
(
    mss_uart_instance_t * this_uart
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /* set break charecter on Tx line */
        set_bit_reg8(&this_uart->hw_reg->LCR,SB);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_clear_break
(
    mss_uart_instance_t * this_uart
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /* remove break charecter from Tx line */
        clear_bit_reg8(&this_uart->hw_reg->LCR,SB);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_set_pidpei_handler
(
    mss_uart_instance_t * this_uart,
    mss_uart_irq_handler_t handler
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(handler != INVALID_IRQ_HANDLER);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
       (handler != INVALID_IRQ_HANDLER))
    {
        this_uart->pid_pei_handler = handler;

        /* Clear any previously pended interrupts */
        NVIC_ClearPendingIRQ( this_uart->irqn );

        /* Enable PID parity error interrupt. */
        set_bit_reg8(&this_uart->hw_reg->IEM,EPID_PEI);

        /* Enable UART instance interrupt in Cortex-M3 NVIC. */
        NVIC_EnableIRQ(this_uart->irqn);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_set_linbreak_handler
(
    mss_uart_instance_t * this_uart,
    mss_uart_irq_handler_t handler
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(handler != INVALID_IRQ_HANDLER);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
       (handler != INVALID_IRQ_HANDLER))
    {
        this_uart->break_handler = handler;

        /* Clear any previously pended interrupts */
        NVIC_ClearPendingIRQ( this_uart->irqn );

        /* Enable LIN break detection interrupt. */
        set_bit_reg8(&this_uart->hw_reg->IEM,ELINBI);

        /* Enable UART instance interrupt in Cortex-M3 NVIC. */
        NVIC_EnableIRQ(this_uart->irqn);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_set_linsync_handler
(
    mss_uart_instance_t * this_uart,
    mss_uart_irq_handler_t handler
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(handler != INVALID_IRQ_HANDLER);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
       (handler != INVALID_IRQ_HANDLER))
    {
        this_uart->sync_handler = handler;

        /* Clear any previously pended interrupts */
        NVIC_ClearPendingIRQ( this_uart->irqn );

        /* Enable LIN sync detection interrupt. */
        set_bit_reg8(&this_uart->hw_reg->IEM,ELINSI);

        /* Enable UART instance interrupt in Cortex-M3 NVIC. */
        NVIC_EnableIRQ(this_uart->irqn);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_set_nack_handler
(
    mss_uart_instance_t * this_uart,
    mss_uart_irq_handler_t handler
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(handler != INVALID_IRQ_HANDLER);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
       (handler != INVALID_IRQ_HANDLER))
    {
        this_uart->nack_handler = handler;

        /* Clear any previously pended interrupts */
        NVIC_ClearPendingIRQ( this_uart->irqn );

        /* Enable LIN sync detection interrupt. */
        set_bit_reg8(&this_uart->hw_reg->IEM,ENACKI);

        /* Enable UART instance interrupt in Cortex-M3 NVIC. */
        NVIC_EnableIRQ(this_uart->irqn);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_set_rx_timeout_handler
(
    mss_uart_instance_t * this_uart,
    mss_uart_irq_handler_t handler
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(handler != INVALID_IRQ_HANDLER);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
       (handler != INVALID_IRQ_HANDLER))
    {
        this_uart->rto_handler = handler;

        /* Clear any previously pended interrupts */
        NVIC_ClearPendingIRQ( this_uart->irqn );

        /* Enable receiver timeout interrupt. */
        set_bit_reg8(&this_uart->hw_reg->IEM,ERTOI);

        /* Enable UART instance interrupt in Cortex-M3 NVIC. */
        NVIC_EnableIRQ(this_uart->irqn);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void 
MSS_UART_enable_half_duplex
(
    mss_uart_instance_t * this_uart
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /* enable single wire half-duplex mode */
        set_bit_reg8(&this_uart->hw_reg->MM2,ESWM);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void 
MSS_UART_disable_half_duplex
(
    mss_uart_instance_t * this_uart
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /* enable single wire half-duplex mode */
        clear_bit_reg8(&this_uart->hw_reg->MM2,ESWM);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_set_rx_endian
(
    mss_uart_instance_t * this_uart,
    mss_uart_endian_t endian    
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(MSS_UART_INVALID_ENDIAN > endian);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) && 
       (MSS_UART_INVALID_ENDIAN > endian))
    {
        /* Configure MSB first / LSB first for receiver */
        ((MSS_UART_LITTLEEND == endian) ? (clear_bit_reg8(&this_uart->hw_reg->MM1,E_MSB_RX)) :
                                          (set_bit_reg8(&this_uart->hw_reg->MM1,E_MSB_RX)));
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_set_tx_endian
(
    mss_uart_instance_t * this_uart,
    mss_uart_endian_t endian    
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(MSS_UART_INVALID_ENDIAN > endian);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) && 
       (MSS_UART_INVALID_ENDIAN > endian))
    {
        /* Configure MSB first / LSB first for transmitter */
        ((MSS_UART_LITTLEEND == endian) ? (clear_bit_reg8(&this_uart->hw_reg->MM1,E_MSB_TX)) :
                                          (set_bit_reg8(&this_uart->hw_reg->MM1,E_MSB_TX)) ) ;
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_set_filter_length
(
    mss_uart_instance_t * this_uart,
    mss_uart_filter_length_t length
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(MSS_UART_INVALID_FILTER_LENGTH > length);
    
    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) && 
       (MSS_UART_INVALID_FILTER_LENGTH > length))
    {
        /* Configure glitch filter length */
        this_uart->hw_reg->GFR = (uint8_t)length;
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_enable_afm
(
     mss_uart_instance_t * this_uart
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /* Disable RX FIFO till address flag with correct address is received */
        set_bit_reg8(&this_uart->hw_reg->MM2,EAFM);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_disable_afm
(
     mss_uart_instance_t * this_uart
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /* Enable RX FIFO irrespective of address flag and
           correct address is received */
        clear_bit_reg8(&this_uart->hw_reg->MM2,EAFM);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_enable_afclear
(
     mss_uart_instance_t * this_uart
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /* Enable address flag clearing */
        /* Disable RX FIFO till another address flag with 
           correct address is received */
        set_bit_reg8(&this_uart->hw_reg->MM2,EAFC);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_disable_afclear
(
     mss_uart_instance_t * this_uart
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /* Disable address flag clearing */
        clear_bit_reg8(&this_uart->hw_reg->MM2,EAFC);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void 
MSS_UART_enable_rx_timeout
(
    mss_uart_instance_t * this_uart,
    uint8_t timeout
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /* Load the receive timeout value */
        this_uart->hw_reg->RTO = timeout;
        /*Enable receiver time-out */
        set_bit_reg8(&this_uart->hw_reg->MM0,ERTO);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void 
MSS_UART_disable_rx_timeout
(
    mss_uart_instance_t * this_uart
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /*Disable receiver time-out */
        clear_bit_reg8(&this_uart->hw_reg->MM0,ERTO);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void 
MSS_UART_enable_tx_time_guard
(
    mss_uart_instance_t * this_uart,
    uint8_t timeguard
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /* Load the transmitter time guard value */
        this_uart->hw_reg->TTG = timeguard;
        /*Enable transmitter time guard */
        set_bit_reg8(&this_uart->hw_reg->MM0,ETTG);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void 
MSS_UART_disable_tx_time_guard
(
    mss_uart_instance_t * this_uart
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        /*Disable transmitter time guard */
        clear_bit_reg8(&this_uart->hw_reg->MM0,ETTG);
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void
MSS_UART_set_address
(
    mss_uart_instance_t * this_uart,
    uint8_t address
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        this_uart->hw_reg->ADR = address;
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void 
MSS_UART_set_ready_mode
(
    mss_uart_instance_t * this_uart,
    mss_uart_ready_mode_t mode    
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(MSS_UART_INVALID_READY_MODE > mode);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
       (MSS_UART_INVALID_READY_MODE > mode ) )
    {
        /* Configure mode 0 or mode 1 for TXRDY and RXRDY */
        ((MSS_UART_READY_MODE0 == mode) ? clear_bit_reg8(&this_uart->hw_reg->FCR,RDYMODE) :
                                 set_bit_reg8(&this_uart->hw_reg->FCR,RDYMODE) );    
    }
}

/***************************************************************************//**
 * Configure baud divisors using fractional baud rate if possible.
 */
static void
config_baud_divisors
(
    mss_uart_instance_t * this_uart,
    uint32_t baudrate    
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    
    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        uint32_t baud_value;
        uint32_t baud_value_by_64;
        uint32_t baud_value_by_128;
        uint32_t fractional_baud_value;
        uint32_t pclk_freq;

        this_uart->baudrate = baudrate;

        /* Force the value of the CMSIS global variables holding the various system
          * clock frequencies to be updated. */
        SystemCoreClockUpdate();
        if(this_uart == &g_mss_uart0)
        {
            pclk_freq = g_FrequencyPCLK0;
        }
        else
        {
            pclk_freq = g_FrequencyPCLK1;
        }

        /*
         * Compute baud value based on requested baud rate and PCLK frequency.
         * The baud value is computed using the following equation:
         *      baud_value = PCLK_Frequency / (baud_rate * 16)
         */
        baud_value_by_128 = (8u * pclk_freq) / baudrate;
        baud_value_by_64 = baud_value_by_128 / 2u;
        baud_value = baud_value_by_64 / 64u;
        fractional_baud_value = baud_value_by_64 - (baud_value * 64u);
        fractional_baud_value += (baud_value_by_128 - (baud_value * 128u)) - (fractional_baud_value * 2u);
        
        /* Assert if integer baud value fits in 16-bit. */
        ASSERT(baud_value <= UINT16_MAX);
    
        if(baud_value <= (uint32_t)UINT16_MAX)
        {
            if(baud_value > 1u)
            {
                /* 
                 * Use Frational baud rate divisors
                 */
                /* set divisor latch */
                set_bit_reg8(&this_uart->hw_reg->LCR,DLAB);
            
                /* msb of baud value */
                this_uart->hw_reg->DMR = (uint8_t)(baud_value >> 8);
                /* lsb of baud value */
                this_uart->hw_reg->DLR = (uint8_t)baud_value;
            
                /* reset divisor latch */
                clear_bit_reg8(&this_uart->hw_reg->LCR,DLAB);
        
                /* Enable Fractional baud rate */
                set_bit_reg8(&this_uart->hw_reg->MM0,EFBR);
        
                /* Load the fractional baud rate register */
                ASSERT(fractional_baud_value <= (uint32_t)UINT8_MAX);
                this_uart->hw_reg->DFR = (uint8_t)fractional_baud_value;
            }
            else
            {
                /*
                 * Do NOT use Frational baud rate divisors.
                 */
                /* set divisor latch */
                set_bit_reg8(&this_uart->hw_reg->LCR,DLAB);
            
                /* msb of baud value */
                this_uart->hw_reg->DMR = (uint8_t)(baud_value >> 8u);
                /* lsb of baud value */
                this_uart->hw_reg->DLR = (uint8_t)baud_value;
            
                /* reset divisor latch */
                clear_bit_reg8(&this_uart->hw_reg->LCR,DLAB);
                
                /* Disable Fractional baud rate */
                clear_bit_reg8(&this_uart->hw_reg->MM0,EFBR);
            }
        }
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
void 
MSS_UART_set_usart_mode
(
    mss_uart_instance_t * this_uart,
    mss_uart_usart_mode_t mode
)
{
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(MSS_UART_INVALID_SYNC_MODE > mode);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
       (MSS_UART_INVALID_SYNC_MODE > mode))
    {
        /* Nothing to do for the baudrate: operates at PCLK / 2 + glitch filter length */
        /* Clear the ESYN bits 2:0 */
        this_uart->hw_reg->MM0 &= ~SYNC_ASYNC_MODE_MASK;
        this_uart->hw_reg->MM0 |= (uint8_t)mode;
    }
}

/*******************************************************************************
 * Local Functions
 *******************************************************************************/
/*******************************************************************************
 * Global initialization for all modes
 */
static void global_init
(
    mss_uart_instance_t * this_uart,
    uint32_t baud_rate,
    uint8_t line_config
)
{
    /* The driver expects g_mss_uart0 and g_mss_uart1 to be the only
     * mss_uart_instance_t instances used to identify UART0 and UART1. */
    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if(this_uart == &g_mss_uart0)
    {
        this_uart->hw_reg = UART0;
        this_uart->irqn = UART0_IRQn;
        /* reset UART0 */
        SYSREG->SOFT_RST_CR |= SYSREG_MMUART0_SOFTRESET_MASK;
        /* Clear any previously pended UART0 interrupt */
        NVIC_ClearPendingIRQ(UART0_IRQn);
        /* Take UART0 out of reset. */
        SYSREG->SOFT_RST_CR &= ~SYSREG_MMUART0_SOFTRESET_MASK;
    }
    else
    {
        this_uart->hw_reg = UART1;
        this_uart->irqn = UART1_IRQn;
        /* Reset UART1 */
        SYSREG->SOFT_RST_CR |= SYSREG_MMUART1_SOFTRESET_MASK;
        /* Clear any previously pended UART1 interrupt */
        NVIC_ClearPendingIRQ(UART1_IRQn);
        /* Take UART1 out of reset. */
        SYSREG->SOFT_RST_CR &= ~SYSREG_MMUART1_SOFTRESET_MASK;
    }

    /* disable interrupts */
    this_uart->hw_reg->IER = 0u;

    /* FIFO configuration */
    this_uart->hw_reg->FCR = (uint8_t)MSS_UART_FIFO_SINGLE_BYTE;
    /* clear receiver FIFO */
    set_bit_reg8(&this_uart->hw_reg->FCR,CLEAR_RX_FIFO);
    /* clear transmitter FIFO */
    set_bit_reg8(&this_uart->hw_reg->FCR,CLEAR_TX_FIFO);

    /* set default READY mode : Mode 0*/
    /* enable RXRDYN and TXRDYN pins. The earlier FCR write to set the TX FIFO
     * trigger level inadvertently disabled the FCR_RXRDY_TXRDYN_EN bit. */
    set_bit_reg8(&this_uart->hw_reg->FCR,RXRDY_TXRDYN_EN);

    /* disable loopback : local * remote */
    clear_bit_reg8(&this_uart->hw_reg->MCR,LOOP);
    clear_bit_reg8(&this_uart->hw_reg->MCR,RLOOP);

    /* set default TX endian */
    clear_bit_reg8(&this_uart->hw_reg->MM1,E_MSB_TX);
    /* set default RX endian */
    clear_bit_reg8(&this_uart->hw_reg->MM1,E_MSB_RX);

    /* default AFM : disabled */
    clear_bit_reg8(&this_uart->hw_reg->MM2,EAFM);

    /* disable TX time gaurd */
    clear_bit_reg8(&this_uart->hw_reg->MM0,ETTG); 

    /* set default RX timeout */
    clear_bit_reg8(&this_uart->hw_reg->MM0,ERTO); 

    /* disable fractional baud-rate */
    clear_bit_reg8(&this_uart->hw_reg->MM0,EFBR); 

    /* disable single wire mode */
    clear_bit_reg8(&this_uart->hw_reg->MM2,ESWM);

    /* set filter to minimum value */
    this_uart->hw_reg->GFR = 0u;
    /* set default TX time gaurd */
    this_uart->hw_reg->TTG = 0u;
    /* set default RX timeout */
    this_uart->hw_reg->RTO = 0u;
    
    /* 
     * Configure baud rate divisors. This uses the frational baud rate divisor
     * where possible to provide the most accurate baud rat possible.
     */
    config_baud_divisors(this_uart, baud_rate);

    /* set the line control register (bit length, stop bits, parity) */
    this_uart->hw_reg->LCR = line_config;

    /* Instance setup */
    this_uart->baudrate = baud_rate;
    this_uart->lineconfig = line_config;
    this_uart->tx_buff_size = TX_COMPLETE;
    this_uart->tx_buffer = (const uint8_t *)0;
    this_uart->tx_idx = 0u;

    /* Default handlers for MSS UART interrupts */
    this_uart->rx_handler       = NULL_HANDLER;
    this_uart->tx_handler       = NULL_HANDLER;
    this_uart->linests_handler  = NULL_HANDLER;
    this_uart->modemsts_handler = NULL_HANDLER;
    this_uart->rto_handler      = NULL_HANDLER;    
    this_uart->nack_handler     = NULL_HANDLER;   
    this_uart->pid_pei_handler  = NULL_HANDLER;
    this_uart->break_handler    = NULL_HANDLER;    
    this_uart->sync_handler     = NULL_HANDLER;   

    /* Initialize the sticky status */
    this_uart->status = 0u;
}

/***************************************************************************//**
 * Interrupt service routine triggered by any MSS UART interrupt. This routine
 * will call the handler function appropriate to the interrupt from the
 * handlers previously registered with the driver through calls to the
 * MSS_UART_set_*_handler() functions, or it will call the default_tx_handler()
 * function in response to transmit interrupts if MSS_UART_irq_tx() is used to
 * transmit data.
 */
static void
MSS_UART_isr
(
    mss_uart_instance_t * this_uart
)
{
    uint8_t iirf;

    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));

    if((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1))
    {
        iirf = this_uart->hw_reg->IIR & IIRF_MASK;

        switch (iirf)
        {
            case IIRF_MODEM_STATUS:  /* Modem status interrupt */
            {
                ASSERT(NULL_HANDLER != this_uart->modemsts_handler);
                if(NULL_HANDLER != this_uart->modemsts_handler)
                {
                   (*(this_uart->modemsts_handler))(this_uart);
                }
            }
            break;

            case IIRF_THRE: /* Transmitter Holding Register Empty */
            {
                ASSERT(NULL_HANDLER != this_uart->tx_handler);
                if(NULL_HANDLER != this_uart->tx_handler)
                {
                    (*(this_uart->tx_handler))(this_uart);
                }
            }
            break;

            case IIRF_RX_DATA:      /* Received Data Available */
            case IIRF_DATA_TIMEOUT: /* Received Data Timed-out */
            {
                ASSERT(NULL_HANDLER != this_uart->rx_handler);
                if(NULL_HANDLER != this_uart->rx_handler)
                {
                    (*(this_uart->rx_handler))(this_uart);
                }
            }
            break;

            case IIRF_RX_LINE_STATUS:  /* Line Status Interrupt */
            {
                ASSERT(NULL_HANDLER != this_uart->linests_handler);
                if(NULL_HANDLER != this_uart->linests_handler)
                {
                   (*(this_uart->linests_handler))(this_uart);
                }
            }
            break;

            case IIRF_MMI:
            {
                /* Identify multimode interrupts and handle */

                /* Receiver time-out interrupt */
                if(read_bit_reg8(&this_uart->hw_reg->IIM,ERTOI))
                {
                    ASSERT(NULL_HANDLER != this_uart->rto_handler);
                    if(NULL_HANDLER != this_uart->rto_handler)
                    {
                        (*(this_uart->rto_handler))(this_uart);
                    }
                }
                /* NACK interrupt */
                if(read_bit_reg8(&this_uart->hw_reg->IIM,ENACKI))
                {
                    ASSERT(NULL_HANDLER != this_uart->nack_handler);
                    if(NULL_HANDLER != this_uart->nack_handler)
                    {
                        (*(this_uart->nack_handler))(this_uart);
                    }
                }

                /* PID parity error interrupt */
                if(read_bit_reg8(&this_uart->hw_reg->IIM,EPID_PEI))
                {
                    ASSERT(NULL_HANDLER != this_uart->pid_pei_handler);
                    if(NULL_HANDLER != this_uart->pid_pei_handler)
                    {
                        (*(this_uart->pid_pei_handler))(this_uart);
                    }
                }

                /* LIN break detection interrupt */
                if(read_bit_reg8(&this_uart->hw_reg->IIM,ELINBI))
                {
                    ASSERT(NULL_HANDLER != this_uart->break_handler);
                    if(NULL_HANDLER != this_uart->break_handler)
                    {
                        (*(this_uart->break_handler))(this_uart);
                    }
                }

                /* LIN Sync detection interrupt */
                if(read_bit_reg8(&this_uart->hw_reg->IIM,ELINSI))
                {
                    ASSERT(NULL_HANDLER != this_uart->sync_handler);
                    if(NULL_HANDLER != this_uart->sync_handler)
                    {
                        (*(this_uart->sync_handler))(this_uart);
                    }
                }
                break;
            }

            default:
            {
                ASSERT(INVALID_INTERRUPT);
            }
            break;
        }
    }
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
static void
default_tx_handler
(
    mss_uart_instance_t * this_uart
)
{
    uint8_t status;

    ASSERT((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1));
    ASSERT(( (uint8_t *)0 ) != this_uart->tx_buffer);
    ASSERT(0u < this_uart->tx_buff_size);

    if(((this_uart == &g_mss_uart0) || (this_uart == &g_mss_uart1)) &&
       (((uint8_t *)0 ) != this_uart->tx_buffer) &&
       (0u < this_uart->tx_buff_size))
    {
        /* Read the Line Status Register and update the sticky record. */
        status = this_uart->hw_reg->LSR;
        this_uart->status |= status;

        /*
         * This function should only be called as a result of a THRE interrupt.
         * Verify that this is true before proceeding to transmit data.
         */
        if(status & MSS_UART_THRE)
        {
            uint32_t i;
            uint32_t fill_size = TX_FIFO_SIZE;
            uint32_t tx_remain = this_uart->tx_buff_size - this_uart->tx_idx;

            /* Calculate the number of bytes to transmit. */
            if(tx_remain < TX_FIFO_SIZE)
            {
                fill_size = tx_remain;
            }

            /* Fill the TX FIFO with the calculated the number of bytes. */
            for(i = 0u; i < fill_size; ++i)
            {
                /* Send next character in the buffer. */
                this_uart->hw_reg->THR = this_uart->tx_buffer[this_uart->tx_idx];
                ++this_uart->tx_idx;
            }
        }

        /* Flag Tx as complete if all data has been pushed into the Tx FIFO. */
        if(this_uart->tx_idx == this_uart->tx_buff_size)
        {
            this_uart->tx_buff_size = TX_COMPLETE;
            /* disables TX interrupt */
            clear_bit_reg8(&this_uart->hw_reg->IER,ETBEI);
        }
    }
}

#ifdef __cplusplus
}
#endif
