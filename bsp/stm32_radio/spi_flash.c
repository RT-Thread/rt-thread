#include <stm32f10x.h>
#include "board.h"
#include "spi_flash.h"
#include "rtthread.h"

/*
 * WARNING: !!! ENABLING DMA MODE MAY DESTROY YOUR DATA IN THE SPI FLASH !!!
 * Don't set SPI_FLASH_USE_DMA to 1 unless you know what you're doing!
 * However, readonly access is just fine. :)
 */
#define SPI_FLASH_USE_DMA	0
#define SECTOR_SIZE			512

extern uint8_t SPI_WriteByte(unsigned char data);

#if SPI_FLASH_USE_DMA
static uint8_t dummy = 0;
static uint8_t _spi_flash_buffer[SECTOR_SIZE];
#endif

/********************** hardware *************************************/
/* SPI_FLASH_CS   PA4 */
/* SPI_FLASH_RST  PA3 */
#define FLASH_RST_0()    GPIO_ResetBits(GPIOA,GPIO_Pin_3)
#define FLASH_RST_1()    GPIO_SetBits(GPIOA,GPIO_Pin_3)

#define FLASH_CS_0()     GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define FLASH_CS_1()     GPIO_SetBits(GPIOA,GPIO_Pin_4)
/********************** hardware *************************************/

static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    FLASH_RST_0(); // RESET
    FLASH_CS_1();
    FLASH_RST_1();
}

#if SPI_FLASH_USE_DMA
static void DMA_RxConfiguration(rt_uint32_t addr, rt_size_t size)
{
    DMA_InitTypeDef DMA_InitStructure;

    DMA_ClearFlag(DMA1_FLAG_TC2 | DMA1_FLAG_TE2 | DMA1_FLAG_TC3 | DMA1_FLAG_TE3);
    dummy = 0;

	/* DMA Channel configuration ----------------------------------------------*/
	DMA_Cmd(DMA1_Channel2, DISABLE);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&(SPI1->DR));
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32) addr;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = size;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);

	DMA_Cmd(DMA1_Channel2, ENABLE);

	/* Dummy TX channel configuration */
	DMA_Cmd(DMA1_Channel3, DISABLE);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&(SPI1->DR));
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)(&dummy);
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = size;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel3, &DMA_InitStructure);

	DMA_Cmd(DMA1_Channel3, ENABLE);
}
#endif

static uint8_t SPI_HostReadByte(void)
{
    //return SPI_WriteByte(0x00);
    //Wait until the transmit buffer is empty
    //while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while( (SPI1->SR & SPI_I2S_FLAG_TXE) == RESET);
    // Send the byte
    SPI_I2S_SendData(SPI1, 0);

    //Wait until a data is received
    //while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    while( (SPI1->SR & SPI_I2S_FLAG_RXNE) == RESET);
    // Get the received data
    return SPI_I2S_ReceiveData(SPI1);

}

static void SPI_HostWriteByte(uint8_t wByte)
{
    SPI_WriteByte(wByte);
}

/*****************************************************************************/
/*Status Register Format:                                   */
/* ------------------------------------------------------------------------- */
/* | bit7   | bit6   | bit5   | bit4   | bit3   | bit2   | bit1   | bit0   | */
/* |--------|--------|--------|--------|--------|--------|--------|--------| */
/* |RDY/BUSY| COMP   |         device density            |   X    |   X    | */
/* ------------------------------------------------------------------------- */
/* 0:busy   |        |        AT45DB041:0111             | protect|page size */
/* 1:ready  |        |        AT45DB161:1011             |                   */
/* --------------------------------------------------------------------------*/
/*****************************************************************************/
static uint8_t AT45DB_StatusRegisterRead(void)
{
    uint8_t i;

    FLASH_CS_0();
    SPI_HostWriteByte(AT45DB_READ_STATE_REGISTER);
    i = SPI_HostReadByte();
    FLASH_CS_1();

    return i;
}

static void wait_busy(void)
{
    uint16_t i = 0;
    while (i++ < 10000)
    {
        if (AT45DB_StatusRegisterRead() & 0x80)
        {
            return;
        }
    }
    rt_kprintf("\r\nSPI_FLASH timeout!!!\r\n");
}

static void read_page(uint32_t page, uint8_t *pHeader)
{
#if SPI_FLASH_USE_DMA
    rt_sem_take(&spi1_lock, RT_WAITING_FOREVER);

	DMA_RxConfiguration((rt_uint32_t) pHeader, SECTOR_SIZE);

    FLASH_CS_0();

    SPI_HostWriteByte(AT45DB_MM_PAGE_READ);
    SPI_HostWriteByte((uint8_t)(page >> 6));
    SPI_HostWriteByte((uint8_t)(page << 2));
    SPI_HostWriteByte(0x00);

    // 4 don't care bytes
    SPI_HostWriteByte(0x00);
    SPI_HostWriteByte(0x00);
    SPI_HostWriteByte(0x00);
    SPI_HostWriteByte(0x00);

	SPI_I2S_ClearFlag(SPI1, SPI_I2S_FLAG_RXNE);
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx | SPI_I2S_DMAReq_Rx, ENABLE);
	while (DMA_GetFlagStatus(DMA1_FLAG_TC2) == RESET);

	FLASH_CS_1();

	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx | SPI_I2S_DMAReq_Rx, DISABLE);

	rt_sem_release(&spi1_lock);
#else
    uint16_t i;

    rt_sem_take(&spi1_lock, RT_WAITING_FOREVER);

    FLASH_CS_0();

    SPI_HostWriteByte(AT45DB_MM_PAGE_READ);
    SPI_HostWriteByte((uint8_t)(page >> 6));
    SPI_HostWriteByte((uint8_t)(page << 2));
    SPI_HostWriteByte(0x00);

    // 4 don't care bytes
    SPI_HostWriteByte(0x00);
    SPI_HostWriteByte(0x00);
    SPI_HostWriteByte(0x00);
    SPI_HostWriteByte(0x00);

	for (i = 0; i < SECTOR_SIZE; i++)
	{
		*pHeader++ = SPI_HostReadByte();
	}

	FLASH_CS_1();

    rt_sem_release(&spi1_lock);
#endif
}

static void write_page(uint32_t page, uint8_t *pHeader)
{
    uint16_t i;

    rt_sem_take(&spi1_lock, RT_WAITING_FOREVER);

    FLASH_CS_0();

    SPI_HostWriteByte(AT45DB_MM_PAGE_PROG_THRU_BUFFER1);
    SPI_HostWriteByte((uint8_t) (page >> 6));
    SPI_HostWriteByte((uint8_t) (page << 2));
    SPI_HostWriteByte(0x00);

    for (i = 0; i < SECTOR_SIZE; i++)
    {
        SPI_HostWriteByte(*pHeader++);
    }

    FLASH_CS_1();

    wait_busy();

    rt_sem_release(&spi1_lock);
}


#include <rtthread.h>
/* SPI DEVICE */
static struct rt_device spi_flash_device;

/* RT-Thread Device Driver Interface */
static rt_err_t rt_spi_flash_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_spi_flash_open(rt_device_t dev, rt_uint16_t oflag)
{

    return RT_EOK;
}

static rt_err_t rt_spi_flash_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_spi_flash_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    return RT_EOK;
}

static rt_size_t rt_spi_flash_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_uint32_t index, nr;

    nr = size / SECTOR_SIZE;

    for (index = 0; index < nr; index++)
    {
        /* only supply single block read: block size 512Byte */
#if SPI_FLASH_USE_DMA
        read_page((pos / SECTOR_SIZE + index), _spi_flash_buffer);
    	rt_memcpy(((rt_uint8_t *) buffer + index * SECTOR_SIZE), _spi_flash_buffer, SECTOR_SIZE);
#else
        read_page((pos / SECTOR_SIZE + index), ((rt_uint8_t *) buffer + index * SECTOR_SIZE));
#endif
    }

    return nr * SECTOR_SIZE;
}

static rt_size_t rt_spi_flash_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_uint32_t index, nr;

    nr = size / SECTOR_SIZE;

    for (index = 0; index < nr; index++)
    {
        /* only supply single block write: block size 512Byte */
        write_page((pos / SECTOR_SIZE + index), ((rt_uint8_t *) buffer + index * SECTOR_SIZE));
    }

    return nr * SECTOR_SIZE;
}

void rt_hw_spi_flash_init(void)
{
    GPIO_Configuration();

#if SPI_FLASH_USE_DMA
    /* Enable the DMA1 Clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
#endif

    /* register spi_flash device */
    spi_flash_device.type    = RT_Device_Class_Block;
    spi_flash_device.init    = rt_spi_flash_init;
    spi_flash_device.open    = rt_spi_flash_open;
    spi_flash_device.close   = rt_spi_flash_close;
    spi_flash_device.read 	 = rt_spi_flash_read;
    spi_flash_device.write   = rt_spi_flash_write;
    spi_flash_device.control = rt_spi_flash_control;

    /* no private */
    spi_flash_device.private = RT_NULL;

    rt_device_register(&spi_flash_device, "spi0",
                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
}
