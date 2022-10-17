#ifndef __SWM341_PWM_H__
#define __SWM341_PWM_H__


typedef struct {
    uint8_t  Mode;          //PWM_EDGE_ALIGNED、PWM_CENTER_ALIGNED、PWM_ASYM_CENTER_ALIGNED

    uint16_t Clkdiv;        //1--1024

    uint16_t Period;        //周期

    uint16_t HdutyA;        //占空比，高电平时长；PWM_ASYM_CENTER_ALIGNED 模式下设定前半周期的高电平时长
    uint16_t HdutyA2;       //只在 PWM_ASYM_CENTER_ALIGNED 模式下使用，用于设定后半周期的高电平时长
    uint16_t DeadzoneA;     //死区时长，取值0--1023
    uint8_t  IdleLevelA;    //停止状态下PWMxA输出电平
    uint8_t  IdleLevelAN;   //停止状态下PWMxAN输出电平
    uint8_t  OutputInvA;    //PWMxA输出取反
    uint8_t  OutputInvAN;   //PWMxAN输出取反

    uint16_t HdutyB;
    uint16_t HdutyB2;
    uint16_t DeadzoneB;
    uint8_t  IdleLevelB;
    uint8_t  IdleLevelBN;
    uint8_t  OutputInvB;
    uint8_t  OutputInvBN;

    uint8_t  UpOvfIE;       //上升沿计数器溢出中断使能，PWM_EDGE_ALIGNED 模式下向上计数，因此只有上升沿
    uint8_t  DownOvfIE;     //下降沿计数器溢出中断使能，另外两种模式下先向上计数、后向下计数，上升沿是前半周期、下降沿是后半周期
    uint8_t  UpCmpAIE;      //上升沿比较器A匹配中断使能
    uint8_t  DownCmpAIE;    //下降沿比较器A匹配中断使能
    uint8_t  UpCmpBIE;      //上升沿比较器B匹配中断使能
    uint8_t  DownCmpBIE;    //下降沿比较器B匹配中断使能
} PWM_InitStructure;


#define PWM_EDGE_ALIGNED          0
#define PWM_CENTER_ALIGNED        1
#define PWM_ASYM_CENTER_ALIGNED   2     // 非对称中心对齐模式，上升沿和下降沿具有不同的翻转点比较值


#define PWM_CH_A    0
#define PWM_CH_B    1

#define PWM0_MSK    (1 << 0)
#define PWM1_MSK    (1 << 1)
#define PWM2_MSK    (1 << 2)
#define PWM3_MSK    (1 << 3)
#define PWM4_MSK    (1 << 4)

#define PWM_BRK0    (1 << 0)
#define PWM_BRK1    (1 << 1)
#define PWM_BRK2    (1 << 2)

#define PWM_DIR_UP      0
#define PWM_DIR_DOWN    1

#define PWM_TRG_0       0       //计数器溢出或与指定值相等时 PWM 输出触发信号
#define PWM_TRG_1       1
#define PWM_TRG_2       2
#define PWM_TRG_3       3
#define PWM_TRG_4       4
#define PWM_TRG_5       5
#define PWM_TRG_6       6
#define PWM_TRG_7       7

#define PWM_EVT_DIS     0       //外部事件信号为高时 PWM 启动计数、停止计数、暂停计数、屏蔽输出
#define PWM_EVT_0       1
#define PWM_EVT_1       2
#define PWM_EVT_2       3
#define PWM_EVT_3       4
#define PWM_EVT_4       5
#define PWM_EVT_TIMR0   6
#define PWM_EVT_TIMR1   7

/* Interrupt Type */
#define PWM_IT_OVF_UP      (1 << 0)     //向上计数时计数器溢出，PWM_EDGE_ALIGNED 模式下向上计数，因此只有上升沿
#define PWM_IT_OVF_DOWN    (1 << 1)     //向下计数时计数器溢出，另外两种模式下先向上计数、后向下计数，上升沿是前半周期、下降沿是后半周期
#define PWM_IT_CMPA_UP     (1 << 2)     //向上计数时计数器值与CMPA相等
#define PWM_IT_CMPB_UP     (1 << 3)     //向上计数时计数器值与CMPB相等
#define PWM_IT_CMPA_DOWN   (1 << 4)     //向下计数时计数器值与CMPA相等
#define PWM_IT_CMPB_DOWN   (1 << 5)     //向下计数时计数器值与CMPB相等

#define PWM_BRKIT_BRK0     (1 << 0)     //PWM_BRK0引脚上出现刹车信号
#define PWM_BRKIT_BRK1     (1 << 1)
#define PWM_BRKIT_BRK2     (1 << 2)



void PWM_Init(PWM_TypeDef * PWMx, PWM_InitStructure * initStruct);          //PWM初始化
void PWM_Start(uint32_t pwm);                                               //启动PWM，开始PWM输出
void PWM_Stop(uint32_t pwm);                                                //关闭PWM，停止PWM输出
void PWM_Restart(uint32_t pwm);

void PWM_ReloadEn(uint32_t pwm);
void PWM_ReloadDis(uint32_t pwm);

void PWM_BrkInPolarity(uint32_t brk, uint32_t level);
void PWM_BrkConfig(PWM_TypeDef * PWMx, uint32_t chn, uint32_t brk, uint32_t out, uint32_t outN, uint32_t outHold, uint32_t stpCount);

void PWM_OvfTrigger(PWM_TypeDef * PWMx, uint32_t en_up, uint32_t en_down, uint32_t trig_chn);
void PWM_CmpTrigger(PWM_TypeDef * PWMx, uint16_t match, uint32_t dir, uint32_t width, uint32_t trig_chn, uint32_t adc_trig_pos);

void PWM_OutMask(PWM_TypeDef * PWMx, uint32_t chn, uint32_t evt, uint32_t out, uint32_t evt_n, uint32_t out_n);

void PWM_SetPeriod(PWM_TypeDef * PWMx, uint16_t period);                    //设置周期
uint16_t PWM_GetPeriod(PWM_TypeDef * PWMx);                                 //获取周期
void PWM_SetHDuty(PWM_TypeDef * PWMx, uint32_t chn, uint16_t hduty);        //设置高电平时长
uint16_t PWM_GetHDuty(PWM_TypeDef * PWMx, uint32_t chn);                    //获取高电平时长
void PWM_SetHDuty2(PWM_TypeDef * PWMx, uint32_t chn, uint16_t hduty, uint16_t hduty2);      //设置高电平时长，用于非对称中心对齐模式
void PWM_GetHDuty2(PWM_TypeDef * PWMx, uint32_t chn, uint16_t *hduty, uint16_t *hduty2);    //获取高电平时长，用于非对称中心对齐模式
void PWM_SetDeadzone(PWM_TypeDef * PWMx, uint32_t chn, uint16_t deadzone);  //设置死区时长
uint16_t PWM_GetDeadzone(PWM_TypeDef * PWMx, uint32_t chn);                 //获取死区时长

void PWM_IntEn(PWM_TypeDef * PWMx, uint32_t it);                            //中断使能
void PWM_IntDis(PWM_TypeDef * PWMx, uint32_t it);                           //中断禁能
void PWM_IntClr(PWM_TypeDef * PWMx, uint32_t it);                           //中断标志清除
uint32_t PWM_IntStat(PWM_TypeDef * PWMx, uint32_t it);                      //中断标志查询
void PWM_BrkIntEn(uint32_t brkit);                                          //刹车中断使能
void PWM_BrkIntDis(uint32_t brkit);                                         //刹车中断禁能
void PWM_BrkIntClr(uint32_t brkit);                                         //刹车中断标志清除
uint32_t PWM_BrkIntStat(uint32_t brkit);                                    //刹车中断标志查询


#endif //__SWM341_PWM_H__
