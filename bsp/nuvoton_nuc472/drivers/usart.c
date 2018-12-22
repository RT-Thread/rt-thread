/*
 * File      : usart.c
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-12     Bluebear233  first implementation
 */

#include <rtconfig.h>
#include <rtdevice.h>
#include <usart.h>
#include <NUC472_442.h>

/* Private Define ---------------------------------------------------------------*/
#define USEING_UART0                    //Tx:PG2  Rx:PG1

/* Private Typedef --------------------------------------------------------------*/
struct usart
{
    rt_serial_t dev;
    UART_T *usart_base;
};
typedef struct usart* usart_t;

/* Private functions ------------------------------------------------------------*/


static rt_err_t usart_gpio_configure(struct rt_serial_device *serial);
static rt_err_t usart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t usart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int usart_send(struct rt_serial_device *serial, char c);
static int usart_receive(struct rt_serial_device *serial);
static void rt_hw_uart_register(usart_t uart, UART_T *uart_base,
        char *name);
static void uart_isr(usart_t serial);
//static rt_err_t stm32_uart_tx_dma_configure(rt_stm32_uart_t *serial, rt_bool_t bool);
//static rt_err_t stm32_uart_tx_dma_nvic(rt_stm32_uart_t *serial, rt_bool_t bool);


/* Private Variables ------------------------------------------------------------*/
static const struct rt_uart_ops stm32_uart_ops =
{ usart_configure, usart_control, usart_send, usart_receive,
        RT_NULL };

static const struct serial_configure stm32_uart_default_config =
RT_SERIAL_CONFIG_DEFAULT;

#ifdef USEING_UART0
struct usart uart0;
#endif

/* Interrupt Handle Funtion  ----------------------------------------------------*/
#ifdef USEING_UART0
/* 串口0 中断入口 */
void UART0_IRQHandler(void)
{
    uart_isr(&uart0);
}
#endif

/**
 * 中断处理函数
 */
static void uart_isr(usart_t serial)
{
    // 获取串口基地址
    UART_T *uart_base = ((usart_t)serial)->usart_base;

    // 获取中断事件
    uint32_t u32IntSts= uart_base->INTSTS;

    // 接收中断
    if(u32IntSts & (UART_INTSTS_RDAINT_Msk | UART_INTSTS_RXTOINT_Msk))
    {
        rt_hw_serial_isr(&serial->dev, RT_SERIAL_EVENT_RX_IND);
    }

}

/**
 * 串口端口配置
 */
static rt_err_t usart_gpio_configure(struct rt_serial_device *serial)
{
    // 获取串口基地址
    UART_T *uart_base = ((usart_t)serial)->usart_base;

    switch((uint32_t)uart_base)
    {
    case UART0_BASE:
        SYS->GPG_MFPL = SYS_GPG_MFPL_PG1MFP_UART0_RXD | SYS_GPG_MFPL_PG2MFP_UART0_TXD;
        break;

    default:
        rt_kprintf("unknow uart module\n");
        RT_ASSERT(0);
    }

    return RT_EOK;
}

/**
 * 串口配置
 */
static rt_err_t usart_configure(struct rt_serial_device *serial,
        struct serial_configure *cfg)
{
    // 获取串口基地址
    UART_T *uart_base = ((usart_t)serial)->usart_base;

    uint32_t uart_module = 0;
    uint32_t uart_word_len = 0;
    uint32_t uart_stop_bit = 0;
    uint32_t uart_parity = 0;
    uint32_t uart_irq_channel = 0;

    switch((uint32_t)uart_base)
    {
    case UART0_BASE:
        uart_module = UART0_MODULE;
        uart_irq_channel = UART0_IRQn;
        break;

    default:
        rt_kprintf("unknow uart module\n");
        RT_ASSERT(0);
    }

    /* Enable IP clock */
    CLK_EnableModuleClock(uart_module);

    /* Select IP clock source */
    CLK_SetModuleClock(uart_module, CLK_CLKSEL1_UARTSEL_HXT, CLK_CLKDIV0_UART(1));

    /* check baudrate */
    RT_ASSERT(cfg->baud_rate != 0);

    /* check word len */
    switch(cfg->data_bits)
    {
    case DATA_BITS_5:
        uart_word_len = UART_WORD_LEN_5;
        break;

    case DATA_BITS_6:
        uart_word_len = UART_WORD_LEN_6;
        break;

    case DATA_BITS_7:
        uart_word_len = UART_WORD_LEN_7;
        break;

    case DATA_BITS_8:
        uart_word_len = UART_WORD_LEN_8;
        break;

    default:
        rt_kprintf("unsupose data len");
        RT_ASSERT(0);
    }

    /* check stop bit */
    switch(cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart_stop_bit = UART_STOP_BIT_1;
        break;

    case STOP_BITS_2:
        uart_stop_bit = UART_STOP_BIT_2;
        break;

    default:
        rt_kprintf("unsupose stop bit");
        RT_ASSERT(0);
    }

    /* check stop bit */
    switch(cfg->parity)
    {
    case PARITY_NONE:
        uart_parity = UART_PARITY_NONE;
        break;

    case PARITY_ODD:
        uart_parity = UART_PARITY_ODD;
        break;

    case PARITY_EVEN:
        uart_parity = UART_PARITY_EVEN;
        break;

    default:
        rt_kprintf("unsupose parity");
        RT_ASSERT(0);
    }

    /* Open uart */
    {
        uint8_t u8UartClkSrcSel;
        uint32_t u32ClkTbl[4] = {__HXT, 0, __HIRC, __HIRC};
        uint32_t u32Clk;
        uint32_t u32Baud_Div;

        u32ClkTbl[1] = CLK_GetPLLClockFreq();

        u8UartClkSrcSel = (CLK->CLKSEL1 & CLK_CLKSEL1_UARTSEL_Msk) >> CLK_CLKSEL1_UARTSEL_Pos;

        uart_base->FUNCSEL = UART_FUNCSEL_UART;
        uart_base->LINE = uart_word_len | uart_stop_bit | uart_parity;
        uart_base->FIFO = 6 << UART_FIFO_RFITL_Pos;
        uart_base->TOUT = (1 << UART_TOUT_DLY_Pos) | (40 << UART_TOUT_TOIC_Pos);

        u32Clk = (u32ClkTbl[u8UartClkSrcSel]) / (((CLK->CLKDIV0 & CLK_CLKDIV0_UARTDIV_Msk) >> CLK_CLKDIV0_UARTDIV_Pos) + 1);

        u32Baud_Div = UART_BAUD_MODE2_DIVIDER(u32Clk, cfg->baud_rate);

        if (u32Baud_Div > 0xFFFF)
            uart_base->BAUD = (UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER(u32Clk, cfg->baud_rate));
        else
            uart_base->BAUD = (UART_BAUD_MODE2 | u32Baud_Div);
    }


    /* config nvic */
    NVIC_EnableIRQ(uart_irq_channel);

    /* config gpio */
    usart_gpio_configure(serial);

    return RT_EOK;
}

/**
 * 串口中断控制
 */
static rt_err_t usart_control(struct rt_serial_device *serial,
        int cmd, void *arg)
{
    rt_err_t result = RT_EOK;
    rt_uint32_t flag;

    // 获取串口基地址
    UART_T *uart_base = ((usart_t)serial)->usart_base;

    switch ((uint32_t) arg)
    {
    case RT_DEVICE_FLAG_INT_RX:
        flag = UART_INTEN_RDAIEN_Msk | UART_INTEN_RXTOIEN_Msk | UART_INTEN_TOCNTEN_Msk;

        switch (cmd)
        {
        case RT_DEVICE_CTRL_CLR_INT:
            UART_DISABLE_INT(uart_base, flag);
            break;
        case RT_DEVICE_CTRL_SET_INT:
            UART_ENABLE_INT(uart_base, flag);
            break;
        default:
            RT_ASSERT(0);
        }
        break;
// TODO 完善DMA接口
//    case RT_DEVICE_FLAG_DMA_TX:
//        USART_DMACmd(dev->usart_base, USART_DMAReq_Tx, ENABLE);
//        stm32_uart_tx_dma_configure(dev, RT_TRUE);
//        stm32_uart_tx_dma_nvic(dev, RT_TRUE);
//        break;
    default:
        RT_ASSERT(0)
        ;
    }

    return result;



    return RT_EOK;
}

/**
 * 串口发送函数
 */
static int usart_send(struct rt_serial_device *serial, char c)
{
    // 获取串口基地址
    UART_T *uart_base = ((usart_t)serial)->usart_base;

    // 等待FIFO 发送
    while(uart_base->FIFOSTS & UART_FIFOSTS_TXFULL_Msk);

    // 发送字符
    uart_base->DAT = c;

    return 1;
}

/**
 * 串口接收函数
 */
static int usart_receive(struct rt_serial_device *serial)
{
    // 获取串口基地址
    UART_T *uart_base = ((usart_t)serial)->usart_base;

    // 如果FIFO 为空返回
    if(uart_base->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk)
    {
        return -1;
    }

    return UART_READ(uart_base);
}

/**
 * @brief 串口设备注册
 * @param uart           : UART设备结构体
 * @param uart_base      : STM32 UART外设基地址
 * @param name           : STM32 UART设备名
 * @param tx_dma_channel : STM32 UART TX的DMA通道基地址(可选)
 */
static void rt_hw_uart_register(usart_t usart, UART_T * uart_base, char *name)
{
    rt_uint32_t flag;
    RT_ASSERT(usart != RT_NULL);
    RT_ASSERT(uart_base != RT_NULL);

    // 没有定义对应的硬件I2C
    if (!(uart_base == UART0 || uart_base == UART1 || uart_base == UART2
            || uart_base == UART3 || uart_base == UART4 || uart_base == UART5))
    {
        RT_ASSERT(0);
    }

    usart->usart_base = uart_base;
    usart->dev.ops = &stm32_uart_ops;
    usart->dev.config = stm32_uart_default_config;

    flag = RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX;

    rt_hw_serial_register(&usart->dev, name,
            flag, RT_NULL);
}

/**
 * 硬件串口注册
 */
void rt_hw_usart_init(void)
{
#ifdef USEING_UART0
    rt_hw_uart_register(&uart0, UART0, "uart0");
#endif
}
