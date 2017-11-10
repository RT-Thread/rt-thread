/*****************************************************************************
 *
 *            Copyright Andes Technology Corporation 2007-2008
 *                         All Rights Reserved.
 *
 *  Revision History:
 *
 *    Aug.21.2007     Created.
 ****************************************************************************/

/*****************************************************************************
 *
 * FILE NAME                                         VERSION
 *
 *      sspd_ac97.c
 *
 * DESCRIPTION
 *
 *      AC97 codec digital serial interface protocol implementation.
 *      A SSP AC-link & AC97 controller driver supplement.
 *
 * DATA STRUCTURES
 *
 *   None
 *
 * DEPENDENCIES
 *
 *   None
 *
 ****************************************************************************/
#ifndef __SSPD_AC97_H__
#define __SSPD_AC97_H__

/*****************************************************************************
 * AC97 Audio Frame Definitions
 *
 ****************************************************************************/

/*****************************************************************************
 * Definitions for SDATA_OUT frame slots
 ****************************************************************************/
/* Command address port (slot1) */
#define AC97_CMDADDR_RW_MASK                0x00080000      /* AC97 read/write command */
#define AC97_CMDADDR_RW_BIT                 19
    #define AC97_CMD_WRITE                           0
    #define AC97_CMD_READ                            1

#define AC97_CMDADDR_CRIDX_MASK             0x0007f000      /* AC97 control register index (even addressed) */
#define AC97_CMDADDR_CRIDX_SHIFT            12

/* Command data port (slot2) */
#define AC97_CMDDATA_MASK                   0x000ffff0      /* AC97 command data (16 bits) */
#define AC97_CMDDATA_SHIFT                  4

/*****************************************************************************
 * Definitions for SDATA_IN frame slots
 ****************************************************************************/
/* Status address port (slot1) */
#define AC97_STADDR_CRIDX_MASK              0x0007f000      /* Echo of AC97 control register index */
#define AC97_STADDR_CRIDX_SHIFT             12

#define AC97_STADDR_SLOTREQ_MASK            0x00000ffc      /* AC97 2.0 Appendex A SLOTREQ bit definitions */
#define AC97_STADDR_SLOTREQ_SHIFT           2

/* Command data port (slot2) */
#define AC97_STDATA_MASK                    0x000ffff0
#define AC97_STDATA_SHIFT                   4

/*****************************************************************************
 * Definitions for PCM sampling data
 ****************************************************************************/
/* PCM sampling resolution */
#define AC97_PCM_SR16_MASK                  0x000ffff0      /* 16-bit sampling resolution */
#define AC97_PCM_SR16_SHIFT                 4
#define AC97_PCM_SR18_MASK                  0x000ffffc      /* 18-bit sampling resolution */
#define AC97_PCM_SR18_SHIFT                 2
#define AC97_PCM_SR20_MASK                  0x000fffff      /* 20-bit sampling resolution */
#define AC97_PCM_SR20_SHIFT                 0


/*****************************************************************************
 * AC97 Control Register Definitions
 ****************************************************************************/
/* Reset register (index 0x00) */
#define AC97_CRIDX_RESET                    0x00            /* Write any value to do register rest, */
                                                            /* read will return feature implementation id. */
/* Reset register definitions */
#define AC97_ID0_DEDICATED_MIC_MASK         0x0001          /* Dedicated mic PCM in channel */
#define AC97_ID0_DEDICATED_MIC_BIT          0
#define AC97_ID1_RESERVED_MASK              0x0002          /* Reserved (was modem line codec support) */
#define AC97_ID1_RESERVED_BIT               1
#define AC97_ID2_BASE_TREBLE_CTRL_MASK      0x0004          /* Bass and Treble control */
#define AC97_ID2_BASE_TREBLE_CTRL_BIT       2
#define AC97_ID3_SIMULATED_STEREO_MASK      0x0008          /* Simulated stereo */
#define AC97_ID3_SIMULATED_STEREO_BIT       3
#define AC97_ID4_HEADPHONE_OUT_MASK         0x0010          /* Headphone out support */
#define AC97_ID4_HEADPHONE_OUT_BIT          4
#define AC97_ID5_LAUDNESS_MASK              0x0020          /* Loudness (bass boost) support */
#define AC97_ID5_LAUDNESS_BIT               5
#define AC97_ID6_18BIT_DAC_MASK             0x0040          /* 18 bit DAC resolution */
#define AC97_ID6_18BIT_DAC_BIT              6
#define AC97_ID7_20BIT_DAC_MASK             0x0080          /* 20 bit DAC resolution */
#define AC97_ID7_20BIT_DAC_BIT              7
#define AC97_ID8_18BIT_ADC_MASK             0x0100          /* 18 bit ADC resolution */
#define AC97_ID8_18BIT_ADC_BIT              8
#define AC97_ID9_20BIT_ADC_MASK             0x0200          /* 20 bit ADC resolution */
#define AC97_ID9_20BIT_ADC_BIT              9

#define AC97_SE_MASK                        0x7c            /* 3D Stereo Enhancement Technique */
#define AC97_SE_SHIFT                       10
    #define AC97_SE_NONE                         0
    #define AC97_SE_PHAT                         1
    #define AC97_SE_CREATIVE                     2
    #define AC97_SE_NS3D                         3
    #define AC97_SE_YMERSION                     4
    #define AC97_SE_BBE3D                        5
    #define AC97_SE_CRYSTAL3D                    6
    #define AC97_SE_QXPANDER                     7
    #define AC97_SE_SPATIALIZER3D                8
    #define AC97_SE_SRS3D                        9
    #define AC97_SE_PLATFORMTECH3D              10
    #define AC97_SE_AKM3D                       11
    #define AC97_SE_AUREAL                      12
    #define AC97_SE_AZTECH3D                    13
    #define AC97_SE_BINAURA3D                   14
    #define AC97_SE_ESS                         15
    #define AC97_SE_VMAX                        16
    #define AC97_SE_NVIDEA3D                    17
    #define AC97_SE_INCREDIBLE                  18
    #define AC97_SE_TI3D                        19
    #define AC97_SE_VLSI3D                      20
    #define AC97_SE_TRITECH3D                   21
    #define AC97_SE_REALTECH3D                  22
    #define AC97_SE_SAMSUNG3D                   23
    #define AC97_SE_WOLFSON3D                   24
    #define AC97_SE_DELTA3D                     25
    #define AC97_SE_SIGMATEL3D                  26
    #define AC97_SE_ROCKWELL3D                  28

/* Play master volume registers (index 0x02, 0x04, 0x06) */
#define AC97_CRIDX_MASTER_VOLUME            0x02            /* Stereo master volume register (ML, MR) */
#define AC97_CRIDX_HEADPHONE_VOLUME         0x04            /* Headphone volume register (ML, MR) */
#define AC97_CRIDX_MASTER_VOLUME_MONO       0x06            /* Mono master volume register (MM/MR) */

/* Play master volume register definitions */
#define AC97_MR_MASK                        0x003f          /* Right channel level (1.5dB step) */
#define AC97_MR_SHIFT                       0
#define AC97_ML_MASK                        0x3f00          /* Left channel level */
#define AC97_ML_SHIFT                       8
#define AC97_MUTE_MASK                      0x8000          /* Mute bit (able to keep original level value) */
#define AC97_MUTE_BIT                       15

    #define AC97_VOLUME_INCSTEP               (-1)          /* 1.5dB increase step */
    #define AC97_VOLUME_DECSTEP               (+1)          /* 1.5dB decrease step */

    #define AC97_VOLUME_0DB_ATTEN             0x00          /* 0   dB attenuation (max) (required) */
    #define AC97_VOLUME_46P5DB_ATTEN          0x1f          /* 46.5dB attenuation       (required) */
    #define AC97_VOLUME_94P5DB_ATTEN          0x3f          /* 94.5dB attenuation (min) (optional) */

    #define AC97_VOLUME_MAX                   0x00          /* 0   dB attenuation (max) (required) */
    #define AC97_VOLUME_MIDDLE                0x1f          /* 46.5dB attenuation       (required) */
    #define AC97_VOLUME_MIN                   0x3f          /* 94.5dB attenuation (min) (optional) */

/* Master tone control register (index 0x08) */
#define AC97_CRIDX_MASTER_TONE              0x08            /* Master tone (bass & treble) control register */

/* Master tone control register definitions */
#define AC97_TREBLE_MASK                    0x000f          /* Tremble level (10kHz center, 1.5dB step) */
#define AC97_TREBLE_SHIFT                   0
#define AC97_BASS_MASK                      0x0f00          /* Base level (100Hz center, 1.5dB step) */
#define AC97_BASS_SHIFT                     8

    #define AC97_TONE_INCSTEP                 (-1)          /* +1.5dB increase step */
    #define AC97_TONE_DECSTEP                 (+1)          /* -1.5dB decrease step */

    #define AC97_TONE_MAX                     0x00          /* +10.5dB gain */
    #define AC97_TONE_CENTER                  0x07          /*   0  dB gain */
    #define AC97_TONE_MIN                     0x0e          /* -10.5dB gain */
    #define AC97_TONE_BYPASS                  0x0f          /* Bypass */

/* PC beep register (index 0x0a) */
#define AC97_CRIDX_PCBEEP                   0x0a            /* PC beep input level control register */

/* PC beep register definitions */
#define AC97_PCBEEP_MASK                    0x001e          /* Beep level (3dB step) */
#define AC97_PCBEEP_SHIFT                   1
#define AC97_PCBEEP_MUTE_MASK               0x8000          /* Mute bit (able to keep original level value) */
#define AC97_PCBEEP_MUTE_BIT                15

    #define AC97_PCBEEP_INCSTEP               (+1)          /* 3dB increase step */
    #define AC97_PCBEEP_DECSTEP               (-1)          /* 3dB decrease step */

    #define AC97_PCBEEP_0DB                      0          /*  0dB */
    #define AC97_PCBEEP_45DB                    15          /* 45dB */

/* Analog mixer input gain registers (index 0x0c ~ 0x18) */
#define AC97_CRIDX_PHONE_GAIN               0x0c            /* Phone volume input gain control register (GR, M) */
#define AC97_CRIDX_MIC_GAIN                 0x0e            /* Microphone volume input gain control register (BOOST, GR, M) */
#define AC97_CRIDX_LINEIN_GAIN              0x10            /* Line in volume input gain control register (GL, GR, M) */
#define AC97_CRIDX_CD_GAIN                  0x12            /* CD volume input gain control register (GL, GR, M) */
#define AC97_CRIDX_VIDEO_GAIN               0x14            /* Video volume input gain control register (GL, GR, M) */
#define AC97_CRIDX_AUX_GAIN                 0x16            /* AUX volume input gain control register (GL, GR, M) */
#define AC97_CRIDX_PCMOUT_GAIN              0x18            /* PCM out from AC97 volume input gain control register (GL, GR, M) */

/*
 * Phone volume input gain register definitions
 * Microphone volume input gain control register definitions
 * Line in volume input gain control register definitions
 * CD volume input gain control register definitions
 * Video volume input gain control register definitions
 * AUX volume input gain control register definitions
 * PCM out from AC97 volume input gain control register definitions
 */
#define AC97_MIXER_GR_MASK                  0x001f          /* Mixer input gain right channel (1.5dB step) */
#define AC97_MIXER_GR_SHIFT                 0
#define AC97_MIXER_GN_MASK                  AC97_GR_MASK
#define AC97_MIXER_GN_SHIFT                 AC97_GR_SHIFT
#define AC97_MIXER_GL_MASK                  0x1f00          /* Mixer input gain left channel (1.5dB step) */
#define AC97_MIXER_GL_SHIFT                 0
#define AC97_MIXER_MUTE_MASK                0x8000          /* Mute bit (able to keep original level value) */
#define AC97_MIXER_MUTE_BIT                 15

    #define AC97_MIXER_INCSTEP                (-1)          /* 1.5dB increase step */
    #define AC97_MIXER_DECSTEP                (+1)          /* 1.5dB decrease step */

    #define AC97_MIXER_MAX                    0x00          /* +12.0dB gain */
    #define AC97_MIXER_CENTER                 0x08          /*   0  dB gain */
    #define AC97_MIXER_MIN                    0x1f          /* -34.5dB gain */

/* Microphone volume input gain control register specific definitions */
#define AC97_MIC_VOLUME_BOOST_MASK          0x0040          /* 20dB boost bit */
#define AC97_MIC_VOLUME_BOOST_BIT           0

/* ------------------------------------------------ */
/* Record select control register (index 0x1a) */
/* */
#define AC97_CRIDX_RECORD_SELECT            0x1a            /* Record select control register */

/* Record select control register definitions */
#define AC97_RECORD_SR_MASK                 0x0007          /* Record select right channel */
#define AC97_RECORD_SR_SHIFT                0
#define AC97_RECORD_SL_MASK                 0x0700          /* Record select left channel */
#define AC97_RECORD_SL_SHIFT                8

    #define AC97_RECORD_SELECT_MIC               0
    #define AC97_RECORD_SELECT_CD                1
    #define AC97_RECORD_SELECT_VIDEO             2
    #define AC97_RECORD_SELECT_AUX               3
    #define AC97_RECORD_SELECT_LINEIN            4
    #define AC97_RECORD_SELECT_STEREOMIX         5
    #define AC97_RECORD_SELECT_MONOMIX           6
    #define AC97_RECORD_SELECT_PHONE             7

/* ------------------------------------------------ */
/* Record gain registers (index 0x1c, 0x1e) */
/* */
#define AC97_CRIDX_RECORD_GAIN              0x1c            /* Record gain (stereo input) register (GL, GR, M) */
#define AC97_CRIDX_RECORD_GAIN_MIC          0x1e            /* Record gain mic (optional ch3 mic) register (GR, M) */

/* Record gain (stereo input) register definitions */
/* Record gain mic (optional ch3 mic) register definitions */
#define AC97_RECORD_GR_MASK                 0x000f          /* Record gain right channel (1.5dB step) */
#define AC97_RECORD_GR_SHIFT                0
#define AC97_RECORD_GL_MASK                 0x0f00          /* Record gain left channel (1.5dB step) */
#define AC97_RECORD_GL_SHIFT                8
#define AC97_RECORD_MUTE_MASK               0x8000          /* Mute bit (able to keep original level value) */
#define AC97_RECORD_MUTE_BIT                15

    #define AC97_RECORD_INCSTEP               (+1)          /* 1.5dB increase step */
    #define AC97_RECORD_DECSTEP               (-1)          /* 1.5dB decrease step */

    #define AC97_RECORD_0DB                   0x00          /*   0.0dB gain */
    #define AC97_RECORD_22P5DB                0x0f          /* +22.5dB gain */

/* ------------------------------------------------ */
/* General purpose register (index 0x20) */
/* */
#define AC97_CRIDX_GPR                      0x20            /* General purpose register */

/* General purpose register definitions */
#define AC97_GPR_LPBK_MASK                  0x0080          /* ADC/DAC loopback mode (system performance measurement) */
#define AC97_GPR_LPBK_BIT                   7
#define AC97_GPR_MS_MASK                    0x0100          /* Mic select (0: mic1, 1: mic2) */
#define AC97_GPR_MS_BIT                     8
#define AC97_GPR_MIX_MASK                   0x0200          /* Mono output select (0: mix, 1: mic) */
#define AC97_GPR_MIX_BIT                    9
#define AC97_GPR_LD_MASK                    0x1000          /* Loudness/bass_boost (0: off, 1: on) */
#define AC97_GPR_LD_BIT                     12
#define AC97_GPR_3D_MASK                    0x2000          /* 3D stereo enhancement (0: off, 1: on) */
#define AC97_GPR_3D_BIT                     13
#define AC97_GPR_ST_MASK                    0x4000          /* Simulated stereo enhancement (0: off, 1: on) */
#define AC97_GPR_ST_BIT                     14
#define AC97_GPR_POP_MASK                   0x8000          /* PCM out path & mute (0: pre 3D, 1: post 3D) */
#define AC97_GPR_POP_BIT                    15

/* ------------------------------------------------ */
/* 3D control register (index 0x22) */
/* */
#define AC97_CRIDX_3D_CONTROL               0x22            /* 3D control register */

/* 3D control register definitions */
#define AC97_3D_CONTROL_DP_MASK             0x000f          /* Depth */
#define AC97_3D_CONTROL_DP_SHIFT            0
#define AC97_3D_CONTROL_CR_MASK             0x0f00          /* Center */
#define AC97_3D_CONTROL_CR_SHIFT            8

/* ------------------------------------------------ */
/* Powerdown control/status register (index 0x20) */
/* */
#define AC97_CRIDX_POWER                    0x26            /* Powerdown control/status register */

/* Powerdown control/status register definitions */
#define AC97_POWER_ADC_MASK                 0x0001          /* ADC selction ready to transmit data */
#define AC97_POWER_ADC_BIT                  0
#define AC97_POWER_DAC_MASK                 0x0002          /* DAC selection ready to accept data */
#define AC97_POWER_DAC_BIT                  1
#define AC97_POWER_ANL_MASK                 0x0004          /* Analog mixer, etc. ready */
#define AC97_POWER_ANL_BIT                  2
#define AC97_POWER_REF_MASK                 0x0008          /* Vref's up to nominal level */
#define AC97_POWER_REF_BIT                  3

#define AC97_POWER_PR0_MASK                 0x0100          /* PCM in ADC's & input mux powerdown */
#define AC97_POWER_PR0_BIT                  8
#define AC97_POWER_PR1_MASK                 0x0200          /* PCM out DACs powerdown */
#define AC97_POWER_PR1_BIT                  9
#define AC97_POWER_PR2_MASK                 0x0400          /* Analog mixer power down (Vref still on) */
#define AC97_POWER_PR2_BIT                  10
#define AC97_POWER_PR3_MASK                 0x0800          /* Analog mixer power down (Vref off) */
#define AC97_POWER_PR3_BIT                  11
#define AC97_POWER_PR4_MASK                 0x1000          /* Digital interface (AC-link) powerdown (external clk off) */
#define AC97_POWER_PR4_BIT                  12
#define AC97_POWER_PR5_MASK                 0x2000          /* Internal clk disable */
#define AC97_POWER_PR5_BIT                  13
#define AC97_POWER_PR6_MASK                 0x4000          /* HP amp powerdown */
#define AC97_POWER_PR6_BIT                  14

#define AC97_POWER_EAPD_MASK                0x8000          /* External amplifier power down */
#define AC97_POWER_EAPD_BIT                 15

/* ------------------------------------------------ */
/* Vendor ID registers (index 0x20) */
/* */
#define AC97_CRIDX_VENDOR_ID1               0x7c            /* Vendor ID register 1 */
#define AC97_CRIDX_VENDOR_ID2               0x7e            /* Vendor ID register 2 */

/* Vendor ID 1 register definitions */
#define AC97_VENDOR_CHAR2_MASK              0x00ff          /* Second ascii char of vendor id */
#define AC97_VENDOR_CHAR2_SHIFT             0
#define AC97_VENDOR_CHAR1_MASK              0xff00          /* First ascii char of vendor id */
#define AC97_VENDOR_CHAR1_SHIFT             8

/* Vendor ID 2 register definitions */
#define AC97_VENDOR_REV_MASK                0x00ff          /* Vendor revision number */
#define AC97_VENDOR_REV_SHIFT               0
#define AC97_VENDOR_CHAR3_MASK              0xff00          /* Third ascii char of vendor id */
#define AC97_VENDOR_CHAR3_SHIFT             8

/*
 * Todo:
 *   Appendix A - AC97 2.0 Variable Sample Rate Extension
 *   Appendix B - AC97 2.0 Modem AFE Extension
 *   Appendix C - AC97 2.0 Multiple Codec Extension
 */

/*****************************************************************************
 * AC97 Driver-Supplement Helper Macros
 ****************************************************************************/

/* Make frame slot1 value to write AC97 codec register */
#define AC97_MAKE_WCMD_ADDR(idx)                                               \
    (((AC97_CMD_WRITE << AC97_CMDADDR_RW_BIT) & AC97_CMDADDR_RW_MASK) |        \
     (((uint32_t)(idx) << AC97_CMDADDR_CRIDX_SHIFT) & AC97_CMDADDR_CRIDX_MASK))

/* Make frame slot1 value to read AC97 codec register */
#define AC97_MAKE_RCMD_ADDR(idx)                                               \
    (((AC97_CMD_READ << AC97_CMDADDR_RW_BIT) & AC97_CMDADDR_RW_MASK) |         \
     (((uint32_t)(idx) << AC97_CMDADDR_CRIDX_SHIFT) & AC97_CMDADDR_CRIDX_MASK))

/* Make frame slot2 value to write AC97 codec register */
#define AC97_MAKE_CMD_DATA(data)                                               \
    (((uint32_t)(data) << AC97_CMDDATA_SHIFT) & AC97_CMDDATA_MASK)

/* Make frame slot1 and slot2 value to tx buffer for AC97 codec register write */
#define AC97_MAKE_WCMD(txb, idx, data)                                         \
    ((uint32_t *)(txb))[0] = AC97_MAKE_WCMD_ADDR(idx);                         \
    ((uint32_t *)(txb))[1] = AC97_MAKE_CMD_DATA(data);

/* Make frame slot1 and slot2 value to tx buffer for AC97 codec register read */
#define AC97_MAKE_RCMD(txb, idx, data)                                         \
    ((uint32_t *)(txb))[0] = AC97_MAKE_RCMD_ADDR(idx);                         \
    /*((uint32_t *)(txb))[1] = AC97_MAKE_CMD_DATA(data); */

/*******************************************************************************
 * Following helper functions imply non-20-bit msb-aligned sdata_out format
 ******************************************************************************/

/* Make codec stereo volume */
#define AC97_STEREO_VOLUME(l, r)                                               \
    ((((uint32_t)(l) << AC97_ML_SHIFT) & AC97_ML_MASK) |                       \
     (((uint32_t)(r) << AC97_MR_SHIFT) & AC97_MR_MASK))

/* Make codec mono volume */
#define AC97_MONO_VOLUME(m)                                                    \
    ((((uint32_t)(m) << AC97_MR_SHIFT) & AC97_MR_MASK))

/* Make tone (bass, treble) gain value */
#define AC97_TONE_GAIN(b, t)                                                   \
    ((((uint32_t)(b) << AC97_BASS_SHIFT) & AC97_BASS_MASK) |                   \
     (((uint32_t)(t) << AC97_TREBLE_SHIFT) & AC97_TREBLE_MASK))

/* Make pc-beep gain value */
#define AC97_PCBEEP_GAIN(g)                                                    \
    ((((uint32_t)(g) << AC97_MIXER_GR_SHIFT) & AC97_MIXER_GR_MASK))

/* Make mixer phone gain value */
#define AC97_PHONE_GAIN(m)                                                     \
    ((((uint32_t)(m) << AC97_PCBEEP_SHIFT) & AC97_PCBEEP_MASK))

/* Make mixer mic gain value */
#define AC97_MIC_GAIN(b, m)                                                    \
    ((((uint32_t)(m) << AC97_MIXER_GR_SHIFT) & AC97_MIXER_GR_MASK) |           \
     (((uint32_t)(b) << AC97_MIC_VOLUME_BOOST_BIT) & AC97_MIC_VOLUME_BOOST_MASK))

/* Make mixer gain value */
#define AC97_MIXER_GAIN(l, r)                                                  \
    ((((uint32_t)(l) << AC97_MIXER_GL_SHIFT) & AC97_MIXER_GL_MASK) |           \
     (((uint32_t)(r) << AC97_MIXER_GR_SHIFT) & AC97_MIXER_GR_MASK))

/* Make record select value */
#define AC97_RECORD_SELECT(l, r)                                               \
    ((((uint32_t)(l) << AC97_RECORD_SL_SHIFT) & AC97_RECORD_SL_MASK) |         \
     (((uint32_t)(r) << AC97_RECORD_SR_SHIFT) & AC97_RECORD_SR_MASK))

/* Make record gain value */
#define AC97_RECORD_GAIN(l, r)                                                 \
    ((((uint32_t)(l) << AC97_RECORD_GL_SHIFT) & AC97_RECORD_GL_MASK) |         \
     (((uint32_t)(r) << AC97_RECORD_GR_SHIFT) & AC97_RECORD_GR_MASK))

/* Make record mic gain value */
#define AC97_RECORD_MIC_GAIN(m)                                                \
    (((uint32_t)(m) << AC97_RECORD_GR_SHIFT) & AC97_RECORD_GR_MASK)

void ac97_init(void);
#endif /* __SSPD_AC97_H__ */
