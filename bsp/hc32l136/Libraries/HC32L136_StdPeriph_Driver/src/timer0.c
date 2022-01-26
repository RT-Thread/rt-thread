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

/** \file timer3.c
 **
 ** Common API of base timer.
 ** @link BT Tiemr3 Group Some description @endlink
 **
 **   - 2018-04-18    First Version
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "timer0.h"
/**
 *******************************************************************************
 ** \addtogroup Tim0Group
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
//#define IS_VALID_TIM(x)         (TIM0 == (x) || TIM1 == (x) || TIM2 == (x))

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static func_ptr_t pfnTim0Callback = NULL;


/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/


/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 *****************************************************************************
 ** \brief Base Timer3 中断标志获取(模式0/1/23)
 **
 **
 ** \param [in]  enTim0Irq           中断类型
 ** 
 ** \retval TRUE or FALSE                                      
 *****************************************************************************/
boolean_t Tim0_GetIntFlag(en_tim0_irq_type_t enTim0Irq)
{
    boolean_t bRetVal = FALSE;
    uint32_t u32Val;
        
    u32Val = M0P_TIM0_MODE23->IFR;
    bRetVal = (u32Val>>enTim0Irq) & 0x1;

    return bRetVal;
}

/**
 *****************************************************************************
 ** \brief Base Timer3 中断标志清除(模式0/1/23)
 **
 **
 ** \param [in]  enTim0Irq           中断类型
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_ClearIntFlag(en_tim0_irq_type_t enTim0Irq)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE23->ICLR = ~(1u<<enTim0Irq);
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer3 中断所有标志清除(模式23)
 **
 **
 ** 
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_ClearAllIntFlag(void)
{
    en_result_t enResult = Ok;
    
    M0P_TIM0_MODE23->ICLR_f.BIF = 0;
    M0P_TIM0_MODE23->ICLR_f.CA0E = 0;
    M0P_TIM0_MODE23->ICLR_f.CA0F = 0;
    M0P_TIM0_MODE23->ICLR_f.CB0E = 0;
    M0P_TIM0_MODE23->ICLR_f.CB0F = 0;
    M0P_TIM0_MODE23->ICLR_f.TIF = 0;
    M0P_TIM0_MODE23->ICLR_f.UIF = 0;
        
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer3 中断使能(模式0)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_Mode0_EnableIrq(void)
{
    en_result_t enResult = Ok;
    
    M0P_TIM0_MODE0->M0CR_f.UIE = TRUE;

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer3 中断禁止(模式0)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_Mode0_DisableIrq(void)
{
    en_result_t enResult = Ok;
    
    M0P_TIM0_MODE0->M0CR_f.UIE = FALSE;

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer3 中断使能(模式1)
 **
 **
 ** \param [in]  enTim0Irq           中断类型
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_Mode1_EnableIrq (en_tim0_irq_type_t enTim0Irq)
{
    en_result_t enResult = Ok;
    
        
    switch (enTim0Irq)
    {
        case Tim0UevIrq:
            M0P_TIM0_MODE1->M1CR_f.UIE = TRUE;
            break;
        case Tim0CA0Irq:
            M0P_TIM0_MODE1->CR0_f.CIEA = TRUE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer3 中断禁止(模式1)
 **
 **
 ** \param [in]  enTim0Irq           中断类型
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_Mode1_DisableIrq (en_tim0_irq_type_t enTim0Irq)
{
    en_result_t enResult = Ok;
    
        
    switch (enTim0Irq)
    {
        case Tim0UevIrq:
            M0P_TIM0_MODE1->M1CR_f.UIE = FALSE;
            break;
        case Tim0CA0Irq:
            M0P_TIM0_MODE1->CR0_f.CIEA = FALSE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer3 中断使能(模式23)
 **
 **
 ** \param [in]  enTim0Irq           中断类型
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_Mode23_EnableIrq (en_tim0_irq_type_t enTim0Irq)
{
    en_result_t enResult = Ok;
    
        
    switch (enTim0Irq)
    {
        case Tim0UevIrq:
            M0P_TIM0_MODE23->M23CR_f.UIE = TRUE;
            break;
        case Tim0CA0Irq:
            M0P_TIM0_MODE23->CRCH0_f.CIEA = TRUE;
            break;
        case Tim0CB0Irq:
            M0P_TIM0_MODE23->CRCH0_f.CIEB = TRUE;
            break;
//        case Tim0CA1Irq:
//            M0P_TIM0_MODE23->CRCH1_f.CIEA = TRUE;
//            break;
//        case Tim0CB1Irq:
//            M0P_TIM0_MODE23->CRCH1_f.CIEB = TRUE;
//            break;
//        case Tim0CA2Irq:
//            M0P_TIM0_MODE23->CRCH2_f.CIEA = TRUE;
//            break;
//        case Tim0CB2Irq:
//            M0P_TIM0_MODE23->CRCH2_f.CIEB = TRUE;
//            break;
        case Tim0BkIrq:
            M0P_TIM0_MODE23->M23CR_f.BIE = TRUE;
            break;
        case Tim0TrigIrq:
            M0P_TIM0_MODE23->M23CR_f.TIE = TRUE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer3 中断禁止(模式23)
 **
 **
 ** \param [in]  enTim0Irq           中断类型
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_Mode23_DisableIrq (en_tim0_irq_type_t enTim0Irq)
{
    en_result_t enResult = Ok;
    
        
    switch (enTim0Irq)
    {
        case Tim0UevIrq:
            M0P_TIM0_MODE23->M23CR_f.UIE = FALSE;
            break;
        case Tim0CA0Irq:
            M0P_TIM0_MODE23->CRCH0_f.CIEA = FALSE;
            break;
        case Tim0CB0Irq:
            M0P_TIM0_MODE23->CRCH0_f.CIEB = FALSE;
            break;
//        case Tim0CA1Irq:
//            M0P_TIM0_MODE23->CRCH1_f.CIEA = FALSE;
//            break;
//        case Tim0CB1Irq:
//            M0P_TIM0_MODE23->CRCH1_f.CIEB = FALSE;
//            break;
//        case Tim0CA2Irq:
//            M0P_TIM0_MODE23->CRCH2_f.CIEA = FALSE;
//            break;
//        case Tim0CB2Irq:
//            M0P_TIM0_MODE23->CRCH2_f.CIEB = FALSE;
//            break;
        case Tim0BkIrq:
            M0P_TIM0_MODE23->M23CR_f.BIE = FALSE;
            break;
        case Tim0TrigIrq:
            M0P_TIM0_MODE23->M23CR_f.TIE = FALSE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer3 中断服务函数
 **
 **
 ** \param [in]  u8Param           Timer0通道选择(0 - TIM0)
 ** 
 ** \retval NULL                                     
 *****************************************************************************/
void Tim0_IRQHandler(uint8_t u8Param)
{
    switch (u8Param)
    {
        case 0:
            if(NULL != pfnTim0Callback)
            {
                pfnTim0Callback();
            }
            break;
        default:
            ;
            break;       
    }
}



/**
 *****************************************************************************
 ** \brief Base Timer3 初始化配置(模式0)
 **
 **
 ** \param [in]  pstcConfig       初始化配置结构体指针
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_Mode0_Init(stc_tim0_mode0_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
  
    M0P_TIM0_MODE0->M0CR_f.MODE   = pstcConfig->enWorkMode;
    M0P_TIM0_MODE0->M0CR_f.GATEP  = pstcConfig->enGateP;
    M0P_TIM0_MODE0->M0CR_f.GATE   = pstcConfig->bEnGate;
    M0P_TIM0_MODE0->M0CR_f.PRS    = pstcConfig->enPRS;
    M0P_TIM0_MODE0->M0CR_f.TOGEN  = pstcConfig->bEnTog;
    M0P_TIM0_MODE0->M0CR_f.CT     = pstcConfig->enCT;
    M0P_TIM0_MODE0->M0CR_f.MD     = pstcConfig->enCntMode; 
                
    pfnTim0Callback      = pstcConfig->pfnTim0Cb;
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer3 启动运行(模式0)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M0_Run(void)
{
    en_result_t enResult = Ok;
    
    M0P_TIM0_MODE0->M0CR_f.CTEN = TRUE;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 停止运行(模式0)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M0_Stop(void)
{
    en_result_t enResult = Ok;
    
    M0P_TIM0_MODE0->M0CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
 *****************************************************************************
 ** \brief Base Timer3 翻转输出使能/禁止设定(模式0)
 **
 **
 ** \param [in]  bEnOutput          翻转输出设定 TRUE:使能, FALSE:禁止
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M0_EnTOG_Output(boolean_t bEnOutput)
{
    en_result_t enResult = Ok;
    
    M0P_TIM0_MODE0->DTR_f.MOE = bEnOutput;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 16位计数器初值设置(模式0)
 **
 **
 ** \param [in]  u16Data          CNT 16位初值
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M0_Cnt16Set(uint16_t u16Data)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE0->CNT_f.CNT = u16Data;
 
    return enResult; 
}

/**
 *****************************************************************************
 ** \brief Base Timer3 16位计数值获取(模式0)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval 16bits计数值                                      
 *****************************************************************************/
uint16_t Tim0_M0_Cnt16Get(void)
{
    uint16_t    u16CntData = 0;
      
    u16CntData = M0P_TIM0_MODE0->CNT_f.CNT;
    
    return u16CntData; 
}

/**
 *****************************************************************************
 ** \brief Base Timer3 重载值设置(模式0)
 **
 **
 ** \param [in]  u16Data          16bits重载值
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M0_ARRSet(uint16_t u16Data)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE0->ARR_f.ARR = u16Data;

    return enResult; 
}

/**
 *****************************************************************************
 ** \brief Base Timer3 32位计数器初值设置(模式0)
 **
 **
 ** \param [in]  u32Data          32位初值
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M0_Cnt32Set(uint32_t u32Data)
{
    en_result_t enResult = Ok;
    
    M0P_TIM0_MODE0->CNT32_f.CNT32 = u32Data;
    
    return enResult; 
}

/**
 *****************************************************************************
 ** \brief Base Timer3 32位计数值获取(模式0)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval 32bits计数值                                      
 *****************************************************************************/
uint32_t Tim0_M0_Cnt32Get(void)
{
    uint32_t    u32CntData = 0;
    
    u32CntData = M0P_TIM0_MODE0->CNT32_f.CNT32;
    
    return u32CntData;
}

/**
 *****************************************************************************
 ** \brief Base Timer0 初始化配置(模式1)
 **
 **
 ** \param [in]  pstcConfig       初始化配置结构体指针
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_Mode1_Init(stc_tim0_mode1_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
  
//    M0P_TIM0_MODE0->M1CR_f.MODE    = pstcConfig->enWorkMode;
//    M0P_TIM0_MODE0->M1CR_f.PRS     = pstcConfig->enPRS;
//    M0P_TIM0_MODE0->M1CR_f.CT      = pstcConfig->enCT;
//    M0P_TIM0_MODE0->M1CR_f.ONESHOT = pstcConfig->enOneShot;
//                
//    pfnTim0Callback      = pstcConfig->pfnTim0Cb;
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer3 PWC 输入配置(模式1)
 **
 **
 ** \param [in]  pstcConfig       初始化配置结构体指针
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M1_Input_Config(stc_tim0_pwc_input_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
    
//    M0P_TIM0_MODE0->MSCR_f.TS    = pstcConfig->enTsSel;
//    M0P_TIM0_MODE0->MSCR_f.IA0S  = pstcConfig->enIA0Sel;
//    M0P_TIM0_MODE0->MSCR_f.IB0S  = pstcConfig->enIB0Sel;
//    M0P_TIM0_MODE0->FLTR_f.ETP   = pstcConfig->enETRPhase;
//    M0P_TIM0_MODE0->FLTR_f.FLTET = pstcConfig->enFltETR;
//    M0P_TIM0_MODE0->FLTR_f.FLTA0 = pstcConfig->enFltIA0;
//    M0P_TIM0_MODE0->FLTR_f.FLTB0 = pstcConfig->enFltIB0;
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer3 PWC测量边沿起始结束选择(模式1)
 **
 **
 ** \param [in]  enEdgeSel           pwc测量起始终止电平
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M1_PWC_Edge_Sel(en_tim0_m1cr_Edge_t enEdgeSel)
{
    en_result_t enResult = Ok;
        
//    switch (enEdgeSel)
//    {
//        case 0:                                 ///< 上升沿到上升沿(周期)
//            M0P_TIM0_MODE0->M1CR_f.EDG1ST = 0;  //上升沿
//            M0P_TIM0_MODE0->M1CR_f.EDG2ND = 0;  //上升沿
//            break;
//        case 1:                                 ///< 下降沿到上升沿(低电平)
//            M0P_TIM0_MODE0->M1CR_f.EDG1ST = 1;  //下降沿
//            M0P_TIM0_MODE0->M1CR_f.EDG2ND = 0;  //上升沿
//            break;
//        case 2:                                 ///< 上升沿到下降沿(高电平)
//            M0P_TIM0_MODE0->M1CR_f.EDG1ST = 0;  //上升沿
//            M0P_TIM0_MODE0->M1CR_f.EDG2ND = 1;  //下降沿
//            break;
//        case 3:                                 ///< 下降沿到下降沿(周期)
//            M0P_TIM0_MODE0->M1CR_f.EDG1ST = 1;  //下降沿
//            M0P_TIM0_MODE0->M1CR_f.EDG2ND = 1;  //下降沿
//            break;
//        default:
//            ;
//            break;       
//    }
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 启动运行(模式1)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M1_Run(void)
{
    en_result_t enResult = Ok;
        
//    M0P_TIM0_MODE0->M1CR_f.CTEN = TRUE;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 停止运行(模式1)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M1_Stop(void)
{
    en_result_t enResult = Ok;
        
//    M0P_TIM0_MODE0->M1CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
 *****************************************************************************
 ** \brief Base Timer3 16位计数器初值设置(模式1)
 **
 **
 ** \param [in]  u16Data          16位初值
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M1_Cnt16Set(uint16_t u16Data)
{
    en_result_t enResult = Ok;
  
    M0P_TIM0_MODE0->CNT_f.CNT = u16Data;
    
    return enResult; 
}

/**
 *****************************************************************************
 ** \brief Base Timer3 16位计数值获取(模式1)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval 16bits计数值                                      
 *****************************************************************************/
uint16_t Tim0_M1_Cnt16Get(void)
{
    uint16_t    u16CntData = 0;
  
    u16CntData = M0P_TIM0_MODE0->CNT_f.CNT;
        
    return u16CntData; 
}

/**
 *****************************************************************************
 ** \brief Base Timer3 脉冲宽度测量结果数值获取(模式1)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval 16bits脉冲宽度测量结果                                      
 *****************************************************************************/
uint16_t Tim0_M1_PWC_CapValueGet(void)
{
    uint16_t    u16CapData = 0;

//    u16CapData = M0P_TIM0_MODE0->CCR0A_f.CCR0A;
        
    return u16CapData; 
}

/**
 *****************************************************************************
 ** \brief Base Timer3 初始化配置(模式23)
 **
 **
 ** \param [in]  pstcConfig       初始化配置结构体指针
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_Mode23_Init(stc_tim0_mode23_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
  
    M0P_TIM0_MODE23->M23CR_f.MODE    = pstcConfig->enWorkMode;
    
    M0P_TIM0_MODE23->M23CR_f.PRS     = pstcConfig->enPRS;
    M0P_TIM0_MODE23->M23CR_f.CT      = pstcConfig->enCT;
    M0P_TIM0_MODE23->M23CR_f.COMP    = pstcConfig->enPWMTypeSel;
    M0P_TIM0_MODE23->M23CR_f.PWM2S   = pstcConfig->enPWM2sSel;
    M0P_TIM0_MODE23->M23CR_f.ONESHOT = pstcConfig->bOneShot;
    M0P_TIM0_MODE23->M23CR_f.URS     = pstcConfig->bURSSel;
    M0P_TIM0_MODE23->M23CR_f.DIR     = pstcConfig->enCntDir;
                
    pfnTim0Callback      = pstcConfig->pfnTim0Cb;
        
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer3 PWM输出使能(模式23)
 **
 **
 ** \param [in]  bEnOutput          PWM输出使能/禁止设定
 ** \param [in]  bEnAutoOutput      PWM自动输出使能/禁止设定
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_EnPWM_Output(boolean_t bEnOutput, boolean_t bEnAutoOutput)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE23->DTR_f.MOE = bEnOutput;
    M0P_TIM0_MODE23->DTR_f.AOE = bEnAutoOutput;
    
    return enResult;
}


/**
 *****************************************************************************
 ** \brief Base Timer3 启动运行(模式23)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_Run(void)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE23->M23CR_f.CTEN = TRUE;
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer3 停止运行(模式23)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_Stop(void)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE23->M23CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
 *****************************************************************************
 ** \brief Base Timer3 重载值设置(模式23)
 **
 **
 ** \param [in]  u16Data          16bits重载值
 ** \param [in]  bArrBufEn        ARR重载缓存使能TRUE/禁止FALSE
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_ARRSet(uint16_t u16Data, boolean_t bArrBufEn)
{
    en_result_t enResult = Ok;
        
     M0P_TIM0_MODE23->ARR_f.ARR       = u16Data;
     M0P_TIM0_MODE23->M23CR_f.BUFPEN  = bArrBufEn;

    return enResult; 
}

/**
 *****************************************************************************
 ** \brief Base Timer3 16位计数器初值设置(模式23)
 **
 **
 ** \param [in]  u16Data          16位初值
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_Cnt16Set(uint16_t u16Data)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE23->CNT_f.CNT = u16Data;

    return enResult; 
}

/**
 *****************************************************************************
 ** \brief Base Timer3 16位计数值获取(模式23)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval 16bits计数值                                      
 *****************************************************************************/
uint16_t Tim0_M23_Cnt16Get(void)
{
    uint16_t    u16CntData = 0;
        
    u16CntData = M0P_TIM0_MODE23->CNT_f.CNT;
    
    return u16CntData; 
}

/**
 *****************************************************************************
 ** \brief Base Timer3 比较捕获寄存器CCRxA/CCRxB设置(模式23)
 **
 **
 ** \param [in]  enCCRSel           CCRxA/CCRxB设定
 ** \param [in]  u16Data            CCRxA/CCRxB 16位初始值
 ** 
 ** \retval Ok or Error                                     
 *****************************************************************************/
en_result_t Tim0_M23_CCR_Set(en_tim0_m23_ccrx_t enCCRSel, uint16_t u16Data)
{
    en_result_t enResult = Ok;
        
    if(Tim0CCR0A == enCCRSel)
    {
        M0P_TIM0_MODE23->CCR0A_f.CCR0A = u16Data;
    }
    else if(Tim0CCR0B == enCCRSel)
    {
        M0P_TIM0_MODE23->CCR0B_f.CCR0B = u16Data;
    }
//    else if(Tim0CCR1A == enCCRSel)
//    {
//        M0P_TIM0_MODE23->CCR1A_f.CCR1A = u16Data;
//    }
//    else if(Tim0CCR1B == enCCRSel)
//    {
//        M0P_TIM0_MODE23->CCR1B_f.CCR1B = u16Data;
//    }
//    else if(Tim0CCR2A == enCCRSel)
//    {
//        M0P_TIM0_MODE23->CCR2A_f.CCR2A = u16Data;
//    }
//    else if(Tim0CCR2B == enCCRSel)
//    {
//        M0P_TIM0_MODE23->CCR2B_f.CCR2B = u16Data;
//    }
    else
    {
        enResult = Error;
    }
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer3 比较捕获寄存器CCRxA/CCRxB读取(模式23)
 **
 **
 ** \param [in]  enCCRSel           CCRxA/CCRxB设定
 ** 
 ** \retval 16bitsCCRxA/CCRxB捕获值                                     
 *****************************************************************************/
uint16_t Tim0_M23_CCR_Get(en_tim0_m23_ccrx_t enCCRSel)
{
    uint16_t    u16Data = 0;
    
    if(Tim0CCR0A == enCCRSel)
    {
        u16Data = M0P_TIM0_MODE23->CCR0A_f.CCR0A;
    }
    else if(Tim0CCR0B == enCCRSel)
    {
        u16Data = M0P_TIM0_MODE23->CCR0B_f.CCR0B;
    }
//    else if(Tim0CCR1A == enCCRSel)
//    {
//        u16Data = M0P_TIM0_MODE23->CCR1A_f.CCR1A;
//    }
//    else if(Tim0CCR1B == enCCRSel)
//    {
//        u16Data = M0P_TIM0_MODE23->CCR1B_f.CCR1B;
//    }
//    else if(Tim0CCR2A == enCCRSel)
//    {
//        u16Data = M0P_TIM0_MODE23->CCR2A_f.CCR2A;
//    }
//    else if(Tim0CCR2B == enCCRSel)
//    {
//        u16Data = M0P_TIM0_MODE23->CCR2B_f.CCR2B;
//    }
    else
    {
        u16Data = 0;
    }
    
    return u16Data; 
}

/**
 *****************************************************************************
 ** \brief Base Timer3 PWM互补输出模式下，GATE功能选择(模式23)
 **
 **
 ** \param [in]  pstcConfig       初始化配置结构体指针
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_GateFuncSel(stc_tim0_m23_gate_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE23->M23CR_f.CSG = pstcConfig->enGateFuncSel;
    M0P_TIM0_MODE23->M23CR_f.CRG = pstcConfig->bGateRiseCap;
    M0P_TIM0_MODE23->M23CR_f.CFG = pstcConfig->bGateFallCap;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 主从模式配置(模式23)
 **
 **
 ** \param [in]  pstcConfig       初始化配置结构体指针
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_MasterSlave_Set(stc_tim0_m23_master_slave_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
    
    M0P_TIM0_MODE23->MSCR_f.MSM = pstcConfig->enMasterSlaveSel;
    M0P_TIM0_MODE23->MSCR_f.MMS = pstcConfig->enMasterSrc;
    M0P_TIM0_MODE23->MSCR_f.SMS = pstcConfig->enSlaveModeSel;
    M0P_TIM0_MODE23->MSCR_f.TS  = pstcConfig->enTsSel;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 CHxA/CHxB比较通道控制(模式23)
 **
 **
 ** \param [in]  pstcConfig       初始化配置结构体指针
 ** \param [in]  enTim0Chx        Timer3通道(Tim0CH0, Tim0CH1, Tim0CH2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_PortOutput_Config(en_tim0_channel_t enTim0Chx, stc_tim0_m23_compare_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
    
    switch (enTim0Chx)
    {
        case Tim0CH0:
            M0P_TIM0_MODE23->CRCH0_f.CSA         = 0;
            M0P_TIM0_MODE23->FLTR_f.OCMA0_FLTA0  = pstcConfig->enCHxACmpCtrl;
            M0P_TIM0_MODE23->FLTR_f.CCPA0        = pstcConfig->enCHxAPolarity;
            M0P_TIM0_MODE23->CRCH0_f.BUFEA       = pstcConfig->bCHxACmpBufEn;
            M0P_TIM0_MODE23->M23CR_f.CIS         = pstcConfig->enCHxACmpIntSel;
    
            M0P_TIM0_MODE23->CRCH0_f.CSB         = 0;
            M0P_TIM0_MODE23->FLTR_f.OCMB0_FLTB0  = pstcConfig->enCHxBCmpCtrl;
            M0P_TIM0_MODE23->FLTR_f.CCPB0        = pstcConfig->enCHxBPolarity;
            M0P_TIM0_MODE23->CRCH0_f.BUFEB       = pstcConfig->bCHxBCmpBufEn;
            M0P_TIM0_MODE23->CRCH0_f.CISB        = pstcConfig->enCHxBCmpIntSel;
          break;
//        case Tim0CH1:
//            M0P_TIM0_MODE23->CRCH1_f.CSA         = 0;
//            M0P_TIM0_MODE23->FLTR_f.OCMA1_FLTA1  = pstcConfig->enCHxACmpCtrl;
//            M0P_TIM0_MODE23->FLTR_f.CCPA1        = pstcConfig->enCHxAPolarity;
//            M0P_TIM0_MODE23->CRCH1_f.BUFEA       = pstcConfig->bCHxACmpBufEn;
//            M0P_TIM0_MODE23->M23CR_f.CIS         = pstcConfig->enCHxACmpIntSel;
//    
//            M0P_TIM0_MODE23->CRCH1_f.CSB         = 0;
//            M0P_TIM0_MODE23->FLTR_f.OCMB1_FLTB1  = pstcConfig->enCHxBCmpCtrl;
//            M0P_TIM0_MODE23->FLTR_f.CCPB1        = pstcConfig->enCHxBPolarity;
//            M0P_TIM0_MODE23->CRCH1_f.BUFEB       = pstcConfig->bCHxBCmpBufEn;
//            M0P_TIM0_MODE23->CRCH1_f.CISB        = pstcConfig->enCHxBCmpIntSel;
//          break;
//        case Tim0CH2:
//            M0P_TIM0_MODE23->CRCH2_f.CSA         = 0;
//            M0P_TIM0_MODE23->FLTR_f.OCMA2_FLTA2  = pstcConfig->enCHxACmpCtrl;
//            M0P_TIM0_MODE23->FLTR_f.CCPA2        = pstcConfig->enCHxAPolarity;
//            M0P_TIM0_MODE23->CRCH2_f.BUFEA       = pstcConfig->bCHxACmpBufEn;
//            M0P_TIM0_MODE23->M23CR_f.CIS         = pstcConfig->enCHxACmpIntSel;
//    
//            M0P_TIM0_MODE23->CRCH2_f.CSB         = 0;
//            M0P_TIM0_MODE23->FLTR_f.OCMB2_FLTB2  = pstcConfig->enCHxBCmpCtrl;
//            M0P_TIM0_MODE23->FLTR_f.CCPB2        = pstcConfig->enCHxBPolarity;
//            M0P_TIM0_MODE23->CRCH2_f.BUFEB       = pstcConfig->bCHxBCmpBufEn;
//            M0P_TIM0_MODE23->CRCH2_f.CISB        = pstcConfig->enCHxBCmpIntSel;
//          break;
        default:
            enResult = Error;
          break;
    }
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 CHxA/CHxB输入控制(模式23)
 **
 **
 ** \param [in]  pstcConfig       初始化配置结构体指针
 ** \param [in]  enTim0Chx        Timer3通道(Tim0CH0, Tim0CH1, Tim0CH2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_PortInput_Config(en_tim0_channel_t enTim0Chx, stc_tim0_m23_input_config_t* pstcConfig)
{
    en_result_t enResult = Ok;

    switch (enTim0Chx)
    {
        case Tim0CH0:
            M0P_TIM0_MODE23->CRCH0_f.CSA           = 1;
            M0P_TIM0_MODE23->CRCH0_f.CFA_CRA_BKSA  = pstcConfig->enCHxACapSel;
            M0P_TIM0_MODE23->FLTR_f.OCMA0_FLTA0    = pstcConfig->enCHxAInFlt;
            M0P_TIM0_MODE23->FLTR_f.CCPA0          = pstcConfig->enCHxAPolarity;
    
            M0P_TIM0_MODE23->CRCH0_f.CSB           = 1;
            M0P_TIM0_MODE23->CRCH0_f.CFB_CRB_BKSB  = pstcConfig->enCHxBCapSel;
            M0P_TIM0_MODE23->FLTR_f.OCMB0_FLTB0    = pstcConfig->enCHxBInFlt;
            M0P_TIM0_MODE23->FLTR_f.CCPB0          = pstcConfig->enCHxBPolarity;
          break;
//        case Tim0CH1:
//            M0P_TIM0_MODE23->CRCH1_f.CSA           = 1;
//            M0P_TIM0_MODE23->CRCH1_f.CFA_CRA_BKSA  = pstcConfig->enCHxACapSel;
//            M0P_TIM0_MODE23->FLTR_f.OCMA1_FLTA1    = pstcConfig->enCHxAInFlt;
//            M0P_TIM0_MODE23->FLTR_f.CCPA1          = pstcConfig->enCHxAPolarity;
//    
//            M0P_TIM0_MODE23->CRCH1_f.CSB           = 1;
//            M0P_TIM0_MODE23->CRCH1_f.CFB_CRB_BKSB  = pstcConfig->enCHxBCapSel;
//            M0P_TIM0_MODE23->FLTR_f.OCMB1_FLTB1    = pstcConfig->enCHxBInFlt;
//            M0P_TIM0_MODE23->FLTR_f.CCPB1          = pstcConfig->enCHxBPolarity;
//          break;
//        case Tim0CH2:
//            M0P_TIM0_MODE23->CRCH2_f.CSA           = 1;
//            M0P_TIM0_MODE23->CRCH2_f.CFA_CRA_BKSA  = pstcConfig->enCHxACapSel;
//            M0P_TIM0_MODE23->FLTR_f.OCMA2_FLTA2    = pstcConfig->enCHxAInFlt;
//            M0P_TIM0_MODE23->FLTR_f.CCPA2          = pstcConfig->enCHxAPolarity;
//    
//            M0P_TIM0_MODE23->CRCH2_f.CSB           = 1;
//            M0P_TIM0_MODE23->CRCH2_f.CFB_CRB_BKSB  = pstcConfig->enCHxBCapSel;
//            M0P_TIM0_MODE23->FLTR_f.OCMB2_FLTB2    = pstcConfig->enCHxBInFlt;
//            M0P_TIM0_MODE23->FLTR_f.CCPB2          = pstcConfig->enCHxBPolarity;
//          break;
        default:
            enResult = Error;
          break;
    }
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 ERT输入控制(模式23)
 **
 **
 ** \param [in]  pstcConfig       初始化配置结构体指针
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_ETRInput_Config(stc_tim0_m23_etr_input_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE23->FLTR_f.ETP    = pstcConfig->enETRPolarity;
    M0P_TIM0_MODE23->FLTR_f.FLTET  = pstcConfig->enETRFlt;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 刹车BK输入控制(模式23)
 **
 **
 ** \param [in]  pstcConfig       初始化配置结构体指针
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_BrakeInput_Config(stc_tim0_m23_bk_input_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE23->DTR_f.BKE             = pstcConfig->bEnBrake;
    M0P_TIM0_MODE23->DTR_f.VC0E            = pstcConfig->bEnVC0Brake;
    M0P_TIM0_MODE23->DTR_f.VC1E            = pstcConfig->bEnVC1Brake;
    M0P_TIM0_MODE23->DTR_f.SAFEEN          = pstcConfig->bEnSafetyBk;
    M0P_TIM0_MODE23->DTR_f.BKSEL           = pstcConfig->bEnBKSync;
    M0P_TIM0_MODE23->CRCH0_f.CFA_CRA_BKSA  = pstcConfig->enBkCH0AStat;
    M0P_TIM0_MODE23->CRCH0_f.CFB_CRB_BKSB  = pstcConfig->enBkCH0BStat;
//    M0P_TIM0_MODE23->CRCH1_f.CFA_CRA_BKSA  = pstcConfig->enBkCH1AStat;
//    M0P_TIM0_MODE23->CRCH1_f.CFB_CRB_BKSB  = pstcConfig->enBkCH1BStat;
//    M0P_TIM0_MODE23->CRCH2_f.CFA_CRA_BKSA  = pstcConfig->enBkCH2AStat;
//    M0P_TIM0_MODE23->CRCH2_f.CFB_CRB_BKSB  = pstcConfig->enBkCH2BStat;
    M0P_TIM0_MODE23->FLTR_f.BKP            = pstcConfig->enBrakePolarity;
    M0P_TIM0_MODE23->FLTR_f.FLTBK          = pstcConfig->enBrakeFlt;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 触发ADC控制(模式23)
 **
 **
 ** \param [in]  pstcConfig       初始化配置结构体指针
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_TrigADC_Config(stc_tim0_m23_adc_trig_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE23->ADTR_f.ADTE   = pstcConfig->bEnTrigADC;
    M0P_TIM0_MODE23->ADTR_f.UEVE   = pstcConfig->bEnUevTrigADC;
    M0P_TIM0_MODE23->ADTR_f.CMA0E  = pstcConfig->bEnCH0ACmpTrigADC;
    M0P_TIM0_MODE23->ADTR_f.CMB0E  = pstcConfig->bEnCH0BCmpTrigADC;
//    M0P_TIM0_MODE23->ADTR_f.CMA1E  = pstcConfig->bEnCH1ACmpTrigADC;
//    M0P_TIM0_MODE23->ADTR_f.CMB1E  = pstcConfig->bEnCH1BCmpTrigADC;
//    M0P_TIM0_MODE23->ADTR_f.CMA2E  = pstcConfig->bEnCH2ACmpTrigADC;
//    M0P_TIM0_MODE23->ADTR_f.CMB2E  = pstcConfig->bEnCH2BCmpTrigADC;
    return enResult;    
}

/**
 *****************************************************************************
** \brief Base Timer3 死区功能(模式23)
 **
 **
 ** \param [in]  pstcConfig       初始化配置结构体指针
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_DT_Config(stc_tim0_m23_dt_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE23->DTR_f.DTEN = pstcConfig->bEnDeadTime;
    M0P_TIM0_MODE23->DTR_f.DTR  = pstcConfig->u8DeadTimeValue;
    
    return enResult;    
}

/**
 *****************************************************************************
** \brief Base Timer3 重复周期设置(模式23)
 **
 **
 ** \param [in]  u8ValidPeriod       重复周期值
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_SetValidPeriod(uint8_t u8ValidPeriod)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE23->RCR_f.RCR = u8ValidPeriod;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 OCREF清除功能(模式23)
 **
 **
 ** \param [in]  pstcConfig       初始化配置结构体指针
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_OCRefClr(stc_tim0_m23_OCREF_Clr_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE23->M23CR_f.OCCS = pstcConfig->enOCRefClrSrcSel;
    M0P_TIM0_MODE23->M23CR_f.OCCE = pstcConfig->bVCClrEn;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 使能DMA传输(模式23)
 **
 **
 ** \param [in]  pstcConfig       初始化配置结构体指针
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_EnDMA(stc_tim0_m23_trig_dma_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE23->M23CR_f.UDE  = pstcConfig->bUevTrigDMA;
    M0P_TIM0_MODE23->M23CR_f.TDE  = pstcConfig->bTITrigDMA;
    M0P_TIM0_MODE23->CRCH0_f.CDEA = pstcConfig->bCmpA0TrigDMA;
    M0P_TIM0_MODE23->CRCH0_f.CDEB = pstcConfig->bCmpB0TrigDMA;
//    M0P_TIM0_MODE23->CRCH1_f.CDEA = pstcConfig->bCmpA1TrigDMA;
//    M0P_TIM0_MODE23->CRCH1_f.CDEB = pstcConfig->bCmpB1TrigDMA;
//    M0P_TIM0_MODE23->CRCH2_f.CDEA = pstcConfig->bCmpA2TrigDMA;
//    M0P_TIM0_MODE23->CRCH2_f.CDEB = pstcConfig->bCmpB2TrigDMA;
    M0P_TIM0_MODE23->MSCR_f.CCDS  = pstcConfig->enCmpUevTrigDMA;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 捕获比较A软件触发(模式23)
 **
 **
 ** \param [in]  enTim0Chx           Timer3通道(Tim0CH0, Tim0CH1, Tim0CH2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_EnSwTrigCapCmpA(en_tim0_channel_t enTim0Chx)
{
    en_result_t enResult = Ok;
    if(Tim0CH0 == enTim0Chx)
    {
        M0P_TIM0_MODE23->CRCH0_f.CCGA = TRUE;
    }
//    else if(Tim0CH1 == enTim0Chx)
//    {
//        M0P_TIM0_MODE23->CRCH1_f.CCGA = TRUE;
//    }
//    else if(Tim0CH2 == enTim0Chx)
//    {
//        M0P_TIM0_MODE23->CRCH2_f.CCGA = TRUE;
//    }
    else
    {
        enResult = Error;
    }
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 捕获比较B软件触发(模式23)
 **
 **
 ** \param [in]  enTim0Chx           Timer3通道(Tim0CH0, Tim0CH1, Tim0CH2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_EnSwTrigCapCmpB(en_tim0_channel_t enTim0Chx)
{
    en_result_t enResult = Ok;
    if(Tim0CH0 == enTim0Chx)
    {
        M0P_TIM0_MODE23->CRCH0_f.CCGB = TRUE;
    }
//    else if(Tim0CH1 == enTim0Chx)
//    {
//        M0P_TIM0_MODE23->CRCH1_f.CCGB = TRUE;
//    }
//    else if(Tim0CH2 == enTim0Chx)
//    {
//        M0P_TIM0_MODE23->CRCH2_f.CCGB = TRUE;
//    }
    else
    {
        enResult = Error;
    }
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 软件更新使能(模式23)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_EnSwUev(void)
{
    en_result_t enResult = Ok;
    
    M0P_TIM0_MODE23->M23CR_f.UG = TRUE;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 软件触发使能(模式23)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_EnSwTrig(void)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE23->M23CR_f.TG = TRUE;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer3 软件刹车使能(模式23)
 **
 **
 ** \param [in]  none
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Tim0_M23_EnSwBk(void)
{
    en_result_t enResult = Ok;
        
    M0P_TIM0_MODE23->M23CR_f.BG = TRUE;
    
    return enResult;    
}

//@} // Tim0Group

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
