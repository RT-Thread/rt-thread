/****************************************************************************************************************************************** 
* 文件名称:	SWM320_uart.c
* 功能说明:	SWM320单片机的UART串口功能驱动库
* 技术支持:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项: 没有编写LIN功能相关的函数
* 版本日期:	V1.1.0		2017年10月25日
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
#include "SWM320.h"
#include "SWM320_uart.h"


/****************************************************************************************************************************************** 
* 函数名称:	UART_Init()
* 功能说明:	UART串口初始化
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*			UART_InitStructure * initStruct    包含UART串口相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_Init(UART_TypeDef * UARTx, UART_InitStructure * initStruct)
{	
	switch((uint32_t)UARTx)
	{
	case ((uint32_t)UART0):
		SYS->CLKEN |= (0x01 << SYS_CLKEN_UART0_Pos);
		break;
	
	case ((uint32_t)UART1):
		SYS->CLKEN |= (0x01 << SYS_CLKEN_UART1_Pos);
		break;
	
	case ((uint32_t)UART2):
		SYS->CLKEN |= (0x01 << SYS_CLKEN_UART2_Pos);
		break;
	
	case ((uint32_t)UART3):
		SYS->CLKEN |= (0x01 << SYS_CLKEN_UART3_Pos);
		break;
	}
	
	UART_Close(UARTx);	//一些关键寄存器只能在串口关闭时设置
	
	UARTx->CTRL |= (0x01 << UART_CTRL_BAUDEN_Pos);
	UARTx->BAUD &= ~UART_BAUD_BAUD_Msk;
	UARTx->BAUD |= ((SystemCoreClock/16/initStruct->Baudrate - 1) << UART_BAUD_BAUD_Pos);
	
	UARTx->CTRL &= ~(UART_CTRL_DATA9b_Msk | UART_CTRL_PARITY_Msk | UART_CTRL_STOP2b_Msk);
	UARTx->CTRL |= (initStruct->DataBits << UART_CTRL_DATA9b_Pos) |
				   (initStruct->Parity   << UART_CTRL_PARITY_Pos) |
				   (initStruct->StopBits << UART_CTRL_STOP2b_Pos);
	
	/* 在SWM320中，当 RXLVL >= RXTHR 时触发中断，如果RXTHR设置为0的话，在未接收到数据时就会一直触发中断；
	   其他芯片中，当 RXLVL >  RXTHR 时触发中断，为解决SWM320中RXTHR不能为0的问题，并统一库函数API，这里将RXTHR设置值加一
	*/
	switch((uint32_t)UARTx)  // 软件复位不能清零 NVIC 寄存器，若不手动清除，下面的代码清零 RXTHR 时会导致一直进入 ISR
    {
    case ((uint32_t)UART0):  NVIC_DisableIRQ(UART0_IRQn);  break;
    case ((uint32_t)UART1):  NVIC_DisableIRQ(UART1_IRQn);  break;
    case ((uint32_t)UART2):  NVIC_DisableIRQ(UART2_IRQn);  break;
    case ((uint32_t)UART3):  NVIC_DisableIRQ(UART3_IRQn);  break;
    }
	UARTx->FIFO &= ~(UART_FIFO_RXTHR_Msk | UART_FIFO_TXTHR_Msk);
	UARTx->FIFO |= ((initStruct->RXThreshold + 1) << UART_FIFO_RXTHR_Pos) | 
				   (initStruct->TXThreshold << UART_FIFO_TXTHR_Pos);
	
	UARTx->CTRL &= ~UART_CTRL_TOTIME_Msk;
	UARTx->CTRL |= (initStruct->TimeoutTime << UART_CTRL_TOTIME_Pos);
	
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
* 函数名称:	UART_Open()
* 功能说明:	UART串口打开
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_Open(UART_TypeDef * UARTx)
{
	UARTx->CTRL |= (0x01 << UART_CTRL_EN_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_Close()
* 功能说明:	UART串口关闭
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_Close(UART_TypeDef * UARTx)
{
	UARTx->CTRL &= ~(0x01 << UART_CTRL_EN_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_WriteByte()
* 功能说明:	发送一个字节数据
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，可取值包括UART0、UART1、UART2、UART3、UART4
*			uint32_t data			要发送的字节			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_WriteByte(UART_TypeDef * UARTx, uint32_t data)
{
	UARTx->DATA = data;
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_ReadByte()
* 功能说明:	读取一个字节数据，并指出数据是否Valid
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，可取值包括UART0、UART1、UART2、UART3、UART4
*			uint32_t * data			接收到的数据
* 输    出: uint32_t				0 无错误    UART_ERR_PARITY 奇偶校验错误
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
* 函数名称:	UART_IsTXBusy()
* 功能说明:	UART是否正在发送数据
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t				1 UART正在发送数据    0 数据已发完
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_IsTXBusy(UART_TypeDef * UARTx)
{
	return (UARTx->CTRL & UART_CTRL_TXIDLE_Msk) ? 0 : 1;
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_IsRXFIFOEmpty()
* 功能说明:	接收FIFO是否为空，如果不空则说明其中有数据可以读取
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t				1 接收FIFO空    0 接收FIFO非空
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_IsRXFIFOEmpty(UART_TypeDef * UARTx)
{
	return (UARTx->CTRL & UART_CTRL_RXNE_Msk) ? 0 : 1;
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_IsTXFIFOFull()
* 功能说明:	发送FIFO是否为满，如果不满则可以继续向其中写入数据
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t				1 发送FIFO满    0 发送FIFO不满
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_IsTXFIFOFull(UART_TypeDef * UARTx)
{
	return (UARTx->CTRL & UART_CTRL_TXFF_Msk) ? 1 : 0;
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_SetBaudrate()
* 功能说明:	设置波特率
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*			uint32_t baudrate		要设置的波特率
* 输    出: 无
* 注意事项: 不要在串口工作时更改波特率，使用此函数前请先调用UART_Close()关闭串口
******************************************************************************************************************************************/
void UART_SetBaudrate(UART_TypeDef * UARTx, uint32_t baudrate)
{
	UARTx->BAUD &= ~UART_BAUD_BAUD_Msk;
	UARTx->BAUD |= ((SystemCoreClock/16/baudrate - 1) << UART_BAUD_BAUD_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_GetBaudrate()
* 功能说明:	查询波特率
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t				当前波特率
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_GetBaudrate(UART_TypeDef * UARTx)
{
	return SystemCoreClock/16/(((UARTx->BAUD & UART_BAUD_BAUD_Msk) >> UART_BAUD_BAUD_Pos) + 1);
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_CTSConfig()
* 功能说明:	UART CTS流控配置
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*			uint32_t enable			1 使能CTS流控    0 禁止CTS流控
*			uint32_t polarity		0 CTS输入为低表示可以发送数据    1 CTS输入为高表示可以发送数据
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
* 函数名称:	UART_CTSLineState()
* 功能说明:	UART CTS线当前状态
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t				0 CTS线当前为低电平    1 CTS线当前为高电平
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_CTSLineState(UART_TypeDef * UARTx)
{
	return (UARTx->CTSCR & UART_CTSCR_STAT_Msk) ? 1 : 0;
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_RTSConfig()
* 功能说明:	UART RTS流控配置
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*			uint32_t enable			1 使能RTS流控    0 禁止RTS流控
*			uint32_t polarity		0 RTS输出低表示可以接收数据    1 RTS输出高表示可以接收数据
*			uint32_t threshold		RTS流控的触发阈值，可取值UART_RTS_1BYTE、UART_RTS_2BYTE、UART_RTS_4BYTE、UART_RTS_6BYTE
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
* 函数名称:	UART_RTSLineState()
* 功能说明:	UART RTS线当前状态
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t				0 RTS线当前为低电平    1 RTS线当前为高电平
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_RTSLineState(UART_TypeDef * UARTx)
{
	return (UARTx->RTSCR & UART_RTSCR_STAT_Msk) ? 1 : 0;
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_LINConfig()
* 功能说明:	UART LIN功能配置
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*			uint32_t detectedIEn	检测到Break中断使能
*			uint32_t generatedIEn	Break发送完成中断使能
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_LINConfig(UART_TypeDef * UARTx, uint32_t detectedIEn, uint32_t generatedIEn)
{
	UARTx->LINCR &= ~(UART_LINCR_BRKDETIE_Msk | UART_LINCR_GENBRKIE_Msk);
	UARTx->LINCR |= (detectedIEn  << UART_LINCR_BRKDETIE_Pos) |
					(generatedIEn << UART_LINCR_GENBRKIE_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_LINGenerate()
* 功能说明:	UART LIN产生/发送Break
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_LINGenerate(UART_TypeDef * UARTx)
{
	UARTx->LINCR |= (1 << UART_LINCR_GENBRK_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_LINIsDetected()
* 功能说明:	UART LIN是否检测到Break
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t				1 检测到LIN Break    0 未检测到LIN Break
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_LINIsDetected(UART_TypeDef * UARTx)
{
	return (UARTx->LINCR & UART_LINCR_BRKDETIF_Msk) ? 1 : 0;
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_LINIsGenerated()
* 功能说明:	UART LIN Break是否发送完成
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t				1 LIN Break 发送完成    0 LIN Break发送未完成
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_LINIsGenerated(UART_TypeDef * UARTx)
{
	return (UARTx->LINCR & UART_LINCR_GENBRKIF_Msk) ? 1 : 0;
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_ABRStart()
* 功能说明:	UART 自动波特率检测开始
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
*			uint32_t detectChar		用于自动检测、计算波特率的检测字符
*									8位数据时可取值：0xFF、0xFE、0xF8、0x80，分别表示发送方必须发送0xFF、0xFE、0xF8、0x80
*									9位数据时可取值：0x1FF、0x1FE、0x1F8、0x180，分别表示发送方必须发送0x1FF、0x1FE、0x1F8、0x180
* 输    出: 无
* 注意事项: 自动波特率检测时不能开启奇偶校验
******************************************************************************************************************************************/
void UART_ABRStart(UART_TypeDef * UARTx, uint32_t detectChar)
{
	uint32_t bits;
	
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
* 函数名称:	UART_ABRIsDone()
* 功能说明:	UART 自动波特率是否完成
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t				0 未完成    UART_ABR_RES_OK 已完成，且成功    UART_ABR_RES_ERR 已完成，但失败、出错
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
* 函数名称:	UART_INTRXThresholdEn()
* 功能说明:	当RX FIFO中数据个数 >= RXThreshold时 触发中断
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_INTRXThresholdEn(UART_TypeDef * UARTx)
{
	UARTx->CTRL |= (0x01 << UART_CTRL_RXIE_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_INTRXThresholdDis()
* 功能说明:	当RX FIFO中数据个数 >= RXThreshold时 不触发中断
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_INTRXThresholdDis(UART_TypeDef * UARTx)
{
	UARTx->CTRL &= ~(0x01 << UART_CTRL_RXIE_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_INTRXThresholdStat()
* 功能说明:	是否RX FIFO中数据个数 >= RXThreshold
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t				1 RX FIFO中数据个数 >= RXThreshold		0 RX FIFO中数据个数 < RXThreshold
* 注意事项: RXIF = RXTHRF & RXIE
******************************************************************************************************************************************/
uint32_t UART_INTRXThresholdStat(UART_TypeDef * UARTx)
{
	return (UARTx->BAUD & UART_BAUD_RXIF_Msk) ? 1 : 0;
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_INTTXThresholdEn()
* 功能说明:	当TX FIFO中数据个数 <= TXThreshold时 触发中断
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_INTTXThresholdEn(UART_TypeDef * UARTx)
{
	UARTx->CTRL |= (0x01 << UART_CTRL_TXIE_Pos);	
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_INTTXThresholdDis()
* 功能说明:	当TX FIFO中数据个数 <= TXThreshold时 不触发中断
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_INTTXThresholdDis(UART_TypeDef * UARTx)
{
	UARTx->CTRL &= ~(0x01 << UART_CTRL_TXIE_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_INTTXThresholdStat()
* 功能说明:	是否TX FIFO中数据个数 <= TXThreshold
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t				1 TX FIFO中数据个数 <= TXThreshold		0 TX FIFO中数据个数 > TXThreshold
* 注意事项: TXIF = TXTHRF & TXIE
******************************************************************************************************************************************/
uint32_t UART_INTTXThresholdStat(UART_TypeDef * UARTx)
{
	return (UARTx->BAUD & UART_BAUD_TXIF_Msk) ? 1 : 0;
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_INTTimeoutEn()
* 功能说明:	接收发生超时时 触发中断
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_INTTimeoutEn(UART_TypeDef * UARTx)
{
	UARTx->CTRL |= (0x01 << UART_CTRL_TOIE_Pos);	
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_INTTimeoutDis()
* 功能说明:	接收发生超时时 不触发中断
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_INTTimeoutDis(UART_TypeDef * UARTx)
{
	UARTx->CTRL &= ~(0x01 << UART_CTRL_TOIE_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_INTTimeoutStat()
* 功能说明:	是否发生了接收超时，即超过 TimeoutTime/(Baudrate/10) 秒没有在RX线上接收到数据时触发中断
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t				1 发生了接收超时		0 未发生接收超时
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_INTTimeoutStat(UART_TypeDef * UARTx)
{
	return (UARTx->BAUD & UART_BAUD_TOIF_Msk) ? 1 : 0;
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_INTTXDoneEn()
* 功能说明:	发送FIFO空且发送移位寄存器空中断使能
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_INTTXDoneEn(UART_TypeDef * UARTx)
{
	UARTx->CTRL |= (0x01 << UART_CTRL_TXDOIE_Pos);	
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_INTTXDoneDis()
* 功能说明:	发送FIFO空且发送移位寄存器空中断禁止
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_INTTXDoneDis(UART_TypeDef * UARTx)
{
	UARTx->CTRL &= ~(0x01 << UART_CTRL_TXDOIE_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称:	UART_INTTXDoneStat()
* 功能说明:	发送FIFO空且发送移位寄存器空中断状态
* 输    入: UART_TypeDef * UARTx	指定要被设置的UART串口，有效值包括UART0、UART1、UART2、UART3
* 输    出: uint32_t				1 发送FIFO空且发送移位寄存器空		0 发送FIFO或发送移位寄存器未空
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t UART_INTTXDoneStat(UART_TypeDef * UARTx)
{
	return (UARTx->BAUD & UART_BAUD_TXDOIF_Msk) ? 1 : 0;
}
