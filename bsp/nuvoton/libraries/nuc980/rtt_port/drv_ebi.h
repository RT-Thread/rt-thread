/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-3-5        Philo            First version
*
******************************************************************************/
#ifndef __DRV_EBI_H___
#define __DRV_EBI_H___

#include <rtdevice.h>
#include "NuMicro.h"

#define MAX_BANK    EBI_BANK2

/**
  * @brief      Initialize EBI for specify Bank
  *
  * @param[in]  u32Bank             Bank number for EBI. Valid values are:
  *                                     - \ref EBI_BANK0
  *                                     - \ref EBI_BANK1
  *                                     - \ref EBI_BANK2
  * @param[in]  u32DataWidth        Data bus width. Valid values are:
  *                                     - \ref EBI_BUSWIDTH_8BIT
  *                                     - \ref EBI_BUSWIDTH_16BIT
  * @param[in]  u32TimingClass      Default timing configuration. Valid values are:
  *                                     - \ref EBI_TIMING_FASTEST
  *                                     - \ref EBI_TIMING_VERYFAST
  *                                     - \ref EBI_TIMING_FAST
  *                                     - \ref EBI_TIMING_NORMAL
  *                                     - \ref EBI_TIMING_SLOW
  *                                     - \ref EBI_TIMING_VERYSLOW
  *                                     - \ref EBI_TIMING_SLOWEST
  * @param[in]  u32BusMode          Set EBI bus operate mode. Valid values are:
  *                                     - \ref EBI_OPMODE_NORMAL
  *                                     - \ref EBI_OPMODE_CACCESS
  * @param[in]  u32CSActiveLevel    CS is active High/Low. Valid values are:
  *                                     - \ref EBI_CS_ACTIVE_HIGH
  *                                     - \ref EBI_CS_ACTIVE_LOW
  *
  * @return     None
  *
  * @details    This function is used to open specify EBI bank with different bus width, timing setting and \n
  *             active level of CS pin to access EBI device.
  * @note       Write Buffer Enable(WBUFEN) and Extend Time Of ALE(TALE) are only available in EBI bank0 control register.
  */
rt_err_t nu_ebi_init(uint32_t u32Bank, uint32_t u32DataWidth, uint32_t u32TimingClass, uint32_t u32BusMode, uint32_t u32CSActiveLevel);

#endif // __DRV_EBI_H___
