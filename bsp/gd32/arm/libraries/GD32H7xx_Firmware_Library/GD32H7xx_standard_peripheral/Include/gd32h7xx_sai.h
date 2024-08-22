/*!
    \file    gd32h7xx_sai.h
    \brief   definitions for the SAI

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

#ifndef GD32H7XX_SAI_H
#define GD32H7XX_SAI_H

#include "gd32h7xx.h"

/* SAI definitions */
#define SAI0                            (SAI_BASE + 0x00000000U)                          /*!< SAI0 base address */
#define SAI1                            (SAI_BASE + 0x00000400U)                          /*!< SAI1 base address */
#define SAI2                            (SAI_BASE + 0x00000800U)                          /*!< SAI2 base address */

/* registers definitions */
#define SAI_SYNCFG(saix)                REG32((saix) + 0x00000000U)                       /*!< SAI synchronize configuration register */
#define SAI_B0CFG0(saix)                REG32((saix) + 0x00000004U)                       /*!< SAI block 0 configuration register0 */
#define SAI_B0CFG1(saix)                REG32((saix) + 0x00000008U)                       /*!< SAI block 0 configuration register1 */
#define SAI_B0FCFG(saix)                REG32((saix) + 0x0000000CU)                       /*!< SAI block 0 frame configuration register */
#define SAI_B0SCFG(saix)                REG32((saix) + 0x00000010U)                       /*!< SAI block 0 slot configuration register */
#define SAI_B0INTEN(saix)               REG32((saix) + 0x00000014U)                       /*!< SAI block 0 interrupt enable register  */
#define SAI_B0STAT(saix)                REG32((saix) + 0x00000018U)                       /*!< SAI block 0 status register */
#define SAI_B0INTC(saix)                REG32((saix) + 0x0000001CU)                       /*!< SAI block 0 interrupt flag clear register */
#define SAI_B0DATA(saix)                REG32((saix) + 0x00000020U)                       /*!< SAI block 0 data register */
#define SAI_B1CFG0(saix)                REG32((saix) + 0x00000024U)                       /*!< SAI block 1 configuration register0 */
#define SAI_B1CFG1(saix)                REG32((saix) + 0x00000028U)                       /*!< SAI block 1 configuration register1 */
#define SAI_B1FCFG(saix)                REG32((saix) + 0x0000002CU)                       /*!< SAI block 1 frame configuration register */
#define SAI_B1SCFG(saix)                REG32((saix) + 0x00000030U)                       /*!< SAI block 1 slot configuration register */
#define SAI_B1INTEN(saix)               REG32((saix) + 0x00000034U)                       /*!< SAI block 1 interrupt enable register  */
#define SAI_B1STAT(saix)                REG32((saix) + 0x00000038U)                       /*!< SAI block 1 status register */
#define SAI_B1INTC(saix)                REG32((saix) + 0x0000003CU)                       /*!< SAI block 1 interrupt flag clear register */
#define SAI_B1DATA(saix)                REG32((saix) + 0x00000040U)                       /*!< SAI block 1 data register */
#define SAI_PDMCTL(saix)                REG32((saix) + 0x00000044U)                       /*!< SAI PDM control register */
#define SAI_PDMCFG(saix)                REG32((saix) + 0x00000048U)                       /*!< SAI PDM configuration register */

#define SAI_CFG0(saix, blocky)          REG32(((saix) + 0x00000004U) + 0x20U * (blocky))  /*!< SAI block configuration register0 */
#define SAI_CFG1(saix, blocky)          REG32(((saix) + 0x00000008U) + 0x20U * (blocky))  /*!< SAI block configuration register1 */
#define SAI_FCFG(saix, blocky)          REG32(((saix) + 0x0000000CU) + 0x20U * (blocky))  /*!< SAI block frame configuration register */
#define SAI_SCFG(saix, blocky)          REG32(((saix) + 0x00000010U) + 0x20U * (blocky))  /*!< SAI block slot configuration register */
#define SAI_INTEN(saix, blocky)         REG32(((saix) + 0x00000014U) + 0x20U * (blocky))  /*!< SAI block interrupt enable register  */
#define SAI_STAT(saix, blocky)          REG32(((saix) + 0x00000018U) + 0x20U * (blocky))  /*!< SAI block status register */
#define SAI_INTC(saix, blocky)          REG32(((saix) + 0x0000001CU) + 0x20U * (blocky))  /*!< SAI block interrupt flag clear register */
#define SAI_DATA(saix, blocky)          REG32(((saix) + 0x00000020U) + 0x20U * (blocky))  /*!< SAI block data register */

/* bits definitions */
/* SAI_SYNCFG */
#define SAI_SYNCFG_SYNI                 BITS(0,1)                                   /*!< synchronization inputs */
#define SAI_SYNCFG_SYNO                 BITS(4,5)                                   /*!< synchronization outputs */

/* SAI_CFG0 */
#define SAI_CFG0_OPTMOD                 BITS(0,1)                                   /*!< operating mode */
#define SAI_CFG0_PROT                   BITS(2,3)                                   /*!< protocol selection */
#define SAI_CFG0_DATAWD                 BITS(5,7)                                   /*!< data width */
#define SAI_CFG0_SHIFTDIR               BIT(8)                                      /*!< shift direction */
#define SAI_CFG0_SAMPEDGE               BIT(9)                                      /*!< sampling clock edge */
#define SAI_CFG0_SYNCMOD                BITS(10,11)                                 /*!< synchronization mode */
#define SAI_CFG0_MONO                   BIT(12)                                     /*!< stereo and mono mode selection */
#define SAI_CFG0_ODRIV                  BIT(13)                                     /*!< output drive */
#define SAI_CFG0_SAIEN                  BIT(16)                                     /*!< sai sub-block enable */
#define SAI_CFG0_DMAEN                  BIT(17)                                     /*!< DMA enable */
#define SAI_CFG0_BYPASS                 BIT(19)                                     /*!< clock divider logic bypass */
#define SAI_CFG0_MDIV                   BITS(20,25)                                 /*!< master clock divider ratio */
#define SAI_CFG0_MOSPR                  BIT(26)                                     /*!< the master clock oversampling rate */
#define SAI_CFG0_MCLKEN                 BIT(27)                                     /*!< the master clock enable */

/* SAI_CFG1 */
#define SAI_CFG1_FFTH                   BITS(0,2)                                   /*!< FIFO threshold */
#define SAI_CFG1_FLUSH                  BIT(3)                                      /*!< FIFO flush */
#define SAI_CFG1_SDOM                   BIT(4)                                      /*!< serial data output management */
#define SAI_CFG1_MT                     BIT(5)                                      /*!< mute mode on */
#define SAI_CFG1_MTVAL                  BIT(6)                                      /*!< mute value */
#define SAI_CFG1_MTFCNT                 BITS(7,12)                                  /*!< mute frame count */
#define SAI_CFG1_CPLMOD                 BIT(13)                                     /*!< complement mode */
#define SAI_CFG1_CPAMOD                 BITS(14,15)                                 /*!< compander mode */

/* SAI_FCFG */
#define SAI_FCFG_FWD                    BITS(0,7)                                   /*!< frame width */
#define SAI_FCFG_FSAWD                  BITS(8,14)                                  /*!< frame synchronization active width */
#define SAI_FCFG_FSFUNC                 BIT(16)                                     /*!< frame synchronization function */
#define SAI_FCFG_FSPL                   BIT(17)                                     /*!< Frame synchronization active polarity */
#define SAI_FCFG_FSOST                  BIT(18)                                     /*!< frame synchronization offset */

/* SAI_SCFG */
#define SAI_SCFG_DATAOST                BITS(0,4)                                   /*!< data offset */
#define SAI_SCFG_SLOTWD                 BITS(6,7)                                   /*!< slot width */
#define SAI_SCFG_SLOTNUM                BITS(8,11)                                  /*!< slot number within frame */
#define SAI_SCFG_SLOTAV                 BITS(16,31)                                 /*!< slot activation vector */

/* SAI_INTEN */
#define SAI_INTEN_OUERRIE               BIT(0)                                      /*!< FIFO overrun or underrun interrupt enable */
#define SAI_INTEN_MTDETIE               BIT(1)                                      /*!< mute detection interrupt enable */
#define SAI_INTEN_ERRCKIE               BIT(2)                                      /*!< error clock interrupt enable */
#define SAI_INTEN_FFREQIE               BIT(3)                                      /*!< FIFO request interrupt enable */
#define SAI_INTEN_ACNRDYIE              BIT(4)                                      /*!< audio codec not ready interrupt enable */
#define SAI_INTEN_FSADETIE              BIT(5)                                      /*!< frame synchronization advanced detection interrupt enable */
#define SAI_INTEN_FSPDETIE              BIT(6)                                      /*!< frame synchronization postpone detection interrupt enable */

/* SAI_STAT */
#define SAI_STAT_OUERR                  BIT(0)                                      /*!< FIFO overrun or underrun */
#define SAI_STAT_MTDET                  BIT(1)                                      /*!< mute detection */
#define SAI_STAT_ERRCK                  BIT(2)                                      /*!< error clock */
#define SAI_STAT_FFREQ                  BIT(3)                                      /*!< FIFO request */
#define SAI_STAT_ACNRDY                 BIT(4)                                      /*!< audio codec not ready */
#define SAI_STAT_FSADET                 BIT(5)                                      /*!< frame synchronization advanced detection */
#define SAI_STAT_FSPDET                 BIT(6)                                      /*!< frame synchronization postpone detection */
#define SAI_STAT_FFSTAT                 BITS(16,18)                                 /*!< FIFO status */

/* SAI_INTC */
#define SAI_INTC_OUERRC                 BIT(0)                                      /*!< FIFO overrun or underrun interrupt clear */
#define SAI_INTC_MTDETC                 BIT(1)                                      /*!< mute detection interrupt clear */
#define SAI_INTC_ERRCKC                 BIT(2)                                      /*!< error clock interrupt clear */
#define SAI_INTC_ACNRDYC                BIT(4)                                      /*!< audio codec not ready interrupt clear */
#define SAI_INTC_FSADETC                BIT(5)                                      /*!< frame synchronization advanced detection interrupt clear */
#define SAI_INTC_FSPDETC                BIT(6)                                      /*!< frame synchronization postpone detection interrupt clear */

/* SAI_DATA */
#define SAI_DATA_DATA                   BITS(0,31)                                  /*!< transfer data or receive data */

/* SAI_PDMCTL */
#define SAI_PDMCTL_PDMEN                BIT(0)                                      /*!< PDM enable */
#define SAI_PDMCTL_MICNUMSEL            BITS(4,5)                                   /*!< microphones number selected */
#define SAI_PDMCTL_CLKL0EN              BIT(8)                                      /*!< PDM clock line 0 enable */
#define SAI_PDMCTL_CLKL1EN              BIT(9)                                      /*!< PDM clock line 1 enable */

/* SAI_PDMCFG */
#define SAI_PDMCFG_DPL0                 BITS(0,2)                                   /*!< the 0 group of left channel microphone data flow delay period */
#define SAI_PDMCTL_DPR0                 BITS(4,6)                                   /*!< the 0 group of right channel microphone data flow delay period */
#define SAI_PDMCFG_DPL1                 BITS(8,10)                                  /*!< the 1st group of left channel microphone data flow delay period */
#define SAI_PDMCTL_DPR1                 BITS(12,14)                                 /*!< the 1st group of right channel microphone data flow delay period */
#define SAI_PDMCFG_DPL2                 BITS(16,18)                                 /*!< the 2nd group of left channel microphone data flow delay period */
#define SAI_PDMCTL_DPR2                 BITS(20,22)                                 /*!< the 2nd group of right channel microphone data flow delay period */
#define SAI_PDMCFG_DPL3                 BITS(24,26)                                 /*!< the 3rd group of left channel microphone data flow delay period */
#define SAI_PDMCTL_DPR3                 BITS(28,30)                                 /*!< the 3rd group of right channel microphone data flow delay period */

/* constants definitions */
/* SAI initialize parameter struct definitions */
typedef struct {
    uint32_t operating_mode;                                                        /*!< operating mode */
    uint32_t protocol;                                                              /*!< protocol selection */
    uint32_t data_width;                                                            /*!< data width */
    uint32_t shift_dir;                                                             /*!< shift direction */
    uint32_t sample_edge;                                                           /*!< sampling clock edge */
    uint32_t sync_mode;                                                             /*!< synchronization mode */
    uint32_t output_drive;                                                          /*!< output drive */
    uint32_t clk_div_bypass;                                                        /*!< clock divider logic bypass */
    uint32_t mclk_div;                                                              /*!< master clock divider ratio */
    uint32_t mclk_oversampling;                                                     /*!< the master clock oversampling rate */
    uint32_t mclk_enable;                                                           /*!< the master clock enable */
    uint32_t fifo_threshold;                                                        /*!< FIFO threshold */
} sai_parameter_struct;

/* SAI frame initialize parameter struct definitions */
typedef struct {
    uint32_t frame_width;                                                           /*!< frame width */
    uint32_t frame_sync_width;                                                      /*!< frame synchronization active width */
    uint32_t frame_sync_function;                                                   /*!< frame synchronization function */
    uint32_t frame_sync_polarity;                                                   /*!< frame synchronization active polarity */
    uint32_t frame_sync_offset;                                                     /*!< frame synchronization offset */
} sai_frame_parameter_struct;

/* SAI slot initialize parameter struct definitions */
typedef struct {
    uint32_t slot_number;                                                           /*!< slot number */
    uint32_t slot_width;                                                            /*!< slot width */
    uint32_t data_offset;                                                           /*!< data offset */
    uint32_t slot_active;                                                           /*!< slot activation vector */
} sai_slot_parameter_struct;

/* SAI FIFO status */
typedef enum {
    FIFO_EMPTY  = 0U,                                                               /*!< empty */
    FIFO_EMPTY_TO_1_4_FULL,                                                         /*!< empty < fifo_level <= 1/4_full. */
    FIFO_1_4_FULL_TO_1_2_FULL,                                                      /*!< 1/4_full < fifo_level <= 1/2_full. */
    FIFO_1_2_FULL_TO_3_4_FULL,                                                      /*!< 1/2_full < fifo_level <= 3/4_full. */
    FIFO_3_4_FULL_TO_FULL,                                                          /*!< 3/4_full < fifo_level < full */
    FIFO_FULL                                                                       /*!< full */
} sai_fifo_state_enum;

/* SAI synchronization output definitions */
#define SYNCFG_SYNO(regval)             (BITS(4,5)&((uint32_t)(regval) << 4U))
#define SAI_SYNCOUTPUT_OFF              SYNCFG_SYNO(0)                              /*!< no synchronization output signals */
#define SAI_SYNCOUTPUT_BLOCK0           SYNCFG_SYNO(1)                              /*!< block 0 used for further synchronization for others SAI */
#define SAI_SYNCOUTPUT_BLOCK1           SYNCFG_SYNO(2)                              /*!< block 1 used for further synchronization for others SAI */

/* SAI synchronization input definitions */
#define SYNCFG_SYNI(regval)             (BITS(0,1)&((uint32_t)(regval) << 0U))
#define SAI_SYNCINPUT_SAI0              SYNCFG_SYNI(0)                              /*!< SAI 1 / 2 selects the synchronization coming from SAI 0 */
#define SAI_SYNCINPUT_SAI1              SYNCFG_SYNI(1)                              /*!< SAI 0 / 2 selects the synchronization coming from SAI 1 */
#define SAI_SYNCINPUT_SAI2              SYNCFG_SYNI(2)                              /*!< SAI 0 / 1 selects the synchronization coming from SAI 2 */

/* SAI master clock enable */
#define SAI_MCLK_DISABLE               ((uint32_t)0x00000000U)                      /*!< the master clock is enable when SAI enable */
#define SAI_MCLK_ENABLE                 SAI_CFG0_MCLKEN                             /*!< the master clock is enable now */

/* SAI master clock oversampling rate */
#define SAI_MCLK_OVERSAMP_256          ((uint32_t)0x00000000U)                      /*!< MCLK = 256 * Ffs */
#define SAI_MCLK_OVERSAMP_512           SAI_CFG0_MOSPR                              /*!< MCLK = 512 * Ffs */

/* SAI master clock divider ratio definitions */
#define CFG0_MDIV(regval)              (BITS(20,25)&((uint32_t)(regval) << 20U))
#define SAI_MCLKDIV_1                   CFG0_MDIV(0)                                /*!< primary frequency divider logic bypass */
#define SAI_MCLKDIV_2                   CFG0_MDIV(2)                                /*!< SAI clock is divided by 2 */
#define SAI_MCLKDIV_3                   CFG0_MDIV(3)                                /*!< SAI clock is divided by 3 */
#define SAI_MCLKDIV_4                   CFG0_MDIV(4)                                /*!< SAI clock is divided by 4 */
#define SAI_MCLKDIV_5                   CFG0_MDIV(5)                                /*!< SAI clock is divided by 5 */
#define SAI_MCLKDIV_6                   CFG0_MDIV(6)                                /*!< SAI clock is divided by 6 */
#define SAI_MCLKDIV_7                   CFG0_MDIV(7)                                /*!< SAI clock is divided by 7 */
#define SAI_MCLKDIV_8                   CFG0_MDIV(8)                                /*!< SAI clock is divided by 8 */
#define SAI_MCLKDIV_9                   CFG0_MDIV(9)                                /*!< SAI clock is divided by 9 */
#define SAI_MCLKDIV_10                  CFG0_MDIV(10)                               /*!< SAI clock is divided by 10 */
#define SAI_MCLKDIV_11                  CFG0_MDIV(11)                               /*!< SAI clock is divided by 11 */
#define SAI_MCLKDIV_12                  CFG0_MDIV(12)                               /*!< SAI clock is divided by 12 */
#define SAI_MCLKDIV_13                  CFG0_MDIV(13)                               /*!< SAI clock is divided by 13 */
#define SAI_MCLKDIV_14                  CFG0_MDIV(14)                               /*!< SAI clock is divided by 14 */
#define SAI_MCLKDIV_15                  CFG0_MDIV(15)                               /*!< SAI clock is divided by 15 */
#define SAI_MCLKDIV_16                  CFG0_MDIV(16)                               /*!< SAI clock is divided by 16 */
#define SAI_MCLKDIV_17                  CFG0_MDIV(17)                               /*!< SAI clock is divided by 17 */
#define SAI_MCLKDIV_18                  CFG0_MDIV(18)                               /*!< SAI clock is divided by 18 */
#define SAI_MCLKDIV_19                  CFG0_MDIV(19)                               /*!< SAI clock is divided by 19 */
#define SAI_MCLKDIV_20                  CFG0_MDIV(20)                               /*!< SAI clock is divided by 20 */
#define SAI_MCLKDIV_21                  CFG0_MDIV(21)                               /*!< SAI clock is divided by 21 */
#define SAI_MCLKDIV_22                  CFG0_MDIV(22)                               /*!< SAI clock is divided by 22 */
#define SAI_MCLKDIV_23                  CFG0_MDIV(23)                               /*!< SAI clock is divided by 23 */
#define SAI_MCLKDIV_24                  CFG0_MDIV(24)                               /*!< SAI clock is divided by 24 */
#define SAI_MCLKDIV_25                  CFG0_MDIV(25)                               /*!< SAI clock is divided by 25 */
#define SAI_MCLKDIV_26                  CFG0_MDIV(26)                               /*!< SAI clock is divided by 26 */
#define SAI_MCLKDIV_27                  CFG0_MDIV(27)                               /*!< SAI clock is divided by 27 */
#define SAI_MCLKDIV_28                  CFG0_MDIV(28)                               /*!< SAI clock is divided by 28 */
#define SAI_MCLKDIV_29                  CFG0_MDIV(29)                               /*!< SAI clock is divided by 29 */
#define SAI_MCLKDIV_30                  CFG0_MDIV(30)                               /*!< SAI clock is divided by 30 */
#define SAI_MCLKDIV_31                  CFG0_MDIV(31)                               /*!< SAI clock is divided by 31 */
#define SAI_MCLKDIV_32                  CFG0_MDIV(32)                               /*!< SAI clock is divided by 32 */
#define SAI_MCLKDIV_33                  CFG0_MDIV(33)                               /*!< SAI clock is divided by 33 */
#define SAI_MCLKDIV_34                  CFG0_MDIV(34)                               /*!< SAI clock is divided by 34 */
#define SAI_MCLKDIV_35                  CFG0_MDIV(35)                               /*!< SAI clock is divided by 35 */
#define SAI_MCLKDIV_36                  CFG0_MDIV(36)                               /*!< SAI clock is divided by 36 */
#define SAI_MCLKDIV_37                  CFG0_MDIV(37)                               /*!< SAI clock is divided by 37 */
#define SAI_MCLKDIV_38                  CFG0_MDIV(38)                               /*!< SAI clock is divided by 38 */
#define SAI_MCLKDIV_39                  CFG0_MDIV(39)                               /*!< SAI clock is divided by 39 */
#define SAI_MCLKDIV_40                  CFG0_MDIV(40)                               /*!< SAI clock is divided by 40 */
#define SAI_MCLKDIV_41                  CFG0_MDIV(41)                               /*!< SAI clock is divided by 41 */
#define SAI_MCLKDIV_42                  CFG0_MDIV(42)                               /*!< SAI clock is divided by 42 */
#define SAI_MCLKDIV_43                  CFG0_MDIV(43)                               /*!< SAI clock is divided by 43 */
#define SAI_MCLKDIV_44                  CFG0_MDIV(44)                               /*!< SAI clock is divided by 44 */
#define SAI_MCLKDIV_45                  CFG0_MDIV(45)                               /*!< SAI clock is divided by 45 */
#define SAI_MCLKDIV_46                  CFG0_MDIV(46)                               /*!< SAI clock is divided by 46 */
#define SAI_MCLKDIV_47                  CFG0_MDIV(47)                               /*!< SAI clock is divided by 47 */
#define SAI_MCLKDIV_48                  CFG0_MDIV(48)                               /*!< SAI clock is divided by 48 */
#define SAI_MCLKDIV_49                  CFG0_MDIV(49)                               /*!< SAI clock is divided by 49 */
#define SAI_MCLKDIV_50                  CFG0_MDIV(50)                               /*!< SAI clock is divided by 50 */
#define SAI_MCLKDIV_51                  CFG0_MDIV(51)                               /*!< SAI clock is divided by 51 */
#define SAI_MCLKDIV_52                  CFG0_MDIV(52)                               /*!< SAI clock is divided by 52 */
#define SAI_MCLKDIV_53                  CFG0_MDIV(53)                               /*!< SAI clock is divided by 53 */
#define SAI_MCLKDIV_54                  CFG0_MDIV(54)                               /*!< SAI clock is divided by 54 */
#define SAI_MCLKDIV_55                  CFG0_MDIV(55)                               /*!< SAI clock is divided by 55 */
#define SAI_MCLKDIV_56                  CFG0_MDIV(56)                               /*!< SAI clock is divided by 56 */
#define SAI_MCLKDIV_57                  CFG0_MDIV(57)                               /*!< SAI clock is divided by 57 */
#define SAI_MCLKDIV_58                  CFG0_MDIV(58)                               /*!< SAI clock is divided by 58 */
#define SAI_MCLKDIV_59                  CFG0_MDIV(59)                               /*!< SAI clock is divided by 59 */
#define SAI_MCLKDIV_60                  CFG0_MDIV(60)                               /*!< SAI clock is divided by 60 */
#define SAI_MCLKDIV_61                  CFG0_MDIV(61)                               /*!< SAI clock is divided by 61 */
#define SAI_MCLKDIV_62                  CFG0_MDIV(62)                               /*!< SAI clock is divided by 62 */
#define SAI_MCLKDIV_63                  CFG0_MDIV(63)                               /*!< SAI clock is divided by 63 */

/* SAI clock divider logic bypass */
#define SAI_CLKDIV_BYPASS_OFF           ((uint32_t)0x00000000U)                     /*!< clock divider ratio is applied to both primary and secondary divider logic */
#define SAI_CLKDIV_BYPASS_ON            SAI_CFG0_BYPASS                             /*!< clock divider logic is bypassed */

/* SAI output drive */
#define SAI_OUTPUT_WITH_SAIEN           ((uint32_t)0x00000000U)                     /*!< SAI sub-block output driven only when SAIEN is set */
#define SAI_OUTPUT_NOW                  SAI_CFG0_ODRIV                              /*!< SAI sub-block output driven according to ODRIV setting */

/* SAI stereo and mono mode selection */
#define SAI_STEREO_MODE                 ((uint32_t)0x00000000U)                     /*!< stereo mode */
#define SAI_MONO_MODE                   SAI_CFG0_MONO                               /*!< mono mode */

/* SAI synchronization mode definitions */
#define CFG0_SYNCMOD(regval)            (BITS(10,11)&((uint32_t)(regval) << 10U))
#define SAI_SYNCMODE_ASYNC              CFG0_SYNCMOD(0)                             /*!< asynchronous with the other sub-block */
#define SAI_SYNCMODE_OTHERBLOCK         CFG0_SYNCMOD(1)                             /*!< synchronous with the other sub-block */
#define SAI_SYNCMODE_EXTERNALSAI        CFG0_SYNCMOD(2)                             /*!< synchronous with an external SAI audio sub-block */

/* SAI sampling clock edge */
#define SAI_SAMPEDGE_FALLING            ((uint32_t)0x00000000U)                     /*!< data sampled on SCK falling edge */
#define SAI_SAMPEDGE_RISING             SAI_CFG0_SAMPEDGE                           /*!< data sampled on SCK rising edge */

/* SAI Shift direction */
#define SAI_SHIFT_MSB                   ((uint32_t)0x00000000U)                     /*!< data is shifted with MSB first */
#define SAI_SHIFT_LSB                   SAI_CFG0_SHIFTDIR                           /*!< data is shifted with LSB first */

/* SAI data width definitions */
#define CFG0_DW(regval)                 (BITS(5,7)&((uint32_t)(regval) << 5U))
#define SAI_DATAWIDTH_8BIT              CFG0_DW(2)                                  /*!< SAI data width 8 bit */
#define SAI_DATAWIDTH_10BIT             CFG0_DW(3)                                  /*!< SAI data width 10 bit */
#define SAI_DATAWIDTH_16BIT             CFG0_DW(4)                                  /*!< SAI data width 16 bit */
#define SAI_DATAWIDTH_20BIT             CFG0_DW(5)                                  /*!< SAI data width 20 bit */
#define SAI_DATAWIDTH_24BIT             CFG0_DW(6)                                  /*!< SAI data width 24 bit */
#define SAI_DATAWIDTH_32BIT             CFG0_DW(7)                                  /*!< SAI data width 32 bit */

/* SAI protocol selection */
#define CFG0_PROTOCOL(regval)           (BITS(2,3)&((uint32_t)(regval) << 2U))
#define SAI_PROTOCOL_POLYMORPHIC        CFG0_PROTOCOL(0)                            /*!< polymorphic */
#define SAI_PROTOCOL_SPDIF              CFG0_PROTOCOL(1)                            /*!< SPDIF */
#define SAI_PROTOCOL_AC97               CFG0_PROTOCOL(2)                            /*!< AC97 */

/* SAI operating mode */
#define CFG0_OPERATING(regval)          (BITS(0,1)&((uint32_t)(regval) << 0U))
#define SAI_MASTER_TRANSMITTER          CFG0_OPERATING(0)                           /*!< master transmitter */
#define SAI_MASTER_RECEIVER             CFG0_OPERATING(1)                           /*!< master receiver */
#define SAI_SLAVE_TRANSMITTER           CFG0_OPERATING(2)                           /*!< slave transmitter */
#define SAI_SLAVE_RECEIVER              CFG0_OPERATING(3)                           /*!< slave receiver */

/* SAI compander mode */
#define CFG1_COMPANDER(regval)          (BITS(14,15)&((uint32_t)(regval) << 14U))
#define SAI_COMPANDER_OFF               CFG1_COMPANDER(0)                           /*!< no compansion applies */
#define SAI_COMPANDER_ULAW              CFG1_COMPANDER(2)                           /*!< u-law algorithm */
#define SAI_COMPANDER_ALAW              CFG1_COMPANDER(3)                           /*!< A-law algorithm */

/* SAI complement mode */
#define SAI_COMPLEMENT_1S               ((uint32_t)0x00000000U)                     /*!< data represented in 1's complement form */
#define SAI_COMPLEMENT_2S               SAI_CFG1_CPLMOD                             /*!< data represented in 2's complement form */

/* SAI mute value */
#define SAI_MUTESENT_0                  ((uint32_t)0x00000000U)                     /*!< 0 is sent via the serial data line when mute is on */
#define SAI_MUTESENT_LASTFREAM          SAI_CFG1_MTVAL                              /*!< if SLOTNB is less or equals to two, last frame is sent via the serial data line */

/* SAI mute on */
#define SAI_MUTE_OFF                    ((uint32_t)0x00000000U)                     /*!< mute mode off */
#define SAI_MUTE_ON                     SAI_CFG1_MT                                 /*!< mute mode on */

/* SAI serial data line output management */
#define SAI_SDLINE_DRIVE                ((uint32_t)0x00000000U)                     /*!< SD line output is driven entirely during the audio frame */
#define SAI_SDLINE_RELEASE              SAI_CFG1_SDOM                               /*!< SD line output is released near inactive slots */

/* SAI FIFO threshold */
#define CFG1_FFTH(regval)               (BITS(0,2)&((uint32_t)(regval) << 0U))
#define SAI_FIFOTH_EMPTY                CFG1_FFTH(0)                                /*!< FIFO threshold empty */
#define SAI_FIFOTH_QUARTER              CFG1_FFTH(1)                                /*!< FIFO threshold quarter full */
#define SAI_FIFOTH_HALF                 CFG1_FFTH(2)                                /*!< FIFO threshold half full */
#define SAI_FIFOTH_THREE_QUARTER        CFG1_FFTH(3)                                /*!< FIFO threshold three quarter full */
#define SAI_FIFOTH_FULL                 CFG1_FFTH(4)                                /*!< FIFO threshold full */

/* SAI frame synchronization offset */
#define SAI_FS_OFFSET_BEGINNING         ((uint32_t)0x00000000U)                     /*!< FS active edge asserted at the beginning of the first bit of the first slot */
#define SAI_FS_OFFSET_ONEBITBEFORE      SAI_FCFG_FSOST                              /*!< FS active edge asserted one bit cycle before normal FS when FSOST is 0 */

/* SAI frame synchronization active polarity */
#define SAI_FS_POLARITY_LOW             ((uint32_t)0x00000000U)                     /*!< FS low active polarity */
#define SAI_FS_POLARITY_HIGH             SAI_FCFG_FSPL                              /*!< FS high active polarity */

/* SAI frame synchronization function */
#define SAI_FS_FUNC_START               ((uint32_t)0x00000000U)                     /*!< FS only defines frame start */
#define SAI_FS_FUNC_START_CHANNEL        SAI_FCFG_FSFUNC                            /*!< FS define both frame start and channel number */

/* SAI slot active */
#define SAI_SLOT_ACTIVE_NONE            ((uint32_t)0x00000000U)                     /*!< all slot inactive */
#define SAI_SLOT_ACTIVE_0                BIT(16)                                    /*!< slot 0 active */
#define SAI_SLOT_ACTIVE_1                BIT(17)                                    /*!< slot 1 active */
#define SAI_SLOT_ACTIVE_2                BIT(18)                                    /*!< slot 2 active */
#define SAI_SLOT_ACTIVE_3                BIT(19)                                    /*!< slot 3 active */
#define SAI_SLOT_ACTIVE_4                BIT(20)                                    /*!< slot 4 active */
#define SAI_SLOT_ACTIVE_5                BIT(21)                                    /*!< slot 5 active */
#define SAI_SLOT_ACTIVE_6                BIT(22)                                    /*!< slot 6 active */
#define SAI_SLOT_ACTIVE_7                BIT(23)                                    /*!< slot 7 active */
#define SAI_SLOT_ACTIVE_8                BIT(24)                                    /*!< slot 8 active */
#define SAI_SLOT_ACTIVE_9                BIT(25)                                    /*!< slot 9 active */
#define SAI_SLOT_ACTIVE_10               BIT(26)                                    /*!< slot 10 active */
#define SAI_SLOT_ACTIVE_11               BIT(27)                                    /*!< slot 11 active */
#define SAI_SLOT_ACTIVE_12               BIT(28)                                    /*!< slot 12 active */
#define SAI_SLOT_ACTIVE_13               BIT(29)                                    /*!< slot 13 active */
#define SAI_SLOT_ACTIVE_14               BIT(30)                                    /*!< slot 14 active */
#define SAI_SLOT_ACTIVE_15               BIT(31)                                    /*!< slot 15 active */
#define SAI_SLOT_ACTIVE_ALL              BITS(16,31)                                /*!< slot all active */

/* SAI slot width definitions */
#define SCFG_SW(regval)                 (BITS(6,7)&((uint32_t)(regval) << 6U))
#define SAI_SLOT_WIDTH_DATA              SCFG_SW(0)                                 /*!< slot width equals data width */
#define SAI_SLOT_WIDTH_16BIT             SCFG_SW(1)                                 /*!< slot width of 16-bits */
#define SAI_SLOT_WIDTH_32BIT             SCFG_SW(2)                                 /*!< slot width of 32-bits */

/* SAI interrupt enable or disable */
#define SAI_INT_OUERR                   SAI_INTEN_OUERRIE                           /*!< FIFO overrun or underrun interrupt enable */
#define SAI_INT_MTDET                   SAI_INTEN_MTDETIE                           /*!< mute detection interrupt enable */
#define SAI_INT_ERRCK                   SAI_INTEN_ERRCKIE                           /*!< error clock interrupt enable */
#define SAI_INT_FFREQ                   SAI_INTEN_FFREQIE                           /*!< FIFO request interrupt enable */
#define SAI_INT_ACNRDY                  SAI_INTEN_ACNRDYIE                          /*!< audio codec not ready interrupt enable */
#define SAI_INT_FSADET                  SAI_INTEN_FSADETIE                          /*!< frame synchronization advanced detection interrupt enable */
#define SAI_INT_FSPDET                  SAI_INTEN_FSPDETIE                          /*!< frame synchronization postpone detection interrupt enable */

/* SAI flags */
#define SAI_FLAG_OUERR                  SAI_STAT_OUERR                              /*!< FIFO overrun or underrun flag */
#define SAI_FLAG_MTDET                  SAI_STAT_MTDET                              /*!< mute detection flag */
#define SAI_FLAG_ERRCK                  SAI_STAT_ERRCK                              /*!< error clock flag */
#define SAI_FLAG_FFREQ                  SAI_STAT_FFREQ                              /*!< FIFO request flag */
#define SAI_FLAG_ACNRDY                 SAI_STAT_ACNRDY                             /*!< audio codec not ready flag */
#define SAI_FLAG_FSADET                 SAI_STAT_FSADET                             /*!< frame synchronization advanced detection flag */
#define SAI_FLAG_FSPDET                 SAI_STAT_FSPDET                             /*!< frame synchronization postpone detection flag */

/* SAI FIFO status */
#define STAT_FFSTAT(regval)             (BITS(16,18)&((uint32_t)(regval) << 16U))
#define SAI_FIFO_STAT_EMPTY              STAT_FFSTAT(0)                             /*!< FIFO status empty */
#define SAI_FIFO_STAT_QUARTER            STAT_FFSTAT(1)                             /*!< receiver: empty < FIFO <= 1/4,  transmitter: empty <  FIFO < 1/4 */
#define SAI_FIFO_STAT_HALF               STAT_FFSTAT(2)                             /*!< receiver: 1/4   < FIFO <= 1/2,  transmitter: 1/4   <= FIFO < 1/2 */
#define SAI_FIFO_STAT_THREE_QUARTER      STAT_FFSTAT(3)                             /*!< receiver: 1/2   < FIFO <= 3/4,  transmitter: 1/2   <= FIFO < 3/4 */
#define SAI_FIFO_STAT_NEARFULL           STAT_FFSTAT(4)                             /*!< receiver: 3/4   < FIFO <  full, transmitter: 3/4   <= FIFO < full */
#define SAI_FIFO_STAT_FULL               STAT_FFSTAT(5)                             /*!< FIFO status full */

/* SAI PDM microphone */
#define SAI_PDM_MICROPHONE0_L           ((uint32_t)0x00000000U)                     /*!< the group 0 left channel microphone */
#define SAI_PDM_MICROPHONE0_R           ((uint32_t)0x00000001U)                     /*!< the group 0 right channel microphone */
#define SAI_PDM_MICROPHONE1_L           ((uint32_t)0x00000002U)                     /*!< the group 1 left channel microphone */
#define SAI_PDM_MICROPHONE1_R           ((uint32_t)0x00000003U)                     /*!< the group 1 right channel microphone */
#define SAI_PDM_MICROPHONE2_L           ((uint32_t)0x00000004U)                     /*!< the group 2 left channel microphone */
#define SAI_PDM_MICROPHONE2_R           ((uint32_t)0x00000005U)                     /*!< the group 2 right channel microphone */
#define SAI_PDM_MICROPHONE3_L           ((uint32_t)0x00000006U)                     /*!< the group 3 left channel microphone */
#define SAI_PDM_MICROPHONE3_R           ((uint32_t)0x00000007U)                     /*!< the group 3 right channel microphone */

#define SAI_BLOCK0                      ((uint32_t)0x00000000U)                     /*!< Block 0 */
#define SAI_BLOCK1                      ((uint32_t)0x00000001U)                     /*!< Block 1 */

/* function declarations */
/* SAI deinitialization and initialization functions */
/* reset SAI */
void sai_deinit(uint32_t sai_periph);
/* initialize SAI parameter struct with the default values */
void sai_struct_para_init(sai_parameter_struct *sai_init_stuct);
/* initialize SAI frame parameter struct with the default values */
void sai_frame_struct_para_init(sai_frame_parameter_struct *sai_frame_init_struct);
/* initialize SAI slot parameter struct with the default values */
void sai_slot_struct_para_init(sai_slot_parameter_struct *sai_slot_init_struct);
/* initialize SAI */
void sai_init(uint32_t sai_periph, uint32_t block, sai_parameter_struct *sai_struct);
/* initialize SAI frame */
void sai_frame_init(uint32_t sai_periph, uint32_t block, sai_frame_parameter_struct *sai_frame_struct);
/* initialize SAI slot */
void sai_slot_init(uint32_t sai_periph, uint32_t block, sai_slot_parameter_struct *sai_slot_struct);
/* sai enable */
void sai_enable(uint32_t sai_periph, uint32_t block);
/* sai disable */
void sai_disable(uint32_t sai_periph, uint32_t block);

/* SAI configuration functions */
/* SAI serial data near inactive slot output management */
void sai_sdoutput_config(uint32_t sai_periph, uint32_t block, uint32_t sdout);
/* configure SAI mono mode */
void sai_monomode_config(uint32_t sai_periph, uint32_t block, uint32_t mono);
/* configure SAI companding mode */
void sai_companding_config(uint32_t sai_periph, uint32_t block, uint32_t compander,
                           uint32_t complement);
/* enable SAI mute detected or mute send */
void sai_mute_enable(uint32_t sai_periph, uint32_t block);
/* disable SAI mute detected or mute send */
void sai_mute_disable(uint32_t sai_periph, uint32_t block);
/* configure SAI mute value */
void sai_mute_value_config(uint32_t sai_periph, uint32_t block, uint32_t value);
/* configure SAI mute frame count */
void sai_mute_count_config(uint32_t sai_periph, uint32_t block, uint32_t count);
/* SAI transmit data */
void sai_data_transmit(uint32_t sai_periph, uint32_t block, uint32_t data);
/* SAI receive data */
uint32_t sai_data_receive(uint32_t sai_periph, uint32_t block);
/* get SAI fifo status */
sai_fifo_state_enum sai_fifo_status_get(uint32_t sai_periph, uint32_t block);
/* SAI fifo flush */
void sai_fifo_flush(uint32_t sai_periph, uint32_t block);

/* SAI DMA functions */
/* enable SAI dma */
void sai_dma_enable(uint32_t sai_periph, uint32_t block);
/* disable SAI dma */
void sai_dma_disable(uint32_t sai_periph, uint32_t block);

/* SAI synchronization function */
/* configure synchronization input select */
void sai_sync_input_config(uint32_t sai_periph, uint32_t input);
/* configure synchronization output select */
void sai_sync_output_config(uint32_t sai_periph, uint32_t output);

/* SAI pdm mode functions */
/* enable SAI pdm mode */
void sai_pdm_enable(uint32_t sai_periph);
/* disable SAI pdm mode */
void sai_pdm_disable(uint32_t sai_periph);
/* configure SAI pdm mode microphone number */
void sai_pdm_microphone_number_config(uint32_t sai_periph, uint32_t microphonenum);
/* configure SAI pdm mode microphone delay */
void sai_pdm_delay_config(uint32_t sai_periph, uint32_t microphone, uint32_t delay);
/* enable SAI pdm mode clock line 0 */
void sai_pdm_clk0_enable(uint32_t sai_periph);
/* disable SAI pdm mode clock line 0 */
void sai_pdm_clk0_disable(uint32_t sai_periph);
/* enable SAI pdm mode clock line 1 */
void sai_pdm_clk1_enable(uint32_t sai_periph);
/* disable SAI pdm mode clock line 1 */
void sai_pdm_clk1_disable(uint32_t sai_periph);

/* flag and interrupt functions */
/* enable the SAI interrupt */
void sai_interrupt_enable(uint32_t sai_periph, uint32_t block, uint32_t interrupt);
/* disable the SAI interrupt */
void sai_interrupt_disable(uint32_t sai_periph, uint32_t block, uint32_t interrupt);
/* get SAI interrupt flag status */
FlagStatus sai_interrupt_flag_get(uint32_t sai_periph, uint32_t block, uint32_t interrupt);
/* clear SAI interrupt flag status */
void sai_interrupt_flag_clear(uint32_t sai_periph, uint32_t block, uint32_t interrupt);
/* get SAI flag status */
FlagStatus sai_flag_get(uint32_t sai_periph, uint32_t block, uint32_t flag);
/* clear SAI flag status */
void sai_flag_clear(uint32_t sai_periph, uint32_t block, uint32_t flag);

#endif /* GD32H7XX_SAI_H */
