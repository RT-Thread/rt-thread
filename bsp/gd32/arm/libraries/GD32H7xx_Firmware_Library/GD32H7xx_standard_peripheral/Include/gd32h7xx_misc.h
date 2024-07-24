/*!
    \file    gd32h7xx_misc.h
    \brief   definitions for the MISC

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef GD32H7XX_MISC_H
#define GD32H7XX_MISC_H

#include "gd32h7xx.h"

#if (__MPU_PRESENT == 1)

/* MPU region init parameter struct definitions */
typedef struct
{
    uint32_t region_base_address;    /*!< region base address */
    uint8_t region_number;           /*!< region number */
    uint8_t region_size;             /*!< region size */
    uint8_t subregion_disable;       /*!< subregion disable */
    uint8_t tex_type;                /*!< tex type */
    uint8_t access_permission;       /*!< access permissions(AP) field */
    uint8_t access_shareable;        /*!< shareable */
    uint8_t access_cacheable;        /*!< cacheable */
    uint8_t access_bufferable;       /*!< bufferable */
    uint8_t instruction_exec;        /*!< execute never */
}mpu_region_init_struct;

#endif /* __MPU_PRESENT */

/* constants definitions */
/* set the RAM and FLASH base address */
#define NVIC_VECTTAB_RAM                ((uint32_t)0x24000000U)   /*!< RAM base address */
#define NVIC_VECTTAB_FLASH              ((uint32_t)0x08000000U)   /*!< Flash base address */

/* set the NVIC vector table offset mask */
#define NVIC_VECTTAB_OFFSET_MASK        ((uint32_t)0x1FFFFF80U)

/* the register key mask, if you want to do the write operation, you should write 0x5FA to VECTKEY bits */
#define NVIC_AIRCR_VECTKEY_MASK         ((uint32_t)0x05FA0000U)

/* priority group - define the pre-emption priority and the subpriority */
#define NVIC_PRIGROUP_PRE0_SUB4         ((uint32_t)0x00000700U)   /*!< 0 bits for pre-emption priority, 4 bits for subpriority */
#define NVIC_PRIGROUP_PRE1_SUB3         ((uint32_t)0x00000600U)   /*!< 1 bits for pre-emption priority, 3 bits for subpriority */
#define NVIC_PRIGROUP_PRE2_SUB2         ((uint32_t)0x00000500U)   /*!< 2 bits for pre-emption priority, 2 bits for subpriority */
#define NVIC_PRIGROUP_PRE3_SUB1         ((uint32_t)0x00000400U)   /*!< 3 bits for pre-emption priority, 1 bits for subpriority */
#define NVIC_PRIGROUP_PRE4_SUB0         ((uint32_t)0x00000300U)   /*!< 4 bits for pre-emption priority, 0 bits for subpriority */

/* choose the method to enter or exit the low power mode */
#define SCB_SCR_SLEEPONEXIT             ((uint8_t)0x02U)          /*!< choose the system whether enter low power mode by exiting from ISR */
#define SCB_SCR_SLEEPDEEP               ((uint8_t)0x04U)          /*!< choose the system enter the DEEPSLEEP mode or SLEEP mode */
#define SCB_SCR_SEVONPEND               ((uint8_t)0x10U)          /*!< choose the interrupt source that can wake up the low power mode */

#define SCB_LPM_SLEEP_EXIT_ISR          SCB_SCR_SLEEPONEXIT       /*!< low power mode by exiting from ISR */
#define SCB_LPM_DEEPSLEEP               SCB_SCR_SLEEPDEEP         /*!< DEEPSLEEP mode or SLEEP mode */
#define SCB_LPM_WAKE_BY_ALL_INT         SCB_SCR_SEVONPEND         /*!< wakeup by all interrupt */

/* choose the systick clock source */
#define SYSTICK_CLKSOURCE_CKSYS_DIV2    ((uint32_t)0xFFFFFFFBU)   /*!< systick clock source is from CK_SYS/2 */
#define SYSTICK_CLKSOURCE_CKSYS         ((uint32_t)0x00000004U)   /*!< systick clock source is from CK_SYS */

#if (__MPU_PRESENT == 1)

#define MPU_REGION_NUMBER0              ((uint8_t)0x00U)          /*!< MPU region number 0 */
#define MPU_REGION_NUMBER1              ((uint8_t)0x01U)          /*!< MPU region number 1 */
#define MPU_REGION_NUMBER2              ((uint8_t)0x02U)          /*!< MPU region number 2 */
#define MPU_REGION_NUMBER3              ((uint8_t)0x03U)          /*!< MPU region number 3 */
#define MPU_REGION_NUMBER4              ((uint8_t)0x04U)          /*!< MPU region number 4 */
#define MPU_REGION_NUMBER5              ((uint8_t)0x05U)          /*!< MPU region number 5 */
#define MPU_REGION_NUMBER6              ((uint8_t)0x06U)          /*!< MPU region number 6 */
#define MPU_REGION_NUMBER7              ((uint8_t)0x07U)          /*!< MPU region number 7 */
#define MPU_REGION_NUMBER8              ((uint8_t)0x08U)          /*!< MPU region number 8 */
#define MPU_REGION_NUMBER9              ((uint8_t)0x09U)          /*!< MPU region number 9 */
#define MPU_REGION_NUMBER10             ((uint8_t)0x0AU)          /*!< MPU region number 10 */
#define MPU_REGION_NUMBER11             ((uint8_t)0x0BU)          /*!< MPU region number 11 */
#define MPU_REGION_NUMBER12             ((uint8_t)0x0CU)          /*!< MPU region number 12 */
#define MPU_REGION_NUMBER13             ((uint8_t)0x0DU)          /*!< MPU region number 13 */
#define MPU_REGION_NUMBER14             ((uint8_t)0x0EU)          /*!< MPU region number 14 */
#define MPU_REGION_NUMBER15             ((uint8_t)0x0FU)          /*!< MPU region number 15 */

#define MPU_REGION_SIZE_32B             ARM_MPU_REGION_SIZE_32B   /*!< MPU region size is 32 bytes, the smallest supported region size is 32 bytes */
#define MPU_REGION_SIZE_64B             ARM_MPU_REGION_SIZE_64B   /*!< MPU region size is 64 bytes */
#define MPU_REGION_SIZE_128B            ARM_MPU_REGION_SIZE_128B  /*!< MPU region size is 128 bytes */
#define MPU_REGION_SIZE_256B            ARM_MPU_REGION_SIZE_256B  /*!< MPU region size is 256 bytes */
#define MPU_REGION_SIZE_512B            ARM_MPU_REGION_SIZE_512B  /*!< MPU region size is 512 bytes */
#define MPU_REGION_SIZE_1KB             ARM_MPU_REGION_SIZE_1KB   /*!< MPU region size is 1K bytes */
#define MPU_REGION_SIZE_2KB             ARM_MPU_REGION_SIZE_2KB   /*!< MPU region size is 2K bytes */
#define MPU_REGION_SIZE_4KB             ARM_MPU_REGION_SIZE_4KB   /*!< MPU region size is 4K bytes */
#define MPU_REGION_SIZE_8KB             ARM_MPU_REGION_SIZE_8KB   /*!< MPU region size is 8K bytes */
#define MPU_REGION_SIZE_16KB            ARM_MPU_REGION_SIZE_16KB  /*!< MPU region size is 16K bytes */
#define MPU_REGION_SIZE_32KB            ARM_MPU_REGION_SIZE_32KB  /*!< MPU region size is 32K bytes */
#define MPU_REGION_SIZE_64KB            ARM_MPU_REGION_SIZE_64KB  /*!< MPU region size is 64K bytes */
#define MPU_REGION_SIZE_128KB           ARM_MPU_REGION_SIZE_128KB /*!< MPU region size is 128K bytes */
#define MPU_REGION_SIZE_256KB           ARM_MPU_REGION_SIZE_256KB /*!< MPU region size is 256K bytes */
#define MPU_REGION_SIZE_512KB           ARM_MPU_REGION_SIZE_512KB /*!< MPU region size is 512K bytes */
#define MPU_REGION_SIZE_1MB             ARM_MPU_REGION_SIZE_1MB   /*!< MPU region size is 1M bytes */
#define MPU_REGION_SIZE_2MB             ARM_MPU_REGION_SIZE_2MB   /*!< MPU region size is 2M bytes */
#define MPU_REGION_SIZE_4MB             ARM_MPU_REGION_SIZE_4MB   /*!< MPU region size is 4M bytes */
#define MPU_REGION_SIZE_8MB             ARM_MPU_REGION_SIZE_8MB   /*!< MPU region size is 8M bytes */
#define MPU_REGION_SIZE_16MB            ARM_MPU_REGION_SIZE_16MB  /*!< MPU region size is 16M bytes */
#define MPU_REGION_SIZE_32MB            ARM_MPU_REGION_SIZE_32MB  /*!< MPU region size is 32M bytes */
#define MPU_REGION_SIZE_64MB            ARM_MPU_REGION_SIZE_64MB  /*!< MPU region size is 64M bytes */
#define MPU_REGION_SIZE_128MB           ARM_MPU_REGION_SIZE_128MB /*!< MPU region size is 128M bytes */
#define MPU_REGION_SIZE_256MB           ARM_MPU_REGION_SIZE_256MB /*!< MPU region size is 256M bytes */
#define MPU_REGION_SIZE_512MB           ARM_MPU_REGION_SIZE_512MB /*!< MPU region size is 512M bytes */
#define MPU_REGION_SIZE_1GB             ARM_MPU_REGION_SIZE_1GB   /*!< MPU region size is 1G bytes */
#define MPU_REGION_SIZE_2GB             ARM_MPU_REGION_SIZE_2GB   /*!< MPU region size is 2G bytes */
#define MPU_REGION_SIZE_4GB             ARM_MPU_REGION_SIZE_4GB   /*!< MPU region size is 4G bytes */

#define MPU_SUBREGION_ENABLE            ((uint8_t)0x00U)          /*!< Subregion enable */
#define MPU_SUBREGION_DISABLE           ((uint8_t)0x01U)          /*!< Subregion disable */

#define MPU_TEX_TYPE0                   ((uint8_t)0x00U)          /*!< MPU TEX type 0 */
#define MPU_TEX_TYPE1                   ((uint8_t)0x01U)          /*!< MPU TEX type 1 */
#define MPU_TEX_TYPE2                   ((uint8_t)0x02U)          /*!< MPU TEX type 2 */

#define MPU_AP_NO_ACCESS                ARM_MPU_AP_NONE           /*!< MPU access permission no access */
#define MPU_AP_PRIV_RW                  ARM_MPU_AP_PRIV           /*!< MPU access permission privileged access only */
#define MPU_AP_PRIV_RW_UNPRIV_RO        ARM_MPU_AP_URO            /*!< MPU access permission unprivileged access read-only */
#define MPU_AP_FULL_ACCESS              ARM_MPU_AP_FULL           /*!< MPU access permission full access */
#define MPU_AP_PRIV_RO                  ARM_MPU_AP_PRO            /*!< MPU access permission privileged access read-only */
#define MPU_AP_PRIV_UNPRIV_RO           ARM_MPU_AP_RO             /*!< MPU access permission privileged and unprivileged read-only access */

#define MPU_ACCESS_SHAREABLE            ((uint8_t)0x01U)          /*!< MPU access shareable */
#define MPU_ACCESS_NON_SHAREABLE        ((uint8_t)0x00U)          /*!< MPU access non-shareable */

#define MPU_ACCESS_CACHEABLE            ((uint8_t)0x01U)          /*!< MPU access cacheable */
#define MPU_ACCESS_NON_CACHEABLE        ((uint8_t)0x00U)          /*!< MPU access non-cacheable */

#define MPU_ACCESS_BUFFERABLE           ((uint8_t)0x01U)          /*!< MPU access bufferable */
#define MPU_ACCESS_NON_BUFFERABLE       ((uint8_t)0x00U)          /*!< MPU access non-bufferable */

#define MPU_INSTRUCTION_EXEC_PERMIT     ((uint8_t)0x00U)          /*!< execution of an instruction fetched from this region permitted */
#define MPU_INSTRUCTION_EXEC_NOT_PERMIT ((uint8_t)0x01U)          /*!< execution of an instruction fetched from this region not permitted */

#define MPU_MODE_HFNMI_PRIVDEF_NONE     ((uint32_t)0x00000000U)   /*!< HFNMIENA and PRIVDEFENA are 0 */
#define MPU_MODE_HARDFAULT_NMI          MPU_CTRL_HFNMIENA_Msk     /*!< use the MPU for memory accesses by HardFault and NMI handlers only */
#define MPU_MODE_PRIV_DEFAULT           MPU_CTRL_PRIVDEFENA_Msk   /*!< enables the default memory map as a background region for privileged access only */
#define MPU_MODE_HFNMI_PRIVDEF          ((uint32_t)MPU_CTRL_HFNMIENA_Msk | MPU_CTRL_PRIVDEFENA_Msk) /*!< HFNMIENA and PRIVDEFENA are 1 */

#endif /* __MPU_PRESENT */

/* function declarations */
/* set the priority group */
void nvic_priority_group_set(uint32_t nvic_prigroup);

/* enable NVIC interrupt request */
void nvic_irq_enable(uint8_t nvic_irq, uint8_t nvic_irq_pre_priority, uint8_t nvic_irq_sub_priority);
/* disable NVIC interrupt request */
void nvic_irq_disable(uint8_t nvic_irq);

/* set the NVIC vector table base address */
void nvic_vector_table_set(uint32_t nvic_vict_tab, uint32_t offset);

/* set the state of the low power mode */
void system_lowpower_set(uint8_t lowpower_mode);
/* reset the state of the low power mode */
void system_lowpower_reset(uint8_t lowpower_mode);

/* set the systick clock source */
void systick_clksource_set(uint32_t systick_clksource);

#if (__MPU_PRESENT == 1)
/* initialize mpu_region_init_struct with the default values */
void mpu_region_struct_para_init(mpu_region_init_struct *mpu_init_struct);
/* configure the MPU region */
void mpu_region_config(mpu_region_init_struct *mpu_init_struct);
/* enable the MPU region */
void mpu_region_enable(void);
#endif /* __MPU_PRESENT */

#endif /* GD32H7XX_MISC_H */
