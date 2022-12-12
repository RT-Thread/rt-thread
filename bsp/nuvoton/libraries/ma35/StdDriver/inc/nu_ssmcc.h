/****************************************************************************//**
 * @file     nu_ssmcc.h
 * @brief    SSMCC driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_SSMCC_H__
#define __NU_SSMCC_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SSMCC_Driver SSMCC Driver
  @{
*/

/** @addtogroup SSMCC_EXPORTED_CONSTANTS SSMCC Exported Constants
  @{
*/
#define SSMCC_REGION_0      0UL     /*!< region 0                \hideinitializer */
#define SSMCC_REGION_1      1UL     /*!< region 1                \hideinitializer */
#define SSMCC_REGION_2      2UL     /*!< region 2                \hideinitializer */
#define SSMCC_REGION_3      3UL     /*!< region 3                \hideinitializer */
#define SSMCC_REGION_4      4UL     /*!< region 4                \hideinitializer */
#define SSMCC_REGION_5      5UL     /*!< region 5                \hideinitializer */
#define SSMCC_REGION_6      6UL     /*!< region 6                \hideinitializer */
#define SSMCC_REGION_7      7UL     /*!< region 7                \hideinitializer */
#define SSMCC_REGION_8      8UL     /*!< region 8                \hideinitializer */

#define SSMCC_SECURE_READ        0x40000000UL     /*!< set region to secure read                \hideinitializer */
#define SSMCC_SECURE_WRITE       0x80000000UL     /*!< set region to secure write               \hideinitializer */
#define SSMCC_NONSECURE_READ     0x00000001UL     /*!< set region to non-secure read            \hideinitializer */
#define SSMCC_NONSECURE_WRITE    0x00010000UL     /*!< set region to non-secure write           \hideinitializer */
#define SSMCC_M4NS_READ          0x00000002UL     /*!< set region to m4 non-secure read         \hideinitializer */
#define SSMCC_M4NS_WRITE         0x00020000UL     /*!< set region to m4 non-secure write        \hideinitializer */

typedef struct ssmcc_param
{
    uint32_t region_no;
    uint32_t base_address;
    uint32_t size;
    uint32_t attribute;
} SSMCC_PARAM_T;

/*@}*/ /* end of group SSMCC_EXPORTED_CONSTANTS */

/** @addtogroup SSMCC_EXPORTED_FUNCTIONS SSMCC Exported Functions
  @{
*/

void SSMCC_SetRegion0(uint32_t u32Attr);
void SSMCC_SetRegion(SSMCC_PARAM_T *psParam);


/*@}*/ /* end of group SSMCC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SSMCC_Driver */

/*@}*/ /* end of group Standard_Driver */
#ifdef __cplusplus
}
#endif

#endif


