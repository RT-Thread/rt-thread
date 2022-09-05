/* hal_wwdg.h */

#ifndef __HAL_WWDG_H__
#define __HAL_WWDG_H__

/*!
 * @addtogroup WWDG
 * @{
 */

#include "hal_common.h"

/*!
 * @brief WWDG driver version number.
 */
#define WWDG_DRIVER_VERSION 0u /*!< WWDG_0. */

/*!
 * @brief The lower limit value of WWDG counter.
 */
#define WWDG_LOWER_LIMIT 0x40u /*!< If WWDG counter Below this value, WWDG will generate a reset request. */

/*!
 * @addtogroup WWDG_INT
 * @brief WWDG_STATUS mask codes
 * @{
 */
#define WWDG_INT_ALMOST_TIMEOUT WWDG_CFGR_EWI_MASK /*!< WWDG interrupt: Almost timeout. */
/*!
 * @}
 */

/*!
 * @addtogroup WWDG_STATUS
 * @brief WWDG_STATUS mask codes
 * @{
 */
#define WWDG_STATUS_ALMOST_TIMEOUT WWDG_SR_EWIF_MASK /*!< WWDG status: Almost timeout. */
/*!
 * @}
 */

/*!
 * @brief WWDG prescaler type.
 *
 * Select the prescaler of WWDG counter clock.
 */
typedef enum
{
    WWDG_Prescaler_1 = 0u, /*!< WWDG Prescaler 1. */
    WWDG_Prescaler_2 = 1u, /*!< WWDG Prescaler 2. */
    WWDG_Prescaler_4 = 2u, /*!< WWDG Prescaler 4. */
    WWDG_Prescaler_8 = 3u, /*!< WWDG Prescaler 8. */
} WWDG_Prescaler_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref WWDG_Init() to initialize the USB module.
 */
typedef struct
{
    WWDG_Prescaler_Type Prescaler;  /*!< Specify the WWDG counter prescaler. */
    uint32_t            UpperLimit; /*!< Specify the upperLimit, WWDG will generate a reset request if reload WWDG counter before the counter value greater than UpperLimit. */
} WWDG_Init_Type;

/*!
 * @brief Initialize the WWDG module.
 *
 * @param WWDGx WWDG instance.
 * @param init Pointer to the initialization structure. See to @ref WWDG_Init_Type.
 * @return None.
 */
void WWDG_Init(WWDG_Type * WWDGx, WWDG_Init_Type * init);

/*!
 * @brief Start counting.
 *
 * If the counter is started, it cannot be stoped unless reset MCU.
 *
 * @param WWDGx WWDG instance.
 * @return None.
 */
void WWDG_Start(WWDG_Type * WWDGx);

/*!
 * @brief Reolad WWDG counter (Feed dog).
 *
 * Reload WWDG counter to ensure that the counter value greater than WWDG_LOWER_LIMIT_VALUE and prevent generate a reset request.
 *
 * @param WWDGx WWDG instance.
 * @param value The value of reload WWDG counter, the value ranges from 0x40 to 0x7f.
 * @return None.
 */
void WWDG_Reload(WWDG_Type * WWDGx, uint32_t value);

/*!
 * @brief Enable interrupts of the WWDG module.
 *
 * @param WWDGx WWDG instance.
 * @param interrupts Interrupt code masks. See to @ref WWDG_INT.
 * @param enable 'true' to enable the indicated interrupts, 'false' has no effect.
 * @return None.
 */
void WWDG_EnableInterrupts(WWDG_Type * WWDGx, uint32_t interrupts, bool enable);

/*!
 * @brief Get the status flags of the WWDG module.
 *
 * @param WWDGx WWDG instance.
 * @return status flags. See to @ref WWDG_STATUS.
 */
uint32_t WWDG_GetStatus(WWDG_Type * WWDGx);

/*!
 * @brief Clear the status flags of the WWDG module.
 *
 * @param WWDGx WWDG instance.
 * @param status status flags. See to @ref WWDG_STATUS.
 * @return None.
 */
void WWDG_ClearStatus(WWDG_Type * WWDGx, uint32_t status);

/*!
 *@}
 */

#endif /* __HAL_WWDG_H__. */

/* EOF. */
