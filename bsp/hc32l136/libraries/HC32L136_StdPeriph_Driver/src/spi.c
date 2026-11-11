/******************************************************************************
* Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
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
* included with eaenCh copy of this software, whether used in part or whole,
* at all times.
*/
/*****************************************************************************/
/** \file spi.c
 **
 ** SPI driver API.
 ** @link Driver Group Some description @endlink
 **
 **   - 2018-05-17  1.0  Devi First version for Device Driver Library of
 **                      Module.
 **
 *****************************************************************************/

/******************************************************************************
 * Include files
 *****************************************************************************/
#include "spi.h"

/**
 ******************************************************************************
 ** \addtogroup SpiGroup
 *****************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 *****************************************************************************/

#define IS_VALID_STAT(x)            (   SpiIf == (x)||\
                                        SpiSserr == (x)||\
                                        SpiBusy == (x)||\
                                        SpiMdf == (x)||\
                                        SpiTxe == (x)||\
                                        SpiRxne == (x))
#define IS_VALID_CH(x)              (   Spi0 == (x)||\
                                        Spi1 == (x))


/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Local variable prototypes ('static')                                       */
/******************************************************************************/
static func_ptr_t pfnSpi0Callback = NULL; ///< callback function pointer for SPI Irq
static func_ptr_t pfnSpi1Callback = NULL; ///< callback function pointer for SPI Irq
/**
 ******************************************************************************
 ** \brief  SPI 中断处理函数
 **
 ** \param [in] enCh通道
 **
 ** \retval 无
 ** 
 ******************************************************************************/
void Spi_IRQHandler(en_spi_channel_t enCh)
{
    if(Spi0 == enCh)
    {
		if(NULL != pfnSpi0Callback)
		{
			pfnSpi0Callback();
		}   
    }
    else
    {
		if(NULL != pfnSpi1Callback)
		{
			pfnSpi1Callback();
		}
 
    }   
}
/**
 ******************************************************************************
 ** \brief  SPI 请求状态获取
 **
 ** \param [in]enCh 通道
 **
 ** \retval 请求状态
 ** 
 ******************************************************************************/
uint8_t Spi_GetState(en_spi_channel_t enCh)
{
    uint8_t u8State = 0;
    ASSERT(IS_VALID_CH(enCh));
    if(Spi0 == enCh)
    {
        u8State = M0P_SPI0->STAT;
    }
    else
    {
        u8State = M0P_SPI1->STAT;
    }
    return u8State;
}
/**
 ******************************************************************************
 ** \brief  SPI 请求状态获取
 **
 ** \param [in]enCh 通道， enStatus 获取请求
 **
 ** \retval 请求状态
 ** 
 ******************************************************************************/
boolean_t Spi_GetStatus(en_spi_channel_t enCh,en_spi_status_t enStatus)
{
    boolean_t bFlag = FALSE;
    ASSERT(IS_VALID_CH(enCh));
    ASSERT(IS_VALID_STAT(enStatus));
    if(Spi0 == enCh)
    {
        switch (enStatus)
        {
            case SpiIf:
                bFlag = M0P_SPI0->STAT_f.SPIF;
                break;
            case SpiSserr:
                bFlag = M0P_SPI0->STAT_f.SSERR;
                break;
            case SpiMdf:
                bFlag = M0P_SPI0->STAT_f.MDF;
                break;
            case SpiBusy:
                bFlag = M0P_SPI0->STAT_f.BUSY;
                break;
            case SpiTxe:
                bFlag = M0P_SPI0->STAT_f.TXE;
                break;
            case SpiRxne:
                bFlag = M0P_SPI0->STAT_f.RXNE;
                break;
            default:
                break;
        }   
    }
    else
    {
        switch (enStatus)
        {
            case SpiIf:
                bFlag = M0P_SPI1->STAT_f.SPIF;
                break;
            case SpiSserr:
                bFlag = M0P_SPI1->STAT_f.SSERR;
                break;
            case SpiMdf:
                bFlag = M0P_SPI1->STAT_f.MDF;
                break;
            case SpiBusy:
                bFlag = M0P_SPI1->STAT_f.BUSY;
                break;
            case SpiTxe:
                bFlag = M0P_SPI1->STAT_f.TXE;
                break;
            case SpiRxne:
                bFlag = M0P_SPI1->STAT_f.RXNE;
                break;
            default:
                break;
        }   
    }
    return bFlag;
}
/**
 ******************************************************************************
 ** \brief  SPI中断清除
 **
 ** \param [in]enCh 通道， enStatus 获取请求
 **
 ** \retval 请求状态
 ** 
 ******************************************************************************/
en_result_t Spi_ClearStatus(en_spi_channel_t enCh)
{
    en_result_t enRet = Error;
    ASSERT(IS_VALID_CH(enCh));
    if(Spi0 == enCh)
    {
        M0P_SPI0->ICLR_f.INT_CLR = 0;
    }
    else
    {
        M0P_SPI1->ICLR_f.INT_CLR = 0;
    }
    enRet = Ok;
    return enRet;
}
/**
 ******************************************************************************
 ** \brief  SPI 功能使能禁止函数
 **
 ** \param [in] enCh通道，enFunc功能，bFlag 0/1使能或禁止
 **
 ** \retval Ok初始化成功
 ** \retval ErrorInvalidParameter 初始化错误
 ******************************************************************************/
en_result_t Spi_FuncEn(en_spi_channel_t enCh,en_spi_func_t enFunc,boolean_t bFlag)
{
    en_result_t enRet = Error;
    ASSERT(IS_VALID_CH(enCh));
    if(Spi0 == enCh)
    {
        switch(enFunc)
        {
            case SpiRxNeIe:
                M0P_SPI0->CR2_f.RXNEIE = bFlag;
                break;
            case SpiTxEIe:
                M0P_SPI0->CR2_f.TXEIE = bFlag;
                break;
            case SpiDmaTxEn:
                M0P_SPI0->CR2_f.HDMA_TX = bFlag;
                break;
            case SpiDmaRxEn:
                M0P_SPI0->CR2_f.HDMA_RX = bFlag;
                break;
            default:
                return ErrorInvalidParameter;
        } 
    }
    else
    {
        switch(enFunc)
        {
            case SpiRxNeIe:
                M0P_SPI1->CR2_f.RXNEIE = bFlag;
                break;
            case SpiTxEIe:
                M0P_SPI1->CR2_f.TXEIE = bFlag;
                break;
            case SpiDmaTxEn:
                M0P_SPI1->CR2_f.HDMA_TX = bFlag;
                break;
            case SpiDmaRxEn:
                M0P_SPI1->CR2_f.HDMA_RX = bFlag;
                break;
            default:
                return ErrorInvalidParameter;
        }  
    }
    enRet = Ok;
    return enRet;
}
/**
 ******************************************************************************
 ** \brief  SPI 总体初始化函数
 **
 ** \param [in] 
            enCh通道
            pstcSpiConfig初始化结构
 **
 ** \retval Ok初始化成功
 ** \retval ErrorInvalidParameter 初始化错误
 ******************************************************************************/
en_result_t Spi_Init(en_spi_channel_t enCh,stc_spi_config_t *pstcSpiConfig)
{
    ASSERT(NULL != pstcSpiConfig);
    ASSERT(IS_VALID_CH(enCh));
    if(Spi0 == enCh)
    {
        M0P_SPI0->CR = 0x00;

        M0P_SPI0->CR_f.MSTR = pstcSpiConfig->bMasterMode;
        M0P_SPI0->CR_f.CPOL = pstcSpiConfig->bCPOL;
        M0P_SPI0->CR_f.CPHA = pstcSpiConfig->bCPHA;
        if(pstcSpiConfig->u8BaudRate > SpiClkDiv16)
        {
            M0P_SPI0->CR_f.SPR2 = 1;      
        }
        M0P_SPI0->CR |= (pstcSpiConfig->u8BaudRate&0x03u);    

        M0P_SPI0->STAT = 0x00;

        M0P_SPI0->CR_f.SPEN = TRUE;
        if (TRUE == pstcSpiConfig->bIrqEn)
        {
            M0P_SPI0->CR2_f.INT_EN = 1;
            EnableNvic(SPI0_IRQn,IrqLevel3,TRUE);
        }
        else
        {
            EnableNvic(SPI0_IRQn,IrqLevel3,FALSE);
        }
        if(NULL != pstcSpiConfig->pfnSpi0IrqCb)
        {
            pfnSpi0Callback = pstcSpiConfig->pfnSpi0IrqCb;
        } 
    }
    else
    {
        M0P_SPI1->CR = 0x00;

        M0P_SPI1->CR_f.MSTR = pstcSpiConfig->bMasterMode;
        M0P_SPI1->CR_f.CPOL = pstcSpiConfig->bCPOL;
        M0P_SPI1->CR_f.CPHA = pstcSpiConfig->bCPHA;
        if(pstcSpiConfig->u8BaudRate > SpiClkDiv16)
        {
            M0P_SPI1->CR_f.SPR2 = 1;      
        }
        M0P_SPI1->CR |= (pstcSpiConfig->u8BaudRate&0x03u);    

        M0P_SPI1->STAT = 0x00;

        M0P_SPI1->CR_f.SPEN = TRUE;
        if (TRUE == pstcSpiConfig->bIrqEn)
        {
            M0P_SPI1->CR2_f.INT_EN = 1;
            EnableNvic(SPI1_IRQn,IrqLevel3,TRUE);
        }
        else
        {
            EnableNvic(SPI1_IRQn,IrqLevel3,FALSE);
        }
        if(NULL != pstcSpiConfig->pfnSpi1IrqCb)
        {
            pfnSpi1Callback = pstcSpiConfig->pfnSpi1IrqCb;
        } 
    }
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  SPI 禁止函数
 **
 ** \param [in] enCh通道
 **
 ** \retval Ok禁止设置成功
 ** 
 ******************************************************************************/
en_result_t Spi_DeInit(en_spi_channel_t enCh)
{
    ASSERT(IS_VALID_CH(enCh));
    if(Spi0 == enCh)
    {
        M0P_SPI0->DATA  = 0x00;   
        M0P_SPI0->STAT  = 0x00;
        M0P_SPI0->CR  = 0x00;
        pfnSpi0Callback  = NULL;
        EnableNvic(SPI0_IRQn,IrqLevel3,FALSE);  
    }
    else
    {
        M0P_SPI1->DATA  = 0x00;   
        M0P_SPI1->STAT  = 0x00;
        M0P_SPI1->CR  = 0x00;
        pfnSpi1Callback  = NULL;
        EnableNvic(SPI1_IRQn,IrqLevel3,FALSE);  
    }
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  SPI 配置主发送的电平
 **
 ** \param [in] 高低电平
 **
 ** \retval 无
 ** 
 ******************************************************************************/
void Spi_SetCS(en_spi_channel_t enCh,boolean_t bFlag) 
{
    ASSERT(IS_VALID_CH(enCh));
    if(Spi0 == enCh)
    {
       M0P_SPI0->SSN  = bFlag; 
    }
    else
    {
       M0P_SPI1->SSN  = bFlag; 
    }   
} 
/**
 ******************************************************************************
 ** \brief  SPI 发送一字节函数
 **
 ** \param [in] enCh通道，u8Data发送字节
 **
 ** \retval Ok发送成功
 ** 
 ******************************************************************************/
en_result_t Spi_SendData(en_spi_channel_t enCh,uint8_t u8Data)
{
    uint32_t u32TimeOut;
    ASSERT(IS_VALID_CH(enCh));
    u32TimeOut = 1000;
    if(Spi0 == enCh)
    {
        while(--u32TimeOut)
        {
            if(TRUE == M0P_SPI0->STAT_f.TXE)
            {
                break;
            }
        }
        if(u32TimeOut == 0)
        {
            return ErrorTimeout;
        }
        M0P_SPI0->DATA = u8Data;
        u32TimeOut = 1000;
        while(--u32TimeOut)
        {
            if(TRUE == M0P_SPI0->STAT_f.RXNE)
            {
                break;
            }
        }
        if(u32TimeOut == 0)
        {
            return ErrorTimeout;
        }
        u8Data = M0P_SPI0->DATA;
    }
    else
    {
        while(--u32TimeOut)
        {
            if(TRUE == M0P_SPI1->STAT_f.TXE)

            {
                break;
            }
        }
        if(u32TimeOut == 0)
        {
            return ErrorTimeout;
        }
        M0P_SPI1->DATA = u8Data;
        u32TimeOut = 1000;
        while(--u32TimeOut)
        {
            if(TRUE == M0P_SPI1->STAT_f.RXNE)
            {
                break;
            }
        }
        if(u32TimeOut == 0)
        {
            return ErrorTimeout;
        }
        u8Data = M0P_SPI1->DATA; 
    }
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  SPI 接收一字节函数
 **
 ** \param [in] enCh接收通道
 **
 ** \retval 接收一字节数据
 ** 
 ******************************************************************************/
uint8_t Spi_ReceiveData(en_spi_channel_t enCh,boolean_t bMasterOrSlave)
{
    uint8_t temp;
    ASSERT(IS_VALID_CH(enCh));
    if(Spi0 == enCh)
    {
        if(1 == bMasterOrSlave)
        {
          M0P_SPI0->DATA = 0x00;
        }
        while(0 == M0P_SPI0->STAT_f.RXNE){;}
        temp = M0P_SPI0->DATA;
    }
    else
    {
        if(1 == bMasterOrSlave)
        {
            M0P_SPI1->DATA = 0x00;
        }
        while(0 == M0P_SPI1->STAT_f.RXNE){;}
        temp = M0P_SPI1->DATA;
    }  
    return temp;
}

//@} // SpiGroup
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

