/******************************************************************************
*Copyright(C)2018, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
* 
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/

/** \file sysctrl.c
 **
 ** Common API of sysctrl.
 ** @link SysctrlGroup Some description @endlink
 **
 **   - 2018-04-22 Lux
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "sysctrl.h"

/**
 *******************************************************************************
 ** \addtogroup SysctrlGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CLK_TIMEOUT             (1000000u)

#define IS_VALID_SRC(x)         (   ClkRCH == (x)||\
                                    ClkXTH == (x)||\
                                    ClkRCL == (x)||\
                                    ClkXTL == (x) )


#define IS_VALID_FUNC(x)        (   ClkFuncWkupRCH == (x)||\
                                    ClkFuncXTHEn == (x)||\
                                    ClkFuncXTLEn == (x)||\
                                    ClkFuncXTLAWSON == (x)||\
                                    ClkFuncFaultEn == (x)||\
                                    ClkFuncRtcLPWEn == (x)||\
                                    ClkFuncLockUpEn == (x)||\
                                    ClkFuncRstPinIOEn == (x)||\
                                    ClkFuncSwdPinIOEn == (x) )

#define RCH_CR_TRIM_24M_VAL         (*((volatile uint16_t*) (0x00100C00ul)))
#define RCH_CR_TRIM_22_12M_VAL      (*((volatile uint16_t*) (0x00100C02ul)))
#define RCH_CR_TRIM_16M_VAL         (*((volatile uint16_t*) (0x00100C04ul)))
#define RCH_CR_TRIM_8M_VAL          (*((volatile uint16_t*) (0x00100C06ul)))
#define RCH_CR_TRIM_4M_VAL          (*((volatile uint16_t*) (0x00100C08ul)))

#define RCL_CR_TRIM_38400_VAL       (*((volatile uint16_t*) (0x00100C20ul)))
#define RCL_CR_TRIM_32768_VAL       (*((volatile uint16_t*) (0x00100C22ul)))

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
extern uint32_t SystemCoreClock;
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/


/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 *******************************************************************************
 ** \brief SYSCTRL0\SYSCTRL1寄存器操作解锁
 **
 ** \retval None
 ******************************************************************************/
static void _SysctrlUnlock(void)
{
    M0P_SYSCTRL->SYSCTRL2 = 0x5A5A;
    M0P_SYSCTRL->SYSCTRL2 = 0xA5A5;
}

/**
 *******************************************************************************
 ** \brief 系统时钟源使能
 ** \param [in]  enSource   目标时钟源
 ** \param [in]  bFlag      使能1-开/0-关
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_ClkSourceEnable(en_sysctrl_clk_source_t enSource, boolean_t bFlag)
{
    en_result_t enRet = Ok;

    _SysctrlUnlock();
    bFlag = !!bFlag;

    switch (enSource)
    {
        case SysctrlClkRCH:
            M0P_SYSCTRL->SYSCTRL0_f.RCH_EN = bFlag;
            while(bFlag && (1 != M0P_SYSCTRL->RCH_CR_f.STABLE))
            {
                ;
            }
            break;
        
        case SysctrlClkXTH:
            M0P_GPIO->PDADS_f.PD00 = 1;
            M0P_GPIO->PDADS_f.PD01 = 1;           
            M0P_SYSCTRL->SYSCTRL0_f.XTH_EN = bFlag;
            while(bFlag && (1 != M0P_SYSCTRL->XTH_CR_f.STABLE))
            {
                ;
            }
            break;

        case SysctrlClkRCL:
            M0P_SYSCTRL->SYSCTRL0_f.RCL_EN = bFlag;
            while(bFlag && (1 != M0P_SYSCTRL->RCL_CR_f.STABLE))
            {
                ;
            }
            break;
        
        case SysctrlClkXTL:
            M0P_GPIO->PCADS_f.PC14 = 1;
            M0P_GPIO->PCADS_f.PC15 = 1;
            M0P_SYSCTRL->SYSCTRL0_f.XTL_EN = bFlag;
            while(bFlag && (1 != M0P_SYSCTRL->XTL_CR_f.STABLE))
            {
                ;
            }
            break;

        case SysctrlClkPLL:
            M0P_SYSCTRL->SYSCTRL0_f.PLL_EN = bFlag;
            while(bFlag && (1 != M0P_SYSCTRL->PLL_CR_f.STABLE))
            {
                ;
            }
            break;
        
        default:
            enRet = ErrorInvalidParameter;
            break;
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief 外部高速晶振驱动配置
 ** \param [in]  enFreq     外部高速晶振频率范围选择
 ** \param [in]  enDriver   外部高速晶振驱动能力选择
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_XTHDriverConfig(en_sysctrl_xtal_driver_t enDriver)
{
    en_result_t enRet = Ok;
    
    M0P_SYSCTRL->XTH_CR_f.DRIVER   = enDriver;
    
    return enRet;
}

/**
 *******************************************************************************
 ** \brief 外部低速晶振驱动配置
 ** \param [in]  enFreq     外部低速晶振频率范围选择
 ** \param [in]  enDriver   外部低速晶振驱动能力选择
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_XTLDriverConfig(en_sysctrl_xtl_amp_t enAmp, en_sysctrl_xtal_driver_t enDriver)
{
    en_result_t enRet = Ok;
    
    M0P_SYSCTRL->XTL_CR_f.AMP_SEL = enAmp; 
    M0P_SYSCTRL->XTL_CR_f.DRIVER  = enDriver;
    
    return enRet;
}

/**
 *******************************************************************************
 ** \brief 外部高速时钟稳定周期配置
 ** \param [in]  enCycle     外部高速时钟稳定周期设置
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetXTHStableTime(en_sysctrl_xth_cycle_t enCycle)
{
    en_result_t enRet = Ok;
    M0P_SYSCTRL->XTH_CR_f.STARTUP = enCycle;
    return enRet;
}

/**
 *******************************************************************************
 ** \brief 内部低速时钟稳定周期配置
 ** \param [in]  enCycle     内部低速时钟稳定周期设置
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetRCLStableTime(en_sysctrl_rcl_cycle_t enCycle)
{
    en_result_t enRet = Ok;
    M0P_SYSCTRL->RCL_CR_f.STARTUP = enCycle;
    return enRet;
}

/**
 *******************************************************************************
 ** \brief 外部低速时钟稳定周期配置
 ** \param [in]  enCycle     外部低速时钟稳定周期设置
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetXTLStableTime(en_sysctrl_xtl_cycle_t enCycle)
{
    en_result_t enRet = Ok;
    M0P_SYSCTRL->XTL_CR_f.STARTUP = enCycle;
    return enRet;
}

/**
 *******************************************************************************
 ** \brief PLL稳定周期配置
 ** \param [in]  enCycle    PLL稳定周期设置
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetPLLStableTime(en_sysctrl_pll_cycle_t enCycle)
{
    en_result_t enRet = Ok;
    M0P_SYSCTRL->PLL_CR_f.STARTUP = enCycle;
    return enRet;
}

/**
 *******************************************************************************
 ** \brief 时钟源切换，该函数执行后会开启新时钟源
 ** \note  选择时钟源之前，需根据需要配置目标时钟源的频率/驱动参数/使能时钟源等
 ** \param [in]  enSource   新时钟源
 ** 
 ** \retval      Ok         设定成功
 **              其他       设定失败
 ******************************************************************************/
en_result_t Sysctrl_SysClkSwitch(en_sysctrl_clk_source_t enSource)
{
    en_result_t enRet = Ok;
    
    en_sysctrl_clk_source_t ClkNew = enSource;

    _SysctrlUnlock();
    M0P_SYSCTRL->SYSCTRL0_f.CLK_SW5_SEL = ClkNew;

    //更新Core时钟（HCLK）
    SystemCoreClockUpdate();

    return enRet;
}

/**
 *******************************************************************************
 ** \brief   获得系统时钟（HCLK）频率值    
 ** \retval  uint32_t         HCLK频率值
 **
 ******************************************************************************/
uint32_t Sysctrl_GetHClkFreq(void)
{
    uint32_t u32Val = 0;
    const uint32_t u32hcr_tbl[] = { 4000000, 8000000, 16000000, 22120000, 24000000};
    const uint16_t u32lcr_tbl[] = { 32768, 38400};
    en_sysctrl_clk_source_t enSrc;
    uint16_t u16Trim[5] = {0};
    u16Trim[4] = RCH_CR_TRIM_24M_VAL;
    u16Trim[3] = RCH_CR_TRIM_22_12M_VAL;
    u16Trim[2] = RCH_CR_TRIM_16M_VAL;
    u16Trim[1] = RCH_CR_TRIM_8M_VAL;
    u16Trim[0] = RCL_CR_TRIM_38400_VAL;

    //获取当前系统时钟
    enSrc = (en_sysctrl_clk_source_t)(M0P_SYSCTRL->SYSCTRL0_f.CLK_SW5_SEL);
    
    switch (enSrc)
    {
        case SysctrlClkRCH:
            {
                
                if((M0P_SYSCTRL->RCH_CR_f.TRIM) == (u16Trim[4]))
                {
                    u32Val = u32hcr_tbl[4];
                }
                else if((M0P_SYSCTRL->RCH_CR_f.TRIM) == (u16Trim[3]))
                {
                    u32Val = u32hcr_tbl[3];
                }                   
                else if((M0P_SYSCTRL->RCH_CR_f.TRIM) == (u16Trim[2]))
                {
                    u32Val = u32hcr_tbl[2];
                }    
                else if((M0P_SYSCTRL->RCH_CR_f.TRIM) == (u16Trim[1]))
                {
                    u32Val = u32hcr_tbl[1];
                }
                else
                {
                    u32Val = u32hcr_tbl[0];
                }
            }
            break;
        case SysctrlClkXTH:
            u32Val = SYSTEM_XTH;
            break;
        case SysctrlClkRCL:
            {
                if(u16Trim[0] == (M0P_SYSCTRL->RCL_CR_f.TRIM))
                {
                    u32Val = u32lcr_tbl[1];
                }
                else
                {
                    u32Val = u32lcr_tbl[0];
                }
            }
            break;
        case SysctrlClkXTL:
            u32Val = SYSTEM_XTL;
            break;
        case SysctrlClkPLL:
            {
                if (SysctrlPllRch == M0P_SYSCTRL->PLL_CR_f.REFSEL)
                {
                    if(u16Trim[4] == M0P_SYSCTRL->RCH_CR_f.TRIM)
                    {
                        u32Val = u32hcr_tbl[4];
                    }
                    else if(u16Trim[3] == M0P_SYSCTRL->RCH_CR_f.TRIM)
                    {
                        u32Val = u32hcr_tbl[3];
                    }                   
                    else if(u16Trim[2] == M0P_SYSCTRL->RCH_CR_f.TRIM)
                    {
                        u32Val = u32hcr_tbl[2];
                    }    
                    else if(u16Trim[1] == M0P_SYSCTRL->RCH_CR_f.TRIM)
                    {
                        u32Val = u32hcr_tbl[1];
                    }
                    else
                    {
                        u32Val = u32hcr_tbl[0];
                    }
                }
                else
                {
                    u32Val = SYSTEM_XTH;
                }
                
                u32Val = (u32Val * M0P_SYSCTRL->PLL_CR_f.DIVN);
            }
            break;        
        default:
            u32Val = 0u;
            break;
    }

    u32Val = (u32Val >> M0P_SYSCTRL->SYSCTRL0_f.HCLK_PRS);

    return u32Val;
}

/**
 *******************************************************************************
 ** \brief 获得外设时钟（PCLK）频率值    
 ** \retval uint32_t   PCLK频率值(Hz)
 **
 ******************************************************************************/
uint32_t Sysctrl_GetPClkFreq(void)
{
    uint32_t u32Val = 0;

    u32Val = Sysctrl_GetHClkFreq();
    u32Val = (u32Val >> (M0P_SYSCTRL->SYSCTRL0_f.PCLK_PRS));

    return u32Val;
}


/**
 *******************************************************************************
 ** \brief 时钟初始化函数
 ** \param [in]  pstcCfg    初始化配置参数   
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_ClkInit(stc_sysctrl_clk_config_t *pstcCfg)
{
    en_result_t enRet = Ok;
    
    //系统时钟参数配置
    switch(pstcCfg->enClkSrc)
    {   
        case SysctrlClkRCH:  

            break;    
        case SysctrlClkXTH:    
            Sysctrl_XTHDriverConfig(SysctrlXtalDriver3);
            Sysctrl_SetXTHStableTime(SysctrlXthStableCycle16384);           
            break;    
        case SysctrlClkRCL:    
            Sysctrl_SetRCLStableTime(SysctrlRclStableCycle256);    
            break;    
        case SysctrlClkXTL:    
            Sysctrl_XTLDriverConfig(SysctrlXtlAmp3, SysctrlXtalDriver3);
            Sysctrl_SetXTLStableTime(SysctrlXtlStableCycle16384);
            break;
        case SysctrlClkPLL:    
            Sysctrl_SetPLLStableTime(SysctrlPllStableCycle16384);
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }
    
    //时钟源使能
    Sysctrl_ClkSourceEnable(pstcCfg->enClkSrc, TRUE);
    
    //时钟源切换
    Sysctrl_SysClkSwitch(pstcCfg->enClkSrc);
    
    //时钟分频设置
    Sysctrl_SetHCLKDiv(pstcCfg->enHClkDiv);
    Sysctrl_SetPCLKDiv(pstcCfg->enPClkDiv);

    return enRet;
}

/**
 *******************************************************************************
 ** \brief 时钟去初始化函数
 ** \param [in]  
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_ClkDeInit(void)
{
    en_result_t enRet = Ok;
    
    //配置RCH为内部4Hz
    Sysctrl_SetRCHTrim(SysctrlRchFreq4MHz);
    
    //时钟源使能
    Sysctrl_ClkSourceEnable(SysctrlClkRCH, TRUE);
    
    //时钟源切换
    Sysctrl_SysClkSwitch(SysctrlClkRCH);
    
    //其它时钟源使能关闭
    Sysctrl_ClkSourceEnable(SysctrlClkXTH, FALSE);
    Sysctrl_ClkSourceEnable(SysctrlClkRCL, FALSE);
    Sysctrl_ClkSourceEnable(SysctrlClkXTL, FALSE);
    Sysctrl_ClkSourceEnable(SysctrlClkPLL, FALSE);
    
    //时钟分频设置
    Sysctrl_SetHCLKDiv(SysctrlHclkDiv1);
    Sysctrl_SetPCLKDiv(SysctrlPclkDiv1);
    
    return enRet;
}

/**
 *******************************************************************************
 ** \brief 内部高速时钟频率TRIM值加载
 ** \param [in]  enRCHFreq  设定的RCH目标频率值
 ** \retval      Ok         设定成功
 **             其他        设定失败或时钟未稳定
 ******************************************************************************/
en_result_t Sysctrl_SetRCHTrim(en_sysctrl_rch_freq_t enRCHFreq)
{
    en_result_t enRet = Ok;

    //加载RCH Trim值
    switch (enRCHFreq)
    {
        case SysctrlRchFreq4MHz:
            M0P_SYSCTRL->RCH_CR_f.TRIM = RCH_CR_TRIM_4M_VAL;
            break;
        case SysctrlRchFreq8MHz:
            M0P_SYSCTRL->RCH_CR_f.TRIM = RCH_CR_TRIM_8M_VAL;
            break;
        case SysctrlRchFreq16MHz:
            M0P_SYSCTRL->RCH_CR_f.TRIM = RCH_CR_TRIM_16M_VAL;
            break;
        case SysctrlRchFreq22_12MHz:
            M0P_SYSCTRL->RCH_CR_f.TRIM = RCH_CR_TRIM_22_12M_VAL;
            break;
        case SysctrlRchFreq24MHz:
            M0P_SYSCTRL->RCH_CR_f.TRIM = RCH_CR_TRIM_24M_VAL;
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }
    
    return enRet;
}

/**
 *******************************************************************************
 ** \brief 外部高速时钟频率范围设定
 ** \param [in]  enXTHFreq  设定的频率值
 ** \retval      Ok         设定成功
 **              其他       设定失败或时钟未稳定
 ******************************************************************************/
en_result_t Sysctrl_SetXTHFreq(en_sysctrl_xth_freq_t enXTHFreq)
{
    en_result_t enRet = Ok;

    M0P_SYSCTRL->XTH_CR_f.XTH_FSEL = enXTHFreq;
    
    return enRet;
}

/**
 *******************************************************************************
 ** \brief PLL时钟配置
 ** \param [in]  pstcPLLCfg PLL配置结构体指针
 ** \retval      Ok         设定成功
 **              其他       设定失败或参数值不匹配
 ******************************************************************************/
en_result_t Sysctrl_SetPLLFreq(stc_sysctrl_pll_config_t *pstcPLLCfg)
{
    en_result_t enRet = Ok;    
    
    uint16_t u16Trim[5] = {0};
    u16Trim[4] = RCH_CR_TRIM_24M_VAL;
    u16Trim[3] = RCH_CR_TRIM_22_12M_VAL;
    u16Trim[2] = RCH_CR_TRIM_16M_VAL;
    u16Trim[1] = RCH_CR_TRIM_8M_VAL;
    
    ////PLL最高时钟不能超过48MHz
    //RCH作为PLL输入
    if (SysctrlPllRch == pstcPLLCfg->enPllClkSrc)
    {
        if( ((u16Trim[4] == M0P_SYSCTRL->RCH_CR_f.TRIM) && (pstcPLLCfg->enPllMul > 2)) ||                
            ((u16Trim[3] == M0P_SYSCTRL->RCH_CR_f.TRIM) && (pstcPLLCfg->enPllMul > 2)) ||
            ((u16Trim[2] == M0P_SYSCTRL->RCH_CR_f.TRIM) && (pstcPLLCfg->enPllMul > 3)) ||   
            ((u16Trim[1] == M0P_SYSCTRL->RCH_CR_f.TRIM) && (pstcPLLCfg->enPllMul > 6)))
        {
            return ErrorInvalidMode;
        }
    }
    else    //XTH作为PLL输入
    {
        if ((SYSTEM_XTH * pstcPLLCfg->enPllMul) > 48*1000*1000)
        {
            return ErrorInvalidMode;
        }
    }
    
    M0P_SYSCTRL->PLL_CR_f.FRSEL  = pstcPLLCfg->enInFreq;
    M0P_SYSCTRL->PLL_CR_f.FOSC   = pstcPLLCfg->enOutFreq;
    M0P_SYSCTRL->PLL_CR_f.DIVN   = pstcPLLCfg->enPllMul;
    M0P_SYSCTRL->PLL_CR_f.REFSEL = pstcPLLCfg->enPllClkSrc;
 
    return enRet;    
}

/**
 *******************************************************************************
 ** \brief 内部低速时钟频率TRIM值加载
 ** \param [in]  enRCLFreq  设定的RCL目标频率值
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetRCLTrim(en_sysctrl_rcl_freq_t enRCLFreq)
{
    en_result_t enRet = Ok;

    switch (enRCLFreq)
    {
        case SysctrlRclFreq32768:
            M0P_SYSCTRL->RCL_CR_f.TRIM = RCL_CR_TRIM_32768_VAL;
            break;
        case SysctrlRclFreq38400:
            M0P_SYSCTRL->RCL_CR_f.TRIM = RCL_CR_TRIM_38400_VAL;
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief 系统时钟（HCLK）分频设定
 ** \param [in]  enHCLKDiv  分频设定值
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetHCLKDiv(en_sysctrl_hclk_div_t enHCLKDiv)
{
    en_result_t enRet = Ok;
    
    _SysctrlUnlock();
    M0P_SYSCTRL->SYSCTRL0_f.HCLK_PRS = enHCLKDiv;

    return enRet;
}

/**
 *******************************************************************************
 ** \brief 外设时钟（PCLK）分频设定
 ** \param [in]  enPCLKDiv  分频设定值
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetPCLKDiv(en_sysctrl_pclk_div_t enPCLKDiv)
{
    en_result_t enRet = Ok;
    
    _SysctrlUnlock();
    M0P_SYSCTRL->SYSCTRL0_f.PCLK_PRS = enPCLKDiv;
    
    return enRet;
}

/**
 *******************************************************************************
 ** \brief 设置外设时钟门控开关
 ** \param [in]  enPeripheral   目标外设
 ** \param [in]  bFlag          使能开关
 ** \retval      Ok             设定成功
 **             其他            设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral, boolean_t bFlag)
{
    en_result_t enRet = Ok;

    bFlag = !!bFlag;
    
    setBit(&(M0P_SYSCTRL->PERI_CLKEN), enPeripheral, bFlag);
    
    return enRet;
}

/**
 *******************************************************************************
 ** \brief 获得外设时钟门控开关状态
 ** \param [in]  enPeripheral   目标外设
 ** \retval      TRUE           开
 **              FALSE          关
 ******************************************************************************/
boolean_t Sysctrl_GetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral)
{       
    return getBit(&(M0P_SYSCTRL->PERI_CLKEN), enPeripheral);
}

/**
 *******************************************************************************
 ** \brief 系统功能设定
 ** \param [in]  enFunc     系统功能枚举类型
 ** \param [in]  bFlag      1-开/0-关
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetFunc(en_sysctrl_func_t enFunc, boolean_t bFlag)
{
    en_result_t enRet = Ok;
    
    _SysctrlUnlock();
    bFlag = !!bFlag;

    switch (enFunc)
    {
        case SysctrlWkupByRCHEn:
            M0P_SYSCTRL->SYSCTRL0_f.WAKEUP_BYRCH = bFlag;
            break;
        case SysctrlEXTHEn:
            M0P_SYSCTRL->SYSCTRL1_f.EXTH_EN = bFlag;
            break;
        case SysctrlEXTLEn:
            M0P_SYSCTRL->SYSCTRL1_f.EXTL_EN = bFlag;
            break;
        case SysctrlXTLAlwaysOnEn:
            M0P_SYSCTRL->SYSCTRL1_f.XTL_ALWAYS_ON = bFlag;
            break;
        case SysctrlClkFuncRTCLpmEn:
            M0P_SYSCTRL->SYSCTRL1_f.RTC_LPW = bFlag;
            break;
        case SysctrlCMLockUpEn:
            M0P_SYSCTRL->SYSCTRL1_f.LOCKUP_EN = bFlag;
            break;
        case SysctrlSWDUseIOEn:
            M0P_SYSCTRL->SYSCTRL1_f.SWD_USE_IO = bFlag;
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief 设定RTC校准时钟频率
 ** \param [in]  enRtcAdj   校准频率值
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Sysctrl_SetRTCAdjustClkFreq(en_sysctrl_rtc_adjust_t enRtcAdj)
{
    en_result_t enRet = Ok;

    _SysctrlUnlock();
    M0P_SYSCTRL->SYSCTRL1_f.RTC_FREQ_ADJUST = enRtcAdj;

    return enRet;
}

//@} // SysctrlGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
