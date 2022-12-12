////////////////////////////////////////////////////////////////////////////////
/// @file     hal_sdio.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE SDIO FIRMWARE FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#define _HAL_SDIO_C_
#include "reg_sdio.h"
#include "hal_sdio.h"
#include "hal_rcc.h"



////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup SDIO_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup SDIO_Exported_Functions
/// @{
////////////////////////////////////////////////////////////////////////////////
/// @brief  Deinitializes the SDIO peripheral registers to their default reset
///         values.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SDIO_DeInit(void)
{
    RCC_AHBPeriphResetCmd(RCC_AHBRSTR_SDIO, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBRSTR_SDIO, DISABLE);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Fills each SDIO_InitStruct member with its default value.
/// @param  SDIO_InitStruct: pointer to an SDIO_InitTypeDef structure which
///         will be initialized.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SDIO_StructInit(SDIO_InitTypeDef* SDIO_InitStruct)
{
    // SDIO_InitStruct members default value
    SDIO_InitStruct->SDIO_MDEN = 0;
    SDIO_InitStruct->SDIO_DATWT = 0;
    SDIO_InitStruct->SDIO_SelPTSM = 0;
    SDIO_InitStruct->SDIO_CLKSP = 0;
    SDIO_InitStruct->SDIO_OUTM = 0;
    SDIO_InitStruct->SDIO_SelSM = 0;
    SDIO_InitStruct->SDIO_OPMSel = 0;
}


///
/// @brief  Fills each SDIO_DataInitStruct member with its default value.
/// @param  SDIO_DataInitStruct: pointer to an SDIO_DataInitTypeDef structure which
///         will be initialized.
/// @retval None
///
void SDIO_DataStructInit(SDIO_DataInitTypeDef* SDIO_DataInitStruct)
{
    /* SDIO_DataInitStruct members default value */
    SDIO_DataInitStruct->SDIO_DataTimeOut = 0xFFFFFFFF;
    SDIO_DataInitStruct->SDIO_DataLength = 0x00;
    SDIO_DataInitStruct->SDIO_DataBlockSize = SDIO_DataBlockSize_1b;
    SDIO_DataInitStruct->SDIO_TransferDir = SDIO_TransferDir_ToCard;
//    SDIO_DataInitStruct->SDIO_TransferMode = SDIO_TransferMode_Block;
//    SDIO_DataInitStruct->SDIO_DPSM = SDIO_DPSM_Disable;
}

///
/// @brief  Initializes the SDIO data path according to the specified
///   parameters in the SDIO_DataInitStruct.
/// @param  SDIO_DataInitStruct : pointer to a SDIO_DataInitTypeDef structure that
///   contains the configuration information for the SDIO command.
/// @retval None
///
//void SDIO_DataConfig(SDIO_DataInitTypeDef* SDIO_DataInitStruct)
//{
//    u32 tmpreg = 0;

//    /*---------------------------- SDIO DTIMER Configuration ---------------------*/
//    /* Set the SDIO Data TimeOut value */
//    SDIO->MMC_TIMEOUTCNT = SDIO_DataInitStruct->SDIO_DataTimeOut;

//    /*---------------------------- SDIO DLEN Configuration -----------------------*/
//    /* Set the SDIO DataLength value */
//    SDIO->MMC_BYTECNTL = SDIO_DataInitStruct->SDIO_DataLength;

//    /*---------------------------- SDIO DCTRL Configuration ----------------------*/
//    /* Get the SDIO DCTRL value */
//    tmpreg = SDIO->DCTRL;
//    /* Clear DEN, DTMODE, DTDIR and DBCKSIZE bits */
//    tmpreg &= DCTRL_CLEAR_MASK;
//    /* Set DEN bit according to SDIO_DPSM value */
//    /* Set DTMODE bit according to SDIO_TransferMode value */
//    /* Set DTDIR bit according to SDIO_TransferDir value */
//    /* Set DBCKSIZE bits according to SDIO_DataBlockSize value */
//    tmpreg |= (u32)SDIO_DataInitStruct->SDIO_DataBlockSize | SDIO_DataInitStruct->SDIO_TransferDir;//
//              //| SDIO_DataInitStruct->SDIO_TransferMode | SDIO_DataInitStruct->SDIO_DPSM;

//    /* Write to SDIO DCTRL */
//    SDIO->DCTRL = tmpreg;
//}
////////////////////////////////////////////////////////////////////////////////
/// @brief  The frequency division factor is configured to generate the SDIO clock.
/// @param  value : 1MHz = Fhclk/((mmc_cardsel[5 : 0] + 1) × 2)
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SDIO_ClockSet(u32 value)
{
//    SDIO->MMC_CARDSEL &= ~SDIO_MMC_CARDSEL_MASK;
    SDIO->MMC_CARDSEL = (SDIO_MMC_CARDSEL_CTREN | SDIO_MMC_CARDSEL_ENPCLK | (value & 0x3F));
//    SDIO->MMC_CARDSEL = 0xC0+0x2F;//0xdf;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes the SDIO peripheral according to the specified
///         parameters in the SDIO_InitStruct.
/// @param  SDIO_InitStruct : pointer to a SDIO_InitTypeDef structure
///         that contains the configuration information for the SDIO peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct)
{
    SDIO->MMC_CTRL &= 0x700;
    SDIO->MMC_CTRL |= (SDIO_InitStruct->SDIO_OPMSel | SDIO_InitStruct->SDIO_SelSM |
                       SDIO_InitStruct->SDIO_OUTM | SDIO_InitStruct->SDIO_CLKSP |
                       SDIO_InitStruct->SDIO_SelPTSM | SDIO_InitStruct->SDIO_DATWT |
                       SDIO_InitStruct->SDIO_MDEN);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the SDIO interrupts.
/// @param  SDIO_IT: specifies the SDIO interrupt sources to be enabled or disabled.
///         state  : new state of the specified SDIO interrupts.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SDIO_ITConfig(u32 SDIO_IT, FunctionalState state)
{
    (state) ?  (SDIO->MMC_INT_MASK |= SDIO_IT) : (SDIO->MMC_INT_MASK &= ~SDIO_IT);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the SDIO CRC.
/// @param  SDIO_CRC: specifies the SDIO CRC sources to be enabled or disabled.
///         state   : new state of the specified SDIO CRC.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SDIO_CRCConfig(u32 SDIO_CRC, FunctionalState state)
{
    (state) ?  (SDIO->MMC_CRCCTL |= SDIO_CRC) : (SDIO->MMC_CRCCTL &= ~SDIO_CRC);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Port transfer speed mode.
/// @param  clkdiv : High/low speed.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SDIO_Clock_Set(u8 clkdiv)
{
    SDIO->MMC_CTRL &= ~SDIO_MMC_CTRL_SelPTSM;
    (clkdiv) ? (SDIO->MMC_CTRL |= SDIO_MMC_CTRL_SelPTSM) : (SDIO->MMC_CTRL &= ~SDIO_MMC_CTRL_SelPTSM);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Turn off the SDIO switch.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
SD_Error SD_PowerOFF(void)
{
    SDIO->MMC_CARDSEL &= ~(SDIO_MMC_CARDSEL_ENPCLK | SDIO_MMC_CARDSEL_CTREN);
    return SD_OK;
}
///
/// @brief  Fills each SDIO_CmdInitStruct member with its default value.
/// @param  SDIO_CmdInitStruct: pointer to an SDIO_CmdInitTypeDef
///         structure which will be initialized.
/// @retval None
///
void SDIO_CmdStructInit(SDIO_CmdInitTypeDef* SDIO_CmdInitStruct)
{
    /* SDIO_CmdInitStruct members default value */
    SDIO_CmdInitStruct->SDIO_Argument = 0x00;
    SDIO_CmdInitStruct->SDIO_CmdIndex = 0x00;
    SDIO_CmdInitStruct->SDIO_Response = SDIO_Response_No;
    SDIO_CmdInitStruct->SDIO_Wait = SDIO_Wait_No;
//    SDIO_CmdInitStruct->SDIO_CPSM = SDIO_CPSM_Disable;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  SDIO sends command functions.
/// @param  cmdindex : Type the command.
///         waitrsp  : Expected correspondence.
///         arg      : parameter.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SDIO_Send_Cmd(u8 cmdindex, u8 waitrsp, u32 arg)
{
    SDIO->CMD_BUF0 = (arg >> 0) & 0xFF;
    SDIO->CMD_BUF1 = (arg >> 8) & 0xFF;
    SDIO->CMD_BUF2 = (arg >> 16) & 0xFF;
    SDIO->CMD_BUF3 = (arg >> 24) & 0xFF;
    SDIO->CMD_BUF4 = 0x40 | cmdindex;
    SDIO->CLR_MMC_INT |= 0;
    SDIO->MMC_IO = SDIO_MMC_IO_AUTOTR;
    while(1) {
        if(SDIO->CLR_MMC_INT & SDIO_CLR_MMC_INT_CMDDMC) {
            SDIO->CLR_MMC_INT |= SDIO_CLR_MMC_INT_CMDDMC;
            break;
        }
    }
    if(waitrsp == SDIO_Response_Short) {
        SDIO->MMC_IO =  SDIO_MMC_IO_AUTOCLKG | \
                        SDIO_MMC_IO_AUTOTR | \
                        SDIO_MMC_IO_RESPCMDSEL;
    }
    else if(waitrsp == SDIO_Response_Long) {
        SDIO->MMC_IO =  SDIO_MMC_IO_AUTOCLKG | \
                        SDIO_MMC_IO_AUTOTR | \
                        SDIO_MMC_IO_RESPCMDSEL | \
                        SDIO_MMC_IO_CID_CSDRD;
    }
    else {
    }
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Check the execution status of CMD0.
/// @param  None.
/// @retval card error code.
////////////////////////////////////////////////////////////////////////////////
SD_Error CmdError(void)
{
    SD_Error errorstatus = SD_OK;
    u32 timeout = SDIO_CMD0TIMEOUT;
    while (timeout--) {
        if(((SDIO->MMC_IO & SDIO_MMC_IO_RESPCMDSEL) == 0) && ((SDIO->MMC_IO & SDIO_MMC_IO_AUTOTR) == 0))
            break;
    }
    if (timeout == 0)
        return SD_CMD_RSP_TIMEOUT;
    SDIO->CLR_MMC_INT = SDIO_CLR_MMC_INT_MASK;
    return errorstatus;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Check the error status of the R1 response.
/// @param  cmd : Current command.
/// @retval card error code.
////////////////////////////////////////////////////////////////////////////////
SD_Error CmdResp1Error(u8 cmd)
{
    u32 status;
    u32 response;
    while(1) {
        status = SDIO->CLR_MMC_INT ;
        if(status & (SDIO_CLR_MMC_INT_CRCEMC | SDIO_CLR_MMC_INT_CRNTMC | SDIO_CLR_MMC_INT_CMDDMC))
            break;
    }
    if(status & SDIO_CLR_MMC_INT_CRNTMC) {
        SDIO->CLR_MMC_INT = SDIO_CLR_MMC_INT_CRNTMC;
        return SD_CMD_RSP_TIMEOUT;
    }
    if(status & (SDIO_CLR_MMC_INT_CRCEMC)) {
        SDIO->CLR_MMC_INT = SDIO_CLR_MMC_INT_CRCEMC;
        return SD_CMD_CRC_FAIL;
    }
    SDIO->CLR_MMC_INT = SDIO_CLR_MMC_INT_MASK;

    if((SDIO->CMD_BUF4 & 0x3F) != cmd) {
        return SD_ILLEGAL_CMD;
    }
    response = SDIO->CMD_BUF3 << 24  | SDIO->CMD_BUF2 << 16  | SDIO->CMD_BUF1 << 8  | SDIO->CMD_BUF0;
    return (SD_Error)(response & SD_OCR_ERRORBITS);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Check the execution status of CMD2.
/// @param  None.
/// @retval card error code.
////////////////////////////////////////////////////////////////////////////////
SD_Error CmdResp2Error(void)
{
    SD_Error errorstatus = SD_OK;
    u32 status;
    u32 timeout = SDIO_CMD0TIMEOUT;
    while(timeout--) {
        status = SDIO->CLR_MMC_INT ;
        if(status & (SDIO_CLR_MMC_INT_CRCEMC | SDIO_CLR_MMC_INT_CRNTMC | SDIO_CLR_MMC_INT_CMDDMC))
            break;
    }
    if((timeout == 0) || (status & SDIO_CLR_MMC_INT_CRNTMC)) {
        errorstatus = SD_CMD_RSP_TIMEOUT;
        SDIO->CLR_MMC_INT = SDIO_CLR_MMC_INT_CRNTMC;
        return errorstatus;
    }
    if(status & SDIO_CLR_MMC_INT_CRCEMC) {
        errorstatus = SD_CMD_CRC_FAIL;
        SDIO->CLR_MMC_INT = SDIO_CLR_MMC_INT_CRCEMC;
    }
    SDIO->CLR_MMC_INT = SDIO_CLR_MMC_INT_MASK;
    return errorstatus;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Check the execution status of CMD3.
/// @param  None.
/// @retval card error code.
////////////////////////////////////////////////////////////////////////////////
SD_Error CmdResp3Error(void)
{
    u32 status;
    while(1) {
        status = SDIO->CLR_MMC_INT ;
        if(status & (SDIO_CLR_MMC_INT_CRCEMC | SDIO_CLR_MMC_INT_CRNTMC | SDIO_CLR_MMC_INT_CMDDMC))
            break;
    }
    if(status & SDIO_CLR_MMC_INT_CRNTMC) {
        SDIO->CLR_MMC_INT = SDIO_CLR_MMC_INT_CRNTMC;
        return SD_CMD_RSP_TIMEOUT;
    }
    SDIO->CLR_MMC_INT = SDIO_CLR_MMC_INT_MASK;
    return SD_OK;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Check the execution status of CMD6.
/// @param  None.
/// @retval card error code.
////////////////////////////////////////////////////////////////////////////////
SD_Error CmdResp6Error(u8 cmd, u16* prca)
{
    SD_Error errorstatus = SD_OK;
    u32 status;
    u32 rspr1;
    while(1) {
        status = SDIO->CLR_MMC_INT ;
        if(status & (SDIO_CLR_MMC_INT_CRCEMC | SDIO_CLR_MMC_INT_CRNTMC | SDIO_CLR_MMC_INT_CMDDMC))
            break;
    }
    if(status & SDIO_CLR_MMC_INT_CRNTMC) {
        SDIO->CLR_MMC_INT = SDIO_CLR_MMC_INT_CRNTMC;
        return SD_CMD_RSP_TIMEOUT;
    }
    if(status & SDIO_CLR_MMC_INT_CRCEMC) {
        SDIO->CLR_MMC_INT = SDIO_CLR_MMC_INT_CRCEMC;
        return SD_CMD_CRC_FAIL;
    }
    if((SDIO->CMD_BUF4 & 0x3F) != cmd) {
        return SD_ILLEGAL_CMD;
    }
    SDIO->CLR_MMC_INT = SDIO_CLR_MMC_INT_MASK;
    rspr1 = SDIO->CMD_BUF3 << 24  | SDIO->CMD_BUF2 << 16  | SDIO->CMD_BUF1 << 8  | SDIO->CMD_BUF0;
    if(SD_ALLZERO == (rspr1 & (SD_R6_GENERAL_UNKNOWN_ERROR | SD_R6_ILLEGAL_CMD | SD_R6_COM_CRC_FAILED))) {
        *prca = (u16)(rspr1 >> 16);
        return errorstatus;
    }
    if(rspr1 & SD_R6_GENERAL_UNKNOWN_ERROR) {
        return SD_GENERAL_UNKNOWN_ERROR;
    }
    if(rspr1 & SD_R6_ILLEGAL_CMD) {
        return SD_ILLEGAL_CMD;
    }
    if(rspr1 & SD_R6_COM_CRC_FAILED) {
        return SD_COM_CRC_FAILED;
    }
    return errorstatus;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Check the execution status of CMD7.
/// @param  None.
/// @retval card error code.
////////////////////////////////////////////////////////////////////////////////
SD_Error CmdResp7Error(void)
{
    SD_Error errorstatus = SD_OK;
    u32 status;
    u32 timeout = SDIO_CMD0TIMEOUT;
    while(timeout--) {
        status = SDIO->CLR_MMC_INT ;
        if(status & (SDIO_CLR_MMC_INT_CRCEMC | SDIO_CLR_MMC_INT_CRNTMC | SDIO_CLR_MMC_INT_CMDDMC))
            break;
    }
    if((timeout == 0) || (status & SDIO_CLR_MMC_INT_CRNTMC)) { //timeout
        errorstatus = SD_CMD_RSP_TIMEOUT;
        SDIO->CLR_MMC_INT = SDIO_CLR_MMC_INT_CRNTMC;
        return errorstatus;
    }
    if(status & SDIO_CLR_MMC_INT_CMDDMC) {
        errorstatus = SD_OK;
        SDIO->CLR_MMC_INT = SDIO_CLR_MMC_INT_CMDDMC;
    }
    return errorstatus;
}


////////////////////////////////////////////////////////////////////////////////
/// @brief  Write data direction block size configuration.
/// @param  datatimeout : maximum latency.
///         datalen     : data len
///         blksize     : block count.
///         dir         :  direction
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SDIO_Send_Data_Cfg(u32 datatimeout, u32 datalen, u8 blksize, u8 dir)
{
    u32 tmpreg, tmpreg1, tmpreg2 = 0;
    tmpreg = SDIO->MMC_IO_MBCTL;
    tmpreg1 = SDIO->MMC_IO;
    tmpreg &= ~(SDIO_MMC_IO_MBCTL_BTSSel | SDIO_MMC_IO_MBCTL_SPMBDTR | SDIO_MMC_IO_MBCTL_SMBDTD);
    if (datatimeout < 100) {
        SDIO->MMC_TIMEOUTCNT = datatimeout;
    }
    else if (datatimeout < 10000) {
        SDIO->MMC_TIMEOUTCNT = datatimeout / 100;
        tmpreg |= SDIO_MMC_IO_MBCTL_BTSSel;
    }
    else if (datatimeout < 1000000) {
        SDIO->MMC_TIMEOUTCNT = datatimeout / 10000;
        tmpreg |= SDIO_MMC_IO_MBCTL_BTSSel_2;
    }
    else {
        SDIO->MMC_TIMEOUTCNT = datatimeout / 1000000;
        tmpreg |= SDIO_MMC_IO_MBCTL_BTSSel;
    }
    SDIO->MMC_BYTECNTL = datalen & 0x1FFFFFF; ;
    SDIO->MMC_BLOCKCNT = blksize;
    if (dir == 0) {
        tmpreg |= SDIO_MMC_IO_MBCTL_SMBDTD;
        tmpreg1 |= SDIO_MMC_IO_TRANSFDIR;
        tmpreg2 |= SDIO_BUF_CTLL_SBAD;
    }
    else {
        tmpreg &= ~(SDIO_MMC_IO_MBCTL_SMBDTD);
        tmpreg1 &= ~(SDIO_MMC_IO_TRANSFDIR);
        tmpreg2 &= ~(SDIO_BUF_CTLL_SBAD);
    }
    SDIO->MMC_IO_MBCTL = tmpreg;
    SDIO->MMC_IO = tmpreg1;
    SDIO->BUF_CTL = tmpreg2;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the SDIO's Flag pending bits.
/// @param  SDIO_IT: specifies the flag pending bit to clear.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SDIO_ClearFlag(u32 SDIO_FLAG)
{
    SDIO->CLR_MMC_INT |= SDIO_FLAG;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the SDIO's interrupt pending bits.
/// @param  SDIO_IT: specifies the interrupt pending bit to clear.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SDIO_ClearITPendingBit(u32 SDIO_IT)
{
    SDIO->CLR_MMC_INT |= SDIO_IT;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified SDIO flag is set or not.
/// @param  SDIO_FLAG: specifies the flag to check.
/// @retval The new state of SDIO_FLAG (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
FlagStatus SDIO_GetFlagStatus(u32 SDIO_FLAG)
{
    return ((SDIO->CLR_MMC_INT & SDIO_FLAG) ? SET : RESET);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Reads the value of the data transfer timeout count
/// @param  None.
/// @retval timeout count.
////////////////////////////////////////////////////////////////////////////////
u32 SDIO_GetTimeOutCounter(void)
{
    return (SDIO->MMC_TIMEOUTCNT & 0xFF);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Read one data word from FIFO.
/// @param  None.
/// @retval Data received.
////////////////////////////////////////////////////////////////////////////////
u32 SDIO_ReadData(void)
{
    return SDIO->FIFO;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Write one data word to FIFO.
/// @param  tempbuff : Write data.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SDIO_WriteData(u32 tempbuff)
{
    SDIO->FIFO = tempbuff;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns number of remaining data bytes to be transferred.
/// @param  None
/// @retval Number of remaining data bytes to be transferred
////////////////////////////////////////////////////////////////////////////////
u32 SDIO_GetDataCounter(void)
{
    return SDIO->MMC_BYTECNTL;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enable or Dsiable DMA .
/// @param  tempbuff : Write data.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SDIO_DMACmd(FunctionalState state)
{
    (state) ?  ((SDIO->BUF_CTL |= SDIO_BUF_CTLL_DMAHEN), SDIO->BUF_CTL &= (~(SDIO_BUF_CTLL_DRM))) : (SDIO->BUF_CTL &= ~SDIO_BUF_CTLL_DMAHEN);
}


/// @}

/// @}

/// @}

