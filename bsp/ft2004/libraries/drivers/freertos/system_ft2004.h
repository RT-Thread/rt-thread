/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 15:40:28
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


#ifndef SYSTEM_FT2004_H
#define SYSTEM_FT2004_H

#include "ft_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void SystemInit(void);
    void SystemInitIrqTable(void);
    void SystemIrqHandler(u32 giccIar);
    void SystemSetupSystick(u32 tickRateHz, void *tickHandler, u32 intPriority);
    void SystemClearSystickFlag(void);
    u32 SystemGetIRQNestingLevel(void);
    void vAssertCalled(const char *pcFile, unsigned long ulLine);

#ifdef __cplusplus
}
#endif

#endif // !
