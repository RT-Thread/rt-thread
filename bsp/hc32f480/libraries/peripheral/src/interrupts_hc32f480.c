/******************************************************************************
* Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
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
/*****************************************************************************/
/** \file interrupts_hc32f480.c
 **
 ** A detailed description is available at
 ** @link InterruptGroup Interrupt description @endlink
 **
 **   - 2018-03-02  1.0  Zhangxl First version for Device Driver Library of
 **     interrupt.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "interrupts_hc32f480.h"

/**
 *******************************************************************************
 ** \addtogroup InterruptGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
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
#define IRQ_NUM_MAX  128

func_ptr_t IrqHandler[IRQ_NUM_MAX] = {NULL};

/**
 *******************************************************************************
 ** \brief IRQ Registration
 **
 ** param [in]  stcIrqRegiConf
 **
 ** retval      Ok
 **             ErrorInvalidParameter, pfnCallback == NULL or ...
 **
 ******************************************************************************/
en_result_t enIrqRegistration(stc_irq_regi_conf_t stcIrqRegiConf)
{
    // todo, assert ...
    stc_intc_intsel0_field_t *stcIntSel;

    if (NULL == stcIrqRegiConf.pfnCallback)
    {
        return ErrorInvalidParameter;
    }
    stcIntSel = (stc_intc_intsel0_field_t *)((uint32_t)(&M4_INTC->INTSEL0) + (4 * stcIrqRegiConf.enIRQn));
    stcIntSel->INTSEL = stcIrqRegiConf.enIntSrc;
    IrqHandler[stcIrqRegiConf.enIRQn] = stcIrqRegiConf.pfnCallback;
    return Ok;
}

/**
 *******************************************************************************
 ** \brief NMI IRQ handler
 **
 ******************************************************************************/
void NMI_Handler(void)
{
    Nmi_IrqHandler();
}

/**
 *******************************************************************************
 ** \brief MPU Fault IRQ handler
 **
 ******************************************************************************/
void MemManage_Handler(void)
{
    MemManage_IrqHandler();
}

/**
 *******************************************************************************
 ** \brief Bus Fault IRQ handler
 **
 ******************************************************************************/
void BusFault_Handler(void)
{
    BusFault_IrqHandler();
}

/**
 *******************************************************************************
 ** \brief Usage Fault IRQ handler
 **
 ******************************************************************************/
void UsageFault_Handler(void)
{
    UsageFault_IrqHandler();
}

/**
 *******************************************************************************
 ** \brief DebugMon IRQ handler
 **
 ******************************************************************************/
void DebugMon_Handler(void)
{
    DebugMon_IrqHandler();
}


/**
 *******************************************************************************
 ** \brief Int No.000 IRQ handler
 **
 ******************************************************************************/
void IRQ000_Handler(void)
{
    if (NULL != IrqHandler[Int000_IRQn])
    {
        IrqHandler[Int000_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.001 IRQ handler
 **
 ******************************************************************************/
void IRQ001_Handler(void)
{
    if (NULL != IrqHandler[Int001_IRQn])
    {
        IrqHandler[Int001_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.002 IRQ handler
 **
 ******************************************************************************/
void IRQ002_Handler(void)
{
    if (NULL != IrqHandler[Int002_IRQn])
    {
        IrqHandler[Int002_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.003 IRQ handler
 **
 ******************************************************************************/
void IRQ003_Handler(void)
{
    if (NULL != IrqHandler[Int003_IRQn])
    {
        IrqHandler[Int003_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.004 IRQ handler
 **
 ******************************************************************************/
void IRQ004_Handler(void)
{
    if (NULL != IrqHandler[Int004_IRQn])
    {
        IrqHandler[Int004_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.005 IRQ handler
 **
 ******************************************************************************/
void IRQ005_Handler(void)
{
    if (NULL != IrqHandler[Int005_IRQn])
    {
        IrqHandler[Int005_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.006 IRQ handler
 **
 ******************************************************************************/
void IRQ006_Handler(void)
{
    if (NULL != IrqHandler[Int006_IRQn])
    {
        IrqHandler[Int006_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.007 IRQ handler
 **
 ******************************************************************************/
void IRQ007_Handler(void)
{
    if (NULL != IrqHandler[Int007_IRQn])
    {
        IrqHandler[Int007_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.008 IRQ handler
 **
 ******************************************************************************/
void IRQ008_Handler(void)
{
    if (NULL != IrqHandler[Int008_IRQn])
    {
        IrqHandler[Int008_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.009 IRQ handler
 **
 ******************************************************************************/
void IRQ009_Handler(void)
{
    if (NULL != IrqHandler[Int009_IRQn])
    {
        IrqHandler[Int009_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.010 IRQ handler
 **
 ******************************************************************************/
void IRQ010_Handler(void)
{
    if (NULL != IrqHandler[Int010_IRQn])
    {
        IrqHandler[Int010_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.011 IRQ handler
 **
 ******************************************************************************/
void IRQ011_Handler(void)
{
    if (NULL != IrqHandler[Int011_IRQn])
    {
        IrqHandler[Int011_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.012 IRQ handler
 **
 ******************************************************************************/
void IRQ012_Handler(void)
{
    if (NULL != IrqHandler[Int012_IRQn])
    {
        IrqHandler[Int012_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.013 IRQ handler
 **
 ******************************************************************************/
void IRQ013_Handler(void)
{
    if (NULL != IrqHandler[Int013_IRQn])
    {
        IrqHandler[Int013_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.014 IRQ handler
 **
 ******************************************************************************/
void IRQ014_Handler(void)
{
    if (NULL != IrqHandler[Int014_IRQn])
    {
        IrqHandler[Int014_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.015 IRQ handler
 **
 ******************************************************************************/
void IRQ015_Handler(void)
{
    if (NULL != IrqHandler[Int015_IRQn])
    {
        IrqHandler[Int015_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.016 IRQ handler
 **
 ******************************************************************************/
void IRQ016_Handler(void)
{
    if (NULL != IrqHandler[Int016_IRQn])
    {
        IrqHandler[Int016_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.017 IRQ handler
 **
 ******************************************************************************/
void IRQ017_Handler(void)
{
    if (NULL != IrqHandler[Int017_IRQn])
    {
        IrqHandler[Int017_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.018 IRQ handler
 **
 ******************************************************************************/
void IRQ018_Handler(void)
{
    if (NULL != IrqHandler[Int018_IRQn])
    {
        IrqHandler[Int018_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.019 IRQ handler
 **
 ******************************************************************************/
void IRQ019_Handler(void)
{
    if (NULL != IrqHandler[Int019_IRQn])
    {
        IrqHandler[Int019_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.020 IRQ handler
 **
 ******************************************************************************/
void IRQ020_Handler(void)
{
    if (NULL != IrqHandler[Int020_IRQn])
    {
        IrqHandler[Int020_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.021 IRQ handler
 **
 ******************************************************************************/
void IRQ021_Handler(void)
{
    if (NULL != IrqHandler[Int021_IRQn])
    {
        IrqHandler[Int021_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.022 IRQ handler
 **
 ******************************************************************************/
void IRQ022_Handler(void)
{
    if (NULL != IrqHandler[Int022_IRQn])
    {
        IrqHandler[Int022_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.023 IRQ handler
 **
 ******************************************************************************/
void IRQ023_Handler(void)
{
    if (NULL != IrqHandler[Int023_IRQn])
    {
        IrqHandler[Int023_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.024 IRQ handler
 **
 ******************************************************************************/
void IRQ024_Handler(void)
{
    if (NULL != IrqHandler[Int024_IRQn])
    {
        IrqHandler[Int024_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.025 IRQ handler
 **
 ******************************************************************************/
void IRQ025_Handler(void)
{
    if (NULL != IrqHandler[Int025_IRQn])
    {
        IrqHandler[Int025_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.026 IRQ handler
 **
 ******************************************************************************/
void IRQ026_Handler(void)
{
    if (NULL != IrqHandler[Int026_IRQn])
    {
        IrqHandler[Int026_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.027 IRQ handler
 **
 ******************************************************************************/
void IRQ027_Handler(void)
{
    if (NULL != IrqHandler[Int027_IRQn])
    {
        IrqHandler[Int027_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.028 IRQ handler
 **
 ******************************************************************************/
void IRQ028_Handler(void)
{
    if (NULL != IrqHandler[Int028_IRQn])
    {
        IrqHandler[Int028_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.029 IRQ handler
 **
 ******************************************************************************/
void IRQ029_Handler(void)
{
    if (NULL != IrqHandler[Int029_IRQn])
    {
        IrqHandler[Int029_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.030 IRQ handler
 **
 ******************************************************************************/
void IRQ030_Handler(void)
{
    if (NULL != IrqHandler[Int030_IRQn])
    {
        IrqHandler[Int030_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.031 IRQ handler
 **
 ******************************************************************************/
void IRQ031_Handler(void)
{
    if (NULL != IrqHandler[Int031_IRQn])
    {
        IrqHandler[Int031_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.032 IRQ handler
 **
 ******************************************************************************/
void IRQ032_Handler(void)
{
    if (NULL != IrqHandler[Int032_IRQn])
    {
        IrqHandler[Int032_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.033 IRQ handler
 **
 ******************************************************************************/
void IRQ033_Handler(void)
{
    if (NULL != IrqHandler[Int033_IRQn])
    {
        IrqHandler[Int033_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.034 IRQ handler
 **
 ******************************************************************************/
void IRQ034_Handler(void)
{
    if (NULL != IrqHandler[Int034_IRQn])
    {
        IrqHandler[Int034_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.035 IRQ handler
 **
 ******************************************************************************/
void IRQ035_Handler(void)
{
    if (NULL != IrqHandler[Int035_IRQn])
    {
        IrqHandler[Int035_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.036 IRQ handler
 **
 ******************************************************************************/
void IRQ036_Handler(void)
{
    if (NULL != IrqHandler[Int036_IRQn])
    {
        IrqHandler[Int036_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.037 IRQ handler
 **
 ******************************************************************************/
void IRQ037_Handler(void)
{
    if (NULL != IrqHandler[Int037_IRQn])
    {
        IrqHandler[Int037_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.038 IRQ handler
 **
 ******************************************************************************/
void IRQ038_Handler(void)
{
    if (NULL != IrqHandler[Int038_IRQn])
    {
        IrqHandler[Int038_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.039 IRQ handler
 **
 ******************************************************************************/
void IRQ039_Handler(void)
{
    if (NULL != IrqHandler[Int039_IRQn])
    {
        IrqHandler[Int039_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.040 IRQ handler
 **
 ******************************************************************************/
void IRQ040_Handler(void)
{
    if (NULL != IrqHandler[Int040_IRQn])
    {
        IrqHandler[Int040_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.041 IRQ handler
 **
 ******************************************************************************/
void IRQ041_Handler(void)
{
    if (NULL != IrqHandler[Int041_IRQn])
    {
        IrqHandler[Int041_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.042 IRQ handler
 **
 ******************************************************************************/
void IRQ042_Handler(void)
{
    if (NULL != IrqHandler[Int042_IRQn])
    {
        IrqHandler[Int042_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.043 IRQ handler
 **
 ******************************************************************************/
void IRQ043_Handler(void)
{
    if (NULL != IrqHandler[Int043_IRQn])
    {
        IrqHandler[Int043_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.044 IRQ handler
 **
 ******************************************************************************/
void IRQ044_Handler(void)
{
    if (NULL != IrqHandler[Int044_IRQn])
    {
        IrqHandler[Int044_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.045 IRQ handler
 **
 ******************************************************************************/
void IRQ045_Handler(void)
{
    if (NULL != IrqHandler[Int045_IRQn])
    {
        IrqHandler[Int045_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.046 IRQ handler
 **
 ******************************************************************************/
void IRQ046_Handler(void)
{
    if (NULL != IrqHandler[Int046_IRQn])
    {
        IrqHandler[Int046_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.047 IRQ handler
 **
 ******************************************************************************/
void IRQ047_Handler(void)
{
    if (NULL != IrqHandler[Int047_IRQn])
    {
        IrqHandler[Int047_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.048 IRQ handler
 **
 ******************************************************************************/
void IRQ048_Handler(void)
{
    if (NULL != IrqHandler[Int048_IRQn])
    {
        IrqHandler[Int048_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.049 IRQ handler
 **
 ******************************************************************************/
void IRQ049_Handler(void)
{
    if (NULL != IrqHandler[Int049_IRQn])
    {
        IrqHandler[Int049_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.050 IRQ handler
 **
 ******************************************************************************/
void IRQ050_Handler(void)
{
    if (NULL != IrqHandler[Int050_IRQn])
    {
        IrqHandler[Int050_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.051 IRQ handler
 **
 ******************************************************************************/
void IRQ051_Handler(void)
{
    if (NULL != IrqHandler[Int051_IRQn])
    {
        IrqHandler[Int051_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.052 IRQ handler
 **
 ******************************************************************************/
void IRQ052_Handler(void)
{
    if (NULL != IrqHandler[Int052_IRQn])
    {
        IrqHandler[Int052_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.053 IRQ handler
 **
 ******************************************************************************/
void IRQ053_Handler(void)
{
    if (NULL != IrqHandler[Int053_IRQn])
    {
        IrqHandler[Int053_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.054 IRQ handler
 **
 ******************************************************************************/
void IRQ054_Handler(void)
{
    if (NULL != IrqHandler[Int054_IRQn])
    {
        IrqHandler[Int054_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.055 IRQ handler
 **
 ******************************************************************************/
void IRQ055_Handler(void)
{
    if (NULL != IrqHandler[Int055_IRQn])
    {
        IrqHandler[Int055_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.056 IRQ handler
 **
 ******************************************************************************/
void IRQ056_Handler(void)
{
    if (NULL != IrqHandler[Int056_IRQn])
    {
        IrqHandler[Int056_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.057 IRQ handler
 **
 ******************************************************************************/
void IRQ057_Handler(void)
{
    if (NULL != IrqHandler[Int057_IRQn])
    {
        IrqHandler[Int057_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.058 IRQ handler
 **
 ******************************************************************************/
void IRQ058_Handler(void)
{
    if (NULL != IrqHandler[Int058_IRQn])
    {
        IrqHandler[Int058_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.059 IRQ handler
 **
 ******************************************************************************/
void IRQ059_Handler(void)
{
    if (NULL != IrqHandler[Int059_IRQn])
    {
        IrqHandler[Int059_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.060 IRQ handler
 **
 ******************************************************************************/
void IRQ060_Handler(void)
{
    if (NULL != IrqHandler[Int060_IRQn])
    {
        IrqHandler[Int060_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.061 IRQ handler
 **
 ******************************************************************************/
void IRQ061_Handler(void)
{
    if (NULL != IrqHandler[Int061_IRQn])
    {
        IrqHandler[Int061_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.062 IRQ handler
 **
 ******************************************************************************/
void IRQ062_Handler(void)
{
    if (NULL != IrqHandler[Int062_IRQn])
    {
        IrqHandler[Int062_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.063 IRQ handler
 **
 ******************************************************************************/
void IRQ063_Handler(void)
{
    if (NULL != IrqHandler[Int063_IRQn])
    {
        IrqHandler[Int063_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.064 IRQ handler
 **
 ******************************************************************************/
void IRQ064_Handler(void)
{
    if (NULL != IrqHandler[Int064_IRQn])
    {
        IrqHandler[Int064_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.065 IRQ handler
 **
 ******************************************************************************/
void IRQ065_Handler(void)
{
    if (NULL != IrqHandler[Int065_IRQn])
    {
        IrqHandler[Int065_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.066 IRQ handler
 **
 ******************************************************************************/
void IRQ066_Handler(void)
{
    if (NULL != IrqHandler[Int066_IRQn])
    {
        IrqHandler[Int066_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.067 IRQ handler
 **
 ******************************************************************************/
void IRQ067_Handler(void)
{
    if (NULL != IrqHandler[Int067_IRQn])
    {
        IrqHandler[Int067_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.068 IRQ handler
 **
 ******************************************************************************/
void IRQ068_Handler(void)
{
    if (NULL != IrqHandler[Int068_IRQn])
    {
        IrqHandler[Int068_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.069 IRQ handler
 **
 ******************************************************************************/
void IRQ069_Handler(void)
{
    if (NULL != IrqHandler[Int069_IRQn])
    {
        IrqHandler[Int069_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.070 IRQ handler
 **
 ******************************************************************************/
void IRQ070_Handler(void)
{
    if (NULL != IrqHandler[Int070_IRQn])
    {
        IrqHandler[Int070_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.071 IRQ handler
 **
 ******************************************************************************/
void IRQ071_Handler(void)
{
    if (NULL != IrqHandler[Int071_IRQn])
    {
        IrqHandler[Int071_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.072 IRQ handler
 **
 ******************************************************************************/
void IRQ072_Handler(void)
{
    if (NULL != IrqHandler[Int072_IRQn])
    {
        IrqHandler[Int072_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.073 IRQ handler
 **
 ******************************************************************************/
void IRQ073_Handler(void)
{
    if (NULL != IrqHandler[Int073_IRQn])
    {
        IrqHandler[Int073_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.074 IRQ handler
 **
 ******************************************************************************/
void IRQ074_Handler(void)
{
    if (NULL != IrqHandler[Int074_IRQn])
    {
        IrqHandler[Int074_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.075 IRQ handler
 **
 ******************************************************************************/
void IRQ075_Handler(void)
{
    if (NULL != IrqHandler[Int075_IRQn])
    {
        IrqHandler[Int075_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.076 IRQ handler
 **
 ******************************************************************************/
void IRQ076_Handler(void)
{
    if (NULL != IrqHandler[Int076_IRQn])
    {
        IrqHandler[Int076_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.077 IRQ handler
 **
 ******************************************************************************/
void IRQ077_Handler(void)
{
    if (NULL != IrqHandler[Int077_IRQn])
    {
        IrqHandler[Int077_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.078 IRQ handler
 **
 ******************************************************************************/
void IRQ078_Handler(void)
{
    if (NULL != IrqHandler[Int078_IRQn])
    {
        IrqHandler[Int078_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.079 IRQ handler
 **
 ******************************************************************************/
void IRQ079_Handler(void)
{
    if (NULL != IrqHandler[Int079_IRQn])
    {
        IrqHandler[Int079_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.080 IRQ handler
 **
 ******************************************************************************/
void IRQ080_Handler(void)
{
    if (NULL != IrqHandler[Int080_IRQn])
    {
        IrqHandler[Int080_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.081 IRQ handler
 **
 ******************************************************************************/
void IRQ081_Handler(void)
{
    if (NULL != IrqHandler[Int081_IRQn])
    {
        IrqHandler[Int081_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.082 IRQ handler
 **
 ******************************************************************************/
void IRQ082_Handler(void)
{
    if (NULL != IrqHandler[Int082_IRQn])
    {
        IrqHandler[Int082_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.083 IRQ handler
 **
 ******************************************************************************/
void IRQ083_Handler(void)
{
    if (NULL != IrqHandler[Int083_IRQn])
    {
        IrqHandler[Int083_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.084 IRQ handler
 **
 ******************************************************************************/
void IRQ084_Handler(void)
{
    if (NULL != IrqHandler[Int084_IRQn])
    {
        IrqHandler[Int084_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.085 IRQ handler
 **
 ******************************************************************************/
void IRQ085_Handler(void)
{
    if (NULL != IrqHandler[Int085_IRQn])
    {
        IrqHandler[Int085_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.086 IRQ handler
 **
 ******************************************************************************/
void IRQ086_Handler(void)
{
    if (NULL != IrqHandler[Int086_IRQn])
    {
        IrqHandler[Int086_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.087 IRQ handler
 **
 ******************************************************************************/
void IRQ087_Handler(void)
{
    if (NULL != IrqHandler[Int087_IRQn])
    {
        IrqHandler[Int087_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.088 IRQ handler
 **
 ******************************************************************************/
void IRQ088_Handler(void)
{
    if (NULL != IrqHandler[Int088_IRQn])
    {
        IrqHandler[Int088_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.089 IRQ handler
 **
 ******************************************************************************/
void IRQ089_Handler(void)
{
    if (NULL != IrqHandler[Int089_IRQn])
    {
        IrqHandler[Int089_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.090 IRQ handler
 **
 ******************************************************************************/
void IRQ090_Handler(void)
{
    if (NULL != IrqHandler[Int090_IRQn])
    {
        IrqHandler[Int090_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.091 IRQ handler
 **
 ******************************************************************************/
void IRQ091_Handler(void)
{
    if (NULL != IrqHandler[Int091_IRQn])
    {
        IrqHandler[Int091_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.092 IRQ handler
 **
 ******************************************************************************/
void IRQ092_Handler(void)
{
    if (NULL != IrqHandler[Int092_IRQn])
    {
        IrqHandler[Int092_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.093 IRQ handler
 **
 ******************************************************************************/
void IRQ093_Handler(void)
{
    if (NULL != IrqHandler[Int093_IRQn])
    {
        IrqHandler[Int093_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.094 IRQ handler
 **
 ******************************************************************************/
void IRQ094_Handler(void)
{
    if (NULL != IrqHandler[Int094_IRQn])
    {
        IrqHandler[Int094_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.095 IRQ handler
 **
 ******************************************************************************/
void IRQ095_Handler(void)
{
    if (NULL != IrqHandler[Int095_IRQn])
    {
        IrqHandler[Int095_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.096 IRQ handler
 **
 ******************************************************************************/
void IRQ096_Handler(void)
{
    if (NULL != IrqHandler[Int096_IRQn])
    {
        IrqHandler[Int096_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.097 IRQ handler
 **
 ******************************************************************************/
void IRQ097_Handler(void)
{
    if (NULL != IrqHandler[Int097_IRQn])
    {
        IrqHandler[Int097_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.098 IRQ handler
 **
 ******************************************************************************/
void IRQ098_Handler(void)
{
    if (NULL != IrqHandler[Int098_IRQn])
    {
        IrqHandler[Int098_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.099 IRQ handler
 **
 ******************************************************************************/
void IRQ099_Handler(void)
{
    if (NULL != IrqHandler[Int099_IRQn])
    {
        IrqHandler[Int099_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.100 IRQ handler
 **
 ******************************************************************************/
void IRQ100_Handler(void)
{
    if (NULL != IrqHandler[Int100_IRQn])
    {
        IrqHandler[Int100_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.101 IRQ handler
 **
 ******************************************************************************/
void IRQ101_Handler(void)
{
    if (NULL != IrqHandler[Int101_IRQn])
    {
        IrqHandler[Int101_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.102 IRQ handler
 **
 ******************************************************************************/
void IRQ102_Handler(void)
{
    if (NULL != IrqHandler[Int102_IRQn])
    {
        IrqHandler[Int102_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.103 IRQ handler
 **
 ******************************************************************************/
void IRQ103_Handler(void)
{
    if (NULL != IrqHandler[Int103_IRQn])
    {
        IrqHandler[Int103_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.104 IRQ handler
 **
 ******************************************************************************/
void IRQ104_Handler(void)
{
    if (NULL != IrqHandler[Int104_IRQn])
    {
        IrqHandler[Int104_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.105 IRQ handler
 **
 ******************************************************************************/
void IRQ105_Handler(void)
{
    if (NULL != IrqHandler[Int105_IRQn])
    {
        IrqHandler[Int105_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.106 IRQ handler
 **
 ******************************************************************************/
void IRQ106_Handler(void)
{
    if (NULL != IrqHandler[Int106_IRQn])
    {
        IrqHandler[Int106_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.107 IRQ handler
 **
 ******************************************************************************/
void IRQ107_Handler(void)
{
    if (NULL != IrqHandler[Int107_IRQn])
    {
        IrqHandler[Int107_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.108 IRQ handler
 **
 ******************************************************************************/
void IRQ108_Handler(void)
{
    if (NULL != IrqHandler[Int108_IRQn])
    {
        IrqHandler[Int108_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.109 IRQ handler
 **
 ******************************************************************************/
void IRQ109_Handler(void)
{
    if (NULL != IrqHandler[Int109_IRQn])
    {
        IrqHandler[Int109_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.110 IRQ handler
 **
 ******************************************************************************/
void IRQ110_Handler(void)
{
    if (NULL != IrqHandler[Int110_IRQn])
    {
        IrqHandler[Int110_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.111 IRQ handler
 **
 ******************************************************************************/
void IRQ111_Handler(void)
{
    if (NULL != IrqHandler[Int111_IRQn])
    {
        IrqHandler[Int111_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.112 IRQ handler
 **
 ******************************************************************************/
void IRQ112_Handler(void)
{
    if (NULL != IrqHandler[Int112_IRQn])
    {
        IrqHandler[Int112_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.113 IRQ handler
 **
 ******************************************************************************/
void IRQ113_Handler(void)
{
    if (NULL != IrqHandler[Int113_IRQn])
    {
        IrqHandler[Int113_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.114 IRQ handler
 **
 ******************************************************************************/
void IRQ114_Handler(void)
{
    if (NULL != IrqHandler[Int114_IRQn])
    {
        IrqHandler[Int114_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.115 IRQ handler
 **
 ******************************************************************************/
void IRQ115_Handler(void)
{
    if (NULL != IrqHandler[Int115_IRQn])
    {
        IrqHandler[Int115_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.116 IRQ handler
 **
 ******************************************************************************/
void IRQ116_Handler(void)
{
    if (NULL != IrqHandler[Int116_IRQn])
    {
        IrqHandler[Int116_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.117 IRQ handler
 **
 ******************************************************************************/
void IRQ117_Handler(void)
{
    if (NULL != IrqHandler[Int117_IRQn])
    {
        IrqHandler[Int117_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.118 IRQ handler
 **
 ******************************************************************************/
void IRQ118_Handler(void)
{
    if (NULL != IrqHandler[Int118_IRQn])
    {
        IrqHandler[Int118_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.119 IRQ handler
 **
 ******************************************************************************/
void IRQ119_Handler(void)
{
    if (NULL != IrqHandler[Int119_IRQn])
    {
        IrqHandler[Int119_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.120 IRQ handler
 **
 ******************************************************************************/
void IRQ120_Handler(void)
{
    if (NULL != IrqHandler[Int120_IRQn])
    {
        IrqHandler[Int120_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.121 IRQ handler
 **
 ******************************************************************************/
void IRQ121_Handler(void)
{
    if (NULL != IrqHandler[Int121_IRQn])
    {
        IrqHandler[Int121_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.122 IRQ handler
 **
 ******************************************************************************/
void IRQ122_Handler(void)
{
    if (NULL != IrqHandler[Int122_IRQn])
    {
        IrqHandler[Int122_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.123 IRQ handler
 **
 ******************************************************************************/
void IRQ123_Handler(void)
{
    if (NULL != IrqHandler[Int123_IRQn])
    {
        IrqHandler[Int123_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.124 IRQ handler
 **
 ******************************************************************************/
void IRQ124_Handler(void)
{
    if (NULL != IrqHandler[Int124_IRQn])
    {
        IrqHandler[Int124_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.125 IRQ handler
 **
 ******************************************************************************/
void IRQ125_Handler(void)
{
    if (NULL != IrqHandler[Int125_IRQn])
    {
        IrqHandler[Int125_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.126 IRQ handler
 **
 ******************************************************************************/
void IRQ126_Handler(void)
{
    if (NULL != IrqHandler[Int126_IRQn])
    {
        IrqHandler[Int126_IRQn]();
    }
}

/**
 *******************************************************************************
 ** \brief Int No.127 IRQ handler
 **
 ******************************************************************************/
void IRQ127_Handler(void)
{
    if (NULL != IrqHandler[Int127_IRQn])
    {
        IrqHandler[Int127_IRQn]();
    }
}

//@} // InterruptGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
