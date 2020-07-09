/**************************************************************************//**
 * @file     fmc.h
 * @version  V1.10
 * $Revision: 14 $
 * $Date: 15/11/20 9:55a $
 * @brief    NUC472/NUC442 Flash Memory Controller Driver Header File
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __FMC_H__
#define __FMC_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_FMC_Driver FMC Driver
  @{
*/


/** @addtogroup NUC472_442_FMC_EXPORTED_CONSTANTS FMC Exported Constants
  @{
*/


/*---------------------------------------------------------------------------------------------------------*/
/* Define Base Address                                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
#define FMC_APROM_BASE          0x00000000UL    /*!< APROM Base Address           \hideinitializer */
#define FMC_APROM_END           0x00080000UL    /*!< APROM End Address            \hideinitializer */
#define FMC_LDROM_BASE          0x00100000UL    /*!< LDROM Base Address           \hideinitializer */
#define FMC_LDROM_END           0x00104000UL    /*!< LDROM End Address            \hideinitializer */
#define FMC_CONFIG_BASE         0x00300000UL    /*!< User Configuration Address   \hideinitializer */

#define FMC_FLASH_PAGE_SIZE     0x800           /*!< Flash Page Size (2 Kbytes)   \hideinitializer */
#define FMC_LDROM_SIZE          0x4000          /*!< LDROM Size (16 Kbytes)       \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  ISPCMD constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define FMC_ISPCMD_READ         0x00            /*!< ISP Command: Read flash word          \hideinitializer */
#define FMC_ISPCMD_READ_64      0x40            /*!< ISP Command: Read flash double word   \hideinitializer */
#define FMC_ISPCMD_WRITE        0x21            /*!< ISP Command: Write flash word         \hideinitializer */
#define FMC_ISPCMD_WRITE_64     0x61            /*!< ISP Command: Write flash double word  \hideinitializer */
#define FMC_ISPCMD_PAGE_ERASE   0x22            /*!< ISP Command: Page Erase Flash         \hideinitializer */
#define FMC_ISPCMD_READ_CID     0x0B            /*!< ISP Command: Read Company ID          \hideinitializer */
#define FMC_ISPCMD_READ_PID     0x0C            /*!< ISP Command: Read ProductID           \hideinitializer */
#define FMC_ISPCMD_READ_UID     0x04            /*!< ISP Command: Read Unique ID           \hideinitializer */
#define ISP_ISPCMD_MULTI_WRITE  0x27            /*!< ISP Command: Multiple program         \hideinitializer */
#define FMC_ISPCMD_VECMAP       0x2E            /*!< ISP Command: Vector Page Remap        \hideinitializer */

#define IS_BOOT_FROM_APROM      0               /*!< Is booting from APROM                 \hideinitializer */
#define IS_BOOT_FROM_LDROM      1               /*!< Is booting from LDROM                 \hideinitializer */


/*@}*/ /* end of group NUC472_442_FMC_EXPORTED_CONSTANTS */



/** @addtogroup NUC472_442_FMC_EXPORTED_FUNCTIONS FMC Exported Functions
  @{
*/


/*---------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/

/**
  * @brief This macro selects booting from APROM.
  * @param None
  * @return None
  * \hideinitializer
  */
#define FMC_SET_APROM_BOOT()        (FMC->ISPCTL &= ~FMC_ISPCTL_BS_Msk)

/**
  * @brief This macro selects booting from LDROM.
  * @param None
  * @return None
  * \hideinitializer
  */
#define FMC_SET_LDROM_BOOT()        (FMC->ISPCTL |= FMC_ISPCTL_BS_Msk)

/**
  * @brief This macro enables APROM update function.
  * @param None
  * @return None
  * \hideinitializer
  */
#define FMC_ENABLE_AP_UPDATE()      (FMC->ISPCTL |=  FMC_ISPCTL_APUEN_Msk)

/**
  * @brief This macro disables APROM update function.
  * @param None
  * @return None
  * \hideinitializer
  */
#define FMC_DISABLE_AP_UPDATE()     (FMC->ISPCTL &= ~FMC_ISPCTL_APUEN_Msk)

/**
  * @brief This macro enables User Configuration update function.
  * @param None
  * @return None
  * \hideinitializer
  */
#define FMC_ENABLE_CFG_UPDATE()     (FMC->ISPCTL |=  FMC_ISPCTL_CFGUEN_Msk)

/**
  * @brief This macro disables User Configuration update function.
  * @param None
  * @return None
  * \hideinitializer
  */
#define FMC_DISABLE_CFG_UPDATE()    (FMC->ISPCTL &= ~FMC_ISPCTL_CFGUEN_Msk)

/**
  * @brief This macro enables LDROM update function.
  * @param None
  * @return None
  * \hideinitializer
  */
#define FMC_ENABLE_LD_UPDATE()      (FMC->ISPCTL |=  FMC_ISPCTL_LDUEN_Msk)

/**
  * @brief This macro disables LDROM update function.
  * @param None
  * @return None
  * \hideinitializer
  */
#define FMC_DISABLE_LD_UPDATE()     (FMC->ISPCTL &= ~FMC_ISPCTL_LDUEN_Msk)

/**
  * @brief This macro enables ISP function.
  * @param None
  * @return None
  * \hideinitializer
  */
#define FMC_ENABLE_ISP()            (FMC->ISPCTL |=  FMC_ISPCTL_ISPEN_Msk)      /*!< Enable ISP function         \hideinitializer */

/**
  * @brief This macro disables ISP function.
  * @param None
  * @return None
  * \hideinitializer
  */
#define FMC_DISABLE_ISP()           (FMC->ISPCTL &= ~FMC_ISPCTL_ISPEN_Msk)

/**
  * @brief This macro gets ISP fail flag value.
  * @param None
  * @return ISP fail flag value.
  * \hideinitializer
  */
#define FMC_GET_FAIL_FLAG()         ((FMC->ISPSTS & FMC_ISPSTS_ISPFF_Msk) ? 1 : 0)

/**
  * @brief This macro clears ISP fail flag.
  * @param None
  * @return None
  * \hideinitializer
  */
#define FMC_CLR_FAIL_FLAG()         (FMC->ISPSTS |= FMC_ISPSTS_ISPFF_Msk)       /*!< Clear ISP fail flag         \hideinitializer */




/*---------------------------------------------------------------------------------------------------------*/
/*  Functions                                                                                              */
/*---------------------------------------------------------------------------------------------------------*/

extern void FMC_Close(void);
extern int32_t FMC_Erase(uint32_t u32PageAddr);
extern int32_t FMC_GetBootSource(void);
extern void FMC_Open(void);
extern uint32_t FMC_Read(uint32_t u32Addr);
extern void FMC_Read_64(uint32_t u32Addr, uint32_t *u32Data0, uint32_t *u32Data1);
extern uint32_t FMC_ReadCID(void);
extern uint32_t FMC_ReadPID(void);
extern uint32_t FMC_ReadUCID(uint32_t u32Index);
extern uint32_t FMC_ReadUID(uint32_t u32Index);
extern uint32_t FMC_ReadDataFlashBaseAddr(void);
extern void FMC_SetVectorPageAddr(uint32_t u32PageAddr);
extern uint32_t FMC_GetVectorPageAddr(void);
extern void FMC_Write(uint32_t u32Addr, uint32_t u32Data);
extern void FMC_Write_64(uint32_t u32Addr, uint32_t u32Data0, uint32_t u32Data1);
extern int32_t FMC_ReadConfig(uint32_t *u32Config, uint32_t u32Count);
extern int32_t FMC_WriteConfig(uint32_t *u32Config, uint32_t u32Count);
extern uint32_t FMC_CRC8(uint32_t au32Data[], int i32Count);


/*@}*/ /* end of group NUC472_442_FMC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_FMC_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
