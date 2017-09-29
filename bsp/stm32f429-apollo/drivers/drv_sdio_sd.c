#include "drv_sdio_sd.h"
#include "string.h"
#include <rtthread.h>
#include <dfs_fs.h>

SD_HandleTypeDef        SDCARD_Handler;     
HAL_SD_CardInfoTypedef  SDCardInfo;         //SD卡信息结构体
DMA_HandleTypeDef SDTxDMAHandler,SDRxDMAHandler;    //SD卡DMA发送和接收句柄


//SD卡初始化
//返回值:0 初始化正确；其他值，初始化错误
rt_uint8_t SD_Init(void)
{
    rt_uint8_t SD_Error;
    
    //初始化时的时钟不能大于400KHZ 
    SDCARD_Handler.Instance=SDIO;
    SDCARD_Handler.Init.ClockEdge=SDIO_CLOCK_EDGE_RISING;          //上升沿     
    SDCARD_Handler.Init.ClockBypass=SDIO_CLOCK_BYPASS_DISABLE;     //不使用bypass模式，直接用HCLK进行分频得到SDIO_CK
    SDCARD_Handler.Init.ClockPowerSave=SDIO_CLOCK_POWER_SAVE_DISABLE;    //空闲时不关闭时钟电源
    SDCARD_Handler.Init.BusWide=SDIO_BUS_WIDE_1B;                        //1位数据线
    SDCARD_Handler.Init.HardwareFlowControl=SDIO_HARDWARE_FLOW_CONTROL_DISABLE;//关闭硬件流控
    SDCARD_Handler.Init.ClockDiv=SDIO_TRANSFER_CLK_DIV;            //SD传输时钟频率最大25MHZ
    
    SD_Error=HAL_SD_Init(&SDCARD_Handler,&SDCardInfo);
    if(SD_Error!=SD_OK) return 1;
    
    SD_Error=HAL_SD_WideBusOperation_Config(&SDCARD_Handler,SDIO_BUS_WIDE_4B);//使能宽总线模式
    if(SD_Error!=SD_OK) return 2;
    return 0;
}

//SDMMC底层驱动，时钟使能，引脚配置，DMA配置
//此函数会被HAL_SD_Init()调用
//hsd:SD卡句柄
void HAL_SD_MspInit(SD_HandleTypeDef *hsd)
{
    DMA_HandleTypeDef TxDMAHandler,RxDMAHandler;
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_SDIO_CLK_ENABLE();    //使能SDIO时钟
    __HAL_RCC_DMA2_CLK_ENABLE();    //使能DMA2时钟 
    __HAL_RCC_GPIOC_CLK_ENABLE();   //使能GPIOC时钟
    __HAL_RCC_GPIOD_CLK_ENABLE();   //使能GPIOD时钟
    
    //PC8,9,10,11,12
    GPIO_Initure.Pin=GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;      //推挽复用
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    GPIO_Initure.Alternate=GPIO_AF12_SDIO;  //复用为SDIO
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);     //初始化
    
    //PD2
    GPIO_Initure.Pin=GPIO_PIN_2;            
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);     //初始化

#if (SD_DMA_MODE==1)                        //使用DMA模式
    HAL_NVIC_SetPriority(SDMMC1_IRQn,2,0);  //配置SDMMC1中断，抢占优先级2，子优先级0
    HAL_NVIC_EnableIRQ(SDMMC1_IRQn);        //使能SDMMC1中断
    
    //配置发送DMA
    SDRxDMAHandler.Instance=DMA2_Stream3;
    SDRxDMAHandler.Init.Channel=DMA_CHANNEL_4;
    SDRxDMAHandler.Init.Direction=DMA_PERIPH_TO_MEMORY;
    SDRxDMAHandler.Init.PeriphInc=DMA_PINC_DISABLE;
    SDRxDMAHandler.Init.MemInc=DMA_MINC_ENABLE;
    SDRxDMAHandler.Init.PeriphDataAlignment=DMA_PDATAALIGN_WORD;
    SDRxDMAHandler.Init.MemDataAlignment=DMA_MDATAALIGN_WORD;
    SDRxDMAHandler.Init.Mode=DMA_PFCTRL;
    SDRxDMAHandler.Init.Priority=DMA_PRIORITY_VERY_HIGH;
    SDRxDMAHandler.Init.FIFOMode=DMA_FIFOMODE_ENABLE;
    SDRxDMAHandler.Init.FIFOThreshold=DMA_FIFO_THRESHOLD_FULL;
    SDRxDMAHandler.Init.MemBurst=DMA_MBURST_INC4;
    SDRxDMAHandler.Init.PeriphBurst=DMA_PBURST_INC4;

    __HAL_LINKDMA(hsd, hdmarx, SDRxDMAHandler); //将接收DMA和SD卡的发送DMA连接起来
    HAL_DMA_DeInit(&SDRxDMAHandler);
    HAL_DMA_Init(&SDRxDMAHandler);              //初始化接收DMA
    
    //配置接收DMA 
    SDTxDMAHandler.Instance=DMA2_Stream6;
    SDTxDMAHandler.Init.Channel=DMA_CHANNEL_4;
    SDTxDMAHandler.Init.Direction=DMA_MEMORY_TO_PERIPH;
    SDTxDMAHandler.Init.PeriphInc=DMA_PINC_DISABLE;
    SDTxDMAHandler.Init.MemInc=DMA_MINC_ENABLE;
    SDTxDMAHandler.Init.PeriphDataAlignment=DMA_PDATAALIGN_WORD;
    SDTxDMAHandler.Init.MemDataAlignment=DMA_MDATAALIGN_WORD;
    SDTxDMAHandler.Init.Mode=DMA_PFCTRL;
    SDTxDMAHandler.Init.Priority=DMA_PRIORITY_VERY_HIGH;
    SDTxDMAHandler.Init.FIFOMode=DMA_FIFOMODE_ENABLE;
    SDTxDMAHandler.Init.FIFOThreshold=DMA_FIFO_THRESHOLD_FULL;
    SDTxDMAHandler.Init.MemBurst=DMA_MBURST_INC4;
    SDTxDMAHandler.Init.PeriphBurst=DMA_PBURST_INC4;
    
    __HAL_LINKDMA(hsd, hdmatx, SDTxDMAHandler);//将发送DMA和SD卡的发送DMA连接起来
    HAL_DMA_DeInit(&SDTxDMAHandler);
    HAL_DMA_Init(&SDTxDMAHandler);              //初始化发送DMA 
  

    HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 3, 0);  //接收DMA中断优先级
    HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
    HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 3, 0);  //发送DMA中断优先级
    HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);
#endif
}

//得到卡信息
//cardinfo:卡信息存储区
//返回值:错误状态
rt_uint8_t SD_GetCardInfo(HAL_SD_CardInfoTypedef *cardinfo)
{
    rt_uint8_t sta;
    sta=HAL_SD_Get_CardInfo(&SDCARD_Handler,cardinfo);
    return sta;
}
 #if (SD_DMA_MODE==1)        //DMA模式

//通过DMA读取SD卡一个扇区
//buf:读数据缓存区
//sector:扇区地址
//blocksize:扇区大小(一般都是512字节)
//cnt:扇区个数	
//返回值:错误状态;0,正常;其他,错误代码;
rt_uint8_t SD_ReadBlocks_DMA(uint32_t *buf,uint64_t sector ,uint32_t cnt)
{
    rt_uint8_t err=SD_OK;
    err=HAL_SD_ReadBlocks_DMA(&SDCARD_Handler,buf,sector,SECTOR_SIZE,cnt);//通过DMA读取SD卡一个扇区
    if(err==SD_OK)//读取成功
    {
        //等待读取完成
        err=HAL_SD_CheckReadOperation(&SDCARD_Handler,(uint32_t)SD_TIMEOUT);
    }

    return err;
}

//写SD卡
//buf:写数据缓存区
//sector:扇区地址
//blocksize:扇区大小(一般都是512字节)
//cnt:扇区个数	
//返回值:错误状态;0,正常;其他,错误代码;	
rt_uint8_t SD_WriteBlocks_DMA(uint32_t *buf,uint64_t sector,uint32_t cnt)
{
    rt_uint8_t err=SD_OK; 
    err=HAL_SD_WriteBlocks_DMA(&SDCARD_Handler,buf,sector,SECTOR_SIZE,cnt);//通过DMA写SD卡一个扇区
    if(err==SD_OK)//写成功
    {     
       err=HAL_SD_CheckWriteOperation(&SDCARD_Handler,(uint32_t)SD_TIMEOUT);//等待读取完成/
    }
    return err;
}


//SDMMC1中断服务函数
void SDMMC1_IRQHandler(void)
{
    HAL_SD_IRQHandler(&SDCARD_Handler);
}

//DMA2数据流6中断服务函数
void DMA2_Stream6_IRQHandler(void)
{
    HAL_DMA_IRQHandler(SDCARD_Handler.hdmatx);
}

//DMA2数据流3中断服务函数
void DMA2_Stream3_IRQHandler(void)
{
    HAL_DMA_IRQHandler(SDCARD_Handler.hdmarx);
}
#else                                   //轮训模式
 
//读取SD卡扇区
//buf:读数据缓存区
//sector:扇区地址
//cnt:扇区个数	
//返回值:错误状态;0,正常;其他,错误代码;
rt_uint8_t SD_ReadBlocks(uint32_t *buf,uint64_t sector ,uint32_t cnt)
{
    rt_uint8_t err=SD_OK;
    err=HAL_SD_ReadBlocks(&SDCARD_Handler,buf,sector,SECTOR_SIZE,cnt);//通过DMA读取SD卡一个扇区
    return err;
}

//写SD扇区
//buf:写数据缓存区
//sector:扇区地址
//cnt:扇区个数	
//返回值:错误状态;0,正常;其他,错误代码;	
rt_uint8_t SD_WriteBlocks(uint32_t *buf,uint64_t sector,uint32_t cnt)
{
    return HAL_SD_WriteBlocks(&SDCARD_Handler,buf,sector,SECTOR_SIZE,cnt);
}
#endif

/*
 * RT-Thread SD Card Driver
 * 20100715 Bernard support SDHC card great than 4G.
 * 20110905 JoyChen support to STM32F2xx
 */




static struct rt_device sdcard_device;
static struct rt_semaphore sd_lock;

/* RT-Thread Device Driver Interface */
static rt_err_t rt_sdcard_init(rt_device_t dev)
{
	if (rt_sem_init(&sd_lock, "sdlock", 1, RT_IPC_FLAG_FIFO) != RT_EOK)
	{
		rt_kprintf("init sd lock semaphore failed\n");
	}
	else
		rt_kprintf("SD Card init OK\n");

	return RT_EOK;
}

static rt_err_t rt_sdcard_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_sdcard_close(rt_device_t dev)
{
	return RT_EOK;
}

static uint32_t sdio_buffer[512/sizeof(uint32_t)];
static rt_size_t rt_sdcard_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_uint8_t status = SD_OK;

	rt_sem_take(&sd_lock, RT_WAITING_FOREVER);

    if(((uint32_t)buffer & 0x03) != 0)
    {
        /* non-aligned. */
        uint32_t i;
        uint64_t sector_adr;
        uint8_t* copy_buffer;

        sector_adr = (uint64_t)pos*SECTOR_SIZE;
        copy_buffer = (uint8_t*)buffer;

        for(i=0; i<size; i++)
        {
            #if (SD_DMA_MODE==1)   
            status=SD_ReadBlocks_DMA(sdio_buffer,sector_adr,1);//通过DMA写SD卡一个扇区
            #else
            status=SD_ReadBlocks(sdio_buffer,sector_adr,1);
            #endif
            memcpy(copy_buffer, sdio_buffer, SECTOR_SIZE);
            sector_adr += SECTOR_SIZE;
            copy_buffer += SECTOR_SIZE;
        }
    }
    else
    {
        #if (SD_DMA_MODE==1) 
        status=SD_ReadBlocks_DMA(buffer,(uint64_t)pos*SECTOR_SIZE,size);//通过DMA写SD卡一个扇区
        #else
        SD_ReadBlocks(buffer,(uint64_t)pos*SECTOR_SIZE,size);
        #endif
    }


	rt_sem_release(&sd_lock);
	if (status == SD_OK) return size;

	rt_kprintf("read failed: %d, buffer 0x%08x\n", status, buffer);
	return 0;
}

static rt_size_t rt_sdcard_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_uint8_t status = SD_OK;
	rt_sem_take(&sd_lock, RT_WAITING_FOREVER);

    if(((uint32_t)buffer & 0x03) != 0)
    {
        /* non-aligned. */
        uint32_t i;
        uint64_t sector_adr;
        uint8_t* copy_buffer;

        sector_adr = (uint64_t)pos*SECTOR_SIZE;
        copy_buffer = (uint8_t*)buffer;

        for(i=0; i<size; i++)
        {
            memcpy(sdio_buffer, copy_buffer, SECTOR_SIZE);
            #if (SD_DMA_MODE==1)    
            status=SD_WriteBlocks_DMA((uint32_t*)sdio_buffer,sector_adr,1);
            #else
            status=SD_WriteBlocks((uint32_t*)sdio_buffer,sector_adr,1);
            #endif
            sector_adr += SECTOR_SIZE;
            copy_buffer += SECTOR_SIZE;
            
        }
    }
    else
    {
        #if (SD_DMA_MODE==1)   
        status=SD_WriteBlocks_DMA((uint32_t*)buffer,(uint64_t)pos*SECTOR_SIZE,size);
        #else
        status=SD_WriteBlocks((uint32_t*)buffer,(uint64_t)pos*SECTOR_SIZE,size);
        #endif
    }
	// }
	rt_sem_release(&sd_lock);
	if (status == SD_OK) return size;
	rt_kprintf("write failed: %d, buffer 0x%08x\n", status, buffer);
	return 0;
}

static rt_err_t rt_sdcard_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL) return -RT_ERROR;

        geometry->bytes_per_sector = 512;
        geometry->block_size = SDCardInfo.CardBlockSize;
		geometry->sector_count = SDCardInfo.CardCapacity/SDCardInfo.CardBlockSize;
    }

	return RT_EOK;
}

static int rt_hw_sdcard_init(void)
{
	if (SD_Init() == SD_OK)
	{
		/* register sdcard device */
		sdcard_device.type  = RT_Device_Class_Block;
		sdcard_device.init 	= rt_sdcard_init;
		sdcard_device.open 	= rt_sdcard_open;
		sdcard_device.close = rt_sdcard_close;
		sdcard_device.read 	= rt_sdcard_read;
		sdcard_device.write = rt_sdcard_write;
		sdcard_device.control = rt_sdcard_control;

		/* no private */
		sdcard_device.user_data = &SDCardInfo;

		rt_device_register(&sdcard_device, "sd0",
			RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

		return RT_EOK;
	}
	rt_kprintf("sdcard init failed\n");
    return RT_ERROR;
}
INIT_BOARD_EXPORT(rt_hw_sdcard_init);
