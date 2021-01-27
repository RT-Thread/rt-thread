/**
 **************************************************************************
 * File Name    : at32f4xx_flash.c
 * Description  : at32f4xx FMC source file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_flash.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup FLASH
  * @brief FLASH driver modules
  * @{
  */

/** @defgroup FLASH_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup FLASH_Private_Defines
  * @{
  */


/* Flash Control Register bits */
#define CTRL_PRGM_Set               ((uint32_t)0x00000001)
#define CTRL_PRGM_Rst               ((uint32_t)0xFFFFFFFE)
#define CTRL_PGERS_Set              ((uint32_t)0x00000002)
#define CTRL_PGERS_Rst              ((uint32_t)0xFFFFFFFD)
#define CTRL_CHPERS_Set             ((uint32_t)0x00000004)
#define CTRL_CHPERS_Rst             ((uint32_t)0xFFFFFFFB)
#define CTRL_UOBPRGM_Set            ((uint32_t)0x00000010)
#define CTRL_UOBPRGM_Rst            ((uint32_t)0xFFFFFFEF)
#define CTRL_UOBERS_Set             ((uint32_t)0x00000020)
#define CTRL_UOBERS_Rst             ((uint32_t)0xFFFFFFDF)
#define CTRL_STRT_Set               ((uint32_t)0x00000040)
#define CTRL_LCK_Set                ((uint32_t)0x00000080)
#define CTRL_UOBWE_Rst              ((uint32_t)0xFFFFFDFF)

/* FLASH Mask */
#define RDPRT_Mask                  ((uint32_t)0x00000002)
#define WRPRT0_Mask                 ((uint32_t)0x000000FF)
#define WRPRT1_Mask                 ((uint32_t)0x0000FF00)
#define WRPRT2_Mask                 ((uint32_t)0x00FF0000)
#define WRPRT3_Mask                 ((uint32_t)0xFF000000)
#define UOB_USR_BTOPT               ((uint16_t)0x0008)

#define OPTION_BYTE_PRT_Key         ((uint16_t)0x00CC)

/* FLASH Keys */
#define RDPRT_Key                   ((uint16_t)0x00A5)
#define FLASH_KEY1                  ((uint32_t)0x45670123)
#define FLASH_KEY2                  ((uint32_t)0xCDEF89AB)
#define SLIB_UNLOCK_KEY             ((uint32_t)0xA35F6D24)

/* FLASH BANK address */
#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
#define FLASH_BNK1_SIZE             ((uint32_t)0x80000)
#define FLASH_BNK1_END_ADDR         ((uint32_t)0x807FFFF)
#else
#define FLASH_BNK1_SIZE             ((*((uint32_t*)0x1FFFF7E0)) * 1024)
#define FLASH_BNK1_END_ADDR         (((uint32_t)0x8000000) + FLASH_BNK1_SIZE - 1)
#endif
#define FLASH_BNK2_END_ADDR         ((uint32_t)0x80FFFFF)
#define FLASH_BNK3_START_ADDR       ((uint32_t)0x8400000)
#if defined (AT32F415xx)
#define FLASH_SYSMEM_START_ADDR     ((uint32_t)0x1FFFAC00)
#define FLASH_SYSMEM_END_ADDR       ((uint32_t)0x1FFFF3FF)
#endif

/* Delay definition */
#define ERS_TIMEOUT                 ((uint32_t)0x10000000)
#define PRGM_TIMEOUT                ((uint32_t)0x0000F000)
#define EXT_FLASH_ERS_TIMEOUT       ((uint32_t)0xFFFFFFFF)
#define EXT_FLASH_PRGM_TIMEOUT      ((uint32_t)0x00080000)
/**
  * @}
  */

/** @defgroup FLASH_Private_Macros
  * @{
  */
#define IS_SYS_BOOTLOADER()       ((FLASH->SLIB_CDR0 & FLASH_SLIB_CDR0_BOOT_DIS) == 0x0)
#define IS_RDP_DISABLE()          (FLASH_GetReadProtectStatus() == RESET)
                                    
#define IS_MAIN_SLIB()             ((FLASH->SLIB_CDR0 & FLASH_SLIB_CDR0_SLIB_EN)? 1:0)
#define IS_SYS_SLIB()             ((FLASH->SLIB_CDR0 & FLASH_SLIB_CDR0_SYS_SLIB_EN)? TRUE:FALSE)
#define IS_SLIB_DISABLE()          (IS_MAIN_SLIB()? 0:1)
/**
  * @}
  */

/** @defgroup FLASH_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup FLASH_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup FLASH_Private_Functions
  * @{
  */

/**
  * @brief  Unlocks the FLASH Controller.
  * @note   This function can be used for all at32f4xx devices.
  *         - For AT32F4xx XL-Density devices this function unlocks Bank1 and Bank2.
  *         - For all other devices it unlocks Bank1 and it is equivalent
  *           to FLASH_UnlockBank1 function..
  * @param  None
  * @retval None
  */
void FLASH_Unlock(void)
{
  /* Authorize the FC of Bank1 Access */
  FLASH->FCKEY = FLASH_KEY1;
  FLASH->FCKEY = FLASH_KEY2;

#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
  /* Authorize the FC of Bank2 Access */
  FLASH->FCKEY2 = FLASH_KEY1;
  FLASH->FCKEY2 = FLASH_KEY2;
#endif
}
/**
  * @brief  Unlocks the FLASH Bank1 Controller.
  * @note   This function can be used for all at32f4xx devices.
  *         - For AT32F4xx XL-Density devices this function unlocks Bank1.
  *         - For all other devices it unlocks Bank1 and it is
  *           equivalent to FLASH_Unlock function.
  * @param  None
  * @retval None
  */
void FLASH_UnlockBank1(void)
{
  /* Authorize the FC of Bank1 Access */
  FLASH->FCKEY = FLASH_KEY1;
  FLASH->FCKEY = FLASH_KEY2;
}

#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
/**
  * @brief  Unlocks the FLASH Bank2 Controller.
  * @note   This function can be used only for AT32F4xx XL-Density devices.
  * @param  None
  * @retval None
  */
void FLASH_UnlockBank2(void)
{
  /* Authorize the FC of Bank2 Access */
  FLASH->FCKEY2 = FLASH_KEY1;
  FLASH->FCKEY2 = FLASH_KEY2;

}
#endif

#if !defined (AT32F415xx)
/**
  * @brief  Unlocks the FLASH Bank3 Controller for external flash.
  * @note   This function can not be used for AT32F415 devices.
  * @param  None
  * @retval None
  */
void FLASH_UnlockBank3(void)
{
  /* Authorize the FC of Bank3 Access */
  FLASH->FCKEY3 = FLASH_KEY1;
  FLASH->FCKEY3 = FLASH_KEY2;
}
#endif

/**
  * @brief  Locks the FLASH Controller.
  * @note   This function can be used for all at32f4xx devices.
  *         - For AT32F4xx XL-Density devices this function Locks Bank1 and Bank2.
  *         - For all other devices it Locks Bank1 and it is equivalent
  *           to FLASH_LockBank1 function.
  * @param  None
  * @retval None
  */
void FLASH_Lock(void)
{
  /* Set the Lock Bit to lock the FC and the CTRL of  Bank1 */
  FLASH->CTRL |= CTRL_LCK_Set;

#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
  /* Set the Lock Bit to lock the FC and the CTRL of  Bank2 */
  FLASH->CTRL2 |= CTRL_LCK_Set;
#endif
}

/**
  * @brief  Locks the FLASH Bank1 Controller.
  * @note   this function can be used for all at32f4xx devices.
  *         - For AT32F4xx XL-Density devices this function Locks Bank1.
  *         - For all other devices it Locks Bank1 and it is equivalent
  *           to FLASH_Lock function.
  * @param  None
  * @retval None
  */
void FLASH_LockBank1(void)
{
  /* Set the Lock Bit to lock the FC and the CTRL of  Bank1 */
  FLASH->CTRL |= CTRL_LCK_Set;
}

#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
/**
  * @brief  Locks the FLASH Bank2 Controller.
  * @note   This function can be used only for AT32F4xx XL-Density devices.
  * @param  None
  * @retval None
  */
void FLASH_LockBank2(void)
{
  /* Set the Lock Bit to lock the FC and the CTRL of  Bank2 */
  FLASH->CTRL2 |= CTRL_LCK_Set;
}
#endif

#if !defined (AT32F415xx)
/**
  * @brief  Locks the FLASH Bank3 Controller for external flash.
  * @note   This function can not be used for AT32F415 devices.
  * @param  None
  * @retval None
  */
void FLASH_LockBank3(void)
{
  /* Set the Lock Bit to lock the FC and the CTRL of  Bank3 */
  FLASH->CTRL3 |= CTRL_LCK_Set;
}
#endif

/**
  * @brief  Erases a specified FLASH page.
  * @note   This function can be used for all at32f4xx devices.
  * @param  Page_Address: The page address to be erased.
  * @retval FLASH Status: The returned value can be: FLASH_BSY, FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ErasePage(uint32_t Page_Address)
{
  FLASH_Status status = FLASH_PRC_DONE;
  /* Check the parameters */
  assert_param(IS_FLASH_ADDR(Page_Address));

#if !defined (AT32F415xx)
  /* BANK3 : External flash */
  if(Page_Address >= FLASH_BNK3_START_ADDR)
  {
    /* Wait for last process to be completed */
    status = FLASH_WaitForBank3Process(EXT_FLASH_ERS_TIMEOUT);

    if(status == FLASH_PRC_DONE)
    {
      /* if the previous process is completed, continue to erase the page */
      FLASH->CTRL3 |= CTRL_PGERS_Set;
      FLASH->ADDR3 = Page_Address;
      FLASH->CTRL3 |= CTRL_STRT_Set;

      /* Wait for last process to be completed */
      status = FLASH_WaitForBank3Process(EXT_FLASH_ERS_TIMEOUT);

      /* Disable the PGERS Bit */
      FLASH->CTRL3 &= CTRL_PGERS_Rst;
    }

    return status;
  }
#endif
#if defined (AT32F415xx)
  if(Page_Address >= FLASH_SYSMEM_START_ADDR && Page_Address <= FLASH_SYSMEM_END_ADDR)
  {
    /* Wait for last process to be completed */
    status = FLASH_WaitForProcess(ERS_TIMEOUT);

    if(status == FLASH_PRC_DONE)
    {
      /* if the previous process is completed, continue to erase the page */
      FLASH->CTRL |= CTRL_PGERS_Set;
      FLASH->ADDR = Page_Address;
      FLASH->CTRL |= CTRL_STRT_Set;

      /* Wait for last process to be completed */
      status = FLASH_WaitForProcess(ERS_TIMEOUT);

      /* Disable the PGERS Bit */
      FLASH->CTRL &= CTRL_PGERS_Rst;
    }
  }
#endif
  
  if(Page_Address <= FLASH_BNK1_END_ADDR)
  {
    /* Wait for last process to be completed */
    status = FLASH_WaitForBank1Process(ERS_TIMEOUT);

    if(status == FLASH_PRC_DONE)
    {
      /* if the previous process is completed, continue to erase the page */
      FLASH->CTRL |= CTRL_PGERS_Set;
      FLASH->ADDR = Page_Address;
      FLASH->CTRL |= CTRL_STRT_Set;

      /* Wait for last process to be completed */
      status = FLASH_WaitForBank1Process(ERS_TIMEOUT);

      /* Disable the PGERS Bit */
      FLASH->CTRL &= CTRL_PGERS_Rst;
    }
  }
#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
  else if((Page_Address > FLASH_BNK1_END_ADDR)&&(Page_Address <= FLASH_BNK2_END_ADDR))
  {
    /* Wait for last process to be completed */
    status = FLASH_WaitForBank2Process(ERS_TIMEOUT);

    if(status == FLASH_PRC_DONE)
    {
      /* if the previous process is completed, continue to erase the page */
      FLASH->CTRL2 |= CTRL_PGERS_Set;
      FLASH->ADDR2 = Page_Address;
      FLASH->CTRL2 |= CTRL_STRT_Set;

      /* Wait for last process to be completed */
      status = FLASH_WaitForBank2Process(ERS_TIMEOUT);

      /* Disable the PGERS Bit */
      FLASH->CTRL2 &= CTRL_PGERS_Rst;
    }
  }
#endif

  /* Return the Erase Status */
  return status;
}

/**
  * @brief  Erases all internal FLASH pages.
  * @note   This function can be used for all at32f4xx devices.
  *         This function will not erase external flash pages.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseAllPages(void)
{
  FLASH_Status status = FLASH_PRC_DONE;

#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
  /* Wait for last process to be completed */
  status = FLASH_WaitForBank1Process(ERS_TIMEOUT);

  if(status == FLASH_PRC_DONE)
  {
    /* if the previous process is completed, continue to erase all pages */
    FLASH->CTRL |= CTRL_CHPERS_Set;
    FLASH->CTRL |= CTRL_STRT_Set;

    /* Wait for last process to be completed */
    status = FLASH_WaitForBank1Process(ERS_TIMEOUT);

    /* Disable the CHPERS Bit */
    FLASH->CTRL &= CTRL_CHPERS_Rst;
  }

  if(status == FLASH_PRC_DONE)
  {
    /* if the previous process is completed, continue to erase all pages */
    FLASH->CTRL2 |= CTRL_CHPERS_Set;
    FLASH->CTRL2 |= CTRL_STRT_Set;

    /* Wait for last process to be completed */
    status = FLASH_WaitForBank2Process(ERS_TIMEOUT);

    /* Disable the CHPERS Bit */
    FLASH->CTRL2 &= CTRL_CHPERS_Rst;
  }

#else
  /* Wait for last process to be completed */
  status = FLASH_WaitForProcess(ERS_TIMEOUT);

  if(status == FLASH_PRC_DONE)
  {
    /* if the previous process is completed, continue to erase all pages */
    FLASH->CTRL |= CTRL_CHPERS_Set;
    FLASH->CTRL |= CTRL_STRT_Set;

    /* Wait for last process to be completed */
    status = FLASH_WaitForProcess(ERS_TIMEOUT);

    /* Disable the CHPERS Bit */
    FLASH->CTRL &= CTRL_CHPERS_Rst;
  }

#endif

  /* Return the Erase Status */
  return status;
}

/**
  * @brief  Erases all Bank1 FLASH pages.
  * @note   This function can be used for all at32f4xx devices.
  *         - For AT32F4xx XL-Density devices this function erases all Bank1 pages.
  *         - For all other devices it erases all Bank1 pages and it is equivalent
  *           to FLASH_EraseAllPages function.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseBank1AllPages(void)
{
  FLASH_Status status = FLASH_PRC_DONE;
  /* Wait for last process to be completed */
  status = FLASH_WaitForBank1Process(ERS_TIMEOUT);

  if(status == FLASH_PRC_DONE)
  {
    /* if the previous process is completed, continue to erase all pages */
    FLASH->CTRL |= CTRL_CHPERS_Set;
    FLASH->CTRL |= CTRL_STRT_Set;

    /* Wait for last process to be completed */
    status = FLASH_WaitForBank1Process(ERS_TIMEOUT);

    /* Disable the CHPERS Bit */
    FLASH->CTRL &= CTRL_CHPERS_Rst;
  }

  /* Return the Erase Status */
  return status;
}

#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
/**
  * @brief  Erases all Bank2 FLASH pages.
  * @note   This function can be used only for at32f4xx XL-Density devices.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseBank2AllPages(void)
{
  FLASH_Status status = FLASH_PRC_DONE;
  /* Wait for last process to be completed */
  status = FLASH_WaitForBank2Process(ERS_TIMEOUT);

  if(status == FLASH_PRC_DONE)
  {
    /* if the previous process is completed, continue to erase all pages */
    FLASH->CTRL2 |= CTRL_CHPERS_Set;
    FLASH->CTRL2 |= CTRL_STRT_Set;

    /* Wait for last process to be completed */
    status = FLASH_WaitForBank2Process(ERS_TIMEOUT);

    /* Disable the CHPERS Bit */
    FLASH->CTRL2 &= CTRL_CHPERS_Rst;
  }

  /* Return the Erase Status */
  return status;
}
#endif

#if !defined (AT32F415xx)
/**
  * @brief  Erases all Bank3 FLASH pages.
  * @note   This function can not be used for AT32F415 devices.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseBank3AllPages(void)
{
  FLASH_Status status = FLASH_PRC_DONE;
  if(FLASH_GetSlibState())
    return FLASH_PGRM_FLR;
  /* Wait for last process to be completed */
  status = FLASH_WaitForBank3Process(EXT_FLASH_ERS_TIMEOUT);

  if(status == FLASH_PRC_DONE)
  {
    /* if the previous process is completed, continue to erase all pages */
    FLASH->CTRL3 |= CTRL_CHPERS_Set;
    FLASH->CTRL3 |= CTRL_STRT_Set;

    /* Wait for last process to be completed */
    status = FLASH_WaitForBank3Process(EXT_FLASH_ERS_TIMEOUT);

    /* Disable the CHPERS Bit */
    FLASH->CTRL3 &= CTRL_CHPERS_Rst;
  }

  /* Return the Erase Status */
  return status;
}
#endif

/**
  * @brief  Erases the FLASH option bytes.
  * @note   This functions erases all option bytes except the Read protection (RDP).
  * @note   This function can be used for all at32f4xx devices.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseUserOptionBytes(void)
{
  uint16_t rdptmp = RDPRT_Key;

  FLASH_Status status = FLASH_PRC_DONE;

  /* Get the actual read protection Option Byte value */
  if(FLASH_GetReadProtectStatus() != RESET)
  {
    rdptmp = 0x00;
  }

  /* Wait for last process to be completed */
  status = FLASH_WaitForProcess(ERS_TIMEOUT);

  if(status == FLASH_PRC_DONE)
  {
    /* Authorize the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;

    /* if the previous process is completed, continue to erase the option bytes */
    FLASH->CTRL |= CTRL_UOBERS_Set;
    FLASH->CTRL |= CTRL_STRT_Set;
    /* Wait for last process to be completed */
    status = FLASH_WaitForProcess(ERS_TIMEOUT);

    if(status == FLASH_PRC_DONE)
    {
      /* if the erase process is completed, disable the UOBERS Bit */
      FLASH->CTRL &= CTRL_UOBERS_Rst;

      /* Enable the Option Bytes Programming process */
      FLASH->CTRL |= CTRL_UOBPRGM_Set;
      /* Restore the last read protection Option Byte value */
      UOPTB->RDPRT = (uint16_t)rdptmp;
      /* Wait for last process to be completed */
      status = FLASH_WaitForProcess(PRGM_TIMEOUT);

      if(status != FLASH_TIMEOUT)
      {
        /* if the program process is completed, disable the UOBPRGM Bit */
        FLASH->CTRL &= CTRL_UOBPRGM_Rst;
      }
    }
    else
    {
      if (status != FLASH_TIMEOUT)
      {
        /* Disable the UOBPRGM Bit */
        FLASH->CTRL &= CTRL_UOBPRGM_Rst;
      }
    }
  }

  /* Return the erase status */
  return status;
}

/**
  * @brief  Programs a word at a specified address.
  * @note   This function can be used for all at32f4xx devices.
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
  FLASH_Status status = FLASH_PRC_DONE;
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_FLASH_ADDR(Address));

#if !defined (AT32F415xx)
  if (Address >= FLASH_BNK3_START_ADDR)
  {
    /* Wait for last process to be completed */
    status = FLASH_WaitForBank3Process(PRGM_TIMEOUT);

    if(status == FLASH_PRC_DONE)
    {
      FLASH->CTRL3 |= CTRL_PRGM_Set;

      *(__IO uint32_t*) Address = Data;

      /* Wait for last process to be completed */
      status = FLASH_WaitForBank3Process(PRGM_TIMEOUT);

      /* Disable the PRGM Bit */
      FLASH->CTRL3 &= CTRL_PRGM_Rst;
    }

    return status;
  }
#endif
#if defined (AT32F415xx)
  if(Address >= FLASH_SYSMEM_START_ADDR && Address <= FLASH_SYSMEM_END_ADDR)
  {
    status = FLASH_WaitForProcess(PRGM_TIMEOUT);
    if(status == FLASH_PRC_DONE)
    {
      /* if the previous process is completed, continue to program the new data */
      FLASH->CTRL |= CTRL_PRGM_Set;

      *(__IO uint32_t*)Address = Data;
      /* Wait for last process to be completed */
      status = FLASH_WaitForProcess(PRGM_TIMEOUT);

      /* Disable the PRGM Bit */
      FLASH->CTRL &= CTRL_PRGM_Rst;
    }
  }
#endif  
  
  if(Address <= FLASH_BNK1_END_ADDR)
  {
    /* Wait for last process to be completed */
    status = FLASH_WaitForBank1Process(PRGM_TIMEOUT);

    if(status == FLASH_PRC_DONE)
    {
      FLASH->CTRL |= CTRL_PRGM_Set;

      *(__IO uint32_t*) Address = Data;

      /* Wait for last process to be completed */
      status = FLASH_WaitForProcess(PRGM_TIMEOUT);

      /* Disable the PRGM Bit */
      FLASH->CTRL &= CTRL_PRGM_Rst;
    }
  }
#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
  else if((Address > FLASH_BNK1_END_ADDR)&&(Address <= FLASH_BNK2_END_ADDR))
  {
    /* Wait for last process to be completed */
    status = FLASH_WaitForBank2Process(PRGM_TIMEOUT);

    if(status == FLASH_PRC_DONE)
    {
      FLASH->CTRL2 |= CTRL_PRGM_Set;

      *(__IO uint32_t*) Address = Data;

      /* Wait for last process to be completed */
      status = FLASH_WaitForBank2Process(PRGM_TIMEOUT);

      /* Disable the PRGM Bit */
      FLASH->CTRL2 &= CTRL_PRGM_Rst;
    }
  }
#endif

  /* Return the Program Status */
  return status;
}

/**
  * @brief  Programs a half word at a specified address.
  * @note   This function can be used for all at32f4xx devices.
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
  FLASH_Status status = FLASH_PRC_DONE;
  /* Check the parameters */
  assert_param(IS_FLASH_ADDR(Address));

#if !defined (AT32F415xx)
  if (Address >= FLASH_BNK3_START_ADDR)
  {
    /* Wait for last process to be completed */
    status = FLASH_WaitForBank3Process(PRGM_TIMEOUT);

    if(status == FLASH_PRC_DONE)
    {
      /* if the previous process is completed, continue to program the new data */
      FLASH->CTRL3 |= CTRL_PRGM_Set;

      *(__IO uint16_t*)Address = Data;
      /* Wait for last process to be completed */
      status = FLASH_WaitForBank3Process(PRGM_TIMEOUT);

      /* Disable the PRGM Bit */
      FLASH->CTRL3 &= CTRL_PRGM_Rst;
    }
    return status;
  }
#endif
#if defined (AT32F415xx)
  if(Address >= FLASH_SYSMEM_START_ADDR && Address <= FLASH_SYSMEM_END_ADDR)
  {
    status = FLASH_WaitForProcess(PRGM_TIMEOUT);
    if(status == FLASH_PRC_DONE)
    {
      /* if the previous process is completed, continue to program the new data */
      FLASH->CTRL |= CTRL_PRGM_Set;

      *(__IO uint16_t*)Address = Data;
      /* Wait for last process to be completed */
      status = FLASH_WaitForProcess(PRGM_TIMEOUT);

      /* Disable the PRGM Bit */
      FLASH->CTRL &= CTRL_PRGM_Rst;
    }
  }
#endif

  /* Wait for last process to be completed */
  if(Address <= FLASH_BNK1_END_ADDR)
  {
    status = FLASH_WaitForBank1Process(PRGM_TIMEOUT);
    if(status == FLASH_PRC_DONE)
    {
      /* if the previous process is completed, continue to program the new data */
      FLASH->CTRL |= CTRL_PRGM_Set;

      *(__IO uint16_t*)Address = Data;
      /* Wait for last process to be completed */
      status = FLASH_WaitForBank1Process(PRGM_TIMEOUT);

      /* Disable the PRGM Bit */
      FLASH->CTRL &= CTRL_PRGM_Rst;
    }
  }
#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
  else if((Address > FLASH_BNK1_END_ADDR)&&(Address <= FLASH_BNK2_END_ADDR))
  {
    status = FLASH_WaitForBank2Process(PRGM_TIMEOUT);
    if(status == FLASH_PRC_DONE)
    {
      /* if the previous process is completed, continue to program the new data */
      FLASH->CTRL2 |= CTRL_PRGM_Set;

      *(__IO uint16_t*)Address = Data;
      /* Wait for last process to be completed */
      status = FLASH_WaitForBank2Process(PRGM_TIMEOUT);

      /* Disable the PRGM Bit */
      FLASH->CTRL2 &= CTRL_PRGM_Rst;
    }
  }
#endif

  /* Return the Program Status */
  return status;
}

/**
  * @brief  Programs a byte at a specified address.
  * @note   This function can be used for all at32f4xx devices.
            This function cannot be used to program bank3.
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramByte(uint32_t Address, uint8_t Data)
{
  FLASH_Status status = FLASH_PRC_DONE;
  /* Check the parameters */
  assert_param(IS_FLASH_ADDR(Address));

#if !defined (AT32F415xx)
  if (Address >= FLASH_BNK3_START_ADDR)
  {
    /* This function cannot be used to program bank3 */
    return FLASH_WRPRT_FLR;
  }
#endif
#if defined (AT32F415xx)
  if(Address >= FLASH_SYSMEM_START_ADDR && Address <= FLASH_SYSMEM_END_ADDR)
  {
    status = FLASH_WaitForProcess(PRGM_TIMEOUT);
    if(status == FLASH_PRC_DONE)
    {
      /* if the previous process is completed, continue to program the new data */
      FLASH->CTRL |= CTRL_PRGM_Set;

      *(__IO uint8_t*)Address = Data;
      /* Wait for last process to be completed */
      status = FLASH_WaitForProcess(PRGM_TIMEOUT);

      /* Disable the PRGM Bit */
      FLASH->CTRL &= CTRL_PRGM_Rst;
    }
  }
#endif
  
  if(Address <= FLASH_BNK1_END_ADDR)
  {
    status = FLASH_WaitForBank1Process(PRGM_TIMEOUT);
    if(status == FLASH_PRC_DONE)
    {
      /* if the previous process is completed, continue to program the new data */
      FLASH->CTRL |= CTRL_PRGM_Set;

      *(__IO uint8_t*)Address = Data;
      /* Wait for last process to be completed */
      status = FLASH_WaitForBank1Process(PRGM_TIMEOUT);

      /* Disable the PRGM Bit */
      FLASH->CTRL &= CTRL_PRGM_Rst;
    }
  }
#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
  else if((Address > FLASH_BNK1_END_ADDR)&&(Address <= FLASH_BNK2_END_ADDR))
  {
    status = FLASH_WaitForBank2Process(PRGM_TIMEOUT);
    if(status == FLASH_PRC_DONE)
    {
      /* if the previous process is completed, continue to program the new data */
      FLASH->CTRL2 |= CTRL_PRGM_Set;

      *(__IO uint8_t*)Address = Data;
      /* Wait for last process to be completed */
      status = FLASH_WaitForBank2Process(PRGM_TIMEOUT);

      /* Disable the PRGM Bit */
      FLASH->CTRL2 &= CTRL_PRGM_Rst;
    }
  }  
#endif
  /* Return the Program Status */
  return status;
}

/**
  * @brief  Programs a half word at a specified Option Byte Data address.
  * @note   This function can be used for all at32f4xx devices.
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramUserOptionByteData(uint32_t Address, uint8_t Data)
{
  FLASH_Status status = FLASH_PRC_DONE;
  status = FLASH_WaitForProcess(PRGM_TIMEOUT);

  if(status == FLASH_PRC_DONE)
  {
    /* Authorize the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    /* Enables the Option Bytes Programming process */
    FLASH->CTRL |= CTRL_UOBPRGM_Set;
    *(__IO uint16_t*)Address = Data;

    /* Wait for last process to be completed */
    status = FLASH_WaitForProcess(PRGM_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* if the program process is completed, disable the UOBPRGM Bit */
      FLASH->CTRL &= CTRL_UOBPRGM_Rst;
    }
  }

  /* Return the Option Byte Data Program Status */
  return status;
}

/**
  * @brief  Write protects the desired pages
  * @note   This function can be used for all at32f4xx devices.
  * @param  FLASH_Pages: specifies the address of the pages to be write protected.
  *   This parameter can be:
  *     @arg For @b AT32F415xx devices: value between FLASH_WRPRT_PAGE_0to1 and
  *       FLASH_WRPRT_PAGE_60to61 or FLASH_WRPRT_PAGE_62to63 or FLASH_WRPRT_PAGE_62to127
  *     @arg For @b AT32F4xx Medium-density_devices: value between FLASH_WRPRT_PAGE_0to3 and
  *       FLASH_WRPRT_PAGE_60to63 or FLASH_WRPRT_PAGE_124to127
  *     @arg For @b AT32F4xx High-density_devices: value between FLASH_WRPRT_PAGE_0to1 and
  *       FLASH_WRPRT_PAGE_60to61 or FLASH_WRPRT_PAGE_62to127 or FLASH_WRPRT_PAGE_62to255
  *     @arg For @b AT32F4xx XL-density_devices: value between FLASH_WRPRT_PAGE_0to1 and
  *       FLASH_WRPRT_PAGE_60to61 or FLASH_WRPRT_PAGE_62to511
  *     @arg FLASH_WRPRT_AllPAGES
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EnableWriteProtect(uint32_t FLASH_Pages)
{
  uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;

  FLASH_Status status = FLASH_PRC_DONE;

  /* Check the parameters */
  assert_param(IS_FLASH_WRPRT_PAGES(FLASH_Pages));

  FLASH_Pages = (uint32_t)(~FLASH_Pages);
  WRP0_Data = (uint16_t)(FLASH_Pages & WRPRT0_Mask);
  WRP1_Data = (uint16_t)((FLASH_Pages & WRPRT1_Mask) >> 8);
  WRP2_Data = (uint16_t)((FLASH_Pages & WRPRT2_Mask) >> 16);
  WRP3_Data = (uint16_t)((FLASH_Pages & WRPRT3_Mask) >> 24);

  /* Wait for last process to be completed */
  status = FLASH_WaitForProcess(PRGM_TIMEOUT);

  if(status == FLASH_PRC_DONE)
  {
    /* Authorizes the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    FLASH->CTRL |= CTRL_UOBPRGM_Set;

    if(WRP0_Data != 0xFF)
    {
      UOPTB->WRPRT0 = WRP0_Data;

      /* Wait for last process to be completed */
      status = FLASH_WaitForProcess(PRGM_TIMEOUT);
    }

    if((status == FLASH_PRC_DONE) && (WRP1_Data != 0xFF))
    {
      UOPTB->WRPRT1 = WRP1_Data;

      /* Wait for last process to be completed */
      status = FLASH_WaitForProcess(PRGM_TIMEOUT);
    }

    if((status == FLASH_PRC_DONE) && (WRP2_Data != 0xFF))
    {
      UOPTB->WRPRT2 = WRP2_Data;

      /* Wait for last process to be completed */
      status = FLASH_WaitForProcess(PRGM_TIMEOUT);
    }

    if((status == FLASH_PRC_DONE) && (WRP3_Data != 0xFF))
    {
      UOPTB->WRPRT3 = WRP3_Data;

      /* Wait for last process to be completed */
      status = FLASH_WaitForProcess(PRGM_TIMEOUT);
    }

    if(status != FLASH_TIMEOUT)
    {
      /* if the program process is completed, disable the UOBPRGM Bit */
      FLASH->CTRL &= CTRL_UOBPRGM_Rst;
    }
  }

  /* Return the write protection process Status */
  return status;
}

/**
  * @brief  Enables or disables the read out protection.
  * @note   If the user has already programmed the other option bytes before calling
  *   this function, he must re-program them since this function erases all option bytes.
  * @note   This function can be used for all at32f4xx devices.
  * @param  Newstate: new state of the ReadOut Protection.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ReadProtectConfig(FunctionalState NewState)
{
  FLASH_Status status = FLASH_PRC_DONE;
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  status = FLASH_WaitForProcess(ERS_TIMEOUT);

  if(status == FLASH_PRC_DONE)
  {
    /* Authorizes the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    FLASH->CTRL |= CTRL_UOBERS_Set;
    FLASH->CTRL |= CTRL_STRT_Set;
    /* Wait for last process to be completed */
    status = FLASH_WaitForProcess(ERS_TIMEOUT);

    if(status == FLASH_PRC_DONE)
    {
      /* if the erase process is completed, disable the UOBERS Bit */
      FLASH->CTRL &= CTRL_UOBERS_Rst;
      /* Enable the Option Bytes Programming process */
      FLASH->CTRL |= CTRL_UOBPRGM_Set;

      if(NewState != DISABLE)
      {
        UOPTB->RDPRT = 0x00;
      }
      else
      {
        UOPTB->RDPRT = RDPRT_Key;
      }

      /* Wait for last process to be completed */
      status = FLASH_WaitForProcess(ERS_TIMEOUT);

      if(status != FLASH_TIMEOUT)
      {
        /* if the program process is completed, disable the UOBPRGM Bit */
        FLASH->CTRL &= CTRL_UOBPRGM_Rst;
      }
    }
    else
    {
      if(status != FLASH_TIMEOUT)
      {
        /* Disable the UOBERS Bit */
        FLASH->CTRL &= CTRL_UOBERS_Rst;
      }
    }
  }

  /* Return the protection process Status */
  return status;
}

/**
  * @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
  * @note   This function can be used for all at32f4xx devices.
  * @param  UOB_IWDG: Selects the IWDG mode
  *   This parameter can be one of the following values:
  *     @arg UOB_SW_IWDG: Software IWDG selected
  *     @arg UOB_HW_IWDG: Hardware IWDG selected
  * @param  UOB_STOP: Reset event when entering STOP mode.
  *   This parameter can be one of the following values:
  *     @arg UOB_NO_RST_STP: No reset generated when entering in STOP
  *     @arg UOB_RST_STP: Reset generated when entering in STOP
  * @param  UOB_STDBY: Reset event when entering Standby mode.
  *   This parameter can be one of the following values:
  *     @arg UOB_NO_RST_STDBY: No reset generated when entering in STANDBY
  *     @arg UOB_RST_STDBY: Reset generated when entering in STANDBY
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_UserOptionByteConfig(uint16_t UOB_IWDG, uint16_t UOB_STOP, uint16_t UOB_STDBY)
{
  FLASH_Status status = FLASH_PRC_DONE;

  /* Check the parameters */
  assert_param(IS_UOB_IWDG_CFG(UOB_IWDG));
  assert_param(IS_UOB_STOP_CFG(UOB_STOP));
  assert_param(IS_UOB_STDBY_CFG(UOB_STDBY));

  /* Authorize the small information block programming */
  FLASH->OPTKEYR = FLASH_KEY1;
  FLASH->OPTKEYR = FLASH_KEY2;

  /* Wait for last process to be completed */
  status = FLASH_WaitForProcess(PRGM_TIMEOUT);

  if(status == FLASH_PRC_DONE)
  {
    /* Enable the Option Bytes Programming process */
    FLASH->CTRL |= CTRL_UOBPRGM_Set;

    UOPTB->USR = UOB_IWDG | (uint16_t)(UOB_STOP | (uint16_t)(UOB_STDBY | ((uint16_t)0xF8)));

    /* Wait for last process to be completed */
    status = FLASH_WaitForProcess(PRGM_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* if the program process is completed, disable the UOBPRGM Bit */
      FLASH->CTRL &= CTRL_UOBPRGM_Rst;
    }
  }

  /* Return the Option Byte program Status */
  return status;
}

#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
/**
  * @brief  Configures to boot from Bank1 or Bank2.
  * @note   This function can be used only for at32f403_XL density devices.
  * @param  FLASH_BOOT: select the FLASH Bank to boot from.
  *   This parameter can be one of the following values:
  *     @arg FLASH_BOOT_FROM_BANK1: At startup, if boot pins are set in boot from user Flash
  *        position and this parameter is selected the device will boot from Bank1(Default).
  *     @arg FLASH_BOOT_FROM_BANK2: At startup, if boot pins are set in boot from user Flash
  *        position and this parameter is selected the device will boot from Bank2 or Bank1,
  *        depending on the activation of the bank. The active banks are checked in
  *        the following order: Bank2, followed by Bank1.
  *        The active bank is recognized by the value programmed at the base address
  *        of the respective bank (corresponding to the initial stack pointer value
  *        in the interrupt vector table).
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_BootOptConfig(uint16_t FLASH_BOOT)
{
  FLASH_Status status = FLASH_PRC_DONE;
  assert_param(IS_FLASH_BOOT_CFG(FLASH_BOOT));
  /* Authorize the small information block programming */
  FLASH->OPTKEYR = FLASH_KEY1;
  FLASH->OPTKEYR = FLASH_KEY2;

  /* Wait for last process to be completed */
  status = FLASH_WaitForProcess(PRGM_TIMEOUT);

  if(status == FLASH_PRC_DONE)
  {
    /* Enable the Option Bytes Programming process */
    FLASH->CTRL |= CTRL_UOBPRGM_Set;

    if(FLASH_BOOT == FLASH_BOOT_FROM_BANK1)
    {
      UOPTB->USR |= UOB_USR_BTOPT;
    }
    else
    {
      UOPTB->USR &= (uint16_t)(~(uint16_t)(UOB_USR_BTOPT));
    }

    /* Wait for last process to be completed */
    status = FLASH_WaitForProcess(PRGM_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* if the program process is completed, disable the UOBPRGM Bit */
      FLASH->CTRL &= CTRL_UOBPRGM_Rst;
    }
  }

  /* Return the Option Byte program Status */
  return status;
}
#endif

/**
  * @brief  Returns the FLASH User Option Bytes values.
  * @note   This function can be used for all at32f4xx devices.
  * @param  None
  * @retval The FLASH User Option Bytes values:IWDG_SW(Bit0), RST_STOP(Bit1)
  *         and RST_STDBY(Bit2).
  */
uint32_t FLASH_GetUserOptionByte(void)
{
  /* Return the User Option Byte */
  return (uint32_t)(FLASH->UOB >> 2);
}

/**
  * @brief  Returns the FLASH Write Protection Option Bytes Register value.
  * @note   This function can be used for all at32f4xx devices.
  * @param  None
  * @retval The FLASH Write Protection  Option Bytes Register value
  */
uint32_t FLASH_GetWriteProtectStatus(void)
{
  /* Return the Flash write protection Register value */
  return (uint32_t)(FLASH->WRPRT);
}

/**
  * @brief  Checks whether the FLASH Read Out Protection Status is set or not.
  * @note   This function can be used for all at32f4xx devices.
  * @param  None
  * @retval FLASH ReadOut Protection Status(SET or RESET)
  */
FlagStatus FLASH_GetReadProtectStatus(void)
{
  FlagStatus readoutstatus = RESET;

  if ((FLASH->UOB & RDPRT_Mask) != (uint32_t)RESET)
  {
    readoutstatus = SET;
  }
  else
  {
    readoutstatus = RESET;
  }

  return readoutstatus;
}

/**
  * @brief  Enables or disables the specified FLASH interrupts.
  * @note   This function can be used for all at32f4xx devices.
  *         - For AT32F4xx XL-Density devices, enables or disables the specified FLASH interrupts
              for Bank1 and Bank2.
  *         - For other devices it enables or disables the specified FLASH interrupts for Bank1.
  * @param  FLASH_INT: specifies the FLASH interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg FLASH_INT_FLR: FLASH Error Interrupt
  *     @arg FLASH_INT_PRCDN: FLASH end of process Interrupt
  * @param  NewState: new state of the specified Flash interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FLASH_INTConfig(uint32_t FLASH_INT, FunctionalState NewState)
{
#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
  /* Check the parameters */
  assert_param(IS_FLASH_INT(FLASH_INT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if((FLASH_INT & FLASH_INT_BANK2) != 0x0)
  {
    if(NewState != DISABLE)
    {
      /* Enable the interrupt sources */
      FLASH->CTRL2 |= (FLASH_INT & FLASH_INT_BANK2_MASK);
    }
    else
    {
      /* Disable the interrupt sources */
      FLASH->CTRL2 &= ~(uint32_t)(FLASH_INT & FLASH_INT_BANK2_MASK);
    }
  }
  else if((FLASH_INT & FLASH_INT_BANK3) != 0x0)
  {
    if(NewState != DISABLE)
    {
      /* Enable the interrupt sources */
      FLASH->CTRL3 |= (FLASH_INT & FLASH_INT_BANK3_MASK);
    }
    else
    {
      /* Disable the interrupt sources */
      FLASH->CTRL3 &= ~(uint32_t)(FLASH_INT & FLASH_INT_BANK3_MASK);
    }
  }
  else
  {
    if(NewState != DISABLE)
    {
      /* Enable the interrupt sources */
      FLASH->CTRL |= FLASH_INT;
    }
    else
    {
      /* Disable the interrupt sources */
      FLASH->CTRL &= ~(uint32_t)FLASH_INT;
    }
  }

#else
  /* Check the parameters */
  assert_param(IS_FLASH_INT(FLASH_INT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

#if !defined (AT32F415xx)
  if((FLASH_INT & FLASH_INT_BANK3) != 0x0)
  {
    if(NewState != DISABLE)
    {
      /* Enable the interrupt sources */
      FLASH->CTRL3 |= (FLASH_INT & FLASH_INT_BANK3_MASK);
    }
    else
    {
      /* Disable the interrupt sources */
      FLASH->CTRL3 &= ~(uint32_t)(FLASH_INT & FLASH_INT_BANK3_MASK);
    }
  }
  else
  {
    if(NewState != DISABLE)
    {
      /* Enable the interrupt sources */
      FLASH->CTRL |= FLASH_INT;
    }
    else
    {
      /* Disable the interrupt sources */
      FLASH->CTRL &= ~(uint32_t)FLASH_INT;
    }
  }
#else
  if(NewState != DISABLE)
  {
    /* Enable the interrupt sources */
    FLASH->CTRL |= FLASH_INT;
  }
  else
  {
      /* Disable the interrupt sources */
      FLASH->CTRL &= ~(uint32_t)FLASH_INT;
  }
#endif

#endif
}

/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @note   This function can be used for all at32f4xx devices.
  *         - For AT32F4xx XL-Density devices, this function checks whether the specified
  *           Bank1 or Bank2 flag is set or not.
  *         - For other devices, it checks whether the specified Bank1 flag is
  *           set or not.
  * @param  FLASH_FLAG: specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  *     @arg FLASH_FLAG_BSY: FLASH Busy flag
  *     @arg FLASH_FLAG_PRGMFLR: FLASH Program error flag
  *     @arg FLASH_FLAG_WRPRTFLR: FLASH Write protected error flag
  *     @arg FLASH_FLAG_PRCDN: FLASH End of Operation flag
  *     @arg FLASH_FLAG_UOBFLR:  FLASH Option Byte error flag
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG)
{
  FlagStatus bitstatus = RESET;

#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
  /* Check the parameters */
  assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG)) ;

  if(FLASH_FLAG == FLASH_FLAG_UOBFLR)
  {
    if((FLASH->UOB & FLASH_FLAG_UOBFLR) != (uint32_t)RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  else
  {
    if((FLASH_FLAG & FLASH_FLAG_BANK3) != 0x0)
    {
      if((FLASH->STS3 & FLASH_FLAG) != (uint32_t)RESET)
      {
        bitstatus = SET;
      }
      else
      {
        bitstatus = RESET;
      }
    }
    else if((FLASH_FLAG & FLASH_FLAG_BANK2) != 0x0)
    {
      if((FLASH->STS2 & FLASH_FLAG) != (uint32_t)RESET)
      {
        bitstatus = SET;
      }
      else
      {
        bitstatus = RESET;
      }
    }
    else
    {
      if((FLASH->STS & FLASH_FLAG) != (uint32_t)RESET)
      {
        bitstatus = SET;
      }
      else
      {
        bitstatus = RESET;
      }
    }
  }

#else
  /* Check the parameters */
  assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG)) ;

  if(FLASH_FLAG == FLASH_FLAG_UOBFLR)
  {
    if((FLASH->UOB & FLASH_FLAG_UOBFLR) != (uint32_t)RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  else
  {
#if !defined (AT32F415xx)
    if((FLASH_FLAG & FLASH_FLAG_BANK3) != 0x0)
    {
      if((FLASH->STS3 & FLASH_FLAG) != (uint32_t)RESET)
      {
        bitstatus = SET;
      }
      else
      {
        bitstatus = RESET;
      }
    }
    else
    {
      if((FLASH->STS & FLASH_FLAG) != (uint32_t)RESET)
      {
        bitstatus = SET;
      }
      else
      {
        bitstatus = RESET;
      }
    }
#else
   if((FLASH->STS & FLASH_FLAG) != (uint32_t)RESET)
   {
     bitstatus = SET;
   }
   else
   {
     bitstatus = RESET;
   }    
#endif
  }

#endif

  /* Return the new state of FLASH_FLAG (SET or RESET) */
  return bitstatus;
}

/**
  * @brief  Clears the FLASH's pending flags.
  * @note   This function can be used for all at32f4xx devices.
  *         - For AT32F4xx XL-Density devices, this function clears Bank1 or Bank2 pending flags
  *         - For other devices, it clears Bank1 pending flags.
  * @param  FLASH_FLAG: specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  *     @arg FLASH_FLAG_PRGMFLR: FLASH Program error flag
  *     @arg FLASH_FLAG_WRPRTFLR: FLASH Write protected error flag
  *     @arg FLASH_FLAG_PRCDN: FLASH End of Operation flag
  * @retval None
  */
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
  /* Check the parameters */
  assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG)) ;

  if((FLASH_FLAG & FLASH_FLAG_BANK3) != 0x0)
  {
    /* Clear the flags */
    FLASH->STS3 = FLASH_FLAG;
  }
  else if ((FLASH_FLAG  & FLASH_FLAG_BANK2) != 0x0)
  {
    /* Clear the flags */
    FLASH->STS2 = FLASH_FLAG;
  }
  else
  {
    /* Clear the flags */
    FLASH->STS = FLASH_FLAG;
  }

#else
  /* Check the parameters */
  assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG)) ;

#if !defined (AT32F415xx)
  if((FLASH_FLAG & FLASH_FLAG_BANK3) != 0x0)
  {
    /* Clear the flags */
    FLASH->STS3 = FLASH_FLAG;
  }
  else
  {
    /* Clear the flags */
    FLASH->STS = FLASH_FLAG;
  }
#else
  /* Clear the flags */
  FLASH->STS = FLASH_FLAG;  
#endif

#endif
}

/**
  * @brief  Returns the FLASH Status.
  * @note   This function can be used for all at32f4xx devices, it is equivalent
  *         to FLASH_GetBank1Status function.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_BSY, FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR or FLASH_PRC_DONE
  */
FLASH_Status FLASH_GetStatus(void)
{
  FLASH_Status flashstatus = FLASH_PRC_DONE;

  if((FLASH->STS & FLASH_FLAG_BSY) == FLASH_FLAG_BSY)
  {
    flashstatus = FLASH_BSY;
  }
  else if((FLASH->STS & FLASH_FLAG_PRGMFLR) != 0)
  {
    flashstatus = FLASH_PGRM_FLR;
  }
  else if((FLASH->STS & FLASH_FLAG_WRPRTFLR) != 0 )
  {
    flashstatus = FLASH_WRPRT_FLR;
  }
  else
  {
    flashstatus = FLASH_PRC_DONE;
  }

  /* Return the Flash Status */
  return flashstatus;
}

/**
  * @brief  Returns the FLASH Bank1 Status.
  * @note   This function can be used for all at32f4xx devices, it is equivalent
  *         to FLASH_GetStatus function.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_BSY, FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR or FLASH_PRC_DONE
  */
FLASH_Status FLASH_GetBank1Status(void)
{
  FLASH_Status flashstatus = FLASH_PRC_DONE;

  if((FLASH->STS & FLASH_FLAG_BNK1_BSY) == FLASH_FLAG_BSY)
  {
    flashstatus = FLASH_BSY;
  }
  else if((FLASH->STS & FLASH_FLAG_BNK1_PRGMFLR) != 0)
  {
    flashstatus = FLASH_PGRM_FLR;
  }
  else if((FLASH->STS & FLASH_FLAG_BNK1_WRPRTFLR) != 0 )
  {
    flashstatus = FLASH_WRPRT_FLR;
  }
  else
  {
    flashstatus = FLASH_PRC_DONE;
  }

  /* Return the Flash Status */
  return flashstatus;
}

#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
/**
  * @brief  Returns the FLASH Bank2 Status.
  * @note   This function can be used for at32f4xx XL-Density devices.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_BSY, FLASH_PGRM_FLR,
  *        FLASH_WRPRT_FLR or FLASH_PRC_DONE
  */
FLASH_Status FLASH_GetBank2Status(void)
{
  FLASH_Status flashstatus = FLASH_PRC_DONE;

  if((FLASH->STS2 & (FLASH_FLAG_BNK2_BSY & FLASH_INT_BANK2_MASK)) == (FLASH_FLAG_BNK2_BSY & FLASH_INT_BANK2_MASK))
  {
    flashstatus = FLASH_BSY;
  }
  else if((FLASH->STS2 & (FLASH_FLAG_BNK2_PRGMFLR & FLASH_INT_BANK2_MASK)) != 0)
  {
    flashstatus = FLASH_PGRM_FLR;
  }
  else if((FLASH->STS2 & (FLASH_FLAG_BNK2_WRPRTFLR & ~FLASH_INT_BANK2)) != 0 )
  {
    flashstatus = FLASH_WRPRT_FLR;
  }
  else
  {
    flashstatus = FLASH_PRC_DONE;
  }

  /* Return the Flash Status */
  return flashstatus;
}
#endif

#if !defined (AT32F415xx)
/**
  * @brief  Returns the FLASH Bank3 Status.
  * @note   This function can not be used for AT32F415 devices, it is equivalent
  *         to FLASH_GetStatus function.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_BSY, FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR or FLASH_PRC_DONE
  */
FLASH_Status FLASH_GetBank3Status(void)
{
  FLASH_Status flashstatus = FLASH_PRC_DONE;


  if((FLASH->STS3 & (FLASH_FLAG_BNK3_BSY & FLASH_INT_BANK3_MASK)) == (FLASH_FLAG_BNK3_BSY & FLASH_INT_BANK3_MASK))
  {
    flashstatus = FLASH_BSY;
  }
  else if((FLASH->STS3 & (FLASH_FLAG_BNK3_PRGMFLR & FLASH_INT_BANK3_MASK)) != 0)
  {
    flashstatus = FLASH_PGRM_FLR;
  }
  else if((FLASH->STS3 & (FLASH_FLAG_BNK3_WRPRTFLR & FLASH_INT_BANK3_MASK)) != 0 )
  {
    flashstatus = FLASH_WRPRT_FLR;
  }
  else
  {
    flashstatus = FLASH_PRC_DONE;
  }

  /* Return the Flash Status */
  return flashstatus;
}
#endif

/**
  * @brief  Waits for a Flash process to complete or a TIMEOUT to occur.
  * @note   This function can be used for all at32f4xx devices,
  *         it is equivalent to FLASH_WaitForBank1Process.
  *         - For AT32F4xx XL-Density devices this function waits for a Bank1 Flash process
  *           to complete or a TIMEOUT to occur.
  *         - For all other devices it waits for a Flash process to complete
  *           or a TIMEOUT to occur.
  * @param  Timeout: FLASH programming Timeout
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_WaitForProcess(uint32_t Timeout)
{
  FLASH_Status status = FLASH_PRC_DONE;

  /* Check for the Flash Status */
  status = FLASH_GetBank1Status();

  /* Wait for a Flash process to complete or a TIMEOUT to occur */
  while((status == FLASH_BSY) && (Timeout != 0x00))
  {
    status = FLASH_GetBank1Status();
    Timeout--;
  }

  if(Timeout == 0x00 )
  {
    status = FLASH_TIMEOUT;
  }

  /* Return the process status */
  return status;
}

/**
  * @brief  Waits for a Flash process on Bank1 to complete or a TIMEOUT to occur.
  * @note   This function can be used for all at32f4xx devices,
  *         it is equivalent to FLASH_WaitForProcess.
  * @param  Timeout: FLASH programming Timeout
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_WaitForBank1Process(uint32_t Timeout)
{
  FLASH_Status status = FLASH_PRC_DONE;

  /* Check for the Flash Status */
  status = FLASH_GetBank1Status();

  /* Wait for a Flash process to complete or a TIMEOUT to occur */
  while((status == FLASH_FLAG_BNK1_BSY) && (Timeout != 0x00))
  {
    status = FLASH_GetBank1Status();
    Timeout--;
  }

  if(Timeout == 0x00 )
  {
    status = FLASH_TIMEOUT;
  }

  /* Return the process status */
  return status;
}

#if defined(AT32F403Cx_XL) || defined(AT32F403Rx_XL) || defined(AT32F403Vx_XL) || defined(AT32F403Zx_XL) || \
    defined(AT32F403ACGU7) || defined(AT32F403ACGT7) || defined(AT32F403ARGT7) || defined(AT32F403AVGT7) || \
    defined(AT32F407RGT7)  || defined(AT32F407VGT7)
/**
  * @brief  Waits for a Flash process on Bank2 to complete or a TIMEOUT to occur.
  * @note   This function can be used only for at32f4xx XL-Density devices.
  * @param  Timeout: FLASH programming Timeout
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_WaitForBank2Process(uint32_t Timeout)
{
  FLASH_Status status = FLASH_PRC_DONE;

  /* Check for the Flash Status */
  status = FLASH_GetBank2Status();

  /* Wait for a Flash process to complete or a TIMEOUT to occur */
  while((status == (FLASH_FLAG_BNK2_BSY & FLASH_INT_BANK2_MASK)) && (Timeout != 0x00))
  {
    status = FLASH_GetBank2Status();
    Timeout--;
  }

  if(Timeout == 0x00 )
  {
    status = FLASH_TIMEOUT;
  }

  /* Return the process status */
  return status;
}
#endif

#if !defined (AT32F415xx)
/**
  * @brief  Waits for a Flash process on Bank3 to complete or a TIMEOUT to occur.
  * @note   This function can not be used for AT32F415 devices.
  * @param  Timeout: FLASH programming Timeout
  * @retval FLASH Status: The returned value can be: FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_WaitForBank3Process(uint32_t Timeout)
{
  FLASH_Status status = FLASH_PRC_DONE;

  /* Check for the Flash Status */
  status = FLASH_GetBank3Status();

  /* Wait for a Flash process to complete or a TIMEOUT to occur */
  while((status == (FLASH_FLAG_BNK3_BSY & FLASH_INT_BANK3_MASK)) && (Timeout != 0x00))
  {
    status = FLASH_GetBank3Status();
    Timeout--;
  }

  if(Timeout == 0x00 )
  {
    status = FLASH_TIMEOUT;
  }

  /* Return the process status */
  return status;
}
#endif

#if !defined (AT32F415xx)
/**
  * @brief To set the end address of encrypted data in BANK3.
  *        When the address is larger than this value, the writing data will be
  *        directly written to BANK3 without encryption.
  * @note   This function can not be used for AT32F415 devices.
  * @param EndAddress: The end address of encrypted data in BANK3
  * @retval: None
  */
void FLASH_Bank3EncEndAddrConfig(uint32_t EndAddress)
{
  assert_param(IS_IN_FLASH_BANK3_RANGE(EndAddress));
  if((UOPTB->BANK3SCRKEY[0]==0xFFFFFFFF) && (UOPTB->BANK3SCRKEY[1]==0xFFFFFFFF) && \
     (UOPTB->BANK3SCRKEY[2]==0xFFFFFFFF) && (UOPTB->BANK3SCRKEY[3]==0xFFFFFFFF))
    return;
  if((UOPTB->BANK3SCRKEY[0]==0xFF00FF00) && (UOPTB->BANK3SCRKEY[1]==0xFF00FF00) && \
     (UOPTB->BANK3SCRKEY[2]==0xFF00FF00) && (UOPTB->BANK3SCRKEY[3]==0xFF00FF00))
    return;  
  if((UOPTB->BANK3SCRKEY[0]==0x00FF00FF) && (UOPTB->BANK3SCRKEY[1]==0x00FF00FF) && \
     (UOPTB->BANK3SCRKEY[2]==0x00FF00FF) && (UOPTB->BANK3SCRKEY[3]==0x00FF00FF))
    return;
  FLASH->DA = EndAddress;
}
#endif

/**
  * @brief  Enable SLIB in Main Block
  * @note   This function can be used for all AT32F4xx devices.
  * @param  Psw: SLIB Password
  *         StartPage:SLIB Start Page
  *         DataPage: SLIB data Start Page
  *         EndPage:  SLIB End Page
  *         => SLIB Range = Page#N to Page#C
  * @retval FLASH Status: The returned value can be: FLASH_BSY, FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_SlibMainEnable(uint32_t Psw, uint16_t StartPage, uint16_t DataStartPage, uint16_t EndPage)
{
  uint32_t SlibRange;
  FLASH_Status Status = FLASH_PRC_DONE;

  assert_param(IS_SLIB_DISABLE());
  assert_param((Psw != 0xFFFFFFFF)&&(Psw != 0x00000000));
  assert_param((StartPage >= 1)&&(StartPage <= 127)); 
  assert_param((DataStartPage >= 1)&&(DataStartPage <= 127));
  assert_param((EndPage >= 1)&&(EndPage <= 127));

  /* Wait for last process to be completed */
  Status = FLASH_WaitForProcess(PRGM_TIMEOUT);
  /*check param limits*/
  if((StartPage>=DataStartPage) || ((DataStartPage>EndPage)&&(DataStartPage!=0x7FF)) || (StartPage>EndPage))
    return Status;
  
  SlibRange = ((uint32_t)DataStartPage<<11&FLASH_SLIB_DATA_START_PAGE) | ((uint32_t)EndPage<<22&FLASH_SLIB_END_PAGE) | ((uint32_t)StartPage&FLASH_SLIB_START_PAGE);

  if(Status == FLASH_PRC_DONE)
  {
      /* Unlock SLIB CFG register */
      FLASH->SLIB_KEYR = SLIB_UNLOCK_KEY;

      /* Configure SLIB, set PSW and RANGE */
      FLASH->SLIB_SET_PSW = Psw;
      Status = FLASH_WaitForProcess(PRGM_TIMEOUT);

      FLASH->SLIB_SET_RANGE = SlibRange;
      Status = FLASH_WaitForProcess(PRGM_TIMEOUT);
  }
  return Status;
}

/**
  * @brief  Disable SLIB when SLIB enabled
  * @note   This function can be used for all AT32F4xx devices.
  * @param  Psw: SLIB Password
  * @retval SUCCESS or ERROR
  */
uint32_t FLASH_SlibDisable(uint32_t Psw)
{
  FLASH_Status Status = FLASH_PRC_DONE;

  assert_param(!IS_SLIB_DISABLE());

  /* Write Password to disable SLIB */
  FLASH->SLIB_PSW = Psw;
  Status = FLASH_WaitForProcess(ERS_TIMEOUT);
  
  if(Status == FLASH_PRC_DONE)
  {
    if(FLASH->SLIB_PSW_STS & FLASH_SLIB_PSWSTS_PSW_OK)
      return SUCCESS;
    else
      return ERROR;
  }
  
  return ERROR;
}

#if !defined (AT32F415xx)
/**
 * @brief  Get the value of current remaining SLIB CFG count (range: 256~0)
 * @note   This function can not be used for AT32F415 devices.
 * @param  None 
 * @retval uint32_t
 */
uint32_t FLASH_GetSlibCurCnt(void)
{
  return ((FLASH->SLIB_PSW_STS & FLASH_SLIB_CNT) >> 16);
}
#endif

/**
  * @brief  Get the SLIB state
  * @note   This function can be used for all AT32F4xx devices.
  * @param  None
  * @retval ENABLE or DISABLE
  */
uint8_t FLASH_GetSlibState(void)
{
  if(FLASH->SLIB_CDR0&FLASH_SLIB_CDR0_SLIB_EN)
    return ENABLE;
  else
    return DISABLE;
}

/**
 * @brief  Get the start page of SLIB
 * @note   This function can be used for all AT32F4xx devices
 * @param  None
 * @retval uint16_t
 */
uint16_t FLASH_GetSlibStartPage(void)
{
  return (uint16_t)((FLASH->SLIB_CDR1&FLASH_SLIB_SET_START_PAGE)>>0);
}

/**
 * @brief  Get the data start page of SLIB
 * @note   This function can be used for all AT32F4xx devices
 * @param  None
 * @retval uint16_t
 */
uint16_t FLASH_GetSlibDataStartPage(void)
{
  return (uint16_t)((FLASH->SLIB_CDR1&FLASH_SLIB_SET_DATA_START_PAGE)>>11);
}

/**
 * @brief  Get the end page of SLIB
 * @note   This function can be used for all AT32F4xx devices
 * @param  None
 * @retval uint16_t
 */
uint16_t FLASH_GetSlibEndPage(void)
{
  return (uint16_t)((FLASH->SLIB_CDR1&FLASH_SLIB_SET_END_PAGE)>>22);
}

#if defined (AT32F415xx)
/**
  * @brief  Configure System Memory as AP mode
  * @note   This function can be used only for AT32F415 device.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_BSY, FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_SYS_AP(void)
{
  volatile FLASH_Status tStatus = FLASH_PRC_DONE;

  assert_param(IS_SLIB_DISABLE());
  assert_param(IS_RDP_DISABLE());

  if((FLASH->SLIB_CDR0 & FLASH_SLIB_CDR0_BOOT_DIS) == 0)
  {
    FLASH->SLIB_KEYR = SLIB_UNLOCK_KEY;
    while((FLASH->SLIB_PSW_STS & FLASH_SLIB_UNLOCK) == 0);
    FLASH->SYS_BOOT_DIS_SET = 0;
    tStatus = FLASH_WaitForProcess(PRGM_TIMEOUT);
  }
  return tStatus;
}
#endif /* AT32F415xx */

#if defined (AT32F415xx)
/**
  * @brief  Enable SLIB in System Memory
  * @note   This function can be used only for AT32F415 device.
  * @param  Psw: SLIB Password
  *         data_start_page: SLIB data Start Page
  * @retval FLASH Status: The returned value can be: FLASH_BSY, FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_SlibSysEnable(uint32_t Psw,uint8_t data_start_page)
{
  volatile FLASH_Status tStatus = FLASH_PRC_DONE;
  assert_param(IS_SLIB_DISABLE());

  /* Wait for last process to be completed */
  tStatus = FLASH_WaitForProcess(PRGM_TIMEOUT);
  /* Unlock SLIB CFG register */
  FLASH->SLIB_KEYR = SLIB_UNLOCK_KEY;
  while((FLASH->SLIB_PSW_STS & FLASH_SLIB_UNLOCK) == 0);
  
  /* make sure System Memory as AP mode */
  if(FLASH->SLIB_CDR0 & FLASH_SLIB_CDR0_BOOT_DIS)
  {
    FLASH->SYS_SLIB_SET = (data_start_page<<16)+0x5AA5;
    tStatus = FLASH_WaitForProcess(PRGM_TIMEOUT);
    FLASH->SLIB_SET_PSW = Psw;
    tStatus = FLASH_WaitForProcess(PRGM_TIMEOUT);
  }

  return tStatus;
}
#endif /* AT32F415xx */

#if defined (AT32F415xx)
/**
  * @brief  Check whether the option byte protection is set or not.
  * @note   This function can be used only for AT32F415 device.
  * @param  None
  * @retval Flash option byte protection status(SET or RESET)
  */
FlagStatus FLASH_GetOptionByteProtectStatus(void)
{
  FlagStatus status = RESET;
  
  if ((FLASH->UOB & FLASH_UOB_RDPRTEN) != (uint32_t)RESET)
  {
    if ((FLASH->UOB & FLASH_UOB_OPTION_BYTE_PRT_EN) != (uint32_t)RESET)
    {
      status = SET;
    }
  }
  
  return status;
}
#endif /* AT32F415xx */

#if defined (AT32F415xx)
/**
  * @brief  Configure the option byte protection.
  * @note   If the user has already programmed the other option bytes before calling
  *         this function, he must re-program them since this function erases all option bytes.
  * @note   This function can be used only for AT32F415 device.
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_BSY, FLASH_PGRM_FLR,
  *         FLASH_WRPRT_FLR, FLASH_PRC_DONE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_RDPandOptionByteProtectEnable(void)
{
  FLASH_Status status = FLASH_PRC_DONE;
  /* Check the parameters */

  status = FLASH_WaitForProcess(ERS_TIMEOUT);
    
  if(status == FLASH_PRC_DONE)
  {
    /* Unlock OTP2 */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;

    /* Erase OTP2 */
    FLASH->CTRL |= CTRL_UOBERS_Set;
    FLASH->CTRL |= CTRL_STRT_Set;
    status = FLASH_WaitForProcess(ERS_TIMEOUT);

    if(status == FLASH_PRC_DONE)
    {
      FLASH->CTRL &= CTRL_UOBERS_Rst;

      /* Program OTP2 */
      FLASH->CTRL |= CTRL_UOBPRGM_Set;      
      UOPTB->RDPRT = OPTION_BYTE_PRT_Key;
      status = FLASH_WaitForProcess(ERS_TIMEOUT);

      if(status != FLASH_TIMEOUT)
      {
        FLASH->CTRL &= CTRL_UOBPRGM_Rst;
      }
    }
    else
    {
      if(status != FLASH_TIMEOUT)
      {
        FLASH->CTRL &= CTRL_UOBERS_Rst;
      }
    }

    /* Disable OTP write enable bit */
    FLASH->CTRL &= CTRL_UOBWE_Rst;
  }
  return status;
}
#endif /* AT32F415xx */

#if defined (AT32F415xx)
/**
  * @brief  Disable the option byte protection.
  * @note   This function can be used only for AT32F415 device.
  * @param  None
  * @retval None
  */
void FLASH_OptionByteProtectDisable(void)
{
  volatile FLASH_Status tStatus = FLASH_PRC_DONE;

  if (FLASH_GetOptionByteProtectStatus() != SET) 
  {
    /* option byte protection is not set */
    return;
  }
  FLASH->CTRL |= FLASH_CTRL_OPTION_BYTE_PRT_DIS_TRIG;
  tStatus = FLASH_WaitForProcess(ERS_TIMEOUT);
}
#endif /* AT32F415xx */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

