/**************************************************************************//**
 * @file     crc.h
 * @version  V3.00
 * $Revision: 2 $
 * $Date: 15/05/04 3:27p $
 * @brief    CRC driver header file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
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
#define CRC_CPU_WDATA_8     0x00000000UL            /*!<CRC 8-bit CPU Write Data */
#define CRC_CPU_WDATA_16    0x10000000UL            /*!<CRC 16-bit CPU Write Data */
#define CRC_CPU_WDATA_32    0x20000000UL            /*!<CRC 32-bit CPU Write Data */

/*@}*/ /* end of group CRC_EXPORTED_CONSTANTS */


/** @addtogroup CRC_EXPORTED_FUNCTIONS CRC Exported Functions
  @{
*/

/**
  * @brief      Enable CRC Interrupt
  *
  * @param[in]  u32Mask     Interrupt mask
  *
  * @return     None
  *
  * @details    This macro enable the specify CRC interrupt function by u32Mask setting.
  */
#define CRC_ENABLE_INT(u32Mask)   (CRC->DMAIER |= (u32Mask))

/**
  * @brief      Disable CRC Interrupt
  *
  * @param[in]  u32Mask     Interrupt mask
  *
  * @return     None
  *
  * @details    This macro disable the specify CRC interrupt function by u32Mask setting.
  */
#define CRC_DISABLE_INT(u32Mask)    (CRC->DMAIER &= ~(u32Mask))

/**
  * @brief      Get CRC Interrupt Flag
  *
  * @param      None
  *
  * @return     Interrupt Flag Status
  *
  * @details    This macro gets the CRC interrupt flags.
  */
#define CRC_GET_INT_FLAG()          ((uint32_t)(CRC->DMAISR))

/**
  * @brief      Clear CRC Interrupt Flag
  *
  * @param[in]  u32Mask     Interrupt mask
  *
  * @return     None
  *
  * @details    This macro clear the specify CRC interrupt flag by u32Mask setting.
  */
#define CRC_CLR_INT_FLAG(u32Mask)   (CRC->DMAISR = (u32Mask))

/**
  * @brief      Set CRC seed value
  *
  * @param[in]  u32Seed     Seed value
  *
  * @return     None
  *
  * @details    This macro set CRC seed value.
  *
  * @note       User must to setting CRC_RST (CRC_CTL[1] CRC Engine Reset) to reload the new seed value
  *             to CRC controller.
  */
#define CRC_SET_SEED(u32Seed)       { CRC->SEED = (u32Seed); CRC->CTL |= CRC_CTL_CRC_RST_Msk; }

/**
  * @brief      Get CRC Seed value
  *
  * @param      None
  *
  * @return     Seed Value
  *
  * @details    This macro gets the current CRC seed value.
  */
#define CRC_GET_SEED()              ((uint32_t)(CRC->SEED))

/**
  * @brief      CRC write data
  *
  * @param[in]  u32Data     write data
  *
  * @return     None
  *
  * @details    User can write data directly by this macro to perform CRC operation.
  */
#define CRC_WRITE_DATA(u32Data)     (CRC->WDATA = (u32Data))


/*********************************************************************/
void CRC_Open(uint32_t u32Mode, uint32_t u32Attribute, uint32_t u32Seed, uint32_t u32DataLen);
void CRC_StartDMATransfer(uint32_t u32SrcAddr, uint32_t u32ByteCount);
uint32_t CRC_GetChecksum(void);

/*@}*/ /* end of group CRC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CRC_Driver */

/*@}*/ /* end of group Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__CRC_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
