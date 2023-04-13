/**
    *****************************************************************************
    * @file     system_cmem7.h
    *
    * @brief    CMEM7 system initial header file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#ifndef __SYSTEM_CMEM7_H
#define __SYSTEM_CMEM7_H

#ifdef __cplusplus
 extern "C" {
#endif

/**
  * @brief  Setup the microcontroller system.
  * @note   This function should be used only after reset.
    * @param  None
  * @retval None
    */
void SystemInit(void);

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_CMEM7_H */

