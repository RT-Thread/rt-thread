/**
  ******************************************************************************
  * @file    stm32h7xx_hal_eth.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date   29-December-2017
  * @brief   ETH HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Ethernet (ETH) peripheral:
  *           + Initialization and deinitialization functions
  *           + IO operation functions
  *           + Peripheral Control functions 
  *           + Peripheral State and Errors functions
  *
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
     [..]
     The ETH HAL driver can be used as follows:
     
      (#)Declare a ETH_HandleTypeDef handle structure, for example:
         ETH_HandleTypeDef  heth;
        
      (#)Fill parameters of Init structure in heth handle
  
      (#)Call HAL_ETH_Init() API to initialize the Ethernet peripheral (MAC, DMA, ...) 

      (#)Initialize the ETH low level resources through the HAL_ETH_MspInit() API:
          (##) Enable the Ethernet interface clock using 
                (+++)  __HAL_RCC_ETH1MAC_CLK_ENABLE()
                (+++)  __HAL_RCC_ETH1TX_CLK_ENABLE()
                (+++)  __HAL_RCC_ETH1RX_CLK_ENABLE()
           
          (##) Initialize the related GPIO clocks
          (##) Configure Ethernet pinout
          (##) Configure Ethernet NVIC interrupt (in Interrupt mode)   

      (#) Ethernet data reception is asynchronous, so call the following API
          to start the listening mode:
          (##) HAL_ETH_Start():
               This API starts the MAC and DMA transmission and reception process, 
               without enabling end of transfer interrupts, in this mode user 
               has to poll for data availability by calling HAL_ETH_IsRxDataAvailable()
          (##) HAL_ETH_Start_IT():
               This API starts the MAC and DMA transmission and reception process, 
               end of transfer interrupts are enabled in this mode,  
               HAL_ETH_RxCpltCallback() will be executed when an Ethernet packet is received
               
      (#) When data is received (HAL_ETH_IsRxDataAvailable() returns 1 or Rx interrupt
          occurred), user can call the following APIs to get received data:
          (##) HAL_ETH_GetRxDataBuffer(): Get buffer address of received frame
          (##) HAL_ETH_GetRxDataLength(): Get received frame length
          (##) HAL_ETH_GetRxDataInfo(): Get received frame additional info, 
               please refer to ETH_RxPacketInfo typedef structure 
               
      (#) For transmission path, two APIs are available:
         (##) HAL_ETH_Transmit(): Transmit an ETH frame in blocking mode
         (##) HAL_ETH_Transmit_IT(): Transmit an ETH frame in interrupt mode,
              HAL_ETH_TxCpltCallback() will be executed when end of transfer occur
              
      (#) Communication with an external PHY device:
         (##) HAL_ETH_ReadPHYRegister(): Read a register from an external PHY                
         (##) HAL_ETH_WritePHYRegister(): Write data to an external RHY register

      (#) Configure the Ethernet MAC after ETH peripheral initialization
          (##) HAL_ETH_GetMACConfig(): Get MAC actual configuration into ETH_MACConfigTypeDef 
          (##) HAL_ETH_SetMACConfig(): Set MAC configuration based on ETH_MACConfigTypeDef
      
      (#) Configure the Ethernet DMA after ETH peripheral initialization
          (##) HAL_ETH_GetDMAConfig(): Get DMA actual configuration into ETH_DMAConfigTypeDef 
          (##) HAL_ETH_SetDMAConfig(): Set DMA configuration based on ETH_DMAConfigTypeDef 
      
      -@- The PTP protocol offload APIs are  not supported in this driver.

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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
#include "stm32h7xx_hal.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @defgroup ETH ETH 
  * @brief ETH HAL module driver
  * @{
  */
#ifdef HAL_ETH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup ETH_Private_Constants ETH Private Constants
  * @{
  */
#define ETH_MACCR_MASK       ((uint32_t)0xFFFB7F7CU)
#define ETH_MACECR_MASK      ((uint32_t)0x3F077FFFU) 
#define ETH_MACPFR_MASK      ((uint32_t)0x800007FFU)
#define ETH_MACWTR_MASK      ((uint32_t)0x0000010FU)
#define ETH_MACTFCR_MASK     ((uint32_t)0xFFFF00F2U)
#define ETH_MACRFCR_MASK     ((uint32_t)0x00000003U)
#define ETH_MTLTQOMR_MASK    ((uint32_t)0x00000072U)
#define ETH_MTLRQOMR_MASK    ((uint32_t)0x0000007BU)

#define ETH_DMAMR_MASK       ((uint32_t)0x00007802U)
#define ETH_DMASBMR_MASK     ((uint32_t)0x0000D001U)
#define ETH_DMACCR_MASK      ((uint32_t)0x00013FFFU)
#define ETH_DMACTCR_MASK     ((uint32_t)0x003F1010U)
#define ETH_DMACRCR_MASK     ((uint32_t)0x803F0000U)
#define ETH_MACPCSR_MASK     (ETH_MACPCSR_PWRDWN | ETH_MACPCSR_RWKPKTEN | \
                              ETH_MACPCSR_MGKPKTEN | ETH_MACPCSR_GLBLUCAST | \
                              ETH_MACPCSR_RWKPFE)

/* Timeout values */
#define ETH_SWRESET_TIMEOUT                 ((uint32_t)500U)  
#define ETH_MDIO_BUS_TIMEOUT                ((uint32_t)1000U)

#define ETH_DMARXNDESCWBF_ERRORS_MASK ((uint32_t)(ETH_DMARXNDESCWBF_DE | ETH_DMARXNDESCWBF_RE | \
                                                  ETH_DMARXNDESCWBF_OE | ETH_DMARXNDESCWBF_RWT |\
                                                  ETH_DMARXNDESCWBF_GP | ETH_DMARXNDESCWBF_CE))

#define ETH_MAC_US_TICK               ((uint32_t)1000000U)
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup ETH_Private_Macros ETH Private Macros
  * @{
  */
/* Helper macros for TX descriptor handling */
#define INCR_TX_DESC_INDEX(inx, offset) do {\
	(inx) += (offset);\
          if ((inx) >= ETH_TX_DESC_CNT){\
            (inx) = ((inx) - ETH_TX_DESC_CNT);}\
} while (0)	

/* Helper macros for RX descriptor handling */
#define INCR_RX_DESC_INDEX(inx, offset) do {\
	(inx) += (offset);\
          if ((inx) >= ETH_RX_DESC_CNT){\
            (inx) = ((inx) - ETH_RX_DESC_CNT);}\
} while (0)
/**
  * @}
  */
/* Private function prototypes -----------------------------------------------*/
/** @defgroup ETH_Private_Functions   ETH Private Functions
  * @{
  */
static void ETH_MAC_MDIO_ClkConfig(ETH_HandleTypeDef *heth);
static void ETH_SetMACConfig(ETH_HandleTypeDef *heth,  ETH_MACConfigTypeDef *macconf);
static void ETH_SetDMAConfig(ETH_HandleTypeDef *heth,  ETH_DMAConfigTypeDef *dmaconf);
static void ETH_MACDMAConfig(ETH_HandleTypeDef *heth);
static void ETH_DMATxDescListInit(ETH_HandleTypeDef *heth);
static void ETH_DMARxDescListInit(ETH_HandleTypeDef *heth);
static uint32_t ETH_Prepare_Tx_Descriptors(ETH_HandleTypeDef *heth, ETH_TxPacketConfig *pTxConfig, uint32_t ItMode);
/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup ETH_Exported_Functions ETH Exported Functions
  * @{
  */

/** @defgroup ETH_Exported_Functions_Group1 Initialization and deinitialization functions 
  *  @brief    Initialization and Configuration functions 
  *
@verbatim    
===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================  
    [..]  This subsection provides a set of functions allowing to initialize and
          deinitialize the ETH peripheral:

      (+) User must Implement HAL_ETH_MspInit() function in which he configures
          all related peripherals resources (CLOCK, GPIO and NVIC ).

      (+) Call the function HAL_ETH_Init() to configure the selected device with
          the selected configuration:
        (++) MAC address
        (++) Media interface (MII or RMII)
        (++) Rx DMA Descriptors Tab
        (++) Tx DMA Descriptors Tab
        (++) Length of Rx Buffers 
 
      (+) Call the function HAL_ETH_DescAssignMemory() to assign data buffers 
          for each Rx DMA Descriptor 
          
      (+) Call the function HAL_ETH_DeInit() to restore the default configuration
          of the selected ETH peripheral.    

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the Ethernet peripheral registers. 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_Init(ETH_HandleTypeDef *heth)
{
  uint32_t tickstart;
  
  if(heth == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the ETH peripheral state */
  if(heth->gState == HAL_ETH_STATE_RESET)
  {
    /* Init the low level hardware : GPIO, CLOCK, NVIC. */
    HAL_ETH_MspInit(heth);
  }
  
  heth->gState = HAL_ETH_STATE_BUSY;
  
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  
  if(heth->Init.MediaInterface == HAL_ETH_MII_MODE)
  {
    HAL_SYSCFG_ETHInterfaceSelect(SYSCFG_ETH_MII);
  }
  else
  {
    HAL_SYSCFG_ETHInterfaceSelect(SYSCFG_ETH_RMII);
  }
  
  /* Ethernet Software reset */
  /* Set the SWR bit: resets all MAC subsystem internal registers and logic */
  /* After reset all the registers holds their respective reset values */
  SET_BIT(heth->Instance->DMAMR, ETH_DMAMR_SWR);
  
  /* Get tick */
  tickstart = HAL_GetTick();
  
  /* Wait for software reset */
  while (READ_BIT(heth->Instance->DMAMR, ETH_DMAMR_SWR))
  {
    if(((HAL_GetTick() - tickstart ) > ETH_SWRESET_TIMEOUT))
    {
      /* Set Error Code */
      heth->ErrorCode = HAL_ETH_ERROR_TIMEOUT;
      /* Set State as Error */
      heth->gState = HAL_ETH_STATE_ERROR;
      /* Return Error */
      return HAL_ERROR;
    }
  }
  
  /*------------------ MDIO CSR Clock Range Configuration --------------------*/
  ETH_MAC_MDIO_ClkConfig(heth);
  
  /*------------------ MAC LPI 1US Tic Counter Configuration --------------------*/
  WRITE_REG(heth->Instance->MAC1USTCR, ((HAL_RCC_GetHCLKFreq() / ETH_MAC_US_TICK) - 1));
  
  /*------------------ MAC, MTL and DMA default Configuration ----------------*/	
  ETH_MACDMAConfig(heth);
  
  /* SET DSL to 64 bit */
  MODIFY_REG(heth->Instance->DMACCR, ETH_DMACCR_DSL, ETH_DMACCR_DSL_64BIT);	
  
  /* Set Receive Buffers Length (must be a multiple of 4) */
  if ((heth->Init.RxBuffLen % 4) != 0)
  {
    /* Set Error Code */
    heth->ErrorCode = HAL_ETH_ERROR_PARAM;
    /* Set State as Error */
    heth->gState = HAL_ETH_STATE_ERROR;
    /* Return Error */
    return HAL_ERROR;
  }
  else
  {
    MODIFY_REG(heth->Instance->DMACRCR, ETH_DMACRCR_RBSZ, ((heth->Init.RxBuffLen) << 1));
  }
  
  /*------------------ DMA Tx Descriptors Configuration ----------------------*/
  ETH_DMATxDescListInit(heth);
  
  /*------------------ DMA Rx Descriptors Configuration ----------------------*/
  ETH_DMARxDescListInit(heth);
  
  /*--------------------- ETHERNET MAC Address Configuration ------------------*/
  /* Set MAC addr bits 32 to 47 */
  heth->Instance->MACA0HR = ((heth->Init.MACAddr[5] << 8) | heth->Init.MACAddr[4]);
  /* Set MAC addr bits 0 to 31 */
  heth->Instance->MACA0LR = ((heth->Init.MACAddr[3] << 24) | (heth->Init.MACAddr[2] << 16) | (heth->Init.MACAddr[1] << 8) | heth->Init.MACAddr[0]);
  
  heth->ErrorCode = HAL_ETH_ERROR_NONE;
  heth->gState = HAL_ETH_STATE_READY;
  heth->RxState = HAL_ETH_STATE_READY;
  
  return HAL_OK;
}

/**
  * @brief  DeInitializes the ETH peripheral. 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_DeInit(ETH_HandleTypeDef *heth)
{
  /* Set the ETH peripheral state to BUSY */
  heth->gState = HAL_ETH_STATE_BUSY;
  
  /* De-Init the low level hardware : GPIO, CLOCK, NVIC. */
  HAL_ETH_MspDeInit(heth);
  
  /* Set ETH HAL state to Disabled */
  heth->gState= HAL_ETH_STATE_RESET;

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the ETH MSP.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
__weak void HAL_ETH_MspInit(ETH_HandleTypeDef *heth)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(heth);
  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_ETH_MspInit could be implemented in the user file
  */
}

/**
  * @brief  DeInitializes ETH MSP.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
__weak void HAL_ETH_MspDeInit(ETH_HandleTypeDef *heth)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(heth);
  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_ETH_MspDeInit could be implemented in the user file
  */
}

/**
  * @brief  Assign memory buffers to a DMA Rx descriptor 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  Index : index of the DMA Rx descriptor 
  *                  this parameter can be a value from 0x0 to (ETH_RX_DESC_CNT -1)
  * @param  pBuffer1: address of buffer 1
  * @param  pBuffer2: address of buffer 2 if available
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_DescAssignMemory(ETH_HandleTypeDef *heth, uint32_t Index, uint8_t *pBuffer1, uint8_t *pBuffer2)
{
  ETH_DMADescTypeDef *dmarxdesc = (ETH_DMADescTypeDef *)heth->RxDescList.RxDesc[Index]; 
  
  if((pBuffer1 == NULL) || (Index >= ETH_RX_DESC_CNT))
  {
    /* Set Error Code */
    heth->ErrorCode = HAL_ETH_ERROR_PARAM;
    /* Return Error */
    return HAL_ERROR;
  }

  /* write buffer address to RDES0 */
  WRITE_REG(dmarxdesc->DESC0, (uint32_t)pBuffer1);
  /* store buffer address */
  WRITE_REG(dmarxdesc->BackupAddr0, (uint32_t)pBuffer1);
  /* set buffer address valid bit to RDES3 */
  SET_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCRF_BUF1V);
  
  if(pBuffer2 != NULL)
  {
    /* write buffer 2 address to RDES1 */
    WRITE_REG(dmarxdesc->DESC2, (uint32_t)pBuffer2);
     /* store buffer 2 address */
    WRITE_REG(dmarxdesc->BackupAddr1, (uint32_t)pBuffer2);
    /* set buffer 2 address valid bit to RDES3 */
    SET_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCRF_BUF2V);
  }
  /* set OWN bit to RDES3 */
  SET_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCRF_OWN);
  
  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup ETH_Exported_Functions_Group2 IO operation functions 
  *  @brief ETH Transmit and Receive functions 
  *
@verbatim   
  ==============================================================================
                      ##### IO operation functions #####
  ==============================================================================  
  [..]
    This subsection provides a set of functions allowing to manage the ETH
    data transfer.
      
@endverbatim
  * @{
  */

/**
  * @brief  Enables Ethernet MAC and DMA reception and transmission 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_Start(ETH_HandleTypeDef *heth)
{
  if(heth->gState == HAL_ETH_STATE_READY)
  {
    heth->gState = HAL_ETH_STATE_BUSY;
    
    /* Enable the MAC transmission */
    SET_BIT(heth->Instance->MACCR, ETH_MACCR_TE);
    
    /* Enable the MAC reception */
    SET_BIT(heth->Instance->MACCR, ETH_MACCR_RE);
    
    /* Set the Flush Transmit FIFO bit */
    SET_BIT(heth->Instance->MTLTQOMR, ETH_MTLTQOMR_FTQ);
    
    /* Enable the DMA transmission */
    SET_BIT(heth->Instance->DMACTCR, ETH_DMACTCR_ST); 
    
    /* Enable the DMA reception */
    SET_BIT(heth->Instance->DMACRCR, ETH_DMACRCR_SR); 
    
    /* Clear Tx and Rx process stopped flags */
    heth->Instance->DMACSR |= (ETH_DMACSR_TPS | ETH_DMACSR_RPS);
    
    heth->gState = HAL_ETH_STATE_READY;
    heth->RxState = HAL_ETH_STATE_BUSY_RX;
    
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief  Enables Ethernet MAC and DMA reception/transmission in Interrupt mode 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_Start_IT(ETH_HandleTypeDef *heth)
{
  uint32_t descindex = 0, counter;
  ETH_DMADescTypeDef *dmarxdesc = (ETH_DMADescTypeDef *)heth->RxDescList.RxDesc[descindex];
  
  if(heth->gState == HAL_ETH_STATE_READY)
  {
    heth->gState = HAL_ETH_STATE_BUSY;
     
    /* Set IOC bit to all Rx descriptors */
    for(counter= 0; counter < ETH_RX_DESC_CNT; counter++)
    {
      SET_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCRF_IOC);
      INCR_RX_DESC_INDEX(descindex, 1);
      dmarxdesc = (ETH_DMADescTypeDef *)heth->RxDescList.RxDesc[descindex];
    }
    
    /* save IT mode to ETH Handle */
    heth->RxDescList.ItMode = 1U;
    
    /* Enable the MAC transmission */
    SET_BIT(heth->Instance->MACCR, ETH_MACCR_TE);
    
    /* Enable the MAC reception */
    SET_BIT(heth->Instance->MACCR, ETH_MACCR_RE);
    
    /* Set the Flush Transmit FIFO bit */
    SET_BIT(heth->Instance->MTLTQOMR, ETH_MTLTQOMR_FTQ);
    
    /* Enable the DMA transmission */
    SET_BIT(heth->Instance->DMACTCR, ETH_DMACTCR_ST); 
    
    /* Enable the DMA reception */
    SET_BIT(heth->Instance->DMACRCR, ETH_DMACRCR_SR); 
    
    /* Clear Tx and Rx process stopped flags */
    heth->Instance->DMACSR |= (ETH_DMACSR_TPS | ETH_DMACSR_RPS);
        
    heth->gState = HAL_ETH_STATE_READY;
    heth->RxState = HAL_ETH_STATE_BUSY_RX;
    
    /* Enable ETH DMA interrupts:
    - Tx complete interrupt
    - Rx complete interrupt
    - Fatal bus interrupt
    */
    __HAL_ETH_DMA_ENABLE_IT(heth, (ETH_DMACIER_NIE | ETH_DMACIER_RIE | ETH_DMACIER_TIE  |
                                   ETH_DMACIER_FBEE | ETH_DMACIER_AIE));
    
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief  Stop Ethernet MAC and DMA reception/transmission 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_Stop(ETH_HandleTypeDef *heth)
{
  if(heth->gState != HAL_ETH_STATE_RESET) 
  {
     /* Set the ETH peripheral state to BUSY */
    heth->gState = HAL_ETH_STATE_BUSY;
    
    /* Disable the DMA transmission */
    CLEAR_BIT(heth->Instance->DMACTCR, ETH_DMACTCR_ST);
    
    /* Disable the DMA reception */
    CLEAR_BIT(heth->Instance->DMACRCR, ETH_DMACRCR_SR);
    
    /* Disable the MAC reception */
    CLEAR_BIT( heth->Instance->MACCR, ETH_MACCR_RE);
    
    /* Set the Flush Transmit FIFO bit */
    SET_BIT(heth->Instance->MTLTQOMR, ETH_MTLTQOMR_FTQ);
    
    /* Disable the MAC transmission */
    CLEAR_BIT(heth->Instance->MACCR, ETH_MACCR_TE);
    
    heth->gState = HAL_ETH_STATE_READY;
    heth->RxState = HAL_ETH_STATE_READY;
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief  Stop Ethernet MAC and DMA reception/transmission in Interrupt mode
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_Stop_IT(ETH_HandleTypeDef *heth)
{
  ETH_DMADescTypeDef *dmarxdesc = (ETH_DMADescTypeDef *)heth->RxDescList.RxDesc[0];
  uint32_t index;
  
  if(heth->gState != HAL_ETH_STATE_RESET)
  {
    /* Set the ETH peripheral state to BUSY */
    heth->gState = HAL_ETH_STATE_BUSY;
    
    /* Disable intrrupts:
    - Tx complete interrupt
    - Rx complete interrupt     */
    __HAL_ETH_DMA_DISABLE_IT(heth, (ETH_DMA_NORMAL_IT | ETH_DMA_RX_IT | ETH_DMA_TX_IT));
    
    /* Disable the DMA transmission */
    CLEAR_BIT(heth->Instance->DMACTCR, ETH_DMACTCR_ST);
    
    /* Disable the DMA reception */
    CLEAR_BIT(heth->Instance->DMACRCR, ETH_DMACRCR_SR);
    
    /* Disable the MAC reception */
    CLEAR_BIT( heth->Instance->MACCR, ETH_MACCR_RE);
    
    /* Set the Flush Transmit FIFO bit */
    SET_BIT(heth->Instance->MTLTQOMR, ETH_MTLTQOMR_FTQ);
    
    /* Disable the MAC transmission */
    CLEAR_BIT(heth->Instance->MACCR, ETH_MACCR_TE);
    
    /* Clear IOC bit to all Rx descriptors */
    for(index = 0; index < ETH_RX_DESC_CNT; index++)
    {
      CLEAR_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCRF_IOC);
    }
    
    heth->RxDescList.ItMode = 0U;
    
    heth->gState = HAL_ETH_STATE_READY;
    heth->RxState = HAL_ETH_STATE_READY;
   
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief  Sends an Ethernet Packet in polling mode. 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  pTxConfig: Hold the configuration of packet to be transmitted
  * @param  Timeout: timeout value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_Transmit(ETH_HandleTypeDef *heth, ETH_TxPacketConfig *pTxConfig, uint32_t Timeout)
{
  uint32_t tickstart;
  const ETH_DMADescTypeDef *dmatxdesc;
  
  if(pTxConfig == NULL)
  {
    heth->ErrorCode |= HAL_ETH_ERROR_PARAM;
    return HAL_ERROR;
  }
  
  if(heth->gState == HAL_ETH_STATE_READY)
  {
    /* Config DMA Tx descriptor by Tx Packet info */
    if (ETH_Prepare_Tx_Descriptors(heth, pTxConfig, 0) != HAL_ETH_ERROR_NONE)
    {
      /* Set the ETH error code */
      heth->ErrorCode |= HAL_ETH_ERROR_BUSY;
      return HAL_ERROR;
    }
    
    dmatxdesc = (ETH_DMADescTypeDef *)(&heth->TxDescList)->TxDesc[heth->TxDescList.CurTxDesc];
    
    /* Incr current tx desc index */
    INCR_TX_DESC_INDEX(heth->TxDescList.CurTxDesc, 1);
    
    /* Start transmission */  
    /* issue a poll command to Tx DMA by writing address of next immediate free descriptor */
    WRITE_REG(heth->Instance->DMACTDTPR, (uint32_t)(heth->TxDescList.TxDesc[heth->TxDescList.CurTxDesc]));
    
    tickstart = HAL_GetTick();
    
    /* Wait for data to be transmitted or timeout occured */
    while((dmatxdesc->DESC3 & ETH_DMATXNDESCWBF_OWN) != (uint32_t)RESET)
    {
      if((heth->Instance->DMACSR & ETH_DMACSR_FBE) != (uint32_t)RESET)
      {
        heth->ErrorCode |= HAL_ETH_ERROR_DMA;
        heth->DMAErrorCode = heth->Instance->DMACSR;
        /* Set ETH HAL State to Ready */
        heth->gState = HAL_ETH_STATE_ERROR;
        /* Return function status */
        return HAL_ERROR;
      }
      
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if(((HAL_GetTick() - tickstart ) > Timeout) || (Timeout == 0U))
        {
          heth->ErrorCode |= HAL_ETH_ERROR_TIMEOUT;
          heth->gState = HAL_ETH_STATE_READY;
          return HAL_ERROR;
        }
      }
    }
    
    /* Set ETH HAL State to Ready */
    heth->gState = HAL_ETH_STATE_READY;
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR; 
  }
}

/**
  * @brief  Sends an Ethernet Packet in interrupt mode. 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  pTxConfig: Hold the configuration of packet to be transmitted
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_Transmit_IT(ETH_HandleTypeDef *heth, ETH_TxPacketConfig *pTxConfig)
{
  if(pTxConfig == NULL)
  {
    return HAL_ERROR;
  }
  
  if(heth->gState == HAL_ETH_STATE_READY)
  {
    /* Config DMA Tx descriptor by Tx Packet info */
    if (ETH_Prepare_Tx_Descriptors(heth, pTxConfig, 1) != HAL_ETH_ERROR_NONE)
    {
      heth->ErrorCode = HAL_ETH_ERROR_BUSY;
      return HAL_ERROR;
    }
    
    /* Incr current tx desc index */
    INCR_TX_DESC_INDEX(heth->TxDescList.CurTxDesc, 1);
    
    /* Start transmission */  
    /* issue a poll command to Tx DMA by writing address of next immediate free descriptor */
    WRITE_REG(heth->Instance->DMACTDTPR, (uint32_t)(heth->TxDescList.TxDesc[heth->TxDescList.CurTxDesc]));
    
    return HAL_OK;
    
  }
  else
  {
    return HAL_ERROR; 
  }
}

/**
  * @brief  Checks for received Packets. 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval  1: A Packet is received
  *          0: no Packet received
  */
uint8_t HAL_ETH_IsRxDataAvailable(ETH_HandleTypeDef *heth)
{
  ETH_RxDescListTypeDef *dmarxdesclist = &heth->RxDescList;
  uint32_t descidx = dmarxdesclist->CurRxDesc;
  ETH_DMADescTypeDef *dmarxdesc = (ETH_DMADescTypeDef *)dmarxdesclist->RxDesc[descidx];
  uint32_t descscancnt = 0;
  uint32_t appdesccnt = 0, firstappdescidx = 0;
  
  if(dmarxdesclist->AppDescNbr != 0)
  {
    /* data already received by not yet processed*/
    return 0;
  }
  
  /* Check if descriptor is not owned by DMA */
  while((READ_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCWBF_OWN) == (uint32_t)RESET) && (descscancnt < ETH_RX_DESC_CNT))
  {
    descscancnt++;
    
    /* Check if last descriptor */
    if(READ_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCWBF_LD) != (uint32_t)RESET) 
    {           
      /* Increment the number of descriptors to be passed to the application */
      appdesccnt += 1U;
      
      if(appdesccnt == 1)
      {
        WRITE_REG(firstappdescidx, descidx);
      }
      
      /* Increment current rx descriptor index */
      INCR_RX_DESC_INDEX(descidx, 1); 
      
      /* Check for Context descriptor */
      /* Get current descriptor address */
      dmarxdesc = (ETH_DMADescTypeDef *)dmarxdesclist->RxDesc[descidx];  
      
      if((READ_BIT(dmarxdesc->DESC3,  ETH_DMARXNDESCWBF_OWN)  == (uint32_t)RESET) && 
         (READ_BIT(dmarxdesc->DESC3,  ETH_DMARXNDESCWBF_CTXT)  != (uint32_t)RESET))
      {
        /* Increment the number of descriptors to be passed to the application */
        dmarxdesclist->AppContextDesc = 1;
        /* Increment current rx descriptor index */
        INCR_RX_DESC_INDEX(descidx, 1); 
      }
      
      /* Fill information to Rx descriptors list */
      dmarxdesclist->CurRxDesc = descidx;
      dmarxdesclist->FirstAppDesc = firstappdescidx;
      dmarxdesclist->AppDescNbr = appdesccnt;
      
      /* Return function status */
      return 1;
    }
    /* Check if first descriptor */
    else if(READ_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCWBF_FD) != (uint32_t)RESET)
    {
      WRITE_REG(firstappdescidx, descidx);
      /* Increment the number of descriptors to be passed to the application */
      appdesccnt = 1U;
      
      /* Increment current rx descriptor index */
      INCR_RX_DESC_INDEX(descidx, 1U);
      /* Get current descriptor address */
      dmarxdesc = (ETH_DMADescTypeDef *)dmarxdesclist->RxDesc[descidx];  
    }
    /* It should be an intermediate descriptor */ 
    else
    {      
      /* Increment the number of descriptors to be passed to the application */
      appdesccnt += 1U;
      
      /* Increment current rx descriptor index */
      INCR_RX_DESC_INDEX(descidx, 1U);
      /* Get current descriptor address */
      dmarxdesc = (ETH_DMADescTypeDef *)dmarxdesclist->RxDesc[descidx];            
    } 
  }
  
  /* Build Descriptors if an incomplete Packet is received */ 
  if(appdesccnt > 0)
  {
    descidx = firstappdescidx;
    dmarxdesc = (ETH_DMADescTypeDef *)dmarxdesclist->RxDesc[descidx];
    
    for(descscancnt = 0; descscancnt < appdesccnt; descscancnt++)
    {
      WRITE_REG(dmarxdesc->DESC0, dmarxdesc->BackupAddr0);
      WRITE_REG(dmarxdesc->DESC3, ETH_DMARXNDESCRF_BUF1V);
      
      if (READ_REG(dmarxdesc->BackupAddr1) != ((uint32_t)RESET))
      {
        WRITE_REG(dmarxdesc->DESC2, dmarxdesc->BackupAddr1);
        SET_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCRF_BUF2V);
      }
      
      SET_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCRF_OWN);
      
      if(dmarxdesclist->ItMode != ((uint32_t)RESET))
      {
        SET_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCRF_IOC);
      }
      
      /* Increment rx descriptor index */
      INCR_RX_DESC_INDEX(descidx, 1);
      /* Get descriptor address */
      dmarxdesc = (ETH_DMADescTypeDef *)dmarxdesclist->RxDesc[descidx]; 
    }
  }
  
  /* Fill information to Rx descriptors list: No received Packet */
  dmarxdesclist->AppDescNbr = 0U;  
  
  return 0;
}

/**
  * @brief  This function gets the buffer address of last received Packet.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  RxBuffer: Pointer to a ETH_BufferTypeDef structure
  * @retval HAL status 
  */
HAL_StatusTypeDef HAL_ETH_GetRxDataBuffer(ETH_HandleTypeDef *heth, ETH_BufferTypeDef *RxBuffer)
{
  ETH_RxDescListTypeDef *dmarxdesclist = &heth->RxDescList;
  uint32_t descidx = dmarxdesclist->FirstAppDesc;
  uint32_t index, accumulatedlen = 0, lastdesclen;
  __IO const ETH_DMADescTypeDef *dmarxdesc = (ETH_DMADescTypeDef *)dmarxdesclist->RxDesc[descidx];
  ETH_BufferTypeDef *rxbuff = RxBuffer;
  
  if(dmarxdesclist->AppDescNbr ==0)
  {
    if(HAL_ETH_IsRxDataAvailable(heth) == 0)
    {
      /* No data to be transferred to the application */
      return HAL_ERROR;
    }
  }
  
  /* Get intermediate descriptors buffers: in case of the Packet is splitted into multi descriptors */
  for(index = 0; index < (dmarxdesclist->AppDescNbr - 1); index++)
  {    
    /* Both rx descriptor buffers are valid */
    if(dmarxdesc->BackupAddr1 != 0)
    {
      if(rxbuff == NULL)
      {
        return HAL_ERROR;
      }
      
      rxbuff->buffer = (uint8_t *) dmarxdesc->BackupAddr0;
      rxbuff->len = heth->Init.RxBuffLen;
      
      rxbuff = (struct __ETH_BufferTypeDef *)rxbuff->next;
      
      if(rxbuff == NULL)
      {
        return HAL_ERROR;
      }
      
      rxbuff->buffer = (uint8_t *) dmarxdesc->BackupAddr1;
      rxbuff->len =  heth->Init.RxBuffLen;      
    }
    /* Only buffer 1 address is valid */
    else
    {
      rxbuff->buffer = (uint8_t *) dmarxdesc->BackupAddr0;
      rxbuff->len =  heth->Init.RxBuffLen;      
    }
    
    /* get total length until this descriptor */
    accumulatedlen = READ_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCWBF_PL);
    
    /* Increment to next descriptor */
    INCR_RX_DESC_INDEX(descidx, 1);
    dmarxdesc = (ETH_DMADescTypeDef *)dmarxdesclist->RxDesc[descidx];
    
    /* Point to next buffer */
    rxbuff = (struct __ETH_BufferTypeDef *)rxbuff->next; 
  }
  
  /* Get last descriptor buffers */
  if(rxbuff == NULL)
  {
    return HAL_ERROR;
  }
  
  /* last descriptor data length */
  lastdesclen = READ_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCWBF_PL) - accumulatedlen;
  
  /* data is in only one buffer */
  if(lastdesclen <= heth->Init.RxBuffLen)
  {
    rxbuff->buffer = (uint8_t *) dmarxdesc->BackupAddr0;
    rxbuff->len = lastdesclen; 
  }
  /* data is in two buffers */
  else if(dmarxdesc->BackupAddr1 != 0)
  {
    rxbuff->buffer = (uint8_t *) dmarxdesc->BackupAddr0;
    rxbuff->len = heth->Init.RxBuffLen; 
    
    rxbuff = (struct __ETH_BufferTypeDef *)rxbuff->next;
    
    if(rxbuff == NULL)
    {
      return HAL_ERROR;
    }
    
    rxbuff->buffer = (uint8_t *) dmarxdesc->BackupAddr1;
    rxbuff->len =  lastdesclen - (heth->Init.RxBuffLen);  
  }
  else /* Buffer 2 not valid*/
  {
    return HAL_ERROR;
  }
  
  return HAL_OK;
}

/**
  * @brief  This function gets the length of last received Packet.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  Length: parameter to hold Rx packet length  
  * @retval HAL Status 
  */
HAL_StatusTypeDef HAL_ETH_GetRxDataLength(ETH_HandleTypeDef *heth, uint32_t *Length)
{
  ETH_RxDescListTypeDef *dmarxdesclist = &heth->RxDescList;
  uint32_t descidx = dmarxdesclist->FirstAppDesc;
  __IO const ETH_DMADescTypeDef *dmarxdesc;
  
  if(dmarxdesclist->AppDescNbr ==0)
  {
    if(HAL_ETH_IsRxDataAvailable(heth) == 0)
    {
      /* No data to be transferred to the application */
      return HAL_ERROR;
    }
  }
  
  /* Get index of last descriptor */
  INCR_RX_DESC_INDEX(descidx, (dmarxdesclist->AppDescNbr-1));
  /* Point to last descriptor */
  dmarxdesc = (ETH_DMADescTypeDef *)dmarxdesclist->RxDesc[descidx];
  
  *Length = READ_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCWBF_PL);
  
  return HAL_OK;
}

/**
  * @brief  Get the Rx data info (Packet type, VLAN tag, Filters status, ...)
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  RxPacketInfo: parameter to hold info of received buffer 
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_GetRxDataInfo(ETH_HandleTypeDef *heth, ETH_RxPacketInfo *RxPacketInfo)
{
  ETH_RxDescListTypeDef *dmarxdesclist = &heth->RxDescList;
  uint32_t descidx = dmarxdesclist->FirstAppDesc;
  __IO const ETH_DMADescTypeDef *dmarxdesc;
  
  if(dmarxdesclist->AppDescNbr ==0)
  {
    if(HAL_ETH_IsRxDataAvailable(heth) == 0)
    {
      /* No data to be transferred to the application */
      return HAL_ERROR;
    }
  }
  
  /* Get index of last descriptor */
  INCR_RX_DESC_INDEX(descidx, ((dmarxdesclist->AppDescNbr) - 1U));
  /* Point to last descriptor */
  dmarxdesc = (ETH_DMADescTypeDef *)dmarxdesclist->RxDesc[descidx];
  
  if((dmarxdesc->DESC3 & ETH_DMARXNDESCWBF_ES) != (uint32_t)RESET)
  {
    RxPacketInfo->ErrorCode = READ_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCWBF_ERRORS_MASK);
  }
  else
  {    
    if(READ_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCWBF_RS0V))
    {
      
      if(READ_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCWBF_LT) == ETH_DMARXNDESCWBF_LT_DVLAN)
      {
        RxPacketInfo->VlanTag = READ_BIT(dmarxdesc->DESC0, ETH_DMARXNDESCWBF_OVT); 
        RxPacketInfo->InnerVlanTag = READ_BIT(dmarxdesc->DESC0, ETH_DMARXNDESCWBF_IVT) >> 16;
      }
      else
      {
        RxPacketInfo->VlanTag = READ_BIT(dmarxdesc->DESC0, ETH_DMARXNDESCWBF_OVT);          
      }
    }
    
    if(READ_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCWBF_RS1V))
    {
      /* Get Payload type */
      RxPacketInfo->PayloadType =READ_BIT( dmarxdesc->DESC1, ETH_DMARXNDESCWBF_PT);
      /* Get Header type */
      RxPacketInfo->HeaderType = READ_BIT(dmarxdesc->DESC1, (ETH_DMARXNDESCWBF_IPV4 | ETH_DMARXNDESCWBF_IPV6));
      /* Get Checksum status */
      RxPacketInfo->Checksum = READ_BIT(dmarxdesc->DESC1, (ETH_DMARXNDESCWBF_IPCE | ETH_DMARXNDESCWBF_IPCB | ETH_DMARXNDESCWBF_IPHE));
    }
    
    if(READ_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCWBF_RS2V))
    {
      RxPacketInfo->MacFilterStatus = READ_BIT(dmarxdesc->DESC2, (ETH_DMARXNDESCWBF_HF | ETH_DMARXNDESCWBF_DAF | ETH_DMARXNDESCWBF_SAF | ETH_DMARXNDESCWBF_VF));
      RxPacketInfo->L3FilterStatus = READ_BIT(dmarxdesc->DESC2,  (ETH_DMARXNDESCWBF_L3FM | ETH_DMARXNDESCWBF_L3L4FM));
      RxPacketInfo->L4FilterStatus = READ_BIT(dmarxdesc->DESC2, (ETH_DMARXNDESCWBF_L4FM | ETH_DMARXNDESCWBF_L3L4FM));
    }
  }
  
  /* Get the segment count */
  WRITE_REG(RxPacketInfo->SegmentCnt, dmarxdesclist->AppDescNbr); 
  
  return HAL_OK;
}

/**
* @brief  This function gives back Rx Desc of the last received Packet
*         to the DMA, so ETH DMA will be able to use these descriptors
*         to receive next Packets.
*         It should be called after processing the received Packet.
* @param  heth: pointer to a ETH_HandleTypeDef structure that contains
*         the configuration information for ETHERNET module
* @retval HAL status.
*/
HAL_StatusTypeDef HAL_ETH_BuildRxDescriptors(ETH_HandleTypeDef *heth)
{
  ETH_RxDescListTypeDef *dmarxdesclist = &heth->RxDescList;   
  uint32_t descindex = dmarxdesclist->FirstAppDesc;
  __IO ETH_DMADescTypeDef *dmarxdesc = (ETH_DMADescTypeDef *)dmarxdesclist->RxDesc[descindex];
  uint32_t totalappdescnbr = dmarxdesclist->AppDescNbr; 
  uint32_t descscan;
  
  if(dmarxdesclist->AppDescNbr ==0)
  {
    /* No Rx descriptors to build */
    return HAL_ERROR;
  }
  
  if(dmarxdesclist->AppContextDesc != 0U)
  {
    /* A context descriptor is available */
    totalappdescnbr += 1;
  }
  
  for(descscan =0; descscan < totalappdescnbr; descscan++)
  {
    WRITE_REG(dmarxdesc->DESC0, dmarxdesc->BackupAddr0);
    WRITE_REG(dmarxdesc->DESC3, ETH_DMARXNDESCRF_BUF1V);
    
    if (READ_REG(dmarxdesc->BackupAddr1) != 0U)
    {
      WRITE_REG(dmarxdesc->DESC2, dmarxdesc->BackupAddr1);
      SET_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCRF_BUF2V);
    }
    
    SET_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCRF_OWN);
    
    if(dmarxdesclist->ItMode != 0U)
    {
      SET_BIT(dmarxdesc->DESC3, ETH_DMARXNDESCRF_IOC);
    }
    
    if(descscan < (dmarxdesclist->AppDescNbr -1))
    {
      /* Increment rx descriptor index */
      INCR_RX_DESC_INDEX(descindex, 1);
      /* Get descriptor address */
      dmarxdesc = (ETH_DMADescTypeDef *)dmarxdesclist->RxDesc[descindex]; 
    }
  }
  
  /* Set the Tail pointer address to the last rx descriptor hold by the app */
  WRITE_REG(heth->Instance->DMACRDTPR, (uint32_t)dmarxdesc);
  
  /* reset the Application desc number */
  WRITE_REG(dmarxdesclist->AppDescNbr, 0);
  
  return HAL_OK;
}


/**
  * @brief  This function handles ETH interrupt request.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval HAL status
  */
void HAL_ETH_IRQHandler(ETH_HandleTypeDef *heth)
{
  /* Packet received */
  if (__HAL_ETH_DMA_GET_IT(heth, ETH_DMACSR_RI))
  {
    if(__HAL_ETH_DMA_GET_IT_SOURCE(heth, ETH_DMACIER_RIE)) 
    {      
      /* Call this function to update handle fields */
      if(HAL_ETH_IsRxDataAvailable(heth) == 1)
      {
        /* Receive complete callback */
        HAL_ETH_RxCpltCallback(heth);
      }
      
      /* Clear the Eth DMA Rx IT pending bits */
      __HAL_ETH_DMA_CLEAR_IT(heth, ETH_DMACSR_RI | ETH_DMACSR_NIS);
    }
  }
  
  /* Packet transmitted */
  if (__HAL_ETH_DMA_GET_IT(heth, ETH_DMACSR_TI))
  {
    if(__HAL_ETH_DMA_GET_IT_SOURCE(heth, ETH_DMACIER_TIE)) 
    {    
      /* Transfer complete callback */
      HAL_ETH_TxCpltCallback(heth);
      
      /* Clear the Eth DMA Tx IT pending bits */
      __HAL_ETH_DMA_CLEAR_IT(heth, ETH_DMACSR_TI | ETH_DMACSR_NIS);
    }
  }
  
  
  /* ETH DMA Error */
  if(__HAL_ETH_DMA_GET_IT(heth, ETH_DMACSR_AIS))
  {
    if(__HAL_ETH_DMA_GET_IT_SOURCE(heth, ETH_DMACIER_AIE))
    {
      heth->ErrorCode |= HAL_ETH_ERROR_DMA;
    
      /* if fatal bus error occured */
      if (__HAL_ETH_DMA_GET_IT(heth, ETH_DMACSR_FBE))
      {
        /* Get DMA error code  */
        heth->DMAErrorCode = __HAL_ETH_DMA_GET_IT(heth, (ETH_DMACSR_FBE | ETH_DMACSR_TPS | ETH_DMACSR_RPS));
        
        /* Disable all interrupts */
        __HAL_ETH_DMA_DISABLE_IT(heth, ETH_DMACIER_NIE | ETH_DMACIER_AIE);
        
        /* Set HAL state to ERROR */
        heth->gState = HAL_ETH_STATE_ERROR;
      }
      else
      {
        /* Get DMA error status  */
        heth->DMAErrorCode = __HAL_ETH_DMA_GET_IT(heth, (ETH_DMACSR_CDE | ETH_DMACSR_ETI | ETH_DMACSR_RWT |
                                                       ETH_DMACSR_RBU | ETH_DMACSR_AIS));
      
        /* Clear the interrupt summary flag */
        __HAL_ETH_DMA_CLEAR_IT(heth, (ETH_DMACSR_CDE | ETH_DMACSR_ETI | ETH_DMACSR_RWT |
                                    ETH_DMACSR_RBU | ETH_DMACSR_AIS));
      }
    
      /* Ethernet Error callback */
      HAL_ETH_DMAErrorCallback(heth);
    }
  }
  
  /* ETH MAC Error IT */
  if(__HAL_ETH_MAC_GET_IT(heth, (ETH_MACIER_RXSTSIE | ETH_MACIER_TXSTSIE)))
  {
    /* Get MAC Rx Tx status and clear Status register pending bit */
    heth->MACErrorCode = READ_REG(heth->Instance->MACRXTXSR);
    
    heth->gState = HAL_ETH_STATE_ERROR;
    
    /* Ethernet PMT callback */
    HAL_ETH_MACErrorCallback(heth);
    
    heth->MACErrorCode = (uint32_t)(0x0U);
  } 
  
  /* ETH PMT IT */
  if(__HAL_ETH_MAC_GET_IT(heth, ETH_MAC_PMT_IT))
  {
    /* Get MAC Wake-up source and clear the status register pending bit */
    heth->MACWakeUpEvent = READ_BIT(heth->Instance->MACPCSR, (ETH_MACPCSR_RWKPRCVD | ETH_MACPCSR_MGKPRCVD));
    
    /* Ethernet PMT callback */
    HAL_ETH_PMTCallback(heth);
    
    heth->MACWakeUpEvent = (uint32_t)(0x0U);
  }
  
  /* ETH EEE IT */
  if(__HAL_ETH_MAC_GET_IT(heth, ETH_MAC_LPI_IT))
  {
    /* Get MAC LPI interrupt source and clear the status register pending bit */
    heth->MACLPIEvent = READ_BIT(heth->Instance->MACPCSR, 0x0000000FU);
    
    /* Ethernet EEE callback */
    HAL_ETH_EEECallback(heth);
    
    heth->MACLPIEvent = (uint32_t)(0x0U);
  }

  /* check ETH WAKEUP exti flag */
  if(__HAL_ETH_WAKEUP_EXTI_GET_FLAG(ETH_WAKEUP_EXTI_LINE) != RESET)
  {
    /* Clear ETH WAKEUP Exti pending bit */
    __HAL_ETH_WAKEUP_EXTI_CLEAR_FLAG(ETH_WAKEUP_EXTI_LINE);
    /* ETH WAKEUP interrupt user callback */
    HAL_ETH_WakeUpCallback(heth);
  }
}

/**
  * @brief  Tx Transfer completed callbacks.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
__weak void HAL_ETH_TxCpltCallback(ETH_HandleTypeDef *heth)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(heth);
  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_ETH_TxCpltCallback could be implemented in the user file
  */ 
}

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
__weak void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(heth);
  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_ETH_RxCpltCallback could be implemented in the user file
  */ 
}

/**
  * @brief  Ethernet DMA transfer error callbacks
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
__weak void HAL_ETH_DMAErrorCallback(ETH_HandleTypeDef *heth)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_ETH_DMAErrorCallback could be implemented in the user file
  */ 
}

/**
* @brief  Ethernet MAC transfer error callbacks
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
__weak void HAL_ETH_MACErrorCallback(ETH_HandleTypeDef *heth)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(heth);
  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_ETH_MACErrorCallback could be implemented in the user file
  */ 
}

/**
  * @brief  Ethernet Power Management module IT callback
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
__weak void HAL_ETH_PMTCallback(ETH_HandleTypeDef *heth)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(heth);
  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_ETH_PMTCallback could be implemented in the user file
  */ 
}
    
/**
  * @brief  Energy Efficient Etherent IT callback
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
__weak void HAL_ETH_EEECallback(ETH_HandleTypeDef *heth)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(heth);
  /* NOTE : This function Should not be modified, when the callback is needed,
  the HAL_ETH_EEECallback could be implemented in the user file
  */ 
}

/**
  * @brief  ETH WAKEUP interrupt callback
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
__weak void HAL_ETH_WakeUpCallback(ETH_HandleTypeDef *heth)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(heth);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_ETH_WakeUpCallback could be implemented in the user file
   */ 
}

/**
  * @brief  Read a PHY register
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module                  
  * @param  PHYAddr: PHY port address, must be a value from 0 to 31   
  * @param  PHYReg: PHY register address, must be a value from 0 to 31
  * @param pRegValue: parameter to hold read value                  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_ReadPHYRegister(ETH_HandleTypeDef *heth, uint32_t PHYAddr, uint32_t PHYReg, uint32_t *pRegValue)
{
  uint32_t tmpreg, tickstart;
  
  /* Check for the Busy flag */
  if(READ_BIT(heth->Instance->MACMDIOAR, ETH_MACMDIOAR_MB))
  {
    return HAL_ERROR;
  }
  
  /* Get the  MACMDIOAR value */
  WRITE_REG(tmpreg, heth->Instance->MACMDIOAR);
  
  /* Prepare the MDIO Address Register value 
     - Set the PHY device address 
     - Set the PHY register address
     - Set the read mode 
     - Set the MII Busy bit */
        
  MODIFY_REG(tmpreg, ETH_MACMDIOAR_PA, (PHYAddr <<21));  
  MODIFY_REG(tmpreg, ETH_MACMDIOAR_RDA, (PHYReg << 16));
  MODIFY_REG(tmpreg, ETH_MACMDIOAR_MOC, ETH_MACMDIOAR_MOC_RD);
  SET_BIT(tmpreg, ETH_MACMDIOAR_MB);
  
  /* Write the result value into the MDII Address register */
  WRITE_REG(heth->Instance->MACMDIOAR, tmpreg);
  
  tickstart = HAL_GetTick();
  
  /* Wait for the Busy flag */
  while(READ_BIT(heth->Instance->MACMDIOAR, ETH_MACMDIOAR_MB))
  {
    if(((HAL_GetTick() - tickstart ) > ETH_MDIO_BUS_TIMEOUT))
    {
      return HAL_ERROR;
    }
  }
  
  /* Get MACMIIDR value */
  WRITE_REG(*pRegValue, (uint16_t)heth->Instance->MACMDIODR);

  return HAL_OK;
}


/**
  * @brief  Writes to a PHY register.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module 
  * @param  PHYAddr: PHY port address, must be a value from 0 to 31   
  * @param  PHYReg: PHY register address, must be a value from 0 to 31 
  * @param  RegValue: the value to write
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_WritePHYRegister(ETH_HandleTypeDef *heth, uint32_t PHYAddr, uint32_t PHYReg, uint32_t RegValue)
{
  uint32_t tmpreg, tickstart;
  
  /* Check for the Busy flag */
  if(READ_BIT(heth->Instance->MACMDIOAR, ETH_MACMDIOAR_MB))
  {
    return HAL_ERROR;
  }

  /* Get the  MACMDIOAR value */
  WRITE_REG(tmpreg, heth->Instance->MACMDIOAR);
  
  /* Prepare the MDIO Address Register value 
     - Set the PHY device address 
     - Set the PHY register address
     - Set the write mode 
     - Set the MII Busy bit */
        
  MODIFY_REG(tmpreg, ETH_MACMDIOAR_PA, (PHYAddr <<21));  
  MODIFY_REG(tmpreg, ETH_MACMDIOAR_RDA, (PHYReg << 16));
  MODIFY_REG(tmpreg, ETH_MACMDIOAR_MOC, ETH_MACMDIOAR_MOC_WR);
  SET_BIT(tmpreg, ETH_MACMDIOAR_MB);
  
  
  /* Give the value to the MII data register */
  WRITE_REG(ETH->MACMDIODR, (uint16_t)RegValue);
  
  /* Write the result value into the MII Address register */
  WRITE_REG(ETH->MACMDIOAR, tmpreg);
  
  tickstart = HAL_GetTick();
    
  /* Wait for the Busy flag */
  while(READ_BIT(heth->Instance->MACMDIOAR, ETH_MACMDIOAR_MB))
  {
    if(((HAL_GetTick() - tickstart ) > ETH_MDIO_BUS_TIMEOUT))
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup ETH_Exported_Functions_Group3 Peripheral Control functions 
  *  @brief   ETH control functions 
  *
@verbatim   
  ==============================================================================
                      ##### Peripheral Control functions #####
  ==============================================================================  
  [..]
    This subsection provides a set of functions allowing to control the ETH 
    peripheral.
    
@endverbatim
  * @{
  */
/**
  * @brief  Get the configuration of the MAC and MTL subsystems. 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  macconf: pointer to a ETH_MACConfigTypeDef structure that will hold
  *         the configuration of the MAC. 
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_ETH_GetMACConfig(ETH_HandleTypeDef *heth, ETH_MACConfigTypeDef *macconf)
{
  if (macconf == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Get MAC parameters */
  macconf->PreambleLength = READ_BIT(heth->Instance->MACCR, ETH_MACCR_PRELEN);
  macconf->DeferralCheck = (FunctionalState)(READ_BIT(heth->Instance->MACCR, ETH_MACCR_DC)>> 4);
  macconf->BackOffLimit = READ_BIT(heth->Instance->MACCR, ETH_MACCR_BL);
  macconf->RetryTransmission = (FunctionalState)(!(READ_BIT(heth->Instance->MACCR, ETH_MACCR_DR) >> 8));
  macconf->CarrierSenseDuringTransmit = (FunctionalState)(READ_BIT(heth->Instance->MACCR, ETH_MACCR_DCRS) >> 9);
  macconf->ReceiveOwn = (FunctionalState)(!(READ_BIT(heth->Instance->MACCR, ETH_MACCR_DO) >> 10));
  macconf->CarrierSenseBeforeTransmit = (FunctionalState)(READ_BIT(heth->Instance->MACCR, ETH_MACCR_ECRSFD) >> 11);
  macconf->LoopbackMode = (FunctionalState)(READ_BIT(heth->Instance->MACCR, ETH_MACCR_LM) >> 12);
  macconf->DuplexMode = READ_BIT(heth->Instance->MACCR, ETH_MACCR_DM);
  macconf->Speed = READ_BIT(heth->Instance->MACCR, ETH_MACCR_FES);
  macconf->JumboPacket = (FunctionalState)(READ_BIT(heth->Instance->MACCR, ETH_MACCR_JE) >> 16);
  macconf->Jabber = (FunctionalState)(!(READ_BIT(heth->Instance->MACCR, ETH_MACCR_JD) >>17));
  macconf->Watchdog = (FunctionalState)(!(READ_BIT(heth->Instance->MACCR, ETH_MACCR_WD) >>19));
  macconf->AutomaticPadCRCStrip = (FunctionalState)(READ_BIT(heth->Instance->MACCR, ETH_MACCR_ACS) >> 20);
  macconf->CRCStripTypePacket = (FunctionalState)(READ_BIT(heth->Instance->MACCR, ETH_MACCR_CST) >> 21);
  macconf->Support2KPacket = (FunctionalState)(READ_BIT(heth->Instance->MACCR, ETH_MACCR_S2KP) >> 22);
  macconf->GiantPacketSizeLimitControl = (FunctionalState)(READ_BIT(heth->Instance->MACCR, ETH_MACCR_GPSLCE) >> 23);
  macconf->InterPacketGapVal = READ_BIT(heth->Instance->MACCR, ETH_MACCR_IPG);
  macconf->ChecksumOffload = (FunctionalState)(READ_BIT(heth->Instance->MACCR, ETH_MACCR_IPC) >> 27);
  macconf->SourceAddrControl = READ_BIT(heth->Instance->MACCR, ETH_MACCR_SARC);
  
  macconf->GiantPacketSizeLimit = READ_BIT(heth->Instance->MACECR, ETH_MACECR_GPSL);
  macconf->CRCCheckingRxPackets = (FunctionalState)(!(READ_BIT(heth->Instance->MACECR, ETH_MACECR_DCRCC) >> 16));
  macconf->SlowProtocolDetect = (FunctionalState)(READ_BIT(heth->Instance->MACECR, ETH_MACECR_SPEN) >> 17);
  macconf->UnicastSlowProtocolPacketDetect = (FunctionalState)(READ_BIT(heth->Instance->MACECR, ETH_MACECR_USP) >> 18);
  macconf->ExtendedInterPacketGap = (FunctionalState)(READ_BIT(heth->Instance->MACECR, ETH_MACECR_EIPGEN) >> 24);
  macconf->ExtendedInterPacketGapVal = READ_BIT(heth->Instance->MACECR, ETH_MACECR_EIPG) >> 25;
  
  
  macconf->ProgrammableWatchdog = (FunctionalState)(READ_BIT(heth->Instance->MACWTR, ETH_MACWTR_PWE) >> 8);
  macconf->WatchdogTimeout = READ_BIT(heth->Instance->MACWTR, ETH_MACWTR_WTO);
  
  macconf->TransmitFlowControl = (FunctionalState)(READ_BIT(heth->Instance->MACTFCR, ETH_MACTFCR_TFE) >> 1);
  macconf->ZeroQuantaPause = (FunctionalState)(!(READ_BIT(heth->Instance->MACTFCR, ETH_MACTFCR_DZPQ) >> 7));
  macconf->PauseLowThreshold = READ_BIT(heth->Instance->MACTFCR, ETH_MACTFCR_PLT);
  macconf->PauseTime = (READ_BIT(heth->Instance->MACTFCR, ETH_MACTFCR_PT) >> 16);
  
  
  macconf->ReceiveFlowControl = (FunctionalState)READ_BIT(heth->Instance->MACRFCR, ETH_MACRFCR_RFE);
  macconf->UnicastPausePacketDetect = (FunctionalState)(READ_BIT(heth->Instance->MACRFCR, ETH_MACRFCR_UP) >> 1);
  
  macconf->TransmitQueueMode = READ_BIT(heth->Instance->MTLTQOMR, (ETH_MTLTQOMR_TTC | ETH_MTLTQOMR_TSF));
  
  macconf->ReceiveQueueMode = READ_BIT(heth->Instance->MTLRQOMR, (ETH_MTLRQOMR_RTC | ETH_MTLRQOMR_RSF));
  macconf->ForwardRxUndersizedGoodPacket = (FunctionalState)(READ_BIT(heth->Instance->MTLRQOMR, ETH_MTLRQOMR_FUP) >> 3);
  macconf->ForwardRxErrorPacket = (FunctionalState)(READ_BIT(heth->Instance->MTLRQOMR, ETH_MTLRQOMR_FEP) >> 4);
  macconf->DropTCPIPChecksumErrorPacket = (FunctionalState)(!(READ_BIT(heth->Instance->MTLRQOMR, ETH_MTLRQOMR_DISTCPEF) >> 6));
  
  return HAL_OK; 
}

/**
  * @brief  Get the configuration of the DMA. 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module 
  * @param  dmaconf: pointer to a ETH_DMAConfigTypeDef structure that will hold
  *         the configuration of the ETH DMA.       
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_ETH_GetDMAConfig(ETH_HandleTypeDef *heth, ETH_DMAConfigTypeDef *dmaconf)
{
  if (dmaconf == NULL)
  {
    return HAL_ERROR;
  }
  
  dmaconf->AddressAlignedBeats = (FunctionalState)(READ_BIT(heth->Instance->DMASBMR, ETH_DMASBMR_AAL) >> 12);
  dmaconf->BurstMode = READ_BIT(heth->Instance->DMASBMR, ETH_DMASBMR_FB | ETH_DMASBMR_MB);
  dmaconf->RebuildINCRxBurst = (FunctionalState)(READ_BIT(heth->Instance->DMASBMR, ETH_DMASBMR_RB)>> 15);
  
  dmaconf->DMAArbitration = READ_BIT(heth->Instance->DMAMR, (ETH_DMAMR_TXPR |ETH_DMAMR_PR | ETH_DMAMR_DA));
  
  dmaconf->PBLx8Mode =  (FunctionalState)(READ_BIT(heth->Instance->DMACCR, ETH_DMACCR_8PBL)>> 16);
  dmaconf->MaximumSegmentSize = READ_BIT(heth->Instance->DMACCR, ETH_DMACCR_MSS);
  
  dmaconf->FlushRxPacket = (FunctionalState)(READ_BIT(heth->Instance->DMACRCR,  ETH_DMACRCR_RPF) >> 31);
  dmaconf->RxDMABurstLength = READ_BIT(heth->Instance->DMACRCR, ETH_DMACRCR_RPBL); 
  
  dmaconf->SecondPacketOperate = (FunctionalState)(READ_BIT(heth->Instance->DMACTCR, ETH_DMACTCR_OSP) >> 4);
  dmaconf->TCPSegmentation = (FunctionalState)(READ_BIT(heth->Instance->DMACTCR, ETH_DMACTCR_TSE) >> 12);
  dmaconf->TxDMABurstLength = READ_BIT(heth->Instance->DMACTCR, ETH_DMACTCR_TPBL);
  
  return HAL_OK;
}

/**
  * @brief  Set the MAC configuration. 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module 
  * @param  macconf: pointer to a ETH_MACConfigTypeDef structure that contains
  *         the configuration of the MAC. 
  * @retval HAL status 
  */
HAL_StatusTypeDef HAL_ETH_SetMACConfig(ETH_HandleTypeDef *heth,  ETH_MACConfigTypeDef *macconf)
{
  if(macconf == NULL)
  {
    return HAL_ERROR;
  }
  
  if(heth->RxState == HAL_ETH_STATE_READY)
  {
    ETH_SetMACConfig(heth, macconf);
    
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief  Set the ETH DMA configuration. 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module   
  * @param  dmaconf: pointer to a ETH_DMAConfigTypeDef structure that will hold
  *         the configuration of the ETH DMA.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_SetDMAConfig(ETH_HandleTypeDef *heth,  ETH_DMAConfigTypeDef *dmaconf)
{
  if(dmaconf == NULL)
  {
    return HAL_ERROR;
  }
  
  if(heth->RxState == HAL_ETH_STATE_READY)
  {	
    ETH_SetDMAConfig(heth, dmaconf);
    
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief  Configures the Clock range of ETH MDIO interface.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
void HAL_ETH_SetMDIOClockRange(ETH_HandleTypeDef *heth)
{
  uint32_t tmpreg, hclk;
	
  /* Get the ETHERNET MACMDIOAR value */
  tmpreg = (heth->Instance)->MACMDIOAR;
  
	/* Clear CSR Clock Range bits */
  tmpreg &= ~ETH_MACMDIOAR_CR;  
	
	/* Get hclk frequency value */
  hclk = HAL_RCC_GetHCLKFreq();
	
	/* Set CR bits depending on hclk value */
  if((hclk >= 20000000)&&(hclk < 35000000))
  {
    /* CSR Clock Range between 20-35 MHz */
    tmpreg |= (uint32_t)ETH_MACMDIOAR_CR_DIV16;
  }
  else if((hclk >= 35000000)&&(hclk < 60000000))
  {
    /* CSR Clock Range between 35-60 MHz */ 
    tmpreg |= (uint32_t)ETH_MACMDIOAR_CR_DIV26;
  }  
  else if((hclk >= 60000000)&&(hclk < 100000000))
  {
    /* CSR Clock Range between 60-100 MHz */ 
    tmpreg |= (uint32_t)ETH_MACMDIOAR_CR_DIV42;
  }  
  else if((hclk >= 100000000)&&(hclk < 150000000))
  {
    /* CSR Clock Range between 100-150 MHz */ 
    tmpreg |= (uint32_t)ETH_MACMDIOAR_CR_DIV62;
  }
  else /* (hclk >= 150000000)&&(hclk <= 200000000) */
  {
    /* CSR Clock Range between 150-200 MHz */ 
    tmpreg |= (uint32_t)ETH_MACMDIOAR_CR_DIV102;    
  }
	
  /* Configure the CSR Clock Range */
  (heth->Instance)->MACMDIOAR = (uint32_t)tmpreg;		
}

/**
  * @brief  Set the ETH MAC (L2) Filters configuration. 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module   
  * @param  pFilterConfig: pointer to a ETH_MACFilterConfigTypeDef structure that contains
  *         the configuration of the ETH MAC filters.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_SetMACFilterConfig(ETH_HandleTypeDef *heth, ETH_MACFilterConfigTypeDef *pFilterConfig)
{
  uint32_t filterconfig;
  
  if(pFilterConfig == NULL)
  {
    return HAL_ERROR;
  }
  
  filterconfig = (pFilterConfig->PromiscuousMode | 
                  ((uint32_t)pFilterConfig->HashUnicast << 1) |
                    ((uint32_t)pFilterConfig->HashMulticast << 2)  |
                      ((uint32_t)pFilterConfig->DestAddrInverseFiltering << 3) |
                        ((uint32_t)pFilterConfig->PassAllMulticast << 4) |
                          ((uint32_t)!pFilterConfig->BroadcastFilter << 5) | 
                            ((uint32_t)pFilterConfig->SrcAddrInverseFiltering << 8) |
                              ((uint32_t)pFilterConfig->SrcAddrFiltering << 9) |
                                ((uint32_t)pFilterConfig->HachOrPerfectFilter << 10) |
                                  ((uint32_t)pFilterConfig->ReceiveAllMode << 31) | 
                                    pFilterConfig->ControlPacketsFilter);  
  
  MODIFY_REG(heth->Instance->MACPFR, ETH_MACPFR_MASK, filterconfig);

  return HAL_OK;
}

/**
  * @brief  Get the ETH MAC (L2) Filters configuration. 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module   
  * @param  pFilterConfig: pointer to a ETH_MACFilterConfigTypeDef structure that will hold
  *         the configuration of the ETH MAC filters.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_GetMACFilterConfig(ETH_HandleTypeDef *heth, ETH_MACFilterConfigTypeDef *pFilterConfig)
{
  if(pFilterConfig == NULL)
  {
    return HAL_ERROR;
  }
  
  pFilterConfig->PromiscuousMode = (FunctionalState)(READ_BIT(heth->Instance->MACPFR, ETH_MACPFR_PR));
  pFilterConfig->HashUnicast = (FunctionalState)(READ_BIT(heth->Instance->MACPFR, ETH_MACPFR_HUC) >> 1);
  pFilterConfig->HashMulticast = (FunctionalState)(READ_BIT(heth->Instance->MACPFR, ETH_MACPFR_HMC) >> 2);
  pFilterConfig->DestAddrInverseFiltering = (FunctionalState)(READ_BIT(heth->Instance->MACPFR, ETH_MACPFR_DAIF) >> 3);
  pFilterConfig->PassAllMulticast = (FunctionalState)(READ_BIT(heth->Instance->MACPFR, ETH_MACPFR_PM) >> 4);
  pFilterConfig->BroadcastFilter = (FunctionalState)(!(READ_BIT(heth->Instance->MACPFR, ETH_MACPFR_DBF) >> 5));
  pFilterConfig->ControlPacketsFilter = READ_BIT(heth->Instance->MACPFR, ETH_MACPFR_PCF);
  pFilterConfig->SrcAddrInverseFiltering = (FunctionalState)(READ_BIT(heth->Instance->MACPFR, ETH_MACPFR_SAIF) >> 8);
  pFilterConfig->SrcAddrFiltering = (FunctionalState)(READ_BIT(heth->Instance->MACPFR, ETH_MACPFR_SAF) >> 9);
  pFilterConfig->HachOrPerfectFilter = (FunctionalState)(READ_BIT(heth->Instance->MACPFR, ETH_MACPFR_HPF) >> 10);
  pFilterConfig->ReceiveAllMode = (FunctionalState)(READ_BIT(heth->Instance->MACPFR, ETH_MACPFR_RA) >> 31);
  
  return HAL_OK; 
}

/**
  * @brief  Set the source MAC Address to be matched.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  AddrNbr: The MAC address to configure
  *          This parameter must be a value of the following:
  *            ETH_MAC_ADDRESS1
  *            ETH_MAC_ADDRESS2
  *            ETH_MAC_ADDRESS3
  * @param  pMACAddr: Pointer to MAC address buffer data (6 bytes)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_SetSourceMACAddrMatch(ETH_HandleTypeDef *heth, uint32_t AddrNbr, uint8_t *pMACAddr)
{
  uint32_t macaddrhr, macaddrlr;
  
  if(pMACAddr == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Get mac addr high reg offset */
  macaddrhr = ((uint32_t)&(heth->Instance->MACA0HR) + AddrNbr);
  /* Get mac addr low reg offset */
  macaddrlr = ((uint32_t)&(heth->Instance->MACA0LR) + AddrNbr);
  
  /* Set MAC addr bits 32 to 47 */
  (*(__IO uint32_t *)macaddrhr) = ((pMACAddr[5] << 8) | pMACAddr[4]);
  /* Set MAC addr bits 0 to 31 */
  (*(__IO uint32_t *)macaddrlr) = ((pMACAddr[3] << 24) | (pMACAddr[2] << 16) | (pMACAddr[1] << 8) | pMACAddr[0]);
  
   /* Enable address and set source address bit */
  (*(__IO uint32_t *)macaddrhr) |= (ETH_MACAHR_SA | ETH_MACAHR_AE);
    
  return HAL_OK;
}

/**
  * @brief  Set the ETH Hash Table Value. 
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module   
  * @param  pHashTable: pointer to a table of two 32 bit values, that contains
  *         the 64 bits of the hash table.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETH_SetHashTable(ETH_HandleTypeDef *heth, uint32_t *pHashTable)
{
  if(pHashTable == NULL)
  {
    return HAL_ERROR; 
  }
  
  heth->Instance->MACHT0R = pHashTable[0];
  heth->Instance->MACHT1R = pHashTable[1];
  
  return HAL_OK;
}

/**
  * @brief  Set the VLAN Identifier for Rx packets
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module  
  * @param  ComparisonBits: 12 or 16 bit comparison mode 
            must be a value of @ref ETH_VLAN_Tag_Comparison
  * @param  VLANIdentifier: VLAN Identifier value
  * @retval None
  */
void HAL_ETH_SetRxVLANIdentifier(ETH_HandleTypeDef *heth, uint32_t ComparisonBits, uint32_t VLANIdentifier)
{
  if(ComparisonBits == ETH_VLANTAGCOMPARISON_16BIT)
  {
    MODIFY_REG(heth->Instance->MACVTR, ETH_MACVTR_VL , VLANIdentifier); 
    CLEAR_BIT(heth->Instance->MACVTR, ETH_MACVTR_ETV);
  }
  else
  {
    MODIFY_REG(heth->Instance->MACVTR, ETH_MACVTR_VL_VID , VLANIdentifier);
    SET_BIT(heth->Instance->MACVTR, ETH_MACVTR_ETV);
  }	
}

/**
  * @brief  Enters the Power down mode.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module      
  * @param  pPowerDownConfig: a pointer to ETH_PowerDownConfigTypeDef structure
  *         that contains the Power Down configration
  * @retval None.
  */
void HAL_ETH_EnterPowerDownMode(ETH_HandleTypeDef *heth, ETH_PowerDownConfigTypeDef *pPowerDownConfig)
{
  uint32_t powerdownconfig;
  
  powerdownconfig = (((uint32_t)pPowerDownConfig->MagicPacket << 1) | 
                     ((uint32_t)pPowerDownConfig->WakeUpPacket << 2) |
                       ((uint32_t)pPowerDownConfig->GlobalUnicast << 9) |
                         ((uint32_t)pPowerDownConfig->WakeUpForward << 10) |
                           ETH_MACPCSR_PWRDWN);
  
  /* Enable PMT interrupt */
  __HAL_ETH_MAC_ENABLE_IT(heth, ETH_MACIER_PMTIE);
  
  MODIFY_REG(heth->Instance->MACPCSR, ETH_MACPCSR_MASK, powerdownconfig);
}  

/**
  * @brief  Exits from the Power down mode.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module      
  * @retval None.
  */
void HAL_ETH_ExitPowerDownMode(ETH_HandleTypeDef *heth)
{
  /* clear wake up sources */
  CLEAR_BIT(heth->Instance->MACPCSR, ETH_MACPCSR_RWKPKTEN | ETH_MACPCSR_MGKPKTEN | ETH_MACPCSR_GLBLUCAST | ETH_MACPCSR_RWKPFE);
  
  if(READ_BIT(heth->Instance->MACPCSR, ETH_MACPCSR_PWRDWN))
  {
    /* Exit power down mode */
    CLEAR_BIT(heth->Instance->MACPCSR, ETH_MACPCSR_PWRDWN);
  }
  
  /* Disable PMT interrupt */
  __HAL_ETH_MAC_DISABLE_IT(heth, ETH_MACIER_PMTIE);
}  
 
/**
  * @brief  Set the WakeUp filter.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module   
  * @param  pFilter: pointer to filter registers values
  * @param  Count: number of filter registers, must be from 1 to 8.
  * @retval None.
  */
HAL_StatusTypeDef HAL_ETH_SetWakeUpFilter(ETH_HandleTypeDef *heth, uint32_t *pFilter, uint32_t Count)
{
  uint32_t regindex;
  
  if(pFilter == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Reset Filter Pointer */
  SET_BIT(heth->Instance->MACPCSR, ETH_MACPCSR_RWKFILTRST);
  
  /* Wake up packet filter config */
  for(regindex = 0; regindex < Count; regindex++)
  {
    /* Write filter regs */
    WRITE_REG(heth->Instance->MACRWKPFR, pFilter[regindex]);
  }
  
  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup ETH_Exported_Functions_Group4 Peripheral State and Errors functions 
  *  @brief   ETH State and Errors functions 
  *
@verbatim   
  ==============================================================================
                 ##### Peripheral State and Errors functions #####
  ==============================================================================  
 [..]
   This subsection provides a set of functions allowing to return the State of 
   ETH communication process, return Peripheral Errors occurred during communication 
   process


@endverbatim
  * @{
  */

/**
  * @brief  Returns the ETH state.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval HAL state
  */
HAL_ETH_StateTypeDef HAL_ETH_GetState(ETH_HandleTypeDef *heth)
{
  uint32_t gstate, rxstate;
  gstate = heth->gState;
  rxstate = heth->RxState;
  
  return (HAL_ETH_StateTypeDef)(gstate | rxstate);
}

/**
  * @brief  Returns the ETH error code
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval ETH Error Code
  */
uint32_t HAL_ETH_GetError(ETH_HandleTypeDef *heth)
{
  return heth->ErrorCode;
}

/**
  * @brief  Returns the ETH DMA error code
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval ETH DMA Error Code
  */
uint32_t HAL_ETH_GetDMAError(ETH_HandleTypeDef *heth)
{
  return heth->DMAErrorCode;
}

/**
  * @brief  Returns the ETH MAC error code
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval ETH MAC Error Code
  */
uint32_t HAL_ETH_GetMACError(ETH_HandleTypeDef *heth)
{
  return heth->MACErrorCode;
}

/**
  * @brief  Returns the ETH MAC WakeUp event source
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval ETH MAC WakeUp event source
  */
uint32_t HAL_ETH_GetMACWakeUpSource(ETH_HandleTypeDef *heth)
{
  return heth->MACWakeUpEvent;
}

/**
  * @}
  */

/**
  * @}
  */

static void ETH_SetMACConfig(ETH_HandleTypeDef *heth,  ETH_MACConfigTypeDef *macconf)
{
  uint32_t macregval;
  
  /*------------------------ MACCR Configuration --------------------*/  
  macregval =(macconf->InterPacketGapVal |
              macconf->SourceAddrControl |
                (uint32_t)(macconf->ChecksumOffload << 27) |  
                  (uint32_t)(macconf->GiantPacketSizeLimitControl << 23) |
                    (uint32_t)(macconf->Support2KPacket << 22) |
                      (uint32_t)(macconf->CRCStripTypePacket << 21) |
                        (uint32_t)(macconf->AutomaticPadCRCStrip << 20) | 
                          (uint32_t)(!macconf->Watchdog << 19) | 
                            (uint32_t)(!macconf->Jabber << 17) | 
                              (uint32_t)(macconf->JumboPacket << 16) |
                                macconf->Speed |
                                  macconf->DuplexMode | 
                                    (uint32_t)(macconf->LoopbackMode << 12) |
                                      (uint32_t)(macconf->CarrierSenseBeforeTransmit << 11)|
                                        (uint32_t)(!macconf->ReceiveOwn << 10)|
                                          (uint32_t)(macconf->CarrierSenseDuringTransmit << 9)|
                                            (uint32_t)(!macconf->RetryTransmission << 8)| 
                                              macconf->BackOffLimit | 
                                                (uint32_t)(macconf->DeferralCheck << 4)|
                                                  macconf->PreambleLength);
  
  /* Write to MACCR */
  MODIFY_REG(heth->Instance->MACCR, ETH_MACCR_MASK, macregval);
  
  /*------------------------ MACECR Configuration --------------------*/
  macregval = ((macconf->ExtendedInterPacketGapVal << 25)|
               (uint32_t)(macconf->ExtendedInterPacketGap << 24)|
                 (uint32_t)(macconf->UnicastSlowProtocolPacketDetect << 18)|
                   (uint32_t)(macconf->SlowProtocolDetect << 17)|
                     (uint32_t)(!macconf->CRCCheckingRxPackets << 16) |
                       macconf->GiantPacketSizeLimit);
  
  /* Write to MACECR */
  MODIFY_REG(heth->Instance->MACECR, ETH_MACECR_MASK, macregval);
  
  /*------------------------ MACWTR Configuration --------------------*/
  macregval = ((uint32_t)(macconf->ProgrammableWatchdog << 8) |
               macconf->WatchdogTimeout);
  
  /* Write to MACWTR */
  MODIFY_REG(heth->Instance->MACWTR, ETH_MACWTR_MASK, macregval);   
  
  /*------------------------ MACTFCR Configuration --------------------*/  
  macregval = ((uint32_t)(macconf->TransmitFlowControl << 1) |
               macconf->PauseLowThreshold | 
                 (uint32_t)(!macconf->ZeroQuantaPause << 7) |
                   (macconf->PauseTime << 16));
  
  /* Write to MACTFCR */
  MODIFY_REG(heth->Instance->MACTFCR, ETH_MACTFCR_MASK, macregval); 
  
  /*------------------------ MACRFCR Configuration --------------------*/  
  macregval = ((uint32_t)macconf->ReceiveFlowControl |
               (uint32_t)(macconf->UnicastPausePacketDetect << 1));
  
  /* Write to MACRFCR */
  MODIFY_REG(heth->Instance->MACRFCR, ETH_MACRFCR_MASK, macregval);
  
  /*------------------------ MTLTQOMR Configuration --------------------*/  
  /* Write to MTLTQOMR */
  MODIFY_REG(heth->Instance->MTLTQOMR, ETH_MTLTQOMR_MASK, macconf->TransmitQueueMode);
  
  /*------------------------ MTLRQOMR Configuration --------------------*/  
  macregval = (macconf->ReceiveQueueMode |
               (uint32_t)(!macconf->DropTCPIPChecksumErrorPacket << 6) |
                 (uint32_t)(macconf->ForwardRxErrorPacket << 4) |
                   (uint32_t)(macconf->ForwardRxUndersizedGoodPacket << 3));
  
  /* Write to MTLRQOMR */
  MODIFY_REG(heth->Instance->MTLRQOMR, ETH_MTLRQOMR_MASK, macregval);  
}

static void ETH_SetDMAConfig(ETH_HandleTypeDef *heth,  ETH_DMAConfigTypeDef *dmaconf)
{
  uint32_t dmaregval;

  /*------------------------ DMAMR Configuration --------------------*/    
  MODIFY_REG(heth->Instance->DMAMR, ETH_DMAMR_MASK, dmaconf->DMAArbitration);
  
  /*------------------------ DMASBMR Configuration --------------------*/
  dmaregval = ((uint32_t)(dmaconf->AddressAlignedBeats << 12) |
               dmaconf->BurstMode |
                 (uint32_t)(dmaconf->RebuildINCRxBurst << 15));
  
  MODIFY_REG(heth->Instance->DMASBMR, ETH_DMASBMR_MASK, dmaregval);
  
  /*------------------------ DMACCR Configuration --------------------*/
  dmaregval = ((uint32_t)(dmaconf->PBLx8Mode <<16) | 
               dmaconf->MaximumSegmentSize);
  
  MODIFY_REG(heth->Instance->DMACCR, ETH_DMACCR_MASK, dmaregval);
  
  /*------------------------ DMACTCR Configuration --------------------*/
  dmaregval = (dmaconf->TxDMABurstLength | 
               (uint32_t)(dmaconf->SecondPacketOperate << 4)| 
                 (uint32_t)(dmaconf->TCPSegmentation << 12));
  
  MODIFY_REG(heth->Instance->DMACTCR, ETH_DMACTCR_MASK, dmaregval);
  
  /*------------------------ DMACRCR Configuration --------------------*/
  dmaregval = ((uint32_t)(dmaconf->FlushRxPacket << 31) |
               dmaconf->RxDMABurstLength);
  
  /* Write to DMACRCR */
  MODIFY_REG(heth->Instance->DMACRCR, ETH_DMACRCR_MASK, dmaregval);
}

/**
  * @brief  Configures Ethernet MAC and DMA with default parameters.
  *         called by HAL_ETH_Init() API.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval HAL status
  */
static void ETH_MACDMAConfig(ETH_HandleTypeDef *heth)
{
  ETH_MACConfigTypeDef macDefaultConf;
  ETH_DMAConfigTypeDef dmaDefaultConf;
  
  /*--------------- ETHERNET MAC registers default Configuration --------------*/
  macDefaultConf.AutomaticPadCRCStrip = ENABLE;
  macDefaultConf.BackOffLimit = ETH_BACKOFFLIMIT_10; 
  macDefaultConf.CarrierSenseBeforeTransmit = DISABLE; 
  macDefaultConf.CarrierSenseDuringTransmit = DISABLE;
  macDefaultConf.ChecksumOffload = ENABLE; 
  macDefaultConf.CRCCheckingRxPackets = ENABLE;
  macDefaultConf.CRCStripTypePacket = ENABLE;
  macDefaultConf.DeferralCheck = DISABLE;
  macDefaultConf.DropTCPIPChecksumErrorPacket = ENABLE;
  macDefaultConf.DuplexMode = ETH_FULLDUPLEX_MODE;
  macDefaultConf.ExtendedInterPacketGap = DISABLE;
  macDefaultConf.ExtendedInterPacketGapVal = 0x0;
  macDefaultConf.ForwardRxErrorPacket = DISABLE;
  macDefaultConf.ForwardRxUndersizedGoodPacket = DISABLE;
  macDefaultConf.GiantPacketSizeLimit = 0x618;
  macDefaultConf.GiantPacketSizeLimitControl = DISABLE;
  macDefaultConf.InterPacketGapVal = ETH_INTERPACKETGAP_96BIT;
  macDefaultConf.Jabber = ENABLE;
  macDefaultConf.JumboPacket = DISABLE;
  macDefaultConf.LoopbackMode = DISABLE;
  macDefaultConf.PauseLowThreshold = ETH_PAUSELOWTHRESHOLD_MINUS_4;
  macDefaultConf.PauseTime = 0x0;
  macDefaultConf.PreambleLength = ETH_PREAMBLELENGTH_7;
  macDefaultConf.ProgrammableWatchdog = DISABLE;
  macDefaultConf.ReceiveFlowControl = DISABLE;
  macDefaultConf.ReceiveOwn = ENABLE;
  macDefaultConf.ReceiveQueueMode = ETH_RECEIVESTOREFORWARD;
  macDefaultConf.RetryTransmission = ENABLE;
  macDefaultConf.SlowProtocolDetect = DISABLE;
  macDefaultConf.SourceAddrControl = ETH_SOURCEADDRESS_REPLACE_ADDR0;
  macDefaultConf.Speed = ETH_SPEED_100M;
  macDefaultConf.Support2KPacket = DISABLE;
  macDefaultConf.TransmitQueueMode = ETH_TRANSMITSTOREFORWARD;
  macDefaultConf.TransmitFlowControl = DISABLE;
  macDefaultConf.UnicastPausePacketDetect = DISABLE;
  macDefaultConf.UnicastSlowProtocolPacketDetect = DISABLE;
  macDefaultConf.Watchdog = ENABLE;
  macDefaultConf.WatchdogTimeout =  ETH_MACWTR_WTO_2KB;
  macDefaultConf.ZeroQuantaPause = ENABLE;
  
  /* MAC default configuration */
  ETH_SetMACConfig(heth, &macDefaultConf);
  
  /*--------------- ETHERNET DMA registers default Configuration --------------*/
  dmaDefaultConf.AddressAlignedBeats = ENABLE;
  dmaDefaultConf.BurstMode = ETH_BURSTLENGTH_FIXED;
  dmaDefaultConf.DMAArbitration = ETH_DMAARBITRATION_RX1_TX1;
  dmaDefaultConf.FlushRxPacket = DISABLE;
  dmaDefaultConf.PBLx8Mode = DISABLE;
  dmaDefaultConf.RebuildINCRxBurst = DISABLE;
  dmaDefaultConf.RxDMABurstLength = ETH_RXDMABURSTLENGTH_32BEAT;
  dmaDefaultConf.SecondPacketOperate = DISABLE;
  dmaDefaultConf.TxDMABurstLength = ETH_TXDMABURSTLENGTH_32BEAT;
  dmaDefaultConf.TCPSegmentation = DISABLE;
  dmaDefaultConf.MaximumSegmentSize = 536;
  
  /* DMA default configuration */
  ETH_SetDMAConfig(heth, &dmaDefaultConf);
}

/**
  * @brief  Configures the Clock range of SMI interface.
  *         called by HAL_ETH_Init() API.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
static void ETH_MAC_MDIO_ClkConfig(ETH_HandleTypeDef *heth)
{
  uint32_t tmpreg, hclk;
  
  /* Get the ETHERNET MACMDIOAR value */
  tmpreg = (heth->Instance)->MACMDIOAR;
  
  /* Clear CSR Clock Range bits */
  tmpreg &= ~ETH_MACMDIOAR_CR;  
  
  /* Get hclk frequency value */
  hclk = HAL_RCC_GetHCLKFreq();
  
  /* Set CR bits depending on hclk value */
  if((hclk >= 20000000)&&(hclk < 35000000))
  {
    /* CSR Clock Range between 20-35 MHz */
    tmpreg |= (uint32_t)ETH_MACMDIOAR_CR_DIV16;
  }
  else if((hclk >= 35000000)&&(hclk < 60000000))
  {
    /* CSR Clock Range between 35-60 MHz */ 
    tmpreg |= (uint32_t)ETH_MACMDIOAR_CR_DIV26;
  }  
  else if((hclk >= 60000000)&&(hclk < 100000000))
  {
    /* CSR Clock Range between 60-100 MHz */ 
    tmpreg |= (uint32_t)ETH_MACMDIOAR_CR_DIV42;
  }  
  else if((hclk >= 100000000)&&(hclk < 150000000))
  {
    /* CSR Clock Range between 100-150 MHz */ 
    tmpreg |= (uint32_t)ETH_MACMDIOAR_CR_DIV62;
  }
  else /* (hclk >= 150000000)&&(hclk <= 200000000) */
  {
    /* CSR Clock Range between 150-200 MHz */ 
    tmpreg |= (uint32_t)ETH_MACMDIOAR_CR_DIV102;    
  }
  
  /* Configure the CSR Clock Range */
  (heth->Instance)->MACMDIOAR = (uint32_t)tmpreg;		
}

/**
  * @brief  Initializes the DMA Tx descriptors.
  *         called by HAL_ETH_Init() API.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module  
  * @retval None
  */
static void ETH_DMATxDescListInit(ETH_HandleTypeDef *heth)
{
  ETH_DMADescTypeDef *dmatxdesc;
  uint32_t i;
  
  /* Fill each DMATxDesc descriptor with the right values */   
  for(i=0; i < ETH_TX_DESC_CNT; i++)
  {
    dmatxdesc = heth->Init.TxDesc + i;

    WRITE_REG(dmatxdesc->DESC0, 0x0);
    WRITE_REG(dmatxdesc->DESC1, 0x0);
    WRITE_REG(dmatxdesc->DESC2, 0x0);
    WRITE_REG(dmatxdesc->DESC3, 0x0);
    
    WRITE_REG(heth->TxDescList.TxDesc[i], (uint32_t)dmatxdesc);
  }
  
  heth->TxDescList.CurTxDesc = 0;
  
  /* Set Transmit Descriptor Ring Length */
  WRITE_REG(heth->Instance->DMACTDRLR, (ETH_TX_DESC_CNT -1));
  
  /* Set Transmit Descriptor List Address */
  WRITE_REG(heth->Instance->DMACTDLAR, (uint32_t) heth->Init.TxDesc);
  
  /* Set Transmit Descriptor Tail pointer */
  WRITE_REG(heth->Instance->DMACTDTPR, (uint32_t) heth->Init.TxDesc);
}

/**
  * @brief  Initializes the DMA Rx descriptors in chain mode.
  *         called by HAL_ETH_Init() API.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module  
  * @retval None
  */
static void ETH_DMARxDescListInit(ETH_HandleTypeDef *heth)
{
  ETH_DMADescTypeDef *dmarxdesc;
  uint32_t i;
  
  for(i = 0; i < ETH_RX_DESC_CNT; i++)
  {
    dmarxdesc =  heth->Init.RxDesc + i;
    
    WRITE_REG(dmarxdesc->DESC0, 0x0);
    WRITE_REG(dmarxdesc->DESC1, 0x0);
    WRITE_REG(dmarxdesc->DESC2, 0x0);
    WRITE_REG(dmarxdesc->DESC3, 0x0);
    WRITE_REG(dmarxdesc->BackupAddr0, 0x0);
    WRITE_REG(dmarxdesc->BackupAddr1, 0x0);
    
    /* Set Rx descritors adresses */
    WRITE_REG(heth->RxDescList.RxDesc[i], (uint32_t)dmarxdesc);
  }
  
  WRITE_REG(heth->RxDescList.CurRxDesc, 0);
  WRITE_REG(heth->RxDescList.FirstAppDesc, 0);
  WRITE_REG(heth->RxDescList.AppDescNbr, 0);
  WRITE_REG(heth->RxDescList.ItMode, 0);
  WRITE_REG(heth->RxDescList.AppContextDesc, 0);
  
  /* Set Receive Descriptor Ring Length */
  WRITE_REG(heth->Instance->DMACRDRLR, (ETH_RX_DESC_CNT - 1));
  
  /* Set Receive Descriptor List Address */
  WRITE_REG(heth->Instance->DMACRDLAR, (uint32_t) heth->Init.RxDesc);
  
  /* Set Receive Descriptor Tail pointer Address */
  WRITE_REG(heth->Instance->DMACRDTPR, ((uint32_t)heth->Init.RxDesc + ((ETH_RX_DESC_CNT - 1)*sizeof(ETH_DMADescTypeDef))));
}

/**
  * @brief  Prepare Tx DMA descriptor before transmission.
  *         called by HAL_ETH_Transmit_IT and HAL_ETH_Transmit_IT() API.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module  
  * @param  pTxConfig: Tx packet configuration 
  * @param  ItMode: Enable or disable Tx EOT interrept     
  * @retval Status
  */
static uint32_t ETH_Prepare_Tx_Descriptors(ETH_HandleTypeDef *heth, ETH_TxPacketConfig *pTxConfig, uint32_t ItMode)
{
  ETH_TxDescListTypeDef *dmatxdesclist = &heth->TxDescList; 
  uint32_t descidx = dmatxdesclist->CurTxDesc;
  uint32_t firstdescidx = dmatxdesclist->CurTxDesc;
  uint32_t descnbr = 0, idx;
  ETH_DMADescTypeDef *dmatxdesc = (ETH_DMADescTypeDef *)dmatxdesclist->TxDesc[descidx];
  
  ETH_BufferTypeDef  *txbuffer = pTxConfig->TxBuffer;
  
  /* Current Tx Descriptor Owned by DMA: cannot be used by the application  */
  if(READ_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCWBF_OWN) == ETH_DMATXNDESCWBF_OWN)
  {
    return HAL_ETH_ERROR_BUSY;
  }
  
  /***************************************************************************/
  /*****************    Context descriptor configuration (Optional) **********/
  /***************************************************************************/
  /* If VLAN tag is enabled for this packet */
  if(READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_VLANTAG))
  {
    /* Set vlan tag value */
    MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXCDESC_VT, pTxConfig->VlanTag);
    /* Set vlan tag valid bit */
    SET_BIT(dmatxdesc->DESC3, ETH_DMATXCDESC_VLTV);
    /* Set the descriptor as the vlan input source */
    SET_BIT(heth->Instance->MACVIR, ETH_MACVIR_VLTI);
    
    /* if inner VLAN is enabled */
    if(READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_INNERVLANTAG))
    {
      /* Set inner vlan tag value */
      MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXCDESC_IVT, (pTxConfig->InnerVlanTag << 16));
      /* Set inner vlan tag valid bit */
      SET_BIT(dmatxdesc->DESC3, ETH_DMATXCDESC_IVLTV);
      
      /* Set Vlan Tag control */
      MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXCDESC_IVTIR, pTxConfig->InnerVlanCtrl);
      
      /* Set the descriptor as the inner vlan input source */
      SET_BIT(heth->Instance->MACIVIR, ETH_MACIVIR_VLTI);
      /* Enable double VLAN processing */
      SET_BIT(heth->Instance->MACVTR, ETH_MACVTR_EDVLP);
    }
  }
  
  /* if tcp segementation is enabled for this packet */
  if(READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_TSO))
  {
    /* Set MSS value */
    MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXCDESC_MSS, pTxConfig->MaxSegmentSize);
    /* Set MSS valid bit */
    SET_BIT(dmatxdesc->DESC3, ETH_DMATXCDESC_TCMSSV);
  }
  
  if((READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_VLANTAG)) || (READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_TSO)))
  {
    /* Set as context descriptor */
    SET_BIT(dmatxdesc->DESC3, ETH_DMATXCDESC_CTXT);
    /* Set own bit */
    SET_BIT(dmatxdesc->DESC3, ETH_DMATXCDESC_OWN);
    /* Increment current tx descriptor index */
    INCR_TX_DESC_INDEX(descidx, 1);
    /* Get current descriptor address */
    dmatxdesc = (ETH_DMADescTypeDef *)dmatxdesclist->TxDesc[descidx];
    
    descnbr += 1U;
    
    /* Current Tx Descriptor Owned by DMA: cannot be used by the application  */
    if(READ_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCWBF_OWN) == ETH_DMATXNDESCWBF_OWN)
    {
      dmatxdesc = (ETH_DMADescTypeDef *)dmatxdesclist->TxDesc[firstdescidx];
      /* Clear own bit */
      CLEAR_BIT(dmatxdesc->DESC3, ETH_DMATXCDESC_OWN);
      
      return HAL_ETH_ERROR_BUSY;
    }
  }
  
  /***************************************************************************/
  /*****************    Normal descriptors configuration     *****************/
  /***************************************************************************/
  
  descnbr += 1U;
  
  /* Set header or buffer 1 address */
  WRITE_REG(dmatxdesc->DESC0, (uint32_t)txbuffer->buffer);
  /* Set header or buffer 1 Length */
  MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXNDESCRF_B1L, txbuffer->len);
  
  if(txbuffer->next != NULL)
  {
    txbuffer = txbuffer->next; 
    /* Set buffer 2 address */
    WRITE_REG(dmatxdesc->DESC1, (uint32_t)txbuffer->buffer);
    /* Set buffer 2 Length */
    MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXNDESCRF_B2L, (txbuffer->len << 16));
  }
  else
  {
    WRITE_REG(dmatxdesc->DESC1, 0x0);
    /* Set buffer 2 Length */
    MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXNDESCRF_B2L, 0x0);		
  }
  
  if(READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_TSO))
  {
    /* Set TCP Header length */
    MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_THL, (pTxConfig->TCPHeaderLen << 19));
    /* Set TCP payload length */
    MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_TPL, pTxConfig->PayloadLen);	
    /* Set TCP Segmentation Enabled bit */
    SET_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_TSE);
  }
  else
  {
    MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_FL, pTxConfig->Length);
    
    if(READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_CSUM))
    {
      MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_CIC, pTxConfig->ChecksumCtrl);
    }
    
    if(READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_CRCPAD))
    {
      MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_CPC, pTxConfig->CRCPadCtrl);
    }
  }
  
  if(READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_VLANTAG))
  {
    /* Set Vlan Tag control */
    MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXNDESCRF_VTIR, pTxConfig->VlanCtrl);		
  }
  
  /* Mark it as First Descriptor */
  SET_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_FD);
  /* Mark it as NORMAL descriptor */
  CLEAR_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_CTXT); 
  /* set OWN bit of FIRST descriptor */
  SET_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_OWN);
  
  /* If source address insertion/replacement is enabled for this packet */
  if(READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_SAIC))
  {
    MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_SAIC, pTxConfig->SrcAddrCtrl);
  }
  
  /* only if the packet is splitted into more than one descriptors > 1 */
  while (txbuffer->next != NULL)
  {
    /* Increment current tx descriptor index */
    INCR_TX_DESC_INDEX(descidx, 1);
    /* Get current descriptor address */
    dmatxdesc = (ETH_DMADescTypeDef *)dmatxdesclist->TxDesc[descidx];
    
    /* Current Tx Descriptor Owned by DMA: cannot be used by the application  */
    if(READ_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_OWN) == ETH_DMATXNDESCRF_OWN)
    {
      descidx = firstdescidx;
      dmatxdesc = (ETH_DMADescTypeDef *)dmatxdesclist->TxDesc[descidx];
      
      /* clear previous desc own bit */
      for(idx = 0; idx < descnbr; idx ++)
      {
        CLEAR_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_OWN);
        
        /* Increment current tx descriptor index */
        INCR_TX_DESC_INDEX(descidx, 1);
        /* Get current descriptor address */
        dmatxdesc = (ETH_DMADescTypeDef *)dmatxdesclist->TxDesc[descidx];
      }
      
      return HAL_ETH_ERROR_BUSY;
    }
    
    descnbr += 1U;
    
    /* Get the next Tx buffer in the list */
    txbuffer = (struct __ETH_BufferTypeDef *)txbuffer->next;
    
    /* Set header or buffer 1 address */
    WRITE_REG(dmatxdesc->DESC0, (uint32_t)txbuffer->buffer);
    /* Set header or buffer 1 Length */
    MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXNDESCRF_B1L, txbuffer->len);
    
    if (txbuffer->next != NULL)
    {
      /* Get the next Tx buffer in the list */
      txbuffer = (struct __ETH_BufferTypeDef *)txbuffer->next;
      /* Set buffer 2 address */
      WRITE_REG(dmatxdesc->DESC1, (uint32_t)txbuffer->buffer);
      /* Set buffer 2 Length */
      MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXNDESCRF_B2L, (txbuffer->len << 16));
    }
    else
    {
      WRITE_REG(dmatxdesc->DESC1, 0x0);
      /* Set buffer 2 Length */
      MODIFY_REG(dmatxdesc->DESC2, ETH_DMATXNDESCRF_B2L, 0x0);		
    }
    
    if(READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_TSO))
    {
      /* Set TCP payload length */
      MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_TPL, pTxConfig->PayloadLen);	
      /* Set TCP Segmentation Enabled bit */
      SET_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_TSE);
    }
    else
    {
      /* Set the packet length */
      MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_FL, pTxConfig->Length);  
      
      if(READ_BIT(pTxConfig->Attributes, ETH_TX_PACKETS_FEATURES_CSUM))
      {
        /* Checksum Insertion Control */
        MODIFY_REG(dmatxdesc->DESC3, ETH_DMATXNDESCRF_CIC, pTxConfig->ChecksumCtrl);
      }
    }
    
    /* Set Own bit */
    SET_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_OWN);
    /* Mark it as NORMAL descriptor */
    CLEAR_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_CTXT);
  }
  
  if(ItMode != ((uint32_t)RESET))
  {
    /* Set Interrupt on completition bit */
    SET_BIT(dmatxdesc->DESC2, ETH_DMATXNDESCRF_IOC);     
  }
  else
  {    
    /* Clear Interrupt on completition bit */
    CLEAR_BIT(dmatxdesc->DESC2, ETH_DMATXNDESCRF_IOC); 
  }
      
  /* Mark it as LAST descriptor */
  SET_BIT(dmatxdesc->DESC3, ETH_DMATXNDESCRF_LD); 
  
  dmatxdesclist->CurTxDesc = descidx;
  
  /* Return function status */
  return HAL_ETH_ERROR_NONE;
}

#endif /* HAL_ETH_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
