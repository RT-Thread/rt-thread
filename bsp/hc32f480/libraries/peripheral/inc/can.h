/*****************************************************************************
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
/** \file gpio.h
 **
 ** A detailed description is available at
 ** @link GpioGroup Gpio description @endlink
 **
 **   - 2018-03-07  1.0  Zhangxl First version for Device Driver Library of Gpio.
 **
 ******************************************************************************/

#ifndef __CAN_H__
#define __CAN_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f480.h"
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup GpioGroup General Purpose Input/Output(GPIO)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
 typedef struct 
 {
     __IO uint32_t ID                     : 29;
     uint32_t RESERVED1                   : 2;
     __IO uint32_t ESI                    : 1;
 
 }stc_can_rxid_field_t;
 typedef struct 
 {
     __IO uint32_t ID                     : 29;
     uint32_t RESERVED1                   : 2;
     __IO uint32_t TTSEN                  : 1;
 
 }stc_can_txid_field_t;
  typedef struct 
 { 
     __IO uint32_t DLC                     : 4;
     __IO uint32_t BRS                     : 1;     
     __IO uint32_t EDL                     : 1;
     __IO uint32_t RTR                     : 1;
     __IO uint32_t IDE                     : 1;
     __IO uint32_t RESERVED3               : 24;
  }stc_can_txctrl_field_t;
   typedef struct 
 { 
     __IO uint32_t DLC                     : 4;
     __IO uint32_t BRS                     : 1;     
     __IO uint32_t EDL                     : 1;
     __IO uint32_t RTR                     : 1;
     __IO uint32_t IDE                     : 1;
  }stc_can_rxctrl_field_t; 
 typedef struct 
   
 { 
     __IO uint8_t RESERVED2               : 4;
     __IO uint8_t TX                      : 1;     
     __IO uint8_t KOER                    : 3;
  }stc_can_status_field_t;
 
 
  typedef struct stc_can_rxframe_format
  {
    union
    {
        __IO uint32_t ID;
        stc_can_rxid_field_t ID_f;
    };
    union
    {
        __IO uint8_t CTRL;
        stc_can_rxctrl_field_t CTRL_f;
    };
    union
    {
        __IO uint8_t STATUS;
        stc_can_status_field_t STATUS_f;
    }; 
    __IO uint16_t CYCLETIME;//TTCAN
    __IO uint32_t  data[16];
    /* 
    CiA 603
    */
    
  }stc_can_rxframe_format_t;
  
  
  typedef struct stc_can_txframe_format
  {
    union
    {
        __IO uint32_t ID;
        stc_can_txid_field_t ID_f;
    };
    union
    {
        __IO uint32_t CTRL;
        stc_can_txctrl_field_t CTRL_f;
    };
    __IO uint32_t  data[16];
    /* 
    CiA 603
    */
    
  }stc_can_txframe_format_t;
  
  typedef enum
  {
    NOERR = 0,
    BITERR,
    FORMERR,
    STUFFERR,
    ACKERR,
    CRCERR,
    OTHER
  }stc_can_koer_err_t;
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

//@} // GpioGroup

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H_ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
