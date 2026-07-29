/**
  ******************************************************************************
  * @file    lib_flash.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   FLASH library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_flash.h"  
#include "lib_clk.h"

/* FLASH Keys */
#define FLASH_PASS_KEY      0x55AAAA55
#define FLASH_SERASE_KEY    0xAA5555AA
#define FLASH_CERASE_KEY    0xAA5555AA
#define FLASH_DSTB_KEY      0xAA5555AA
#define FLASH_ICE_KEY       0xAA5555AA

#define FLASH_MODE_MASK     0x1F3

/**
  * @brief  Initializes FLASH mode.
  * @param  CSMode:
                FLASH_CSMODE_DISABLE 
                FLASH_CSMODE_ALWAYSON
                FLASH_CSMODE_TMR2OF   
                FLASH_CSMODE_RTC      
  * @retval None
  */
void FLASH_Init(uint32_t CSMode)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_FLASH_CSMODE(CSMode));  
 
  tmp = FLASH->CTRL;
  tmp &= ~FLASH_MODE_MASK;
  tmp |= CSMode;
  FLASH->CTRL = tmp;
}

/**
  * @brief  Enables or disables FLASH interrupt.
  * @param  IntMask:
                FLASH_INT_CS
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void FLASH_INTConfig(uint32_t IntMask, uint32_t NewState)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_FLASH_INT(IntMask));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 
  
  tmp = FLASH->CTRL;
  tmp &= ~IntMask;
  if (NewState == ENABLE)
  {
    tmp |= IntMask;
  }
  FLASH->CTRL = tmp;
}

/**
  * @brief  Initializes FLASH 1USCYCLE.
  * @param  None
  * @retval None
  */
void FLASH_CycleInit(void)
{
  uint32_t hclk;
  
  hclk = CLK_GetHCLKFreq();

  if (hclk > 1000000)
    MISC2->FLASHWC = (hclk/1000000)<<8;
  else
    MISC2->FLASHWC = 0;
}

/**
  * @brief  Erases a specified FLASH sector.
  * @param  SectorAddr: Erase start address.
  * @retval None
  */
void FLASH_SectorErase(uint32_t SectorAddr)
{
  /* Check parameters */
  assert_parameters(IS_FLASH_ADDRESS(SectorAddr));
  
  /* Unlock flash */
  FLASH->PASS = FLASH_PASS_KEY;

  FLASH->PGADDR = SectorAddr;
  FLASH->SERASE = FLASH_SERASE_KEY;
  while (FLASH->SERASE != 0);

  /* Lock flash */
  FLASH->PASS = 0;
}

/**
  * @brief  Erases chip.
  * @param  None.
  * @retval None
  */
void FLASH_ChipErase(void)
{
  /* Unlock flash */
  FLASH->PASS = FLASH_PASS_KEY;

  FLASH->PGADDR = 0;
  FLASH->CERASE = FLASH_CERASE_KEY;
  while (FLASH->CERASE != 0);

  /* Lock flash */
  FLASH->PASS = 0;
}

/**
  * @brief  Programs n word at a specified start address.
  * @param  Addr: program start address
            WordBuffer: word's buffer pointer to write
            Length: The length of WordBuffer
  * @retval None  
  */
void FLASH_ProgramWord(uint32_t Addr, uint32_t *WordBuffer, uint32_t Length)
{
  uint32_t i;
  
  /* Check parameters */
  assert_parameters(IS_FLASH_ADRRW(Addr));
  
  FLASH->PGADDR = Addr;
  /* Unlock flash */
  FLASH->PASS = FLASH_PASS_KEY;
  
  for (i=0; i<Length; i++)
  {
    FLASH->PGDATA = *(WordBuffer++);
    while (FLASH->STS != 1);
  }
  
  /* Lock flash */
  FLASH->PASS = 0;
}

/**
  * @brief  Programs n half-word at a specified start address.
  * @param  Addr: program start address
            HWordBuffer: half-word's buffer pointer to write
            Length: The length of HWordBuffer
  * @retval None  
  */
void FLASH_ProgramHWord(uint32_t Addr, uint16_t *HWordBuffer, uint32_t Length)
{
  uint32_t i;
  
  /* Check parameters */
  assert_parameters(IS_FLASH_ADRRHW(Addr));
  
  FLASH->PGADDR = Addr;
  /* Unlock flash */
  FLASH->PASS = FLASH_PASS_KEY;
  
  for (i=0; i<Length; i++)
  {
    if (((Addr + 2*i)&0x3) == 0)
      *((__IO uint16_t*)(&FLASH->PGDATA)) = *(HWordBuffer++);
    else
      *((__IO uint16_t*)(&FLASH->PGDATA ) + 1) = *(HWordBuffer++);
    while (FLASH->STS != 1);
  }
  
  /* Lock flash */
  FLASH->PASS = 0;
}

/**
  * @brief  Programs n byte at a specified start address.
  * @param  Addr: program start address
            ByteBuffer: byte's buffer pointer to write
            Length: The length of ByteBuffer
  * @retval None  
  */
void FLASH_ProgramByte(uint32_t Addr, uint8_t *ByteBuffer, uint32_t Length)
{
  uint32_t i;
  
  /* Check parameters */
  assert_parameters(IS_FLASH_ADDRESS(Addr));
  
  FLASH->PGADDR = Addr;
  /* Unlock flash */
  FLASH->PASS = FLASH_PASS_KEY;
  
  for (i=0; i<Length; i++)
  {
    if (((Addr + i)&0x3) == 0)
      *((__IO uint8_t*)(&FLASH->PGDATA)) = *(ByteBuffer++);
    else if (((Addr + i)&0x3) == 1)
      *((__IO uint8_t*)(&FLASH->PGDATA) + 1) = *(ByteBuffer++);
    else if (((Addr + i)&0x3) == 2)
      *((__IO uint8_t*)(&FLASH->PGDATA) + 2) = *(ByteBuffer++);
    else
      *((__IO uint8_t*)(&FLASH->PGDATA) + 3) = *(ByteBuffer++);
    while (FLASH->STS != 1); 
  }
  
  /* Lock flash */
  FLASH->PASS = 0;
}

/**
  * @brief  Enables FLASH read protection.
  * @param  Block: can use the '|' operator.
                FLASH_BLOCK_0 ~ FLASH_BLOCK_31 or FLASH_BLOCK_ALL
  * @retval None  
  */
void FLASH_SetReadProtection(uint32_t Block)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_FLASH_RWBLOCK(Block));

  tmp = *(volatile unsigned int *)(0x0007FC00);
  tmp &= ~Block; 

  /* Unlock flash */
  FLASH->PASS = FLASH_PASS_KEY;
  
  FLASH->PGADDR = 0x7FC00;
  FLASH->PGDATA = tmp;
  while (FLASH->STS != 1);
  /* Lock flash */
  FLASH->PASS = 0;

  tmp = *(volatile unsigned int *)(0x0007FC00);
}

/**
  * @brief  Enables or disables FLASH write protection.
  * @param  Block: can use the '|' operator.
                FLASH_BLOCK_0 ~ FLASH_BLOCK_31 or FLASH_BLOCK_ALL
            NewState:
                ENABLE
                DISABLE
  * @retval None  
  */
void FLASH_WriteProtection(uint32_t Block, uint32_t NewState)
{
  uint32_t wrprot;

  /* Check parameters */
  assert_parameters(IS_FLASH_RWBLOCK(Block));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 

  wrprot = FLASH->WRPROT;

  if (NewState == ENABLE)
  {
    wrprot |= Block;
  }
  else
  {
    wrprot &= ~Block;
  }
  FLASH->WRPROT = wrprot;
}

/**
  * @brief  Enables or disables ICE protection.
  * @param  NewState:
                ENABLE(ICE protection is successful when 0x7FC08 is 0xFFFFFFFF )
                DISABLE
  * @retval None.
  */
void FLASH_ICEProtection(uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState == ENABLE)
  {
    /* Unlock flash */
    FLASH->PASS = FLASH_PASS_KEY;

    FLASH->PGADDR = 0x7FC08;
    FLASH->PGDATA = 0x0A;
    while (FLASH->STS != 1);
    /* Lock flash */
    FLASH->PASS = 0;
  }
  else
  {
    FLASH_SectorErase(0x7FFFF);
    CORTEX_NVIC_SystemReset();
  }
}

/**
  * @brief  Gets read/write/erase protection status.
  * @param  Block: 
                FLASH_BLOCK_0 ~ FLASH_BLOCK_31
            Operation:
                FLASH_READ
                FLASH_WRITE
  * @retval 
            When Operation is FLASH_READ:
                1: Read protection enabled.
                0: Read protection disabled.
            When Operation is FLASH_WRITE:
                1: Write/erase protection enabled.
                0: Write/erase protection disabled.
  */
uint8_t FLASH_GetProtectionStatus(uint32_t Block, uint32_t Operation)
{
  /* Check parameters */
  assert_parameters(IS_FLASH_BLOCK(Block));
  assert_parameters(IS_FLASH_OPERATION(Operation)); 

  if (Operation == FLASH_READ)
  {
    if (FLASH->RDPROT & Block)
      return 1;
    else 
      return 0;
  }
  else
  {
    if (FLASH->WRPROT & Block)
      return 1;
    else 
      return 0;
  }
}

/**
  * @brief  Gets read/write/erase protection status.
  * @param  Operation:
                FLASH_READ
                FLASH_WRITE
  * @retval Read or write/erase protection status.
  */
uint32_t FLASH_GetAllProtectionStatus(uint32_t Operation)
{
  if (Operation == FLASH_READ)
  {
    return FLASH->RDPROT;
  }
  else
  {
    return FLASH->WRPROT;
  }
}

/**
  * @brief  Sets checksum range.
  * @param  AddrStart: checksum start address
            AddrEnd: checksum end address
  * @retval None  
  */
void FLASH_SetCheckSumRange(uint32_t AddrStart, uint32_t AddrEnd)
{
  /* Check parameters */
  assert_parameters(IS_FLASH_CHECKSUMADDR(AddrStart,AddrEnd));
  
  FLASH->CSSADDR = AddrStart;
  FLASH->CSEADDR = AddrEnd;
}

/**
  * @brief  Sets checksum compare value.
  * @param  Checksum: checksum compare value
  * @retval None  
  */
void FLASH_SetCheckSumCompValue(uint32_t Checksum)
{
  FLASH->CSCVALUE = Checksum;
}

/**
  * @brief  Gets FLASH checksum value.
  * @param  None
  * @retval Checksum  
  */
uint32_t FLASH_GetCheckSum(void)
{
  return FLASH->CSVALUE;
}

/**
  * @brief  Gets FLASH interrupt status.
  * @param  IntMask:
                FLASH_INT_CS
  * @retval 1: interrupt status set
            0: interrupt status reset
  */
uint8_t FLASH_GetINTStatus(uint32_t IntMask)
{
  /* Check parameters */
  assert_parameters(IS_FLASH_INT(IntMask));

  if (FLASH->INTSTS & FLASH_INTSTS_CSERR)
  {
    return 1;
  }
  else
  {
    return 0;
  } 
}

/**
  * @brief  Clears FLASH interrupt status.
  * @param  IntMask:
                FLASH_INT_CS
  * @retval None
  */
void FLASH_ClearINTStatus(uint32_t IntMask)
{
  /* Check parameters */
  assert_parameters(IS_FLASH_INT(IntMask));
  
  if (IntMask == FLASH_INT_CS)
  {
    FLASH->INTSTS = FLASH_INTSTS_CSERR;
  }
}

/*********************************** END OF FILE ******************************/
