/**************************************************************************//**
 * @file     nu_crc.h
 * @version  V1.00
 * @brief    M480 series CRC driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_CRC_H__
#define __NU_CRC_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CRC_Driver CRC Driver
  @{
*/

/** @addtogroup CRC_EXPORTED_CONSTANTS CRC Exported Constants
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/*  CRC Polynomial Mode Constant Definitions                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define CRC_CCITT           (0UL << CRC_CTL_CRCMODE_Pos) /*!<CRC Polynomial Mode - CCITT \hideinitializer */
#define CRC_8               (1UL << CRC_CTL_CRCMODE_Pos) /*!<CRC Polynomial Mode - CRC8 \hideinitializer */
#define CRC_16              (2UL << CRC_CTL_CRCMODE_Pos) /*!<CRC Polynomial Mode - CRC16 \hideinitializer */
#define CRC_32              (3UL << CRC_CTL_CRCMODE_Pos) /*!<CRC Polynomial Mode - CRC32 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Checksum, Write data Constant Definitions                                                              */
/*---------------------------------------------------------------------------------------------------------*/
#define CRC_CHECKSUM_COM    (CRC_CTL_CHKSFMT_Msk)       /*!<CRC Checksum Complement \hideinitializer */
#define CRC_CHECKSUM_RVS    (CRC_CTL_CHKSREV_Msk)       /*!<CRC Checksum Reverse \hideinitializer */
#define CRC_WDATA_COM       (CRC_CTL_DATFMT_Msk)        /*!<CRC Write Data Complement \hideinitializer */
#define CRC_WDATA_RVS       (CRC_CTL_DATREV_Msk)        /*!<CRC Write Data Reverse \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CPU Write Data Length Constant Definitions                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define CRC_CPU_WDATA_8     (0UL << CRC_CTL_DATLEN_Pos) /*!<CRC CPU Write Data length is 8-bit \hideinitializer */
#define CRC_CPU_WDATA_16    (1UL << CRC_CTL_DATLEN_Pos) /*!<CRC CPU Write Data length is 16-bit \hideinitializer */
#define CRC_CPU_WDATA_32    (2UL << CRC_CTL_DATLEN_Pos) /*!<CRC CPU Write Data length is 32-bit \hideinitializer */

/*@}*/ /* end of group CRC_EXPORTED_CONSTANTS */


/** @addtogroup CRC_EXPORTED_FUNCTIONS CRC Exported Functions
  @{
*/

/**
  * @brief      Set CRC Seed Value
  *
  * @param[in]  u32Seed     Seed value
  *
  * @return     None
  *
  * @details    This macro is used to set CRC seed value.
  *
  * @note       User must to perform CRC_CHKSINIT(CRC_CTL[1] CRC Engine Reset) to reload the new seed value
  *             to CRC controller.
  * \hideinitializer
  */
#define CRC_SET_SEED(u32Seed)   do{ CRC->SEED = (u32Seed); CRC->CTL |= CRC_CTL_CHKSINIT_Msk; }while(0)

/**
 * @brief       Get CRC Seed Value
 *
  * @param      None
 *
 * @return      CRC seed value
 *
 * @details     This macro gets the current CRC seed value.
 * \hideinitializer
 */
#define CRC_GET_SEED()          (CRC->SEED)

/**
 * @brief       CRC Write Data
 *
 * @param[in]   u32Data     Write data
 *
 * @return      None
 *
 * @details    User can write data directly to CRC Write Data Register(CRC_DAT) by this macro to perform CRC operation.
 * \hideinitializer
 */
#define CRC_WRITE_DATA(u32Data)   (CRC->DAT = (u32Data))

void CRC_Open(uint32_t u32Mode, uint32_t u32Attribute, uint32_t u32Seed, uint32_t u32DataLen);
uint32_t CRC_GetChecksum(void);

/*@}*/ /* end of group CRC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CRC_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
