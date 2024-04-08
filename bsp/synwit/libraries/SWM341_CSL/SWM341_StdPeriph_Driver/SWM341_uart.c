/******************************************************************************************************************************************
* 文件名称: SWM341_uart.c
* 功能说明: SWM341单片机的UART串口功能驱动库
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项: 没有编写LIN功能相关的函数
* 版本日期: V1.0.0      2016年1月30日
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
#include "SWM341_uart.h"


/******************************************************************************************************************************************
* 函数名称: UART_Init()
* 功能说明: UART串口初始化
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*           UART_InitStructure * initStruct    包含UART串口相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_Init(UART_TypeDef * UARTx, UART_InitStructure * initStruct)
{
    switch((uint32_t)UARTx)
    {
    case ((uint32_t)UART0):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_UART0_Pos);
        break;

    case ((uint32_t)UART1):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_UART1_Pos);
        break;

    case ((uint32_t)UART2):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_UART2_Pos);
        break;

    case ((uint32_t)UART3):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_UART3_Pos);
        break;
    }

    UART_Close(UARTx);  //一些关键寄存器只能在串口关闭时设置

    UARTx->BAUD &= ~(UART_BAUD_BAUD_Msk | UART_BAUD_FRAC_Msk);
    UARTx->BAUD |= (((SystemCoreClock/initStruct->Baudrate - 1) / 16) << UART_BAUD_BAUD_Pos) |
                   (((SystemCoreClock/initStruct->Baudrate - 1) % 16) << UART_BAUD_FRAC_Pos);

    UARTx->CTRL &= ~(UART_CTRL_DATA9b_Msk | UART_CTRL_PARITY_Msk | UART_CTRL_STOP2b_Msk);
    UARTx->CTRL |= (initStruct->DataBits << UART_CTRL_DATA9b_Pos) |
                   (initStruct->Parity   << UART_CTRL_PARITY_Pos) |
                   (initStruct->StopBits << UART_CTRL_STOP2b_Pos);

    UARTx->FIFO &= ~(UART_FIFO_RXTHR_Msk | UART_FIFO_TXTHR_Msk);
    UARTx->FIFO |= (initStruct->RXThreshold << UART_FIFO_RXTHR_Pos) |
                   (initStruct->TXThreshold << UART_FIFO_TXTHR_Pos);

    UARTx->TOCR &= ~UART_TOCR_TIME_Msk;
    UARTx->TOCR |= (1 << UART_TOCR_MODE_Pos) |
                   (initStruct->TimeoutTime << UART_TOCR_TIME_Pos);

    UARTx->CTRL &= ~(UART_CTRL_RXIE_Msk | UART_CTRL_TXIE_Msk | UART_CTRL_TOIE_Msk);
    UARTx->CTRL |= (initStruct->RXThresholdIEn << UART_CTRL_RXIE_Pos) |
                   (initStruct->TXThresholdIEn << UART_CTRL_TXIE_Pos) |
                   (initStruct->TimeoutIEn << UART_CTRL_TOIE_Pos);

    switch((uint32_t)UARTx)
    {
    case ((uint32_t)UART0):
        if(initStruct->RXThresholdIEn | initStruct->TXThresholdIEn | initStruct->TimeoutIEn)
        {
            NVIC_EnableIRQ(UART0_IRQn);
        }
        else
        {
            NVIC_DisableIRQ(UART0_IRQn);
        }
        break;

    case ((uint32_t)UART1):
        if(initStruct->RXThresholdIEn | initStruct->TXThresholdIEn | initStruct->TimeoutIEn)
        {
            NVIC_EnableIRQ(UART1_IRQn);
        }
        else
        {
            NVIC_DisableIRQ(UART1_IRQn);
        }
        break;

    case ((uint32_t)UART2):
        if(initStruct->RXThresholdIEn | initStruct->TXThresholdIEn | initStruct->TimeoutIEn)
        {
            NVIC_EnableIRQ(UART2_IRQn);
        }
        else
        {
            NVIC_DisableIRQ(UART2_IRQn);
        }
        break;

    case ((uint32_t)UART3):
        if(initStruct->RXThresholdIEn | initStruct->TXThresholdIEn | initStruct->TimeoutIEn)
        {
            NVIC_EnableIRQ(UART3_IRQn);
        }
        else
        {
            NVIC_DisableIRQ(UART3_IRQn);
        }
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: UART_Open()
* 功能说明: UART串口打开
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_Open(UART_TypeDef * UARTx)
{
    UARTx->CTRL |= (0x01 << UART_CTRL_EN_Pos);
}

/******************************************************************************************************************************************
* 函数名称: UART_Close()
* 功能说明: UART串口关闭
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_Close(UART_TypeDef * UARTx)
{
    UARTx->CTRL &= ~(0x01 << UART_CTRL_EN_Pos);
}

/******************************************************************************************************************************************
* 函数名称: UART_WriteByte()
* 功能说明: 发送一个字节数据
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，可取值包括UART0、UART1、UART2、UART3、UART4
*           uint8_t data            要发送的字节
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_WriteByte(UART_TypeDef * UARTx, uint8_t data)
{
    UARTx->DATA = data;
}

/******************************************************************************************************************************************
* 函数名称: UART_ReadByte()
* 功能说明: 读取一个字节数据，并指出数据是否Valid
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，可取值包括UART0、UART1、UART2、UART3、UART4
*           uint32_t * data         接收到的数据
* 输    出: uint32_t              0 无错误    UART_ERR_PARITY 奇偶校验错误
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_ReadByte(UART_TypeDef * UARTx, uint32_t * data)
{
    uint32_t reg = UARTx->DATA;

    *data = (reg & UART_DATA_DATA_Msk);

    if(reg & UART_DATA_PAERR_Msk) return UART_ERR_PARITY;

    return 0;
}

/******************************************************************************************************************************************
* 函数名称: UART_IsTXBusy()
* 功能说明: UART是否正在发送数据
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t              1 UART正在发送数据    0 数据已发完
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_IsTXBusy(UART_TypeDef * UARTx)
{
    return (UARTx->CTRL & UART_CTRL_TXIDLE_Msk) ? 0 : 1;
}

/******************************************************************************************************************************************
* 函数名称: UART_IsRXFIFOEmpty()
* 功能说明: 接收FIFO是否为空，如果不空则说明其中有数据可以读取
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t              1 接收FIFO空    0 接收FIFO非空
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_IsRXFIFOEmpty(UART_TypeDef * UARTx)
{
    return (UARTx->CTRL & UART_CTRL_RXNE_Msk) ? 0 : 1;
}

/******************************************************************************************************************************************
* 函数名称: UART_IsTXFIFOFull()
* 功能说明: 发送FIFO是否为满，如果不满则可以继续向其中写入数据
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t              1 发送FIFO满    0 发送FIFO不满
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_IsTXFIFOFull(UART_TypeDef * UARTx)
{
    return (UARTx->CTRL & UART_CTRL_TXFF_Msk) ? 1 : 0;
}

/******************************************************************************************************************************************
* 函数名称: UART_SetBaudrate()
* 功能说明: 设置波特率
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*           uint32_t baudrate       要设置的波特率
* 输    出: 无
* 注意事项: 不要在串口工作时更改波特率，使用此函数前请先调用UART_Close()关闭串口
******************************************************************************************************************************************/
void UART_SetBaudrate(UART_TypeDef * UARTx, uint32_t baudrate)
{
    UARTx->BAUD &= ~(UART_BAUD_BAUD_Msk | UART_BAUD_FRAC_Msk);
    UARTx->BAUD |= (((SystemCoreClock/baudrate - 1) / 16) << UART_BAUD_BAUD_Pos) |
                   (((SystemCoreClock/baudrate - 1) % 16) << UART_BAUD_FRAC_Pos);
}

/******************************************************************************************************************************************
* 函数名称: UART_GetBaudrate()
* 功能说明: 查询波特率
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t              当前波特率
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_GetBaudrate(UART_TypeDef * UARTx)
{
    return SystemCoreClock/(((UARTx->BAUD & UART_BAUD_BAUD_Msk) >> UART_BAUD_BAUD_Pos) * 16 +
                            ((UARTx->BAUD & UART_BAUD_FRAC_Msk) >> UART_BAUD_FRAC_Pos) + 1);
}

/******************************************************************************************************************************************
* 函数名称: UART_CTSConfig()
* 功能说明: UART CTS流控配置
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*           uint32_t enable         1 使能CTS流控    0 禁止CTS流控
*           uint32_t polarity       0 CTS输入为低表示可以发送数据    1 CTS输入为高表示可以发送数据
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_CTSConfig(UART_TypeDef * UARTx, uint32_t enable, uint32_t polarity)
{
    UARTx->CTSCR &= ~(UART_CTSCR_EN_Msk | UART_CTSCR_POL_Msk);
    UARTx->CTSCR |= (enable   << UART_CTSCR_EN_Pos) |
                    (polarity << UART_CTSCR_POL_Pos);
}

/******************************************************************************************************************************************
* 函数名称: UART_CTSLineState()
* 功能说明: UART CTS线当前状态
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t              0 CTS线当前为低电平    1 CTS线当前为高电平
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_CTSLineState(UART_TypeDef * UARTx)
{
    return (UARTx->CTSCR & UART_CTSCR_STAT_Msk) ? 1 : 0;
}

/******************************************************************************************************************************************
* 函数名称: UART_RTSConfig()
* 功能说明: UART RTS流控配置
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*           uint32_t enable         1 使能RTS流控    0 禁止RTS流控
*           uint32_t polarity       0 RTS输出低表示可以接收数据    1 RTS输出高表示可以接收数据
*           uint32_t threshold      RTS流控的触发阈值，可取值UART_RTS_1BYTE、UART_RTS_2BYTE、UART_RTS_4BYTE、UART_RTS_6BYTE
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_RTSConfig(UART_TypeDef * UARTx, uint32_t enable, uint32_t polarity, uint32_t threshold)
{
    UARTx->RTSCR &= ~(UART_RTSCR_EN_Msk | UART_RTSCR_POL_Msk | UART_RTSCR_THR_Msk);
    UARTx->RTSCR |= (enable    << UART_RTSCR_EN_Pos)  |
                    (polarity  << UART_RTSCR_POL_Pos) |
                    (threshold << UART_RTSCR_THR_Pos);
}

/******************************************************************************************************************************************
* 函数名称: UART_RTSLineState()
* 功能说明: UART RTS线当前状态
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t              0 RTS线当前为低电平    1 RTS线当前为高电平
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_RTSLineState(UART_TypeDef * UARTx)
{
    return (UARTx->RTSCR & UART_RTSCR_STAT_Msk) ? 1 : 0;
}

/******************************************************************************************************************************************
* 函数名称: UART_LINConfig()
* 功能说明: UART LIN功能配置
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*           uint32_t detectedLen    检测到Break需要的低电平长度（位数），取值1--16
*           uint32_t detectedIEn    检测到Break中断使能
*           uint32_t generatedLen   Break发送低电平长度，取值1--15
*           uint32_t generatedIEn   Break发送完成中断使能
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_LINConfig(UART_TypeDef * UARTx, uint32_t detectedLen, uint32_t detectedIEn, uint32_t generatedLen, uint32_t generatedIEn)
{
    UARTx->CFG &= ~(UART_CFG_BRKTXLEN_Msk | UART_CFG_BRKRXLEN_Msk);
    UARTx->CFG |= ((detectedLen-1) << UART_CFG_BRKRXLEN_Pos) |
                  (generatedLen    << UART_CFG_BRKTXLEN_Pos);
    UARTx->LINCR &= ~(UART_LINCR_BRKDETIE_Msk | UART_LINCR_GENBRKIE_Msk);
    UARTx->LINCR |= (detectedIEn  << UART_LINCR_BRKDETIE_Pos) |
                    (generatedIEn << UART_LINCR_GENBRKIE_Pos);
}

/******************************************************************************************************************************************
* 函数名称: UART_LINGenerate()
* 功能说明: UART LIN产生/发送Break
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_LINGenerate(UART_TypeDef * UARTx)
{
    UARTx->LINCR |= (1 << UART_LINCR_GENBRK_Pos);
}

/******************************************************************************************************************************************
* 函数名称: UART_LINIsDetected()
* 功能说明: UART LIN是否检测到Break
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t              1 检测到LIN Break    0 未检测到LIN Break
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_LINIsDetected(UART_TypeDef * UARTx)
{
    return (UARTx->LINCR & UART_LINCR_BRKDETIF_Msk) ? 1 : 0;
}

/******************************************************************************************************************************************
* 函数名称: UART_LINIsGenerated()
* 功能说明: UART LIN Break是否发送完成
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t              1 LIN Break 发送完成    0 LIN Break发送未完成
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_LINIsGenerated(UART_TypeDef * UARTx)
{
    return (UARTx->LINCR & UART_LINCR_GENBRKIF_Msk) ? 1 : 0;
}

/******************************************************************************************************************************************
* 函数名称: UART_ABRStart()
* 功能说明: UART 自动波特率检测开始
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*           uint32_t detectChar     用于自动检测、计算波特率的检测字符
*                                   8位数据时可取值：0xFF、0xFE、0xF8、0x80，分别表示发送方必须发送0xFF、0xFE、0xF8、0x80
*                                   9位数据时可取值：0x1FF、0x1FE、0x1F8、0x180，分别表示发送方必须发送0x1FF、0x1FE、0x1F8、0x180
* 输    出: 无
* 注意事项: 自动波特率检测时不能开启奇偶校验
******************************************************************************************************************************************/
void UART_ABRStart(UART_TypeDef * UARTx, uint32_t detectChar)
{
    uint32_t bits = 0;

    if((detectChar == 0xFF) || (detectChar == 0x1FF))      bits = 0;
    else if((detectChar == 0xFE) || (detectChar == 0x1FE)) bits = 1;
    else if((detectChar == 0xF8) || (detectChar == 0x1F8)) bits = 2;
    else if((detectChar == 0x80) || (detectChar == 0x180)) bits = 3;
    else while(1);

    UARTx->BAUD &= ~(UART_BAUD_ABREN_Msk | UART_BAUD_ABRBIT_Msk);
    UARTx->BAUD |= (1    << UART_BAUD_ABREN_Pos) |
                   (bits << UART_BAUD_ABRBIT_Pos);
}

/******************************************************************************************************************************************
* 函数名称: UART_ABRIsDone()
* 功能说明: UART 自动波特率是否完成
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t              0 未完成    UART_ABR_RES_OK 已完成，且成功    UART_ABR_RES_ERR 已完成，但失败、出错
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_ABRIsDone(UART_TypeDef * UARTx)
{
    if(UARTx->BAUD & UART_BAUD_ABREN_Msk)
    {
        return 0;
    }
    else if(UARTx->BAUD & UART_BAUD_ABRERR_Msk)
    {
        return UART_ABR_RES_ERR;
    }
    else
    {
        return UART_ABR_RES_OK;
    }
}

/******************************************************************************************************************************************
* 函数名称: UART_INTEn()
* 功能说明: 中断使能
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*           uint32_t it             interrupt type，有效值有 UART_IT_RX_THR、UART_IT_RX_TOUT、UART_IT_TX_THR、UART_IT_TX_DONE 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_INTEn(UART_TypeDef * UARTx, uint32_t it)
{
    UARTx->CTRL |= it;
}

/******************************************************************************************************************************************
* 函数名称: UART_INTDis()
* 功能说明: 中断禁止
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*           uint32_t it             interrupt type，有效值有 UART_IT_RX_THR、UART_IT_RX_TOUT、UART_IT_TX_THR、UART_IT_TX_DONE 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_INTDis(UART_TypeDef * UARTx, uint32_t it)
{
    UARTx->CTRL &= ~it;
}

/******************************************************************************************************************************************
* 函数名称: UART_INTClr()
* 功能说明: 中断标志清除
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*           uint32_t it             interrupt type，有效值有 UART_IT_RX_TOUT
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_INTClr(UART_TypeDef * UARTx, uint32_t it)
{
    if(it & UART_IT_RX_TOUT)
        UARTx->TOCR |= UART_TOCR_IFCLR_Msk;
}

/******************************************************************************************************************************************
* 函数名称: UART_INTStat()
* 功能说明: 中断状态查询
* 输    入: UART_TypeDef * UARTx  指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*           uint32_t it             interrupt type，有效值有 UART_IT_RX_THR、UART_IT_RX_TOUT、UART_IT_TX_THR、UART_IT_TX_DONE 及其“或”
* 输    出: uint32_t              1 中断已发生    0 中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_INTStat(UART_TypeDef * UARTx, uint32_t it)
{
    return (((it & UART_IT_RX_THR)  && (UARTx->BAUD & UART_BAUD_RXIF_Msk)) ||
            ((it & UART_IT_RX_TOUT) && (UARTx->BAUD & UART_BAUD_TOIF_Msk)) ||
            ((it & UART_IT_TX_THR)  && (UARTx->BAUD & UART_BAUD_TXIF_Msk)) ||
            ((it & UART_IT_TX_DONE) && (UARTx->BAUD & UART_BAUD_TXDOIF_Msk)));
}
