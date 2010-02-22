/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : mass_mal.c
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 04/27/2009
* Description        : Medium Access Layer interface
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
#include "mass_mal.h"
#include "rtthread.h"

uint32_t Mass_Memory_Size[3];
uint32_t Mass_Block_Size[3];
uint32_t Mass_Block_Count[3];

/* logic unit count; the first is 0 */
uint32_t Max_Lun = 2;

rt_device_t dev_sdio = RT_NULL;
rt_device_t dev_spi_flash = RT_NULL;
#if (USB_USE_AUTO_REMOVE == 1)
unsigned long test_unit_ready_last = 0;
#endif

uint16_t MAL_Init(uint8_t lun)
{
    uint16_t status = MAL_OK;

    switch (lun)
    {
    case 0:
        status = MAL_OK;
        break;
    case 1:
        status = MAL_OK;
        break;
    case 2:
        status = MAL_FAIL;
        break;
    default:
        return MAL_FAIL;
    }
    return status;
}

uint16_t MAL_Write(uint8_t lun, uint32_t Memory_Offset, uint32_t *Writebuff, uint16_t Transfer_Length)
{
#if (USB_USE_AUTO_REMOVE == 1)
    test_unit_ready_last = rt_tick_get();
#endif
    switch (lun)
    {
    case 0:
    {
        dev_sdio->write(dev_sdio,Memory_Offset,Writebuff,Transfer_Length);
    }
    break;
    case 1:
    {
        dev_spi_flash->write(dev_spi_flash,Memory_Offset,Writebuff,Transfer_Length);
    }
    break;
    default:
        return MAL_FAIL;
    }
    return MAL_OK;
}

uint16_t MAL_Read(uint8_t lun, uint32_t Memory_Offset, uint32_t *Readbuff, uint16_t Transfer_Length)
{
#if (USB_USE_AUTO_REMOVE == 1)
    test_unit_ready_last = rt_tick_get();
#endif
    switch (lun)
    {
    case 0:
    {
        dev_sdio->read(dev_sdio,Memory_Offset,Readbuff,Transfer_Length);
    }
    break;
    case 1:
    {
        dev_spi_flash->read(dev_spi_flash,Memory_Offset,Readbuff,Transfer_Length);
    }
    break;
    default:
        return MAL_FAIL;
    }
    return MAL_OK;
}

uint16_t MAL_GetStatus (uint8_t lun)
{
#if (USB_USE_AUTO_REMOVE == 1)
    test_unit_ready_last = rt_tick_get();
#endif
    switch(lun)
    {
    case 0:
        return MAL_OK;
    case 1:
        return MAL_OK;
    case 2:
        return MAL_FAIL;
    default:
        return MAL_FAIL;
    }
}

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
