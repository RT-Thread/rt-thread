/***************************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名：  system_ES8P508x.c
*作  者：  Liut
*版  本：  V1.00
*日  期：  2017/07/14
*描  述：  库函数配置文件
*备  注：  适用于 ES8P508x芯片
           本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
***************************************************************/
#include "system_ES8P508x.h"
#include "lib_config.h"

uint32_t SystemCoreClock = 48000000;


/***************************************************************
函数名：SystemCoreClockUpdate
描  述：系统时钟配置为内部时钟20MHZ，同时设置SystemCoreClock
输入值：无
输出值：无
返回值：无
***************************************************************/
void SystemCoreClockUpdate (void)
{
    uint32_t Prot_Temp;
    uint16_t Count=0;
    SystemClockSelect(SCU_SysClk_HRC , CLK_SEL_HRC);        //选择系统时钟为HRC时钟
    PLLClock_Config(DISABLE, SCU_PLL_HRC, SCU_PLL_48M,ENABLE);    //PLL禁止
    Prot_Temp = SCU->PROT.PROT;
    if(Prot_Temp != 0)                                      //写保护了
        {SCU->PROT.Word = 0x55AA6996;}                      //解锁

    SCU->SCLKEN1.HRC_EN = 1;                                //使能内部20MHZ
    do
    {
        Count++;
    }
    while((SCU->SCLKEN1.HRC_RDY == 0)&&(Count != 0xFFF));   //等待时钟开启

    if(Count == 0xFFF)
    {
        return ;
    }

    SCU->SCLKEN0.SYSCLK_DIV = 0;                            //系统时钟后分频1:1

    switch(SCU->SCLKEN0.CLK_SEL)
    {
        case 0:
            SystemCoreClock = 20000000;                     //HRC
            break;
        case 1:
            SystemCoreClock = 32000;                        //LRC
            break;
        default:
            break;
    }

    if(Prot_Temp != 0)                                      //写保护了
        {SCU->PROT.Word = 0x00000000;}                      //打开写保护
}

/***************************************************************
函数名：SystemInit
描  述：系统初始化，设置时钟
输入值：无
输出值：无
返回值：无
***************************************************************/
void SystemInit (void)
{
    SystemCoreClockUpdate();
}

/*************************END OF FILE**********************/
