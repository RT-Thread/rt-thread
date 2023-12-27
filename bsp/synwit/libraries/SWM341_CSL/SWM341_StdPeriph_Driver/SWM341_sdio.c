/******************************************************************************************************************************************
* 文件名称: SWM341_sdio.c
* 功能说明: SWM341单片机的SDIO接口驱动库
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项: 为了通用性、兼容性、易用性，只支持以512字节为单位的读写
* 版本日期: V1.1.0      2017年10月25日
* 升级记录:
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology
*******************************************************************************************************************************************/
#include "SWM341.h"
#include "SWM341_sdio.h"


SD_CardInfo SD_cardInfo;

/******************************************************************************************************************************************
* 函数名称: SDIO_Init()
* 功能说明: SDIO读写SD卡初始化，初始化成高速4线模式、读写以512字节大小进行
* 输    入: uint32_t freq         SDIO_CLK时钟频率
* 输    出: uint32_t              SD_RES_OK 操作成功    SD_RES_ERR 操作失败    SD_RES_TIMEOUT 操作超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SDIO_Init(uint32_t freq)
{
    uint32_t res;
    uint32_t resp, resps[4];

    SYS->CLKSEL &= ~SYS_CLKSEL_SDIO_Msk;
    if(SystemCoreClock > 80000000)      //SDIO时钟需要小于52MHz
        SYS->CLKSEL |= (2 << SYS_CLKSEL_SDIO_Pos);  //SDCLK = SYSCLK / 4
    else
        SYS->CLKSEL |= (0 << SYS_CLKSEL_SDIO_Pos);  //SDCLK = SYSCLK / 2

    SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_SDIO_Pos);

    SDIO->CR2 = (1 << SDIO_CR2_RSTALL_Pos);

    SDIO->CR1 = (1 << SDIO_CR1_CDSRC_Pos) |
                (0 << SDIO_CR1_8BIT_Pos)  |
                (0 << SDIO_CR1_4BIT_Pos)  |
                (1 << SDIO_CR1_PWRON_Pos) |
                (7 << SDIO_CR1_VOLT_Pos);

    SDIO->CR2 = (1 << SDIO_CR2_CLKEN_Pos) |
                (1 << SDIO_CR2_SDCLKEN_Pos) |
                (calcSDCLKDiv(100000) << SDIO_CR2_SDCLKDIV_Pos) |
                (0xC << SDIO_CR2_TIMEOUT_Pos);      // 2**25 SDIO_CLK

    while((SDIO->CR2 & SDIO_CR2_CLKRDY_Msk) == 0);

    for(int i = 0; i < CyclesPerUs * 10; i++) __NOP();

    SDIO->IM = 0xFFFFFFFF;


    SDIO_SendCmd(SD_CMD_GO_IDLE_STATE, 0x00, SD_RESP_NO, 0);                //CMD0: GO_IDLE_STATE

    res = SDIO_SendCmd(SD_CMD_SEND_IF_COND, 0x1AA, SD_RESP_32b, &resp);     //CMD8: SEND_IF_COND, 检测工作电压、检测是否支持SD 2.0
    if(res != SD_RES_OK)
        return res;

    if(resp == 0x1AA) SD_cardInfo.CardType = SDIO_STD_CAPACITY_SD_CARD_V2_0;
    else              SD_cardInfo.CardType = SDIO_STD_CAPACITY_SD_CARD_V1_1;

    do                                                                      //ACMD41: SD_CMD_SD_APP_OP_COND
    {
        res = SDIO_SendCmd(SD_CMD_APP_CMD, 0x00, SD_RESP_32b, &resp);
        if(res != SD_RES_OK)
            return res;

        if((resp & SD_CS_APP_CMD) == 0) return SD_RES_ERR;

        if(SD_cardInfo.CardType == SDIO_STD_CAPACITY_SD_CARD_V2_0)
            SDIO_SendCmd(SD_CMD_SD_APP_OP_COND, 0x80100000|0x40000000, SD_RESP_32b, &resp);
        else
            SDIO_SendCmd(SD_CMD_SD_APP_OP_COND, 0x80100000|0x00000000, SD_RESP_32b, &resp);
    } while(((resp >> 31) & 0x01) == 0);        //上电没完成时resp[31] == 0

    if(((resp >> 30) & 0x01) == 1) SD_cardInfo.CardType = SDIO_HIGH_CAPACITY_SD_CARD;


    SDIO_SendCmd(SD_CMD_ALL_SEND_CID, 0x00, SD_RESP_128b, resps);           //CMD2: SD_CMD_ALL_SEND_CID，获取CID

    parseCID(resps);


    SDIO_SendCmd(SD_CMD_SET_REL_ADDR, 0x00, SD_RESP_32b, &resp);            //CMD3: SD_CMD_SET_REL_ADDR，设置RCA

    SD_cardInfo.RCA = resp >> 16;


    SDIO_SendCmd(SD_CMD_SEND_CSD, SD_cardInfo.RCA << 16, SD_RESP_128b, resps);  //CMD9: SD_CMD_SEND_CSD，获取CSD

    parseCSD(resps);

    if(SD_cardInfo.CardBlockSize < 0x200) return SD_RES_ERR;    //本驱动只支持以512字节为单位的读写，所以最大读写单位必须不小于512


    SDIO->CR2 &= ~(SDIO_CR2_SDCLKEN_Msk | SDIO_CR2_SDCLKDIV_Msk);
    SDIO->CR2 |= (1 << SDIO_CR2_SDCLKEN_Pos) |
                 (calcSDCLKDiv(freq) << SDIO_CR2_SDCLKDIV_Pos); //初始化完成，SDCLK切换到高速


    SDIO_SendCmd(SD_CMD_SEL_DESEL_CARD, SD_cardInfo.RCA << 16, SD_RESP_32b_busy, &resp);    //CMD7: 选中卡，从Standy模式进入Transfer模式
    SDIO->IF = SDIO_IF_TRXDONE_Msk;

    SDIO_SendCmd(SD_CMD_APP_CMD, SD_cardInfo.RCA << 16, SD_RESP_32b, &resp);

    SDIO_SendCmd(SD_CMD_APP_SD_SET_BUSWIDTH, SD_BUSWIDTH_4b, SD_RESP_32b, &resp);   //切换成4位总线模式

    SDIO->CR1 |= (1 << SDIO_CR1_4BIT_Pos);


    SDIO_SendCmd(SD_CMD_SET_BLOCKLEN, 512, SD_RESP_32b, &resp);     //固定块大小位512字节

    SD_cardInfo.CardBlockSize = 512;

    SDIO->BLK = 512;

    return SD_RES_OK;
}

/******************************************************************************************************************************************
* 函数名称: SDIO_BlockWrite()
* 功能说明: 向SD卡写入数据
* 输    入: uint32_t block_addr       SD卡块地址，每块512字节
*           uint32_t buff[]         要写入的数据
* 输    出: uint32_t              SD_RES_OK 操作成功    SD_RES_ERR 操作失败    SD_RES_TIMEOUT 操作超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SDIO_BlockWrite(uint32_t block_addr, uint32_t buff[])
{
    uint32_t res, i;
    uint32_t addr, resp;

    if(SD_cardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)  addr = block_addr;
    else                                                    addr = block_addr * 512;

    res = SDIO_SendCmdWithData(SD_CMD_WRITE_SINGLE_BLOCK, addr, SD_RESP_32b, &resp, 0, 1);
    if(res != SD_RES_OK)
        return res;

    while((SDIO->IF & SDIO_IF_BUFWRRDY_Msk) == 0) __NOP();
    SDIO->IF = SDIO_IF_BUFWRRDY_Msk;

    for(i = 0; i < 512/4; i++) SDIO->DATA = buff[i];

    while((SDIO->IF & SDIO_IF_TRXDONE_Msk) == 0) __NOP();
    SDIO->IF = SDIO_IF_TRXDONE_Msk;

    return SD_RES_OK;
}

/******************************************************************************************************************************************
* 函数名称: SDIO_MultiBlockWrite()
* 功能说明: 向SD卡写入多块数据
* 输    入: uint32_t block_addr       SD卡块地址，每块512字节
*           uint16_t block_cnt      要写入的块数
*           uint32_t buff[]         要写入的数据
* 输    出: uint32_t              SD_RES_OK 操作成功    SD_RES_ERR 操作失败    SD_RES_TIMEOUT 操作超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SDIO_MultiBlockWrite(uint32_t block_addr, uint16_t block_cnt, uint32_t buff[])
{
    uint32_t res, i, j;
    uint32_t addr, resp;

    if(SD_cardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)  addr = block_addr;
    else                                                    addr = block_addr * 512;

    res = SDIO_SendCmdWithData(SD_CMD_WRITE_MULT_BLOCK, addr, SD_RESP_32b, &resp, 0, block_cnt);
    if(res != SD_RES_OK)
        return res;

    for(i = 0; i < block_cnt; i++)
    {
        while((SDIO->IF & SDIO_IF_BUFWRRDY_Msk) == 0) __NOP();
        SDIO->IF = SDIO_IF_BUFWRRDY_Msk;

        for(j = 0; j < 512/4; j++) SDIO->DATA = buff[i*(512/4) + j];
    }

    while((SDIO->IF & SDIO_IF_TRXDONE_Msk) == 0) __NOP();
    SDIO->IF = SDIO_IF_TRXDONE_Msk;

    return SD_RES_OK;
}

/******************************************************************************************************************************************
* 函数名称: SDIO_DMABlockWrite()
* 功能说明: 通过DMA向SD卡写入多块数据
* 输    入: uint32_t block_addr       SD卡块地址，每块512字节
*           uint16_t block_cnt      要写入的块数
*           uint32_t buff[]         要写入的数据
* 输    出: uint32_t              SD_RES_OK 操作成功    SD_RES_ERR 操作失败    SD_RES_TIMEOUT 操作超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SDIO_DMABlockWrite(uint32_t block_addr, uint16_t block_cnt, uint32_t buff[])
{
    uint32_t res;
    uint32_t addr, resp;

    if(SD_cardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)  addr = block_addr;
    else                                                    addr = block_addr * 512;

    SDIO->DMA_MEM_ADDR = (uint32_t) buff;

    res = SDIO_SendCmdWithDataByDMA(SD_CMD_WRITE_MULT_BLOCK, addr, SD_RESP_32b, &resp, 0, block_cnt);
    if(res != SD_RES_OK)
        return res;

    while((SDIO->IF & SDIO_IF_TRXDONE_Msk) == 0) __NOP();
    SDIO->IF = SDIO_IF_TRXDONE_Msk;

    return SD_RES_OK;
}

/******************************************************************************************************************************************
* 函数名称: SDIO_BlockRead()
* 功能说明: 从SD卡读出数据
* 输    入: uint32_t block_addr       SD卡块地址，每块512字节
*           uint32_t buff[]         读出的数据
* 输    出: uint32_t              SD_RES_OK 操作成功    SD_RES_ERR 操作失败    SD_RES_TIMEOUT 操作超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SDIO_BlockRead(uint32_t block_addr, uint32_t buff[])
{
    uint32_t res, i;
    uint32_t addr, resp;

    if(SD_cardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)  addr = block_addr;
    else                                                    addr = block_addr * 512;

    res = SDIO_SendCmdWithData(SD_CMD_READ_SINGLE_BLOCK, addr, SD_RESP_32b, &resp, 1, 1);
    if(res != SD_RES_OK)
        return res;

    while((SDIO->IF & SDIO_IF_BUFRDRDY_Msk) == 0) __NOP();
    SDIO->IF = SDIO_IF_BUFRDRDY_Msk;

    for(i = 0; i < 512/4; i++) buff[i] = SDIO->DATA;

    while((SDIO->IF & SDIO_IF_TRXDONE_Msk) == 0) __NOP();
    SDIO->IF = SDIO_IF_TRXDONE_Msk;

    return SD_RES_OK;
}

/******************************************************************************************************************************************
* 函数名称: SDIO_MultiBlockRead()
* 功能说明: 从SD卡读出多块数据
* 输    入: uint32_t block_addr       SD卡块地址，每块512字节
*           uint16_t block_cnt      要读出的块数
*           uint32_t buff[]         读出的数据
* 输    出: uint32_t              SD_RES_OK 操作成功    SD_RES_ERR 操作失败    SD_RES_TIMEOUT 操作超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SDIO_MultiBlockRead(uint32_t block_addr, uint16_t block_cnt, uint32_t buff[])
{
    uint32_t res, i, j;
    uint32_t addr, resp;

    if(SD_cardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)  addr = block_addr;
    else                                                    addr = block_addr * 512;

    res = SDIO_SendCmdWithData(SD_CMD_READ_MULT_BLOCK, addr, SD_RESP_32b, &resp, 1, block_cnt);
    if(res != SD_RES_OK)
        return res;

    for(i = 0; i < block_cnt; i++)
    {
        while((SDIO->IF & SDIO_IF_BUFRDRDY_Msk) == 0) __NOP();
        SDIO->IF = SDIO_IF_BUFRDRDY_Msk;

        for(j = 0; j < 512/4; j++) buff[i*(512/4) + j] = SDIO->DATA;
    }

    while((SDIO->IF & SDIO_IF_TRXDONE_Msk) == 0) __NOP();
    SDIO->IF = SDIO_IF_TRXDONE_Msk;

    return SD_RES_OK;
}

/******************************************************************************************************************************************
* 函数名称: SDIO_DMABlockRead()
* 功能说明: 通过DMA从SD卡读出多块数据
* 输    入: uint32_t block_addr       SD卡块地址，每块512字节
*           uint16_t block_cnt      要读出的块数
*           uint32_t buff[]         读出的数据
* 输    出: uint32_t              SD_RES_OK 操作成功    SD_RES_ERR 操作失败    SD_RES_TIMEOUT 操作超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SDIO_DMABlockRead(uint32_t block_addr, uint16_t block_cnt, uint32_t buff[])
{
    uint32_t res;
    uint32_t addr, resp;

    if(SD_cardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)  addr = block_addr;
    else                                                    addr = block_addr * 512;

    SDIO->DMA_MEM_ADDR = (uint32_t)buff;

    res = SDIO_SendCmdWithDataByDMA(SD_CMD_READ_MULT_BLOCK, addr, SD_RESP_32b, &resp, 1, block_cnt);
    if(res != SD_RES_OK)
        return res;

    while((SDIO->IF & SDIO_IF_TRXDONE_Msk) == 0) __NOP();
    SDIO->IF = SDIO_IF_TRXDONE_Msk;

    return SD_RES_OK;
}

/******************************************************************************************************************************************
* 函数名称: _SDIO_SendCmd()
* 功能说明: SDIO向SD卡发送命令
* 输    入: uint32_t cmd          命令索引
*           uint32_t arg            命令参数
*           uint32_t resp_type      响应类型，取值SD_RESP_NO、SD_RESP_32b、SD_RESP_128b、SD_RESP_32b_busy
*           uint32_t *resp_data     响应内容
*           uint32_t have_data      是否有数据传输
*           uint32_t data_read      1 读SD卡    0 写SD卡
*           uint16_t block_cnt      读写块个数
*           uint32_t use_dma        1 使用DMA搬运数据
* 输    出: uint32_t              SD_RES_OK 操作成功    SD_RES_ERR 操作失败    SD_RES_TIMEOUT 操作超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t _SDIO_SendCmd(uint32_t cmd, uint32_t arg, uint32_t resp_type, uint32_t *resp_data, uint32_t have_data, uint32_t data_read, uint16_t block_cnt, uint32_t use_dma)
{
    SDIO->BLK &= ~SDIO_BLK_COUNT_Msk;
    SDIO->BLK |= (block_cnt << SDIO_BLK_COUNT_Pos);

    SDIO->ARG = arg;
    SDIO->CMD = (cmd             << SDIO_CMD_CMDINDX_Pos)   |
                (0               << SDIO_CMD_CMDTYPE_Pos)   |
                (0               << SDIO_CMD_IDXCHECK_Pos)  |
                (0               << SDIO_CMD_CRCCHECK_Pos)  |
                (resp_type       << SDIO_CMD_RESPTYPE_Pos)  |
                (have_data       << SDIO_CMD_HAVEDATA_Pos)  |
                (data_read       << SDIO_CMD_DIRREAD_Pos)   |
                ((block_cnt > 1) << SDIO_CMD_MULTBLK_Pos)   |
                ((block_cnt > 1) << SDIO_CMD_BLKCNTEN_Pos)  |
                (((cmd == 53) ? 0 : (block_cnt > 1)) << SDIO_CMD_AUTOCMD12_Pos) |
                (use_dma         << SDIO_CMD_DMAEN_Pos);

    while((SDIO->IF & SDIO_IF_CMDDONE_Msk) == 0)
    {
        if(SDIO->IF & SDIO_IF_CMDTIMEOUT_Msk)
        {
            SDIO->IF = SDIO_IF_CMDTIMEOUT_Msk;

            return SD_RES_TIMEOUT;
        }
        else if(SDIO->IF & SDIO_IF_ERROR_Msk)
        {
            SDIO->IF = 0xFFFFFFFF;

            return SD_RES_ERR;
        }
    }
    SDIO->IF = SDIO_IF_CMDDONE_Msk;

    if(resp_type == SD_RESP_32b)
    {
        resp_data[0] = SDIO->RESP[0];
    }
    else if(resp_type == SD_RESP_128b)
    {
        //寄存器中将CID/CSD[127-8]依次存放在了RESP3-0[119-0]，最低位的CRC被丢掉
        //读出数据时调整了顺序，将CID/CSD[127-8]存放在resp_data0-3[127-8]，最低8位填充0x00
        resp_data[0] = (SDIO->RESP[3] << 8) + ((SDIO->RESP[2] >> 24) & 0xFF);
        resp_data[1] = (SDIO->RESP[2] << 8) + ((SDIO->RESP[1] >> 24) & 0xFF);
        resp_data[2] = (SDIO->RESP[1] << 8) + ((SDIO->RESP[0] >> 24) & 0xFF);
        resp_data[3] = (SDIO->RESP[0] << 8) + 0x00;
    }

    return SD_RES_OK;
}


void parseCID(uint32_t CID_Tab[4])
{
    uint8_t tmp = 0;

    /*!< Byte 0 */
    tmp = (uint8_t)((CID_Tab[0] & 0xFF000000) >> 24);
    SD_cardInfo.SD_cid.ManufacturerID = tmp;

    /*!< Byte 1 */
    tmp = (uint8_t)((CID_Tab[0] & 0x00FF0000) >> 16);
    SD_cardInfo.SD_cid.OEM_AppliID = tmp << 8;

    /*!< Byte 2 */
    tmp = (uint8_t)((CID_Tab[0] & 0x000000FF00) >> 8);
    SD_cardInfo.SD_cid.OEM_AppliID |= tmp;

    /*!< Byte 3 */
    tmp = (uint8_t)(CID_Tab[0] & 0x000000FF);
    SD_cardInfo.SD_cid.ProdName1 = tmp << 24;

    /*!< Byte 4 */
    tmp = (uint8_t)((CID_Tab[1] & 0xFF000000) >> 24);
    SD_cardInfo.SD_cid.ProdName1 |= tmp << 16;

    /*!< Byte 5 */
    tmp = (uint8_t)((CID_Tab[1] & 0x00FF0000) >> 16);
    SD_cardInfo.SD_cid.ProdName1 |= tmp << 8;

    /*!< Byte 6 */
    tmp = (uint8_t)((CID_Tab[1] & 0x0000FF00) >> 8);
    SD_cardInfo.SD_cid.ProdName1 |= tmp;

    /*!< Byte 7 */
    tmp = (uint8_t)(CID_Tab[1] & 0x000000FF);
    SD_cardInfo.SD_cid.ProdName2 = tmp;

    /*!< Byte 8 */
    tmp = (uint8_t)((CID_Tab[2] & 0xFF000000) >> 24);
    SD_cardInfo.SD_cid.ProdRev = tmp;

    /*!< Byte 9 */
    tmp = (uint8_t)((CID_Tab[2] & 0x00FF0000) >> 16);
    SD_cardInfo.SD_cid.ProdSN = tmp << 24;

    /*!< Byte 10 */
    tmp = (uint8_t)((CID_Tab[2] & 0x0000FF00) >> 8);
    SD_cardInfo.SD_cid.ProdSN |= tmp << 16;

    /*!< Byte 11 */
    tmp = (uint8_t)(CID_Tab[2] & 0x000000FF);
    SD_cardInfo.SD_cid.ProdSN |= tmp << 8;

    /*!< Byte 12 */
    tmp = (uint8_t)((CID_Tab[3] & 0xFF000000) >> 24);
    SD_cardInfo.SD_cid.ProdSN |= tmp;

    /*!< Byte 13 */
    tmp = (uint8_t)((CID_Tab[3] & 0x00FF0000) >> 16);
    SD_cardInfo.SD_cid.Reserved1 |= (tmp & 0xF0) >> 4;
    SD_cardInfo.SD_cid.ManufactDate = (tmp & 0x0F) << 8;

    /*!< Byte 14 */
    tmp = (uint8_t)((CID_Tab[3] & 0x0000FF00) >> 8);
    SD_cardInfo.SD_cid.ManufactDate |= tmp;
}

void parseCSD(uint32_t CSD_Tab[4])
{
    uint8_t tmp = 0;

    /*!< Byte 0 */
    tmp = (uint8_t)((CSD_Tab[0] & 0xFF000000) >> 24);
    SD_cardInfo.SD_csd.CSDStruct = (tmp & 0xC0) >> 6;
    SD_cardInfo.SD_csd.SysSpecVersion = (tmp & 0x3C) >> 2;
    SD_cardInfo.SD_csd.Reserved1 = tmp & 0x03;

    /*!< Byte 1 */
    tmp = (uint8_t)((CSD_Tab[0] & 0x00FF0000) >> 16);
    SD_cardInfo.SD_csd.TAAC = tmp;

    /*!< Byte 2 */
    tmp = (uint8_t)((CSD_Tab[0] & 0x0000FF00) >> 8);
    SD_cardInfo.SD_csd.NSAC = tmp;

    /*!< Byte 3 */
    tmp = (uint8_t)(CSD_Tab[0] & 0x000000FF);
    SD_cardInfo.SD_csd.MaxBusClkFrec = tmp;

    /*!< Byte 4 */
    tmp = (uint8_t)((CSD_Tab[1] & 0xFF000000) >> 24);
    SD_cardInfo.SD_csd.CardComdClasses = tmp << 4;

    /*!< Byte 5 */
    tmp = (uint8_t)((CSD_Tab[1] & 0x00FF0000) >> 16);
    SD_cardInfo.SD_csd.CardComdClasses |= (tmp & 0xF0) >> 4;
    SD_cardInfo.SD_csd.RdBlockLen = tmp & 0x0F;

    /*!< Byte 6 */
    tmp = (uint8_t)((CSD_Tab[1] & 0x0000FF00) >> 8);
    SD_cardInfo.SD_csd.PartBlockRead = (tmp & 0x80) >> 7;
    SD_cardInfo.SD_csd.WrBlockMisalign = (tmp & 0x40) >> 6;
    SD_cardInfo.SD_csd.RdBlockMisalign = (tmp & 0x20) >> 5;
    SD_cardInfo.SD_csd.DSRImpl = (tmp & 0x10) >> 4;
    SD_cardInfo.SD_csd.Reserved2 = 0; /*!< Reserved */

    if ((SD_cardInfo.CardType == SDIO_STD_CAPACITY_SD_CARD_V1_1) ||
        (SD_cardInfo.CardType == SDIO_STD_CAPACITY_SD_CARD_V2_0))
    {
        SD_cardInfo.SD_csd.DeviceSize = (tmp & 0x03) << 10;

        /*!< Byte 7 */
        tmp = (uint8_t)(CSD_Tab[1] & 0x000000FF);
        SD_cardInfo.SD_csd.DeviceSize |= (tmp) << 2;

        /*!< Byte 8 */
        tmp = (uint8_t)((CSD_Tab[2] & 0xFF000000) >> 24);
        SD_cardInfo.SD_csd.DeviceSize |= (tmp & 0xC0) >> 6;

        SD_cardInfo.SD_csd.MaxRdCurrentVDDMin = (tmp & 0x38) >> 3;
        SD_cardInfo.SD_csd.MaxRdCurrentVDDMax = (tmp & 0x07);

        /*!< Byte 9 */
        tmp = (uint8_t)((CSD_Tab[2] & 0x00FF0000) >> 16);
        SD_cardInfo.SD_csd.MaxWrCurrentVDDMin = (tmp & 0xE0) >> 5;
        SD_cardInfo.SD_csd.MaxWrCurrentVDDMax = (tmp & 0x1C) >> 2;
        SD_cardInfo.SD_csd.DeviceSizeMul = (tmp & 0x03) << 1;
        /*!< Byte 10 */
        tmp = (uint8_t)((CSD_Tab[2] & 0x0000FF00) >> 8);
        SD_cardInfo.SD_csd.DeviceSizeMul |= (tmp & 0x80) >> 7;

        SD_cardInfo.CardCapacity = (SD_cardInfo.SD_csd.DeviceSize + 1) ;
        SD_cardInfo.CardCapacity *= (1 << (SD_cardInfo.SD_csd.DeviceSizeMul + 2));
        SD_cardInfo.CardBlockSize = 1 << (SD_cardInfo.SD_csd.RdBlockLen);
        SD_cardInfo.CardCapacity *= SD_cardInfo.CardBlockSize;
    }
    else if (SD_cardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)
    {
        /*!< Byte 7 */
        tmp = (uint8_t)(CSD_Tab[1] & 0x000000FF);
        SD_cardInfo.SD_csd.DeviceSize = (tmp & 0x3F) << 16;

        /*!< Byte 8 */
        tmp = (uint8_t)((CSD_Tab[2] & 0xFF000000) >> 24);

        SD_cardInfo.SD_csd.DeviceSize |= (tmp << 8);

        /*!< Byte 9 */
        tmp = (uint8_t)((CSD_Tab[2] & 0x00FF0000) >> 16);

        SD_cardInfo.SD_csd.DeviceSize |= (tmp);

        /*!< Byte 10 */
        tmp = (uint8_t)((CSD_Tab[2] & 0x0000FF00) >> 8);

        SD_cardInfo.CardCapacity = (uint64_t)(SD_cardInfo.SD_csd.DeviceSize + 1) * 512 * 1024;
        SD_cardInfo.CardBlockSize = 512;
    }

    SD_cardInfo.SD_csd.EraseGrSize = (tmp & 0x40) >> 6;
    SD_cardInfo.SD_csd.EraseGrMul = (tmp & 0x3F) << 1;

    /*!< Byte 11 */
    tmp = (uint8_t)(CSD_Tab[2] & 0x000000FF);
    SD_cardInfo.SD_csd.EraseGrMul |= (tmp & 0x80) >> 7;
    SD_cardInfo.SD_csd.WrProtectGrSize = (tmp & 0x7F);

    /*!< Byte 12 */
    tmp = (uint8_t)((CSD_Tab[3] & 0xFF000000) >> 24);
    SD_cardInfo.SD_csd.WrProtectGrEnable = (tmp & 0x80) >> 7;
    SD_cardInfo.SD_csd.ManDeflECC = (tmp & 0x60) >> 5;
    SD_cardInfo.SD_csd.WrSpeedFact = (tmp & 0x1C) >> 2;
    SD_cardInfo.SD_csd.MaxWrBlockLen = (tmp & 0x03) << 2;

    /*!< Byte 13 */
    tmp = (uint8_t)((CSD_Tab[3] & 0x00FF0000) >> 16);
    SD_cardInfo.SD_csd.MaxWrBlockLen |= (tmp & 0xC0) >> 6;
    SD_cardInfo.SD_csd.WriteBlockPaPartial = (tmp & 0x20) >> 5;
    SD_cardInfo.SD_csd.Reserved3 = 0;
    SD_cardInfo.SD_csd.ContentProtectAppli = (tmp & 0x01);

    /*!< Byte 14 */
    tmp = (uint8_t)((CSD_Tab[3] & 0x0000FF00) >> 8);
    SD_cardInfo.SD_csd.FileFormatGrouop = (tmp & 0x80) >> 7;
    SD_cardInfo.SD_csd.CopyFlag = (tmp & 0x40) >> 6;
    SD_cardInfo.SD_csd.PermWrProtect = (tmp & 0x20) >> 5;
    SD_cardInfo.SD_csd.TempWrProtect = (tmp & 0x10) >> 4;
    SD_cardInfo.SD_csd.FileFormat = (tmp & 0x0C) >> 2;
    SD_cardInfo.SD_csd.ECC = (tmp & 0x03);
}

uint32_t calcSDCLKDiv(uint32_t freq)
{
    uint32_t prediv;
    switch((SYS->CLKSEL & SYS_CLKSEL_SDIO_Msk) >> SYS_CLKSEL_SDIO_Pos)
    {
    case 0: prediv = 1; break;
    case 1: prediv = 3; break;
    case 2: prediv = 2; break;
    case 3: prediv = 0; break;
    }

    uint32_t clkdiv = (SystemCoreClock / (1 << prediv)) / freq;
    uint32_t regdiv = 0;

    if(clkdiv > 128)     regdiv = 0x80;
    else if(clkdiv > 64) regdiv = 0x40;
    else if(clkdiv > 32) regdiv = 0x20;
    else if(clkdiv > 16) regdiv = 0x10;
    else if(clkdiv >  8) regdiv = 0x08;
    else if(clkdiv >  4) regdiv = 0x04;
    else if(clkdiv >  2) regdiv = 0x02;
    else if(clkdiv >  1) regdiv = 0x01;
    else                 regdiv = 0x00;

    return regdiv;
}


/******************************************************************************************************************************************
* 函数名称: SDIO_IO_Init()
* 功能说明: SDIO读写IO卡初始化
* 输    入: uint32_t freq         SDIO_CLK时钟频率
*           enum SDIO_bus_width w   SDIO_1bit 1-bit bus   SDIO_4bit 4-bit bus
* 输    出: uint32_t              SD_RES_OK 操作成功    SD_RES_ERR 操作失败    SD_RES_TIMEOUT 操作超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SDIO_IO_Init(uint32_t freq, enum SDIO_bus_width w)
{
    uint32_t res;
    uint32_t resp, resps[4];

    SYS->CLKSEL &= ~SYS_CLKSEL_SDIO_Msk;
    if(SystemCoreClock > 80000000)      //SDIO时钟需要小于52MHz
        SYS->CLKSEL |= (2 << SYS_CLKSEL_SDIO_Pos);  //SDCLK = SYSCLK / 4
    else
        SYS->CLKSEL |= (0 << SYS_CLKSEL_SDIO_Pos);  //SDCLK = SYSCLK / 2

    SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_SDIO_Pos);

//  SDIO->CR2 = (1 << SDIO_CR2_RSTALL_Pos);
    for(int i = 0; i < CyclesPerUs; i++) __NOP();

    SDIO->CR1 = (1 << SDIO_CR1_CDSRC_Pos) |
                (0 << SDIO_CR1_8BIT_Pos)  |
                (w << SDIO_CR1_4BIT_Pos)  |
                (1 << SDIO_CR1_PWRON_Pos) |
                (7 << SDIO_CR1_VOLT_Pos);

    SDIO->CR2 = (1 << SDIO_CR2_CLKEN_Pos) |
                (1 << SDIO_CR2_SDCLKEN_Pos) |
                (calcSDCLKDiv(freq) << SDIO_CR2_SDCLKDIV_Pos) |
                (0xC << SDIO_CR2_TIMEOUT_Pos);      // 2**25 SDIO_CLK

    while((SDIO->CR2 & SDIO_CR2_CLKRDY_Msk) == 0);

    for(int i = 0; i < CyclesPerUs * 10; i++) __NOP();

    SDIO->IM = 0xFFFFFFFF;

    return SD_RES_OK;
}


/******************************************************************************************************************************************
* 函数名称: SDIO_IO_ByteWrite()
* 功能说明: 向IO卡写入单个字节
* 输    入: uint8_t func          The number of the function within the I/O card you wish to read or write
*           uint32_t addr           Start Address of I/O register to read or write. Range is 0--0x1FFFF
*           uint32_t buff[]         要写出的数据
*           uint16_t block_size     要写出的字节个数，取值 1--512
* 输    出: uint32_t              SD_RES_OK 操作成功    SD_RES_ERR 操作失败    SD_RES_TIMEOUT 操作超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SDIO_IO_ByteWrite(uint8_t func, uint32_t addr, uint8_t data)
{
    uint32_t res;
    uint32_t arg, resp;

    arg = (1u   << SD_CMD53_ARG_nRW) |
          (func << SD_CMD53_ARG_Function) |
          (addr << SD_CMD53_ARG_Addr) | data;

    res = SDIO_SendCmd(52, arg, SD_RESP_32b, &resp);
    if(res != SD_RES_OK)
        return res;

    return SD_RES_OK;
}


/******************************************************************************************************************************************
* 函数名称: SDIO_IO_ByteRead()
* 功能说明: 从IO卡读出单个字节
* 输    入: uint8_t func          The number of the function within the I/O card you wish to read or write
*           uint32_t addr           Start Address of I/O register to read or write. Range is 0--0x1FFFF
*           uint32_t buff[]         读取到的数据存入此数组
*           uint16_t block_size     要读取的字节个数，取值 1--512
* 输    出: uint32_t              SD_RES_OK 操作成功    SD_RES_ERR 操作失败    SD_RES_TIMEOUT 操作超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SDIO_IO_ByteRead(uint8_t func, uint32_t addr, uint8_t * data)
{
    uint32_t res;
    uint32_t arg, resp;

    arg = (0u   << SD_CMD53_ARG_nRW) |
          (func << SD_CMD53_ARG_Function) |
          (addr << SD_CMD53_ARG_Addr) | 0x00;

    res = SDIO_SendCmd(52, arg, SD_RESP_32b, &resp);
    if(res != SD_RES_OK)
        return res;

    *data = resp & 0xFF;

    return SD_RES_OK;
}


/******************************************************************************************************************************************
* 函数名称: SDIO_IO_BlockWrite()
* 功能说明: 向IO卡写入单个块数据
* 输    入: uint8_t func          The number of the function within the I/O card you wish to read or write
*           uint32_t addr           Start Address of I/O register to read or write. Range is 0--0x1FFFF
*           uint8_t addrInc         0 Multi byte R/W to fixed address   1 Multi byte R/W to incrementing address
*           uint32_t buff[]         要写出的数据
*           uint16_t block_size     要写出的字节个数，取值 1--512
* 输    出: uint32_t              SD_RES_OK 操作成功    SD_RES_ERR 操作失败    SD_RES_TIMEOUT 操作超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SDIO_IO_BlockWrite(uint8_t func, uint32_t addr, uint8_t addrInc, uint32_t buff[], uint16_t block_size)
{
    uint32_t res, i;
    uint32_t arg, resp;

    SDIO->BLK = block_size;

    arg = (1u                   << SD_CMD53_ARG_nRW) |
          (func                 << SD_CMD53_ARG_Function) |
          (addr                 << SD_CMD53_ARG_Addr) |
          (addrInc              << SD_CMD53_ARG_AddrInc) |
          ((block_size % 512)   << SD_CMD53_ARG_Count) |
          (0                    << SD_CMD53_ARG_CountUnit);

    res = SDIO_SendCmdWithData(53, arg, SD_RESP_32b, &resp, 0, 1);
    if(res != SD_RES_OK)
        return res;

    while((SDIO->IF & SDIO_IF_BUFWRRDY_Msk) == 0) __NOP();
    SDIO->IF = SDIO_IF_BUFWRRDY_Msk;

    for(i = 0; i < block_size/4; i++) SDIO->DATA = buff[i];

    while((SDIO->IF & SDIO_IF_TRXDONE_Msk) == 0) __NOP();
    SDIO->IF = SDIO_IF_TRXDONE_Msk;

    return SD_RES_OK;
}


/******************************************************************************************************************************************
* 函数名称: SDIO_IO_BlockRead()
* 功能说明: 从IO卡读出单个块数据
* 输    入: uint8_t func          The number of the function within the I/O card you wish to read or write
*           uint32_t addr           Start Address of I/O register to read or write. Range is 0--0x1FFFF
*           uint8_t addrInc         0 Multi byte R/W to fixed address   1 Multi byte R/W to incrementing address
*           uint32_t buff[]         读取到的数据存入此数组
*           uint16_t block_size     要读取的字节个数，取值 1--512
* 输    出: uint32_t              SD_RES_OK 操作成功    SD_RES_ERR 操作失败    SD_RES_TIMEOUT 操作超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SDIO_IO_BlockRead(uint8_t func, uint32_t addr, uint8_t addrInc, uint32_t buff[], uint16_t block_size)
{
    uint32_t res, i;
    uint32_t arg, resp;

    SDIO->BLK = block_size;

    arg = (0u                   << SD_CMD53_ARG_nRW) |
          (func                 << SD_CMD53_ARG_Function) |
          (addr                 << SD_CMD53_ARG_Addr) |
          (addrInc              << SD_CMD53_ARG_AddrInc) |
          ((block_size % 512)   << SD_CMD53_ARG_Count) |
          (0                    << SD_CMD53_ARG_CountUnit);

    res = SDIO_SendCmdWithData(53, arg, SD_RESP_32b, &resp, 1, 1);
    if(res != SD_RES_OK)
        return res;

    while((SDIO->IF & SDIO_IF_BUFRDRDY_Msk) == 0) __NOP();
    SDIO->IF = SDIO_IF_BUFRDRDY_Msk;

    for(i = 0; i < block_size/4; i++) buff[i] = SDIO->DATA;

    while((SDIO->IF & SDIO_IF_TRXDONE_Msk) == 0) __NOP();
    SDIO->IF = SDIO_IF_TRXDONE_Msk;

    return SD_RES_OK;
}


/******************************************************************************************************************************************
* 函数名称: SDIO_IO_MultiBlockWrite()
* 功能说明: 向IO卡写入多个块数据
* 输    入: uint8_t func          The number of the function within the I/O card you wish to read or write
*           uint32_t addr           Start Address of I/O register to read or write. Range is 0--0x1FFFF
*           uint8_t addrInc         0 Multi byte R/W to fixed address   1 Multi byte R/W to incrementing address
*           uint32_t buff[]         要写出的数据
*           uint16_t block_count    要写出的块个数，块大小为 512 字节
* 输    出: uint32_t              SD_RES_OK 操作成功    SD_RES_ERR 操作失败    SD_RES_TIMEOUT 操作超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SDIO_IO_MultiBlockWrite(uint8_t func, uint32_t addr, uint8_t addrInc, uint32_t buff[], uint16_t block_count)
{
    uint32_t res, i, j;
    uint32_t arg, resp;

    SDIO->BLK = 512;

    arg = (1u           << SD_CMD53_ARG_nRW) |
          (func         << SD_CMD53_ARG_Function) |
          (addr         << SD_CMD53_ARG_Addr) |
          (addrInc      << SD_CMD53_ARG_AddrInc) |
          (block_count  << SD_CMD53_ARG_Count) |
          (1            << SD_CMD53_ARG_CountUnit);

    res = SDIO_SendCmdWithData(53, arg, SD_RESP_32b, &resp, 0, block_count);
    if(res != SD_RES_OK)
        return res;

    for(i = 0; i < block_count; i++)
    {
        while((SDIO->IF & SDIO_IF_BUFWRRDY_Msk) == 0) __NOP();
        SDIO->IF = SDIO_IF_BUFWRRDY_Msk;

        for(j = 0; j < 512/4; j++) SDIO->DATA = buff[i*(512/4) + j];
    }

    while((SDIO->IF & SDIO_IF_TRXDONE_Msk) == 0) __NOP();
    SDIO->IF = SDIO_IF_TRXDONE_Msk;

    return SD_RES_OK;
}


/******************************************************************************************************************************************
* 函数名称: SDIO_IO_MultiBlockRead()
* 功能说明: 从IO卡读出多个块数据
* 输    入: uint8_t func          The number of the function within the I/O card you wish to read or write
*           uint32_t addr           Start Address of I/O register to read or write. Range is 0--0x1FFFF
*           uint8_t addrInc         0 Multi byte R/W to fixed address   1 Multi byte R/W to incrementing address
*           uint32_t buff[]         读取到的数据存入此数组
*           uint16_t block_count    要读取的块个数，块大小为 512 字节
* 输    出: uint32_t              SD_RES_OK 操作成功    SD_RES_ERR 操作失败    SD_RES_TIMEOUT 操作超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t SDIO_IO_MultiBlockRead(uint8_t func, uint32_t addr, uint8_t addrInc, uint32_t buff[], uint16_t block_count)
{
    uint32_t res, i, j;
    uint32_t arg, resp;

    SDIO->BLK = 512;

    arg = (0u           << SD_CMD53_ARG_nRW) |
          (func         << SD_CMD53_ARG_Function) |
          (addr         << SD_CMD53_ARG_Addr) |
          (addrInc      << SD_CMD53_ARG_AddrInc) |
          (block_count  << SD_CMD53_ARG_Count) |
          (1            << SD_CMD53_ARG_CountUnit);

    res = SDIO_SendCmdWithData(53, arg, SD_RESP_32b, &resp, 1, block_count);
    if(res != SD_RES_OK)
        return res;

    for(i = 0; i < block_count; i++)
    {
        while((SDIO->IF & SDIO_IF_BUFRDRDY_Msk) == 0) __NOP();
        SDIO->IF = SDIO_IF_BUFRDRDY_Msk;

        for(j = 0; j < 512/4; j++) buff[i*(512/4) + j] = SDIO->DATA;
    }

    while((SDIO->IF & SDIO_IF_TRXDONE_Msk) == 0) __NOP();
    SDIO->IF = SDIO_IF_TRXDONE_Msk;

    return SD_RES_OK;
}
