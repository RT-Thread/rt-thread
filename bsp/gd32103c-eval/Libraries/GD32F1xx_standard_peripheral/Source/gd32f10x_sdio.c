/**
 ******************************************************************************
  * @brief   SDIO functions of the firmware library.
 ******************************************************************************
  */
#ifdef GD32F10X_HD
/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_sdio.h"
#include "gd32f10x_rcc.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup SDIO
  * @brief SDIO driver modules
  * @{
  */

/** @defgroup SDIO_Private_Defines
  * @{
  */

/* SDIO registers bit mask */
/* CLKCTLR register mask */
#define CLKCTLR_CLEAR_MASK        ((uint32_t)0xFFFF8100)
/* POWER_PWRSTATE mask */
#define POWER_PWRSTATE_MASK       ((uint32_t)0xFFFFFFFC)
/* DTCTLR register mask */
#define DTCTLR_CLEAR_MASK         ((uint32_t)0xFFFFFF08)
/* CMD register mask */
#define CMD_CLEAR_MASK            ((uint32_t)0xFFFFF800)

/* SDIO RESP Registers Address */
#define SDIO_RESP_ADDR            ((uint32_t)(SDIO_BASE + 0x14))

/**
  * @}
  */

/** @defgroup SDIO_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the SDIO .
  * @param  None
  * @retval None
  */
void SDIO_DeInit(void)
{
    SDIO->POWER = 0x00000000;
    SDIO->CLKCTLR = 0x00000000;
    SDIO->PARA = 0x00000000;
    SDIO->CMD = 0x00000000;
    SDIO->DTTR = 0x00000000;
    SDIO->DTLEN = 0x00000000;
    SDIO->DTCTLR = 0x00000000;
    SDIO->ICR = 0x00C007FF;
    SDIO->IER = 0x00000000;
}

/**
  * @brief  Initialize the SDIO .
  * @param  SDIO_InitParaStruct : pointer to a SDIO_InitPara structure .
  * @retval None
  */
void SDIO_Init(SDIO_InitPara *SDIO_InitParaStruct)
{
    uint32_t temp = 0;

    /* SDIO CLKCTLR Configuration */
    /* Get the SDIO CLKCTLR value */
    temp = SDIO->CLKCTLR;

    /* Clear CLKCTLR register */
    temp &= CLKCTLR_CLEAR_MASK;

    /* Configure the SDIO_ClockDiv value */
    /* Configure the SDIO_ClockPWRSave value */
    /* Configure the SDIO_ClockBypassState value */
    /* Configure the SDIO_BusMode value */
    /* Configure the SDIO_ClockEdge value */
    /* Configure the SDIO_HWFlowCtrlState value */
    temp |= (SDIO_InitParaStruct->SDIO_ClockDiv   | SDIO_InitParaStruct->SDIO_ClockPWRSave |
             SDIO_InitParaStruct->SDIO_ClockBypassState | SDIO_InitParaStruct->SDIO_BusMode |
             SDIO_InitParaStruct->SDIO_ClockEdge  | SDIO_InitParaStruct->SDIO_HWFlowCtrlState);

    /* Update the SDIO CLKCTLR */
    SDIO->CLKCTLR = temp;
}

/**
  * @brief  Fill each SDIO_InitParaStruct Struct member with a default value.
  * @param  SDIO_InitParaStruct: pointer to an SDIO_InitPara structure.
  * @retval None
  */
void SDIO_ParaInit(SDIO_InitPara *SDIO_InitParaStruct)
{
    /* Fill the default value */
    SDIO_InitParaStruct->SDIO_ClockDiv = 0x00;
    SDIO_InitParaStruct->SDIO_ClockEdge = SDIO_CLOCKEDGE_RISING;
    SDIO_InitParaStruct->SDIO_ClockBypassState = SDIO_CLOCKBYPASSSTATE_DISABLE;
    SDIO_InitParaStruct->SDIO_ClockPWRSave = SDIO_CLOCKPWRSAVE_DISABLE;
    SDIO_InitParaStruct->SDIO_BusMode = SDIO_BUSMODE_1B;
    SDIO_InitParaStruct->SDIO_HWFlowCtrlState = SDIO_HWFLOWCTRLSTATE_DISABLE;
}

/**
  * @brief  ENABLE or DISABLE the SDIO Clock.
  * @param  NewValue:  ENABLE or DISABLE.
  * @retval None
  */
void SDIO_Clock_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        SDIO->CLKCTLR |= SDIO_CLKCTLR_CKEN;
    } else {
        SDIO->CLKCTLR &= (uint16_t)~(SDIO_CLKCTLR_CKEN);
    }
}

/**
  * @brief  Configure the power state of SDIO.
  * @param  SDIO_PwrState: new Power state for SDIO.
  *   This value will be :
  *     @arg SDIO_PWRSTATE_ON
  *     @arg SDIO_PWRSTATE_OFF
  * @retval None
  */
void SDIO_SetPWRState(uint32_t SDIO_PwrState)
{
    /* Update the SDIO POWER */
    SDIO->POWER |= SDIO_PwrState;
}

/**
  * @brief  Get the power state of SDIO.
  * @param  None
  * @retval Power state for SDIO.
  *   This value will be :
  *      - 0x00: Power OFF
  *      - 0x02: Power UP
  *      - 0x03: Power ON
  */
uint32_t SDIO_GetPWRState(void)
{
    return (SDIO->POWER & (~POWER_PWRSTATE_MASK));
}

/**
  * @brief  Configure interrupts enables.
  * @param  SDIO_INT: The interrupts sources to configure.
  *   This value will be :
  *     @arg SDIO_INT_CCRCFAIL: Command response CRC failed interrupt
  *     @arg SDIO_INT_DTCRCFAIL: Data CRC failed interrupt
  *     @arg SDIO_INT_CMDTMOUT: Command response timeout interrupt
  *     @arg SDIO_INT_DTTMOUT: Data timeout interrupt
  *     @arg SDIO_INT_TXURE: Transmit FIFO underrun error interrupt
  *     @arg SDIO_INT_RXORE:  Received FIFO overrun error interrupt
  *     @arg SDIO_INT_CMDREND:  Command response received (CRC check passed) interrupt
  *     @arg SDIO_INT_CMDSENT:  Command sent (no response required) interrupt
  *     @arg SDIO_INT_DTEND:  Data end (data counter, SDIDTCNT, is zero) interrupt
  *     @arg SDIO_INT_STBITE: Start bit not detected on all data signals in wide bus mode interrupt
  *     @arg SDIO_INT_DTBLKEND:  Data block sent/received (CRC check passed) interrupt
  *     @arg SDIO_INT_CMDRUN:   Command transfer in progress interrupt
  *     @arg SDIO_INT_TXRUN:    Data transmit in progress interrupt
  *     @arg SDIO_INT_RXRUN:    Data receive in progress interrupt
  *     @arg SDIO_INT_TXFIFOHE: Transmit FIFO Half Empty interrupt
  *     @arg SDIO_INT_RXFIFOHF: Receive FIFO Half Full interrupt
  *     @arg SDIO_INT_TXFIFOF:  Transmit FIFO full interrupt
  *     @arg SDIO_INT_RXFIFOF:  Receive FIFO full interrupt
  *     @arg SDIO_INT_TXFIFOE:  Transmit FIFO empty interrupt
  *     @arg SDIO_INT_RXFIFOE:  Receive FIFO empty interrupt
  *     @arg SDIO_INT_TXDTVAL:   Data valid in transmit FIFO interrupt
  *     @arg SDIO_INT_RXDTVAL:   Data valid in receive FIFO interrupt
  *     @arg SDIO_INT_SDIOINT:   SD I/O interrupt received interrupt
  *     @arg SDIO_INT_ATAEND: CE-ATA command completion signal received for CMD61 interrupt
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_INTConfig(uint32_t SDIO_INT, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the interrupt */
        SDIO->IER |= SDIO_INT;
    } else {
        /* Disable the interrupt */
        SDIO->IER &= ~SDIO_INT;
    }
}

/**
  * @brief  Enable or disable the DMA request for SDIO.
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_DMA_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable DMA request */
        SDIO->DTCTLR |= SDIO_DTCTLR_DMAEN;
    } else {
        /* Disenable DMA request */
        SDIO->DTCTLR &= (uint16_t)~((uint16_t)SDIO_DTCTLR_DMAEN);
    }
}

/**
  * @brief  Initialize the SDIO Command.
  * @param  SDIO_CmdInitParaStruct : pointer to a SDIO_CmdInitPara structure.
  * @retval None
  */
void SDIO_SendCMD(SDIO_CmdInitPara *SDIO_CmdInitParaStruct)
{
    uint32_t temp = 0;

    /* SDIO PARA Configuration */
    /* Configure the SDIO_CMDParameter value */
    SDIO->PARA = SDIO_CmdInitParaStruct->SDIO_CMDParameter;

    /* SDIO CMD Configuration */
    /* Get the SDIO CMD value */
    temp = SDIO->CMD;
    /* Clear CMD register */
    temp &= CMD_CLEAR_MASK;
    /* Configure the SDIO_CMDIndex value */
    /* Configure the SDIO_ResponseType value */
    /* Configure the SDIO_WaitINTState value */
    /* Configure the SDIO_CSMState value */
    temp |= (uint32_t)SDIO_CmdInitParaStruct->SDIO_CMDIndex | SDIO_CmdInitParaStruct->SDIO_ResponseType
            | SDIO_CmdInitParaStruct->SDIO_WaitINTState | SDIO_CmdInitParaStruct->SDIO_CSMState;

    /* Update the SDIO CMD */
    SDIO->CMD = temp;
}

/**
  * @brief  Fill SDIO_CmdInitStruct member with a default value.
  * @param  SDIO_CmdInitParaStruct: pointer to an SDIO_CmdInitPara structure.
  * @retval None
  */
void SDIO_CMDParaInit(SDIO_CmdInitPara *SDIO_CmdInitParaStruct)
{
    /* Fill the default value */
    SDIO_CmdInitParaStruct->SDIO_CMDParameter = 0x00;
    SDIO_CmdInitParaStruct->SDIO_CMDIndex = 0x00;
    SDIO_CmdInitParaStruct->SDIO_ResponseType = SDIO_RESPONSETYPE_NO ;
    SDIO_CmdInitParaStruct->SDIO_WaitINTState = SDIO_WAITINTSTATE_NO;
    SDIO_CmdInitParaStruct->SDIO_CSMState = SDIO_CSMSTATE_DISABLE;
}

/**
  * @brief  Return last response command index.
  * @param  None
  * @retval Return last response command index.
  */
uint8_t SDIO_GetCMDResponse(void)
{
    return (uint8_t)(SDIO->RESPCMD);
}

/**
  * @brief  Return the response for the last received command.
  * @param  SDIO_RESP: The SDIO response registers.
  *   This value will be :
  *     @arg SDIO_RESP1: Response Register 1
  *     @arg SDIO_RESP2: Response Register 2
  *     @arg SDIO_RESP3: Response Register 3
  *     @arg SDIO_RESP4: Response Register 4
  * @retval The Corresponding response register value.
  */
uint32_t SDIO_GetResponse(uint32_t SDIO_RESP)
{
    __IO uint32_t temp = 0;

    temp = SDIO_RESP_ADDR + SDIO_RESP;

    return (*(__IO uint32_t *) temp);
}

/**
  * @brief  Initialize the SDIO SDIO_DataInitParaStruct members.
  * @param  SDIO_DataInitParaStruct : pointer to a SDIO_DataInitPara structure.
  * @retval None
  */
void SDIO_DataConfig(SDIO_DataInitPara *SDIO_DataInitParaStruct)
{
    uint32_t temp = 0;

    /* SDIO DTTR Configuration */
    /* Set the SDIO SDIO_DataTimeOut value */
    SDIO->DTTR = SDIO_DataInitParaStruct->SDIO_DataTimeOut;

    /* SDIO DTLEN Configuration */
    /* Set the SDIO SDIO_DataLength value */
    SDIO->DTLEN = SDIO_DataInitParaStruct->SDIO_DataLength;

    /* SDIO DTCTLR Configuration */
    /* Get the SDIO DTCTLR value */
    temp = SDIO->DTCTLR;
    /* Clear DTCTLR register */
    temp &= DTCTLR_CLEAR_MASK;
    /* Configure the SDIO_DataBlockSize value */
    /* Configure the SDIO_TransDirection value */
    /* Configure the SDIO_TransMode value */
    /* Configure the SDIO_DSMState value */
    temp |= (uint32_t)SDIO_DataInitParaStruct->SDIO_DataBlockSize | SDIO_DataInitParaStruct->SDIO_TransDirection
            | SDIO_DataInitParaStruct->SDIO_TransMode | SDIO_DataInitParaStruct->SDIO_DSMState;

    /* Update the SDIO DTCTLR */
    SDIO->DTCTLR = temp;
}

/**
  * @brief  Fill each SDIO_DataInitParaStruct member with a default value.
  * @param  SDIO_DataInitParaStruct: pointer to an SDIO_DataInitPara structure.
  * @retval None
  */
void SDIO_DataParaInit(SDIO_DataInitPara *SDIO_DataInitParaStruct)
{
    /* Fill the default value */
    SDIO_DataInitParaStruct->SDIO_DataTimeOut = 0xFFFFFFFF;
    SDIO_DataInitParaStruct->SDIO_DataLength = 0x00;
    SDIO_DataInitParaStruct->SDIO_DataBlockSize = SDIO_DATABLOCKSIZE_1B;
    SDIO_DataInitParaStruct->SDIO_TransDirection = SDIO_TRANSDIRECTION_TOCARD;
    SDIO_DataInitParaStruct->SDIO_TransMode = SDIO_TRANSMODE_BLOCK;
    SDIO_DataInitParaStruct->SDIO_DSMState = SDIO_DSMSTATE_DISABLE;
}

/**
  * @brief  Return the number of remaining data bytes to be transferred to card.
  * @param  None
  * @retval Number of remaining data bytes to be transferred
  */
uint32_t SDIO_GetDataCount(void)
{
    return SDIO->DTCNT;
}

/**
  * @brief  Read one word from receive FIFO.
  * @param  None
  * @retval Data received
  */
uint32_t SDIO_ReadData(void)
{
    return SDIO->FIFO;
}

/**
  * @brief  Write one word to transmit FIFO.
  * @param  Data: 32-bit data write to the card.
  * @retval None
  */
void SDIO_WriteData(uint32_t Data)
{
    SDIO->FIFO = Data;
}

/**
  * @brief  Return the number of words remaining to be written or read from FIFO.
  * @param  None
  * @retval Remaining number of words.
  */
uint32_t SDIO_GetFIFOCount(void)
{
    return SDIO->FIFOCNT;
}

/**
  * @brief  Start SD I/O Read Wait operation.
  * @param  NewValue:  ENABLE or DISABLE.
  * @retval None
  */
void SDIO_StartSDIOReadWait(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Start Read Wait operation  */
        SDIO->DTCTLR |= SDIO_DTCTLR_RWSTART;
    } else {
        SDIO->DTCTLR &= (uint16_t)~((uint16_t)SDIO_DTCTLR_RWSTART);
    }
}

/**
  * @brief  Stop the SD I/O Read Wait operation.
  * @param  NewValue:  ENABLE or DISABLE.
  * @retval None
  */
void SDIO_StopSDIOReadWait(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        SDIO->DTCTLR |= SDIO_DTCTLR_RWSTOP;
    } else {
        /* Stop Read Wait operation  */
        SDIO->DTCTLR &= (uint16_t)~((uint16_t)SDIO_DTCTLR_RWSTOP);
    }
}

/**
  * @brief  Configure the SD I/O read wait mode.
  * @param  SDIO_ReadWaitMode: SD I/O Read Wait operation mode.
  *   This value will be :
  *     @arg SDIO_READWAITMODE_CLK: Read Wait operation realize by stopping SDIOCLK
  *     @arg SDIO_READWAITMODE_DAT2: Read Wait operation use SDIO_DAT2
  * @retval None
  */
void SDIO_SetSDIOReadWaitMode(uint32_t SDIO_ReadWaitMode)
{
    if (SDIO_ReadWaitMode == SDIO_READWAITMODE_CLK) {
        /* Read Wait operation stop SDIOCLK  */
        SDIO->DTCTLR |= SDIO_DTCTLR_RWMODE;
    } else {
        /* Read Wait operation use SDIO_DAT2  */
        SDIO->DTCTLR &= (uint16_t)~((uint16_t)SDIO_DTCTLR_RWMODE);
    }
}

/**
  * @brief  SD I/O Mode Operation configuration.
  * @param  NewValue:  ENABLE or DISABLE.
  * @retval None
  */
void SDIO_SetSDIOOperation(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable I/O Mode Operation  */
        SDIO->DTCTLR |= SDIO_DTCTLR_SDIOEN;
    } else {
        /* Disenable I/O Mode Operation  */
        SDIO->DTCTLR &= (uint16_t)~((uint16_t)SDIO_DTCTLR_SDIOEN);
    }
}

/**
  * @brief  Enable or disable the SD I/O suspend operation.
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_SendSDIOSuspend_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable suspend operation  */
        SDIO->CMD |= SDIO_CMD_SDIOSUSPEND;
    } else {
        /* Disenable suspend operation  */
        SDIO->CMD &= (uint16_t)~((uint16_t)SDIO_CMD_SDIOSUSPEND);
    }
}

/**
  * @brief  Enable or disable the CE-ATA command completion signal.
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_CMDCompletion_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable CE-ATA command completion signal  */
        SDIO->CMD |= SDIO_CMD_ENCMDC;
    } else {
        /* Disenable CE-ATA command completion signal  */
        SDIO->CMD &= (uint16_t)~((uint16_t)SDIO_CMD_ENCMDC);
    }
}

/**
  * @brief  Enable or disable the CE-ATA interrupt.
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_CEATAInt_Enable(TypeState NewValue)
{
    if (NewValue != ENABLE) {
        /* Enable CE-ATA interrupt  */
        SDIO->CMD |= SDIO_CMD_NIEN;
    } else {
        /* Disenable CE-ATA interrupt  */
        SDIO->CMD &= (uint16_t)~((uint16_t)SDIO_CMD_NIEN);
    }
}

/**
  * @brief  Send CE-ATA command (CMD61).
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_SendCEATA_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        SDIO->CMD |= SDIO_CMD_ATACMD;
    } else {
        SDIO->CMD &= (uint16_t)~((uint16_t)SDIO_CMD_ATACMD);
    }
}

/**
  * @brief  Check whether the flag is set or not.
  * @param  SDIO_FLAG: the flag to check.
  *   This value will be :
  *     @arg SDIO_FLAG_CCRCFAIL:  Command response received (CRC failed)
  *     @arg SDIO_FLAG_DTCRCFAIL: Data block sent/received (CRC failed)
  *     @arg SDIO_FLAG_CMDTMOUT:  Command response timeout
  *     @arg SDIO_FLAG_DTTMOUT:   Data timeout
  *     @arg SDIO_FLAG_TXURE:     Transmit FIFO underrun error
  *     @arg SDIO_FLAG_RXORE:     Received FIFO overrun error
  *     @arg SDIO_FLAG_CMDREND:   Command response received (CRC check passed)
  *     @arg SDIO_FLAG_CMDSENT:   Command sent (no response required)
  *     @arg SDIO_FLAG_DTEND:     Data end (data counter, SDIDTCNT, is zero)
  *     @arg SDIO_FLAG_STBITE:    Start bit not detected on all data signals in wide
  *                               bus mode.
  *     @arg SDIO_FLAG_DTBLKEND:  Data block sent/received (CRC check passed)
  *     @arg SDIO_FLAG_CMDRUN:    Command transfer in progress
  *     @arg SDIO_FLAG_TXRUN:     Data transmit in progress
  *     @arg SDIO_FLAG_RXRUN:     Data receive in progress
  *     @arg SDIO_FLAG_TXFIFOHE:  Transmit FIFO Half Empty
  *     @arg SDIO_FLAG_RXFIFOHF:  Receive FIFO Half Full
  *     @arg SDIO_FLAG_TXFIFOF:   Transmit FIFO full
  *     @arg SDIO_FLAG_RXFIFOF:   Receive FIFO full
  *     @arg SDIO_FLAG_TXFIFOE:   Transmit FIFO empty
  *     @arg SDIO_FLAG_RXFIFOE:   Receive FIFO empty
  *     @arg SDIO_FLAG_TXDTVAL:   Data available in transmit FIFO
  *     @arg SDIO_FLAG_RXDTVAL:   Data available in receive FIFO
  *     @arg SDIO_FLAG_SDIOINT:   SD I/O interrupt received
  *     @arg SDIO_FLAG_ATAEND:    CE-ATA command completion signal received for CMD61
  * @retval The new state of SDIO_FLAG (SET or RESET).
  */
TypeState SDIO_GetBitState(uint32_t SDIO_FLAG)
{
    if ((SDIO->STR & SDIO_FLAG) != (uint32_t)RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  Clear the pending flags.
  * @param  SDIO_FLAG: the flag to clear.
  *   This value will be :
  *     @arg SDIO_FLAG_CCRCFAIL:  Command response received (CRC check failed)
  *     @arg SDIO_FLAG_DTCRCFAIL: Data block sent/received (CRC check failed)
  *     @arg SDIO_FLAG_CMDTMOUT:  Command response timeout
  *     @arg SDIO_FLAG_DTTMOUT:   Data timeout
  *     @arg SDIO_FLAG_TXURE:     Transmit FIFO underrun error
  *     @arg SDIO_FLAG_RXORE:     Received FIFO overrun error
  *     @arg SDIO_FLAG_CMDREND:   Command response received (CRC check passed)
  *     @arg SDIO_FLAG_CMDSENT:   Command sent (no response required)
  *     @arg SDIO_FLAG_DTEND:     Data end (data counter, SDIO_DTCNT, is zero)
  *     @arg SDIO_FLAG_STBITE:    Start bit not detected on all data signals in wide bus mode
  *     @arg SDIO_FLAG_DTBLKEND:  Data block sent/received (CRC check passed)
  *     @arg SDIO_FLAG_SDIOINT:   SD I/O interrupt received
  *     @arg SDIO_FLAG_ATAEND:    CE-ATA command completion signal received for CMD61
  * @retval None
  */
void SDIO_ClearBitState(uint32_t SDIO_FLAG)
{
    SDIO->ICR = SDIO_FLAG;
}

/**
  * @brief  Check whether the interrupt is pending or not.
  * @param  SDIO_INT: the SDIO interrupt source to check.
  *   This value will be :
  *     @arg SDIO_INT_CCRCFAIL:   Command response received (CRC check failed) interrupt
  *     @arg SDIO_INT_DTCRCFAIL:  Data block sent/received (CRC check failed) interrupt
  *     @arg SDIO_INT_CMDTMOUT:   Command response timeout interrupt
  *     @arg SDIO_INT_DTTMOUT:    Data timeout interrupt
  *     @arg SDIO_INT_TXURE:      Transmit FIFO underrun error interrupt
  *     @arg SDIO_INT_RXORE:      Received FIFO overrun error interrupt
  *     @arg SDIO_INT_CMDREND:    Command response received (CRC check passed) interrupt
  *     @arg SDIO_INT_CMDSENT:    Command sent (no response required) interrupt
  *     @arg SDIO_INT_DTEND:      Data end (data counter, SDIDTCNT, is zero) interrupt
  *     @arg SDIO_INT_STBITE:     Start bit not detected on all data signals in wide bus mode interrupt
  *     @arg SDIO_INT_DTBLKEND:   Data block sent/received (CRC check passed) interrupt
  *     @arg SDIO_INT_CMDRUN:     Command transfer in progress interrupt
  *     @arg SDIO_INT_TXRUN:      Data transmit in progress interrupt
  *     @arg SDIO_INT_RXRUN:      Data receive in progress interrupt
  *     @arg SDIO_INT_TXFIFOHE:   Transmit FIFO Half Empty interrupt
  *     @arg SDIO_INT_RXFIFOHF:   Receive FIFO Half Full interrupt
  *     @arg SDIO_INT_TXFIFOF:    Transmit FIFO full interrupt
  *     @arg SDIO_INT_RXFIFOF:    Receive FIFO full interrupt
  *     @arg SDIO_INT_TXFIFOE:    Transmit FIFO empty interrupt
  *     @arg SDIO_INT_RXFIFOE:    Receive FIFO empty interrupt
  *     @arg SDIO_INT_TXDTVAL:    Data available in transmit FIFO interrupt
  *     @arg SDIO_INT_RXDTVAL:    Data available in receive FIFO interrupt
  *     @arg SDIO_INT_SDIOINT:    SD I/O interrupt received interrupt
  *     @arg SDIO_INT_ATAEND:     CE-ATA command completion signal received for CMD61 interrupt
  * @retval The new state of SDIO_INT (SET or RESET).
  */
TypeState SDIO_GetIntBitState(uint32_t SDIO_INT)
{
    if ((SDIO->STR & SDIO_INT) != (uint32_t)RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  Clear the interrupt pending bits.
  * @param  SDIO_INT: the interrupt pending bit to clear.
  *   This value will be :
  *     @arg SDIO_INT_CCRCFAIL:   Command response received (CRC check failed) interrupt
  *     @arg SDIO_INT_DTCRCFAIL:  Data block sent/received (CRC check failed) interrupt
  *     @arg SDIO_INT_CMDTMOUT:   Command response timeout interrupt
  *     @arg SDIO_INT_DTTMOUT:    Data timeout interrupt
  *     @arg SDIO_INT_TXURE:      Transmit FIFO underrun error interrupt
  *     @arg SDIO_INT_RXORE:      Received FIFO overrun error interrupt
  *     @arg SDIO_INT_CMDREND:    Command response received (CRC check passed) interrupt
  *     @arg SDIO_INT_CMDSENT:    Command sent (no response required) interrupt
  *     @arg SDIO_INT_DTEND:      Data end (data counter, SDIDTCNT, is zero) interrupt
  *     @arg SDIO_INT_STBITE:     Start bit not detected on all data signals in wide
  *                               bus mode interrupt
  *     @arg SDIO_INT_SDIOINT:    SD I/O interrupt received interrupt
  *     @arg SDIO_INT_ATAEND:     CE-ATA command completion signal received for CMD61
  * @retval None
  */
void SDIO_ClearIntBitState(uint32_t SDIO_INT)
{
    SDIO->ICR = SDIO_INT;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif
