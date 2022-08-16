/******************************************************************************************************************************************
* 文件名称: SWM341_jpeg.c
* 功能说明: SWM341单片机的JPEG解码器驱动库
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
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
#include "SWM341_jpeg.h"

#include <math.h>
#include <string.h>


/******************************************************************************************************************************************
* 函数名称: JPEG_Init()
* 功能说明: JPEG解码器初始化
* 输    入: JPEG_TypeDef * JPEGx  指定要被设置的JPEG解码器，有效值包括JPEG
*           JPEG_InitStructure * initStruct    包含JPEG解码器相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void JPEG_Init(JPEG_TypeDef * JPEGx, JPEG_InitStructure * initStruct)
{
    switch((uint32_t)JPEGx)
    {
    case ((uint32_t)JPEG):
        SYS->CLKEN1 |= (0x01 << SYS_CLKEN1_JPEG_Pos);
        break;
    }

    JPEGx->IR = JPEG_IR_ICDONE_Msk |
                JPEG_IR_ICERROR_Msk;
    JPEGx->IR = ((initStruct->DoneIEn  ? 1 : 0) << JPEG_IR_IEDONE_Pos) |
                ((initStruct->ErrorIEn ? 1 : 0) << JPEG_IR_IEERROR_Pos);

    switch((uint32_t)JPEGx)
    {
    case ((uint32_t)JPEG):
        if(initStruct->DoneIEn | initStruct->ErrorIEn)
        {
            NVIC_EnableIRQ(JPEG_IRQn);
        }
        else
        {
            NVIC_DisableIRQ(JPEG_IRQn);
        }
        break;
    }
}


/******************************************************************************************************************************************
* 函数名称: JPEG_Decode()
* 功能说明: JPEG解码器解码
* 输    入: JPEG_TypeDef * JPEGx  指定要被设置的JPEG解码器，有效值包括JPEG
*           jfif_info_t * jfif_info     要解码图像的信息
*           jpeg_outset_t * jpeg_outset 解码输出设定
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void JPEG_Decode(JPEG_TypeDef * JPEGx, jfif_info_t * jfif_info, jpeg_outset_t * jpeg_outset)
{
    int32_t i, j;
    uint8_t hxvx;
    uint8_t out_rgb = ((jpeg_outset->format & 7) > 1 ? 1 : 0);  // output rgb ?

    switch((jfif_info->CompInfo[0].hfactor << 4) | jfif_info->CompInfo[0].vfactor)
    {
    case 0x11: hxvx = JPEG_FMT_H1V1;  break;
    case 0x21: hxvx = JPEG_FMT_H2V1;  break;
    case 0x22: hxvx = JPEG_FMT_H2V2;  break;
    default:   return;
    }

    JPEGx->CFG = (hxvx << JPEG_CFG_SRCFMT_Pos)  |
                 (0    << JPEG_CFG_SCANMOD_Pos) |
                 (0    << JPEG_CFG_NISCOMP_Pos) |
                 (jfif_info->CompInfo[0].htab_id_dc << JPEG_CFG_HT1COMP_Pos) |
                 (jfif_info->CompInfo[1].htab_id_dc << JPEG_CFG_HT2COMP_Pos) |
                 (jfif_info->CompInfo[2].htab_id_dc << JPEG_CFG_HT3COMP_Pos) |
                 (jfif_info->CompInfo[0].qtab_id    << JPEG_CFG_QT1COMP_Pos) |
                 (jfif_info->CompInfo[1].qtab_id    << JPEG_CFG_QT2COMP_Pos) |
                 (jfif_info->CompInfo[2].qtab_id    << JPEG_CFG_QT3COMP_Pos) |
                 (jpeg_outset->format << JPEG_CFG_OUTFMT_Pos)  |
                 (out_rgb             << JPEG_CFG_YUV2RGB_Pos) |
                 (jpeg_outset->dither << JPEG_CFG_565DITH_Pos);

    JPEGx->IMGSIZ = ((jfif_info->Width  - 1) << JPEG_IMGSIZ_HPIX_Pos) |
                    ((jfif_info->Height - 1) << JPEG_IMGSIZ_VPIX_Pos);

    JPEGx->CSBASE = jfif_info->CodeAddr;
    JPEGx->CODLEN = jfif_info->CodeLen - 1;

    if(out_rgb)
    {
        JPEGx->RGBASE = jpeg_outset->RGBAddr;

        switch(jpeg_outset->format & 7)
        {
        case JPEG_OUT_XRGB888:
            JPEG->IMGSTR = jfif_info->Width << JPEG_IMGSTR_RGBLINE_Pos;
            break;

        case JPEG_OUT_RGB888:
            JPEG->IMGSTR = (int)ceil(jfif_info->Width*3/4.0) << JPEG_IMGSTR_RGBLINE_Pos;
            break;

        case JPEG_OUT_RGB565:
            JPEG->IMGSTR = (int)ceil(jfif_info->Width / 2.0) << JPEG_IMGSTR_RGBLINE_Pos;
            break;
        }
    }
    else
    {
        JPEGx->YBASE  = jpeg_outset->YAddr;
        JPEGx->UBASE  = jpeg_outset->CbAddr;
        JPEGx->VBASE  = jpeg_outset->CrAddr;

        switch(((jpeg_outset->format & 7) << 4) | hxvx)
        {
        case (JPEG_OUT_YUV << 4) | JPEG_FMT_H1V1:
            JPEG->IMGSTR = ((int)ceil(jfif_info->Width / 4.0) << JPEG_IMGSTR_YLINE_Pos) |
                           ((int)ceil(jfif_info->Width / 4.0) << JPEG_IMGSTR_UVLINE_Pos);
            break;

        case (JPEG_OUT_YUV << 4) | JPEG_FMT_H2V1:
        case (JPEG_OUT_YUV << 4) | JPEG_FMT_H2V2:
            JPEG->IMGSTR = ((int)ceil(jfif_info->Width / 4.0) << JPEG_IMGSTR_YLINE_Pos) |
                           ((int)ceil(jfif_info->Width / 8.0) << JPEG_IMGSTR_UVLINE_Pos);
            break;

        case (JPEG_OUT_YUVsp << 4) | JPEG_FMT_H1V1:
            JPEG->IMGSTR = ((int)ceil(jfif_info->Width / 4.0) << JPEG_IMGSTR_YLINE_Pos) |
                           ((int)ceil(jfif_info->Width / 2.0) << JPEG_IMGSTR_UVLINE_Pos);
            break;

        case (JPEG_OUT_YUVsp << 4) | JPEG_FMT_H2V1:
        case (JPEG_OUT_YUVsp << 4) | JPEG_FMT_H2V2:
            JPEG->IMGSTR = ((int)ceil(jfif_info->Width / 4.0) << JPEG_IMGSTR_YLINE_Pos) |
                           ((int)ceil(jfif_info->Width / 4.0) << JPEG_IMGSTR_UVLINE_Pos);
            break;
        }
    }

    for(i = 0; i < jfif_info->QTableCnt; i++)
    {
        for(j = 0; j < 16; j++)
        {
            JPEGx->QTABLE[i][j] = ((uint32_t *)&jfif_info->QTable[i])[j];
        }
    }

    for(i = 0; i < jfif_info->HTableCnt; i++)
    {
        /* DC Haffman Table */
        for(j = 0; j < 12; j += 2)
        {
            JPEGx->HTABLE[i].DC_CODEWORD[j/2] = (jfif_info->HTable[i].DC.codeWord[j]   << (16 - jfif_info->HTable[i].DC.codeLen[j])) |
                                                (jfif_info->HTable[i].DC.codeWord[j+1] << (32 - jfif_info->HTable[i].DC.codeLen[j+1]));
        }
        for(j = 10; j > 1; j -= 2)
        {
            if((jfif_info->HTable[i].DC.codeWord[j+1] == 0) && (jfif_info->HTable[i].DC.codeWord[j] == 0))
                JPEGx->HTABLE[i].DC_CODEWORD[j/2] = 0xFFFFFFFF;
            else if(jfif_info->HTable[i].DC.codeWord[j+1] == 0)
                JPEGx->HTABLE[i].DC_CODEWORD[j/2] = 0xFFFF0000 | (jfif_info->HTable[i].DC.codeWord[j] << (16 - jfif_info->HTable[i].DC.codeLen[j]));
            else
                break;
        }

        JPEGx->HTABLE[i].DC_CODELEN[0] = ((jfif_info->HTable[i].DC.codeLen[0]  ? jfif_info->HTable[i].DC.codeLen[0] - 1 : 0) <<  0) |
                                         ((jfif_info->HTable[i].DC.codeLen[1]  ? jfif_info->HTable[i].DC.codeLen[1] - 1 : 0) <<  4) |
                                         ((jfif_info->HTable[i].DC.codeLen[2]  ? jfif_info->HTable[i].DC.codeLen[2] - 1 : 0) <<  8) |
                                         ((jfif_info->HTable[i].DC.codeLen[3]  ? jfif_info->HTable[i].DC.codeLen[3] - 1 : 0) << 12) |
                                         ((jfif_info->HTable[i].DC.codeLen[4]  ? jfif_info->HTable[i].DC.codeLen[4] - 1 : 0) << 16) |
                                         ((jfif_info->HTable[i].DC.codeLen[5]  ? jfif_info->HTable[i].DC.codeLen[5] - 1 : 0) << 20) |
                                         ((jfif_info->HTable[i].DC.codeLen[6]  ? jfif_info->HTable[i].DC.codeLen[6] - 1 : 0) << 24) |
                                         ((jfif_info->HTable[i].DC.codeLen[7]  ? jfif_info->HTable[i].DC.codeLen[7] - 1 : 0) << 28);
        JPEGx->HTABLE[i].DC_CODELEN[1] = ((jfif_info->HTable[i].DC.codeLen[8]  ? jfif_info->HTable[i].DC.codeLen[8] - 1 : 0) <<  0) |
                                         ((jfif_info->HTable[i].DC.codeLen[9]  ? jfif_info->HTable[i].DC.codeLen[9] - 1 : 0) <<  4) |
                                         ((jfif_info->HTable[i].DC.codeLen[10] ? jfif_info->HTable[i].DC.codeLen[10]- 1 : 0) <<  8) |
                                         ((jfif_info->HTable[i].DC.codeLen[11] ? jfif_info->HTable[i].DC.codeLen[11]- 1 : 0) << 12);

        JPEGx->HTABLE[i].DC_CODEVAL[0] = (jfif_info->HTable[i].DC.codeVal[0] <<  0) |
                                         (jfif_info->HTable[i].DC.codeVal[1] <<  4) |
                                         (jfif_info->HTable[i].DC.codeVal[2] <<  8) |
                                         (jfif_info->HTable[i].DC.codeVal[3] << 12) |
                                         (jfif_info->HTable[i].DC.codeVal[4] << 16) |
                                         (jfif_info->HTable[i].DC.codeVal[5] << 20) |
                                         (jfif_info->HTable[i].DC.codeVal[6] << 24) |
                                         (jfif_info->HTable[i].DC.codeVal[7] << 28);
        JPEGx->HTABLE[i].DC_CODEVAL[1] = (jfif_info->HTable[i].DC.codeVal[8] <<  0) |
                                         (jfif_info->HTable[i].DC.codeVal[9] <<  4) |
                                         (jfif_info->HTable[i].DC.codeVal[10]<<  8) |
                                         (jfif_info->HTable[i].DC.codeVal[11]<< 12);

        /* AC Haffman Table */
        uint16_t minCode[16];       // mini code word for each lenght
        uint8_t  minIndx[16];       // index of mincode
        uint8_t  prelen;            // preiou Len

        memset(minCode, 0, sizeof(minCode));
        memset(minIndx, 0, sizeof(minIndx));
        for(j = 0, prelen = 0; j < 162; j++)
        {
            if(jfif_info->HTable[i].AC.codeLen[j] == 0) break;

            if(jfif_info->HTable[i].AC.codeLen[j] != prelen)
            {
                minCode[jfif_info->HTable[i].AC.codeLen[j] - 1] = jfif_info->HTable[i].AC.codeWord[j] << (16 - jfif_info->HTable[i].AC.codeLen[j]);
                minIndx[jfif_info->HTable[i].AC.codeLen[j] - 1] = j;

                prelen = jfif_info->HTable[i].AC.codeLen[j];
            }
        }

        if(minCode[15] == 0) minCode[15] = 0xFFFF;
        for(j = 14; j > jfif_info->HTable[i].AC.codeLen[0] - 1; j--)
        {
            if(minCode[j] == 0) minCode[j] = minCode[j+1];
        }

        for(j = 0; j < 16; j += 2)
        {
            JPEGx->HTABLE[i].AC_CODEWORD[j/2] = (minCode[j]   << 0)  |
                                                (minCode[j+1] << 16);
        }

        for(j = 0; j < 16; j += 4)
        {
            JPEGx->HTABLE[i].AC_CODEADDR[j/4] = (minIndx[j]   << 0)  |
                                                (minIndx[j+1] << 8)  |
                                                (minIndx[j+2] << 16) |
                                                (minIndx[j+3] << 24);
        }

        for(j = 0; j < 164; j += 4)
        {
            JPEGx->HTABLE[i].AC_CODEVAL[j/4] = (jfif_info->HTable[i].AC.codeVal[j]   <<  0) |
                                               (jfif_info->HTable[i].AC.codeVal[j+1] <<  8) |
                                               (jfif_info->HTable[i].AC.codeVal[j+2] << 16) |
                                               (jfif_info->HTable[i].AC.codeVal[j+3] << 24);
        }
    }

    JPEGx->CR = (1 << JPEG_CR_LASTBUF_Pos) |
                (1 << JPEG_CR_START_Pos);
}


/******************************************************************************************************************************************
* 函数名称: JPEG_DecodeBusy()
* 功能说明: JPEG解码器忙查询
* 输    入: JPEG_TypeDef * JPEGx  指定要被设置的JPEG解码器，有效值包括JPEG
* 输    出: uint32_t              1 正在解码    0 空闲，未在解码
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t JPEG_DecodeBusy(JPEG_TypeDef * JPEGx)
{
    return (JPEGx->SR & JPEG_SR_BUSY_Msk) ? 1 : 0;
}
