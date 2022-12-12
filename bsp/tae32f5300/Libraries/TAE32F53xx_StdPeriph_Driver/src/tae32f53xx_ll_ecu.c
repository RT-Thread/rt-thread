/**
  ******************************************************************************
  * @file    tae32f53xx_ll_ecu.c
  * @author  MCD Application Team
  * @brief   ECU LL module driver
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


#define DBG_TAG             "ECU LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup ECU_LL ECU LL
  * @brief    ECU LL module driver
  * @{
  */

#ifdef LL_ECU_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup ECU_LL_Exported_Functions ECU LL Exported Functions
  * @brief    ECU LL Exported Functions
  * @{
  */

/** @defgroup ECU_LL_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
  [..]
    This section provides functions allowing to initialize and de-initialize the ECU
    to be ready for use.

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the ECU peripheral according to the specified parameters in the ECU_Init.
  * @param  ECU_Init: pointer to a ECU_InitTypeDef structure that contains
  *         the configuration information for the specified ECU peripheral.
  * @return status of the initialization
  */
LL_StatusETypeDef LL_ECU_Init(ECU_TypeDef *Instance, ECU_InitTypeDef *ECU_Init)
{
    /*hardware level Initializes*/
    LL_ECU_MspInit(Instance);
    /*check paramter*/
    assert_param(IS_ECU_MODULE(ECU_Init->ModuleEnable));
    assert_param(IS_ECU_AVERAGE(ECU_Init->AverageSel));
    assert_param(IS_ECU_ACSFT(ECU_Init->ACLeftShift));
    assert_param(IS_ECU_APSFT(ECU_Init->APRightShift));
    assert_param(IS_ECU_DATSEL(ECU_Init->DataSel));
    assert_param(IS_ECU_CRSSEL(ECU_Init->CrossZeroSel));

    if (ECU_Init->ModuleEnable == ENABLE) {
        /*ECU control register, enable mdule */
        if (ECU_Init->InterruptEn == ENABLE) {
            SET_BIT(Instance->CON, ECU_CON_ENABLE | ECU_CON_INTEN);
        } else {
            SET_BIT(Instance->CON, ECU_CON_ENABLE);
        }

        /*Configure averages the data results*/
        /*Configure The right shift number of power results and
         *the left shift number of active power results are configured.*/
        MODIFY_REG(Instance->CON,
                   ECU_CON_AVGSEL
                   | ECU_CON_APSFT
                   | ECU_CON_ACSFT,
                   ECU_Init->AverageSel
                   | ECU_Init->APRightShift
                   | ECU_Init->ACLeftShift
                  );
        /*Configure the corresponding event selection bits*/
        MODIFY_REG(Instance->PRC,
                   ECU_PRC_CRSSEL
                   | ECU_PRC_ADRSEL
                   | ECU_PRC_DATSEL,
                   ECU_Init->CrossZeroSel
                   | ECU_Init->AddressSel
                   | ECU_Init->DataSel
                  );
        /*Configure cache voltage and current data storage addresses and offset addresses*/
        /*Configure voltage start address*/
        MODIFY_REG(Instance->V_ADDR1, ECU_V_ADDR1_STADDR, ECU_Init->VStartAddr);
        /*Configure voltage offset address*/
        MODIFY_REG(Instance->V_ADDR2, ECU_V_ADDR2_OFADDR, ECU_Init->VOffsetAddr);
        /*Configure current start address*/
        MODIFY_REG(Instance->I_ADDR1, ECU_I_ADDR1_STADDR, ECU_Init->IStartAddr);
        /*Configure current offset address*/
        MODIFY_REG(Instance->I_ADDR2, ECU_I_ADDR2_OFADDR, ECU_Init->IOffsetAddr);

        return LL_OK;
    } else {
        return LL_ERROR;
    }
}

/**
  * @brief  De-initializes the ECU peripheral registers to their default reset values.
  * @return status of the de-initialization
  */
LL_StatusETypeDef LL_ECU_DeInit(ECU_TypeDef *Instance)
{
    /*Get the current working status of the ECU*/
    if (__LL_ECU_GET_STA(Instance)) {
        /*Disable the module*/
        __LL_ECU_MODULE_DISABLE(Instance);
    }

    /*Reset configuration register,Sets the value of the register to restore the default value */
    MODIFY_REG(Instance->CON,
               ECU_CON_INTEN | ECU_CON_INT | ECU_CON_AVGSEL | ECU_CON_APSFT | ECU_CON_ACSFT,
               (0x8U << ECU_CON_APSFT_Pos) | (0x8U << ECU_CON_ACSFT_Pos)
              );
    /*Reset the event selection register*/
    CLEAR_BIT(Instance->PRC, ECU_PRC_DATSEL | ECU_PRC_ADRSEL | ECU_PRC_CRSSEL);
    /*Clears the input square root data*/
    CLEAR_REG(Instance->SQRT_IN);
    /*Clear the starting address of the voltage buffer*/
    CLEAR_BIT(Instance->V_ADDR1, ECU_V_ADDR1_STADDR);
    /*Clear the offset address of the voltage buffer*/
    CLEAR_BIT(Instance->V_ADDR2, ECU_V_ADDR2_OFADDR);
    /*Clear the starting address of the current buffer*/
    CLEAR_BIT(Instance->I_ADDR1, ECU_I_ADDR1_STADDR);
    /*Clear the offset address of the current buffer*/
    CLEAR_BIT(Instance->I_ADDR2, ECU_I_ADDR2_OFADDR);

    return LL_OK;
}

/**
  * @brief  Initializes the ECU MSP.
  * @param  ECU ECU instance
  * @return None
  */
__WEAK void LL_ECU_MspInit(ECU_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ECU_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the ECU MSP
  * @param  ECU ECU instance
  * @return None
  */
__WEAK void LL_ECU_MspDeInit(ECU_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ECU_MspDeInit could be implemented in the user file
     */
}
/**
  * @}
  */


/** @defgroup ECU_LL_Exported_Functions_Group2 ECU Read calulate result operation functions
 *  @brief    ECU Read calulate result operation functions
 *
@verbatim
 ===============================================================================
                       ##### Read result value functions #####
 ===============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the ECUs:
    (+) Read the ECU SQRT_OUT value
    (+) Write the ECU SQRT_IN value
  @note For the above operation of reading registers, please determine whether the mark of completion of calculation
        is set before reading, or try to read data in the interrupt
@endverbatim
  * @{
  */

/**
  * @brief  Set the data input that you want to take the square root of
  * @param  __VALUE__ input data
  * @return None
  */
void LL_ECU_WriteSqrtInData(ECU_TypeDef *Instance, uint32_t SqrtValue)
{
    /*Check whether the last square root calculation was completed.*/
    if (__LL_ECU_SQRT_DONE_FLAG(Instance)) {
        /*If not, wait for the flag to clear*/
        while (__LL_ECU_SQRT_DONE_FLAG(Instance));
    }

    /*If complete, write the data you need to take the square root of*/
    MODIFY_REG(Instance->SQRT_IN, ECU_SQRT_INDATA, SqrtValue);
    /*Square root enable*/
    __LL_ECU_SQRT_ENABLE(Instance);
}

/**
  * @brief  Get the result of square root data
  * @param  Instance ECU instance
  * @return The result of the square root of the input data
  */
uint32_t LL_ECU_ReadSqrtOutData(ECU_TypeDef *Instance)
{
    /*Check whether the last square root calculation was completed.*/
    if (__LL_ECU_SQRT_DONE_FLAG(Instance)) {
        /*If not, wait for the flag to clear*/
        while (__LL_ECU_SQRT_DONE_FLAG(Instance));
    }

    /*If completed, the result of the operation is read*/
    return (uint32_t)READ_REG(Instance->SQRT_OUT);
}
/**
  * @}
  */


/** @defgroup ECU_LL_Exported_Functions_Interrupt ECU IRQ handler management
  * @brief    ECU IRQ handler management
  *
@verbatim
  ==============================================================================
                        ##### IRQ handler management #####
  ==============================================================================
  [..]
    This section provides ECU IRQ handler function.

@endverbatim
  * @{
  */

/**
  * @brief  This function handles ECU interrupts requests.
  * @param  ECU ECU instance
  * @return None
  */
void LL_ECU_IRQHandler(ECU_TypeDef *Instance)
{
    if (__LL_ECU_DONE_GET_IT(Instance) && __LL_ECU_DONE_GET_FLAG(Instance)) {
        __LL_ECU_DONE_CLEAR_FLAG(Instance);

        /*Handle something*/
        LL_ECU_CalDoneCallback(Instance);
    }
}

/**
  * @brief  ECU parameters calculate completed detection callback.
  * @return None
  */
__WEAK void LL_ECU_CalDoneCallback(ECU_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_ECU_CalDoneCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


#endif /* LL_ECU_MODULE_ENABLE */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

