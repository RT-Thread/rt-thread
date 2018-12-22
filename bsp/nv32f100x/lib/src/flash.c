/******************************************************************************
******************************************************************************
*
* @file flash.c
*
* @brief application entry point which performs application specific tasks. 
*
*******************************************************************************
*
* provide a demo for how to initialize the NV32, output messages via SCI, 
* flash operations, etc.
* NOTE:
*	printf call may occupy a lot of memory (around 1924 bytes), so please
*	consider your code size before using printf.
******************************************************************************
*
* provide FLASH driver
*
******************************************************************************/

#include "flash.h"
/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Constants and macros
******************************************************************************/


/******************************************************************************
* Local types
******************************************************************************/

/******************************************************************************
* Local function prototypes
******************************************************************************/

/******************************************************************************
* Local variables
******************************************************************************/

/******************************************************************************
* Local functions
******************************************************************************/

/******************************************************************************
* Global functions
******************************************************************************/
/*****************************************************************************//*!
+FUNCTION----------------------------------------------------------------
* @function name: Flash_CopyInRAM
*
* @brief This section of the code is the one that copies the routine into RAM. 
* It is following the steps  documented in Technical Note 228
*        
* @param  
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/

#define FLASH_ENABLE_STALLING_FLASH_CONTROLLER


/*****************************************************************************//*!
+FUNCTION----------------------------------------------------------------
* @function name: Flash_Init
*
* @brief initialize flash driver
*        
* @param  
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/

uint16_t Flash_Init(void)
{
	uint16_t err   = FLASH_ERR_SUCCESS;
	uint32_t clkDIV = BUS_CLK_HZ/1000000L - 1;
	uint32_t Tpgs  =(285 *(BUS_CLK_HZ/100))/1000000L;  //update 2016.8.4 by 高重医のGG
	uint32_t Tprog =(675*(BUS_CLK_HZ/100))/1000000L;   //by 高重医のGG
//        printf("Tpgs= %x \n" , Tpgs);
//        printf("Tprog= %x \n" , Tprog);   
        
	EFMCR=(clkDIV<<24) + 0x00001103; //divide to 1M hz 
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
* @brief program flash routine, each program operation supports up to 2 longwords
* 		 programming
*        
* @param  
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/

uint16_t Flash_Program(uint32_t wNVMTargetAddress, uint8_t *pData, uint16_t sizeBytes)
{
	uint16_t err = FLASH_ERR_SUCCESS;
	uint16_t w2LongWordCount = sizeBytes>>3;
	uint8_t  wLeftBytes = (sizeBytes & 0x07);
	uint16_t wLeftLongWords = wLeftBytes>>2;
	uint32_t wTargetAddress = wNVMTargetAddress;
	uint32_t dwData0,dwData1;
	uint32_t *pdwData = (uint32_t*)pData;
	int  i;
 //printf("\n adr : 0x%x ,data = 0x%x\n",w2LongWordCount,wLeftLongWords );
	// Check address to see if it is aligned to 4 bytes
	// Global address [1:0] must be 00.
	if(wNVMTargetAddress & 0x03)
	{
		err = FLASH_ERR_INVALID_PARAM;
		return (err);
	}
	// Loop for the two longwords (8 bytes) programming
	for(i = 0; i < w2LongWordCount; i++)
	{
		dwData0 = *pdwData++;
		dwData1 = *pdwData++;
		err = Flash_Program2LongWords(wTargetAddress, dwData0, dwData1);
		if(err)
		{
			goto EndP;
			//break;
		}
		wTargetAddress += 8;
	}
	// Loop for the single longword (4 bytes) programming
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
	wLeftBytes = (wLeftBytes-(wLeftLongWords<<2));	// calculate the # of bytes that are not programmed
	if(!wLeftBytes){
		return (err);
	}
        
#if     defined(BIG_ENDIAN)                
	dwData0 = 0;
	pData = (uint8_t*)pdwData;	// pointer to the left bytes
	for(i = wLeftBytes; i >0; i--)
	{
		dwData0 <<= 8;
		dwData0 |= *pData++;	// MSB byte first
	}
	// Calculate how many bytes need to be filled with 0xFFs
	// in order to form a single longword for the left bytes of data
	wLeftBytes = 4 - wLeftBytes;	
	//  
	for(i = wLeftBytes; i >0; i--)
	{
		dwData0 <<= 8;
		dwData0 |= 0xFF;	// MSB byte first
	}
#else
	dwData0 = 0xFFFFFFFFL;        
	pData = (uint8_t*)pdwData+wLeftBytes-1;	// pointer to the left bytes
	for(i = wLeftBytes; i >0; i--)
	{
		dwData0 <<= 8;
		dwData0 |= *pData--;	// MSB byte first
	}
#endif	
	// Now program the last longword
	err = Flash_Program1LongWord(wTargetAddress, dwData0);	
EndP:	
	return (err);
}

uint16_t Flash_Program1LongWord(uint32_t wNVMTargetAddress, uint32_t dwData)
{
	uint16_t err = FLASH_ERR_SUCCESS;
	
	// Check address to see if it is aligned to 4 bytes
	// Global address [1:0] must be 00.
	if(wNVMTargetAddress & 0x03)
	{
		err = FLASH_ERR_INVALID_PARAM;
		return (err);
	}
	// Clear error flags
	EFMCMD = FLASH_CMD_CLEAR;
	// Write index to specify the command code to be loaded
	M32(wNVMTargetAddress) = dwData;
	// Write command code and memory address bits[23:16]	
        EFM_LaunchCMD(FLASH_CMD_PROGRAM);
	return (err);
}


uint16_t Flash_Program2LongWords(uint32_t wNVMTargetAddress, uint32_t dwData0, uint32_t dwData1)
{
	uint16_t err = FLASH_ERR_SUCCESS;

	
	// Check address to see if it is aligned to 4 bytes
	// Global address [1:0] must be 00.
	if(wNVMTargetAddress & 0x03)
	{
		err = FLASH_ERR_INVALID_PARAM;
		return (err);
	}
	// Clear error flags

	EFMCMD = FLASH_CMD_CLEAR;

//	printf("\n write data  adr : 0x%x ,data = 0x%x\n",dwData0,dwData1 );
	// Write index to specify the command code to be loaded
	M32(wNVMTargetAddress) = dwData0;
	// Write command code and memory address bits[23:16]	
  EFM_LaunchCMD(FLASH_CMD_PROGRAM);
	wNVMTargetAddress = wNVMTargetAddress +4;
	
	//	printf("\n write data  adr : 0x%x ,data = 0x%x\n",wNVMTargetAddress,dwData1 );
	// Clear error flags
		EFMCMD = FLASH_CMD_CLEAR;
	// Write index to specify the command code to be loaded
	M32(wNVMTargetAddress) = dwData1;
	// Write command code and memory address bits[23:16]	
  EFM_LaunchCMD(FLASH_CMD_PROGRAM);
//	printf("\n write data  adr : 0x%x ,data = 0x%x\n",wNVMTargetAddress,dwData1 );
	return (err);
}





/*****************************************************************************//*!
+FUNCTION----------------------------------------------------------------
* @function name: Flash_EraseSector
*
* @brief erase flash sector, each flash sector is of 512 bytes long,
* global address [1:0] = 00.
*        
* @param  
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
uint16_t  Flash_EraseSector(uint32_t wNVMTargetAddress)
{
	uint16_t err = FLASH_ERR_SUCCESS;
	// Check address to see if it is aligned to 4 bytes
	// Global address [1:0] must be 00.
	if(wNVMTargetAddress & 0x03)
	{
		err = FLASH_ERR_INVALID_PARAM;
		return (err);
	}
	// Clear error flags
		EFMCMD = FLASH_CMD_CLEAR;
	  M32(wNVMTargetAddress) = 0xffffffff;
	  EFM_LaunchCMD(FLASH_CMD_ERASE_SECTOR);
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
* @brief erase all block,both flash and EEPROM
*        
* @param  
*	
* @return none
*
* @ Pass/ Fail criteria: none
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
* @ Pass/ Fail criteria: none
*****************************************************************************/
uint16_t NVM_Unsecure(void)
{
	uint16_t err = FLASH_ERR_SUCCESS;

    return err;
}

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
