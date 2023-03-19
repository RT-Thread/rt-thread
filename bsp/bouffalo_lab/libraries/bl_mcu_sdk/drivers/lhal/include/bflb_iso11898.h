#ifndef _BFLB_ISO11898_H
#define _BFLB_ISO11898_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup ISO11898
  * @{
  */

#define ISO11898_TIMEOUT (320 * 1000 * 1000)

#define ISO11898_MODE_NORMAL          0 /*!< normal mode */
#define ISO11898_MODE_LOOPBACK        1 /*!< loopback mode */
#define ISO11898_MODE_SILENT          2 /*!< silent mode */
#define ISO11898_MODE_SILENT_LOOPBACK 3 /*!< loopback combined with silent mode */

#define ISO11898_SAMPLE_SINGLE 0 /*!< the bus is sampled three times, recommended for low/medium speed buses */
#define ISO11898_SAMPLE_TRIPLE 1 /*!< the bus is sampled once, recommended for high speed buses */

#define ISO11898_SJW_1TQ 0 /*!< 1 time quantum */
#define ISO11898_SJW_2TQ 1 /*!< 2 time quantum */
#define ISO11898_SJW_3TQ 2 /*!< 3 time quantum */
#define ISO11898_SJW_4TQ 3 /*!< 4 time quantum */

#define ISO11898_BS1_1TQ  0  /*!< 1 time quantum */
#define ISO11898_BS1_2TQ  1  /*!< 2 time quantum */
#define ISO11898_BS1_3TQ  2  /*!< 3 time quantum */
#define ISO11898_BS1_4TQ  3  /*!< 4 time quantum */
#define ISO11898_BS1_5TQ  4  /*!< 5 time quantum */
#define ISO11898_BS1_6TQ  5  /*!< 6 time quantum */
#define ISO11898_BS1_7TQ  6  /*!< 7 time quantum */
#define ISO11898_BS1_8TQ  7  /*!< 8 time quantum */
#define ISO11898_BS1_9TQ  8  /*!< 9 time quantum */
#define ISO11898_BS1_10TQ 9  /*!< 10 time quantum */
#define ISO11898_BS1_11TQ 10 /*!< 11 time quantum */
#define ISO11898_BS1_12TQ 11 /*!< 12 time quantum */
#define ISO11898_BS1_13TQ 12 /*!< 13 time quantum */
#define ISO11898_BS1_14TQ 13 /*!< 14 time quantum */
#define ISO11898_BS1_15TQ 14 /*!< 15 time quantum */
#define ISO11898_BS1_16TQ 15 /*!< 16 time quantum */

#define ISO11898_BS2_1TQ 0 /*!< 1 time quantum */
#define ISO11898_BS2_2TQ 1 /*!< 2 time quantum */
#define ISO11898_BS2_3TQ 2 /*!< 3 time quantum */
#define ISO11898_BS2_4TQ 3 /*!< 4 time quantum */
#define ISO11898_BS2_5TQ 4 /*!< 5 time quantum */
#define ISO11898_BS2_6TQ 5 /*!< 6 time quantum */
#define ISO11898_BS2_7TQ 6 /*!< 7 time quantum */
#define ISO11898_BS2_8TQ 7 /*!< 8 time quantum */

#define ISO11898_ID_STANDARD 0 /*!< standard ID */
#define ISO11898_ID_EXTENDED 1 /*!< extended ID */

#define ISO11898_RTR_DATA   0 /*!< data frame */
#define ISO11898_RTR_REMOTE 1 /*!< remote frame */

/** @defgroup ISO11898_INTSTS iso11898 interrupt status definition
  * @{
  */
#define ISO11898_INTSTS_RX               (1 << 0)
#define ISO11898_INTSTS_TX               (1 << 1)
#define ISO11898_INTSTS_ERROR_WARNING    (1 << 2)
#define ISO11898_INTSTS_DATA_OVERRUN     (1 << 3)
#define ISO11898_INTSTS_ERROR_PASSIVE    (1 << 5)
#define ISO11898_INTSTS_ARBITRATION_LOST (1 << 6)
#define ISO11898_INTSTS_BUS_ERROR        (1 << 7)
/**
  * @}
  */

#define ISO11898_STATUS_RX_NOT_EMPTY  (1 << 0)
#define ISO11898_STATUS_RX_OVERRUN    (1 << 1)
#define ISO11898_STATUS_TX_AVAILABLE  (1 << 2)
#define ISO11898_STATUS_TX_COMPLETE   (1 << 3)
#define ISO11898_STATUS_RX_RECEIVING  (1 << 4)
#define ISO11898_STATUS_TX_SENDING    (1 << 5)
#define ISO11898_STATUS_ERROR_COUNTER (1 << 6)
#define ISO11898_STATUS_BUS_OFF       (1 << 7)

#define ISO11898_FILTER_TYPE_SINGLE 0
#define ISO11898_FILTER_TYPE_DUAL   1

struct bflb_iso11898_config_s {
    uint8_t prescaler; /*!< specifies the length of a time quantum, ranges from 1 to 63, tq=tclk*2*(prescaler+1) */
    uint8_t mode;      /*!< specifies the CAN operating mode. @ref ISO11898_MODE_XXX */
    uint8_t sample;    /*!< specifies the number of sample times. @ref ISO11898_SAMPLE_XXX */
    uint8_t sjw;       /*!< specifies the maximum number of time quanta the ISO11898 hardware is allowed to lengthen or shorten a bit to perform resynchronization. @ref ISO11898_SJW_XXX */
    uint8_t bs1;       /*!< specifies the number of time quanta in Bit Segment 1. @ref ISO11898_BS1_XXX */
    uint8_t bs2;       /*!< specifies the number of time quanta in Bit Segment 2. @ref ISO11898_BS2_XXX */
};

struct bflb_iso11898_msg_s {
    uint32_t std_id; /*!< specifies the standard identifier, this parameter can be a value between 0 to 0x7FF */
    uint32_t ext_id; /*!< specifies the extended identifier, this parameter can be a value between 0 to 0x1FFFFFFF */
    uint8_t id_type; /*!< specifies the type of identifier for the message that will be send or received. @ref ISO11898_ID_XXX */
    uint8_t rtr;     /*!< specifies the type of frame for the message that will be send or received, @ref ISO11898_RTR_XXX */
    uint8_t dlc;     /*!< specifies the length of the frame that will be send or received, this parameter can be a value between 0 to 8 */
    uint8_t data[8]; /*!< contains the data to be send or received, it ranges from 0 to 0xFF */
};

struct bflb_iso11898_filter_s {
    uint8_t filter_type;
    uint8_t code0;
    uint8_t code1;
    uint8_t code2;
    uint8_t code3;
    uint8_t mask0;
    uint8_t mask1;
    uint8_t mask2;
    uint8_t mask3;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] config
 */
void bflb_iso11898_init(struct bflb_device_s *dev, struct bflb_iso11898_config_s *config);

/**
 * @brief
 *
 * @param [in] dev
 */
void bflb_iso11898_deinit(struct bflb_device_s *dev);

/**
 * @brief
 *
 * @param [in] dev
 */
void bflb_iso11898_abort_send(struct bflb_device_s *dev);

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] msg
 * @param [in] timeout
 * @return int8_t
 */
int8_t bflb_iso11898_send(struct bflb_device_s *dev, struct bflb_iso11898_msg_s *msg, uint32_t timeout);

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] msg
 * @param [in] timeout
 * @return int8_t
 */
int8_t bflb_iso11898_recv(struct bflb_device_s *dev, struct bflb_iso11898_msg_s *msg, uint32_t timeout);

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] mode
 */
void bflb_iso11898_set_mode(struct bflb_device_s *dev, uint8_t mode);

/**
 * @brief
 *
 * @param [in] dev
 * @return uint8_t
 */
uint8_t bflb_iso11898_get_status(struct bflb_device_s *dev);

/**
 * @brief
 *
 * @param [in] dev
 * @return uint8_t
 */
uint8_t bflb_iso11898_get_mode(struct bflb_device_s *dev);

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] filter
 */
void bflb_iso11898_set_filter(struct bflb_device_s *dev, struct bflb_iso11898_filter_s *filter);

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] mask
 */
void bflb_iso11898_txint_mask(struct bflb_device_s *dev, bool mask);

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] mask
 */
void bflb_iso11898_rxint_mask(struct bflb_device_s *dev, bool mask);

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] mask
 */
void bflb_iso11898_errint_mask(struct bflb_device_s *dev, bool mask);

/**
 * @brief
 *
 * @param [in] dev
 * @return uint32_t
 */
uint32_t bflb_iso11898_get_int_status(struct bflb_device_s *dev);

/**
 * @brief
 *
 * @param [in] dev
 * @param [in] cmd
 * @param [in] arg
 * @return int
 */
int bflb_iso11898_feature_control(struct bflb_device_s *dev, int cmd, size_t arg);

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
