/**
  ******************************************************************************
  * @file    lib_wdt.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   WDT library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_WDT_H
#define __LIB_WDT_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"


#define WDT_2_SECS            (0x0U << PMU_WDTEN_WDTSEL_Pos)
#define WDT_4_SECS            (0x1U << PMU_WDTEN_WDTSEL_Pos)
#define WDT_8_SECS            (0x2U << PMU_WDTEN_WDTSEL_Pos)
#define WDT_16_SECS           (0x3U << PMU_WDTEN_WDTSEL_Pos)

/* Private macros ------------------------------------------------------------*/
#define IS_WDT_PERIOD(__PERIOD__)  (((__PERIOD__) == WDT_2_SECS)   ||\
                                    ((__PERIOD__) == WDT_4_SECS)   ||\
                                    ((__PERIOD__) == WDT_8_SECS) ||\
                                    ((__PERIOD__) == WDT_16_SECS))

/* Exported Functions ------------------------------------------------------- */
void WDT_Enable(void);
void WDT_Disable(void);
void WDT_Clear(void);
void WDT_SetPeriod(uint32_t period);
uint16_t WDT_GetCounterValue(void);
   
#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_WDT_H */

/*********************************** END OF FILE ******************************/
