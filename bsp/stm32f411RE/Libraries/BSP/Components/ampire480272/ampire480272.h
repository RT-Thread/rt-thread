/**
  ******************************************************************************
  * @file    ampire480272.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-February-2014
  * @brief   This file contains all the constants parameters for the ampire480272
  *          LCD component.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AMPIRE480272_H
#define __AMPIRE480272_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/  

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
  
/** @addtogroup ampire480272
  * @{
  */

/** @defgroup AMPIRE480272_Exported_Types
  * @{
  */
   
/**
  * @}
  */ 

/** @defgroup AMPIRE480272_Exported_Constants
  * @{
  */
  
/** 
  * @brief  AMPIRE480272 Size  
  */     
#define  AMPIRE480272_WIDTH    ((uint16_t)480)          /* LCD PIXEL WIDTH            */
#define  AMPIRE480272_HEIGHT   ((uint16_t)272)          /* LCD PIXEL HEIGHT           */

/** 
  * @brief  AMPIRE480272 Timing  
  */     
#define  AMPIRE480272_HSYNC            ((uint16_t)41)   /* Horizontal synchronization */
#define  AMPIRE480272_HBP              ((uint16_t)2)    /* Horizontal back porch      */ 
#define  AMPIRE480272_HFP              ((uint16_t)2)    /* Horizontal front porch     */
#define  AMPIRE480272_VSYNC            ((uint16_t)10)   /* Vertical synchronization   */
#define  AMPIRE480272_VBP              ((uint16_t)2)    /* Vertical back porch        */
#define  AMPIRE480272_VFP              ((uint16_t)2)    /* Vertical front porch       */

/** 
  * @brief  AMPIRE480272 frequency divider  
  */    
#define  AMPIRE480272_FREQUENCY_DIVIDER    5            /* LCD Frequency divider      */
/**
  * @}
  */
  
/** @defgroup AMPIRE480272_Exported_Functions
  * @{
  */    

/**
  * @}
  */    
#ifdef __cplusplus
}
#endif

#endif /* __AMPIRE480272_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
