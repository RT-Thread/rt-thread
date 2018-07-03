/*******************************************************************************
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
/******************************************************************************/
/** \file ddl.c
 **
 ** A detailed description is available at
 ** @link DdlGroup Ddl common description @endlink
 **
 **   - 2017-5-16  1.0  Zhangxl First version for Device Driver Library of Ddl
 **     common part.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <assert.h>
#include "ddl.h"
#ifdef __DEBUG
#include "hc32f480.h"
#endif

/**
 *******************************************************************************
 ** \addtogroup DdlGroup
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

/**
 *******************************************************************************
 ** \brief Data printf via Uart Ch.3
 **
 ** \param [in]  u8Data             Data to be sent
 **
 **
 ******************************************************************************/
#ifdef __DEBUG
static void DebugOutput(uint8_t u8Data)
{
    M4_USART3->TDR_f.TDR = u8Data;
    while (0 == M4_USART3->SR_f.TCF);
}

/**
 *******************************************************************************
 ** \brief Re-target putchar function
 **
 ******************************************************************************/
int32_t fputc(int32_t ch, FILE *f)
{
    DebugOutput((uint8_t)ch);

    return (ch);
}

/**
 *******************************************************************************
 ** \brief Debug printf initialization function
 **
 ******************************************************************************/
void Ddl_UartInit(void)
{
    uint32_t u32Pclk = 0;
    volatile uint32_t u32ReloadVal = 0;

    M4_USART3->CR_f.TE = 0;
    M4_USART3->CR_f.RE = 0;
    /* unlock */
    M4_PORT->PWPR = 0xA501;   
    /* usart3_tx gpio */
    M4_PORT->PFSR402_f.FSEL = 6;
    /* lock */
    M4_PORT->PWPR = 0xA500;
    /* enable usart3 */
    M4_MSTP->FCG1_f.SCI3 = 0;   
    /* usart3 init */
    M4_USART3->MR_f.MS = 0x0;    
    M4_USART3->MR_f.CL = 0x2; 
    M4_USART3->MR_f.PE = 0x0;
    M4_USART3->MR_f.STP = 0x0;   
    M4_USART3->MR_f.ML = 0x0;
    u32Pclk = SystemCoreClock;
    u32ReloadVal = u32Pclk/(32*9600) - 1;
    M4_USART3->BRR = u32ReloadVal;
    M4_USART3->CR_f.TE = 1;  
}
#endif

/**
 *******************************************************************************
 ** \brief Delay function, delay 1ms approximately
 **
 ** \param [in]  u32Cnt             ms
 **
 **
 ******************************************************************************/
void Ddl_Delay1ms(uint32_t u32Cnt)
{
    volatile uint32_t i = 0;
    uint32_t u32Cyc = 0;

    u32Cyc = SystemCoreClock;
    u32Cyc = u32Cyc / 10000;

    while (u32Cnt-- > 0)
    {
        i = u32Cyc;
        while (i-- > 0)
        {
            ;
        }
    }
}

#ifdef __DEBUG
__WEAKDEF void Ddl_AssertHook(uint8_t* file, uint32_t line);
void Ddl_AssertHandler(uint8_t* file, uint32_t line)
{
    Ddl_AssertHook(file, line);
    assert(0);
}
#endif

//@} // DdlGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
