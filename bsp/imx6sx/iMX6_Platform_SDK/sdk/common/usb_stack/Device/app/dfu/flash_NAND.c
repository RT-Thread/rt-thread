/********************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
**************************************************************************//*!
 *
 * @file flash_NAND.c
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file includes flash routines
 *
 *****************************************************************************/

/*********************************** Includes ***********************************/
#include "hidef.h" /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "flash_NAND.h" /* include flash driver header file */

uint_8 test_erase_cmd( uint_8* to_ptr, uint_16 write_data);
uint_8 test_program_cmd(uint_8* to_ptr, uint_16 write_data);
void unprotect_sector(uint_8 *p_FlashSector);

/*********************************** Macros ************************************/

/*********************************** Defines ***********************************/

/*********************************** Constant **********************************/

/*********************************** Variables *********************************/

/*********************************** Prototype *********************************/

/*********************************** Function **********************************/
/*******************************************************************************
 * Function:        Flash_Init
 *
 * Description:     Set the flash clock
 *
 * Returns:         never return
 *
 * Notes:
 *
 *******************************************************************************/
void Flash_Init()
{

}
/*******************************************************************************
 * Function:        test_program_cmd
 *
 * Description:     Check the status of flash program operation
 *
 * Returns:         uint_8
 *
 * Notes:
 *
 *******************************************************************************/

uint_8 test_program_cmd(uint_8* to_ptr, uint_16 write_data)
{

    uint_16     test_data, test_data1;
    uint_16     cycle_counter = 5000;
    uint_8       error_count = 0;
    uint_8     result =  FLASH_BUSY;   

    while(result == FLASH_BUSY){
        /* Read 1 */
        test_data = *(uint_16 *)to_ptr;
        /* DQ7 contain valid data? */
        if((test_data & DQ7) == (write_data & DQ7)){
            /* Read 2 */
            test_data1 = *(uint_16 *)to_ptr;
            /* Read 3 */
            test_data = *(uint_16 *)to_ptr;
            /* Read 3 valid data => Write operation complete */
            if(test_data == write_data){
                result = FLASH_READY;
            }
            /* Read 3 doesn't contain valid data, operation failed */
            else {                  
                if(error_count++>2){
                    result = FLASH_ERROR;
                    /* software flash reset */
                    *(uint_16 *)to_ptr = FLASH_RESET_CMD;
                }
            }
        }
        /* test for operation internal timeout */
        else {
            if(!(test_data & DQ5)){
                test_data1 = *(uint_16 *)to_ptr;
                test_data = *(uint_16 *)to_ptr;
                /* DQ6 togling? Timeout occured */  
                if(test_data1 & DQ6 != test_data & DQ6){
                    result = FLASH_TIMEOUT;
                    /* software flash reset */
                    *(uint_16 *)to_ptr = FLASH_RESET_CMD;
                }
            }
        }
        /* timeout test */
        if(!cycle_counter--){
            result = FLASH_TIMEOUT;
        }
    }
    
    return result;	   	
	
}
/*******************************************************************************
 * Function:        test_erase_cmd
 *
 * Description:     Check the status of erase sector operation
 *
 * Returns:         uint_8
 *
 * Notes:
 *
 *******************************************************************************/
uint_8 test_erase_cmd( uint_8* to_ptr, uint_16 write_data)
{
	uint_16     test_data, test_data1;
    uint_8       error_count = 0;
    uint_8     result =  FLASH_BUSY;  	
	
    while(result == FLASH_BUSY){
        /* Read 1 */
        test_data = *(uint_16 *)to_ptr;
        /* DQ7 contain valid data? */
        if((test_data & DQ7) == (write_data & DQ7)){
            /* Read 2 */
            test_data1 = *(uint_16 *)to_ptr;
            /* Read 3 */
            test_data = *(uint_16 *)to_ptr;
            /* DQ6 toggling, device error */
            if((test_data & DQ6) != (test_data1 & DQ6) ){
                /* software flash reset */
                *(uint_16 *)to_ptr = FLASH_RESET_CMD;
                result = FLASH_ERROR;
            }
            /* Erase operation complete */
            if((test_data & DQ2) == (test_data1 & DQ2)){
                result = FLASH_READY;
            }
        }
        /* test for operation internal timeout */
        else {
            /* read 1 DQ5 = 1? */
            if(test_data & DQ5){
                /* read 2 */
                test_data1 = *(uint_16 *)to_ptr;
                /* read 3 */
                test_data = *(uint_16 *)to_ptr;
                /* DQ6 togling? Timeout occured */  
                if(test_data1 & DQ6 != test_data & DQ6){
                    result = FLASH_TIMEOUT;
                    /* software flash reset */
                    *(uint_16 *)to_ptr = FLASH_RESET_CMD;
                }
            }
        }
    }
    
    return result;       

}
/*******************************************************************************
 * Function:        unprotect_sector
 *
 * Description:     Unprotect the specifed sector
 *
 * Returns:         never return
 *
 * Notes:
 *
 *******************************************************************************/
void unprotect_sector(uint_8 *p_FlashSector)
{
    uint_16_ptr base_address_ptr = (uint_16_ptr)S28WS128_BASE_ADDR;

	/* write unlock cycle 1 */
	*((uint_16 *)(base_address_ptr + 0x555)) = 0x00AA;
	
	/* write unlock cycle 2 */
	*((uint_16 *)(base_address_ptr + 0x2AA)) = 0x0055;
	
	/* write command */
	*((uint_16 *)(p_FlashSector + 0x555)) = 0x00E0;	
	*((uint_16 *)base_address_ptr)= 0xA0;
	*(p_FlashSector) = 0x01;
	
	/* command set exit */
	*((uint_16 *)base_address_ptr) = 0x0090; 
    *((uint_16 *)base_address_ptr) = 0x0000; 
     
    /* reset device */
    *((uint_16 *)base_address_ptr) = FLASH_RESET_CMD;

}
/*******************************************************************************
 * Function:        Flash_SectorErase
 *
 * Description:     erase a sector of the flash
 *
 * Returns:         Error Code
 *
 * Notes:
 *
 *******************************************************************************/
uint_8 Flash_SectorErase(uint_8 *p_FlashSector)
{
	volatile uint_16 * sect16_ptr;
	uint_8  returnCode = FLASH_READY;
	uint_16 tmp1;
	
	sect16_ptr = (volatile uint_16 *)p_FlashSector;

	
	/* Unprotect flash */
	unprotect_sector(p_FlashSector);
	
	/* Bus cyle 1 &2:Unlock Flash */
    *( sect16_ptr + 0x555 ) = 0x00AA;
    *( sect16_ptr + 0x2AA ) = 0x0055;

	/* Bus cyle 3:Set up command */	
     *( sect16_ptr + 0x555 ) = 0x0080;
	
	/* Bus cyle 4 &5: Unlock Flash */
     *( sect16_ptr + 0x555 ) = 0x00AA;
     *( sect16_ptr +0x2AA ) = 0x0055;
	
	/* Bus cyle 6: Erase sector */
	 *( sect16_ptr )    = 0x0030;   
		
	/* wait, until DQ3 = 0 */ 
	 tmp1 = *sect16_ptr; 
	while(!(tmp1 & DQ3))
	{      
          tmp1 = *sect16_ptr;   
    }
   
    /* Check the erase operation */
    returnCode = test_erase_cmd(p_FlashSector, (uint_16)0xFFFF);
    
    return returnCode;
}


/*******************************************************************************
 * Function:        Flash_ByteProgram
 *
 * Description:     byte program the flash
 *
 * Returns:         Error Code
 *
 * Notes:
 *
 *******************************************************************************/
uint_8 Flash_ByteProgram( uint_8 *to_ptr, uint_8 *from_ptr, int size )
	
{
  	volatile uint_16_ptr  base16_ptr;
  	uint_8                 result = FLASH_READY;

   	uint_16                 temp_data = 0xFFFF;
   	uint_8 					* temp_data_ptr;
    uint_8                  byte_data_counter = 0;
 
      
  	/* set the flash base address */
  	base16_ptr = (uint_16_ptr)S28WS128_BASE_ADDR; 
  	
  	temp_data_ptr =(uint_8*)  &temp_data;

  	/* we have data to write */
  	while (size) 
  	{
     	/* read old data to write word */
      	temp_data = *(uint_16_ptr)to_ptr;
     	/* move data to write word byte by byte */
    	while( byte_data_counter < WS_BYTES_IN_WORD && size		)
    	{
        	*(uint_8*)(temp_data_ptr+byte_data_counter) = *from_ptr++;
        	byte_data_counter++;
       		size--;
     	}
	 	
	    /* unlock flash */
	    *( base16_ptr + 0x555 ) = 0x00AA;
	    *( base16_ptr + 0x2AA ) = 0x0055;
	    /* Write command */            
	    *( base16_ptr + 0x555 ) = 0x00A0;
	    /* write value */        
	    *(uint_16 *)to_ptr = temp_data;     

	    /* test if the write operation complete */
	    result = test_program_cmd(to_ptr, temp_data);
	    /* if write command failed, exit write command */ 
	    if(result != FLASH_READY){
	        break;
	    }
	     byte_data_counter = 0;
	     temp_data = 0xFFFF;
	     to_ptr += WS_BYTES_IN_WORD;
  }/* Endwhile */

	return result; 
}
