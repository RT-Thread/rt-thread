/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g45x_sdio.c
 * @author Nations
 * @version v1.0.1
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g45x_sdio.h"
#include "n32g45x_rcc.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup SDIO
 * @brief SDIO driver modules
 * @{
 */

/** @addtogroup SDIO_Private_TypesDefinitions
 * @{
 */

/* ------------ SDIO registers bit address in the alias region ----------- */
#define SDIO_OFFSET (SDIO_BASE - PERIPH_BASE)

/* --- CLKCTRL Register ---*/

/* Alias word address of CLKEN bit */
#define CLKCTRL_OFFSET   (SDIO_OFFSET + 0x04)
#define CLKEN_BIT_NUMBER 0x08
#define CLKCTRL_CLKEN_BB (PERIPH_BB_BASE + (CLKCTRL_OFFSET * 32) + (CLKEN_BIT_NUMBER * 4))

/* --- CMDCTRL Register ---*/

/* Alias word address of SDIOSUSPEND bit */
#define CMD_OFFSET              (SDIO_OFFSET + 0x0C)
#define SDIO_SUSPEND_BIT_NUMBER 0x0B
#define CMD_SDIO_SUSPEND_BB     (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (SDIO_SUSPEND_BIT_NUMBER * 4))

/* Alias word address of ENCMDCOMPL bit */
#define EN_CMD_COMPL_BIT_NUMBER 0x0C
#define EN_CMD_COMPL_BB         (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (EN_CMD_COMPL_BIT_NUMBER * 4))

/* Alias word address of NIEN bit */
#define NIEN_BIT_NUMBER 0x0D
#define CMD_NIEN_BB     (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (NIEN_BIT_NUMBER * 4))

/* Alias word address of ATACMD bit */
#define ATACMD_BIT_NUMBER 0x0E
#define CMD_ATACMD_BB     (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (ATACMD_BIT_NUMBER * 4))

/* --- DATCTRL Register ---*/

/* Alias word address of DMAEN bit */
#define DCTRL_OFFSET     (SDIO_OFFSET + 0x2C)
#define DMAEN_BIT_NUMBER 0x03
#define DCTRL_DMAEN_BB   (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (DMAEN_BIT_NUMBER * 4))

/* Alias word address of RWSTART bit */
#define RWSTART_BIT_NUMBER 0x08
#define DCTRL_RWSTART_BB   (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (RWSTART_BIT_NUMBER * 4))

/* Alias word address of RWSTOP bit */
#define RWSTOP_BIT_NUMBER 0x09
#define DCTRL_RWSTOP_BB   (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (RWSTOP_BIT_NUMBER * 4))

/* Alias word address of RWMOD bit */
#define RWMOD_BIT_NUMBER 0x0A
#define DCTRL_RWMOD_BB   (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (RWMOD_BIT_NUMBER * 4))

/* Alias word address of SDIOEN bit */
#define SDIOEN_BIT_NUMBER 0x0B
#define DCTRL_SDIOEN_BB   (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (SDIOEN_BIT_NUMBER * 4))

/* ---------------------- SDIO registers bit mask ------------------------ */

/* --- CLKCTRL Register ---*/

/* CLKCTRL register clear mask */
#define CLKCTRL_CLR_MASK ((uint32_t)0xFFFF8100)

/* --- PWRCTRL Register ---*/

/* SDIO PWRCTRL Mask */
#define POWER_PWRCTRL_MASK ((uint32_t)0xFFFFFFFC)

/* --- DATCTRL Register ---*/

/* SDIO DATCTRL Clear Mask */
#define DATCTRL_CLR_MASK ((uint32_t)0xFFFFFF08)

/* --- CMDCTRL Register ---*/

/* CMDCTRL Register clear mask */
#define CMD_CLR_MASK ((uint32_t)0xFFFFF800)

/* SDIO RESP Registers Address */
#define SDID_RESPONSE_ADDR ((uint32_t)(SDIO_BASE + 0x14))

/**
 * @}
 */

/** @addtogroup SDIO_Private_Defines
 * @{
 */

/**
 * @}
 */

/** @addtogroup SDIO_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup SDIO_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup SDIO_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup SDIO_Private_Functions
 * @{
 */

/**
 * @brief  Deinitializes the SDIO peripheral registers to their default reset values.
 */
void SDIO_DeInit(void)
{
    SDIO->PWRCTRL    = 0x00000000;
    SDIO->CLKCTRL    = 0x00000000;
    SDIO->CMDARG     = 0x00000000;
    SDIO->CMDCTRL    = 0x00000000;
    SDIO->DTIMER = 0x00000000;
    SDIO->DATLEN     = 0x00000000;
    SDIO->DATCTRL    = 0x00000000;
    SDIO->INTCLR     = 0x00C007FF;
    SDIO->INTEN      = 0x00000000;
}

/**
 * @brief  Initializes the SDIO peripheral according to the specified
 *         parameters in the SDIO_InitStruct.
 * @param SDIO_InitStruct pointer to a SDIO_InitType structure
 *         that contains the configuration information for the SDIO peripheral.
 */
void SDIO_Init(SDIO_InitType* SDIO_InitStruct)
{
    uint32_t tmpregister = 0;

    /* Check the parameters */
    assert_param(IS_SDIO_CLK_EDGE(SDIO_InitStruct->ClkEdge));
    assert_param(IS_SDIO_CLK_BYPASS(SDIO_InitStruct->ClkBypass));
    assert_param(IS_SDIO_CLK_POWER_SAVE(SDIO_InitStruct->ClkPwrSave));
    assert_param(IS_SDIO_BUS_WIDTH(SDIO_InitStruct->BusWidth));
    assert_param(IS_SDIO_HARDWARE_CLKCTRL(SDIO_InitStruct->HardwareClkCtrl));

    /*---------------------------- SDIO CLKCTRL Configuration ------------------------*/
    /* Get the SDIO CLKCTRL value */
    tmpregister = SDIO->CLKCTRL;

    /* Clear CLKDIV, PWRSAV, BYPASS, WIDBUS, NEGEDGE, HWFC_EN bits */
    tmpregister &= CLKCTRL_CLR_MASK;

    /* Set CLKDIV bits according to ClkDiv value */
    /* Set PWRSAV bit according to ClkPwrSave value */
    /* Set BYPASS bit according to ClkBypass value */
    /* Set WIDBUS bits according to BusWidth value */
    /* Set NEGEDGE bits according to ClkEdge value */
    /* Set HWFC_EN bits according to HardwareClkCtrl value */
    tmpregister |= (SDIO_InitStruct->ClkDiv | SDIO_InitStruct->ClkPwrSave | SDIO_InitStruct->ClkBypass
                    | SDIO_InitStruct->BusWidth | SDIO_InitStruct->ClkEdge | SDIO_InitStruct->HardwareClkCtrl);

    /* Write to SDIO CLKCTRL */
    SDIO->CLKCTRL = tmpregister;
}

/**
 * @brief  Fills each SDIO_InitStruct member with its default value.
 * @param SDIO_InitStruct pointer to an SDIO_InitType structure which
 *   will be initialized.
 */
void SDIO_InitStruct(SDIO_InitType* SDIO_InitStruct)
{
    /* SDIO_InitStruct members default value */
    SDIO_InitStruct->ClkDiv          = 0x00;
    SDIO_InitStruct->ClkEdge         = SDIO_CLKEDGE_RISING;
    SDIO_InitStruct->ClkBypass       = SDIO_ClkBYPASS_DISABLE;
    SDIO_InitStruct->ClkPwrSave      = SDIO_CLKPOWERSAVE_DISABLE;
    SDIO_InitStruct->BusWidth        = SDIO_BUSWIDTH_1B;
    SDIO_InitStruct->HardwareClkCtrl = SDIO_HARDWARE_CLKCTRL_DISABLE;
}

/**
 * @brief  Enables or disables the SDIO Clock.
 * @param Cmd new state of the SDIO Clock. This parameter can be: ENABLE or DISABLE.
 */
void SDIO_EnableClock(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    *(__IO uint32_t*)CLKCTRL_CLKEN_BB = (uint32_t)Cmd;
}

/**
 * @brief  Sets the power status of the controller.
 * @param SDIO_PowerState new state of the Power state.
 *   This parameter can be one of the following values:
 *     @arg SDIO_POWER_CTRL_OFF
 *     @arg SDIO_POWER_CTRL_ON
 */
void SDIO_SetPower(uint32_t SDIO_PowerState)
{
    /* Check the parameters */
    assert_param(IS_SDIO_POWER_CTRL(SDIO_PowerState));

    SDIO->PWRCTRL &= POWER_PWRCTRL_MASK;
    SDIO->PWRCTRL |= SDIO_PowerState;
}

/**
 * @brief  Gets the power status of the controller.
 * @return Power status of the controller. The returned value can
 *   be one of the following:
 * - 0x00: Power OFF
 * - 0x02: Power UP
 * - 0x03: Power ON
 */
uint32_t SDIO_GetPower(void)
{
    return (SDIO->PWRCTRL & (~POWER_PWRCTRL_MASK));
}

/**
 * @brief  Enables or disables the SDIO interrupts.
 * @param SDIO_IT specifies the SDIO interrupt sources to be enabled or disabled.
 *   This parameter can be one or a combination of the following values:
 *     @arg SDIO_INT_CCRCERR Command response received (CRC check failed) interrupt
 *     @arg SDIO_INT_DCRCERR Data block sent/received (CRC check failed) interrupt
 *     @arg SDIO_INT_CMDTIMEOUT Command response timeout interrupt
 *     @arg SDIO_INT_DATTIMEOUT Data timeout interrupt
 *     @arg SDIO_INT_TXURERR Transmit DATFIFO underrun error interrupt
 *     @arg SDIO_INT_RXORERR Received DATFIFO overrun error interrupt
 *     @arg SDIO_INT_CMDRESPRECV Command response received (CRC check passed) interrupt
 *     @arg SDIO_INT_CMDSEND Command sent (no response required) interrupt
 *     @arg SDIO_INT_DATEND Data end (data counter, SDIDCOUNT, is zero) interrupt
 *     @arg SDIO_INT_SBERR Start bit not detected on all data signals in wide
 *                            bus mode interrupt
 *     @arg SDIO_INT_DATBLKEND Data block sent/received (CRC check passed) interrupt
 *     @arg SDIO_INT_CMDRUN Command transfer in progress interrupt
 *     @arg SDIO_INT_TXRUN Data transmit in progress interrupt
 *     @arg SDIO_INT_RXRUN Data receive in progress interrupt
 *     @arg SDIO_INT_TFIFOHE Transmit DATFIFO Half Empty interrupt
 *     @arg SDIO_INT_RFIFOHF Receive DATFIFO Half Full interrupt
 *     @arg SDIO_INT_TFIFOF Transmit DATFIFO full interrupt
 *     @arg SDIO_INT_RFIFOF Receive DATFIFO full interrupt
 *     @arg SDIO_INT_TFIFOE Transmit DATFIFO empty interrupt
 *     @arg SDIO_INT_RFIFOE Receive DATFIFO empty interrupt
 *     @arg SDIO_INT_TDATVALID Data available in transmit DATFIFO interrupt
 *     @arg SDIO_INT_RDATVALID Data available in receive DATFIFO interrupt
 *     @arg SDIO_INT_SDIOINT SD I/O interrupt received interrupt
 *     @arg SDIO_INT_CEATAF CE-ATA command completion signal received for CMD61 interrupt
 * @param Cmd new state of the specified SDIO interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 */
void SDIO_ConfigInt(uint32_t SDIO_IT, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_SDIO_INT(SDIO_IT));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the SDIO interrupts */
        SDIO->INTEN |= SDIO_IT;
    }
    else
    {
        /* Disable the SDIO interrupts */
        SDIO->INTEN &= ~SDIO_IT;
    }
}

/**
 * @brief  Enables or disables the SDIO DMA request.
 * @param Cmd new state of the selected SDIO DMA request.
 *   This parameter can be: ENABLE or DISABLE.
 */
void SDIO_DMACmd(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    *(__IO uint32_t*)DCTRL_DMAEN_BB = (uint32_t)Cmd;
}

/**
 * @brief  Initializes the SDIO Command according to the specified
 *         parameters in the SDIO_CmdInitStruct and send the command.
 * @param SDIO_CmdInitStruct pointer to a SDIO_CmdInitType
 *         structure that contains the configuration information for the SDIO command.
 */
void SDIO_SendCmd(SDIO_CmdInitType* SDIO_CmdInitStruct)
{
    uint32_t tmpregister = 0;

    /* Check the parameters */
    assert_param(IS_SDIO_CMD_INDEX(SDIO_CmdInitStruct->CmdIndex));
    assert_param(IS_SDIO_RESP(SDIO_CmdInitStruct->ResponseType));
    assert_param(IS_SDIO_WAIT(SDIO_CmdInitStruct->WaitType));
    assert_param(IS_SDIO_CPSM(SDIO_CmdInitStruct->CPSMConfig));

    /*---------------------------- SDIO CMDARG Configuration ------------------------*/
    /* Set the SDIO Argument value */
    SDIO->CMDARG = SDIO_CmdInitStruct->CmdArgument;

    /*---------------------------- SDIO CMDCTRL Configuration ------------------------*/
    /* Get the SDIO CMDCTRL value */
    tmpregister = SDIO->CMDCTRL;
    /* Clear CMDINDEX, WAITRESP, WAITINT, WAITPEND, CPSMEN bits */
    tmpregister &= CMD_CLR_MASK;
    /* Set CMDINDEX bits according to CmdIndex value */
    /* Set WAITRESP bits according to ResponseType value */
    /* Set WAITINT and WAITPEND bits according to WaitType value */
    /* Set CPSMEN bits according to CPSMConfig value */
    tmpregister |= (uint32_t)SDIO_CmdInitStruct->CmdIndex | SDIO_CmdInitStruct->ResponseType
                   | SDIO_CmdInitStruct->WaitType | SDIO_CmdInitStruct->CPSMConfig;

    /* Write to SDIO CMDCTRL */
    SDIO->CMDCTRL = tmpregister;
}

/**
 * @brief  Fills each SDIO_CmdInitStruct member with its default value.
 * @param SDIO_CmdInitStruct pointer to an SDIO_CmdInitType
 *         structure which will be initialized.
 */
void SDIO_InitCmdStruct(SDIO_CmdInitType* SDIO_CmdInitStruct)
{
    /* SDIO_CmdInitStruct members default value */
    SDIO_CmdInitStruct->CmdArgument  = 0x00;
    SDIO_CmdInitStruct->CmdIndex     = 0x00;
    SDIO_CmdInitStruct->ResponseType = SDIO_RESP_NO;
    SDIO_CmdInitStruct->WaitType     = SDIO_WAIT_NO;
    SDIO_CmdInitStruct->CPSMConfig   = SDIO_CPSM_DISABLE;
}

/**
 * @brief  Returns command index of last command for which response received.
 * @return Returns the command index of the last command response received.
 */
uint8_t SDIO_GetCmdResp(void)
{
    return (uint8_t)(SDIO->CMDRESP);
}

/**
 * @brief  Returns response received from the card for the last command.
 * @param SDIO_RESP Specifies the SDIO response register.
 *   This parameter can be one of the following values:
 *     @arg SDIO_RESPONSE_1 Response Register 1
 *     @arg SDIO_RESPONSE_2 Response Register 2
 *     @arg SDIO_RESPONSE_3 Response Register 3
 *     @arg SDIO_RESPONSE_4 Response Register 4
 * @return The Corresponding response register value.
 */
uint32_t SDIO_GetResp(uint32_t SDIO_RESP)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_SDIO_RESPONSE(SDIO_RESP));

    tmp = SDID_RESPONSE_ADDR + SDIO_RESP;

    return (*(__IO uint32_t*)tmp);
}

/**
 * @brief  Initializes the SDIO data path according to the specified
 *   parameters in the SDIO_DataInitStruct.
 * @param SDIO_DataInitStruct pointer to a SDIO_DataInitType structure that
 *   contains the configuration information for the SDIO command.
 */
void SDIO_ConfigData(SDIO_DataInitType* SDIO_DataInitStruct)
{
    uint32_t tmpregister = 0;

    /* Check the parameters */
    assert_param(IS_SDIO_DAT_LEN(SDIO_DataInitStruct->DatLen));
    assert_param(IS_SDIO_BLK_SIZE(SDIO_DataInitStruct->DatBlkSize));
    assert_param(IS_SDIO_TRANSFER_DIRECTION(SDIO_DataInitStruct->TransferDirection));
    assert_param(IS_SDIO_TRANS_MODE(SDIO_DataInitStruct->TransferMode));
    assert_param(IS_SDIO_DPSM(SDIO_DataInitStruct->DPSMConfig));

    /*---------------------------- SDIO DATTIMEOUT Configuration ---------------------*/
    /* Set the SDIO Data TimeOut value */
    SDIO->DTIMER = SDIO_DataInitStruct->DatTimeout;

    /*---------------------------- SDIO DATLEN Configuration -----------------------*/
    /* Set the SDIO DataLength value */
    SDIO->DATLEN = SDIO_DataInitStruct->DatLen;

    /*---------------------------- SDIO DATCTRL Configuration ----------------------*/
    /* Get the SDIO DATCTRL value */
    tmpregister = SDIO->DATCTRL;
    /* Clear DEN, DTMODE, DTDIR and DBCKSIZE bits */
    tmpregister &= DATCTRL_CLR_MASK;
    /* Set DEN bit according to DPSMConfig value */
    /* Set DTMODE bit according to TransferMode value */
    /* Set DTDIR bit according to TransferDirection value */
    /* Set DBCKSIZE bits according to DatBlkSize value */
    tmpregister |= (uint32_t)SDIO_DataInitStruct->DatBlkSize | SDIO_DataInitStruct->TransferDirection
                   | SDIO_DataInitStruct->TransferMode | SDIO_DataInitStruct->DPSMConfig;

    if(SDIO_DataInitStruct->TransferDirection)
    {
        tmpregister &= ~(1<<12);
    }
    else
    {
        tmpregister |= 1<<12;
    }

    /* Write to SDIO DATCTRL */
    SDIO->DATCTRL = tmpregister;
}

/**
 * @brief  Fills each SDIO_DataInitStruct member with its default value.
 * @param SDIO_DataInitStruct pointer to an SDIO_DataInitType structure which
 *         will be initialized.
 */
void SDIO_InitDataStruct(SDIO_DataInitType* SDIO_DataInitStruct)
{
    /* SDIO_DataInitStruct members default value */
    SDIO_DataInitStruct->DatTimeout        = 0xFFFFFFFF;
    SDIO_DataInitStruct->DatLen            = 0x00;
    SDIO_DataInitStruct->DatBlkSize        = SDIO_DATBLK_SIZE_1B;
    SDIO_DataInitStruct->TransferDirection = SDIO_TRANSDIR_TOCARD;
    SDIO_DataInitStruct->TransferMode      = SDIO_TRANSMODE_BLOCK;
    SDIO_DataInitStruct->DPSMConfig        = SDIO_DPSM_DISABLE;
}

/**
 * @brief  Returns number of remaining data bytes to be transferred.
 * @return Number of remaining data bytes to be transferred
 */
uint32_t SDIO_GetDataCountValue(void)
{
    return SDIO->DATCOUNT;
}

/**
 * @brief  Read one data word from Rx DATFIFO.
 * @return Data received
 */
uint32_t SDIO_ReadData(void)
{
    return SDIO->DATFIFO;
}

/**
 * @brief  Write one data word to Tx DATFIFO.
 * @param Data 32-bit data word to write.
 */
void SDIO_WriteData(uint32_t Data)
{
    SDIO->DATFIFO = Data;
}

/**
 * @brief  Returns the number of words left to be written to or read from DATFIFO.
 * @return Remaining number of words.
 */
uint32_t SDIO_GetFifoCounter(void)
{
    return SDIO->FIFOCOUNT;
}

/**
 * @brief  Starts the SD I/O Read Wait operation.
 * @param Cmd new state of the Start SDIO Read Wait operation.
 *   This parameter can be: ENABLE or DISABLE.
 */
void SDIO_EnableReadWait(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    *(__IO uint32_t*)DCTRL_RWSTART_BB = (uint32_t)Cmd;
}

/**
 * @brief  Stops the SD I/O Read Wait operation.
 * @param Cmd new state of the Stop SDIO Read Wait operation.
 *   This parameter can be: ENABLE or DISABLE.
 */
void SDIO_DisableReadWait(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    *(__IO uint32_t*)DCTRL_RWSTOP_BB = (uint32_t)Cmd;
}

/**
 * @brief  Sets one of the two options of inserting read wait interval.
 * @param SDIO_ReadWaitMode SD I/O Read Wait operation mode.
 *   This parameter can be:
 *     @arg SDIO_RDWAIT_MODE_CLK Read Wait control by stopping SDIOCLK
 *     @arg SDIO_RDWAIT_MODE_DAT2 Read Wait control using SDIO_DATA2
 */
void SDIO_EnableSdioReadWaitMode(uint32_t SDIO_ReadWaitMode)
{
    /* Check the parameters */
    assert_param(IS_SDIO_RDWAIT_MODE(SDIO_ReadWaitMode));

    *(__IO uint32_t*)DCTRL_RWMOD_BB = SDIO_ReadWaitMode;
}

/**
 * @brief  Enables or disables the SD I/O Mode Operation.
 * @param Cmd new state of SDIO specific operation.
 *   This parameter can be: ENABLE or DISABLE.
 */
void SDIO_EnableSdioOperation(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    *(__IO uint32_t*)DCTRL_SDIOEN_BB = (uint32_t)Cmd;
}

/**
 * @brief  Enables or disables the SD I/O Mode suspend command sending.
 * @param Cmd new state of the SD I/O Mode suspend command.
 *   This parameter can be: ENABLE or DISABLE.
 */
void SDIO_EnableSendSdioSuspend(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    *(__IO uint32_t*)CMD_SDIO_SUSPEND_BB = (uint32_t)Cmd;
}

/**
 * @brief  Enables or disables the command completion signal.
 * @param Cmd new state of command completion signal.
 *   This parameter can be: ENABLE or DISABLE.
 */
void SDIO_EnableCommandCompletion(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    *(__IO uint32_t*)EN_CMD_COMPL_BB = (uint32_t)Cmd;
}

/**
 * @brief  Enables or disables the CE-ATA interrupt.
 * @param Cmd new state of CE-ATA interrupt. This parameter can be: ENABLE or DISABLE.
 */
void SDIO_EnableCEATAInt(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    *(__IO uint32_t*)CMD_NIEN_BB = (uint32_t)((~((uint32_t)Cmd)) & ((uint32_t)0x1));
}

/**
 * @brief  Sends CE-ATA command (CMD61).
 * @param Cmd new state of CE-ATA command. This parameter can be: ENABLE or DISABLE.
 */
void SDIO_EnableSendCEATA(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    *(__IO uint32_t*)CMD_ATACMD_BB = (uint32_t)Cmd;
}

/**
 * @brief  Checks whether the specified SDIO flag is set or not.
 * @param SDIO_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg SDIO_FLAG_CCRCERR Command response received (CRC check failed)
 *     @arg SDIO_FLAG_DCRCERR Data block sent/received (CRC check failed)
 *     @arg SDIO_FLAG_CMDTIMEOUT Command response timeout
 *     @arg SDIO_FLAG_DATTIMEOUT Data timeout
 *     @arg SDIO_FLAG_TXURERR Transmit DATFIFO underrun error
 *     @arg SDIO_FLAG_RXORERR Received DATFIFO overrun error
 *     @arg SDIO_FLAG_CMDRESPRECV Command response received (CRC check passed)
 *     @arg SDIO_FLAG_CMDSEND Command sent (no response required)
 *     @arg SDIO_FLAG_DATEND Data end (data counter, SDIDCOUNT, is zero)
 *     @arg SDIO_FLAG_SBERR Start bit not detected on all data signals in wide
 *                              bus mode.
 *     @arg SDIO_FLAG_DATBLKEND Data block sent/received (CRC check passed)
 *     @arg SDIO_FLAG_CMDRUN Command transfer in progress
 *     @arg SDIO_FLAG_TXRUN Data transmit in progress
 *     @arg SDIO_FLAG_RXRUN Data receive in progress
 *     @arg SDIO_FLAG_TFIFOHE Transmit DATFIFO Half Empty
 *     @arg SDIO_FLAG_RFIFOHF Receive DATFIFO Half Full
 *     @arg SDIO_FLAG_TFIFOF Transmit DATFIFO full
 *     @arg SDIO_FLAG_RFIFOF Receive DATFIFO full
 *     @arg SDIO_FLAG_TFIFOE Transmit DATFIFO empty
 *     @arg SDIO_FLAG_RFIFOE Receive DATFIFO empty
 *     @arg SDIO_FLAG_TDATVALID Data available in transmit DATFIFO
 *     @arg SDIO_FLAG_RDATVALID Data available in receive DATFIFO
 *     @arg SDIO_FLAG_SDIOINT SD I/O interrupt received
 *     @arg SDIO_FLAG_CEATAF CE-ATA command completion signal received for CMD61
 * @return The new state of SDIO_FLAG (SET or RESET).
 */
FlagStatus SDIO_GetFlag(uint32_t SDIO_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_SDIO_FLAG(SDIO_FLAG));

    if ((SDIO->STS & SDIO_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Clears the SDIO's pending flags.
 * @param SDIO_FLAG specifies the flag to clear.
 *   This parameter can be one or a combination of the following values:
 *     @arg SDIO_FLAG_CCRCERR Command response received (CRC check failed)
 *     @arg SDIO_FLAG_DCRCERR Data block sent/received (CRC check failed)
 *     @arg SDIO_FLAG_CMDTIMEOUT Command response timeout
 *     @arg SDIO_FLAG_DATTIMEOUT Data timeout
 *     @arg SDIO_FLAG_TXURERR Transmit DATFIFO underrun error
 *     @arg SDIO_FLAG_RXORERR Received DATFIFO overrun error
 *     @arg SDIO_FLAG_CMDRESPRECV Command response received (CRC check passed)
 *     @arg SDIO_FLAG_CMDSEND Command sent (no response required)
 *     @arg SDIO_FLAG_DATEND Data end (data counter, SDIDCOUNT, is zero)
 *     @arg SDIO_FLAG_SBERR Start bit not detected on all data signals in wide
 *                              bus mode
 *     @arg SDIO_FLAG_DATBLKEND Data block sent/received (CRC check passed)
 *     @arg SDIO_FLAG_SDIOINT SD I/O interrupt received
 *     @arg SDIO_FLAG_CEATAF CE-ATA command completion signal received for CMD61
 */
void SDIO_ClrFlag(uint32_t SDIO_FLAG)
{
    /* Check the parameters */
    assert_param(IS_SDIO_CLR_FLAG(SDIO_FLAG));

    SDIO->INTCLR = SDIO_FLAG;
}

/**
 * @brief  Checks whether the specified SDIO interrupt has occurred or not.
 * @param SDIO_IT specifies the SDIO interrupt source to check.
 *   This parameter can be one of the following values:
 *     @arg SDIO_INT_CCRCERR Command response received (CRC check failed) interrupt
 *     @arg SDIO_INT_DCRCERR Data block sent/received (CRC check failed) interrupt
 *     @arg SDIO_INT_CMDTIMEOUT Command response timeout interrupt
 *     @arg SDIO_INT_DATTIMEOUT Data timeout interrupt
 *     @arg SDIO_INT_TXURERR Transmit DATFIFO underrun error interrupt
 *     @arg SDIO_INT_RXORERR Received DATFIFO overrun error interrupt
 *     @arg SDIO_INT_CMDRESPRECV Command response received (CRC check passed) interrupt
 *     @arg SDIO_INT_CMDSEND Command sent (no response required) interrupt
 *     @arg SDIO_INT_DATEND Data end (data counter, SDIDCOUNT, is zero) interrupt
 *     @arg SDIO_INT_SBERR Start bit not detected on all data signals in wide
 *                            bus mode interrupt
 *     @arg SDIO_INT_DATBLKEND Data block sent/received (CRC check passed) interrupt
 *     @arg SDIO_INT_CMDRUN Command transfer in progress interrupt
 *     @arg SDIO_INT_TXRUN Data transmit in progress interrupt
 *     @arg SDIO_INT_RXRUN Data receive in progress interrupt
 *     @arg SDIO_INT_TFIFOHE Transmit DATFIFO Half Empty interrupt
 *     @arg SDIO_INT_RFIFOHF Receive DATFIFO Half Full interrupt
 *     @arg SDIO_INT_TFIFOF Transmit DATFIFO full interrupt
 *     @arg SDIO_INT_RFIFOF Receive DATFIFO full interrupt
 *     @arg SDIO_INT_TFIFOE Transmit DATFIFO empty interrupt
 *     @arg SDIO_INT_RFIFOE Receive DATFIFO empty interrupt
 *     @arg SDIO_INT_TDATVALID Data available in transmit DATFIFO interrupt
 *     @arg SDIO_INT_RDATVALID Data available in receive DATFIFO interrupt
 *     @arg SDIO_INT_SDIOINT SD I/O interrupt received interrupt
 *     @arg SDIO_INT_CEATAF CE-ATA command completion signal received for CMD61 interrupt
 * @return The new state of SDIO_IT (SET or RESET).
 */
INTStatus SDIO_GetIntStatus(uint32_t SDIO_IT)
{
    INTStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_SDIO_GET_INT(SDIO_IT));
    if ((SDIO->STS & SDIO_IT) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Clears the SDIO's interrupt pending bits.
 * @param SDIO_IT specifies the interrupt pending bit to clear.
 *   This parameter can be one or a combination of the following values:
 *     @arg SDIO_INT_CCRCERR Command response received (CRC check failed) interrupt
 *     @arg SDIO_INT_DCRCERR Data block sent/received (CRC check failed) interrupt
 *     @arg SDIO_INT_CMDTIMEOUT Command response timeout interrupt
 *     @arg SDIO_INT_DATTIMEOUT Data timeout interrupt
 *     @arg SDIO_INT_TXURERR Transmit DATFIFO underrun error interrupt
 *     @arg SDIO_INT_RXORERR Received DATFIFO overrun error interrupt
 *     @arg SDIO_INT_CMDRESPRECV Command response received (CRC check passed) interrupt
 *     @arg SDIO_INT_CMDSEND Command sent (no response required) interrupt
 *     @arg SDIO_INT_DATEND Data end (data counter, SDIDCOUNT, is zero) interrupt
 *     @arg SDIO_INT_SBERR Start bit not detected on all data signals in wide
 *                            bus mode interrupt
 *     @arg SDIO_INT_SDIOINT SD I/O interrupt received interrupt
 *     @arg SDIO_INT_CEATAF CE-ATA command completion signal received for CMD61
 */
void SDIO_ClrIntPendingBit(uint32_t SDIO_IT)
{
    /* Check the parameters */
    assert_param(IS_SDIO_CLR_INT(SDIO_IT));

    SDIO->INTCLR = SDIO_IT;
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
