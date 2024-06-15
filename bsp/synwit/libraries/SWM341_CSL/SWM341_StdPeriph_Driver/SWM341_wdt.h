#ifndef __SWM341_WDT_H__
#define __SWM341_WDT_H__

void WDT_Init(WDT_TypeDef * WDTx, uint32_t int_period, uint32_t rst_period);
void WDT_ReInit(WDT_TypeDef * WDTx, uint32_t int_period, uint32_t rst_period);
void WDT_Start(WDT_TypeDef * WDTx);         //启动指定WDT，开始倒计时
void WDT_Stop(WDT_TypeDef * WDTx);          //关闭指定WDT，停止倒计时

void WDT_Feed(WDT_TypeDef * WDTx);          //喂狗，重新从装载值开始倒计时


void WDT_INTClr(WDT_TypeDef * WDTx);        //中断标志清除
uint32_t WDT_INTStat(WDT_TypeDef * WDTx);   //中断状态查询


#endif //__SWM341_WDT_H__
