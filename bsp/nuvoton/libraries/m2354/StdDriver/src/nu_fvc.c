/**************************************************************************//**
 * @file     fvc.c
 * @version  V3.00
 * @brief    FVC driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup FVC_Driver FVC Driver
  @{
*/


/** @addtogroup FVC_EXPORTED_FUNCTIONS FVC Exported Functions
  @{
*/


/**
  * @brief      Initial firmware version counter
  * @param      None
  * @retval     0       Successful
  * @retval     -1      Failed
  * @details    FVC needs to be initialed before using it. This function is used to initial the FVC.
  *
  */
int32_t FVC_Open(void)
{
    int32_t timeout;

    /* Just return when it is ready */
    if(FVC->STS & FVC_STS_RDY_Msk)
        return 0;

    /* Init FVC */
    FVC->CTL = FVC_VCODE | FVC_CTL_INIT_Msk;

    /* Waiting for ready */
    timeout = 0x100000;
    while((FVC->STS & FVC_STS_RDY_Msk) == 0)
    {
        if(timeout-- < 0)
        {
            /* Init timeout. */
            return -1;
        }
    }

    return 0;
}



/**
  * @brief      Enable anti version rollback
  * @details    FVC can limit the version number to be increased only to avoid version rollback.
  *             This function is used to enable it.
  *
  */
void FVC_EnableMonotone(void)
{
    FVC->CTL = FVC_VCODE | FVC_CTL_MONOEN_Msk;
    /* Waiting if FVC is in busy */
    while(FVC->STS & FVC->STS & FVC_STS_BUSY_Msk) {}
}

/**
  * @brief      Set non-volatile version counter
  * @param[in]  u32NvcIdx    Index number of non-volatile version counter. It could be 0, 1, 4, 5.
  * @param[in]  u32Cnt       Version Number. It could be 0~63 for u32NvcIdx=0, 1, and 0~255 for u32NvcIdx=4, 5
  * @retval     0       Successful
  * @retval     -1      Failed
  * @details    Set non-volatile version counter
  *
  */
int32_t FVC_SetNVC(uint32_t u32NvcIdx, uint32_t u32Cnt)
{
    if(u32NvcIdx < 2)
    {
        if(u32Cnt >= 64)
            /* The counter value is out of range */
            return -1;
    }
    else if(u32NvcIdx < 4)
        return -1;
    else if(u32NvcIdx < 6)
    {
        /* The counter value is out of range */
        if(u32Cnt >= 256)
            /* The counter value is out of range */
            return -1;
    }
    else
        return -1;

    FVC->NVC[u32NvcIdx] = (FVC->NVC[u32NvcIdx] << 16) | (u32Cnt & 0x3ful);
    while(FVC->STS & FVC_STS_BUSY_Msk) {}
    if(FVC->NVC[u32NvcIdx] != u32Cnt)
        return -1;

    return 0;
}


/**
  * @brief      Get non-volatile version counter
  * @param[in]  u32NvcIdx    Index number of non-volatile version counter. It could be 0, 1, 4, 5.
  * @retval     the version counter
  * @retval     -1      Failed
  * @details    Get non-volatile version counter
  *
  */
int32_t FVC_GetNVC(uint32_t u32NvcIdx)
{
    if((u32NvcIdx == 2) || (u32NvcIdx == 3) || (u32NvcIdx > 5))
        return -1;

    return FVC->NVC[u32NvcIdx];
}

/**@}*/ /* end of group FVC_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group FVC_Driver */

/**@}*/ /* end of group Standard_Driver */

