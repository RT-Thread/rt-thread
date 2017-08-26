/***********************************************************************!     
 *     技术讨论：QQ群  123763203
 *     官网    ：www.navota.com
 *
 * @file       flash.c
 * @brief      flash函数库
 * @author     Navota
 * @date       2017-1-1
 ************************************************************************/

#include "nv32f100.h"

#define FLASH_ENABLE_STALLING_FLASH_CONTROLLER


/*****************************************************************************//*!
+FUNCTION----------------------------------------------------------------
* @function name: Flash_Init
*
* @brief 初始化FLASH
*        
* @param  
*
* @return none
*
*****************************************************************************/

uint16_t Flash_Init(void)
{
	uint16_t err   = FLASH_ERR_SUCCESS;
	uint32_t clkDIV = BUS_CLK_HZ/1000000L - 1;
	uint32_t Tpgs  =(285 *(BUS_CLK_HZ/100))/1000000L;  //update 2016.8.4 by 光脚板のGG
	uint32_t Tprog =(675*(BUS_CLK_HZ/100))/1000000L;   //by 光脚板のGG
//        printf("Tpgs= %x \n" , Tpgs);
//        printf("Tprog= %x \n" , Tprog);   
        
	EFMCR=(clkDIV<<24) + 0x00001101; //divide to 1M hz 
	EFMETM0=(Tpgs<<16)  + 0x00001194;  //0x00281194; //
	EFMETM1=(Tprog<<16) + 0x000088B8; //
//        printf("EFMCR= %x \n" , EFMCR); 
//        printf("EFMETM0= %x \n" , EFMETM0);         
//        printf("EFMETM1= %x \n" , EFMETM1); 
  return(err);
}

/*****************************************************************************//*!
+FUNCTION----------------------------------------------------------------
* @function name: FlashProgram
*
* @brief    flash加载编程：总的过程就是，给出字节长度，先写入满足两个字的个数，
*                再写入剩余满足一个字的个数，最后写入剩余的字节数。
*        
* @param[in]     wNVMTargetAddress     所要存放的FLASH首地址
* @param[in]     *pData                所要存放的数据
* @param[in]     sizeBytes             字节长度
*
* @return none
*
*****************************************************************************/

uint16_t Flash_Program(uint32_t wNVMTargetAddress, uint8_t *pData, uint16_t sizeBytes)
{
	uint16_t err = FLASH_ERR_SUCCESS;
	uint16_t w2LongWordCount = sizeBytes>>3;//处理一下，得到2个字的个数
	uint8_t  wLeftBytes = (sizeBytes & 0x07);//低位三个字节的个数
	uint16_t wLeftLongWords = wLeftBytes>>2;//低位中满一个字个数
	uint32_t wTargetAddress = wNVMTargetAddress;
	uint32_t dwData0,dwData1;
	uint32_t *pdwData = (uint32_t*)pData;//传参
	int  i;
        //判断是否字对齐
	if(wNVMTargetAddress & 0x03)
	{
		err = FLASH_ERR_INVALID_PARAM;
		return (err);//返回无效的参数
	}
	//循环写入两个长字（即8个字节），共写入w2LongWordCount * 8个字节
	for(i = 0; i < w2LongWordCount; i++)
	{
		dwData0 = *pdwData++;
		dwData1 = *pdwData++;
		err = Flash_Program2LongWords(wTargetAddress, dwData0, dwData1);//加载两个字的编程
		if(err) //地址不为4个字节对齐，则直接跳转
		{
			goto EndP;
			//break;
		}
		wTargetAddress += 8;//循环一次写入8个字节，即2个字，NV32的flash是字对齐的
	}
	// 一个字的编程，即4bytes
	for(i = 0; i < wLeftLongWords; i++)
	{
		dwData0 = *pdwData++;
		//printf("\n adr : 0x%x ,data = 0x%x\n",i,dwData0 );
		err = Flash_Program1LongWord(wTargetAddress, dwData0);
    //printf("\n adr : 0x%x ,data = 0x%x\n",i,dwData0 );
		if(err)
		{			
			goto EndP;
			//break;
		}
		wTargetAddress += 4;
	}
	wLeftBytes = (wLeftBytes-(wLeftLongWords<<2));	//在两字和一字的编程都处理完后剩余的低两位字节数
	if(!wLeftBytes){ //若无剩余字节数，返回成功
		return (err);
	}
        
#if     defined(BIG_ENDIAN)                
	dwData0 = 0;
	pData = (uint8_t*)pdwData;	
	for(i = wLeftBytes; i >0; i--)
	{
		dwData0 <<= 8;
		dwData0 |= *pData++;	
	}
	
	wLeftBytes = 4 - wLeftBytes;	 
	for(i = wLeftBytes; i >0; i--)
	{
		dwData0 <<= 8;
		dwData0 |= 0xFF;	
	}
#else
	dwData0 = 0xFFFFFFFFL;        
	pData = (uint8_t*)pdwData+wLeftBytes-1;	
	for(i = wLeftBytes; i >0; i--)
	{
		dwData0 <<= 8;
		dwData0 |= *pData--;	
	}
#endif	
	err = Flash_Program1LongWord(wTargetAddress, dwData0);	
EndP:	
	return (err);
}


/*****************************************************************************//*!

* @function name: FlashProgram1LongWord
*
* @brief  加载一个字的大小，编程到FLASH中(也就是四个字节)
*        
* @param[in]     wNVMTargetAddress     所要存放的FLASH首地址
* @param[in]     dwData                所要存放的数据
*
* @return none  
*
*****************************************************************************/
uint16_t Flash_Program1LongWord(uint32_t wNVMTargetAddress, uint32_t dwData)
{
	uint16_t err = FLASH_ERR_SUCCESS;
	
	//判断是否为字对齐
	if(wNVMTargetAddress & 0x03)
	{
		err = FLASH_ERR_INVALID_PARAM;
		return (err);
	}
        // 清除错误标志
	EFMCMD = FLASH_CMD_CLEAR;
	//写入数据到对应的地址中
	M32(wNVMTargetAddress) = dwData;
	//加载编程命令	
        EFM_LaunchCMD(FLASH_CMD_PROGRAM);
	return (err);//返回状态
}

/*****************************************************************************//*!

* @function name: FlashProgram2LongWords
*
* @brief  加载两个字的大小，编程到FLASH中(也就是八个字节)
*        
* @param[in]     wNVMTargetAddress     所要存放的FLASH首地址
* @param[in]     dwData0               低4个字节
* @param[in]     dwData1               高4个字节
*
* @return none  
*
*****************************************************************************/
uint16_t Flash_Program2LongWords(uint32_t wNVMTargetAddress, uint32_t dwData0, uint32_t dwData1)
{
	uint16_t err = FLASH_ERR_SUCCESS;

	
	//判断是否为字对齐
	if(wNVMTargetAddress & 0x03)
	{
		err = FLASH_ERR_INVALID_PARAM;
		return (err);
	}
	// 清除错误标志

	EFMCMD = FLASH_CMD_CLEAR;

//	printf("\n write data  adr : 0x%x ,data = 0x%x\n",dwData0,dwData1 );
	M32(wNVMTargetAddress) = dwData0;//存放数据到以目标地址为起始的4个字节的空间中
        EFM_LaunchCMD(FLASH_CMD_PROGRAM);//0x20000000,加载编程命令
	wNVMTargetAddress = wNVMTargetAddress +4;//地址是字对齐的，地址向后移一个字
	
	//printf("\n write data  adr : 0x%x ,data = 0x%x\n",wNVMTargetAddress,dwData1 );
	// 清除错误标志
	EFMCMD = FLASH_CMD_CLEAR;
	M32(wNVMTargetAddress) = dwData1;//第二个数据放入处理后的地址的4个字节的空间中
        EFM_LaunchCMD(FLASH_CMD_PROGRAM);//加载编程命令
//	printf("\n write data  adr : 0x%x ,data = 0x%x\n",wNVMTargetAddress,dwData1 );
	return (err);//返回处理状态
}





/*****************************************************************************//*!
+FUNCTION----------------------------------------------------------------
* @function name: Flash_EraseSector
*
* @brief 擦除目标地址的一个扇区（512字节）,.
*        
* @param[in]    wNVMTargetAddress   擦除扇区的首地址
*
* @return none
*
*****************************************************************************/
uint16_t  Flash_EraseSector(uint32_t wNVMTargetAddress)
{
	uint16_t err = FLASH_ERR_SUCCESS;
	// 判断是否字对齐
	if(wNVMTargetAddress & 0x03)
	{
		err = FLASH_ERR_INVALID_PARAM;
		return (err);
	}
	// 清除错误标志
		EFMCMD = FLASH_CMD_CLEAR;
	  M32(wNVMTargetAddress) = 0xffffffff;
	  EFM_LaunchCMD(FLASH_CMD_ERASE_SECTOR);//加载擦除命令
	return (err);
}


uint16_t Flash_VerifyBackdoorKey()
{
	uint16_t err = FLASH_ERR_SUCCESS;
//        int i;
        
	// Clear error flags
	 EFMCMD = FLASH_CMD_CLEAR;
	// Write index to specify the command code to be loaded
	 Custombkd = FLASH_FACTORY_KEY;
	return (err);
}

/*****************************************************************************//*!
+FUNCTION----------------------------------------------------------------
* @function name: NVM_EraseAll
*
* @brief 整片擦除FLASH(慎用，注意0X40E这个地址，在调试阶段写入0XFE)
*        
* @param  
*	
* @return none
*
*****************************************************************************/
uint16_t NVM_EraseAll(void)
{
	uint16_t err = FLASH_ERR_SUCCESS;
		EFMCMD = FLASH_CMD_CLEAR;
	  EFM_LaunchCMD(FLASH_CMD_ERASE_ALL);
	// Clear error flags
    return err;
}

/*****************************************************************************//*!
+FUNCTION----------------------------------------------------------------
* @function name: NVM_Unsecure
*
* @brief unsecure 
*        
* @param  
*	
* @return none
*
*****************************************************************************/
uint16_t NVM_Unsecure(void)
{
	uint16_t err = FLASH_ERR_SUCCESS;

    return err;
}



/*****************************************************************************//*!
+FUNCTION----------------------------------------------------------------
* @function name: EFM_LaunchCMD
*
* @brief 命令加载函数(注：此函数须放入SRAM中运行)
*        
* @param  
*	
* @return none
*
*****************************************************************************/
#ifdef IAR
void __ramfunc EFM_LaunchCMD(uint32_t EFM_CMD)
#else
void EFM_LaunchCMD(uint32_t EFM_CMD)
#endif
{
  DisableInterrupts;
		if((EFMCMD&EFM_DONE_MASK)== EFM_STATUS_READY)
		{
	  EFMCMD = EFM_CMD;
		}
	while(1)
	{
		if((EFMCMD&EFM_DONE_MASK) == EFM_STATUS_DONE) break;
	}
 EnableInterrupts;
}
