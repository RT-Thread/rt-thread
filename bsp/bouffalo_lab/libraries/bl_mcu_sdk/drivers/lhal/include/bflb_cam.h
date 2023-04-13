#ifndef _BFLB_CAM_H
#define _BFLB_CAM_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup CAM
  * @{
  */

/** @defgroup CAM_INPUT_FORMAT CAMERA input format definition
  * @{
  */
#define CAM_INPUT_FORMAT_YUV422_YUYV 0
#define CAM_INPUT_FORMAT_YUV422_YVYU 1
#define CAM_INPUT_FORMAT_YUV422_UYVY 2
#define CAM_INPUT_FORMAT_YUV422_VYUY 3
#define CAM_INPUT_FORMAT_GRAY        4
#define CAM_INPUT_FORMAT_RGB565      5
#define CAM_INPUT_FORMAT_BGR565      6
#define CAM_INPUT_FORMAT_RGB888      7
#define CAM_INPUT_FORMAT_BGR888      8
/**
  * @}
  */

/** @defgroup CAM_OUTPUT_FORMAT CAMERA output format definition
  * @{
  */
#define CAM_OUTPUT_FORMAT_AUTO             0
#define CAM_OUTPUT_FORMAT_YUV422           1
#define CAM_OUTPUT_FORMAT_GRAY             2
#define CAM_OUTPUT_FORMAT_YUV422_UV        3
#define CAM_OUTPUT_FORMAT_YUV420_UV        4
#define CAM_OUTPUT_FORMAT_RGB565_OR_BGR565 5
#define CAM_OUTPUT_FORMAT_RGB888_OR_BGR888 6
#if !defined(BL702)
#define CAM_OUTPUT_FORMAT_RGB888_TO_RGB565   7
#define CAM_OUTPUT_FORMAT_RGB888_TO_BGR565   8
#define CAM_OUTPUT_FORMAT_RGB888_TO_RGBA8888 9
#endif

/**
  * @}
  */

/** @defgroup CAM_INTSTS CAMERA interrupt status definition
  * @{
  */
#if defined(BL702)
#define CAM_INTSTS_NORMAL           (1 << 0)
#define CAM_INTSTS_MEMORY_OVERWRITE (1 << 2)
#define CAM_INTSTS_FRAME_OVERWRITE  (1 << 4)
#define CAM_INTSTS_FIFO_OVERWRITE   (1 << 6)
#define CAM_INTSTS_HSYNC_MISMATCH   (1 << 8)
#define CAM_INTSTS_VSYNC_MISMATCH   (1 << 9)
#else
#define CAM_INTSTS_NORMAL           (1 << 12)
#define CAM_INTSTS_MEMORY_OVERWRITE (1 << 13)
#define CAM_INTSTS_FRAME_OVERWRITE  (1 << 14)
#define CAM_INTSTS_FIFO_OVERWRITE   (1 << 15)
#define CAM_INTSTS_HSYNC_MISMATCH   (1 << 21)
#define CAM_INTSTS_VSYNC_MISMATCH   (1 << 22)
#endif
/**
  * @}
  */

/** @defgroup CAM_INTMASK CAMERA interrupt mask definition
  * @{
  */
#if defined(BL702)
#define CAM_INTMASK_NORMAL           (1 << 0)
#define CAM_INTMASK_MEMORY_OVERWRITE (1 << 2)
#define CAM_INTMASK_FRAME_OVERWRITE  (1 << 3)
#define CAM_INTMASK_FIFO_OVERWRITE   (1 << 4)
#define CAM_INTMASK_HSYNC_MISMATCH   (1 << 5)
#define CAM_INTMASK_VSYNC_MISMATCH   (1 << 6)
#else
#define CAM_INTMASK_NORMAL           (1 << 8)
#define CAM_INTMASK_MEMORY_OVERWRITE (1 << 9)
#define CAM_INTMASK_FRAME_OVERWRITE  (1 << 10)
#define CAM_INTMASK_FIFO_OVERWRITE   (1 << 11)
#define CAM_INTMASK_HSYNC_MISMATCH   (1 << 6)
#define CAM_INTMASK_VSYNC_MISMATCH   (1 << 7)
#endif
/**
  * @}
  */

/** @defgroup CAM_INTCLR CAMERA interrupt clear definition
  * @{
  */
#define CAM_INTCLR_NORMAL           (1 << 4)
#define CAM_INTCLR_MEMORY_OVERWRITE (1 << 5)
#define CAM_INTCLR_FRAME_OVERWRITE  (1 << 6)
#define CAM_INTCLR_FIFO_OVERWRITE   (1 << 7)
#define CAM_INTCLR_HSYNC_MISMATCH   (1 << 8)
#define CAM_INTCLR_VSYNC_MISMATCH   (1 << 9)
/**
  * @}
  */

/** @defgroup CAM_POLARITY CAMERA hsync/vsync polarity active level definition
  * @{
  */
#define CAM_POLARITY_ACTIVE_LOW  0
#define CAM_POLARITY_ACTIVE_HIGH 1
/**
  * @}
  */

/** @defgroup CAM_INPUT_SOURCE CAMERA input source definition
  * @{
  */
#define CAM_INPUT_SOURCE_DVP 0
#if defined(BL808)
#define CAM_INPUT_SOURCE_CSI 1
#endif
/**
  * @}
  */

/** @defgroup CAM_BURST CAMERA burst length definition
  * @{
  */
#define CAM_BURST_INCR1  0
#define CAM_BURST_INCR4  1
#define CAM_BURST_INCR8  2
#define CAM_BURST_INCR16 3
#if !defined(BL702)
#define CAM_BURST_INCR32 5
#define CAM_BURST_INCR64 6
#endif
/**
  * @}
  */

/** @defgroup CAM_CMD CAMERA feature control cmd definition
  * @{
  */
#define CAM_CMD_SET_VSYNC_POLARITY 1
#define CAM_CMD_SET_HSYNC_POLARITY 2
#define CAM_CMD_SET_BURST          3
#if !defined(BL702)
#define CAM_CMD_SET_RGBA8888_ALPHA 4
#define CAM_CMD_GET_FRAME_ID       5
#endif
#define CAM_CMD_WRAP_MODE                6
#define CAM_CMD_COUNT_TRIGGER_NORMAL_INT 7
#if !defined(BL702)
#define CAM_CMD_FRAME_ID_RESET         8
#define CAM_CMD_INVERSE_VSYNC_POLARITY 9
#define CAM_CMD_INVERSE_HSYNC_POLARITY 10
#endif

/**
  * @}
  */

/**
 * @brief CAM configuration structure
 *
 * @param input_format   CAM input format, use @ref CAM_INPUT_FORMAT
 * @param resolution_x   CAM resolution x
 * @param resolution_y   CAM resolution y
 * @param h_blank        CAM Hsync blank
 * @param pixel_clock    CAM pixel clock
 * @param with_mjpeg     CAM with mjpeg or not
 * @param input_source   CAM input source, use @ref CAM_INPUT_SOURCE
 * @param output_format  CAM output format, use @ref CAM_OUTPUT_FORMAT
 * @param output_bufaddr CAM output buffer address , must be align 16
 * @param output_bufsize CAM output buffer size, should not be less than one frame size
 */
struct bflb_cam_config_s {
    uint8_t input_format;
    uint16_t resolution_x;
    uint16_t resolution_y;
    uint16_t h_blank;
    uint32_t pixel_clock;
    bool with_mjpeg;
    uint8_t input_source;
    uint8_t output_format;
    uint32_t output_bufaddr;
    uint32_t output_bufsize;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize cam.
 *
 * @param [in] dev device handle
 * @param [in] config pointer to cam configure structure
 */
void bflb_cam_init(struct bflb_device_s *dev, const struct bflb_cam_config_s *config);

/**
 * @brief Enable cam.
 *
 * @param [in] dev device handle
 */
void bflb_cam_start(struct bflb_device_s *dev);

/**
 * @brief Disable cam.
 *
 * @param [in] dev device handle
 */
void bflb_cam_stop(struct bflb_device_s *dev);

/**
 * @brief Mask or unmask cam interrupt.
 *
 * @param [in] dev device handle
 * @param [in] int_type cam interrupt mask type, use @ref CAM_INTMASK
 * @param [in] mask mask or unmask
 */
void bflb_cam_int_mask(struct bflb_device_s *dev, uint32_t int_type, bool mask);

/**
 * @brief Clear cam interrupt.
 *
 * @param [in] dev device handle
 * @param [in] int_type int_type cam interrupt clear type, use @ref CAM_INTCLR
 */
void bflb_cam_int_clear(struct bflb_device_s *dev, uint32_t int_type);

/**
 * @brief Crop vsync.
 *
 * @param [in] dev device handle
 * @param [in] start_line start line of window
 * @param [in] end_line end line of window, not include
 */
void bflb_cam_crop_vsync(struct bflb_device_s *dev, uint16_t start_line, uint16_t end_line);

/**
 * @brief Crop hsync.
 *
 * @param [in] dev device handle
 * @param [in] start_pixel start pixel of each line
 * @param [in] end_pixel end pixel of each line, not include
 */
void bflb_cam_crop_hsync(struct bflb_device_s *dev, uint16_t start_pixel, uint16_t end_pixel);

/**
 * @brief Pop one frame.
 *
 * @param [in] dev device handle
 */
void bflb_cam_pop_one_frame(struct bflb_device_s *dev);

#if !defined(BL702)
/**
 * @brief Swap input order of y and uv.
 *
 * @param [in] dev device handle
 * @param [in] enable enable or disable
 */
void bflb_cam_swap_input_yu_order(struct bflb_device_s *dev, bool enable);

/**
 * @brief Set frame filter, if frame_count = 3, frame_valid = 101b, second frame will be dropped every 3 frames.
 *
 * @param [in] dev device handle
 * @param [in] frame_count frame filter period
 * @param [in] frame_valid frame valid
 */
void bflb_cam_filter_frame_period(struct bflb_device_s *dev, uint8_t frame_count, uint32_t frame_valid);
#endif

/**
 * @brief Get frame count.
 *
 * @param [in] dev device handle
 * @return Frame count
 */
uint8_t bflb_cam_get_frame_count(struct bflb_device_s *dev);

/**
 * @brief Get frame information.
 *
 * @param [in] dev device handle
 * @param [out] pic pointer to frame start address
 * @return Size of frame
 */
uint32_t bflb_cam_get_frame_info(struct bflb_device_s *dev, uint8_t **pic);

/**
 * @brief Get interrupt status.
 *
 * @param [in] dev device handle
 * @return Interrupt status
 */
uint32_t bflb_cam_get_intstatus(struct bflb_device_s *dev);

/**
 * @brief Control cam feature.
 *
 * @param [in] dev device handle
 * @param [in] cmd feature command
 * @param [in] arg user data
 * @return A negated errno value on failure
 */
int bflb_cam_feature_control(struct bflb_device_s *dev, int cmd, size_t arg);

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
