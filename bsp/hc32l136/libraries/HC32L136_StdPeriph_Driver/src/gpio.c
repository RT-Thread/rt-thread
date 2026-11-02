/******************************************************************************
* Copyright (C) 2018, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
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
/******************************************************************************/
/** \file Gpio.c
 **
 ** GPIO driver API.
 ** @link Driver Group Some description @endlink
 **
 **   - 2018-04-22  1.0  Lux First version
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "gpio.h"

/**
 *******************************************************************************
 ** \addtogroup GpioGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IS_VALID_PIN(port,pin)      (  )
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')         *
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 *******************************************************************************
 ** \brief GPIO 初始化
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 ** \param [in]  pstcGpioCfg     IO 配置结构体指针
 **
 ** \retval Ok         设置成功
 **         其他值     设置失败
 ******************************************************************************/
en_result_t Gpio_Init(en_gpio_port_t enPort, en_gpio_pin_t enPin, stc_gpio_config_t  *pstcGpioCfg)
{
    //配置为默认值,GPIO功能
    *((uint32_t*)(((uint32_t)(&(M0P_GPIO->PA00_SEL)) + enPort) + (((uint32_t)enPin)<<2))) = GpioAf0;
    
    //方向配置
    if(GpioDirIn == pstcGpioCfg->enDir)
    {
        setBit(((uint32_t)&M0P_GPIO->PADIR + enPort), enPin, TRUE);
    }
    else
    {
        setBit(((uint32_t)&M0P_GPIO->PADIR + enPort), enPin, FALSE);
    }
    
    //驱动能力配置
    if(GpioDrvH == pstcGpioCfg->enDrv)
    {
        setBit(((uint32_t)&M0P_GPIO->PADR + enPort), enPin, FALSE);
    }
    else
    {
        setBit(((uint32_t)&M0P_GPIO->PADR + enPort), enPin, TRUE);
    }
    
    //上拉下拉配置
    if(GpioPu == pstcGpioCfg->enPuPd)
    {
        setBit(((uint32_t)&M0P_GPIO->PAPU + enPort), enPin, TRUE);
        setBit(((uint32_t)&M0P_GPIO->PAPD + enPort), enPin, FALSE);
    }
    else if(GpioPd == pstcGpioCfg->enPuPd)
    {
        setBit(((uint32_t)&M0P_GPIO->PAPU + enPort), enPin, FALSE);
        setBit(((uint32_t)&M0P_GPIO->PAPD + enPort), enPin, TRUE);
    }
    else
    {
        setBit(((uint32_t)&M0P_GPIO->PAPU + enPort), enPin, FALSE);
        setBit(((uint32_t)&M0P_GPIO->PAPD + enPort), enPin, FALSE);
    }
    
    //开漏输出功能
    if(GpioOdDisable == pstcGpioCfg->enOD)
    {
        setBit(((uint32_t)&M0P_GPIO->PAOD + enPort), enPin, FALSE);
    }
    else
    {
        setBit(((uint32_t)&M0P_GPIO->PAOD + enPort), enPin, TRUE);
    }
    
    M0P_GPIO->CTRL2_f.AHB_SEL = pstcGpioCfg->enCtrlMode;

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO输入值获取
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 **
 ** \retval boolean_t            IO电平高低
 ******************************************************************************/
boolean_t Gpio_GetInputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    return getBit(((uint32_t)&M0P_GPIO->PAIN + enPort), enPin);
}

/**
 *******************************************************************************
 ** \brief GPIO IO Port输入数据获取
 **
 ** \param [in]  enPort          IO Port
 **
 ** \retval boolean_t            IO Port数据
 ******************************************************************************/
uint16_t    Gpio_GetInputData(en_gpio_port_t enPort)
{
    return (uint16_t)(*((uint32_t *)((uint32_t)&M0P_GPIO->PAIN + enPort))); 
}

/**
 *******************************************************************************
 ** \brief GPIO IO输出值写入
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 ** \param [out] bVal            输出值
 **
 ** \retval en_result_t          Ok      设置成功
 **                              其他值  设置失败
 ******************************************************************************/
en_result_t Gpio_WriteOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin, boolean_t bVal)
{
    setBit(((uint32_t)&M0P_GPIO->PAOUT + enPort), enPin, bVal);
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO输出值获取
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 **
 ** \retval boolean_t            IO电平高低
 ******************************************************************************/
boolean_t   Gpio_ReadOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    return getBit(((uint32_t)&M0P_GPIO->PAOUT + enPort), enPin);
}

/**
 *******************************************************************************
 ** \brief GPIO IO Port设置，可同时设置一组Port中的多个PIN
 **
 ** \param [in]  enPort          IO Port
 ** \param [in]  u16ValMsk       该Port的16个PIN掩码值,将需要设置的PIN对应的bit写1有效   
 **
 ** \retval boolean_t            IO Port数据
 ******************************************************************************/
en_result_t Gpio_SetPort(en_gpio_port_t enPort, uint16_t u16ValMsk)
{
    *((uint16_t*)(((uint32_t)&(M0P_GPIO->PABSET)) + enPort)) = u16ValMsk;
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO设置
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 **
 ** \retval en_result_t          Ok      设置成功
 **                              其他值  设置失败
 ******************************************************************************/
en_result_t Gpio_SetIO(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    setBit(((uint32_t)&M0P_GPIO->PABSET + enPort), enPin, TRUE);
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO Port清零，可同时清零一组Port中的多个PIN
 **
 ** \param [in]  enPort          IO Port
 ** \param [in]  u16ValMsk       该Port的16个PIN掩码值,将需要清零的PIN对应的bit写1有效
 **
 ** \retval boolean_t            IO Port数据
 ******************************************************************************/
en_result_t Gpio_ClrPort(en_gpio_port_t enPort, uint16_t u16ValMsk)
{
    *((uint16_t*)(((uint32_t)&(M0P_GPIO->PABCLR)) + enPort)) = u16ValMsk;
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO清零
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 **
 ** \retval en_result_t          Ok      设置成功
 **                              其他值  设置失败
 ******************************************************************************/
en_result_t Gpio_ClrIO(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    setBit(((uint32_t)&M0P_GPIO->PABCLR + enPort), enPin, TRUE);
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO Port置位/清零，可同时置位/清零一组Port中的多个PIN
 **
 ** \param [in]  enPort       IO Port
** \param [in]  u32ValMsk     高16bits表示该Port的16个PIN置位掩码值,
 **                           低16bits表示该Port的16个PIN清零掩码值,
**                            将需要设置的PIN对应的bit写1,同一个PIN的掩码同时为1,则该PIN清零。                              
 **
 ** \retval en_result_t       Ok      设置成功
 **                           其他值  设置失败
 ******************************************************************************/
en_result_t Gpio_SetClrPort(en_gpio_port_t enPort, uint32_t u32ValMsk)
{
    *((uint32_t*)(((uint32_t)&(M0P_GPIO->PABSETCLR)) + enPort)) = u32ValMsk;
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO配置为模拟功能模式
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 **
 ** \retval Ok         设置成功
 **         其他值     设置失败
 ******************************************************************************/
en_result_t Gpio_SetAnalogMode(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    setBit((uint32_t)&M0P_GPIO->PAADS + enPort, enPin, TRUE);

    return Ok;
}

/**
 *******************************************************************************
** \brief GPIO IO复用功能设置
 **
 ** \param [in]  enPort    IO Port口
 ** \param [in]  enPin     IO Pin脚
 ** \param [in]  enAf      复用功能枚举类型选择
 ** \retval Ok             设置成功
 **         其他值         设置失败
 ******************************************************************************/
en_result_t Gpio_SetAfMode(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_af_t enAf)
{
    *((uint32_t*)(((uint32_t)(&(M0P_GPIO->PA00_SEL)) + enPort) + (((uint32_t)enPin)<<2))) = enAf;
    
    return Ok;
}


static en_result_t _GpioEnableIrq(en_gpio_port_t enPort,
                           en_gpio_pin_t enPin,
                           en_gpio_irqtype_t enType,
                           boolean_t bEnable)
{
    //high level
    if (enType & GpioIrqHigh)
    {
        setBit((uint32_t)&M0P_GPIO->PAHIE + enPort, enPin, bEnable);
    }
    //low level
    if (enType & GpioIrqLow)
    {
        setBit((uint32_t)&M0P_GPIO->PALIE + enPort, enPin, bEnable);
    }
    //rising
    if (enType & GpioIrqRising)
    {
        setBit((uint32_t)&M0P_GPIO->PARIE + enPort, enPin, bEnable);
    }
    //falling
    if (enType & GpioIrqFalling)
    {
        setBit((uint32_t)&M0P_GPIO->PAFIE + enPort, enPin, bEnable);
    }

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO中断使能
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 ** \param [in]  enType          中断使能类型
 **
 ** \retval      Ok            设置成功
 ******************************************************************************/
en_result_t Gpio_EnableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType)
{
    _GpioEnableIrq(enPort, enPin, enType, TRUE);
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO中断关闭
 **
 ** \param [in]  enPort          IO Port口
 ** \param [in]  enPin           IO Pin脚
 ** \param [in]  enType          中断使能类型
 **
 ** \retval      Ok            设置成功
 ******************************************************************************/
en_result_t Gpio_DisableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType)
{
    _GpioEnableIrq(enPort, enPin, enType, FALSE);
    
    return Ok;
}


/**
 *******************************************************************************
 ** \brief GPIO 获得IO中断状态
 **
 ** \param [in]  u8Port          IO Port口
 ** \param [in]  u8Pin           IO Pin脚
 **
 ** \retval      IO中断状态开关
 ******************************************************************************/
boolean_t Gpio_GetIrqStatus(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    return getBit((uint32_t)&M0P_GPIO->PA_STAT + enPort, enPin);
}

/**
 *******************************************************************************
 ** \brief GPIO 清除IO中断状态
 **
 ** \param [in]  u8Port          IO Port口
 ** \param [in]  u8Pin           IO Pin脚
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_ClearIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    setBit((uint32_t)&M0P_GPIO->PA_ICLR + enPort, enPin, FALSE);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——中断模式配置
 **
 ** \param [in]  enIrqMode          端口中断模式（深度休眠是否响应中断）
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfIrqModeConfig(en_gpio_sf_irqmode_t enIrqMode)
{
    M0P_GPIO->CTRL0_f.IESEL = enIrqMode;
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——IR输出极性配置
 **
 ** \param [in]  enIrPolMode          IR输出极性配置枚举
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfIrPolConfig(en_gpio_sf_irpol_t enIrPolMode)
{
    M0P_GPIO->CTRL1_f.IR_POL = enIrPolMode;
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——HCLK输出配置
 **
 ** \param [in]  enGate         HCLK输出使能
 ** \param [in]  enDiv          输出分频枚举值
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfHClkOutputConfig(en_gpio_sf_hclkout_g_t enGate, en_gpio_sf_hclkout_div_t enDiv)
{
    M0P_GPIO->CTRL1_f.HCLK_EN  = enGate;
    M0P_GPIO->CTRL1_f.HCLK_SEL = enDiv;
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——PCLK输出配置
 **
 ** \param [in]  enGate         PCLK输出使能
 ** \param [in]  enDiv          输出分频枚举值
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfPClkOutputConfig(en_gpio_sf_pclkout_g_t enGate, en_gpio_sf_pclkout_div_t enDiv)
{
    M0P_GPIO->CTRL1_f.PCLK_EN  = enGate;
    M0P_GPIO->CTRL1_f.PCLK_SEL = enDiv;
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——外部时钟输入来源配置
 **
 ** \param [in]  enExtClk         外部时钟信号来源选择枚举
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfExtClkConfig(en_gpio_sf_ssn_extclk_t enExtClk)
{
    M0P_GPIO->CTRL1_f.EXT_CLK_SEL  = enExtClk;
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——SSN 通道信号来源配置
 **
 ** \param [in]  enSpi         SSN SPI通道选择枚举
 ** \param [in]  enSsn         SSN 信号来源选择枚举
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfSsnConfig(en_gpio_sf_ssnspi_t enSpi, en_gpio_sf_ssn_extclk_t enSsn)
{
    //SPI0
    if(enSpi == GpioSpi0)
    {
        M0P_GPIO->CTRL1_f.SSN0_SEL = enSsn;
    }
    //SPI1
    if(enSpi == GpioSpi1)
    {
        M0P_GPIO->CTRL2_f.SSN1_SEL = enSsn;
    }
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——Timer 门控输入配置
 **
 ** \param [in]  enTimG       Timer类型选择枚举
 ** \param [in]  enSf         Timer互联功能选择枚举
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfTimGConfig(en_gpio_sf_tim_g_t enTimG, en_gpio_sf_t enSf)
{
    M0P_GPIO->TIMGS &= (uint32_t)(~(0x07U<<enTimG));
    M0P_GPIO->TIMGS |= (uint32_t)(enSf<<enTimG);
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——Timer ETR选择配置
 **
 ** \param [in]  enTimE       Timer类型选择枚举
 ** \param [in]  enSf         Timer互联功能选择枚举
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfTimEConfig(en_gpio_sf_tim_e_t enTimE, en_gpio_sf_t enSf)
{
    M0P_GPIO->TIMES &= (uint32_t)(~(0x07U<<enTimE));
    M0P_GPIO->TIMES |= (uint32_t)(enSf<<enTimE);
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——Timer 捕获输入选择配置
 **
 ** \param [in]  enTimC       Timer类型选择枚举
 ** \param [in]  enSf         Timer互联功能选择枚举
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfTimCConfig(en_gpio_sf_tim_c_t enTimC, en_gpio_sf_t enSf)
{
    M0P_GPIO->TIMCPS &= (uint32_t)(~(0x07u<<enTimC));
    M0P_GPIO->TIMCPS |= (uint32_t)(enSf<<enTimC);
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO 端口辅助功能配置——PCA 捕获输入选择配置
 **
 ** \param [in]  enPca        PCA类型选择枚举
 ** \param [in]  enSf         PCA互联功能选择枚举
 **
 ** \retval    Ok       设置成功
 ******************************************************************************/
en_result_t Gpio_SfPcaConfig(en_gpio_sf_pca_t enPca, en_gpio_sf_t enSf)
{
    if(GpioSfPcaCH0 == enPca)
    {
        M0P_GPIO->PCAS_f.PCA_CH0 = enSf;
    }
    
    if(GpioSfPcaECI == enPca)
    {
        M0P_GPIO->PCAS_f.PCA_ECI = enSf;
    }
    
    return Ok;
}


//@} // GpioGroup


/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

