/**************************************************************************//**
 * @file     FMC.h
 * @version  V3.0
 * $Revision: 13 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 Series Flash Memory Controller Driver Header File
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __FMC_H__
#define __FMC_H__

#include "M051Series.h"

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_FMC_Driver FMC Driver
  @{
*/

/** @addtogroup M051_FMC_EXPORTED_CONSTANTS FMC Exported Constants
  @{
*/


/*---------------------------------------------------------------------------------------------------------*/
/* Define Base Address                                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
#define FMC_APROM_BASE          0x00000000UL    /*!< APROM  Base Address         */
#define FMC_LDROM_BASE          0x00100000UL    /*!< LDROM  Base Address         */
#define FMC_CONFIG_BASE         0x00300000UL    /*!< CONFIG Base Address         */

#define FMC_FLASH_PAGE_SIZE     0x200           /*!< Flash Page Size (512 Bytes) */
#define FMC_LDROM_SIZE          0x1000          /*!< LDROM Size (4 KBytes)       */

/*---------------------------------------------------------------------------------------------------------*/
/*  ISPCON constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define FMC_ISPCON_BS_LDROM     0x2     /*!< ISPCON setting to select to boot from LDROM */
#define FMC_ISPCON_BS_APROM     0x0     /*!< ISPCON setting to select to boot from APROM */

/*---------------------------------------------------------------------------------------------------------*/
/*  ISPCMD constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define FMC_ISPCMD_READ        0x00     /*!< ISP Command: Read Flash       */
#define FMC_ISPCMD_PROGRAM     0x21     /*!< ISP Command: Program Flash    */
#define FMC_ISPCMD_PAGE_ERASE  0x22     /*!< ISP Command: Page Erase Flash */
#define FMC_ISPCMD_VECMAP      0x2e     /*!< ISP Command: Set VECMAP       */
#define FMC_ISPCMD_READ_UID    0x04     /*!< ISP Command: Read Unique ID   */
#define FMC_ISPCMD_READ_CID    0x0B     /*!< ISP Command: Read Company ID   */
#define FMC_ISPCMD_READ_DID    0x0C     /*!< ISP Command: Read Device ID    */


/*@}*/ /* end of group M051_FMC_EXPORTED_CONSTANTS */

/** @addtogroup M051_FMC_EXPORTED_FUNCTIONS FMC Exported Functions
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  FMC Macro Definitions                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
#define FMC_ENABLE_ISP()          (FMC->ISPCON |=  FMC_ISPCON_ISPEN_Msk)  /*!< Enable ISP Function  */
#define FMC_DISABLE_ISP()         (FMC->ISPCON &= ~FMC_ISPCON_ISPEN_Msk)  /*!< Disable ISP Function */
#define FMC_ENABLE_LD_UPDATE()    (FMC->ISPCON |=  FMC_ISPCON_LDUEN_Msk)  /*!< Enable LDROM Update Function   */
#define FMC_DISABLE_LD_UPDATE()   (FMC->ISPCON &= ~FMC_ISPCON_LDUEN_Msk)  /*!< Disable LDROM Update Function  */
#define FMC_ENABLE_CFG_UPDATE()   (FMC->ISPCON |=  FMC_ISPCON_CFGUEN_Msk) /*!< Enable CONFIG Update Function  */
#define FMC_DISABLE_CFG_UPDATE()  (FMC->ISPCON &= ~FMC_ISPCON_CFGUEN_Msk) /*!< Disable CONFIG Update Function */
#define FMC_ENABLE_AP_UPDATE()    (FMC->ISPCON |=  FMC_ISPCON_APUEN_Msk)  /*!< Enable APROM Update Function   */
#define FMC_DISABLE_AP_UPDATE()   (FMC->ISPCON &= ~FMC_ISPCON_APUEN_Msk)  /*!< Disable APROM Update Function  */
#define FMC_GET_FAIL_FLAG()       ((FMC->ISPCON & FMC_ISPCON_ISPFF_Msk) ? 1 : 0)  /*!< Get ISP fail flag  */
#define FMC_SET_APROM_BOOT()      (FMC->ISPCON &= ~FMC_ISPCON_BS_Msk)     /*!< Select booting from APROM  */
#define FMC_SET_LDROM_BOOT()      (FMC->ISPCON |= FMC_ISPCON_BS_Msk)      /*!< Select booting from LDROM  */


/*---------------------------------------------------------------------------------------------------------*/
/* inline functions                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
/**
 * @brief      Program 32-bit data into specified address of flash
 *
 * @param[in]  u32addr  Flash address include APROM, LDROM, Data Flash, and CONFIG
 * @param[in]  u32data  32-bit Data to program
 *
 * @details    To program word data into Flash include APROM, LDROM, Data Flash, and CONFIG.
 *             The corresponding functions in CONFIG are listed in FMC section of Technical Reference Manual.
 *
 * @note
 *             Please make sure that Register Write-Protection Function has been disabled
 *             before using this function.
 */
static __INLINE void FMC_Write(uint32_t u32addr, uint32_t u32data)
{
    FMC->ISPCMD = FMC_ISPCMD_PROGRAM;   /* Set ISP Command Code */
    FMC->ISPADR = u32addr;              /* Set Target ROM Address. The address must be word alignment. */
    FMC->ISPDAT = u32data;              /* Set Data to Program */
    FMC->ISPTRG = 0x1;                  /* Trigger to start ISP procedure */
    __ISB();                            /* To make sure ISP/CPU be Synchronized */
    while(FMC->ISPTRG);                 /* Waiting for ISP Done */
}

/**
 * @brief       Read 32-bit Data from specified address of flash
 *
 * @param[in]   u32addr  Flash address include APROM, LDROM, Data Flash, and CONFIG
 *
 * @return      The data of specified address
 *
 * @details     To read word data from Flash include APROM, LDROM, Data Flash, and CONFIG.
 *
 * @note
 *              Please make sure that Register Write-Protection Function has been disabled
 *              before using this function.
 */
static __INLINE uint32_t FMC_Read(uint32_t u32addr)
{
    FMC->ISPCMD = FMC_ISPCMD_READ; /* Set ISP Command Code */
    FMC->ISPADR = u32addr;         /* Set Target ROM Address. The address must be word alignment. */
    FMC->ISPTRG = 0x1;             /* Trigger to start ISP procedure */
    __ISB();                       /* To make sure ISP/CPU be Synchronized */
    while(FMC->ISPTRG);            /* Waiting for ISP Done */

    return FMC->ISPDAT;
}


/**
 * @brief      Flash page erase
 *
 * @param[in]  u32addr  Flash address including APROM, LDROM, Data Flash, and CONFIG
 *
 * @details    To do flash page erase. The target address could be APROM, LDROM, Data Flash, or CONFIG.
 *             The page size is 512 bytes.
 *
 * @retval      0: Success
 * @retval     -1: Erase failed
 *
 * @note
 *             Please make sure that Register Write-Protection Function has been disabled
 *             before using this function.
 */
static __INLINE int32_t FMC_Erase(uint32_t u32addr)
{
    FMC->ISPCMD = FMC_ISPCMD_PAGE_ERASE; /* Set ISP Command Code */
    FMC->ISPADR = u32addr;               /* Set Target ROM Address. The address must be page alignment. */
    FMC->ISPTRG = 0x1;                   /* Trigger to start ISP procedure */
    __ISB();                             /* To make sure ISP/CPU be Synchronized */
    while(FMC->ISPTRG);                  /* Waiting for ISP Done */

    /* Check ISPFF flag to know whether erase OK or fail. */
    if(FMC->ISPCON & FMC_ISPCON_ISPFF_Msk)
    {
        FMC->ISPCON = FMC_ISPCON_ISPFF_Msk;
        return -1;
    }
    return 0;
}

/**
 * @brief       Read Unique ID
 *
 * @param[in]   u8index  UID index. 0 = UID[31:0], 1 = UID[63:32], 2 = UID[95:64]
 *
 * @return      The 32-bit unique ID data of specified UID index.
 *
 * @details     To read out 96-bit Unique ID.
 *
 * @note
 *              Please make sure that Register Write-Protection Function has been disabled
 *              before using this function.
 */
static __INLINE uint32_t FMC_ReadUID(uint8_t u8index)
{
    FMC->ISPCMD = FMC_ISPCMD_READ_UID; /* Set ISP Command Code */
    FMC->ISPADR = (u8index << 2);      /* Set UID Address. It must be word alignment. */
    FMC->ISPTRG = 0x1;                 /* Trigger to start ISP procedure */
    __ISB();                           /* To make sure ISP/CPU be Synchronized */
    while(FMC->ISPTRG);                /* Waiting for ISP Done */

    return FMC->ISPDAT;
}


/**
  * @brief    Read company ID
  *
  * @retval   The company ID (32-bit)
  *
  * @details  The company ID of Nuvoton is fixed to be 0xDA
  */
static __INLINE uint32_t FMC_ReadCID(void)
{
    FMC->ISPCMD = FMC_ISPCMD_READ_CID;           /* Set ISP Command Code */
    FMC->ISPADR = 0x0;                           /* Must keep 0x0 when read CID */
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;          /* Trigger to start ISP procedure */
    __ISB();                                     /* To make sure ISP/CPU be Synchronized */
    while(FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) ;  /* Waiting for ISP Done */

    return FMC->ISPDAT;
}


/**
  * @brief    Read device ID
  *
  * @retval   The device ID (32-bit)
  *
  */
static __INLINE uint32_t FMC_ReadDID(void)
{
    FMC->ISPCMD = FMC_ISPCMD_READ_DID;          /* Set ISP Command Code */
    FMC->ISPADR = 0;                            /* Must keep 0x0 when read DID */
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;         /* Trigger to start ISP procedure */
    __ISB();                                    /* To make sure ISP/CPU be Synchronized */
    while(FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk);  /* Waiting for ISP Done */

    return FMC->ISPDAT;
}



/**
  * @brief    Read product ID
  *
  * @retval   The product ID (32-bit)
  *
  */
static __INLINE uint32_t FMC_ReadPID(void)
{
    FMC->ISPCMD = FMC_ISPCMD_READ_DID;          /* Set ISP Command Code */
    FMC->ISPADR = 0x04;                         /* Must keep 0x4 when read PID */
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;         /* Trigger to start ISP procedure */
    __ISB();                                    /* To make sure ISP/CPU be Synchronized */
    while(FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk);  /* Waiting for ISP Done */

    return FMC->ISPDAT;
}

/**
  * @brief      To read UCID
  *
  * @param[in]  u32Index    Index of the UCID to read. u32Index must be 0, 1, 2, or 3.
  *
  * @retval     The UCID of specified index
  *
  */
static __INLINE uint32_t FMC_ReadUCID(uint32_t u32Index)
{
    FMC->ISPCMD = FMC_ISPCMD_READ_UID;          /* Set ISP Command Code */
    FMC->ISPADR = (0x04 * u32Index) + 0x10;     /* The UCID is at offset 0x10 with word alignment. */
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;         /* Trigger to start ISP procedure */
    __ISB();                                    /* To make sure ISP/CPU be Synchronized */
    while(FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk);  /* Waiting for ISP Done */

    return FMC->ISPDAT;
}



/**
 * @brief       Set vector mapping address
 *
 * @param[in]   u32MapAddr  The page address to remap to address 0x0. The address must be page alignment.
 *
 * @details     To set VECMAP to remap specified page address to 0x0.
 *
 * @note
 *              VECMAP only valid when new IAP function is enabled. (CBS = 10'b or 00'b)
 *
 */
static __INLINE void FMC_SetVectorPageAddr(uint32_t u32PageAddr)
{
    FMC->ISPCMD = FMC_ISPCMD_VECMAP; /* Set ISP Command Code */
    FMC->ISPADR = u32PageAddr;       /* The address of specified page which will be map to address 0x0. It must be page alignment. */
    FMC->ISPTRG = 0x1;               /* Trigger to start ISP procedure */
    __ISB();                         /* To make sure ISP/CPU be Synchronized */
    while(FMC->ISPTRG);              /* Waiting for ISP Done */
}


/**
 * @brief       Get current vector mapping address.
 *
 * @return      The current vector mapping address.
 *
 * @details     To get VECMAP value which is the page address for remapping to 0x0.
 *
 * @note
 *              VECMAP only valid when new IAP function is enabled. (CBS = 10'b or 00'b)
 *
 */
static __INLINE uint32_t FMC_GetVECMAP(void)
{
    return (FMC->ISPSTA & FMC_ISPSTA_VECMAP_Msk);
}

extern void FMC_Open(void);
extern void FMC_Close(void);
extern void FMC_EnableAPUpdate(void);
extern void FMC_DisableAPUpdate(void);
extern void FMC_EnableConfigUpdate(void);
extern void FMC_DisableConfigUpdate(void);
extern void FMC_EnableLDUpdate(void);
extern void FMC_DisableLDUpdate(void);
extern int32_t FMC_ReadConfig(uint32_t *u32Config, uint32_t u32Count);
extern int32_t FMC_WriteConfig(uint32_t *u32Config, uint32_t u32Count);
extern void FMC_SetBootSource(int32_t i32BootSrc);
extern int32_t FMC_GetBootSource(void);
extern uint32_t FMC_ReadDataFlashBaseAddr(void);

/*@}*/ /* end of group M051_FMC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_FMC_Driver */

/*@}*/ /* end of group M051_Device_Driver */

#ifdef __cplusplus
}
#endif


#endif

