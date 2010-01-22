#include "stm32f10x.h"
#include "usb_lib.h"
#include "usb_istr.h"
#include "hw_config.h"
#include "usb_pwr.h"

#include "rtthread.h"

extern uint32_t Mass_Memory_Size[3];
extern uint32_t Mass_Block_Size[3];
extern uint32_t Mass_Block_Count[3];
extern rt_device_t dev_sdio;
extern rt_device_t dev_spi_flash;

#include <finsh.h>
#include "sdcard.h"
void USB_cable(void)
{
    rt_device_t dev = RT_NULL;
    SD_CardInfo * sdio_info = RT_NULL;
    dev = rt_device_find("sd0");

    {
        SPI_InitTypeDef SPI_InitStructure;
        /*------------------------ SPI1 configuration ------------------------*/
        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//SPI_Direction_1Line_Tx;
        SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
        SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
        SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
        SPI_InitStructure.SPI_NSS  = SPI_NSS_Soft;
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;/* 72M/64=1.125M */
        SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
        SPI_InitStructure.SPI_CRCPolynomial = 7;

        SPI_I2S_DeInit(SPI1);
        SPI_Init(SPI1, &SPI_InitStructure);

        /* Enable SPI_MASTER */
        SPI_Cmd(SPI1, ENABLE);
        SPI_CalculateCRC(SPI1, DISABLE);
    }


    /* SPI_FLASH */
    dev_spi_flash = rt_device_find("spi0");
    Mass_Block_Size[1]  = 512;
    Mass_Block_Count[1] = 4096;
    Mass_Memory_Size[1] = 4096*512;

    if(dev != RT_NULL)
    {
        dev_sdio = dev;
        sdio_info = (SD_CardInfo *)dev->private;
        Mass_Memory_Size[0] = sdio_info->CardCapacity;
        Mass_Block_Size[0]  = sdio_info->CardBlockSize;
        Mass_Block_Count[0] = Mass_Memory_Size[0] / Mass_Block_Size[0];
    }
    else
    {
        rt_kprintf("\r\nNo find the device sd0 !!!!");
    }

    /* 3:NAND */

    /* usb msc up*/
    Set_System();
    Set_USBClock();
    USB_Interrupts_Config();
    USB_Init();
}
FINSH_FUNCTION_EXPORT(USB_cable, cable_the_usb);
