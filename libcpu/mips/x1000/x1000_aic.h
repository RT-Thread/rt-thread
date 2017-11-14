/**
  ******************************************************************************
  * @file    x1000_aic.h
  * @author  Urey
  * @version V1.0.0
  * @date    2017Äê2ÔÂ20ÈÕ
  * @brief   TODO
  ******************************************************************************         
**/ 


#ifndef _X1000_AIC_H_
#define _X1000_AIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#define AIC_FR      (AIC_BASE + 0x00)
#define AIC_CR      (AIC_BASE + 0x04)
#define AIC_ACCR1   (AIC_BASE + 0x08)
#define AIC_ACCR2   (AIC_BASE + 0x0c)
#define AIC_I2SCR   (AIC_BASE + 0x10)
#define AIC_SR      (AIC_BASE + 0x14)
#define AIC_ACSR    (AIC_BASE + 0x18)
#define AIC_I2SSR   (AIC_BASE + 0x1c)
#define AIC_ACCAR   (AIC_BASE + 0x20)
#define AIC_ACCDR   (AIC_BASE + 0x24)
#define AIC_ACSAR   (AIC_BASE + 0x28)
#define AIC_ACSDR   (AIC_BASE + 0x2c)
#define AIC_I2SDIV  (AIC_BASE + 0x30)
#define AIC_DR      (AIC_BASE + 0x34)

#define SPDIF_ENA   (AIC_BASE + 0x80)
#define SPDIF_CTRL  (AIC_BASE + 0x84)
#define SPDIF_STATE (AIC_BASE + 0x88)
#define SPDIF_CFG1  (AIC_BASE + 0x8c)
#define SPDIF_CFG2  (AIC_BASE + 0x90)
#define SPDIF_FIFO  (AIC_BASE + 0x94)

#define ICDC_CKCFG  (AIC_BASE + 0xa0)
#define ICDC_RGADW  (AIC_BASE + 0xa4)
#define ICDC_RGDATA (AIC_BASE + 0xa8)


/* AIC_FR definition */
#define AIC_FR_RFTH_LSB     24
#define AIC_FR_RFTH(x)  ( ( (x)/2 - 1 ) << AIC_FR_RFTH_LSB)     // 2, 4, ..., 32
#define AIC_FR_RFTH_MASK    BITS_H2L(27, AIC_FR_RFTH_LSB)

#define AIC_FR_TFTH_LSB     16
#define AIC_FR_TFTH(x)      ( ( (x)/2 ) << AIC_FR_TFTH_LSB)     // 2, 4, ..., 32
#define AIC_FR_TFTH_MASK    BITS_H2L(20, AIC_FR_TFTH_LSB)

/* new@4770 */
#define AIC_FR_IBCKD        BIT10

/* new@4770 */
#define AIC_FR_ISYNCD       BIT9

/* new@4770 */
#define IC_FR_DMODE     BIT8

#define AIC_FR_LSMP     BIT6
#define AIC_FR_ICDC     BIT5
#define AIC_FR_AUSEL        BIT4
#define AIC_FR_RST      BIT3
#define AIC_FR_BCKD     BIT2
#define AIC_FR_SYNCD        BIT1
#define AIC_FR_ENB      BIT0


/* AIC_CR definition */
#define AIC_CR_PACK16       BIT28

#define AIC_CR_CHANNEL_LSB  24
#define AIC_CR_CHANNEL_MASK BITS_H2L(26, 24)
#define AIC_CR_CHANNEL_MONO   (0x0 << AIC_CR_CHANNEL_LSB)
#define AIC_CR_CHANNEL_STEREO (0x1 << AIC_CR_CHANNEL_LSB)
#define AIC_CR_CHANNEL_4CHNL  (0x3 << AIC_CR_CHANNEL_LSB)
#define AIC_CR_CHANNEL_6CHNL  (0x5 << AIC_CR_CHANNEL_LSB)
#define AIC_CR_CHANNEL_8CHNL  (0x7 << AIC_CR_CHANNEL_LSB)

#define AIC_CR_OSS_LSB      19
#define AIC_CR_OSS_MASK     BITS_H2L(21, AIC_CR_OSS_LSB)
#define AIC_CR_OSS(n)       (((n) > 18 ? (n)/6 : (n)/9) << AIC_CR_OSS_LSB)  /* n = 8, 16, 18, 20, 24 */

#define AIC_CR_ISS_LSB      16
#define AIC_CR_ISS_MASK     BITS_H2L(18, AIC_CR_ISS_LSB)
#define AIC_CR_ISS(n)       (((n) > 18 ? (n)/6 : (n)/9) << AIC_CR_ISS_LSB)  /* n = 8, 16, 18, 20, 24 */

#define AIC_CR_RDMS     BIT15
#define AIC_CR_TDMS     BIT14
#define AIC_CR_M2S      BIT11
#define AIC_CR_ENDSW        BIT10
#define AIC_CR_AVSTSU       BIT9
#define AIC_CR_TFLUSH       BIT8
#define AIC_CR_RFLUSH       BIT7
#define AIC_CR_EROR     BIT6
#define AIC_CR_ETUR     BIT5
#define AIC_CR_ERFS     BIT4
#define AIC_CR_ETFS     BIT3
#define AIC_CR_ENLBF        BIT2
#define AIC_CR_ERPL     BIT1
#define AIC_CR_EREC     BIT0

/* AIC controller AC-link control register 1(ACCR1) */
#define AIC_ACCR1_RS_LSB    16
#define AIC_ACCR1_RS_MASK   BITS_H2L(25, AIC_ACCR1_RS_LSB)
#define AIC_ACCR1_RS_SLOT(n)    ((1 << ((n) - 3)) << AIC_ACCR1_RS_LSB)  /* n = 3 .. 12 */

#define AIC_ACCR1_XS_LSB    0
#define AIC_ACCR1_XS_MASK   BITS_H2L(9, AIC_ACCR1_XS_LSB)
#define AIC_ACCR1_XS_SLOT(n)    ((1 << ((n) - 3)) << AIC_ACCR1_XS_LSB)  /* n = 3 .. 12 */

/* AIC controller AC-link control register 2 (ACCR2) */
#define AIC_ACCR2_ERSTO     BIT18
#define AIC_ACCR2_ESADR     BIT17
#define AIC_ACCR2_ECADT     BIT16
#define AIC_ACCR2_SO        BIT3
#define AIC_ACCR2_SR        BIT2
#define AIC_ACCR2_SS        BIT1
#define AIC_ACCR2_SA        BIT0

/* AIC controller i2s/msb-justified control register (I2SCR) */
#define AIC_I2SCR_RFIRST    BIT17
#define AIC_I2SCR_SWLH      BIT16
#define AIC_I2SCR_ISTPBK    BIT13
#define AIC_I2SCR_STPBK     BIT12
#define AIC_I2SCR_ESCLK     BIT4
#define AIC_I2SCR_AMSL      BIT0

/* AIC controller FIFO status register (AICSR) */
#define AIC_SR_RFL_LSB      24
#define AIC_SR_RFL_MASK     BITS_H2L(29, AIC_SR_RFL_LSB)

#define AIC_SR_TFL_LSB      8
#define AIC_SR_TFL_MASK     BITS_H2L(13, AIC_SR_TFL_LSB)

#define AIC_SR_ROR      BIT6
#define AIC_SR_TUR      BIT5
#define AIC_SR_RFS      BIT4
#define AIC_SR_TFS      BIT3

/* AIC controller AC-link status register (ACSR) */
#define AIC_ACSR_SLTERR     BIT21
#define AIC_ACSR_CRDY       BIT20
#define AIC_ACSR_CLPM       BIT19
#define AIC_ACSR_RSTO       BIT18
#define AIC_ACSR_SADR       BIT17
#define AIC_ACSR_CADT       BIT16

/* AIC controller I2S/MSB-justified status register (I2SSR) */
#define AIC_I2SSR_CHBSY     BIT5
#define AIC_I2SSR_TBSY      BIT4
#define AIC_I2SSR_RBSY      BIT3
#define AIC_I2SSR_BSY       BIT2

/* AIC controller AC97 codec command address register (ACCAR) */
#define AIC_ACCAR_CAR_LSB   0
#define AIC_ACCAR_CAR_MASK  BITS_H2L(19, AIC_ACCAR_CAR_LSB)


/* AIC controller AC97 codec command data register (ACCDR) */
#define AIC_ACCDR_CDR_LSB   0
#define AIC_ACCDR_CDR_MASK  BITS_H2L(19, AIC_ACCDR_CDR_LSB)

/* AC97 read and write macro based on ACCAR and ACCDR */
#define AC97_READ_CMD       BIT19
#define AC97_WRITE_CMD      (BIT19 & ~BIT19)

#define AC97_INDEX_LSB      12
#define AC97_INDEX_MASK     BITS_H2L(18, AC97_INDEX_LSB)

#define AC97_DATA_LSB       4
#define AC97_DATA_MASK      BITS_H2L(19, AC97_DATA_LSB)

/* AIC controller AC97 codec status address register (ACSAR) */
#define AIC_ACSAR_SAR_LSB   0
#define AIC_ACSAR_SAR_MASK  BITS_H2L(19, AIC_ACSAR_SAR_LSB)

/* AIC controller AC97 codec status data register (ACSDR) */
#define AIC_ACSDR_SDR_LSB   0
#define AIC_ACSDR_SDR_MASK  BITS_H2L(19, AIC_ACSDR_SDR_LSB)

/* AIC controller I2S/MSB-justified clock divider register (I2SDIV) */
#define AIC_I2SDIV_IDIV_LSB 16
#define AIC_I2SDIV_IDIV_MASK    BITS_H2L(24, AIC_I2SDIV_IDIV_LSB)
#define AIC_I2SDIV_DIV_LSB  0
#define AIC_I2SDIV_DIV_MASK BITS_H2L(8, AIC_I2SDIV_DIV_LSB)

/* SPDIF enable register (SPDIF_ENA) */
#define SPDIF_ENA_SPEN      BIT0

/* SPDIF control register (SPDIF_CTRL) */
#define SPDIF_CTRL_DMAEN        BIT15
#define SPDIF_CTRL_DTYPE        BIT14
#define SPDIF_CTRL_SIGN         BIT13
#define SPDIF_CTRL_INVALID      BIT12
#define SPDIF_CTRL_RST          BIT11
#define SPDIF_CTRL_SPDIFI2S     BIT10
#define SPDIF_CTRL_MTRIG        BIT1
#define SPDIF_CTRL_MFFUR        BIT0

/* SPDIF state register (SPDIF_STAT) */
#define SPDIF_STAT_BUSY     BIT7
#define SPDIF_STAT_FTRIG    BIT1
#define SPDIF_STAT_FUR      BIT0

#define SPDIF_STAT_FLVL_LSB 8
#define SPDIF_STAT_FLVL_MASK    BITS_H2L(14, SPDIF_STAT_FLVL_LSB)

/* SPDIF configure 1 register (SPDIF_CFG1) */
#define SPDIF_CFG1_INITLVL  BIT17
#define SPDIF_CFG1_ZROVLD   BIT16

#define SPDIF_CFG1_TRIG_LSB 12
#define SPDIF_CFG1_TRIG_MASK    BITS_H2L(13, SPDIF_CFG1_TRIG_LSB)
#define SPDIF_CFG1_TRIG(n)  (((n) > 16 ? 3 : (n)/8) << SPDIF_CFG1_TRIG_LSB) /* n = 4, 8, 16, 32 */

#define SPDIF_CFG1_SRCNUM_LSB   8
#define SPDIF_CFG1_SRCNUM_MASK  BITS_H2L(11, SPDIF_CFG1_SRCNUM_LSB)

#define SPDIF_CFG1_CH1NUM_LSB   4
#define SPDIF_CFG1_CH1NUM_MASK  BITS_H2L(7, SPDIF_CFG1_CH1NUM_LSB)

#define SPDIF_CFG1_CH2NUM_LSB   0
#define SPDIF_CFG1_CH2NUM_MASK  BITS_H2L(3, SPDIF_CFG1_CH2NUM_LSB)

/* SPDIF configure 2 register (SPDIF_CFG2) */
#define SPDIF_CFG2_MAXWL    BIT18
#define SPDIF_CFG2_PRE      BIT3
#define SPDIF_CFG2_COPYN    BIT2
#define SPDIF_CFG2_AUDION   BIT1
#define SPDIF_CFG2_CONPRO   BIT0

#define SPDIF_CFG2_FS_LSB   26
#define SPDIF_CFG2_FS_MASK  BITS_H2L(29, SPDIF_CFG2_FS_LSB)

#define SPDIF_CFG2_ORGFRQ_LSB   22
#define SPDIF_CFG2_ORGFRQ_MASK  BITS_H2L(25, SPDIF_CFG2_ORGFRQ_LSB)

#define SPDIF_CFG2_SAMWL_LSB    19
#define SPDIF_CFG2_SAMWL_MASK   BITS_H2L(21, SPDIF_CFG2_SAMWL_LSB)

#define SPDIF_CFG2_CLKACU_LSB   16
#define SPDIF_CFG2_CLKACU_MASK  BITS_H2L(17, SPDIF_CFG2_CLKACU_LSB)

#define SPDIF_CFG2_CATCODE_LSB  8
#define SPDIF_CFG2_CATCODE_MASK BITS_H2L(15, SPDIF_CFG2_CATCODE_LSB)

#define SPDIF_CFG2_CHMD_LSB 6
#define SPDIF_CFG2_CHMD_MASK    BITS_H2L(7, SPDIF_CFG2_CHMD_LSB)

/* ICDC internal register access control register(RGADW) */
#define ICDC_RGADW_RGWR     BIT16

#define ICDC_RGADW_RGADDR_LSB   8
#define ICDC_RGADW_RGADDR_MASK  BITS_H2L(14, ICDC_RGADW_RGADDR_LSB)

#define ICDC_RGADW_RGDIN_LSB    0
#define ICDC_RGADW_RGDIN_MASK   BITS_H2L(7, ICDC_RGADW_RGDIN_LSB)


/* ICDC internal register data output register (RGDATA)*/
#define ICDC_RGDATA_IRQ     BIT8

#define ICDC_RGDATA_RGDOUT_LSB  0
#define ICDC_RGDATA_RGDOUT_MASK BITS_H2L(7, ICDC_RGDATA_RGDOUT_LSB)


#ifndef __MIPS_ASSEMBLER


#define REG_AIC_FR      REG32(AIC_FR)
#define REG_AIC0_FR     REG32(AIC0_FR)
#define REG_AIC_CR      REG32(AIC_CR)
#define REG_AIC_ACCR1       REG32(AIC_ACCR1)
#define REG_AIC_ACCR2       REG32(AIC_ACCR2)
#define REG_AIC_I2SCR       REG32(AIC_I2SCR)
#define REG_AIC_SR      REG32(AIC_SR)
#define REG_AIC_ACSR        REG32(AIC_ACSR)
#define REG_AIC_I2SSR       REG32(AIC_I2SSR)
#define REG_AIC_ACCAR       REG32(AIC_ACCAR)
#define REG_AIC_ACCDR       REG32(AIC_ACCDR)
#define REG_AIC_ACSAR       REG32(AIC_ACSAR)
#define REG_AIC_ACSDR       REG32(AIC_ACSDR)
#define REG_AIC_I2SDIV      REG32(AIC_I2SDIV)
#define REG_AIC_DR      REG32(AIC_DR)

#define REG_SPDIF_ENA       REG32(SPDIF_ENA)
#define REG_SPDIF_CTRL      REG32(SPDIF_CTRL)
#define REG_SPDIF_STATE     REG32(SPDIF_STATE)
#define REG_SPDIF_CFG1      REG32(SPDIF_CFG1)
#define REG_SPDIF_CFG2      REG32(SPDIF_CFG2)
#define REG_SPDIF_FIFO      REG32(SPDIF_FIFO)

#define REG_ICDC_RGADW      REG32(ICDC_RGADW)
#define REG_ICDC_RGDATA     REG32(ICDC_RGDATA)

#if 0
#define __aic_enable()      ( REG_AIC_FR |= AIC_FR_ENB )
#define __aic_disable()     ( REG_AIC_FR &= ~AIC_FR_ENB )

#define __aic_select_ac97() ( REG_AIC_FR &= ~AIC_FR_AUSEL )
#define __aic_select_i2s()  ( REG_AIC_FR |= AIC_FR_AUSEL )

#define __aic_play_zero()   ( REG_AIC_FR &= ~AIC_FR_LSMP )
#define __aic_play_lastsample() ( REG_AIC_FR |= AIC_FR_LSMP )

#define __i2s_as_master()   ( REG_AIC_FR |= AIC_FR_BCKD | AIC_FR_SYNCD )
#define __i2s_as_slave()    ( REG_AIC_FR &= ~(AIC_FR_BCKD | AIC_FR_SYNCD) )

#define jz_aic_ibck_in      (CLRREG32(AIC_FR, AIC_FR_IBCKD))
#define jz_aic_ibck_out     (SETREG32(AIC_FR, AIC_FR_IBCKD))

#define jz_aic_isync_in     (CLRREG32(AIC_FR, AIC_FR_ISYNCD))
#define jz_aic_isync_out    (SETREG32(AIC_FR, AIC_FR_ISYNCD))

#define jz_aic_enable_dmode (SETREG32(AIC_FR, AIC_FR_DMODE))
#define jz_aic_disable_dmode    (CLRREG32(AIC_FR, AIC_FR_DMODE))

#define __aic_reset_status()          ( REG_AIC_FR & AIC_FR_RST )

#define __aic_reset()                                   \
do {                                                    \
        REG_AIC_FR |= AIC_FR_RST;                       \
} while(0)


#define __aic_set_transmit_trigger(n)           \
do {                            \
    REG_AIC_FR &= ~AIC_FR_TFTH_MASK;        \
    REG_AIC_FR |= ((n) << AIC_FR_TFTH_LSB);     \
} while(0)

#define __aic_set_receive_trigger(n)            \
do {                            \
    REG_AIC_FR &= ~AIC_FR_RFTH_MASK;        \
    REG_AIC_FR |= ((n) << AIC_FR_RFTH_LSB);     \
} while(0)

#define __aic_enable_oldstyle()
#define __aic_enable_newstyle()
#define __aic_enable_pack16()   ( REG_AIC_CR |= AIC_CR_PACK16 )
#define __aic_enable_unpack16() ( REG_AIC_CR &= ~AIC_CR_PACK16)

#define jz_aic_set_channel(n)                       \
    do {                                \
        switch((n)) {                       \
        case 1:                         \
        case 2:                         \
        case 4:                         \
        case 6:                         \
        case 8:                         \
            CLRREG32(AIC_CR, AIC_CR_CHANNEL_MASK);      \
            SETREG32(AIC_CR, ((((n) - 1) << 24) & AIC_CR_CHANNEL_MASK)); \
            break;                      \
        default:                        \
            printk("invalid aic channel, must be 1, 2, 4, 6, or 8\n"); \
            break;                      \
        }                           \
    } while(0)

/* n = AIC_CR_CHANNEL_MONO,AIC_CR_CHANNEL_STEREO ... */
#define __aic_out_channel_select(n)                    \
do {                                                   \
    REG_AIC_CR &= ~AIC_CR_CHANNEL_MASK;            \
        REG_AIC_CR |= ((n) << AIC_CR_CHANNEL_LSB );                \
} while(0)

#define __aic_enable_record()   ( REG_AIC_CR |= AIC_CR_EREC )
#define __aic_disable_record()  ( REG_AIC_CR &= ~AIC_CR_EREC )
#define __aic_enable_replay()   ( REG_AIC_CR |= AIC_CR_ERPL )
#define __aic_disable_replay()  ( REG_AIC_CR &= ~AIC_CR_ERPL )
#define __aic_enable_loopback() ( REG_AIC_CR |= AIC_CR_ENLBF )
#define __aic_disable_loopback() ( REG_AIC_CR &= ~AIC_CR_ENLBF )

#define __aic_flush_tfifo() ( REG_AIC_CR |= AIC_CR_TFLUSH )
#define __aic_unflush_tfifo()   ( REG_AIC_CR &= ~AIC_CR_TFLUSH )
#define __aic_flush_rfifo() ( REG_AIC_CR |= AIC_CR_RFLUSH )
#define __aic_unflush_rfifo()   ( REG_AIC_CR &= ~AIC_CR_RFLUSH )

#define __aic_enable_transmit_intr() \
  ( REG_AIC_CR |= (AIC_CR_ETFS | AIC_CR_ETUR) )
#define __aic_disable_transmit_intr() \
  ( REG_AIC_CR &= ~(AIC_CR_ETFS | AIC_CR_ETUR) )
#define __aic_enable_receive_intr() \
  ( REG_AIC_CR |= (AIC_CR_ERFS | AIC_CR_EROR) )
#define __aic_disable_receive_intr() \
  ( REG_AIC_CR &= ~(AIC_CR_ERFS | AIC_CR_EROR) )

#define __aic_enable_transmit_dma()  ( REG_AIC_CR |= AIC_CR_TDMS )
#define __aic_disable_transmit_dma() ( REG_AIC_CR &= ~AIC_CR_TDMS )
#define __aic_enable_receive_dma()   ( REG_AIC_CR |= AIC_CR_RDMS )
#define __aic_disable_receive_dma()  ( REG_AIC_CR &= ~AIC_CR_RDMS )

#define __aic_enable_mono2stereo()   ( REG_AIC_CR |= AIC_CR_M2S )
#define __aic_disable_mono2stereo()  ( REG_AIC_CR &= ~AIC_CR_M2S )
#define __aic_enable_byteswap()      ( REG_AIC_CR |= AIC_CR_ENDSW )
#define __aic_disable_byteswap()     ( REG_AIC_CR &= ~AIC_CR_ENDSW )
#define __aic_enable_unsignadj()     ( REG_AIC_CR |= AIC_CR_AVSTSU )
#define __aic_disable_unsignadj()    ( REG_AIC_CR &= ~AIC_CR_AVSTSU )

#define AC97_PCM_XS_L_FRONT     AIC_ACCR1_XS_SLOT(3)
#define AC97_PCM_XS_R_FRONT     AIC_ACCR1_XS_SLOT(4)
#define AC97_PCM_XS_CENTER      AIC_ACCR1_XS_SLOT(6)
#define AC97_PCM_XS_L_SURR      AIC_ACCR1_XS_SLOT(7)
#define AC97_PCM_XS_R_SURR      AIC_ACCR1_XS_SLOT(8)
#define AC97_PCM_XS_LFE         AIC_ACCR1_XS_SLOT(9)

#define AC97_PCM_RS_L_FRONT     AIC_ACCR1_RS_SLOT(3)
#define AC97_PCM_RS_R_FRONT     AIC_ACCR1_RS_SLOT(4)
#define AC97_PCM_RS_CENTER      AIC_ACCR1_RS_SLOT(6)
#define AC97_PCM_RS_L_SURR      AIC_ACCR1_RS_SLOT(7)
#define AC97_PCM_RS_R_SURR      AIC_ACCR1_RS_SLOT(8)
#define AC97_PCM_RS_LFE         AIC_ACCR1_RS_SLOT(9)

#define __ac97_set_xs_none()    ( REG_AIC_ACCR1 &= ~AIC_ACCR1_XS_MASK )
#define __ac97_set_xs_mono()                        \
do {                                    \
    REG_AIC_ACCR1 &= ~AIC_ACCR1_XS_MASK;                \
    REG_AIC_ACCR1 |= AC97_PCM_XS_R_FRONT;               \
} while(0)
#define __ac97_set_xs_stereo()                      \
do {                                    \
    REG_AIC_ACCR1 &= ~AIC_ACCR1_XS_MASK;                \
    REG_AIC_ACCR1 |= AC97_PCM_XS_L_FRONT | AC97_PCM_XS_R_FRONT; \
} while(0)

/* In fact, only stereo is support now. */
#define __ac97_set_rs_none()    ( REG_AIC_ACCR1 &= ~AIC_ACCR1_RS_MASK )
#define __ac97_set_rs_mono()                        \
do {                                    \
    REG_AIC_ACCR1 &= ~AIC_ACCR1_RS_MASK;                \
    REG_AIC_ACCR1 |= AC97_PCM_RS_R_FRONT;               \
} while(0)
#define __ac97_set_rs_stereo()                      \
do {                                    \
    REG_AIC_ACCR1 &= ~AIC_ACCR1_RS_MASK;                \
    REG_AIC_ACCR1 |= AC97_PCM_RS_L_FRONT | AC97_PCM_RS_R_FRONT; \
} while(0)

#define __ac97_warm_reset_codec()       \
 do {                       \
    REG_AIC_ACCR2 |= AIC_ACCR2_SA;      \
    REG_AIC_ACCR2 |= AIC_ACCR2_SS;      \
    udelay(2);              \
    REG_AIC_ACCR2 &= ~AIC_ACCR2_SS;     \
    REG_AIC_ACCR2 &= ~AIC_ACCR2_SA;     \
 } while (0)

#define __ac97_cold_reset_codec()       \
 do {                       \
    REG_AIC_ACCR2 |=  AIC_ACCR2_SR;     \
    udelay(2);              \
    REG_AIC_ACCR2 &= ~AIC_ACCR2_SR;     \
 } while (0)

/* n=8,16,18,20 */
#define __ac97_set_iass(n) \
 ( REG_AIC_ACCR2 = (REG_AIC_ACCR2 & ~AIC_ACCR2_IASS_MASK) | AIC_ACCR2_IASS_##n##BIT )
#define __ac97_set_oass(n) \
 ( REG_AIC_ACCR2 = (REG_AIC_ACCR2 & ~AIC_ACCR2_OASS_MASK) | AIC_ACCR2_OASS_##n##BIT )

/* This bit should only be set in 2 channels configuration */
#define __i2s_send_rfirst()   ( REG_AIC_I2SCR |= AIC_I2SCR_RFIRST )  /* RL */
#define __i2s_send_lfirst()   ( REG_AIC_I2SCR &= ~AIC_I2SCR_RFIRST ) /* LR */

/* This bit should only be set in 2 channels configuration and 16bit-packed mode */
#define __i2s_switch_lr()     ( REG_AIC_I2SCR |= AIC_I2SCR_SWLH )
#define __i2s_unswitch_lr()   ( REG_AIC_I2SCR &= ~AIC_I2SCR_SWLH )

#define __i2s_select_i2s()            ( REG_AIC_I2SCR &= ~AIC_I2SCR_AMSL )
#define __i2s_select_msbjustified()   ( REG_AIC_I2SCR |= AIC_I2SCR_AMSL )

/* n=8,16,18,20,24 */
/*#define __i2s_set_sample_size(n) \
 ( REG_AIC_I2SCR |= (REG_AIC_I2SCR & ~AIC_I2SCR_WL_MASK) | AIC_I2SCR_WL_##n##BIT )*/

#define __i2s_out_channel_select(n) __aic_out_channel_select(n)

#define __i2s_set_oss_sample_size(n) \
 ( REG_AIC_CR = (REG_AIC_CR & ~AIC_CR_OSS_MASK) | AIC_CR_OSS(n))
#define __i2s_set_iss_sample_size(n) \
 ( REG_AIC_CR = (REG_AIC_CR & ~AIC_CR_ISS_MASK) | AIC_CR_ISS(n))

#define __i2s_stop_bitclk()   ( REG_AIC_I2SCR |= AIC_I2SCR_STPBK )
#define __i2s_start_bitclk()  ( REG_AIC_I2SCR &= ~AIC_I2SCR_STPBK )

#define __i2s_stop_ibitclk()   ( REG_AIC_I2SCR |= AIC_I2SCR_ISTPBK )
#define __i2s_start_ibitclk()  ( REG_AIC_I2SCR &= ~AIC_I2SCR_ISTPBK )

#define __aic_transmit_request()  ( REG_AIC_SR & AIC_SR_TFS )
#define __aic_receive_request()   ( REG_AIC_SR & AIC_SR_RFS )
#define __aic_transmit_underrun() ( REG_AIC_SR & AIC_SR_TUR )
#define __aic_receive_overrun()   ( REG_AIC_SR & AIC_SR_ROR )

#define __aic_clear_errors()      ( REG_AIC_SR &= ~(AIC_SR_TUR | AIC_SR_ROR) )

#define __aic_get_transmit_resident() \
  ( (REG_AIC_SR & AIC_SR_TFL_MASK) >> AIC_SR_TFL_LSB )
#define __aic_get_receive_count() \
  ( (REG_AIC_SR & AIC_SR_RFL_MASK) >> AIC_SR_RFL_LSB )

#define __ac97_command_transmitted()     ( REG_AIC_ACSR & AIC_ACSR_CADT )
#define __ac97_status_received()         ( REG_AIC_ACSR & AIC_ACSR_SADR )
#define __ac97_status_receive_timeout()  ( REG_AIC_ACSR & AIC_ACSR_RSTO )
#define __ac97_codec_is_low_power_mode() ( REG_AIC_ACSR & AIC_ACSR_CLPM )
#define __ac97_codec_is_ready()          ( REG_AIC_ACSR & AIC_ACSR_CRDY )
#define __ac97_slot_error_detected()     ( REG_AIC_ACSR & AIC_ACSR_SLTERR )
#define __ac97_clear_slot_error()        ( REG_AIC_ACSR &= ~AIC_ACSR_SLTERR )

#define __i2s_is_busy()         ( REG_AIC_I2SSR & AIC_I2SSR_BSY )

#define __ac97_out_rcmd_addr(reg)                   \
do {                                    \
    REG_AIC_ACCAR = AC97_READ_CMD | ((reg) << AC97_INDEX_LSB);  \
} while (0)

#define __ac97_out_wcmd_addr(reg)                   \
do {                                    \
    REG_AIC_ACCAR = AC97_WRITE_CMD | ((reg) << AC97_INDEX_LSB);     \
} while (0)

#define __ac97_out_data(value)                      \
do {                                    \
    REG_AIC_ACCDR = ((value) << AC97_DATA_LSB);             \
} while (0)

#define __ac97_in_data() \
 ( (REG_AIC_ACSDR & CODEC_REG_DATA_MASK) >> AC97_DATA_LSB )

#define __ac97_in_status_addr() \
 ( (REG_AIC_ACSAR & AC97_INDEX_MASK) >> AC97_INDEX_LSB )

#define __i2s_set_sample_rate(i2sclk, sync) \
  ( REG_AIC_I2SDIV = ((i2sclk) / (4*64)) / (sync) )

#define __aic_write_tfifo(v)  ( REG_AIC_DR = (v) )
#define __aic_read_rfifo()    ( REG_AIC_DR )

#define __aic_internal_codec()  ( REG_AIC_FR |= AIC_FR_ICDC )
#define __aic_external_codec()  ( REG_AIC_FR &= ~AIC_FR_ICDC )
#define __aic0_internal_codec()  ( REG_AIC0_FR |= AIC_FR_ICDC )
#define __aic0_external_codec()  ( REG_AIC0_FR &= ~AIC_FR_ICDC )

//
// Define next ops for AC97 compatible
//

#define AC97_ACSR   AIC_ACSR

#define __ac97_enable()     __aic_enable(); __aic_select_ac97()
#define __ac97_disable()    __aic_disable()
#define __ac97_reset()      __aic_reset()

#define __ac97_set_transmit_trigger(n)  __aic_set_transmit_trigger(n)
#define __ac97_set_receive_trigger(n)   __aic_set_receive_trigger(n)

#define __ac97_enable_record()      __aic_enable_record()
#define __ac97_disable_record()     __aic_disable_record()
#define __ac97_enable_replay()      __aic_enable_replay()
#define __ac97_disable_replay()     __aic_disable_replay()
#define __ac97_enable_loopback()    __aic_enable_loopback()
#define __ac97_disable_loopback()   __aic_disable_loopback()

#define __ac97_enable_transmit_dma()    __aic_enable_transmit_dma()
#define __ac97_disable_transmit_dma()   __aic_disable_transmit_dma()
#define __ac97_enable_receive_dma() __aic_enable_receive_dma()
#define __ac97_disable_receive_dma()    __aic_disable_receive_dma()

#define __ac97_transmit_request()   __aic_transmit_request()
#define __ac97_receive_request()    __aic_receive_request()
#define __ac97_transmit_underrun()  __aic_transmit_underrun()
#define __ac97_receive_overrun()    __aic_receive_overrun()

#define __ac97_clear_errors()       __aic_clear_errors()

#define __ac97_get_transmit_resident()  __aic_get_transmit_resident()
#define __ac97_get_receive_count()  __aic_get_receive_count()

#define __ac97_enable_transmit_intr()   __aic_enable_transmit_intr()
#define __ac97_disable_transmit_intr()  __aic_disable_transmit_intr()
#define __ac97_enable_receive_intr()    __aic_enable_receive_intr()
#define __ac97_disable_receive_intr()   __aic_disable_receive_intr()

#define __ac97_write_tfifo(v)       __aic_write_tfifo(v)
#define __ac97_read_rfifo()     __aic_read_rfifo()

//
// Define next ops for I2S compatible
//

#define I2S_ACSR    AIC_I2SSR

#define __i2s_enable()       __aic_enable(); __aic_select_i2s()
#define __i2s_disable()     __aic_disable()
#define __i2s_reset()       __aic_reset()

#define __i2s_set_transmit_trigger(n)   __aic_set_transmit_trigger(n)
#define __i2s_set_receive_trigger(n)    __aic_set_receive_trigger(n)

#define __i2s_enable_record()       __aic_enable_record()
#define __i2s_disable_record()      __aic_disable_record()
#define __i2s_enable_replay()       __aic_enable_replay()
#define __i2s_disable_replay()      __aic_disable_replay()
#define __i2s_enable_loopback()     __aic_enable_loopback()
#define __i2s_disable_loopback()    __aic_disable_loopback()

#define __i2s_enable_transmit_dma() __aic_enable_transmit_dma()
#define __i2s_disable_transmit_dma()    __aic_disable_transmit_dma()
#define __i2s_enable_receive_dma()  __aic_enable_receive_dma()
#define __i2s_disable_receive_dma() __aic_disable_receive_dma()

#define __i2s_transmit_request()    __aic_transmit_request()
#define __i2s_receive_request()     __aic_receive_request()
#define __i2s_transmit_underrun()   __aic_transmit_underrun()
#define __i2s_receive_overrun()     __aic_receive_overrun()

#define __i2s_clear_errors()        __aic_clear_errors()

#define __i2s_get_transmit_resident()   __aic_get_transmit_resident()
#define __i2s_get_receive_count()   __aic_get_receive_count()

#define __i2s_enable_transmit_intr()    __aic_enable_transmit_intr()
#define __i2s_disable_transmit_intr()   __aic_disable_transmit_intr()
#define __i2s_enable_receive_intr() __aic_enable_receive_intr()
#define __i2s_disable_receive_intr()    __aic_disable_receive_intr()

#define __i2s_write_tfifo(v)        __aic_write_tfifo(v)
#define __i2s_read_rfifo()      __aic_read_rfifo()

#define __i2s_reset_codec()         \
 do {                       \
 } while (0)


/*************************************************************************
 * SPDIF INTERFACE in AIC Controller
 *************************************************************************/

#define __spdif_enable()        ( REG_SPDIF_ENA |= SPDIF_ENA_SPEN )
#define __spdif_disable()       ( REG_SPDIF_ENA &= ~SPDIF_ENA_SPEN )

#define __spdif_enable_transmit_dma()     ( REG_SPDIF_CTRL |= SPDIF_CTRL_DMAEN )
#define __spdif_disable_transmit_dma()    ( REG_SPDIF_CTRL &= ~SPDIF_CTRL_DMAEN )
#define __spdif_enable_dtype()            ( REG_SPDIF_CTRL |= SPDIF_CTRL_DTYPE )
#define __spdif_disable_dtype()           ( REG_SPDIF_CTRL &= ~SPDIF_CTRL_DTYPE )
#define __spdif_enable_sign()             ( REG_SPDIF_CTRL |= SPDIF_CTRL_SIGN )
#define __spdif_disable_sign()            ( REG_SPDIF_CTRL &= ~SPDIF_CTRL_SIGN )
#define __spdif_enable_invalid()          ( REG_SPDIF_CTRL |= SPDIF_CTRL_INVALID )
#define __spdif_disable_invalid()         ( REG_SPDIF_CTRL &= ~SPDIF_CTRL_INVALID )
#define __spdif_enable_reset()            ( REG_SPDIF_CTRL |= SPDIF_CTRL_RST )
#define __spdif_select_spdif()            ( REG_SPDIF_CTRL |= SPDIF_CTRL_SPDIFI2S )
#define __spdif_select_i2s()              ( REG_SPDIF_CTRL &= ~SPDIF_CTRL_SPDIFI2S )
#define __spdif_enable_MTRIGmask()        ( REG_SPDIF_CTRL |= SPDIF_CTRL_MTRIG )
#define __spdif_disable_MTRIGmask()       ( REG_SPDIF_CTRL &= ~SPDIF_CTRL_MTRIG )
#define __spdif_enable_MFFURmask()        ( REG_SPDIF_CTRL |= SPDIF_CTRL_MFFUR )
#define __spdif_disable_MFFURmask()       ( REG_SPDIF_CTRL &= ~SPDIF_CTRL_MFFUR )

#define __spdif_enable_initlvl_high()     ( REG_SPDIF_CFG1 |=  SPDIF_CFG1_INITLVL )
#define __spdif_enable_initlvl_low()      ( REG_SPDIF_CFG1 &=  ~SPDIF_CFG1_INITLVL )
#define __spdif_enable_zrovld_invald()    ( REG_SPDIF_CFG1 |=  SPDIF_CFG1_ZROVLD )
#define __spdif_enable_zrovld_vald()      ( REG_SPDIF_CFG1 &=  ~SPDIF_CFG1_ZROVLD )

/* 0, 1, 2, 3 */
#define __spdif_set_transmit_trigger(n)         \
do {                            \
    REG_SPDIF_CFG1 &= ~SPDIF_CFG1_TRIG_MASK;    \
    REG_SPDIF_CFG1 |= SPDIF_CFG1_TRIG(n);   \
} while(0)

/* 1 ~ 15 */
#define __spdif_set_srcnum(n)               \
do {                            \
    REG_SPDIF_CFG1 &= ~SPDIF_CFG1_SRCNUM_MASK;  \
    REG_SPDIF_CFG1 |= ((n) << SPDIF_CFG1_SRCNUM_LSB);   \
} while(0)

/* 1 ~ 15 */
#define __spdif_set_ch1num(n)               \
do {                            \
    REG_SPDIF_CFG1 &= ~SPDIF_CFG1_CH1NUM_MASK;  \
    REG_SPDIF_CFG1 |= ((n) << SPDIF_CFG1_CH1NUM_LSB);   \
} while(0)

/* 1 ~ 15 */
#define __spdif_set_ch2num(n)               \
do {                            \
    REG_SPDIF_CFG1 &= ~SPDIF_CFG1_CH2NUM_MASK;  \
    REG_SPDIF_CFG1 |= ((n) << SPDIF_CFG1_CH2NUM_LSB);   \
} while(0)

/* 0x0, 0x2, 0x3, 0xa, 0xe */
#define __spdif_set_fs(n)               \
do {                            \
    REG_SPDIF_CFG2 &= ~SPDIF_CFG2_FS_MASK;      \
    REG_SPDIF_CFG2 |= ((n) << SPDIF_CFG2_FS_LSB);   \
} while(0)

/* 0xd, 0xc, 0x5, 0x1 */
#define __spdif_set_orgfrq(n)               \
do {                            \
    REG_SPDIF_CFG2 &= ~SPDIF_CFG2_ORGFRQ_MASK;      \
    REG_SPDIF_CFG2 |= ((n) << SPDIF_CFG2_ORGFRQ_LSB);   \
} while(0)

/* 0x1, 0x6, 0x2, 0x4, 0x5 */
#define __spdif_set_samwl(n)                \
do {                            \
    REG_SPDIF_CFG2 &= ~SPDIF_CFG2_SAMWL_MASK;       \
    REG_SPDIF_CFG2 |= ((n) << SPDIF_CFG2_SAMWL_LSB);    \
} while(0)

#define __spdif_enable_samwl_24()    ( REG_SPDIF_CFG2 |= SPDIF_CFG2_MAXWL )
#define __spdif_enable_samwl_20()    ( REG_SPDIF_CFG1 &= ~SPDIF_CFG2_MAXWL )

/* 0x1, 0x1, 0x2, 0x3 */
#define __spdif_set_clkacu(n)               \
do {                            \
    REG_SPDIF_CFG2 &= ~SPDIF_CFG2_CLKACU_MASK;      \
    REG_SPDIF_CFG2 |= ((n) << SPDIF_CFG2_CLKACU_LSB);   \
} while(0)

/* see IEC60958-3 */
#define __spdif_set_catcode(n)              \
do {                            \
    REG_SPDIF_CFG2 &= ~SPDIF_CFG2_CATCODE_MASK;     \
    REG_SPDIF_CFG2 |= ((n) << SPDIF_CFG2_CATCODE_LSB);  \
} while(0)

/* n = 0x0, */
#define __spdif_set_chmode(n)               \
do {                            \
    REG_SPDIF_CFG2 &= ~SPDIF_CFG2_CHMD_MASK;    \
    REG_SPDIF_CFG2 |= ((n) << SPDIF_CFG2_CHMD_LSB); \
} while(0)

#define __spdif_enable_pre()       ( REG_SPDIF_CFG2 |= SPDIF_CFG2_PRE )
#define __spdif_disable_pre()      ( REG_SPDIF_CFG2 &= ~SPDIF_CFG2_PRE )
#define __spdif_enable_copyn()     ( REG_SPDIF_CFG2 |= SPDIF_CFG2_COPYN )
#define __spdif_disable_copyn()    ( REG_SPDIF_CFG2 &= ~SPDIF_CFG2_COPYN )
/* audio sample word represents linear PCM samples */
#define __spdif_enable_audion()    ( REG_SPDIF_CFG2 &= ~SPDIF_CFG2_AUDION )
/* udio sample word used for other purpose */
#define __spdif_disable_audion()   ( REG_SPDIF_CFG2 |= SPDIF_CFG2_AUDION )
#define __spdif_enable_conpro()    ( REG_SPDIF_CFG2 &= ~SPDIF_CFG2_CONPRO )
#define __spdif_disable_conpro()   ( REG_SPDIF_CFG2 |= SPDIF_CFG2_CONPRO )

/***************************************************************************
 * ICDC
 ***************************************************************************/
#define __i2s_internal_codec()         __aic_internal_codec()
#define __i2s_external_codec()         __aic_external_codec()

#define __icdc_clk_ready()             ( REG_ICDC_CKCFG & ICDC_CKCFG_CKRDY )
#define __icdc_sel_adc()               ( REG_ICDC_CKCFG |= ICDC_CKCFG_SELAD )
#define __icdc_sel_dac()               ( REG_ICDC_CKCFG &= ~ICDC_CKCFG_SELAD )

#define __icdc_set_rgwr()              ( REG_ICDC_RGADW |= ICDC_RGADW_RGWR )
#define __icdc_clear_rgwr()            ( REG_ICDC_RGADW &= ~ICDC_RGADW_RGWR )
#define __icdc_rgwr_ready()            ( REG_ICDC_RGADW & ICDC_RGADW_RGWR )

#define AIC_RW_CODEC_START()        while (INREG32(ICDC_RGADW) & ICDC_RGADW_RGWR)
#define AIC_RW_CODEC_STOP()     while (INREG32(ICDC_RGADW) & ICDC_RGADW_RGWR)


#define __icdc_set_addr(n)              \
do {                                \
    REG_ICDC_RGADW &= ~ICDC_RGADW_RGADDR_MASK;  \
    REG_ICDC_RGADW |= (n) << ICDC_RGADW_RGADDR_LSB; \
} while(0)

#define __icdc_set_cmd(n)               \
do {                                \
    REG_ICDC_RGADW &= ~ICDC_RGADW_RGDIN_MASK;   \
    REG_ICDC_RGADW |= (n) << ICDC_RGADW_RGDIN_LSB;  \
} while(0)

#define __icdc_irq_pending()            ( REG_ICDC_RGDATA & ICDC_RGDATA_IRQ )
#define __icdc_get_value()              ( REG_ICDC_RGDATA & ICDC_RGDATA_RGDOUT_MASK )



#endif /* __MIPS_ASSEMBLER */

#endif

#ifdef __cplusplus
}
#endif

#endif /* _X1000_AIC_H_ */
