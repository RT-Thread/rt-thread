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

/** \file ram.c
 **
 ** Common API of ram.
 ** @link RamGroup Some description @endlink
 **
 **   - 2018-05-08
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l196_ram.h"
/**
 *******************************************************************************
 ** \addtogroup ramGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

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

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 *****************************************************************************
 ** \brief Ram奇偶校验出错地址获取
 **
 ** 
 ** \retval ERROR ADDRESS                                    
 *****************************************************************************/
uint32_t Ram_ErrAddrGet(void)
{    
    return M0P_RAM->ERRADDR;
}

/**
 *****************************************************************************
 ** \brief Ram中断标志获取
 **
 ** 
 ** \retval TRUE or FALSE                                     
 *****************************************************************************/
boolean_t Ram_GetIntFlag(void)
{    
    if(M0P_RAM->IFR & 0x1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 *****************************************************************************
 ** \brief Ram中断标志清除
 **
 **
 ** \retval Null                                      
 *****************************************************************************/
void Ram_ClearIntFlag(void)
{
    M0P_RAM->ICLR = 0u;    
}

/**
 *****************************************************************************
 ** \brief Ram中断使能
 ** 
 ** \retval Null                                     
 *****************************************************************************/
void Ram_EnableIrq (void)
{
    M0P_RAM->CR |= 0x2u;  
}

/**
 *****************************************************************************
 ** \brief ram中断禁止
 ** 
 ** \retval Null                                      
 *****************************************************************************/
void Ram_DisableIrq(void)
{
    M0P_RAM->CR &= 0x1;
}


//@} // RamGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
