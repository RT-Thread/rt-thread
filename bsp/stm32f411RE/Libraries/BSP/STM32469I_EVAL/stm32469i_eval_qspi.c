/**
  ******************************************************************************
  * @file    stm32469i_eval_qspi.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    29-September-2015
  * @brief   This file includes a standard driver for the N25Q256A QSPI 
  *          memory mounted on STM32469I-EVAL board.
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================  
  [..]
   (#) This driver is used to drive the S25FL512SAGMFI01 and N25Q512A QSPI external 
       memory mounted on STM32469I-EVAL evaluation board.
       
   (#) This driver need a specific component driver (FL512SAGMFI01 and N25Q512A) to be included with.

   (#) Initialization steps:
       (++) Initialize the QPSI external memory using the BSP_QSPI_Init() function. This 
            function includes the MSP layer hardware resources initialization and the
            QSPI interface with the external memory.
  
   (#) QSPI memory operations
       (++) QSPI memory can be accessed with read/write operations once it is
            initialized.
            Read/write operation can be performed with AHB access using the functions
            BSP_QSPI_Read()/BSP_QSPI_Write(). 
       (++) The function BSP_QSPI_GetInfo() returns the configuration of the QSPI memory. 
            (see the QSPI memory data sheet)
       (++) Perform erase block operation using the function BSP_QSPI_Erase_Block() and by
            specifying the block address. You can perform an erase operation of the whole 
            chip by calling the function BSP_QSPI_Erase_Chip(). 
       (++) The function BSP_QSPI_GetStatus() returns the current status of the QSPI memory. 
            (see the QSPI memory data sheet)
  @endverbatim
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
#include "stm32469i_eval_qspi.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32469I_EVAL
  * @{
  */ 
  
/** @defgroup STM32469I_EVAL_QSPI STM32469I_EVAL QSPI
  * @{
  */ 


/* Private variables ---------------------------------------------------------*/
#define JEDEC_MANUF_ID_MICRON   ((uint8_t) 0x20)
#define JEDEC_MANUF_ID_SPANSION ((uint8_t) 0x01)
/** @defgroup STM32469I_EVAL_QSPI_Private_Variables Private Variables
  * @{
  */       
QSPI_HandleTypeDef QSPIHandle;
QSPI_InfoTypeDef QspiInfo;

/**
  * @}
  */ 



/* Private functions ---------------------------------------------------------*/
    
/** @defgroup STM32469I_EVAL_QSPI_Private_Functions QSPI Private Functions
  * @{
  */ 
static uint8_t QSPI_ResetMemory          (QSPI_HandleTypeDef *hqspi);
static uint8_t QSPI_EnterFourBytesAddress(QSPI_HandleTypeDef *hqspi);
static uint8_t QSPI_DummyCyclesCfg       (QSPI_HandleTypeDef *hqspi);
static uint8_t QSPI_WriteEnable          (QSPI_HandleTypeDef *hqspi);
static uint8_t QSPI_AutoPollingMemReady  (QSPI_HandleTypeDef *hqspi, uint32_t Timeout);
static uint8_t QSPI_ReadID               (QSPI_InfoTypeDef *pqspi_info);

/**
  * @}
  */
    
/** @defgroup STM32469I_EVAL_QSPI_Exported_Functions QSPI Exported Functions
  * @{
  */ 

/**
  * @brief  Initializes the QSPI interface.
  * @retval QSPI memory status
  */
uint8_t BSP_QSPI_Init(void)
{ 
  QSPIHandle.Instance = QUADSPI;

  /* Call the DeInit function to reset the driver */
  if (HAL_QSPI_DeInit(&QSPIHandle) != HAL_OK)
  {
    return QSPI_ERROR;
  }
        
  /* System level initialization */
  BSP_QSPI_MspInit(&QSPIHandle, NULL);
  
  /* QSPI initialization */
  /* Init typedef is the same for both S25FL512S and N25Q512A memories, as they have the same FLASH size */
  QSPIHandle.Init.ClockPrescaler     = 1; /* QSPI Freq= 180 MHz / (1+1) = 90 MHz */
  QSPIHandle.Init.FifoThreshold      = 1;
  QSPIHandle.Init.SampleShifting     = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  QSPIHandle.Init.FlashSize          = POSITION_VAL(S25FL512S_FLASH_SIZE) - 1; /* same size on both memory types */
  QSPIHandle.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_2_CYCLE;
  QSPIHandle.Init.ClockMode          = QSPI_CLOCK_MODE_0;
  QSPIHandle.Init.FlashID            = QSPI_FLASH_ID_1;
  QSPIHandle.Init.DualFlash          = QSPI_DUALFLASH_DISABLE;

  if (HAL_QSPI_Init(&QSPIHandle) != HAL_OK)
  {
    return QSPI_ERROR;
  }

  /* Detect the memory ID */
  if (QSPI_ReadID(&QspiInfo) != QSPI_OK)
  {
    return QSPI_NOT_SUPPORTED;
  }
  
  /* QSPI memory reset */
  if (QSPI_ResetMemory(&QSPIHandle) != QSPI_OK)
  {
    return QSPI_NOT_SUPPORTED;
  }
 
  /* Set the QSPI memory in 4-bytes address mode */
  if (QSPI_EnterFourBytesAddress(&QSPIHandle) != QSPI_OK)
  {
    return QSPI_NOT_SUPPORTED;
  }
 
  /* Configuration of the dummy cucles on QSPI memory side */
  if (QSPI_DummyCyclesCfg(&QSPIHandle) != QSPI_OK)
  {
    return QSPI_NOT_SUPPORTED;
  }

  return QSPI_OK;
}

/**
  * @brief  De-Initializes the QSPI interface.
  * @retval QSPI memory status
  */
uint8_t BSP_QSPI_DeInit(void)
{ 
  QSPIHandle.Instance = QUADSPI;

  /* Call the DeInit function to reset the driver */
  if (HAL_QSPI_DeInit(&QSPIHandle) != HAL_OK)
  {
    return QSPI_ERROR;
  }
        
  /* System level De-initialization */
  BSP_QSPI_MspDeInit(&QSPIHandle, NULL);
  
  return QSPI_OK;
}

/**
  * @brief  Reads an amount of data from the QSPI memory.
  * @param  pData: Pointer to data to be read
  * @param  ReadAddr: Read start address
  * @param  Size: Size of data to read    
  * @retval QSPI memory status
  */
uint8_t BSP_QSPI_Read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size)
{
  QSPI_CommandTypeDef s_command;

  /* Initialize the read command */
  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = QUAD_OUT_FAST_READ_CMD; /* same value on both memory types */
  s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
  s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
  s_command.Address           = ReadAddr;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_4_LINES;
  s_command.DummyCycles       = QspiInfo.DummyCyclesRead;
  s_command.NbData            = Size;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
  
  /* Configure the command */
  if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return QSPI_ERROR;
  }
  
  /* Reception of the data */
  if (HAL_QSPI_Receive(&QSPIHandle, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return QSPI_ERROR;
  }

  return QSPI_OK;
}

/**
  * @brief  Writes an amount of data to the QSPI memory.
  * @param  pData: Pointer to data to be written
  * @param  WriteAddr: Write start address
  * @param  Size: Size of data to write    
  * @retval QSPI memory status
  */
uint8_t BSP_QSPI_Write(uint8_t* pData, uint32_t WriteAddr, uint32_t Size)
{
  QSPI_CommandTypeDef s_command;
  uint32_t end_addr, current_size, current_addr;
  
  /* Calculation of the size between the write address and the end of the page */
  current_addr = 0;

  while (current_addr <= WriteAddr)
  {
    current_addr += QspiInfo.ProgPageSize;
  }
  current_size = current_addr - WriteAddr;

  /* Check if the size of the data is less than the remaining place in the page */
  if (current_size > Size)
  {
    current_size = Size;
  }

  /* Initialize the adress variables */
  current_addr = WriteAddr;
  end_addr = WriteAddr + Size;

  /* Initialize the program command */
  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = QUAD_IN_FAST_PROG_CMD; /* same value on both memory types */
  s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
  s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_4_LINES;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
  
  /* Perform the write page by page */
  do
  {
    s_command.Address = current_addr;
    s_command.NbData  = current_size;

    /* Enable write operations */
    if (QSPI_WriteEnable(&QSPIHandle) != QSPI_OK)
    {
      return QSPI_ERROR;
    }
    
    /* Configure the command */
    if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }
    
    /* Transmission of the data */
    if (HAL_QSPI_Transmit(&QSPIHandle, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }
    
    /* Configure automatic polling mode to wait for end of program */  
    if (QSPI_AutoPollingMemReady(&QSPIHandle, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
    {
      return QSPI_ERROR;
    }
    
    /* Update the address and size variables for next page programming */
    current_addr += current_size;
    pData += current_size;
    current_size = ((current_addr + QspiInfo.ProgPageSize) > end_addr) ? (end_addr - current_addr) : QspiInfo.ProgPageSize;
  } while (current_addr < end_addr);
  
  return QSPI_OK;
}

/**
  * @brief  Erases the specified block of the QSPI memory. 
  * @param  BlockAddress: Block address to erase  
  * @retval QSPI memory status
  */
uint8_t BSP_QSPI_Erase_Block(uint32_t BlockAddress)
{
  QSPI_CommandTypeDef s_command;

  /* Initialize the erase command */
  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = SECTOR_ERASE_CMD; /* same value on both memory types */
  s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
  s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
  s_command.Address           = BlockAddress;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  /* Enable write operations */
  if (QSPI_WriteEnable(&QSPIHandle) != QSPI_OK)
  {
    return QSPI_ERROR;
  }

  /* Send the command */
  if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return QSPI_ERROR;
  }
  
  /* Configure automatic polling mode to wait for end of erase */  
  if (QSPI_AutoPollingMemReady(&QSPIHandle, QspiInfo.SectorEraseMaxTime) != QSPI_OK)
  {
    return QSPI_ERROR;
  }

  return QSPI_OK;
}

/**
  * @brief  Erases the entire QSPI memory.
  * @retval QSPI memory status
  */
uint8_t BSP_QSPI_Erase_Chip(void)
{
  QSPI_CommandTypeDef s_command;

  /* Initialize the erase command */
  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = BULK_ERASE_CMD; /* same value on both memory types */
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  /* Enable write operations */
  if (QSPI_WriteEnable(&QSPIHandle) != QSPI_OK)
  {
    return QSPI_ERROR;
  }

  /* Send the command */
  if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return QSPI_ERROR;
  }
  
  /* Configure automatic polling mode to wait for end of erase */  
  if (QSPI_AutoPollingMemReady(&QSPIHandle, QspiInfo.BulkEraseMaxTime) != QSPI_OK)
  {
    return QSPI_ERROR;
  }

  return QSPI_OK;
}

/**
  * @brief  Reads current status of the QSPI memory.
  * @retval QSPI memory status
  */
uint8_t BSP_QSPI_GetStatus(void)
{
  QSPI_CommandTypeDef s_command;
  uint8_t reg1, reg2;

  if (QspiInfo.ManufID == QSPI_N25Q512A)
  {
    /* Initialize the read flag status register command */
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = READ_FLAG_STATUS_REG_CMD; /* same value on both memory types */
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_1_LINE;
    s_command.DummyCycles       = 0;
    s_command.NbData            = 1;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    /* Configure the command */
    if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Reception of the data */
    if (HAL_QSPI_Receive(&QSPIHandle, &reg1, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Check the value of the register */
    if ((reg1 & (N25Q512A_FSR_PRERR | N25Q512A_FSR_VPPERR | N25Q512A_FSR_PGERR | N25Q512A_FSR_ERERR)) != 0)
    {
      return QSPI_ERROR;
    }
    else if ((reg1 & (N25Q512A_FSR_PGSUS | N25Q512A_FSR_ERSUS)) != 0)
    {
      return QSPI_SUSPENDED;
    }
    else if ((reg1 & N25Q512A_FSR_READY) != 0)
    {
      return QSPI_OK;
    }
    else
    {
      return QSPI_BUSY;
    }
  }
  else
  {
    /* Initialize the read flag status register1 command */
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = S25FL512S_READ_STATUS_REG1_CMD;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_1_LINE;
    s_command.DummyCycles       = 0;
    s_command.NbData            = 1;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    /* Configure the command */
    if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Reception of the data */
    if (HAL_QSPI_Receive(&QSPIHandle, &reg1, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }


    /* Initialize the read flag status register2 command */
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = S25FL512S_READ_STATUS_REG2_CMD;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_1_LINE;
    s_command.DummyCycles       = 0;
    s_command.NbData            = 1;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
  
    /* Configure the command */
    if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }
  
    /* Reception of the data */
    if (HAL_QSPI_Receive(&QSPIHandle, &reg2, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Check the value of the register */
    if ((reg1 & (S25FL512S_SR1_ERERR | S25FL512S_SR1_PGERR | S25FL512S_SR1_SRWD )) != 0)
    {
      return QSPI_ERROR;
    }
    if ((reg1 & (S25FL512S_SR1_BP0 | S25FL512S_SR1_BP1 | S25FL512S_SR1_BP2)) != 0)
    {
      return QSPI_PROTECTED;
    }

    if ((reg2 & (S25FL512S_SR2_PS | S25FL512S_SR2_ES)) != 0)
    {
      return QSPI_SUSPENDED;
    }
    if ((reg1 & (S25FL512S_SR1_WIP | S25FL512S_SR1_WREN)) == 0)
    {
      return QSPI_OK;
    }
    else
    {
      return QSPI_BUSY;
    }
  }
}

/**
  * @brief  Reads the configuration of the memory and fills QspiInfo struct
  * @param  pInfo pointer to Info structure
  * @retval QSPI memory status
  */
uint8_t BSP_QSPI_GetInfo(QSPI_InfoTypeDef* pInfo)
{

  if (QSPI_ReadID(pInfo) != QSPI_OK)
  {
    return QSPI_ERROR;
  }

  return QSPI_OK;
}

/**
* @brief Configure the QSPI in memory-mapped mode
* @param None 
* @retval QSPI memory status
*/
uint8_t BSP_QSPI_MemoryMappedMode(void)
{
  QSPI_CommandTypeDef s_command;
  QSPI_MemoryMappedTypeDef s_mem_mapped_cfg;

  /* Configure the command for the read instruction */
  s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction = QUAD_OUT_FAST_READ_CMD;
  s_command.AddressMode = QSPI_ADDRESS_1_LINE;
  s_command.AddressSize = QSPI_ADDRESS_32_BITS;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode = QSPI_DATA_4_LINES;
  s_command.DummyCycles = QspiInfo.DummyCyclesRead;
  s_command.DdrMode = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

  /* Configure the memory mapped mode */
  s_mem_mapped_cfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
  s_mem_mapped_cfg.TimeOutPeriod = 0; //1;

  if (HAL_QSPI_MemoryMapped(&QSPIHandle, &s_command, &s_mem_mapped_cfg) != HAL_OK)
  {
    return QSPI_ERROR;
  }

  return QSPI_OK;
}

/**
  * @}
  */

/** @addtogroup STM32446E_EVAL_QSPI_Private_Functions 
  * @{
  */ 

/**
  * @brief QSPI MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  *           - NVIC configuration for QSPI interrupt
  * @retval None
  */
__weak void BSP_QSPI_MspInit(QSPI_HandleTypeDef *hqspi, void *Params)
{
  GPIO_InitTypeDef gpio_init_structure;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable the QuadSPI memory interface clock */
  QSPI_CLK_ENABLE();
  /* Reset the QuadSPI memory interface */
  QSPI_FORCE_RESET();
  QSPI_RELEASE_RESET();
  /* Enable GPIO clocks */
  QSPI_CS_GPIO_CLK_ENABLE();
  QSPI_DX_CLK_GPIO_CLK_ENABLE();

  /*##-2- Configure peripheral GPIO ##########################################*/
  /* QSPI CS GPIO pin configuration  */
  gpio_init_structure.Pin       = QSPI_CS_PIN;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF10_QSPI;
  HAL_GPIO_Init(QSPI_CS_GPIO_PORT, &gpio_init_structure);

  /* QSPI CLK GPIO pin configuration  */
  gpio_init_structure.Pin       = QSPI_CLK_PIN;
  gpio_init_structure.Pull      = GPIO_NOPULL;
  gpio_init_structure.Alternate = GPIO_AF9_QSPI;
  HAL_GPIO_Init(QSPI_CLK_GPIO_PORT, &gpio_init_structure);

  /* QSPI D0 and D1 GPIO pin configuration  */
  gpio_init_structure.Pin       = (QSPI_D0_PIN | QSPI_D1_PIN);
  gpio_init_structure.Alternate = GPIO_AF10_QSPI;
  HAL_GPIO_Init(QSPI_DX_GPIO_PORT, &gpio_init_structure);

  /* QSPI D2 and D3 GPIO pin configuration  */
  gpio_init_structure.Pin       = (QSPI_D2_PIN | QSPI_D3_PIN) ;
  gpio_init_structure.Alternate = GPIO_AF9_QSPI;
  HAL_GPIO_Init(QSPI_DX_GPIO_PORT, &gpio_init_structure);

  /*##-3- Configure the NVIC for QSPI #########################################*/
  /* NVIC configuration for QSPI interrupt */
  HAL_NVIC_SetPriority(QUADSPI_IRQn, 0x0F, 0);
  HAL_NVIC_EnableIRQ(QUADSPI_IRQn);

}

/**
  * @brief QSPI MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @retval None
  */
__weak void BSP_QSPI_MspDeInit(QSPI_HandleTypeDef *hqspi, void *Params)
{
  /*##-1- Disable the NVIC for QSPI ###########################################*/
  HAL_NVIC_DisableIRQ(QUADSPI_IRQn);

  /*##-2- Disable peripherals and GPIO Clocks ################################*/
  /* De-Configure QSPI pins */
  HAL_GPIO_DeInit(QSPI_CS_GPIO_PORT, QSPI_CS_PIN);
  HAL_GPIO_DeInit(QSPI_CLK_GPIO_PORT, QSPI_CLK_PIN);
  HAL_GPIO_DeInit(QSPI_DX_GPIO_PORT, QSPI_D0_PIN);
  HAL_GPIO_DeInit(QSPI_DX_GPIO_PORT, QSPI_D1_PIN);
  HAL_GPIO_DeInit(QSPI_DX_GPIO_PORT, QSPI_D2_PIN);
  HAL_GPIO_DeInit(QSPI_DX_GPIO_PORT, QSPI_D3_PIN);

  /*##-3- Reset peripherals ##################################################*/
  /* Reset the QuadSPI memory interface */
  QSPI_FORCE_RESET();
  QSPI_RELEASE_RESET();

  /* Disable the QuadSPI memory interface clock */
  QSPI_CLK_DISABLE();
}

/**
  * @brief  This function reset the QSPI memory.
  * @param  hqspi: QSPI handle
  * @retval None
  */
static uint8_t QSPI_ResetMemory(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef s_command;
  uint32_t instruction1, instruction2;

  /* Command ID differs between N25Q512A and S25FL512S memories */
  if (QspiInfo.ManufID == QSPI_N25Q512A)
  {
    instruction1 = RESET_ENABLE_CMD;
    instruction2 = RESET_MEMORY_CMD;
  }
  else
  {
    instruction1 = S25FL512S_MODE_BIT_RESET_CMD;
    instruction2 = S25FL512S_SOFTWARE_RESET_CMD;
  }

  /* Initialize the Mode Bit Reset command */
  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = instruction1;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  /* Send the command */
  if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return QSPI_ERROR;
  }

  /* Send the SW reset command */
  s_command.Instruction       = instruction2;
  if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return QSPI_ERROR;
  }

  /* Configure automatic polling mode to wait the memory is ready */  
  if (QSPI_AutoPollingMemReady(&QSPIHandle, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
  {
    return QSPI_ERROR;
  }
  return QSPI_OK;
}

/**
  * @brief  This function set the QSPI memory in 4-byte address mode
  * @param  hqspi: QSPI handle
  * @retval None
  */
static uint8_t QSPI_EnterFourBytesAddress(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef s_command;
  uint8_t reg1;

  /* Command ID differs between N25Q512A and S25FL512S memories */
  if (QspiInfo.ManufID == QSPI_N25Q512A)
  {
    /* Initialize the command */
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = ENTER_4_BYTE_ADDR_MODE_CMD;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_NONE;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    /* Enable write operations */
    if (QSPI_WriteEnable(hqspi) != QSPI_OK)
    {
      return QSPI_ERROR;
    }

    /* Send the command */
    if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Configure automatic polling mode to wait the memory is ready */
    if (QSPI_AutoPollingMemReady(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
    {
      return QSPI_ERROR;
    }

    return QSPI_OK;
  }
  else
  {
    /* Initialize the read bank register command */
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = S25FL512S_READ_BANK_REG_CMD;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_1_LINE;
    s_command.DummyCycles       = 0;
    s_command.NbData            = 1;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    /* Configure the command */
    if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Reception of the data */
    if (HAL_QSPI_Receive(&QSPIHandle, &reg1, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Enable write operations */
    if (QSPI_WriteEnable(&QSPIHandle) != QSPI_OK)
    {
      return QSPI_ERROR;
    }

    /* Update Bank address register (with 4byte addressing bit) */
    s_command.Instruction = S25FL512S_WRITE_BANK_REG_CMD;
    MODIFY_REG(reg1, S25FL512S_BA_EXTADD, S25FL512S_BA_EXTADD);

    /* Configure the write volatile configuration register command */
    if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Transmission of the data Status Register 1 */
    if (HAL_QSPI_Transmit(&QSPIHandle, &reg1, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }
    return QSPI_OK;
  }
}

/**
  * @brief  This function configure the dummy cycles on memory side.
  * @param  hqspi: QSPI handle
  * @retval None
  */
static uint8_t QSPI_DummyCyclesCfg(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef s_command;
  uint8_t reg[2];
  /* Command ID differs between N25Q512A and S25FL512S memories */
  if (QspiInfo.ManufID == QSPI_N25Q512A)
  {
    /* Initialize the read volatile configuration register command */
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = READ_VOL_CFG_REG_CMD;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_1_LINE;
    s_command.DummyCycles       = 0;
    s_command.NbData            = 1;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    /* Configure the command */
    if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Reception of the data */
    if (HAL_QSPI_Receive(hqspi, &reg[0], HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Enable write operations */
    if (QSPI_WriteEnable(hqspi) != QSPI_OK)
    {
      return QSPI_ERROR;
    }

    /* Update volatile configuration register (with new dummy cycles) */
    s_command.Instruction = WRITE_VOL_CFG_REG_CMD;
    MODIFY_REG(reg[0], N25Q512A_VCR_NB_DUMMY, (N25Q512A_DUMMY_CYCLES_READ_QUAD << POSITION_VAL(N25Q512A_VCR_NB_DUMMY)));

    /* Configure the write volatile configuration register command */
    if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Transmission of the data */
    if (HAL_QSPI_Transmit(hqspi, &reg[0], HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }
  }
  else
  {
    /* Initialize the read configuration register command */
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = S25FL512S_READ_CONFIGURATION_REG1_CMD;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_1_LINE;
    s_command.DummyCycles       = 0;
    s_command.NbData            = 1;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    /* Configure the command */
    if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Reception of the data */
    if (HAL_QSPI_Receive(&QSPIHandle, &reg[1], HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Initialize the read status register1 command */
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = S25FL512S_READ_STATUS_REG1_CMD;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_1_LINE;
    s_command.DummyCycles       = 0;
    s_command.NbData            = 1;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    /* Configure the command */
    if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Reception of the data */
    if (HAL_QSPI_Receive(&QSPIHandle, &reg[0], HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Enable write operations */
    if (QSPI_WriteEnable(&QSPIHandle) != QSPI_OK)
    {
      return QSPI_ERROR;
    }

    /* Update configuration register (with new Latency Code) */
    s_command.Instruction       = S25FL512S_WRITE_STATUS_CMD_REG_CMD;
    s_command.NbData            = 2;
    MODIFY_REG(reg[1], S25FL512S_CR1_LC_MASK, S25FL512S_CR1_LC1);

    /* Configure the write volatile configuration register command */
    if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }

    /* Transmission of the data Status Register 1 */
    if (HAL_QSPI_Transmit(&QSPIHandle, reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      return QSPI_ERROR;
    }
  }
  return QSPI_OK;
}

/**
  * @brief  This function send a Write Enable and wait it is effective.
  * @param  hqspi: QSPI handle
  * @retval None
  */
static uint8_t QSPI_WriteEnable(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef     s_command;
  QSPI_AutoPollingTypeDef sConfig;

  /* Enable write operations */
  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = WRITE_ENABLE_CMD; /* equal on both memory types */
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_NONE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return QSPI_ERROR;
  }
  
  /* Configure automatic polling mode to wait for write enabling */  
  sConfig.Match           = S25FL512S_SR1_WREN;
  sConfig.Mask            = S25FL512S_SR1_WREN; /* equal on both memory types */
  sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 1;
  sConfig.Interval        = 0x10;
  sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

  s_command.Instruction    = READ_STATUS_REG_CMD; /* equal on both memory types */
  s_command.DataMode       = QSPI_DATA_1_LINE;

  if (HAL_QSPI_AutoPolling(&QSPIHandle, &s_command, &sConfig, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return QSPI_ERROR;
  }

  return QSPI_OK;
}

/**
  * @brief  This function read the SR of the memory and wait the EOP.
  * @param  hqspi: QSPI handle
  * @param  Timeout: timeout value before returning an error
  * @retval None
  */
static uint8_t QSPI_AutoPollingMemReady(QSPI_HandleTypeDef *hqspi, uint32_t Timeout)
{
  QSPI_CommandTypeDef     s_command;
  QSPI_AutoPollingTypeDef sConfig;

  /* Configure automatic polling mode to wait for memory ready */  
  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = READ_STATUS_REG_CMD; /* same value on both memory types */
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_1_LINE;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  sConfig.Match           = 0;
  sConfig.Mask            = S25FL512S_SR1_WIP; /* same value on both memory types */
  sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 1;
  sConfig.Interval        = 0x10;
  sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

  if (HAL_QSPI_AutoPolling(&QSPIHandle, &s_command, &sConfig, Timeout) != HAL_OK)
  {
    return QSPI_ERROR;
  }

  return QSPI_OK;
}

/**
  * @brief  This function reads the ID of the QSPI Memory and fills the info struct
  * @param  pqspi_info: pointer to the Info Typedef strcture
  * @retval None
  */
static uint8_t QSPI_ReadID(QSPI_InfoTypeDef *pqspi_info)
{
  QSPI_CommandTypeDef     s_command;
  uint8_t reg[6];

  /* Configure automatic polling mode to wait for memory ready */
  s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = READ_ID_CMD2; /* same value on both memory types */
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = QSPI_DATA_1_LINE;
  s_command.NbData            = 6;
  s_command.DummyCycles       = 0;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(&QSPIHandle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return QSPI_ERROR;
  }

  /* Reception of the data */
  if (HAL_QSPI_Receive(&QSPIHandle, reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return QSPI_ERROR;
  }

  /* Check the received ID of the QSPI Memory */
  if (reg[0] == JEDEC_MANUF_ID_MICRON)
  {
    pqspi_info->ManufID = QSPI_N25Q512A;
    pqspi_info->FlashSize = (reg[2]<<21) & 0xFFFFFFFF;
    pqspi_info->EraseSectorSize = N25Q512A_SECTOR_SIZE;
    pqspi_info->EraseSectorsNumber = (N25Q512A_FLASH_SIZE/N25Q512A_SECTOR_SIZE);
    pqspi_info->ProgPageSize = N25Q512A_PAGE_SIZE;
    pqspi_info->ProgPagesNumber = (N25Q512A_FLASH_SIZE/N25Q512A_PAGE_SIZE);
    pqspi_info->DummyCyclesRead = 10;
    pqspi_info->SectorEraseMaxTime = N25Q512A_SECTOR_ERASE_MAX_TIME;
    pqspi_info->BulkEraseMaxTime = N25Q512A_BULK_ERASE_MAX_TIME;
  }
  if (reg[0] == JEDEC_MANUF_ID_SPANSION)
  {
    pqspi_info->ManufID = QSPI_S25FL512S;
    pqspi_info->FlashSize = (reg[2]<<21) & 0xFFFFFFFF;
    pqspi_info->EraseSectorSize = S25FL512S_SECTOR_SIZE;
    pqspi_info->EraseSectorsNumber = (S25FL512S_FLASH_SIZE/S25FL512S_SECTOR_SIZE);
    pqspi_info->ProgPageSize = S25FL512S_PAGE_SIZE;
    pqspi_info->ProgPagesNumber = (S25FL512S_FLASH_SIZE/S25FL512S_PAGE_SIZE);
    pqspi_info->DummyCyclesRead = 8;
    pqspi_info->SectorEraseMaxTime = S25FL512S_SECTOR_ERASE_MAX_TIME;
    pqspi_info->BulkEraseMaxTime = S25FL512S_BULK_ERASE_MAX_TIME;
  }

  return QSPI_OK;

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

