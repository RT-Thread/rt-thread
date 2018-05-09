#include "FM25Lx.h"
#include "rtthread.h"
#include "stm32f2xx_rcc.h"
#include <stm32f2xx.h>

#define FLASH_TRACE(...)
//#define FLASH_TRACE  rt_kprintf

#define CS_LOW()      GPIO_ResetBits(FM25_SPI_NSS_GPIO, FM25_SPI_NSS_PIN)
#define CS_HIGH()     GPIO_SetBits(FM25_SPI_NSS_GPIO, FM25_SPI_NSS_PIN)
#define spi_config()  rt_hw_spi2_baud_rate(SPI_BaudRatePrescaler_4);/* 72M/4=18M */

#define fram_lock()    rt_sem_take(fram_lock, RT_WAITING_FOREVER);
#define fram_unlock()  rt_sem_release(fram_lock);

static uint32_t spi_timeout_cnt = 0;

rt_sem_t fram_lock;

void rt_hw_spi2_baud_rate(uint16_t SPI_BaudRatePrescaler)
{
    SPI2->CR1 &= ~SPI_BaudRatePrescaler_256;
    SPI2->CR1 |= SPI_BaudRatePrescaler;
}

/* FM25L256 using SPI2 */
void fm25_spi_cfg()
{
	GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStructure;

    /* Enable SPI Periph clock */
    RCC_AHB1PeriphClockCmd(FM25_SPI_NSS_GPIO_CLK | FM25_SPI_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(FM25_SPI_CLK, ENABLE); //enable SPI clock

    //Setup GPIO
    GPIO_InitStructure.GPIO_Pin = FM25_SPI_SCK | FM25_SPI_MISO | FM25_SPI_MOSI;

   	/*Connect Pin to AF*/
	GPIO_PinAFConfig(FM25_SPI_GPIO, GPIO_PinSource3, GPIO_AF_SPI3);
	GPIO_PinAFConfig(FM25_SPI_GPIO, GPIO_PinSource4, GPIO_AF_SPI3);
	GPIO_PinAFConfig(FM25_SPI_GPIO, GPIO_PinSource5, GPIO_AF_SPI3);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(FM25_SPI_GPIO, &GPIO_InitStructure);

	/* CS pin: PB12 */
    GPIO_InitStructure.GPIO_Pin   = FM25_SPI_NSS_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(FM25_SPI_NSS_GPIO, &GPIO_InitStructure);
	CS_HIGH();

	SPI_Cmd(FM25_SPI, DISABLE);
    /*------------------------ SPI configuration ------------------------*/
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//SPI_Direction_1Line_Tx;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS  = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;/* 72M/64=1.125M */
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;

    //SPI_I2S_DeInit(FM25_SPI);
    SPI_Init(FM25_SPI, &SPI_InitStructure);

    /* Enable SPI_MASTER */
    SPI_Cmd(FM25_SPI, ENABLE);
    //SPI_CalculateCRC(FM25_SPI, DISABLE);

	fram_lock = rt_sem_create("framlock", 1, RT_IPC_FLAG_FIFO);
}
static uint8_t spi_readwrite(uint8_t data)
{
    int32_t timeout = 0xFFFFF;
	//rt_kprintf("State 0x%X\n", SPI_I2S_GetFlagStatus(FM25_SPI, SPI_I2S_FLAG_TXE));
	//Wait until the transmit buffer is empty
    while (SPI_I2S_GetFlagStatus(FM25_SPI, SPI_I2S_FLAG_TXE) == RESET && --timeout >0);

	if( timeout <= 0 ){ spi_timeout_cnt++; return 0;}
    // Send the byte
    SPI_I2S_SendData(FM25_SPI, data);

	timeout = 0xFFFFF;
    //Wait until a data is received
    while (SPI_I2S_GetFlagStatus(FM25_SPI, SPI_I2S_FLAG_RXNE) == RESET && --timeout >0);
	if( timeout <= 0 ){ spi_timeout_cnt++; return 0;}
    // Get the received data
    data = SPI_I2S_ReceiveData(FM25_SPI);

    // Return the shifted data
    return data;
}
static uint8_t fm25_read_status(void)
{
    uint8_t tmp;

    CS_LOW();
    spi_readwrite( FM25_RDSR );
    tmp=spi_readwrite(0xFF);
    CS_HIGH();
    return tmp;
}

rt_size_t fm25_read(rt_device_t dev, rt_off_t offset, void * buf, rt_size_t size)
{
    uint32_t index;

	uint8_t *buffer = (uint8_t*) buf;

    fram_lock();
    //spi_config();
	//rt_kprintf("READ: %d, size=%d\n", offset, size);

    CS_LOW();
	spi_readwrite( FM25_READ);
	spi_readwrite( (offset >> 8)&0xFF );
	spi_readwrite( offset & 0xFF  );
    for(index=0; index<size; index++)
    {
		*buffer++ = spi_readwrite(0xFF);

		if( spi_timeout_cnt > 0 )
		{
			fram_unlock();
			spi_timeout_cnt = 0;
			rt_kprintf("Read time out\n");
			return -1;
		}

		offset++;
    }
    CS_HIGH();

    fram_unlock();

    return size;
}

rt_size_t fm25_write(rt_device_t dev, rt_off_t offset, const void * buf, rt_size_t size)
{
    uint32_t index = size;

	uint8_t *buffer = (uint8_t*) buf;
    fram_lock();
    //spi_config();
	//rt_kprintf("WRITE: %d, size=%d\n", offset, size);
	CS_LOW();
    spi_readwrite( FM25_WREN );
	CS_HIGH();
	CS_LOW();
    spi_readwrite( FM25_WRITE);
	spi_readwrite( (offset >> 8)&0xFF );
	spi_readwrite( offset & 0xFF  );
	while( index > 0 )
	{
		spi_readwrite( *buffer++ );

		if( spi_timeout_cnt > 0 )
		{
			fram_unlock();
			rt_kprintf("Write time out\n");
			spi_timeout_cnt = 0;
			return -1;
		}
		index--;
		offset++;	
	}
    CS_HIGH();
	//rt_thread_delay(100);

    fram_unlock();

    return size;
}
static rt_err_t fm25_init(rt_device_t dev)
{
	return RT_EOK;
}
static rt_err_t fm25_open(rt_device_t dev, rt_uint16_t oflag)
{
	char i;
	SPI_Cmd(FM25_SPI, ENABLE);

	if( oflag != RT_DEVICE_FLAG_RDONLY )
	{
		CS_LOW();
		spi_readwrite( FM25_WRSR );
		spi_readwrite( FM25_WPEN );
		CS_HIGH();
		//rt_kprintf("RDSR=0x%X\n", fm25_read_status());

	}
	return RT_EOK;
}
static rt_err_t fm25_close(rt_device_t dev)
{
	CS_LOW();
    spi_readwrite( FM25_WRDI );
    CS_HIGH();
	SPI_Cmd(FM25_SPI, DISABLE);

	return RT_EOK;
}
static rt_err_t fm25_control(rt_device_t dev, int cmd, void *args)
{
	 RT_ASSERT(dev != RT_NULL);

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL) return -RT_ERROR;

        geometry->bytes_per_sector = 1;
        geometry->block_size = 1;
		geometry->sector_count = 8192;
		
    }

	return RT_EOK;
}

static struct rt_device	spi_flash_device;
void fm25_hw_init()
{
	int i = 0xFFFFF;
	fm25_spi_cfg();

	while(i--);
	//spi_config();
	CS_LOW();
    spi_readwrite( FM25_WRDI );
    CS_HIGH();

	spi_flash_device.type    = RT_Device_Class_Block;
    spi_flash_device.init    = fm25_init;
    spi_flash_device.open    = fm25_open;
    spi_flash_device.close   = fm25_close;
    spi_flash_device.read 	 = fm25_read;
    spi_flash_device.write   = fm25_write;
    spi_flash_device.control = fm25_control;
    /* no private */
    spi_flash_device.user_data = RT_NULL;

    rt_device_register(&spi_flash_device, "fram0",
                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);

}

int fram_test(int x)
{
	//rt_kprintf("SR=0x%X\nCR1=0x%X\nCR2=0x%X\n", FM25_SPI->SR, FM25_SPI->CR1,FM25_SPI->CR2);
	 rt_device_t device = RT_NULL;
	char buf[256];
	char read[256];
	int i, j;

	for(i =0; i< 256; i++ )
	{
		buf[i] = i;
		read[i] = 0;
	}
    // step 1:find device
    device = rt_device_find("fram0");
    if( device == RT_NULL)
    {
        rt_kprintf("device %s: not found!\r\n");
        return RT_ERROR;
    }
	device->open(device,RT_DEVICE_FLAG_RDWR);

	for( j = 0; j < FM25_MAXSIZE; j+= 256 )
	//j = 256*x;
	{
		//rt_kprintf("RDSR=0x%X\n", fm25_read_status());
		device->write(device,j, buf,256);
		device->read(device,j, read,256);
		for(i =0; i< 256; i++ )
		{
			if( buf[i] != read[i] )
				rt_kprintf("error at %d: %d!=%d\n", i, buf[i], read[i]);
		}
	}
	device->close(device);
	rt_kprintf("Finsh test\n");
}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(fram_test, test system);
#endif
