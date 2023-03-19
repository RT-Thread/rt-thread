#ifndef _BFLB_DBI_H
#define _BFLB_DBI_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup DBI
  * @{
  */

#if defined(BL616)
#define DBI_QSPI_SUPPORT        1
#define DBI_YUV_SUPPORT         1
#define DBI_WRITE_DATA_BYTE_MAX 256
#define DBI_READ_DATA_BYTE_MAX  8
#define SPI_FIFO_NUM_MAX        8
#elif defined(BL606P) || defined(BL808)
#define DBI_QSPI_SUPPORT        0
#define DBI_YUV_SUPPORT         0
#define DBI_WRITE_DATA_BYTE_MAX 4
#define DBI_READ_DATA_BYTE_MAX  4
#define SPI_FIFO_NUM_MAX        8
#else
#error "unknown device"
#endif

#define DBI_WRITE_PIXEL_CNT_MAX 0x00FFFFFF

/** @defgroup DBI_MODE dbi working mode definition
  * @{
  */
#define DBI_MODE_TYPE_B         0 /* mipi-dbi typeB 8-wire-data mode */
#define DBI_MODE_TYPE_C_4_WIRE  1 /* mipi-dbi typeC 4-wire mode */
#define DBI_MODE_TYPE_C_3_WIRE  2 /* mipi-dbi typeC 3-wire mode */
#if (DBI_QSPI_SUPPORT)
#define DBI_MODE_EX_QSPI 3 /* Not the mipi standard. Extra support for QSPI mode */
#endif
/**
  * @}
  */

/** @defgroup DBI_PIXEL_INPUT_FORMAT dbi fifo input pixel format, the FIFO are filled in 32-bits width definition
  * @{
  */
#define DBI_PIXEL_INPUT_FORMAT_NBGR_8888 0 /* 32-bit/pixel, memory byte: [0]->pixel[0][R], [1]->pixel[0][G], [2]->pixel[0][B], [3]->invalid, [4]->pixel[1][R], ... */
#define DBI_PIXEL_INPUT_FORMAT_NRGB_8888 1 /* 32-bit/pixel, memory byte: [0]->pixel[0][B], [1]->pixel[0][G], [2]->pixel[0][R], [3]->invalid, [4]->pixel[1][B], ... */
#define DBI_PIXEL_INPUT_FORMAT_BGRN_8888 2 /* 32-bit/pixel, memory byte: [0]->invalid, [1]->pixel[0][R], [2]->pixel[0][G], [3]->pixel[0][B], [4]->invalid, [5]->pixel[1][R], ... */
#define DBI_PIXEL_INPUT_FORMAT_RGBN_8888 3 /* 32-bit/pixel, memory byte: [0]->invalid, [1]->pixel[0][B], [2]->pixel[0][G], [3]->pixel[0][R], [4]->invalid, [5]->pixel[1][B], ... */
#define DBI_PIXEL_INPUT_FORMAT_RGB_888   4 /* 24-bit/pixel, memory byte: [0]->pixel[0][R], [1]->pixel[0][G], [2]->pixel[0][B], [3]->pixel[1][R], [4]->pixel[1][G], ... */
#define DBI_PIXEL_INPUT_FORMAT_BGR_888   5 /* 24-bit/pixel, memory byte: [0]->pixel[0][B], [1]->pixel[0][G], [2]->pixel[0][R], [3]->pixel[1][B], [4]->pixel[1][G], ... */
#define DBI_PIXEL_INPUT_FORMAT_BGR_565   6 /* 16-bit/pixel, */
#define DBI_PIXEL_INPUT_FORMAT_RGB_565   7 /* 16-bit/pixel, */
/**
  * @}
  */

/** @defgroup DBI_PIXEL_OUTPUT_FORMAT dbi output pixel format definition
  * @{
  */
#define DBI_PIXEL_OUTPUT_FORMAT_RGB_565  0 /* 16-bit/pixel */
#define DBI_PIXEL_OUTPUT_FORMAT_RGB_888  1 /* 24-bit/pixel, Compatible with RGB666 format */
/**
  * @}
  */

/** @defgroup DBI_CLOCK_MODE dbi clock phase and polarity definition
  * @{
  */
#define DBI_CLOCK_MODE_0                 0 /* CPOL=0 CHPHA=0 */
#define DBI_CLOCK_MODE_1                 1 /* CPOL=0 CHPHA=1 */
#define DBI_CLOCK_MODE_2                 2 /* CPOL=1 CHPHA=0 */
#define DBI_CLOCK_MODE_3                 3 /* CPOL=1 CHPHA=1 */
/**
  * @}
  */

/** @defgroup DBI_QSPI_WIRE_NUM dbi qspi wire num definition
  * @{
  */
#define DBI_QSPI_WIRE_NUM_1              0 /* 1-wire mode */
#define DBI_QSPI_WIRE_NUM_4              1 /* 4-wire mode */
/**
  * @}
  */

/** @defgroup SPI_INTSTS dbi interrupt status definition
  * @{
  */
#define DBI_INTSTS_TC                    (1 << 0)
#define SPI_INTSTS_TX_FIFO               (1 << 1)
#define SPI_INTSTS_FIFO_ERR              (1 << 2)
/**
  * @}
  */

/** @defgroup DBI_INTCLR dbi interrupt clear definition
  * @{
  */
#define DBI_INTCLR_TC                    (1 << 0)
/**
  * @}
  */

/** @defgroup DBI_CMD dbi feature control cmd definition
  * @{
  */
#define DBI_CMD_CLEAR_TX_FIFO            (0x01)
#define DBI_CMD_GET_TX_FIFO_CNT          (0x02)
#define DBI_CMD_MASK_CMD_PHASE           (0x03)
#define DBI_CMD_CS_CONTINUE              (0x04)
#define DBI_CMD_SET_DUMMY_CNT            (0x05)
#define DBI_CMD_GET_SIZE_OF_PIXEL_CNT    (0x06)
#define DBI_CMD_INPUT_PIXEL_FORMAT       (0x07)
#define DBI_CMD_OUTPUT_PIXEL_FORMAT      (0x08)
#if (DBI_QSPI_SUPPORT)
#define DBI_CMD_YUV_TO_RGB_ENABLE (0x10)
#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
 * @brief DBI configuration structure
 *
 * @param dbi_mode              DBI working mode, use @ref DBI_MODE
 * @param pixel_input_format    DBI input pixel_format, use @ref DBI_PIXEL_INPUT_FORMAT
 * @param pixel_output_format   DBI output pixel_format, use @ref DBI_PIXEL_OUTPUT_FORMAT
 * @param clk_mode              DBI clock phase and polarity, use @ref DBI_CLOCK_MODE
 * @param clk_freq_hz           DBI clock frequency
 * @param tx_fifo_threshold     DBI tx fifo threshold, should be less than 16
 * @param cmd_wire_mode         DBI qspi mode, number of wire in the command phase, use @ref DBI_QSPI_WIRE_NUM
 * @param addr_wire_mode        DBI qspi mode, number of wire in the address phase, use @ref DBI_QSPI_WIRE_NUM
 * @param data_wire_mode        DBI qspi mode, number of wire in the data phase, use @ref DBI_QSPI_WIRE_NUM
 */
struct bflb_dbi_config_s {
    uint8_t dbi_mode;
    uint8_t pixel_input_format;
    uint8_t pixel_output_format;
    uint8_t clk_mode;
    uint32_t clk_freq_hz;
    uint8_t tx_fifo_threshold;
#if (DBI_QSPI_SUPPORT)
    uint8_t cmd_wire_mode;
    uint8_t addr_wire_mode;
    uint8_t data_wire_mode;
#endif
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize dbi.
 *
 * @param [in] dev device handle
 * @param [in] config pointer to save dbi config
 */
void bflb_dbi_init(struct bflb_device_s *dev, const struct bflb_dbi_config_s *config);

/**
 * @brief Deinitialize dbi.
 *
 * @param [in] dev device handle
 */
void bflb_dbi_deinit(struct bflb_device_s *dev);

#if DBI_QSPI_SUPPORT
/**
 * @brief Set the address value and address length of the QSPI
 *
 * @param [in] dev device handle
 * @param [in] addr_byte_size address size(byte), range 1 ~ 4
 * @param [in] addr_val address value: [0:7]->addr[0], [8:15]->addr[1], [16:23]->addr[2], [24:31]->addr[3].
 */
void bflb_dbi_qspi_set_addr(struct bflb_device_s *dev, uint8_t addr_byte_size, uint32_t addr_val);

#endif

/**
 * @brief Send cmd with pixel data, send cmd -> send address(only QSPI mode) -> send parameter_data.
 *
 * @param [in] dev device handle
 * @param [in] cmd command
 * @param [in] data_len Parameter length (byte), The maximum is DBI_WRITE_DATA_BYTE_MAX
 * @param [in] data_buff Parameter buffer, Cannot be null
 * @return
 */
int bflb_dbi_send_cmd_data(struct bflb_device_s *dev, uint8_t cmd, uint8_t data_len, uint8_t *data_buff);

/**
 * @brief To read the data after sending the command, send cmd -> send address(only QSPI mode) -> read parameter_data.
 *
 * @param [in] dev device handle
 * @param [in] cmd command
 * @param [in] data_len Length of data to be read (byte), The maximum is DBI_READ_DATA_BYTE_MAX
 * @param [in] data_buff Buff of data to be read, discard data if null
 * @return
 */
int bflb_dbi_send_cmd_read_data(struct bflb_device_s *dev, uint8_t cmd, uint8_t data_len, uint8_t *data_buff);

/**
 * @brief Send cmd with pixel data, send cmd -> send address(only QSPI mode) -> send pixel_data,
 *
 * @param [in] dev device handle
 * @param [in] cmd command
 * @param [in] pixel_cnt Number of pixels,The maximum is DBI_WRITE_PIXEL_CNT_MAX
 * @param [in] pixel_buff Pixels buffer, NULL when using DMA, in which case data needs to be transferred by DMA later, and wait for the transfer to complete
 * @return
 */
int bflb_dbi_send_cmd_pixel(struct bflb_device_s *dev, uint8_t cmd, uint32_t pixel_cnt, void *pixel_buff);

/**
 * @brief Enable dbi tx dma.
 *
 * @param [in] dev device handle
 * @param [in] enable true means enable, otherwise disable.
 */
void bflb_dbi_link_txdma(struct bflb_device_s *dev, bool enable);

/**
 * @brief Enable or disable dbi rx fifo threhold interrupt.
 *
 * @param [in] dev device handle
 * @param [in] mask true means disable, false means enable
 */
void bflb_dbi_txint_mask(struct bflb_device_s *dev, bool mask);

/**
 * @brief Enable or disable dbi transfer completion interrupt.
 *
 * @param [in] dev device handle
 * @param [in] mask true means disable, false means enable
 */
void bflb_dbi_tcint_mask(struct bflb_device_s *dev, bool mask);

/**
 * @brief Enable or disable dbi error interrupt.
 *
 * @param [in] dev device handle
 * @param [in] mask true means disable, false means enable
 */
void bflb_dbi_errint_mask(struct bflb_device_s *dev, bool mask);

/**
 * @brief Get dbi interrupt status.
 *
 * @param [in] dev device handle
 * @return interrupt status, use @ref DBI_INTSTS
 */
uint32_t bflb_dbi_get_intstatus(struct bflb_device_s *dev);

/**
 * @brief Clear dbi interrupt status.
 *
 * @param [in] dev device handle
 * @param [in] int_clear clear value, use @ref SPI_INTCLR
 */
void bflb_dbi_int_clear(struct bflb_device_s *dev, uint32_t int_clear);

/**
 * @brief Control dbi feature.
 *
 * @param [in] dev device handle
 * @param [in] cmd feature command, use @ref DBI_CMD
 * @param [in] arg user data
 * @return A negated errno value on failure.
 */
int bflb_dbi_feature_control(struct bflb_device_s *dev, int cmd, size_t arg);

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
