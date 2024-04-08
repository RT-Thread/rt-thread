/******************************************************************************************************************************************
* 文件名称: SWM341_i2c.c
* 功能说明: SWM341单片机的I2C串行接口功能驱动库
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.0.0      2016年1月30日
* 升级记录:
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIES AT PROVIDING CUSTOMERS WITH CODING INFORMATION
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIEE. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIES ARISING FROM THE CONTENT
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology
*******************************************************************************************************************************************/
#include "SWM341.h"
#include "SWM341_i2c.h"


/******************************************************************************************************************************************
* 函数名称: I2C_Init()
* 功能说明: I2C初始化
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
*           I2C_InitStructure * initStruct  包含I2C相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void I2C_Init(I2C_TypeDef * I2Cx, I2C_InitStructure * initStruct)
{
    switch((uint32_t)I2Cx)
    {
    case ((uint32_t)I2C0):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_I2C0_Pos);
        break;

    case((uint32_t)I2C1):
        SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_I2C1_Pos);
        break;
    }

    I2C_Close(I2Cx);    //一些关键寄存器只能在I2C关闭时设置

    if(initStruct->Master == 1)
    {
        I2Cx->CR |= (1 << I2C_CR_MASTER_Pos);

        I2Cx->CLK = (((SystemCoreClock/2)/1000000/3*2 - 1) << I2C_CLK_SCLL_Pos) |
                    (((SystemCoreClock/2)/1000000/3*1 - 1) << I2C_CLK_SCLH_Pos) |
                    ((1000000 / initStruct->MstClk - 1)    << I2C_CLK_DIV_Pos);

        I2Cx->IF = 0xFFFFFFFF;
        I2Cx->IE = (initStruct->TXEmptyIEn << I2C_IE_TXE_Pos) |
                   (initStruct->RXNotEmptyIEn << I2C_IE_RXNE_Pos);

        switch((uint32_t)I2Cx)
        {
        case ((uint32_t)I2C0):
            if(initStruct->TXEmptyIEn | initStruct->RXNotEmptyIEn)
            {
                NVIC_EnableIRQ(I2C0_IRQn);
            }
            else
            {
                NVIC_DisableIRQ(I2C0_IRQn);
            }
            break;

        case ((uint32_t)I2C1):
            if(initStruct->TXEmptyIEn | initStruct->RXNotEmptyIEn)
            {
                NVIC_EnableIRQ(I2C1_IRQn);
            }
            else
            {
                NVIC_DisableIRQ(I2C1_IRQn);
            }
            break;
        }
    }
    else
    {
        I2Cx->CR &= ~(1 << I2C_CR_MASTER_Pos);

        I2Cx->SCR &= ~I2C_SCR_ADDR10_Msk;
        I2Cx->SCR |= (initStruct->Addr10b << I2C_SCR_ADDR10_Pos);

        if(initStruct->Addr10b)
            I2Cx->SADDR = (initStruct->SlvAddr    << I2C_SADDR_ADDR10_Pos) |
                          (initStruct->SlvAddrMsk << I2C_SADDR_MASK10_Pos);
        else
            I2Cx->SADDR = (initStruct->SlvAddr    << I2C_SADDR_ADDR7_Pos) |
                          (initStruct->SlvAddrMsk << I2C_SADDR_MASK7_Pos);

        I2Cx->IF = 0xFFFFFFFF;
        I2Cx->IE = (initStruct->TXEmptyIEn    << I2C_IE_TXE_Pos) |
                   (initStruct->RXNotEmptyIEn << I2C_IE_RXNE_Pos) |
                   (initStruct->SlvSTADetIEn  << I2C_IE_RXSTA_Pos) |
                   (initStruct->SlvSTODetIEn  << I2C_IE_RXSTO_Pos);

        switch((uint32_t)I2Cx)
        {
        case ((uint32_t)I2C0):
            if(initStruct->SlvSTADetIEn | initStruct->SlvSTODetIEn | initStruct->TXEmptyIEn | initStruct->RXNotEmptyIEn)
            {
                NVIC_EnableIRQ(I2C0_IRQn);
            }
            else
            {
                NVIC_DisableIRQ(I2C0_IRQn);
            }
            break;

        case ((uint32_t)I2C1):
            if(initStruct->SlvSTADetIEn | initStruct->SlvSTODetIEn | initStruct->TXEmptyIEn | initStruct->RXNotEmptyIEn)
            {
                NVIC_EnableIRQ(I2C1_IRQn);
            }
            else
            {
                NVIC_DisableIRQ(I2C1_IRQn);
            }
            break;
        }
    }
}

/******************************************************************************************************************************************
* 函数名称: I2C_Open()
* 功能说明: I2C打开，允许收发
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void I2C_Open(I2C_TypeDef * I2Cx)
{
    I2Cx->CR |= (0x01 << I2C_CR_EN_Pos);
}

/******************************************************************************************************************************************
* 函数名称: I2C_Close()
* 功能说明: I2C关闭，禁止收发
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void I2C_Close(I2C_TypeDef * I2Cx)
{
    I2Cx->CR &= ~(0x01 << I2C_CR_EN_Pos);
}

/******************************************************************************************************************************************
* 函数名称: I2C_Start()
* 功能说明: 产生起始信号并发送设备地址
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
*           uint8_t addr            设备地址
*           uint8_t wait            是否等待发送完成，1 等待发送完成   0 不等待，立即返回
* 输    出: uint8_t                   1 接收到ACK   0 接收到NACK
* 注意事项: 若选择不等待，立即返回，则返回值无意义；后续可通过 I2C_StartDone() 查询是否完成，完成后调用 I2C_IsAck() 查询接收到ACK还是NACK
******************************************************************************************************************************************/
uint8_t I2C_Start(I2C_TypeDef * I2Cx, uint8_t addr, uint8_t wait)
{
    I2Cx->TXDATA = addr;
    I2Cx->MCR = (1 << I2C_MCR_STA_Pos) |
                (1 << I2C_MCR_WR_Pos);              //发送起始位和从机地址

    if(wait == 0)
        return 0;

    while(I2Cx->MCR & I2C_MCR_WR_Msk) __NOP();      //等待发送完成

    return (I2Cx->TR & I2C_TR_RXACK_Msk) ? 0 : 1;
}

uint8_t I2C_StartDone(I2C_TypeDef * I2Cx)
{
    return (I2Cx->MCR & I2C_MCR_WR_Msk) ? 0 : 1;
}

uint8_t I2C_IsAck(I2C_TypeDef * I2Cx)
{
    return (I2Cx->TR & I2C_TR_RXACK_Msk) ? 0 : 1;
}

/******************************************************************************************************************************************
* 函数名称: I2C_Stop()
* 功能说明: 产生停止信号
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
*           uint8_t wait            是否等待发送完成，1 等待发送完成   0 不等待，立即返回
* 输    出: 无
* 注意事项: 若选择不等待，立即返回；后续可通过 I2C_StopDone() 查询是否完成
******************************************************************************************************************************************/
void I2C_Stop(I2C_TypeDef * I2Cx, uint8_t wait)
{
    I2Cx->MCR = (1 << I2C_MCR_STO_Pos);

    if(wait == 0)
        return;

    while(I2Cx->MCR & I2C_MCR_STO_Msk) __NOP();     //等待发送完成
}

uint8_t I2C_StopDone(I2C_TypeDef * I2Cx)
{
    return (I2Cx->MCR & I2C_MCR_STO_Msk) ? 0 : 1;
}

/******************************************************************************************************************************************
* 函数名称: I2C_Write()
* 功能说明: 写入一个数据
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
*           uint8_t data            要写的数据
*           uint8_t wait            是否等待发送完成，1 等待发送完成   0 不等待，立即返回
* 输    出: uint8_t                   1 接收到ACK   0 接收到NACK
* 注意事项: 若选择不等待，立即返回，则返回值无意义；后续可通过 I2C_WriteDone() 查询是否完成，完成后调用 I2C_IsAck() 查询接收到ACK还是NACK
******************************************************************************************************************************************/
uint8_t I2C_Write(I2C_TypeDef * I2Cx, uint8_t data, uint8_t wait)
{
    I2Cx->TXDATA = data;
    I2Cx->MCR = (1 << I2C_MCR_WR_Pos);

    if(wait == 0)
        return 0;

    while(I2Cx->MCR & I2C_MCR_WR_Msk) __NOP();      //等待发送完成

    return (I2Cx->TR & I2C_TR_RXACK_Msk) ? 0 : 1;
}

uint8_t I2C_WriteDone(I2C_TypeDef * I2Cx)
{
    return (I2Cx->MCR & I2C_MCR_WR_Msk) ? 0 : 1;
}

/******************************************************************************************************************************************
* 函数名称: I2C_Read()
* 功能说明: 读取一个数据
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
*           uint8_t ack             1 发送ACK   0 发送NACK
*           uint8_t wait            是否等待发送完成，1 等待发送完成   0 不等待，立即返回
* 输    出: uint8_t                   读取到的数据
* 注意事项: 若选择不等待，立即返回，则返回值无意义；后续可通过 I2C_ReadDone() 查询是否完成，完成后通过 I2Cx->RXDATA 获取读取到的数据
******************************************************************************************************************************************/
uint8_t I2C_Read(I2C_TypeDef * I2Cx, uint8_t ack, uint8_t wait)
{
    I2Cx->TR = ((ack ? 0 : 1) << I2C_TR_TXACK_Pos);

    I2Cx->MCR = (1 << I2C_MCR_RD_Pos);

    if(wait == 0)
        return 0;

    while(I2Cx->MCR & I2C_MCR_RD_Msk) __NOP();      //等待接收完成

    return I2Cx->RXDATA;
}

uint8_t I2C_ReadDone(I2C_TypeDef * I2Cx)
{
    return (I2Cx->MCR & I2C_MCR_RD_Msk) ? 0 : 1;
}

/******************************************************************************************************************************************
* 函数名称: I2C_INTEn()
* 功能说明: 中断使能
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
*           uint32_t it             interrupt type，有效值I2C_IT_TX_EMPTY、I2C_IT_RX_NOT_EMPTY、I2C_IT_RX_OVF、I2C_IT_TX_DONE、I2C_IT_RX_DONE、
*                                   I2C_IT_SLV_DET_STA、I2C_IT_SLV_DET_STP、I2C_IT_ARB_LOST、I2C_IT_SCL_LOW_TO 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void I2C_INTEn(I2C_TypeDef * I2Cx, uint32_t it)
{
    I2Cx->IE |= it;
}

/******************************************************************************************************************************************
* 函数名称: I2C_INTDis()
* 功能说明: 中断禁止
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
*           uint32_t it             interrupt type，有效值I2C_IT_TX_EMPTY、I2C_IT_RX_NOT_EMPTY、I2C_IT_RX_OVF、I2C_IT_TX_DONE、I2C_IT_RX_DONE、
*                                   I2C_IT_SLV_DET_STA、I2C_IT_SLV_DET_STP、I2C_IT_ARB_LOST、I2C_IT_SCL_LOW_TO 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void I2C_INTDis(I2C_TypeDef * I2Cx, uint32_t it)
{
    I2Cx->IE &= ~it;
}

/******************************************************************************************************************************************
* 函数名称: I2C_INTClr()
* 功能说明: 中断标志清除
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
*           uint32_t it             interrupt type，有效值I2C_IT_TX_EMPTY、I2C_IT_RX_NOT_EMPTY、I2C_IT_RX_OVF、I2C_IT_TX_DONE、I2C_IT_RX_DONE、
*                                   I2C_IT_SLV_DET_STA、I2C_IT_SLV_DET_STP、I2C_IT_ARB_LOST、I2C_IT_SCL_LOW_TO 及其“或”
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void I2C_INTClr(I2C_TypeDef * I2Cx, uint32_t it)
{
    I2Cx->IF = it;
}

/******************************************************************************************************************************************
* 函数名称: I2C_INTStat()
* 功能说明: 中断状态查询
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
*           uint32_t it             interrupt type，有效值I2C_IT_TX_EMPTY、I2C_IT_RX_NOT_EMPTY、I2C_IT_RX_OVF、I2C_IT_TX_DONE、I2C_IT_RX_DONE、
*                                   I2C_IT_SLV_DET_STA、I2C_IT_SLV_DET_STP、I2C_IT_ARB_LOST、I2C_IT_SCL_LOW_TO 及其“或”
* 输    出: uint32_t              1 中断发生    0 中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t I2C_INTStat(I2C_TypeDef * I2Cx, uint32_t it)
{
    return (I2Cx->IF & it) ? 1 : 0;
}
