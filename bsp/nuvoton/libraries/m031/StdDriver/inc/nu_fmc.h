/**************************************************************************//**
 * @file     nu_fmc.h
 * @version  V1.00
 * $Revision: 11 $
 * $Date: 18/06/20 3:38p $
 * @brief    M031 Series Flash Memory Controller Driver Header File
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __NU_FMC_H__
#define __NU_FMC_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup FMC_Driver FMC Driver
  @{
*/


/** @addtogroup FMC_EXPORTED_CONSTANTS FMC Exported Constants
  @{
*/

//#define PAGE_SIZE_2048                        /*!< Please enable the compiler option for 2K page size     */

/*----------------------------------------------------------------------------------------------------------*/
/* Define Base Address                                                                                      */
/*----------------------------------------------------------------------------------------------------------*/
#define FMC_APROM_BASE          0x00000000UL    /*!< APROM base address                    \hideinitializer */
#define FMC_LDROM_BASE          0x00100000UL    /*!< LDROM  Base Address                   \hideinitializer */
#define FMC_SPROM_BASE          0x00200000UL    /*!< SPROM  Base Address                   \hideinitializer */
#define FMC_CONFIG_BASE         0x00300000UL    /*!< CONFIG Base Address                   \hideinitializer */
#define FMC_USER_CONFIG_0       0x00300000UL    /*!< User Config 0 address                 \hideinitializer */
#define FMC_USER_CONFIG_1       0x00300004UL    /*!< User Config 1 address                 \hideinitializer */
#define FMC_USER_CONFIG_2       0x00300008UL    /*!< User Config 2 address                 \hideinitializer */

#ifndef PAGE_SIZE_2048
#define FMC_FLASH_PAGE_SIZE     (0x200)         /*!< Flash Page Size (512 bytes)           \hideinitializer */
#define FMC_PAGE_ADDR_MASK      (0xFFFFFE00UL)  /*!< Flash page address mask               \hideinitializer */

#define FMC_SPROM_SIZE          (0x200)         /*!< SPROM Size (512 bytes)                \hideinitializer */
#else
#define FMC_FLASH_PAGE_SIZE     (0x800)         /*!< Flash Page Size (2048 bytes)          \hideinitializer */
#define FMC_PAGE_ADDR_MASK      (0xFFFFF800UL)  /*!< Flash page address mask               \hideinitializer */

#define FMC_SPROM_SIZE          (0x800)         /*!< SPROM Size (2048 bytes)               \hideinitializer */
#endif

#define FMC_MULTI_WORD_PROG_LEN (256UL)         /*!< The length of a multi-word program.   \hideinitializer */

/*----------------------------------------------------------------------------------------------------------*/
/*  ISPCMD constant definitions                                                                             */
/*----------------------------------------------------------------------------------------------------------*/
#define FMC_ISPCMD_READ         0x00UL          /*!< ISP Command: Read flash word          \hideinitializer */
#define FMC_ISPCMD_READ_UID     0x04UL          /*!< ISP Command: Read Unique ID           \hideinitializer */
#define FMC_ISPCMD_READ_ALL1    0x08UL          /*!< ISP Command: Read all-one result      \hideinitializer */                                                                          //  I version
#define FMC_ISPCMD_READ_CID     0x0BUL          /*!< ISP Command: Read Company ID          \hideinitializer */
#define FMC_ISPCMD_READ_DID     0x0CUL          /*!< ISP Command: Read Device ID           \hideinitializer */
#define FMC_ISPCMD_READ_CKS     0x0DUL          /*!< ISP Command: Read checksum            \hideinitializer */
#define FMC_ISPCMD_PROGRAM      0x21UL          /*!< ISP Command: Write flash word         \hideinitializer */
#define FMC_ISPCMD_PROGRAM_64   0x61UL          /*!< ISP Command: 64-bit program Flash     \hideinitializer */
#define FMC_ISPCMD_PAGE_ERASE   0x22UL          /*!< ISP Command: Page Erase Flash         \hideinitializer */
#define FMC_ISPCMD_BANK_ERASE   0x23UL          /*!< ISP Command: Bank Erase Flash         \hideinitializer */
#define FMC_ISPCMD_MULTI_PROG   0x27UL          /*!< ISP Command: Flash Multi-Word Program \hideinitializer */
#define FMC_ISPCMD_RUN_ALL1     0x28UL          /*!< ISP Command: Run all-one verification \hideinitializer */                                                                  // I version
#define FMC_ISPCMD_RUN_CKS      0x2DUL          /*!< ISP Command: Run checksum calculation \hideinitializer */
#define FMC_ISPCMD_BANK_REMAP   0x2CUL          /*!< ISP Command: Bank Remap               \hideinitializer */
#define FMC_ISPCMD_VECMAP       0x2EUL          /*!< ISP Command: Vector Page Remap        \hideinitializer */

#define IS_BOOT_FROM_APROM      0UL             /*!< Is booting from APROM                 \hideinitializer */
#define IS_BOOT_FROM_LDROM      1UL             /*!< Is booting from LDROM                 \hideinitializer */

#define READ_ALLONE_YES         0xA11FFFFFUL    /*!< Check-all-one result is all one.      \hideinitializer */
#define READ_ALLONE_NOT         0xA1100000UL    /*!< Check-all-one result is not all one.  \hideinitializer */
#define READ_ALLONE_CMD_FAIL    0xFFFFFFFFUL    /*!< Check-all-one command failed.         \hideinitializer */
/*@}*/ /* end of group FMC_EXPORTED_CONSTANTS */


/** @addtogroup FMC_EXPORTED_FUNCTIONS FMC Exported Functions
  @{
*/


/*---------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/

#define FMC_SET_APROM_BOOT()        (FMC->ISPCTL &= ~FMC_ISPCTL_BS_Msk)         /*!< Select booting from APROM  \hideinitializer */
#define FMC_SET_LDROM_BOOT()        (FMC->ISPCTL |= FMC_ISPCTL_BS_Msk)          /*!< Select booting from LDROM  \hideinitializer */
#define FMC_ENABLE_AP_UPDATE()      (FMC->ISPCTL |=  FMC_ISPCTL_APUEN_Msk)      /*!< Enable APROM update        \hideinitializer */
#define FMC_DISABLE_AP_UPDATE()     (FMC->ISPCTL &= ~FMC_ISPCTL_APUEN_Msk)      /*!< Disable APROM update       \hideinitializer */
#define FMC_ENABLE_CFG_UPDATE()     (FMC->ISPCTL |=  FMC_ISPCTL_CFGUEN_Msk)     /*!< Enable User Config update  \hideinitializer */
#define FMC_DISABLE_CFG_UPDATE()    (FMC->ISPCTL &= ~FMC_ISPCTL_CFGUEN_Msk)     /*!< Disable User Config update \hideinitializer */
#define FMC_ENABLE_LD_UPDATE()      (FMC->ISPCTL |=  FMC_ISPCTL_LDUEN_Msk)      /*!< Enable LDROM update        \hideinitializer */
#define FMC_DISABLE_LD_UPDATE()     (FMC->ISPCTL &= ~FMC_ISPCTL_LDUEN_Msk)      /*!< Disable LDROM update       \hideinitializer */
#define FMC_ENABLE_SP_UPDATE()      (FMC->ISPCTL |=  FMC_ISPCTL_SPUEN_Msk)      /*!< Enable SPROM update        \hideinitializer */
#define FMC_DISABLE_SP_UPDATE()     (FMC->ISPCTL &= ~FMC_ISPCTL_SPUEN_Msk)      /*!< Disable SPROM update       \hideinitializer */
#define FMC_DISABLE_ISP()           (FMC->ISPCTL &= ~FMC_ISPCTL_ISPEN_Msk)      /*!< Disable ISP function       \hideinitializer */
#define FMC_ENABLE_ISP()            (FMC->ISPCTL |=  FMC_ISPCTL_ISPEN_Msk)      /*!< Enable ISP function        \hideinitializer */
#define FMC_GET_FAIL_FLAG()         ((FMC->ISPCTL & FMC_ISPCTL_ISPFF_Msk) ? 1UL : 0UL)  /*!< Get ISP fail flag  \hideinitializer */
#define FMC_CLR_FAIL_FLAG()         (FMC->ISPCTL |= FMC_ISPCTL_ISPFF_Msk)       /*!< Clear ISP fail flag        \hideinitializer */
#define FMC_ENABLE_ISP_INT()        (FMC->ISPCTL |=  FMC_ISPCTL_INTEN_Msk) /*!< Enable ISP interrupt */
#define FMC_DISABLE_ISP_INT()       (FMC->ISPCTL &= ~FMC_ISPCTL_INTEN_Msk) /*!< Disable ISP interrupt */
#define FMC_GET_ISP_INT_FLAG()      ((FMC->ISPSTS & FMC_ISPSTS_INTFLAG_Msk) ? 1UL : 0UL) /*!< Get ISP interrupt flag Status */
#define FMC_CLEAR_ISP_INT_FLAG()    (FMC->ISPSTS = FMC_ISPSTS_INTFLAG_Msk) /*!< Clear ISP interrupt flag*/

/*---------------------------------------------------------------------------------------------------------*/

__STATIC_INLINE uint32_t FMC_ReadCID(void);
__STATIC_INLINE uint32_t FMC_ReadPID(void);
__STATIC_INLINE uint32_t FMC_ReadUID(uint8_t u8Index);
__STATIC_INLINE uint32_t FMC_ReadUCID(uint32_t u32Index);
__STATIC_INLINE void FMC_SetVectorPageAddr(uint32_t u32PageAddr);
__STATIC_INLINE uint32_t FMC_GetVECMAP(void);

/**
 * @brief       Get current vector mapping address.
 * @param       None
 * @return      The current vector mapping address.
 * @details     To get VECMAP value which is the page address for remapping to vector page (0x0).
 * @note
 *              VECMAP only valid when new IAP function is enabled. (CBS = 10'b or 00'b)
 */
__STATIC_INLINE uint32_t FMC_GetVECMAP(void)
{
    return (FMC->ISPSTS & FMC_ISPSTS_VECMAP_Msk);
}

/**
  * @brief    Read company ID
  * @param    None
  * @return   The company ID (32-bit)
  * @details  The company ID of Nuvoton is fixed to be 0xDA
  */
__STATIC_INLINE uint32_t FMC_ReadCID(void)
{
    FMC->ISPCMD = FMC_ISPCMD_READ_CID;           /* Set ISP Command Code */
    FMC->ISPADDR = 0x0u;                         /* Must keep 0x0 when read CID */
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;          /* Trigger to start ISP procedure */
#if ISBEN
    __ISB();
#endif                                           /* To make sure ISP/CPU be Synchronized */
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) {} /* Waiting for ISP Done */

    return FMC->ISPDAT;
}

/**
  * @brief    Read product ID
  * @param    None
  * @return   The product ID (32-bit)
  * @details  This function is used to read product ID.
  */
__STATIC_INLINE uint32_t FMC_ReadPID(void)
{
    FMC->ISPCMD = FMC_ISPCMD_READ_DID;          /* Set ISP Command Code */
    FMC->ISPADDR = 0x04u;                       /* Must keep 0x4 when read PID */
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;         /* Trigger to start ISP procedure */
#if ISBEN
    __ISB();
#endif                                          /* To make sure ISP/CPU be Synchronized */
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) {} /* Waiting for ISP Done */

    return FMC->ISPDAT;
}

/**
 * @brief       Read Unique ID
 * @param[in]   u8Index  UID index. 0 = UID[31:0], 1 = UID[63:32], 2 = UID[95:64]
 * @return      The 32-bit unique ID data of specified UID index.
 * @details     To read out 96-bit Unique ID.
 */
__STATIC_INLINE uint32_t FMC_ReadUID(uint8_t u8Index)
{
    FMC->ISPCMD = FMC_ISPCMD_READ_UID;
    FMC->ISPADDR = ((uint32_t)u8Index << 2u);
    FMC->ISPDAT = 0u;
    FMC->ISPTRG = 0x1u;
#if ISBEN
    __ISB();
#endif
    while (FMC->ISPTRG) {}

    return FMC->ISPDAT;
}

/**
  * @brief      To read UCID
  * @param[in]  u32Index    Index of the UCID to read. u32Index must be 0, 1, 2, or 3.
  * @return     The UCID of specified index
  * @details    This function is used to read unique chip ID (UCID).
  */
__STATIC_INLINE uint32_t FMC_ReadUCID(uint32_t u32Index)
{
    FMC->ISPCMD = FMC_ISPCMD_READ_UID;            /* Set ISP Command Code */
    FMC->ISPADDR = (0x04u * u32Index) + 0x10u;    /* The UCID is at offset 0x10 with word alignment. */
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;           /* Trigger to start ISP procedure */
#if ISBEN
    __ISB();
#endif                                            /* To make sure ISP/CPU be Synchronized */
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) {} /* Waiting for ISP Done */

    return FMC->ISPDAT;
}

/**
 * @brief       Set vector mapping address
 * @param[in]   u32PageAddr  The page address to remap to address 0x0. The address must be page alignment.
 * @return      To set VECMAP to remap specified page address to 0x0.
 * @details     This function is used to set VECMAP to map specified page to vector page (0x0).
 * @note
 *              VECMAP only valid when new IAP function is enabled. (CBS = 10'b or 00'b)
 */
__STATIC_INLINE void FMC_SetVectorPageAddr(uint32_t u32PageAddr)
{
    FMC->ISPCMD = FMC_ISPCMD_VECMAP;  /* Set ISP Command Code */
    FMC->ISPADDR = u32PageAddr;       /* The address of specified page which will be map to address 0x0. It must be page alignment. */
    FMC->ISPTRG = 0x1u;               /* Trigger to start ISP procedure */
#if ISBEN
    __ISB();
#endif                                /* To make sure ISP/CPU be Synchronized */
    while (FMC->ISPTRG) {}            /* Waiting for ISP Done */
}


/*---------------------------------------------------------------------------------------------------------*/
/*  Functions                                                                                              */
/*---------------------------------------------------------------------------------------------------------*/

extern void FMC_Close(void);
extern int32_t FMC_Erase(uint32_t u32PageAddr);
extern int32_t FMC_Erase_SPROM(void);
extern int32_t FMC_Erase_Bank(uint32_t u32BankAddr);
extern int32_t FMC_GetBootSource(void);
extern void FMC_Open(void);
extern uint32_t FMC_Read(uint32_t u32Addr);
extern uint32_t FMC_ReadDataFlashBaseAddr(void);
extern void FMC_SetBootSource(int32_t i32BootSrc);
extern void FMC_Write(uint32_t u32Addr, uint32_t u32Data);
extern int32_t  FMC_Write8Bytes(uint32_t u32addr, uint32_t u32data0, uint32_t u32data1);
extern int32_t  FMC_ReadConfig(uint32_t u32Config[], uint32_t u32Count);
extern int32_t  FMC_WriteConfig(uint32_t u32Config[], uint32_t u32Count);
extern uint32_t FMC_GetChkSum(uint32_t u32addr, uint32_t u32count);
extern uint32_t  FMC_CheckAllOne(uint32_t u32addr, uint32_t u32count);
extern int32_t FMC_WriteMultiple(uint32_t u32Addr, uint32_t pu32Buf[], uint32_t u32Len);
extern int32_t FMC_RemapBank(uint32_t u32BankIdx);

/*@}*/ /* end of group FMC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group FMC_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif   /* __NU_FMC_H__ */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
