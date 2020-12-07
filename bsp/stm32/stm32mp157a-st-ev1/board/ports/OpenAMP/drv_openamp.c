/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-24     thread-liu   first version
 */

#include <board.h>

#ifdef BSP_USING_OPENAMP

#include <finsh.h>
#include <drv_openamp.h>
#include <openamp.h>
#include <virt_uart.h>
#include <openamp/rpmsg_virtio.h>

//#define DRV_DEBUG
#define LOG_TAG             "drv.openamp"
#include <drv_log.h>

IPCC_HandleTypeDef hipcc;
static VIRT_UART_HandleTypeDef huart0;

static rt_uint8_t rx_buffer[MAX_BUFFER_SIZE];
static rt_uint8_t tx_buffer[MAX_BUFFER_SIZE];
  
struct rthw_openamp
{
    struct rt_device  parent;
    struct rt_openamp serial;
    struct rt_semaphore sema;
};
static struct rthw_openamp  dev_openamp;

void IPCC_RX1_IRQHandler(void) 
{
    rt_interrupt_enter();
    
    HAL_IPCC_RX_IRQHandler(&hipcc);
    
    rt_interrupt_leave();
}

void IPCC_TX1_IRQHandler(void)
{
    rt_interrupt_enter();
        
    HAL_IPCC_TX_IRQHandler(&hipcc);
    
    rt_interrupt_leave();
}

void VIRT_UART0_RxCpltCallback(VIRT_UART_HandleTypeDef *huart) 
{  
    rt_uint16_t rx_size = 0, i = 0;
    rt_size_t count, size, offset;
    rt_uint8_t *buf = RT_NULL;
    
    struct rthw_openamp  *device;
    device = (struct rthw_openamp *)rt_device_find("openamp");
    RT_ASSERT(device != RT_NULL);
   
    buf    = device->serial.rbuf; 
    count  = device->serial.rbuf_count;
    size   = device->serial.rbuf_size;
    offset = device->serial.rbuf_start + count;
   
    rt_sem_take(&device->sema, RT_WAITING_FOREVER);
        
    rx_size = (huart->RxXferSize < MAX_BUFFER_SIZE) ? huart->RxXferSize : MAX_BUFFER_SIZE - 1;

    if (count < size)
    {
        if (offset >= size)
        {
            offset -= size;
        }
        
        for (i = 0; i < rx_size; i++)
        {
           buf[offset++] = huart->pRxBuffPtr[i];
           count++;
        }
    }

    device->serial.rbuf_count = count;
    
    rt_sem_release(&device->sema);
}
 
static rt_err_t _init(struct rt_device *dev)
{
    struct rthw_openamp  *device;
    device = (struct rthw_openamp *)dev;
    RT_ASSERT(device != RT_NULL);
    
    device->serial.rbuf_start  = 0;
    device->serial.rbuf_count  = 0;
    device->serial.tbuf_start  = 0;
    device->serial.tbuf_count  = 0;
    device->serial.rbuf_size   = MAX_BUFFER_SIZE;
    device->serial.tbuf_size   = MAX_BUFFER_SIZE;
    device->serial.rbuf        = rx_buffer;
    device->serial.tbuf        = tx_buffer;
  
    if (rt_sem_init(&device->sema, "openamplock", 1, RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        return RT_ERROR;
    }
    
    return RT_EOK;
}

static rt_size_t _read(struct rt_device *dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_size_t count, rbsize, offset;
    rt_uint8_t *buf     = RT_NULL; 
    rt_uint8_t *pBuffer = RT_NULL;
    rt_uint16_t i = 0;
    
    struct rthw_openamp  *device;
    device = (struct rthw_openamp *)dev;
    RT_ASSERT(device != RT_NULL);
    
    pBuffer = (unsigned char*)buffer;
    count   = device->serial.rbuf_count;
    buf     = device->serial.rbuf;
    
    if (count == 0)
    {
        return -RT_ERROR;
    }
    
    rt_sem_take(&device->sema, RT_WAITING_FOREVER);
    
    if (count >= size)
    {
        count = size;
    } 

    offset = device->serial.rbuf_start;
    rbsize = device->serial.rbuf_size;
 
    for (i = 0; i < count; i++)
    {
        *pBuffer++ = buf[offset++];
        if (offset > rbsize)
        {
           offset = 0;  
        }
    }

    device->serial.rbuf_start  = offset;
    device->serial.rbuf_count -= count;
    
    rt_sem_release(&device->sema);
    
    return count;
}
 
static rt_size_t _write(struct rt_device *dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_err_t result = VIRT_UART_OK;
    
    struct rthw_openamp  *device;
    device = (struct rthw_openamp *)dev;
    RT_ASSERT(device != RT_NULL);
    
    rt_sem_take(&device->sema, RT_WAITING_FOREVER);
    result = VIRT_UART_Transmit(&huart0, (uint8_t *)buffer, size); 
    rt_sem_release(&device->sema);
        
    if (result != VIRT_UART_OK)
    {
        return -RT_ERROR;
    }
    
    return size;
}

static rt_err_t rt_hw_openamp_register(struct rthw_openamp  *openamp, const char *name, rt_uint32_t flag, void *data)
{
    struct rt_device *device;
    RT_ASSERT(openamp != RT_NULL);

    device = &(openamp->parent);

    device->type        = RT_Device_Class_Char;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

    device->init        = _init;
    device->open        = RT_NULL;
    device->close       = RT_NULL;
    device->read        = _read;
    device->write       = _write;
    device->control     = RT_NULL;
    device->user_data   = data;

    /* register a character device */
    return rt_device_register(device, name, flag);
}

static int openamp_init(void)
{  
    extern int MX_OPENAMP_Init(int RPMsgRole, rpmsg_ns_bind_cb ns_bind_cb);

    /* IPCC init */
    hipcc.Instance = IPCC;
    if (HAL_IPCC_Init(&hipcc) != HAL_OK)
    {
        return RT_ERROR;
    }
    /* openamp slave device */
    MX_OPENAMP_Init(RPMSG_REMOTE, NULL);
    
    if (VIRT_UART_Init(&huart0) != VIRT_UART_OK) 
    {
        return RT_ERROR;
    }
    if (VIRT_UART_RegisterCallback(&huart0, VIRT_UART_RXCPLT_CB_ID, VIRT_UART0_RxCpltCallback) != VIRT_UART_OK) 
    {
        return RT_ERROR;
    }
    
    return RT_EOK;    
}

int rt_hw_openamp_init(void)
{
    openamp_init();
    
    rt_hw_openamp_register(&dev_openamp, "openamp", 0, NULL);
    
    if (RT_CONSOLE_DEVICE_NAME == "openamp")
    {
        rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
    }

    return RT_EOK;
}
INIT_PREV_EXPORT(rt_hw_openamp_init);

static void openamp_thread_entry(void *parameter) 
{
    rt_size_t size = 0;
    struct rthw_openamp  *device = RT_NULL;
    
    device = (struct rthw_openamp *)rt_device_find("openamp");
    RT_ASSERT(device != RT_NULL);
    
    for (;;) 
    {
        OPENAMP_check_for_message();

        size = device->serial.rbuf_count;
        if (size > 0)
        {
            if (device->parent.rx_indicate != RT_NULL) 
            {
                device->parent.rx_indicate(&device->parent, size);
            }
        }
        
        rt_thread_mdelay(1);
    }
}

static int creat_openamp_thread(void)
{
    rt_thread_t tid = RT_NULL;
    
    tid = rt_thread_create("OpenAMP", 
                        openamp_thread_entry, 
                        RT_NULL, 
                        OPENAMP_THREAD_STACK_SIZE, 
                        OPENAMP_THREAD_PRIORITY, 
                        OPENAMP_THREAD_TIMESLICE);
    
    if (tid == RT_NULL) 
    {
        LOG_E("openamp thread create failed!");
        return RT_ERROR;
    } 
    
    rt_thread_startup(tid);
    
    return RT_EOK;
}
INIT_APP_EXPORT(creat_openamp_thread);

#ifdef FINSH_USING_MSH

static int console(int argc, char **argv)
{
    rt_err_t result = RT_EOK;
    
    if (argc > 1)
    {
        if (!strcmp(argv[1], "set"))
        {
            rt_kprintf("console change to %s\n", argv[2]);
            rt_console_set_device(argv[2]);
            finsh_set_device(argv[2]);
        }
        else
        {
            rt_kprintf("Unknown command. Please enter 'console' for help\n");
            result = -RT_ERROR;
        }
    }
    else
    {
        rt_kprintf("Usage: \n");
        rt_kprintf("console set <name>   - change console by name\n");
        result = -RT_ERROR;
    }
    return result;
}
MSH_CMD_EXPORT(console, set console name);

#endif /* FINSH_USING_MSH */

#endif
