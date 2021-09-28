/*!
    \file  gd32f3x0_pmu.h
    \brief definitions for the PMU

    \version 2017-06-06, V1.0.0, firmware for GD32F3x0
    \version 2019-06-01, V2.0.0, firmware for GD32F3x0
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

#ifndef GD32F3X0_PMU_H
#define GD32F3X0_PMU_H

#include "gd32f3x0.h"

/* PMU definitions */
#define PMU                           PMU_BASE                 /*!< PMU base address */

/* registers definitions */
#define PMU_CTL                       REG32(PMU + 0x00000000U) /*!< PMU control register */
#define PMU_CS                        REG32(PMU + 0x00000004U) /*!< PMU control and status register */

/* bits definitions */
/* PMU_CTL */
#define PMU_CTL_LDOLP                 BIT(0)                   /*!< LDO low power mode */
#define PMU_CTL_STBMOD                BIT(1)                   /*!< standby mode */
#define PMU_CTL_WURST                 BIT(2)                   /*!< wakeup flag reset */
#define PMU_CTL_STBRST                BIT(3)                   /*!< standby flag reset */
#define PMU_CTL_LVDEN                 BIT(4)                   /*!< low voltage detector enable */
#define PMU_CTL_LVDT                  BITS(5,7)                /*!< low voltage detector threshold */
#define PMU_CTL_BKPWEN                BIT(8)                   /*!< backup domain write enable */
#define PMU_CTL_LDLP                  BIT(10)                  /*!< low-driver mode when use low power LDO */
#define PMU_CTL_LDNP                  BIT(11)                  /*!< low-driver mode when use normal power LDO */
#define PMU_CTL_LDOVS                 BITS(14,15)              /*!< LDO output voltage select */
#define PMU_CTL_HDEN                  BIT(16)                  /*!< high-driver mode enable */
#define PMU_CTL_HDS                   BIT(17)                  /*!< high-driver mode switch */
#define PMU_CTL_LDEN                  BITS(18,19)              /*!< low-driver mode enable in deep-sleep mode */

/* PMU_CS */
#define PMU_CS_WUF                    BIT(0)                   /*!< wakeup flag */
#define PMU_CS_STBF                   BIT(1)                   /*!< standby flag */
#define PMU_CS_LVDF                   BIT(2)                   /*!< low voltage detector status flag */
#define PMU_CS_WUPEN0                 BIT(8)                   /*!< wakeup pin enable */
#define PMU_CS_WUPEN1                 BIT(9)                   /*!< wakeup pin enable */
#define PMU_CS_WUPEN4                 BIT(12)                  /*!< wakeup pin enable */
#define PMU_CS_WUPEN5                 BIT(13)                  /*!< wakeup pin enable */
#define PMU_CS_WUPEN6                 BIT(14)                  /*!< wakeup pin enable */
#define PMU_CS_LDOVSRF                BIT(15)                  /*!< LDO voltage select ready flag */
#define PMU_CS_HDRF                   BIT(16)                  /*!< high-driver ready flag */
#define PMU_CS_HDSRF                  BIT(17)                  /*!< high-driver switch ready flag */
#define PMU_CS_LDRF                   BITS(18,19)              /*!< low-driver mode ready flag */

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
#define PMU_LDOVS_LOW                 CTL_LDOVS(1)             /*!< LDO output voltage low mode */
#define PMU_LDOVS_MID                 CTL_LDOVS(2)             /*!< LDO output voltage mid mode */
#define PMU_LDOVS_HIGH                CTL_LDOVS(3)             /*!< LDO output voltage high mode */

/* PMU low-driver mode enable in deep-sleep mode */
#define CTL_LDEN(regval)              (BITS(18,19)&((uint32_t)(regval)<<18))
#define PMU_LOWDRIVER_DISABLE         CTL_LDEN(0)              /*!< low-driver mode disable in deep-sleep mode */
#define PMU_LOWDRIVER_ENABLE          CTL_LDEN(3)              /*!< low-driver mode enable in deep-sleep mode */

/* PMU high-driver mode switch */
#define PMU_HIGHDR_SWITCH_NONE        ((uint32_t)0x00000000U)  /*!< no high-driver mode switch */
#define PMU_HIGHDR_SWITCH_EN          PMU_CTL_HDS              /*!< high-driver mode switch */

/* PMU low-driver mode when use normal power LDO */
#define PMU_NORMALDR_NORMALPWR        ((uint32_t)0x00000000U)  /*!< normal-driver when use normal power LDO */
#define PMU_LOWDR_NORMALPWR           PMU_CTL_LDNP             /*!< low-driver mode enabled when LDEN is 11 and use normal power LDO */

/* PMU low-driver mode when use low power LDO */
#define PMU_NORMALDR_LOWPWR           ((uint32_t)0x00000000U)  /*!< normal-driver when use low power LDO */
#define PMU_LOWDR_LOWPWR              PMU_CTL_LDLP             /*!< low-driver mode enabled when LDEN is 11 and use low power LDO */

/* PMU ldo definitions */
#define PMU_LDO_NORMAL                ((uint32_t)0x00000000U)  /*!< LDO operates normally when PMU enter deepsleep mode */
#define PMU_LDO_LOWPOWER              PMU_CTL_LDOLP            /*!< LDO work at low power status when PMU enter deepsleep mode */

/* PMU low power mode ready flag definitions */
#define CS_LDRF(regval)               (BITS(18,19)&((uint32_t)(regval)<<18))
#define PMU_LDRF_NORMAL               CS_LDRF(0)               /*!< normal-driver in deep-sleep mode */
#define PMU_LDRF_LOWDRIVER            CS_LDRF(3)               /*!< low-driver mode in deep-sleep mode */

/* PMU flag definitions */
#define PMU_FLAG_WAKEUP               PMU_CS_WUF               /*!< wakeup flag status */
#define PMU_FLAG_STANDBY              PMU_CS_STBF              /*!< standby flag status */
#define PMU_FLAG_LVD                  PMU_CS_LVDF              /*!< LVD flag status */
#define PMU_FLAG_LDOVSR               PMU_CS_LDOVSRF           /*!< LDO voltage select ready flag */
#define PMU_FLAG_HDR                  PMU_CS_HDRF              /*!< high-driver ready flag */
#define PMU_FLAG_HDSR                 PMU_CS_HDSRF             /*!< high-driver switch ready flag */
#define PMU_FLAG_LDR                  PMU_CS_LDRF              /*!< low-driver mode ready flag */

/* PMU WKUP pin definitions */
#define PMU_WAKEUP_PIN0               PMU_CS_WUPEN0            /*!< WKUP Pin 0 (PA0) enable */
#define PMU_WAKEUP_PIN1               PMU_CS_WUPEN1            /*!< WKUP Pin 1 (PC13) enable */
#define PMU_WAKEUP_PIN4               PMU_CS_WUPEN4            /*!< WKUP Pin 4 (PC5) enable */
#define PMU_WAKEUP_PIN5               PMU_CS_WUPEN5            /*!< WKUP Pin 5 (PB5) enable */
#define PMU_WAKEUP_PIN6               PMU_CS_WUPEN6            /*!< WKUP Pin 6 (PB15) enable */

/* PMU flag reset definitions */
#define PMU_FLAG_RESET_WAKEUP         PMU_CTL_WURST            /*!< wakeup flag reset */
#define PMU_FLAG_RESET_STANDBY        PMU_CTL_STBRST           /*!< standby flag reset */

/* PMU command constants definitions */
#define WFI_CMD                       ((uint8_t)0x00U)         /*!< use WFI command */
#define WFE_CMD                       ((uint8_t)0x01U)         /*!< use WFE command */

/* function declarations */
/* function configuration */
/* reset PMU registers */
void pmu_deinit(void);
/* select low voltage detector threshold */
void pmu_lvd_select(uint32_t lvdt_n);
/* select LDO output voltage */
void pmu_ldo_output_select(uint32_t ldo_output);
/* disable PMU lvd */
void pmu_lvd_disable(void);

/* functions of low-driver mode and high-driver mode in deep-sleep mode */
/* enable low-driver mode in deep-sleep mode */
void pmu_lowdriver_mode_enable(void);
/* disable low-driver mode in deep-sleep mode */
void pmu_lowdriver_mode_disable(void);
/* enable high-driver mode */
void pmu_highdriver_mode_enable(void);
/* disable high-driver mode */
void pmu_highdriver_mode_disable(void);
/* switch high-driver mode */
void pmu_highdriver_switch_select(uint32_t highdr_switch);
/* in deep-sleep mode, low-driver mode when use low power LDO */
void pmu_lowpower_driver_config(uint32_t mode);
/* in deep-sleep mode, low-driver mode when use normal power LDO */
void pmu_normalpower_driver_config(uint32_t mode);

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

#endif /* GD32F3X0_PMU_H */
