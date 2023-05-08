#ifndef _BFLB_MJPEG_H
#define _BFLB_MJPEG_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup MJPEG
  * @{
  */

/** @defgroup MJPEG_FORMAT mjpeg format definition
  * @{
  */
#define MJPEG_FORMAT_YUV422_YUYV   0
#define MJPEG_FORMAT_YUV422_YVYU   1
#define MJPEG_FORMAT_YUV422_UYVY   2
#define MJPEG_FORMAT_YUV422_VYUY   3
#define MJPEG_FORMAT_YUV422SP_NV16 4
#define MJPEG_FORMAT_YUV422SP_NV61 5
#define MJPEG_FORMAT_YUV420SP_NV12 6
#define MJPEG_FORMAT_YUV420SP_NV21 7
#define MJPEG_FORMAT_GRAY          8
/**
  * @}
  */

/** @defgroup MJPEG_INTSTS mjpeg interrupt status definition
  * @{
  */
#define MJPEG_INTSTS_ONE_FRAME     (1 << 4)
/**
  * @}
  */

/** @defgroup MJPEG_INTCLR mjpeg interrupt clear definition
  * @{
  */
#define MJPEG_INTCLR_ONE_FRAME     (1 << 8)
/**
  * @}
  */

/** @defgroup MJPEG_CMD mjpeg feature control cmd definition
  * @{
  */
#define MJPEG_CMD_SET_INPUTADDR0   0x00
#define MJPEG_CMD_SET_INPUTADDR1   0x01
/**
  * @}
  */

#define MJPEG_MAX_FRAME_COUNT      4

/**
 * @brief MJPEG configuration structure
 *
 * @param format            MJPEG format, use @ref MJPEG_FORMAT
 * @param resolution_x      MJPEG width, must be a multiple of 8 or a multiple of 16
 * @param resolution_y      MJPEG higth, must be a multiple of 8 or a multiple of 16
 * @param input_bufaddr0    MJPEG input buffer address 0 for yy , must be align 16
 * @param input_bufaddr1    MJPEG input buffer address 0 for yy , must be align 16
 * @param output_bufaddr    MJPEG output buffer address , must be align 16
 * @param output_bufsize    MJPEG output buffer size, must be larger than resolution_x*resolution_y*2*MJPEG_MAX_FRAME_COUNT
 */
struct bflb_mjpeg_config_s {
    uint8_t format;
    uint8_t quality;
    uint16_t rows;
    uint16_t resolution_x;
    uint16_t resolution_y;
    uint32_t input_bufaddr0;
    uint32_t input_bufaddr1;
    uint32_t output_bufaddr;
    uint32_t output_bufsize;
    uint16_t *input_yy_table;
    uint16_t *input_uv_table;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize mjpeg.
 *
 * @param [in] dev device handle
 * @param [in] config pointer to save mjpeg config
 */
void bflb_mjpeg_init(struct bflb_device_s *dev, const struct bflb_mjpeg_config_s *config);

/**
 * @brief Start mjpeg compression with camera.
 *
 * @param [in] dev device handle
 */
void bflb_mjpeg_start(struct bflb_device_s *dev);

/**
 * @brief Stop mjpeg compression with camera.
 *
 * @param [in] dev device handle
 */
void bflb_mjpeg_stop(struct bflb_device_s *dev);

/**
 * @brief Start mjpeg compression without camera.
 *
 * @param [in] dev device handle
 * @param [in] frame_count frame count to compress
 */
void bflb_mjpeg_sw_run(struct bflb_device_s *dev, uint8_t frame_count);

/**
 * @brief Start mjpeg kick mode compression without camera.
 *
 * @param [in] dev device handle
 * @param [in] kick_count kick block horizontal count to compress
 */
void bflb_mjpeg_kick_run(struct bflb_device_s *dev, uint16_t kick_count);

/**
 * @brief Stop mjpeg kick mode compression without camera.
 *
 * @param [in] dev device handle
 */
void bflb_mjpeg_kick_stop(struct bflb_device_s *dev);

/**
 * @brief kick one times compression without camera.
 *
 * @param [in] dev device handle
 */
void bflb_mjpeg_kick(struct bflb_device_s *dev);
/**
 * @brief Enable or disable mjpeg one frame compression completion interrupt.
 *
 * @param [in] dev device handle
 * @param [in] mask true means disable, false means enable
 */
void bflb_mjpeg_tcint_mask(struct bflb_device_s *dev, bool mask);

/**
 * @brief Enable or disable mjpeg error interrupt.
 *
 * @param [in] dev device handle
 * @param [in] mask true means disable, false means enable
 */
void bflb_mjpeg_errint_mask(struct bflb_device_s *dev, bool mask);

/**
 * @brief Get mjpeg interrupt status.
 *
 * @param [in] dev device handle
 * @return interrupt status
 */
uint32_t bflb_mjpeg_get_intstatus(struct bflb_device_s *dev);

/**
 * @brief Clear mjpeg interrupt status.
 *
 * @param [in] dev device handle
 * @param [in] int_clear clear value
 */
void bflb_mjpeg_int_clear(struct bflb_device_s *dev, uint32_t int_clear);

/**
 * @brief Get number of frame count that has compressed.
 *
 * @param [in] dev device handle
 * @return compressed frame count
 */
uint8_t bflb_mjpeg_get_frame_count(struct bflb_device_s *dev);

/**
 * @brief Drop one frame that has compressed.
 *
 * @param [in] dev device handle
 */
void bflb_mjpeg_pop_one_frame(struct bflb_device_s *dev);

/**
 * @brief Get one frame information.
 *
 * @param [in] dev device handle
 * @param [in] pic pointer to save frame address.
 * @return frame length
 */
uint32_t bflb_mjpeg_get_frame_info(struct bflb_device_s *dev, uint8_t **pic);

/**
 * @brief Calculate jpeg quantize table.
 *
 * @param [in] quality image quality
 * @param [in] input_table pointer to save input table
 * @param [in] output_table pointer to save output table
 */
void bflb_mjpeg_calculate_quantize_table(uint8_t quality, uint16_t *input_table, uint16_t *output_table);

/**
 * @brief Fill quantize table into mjpeg register.
 *
 * @param [in] dev device handle
 * @param [in] input_yy yy quantize table
 * @param [in] input_uv uv quantize table
 */
void bflb_mjpeg_fill_quantize_table(struct bflb_device_s *dev, uint16_t *input_yy, uint16_t *input_uv);

/**
 * @brief Fill jpeg header into mjpeg register and enable hardware auto adding jpeg tail.
 *
 * @param [in] dev device handle
 * @param [in] header pointer to jpeg header
 * @param [in] header_len jpeg header length
 */
void bflb_mjpeg_fill_jpeg_header_tail(struct bflb_device_s *dev, uint8_t *header, uint32_t header_len);

/**
 * @brief Set mjpeg input when uses camera with yuv402sp.
 *
 * @param [in] dev device handle
 * @param [in] yy camera id for yy
 * @param [in] uv camera id for uv
 */
void bflb_mjpeg_set_yuv420sp_cam_input(struct bflb_device_s *dev, uint8_t yy, uint8_t uv);

/**
 * @brief Control mjpeg feature.
 *
 * @param [in] dev device handle
 * @param [in] cmd feature command
 * @param [in] arg user data
 * @return A negated errno value on failure.
 */
int bflb_mjpeg_feature_control(struct bflb_device_s *dev, int cmd, size_t arg);

/**
 * @brief Control mjpeg feature.
 *
 * @param [in] dev device handle
 * @param [in] input_buf0 input buffer 0
 * @param [in] input_buf1 input buffer 1
 * @param [in] output_buff output buffer
 * @param [in] output_buff_size size of output buffer
 * @return A negated errno value on failure.
 */
void bflb_mjpeg_update_input_output_buff(struct bflb_device_s *dev, void *input_buf0, void *input_buf1, void *output_buff, size_t output_buff_size);

#ifdef __cplusplus
}
#endif

/**
  * @}
  */

/**
  * @}
  */

#endif