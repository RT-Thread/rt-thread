/*!
    \file  gd32e230_pmu.h
    \brief definitions for the PMU
    
    \version 2018-06-19, V1.0.0, firmware for GD32E230
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

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

#ifndef GD32E230_PMU_H
#define GD32E230_PMU_H

#include "gd32e230.h"

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
#define PMU_CTL_LDOVS_0               BIT(14)                  /*!< LDO output voltage select */
#define PMU_CTL_LDOVS_1               BIT(15)                  /*!< LDO output voltage select */
#define PMU_CTL_LDOVS                 BITS(14,15)              /*!< LDO output voltage select */

/* PMU_CS */
#define PMU_CS_WUF                    BIT(0)                   /*!< wakeup flag */
#define PMU_CS_STBF                   BIT(1)                   /*!< standby flag */
#define PMU_CS_LVDF                   BIT(2)                   /*!< low voltage detector status flag */
#define PMU_CS_WUPEN0                 BIT(8)                   /*!< wakeup pin enable */
#define PMU_CS_WUPEN1                 BIT(9)                   /*!< wakeup pin enable */
#define PMU_CS_WUPEN5                 BIT(13)                  /*!< wakeup pin enable */
#define PMU_CS_WUPEN6                 BIT(14)                  /*!< wakeup pin enable */

/* constants definitions */
/* PMU low voltage detector threshold definitions */
#define CTL_LVDT(regval)              (BITS(5,7)&((uint32_t)(regval)<<5))
#define PMU_LVDT_0                    CTL_LVDT(0)              /*!< voltage threshold is 2.1V */
#define PMU_LVDT_1                    CTL_LVDT(1)              /*!< voltage threshold is 2.3V */
#define PMU_LVDT_2                    CTL_LVDT(2)              /*!< voltage threshold is 2.4V */
#define PMU_LVDT_3                    CTL_LVDT(3)              /*!< voltage threshold is 2.6V */
#define PMU_LVDT_4                    CTL_LVDT(4)              /*!< voltage threshold is 2.7V */
#define PMU_LVDT_5                    CTL_LVDT(5)              /*!< voltage threshold is 2.9V */
#define PMU_LVDT_6                    CTL_LVDT(6)              /*!< voltage threshold is 3.0V */
#define PMU_LVDT_7                    CTL_LVDT(7)              /*!< voltage threshold is 3.1V */

/* PMU LDO output voltage select definitions */
#define CTL_LDOVS(regval)             (BITS(14,15)&((uint32_t)(regval)<<14))
#define PMU_LDOVS_HIGH                CTL_LDOVS(1)             /*!< LDO output voltage high mode */
#define PMU_LDOVS_LOW                 CTL_LDOVS(2)             /*!< LDO output voltage low mode */

/* PMU ldo definitions */
#define PMU_LDO_NORMAL                ((uint32_t)0x00000000U)  /*!< LDO operates normally when PMU enter deepsleep mode */
#define PMU_LDO_LOWPOWER              PMU_CTL_LDOLP            /*!< LDO work at low power status when PMU enter deepsleep mode */

/* PMU flag definitions */
#define PMU_FLAG_WAKEUP               PMU_CS_WUF               /*!< wakeup flag status */
#define PMU_FLAG_STANDBY              PMU_CS_STBF              /*!< standby flag status */
#define PMU_FLAG_LVD                  PMU_CS_LVDF              /*!< LVD flag status */

/* PMU WKUP pin definitions */
#define PMU_WAKEUP_PIN0               PMU_CS_WUPEN0            /*!< WKUP Pin 0 (PA0) enable */
#define PMU_WAKEUP_PIN1               PMU_CS_WUPEN1            /*!< WKUP Pin 1 (PC13) enable */
#define PMU_WAKEUP_PIN5               PMU_CS_WUPEN5            /*!< WKUP Pin 5 (PB5) enable */
#define PMU_WAKEUP_PIN6               PMU_CS_WUPEN6            /*!< WKUP Pin 6 (PB15) enable */

/* PMU flag reset definitions */
#define PMU_FLAG_RESET_WAKEUP         PMU_CTL_WURST            /*!< wakeup flag reset */
#define PMU_FLAG_RESET_STANDBY        PMU_CTL_STBRST           /*!< standby flag reset */

/* PMU command constants definitions */
#define WFI_CMD                       ((uint8_t)0x00U)         /*!< use WFI command */
#define WFE_CMD                       ((uint8_t)0x01U)         /*!< use WFE command */

/* function declarations */
/* reset PMU registers */
void pmu_deinit(void);

/* select low voltage detector threshold */
void pmu_lvd_select(uint32_t lvdt_n);
/* select LDO output voltage */
void pmu_ldo_output_select(uint32_t ldo_output);
/* disable PMU lvd */
void pmu_lvd_disable(void);

/* set PMU mode */
/* PMU work in sleep mode */
void pmu_to_sleepmode(uint8_t sleepmodecmd);
/* PMU work in deepsleep mode */
void pmu_to_deepsleepmode(uint32_t ldo, uint8_t deepsleepmodecmd);
/* PMU work in standby mode */
void pmu_to_standbymode(uint8_t standbymodecmd);
/* enable PMU wakeup pin */
void pmu_wakeup_pin_enable(uint32_t wakeup_pin);
/* disable PMU wakeup pin */
void pmu_wakeup_pin_disable(uint32_t wakeup_pin);

/* backup related functions */
/* enable backup domain write */
void pmu_backup_write_enable(void);
/* disable backup domain write */
void pmu_backup_write_disable(void);

/* flag functions */
/* clear flag bit */
void pmu_flag_clear(uint32_t flag_clear);
/* get flag state */
FlagStatus pmu_flag_get(uint32_t flag);

#endif /* GD32E230_PMU_H */
