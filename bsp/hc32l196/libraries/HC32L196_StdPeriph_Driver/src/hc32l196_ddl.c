/*******************************************************************************
* Copyright (C) 2019, Huada Semiconductor Co.,Ltd All rights reserved.    
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
 ** Common API of DDL.
 ** @link ddlGroup Some description @endlink
 **
 **   - 2019-03-03
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "hc32l196_ddl.h"

/**
 ******************************************************************************
 ** \addtogroup DDL Common Functions
 ******************************************************************************/
//@{

/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/

/******************************************************************************/
/* Global variable definitions (declared in header file with 'extern')        */
/******************************************************************************/

/******************************************************************************/
/* Local type definitions ('typedef')                                         */
/******************************************************************************/

/******************************************************************************/
/* Local variable definitions ('static')                                      */
/******************************************************************************/

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Function implementation - global ('extern') and local ('static')           */
/******************************************************************************/
#ifndef __DEBUG
#define __DEBUG
//#define __CC_ARM
#endif

uint32_t Log2(uint32_t u32Val)
{
    uint32_t u32V1 = 0;
    
    if(0u == u32Val)
    {
        return 0;
    }
    
    while(u32Val > 1u)
    {
        u32V1++;
        u32Val /=2;
    }
    
    return u32V1;
}


/**
 *******************************************************************************
 ** \brief Memory clear function for DDL_ZERO_STRUCT()
 ******************************************************************************/
void ddl_memclr(void *pu8Address, uint32_t u32Count)
{
    uint8_t *pu8Addr = (uint8_t *)pu8Address;
    
    if(NULL == pu8Addr)
    {
        return;
    }
    
    while (u32Count--)
    {
        *pu8Addr++ = 0;
    }
}

/**
 * \brief   delay1ms
 *          delay approximately 1ms.
 * \param   [in]  u32Cnt
 * \retval  void
 */
void delay1ms(uint32_t u32Cnt)
{
    uint32_t u32end;
    
    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL  = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
    
    while(u32Cnt-- > 0)
    {
        SysTick->VAL  = 0;
        u32end = 0x1000000 - SystemCoreClock/1000;
        while(SysTick->VAL > u32end)
        {
            ;
        }
    }
    
    SysTick->CTRL = (SysTick->CTRL & (~SysTick_CTRL_ENABLE_Msk));
}

/**
 * \brief   delay100us
 *          delay approximately 100us.
 * \param   [in]  u32Cnt
 * \retval  void
 */
void delay100us(uint32_t u32Cnt)
{
    uint32_t u32end;
    
    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL  = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
    
    while(u32Cnt-- > 0)
    {
        SysTick->VAL = 0;

        u32end = 0x1000000 - SystemCoreClock/10000;
        while(SysTick->VAL > u32end)
        {
            ;
        }
    }
    
    SysTick->CTRL = (SysTick->CTRL & (~SysTick_CTRL_ENABLE_Msk));
}

/**
 * \brief   delay10us
 *          delay approximately 10us.
 * \param   [in]  u32Cnt
 * \retval  void
 */
void delay10us(uint32_t u32Cnt)
{
    uint32_t u32end;
    
    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL  = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
    
    while(u32Cnt-- > 0)
    {
        SysTick->VAL = 0;

        u32end = 0x1000000 - SystemCoreClock/100000;
        while(SysTick->VAL > u32end)
        {
            ;
        }
    }
    
    SysTick->CTRL = (SysTick->CTRL & (~SysTick_CTRL_ENABLE_Msk));
}

/**
 * \brief   set register bit
 *          
 * \param   [in]  addr
 * \param   [in]  offset
 * \retval  void
 */
void SetBit(uint32_t addr, uint32_t offset, boolean_t bFlag)
{
    if(TRUE == bFlag)
    {
        *((volatile uint32_t *)(addr)) |= ((1UL)<<(offset));
    }
    else
    {
        *((volatile uint32_t *)(addr)) &= (~(1UL<<(offset)));
    }    
    
    
}


/**
 * \brief   get register bit
 *          
 * \param   [in]  addr
 * \param   [in]  offset
 * \retval  void
 */
boolean_t GetBit(uint32_t addr, uint32_t offset)
{
    return ((((*((volatile uint32_t *)(addr))) >> (offset)) & 1u) > 0) ? TRUE : FALSE;
}
//@} // DDL Functions

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

