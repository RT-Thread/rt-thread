/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_IWDG_H__
#define __HAL_IWDG_H__

#include "hal_common.h"

/*!
 * @addtogroup IWDG
 * @{
 */

/*!
 * @brief IWDG driver version number.
 */
#define IWDG_DRIVER_VERSION 0u /*!< IWDG_0. */

/*!
 * @brief IWDG key values
 */
#define IWDG_KEY_ENABLE  0xCCCC /*!< IWDG Peripheral Enable . */
#define IWDG_KEY_RELOAD  0xAAAA /*!< IWDG Reload Counter Enable. */
#define IWDG_KEY_UNLOCK  0x5555 /*!< IWDG KR Write Access Enable*/

/*!
 * @addtogroup IWDG_STATUS
 * @{
 */
#define IWDG_STATUS_RELOAD_UPDATE     IWDG_SR_RVU_MASK           /*!< Status flag when IWDG counter reload value update, can not be cleared. */
#define IWDG_STATUS_PRESCALER_UPDATE  IWDG_SR_PVU_MASK           /*!< Status flag when IWDG prescaler value update, can not be cleared. */
#define IWDG_STATUS_ALMOST_TIMEOUT    IWDG_SR_IVU_MASK           /*!< Status flag when IWDG almost timeout. */
/*!
 * @}
 */

/*!
 * @addtogroup IWDG_INT
 * @{
 */
#define IWDG_INT_ALMOST_TIMEOUT  IWDG_CR_IRQSEL_MASK           /*!< IWDG Interrupt: Select IWDG interrupt method */
/*!
 * @}
 */

/*!
 * @brief IWDG prescaler type.
 *
 * Select the prescaler of time base as the IWDG counter clock.
 */
typedef enum
{
    IWDG_Prescaler_4   = 0u, /*!< IWDG prescaler 4. */
    IWDG_Prescaler_8   = 1u, /*!< IWDG prescaler 8. */
    IWDG_Prescaler_16  = 2u, /*!< IWDG prescaler 16. */
    IWDG_Prescaler_32  = 3u, /*!< IWDG prescaler 32. */
    IWDG_Prescaler_64  = 4u, /*!< IWDG prescaler 64. */
    IWDG_Prescaler_128 = 5u, /*!< IWDG prescaler 128. */
    IWDG_Prescaler_256 = 6u, /*!< IWDG prescaler 256. */
} IWDG_Prescaler_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref IWDG_Init() to initialize the IWDG module.
 */
typedef struct
{
    IWDG_Prescaler_Type  Prescaler; /*!< Specify the IWDG counter time base division value. */
    uint32_t             Relaod;    /*!< Specify the IWDG counter reload value. */
} IWDG_Init_Type;

/*!
 * @brief Initialize the IWDG module.
 *
 * @param IWDGx IWDG instance.
 * @param init Pointer to the initialization structure. See to @ref IWDG_Init_Type.
 * @return None.
 */
void IWDG_Init(IWDG_Type * IWDGx, IWDG_Init_Type * init);

/*!
 * @brief Start the IWDG counter.
 *
 * Once IWDG counter is started, it cannot be stopped unless reset MCU.
 *
 * @param IWDGx IWDG instance.
 * @return None.
 */
void IWDG_Start(IWDG_Type * IWDGx);

/*!
 * @brief Get the current status flags of the IWDG module.
 *
 * @param IWDGx IWDG instance.
 * @return Status flags. See to @ref IWDG_STATUS.
 */
uint32_t IWDG_GetStatus(IWDG_Type * IWDGx);

/*!
 * @brief Clear the status flags of the IWDG module.
 *
 * @param IWDGx IWDG instance.
 * @param status Status flags. See to @ref IWDG_STATUS.
 * @return None.
 */
void IWDG_ClearStatus(IWDG_Type * IWDGx, uint32_t status);

/*!
 * @brief Do reload IWDG counter (i.e. "feed dog").
 *
 * @param IWDGx IWDG instance.
 * @return None.
 */
void IWDG_DoReload(IWDG_Type * IWDGx);

/*!
 * @brief Enable interrupts of the IWDG module.
 *
 * @param IWDGx IWDG instance.
 * @param interrupts Interrupt code masks. See to @ref IWDG_INT.
 * @param enable 'true' to enable the indicated interrupts, 'false' has no effect.
 * @return None.
 */
void IWDG_EnableInterrupts(IWDG_Type * IWDGx, uint32_t interrupts, bool enable);

/*!
 *@}
 */

#endif /* __HAL_IWDG_H__ */
