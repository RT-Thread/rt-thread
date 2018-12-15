

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "gps.h"
#include "appconfig.h"


#define SAMPLE_UART_NAME       "uart2"

static rt_device_t gpsserial;
/* 用于接收消息的信号量 */
static struct rt_semaphore rx_sem;
static char uart_name[RT_NAME_MAX];
static RxControl_Type gpsRx;
static TxControl_Type gpsTx;
static char gpsRXBuf[1024];
static char gpsTXBuf[1024];
/* 接收数据回调函数 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

void  gps_thread_entry(void*param)
{
    rt_uint16_t len = 0;
    while (1)
    {

        while (rt_sem_take(&rx_sem, 10)==RT_EOK)/* 阻塞等待接收信号量，等到信号量后再次读取数据 */
        {
            /* 从串口读取一个字节的数据，没有读取到则等待接收信号量 */
            len += rt_device_read(gpsserial, -1, &gpsRx.recBuf[len], 40);
            if(len>1024)
                len = 0;
        }
        gpsRx.recsize = len;
        len = 0;
    }
}

//发送数据
static void tranData(unsigned char*data)
{
    if(data == 0)
        return;
    rt_device_write(gpsserial, 0, (const char*)data, strlen((const char*)data));
}

//串口初始化
static int initGps(void)
{
    rt_memset(gpsRXBuf,0,sizeof(gpsRXBuf));
    rt_memset(gpsTXBuf,0,sizeof(gpsTXBuf));
    memset(&gpsRx,0,sizeof(gpsRx));
    memset(&gpsTx,0,sizeof(gpsTx));
    gpsRx.recBuf = gpsRXBuf;
    gpsTx.trnBuf = gpsTXBuf;
    /* 查找系统中的串口设备 */
    gpsserial = rt_device_find(SAMPLE_UART_NAME);

    if (gpsserial != RT_NULL)
    {
        rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
        /* 以读写及中断接收方式打开串口设备 */
        rt_device_open(gpsserial, RT_DEVICE_OFLAG_RDWR|RT_DEVICE_FLAG_INT_RX);
        /* 设置接收回调函数 */
        rt_device_set_rx_indicate(gpsserial, uart_input);


    }
    else
    {
        rt_kprintf("uart sample run failed! can't find %s device!\n",uart_name);
        return RT_ERROR;
    }

    rt_thread_t tid;
    tid = rt_thread_create("gps",gps_thread_entry,RT_NULL,1024,10,20);
    if(tid)
        rt_thread_startup(tid);
    else
        return RT_ERROR;
    return RT_EOK;
}

INIT_APP_EXPORT(initGps);




