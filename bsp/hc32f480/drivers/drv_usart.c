/******************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
 *
 * This software is owned and published by:
 * Huada Semiconductor Co.,Ltd ("HDSC").
 *
 * BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
 * BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
 *
 * This software contains source code for use with HDSC
 * components. This software is licensed by HDSC to be adapted only
 * for use in systems utilizing HDSC components. HDSC shall not be
 * responsible for misuse or illegal use of this software for devices not
 * supported herein. HDSC is providing this software "AS IS" and will
 * not be responsible for issues arising from incorrect user implementation
 * of the software.
 *
 * Disclaimer:
 * HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
 * REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
 * ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
 * WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
 * WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
 * WARRANTY OF NONINFRINGEMENT.
 * HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
 * LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
 * INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
 * SAVINGS OR PROFITS,
 * EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
 * INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
 * FROM, THE SOFTWARE.
 *
 * This software may be replicated in part or whole for the licensed use,
 * with the restriction that this Disclaimer and Copyright notice must be
 * included with each copy of this software, whether used in part or whole,
 * at all times.
 */
/******************************************************************************/
/** \file drv_usart.c
 **
 ** History:
 **
 **   - 2018-05-30  1.0  JasonJia   First version.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtdevice.h>
#include "clk.h"
#include "usart.h"
#include "gpio.h"
#include "irq_map.h"
#include "interrupts_hc32f480.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
struct hc32_usart
{
    M4_USART_TypeDef                *usart_device;
    IRQn_Type                       irq_rx;
    IRQn_Type                       irq_tx;
};
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define UART1_PORT                  Port6
#define UART1_PIN_RX                Pin10
#define UART1_PIN_TX                Pin11

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static rt_err_t hc32_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t hc32_control(struct rt_serial_device *serial, int cmd, void *arg);
static int hc32_putc(struct rt_serial_device *serial, char c);
static int hc32_getc(struct rt_serial_device *serial);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
#if defined(RT_USING_UART1)
static struct hc32_usart usart1 =
{
    M4_USART1,
    USART1_RI_IRQn,
    USART1_TC_IRQn,
};
static struct rt_serial_device serial1;
#endif

static const struct rt_uart_ops hc32_usart_ops =
{
    hc32_configure,
    hc32_control,
    hc32_putc,
    hc32_getc,
};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
static rt_err_t hc32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct hc32_usart* usart;
    stc_uart_config_t stc_UartCfg;

    RT_ASSERT(RT_NULL != serial);
    RT_ASSERT(RT_NULL != cfg);

    usart = (struct hc32_usart *)serial->parent.user_data;

    RT_ASSERT(RT_NULL != usart);

    DDL_ZERO_STRUCT(stc_UartCfg);

    stc_UartCfg.u32Baudrate = cfg->baud_rate;

    if(BIT_ORDER_LSB == cfg->bit_order)
    {
        stc_UartCfg.enDataSequence = DataLSB;
    }
    else
    {
        stc_UartCfg.enDataSequence = DataMSB;
    }

    switch(cfg->stop_bits)
    {
    case STOP_BITS_1:
        stc_UartCfg.enStopBit = Stop1Bit;
        break;
    case STOP_BITS_2:
        stc_UartCfg.enStopBit = Stop2Bit;
        break;
    default:
        RT_ASSERT(0);
        break;
    }

    switch(cfg->parity)
    {
    case PARITY_NONE:
        stc_UartCfg.enParity = ParityDisEn;
        break;
    case PARITY_EVEN:
        stc_UartCfg.enParity = ParityEven;
        break;
    default:
        stc_UartCfg.enParity = ParityOdd;
        break;
    }

    switch(cfg->data_bits)
    {
    case DATA_BITS_8:
        stc_UartCfg.enDataLength = Len8bit;
        break;
    case DATA_BITS_9:
        stc_UartCfg.enDataLength = Len9bit;
        break;
    default:
        RT_ASSERT(0);
        break;
    }

    UART_Init(usart->usart_device, &stc_UartCfg);

    if(serial->parent.flag & RT_DEVICE_FLAG_RDWR || serial->parent.flag & RT_DEVICE_FLAG_RDONLY)
    {
        UART_FuncCfg(usart->usart_device, FuncRxEn, Enable);
    }

    if(serial->parent.flag & RT_DEVICE_FLAG_RDWR || serial->parent.flag & RT_DEVICE_FLAG_WRONLY)
    {
        UART_FuncCfg(usart->usart_device, FuncTxEn, Enable);
    }

    return RT_EOK;
}

static rt_err_t hc32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hc32_usart* usart;
    rt_uint32_t ctrl_arg = (rt_uint32_t)(arg);

    RT_ASSERT(RT_NULL != serial);
    usart = (struct hc32_usart *)serial->parent.user_data;

    RT_ASSERT(RT_NULL != usart);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:

        if(RT_DEVICE_FLAG_INT_RX == ctrl_arg)
        {
            /* Disable rx irq */
            NVIC_DisableIRQ(usart->irq_rx);
            /* Disable interrupt */
            UART_FuncCfg(usart->usart_device, FuncRxIrqEn, Disable);
        }
        else
        {
            /* Disable tx irq */
            NVIC_DisableIRQ(usart->irq_tx);
            /* Disable interrupt */
            UART_FuncCfg(usart->usart_device, FuncTxCompleteIrqEn, Disable);
        }

        break;
    case RT_DEVICE_CTRL_SET_INT:

        if(RT_DEVICE_FLAG_INT_RX == ctrl_arg)
        {
            /* Enable rx irq */
            NVIC_EnableIRQ(usart->irq_rx);
            /* Enable interrupt */
            UART_FuncCfg(usart->usart_device, FuncRxIrqEn, Enable);
        }
        else
        {
            /* Enable tx irq */
            NVIC_EnableIRQ(usart->irq_tx);

            /* Do not enable tx interrupt here! */
        }

        break;
    case RT_DEVICE_CTRL_CONFIG:
        //TBD
        break;
    }

    return RT_EOK;
}

static int hc32_putc(struct rt_serial_device *serial, char c)
{
    struct hc32_usart* usart;

    RT_ASSERT(RT_NULL != serial);
    usart = (struct hc32_usart*)serial->parent.user_data;

    RT_ASSERT(RT_NULL != usart);

    if(serial->parent.open_flag & RT_DEVICE_FLAG_INT_TX)
    {
        /* Interrupt mode. */
        if(c == '\n')
        {
            c = '\r';
        }

        UART_SendData(usart->usart_device, c);
        UART_FuncCfg(usart->usart_device, FuncTxCompleteIrqEn, Enable);

        /* return -1 to wait TC. */
        return -1;
    }
    else
    {
        /* Polling mode. */
        UART_SendData(usart->usart_device, c);
        while(UART_GetStatus(usart->usart_device, FlagTxComplete) != RT_TRUE);
    }

    return 1;
}

static int hc32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct hc32_usart* usart;

    RT_ASSERT(RT_NULL != serial);
    usart = (struct hc32_usart*)serial->parent.user_data;

    RT_ASSERT(RT_NULL != usart);

    ch = -1;

    if(UART_GetStatus(usart->usart_device, FlagRxFull))
    {
        ch = (rt_uint8_t)UART_RevData(usart->usart_device);
    }

    return ch;
}

static void uart1_rx_irq_handler(void)
{
    struct hc32_usart* usart = (struct hc32_usart*)serial1.parent.user_data;

    RT_ASSERT(RT_NULL != usart);

    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);

    /* Do not support clear RXFF flag.Recv data will clear it. */

    /* leave interrupt */
    rt_interrupt_leave();
}

static void uart1_tx_irq_handler(void)
{
    struct hc32_usart* usart = (struct hc32_usart*)serial1.parent.user_data;

    RT_ASSERT(RT_NULL != usart);

    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_TX_DONE);

    /* Disable TC. Do not support clear TC flag.Send data will clear it. */
    UART_FuncCfg(usart->usart_device, FuncTxCompleteIrqEn, Enable);

    /* leave interrupt */
    rt_interrupt_leave();
}

int hc32_hw_console_init(const char *name)
{
    stc_port_init_t stcPortInit;
    stc_irq_regi_conf_t stcIrqRegiConf;
    struct hc32_usart *usart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART1
    /* Enable UART1 clock */
    Clk_Fcg1PeriphClockCmd(CLK_FCG1_PERIPH_UART1, Enable);

    /* Config gpio. */
    DDL_ZERO_STRUCT(stcPortInit);
    stcPortInit.bPuEn = 1;
    /* RXD1(P610) pull-up enable. */
    Port_Init(UART1_PORT, UART1_PIN_RX, stcPortInit);

    /* Enable gpio usart function. */
    Port_Unlock();
    Port_SetFunc(UART1_PORT, UART1_PIN_RX, Func_SciOdd, Disable);
    Port_SetFunc(UART1_PORT, UART1_PIN_TX, Func_SciOdd, Disable);
    Port_Lock();

    usart = &usart1;

    /* Config rx nvic. */
    stcIrqRegiConf.enIRQn = usart->irq_rx;
    stcIrqRegiConf.enIntSrc = USART1_RI;
    stcIrqRegiConf.pfnCallback = uart1_rx_irq_handler;
    enIrqRegistration(stcIrqRegiConf);
    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
    NVIC_SetPriority(stcIrqRegiConf.enIRQn, 3);

    /* Config tx nvic.Do not use TI,it's not compatible with serial framework. */
    stcIrqRegiConf.enIRQn = usart->irq_tx;
    stcIrqRegiConf.enIntSrc = USART1_TCI;
    stcIrqRegiConf.pfnCallback = uart1_tx_irq_handler;
    enIrqRegistration(stcIrqRegiConf);
    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
    NVIC_SetPriority(stcIrqRegiConf.enIRQn, 4);

    serial1.ops = &hc32_usart_ops;
    serial1.config = config;

    rt_hw_serial_register(  &serial1,
                            name,
                            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX,
                            usart);
#endif

    return 0;
}

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


