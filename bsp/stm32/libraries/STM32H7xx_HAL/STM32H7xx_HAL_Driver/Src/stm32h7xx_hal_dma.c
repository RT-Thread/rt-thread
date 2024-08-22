/**
  ******************************************************************************
  * @file    stm32h7xx_hal_dma.c
  * @author  MCD Application Team
  * @brief   DMA HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Direct Memory Access (DMA) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
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
   (#) Enable and configure the peripheral to be connected to the DMA Stream
       (except for internal SRAM/FLASH memories: no initialization is
       necessary) please refer to Reference manual for connection between peripherals
       and DMA requests .

   (#) For a given Stream, program the required configuration through the following parameters:
       Transfer Direction, Source and Destination data formats,
       Circular, Normal or peripheral flow control mode, Stream Priority level,
       Source and Destination Increment mode, FIFO mode and its Threshold (if needed),
       Burst mode for Source and/or Destination (if needed) using HAL_DMA_Init() function.

     *** Polling mode IO operation ***
     =================================
    [..]
          (+) Use HAL_DMA_Start() to start DMA transfer after the configuration of Source
              address and destination address and the Length of data to be transferred
          (+) Use HAL_DMA_PollForTransfer() to poll for the end of current transfer, in this
              case a fixed Timeout can be configured by User depending from his application.

     *** Interrupt mode IO operation ***
     ===================================
    [..]
          (+) Configure the DMA interrupt priority using HAL_NVIC_SetPriority()
          (+) Enable the DMA IRQ handler using HAL_NVIC_EnableIRQ()
          (+) Use HAL_DMA_Start_IT() to start DMA transfer after the configuration of
              Source address and destination address and the Length of data to be transferred. In this
              case the DMA interrupt is configured
          (+) Use HAL_DMA_IRQHandler() called under DMA_IRQHandler() Interrupt subroutine
          (+) At the end of data transfer HAL_DMA_IRQHandler() function is executed and user can
              add his own function by customization of function pointer XferCpltCallback and
              XferErrorCallback (i.e a member of DMA handle structure).
    [..]
     (#) Use HAL_DMA_GetState() function to return the DMA state and HAL_DMA_GetError() in case of error
         detection.

     (#) Use HAL_DMA_Abort() function to abort the current transfer

     -@-   In Memory-to-Memory transfer mode, Circular mode is not allowed.

     -@-   The FIFO is used mainly to reduce bus usage and to allow data packing/unpacking: it is
           possible to set different Data Sizes for the Peripheral and the Memory (ie. you can set
           Half-Word data size for the peripheral to access its data register and set Word data size
           for the Memory to gain in access time. Each two half words will be packed and written in
           a single access to a Word in the Memory).

     -@-   When FIFO is disabled, it is not allowed to configure different Data Sizes for Source
           and Destination. In this case the Peripheral Data Size will be applied to both Source
           and Destination.

     *** DMA HAL driver macros list ***
     =============================================
     [..]
       Below the list of most used macros in DMA HAL driver.

      (+) __HAL_DMA_ENABLE: Enable the specified DMA Stream.
      (+) __HAL_DMA_DISABLE: Disable the specified DMA Stream.
      (+) __HAL_DMA_GET_FS: Return the current DMA Stream FIFO filled level.
      (+) __HAL_DMA_ENABLE_IT: Enable the specified DMA Stream interrupts.
      (+) __HAL_DMA_DISABLE_IT: Disable the specified DMA Stream interrupts.
      (+) __HAL_DMA_GET_IT_SOURCE: Check whether the specified DMA Stream interrupt has occurred or not.

     [..]
      (@) You can refer to the DMA HAL driver header file for more useful macros.

  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @defgroup DMA DMA
  * @brief DMA HAL module driver
  * @{
  */

#ifdef HAL_DMA_MODULE_ENABLED

/* Private types -------------------------------------------------------------*/
/** @addtogroup DMA_Private_Types
  * @{
  */
typedef struct
{
  __IO uint32_t ISR;   /*!< DMA interrupt status register */
  __IO uint32_t Reserved0;
  __IO uint32_t IFCR;  /*!< DMA interrupt flag clear register */
} DMA_Base_Registers;

typedef struct
{
  __IO uint32_t ISR;   /*!< BDMA interrupt status register */
  __IO uint32_t IFCR;  /*!< BDMA interrupt flag clear register */
} BDMA_Base_Registers;
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup DMA_Private_Constants
 * @{
 */
#define HAL_TIMEOUT_DMA_ABORT         (5U)  /* 5 ms */

#define BDMA_PERIPH_TO_MEMORY         (0x00000000U)                /*!< Peripheral to memory direction */
#define BDMA_MEMORY_TO_PERIPH         ((uint32_t)BDMA_CCR_DIR)     /*!< Memory to peripheral direction */
#define BDMA_MEMORY_TO_MEMORY         ((uint32_t)BDMA_CCR_MEM2MEM) /*!< Memory to memory direction     */

/* DMA to BDMA conversion */
#define DMA_TO_BDMA_DIRECTION(__DMA_DIRECTION__) (((__DMA_DIRECTION__) == DMA_MEMORY_TO_PERIPH)? BDMA_MEMORY_TO_PERIPH: \
                                                  ((__DMA_DIRECTION__) == DMA_MEMORY_TO_MEMORY)? BDMA_MEMORY_TO_MEMORY: \
                                                  BDMA_PERIPH_TO_MEMORY)

#define DMA_TO_BDMA_PERIPHERAL_INC(__DMA_PERIPHERAL_INC__) ((__DMA_PERIPHERAL_INC__) >> 3U)
#define DMA_TO_BDMA_MEMORY_INC(__DMA_MEMORY_INC__) ((__DMA_MEMORY_INC__) >> 3U)

#define DMA_TO_BDMA_PDATA_SIZE(__DMA_PDATA_SIZE__) ((__DMA_PDATA_SIZE__) >> 3U)
#define DMA_TO_BDMA_MDATA_SIZE(__DMA_MDATA_SIZE__) ((__DMA_MDATA_SIZE__) >> 3U)

#define DMA_TO_BDMA_MODE(__DMA_MODE__) ((__DMA_MODE__) >> 3U)

#define DMA_TO_BDMA_PRIORITY(__DMA_PRIORITY__) ((__DMA_PRIORITY__) >> 4U)

#if defined(UART9)
#define IS_DMA_UART_USART_REQUEST(__REQUEST__) ((((__REQUEST__) >= DMA_REQUEST_USART1_RX)  &&  ((__REQUEST__) <= DMA_REQUEST_USART3_TX)) || \
                                                 (((__REQUEST__) >= DMA_REQUEST_UART4_RX)  &&  ((__REQUEST__) <= DMA_REQUEST_UART5_TX )) || \
                                                 (((__REQUEST__) >= DMA_REQUEST_USART6_RX) &&  ((__REQUEST__) <= DMA_REQUEST_USART6_TX)) || \
                                                 (((__REQUEST__) >= DMA_REQUEST_UART7_RX)  &&  ((__REQUEST__) <= DMA_REQUEST_UART8_TX )) || \
                                                 (((__REQUEST__) >= DMA_REQUEST_UART9_RX)  &&  ((__REQUEST__) <= DMA_REQUEST_USART10_TX )))
#else
#define IS_DMA_UART_USART_REQUEST(__REQUEST__) ((((__REQUEST__) >= DMA_REQUEST_USART1_RX)  &&  ((__REQUEST__) <= DMA_REQUEST_USART3_TX)) || \
                                                 (((__REQUEST__) >= DMA_REQUEST_UART4_RX)  &&  ((__REQUEST__) <= DMA_REQUEST_UART5_TX )) || \
                                                 (((__REQUEST__) >= DMA_REQUEST_USART6_RX) &&  ((__REQUEST__) <= DMA_REQUEST_USART6_TX)) || \
                                                 (((__REQUEST__) >= DMA_REQUEST_UART7_RX)  &&  ((__REQUEST__) <= DMA_REQUEST_UART8_TX )))

#endif
/**
  * @}
  */
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @addtogroup DMA_Private_Functions
  * @{
  */
static void DMA_SetConfig(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
static uint32_t DMA_CalcBaseAndBitshift(DMA_HandleTypeDef *hdma);
static HAL_StatusTypeDef DMA_CheckFifoParam(DMA_HandleTypeDef *hdma);
static void DMA_CalcDMAMUXChannelBaseAndMask(DMA_HandleTypeDef *hdma);
static void DMA_CalcDMAMUXRequestGenBaseAndMask(DMA_HandleTypeDef *hdma);

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @addtogroup DMA_Exported_Functions
  * @{
  */

/** @addtogroup DMA_Exported_Functions_Group1
  *
@verbatim
 ===============================================================================
             ##### Initialization and de-initialization functions  #####
 ===============================================================================
    [..]
    This section provides functions allowing to initialize the DMA Stream source
    and destination incrementation and data sizes, transfer direction,
    circular/normal mode selection, memory-to-memory mode selection and Stream priority value.
    [..]
    The HAL_DMA_Init() function follows the DMA configuration procedures as described in
    reference manual.
    The HAL_DMA_DeInit function allows to deinitialize the DMA stream.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the DMA according to the specified
  *         parameters in the DMA_InitTypeDef and create the associated handle.
  * @param  hdma: Pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA Stream.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma)
{
  uint32_t registerValue;
  uint32_t tickstart = HAL_GetTick();
  DMA_Base_Registers *regs_dma;
  BDMA_Base_Registers *regs_bdma;

  /* Check the DMA peripheral handle */
  if(hdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_DMA_ALL_INSTANCE(hdma->Instance));
  assert_param(IS_DMA_DIRECTION(hdma->Init.Direction));
  assert_param(IS_DMA_PERIPHERAL_INC_STATE(hdma->Init.PeriphInc));
  assert_param(IS_DMA_MEMORY_INC_STATE(hdma->Init.MemInc));
  assert_param(IS_DMA_PERIPHERAL_DATA_SIZE(hdma->Init.PeriphDataAlignment));
  assert_param(IS_DMA_MEMORY_DATA_SIZE(hdma->Init.MemDataAlignment));
  assert_param(IS_DMA_MODE(hdma->Init.Mode));
  assert_param(IS_DMA_PRIORITY(hdma->Init.Priority));

  if(IS_DMA_STREAM_INSTANCE(hdma->Instance) != 0U) /* DMA1 or DMA2 instance */
  {
    assert_param(IS_DMA_REQUEST(hdma->Init.Request));
    assert_param(IS_DMA_FIFO_MODE_STATE(hdma->Init.FIFOMode));
    /* Check the memory burst, peripheral burst and FIFO threshold parameters only
       when FIFO mode is enabled */
    if(hdma->Init.FIFOMode != DMA_FIFOMODE_DISABLE)
    {
      assert_param(IS_DMA_FIFO_THRESHOLD(hdma->Init.FIFOThreshold));
      assert_param(IS_DMA_MEMORY_BURST(hdma->Init.MemBurst));
      assert_param(IS_DMA_PERIPHERAL_BURST(hdma->Init.PeriphBurst));
    }

    /* Change DMA peripheral state */
    hdma->State = HAL_DMA_STATE_BUSY;

    /* Allocate lock resource */
    __HAL_UNLOCK(hdma);

    /* Disable the peripheral */
    __HAL_DMA_DISABLE(hdma);

    /* Check if the DMA Stream is effectively disabled */
    while((((DMA_Stream_TypeDef   *)hdma->Instance)->CR & DMA_SxCR_EN) != 0U)
    {
      /* Check for the Timeout */
      if((HAL_GetTick() - tickstart ) > HAL_TIMEOUT_DMA_ABORT)
      {
        /* Update error code */
        hdma->ErrorCode = HAL_DMA_ERROR_TIMEOUT;

        /* Change the DMA state */
        hdma->State = HAL_DMA_STATE_ERROR;

        return HAL_ERROR;
      }
    }

    /* Get the CR register value */
    registerValue = ((DMA_Stream_TypeDef   *)hdma->Instance)->CR;

    /* Clear CHSEL, MBURST, PBURST, PL, MSIZE, PSIZE, MINC, PINC, CIRC, DIR, CT and DBM bits */
    registerValue &= ((uint32_t)~(DMA_SxCR_MBURST | DMA_SxCR_PBURST | \
                        DMA_SxCR_PL    | DMA_SxCR_MSIZE  | DMA_SxCR_PSIZE  | \
                        DMA_SxCR_MINC  | DMA_SxCR_PINC   | DMA_SxCR_CIRC   | \
                        DMA_SxCR_DIR   | DMA_SxCR_CT     | DMA_SxCR_DBM));

    /* Prepare the DMA Stream configuration */
    registerValue |=  hdma->Init.Direction           |
            hdma->Init.PeriphInc           | hdma->Init.MemInc           |
            hdma->Init.PeriphDataAlignment | hdma->Init.MemDataAlignment |
            hdma->Init.Mode                | hdma->Init.Priority;

    /* the Memory burst and peripheral burst are not used when the FIFO is disabled */
    if(hdma->Init.FIFOMode == DMA_FIFOMODE_ENABLE)
    {
      /* Get memory burst and peripheral burst */
      registerValue |=  hdma->Init.MemBurst | hdma->Init.PeriphBurst;
    }

    /* Work around for Errata 2.22: UART/USART- DMA transfer lock: DMA stream could be
                                    lock when transferring data to/from USART/UART */
#if (STM32H7_DEV_ID == 0x450UL)
    if((DBGMCU->IDCODE & 0xFFFF0000U) >= 0x20000000U)
    {
#endif /* STM32H7_DEV_ID == 0x450UL */
      if(IS_DMA_UART_USART_REQUEST(hdma->Init.Request) != 0U)
      {
        registerValue |= DMA_SxCR_TRBUFF;
      }
#if (STM32H7_DEV_ID == 0x450UL)
    }
#endif /* STM32H7_DEV_ID == 0x450UL */

    /* Write to DMA Stream CR register */
    ((DMA_Stream_TypeDef   *)hdma->Instance)->CR = registerValue;

    /* Get the FCR register value */
    registerValue = ((DMA_Stream_TypeDef   *)hdma->Instance)->FCR;

    /* Clear Direct mode and FIFO threshold bits */
    registerValue &= (uint32_t)~(DMA_SxFCR_DMDIS | DMA_SxFCR_FTH);

    /* Prepare the DMA Stream FIFO configuration */
    registerValue |= hdma->Init.FIFOMode;

    /* the FIFO threshold is not used when the FIFO mode is disabled */
    if(hdma->Init.FIFOMode == DMA_FIFOMODE_ENABLE)
    {
      /* Get the FIFO threshold */
      registerValue |= hdma->Init.FIFOThreshold;

      /* Check compatibility between FIFO threshold level and size of the memory burst */
      /* for INCR4, INCR8, INCR16 */
      if(hdma->Init.MemBurst != DMA_MBURST_SINGLE)
      {
        if (DMA_CheckFifoParam(hdma) != HAL_OK)
        {
          /* Update error code */
          hdma->ErrorCode = HAL_DMA_ERROR_PARAM;

          /* Change the DMA state */
          hdma->State = HAL_DMA_STATE_READY;

          return HAL_ERROR;
        }
      }
    }

    /* Write to DMA Stream FCR */
    ((DMA_Stream_TypeDef   *)hdma->Instance)->FCR = registerValue;

    /* Initialize StreamBaseAddress and StreamIndex parameters to be used to calculate
       DMA steam Base Address needed by HAL_DMA_IRQHandler() and HAL_DMA_PollForTransfer() */
    regs_dma = (DMA_Base_Registers *)DMA_CalcBaseAndBitshift(hdma);

    /* Clear all interrupt flags */
    regs_dma->IFCR = 0x3FUL << (hdma->StreamIndex & 0x1FU);
  }
  else if(IS_BDMA_CHANNEL_INSTANCE(hdma->Instance) != 0U) /* BDMA instance(s) */
  {
    if(IS_BDMA_CHANNEL_DMAMUX_INSTANCE(hdma->Instance) != 0U)
    {
      /* Check the request parameter */
      assert_param(IS_BDMA_REQUEST(hdma->Init.Request));
    }

    /* Change DMA peripheral state */
    hdma->State = HAL_DMA_STATE_BUSY;

    /* Allocate lock resource */
    __HAL_UNLOCK(hdma);

    /* Get the CR register value */
    registerValue = ((BDMA_Channel_TypeDef *)hdma->Instance)->CCR;

    /* Clear PL, MSIZE, PSIZE, MINC, PINC, CIRC, DIR, MEM2MEM, DBM and CT bits */
    registerValue &= ((uint32_t)~(BDMA_CCR_PL    | BDMA_CCR_MSIZE   | BDMA_CCR_PSIZE  | \
                                  BDMA_CCR_MINC  | BDMA_CCR_PINC    | BDMA_CCR_CIRC   | \
                                  BDMA_CCR_DIR   | BDMA_CCR_MEM2MEM | BDMA_CCR_DBM    | \
                                  BDMA_CCR_CT));

    /* Prepare the DMA Channel configuration */
    registerValue |=  DMA_TO_BDMA_DIRECTION(hdma->Init.Direction)            |
                      DMA_TO_BDMA_PERIPHERAL_INC(hdma->Init.PeriphInc)       |
                      DMA_TO_BDMA_MEMORY_INC(hdma->Init.MemInc)              |
                      DMA_TO_BDMA_PDATA_SIZE(hdma->Init.PeriphDataAlignment) |
                      DMA_TO_BDMA_MDATA_SIZE(hdma->Init.MemDataAlignment)    |
                      DMA_TO_BDMA_MODE(hdma->Init.Mode)                      |
                      DMA_TO_BDMA_PRIORITY(hdma->Init.Priority);

    /* Write to DMA Channel CR register */
    ((BDMA_Channel_TypeDef *)hdma->Instance)->CCR = registerValue;

    /* calculation of the channel index */
    hdma->StreamIndex = (((uint32_t)((uint32_t*)hdma->Instance) - (uint32_t)BDMA_Channel0) / ((uint32_t)BDMA_Channel1 - (uint32_t)BDMA_Channel0)) << 2U;

    /* Initialize StreamBaseAddress and StreamIndex parameters to be used to calculate
    DMA steam Base Address needed by HAL_DMA_IRQHandler() and HAL_DMA_PollForTransfer() */
    regs_bdma = (BDMA_Base_Registers *)DMA_CalcBaseAndBitshift(hdma);

    /* Clear all interrupt flags */
    regs_bdma->IFCR = ((BDMA_IFCR_CGIF0) << (hdma->StreamIndex & 0x1FU));
  }
  else
  {
    hdma->ErrorCode = HAL_DMA_ERROR_PARAM;
    hdma->State     = HAL_DMA_STATE_ERROR;

    return HAL_ERROR;
  }

  if(IS_DMA_DMAMUX_ALL_INSTANCE(hdma->Instance) != 0U) /* No DMAMUX available for BDMA1 */
  {
    /* Initialize parameters for DMAMUX channel :
    DMAmuxChannel, DMAmuxChannelStatus and DMAmuxChannelStatusMask
    */
    DMA_CalcDMAMUXChannelBaseAndMask(hdma);

    if(hdma->Init.Direction == DMA_MEMORY_TO_MEMORY)
    {
      /* if memory to memory force the request to 0*/
      hdma->Init.Request = DMA_REQUEST_MEM2MEM;
    }

    /* Set peripheral request  to DMAMUX channel */
    hdma->DMAmuxChannel->CCR = (hdma->Init.Request & DMAMUX_CxCR_DMAREQ_ID);

    /* Clear the DMAMUX synchro overrun flag */
    hdma->DMAmuxChannelStatus->CFR = hdma->DMAmuxChannelStatusMask;

    /* Initialize parameters for DMAMUX request generator :
    if the DMA request is DMA_REQUEST_GENERATOR0 to DMA_REQUEST_GENERATOR7
    */
    if((hdma->Init.Request >= DMA_REQUEST_GENERATOR0) && (hdma->Init.Request <= DMA_REQUEST_GENERATOR7))
    {
      /* Initialize parameters for DMAMUX request generator :
      DMAmuxRequestGen, DMAmuxRequestGenStatus and DMAmuxRequestGenStatusMask */
      DMA_CalcDMAMUXRequestGenBaseAndMask(hdma);

      /* Reset the DMAMUX request generator register */
      hdma->DMAmuxRequestGen->RGCR = 0U;

      /* Clear the DMAMUX request generator overrun flag */
      hdma->DMAmuxRequestGenStatus->RGCFR = hdma->DMAmuxRequestGenStatusMask;
    }
    else
    {
      hdma->DMAmuxRequestGen = 0U;
      hdma->DMAmuxRequestGenStatus = 0U;
      hdma->DMAmuxRequestGenStatusMask = 0U;
    }
  }

  /* Initialize the error code */
  hdma->ErrorCode = HAL_DMA_ERROR_NONE;

  /* Initialize the DMA state */
  hdma->State = HAL_DMA_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  DeInitializes the DMA peripheral
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA Stream.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA_DeInit(DMA_HandleTypeDef *hdma)
{
  DMA_Base_Registers *regs_dma;
  BDMA_Base_Registers *regs_bdma;

  /* Check the DMA peripheral handle */
  if(hdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Disable the selected DMA Streamx */
  __HAL_DMA_DISABLE(hdma);

  if(IS_DMA_STREAM_INSTANCE(hdma->Instance) != 0U) /* DMA1 or DMA2 instance */
  {
    /* Reset DMA Streamx control register */
    ((DMA_Stream_TypeDef   *)hdma->Instance)->CR   = 0U;

    /* Reset DMA Streamx number of data to transfer register */
    ((DMA_Stream_TypeDef   *)hdma->Instance)->NDTR = 0U;

    /* Reset DMA Streamx peripheral address register */
    ((DMA_Stream_TypeDef   *)hdma->Instance)->PAR  = 0U;

    /* Reset DMA Streamx memory 0 address register */
    ((DMA_Stream_TypeDef   *)hdma->Instance)->M0AR = 0U;

    /* Reset DMA Streamx memory 1 address register */
    ((DMA_Stream_TypeDef   *)hdma->Instance)->M1AR = 0U;

    /* Reset DMA Streamx FIFO control register */
    ((DMA_Stream_TypeDef   *)hdma->Instance)->FCR  = (uint32_t)0x00000021U;

    /* Get DMA steam Base Address */
    regs_dma = (DMA_Base_Registers *)DMA_CalcBaseAndBitshift(hdma);

    /* Clear all interrupt flags at correct offset within the register */
    regs_dma->IFCR = 0x3FUL << (hdma->StreamIndex & 0x1FU);
  }
  else if(IS_BDMA_CHANNEL_INSTANCE(hdma->Instance) != 0U) /* BDMA instance(s) */
  {
    /* Reset DMA Channel control register */
    ((BDMA_Channel_TypeDef *)hdma->Instance)->CCR  = 0U;

    /* Reset DMA Channel Number of Data to Transfer register */
    ((BDMA_Channel_TypeDef *)hdma->Instance)->CNDTR = 0U;

    /* Reset DMA Channel peripheral address register */
    ((BDMA_Channel_TypeDef *)hdma->Instance)->CPAR  = 0U;

    /* Reset DMA Channel memory 0 address register */
    ((BDMA_Channel_TypeDef *)hdma->Instance)->CM0AR = 0U;

    /* Reset DMA Channel memory 1 address register */
    ((BDMA_Channel_TypeDef *)hdma->Instance)->CM1AR = 0U;

    /* Get DMA steam Base Address */
    regs_bdma = (BDMA_Base_Registers *)DMA_CalcBaseAndBitshift(hdma);

    /* Clear all interrupt flags at correct offset within the register */
    regs_bdma->IFCR = ((BDMA_IFCR_CGIF0) << (hdma->StreamIndex & 0x1FU));
  }
  else
  {
    /* Return error status */
    return HAL_ERROR;
  }

#if defined (BDMA1) /* No DMAMUX available for BDMA1 available on  STM32H7Ax/Bx devices only */
  if(IS_DMA_DMAMUX_ALL_INSTANCE(hdma->Instance) != 0U) /* No DMAMUX available for BDMA1 */
#endif /* BDMA1 */
  {
    /* Initialize parameters for DMAMUX channel :
    DMAmuxChannel, DMAmuxChannelStatus and DMAmuxChannelStatusMask */
    DMA_CalcDMAMUXChannelBaseAndMask(hdma);

    if(hdma->DMAmuxChannel != 0U)
    {
      /* Resett he DMAMUX channel that corresponds to the DMA stream */
      hdma->DMAmuxChannel->CCR = 0U;

      /* Clear the DMAMUX synchro overrun flag */
      hdma->DMAmuxChannelStatus->CFR = hdma->DMAmuxChannelStatusMask;
    }

    if((hdma->Init.Request >= DMA_REQUEST_GENERATOR0) && (hdma->Init.Request <= DMA_REQUEST_GENERATOR7))
    {
      /* Initialize parameters for DMAMUX request generator :
      DMAmuxRequestGen, DMAmuxRequestGenStatus and DMAmuxRequestGenStatusMask */
      DMA_CalcDMAMUXRequestGenBaseAndMask(hdma);

      /* Reset the DMAMUX request generator register */
      hdma->DMAmuxRequestGen->RGCR = 0U;

      /* Clear the DMAMUX request generator overrun flag */
      hdma->DMAmuxRequestGenStatus->RGCFR = hdma->DMAmuxRequestGenStatusMask;
    }

    hdma->DMAmuxRequestGen = 0U;
    hdma->DMAmuxRequestGenStatus = 0U;
    hdma->DMAmuxRequestGenStatusMask = 0U;
  }


  /* Clean callbacks */
  hdma->XferCpltCallback       = NULL;
  hdma->XferHalfCpltCallback   = NULL;
  hdma->XferM1CpltCallback     = NULL;
  hdma->XferM1HalfCpltCallback = NULL;
  hdma->XferErrorCallback      = NULL;
  hdma->XferAbortCallback      = NULL;

  /* Initialize the error code */
  hdma->ErrorCode = HAL_DMA_ERROR_NONE;

  /* Initialize the DMA state */
  hdma->State = HAL_DMA_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hdma);

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup DMA_Exported_Functions_Group2
  *
@verbatim
 ===============================================================================
                      #####  IO operation functions  #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the source, destination address and data length and Start DMA transfer
      (+) Configure the source, destination address and data length and
          Start DMA transfer with interrupt
      (+) Register and Unregister DMA callbacks
      (+) Abort DMA transfer
      (+) Poll for transfer complete
      (+) Handle DMA interrupt request

@endverbatim
  * @{
  */

/**
  * @brief  Starts the DMA Transfer.
  * @param  hdma      : pointer to a DMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified DMA Stream.
  * @param  SrcAddress: The source memory Buffer address
  * @param  DstAddress: The destination memory Buffer address
  * @param  DataLength: The length of data to be transferred from source to destination
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA_Start(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_DMA_BUFFER_SIZE(DataLength));

  /* Check the DMA peripheral handle */
  if(hdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hdma);

  if(HAL_DMA_STATE_READY == hdma->State)
  {
    /* Change DMA peripheral state */
    hdma->State = HAL_DMA_STATE_BUSY;

    /* Initialize the error code */
    hdma->ErrorCode = HAL_DMA_ERROR_NONE;

    /* Disable the peripheral */
    __HAL_DMA_DISABLE(hdma);

    /* Configure the source, destination address and the data length */
    DMA_SetConfig(hdma, SrcAddress, DstAddress, DataLength);

    /* Enable the Peripheral */
    __HAL_DMA_ENABLE(hdma);
  }
  else
  {
    /* Set the error code to busy */
    hdma->ErrorCode = HAL_DMA_ERROR_BUSY;

    /* Process unlocked */
    __HAL_UNLOCK(hdma);

    /* Return error status */
    status = HAL_ERROR;
  }
  return status;
}

/**
  * @brief  Start the DMA Transfer with interrupt enabled.
  * @param  hdma:       pointer to a DMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified DMA Stream.
  * @param  SrcAddress: The source memory Buffer address
  * @param  DstAddress: The destination memory Buffer address
  * @param  DataLength: The length of data to be transferred from source to destination
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_DMA_BUFFER_SIZE(DataLength));

  /* Check the DMA peripheral handle */
  if(hdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hdma);

  if(HAL_DMA_STATE_READY == hdma->State)
  {
    /* Change DMA peripheral state */
    hdma->State = HAL_DMA_STATE_BUSY;

    /* Initialize the error code */
    hdma->ErrorCode = HAL_DMA_ERROR_NONE;

    /* Disable the peripheral */
    __HAL_DMA_DISABLE(hdma);

    /* Configure the source, destination address and the data length */
    DMA_SetConfig(hdma, SrcAddress, DstAddress, DataLength);

    if(IS_DMA_STREAM_INSTANCE(hdma->Instance) != 0U) /* DMA1 or DMA2 instance */
    {
      /* Enable Common interrupts*/
      MODIFY_REG(((DMA_Stream_TypeDef   *)hdma->Instance)->CR, (DMA_IT_TC | DMA_IT_TE | DMA_IT_DME | DMA_IT_HT), (DMA_IT_TC | DMA_IT_TE | DMA_IT_DME));

      if(hdma->XferHalfCpltCallback != NULL)
      {
        /* Enable Half Transfer IT if corresponding Callback is set */
        ((DMA_Stream_TypeDef   *)hdma->Instance)->CR  |= DMA_IT_HT;
      }
    }
    else /* BDMA channel */
    {
      /* Enable Common interrupts */
      MODIFY_REG(((BDMA_Channel_TypeDef   *)hdma->Instance)->CCR, (BDMA_CCR_TCIE | BDMA_CCR_HTIE | BDMA_CCR_TEIE), (BDMA_CCR_TCIE | BDMA_CCR_TEIE));

      if(hdma->XferHalfCpltCallback != NULL)
      {
        /*Enable Half Transfer IT if corresponding Callback is set */
        ((BDMA_Channel_TypeDef   *)hdma->Instance)->CCR  |= BDMA_CCR_HTIE;
      }
    }

    if(IS_DMA_DMAMUX_ALL_INSTANCE(hdma->Instance) != 0U) /* No DMAMUX available for BDMA1 */
    {
      /* Check if DMAMUX Synchronization is enabled */
      if((hdma->DMAmuxChannel->CCR & DMAMUX_CxCR_SE) != 0U)
      {
        /* Enable DMAMUX sync overrun IT*/
        hdma->DMAmuxChannel->CCR |= DMAMUX_CxCR_SOIE;
      }

      if(hdma->DMAmuxRequestGen != 0U)
      {
        /* if using DMAMUX request generator, enable the DMAMUX request generator overrun IT*/
        /* enable the request gen overrun IT */
        hdma->DMAmuxRequestGen->RGCR |= DMAMUX_RGxCR_OIE;
      }
    }

    /* Enable the Peripheral */
    __HAL_DMA_ENABLE(hdma);
  }
  else
  {
    /* Set the error code to busy */
    hdma->ErrorCode = HAL_DMA_ERROR_BUSY;

    /* Process unlocked */
    __HAL_UNLOCK(hdma);

    /* Return error status */
    status = HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Aborts the DMA Transfer.
  * @param  hdma  : pointer to a DMA_HandleTypeDef structure that contains
  *                 the configuration information for the specified DMA Stream.
  *
  * @note  After disabling a DMA Stream, a check for wait until the DMA Stream is
  *        effectively disabled is added. If a Stream is disabled
  *        while a data transfer is ongoing, the current data will be transferred
  *        and the Stream will be effectively disabled only after the transfer of
  *        this single data is finished.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma)
{
  /* calculate DMA base and stream number */
  DMA_Base_Registers *regs_dma;
  BDMA_Base_Registers *regs_bdma;
  const __IO uint32_t *enableRegister;

  uint32_t tickstart = HAL_GetTick();

 /* Check the DMA peripheral handle */
  if(hdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the DMA peripheral state */
  if(hdma->State != HAL_DMA_STATE_BUSY)
  {
    hdma->ErrorCode = HAL_DMA_ERROR_NO_XFER;

    /* Process Unlocked */
    __HAL_UNLOCK(hdma);

    return HAL_ERROR;
  }
  else
  {
    /* Disable all the transfer interrupts */
    if(IS_DMA_STREAM_INSTANCE(hdma->Instance) != 0U) /* DMA1 or DMA2 instance */
    {
       /* Disable DMA All Interrupts  */
      ((DMA_Stream_TypeDef   *)hdma->Instance)->CR  &= ~(DMA_IT_TC | DMA_IT_TE | DMA_IT_DME | DMA_IT_HT);
      ((DMA_Stream_TypeDef   *)hdma->Instance)->FCR &= ~(DMA_IT_FE);

      enableRegister = (__IO uint32_t *)(&(((DMA_Stream_TypeDef   *)hdma->Instance)->CR));
    }
    else /* BDMA channel */
    {
      /* Disable DMA All Interrupts */
      ((BDMA_Channel_TypeDef   *)hdma->Instance)->CCR  &= ~(BDMA_CCR_TCIE | BDMA_CCR_HTIE | BDMA_CCR_TEIE);

      enableRegister = (__IO uint32_t *)(&(((BDMA_Channel_TypeDef   *)hdma->Instance)->CCR));
    }

    if(IS_DMA_DMAMUX_ALL_INSTANCE(hdma->Instance) != 0U) /* No DMAMUX available for BDMA1 */
    {
      /* disable the DMAMUX sync overrun IT */
      hdma->DMAmuxChannel->CCR &= ~DMAMUX_CxCR_SOIE;
    }

    /* Disable the stream */
    __HAL_DMA_DISABLE(hdma);

    /* Check if the DMA Stream is effectively disabled */
    while(((*enableRegister) & DMA_SxCR_EN) != 0U)
    {
      /* Check for the Timeout */
      if((HAL_GetTick() - tickstart ) > HAL_TIMEOUT_DMA_ABORT)
      {
        /* Update error code */
        hdma->ErrorCode = HAL_DMA_ERROR_TIMEOUT;

        /* Change the DMA state */
        hdma->State = HAL_DMA_STATE_ERROR;

        /* Process Unlocked */
        __HAL_UNLOCK(hdma);

        return HAL_ERROR;
      }
    }

    /* Clear all interrupt flags at correct offset within the register */
    if(IS_DMA_STREAM_INSTANCE(hdma->Instance) != 0U) /* DMA1 or DMA2 instance */
    {
      regs_dma = (DMA_Base_Registers *)hdma->StreamBaseAddress;
      regs_dma->IFCR = 0x3FUL << (hdma->StreamIndex & 0x1FU);
    }
    else /* BDMA channel */
    {
      regs_bdma = (BDMA_Base_Registers *)hdma->StreamBaseAddress;
      regs_bdma->IFCR = ((BDMA_IFCR_CGIF0) << (hdma->StreamIndex & 0x1FU));
    }

    if(IS_DMA_DMAMUX_ALL_INSTANCE(hdma->Instance) != 0U) /* No DMAMUX available for BDMA1 */
    {
      /* Clear the DMAMUX synchro overrun flag */
      hdma->DMAmuxChannelStatus->CFR = hdma->DMAmuxChannelStatusMask;

      if(hdma->DMAmuxRequestGen != 0U)
      {
        /* if using DMAMUX request generator, disable the DMAMUX request generator overrun IT */
        /* disable the request gen overrun IT */
        hdma->DMAmuxRequestGen->RGCR &= ~DMAMUX_RGxCR_OIE;

        /* Clear the DMAMUX request generator overrun flag */
        hdma->DMAmuxRequestGenStatus->RGCFR = hdma->DMAmuxRequestGenStatusMask;
      }
    }

    /* Change the DMA state */
    hdma->State = HAL_DMA_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hdma);
  }

  return HAL_OK;
}

/**
  * @brief  Aborts the DMA Transfer in Interrupt mode.
  * @param  hdma  : pointer to a DMA_HandleTypeDef structure that contains
  *                 the configuration information for the specified DMA Stream.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA_Abort_IT(DMA_HandleTypeDef *hdma)
{
  BDMA_Base_Registers *regs_bdma;

  /* Check the DMA peripheral handle */
  if(hdma == NULL)
  {
    return HAL_ERROR;
  }

  if(hdma->State != HAL_DMA_STATE_BUSY)
  {
    hdma->ErrorCode = HAL_DMA_ERROR_NO_XFER;
    return HAL_ERROR;
  }
  else
  {
    if(IS_DMA_STREAM_INSTANCE(hdma->Instance) != 0U) /* DMA1 or DMA2 instance */
    {
      /* Set Abort State  */
      hdma->State = HAL_DMA_STATE_ABORT;

      /* Disable the stream */
      __HAL_DMA_DISABLE(hdma);
    }
    else /* BDMA channel */
    {
      /* Disable DMA All Interrupts  */
      ((BDMA_Channel_TypeDef   *)hdma->Instance)->CCR  &= ~(BDMA_CCR_TCIE | BDMA_CCR_HTIE | BDMA_CCR_TEIE);

      /* Disable the channel */
      __HAL_DMA_DISABLE(hdma);

      if(IS_DMA_DMAMUX_ALL_INSTANCE(hdma->Instance) != 0U) /* No DMAMUX available for BDMA1 */
      {
        /* disable the DMAMUX sync overrun IT */
        hdma->DMAmuxChannel->CCR &= ~DMAMUX_CxCR_SOIE;

        /* Clear all flags */
        regs_bdma = (BDMA_Base_Registers *)hdma->StreamBaseAddress;
        regs_bdma->IFCR = ((BDMA_IFCR_CGIF0) << (hdma->StreamIndex & 0x1FU));

        /* Clear the DMAMUX synchro overrun flag */
        hdma->DMAmuxChannelStatus->CFR = hdma->DMAmuxChannelStatusMask;

        if(hdma->DMAmuxRequestGen != 0U)
        {
          /* if using DMAMUX request generator, disable the DMAMUX request generator overrun IT*/
          /* disable the request gen overrun IT */
          hdma->DMAmuxRequestGen->RGCR &= ~DMAMUX_RGxCR_OIE;

          /* Clear the DMAMUX request generator overrun flag */
          hdma->DMAmuxRequestGenStatus->RGCFR = hdma->DMAmuxRequestGenStatusMask;
        }
      }

      /* Change the DMA state */
      hdma->State = HAL_DMA_STATE_READY;

      /* Process Unlocked */
      __HAL_UNLOCK(hdma);

      /* Call User Abort callback */
      if(hdma->XferAbortCallback != NULL)
      {
        hdma->XferAbortCallback(hdma);
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Polling for transfer complete.
  * @param  hdma:          pointer to a DMA_HandleTypeDef structure that contains
  *                        the configuration information for the specified DMA Stream.
  * @param  CompleteLevel: Specifies the DMA level complete.
  * @note   The polling mode is kept in this version for legacy. it is recommended to use the IT model instead.
  *         This model could be used for debug purpose.
  * @note   The HAL_DMA_PollForTransfer API cannot be used in circular and double buffering mode (automatic circular mode).
  * @param  Timeout:       Timeout duration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *hdma, HAL_DMA_LevelCompleteTypeDef CompleteLevel, uint32_t Timeout)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t cpltlevel_mask;
  uint32_t tickstart = HAL_GetTick();

  /* IT status register */
  __IO uint32_t *isr_reg;
  /* IT clear flag register */
  __IO uint32_t *ifcr_reg;

  /* Check the DMA peripheral handle */
  if(hdma == NULL)
  {
    return HAL_ERROR;
  }

  if(HAL_DMA_STATE_BUSY != hdma->State)
  {
    /* No transfer ongoing */
    hdma->ErrorCode = HAL_DMA_ERROR_NO_XFER;
    __HAL_UNLOCK(hdma);

    return HAL_ERROR;
  }

  if(IS_DMA_STREAM_INSTANCE(hdma->Instance) != 0U) /* DMA1 or DMA2 instance */
  {
    /* Polling mode not supported in circular mode and double buffering mode */
    if ((((DMA_Stream_TypeDef   *)hdma->Instance)->CR & DMA_SxCR_CIRC) != 0U)
    {
      hdma->ErrorCode = HAL_DMA_ERROR_NOT_SUPPORTED;
      return HAL_ERROR;
    }

    /* Get the level transfer complete flag */
    if(CompleteLevel == HAL_DMA_FULL_TRANSFER)
    {
      /* Transfer Complete flag */
      cpltlevel_mask = DMA_FLAG_TCIF0_4 << (hdma->StreamIndex & 0x1FU);
    }
    else
    {
      /* Half Transfer Complete flag */
      cpltlevel_mask = DMA_FLAG_HTIF0_4 << (hdma->StreamIndex & 0x1FU);
    }

    isr_reg  = &(((DMA_Base_Registers *)hdma->StreamBaseAddress)->ISR);
    ifcr_reg = &(((DMA_Base_Registers *)hdma->StreamBaseAddress)->IFCR);
  }
  else /* BDMA channel */
  {
    /* Polling mode not supported in circular mode */
    if ((((BDMA_Channel_TypeDef   *)hdma->Instance)->CCR & BDMA_CCR_CIRC) != 0U)
    {
      hdma->ErrorCode = HAL_DMA_ERROR_NOT_SUPPORTED;
      return HAL_ERROR;
    }

    /* Get the level transfer complete flag */
    if(CompleteLevel == HAL_DMA_FULL_TRANSFER)
    {
      /* Transfer Complete flag */
      cpltlevel_mask = BDMA_FLAG_TC0 << (hdma->StreamIndex & 0x1FU);
    }
    else
    {
      /* Half Transfer Complete flag */
      cpltlevel_mask = BDMA_FLAG_HT0 << (hdma->StreamIndex & 0x1FU);
    }

    isr_reg  = &(((BDMA_Base_Registers *)hdma->StreamBaseAddress)->ISR);
    ifcr_reg = &(((BDMA_Base_Registers *)hdma->StreamBaseAddress)->IFCR);
  }

  while(((*isr_reg) & cpltlevel_mask) == 0U)
  {
    if(IS_DMA_STREAM_INSTANCE(hdma->Instance) != 0U) /* DMA1 or DMA2 instance */
    {
      if(((*isr_reg) & (DMA_FLAG_FEIF0_4 << (hdma->StreamIndex & 0x1FU))) != 0U)
      {
        /* Update error code */
        hdma->ErrorCode |= HAL_DMA_ERROR_FE;

        /* Clear the FIFO error flag */
        (*ifcr_reg) = DMA_FLAG_FEIF0_4 << (hdma->StreamIndex & 0x1FU);
      }

      if(((*isr_reg) & (DMA_FLAG_DMEIF0_4 << (hdma->StreamIndex & 0x1FU))) != 0U)
      {
        /* Update error code */
        hdma->ErrorCode |= HAL_DMA_ERROR_DME;

        /* Clear the Direct Mode error flag */
        (*ifcr_reg) = DMA_FLAG_DMEIF0_4 << (hdma->StreamIndex & 0x1FU);
      }

      if(((*isr_reg) & (DMA_FLAG_TEIF0_4 << (hdma->StreamIndex & 0x1FU))) != 0U)
      {
        /* Update error code */
        hdma->ErrorCode |= HAL_DMA_ERROR_TE;

        /* Clear the transfer error flag */
        (*ifcr_reg) = DMA_FLAG_TEIF0_4 << (hdma->StreamIndex & 0x1FU);

        /* Change the DMA state */
        hdma->State = HAL_DMA_STATE_READY;

        /* Process Unlocked */
        __HAL_UNLOCK(hdma);

        return HAL_ERROR;
      }
    }
    else /* BDMA channel */
    {
      if(((*isr_reg) & (BDMA_FLAG_TE0 << (hdma->StreamIndex & 0x1FU))) != 0U)
      {
        /* When a DMA transfer error occurs */
        /* A hardware clear of its EN bits is performed */
        /* Clear all flags */
        (*isr_reg) = ((BDMA_ISR_GIF0) << (hdma->StreamIndex & 0x1FU));

        /* Update error code */
        hdma->ErrorCode = HAL_DMA_ERROR_TE;

        /* Change the DMA state */
        hdma->State = HAL_DMA_STATE_READY;

        /* Process Unlocked */
        __HAL_UNLOCK(hdma);

        return HAL_ERROR;
      }
    }

    /* Check for the Timeout (Not applicable in circular mode)*/
    if(Timeout != HAL_MAX_DELAY)
    {
      if(((HAL_GetTick() - tickstart ) > Timeout)||(Timeout == 0U))
      {
        /* Update error code */
        hdma->ErrorCode = HAL_DMA_ERROR_TIMEOUT;

        /* if timeout then abort the current transfer */
        /* No need to check return value: as in this case we will return HAL_ERROR with HAL_DMA_ERROR_TIMEOUT error code  */
        (void) HAL_DMA_Abort(hdma);
          /*
            Note that the Abort function will
              - Clear the transfer error flags
              - Unlock
              - Set the State
          */

        return HAL_ERROR;
      }
    }

    if(IS_DMA_DMAMUX_ALL_INSTANCE(hdma->Instance) != 0U) /* No DMAMUX available for BDMA1 */
    {
      /* Check for DMAMUX Request generator (if used) overrun status */
      if(hdma->DMAmuxRequestGen != 0U)
      {
        /* if using DMAMUX request generator Check for DMAMUX request generator overrun */
        if((hdma->DMAmuxRequestGenStatus->RGSR & hdma->DMAmuxRequestGenStatusMask) != 0U)
        {
          /* Clear the DMAMUX request generator overrun flag */
          hdma->DMAmuxRequestGenStatus->RGCFR = hdma->DMAmuxRequestGenStatusMask;

          /* Update error code */
          hdma->ErrorCode |= HAL_DMA_ERROR_REQGEN;
        }
      }

      /* Check for DMAMUX Synchronization overrun */
      if((hdma->DMAmuxChannelStatus->CSR & hdma->DMAmuxChannelStatusMask) != 0U)
      {
        /* Clear the DMAMUX synchro overrun flag */
        hdma->DMAmuxChannelStatus->CFR = hdma->DMAmuxChannelStatusMask;

        /* Update error code */
        hdma->ErrorCode |= HAL_DMA_ERROR_SYNC;
      }
    }
  }


  /* Get the level transfer complete flag */
  if(CompleteLevel == HAL_DMA_FULL_TRANSFER)
  {
    /* Clear the half transfer and transfer complete flags */
    if(IS_DMA_STREAM_INSTANCE(hdma->Instance) != 0U) /* DMA1 or DMA2 instance */
    {
      (*ifcr_reg) = (DMA_FLAG_HTIF0_4 | DMA_FLAG_TCIF0_4) << (hdma->StreamIndex & 0x1FU);
    }
    else /* BDMA channel */
    {
      (*ifcr_reg) = (BDMA_FLAG_TC0 << (hdma->StreamIndex & 0x1FU));
    }

    hdma->State = HAL_DMA_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hdma);
  }
  else /*CompleteLevel = HAL_DMA_HALF_TRANSFER*/
  {
    /* Clear the half transfer and transfer complete flags */
    if(IS_DMA_STREAM_INSTANCE(hdma->Instance) != 0U) /* DMA1 or DMA2 instance */
    {
      (*ifcr_reg) = (DMA_FLAG_HTIF0_4) << (hdma->StreamIndex & 0x1FU);
    }
    else /* BDMA channel */
    {
      (*ifcr_reg) = (BDMA_FLAG_HT0 << (hdma->StreamIndex & 0x1FU));
    }
  }

  return status;
}

/**
  * @brief  Handles DMA interrupt request.
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA Stream.
  * @retval None
  */
void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma)
{
  uint32_t tmpisr_dma, tmpisr_bdma;
  uint32_t ccr_reg;
  __IO uint32_t count = 0U;
  uint32_t timeout = SystemCoreClock / 9600U;

  /* calculate DMA base and stream number */
  DMA_Base_Registers  *regs_dma  = (DMA_Base_Registers *)hdma->StreamBaseAddress;
  BDMA_Base_Registers *regs_bdma = (BDMA_Base_Registers *)hdma->StreamBaseAddress;

  tmpisr_dma  = regs_dma->ISR;
  tmpisr_bdma = regs_bdma->ISR;

  if(IS_DMA_STREAM_INSTANCE(hdma->Instance) != 0U)  /* DMA1 or DMA2 instance */
  {
    /* Transfer Error Interrupt management ***************************************/
    if ((tmpisr_dma & (DMA_FLAG_TEIF0_4 << (hdma->StreamIndex & 0x1FU))) != 0U)
    {
      if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_TE) != 0U)
      {
        /* Disable the transfer error interrupt */
        ((DMA_Stream_TypeDef   *)hdma->Instance)->CR  &= ~(DMA_IT_TE);

        /* Clear the transfer error flag */
        regs_dma->IFCR = DMA_FLAG_TEIF0_4 << (hdma->StreamIndex & 0x1FU);

        /* Update error code */
        hdma->ErrorCode |= HAL_DMA_ERROR_TE;
      }
    }
    /* FIFO Error Interrupt management ******************************************/
    if ((tmpisr_dma & (DMA_FLAG_FEIF0_4 << (hdma->StreamIndex & 0x1FU))) != 0U)
    {
      if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_FE) != 0U)
      {
        /* Clear the FIFO error flag */
        regs_dma->IFCR = DMA_FLAG_FEIF0_4 << (hdma->StreamIndex & 0x1FU);

        /* Update error code */
        hdma->ErrorCode |= HAL_DMA_ERROR_FE;
      }
    }
    /* Direct Mode Error Interrupt management ***********************************/
    if ((tmpisr_dma & (DMA_FLAG_DMEIF0_4 << (hdma->StreamIndex & 0x1FU))) != 0U)
    {
      if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_DME) != 0U)
      {
        /* Clear the direct mode error flag */
        regs_dma->IFCR = DMA_FLAG_DMEIF0_4 << (hdma->StreamIndex & 0x1FU);

        /* Update error code */
        hdma->ErrorCode |= HAL_DMA_ERROR_DME;
      }
    }
    /* Half Transfer Complete Interrupt management ******************************/
    if ((tmpisr_dma & (DMA_FLAG_HTIF0_4 << (hdma->StreamIndex & 0x1FU))) != 0U)
    {
      if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_HT) != 0U)
      {
        /* Clear the half transfer complete flag */
        regs_dma->IFCR = DMA_FLAG_HTIF0_4 << (hdma->StreamIndex & 0x1FU);

        /* Multi_Buffering mode enabled */
        if(((((DMA_Stream_TypeDef   *)hdma->Instance)->CR) & (uint32_t)(DMA_SxCR_DBM)) != 0U)
        {
          /* Current memory buffer used is Memory 0 */
          if((((DMA_Stream_TypeDef   *)hdma->Instance)->CR & DMA_SxCR_CT) == 0U)
          {
            if(hdma->XferHalfCpltCallback != NULL)
            {
              /* Half transfer callback */
              hdma->XferHalfCpltCallback(hdma);
            }
          }
          /* Current memory buffer used is Memory 1 */
          else
          {
            if(hdma->XferM1HalfCpltCallback != NULL)
            {
              /* Half transfer callback */
              hdma->XferM1HalfCpltCallback(hdma);
            }
          }
        }
        else
        {
          /* Disable the half transfer interrupt if the DMA mode is not CIRCULAR */
          if((((DMA_Stream_TypeDef   *)hdma->Instance)->CR & DMA_SxCR_CIRC) == 0U)
          {
            /* Disable the half transfer interrupt */
            ((DMA_Stream_TypeDef   *)hdma->Instance)->CR  &= ~(DMA_IT_HT);
          }

          if(hdma->XferHalfCpltCallback != NULL)
          {
            /* Half transfer callback */
            hdma->XferHalfCpltCallback(hdma);
          }
        }
      }
    }
    /* Transfer Complete Interrupt management ***********************************/
    if ((tmpisr_dma & (DMA_FLAG_TCIF0_4 << (hdma->StreamIndex & 0x1FU))) != 0U)
    {
      if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_TC) != 0U)
      {
        /* Clear the transfer complete flag */
        regs_dma->IFCR = DMA_FLAG_TCIF0_4 << (hdma->StreamIndex & 0x1FU);

        if(HAL_DMA_STATE_ABORT == hdma->State)
        {
          /* Disable all the transfer interrupts */
          ((DMA_Stream_TypeDef   *)hdma->Instance)->CR  &= ~(DMA_IT_TC | DMA_IT_TE | DMA_IT_DME);
          ((DMA_Stream_TypeDef   *)hdma->Instance)->FCR &= ~(DMA_IT_FE);

          if((hdma->XferHalfCpltCallback != NULL) || (hdma->XferM1HalfCpltCallback != NULL))
          {
            ((DMA_Stream_TypeDef   *)hdma->Instance)->CR  &= ~(DMA_IT_HT);
          }

          /* Clear all interrupt flags at correct offset within the register */
          regs_dma->IFCR = 0x3FUL << (hdma->StreamIndex & 0x1FU);

          /* Change the DMA state */
          hdma->State = HAL_DMA_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hdma);

          if(hdma->XferAbortCallback != NULL)
          {
            hdma->XferAbortCallback(hdma);
          }
          return;
        }

        if(((((DMA_Stream_TypeDef   *)hdma->Instance)->CR) & (uint32_t)(DMA_SxCR_DBM)) != 0U)
        {
          /* Current memory buffer used is Memory 0 */
          if((((DMA_Stream_TypeDef   *)hdma->Instance)->CR & DMA_SxCR_CT) == 0U)
          {
            if(hdma->XferM1CpltCallback != NULL)
            {
              /* Transfer complete Callback for memory1 */
              hdma->XferM1CpltCallback(hdma);
            }
          }
          /* Current memory buffer used is Memory 1 */
          else
          {
            if(hdma->XferCpltCallback != NULL)
            {
              /* Transfer complete Callback for memory0 */
              hdma->XferCpltCallback(hdma);
            }
          }
        }
        /* Disable the transfer complete interrupt if the DMA mode is not CIRCULAR */
        else
        {
          if((((DMA_Stream_TypeDef   *)hdma->Instance)->CR & DMA_SxCR_CIRC) == 0U)
          {
            /* Disable the transfer complete interrupt */
            ((DMA_Stream_TypeDef   *)hdma->Instance)->CR  &= ~(DMA_IT_TC);

            /* Change the DMA state */
            hdma->State = HAL_DMA_STATE_READY;

            /* Process Unlocked */
            __HAL_UNLOCK(hdma);
          }

          if(hdma->XferCpltCallback != NULL)
          {
            /* Transfer complete callback */
            hdma->XferCpltCallback(hdma);
          }
        }
      }
    }

    /* manage error case */
    if(hdma->ErrorCode != HAL_DMA_ERROR_NONE)
    {
      if((hdma->ErrorCode & HAL_DMA_ERROR_TE) != 0U)
      {
        hdma->State = HAL_DMA_STATE_ABORT;

        /* Disable the stream */
        __HAL_DMA_DISABLE(hdma);

        do
        {
          if (++count > timeout)
          {
            break;
          }
        }
        while((((DMA_Stream_TypeDef   *)hdma->Instance)->CR & DMA_SxCR_EN) != 0U);

        if((((DMA_Stream_TypeDef   *)hdma->Instance)->CR & DMA_SxCR_EN) != 0U)
        {
          /* Change the DMA state to error if DMA disable fails */
          hdma->State = HAL_DMA_STATE_ERROR;
        }
        else
        {
          /* Change the DMA state to Ready if DMA disable success */
          hdma->State = HAL_DMA_STATE_READY;
        }

        /* Process Unlocked */
        __HAL_UNLOCK(hdma);
      }

      if(hdma->XferErrorCallback != NULL)
      {
        /* Transfer error callback */
        hdma->XferErrorCallback(hdma);
      }
    }
  }
  else if(IS_BDMA_CHANNEL_INSTANCE(hdma->Instance) != 0U)  /* BDMA instance(s) */
  {
    ccr_reg = (((BDMA_Channel_TypeDef   *)hdma->Instance)->CCR);

    /* Half Transfer Complete Interrupt management ******************************/
    if (((tmpisr_bdma & (BDMA_FLAG_HT0 << (hdma->StreamIndex & 0x1FU))) != 0U) && ((ccr_reg & BDMA_CCR_HTIE) != 0U))
    {
      /* Clear the half transfer complete flag */
      regs_bdma->IFCR = (BDMA_ISR_HTIF0 << (hdma->StreamIndex & 0x1FU));

      /* Disable the transfer complete interrupt if the DMA mode is Double Buffering */
      if((ccr_reg & BDMA_CCR_DBM) != 0U)
      {
        /* Current memory buffer used is Memory 0 */
        if((ccr_reg & BDMA_CCR_CT) == 0U)
        {
          if(hdma->XferM1HalfCpltCallback != NULL)
          {
            /* Half transfer Callback for Memory 1 */
            hdma->XferM1HalfCpltCallback(hdma);
          }
        }
        /* Current memory buffer used is Memory 1 */
        else
        {
          if(hdma->XferHalfCpltCallback != NULL)
          {
            /* Half transfer Callback for Memory 0 */
            hdma->XferHalfCpltCallback(hdma);
          }
        }
      }
      else
      {
        if((ccr_reg & BDMA_CCR_CIRC) == 0U)
        {
          /* Disable the half transfer interrupt */
          __HAL_DMA_DISABLE_IT(hdma, DMA_IT_HT);
        }

        /* DMA peripheral state is not updated in Half Transfer */
        /* but in Transfer Complete case */

       if(hdma->XferHalfCpltCallback != NULL)
        {
          /* Half transfer callback */
          hdma->XferHalfCpltCallback(hdma);
        }
      }
    }

    /* Transfer Complete Interrupt management ***********************************/
    else if (((tmpisr_bdma & (BDMA_FLAG_TC0 << (hdma->StreamIndex & 0x1FU))) != 0U) && ((ccr_reg & BDMA_CCR_TCIE) != 0U))
    {
      /* Clear the transfer complete flag */
      regs_bdma->IFCR = (BDMA_ISR_TCIF0) << (hdma->StreamIndex & 0x1FU);

      /* Disable the transfer complete interrupt if the DMA mode is Double Buffering */
      if((ccr_reg & BDMA_CCR_DBM) != 0U)
      {
        /* Current memory buffer used is Memory 0 */
        if((ccr_reg & BDMA_CCR_CT) == 0U)
        {
          if(hdma->XferM1CpltCallback != NULL)
          {
            /* Transfer complete Callback for Memory 1 */
            hdma->XferM1CpltCallback(hdma);
          }
        }
        /* Current memory buffer used is Memory 1 */
        else
        {
          if(hdma->XferCpltCallback != NULL)
          {
            /* Transfer complete Callback for Memory 0 */
            hdma->XferCpltCallback(hdma);
          }
        }
      }
      else
      {
        if((ccr_reg & BDMA_CCR_CIRC) == 0U)
        {
          /* Disable the transfer complete and error interrupt, if the DMA mode is not CIRCULAR */
          __HAL_DMA_DISABLE_IT(hdma, DMA_IT_TE | DMA_IT_TC);

          /* Change the DMA state */
          hdma->State = HAL_DMA_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hdma);
        }

        if(hdma->XferCpltCallback != NULL)
        {
          /* Transfer complete callback */
          hdma->XferCpltCallback(hdma);
        }
      }
    }
    /* Transfer Error Interrupt management **************************************/
    else if (((tmpisr_bdma & (BDMA_FLAG_TE0 << (hdma->StreamIndex & 0x1FU))) != 0U) && ((ccr_reg & BDMA_CCR_TEIE) != 0U))
    {
      /* When a DMA transfer error occurs */
      /* A hardware clear of its EN bits is performed */
      /* Disable ALL DMA IT */
      __HAL_DMA_DISABLE_IT(hdma, (DMA_IT_TC | DMA_IT_HT | DMA_IT_TE));

      /* Clear all flags */
      regs_bdma->IFCR = (BDMA_ISR_GIF0) << (hdma->StreamIndex & 0x1FU);

      /* Update error code */
      hdma->ErrorCode = HAL_DMA_ERROR_TE;

      /* Change the DMA state */
      hdma->State = HAL_DMA_STATE_READY;

      /* Process Unlocked */
      __HAL_UNLOCK(hdma);

      if (hdma->XferErrorCallback != NULL)
      {
        /* Transfer error callback */
        hdma->XferErrorCallback(hdma);
      }
    }
    else
    {
      /* Nothing To Do */
    }
  }
  else
  {
    /* Nothing To Do */
  }
}

/**
  * @brief  Register callbacks
  * @param  hdma:                 pointer to a DMA_HandleTypeDef structure that contains
  *                               the configuration information for the specified DMA Stream.
  * @param  CallbackID:           User Callback identifier
  *                               a DMA_HandleTypeDef structure as parameter.
  * @param  pCallback:            pointer to private callback function which has pointer to
  *                               a DMA_HandleTypeDef structure as parameter.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID, void (* pCallback)(DMA_HandleTypeDef *_hdma))
{

  HAL_StatusTypeDef status = HAL_OK;

  /* Check the DMA peripheral handle */
  if(hdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hdma);

  if(HAL_DMA_STATE_READY == hdma->State)
  {
    switch (CallbackID)
    {
    case  HAL_DMA_XFER_CPLT_CB_ID:
      hdma->XferCpltCallback = pCallback;
      break;

    case  HAL_DMA_XFER_HALFCPLT_CB_ID:
      hdma->XferHalfCpltCallback = pCallback;
      break;

    case  HAL_DMA_XFER_M1CPLT_CB_ID:
      hdma->XferM1CpltCallback = pCallback;
      break;

    case  HAL_DMA_XFER_M1HALFCPLT_CB_ID:
      hdma->XferM1HalfCpltCallback = pCallback;
      break;

    case  HAL_DMA_XFER_ERROR_CB_ID:
      hdma->XferErrorCallback = pCallback;
      break;

    case  HAL_DMA_XFER_ABORT_CB_ID:
      hdma->XferAbortCallback = pCallback;
      break;

    default:
      status =  HAL_ERROR;
      break;
    }
  }
  else
  {
    /* Return error status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hdma);

  return status;
}

/**
  * @brief  UnRegister callbacks
  * @param  hdma:                 pointer to a DMA_HandleTypeDef structure that contains
  *                               the configuration information for the specified DMA Stream.
  * @param  CallbackID:           User Callback identifier
  *                               a HAL_DMA_CallbackIDTypeDef ENUM as parameter.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the DMA peripheral handle */
  if(hdma == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hdma);

  if(HAL_DMA_STATE_READY == hdma->State)
  {
    switch (CallbackID)
    {
    case  HAL_DMA_XFER_CPLT_CB_ID:
      hdma->XferCpltCallback = NULL;
      break;

    case  HAL_DMA_XFER_HALFCPLT_CB_ID:
      hdma->XferHalfCpltCallback = NULL;
      break;

    case  HAL_DMA_XFER_M1CPLT_CB_ID:
      hdma->XferM1CpltCallback = NULL;
      break;

    case  HAL_DMA_XFER_M1HALFCPLT_CB_ID:
      hdma->XferM1HalfCpltCallback = NULL;
      break;

    case  HAL_DMA_XFER_ERROR_CB_ID:
      hdma->XferErrorCallback = NULL;
      break;

    case  HAL_DMA_XFER_ABORT_CB_ID:
      hdma->XferAbortCallback = NULL;
      break;

    case   HAL_DMA_XFER_ALL_CB_ID:
      hdma->XferCpltCallback = NULL;
      hdma->XferHalfCpltCallback = NULL;
      hdma->XferM1CpltCallback = NULL;
      hdma->XferM1HalfCpltCallback = NULL;
      hdma->XferErrorCallback = NULL;
      hdma->XferAbortCallback = NULL;
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
  __HAL_UNLOCK(hdma);

  return status;
}

/**
  * @}
  */

/** @addtogroup DMA_Exported_Functions_Group3
  *
@verbatim
 ===============================================================================
                    ##### State and Errors functions #####
 ===============================================================================
    [..]
    This subsection provides functions allowing to
      (+) Check the DMA state
      (+) Get error code

@endverbatim
  * @{
  */

/**
  * @brief  Returns the DMA state.
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA Stream.
  * @retval HAL state
  */
HAL_DMA_StateTypeDef HAL_DMA_GetState(DMA_HandleTypeDef *hdma)
{
  return hdma->State;
}

/**
  * @brief  Return the DMA error code
  * @param  hdma : pointer to a DMA_HandleTypeDef structure that contains
  *              the configuration information for the specified DMA Stream.
  * @retval DMA Error Code
  */
uint32_t HAL_DMA_GetError(DMA_HandleTypeDef *hdma)
{
  return hdma->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup DMA_Private_Functions
  * @{
  */

/**
  * @brief  Sets the DMA Transfer parameter.
  * @param  hdma:       pointer to a DMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified DMA Stream.
  * @param  SrcAddress: The source memory Buffer address
  * @param  DstAddress: The destination memory Buffer address
  * @param  DataLength: The length of data to be transferred from source to destination
  * @retval None
  */
static void DMA_SetConfig(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
  /* calculate DMA base and stream number */
  DMA_Base_Registers  *regs_dma  = (DMA_Base_Registers *)hdma->StreamBaseAddress;
  BDMA_Base_Registers *regs_bdma = (BDMA_Base_Registers *)hdma->StreamBaseAddress;

  if(IS_DMA_DMAMUX_ALL_INSTANCE(hdma->Instance) != 0U) /* No DMAMUX available for BDMA1 */
  {
    /* Clear the DMAMUX synchro overrun flag */
    hdma->DMAmuxChannelStatus->CFR = hdma->DMAmuxChannelStatusMask;

    if(hdma->DMAmuxRequestGen != 0U)
    {
      /* Clear the DMAMUX request generator overrun flag */
      hdma->DMAmuxRequestGenStatus->RGCFR = hdma->DMAmuxRequestGenStatusMask;
    }
  }

  if(IS_DMA_STREAM_INSTANCE(hdma->Instance) != 0U) /* DMA1 or DMA2 instance */
  {
    /* Clear all interrupt flags at correct offset within the register */
    regs_dma->IFCR = 0x3FUL << (hdma->StreamIndex & 0x1FU);

    /* Clear DBM bit */
    ((DMA_Stream_TypeDef *)hdma->Instance)->CR &= (uint32_t)(~DMA_SxCR_DBM);

    /* Configure DMA Stream data length */
    ((DMA_Stream_TypeDef *)hdma->Instance)->NDTR = DataLength;

    /* Peripheral to Memory */
    if((hdma->Init.Direction) == DMA_MEMORY_TO_PERIPH)
    {
      /* Configure DMA Stream destination address */
      ((DMA_Stream_TypeDef *)hdma->Instance)->PAR = DstAddress;

      /* Configure DMA Stream source address */
      ((DMA_Stream_TypeDef *)hdma->Instance)->M0AR = SrcAddress;
    }
    /* Memory to Peripheral */
    else
    {
      /* Configure DMA Stream source address */
      ((DMA_Stream_TypeDef *)hdma->Instance)->PAR = SrcAddress;

      /* Configure DMA Stream destination address */
      ((DMA_Stream_TypeDef *)hdma->Instance)->M0AR = DstAddress;
    }
  }
  else if(IS_BDMA_CHANNEL_INSTANCE(hdma->Instance) != 0U) /* BDMA instance(s) */
  {
    /* Clear all flags */
    regs_bdma->IFCR = (BDMA_ISR_GIF0) << (hdma->StreamIndex & 0x1FU);

    /* Configure DMA Channel data length */
    ((BDMA_Channel_TypeDef *)hdma->Instance)->CNDTR = DataLength;

    /* Peripheral to Memory */
    if((hdma->Init.Direction) == DMA_MEMORY_TO_PERIPH)
    {
      /* Configure DMA Channel destination address */
      ((BDMA_Channel_TypeDef *)hdma->Instance)->CPAR = DstAddress;

      /* Configure DMA Channel source address */
      ((BDMA_Channel_TypeDef *)hdma->Instance)->CM0AR = SrcAddress;
    }
    /* Memory to Peripheral */
    else
    {
      /* Configure DMA Channel source address */
      ((BDMA_Channel_TypeDef *)hdma->Instance)->CPAR = SrcAddress;

      /* Configure DMA Channel destination address */
      ((BDMA_Channel_TypeDef *)hdma->Instance)->CM0AR = DstAddress;
    }
  }
  else
  {
    /* Nothing To Do */
  }
}

/**
  * @brief  Returns the DMA Stream base address depending on stream number
  * @param  hdma:       pointer to a DMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified DMA Stream.
  * @retval Stream base address
  */
static uint32_t DMA_CalcBaseAndBitshift(DMA_HandleTypeDef *hdma)
{
  if(IS_DMA_STREAM_INSTANCE(hdma->Instance) != 0U) /* DMA1 or DMA2 instance */
  {
    uint32_t stream_number = (((uint32_t)((uint32_t*)hdma->Instance) & 0xFFU) - 16U) / 24U;

    /* lookup table for necessary bitshift of flags within status registers */
    static const uint8_t flagBitshiftOffset[8U] = {0U, 6U, 16U, 22U, 0U, 6U, 16U, 22U};
    hdma->StreamIndex = flagBitshiftOffset[stream_number & 0x7U];

    if (stream_number > 3U)
    {
      /* return pointer to HISR and HIFCR */
      hdma->StreamBaseAddress = (((uint32_t)((uint32_t*)hdma->Instance) & (uint32_t)(~0x3FFU)) + 4U);
    }
    else
    {
      /* return pointer to LISR and LIFCR */
      hdma->StreamBaseAddress = ((uint32_t)((uint32_t*)hdma->Instance) & (uint32_t)(~0x3FFU));
    }
  }
  else /* BDMA instance(s) */
  {
    /* return pointer to ISR and IFCR */
    hdma->StreamBaseAddress = ((uint32_t)((uint32_t*)hdma->Instance) & (uint32_t)(~0xFFU));
  }

  return hdma->StreamBaseAddress;
}

/**
  * @brief  Check compatibility between FIFO threshold level and size of the memory burst
  * @param  hdma:       pointer to a DMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified DMA Stream.
  * @retval HAL status
  */
static HAL_StatusTypeDef DMA_CheckFifoParam(DMA_HandleTypeDef *hdma)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Memory Data size equal to Byte */
  if (hdma->Init.MemDataAlignment == DMA_MDATAALIGN_BYTE)
  {
    switch (hdma->Init.FIFOThreshold)
    {
      case DMA_FIFO_THRESHOLD_1QUARTERFULL:
      case DMA_FIFO_THRESHOLD_3QUARTERSFULL:

        if ((hdma->Init.MemBurst & DMA_SxCR_MBURST_1) == DMA_SxCR_MBURST_1)
        {
          status = HAL_ERROR;
        }
        break;

      case DMA_FIFO_THRESHOLD_HALFFULL:
        if (hdma->Init.MemBurst == DMA_MBURST_INC16)
        {
          status = HAL_ERROR;
        }
        break;

      case DMA_FIFO_THRESHOLD_FULL:
        break;

      default:
        break;
    }
  }

  /* Memory Data size equal to Half-Word */
  else if (hdma->Init.MemDataAlignment == DMA_MDATAALIGN_HALFWORD)
  {
    switch (hdma->Init.FIFOThreshold)
    {
      case DMA_FIFO_THRESHOLD_1QUARTERFULL:
      case DMA_FIFO_THRESHOLD_3QUARTERSFULL:
        status = HAL_ERROR;
        break;

      case DMA_FIFO_THRESHOLD_HALFFULL:
        if ((hdma->Init.MemBurst & DMA_SxCR_MBURST_1) == DMA_SxCR_MBURST_1)
        {
          status = HAL_ERROR;
        }
        break;

      case DMA_FIFO_THRESHOLD_FULL:
        if (hdma->Init.MemBurst == DMA_MBURST_INC16)
        {
          status = HAL_ERROR;
        }
        break;

      default:
        break;
    }
  }

  /* Memory Data size equal to Word */
  else
  {
    switch (hdma->Init.FIFOThreshold)
    {
      case DMA_FIFO_THRESHOLD_1QUARTERFULL:
      case DMA_FIFO_THRESHOLD_HALFFULL:
      case DMA_FIFO_THRESHOLD_3QUARTERSFULL:
        status = HAL_ERROR;
        break;

      case DMA_FIFO_THRESHOLD_FULL:
        if ((hdma->Init.MemBurst & DMA_SxCR_MBURST_1) == DMA_SxCR_MBURST_1)
        {
          status = HAL_ERROR;
        }
    break;

      default:
        break;
    }
  }

  return status;
}

/**
  * @brief  Updates the DMA handle with the DMAMUX  channel and status mask depending on stream number
  * @param  hdma:       pointer to a DMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified DMA Stream.
  * @retval HAL status
  */
static void DMA_CalcDMAMUXChannelBaseAndMask(DMA_HandleTypeDef *hdma)
{
  uint32_t stream_number;
  uint32_t stream_baseaddress = (uint32_t)((uint32_t*)hdma->Instance);

  if(IS_BDMA_CHANNEL_DMAMUX_INSTANCE(hdma->Instance) != 0U)
  {
    /* BDMA Channels are connected to DMAMUX2 channels */
    stream_number = (((uint32_t)((uint32_t*)hdma->Instance) & 0xFFU) - 8U) / 20U;
    hdma->DMAmuxChannel = (DMAMUX_Channel_TypeDef *)((uint32_t)(((uint32_t)DMAMUX2_Channel0) + (stream_number * 4U)));
    hdma->DMAmuxChannelStatus = DMAMUX2_ChannelStatus;
    hdma->DMAmuxChannelStatusMask = 1UL << (stream_number & 0x1FU);
  }
  else
  {
    /* DMA1/DMA2 Streams are connected to DMAMUX1 channels */
    stream_number = (((uint32_t)((uint32_t*)hdma->Instance) & 0xFFU) - 16U) / 24U;

    if((stream_baseaddress <= ((uint32_t)DMA2_Stream7) ) && \
       (stream_baseaddress >= ((uint32_t)DMA2_Stream0)))
    {
      stream_number += 8U;
    }
    hdma->DMAmuxChannel = (DMAMUX_Channel_TypeDef *)((uint32_t)(((uint32_t)DMAMUX1_Channel0) + (stream_number * 4U)));
    hdma->DMAmuxChannelStatus = DMAMUX1_ChannelStatus;
    hdma->DMAmuxChannelStatusMask = 1UL << (stream_number & 0x1FU);
  }
}

/**
  * @brief  Updates the DMA handle with the DMAMUX  request generator params
  * @param  hdma:       pointer to a DMA_HandleTypeDef structure that contains
  *                     the configuration information for the specified DMA Stream.
  * @retval HAL status
  */
static void DMA_CalcDMAMUXRequestGenBaseAndMask(DMA_HandleTypeDef *hdma)
{
  uint32_t request =  hdma->Init.Request & DMAMUX_CxCR_DMAREQ_ID;

  if((request >= DMA_REQUEST_GENERATOR0) && (request <= DMA_REQUEST_GENERATOR7))
  {
    if(IS_BDMA_CHANNEL_DMAMUX_INSTANCE(hdma->Instance) != 0U)
    {
      /* BDMA Channels are connected to DMAMUX2 request generator blocks */
      hdma->DMAmuxRequestGen = (DMAMUX_RequestGen_TypeDef *)((uint32_t)(((uint32_t)DMAMUX2_RequestGenerator0) + ((request - 1U) * 4U)));

      hdma->DMAmuxRequestGenStatus = DMAMUX2_RequestGenStatus;
    }
    else
    {
      /* DMA1 and DMA2 Streams use DMAMUX1 request generator blocks */
      hdma->DMAmuxRequestGen = (DMAMUX_RequestGen_TypeDef *)((uint32_t)(((uint32_t)DMAMUX1_RequestGenerator0) + ((request - 1U) * 4U)));

      hdma->DMAmuxRequestGenStatus = DMAMUX1_RequestGenStatus;
    }

    hdma->DMAmuxRequestGenStatusMask = 1UL << (request - 1U);
  }
}

/**
  * @}
  */

#endif /* HAL_DMA_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

