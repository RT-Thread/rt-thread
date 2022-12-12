/*!
    \file    gd32f20x_bkp.h
    \brief   definitions for the BKP

    \version 2015-07-15, V1.0.0, firmware for GD32F20x
    \version 2017-06-05, V2.0.0, firmware for GD32F20x
    \version 2018-10-31, V2.1.0, firmware for GD32F20x
    \version 2020-09-30, V2.2.0, firmware for GD32F20x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

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

#ifndef GD32F20X_BKP_H
#define GD32F20X_BKP_H

#include "gd32f20x.h"

/* BKP definitions */
#define BKP                             BKP_BASE                 /*!< BKP base address */

/* registers definitions */
#define BKP_DATA0                       REG16((BKP) + 0x04U)     /*!< BKP data register 0 */
#define BKP_DATA1                       REG16((BKP) + 0x08U)     /*!< BKP data register 1 */
#define BKP_DATA2                       REG16((BKP) + 0x0CU)     /*!< BKP data register 2 */
#define BKP_DATA3                       REG16((BKP) + 0x10U)     /*!< BKP data register 3 */
#define BKP_DATA4                       REG16((BKP) + 0x14U)     /*!< BKP data register 4 */
#define BKP_DATA5                       REG16((BKP) + 0x18U)     /*!< BKP data register 5 */
#define BKP_DATA6                       REG16((BKP) + 0x1CU)     /*!< BKP data register 6 */
#define BKP_DATA7                       REG16((BKP) + 0x20U)     /*!< BKP data register 7 */
#define BKP_DATA8                       REG16((BKP) + 0x24U)     /*!< BKP data register 8 */
#define BKP_DATA9                       REG16((BKP) + 0x28U)     /*!< BKP data register 9 */
#define BKP_DATA10                      REG16((BKP) + 0x40U)     /*!< BKP data register 10 */
#define BKP_DATA11                      REG16((BKP) + 0x44U)     /*!< BKP data register 11 */
#define BKP_DATA12                      REG16((BKP) + 0x48U)     /*!< BKP data register 12 */
#define BKP_DATA13                      REG16((BKP) + 0x4CU)     /*!< BKP data register 13 */
#define BKP_DATA14                      REG16((BKP) + 0x50U)     /*!< BKP data register 14 */
#define BKP_DATA15                      REG16((BKP) + 0x54U)     /*!< BKP data register 15 */
#define BKP_DATA16                      REG16((BKP) + 0x58U)     /*!< BKP data register 16 */
#define BKP_DATA17                      REG16((BKP) + 0x5CU)     /*!< BKP data register 17 */
#define BKP_DATA18                      REG16((BKP) + 0x60U)     /*!< BKP data register 18 */
#define BKP_DATA19                      REG16((BKP) + 0x64U)     /*!< BKP data register 19 */
#define BKP_DATA20                      REG16((BKP) + 0x68U)     /*!< BKP data register 20 */
#define BKP_DATA21                      REG16((BKP) + 0x6CU)     /*!< BKP data register 21 */
#define BKP_DATA22                      REG16((BKP) + 0x70U)     /*!< BKP data register 22 */
#define BKP_DATA23                      REG16((BKP) + 0x74U)     /*!< BKP data register 23 */
#define BKP_DATA24                      REG16((BKP) + 0x78U)     /*!< BKP data register 24 */
#define BKP_DATA25                      REG16((BKP) + 0x7CU)     /*!< BKP data register 25 */
#define BKP_DATA26                      REG16((BKP) + 0x80U)     /*!< BKP data register 26 */
#define BKP_DATA27                      REG16((BKP) + 0x84U)     /*!< BKP data register 27 */
#define BKP_DATA28                      REG16((BKP) + 0x88U)     /*!< BKP data register 28 */
#define BKP_DATA29                      REG16((BKP) + 0x8CU)     /*!< BKP data register 29 */
#define BKP_DATA30                      REG16((BKP) + 0x90U)     /*!< BKP data register 30 */
#define BKP_DATA31                      REG16((BKP) + 0x94U)     /*!< BKP data register 31 */
#define BKP_DATA32                      REG16((BKP) + 0x98U)     /*!< BKP data register 32 */
#define BKP_DATA33                      REG16((BKP) + 0x9CU)     /*!< BKP data register 33 */
#define BKP_DATA34                      REG16((BKP) + 0xA0U)     /*!< BKP data register 34 */
#define BKP_DATA35                      REG16((BKP) + 0xA4U)     /*!< BKP data register 35 */
#define BKP_DATA36                      REG16((BKP) + 0xA8U)     /*!< BKP data register 36 */
#define BKP_DATA37                      REG16((BKP) + 0xACU)     /*!< BKP data register 37 */
#define BKP_DATA38                      REG16((BKP) + 0xB0U)     /*!< BKP data register 38 */
#define BKP_DATA39                      REG16((BKP) + 0xB4U)     /*!< BKP data register 39 */
#define BKP_DATA40                      REG16((BKP) + 0xB8U)     /*!< BKP data register 40 */
#define BKP_DATA41                      REG16((BKP) + 0xBCU)     /*!< BKP data register 41 */
#define BKP_OCTL                        REG16((BKP) + 0x2CU)     /*!< RTC signal output control register */
#define BKP_TPCTL0                      REG16((BKP) + 0x30U)     /*!< tamper pin control register 0 */
#define BKP_TPCS                        REG16((BKP) + 0x34U)     /*!< tamper control and status register */
#define BKP_TPCTL1                      REG16((BKP) + 0x38U)     /*!< tamper pin control register 1 */

/* bits definitions */
/* BKP_DATA */
#define BKP_DATA                        BITS(0,15)               /*!< backup data */

/* BKP_OCTL */
#define BKP_OCTL_RCCV                   BITS(0,6)                /*!< RTC clock calibration value */
#define BKP_OCTL_COEN                   BIT(7)                   /*!< RTC clock calibration output enable */
#define BKP_OCTL_ASOEN                  BIT(8)                   /*!< RTC alarm or second signal output enable */
#define BKP_OCTL_ROSEL                  BIT(9)                   /*!< RTC output selection */
#define BKP_OCTL_CCOSEL                 BIT(14)                  /*!< RTC clock output selection */
#define BKP_OCTL_CALDIR                 BIT(15)                  /*!< RTC clock calibration direction */

/* BKP_TPCTL0 */
#define BKP_TPCTL0_TPEN0                BIT(0)                   /*!< tamper0 detection enable */
#define BKP_TPCTL0_TPAL0                BIT(1)                   /*!< tamper0 pin active level */

/* BKP_TPCS */
#define BKP_TPCS_TER0                   BIT(0)                   /*!< tamper0 event reset */
#define BKP_TPCS_TIR0                   BIT(1)                   /*!< tamper0 interrupt reset */
#define BKP_TPCS_TPIE0                  BIT(2)                   /*!< tamper0 interrupt enable */
#define BKP_TPCS_TER1                   BIT(5)                   /*!< tamper1 event reset */
#define BKP_TPCS_TIR1                   BIT(6)                   /*!< tamper1 interrupt reset */
#define BKP_TPCS_TPIE1                  BIT(7)                   /*!< tamper1 interrupt enable */
#define BKP_TPCS_TEF0                   BIT(8)                   /*!< tamper0 event flag */
#define BKP_TPCS_TIF0                   BIT(9)                   /*!< tamper0 interrupt flag */
#define BKP_TPCS_TEF1                   BIT(14)                  /*!< tamper1 event flag */
#define BKP_TPCS_TIF1                   BIT(15)                  /*!< tamper1 interrupt flag */

/* BKP_TPCTL1 */
#define BKP_TPCTL1_TPEN1                BIT(8)                   /*!< tamper1 detection enable */
#define BKP_TPCTL1_TPAL1                BIT(9)                   /*!< tamper1 pin active level */
#define BKP_TPCTL1_TPM2                 BIT(14)                  /*!< the second waveform detection enable */
#define BKP_TPCTL1_TPM1                 BIT(15)                  /*!< the first waveform detection enable */

/* constants definitions */
/* tamperx definitions */
typedef enum
{
    TAMPER_0 = 0,                                                /*!< BKP tamper0 */
    TAMPER_1,                                                    /*!< BKP tamper1 */
}bkp_tamper_enum;

/* BKP data register number */
typedef enum
{
    BKP_DATA_0 = 1,                                              /*!< BKP data register 0 */
    BKP_DATA_1,                                                  /*!< BKP data register 1 */
    BKP_DATA_2,                                                  /*!< BKP data register 2 */
    BKP_DATA_3,                                                  /*!< BKP data register 3 */
    BKP_DATA_4,                                                  /*!< BKP data register 4 */
    BKP_DATA_5,                                                  /*!< BKP data register 5 */
    BKP_DATA_6,                                                  /*!< BKP data register 6 */
    BKP_DATA_7,                                                  /*!< BKP data register 7 */
    BKP_DATA_8,                                                  /*!< BKP data register 8 */
    BKP_DATA_9,                                                  /*!< BKP data register 9 */
    BKP_DATA_10,                                                 /*!< BKP data register 10 */
    BKP_DATA_11,                                                 /*!< BKP data register 11 */
    BKP_DATA_12,                                                 /*!< BKP data register 12 */
    BKP_DATA_13,                                                 /*!< BKP data register 13 */
    BKP_DATA_14,                                                 /*!< BKP data register 14 */
    BKP_DATA_15,                                                 /*!< BKP data register 15 */
    BKP_DATA_16,                                                 /*!< BKP data register 16 */
    BKP_DATA_17,                                                 /*!< BKP data register 17 */
    BKP_DATA_18,                                                 /*!< BKP data register 18 */
    BKP_DATA_19,                                                 /*!< BKP data register 19 */
    BKP_DATA_20,                                                 /*!< BKP data register 20 */
    BKP_DATA_21,                                                 /*!< BKP data register 21 */
    BKP_DATA_22,                                                 /*!< BKP data register 22 */
    BKP_DATA_23,                                                 /*!< BKP data register 23 */
    BKP_DATA_24,                                                 /*!< BKP data register 24 */
    BKP_DATA_25,                                                 /*!< BKP data register 25 */
    BKP_DATA_26,                                                 /*!< BKP data register 26 */
    BKP_DATA_27,                                                 /*!< BKP data register 27 */
    BKP_DATA_28,                                                 /*!< BKP data register 28 */
    BKP_DATA_29,                                                 /*!< BKP data register 29 */
    BKP_DATA_30,                                                 /*!< BKP data register 30 */
    BKP_DATA_31,                                                 /*!< BKP data register 31 */
    BKP_DATA_32,                                                 /*!< BKP data register 32 */
    BKP_DATA_33,                                                 /*!< BKP data register 33 */
    BKP_DATA_34,                                                 /*!< BKP data register 34 */
    BKP_DATA_35,                                                 /*!< BKP data register 35 */
    BKP_DATA_36,                                                 /*!< BKP data register 36 */
    BKP_DATA_37,                                                 /*!< BKP data register 37 */
    BKP_DATA_38,                                                 /*!< BKP data register 38 */
    BKP_DATA_39,                                                 /*!< BKP data register 39 */
    BKP_DATA_40,                                                 /*!< BKP data register 40 */
    BKP_DATA_41,                                                 /*!< BKP data register 41 */
}bkp_data_register_enum;

/* BKP register */
#define BKP_DATA0_9(number)             REG16((BKP) + 0x04U + (number) * 0x04U)
#define BKP_DATA10_41(number)           REG16((BKP) + 0x40U + ((number)-10U) * 0x04U)

/* get data of BKP data register */
#define BKP_DATA_GET(regval)            GET_BITS((uint32_t)(regval), 0, 15)

/* RTC clock calibration value */
#define OCTL_RCCV(regval)               (BITS(0,6) & ((uint32_t)(regval) << 0))

/* RTC output selection */
#define RTC_OUTPUT_ALARM_PULSE          ((uint16_t)0x0000U)      /*!< RTC alarm pulse is selected as the RTC output */
#define RTC_OUTPUT_SECOND_PULSE         ((uint16_t)0x0200U)      /*!< RTC second pulse is selected as the RTC output */

/* RTC clock output selection */
#define RTC_CLOCK_DIV64                 ((uint16_t)0x0000U)      /*!< RTC clock div 64 */
#define RTC_CLOCK_DIV1                  ((uint16_t)0x4000U)      /*!< RTC clock div 1 */

/* RTC clock calibration direction */
#define RTC_CLOCK_SLOWED_DOWN           ((uint16_t)0x0000U)      /*!< RTC clock slow down */
#define RTC_CLOCK_SPEED_UP              ((uint16_t)0x8000U)      /*!< RTC clock speed up */

/* tamper pin active level */
#define TAMPER_PIN_ACTIVE_HIGH          ((uint16_t)0x0000U)      /*!< the tamper pin is active high */
#define TAMPER_PIN_ACTIVE_LOW           ((uint16_t)0x0002U)      /*!< the tamper pin is active low */

/* tamper flag */
#define BKP_FLAG_TAMPER0                BKP_TPCS_TEF0            /*!< tamper0 event flag */
#define BKP_FLAG_TAMPER1_WAVEDETECT     BKP_TPCS_TEF1            /*!< tamper1/waveform detect event flag */

/* tamper interrupt flag */
#define BKP_INT_FLAG_TAMPER0            BKP_TPCS_TIF0            /*!< tamper0 interrupt flag */
#define BKP_INT_FLAG_TAMPER1_WAVEDETECT BKP_TPCS_TIF1            /*!< tamper1/waveform detect interrupt flag */

/* waveform detection mode */
#define BKP_WAVEFORM_DETECT_1           BKP_TPCTL1_TPM1          /*!< the first waveform detection */
#define BKP_WAVEFORM_DETECT_2           BKP_TPCTL1_TPM2          /*!< the second waveform detection */

/* function declarations */
/* initialization functions */
/* reset BKP registers */
void bkp_deinit(void);
/* write BKP data register */
void bkp_data_write(bkp_data_register_enum register_number, uint16_t data);
/* read BKP data register */
uint16_t bkp_data_read(bkp_data_register_enum register_number);

/* function configuration */
/* RTC related functions */
/* enable RTC clock calibration output */
void bkp_rtc_calibration_output_enable(void);
/* disable RTC clock calibration output */
void bkp_rtc_calibration_output_disable(void);
/* enable RTC alarm or second signal output */
void bkp_rtc_signal_output_enable(void);
/* disable RTC alarm or second signal output */
void bkp_rtc_signal_output_disable(void);
/* select RTC output */
void bkp_rtc_output_select(uint16_t outputsel);
/* RTC clock output selection */
void bkp_rtc_clock_output_select(uint16_t clocksel);
/* RTC clock calibration direction */
void bkp_rtc_clock_calibration_direction(uint16_t direction);
/* set RTC clock calibration value */
void bkp_rtc_calibration_value_set(uint8_t value);

/* tamper pin related functions */
/* enable tamper pin detection */
void bkp_tamper_detection_enable(bkp_tamper_enum tamperx);
/* disable tamper pin detection */
void bkp_tamper_detection_disable(bkp_tamper_enum tamperx);
/* set tamper pin active level */
void bkp_tamper_active_level_set(bkp_tamper_enum tamperx, uint16_t level);

/* interrupt & flag functions */
/* enable tamper pin interrupt */
void bkp_tamper_interrupt_enable(bkp_tamper_enum tamperx);
/* disable tamper pin interrupt */
void bkp_tamper_interrupt_disable(bkp_tamper_enum tamperx);
/* waveform detect configure */
void bkp_waveform_detect_enable(uint16_t waveform_detect_mode, ControlStatus newvalue);
/* get BKP flag state */
FlagStatus bkp_flag_get(uint16_t flag);
/* clear BKP flag state */
void bkp_flag_clear(uint16_t flag);
/* get BKP interrupt flag state */
FlagStatus bkp_interrupt_flag_get(uint16_t flag);
/* clear BKP interrupt flag state */
void bkp_interrupt_flag_clear(uint16_t flag);

#endif /* GD32F20X_BKP_H */
