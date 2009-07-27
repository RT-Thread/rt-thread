/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : stm32f10x_flash.c
* Author             : MCD Application Team
* Version            : V2.0.3Patch1
* Date               : 04/06/2009
* Description        : This file provides all the FLASH firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_flash.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Flash Access Control Register bits */
#define ACR_LATENCY_Mask         ((u32)0x00000038)
#define ACR_HLFCYA_Mask          ((u32)0xFFFFFFF7)
#define ACR_PRFTBE_Mask          ((u32)0xFFFFFFEF)

#ifdef _FLASH_PROG
/* Flash Access Control Register bits */
#define ACR_PRFTBS_Mask          ((u32)0x00000020)

/* Flash Control Register bits */
#define CR_PG_Set                ((u32)0x00000001)
#define CR_PG_Reset              ((u32)0x00001FFE)

#define CR_PER_Set               ((u32)0x00000002)
#define CR_PER_Reset             ((u32)0x00001FFD)

#define CR_MER_Set               ((u32)0x00000004)
#define CR_MER_Reset             ((u32)0x00001FFB)

#define CR_OPTPG_Set             ((u32)0x00000010)
#define CR_OPTPG_Reset           ((u32)0x00001FEF)

#define CR_OPTER_Set             ((u32)0x00000020)
#define CR_OPTER_Reset           ((u32)0x00001FDF)

#define CR_STRT_Set              ((u32)0x00000040)

#define CR_LOCK_Set              ((u32)0x00000080)

/* FLASH Mask */
#define RDPRT_Mask               ((u32)0x00000002)
#define WRP0_Mask                ((u32)0x000000FF)
#define WRP1_Mask                ((u32)0x0000FF00)
#define WRP2_Mask                ((u32)0x00FF0000)
#define WRP3_Mask                ((u32)0xFF000000)

/* FLASH Keys */
#define RDP_Key                  ((u16)0x00A5)
#define FLASH_KEY1               ((u32)0x45670123)
#define FLASH_KEY2               ((u32)0xCDEF89AB)

/* Delay definition */
#define EraseTimeout             ((u32)0x00000FFF)
#define ProgramTimeout           ((u32)0x0000000F)
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
#ifdef _FLASH_PROG
static void delay(void);
#endif

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : FLASH_SetLatency
* Description    : Sets the code latency value.
* Input          : - FLASH_Latency: specifies the FLASH Latency value.
*                    This parameter can be one of the following values:
*                       - FLASH_Latency_0: FLASH Zero Latency cycle
*                       - FLASH_Latency_1: FLASH One Latency cycle
*                       - FLASH_Latency_2: FLASH Two Latency cycles
* Output         : None
* Return         : None
*******************************************************************************/
void FLASH_SetLatency(u32 FLASH_Latency)
{
  u32 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_FLASH_LATENCY(FLASH_Latency));

  /* Read the ACR register */
  tmpreg = FLASH->ACR;

  /* Sets the Latency value */
  tmpreg &= ACR_LATENCY_Mask;
  tmpreg |= FLASH_Latency;

  /* Write the ACR register */
  FLASH->ACR = tmpreg;
}

/*******************************************************************************
* Function Name  : FLASH_HalfCycleAccessCmd
* Description    : Enables or disables the Half cycle flash access.
* Input          : - FLASH_HalfCycle: specifies the FLASH Half cycle Access mode.
*                    This parameter can be one of the following values:
*                       - FLASH_HalfCycleAccess_Enable: FLASH Half Cycle Enable
*                       - FLASH_HalfCycleAccess_Disable: FLASH Half Cycle Disable
* Output         : None
* Return         : None
*******************************************************************************/
void FLASH_HalfCycleAccessCmd(u32 FLASH_HalfCycleAccess)
{
  /* Check the parameters */
  assert_param(IS_FLASH_HALFCYCLEACCESS_STATE(FLASH_HalfCycleAccess));

  /* Enable or disable the Half cycle access */
  FLASH->ACR &= ACR_HLFCYA_Mask;
  FLASH->ACR |= FLASH_HalfCycleAccess;
}

/*******************************************************************************
* Function Name  : FLASH_PrefetchBufferCmd
* Description    : Enables or disables the Prefetch Buffer.
* Input          : - FLASH_PrefetchBuffer: specifies the Prefetch buffer status.
*                    This parameter can be one of the following values:
*                       - FLASH_PrefetchBuffer_Enable: FLASH Prefetch Buffer Enable
*                       - FLASH_PrefetchBuffer_Disable: FLASH Prefetch Buffer Disable
* Output         : None
* Return         : None
*******************************************************************************/
void FLASH_PrefetchBufferCmd(u32 FLASH_PrefetchBuffer)
{
  /* Check the parameters */
  assert_param(IS_FLASH_PREFETCHBUFFER_STATE(FLASH_PrefetchBuffer));

  /* Enable or disable the Prefetch Buffer */
  FLASH->ACR &= ACR_PRFTBE_Mask;
  FLASH->ACR |= FLASH_PrefetchBuffer;
}

#ifdef _FLASH_PROG
/*******************************************************************************
* Function Name  : FLASH_Unlock
* Description    : Unlocks the FLASH Program Erase Controller.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FLASH_Unlock(void)
{
  /* Authorize the FPEC Access */
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;
}

/*******************************************************************************
* Function Name  : FLASH_Lock
* Description    : Locks the FLASH Program Erase Controller.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FLASH_Lock(void)
{
  /* Set the Lock Bit to lock the FPEC and the FCR */
  FLASH->CR |= CR_LOCK_Set;
}

/*******************************************************************************
* Function Name  : FLASH_ErasePage
* Description    : Erases a specified FLASH page.
* Input          : - Page_Address: The page address to be erased.
* Output         : None
* Return         : FLASH Status: The returned value can be: FLASH_BUSY,
*                  FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or
*                  FLASH_TIMEOUT.
*******************************************************************************/
FLASH_Status FLASH_ErasePage(u32 Page_Address)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Page_Address));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(EraseTimeout);

  if(status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to erase the page */
    FLASH->CR|= CR_PER_Set;
    FLASH->AR = Page_Address;
    FLASH->CR|= CR_STRT_Set;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if(status != FLASH_BUSY)
    {
      /* if the erase operation is completed, disable the PER Bit */
      FLASH->CR &= CR_PER_Reset;
    }
  }
  /* Return the Erase Status */
  return status;
}

/*******************************************************************************
* Function Name  : FLASH_EraseAllPages
* Description    : Erases all FLASH pages.
* Input          : None
* Output         : None
* Return         : FLASH Status: The returned value can be: FLASH_BUSY,
*                  FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or
*                  FLASH_TIMEOUT.
*******************************************************************************/
FLASH_Status FLASH_EraseAllPages(void)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(EraseTimeout);

  if(status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to erase all pages */
     FLASH->CR |= CR_MER_Set;
     FLASH->CR |= CR_STRT_Set;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if(status != FLASH_BUSY)
    {
      /* if the erase operation is completed, disable the MER Bit */
      FLASH->CR &= CR_MER_Reset;
    }
  }
  /* Return the Erase Status */
  return status;
}

/*******************************************************************************
* Function Name  : FLASH_EraseOptionBytes
* Description    : Erases the FLASH option bytes.
* Input          : None
* Output         : None
* Return         : FLASH Status: The returned value can be: FLASH_BUSY,
*                  FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or
*                  FLASH_TIMEOUT.
*******************************************************************************/
FLASH_Status FLASH_EraseOptionBytes(void)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(EraseTimeout);

  if(status == FLASH_COMPLETE)
  {
    /* Authorize the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;

    /* if the previous operation is completed, proceed to erase the option bytes */
    FLASH->CR |= CR_OPTER_Set;
    FLASH->CR |= CR_STRT_Set;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if(status == FLASH_COMPLETE)
    {
      /* if the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= CR_OPTER_Reset;

      /* Enable the Option Bytes Programming operation */
      FLASH->CR |= CR_OPTPG_Set;

      /* Enable the readout access */
      OB->RDP= RDP_Key;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);

      if(status != FLASH_BUSY)
      {
        /* if the program operation is completed, disable the OPTPG Bit */
        FLASH->CR &= CR_OPTPG_Reset;
      }
    }
    else
    {
      if (status != FLASH_BUSY)
      {
        /* Disable the OPTPG Bit */
        FLASH->CR &= CR_OPTPG_Reset;
      }
    }
  }
  /* Return the erase status */
  return status;
}

/*******************************************************************************
* Function Name  : FLASH_ProgramWord
* Description    : Programs a word at a specified address.
* Input          : - Address: specifies the address to be programmed.
*                  - Data: specifies the data to be programmed.
* Output         : None
* Return         : FLASH Status: The returned value can be: FLASH_BUSY,
*                  FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or
*                  FLASH_TIMEOUT.
*******************************************************************************/
FLASH_Status FLASH_ProgramWord(u32 Address, u32 Data)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(ProgramTimeout);

  if(status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to program the new first
    half word */
    FLASH->CR |= CR_PG_Set;

    *(vu16*)Address = (u16)Data;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if(status == FLASH_COMPLETE)
    {
      /* if the previous operation is completed, proceed to program the new second
      half word */
      *(vu16*)(Address + 2) = Data >> 16;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);

      if(status != FLASH_BUSY)
      {
        /* Disable the PG Bit */
        FLASH->CR &= CR_PG_Reset;
      }
    }
    else
    {
      if (status != FLASH_BUSY)
      {
        /* Disable the PG Bit */
        FLASH->CR &= CR_PG_Reset;
      }
     }
  }
  /* Return the Program Status */
  return status;
}

/*******************************************************************************
* Function Name  : FLASH_ProgramHalfWord
* Description    : Programs a half word at a specified address.
* Input          : - Address: specifies the address to be programmed.
*                  - Data: specifies the data to be programmed.
* Output         : None
* Return         : FLASH Status: The returned value can be: FLASH_BUSY,
*                  FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or
*                  FLASH_TIMEOUT.
*******************************************************************************/
FLASH_Status FLASH_ProgramHalfWord(u32 Address, u16 Data)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(ProgramTimeout);

  if(status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to program the new data */
    FLASH->CR |= CR_PG_Set;

    *(vu16*)Address = Data;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if(status != FLASH_BUSY)
    {
      /* if the program operation is completed, disable the PG Bit */
      FLASH->CR &= CR_PG_Reset;
    }
  }
  /* Return the Program Status */
  return status;
}

/*******************************************************************************
* Function Name  : FLASH_ProgramOptionByteData
* Description    : Programs a half word at a specified Option Byte Data address.
* Input          : - Address: specifies the address to be programmed.
*                    This parameter can be 0x1FFFF804 or 0x1FFFF806.
*                  - Data: specifies the data to be programmed.
* Output         : None
* Return         : FLASH Status: The returned value can be: FLASH_BUSY,
*                  FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or
*                  FLASH_TIMEOUT.
*******************************************************************************/
FLASH_Status FLASH_ProgramOptionByteData(u32 Address, u8 Data)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_OB_DATA_ADDRESS(Address));

  status = FLASH_WaitForLastOperation(ProgramTimeout);

  if(status == FLASH_COMPLETE)
  {
    /* Authorize the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;

    /* Enables the Option Bytes Programming operation */
    FLASH->CR |= CR_OPTPG_Set;
    *(vu16*)Address = Data;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if(status != FLASH_BUSY)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  }
  /* Return the Option Byte Data Program Status */
  return status;
}

/*******************************************************************************
* Function Name  : FLASH_EnableWriteProtection
* Description    : Write protects the desired pages
* Input          : - FLASH_Pages: specifies the address of the pages to be
*                    write protected. This parameter can be:
*                    - For STM32F10Xxx Medium-density devices (FLASH page size equal to 1 KB)
*                       - A value between FLASH_WRProt_Pages0to3 and
*                         FLASH_WRProt_Pages124to127
*                    - For STM32F10Xxx High-density devices (FLASH page size equal to 2 KB)
*                       - A value between FLASH_WRProt_Pages0to1 and
*                         FLASH_WRProt_Pages60to61 or FLASH_WRProt_Pages62to255
*                       - FLASH_WRProt_AllPages
* Output         : None
* Return         : FLASH Status: The returned value can be: FLASH_BUSY,
*                  FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or
*                  FLASH_TIMEOUT.
*******************************************************************************/
FLASH_Status FLASH_EnableWriteProtection(u32 FLASH_Pages)
{
  u16 WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;

  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_FLASH_WRPROT_PAGE(FLASH_Pages));

  FLASH_Pages = (u32)(~FLASH_Pages);
  WRP0_Data = (vu16)(FLASH_Pages & WRP0_Mask);
  WRP1_Data = (vu16)((FLASH_Pages & WRP1_Mask) >> 8);
  WRP2_Data = (vu16)((FLASH_Pages & WRP2_Mask) >> 16);
  WRP3_Data = (vu16)((FLASH_Pages & WRP3_Mask) >> 24);

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(ProgramTimeout);

  if(status == FLASH_COMPLETE)
  {
    /* Authorizes the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;
    FLASH->CR |= CR_OPTPG_Set;

    if(WRP0_Data != 0xFF)
    {
      OB->WRP0 = WRP0_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }
    if((status == FLASH_COMPLETE) && (WRP1_Data != 0xFF))
    {
      OB->WRP1 = WRP1_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }

    if((status == FLASH_COMPLETE) && (WRP2_Data != 0xFF))
    {
      OB->WRP2 = WRP2_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }

    if((status == FLASH_COMPLETE)&& (WRP3_Data != 0xFF))
    {
      OB->WRP3 = WRP3_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);
    }

    if(status != FLASH_BUSY)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  }
  /* Return the write protection operation Status */
  return status;
}

/*******************************************************************************
* Function Name  : FLASH_ReadOutProtection
* Description    : Enables or disables the read out protection.
*                  If the user has already programmed the other option bytes before
*                  calling this function, he must re-program them since this
*                  function erases all option bytes.
* Input          : - Newstate: new state of the ReadOut Protection.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : FLASH Status: The returned value can be: FLASH_BUSY,
*                  FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or
*                  FLASH_TIMEOUT.
*******************************************************************************/
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  status = FLASH_WaitForLastOperation(EraseTimeout);

  if(status == FLASH_COMPLETE)
  {
    /* Authorizes the small information block programming */
    FLASH->OPTKEYR = FLASH_KEY1;
    FLASH->OPTKEYR = FLASH_KEY2;

    FLASH->CR |= CR_OPTER_Set;
    FLASH->CR |= CR_STRT_Set;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if(status == FLASH_COMPLETE)
    {
      /* if the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= CR_OPTER_Reset;

      /* Enable the Option Bytes Programming operation */
      FLASH->CR |= CR_OPTPG_Set;

      if(NewState != DISABLE)
      {
        OB->RDP = 0x00;
      }
      else
      {
        OB->RDP = RDP_Key;
      }

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(EraseTimeout);

      if(status != FLASH_BUSY)
      {
        /* if the program operation is completed, disable the OPTPG Bit */
        FLASH->CR &= CR_OPTPG_Reset;
      }
    }
    else
    {
      if(status != FLASH_BUSY)
      {
        /* Disable the OPTER Bit */
        FLASH->CR &= CR_OPTER_Reset;
      }
    }
  }
  /* Return the protection operation Status */
  return status;
}

/*******************************************************************************
* Function Name  : FLASH_UserOptionByteConfig
* Description    : Programs the FLASH User Option Byte: IWDG_SW / RST_STOP /
*                  RST_STDBY.
* Input          : - OB_IWDG: Selects the IWDG mode
*                     This parameter can be one of the following values:
*                     - OB_IWDG_SW: Software IWDG selected
*                     - OB_IWDG_HW: Hardware IWDG selected
*                  - OB_STOP: Reset event when entering STOP mode.
*                     This parameter can be one of the following values:
*                     - OB_STOP_NoRST: No reset generated when entering in STOP
*                     - OB_STOP_RST: Reset generated when entering in STOP
*                  - OB_STDBY: Reset event when entering Standby mode.
*                    This parameter can be one of the following values:
*                     - OB_STDBY_NoRST: No reset generated when entering in STANDBY
*                     - OB_STDBY_RST: Reset generated when entering in STANDBY
* Output         : None
* Return         : FLASH Status: The returned value can be: FLASH_BUSY,
*                  FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or
*                  FLASH_TIMEOUT.
*******************************************************************************/
FLASH_Status FLASH_UserOptionByteConfig(u16 OB_IWDG, u16 OB_STOP, u16 OB_STDBY)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
  assert_param(IS_OB_STOP_SOURCE(OB_STOP));
  assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));

  /* Authorize the small information block programming */
  FLASH->OPTKEYR = FLASH_KEY1;
  FLASH->OPTKEYR = FLASH_KEY2;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(ProgramTimeout);

  if(status == FLASH_COMPLETE)
  {
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= CR_OPTPG_Set;

    OB->USER = ( OB_IWDG | OB_STOP |OB_STDBY) | (u16)0xF8;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if(status != FLASH_BUSY)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= CR_OPTPG_Reset;
    }
  }
  /* Return the Option Byte program Status */
  return status;
}

/*******************************************************************************
* Function Name  : FLASH_GetUserOptionByte
* Description    : Returns the FLASH User Option Bytes values.
* Input          : None
* Output         : None
* Return         : The FLASH User Option Bytes values:IWDG_SW(Bit0), RST_STOP(Bit1)
*                  and RST_STDBY(Bit2).
*******************************************************************************/
u32 FLASH_GetUserOptionByte(void)
{
  /* Return the User Option Byte */
  return (u32)(FLASH->OBR >> 2);
}

/*******************************************************************************
* Function Name  : FLASH_GetWriteProtectionOptionByte
* Description    : Returns the FLASH Write Protection Option Bytes Register value.
* Input          : None
* Output         : None
* Return         : The FLASH Write Protection  Option Bytes Register value
*******************************************************************************/
u32 FLASH_GetWriteProtectionOptionByte(void)
{
  /* Return the Falsh write protection Register value */
  return (u32)(FLASH->WRPR);
}

/*******************************************************************************
* Function Name  : FLASH_GetReadOutProtectionStatus
* Description    : Checks whether the FLASH Read Out Protection Status is set
*                  or not.
* Input          : None
* Output         : None
* Return         : FLASH ReadOut Protection Status(SET or RESET)
*******************************************************************************/
FlagStatus FLASH_GetReadOutProtectionStatus(void)
{
  FlagStatus readoutstatus = RESET;

  if ((FLASH->OBR & RDPRT_Mask) != (u32)RESET)
  {
    readoutstatus = SET;
  }
  else
  {
    readoutstatus = RESET;
  }
  return readoutstatus;
}

/*******************************************************************************
* Function Name  : FLASH_GetPrefetchBufferStatus
* Description    : Checks whether the FLASH Prefetch Buffer status is set or not.
* Input          : None
* Output         : None
* Return         : FLASH Prefetch Buffer Status (SET or RESET).
*******************************************************************************/
FlagStatus FLASH_GetPrefetchBufferStatus(void)
{
  FlagStatus bitstatus = RESET;

  if ((FLASH->ACR & ACR_PRFTBS_Mask) != (u32)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the new state of FLASH Prefetch Buffer Status (SET or RESET) */
  return bitstatus;
}

/*******************************************************************************
* Function Name  : FLASH_ITConfig
* Description    : Enables or disables the specified FLASH interrupts.
* Input          : - FLASH_IT: specifies the FLASH interrupt sources to be
*                    enabled or disabled.
*                    This parameter can be any combination of the following values:
*                       - FLASH_IT_ERROR: FLASH Error Interrupt
*                       - FLASH_IT_EOP: FLASH end of operation Interrupt
* Output         : None
* Return         : None
*******************************************************************************/
void FLASH_ITConfig(u16 FLASH_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FLASH_IT(FLASH_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if(NewState != DISABLE)
  {
    /* Enable the interrupt sources */
    FLASH->CR |= FLASH_IT;
  }
  else
  {
    /* Disable the interrupt sources */
    FLASH->CR &= ~(u32)FLASH_IT;
  }
}

/*******************************************************************************
* Function Name  : FLASH_GetFlagStatus
* Description    : Checks whether the specified FLASH flag is set or not.
* Input          : - FLASH_FLAG: specifies the FLASH flag to check.
*                     This parameter can be one of the following values:
*                    - FLASH_FLAG_BSY: FLASH Busy flag
*                    - FLASH_FLAG_PGERR: FLASH Program error flag
*                    - FLASH_FLAG_WRPRTERR: FLASH Write protected error flag
*                    - FLASH_FLAG_EOP: FLASH End of Operation flag
*                    - FLASH_FLAG_OPTERR:  FLASH Option Byte error flag
* Output         : None
* Return         : The new state of FLASH_FLAG (SET or RESET).
*******************************************************************************/
FlagStatus FLASH_GetFlagStatus(u16 FLASH_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG)) ;

  if(FLASH_FLAG == FLASH_FLAG_OPTERR)
  {
    if((FLASH->OBR & FLASH_FLAG_OPTERR) != (u32)RESET)
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
   if((FLASH->SR & FLASH_FLAG) != (u32)RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  /* Return the new state of FLASH_FLAG (SET or RESET) */
  return bitstatus;
}

/*******************************************************************************
* Function Name  : FLASH_ClearFlag
* Description    : Clears the FLASH’s pending flags.
* Input          : - FLASH_FLAG: specifies the FLASH flags to clear.
*                    This parameter can be any combination of the following values:
*                    - FLASH_FLAG_BSY: FLASH Busy flag
*                    - FLASH_FLAG_PGERR: FLASH Program error flag
*                    - FLASH_FLAG_WRPRTERR: FLASH Write protected error flag
*                    - FLASH_FLAG_EOP: FLASH End of Operation flag
* Output         : None
* Return         : None
*******************************************************************************/
void FLASH_ClearFlag(u16 FLASH_FLAG)
{
  /* Check the parameters */
  assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG)) ;

  /* Clear the flags */
  FLASH->SR = FLASH_FLAG;
}

/*******************************************************************************
* Function Name  : FLASH_GetStatus
* Description    : Returns the FLASH Status.
* Input          : None
* Output         : None
* Return         : FLASH Status: The returned value can be: FLASH_BUSY,
*                  FLASH_ERROR_PG, FLASH_ERROR_WRP or FLASH_COMPLETE
*******************************************************************************/
FLASH_Status FLASH_GetStatus(void)
{
  FLASH_Status flashstatus = FLASH_COMPLETE;

  if((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY)
  {
    flashstatus = FLASH_BUSY;
  }
  else
  {
    if(FLASH->SR & FLASH_FLAG_PGERR)
    {
      flashstatus = FLASH_ERROR_PG;
    }
    else
    {
      if(FLASH->SR & FLASH_FLAG_WRPRTERR)
      {
        flashstatus = FLASH_ERROR_WRP;
      }
      else
      {
        flashstatus = FLASH_COMPLETE;
      }
    }
  }
  /* Return the Flash Status */
  return flashstatus;
}

/*******************************************************************************
* Function Name  : FLASH_WaitForLastOperation
* Description    : Waits for a Flash operation to complete or a TIMEOUT to occur.
* Input          : - Timeout: FLASH progamming Timeout
* Output         : None
* Return         : FLASH Status: The returned value can be: FLASH_BUSY,
*                  FLASH_ERROR_PG, FLASH_ERROR_WRP, FLASH_COMPLETE or
*                  FLASH_TIMEOUT.
*******************************************************************************/
FLASH_Status FLASH_WaitForLastOperation(u32 Timeout)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check for the Flash Status */
  status = FLASH_GetStatus();

  /* Wait for a Flash operation to complete or a TIMEOUT to occur */
  while((status == FLASH_BUSY) && (Timeout != 0x00))
  {
    delay();
    status = FLASH_GetStatus();
    Timeout--;
  }

  if(Timeout == 0x00 )
  {
    status = FLASH_TIMEOUT;
  }

  /* Return the operation status */
  return status;
}

/*******************************************************************************
* Function Name  : delay
* Description    : Inserts a time delay.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void delay(void)
{
  vu32 i = 0;

  for(i = 0xFF; i != 0; i--)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
