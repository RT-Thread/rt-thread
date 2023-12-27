/******************************************************************************************************************************************
* 文件名称: SWM320_i2c.c
* 功能说明: SWM320单片机的I2C串行接口功能驱动库
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.1.0      2017年10月25日
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
#include "SWM320.h"
#include "SWM320_i2c.h"

/******************************************************************************************************************************************
* 函数名称: I2C_Init()
* 功能说明: I2C初始化
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
*           I2C_InitStructure * initStruct  包含I2C相关设定值的结构体
* 输    出: 无
* 注意事项: 模块只能工作于主机模式
******************************************************************************************************************************************/
void I2C_Init(I2C_TypeDef * I2Cx, I2C_InitStructure * initStruct)
{
    switch((uint32_t)I2Cx)
    {
    case ((uint32_t)I2C0):
        SYS->CLKEN |= (0x01 << SYS_CLKEN_I2C0_Pos);
        break;

    case ((uint32_t)I2C1):
        SYS->CLKEN |= (0x01 << SYS_CLKEN_I2C1_Pos);
        break;
    }

    I2C_Close(I2Cx);    //一些关键寄存器只能在I2C关闭时设置

    if(initStruct->Master == 1)
    {
        I2Cx->CLKDIV = SystemCoreClock/5/initStruct->MstClk;

        I2Cx->MSTCMD = (I2Cx->MSTCMD & (~I2C_MSTCMD_IF_Msk)) | (1 << I2C_MSTCMD_IF_Pos);    //使能中断之前先清除中断标志
        I2Cx->CTRL &= ~I2C_CTRL_MSTIE_Msk;
        I2Cx->CTRL |= (initStruct->MstIEn << I2C_CTRL_MSTIE_Pos);

        switch((uint32_t)I2Cx)
        {
        case ((uint32_t)I2C0):
            if(initStruct->MstIEn)
            {
                NVIC_EnableIRQ(I2C0_IRQn);
            }
            else
            {
                NVIC_DisableIRQ(I2C0_IRQn);
            }
            break;

        case ((uint32_t)I2C1):
            if(initStruct->MstIEn)
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
        I2Cx->SLVCR |=  (1 << I2C_SLVCR_SLAVE_Pos);

        I2Cx->SLVCR &= ~(I2C_SLVCR_ADDR7b_Msk | I2C_SLVCR_ADDR_Msk);
        I2Cx->SLVCR |= (1 << I2C_SLVCR_ACK_Pos) |
                       (initStruct->Addr7b << I2C_SLVCR_ADDR7b_Pos) |
                       (initStruct->SlvAddr << I2C_SLVCR_ADDR_Pos);

        I2Cx->SLVIF = I2C_SLVIF_RXEND_Msk | I2C_SLVIF_TXEND_Msk | I2C_SLVIF_STADET_Msk | I2C_SLVIF_STODET_Msk;  //清中断标志
        I2Cx->SLVCR &= ~(I2C_SLVCR_IM_RXEND_Msk | I2C_SLVCR_IM_TXEND_Msk | I2C_SLVCR_IM_STADET_Msk | I2C_SLVCR_IM_STODET_Msk |
                         I2C_SLVCR_IM_RDREQ_Msk | I2C_SLVCR_IM_WRREQ_Msk);
        I2Cx->SLVCR |= ((initStruct->SlvRxEndIEn  ? 0 : 1) << I2C_SLVCR_IM_RXEND_Pos)  |
                       ((initStruct->SlvTxEndIEn  ? 0 : 1) << I2C_SLVCR_IM_TXEND_Pos)  |
                       ((initStruct->SlvSTADetIEn ? 0 : 1) << I2C_SLVCR_IM_STADET_Pos) |
                       ((initStruct->SlvSTODetIEn ? 0 : 1) << I2C_SLVCR_IM_STODET_Pos) |
                       ((initStruct->SlvRdReqIEn  ? 0 : 1) << I2C_SLVCR_IM_RDREQ_Pos)  |
                       ((initStruct->SlvWrReqIEn  ? 0 : 1) << I2C_SLVCR_IM_WRREQ_Pos);

        switch((uint32_t)I2Cx)
        {
        case ((uint32_t)I2C0):
            if(initStruct->SlvRxEndIEn | initStruct->SlvTxEndIEn | initStruct->SlvSTADetIEn |
               initStruct->SlvSTODetIEn | initStruct->SlvRdReqIEn | initStruct->SlvWrReqIEn)
            {
                NVIC_EnableIRQ(I2C0_IRQn);
            }
            else
            {
                NVIC_DisableIRQ(I2C0_IRQn);
            }
            break;

        case ((uint32_t)I2C1):
            if(initStruct->SlvRxEndIEn | initStruct->SlvTxEndIEn | initStruct->SlvSTADetIEn |
               initStruct->SlvSTODetIEn | initStruct->SlvRdReqIEn | initStruct->SlvWrReqIEn)
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
    I2Cx->CTRL |= (0x01 << I2C_CTRL_EN_Pos);
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
    I2Cx->CTRL &= ~I2C_CTRL_EN_Msk;
}

/******************************************************************************************************************************************
* 函数名称: I2C_Start()
* 功能说明: 产生起始信号并发送设备地址
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
*           uint8_t addr            设备地址
* 输    出: uint8_t                   1 接收到ACK   0 接收到NACK
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t I2C_Start(I2C_TypeDef * I2Cx, uint8_t addr)
{
    I2Cx->MSTDAT = addr;
    I2Cx->MSTCMD = (1 << I2C_MSTCMD_STA_Pos) |
                   (1 << I2C_MSTCMD_WR_Pos);                //发送起始位和从机地址
    while(I2Cx->MSTCMD & I2C_MSTCMD_TIP_Msk) __NOP();       //等待发送完成

    return (I2Cx->MSTCMD & I2C_MSTCMD_RXACK_Msk) ? 0 : 1;
}

/******************************************************************************************************************************************
* 函数名称: I2C_Stop()
* 功能说明: 产生停止信号
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void I2C_Stop(I2C_TypeDef * I2Cx)
{
    I2Cx->MSTCMD = (1 << I2C_MSTCMD_STO_Pos);
    while(I2Cx->MSTCMD & I2C_MSTCMD_TIP_Msk) __NOP();       //等待发送完成
}

/******************************************************************************************************************************************
* 函数名称: I2C_Write()
* 功能说明: 写入一个数据
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
*           uint8_t data            要写的数据
* 输    出: uint8_t                   1 接收到ACK   0 接收到NACK
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t I2C_Write(I2C_TypeDef * I2Cx, uint8_t data)
{
    I2Cx->MSTDAT = data;
    I2Cx->MSTCMD = (1 << I2C_MSTCMD_WR_Pos);
    while(I2Cx->MSTCMD & I2C_MSTCMD_TIP_Msk) __NOP();       //等待发送完成

    return (I2Cx->MSTCMD & I2C_MSTCMD_RXACK_Msk) ? 0 : 1;
}

/******************************************************************************************************************************************
* 函数名称: I2C_Read()
* 功能说明: 读取一个数据
* 输    入: I2C_TypeDef * I2Cx        指定要被设置的I2C，有效值包括I2C0、I2C1
*           uint8_t ack             1 发送ACK   0 发送NACK
* 输    出: uint8_t                   读取到的数据
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t I2C_Read(I2C_TypeDef * I2Cx, uint8_t ack)
{
    I2Cx->MSTCMD = (1 << I2C_MSTCMD_RD_Pos) |
                   ((ack ? 0 : 1) << I2C_MSTCMD_ACK_Pos);
    while(I2Cx->MSTCMD & I2C_MSTCMD_TIP_Msk) __NOP();       //等待接收完成

    return I2Cx->MSTDAT;
}
