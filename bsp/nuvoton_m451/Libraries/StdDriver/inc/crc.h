/**************************************************************************//**
 * @file     crc.h
 * @version  V3.00
 * $Revision: 6 $
 * $Date: 15/08/11 10:26a $
 * @brief    M451 series CRC driver header file
 *
 * @note
 * Copyright (C) 2013~2015 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __CRC_H__
#define __CRC_H__

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
#define CRC_CCITT           0x00000000UL            /*!<CRC Polynomial Mode - CCITT */
#define CRC_8               0x40000000UL            /*!<CRC Polynomial Mode - CRC8 */
#define CRC_16              0x80000000UL            /*!<CRC Polynomial Mode - CRC16 */
#define CRC_32              0xC0000000UL            /*!<CRC Polynomial Mode - CRC32 */

/*---------------------------------------------------------------------------------------------------------*/
/*  Checksum, Write data Constant Definitions                                                              */
/*---------------------------------------------------------------------------------------------------------*/
#define CRC_CHECKSUM_COM    0x08000000UL            /*!<CRC Checksum Complement */
#define CRC_CHECKSUM_RVS    0x02000000UL            /*!<CRC Checksum Reverse */
#define CRC_WDATA_COM       0x04000000UL            /*!<CRC Write Data Complement */
#define CRC_WDATA_RVS       0x01000000UL            /*!<CRC Write Data Reverse */

/*---------------------------------------------------------------------------------------------------------*/
/*  CPU Write Data Length Constant Definitions                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define CRC_CPU_WDATA_8     0x00000000UL            /*!<CRC CPU Write Data length is 8-bit */
#define CRC_CPU_WDATA_16    0x10000000UL            /*!<CRC CPU Write Data length is 16-bit */
#define CRC_CPU_WDATA_32    0x20000000UL            /*!<CRC CPU Write Data length is 32-bit */

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
  * @note       User must to perform CRC_RST(CRC_CTL[1] CRC Engine Reset) to reload the new seed value
  *             to CRC controller.
  */
#define CRC_SET_SEED(u32Seed)   { CRC->SEED = (u32Seed); CRC->CTL |= CRC_CTL_CRCRST_Msk; }

/**
 * @brief       Get CRC Seed Value
 *
  * @param      None
 *
 * @return      CRC seed value
 *
 * @details     This macro gets the current CRC seed value.
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

#endif //__CRC_H__

/*** (C) COPYRIGHT 2013~2015 Nuvoton Technology Corp. ***/
