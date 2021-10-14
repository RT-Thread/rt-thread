/******************************************************************************
*Copyright(C)2017, Huada Semiconductor Co.,Ltd All rights reserved.
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

/** \file pca.c
 **
 ** Common API of PCA.
 ** @link pcaGroup Some description @endlink
 **
 **   - 2018-04-16 Husj First version
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "pca.h"
/**
 *******************************************************************************
 ** \addtogroup PcaGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IS_VALID_MODULE(x)         (Module0 == (x) ||\
                                    Module1 == (x) ||\
                                    Module2 == (x) ||\
                                    Module3 == (x) ||\
                                    Module4 == (x))

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static func_ptr_t pfnPcaCallback = NULL;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 *****************************************************************************
 ** \brief PCA中断标志获取
 **
 **
 ** \param [in]  enModule           PCA模块选择（Module0、Module1、Module2、Module3、Module4）
 ** 
 ** \retval TRUE or FALSE                                      
 *****************************************************************************/
boolean_t Pca_GetIntFlag(en_pca_module_t enModule)
{
    boolean_t bRetVal = FALSE;
  
    ASSERT(IS_VALID_MODULE(enModule));
    
    switch (enModule)
    {
        case Module0:
            bRetVal = M0P_PCA->CCON_f.CCF0 ? TRUE : FALSE;
            break;    
        case Module1: 
            bRetVal = M0P_PCA->CCON_f.CCF1 ? TRUE : FALSE;
            break;    
        case Module2: 
            bRetVal = M0P_PCA->CCON_f.CCF2 ? TRUE : FALSE;
            break;    
        case Module3: 
            bRetVal = M0P_PCA->CCON_f.CCF3 ? TRUE : FALSE;
            break;    
        case Module4: 
            bRetVal = M0P_PCA->CCON_f.CCF4 ? TRUE : FALSE;
            break;
        default:
            bRetVal = FALSE;
            break;
    }
    
    return bRetVal;    
}

/**
 *****************************************************************************
 ** \brief PCA计数中断标志获取
 **
 **
 ** 
 ** \retval TRUE or FALSE                                      
 *****************************************************************************/
boolean_t Pca_GetCntIntFlag(void)
{
    boolean_t bRetVal = FALSE;
    
    bRetVal = M0P_PCA->CCON_f.CF ? TRUE : FALSE;
   
    return bRetVal; 
}

/**
 *****************************************************************************
 ** \brief PCA中断标志清除
 **
 **
 ** \param [in]  enModule           PCA模块选择（Module0、Module1、Module2、Module3、Module4）
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Pca_ClearIntFlag(en_pca_module_t enModule)
{
    en_result_t enResult = Error;
  
    ASSERT(IS_VALID_MODULE(enModule));
    
    switch (enModule)
    {
        case Module0:
            M0P_PCA->ICLR_f.CCF0 = FALSE;
            enResult = Ok;
            break;             
        case Module1:          
            M0P_PCA->ICLR_f.CCF1 = FALSE;
            enResult = Ok;
            break;             
        case Module2:          
            M0P_PCA->ICLR_f.CCF2 = FALSE;
            enResult = Ok;
            break;             
        case Module3:          
            M0P_PCA->ICLR_f.CCF3 = FALSE;
            enResult = Ok;
            break;             
        case Module4:          
            M0P_PCA->ICLR_f.CCF4 = FALSE;
            enResult = Ok;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;  
}

/**
 *****************************************************************************
 ** \brief PCA计数中断标志清除
 **
 **
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Pca_ClearCntIntFlag(void)
{
    en_result_t enResult = Error;

    M0P_PCA->ICLR_f.CF = FALSE;
    enResult = Ok;
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief PCA中断服务程序
 **
 **
 ** \param [in]  u8Param           == 0
 **                                       
 *****************************************************************************/
void Pca_IRQHandler(uint8_t u8Param)
{
    if(NULL != pfnPcaCallback)
    {
        pfnPcaCallback();
    }
}

/**
 *****************************************************************************
 ** \brief PCA中断使能
 **
 **
 ** \param [in]  enModule           PCA模块选择（Module0、Module1、Module2、Module3、Module4）
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Pca_EnableIrq(en_pca_module_t enModule)
{
    en_result_t enResult = Error;
  
    ASSERT(IS_VALID_MODULE(enModule));
    
    switch (enModule)
    {
        case Module0:
            M0P_PCA->CCAPM0_f.CCIE = TRUE;
            enResult = Ok;
            break;             
        case Module1:          
            M0P_PCA->CCAPM1_f.CCIE = TRUE;
            enResult = Ok;
            break;             
        case Module2:          
            M0P_PCA->CCAPM2_f.CCIE = TRUE;
            enResult = Ok;
            break;             
        case Module3:          
            M0P_PCA->CCAPM3_f.CCIE = TRUE;
            enResult = Ok;
            break;             
        case Module4:          
            M0P_PCA->CCAPM4_f.CCIE = TRUE;
            enResult = Ok;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;  
}

/**
 *****************************************************************************
 ** \brief PCA计数中断使能
 **
 **
 ** 
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Pca_EnableCntIrq (void)
{
    en_result_t enResult = Error;

    M0P_PCA->CMOD_f.CFIE = TRUE;
    enResult = Ok;
    
    return enResult; 
}

/**
 *****************************************************************************
 ** \brief PCA中断禁止
 **
 **
 ** \param [in]  enModule           PCA模块选择（Module0、Module1、Module2、Module3、Module4）
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Pca_DisableIrq(en_pca_module_t enModule)
{
    en_result_t enResult = Error;
  
    ASSERT(IS_VALID_MODULE(enModule));
    
    switch (enModule)
    {
        case Module0:
            M0P_PCA->CCAPM0_f.CCIE = FALSE;
            enResult = Ok;
            break;             
        case Module1:          
            M0P_PCA->CCAPM1_f.CCIE = FALSE;
            enResult = Ok;
            break;             
        case Module2:          
            M0P_PCA->CCAPM2_f.CCIE = FALSE;
            enResult = Ok;
            break;             
        case Module3:          
            M0P_PCA->CCAPM3_f.CCIE = FALSE;
            enResult = Ok;
            break;             
        case Module4:          
            M0P_PCA->CCAPM4_f.CCIE = FALSE;
            enResult = Ok;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;  
}

/**
 *****************************************************************************
 ** \brief PCA计数中断禁止
 **
 **
 ** 
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Pca_DisableCntIrq(void)
{
    en_result_t enResult = Error;

    M0P_PCA->CMOD_f.CFIE = FALSE;
    enResult = Ok;
    
    return enResult;
}


/**
 *****************************************************************************
 ** \brief PCA初始化配置
 **
 **
 ** \param [in]  pstcConfig           PCA模块配置结构体指针
 **  
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Pca_Init(stc_pca_config_t* pstcConfig)
{
    en_result_t enResult = Error;

    M0P_PCA->CMOD_f.CIDL = pstcConfig->enCIDL;
    M0P_PCA->CMOD_f.WDTE = pstcConfig->enWDTE;
    M0P_PCA->CMOD_f.CPS  = pstcConfig->enCPS;
    
    pfnPcaCallback       = pstcConfig->pfnPcaCb;
    
    enResult = Ok;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief PCA模式配置
 **
 **
 ** \param [in]  enModule            PCA模块选择（Module0、Module1、Module2、Module3、Module4）
 ** \param [in]  pstcCapMod          PCA模式配置结构体指针
 **  
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Pca_CapModConfig(en_pca_module_t enModule, stc_pca_capmodconfig_t* pstcCapMod)
{
    en_result_t enResult = Error;
  
    ASSERT(IS_VALID_MODULE(enModule));
    
    switch (enModule)
    {
        case Module0:
            {
                M0P_PCA->CCAPM0_f.ECOM = pstcCapMod->enECOM;
                M0P_PCA->CCAPM0_f.CAPP = pstcCapMod->enCAPP;
                M0P_PCA->CCAPM0_f.CAPN = pstcCapMod->enCAPN;
                M0P_PCA->CCAPM0_f.MAT  = pstcCapMod->enMAT;
                M0P_PCA->CCAPM0_f.TOG  = pstcCapMod->enTOG;
                M0P_PCA->CCAPM0_f.PWM  = pstcCapMod->en8bitPWM;
                enResult = Ok;
            }
            break;             
        case Module1:          
            {
                M0P_PCA->CCAPM1_f.ECOM = pstcCapMod->enECOM;
                M0P_PCA->CCAPM1_f.CAPP = pstcCapMod->enCAPP;
                M0P_PCA->CCAPM1_f.CAPN = pstcCapMod->enCAPN;
                M0P_PCA->CCAPM1_f.MAT  = pstcCapMod->enMAT;
                M0P_PCA->CCAPM1_f.TOG  = pstcCapMod->enTOG;
                M0P_PCA->CCAPM1_f.PWM  = pstcCapMod->en8bitPWM;                
                enResult = Ok;
            }
            break;             
        case Module2:          
            {
                M0P_PCA->CCAPM2_f.ECOM = pstcCapMod->enECOM;
                M0P_PCA->CCAPM2_f.CAPP = pstcCapMod->enCAPP;
                M0P_PCA->CCAPM2_f.CAPN = pstcCapMod->enCAPN;
                M0P_PCA->CCAPM2_f.MAT  = pstcCapMod->enMAT;
                M0P_PCA->CCAPM2_f.TOG  = pstcCapMod->enTOG;
                M0P_PCA->CCAPM2_f.PWM  = pstcCapMod->en8bitPWM;                
                enResult = Ok;
            }
            break;             
        case Module3:          
            {
                M0P_PCA->CCAPM3_f.ECOM = pstcCapMod->enECOM;
                M0P_PCA->CCAPM3_f.CAPP = pstcCapMod->enCAPP;
                M0P_PCA->CCAPM3_f.CAPN = pstcCapMod->enCAPN;
                M0P_PCA->CCAPM3_f.MAT  = pstcCapMod->enMAT;
                M0P_PCA->CCAPM3_f.TOG  = pstcCapMod->enTOG;
                M0P_PCA->CCAPM3_f.PWM  = pstcCapMod->en8bitPWM;                
                enResult = Ok;
            }
            break;             
        case Module4:          
            {
                M0P_PCA->CCAPM4_f.ECOM = pstcCapMod->enECOM;
                M0P_PCA->CCAPM4_f.CAPP = pstcCapMod->enCAPP;
                M0P_PCA->CCAPM4_f.CAPN = pstcCapMod->enCAPN;
                M0P_PCA->CCAPM4_f.MAT  = pstcCapMod->enMAT;
                M0P_PCA->CCAPM4_f.TOG  = pstcCapMod->enTOG;
                M0P_PCA->CCAPM4_f.PWM  = pstcCapMod->en8bitPWM;                
                enResult = Ok;
            }
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult; 
}

/**
 *****************************************************************************
 ** \brief PCA启动运行
 **
 **
 ** 
 **  
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Pca_Run(void)
{
    en_result_t enResult = Error;

    M0P_PCA->CCON_f.CR = TRUE;
    enResult = Ok;
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief PCA停止运行
 **
 **
 ** 
 **  
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Pca_Stop(void)
{
    en_result_t enResult = Error;

    M0P_PCA->CCON_f.CR = FALSE;
    enResult = Ok;
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief PCA16位比较数据设置
 **
 **
 ** \param [in]  enModule            PCA模块选择（Module0、Module1、Module2、Module3、Module4）
 ** \param [in]  u16Data             PCA捕获数据
 **  
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Pca_CmpData16Set(en_pca_module_t enModule, uint16_t u16Data)
{
    en_result_t enResult = Error;
  
    ASSERT(IS_VALID_MODULE(enModule));
    
    switch (enModule)
    {
        case Module0:
            M0P_PCA->CCAP0_f.CCAP0 = u16Data;
            enResult = Ok;
            break;             
        case Module1:          
            M0P_PCA->CCAP1_f.CCAP1 = u16Data;
            enResult = Ok;
            break;             
        case Module2:          
            M0P_PCA->CCAP2_f.CCAP2 = u16Data;
            enResult = Ok;
            break;             
        case Module3:          
            M0P_PCA->CCAP3_f.CCAP3 = u16Data;
            enResult = Ok;
            break;             
        case Module4:          
            M0P_PCA->CCAP4_f.CCAP4 = u16Data;
            enResult = Ok;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;  
}


/**
 *****************************************************************************
 ** \brief PCA16位捕获数据获取
 **
 **
 ** \param [in]  enModule            PCA模块选择（Module0、Module1、Module2、Module3、Module4）
 **  
 ** \retval u16Data
 *****************************************************************************/
uint16_t Pca_CapData16Get(en_pca_module_t enModule)
{
    uint16_t u16Data = 0;
    
    ASSERT(IS_VALID_MODULE(enModule));
    
    switch (enModule)
    {
        case Module0:
            u16Data = M0P_PCA->CCAP0_f.CCAP0;
            break;             
        case Module1:          
            u16Data = M0P_PCA->CCAP1_f.CCAP1;
            break;             
        case Module2:          
            u16Data = M0P_PCA->CCAP2_f.CCAP2;
            break;             
        case Module3:          
            u16Data = M0P_PCA->CCAP3_f.CCAP3;
            break;             
        case Module4:          
            u16Data = M0P_PCA->CCAP4_f.CCAP4;
            break;
        default:
            u16Data = 0;
            break;
    }
    
    return u16Data;  
}

/**
 *****************************************************************************
 ** \brief PCA高8位比较数据设置
 **
 **
 ** \param [in]  enModule            PCA模块选择（Module0、Module1、Module2、Module3、Module4）
 ** \param [in]  u8Data             PCA高8位捕获数据
 **  
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Pca_CmpDataHSet(en_pca_module_t enModule, uint8_t u8Data)
{
    en_result_t enResult = Error;
  
    ASSERT(IS_VALID_MODULE(enModule));
    
    switch (enModule)
    {
        case Module0:
            M0P_PCA->CCAP0H_f.CCAP0 = u8Data;
            enResult = Ok;
            break;             
        case Module1:          
            M0P_PCA->CCAP1H_f.CCAP1 = u8Data;
            enResult = Ok;
            break;             
        case Module2:          
            M0P_PCA->CCAP2H_f.CCAP2 = u8Data;
            enResult = Ok;
            break;             
        case Module3:          
            M0P_PCA->CCAP3H_f.CCAP3 = u8Data;
            enResult = Ok;
            break;             
        case Module4:          
            M0P_PCA->CCAP4H_f.CCAP4 = u8Data;
            enResult = Ok;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult; 
}

/**
 *****************************************************************************
 ** \brief PCA低8位比较数据设置
 **
 **
 ** \param [in]  enModule            PCA模块选择（Module0、Module1、Module2、Module3、Module4）
 ** \param [in]  u8Data              PCA低8位捕获数据
 **  
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Pca_CmpDataLSet(en_pca_module_t enModule, uint8_t u8Data)
{
    en_result_t enResult = Error;
  
    ASSERT(IS_VALID_MODULE(enModule));
    
    switch (enModule)
    {
        case Module0:
            M0P_PCA->CCAP0L_f.CCAP0 = u8Data;
            enResult = Ok;
            break;             
        case Module1:          
            M0P_PCA->CCAP1L_f.CCAP1 = u8Data;
            enResult = Ok;
            break;             
        case Module2:          
            M0P_PCA->CCAP2L_f.CCAP2 = u8Data;
            enResult = Ok;
            break;             
        case Module3:          
            M0P_PCA->CCAP3L_f.CCAP3 = u8Data;
            enResult = Ok;
            break;             
        case Module4:          
            M0P_PCA->CCAP4L_f.CCAP4 = u8Data;
            enResult = Ok;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult; 
}

/**
 *****************************************************************************
 ** \brief PCA计数器初值设置
 **
 **
 ** 
 ** \param [in]  u16Data              PCA计数器初值
 **  
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Pca_Cnt16Set(uint16_t u16Data)
{
    en_result_t enResult = Error;
    
    M0P_PCA->CNT_f.CNT = u16Data;
    enResult = Ok;
    
    return enResult; 
}

/**
 *****************************************************************************
 ** \brief PCA16位计数器值获取
 **
 **
 **  
 ** \retval 16位计数器值
 *****************************************************************************/
uint16_t Pca_Cnt16Get(void)
{
    uint16_t u16CntData = 0;

    u16CntData = M0P_PCA->CNT_f.CNT;
    
    return u16CntData;
}

/**
 *****************************************************************************
 ** \brief PCA周期重载值设置
 **
 **
 ** 
 ** \param [in]  u16Data              PCA周期重载值
 **  
 ** \retval Ok or Error
 *****************************************************************************/
en_result_t Pca_CARRSet(uint16_t u16Data)
{
    en_result_t enResult = Error;
    
    M0P_PCA->CARR_f.CARR = u16Data;
    enResult = Ok;
    
    return enResult; 
}

/**
 *****************************************************************************
 ** \brief PCA周期重载值获取
 **
 **
 **  
 ** \retval PCA周期重载值
 *****************************************************************************/
uint16_t Pca_CARRGet(void)
{
    uint16_t u16CntData = 0;

    u16CntData = M0P_PCA->CARR_f.CARR;
    
    return u16CntData;
}

/**
 *****************************************************************************
 ** \brief PCA增强PWM 使能
 **
 **
 ** 
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Pca_Enable16bitPWM(void)
{
    en_result_t enResult = Error;

    M0P_PCA->EPWM_f.EPWM = TRUE;
    enResult = Ok;
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief PCA增强PWM 禁止
 **
 **
 ** 
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Pca_Disable16bitPWM(void)
{
    en_result_t enResult = Error;

    M0P_PCA->EPWM_f.EPWM = FALSE;
    enResult = Ok;
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief PCA比较高速输出标志获取
 **
 **
 ** \param [in]  enModule            PCA模块选择（Module0、Module1、Module2、Module3、Module4）
 **  
 ** \retval TRUE or FALSE
 *****************************************************************************/
boolean_t Pca_GetCmpHighFlag(en_pca_module_t enModule)
{
    boolean_t bRetVal = FALSE;
  
    ASSERT(IS_VALID_MODULE(enModule));
    
    switch (enModule)
    {
        case Module0:
            bRetVal = M0P_PCA->CCAPO_f.CCAPO0 ? TRUE : FALSE;
            break;    
        case Module1: 
            bRetVal = M0P_PCA->CCAPO_f.CCAPO1 ? TRUE : FALSE;
            break;    
        case Module2: 
            bRetVal = M0P_PCA->CCAPO_f.CCAPO2 ? TRUE : FALSE;
            break;    
        case Module3: 
            bRetVal = M0P_PCA->CCAPO_f.CCAPO3 ? TRUE : FALSE;
            break;    
        case Module4: 
            bRetVal = M0P_PCA->CCAPO_f.CCAPO4 ? TRUE : FALSE;
            break;
        default:
            bRetVal = FALSE;
            break;
    }
    
    return bRetVal;  
}

//@} // PcaGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
