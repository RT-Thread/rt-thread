#ifndef _BFLB_AUADC_H
#define _BFLB_AUADC_H

#include "bflb_core.h"

/**
 *  @defgroup AUADC_SAMPLING_RATE auadc sampling rate
 */
#define AUADC_SAMPLING_RATE_8K           0  /* audio mode */
#define AUADC_SAMPLING_RATE_16K          1  /* audio mode */
#define AUADC_SAMPLING_RATE_24K          2  /* audio mode, same as 22.02K, adjust the AUPLL clock */
#define AUADC_SAMPLING_RATE_32K          3  /* audio mode */
#define AUADC_SAMPLING_RATE_48K          4  /* audio mode, same as 44.1K, adjust the AUPLL clock */
#define AUADC_SAMPLING_RATE_MEASURE_128K 8  /* only used in ADC measurement mode */
#define AUADC_SAMPLING_RATE_MEASURE_256K 9  /* only used in ADC measurement mode */
#define AUADC_SAMPLING_RATE_MEASURE_512K 10 /* only used in ADC measurement mode */
/**
  * @}
  */

/**
 *  @defgroup AUADC_INPUT_MODE auadc input mode
 */
#define AUADC_INPUT_MODE_ADC             0 /* Analog ADC */
#define AUADC_INPUT_MODE_PDM_L           1 /* PDM left channel */
#define AUADC_INPUT_MODE_PDM_R           2 /* PDM right channel */
/**
  * @}
  */

/**
 *  @defgroup AUADC_DATA_FORMAT auadc data format
 */
#define AUADC_DATA_FORMAT_16BIT          3
#define AUADC_DATA_FORMAT_20BIT          2
#define AUADC_DATA_FORMAT_24BIT          1
#define AUADC_DATA_FORMAT_32BIT          0
/**
  * @}
  */

/**
 *  @brief AUADC_ADC_ANALOG_CH auadc adc input ch
 */
#define AUADC_ADC_ANALOG_CH_0            0
#define AUADC_ADC_ANALOG_CH_1            1
#define AUADC_ADC_ANALOG_CH_2            2
#define AUADC_ADC_ANALOG_CH_3            3
#define AUADC_ADC_ANALOG_CH_4            4
#define AUADC_ADC_ANALOG_CH_5            5
#define AUADC_ADC_ANALOG_CH_6            6
#define AUADC_ADC_ANALOG_CH_7            7
/**
  * @}
  */

/**
 *  @brief AUADC_ADC_MEASURE_RATE auadc adc Sampling rate in measurement mode, @ AUADC_SAMPLING_RATE_MEASURE_256K
 */

#define AUADC_ADC_MEASURE_RATE_SPS_2_5   0
#define AUADC_ADC_MEASURE_RATE_SPS_5     1
#define AUADC_ADC_MEASURE_RATE_SPS_10    2
#define AUADC_ADC_MEASURE_RATE_SPS_20    3
#define AUADC_ADC_MEASURE_RATE_SPS_25    4
#define AUADC_ADC_MEASURE_RATE_SPS_50    5
#define AUADC_ADC_MEASURE_RATE_SPS_100   6
#define AUADC_ADC_MEASURE_RATE_SPS_200   7
#define AUADC_ADC_MEASURE_RATE_SPS_400   8
#define AUADC_ADC_MEASURE_RATE_SPS_800   9
#define AUADC_ADC_MEASURE_RATE_SPS_1000  10
#define AUADC_ADC_MEASURE_RATE_SPS_2000  11
#define AUADC_ADC_MEASURE_RATE_SPS_4000  12

/**
  * @}
  */

/**
 *  @brief AUADC_ADC_MODE auadc adc mode
 */
#define AUADC_ADC_MODE_AUDIO             0
#define AUADC_ADC_MODE_MEASURE           1
/**
  * @}
  */

/**
 *  @brief AUADC_ADC_PGA_MODE auadc adc mode, Ac or DC, differential or single
 */
#define AUADC_ADC_PGA_MODE_AC_DIFFER     0
#define AUADC_ADC_PGA_MODE_AC_SINGLE     1
#define AUADC_ADC_PGA_MODE_DC_DIFFER     2
#define AUADC_ADC_PGA_MODE_DC_SINGLE     3
/**
  * @}
  */

/** @defgroup AUADC_INTMASK auadc interrupt status definition
  * @{
  */
#define AUADC_INTMASK_FIFO_OVER          (1 << 1)
#define AUADC_INTMASK_FIFO_UNDER         (1 << 2)
#define AUADC_INTMASK_FIFO_AVAILABLE     (1 << 3)
/**
  * @}
  */

/** @defgroup AUADC_INTSTS auadc interrupt status definition
  * @{
  */
#define AUADC_INTSTS_FIFO_OVER           (1 << 1)
#define AUADC_INTSTS_FIFO_UNDER          (1 << 2)
#define AUADC_INTSTS_FIFO_AVAILABLE      (1 << 4)
/**
  * @}
  */

/** @defgroup AUADC_CMD auadc feature control cmd definition
  * @{
  */
#define AUADC_CMD_RECORD_START           (0x01)
#define AUADC_CMD_RECORD_STOP            (0x02)
#define AUADC_CMD_SET_VOLUME_VAL         (0x03)
#define AUADC_CMD_SET_PGA_GAIN_VAL       (0x04)
#define AUADC_CMD_CLEAR_RX_FIFO          (0x05)
#define AUADC_CMD_GET_RX_FIFO_CNT        (0x06)
/**
  * @}
  */

/**
 * @brief auadc initialization configuration structure
 *
 * @param sampling_rate         auadc sampling rate, use @ref AUADC_SAMPLING_RATE
 * @param input_mode            auadc mode, use @ref AUADC_INPUT_MODE
 * @param data_format           auadc fifo data format, use @ref AUADC_DATA_FORMAT
 * @param fifo_threshold        auadc tx fifo threshold, 0 ~ 7
 */
struct bflb_auadc_init_config_s {
    uint8_t sampling_rate;
    uint8_t input_mode;
    uint8_t data_format;
    uint8_t fifo_threshold;
};

/**
 * @brief auadc adc analog initialization configuration structure
 *
 * @param analog_adc_en         auadc sampling rate, use true or false
 * @param adc_mode              auadc adc work pattern, use @ref AUADC_ADC_MODE
 * @param adc_pga_mode          auadc adc PGA mode, use @ref AUADC_ADC_PGA_MODE
 * @param adc_pga_posi_ch       auadc adc positive channel selection, use @ref AUADC_ADC_ANALOG_CH
 * @param adc_pga_nega_ch       auadc adc negative channel selection, This channel is valid only when adc_pga_mode is differential, use @ref AUADC_ADC_ANALOG_CH
 * @param adc_pga_gain          auadc adc PGA Gain control, 6dB ~ 42dB, step by 3db
 * @param adc_measure_rate      auadc adc sampling rate in measurement mode @ AUADC_SAMPLING_RATE_MEASURE_256K, use @ref AUADC_ADC_MEASURE_RATE
 */
struct bflb_auadc_adc_init_config_s {
    uint8_t auadc_analog_en;
    uint8_t adc_mode;
    uint8_t adc_pga_mode;
    uint8_t adc_pga_posi_ch;
    uint8_t adc_pga_nega_ch;
    uint8_t adc_pga_gain;
    uint8_t adc_measure_rate;
};

int bflb_auadc_init(struct bflb_device_s *dev, const struct bflb_auadc_init_config_s *config);

int bflb_auadc_adc_init(struct bflb_device_s *dev, const struct bflb_auadc_adc_init_config_s *config);

int bflb_auadc_link_rxdma(struct bflb_device_s *dev, bool enable);

int bflb_auadc_int_mask(struct bflb_device_s *dev, uint32_t int_sts);

int bflb_auadc_int_unmask(struct bflb_device_s *dev, uint32_t int_sts);

int bflb_auadc_get_intstatus(struct bflb_device_s *dev);

int bflb_auadc_feature_control(struct bflb_device_s *dev, int cmd, size_t arg);

#endif