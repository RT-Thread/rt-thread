/**
 **************************************************************************
 * File Name    : at32f4xx_sdio.c
 * Description  : at32f4xx SDIO source file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_sdio.h"
#include "at32f4xx_rcc.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup SDIO
  * @brief SDIO driver modules
  * @{
  */

/** @defgroup SDIO_Private_TypesDefinitions
  * @{
  */

/* --- CLKCR Register ---*/

/* SDIO CLKEN mask */
#define CLKCTRL_CLKEN_Set           ((uint32_t)0x00000100)
#define CLKCTRL_CLKEN_Rst           ((uint32_t)0xFFFFFEFF)


/* --- CMD Register ---*/

/* SDIO SDIOSUSPEND mask */
#define CMD_SDIOSUSP_Set            ((uint32_t)0x00000800)
#define CMD_SDIOSUSP_Rst            ((uint32_t)0xFFFFF7FF)

/* SDIO ENCMDCOMPL mask */
#define CMD_CMPLSGNLEN_Set          ((uint32_t)0x00001000)
#define CMD_CMPLSGNLEN_Rst          ((uint32_t)0xFFFFEFFF)

/* SDIO INTDIS mask */
#define CMD_INTDIS_Set              ((uint32_t)0x00002000)
#define CMD_INTDIS_Rst              ((uint32_t)0xFFFFDFFF)

/* SDIO ATACMD mask */
#define CMD_ATACMD_Set              ((uint32_t)0x00004000)
#define CMD_ATACMD_Rst              ((uint32_t)0xFFFFBFFF)


/* --- DTCTRL Register ---*/

/* SDIO ATACMD mask */
#define DTCTRL_DMAEN_Set            ((uint32_t)0x00000008)
#define DTCTRL_DMAEN_Rst            ((uint32_t)0xFFFFFFF7)

/* SDIO RWSTART mask */
#define DTCTRL_RWSTART_Set          ((uint32_t)0x00000100)
#define DTCTRL_RWSTART_Rst          ((uint32_t)0xFFFFFEFF)

/* SDIO RWSTOP mask */
#define DTCTRL_RWSTOP_Set           ((uint32_t)0x00000200)
#define DTCTRL_RWSTOP_Rst           ((uint32_t)0xFFFFFDFF)

/* SDIO RWMOD mask */
#define DTCTRL_RWMOD_Set            ((uint32_t)0x00000400)

/* SDIO SDIOEN mask */
#define DTCTRL_SDIOEN_Set           ((uint32_t)0x00000800)
#define DTCTRL_SDIOEN_Rst           ((uint32_t)0xFFFFF7FF)

/* ---------------------- SDIO registers bit mask ------------------------ */

/* --- CLKCR Register ---*/

/* CLKCR register clear mask */
#define CLKCTRL_CLEAR_MASK          ((uint32_t)0xFFFE0100)

/* --- PWRCTRL Register ---*/

/* SDIO PWRCTRL Mask */
#define PWR_PWRCTRL_MASK            ((uint32_t)0xFFFFFFFC)

/* --- DTCTRL Register ---*/

/* SDIO DTCTRL Clear Mask */
#define DTCTRL_CLEAR_MASK           ((uint32_t)0xFFFFFF08)
#define DTCTRL_RWMOD_MASK           ((uint32_t)0xFFFFFBFF)

/* --- CMD Register ---*/

/* CMD Register clear mask */
#define CMD_CLEAR_MASK              ((uint32_t)0xFFFFF800)

/* SDIO RESP Registers Address Offset */
#define SDIO_RSP_ADDR_OFFSET        ((uint32_t)0x14)

/**
  * @}
  */

/** @defgroup SDIO_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @defgroup SDIO_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup SDIO_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup SDIO_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup SDIO_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the SDIO peripheral registers to their default reset values.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @retval None
  */
void SDIO_Reset(SDIO_Type * SDIOx)
{
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  SDIOx->POWER = 0x00000000;
  SDIOx->CLKCTRL = 0x00000000;
  SDIOx->ARG = 0x00000000;
  SDIOx->CMD = 0x00000000;
  SDIOx->DTTMR = 0x00000000;
  SDIOx->DTLEN = 0x00000000;
  SDIOx->DTCTRL = 0x00000000;
  SDIOx->INTCLR = 0x00C007FF;
  SDIOx->INTEN = 0x00000000;
}

/**
  * @brief  Initializes the SDIO peripheral according to the specified
  *         parameters in the SDIO_InitStruct.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  SDIO_InitStruct : pointer to a SDIO_InitType structure
  *         that contains the configuration information for the SDIO peripheral.
  * @retval None
  */
void SDIO_Init(SDIO_Type * SDIOx, SDIO_InitType* SDIO_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_SDIO_CLK_EDGE(SDIO_InitStruct->SDIO_ClkEdge));
  assert_param(IS_SDIO_CLK_BYPASS(SDIO_InitStruct->SDIO_ClkBypass));
  assert_param(IS_SDIO_CLK_POWER_SAVE(SDIO_InitStruct->SDIO_ClkPowerSave));
  assert_param(IS_SDIO_BUS_WIDTH(SDIO_InitStruct->SDIO_BusWidth));
  assert_param(IS_SDIO_FLOW_CTRL(SDIO_InitStruct->SDIO_FlowCtrl));

  /*---------------------------- SDIO CLKCR Configuration ------------------------*/
  /* Get the SDIOx CLKCR value */
  tmpreg = SDIOx->CLKCTRL;

  /* Clear CLKDIV, PWRSAV, BYPASS, WIDBUS, NEGEDGE, HWFC_EN bits */
  tmpreg &= CLKCTRL_CLEAR_MASK;

  /* Set PWRSAV bit according to SDIO_ClockPowerSave value */
  /* Set BYPASS bit according to SDIO_ClockBypass value */
  /* Set WIDBUS bits according to SDIO_BusWide value */
  /* Set NEGEDGE bits according to SDIO_ClockEdge value */
  /* Set HWFC_EN bits according to SDIO_HardwareFlowControl value */
  tmpreg |= (SDIO_InitStruct->SDIO_ClkPowerSave | SDIO_InitStruct->SDIO_ClkBypass |
             SDIO_InitStruct->SDIO_BusWidth | SDIO_InitStruct->SDIO_ClkEdge | SDIO_InitStruct->SDIO_FlowCtrl);

  /* Set CLKDIV bits according to SDIO_ClockDiv value */
  tmpreg |= ((SDIO_InitStruct->SDIO_ClkPsc & 0x00FF) | ((SDIO_InitStruct->SDIO_ClkPsc & 0x0300) << 7));
  /* Write to SDIOx CLKCR */
  SDIOx->CLKCTRL = tmpreg;
}

/**
  * @brief  Fills each SDIO_InitStruct member with its default value.
  * @param  SDIO_InitStruct: pointer to an SDIO_InitType structure which
  *   will be initialized.
  * @retval None
  */
void SDIO_StructInit(SDIO_InitType* SDIO_InitStruct)
{
  /* SDIO_InitStruct members default value */
  SDIO_InitStruct->SDIO_ClkPsc = 0x00;
  SDIO_InitStruct->SDIO_ClkEdge = SDIO_ClkEdge_Rising;
  SDIO_InitStruct->SDIO_ClkBypass = SDIO_ClkBypass_Disable;
  SDIO_InitStruct->SDIO_ClkPowerSave = SDIO_ClkPowerSave_Disable;
  SDIO_InitStruct->SDIO_BusWidth = SDIO_BusWidth_1b;
  SDIO_InitStruct->SDIO_FlowCtrl = SDIO_FlowCtrl_Disable;
}

/**
  * @brief  Enables or disables the SDIO Clock.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  NewState: new state of the SDIO Clock. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_ClockCmd(SDIO_Type * SDIOx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the SDIO Clock. */
    SDIOx->CLKCTRL |= CLKCTRL_CLKEN_Set;
  }
  else
  {
    /* Disable the SDIO Clock. */
    SDIOx->CLKCTRL &= CLKCTRL_CLKEN_Rst;
  }
}

/**
  * @brief  Sets the power status of the controller.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  SDIO_PowerState: new state of the Power state.
  *   This parameter can be one of the following values:
  *     @arg SDIO_PowerSave_OFF
  *     @arg SDIO_PowerSave_ON
  * @retval None
  */
void SDIO_SetPowerSaveState(SDIO_Type * SDIOx, uint32_t SDIO_PowerState)
{
  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_SDIO_POWER_SAVE(SDIO_PowerState));

  SDIOx->POWER &= PWR_PWRCTRL_MASK;
  SDIOx->POWER |= SDIO_PowerState;
}

/**
  * @brief  Gets the power status of the controller.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @retval Power status of the controller. The returned value can
  *   be one of the following:
  * - 0x00: Power OFF
  * - 0x02: Power UP
  * - 0x03: Power ON
  */
uint32_t SDIO_GetPowerSaveState(SDIO_Type * SDIOx)
{
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  return (SDIOx->POWER & (~PWR_PWRCTRL_MASK));
}

/**
  * @brief  Enables or disables the SDIO interrupts.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  SDIO_INT: specifies the SDIO interrupt sources to be enabled or disabled.
  *   This parameter can be one or a combination of the following values:
  *     @arg SDIO_INT_CMDFAIL:    Command response received (CRC check failed) interrupt
  *     @arg SDIO_INT_DTFAIL:     Data block sent/received (CRC check failed) interrupt
  *     @arg SDIO_INT_CMDTIMEOUT: Command response timeout interrupt
  *     @arg SDIO_INT_DTTIMEOUT:  Data timeout interrupt
  *     @arg SDIO_INT_TXERRU:     Transmit FIFO underrun error interrupt
  *     @arg SDIO_INT_RXERRO:     Received FIFO overrun error interrupt
  *     @arg SDIO_INT_CMDRSPCMPL: Command response received (CRC check passed) interrupt
  *     @arg SDIO_INT_CMDCMPL:    Command sent (no response required) interrupt
  *     @arg SDIO_INT_DTCMPL:     Data end (data counter, SDIDCOUNT, is zero) interrupt
  *     @arg SDIO_INT_SBITERR:    Start bit not detected on all data signals in wide bus mode interrupt
  *     @arg SDIO_INT_DTBLKCMPL:  Data block sent/received (CRC check passed) interrupt
  *     @arg SDIO_INT_DOCMD:      Command transfer in progress interrupt
  *     @arg SDIO_INT_DOTX:       Data transmit in progress interrupt
  *     @arg SDIO_INT_DORX:       Data receive in progress interrupt
  *     @arg SDIO_INT_TXBUF_H:    Transmit FIFO Half Empty interrupt
  *     @arg SDIO_INT_RXBUF_H:    Receive FIFO Half Full interrupt
  *     @arg SDIO_INT_TXBUF_F:    Transmit FIFO full interrupt
  *     @arg SDIO_INT_RXBUF_F:    Receive FIFO full interrupt
  *     @arg SDIO_INT_TXBUF_E:    Transmit FIFO empty interrupt
  *     @arg SDIO_INT_RXBUF_E:    Receive FIFO empty interrupt
  *     @arg SDIO_INT_TXBUF:      Data available in transmit FIFO interrupt
  *     @arg SDIO_INT_RXBUF:      Data available in receive FIFO interrupt
  *     @arg SDIO_INT_SDIOIF:     SD I/O interrupt received interrupt
  *     @arg SDIO_INT_ATACMPL:    CE-ATA command completion signal received for CMD61 interrupt
  * @param  NewState: new state of the specified SDIO interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_INTConfig(SDIO_Type * SDIOx, uint32_t SDIO_INT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_SDIO_INT(SDIO_INT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the SDIO interrupts */
    SDIOx->INTEN |= SDIO_INT;
  }
  else
  {
    /* Disable the SDIO interrupts */
    SDIOx->INTEN &= ~SDIO_INT;
  }
}

/**
  * @brief  Enables or disables the SDIO DMA request.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  NewState: new state of the selected SDIO DMA request.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_DMACmd(SDIO_Type * SDIOx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected SDIO DMA request. */
    SDIOx->DTCTRL |= DTCTRL_DMAEN_Set;
  }
  else
  {
    /* Disable the selected SDIO DMA request. */
    SDIOx->DTCTRL &= DTCTRL_DMAEN_Rst;
  }
}

/**
  * @brief  Initializes the SDIO Command according to the specified
  *         parameters in the SDIO_CmdInitStruct and send the command.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  SDIO_CmdInitStruct : pointer to a SDIO_CmdInitType
  *         structure that contains the configuration information for the SDIO command.
  * @retval None
  */
void SDIO_SendCommand(SDIO_Type * SDIOx, SDIO_CmdInitType *SDIO_CmdInitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_SDIO_CMD_IDX(SDIO_CmdInitStruct->SDIO_CmdIdx));
  assert_param(IS_SDIO_RSP_TYPE(SDIO_CmdInitStruct->SDIO_Resp));
  assert_param(IS_SDIO_WAIT(SDIO_CmdInitStruct->SDIO_Wait));
  assert_param(IS_SDIO_CPSM(SDIO_CmdInitStruct->SDIO_CPSM));

  /*---------------------------- SDIOx ARG Configuration ------------------------*/
  /* Set the SDIOx Argument value */
  SDIOx->ARG = SDIO_CmdInitStruct->SDIO_Argu;

  /*---------------------------- SDIOx CMD Configuration ------------------------*/
  /* Get the SDIOx CMD value */
  tmpreg = SDIOx->CMD;
  /* Clear CMDINDEX, WAITRESP, WAITINT, WAITPEND, CPSMEN bits */
  tmpreg &= CMD_CLEAR_MASK;
  /* Set CMDINDEX bits according to SDIO_CmdIndex value */
  /* Set WAITRESP bits according to SDIO_Response value */
  /* Set WAITINT and WAITPEND bits according to SDIO_Wait value */
  /* Set CPSMEN bits according to SDIO_CPSM value */
  tmpreg |= (uint32_t)SDIO_CmdInitStruct->SDIO_CmdIdx | SDIO_CmdInitStruct->SDIO_Resp
            | SDIO_CmdInitStruct->SDIO_Wait | SDIO_CmdInitStruct->SDIO_CPSM;

  /* Write to SDIOx CMD */
  SDIOx->CMD = tmpreg;
}

/**
  * @brief  Fills each SDIO_CmdInitStruct member with its default value.
  * @param  SDIO_CmdInitStruct: pointer to an SDIO_CmdInitType
  *         structure which will be initialized.
  * @retval None
  */
void SDIO_CmdStructInit(SDIO_CmdInitType* SDIO_CmdInitStruct)
{
  /* SDIO_CmdInitStruct members default value */
  SDIO_CmdInitStruct->SDIO_Argu = 0x00;
  SDIO_CmdInitStruct->SDIO_CmdIdx = 0x00;
  SDIO_CmdInitStruct->SDIO_Resp = SDIO_Rsp_No;
  SDIO_CmdInitStruct->SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStruct->SDIO_CPSM = SDIO_CPSM_Disable;
}

/**
  * @brief  Returns command index of last command for which response received.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @retval Returns the command index of the last command response received.
  */
uint8_t SDIO_GetCommandResponse(SDIO_Type * SDIOx)
{
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  return (uint8_t)(SDIOx->RSPCMD);
}

/**
  * @brief  Returns response received from the card for the last command.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  SDIO_RESP: Specifies the SDIO response register.
  *   This parameter can be one of the following values:
  *     @arg SDIO_RSP1: Response Register 1
  *     @arg SDIO_RSP2: Response Register 2
  *     @arg SDIO_RSP3: Response Register 3
  *     @arg SDIO_RSP4: Response Register 4
  * @retval The Corresponding response register value.
  */
uint32_t SDIO_GetResponse(SDIO_Type * SDIOx, uint32_t SDIO_RESP)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_SDIO_RSP(SDIO_RESP));

  tmp = (uint32_t)&SDIOx->RSP1 + SDIO_RESP;

  return (*(__IO uint32_t *) tmp);
}

/**
  * @brief  Initializes the SDIO data path according to the specified
  *   parameters in the SDIO_DataInitStruct.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  SDIO_DataInitStruct : pointer to a SDIO_DataInitType structure that
  *   contains the configuration information for the SDIO command.
  * @retval None
  */
void SDIO_DataConfig(SDIO_Type * SDIOx, SDIO_DataInitType* SDIO_DataInitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_SDIO_DATA_LEN(SDIO_DataInitStruct->SDIO_DataLen));
  assert_param(IS_SDIO_BLK_SIZE(SDIO_DataInitStruct->SDIO_DataBlkSize));
  assert_param(IS_SDIO_TRANSFER_DIR(SDIO_DataInitStruct->SDIO_TransferDir));
  assert_param(IS_SDIO_TRANSFER_MODE(SDIO_DataInitStruct->SDIO_TransferMode));
  assert_param(IS_SDIO_DPSM(SDIO_DataInitStruct->SDIO_DPSM));

  /*---------------------------- SDIO DTIMER Configuration ---------------------*/
  /* Set the SDIOx Data TimeOut value */
  SDIOx->DTTMR = SDIO_DataInitStruct->SDIO_DataTimeOut;

  /*---------------------------- SDIOx DLEN Configuration -----------------------*/
  /* Set the SDIOx DataLength value */
  SDIOx->DTLEN = SDIO_DataInitStruct->SDIO_DataLen;

  /*---------------------------- SDIO DTCTRL Configuration ----------------------*/
  /* Get the SDIOx DTCTRL value */
  tmpreg = SDIOx->DTCTRL;
  /* Clear DEN, DTMODE, DTDIR and DBCKSIZE bits */
  tmpreg &= DTCTRL_CLEAR_MASK;
  /* Set DEN bit according to SDIO_DPSM value */
  /* Set DTMODE bit according to SDIO_TransferMode value */
  /* Set DTDIR bit according to SDIO_TransferDir value */
  /* Set DBCKSIZE bits according to SDIO_DataBlockSize value */
  tmpreg |= (uint32_t)SDIO_DataInitStruct->SDIO_DataBlkSize | SDIO_DataInitStruct->SDIO_TransferDir
            | SDIO_DataInitStruct->SDIO_TransferMode | SDIO_DataInitStruct->SDIO_DPSM;

  /* Write to SDIOx DTCTRL */
  SDIOx->DTCTRL = tmpreg;
}

/**
  * @brief  Fills each SDIO_DataInitStruct member with its default value.
  * @param  SDIO_DataInitStruct: pointer to an SDIO_DataInitType structure which
  *         will be initialized.
  * @retval None
  */
void SDIO_DataStructInit(SDIO_DataInitType* SDIO_DataInitStruct)
{
  /* SDIO_DataInitStruct members default value */
  SDIO_DataInitStruct->SDIO_DataTimeOut = 0xFFFFFFFF;
  SDIO_DataInitStruct->SDIO_DataLen = 0x00;
  SDIO_DataInitStruct->SDIO_DataBlkSize = SDIO_DataBlkSize_1b;
  SDIO_DataInitStruct->SDIO_TransferDir = SDIO_TransferDir_ToCard;
  SDIO_DataInitStruct->SDIO_TransferMode = SDIO_TransferMode_Block;
  SDIO_DataInitStruct->SDIO_DPSM = SDIO_DPSM_Disable;
}

/**
  * @brief  Returns number of remaining data bytes to be transferred.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @retval Number of remaining data bytes to be transferred
  */
uint32_t SDIO_GetDataCounter(SDIO_Type * SDIOx)
{
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  return SDIOx->DTCNTR;
}

/**
  * @brief  Read one data word from Rx FIFO.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @retval Data received
  */
uint32_t SDIO_ReadData(SDIO_Type * SDIOx)
{
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  return SDIOx->BUF;
}

/**
  * @brief  Write one data word to Tx FIFO.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  Data: 32-bit data word to write.
  * @retval None
  */
void SDIO_WriteData(SDIO_Type * SDIOx, uint32_t Data)
{
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  SDIOx->BUF = Data;
}

/**
  * @brief  Returns the number of words left to be written to or read from FIFO.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @retval Remaining number of words.
  */
uint32_t SDIO_GetBUFCount(SDIO_Type * SDIOx)
{
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  return SDIOx->BUFCNTR;
}

/**
  * @brief  Starts the SD I/O Read Wait operation.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  NewState: new state of the Start SDIO Read Wait operation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_StartSDIOReadWait(SDIO_Type * SDIOx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Start SDIO Read Wait operation. */
    SDIOx->DTCTRL |= DTCTRL_RWSTART_Set;
  }
  else
  {
    /* Disable the Start SDIO Read Wait operation. */
    SDIOx->DTCTRL &= DTCTRL_RWSTART_Rst;
  }
}

/**
  * @brief  Stops the SD I/O Read Wait operation.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  NewState: new state of the Stop SDIO Read Wait operation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_StopSDIOReadWait(SDIO_Type * SDIOx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Stop SDIO Read Wait operation. */
    SDIOx->DTCTRL |= DTCTRL_RWSTOP_Set;
  }
  else
  {
    /* Disable the Stop SDIO Read Wait operation. */
    SDIOx->DTCTRL &= DTCTRL_RWSTOP_Rst;
  }
}

/**
  * @brief  Sets one of the two options of inserting read wait interval.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  SDIO_ReadWaitMode: SD I/O Read Wait operation mode.
  *   This parameter can be:
  *     @arg SDIO_ReadWaitMode_CLK: Read Wait control by stopping SDIOCLK
  *     @arg SDIO_ReadWaitMode_DATA2: Read Wait control using SDIO_DATA2
  * @retval None
  */
void SDIO_SetSDIOReadWaitMode(SDIO_Type * SDIOx, uint32_t SDIO_ReadWaitMode)
{
  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_SDIO_READWAIT_MODE(SDIO_ReadWaitMode));

  SDIOx->DTCTRL &= DTCTRL_RWMOD_MASK;

  SDIOx->DTCTRL |= SDIO_ReadWaitMode;
}

/**
  * @brief  Enables or disables the SD I/O Mode Operation.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  NewState: new state of SDIO specific operation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_SetSDIOOperation(SDIO_Type * SDIOx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable SDIO specific operation. */
    SDIOx->DTCTRL |= DTCTRL_SDIOEN_Set;
  }
  else
  {
    /* Disable SDIO specific operation. */
    SDIOx->DTCTRL &= DTCTRL_SDIOEN_Rst;
  }
}

/**
  * @brief  Enables or disables the SD I/O Mode suspend command sending.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  NewState: new state of the SD I/O Mode suspend command.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_SendSDIOSuspendCmd(SDIO_Type * SDIOx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable SD I/O Mode suspend command. */
    SDIOx->CMD |= CMD_SDIOSUSP_Set;
  }
  else
  {
    /* Disable SD I/O Mode suspend command. */
    SDIOx->CMD &= CMD_SDIOSUSP_Rst;
  }
}

/**
  * @brief  Enables or disables the command completion signal.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  NewState: new state of command completion signal.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_CommandCompletionCmd(SDIO_Type * SDIOx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the command completion signal. */
    SDIOx->CMD |= CMD_CMPLSGNLEN_Set;
  }
  else
  {
    /* Disable the command completion signal. */
    SDIOx->CMD &= CMD_CMPLSGNLEN_Rst;
  }
}

/**
  * @brief  Enables or disables the CE-ATA interrupt.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  NewState: new state of CE-ATA interrupt. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_ATAINTCmd(SDIO_Type * SDIOx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable ATA Interrupt. */
    SDIOx->CMD &= CMD_INTDIS_Rst;
  }
  else
  {
    /* Disable CE-ATA command. */
    SDIOx->CMD |= CMD_INTDIS_Set;
  }
}

/**
  * @brief  Sends CE-ATA command (CMD61).
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  NewState: new state of CE-ATA command. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_SendATACmd(SDIO_Type * SDIOx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable CE-ATA command. */
    SDIOx->CMD |= CMD_ATACMD_Set;
  }
  else
  {
    /* Disable CE-ATA command. */
    SDIOx->CMD &= CMD_ATACMD_Rst;
  }
}

/**
  * @brief  Checks whether the specified SDIO flag is set or not.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  SDIO_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg SDIO_FLG_CMDFAIL:    Command response received (CRC check failed)
  *     @arg SDIO_FLG_DTFAIL:     Data block sent/received (CRC check failed)
  *     @arg SDIO_FLG_CMDTIMEOUT: Command response timeout
  *     @arg SDIO_FLG_DTTIMEOUT:  Data timeout
  *     @arg SDIO_FLG_TXERRU:     Transmit FIFO underrun error
  *     @arg SDIO_FLG_RXERRO:     Received FIFO overrun error
  *     @arg SDIO_FLG_CMDRSPCMPL: Command response received (CRC check passed)
  *     @arg SDIO_FLG_CMDCMPL:    Command sent (no response required)
  *     @arg SDIO_FLG_DTCMPL:     Data end (data counter, SDIDCOUNT, is zero)
  *     @arg SDIO_FLG_SBITERR:    Start bit not detected on all data signals in wide bus mode.
  *     @arg SDIO_FLG_DTBLKCMPL:  Data block sent/received (CRC check passed)
  *     @arg SDIO_FLG_DOCMD:      Command transfer in progress
  *     @arg SDIO_FLG_DOTX:       Data transmit in progress
  *     @arg SDIO_FLG_DORX:       Data receive in progress
  *     @arg SDIO_FLG_TXBUF_H:    Transmit FIFO Half Empty
  *     @arg SDIO_FLG_RXBUF_H:    Receive FIFO Half Full
  *     @arg SDIO_FLG_TXBUF_F:    Transmit FIFO full
  *     @arg SDIO_FLG_RXBUF_F:    Receive FIFO full
  *     @arg SDIO_FLG_TXBUF_E:    Transmit FIFO empty
  *     @arg SDIO_FLG_RXBUF_E:    Receive FIFO empty
  *     @arg SDIO_FLG_TXBUF:      Data available in transmit FIFO
  *     @arg SDIO_FLG_RXBUF:      Data available in receive FIFO
  *     @arg SDIO_FLG_SDIOIF:     SD I/O interrupt received
  *     @arg SDIO_FLG_ATACMPL:    CE-ATA command completion signal received for CMD61
  * @retval The new state of SDIO_FLAG (SET or RESET).
  */
FlagStatus SDIO_GetFlagStatus(SDIO_Type * SDIOx, uint32_t SDIO_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_SDIO_FLG(SDIO_FLAG));

  if ((SDIOx->STS & SDIO_FLAG) != (uint32_t)RESET)
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
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  SDIO_FLAG: specifies the flag to clear.
  *   This parameter can be one or a combination of the following values:
  *     @arg SDIO_FLG_CMDFAIL:    Command response received (CRC check failed)
  *     @arg SDIO_FLG_DTFAIL:     Data block sent/received (CRC check failed)
  *     @arg SDIO_FLG_CMDTIMEOUT: Command response timeout
  *     @arg SDIO_FLG_DTTIMEOUT:  Data timeout
  *     @arg SDIO_FLG_TXERRU:     Transmit FIFO underrun error
  *     @arg SDIO_FLG_RXERRO:     Received FIFO overrun error
  *     @arg SDIO_FLG_CMDRSPCMPL: Command response received (CRC check passed)
  *     @arg SDIO_FLG_CMDCMPL:    Command sent (no response required)
  *     @arg SDIO_FLG_DTCMPL:     Data end (data counter, SDIDCOUNT, is zero)
  *     @arg SDIO_FLG_SBITERR:    Start bit not detected on all data signals in wide bus mode
  *     @arg SDIO_FLG_DTBLKCMPL:  Data block sent/received (CRC check passed)
  *     @arg SDIO_FLG_SDIOIF:     SD I/O interrupt received
  *     @arg SDIO_FLG_ATACMPL:    CE-ATA command completion signal received for CMD61
  * @retval None
  */
void SDIO_ClearFlag(SDIO_Type * SDIOx, uint32_t SDIO_FLAG)
{
  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_SDIO_CLEAR_FLG(SDIO_FLAG));

  SDIOx->INTCLR = SDIO_FLAG;
}

/**
  * @brief  Checks whether the specified SDIO interrupt has occurred or not.
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  SDIO_INT: specifies the SDIO interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg SDIO_INT_CMDFAIL:    Command response received (CRC check failed) interrupt
  *     @arg SDIO_INT_DTFAIL:     Data block sent/received (CRC check failed) interrupt
  *     @arg SDIO_INT_CMDTIMEOUT: Command response timeout interrupt
  *     @arg SDIO_INT_DTTIMEOUT:  Data timeout interrupt
  *     @arg SDIO_INT_TXERRU:     Transmit FIFO underrun error interrupt
  *     @arg SDIO_INT_RXERRO:     Received FIFO overrun error interrupt
  *     @arg SDIO_INT_CMDRSPCMPL: Command response received (CRC check passed) interrupt
  *     @arg SDIO_INT_CMDCMPL:    Command sent (no response required) interrupt
  *     @arg SDIO_INT_DTCMPL:     Data end (data counter, SDIDCOUNT, is zero) interrupt
  *     @arg SDIO_INT_SBITERR:    Start bit not detected on all data signals in wide bus mode interrupt
  *     @arg SDIO_INT_DTBLKCMPL:  Data block sent/received (CRC check passed) interrupt
  *     @arg SDIO_INT_DOCMD:      Command transfer in progress interrupt
  *     @arg SDIO_INT_DOTX:       Data transmit in progress interrupt
  *     @arg SDIO_INT_DORX:       Data receive in progress interrupt
  *     @arg SDIO_INT_TXBUF_H:    Transmit FIFO Half Empty interrupt
  *     @arg SDIO_INT_RXBUF_H:    Receive FIFO Half Full interrupt
  *     @arg SDIO_INT_TXBUF_F:    Transmit FIFO full interrupt
  *     @arg SDIO_INT_RXBUF_F:    Receive FIFO full interrupt
  *     @arg SDIO_INT_TXBUF_E:    Transmit FIFO empty interrupt
  *     @arg SDIO_INT_RXBUF_E:    Receive FIFO empty interrupt
  *     @arg SDIO_INT_TXBUF:      Data available in transmit FIFO interrupt
  *     @arg SDIO_INT_RXBUF:      Data available in receive FIFO interrupt
  *     @arg SDIO_INT_SDIOIF:     SD I/O interrupt received interrupt
  *     @arg SDIO_INT_ATACMPL:    CE-ATA command completion signal received for CMD61 interrupt
  * @retval The new state of SDIO_INT (SET or RESET).
  */
ITStatus SDIO_GetINTStatus(SDIO_Type * SDIOx, uint32_t SDIO_INT)
{
  ITStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_SDIO_GET_INT(SDIO_INT));

  if ((SDIOx->STS & SDIO_INT) != (uint32_t)RESET)
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
  * @param  SDIOx: where x can be 1 or 2 to select the SDIO peripheral.
  * @param  SDIO_INT: specifies the interrupt pending bit to clear.
  *   This parameter can be one or a combination of the following values:
  *     @arg SDIO_INT_CMDFAIL:    Command response received (CRC check failed) interrupt
  *     @arg SDIO_INT_DTFAIL:     Data block sent/received (CRC check failed) interrupt
  *     @arg SDIO_INT_CMDTIMEOUT: Command response timeout interrupt
  *     @arg SDIO_INT_DTTIMEOUT:  Data timeout interrupt
  *     @arg SDIO_INT_TXERRU:     Transmit FIFO underrun error interrupt
  *     @arg SDIO_INT_RXERRO:     Received FIFO overrun error interrupt
  *     @arg SDIO_INT_CMDRSPCMPL: Command response received (CRC check passed) interrupt
  *     @arg SDIO_INT_CMDCMPL:    Command sent (no response required) interrupt
  *     @arg SDIO_INT_DTCMPL:     Data end (data counter, SDIDCOUNT, is zero) interrupt
  *     @arg SDIO_INT_SBITERR:    Start bit not detected on all data signals in wide bus mode interrupt
  *     @arg SDIO_INT_SDIOIF:     SD I/O interrupt received interrupt
  *     @arg SDIO_INT_ATACMPL:    CE-ATA command completion signal received for CMD61
  * @retval None
  */
void SDIO_ClearINTPendingBit(SDIO_Type * SDIOx, uint32_t SDIO_INT)
{
  /* Check the parameters */
  assert_param(IS_SDIO_ALL_PERIPH(SDIOx));
  assert_param(IS_SDIO_CLEAR_INT(SDIO_INT));

  SDIOx->INTCLR = SDIO_INT;
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


