/**************************************************************************//**
 * @file     dpm.c
 * @version  V3.00
 * @brief    Debug Protection Mechanism (DPM) driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup DPM_Driver DPM Driver
  @{
*/

/** @addtogroup DPM_EXPORTED_FUNCTIONS DPM Exported Functions
  @{
*/

/**
  * @brief      Set Debug Disable
  * @param[in]  u32dpm  The pointer of the specified DPM module
  *                     - \ref SECURE_DPM
  *                     - \ref NONSECURE_DPM
  * @return     None
  * @details    This macro sets Secure or Non-secure DPM debug disable.
  *             The debug disable function works after reset (chip reset or pin reset).
  */
void DPM_SetDebugDisable(uint32_t u32dpm)
{
    DPM_T *dpm;

    if(__PC()&NS_OFFSET) dpm = DPM_NS;
    else dpm = DPM;

    if(u32dpm == SECURE_DPM) /* Secure DPM */
    {
        while(dpm->STS & DPM_STS_BUSY_Msk);
        dpm->CTL = (DPM->CTL & (~DPM_CTL_WVCODE_Msk)) | (DPM_CTL_WVCODE | DPM_CTL_DBGDIS_Msk);
    }
    else    /* Non-secure DPM */
    {
        while(dpm->NSSTS & DPM_NSSTS_BUSY_Msk);
        dpm->NSCTL = (dpm->NSCTL & (~DPM_NSCTL_WVCODE_Msk)) | (DPM_NSCTL_WVCODE | DPM_NSCTL_DBGDIS_Msk);
    }
}

/**
  * @brief      Set Debug Lock
  * @param[in]  u32dpm  Select DPM module. Valid values are:
  *                     - \ref SECURE_DPM
  *                     - \ref NONSECURE_DPM
  * @return     None
  * @details    This macro sets Secure or Non-secure DPM debug lock.
  *             The debug lock function works after reset (chip reset or pin reset).
  */
void DPM_SetDebugLock(uint32_t u32dpm)
{
    DPM_T *dpm;

    if(__PC()&NS_OFFSET) dpm = DPM_NS;
    else dpm = DPM;

    if(u32dpm == SECURE_DPM) /* Secure DPM */
    {
        while(dpm->STS & DPM_STS_BUSY_Msk);
        dpm->CTL = (dpm->CTL & (~DPM_CTL_WVCODE_Msk)) | (DPM_CTL_WVCODE | DPM_CTL_LOCK_Msk);
    }
    else    /* Non-secure DPM */
    {
        while(dpm->NSSTS & DPM_NSSTS_BUSY_Msk);
        dpm->NSCTL = (dpm->NSCTL & (~DPM_NSCTL_WVCODE_Msk)) | (DPM_NSCTL_WVCODE | DPM_NSCTL_LOCK_Msk);
    }
}

/**
  * @brief      Get Debug Disable
  * @param[in]  u32dpm  Select DPM module. Valid values are:
  *                     - \ref SECURE_DPM
  *                     - \ref NONSECURE_DPM
  * @retval     0   Debug is not in disable status
  * @retval     1   Debug is in disable status
  * @details    This macro gets Secure or Non-secure DPM debug disable status.
  *             If Secure debug is disabled, debugger cannot access Secure region and can access Non-secure region only.
  *             If Non-secure debug is disabled, debugger cannot access all Secure and Non-secure region.
  */
uint32_t DPM_GetDebugDisable(uint32_t u32dpm)
{
    uint32_t u32RetVal = 0;
    DPM_T *dpm;

    if(__PC()&NS_OFFSET) dpm = DPM_NS;
    else dpm = DPM;

    if(u32dpm == SECURE_DPM) /* Secure DPM */
    {
        while(dpm->STS & DPM_STS_BUSY_Msk);
        u32RetVal = (dpm->STS & DPM_STS_DBGDIS_Msk) >> DPM_STS_DBGDIS_Pos;
    }
    else    /* Non-secure DPM */
    {
        while(dpm->NSSTS & DPM_NSSTS_BUSY_Msk);
        u32RetVal = (dpm->NSSTS & DPM_NSSTS_DBGDIS_Msk) >> DPM_NSSTS_DBGDIS_Pos;
    }

    return u32RetVal;
}

/**
  * @brief      Get Debug Lock
  * @param[in]  u32dpm  Select DPM module. Valid values are:
  *                     - \ref SECURE_DPM
  *                     - \ref NONSECURE_DPM
  * @retval     0   Debug is not in lock status
  * @retval     1   Debug is in lock status
  * @details    This macro gets Secure or Non-secure DPM debug disable status.
  *             If Secure debug is locked, debugger cannot access Secure region and can access Non-secure region only.
  *             If Non-secure debug is locked, debugger cannot access all Secure and Non-secure region.
  */
uint32_t DPM_GetDebugLock(uint32_t u32dpm)
{
    uint32_t u32RetVal = 0;
    DPM_T *dpm;

    if(__PC()&NS_OFFSET) dpm = DPM_NS;
    else dpm = DPM;

    if(u32dpm == SECURE_DPM) /* Secure DPM */
    {
        while(dpm->STS & DPM_STS_BUSY_Msk);
        u32RetVal = (dpm->STS & DPM_STS_LOCK_Msk) >> DPM_STS_LOCK_Pos;
    }
    else                    /* Non-secure DPM */
    {
        while(dpm->NSSTS & DPM_NSSTS_BUSY_Msk);
        u32RetVal = (dpm->NSSTS & DPM_NSSTS_LOCK_Msk) >> DPM_NSSTS_LOCK_Pos;
    }

    return u32RetVal;
}

/**
  * @brief      Update DPM Password
  * @param[in]  u32dpm        Select DPM module. Valid values are:
  *                           - \ref SECURE_DPM
  *                           - \ref NONSECURE_DPM
  * @param[in]  au32Password  Password length is 256 bits.
  * @retval     0   No password is updated. The password update count has reached the maximum value.
  * @retval     1   Password update is successful.
  * @details    This macro updates Secure or Non-secure DPM password.
  */
uint32_t DPM_SetPasswordUpdate(uint32_t u32dpm, uint32_t au32Pwd[])
{
    uint32_t u32i, u32RetVal = 0;
    DPM_T *dpm;

    if(__PC()&NS_OFFSET) dpm = DPM_NS;
    else dpm = DPM;

    if(u32dpm == SECURE_DPM) /* Secure DPM */
    {
        /* Set Secure DPM password */
        for(u32i = 0; u32i < 4; u32i++)
        {
            while(dpm->STS & DPM_STS_BUSY_Msk);
            dpm->SPW[u32i] = au32Pwd[u32i];
        }

        /* Set Secure DPM password update */
        while(dpm->STS & DPM_STS_BUSY_Msk);
        dpm->CTL = (dpm->CTL & (~DPM_CTL_WVCODE_Msk)) | (DPM_CTL_WVCODE | DPM_CTL_PWUPD_Msk);

        /* Check Secure DPM password update flag */
        while(dpm->STS & DPM_STS_BUSY_Msk);
        u32RetVal = (dpm->STS & DPM_STS_PWUOK_Msk) >> DPM_STS_PWUOK_Pos;

        /* Clear Secure DPM password update flag */
        if(u32RetVal) dpm->STS = DPM_STS_PWUOK_Msk;
    }
    else    /* Non-secure DPM */
    {
        /* Set Non-secure DPM password */
        for(u32i = 0; u32i < 4; u32i++)
        {
            while(dpm->NSSTS & DPM_NSSTS_BUSY_Msk);
            dpm->NSPW[u32i] = au32Pwd[u32i];
        }

        /* Set Non-secure DPM password update */
        while(dpm->NSSTS & DPM_NSSTS_BUSY_Msk);
        dpm->NSCTL = (dpm->NSCTL & (~DPM_CTL_WVCODE_Msk)) | (DPM_CTL_WVCODE | DPM_NSCTL_PWUPD_Msk);

        /* Check Non-secure DPM password update flag */
        while(dpm->NSSTS & DPM_NSSTS_BUSY_Msk);
        u32RetVal = (dpm->NSSTS & DPM_NSSTS_PWUOK_Msk) >> DPM_NSSTS_PWUOK_Pos;

        /* Clear Non-secure DPM password update flag */
        if(u32RetVal) dpm->NSSTS = DPM_NSSTS_PWUOK_Msk;
    }

    return u32RetVal;
}

/**
  * @brief      Compare DPM Password
  * @param[in]  u32dpm  Select DPM module. Valid values are:
  *                     - \ref SECURE_DPM
  *                     - \ref NONSECURE_DPM
  * @retval     0   The password comparison can be proccessed.
  * @retval     1   No more password comparison can be proccessed. \n
  *                 The password comparison fail times has reached the maximum value.
  * @details    This macro sets Secure or Non-secure DPM password comparison. \n
  *             The comparison result is checked by DPM_GetPasswordErrorFlag().
  */
uint32_t DPM_SetPasswordCompare(uint32_t u32dpm, uint32_t au32Pwd[])
{
    uint32_t u32i, u32RetVal = 0;
    DPM_T *dpm;

    if(__PC()&NS_OFFSET) dpm = DPM_NS;
    else dpm = DPM;

    if(u32dpm == SECURE_DPM) /* Secure DPM */
    {
        /* Check Secure DPM password compare fail times maximum flag */
        while(dpm->STS & DPM_STS_BUSY_Msk);
        if(dpm->STS & DPM_STS_PWFMAX_Msk)
        {
            u32RetVal = 1;
        }
        else
        {
            /* Set Secure DPM password */
            for(u32i = 0; u32i < 4; u32i++)
            {
                while(dpm->STS & DPM_STS_BUSY_Msk);
                dpm->SPW[u32i] = au32Pwd[u32i];
            }

            /* Set Secure DPM password cpmpare */
            while(dpm->STS & DPM_STS_BUSY_Msk);
            dpm->CTL = (dpm->CTL & (~DPM_CTL_WVCODE_Msk)) | (DPM_CTL_WVCODE | DPM_CTL_PWCMP_Msk);
        }
    }
    else    /* Non-secure DPM */
    {
        /* Check Non-secure DPM password compare fail times maximum flag */
        while(dpm->NSSTS & DPM_NSSTS_BUSY_Msk);
        if(dpm->NSSTS & DPM_NSSTS_PWFMAX_Msk)
        {
            u32RetVal = 1;
        }
        else
        {
            /* Set Non-secure DPM password */
            for(u32i = 0; u32i < 4; u32i++)
            {
                while(dpm->NSSTS & DPM_NSSTS_BUSY_Msk);
                dpm->NSPW[u32i] = au32Pwd[u32i];
            }

            /* Set Non-secure DPM password compare */
            while(dpm->NSSTS & DPM_NSSTS_BUSY_Msk);
            dpm->NSCTL = (dpm->NSCTL & (~DPM_NSCTL_WVCODE_Msk)) | (DPM_NSCTL_WVCODE | DPM_NSCTL_PWCMP_Msk);
        }
    }

    return u32RetVal;
}

/**
  * @brief      Get DPM Password Error Flag
  * @param[in]  u32dpm        Select DPM module. Valid values are:
  *                           - \ref SECURE_DPM
  *                           - \ref NONSECURE_DPM
  * @return     Specified DPM module password compare error flag.
  * @details    This macro returns Secure or Non-secure DPM password compare error flag.
  */
uint32_t DPM_GetPasswordErrorFlag(uint32_t u32dpm)
{
    uint32_t u32RetVal = 0;
    DPM_T *dpm;

    if(__PC()&NS_OFFSET) dpm = DPM_NS;
    else dpm = DPM;

    if(u32dpm == SECURE_DPM) /* Secure DPM */
    {
        /* Check Secure DPM password compare error flag */
        while(dpm->STS & DPM_STS_BUSY_Msk);
        u32RetVal = (dpm->STS & DPM_STS_PWCERR_Msk) >> DPM_STS_PWCERR_Pos;
    }
    else    /* Non-secure DPM */
    {
        /* Check Non-secure DPM password compare error flag */
        while(dpm->NSSTS & DPM_NSSTS_BUSY_Msk);
        u32RetVal = (dpm->NSSTS & DPM_NSSTS_PWCERR_Msk) >> DPM_NSSTS_PWCERR_Pos;
    }

    return u32RetVal;
}

/**
  * @brief      Get DPM Interrupt Flag
  * @param      None
  * @return     Secure DPM interrupt flag.
  * @details    This macro returns Secure DPM interrupt flag.
  *             Secure DPM interrupt flag includes Secure and Non-secure DPM password compare error flag.
  *             This macro is for Secure DPM and Secure region only.
  */
uint32_t DPM_GetIntFlag(void)
{
    while(DPM->STS & DPM_STS_BUSY_Msk);
    return (DPM->STS & DPM_STS_INT_Msk) >> DPM_STS_INT_Pos;
}


/**
  * @brief      Clear DPM Password Error Flag
  * @param[in]  u32dpm        Select DPM module. Valid values are:
  *                           - \ref SECURE_DPM
  *                           - \ref NONSECURE_DPM
  * @return     Specified DPM module interrupt flag.
  * @details    This macro clears Secure or Non-secure DPM password compare error flag.
  */
void DPM_ClearPasswordErrorFlag(uint32_t u32dpm)
{
    DPM_T *dpm;

    if(__PC()&NS_OFFSET) dpm = DPM_NS;
    else dpm = DPM;

    if(u32dpm == SECURE_DPM) /* Secure DPM */
    {
        while(dpm->STS & DPM_STS_BUSY_Msk);
        dpm->STS = DPM_STS_PWCERR_Msk;
    }
    else    /* Non-secure DPM */
    {
        while(dpm->NSSTS & DPM_NSSTS_BUSY_Msk);
        dpm->NSSTS = DPM_NSSTS_PWCERR_Msk;
    }
}

/**
  * @brief      Enable Debugger Write Access
  * @param[in]  u32dpm        Select DPM module. Valid values are:
  *                           - \ref SECURE_DPM
  *                           - \ref NONSECURE_DPM
  * @return     None.
  * @details    This macro enables external debugger to write Secure or Non-secure DPM registers.
  */
void DPM_EnableDebuggerWriteAccess(uint32_t u32dpm)
{
    DPM_T *dpm;

    if(__PC()&NS_OFFSET) dpm = DPM_NS;
    else dpm = DPM;

    if(u32dpm == SECURE_DPM) /* Secure DPM */
    {
        while(dpm->STS & DPM_STS_BUSY_Msk);
        dpm->CTL = (dpm->CTL & (~(DPM_CTL_RVCODE_Msk | DPM_CTL_DACCWDIS_Msk))) | DPM_CTL_WVCODE;
    }
    else    /* Non-secure DPM */
    {
        while(dpm->NSSTS & DPM_NSSTS_BUSY_Msk);
        dpm->NSCTL = (dpm->NSCTL & (~(DPM_NSCTL_RVCODE_Msk | DPM_NSCTL_DACCWDIS_Msk))) | DPM_NSCTL_WVCODE;
    }
}

/**
  * @brief      Disable Debugger Write Access
  * @param[in]  u32dpm        Select DPM module. Valid values are:
  *                           - \ref SECURE_DPM
  *                           - \ref NONSECURE_DPM
  * @return     None.
  * @details    This macro disables external debugger to write Secure or Non-secure DPM registers.
  */
void DPM_DisableDebuggerWriteAccess(uint32_t u32dpm)
{
    DPM_T *dpm;

    if(__PC()&NS_OFFSET) dpm = DPM_NS;
    else dpm = DPM;

    if(u32dpm == SECURE_DPM) /* Secure DPM */
    {
        while(dpm->STS & DPM_STS_BUSY_Msk);
        dpm->CTL = (dpm->CTL & (~DPM_CTL_RVCODE_Msk)) | (DPM_CTL_WVCODE | DPM_CTL_DACCWDIS_Msk);
    }
    else    /* Non-secure DPM */
    {
        while(dpm->NSSTS & DPM_NSSTS_BUSY_Msk);
        dpm->NSCTL = (dpm->NSCTL & (~DPM_NSCTL_RVCODE_Msk)) | (DPM_NSCTL_WVCODE | DPM_NSCTL_DACCWDIS_Msk);
    }
}


/**@}*/ /* end of group DPM_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group DPM_Driver */

/**@}*/ /* end of group Standard_Driver */

