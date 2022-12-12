/********************************** (C) COPYRIGHT  *******************************
* File Name          : ch32f20x_SDIO.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/08/08
* Description        : This file provides all the SDIO firmware functions.
*******************************************************************************/
#include "ch32f20x_sdio.h"
#include "ch32f20x_rcc.h"


#define SDIO_OFFSET              (SDIO_BASE - PERIPH_BASE)

/* CLKCR register clear mask */
#define CLKCR_CLEAR_MASK         ((uint32_t)0xFFFF8100) 

/* SDIO PWRCTRL Mask */
#define PWR_PWRCTRL_MASK         ((uint32_t)0xFFFFFFFC)

/* SDIO DCTRL Clear Mask */
#define DCTRL_CLEAR_MASK         ((uint32_t)0xFFFFFF08)

/* CMD Register clear mask */
#define CMD_CLEAR_MASK           ((uint32_t)0xFFFFF800)

/* SDIO RESP Registers Address */
#define SDIO_RESP_ADDR           ((uint32_t)(SDIO_BASE + 0x14))

/*******************************************************************************
* Function Name  : SDIO_DeInit
* Description    : Deinitializes the SDIO peripheral registers to their default reset values.
* Input          : None
* Return         : None
*******************************************************************************/
void SDIO_DeInit(void)
{
  SDIO->POWER = 0x00000000;
  SDIO->CLKCR = 0x00000000;
  SDIO->ARG = 0x00000000;
  SDIO->CMD = 0x00000000;
  SDIO->DTIMER = 0x00000000;
  SDIO->DLEN = 0x00000000;
  SDIO->DCTRL = 0x00000000;
  SDIO->ICR = 0x00C007FF;
  SDIO->MASK = 0x00000000;
}

/*******************************************************************************
* Function Name  : SDIO_Init
* Description    : Initializes the SDIO peripheral according to the specified
*      parameters in the SDIO_InitStruct.
* Input          : SDIO_InitStruct : pointer to a SDIO_InitTypeDef structure
*      that contains the configuration information for the SDIO peripheral.
* Return         : None
*******************************************************************************/
void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct)
{
  uint32_t tmpreg = 0;
   
  tmpreg = SDIO->CLKCR;
  tmpreg &= CLKCR_CLEAR_MASK;
  tmpreg |= (SDIO_InitStruct->SDIO_ClockDiv  | SDIO_InitStruct->SDIO_ClockPowerSave |
             SDIO_InitStruct->SDIO_ClockBypass | SDIO_InitStruct->SDIO_BusWide |
             SDIO_InitStruct->SDIO_ClockEdge | SDIO_InitStruct->SDIO_HardwareFlowControl); 

  SDIO->CLKCR = tmpreg;
}

/*******************************************************************************
* Function Name  : SDIO_StructInit
* Description    : Fills each SDIO_InitStruct member with its default value.
* Input          : SDIO_InitStruct: pointer to an SDIO_InitTypeDef structure which
*                    will be initialized.
* Return         : None
*******************************************************************************/
void SDIO_StructInit(SDIO_InitTypeDef* SDIO_InitStruct)
{
  SDIO_InitStruct->SDIO_ClockDiv = 0x00;
  SDIO_InitStruct->SDIO_ClockEdge = SDIO_ClockEdge_Rising;
  SDIO_InitStruct->SDIO_ClockBypass = SDIO_ClockBypass_Disable;
  SDIO_InitStruct->SDIO_ClockPowerSave = SDIO_ClockPowerSave_Disable;
  SDIO_InitStruct->SDIO_BusWide = SDIO_BusWide_1b;
  SDIO_InitStruct->SDIO_HardwareFlowControl = SDIO_HardwareFlowControl_Disable;
}

/*******************************************************************************
* Function Name  : SDIO_ClockCmd
* Description    : Enables or disables the SDIO Clock.
* Input          : SDIO_InitStruct: pointer to an SDIO_InitTypeDef structure which
*                    will be initialized.
*                  NewState£ºENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void SDIO_ClockCmd(FunctionalState NewState)
{
  if(NewState) SDIO->CLKCR |= ((uint32_t)1<<8);
  else SDIO->CLKCR &= ~((uint32_t)1<<8);
}

/*******************************************************************************
* Function Name  : SDIO_SetPowerState
* Description    : Sets the power status of the controller.
* Input          : SDIO_PowerState: new state of the Power state.
*                    SDIO_PowerState_OFF
*                    SDIO_PowerState_ON
* Return         : None
*******************************************************************************/
void SDIO_SetPowerState(uint32_t SDIO_PowerState)
{
  
  SDIO->POWER &= PWR_PWRCTRL_MASK;
  SDIO->POWER |= SDIO_PowerState;
}

/*******************************************************************************
* Function Name  : SDIO_GetPowerState
* Description    : Gets the power status of the controller.
* Input          : None
* Return         :
*                  - 0x00: Power OFF
*                  - 0x02: Power UP
*                  - 0x03: Power ON
*******************************************************************************/
uint32_t SDIO_GetPowerState(void)
{
  return (SDIO->POWER & (~PWR_PWRCTRL_MASK));
}

/*******************************************************************************
* Function Name  : SDIO_ITConfig
* Description    : Enables or disables the SDIO interrupts.
* Input          : DIO_IT: specifies the SDIO interrupt sources to be enabled or disabled.
*                    SDIO_IT_CCRCFAIL
*                    SDIO_IT_DCRCFAIL
*                    SDIO_IT_CTIMEOUT
*                    SDIO_IT_DTIMEOUT
*                    SDIO_IT_TXUNDERR
*                    SDIO_IT_RXOVERR
*                    SDIO_IT_CMDREND
*                    SDIO_IT_CMDSENT
*                    SDIO_IT_DATAEND
*                    SDIO_IT_STBITERR
*                    SDIO_IT_DBCKEND
*                    SDIO_IT_CMDACT
*                    SDIO_IT_TXACT
*                    SDIO_IT_RXACT
*                    SDIO_IT_TXFIFOHE
*                    SDIO_IT_RXFIFOHF
*                    SDIO_IT_TXFIFOF
*                    SDIO_IT_RXFIFOF
*                    SDIO_IT_TXFIFOE
*                    SDIO_IT_RXFIFOE
*                    SDIO_IT_TXDAVL
*                    SDIO_IT_RXDAVL
*                    SDIO_IT_SDIOIT
*                    SDIO_IT_CEATAEND
*                  NewState:ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void SDIO_ITConfig(uint32_t SDIO_IT, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    SDIO->MASK |= SDIO_IT;
  }
  else
  {
    SDIO->MASK &= ~SDIO_IT;
  } 
}

/*******************************************************************************
* Function Name  : SDIO_DMACmd
* Description    : Enables or disables the SDIO DMA request.
* Input          : NewState:ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void SDIO_DMACmd(FunctionalState NewState)
{
  if(NewState) SDIO->DCTRL |= ((uint32_t)1<<3);
  else SDIO->DCTRL &= ~((uint32_t)1<<3);
}

/*******************************************************************************
* Function Name  : SDIO_SendCommand
* Description    : Initializes the SDIO Command according to the specified
*       parameters in the SDIO_CmdInitStruct and send the command.
* Input          : SDIO_CmdInitStruct : pointer to a SDIO_CmdInitTypeDef
*       structure that contains the configuration information for the SDIO command.
* Return         : None
*******************************************************************************/
void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct)
{
  uint32_t tmpreg = 0;

  SDIO->ARG = SDIO_CmdInitStruct->SDIO_Argument;
  
  tmpreg = SDIO->CMD;
  tmpreg &= CMD_CLEAR_MASK;
  tmpreg |= (uint32_t)SDIO_CmdInitStruct->SDIO_CmdIndex | SDIO_CmdInitStruct->SDIO_Response
           | SDIO_CmdInitStruct->SDIO_Wait | SDIO_CmdInitStruct->SDIO_CPSM;
  
  SDIO->CMD = tmpreg;
}

/*******************************************************************************
* Function Name  : SDIO_CmdStructInit
* Description    : Fills each SDIO_CmdInitStruct member with its default value.
* Input          : SDIO_CmdInitStruct: pointer to an SDIO_CmdInitTypeDef
*        structure which will be initialized.
* Return         : None
*******************************************************************************/
void SDIO_CmdStructInit(SDIO_CmdInitTypeDef* SDIO_CmdInitStruct)
{
  SDIO_CmdInitStruct->SDIO_Argument = 0x00;
  SDIO_CmdInitStruct->SDIO_CmdIndex = 0x00;
  SDIO_CmdInitStruct->SDIO_Response = SDIO_Response_No;
  SDIO_CmdInitStruct->SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStruct->SDIO_CPSM = SDIO_CPSM_Disable;
}

/*******************************************************************************
* Function Name  : SDIO_GetCommandResponse
* Description    : Returns command index of last command for which response received.
* Input          : None
* Return         : Returns the command index of the last command response received.
*******************************************************************************/
uint8_t SDIO_GetCommandResponse(void)
{
  return (uint8_t)(SDIO->RESPCMD);
}


/*******************************************************************************
* Function Name  : SDIO_GetResponse
* Description    : Returns response received from the card for the last command.
* Input          : SDIO_RESP: Specifies the SDIO response register.
*                    SDIO_RESP1: Response Register 1
*                    SDIO_RESP2: Response Register 2
*                    SDIO_RESP3: Response Register 3
*                    SDIO_RESP4: Response Register 4
* Return         : Returns the command index of the last command response received.
*******************************************************************************/
uint32_t SDIO_GetResponse(uint32_t SDIO_RESP)
{
  __IO uint32_t tmp = 0;

  tmp = SDIO_RESP_ADDR + SDIO_RESP;
  
  return (*(__IO uint32_t *) tmp); 
}

/*******************************************************************************
* Function Name  : SDIO_DataConfig
* Description    : Initializes the SDIO data path according to the specified
* Input          : SDIO_DataInitStruct : pointer to a SDIO_DataInitTypeDef structure that
*                    contains the configuration information for the SDIO command.
* Return         : None
*******************************************************************************/
void SDIO_DataConfig(SDIO_DataInitTypeDef* SDIO_DataInitStruct)
{
  uint32_t tmpreg = 0;

  SDIO->DTIMER = SDIO_DataInitStruct->SDIO_DataTimeOut;
  SDIO->DLEN = SDIO_DataInitStruct->SDIO_DataLength;
  tmpreg = SDIO->DCTRL;
  tmpreg &= DCTRL_CLEAR_MASK;
  tmpreg |= (uint32_t)SDIO_DataInitStruct->SDIO_DataBlockSize | SDIO_DataInitStruct->SDIO_TransferDir
           | SDIO_DataInitStruct->SDIO_TransferMode | SDIO_DataInitStruct->SDIO_DPSM;

  SDIO->DCTRL = tmpreg;
}

/*******************************************************************************
* Function Name  : SDIO_DataStructInit
* Description    : Fills each SDIO_DataInitStruct member with its default value.
* Input          : SDIO_DataInitStruct: pointer to an SDIO_DataInitTypeDef structure which
*                  will be initialized.
* Return         : None
*******************************************************************************/
void SDIO_DataStructInit(SDIO_DataInitTypeDef* SDIO_DataInitStruct)
{
  SDIO_DataInitStruct->SDIO_DataTimeOut = 0xFFFFFFFF;
  SDIO_DataInitStruct->SDIO_DataLength = 0x00;
  SDIO_DataInitStruct->SDIO_DataBlockSize = SDIO_DataBlockSize_1b;
  SDIO_DataInitStruct->SDIO_TransferDir = SDIO_TransferDir_ToCard;
  SDIO_DataInitStruct->SDIO_TransferMode = SDIO_TransferMode_Block;  
  SDIO_DataInitStruct->SDIO_DPSM = SDIO_DPSM_Disable;
}

/*******************************************************************************
* Function Name  : SDIO_GetDataCounter
* Description    : Returns number of remaining data bytes to be transferred.
* Input          : None
* Return         : Number of remaining data bytes to be transferred
*******************************************************************************/
uint32_t SDIO_GetDataCounter(void)
{ 
  return SDIO->DCOUNT;
}

/*******************************************************************************
* Function Name  : SDIO_ReadData
* Description    : Read one data word from Rx FIFO.
* Input          : None
* Return         : Data received
*******************************************************************************/
uint32_t SDIO_ReadData(void)
{ 
  return SDIO->FIFO;
}

/*******************************************************************************
* Function Name  : SDIO_WriteData
* Description    : Write one data word to Tx FIFO.
* Input          : Data: 32-bit data word to write.
* Return         : None
*******************************************************************************/
void SDIO_WriteData(uint32_t Data)
{ 
  SDIO->FIFO = Data;
}

/*******************************************************************************
* Function Name  : SDIO_GetFIFOCount
* Description    : Returns the number of words left to be written to or read from FIFO.
* Input          : None
* Return         : Remaining number of words.
*******************************************************************************/
uint32_t SDIO_GetFIFOCount(void)
{ 
  return SDIO->FIFOCNT;
}

/*******************************************************************************
* Function Name  : SDIO_StartSDIOReadWait
* Description    : Starts the SD I/O Read Wait operation.
* Input          : NewState£ºENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void SDIO_StartSDIOReadWait(FunctionalState NewState)
{ 
  if(NewState) SDIO->DCTRL |= ((uint32_t)1<<8);
  else SDIO->DCTRL &= ~((uint32_t)1<<8);
}

/*******************************************************************************
* Function Name  : SDIO_StopSDIOReadWait
* Description    : Stops the SD I/O Read Wait operation.
* Input          : NewState£ºENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void SDIO_StopSDIOReadWait(FunctionalState NewState)
{ 
  if(NewState) SDIO->DCTRL |= ((uint32_t)1<<9);
  else SDIO->DCTRL &= ~((uint32_t)1<<9);

}

/*******************************************************************************
* Function Name  : SDIO_SetSDIOReadWaitMode
* Description    : Sets one of the two options of inserting read wait interval.
* Input          : SDIO_ReadWaitMode: SD I/O Read Wait operation mode.
*                    SDIO_ReadWaitMode_CLK: Read Wait control by stopping SDIOCLK
*                    SDIO_ReadWaitMode_DATA2: Read Wait control using SDIO_DATA2
* Return         : None
*******************************************************************************/
void SDIO_SetSDIOReadWaitMode(uint32_t SDIO_ReadWaitMode)
{
  if(SDIO_ReadWaitMode) SDIO->DCTRL |= ((uint32_t)1<<10);
  else SDIO->DCTRL &= ~((uint32_t)1<<10);
}

/*******************************************************************************
* Function Name  : SDIO_SetSDIOOperation
* Description    : Enables or disables the SD I/O Mode Operation.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void SDIO_SetSDIOOperation(FunctionalState NewState)
{ 
  if(NewState) SDIO->DCTRL |= ((uint32_t)1<<11);
  else SDIO->DCTRL &= ~((uint32_t)1<<11);
}

/*******************************************************************************
* Function Name  : SDIO_SendSDIOSuspendCmd
* Description    : Enables or disables the SD I/O Mode suspend command sending.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void SDIO_SendSDIOSuspendCmd(FunctionalState NewState)
{ 
  if(NewState) SDIO->CMD |= ((uint32_t)1<<11);
  else SDIO->CMD &= ~((uint32_t)1<<11);
}

/*******************************************************************************
* Function Name  : SDIO_CommandCompletionCmd
* Description    : Enables or disables the command completion signal.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void SDIO_CommandCompletionCmd(FunctionalState NewState)
{ 
  if(NewState) SDIO->CMD |= ((uint32_t)1<<12);
  else SDIO->CMD &= ~((uint32_t)1<<12);
}

/*******************************************************************************
* Function Name  : SDIO_CEATAITCmd
* Description    : Enables or disables the CE-ATA interrupt.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void SDIO_CEATAITCmd(FunctionalState NewState)
{ 
  if(NewState) SDIO->CMD |= ((uint32_t)1<<13);
  else SDIO->CMD &= ~((uint32_t)1<<13);
}

/*******************************************************************************
* Function Name  : SDIO_SendCEATACmd
* Description    : Sends CE-ATA command (CMD61).
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void SDIO_SendCEATACmd(FunctionalState NewState)
{ 
  if(NewState) SDIO->CMD |= ((uint32_t)1<<14);
  else SDIO->CMD &= ~((uint32_t)1<<14);
}

/*******************************************************************************
* Function Name  : SDIO_GetFlagStatus
* Description    : Checks whether the specified SDIO flag is set or not.
* Input          : SDIO_FLAG: specifies the flag to check.
*                    SDIO_FLAG_CCRCFAIL: Command response received (CRC check failed)
*                    SDIO_FLAG_DCRCFAIL: Data block sent/received (CRC check failed)
*                    SDIO_FLAG_CTIMEOUT: Command response timeout
*                    SDIO_FLAG_DTIMEOUT: Data timeout
*                    SDIO_FLAG_TXUNDERR: Transmit FIFO underrun error
*                    SDIO_FLAG_RXOVERR:  Received FIFO overrun error
*                    SDIO_FLAG_CMDREND:  Command response received (CRC check passed)
*                    SDIO_FLAG_CMDSENT:  Command sent (no response required)
*                    SDIO_FLAG_DATAEND:  Data end (data counter, SDIDCOUNT, is zero)
*                    SDIO_FLAG_STBITERR: Start bit not detected on all data signals in wide
*                              bus mode.
*                    SDIO_FLAG_DBCKEND:  Data block sent/received (CRC check passed)
*                    SDIO_FLAG_CMDACT:   Command transfer in progress
*                    SDIO_FLAG_TXACT:    Data transmit in progress
*                    SDIO_FLAG_RXACT:    Data receive in progress
*                    SDIO_FLAG_TXFIFOHE: Transmit FIFO Half Empty
*                    SDIO_FLAG_RXFIFOHF: Receive FIFO Half Full
*                    SDIO_FLAG_TXFIFOF:  Transmit FIFO full
*                    SDIO_FLAG_RXFIFOF:  Receive FIFO full
*                    SDIO_FLAG_TXFIFOE:  Transmit FIFO empty
*                    SDIO_FLAG_RXFIFOE:  Receive FIFO empty
*                    SDIO_FLAG_TXDAVL:   Data available in transmit FIFO
*                    SDIO_FLAG_RXDAVL:   Data available in receive FIFO
*                    SDIO_FLAG_SDIOIT:   SD I/O interrupt received
*                    SDIO_FLAG_CEATAEND: CE-ATA command completion signal received for CMD61
* Return         : ITStatus£ºSET or RESET
*******************************************************************************/
FlagStatus SDIO_GetFlagStatus(uint32_t SDIO_FLAG)
{ 
  FlagStatus bitstatus = RESET;
  
  if ((SDIO->STA & SDIO_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}


/*******************************************************************************
* Function Name  : SDIO_ClearFlag
* Description    : Clears the SDIO's pending flags.
* Input          : SDIO_FLAG: specifies the flag to clear.
*                    SDIO_FLAG_CCRCFAIL: Command response received (CRC check failed)
*                    SDIO_FLAG_DCRCFAIL: Data block sent/received (CRC check failed)
*                    SDIO_FLAG_CTIMEOUT: Command response timeout
*                    SDIO_FLAG_DTIMEOUT: Data timeout
*                    SDIO_FLAG_TXUNDERR: Transmit FIFO underrun error
*                    SDIO_FLAG_RXOVERR:  Received FIFO overrun error
*                    SDIO_FLAG_CMDREND:  Command response received (CRC check passed)
*                    SDIO_FLAG_CMDSENT:  Command sent (no response required)
*                    SDIO_FLAG_DATAEND:  Data end (data counter, SDIDCOUNT, is zero)
*                    SDIO_FLAG_STBITERR: Start bit not detected on all data signals in wide
*                              bus mode
*                    SDIO_FLAG_DBCKEND:  Data block sent/received (CRC check passed)
*                    SDIO_FLAG_SDIOIT:   SD I/O interrupt received
*                    SDIO_FLAG_CEATAEND: CE-ATA command completion signal received for CMD61
* Return         : None
*******************************************************************************/
void SDIO_ClearFlag(uint32_t SDIO_FLAG)
{
  SDIO->ICR = SDIO_FLAG;
}

/*******************************************************************************
* Function Name  : SDIO_GetITStatus
* Description    : Checks whether the specified SDIO interrupt has occurred or not.
* Input          : SDIO_IT: specifies the SDIO interrupt source to check.
*                    SDIO_IT_CCRCFAIL: Command response received (CRC check failed) interrupt
*                    SDIO_IT_DCRCFAIL: Data block sent/received (CRC check failed) interrupt
*                    SDIO_IT_CTIMEOUT: Command response timeout interrupt
*                    SDIO_IT_DTIMEOUT: Data timeout interrupt
*                    SDIO_IT_TXUNDERR: Transmit FIFO underrun error interrupt
*                    SDIO_IT_RXOVERR:  Received FIFO overrun error interrupt
*                    SDIO_IT_CMDREND:  Command response received (CRC check passed) interrupt
*                    SDIO_IT_CMDSENT:  Command sent (no response required) interrupt
*                    SDIO_IT_DATAEND:  Data end (data counter, SDIDCOUNT, is zero) interrupt
*                    SDIO_IT_STBITERR: Start bit not detected on all data signals in wide
*                            bus mode interrupt
*                    SDIO_IT_DBCKEND:  Data block sent/received (CRC check passed) interrupt
*                    SDIO_IT_CMDACT:   Command transfer in progress interrupt
*                    SDIO_IT_TXACT:    Data transmit in progress interrupt
*                    SDIO_IT_RXACT:    Data receive in progress interrupt
*                    SDIO_IT_TXFIFOHE: Transmit FIFO Half Empty interrupt
*                    SDIO_IT_RXFIFOHF: Receive FIFO Half Full interrupt
*                    SDIO_IT_TXFIFOF:  Transmit FIFO full interrupt
*                    SDIO_IT_RXFIFOF:  Receive FIFO full interrupt
*                    SDIO_IT_TXFIFOE:  Transmit FIFO empty interrupt
*                    SDIO_IT_RXFIFOE:  Receive FIFO empty interrupt
*                    SDIO_IT_TXDAVL:   Data available in transmit FIFO interrupt
*                    SDIO_IT_RXDAVL:   Data available in receive FIFO interrupt
*                    SDIO_IT_SDIOIT:   SD I/O interrupt received interrupt
*                    SDIO_IT_CEATAEND: CE-ATA command completion signal received for CMD61 interrupt
* Return         : ITStatus£ºSET or RESET
*******************************************************************************/
ITStatus SDIO_GetITStatus(uint32_t SDIO_IT)
{ 
  ITStatus bitstatus = RESET;
  
  if ((SDIO->STA & SDIO_IT) != (uint32_t)RESET)  
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/*******************************************************************************
* Function Name  : SDIO_ClearITPendingBit
* Description    : Clears the SDIO's interrupt pending bits.
* Input          : SDIO_IT: specifies the interrupt pending bit to clear.
*                    SDIO_IT_CCRCFAIL: Command response received (CRC check failed) interrupt
*                    SDIO_IT_DCRCFAIL: Data block sent/received (CRC check failed) interrupt
*                    SDIO_IT_CTIMEOUT: Command response timeout interrupt
*                    SDIO_IT_DTIMEOUT: Data timeout interrupt
*                    SDIO_IT_TXUNDERR: Transmit FIFO underrun error interrupt
*                    SDIO_IT_RXOVERR:  Received FIFO overrun error interrupt
*                    SDIO_IT_CMDREND:  Command response received (CRC check passed) interrupt
*                    SDIO_IT_CMDSENT:  Command sent (no response required) interrupt
*                    SDIO_IT_DATAEND:  Data end (data counter, SDIDCOUNT, is zero) interrupt
*                    SDIO_IT_STBITERR: Start bit not detected on all data signals in wide
*                            bus mode interrupt
*                    SDIO_IT_SDIOIT:   SD I/O interrupt received interrupt
*                    SDIO_IT_CEATAEND: CE-ATA command completion signal received for CMD61
* Return         : None
*******************************************************************************/
void SDIO_ClearITPendingBit(uint32_t SDIO_IT)
{
  SDIO->ICR = SDIO_IT;
}
