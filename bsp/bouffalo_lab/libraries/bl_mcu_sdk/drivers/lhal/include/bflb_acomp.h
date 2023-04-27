#ifndef _BFLB_ACOMP_H
#define _BFLB_ACOMP_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup ACOMP
  * @{
  */

/** @defgroup Analog compare id type definition
 * @{
 */
#define AON_ACOMP0_ID   0
#define AON_ACOMP1_ID   1


/** @defgroup Analog compare scaling factor type definition
 * @{
 */
#define AON_ACOMP_SCALING_FACTOR_0P25           0x00    /*!< Analog compare level scaling factor 0.25 */
#define AON_ACOMP_SCALING_FACTOR_0P5            0x10    /*!< Analog compare level scaling factor 0.5 */
#define AON_ACOMP_SCALING_FACTOR_0P75           0x20    /*!< Analog compare level scaling factor 0.75 */
#define AON_ACOMP_SCALING_FACTOR_1              0x30    /*!< Analog compare level scaling factor 1 */

/**
 *  @brief Analog compare channel type definition
 */
#define AON_ACOMP_CHAN_ADC0                     0   /*!< Analog compare channel,ADC input channel 0 */
#define AON_ACOMP_CHAN_ADC1                     1   /*!< Analog compare channel,ADC input channel 1 */
#define AON_ACOMP_CHAN_ADC2                     2   /*!< Analog compare channel,ADC input channel 2 */
#define AON_ACOMP_CHAN_ADC3                     3   /*!< Analog compare channel,ADC input channel 3 */
#define AON_ACOMP_CHAN_ADC4                     4   /*!< Analog compare channel,ADC input channel 4 */
#define AON_ACOMP_CHAN_ADC5                     5   /*!< Analog compare channel,ADC input channel 5 */
#define AON_ACOMP_CHAN_ADC6                     6   /*!< Analog compare channel,ADC input channel 6 */
#define AON_ACOMP_CHAN_ADC7                     7   /*!< Analog compare channel,ADC input channel 7 */
#define AON_ACOMP_CHAN_DACA                     8   /*!< Analog compare channel,DAC output channel A */
#define AON_ACOMP_CHAN_DACB                     9   /*!< Analog compare channel,DAC output channel B */
#define AON_ACOMP_CHAN_VREF_1P25V               10  /*!< Analog compare channel,1.25V ref voltage */
#define AON_ACOMP_CHAN_VIO_X_SCALING_FACTOR_1   11  /*!< Analog compare channel,first,VIO * scaling factor */
#define AON_ACOMP_CHAN_VIO_X_SCALING_FACTOR_2   12  /*!< Analog compare channel,second,VIO * scaling factor */
#define AON_ACOMP_CHAN_VIO_X_SCALING_FACTOR_3   13  /*!< Analog compare channel,third,VIO * scaling factor */
#define AON_ACOMP_CHAN_VIO_X_SCALING_FACTOR_4   14  /*!< Analog compare channel,forth,VIO * scaling factor */
#define AON_ACOMP_CHAN_VSS                      15  /*!< Analog compare channel,vss */

/**
 *  @brief Analog compare bias current control type definition
 */
#define AON_ACOMP_BIAS_POWER_MODE1              0   /*!< Analog compare power mode 1,slow response mode */
#define AON_ACOMP_BIAS_POWER_MODE2              1   /*!< Analog compare power mode 2,medium response mode */
#define AON_ACOMP_BIAS_POWER_MODE3              2   /*!< Analog compare power mode 3,fast response mode */
#define AON_ACOMP_BIAS_POWER_NONE               3   /*!< Analog compare power mode none */

/**
 *  @brief Analog compare hysteresis voltage type definition
 */
#define AON_ACOMP_HYSTERESIS_VOLT_NONE          0   /*!< Analog compare hysteresis voltage none */
#define AON_ACOMP_HYSTERESIS_VOLT_10MV          1   /*!< Analog compare hysteresis voltage 10mv */
#define AON_ACOMP_HYSTERESIS_VOLT_20MV          2   /*!< Analog compare hysteresis voltage 20mv */
#define AON_ACOMP_HYSTERESIS_VOLT_30MV          3   /*!< Analog compare hysteresis voltage 30mv */
#define AON_ACOMP_HYSTERESIS_VOLT_40MV          4   /*!< Analog compare hysteresis voltage 40mv */
#define AON_ACOMP_HYSTERESIS_VOLT_50MV          5   /*!< Analog compare hysteresis voltage 50mv */
#define AON_ACOMP_HYSTERESIS_VOLT_60MV          6   /*!< Analog compare hysteresis voltage 60mv */
#define AON_ACOMP_HYSTERESIS_VOLT_70MV          7   /*!< Analog compare hysteresis voltage 70mv */


/**
 * @brief ACOMP configuration structure
 *
 * @param mux_en                    ACOMP mux enable
 * @param pos_chan_sel              ACOMP positive channel select
 * @param neg_chan_sel              ACOMP negtive channel select
 * @param vio_sel                   ACOMP VIO voltage select, (vioSel/66)*avdd33
 * @param scaling_factor            ACOMP scaling factor select factor
 * @param bias_prog                 ACOMP bias current control
 * @param hysteresis_pos_volt       ACOMP hysteresis voltage for positive
 * @param hysteresis_neg_volt       ACOMP hysteresis voltage for negtive
 */
struct bflb_acomp_config_s {
    uint8_t mux_en;
    uint8_t pos_chan_sel;
    uint8_t neg_chan_sel;
    uint8_t vio_sel;
    uint8_t scaling_factor;
    uint8_t bias_prog;
    uint8_t hysteresis_pos_volt;
    uint8_t hysteresis_neg_volt;
};


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize acomp.
 *
 * @param [in] acomp_id acomp index
 * @param [in] config pointer to save acomp configuration
 */
void bflb_acomp_init(uint8_t acomp_id, const struct bflb_acomp_config_s *config);

/**
 * @brief Enable acomp.
 *
 * @param [in] acomp_id acomp index
 */
void bflb_acomp_enable(uint8_t acomp_id);

/**
 * @brief Disable acomp.
 *
 * @param [in] acomp_id acomp index
 */
void bflb_acomp_disable(uint8_t acomp_id);

/**
 * @brief Get acomp result.
 *
 * @param [in] acomp_id acomp index
 * @return acomp result
 */
uint32_t bflb_acomp_get_result(uint8_t acomp_id);

/**
 * @brief gpio change adc_chan_id.
 *
 * @param [in] pin gpio index
 * @param [out] channel adc channel index
 * @return Zero on success; a negated errno value on failure
 */
uint32_t bflb_acomp_gpio_2_chanid(uint32_t pin, uint32_t* channel);

/**
 * @brief adc_chan_id change gpio index.
 *
 * @param [in] channel adc channel index
 * @param [out] pin gpio index
 * @return Zero on success; a negated errno value on failure
 */
uint32_t bflb_acomp_chanid_2_gpio(uint32_t channel, uint32_t* pin);


#if 0
/**
 * @brief Get acomp postive input.
 *
 * @param [in] acomp_id acomp index
 * @return acomp postive input
 */
uint32_t bflb_acomp_get_postive_input(uint8_t acomp_id);
#endif


#ifdef __cplusplus
}
#endif

#endif
