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
/** \file crc.h
**
** CRC 数据结构及API声明.
**
**   - 2016-05-04  LuX V1.0.
**
******************************************************************************/

#ifndef __CRC_H__
#define __HDIV_H__

/******************************************************************************
* Include files
******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif
  
  /**
  ******************************************************************************
  ** \defgroup CrcGroup Cyclic Redundancy Check (CRC)
  **
  ******************************************************************************/
  //@{
  
  /******************************************************************************
  * Global type definitions
  ******************************************************************************/
  
  /******************************************************************************
  * Global definitions
  ******************************************************************************/
  
  /******************************************************************************
  * Local type definitions ('typedef')
  ******************************************************************************/
  typedef struct stc_div_unsigned_result
  {
    uint32_t Quotient;
    uint32_t Remainder;	
  }stc_div_unsigned_result_t;
  
  typedef struct stc_div_signed_result
  {
    int32_t Quotient;
    int32_t Remainder;	
  }stc_div_signed_result_t;
  /******************************************************************************
  * Global variable definitions ('extern')
  ******************************************************************************/
  
  /******************************************************************************
  * Global function prototypes (definition in C source)                        
  ******************************************************************************/
  //HDIV
  en_result_t Hdiv_Unsigned(uint32_t Dividend,uint16_t Divisor,stc_div_unsigned_result_t* stcDivResult);
  en_result_t Hdiv_Signed(int32_t Dividend,int16_t Divisor,stc_div_signed_result_t* stcDivResult);
  
  boolean_t Hdiv_GetEndState(void);
  boolean_t Hdiv_GetZeroState(void);
  
  //@} // CRC Group
  
#ifdef __cplusplus
}
#endif

#endif /* __CRC_H__ */
/******************************************************************************
* EOF (not truncated)
******************************************************************************/

