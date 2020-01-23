/**
  ******************************************************************************
  * @file    md_fc.c
  * @brief   ES32F0271 FC Source File.
  *
  * @version V1.00.01
  * @date    day/mon/year
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include "md_syscfg.h"
#include "md_fc.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (FC)

/** @defgroup FC FC
  * @brief FC micro driver
  * @{
  */

/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/

/* Private constants ----------------------------------------------------------*/
/** @defgroup MD_FC_Private_Constants FC Private Constants
  * @{
  */

#define  REMAPDATA_BASE    ((     uint32_t)0x00000000) /*  FLASH Main  (64K Bytes)  */
#define  REMAPINFO_BASE    ((     uint32_t)0x00000000) /*  FLASH Info  ( 6K Bytes) - Boot Loader Memory  */

#define  EFOPT_PAGE6_OFFSET    (MD_FC_PC_EF_IPAGESZ*6)
#define  EFOPT_PAGE7_OFFSET    (MD_FC_PC_EF_IPAGESZ*7)
#define  EFOPT_PL1_OFFSET      (MD_FC_PC_EF_IPAGESZ*7+0x0)
#define  EFOPT_PL2_OFFSET      (MD_FC_PC_EF_IPAGESZ*6+0x28)
#define  EFOPT_REMAP_OFFSET    (MD_FC_PC_EF_IPAGESZ*7+0x8)

/**
  * @} MD_FC_Private_Constants
  */

/* Private function prototypes ------------------------------------------------*/

/* Public functions -----------------------------------------------------------*/
/** @defgroup MD_FC_Public_Functions FC Public Functions
  * @{
  */

/**
  * @brief  FC main erase.
  * @note  To prevent unexpected code branch, the main erase function must specify a dedicated main erase ID
  * @param  MEraseID Key for main erase, must be 0xA5A5AA55
  * @retval  An ErrorStatus enumeration value:
  *          - SUCCESS: Main flash erased
  *          - ERROR: Main erase ID mismatch
  */
ErrorStatus md_fc_merase(uint32_t MEraseID)
{
  ErrorStatus status = ERROR;

  /* Check the ID */
  if (MEraseID != MD_FC_PC_EF_MERASEID)
    return status;

  /* Write MERASE to CMD*/
  md_fc_set_fc_cmd(MD_FC_PC_CMD_MACRO_ERASE);

  status = SUCCESS;
  return status;
}

/**
  * @brief  FC Sector Erase
  * @note  To prevent unexpected code branch, the page erase function must specify the complement start address
  * @param  pSErasePara Pointer to structure md_fc_ControlTypeDef
  * @retval  An ErrorStatus enumeration value.
  *          - SUCCESS: Specified page address erased
  *          - ERROR: Complement of start address mismatch
  */
ErrorStatus md_fc_serase(md_fc_ControlTypeDef *pSErasePara)
{
  ErrorStatus status = ERROR;

  /* Check the start address and complement of start address*/
  if (pSErasePara->SAddr & pSErasePara->SAddrC)
    return status;

  /* Write sector address to PA*/
  md_fc_set_pa_prog_addr(pSErasePara->SAddr);
  /* Write SERASE to CMD*/
  md_fc_set_fc_cmd(MD_FC_PC_CMD_SECTOR_ERASE);

  status = SUCCESS;
  return status;
}

/**
  * @brief  FC Page Program
  * @note  To prevent unexpected code branch, the page program function must specify the complement start address
  * @param  pProgramPara Pointer to structure md_fc_ControlTypeDef
  * @retval An ErrorStatus enumeration value.
  *          - SUCCESS: Data in data buffer programed to specified page address
  *          - ERROR: Complement of start address mismatch
  */
ErrorStatus md_fc_program(md_fc_ControlTypeDef *pProgramPara)
{
  ErrorStatus status = ERROR;
  uint16_t  BCnt;

  md_fc_set_pa_pcnt(pProgramPara->BCnt);
  md_fc_set_pa_prog_addr(pProgramPara->SAddr);
  BCnt = pProgramPara->BCnt;
  BCnt >>= 3;

  while (BCnt--)
  {
    /* Check the start address and complement of start address*/
    if (pProgramPara->SAddr & pProgramPara->SAddrC)
      return status;

    /* Write lower 32bit program data to PLD*/
    md_fc_set_pld(*pProgramPara->pU32Buf++);
    /* Write higher 32bit program data to PHD*/
    md_fc_set_phd(*pProgramPara->pU32Buf++);
    /* Write PROGRAM to CMD*/
    md_fc_set_fc_cmd(MD_FC_PC_CMD_PROG_EFLASH);
  }

  status = SUCCESS;
  return status;
}

/**
  * @brief  FC Page Read
  * @param  pReadPara Pointer to structure md_fc_ControlTypeDef
  * @retval  Always return SUCCESS
  *         - Data in specified page address read to data buffer
  */
ErrorStatus  md_fc_read(md_fc_ControlTypeDef *pReadPara)
{
  ErrorStatus status = SUCCESS;
  uint32_t   *EFAddr;
  uint16_t  BCnt;

  if (md_syscfg_get_remap_memmod(SYSCFG) == MD_SYSCFG_MEMMOD_MAIN)  /*  Reamp from Main  */
    EFAddr = (uint32_t *)(REMAPDATA_BASE + pReadPara->SAddr);
  else
    EFAddr = (uint32_t *)(FLASH_BASE + pReadPara->SAddr);

  BCnt = pReadPara->BCnt;
  BCnt >>= 2;

  while (BCnt--)
    *pReadPara->pU32Buf++ = *EFAddr++;

  return status;
}

/**
  * @brief  FC Update Protect Level 1 Setting
  * @param  pUpdPL1Para Pointer to structure md_fc_UpdProtTypeDdef
  * @retval  Always return SUCCESS
  */
ErrorStatus  md_fc_updprotl1(md_fc_UpdProtTypeDef *pUpdPL1Para)
{
  ErrorStatus status = SUCCESS;
  uint32_t  EFProtL1L, EFProtL1H;

  EFProtL1L = FC->OP_PRT1L;
  EFProtL1H = FC->OP_PRT1H;

  if ((EFProtL1L == 0xffffffffUL) && (EFProtL1H == 0xffffffffUL)) /*  First Time to Set Level1  */
  {
    /* Write offset address to PA*/
    md_fc_set_pa_prog_addr(EFOPT_PL1_OFFSET);
    md_fc_enable_pa_ifren();
    /* Write lower 32bit update data to PLD*/
    md_fc_set_pld(pUpdPL1Para->UpdateL);
    /* Write higher 32bit update data to PHD*/
    md_fc_set_phd(pUpdPL1Para->UpdateH);

    /* Write PROGRAM to CMD*/
    md_fc_set_fc_cmd(MD_FC_PC_CMD_PROG_EFLASH);
  }
  else
  {
    /* Write lower 32bit clear data to PLD*/
    md_fc_set_pld(pUpdPL1Para->ClearL);
    /* Write higher 32bit clear data to PHD*/
    md_fc_set_phd(pUpdPL1Para->ClearH);

    /* Write lower 32bit data to UPL*/
    md_fc_set_upl(pUpdPL1Para->UpdateL);
    /* Write higher 32bit data to UPH*/
    md_fc_set_uph(pUpdPL1Para->UpdateH);

    /* Write UPDPL1 to CMD*/
    md_fc_set_fc_cmd(MD_FC_PC_CMD_UPDATE_LV1_PROTECT);
  }

  return status;
}

/**
  * @brief  FC Update Protect Level 2 Setting
  * @param  pUpdPL2Para Pointer to structure md_fc_UpdProtTypeDdef
  * @retval  Always return SUCCESS
  */
ErrorStatus  md_fc_updprotl2(md_fc_UpdProtTypeDef *pUpdPL2Para)
{
  ErrorStatus status = SUCCESS;
  uint32_t  EFProtL2L, EFProtL2H;

  EFProtL2L = FC->OP_PRT2L;
  EFProtL2H = FC->OP_PRT2H;

  if ((EFProtL2L == 0xffffffffUL) && (EFProtL2H == 0xffffffffUL)) /*  First Time to Set Level2  */
  {
    /* Write offset address to PA*/
    md_fc_set_pa_prog_addr(EFOPT_PL2_OFFSET);
    md_fc_enable_pa_ifren();
    /* Write lower 32bit update data to PLD*/
    md_fc_set_pld(pUpdPL2Para->UpdateL);
    /* Write higher 32bit update data to PHD*/
    md_fc_set_phd(pUpdPL2Para->UpdateH);

    /* Write PROGRAM to CMD*/
    md_fc_set_fc_cmd(MD_FC_PC_CMD_PROG_EFLASH);
  }
  else
  {
    /* Write lower 32bit clear data to PLD*/
    md_fc_set_pld(pUpdPL2Para->ClearL);
    /* Write higher 32bit clear data to PHD*/
    md_fc_set_phd(pUpdPL2Para->ClearH);

    /* Write lower 32bit data to UPL*/
    md_fc_set_upl(pUpdPL2Para->UpdateL);
    /* Write higher 32bit data to UPH*/
    md_fc_set_uph(pUpdPL2Para->UpdateH);

    /* Write UPDPL2 to CMD*/
    md_fc_set_fc_cmd(MD_FC_PC_CMD_UPDATE_LV2_PROTECT);
  }

  return status;
}

/**
  * @brief  FC Update Remap Option
  * @param  UpdRemap New remap setting value (remap address=valus(0x0~0xf)*0x1000, 0x10=BootLoader)
  * @retval  Always return SUCCESS
  */
ErrorStatus  md_fc_updremap(uint8_t UpdRemap)
{
  ErrorStatus status = SUCCESS;

  /* Write sector address to PA*/
  md_fc_enable_pa_ifren();
  md_fc_set_pa_prog_addr(EFOPT_PAGE7_OFFSET);
  /* Write SERASE to CMD*/
  md_fc_set_fc_cmd(MD_FC_PC_CMD_SECTOR_ERASE);
  /* Write remap offset address to PA*/
  md_fc_set_pa_prog_addr(EFOPT_REMAP_OFFSET);
  md_fc_enable_pa_ifren();
  /* Write lower 32bit remap data to PLD*/
  md_fc_set_pld(0xffffff00UL | UpdRemap);
  /* Write higher 32bit remap data to PHD*/
  md_fc_set_phd(0xffffffffUL);
  /* Write PROGRAM to CMD*/
  md_fc_set_fc_cmd(MD_FC_PC_CMD_PROG_EFLASH);

  return status;
}

/**
  * @} MD_FC_Public_Functions
  */

/**
  * @} FC
  */
#endif

/**
  * @} Micro_Driver
  */

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
