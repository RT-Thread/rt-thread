
/***********************************************************************
 * Filename    : HAL_IWDT.h
 * Description : IHAL WDT driver header file
 * Author(s)   : CWT
 * version     : V1.0
 * Modify date : 2020-04-17  
 ***********************************************************************/

#ifndef __HAL_IWDT_H__
#define __HAL_IWDT_H__

#include "ACM32Fxx_HAL.h"


/****************  Bit definition for IWDT register  ***********************/


/*----------------------macro definition------------------------*/
#define IWDT_ENABLE_COMMAND  (0xCCCCU)
#define IWDT_WRITE_ENABLE_COMMAND  (0x5555U)  
#define IWDT_WAKEUP_ENABLE_COMMAND  (0x6666U)  
#define IWDT_WAKEUP_DISABLE_COMMAND  (0x9999U) 
#define IWDT_RELOAD_COMMAND  (0xAAAAU)    

#define IWDT_RELOAD_MAX_VALUE  (0x0FFFU)  

/*----------------------type definition------------------------*/
typedef enum _IWDT_CLOCK_PRESCALER{       
    IWDT_CLOCK_PRESCALER_4   = 0, 
    IWDT_CLOCK_PRESCALER_8   = 1,    
    IWDT_CLOCK_PRESCALER_16  = 2,  
    IWDT_CLOCK_PRESCALER_32  = 3,  
    IWDT_CLOCK_PRESCALER_64  = 4,  
    IWDT_CLOCK_PRESCALER_128 = 5,   
    IWDT_CLOCK_PRESCALER_256 = 6,  
}IWDT_CLOCK_PRESCALER;  

typedef struct
{
    uint32_t Prescaler;                            
    uint32_t Reload;                              
    uint32_t Window;     
    uint32_t Wakeup;  
} IWDT_InitTypeDef;

typedef struct
{
    IWDT_TypeDef                 *Instance;  /*!< Register base address    */  
    IWDT_InitTypeDef             Init;       /*!< IWDT required parameters */
} IWDT_HandleTypeDef;


 HAL_StatusTypeDef HAL_IWDT_Init(IWDT_HandleTypeDef * hidt);  
 HAL_StatusTypeDef HAL_IWDT_Kick_Watchdog_Wait_For_Done(IWDT_HandleTypeDef * hidt);   
#endif
