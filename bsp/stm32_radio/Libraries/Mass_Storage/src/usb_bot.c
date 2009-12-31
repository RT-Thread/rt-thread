/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : usb_bot.c
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 04/27/2009
* Description        : BOT State Machine management
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usb_scsi.h"
#include "hw_config.h"
#include "usb_regs.h"
#include "usb_mem.h"
#include "usb_conf.h"
#include "usb_bot.h"
#include "memory.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t Bot_State;
uint8_t Bulk_Data_Buff[BULK_MAX_PACKET_SIZE];  /* data buffer*/
uint16_t Data_Len;
Bulk_Only_CBW CBW;
Bulk_Only_CSW CSW;
uint32_t SCSI_LBA , SCSI_BlkLen;
extern uint32_t Max_Lun;
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Mass_Storage_In
* Description    : Mass Storage IN transfer.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Mass_Storage_In (void)
{
    switch (Bot_State)
    {
    case BOT_CSW_Send:
    case BOT_ERROR:
        Bot_State = BOT_IDLE;
        SetEPRxStatus(ENDP2, EP_RX_VALID);/* enable the Endpoint to recive the next cmd*/
        break;
    case BOT_DATA_IN:
        switch (CBW.CB[0])
        {
        case SCSI_READ10:
            SCSI_Read10_Cmd(CBW.bLUN , SCSI_LBA , SCSI_BlkLen);
            break;
        }
        break;
    case BOT_DATA_IN_LAST:
        Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
        SetEPRxStatus(ENDP2, EP_RX_VALID);
        break;

    default:
        break;
    }
}

/*******************************************************************************
* Function Name  : Mass_Storage_Out
* Description    : Mass Storage OUT transfer.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Mass_Storage_Out (void)
{
    uint8_t CMD;
    CMD = CBW.CB[0];
    Data_Len = GetEPRxCount(ENDP2);


    /* read data to Bulk_Data_Buff */
    PMAToUserBufferCopy(Bulk_Data_Buff, ENDP2_RXADDR, Data_Len);

    switch (Bot_State)
    {
    case BOT_IDLE:
        CBW_Decode();
        break;
    case BOT_DATA_OUT:
        if (CMD == SCSI_WRITE10)
        {
            SCSI_Write10_Cmd(CBW.bLUN , SCSI_LBA , SCSI_BlkLen);
            break;
        }
        Bot_Abort(DIR_OUT);
        Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
        Set_CSW (CSW_PHASE_ERROR, SEND_CSW_DISABLE);
        break;
    default:
        Bot_Abort(BOTH_DIR);
        Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
        Set_CSW (CSW_PHASE_ERROR, SEND_CSW_DISABLE);
        break;
    }
}

/*******************************************************************************
* Function Name  : CBW_Decode
* Description    : Decode the received CBW and call the related SCSI command
*                 routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CBW_Decode(void)
{
    uint32_t Counter;

    /* read data from Bulk_Data_Buff to CBW */
    for (Counter = 0; Counter < Data_Len; Counter++)
    {
        *((uint8_t *)&CBW + Counter) = Bulk_Data_Buff[Counter];
    }
    /* copy return TAG */
    CSW.dTag = CBW.dTag;
    CSW.dDataResidue = CBW.dDataLength;

    if (Data_Len != BOT_CBW_PACKET_LENGTH)
    {
        Bot_Abort(BOTH_DIR);
        /* reset the CBW.dSignature to desible the clear feature until receiving a Mass storage reset*/
        CBW.dSignature = 0;
        Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, PARAMETER_LIST_LENGTH_ERROR);
        Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
        return;
    }

    if ((CBW.CB[0] == SCSI_READ10 ) || (CBW.CB[0] == SCSI_WRITE10 ))
    {
        /* Calculate Logical Block Address */
        SCSI_LBA = (CBW.CB[2] << 24) | (CBW.CB[3] << 16) | (CBW.CB[4] <<  8) | CBW.CB[5];
        /* Calculate the Number of Blocks to transfer */
        SCSI_BlkLen = (CBW.CB[7] <<  8) | CBW.CB[8];
    }

    /* USBC */
    if (CBW.dSignature == BOT_CBW_SIGNATURE)
    {
        /* Valid CBW */
        if ((CBW.bLUN > Max_Lun) || (CBW.bCBLength < 1) || (CBW.bCBLength > 16))
        {
            Bot_Abort(BOTH_DIR);
            Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
            Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
        }
        else
        {
            switch (CBW.CB[0])
            {
            case SCSI_REQUEST_SENSE:
                SCSI_RequestSense_Cmd (CBW.bLUN);
                break;
            case SCSI_INQUIRY:
                SCSI_Inquiry_Cmd(CBW.bLUN);
                break;
            case SCSI_START_STOP_UNIT:
                SCSI_Start_Stop_Unit_Cmd(CBW.bLUN);
                break;
            case SCSI_ALLOW_MEDIUM_REMOVAL:
                SCSI_Start_Stop_Unit_Cmd(CBW.bLUN);
                break;
            case SCSI_MODE_SENSE6:
                SCSI_ModeSense6_Cmd (CBW.bLUN);
                break;
            case SCSI_MODE_SENSE10:
                SCSI_ModeSense10_Cmd (CBW.bLUN);
                break;
            case SCSI_READ_FORMAT_CAPACITIES:
                SCSI_ReadFormatCapacity_Cmd(CBW.bLUN);
                break;
            case SCSI_READ_CAPACITY10:
                SCSI_ReadCapacity10_Cmd(CBW.bLUN);
                break;
            case SCSI_TEST_UNIT_READY:
                SCSI_TestUnitReady_Cmd(CBW.bLUN);
                break;
            case SCSI_READ10:
                SCSI_Read10_Cmd(CBW.bLUN, SCSI_LBA , SCSI_BlkLen);
                break;
            case SCSI_WRITE10:
                SCSI_Write10_Cmd(CBW.bLUN, SCSI_LBA , SCSI_BlkLen);
                break;
            case SCSI_VERIFY10:
                SCSI_Verify10_Cmd(CBW.bLUN);
                break;
            case SCSI_FORMAT_UNIT:
                SCSI_Format_Cmd(CBW.bLUN);
                break;
                /*Unsupported command*/

            case SCSI_MODE_SELECT10:
                SCSI_Mode_Select10_Cmd(CBW.bLUN);
                break;
            case SCSI_MODE_SELECT6:
                SCSI_Mode_Select6_Cmd(CBW.bLUN);
                break;

            case SCSI_SEND_DIAGNOSTIC:
                SCSI_Send_Diagnostic_Cmd(CBW.bLUN);
                break;
            case SCSI_READ6:
                SCSI_Read6_Cmd(CBW.bLUN);
                break;
            case SCSI_READ12:
                SCSI_Read12_Cmd(CBW.bLUN);
                break;
            case SCSI_READ16:
                SCSI_Read16_Cmd(CBW.bLUN);
                break;
            case SCSI_READ_CAPACITY16:
                SCSI_READ_CAPACITY16_Cmd(CBW.bLUN);
                break;
            case SCSI_WRITE6:
                SCSI_Write6_Cmd(CBW.bLUN);
                break;
            case SCSI_WRITE12:
                SCSI_Write12_Cmd(CBW.bLUN);
                break;
            case SCSI_WRITE16:
                SCSI_Write16_Cmd(CBW.bLUN);
                break;
            case SCSI_VERIFY12:
                SCSI_Verify12_Cmd(CBW.bLUN);
                break;
            case SCSI_VERIFY16:
                SCSI_Verify16_Cmd(CBW.bLUN);
                break;

            default:
            {
                Bot_Abort(BOTH_DIR);
                Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_COMMAND);
                Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
            }
            }
        }
    }
    else
    {
        /* Invalid CBW */
        Bot_Abort(BOTH_DIR);
        Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_COMMAND);
        Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
    }
}

/*******************************************************************************
* Function Name  : Transfer_Data_Request
* Description    : Send the request response to the PC HOST.
* Input          : uint8_t* Data_Address : point to the data to transfer.
*                  uint16_t Data_Length : the nember of Bytes to transfer.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Transfer_Data_Request(uint8_t* Data_Pointer, uint16_t Data_Len)
{
    UserToPMABufferCopy(Data_Pointer, ENDP1_TXADDR, Data_Len);

    SetEPTxCount(ENDP1, Data_Len);
    SetEPTxStatus(ENDP1, EP_TX_VALID);
    Bot_State = BOT_DATA_IN_LAST;
    CSW.dDataResidue -= Data_Len;
    CSW.bStatus = CSW_CMD_PASSED;
}

/*******************************************************************************
* Function Name  : Set_CSW
* Description    : Set the SCW with the needed fields.
* Input          : uint8_t CSW_Status this filed can be CSW_CMD_PASSED,CSW_CMD_FAILED,
*                  or CSW_PHASE_ERROR.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Set_CSW (uint8_t CSW_Status, uint8_t Send_Permission)
{
    CSW.dSignature = BOT_CSW_SIGNATURE;
    CSW.bStatus = CSW_Status;

    UserToPMABufferCopy(((uint8_t *)& CSW), ENDP1_TXADDR, CSW_DATA_LENGTH);

    SetEPTxCount(ENDP1, CSW_DATA_LENGTH);
    Bot_State = BOT_ERROR;
    if (Send_Permission)
    {
        Bot_State = BOT_CSW_Send;
        SetEPTxStatus(ENDP1, EP_TX_VALID);
    }

}

/*******************************************************************************
* Function Name  : Bot_Abort
* Description    : Stall the needed Endpoint according to the selected direction.
* Input          : Endpoint direction IN, OUT or both directions
* Output         : None.
* Return         : None.
*******************************************************************************/
void Bot_Abort(uint8_t Direction)
{
    switch (Direction)
    {
    case DIR_IN :
        SetEPTxStatus(ENDP1, EP_TX_STALL);
        break;
    case DIR_OUT :
        SetEPRxStatus(ENDP2, EP_RX_STALL);
        break;
    case BOTH_DIR :
        SetEPTxStatus(ENDP1, EP_TX_STALL);
        SetEPRxStatus(ENDP2, EP_RX_STALL);
        break;
    default:
        break;
    }
}

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
