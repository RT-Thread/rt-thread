/**************************************************************************//**
 * @file     nu_plm.h
 * @version  V3.00
 * @brief    Product life cycle management
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_PLM_H__
#define __NU_PLM_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup PLM_Driver PLM Driver
  @{
*/

/** @addtogroup PLM_EXPORTED_CONSTANTS PLM Exported Constants
  @{
*/

typedef enum
{
    PLM_VENDOR = 0,
    PLM_OEM = 1,
    PLM_DEPLOYED = 3,
    PLM_RMA = 7
} PLM_STAGE_T;

#define PLM_VCODE   (0x475A0000ul)  /*!< The key code for PLM_CTL write. */

/**@}*/ /* end of group FVC_EXPORTED_CONSTANTS */


/** @addtogroup FVC_EXPORTED_FUNCTIONS FVC Exported Functions
  @{
*/


/**
  * @brief      Get product life-cycle stage
  * @return     Current stage of PLM
  * @details    This function is used to Get PLM stage.
  */
#define PLM_GetStage()  (PLM->STS & PLM_STS_STAGE_Msk)


/**
  * @brief      Set product life-cycle stage
  * @param[in]  stage   Product life-cycle stage. It could be:
  *                     \ref PLM_VENDOR
  *                     \ref PLM_OEM
  *                     \ref PLM_DEPLOYED
  *                     \ref PLM_RMA
  * @retval     0   Successful
  * @retval     -1  Failed
  * @details    This function is used to set PLM stage. It could be only be VENDOR, OEM, DEPLOYED and RMA.
  *             The setting of PLM cannot be rollback.
  */
__STATIC_INLINE int32_t PLM_SetStage(PLM_STAGE_T stage)
{

    /* Do nothing when stage is not changed */
    if(PLM_GetStage() == stage)
        return 0;

    PLM->CTL = PLM_VCODE | (stage);

    /* The dirty flag should be set when PLM stage set successfully. */
    if(PLM->STS & PLM_STS_DIRTY_Msk)
        return -1;

    return 0;
}

/**@}*/ /* end of group PLM_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group PLM_Driver */

/**@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_PLM_H__ */

