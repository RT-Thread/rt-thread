/******************************************************************************************************************************************
* 文件名称: SWM341_sleep.c
* 功能说明: SWM341单片机的Sleep功能驱动库
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
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
#include "SWM341_sleep.h"


#if   defined ( __CC_ARM )

/* 进入休眠Sleep模式的代码指令，生成这段儿指令的C代码是：
void EnterSleepMode(void)
{
    __NOP();__NOP();__NOP();
    SYS->SLEEP |= (1 << SYS_SLEEP_SLEEP_Pos);
}
*/
uint16_t Code_EnterSleepMode[] = {
    0xBF00, 0xBF00, 0xBF00, 0x2001, 0x0780, 0x6901, 0x2201, 0x4311,
    0x6101, 0x4770,
};

__asm void EnterSleepMode(void)
{
    IMPORT Code_EnterSleepMode
    PUSH {LR}
    NOP
    LDR R0,=Code_EnterSleepMode
    ADDS R0, R0, #1
    NOP
    BLX R0
    POP {R0}
    BX R0
}


/* 进入休眠Stop模式的代码指令，生成这段儿指令的C代码是：
void EnterStopMode(void)
{
    __NOP();__NOP();__NOP();
    SYS->SLEEP |= (1 << SYS_SLEEP_STOP_Pos);
}
*/
uint16_t Code_EnterStopMode[] = {
    0xBF00, 0xBF00, 0xBF00, 0x2001, 0x0780, 0x6901, 0x2202, 0x4311,
    0x6101, 0x4770,
};

__asm void EnterStopMode(void)
{
    IMPORT Code_EnterStopMode
    PUSH {LR}
    NOP
    LDR R0,=Code_EnterStopMode
    ADDS R0, R0, #1
    NOP
    BLX R0
    POP {R0}
    BX R0
}

#elif defined ( __ICCARM__ )

__ramfunc void EnterSleepMode(void)
{
    __NOP();__NOP();__NOP();
    SYS->SLEEP |= (1 << SYS_SLEEP_SLEEP_Pos);
}

__ramfunc void EnterStopMode(void)
{
    __NOP();__NOP();__NOP();
    SYS->SLEEP |= (1 << SYS_SLEEP_STOP_Pos);
}

#endif
