#include <stm32f10x.h>
#include "spi_flash.h"
#include "rtthread.h"

extern unsigned char SPI_WriteByte(unsigned char data);

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

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    FLASH_RST_0(); // RESET
    FLASH_CS_1();
    FLASH_RST_1();
}

static unsigned char SPI_HostReadByte(void)
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

static void SPI_HostWriteByte(unsigned char wByte)
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
static unsigned char AT45DB_StatusRegisterRead(void)
{
    unsigned char i;

    FLASH_CS_0();
    SPI_HostWriteByte(AT45DB_READ_STATE_REGISTER);
    i=SPI_HostReadByte();
    FLASH_CS_1();

    return i;
}

static void wait_busy(void)
{
    unsigned int    i=0;
    while (i++<3000)
    {
        if (AT45DB_StatusRegisterRead()&0x80)
        {
            break;
        }
    }
    if( !(i<3000) )
    {
        rt_kprintf("\r\nSPI_FLASH timeout!!!");
    }
}

static void read_page(unsigned int page,unsigned char * pHeader)
{
    unsigned int i=0;

    wait_busy();

    FLASH_CS_0();
    SPI_HostWriteByte(AT45DB_MM_PAGE_TO_B1_XFER);
    SPI_HostWriteByte((unsigned char)(page >> 6));
    SPI_HostWriteByte((unsigned char)(page << 2));
    SPI_HostWriteByte(0x00);
    FLASH_CS_1();

    wait_busy();

    FLASH_CS_0();
    SPI_HostWriteByte(AT45DB_BUFFER_1_READ);
    SPI_HostWriteByte(0x00);
    SPI_HostWriteByte(0x00);
    SPI_HostWriteByte(0x00);
    SPI_HostWriteByte(0x00);
    for (i=0; i<512; i++)
    {
        *pHeader++ = SPI_HostReadByte();
    }
    FLASH_CS_1();

}

static void write_page(unsigned int page,unsigned char * pHeader)
{
    unsigned int i;

    wait_busy();

    FLASH_CS_0();
    SPI_HostWriteByte(AT45DB_BUFFER_2_WRITE);
    SPI_HostWriteByte(0);
    SPI_HostWriteByte(0);
    SPI_HostWriteByte(0);
    for(i=0; i<512; i++)
    {
        SPI_HostWriteByte(*pHeader++);
    }
    FLASH_CS_1();

    wait_busy();

    FLASH_CS_0();
    SPI_HostWriteByte(AT45DB_B2_TO_MM_PAGE_PROG_WITH_ERASE);
    SPI_HostWriteByte((unsigned char)(page>>6));
    SPI_HostWriteByte((unsigned char)(page<<2));
    SPI_HostWriteByte(0x00);
    FLASH_CS_1();
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
    rt_uint8_t *ptr;
    rt_uint32_t index, nr;

    nr = size/512;
    ptr = (rt_uint8_t*)buffer;

    for (index = 0; index < nr; index ++)
    {
        /* only supply single block read: block size 512Byte */
        read_page((pos + index * 512)/512, &ptr[index * 512]);
    }

    return nr * 512;
}

static rt_size_t rt_spi_flash_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_uint8_t *ptr;
    rt_uint32_t index, nr;

    nr = size / 512;
    ptr = (rt_uint8_t*)buffer;

    for (index = 0; index < nr; index ++)
    {
        /* only supply single block write: block size 512Byte */
        write_page((pos + index * 512)/512, &ptr[index * 512]);
    }

    return nr * 512;
}

void rt_hw_spi_flash_init(void)
{
    GPIO_Configuration();

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
