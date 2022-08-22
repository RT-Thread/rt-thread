#ifndef __SWM320_PWM_H__
#define __SWM320_PWM_H__

typedef struct {
    uint8_t  clk_div;       //PWM_CLKDIV_1、PWM_CLKDIV_8

    uint8_t  mode;          //PWM_MODE_INDEP、PWM_MODE_COMPL、PWM_MODE_INDEP_CALIGN、PWM_MODE_COMPL_CALIGN

    uint16_t cycleA;        //A路周期
    uint16_t hdutyA;        //A路占空比
    uint16_t deadzoneA;     //A路死区时长，取值0--1023
    uint8_t  initLevelA;    //A路初始输出电平，0 低电平    1 高电平

    uint16_t cycleB;        //B路周期
    uint16_t hdutyB;        //B路占空比
    uint16_t deadzoneB;     //B路死区时长，取值0--1023
    uint8_t  initLevelB;    //B路初始输出电平，0 低电平    1 高电平

    uint8_t  HEndAIEn;      //A路高电平结束中断使能
    uint8_t  NCycleAIEn;    //A路新周期开始中断使能
    uint8_t  HEndBIEn;      //B路高电平结束中断使能
    uint8_t  NCycleBIEn;    //B路新周期开始中断使能
} PWM_InitStructure;

#define PWM_CLKDIV_1    0
#define PWM_CLKDIV_8    1

#define PWM_MODE_INDEP          0       //A路和B路为两路独立输出
#define PWM_MODE_COMPL          1       //A路和B路为一路互补输出
#define PWM_MODE_INDEP_CALIGN   3       //A路和B路为两路独立输出，中心对齐
#define PWM_MODE_COMPL_CALIGN   4       //A路和B路为一路互补输出，中心对齐

#define PWM_CH_A    0
#define PWM_CH_B    1


void PWM_Init(PWM_TypeDef * PWMx, PWM_InitStructure * initStruct);          //PWM初始化
void PWM_Start(PWM_TypeDef * PWMx, uint32_t chA, uint32_t chB);             //启动PWM，开始PWM输出
void PWM_Stop(PWM_TypeDef * PWMx, uint32_t chA, uint32_t chB);              //关闭PWM，停止PWM输出

void PWM_SetCycle(PWM_TypeDef * PWMx, uint32_t chn, uint16_t cycle);        //设置周期
uint16_t PWM_GetCycle(PWM_TypeDef * PWMx, uint32_t chn);                    //获取周期
void PWM_SetHDuty(PWM_TypeDef * PWMx, uint32_t chn, uint16_t hduty);        //设置高电平时长
uint16_t PWM_GetHDuty(PWM_TypeDef * PWMx, uint32_t chn);                    //获取高电平时长
void PWM_SetDeadzone(PWM_TypeDef * PWMx, uint32_t chn, uint8_t deadzone);   //设置死区时长
uint8_t  PWM_GetDeadzone(PWM_TypeDef * PWMx, uint32_t chn);                 //获取死区时长

void PWM_IntNCycleEn(PWM_TypeDef * PWMx, uint32_t chn);                     //新周期开始中断使能
void PWM_IntNCycleDis(PWM_TypeDef * PWMx, uint32_t chn);                    //新周期开始中断禁能
void PWM_IntNCycleClr(PWM_TypeDef * PWMx, uint32_t chn);                    //新周期开始中断标志清除
uint32_t PWM_IntNCycleStat(PWM_TypeDef * PWMx, uint32_t chn);               //新周期开始中断是否发生
void PWM_IntHEndEn(PWM_TypeDef * PWMx, uint32_t chn);                       //高电平结束中断使能
void PWM_IntHEndDis(PWM_TypeDef * PWMx, uint32_t chn);                      //高电平结束中断禁能
void PWM_IntHEndClr(PWM_TypeDef * PWMx, uint32_t chn);                      //高电平结束中断标志清除
uint32_t PWM_IntHEndStat(PWM_TypeDef * PWMx, uint32_t chn);                 //高电平结束中断是否发生


#endif //__SWM320_PWM_H__
