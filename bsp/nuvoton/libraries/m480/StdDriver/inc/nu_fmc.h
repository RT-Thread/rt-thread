/**************************************************************************//**
 * @file     nu_fmc.h
 * @version  V1.00
 * @brief    M480 Series Flash Memory Controller Driver Header File
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
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


/*---------------------------------------------------------------------------------------------------------*/
/* Define Base Address                                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
#define FMC_APROM_BASE          0x00000000UL    /*!< APROM base address          \hideinitializer */
#define FMC_APROM_END           0x00080000UL    /*!< APROM end address           \hideinitializer */
#define FMC_APROM_BANK0_END     (FMC_APROM_END/2UL)  /*!< APROM bank0 end address     \hideinitializer */
#define FMC_LDROM_BASE          0x00100000UL    /*!< LDROM base address          \hideinitializer */
#define FMC_LDROM_END           0x00101000UL    /*!< LDROM end address           \hideinitializer */
#define FMC_SPROM_BASE          0x00200000UL    /*!< SPROM base address          \hideinitializer */
#define FMC_SPROM_END           0x00201000UL    /*!< SPROM end address           \hideinitializer */
#define FMC_XOM_BASE            0x00200000UL    /*!< XOM  Base Address           \hideinitializer */
#define FMC_XOMR0_BASE          0x00200000UL    /*!< XOMR 0 Base Address         \hideinitializer */
#define FMC_XOMR1_BASE          0x00200010UL    /*!< XOMR 1 Base Address         \hideinitializer */
#define FMC_XOMR2_BASE          0x00200020UL    /*!< XOMR 2 Base Address         \hideinitializer */
#define FMC_XOMR3_BASE          0x00200030UL    /*!< XOMR 3 Base Address         \hideinitializer */
#define FMC_CONFIG_BASE         0x00300000UL    /*!< User Configuration address  \hideinitializer */
#define FMC_USER_CONFIG_0       0x00300000UL    /*!< User Config 0 address       \hideinitializer */
#define FMC_USER_CONFIG_1       0x00300004UL    /*!< User Config 1 address       \hideinitializer */
#define FMC_USER_CONFIG_2       0x00300008UL    /*!< User Config 2 address       \hideinitializer */
#define FMC_KPROM_BASE          0x00301000UL    /*!< Security ROM base address   \hideinitializer */
#define FMC_OTP_BASE            0x00310000UL    /*!< OTP flash base address      \hideinitializer */

#define FMC_FLASH_PAGE_SIZE     0x1000UL        /*!< Flash Page Size (4K bytes)  \hideinitializer */
#define FMC_PAGE_ADDR_MASK      0xFFFFF000UL    /*!< Flash page address mask     \hideinitializer */
#define FMC_MULTI_WORD_PROG_LEN 512             /*!< The maximum length of a multi-word program.  */

#define FMC_APROM_SIZE          FMC_APROM_END   /*!< APROM Size                  \hideinitializer */
#define FMC_BANK_SIZE           (FMC_APROM_SIZE/2UL) /*!< APROM Bank Size        \hideinitializer */
#define FMC_LDROM_SIZE          0x1000UL        /*!< LDROM Size (4 Kbytes)       \hideinitializer */
#define FMC_SPROM_SIZE          0x1000UL        /*!< SPROM Size (4 Kbytes)       \hideinitializer */
#define FMC_OTP_ENTRY_CNT       256UL           /*!< OTP entry number            \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  XOM region number constant definitions                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
#define XOMR0   0UL                             /*!< XOM region 0     */
#define XOMR1   1UL                             /*!< XOM region 1     */
#define XOMR2   2UL                             /*!< XOM region 2     */
#define XOMR3   3UL                             /*!< XOM region 3     */

/*---------------------------------------------------------------------------------------------------------*/
/*  ISPCTL constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define IS_BOOT_FROM_LDROM      0x1UL           /*!< ISPCTL setting to select to boot from LDROM */
#define IS_BOOT_FROM_APROM      0x0UL           /*!< ISPCTL setting to select to boot from APROM */

/*---------------------------------------------------------------------------------------------------------*/
/*  ISPCMD constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define FMC_ISPCMD_READ         0x00UL          /*!< ISP Command: Read flash word         \hideinitializer */
#define FMC_ISPCMD_READ_UID     0x04UL          /*!< ISP Command: Read Unique ID          \hideinitializer */
#define FMC_ISPCMD_READ_ALL1    0x08UL          /*!< ISP Command: Read all-one result     \hideinitializer */
#define FMC_ISPCMD_READ_CID     0x0BUL          /*!< ISP Command: Read Company ID         \hideinitializer */
#define FMC_ISPCMD_READ_DID     0x0CUL          /*!< ISP Command: Read Device ID          \hideinitializer */
#define FMC_ISPCMD_READ_CKS     0x0DUL          /*!< ISP Command: Read checksum           \hideinitializer */
#define FMC_ISPCMD_PROGRAM      0x21UL          /*!< ISP Command: Write flash word        \hideinitializer */
#define FMC_ISPCMD_PAGE_ERASE   0x22UL          /*!< ISP Command: Page Erase Flash        \hideinitializer */
#define FMC_ISPCMD_BANK_ERASE   0x23UL          /*!< ISP Command: Erase Flash bank 0 or 1 \hideinitializer */
#define FMC_ISPCMD_BLOCK_ERASE  0x25UL          /*!< ISP Command: Erase 4 pages alignment of APROM in bank 0 or 1  \hideinitializer */
#define FMC_ISPCMD_PROGRAM_MUL  0x27UL          /*!< ISP Command: Multuple word program   \hideinitializer */
#define FMC_ISPCMD_RUN_ALL1     0x28UL          /*!< ISP Command: Run all-one verification \hideinitializer */
#define FMC_ISPCMD_RUN_CKS      0x2DUL          /*!< ISP Command: Run checksum calculation \hideinitializer */
#define FMC_ISPCMD_VECMAP       0x2EUL          /*!< ISP Command: Vector Page Remap       \hideinitializer */
#define FMC_ISPCMD_READ_64      0x40UL          /*!< ISP Command: Read double flash word  \hideinitializer */
#define FMC_ISPCMD_PROGRAM_64   0x61UL          /*!< ISP Command: Write double flash word \hideinitializer */

#define READ_ALLONE_YES         0xA11FFFFFUL    /*!< Check-all-one result is all one.     \hideinitializer */
#define READ_ALLONE_NOT         0xA1100000UL    /*!< Check-all-one result is not all one. \hideinitializer */
#define READ_ALLONE_CMD_FAIL    0xFFFFFFFFUL    /*!< Check-all-one command failed.        \hideinitializer */


/*@}*/ /* end of group FMC_EXPORTED_CONSTANTS */


/** @addtogroup FMC_EXPORTED_MACROS FMC Exported Macros
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

/*@}*/ /* end of group FMC_EXPORTED_MACROS */


/** @addtogroup FMC_EXPORTED_FUNCTIONS FMC Exported Functions
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/* inline functions                                                                                        */
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
    while(FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) {} /* Waiting for ISP Done */

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
    while(FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) {} /* Waiting for ISP Done */

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
    while(FMC->ISPTRG) {}

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
    while(FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) {}  /* Waiting for ISP Done */

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
    while(FMC->ISPTRG) {}             /* Waiting for ISP Done */
}


/*---------------------------------------------------------------------------------------------------------*/
/*  Functions                                                                                              */
/*---------------------------------------------------------------------------------------------------------*/

extern void     FMC_Close(void);
extern int32_t  FMC_ConfigXOM(uint32_t xom_num, uint32_t xom_base, uint8_t xom_page);
extern int32_t  FMC_Erase(uint32_t u32PageAddr);
extern int32_t  FMC_Erase_SPROM(void);
extern int32_t  FMC_Erase_Block(uint32_t u32BlockAddr);
extern int32_t  FMC_Erase_Bank(uint32_t u32BankAddr);
extern int32_t  FMC_EraseXOM(uint32_t xom_num);
extern int32_t  FMC_GetXOMState(uint32_t xom_num);
extern int32_t  FMC_GetBootSource(void);
extern void     FMC_Open(void);
extern uint32_t FMC_Read(uint32_t u32Addr);
extern int32_t  FMC_Read_64(uint32_t u32addr, uint32_t * u32data0, uint32_t * u32data1);
extern uint32_t FMC_ReadDataFlashBaseAddr(void);
extern void     FMC_SetBootSource(int32_t i32BootSrc);
extern void     FMC_Write(uint32_t u32Addr, uint32_t u32Data);
extern int32_t  FMC_Write8Bytes(uint32_t u32addr, uint32_t u32data0, uint32_t u32data1);
extern int32_t  FMC_WriteMultiple(uint32_t u32Addr, uint32_t pu32Buf[], uint32_t u32Len);
extern int32_t  FMC_Write_OTP(uint32_t otp_num, uint32_t low_word, uint32_t high_word);
extern int32_t  FMC_Read_OTP(uint32_t otp_num, uint32_t *low_word, uint32_t *high_word);
extern int32_t  FMC_Lock_OTP(uint32_t otp_num);
extern int32_t  FMC_Is_OTP_Locked(uint32_t otp_num);
extern int32_t  FMC_ReadConfig(uint32_t u32Config[], uint32_t u32Count);
extern int32_t  FMC_WriteConfig(uint32_t u32Config[], uint32_t u32Count);
extern uint32_t FMC_GetChkSum(uint32_t u32addr, uint32_t u32count);
extern uint32_t FMC_CheckAllOne(uint32_t u32addr, uint32_t u32count);
extern int32_t  FMC_SetSPKey(uint32_t key[3], uint32_t kpmax, uint32_t kemax, const int32_t lock_CONFIG, const int32_t lock_SPROM);
extern int32_t  FMC_CompareSPKey(uint32_t key[3]);


/*@}*/ /* end of group FMC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group FMC_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif   /* __NU_FMC_H__ */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
