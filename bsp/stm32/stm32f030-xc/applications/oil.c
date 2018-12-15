

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "oil.h"
#include "appconfig.h"


#define SAMPLE_UART_NAME       "uart4"

static rt_device_t oilserial;
/* 用于接收消息的信号量 */
static struct rt_semaphore rx_sem;
static char uart_name[RT_NAME_MAX];
static RxControl_Type oilRx;
static TxControl_Type oilTx;
static char oilRXBuf[1024];
static char oilTXBuf[1024];
/* 接收数据回调函数 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

void  oil_thread_entry(void*param)
{
    rt_uint16_t len = 0;
    while (1)
    {

        while (rt_sem_take(&rx_sem, 10)==RT_EOK)/* 阻塞等待接收信号量，等到信号量后再次读取数据 */
        {
            /* 从串口读取一个字节的数据，没有读取到则等待接收信号量 */
            len += rt_device_read(oilserial, -1, &oilRx.recBuf[len], 40);
            if(len>1024)
                len = 0;
        }
        oilRx.recsize = len;
        len = 0;
    }
}

//发送数据
static void tranData(unsigned char*data)
{
    if(data == 0)
        return;
    rt_device_write(oilserial, 0, (const char*)data, strlen((const char*)data));
}

//串口初始化
static int initoil(void)
{
    rt_memset(oilRXBuf,0,sizeof(oilRXBuf));
    rt_memset(oilTXBuf,0,sizeof(oilTXBuf));
    memset(&oilRx,0,sizeof(oilRx));
    memset(&oilTx,0,sizeof(oilTx));
    oilRx.recBuf = oilRXBuf;
    oilTx.trnBuf = oilTXBuf;
    /* 查找系统中的串口设备 */
    oilserial = rt_device_find(SAMPLE_UART_NAME);

    if (oilserial != RT_NULL)
    {
        rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
        /* 以读写及中断接收方式打开串口设备 */
        rt_device_open(oilserial, RT_DEVICE_OFLAG_RDWR|RT_DEVICE_FLAG_INT_RX);
        /* 设置接收回调函数 */
        rt_device_set_rx_indicate(oilserial, uart_input);


    }
    else
    {
        rt_kprintf("uart sample run failed! can't find %s device!\n",uart_name);
        return RT_ERROR;
    }

    rt_thread_t tid;
    tid = rt_thread_create("oil",oil_thread_entry,RT_NULL,1024,8,20);
    if(tid)
        rt_thread_startup(tid);
    else
        return RT_ERROR;
    return RT_EOK;
}

INIT_APP_EXPORT(initoil);




