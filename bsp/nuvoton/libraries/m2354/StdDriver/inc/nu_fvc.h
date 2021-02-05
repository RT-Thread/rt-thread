/**************************************************************************//**
 * @file     nu_fvc.h
 * @version  V3.00
 * @brief    Firmware Version Counter Driver Header
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_FVC_H__
#define __NU_FVC_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup FVC_Driver FVC Driver
  @{
*/

/** @addtogroup FVC_EXPORTED_CONSTANTS FVC Exported Constants
  @{
*/

#define FVC_VCODE   (0x77100000ul)  /*!< The key code for FVC_CTL write. */

/**@}*/ /* end of group FVC_EXPORTED_CONSTANTS */


/** @addtogroup FVC_EXPORTED_FUNCTIONS FVC Exported Functions
  @{
*/

int32_t FVC_Open(void);
void FVC_EnableMonotone(void);
int32_t FVC_SetNVC(uint32_t u32NvcIdx, uint32_t u32Cnt);
int32_t FVC_GetNVC(uint32_t u32NvcIdx);


/**@}*/ /* end of group FVC_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group FVC_Driver */

/**@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_FVC_H__ */
