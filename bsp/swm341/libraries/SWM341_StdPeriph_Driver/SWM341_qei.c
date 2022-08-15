/******************************************************************************************************************************************
* 文件名称: SWM341_qei.c
* 功能说明: SWM341单片机的正交编码器接口QEI功能驱动库
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.0.0      2013年06月30日
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
#include "SWM341_qei.h"


/******************************************************************************************************************************************
* 函数名称: QEI_Init()
* 功能说明: 正交编码器接口QEI初始化
* 输    入: QEI_TypeDef * QEIx        指定要被设置的正交编码器接口，有效值包括QEI
*           QEI_InitStructure * initStruct      包含正交编码器接口相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void QEI_Init(QEI_TypeDef * QEIx,QEI_InitStructure * initStruct)
{
    switch((uint32_t)QEIx)
    {
    case ((uint32_t)QEI):
        SYS->CLKEN1 |= (1 << SYS_CLKEN1_QEI_Pos);
        break;
    }

    QEI_Stop(QEIx);     //配置前关闭QEI模块

    QEIx->CR = (initStruct->swapAB << QEI_CR_ABSWAP_Pos) |
               (initStruct->mode   << QEI_CR_X2X4_Pos)   |
               (1                  << QEI_CR_RSTSRC_Pos) |
               (1                  << QEI_CR_MODE_Pos);

    QEIx->POSCNT = 0;
    QEIx->MAXCNT = initStruct->maxcnt;

    QEIx->IC = 0x0F;
    QEIx->IE = 0x0F;
    QEIx->IM = (initStruct->intINDEXEn << QEI_IM_INDEX_Pos) |
               (initStruct->intMATCHEn << QEI_IM_MATCH_Pos) |
               (initStruct->intCNTOVEn << QEI_IM_CNTOV_Pos) |
               (initStruct->intERROREn << QEI_IM_ERROR_Pos);

    if(initStruct->intINDEXEn | initStruct->intMATCHEn | initStruct->intCNTOVEn | initStruct->intERROREn)
    {
        NVIC_EnableIRQ(QEI_IRQn);
    }
}

/******************************************************************************************************************************************
* 函数名称: QEI_Start()
* 功能说明: 启动指定QEI
* 输    入: QEI_TypeDef * QEIx        指定要被设置的正交编码器接口，有效值包括QEI
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void QEI_Start(QEI_TypeDef * QEIx)
{
    QEIx->CR |= (1 << QEI_CR_ENA_Pos);
}

/******************************************************************************************************************************************
* 函数名称: QEI_Stop()
* 功能说明: 关闭指定QEI
* 输    入: QEI_TypeDef * QEIx        指定要被设置的正交编码器接口，有效值包括QEI
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void QEI_Stop(QEI_TypeDef * QEIx)
{
    QEIx->CR &= ~(1 << QEI_CR_ENA_Pos);
}

/******************************************************************************************************************************************
* 函数名称: QEI_IntEn()
* 功能说明: QEI中断使能
* 输    入: QEI_TypeDef * QEIx        指定要被设置的正交编码器接口，有效值包括QEI
*           uint32_t it             interrupt type，取值QEI_INT_INDEX、QEI_INT_MATCH、QEI_INT_CNTOV、QEI_INT_ERROR 及其或
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void QEI_IntEn(QEI_TypeDef * QEIx, uint32_t it)
{
    QEIx->IM |= it;

    switch((uint32_t)QEIx)
    {
    case ((uint32_t)QEI):
        NVIC_EnableIRQ(QEI_IRQn);
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: QEI_IntDis()
* 功能说明: QEI中断关闭
* 输    入: QEI_TypeDef * QEIx        指定要被设置的正交编码器接口，有效值包括QEI
*           uint32_t it             interrupt type，取值QEI_INT_INDEX、QEI_INT_MATCH、QEI_INT_CNTOV、QEI_INT_ERROR 及其或
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void QEI_IntDis(QEI_TypeDef * QEIx, uint32_t it)
{
    QEIx->IM &= ~it;
}

/******************************************************************************************************************************************
* 函数名称: QEI_IntClr()
* 功能说明: QEI中断标志清除
* 输    入: QEI_TypeDef * QEIx        指定要被设置的正交编码器接口，有效值包括QEI
*           uint32_t it             interrupt type，取值QEI_INT_INDEX、QEI_INT_MATCH、QEI_INT_CNTOV、QEI_INT_ERROR 及其或
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void QEI_IntClr(QEI_TypeDef * QEIx, uint32_t it)
{
    QEIx->IC = it;
}

/******************************************************************************************************************************************
* 函数名称: QEI_IntStat()
* 功能说明: QEI中断状态查询
* 输    入: QEI_TypeDef * QEIx        指定要被设置的正交编码器接口，有效值包括QEI
*           uint32_t it             interrupt type，取值QEI_INT_INDEX、QEI_INT_MATCH、QEI_INT_CNTOV、QEI_INT_ERROR 及其或
* 输    出: uint32_t              0 没有中断发生    非0值 有中断发生
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t QEI_IntStat(QEI_TypeDef * QEIx, uint32_t it)
{
    return (QEIx->IF & it);
}
