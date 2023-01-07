/**
  ******************************************************************************
  * @file    bl808_audio.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __BL808_AUDIO_H__
#define __BL808_AUDIO_H__

#include "audio_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  AUDIO
 *  @{
 */

/** @defgroup  AUDIO_Public_Types
 *  @{
 */

/**
 *  @brief Audio ADC ID
 */
typedef enum {
    AUDIO_ADC_0, /*!< Audio ADC 0 */
    AUDIO_ADC_1, /*!< Audio ADC 1 */
    AUDIO_ADC_2, /*!< Audio ADC 2 */
} Audio_ADC_ID_Type;

/**
 *  @brief Audio DAC ID
 */
typedef enum {
    AUDIO_DAC_0, /*!< Audio DAC 0 */
    AUDIO_DAC_1, /*!< Audio DAC 1 */
} Audio_DAC_ID_Type;

/**
 *  @brief Audio AEC ID
 */
typedef enum {
    AUDIO_AEC_0, /*!< Audio AEC 0 */
    AUDIO_AEC_1, /*!< Audio AEC 1 */
} Audio_AEC_ID_Type;

/**
 *  @brief Audio PDM ID
 */
typedef enum {
    AUDIO_PDM_0, /*!< select PDM Channel 0 */
    AUDIO_PDM_1, /*!< select PDM Channel 1 */
    AUDIO_PDM_2, /*!< select PDM Channel 2 */
} Audio_PDM_ID_Type;

/**
 *  @brief Audio MUTE
 */
typedef enum {
    AUDIO_UNMUTE, /*!< unmute */
    AUDIO_MUTE,   /*!< mute */
} Audio_Mute_Type;

/**
 *  @brief Audio ADC Clock
 */
typedef enum {
    AUDIO_ADC_8_KHZ,  /*!< Audio ADC Clock set as 8KHZ */
    AUDIO_ADC_16_KHZ, /*!< Audio ADC Clock set as 16KHZ */
    AUDIO_ADC_24_KHZ, /*!< Audio ADC Clock set as 24KHZ */
    AUDIO_ADC_32_KHZ, /*!< Audio ADC Clock set as 32KHZ */
    AUDIO_ADC_48_KHZ, /*!< Audio ADC Clock set as 48KHZ */
    AUDIO_ADC_96_KHZ, /*!< Audio ADC Clock set as 96KHZ */
} Audio_ADC_Clock_Type;

/**
 *  @brief Audio DAC Clock
 */
typedef enum {
    AUDIO_DAC_8_KHZ,   /*!< Audio DAC Clock set as 8KHZ */
    AUDIO_DAC_16_KHZ,  /*!< Audio DAC Clock set as 16KHZ */
    AUDIO_DAC_24_KHZ,  /*!< Audio DAC Clock set as 24KHZ */
    AUDIO_DAC_32_KHZ,  /*!< Audio DAC Clock set as 32KHZ */
    AUDIO_DAC_48_KHZ,  /*!< Audio DAC Clock set as 48KHZ */
    AUDIO_DAC_96_KHZ,  /*!< Audio DAC Clock set as 96KHZ */
    AUDIO_DAC_192_KHZ, /*!< Audio DAC Clock set as 192KHZ */
} Audio_DAC_Clock_Type;

/**
 *  @brief Audio ADC Source Interface
 */
typedef enum {
    AUDIO_ADC_ANALOG, /*!< set AUDIO ADC as ANALOG mode connect AMIC */
    AUDIO_ADC_PDM,    /*!< set AUDIO ADC as PDM mode connect to DMIC */
} Audio_ADC_Source_Type;

/**
 *  @brief Audio LSFR Type
 */
typedef enum {
    AUDIO_LFSR32, /*!< Audio LFSR32 */
    AUDIO_LFSR24, /*!< Audio LFSR24 */
    AUDIO_LFSR16, /*!< Audio LFSR16 */
    AUDIO_LFSR12, /*!< Audio LFSR12 */
} Audio_LFSR_Type;

/**
 *  @brief Audio Mixer Mode
 */
typedef enum {
    AUDIO_SECOND_DEBUG_MODE = 0x1, /*!< Audio second mode debug mode */
    AUDIO_SIDETONE_LOOPBACK = 0x2, /*!< Audio sidetone mode mix will mixer dac with adc data */
} Audio_Mixer_Mode;

/**
 *  @brief Audio Mixer Volume Type
 */
typedef enum {
    AUDIO_MIXER_VOLUME_0_DB,  /*!< Audio Mix Volume 0DB */
    AUDIO_MIXER_VOLUME_6_DB,  /*!< Audio Mix Volume 6DB */
    AUDIO_MIXER_VOLUME_12_DB, /*!< Audio Mix Volume 12DB */
    AUDIO_MIXER_VOLUME_18_DB, /*!< Audio Mix Volume 18DB */
    AUDIO_MIXER_VOLUME_36_DB, /*!< Audio Mix Volume 36DB */
    AUDIO_MIXER_VOLUME_54_DB, /*!< Audio Mix Volume 54DB */
    AUDIO_MIXER_VOLUME_72_DB, /*!< Audio Mix Volume 72DB */
    AUDIO_MIXER_VOLUME_MUTE,  /*!< Audio Mix Volume Mute */
} Audio_Mixer_Volume_Type;

/**
 *  @brief Audio Mixer ID
 */
typedef enum {
    AUDIO_MIXER_ID_0, /*!< Audio Mix ID 0 */
    AUDIO_MIXER_ID_1, /*!< Audio Mix ID 1 */
} Audio_Mixer_ID_Type;

/**
 *  @brief Audio dac order
 */
typedef enum {
    AUDIO_DAC_2_ORDER, /*!< Audio ORDER 2 */
    AUDIO_DAC_3_ORDER, /*!< Audio ORDER 3 */
} Audio_DAC_Order_Type;

/**
 *  @brief Audio aec attenuation mode
 */
typedef enum {
    AUDIO_AEC_NO_DROP,    /*!< DROP 0 LSB */
    AUDIO_AEC_DROP_1LSB,  /*!< DROP 1 LSB */
    AUDIO_AEC_DROP_2LSB,  /*!< DROP 2 LSB */
    AUDIO_AEC_DROP_3LSB,  /*!< DROP 3 LSB */
    AUDIO_AEC_DROP_6LSB,  /*!< DROP 6 LSB */
    AUDIO_AEC_DROP_9LSB,  /*!< DROP 9 LSB */
    AUDIO_AEC_DROP_12LSB, /*!< DROP 12 LSB */
} Audio_AEC_Atten_Mode;

/**
 *  @brief Audio PDM Source Select
 */
typedef enum {
    AUDIO_PDM_0_L, /*!< select PDM0 Left  Channel */
    AUDIO_PDM_0_R, /*!< select PDM0 Right Channel */
    AUDIO_PDM_1_L, /*!< select PDM1 Left  Channel */
    AUDIO_PDM_1_R, /*!< select PDM1 Right Channel */
    AUDIO_PDM_2_L, /*!< select PDM2 Left  Channel */
    AUDIO_PDM_2_R, /*!< select PDM2 Right Channel */
} Audio_PDM_Source_Type;

/**
 *  @brief Audio Resolution
 */
typedef enum {
    AUDIO_RES_16_BITS, /*!< select ADC Resolution as 16 bit */
    AUDIO_RES_20_BITS, /*!< select ADC Resolution as 20 bit */
} Audio_Resolution_Type;

/**
 *  @brief Audio Resolution
 */
typedef enum {
    AUDIO_FIFO_AILGN_MSB_AT_BIT31, /*!< Mode 0: Valid data's MSB is at [31] of FIFO register */
    AUDIO_FIFO_AILGN_MSB_AT_BIT23, /*!< Mode 1: Valid data's MSB is at [23] of FIFO register */
    AUDIO_FIFO_AILGN_MSB_AT_BIT19, /*!< Mode 2: Valid data's MSB is at [19] of FIFO register */
    AUDIO_FIFO_AILGN_MSB_AT_BIT15, /*!< Mode 3: Valid data's MSB is at [15] of FIFO register */
} Audio_FIFO_Ailgn_Mode;

/**
 *  @brief Audio Resolution
 */
typedef enum {
    AUDIO_DRQ_EQUEL_TO_IRQ,       /*!< DMA request threhold is equeal to Interrupt threhold */
    AUDIO_DRQ_THR_AS_4_TX_8_RX,   /*!< DMA request threhold is 4 when config TX FIFO DRQ , 8 when config RX FIFO */
    AUDIO_DRQ_THR_AS_8_TX_16_RX,  /*!< DMA request threhold is 8 when config TX FIFO DRQ , 16 when config RX FIFO */
    AUDIO_DRQ_THR_AS_16_TX_32_RX, /*!< DMA request threhold is 16 when config TX FIFO DRQ , 32 when config RX FIFO */
} Audio_FIFO_DQR_Threshold_Mode;

/**
 *  @brief Audio initerrupt type
 */
typedef enum {
    AUDIO_INT_RX_FIFO_THR,          /*!< Audio RX FIFO counter upper than threhold interrupt */
    AUDIO_INT_RX_FIFO_OVERRUN,      /*!< Audio RX FIFO overrun */
    AUDIO_INT_RX_FIFO_UNDERRUN,     /*!< Audio RX FIFO underrun */
    AUDIO_INT_TX_FIFO_THR,          /*!< Audio TX FIFO THL */
    AUDIO_INT_TX_FIFO_OVERRUN,      /*!< Audio TX FIFO overrun */
    AUDIO_INT_TX_FIFO_UNDERRUN,     /*!< Audio TX FIFO underrun */
    AUDIO_INT_ADC0_SET_VOLUME_DONE, /*!< Audio set ADC0 volume done */
    AUDIO_INT_ADC1_SET_VOLUME_DONE, /*!< Audio set ADC1 volume done */
    AUDIO_INT_ADC2_SET_VOLUME_DONE, /*!< Audio set ADC2 volume done */
    AUDIO_INT_DAC0_SET_VOLUME_DONE, /*!< Audio set DAC0 volume done */
    AUDIO_INT_DAC1_SET_VOLUME_DONE, /*!< Audio set DAC1 volume done */
    AUDIO_INT_VAD,                  /*!< Audio VAD */
    AUDIO_INT_NUM_ALL,              /*!< Audio int all */
} Audio_INT_Type;

/**
 *  @brief Audio peq qtfm
 */
typedef enum {
    AUDIO_PEQ_QFMT_20_17, /*!< Audio QFMT 20.17 */
    AUDIO_PEQ_QFMT_20_16, /*!< Audio QFMT 20.16 */
} Audio_PEQ_QTFM_Type;

/**
 *  @brief Audio mute mode
 */
typedef enum {
    AUIDO_MUTE_DIRECTLY,       /*!< mute directly */
    AUDIO_MUTE_WITH_RAMP_DOWN, /*!< mute with rampdown */
} Audio_Mute_Mode;

/**
 *  @brief Audio ramp rate
 */
typedef enum {
    AUIDO_RAMP_RATE_2_FS,    /*!< ramp rate 2 fs */
    AUIDO_RAMP_RATE_4_FS,    /*!< ramp rate 4 fs */
    AUIDO_RAMP_RATE_8_FS,    /*!< ramp rate 8 fs */
    AUIDO_RAMP_RATE_16_FS,   /*!< ramp rate 16 fs */
    AUIDO_RAMP_RATE_32_FS,   /*!< ramp rate 32 fs */
    AUIDO_RAMP_RATE_64_FS,   /*!< ramp rate 64 fs */
    AUIDO_RAMP_RATE_128_FS,  /*!< ramp rate 128 fs */
    AUIDO_RAMP_RATE_256_FS,  /*!< ramp rate 256 fs */
    AUIDO_RAMP_RATE_512_FS,  /*!< ramp rate 512 fs */
    AUIDO_RAMP_RATE_1024_FS, /*!< ramp rate 1024 fs */
    AUIDO_RAMP_RATE_2048_FS, /*!< ramp rate 2048 fs */
} Audio_Ramp_Rate_Type;

/**
 *  @brief Audio zero cross rate
 */
typedef enum {
    AUIDO_ZERO_CROSS_RATE_2_FS,    /*!< ramp rate 2 fs */
    AUIDO_ZERO_CROSS_RATE_4_FS,    /*!< ramp rate 4 fs */
    AUIDO_ZERO_CROSS_RATE_8_FS,    /*!< ramp rate 8 fs */
    AUIDO_ZERO_CROSS_RATE_16_FS,   /*!< ramp rate 16 fs */
    AUIDO_ZERO_CROSS_RATE_32_FS,   /*!< ramp rate 32 fs */
    AUIDO_ZERO_CROSS_RATE_64_FS,   /*!< ramp rate 64 fs */
    AUIDO_ZERO_CROSS_RATE_128_FS,  /*!< ramp rate 128 fs */
    AUIDO_ZERO_CROSS_RATE_256_FS,  /*!< ramp rate 256 fs */
    AUIDO_ZERO_CROSS_RATE_512_FS,  /*!< ramp rate 512 fs */
    AUIDO_ZERO_CROSS_RATE_1024_FS, /*!< ramp rate 1024 fs */
    AUIDO_ZERO_CROSS_RATE_2048_FS, /*!< ramp rate 2048 fs */
} Audio_Zero_Cross_Rate_Type;

/**
 *  @brief Audio volume ctr mode
 */
typedef enum {
    AUIDO_VOLUME_UPDATE_FORCE,            /*!< volume update force */
    AUIDO_VOLUME_UPDATE_AT_ZERO_CROSSING, /*!< volume update at zero crossing */
    AUIDO_VOLUME_UPDATE_AT_RAMP,          /*!< volume update at zero crossing */
} Audio_Volume_Ctr_Mode;

/**
 *  @brief Audio_AGC_Detect_Mode
 */
typedef enum {
    AUIDO_AGC_DETECT_BY_PEAK,    /*!< detect by peak */
    AUIDO_AGC_DETECT_BY_AVERAGE, /*!< detect by average */
} Audio_AGC_Detect_Mode;

/**
 *  @brief Audio_AGC_Src_Type
 */
typedef enum {
    AUIDO_AGC_CH0_ABSOLUTE_VALUE,     /*!< Audio AGC CH0 */
    AUIDO_AGC_CH1_ABSOLUTE_VALUE,     /*!< Audio AGC CH1 */
    AUIDO_AGC_CH2_ABSOLUTE_VALUE,     /*!< Audio AGC CH2 */
    AUIDO_AGC_MAXIMUM_VALUE_OF_CH012, /*!< Audio AGC Max value of ch012 */
} Audio_AGC_Src_Type;

/**
 *  @brief Auido_DRC_Data_Type
 */
typedef enum {
    AUIDO_DRC_DATA_SOURCE_CH0,                /*!< Audio DRC SOURCE CH0 */
    AUIDO_DRC_DATA_SOURCE_CH1,                /*!< Audio DRC SOURCE CH1 */
    AUIDO_DRC_DATA_SOURCE_AVERAGE_OF_CH0_CH1, /*!< Audio DRC SOURCE (CH0+CH1)/2 */
    AUIDO_DRC_DATA_SOURCE_MAX_OF_CH0_CH1,     /*!< Audio DRC MAX(CH0,CH1) */
} Auido_DRC_Data_Type;

/**
 *  @brief Auido_VAD_Source_Type
 */
typedef enum {
    AUIDO_VAD_DATA_SOURCE_ADC_CH0,                 /*!< Audio ADC CH0 */
    AUIDO_VAD_DATA_SOURCE_ADC_CH1,                 /*!< Audio ADC CH1 */
    AUIDO_VAD_DATA_SOURCE_ADC_CH2,                 /*!< Audio ADC CH2 */
    AUIDO_VAD_DATA_SOURCE_AEC_CH0,                 /*!< Audio AEC CH0 */
    AUIDO_VAD_DATA_SOURCE_AEC_CH1,                 /*!< Audio AEC CH1 */
    AUDIO_VAD_DATA_SOURCE_AVERAGE_ADC_CH0_ADD_CH1, /*!< Audio (ADC0+ADC1)/2 */
    AUDIO_VAD_DATA_SOURCE_AVERAGE_ADC_CH1_ADD_CH2, /*!< Audio (ADC1+ADC2)/2 */
    AUDIO_VAD_DATA_SOURCE_AVERAGE_ADC_CH2_ADD_CH0, /*!< Audio (ADC2+ADC0)/2 */
} Auido_VAD_Source_Type;

/**
 *  @brief Auido_VAD_FramingShift_Type
 */
typedef enum {
    AUIDO_VAD_FRAMING_SHIFT_2P5_MS,  /*!< Audio VAD FramingShift = 2.5 */
    AUIDO_VAD_FRAMING_SHIFT_5_MS,    /*!< Audio VAD FramingShift = 5 */
    AUIDO_VAD_FRAMING_SHIFT_7P5_MS,  /*!< Audio VAD FramingShift = 7.5 */
    AUIDO_VAD_FRAMING_SHIFT_10_MS,   /*!< Audio VAD FramingShift = 10 */
    AUIDO_VAD_FRAMING_SHIFT_12P5_MS, /*!< Audio VAD FramingShift = 12.5 */
    AUIDO_VAD_FRAMING_SHIFT_15_MS,   /*!< Audio VAD FramingShift = 15 */
    AUIDO_VAD_FRAMING_SHIFT_17P5_MS, /*!< Audio VAD FramingShift = 17.5 */
    AUIDO_VAD_FRAMING_SHIFT_20_MS,   /*!< Audio VAD FramingShift = 20 */
} Auido_VAD_FramingShift_Type;

/**
 *  @brief Auido_VAD_FramingTime_Type
 */
typedef enum {
    AUIDO_VAD_FRAMING_TIME_2, /*!< Audio VAD FramingTime  K= 2 */
    AUIDO_VAD_FRAMING_TIME_3, /*!< Audio VAD FramingTime  K= 3 */
    AUIDO_VAD_FRAMING_TIME_4, /*!< Audio VAD FramingTime  K= 4 */
    AUIDO_VAD_FRAMING_TIME_5, /*!< Audio VAD FramingTime  K= 5 */
} Auido_VAD_FramingTime_Type;

/**
 *  @brief Auido_VAD_FramingTime_Type
 */
typedef enum {
    AUIDO_VAD_ORIGINAL_OUTPUT, /*!< Original VAD output(VAD00) */
    AUIDO_VAD_OUT0,            /*!< Debounced VAD output(VADout0), with small NDV but large DL */
    AUIDO_VAD_OUT1,            /*!< Debounced VAD output(VADout1) */
    AUIDO_VAD_OUT2,            /*!< Debounced VAD output(VADout2), with small DL but large NDV */
} Auido_VAD_IRQ_Source_Type;

/**
 *  @brief Auido_VAD_NoisyBufferLen_Type
 */
typedef enum {
    AUIDO_VAD_NOISY_BUF_LEN_4,  /*!< noise buffer length control 4 */
    AUIDO_VAD_NOISY_BUF_LEN_8,  /*!< noise buffer length control 8 */
    AUIDO_VAD_NOISY_BUF_LEN_12, /*!< noise buffer length control 12 */
    AUIDO_VAD_NOISY_BUF_LEN_16, /*!< noise buffer length control 16 */
    AUIDO_VAD_NOISY_BUF_LEN_20, /*!< noise buffer length control 20 */
    AUIDO_VAD_NOISY_BUF_LEN_24, /*!< noise buffer length control 24 */
    AUIDO_VAD_NOISY_BUF_LEN_28, /*!< noise buffer length control 28 */
    AUIDO_VAD_NOISY_BUF_LEN_32, /*!< noise buffer length control 32 */
} Auido_VAD_NoisyBufferLen_Type;

/**
 *  @brief noise buffer monitor control, forcing noise buffer to refresh when both:VAD goes into high and VAD high last for2'h0: 1s2'h1: 2s2'h2: 4s 2'h3: 8s this monit function is designed in case that VAD is locked into active state and noise buffer no longer refreshes itself. this will happen when audio-background-noise suddenly changes from a relative low level to a much higher one
 */
typedef enum {
    AUIDO_VAD_NOISY_MONITOR_1_S, /*!< noise monitor 1 s */
    AUIDO_VAD_NOISY_MONITOR_2_S, /*!< noise monitor 2 s */
    AUIDO_VAD_NOISY_MONITOR_4_S, /*!< noise monitor 4 s */
    AUIDO_VAD_NOISY_MONITOR_8_S, /*!< noise monitor 8 s */
} Auido_VAD_NoisyBufferMonitor_Type;

/**
 *  @brief Audio Clock Configuration
 */
typedef struct {
    Audio_ADC_Clock_Type adc_clock; /*!< ADC Rate Configuration */
    Audio_DAC_Clock_Type dac_clock; /*!< DAC Rate Configuration */
    BL_Fun_Type pdm_clk_inv;        /*!< enable or not pdm clock inv */
    BL_Fun_Type adc_clk_inv;        /*!< enable or not adc clock inv */
    BL_Fun_Type dac_clk_inv;        /*!< enable or not dac clock inv */
} Audio_Clock_CFG_Type;

/**
 *  @brief Audio FIFO Configuration
 */
typedef struct {
    Audio_Resolution_Type resolution;               /*!< Receiving Audio Sample Resolution */
    Audio_FIFO_Ailgn_Mode ailgnMode;                /*!< FIFO alignMode */
    uint8_t FifoIntThreshold;                       /*!< FIFO IRQ Threshold */
    Audio_FIFO_DQR_Threshold_Mode dmaThresholdMode; /*!< FIFO DRQ Threshold mode */
    BL_Fun_Type dmaEn;                              /*!< enable DMA FIFO interface */
} Audio_FifoCfg_Type;

/**
 *  @brief Audio Volume Configuration
 */
typedef struct {
    Audio_Mute_Mode muteMode;                          /*!< Audio mute mode   directly mute or use ramp down */
    Audio_Ramp_Rate_Type muteRmpdnRate;                /*!< mute ramp down rate when voice is in up process this parameter define slope */
    Audio_Ramp_Rate_Type muteRmpupRate;                /*!< mute ramp up rate when voice is in down process this parameter define slop */
    Audio_Volume_Ctr_Mode volumeCtrMode;               /*!< volume will update at direct or zero crossing or ramp */
    Audio_Zero_Cross_Rate_Type volumeZeroCrossRate;    /*!< when volume ctrl is zero crossing , select crossing rate */
    Audio_Ramp_Rate_Type volumeRmpRate;                /*!< when volume ctrl is ramp ,select ramp rate */
    Audio_Zero_Cross_Rate_Type volumeZeroCrossTimeout; /*!< if select zero cross mode ,  set volume directly when time out */
} Audio_Volume_Cfg_Type;

/**
 *  @brief Audio VAD Configuration
 */
typedef struct {
    Auido_VAD_Source_Type vadSource;                         /*!< VAD source select */
    Auido_VAD_FramingShift_Type vadFramingShift;             /*!< framing-shift control */
    Auido_VAD_FramingTime_Type vadFramingTime;               /*!< framing-time control, K times of framing-shift */
    Auido_VAD_IRQ_Source_Type vadIRQSource;                  /*!< select witch VAD output as final IRQ */
    BL_Fun_Type vadNoisyBufferMonitorEnable;                 /*!< enable or not noisy buffer monitor */
    Auido_VAD_NoisyBufferLen_Type vadNoisyBufferLen;         /*!< noise buffer length control */
    Auido_VAD_NoisyBufferMonitor_Type vadNoisyBufferMonitor; /*!< this monit function is designed in case that VAD is locked into active state and noise buffer 
                                                 no longer refreshes itself. this will happen when audio-background-noise suddenly changes from a 
                                                 relative low level to a much higher one */
    uint32_t noisyBufferThr;                                 /*!< vad_noise_th */
    uint8_t noisyBufferDiscardNumber;                        /*!< noise buffer discard number: */
    uint16_t noisyBufferThrBais;                             /*!< bias for noise threshold(s8.8, 2's) */
    uint8_t noisyBufferThrScale;                             /*!< noise threshold scale factor, real scale factor in circuit=dec(nth_scale)/256 */
    uint16_t vadNoisyMaxLimit;                               /*!< noise threshold max limitation */
    BL_Fun_Type vadNoisyMaxLimitEnable;                      /*!< noise threshold max limitation enable signal */
    uint16_t vadNoisyMinLimit;                               /*!< noise threshold min limitation */
    BL_Fun_Type vadNoisyMinLimitEnable;                      /*!< noise threshold min limitation enable signal */
    uint16_t vadSmoothRise;                                  /*!< VAD output debouce, remove the positive pulse whose width is smaller than Register Value, the 
                                                 real debouce time = Resister Vale * framing-shift */
    uint16_t vadSmoothFall;                                  /*!< VAD output debouce, remove the negative pulse whose width is smaller than Register Value, the 
                                                 real debouce time = Resister Vale * framing-shift */
} Audio_VAD_Cfg_Type;

/**
 *  @brief Audio agc Config
 */
typedef struct {
    BL_Fun_Type agc_force_gain_en;         /*!< 1 force agc gain */
    uint16_t agc_force_gain_ind;           /*!< force agc gain index //default 0 -6-24 */
    uint16_t agc_max_gain_qdb;             /*!< agc maximun gain //default 24 -6-24 */
    uint16_t agc_min_gain_qdb;             /*!< agc minimum gain */
    uint8_t agc_level_target;              /*!< agc level target //default-12 -6--20 */
    uint8_t agc_level_hyst_attack;         /*!< agc level hysteresis attack */
    uint8_t agc_level_hyst_decay;          /*!< agc level hysteresis decay */
    uint8_t agc_hold_time_ms;              /*!< agc hold time(ms)//0-32,1-64,2-96,3-128,4-256,5-512 default 96 */
    uint8_t agc_decay_time_ms;             /*!< agc decay time(ms) //0-32,1-64,2-96,3-128,4-256,5-512 default 64 */
    uint8_t agc_attack_time_ms;            /*!< agc attack time(ms) //0-8,1-16,2-24,3-32,4-64,5-128 default 16 */
    BL_Fun_Type adc3_pga_hw_ctrl;          /*!< 1 enable hw control */
    BL_Fun_Type adc2_pga_hw_ctrl;          /*!< 1 enable hw control */
    BL_Fun_Type adc1_pga_hw_ctrl;          /*!< 1 enable hw control */
    uint8_t agc_noise_gate_th;             /*!< agc noise gate threshold //default -48 -32--72 */
    uint8_t agc_noise_gate_hyst;           /*!< agc noise gate hysteresis //default 2 0/1/2/4 */
    uint8_t agc_silence_gain_qdb;          /*!< agc silence gain qdb //s9.2, default 0 */
    uint8_t agc_silence_gain_wait_ms;      /*!< agc silence gain wait time(ms) */
    uint8_t agc_noise_enter_time_ms;       /*!< agc noise enter time //default 0 NORMAL_SILENCE_DEBOUNCE_TIME_MS 0/1/2/4/8/16/32/64/96/128 */
    uint8_t agc_noise_exit_time_ms;        /*!< agc noise exit time(ms) //default 0 SILENCE_NORMAL_DEBOUNCE_TIME_MS 0/1/2/4/8/16/32/64/96/128 */
    uint8_t agc_dbv_settle_time;           /*!< agc dbv settle time */
    Audio_AGC_Src_Type agc_src_select;     /*!< agc source select  0 ch0 absolute value, 1 ch1 absolute value, 2 ch2 absolute value, 3 maximum 
                                                 value of ch0/1/2 */
    Audio_AGC_Detect_Mode agc_detect_mode; /*!< 0 detect by peak, 1 detect by average */
    uint8_t agc_attack_time;               /*!< agc peak filter attack time */
    uint8_t agc_release_time;              /*!< agc peak filter release time */
    uint8_t agc_average_time;              /*!< agc rms filter average time */
    BL_Fun_Type agc_pga_ctrl_en;           /*!< 1 enable pga controlled by hw agc */
} Audio_AGC_Config_Type;

/**
 *  @brief Audio agc Config
 */
typedef struct {
    Auido_DRC_Data_Type drc_raw_sel;  /*!< drc raw data select 0 ch0, 1 ch1, 2 (ch0+ch1)/2, 3  max(ch0,ch1) */
    Auido_DRC_Data_Type drc_peak_sel; /*!< drc peak data select 0 ch0, 1 ch1, 2 (ch0+ch1)/2, 3  max(ch0,ch1) */
    Auido_DRC_Data_Type drc_avg_sel;  /*!< drc average data select  0 ch0, 1 ch1, 2 (ch0+ch1)/2, 3  max(ch0,ch1) */
    BL_Fun_Type drc_avg_en;           /*!< 1 enable average filter */
    uint8_t drc_avg_time;             /*!< drc average filter period */
    uint8_t drc_att_time;             /*!< drc peak filter attack time */
    uint8_t drc_rls_time;             /*!< drc peak filter release time */
    uint8_t drc_ngt_downsample_en;    /*!< 1 drc and noise gate down sample by dac_rate */
    uint8_t drc_threshold_l;          /*!< drc threshold of limiter */
    uint8_t drc_threshold_c;          /*!< drc threshold of compressor */
    uint8_t drc_threshold_e;          /*!< drc threshold of expander */
    uint8_t drc_slope_mode_c;         /*!< drc compressor slope mode   0 1-8/8, 1 1-5/8, 2 1-4/8, 3 1-2/8 */
    uint8_t drc_slope_mode_e;         /*!< drc expander slope mode  0 0, 1 -1, 2 -2, 3 -3 */
    uint8_t drc_makeup_gain;          /*!< drc make up gain */
    uint8_t drc_attack_time;          /*!< drc attack time */
    uint8_t drc_release_time;         /*!< drc release time */
    BL_Fun_Type ngt_en;               /*!< 1 enable noise gate */
    Auido_DRC_Data_Type ngt_src_sel;  /*!< noise gate source select  0 ch0, 1 ch1, 2 (ch0+ch1)/2, 3 max(ch0,ch1) */
    uint8_t ngt_avg_time;             /*!< noise gate average time */
    uint8_t ngt_threshold;            /*!< noise gate threshold */
    uint8_t ngt_hysteresis;           /*!< noise gate hysteresis */
    BL_Fun_Type ngt_noise_hold_en;    /*!< noise hold enable */
    uint8_t ngt_noise_hold_time_k;    /*!< noise hold time k */
    BL_Fun_Type ngt_signal_hold_en;   /*!< signal hold enable */
    uint8_t ngt_signal_hold_time_k;   /*!< signal hold time k */
    BL_Fun_Type ngt_dmute_on;         /*!< 1 enanle noise gate mute hw */
    BL_Fun_Type zd_en;                /*!< two channels, 0 zd disabled, 1  zd on channel0, 2 zd on channel1, 3 zd on both channels */
    uint16_t zd_time;                 /*!< number of zeros */
} Audio_DRC_Config_Type;

/*@} end of group AUDIO_Public_Types */

/** @defgroup  AUDIO_Public_Constants
 *  @{
 */

/** @defgroup  AUDIO_ADC_ID_TYPE
 *  @{
 */
#define IS_AUDIO_ADC_ID_TYPE(type) (((type) == AUDIO_ADC_0) || \
                                    ((type) == AUDIO_ADC_1) || \
                                    ((type) == AUDIO_ADC_2))

/** @defgroup  AUDIO_DAC_ID_TYPE
 *  @{
 */
#define IS_AUDIO_DAC_ID_TYPE(type) (((type) == AUDIO_DAC_0) || \
                                    ((type) == AUDIO_DAC_1))

/** @defgroup  AUDIO_AEC_ID_TYPE
 *  @{
 */
#define IS_AUDIO_AEC_ID_TYPE(type) (((type) == AUDIO_AEC_0) || \
                                    ((type) == AUDIO_AEC_1))

/** @defgroup  AUDIO_PDM_ID_TYPE
 *  @{
 */
#define IS_AUDIO_PDM_ID_TYPE(type) (((type) == AUDIO_PDM_0) || \
                                    ((type) == AUDIO_PDM_1) || \
                                    ((type) == AUDIO_PDM_2))

/** @defgroup  AUDIO_MUTE_TYPE
 *  @{
 */
#define IS_AUDIO_MUTE_TYPE(type) (((type) == AUDIO_UNMUTE) || \
                                  ((type) == AUDIO_MUTE))

/** @defgroup  AUDIO_ADC_CLOCK_TYPE
 *  @{
 */
#define IS_AUDIO_ADC_CLOCK_TYPE(type) (((type) == AUDIO_ADC_8_KHZ) ||  \
                                       ((type) == AUDIO_ADC_16_KHZ) || \
                                       ((type) == AUDIO_ADC_24_KHZ) || \
                                       ((type) == AUDIO_ADC_32_KHZ) || \
                                       ((type) == AUDIO_ADC_48_KHZ) || \
                                       ((type) == AUDIO_ADC_96_KHZ))

/** @defgroup  AUDIO_DAC_CLOCK_TYPE
 *  @{
 */
#define IS_AUDIO_DAC_CLOCK_TYPE(type) (((type) == AUDIO_DAC_8_KHZ) ||  \
                                       ((type) == AUDIO_DAC_16_KHZ) || \
                                       ((type) == AUDIO_DAC_24_KHZ) || \
                                       ((type) == AUDIO_DAC_32_KHZ) || \
                                       ((type) == AUDIO_DAC_48_KHZ) || \
                                       ((type) == AUDIO_DAC_96_KHZ) || \
                                       ((type) == AUDIO_DAC_192_KHZ))

/** @defgroup  AUDIO_ADC_SOURCE_TYPE
 *  @{
 */
#define IS_AUDIO_ADC_SOURCE_TYPE(type) (((type) == AUDIO_ADC_ANALOG) || \
                                        ((type) == AUDIO_ADC_PDM))

/** @defgroup  AUDIO_LFSR_TYPE
 *  @{
 */
#define IS_AUDIO_LFSR_TYPE(type) (((type) == AUDIO_LFSR32) || \
                                  ((type) == AUDIO_LFSR24) || \
                                  ((type) == AUDIO_LFSR16) || \
                                  ((type) == AUDIO_LFSR12))

/** @defgroup  AUDIO_MIXER_MODE
 *  @{
 */
#define IS_AUDIO_MIXER_MODE(type) (((type) == AUDIO_SECOND_DEBUG_MODE) || \
                                   ((type) == AUDIO_SIDETONE_LOOPBACK))

/** @defgroup  AUDIO_MIXER_VOLUME_TYPE
 *  @{
 */
#define IS_AUDIO_MIXER_VOLUME_TYPE(type) (((type) == AUDIO_MIXER_VOLUME_0_DB) ||  \
                                          ((type) == AUDIO_MIXER_VOLUME_6_DB) ||  \
                                          ((type) == AUDIO_MIXER_VOLUME_12_DB) || \
                                          ((type) == AUDIO_MIXER_VOLUME_18_DB) || \
                                          ((type) == AUDIO_MIXER_VOLUME_36_DB) || \
                                          ((type) == AUDIO_MIXER_VOLUME_54_DB) || \
                                          ((type) == AUDIO_MIXER_VOLUME_72_DB) || \
                                          ((type) == AUDIO_MIXER_VOLUME_MUTE))

/** @defgroup  AUDIO_MIXER_ID_TYPE
 *  @{
 */
#define IS_AUDIO_MIXER_ID_TYPE(type) (((type) == AUDIO_MIXER_ID_0) || \
                                      ((type) == AUDIO_MIXER_ID_1))

/** @defgroup  AUDIO_DAC_ORDER_TYPE
 *  @{
 */
#define IS_AUDIO_DAC_ORDER_TYPE(type) (((type) == AUDIO_DAC_2_ORDER) || \
                                       ((type) == AUDIO_DAC_3_ORDER))

/** @defgroup  AUDIO_AEC_ATTEN_MODE
 *  @{
 */
#define IS_AUDIO_AEC_ATTEN_MODE(type) (((type) == AUDIO_AEC_NO_DROP) ||   \
                                       ((type) == AUDIO_AEC_DROP_1LSB) || \
                                       ((type) == AUDIO_AEC_DROP_2LSB) || \
                                       ((type) == AUDIO_AEC_DROP_3LSB) || \
                                       ((type) == AUDIO_AEC_DROP_6LSB) || \
                                       ((type) == AUDIO_AEC_DROP_9LSB) || \
                                       ((type) == AUDIO_AEC_DROP_12LSB))

/** @defgroup  AUDIO_PDM_SOURCE_TYPE
 *  @{
 */
#define IS_AUDIO_PDM_SOURCE_TYPE(type) (((type) == AUDIO_PDM_0_L) || \
                                        ((type) == AUDIO_PDM_0_R) || \
                                        ((type) == AUDIO_PDM_1_L) || \
                                        ((type) == AUDIO_PDM_1_R) || \
                                        ((type) == AUDIO_PDM_2_L) || \
                                        ((type) == AUDIO_PDM_2_R))

/** @defgroup  AUDIO_RESOLUTION_TYPE
 *  @{
 */
#define IS_AUDIO_RESOLUTION_TYPE(type) (((type) == AUDIO_RES_16_BITS) || \
                                        ((type) == AUDIO_RES_20_BITS))

/** @defgroup  AUDIO_FIFO_AILGN_MODE
 *  @{
 */
#define IS_AUDIO_FIFO_AILGN_MODE(type) (((type) == AUDIO_FIFO_AILGN_MSB_AT_BIT31) || \
                                        ((type) == AUDIO_FIFO_AILGN_MSB_AT_BIT23) || \
                                        ((type) == AUDIO_FIFO_AILGN_MSB_AT_BIT19) || \
                                        ((type) == AUDIO_FIFO_AILGN_MSB_AT_BIT15))

/** @defgroup  AUDIO_FIFO_DQR_THRESHOLD_MODE
 *  @{
 */
#define IS_AUDIO_FIFO_DQR_THRESHOLD_MODE(type) (((type) == AUDIO_DRQ_EQUEL_TO_IRQ) ||      \
                                                ((type) == AUDIO_DRQ_THR_AS_4_TX_8_RX) ||  \
                                                ((type) == AUDIO_DRQ_THR_AS_8_TX_16_RX) || \
                                                ((type) == AUDIO_DRQ_THR_AS_16_TX_32_RX))

/** @defgroup  AUDIO_INT_TYPE
 *  @{
 */
#define IS_AUDIO_INT_TYPE(type) (((type) == AUDIO_INT_RX_FIFO_THR) ||          \
                                 ((type) == AUDIO_INT_RX_FIFO_OVERRUN) ||      \
                                 ((type) == AUDIO_INT_RX_FIFO_UNDERRUN) ||     \
                                 ((type) == AUDIO_INT_TX_FIFO_THR) ||          \
                                 ((type) == AUDIO_INT_TX_FIFO_OVERRUN) ||      \
                                 ((type) == AUDIO_INT_TX_FIFO_UNDERRUN) ||     \
                                 ((type) == AUDIO_INT_ADC0_SET_VOLUME_DONE) || \
                                 ((type) == AUDIO_INT_ADC1_SET_VOLUME_DONE) || \
                                 ((type) == AUDIO_INT_ADC2_SET_VOLUME_DONE) || \
                                 ((type) == AUDIO_INT_DAC0_SET_VOLUME_DONE) || \
                                 ((type) == AUDIO_INT_DAC1_SET_VOLUME_DONE) || \
                                 ((type) == AUDIO_INT_VAD) ||                  \
                                 ((type) == AUDIO_INT_NUM_ALL))

/** @defgroup  AUDIO_PEQ_QTFM_TYPE
 *  @{
 */
#define IS_AUDIO_PEQ_QTFM_TYPE(type) (((type) == AUDIO_PEQ_QFMT_20_17) || \
                                      ((type) == AUDIO_PEQ_QFMT_20_16))

/** @defgroup  AUDIO_MUTE_MODE
 *  @{
 */
#define IS_AUDIO_MUTE_MODE(type) (((type) == AUIDO_MUTE_DIRECTLY) || \
                                  ((type) == AUDIO_MUTE_WITH_RAMP_DOWN))

/** @defgroup  AUDIO_RAMP_RATE_TYPE
 *  @{
 */
#define IS_AUDIO_RAMP_RATE_TYPE(type) (((type) == AUIDO_RAMP_RATE_2_FS) ||    \
                                       ((type) == AUIDO_RAMP_RATE_4_FS) ||    \
                                       ((type) == AUIDO_RAMP_RATE_8_FS) ||    \
                                       ((type) == AUIDO_RAMP_RATE_16_FS) ||   \
                                       ((type) == AUIDO_RAMP_RATE_32_FS) ||   \
                                       ((type) == AUIDO_RAMP_RATE_64_FS) ||   \
                                       ((type) == AUIDO_RAMP_RATE_128_FS) ||  \
                                       ((type) == AUIDO_RAMP_RATE_256_FS) ||  \
                                       ((type) == AUIDO_RAMP_RATE_512_FS) ||  \
                                       ((type) == AUIDO_RAMP_RATE_1024_FS) || \
                                       ((type) == AUIDO_RAMP_RATE_2048_FS))

/** @defgroup  AUDIO_ZERO_CROSS_RATE_TYPE
 *  @{
 */
#define IS_AUDIO_ZERO_CROSS_RATE_TYPE(type) (((type) == AUIDO_ZERO_CROSS_RATE_2_FS) ||    \
                                             ((type) == AUIDO_ZERO_CROSS_RATE_4_FS) ||    \
                                             ((type) == AUIDO_ZERO_CROSS_RATE_8_FS) ||    \
                                             ((type) == AUIDO_ZERO_CROSS_RATE_16_FS) ||   \
                                             ((type) == AUIDO_ZERO_CROSS_RATE_32_FS) ||   \
                                             ((type) == AUIDO_ZERO_CROSS_RATE_64_FS) ||   \
                                             ((type) == AUIDO_ZERO_CROSS_RATE_128_FS) ||  \
                                             ((type) == AUIDO_ZERO_CROSS_RATE_256_FS) ||  \
                                             ((type) == AUIDO_ZERO_CROSS_RATE_512_FS) ||  \
                                             ((type) == AUIDO_ZERO_CROSS_RATE_1024_FS) || \
                                             ((type) == AUIDO_ZERO_CROSS_RATE_2048_FS))

/** @defgroup  AUDIO_VOLUME_CTR_MODE
 *  @{
 */
#define IS_AUDIO_VOLUME_CTR_MODE(type) (((type) == AUIDO_VOLUME_UPDATE_FORCE) ||            \
                                        ((type) == AUIDO_VOLUME_UPDATE_AT_ZERO_CROSSING) || \
                                        ((type) == AUIDO_VOLUME_UPDATE_AT_RAMP))

/** @defgroup  AUDIO_AGC_DETECT_MODE
 *  @{
 */
#define IS_AUDIO_AGC_DETECT_MODE(type) (((type) == AUIDO_AGC_DETECT_BY_PEAK) || \
                                        ((type) == AUIDO_AGC_DETECT_BY_AVERAGE))

/** @defgroup  AUDIO_AGC_SRC_TYPE
 *  @{
 */
#define IS_AUDIO_AGC_SRC_TYPE(type) (((type) == AUIDO_AGC_CH0_ABSOLUTE_VALUE) || \
                                     ((type) == AUIDO_AGC_CH1_ABSOLUTE_VALUE) || \
                                     ((type) == AUIDO_AGC_CH2_ABSOLUTE_VALUE) || \
                                     ((type) == AUIDO_AGC_MAXIMUM_VALUE_OF_CH012))

/** @defgroup  AUIDO_DRC_DATA_TYPE
 *  @{
 */
#define IS_AUIDO_DRC_DATA_TYPE(type) (((type) == AUIDO_DRC_DATA_SOURCE_CH0) ||                \
                                      ((type) == AUIDO_DRC_DATA_SOURCE_CH1) ||                \
                                      ((type) == AUIDO_DRC_DATA_SOURCE_AVERAGE_OF_CH0_CH1) || \
                                      ((type) == AUIDO_DRC_DATA_SOURCE_MAX_OF_CH0_CH1))

/** @defgroup  AUIDO_VAD_SOURCE_TYPE
 *  @{
 */
#define IS_AUIDO_VAD_SOURCE_TYPE(type) (((type) == AUIDO_VAD_DATA_SOURCE_ADC_CH0) ||                 \
                                        ((type) == AUIDO_VAD_DATA_SOURCE_ADC_CH1) ||                 \
                                        ((type) == AUIDO_VAD_DATA_SOURCE_ADC_CH2) ||                 \
                                        ((type) == AUIDO_VAD_DATA_SOURCE_AEC_CH0) ||                 \
                                        ((type) == AUIDO_VAD_DATA_SOURCE_AEC_CH1) ||                 \
                                        ((type) == AUDIO_VAD_DATA_SOURCE_AVERAGE_ADC_CH0_ADD_CH1) || \
                                        ((type) == AUDIO_VAD_DATA_SOURCE_AVERAGE_ADC_CH1_ADD_CH2) || \
                                        ((type) == AUDIO_VAD_DATA_SOURCE_AVERAGE_ADC_CH2_ADD_CH0))

/** @defgroup  AUIDO_VAD_FRAMINGSHIFT_TYPE
 *  @{
 */
#define IS_AUIDO_VAD_FRAMINGSHIFT_TYPE(type) (((type) == AUIDO_VAD_FRAMING_SHIFT_2P5_MS) ||  \
                                              ((type) == AUIDO_VAD_FRAMING_SHIFT_5_MS) ||    \
                                              ((type) == AUIDO_VAD_FRAMING_SHIFT_7P5_MS) ||  \
                                              ((type) == AUIDO_VAD_FRAMING_SHIFT_10_MS) ||   \
                                              ((type) == AUIDO_VAD_FRAMING_SHIFT_12P5_MS) || \
                                              ((type) == AUIDO_VAD_FRAMING_SHIFT_15_MS) ||   \
                                              ((type) == AUIDO_VAD_FRAMING_SHIFT_17P5_MS) || \
                                              ((type) == AUIDO_VAD_FRAMING_SHIFT_20_MS))

/** @defgroup  AUIDO_VAD_FRAMINGTIME_TYPE
 *  @{
 */
#define IS_AUIDO_VAD_FRAMINGTIME_TYPE(type) (((type) == AUIDO_VAD_FRAMING_TIME_2) || \
                                             ((type) == AUIDO_VAD_FRAMING_TIME_3) || \
                                             ((type) == AUIDO_VAD_FRAMING_TIME_4) || \
                                             ((type) == AUIDO_VAD_FRAMING_TIME_5))

/** @defgroup  AUIDO_VAD_IRQ_SOURCE_TYPE
 *  @{
 */
#define IS_AUIDO_VAD_IRQ_SOURCE_TYPE(type) (((type) == AUIDO_VAD_ORIGINAL_OUTPUT) || \
                                            ((type) == AUIDO_VAD_OUT0) ||            \
                                            ((type) == AUIDO_VAD_OUT1) ||            \
                                            ((type) == AUIDO_VAD_OUT2))

/** @defgroup  AUIDO_VAD_NOISYBUFFERLEN_TYPE
 *  @{
 */
#define IS_AUIDO_VAD_NOISYBUFFERLEN_TYPE(type) (((type) == AUIDO_VAD_NOISY_BUF_LEN_4) ||  \
                                                ((type) == AUIDO_VAD_NOISY_BUF_LEN_8) ||  \
                                                ((type) == AUIDO_VAD_NOISY_BUF_LEN_12) || \
                                                ((type) == AUIDO_VAD_NOISY_BUF_LEN_16) || \
                                                ((type) == AUIDO_VAD_NOISY_BUF_LEN_20) || \
                                                ((type) == AUIDO_VAD_NOISY_BUF_LEN_24) || \
                                                ((type) == AUIDO_VAD_NOISY_BUF_LEN_28) || \
                                                ((type) == AUIDO_VAD_NOISY_BUF_LEN_32))

/** @defgroup  AUIDO_VAD_NOISYBUFFERMONITOR_TYPE
 *  @{
 */
#define IS_AUIDO_VAD_NOISYBUFFERMONITOR_TYPE(type) (((type) == AUIDO_VAD_NOISY_MONITOR_1_S) || \
                                                    ((type) == AUIDO_VAD_NOISY_MONITOR_2_S) || \
                                                    ((type) == AUIDO_VAD_NOISY_MONITOR_4_S) || \
                                                    ((type) == AUIDO_VAD_NOISY_MONITOR_8_S))

/*@} end of group AUDIO_Public_Constants */

/** @defgroup  AUDIO_Public_Macros
 *  @{
 */
#define AUDIO_PRIVATE_BIT_POS(n)  (0x01 << n)
#define ADC1_DATA_CHANNEL_FIFO_EN AUDIO_PRIVATE_BIT_POS(0)
#define ADC2_DATA_CHANNEL_FIFO_EN AUDIO_PRIVATE_BIT_POS(1)
#define ADC3_DATA_CHANNEL_FIFO_EN AUDIO_PRIVATE_BIT_POS(2)
#define AEC1_DATA_CHANNEL_FIFO_EN AUDIO_PRIVATE_BIT_POS(3)
#define AEC2_DATA_CHANNEL_FIFO_EN AUDIO_PRIVATE_BIT_POS(4)
#define DAC1_DATA_CHANNEL_FIFO_EN AUDIO_PRIVATE_BIT_POS(0)
#define DAC2_DATA_CHANNEL_FIFO_EN AUDIO_PRIVATE_BIT_POS(1)

/*@} end of group AUDIO_Public_Macros */

/** @defgroup  AUDIO_Public_Functions
 *  @{
 */
void Audio_Clock_Init(Audio_Clock_CFG_Type *cfg);
//debug api
void Debug0_Write(uint32_t wCmd);
uint32_t Debug1_Read(void);
void Debug2_Write(uint32_t wCmd);
void Debug3_Write(uint32_t wCmd);
//
BL_Err_Type Audio_Tx_Source_DAC_Sel(uint8_t tx_channel, Audio_DAC_ID_Type dac_id);
BL_Err_Type Audio_Rx_Source_ADC_Sel(uint8_t rx_channel, Audio_ADC_ID_Type adc_id);
BL_Err_Type Audio_Rx_Source_AEC_Sel(uint8_t rx_channel, Audio_AEC_ID_Type aec_id);
//
void Audio_Set_ADC_Source(Audio_ADC_ID_Type id, Audio_ADC_Source_Type adc_source);
//
void Audio_AEC_Enable(Audio_AEC_ID_Type id);
void Audio_AEC_Disable(Audio_AEC_ID_Type id);
void Audio_ADC_Enable(Audio_ADC_ID_Type id);
void Audio_ADC_Disable(Audio_ADC_ID_Type id);
void Audio_DAC_Enable(Audio_DAC_ID_Type id);
void Audio_DAC_Disable(Audio_DAC_ID_Type id);
//performance
void Audio_Set_HPF_Parameter(Audio_ADC_ID_Type id, uint8_t k1_enable, uint8_t k1,
                             uint8_t k2_enable, uint8_t k2);
//0x08
void Audio_Set_ADC_LFSR(Audio_LFSR_Type lfsrType);
BL_Sts_Type Audio_Get_ADC_LFSR(void);
void Audio_Set_ADC_Scaling_Value(Audio_ADC_ID_Type id, uint8_t scalingVal);
void Audio_Set_Fir_Mode(Audio_ADC_ID_Type id, uint8_t enable);
//0x10
void Audio_ADC_Mash_Bit_Swap(Audio_ADC_ID_Type id, uint8_t swap);
void Audio_ADC_PDM_Inv_Swap(Audio_ADC_ID_Type id, uint8_t swap);
void Audio_ADC_Set_PDM_Value(uint8_t pdm_l, uint8_t pdm_h);
//0x14
void Audio_Set_DAC_LFSR(Audio_LFSR_Type lfsrType);
void Audio_Set_DAC_Dither(uint8_t enable, uint8_t amp);
void Audio_Set_DAC_Scaling(uint8_t enable, uint8_t scaling);
void Audio_Set_DAC_Order(Audio_DAC_Order_Type order);
void Audio_Set_DAC_Dwa_Swap(uint8_t swap);
void Audio_Set_DAC_Dwa_Bypass(uint8_t bypass);
//0x18
void Audio_Set_AEC_Record_Vid(uint8_t enable, uint8_t div);
void Audio_Set_AEC_Atten_mode(Audio_AEC_ID_Type aec_id, Audio_AEC_Atten_Mode mode);
//0x1c PDM Source sel
void Audio_ADC_PDM_Channel_Sel(Audio_PDM_ID_Type id,
                               Audio_PDM_Source_Type pdmSel);
void Audio_ADC_PDM_Enable(Audio_PDM_ID_Type id);
void Audio_ADC_PDM_Disable(Audio_PDM_ID_Type id);
//mix about
void Audio_Set_Mixer_Mode(uint8_t enable, Audio_Mixer_ID_Type mixerId, Audio_Mixer_Mode mode,
                          Audio_ADC_ID_Type sidetoneChannel, Audio_Mixer_Volume_Type Volume);
//int about
void Auido_IntMask(Audio_INT_Type intType, BL_Mask_Type intMask);
void Auido_IntClear(Audio_INT_Type intType);
BL_Err_Type Audio_Int_Callback_Install(Audio_INT_Type intType, intCallback_Type *cbFun);
BL_Sts_Type Audio_GetIntStatus(Audio_INT_Type intType);
void Audio_RxFifoClear(void);
uint32_t Audio_GetRxFifoCount(void);
uint32_t Audio_ReadRxFifo(void);
void Audio_TxFifoClear(void);
uint32_t Audio_GetTxFifoCount(void);
void Audio_WriteTxFifo(uint32_t da);
//fifo about
void Audio_RxFifoConfig(Audio_FifoCfg_Type *cfg);
void Audio_TxFifoConfig(Audio_FifoCfg_Type *Cfg);
void Audio_RxFifoEnable(uint8_t ch);
void Audio_RxFifoDisable(uint8_t ch);
void Audio_TxFifoEnable(uint8_t ch);
void Audio_TxFifoDisable(uint8_t ch);
//PEQ about
BL_Err_Type Audio_PEQ_Config(uint8_t peq_index, uint8_t peqBypass, Audio_PEQ_QTFM_Type qtfm,
                             uint32_t *b_pra, uint32_t *a_pra);
//volume control
BL_Err_Type Audio_DAC_Set_Mute(BL_Fun_Type muteSyncAllDac, Audio_DAC_ID_Type dac_id,
                               Audio_Mute_Type mute);
BL_Err_Type Audio_ADC_Set_Mute(BL_Fun_Type muteSyncAllAdc, Audio_ADC_ID_Type adc_id, Audio_Mute_Type mute);
BL_Err_Type Audio_ADC_Software_Volume_Config(Audio_ADC_ID_Type adc_id, Audio_Volume_Cfg_Type *cfg);
BL_Err_Type Audio_DAC_Software_Volume_Config(Audio_DAC_ID_Type dac_id, Audio_Volume_Cfg_Type *cfg);
BL_Err_Type Audio_ADC_Set_Volume(BL_Fun_Type volumeSyncAllAdc, Audio_ADC_ID_Type adc_id, uint16_t volume);
BL_Err_Type Audio_DAC_Set_Volume(BL_Fun_Type volumeSyncAllDac, Audio_DAC_ID_Type dac_id, uint16_t volume);
BL_Err_Type Audio_ADC_Set_Volume_Block(BL_Fun_Type volumeSyncAllAdc, Audio_ADC_ID_Type adc_id, uint16_t volume,
                                       uint32_t blockTimeout);
BL_Err_Type Audio_DAC_Set_Volume_Block(BL_Fun_Type volumeSyncAllDac, Audio_DAC_ID_Type dac_id, uint16_t volume,
                                       uint32_t blockTimeout);
BL_Err_Type Audio_ADC_Set_Volume_Reg(BL_Fun_Type volumeSyncAllAdc, Audio_ADC_ID_Type adc_id, uint16_t volume);
BL_Err_Type Audio_DAC_Set_Volume_Reg(BL_Fun_Type volumeSyncAllDac, Audio_DAC_ID_Type dac_id, uint16_t volume);
void Audio_ADC_Reset_Volume_Update(Audio_ADC_ID_Type adc_id);
void Audio_ADC_Reset_Volume_Update(Audio_ADC_ID_Type dac_id);
void Audio_Reset_Volume_All_Update(uint8_t isAdcOrDac);
BL_Err_Type Audio_ADC_Hardware_Volume_Config(Audio_Volume_Cfg_Type *cfg);
uint16_t Audio_ADC_Get_Hardware_Volume(void);
uint16_t Audio_ADC_Get_Volume(Audio_ADC_ID_Type adc_id);
uint16_t Audio_DAC_Get_Volume(Audio_DAC_ID_Type dac_id);
BL_Sts_Type Audio_IS_ADC_Mute_Done(Audio_ADC_ID_Type adc_id);
BL_Sts_Type Audio_IS_ADC_Volume_Set_Busy(Audio_ADC_ID_Type adc_id);
BL_Sts_Type Audio_IS_DAC_Mute_Set_Done(Audio_DAC_ID_Type dac_id);
BL_Sts_Type Audio_IS_DAC_Volume_Set_Busy(Audio_DAC_ID_Type dac_id);
//agc about
void Audio_AGC_Init(uint8_t enable, Audio_AGC_Config_Type *cfg);
//drc about
void Audio_DRC_Init(uint8_t enable, Audio_DRC_Config_Type *cfg);
//vad about
void Audio_VAD_Init(Audio_VAD_Cfg_Type *cfg);
void Audio_VAD_Enable(void);
void Audio_VAD_Disable(void);
uint32_t Audio_VAD_Get_EK(void);
void Audio_DAC_Reset_Volume_Update(Audio_DAC_ID_Type dac_id);

/*power */
void Audio_Poweron(void);

/*analog gain */
void Audio_SetADCAnalogGain(Audio_ADC_ID_Type adc, uint8_t analogGain);
void Audio_SetDACAnalogGain(Audio_DAC_ID_Type dac, uint8_t analogGain);

void AUDIO_IRQHandler(void);

/*@} end of group AUDIO_Public_Functions */

/*@} end of group AUDIO */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_AUDIO_H__ */
