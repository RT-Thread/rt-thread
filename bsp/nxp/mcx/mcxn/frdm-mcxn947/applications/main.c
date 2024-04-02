/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 * Copyright (c) 2019-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-24     Magicoe      first version
 * 2020-01-10     Kevin/Karl   Add PS demo
 * 2020-09-21     supperthomas fix the main.c
 *
 */

#include <rtdevice.h>
#include <rtthread.h>
#include "drv_pin.h"

#define LEDB_PIN        ((0*32)+10)
#define BUTTON_PIN      ((0*32)+23)

#define W25Q64_SPI_DEVICE_NAME   "spi70"

const uint8_t Text_Buffer[] = {"RT-Thread based MCXN947 LPSPI and W25Q64 communication routine"};
#define SIZE            sizeof(Text_Buffer)

/* W25Q64 Instruction list */
uint8_t const W25X_WriteEnable=		  0x06 ;
uint8_t const W25X_WriteDisable=		0x04 ;
uint8_t const W25X_ManufactDeviceID=		0x90 ;
uint8_t const W25X_ReadStatusReg=		  0x05 ;
uint8_t const W25X_WriteStatusReg=		0x01 ;
uint8_t const W25X_ReadData=		0x03 ;
uint8_t const W25X_FastReadData=		  0x0B ;
uint8_t const W25X_FastReadDual=		0x3B ;
uint8_t const W25X_PageProgram=		0x02 ;
uint8_t const W25X_BlockErase=		  0xD8 ;
uint8_t const W25X_SectorErase=		0x20 ;
uint8_t const W25X_ChipErase=		  0xC7 ;
uint8_t const W25X_PowerDown=		0xB9 ;
uint8_t const W25X_ReleasePowerDown=		0xAB ;
uint8_t const W25X_DeviceID=		  0xAB ;
uint8_t const W25X_JedecDeviceID=		0x9F ;

static struct rt_spi_device *spi_device_w25;
static void sw_pin_cb(void *args);
void W25Q64_Init(void);
void W25Q64_ReadID(void);
void flash_write_enable(void);
void flash_write_disable(void);
uint8_t W25Q64_ReadSR(void);
void W25Q64_WriteSR(uint8_t Byte);
void W25Q64_Read(uint8_t *pBuffer, uint32_t ReadAddress, uint16_t Num);
void W25Q64_Write_Page(uint8_t *pBuffer, uint32_t WriteAddress, uint16_t Num);
void W25Q64_Wait_Busy(void);
void W25Q64_Write_NoCheck(uint8_t *pBuffer, uint32_t WriteAddress, uint16_t Num);
void W25Q64_Erase_Chip(void);
void W25Q64_Erase_Sector(uint32_t SecAddress);
void W25Q64_PowerDown(void);
void W25Q64_Wakeup(void);
void W25Q64_Write(uint8_t *pBuffer, uint32_t WriteAddress, uint16_t Num);

/* W25Q64 Init */
void W25Q64_Init(void)
{
		spi_device_w25 = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));

	  rt_spi_bus_attach_device_cspin(spi_device_w25, W25Q64_SPI_DEVICE_NAME, "spi7", 96, RT_NULL);
		spi_device_w25 = (struct rt_spi_device *)rt_device_find(W25Q64_SPI_DEVICE_NAME);
	  if(!spi_device_w25)
		{
			  rt_kprintf("spi sample run failed! can't find %s device!\n","spi7");
		}
		else
		{
			  struct rt_spi_configuration cfg;
		    cfg.data_width = 8;
		    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_3 | RT_SPI_MSB;
		    cfg.max_hz = 50 * 1000 *1000;
		    rt_spi_configure(spi_device_w25, &cfg);
		}
		rt_kprintf("W25Q64 Init Successful!\n");
}

/* W25Q64 Flash Write Enable */
void flash_write_enable(void)
{
	  rt_spi_send(spi_device_w25, &W25X_WriteEnable, 1);
}

/* W25Q64 Flash Write Disable */
void flash_write_disable(void)
{
	  rt_spi_send(spi_device_w25, &W25X_WriteDisable, 1);
}

/* W25Q64 Read ID */
void W25Q64_ReadID(void)
{
		rt_uint8_t w25x_read_id = 0x90;
    rt_uint8_t id[5] = {0};
//		flash_write_enable();

    rt_spi_send_then_recv(spi_device_w25, &w25x_read_id, 1, id, 5);
		/* W25Q64 ID: 0xEF16 */
		rt_kprintf("W25Q64 ID:0X%X%X\n", id[3], id[4]);
}

/* Read W25Q64 Status Register 
 * BIT7  6  5  4   3   2   1   0
 * SPR   RV TB BP2 BP1 BP0 WEL BUSY
 * SPR : Default 0, status register protection bit, used with WP
 * TB/BP2/BP1/BP0 : Flash area write protection Settings
 * WEL : Write enable lock
 * BUSY : Busy flag bit: 1 busy; 0 idle
 */
uint8_t W25Q64_ReadSR(void)
{
	  uint8_t Byte = 0;

	  rt_spi_send_then_recv(spi_device_w25, &W25X_ReadStatusReg, 1, &Byte, 1);
		
//		rt_kprintf("W25Q64 Status Register Value: 0X%X\n", Byte);
		return Byte;
}

/* Write W25Q64 Status Register
 * BIT7  6  5  4   3   2   1   0
 * SPR   RV TB BP2 BP1 BP0 WEL BUSY
 * SPR : Default 0, status register protection bit, used with WP
 * TB/BP2/BP1/BP0 : Flash area write protection Settings
 * WEL : Write enable lock
 * BUSY : Busy flag bit: 1 busy; 0 idle
 * !!! Only SPR, TB, BP2, BP1, and BP0 (bit 7,5,4,3,2) can be written
 */
void W25Q64_WriteSR(uint8_t Byte)
{
	  rt_spi_send_then_send(spi_device_w25, &W25X_WriteStatusReg, 1, &Byte, 1);
}

/* Read W25Q64 SPI Flash
 * Begins reading data of a specified length at a specified address
 * pBuffer : Data Memory area
 * ReadAddress : Read Address
 * Num : Read Byte Size
 */
void W25Q64_Read(uint8_t *pBuffer, uint32_t ReadAddress, uint16_t Num)
{
	  /* 03h A23~A16 A15~A8 A7~A0 D7~D0 */
	  uint32_t Read_Use_Address = (W25X_ReadData) | (ReadAddress << 8);
	  rt_spi_send_then_recv(spi_device_w25, &Read_Use_Address, 4, pBuffer, Num);
}

/* Write up to 256 bytes of data at the specified address
 * (Do not exceed the number of bytes remaining on the page)
 * pBuffer : Data Memory area
 * WriteAddress : Write Address
 * Num : Write Byte Size
 */
void W25Q64_Write_Page(uint8_t *pBuffer, uint32_t WriteAddress, uint16_t Num)
{
	  /* 02h A23~A16 A15~A8 A7~A0 D7~D0 */
	  uint32_t Write_Use_Address = (W25X_PageProgram) | (WriteAddress << 8);
	  flash_write_enable();
	  rt_spi_send_then_send(spi_device_w25, &Write_Use_Address, 4, pBuffer, Num%256);
	  W25Q64_Wait_Busy();
}

/* W25Q64 Wait leisure
 * parameter : void
 */
void W25Q64_Wait_Busy(void)
{
	  while((W25Q64_ReadSR() & 0x01) == 0x01); /* SR Register bit0 -> 0 */
}

/* The SPI Flash writes data of a specified length at a specified address without checking
 * pBuffer : Data Memory area
 * WriteAddress : Write Address
 * Num : Write Byte Size
 */
void W25Q64_Write_NoCheck(uint8_t *pBuffer, uint32_t WriteAddress, uint16_t Num)
{
	  uint16_t Page_Remain;
	  Page_Remain = 256 - WriteAddress % 256;
	  if(Num <= Page_Remain)
		{
			  Page_Remain = Num;
		}
		while(1)
		{
			  W25Q64_Write_Page(pBuffer, WriteAddress, Page_Remain);
			  if(Num == Page_Remain)
				{
					  break;
				}
				else /* Num > Page_Remain */
				{
					  pBuffer = pBuffer + Page_Remain;
					  WriteAddress = WriteAddress + Page_Remain;
					  Num = Num - Page_Remain;
					  
					  if(Num > 255)
						{
							  Page_Remain = 255;
						}
						else
						{
							  Page_Remain = Num;
						}
				}
		}
}

/* Start writing data of a specified length at a specified address (with erasure)
 * pBuffer : Data Memory area
 * WriteAddress : Write Address(24 bit)
 * Num : Write Byte Size(Max: 65535)
 */
uint8_t W25Q64_Buffer[4096];

void W25Q64_Write(uint8_t *pBuffer, uint32_t WriteAddress, uint16_t Num)
{
	  uint32_t SecAddress;
	  uint16_t SecMove;
	  uint16_t SecRemain;
    uint16_t i;
	  uint8_t *W25Q64_Buf;
    
    W25Q64_Buf = W25Q64_Buffer;
	  SecAddress = WriteAddress / 4096;
	  SecMove = WriteAddress % 4096;
	  SecRemain = 4096 - SecMove;
	
	  if(Num <= SecRemain)
		{
			  SecRemain = Num;
		}
		while(1)
		{
			  W25Q64_Read(W25Q64_Buf, SecAddress*4096, 4096);
			  for(i = 0; i < SecRemain; i ++)
				{
					  if(W25Q64_Buf[SecMove + i] != 0xFF)
						{
							  break;
						}
				}
				if(i < SecRemain)
				{
					  W25Q64_Erase_Sector(SecAddress);
					  for(i = 0; i < SecRemain; i ++)
						{
							  W25Q64_Buf[i + SecMove] = pBuffer[i];
						}
						W25Q64_Write_NoCheck(W25Q64_Buf, SecAddress*4096, 4096);
				}
				else
				{
					  W25Q64_Write_NoCheck(pBuffer, WriteAddress, SecRemain);
				}
				if(Num == SecRemain)
				{
					  break;
				}
				else
				{
					  SecAddress ++;
					  SecMove = 0;
					  
					  pBuffer = pBuffer + SecRemain;
					  WriteAddress = WriteAddress + SecRemain;
					
					  Num = Num - SecRemain;
					  if(Num > 4096)
						{
							  SecRemain = 4096;
						}
						else
						{
							  SecRemain = Num;
						}
				}
		}
		
//    W25Q64_Erase_Sector(WriteAddress);
//		W25Q64_Write_NoCheck(pBuffer, WriteAddress, Num);
}

/* Erase the entire chip
 * Parameter : Void
 */
void W25Q64_Erase_Chip(void)
{
	  flash_write_enable();
	  W25Q64_Wait_Busy();
	  rt_spi_send(spi_device_w25, &W25X_ChipErase, 1);
	  W25Q64_Wait_Busy();
}

/* Erases a sector
 * Parameter : SecAddress(Prepare the sector address to erase)
 */
void W25Q64_Erase_Sector(uint32_t SecAddress)
{
	  rt_kprintf("fe: 0x%x\r\n",SecAddress);
	  uint32_t EraseSectorCmd = (W25X_SectorErase) | (SecAddress << 8);
	  SecAddress = SecAddress * 4096;
	  flash_write_enable();
	  W25Q64_Wait_Busy();
	  rt_spi_send(spi_device_w25, &EraseSectorCmd, 4);
	  W25Q64_Wait_Busy();
}

/* Enter power failure mode
 * Parameter : void
 */
void W25Q64_PowerDown(void)
{
	  rt_spi_send(spi_device_w25, &W25X_PowerDown, 1);
	  rt_hw_us_delay(3);
}

/* Wakeup
 * Parameter : void
 */
void W25Q64_Wakeup(void)
{
	  rt_spi_send(spi_device_w25, &W25X_ReleasePowerDown, 1);
	  rt_hw_us_delay(3);
}

int main(void)
{
#if defined(__CC_ARM)
    rt_kprintf("using armcc, version: %d\n", __ARMCC_VERSION);
#elif defined(__clang__)
    rt_kprintf("using armclang, version: %d\n", __ARMCC_VERSION);
#elif defined(__ICCARM__)
    rt_kprintf("using iccarm, version: %d\n", __VER__);
#elif defined(__GNUC__)
    rt_kprintf("using gcc, version: %d.%d\n", __GNUC__, __GNUC_MINOR__);
#endif

    rt_pin_mode(LEDB_PIN, PIN_MODE_OUTPUT);  /* Set GPIO as Output */

    rt_pin_mode(BUTTON_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(BUTTON_PIN, PIN_IRQ_MODE_FALLING, sw_pin_cb, RT_NULL);
    rt_pin_irq_enable(BUTTON_PIN, 1);

    rt_kprintf("MCXN947 SPI Interview W25Q64 Flash \r\n");


#ifdef RT_USING_SDIO
    rt_thread_mdelay(2000);
    if (dfs_mount("sd", "/", "elm", 0, NULL) == 0)
    {
        rt_kprintf("sd mounted to /\n");
    }
    else
    {
        rt_kprintf("sd mount to / failed\n");
    }
#endif

		uint8_t DataTemp[SIZE];
    uint32_t Flash_Size;
		uint32_t i = 0;
		W25Q64_Init();
		W25Q64_ReadID();
		/* W25Q64 Flash Size: 8M */
		Flash_Size = 8*1024*1024;

		W25Q64_Write((uint8_t *)Text_Buffer, Flash_Size - 100, SIZE);
		rt_kprintf("W25Q64 Write Finished!\r\n");

		rt_kprintf("Start Read W25Q64......\r\n");
	  W25Q64_Read(DataTemp, Flash_Size - 100, SIZE);
	  rt_kprintf("The Data Readed Is: %s\n",DataTemp);

    while (1)
    {
        rt_pin_write(LEDB_PIN, PIN_HIGH);    /* Set GPIO output 1 */
        rt_thread_mdelay(500);               /* Delay 500mS */
        rt_pin_write(LEDB_PIN, PIN_LOW);     /* Set GPIO output 0 */
        rt_thread_mdelay(500);               /* Delay 500mS */
    }
}

static void sw_pin_cb(void *args)
{
    rt_kprintf("sw2 pressed\r\n");
}

// end file
