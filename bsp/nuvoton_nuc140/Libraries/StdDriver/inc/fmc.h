/**************************************************************************//**
 * @file     FMC.h
 * @version  V3.0
 * $Revision: 4 $
 * $Date: 15/05/19 3:44p $
 * @brief    Flash Memory Controller Driver Header File
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __FMC_H__
#define __FMC_H__


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
#define FMC_APROM_BASE          0x00000000UL    /*!< APROM  Base Address         */
#define FMC_LDROM_BASE          0x00100000UL    /*!< LDROM  Base Address         */
#define FMC_CONFIG_BASE         0x00300000UL    /*!< CONFIG Base Address         */

#define FMC_FLASH_PAGE_SIZE     0x200           /*!< Flash Page Size (512 Bytes) */
#define FMC_LDROM_SIZE          0x1000          /*!< LDROM Size (4K Bytes)       */

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


/*@}*/ /* end of group FMC_EXPORTED_CONSTANTS */

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
 * @details    This function will set ISPEN bit of ISPCON control register to enable ISP function.
 *
 */
#define FMC_ENABLE_ISP()          (FMC->ISPCON |=  FMC_ISPCON_ISPEN_Msk)


/**
 * @brief      Disable ISP Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will clear ISPEN bit of ISPCON control register to disable ISP function.
 *
 */
#define FMC_DISABLE_ISP()         (FMC->ISPCON &= ~FMC_ISPCON_ISPEN_Msk)


/**
 * @brief      Enable LDROM Update Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will set LDUEN bit of ISPCON control register to enable LDROM update function.
 *             User needs to set LDUEN bit before they can update LDROM.
 *
 */
#define FMC_ENABLE_LD_UPDATE()    (FMC->ISPCON |=  FMC_ISPCON_LDUEN_Msk)



/**
 * @brief      Disable LDROM Update Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will set ISPEN bit of ISPCON control register to disable LDROM update function.
 *
 */
#define FMC_DISABLE_LD_UPDATE()   (FMC->ISPCON &= ~FMC_ISPCON_LDUEN_Msk)  /*!< Disable LDROM Update Function  */



/**
 * @brief      Enable User Configuration Update Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will set CFGUEN bit of ISPCON control register to enable User Configuration update function.
 *             User needs to set CFGUEN bit before they can update User Configuration area.
 *
 */
#define FMC_ENABLE_CFG_UPDATE()   (FMC->ISPCON |=  FMC_ISPCON_CFGUEN_Msk)

/**
 * @brief      Disable User Configuration Update Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will clear CFGUEN bit of ISPCON control register to disable User Configuration update function.
 *
 */
#define FMC_DISABLE_CFG_UPDATE()  (FMC->ISPCON &= ~FMC_ISPCON_CFGUEN_Msk)           /*!< Disable CONFIG Update Function */


/**
 * @brief      Enable APROM Update Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will set APUEN bit of ISPCON control register to enable APROM update function.
 *             User needs to set APUEN bit before they can update APROM in APROM boot mode.
 *
 */
#define FMC_ENABLE_AP_UPDATE()    (FMC->ISPCON |=  FMC_ISPCON_APUEN_Msk)


/**
 * @brief      Disable APROM Update Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This function will clear APUEN bit of ISPCON control register to disable APROM update function.
 *
 */
#define FMC_DISABLE_AP_UPDATE()   (FMC->ISPCON &= ~FMC_ISPCON_APUEN_Msk)            /*!< Disable APROM Update Function  */

/**
 * @brief      Get ISP fail flag
 *
 * @param      None
 *
 * @retval     0 Previous ISP command execution result is successful
 * @retval     1 Previous ISP command execution result is fail
 *
 * @details    ISPFF flag of ISPCON is used to indicate ISP command success or fail.
 *             This function will return the ISPFF flag to identify ISP command OK or fail.
 *
 */
#define FMC_GET_FAIL_FLAG()       ((FMC->ISPCON & FMC_ISPCON_ISPFF_Msk) ? 1 : 0)


/**
 * @brief      Select booting from APROM
 *
 * @param      None
 *
 * @return     None
 *
 * @details    If MCU is working without IAP, user need to set BS bit of ISPCON and reset CPU to execute the code of LDROM/APROM.
 *             This function is used to set BS bit of ISPCON to boot to APROM.
 *
 * @note       To valid new BS bit setting, user also need to trigger CPU reset or System Reset Request after setting BS bit.
 *
 */
#define FMC_SET_APROM_BOOT()      (FMC->ISPCON &= ~FMC_ISPCON_BS_Msk)

/**
 * @brief      Select booting from APROM
 *
 * @param      None
 *
 * @return     None
 *
 * @details    If MCU is working without IAP, user need to set/clear BS bit of ISPCON and reset CPU to execute the code of APROM/LDROM.
 *             This function is used to clear BS bit of ISPCON to boot to LDROM.
 *
 * @note       To valid new BS bit setting, user also need to trigger CPU reset or System Reset Request after clear BS bit.
 *
 */
#define FMC_SET_LDROM_BOOT()      (FMC->ISPCON |= FMC_ISPCON_BS_Msk)


/*---------------------------------------------------------------------------------------------------------*/
/* inline functions                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
/**
 * @brief      Program 32-bit data into specified address of flash
 *
 * @param[in]  u32addr  Flash address include APROM, LDROM, Data Flash, and CONFIG
 * @param[in]  u32data  32-bit Data to program
 *
 * @return     None
 *
 * @details    To program word data into Flash include APROM, LDROM, Data Flash, and CONFIG.
 *             The corresponding functions in CONFIG are listed in FMC section of Technical Reference Manual.
 *
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
 * @retval      0 Success
 * @retval     -1 Erase failed
 *
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
        FMC->ISPCON |= FMC_ISPCON_ISPFF_Msk;
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
  * @param    None
  *
  * @return   The company ID (32-bit)
  *
  * @details  The company ID of Nuvoton is fixed to be 0xDA
  *
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
  * @brief    Read product ID
  *
  * @param    None
  *
  * @return   The product ID (32-bit)
  *
  * @details  This function is used to read product ID.
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
  * @return     The UCID of specified index
  *
  * @details    This function is used to read unique chip ID (UCID).
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
 * @param[in]   u32PageAddr  The page address to remap to address 0x0. The address must be page alignment.
 *
 * @return      None
 *
 * @details     This function is used to set VECMAP to map specified page to vector page (0x0).
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
 * @param       None
 *
 * @return      The current vector mapping address.
 *
 * @details     To get VECMAP value which is the page address for remapping to vector page (0x0).
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

/*@}*/ /* end of group FMC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group FMC_Driver */

/*@}*/ /* end of group Device_Driver */

#ifdef __cplusplus
}
#endif


#endif

