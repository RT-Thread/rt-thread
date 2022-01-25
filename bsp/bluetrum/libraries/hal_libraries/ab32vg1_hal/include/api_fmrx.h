#ifndef FMRX_H__
#define FMRX_H__

/**
 * @brief Synchronize between FMRX and DAC
 *
 * @param buf_size Size of audio buffer.
 */
void fmrx_dac_sync(uint32_t buf_size);

/**
 * @brief FMRX power on.
 *
 * @param val Make it zero now.
 */
void fmrx_power_on(uint32_t val);

/**
 * @brief FMRX power off.
 *
 */
void fmrx_power_off(void);

/**
 * @brief FMRX digital start.
 *
 */
void fmrx_digital_start(void);

/**
 * @brief FMRX digital stop.
 *
 */
void fmrx_digital_stop(void);

/**
 * @brief FMRX dma to aubuf enable.
 *
 * @param enable RT_TRUE or RT_FALSE.
 */
void fmrx_dma_to_aubuf(uint8_t enable);

#endif
