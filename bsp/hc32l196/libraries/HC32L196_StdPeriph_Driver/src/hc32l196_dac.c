/******************************************************************************
* Copyright (C) 2019, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/******************************************************************************/
/** \file dac.c
 **
 ** dac driver API.
 **
 **   - 2019-04-10    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l196_dac.h"

/**
 ******************************************************************************
 ** \addtogroup AdcGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/

/**
******************************************************************************
    ** \brief  使能相关通道的DMA DMA_CR0中的DMAEN0
    ** 
  ** @param  NewState  :   TRUE 或者 FALSE
    ** \retval 无
    **
******************************************************************************/
void Dac_DmaCmd(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_DAC->CR0)), 12, NewState);
}

/**
******************************************************************************
    ** \brief  配置DAC的DMA下溢中断， DMA_CR0中的DMAUDRIE0
    ** 
  ** @param  NewState  :   TRUE 或者 FALSE
    ** \retval 无
    **
******************************************************************************/
void Dac_DmaITCfg(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_DAC->CR0)), 13, NewState);
}

/**
******************************************************************************
    ** \brief  获取DAC的DMA下溢中断标志位状态， DMA_SR中的DMAUDR0
    ** 
    ** @param  无
    ** \retval TRUE 或 FALSE
    **
******************************************************************************/
boolean_t Dac_GetITStatus(void)
{  
    return GetBit((uint32_t)(&(M0P_DAC->SR)), 13);
}

/**
******************************************************************************
    ** \brief  配置DAC的使能与禁止， DMA_CR0中的EN0
    ** 
  ** @param  NewState  :   TRUE 或者 FALSE
    ** \retval 无
    **
******************************************************************************/
void Dac_Cmd(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_DAC->CR0)), 0, NewState);
}

/**
******************************************************************************
    ** \brief  软件触发寄存器，触发DAC转换 DMA_SWTRIGR中的SWTRIG0
    ** 
    ** @param  无
    ** \retval 无
    **
******************************************************************************/
void Dac_SoftwareTriggerCmd(void)
{
    SetBit((uint32_t)(&(M0P_DAC->SWTRIGR)), 0, 1);
}
    
/**
******************************************************************************
** \brief  初始化DAC0
    ** 
    ** @param  DAC_InitStruct  :   用于初始化DAC0的结构体
    ** \retval 无
    **
******************************************************************************/
void Dac_Init(stc_dac_cfg_t* DAC_InitStruct)
{
    M0P_DAC->CR0_f.BOFF0 = DAC_InitStruct->boff_t;
    M0P_DAC->CR0_f.TEN0  = DAC_InitStruct->ten_t;
    M0P_DAC->CR0_f.TSEL0 = DAC_InitStruct->tsel_t;
    M0P_DAC->CR0_f.WAVE0 = DAC_InitStruct->wave_t;
    M0P_DAC->CR0_f.MAMP0 = DAC_InitStruct->mamp_t;
    M0P_DAC->CR0_f.SREF0 = DAC_InitStruct->sref_t;
    
    if(DAC_InitStruct->align == DacLeftAlign)
    {
        M0P_DAC->DHR12L0_f.DHR0 = DAC_InitStruct->dhr12;
    }
    else if(DAC_InitStruct->align == DacRightAlign)
    {
        M0P_DAC->DHR12R0_f.DHR0 = DAC_InitStruct->dhr12;
    }
    else
    {
        M0P_DAC->DHR8R0_f.DHR0 = DAC_InitStruct->dhr8;
    }
}

/**
******************************************************************************
** \brief  向DAC0的数据保持寄存器写数据
    ** 
    ** @param  DAC_Channel:   Dac_0
    ** @param  DAC_Align  :   Right_Align 与Left_Align
    ** @param  DAC_Bit    :   Bit8 与Bit12
    ** @param  Data       :   所要发送的数据
    ** \retval 无
    **
******************************************************************************/
void Dac_SetChannelData(en_align_t DAC_Align, en_bitno_t DAC_Bit, uint16_t Data)
{  
    if(DAC_Align == DacRightAlign)
    {
        if(DAC_Bit == DacBit8)
        {
            M0P_DAC->DHR8R0_f.DHR0 = (uint8_t)Data;
        }
        else if(DAC_Bit == DacBit12)
        {
            M0P_DAC->DHR12R0_f.DHR0 = Data;
        }
        else
        {
          return;
        }
    }
    else if(DAC_Align == DacLeftAlign)
    {
        if(DAC_Bit == DacBit8)
        {
            return;
        }
        else if(DAC_Bit == DacBit12)
        {
            M0P_DAC->DHR12L0_f.DHR0 = Data;
        }
        else
        {
          return;
        }
    }
    else
    {
        return;
    }
}



/**
******************************************************************************
    ** \brief  获取DAC数据输出寄存器DAC_DOR0
    ** 
    ** @param  无
    ** \retval DAC_DOR0的值
    **
******************************************************************************/
uint16_t Dac_GetDataOutputValue(void)
{
    uint16_t tmp;

    tmp = M0P_DAC->DOR0_f.DOR0;
    return tmp&0x0fff;
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


