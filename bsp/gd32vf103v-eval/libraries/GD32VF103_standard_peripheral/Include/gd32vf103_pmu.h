/*!
    \file    gd32vf103_pmu.h
    \brief   definitions for the PMU

    \version 2019-6-5, V1.0.0, firmware for GD32VF103
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

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

#ifndef GD32VF103_PMU_H
#define GD32VF103_PMU_H

#include "gd32vf103.h"

/* PMU definitions */
#define PMU                           PMU_BASE                 /*!< PMU base address */

/* registers definitions */
#define PMU_CTL                       REG32((PMU) + 0x00U)     /*!< PMU control register */
#define PMU_CS                        REG32((PMU) + 0x04U)     /*!< PMU control and status register */

/* bits definitions */
/* PMU_CTL */
#define PMU_CTL_LDOLP                 BIT(0)                   /*!< LDO low power mode */
#define PMU_CTL_STBMOD                BIT(1)                   /*!< standby mode */
#define PMU_CTL_WURST                 BIT(2)                   /*!< wakeup flag reset */
#define PMU_CTL_STBRST                BIT(3)                   /*!< standby flag reset */
#define PMU_CTL_LVDEN                 BIT(4)                   /*!< low voltage detector enable */
#define PMU_CTL_LVDT                  BITS(5,7)                /*!< low voltage detector threshold */
#define PMU_CTL_BKPWEN                BIT(8)                   /*!< backup domain write enable */

/* PMU_CS */
#define PMU_CS_WUF                    BIT(0)                   /*!< wakeup flag */
#define PMU_CS_STBF                   BIT(1)                   /*!< standby flag */
#define PMU_CS_LVDF                   BIT(2)                   /*!< low voltage detector status flag */
#define PMU_CS_WUPEN                  BIT(8)                   /*!< wakeup pin enable */

/* constants definitions */
/* PMU low voltage detector threshold definitions */
#define CTL_LVDT(regval)              (BITS(5,7)&((uint32_t)(regval) << 5))
#define PMU_LVDT_0                    CTL_LVDT(0)              /*!< voltage threshold is 2.2V */
#define PMU_LVDT_1                    CTL_LVDT(1)              /*!< voltage threshold is 2.3V */
#define PMU_LVDT_2                    CTL_LVDT(2)              /*!< voltage threshold is 2.4V */
#define PMU_LVDT_3                    CTL_LVDT(3)              /*!< voltage threshold is 2.5V */
#define PMU_LVDT_4                    CTL_LVDT(4)              /*!< voltage threshold is 2.6V */
#define PMU_LVDT_5                    CTL_LVDT(5)              /*!< voltage threshold is 2.7V */
#define PMU_LVDT_6                    CTL_LVDT(6)              /*!< voltage threshold is 2.8V */
#define PMU_LVDT_7                    CTL_LVDT(7)              /*!< voltage threshold is 2.9V */

/* PMU flag definitions */
#define PMU_FLAG_WAKEUP               PMU_CS_WUF               /*!< wakeup flag status */
#define PMU_FLAG_STANDBY              PMU_CS_STBF              /*!< standby flag status */
#define PMU_FLAG_LVD                  PMU_CS_LVDF              /*!< lvd flag status */

/* PMU ldo definitions */
#define PMU_LDO_NORMAL                ((uint32_t)0x00000000U)  /*!< LDO normal work when PMU enter deepsleep mode */
#define PMU_LDO_LOWPOWER              PMU_CTL_LDOLP            /*!< LDO work at low power status when PMU enter deepsleep mode */

/* PMU flag reset definitions */
#define PMU_FLAG_RESET_WAKEUP         ((uint8_t)0x00U)         /*!< wakeup flag reset */
#define PMU_FLAG_RESET_STANDBY        ((uint8_t)0x01U)         /*!< standby flag reset */

/* PMU command constants definitions */
#define WFI_CMD                       ((uint8_t)0x00U)         /*!< use WFI command */
#define WFE_CMD                       ((uint8_t)0x01U)         /*!< use WFE command */

/* function declarations */
/* reset PMU registers */
void pmu_deinit(void);

/* select low voltage detector threshold */
void pmu_lvd_select(uint32_t lvdt_n);
/* disable PMU lvd */
void pmu_lvd_disable(void);

/* set PMU mode */
/* PMU work at sleep mode */
void pmu_to_sleepmode(uint8_t sleepmodecmd);
/* PMU work at deepsleep mode */
void pmu_to_deepsleepmode(uint32_t ldo, uint8_t deepsleepmodecmd);
/* PMU work at standby mode */
void pmu_to_standbymode(uint8_t standbymodecmd);
/* enable PMU wakeup pin */
void pmu_wakeup_pin_enable(void);
/* disable PMU wakeup pin */
void pmu_wakeup_pin_disable(void);

/* backup related functions */
/* enable write access to the registers in backup domain */
void pmu_backup_write_enable(void);
/* disable write access to the registers in backup domain */
void pmu_backup_write_disable(void);

/* flag functions */
/* get flag state */
FlagStatus pmu_flag_get(uint32_t flag);
/* clear flag bit */
void pmu_flag_clear(uint32_t flag_reset);

#endif /* GD32VF103_PMU_H */
