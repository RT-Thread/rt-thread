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
/******************************************************************************/
/** \file swdt.c
 **
 ** A detailed description is available at
 ** @link SwdtGroup Swdt description @endlink
 **
 **   - 2017-03-13  1.0  yangjp First version for Device Driver Library of Swdt.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "swdt.h"

/**
 *******************************************************************************
 ** \addtogroup SwdtGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*! SWDT_RR register refresh key */
#define SWDT_REFRESH_KEY_START       ((uint16_t)0x0123)
#define SWDT_REFRESH_KEY_END         ((uint16_t)0x3210)

/*! Parameter validity check for interrupt flag type */
#define IS_SWDT_IRQ_FLAG(x)          (((x) == Swdt_CountUnderflow_Irq)    || \
                                      ((x) == Swdt_RefreshError_Irq))

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
 ** \brief   Swdt refresh counter
 **
 ** \param   none
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Swdt_RefreshCounter(void)
{
    M4_SWDT->RR = SWDT_REFRESH_KEY_START;
    M4_SWDT->RR = SWDT_REFRESH_KEY_END;
}

/**
 *******************************************************************************
 ** \brief   Swdt gets the current count value
 **
 ** \param   none
 **                                   
 ** \retval  [out]  current count value
 **
 ******************************************************************************/
uint16_t Swdt_GetCountValue(void)
{
    return ((uint16_t)M4_SWDT->SR);
}

/**
 *******************************************************************************
 ** \brief   Swdt get interrupt flags
 **
 ** \param   none
 **                                   
 ** \retval  [out]  status register all interrupt flags
 **
 ******************************************************************************/
uint8_t Swdt_GetIrqFlag(void)
{
    return ((uint8_t)(((M4_SWDT->SR)>>16) & 0x03));
}

/**
 *******************************************************************************
 ** \brief   Swdt clear interrupt flags
 **
 ** \param   [in]  enPort             GPIO port index, This parameter can be 
 **                                   any value of @ref en_port_t
 **                                   
 ** \retval  none
 **
 ******************************************************************************/
void Swdt_ClearIrqFlag(en_swdt_irq_flag_t irqFlag)
{
    /* Check the parameter */
    DDL_ASSERT(IS_SWDT_IRQ_FLAG(irqFlag));

    /* clear the status */
    switch (irqFlag)
    {
        case Swdt_CountUnderflow_Irq:
            M4_SWDT->SR_f.UDF = 0u;
            break;
        case Swdt_RefreshError_Irq:
            M4_SWDT->SR_f.REF = 0u;
            break;
        default:
            break;
    }
}


//@} // SwdtGroup

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
