/*  ******************************************************************************
  * @file               ft32f0xx_dac.c
  * @author             FMD xzhang
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of RNG peripheral
  * @version            V1.0.0
  * @data                   2025-03-11
    *******************************************************************************/
#include "ft32f4xx_rng.h"
/*RNG initial config include:1 rng_clk config (48mhz)
 *                           2 rng enable
 *                           3 rng interrupt enable
 */
/**
  * @brief  Initializes the RNG peripheral.
  * @param
  * @retval
  */
void  RNG_Init()
{
    /* Enable the RNG Peripheral */
    RNG ->  RNG_CR |= RNG_EN;
}

/**
  * @brief  DeInitializes the RNG peripheral and all register.
  * @param  NewState: new state of the configed undervoltage reset :BOR_EN.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval
  */
void RNG_DeInit(FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        /* Disable the RNG Peripheral */
        RNG ->  RNG_CR &= ~RNG_EN;
        /* Disable the RNG interrupt and SEIS CEIS */
        RNG -> RNG_CR &= ~RNG_IE;
        /* SEIS and CEIS RC_W0 */
        RNG -> RNG_SR &= ~RNG_SEIS;
        RNG -> RNG_SR &= ~RNG_CEIS;
    }
}
/**
  * @brief  Generates a 32-bit random number.
  * @note   When no more random number data is available in DR register, RNG_DRDY
  *         flag is automatically cleared.
  * @retval
  */
uint32_t RNG_GenerateRandomNumber()
{
    uint32_t random32bit;
    /* Check if data register contains valid random data */
    if ((RNG->RNG_SR & RNG_DRDY) == RNG_DRDY)
    {
        //if DRDY is ready random data can be read
        random32bit = RNG -> RNG_DR;        //if random data is read DRDY will be clear auto
    }
    return random32bit;
}


/**
  * @brief enable interrupt mode.
  * @param  NewState: new state of the configed undervoltage reset :BOR_EN.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval
  */
void RNG_IT(FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        /* Enable the RNG Interrupts: Data Ready, Clock error, Seed error */
        RNG -> RNG_CR |=  RNG_IE;
    }
    else
    {
        RNG -> RNG_CR &= ~RNG_IE;
    }
}
/**
  * @brief Back ERROR status include SEIS:0x01 SECS:0x02 CEIS:0x10 CECS:0x20.
  * @param
  * @retval
  */
uint8_t RNG_get_error_status()
{

    uint8_t bit_status;
    if ((RNG -> RNG_CR & RNG_IE) == RNG_IE)
    {

        if (((RNG -> RNG_SR) & RNG_SECS) == RNG_SECS)

            bit_status = 0x01;

        if ((RNG -> RNG_SR & RNG_CECS) == RNG_CECS)

            bit_status = 0x10;
    }
    return bit_status;
}

