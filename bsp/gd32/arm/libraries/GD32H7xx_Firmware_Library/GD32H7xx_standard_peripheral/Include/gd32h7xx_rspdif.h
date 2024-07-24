/*!
    \file    gd32h7xx_rspdif.h
    \brief   definitions for the RSPDIF

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

#ifndef GD32H7XX_RSPDIF_H
#define GD32H7XX_RSPDIF_H

#include "gd32h7xx.h"

/* RSPDIF definitions */
#define RSPDIF                      RSPDIF_BASE                                     /*!< RSPDIF base address */

/* registers definitions */
#define RSPDIF_CTL                  REG32(RSPDIF + 0x00000000U)                     /*!< RSPDIF control register */
#define RSPDIF_INTEN                REG32(RSPDIF + 0x00000004U)                     /*!< RSPDIF interrupt enable register */
#define RSPDIF_STAT                 REG32(RSPDIF + 0x00000008U)                     /*!< RSPDIF status register */
#define RSPDIF_STATC                REG32(RSPDIF + 0x0000000CU)                     /*!< RSPDIF status flag clear register */
#define RSPDIF_DATA                 REG32(RSPDIF + 0x00000010U)                     /*!< RSPDIF RX data register */
#define RSPDIF_CHSTAT               REG32(RSPDIF + 0x00000014U)                     /*!< RSPDIF RX channel status register */
#define RSPDIF_DTH                  REG32(RSPDIF + 0x00000018U)                     /*!< RSPDIF RX data threshold register */

#define RSPDIF_DATA_F0              REG32(RSPDIF + 0x00000010U)                     /*!< RSPDIF RX data register fomat 0 */
#define RSPDIF_DATA_F1              REG32(RSPDIF + 0x00000010U)                     /*!< RSPDIF RX data register fomat 1 */
#define RSPDIF_DATA_F2              REG32(RSPDIF + 0x00000010U)                     /*!< RSPDIF RX data register fomat 2 */

/* bits definitions */
/* RSPDIF_CTL */
#define RSPDIF_CTL_RXCFG            BITS(0,1)                                       /*!< RSPDIF configuration */
#define RSPDIF_CTL_DMAREN           BIT(2)                                          /*!< RSPDIF receiver DMA enable for data flow */
#define RSPDIF_CTL_RXSTEOMEN        BIT(3)                                          /*!< RSPDIF RX stereo mode enable */
#define RSPDIF_CTL_RXDF             BITS(4,5)                                       /*!< RSPDIF RX data format selection */
#define RSPDIF_CTL_PNCPEN           BIT(6)                                          /*!< RSPDIF parity error bit no copy enable bit */
#define RSPDIF_CTL_VNCPEN           BIT(7)                                          /*!< RSPDIF validity bit no copy enable bit */
#define RSPDIF_CTL_CUNCPEN          BIT(8)                                          /*!< RSPDIF channel status and user bits no copy enable bit */
#define RSPDIF_CTL_PTNCPEN          BIT(9)                                          /*!< RSPDIF preamble type bits no copy enable bit */
#define RSPDIF_CTL_DMACBEN          BIT(10)                                         /*!< RSPDIF control buffer DMA enable for control flow */
#define RSPDIF_CTL_CFCHSEL          BIT(11)                                         /*!< RSPDIF the control flow acquires channel state source selection */
#define RSPDIF_CTL_MAXRT            BITS(12,13)                                     /*!< RSPDIF maximum number of retries allowed during the RSPDIF synchronization phase */
#define RSPDIF_CTL_WFRXA            BIT(14)                                         /*!< RSPDIF wait for the four valid transition signal of the selected RSPDIF channel */
#define RSPDIF_CTL_RXCHSEL          BITS(16,18)                                     /*!< RSPDIF input channel selection */
#define RSPDIF_CTL_SCKEN            BIT(20)                                         /*!< RSPDIF symbol clock enable */
#define RSPDIF_CTL_BKSCKEN          BIT(21)                                         /*!< RSPDIF backup symbol clock enable */

/* RSPDIF_INTEN */
#define RSPDIF_INTEN_RBNEIE         BIT(0)                                          /*!< RSPDIF_DATA register no empty interrupt enable */
#define RSPDIF_INTEN_CBNEIE         BIT(1)                                          /*!< RSPDIF_CHSTAT register no empty interrupt enable */
#define RSPDIF_INTEN_PERRIE         BIT(2)                                          /*!< RSPDIF parity error interrupt enable */
#define RSPDIF_INTEN_RXORERRIE      BIT(3)                                          /*!< RSPDIF RX overrun error interrupt enable */
#define RSPDIF_INTEN_SYNDBIE        BIT(4)                                          /*!< RSPDIF synchronization block detected interrupt enable */
#define RSPDIF_INTEN_SYNDOIE        BIT(5)                                          /*!< RSPDIF synchronization done interrupt enable */
#define RSPDIF_INTEN_RXDCERRIE      BIT(6)                                          /*!< RSPDIF data decoding error interrupt enable */

/* RSPDIF_STAT */
#define RSPDIF_STAT_RBNE            BIT(0)                                          /*!< RSPDIF_DATA register is not empty */
#define RSPDIF_STAT_CBNE            BIT(1)                                          /*!< RSPDIF_CHSTAT control buffer is not empty */
#define RSPDIF_STAT_PERR            BIT(2)                                          /*!< RSPDIF parity error */
#define RSPDIF_STAT_RXORERR         BIT(3)                                          /*!< RSPDIF RX overrun error */
#define RSPDIF_STAT_SYNDB           BIT(4)                                          /*!< RSPDIF synchronization block detected */
#define RSPDIF_STAT_SYNDO           BIT(5)                                          /*!< RSPDIF synchronization done */
#define RSPDIF_STAT_FRERR           BIT(6)                                          /*!< RSPDIF frame error */
#define RSPDIF_STAT_SYNERR          BIT(7)                                          /*!< RSPDIF synchronization error */
#define RSPDIF_STAT_TMOUTERR        BIT(8)                                          /*!< RSPDIF timeout error */
#define RSPDIF_STAT_CKCNT5          BITS(16,30)                                     /*!< the number of consecutive time clock cycles */

/* RSPDIF_STATC */
#define RSPDIF_STATC_PERRC          BIT(2)                                          /*!< RSPDIF clears the parity error flag */
#define RSPDIF_STATC_RXORERRC       BIT(3)                                          /*!< RSPDIF clears the RX overrun error flag */
#define RSPDIF_STATC_SYNDBC         BIT(4)                                          /*!< RSPDIF clears the synchronization block detected flag  */
#define RSPDIF_STATC_SYNDOC         BIT(5)                                          /*!< RSPDIF clears the synchronization done flag  */

/* RSPDIF_DATA */
/* RSPDIF_DATA_F0 */
#define RSPDIF_DATA_F0_DATA0        BITS(0,23)                                      /*!< data value */
#define RSPDIF_DATA_F0_P            BIT(24)                                         /*!< parity error bit */
#define RSPDIF_DATA_F0_V            BIT(25)                                         /*!< validity bit */
#define RSPDIF_DATA_F0_U            BIT(26)                                         /*!< user bit */
#define RSPDIF_DATA_F0_C            BIT(27)                                         /*!< channel status bit */
#define RSPDIF_DATA_F0_PREF         BITS(28,29)                                     /*!< preamble type */

/* RSPDIF_DATA_F1 */
#define RSPDIF_DATA_F1_P            BIT(0)                                          /*!< parity error bit */
#define RSPDIF_DATA_F1_V            BIT(1)                                          /*!< validity bit */
#define RSPDIF_DATA_F1_U            BIT(2)                                          /*!< user bit */
#define RSPDIF_DATA_F1_C            BIT(3)                                          /*!< channel status bit */
#define RSPDIF_DATA_F1_PREF         BITS(4,5)                                       /*!< preamble type */
#define RSPDIF_DATA_F1_DATA0        BITS(8,31)                                      /*!< data value */

/* RSPDIF_DATA_F2 */
#define RSPDIF_DATA_F2_DATA1        BITS(0,15)                                      /*!< steo mode: this field contains the channel B data\
                                                                                    mono mode: this field contains the more recent value */
#define RSPDIF_DATA_F2_DATA2        BITS(16,31)                                     /*!< steo mode: this field contains the channel A data\
                                                                                    mono mode: this field contains the oldest value */

/* RSPDIF_CHSTAT */
#define RSPDIF_CHSTAT_USER          BITS(0,15)                                      /*!< user data information */
#define RSPDIF_CHSTAT_CHS           BITS(16,23)                                     /*!< channel A status information */
#define RSPDIF_CHSTAT_SOB           BIT(24)                                         /*!< start of block */

/* RSPDIF_DTH */
#define RSPDIF_DTH_THHI             BITS(0,12)                                      /*!< high threshold */
#define RSPDIF_DTH_THLO             BITS(16,28)                                     /*!< low threshold */

/* constants definitions */
/* RSPDIF initialization parameter structure definitions */
typedef struct {
    uint32_t input_sel;                                                             /*!< the RSPDIF input selection */
    uint32_t max_retrie;                                                            /*!< the RSPDIF maximum allowed re-tries during synchronization phase */
    uint32_t wait_activity;                                                         /*!< the RSPDIF wait for activity on the selected input */
    uint32_t channel_sel;                                                           /*!< whether swapping the channel status from channel A or B */
    uint32_t sample_format;                                                         /*!< the RSPDIF data samples format (LSB, MSB, ...) */
    uint32_t sound_mode;                                                            /*!< the RSPDIF is in stereo or mono mode */
    uint32_t pre_type;                                                              /*!< whether opy the preamble type value into the RSPDIF_DATA */
    uint32_t channel_status_bit;                                                    /*!< whether the channel status and user bits are copied or not into the received frame */
    uint32_t validity_bit;                                                          /*!< whether the validity bit is copied or not into the received frame */
    uint32_t parity_error_bit;                                                      /*!< whether the parity error bit is copied or not into the received frame */
    uint32_t symbol_clk;                                                            /*!< the RSPDIF symbol clock generation */
    uint32_t bak_symbol_clk;                                                        /*!< the RSPDIF backup symbol clock generation */
} rspdif_parameter_struct;

/* RSPDIF data parameter structure definitions */
typedef struct {
    uint32_t format;                                                                /*!< the data dormat */
    uint32_t preamble;                                                              /*!< the preamble type */
    uint32_t channel_status;                                                        /*!< channel status bit */
    uint32_t user_bit;                                                              /*!< user bit */
    uint32_t validity;                                                              /*!< validity bit */
    uint32_t parity_err;                                                            /*!< parity error bit */
    uint32_t data0;                                                                 /*!< data value 0 */
    uint32_t data1;                                                                 /*!< data value 1 */
} rspdif_data_struct;

/* RSPDIF configuration */
#define CTL_RXCFG(regval)                   (BITS(0,1) & ((uint32_t)(regval)))
#define RSPDIF_STATE_IDLE                   CTL_RXCFG(0)                            /*!< disable RSPDIF */
#define RSPDIF_STATE_SYNC                   CTL_RXCFG(1)                            /*!< enable RSPDIF synchronization only */
#define RSPDIF_STATE_RCV                    CTL_RXCFG(3)                            /*!< enable RSPDIF */

/* RX stereo mode enable */
#define RSPDIF_STEREOMODE_DISABLE           ((uint32_t)0x00000000U)                 /*!< MONO mode */
#define RSPDIF_STEREOMODE_ENABLE            ((uint32_t)RSPDIF_CTL_RXSTEOMEN)        /*!< STEREO mode */

/* RX data format selection */
#define CTL_RXDF(regval)                    (BITS(4,5) & ((uint32_t)(regval) << 4))
#define RSPDIF_DATAFORMAT_LSB               CTL_RXDF(0)                             /*!< the data format is described in the RSPDIF_DATA_F0 register, audio data is right aligned (LSB) */
#define RSPDIF_DATAFORMAT_MSB               CTL_RXDF(1)                             /*!< the data format is described in the RSPDIF_DATA_F1 register, audio data is left aligned (MSB) */
#define RSPDIF_DATAFORMAT_32BITS            CTL_RXDF(2)                             /*!< the data format is described in the RSPDIF_DATA_F2 register, which packs two 16-bit audio data into one 32-bit data */

/* whether copy preamble type bit into RSPDIF_DATA */
#define RSPDIF_PREAMBLE_TYPE_MASK_OFF       ((uint32_t)0x00000000U)                 /*!< copy the preamble type bit into the RSPDIF_DATA */
#define RSPDIF_PREAMBLE_TYPE_MASK_ON        ((uint32_t)RSPDIF_CTL_PTNCPEN)          /*!< do not copy the preamble type bit into the RSPDIF_DATA, but write 0 instead */

/* whether copy channel status and user bits into RSPDIF_DATA */
#define RSPDIF_CHANNEL_STATUS_MASK_OFF      ((uint32_t)0x00000000U)                 /*!< copy the channel status and user bit into the RSPDIF_DATA */
#define RSPDIF_CHANNEL_STATUS_MASK_ON       ((uint32_t)RSPDIF_CTL_CUNCPEN)          /*!< do not copy the channel status and user bit into the RSPDIF_DATA, but write 0 instead */

/* whether copy validity bit into RSPDIF_DATA */
#define RSPDIF_VALIDITY_MASK_OFF            ((uint32_t)0x00000000U)                 /*!< copy the validity bit into the RSPDIF_DATA */
#define RSPDIF_VALIDITY_MASK_ON             ((uint32_t)RSPDIF_CTL_VNCPEN)           /*!< do not copy the validity bit into the RSPDIF_DATA, but write 0 instead */

/* whether copy parity error bit into RSPDIF_DATA */
#define RSPDIF_PERROR_MASK_OFF        ((uint32_t)0x00000000U)                 /*!< copy the parity error bit into the RSPDIF_DATA */
#define RSPDIF_PERROR_MASK_ON         ((uint32_t)RSPDIF_CTL_PNCPEN)           /*!< do not copy the parity error bit into the RSPDIF_DATA, but write 0 instead */

/* maximum number of retries allowed during the RSPDIF synchronization */
#define CTL_MAXRT(regval)                   (BITS(12,13) & ((uint32_t)(regval) << 12))
#define RSPDIF_MAXRETRIES_NONE              CTL_MAXRT(0)                           /*!< no retry */
#define RSPDIF_MAXRETRIES_3                 CTL_MAXRT(1)                           /*!< allow up to 3 retries */
#define RSPDIF_MAXRETRIES_15                CTL_MAXRT(2)                           /*!< allow up to 15 retries */
#define RSPDIF_MAXRETRIES_63                CTL_MAXRT(3)                           /*!< allow up to 63 retries */

/* wait for the four valid transition signal of the selected RSPDIF channel */
#define RSPDIF_WAIT_FOR_ACTIVITY_OFF        ((uint32_t)0x00000000U)                 /*!< RSPDIF does not wait for the valid conversion signal from the selected RSPDIF channel */
#define RSPDIF_WAIT_FOR_ACTIVITY_ON         ((uint32_t)RSPDIF_CTL_WFRXA)            /*!< RSPDIF wait for the valid conversion signal from the selected RSPDIF channel */

/* input channel selection */
#define CTL_RXCHSEL(regval)                 (BITS(16,18) & ((uint32_t)(regval) << 16))
#define RSPDIF_INPUT_IN0                    CTL_RXCHSEL(0)                          /*!< RSPDIF_CH0 selected */
#define RSPDIF_INPUT_IN1                    CTL_RXCHSEL(1)                          /*!< RSPDIF_CH1 selected */
#define RSPDIF_INPUT_IN2                    CTL_RXCHSEL(2)                          /*!< RSPDIF_CH2 selected */
#define RSPDIF_INPUT_IN3                    CTL_RXCHSEL(3)                          /*!< RSPDIF_CH3 selected */

/* symbol clock enable */
#define RSPDIF_SYMBOL_CLK_OFF               ((uint32_t)0x00000000U)                 /*!< the RSPDIF does not generate a symbol clock */
#define RSPDIF_SYMBOL_CLK_ON                RSPDIF_CTL_SCKEN                        /*!< the RSPDIF generates a symbol clock */

/* backup symbol clock enable */
#define RSPDIF_BACKUP_SYMBOL_CLK_OFF        ((uint32_t)0x00000000U)                 /*!< the RSPDIF does not generate a backup symbol clock */
#define RSPDIF_BACKUP_SYMBOL_CLK_ON         RSPDIF_CTL_BKSCKEN                      /*!< the RSPDIF generates a backup symbol clock if SCKEN = 1 */

/* the control flow acquires channel state source selection */
#define RSPDIF_CHANNEL_A                    ((uint32_t)0x00000000U)                 /*!< gets channel status from channel A */
#define RSPDIF_CHANNEL_B                    ((uint32_t)RSPDIF_CTL_CFCHSEL)          /*!< gets channel status from channel B */

/* RSPDIF preamble type */
#define RSPDIF_PREAMBLE_NONE                ((uint32_t)0x00000000U)                 /*!< RSPDIF preamble received not used */
#define RSPDIF_PREAMBLE_B                   ((uint32_t)0x00000001U)                 /*!< RSPDIF Preamble B received */
#define RSPDIF_PREAMBLE_M                   ((uint32_t)0x00000002U)                 /*!< RSPDIF Preamble M received */
#define RSPDIF_PREAMBLE_W                   ((uint32_t)0x00000003U)                 /*!< RSPDIF Preamble W received */

/* RSPDIF interrupt enable or disable constants definitions */
#define RSPDIF_INT_RBNE                     RSPDIF_INTEN_RBNEIE                     /*!< RSPDIF RX buffer no empty interrupt enable */
#define RSPDIF_INT_CBNE                     RSPDIF_INTEN_CBNEIE                     /*!< RSPDIF RX control buffer no empty interrupt enable */
#define RSPDIF_INT_PERR                     RSPDIF_INTEN_PERRIE                     /*!< RSPDIF parity error interrupt enable */
#define RSPDIF_INT_RXORERR                  RSPDIF_INTEN_RXORERRIE                  /*!< RSPDIF RX overrun error interrupt enable */
#define RSPDIF_INT_SYNDB                    RSPDIF_INTEN_SYNDBIE                    /*!< RSPDIF synchronization block detected interrupt enable */
#define RSPDIF_INT_SYNDO                    RSPDIF_INTEN_SYNDOIE                    /*!< RSPDIF synchronization done interrupt enable */
#define RSPDIF_INT_RXDCERR                  RSPDIF_INTEN_RXDCERRIE                  /*!< RSPDIF data decoding error interrupt enable */

/* RSPDIF flags */
#define RSPDIF_FLAG_RBNE                    RSPDIF_STAT_RBNE                        /*!< RSPDIF RX buffer is not empty */
#define RSPDIF_FLAG_CBNE                    RSPDIF_STAT_CBNE                        /*!< RSPDIF RX control buffer is not empty */
#define RSPDIF_FLAG_PERR                    RSPDIF_STAT_PERR                        /*!< RSPDIF parity error */
#define RSPDIF_FLAG_RXORERR                 RSPDIF_STAT_RXORERR                     /*!< RSPDIF RX overrun error */
#define RSPDIF_FLAG_SYNDB                   RSPDIF_STAT_SYNDB                       /*!< RSPDIF synchronization block detected */
#define RSPDIF_FLAG_SYNDO                   RSPDIF_STAT_SYNDO                       /*!< RSPDIF synchronization done */
#define RSPDIF_FLAG_FRERR                   RSPDIF_STAT_FRERR                       /*!< RSPDIF frame error */
#define RSPDIF_FLAG_SYNERR                  RSPDIF_STAT_SYNERR                      /*!< RSPDIF synchronization error */
#define RSPDIF_FLAG_TMOUTERR                RSPDIF_STAT_TMOUTERR                    /*!< RSPDIF time out error */

/* RSPDIF interrupt flags */
#define RSPDIF_INT_FLAG_RBNE                RSPDIF_STAT_RBNE                        /*!< RSPDIF RX buffer no empty interrupt flag */
#define RSPDIF_INT_FLAG_CBNE                RSPDIF_STAT_CBNE                        /*!< RSPDIF RX control buffer no empty interrupt flag */
#define RSPDIF_INT_FLAG_PERR                RSPDIF_STAT_PERR                        /*!< RSPDIF parity error interrupt flag */
#define RSPDIF_INT_FLAG_RXORERR             RSPDIF_STAT_RXORERR                     /*!< RSPDIF RX overrun error interrupt flag */
#define RSPDIF_INT_FLAG_SYNDB               RSPDIF_STAT_SYNDB                       /*!< RSPDIF synchronization block detected interrupt flag */
#define RSPDIF_INT_FLAG_SYNDO               RSPDIF_STAT_SYNDO                       /*!< RSPDIF synchronization done interrupt flag */
#define RSPDIF_INT_FLAG_FRERR               RSPDIF_STAT_FRERR                       /*!< RSPDIF frame error interrupt flag */
#define RSPDIF_INT_FLAG_SYNERR              RSPDIF_STAT_SYNERR                      /*!< RSPDIF synchronization error interrupt flag */
#define RSPDIF_INT_FLAG_TMOUTERR            RSPDIF_STAT_TMOUTERR                    /*!< RSPDIF time out error interrupt flag */

/* function declarations */
/* RSPDIF deinitialization and initialization functions */
/* reset the RSPDIF */
void rspdif_deinit(void);
/* initialize the parameters of RSPDIF structure with the default values */
void rspdif_struct_para_init(rspdif_parameter_struct *rspdif_struct);
/* initialize the RSPDIF parameters */
void rspdif_init(rspdif_parameter_struct *rspdif_struct);
/* specifies the RSPDIF peripheral state */
void rspdif_enable(uint32_t mode);
/* disable RSPDIF */
void rspdif_disable(void);

/* symbol clock functions */
/* enable RSPDIF symbol clock */
void rspdif_symbol_clock_enable(void);
/* disable RSPDIF symbol clock */
void rspdif_symbol_clock_disable(void);
/* enable RSPDIF backup symbol clock */
void rspdif_backup_symbol_clock_enable(void);
/* disable RSPDIF backup symbol clock */
void rspdif_backup_symbol_clock_disable(void);

/* DMA functions */
/* enable the RSPDIF receiver DMA */
void rspdif_dma_enable(void);
/* disable the RSPDIF receiver DMA */
void rspdif_dma_disable(void);
/* enable the RSPDIF control buffer DMA */
void rspdif_control_buffer_dma_enable(void);
/* disable the RSPDIF control buffer DMA */
void rspdif_control_buffer_dma_disable(void);

/* transfer function */
/* RSPDIF read data */
void rspdif_data_read(rspdif_data_struct *data_struct);

/* information acquisition functions */
/* get duration of 5 symbols counted using rspdif_ck */
uint32_t rspdif_duration_of_symbols_get(void);
/* get user data information */
uint32_t rspdif_user_data_get(void);
/* get channel status information */
uint32_t rspdif_channel_status_get(void);
/* get start of block */
FlagStatus rspdif_start_block_status_get(void);
/* get threshold low estimation */
uint32_t rspdif_low_threshold_get(void);
/* get threshold high estimation */
uint32_t rspdif_high_threshold_get(void);

/* flag and interrupt functions */
/* get RSPDIF flag status */
FlagStatus rspdif_flag_get(uint16_t flag);
/* clear RSPDIF flag */
void rspdif_flag_clear(uint16_t flag);
/* enable RSPDIF interrupt */
void rspdif_interrupt_enable(uint8_t interrupt);
/* disable RSPDIF interrupt */
void rspdif_interrupt_disable(uint8_t interrupt);
/* get RSPDIF interrupt flag status */
FlagStatus rspdif_interrupt_flag_get(uint16_t int_flag);
/* clear RSPDIF interrupt flag status */
void rspdif_interrupt_flag_clear(uint16_t int_flag);

#endif /* GD32H7XX_RSPDIF_H */
