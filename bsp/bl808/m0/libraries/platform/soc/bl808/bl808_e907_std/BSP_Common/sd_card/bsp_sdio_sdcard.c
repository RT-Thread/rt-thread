#include "bsp_sdio_sdcard.h"
#include "bflb_platform.h"

#define SDH_CLK_SRC                     (32000000ul)
#define SDH_CLK_INIT                    (400000ul)
#define SDH_CLK_TRANSFER                (16000000ul)
#define SDIO_CMDTIMEOUT                ((uint32_t)0x00010000)
/* Private variables ---------------------------------------------------------*/

static sd_card_t* pSDCardInfo = NULL;

static volatile SD_Error SDH_WaitStatus   =  SD_WAITING;
static volatile SD_Error SDH_CMDWaitStatus   =  SD_WAITING;
static SDH_Cfg_Type                 SDH_Cfg_Type_Instance;
static SDH_CMD_Cfg_Type             SDH_CMD_Cfg_TypeInstance;
static SDH_Data_Cfg_Type            SDH_Data_Cfg_TypeInstance;
static SDH_Trans_Cfg_Type           SDH_Trans_Cfg_TypeInstance= {&SDH_Data_Cfg_TypeInstance,&SDH_CMD_Cfg_TypeInstance};
static SDH_Trans_Callback_Cfg_Type  SDH_Trans_Callback_Cfg_TypeInstance;


static SDH_Handle_Cfg_Type SDH_Handle_Cfg_TypeInstance ;

static SDH_DMA_Cfg_Type   SDH_DMA_Cfg_TypeInstance;
/*causion: ADMA related variables must on OCRAM or shared ram*/
static SDH_ADMA2_Desc_Type adma2Entries[16] ATTR_DMA_RAM_SECTION;


/* Private function prototypes -----------------------------------------------*/
static void SD_DecodeCid(sd_card_t* card, uint32_t* rawCid);
static void SD_DecodeCsd(sd_card_t* card, uint32_t* rawCsd);
static void SD_DecodeScr(sd_card_t* card, uint32_t* rawScr);
static void SDH_INT_Init(void);
static status_t SDH_SendCardCommand(SDH_CMD_Cfg_Type* cmd);
static void SDH_HostInit(void);
static status_t SDH_GoIdle(void);
static status_t SD_SendApplicationCmd(uint32_t relativeAddress);
static status_t SD_SendInterfaceCondition(void);
static status_t SD_ApplicationSendOperationCondition(sd_card_t* card, uint32_t argument);
static status_t SD_AllSendCid(sd_card_t* card);
static status_t SD_SendRca(sd_card_t* card);
static status_t SD_SendCsd(sd_card_t* card);
static status_t SD_SelectCard(sd_card_t* card, BL_Fun_Type NewState);
static status_t SD_SendScr(sd_card_t* card);
static status_t SD_SendSsr(sd_card_t* card);
static status_t SD_SetDataBusWidth(sd_card_t* card, SDH_Data_Bus_Width_Type width);
static status_t SD_SwitchFunction(uint32_t mode, uint32_t group, uint32_t number, uint32_t status[16]);
static status_t SD_SelectFunction(uint32_t group, uint32_t function);
static status_t SD_SetBlockSize(uint32_t blockSize);
static status_t SDH_SDCardInit(uint32_t bus_wide,sd_card_t* card);
static status_t WaitInProgramming(void);
static status_t IsCardProgramming(uint8_t* pstatus);
static status_t SDH_CardTransferNonBlocking(SDH_DMA_Cfg_Type* dmaCfg,SDH_Trans_Cfg_Type* transfer);


static void SD_DecodeCid(sd_card_t* card, uint32_t* rawCid)
{
    sd_cid_t* cid;

    cid = &(card->cid);
    cid->manufacturerID = (uint8_t)((rawCid[3U] & 0xFF0000U) >> 16U);
    cid->applicationID = (uint16_t)((rawCid[3U] & 0xFFFFU) >> 0U);

    cid->productName[0U] = (uint8_t)((rawCid[1U] & 0xFF000000U) >> 24);
    cid->productName[1U] = (uint8_t)((rawCid[2U] & 0xFF) >> 0U);
    cid->productName[2U] = (uint8_t)((rawCid[2U] & 0xFF00U) >> 8U);
    cid->productName[3U] = (uint8_t)((rawCid[2U] & 0xFF0000U) >> 16U);
    cid->productName[4U] = (uint8_t)((rawCid[2U] & 0xFF000000U) >> 24U);

    cid->productVersion = (uint8_t)((rawCid[1U] & 0xFF0000U) >> 16U);

    cid->productSerialNumber = (uint32_t)((rawCid[1U] & 0xFFFFU) << 16U);
    cid->productSerialNumber |= (uint32_t)((rawCid[0U] & 0xFFFF0000U) >> 16U);

    cid->manufacturerData = (uint16_t)((rawCid[0U] & 0xFFFU) >> 0U);
}
static void SD_DecodeCsd(sd_card_t* card, uint32_t* rawCsd)
{
    sd_csd_t* csd;

    csd = &(card->csd);
    csd->csdStructure = (uint8_t)((rawCsd[3U] & 0xC00000U) >> 22U);
    csd->dataReadAccessTime1 = (uint8_t)((rawCsd[3U] & 0xFF00U) >> 8U);
    csd->dataReadAccessTime2 = (uint8_t)((rawCsd[3U] & 0xFFU) >> 0U);

    csd->transferSpeed = (uint8_t)((rawCsd[2U] & 0xFF000000U) >> 24);
    csd->cardCommandClass = (uint16_t)((rawCsd[2U] & 0xFFF000U) >> 12U);
    csd->readBlockLength = (uint8_t)((rawCsd[2U] & 0xF00U) >> 8U);

    switch (csd->csdStructure)
    {
    /*csd version 1.1*/
    case 0:
        csd->deviceSize = (uint32_t)((rawCsd[2U] & 0x3U) << 10U);
        csd->deviceSize |= (uint32_t)((rawCsd[1U] & 0xFFC00000U) >> 22U);

        csd->deviceSizeMultiplier = (uint8_t)((rawCsd[1U] & 0x380U) >> 7U);

        /* Get card total block count and block size. */
        card->blockCount = ((csd->deviceSize + 1U) << (csd->deviceSizeMultiplier + 2U));
        card->blockSize = (1U << (csd->readBlockLength));
        if (card->blockSize != SDH_DEFAULT_BLOCK_SIZE)
        {
            card->blockCount = (card->blockCount * card->blockSize);
            card->blockSize = SDH_DEFAULT_BLOCK_SIZE;
            card->blockCount = (card->blockCount / card->blockSize);
        }
        break;
    /*csd version 2.0*/
    case 1:
        card->blockSize = SDH_DEFAULT_BLOCK_SIZE;

        csd->deviceSize = (uint32_t)((rawCsd[1U] & 0x3FFFFF00U) >> 8U);

        if (csd->deviceSize >= 0xFFFFU)
        {
            card->flags |= SD_SupportSdxcFlag;
        }

        card->blockCount = ((csd->deviceSize + 1U) * 1024U);
        break;
    default:
        break;
    }
}
static void SD_DecodeScr(sd_card_t* card, uint32_t* rawScr)
{
    sd_scr_t* scr;

    scr = &(card->scr);
    scr->scrStructure = (uint8_t)((rawScr[1U] & 0xF0000000U) >> 28U);
    scr->sdSpecification = (uint8_t)((rawScr[1U] & 0xF000000U) >> 24U);

    if ((uint8_t)((rawScr[1U] & 0x800000U) >> 23U))
    {
        scr->flags |= SD_ScrDataStatusAfterErase;
    }

    scr->sdSecurity = (uint8_t)((rawScr[1U] & 0x700000U) >> 20U);
    scr->sdBusWidths = (uint8_t)((rawScr[1U] & 0xF0000U) >> 16U);

    if ((uint8_t)((rawScr[0U] & 0x8000U) >> 15U))
    {
        scr->flags |= SD_ScrSdSpecification3;
    }

    scr->extendedSecurity = (uint8_t)((rawScr[1U] & 0x7800U) >> 10U);
    scr->commandSupport = (uint8_t)(rawScr[1U] & 0x3U);
    scr->reservedForManufacturer = rawScr[0U];

    /* Get specification version. */
    switch (scr->sdSpecification)
    {
    case 0U:
        card->version = SD_SpecificationVersion1_0;
        break;
    case 1U:
        card->version = SD_SpecificationVersion1_1;
        break;
    case 2U:
        card->version = SD_SpecificationVersion2_0;
        if (card->scr.flags & SD_ScrSdSpecification3)
        {
            card->version = SD_SpecificationVersion3_0;
        }
        break;
    default:
        break;
    }
    if (card->scr.sdBusWidths & 0x4U)
    {
        card->flags |= SD_Support4BitWidthFlag;
    }
    /* speed class control cmd */
    if (card->scr.commandSupport & 0x01U)
    {
        card->flags |= SD_SupportSpeedClassControlCmd;
    }
    /* set block count cmd */
    if (card->scr.commandSupport & 0x02U)
    {
        card->flags |= SD_SupportSetBlockCountCmd;
    }
}


/*!< SDH transfer complete callback */
void SDH_TransferFinished_CallBack(SDH_Handle_Cfg_Type* handle,SDH_Stat_Type status,void* userData)
{
    //bflb_platform_printf("Interrupt occurs! intFlag=0x%02x,\r\n",handle->intFlag);
    if(status != SDH_STAT_SUCCESS)
    {
        SDH_WaitStatus = SD_DataCfg_ERROR;
    }
    else
    {
        SDH_WaitStatus = SD_OK;
    }
}
/*!< SDH transfer complete callback */
void SDH_CMDTransferFinished_CallBack(SDH_Handle_Cfg_Type* handle,SDH_Stat_Type status,void* userData)
{
    //bflb_platform_printf("Interrupt occurs! intFlag=0x%02x,\r\n",handle->intFlag);
    if(status != SDH_STAT_SUCCESS)
    {
        SDH_CMDWaitStatus = SD_CMD_ERROR;
    }
    else
    {
        SDH_CMDWaitStatus = SD_OK;
    }
}

/****************************************************************************//**
 * @brief  SDH INT init
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
static void SDH_INT_Init(void)
{
    SDH_DisableIntSource(SDH_INT_ALL);
    SDH_Trans_Callback_Cfg_TypeInstance.SDH_CallBack_TransferFinished = SDH_TransferFinished_CallBack;
    SDH_Trans_Callback_Cfg_TypeInstance.SDH_CMDCallBack_TransferFinished = SDH_CMDTransferFinished_CallBack;
    SDH_InstallHandleCallback(&SDH_Handle_Cfg_TypeInstance, &SDH_Trans_Callback_Cfg_TypeInstance, NULL);
}

static status_t SDH_SendCardCommand(SDH_CMD_Cfg_Type* cmd)
{
    status_t errorstatus = Status_Success;

    uint32_t timeout = SDIO_CMDTIMEOUT;
    SDH_CMDWaitStatus=SD_WAITING;

    SDH_SendCommand(cmd);

    SDH_ITConfig(SDH_INT_CMD_COMPLETED|SDH_INT_CMD_ERRORS,ENABLE);
    /*wait for Xfer status. might pending here in multi-task OS*/
    while( SDH_CMDWaitStatus == SD_WAITING)
    {
        timeout--;
        //SDH_MSG("timeout is %d\r\n",timeout);
        if(timeout==0)
            break;
    }
    SDH_ITConfig(SDH_INT_CMD_COMPLETED|SDH_INT_CMD_ERRORS,DISABLE);

    SDH_MSG("timeout=%d\r\n",timeout);
    SDH_MSG("SDH_CMDWaitStatus=%d\r\n",SDH_CMDWaitStatus);
    if(timeout == 0)
    {
        SDH_MSG("Status_Timeout\r\n");
        errorstatus = Status_Timeout;
    }
    else if(SDH_CMDWaitStatus != SD_OK)
    {
        SDH_MSG("Comamnd error\r\n");
        errorstatus = Status_SDH_CmdResponseError;
    }
    else
    {
        SDH_GetCmdResp(cmd);

    }
    SDH_CMDWaitStatus = SD_WAITING;

    return errorstatus;
}

static void SDH_HostInit(void)
{
    /* initialise SDH controller*/
    SDH_Cfg_Type_Instance.vlot18Enable = DISABLE;
    SDH_Cfg_Type_Instance.highSpeed = ENABLE;
    SDH_Cfg_Type_Instance.dataWidth = SDH_DATA_BUS_WIDTH_1BIT;
    SDH_Cfg_Type_Instance.volt = SDH_VOLTAGE_3P3V;
    SDH_Cfg_Type_Instance.srcClock = SDH_CLK_SRC;
    SDH_Cfg_Type_Instance.busClock = SDH_CLK_INIT;
    SDH_Ctrl_Init(&SDH_Cfg_Type_Instance);

    /*setup timeout counter*/
    SDH_Set_Timeout(0x0e);

    /*power on host controller*/
    SDH_Powon();
}
/*
* GO_IDLE_STATE, send card to reset state
*/
static status_t SDH_GoIdle(void)
{
    status_t errorstatus = Status_Success;
    SDH_CMD_Cfg_Type  SDH_CMD_Cfg_TypeInstance;

    /*CMD0: GO_IDLE_STATE, send card to reset state*/
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_GO_IDLE_STATE;
    SDH_CMD_Cfg_TypeInstance.argument = 0;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_NONE;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);
    return errorstatus;
}

static status_t SD_SendApplicationCmd(uint32_t relativeAddress)
{
    status_t errorstatus = Status_Success;
    SDH_CMD_Cfg_Type  SDH_CMD_Cfg_TypeInstance;

    /*send CMD55*/
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_APP_CMD;
    SDH_CMD_Cfg_TypeInstance.argument = relativeAddress;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);
    if(errorstatus != Status_Success)
    {
        return Status_SDH_CmdResponseError;
    }
    else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS)
    {
        return Status_SDH_CmdResponseError;
    }
    return errorstatus;
}

static status_t SD_SendInterfaceCondition(void)
{
    status_t errorstatus = Status_Success;
    SDH_CMD_Cfg_Type  SDH_CMD_Cfg_TypeInstance;

    /* CMD8: SEND_IF_COND */
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_HS_SEND_EXT_CSD;
    SDH_CMD_Cfg_TypeInstance.argument = SD_CHECK_PATTERN;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R7;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);
    if(errorstatus != Status_Success)
        return Status_SDH_CmdResponseError;

    SDH_MSG("\r\n Response to CMD8 is: 0x%02x.\r\n",SDH_CMD_Cfg_TypeInstance.response[0]);


    if( (SDH_CMD_Cfg_TypeInstance.response[0U] & 0xFFU) != (SD_CHECK_PATTERN&0xff) )
        return Status_SDH_CardNotSupport;

    return errorstatus;
}

static status_t SD_ApplicationSendOperationCondition(sd_card_t* card, uint32_t argument)
{
    status_t errorstatus = Status_Success;
    uint32_t response = 0, count = 0, validvoltage = 0;
    SDH_CMD_Cfg_Type  SDH_CMD_Cfg_TypeInstance;

    do
    {

        if(Status_Success != (errorstatus = SD_SendApplicationCmd(0)) )
            return errorstatus;
        /*ACMD41*/
        SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SD_APP_OP_COND;
        SDH_CMD_Cfg_TypeInstance.argument = argument;
        SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
        SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R3;
        SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

        errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);
        if(errorstatus != Status_Success)
            return Status_SDH_CmdResponseError;

        response = SDH_CMD_Cfg_TypeInstance.response[0];
        validvoltage = (((response >> 31) == 1) ? 1 : 0);
        count++;
    }
    while(  (!validvoltage) && (count < SD_MAX_VOLT_TRIAL)  );

    if(count  == SD_MAX_VOLT_TRIAL)
        return Status_Timeout;
    else
    {
        card->ocr = response;
        if (response &= SD_OcrHostCapacitySupportFlag)
        {
            /* change from sdsc to sdhc */
            card->flags |= SD_SupportHighCapacityFlag;
        }
    }

    return errorstatus;
}
static status_t SD_AllSendCid(sd_card_t* card)
{
    status_t errorstatus = Status_Success;
    SDH_CMD_Cfg_Type  SDH_CMD_Cfg_TypeInstance;

    /* CMD2: SD_CMD_ALL_SEND_CID */
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_ALL_SEND_CID;
    SDH_CMD_Cfg_TypeInstance.argument = 0;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R2;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);
    if(errorstatus != Status_Success)
        return Status_SDH_CmdResponseError;

    card->rawCid[0] = SDH_CMD_Cfg_TypeInstance.response[0];
    card->rawCid[1] = SDH_CMD_Cfg_TypeInstance.response[1];
    card->rawCid[2] = SDH_CMD_Cfg_TypeInstance.response[2];
    card->rawCid[3] = SDH_CMD_Cfg_TypeInstance.response[3];

    SD_DecodeCid(card,card->rawCid);

    return errorstatus;
}

static status_t SD_SendRca(sd_card_t* card)
{
    status_t errorstatus = Status_Success;
    SDH_CMD_Cfg_Type  SDH_CMD_Cfg_TypeInstance;

    /*CMD3: send relative card address*/
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SET_REL_ADDR;
    SDH_CMD_Cfg_TypeInstance.argument = 0;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R6;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);
    if(errorstatus != Status_Success)
        return Status_SDH_CmdResponseError;

    card->relativeAddress = SDH_CMD_Cfg_TypeInstance.response[0]>>16;

    return errorstatus;
}

static status_t SD_SendCsd(sd_card_t* card)
{
    status_t errorstatus = Status_Success;
    SDH_CMD_Cfg_Type  SDH_CMD_Cfg_TypeInstance;

    /*CMD9: send card-specific data(CSD)*/
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SEND_CSD;
    SDH_CMD_Cfg_TypeInstance.argument = (uint32_t)( (card->relativeAddress) << 16);
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R2;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);
    if(errorstatus != Status_Success)
        return Status_SDH_CmdResponseError;

    card->rawCsd[0] = SDH_CMD_Cfg_TypeInstance.response[0];
    card->rawCsd[1] = SDH_CMD_Cfg_TypeInstance.response[1];
    card->rawCsd[2] = SDH_CMD_Cfg_TypeInstance.response[2];
    card->rawCsd[3] = SDH_CMD_Cfg_TypeInstance.response[3];

    SD_DecodeCsd(card,card->rawCsd);

    return errorstatus;
}

static status_t SD_SelectCard(sd_card_t* card, BL_Fun_Type NewState)
{
    status_t errorstatus = Status_Success;
    SDH_CMD_Cfg_Type  SDH_CMD_Cfg_TypeInstance;

    /* CMD7: select/deselect specified card */
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SEL_DESEL_CARD;

    if(NewState == ENABLE)
    {
        SDH_CMD_Cfg_TypeInstance.argument = (uint32_t)( (card->relativeAddress) << 16);
        SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1B;
    }
    else
    {
        SDH_CMD_Cfg_TypeInstance.argument = 0;
        SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_NONE;
    }

    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);

    if(errorstatus != Status_Success)
        return Status_SDH_TransferFailed;
    else if( (NewState == ENABLE) && (SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS) )
    {
        return Status_SDH_CmdResponseError;
    }

    return errorstatus;
}

static status_t SD_SendScr(sd_card_t* card)
{
    status_t errorstatus = Status_Success;
    SDH_Stat_Type stat = SDH_STAT_SUCCESS;
    SDH_CMD_Cfg_Type   SDH_CMD_Cfg_TypeInstance;
    SDH_Data_Cfg_Type  SDH_Data_Cfg_TypeInstance;
    uint32_t tempscr[2] = {0, 0};

    errorstatus = SD_SendApplicationCmd((uint32_t)( (card->relativeAddress) << 16));
    if(errorstatus != Status_Success)
        goto out;

    /*!< Set Block Size To 8 Bytes */
    SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = DISABLE;
    SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
    SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
    SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
    SDH_Data_Cfg_TypeInstance.blockSize = 8;
    SDH_Data_Cfg_TypeInstance.blockCount = 1;
    SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
    SDH_Data_Cfg_TypeInstance.rxData = tempscr;
    SDH_Data_Cfg_TypeInstance.txDataLen = 0;
    SDH_Data_Cfg_TypeInstance.txData = NULL;
    /* Config the data transfer parameter */
    stat = SDH_ConfigDataTranfer(&SDH_Data_Cfg_TypeInstance);
    if (SDH_STAT_SUCCESS != stat)
    {
        return Status_SDH_TransferFailed;
    }

    /*!< Send ACMD51 SD_APP_SEND_SCR with argument as 0 */
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SD_APP_SEND_SCR;
    SDH_CMD_Cfg_TypeInstance.argument = 0;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);

    if(errorstatus != Status_Success)
        goto out;
    else if( SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS )
    {
        errorstatus = Status_SDH_CmdResponseError;
        goto out;
    }

    SDH_WaitStatus=SD_WAITING;
    SDH_ITConfig(SDH_INT_BUFFER_READ_READY|SDH_INT_DATA_COMPLETED|SDH_INT_DATA_ERRORS|SDH_INT_DMA_ERROR|SDH_INT_AUTO_CMD12_ERROR,ENABLE);
    /*wait for Xfer status. might pending here in multi-task OS*/
    while(SDH_WaitStatus == SD_WAITING) {}

    SDH_ITConfig(SDH_INT_BUFFER_READ_READY|SDH_INT_DATA_COMPLETED|SDH_INT_DATA_ERRORS|SDH_INT_DMA_ERROR|SDH_INT_AUTO_CMD12_ERROR,DISABLE);

    if(SDH_WaitStatus != SD_OK)
    {
        errorstatus = Status_SDH_TransferFailed;
        SDH_WaitStatus = SD_WAITING;
        goto out;
    }
    else
    {
        SDH_WaitStatus = SD_WAITING;
        SDH_ReadDataPort(&SDH_Data_Cfg_TypeInstance);
        card->rawScr[1] = ((tempscr[0] & SD_0TO7BITS) << 24) | ((tempscr[0] & SD_8TO15BITS) << 8) | ((tempscr[0] & SD_16TO23BITS) >> 8) | ((tempscr[0] & SD_24TO31BITS) >> 24);
        card->rawScr[0] = ((tempscr[1] & SD_0TO7BITS) << 24) | ((tempscr[1] & SD_8TO15BITS) << 8) | ((tempscr[1] & SD_16TO23BITS) >> 8) | ((tempscr[1] & SD_24TO31BITS) >> 24);
        SD_DecodeScr(card,card->rawScr);
    }

out:
    return errorstatus;
}
static status_t SD_SendSsr(sd_card_t* card)
{
    status_t errorstatus = Status_Success;
    SDH_Stat_Type stat = SDH_STAT_SUCCESS;
    SDH_CMD_Cfg_Type   SDH_CMD_Cfg_TypeInstance;
    SDH_Data_Cfg_Type  SDH_Data_Cfg_TypeInstance;

    errorstatus = SD_SendApplicationCmd((uint32_t)( (card->relativeAddress) << 16));
    if(errorstatus != Status_Success)
        goto out;

    /*!< Set Block Size To 512 Bytes */
    SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = DISABLE;
    SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
    SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
    SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
    SDH_Data_Cfg_TypeInstance.blockSize = 64;
    SDH_Data_Cfg_TypeInstance.blockCount = 1;
    SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
    SDH_Data_Cfg_TypeInstance.rxData = card->rawSsr;
    SDH_Data_Cfg_TypeInstance.txDataLen = 0;
    SDH_Data_Cfg_TypeInstance.txData = NULL;
    /* Config the data transfer parameter */
    stat = SDH_ConfigDataTranfer(&SDH_Data_Cfg_TypeInstance);
    if (SDH_STAT_SUCCESS != stat)
    {
        return Status_SDH_TransferFailed;
    }

    /*!< Send ACMD13 SD_APP_SEND_SCR with argument as 0 */
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SD_APP_STAUS;
    SDH_CMD_Cfg_TypeInstance.argument = 0;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);

    if(errorstatus != Status_Success)
        goto out;
    else if( SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS )
    {
        errorstatus = Status_SDH_CmdResponseError;
        goto out;
    }

    SDH_WaitStatus=SD_WAITING;
    SDH_ITConfig(SDH_INT_BUFFER_READ_READY|SDH_INT_DATA_COMPLETED|SDH_INT_DATA_ERRORS|SDH_INT_DMA_ERROR|SDH_INT_AUTO_CMD12_ERROR,ENABLE);
    /*wait for Xfer status. might pending here in multi-task OS*/
    while(SDH_WaitStatus == SD_WAITING) {}

    SDH_ITConfig(SDH_INT_BUFFER_READ_READY|SDH_INT_DATA_COMPLETED|SDH_INT_DATA_ERRORS|SDH_INT_DMA_ERROR|SDH_INT_AUTO_CMD12_ERROR,DISABLE);

    if(SDH_WaitStatus != SD_OK)
    {
        errorstatus = Status_SDH_TransferFailed;
        SDH_WaitStatus = SD_WAITING;
        goto out;
    }
    else
    {
        SDH_WaitStatus = SD_WAITING;
        SDH_ReadDataPort(&SDH_Data_Cfg_TypeInstance);
    }

out:
    return errorstatus;
}
static status_t SD_SetDataBusWidth(sd_card_t* card, SDH_Data_Bus_Width_Type width)
{
    status_t errorstatus = Status_Success;
    SDH_CMD_Cfg_Type   SDH_CMD_Cfg_TypeInstance;

    if(width == SDH_DATA_BUS_WIDTH_1BIT)
        SDH_CMD_Cfg_TypeInstance.argument = 0;
    else if(width == SDH_DATA_BUS_WIDTH_4BITS)
        SDH_CMD_Cfg_TypeInstance.argument = 2;
    else
        return Status_InvalidArgument;


    errorstatus = SD_SendApplicationCmd((uint32_t)( (card->relativeAddress) << 16));
    if(errorstatus != Status_Success)
        goto out;

    /*!< Send ACMD6 APP_CMD with argument as 2 for wide bus mode */
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_APP_SD_SET_BUSWIDTH;

    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);

    if(errorstatus != Status_Success)
        goto out;
    else if( SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS )
    {
        errorstatus = Status_SDH_CmdResponseError;
        goto out;
    }

    /* reinitialise SDH controller*/
    SDH_Cfg_Type_Instance.vlot18Enable = DISABLE;
    SDH_Cfg_Type_Instance.highSpeed = ENABLE;
    SDH_Cfg_Type_Instance.dataWidth = width;
    SDH_Cfg_Type_Instance.volt = SDH_VOLTAGE_3P3V;
    SDH_Cfg_Type_Instance.srcClock = SDH_CLK_SRC;
    SDH_Cfg_Type_Instance.busClock = SDH_CLK_TRANSFER;
    SDH_Ctrl_Init(&SDH_Cfg_Type_Instance);

out:
    return errorstatus;
}
static status_t SD_SwitchFunction(uint32_t mode, uint32_t group, uint32_t number, uint32_t status[16])
{

    status_t errorstatus = Status_Success;
    SDH_Stat_Type stat = SDH_STAT_SUCCESS;
    SDH_CMD_Cfg_Type   SDH_CMD_Cfg_TypeInstance;
    SDH_Data_Cfg_Type  SDH_Data_Cfg_TypeInstance;

    /*!< Set Block Size To 512 Bytes */
    SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = DISABLE;
    SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
    SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
    SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
    SDH_Data_Cfg_TypeInstance.blockSize = 64;
    SDH_Data_Cfg_TypeInstance.blockCount = 1;
    SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
    SDH_Data_Cfg_TypeInstance.rxData = status;
    SDH_Data_Cfg_TypeInstance.txDataLen = 0;
    SDH_Data_Cfg_TypeInstance.txData = NULL;
    /* Config the data transfer parameter */
    stat = SDH_ConfigDataTranfer(&SDH_Data_Cfg_TypeInstance);
    if (SDH_STAT_SUCCESS != stat)
    {
        return Status_SDH_TransferFailed;
    }

    /*!< Send CMD6 SD_CMD_HS_SWITCH with argument as 0 */
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_HS_SWITCH;
    SDH_CMD_Cfg_TypeInstance.argument = (mode << 31U | 0x00FFFFFFU);
    SDH_CMD_Cfg_TypeInstance.argument &= ~((uint32_t)(0xFU) << (group * 4U));
    SDH_CMD_Cfg_TypeInstance.argument |= (number << (group * 4U));
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);

    if(errorstatus != Status_Success)
        goto out;
    else if( SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS )
    {
        errorstatus = Status_SDH_CmdResponseError;
        goto out;
    }


    /*wait for Xfer status. might pending here in multi-task OS*/
    SDH_WaitStatus=SD_WAITING;
    SDH_ITConfig(SDH_INT_BUFFER_READ_READY|SDH_INT_DATA_COMPLETED|SDH_INT_DATA_ERRORS|SDH_INT_DMA_ERROR|SDH_INT_AUTO_CMD12_ERROR,ENABLE);
    while(SDH_WaitStatus == SD_WAITING) {}

    SDH_ITConfig(SDH_INT_BUFFER_READ_READY|SDH_INT_DATA_COMPLETED|SDH_INT_DATA_ERRORS|SDH_INT_DMA_ERROR|SDH_INT_AUTO_CMD12_ERROR,DISABLE);

    if(SDH_WaitStatus != SD_OK)
    {
        errorstatus = Status_SDH_TransferFailed;
        SDH_WaitStatus = SD_WAITING;
        goto out;
    }
    else
    {
        SDH_WaitStatus = SD_WAITING;
        SDH_ReadDataPort(&SDH_Data_Cfg_TypeInstance);
    }

out:
    return errorstatus;
}

static ATTR_USED status_t SD_SelectFunction(uint32_t group, uint32_t function)
{
    status_t errorstatus = Status_Success;
    uint32_t cmd6Status[16] = {0};
    uint16_t functionGroupInfo[6U] = {0};
    uint32_t currentFunctionStatus = 0U;

    uint32_t i;

    /* Check if card support high speed mode. */
    if (Status_Success != SD_SwitchFunction(SDH_SwitchCheck, group, function, cmd6Status))
    {
        return Status_SDH_SDIO_SwitchHighSpeedFail;
    }

    for(i=0; i<16; i++)
    {
        SDH_MSG("cmd6Status[%d]=0x%x.\r\n",i,cmd6Status[i]);
    }
    /* In little endian mode, SD bus byte transferred first is the byte stored in lowest byte position in
    a word which will cause 4 byte's sequence in a word is not consistent with their original sequence from
    card. So the sequence of 4 bytes received in a word should be converted. */
    cmd6Status[0U] = SWAP_WORD_BYTE_SEQUENCE(cmd6Status[0U]);
    cmd6Status[1U] = SWAP_WORD_BYTE_SEQUENCE(cmd6Status[1U]);
    cmd6Status[2U] = SWAP_WORD_BYTE_SEQUENCE(cmd6Status[2U]);
    cmd6Status[3U] = SWAP_WORD_BYTE_SEQUENCE(cmd6Status[3U]);
    cmd6Status[4U] = SWAP_WORD_BYTE_SEQUENCE(cmd6Status[4U]);

    functionGroupInfo[5U] = (uint16_t)cmd6Status[0U];
    functionGroupInfo[4U] = (uint16_t)(cmd6Status[1U] >> 16U);
    functionGroupInfo[3U] = (uint16_t)(cmd6Status[1U]);
    functionGroupInfo[2U] = (uint16_t)(cmd6Status[2U] >> 16U);
    functionGroupInfo[1U] = (uint16_t)(cmd6Status[2U]);
    functionGroupInfo[0U] = (uint16_t)(cmd6Status[3U] >> 16U);
    currentFunctionStatus = ((cmd6Status[3U] & 0xFFFFU) << 8U) | (cmd6Status[4U] >> 24U);

    for(i=0; i<6; i++)
    {
        SDH_MSG("functionGroupInfo[%d]=0x%x.\r\n",i,functionGroupInfo[i]);
    }

    SDH_MSG("currentFunctionStatus = 0x%x.\r\n",currentFunctionStatus);

    /* check if function is support */
    if (((functionGroupInfo[group] & (1 << function)) == 0U) ||
            ((currentFunctionStatus >> (group * 4U)) & 0xFU) != function)
    {
        return Status_SDH_SDIO_SwitchHighSpeedFail;
    }


    /* Check if card support high speed mode. */
    if (Status_Success != SD_SwitchFunction(SDH_SwitchSet, group, function, cmd6Status))
    {
        return Status_SDH_SDIO_SwitchHighSpeedFail;
    }
    /* In little endian mode is little endian, SD bus byte transferred first is the byte stored in lowest byte
    position in a word which will cause 4 byte's sequence in a word is not consistent with their original
    sequence from card. So the sequence of 4 bytes received in a word should be converted. */
    cmd6Status[3U] = SWAP_WORD_BYTE_SEQUENCE(cmd6Status[3U]);
    cmd6Status[4U] = SWAP_WORD_BYTE_SEQUENCE(cmd6Status[4U]);

    /* According to the "switch function status[bits 511~0]" return by switch command in mode "set function":
         -check if group 1 is successfully changed to function 1 by checking if bits 379~376 equal value 1;
     */
    currentFunctionStatus = ((cmd6Status[3U] & 0xFFFFU) << 8U) | (cmd6Status[4U] >> 24U);
    SDH_MSG("currentFunctionStatus = 0x%x.\r\n",currentFunctionStatus);


    if (((currentFunctionStatus >> (group * 4U)) & 0xFU) != function)
    {
        return Status_SDH_SDIO_SwitchHighSpeedFail;
    }
    return errorstatus;
}

static status_t SD_SetBlockSize(uint32_t blockSize)
{
    status_t errorstatus = Status_Success;
    SDH_CMD_Cfg_Type   SDH_CMD_Cfg_TypeInstance;

    /*!< Set Block Size for SDSC Card,cmd16,no impact on SDHC card */
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SET_BLOCKLEN;
    SDH_CMD_Cfg_TypeInstance.argument = (uint32_t) blockSize;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);

    if(errorstatus != Status_Success)
        goto out;
    else if( SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS )
    {
        errorstatus = Status_SDH_CmdResponseError;
        goto out;
    }

out:
    return errorstatus;
}


static status_t SDH_SDCardInit(uint32_t bus_wide,sd_card_t* card)
{
    status_t errorstatus = Status_Success;
    uint32_t applicationCommand41Argument = SD_OcrVdd33_34Flag | SD_OcrVdd32_33Flag;

    /* reset variables */
    card->flags = 0U;

    SDH_MSG("Go idle in...\r\n");
    errorstatus = SDH_GoIdle();
    if(errorstatus != SD_OK)
        return Status_SDH_GoIdleFailed;
    SDH_MSG("Go idle out...\r\n");

    errorstatus = SD_SendInterfaceCondition();
    if(errorstatus == Status_Success)
    {
        /* SDHC or SDXC card */
        applicationCommand41Argument |= SD_OcrHostCapacitySupportFlag;
        card->flags |= SD_SupportSdhcFlag;
    }
    else
    {
        /* SDSC card */
        errorstatus = SDH_GoIdle();
        if(errorstatus != Status_Success)
            return Status_SDH_GoIdleFailed;
    }
    /* Set card interface condition according to SDHC capability and card's supported interface condition. */
    errorstatus = SD_ApplicationSendOperationCondition(card, applicationCommand41Argument);
    if(errorstatus != Status_Success)
        return Status_SDH_SendApplicationCommandFailed;

    SDH_MSG("\r\n OCR is: 0x%02x .\r\n",card->ocr );
    SDH_MSG("\t SDHC supported[%s] .\r\n",((card->flags & SD_SupportHighCapacityFlag)? "YES" : "NO" ) );

    errorstatus = SD_AllSendCid(card);
    if(errorstatus != Status_Success)
        return Status_SDH_AllSendCidFailed;

    SDH_MSG("\r\n CID is: 0x%02x-0x%02x-0x%02x-0x%02x.\r\n",
            card->rawCid[0],card->rawCid[1],card->rawCid[2],card->rawCid[3]);
    SDH_MSG("\t manufacturerID is: 0x%02x.\r\n",card->cid.manufacturerID);
    SDH_MSG("\t applicationID is: %c%c.\r\n",(card->cid.applicationID)>>8,card->cid.applicationID);
    SDH_MSG("\t productName is: %c%c%c%c%c.\r\n",
            card->cid.productName[0],card->cid.productName[1],card->cid.productName[2],card->cid.productName[3],card->cid.productName[4]);
    SDH_MSG("\t manufacturerData is: 0x%02x.\r\n",card->cid.manufacturerData);


    errorstatus = SD_SendRca(card);
    if(errorstatus != Status_Success)
        return Status_SDH_SendRelativeAddressFailed;
    SDH_MSG("\r\n RCA is: 0x%02x.\r\n",card->relativeAddress);

    errorstatus = SD_SendCsd(card);
    if(errorstatus != Status_Success)
        return Status_SDH_SendCsdFailed;
    SDH_MSG("\r\n CSD is: 0x%02x-0x%02x-0x%02x-0x%02x.\r\n",
            card->rawCsd[0],card->rawCsd[1],card->rawCsd[2],card->rawCsd[3]);
    SDH_MSG("\t CSD Version is: %s .\r\n",card->csd.csdStructure ? "csd version 2.0" : "csd version 1.0");
    SDH_MSG("\t blockLen=%d, blockCounter=%d, CardSize is %d[MBytes].\r\n",card->blockSize,card->blockCount,(card->blockCount)>>11 );

    errorstatus = SD_SelectCard(card,ENABLE);
    if(errorstatus != Status_Success)
        return Status_SDH_SelectCardFailed;


    errorstatus = SD_SendScr(card);
    if(errorstatus != Status_Success)
        return Status_SDH_SendScrFailed;

    SDH_MSG("\r\n SCR is: 0x%x-0x%x.\r\n",card->rawScr[0],card->rawScr[1]);
    SDH_MSG("\t SD Spec Version is: [0x%02x]%s.\r\n",card->version,
            (card->version&SD_SpecificationVersion3_0) ? "V3.0" : ((card->version&SD_SpecificationVersion2_0) ? "V2.0" : ((card->version&SD_SpecificationVersion1_1) ? "V1.1" : "V1.0")));
    SDH_MSG("\t Erased bit is %d.\r\n", (card->scr.flags & SD_ScrDataStatusAfterErase)  );
    SDH_MSG("\t 4-line supported[%s].\r\n",((card->flags & SD_Support4BitWidthFlag)? "YES" : "NO" ) );
    SDH_MSG("\t SetBlockCountCmd supported[%s].\r\n",  ((card->flags & SD_SupportSetBlockCountCmd)? "YES" : "NO" ) );

    if(card->flags & SD_Support4BitWidthFlag)
        errorstatus = SD_SetDataBusWidth(card,(SDH_Data_Bus_Width_Type)bus_wide);
    else
        errorstatus = SD_SetDataBusWidth(card,SDH_DATA_BUS_WIDTH_1BIT);

    if(errorstatus != Status_Success)
        return Status_SDH_SetDataBusWidthFailed;


    errorstatus = SD_SendSsr(card);
    if(errorstatus != Status_Success)
        return Status_SDH_SendSsrFailed;
    SDH_MSG("\r\n SSR[0] is: 0x%x.\r\n",card->rawSsr[0]);
    SDH_MSG("\t Current is %d-line mode.\r\n",(card->rawSsr[0]&0x80) ? 4 : 1);

    errorstatus = SD_SetBlockSize(SDH_DEFAULT_BLOCK_SIZE);
    if(errorstatus != Status_Success)
        return  Status_SDH_SetCardBlockSizeFailed;
    //SD_SelectFunction(SDH_GroupTimingMode,SDH_TimingSDR25HighSpeedMode);

    return errorstatus;
}
/**
  * @brief  Initializes the SD card device.
  * @retval SD status
  */
status_t SDH_Init(uint32_t bus_wide,sd_card_t* pOutCardInfo)
{
    pSDCardInfo = pOutCardInfo;

    SDH_INT_Init();

    /* reset SDH controller*/
    SDH_Reset();

    SDH_HostInit();

    if(pOutCardInfo==NULL){
        return Status_InvalidArgument;
    }else{
        return SDH_SDCardInit(bus_wide,pOutCardInfo);
    }
}

/**
  * @brief  Allows to erase memory area specified for the given card.
  * @param  startaddr: the start address.
  * @param  endaddr: the end address.
  * @retval SD_Error: SD Card Error code.
  */
status_t SD_Erase(uint32_t startaddr, uint32_t endaddr)
{
    status_t errorstatus = Status_Success;
    uint8_t cardstate = 0;

    /* SDSC card uses byte unit address*/
    if( !(pSDCardInfo->flags & SD_SupportHighCapacityFlag) )
    {
        startaddr *= 512;
        endaddr *= 512;
    }

    /*!< Send CMD32 SD_ERASE_GRP_START with argument as addr  */
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SD_ERASE_GRP_START;
    SDH_CMD_Cfg_TypeInstance.argument = startaddr;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);
    if(errorstatus != Status_Success)
        goto out;
    else if( SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS )
    {
        errorstatus = Status_SDH_CmdResponseError;
        goto out;
    }

    /*!< Send CMD33 SD_ERASE_GRP_END with argument as addr  */
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SD_ERASE_GRP_END;
    SDH_CMD_Cfg_TypeInstance.argument = endaddr;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);
    if(errorstatus != Status_Success)
        goto out;
    else if( SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS )
    {
        errorstatus = Status_SDH_CmdResponseError;
        goto out;
    }

    /*!< Send CMD38 ERASE */
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_ERASE;
    SDH_CMD_Cfg_TypeInstance.argument = 0;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1B;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);
    if(errorstatus != Status_Success)
        goto out;
    else if( SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS )
    {
        errorstatus = Status_SDH_CmdResponseError;
        goto out;
    }

    /*!< Wait till the card is in programming state */
    errorstatus = IsCardProgramming(&cardstate);
    while ((errorstatus == SD_OK) && ((SD_CARD_PROGRAMMING == cardstate) || (SD_CARD_RECEIVING == cardstate)))
    {
        errorstatus = IsCardProgramming(&cardstate);
    }

out:
    return errorstatus;
}
static status_t WaitInProgramming(void)
{
    uint8_t cardstate = 0;
    status_t errorstatus = Status_Success;
    //uint32_t maxdelay = 0;
    //maxdelay = 120000/(SDH_CLK_SRC/SDH_CLK_TRANSFER);

    //while(maxdelay--){}
    /*!< Wait till the card is in programming state */
    errorstatus = IsCardProgramming(&cardstate);
    while ((errorstatus == Status_Success) && ((SD_CARD_PROGRAMMING == cardstate) || (SD_CARD_RECEIVING == cardstate)))
    {
        errorstatus = IsCardProgramming(&cardstate);
    }

    return errorstatus;
}
/*check sd card state*/
static status_t IsCardProgramming(uint8_t* pstatus)
{
    status_t errorstatus = Status_Success;

    /*cmd13 addressed card send its status*/
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SEND_STATUS;
    SDH_CMD_Cfg_TypeInstance.argument = (uint32_t) (pSDCardInfo->relativeAddress) << 16;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    errorstatus = SDH_SendCardCommand(&SDH_CMD_Cfg_TypeInstance);
    if(errorstatus != Status_Success)
        goto out;
    else if( SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS )
    {
        errorstatus = Status_SDH_CmdResponseError;
        goto out;
    }
    /*!< Find out card status */
    *pstatus = (uint8_t) ((SDH_CMD_Cfg_TypeInstance.response[0] >> 9) & 0x0000000F);   //status[12:9] :cardstate

out:
    return(errorstatus);
}
static status_t SDH_CardTransferNonBlocking(SDH_DMA_Cfg_Type* dmaCfg,SDH_Trans_Cfg_Type* transfer)
{
    status_t errorstatus = Status_Success;
    SDH_Stat_Type stat = SDH_STAT_SUCCESS;

    SDH_CMD_Cfg_Type* cmdCfg = transfer->cmdCfg;

    stat = SDH_TransferNonBlocking(&SDH_DMA_Cfg_TypeInstance, &SDH_Trans_Cfg_TypeInstance);

    if(stat != SDH_STAT_SUCCESS)
    {
        return Status_SDH_TransferFailed;
    }

    errorstatus = SDH_SendCardCommand(cmdCfg);
    if(errorstatus != Status_Success)
        return errorstatus;
    else if( SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS )
    {
        return Status_SDH_CmdResponseError;
    }

    return errorstatus;
}
/**
  * @brief  Allows to read blocks from a specified address  in a card.  The Data
  *         transfer can be managed by DMA mode or Polling mode. //?????
  * @note   This operation should be followed by two functions to check if the
  *         DMA Controller and SD Card status.     //dma????????????
  *          - SD_ReadWaitOperation(): this function insure that the DMA
  *            controller has finished all data transfer.
  *          - SD_GetStatus(): to check that the SD Card has finished the
  *            data transfer and it is ready for data.
  * @param  readbuff: pointer to the buffer that will contain the received data.
  * @param  ReadAddr: Address from where data are to be read.
  * @param  BlockSize: the SD card Data block size. The Block size should be 512.
  * @param  NumberOfBlocks: number of blocks to be read.
  * @retval SD_Error: SD Card Error code.
  */
status_t SDH_BlockReadMultiBlocks(uint8_t* readbuff, uint32_t ReadAddr, uint16_t BlockSize, uint32_t NumberOfBlocks)
{
    status_t errorstatus = Status_Success;
    SDH_Stat_Type stat = SDH_STAT_SUCCESS;
    /* SDSC card uses byte unit address*/
    if( !(pSDCardInfo->flags & SD_SupportHighCapacityFlag) )
    {
        BlockSize = 512;
        ReadAddr *= 512;
    }
    /*!< Set Block Size for SDSC Card,cmd16,no impact on SDHC card */
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SET_BLOCKLEN;
    SDH_CMD_Cfg_TypeInstance.argument = (uint32_t) BlockSize;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);
    stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
    if(stat != SDH_STAT_SUCCESS)
    {
        return Status_SDH_CmdResponseError;
    }
    else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS)
    {
        return Status_SDH_CmdResponseError;
    }

    /*set cmd parameter for READ_MULTIPLE_BLOCK*/
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_READ_MULT_BLOCK;
    //SDH_CMD_Cfg_TypeInstance.index = SD_CMD_READ_SINGLE_BLOCK;
    SDH_CMD_Cfg_TypeInstance.argument =  (uint32_t)ReadAddr;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;
    /*set data parameter for READ_MULTIPLE_BLOCK*/
    SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = ENABLE;
    if(pSDCardInfo->flags & SD_SupportSetBlockCountCmd){
        SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = ENABLE;
    }else{
        SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
    }
    SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
    SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
    SDH_Data_Cfg_TypeInstance.blockSize = BlockSize;
    SDH_Data_Cfg_TypeInstance.blockCount = NumberOfBlocks;
    SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
    SDH_Data_Cfg_TypeInstance.rxData = (uint32_t*)readbuff;
    SDH_Data_Cfg_TypeInstance.txDataLen = 0;
    SDH_Data_Cfg_TypeInstance.txData = NULL;
    /*set parameters for SDH_DMA_Cfg_TypeInstance*/
    SDH_DMA_Cfg_TypeInstance.dmaMode = SDH_DMA_MODE_ADMA2;
    SDH_DMA_Cfg_TypeInstance.burstSize = SDH_BURST_SIZE_64_BYTES;
    SDH_DMA_Cfg_TypeInstance.fifoThreshold = SDH_FIFO_THRESHOLD_256_BYTES;
    SDH_DMA_Cfg_TypeInstance.admaEntries = (uint32_t*)adma2Entries;
    SDH_DMA_Cfg_TypeInstance.maxEntries = sizeof(adma2Entries)/sizeof(adma2Entries[0]);

    stat = SDH_TransferBlocking(&SDH_DMA_Cfg_TypeInstance, &SDH_Trans_Cfg_TypeInstance);

    if(stat != SDH_STAT_SUCCESS)
    {
        return Status_SDH_TransferFailed;
    }
    return(errorstatus);
}
status_t SDH_ReadMultiBlocks(uint8_t* readbuff, uint32_t ReadAddr, uint16_t BlockSize, uint32_t NumberOfBlocks)
{
    status_t errorstatus = Status_Success;

    /* SDSC card uses byte unit address*/
    if( !(pSDCardInfo->flags & SD_SupportHighCapacityFlag) )
    {
        BlockSize = 512;
        ReadAddr *= 512;
    }
    SDH_MSG("Read-->IN, read %d blocks from %d with buffer 0x%p. \r\n",NumberOfBlocks,ReadAddr,readbuff);

    /*set cmd parameter for READ_MULTIPLE_BLOCK*/
    if(NumberOfBlocks<=1)
        SDH_CMD_Cfg_TypeInstance.index = SD_CMD_READ_SINGLE_BLOCK;
    else
        SDH_CMD_Cfg_TypeInstance.index = SD_CMD_READ_MULT_BLOCK;

    SDH_CMD_Cfg_TypeInstance.argument =  (uint32_t)ReadAddr;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;
    /*set data parameter for READ_MULTIPLE_BLOCK*/
    if(NumberOfBlocks<=1){
        SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = DISABLE;
    }else{
        SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = ENABLE;
        if(pSDCardInfo->flags & SD_SupportSetBlockCountCmd){
            SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = ENABLE;
        }else{
            SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
        }
    }

    SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
    SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
    SDH_Data_Cfg_TypeInstance.blockSize = BlockSize;
    SDH_Data_Cfg_TypeInstance.blockCount = NumberOfBlocks;
    SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
    SDH_Data_Cfg_TypeInstance.rxData = (uint32_t*)readbuff;
    SDH_Data_Cfg_TypeInstance.txDataLen = 0;
    SDH_Data_Cfg_TypeInstance.txData = NULL;
    /*set parameters for SDH_DMA_Cfg_TypeInstance*/
    SDH_DMA_Cfg_TypeInstance.dmaMode = SDH_DMA_MODE_ADMA2;
    SDH_DMA_Cfg_TypeInstance.burstSize = SDH_BURST_SIZE_64_BYTES;
    SDH_DMA_Cfg_TypeInstance.fifoThreshold = SDH_FIFO_THRESHOLD_256_BYTES;
    SDH_DMA_Cfg_TypeInstance.admaEntries = (uint32_t*)adma2Entries;
    SDH_DMA_Cfg_TypeInstance.maxEntries = sizeof(adma2Entries)/sizeof(adma2Entries[0]);

    errorstatus = SDH_CardTransferNonBlocking(&SDH_DMA_Cfg_TypeInstance, &SDH_Trans_Cfg_TypeInstance);

    if(errorstatus != Status_Success)
    {
        goto out;
    }

    /*wait for Xfer status. might pending here in multi-task OS*/
    SDH_WaitStatus = SD_WAITING;
    SDH_ITConfig(SDH_INT_DATA_COMPLETED|SDH_INT_DATA_ERRORS|SDH_INT_DMA_ERROR|SDH_INT_AUTO_CMD12_ERROR,ENABLE);
    while(SDH_WaitStatus == SD_WAITING) {}

    SDH_ITConfig(SDH_INT_DATA_COMPLETED|SDH_INT_DATA_ERRORS|SDH_INT_DMA_ERROR|SDH_INT_AUTO_CMD12_ERROR,DISABLE);

    if(SDH_WaitStatus != SD_OK)
    {
        errorstatus = Status_SDH_TransferFailed;
        SDH_WaitStatus = SD_WAITING;
        goto out;
    }
    else
    {
        SDH_WaitStatus = SD_WAITING;
    }

    SDH_MSG("Read-->OUT, read %d blocks from %d with buffer 0x%p. \r\n",NumberOfBlocks,ReadAddr,readbuff);

out:
    return(errorstatus);
}

status_t SDH_BlockWriteMultiBlocks(uint8_t* writebuff, uint32_t WriteAddr, uint16_t BlockSize, uint32_t NumberOfBlocks)
{
    status_t errorstatus = Status_Success;
    SDH_Stat_Type stat = SDH_STAT_SUCCESS;
    /* SDSC card uses byte unit address*/
    if( !(pSDCardInfo->flags & SD_SupportHighCapacityFlag) )
    {
        BlockSize = 512;
        WriteAddr *= 512;
    }
    /*!< Set Block Size for SDSC Card,cmd16,no impact on SDHC card */
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SET_BLOCKLEN;
    SDH_CMD_Cfg_TypeInstance.argument = (uint32_t) BlockSize;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;

    SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);
    stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
    if(stat != SDH_STAT_SUCCESS)
    {
        return Status_SDH_CmdResponseError;
    }
    else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS)
    {
        return Status_SDH_CmdResponseError;
    }

    /*set cmd parameter for SD_CMD_WRITE_MULT_BLOCK*/
    SDH_CMD_Cfg_TypeInstance.index = SD_CMD_WRITE_MULT_BLOCK;
    SDH_CMD_Cfg_TypeInstance.argument =  (uint32_t)WriteAddr;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;
    /*set data parameter for WRITE_MULTIPLE_BLOCK*/
    SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = ENABLE;
    if(pSDCardInfo->flags & SD_SupportSetBlockCountCmd){
        SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = ENABLE;
    }else{
        SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
    }
    SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
    SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
    SDH_Data_Cfg_TypeInstance.blockSize = BlockSize;
    SDH_Data_Cfg_TypeInstance.blockCount = NumberOfBlocks;
    SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
    SDH_Data_Cfg_TypeInstance.rxData = NULL;
    SDH_Data_Cfg_TypeInstance.txDataLen = 0;
    SDH_Data_Cfg_TypeInstance.txData = (uint32_t*)writebuff;
    /*set parameters for SDH_DMA_Cfg_TypeInstance*/
    SDH_DMA_Cfg_TypeInstance.dmaMode = SDH_DMA_MODE_ADMA2;
    SDH_DMA_Cfg_TypeInstance.burstSize = SDH_BURST_SIZE_64_BYTES;
    SDH_DMA_Cfg_TypeInstance.fifoThreshold = SDH_FIFO_THRESHOLD_256_BYTES;
    SDH_DMA_Cfg_TypeInstance.admaEntries = (uint32_t*)adma2Entries;
    SDH_DMA_Cfg_TypeInstance.maxEntries = sizeof(adma2Entries)/sizeof(adma2Entries[0]);

    stat = SDH_TransferBlocking(&SDH_DMA_Cfg_TypeInstance, &SDH_Trans_Cfg_TypeInstance);
    if(stat != SDH_STAT_SUCCESS)
    {
        return Status_SDH_TransferFailed;
    }

    errorstatus = WaitInProgramming();

    return(errorstatus);
}
status_t SDH_WriteMultiBlocks(uint8_t* writebuff, uint32_t WriteAddr, uint16_t BlockSize, uint32_t NumberOfBlocks)
{
    status_t errorstatus = Status_Success;

    if((pSDCardInfo!=NULL)&&(!(pSDCardInfo->flags & SD_SupportHighCapacityFlag))){
        /* It's SDCS card,SDSC card uses byte unit address*/
        BlockSize = 512;
        WriteAddr *= 512;
    }

    SDH_MSG("Write-->IN, write %d blocks to %d with buffer 0x%p. \r\n",NumberOfBlocks,WriteAddr,writebuff);
    /*set cmd parameter for SD_CMD_WRITE_MULT_BLOCK*/
    if(NumberOfBlocks<=1)
        SDH_CMD_Cfg_TypeInstance.index = SD_CMD_WRITE_SINGLE_BLOCK;
    else
        SDH_CMD_Cfg_TypeInstance.index = SD_CMD_WRITE_MULT_BLOCK;

    SDH_CMD_Cfg_TypeInstance.argument =  (uint32_t)WriteAddr;
    SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
    SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
    SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;
    /*set data parameter for WRITE_MULTIPLE_BLOCK*/
    if(NumberOfBlocks<=1){
        SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = DISABLE;
    }else{
        SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = ENABLE;
        if(pSDCardInfo->flags & SD_SupportSetBlockCountCmd){
            SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = ENABLE;
        }else{
            SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
        }
    }

    SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
    SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
    SDH_Data_Cfg_TypeInstance.blockSize = BlockSize;
    SDH_Data_Cfg_TypeInstance.blockCount = NumberOfBlocks;
    SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
    SDH_Data_Cfg_TypeInstance.rxData = NULL;
    SDH_Data_Cfg_TypeInstance.txDataLen = 0;
    SDH_Data_Cfg_TypeInstance.txData = (uint32_t*)writebuff;
    /*set parameters for SDH_DMA_Cfg_TypeInstance*/
    SDH_DMA_Cfg_TypeInstance.dmaMode = SDH_DMA_MODE_ADMA2;
    SDH_DMA_Cfg_TypeInstance.burstSize = SDH_BURST_SIZE_64_BYTES;
    SDH_DMA_Cfg_TypeInstance.fifoThreshold = SDH_FIFO_THRESHOLD_256_BYTES;
    SDH_DMA_Cfg_TypeInstance.admaEntries = (uint32_t*)adma2Entries;
    SDH_DMA_Cfg_TypeInstance.maxEntries = sizeof(adma2Entries)/sizeof(adma2Entries[0]);

    errorstatus = SDH_CardTransferNonBlocking(&SDH_DMA_Cfg_TypeInstance, &SDH_Trans_Cfg_TypeInstance);

    if(errorstatus != Status_Success)
    {
        return errorstatus;
    }

    /*wait for Xfer status. might pending here in multi-task OS*/
    SDH_WaitStatus = SD_WAITING;
    SDH_ITConfig(SDH_INT_DATA_COMPLETED|SDH_INT_DATA_ERRORS|SDH_INT_DMA_ERROR|SDH_INT_AUTO_CMD12_ERROR,ENABLE);
    while(SDH_WaitStatus == SD_WAITING) {}

    SDH_ITConfig(SDH_INT_DATA_COMPLETED|SDH_INT_DATA_ERRORS|SDH_INT_DMA_ERROR|SDH_INT_AUTO_CMD12_ERROR,DISABLE);

    if(SDH_WaitStatus != SD_OK)
    {
        errorstatus = Status_SDH_TransferFailed;
        SDH_WaitStatus = SD_WAITING;

        goto out;
    }
    else
    {
        SDH_WaitStatus = SD_WAITING;
        errorstatus = WaitInProgramming();
    }
    SDH_MSG("Write-->OUT, write %d blocks to %d with buffer 0x%p. \r\n",NumberOfBlocks,WriteAddr,writebuff);

out:
    return(errorstatus);
}
