/**************************************************************************//**
 * @file     nu_fmc.h
 * @version  V3.0
 * $Revision: 2 $
 * $Date: 19/11/27 3:11p $
 * @brief    M2355 Series Flash Memory Controller(FMC) driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
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
/* Global constant definitions                                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
#define ISBEN   0UL
#define FMC_ISP   ( (__PC() & 0x10000000) ? FMC_NS : FMC)

/*---------------------------------------------------------------------------------------------------------*/
/* Define Base Address                                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
#define FMC_APROM_BASE          0x00000000UL    /*!< APROM  Base Address          */
#define FMC_APROM_END           0x00100000UL    /*!< APROM end address            */
#define FMC_APROM_BANK0_END     (FMC_APROM_END/2UL)  /*!< APROM bank0 end address */
#define FMC_LDROM_BASE          0x00100000UL    /*!< LDROM  Base Address          */
#define FMC_LDROM_END           0x00104000UL    /*!< LDROM end address            */
#define FMC_DTFSH_BASE          0x00110000UL    /*!< LDROM  Base Address          */
#define FMC_DTFSH_END           0x00112000UL    /*!< LDROM end address            */
#define FMC_XOM_BASE            0x00200000UL    /*!< XOM  Base Address            */
#define FMC_XOMR0_BASE          0x00200000UL    /*!< XOMR 0 Base Address */
#define FMC_XOMR1_BASE          0x00200010UL    /*!< XOMR 1 Base Address */
#define FMC_XOMR2_BASE          0x00200020UL    /*!< XOMR 2 Base Address */
#define FMC_XOMR3_BASE          0x00200030UL    /*!< XOMR 3 Base Address */
#define FMC_NSCBA_BASE          0x00210800UL    /*!< Non-Secure base address      */
#define FMC_SCRLOCK_BASE        0x00610000UL    /*!< Secure Region Lock base address */
#define FMC_ARLOCK_BASE         0x00610008UL    /*!< All Region Lock base address */
#define FMC_CONFIG_BASE         0x00300000UL    /*!< CONFIG Base Address          */
#define FMC_USER_CONFIG_0       0x00300000UL    /*!< CONFIG 0 Address */
#define FMC_USER_CONFIG_1       0x00300004UL    /*!< CONFIG 1 Address */
#define FMC_USER_CONFIG_2       0x00300008UL    /*!< CONFIG 2 Address */
#define FMC_USER_CONFIG_3       0x0030000CUL    /*!< CONFIG 3 Address */
#define FMC_OTP_BASE            0x00310000UL    /*!< OTP flash base address       */

#define FMC_FLASH_PAGE_SIZE     0x800UL         /*!< Flash Page Size (2048 Bytes) */
#define FMC_PAGE_ADDR_MASK      0xFFFFF800UL    /*!< Flash page address mask      */
#define FMC_MULTI_WORD_PROG_LEN 512UL           /*!< The maximum length of a multi-word program.  */

#define FMC_APROM_SIZE          FMC_APROM_END   /*!< APROM Size                  */
#define FMC_BANK_SIZE           (FMC_APROM_SIZE/2UL) /*!< APROM Bank Size             */
#define FMC_LDROM_SIZE          0x4000UL        /*!< LDROM Size (4 Kbytes)       */
#define FMC_OTP_ENTRY_CNT       256UL           /*!< OTP entry number            */

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
#define IS_BOOT_FROM_LDROM      0x1UL     /*!< ISPCTL setting to select to boot from LDROM */
#define IS_BOOT_FROM_APROM      0x0UL     /*!< ISPCTL setting to select to boot from APROM */

/*---------------------------------------------------------------------------------------------------------*/
/*  ISPCMD constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define FMC_ISPCMD_READ         0x00UL     /*!< ISP Command: Read Flash               */
#define FMC_ISPCMD_READ_UID     0x04UL     /*!< ISP Command: Read Unique ID           */
#define FMC_ISPCMD_READ_ALL1    0x08UL     /*!< ISP Command: Read all-one result      */
#define FMC_ISPCMD_READ_CID     0x0BUL     /*!< ISP Command: Read Company ID          */
#define FMC_ISPCMD_READ_DID     0x0CUL     /*!< ISP Command: Read Device ID           */
#define FMC_ISPCMD_READ_CKS     0x0DUL     /*!< ISP Command: Read Checksum            */
#define FMC_ISPCMD_PROGRAM      0x21UL     /*!< ISP Command: 32-bit Program Flash     */
#define FMC_ISPCMD_PAGE_ERASE   0x22UL     /*!< ISP Command: Page Erase Flash         */
#define FMC_ISPCMD_BANK_ERASE   0x23UL     /*!< ISP Command: Erase Flash bank 0 or 1  */
#define FMC_ISPCMD_PROGRAM_MUL  0x27UL     /*!< ISP Command: Flash Multi-Word Program */
#define FMC_ISPCMD_RUN_ALL1     0x28UL     /*!< ISP Command: Run all-one verification */
#define FMC_ISPCMD_BANK_REMAP   0x2CUL     /*!< ISP Command: Bank Remap                */
#define FMC_ISPCMD_RUN_CKS      0x2DUL     /*!< ISP Command: Run Check Calculation    */
#define FMC_ISPCMD_VECMAP       0x2EUL     /*!< ISP Command: Set vector mapping       */
#define FMC_ISPCMD_READ_64      0x40UL     /*!< ISP Command: 64-bit read Flash        */
#define FMC_ISPCMD_PROGRAM_64   0x61UL     /*!< ISP Command: 64-bit program Flash     */

#define READ_ALLONE_YES         0xA11FFFFFUL    /*!< Check-all-one result is all one.     */
#define READ_ALLONE_NOT         0xA1100000UL    /*!< Check-all-one result is not all one. */
#define READ_ALLONE_CMD_FAIL    0xFFFFFFFFUL    /*!< Check-all-one command failed.        */

/**@}*/ /* end of group FMC_EXPORTED_CONSTANTS */

/** @addtogroup FMC_EXPORTED_FUNCTIONS FMC Exported Functions
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  FMC Macro Definitions                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
/**
 * @brief      Enable ISP Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will set ISPEN bit of ISPCTL control register to enable ISP function.
 *
 */
#define FMC_ENABLE_ISP()          (FMC_ISP->ISPCTL |=  FMC_ISPCTL_ISPEN_Msk)  /*!< Enable ISP Function  */

/**
 * @brief      Disable ISP Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will clear ISPEN bit of ISPCTL control register to disable ISP function.
 *
 */
#define FMC_DISABLE_ISP()         (FMC_ISP->ISPCTL &= ~FMC_ISPCTL_ISPEN_Msk)  /*!< Disable ISP Function */

/**
 * @brief      Disable Non Secure ISP Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will clear ISPEN bit of ISPCTL control register to disable Non Secure ISP function.
 *
 */

#define FMC_ENABLE_LD_UPDATE()    (FMC->ISPCTL |=  FMC_ISPCTL_LDUEN_Msk)  /*!< Enable LDROM Update Function   */

/**
 * @brief      Disable LDROM Update Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will set ISPEN bit of ISPCTL control register to disable LDROM update function.
 *
 */
#define FMC_DISABLE_LD_UPDATE()   (FMC->ISPCTL &= ~FMC_ISPCTL_LDUEN_Msk)  /*!< Disable LDROM Update Function  */

/**
 * @brief      Enable User Configuration Update Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will set CFGUEN bit of ISPCTL control register to enable User Configuration update function.
 *             User needs to set CFGUEN bit before they can update User Configuration area.
 *
 */
#define FMC_ENABLE_CFG_UPDATE()   (FMC->ISPCTL |=  FMC_ISPCTL_CFGUEN_Msk) /*!< Enable CONFIG Update Function  */

/**
 * @brief      Disable User Configuration Update Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will clear CFGUEN bit of ISPCTL control register to disable User Configuration update function.
 *
 */
#define FMC_DISABLE_CFG_UPDATE()  (FMC->ISPCTL &= ~FMC_ISPCTL_CFGUEN_Msk) /*!< Disable CONFIG Update Function */


/**
 * @brief      Enable APROM Update Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will set APUEN bit of ISPCTL control register to enable APROM update function.
 *             User needs to set APUEN bit before they can update APROM in APROM boot mode.
 *
 */
#define FMC_ENABLE_AP_UPDATE()    (FMC_ISP->ISPCTL |=  FMC_ISPCTL_APUEN_Msk)  /*!< Enable APROM Update Function   */

/**
 * @brief      Disable APROM Update Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will clear APUEN bit of ISPCTL control register to disable APROM update function.
 *
 */
#define FMC_DISABLE_AP_UPDATE()   (FMC_ISP->ISPCTL &= ~FMC_ISPCTL_APUEN_Msk)  /*!< Disable APROM Update Function  */

/**
 * @brief      Get ISP Fail Flag
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function is used to get ISP fail flag when do ISP actoin.
 *
 */
#define FMC_GET_FAIL_FLAG()         ((FMC_ISP->ISPCTL & FMC_ISPCTL_ISPFF_Msk) ? 1UL : 0UL)  /*!< Get ISP fail flag */

/**
 * @brief      Clear ISP Fail Flag
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function is used to clear ISP fail flag when ISP fail flag set.
 *
 */
#define FMC_CLR_FAIL_FLAG()         (FMC_ISP->ISPCTL |= FMC_ISPCTL_ISPFF_Msk)       /*!< Clear ISP fail flag */

/**
 * @brief      Enable ISP Interrupt
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will enable ISP action interrupt.
 *
 */
#define FMC_ENABLE_ISP_INT()     (FMC_ISP->ISPCTL |=  FMC_ISPCTL_INTEN_Msk) /*!< Enable ISP interrupt */

/**
 * @brief      Disable ISP Interrupt
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will disable ISP action interrupt.
 *
 */
#define FMC_DISABLE_ISP_INT()     (FMC_ISP->ISPCTL &= ~FMC_ISPCTL_INTEN_Msk) /*!< Disable ISP interrupt */

/**
 * @brief      Get ISP Interrupt Flag
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will get ISP action interrupt status
 *
 */
#define FMC_GET_ISP_INT_FLAG()     ((FMC_ISP->ISPSTS & FMC_ISPSTS_INTFLAG_Msk) ? 1UL : 0UL) /*!< Get ISP interrupt flag Status */

/**
 * @brief      Clear ISP Interrupt Flag
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will clear ISP interrupt flag
 *
 */
#define FMC_CLEAR_ISP_INT_FLAG()     (FMC_ISP->ISPSTS = FMC_ISPSTS_INTFLAG_Msk) /*!< Clear ISP interrupt flag*/

/**
 * @brief      Enable Data Flash Scrambling Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will set SCRAMEN bit of DFCTL control register to enable Data Flash Scrambling Function.
 *
 */
#define FMC_ENABLE_SCRAMBLE()          (FMC->DFCTL |= FMC_DFCTL_SCRAMEN_Msk)  /*!< Enable Data Flash Scrambling Function  */

/**
 * @brief      Disable Data Flash Scrambling Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will clear SCRAMEN bit of DFCTL control register to disable Data Flash Scrambling Function.
 *
 */
#define FMC_DISABLE_SCRAMBLE()          (FMC->DFCTL &= ~FMC_DFCTL_SCRAMEN_Msk)  /*!< Disable Data Flash Scrambling Function  */

/**
 * @brief      Enable Data Flash Silent Access Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will set SILENTEN bit of DFCTL control register to enable Data Flash Silent Access Function.
 *
 */
#define FMC_ENABLE_SILENT()          (FMC->DFCTL |= FMC_DFCTL_SILENTEN_Msk)  /*!< Enable Data Flash Silent Access Function  */

/**
 * @brief      Disable Data Flash Silent Access Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will clear SILENTEN bit of DFCTL control register to disable Data Flash Silent Access Function.
 *
 */
#define FMC_DISABLE_SILENT()          (FMC->DFCTL &= ~FMC_DFCTL_SILENTEN_Msk)  /*!< Disable Data Flash Silent Access Function  */

/**
 * @brief      Enable Data Flash Temper Attack Program Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will set TMPCLR bit of DFCTL control register to enable Data Flash Temper Attack Program Function.
 *
 */
#define FMC_ENABLE_TMPCLR()          (FMC->DFCTL |= FMC_DFCTL_TMPCLR_Msk)  /*!< Enable Data Flash Temper Attack Program Function  */

/**
 * @brief      Disable Data Flash Temper Attack Program Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will clear TMPCLR bit of DFCTL control register to disable Data Flash Temper Attack Program Function.
 *
 */
#define FMC_DISABLE_TMPCLR()          (FMC->DFCTL &= ~FMC_DFCTL_TMPCLR_Msk)  /*!< Disable Data Flash Temper Attack Program Function  */

/**
 * @brief      Get Data Flash Temper Attack Programming Done Flag
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will get Data Flash Temper Attack Programming Done flag
 *
 */
#define FMC_GET_TMPCLRDONE_FLAG()     ((FMC->DFSTS & FMC_DFSTS_TMPCLRDONE_Msk) ? 1UL : 0UL) /*!< Get Data Flash Temper Attack Programming Done Flag */

/**
 * @brief      Get Data Flash Temper Attack Programming Busy Flag
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will get Data Flash Temper Attack Programming Busy flag
 *
 */
#define FMC_GET_TMPCLRBUSY_FLAG()     ((FMC->DFSTS & FMC_DFSTS_TMPCLRBUSY_Msk) ? 1UL : 0UL) /*!< Get Data Flash Temper Attack Programming Busy Flag */

/**
 * @brief      Clear Data Flash Temper Attack Programming Done Flag
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will clear Data Flash Temper Attack Programming Done flag
 *
 */
#define FMC_CLEAR_TMPCLRDONE_FLAG()     (FMC->DFSTS |= FMC_DFSTS_TMPCLRDONE_Msk)  /*!< Clear Data Flash Temper Attack Programming Done Flag */

/*---------------------------------------------------------------------------------------------------------*/
/* inline functions                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t FMC_ReadCID(void);
__STATIC_INLINE uint32_t FMC_ReadPID(void);
__STATIC_INLINE uint32_t FMC_ReadUID(uint8_t u8Index);
__STATIC_INLINE uint32_t FMC_ReadUCID(uint32_t u32Index);
__STATIC_INLINE void FMC_SetVectorPageAddr(uint32_t u32PageAddr);
__STATIC_INLINE uint32_t FMC_GetVECMAP(void);
__STATIC_INLINE void FMC_SetScrambleKey(uint32_t u32ScrambleKey);

/**
 * @brief       Get current vector mapping address.
 *
 * @param       None
 *
 * @return      The current vector mapping address.
 *
 * @details     To get VECMAP value which is the page address for remapping to vector page (0x0).
 *
 */
__STATIC_INLINE uint32_t FMC_GetVECMAP(void)
{
    return (FMC->ISPSTS & FMC_ISPSTS_VECMAP_Msk);
}

/**
  * @brief    Read company ID
  *
  * @param    None
  *
  * @return   The company ID (32-bit)
  *
  * @details  The company ID of Nuvoton is fixed to be 0xDA
  */
__STATIC_INLINE uint32_t FMC_ReadCID(void)
{
    FMC_ISP->ISPCMD = FMC_ISPCMD_READ_CID;           /* Set ISP Command Code */
    FMC_ISP->ISPADDR = 0x0u;                         /* Must keep 0x0 when read CID */
    FMC_ISP->ISPTRG = FMC_ISPTRG_ISPGO_Msk;          /* Trigger to start ISP procedure */
#if ISBEN
    __ISB();
#endif                                           /* To make sure ISP/CPU be Synchronized */
    while(FMC_ISP->ISPTRG & FMC_ISPTRG_ISPGO_Msk) {} /* Waiting for ISP Done */

    return FMC_ISP->ISPDAT;
}

/**
  * @brief    Read product ID
  *
  * @param    None
  *
  * @return   The product ID (32-bit)
  *
  * @details  This function is used to read product ID.
  */
__STATIC_INLINE uint32_t FMC_ReadPID(void)
{
    FMC_ISP->ISPCMD = FMC_ISPCMD_READ_DID;          /* Set ISP Command Code */
    FMC_ISP->ISPADDR = 0x04u;                       /* Must keep 0x4 when read PID */
    FMC_ISP->ISPTRG = FMC_ISPTRG_ISPGO_Msk;         /* Trigger to start ISP procedure */
#if ISBEN
    __ISB();
#endif                                          /* To make sure ISP/CPU be Synchronized */
    while(FMC_ISP->ISPTRG & FMC_ISPTRG_ISPGO_Msk) {} /* Waiting for ISP Done */

    return FMC_ISP->ISPDAT;
}


/**
 * @brief       Read Unique ID
 *
 * @param[in]   u8Index  UID index. 0 = UID[31:0], 1 = UID[63:32], 2 = UID[95:64]
 *
 * @return      The 32-bit unique ID data of specified UID index.
 *
 * @details     To read out 96-bit Unique ID.
 */
__STATIC_INLINE uint32_t FMC_ReadUID(uint8_t u8Index)
{
    FMC_ISP->ISPCMD = FMC_ISPCMD_READ_UID;
    FMC_ISP->ISPADDR = ((uint32_t)u8Index << 2u);
    FMC_ISP->ISPDAT = 0u;
    FMC_ISP->ISPTRG = 0x1u;
#if ISBEN
    __ISB();
#endif
    while(FMC_ISP->ISPTRG) {}

    return FMC_ISP->ISPDAT;
}

/**
  * @brief      To read UCID
  *
  * @param[in]  u32Index    Index of the UCID to read. u32Index must be 0, 1, 2, or 3.
  *
  * @return     The UCID of specified index
  *
  * @details    This function is used to read unique chip ID (UCID).
  */
__STATIC_INLINE uint32_t FMC_ReadUCID(uint32_t u32Index)
{
    FMC_ISP->ISPCMD = FMC_ISPCMD_READ_UID;            /* Set ISP Command Code */
    FMC_ISP->ISPADDR = (0x04u * u32Index) + 0x10u;    /* The UCID is at offset 0x10 with word alignment. */
    FMC_ISP->ISPTRG = FMC_ISPTRG_ISPGO_Msk;           /* Trigger to start ISP procedure */
#if ISBEN
    __ISB();
#endif                                            /* To make sure ISP/CPU be Synchronized */
    while(FMC_ISP->ISPTRG & FMC_ISPTRG_ISPGO_Msk) {}  /* Waiting for ISP Done */

    return FMC_ISP->ISPDAT;
}


/**
 * @brief       Set vector mapping address
 *
 * @param[in]   u32PageAddr  The page address to remap to address 0x0. The address must be page alignment.
 *
 * @return      To set VECMAP to remap specified page address to 0x0.
 *
 * @details     This function is used to set VECMAP to map specified page to vector page (0x0).
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

/**
 * @brief       Set Data Flash scrambling key
 *
 * @param[in]   u32ScramKey  The value of scrambling key.
 *
 * @return      NULL
 *
 * @details     This function is used to set Data Flash scrambling key.
 */
__STATIC_INLINE void FMC_SetScrambleKey(uint32_t u32ScrambleKey)
{
    FMC->SCRKEY = u32ScrambleKey;
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Functions                                                                                              */
/*---------------------------------------------------------------------------------------------------------*/

extern uint32_t  FMC_CheckAllOne(uint32_t u32addr, uint32_t u32count);
extern void FMC_Close(void);
extern int32_t FMC_ConfigXOM(uint32_t xom_num, uint32_t xom_base, uint8_t xom_page);
extern int32_t FMC_Erase(uint32_t u32PageAddr);
extern int32_t FMC_EraseBank(uint32_t u32BankAddr);
extern int32_t FMC_EraseXOM(uint32_t xom_num);
extern uint32_t  FMC_GetChkSum(uint32_t u32addr, uint32_t u32count);
extern int32_t FMC_IsOTPLocked(uint32_t otp_num);
extern int32_t FMC_GetXOMState(uint32_t xom_num);
extern int32_t FMC_LockOTP(uint32_t otp_num);
extern void FMC_Open(void);
extern uint32_t FMC_Read(uint32_t u32Addr);
extern int32_t FMC_Read64(uint32_t u32addr, uint32_t * u32data0, uint32_t * u32data1);
extern int32_t FMC_ReadOTP(uint32_t otp_num, uint32_t *low_word, uint32_t *high_word);
extern int32_t FMC_ReadConfig(uint32_t u32Config[], uint32_t u32Count);
extern void FMC_Write(uint32_t u32Addr, uint32_t u32Data);
extern int32_t FMC_Write8Bytes(uint32_t u32addr, uint32_t u32data0, uint32_t u32data1);
extern int32_t FMC_WriteConfig(uint32_t au32Config[], uint32_t u32Count);
extern int32_t FMC_WriteMultiple(uint32_t u32Addr, uint32_t pu32Buf[], uint32_t u32Len);
extern int32_t FMC_WriteOTP(uint32_t otp_num, uint32_t low_word, uint32_t high_word);
extern int32_t FMC_WriteMultipleA(uint32_t u32Addr, uint32_t pu32Buf[], uint32_t u32Len);
extern int32_t FMC_RemapBank(uint32_t u32Bank);

/**@}*/ /* end of group FMC_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group FMC_Driver */

/**@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_FMC_H__ */

