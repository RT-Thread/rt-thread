

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "sim800c.h"
#include "appconfig.h"

#define SAMPLE_UART_NAME       "uart6"

static rt_device_t sim800serial;
/* 用于接收消息的信号量 */
static struct rt_semaphore rx_sem;
/* 用于接收消息的信号量 */
static struct rt_semaphore simApp_sem;
static char uart_name[RT_NAME_MAX];
static RxControl_Type simRx;
static TxControl_Type simTx;
static char sim800RXBuf[1024];
static char sim800TXBuf[1024];
static void sim800cApp_thread_entry(void* param);
/* 接收数据回调函数 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

void  sim800_thread_entry(void*param)
{
    rt_uint16_t len = 0;
    while (1)
    {

        while (rt_sem_take(&rx_sem, 10)==RT_EOK)/* 阻塞等待接收信号量，等到信号量后再次读取数据 */
        {
            /* 从串口读取一个字节的数据，没有读取到则等待接收信号量 */
            len += rt_device_read(sim800serial, -1, &simRx.recBuf[len], 40);
            if(len>1024)
                len = 0;
        }
		simRx.recBuf[len+1] = '0';
        simRx.recsize = len;
		if(len>1)
			rt_sem_release(&simApp_sem);
        len = 0;
    }
}

//发送数据
static void tranData(unsigned char*data)
{
    if(data == 0)
        return;
    rt_device_write(sim800serial, 0, (const char*)data, strlen((const char*)data));
}

//串口初始化
static int initSim800c(void)
{
    rt_memset(sim800RXBuf,0,sizeof(sim800RXBuf));
    rt_memset(sim800TXBuf,0,sizeof(sim800TXBuf));
    memset(&simRx,0,sizeof(simRx));
    memset(&simTx,0,sizeof(simTx));
    simRx.recBuf = sim800RXBuf;
    simTx.trnBuf = sim800TXBuf;
    /* 查找系统中的串口设备 */
    sim800serial = rt_device_find(SAMPLE_UART_NAME);

    if (sim800serial != RT_NULL)
    {
        rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
        rt_sem_init(&simApp_sem, "simApp", 0, RT_IPC_FLAG_FIFO);
        /* 以读写及中断接收方式打开串口设备 */
        rt_device_open(sim800serial, RT_DEVICE_OFLAG_RDWR|RT_DEVICE_FLAG_INT_RX);
        /* 设置接收回调函数 */
        rt_device_set_rx_indicate(sim800serial, uart_input);


    }
    else
    {
        rt_kprintf("uart sample run failed! can't find %s device!\n",uart_name);
        return RT_ERROR;
    }

    rt_thread_t tid;
    tid = rt_thread_create("sim800",sim800_thread_entry,RT_NULL,1024,9,20);
    if(tid)
        rt_thread_startup(tid);
    else
        return -RT_ERROR;

    tid = rt_thread_create("simApp",sim800cApp_thread_entry,RT_NULL,1024,11,20);
    if(tid)
        rt_thread_startup(tid);
    else
        return -RT_ERROR;
	
    return RT_EOK;

}

INIT_APP_EXPORT(initSim800c);

char* cpin = "AT+CPIN?\r\n";//查询卡状态
char* creg = "AT+CREG?\r\n";//注册

//注册sim800c
void regSim800c(void)
{
    while(1)
    {
        tranData((rt_uint8_t*)cpin);
		rt_sem_take(&simApp_sem,500);
        if(simRx.recsize<2)
        {
            rt_thread_delay(500);
            continue;
        }
		rt_kprintf("\n%s\n",sim800RXBuf);
        simRx.recsize = 0;
        tranData((rt_uint8_t*)creg);
		rt_sem_take(&simApp_sem,500);
        if(simRx.recsize<2)
        {
            rt_thread_delay(500);
            continue;
        }
		rt_kprintf("\n%s\n",sim800RXBuf);
        simRx.recsize = 0;
//		return;
    }

}
static void sim800cApp_thread_entry(void* param)
{
    regSim800c();
    rt_kprintf("sim800c reg success!\n");
    while(1)
    {
            rt_thread_delay(500);
    }
}

