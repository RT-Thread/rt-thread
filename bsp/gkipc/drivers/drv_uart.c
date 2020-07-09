#include <rtdevice.h>

#include "gtypes.h"
#include "gh_uart.h"
#include "gh_debug_rct.h"
#include "gd_uart.h"
#include "gd_int.h"

/*---------------------------------------------------------------------------*/
/* local defines                                                             */
/*---------------------------------------------------------------------------*/

#define UART_IRQ_CLEAR_ALL   0x3 /* IRQ CLR Register: rx_IRQ, rx_parity_IRQ  */
#define UART_RISING_TXE_RXE  0x3 /* for UART_control register:               */
                                 /* clock edge polarity = rising,            */
                                 /* TX = enable, RX = enable                 */

/* UART[x]_FC_REG */
#define UART_FC_RX_ONECHAR              0x0 /* RCVR_Trigger: FIFO has 1 char */
#define UART_FC_RX_QUARTER_FULL         0x1 /* RCVR_Trigger: FIFO is one-fourth to full */
#define UART_FC_RX_HALF_FULL            0x2 /* RCVR_Trigger: FIFO is half to full */
#define UART_FC_RX_2_TO_FULL            0x3 /* RCVR_Trigger: FIFO is 2 char to full */
#define UART_FC_TX_EMPTY                0x0 /* TX_Empty_Trigger:  FIFO is empty */
#define UART_FC_TX_2_IN_FIFO            0x1 /* TX_Empty_Trigger:  FIFO has 2 char */
#define UART_FC_TX_QUATER_IN_FIFO       0x2 /* TX_Empty_Trigger:  FIFO is one-fourth to full */
#define UART_FC_TX_HALF_IN_FIFO         0x3 /* TX_Empty_Trigger:  FIFO is half to full */

/* UART[x]_II_REG */
#define UART_II_MODEM_STATUS_CHANGED    0x0
#define UART_II_NO_INT_PENDING          0x1
#define UART_II_THR_EMPTY               0x2
#define UART_II_RCV_DATA_AVAIL          0x4
#define UART_II_RCV_STATUS              0x6
#define UART_II_CHAR_TIMEOUT            0xc

#define MAX_UART_CNT    (3)

/*---------------------------------------------------------------------------*/
/* local data types                                                          */
/*---------------------------------------------------------------------------*/

struct gk_uart
{
    u8 index;
};

/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/

static struct gk_uart uart[MAX_UART_CNT] =
{
    {0},{1},{2}
};

static GD_HANDLE intHandle[MAX_UART_CNT];
static struct rt_serial_device serial[MAX_UART_CNT];

/*---------------------------------------------------------------------------*/
/* local  functions                                                          */
/*---------------------------------------------------------------------------*/

static void uartSetBaudrate(U32 index, U32 baudRate)
{
    U32 brdi;
    GH_PLL_set_SCALER_UART(0x01);
    brdi = (48000000/2) * 10 / baudRate / 16;
    if (brdi % 10 >= 5)
        brdi = (brdi / 10) + 1;
    else
        brdi = (brdi / 10);
    GH_UART_set_LCR_dlab(index, 1);
    GH_UART_set_DLL_BaudDivint_L(index, brdi & 0xff);
    GH_UART_set_DLH_BaudDivint_H(index, (brdi >> 8) & 0xff);
    GH_UART_set_LCR_dlab(index, 0);
}

static void uartSetDataBits(U32 index, U32 dataBits)
{
    U32 data_bits = dataBits;
    // 0 = use 5 data bits
    // 1 = use 6 data bits
    // 2 = use 7 data bits
    // 3 = use 8 data bits
    //data_bits -= GD_UART_5_DATATBITS;

    if(GH_UART_get_LCR_cls(index) != data_bits)
    {
         GH_UART_set_LCR_cls(index, data_bits);
    }
}

static void uartSetStopBits(U32 index, U32 stopBits)
{
    // 0 = use 1 stop bit
    // 1 = use 2 stop bits
    if(GH_UART_get_LCR_stop(index) != stopBits)
    {
         GH_UART_set_LCR_stop(index, stopBits);
    }
}

static void uartSetParity(U32 index, U32 parity)
{
    switch(parity)
    {
    case GD_UART_NO_PARITY:
        if(GH_UART_get_LCR_pen(index))
        {
            GH_UART_set_LCR_pen(index, 0);
        }
        break;

    case GD_UART_ODD_PARITY:
        if(!GH_UART_get_LCR_pen(index))
        {
            GH_UART_set_LCR_pen(index, 1);
        }
        if(GH_UART_get_LCR_eps(index))
        {
            GH_UART_set_LCR_eps(index, 0);
        }
        break;

    case GD_UART_EVEN_PARITY:
        if(!GH_UART_get_LCR_pen(index))
        {
            GH_UART_set_LCR_pen(index, 1);
        }
        if(!GH_UART_get_LCR_eps(index))
        {
            GH_UART_set_LCR_eps(index, 1);
        }
        break;

    default:
        break;
    }
}

static void uartSetFlowControl(U32 index, U32 flowCtrl)
{
    if(index == 0)
    {
        // In UART0, only the Loopback bit is used and flow control is not supported.
        // In UART1, all the bits are used.
        if((flowCtrl == 0) || (flowCtrl == 0x10))
        {
            if(GH_UART_get_MCR(index) != flowCtrl)
            {
                GH_UART_set_MCR(index, flowCtrl);
            }
        }
        return;
    }
    if(GH_UART_get_MCR(index) != flowCtrl)
    {
        GH_UART_set_MCR(index, flowCtrl);
    }
}

static void uartISR(void)
{
    U8 interruptID;
    interruptID = GH_UART_get_IIR_interrupt_id(0);

    switch (interruptID)
    {
        case UART_II_MODEM_STATUS_CHANGED:
        case UART_II_NO_INT_PENDING:
            break;
        case UART_II_THR_EMPTY:
            rt_hw_serial_isr(&serial[0], RT_SERIAL_EVENT_TX_DONE);
            break;
        case UART_II_RCV_DATA_AVAIL:
        case UART_II_RCV_STATUS:
            rt_hw_serial_isr(&serial[0], RT_SERIAL_EVENT_RX_IND);
            break;
        case UART_II_CHAR_TIMEOUT:
            GH_UART_get_RBR_Data(0);
            rt_hw_serial_isr(&serial[0], RT_SERIAL_EVENT_RX_TIMEOUT);
            break;
        default:
            break;
    }

}
static void uartISR1(void)
{
    U8 interruptID;
    interruptID = GH_UART_get_IIR_interrupt_id(1);

    switch (interruptID)
    {
        case UART_II_MODEM_STATUS_CHANGED:
        case UART_II_NO_INT_PENDING:
            break;
        case UART_II_THR_EMPTY:
            rt_hw_serial_isr(&serial[1], RT_SERIAL_EVENT_TX_DONE);
            break;
        case UART_II_RCV_DATA_AVAIL:
        case UART_II_RCV_STATUS:
            rt_hw_serial_isr(&serial[1], RT_SERIAL_EVENT_RX_IND);
            break;
        case UART_II_CHAR_TIMEOUT:
            GH_UART_get_RBR_Data(1);
            rt_hw_serial_isr(&serial[1], RT_SERIAL_EVENT_RX_TIMEOUT);
            break;
        default:
            break;
    }

}

static void uartISR2(void)
{
    U8 interruptID;
    interruptID = GH_UART_get_IIR_interrupt_id(2);

    switch (interruptID)
    {
        case UART_II_MODEM_STATUS_CHANGED:
        case UART_II_NO_INT_PENDING:
            break;
        case UART_II_THR_EMPTY:
            rt_hw_serial_isr(&serial[2], RT_SERIAL_EVENT_TX_DONE);
            break;
        case UART_II_RCV_DATA_AVAIL:
        case UART_II_RCV_STATUS:
            rt_hw_serial_isr(&serial[2], RT_SERIAL_EVENT_RX_IND);
            break;
        case UART_II_CHAR_TIMEOUT:
            GH_UART_get_RBR_Data(2);
            rt_hw_serial_isr(&serial[2], RT_SERIAL_EVENT_RX_TIMEOUT);
            break;
        default:
            break;
    }

}


static GERR uartSetIntMode(U8 channel)
{

    GD_UART_STATE_MACHINE_S* uart_handle_ptr = NULL;
    GD_INT_OPEN_PARAMS_S intParams;
    GERR                 ret = GD_OK;

    intParams.sensitivity    = GD_INT_LEVEL_HIGH;    //hhl note: check this value.
    intParams.active         = GD_INT_INVERT_IRQ;
    intParams.priority       = GD_INT_MID_PRIORITY;

    if(channel == 0)
    {
        intParams.type           = (S8)GD_INT_UART_IRQ;
        intParams.isrFct.lowPrio = uartISR;
        ret = GD_INT_Open(&intParams, &intHandle[0]);
    }
    else if(channel == 1)
    {
        intParams.type           = (S8)GD_INT_UART1_IRQ;
        intParams.isrFct.lowPrio = uartISR1;
        ret = GD_INT_Open(&intParams, &intHandle[1]);
    }
    else
    {
        intParams.type           = (S8)GD_INT_UART2_IRQ;
        intParams.isrFct.lowPrio = uartISR2;
        ret = GD_INT_Open(&intParams, &intHandle[2]);
    }

    return ret;
}

/**
* UART device in RT-Thread
*/
static rt_err_t gk_uart_configure(struct rt_serial_device *serial,
                                struct serial_configure *cfg)
{
    int div;
    GD_UART_DATABITS_E data_mode;
    GD_UART_STOPBITS_E stop_mode;
    GD_UART_PARITY_E parity_mode;
    struct gk_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct gk_uart *)serial->parent.user_data;

    switch (cfg->data_bits)
    {
        case DATA_BITS_8:
            data_mode = GD_UART_8_DATATBITS;
            break;
        case DATA_BITS_7:
            data_mode = GD_UART_7_DATATBITS;
            break;
        case DATA_BITS_6:
            data_mode = GD_UART_6_DATATBITS;
            break;
        case DATA_BITS_5:
            data_mode = GD_UART_5_DATATBITS;
            break;
        default:
            data_mode = GD_UART_8_DATATBITS;
            break;
    }

    switch (cfg->stop_bits)
    {
        case STOP_BITS_2:
            stop_mode = GD_UART_20_STOPBITS;//UART_STOP_BIT2;
            break;
        case STOP_BITS_1:
        default:
            stop_mode = GD_UART_10_STOPBITS;
            break;
    }

    switch (cfg->parity)
    {
        case PARITY_ODD:
            parity_mode = GD_UART_ODD_PARITY;
            break;
        case PARITY_EVEN:
            parity_mode = GD_UART_EVEN_PARITY;
            break;
        case PARITY_NONE:
        default:
            parity_mode = GD_UART_NO_PARITY;
            break;
    }

    uartSetBaudrate(uart->index,cfg->baud_rate);
    uartSetDataBits(uart->index,   data_mode);
    uartSetParity(uart->index,     parity_mode);
    uartSetStopBits(uart->index,   stop_mode);
    uartSetFlowControl(uart->index,0);

    return RT_EOK;
}

#define RT_DEVICE_CTRL_GET_CONFIG 0xFF

static rt_err_t gk_uart_control(struct rt_serial_device *serial,
                              int cmd, void *arg)
{
    struct gk_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct gk_uart *)serial->parent.user_data;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_CLR_INT:
            /* disable rx irq */
            GD_INT_Enable(&intHandle[uart->index],0);

            GH_UART_set_IER_erbfi(uart->index, 0);

            break;
        case RT_DEVICE_CTRL_SET_INT:
            /* enable rx irq */

            GH_UART_set_FCR_FIFO_Enable(uart->index, 1);
            GH_UART_set_FCR_RCVR_Trigger(uart->index, UART_FC_RX_ONECHAR);
            GH_UART_set_FCR_TX_Empty_Trigger(uart->index, UART_FC_TX_EMPTY);
            GH_UART_set_FCR_XMIT_FIFO_Reset(uart->index, 1);
            GH_UART_set_FCR_RCVR_FIFO_Reset(uart->index, 1);
            GH_UART_set_IER_etbei(uart->index, 0); //Turn off THRE interrupt

            uartSetIntMode(uart->index);

            GD_INT_Enable(&intHandle[uart->index],1);

            GH_UART_set_IER_erbfi(uart->index,1);
            GH_UART_set_IER_elsi(uart->index,1);

            break;

        case RT_DEVICE_CTRL_GET_CONFIG:
            if(!arg)
            {
                rt_kprintf("%s,line=%d,param is NULL!\n",__FUNCTION__,__LINE__);
                return RT_ERROR;
            }

            *((struct serial_configure *)arg) = serial->config;

            break;

        default:
            break;
    }

    return RT_EOK;
}

static int gk_uart_putc(struct rt_serial_device *serial, char c)
{
    struct gk_uart *uart = serial->parent.user_data;
    unsigned int ret;
    ret = GH_UART_get_LSR_temt(uart->index);

    if(serial->parent.open_flag & RT_DEVICE_FLAG_INT_TX){

        GH_UART_set_THR_Data(uart->index, c);
        if (GH_UART_get_IER_etbei(uart->index) == 0)
        {
            GH_UART_set_IER_etbei(uart->index, 1); //Turn on THRE interrupt
        }
        return 1;
    }
    else
    {
        while(!GH_UART_get_LSR_temt(uart->index));
        GH_UART_set_THR_Data(uart->index, c);
        return 1;
    }

}

static int gk_uart_getc(struct rt_serial_device *serial)
{
    struct gk_uart *uart = serial->parent.user_data;

    if(!GH_UART_get_LSR_dr(uart->index))
        return -1;

    return GH_UART_get_RBR_Data(uart->index);

}

static const struct rt_uart_ops gk_uart_ops =
{
    gk_uart_configure,
    gk_uart_control,
    gk_uart_putc,
    gk_uart_getc,
};

/**
 * This function will handle init uart
 */
void rt_hw_uart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    int i;
    char devname[6];

    for(i=0; i<MAX_UART_CNT; i++)
    {
        serial[i].ops = &gk_uart_ops;
        serial[i].config = config;

        rt_sprintf(devname,"uart%d",i);

        rt_hw_serial_register(&serial[i], devname,
                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_STREAM ,
                &uart[i]);
    }
}


int GM_Printf(const char *__format, ...)
{
    rt_kprintf(__format);

    return 0;
}


