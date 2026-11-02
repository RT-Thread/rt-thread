/*************************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.    
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
/** \file uart.c
 **
 ** UART function driver API.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2017-05-17  1.0  CJ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "uart.h"
/**
 ******************************************************************************
 ** \addtogroup UartGroup
 ******************************************************************************/
//@{
/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/

#define IS_VALID_CH(x)          ((UARTCH0 == (x)) ||\
                                 (UARTCH1 == (x)))

#define IS_VALID_IRQSEL(x)      ((UartTxIrq == (x)) ||\
                                 (UartRxIrq == (x)) ||\
                                 (UartFEIrq == (x)) ||\
                                 (UartCtsIrq == (x))||\
                                 (UartPEIrq == (x)) ||\
                                 (UartTxEIrq == (x))) 

#define IS_VALID_MODE(x)        ((UartMode0==(x))||\
                                 (UartMode1==(x))||\
                                 (UartMode2==(x))||\
                                 (UartMode3==(x)))

#define IS_VALID_STATUS(x)      ((UartCts == (x))||\
                                 (UartRC == (x))||\
                                 (UartTC == (x))||\
                                 (UartPE == (x))||\
                                 (UartCtsIf == (x))||\
                                 (UartTxe == (x))||\
                                 (UartFE == (x)))
/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/
static stc_uart_instance_data_t* UartGetInternDataPtr(uint8_t u8Idx);
static void UartInitNvic(uint8_t u8Idx);
static void UartDeInitNvic(uint8_t u8Idx);
/******************************************************************************/
/* Local variable definitions ('static')                                       */
/******************************************************************************/
static stc_uart_instance_data_t m_astcUartInstanceDataLut[] =
{
    {
        UARTCH0,
        M0P_UART0,       /* pstcInstance */
        {NULL,NULL,NULL,NULL,NULL},     
    },
    {
        UARTCH1,
        M0P_UART1,       /* pstcInstance */
       {NULL,NULL,NULL,NULL,NULL},    
    },
};
/**
 ******************************************************************************
 ** \brief  UART0/1通道 相关地址获取
 **
 ** \param [in] u8Idx通道号
 **
 ** \retval 通道对应的地址结构
 **
 ******************************************************************************/
static stc_uart_instance_data_t* UartGetInternDataPtr(uint8_t u8Idx)
{
    stc_uart_instance_data_t* pstcData = NULL;
    uint8_t u8i = 0;
    for (u8i = 0; u8i < ARRAY_SZ(m_astcUartInstanceDataLut); u8i++)
    {
        if (u8Idx == m_astcUartInstanceDataLut[u8i].u32Idx)
        {
            pstcData = &m_astcUartInstanceDataLut[u8i];
            break;
        }
    }

    return (pstcData);
}
/**
 ******************************************************************************
 ** \brief  UART通信中断使能函数设置
 **
 ** \param [in] u8Idx通道号，enIrqSel发送or接收中断使能
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_EnableIrq(uint8_t u8Idx,
                           en_uart_irq_sel_t enIrqSel)
{
    stc_uart_instance_data_t* pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    ASSERT(IS_VALID_IRQSEL(enIrqSel));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    switch(enIrqSel)
    {
        case  UartTxIrq:
            pstcData->pstcInstance->SCON_f.TCIE  = 1u;
            break;
        case  UartRxIrq:
            pstcData->pstcInstance->SCON_f.RCIE  = 1u;
            break; 
        case  UartFEIrq:
            pstcData->pstcInstance->SCON_f.FEIE  = 1u;
            break;
        case  UartCtsIrq:
            pstcData->pstcInstance->SCON_f.CTSIE = 1u;
            break;
        case  UartPEIrq:
            pstcData->pstcInstance->SCON_f.PEIE  = 1u;
            break;
        case  UartTxEIrq:
            pstcData->pstcInstance->SCON_f.TXEIE = 1u;
            break;
        default:
            return (ErrorInvalidParameter);       
    }
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通信中断禁止函数设置
 **
 ** \param [in] u8Idx通道号，enIrqSel发送or接收中断禁止
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_DisableIrq(uint8_t u8Idx, 
                            en_uart_irq_sel_t enIrqSel)
{
    stc_uart_instance_data_t *pstcData = NULL;

    ASSERT(IS_VALID_CH(u8Idx));
    ASSERT(IS_VALID_IRQSEL(enIrqSel));
        
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    switch(enIrqSel)
    {
        case  UartTxIrq:
            pstcData->pstcInstance->SCON_f.TCIE  = 0u;
            break;
        case  UartRxIrq:
            pstcData->pstcInstance->SCON_f.RCIE  = 0u;
            break; 
        case  UartFEIrq:
            pstcData->pstcInstance->SCON_f.FEIE  = 0u;
            break;
        case  UartCtsIrq:
            pstcData->pstcInstance->SCON_f.CTSIE = 0u;
            break;
        case  UartPEIrq:
            pstcData->pstcInstance->SCON_f.PEIE  = 0u;
            break;
        case  UartTxEIrq:
            pstcData->pstcInstance->SCON_f.TXEIE = 0u;
            break;
        default:
            return (ErrorInvalidParameter);       
    }
    
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道4种模式配置
 **
 ** \param [in] u8Idx通道号，mode哪种模式
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_SetMode(uint8_t u8Idx,en_uart_mode_t enMode)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    ASSERT(IS_VALID_MODE(enMode));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    } 
    pstcData->pstcInstance->SCON_f.SM = enMode;
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道多主机模式配置
 **
 ** \param [in] u8Idx通道号，stcMultiConfig多主机模式结构
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_SetMultiMode(uint8_t u8Idx,stc_uart_multimode_t* pstcMultiConfig)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    if(NULL != pstcMultiConfig)
    {
        pstcData->pstcInstance->SCON_f.ADRDET = pstcMultiConfig->enMulti_mode;
        if(pstcMultiConfig->enMulti_mode == UartMulti)
        {
            pstcData->pstcInstance->SADDR = pstcMultiConfig->u8SlaveAddr;
            pstcData->pstcInstance->SADEN = pstcMultiConfig->u8SaddEn;
        }
    }
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道多主机模式发送数据/地址帧或者奇偶校验配置TB8
 **
 ** \param [in] u8Idx通道号，tb8数据or地址帧或者奇偶校验
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_SetMMDOrCk(uint8_t u8Idx,en_uart_mmdorck_t enTb8)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    pstcData->pstcInstance->SCON_f.B8CONT = enTb8;
    return Ok;
}
/**
 ******************************************************************************
 ** \brief 获取RB8数值
 **
 ** \param [in] u8Idx通道号
 **
 ** \retval RB8
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
boolean_t Uart_GetRb8(uint8_t u8Idx)
{
     stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    return (pstcData->pstcInstance->SBUF_f.DATA8);
}
/**
 ******************************************************************************
 ** \brief  UART通道多主机模式从机地址配置函数
 **
 ** \param [in] u8Idx通道号，addr地址
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_SetSaddr(uint8_t u8Idx,uint8_t u8Addr)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    pstcData->pstcInstance->SADDR = u8Addr;
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道多主机模式从机掩码配置函数
 **
 ** \param [in] u8Idx通道号，addren地址掩码
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_SetSaddrEn(uint8_t u8Idx,uint8_t u8Addren)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    pstcData->pstcInstance->SADEN = u8Addren;
    return Ok;  
}
/**
 ******************************************************************************
 ** \brief  UART通道停止位长度设置
 **
 ** \param [in] u8Idx通道号，u8Len停止位长度
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_SetStopBit(uint8_t u8Idx,uint8_t u8Len)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    switch(u8Len)
    {
        case Uart1bit:
        case Uart15bit:
        case Uart2bit:
           pstcData->pstcInstance->SCON_f.STOPBIT =  u8Len;
           break;
        default:
            return ErrorInvalidParameter;
    }
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART采样频率配置
 **
 ** \param [in] u8Idx通道号，u8Div采样频率
 **
 ** \retval OK配置成功
 ******************************************************************************/
en_result_t Uart_SetClkDiv(uint8_t u8Idx,en_uart_clkdiv_t enClkDiv)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    pstcData->pstcInstance->SCON_f.OVER = enClkDiv;
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道波特率配置值计算
 **
 ** \param [in] u8Idx通道号，pstcBaud波特率，
 **
 ** \retval 定时器配置值
 ** \retval 0,获取值失败,u16Scnt波特率设置值
 ******************************************************************************/
uint16_t Uart_CalScnt(uint8_t u8Idx,stc_uart_baud_t *pstcBaud)
{
    stc_uart_instance_data_t *pstcData = NULL;
	uint16_t u16Scnt = 0;
    uint8_t u8Over = 0;
    ASSERT(IS_VALID_CH(u8Idx));

    pstcData = UartGetInternDataPtr(u8Idx);
    u8Over = pstcData->pstcInstance->SCON_f.OVER;
    if(UartMode0 == pstcBaud->enRunMode)
    {
        return 0;//test
    }
    if((UartMode1 == pstcBaud->enRunMode)||(UartMode3 == pstcBaud->enRunMode))
    {
        if(0 == u8Over)
        {
            u8Over = 16;
        }
        else
        {
            u8Over = 8;
        }
            
        u16Scnt = pstcBaud->u32Pclk/(pstcBaud->u32Baud*u8Over);
    }
    else
    {
        if(0 == u8Over)
        {
            u8Over = 32;
        }
        else
        {
            u8Over = 16;
        } 
       u16Scnt = pstcBaud->u32Pclk/u8Over; 
    }   
    return u16Scnt;
}
/**
 ******************************************************************************
 ** \brief  UART通道波特率配置
 **
 ** \param [in] u8Idx通道号，u16Scnt波特率设置
 **
 ** \retval 定时器配置值
 ** \retval 0,获取值失败
 ******************************************************************************/
en_result_t Uart_SetBaud(uint8_t u8Idx,uint16_t u16Scnt)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    pstcData->pstcInstance->SCNT = u16Scnt;
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UART通道波特率获取
 **
 ** \param [in] u8Idx通道号,u8Mode工作模式
 **
 ** \retval 波特率
 ******************************************************************************/
uint32_t Uart_GetBaud(uint8_t u8Idx,uint8_t u8Mode,uint32_t u32Pclk)
{
    stc_uart_instance_data_t *pstcData = NULL;
	uint32_t u32Baud = 0;
    uint8_t u8Over = 0;
	uint16_t u16Scnt = 0;
    ASSERT(IS_VALID_CH(u8Idx)); 
    pstcData = UartGetInternDataPtr(u8Idx);       
    u16Scnt = pstcData->pstcInstance->SCNT;
    
    switch(u8Mode)
    {
        case UartMode0:
            u32Baud = u32Pclk/12;
            break;
        case UartMode1:
        case UartMode3:
            if(0 == pstcData->pstcInstance->SCON_f.OVER)
            {
                u8Over = 16;
            }
            else
            {
                u8Over = 8;
            }
            u32Baud = u32Pclk/(u8Over*u16Scnt);
            break;
        case UartMode2:
            if(0 == pstcData->pstcInstance->SCON_f.OVER)
            {
                u8Over = 32;
            }
            else
            {
                u8Over = 16;
            }
            u32Baud = u32Pclk/u8Over;
            break;
        default :
          return 0;//test
    }
    return u32Baud;
}
/**
 ******************************************************************************
 ** \brief  UART通道发送或接收等功能使能设置
 **
 ** \param [in] u8Idx通道号，enFunc功能
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_EnableFunc(uint8_t u8Idx, en_uart_func_t enFunc)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    switch(enFunc)
    {
        case UartTx:
        case UartRx:
            pstcData->pstcInstance->SCON_f.REN = 1u;
            break;
        case UartDmaTx:
            pstcData->pstcInstance->SCON_f.DMATXEN = 1u;
            break;
        case UartDmaRx:
            pstcData->pstcInstance->SCON_f.DMARXEN = 1u;
            break;
        case UartCtsRts:
            pstcData->pstcInstance->SCON_f.CTSEN = 1u;
            pstcData->pstcInstance->SCON_f.RTSEN = 1u;
            break;
        default:
            return ErrorInvalidParameter;
    }
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道发送或接收等功能禁止设置
 **
 ** \param [in] u8Idx通道号，enFunc功能
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_DisableFunc(uint8_t u8Idx, en_uart_func_t enFunc)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    switch(enFunc)
    {
        case UartTx:
        case UartRx:
            pstcData->pstcInstance->SCON_f.REN = 0u;
            break;
        case UartDmaTx:
            pstcData->pstcInstance->SCON_f.DMATXEN = 0u;
            break;
        case UartDmaRx:
            pstcData->pstcInstance->SCON_f.DMARXEN = 0u;
            break;
        case UartCtsRts:
            pstcData->pstcInstance->SCON_f.CTSEN = 0u;
            pstcData->pstcInstance->SCON_f.RTSEN = 0u;
            break;
        default:
            return ErrorInvalidParameter;
    }
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道通信状态获取
 **
 ** \param [in] u8Idx通道号
 **
 ** \retval 状态值
 ******************************************************************************/
uint8_t Uart_GetIsr(uint8_t u8Idx)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    return (pstcData->pstcInstance->ISR);
}
/**
 ******************************************************************************
 ** \brief  UART通道通信状态获取
 **
 ** \param [in] u8Idx通道号，enStatus获取哪个状态
 **
 ** \retval 状态值
 **\retval ErrorInvalidParameter获取失败
 ******************************************************************************/
boolean_t Uart_GetStatus(uint8_t u8Idx,en_uart_status_t enStatus)
{
    boolean_t bStatus=FALSE;
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    ASSERT(IS_VALID_STATUS(enStatus));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;//4，用户只需判断0或1
    }
    switch(enStatus)
    {
        case UartCts:
            bStatus = (pstcData->pstcInstance->ISR_f.CTS == 1) ? TRUE : FALSE;
            break;
        case UartRC:
            bStatus = (pstcData->pstcInstance->ISR_f.RC == 1) ? TRUE : FALSE;
            break;
        case UartTC:
            bStatus = (pstcData->pstcInstance->ISR_f.TC == 1) ? TRUE : FALSE;
            break;
        case UartPE:
            bStatus = (pstcData->pstcInstance->ISR_f.PE == 1) ? TRUE : FALSE;
            break;
        case UartFE:
            bStatus = (pstcData->pstcInstance->ISR_f.FE == 1) ? TRUE : FALSE;
            break;
        case UartCtsIf:
            bStatus = (pstcData->pstcInstance->ISR_f.CTSIF == 1) ? TRUE : FALSE;
            break;
        case UartTxe:
            bStatus = (pstcData->pstcInstance->ISR_f.TXE == 1) ? TRUE : FALSE;
            break;
        default:
            break; 
    }
    return bStatus;
}
/**
 ******************************************************************************
 ** \brief  UART通道通信状态清除
 **
 ** \param [in] u8Idx通道号
 **
 ** \retval OK
 ******************************************************************************/
en_result_t Uart_ClrIsr(uint8_t u8Idx)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    pstcData->pstcInstance->ICR = 0u;
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道通信状态清除
 **
 ** \param [in] u8Idx通道号，enStatus清除哪个状态
 **
 ** \retval 状态值
 **\retval ErrorInvalidParameter清除失败
 ******************************************************************************/
en_result_t Uart_ClrStatus(uint8_t u8Idx,en_uart_status_t enStatus)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    ASSERT(IS_VALID_STATUS(enStatus));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    switch(enStatus)
    {
        case UartCts:
            pstcData->pstcInstance->ICR_f.CTSIFCF = 0;
            break;
        case UartRC:
            pstcData->pstcInstance->ICR_f.RCCF = 0;
            break;
        case UartTC:
            pstcData->pstcInstance->ICR_f.TCCF = 0;
            break;
        case UartPE:
            pstcData->pstcInstance->ICR_f.PECF = 0;
            break;
        case UartFE:
            pstcData->pstcInstance->ICR_f.FECF = 0;
            break;   
        default:
            break; 
    }
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道发送数据函数,查询方式调用此函数，中断方式发送不适用
 **
 ** \param [in] u8Idx通道号，Data发送数据
 **
 ** \retval Ok发送成功
 **\retval ErrorInvalidParameter发送失败
 ******************************************************************************/
en_result_t Uart_SendData(uint8_t u8Idx, uint8_t u8Data)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    while(FALSE == Uart_GetStatus(u8Idx, UartTxe))
    {}
    pstcData->pstcInstance->SBUF_f.DATA = u8Data;    
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道接收数据函数
 **
 ** \param [in] u8Idx通道号
 **
 ** \retval 接收数据
 **\retval ErrorInvalidParameter接收失败
 ******************************************************************************/
int Uart_ReceiveData(uint8_t u8Idx)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return -1;
    }
    return (pstcData->pstcInstance->SBUF_f.DATA);
}
/**
 ******************************************************************************
 ** \brief  UART通道中断处理函数
 **
 ** \param [in] u8Param通道号
 **
 ** \retval 无
 **
 ******************************************************************************/
void Uart_IRQHandler(uint8_t u8Param)
{
    stc_uart_instance_data_t *pstcData = NULL;
    pstcData = UartGetInternDataPtr(u8Param);
    if (NULL == pstcData)
    {
        return;
    }
    if(1 == pstcData->pstcInstance->ISR_f.FE)
    {
        Uart_ClrStatus(u8Param,UartFE);
        if(NULL != pstcData->stcUartInternIrqCb.pfnRxFEIrqCb)
        {
            pstcData->stcUartInternIrqCb.pfnRxFEIrqCb();
        }
        return;//帧出错则不进行后续数据处理
    }
    if(1 == pstcData->pstcInstance->ISR_f.PE)
    {
        Uart_ClrStatus(u8Param,UartPE);
        if(NULL != pstcData->stcUartInternIrqCb.pfnPEIrqCb)
        {
            pstcData->stcUartInternIrqCb.pfnPEIrqCb();
        }
        return;//若奇偶校验出错则不进行后续数据处理
    }
    if(1 == pstcData->pstcInstance->ISR_f.CTSIF)
    {
        Uart_ClrStatus(u8Param,UartCts);
        if(NULL != pstcData->stcUartInternIrqCb.pfnCtsIrqCb)
        {
            pstcData->stcUartInternIrqCb.pfnCtsIrqCb();
        }
    }
    if(1 == pstcData->pstcInstance->ISR_f.RC)
    {
        Uart_ClrStatus(u8Param,UartRC);
        if(NULL != pstcData->stcUartInternIrqCb.pfnRxIrqCb)
        {
            pstcData->stcUartInternIrqCb.pfnRxIrqCb();
        }
    }
    if(1 == pstcData->pstcInstance->ISR_f.TC)
    {
        Uart_ClrStatus(u8Param,UartTC);
        if(NULL != pstcData->stcUartInternIrqCb.pfnTxIrqCb)
        {
            pstcData->stcUartInternIrqCb.pfnTxIrqCb();
        }
    }
}
/**
 ******************************************************************************
 ** \brief  UART通道使能内核NVIC中断
 **
 ** \param [in] u8Idx通道号
 **
 ** \retval 无
 **
 ******************************************************************************/
static void UartInitNvic(uint8_t u8Idx)
{
    IRQn_Type enIrqIndex;
    
    ASSERT(IS_VALID_CH(u8Idx));;
    enIrqIndex = (IRQn_Type)(UART0_IRQn + u8Idx);
    NVIC_ClearPendingIRQ(enIrqIndex);
    NVIC_SetPriority(enIrqIndex,IrqLevel3);
    NVIC_EnableIRQ(enIrqIndex);
    
}
/**
 ******************************************************************************
 ** \brief  UART通道禁止内核NVIC中断
 **
 ** \param [in] u8Idx通道号
 **
 ** \retval 无
 **
 ******************************************************************************/
static void UartDeInitNvic(uint8_t u8Idx)
{
    IRQn_Type enIrqIndex;

    ASSERT(IS_VALID_CH(u8Idx));
    enIrqIndex = (IRQn_Type)(UART0_IRQn + u8Idx);
    NVIC_ClearPendingIRQ(enIrqIndex);
    NVIC_SetPriority(enIrqIndex,IrqLevel3);
    NVIC_DisableIRQ(enIrqIndex);
    
}
/**
 ******************************************************************************
 ** \brief  UART通道初始化函数
 **
 ** \param [in] u8Idx通道号，pstcConfig初始化结构体
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_Init(uint8_t u8Idx, 
                      stc_uart_config_t* pstcConfig)
{
    en_result_t enRet = Error;
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    if(NULL == pstcConfig)
    {
        return ErrorInvalidParameter;
    }
    enRet = Uart_SetMode(u8Idx,pstcConfig->enRunMode);
    enRet = Uart_SetStopBit(u8Idx,pstcConfig->enStopBit);
    if(NULL != pstcConfig->pstcMultiMode)
    {
        enRet = Uart_SetMultiMode(u8Idx,pstcConfig->pstcMultiMode);
    }
    if(NULL != pstcConfig->pstcIrqCb)
    {
        pstcData->stcUartInternIrqCb.pfnRxFEIrqCb = pstcConfig->pstcIrqCb->pfnRxFEIrqCb;
        pstcData->stcUartInternIrqCb.pfnRxIrqCb = pstcConfig->pstcIrqCb->pfnRxIrqCb;
        pstcData->stcUartInternIrqCb.pfnTxIrqCb = pstcConfig->pstcIrqCb->pfnTxIrqCb;
        pstcData->stcUartInternIrqCb.pfnCtsIrqCb = pstcConfig->pstcIrqCb->pfnCtsIrqCb;
        pstcData->stcUartInternIrqCb.pfnPEIrqCb = pstcConfig->pstcIrqCb->pfnPEIrqCb;
    }
    if(pstcConfig->bTouchNvic == TRUE)
    {
        UartInitNvic(u8Idx);
    }
    else
    {
        UartDeInitNvic(u8Idx);
    }
    enRet = Ok;
    return enRet;
}
//@} // UartGroup      
