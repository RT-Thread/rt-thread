#ifndef __SWM320_TIMR_H__
#define __SWM320_TIMR_H__

#define TIMR_MODE_TIMER     0
#define TIMR_MODE_COUNTER   1

void TIMR_Init(TIMR_TypeDef * TIMRx, uint32_t mode, uint32_t period, uint32_t int_en);  //定时器/计数器初始化
void TIMR_Start(TIMR_TypeDef * TIMRx);                          //启动定时器，从初始值开始计时/计数
void TIMR_Stop(TIMR_TypeDef * TIMRx);                           //停止定时器
void TIMR_Halt(TIMR_TypeDef * TIMRx);                           //暂停定时器，计数值保持不变
void TIMR_Resume(TIMR_TypeDef * TIMRx);                         //恢复定时器，从暂停处继续计数

void TIMR_SetPeriod(TIMR_TypeDef * TIMRx, uint32_t period);     //设置定时/计数周期
uint32_t TIMR_GetPeriod(TIMR_TypeDef * TIMRx);                  //获取定时/计数周期
uint32_t TIMR_GetCurValue(TIMR_TypeDef * TIMRx);                //获取当前计数值

void TIMR_INTEn(TIMR_TypeDef * TIMRx);                          //使能中断
void TIMR_INTDis(TIMR_TypeDef * TIMRx);                         //禁能中断
void TIMR_INTClr(TIMR_TypeDef * TIMRx);                         //清除中断标志
uint32_t TIMR_INTStat(TIMR_TypeDef * TIMRx);                    //获取中断状态



#define PULSE_LOW    0
#define PULSE_HIGH   1

void Pulse_Init(uint32_t pulse, uint32_t int_en);
void Pulse_Start(void);
uint32_t Pulse_Done(void);


#endif //__SWM320_TIMR_H__
