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
#include "usb_lib.h"
#include "udisk\mass_mal.h"
#include <string.h>

uint32_t Mass_Memory_Size[1];
uint32_t Mass_Block_Size[1];
uint32_t Mass_Block_Count[1];



/* logic unit count; the first is 0 */
uint32_t Max_Lun = 0;
#include <rtthread.h>
#define UDISK_DEV "w25"
rt_device_t SD_DEV;
rt_uint8_t * Data_Buffer=0;
uint16_t MAL_Init(uint8_t lun)
{
    uint16_t status = MAL_OK;
		Data_Buffer=(rt_uint8_t *)rt_malloc(4096);
	  SD_DEV=rt_device_find(UDISK_DEV);
    switch (lun)
    {
    case 0:
    {
			struct rt_device_blk_geometry geometry;
         rt_device_control(SD_DEV ,RT_DEVICE_CTRL_BLK_GETGEOME,&geometry);
        Mass_Memory_Size[0] = (geometry.bytes_per_sector)*(geometry.sector_count);
        Mass_Block_Size[0]  = geometry.block_size ;
        Mass_Block_Count[0] = geometry.sector_count;
			
// 			   Mass_Memory_Size[0] = 8UL*1024*1024;
//          Mass_Block_Size[0]  = 4096 ;
//          Mass_Block_Count[0] = Mass_Memory_Size[0] / Mass_Block_Size[0];
//         
        
        status = MAL_OK;
    }
    break;
    case 1:
		    status = MAL_FAIL;
        break;
    case 2:
        status = MAL_FAIL;
        break;
    default:
       break;//  return MAL_FAIL;
    }
    return status;
}

uint16_t MAL_Write(uint8_t lun, uint32_t Memory_Offset, uint8_t *Writebuff, uint16_t Transfer_Length)
{ 
    switch (lun)
    {
    case 0:
    {   
			rt_device_write(SD_DEV,Memory_Offset/Mass_Block_Size[0],Writebuff,Transfer_Length/Mass_Block_Size[0]);
	//		w25qxx.writen(Memory_Offset,(char *)Writebuff,Transfer_Length);
    }
    break;
     default:
        return MAL_FAIL;
    }
    return MAL_OK;
}

uint16_t MAL_Read(uint8_t lun, uint32_t Memory_Offset, uint8_t *Readbuff, uint16_t Transfer_Length)
{   

    switch (lun){
    case 0:
			rt_device_read(SD_DEV,Memory_Offset/Mass_Block_Size[0],Readbuff,Transfer_Length/Mass_Block_Size[0]);
//   	w25qxx.readn(Memory_Offset,(char *)Readbuff,Transfer_Length);
		return MAL_OK;
    case 1:
    return MAL_OK;
	}
	return MAL_OK;
}
 
uint16_t MAL_GetStatus (uint8_t lun)
{
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
