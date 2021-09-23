/**
  ******************************************************************************
  * @file    lib_crypt.c 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   CRYPT library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_crypt.h"

/**
  * @brief  Configure PTRA register, data in this address will be read out to do 
  *         the CRYPT calculation
  * @param  AddrA: the SRAM address(Bit 14:0)
  * @retval None
  */
void CRYPT_AddressAConfig(uint16_t AddrA)
{
  /* Check parameters */
  assert_parameters(IS_CRYPT_ADDR(AddrA));
  
  CRYPT->PTRA = AddrA & CRYPT_PTRA_PTRA;
}

/**
  * @brief  Configure PTRB register, data in this address will be read out to do 
  *         the CRYPT calculation
  * @param  AddrB: the SRAM address(Bit 14:0)
  * @retval None
  */
void CRYPT_AddressBConfig(uint16_t AddrB)
{
  /* Check parameters */
  assert_parameters(IS_CRYPT_ADDR(AddrB));

  CRYPT->PTRB = AddrB & CRYPT_PTRB_PTRB;
}

/**
  * @brief  Configure PTRO register, The CRYPT engine will write calculation 
  *         result into this address
  * @param  AddrO: the SRAM address(Bit 14:0)
  * @retval None
  */
void CRYPT_AddressOConfig(uint16_t AddrO)
{
  /* Check parameters */
  assert_parameters(IS_CRYPT_ADDR(AddrO)); 
  
  CRYPT->PTRO = AddrO & CRYPT_PTRO_PTRO;
}

/**
  * @brief  Get carry/borrow bit of add/sub operation.
  * @param  None
  * @retval carry/borrow bit value
  */
uint8_t CRYPT_GetCarryBorrowBit(void)
{
  if (CRYPT->CARRY & CRYPT_CARRY_CARRY)
    return (1);
  else
    return (0);
}

/**
  * @brief  Start addition operation.
  * @param  Length:
  *             CRYPT_LENGTH_32
  *             CRYPT_LENGTH_64
  *             CRYPT_LENGTH_96
  *             CRYPT_LENGTH_128
  *             CRYPT_LENGTH_160
  *             CRYPT_LENGTH_192
  *             CRYPT_LENGTH_224
  *             CRYPT_LENGTH_256
  *             CRYPT_LENGTH_288
  *             CRYPT_LENGTH_320
  *             CRYPT_LENGTH_352
  *             CRYPT_LENGTH_384
  *             CRYPT_LENGTH_416
  *             CRYPT_LENGTH_448
  *             CRYPT_LENGTH_480
  *             CRYPT_LENGTH_512
  *         Nostop:
  *             CRYPT_STOPCPU
  *             CRYPT_NOSTOPCPU
  * @retval None
  */
void CRYPT_StartAdd(uint32_t Length, uint32_t Nostop)
{
  /* Check parameters */
  assert_parameters(IS_CRYPT_LENGTH(Length)); 
  assert_parameters(IS_CRYPT_NOSTOP(Nostop));
  
  CRYPT->CTRL = (Nostop \
                |Length \
                |CRYPT_CTRL_MODE_ADD \
                |CRYPT_CTRL_ACT);
}

/**
  * @brief  Start multiplication operation.
  * @param  Length:
  *             CRYPT_LENGTH_32
  *             CRYPT_LENGTH_64
  *             CRYPT_LENGTH_96
  *             CRYPT_LENGTH_128
  *             CRYPT_LENGTH_160
  *             CRYPT_LENGTH_192
  *             CRYPT_LENGTH_224
  *             CRYPT_LENGTH_256
  *             CRYPT_LENGTH_288
  *             CRYPT_LENGTH_320
  *             CRYPT_LENGTH_352
  *             CRYPT_LENGTH_384
  *             CRYPT_LENGTH_416
  *             CRYPT_LENGTH_448
  *             CRYPT_LENGTH_480
  *             CRYPT_LENGTH_512
  *         Nostop:
  *             CRYPT_STOPCPU
  *             CRYPT_NOSTOPCPU
  * @retval None
  */
void CRYPT_StartMultiply(uint32_t Length, uint32_t Nostop)
{
  /* Check parameters */
  assert_parameters(IS_CRYPT_LENGTH(Length)); 
  assert_parameters(IS_CRYPT_NOSTOP(Nostop));
  
  CRYPT->CTRL = (Nostop \
                |Length \
                |CRYPT_CTRL_MODE_MULTIPLY \
                |CRYPT_CTRL_ACT);
}

/**
  * @brief  Start subtraction operation.
  * @param  Length:
  *             CRYPT_LENGTH_32
  *             CRYPT_LENGTH_64
  *             CRYPT_LENGTH_96
  *             CRYPT_LENGTH_128
  *             CRYPT_LENGTH_160
  *             CRYPT_LENGTH_192
  *             CRYPT_LENGTH_224
  *             CRYPT_LENGTH_256
  *             CRYPT_LENGTH_288
  *             CRYPT_LENGTH_320
  *             CRYPT_LENGTH_352
  *             CRYPT_LENGTH_384
  *             CRYPT_LENGTH_416
  *             CRYPT_LENGTH_448
  *             CRYPT_LENGTH_480
  *             CRYPT_LENGTH_512
  *         Nostop:
  *             CRYPT_STOPCPU
  *             CRYPT_NOSTOPCPU
  * @retval None
  */
void CRYPT_StartSub(uint32_t Length, uint32_t Nostop)
{
  /* Check parameters */
  assert_parameters(IS_CRYPT_LENGTH(Length)); 
  assert_parameters(IS_CRYPT_NOSTOP(Nostop));
  
  CRYPT->CTRL = (Nostop \
                |Length \
                |CRYPT_CTRL_MODE_SUB \
                |CRYPT_CTRL_ACT);
}

/**
  * @brief  Start rigth shift 1-bit operation.
  * @param  Length:
  *             CRYPT_LENGTH_32
  *             CRYPT_LENGTH_64
  *             CRYPT_LENGTH_96
  *             CRYPT_LENGTH_128
  *             CRYPT_LENGTH_160
  *             CRYPT_LENGTH_192
  *             CRYPT_LENGTH_224
  *             CRYPT_LENGTH_256
  *             CRYPT_LENGTH_288
  *             CRYPT_LENGTH_320
  *             CRYPT_LENGTH_352
  *             CRYPT_LENGTH_384
  *             CRYPT_LENGTH_416
  *             CRYPT_LENGTH_448
  *             CRYPT_LENGTH_480
  *             CRYPT_LENGTH_512
  *         Nostop:
  *             CRYPT_STOPCPU
  *             CRYPT_NOSTOPCPU
  * @retval None
  */
void CRYPT_StartRShift1(uint32_t Length, uint32_t Nostop)
{
  /* Check parameters */
  assert_parameters(IS_CRYPT_LENGTH(Length)); 
  assert_parameters(IS_CRYPT_NOSTOP(Nostop));
  
  CRYPT->CTRL = (Nostop \
                |Length \
                |CRYPT_CTRL_MODE_RSHIFT1 \
                |CRYPT_CTRL_ACT);
}

/**
  * @brief  Waiting for last operation to complete. 
  * @param  None
  * @retval None
  */
void CRYPT_WaitForLastOperation(void)
{
  while (CRYPT->CTRL & CRYPT_CTRL_ACT)
  {
  }
}

/*********************************** END OF FILE ******************************/
