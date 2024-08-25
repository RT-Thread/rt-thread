/**
  ******************************************************************************
  * @file    stm32h7xx_hal_mdma.c
  * @author  MCD Application Team
  * @brief  This file provides firmware functions to manage the following
  *         functionalities of the Master Direct Memory Access (MDMA) peripheral:
  *           + Initialization/de-initialization functions
  *           + I/O operation functions
  *           + Peripheral State and errors functions
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
   (#) Enable and configure the peripheral to be connected to the MDMA Channel
       (except for internal SRAM/FLASH memories: no initialization is
       necessary) please refer to Reference manual for connection between peripherals
       and MDMA requests.

   (#)
       For a given Channel use HAL_MDMA_Init function to program the required configuration through the following parameters:
       transfer request , channel priority, data endianness, Source increment, destination increment ,
       source data size, destination data size, data alignment, source Burst, destination Burst ,
       buffer Transfer Length, Transfer Trigger Mode (buffer transfer, block transfer, repeated block transfer
       or full transfer) source and destination block address offset, mask address and data.

       If using the MDMA in linked list mode then use function HAL_MDMA_LinkedList_CreateNode to fill a transfer node.
       Note that parameters given to the function HAL_MDMA_Init corresponds always to the node zero.
       Use function HAL_MDMA_LinkedList_AddNode to connect the created node to the linked list at a given position.
       User can make a linked list circular using function HAL_MDMA_LinkedList_EnableCircularMode , this function will automatically connect the
       last node of the list to the first one in order to make the list circular.
       In this case the linked list will loop on node 1 : first node connected after the initial transfer defined by the HAL_MDMA_Init

      -@-   The initial transfer itself (node 0 corresponding to the Init).
            User can disable the circular mode using function HAL_MDMA_LinkedList_DisableCircularMode, this function will then remove
            the connection between last node and first one.

       Function HAL_MDMA_LinkedList_RemoveNode can be used to remove (disconnect) a node from the transfer linked list.
       When a linked list is circular (last node connected to first one), if removing node1  (node where the linked list loops),
       the linked list remains circular and node 2 becomes the first one.
       Note that if the linked list is made circular the transfer will loop infinitely (or until aborted by the user).

    [..]
       (+) User can select the transfer trigger mode (parameter TransferTriggerMode) to define the amount of data to be
           transfer upon a request :
             (++) MDMA_BUFFER_TRANSFER : each request triggers a transfer of BufferTransferLength data
               with BufferTransferLength defined within the HAL_MDMA_Init.
             (++) MDMA_BLOCK_TRANSFER : each request triggers a transfer of a block
               with block size defined within the function HAL_MDMA_Start/HAL_MDMA_Start_IT
               or within the current linked list node parameters.
             (++) MDMA_REPEAT_BLOCK_TRANSFER : each request triggers a transfer of a number of blocks
               with block size and number of blocks defined within the function HAL_MDMA_Start/HAL_MDMA_Start_IT
               or within the current linked list node parameters.
             (++) MDMA_FULL_TRANSFER : each request triggers a full transfer
              all blocks and all nodes(if a linked list has been created using HAL_MDMA_LinkedList_CreateNode \ HAL_MDMA_LinkedList_AddNode).

     *** Polling mode IO operation ***
     =================================
    [..]
          (+) Use HAL_MDMA_Start() to start MDMA transfer after the configuration of Source
              address and destination address and the Length of data to be transferred.
          (+) Use HAL_MDMA_PollForTransfer() to poll for the end of current transfer or a transfer level
             In this case a fixed Timeout can be configured by User depending from his application.
          (+) Use HAL_MDMA_Abort() function to abort the current transfer : blocking method this API returns
              when the abort ends or timeout (should not be called from an interrupt service routine).

     *** Interrupt mode IO operation ***
     ===================================
    [..]
          (+) Configure the MDMA interrupt priority using HAL_NVIC_SetPriority()
          (+) Enable the MDMA IRQ handler using HAL_NVIC_EnableIRQ()
          (+) Use HAL_MDMA_Start_IT() to start MDMA transfer after the configuration of
              Source address and destination address and the Length of data to be transferred. In this
              case the MDMA interrupt is configured.
          (+) Use HAL_MDMA_IRQHandler() called under MDMA_IRQHandler() Interrupt subroutine
          (+) At the end of data transfer HAL_MDMA_IRQHandler() function is executed and user can
              add his own function by customization of function pointer XferCpltCallback and
              XferErrorCallback (i.e a member of MDMA handle structure).

          (+) Use HAL_MDMA_Abort_IT() function to abort the current transfer : non-blocking method. This API will finish the execution immediately
              then the callback XferAbortCallback (if specified  by the user) is asserted once the MDMA channel has effectively aborted.
              (could be called from an interrupt service routine).

          (+) Use functions HAL_MDMA_RegisterCallback and HAL_MDMA_UnRegisterCallback respectevely to register unregister user callbacks
              from the following list :
              (++) XferCpltCallback            : transfer complete callback.
              (++) XferBufferCpltCallback      : buffer transfer complete callback.
              (++) XferBlockCpltCallback       : block transfer complete callback.
              (++) XferRepeatBlockCpltCallback : repeated block transfer complete callback.
              (++) XferErrorCallback           : transfer error callback.
              (++) XferAbortCallback           : transfer abort complete callback.

    [..]
         (+)  If the transfer Request corresponds to SW request (MDMA_REQUEST_SW) User can use function HAL_MDMA_GenerateSWRequest to
              trigger requests manually. Function HAL_MDMA_GenerateSWRequest must be used with the following precautions:
              (++) This function returns an error if used while the Transfer has ended or not started.
              (++) If used while the current request has not been served yet (current request transfer on going)
                this function returns an error and the new request is ignored.

              Generally this function should be used in conjunctions with the MDMA callbacks:
              (++) example 1:
                 (+++) Configure a transfer with request set to MDMA_REQUEST_SW and trigger mode set to MDMA_BUFFER_TRANSFER
                 (+++) Register a callback for buffer transfer complete (using callback ID set to HAL_MDMA_XFER_BUFFERCPLT_CB_ID)
                 (+++) After calling HAL_MDMA_Start_IT the MDMA will issue the transfer of a first BufferTransferLength data.
                 (+++) When the buffer transfer complete callback is asserted first buffer has been transferred and user can ask for a new buffer transfer
                   request using HAL_MDMA_GenerateSWRequest.

              (++) example 2:
                 (+++) Configure a transfer with request set to MDMA_REQUEST_SW and trigger mode set to MDMA_BLOCK_TRANSFER
                 (+++) Register a callback for block transfer complete (using callback ID HAL_MDMA_XFER_BLOCKCPLT_CB_ID)
                 (+++) After calling HAL_MDMA_Start_IT the MDMA will issue the transfer of a first block of data.
                 (+++) When the block transfer complete callback is asserted the first block has been transferred and user can ask
                   for a new block transfer request using HAL_MDMA_GenerateSWRequest.

    [..]  Use HAL_MDMA_GetState() function to return the MDMA state and HAL_MDMA_GetError() in case of error detection.

     *** MDMA HAL driver macros list ***
     =============================================
     [..]
       Below the list of most used macros in MDMA HAL driver.

      (+) __HAL_MDMA_ENABLE: Enable the specified MDMA Channel.
      (+) __HAL_MDMA_DISABLE: Disable the specified MDMA Channel.
      (+) __HAL_MDMA_GET_FLAG: Get the MDMA Channel pending flags.
      (+) __HAL_MDMA_CLEAR_FLAG: Clear the MDMA Channel pending flags.
      (+) __HAL_MDMA_ENABLE_IT: Enable the specified MDMA Channel interrupts.
      (+) __HAL_MDMA_DISABLE_IT: Disable the specified MDMA Channel interrupts.
      (+) __HAL_MDMA_GET_IT_SOURCE: Check whether the specified MDMA Channel interrupt has occurred or not.

     [..]
      (@) You can refer to the header file of the MDMA HAL driver for more useful macros.

    [..]

  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @defgroup MDMA  MDMA
  * @brief MDMA HAL module driver
  * @{
  */

#ifdef HAL_MDMA_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup MDMA_Private_Constants
 * @{
 */
#define HAL_TIMEOUT_MDMA_ABORT    5U    /* 5 ms */
#define HAL_MDMA_CHANNEL_SIZE     0x40U /* an MDMA instance channel size is 64 byte  */
/**
  * @}
  */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @addtogroup MDMA_Private_Functions_Prototypes
  * @{
  */
static void MDMA_SetConfig(MDMA_HandleTypeDef *hmdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t BlockDataLength, uint32_t BlockCount);
static void MDMA_Init(MDMA_HandleTypeDef *hmdma);

/**
  * @}
  */

/** @addtogroup MDMA_Exported_Functions MDMA Exported Functions
  * @{
  */

/** @addtogroup MDMA_Exported_Functions_Group1
  *
@verbatim
 ===============================================================================
             ##### Initialization and de-initialization functions  #####
 ===============================================================================
    [..]
    This section provides functions allowing to :
      Initialize and de-initialize the MDMA channel.
      Register and Unregister MDMA callbacks
    [..]
    The HAL_MDMA_Init() function follows the MDMA channel configuration procedures as described in
    reference manual.
    The HAL_MDMA_DeInit function allows to deinitialize the MDMA channel.
    HAL_MDMA_RegisterCallback and  HAL_MDMA_UnRegisterCallback functions allows
    respectevely to register/unregister an MDMA callback function.

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the MDMA according to the specified
  *         parameters in the MDMA_InitTypeDef and create the associated handle.
  * @param  hmdma: Pointer to a MDMA_HandleTypeDef structure that contains
  *               the configuration information for the specified MDMA Channel.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_Init(MDMA_HandleTypeDef *hmdma)
{
  uint32_t tickstart = HAL_GetTick();

  /* Check the MDMA peripheral handle */
  if(hmdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_MDMA_STREAM_ALL_INSTANCE(hmdma->Instance));
  assert_param(IS_MDMA_PRIORITY(hmdma->Init.Priority));
  assert_param(IS_MDMA_ENDIANNESS_MODE(hmdma->Init.Endianness));
  assert_param(IS_MDMA_REQUEST(hmdma->Init.Request));
  assert_param(IS_MDMA_SOURCE_INC(hmdma->Init.SourceInc));
  assert_param(IS_MDMA_DESTINATION_INC(hmdma->Init.DestinationInc));
  assert_param(IS_MDMA_SOURCE_DATASIZE(hmdma->Init.SourceDataSize));
  assert_param(IS_MDMA_DESTINATION_DATASIZE(hmdma->Init.DestDataSize));
  assert_param(IS_MDMA_DATA_ALIGNMENT(hmdma->Init.DataAlignment));
  assert_param(IS_MDMA_SOURCE_BURST(hmdma->Init.SourceBurst));
  assert_param(IS_MDMA_DESTINATION_BURST(hmdma->Init.DestBurst));
  assert_param(IS_MDMA_BUFFER_TRANSFER_LENGTH(hmdma->Init.BufferTransferLength));
  assert_param(IS_MDMA_TRANSFER_TRIGGER_MODE(hmdma->Init.TransferTriggerMode));
  assert_param(IS_MDMA_BLOCK_ADDR_OFFSET(hmdma->Init.SourceBlockAddressOffset));
  assert_param(IS_MDMA_BLOCK_ADDR_OFFSET(hmdma->Init.DestBlockAddressOffset));


  /* Allocate lock resource */
  __HAL_UNLOCK(hmdma);

  /* Change MDMA peripheral state */
  hmdma->State = HAL_MDMA_STATE_BUSY;

  /* Disable the MDMA channel */
  __HAL_MDMA_DISABLE(hmdma);

  /* Check if the MDMA channel is effectively disabled */
  while((hmdma->Instance->CCR & MDMA_CCR_EN) != 0U)
  {
    /* Check for the Timeout */
    if((HAL_GetTick() - tickstart ) > HAL_TIMEOUT_MDMA_ABORT)
    {
      /* Update error code */
      hmdma->ErrorCode = HAL_MDMA_ERROR_TIMEOUT;

      /* Change the MDMA state */
      hmdma->State = HAL_MDMA_STATE_ERROR;

      return HAL_ERROR;
    }
  }

  /* Initialize the MDMA channel registers */
  MDMA_Init(hmdma);

  /* Reset the MDMA first/last linkedlist node addresses and node counter */
  hmdma->FirstLinkedListNodeAddress  = 0;
  hmdma->LastLinkedListNodeAddress   = 0;
  hmdma->LinkedListNodeCounter  = 0;

  /* Initialize the error code */
  hmdma->ErrorCode = HAL_MDMA_ERROR_NONE;

  /* Initialize the MDMA state */
  hmdma->State = HAL_MDMA_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  DeInitializes the MDMA peripheral
  * @param  hmdma: pointer to a MDMA_HandleTypeDef structure that contains
  *               the configuration information for the specified MDMA Channel.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_DeInit(MDMA_HandleTypeDef *hmdma)
{

  /* Check the MDMA peripheral handle */
  if(hmdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Disable the selected MDMA Channelx */
  __HAL_MDMA_DISABLE(hmdma);

  /* Reset MDMA Channel control register */
  hmdma->Instance->CCR  = 0;
  hmdma->Instance->CTCR = 0;
  hmdma->Instance->CBNDTR = 0;
  hmdma->Instance->CSAR = 0;
  hmdma->Instance->CDAR = 0;
  hmdma->Instance->CBRUR = 0;
  hmdma->Instance->CLAR = 0;
  hmdma->Instance->CTBR = 0;
  hmdma->Instance->CMAR = 0;
  hmdma->Instance->CMDR = 0;

  /* Clear all flags */
  __HAL_MDMA_CLEAR_FLAG(hmdma,(MDMA_FLAG_TE | MDMA_FLAG_CTC | MDMA_FLAG_BRT | MDMA_FLAG_BT | MDMA_FLAG_BFTC));

  /* Reset the  MDMA first/last linkedlist node addresses and node counter */
  hmdma->FirstLinkedListNodeAddress  = 0;
  hmdma->LastLinkedListNodeAddress   = 0;
  hmdma->LinkedListNodeCounter  = 0;

  /* Initialize the error code */
  hmdma->ErrorCode = HAL_MDMA_ERROR_NONE;

  /* Initialize the MDMA state */
  hmdma->State = HAL_MDMA_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hmdma);

  return HAL_OK;
}

/**
  * @brief  Config the Post request Mask address and Mask data
  * @param  hmdma      : pointer to a MDMA_HandleTypeDef structure that contains
  *                               the configuration information for the specified MDMA Channel.
  * @param  MaskAddress: specifies the address to be updated (written) with MaskData after a request is served.
  * @param  MaskData:    specifies the value to be written to MaskAddress after a request is served.
  *                      MaskAddress and MaskData could be used to automatically clear a peripheral flag when the request is served.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_ConfigPostRequestMask(MDMA_HandleTypeDef *hmdma, uint32_t MaskAddress, uint32_t MaskData)
{
  HAL_StatusTypeDef  status = HAL_OK;

  /* Check the MDMA peripheral handle */
  if(hmdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hmdma);

  if(HAL_MDMA_STATE_READY == hmdma->State)
  {
    /* if HW request set Post Request MaskAddress and MaskData,  */
    if((hmdma->Instance->CTCR & MDMA_CTCR_SWRM) == 0U)
    {
      /* Set the HW request clear Mask and Data */
      hmdma->Instance->CMAR = MaskAddress;
      hmdma->Instance->CMDR = MaskData;

      /*
      -If the request is done by SW : BWM could be set to 1 or 0.
      -If the request is done by a peripheral :
         If mask address not set (0) => BWM must be set to 0
         If mask address set (different than 0) => BWM could be set to 1 or 0
      */
      if(MaskAddress == 0U)
      {
        hmdma->Instance->CTCR &=  ~MDMA_CTCR_BWM;
      }
      else
      {
        hmdma->Instance->CTCR |=  MDMA_CTCR_BWM;
      }
    }
    else
    {
      /* Return error status */
      status =  HAL_ERROR;
    }
  }
  else
  {
    /* Return error status */
    status =  HAL_ERROR;
  }
  /* Release Lock */
  __HAL_UNLOCK(hmdma);

  return status;
}

/**
  * @brief  Register callbacks
  * @param  hmdma:                pointer to a MDMA_HandleTypeDef structure that contains
  *                               the configuration information for the specified MDMA Channel.
  * @param  CallbackID:           User Callback identifier
  * @param  pCallback:            pointer to callbacsk function.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_RegisterCallback(MDMA_HandleTypeDef *hmdma, HAL_MDMA_CallbackIDTypeDef CallbackID, void (* pCallback)(MDMA_HandleTypeDef *_hmdma))
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the MDMA peripheral handle */
  if(hmdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hmdma);

  if(HAL_MDMA_STATE_READY == hmdma->State)
  {
    switch (CallbackID)
    {
    case  HAL_MDMA_XFER_CPLT_CB_ID:
      hmdma->XferCpltCallback = pCallback;
      break;

    case  HAL_MDMA_XFER_BUFFERCPLT_CB_ID:
      hmdma->XferBufferCpltCallback = pCallback;
      break;

    case  HAL_MDMA_XFER_BLOCKCPLT_CB_ID:
      hmdma->XferBlockCpltCallback = pCallback;
      break;

    case  HAL_MDMA_XFER_REPBLOCKCPLT_CB_ID:
      hmdma->XferRepeatBlockCpltCallback = pCallback;
      break;

    case  HAL_MDMA_XFER_ERROR_CB_ID:
      hmdma->XferErrorCallback = pCallback;
      break;

    case  HAL_MDMA_XFER_ABORT_CB_ID:
      hmdma->XferAbortCallback = pCallback;
      break;

    default:
      break;
    }
  }
  else
  {
    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hmdma);

  return status;
}

/**
  * @brief  UnRegister callbacks
  * @param  hmdma:                 pointer to a MDMA_HandleTypeDef structure that contains
  *                               the configuration information for the specified MDMA Channel.
  * @param  CallbackID:           User Callback identifier
  *                               a HAL_MDMA_CallbackIDTypeDef ENUM as parameter.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_UnRegisterCallback(MDMA_HandleTypeDef *hmdma, HAL_MDMA_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the MDMA peripheral handle */
  if(hmdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hmdma);

  if(HAL_MDMA_STATE_READY == hmdma->State)
  {
    switch (CallbackID)
    {
    case  HAL_MDMA_XFER_CPLT_CB_ID:
      hmdma->XferCpltCallback = NULL;
      break;

    case  HAL_MDMA_XFER_BUFFERCPLT_CB_ID:
      hmdma->XferBufferCpltCallback = NULL;
      break;

    case  HAL_MDMA_XFER_BLOCKCPLT_CB_ID:
      hmdma->XferBlockCpltCallback = NULL;
      break;

    case  HAL_MDMA_XFER_REPBLOCKCPLT_CB_ID:
      hmdma->XferRepeatBlockCpltCallback = NULL;
      break;

    case  HAL_MDMA_XFER_ERROR_CB_ID:
      hmdma->XferErrorCallback = NULL;
      break;

    case  HAL_MDMA_XFER_ABORT_CB_ID:
      hmdma->XferAbortCallback = NULL;
      break;

    case   HAL_MDMA_XFER_ALL_CB_ID:
      hmdma->XferCpltCallback = NULL;
      hmdma->XferBufferCpltCallback = NULL;
      hmdma->XferBlockCpltCallback = NULL;
      hmdma->XferRepeatBlockCpltCallback = NULL;
      hmdma->XferErrorCallback = NULL;
      hmdma->XferAbortCallback = NULL;
      break;

    default:
      status = HAL_ERROR;
      break;
    }
  }
  else
  {
    status = HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hmdma);

  return status;
}

/**
  * @}
  */

/** @addtogroup MDMA_Exported_Functions_Group2
 *
@verbatim
 ===============================================================================
                      #####  Linked list operation functions  #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Create a linked list node
      (+) Add a node to the MDMA linked list
      (+) Remove a node from the MDMA linked list
      (+) Enable/Disable linked list circular mode
@endverbatim
  * @{
  */

/**
  * @brief  Initializes an MDMA Link Node according to the specified
  *         parameters in the pMDMA_LinkedListNodeConfig .
  * @param  pNode: Pointer to a MDMA_LinkNodeTypeDef structure that contains Linked list node
  *         registers configurations.
  * @param  pNodeConfig: Pointer to a MDMA_LinkNodeConfTypeDef structure that contains
  *               the configuration information for the specified MDMA Linked List Node.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_LinkedList_CreateNode(MDMA_LinkNodeTypeDef *pNode, MDMA_LinkNodeConfTypeDef *pNodeConfig)
{
  uint32_t addressMask;
  uint32_t blockoffset;

  /* Check the MDMA peripheral state */
  if((pNode == NULL) || (pNodeConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_MDMA_PRIORITY(pNodeConfig->Init.Priority));
  assert_param(IS_MDMA_ENDIANNESS_MODE(pNodeConfig->Init.Endianness));
  assert_param(IS_MDMA_REQUEST(pNodeConfig->Init.Request));
  assert_param(IS_MDMA_SOURCE_INC(pNodeConfig->Init.SourceInc));
  assert_param(IS_MDMA_DESTINATION_INC(pNodeConfig->Init.DestinationInc));
  assert_param(IS_MDMA_SOURCE_DATASIZE(pNodeConfig->Init.SourceDataSize));
  assert_param(IS_MDMA_DESTINATION_DATASIZE(pNodeConfig->Init.DestDataSize));
  assert_param(IS_MDMA_DATA_ALIGNMENT(pNodeConfig->Init.DataAlignment));
  assert_param(IS_MDMA_SOURCE_BURST(pNodeConfig->Init.SourceBurst));
  assert_param(IS_MDMA_DESTINATION_BURST(pNodeConfig->Init.DestBurst));
  assert_param(IS_MDMA_BUFFER_TRANSFER_LENGTH(pNodeConfig->Init.BufferTransferLength));
  assert_param(IS_MDMA_TRANSFER_TRIGGER_MODE(pNodeConfig->Init.TransferTriggerMode));
  assert_param(IS_MDMA_BLOCK_ADDR_OFFSET(pNodeConfig->Init.SourceBlockAddressOffset));
  assert_param(IS_MDMA_BLOCK_ADDR_OFFSET(pNodeConfig->Init.DestBlockAddressOffset));

  assert_param(IS_MDMA_TRANSFER_LENGTH(pNodeConfig->BlockDataLength));
  assert_param(IS_MDMA_BLOCK_COUNT(pNodeConfig->BlockCount));


  /* Configure next Link node Address Register to zero */
  pNode->CLAR =  0;

  /* Configure the Link Node registers*/
  pNode->CTBR   = 0;
  pNode->CMAR   = 0;
  pNode->CMDR   = 0;
  pNode->Reserved = 0;

  /* Write new CTCR Register value */
  pNode->CTCR =  pNodeConfig->Init.SourceInc | pNodeConfig->Init.DestinationInc | \
    pNodeConfig->Init.SourceDataSize | pNodeConfig->Init.DestDataSize           | \
      pNodeConfig->Init.DataAlignment| pNodeConfig->Init.SourceBurst            | \
        pNodeConfig->Init.DestBurst                                             | \
          ((pNodeConfig->Init.BufferTransferLength - 1U) << MDMA_CTCR_TLEN_Pos) | \
            pNodeConfig->Init.TransferTriggerMode;

  /* If SW request set the CTCR register to SW Request Mode*/
  if(pNodeConfig->Init.Request == MDMA_REQUEST_SW)
  {
    pNode->CTCR |= MDMA_CTCR_SWRM;
  }

  /*
  -If the request is done by SW : BWM could be set to 1 or 0.
  -If the request is done by a peripheral :
     If mask address not set (0) => BWM must be set to 0
     If mask address set (different than 0) => BWM could be set to 1 or 0
  */
  if((pNodeConfig->Init.Request == MDMA_REQUEST_SW) || (pNodeConfig->PostRequestMaskAddress != 0U))
  {
    pNode->CTCR |=  MDMA_CTCR_BWM;
  }

  /* Set the new CBNDTR Register value */
  pNode->CBNDTR = ((pNodeConfig->BlockCount - 1U) << MDMA_CBNDTR_BRC_Pos) & MDMA_CBNDTR_BRC;

  /* if block source address offset is negative set the Block Repeat Source address Update Mode to decrement */
  if(pNodeConfig->Init.SourceBlockAddressOffset < 0)
  {
    pNode->CBNDTR |= MDMA_CBNDTR_BRSUM;
    /*write new CBRUR Register value : source repeat block offset */
    blockoffset = (uint32_t)(- pNodeConfig->Init.SourceBlockAddressOffset);
    pNode->CBRUR = blockoffset & 0x0000FFFFU;
  }
  else
  {
    /*write new CBRUR Register value : source repeat block offset */
    pNode->CBRUR = (((uint32_t) pNodeConfig->Init.SourceBlockAddressOffset) & 0x0000FFFFU);
  }

  /* if block destination address offset is negative set the Block Repeat destination address Update Mode to decrement */
  if(pNodeConfig->Init.DestBlockAddressOffset < 0)
  {
    pNode->CBNDTR |= MDMA_CBNDTR_BRDUM;
    /*write new CBRUR Register value : destination repeat block offset */
    blockoffset = (uint32_t)(- pNodeConfig->Init.DestBlockAddressOffset);
    pNode->CBRUR |= ((blockoffset & 0x0000FFFFU) << MDMA_CBRUR_DUV_Pos);
  }
  else
  {
    /*write new CBRUR Register value : destination repeat block offset */
    pNode->CBRUR |= ((((uint32_t)pNodeConfig->Init.DestBlockAddressOffset) & 0x0000FFFFU) << MDMA_CBRUR_DUV_Pos);
  }

  /* Configure MDMA Link Node data length */
  pNode->CBNDTR |=  pNodeConfig->BlockDataLength;

  /* Configure MDMA Link Node destination address */
  pNode->CDAR = pNodeConfig->DstAddress;

  /* Configure MDMA Link Node Source address */
  pNode->CSAR = pNodeConfig->SrcAddress;

  /* if HW request set the HW request and the requet CleraMask and ClearData MaskData,  */
  if(pNodeConfig->Init.Request != MDMA_REQUEST_SW)
  {
    /* Set the HW request in CTBR register  */
    pNode->CTBR = pNodeConfig->Init.Request & MDMA_CTBR_TSEL;
    /* Set the HW request clear Mask and Data */
    pNode->CMAR = pNodeConfig->PostRequestMaskAddress;
    pNode->CMDR = pNodeConfig->PostRequestMaskData;
  }

  addressMask = pNodeConfig->SrcAddress & 0xFF000000U;
  if((addressMask == 0x20000000U) || (addressMask == 0x00000000U))
  {
    /*The AHBSbus is used as source (read operation) on channel x */
    pNode->CTBR |= MDMA_CTBR_SBUS;
  }

  addressMask = pNodeConfig->DstAddress & 0xFF000000U;
  if((addressMask == 0x20000000U) || (addressMask == 0x00000000U))
  {
    /*The AHB bus is used as destination (write operation) on channel x */
    pNode->CTBR |= MDMA_CTBR_DBUS;
  }

  return HAL_OK;
}

/**
  * @brief  Connect a node to the linked list.
  * @param  hmdma    : Pointer to a MDMA_HandleTypeDef structure that contains
  *                    the configuration information for the specified MDMA Channel.
  * @param  pNewNode : Pointer to a MDMA_LinkNodeTypeDef structure that contains Linked list node
  *                    to be add to the list.
  * @param pPrevNode : Pointer to the new node position in the linked list or zero to insert the new node
  *                    at the end of the list
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_LinkedList_AddNode(MDMA_HandleTypeDef *hmdma, MDMA_LinkNodeTypeDef *pNewNode, MDMA_LinkNodeTypeDef *pPrevNode)
{
  MDMA_LinkNodeTypeDef *pNode;
  uint32_t counter = 0, nodeInserted = 0;
  HAL_StatusTypeDef hal_status = HAL_OK;

  /* Check the MDMA peripheral handle */
  if((hmdma == NULL) || (pNewNode == NULL))
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hmdma);

  if(HAL_MDMA_STATE_READY == hmdma->State)
  {
    /* Change MDMA peripheral state */
    hmdma->State = HAL_MDMA_STATE_BUSY;

    /* Check if this is the first node (after the Inititlization node) */
    if((uint32_t)hmdma->FirstLinkedListNodeAddress == 0U)
    {
      if(pPrevNode == NULL)
      {
        /* if this is the first node after the initialization
        connect this node to the node 0 by updating
        the MDMA channel CLAR register to this node address */
        hmdma->Instance->CLAR = (uint32_t)pNewNode;
        /* Set the MDMA handle First linked List node*/
        hmdma->FirstLinkedListNodeAddress = pNewNode;

        /*reset New node link */
        pNewNode->CLAR = 0;

        /* Update the Handle last node address */
        hmdma->LastLinkedListNodeAddress = pNewNode;

        hmdma->LinkedListNodeCounter = 1;
      }
      else
      {
        hal_status = HAL_ERROR;
      }
    }
    else if(hmdma->FirstLinkedListNodeAddress != pNewNode)
    {
      /* Check if the node to insert already exists*/
      pNode = hmdma->FirstLinkedListNodeAddress;
      while((counter < hmdma->LinkedListNodeCounter) && (hal_status == HAL_OK))
      {
        if(pNode->CLAR == (uint32_t)pNewNode)
        {
          hal_status = HAL_ERROR; /* error this node already exist in the linked list and it is not first node */
        }
        pNode = (MDMA_LinkNodeTypeDef *)pNode->CLAR;
        counter++;
      }

      if(hal_status == HAL_OK)
      {
        /* Check if the previous node is the last one in the current list or zero */
        if((pPrevNode == hmdma->LastLinkedListNodeAddress) || (pPrevNode == NULL))
        {
          /* insert the new node at the end of the list */
          pNewNode->CLAR = hmdma->LastLinkedListNodeAddress->CLAR;
          hmdma->LastLinkedListNodeAddress->CLAR = (uint32_t)pNewNode;
          /* Update the Handle last node address */
          hmdma->LastLinkedListNodeAddress = pNewNode;
          /* Increment the linked list node counter */
          hmdma->LinkedListNodeCounter++;
        }
        else
        {
          /*insert the new node after the pPreviousNode node */
          pNode = hmdma->FirstLinkedListNodeAddress;
          counter = 0;
          while((counter < hmdma->LinkedListNodeCounter) && (nodeInserted == 0U))
          {
            counter++;
            if(pNode == pPrevNode)
            {
              /*Insert the new node after the previous one */
              pNewNode->CLAR = pNode->CLAR;
              pNode->CLAR = (uint32_t)pNewNode;
              /* Increment the linked list node counter */
              hmdma->LinkedListNodeCounter++;
              nodeInserted = 1;
            }
            else
            {
              pNode = (MDMA_LinkNodeTypeDef *)pNode->CLAR;
            }
          }

          if(nodeInserted == 0U)
          {
            hal_status = HAL_ERROR;
          }
        }
      }
    }
    else
    {
      hal_status = HAL_ERROR;
    }

    /* Process unlocked */
    __HAL_UNLOCK(hmdma);

    hmdma->State = HAL_MDMA_STATE_READY;

    return hal_status;
  }
  else
  {
    /* Process unlocked */
    __HAL_UNLOCK(hmdma);

    /* Return error status */
    return HAL_BUSY;
  }
}

/**
  * @brief  Disconnect/Remove a node from the transfer linked list.
  * @param  hmdma : Pointer to a MDMA_HandleTypeDef structure that contains
  *                 the configuration information for the specified MDMA Channel.
  * @param  pNode : Pointer to a MDMA_LinkNodeTypeDef structure that contains Linked list node
  *                 to be removed from the list.
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_LinkedList_RemoveNode(MDMA_HandleTypeDef *hmdma, MDMA_LinkNodeTypeDef *pNode)
{
  MDMA_LinkNodeTypeDef *ptmpNode;
  uint32_t counter = 0, nodeDeleted = 0;
  HAL_StatusTypeDef hal_status = HAL_OK;

  /* Check the MDMA peripheral handle */
  if((hmdma == NULL) || (pNode == NULL))
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hmdma);

  if(HAL_MDMA_STATE_READY == hmdma->State)
  {
    /* Change MDMA peripheral state */
    hmdma->State = HAL_MDMA_STATE_BUSY;

    /* If first and last node are null (no nodes in the list) : return error*/
    if(((uint32_t)hmdma->FirstLinkedListNodeAddress == 0U) || ((uint32_t)hmdma->LastLinkedListNodeAddress == 0U) || (hmdma->LinkedListNodeCounter == 0U))
    {
      hal_status = HAL_ERROR;
    }
    else if(hmdma->FirstLinkedListNodeAddress == pNode) /* Deleting first node */
    {
      /* Delete 1st node */
      if(hmdma->LastLinkedListNodeAddress == pNode)
      {
        /*if the last node is at the same time the first one (1 single node after the init node 0)
        then update the last node too */

        hmdma->FirstLinkedListNodeAddress = 0;
        hmdma->LastLinkedListNodeAddress  = 0;
        hmdma->LinkedListNodeCounter = 0;

        hmdma->Instance->CLAR = 0;
      }
      else
      {
        if((uint32_t)hmdma->FirstLinkedListNodeAddress == hmdma->LastLinkedListNodeAddress->CLAR)
        {
          /* if last node is looping to first (circular list) one update the last node connection */
          hmdma->LastLinkedListNodeAddress->CLAR = pNode->CLAR;
        }

        /* if deleting the first node after the initialization
        connect the next node to the node 0 by updating
        the MDMA channel CLAR register to this node address */
        hmdma->Instance->CLAR = pNode->CLAR;
        hmdma->FirstLinkedListNodeAddress = (MDMA_LinkNodeTypeDef *)hmdma->Instance->CLAR;
        /* Update the Handle node counter */
        hmdma->LinkedListNodeCounter--;
      }
    }
    else /* Deleting any other node */
    {
      /*Deleted node is not the first one : find it  */
      ptmpNode = hmdma->FirstLinkedListNodeAddress;
      while((counter < hmdma->LinkedListNodeCounter) && (nodeDeleted == 0U))
      {
        counter++;
        if(ptmpNode->CLAR == ((uint32_t)pNode))
        {
          /* if deleting the last node */
          if(pNode == hmdma->LastLinkedListNodeAddress)
          {
            /*Update the linked list last node address in the handle*/
            hmdma->LastLinkedListNodeAddress = ptmpNode;
          }
          /* update the next node link after deleting pMDMA_LinkedListNode */
          ptmpNode->CLAR = pNode->CLAR;
          nodeDeleted = 1;
          /* Update the Handle node counter */
          hmdma->LinkedListNodeCounter--;
        }
        else
        {
          ptmpNode = (MDMA_LinkNodeTypeDef *)ptmpNode->CLAR;
        }
      }

      if(nodeDeleted == 0U)
      {
        /* last node reashed without finding the node to delete : return error */
        hal_status = HAL_ERROR;
      }
    }

    /* Process unlocked */
    __HAL_UNLOCK(hmdma);

    hmdma->State = HAL_MDMA_STATE_READY;

    return hal_status;
  }
  else
  {
    /* Process unlocked */
    __HAL_UNLOCK(hmdma);

    /* Return error status */
    return HAL_BUSY;
  }
}

/**
  * @brief  Make the linked list circular by connecting the last node to the first.
  * @param  hmdma : Pointer to a MDMA_HandleTypeDef structure that contains
  *                 the configuration information for the specified MDMA Channel.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_LinkedList_EnableCircularMode(MDMA_HandleTypeDef *hmdma)
{
  HAL_StatusTypeDef hal_status = HAL_OK;

  /* Check the MDMA peripheral handle */
  if(hmdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hmdma);

  if(HAL_MDMA_STATE_READY == hmdma->State)
  {
    /* Change MDMA peripheral state */
    hmdma->State = HAL_MDMA_STATE_BUSY;

    /* If first and last node are null (no nodes in the list) : return error*/
    if(((uint32_t)hmdma->FirstLinkedListNodeAddress == 0U) || ((uint32_t)hmdma->LastLinkedListNodeAddress == 0U) || (hmdma->LinkedListNodeCounter == 0U))
    {
      hal_status = HAL_ERROR;
    }
    else
    {
      /* to enable circular mode Last Node should be connected to first node */
      hmdma->LastLinkedListNodeAddress->CLAR = (uint32_t)hmdma->FirstLinkedListNodeAddress;
    }

  }
  /* Process unlocked */
  __HAL_UNLOCK(hmdma);

  hmdma->State = HAL_MDMA_STATE_READY;

  return hal_status;
}

/**
  * @brief  Disable the linked list circular mode by setting the last node connection to null
  * @param  hmdma : Pointer to a MDMA_HandleTypeDef structure that contains
  *                 the configuration information for the specified MDMA Channel.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_LinkedList_DisableCircularMode(MDMA_HandleTypeDef *hmdma)
{
  HAL_StatusTypeDef hal_status = HAL_OK;

  /* Check the MDMA peripheral handle */
  if(hmdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hmdma);

  if(HAL_MDMA_STATE_READY == hmdma->State)
  {
    /* Change MDMA peripheral state */
    hmdma->State = HAL_MDMA_STATE_BUSY;

    /* If first and last node are null (no nodes in the list) : return error*/
    if(((uint32_t)hmdma->FirstLinkedListNodeAddress == 0U) || ((uint32_t)hmdma->LastLinkedListNodeAddress == 0U) || (hmdma->LinkedListNodeCounter == 0U))
    {
      hal_status = HAL_ERROR;
    }
    else
    {
      /* to disable circular mode Last Node should be connected to NULL */
      hmdma->LastLinkedListNodeAddress->CLAR = 0;
    }

  }
  /* Process unlocked */
  __HAL_UNLOCK(hmdma);

  hmdma->State = HAL_MDMA_STATE_READY;

  return hal_status;
}

/**
  * @}
  */

/** @addtogroup MDMA_Exported_Functions_Group3
 *
@verbatim
 ===============================================================================
                      #####  IO operation functions  #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the source, destination address and data length and Start MDMA transfer
      (+) Configure the source, destination address and data length and
          Start MDMA transfer with interrupt
      (+) Abort MDMA transfer
      (+) Poll for transfer complete
      (+) Generate a SW request (when Request is set to MDMA_REQUEST_SW)
      (+) Handle MDMA interrupt request

@endverbatim
  * @{
  */

/**
  * @brief  Starts the MDMA Transfer.
  * @param  hmdma           : pointer to a MDMA_HandleTypeDef structure that contains
  *                           the configuration information for the specified MDMA Channel.
  * @param  SrcAddress      : The source memory Buffer address
  * @param  DstAddress      : The destination memory Buffer address
  * @param  BlockDataLength : The length of a block transfer in bytes
  * @param  BlockCount      : The number of a blocks to be transfer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_Start(MDMA_HandleTypeDef *hmdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t BlockDataLength, uint32_t BlockCount)
{
  /* Check the parameters */
  assert_param(IS_MDMA_TRANSFER_LENGTH(BlockDataLength));
  assert_param(IS_MDMA_BLOCK_COUNT(BlockCount));

  /* Check the MDMA peripheral handle */
  if(hmdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hmdma);

  if(HAL_MDMA_STATE_READY == hmdma->State)
  {
    /* Change MDMA peripheral state */
    hmdma->State = HAL_MDMA_STATE_BUSY;

    /* Initialize the error code */
    hmdma->ErrorCode = HAL_MDMA_ERROR_NONE;

    /* Disable the peripheral */
    __HAL_MDMA_DISABLE(hmdma);

    /* Configure the source, destination address and the data length */
    MDMA_SetConfig(hmdma, SrcAddress, DstAddress, BlockDataLength, BlockCount);

    /* Enable the Peripheral */
    __HAL_MDMA_ENABLE(hmdma);

    if(hmdma->Init.Request == MDMA_REQUEST_SW)
    {
      /* activate If SW request mode*/
      hmdma->Instance->CCR |=  MDMA_CCR_SWRQ;
    }
  }
  else
  {
    /* Process unlocked */
    __HAL_UNLOCK(hmdma);

    /* Return error status */
    return HAL_BUSY;
  }

  return HAL_OK;
}

/**
  * @brief  Starts the MDMA Transfer with interrupts enabled.
  * @param  hmdma           : pointer to a MDMA_HandleTypeDef structure that contains
  *                           the configuration information for the specified MDMA Channel.
  * @param  SrcAddress      : The source memory Buffer address
  * @param  DstAddress      : The destination memory Buffer address
  * @param  BlockDataLength : The length of a block transfer in bytes
  * @param  BlockCount      : The number of a blocks to be transfer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_Start_IT(MDMA_HandleTypeDef *hmdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t BlockDataLength, uint32_t BlockCount)
{
  /* Check the parameters */
  assert_param(IS_MDMA_TRANSFER_LENGTH(BlockDataLength));
  assert_param(IS_MDMA_BLOCK_COUNT(BlockCount));

  /* Check the MDMA peripheral handle */
  if(hmdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hmdma);

  if(HAL_MDMA_STATE_READY == hmdma->State)
  {
    /* Change MDMA peripheral state */
    hmdma->State = HAL_MDMA_STATE_BUSY;

    /* Initialize the error code */
    hmdma->ErrorCode = HAL_MDMA_ERROR_NONE;

    /* Disable the peripheral */
    __HAL_MDMA_DISABLE(hmdma);

    /* Configure the source, destination address and the data length */
    MDMA_SetConfig(hmdma, SrcAddress, DstAddress, BlockDataLength, BlockCount);

    /* Enable Common interrupts i.e Transfer Error IT and Channel Transfer Complete IT*/
    __HAL_MDMA_ENABLE_IT(hmdma, (MDMA_IT_TE | MDMA_IT_CTC));

    if(hmdma->XferBlockCpltCallback != NULL)
    {
      /* if Block transfer complete Callback is set enable the corresponding IT*/
      __HAL_MDMA_ENABLE_IT(hmdma, MDMA_IT_BT);
    }

    if(hmdma->XferRepeatBlockCpltCallback != NULL)
    {
      /* if Repeated Block transfer complete Callback is set enable the corresponding IT*/
      __HAL_MDMA_ENABLE_IT(hmdma, MDMA_IT_BRT);
    }

    if(hmdma->XferBufferCpltCallback != NULL)
    {
      /* if buffer transfer complete Callback is set enable the corresponding IT*/
      __HAL_MDMA_ENABLE_IT(hmdma, MDMA_IT_BFTC);
    }

    /* Enable the Peripheral */
    __HAL_MDMA_ENABLE(hmdma);

    if(hmdma->Init.Request == MDMA_REQUEST_SW)
    {
      /* activate If SW request mode*/
      hmdma->Instance->CCR |=  MDMA_CCR_SWRQ;
    }
  }
  else
  {
    /* Process unlocked */
    __HAL_UNLOCK(hmdma);

    /* Return error status */
    return HAL_BUSY;
  }

  return HAL_OK;
}

/**
  * @brief  Aborts the MDMA Transfer.
  * @param  hmdma  : pointer to a MDMA_HandleTypeDef structure that contains
  *                 the configuration information for the specified MDMA Channel.
  *
  * @note  After disabling a MDMA Channel, a check for wait until the MDMA Channel is
  *        effectively disabled is added. If a Channel is disabled
  *        while a data transfer is ongoing, the current data will be transferred
  *        and the Channel will be effectively disabled only after the transfer of
  *        this single data is finished.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_Abort(MDMA_HandleTypeDef *hmdma)
{
  uint32_t tickstart =  HAL_GetTick();

  /* Check the MDMA peripheral handle */
  if(hmdma == NULL)
  {
    return HAL_ERROR;
  }

  if(HAL_MDMA_STATE_BUSY != hmdma->State)
  {
    hmdma->ErrorCode = HAL_MDMA_ERROR_NO_XFER;

    /* Process Unlocked */
    __HAL_UNLOCK(hmdma);

    return HAL_ERROR;
  }
  else
  {
    /* Disable all the transfer interrupts */
    __HAL_MDMA_DISABLE_IT(hmdma, (MDMA_IT_TE | MDMA_IT_CTC | MDMA_IT_BT | MDMA_IT_BRT | MDMA_IT_BFTC));

    /* Disable the channel */
    __HAL_MDMA_DISABLE(hmdma);

    /* Check if the MDMA Channel is effectively disabled */
    while((hmdma->Instance->CCR & MDMA_CCR_EN) != 0U)
    {
      /* Check for the Timeout */
      if( (HAL_GetTick()  - tickstart ) > HAL_TIMEOUT_MDMA_ABORT)
      {
        /* Update error code */
        hmdma->ErrorCode |= HAL_MDMA_ERROR_TIMEOUT;

        /* Process Unlocked */
        __HAL_UNLOCK(hmdma);

        /* Change the MDMA state */
        hmdma->State = HAL_MDMA_STATE_ERROR;

        return HAL_ERROR;
      }
    }

    /* Clear all interrupt flags */
    __HAL_MDMA_CLEAR_FLAG(hmdma, (MDMA_FLAG_TE | MDMA_FLAG_CTC | MDMA_FLAG_BT | MDMA_FLAG_BRT | MDMA_FLAG_BFTC));

    /* Process Unlocked */
    __HAL_UNLOCK(hmdma);

    /* Change the MDMA state*/
    hmdma->State = HAL_MDMA_STATE_READY;
  }

  return HAL_OK;
}

/**
  * @brief  Aborts the MDMA Transfer in Interrupt mode.
  * @param  hmdma  : pointer to a MDMA_HandleTypeDef structure that contains
  *                 the configuration information for the specified MDMA Channel.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_Abort_IT(MDMA_HandleTypeDef *hmdma)
{
  /* Check the MDMA peripheral handle */
  if(hmdma == NULL)
  {
    return HAL_ERROR;
  }

  if(HAL_MDMA_STATE_BUSY != hmdma->State)
  {
    /* No transfer ongoing */
    hmdma->ErrorCode = HAL_MDMA_ERROR_NO_XFER;

    return HAL_ERROR;
  }
  else
  {
    /* Set Abort State  */
    hmdma->State = HAL_MDMA_STATE_ABORT;

    /* Disable the stream */
    __HAL_MDMA_DISABLE(hmdma);
  }

  return HAL_OK;
}

/**
  * @brief  Polling for transfer complete.
  * @param  hmdma:          pointer to a MDMA_HandleTypeDef structure that contains
  *                        the configuration information for the specified MDMA Channel.
  * @param  CompleteLevel: Specifies the MDMA level complete.
  * @param  Timeout:       Timeout duration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_PollForTransfer(MDMA_HandleTypeDef *hmdma, HAL_MDMA_LevelCompleteTypeDef CompleteLevel, uint32_t Timeout)
{
  uint32_t levelFlag, errorFlag;
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_MDMA_LEVEL_COMPLETE(CompleteLevel));

  /* Check the MDMA peripheral handle */
  if(hmdma == NULL)
  {
    return HAL_ERROR;
  }

  if(HAL_MDMA_STATE_BUSY != hmdma->State)
  {
    /* No transfer ongoing */
    hmdma->ErrorCode = HAL_MDMA_ERROR_NO_XFER;

    return HAL_ERROR;
  }

  /* Get the level transfer complete flag */
  levelFlag = ((CompleteLevel == HAL_MDMA_FULL_TRANSFER)  ? MDMA_FLAG_CTC  : \
               (CompleteLevel == HAL_MDMA_BUFFER_TRANSFER)? MDMA_FLAG_BFTC : \
               (CompleteLevel == HAL_MDMA_BLOCK_TRANSFER) ? MDMA_FLAG_BT   : \
               MDMA_FLAG_BRT);


  /* Get timeout */
  tickstart = HAL_GetTick();

  while(__HAL_MDMA_GET_FLAG(hmdma, levelFlag) == 0U)
  {
    if((__HAL_MDMA_GET_FLAG(hmdma, MDMA_FLAG_TE) != 0U))
    {
      /* Get the transfer error source flag */
      errorFlag = hmdma->Instance->CESR;

      if((errorFlag & MDMA_CESR_TED) == 0U)
      {
        /* Update error code : Read Transfer error  */
        hmdma->ErrorCode |= HAL_MDMA_ERROR_READ_XFER;
      }
      else
      {
        /* Update error code : Write Transfer error */
        hmdma->ErrorCode |= HAL_MDMA_ERROR_WRITE_XFER;
      }

      if((errorFlag & MDMA_CESR_TEMD) != 0U)
      {
        /* Update error code : Error Mask Data */
        hmdma->ErrorCode |= HAL_MDMA_ERROR_MASK_DATA;
      }

      if((errorFlag & MDMA_CESR_TELD) != 0U)
      {
        /* Update error code : Error Linked list */
        hmdma->ErrorCode |= HAL_MDMA_ERROR_LINKED_LIST;
      }

      if((errorFlag & MDMA_CESR_ASE) != 0U)
      {
        /* Update error code : Address/Size alignment error */
        hmdma->ErrorCode |= HAL_MDMA_ERROR_ALIGNMENT;
      }

      if((errorFlag & MDMA_CESR_BSE) != 0U)
      {
        /* Update error code : Block Size error */
        hmdma->ErrorCode |= HAL_MDMA_ERROR_BLOCK_SIZE;
      }

      (void) HAL_MDMA_Abort(hmdma); /* if error then abort the current transfer */

      /*
        Note that the Abort function will
          - Clear all transfer flags
          - Unlock
          - Set the State
      */

      return HAL_ERROR;

    }

    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if(((HAL_GetTick() - tickstart ) > Timeout) || (Timeout == 0U))
      {
        /* Update error code */
        hmdma->ErrorCode |= HAL_MDMA_ERROR_TIMEOUT;

        (void) HAL_MDMA_Abort(hmdma); /* if timeout then abort the current transfer */

        /*
          Note that the Abort function will
            - Clear all transfer flags
            - Unlock
            - Set the State
        */

        return HAL_ERROR;
      }
    }
  }

  /* Clear the transfer level flag */
  if(CompleteLevel == HAL_MDMA_BUFFER_TRANSFER)
  {
    __HAL_MDMA_CLEAR_FLAG(hmdma, MDMA_FLAG_BFTC);

  }
  else if(CompleteLevel == HAL_MDMA_BLOCK_TRANSFER)
  {
    __HAL_MDMA_CLEAR_FLAG(hmdma, (MDMA_FLAG_BFTC | MDMA_FLAG_BT));

  }
  else if(CompleteLevel == HAL_MDMA_REPEAT_BLOCK_TRANSFER)
  {
    __HAL_MDMA_CLEAR_FLAG(hmdma, (MDMA_FLAG_BFTC | MDMA_FLAG_BT | MDMA_FLAG_BRT));
  }
  else if(CompleteLevel == HAL_MDMA_FULL_TRANSFER)
  {
    __HAL_MDMA_CLEAR_FLAG(hmdma, (MDMA_FLAG_BRT | MDMA_FLAG_BT | MDMA_FLAG_BFTC | MDMA_FLAG_CTC));

    /* Process unlocked */
    __HAL_UNLOCK(hmdma);

    hmdma->State = HAL_MDMA_STATE_READY;
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Generate an MDMA SW request trigger to activate the request on the given Channel.
  * @param  hmdma:       pointer to a MDMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified MDMA Stream.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MDMA_GenerateSWRequest(MDMA_HandleTypeDef *hmdma)
{
  uint32_t request_mode;

  /* Check the MDMA peripheral handle */
  if(hmdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Get the softawre request mode */
  request_mode = hmdma->Instance->CTCR & MDMA_CTCR_SWRM;

  if((hmdma->Instance->CCR &  MDMA_CCR_EN) == 0U)
  {
    /* if no Transfer on going (MDMA enable bit not set) return error */
    hmdma->ErrorCode = HAL_MDMA_ERROR_NO_XFER;

    return HAL_ERROR;
  }
  else if(((hmdma->Instance->CISR &  MDMA_CISR_CRQA) != 0U) || (request_mode == 0U))
  {
    /* if an MDMA ongoing request has not yet end or if request mode is not SW request return error */
    hmdma->ErrorCode = HAL_MDMA_ERROR_BUSY;

    return HAL_ERROR;
  }
  else
  {
    /* Set the SW request bit to activate the request on the Channel */
    hmdma->Instance->CCR |= MDMA_CCR_SWRQ;

    return HAL_OK;
  }
}

/**
  * @brief  Handles MDMA interrupt request.
  * @param  hmdma: pointer to a MDMA_HandleTypeDef structure that contains
  *               the configuration information for the specified MDMA Channel.
  * @retval None
  */
void HAL_MDMA_IRQHandler(MDMA_HandleTypeDef *hmdma)
{
  __IO uint32_t count = 0;
  uint32_t timeout = SystemCoreClock / 9600U;

  uint32_t generalIntFlag, errorFlag;

  /* General Interrupt Flag management ****************************************/
  generalIntFlag =  1UL << ((((uint32_t)hmdma->Instance - (uint32_t)(MDMA_Channel0))/HAL_MDMA_CHANNEL_SIZE) & 0x1FU);
  if((MDMA->GISR0 & generalIntFlag) == 0U)
  {
    return; /* the  General interrupt flag for the current channel is down , nothing to do */
  }

  /* Transfer Error Interrupt management ***************************************/
  if((__HAL_MDMA_GET_FLAG(hmdma, MDMA_FLAG_TE) != 0U))
  {
    if(__HAL_MDMA_GET_IT_SOURCE(hmdma, MDMA_IT_TE) != 0U)
    {
      /* Disable the transfer error interrupt */
      __HAL_MDMA_DISABLE_IT(hmdma, MDMA_IT_TE);

      /* Get the transfer error source flag */
      errorFlag = hmdma->Instance->CESR;

      if((errorFlag & MDMA_CESR_TED) == 0U)
      {
        /* Update error code : Read Transfer error  */
        hmdma->ErrorCode |= HAL_MDMA_ERROR_READ_XFER;
      }
      else
      {
        /* Update error code : Write Transfer error */
        hmdma->ErrorCode |= HAL_MDMA_ERROR_WRITE_XFER;
      }

      if((errorFlag & MDMA_CESR_TEMD) != 0U)
      {
        /* Update error code : Error Mask Data */
        hmdma->ErrorCode |= HAL_MDMA_ERROR_MASK_DATA;
      }

      if((errorFlag & MDMA_CESR_TELD) != 0U)
      {
        /* Update error code : Error Linked list */
        hmdma->ErrorCode |= HAL_MDMA_ERROR_LINKED_LIST;
      }

      if((errorFlag & MDMA_CESR_ASE) != 0U)
      {
        /* Update error code : Address/Size alignment error */
        hmdma->ErrorCode |= HAL_MDMA_ERROR_ALIGNMENT;
      }

      if((errorFlag & MDMA_CESR_BSE) != 0U)
      {
        /* Update error code : Block Size error error */
        hmdma->ErrorCode |= HAL_MDMA_ERROR_BLOCK_SIZE;
      }

      /* Clear the transfer error flags */
      __HAL_MDMA_CLEAR_FLAG(hmdma, MDMA_FLAG_TE);
    }
  }

  /* Buffer Transfer Complete Interrupt management ******************************/
  if((__HAL_MDMA_GET_FLAG(hmdma, MDMA_FLAG_BFTC) != 0U))
  {
    if(__HAL_MDMA_GET_IT_SOURCE(hmdma, MDMA_IT_BFTC) != 0U)
    {
      /* Clear the buffer transfer complete flag */
      __HAL_MDMA_CLEAR_FLAG(hmdma, MDMA_FLAG_BFTC);

      if(hmdma->XferBufferCpltCallback != NULL)
      {
        /* Buffer transfer callback */
        hmdma->XferBufferCpltCallback(hmdma);
      }
    }
  }

  /* Block Transfer Complete Interrupt management ******************************/
  if((__HAL_MDMA_GET_FLAG(hmdma, MDMA_FLAG_BT) != 0U))
  {
    if(__HAL_MDMA_GET_IT_SOURCE(hmdma, MDMA_IT_BT) != 0U)
    {
      /* Clear the block transfer complete flag */
      __HAL_MDMA_CLEAR_FLAG(hmdma, MDMA_FLAG_BT);

      if(hmdma->XferBlockCpltCallback != NULL)
      {
        /* Block transfer callback */
        hmdma->XferBlockCpltCallback(hmdma);
      }
    }
  }

  /* Repeated Block Transfer Complete Interrupt management ******************************/
  if((__HAL_MDMA_GET_FLAG(hmdma, MDMA_FLAG_BRT) != 0U))
  {
    if(__HAL_MDMA_GET_IT_SOURCE(hmdma, MDMA_IT_BRT) != 0U)
    {
      /* Clear the repeat block transfer complete flag */
      __HAL_MDMA_CLEAR_FLAG(hmdma, MDMA_FLAG_BRT);

      if(hmdma->XferRepeatBlockCpltCallback != NULL)
      {
        /* Repeated Block transfer callback */
        hmdma->XferRepeatBlockCpltCallback(hmdma);
      }
    }
  }

  /* Channel Transfer Complete Interrupt management ***********************************/
  if((__HAL_MDMA_GET_FLAG(hmdma, MDMA_FLAG_CTC) != 0U))
  {
    if(__HAL_MDMA_GET_IT_SOURCE(hmdma, MDMA_IT_CTC) != 0U)
    {
      /* Disable all the transfer interrupts */
      __HAL_MDMA_DISABLE_IT(hmdma, (MDMA_IT_TE | MDMA_IT_CTC | MDMA_IT_BT | MDMA_IT_BRT | MDMA_IT_BFTC));

      if(HAL_MDMA_STATE_ABORT == hmdma->State)
      {
        /* Process Unlocked */
        __HAL_UNLOCK(hmdma);

        /* Change the DMA state */
        hmdma->State = HAL_MDMA_STATE_READY;

        if(hmdma->XferAbortCallback != NULL)
        {
          hmdma->XferAbortCallback(hmdma);
        }
        return;
      }

      /* Clear the Channel Transfer Complete flag */
      __HAL_MDMA_CLEAR_FLAG(hmdma, MDMA_FLAG_CTC);

      /* Process Unlocked */
      __HAL_UNLOCK(hmdma);

      /* Change MDMA peripheral state */
      hmdma->State = HAL_MDMA_STATE_READY;

      if(hmdma->XferCpltCallback != NULL)
      {
        /* Channel Transfer Complete callback */
        hmdma->XferCpltCallback(hmdma);
      }
    }
  }

  /* manage error case */
  if(hmdma->ErrorCode != HAL_MDMA_ERROR_NONE)
  {
    hmdma->State = HAL_MDMA_STATE_ABORT;

    /* Disable the channel */
    __HAL_MDMA_DISABLE(hmdma);

    do
    {
      if (++count > timeout)
      {
        break;
      }
    }
    while((hmdma->Instance->CCR & MDMA_CCR_EN) != 0U);

    /* Process Unlocked */
    __HAL_UNLOCK(hmdma);

    if((hmdma->Instance->CCR & MDMA_CCR_EN) != 0U)
    {
      /* Change the MDMA state to error if MDMA disable fails */
      hmdma->State = HAL_MDMA_STATE_ERROR;
    }
    else
    {
      /* Change the MDMA state to Ready if MDMA disable success */
      hmdma->State = HAL_MDMA_STATE_READY;
    }


    if (hmdma->XferErrorCallback != NULL)
    {
      /* Transfer error callback */
      hmdma->XferErrorCallback(hmdma);
    }
  }
}

/**
  * @}
  */

/** @addtogroup MDMA_Exported_Functions_Group4
 *
@verbatim
 ===============================================================================
                    ##### State and Errors functions #####
 ===============================================================================
    [..]
    This subsection provides functions allowing to
      (+) Check the MDMA state
      (+) Get error code

@endverbatim
  * @{
  */

/**
  * @brief  Returns the MDMA state.
  * @param  hmdma: pointer to a MDMA_HandleTypeDef structure that contains
  *               the configuration information for the specified MDMA Channel.
  * @retval HAL state
  */
HAL_MDMA_StateTypeDef HAL_MDMA_GetState(MDMA_HandleTypeDef *hmdma)
{
  return hmdma->State;
}

/**
  * @brief  Return the MDMA error code
  * @param  hmdma : pointer to a MDMA_HandleTypeDef structure that contains
  *              the configuration information for the specified MDMA Channel.
  * @retval MDMA Error Code
  */
uint32_t HAL_MDMA_GetError(MDMA_HandleTypeDef *hmdma)
{
  return hmdma->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup MDMA_Private_Functions
  * @{
  */

/**
  * @brief  Sets the MDMA Transfer parameter.
  * @param  hmdma:       pointer to a MDMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified MDMA Channel.
  * @param  SrcAddress: The source memory Buffer address
  * @param  DstAddress: The destination memory Buffer address
  * @param  BlockDataLength : The length of a block transfer in bytes
  * @param  BlockCount: The number of blocks to be transferred
  * @retval HAL status
  */
static void MDMA_SetConfig(MDMA_HandleTypeDef *hmdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t BlockDataLength, uint32_t BlockCount)
{
  uint32_t addressMask;

  /* Configure the MDMA Channel data length */
  MODIFY_REG(hmdma->Instance->CBNDTR ,MDMA_CBNDTR_BNDT, (BlockDataLength & MDMA_CBNDTR_BNDT));

  /* Configure the MDMA block repeat count */
  MODIFY_REG(hmdma->Instance->CBNDTR , MDMA_CBNDTR_BRC , ((BlockCount - 1U) << MDMA_CBNDTR_BRC_Pos) & MDMA_CBNDTR_BRC);

  /* Clear all interrupt flags */
  __HAL_MDMA_CLEAR_FLAG(hmdma, MDMA_FLAG_TE | MDMA_FLAG_CTC | MDMA_CISR_BRTIF | MDMA_CISR_BTIF | MDMA_CISR_TCIF);

  /* Configure MDMA Channel destination address */
  hmdma->Instance->CDAR = DstAddress;

  /* Configure MDMA Channel Source address */
  hmdma->Instance->CSAR = SrcAddress;

  addressMask = SrcAddress & 0xFF000000U;
  if((addressMask == 0x20000000U) || (addressMask == 0x00000000U))
  {
    /*The AHBSbus is used as source (read operation) on channel x */
    hmdma->Instance->CTBR |= MDMA_CTBR_SBUS;
  }
  else
  {
    /*The AXI bus is used as source (read operation) on channel x */
    hmdma->Instance->CTBR &= (~MDMA_CTBR_SBUS);
  }

  addressMask = DstAddress & 0xFF000000U;
  if((addressMask == 0x20000000U) || (addressMask == 0x00000000U))
  {
    /*The AHB bus is used as destination (write operation) on channel x */
    hmdma->Instance->CTBR |= MDMA_CTBR_DBUS;
  }
  else
  {
    /*The AXI bus is used as destination (write operation) on channel x */
    hmdma->Instance->CTBR &= (~MDMA_CTBR_DBUS);
  }

  /* Set the linked list register to the first node of the list */
  hmdma->Instance->CLAR = (uint32_t)hmdma->FirstLinkedListNodeAddress;
}

/**
  * @brief  Initializes the MDMA handle according to the specified
  *         parameters in the MDMA_InitTypeDef
  * @param  hmdma:       pointer to a MDMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified MDMA Channel.
  * @retval None
  */
static void MDMA_Init(MDMA_HandleTypeDef *hmdma)
{
  uint32_t blockoffset;

  /* Prepare the MDMA Channel configuration */
  hmdma->Instance->CCR = hmdma->Init.Priority  | hmdma->Init.Endianness;

  /* Write new CTCR Register value */
  hmdma->Instance->CTCR =  hmdma->Init.SourceInc      | hmdma->Init.DestinationInc | \
                           hmdma->Init.SourceDataSize | hmdma->Init.DestDataSize   | \
                           hmdma->Init.DataAlignment  | hmdma->Init.SourceBurst    | \
                           hmdma->Init.DestBurst                                   | \
                           ((hmdma->Init.BufferTransferLength - 1U) << MDMA_CTCR_TLEN_Pos) | \
                           hmdma->Init.TransferTriggerMode;

  /* If SW request set the CTCR register to SW Request Mode */
  if(hmdma->Init.Request == MDMA_REQUEST_SW)
  {
    /*
    -If the request is done by SW : BWM could be set to 1 or 0.
    -If the request is done by a peripheral :
    If mask address not set (0) => BWM must be set to 0
    If mask address set (different than 0) => BWM could be set to 1 or 0
    */
    hmdma->Instance->CTCR |= (MDMA_CTCR_SWRM | MDMA_CTCR_BWM);
  }

  /* Reset CBNDTR Register */
  hmdma->Instance->CBNDTR = 0;

  /* if block source address offset is negative set the Block Repeat Source address Update Mode to decrement */
  if(hmdma->Init.SourceBlockAddressOffset < 0)
  {
    hmdma->Instance->CBNDTR |= MDMA_CBNDTR_BRSUM;
    /* Write new CBRUR Register value : source repeat block offset */
    blockoffset = (uint32_t)(- hmdma->Init.SourceBlockAddressOffset);
    hmdma->Instance->CBRUR = (blockoffset & 0x0000FFFFU);
  }
  else
  {
    /* Write new CBRUR Register value : source repeat block offset */
    hmdma->Instance->CBRUR = (((uint32_t)hmdma->Init.SourceBlockAddressOffset) & 0x0000FFFFU);
  }

  /* If block destination address offset is negative set the Block Repeat destination address Update Mode to decrement */
  if(hmdma->Init.DestBlockAddressOffset < 0)
  {
    hmdma->Instance->CBNDTR |= MDMA_CBNDTR_BRDUM;
    /* Write new CBRUR Register value : destination repeat block offset */
    blockoffset = (uint32_t)(- hmdma->Init.DestBlockAddressOffset);
    hmdma->Instance->CBRUR |= ((blockoffset & 0x0000FFFFU) << MDMA_CBRUR_DUV_Pos);
  }
  else
  {
    /*write new CBRUR Register value : destination repeat block offset */
    hmdma->Instance->CBRUR |= ((((uint32_t)hmdma->Init.DestBlockAddressOffset) & 0x0000FFFFU) << MDMA_CBRUR_DUV_Pos);
  }

  /* if HW request set the HW request and the requet CleraMask and ClearData MaskData, */
  if(hmdma->Init.Request != MDMA_REQUEST_SW)
  {
    /* Set the HW request in CTRB register  */
    hmdma->Instance->CTBR = hmdma->Init.Request & MDMA_CTBR_TSEL;
  }
  else /* SW request : reset the CTBR register */
  {
    hmdma->Instance->CTBR = 0;
  }

  /* Write Link Address Register */
  hmdma->Instance->CLAR =  0;
}

/**
  * @}
  */

#endif /* HAL_MDMA_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

