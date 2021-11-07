
/***********************************************************************
 * Filename    : HAL_WDT.h
 * Description : HAL WDT driver header file
 * Author(s)   : CWT
 * version     : V1.0
 * Modify date : 2020-04-17  
 ***********************************************************************/

#ifndef __HAL_WDT_H__
#define __HAL_WDT_H__

#include "ACM32Fxx_HAL.h"


/****************  Bit definition for WDT CTRL register  ********************/
#define WDT_CTRL_EN                         BIT7
#define WDT_CTRL_MODE                       BIT6
#define WDT_CTRL_INTEN                      BIT4
#define WDT_CTRL_DIVISOR                    (BIT0|BIT1|BIT2)

/****************  Bit definition for WDTRIS register  ********************/
#define WDT_WDTRIS                          BIT0 

typedef enum
{
    WDT_MODE_RST = 0x00U, 
    WDT_MODE_INT = 0x01U,  
} WDT_MODE;  

typedef enum
{
    WDT_DIVISOR_NONE = 0x00U,  
    WDT_DIVISOR_2 = 0x01U,
    WDT_DIVISOR_4 = 0x02U,
    WDT_DIVISOR_8 = 0x03U,
    WDT_DIVISOR_16 = 0x04U,
    WDT_DIVISOR_32 = 0x05U,
    WDT_DIVISOR_64 = 0x06U,
    WDT_DIVISOR_128 = 0x07U,
} WDT_DIVISOR; 

typedef struct
{          
    WDT_DIVISOR WDTDivisor;             
    WDT_MODE WDTMode; 
    uint32_t WDTLoad;
    uint32_t WDTINTCLRTIME;
} WDT_InitTypeDef;

typedef struct
{
    WDT_TypeDef            *Instance;                /*!< WDT registers base address        */
    WDT_InitTypeDef         Init;                    /*!< WDT communication parameters      */
}WDT_HandleTypeDef;

#define WDT_ENABLE                      (0x01 << 7)
#define WDT_DISABLE                     (~WDT_ENABLE) 
#define WDT_INT_ENABLE                  (0x01 << 4)
#define WDT_INT_DISABLE                 (~WDT_INT_ENABLE) 
/************************************************************************
 * function   : HAL_WDT_Feed
 * Description: WDT feed. 
 * input : 
 *         none 
 * return: none
 ************************************************************************/
 void HAL_WDT_Feed(WDT_HandleTypeDef* hwdt);
/************************************************************************
 * function   : WDT_IRQHandler
 * Description: WDT interrupt service routine. 
 * input : 
 *         none 
 * return: none
 ************************************************************************/
 void HAL_WDT_IRQHandler(WDT_HandleTypeDef* hwdt);
/************************************************************************
 * function   : HAL_WDT_Init
 * Description: WDT initiation. 
 * input : 
 *         pinit initiation parameters 
 * return: none
 ************************************************************************/
 void HAL_WDT_Init(WDT_HandleTypeDef* hwdt);
/************************************************************************
 * function   : WDT_Start
 * Description: WDT start
 * input : none
 *         
 * return: none
 ************************************************************************/
 void HAL_WDT_Start(WDT_HandleTypeDef* hwdt);
/************************************************************************
 * function   : WDT_Stop
 * Description: WDT stop
 * input : none
 *         
 * return: none
 ************************************************************************/
 void HAL_WDT_Stop(WDT_HandleTypeDef* hwdt);
/************************************************************************
 * function   : WDT_Int_Enable
 * Description: WDT int enable
 * input : none
 *         
 * return: none
 ************************************************************************/
 void HAL_WDT_Int_Enable(WDT_HandleTypeDef* hwdt);
/************************************************************************
 * function   : WDT_Int_Disable
 * Description: WDT int disable
 * input : none
 *         
 * return: none
 ************************************************************************/
 void HAL_WDT_Int_Disable(WDT_HandleTypeDef* hwdt);

#endif
