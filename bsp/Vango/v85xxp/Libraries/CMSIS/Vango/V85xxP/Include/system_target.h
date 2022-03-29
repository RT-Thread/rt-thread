/**
  ******************************************************************************
  * @file    system_target.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   system source file.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __SYSTEM_TARGET_H
#define __SYSTEM_TARGET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "type_def.h"



extern void SystemInit(void);
extern void SystemUpdate(void);


#ifdef USE_TARGET_DRIVER
    #include "lib_conf.h"
#endif /* USE_TARGET_DRIVER */

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_TARGET_H */

/*********************************** END OF FILE ******************************/
