/**
  ******************************************************************************
  * @file    lib_misc.h 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   MISC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_MISC_H
#define __LIB_MISC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
   
//FlagMask
#define MISC_FLAG_LOCKUP    MISC_SRAMINT_LOCKUP
#define MISC_FLAG_PIAC      MISC_SRAMINT_PIAC
#define MISC_FLAG_HIAC      MISC_SRAMINT_HIAC
#define MISC_FLAG_PERR      MISC_SRAMINT_PERR
#define MISC_FLAG_Msk      (MISC_FLAG_LOCKUP | MISC_FLAG_PIAC | MISC_FLAG_HIAC | MISC_FLAG_PERR)  
  
//MISC interrupt
#define MISC_INT_LOCK       MISC_SRAMINIT_LOCKIE
#define MISC_INT_PIAC       MISC_SRAMINIT_PIACIE
#define MISC_INT_HIAC       MISC_SRAMINIT_HIACIE
#define MISC_INT_PERR       MISC_SRAMINIT_PERRIE
#define MISC_INT_Msk       (MISC_INT_LOCK | MISC_INT_PIAC | MISC_INT_HIAC | MISC_INT_PERR) 

//IR
#define MISC_IREN_TX0       MISC_IREN_UART0
#define MISC_IREN_TX1       MISC_IREN_UART1
#define MISC_IREN_TX2       MISC_IREN_UART2
#define MISC_IREN_TX3       MISC_IREN_UART3
#define MISC_IREN_TX4       MISC_IREN_UART4
#define MISC_IREN_TX5       MISC_IREN_UART5
#define MISC_IREN_Msk      (0x3FUL)   

/* Private macros ------------------------------------------------------------*/
#define IS_MISC_FLAGR(__FLAGR__) (((__FLAGR__) == MISC_FLAG_LOCKUP) ||\
                                  ((__FLAGR__) == MISC_FLAG_PIAC)   ||\
                                  ((__FLAGR__) == MISC_FLAG_HIAC)   ||\
                                  ((__FLAGR__) == MISC_FLAG_PERR))

#define IS_MISC_FLAGC(__FLAGC__)  ((((__FLAGC__) & MISC_FLAG_Msk) != 0U) &&\
                                   (((__FLAGC__) & ~MISC_FLAG_Msk) == 0U))

#define IS_MISC_INT(__INT__)  ((((__INT__) & MISC_INT_Msk) != 0U) &&\
                               (((__INT__) &~MISC_INT_Msk) == 0U))

#define IS_MISC_IREN(__IREN__)  ((((__IREN__) & MISC_IREN_Msk) != 0U) &&\
                                 (((__IREN__) & ~MISC_IREN_Msk) == 0U))

/* Exported Functions ------------------------------------------------------- */
uint8_t MISC_GetFlag(uint32_t FlagMask);
void MISC_ClearFlag(uint32_t FlagMask);
void MISC_INTConfig(uint32_t INTMask, uint32_t NewState);
void MISC_SRAMParityCmd(uint32_t NewState);
uint32_t MISC_GetSRAMPEAddr(void);
uint32_t MISC_GetAPBErrAddr(void);
uint32_t MISC_GetAHBErrAddr(void);
void MISC_IRCmd(uint32_t IRx, uint32_t NewState);
void MISC_IRDutyConfig(uint16_t DutyHigh, uint16_t DutyLow);
void MISC_HardFaultCmd(uint32_t NewState);
void MISC_LockResetCmd(uint32_t NewState);
void MISC_IRQLATConfig(uint8_t Latency);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_MISC_H */

/*********************************** END OF FILE ******************************/
