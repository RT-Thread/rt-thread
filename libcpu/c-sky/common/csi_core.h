/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     csi_core.h
 * @brief    CSI Core Layer Header File
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _CORE_H_
#define _CORE_H_

#include <stdint.h>
#include "csi_gcc.h"

#ifdef __cplusplus
extern "C" {
#endif


/* ##################################    NVIC function  ############################################ */

/**
  \brief   initialize the NVIC interrupt controller
  \param [in]      prio_bits  the priority bits of NVIC interrupt controller.
 */
void drv_nvic_init(uint32_t prio_bits);

/**
  \brief   Enable External Interrupt
  \details Enables a device-specific interrupt in the NVIC interrupt controller.
  \param [in]      irq_num  External interrupt number. Value cannot be negative.
 */
void drv_nvic_enable_irq(int32_t irq_num);
/**
  \brief   Disable External Interrupt
  \details Disables a device-specific interrupt in the NVIC interrupt controller.
  \param [in]      irq_num  External interrupt number. Value cannot be negative.
 */
void drv_nvic_disable_irq(int32_t irq_num);

/**
  \brief   Get Pending Interrupt
  \details Reads the pending register in the NVIC and returns the pending bit for the specified interrupt.
  \param [in]      irq_num  Interrupt number.
  \return             0  Interrupt status is not pending.
  \return             1  Interrupt status is pending.
 */
uint32_t drv_nvic_get_pending_irq(int32_t irq_num);

/**
  \brief   Set Pending Interrupt
  \details Sets the pending bit of an external interrupt.
  \param [in]      irq_num  Interrupt number. Value cannot be negative.
 */
void drv_nvic_set_pending_irq(int32_t irq_num);

/**
  \brief   Clear Pending Interrupt
  \details Clears the pending bit of an external interrupt.
  \param [in]      irq_num  External interrupt number. Value cannot be negative.
 */
void drv_nvic_clear_pending_irq(int32_t irq_num);

/**
  \brief   Get Active Interrupt
  \details Reads the active register in the NVIC and returns the active bit for the device specific interrupt.
  \param [in]      irq_num  Device specific interrupt number.
  \return             0  Interrupt status is not active.
  \return             1  Interrupt status is active.
  \note    irq_num must not be negative.
 */
uint32_t drv_nvic_get_active(int32_t irq_num);

/**
 \brief   Set Interrupt Priority
 \details Sets the priority of an interrupt.
 \note    The priority cannot be set for every core interrupt.
 \param [in]      irq_num  Interrupt number.
 \param [in]  priority  Priority to set.
*/
void drv_nvic_set_prio(int32_t irq_num, uint32_t priority);
/**
  \brief   Get Interrupt Priority
  \details Reads the priority of an interrupt.
           The interrupt number can be positive to specify an external (device specific) interrupt,
           or negative to specify an internal (core) interrupt.
  \param [in]   irq_num  Interrupt number.
  \return             Interrupt Priority.
                      Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
uint32_t drv_nvic_get_prio(int32_t irq_num);

/*@} end of CSI_Core_NVICFunctions */


/* ##########################  Cache functions  #################################### */

/**
  \brief   Enable I-Cache
  \details Turns on I-Cache
  */
void drv_icache_enable(void);

/**
  \brief   Disable I-Cache
  \details Turns off I-Cache
  */
void drv_icache_disable(void);

/**
  \brief   Invalidate I-Cache
  \details Invalidates I-Cache
  */
void drv_icache_invalid(void);

/**
  \brief   Enable D-Cache
  \details Turns on D-Cache
  \note    I-Cache also turns on.
  */
void drv_dcache_enable(void);

/**
  \brief   Disable D-Cache
  \details Turns off D-Cache
  \note    I-Cache also turns off.
  */
void drv_dcache_disable(void);

/**
  \brief   Invalidate D-Cache
  \details Invalidates D-Cache
  \note    I-Cache also invalid
  */
void drv_dcache_invalid(void);

/**
  \brief   Clean D-Cache
  \details Cleans D-Cache
  \note    I-Cache also cleans
  */
void drv_dcache_clean(void);

/**
  \brief   Clean & Invalidate D-Cache
  \details Cleans and Invalidates D-Cache
  \note    I-Cache also flush.
  */
void drv_dcache_clean_invalid(void);


/**
  \brief   D-Cache Invalidate by address
  \details Invalidates D-Cache for the given address
  \param[in]   addr    address (aligned to 16-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
void drv_dcache_invalid_range(uint32_t *addr, int32_t dsize);

/**
  \brief   D-Cache Clean by address
  \details Cleans D-Cache for the given address
  \param[in]   addr    address (aligned to 16-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
void drv_dcache_clean_range(uint32_t *addr, int32_t dsize);

/**
  \brief   D-Cache Clean and Invalidate by address
  \details Cleans and invalidates D_Cache for the given address
  \param[in]   addr    address (aligned to 16-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
void drv_dcache_clean_invalid_range(uint32_t *addr, int32_t dsize);

/**
  \brief   setup cacheable range Cache
  \details setup Cache range
  */
void drv_cache_set_range(uint32_t index, uint32_t baseAddr, uint32_t size, uint32_t enable);

/**
  \brief   Enable cache profile
  \details Turns on Cache profile
  */
void drv_cache_enable_profile(void);

/**
  \brief   Disable cache profile
  \details Turns off Cache profile
  */
void drv_cache_disable_profile(void);
/**
  \brief   Reset cache profile
  \details Reset Cache profile
  */
void drv_cache_reset_profile(void);

/**
  \brief   cache access times
  \details Cache access times
  \note    every 256 access add 1.
  */
uint32_t drv_cache_get_access_time(void);

/**
  \brief   cache miss times
  \details Cache miss times
  \note    every 256 miss add 1.
  */
uint32_t drv_cache_get_miss_time(void);

/* ##################################    SysTick function  ############################################ */

/**
  \brief   CORE timer Configuration
  \details Initializes the System Timer and its interrupt, and starts the System Tick Timer.
           Counter is in free running mode to generate periodic interrupts.
  \param [in]  ticks  Number of ticks between two interrupts.
  \param [in]  irq_num   core timer Interrupt number.
  \return          0  Function succeeded.
  \return          1  Function failed.
  \note    When the variable <b>__Vendor_SysTickConfig</b> is set to 1, then the
           function <b>SysTick_Config</b> is not included. In this case, the file <b><i>device</i>.h</b>
           must contain a vendor-specific implementation of this function.
 */
uint32_t drv_coret_config(uint32_t ticks, int32_t irq_num);

#ifdef __cplusplus
}
#endif

#endif /* _CORE_H_ */
