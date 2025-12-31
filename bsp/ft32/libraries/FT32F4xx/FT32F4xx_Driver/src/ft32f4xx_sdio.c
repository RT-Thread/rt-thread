/**
  ******************************************************************************
  * @file               ft32f4xx_sdio.c
    ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_sdio.h"
#include "system_ft32f4xx.h"
#include "ft32f4xx_rcc.h"


/** @defgroup SDIO
  * @brief SDIO driver modules
  * @{
  */

/*******************/
void SDIO_DeInit(void)
{
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SDIO, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SDIO, DISABLE);
}

/*******************/
void SDIO_odpullupConfig(uint32_t SDIO_odenable)
{
    /* 1.Clear CTRL_enable_OD_pullup bit */
    SDIO -> CTRL &= ~(0x1 << 24);
    assert_param(IS_SDIO_OD_PULLUP(SDIO_odenable));
    SDIO -> CTRL |= SDIO_odenable;
}


/*******************/
void SDIO_UseholdregConfig(uint32_t SDIO_Useholdregenable)
{
    /* 1.Clear CMD_use_hold_reg bit */
    SDIO -> CMD &= ~(0x1 << 29);
    assert_param(IS_SDIO_USE_HOLD_REG(SDIO_Useholdregenable));
    SDIO -> CMD |= SDIO_Useholdregenable;
}

/*******************/
void SDIO_PowerEnableConfig(uint32_t SDIO_PowerEnable)
{
    assert_param(IS_SDIO_POWER_ON(SDIO_PowerEnable));
    SDIO -> PWREN  = SDIO_PowerEnable;
}


/*******************/
void SDIO_TimeOutConfig(uint32_t SDIO_TMOUTValue)
{
    /* Set the TMOUT bits include RESPONSE TMOUT and DATA TMOUT values */
    SDIO -> TMOUT = (uint32_t)SDIO_TMOUTValue;
}


/*******************/
void SDIO_FifoThConfig(uint32_t SDIO_FIFOTHValue)
{
    /* Set the FIFOTH bits include Tx_WMark and Rx_WMark values */
    SDIO -> FIFOTH = (uint32_t)SDIO_FIFOTHValue;
}


/*******************/
void SDIO_CardWidthConfig(uint32_t SDIO_CardWidth)
{
    assert_param(IS_SDIO_CARD_WIDE(SDIO_CardWidth));
    SDIO -> CTYPE  = SDIO_CardWidth;
}


/*******************/
void SDIO_TransferModeConfig(uint32_t SDIO_TransferMode)
{
    SDIO -> CMD &= ~(0x1 << 11);
    assert_param(IS_SDIO_TRANSFER_MODE(SDIO_TransferMode));
    SDIO -> CMD  |= SDIO_TransferMode;
}


/*******************/
void SDIO_TransferDirectionConfig(uint32_t SDIO_ReadWrite)
{
    SDIO -> CMD &= ~(0x1 << 10);
    assert_param(IS_SDIO_TRANSFER_DIR(SDIO_ReadWrite));
    SDIO -> CMD  |= SDIO_ReadWrite;
}


/*******************/
void SDIO_DataExpectedConfig(uint32_t SDIO_DataExpected)
{
    /* 1.Clear DataExpected bit */
    SDIO -> CMD &= ~(0x1 << 9);
    assert_param(IS_SDIO_DATA_EXPECT(SDIO_DataExpected));
    SDIO -> CMD  |= SDIO_DataExpected;
}


/*******************/
void SDIO_CheckResponseCRCConfig(uint32_t SDIO_CheckResponseCRC)
{
    /* 1.Clear CheckResponseCRC bit */
    SDIO -> CMD &= ~(0x1 << 8);
    assert_param(IS_SDIO_CHECK_RESPONSE_CRC(SDIO_CheckResponseCRC));
    SDIO -> CMD  |= SDIO_CheckResponseCRC;
}


/*******************/
void SDIO_ResponseLengthConfig(uint32_t SDIO_ResponseLength)
{
    /* 1.Clear ResponseLength bit */
    SDIO -> CMD &= ~(0x1 << 7);
    assert_param(IS_SDIO_RESPONSE(SDIO_ResponseLength));
    SDIO -> CMD  |= SDIO_ResponseLength;
}


/*******************/
void SDIO_ResponseExpectConfig(uint32_t SDIO_ResponseExpect)
{
    /* 1.Clear ResponseExpect bit */
    SDIO -> CMD &= ~(0x1 << 6);
    assert_param(IS_SDIO_RESPONSE_EXPECT(SDIO_ResponseExpect));
    SDIO -> CMD  |= SDIO_ResponseExpect;
}


/*******************/
void SDIO_ChangeCardClock(uint32_t SDIO_Clkdiv)
{
    /* 1.Clear CLKENA[0] bit */
    SDIO->CLKENA &= ~SDIO_CLKENA_CCLK_ENABLE_0;
    /* 2.1.Check the parameters */
    assert_param(IS_SDIO_CLKDIV(SDIO_Clkdiv));
    /* 2.2.Clear CLKDIV[7:0] bits */
    SDIO->CLKDIV &= ~SDIO_CLKDIV_CLK_DIVIDER0;
    /* 2.3.Set the SDIO_CLKDIV[7:0] bits according to SDIO_Clkdiv value */
    SDIO->CLKDIV |= SDIO_Clkdiv;
    /* 3.Enable CMD_UPDATE_CLOCK_REGISTERS_ONLY bit */
    SDIO->CMD |= SDIO_CMD_UPDATE_CLOCK_REGISTERS_ONLY;
    /* 4.Enable CLKENA[0] bit */
    SDIO->CLKENA |= SDIO_CLKENA_CCLK_ENABLE_0;
    /* 5.Enable CMD_START_CMD bit */
    SDIO->CMD |= SDIO_CMD_START_CMD;
    while (((SDIO -> CMD) & SDIO_CMD_START_CMD) == SDIO_CMD_START_CMD);
    /* 6.Clean CMD_UPDATE_CLOCK_REGISTERS_ONLY bit */
    SDIO->CMD &= ~SDIO_CMD_UPDATE_CLOCK_REGISTERS_ONLY;
}

/*******************/
void SDIO_SendCMD(uint32_t SDIO_CmdIndex)
{
    /* 1.Clear CMD_INDEX bit */
    SDIO -> CMD &= ~(0x3F << 0);
    /* 2.1.Check the parameters */
    assert_param(IS_SDIO_CMD_INDEX(SDIO_CmdIndex));
    /* 2.2.Send Command */
    SDIO -> CMD |= SDIO_CmdIndex;
    /* 3.Enable CMD_START_CMD bit */
    SDIO->CMD |= SDIO_CMD_START_CMD;
    while (((SDIO -> CMD) & SDIO_CMD_START_CMD) == SDIO_CMD_START_CMD);
}


/*******************/
void SDIO_CMDARGConfig(uint32_t SDIO_CmdArgument)
{
    assert_param(IS_SDIO_CMD_ARG(SDIO_CmdArgument));
    SDIO -> CMDARG  = SDIO_CmdArgument;
}


/*******************/
void SDIO_BlockSizeConfig(uint32_t SDIO_BlockSize)
{
    assert_param(IS_SDIO_BLOCK_SIZE(SDIO_BlockSize));
    SDIO -> BLKSIZ = SDIO_BlockSize;
}


/*******************/
void SDIO_ByteCountConfig(uint32_t SDIO_ByteCount)
{
    assert_param(IS_SDIO_DATA_BYTE_COUNT(SDIO_ByteCount));
    SDIO -> BYTCNT = SDIO_ByteCount;
}


/*******************/
void SDIO_ITConfig(uint32_t SDIO_IT)
{
    /* 1.enable CTRL_int_enable bit */
    SDIO -> CTRL |= SDIO_CTRL_INT_ENABLE;
    /* Check the parameters */
    assert_param(IS_SDIO_IT_MASK(SDIO_IT));
    SDIO->INTMASK |= SDIO_IT;
}


/*******************/
FlagStatus SDIO_GetITFlag(uint32_t SDIO_FLAG)
{
    /* Check the parameters */
    assert_param(IS_SDIO_IT_FLAG(SDIO_FLAG));
    return ((FlagStatus)(SDIO->MINTSTS & SDIO_FLAG));
}


/*******************/
void SDIO_ClearITFlag(uint32_t SDIO_FLAG)
{
    /* Check the parameters */
    assert_param(IS_SDIO_IT_CLEAN(SDIO_FLAG));
    SDIO->RINTSTS |= SDIO_FLAG;
}


/*************/
uint32_t SDIO_GetFifoStatus(uint32_t SDIO_FIFOStatus)
{
    /* Check the parameters */
    assert_param(IS_SDIO_STATUS(SDIO_FIFOStatus));
    return (uint32_t)((SDIO->STATUS) & SDIO_FIFOStatus);
}


/*************/
uint32_t SDIO_GetStatus(uint32_t SDIO_Status)
{
    /* Check the parameters */
    assert_param(IS_SDIO_STATUS(SDIO_Status));
    return (uint32_t)((SDIO->STATUS) & SDIO_Status);
}
/***********************************************************************************/
/***********************************************************************************/




