/**
  ******************************************************************************
  * @file    lib_CodeRAM.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   Codes executed in SRAM.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __LIB_CODERAM_H
#define __LIB_CODERAM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "target.h"   

#ifndef __GNUC__

#ifdef __ICCARM__          /* EWARM */
  #define __RAM_FUNC       __ramfunc
#endif

#ifdef __CC_ARM            /* MDK-ARM */
  #define __RAM_FUNC       __attribute__((used))
#endif

/* Exported Functions ------------------------------------------------------- */

__RAM_FUNC void PMU_EnterIdle_FlashDSTB(void);

#endif /* __GNUC__ */

#ifdef __cplusplus
}
#endif

#endif /* __LIB_CODERAM_H */

/*********************************** END OF FILE ******************************/
