/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *文件名：  lib_scu.c
 *作  者：  Liut
 *版  本：  V1.00
 *日  期：  2017/07/14
 *描  述：  系统控制模块库函数
 *备  注：  适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#include "lib_scu.h"

/***************************************************************
  函数名：SCU_OpenXTAL
  描  述: 开启外部时钟
  输入值：无
  输出值：无
  返回值：系统时钟源
 ***************************************************************/
void SCU_OpenXTAL(void)
{
	SCU_RegUnLock();
	SCU->SCLKEN1.XTAL_EN = 1;
	SCU->SCLKEN0.XTAL_LP = 0;
	while(SCU->SCLKEN1.XTAL_RDY == 0); //等待外部时钟稳定
	SCU_RegLock() ;
}

/***************************************************************
  函数名：SCU_NMISelect
  描  述：设置NMI不可屏蔽中断
  输入值：不可屏蔽中断
  输出值：无
  返回值：无
 ***************************************************************/
void SCU_NMISelect(SCU_TYPE_NMICS NMI_Type)
{
	  SCU_RegUnLock();
    SCU->NMICON.NMICS = NMI_Type;
	  SCU_RegLock() ;
}

/***************************************************************
  函数名：SCU_GetPWRCFlagStatus
  描  述：获取PWRC复位状态寄存器标志位状态
  输入值：PWRC寄存器标志位
  输出值：无
  返回值：RESET/SET
 ***************************************************************/
FlagStatus  SCU_GetPWRCFlagStatus(SCU_TYPE_PWRC PWRC_Flag)
{
    FlagStatus bitstatus = RESET;
    if((SCU->PWRC.Word & (uint32_t)PWRC_Flag) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  函数名：SCU_ClearPWRCFlagBit
  描  述：清除PWRC复位状态寄存器标志位
  输入值：PWRC寄存器标志位
  输出值：无
  返回值：无
 ***************************************************************/
void SCU_ClearPWRCFlagBit(SCU_TYPE_PWRC PWRC_Flag)
{
	  SCU_RegUnLock() ;
    SCU->PWRC.Word &= ~((uint32_t)PWRC_Flag);
	  SCU_RegLock() ;
}

/***************************************************************
  函数名：SCU_GetLVDFlagStatus
  描  述：获取LVDD寄存器标志位状态
  输入值：LVD寄存器标志位
  输出值：无
  返回值：RESET/SET
 ***************************************************************/
FlagStatus  SCU_GetLVDFlagStatus(SCU_TYPE_LVD0CON LVD_Flag)
{
    FlagStatus bitstatus = RESET;

    if((SCU->LVDCON.Word & (uint32_t)LVD_Flag) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  函数名：SCU_SysClkSelect
  描  述：选择系统时钟
  输入值：时钟源
  输出值：无
  返回值：无
 ***************************************************************/
void SCU_SysClkSelect(SCU_TYPE_SYSCLK Sysclk)
{
	  SCU_RegUnLock() ;
    SCU->SCLKEN0.CLK_SEL = Sysclk;
	  SCU_RegLock() ;
}

/***************************************************************
  函数名：SCU_GetSysClk
  描  述：获取系统时钟源
  输入值：无
  输出值：无
  返回值：系统时钟源
 ***************************************************************/
SCU_TYPE_SYSCLK SCU_GetSysClk(void)
{
    return (SCU_TYPE_SYSCLK)(SCU->SCLKEN0.CLK_SEL);
}

/***************************************************************
  函数名：SCU_HRCReadyFlag
  描  述：获取HRC稳定标志位
  输入值：无
  输出值：无
  返回值：RESET（不稳定）/SET（稳定）
 ***************************************************************/
FlagStatus SCU_HRCReadyFlag(void)
{
    FlagStatus bitstatus = RESET;

    if((SCU->SCLKEN1.HRC_RDY) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  函数名：SCU_XTALReadyFlag
  描  述：获取XTAL稳定标志位
  输入值：无
  输出值：无
  返回值：RESET（不稳定）/SET（稳定）
 ***************************************************************/
FlagStatus  SCU_XTALReadyFlag(void)
{
    FlagStatus bitstatus = RESET;

    if((SCU->SCLKEN1.XTAL_RDY) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  函数名：SCU_LOSCReadyFlag
  描  述：获取LOSC稳定标志位
  输入值：无
  输出值：无
  返回值：RESET（不稳定）/SET（稳定）
 ***************************************************************/
FlagStatus  SCU_PLLReadyFlag(void)
{
    FlagStatus bitstatus = RESET;

    if((SCU->SCLKEN1.PLL_RDY) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
 函数名：SystemClockConfig
 描  述：系统时钟配置：内部时钟，20MHZ，打开所有外设时钟
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void SystemClockConfig(void)
{
    uint32_t Prot_Temp;

    Prot_Temp = SCU->PROT.PROT;

    if(Prot_Temp != 0)                      //写保护了
        SCU_RegUnLock();                    //解锁

    SCU_HRC_Enable();                       //使能内部20MHZ
    while(SCU_HRCReadyFlag() != SET);       //等待时钟开启
    SCU_SysClkSelect(SCU_SysClk_HRC);       //选择内部20MHZ为系统时钟
	
    SCU_SysClk_Div1();                      //系统时钟后分频1:1    
    
    SystemCoreClock = 20000000;

    if(Prot_Temp != 0)                      //写保护了
        SCU_RegLock();                      //打开写保护
}

/***************************************************************
  函数名：DeviceClockAllEnable
  描  述：打开所有外设时钟
  输入值：无
  输出值：无
  返回值：无
 ***************************************************************/
void DeviceClockAllEnable(void)
{
    uint32_t Prot_Temp;

    Prot_Temp = SCU->PROT.PROT;
    if(Prot_Temp != 0)                      //写保护了
        SCU_RegUnLock();                    //解锁

    SCU->PCLKEN0.Word = 0xFFFFFFFF;
    SCU->PCLKEN1.Word = 0xFFFFFFFF;         //打开所有外设时钟

    if(Prot_Temp != 0)                      //写保护了
        SCU_RegLock();                      //打开写保护
}

/***************************************************************
  函数名：DeviceClockAllDisable
  描  述：关闭所有外设时钟
  输入值：无
  输出值：无
  返回值：无
 ***************************************************************/
void DeviceClockAllDisable(void)
{
    uint32_t Prot_Temp;

    Prot_Temp = SCU->PROT.PROT;
    if(Prot_Temp != 0)                      //写保护了
        SCU_RegUnLock();                    //解锁

    SCU->PCLKEN0.Word = 0x00000000;         //关闭所有外设时钟，scu无法关闭
    SCU->PCLKEN1.Word = 0x00000000;

    if(Prot_Temp != 0)                      //写保护了
        SCU_RegLock();                  //打开写保护
}

/***************************************************************
  函数名：SystemClockConfig
  描  述：系统时钟选择
  输入值：CLKx 系统时钟源选择
  输出值：无
  返回值：无
 ***************************************************************/
void SystemClockSelect(SCU_TYPE_SYSCLK SYSCLKx , SCU_TYPE_CLK_SEL CLK_SEL)
{
    SCU_RegUnLock();                        //解锁

    switch(SYSCLKx)
    {
        case 0:
            SCU_HRC_Enable();
            while(SCU_HRCReadyFlag() != SET);
            break;
        case 1:
            SCU_XTAL_Enable();
            while(SCU_XTALReadyFlag() != SET);
            break;
        case 2:
            SCU_PLL_Enable();
            while(SCU_PLLReadyFlag() != SET);
            break;
        default:break;
    }

    SCU->SCLKEN0.SYSCLK_DIV = 0;
    SCU->SCLKEN0.CLK_SEL = CLK_SEL;

    SCU_RegLock();
}


/***************************************************************
  函数名：PLLClock_Config
  描  述：PLL时钟配置,并设置PLL时钟为系统时钟
  输入值：pll_en:是否开启PLL，pll_origin：pll时钟源选择，pll_out：pll输出频率选择，sys_pll：系统时钟是否使用PLL时钟
  输出值：无
  返回值：无
 ***************************************************************/
void PLLClock_Config(TYPE_FUNCEN pll_en , SCU_PLL_Origin  pll_origin ,SCU_PLL_Out pll_out,TYPE_FUNCEN sys_pll)
{
    SCU_RegUnLock();

    if(pll_en == DISABLE)  //如果PLL配置为禁止，则直接禁止PLL，并返回
    {
        SCU->SCLKEN0.PLL_MUX = 0;
        SCU->SCLKEN1.PLL_BYLOCK = 0;
        SCU->SCLKEN0.CLKFLT_BY = 0x00;
        SCU->SCLKEN1.PLL_EN = 0;
        return;
    }

    if((pll_origin == SCU_PLL_HRC))         //如果使用内部高速时钟，需开启内部高速时钟
    {
        if(SCU->SCLKEN1.HRC_RDY == 0)
        {
            SCU->SCLKEN1.HRC_EN = 1;
            while(SCU->SCLKEN1.HRC_RDY == 0);  //等待HRC开启
        }
    }

    if((pll_origin == SCU_PLL_XTAL_32K)
       || (pll_origin == SCU_PLL_XTAL_4M)
       ||(pll_origin == SCU_PLL_XTAL_8M)
       || (pll_origin == SCU_PLL_XTAL_16M)
       || (pll_origin == SCU_PLL_XTAL_20M))          //如果使用外部时钟，需开启外部时钟
    {
        if(SCU->SCLKEN1.XTAL_RDY == 0)
        {
            SCU->SCLKEN1.XTAL_EN = 1;
					  SCU->SCLKEN0.XTAL_LP = 0;
            while(SCU->SCLKEN1.XTAL_RDY == 0);  //等待XTAL开启
        }
    }

    switch(pll_origin)
    {
        case SCU_PLL_HRC:
            SCU->SCLKEN1.PLL_REF_SEL = 0x00;
            break;
        case SCU_PLL_LRC:
            SCU->SCLKEN1.PLL_REF_SEL = 0x02;
            break;
        case SCU_PLL_XTAL_32K:
            SCU->SCLKEN1.PLL_REF_SEL = 0x03;
            break;
        case SCU_PLL_XTAL_4M:
            SCU->SCLKEN1.PLL_REF_SEL = 0x04;
            break;
        case SCU_PLL_XTAL_8M:
            SCU->SCLKEN1.PLL_REF_SEL = 0x05;
            break;
        case SCU_PLL_XTAL_16M:
            SCU->SCLKEN1.PLL_REF_SEL = 0x06;
            break;
        case SCU_PLL_XTAL_20M:
            SCU->SCLKEN1.PLL_REF_SEL = 0x07;
            break;
        default:
            break;
    }

    SCU->SCLKEN1.PLL_48M_SEL = pll_out;   //配置PLL输出为32或48Mhz

    SCU->SCLKEN1.PLL_EN = 1;
    while(SCU->SCLKEN1.PLL_RDY == 0);


    if(sys_pll == ENABLE)
    {

        if(pll_out == SCU_PLL_32M)
        {
          SCU->SCLKEN0.CLKFLT_BY = 0;
        }
        else
        {
          SCU->SCLKEN0.CLKFLT_BY = 0x55;  //48M 时钟滤波旁路
        }
        SCU->SCLKEN1.PLL_BYLOCK = 1;
        SCU->SCLKEN0.PLL_MUX = 1;
    }
    else
    {
        SCU->SCLKEN0.PLL_MUX = 0;
        SCU->SCLKEN1.PLL_BYLOCK = 0;
        SCU->SCLKEN0.CLKFLT_BY = 0x00;
    }

    SCU_RegLock(); 
}

/*************************END OF FILE**********************/



