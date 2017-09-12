

#include "drv_sdio_sd.h"
#include "string.h"
#include <rtthread.h>

#define SD_TIMEOUT              (1000000U)
#define SECTOR_SIZE		        512
//#define SD_DMA_MODE    		    1

#define DEBUG

#ifdef RT_USING_DFS
#include <dfs_fs.h>

static SD_HandleTypeDef hsd;
static HAL_SD_CardInfoTypedef  sdcard_info;
static rt_uint32_t _sdcard_buffer[SECTOR_SIZE / sizeof(rt_uint32_t)];
static struct rt_device sdcard_device;
static struct rt_semaphore sd_lock;

#ifdef SD_DMA_MODE
static DMA_HandleTypeDef SDTxDMAHandler,SDRxDMAHandler;
#endif

#ifdef DEBUG
#define DEBUG_PRINTF(...)       rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)   
#endif

rt_err_t sdio_sd_init(void)
{    
    hsd.Instance = SDIO;
    hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
    hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
    hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
    hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
    hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
    hsd.Init.ClockDiv = SDIO_INIT_CLK_DIV;
    
    if (HAL_SD_Init(&hsd, &sdcard_info) != HAL_OK)
        return RT_ERROR;
    
    if(HAL_SD_WideBusOperation_Config(&hsd, SDIO_BUS_WIDE_4B) != HAL_OK) 
        return RT_ERROR;
    
    return RT_EOK;
}

void HAL_SD_MspInit(SD_HandleTypeDef *hsd)
{
    DMA_HandleTypeDef TxDMAHandler,RxDMAHandler;
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_SDIO_CLK_ENABLE();
#if (SD_DMA_MODE == 1)
    __HAL_RCC_DMA2_CLK_ENABLE();
#endif
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    
    //PC8,9,10,11,12
    GPIO_Initure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;
    GPIO_Initure.Alternate = GPIO_AF12_SDIO;
    HAL_GPIO_Init(GPIOC, &GPIO_Initure);
    
    //PD2
    GPIO_Initure.Pin = GPIO_PIN_2;            
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);

#if (SD_DMA_MODE==1)                        //使用DMA模式
    HAL_NVIC_SetPriority(SDMMC1_IRQn,2,0);  //配置SDMMC1中断，抢占优先级2，子优先级0
    HAL_NVIC_EnableIRQ(SDMMC1_IRQn);        //使能SDMMC1中断
    
    //配置发送DMA
    SDRxDMAHandler.Instance = DMA2_Stream3;
    SDRxDMAHandler.Init.Channel = DMA_CHANNEL_4;
    SDRxDMAHandler.Init.Direction = DMA_PERIPH_TO_MEMORY;
    SDRxDMAHandler.Init.PeriphInc = DMA_PINC_DISABLE;
    SDRxDMAHandler.Init.MemInc = DMA_MINC_ENABLE;
    SDRxDMAHandler.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    SDRxDMAHandler.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    SDRxDMAHandler.Init.Mode = DMA_PFCTRL;
    SDRxDMAHandler.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    SDRxDMAHandler.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    SDRxDMAHandler.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    SDRxDMAHandler.Init.MemBurst = DMA_MBURST_INC4;
    SDRxDMAHandler.Init.PeriphBurst = DMA_PBURST_INC4;

    __HAL_LINKDMA(hsd, hdmarx, SDRxDMAHandler); //将接收DMA和SD卡的发送DMA连接起来
    HAL_DMA_DeInit(&SDRxDMAHandler);
    HAL_DMA_Init(&SDRxDMAHandler);              //初始化接收DMA
    
    //配置接收DMA 
    SDTxDMAHandler.Instance = DMA2_Stream6;
    SDTxDMAHandler.Init.Channel = DMA_CHANNEL_4;
    SDTxDMAHandler.Init.Direction = DMA_MEMORY_TO_PERIPH;
    SDTxDMAHandler.Init.PeriphInc = DMA_PINC_DISABLE;
    SDTxDMAHandler.Init.MemInc = DMA_MINC_ENABLE;
    SDTxDMAHandler.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    SDTxDMAHandler.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    SDTxDMAHandler.Init.Mode = DMA_PFCTRL;
    SDTxDMAHandler.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    SDTxDMAHandler.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    SDTxDMAHandler.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    SDTxDMAHandler.Init.MemBurst = DMA_MBURST_INC4;
    SDTxDMAHandler.Init.PeriphBurst = DMA_PBURST_INC4;
    
    __HAL_LINKDMA(hsd, hdmatx, SDTxDMAHandler);//将发送DMA和SD卡的发送DMA连接起来
    HAL_DMA_DeInit(&SDTxDMAHandler);
    HAL_DMA_Init(&SDTxDMAHandler);              //初始化发送DMA 
  

    HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 3, 0);  //接收DMA中断优先级
    HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
    HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 3, 0);  //发送DMA中断优先级
    HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);
#endif
}

rt_uint8_t SD_GetCardInfo(HAL_SD_CardInfoTypedef *cardinfo)
{
    return HAL_SD_Get_CardInfo(&hsd, cardinfo);
}

 #if (SD_DMA_MODE==1)

HAL_SD_ErrorTypedef SD_ReadBlocks(void* buf,uint64_t sector ,uint32_t cnt)
{
    HAL_SD_ErrorTypedef err;
    
    err = HAL_SD_ReadBlocks_DMA(&hsd, buf, sector, SECTOR_SIZE, cnt);
    if(err != SD_OK)
    {
        DEBUG_PRINTF("err: %d\n", err);
        return err;
    }

    return HAL_SD_CheckReadOperation(&hsd, (uint32_t)SD_TIMEOUT);
}

HAL_SD_ErrorTypedef SD_WriteBlocks(const void* buf,uint64_t sector,uint32_t cnt)
{
    HAL_SD_ErrorTypedef err; 
    
    err = HAL_SD_WriteBlocks_DMA(&hsd, (uint32_t *)buf, sector, SECTOR_SIZE, cnt);
    if(err != SD_OK)
    {
		DEBUG_PRINTF("err: %d\n", err);
        return err;
    }
    
    return HAL_SD_CheckWriteOperation(&hsd, (uint32_t)SD_TIMEOUT);
}

void SDMMC1_IRQHandler(void)
{
    HAL_SD_IRQHandler(&hsd);
}

void DMA2_Stream6_IRQHandler(void)
{
    HAL_DMA_IRQHandler(hsd.hdmatx);
}

void DMA2_Stream3_IRQHandler(void)
{
    HAL_DMA_IRQHandler(hsd.hdmarx);
}
#else
 
HAL_SD_ErrorTypedef SD_ReadBlocks(void* buf, uint64_t sector, uint32_t cnt)
{
    return HAL_SD_ReadBlocks(&hsd, (uint32_t * )buf, sector, SECTOR_SIZE, cnt);
}

HAL_SD_ErrorTypedef SD_WriteBlocks(const void* buf, uint64_t sector, uint32_t cnt)
{
    return HAL_SD_WriteBlocks(&hsd, (uint32_t * )buf, sector, SECTOR_SIZE, cnt);
}
#endif

static rt_err_t rt_sdcard_init(rt_device_t dev)
{
	if (rt_sem_init(&sd_lock, "sdlock", 1, RT_IPC_FLAG_FIFO) != RT_EOK)
	{
		DEBUG_PRINTF("init sd lock semaphore failed\n");
        return RT_ERROR;
	}
	else
    {
		DEBUG_PRINTF("SD Card init OK\n");
        return RT_EOK;
    }
}

static rt_err_t rt_sdcard_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_sdcard_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_sdcard_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	HAL_SD_ErrorTypedef status = SD_OK;
	rt_uint32_t retry;
   
	rt_sem_take(&sd_lock, RT_WAITING_FOREVER);

    retry = 3;
    while(retry)
    {
        /* read all sectors */
        if ((rt_uint32_t)buffer % 4 != 0)
        {
            rt_uint32_t index;

            /* which is not alignment with 4 or chip SRAM */
            for (index = 0; index < size; index++)
            {
                status = SD_ReadBlocks(buffer, (uint64_t)pos * SECTOR_SIZE, 1);
				if (status != HAL_OK) 
                    break;

                /* copy to the buffer */
                rt_memcpy(((rt_uint8_t*)buffer + index * SECTOR_SIZE), _sdcard_buffer, SECTOR_SIZE);
            }
        }
        else
        {
            status = SD_ReadBlocks(buffer, (uint64_t)pos*SECTOR_SIZE, size);
        }

        if (status == HAL_OK) 
            break;

        retry --;
    }
    
	rt_sem_release(&sd_lock);
    
	if (status == HAL_OK) 
    {
        return size;
    }
    else
    {
        DEBUG_PRINTF("rt_sdcard_read, ");
        DEBUG_PRINTF("dev: %08X, pos: %d, ", (uint32_t)dev, pos);
        DEBUG_PRINTF("buffer: 0x%08X, size: %d\n", buffer, size);
        DEBUG_PRINTF("read failed: status/%d, buffer 0x%08x\n", status, buffer);   
        return 0;
    }
}

static rt_size_t rt_sdcard_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	HAL_SD_ErrorTypedef status = SD_OK;
	rt_uint32_t retry;
    static rt_uint32_t count = 0;

    RT_ASSERT(((uint32_t)buffer & 0x3) == 0x0);     //align to 4 bytes;
   
	rt_sem_take(&sd_lock, RT_WAITING_FOREVER);

    retry = 3;
    while(retry)
    {
        /* read all sectors */
        if ((rt_uint32_t)buffer % 4 != 0)
        {
            rt_uint32_t index;

            /* which is not alignment with 4 or chip SRAM */
            for (index = 0; index < size; index++)
            {
                /* copy to the buffer */
                rt_memcpy(((rt_uint8_t*)buffer + index * SECTOR_SIZE), _sdcard_buffer, SECTOR_SIZE); 
                status = SD_WriteBlocks(buffer, (uint64_t)pos * SECTOR_SIZE, 1);
				if (status != HAL_OK) 
                    break;
            }
        }
        else
        {
            status = SD_WriteBlocks(buffer, (uint64_t)pos*SECTOR_SIZE, size);
        }

        if (status == HAL_OK) 
            break;

        retry --;
    }
    
	rt_sem_release(&sd_lock);
    
	if (status == HAL_OK) 
    {
        return size;
    }
    else
    {
        DEBUG_PRINTF("rt_sdcard_write: %d, ", count);
        DEBUG_PRINTF("dev: %08X, pos: %d, ", (uint32_t)dev, pos);
        DEBUG_PRINTF("buffer: 0x%08X, size: %d\n",  (uint32_t)buffer, size);
        DEBUG_PRINTF("write failed: status/%d, buffer 0x%08x\n", status, buffer);
        return 0;
    }
}

static rt_err_t rt_sdcard_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry = (struct rt_device_blk_geometry *)args;

        if (geometry == RT_NULL) 
            return -RT_ERROR;

        geometry->bytes_per_sector = sdcard_info.CardBlockSize;
        geometry->block_size       = sdcard_info.CardBlockSize;
		geometry->sector_count     = sdcard_info.CardCapacity / sdcard_info.CardBlockSize;
    }

	return RT_EOK;
}

static int rt_hw_sdcard_init(void)
{
	if (sdio_sd_init() != RT_EOK)
	{
        DEBUG_PRINTF("sdcard init failed\n");
        return RT_ERROR;
    }
    
    /* register sdcard device */
    sdcard_device.type  = RT_Device_Class_Block;
    sdcard_device.init 	= rt_sdcard_init;
    sdcard_device.open 	= rt_sdcard_open;
    sdcard_device.close = rt_sdcard_close;
    sdcard_device.read 	= rt_sdcard_read;
    sdcard_device.write = rt_sdcard_write;
    sdcard_device.control = rt_sdcard_control;

    rt_device_register(&sdcard_device, "sd0",
        RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_sdcard_init);
#endif
