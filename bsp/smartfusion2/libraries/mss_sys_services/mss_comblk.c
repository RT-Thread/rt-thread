/*******************************************************************************
 * (c) Copyright 2012-2016 Microsemi SoC Products Group.  All rights reserved.
 *
 * SmartFusion2 COMBLK access functions.
 *
 * SVN $Revision: 8345 $
 * SVN $Date: 2016-03-23 11:53:04 +0530 (Wed, 23 Mar 2016) $
 */

#include "mss_comblk.h"
#include "../../CMSIS/mss_assert.h"

/*==============================================================================
 *
 */
/*------------------------------------------------------------------------------
 * Control register bit masks.
 */
#define CR_FLUSHOUT_MASK    0x01u
#define CR_FLUSHIN_MASK     0x02u
#define CR_SIZETX_MASK      0x04u
#define CR_ENABLE_MASK      0x10u
#define CR_LOOPBACK_MASK    0x20u

/*------------------------------------------------------------------------------
 * Status and interrupt enable registers bit masks.
 */
#define TXTOKAY_MASK        0x01u
#define RCVOKAY_MASK        0x02u
#define TXOVERFLOW_MASK     0x04u
#define RXUNDERFLOW_MASK    0x08u
/*------------------------------------------------------------------------------
 * DATA8 register bit masks.
 */
#define DATA8_COMMAND_MASK  0x8000u

/*------------------------------------------------------------------------------
 * COMBLK driver states.
 */
#define COMBLK_IDLE             0u
#define COMBLK_TX_CMD           1u
#define COMBLK_TX_DATA          2u
#define COMBLK_WAIT_RESPONSE    3u
#define COMBLK_RX_RESPONSE      4u
#define COMBLK_TX_PAGED_DATA    5u

#define POR_DIGEST_ERROR_OPCODE         0xF1u

/*==============================================================================
 * COMBLK interrupt service routine.
 */
void ComBlk_IRQHandler(void);

/*==============================================================================
 * Local functions.
 */
static void abort_current_cmd(void);
static void send_cmd_opcode(uint8_t opcode);
static uint32_t fill_tx_fifo(const uint8_t * p_cmd, uint32_t cmd_size);
static void handle_tx_okay_irq(void);
static void handle_rx_okay_irq(void);
static void complete_request(uint16_t response_length);
static void process_sys_ctrl_command(uint8_t cmd_opcode);

/*==============================================================================
 * Global variables:
 */
static volatile uint8_t g_comblk_cmd_opcode = 0u;
static const uint8_t * g_comblk_p_cmd = 0u;
static volatile uint16_t g_comblk_cmd_size = 0u;
static const uint8_t * g_comblk_p_data = 0u;
static volatile uint32_t g_comblk_data_size = 0u;
static uint8_t * g_comblk_p_response = 0u;
static uint16_t g_comblk_response_size = 0u;
static volatile uint16_t g_comblk_response_idx = 0u;
static comblk_completion_handler_t g_comblk_completion_handler = 0;
static uint32_t (*g_comblk_page_handler)(uint8_t const ** pp_next_page) = 0;
static volatile uint8_t g_request_in_progress = 0u;
static uint8_t g_comblk_state = COMBLK_IDLE;
static volatile comblk_async_event_handler_t g_async_event_handler = 0;

/*==============================================================================
 *
 */
void MSS_COMBLK_init
(
    comblk_async_event_handler_t async_event_handler,
    uint8_t* p_response
)
{
    /*
     * Disable and clear previous interrupts.
     */
    NVIC_DisableIRQ(ComBlk_IRQn);
    COMBLK->INT_ENABLE = 0u;
    NVIC_ClearPendingIRQ(ComBlk_IRQn);
    
    g_async_event_handler = async_event_handler;
    
    /*
     * Initialize COMBLK driver state variables:
     */
    g_request_in_progress = 0u;
    g_comblk_cmd_opcode = 0u;
    g_comblk_p_cmd = 0u;
    g_comblk_cmd_size = 0u;
    g_comblk_p_data = 0u;
    g_comblk_data_size = 0u;
    g_comblk_p_response = p_response;
    g_comblk_response_size = 0u;
    g_comblk_response_idx = 0u;
    g_comblk_completion_handler = 0;
    
    g_comblk_state = COMBLK_IDLE;
    
    /*
     * Disable loopback before enabling the MSS COMM_BLK to ensure that any
     * codes waiting in the TX FIFO of the System Controller’s COMM_BLK are
     * not lost.
     */
    COMBLK->CONTROL &= ~CR_LOOPBACK_MASK;
    COMBLK->CONTROL |= CR_ENABLE_MASK;
    
    /*--------------------------------------------------------------------------
     * Enable receive interrupt to receive asynchronous events from the system
     * controller.
     */
    COMBLK->INT_ENABLE &= ~TXTOKAY_MASK;
    COMBLK->INT_ENABLE |= RCVOKAY_MASK;
    NVIC_EnableIRQ(ComBlk_IRQn);
}

/*==============================================================================
 *
 */
void MSS_COMBLK_send_cmd_with_ptr
(
    uint8_t cmd_opcode,
    uint32_t cmd_params_ptr,
    uint8_t * p_response,
    uint16_t response_size,
    comblk_completion_handler_t completion_handler
)
{
    uint32_t tx_okay;
    
    /*--------------------------------------------------------------------------
     * Disable and clear previous interrupts.
     */
    NVIC_DisableIRQ(ComBlk_IRQn);
    COMBLK->INT_ENABLE = 0u;
    NVIC_ClearPendingIRQ(ComBlk_IRQn);
    
    /*--------------------------------------------------------------------------
     * Abort current command if any.
     */
    abort_current_cmd();
    
    /*--------------------------------------------------------------------------
     * Initialize COMBLK driver state variables.
     */
    g_request_in_progress = 1u;
    g_comblk_cmd_opcode = cmd_opcode;
    g_comblk_p_cmd = 0u;
    g_comblk_cmd_size = 0u;
    g_comblk_p_data = 0u;
    g_comblk_data_size = 0u;
    g_comblk_p_response = p_response;
    g_comblk_response_size = response_size;
    g_comblk_response_idx = 0u;
    g_comblk_page_handler = 0u;
    g_comblk_completion_handler = completion_handler;
    
    /*--------------------------------------------------------------------------
     * Send command opcode as a single byte write to the Tx FIFO.
     */
    send_cmd_opcode(g_comblk_cmd_opcode);
    
    /*--------------------------------------------------------------------------
     * Send the command parameters pointer to the Tx FIFO as a single 4 bytes
     * write to the Tx FIFO.
     */
    COMBLK->CONTROL |= CR_SIZETX_MASK;
    
    /* Wait for space to become available in Tx FIFO. */
    do {
        tx_okay = COMBLK->STATUS & TXTOKAY_MASK;
    } while(0u == tx_okay);
    
    /* Send command opcode. */
    COMBLK->DATA32 = cmd_params_ptr;
    
    COMBLK->CONTROL &= ~CR_SIZETX_MASK;
    
    g_comblk_state = COMBLK_WAIT_RESPONSE;
    
    /*--------------------------------------------------------------------------
     * Enable interrupt.
     */
    COMBLK->INT_ENABLE |= RCVOKAY_MASK;
    NVIC_EnableIRQ(ComBlk_IRQn);
}

/*==============================================================================
 *
 */
void MSS_COMBLK_send_cmd
(
    const uint8_t * p_cmd,
    uint16_t cmd_size,
    const uint8_t * p_data,
    uint32_t data_size,
    uint8_t * p_response,
    uint16_t response_size,
    comblk_completion_handler_t completion_handler
)
{
    uint32_t size_sent;
    
    ASSERT(cmd_size > 0);
    
    /*
     * Disable and clear previous interrupts.
     */
    NVIC_DisableIRQ(ComBlk_IRQn);
    COMBLK->INT_ENABLE = 0u;
    NVIC_ClearPendingIRQ(ComBlk_IRQn);
    
    /*
     * Abort current command if any.
     */
    abort_current_cmd();
    
    /*
     * Initialize COMBLK driver state variables:
     */
    g_request_in_progress = 1u;
    g_comblk_cmd_opcode = p_cmd[0];
    g_comblk_p_cmd = p_cmd;
    g_comblk_cmd_size = cmd_size;
    g_comblk_p_data = p_data;
    g_comblk_data_size = data_size;
    g_comblk_p_response = p_response;
    g_comblk_response_size = response_size;
    g_comblk_response_idx = 0u;
    g_comblk_page_handler = 0u;
    g_comblk_completion_handler = completion_handler;
    
    COMBLK->INT_ENABLE |= RCVOKAY_MASK;

    /*
     * Fill FIFO with command.
     */
    send_cmd_opcode(g_comblk_cmd_opcode);
    size_sent = fill_tx_fifo(&p_cmd[1], cmd_size - 1u);
    ++size_sent;    /* Adjust for opcode byte sent. */
    if(size_sent < cmd_size)
    {
        g_comblk_cmd_size = g_comblk_cmd_size - (uint16_t)size_sent;
        g_comblk_p_cmd = &g_comblk_p_cmd[size_sent];
        
        g_comblk_state = COMBLK_TX_CMD;
    }
    else
    {
        g_comblk_cmd_size = 0u;
        if(g_comblk_data_size > 0u)
        {
            g_comblk_state = COMBLK_TX_DATA;
        }
        else
        {
            g_comblk_state = COMBLK_WAIT_RESPONSE;
        }
    }

    /*
     * Enable interrupt.
     */
    NVIC_EnableIRQ(ComBlk_IRQn);
}

/*==============================================================================
 *
 */
void MSS_COMBLK_send_paged_cmd
(
    const uint8_t * p_cmd,
    uint16_t cmd_size,
    uint8_t * p_response,
    uint16_t response_size,
    comblk_page_handler_t page_read_handler,
    comblk_completion_handler_t completion_handler
)
{
    uint32_t size_sent;
    uint8_t irq_enable = 0u;
    
    ASSERT(cmd_size > 0u);
    
    /*
     * Disable and clear previous interrupts.
     */
    NVIC_DisableIRQ(ComBlk_IRQn);
    COMBLK->INT_ENABLE = 0u;
    NVIC_ClearPendingIRQ(ComBlk_IRQn);
    
    /*
     * Abort current command if any.
     */
    abort_current_cmd();
    
    /*
     * Initialize COMBLK driver state variables:
     */
    g_request_in_progress = 1u;
    g_comblk_cmd_opcode = p_cmd[0];
    g_comblk_p_cmd = p_cmd;
    g_comblk_cmd_size = cmd_size;
    g_comblk_p_data = 0;
    g_comblk_data_size = 0u;
    g_comblk_p_response = p_response;
    g_comblk_response_size = response_size;
    g_comblk_response_idx = 0u;
    g_comblk_page_handler = page_read_handler;
    g_comblk_completion_handler = completion_handler;
    
    /*
     * Fill FIFO with command.
     */
    send_cmd_opcode(g_comblk_cmd_opcode);
    size_sent = fill_tx_fifo(&p_cmd[1], cmd_size - 1u);
    ++size_sent;    /* Adjust for opcode byte sent. */
    if(size_sent < cmd_size)
    {
        g_comblk_cmd_size = g_comblk_cmd_size - (uint16_t)size_sent;
        g_comblk_p_cmd = &g_comblk_p_cmd[size_sent];
        
        g_comblk_state = COMBLK_TX_CMD;
        irq_enable = TXTOKAY_MASK | RCVOKAY_MASK;
    }
    else
    {
        g_comblk_cmd_size = 0u;
        g_comblk_state = COMBLK_TX_PAGED_DATA;
        irq_enable = TXTOKAY_MASK | RCVOKAY_MASK;
    }

    /*
     * Enable interrupt.
     */
    COMBLK->INT_ENABLE |= irq_enable;
    NVIC_EnableIRQ(ComBlk_IRQn);
}

/*==============================================================================
 * COMBLK interrupt handler.
 */
void ComBlk_IRQHandler(void)
{
    uint8_t status;
    uint8_t tx_okay;
    uint8_t rcv_okay;
    
    status = (uint8_t)COMBLK->STATUS;
    
    /* Mask off interrupt that are not enabled.*/
    status &= COMBLK->INT_ENABLE;
    
    rcv_okay = status & RCVOKAY_MASK;
    
    if(rcv_okay)
    {
        handle_rx_okay_irq();
    }
        
    tx_okay = status & TXTOKAY_MASK;
    if(tx_okay)
    {
        handle_tx_okay_irq();
    }
}

/*==============================================================================
 *
 */
static void handle_tx_okay_irq(void)
{
    switch(g_comblk_state)
    {
        /*----------------------------------------------------------------------
         * The TX_OKAY interrupt should only be enabled for states COMBLK_TX_CMD
         * and COMBLK_TX_DATA.
         */
        case COMBLK_TX_CMD:
            if(g_comblk_cmd_size > 0u)
            {
                uint32_t size_sent;
                size_sent = fill_tx_fifo(g_comblk_p_cmd, g_comblk_cmd_size);
                if(size_sent < g_comblk_cmd_size)
                {
                    g_comblk_cmd_size = g_comblk_cmd_size - (uint16_t)size_sent;
                    g_comblk_p_cmd = &g_comblk_p_cmd[size_sent];
                }
                else
                {
                    g_comblk_cmd_size = 0u;
                    if(g_comblk_data_size > 0u)
                    {
                        g_comblk_state = COMBLK_TX_DATA;
                    }
                    else
                    {
                        g_comblk_state = COMBLK_WAIT_RESPONSE;
                    }
                }
            }
            else
            {
                /*
                 * This is an invalid situation indicating a bug in the driver
                 * or corrupted memory.
                 */
                ASSERT(0);
                abort_current_cmd();
            }
        break;
            
        case COMBLK_TX_DATA:
            if(g_comblk_data_size > 0u)
            {
                uint32_t size_sent;
                size_sent = fill_tx_fifo(g_comblk_p_data, g_comblk_data_size);
                if(size_sent < g_comblk_data_size)
                {
                    g_comblk_data_size = g_comblk_data_size - size_sent;
                    g_comblk_p_data = &g_comblk_p_data[size_sent];
                }
                else
                {
                    COMBLK->INT_ENABLE &= ~TXTOKAY_MASK;
                    g_comblk_state = COMBLK_WAIT_RESPONSE;
                }
            }
            else
            {
                /*
                 * This is an invalid situation indicating a bug in the driver
                 * or corrupted memory.
                 */
                ASSERT(0);
                abort_current_cmd();
            }
        break;
           
        case COMBLK_TX_PAGED_DATA:
            /*
             * Read a page of data if required.
             */
            if(0u == g_comblk_data_size)
            {
                if(g_comblk_page_handler != 0)
                {
                    g_comblk_data_size = g_comblk_page_handler(&g_comblk_p_data);
                    if(0u == g_comblk_data_size)
                    {
                        COMBLK->INT_ENABLE &= ~TXTOKAY_MASK;
                        g_comblk_state = COMBLK_WAIT_RESPONSE;
                    }
                }
                else
                {
                    ASSERT(0);
                    abort_current_cmd();
                }
            }
            
            /*
             * Transmit the page data or move to COMBLK_WAIT_RESPONSE state if
             * no further page data could be obtained by the call to the page
             * handler above.
             */
            if(0u == g_comblk_data_size)
            {
                COMBLK->INT_ENABLE &= ~TXTOKAY_MASK;
                g_comblk_state = COMBLK_WAIT_RESPONSE;
            }
            else
            {
                uint32_t size_sent;
                size_sent = fill_tx_fifo(g_comblk_p_data, g_comblk_data_size);
                g_comblk_data_size = g_comblk_data_size - size_sent;
                g_comblk_p_data = &g_comblk_p_data[size_sent];
            }
        break;
            
        /*----------------------------------------------------------------------
         * The TX_OKAY interrupt should NOT be enabled for states COMBLK_IDLE,
         * COMBLK_WAIT_RESPONSE and COMBLK_RX_RESPONSE.
         */
        case COMBLK_IDLE:
            /* Fall through */
        case COMBLK_WAIT_RESPONSE:
            /* Fall through */
        case COMBLK_RX_RESPONSE:
            /* Fall through */
        default:
            COMBLK->INT_ENABLE &= ~TXTOKAY_MASK;
            complete_request(0u);
            g_comblk_state = COMBLK_IDLE;
        break;
    }
}

/*==============================================================================
 *
 */
static void handle_rx_okay_irq(void)
{
    uint16_t data16;
    uint16_t is_command;
    uint8_t data8;
    
    data16 = (uint16_t)COMBLK->DATA8;
    is_command = data16 & DATA8_COMMAND_MASK;
    data8 = (uint8_t)data16;
            
    switch(g_comblk_state)
    {
        /*----------------------------------------------------------------------
        * MSS_COMBLK_init() enables the RCV_OKAY interrupt for the COMBLK_IDLE
        * state to receive the asynchronous power-on-reset from the system
        * controller.
        */
        case COMBLK_IDLE:
            if(is_command)
            {
                if(data8 != POR_DIGEST_ERROR_OPCODE)
                {
                    uint8_t rxed_opcode;
                    rxed_opcode = data8;
                    process_sys_ctrl_command(rxed_opcode);
                }
                else
                {  
                    g_comblk_response_idx = 0;
                    g_comblk_p_response[g_comblk_response_idx] = data8;
                    g_comblk_response_idx++;
                    g_comblk_p_response[g_comblk_response_idx] = 0x00u;                
                    g_comblk_state = COMBLK_RX_RESPONSE;
                }
            }
        break;
       
        /*----------------------------------------------------------------------
         * The RCV_OKAY interrupt should only be enabled for states
         * COMBLK_WAIT_RESPONSE and COMBLK_RX_RESPONSE. 
         */
        case COMBLK_WAIT_RESPONSE:
            if(is_command)
            {
                uint8_t rxed_opcode;
                rxed_opcode = data8;
                if(rxed_opcode == g_comblk_cmd_opcode)
                {
                    g_comblk_response_idx = 0u;
                    g_comblk_p_response[g_comblk_response_idx] = rxed_opcode;
                    ++g_comblk_response_idx;
                    g_comblk_state = COMBLK_RX_RESPONSE;
                }
                else
                {
                    process_sys_ctrl_command(rxed_opcode);
                }
            }
        break;
            
        case COMBLK_RX_RESPONSE:
            if(is_command)
            {
                uint8_t rxed_opcode;
                rxed_opcode = data8;
                process_sys_ctrl_command(rxed_opcode);
            }
            else
            {
                if( g_comblk_p_response[g_comblk_response_idx-1] == POR_DIGEST_ERROR_OPCODE)
                {
                    g_comblk_p_response[g_comblk_response_idx] = data8;
                    process_sys_ctrl_command(g_comblk_p_response[g_comblk_response_idx-1]);
                    g_comblk_state = COMBLK_IDLE;
                }
                else
                {
                    if(g_comblk_response_idx < g_comblk_response_size)
                    {
                        uint8_t rxed_data;
                        
                        rxed_data = data8;
                        g_comblk_p_response[g_comblk_response_idx] = rxed_data;
                        ++g_comblk_response_idx;
                    }
                    
                    if(g_comblk_response_idx == g_comblk_response_size)
                    {
                        complete_request(g_comblk_response_idx);
                        g_comblk_state = COMBLK_IDLE;
                    }
                }
            }
        break;
            
        /*----------------------------------------------------------------------
         * The RCV_OKAY interrupt should NOT be enabled for states
         * COMBLK_IDLE, COMBLK_TX_CMD and COMBLK_TX_DATA.
         */
        case COMBLK_TX_PAGED_DATA:
            /* This is needed because when there is an error, we need to terminate loading the data */
            if(!is_command)
            {
                g_comblk_p_response[1] = data8;
                complete_request(2u);
                g_comblk_state = COMBLK_IDLE;
            }
            else
            {
                uint8_t rxed_opcode;
                rxed_opcode = data8;
                process_sys_ctrl_command(rxed_opcode);
            }
        break;
        
        case COMBLK_TX_CMD:
            /* Fall through */
        case COMBLK_TX_DATA:
            /* Fall through */
            if(is_command)
            {
                uint8_t rxed_opcode;
                rxed_opcode = data8;
                process_sys_ctrl_command(rxed_opcode);
            }
        break;
        
        default:
            complete_request(0u);
            g_comblk_state = COMBLK_IDLE;
        break;
    }
}

/*==============================================================================
 *
 */
static void complete_request
(
    uint16_t response_length
)
{
    if(g_comblk_completion_handler != 0)
    {
        g_comblk_completion_handler(g_comblk_p_response, response_length);
        g_comblk_completion_handler = 0;
        g_request_in_progress = 0u;
    }
}

/*==============================================================================
 *
 */
static void abort_current_cmd(void)
{
    if(g_request_in_progress)
    {
        uint32_t flush_in_progress;
        
        /*
         * Call completion handler just in case we are in a multi threaded system
         * to avoid a task lockup.
         */
        complete_request(g_comblk_response_idx);
        
        /*
         * Flush the FIFOs
         */
        COMBLK->CONTROL |= CR_FLUSHOUT_MASK;
        do {
            flush_in_progress = COMBLK->CONTROL & CR_FLUSHOUT_MASK;
        } while(flush_in_progress);
    }
}

/*==============================================================================
 *
 */
static void send_cmd_opcode
(
    uint8_t opcode
)
{
    uint32_t tx_okay;
    
    /* Set transmit FIFO to transfer bytes. */
    COMBLK->CONTROL &= ~CR_SIZETX_MASK;
    
    /* Wait for space to become available in Tx FIFO. */
    do {
        tx_okay = COMBLK->STATUS & TXTOKAY_MASK;
    } while(0u == tx_okay);
    
    /* Send command opcode. */
    COMBLK->FRAME_START8 = opcode;
}

/*==============================================================================
 *
 */
static uint32_t fill_tx_fifo
(
    const uint8_t * p_cmd,
    uint32_t cmd_size
)
{
    volatile uint32_t tx_okay;
    uint32_t size_sent;

    /* Set transmit FIFO to transfer bytes. */
    COMBLK->CONTROL &= ~CR_SIZETX_MASK;
    
    size_sent = 0u;
    tx_okay = COMBLK->STATUS & TXTOKAY_MASK;
    while((tx_okay != 0u) && (size_sent < cmd_size))
    {
        COMBLK->DATA8 = p_cmd[size_sent];
        ++size_sent;
        tx_okay = COMBLK->STATUS & TXTOKAY_MASK;
    }
    
    return size_sent;
}

/*==============================================================================
 *
 */
static void process_sys_ctrl_command(uint8_t cmd_opcode)
{
    if(g_async_event_handler != 0)
    {
        g_async_event_handler(cmd_opcode);
    }
}

