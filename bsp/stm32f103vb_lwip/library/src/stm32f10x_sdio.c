/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_sdio.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all the SDIO firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_sdio.h"
#include "stm32f10x_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* ------------ SDIO registers bit address in the alias region ----------- */
#define SDIO_OFFSET                (SDIO_BASE - PERIPH_BASE)

/* --- CLKCR Register ---*/
/* Alias word address of CLKEN bit */
#define CLKCR_OFFSET              (SDIO_OFFSET + 0x04)
#define CLKEN_BitNumber           0x08
#define CLKCR_CLKEN_BB            (PERIPH_BB_BASE + (CLKCR_OFFSET * 32) + (CLKEN_BitNumber * 4))

/* --- CMD Register ---*/
/* Alias word address of SDIOSUSPEND bit */
#define CMD_OFFSET                (SDIO_OFFSET + 0x0C)
#define SDIOSUSPEND_BitNumber     0x0B
#define CMD_SDIOSUSPEND_BB        (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (SDIOSUSPEND_BitNumber * 4))

/* Alias word address of ENCMDCOMPL bit */
#define ENCMDCOMPL_BitNumber      0x0C
#define CMD_ENCMDCOMPL_BB         (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (ENCMDCOMPL_BitNumber * 4))

/* Alias word address of NIEN bit */
#define NIEN_BitNumber            0x0D
#define CMD_NIEN_BB               (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (NIEN_BitNumber * 4))

/* Alias word address of ATACMD bit */
#define ATACMD_BitNumber          0x0E
#define CMD_ATACMD_BB             (PERIPH_BB_BASE + (CMD_OFFSET * 32) + (ATACMD_BitNumber * 4))

/* --- DCTRL Register ---*/
/* Alias word address of DMAEN bit */
#define DCTRL_OFFSET              (SDIO_OFFSET + 0x2C)
#define DMAEN_BitNumber           0x03
#define DCTRL_DMAEN_BB            (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (DMAEN_BitNumber * 4))

/* Alias word address of RWSTART bit */
#define RWSTART_BitNumber         0x08
#define DCTRL_RWSTART_BB          (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (RWSTART_BitNumber * 4))

/* Alias word address of RWSTOP bit */
#define RWSTOP_BitNumber          0x09
#define DCTRL_RWSTOP_BB           (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (RWSTOP_BitNumber * 4))

/* Alias word address of RWMOD bit */
#define RWMOD_BitNumber           0x0A
#define DCTRL_RWMOD_BB            (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (RWMOD_BitNumber * 4))

/* Alias word address of SDIOEN bit */
#define SDIOEN_BitNumber          0x0B
#define DCTRL_SDIOEN_BB           (PERIPH_BB_BASE + (DCTRL_OFFSET * 32) + (SDIOEN_BitNumber * 4))


/* ---------------------- SDIO registers bit mask ------------------------ */
/* --- CLKCR Register ---*/
/* CLKCR register clear mask */
#define CLKCR_CLEAR_MASK         ((u32)0xFFFF8100) 

/* --- PWRCTRL Register ---*/
/* SDIO PWRCTRL Mask */
#define PWR_PWRCTRL_MASK         ((u32)0xFFFFFFFC)

/* --- DCTRL Register ---*/
/* SDIO DCTRL Clear Mask */
#define DCTRL_CLEAR_MASK         ((u32)0xFFFFFF08)

/* --- CMD Register ---*/
/* CMD Register clear mask */
#define CMD_CLEAR_MASK           ((u32)0xFFFFF800)

/* SDIO RESP Registers Address */
#define SDIO_RESP_ADDR           ((u32)(SDIO_BASE + 0x14))

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : SDIO_DeInit
* Description    : Deinitializes the SDIO peripheral registers to their default
*                  reset values.
* Input          : None
* Output         : None
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
*                  parameters in the SDIO_InitStruct.
* Input          : SDIO_InitStruct : pointer to a SDIO_InitTypeDef structure 
*                  that contains the configuration information for the SDIO 
*                  peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct)
{
  u32 tmpreg = 0;
    
  /* Check the parameters */
  assert_param(IS_SDIO_CLOCK_EDGE(SDIO_InitStruct->SDIO_ClockEdge));
  assert_param(IS_SDIO_CLOCK_BYPASS(SDIO_InitStruct->SDIO_ClockBypass));
  assert_param(IS_SDIO_CLOCK_POWER_SAVE(SDIO_InitStruct->SDIO_ClockPowerSave));
  assert_param(IS_SDIO_BUS_WIDE(SDIO_InitStruct->SDIO_BusWide));
  assert_param(IS_SDIO_HARDWARE_FLOW_CONTROL(SDIO_InitStruct->SDIO_HardwareFlowControl)); 
   
/*---------------------------- SDIO CLKCR Configuration ------------------------*/  
  /* Get the SDIO CLKCR value */
  tmpreg = SDIO->CLKCR;
  
  /* Clear CLKDIV, PWRSAV, BYPASS, WIDBUS, NEGEDGE, HWFC_EN bits */
  tmpreg &= CLKCR_CLEAR_MASK;
  
  /* Set CLKDIV bits according to SDIO_ClockDiv value */
  /* Set PWRSAV bit according to SDIO_ClockPowerSave value */
  /* Set BYPASS bit according to SDIO_ClockBypass value */
  /* Set WIDBUS bits according to SDIO_BusWide value */
  /* Set NEGEDGE bits according to SDIO_ClockEdge value */
  /* Set HWFC_EN bits according to SDIO_HardwareFlowControl value */
  tmpreg |= (SDIO_InitStruct->SDIO_ClockDiv  | SDIO_InitStruct->SDIO_ClockPowerSave |
             SDIO_InitStruct->SDIO_ClockBypass | SDIO_InitStruct->SDIO_BusWide |
             SDIO_InitStruct->SDIO_ClockEdge | SDIO_InitStruct->SDIO_HardwareFlowControl); 
  
  /* Write to SDIO CLKCR */
  SDIO->CLKCR = tmpreg;             
}

/*******************************************************************************
* Function Name  : SDIO_StructInit
* Description    : Fills each SDIO_InitStruct member with its default value.
* Input          : SDIO_InitStruct: pointer to an SDIO_InitTypeDef structure which 
*                  will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_StructInit(SDIO_InitTypeDef* SDIO_InitStruct)
{
  /* SDIO_InitStruct members default value */
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
* Input          : NewState: new state of the SDIO Clock.
*                  This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_ClockCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(vu32 *) CLKCR_CLKEN_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : SDIO_SetPowerState
* Description    : Sets the power status of the controller.
* Input          : SDIO_PowerState: new state of the Power state. 
*                  This parameter can be one of the following values:
*                   - SDIO_PowerState_OFF
*                   - SDIO_PowerState_ON
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_SetPowerState(u32 SDIO_PowerState)
{
  /* Check the parameters */
  assert_param(IS_SDIO_POWER_STATE(SDIO_PowerState));
  
  SDIO->POWER &= PWR_PWRCTRL_MASK;
  SDIO->POWER |= SDIO_PowerState;
}

/*******************************************************************************
* Function Name  : SDIO_GetPowerState
* Description    : Gets the power status of the controller.
* Input          : None
* Output         : None
* Return         : Power status of the controller. The returned value can
*                  be one of the following:
*                       - 0x00: Power OFF
*                       - 0x02: Power UP
*                       - 0x03: Power ON 
*******************************************************************************/
u32 SDIO_GetPowerState(void)
{
  return (SDIO->POWER & (~PWR_PWRCTRL_MASK));
}

/*******************************************************************************
* Function Name  : SDIO_ITConfig
* Description    : Enables or disables the SDIO interrupts.
* Input          : - SDIO_IT: specifies the SDIO interrupt sources to be 
*                    enabled or disabled.
*                    This parameter can be one or a combination of the following
*                    values:
*                      - SDIO_IT_CCRCFAIL: Command response received (CRC check
*                                          failed) interrupt    
*                      - SDIO_IT_DCRCFAIL: Data block sent/received (CRC check 
*                                          failed) interrupt    
*                      - SDIO_IT_CTIMEOUT: Command response timeout interrupt    
*                      - SDIO_IT_DTIMEOUT: Data timeout interrupt    
*                      - SDIO_IT_TXUNDERR: Transmit FIFO underrun error interrupt    
*                      - SDIO_IT_RXOVERR:  Received FIFO overrun error interrupt     
*                      - SDIO_IT_CMDREND:  Command response received (CRC check 
*                                          passed) interrupt     
*                      - SDIO_IT_CMDSENT:  Command sent (no response required) 
*                                          interrupt     
*                      - SDIO_IT_DATAEND:  Data end (data counter, SDIDCOUNT, is 
*                                          zero) interrupt     
*                      - SDIO_IT_STBITERR: Start bit not detected on all data 
*                                          signals in wide bus mode interrupt    
*                      - SDIO_IT_DBCKEND:  Data block sent/received (CRC check 
*                                          passed) interrupt    
*                      - SDIO_IT_CMDACT:   Command transfer in progress interrupt     
*                      - SDIO_IT_TXACT:    Data transmit in progress interrupt       
*                      - SDIO_IT_RXACT:    Data receive in progress interrupt      
*                      - SDIO_IT_TXFIFOHE: Transmit FIFO Half Empty interrupt    
*                      - SDIO_IT_RXFIFOHF: Receive FIFO Half Full interrupt   
*                      - SDIO_IT_TXFIFOF:  Transmit FIFO full interrupt     
*                      - SDIO_IT_RXFIFOF:  Receive FIFO full interrupt     
*                      - SDIO_IT_TXFIFOE:  Transmit FIFO empty interrupt      
*                      - SDIO_IT_RXFIFOE:  Receive FIFO empty interrupt     
*                      - SDIO_IT_TXDAVL:   Data available in transmit FIFO interrupt      
*                      - SDIO_IT_RXDAVL:   Data available in receive FIFO interrupt      
*                      - SDIO_IT_SDIOIT:   SD I/O interrupt received interrupt      
*                      - SDIO_IT_CEATAEND: CE-ATA command completion signal 
*                                          received for CMD61 interrupt
*                  - NewState: new state of the specified SDIO interrupts.
*                  This parameter can be: ENABLE or DISABLE.  
* Output         : None
* Return         : None 
*******************************************************************************/
void SDIO_ITConfig(u32 SDIO_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SDIO_IT(SDIO_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the SDIO interrupts */
    SDIO->MASK |= SDIO_IT;
  }
  else
  {
    /* Disable the SDIO interrupts */
    SDIO->MASK &= ~SDIO_IT;
  } 
}

/*******************************************************************************
* Function Name  : SDIO_DMACmd
* Description    : Enables or disables the SDIO DMA request.
* Input          : NewState: new state of the selected SDIO DMA request.
*                  This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_DMACmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(vu32 *) DCTRL_DMAEN_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : SDIO_SendCommand
* Description    : Initializes the SDIO Command according to the specified 
*                  parameters in the SDIO_CmdInitStruct and send the command.
* Input          : SDIO_CmdInitStruct : pointer to a SDIO_CmdInitTypeDef 
*                  structure that contains the configuration information 
*                  for the SDIO command.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct)
{
  u32 tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_SDIO_CMD_INDEX(SDIO_CmdInitStruct->SDIO_CmdIndex));
  assert_param(IS_SDIO_RESPONSE(SDIO_CmdInitStruct->SDIO_Response));
  assert_param(IS_SDIO_WAIT(SDIO_CmdInitStruct->SDIO_Wait));
  assert_param(IS_SDIO_CPSM(SDIO_CmdInitStruct->SDIO_CPSM));
  
/*---------------------------- SDIO ARG Configuration ------------------------*/
  /* Set the SDIO Argument value */
  SDIO->ARG = SDIO_CmdInitStruct->SDIO_Argument;
  
/*---------------------------- SDIO CMD Configuration ------------------------*/  
  /* Get the SDIO CMD value */
  tmpreg = SDIO->CMD;

  /* Clear CMDINDEX, WAITRESP, WAITINT, WAITPEND, CPSMEN bits */
  tmpreg &= CMD_CLEAR_MASK;
  /* Set CMDINDEX bits according to SDIO_CmdIndex value */
  /* Set WAITRESP bits according to SDIO_Response value */
  /* Set WAITINT and WAITPEND bits according to SDIO_Wait value */
  /* Set CPSMEN bits according to SDIO_CPSM value */
  tmpreg |= (u32)SDIO_CmdInitStruct->SDIO_CmdIndex | SDIO_CmdInitStruct->SDIO_Response
           | SDIO_CmdInitStruct->SDIO_Wait | SDIO_CmdInitStruct->SDIO_CPSM;
  
  /* Write to SDIO CMD */
  SDIO->CMD = tmpreg;
}

/*******************************************************************************
* Function Name  : SDIO_CmdStructInit
* Description    : Fills each SDIO_CmdInitStruct member with its default value.
* Input          : SDIO_CmdInitStruct: pointer to an SDIO_CmdInitTypeDef 
*                  structure which will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_CmdStructInit(SDIO_CmdInitTypeDef* SDIO_CmdInitStruct)
{
  /* SDIO_CmdInitStruct members default value */
  SDIO_CmdInitStruct->SDIO_Argument = 0x00;
  SDIO_CmdInitStruct->SDIO_CmdIndex = 0x00;
  SDIO_CmdInitStruct->SDIO_Response = SDIO_Response_No;
  SDIO_CmdInitStruct->SDIO_Wait = SDIO_Wait_No;
  SDIO_CmdInitStruct->SDIO_CPSM = SDIO_CPSM_Disable;
}

/*******************************************************************************
* Function Name  : SDIO_GetCommandResponse
* Description    : Returns command index of last command for which response 
*                  received.
* Input          : None
* Output         : None
* Return         : Returns the command index of the last command response received.
*******************************************************************************/
u8 SDIO_GetCommandResponse(void)
{
  return (u8)(SDIO->RESPCMD);
}

/*******************************************************************************
* Function Name  : SDIO_GetResponse
* Description    : Returns response received from the card for the last command.
* Input          : - SDIO_RESP: Specifies the SDIO response register. 
*                     This parameter can be one of the following values:
*                       - SDIO_RESP1: Response Register 1
*                       - SDIO_RESP2: Response Register 2
*                       - SDIO_RESP3: Response Register 3
*                       - SDIO_RESP4: Response Register 4                       
* Output         : None
* Return         : The Corresponding response register value.
*******************************************************************************/
u32 SDIO_GetResponse(u32 SDIO_RESP)
{
  /* Check the parameters */
  assert_param(IS_SDIO_RESP(SDIO_RESP));
  
  return (*(vu32 *)(SDIO_RESP_ADDR + SDIO_RESP)); 
}

/*******************************************************************************
* Function Name  : SDIO_DataConfig
* Description    : Initializes the SDIO data path according to the specified 
*                  parameters in the SDIO_DataInitStruct.
* Input          : SDIO_DataInitStruct : pointer to a SDIO_DataInitTypeDef 
*                  structure that contains the configuration information 
*                  for the SDIO command.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_DataConfig(SDIO_DataInitTypeDef* SDIO_DataInitStruct)
{
  u32 tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_SDIO_DATA_LENGTH(SDIO_DataInitStruct->SDIO_DataLength));
  assert_param(IS_SDIO_BLOCK_SIZE(SDIO_DataInitStruct->SDIO_DataBlockSize));
  assert_param(IS_SDIO_TRANSFER_DIR(SDIO_DataInitStruct->SDIO_TransferDir));
  assert_param(IS_SDIO_TRANSFER_MODE(SDIO_DataInitStruct->SDIO_TransferMode));
  assert_param(IS_SDIO_DPSM(SDIO_DataInitStruct->SDIO_DPSM));

/*---------------------------- SDIO DTIMER Configuration ---------------------*/
  /* Set the SDIO Data TimeOut value */
  SDIO->DTIMER = SDIO_DataInitStruct->SDIO_DataTimeOut;
    
/*---------------------------- SDIO DLEN Configuration -----------------------*/
  /* Set the SDIO DataLength value */
  SDIO->DLEN = SDIO_DataInitStruct->SDIO_DataLength;
  
/*---------------------------- SDIO DCTRL Configuration ----------------------*/  
  /* Get the SDIO DCTRL value */
  tmpreg = SDIO->DCTRL;

  /* Clear DEN, DTMODE, DTDIR and DBCKSIZE bits */
  tmpreg &= DCTRL_CLEAR_MASK;
  /* Set DEN bit according to SDIO_DPSM value */
  /* Set DTMODE bit according to SDIO_TransferMode value */
  /* Set DTDIR bit according to SDIO_TransferDir value */
  /* Set DBCKSIZE bits according to SDIO_DataBlockSize value */
  tmpreg |= (u32)SDIO_DataInitStruct->SDIO_DataBlockSize | SDIO_DataInitStruct->SDIO_TransferDir
           | SDIO_DataInitStruct->SDIO_TransferMode | SDIO_DataInitStruct->SDIO_DPSM;
  
  /* Write to SDIO DCTRL */
  SDIO->DCTRL = tmpreg;
}

/*******************************************************************************
* Function Name  : SDIO_DataStructInit
* Description    : Fills each SDIO_DataInitStruct member with its default value.
* Input          : SDIO_DataInitStruct: pointer to an SDIO_DataInitTypeDef 
*                  structure which will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_DataStructInit(SDIO_DataInitTypeDef* SDIO_DataInitStruct)
{
  /* SDIO_DataInitStruct members default value */
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
* Output         : None
* Return         : Number of remaining data bytes to be transferred
*******************************************************************************/
u32 SDIO_GetDataCounter(void)
{ 
  return SDIO->DCOUNT;
}

/*******************************************************************************
* Function Name  : SDIO_ReadData
* Description    : Read one data word from Rx FIFO.
* Input          : None
* Output         : None
* Return         : Data received
*******************************************************************************/
u32 SDIO_ReadData(void)
{ 
  return SDIO->FIFO;
}

/*******************************************************************************
* Function Name  : SDIO_WriteData
* Description    : Write one data word to Tx FIFO.
* Input          : Data: 32-bit data word to write.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_WriteData(u32 Data)
{ 
  SDIO->FIFO = Data;
}

/*******************************************************************************
* Function Name  : SDIO_GetFIFOCount
* Description    : Returns the number of words left to be written to or read
*                  from FIFO.	
* Input          : None
* Output         : None
* Return         : Remaining number of words.
*******************************************************************************/
u32 SDIO_GetFIFOCount(void)
{ 
  return SDIO->FIFOCNT;
}

/*******************************************************************************
* Function Name  : SDIO_StartSDIOReadWait
* Description    : Starts the SD I/O Read Wait operation.	
* Input          : NewState: new state of the Start SDIO Read Wait operation. 
*                  This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_StartSDIOReadWait(FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(vu32 *) DCTRL_RWSTART_BB = (u32) NewState;
}

/*******************************************************************************
* Function Name  : SDIO_StopSDIOReadWait
* Description    : Stops the SD I/O Read Wait operation.	
* Input          : NewState: new state of the Stop SDIO Read Wait operation. 
*                  This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_StopSDIOReadWait(FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(vu32 *) DCTRL_RWSTOP_BB = (u32) NewState;
}

/*******************************************************************************
* Function Name  : SDIO_SetSDIOReadWaitMode
* Description    : Sets one of the two options of inserting read wait interval.	
* Input          : SDIOReadWaitMode: SD I/O Read Wait operation mode.
*                  This parametre can be:
*                    - SDIO_ReadWaitMode_CLK: Read Wait control by stopping SDIOCLK
*                    - SDIO_ReadWaitMode_DATA2: Read Wait control using SDIO_DATA2
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_SetSDIOReadWaitMode(u32 SDIO_ReadWaitMode)
{
  /* Check the parameters */
  assert_param(IS_SDIO_READWAIT_MODE(SDIO_ReadWaitMode));
  
  *(vu32 *) DCTRL_RWMOD_BB = SDIO_ReadWaitMode;
}

/*******************************************************************************
* Function Name  : SDIO_SetSDIOOperation
* Description    : Enables or disables the SD I/O Mode Operation.	
* Input          : NewState: new state of SDIO specific operation. 
*                  This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_SetSDIOOperation(FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(vu32 *) DCTRL_SDIOEN_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : SDIO_SendSDIOSuspendCmd
* Description    : Enables or disables the SD I/O Mode suspend command sending.
* Input          : NewState: new state of the SD I/O Mode suspend command.
*                  This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_SendSDIOSuspendCmd(FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(vu32 *) CMD_SDIOSUSPEND_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : SDIO_CommandCompletionCmd
* Description    : Enables or disables the command completion signal.
* Input          : NewState: new state of command completion signal. 
*                  This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_CommandCompletionCmd(FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(vu32 *) CMD_ENCMDCOMPL_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : SDIO_CEATAITCmd
* Description    : Enables or disables the CE-ATA interrupt.
* Input          : NewState: new state of CE-ATA interrupt. 
*                  This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_CEATAITCmd(FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(vu32 *) CMD_NIEN_BB = (u32)((~((u32)NewState)) & ((u32)0x1));
}

/*******************************************************************************
* Function Name  : SDIO_SendCEATACmd
* Description    : Sends CE-ATA command (CMD61).
* Input          : NewState: new state of CE-ATA command. 
*                  This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_SendCEATACmd(FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(vu32 *) CMD_ATACMD_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : SDIO_GetFlagStatus
* Description    : Checks whether the specified SDIO flag is set or not.	
* Input          : SDIO_FLAG: specifies the flag to check. 
*                  This parameter can be one of the following values:
*                     - SDIO_FLAG_CCRCFAIL: Command response received (CRC check
*                                           failed)    
*                     - SDIO_FLAG_DCRCFAIL: Data block sent/received (CRC check 
*                                           failed)    
*                     - SDIO_FLAG_CTIMEOUT: Command response timeout    
*                     - SDIO_FLAG_DTIMEOUT: Data timeou   
*                     - SDIO_FLAG_TXUNDERR: Transmit FIFO underrun error   
*                     - SDIO_FLAG_RXOVERR:  Received FIFO overrun error    
*                     - SDIO_FLAG_CMDREND:  Command response received (CRC check 
*                                           passed)    
*                     - SDIO_FLAG_CMDSENT:  Command sent (no response required)    
*                     - SDIO_FLAG_DATAEND:  Data end (data counter, SDIDCOUNT, is
*                                           zero)    
*                     - SDIO_FLAG_STBITERR: Start bit not detected on all data 
*                                           signals in wide bus mode   
*                     - SDIO_FLAG_DBCKEND:  Data block sent/received (CRC check 
*                                           passed)    
*                     - SDIO_FLAG_CMDACT:   Command transfer in progress     
*                     - SDIO_FLAG_TXACT:    Data transmit in progress      
*                     - SDIO_FLAG_RXACT:    Data receive in progress      
*                     - SDIO_FLAG_TXFIFOHE: Transmit FIFO Half Empty   
*                     - SDIO_FLAG_RXFIFOHF: Receive FIFO Half Full   
*                     - SDIO_FLAG_TXFIFOF:  Transmit FIFO full    
*                     - SDIO_FLAG_RXFIFOF:  Receive FIFO full     
*                     - SDIO_FLAG_TXFIFOE:  Transmit FIFO empty    
*                     - SDIO_FLAG_RXFIFOE:  Receive FIFO empty    
*                     - SDIO_FLAG_TXDAVL:   Data available in transmit FIFO     
*                     - SDIO_FLAG_RXDAVL:   Data available in receive FIFO     
*                     - SDIO_FLAG_SDIOIT:   SD I/O interrupt received     
*                     - SDIO_FLAG_CEATAEND: CE-ATA command completion signal 
*                                           received for CMD61    
* Output         : None
* Return         : The new state of SDIO_FLAG (SET or RESET).
*******************************************************************************/
FlagStatus SDIO_GetFlagStatus(u32 SDIO_FLAG)
{ 
  FlagStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_SDIO_FLAG(SDIO_FLAG));
  
  if ((SDIO->STA & SDIO_FLAG) != (u32)RESET)
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
*                  This parameter can be one or a combination of the following
*                  values:
*                     - SDIO_FLAG_CCRCFAIL: Command response received (CRC check
*                                           failed)    
*                     - SDIO_FLAG_DCRCFAIL: Data block sent/received (CRC check 
*                                           failed)    
*                     - SDIO_FLAG_CTIMEOUT: Command response timeout    
*                     - SDIO_FLAG_DTIMEOUT: Data timeou   
*                     - SDIO_FLAG_TXUNDERR: Transmit FIFO underrun error   
*                     - SDIO_FLAG_RXOVERR:  Received FIFO overrun error    
*                     - SDIO_FLAG_CMDREND:  Command response received (CRC check 
*                                           passed)    
*                     - SDIO_FLAG_CMDSENT:  Command sent (no response required)    
*                     - SDIO_FLAG_DATAEND:  Data end (data counter, SDIDCOUNT, is
*                                           zero)    
*                     - SDIO_FLAG_STBITERR: Start bit not detected on all data 
*                                           signals in wide bus mode   
*                     - SDIO_FLAG_DBCKEND:  Data block sent/received (CRC check 
*                                           passed)         
*                     - SDIO_FLAG_SDIOIT:   SD I/O interrupt received     
*                     - SDIO_FLAG_CEATAEND: CE-ATA command completion signal 
*                                           received for CMD61    
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_ClearFlag(u32 SDIO_FLAG)
{ 
  /* Check the parameters */
  assert_param(IS_SDIO_CLEAR_FLAG(SDIO_FLAG));
   
  SDIO->ICR = SDIO_FLAG;
}

/*******************************************************************************
* Function Name  : SDIO_GetITStatus
* Description    : Checks whether the specified SDIO interrupt has occurred or not.	
* Input          : SDIO_IT: specifies the SDIO interrupt source to check. 
*                  This parameter can be one of the following values:
*                      - SDIO_IT_CCRCFAIL: Command response received (CRC check
*                                          failed) interrupt    
*                      - SDIO_IT_DCRCFAIL: Data block sent/received (CRC check 
*                                          failed) interrupt    
*                      - SDIO_IT_CTIMEOUT: Command response timeout interrupt    
*                      - SDIO_IT_DTIMEOUT: Data timeout interrupt    
*                      - SDIO_IT_TXUNDERR: Transmit FIFO underrun error interrupt    
*                      - SDIO_IT_RXOVERR:  Received FIFO overrun error interrupt     
*                      - SDIO_IT_CMDREND:  Command response received (CRC check 
*                                          passed) interrupt     
*                      - SDIO_IT_CMDSENT:  Command sent (no response required) 
*                                          interrupt     
*                      - SDIO_IT_DATAEND:  Data end (data counter, SDIDCOUNT, is 
*                                          zero) interrupt     
*                      - SDIO_IT_STBITERR: Start bit not detected on all data 
*                                          signals in wide bus mode interrupt    
*                      - SDIO_IT_DBCKEND:  Data block sent/received (CRC check 
*                                          passed) interrupt    
*                      - SDIO_IT_CMDACT:   Command transfer in progress interrupt     
*                      - SDIO_IT_TXACT:    Data transmit in progress interrupt       
*                      - SDIO_IT_RXACT:    Data receive in progress interrupt      
*                      - SDIO_IT_TXFIFOHE: Transmit FIFO Half Empty interrupt    
*                      - SDIO_IT_RXFIFOHF: Receive FIFO Half Full interrupt   
*                      - SDIO_IT_TXFIFOF:  Transmit FIFO full interrupt     
*                      - SDIO_IT_RXFIFOF:  Receive FIFO full interrupt     
*                      - SDIO_IT_TXFIFOE:  Transmit FIFO empty interrupt      
*                      - SDIO_IT_RXFIFOE:  Receive FIFO empty interrupt     
*                      - SDIO_IT_TXDAVL:   Data available in transmit FIFO interrupt      
*                      - SDIO_IT_RXDAVL:   Data available in receive FIFO interrupt      
*                      - SDIO_IT_SDIOIT:   SD I/O interrupt received interrupt      
*                      - SDIO_IT_CEATAEND: CE-ATA command completion signal 
*                                          received for CMD61 interrupt
* Output         : None
* Return         : The new state of SDIO_IT (SET or RESET).
*******************************************************************************/
ITStatus SDIO_GetITStatus(u32 SDIO_IT)
{ 
  ITStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_SDIO_GET_IT(SDIO_IT));

  if ((SDIO->STA & SDIO_IT) != (u32)RESET)  
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
* Description    : Clears the SDIO’s interrupt pending bits.	
* Input          : SDIO_IT: specifies the interrupt pending bit to clear. 
*                   This parameter can be one or a combination of the following
*                   values:
*                      - SDIO_IT_CCRCFAIL: Command response received (CRC check
*                                          failed) interrupt    
*                      - SDIO_IT_DCRCFAIL: Data block sent/received (CRC check 
*                                          failed) interrupt    
*                      - SDIO_IT_CTIMEOUT: Command response timeout interrupt    
*                      - SDIO_IT_DTIMEOUT: Data timeout interrupt    
*                      - SDIO_IT_TXUNDERR: Transmit FIFO underrun error interrupt    
*                      - SDIO_IT_RXOVERR:  Received FIFO overrun error interrupt     
*                      - SDIO_IT_CMDREND:  Command response received (CRC check 
*                                          passed) interrupt     
*                      - SDIO_IT_CMDSENT:  Command sent (no response required) 
*                                          interrupt     
*                      - SDIO_IT_DATAEND:  Data end (data counter, SDIDCOUNT, is 
*                                          zero) interrupt     
*                      - SDIO_IT_STBITERR: Start bit not detected on all data 
*                                          signals in wide bus mode interrupt          
*                      - SDIO_IT_SDIOIT:   SD I/O interrupt received interrupt      
*                      - SDIO_IT_CEATAEND: CE-ATA command completion signal 
*                                          received for CMD61 
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_ClearITPendingBit(u32 SDIO_IT)
{ 
  /* Check the parameters */
  assert_param(IS_SDIO_CLEAR_IT(SDIO_IT));
   
  SDIO->ICR = SDIO_IT;
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
