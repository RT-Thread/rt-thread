/*!
    \file    gd32e50x_pmu.h
    \brief   definitions for the PMU

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

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

#ifndef GD32E50X_PMU_H
#define GD32E50X_PMU_H

#include "gd32e50x.h"

/* PMU definitions */
#define PMU                           PMU_BASE                       /*!< PMU base address */

/* registers definitions */
#define PMU_CTL0                      REG32((PMU) + 0x00000000U)     /*!< PMU control register 0 */
#define PMU_CS0                       REG32((PMU) + 0x00000004U)     /*!< PMU control and status register 0 */
#define PMU_CTL1                      REG32((PMU) + 0x00000008U)     /*!< PMU control register 1 */
#define PMU_CS1                       REG32((PMU) + 0x0000000CU)     /*!< PMU control and status register 1 */

/* bits definitions */
/* PMU_CTL0 */
#define PMU_CTL0_LDOLP                BIT(0)                         /*!< LDO low power mode */
#define PMU_CTL0_STBMOD               BIT(1)                         /*!< standby mode */
#define PMU_CTL0_WURST                BIT(2)                         /*!< wakeup flag reset */
#define PMU_CTL0_STBRST               BIT(3)                         /*!< standby flag reset */
#define PMU_CTL0_LVDEN                BIT(4)                         /*!< low voltage detector enable */
#define PMU_CTL0_LVDT                 BITS(5,7)                      /*!< low voltage detector threshold */
#define PMU_CTL0_BKPWEN               BIT(8)                         /*!< backup domain write enable */
#define PMU_CTL0_LDLP                 BIT(10)                        /*!< low-driver mode when use low power LDO */
#define PMU_CTL0_LDNP                 BIT(11)                        /*!< low-driver mode when use normal power LDO */
#define PMU_CTL0_HDEN                 BIT(16)                        /*!< high-driver mode enable */
#define PMU_CTL0_HDS                  BIT(17)                        /*!< high-driver mode switch */
#define PMU_CTL0_LDEN                 BITS(18,19)                    /*!< low-driver mode enable in deep-sleep/deep-sleep 1/deep-sleep 2 mode */

/* PMU_CS0 */
#define PMU_CS0_WUF                   BIT(0)                         /*!< wakeup flag */
#define PMU_CS0_STBF                  BIT(1)                         /*!< standby flag */
#define PMU_CS0_LVDF                  BIT(2)                         /*!< low voltage detector status flag */
#define PMU_CS0_WUPEN6                BIT(7)                         /*!< wakeup pin 6 enable */
#define PMU_CS0_WUPEN0                BIT(8)                         /*!< wakeup pin 0 enable */
#define PMU_CS0_WUPEN1                BIT(9)                         /*!< wakeup pin 1 enable */
#define PMU_CS0_WUPEN2                BIT(10)                        /*!< wakeup pin 2 enable */
#define PMU_CS0_WUPEN3                BIT(11)                        /*!< wakeup pin 3 enable */
#define PMU_CS0_WUPEN4                BIT(12)                        /*!< wakeup pin 4 enable */
#define PMU_CS0_WUPEN5                BIT(13)                        /*!< wakeup pin 5 enable */
#define PMU_CS0_WUPEN7                BIT(15)                        /*!< wakeup pin 7 enable */
#define PMU_CS0_HDRF                  BIT(16)                        /*!< high-driver ready flag */
#define PMU_CS0_HDSRF                 BIT(17)                        /*!< high-driver switch ready flag */
#define PMU_CS0_LDRF                  BITS(18,19)                    /*!< Low-driver mode ready flag */

/* PMU_CTL1 */
#define PMU_CTL1_DPMOD1               BIT(0)                         /*!< deep-sleep 1 mode enable */
#define PMU_CTL1_DPMOD2               BIT(1)                         /*!< deep-sleep 2 mode enable */

/* PMU_CS1 */
#define PMU_CS1_DPF1                  BIT(0)                         /*!< deep-sleep 1 mode status flag */
#define PMU_CS1_DPF2                  BIT(1)                         /*!< deep-sleep 2 mode status flag */

/* constants definitions */
/* PMU ldo definitions */
#define PMU_LDO_NORMAL                ((uint32_t)0x00000000U)        /*!< LDO normal work when PMU enter deepsleep mode */
#define PMU_LDO_LOWPOWER              PMU_CTL0_LDOLP                 /*!< LDO work at low power status when PMU enter deepsleep mode */

/* PMU low voltage detector threshold definitions */
#define CTL0_LVDT(regval)             (BITS(5,7)&((uint32_t)(regval)<<5))
#define PMU_LVDT_0                    CTL0_LVDT(0)                   /*!< voltage threshold is 2.1V */
#define PMU_LVDT_1                    CTL0_LVDT(1)                   /*!< voltage threshold is 2.3V */
#define PMU_LVDT_2                    CTL0_LVDT(2)                   /*!< voltage threshold is 2.4V */
#define PMU_LVDT_3                    CTL0_LVDT(3)                   /*!< voltage threshold is 2.6V */
#define PMU_LVDT_4                    CTL0_LVDT(4)                   /*!< voltage threshold is 2.7V */
#define PMU_LVDT_5                    CTL0_LVDT(5)                   /*!< voltage threshold is 2.9V */
#define PMU_LVDT_6                    CTL0_LVDT(6)                   /*!< voltage threshold is 3.0V */
#define PMU_LVDT_7                    CTL0_LVDT(7)                   /*!< voltage threshold is 3.1V */

/* PMU low-driver mode when use low power LDO */
#define CTL0_LDLP(regval)             (BIT(10)&((uint32_t)(regval)<<10))
#define PMU_NORMALDR_LOWPWR           CTL0_LDLP(0)                   /*!< normal driver when use low power LDO */
#define PMU_LOWDR_LOWPWR              CTL0_LDLP(1)                   /*!< low-driver mode enabled when LDEN is 11 and use low power LDO */

/* PMU low-driver mode when use normal power LDO */
#define CTL0_LDNP(regval)             (BIT(11)&((uint32_t)(regval)<<11))
#define PMU_NORMALDR_NORMALPWR        CTL0_LDNP(0)                   /*!< normal driver when use normal power LDO */
#define PMU_LOWDR_NORMALPWR           CTL0_LDNP(1)                   /*!< low-driver mode enabled when LDEN is 11 and use normal power LDO */

/* PMU high-driver mode switch */
#define CTL0_HDS(regval)              (BIT(17)&((uint32_t)(regval)<<17))
#define PMU_HIGHDR_SWITCH_NONE        CTL0_HDS(0)                    /*!< no high-driver mode switch */
#define PMU_HIGHDR_SWITCH_EN          CTL0_HDS(1)                    /*!< high-driver mode switch */

/* low-driver mode in deep-sleep/deep-sleep 1/deep-sleep 2 mode */
#define PMU_LOWDRIVER_DISABLE         ((uint32_t)0x00000000U)        /*!< low-driver mode disable in deep-sleep/deep-sleep 1/deep-sleep 2 mode */
#define PMU_LOWDRIVER_ENABLE          PMU_CTL0_LDEN                  /*!< low-driver mode enable in deep-sleep/deep-sleep 1/deep-sleep 2 mode */

/* PMU WKUP pin definitions */
#define PMU_WAKEUP_PIN0               PMU_CS0_WUPEN0                 /*!< WKUP Pin 0 (PA0) enable */
#define PMU_WAKEUP_PIN1               PMU_CS0_WUPEN1                 /*!< WKUP Pin 1 (PC13) enable */
#define PMU_WAKEUP_PIN2               PMU_CS0_WUPEN2                 /*!< WKUP Pin 2 (PE6) enable */
#define PMU_WAKEUP_PIN3               PMU_CS0_WUPEN3                 /*!< WKUP Pin 3 (PA2) enable */
#define PMU_WAKEUP_PIN4               PMU_CS0_WUPEN4                 /*!< WKUP Pin 4 (PC5) enable */
#define PMU_WAKEUP_PIN5               PMU_CS0_WUPEN5                 /*!< WKUP Pin 5 (PB5) enable */
#define PMU_WAKEUP_PIN6               PMU_CS0_WUPEN6                 /*!< WKUP Pin 6 (PB15) enable */
#define PMU_WAKEUP_PIN7               PMU_CS0_WUPEN7                 /*!< WKUP Pin 7 (PF8) enable */

/* PMU low power mode ready flag definitions */
#define CS0_LDRF(regval)              (BITS(18,19)&((uint32_t)(regval)<<18))
#define PMU_LDRF_NORMAL               CS0_LDRF(0)                    /*!< normal driver in deep-sleep/deep-sleep 1/deep-sleep 2 mode */
#define PMU_LDRF_LOWDRIVER            CS0_LDRF(3)                    /*!< low-driver mode in deep-sleep/deep-sleep 1/deep-sleep 2 mode */

/* PMU flag definitions */
#define PMU_FLAG_WAKEUP               PMU_CS0_WUF                    /*!< wakeup flag status */
#define PMU_FLAG_STANDBY              PMU_CS0_STBF                   /*!< standby flag status */
#define PMU_FLAG_LVD                  PMU_CS0_LVDF                   /*!< lvd flag status */
#define PMU_FLAG_HDRF                 PMU_CS0_HDRF                   /*!< high-driver ready flag */
#define PMU_FLAG_HDSRF                PMU_CS0_HDSRF                  /*!< high-driver switch ready flag */
#define PMU_FLAG_LDRF                 PMU_CS0_LDRF                   /*!< low-driver mode ready flag */
#define PMU_FLAG_DEEPSLEEP_1          (BIT(31) | PMU_CS1_DPF1)       /*!< deep-sleep 1 mode status flag */
#define PMU_FLAG_DEEPSLEEP_2          (BIT(31) | PMU_CS1_DPF2)       /*!< deep-sleep 2 mode status flag */

/* PMU flag reset definitions */
#define PMU_FLAG_RESET_WAKEUP         ((uint8_t)0x00U)               /*!< wakeup flag reset */
#define PMU_FLAG_RESET_STANDBY        ((uint8_t)0x01U)               /*!< standby flag reset */
#define PMU_FLAG_RESET_DEEPSLEEP_1    ((uint8_t)0x02U)               /*!< deep-sleep 1 mode status flag reset */
#define PMU_FLAG_RESET_DEEPSLEEP_2    ((uint8_t)0x03U)               /*!< deep-sleep 2 mode status flag reset */

/* PMU command constants definitions */
#define WFI_CMD                       ((uint8_t)0x00U)               /*!< use WFI command */
#define WFE_CMD                       ((uint8_t)0x01U)               /*!< use WFE command */

/* function declarations */
/* reset PMU registers */
void pmu_deinit(void);

/* LVD functions */
/* select low voltage detector threshold */
void pmu_lvd_select(uint32_t lvdt_n);
/* disable PMU LVD */
void pmu_lvd_disable(void);

/* functions of low-driver mode and high-driver mode */
/* enable high-driver mode */
void pmu_highdriver_mode_enable(void);
/* disable high-driver mode */
void pmu_highdriver_mode_disable(void);
/* switch high-driver mode */
void pmu_highdriver_switch_select(uint32_t highdr_switch);
/* enable low-driver mode in deep-sleep/deep-sleep 1/deep-sleep 2 mode */
void pmu_lowdriver_mode_enable(void);
/* disable low-driver mode in deep-sleep/deep-sleep 1/deep-sleep 2 mode */
void pmu_lowdriver_mode_disable(void);
/* in deep-sleep/deep-sleep 1/deep-sleep 2 mode, driver mode when use low power LDO */
void pmu_lowpower_driver_config(uint32_t mode);
/* in deep-sleep/deep-sleep 1/deep-sleep 2 mode, driver mode when use normal power LDO */
void pmu_normalpower_driver_config(uint32_t mode);

/* set PMU mode */
/* PMU work in sleep mode */
void pmu_to_sleepmode(uint8_t sleepmodecmd);
/* PMU work in deepsleep mode */
void pmu_to_deepsleepmode(uint32_t ldo, uint32_t lowdrive, uint8_t deepsleepmodecmd);
/* PMU work in deepsleep mode 1 */
void pmu_to_deepsleepmode_1(uint32_t ldo, uint32_t lowdrive, uint8_t deepsleepmode1cmd);
/* PMU work in deepsleep mode 2 */
void pmu_to_deepsleepmode_2(uint32_t ldo, uint32_t lowdrive, uint8_t deepsleepmode2cmd);
/* PMU work in standby mode */
void pmu_to_standbymode(void);
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
/* get flag state */
FlagStatus pmu_flag_get(uint32_t flag);
/* clear flag bit */
void pmu_flag_clear(uint32_t flag);

#endif /* GD32E50X_PMU_H */
