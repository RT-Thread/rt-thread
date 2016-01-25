/**
  ******************************************************************************
  * @file    stm32469i_discovery_eeprom.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    29-September-2015
  * @brief   This file provides a set of functions needed to manage an I2C M24LR64 
  *          EEPROM memory.
  *          To be able to use this driver, the switch EE_M24LR64 must be defined
  *          in your toolchain compiler preprocessor
  *          
  *          =================================================================== 
  *          Notes:
  *           - This driver is intended for STM32F4xx families devices only. 
  *           - The I2C EEPROM memory (M24LR64) is available on separate daughter 
  *             board ANT7-M24LR-A, which is not provided with the STM32469I-Discovery
  *             board.
  *             To use this driver you have to connect the ANT7-M24LR-A to CN11
  *             connector of STM32469I-Discovery board.
  *          ===================================================================
  *              
  *          It implements a high level communication layer for read and write 
  *          from/to this memory. The needed STM32F4xx hardware resources (I2C and 
  *          GPIO) are defined in stm32469i_discovery.h file, and the initialization is
  *          performed in EEPROM_IO_Init() function declared in stm32469i_discovery.c
  *          file.
  *          You can easily tailor this driver to any other development board, 
  *          by just adapting the defines for hardware resources and 
  *          EEPROM_IO_Init() function. 
  *        
  *          @note In this driver, basic read and write functions (BSP_EEPROM_ReadBuffer() 
  *                and BSP_EEPROM_WritePage()) use DMA mode to perform the data 
  *                transfer to/from EEPROM memory.
  *
  *         @note   Regarding BSP_EEPROM_WritePage(), it is a optimized function to perform
  *                small write (less than 1 page) BUT The number of bytes (combined to write start address) must not 
  *                cross the EEPROM page boundary. This function can only write into
  *                the boundaries of an EEPROM page.
  *                This function doesn't check on boundaries condition (in this driver 
  *                the function BSP_EEPROM_WriteBuffer() which calls BSP_EEPROM_WritePage() is 
  *                responsible of checking on Page boundaries).
  * 
  *             
  *     +-----------------------------------------------------------------+
  *     |               Pin assignment for M24LR64 EEPROM                 |
  *     +---------------------------------------+-----------+-------------+
  *     |  STM32F4xx I2C Pins                   |   EEPROM  |   Pin       |
  *     +---------------------------------------+-----------+-------------+
  *     | .                                     |   E0(GND) |    1  (0V)  |
  *     | .                                     |   AC0     |    2        |
  *     | .                                     |   AC1     |    3        |
  *     | .                                     |   VSS     |    4  (0V)  |
  *     | SDA                                   |   SDA     |    5        |
  *     | SCL                                   |   SCL     |    6        |
  *     | .                                     |   E1(GND) |    7  (0V)  |
  *     | .                                     |   VDD     |    8 (3.3V) |
  *     +---------------------------------------+-----------+-------------+
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32469i_discovery_eeprom.h"

/** @addtogroup BSP
  * @{
  */
  
/** @addtogroup STM32469I-Discovery
  * @{
  */ 
  
/** @addtogroup STM32469I-Discovery_EEPROM
  * @brief This file includes the I2C EEPROM driver of STM32469I-Discovery board.
  * @{
  */ 

/** @defgroup STM32469I-Discovery_EEPROM_Private_Types STM32469I Discovery Eeprom Private Types
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32469I-Discovery_EEPROM_Private_Defines STM32469I Discovery Eeprom Private Defines
  * @{
  */  
/**
  * @}
  */ 

/** @defgroup STM32469I-Discovery_EEPROM_Private_Macros STM32469I Discovery Eeprom Private Macros
  * @{
  */
/**
  * @}
  */ 
  
/** @defgroup STM32469I-Discovery_EEPROM_Private_Variables STM32469I Discovery Eeprom Private Variables
  * @{
  */
__IO uint16_t EEPROMAddress = 0;
__IO uint32_t EEPROMTimeout = EEPROM_READ_TIMEOUT;
__IO uint16_t EEPROMDataRead;
__IO uint8_t  EEPROMDataWrite;
/**
  * @}
  */ 

/** @defgroup STM32469I-Discovery_EEPROM_Private_Function_Prototypes STM32469I Discovery Eeprom Private Prototypes
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32469I-Discovery_EEPROM_Private_Functions STM32469I Discovery Eeprom Private Functions
  * @{
  */ 

/**
  * @brief  Initializes peripherals used by the I2C EEPROM driver.
  * 
  * @note   There are 2 different versions of M24LR64 (A01 & A02).
  *             Then try to connect on 1st one (EEPROM_I2C_ADDRESS_A01) 
  *             and if problem, check the 2nd one (EEPROM_I2C_ADDRESS_A02)
  * @retval EEPROM_OK (0) if operation is correctly performed, else return value 
  *         different from EEPROM_OK (0)
  */
uint32_t BSP_EEPROM_Init(void)
{ 
  /* I2C Initialization */
  EEPROM_IO_Init();
  
  /* Select the EEPROM address for A01 and check if OK */
  EEPROMAddress = EEPROM_I2C_ADDRESS_A01;
  if(EEPROM_IO_IsDeviceReady(EEPROMAddress, EEPROM_MAX_TRIALS) != HAL_OK) 
  {
    /* Select the EEPROM address for A02 and check if OK */
    EEPROMAddress = EEPROM_I2C_ADDRESS_A02;
    if(EEPROM_IO_IsDeviceReady(EEPROMAddress, EEPROM_MAX_TRIALS) != HAL_OK)
    {
      return EEPROM_FAIL;
    }
  }
  return EEPROM_OK;
}

/**
  * @brief  DeInitializes the EEPROM.
  * @retval EEPROM state
  */
uint8_t BSP_EEPROM_DeInit(void)
{ 
  /* I2C won't be disabled because common to other functionalities */
  return EEPROM_OK;
}

/**
  * @brief  Reads a block of data from the EEPROM.
  * @param  pBuffer: pointer to the buffer that receives the data read from 
  *         the EEPROM.
  * @param  ReadAddr: EEPROM's internal address to start reading from.
  * @param  NumByteToRead: pointer to the variable holding number of bytes to 
  *         be read from the EEPROM.
  * 
  *        @note The variable pointed by NumByteToRead is reset to 0 when all the 
  *              data are read from the EEPROM. Application should monitor this 
  *              variable in order know when the transfer is complete.
  * 
  * @retval EEPROM_OK (0) if operation is correctly performed, else return value 
  *         different from EEPROM_OK (0) or the timeout user callback.
  */
uint32_t BSP_EEPROM_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t* NumByteToRead)
{  
  uint32_t buffersize = *NumByteToRead;
  
  /* Set the pointer to the Number of data to be read. This pointer will be used 
     by the DMA Transfer Completer interrupt Handler in order to reset the 
     variable to 0. User should check on this variable in order to know if the 
     DMA transfer has been complete or not. */
  EEPROMDataRead = *NumByteToRead;
  
  if(EEPROM_IO_ReadData(EEPROMAddress, ReadAddr, pBuffer, buffersize) != HAL_OK)
  {
    BSP_EEPROM_TIMEOUT_UserCallback();
    return EEPROM_FAIL;
  }

  /* If all operations OK, return EEPROM_OK (0) */
  return EEPROM_OK;
}

/**
  * @brief  Writes more than one byte to the EEPROM with a single WRITE cycle.
  *
  * @note   The number of bytes (combined to write start address) must not 
  *         cross the EEPROM page boundary. This function can only write into
  *         the boundaries of an EEPROM page.
  *         This function doesn't check on boundaries condition (in this driver 
  *         the function BSP_EEPROM_WriteBuffer() which calls BSP_EEPROM_WritePage() is 
  *         responsible of checking on Page boundaries).
  * 
  * @param  pBuffer: pointer to the buffer containing the data to be written to 
  *         the EEPROM.
  * @param  WriteAddr: EEPROM's internal address to write to.
  * @param  NumByteToWrite: pointer to the variable holding number of bytes to 
  *         be written into the EEPROM. 
  * 
  *        @note The variable pointed by NumByteToWrite is reset to 0 when all the 
  *              data are written to the EEPROM. Application should monitor this 
  *              variable in order know when the transfer is complete.
  * 
  *        @note This function just configure the communication and enable the DMA 
  *              channel to transfer data. Meanwhile, the user application may perform 
  *              other tasks in parallel.
  * 
  * @retval EEPROM_OK (0) if operation is correctly performed, else return value 
  *         different from EEPROM_OK (0) or the timeout user callback.
  */
uint32_t BSP_EEPROM_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t* NumByteToWrite)
{ 
  uint32_t buffersize = *NumByteToWrite;
  uint32_t status = EEPROM_OK;
  
  /* Set the pointer to the Number of data to be written. This pointer will be used 
      by the DMA Transfer Completer interrupt Handler in order to reset the 
      variable to 0. User should check on this variable in order to know if the 
      DMA transfer has been complete or not. */
  EEPROMDataWrite = *NumByteToWrite;  
  
  if(EEPROM_IO_WriteData(EEPROMAddress, WriteAddr, pBuffer, buffersize) != HAL_OK)
  {
    BSP_EEPROM_TIMEOUT_UserCallback();
    status = EEPROM_FAIL;
  }
  
  if(BSP_EEPROM_WaitEepromStandbyState() != EEPROM_OK) 
  {
    return EEPROM_FAIL;
  }
  
  /* If all operations OK, return EEPROM_OK (0) */
  return status;
}

/**
  * @brief  Writes buffer of data to the I2C EEPROM.
  * @param  pBuffer: pointer to the buffer  containing the data to be written 
  *         to the EEPROM.
  * @param  WriteAddr: EEPROM's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the EEPROM.
  * @retval EEPROM_OK (0) if operation is correctly performed, else return value 
  *         different from EEPROM_OK (0) or the timeout user callback.
  */
uint32_t BSP_EEPROM_WriteBuffer(uint8_t *pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
  uint16_t numofpage = 0, numofsingle = 0, count = 0;
  uint16_t addr = 0;
  uint8_t  dataindex = 0;
  uint32_t status = EEPROM_OK;

  addr = WriteAddr % EEPROM_PAGESIZE;
  count = EEPROM_PAGESIZE - addr;
  numofpage =  NumByteToWrite / EEPROM_PAGESIZE;
  numofsingle = NumByteToWrite % EEPROM_PAGESIZE;
 
  /* If WriteAddr is EEPROM_PAGESIZE aligned */
  if(addr == 0) 
  {
    /* If NumByteToWrite < EEPROM_PAGESIZE */
    if(numofpage == 0) 
    {
      /* Store the number of data to be written */
      dataindex = numofsingle;
      /* Start writing data */
      status = BSP_EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
      if(status != EEPROM_OK)
      {
        return status;
      }
    }
    /* If NumByteToWrite > EEPROM_PAGESIZE */
    else  
    {
      while(numofpage--)
      {
        /* Store the number of data to be written */
        dataindex = EEPROM_PAGESIZE;        
        status = BSP_EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
        
        WriteAddr +=  EEPROM_PAGESIZE;
        pBuffer += EEPROM_PAGESIZE;
      }
      
      if(numofsingle!=0)
      {
        /* Store the number of data to be written */
        dataindex = numofsingle;          
        status = BSP_EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
      }
    }
  }
  /* If WriteAddr is not EEPROM_PAGESIZE aligned */
  else 
  {
    /* If NumByteToWrite < EEPROM_PAGESIZE */
    if(numofpage== 0) 
    {
      /* If the number of data to be written is more than the remaining space 
      in the current page: */
      if(NumByteToWrite > count)
      {
        /* Store the number of data to be written */
        dataindex = count;        
        /* Write the data contained in same page */
        status = BSP_EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
        
        /* Store the number of data to be written */
        dataindex = (NumByteToWrite - count);          
        /* Write the remaining data in the following page */
        status = BSP_EEPROM_WritePage((uint8_t*)(pBuffer + count), (WriteAddr + count), (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
      }      
      else      
      {
        /* Store the number of data to be written */
        dataindex = numofsingle;         
        status = BSP_EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
      }     
    }
    /* If NumByteToWrite > EEPROM_PAGESIZE */
    else
    {
      NumByteToWrite -= count;
      numofpage =  NumByteToWrite / EEPROM_PAGESIZE;
      numofsingle = NumByteToWrite % EEPROM_PAGESIZE;
      
      if(count != 0)
      {  
        /* Store the number of data to be written */
        dataindex = count;         
        status = BSP_EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
        WriteAddr += count;
        pBuffer += count;
      } 
      
      while(numofpage--)
      {
        /* Store the number of data to be written */
        dataindex = EEPROM_PAGESIZE;          
        status = BSP_EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
        WriteAddr +=  EEPROM_PAGESIZE;
        pBuffer += EEPROM_PAGESIZE;  
      }
      if(numofsingle != 0)
      {
        /* Store the number of data to be written */
        dataindex = numofsingle;           
        status = BSP_EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t*)(&dataindex));
        if(status != EEPROM_OK)
        {
          return status;
        }
      }
    }
  }  
                                   
  /* If all operations OK, return EEPROM_OK (0) */
  return EEPROM_OK;
}

/**
  * @brief  Wait for EEPROM Standby state.
  * 
  * @note  This function allows to wait and check that EEPROM has finished the 
  *        last operation. It is mostly used after Write operation: after receiving
  *        the buffer to be written, the EEPROM may need additional time to actually
  *        perform the write operation. During this time, it doesn't answer to
  *        I2C packets addressed to it. Once the write operation is complete
  *        the EEPROM responds to its address.
  * 
  * @retval EEPROM_OK (0) if operation is correctly performed, else return value 
  *         different from EEPROM_OK (0) or the timeout user callback.
  */
uint32_t BSP_EEPROM_WaitEepromStandbyState(void)      
{
  /* Check if the maximum allowed number of trials has bee reached */
  if(EEPROM_IO_IsDeviceReady(EEPROMAddress, EEPROM_MAX_TRIALS) != HAL_OK)
  {
    /* If the maximum number of trials has been reached, exit the function */
    BSP_EEPROM_TIMEOUT_UserCallback();
    return EEPROM_TIMEOUT;
  }
  return EEPROM_OK;
}

/**
  * @brief  Basic management of the timeout situation.
  */
__weak void BSP_EEPROM_TIMEOUT_UserCallback(void)
{
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
