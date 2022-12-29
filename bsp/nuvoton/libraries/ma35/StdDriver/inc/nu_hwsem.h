/**************************************************************************//**
 * @file     nu_hwsem.h
 * @brief    HWSEM driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_HWSEM_H__
#define __NU_HWSEM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __has_include
    #if __has_include("rtconfig.h")
        #include "rtconfig.h"
    #endif
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup HWSEM_Driver HWSEM Driver
  @{
*/

/** @addtogroup HWSEM_EXPORTED_CONSTANTS HWSEM Exported Constants
  @{
*/
#define HWSEM_CNT               8ul     /*!<HWSEM count \hideinitializer */
#define HWSEM_NOLOCK            0ul     /*!<Semaphore is non-lock \hideinitializer */
#define HWSEM_LOCK_BY_A35       1ul     /*!<Semaphore lock by A35 \hideinitializer */
#define HWSEM_LOCK_BY_M4        2ul     /*!<Semaphore lock by M4 \hideinitializer */

#if defined(USE_MA35D1_SUBM)
#define HWSEM_LOCK_BY_OWNER     HWSEM_LOCK_BY_M4
#define INTSTS_CORE                         INTSTSM4
#define INTEN_CORE                          INTENM4
#else
#define HWSEM_LOCK_BY_OWNER     HWSEM_LOCK_BY_A35
#define INTSTS_CORE                         INTSTSA35
#define INTEN_CORE                          INTENA35
#endif
#define HWSEM_INTSTS_SEM0IF_Pos     0
#define HWSEM_INTSTS_SEM0IF_Msk     (1<<HWSEM_INTSTS_SEM0IF_Pos)
#define HWSEM_INTEN_SEM0IEN_Pos     0
#define HWSEM_INTEN_SEM0IEN_Msk     (1<<HWSEM_INTEN_SEM0IEN_Pos)

/*@}*/ /* end of group HWSEM_EXPORTED_CONSTANTS */


/** @addtogroup HWSEM_EXPORTED_FUNCTIONS HWSEM Exported Functions
  @{
*/

/**
  * @brief      Reset hardware semaphore
  *
  * @param[in]  hwsem         The pointer of the specified HWSEM module.
  * @param[in]  u32Num        HWSEM number, valid values are between 0~7
  * \hideinitializer
  */
#define HWSEM_RESET(hwsem, u32Num)          ((hwsem)->CTL |= (HWSEM_CTL_SEM0RST_Msk << (u32Num)))

/**
  * @brief
  *
  * @param[in]  hwsem         The pointer of the specified HWSEM module.
  * @param[in]  u32Num        HWSEM number, valid values are between 0~7
  *
  * @retval       0 The specified semaphore is not locked.
  *               Otherwise The specified semaphore is locked.
  * \hideinitializer
  */
#define HWSEM_IS_LOCKED(hwsem, u32Num)         ((hwsem)->SEM[(u32Num)] & (HWSEM_SEM_ID_Msk))

/**
  * @brief
  *
  * @param[in]  hwsem         The pointer of the specified HWSEM module.
  * @param[in]  u32Num        HWSEM number, valid values are between 0~7
  *
  * @retval       0 The key of specified semaphore.
  * \hideinitializer
  */
#define HWSEM_GET_KEY(hwsem, u32Num)         (((hwsem)->SEM[(u32Num)]&HWSEM_SEM_KEY_Msk) >> HWSEM_SEM_KEY_Pos)

/**
  * @brief        Enable specified HWSEM interrupt
  *
  * @param[in]  hwsem         The pointer of the specified HWSEM module.
  * @param[in]  u32Num        HWSEM number, valid values are between 0~7
  *
  *
  *    \hideinitializer
  */
#define HWSEM_ENABLE_INT(hwsem, u32Num)    ((hwsem)->INTEN_CORE |= (HWSEM_INTEN_SEM0IEN_Msk << (u32Num)))


/**
  *    @brief        Disable specified HWSEM interrupt
  *
  * @param[in]  hwsem         The pointer of the specified HWSEM module.
  * @param[in]  u32Num        HWSEM number, valid values are between 0~7
  *
  *
  *    \hideinitializer
  */
#define HWSEM_DISABLE_INT(hwsem, u32Num)    ((hwsem)->INTEN_CORE &= ~(HWSEM_INTEN_SEM0IEN_Msk << (u32Num)))

/**
  * @brief        Get specified interrupt flag
  *
  * @param[in]  hwsem         The pointer of the specified HWSEM module.
  * @param[in]  u32Num        HWSEM number, valid values are between 0~7
  *
  *    @retval       0 The specified interrupt is not happened.
  *                  Otherwise The specified interrupt is happened.
  *    \hideinitializer
  */
#define HWSEM_GET_INT_FLAG(hwsem, u32Num)    ((hwsem)->INTSTS_CORE & (HWSEM_INTSTS_SEM0IF_Msk << (u32Num)))


/**
  * @brief Clear specified interrupt flag
  *
  * @param[in]  hwsem         The pointer of the specified HWSEM module.
  * @param[in]  u32Num        HWSEM number, valid values are between 0~7
  *
  *    \hideinitializer
  */
#define HWSEM_CLR_INT_FLAG(hwsem, u32Num)    ((hwsem)->INTSTS_CORE = (HWSEM_INTSTS_SEM0IF_Msk << (u32Num)))


/**
  * @brief        Unlock specified semaphore
  *
  * @param[in]  hwsem         The pointer of the specified HWSEM module.
  * @param[in]  u32Num        HWSEM number, valid values are between 0~7
  * @param[in]  u8Key         HWSEM channel key
  *
  *    \hideinitializer
  */
#define HWSEM_UNLOCK(hwsem, u32Num, u8Key)    ((hwsem)->SEM[(u32Num)] = ((u8Key) << HWSEM_SEM_KEY_Pos) & HWSEM_SEM_KEY_Msk)
#define HWSEM_LOCK   HWSEM_UNLOCK

/* Declare these inline functions here to avoid MISRA C 2004 rule 8.1 error */
__STATIC_INLINE int32_t HWSEM_Try_Lock(HWSEM_T *hwsem, uint32_t u32Num, uint8_t u8Key);
__STATIC_INLINE void HWSEM_Spin_Lock(HWSEM_T *hwsem, uint32_t u32Num, uint8_t u8Key);

/**
  * @brief        Try to lock specified semaphore
  *
  * @param[in]  hwsem         The pointer of the specified HWSEM module.
  * @param[in]  u32Num        HWSEM number, valid values are between 0~7
  * @param[in]  u8Key         HWSEM channel key
  * @retval     0             Successfully acquire semaphore
  * @retval     -1            Failed to acquire semaphore
  *    \hideinitializer
  */
__STATIC_INLINE int32_t HWSEM_Try_Lock(HWSEM_T *hwsem, uint32_t u32Num, uint8_t u8Key)
{
    hwsem->SEM[u32Num] = (u8Key << HWSEM_SEM_KEY_Pos);
    if ((hwsem->SEM[u32Num] & HWSEM_SEM_ID_Msk) == HWSEM_LOCK_BY_OWNER &&
            (hwsem->SEM[u32Num] & HWSEM_SEM_KEY_Msk) == (u8Key << HWSEM_SEM_KEY_Pos))
        return 0;
    else
        return -1;
}

/**
  * @brief        Spin until lock specified semaphore
  *
  * @param[in]  hwsem         The pointer of the specified HWSEM module.
  * @param[in]  u32Num        HWSEM number, valid values are between 0~7
  * @param[in]  u8Key         HWSEM channel key
  *
  *    \hideinitializer
  */
__STATIC_INLINE void HWSEM_Spin_Lock(HWSEM_T *hwsem, uint32_t u32Num, uint8_t u8Key)
{
    while (1)
    {
        hwsem->SEM[u32Num] = (u8Key << HWSEM_SEM_KEY_Pos);
        if ((hwsem->SEM[u32Num] & HWSEM_SEM_ID_Msk) == HWSEM_LOCK_BY_OWNER &&
                (hwsem->SEM[u32Num] & HWSEM_SEM_KEY_Msk) == (u8Key << HWSEM_SEM_KEY_Pos))
            break;
    }
}

/*@}*/ /* end of group HWSEM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group HWSEM_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif

