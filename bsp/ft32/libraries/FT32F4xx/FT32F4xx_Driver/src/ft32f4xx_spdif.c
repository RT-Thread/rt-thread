/**
  ******************************************************************************
  * @file    ft32f4xx_spdif.c
  * @author  xcao
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the SPDIFRX audio interface:
  *           + Initialization and Configuration
  *           + Data transfers functions
  *           + DMA transfers management
  *           + Interrupts and flags management
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_spdif.h"
#include "ft32f4xx_misc.h"
#define MAX_DELAY   0xFFFF
/** @addtogroup FT32F4XX_Driver
  * @{
  */

/** @defgroup SPDIF SPDIF
  * @brief SPDIFmodule driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup SPDIF_Private_Defines SPDIF Private Defines
  * @{
  */

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup SPDIF_Exported_Functions SPDIF Exported Functions
  * @{
  */

/** @defgroup  SPDIF_Exported_Functions_Group1 Initialization
  *  @brief    Initialization and Configuration functions
  *
  @verbatim
  ===============================================================================
  ##### Initialization and de-initialization functions #####
  ===============================================================================
  [..]  This subsection provides a set of functions allowing to initialize and
        de-initialize the SPDIF peripheral:

  @endverbatim
  * @{
  */

/**
  * @brief  Initializes the SPDIF according to the specified parameters
  *         in the SPDIF_InitTypeDef and create the associated handle.
  * @param  spdif SPDIF handle
  * @retval NONE
  */
void SPDIFRX_Init(SPDIF_HandleTypeDef *spdif, SPDIFRX_InitTypeDef *spdifrx_init)
{
    uint32_t  tmpreg;

    /* Init the low level hardware : GPIO, CLOCK, CORTEX...etc */
    SPDIF_MspInit(spdif);

    /* SFR block register reset */
    spdif->Instance->SPDIF_CTRL &= ~SPDIF_CTRL_SFR_ENABLE;
    //while((spdif->Instance->SPDIF_CTRL&SPDIF_CTRL_SFR_ENABLE) != SPDIF_CTRL_SFR_ENABLE)
    spdif->Instance->SPDIF_CTRL |= SPDIF_CTRL_SFR_ENABLE;

    /* SPDIF core reset */
    spdif->Instance->SPDIF_CTRL &= ~SPDIF_CTRL_SPDIF_ENABLE;
    /* SPDIF core enable */
    spdif->Instance->SPDIF_CTRL |= SPDIF_CTRL_SPDIF_ENABLE;

    /* FIFO reset */
    spdif->Instance->SPDIF_CTRL &= ~SPDIF_CTRL_FIFO_ENABLE;
    while ((spdif->Instance->SPDIF_CTRL & SPDIF_CTRL_FIFO_ENABLE) != SPDIF_CTRL_FIFO_ENABLE)

        /* Reset the old SPDIF CTRL configuration */
        tmpreg = spdif->Instance->SPDIF_CTRL;

    tmpreg &= ~(SPDIF_CTRL_TR_MODE | SPDIF_CTRL_VALIDITYCHECK | SPDIF_CTRL_PARITYCHECK);

    tmpreg |= (uint32_t)(spdifrx_init->StereoMode |
                         spdifrx_init->ValidityBitMask |
                         spdifrx_init->ParityErrorMask |
                         SPDIF_CTRL_INTREQ_MASK);

    spdif->Instance->SPDIF_CTRL = tmpreg;

    /* Set receive fifo almost full and empty threshold */
    spdif->Instance->FIFO_CTRL = ((spdifrx_init->FifoAfullThreshold << 16U) | (spdifrx_init->FifoAemptyThreshold));
}

/**
  * @brief SPDIF MSP Init
  * @param spdif SPDIF handle
  * @retval None
  */
void __attribute__((weak)) SPDIF_MspInit(SPDIF_HandleTypeDef *spdif)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(spdif);

    /* NOTE : This function Should not be modified, when the callback is needed,
    the SPDIFRX_MspInit could be implemented in the user file
    */
}


/**
  * @brief  Receives an amount of data (Data Flow) in blocking mode.
  * @param  spdif pointer to SPDIF_HandleTypeDef structure that contains
  *               the configuration information for SPDIF module.
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be received
  * @param  Timeout Timeout duration
  * @retval none
  */
void  SPDIF_ReceiveDataFlow(SPDIF_HandleTypeDef *spdif, uint32_t *pData, uint16_t Size,
                            uint32_t Timeout)
{
    uint32_t tickstart;
    uint16_t sizeCounter = Size;
    uint32_t *pTmpBuf = pData;

    if ((pData == NULL) || (Size == 0U))
    {
        return;
    }

    /* Start reception */
    spdif->Instance->SPDIF_CTRL |= SPDIF_CTRL_SPDIF_ENABLE;

    /* Wait until lock flag is set */
    while ((spdif->Instance->STAT & SPDIF_STAT_LOCK_FLAG) != SPDIF_STAT_LOCK_FLAG)
    {
        if (Timeout != MAX_DELAY)
        {
            if ((GetTick() - tickstart > Timeout) || (Timeout == 0U))
            {
                return;
            }
        }
    }

    /* Receive data flow */
    while (sizeCounter > 0U)
    {
        if ((spdif->Instance->STAT & SPDIF_STAT_EMPTY_FLAG) != SPDIF_STAT_EMPTY_FLAG)
        {
            (*pTmpBuf) = spdif->Instance->DATA;
            pTmpBuf++;
            sizeCounter--;
        }
    }
}

/**
  * @brief  Receives an amount of data (Data Flow) in non-blocking mode.
  * @param  spdif pointer to SPDIF_HandleTypeDef structure that contains
  *               the configuration information for SPDIF module.
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be received
  * @param  Timeout Timeout duration
  * @retval none
  */
void SPDIFRX_ReceiveDataFlow_IT(SPDIF_HandleTypeDef *spdif, uint32_t *pData, uint16_t Size,
                                uint32_t Timeout)
{
    uint32_t tickstart;
    uint16_t sizeCounter = Size;
    uint32_t *pTmpBuf = pData;

    if ((pData == NULL) || (Size == 0U))
    {
        return;
    }

    /* Enable the SPDIFRX  Parity Error Interrupt */
    spdif->Instance->SPDIF_CTRL |= SPDIF_CTRL_PARITY_MASK;

    /* Enable the SPDIFRX  OVR Error Interrupt */
    spdif->Instance->SPDIF_CTRL |= SPDIF_CTRL_OVRERR_MASK;

    /* Start reception */
    spdif->Instance->SPDIF_CTRL |= SPDIF_CTRL_SPDIF_ENABLE;

    /* Wait until lock flag is set */
    while ((spdif->Instance->STAT & SPDIF_STAT_LOCK_FLAG) != SPDIF_STAT_LOCK_FLAG)
    {
        if (Timeout != MAX_DELAY)
        {
            if ((GetTick() - tickstart > Timeout) || (Timeout == 0U))
            {
                return;
            }
        }
    }

}
