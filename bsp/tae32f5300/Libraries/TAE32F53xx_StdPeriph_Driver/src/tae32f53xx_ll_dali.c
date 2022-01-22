/**
  ******************************************************************************
  * @file    tae32f53xx_ll_dali.c
  * @author  MCD Application Team
  * @brief   Source file for DALI module
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll.h"


#define DBG_TAG             "DALI LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup DALI_LL DALI LL
  * @brief    DALI LL module driver.
  * @{
  */

#ifdef LL_DALI_MODULE_ENABLED

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup DALI_LL_Exported_Functions DALI LL Exported Functions
  * @brief    DALI LL Exported Functions
  * @{
  */

/** @defgroup DALI_LL_Exported_Functions_Group1 Initialization and De-Initialization functions
  * @brief    Initialization and De-Initialization functions
@verbatim
  ==============================================================================
              ##### Initialization and De-Initialization functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the DALI Module.
    (+) De-initialize the DALI Module.
@endverbatim
* @{
*/

/**
  * @brief  Initialize the DALI peripheral
  * @param  Instance DALI peripheral instance
  * @param  Init pointer to a DALI_InitTypeDef structure that contains the configuration
  *         information for the specified DALI peripheral.
  * @return status of the initialization
  */
LL_StatusETypeDef LL_DALI_Init(DALI_TypeDef *Instance, DALI_InitTypeDef *Init)
{
    uint32_t prescaler = LL_SYSCTRL_APB1ClkGet() / 16 / Init->Baudrate;

    /* Check the parameters */
    assert_param(IS_DALI_ALL_INSTANCE(Instance));
    assert_param(Init != NULL);
    assert_param(IS_DALI_MODE(Init->Mode));
    assert_param(IS_DALI_MESSAGE_LEN(Init->MessageLen));
    assert_param(IS_DALI_POLARITY(Init->Polarity));
    assert_param(IS_DALI_FILTER_ENABLE(Init->Filter));
    assert_param(IS_DALI_FORWARD_DELAY(Init->ForwardDelay));
    assert_param(IS_DALI_BACKWARD_DELAY(Init->BackwardDelay));
    assert_param(IS_DALI_BAUDRATE(Init->Baudrate));
    assert_param(IS_DALI_PRESCALE(prescaler));

    /* Handle Something */
    LL_DALI_MspInit(Instance);

    /* Disable DALI before configuration */
    __LL_DALI_DISABLE(Instance);

    /* Clear all pending flags */
    __LL_DALI_PENDING_FLAG_CLEAR(Instance, (DALI_FLAG_BEIF
                                            | DALI_FLAG_FEIF
                                            | DALI_FLAG_BDIF
                                            | DALI_FLAG_FDIF));

    /* Configures: Forward frame message length, Polarity, Working mode */
    WRITE_REG(Instance->CR, (Init->MessageLen | Init->Polarity | Init->Mode));

    /* Configures: Filter feature enable, Filter counter value */
    if (Init->Filter == DALI_FILTER_ENABLE) {
        assert_param(IS_DALI_FILTER_COUNTER(Init->FilterCounter));

        WRITE_REG(Instance->FCR, (Init->Filter | Init->FilterCounter));
    } else {
        WRITE_REG(Instance->FCR, 0);
    }

    /* Configures: Prescaler */
    WRITE_REG(Instance->PSCR, (DALI_PSCR_FTR_Msk | (prescaler & DALI_PSCR_PSC_Msk)));

    /* Configures: Timing control */
    WRITE_REG(Instance->TCR, ((Init->BackwardDelay << 16)
                              | (Init->ForwardDelay)));

    /* Enable DALI module */
    __LL_DALI_ENABLE(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  DeInitializes the DALI
  * @param  Instance DALI peripheral instance
  * @return status of the initialization
  */
LL_StatusETypeDef LL_DALI_DeInit(DALI_TypeDef *Instance)
{
    /* Check the parameters */
    assert_param(IS_DALI_ALL_INSTANCE(Instance));

    /* Disable DALI before configuration */
    __LL_DALI_DISABLE(Instance);

    /* Handle Something */
    LL_DALI_MspDeInit(Instance);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Initializes the DALI MSP.
  * @param  Instance DALI peripheral
  * @return None
  */
__WEAK void LL_DALI_MspInit(DALI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_DALI_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the DALI MSP
  * @param  Instance DALI peripheral
  * @return None
  */
__WEAK void LL_DALI_MspDeInit(DALI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_DALI_MspDeInit could be implemented in the user file
     */
}

/**
  * @}
  */


/** @defgroup DALI_LL_Exported_Functions_Group2 DALI Peripheral State functions
  * @brief    DALI Peripheral State functions
@verbatim
  ===============================================================================
                       ##### Peripheral State functions #####
  ===============================================================================
  [..]
    This section provides functions allowing to:
    (+) Peripheral State functions
@endverbatim
  * @{
  */

/**
  * @brief  Wait for a DALI operation to complete.
  * @param  Timeout Maximum DALI operation timeout
  * @return LL Status
  */
LL_StatusETypeDef LL_DALI_WaitForLastOperation(DALI_TypeDef *Instance, uint32_t Timeout)
{
    uint32_t tickstart = LL_GetTick();

    /* Wait for the DALI operation to complete by polling on BUSY flag to be reset.
       Even if the DALI operation fails, the BUSY flag will be reset and an error
       flag will be set */
    while (__LL_DALI_STATUS_FLAG_GET(Instance, DALI_FLAG_BSY) != RESET) {
        if (Timeout != LL_WAIT_FOREVER) {
            if ((Timeout == 0U) || ((LL_GetTick() - tickstart) > Timeout)) {
                return LL_TIMEOUT;
            }
        }
    }

    /* Check if any errors occurred */
    if ((__LL_DALI_PENDING_FLAG_GET(Instance, DALI_FLAG_FEIF) != RESET) ||
        (__LL_DALI_PENDING_FLAG_GET(Instance, DALI_FLAG_BEIF) != RESET)) {
        return LL_ERROR;
    }

    /* Return function status */
    return LL_OK;
}

/**
  * @}
  */


/** @defgroup DALI_LL_Exported_Functions_Group3 DALI IO operation functions
  * @brief    DALI IO operation functions
  *
@verbatim
  ==============================================================================
             ##### IO operation functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) DALI Master Transmit forward frame (with or without interruption).
      (+) DALI Master Receive backward frame (with or without interruption).
      (+) DALI Slave Transmit backward frame (with or without interruption).
      (+) DALI Slave Receive forward frame (with or without interruption).
@endverbatim
  * @{
  */

/**
  * @brief  DALI Master transmit forward data
  * @note   This function can only be used when DALI working in MASTER mode
  * @param  Instance DALI peripheral
  * @param  ForwardData forward frame data
  * @return LL Status
  */
LL_StatusETypeDef LL_DALI_Master_Transmit(DALI_TypeDef *Instance, uint32_t ForwardData)
{
    LL_StatusETypeDef status;

    /* Check the parameters */
    assert_param(IS_DALI_ALL_INSTANCE(Instance));

    /* Wait until last operation complete */
    if ((status = LL_DALI_WaitForLastOperation(Instance, DALI_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Write Data to Forward Data Register */
        WRITE_REG(Instance->FDR, ForwardData & 0xFFFFFFUL);

        /* Start transmission */
        SET_BIT(Instance->CR, DALI_CR_TS);

        /* Wait until operation complete */
        if ((status = LL_DALI_WaitForLastOperation(Instance, DALI_TIMEOUT_MAX_VALUE)) == LL_OK) {
            if (__LL_DALI_PENDING_FLAG_GET(Instance, DALI_FLAG_FDIF) != SET) {
                status = LL_FAILED;
            }

            /* Clear forward done flag */
            __LL_DALI_PENDING_FLAG_CLEAR(Instance, DALI_FLAG_FDIF);
        }
    }

    /* Return function status */
    return status;
}

/**
  * @brief  DALI Master transmit forward data with interrupt
  * @note   This function can only be used when DALI working in MASTER mode
  * @param  Instance DALI peripheral
  * @param  ForwardData forward frame data
  * @return LL Status
  */
LL_StatusETypeDef LL_DALI_Master_Transmit_IT(DALI_TypeDef *Instance, uint32_t ForwardData)
{
    LL_StatusETypeDef status;

    /* Check the parameters */
    assert_param(IS_DALI_ALL_INSTANCE(Instance));

    /* Wait until last operation complete */
    if ((status = LL_DALI_WaitForLastOperation(Instance, DALI_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Write Data to Forward Data Register */
        WRITE_REG(Instance->FDR, ForwardData & 0xFFFFFFUL);

        /* Enable FDIE interrupts */
        __LL_DALI_IT_ENABLE(Instance, DALI_IT_FDIE);

        /* Start transmission */
        SET_BIT(Instance->CR, DALI_CR_TS);
    }

    /* Return function status */
    return status;
}

/**
  * @brief  DALI Master receive backward data
  * @note   This function can only be used when DALI working in MASTER mode
  * @param  Instance DALI peripheral
  * @param  BackwardData Specifies the data pointer to read in.
  * @return LL status
  */
LL_StatusETypeDef LL_DALI_Master_Receive(DALI_TypeDef *Instance, uint8_t *BackwardData)
{
    LL_StatusETypeDef status;

    /* Check the parameters */
    assert_param(IS_DALI_ALL_INSTANCE(Instance));
    assert_param(BackwardData != NULL);

    /* Wait until last operation complete */
    if ((status = LL_DALI_WaitForLastOperation(Instance, DALI_TIMEOUT_MAX_VALUE)) == LL_OK) {

        /* Check and clear BDIF flag */
        if (__LL_DALI_PENDING_FLAG_GET(Instance, DALI_FLAG_BDIF) != RESET) {
            __LL_DALI_PENDING_FLAG_CLEAR(Instance, DALI_FLAG_BDIF);

            *BackwardData = READ_REG(Instance->BDR) & 0xFFUL;
        } else {
            status = LL_FAILED;
        }
    }

    /* Return function status */
    return status;
}

/**
  * @brief  DALI Master receive backward data with interrupt
  * @note   This function can only be used when DALI working in MASTER mode
  * @param  Instance DALI peripheral
  * @note   Use __LL_DALI_MSTR_READ_BACKWARD_DATA() to get the backword data in IRQ callbacks
  * @return LL status
  */
LL_StatusETypeDef LL_DALI_Master_Receive_IT(DALI_TypeDef *Instance)
{
    LL_StatusETypeDef status;

    /* Check the parameters */
    assert_param(IS_DALI_ALL_INSTANCE(Instance));

    /* Wait until last operation complete */
    if ((status = LL_DALI_WaitForLastOperation(Instance, DALI_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Enable BDIE interrupts */
        __LL_DALI_IT_ENABLE(Instance, DALI_IT_BDIE);
    }

    /* Return function status */
    return status;
}

/**
  * @brief  DALI Slave transmit backward data
  * @note   This function can only be used when DALI working in SLAVE mode
  * @param  Instance DALI peripheral
  * @param  BackwardData backward frame data
  * @return LL status
  */
LL_StatusETypeDef LL_DALI_Slave_Transmit(DALI_TypeDef *Instance, uint8_t BackwardData)
{
    LL_StatusETypeDef status;

    /* Check the parameters */
    assert_param(IS_DALI_ALL_INSTANCE(Instance));

    /* Wait until last operation complete */
    if ((status = LL_DALI_WaitForLastOperation(Instance, DALI_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Write Data to Forward Data Register */
        WRITE_REG(Instance->BDR, BackwardData);

        /* Start transmission */
        SET_BIT(Instance->CR, DALI_CR_TS);

        /* Wait until operation complete */
        if ((status = LL_DALI_WaitForLastOperation(Instance, DALI_TIMEOUT_MAX_VALUE)) == LL_OK) {
            if (__LL_DALI_PENDING_FLAG_GET(Instance, DALI_FLAG_BDIF) != SET) {
                status = LL_FAILED;
            }

            /* Clear forward done flag */
            __LL_DALI_PENDING_FLAG_CLEAR(Instance, DALI_FLAG_BDIF);
        }
    }

    /* Return function status */
    return status;
}

/**
  * @brief  DALI Slave transmit backward data with interrupt
  * @note   This function can only be used when DALI working in SLAVE mode
  * @param  Instance DALI peripheral
  * @param  BackwardData backward frame data
  * @return LL status
  */
LL_StatusETypeDef LL_DALI_Slave_Transmit_IT(DALI_TypeDef *Instance, uint8_t BackwardData)
{
    LL_StatusETypeDef status;

    /* Check the parameters */
    assert_param(IS_DALI_ALL_INSTANCE(Instance));

    /* Wait until last operation complete */
    if ((status = LL_DALI_WaitForLastOperation(Instance, DALI_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Write Data to Forward Data Register */
        WRITE_REG(Instance->BDR, BackwardData);

        /* Enable BDIE interrupts */
        __LL_DALI_IT_ENABLE(Instance, DALI_IT_BDIE);

        /* Start transmission */
        SET_BIT(Instance->CR, DALI_CR_TS);

    }

    /* Return function status */
    return status;
}

/**
  * @brief  DALI Slave receive forward data
  * @note   This function can only be used when DALI working in SLAVE mode
  * @param  Instance DALI peripheral
  * @param  ForwardData Specifies the data pointer to read in.
  * @return LL status
  */
LL_StatusETypeDef LL_DALI_Slave_Receive(DALI_TypeDef *Instance, uint32_t *ForwardData)
{
    LL_StatusETypeDef status;

    /* Check the parameters */
    assert_param(IS_DALI_ALL_INSTANCE(Instance));
    assert_param(ForwardData != NULL);

    /* Wait until last operation complete */
    if ((status = LL_DALI_WaitForLastOperation(Instance, DALI_TIMEOUT_MAX_VALUE)) == LL_OK) {

        /* Check and clear FDIF flag */
        if (__LL_DALI_PENDING_FLAG_GET(Instance, DALI_FLAG_FDIF) != RESET) {
            __LL_DALI_PENDING_FLAG_CLEAR(Instance, DALI_FLAG_FDIF);

            *ForwardData = READ_REG(Instance->FDR) & 0xFFFFFFUL;
        } else {
            status = LL_FAILED;
        }
    }

    /* Return function status */
    return status;
}

/**
  * @brief  DALI Slave receive forward data with interrupt
  * @note   This function can only be used when DALI working in SLAVE mode
  * @param  Instance DALI peripheral
  * @note   Use __LL_DALI_SLV_READ_FORWARD_DATA() to get the forward data in IRQ callbacks
  * @return LL status
  */
LL_StatusETypeDef LL_DALI_Slave_Receive_IT(DALI_TypeDef *Instance)
{
    LL_StatusETypeDef status;

    /* Check the parameters */
    assert_param(IS_DALI_ALL_INSTANCE(Instance));

    /* Wait until last operation complete */
    if ((status = LL_DALI_WaitForLastOperation(Instance, DALI_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Enable FDIE interrupts */
        __LL_DALI_IT_ENABLE(Instance, DALI_IT_FDIE);
    }

    /* Return function status */
    return status;
}

/**
  * @}
  */


/** @defgroup DALI_LL_Exported_Functions_Interrupt DALI Initerrupt management
  * @brief    DALI Initerrupt management
@verbatim
  ===============================================================================
                          ##### Initerrupt management #####
  ===============================================================================
  [..]
      This section provides DALI interrupt handler and callback functions.
@endverbatim
  * @{
  */

/**
  * @brief   This function handles DALI interrupts requests.
  * @param   Instance DALI peripheral
  * @return  None
  */
void LL_DALI_IRQHandler(DALI_TypeDef *Instance)
{
    if ((__LL_DALI_IT_SOURCE_CHECK(Instance, DALI_IT_FDIE) != RESET) &&
        (__LL_DALI_PENDING_FLAG_GET(Instance, DALI_FLAG_FDIF) != RESET)) {

        /* Disable and clear interrupt */
        __LL_DALI_IT_DISABLE(Instance, DALI_IT_FDIE);
        __LL_DALI_PENDING_FLAG_CLEAR(Instance, DALI_FLAG_FDIF);

        if (__LL_DALI_PENDING_FLAG_GET(Instance, DALI_FLAG_FEIF) != RESET) {
            __LL_DALI_PENDING_FLAG_CLEAR(Instance, DALI_FLAG_FEIF);

            /* Error detected */
            if (READ_BIT(Instance->CR, DALI_CR_MODE_Msk) != DALI_MODE_SLAVE) {
                LL_DALI_MstrTransmitErrorCallback(Instance);
            } else {
                LL_DALI_SlvReceiveErrorCallback(Instance);
            }
        } else {

            /* Transmission complete */
            if (READ_BIT(Instance->CR, DALI_CR_MODE_Msk) != DALI_MODE_SLAVE) {
                LL_DALI_MstrTransmitDoneCallback(Instance);
            } else {
                LL_DALI_SlvReceiveDoneCallback(Instance);
            }
        }
    }

    if ((__LL_DALI_IT_SOURCE_CHECK(Instance, DALI_IT_BDIE) != RESET) &&
        (__LL_DALI_PENDING_FLAG_GET(Instance, DALI_FLAG_BDIF) != RESET)) {

        /* Disable and clear interrupt */
        __LL_DALI_IT_DISABLE(Instance, DALI_IT_BDIE);
        __LL_DALI_PENDING_FLAG_CLEAR(Instance, DALI_FLAG_BDIF);

        if (__LL_DALI_PENDING_FLAG_GET(Instance, DALI_FLAG_BEIF) != RESET) {
            __LL_DALI_PENDING_FLAG_CLEAR(Instance, DALI_FLAG_BEIF);

            /* Error detected */
            if (READ_BIT(Instance->CR, DALI_CR_MODE_Msk) != DALI_MODE_SLAVE) {
                LL_DALI_MstrRecviveErrorCallback(Instance);
            } else {
                LL_DALI_SlvTransmitErrorCallback(Instance);
            }
        } else {
            /* Transmission complete */
            if (READ_BIT(Instance->CR, DALI_CR_MODE_Msk) != DALI_MODE_SLAVE) {
                LL_DALI_MstrRecviveDoneCallback(Instance);
            } else {
                LL_DALI_SlvTransmitDoneCallback(Instance);
            }
        }
    }
}

/**
  * @brief  DALI Master receive backward frame done callback
  *         Use __LL_DALI_MSTR_READ_BACKWARD_DATA() to get the backword data
  * @param  Instance DALI peripheral
  * @return None
  */
__WEAK void LL_DALI_MstrRecviveDoneCallback(DALI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_DALI_MstrRecviveDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  DALI Master receive backward frame failed callback
  * @param  Instance DALI peripheral
  * @return None
  */
__WEAK void LL_DALI_MstrRecviveErrorCallback(DALI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_DALI_MstrRecviveErrorCallback could be implemented in the user file
     */
}

/**
  * @brief  DALI Master transmit forward frame done callback
  * @param  Instance DALI peripheral
  * @return None
  */
__WEAK void LL_DALI_MstrTransmitDoneCallback(DALI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_DALI_MstrTransmitDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  DALI Master transmit forward frame failed callback
  * @param  Instance DALI peripheral
  * @return None
  */
__WEAK void LL_DALI_MstrTransmitErrorCallback(DALI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_DALI_MstrTransmitErrorCallback could be implemented in the user file
     */
}

/**
  * @brief  DALI Slave receive forward frame done callback
  *         Use __LL_DALI_SLV_READ_FORWARD_DATA() to get the forward data
  * @param  Instance DALI peripheral
  * @return None
  */
__WEAK void LL_DALI_SlvReceiveDoneCallback(DALI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_DALI_SlvReceiveDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  DALI Slave receive forward frame failed callback
  * @param  Instance DALI peripheral
  * @return None
  */
__WEAK void LL_DALI_SlvReceiveErrorCallback(DALI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_DALI_SlvReceiveErrorCallback could be implemented in the user file
     */
}

/**
  * @brief  DALI Slave transmit backward frame done callback
  * @param  Instance DALI peripheral
  * @return None
  */
__WEAK void LL_DALI_SlvTransmitDoneCallback(DALI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_DALI_SlvTransmitDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  DALI Slave transmit backward frame failed callback
  * @param  Instance DALI peripheral
  * @return None
  */
__WEAK void LL_DALI_SlvTransmitErrorCallback(DALI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_DALI_SlvTransmitErrorCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


#endif /* LL_DALI_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

