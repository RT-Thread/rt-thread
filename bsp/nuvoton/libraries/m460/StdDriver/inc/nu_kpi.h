/**************************************************************************//**
 * @file     nu_kpi.h
 * @version  V3.00
 * @brief    Keypad interface driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_KPI_H__
#define __NU_KPI_H__


#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup KPI_Driver KPI Driver
  @{
*/

/** @addtogroup KPI_EXPORTED_CONSTANTS KPI Exported Constants
  @{
*/

#define KPI_MAX_ROW     6
#define KPI_MAX_COL     8
#define KPI_MAX_KEYS    (KPI_MAX_ROW * KPI_MAX_COL)

#define KPI_PRESS   0
#define KPI_RELEASE 1

typedef struct
{
    uint8_t     x;
    uint8_t     y;
    uint16_t    st;
} KPI_KEY_T;

/**@}*/ /* end of group KPI_EXPORTED_CONSTANTS */


/** @addtogroup KPI_EXPORTED_FUNCTIONS KPI Exported Functions
  @{
*/

int32_t KPI_Open(uint32_t u32Rows, uint32_t u32Columns, KPI_KEY_T *pkeyQueue, uint32_t u32MaxKeyCnt);
void KPI_Close(void);
int32_t KPI_kbhit(void);
KPI_KEY_T KPI_GetKey(void);
void KPI_SetSampleTime(uint32_t ms);

/**@}*/ /* end of group KPI_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group KPI_Driver */

/**@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_KPI_H__ */

