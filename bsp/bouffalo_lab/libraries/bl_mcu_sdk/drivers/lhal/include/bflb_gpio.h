#ifndef _BFLB_GPIO_H
#define _BFLB_GPIO_H

#include "bflb_core.h"

/** @addtogroup LHAL
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/**
 * @brief Gpio pin definitions
 *
 * BL602  : GPIO0/1/2/7/8/14/15/20/21/22
 * BL604  : GPIO0 ~ GPIO5, GPIO7/8/11/12/14/16/17/20/21/22
 * BL606  : GPIO0 ~ GPIO22
 * BL702  : GPIO0/1/2/7/8/9/14/15/17/23/24/25/26/27/28
 * BL704  : GPIO0 ~ GPIO3, GPIO7 ~ GPIO11, GPIO14/15, GPIO17 ~ GPIO28,
 * BL706  : GPIO0 ~ GPIO31
 * BL606P : GPIO0 ~ GPIO5, GPIO11 ~ GPIO12, GPIO16 ~ GPIO21, GPIO24 ~ GPIO28, GPIO34 ~ GPIO41
 * BL616  : GPIO0 ~ GPIO3, GPIO10 ~ GPIO17, GPIO20 ~ GPIO22, GPIO27 ~ GPIO30
 * BL618  : GPIO0 ~ GPIO34
 * BL808C : GPIO0 ~ GPIO23, GPIO34 ~ GPIO45
 * BL808D : GPIO0 ~ GPIO8, GPIO11 ~ GPIO41
 *
 */

/** @defgroup GPIO_PIN gpio pin definition
  * @{
  */
#define GPIO_PIN_0      0
#define GPIO_PIN_1      1
#define GPIO_PIN_2      2
#define GPIO_PIN_3      3
#define GPIO_PIN_4      4
#define GPIO_PIN_5      5
#define GPIO_PIN_6      6
#define GPIO_PIN_7      7
#define GPIO_PIN_8      8
#define GPIO_PIN_9      9
#define GPIO_PIN_10     10
#define GPIO_PIN_11     11
#define GPIO_PIN_12     12
#define GPIO_PIN_13     13
#define GPIO_PIN_14     14
#define GPIO_PIN_15     15
#define GPIO_PIN_16     16
#define GPIO_PIN_17     17
#define GPIO_PIN_18     18
#define GPIO_PIN_19     19
#define GPIO_PIN_20     20
#define GPIO_PIN_21     21
#define GPIO_PIN_22     22
#define GPIO_PIN_23     23
#define GPIO_PIN_24     24
#define GPIO_PIN_25     25
#define GPIO_PIN_26     26
#define GPIO_PIN_27     27
#define GPIO_PIN_28     28
#define GPIO_PIN_29     29
#define GPIO_PIN_30     30
#define GPIO_PIN_31     31
#define GPIO_PIN_32     32
#define GPIO_PIN_33     33
#define GPIO_PIN_34     34
#define GPIO_PIN_35     35
#define GPIO_PIN_36     36
#define GPIO_PIN_37     37
#define GPIO_PIN_38     38
#define GPIO_PIN_39     39
#define GPIO_PIN_40     40
#define GPIO_PIN_41     41
#define GPIO_PIN_42     42
#define GPIO_PIN_43     43
#define GPIO_PIN_44     44
#define GPIO_PIN_45     45
/**
  * @}
  */

/* cfgset list */
#define GPIO_FUNC_SHIFT (0) /* Bits 0-4: GPIO function */
#define GPIO_FUNC_MASK  (0x1f << GPIO_FUNC_SHIFT)
#if defined(BL602)
#define GPIO_FUNC_SDIO (1 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_SPI0 (4 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2C0 (6 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_PWM0 (8 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_JTAG (14 << GPIO_FUNC_SHIFT)
#elif defined(BL702)
#define GPIO_FUNC_CLK_OUT  (0 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2S      (3 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_SPI0     (4 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2C0     (6 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_PWM0     (8 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_CAM      (9 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_JTAG     (14 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_EMAC     (19 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_CAM_MCLK (23 << GPIO_FUNC_SHIFT)
#elif defined(BL702L)
#define GPIO_FUNC_SPI0    (4 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2C0    (6 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_PWM0    (8 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_KEYSCAN (13 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_JTAG    (14 << GPIO_FUNC_SHIFT)
#elif defined(BL616)
#define GPIO_FUNC_SDH       (0 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_SPI0      (1 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2S       (3 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_PDM       (4 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2C0      (5 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2C1      (6 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_EMAC      (8 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_CAM       (9 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_SDU       (12 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_PWM0      (16 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_DBI_B     (22 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_DBI_C     (23 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_DBI_QSPI  (24 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_AUDAC_PWM (25 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_JTAG      (26 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_PEC       (27 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_CLKOUT    (31 << GPIO_FUNC_SHIFT)
#elif defined(BL606P) || defined(BL808)
#define GPIO_FUNC_SDH     (0 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_SPI0    (1 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2S     (3 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_PDM     (4 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2C0    (5 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2C1    (6 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_EMAC    (8 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_CAM     (9 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_SDU     (12 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_PWM0    (16 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_PWM1    (17 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_SPI1    (18 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2C2    (19 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2C3    (20 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2C3    (20 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_DBI_B   (22 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_DBI_C   (23 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_JTAG_LP (25 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_JTAG_M0 (26 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_JTAG_D0 (27 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_CLKOUT  (31 << GPIO_FUNC_SHIFT)
#elif defined(BL628)
#define GPIO_FUNC_SDH    (0 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_SPI0   (1 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2S    (3 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_PDM    (4 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2C0   (5 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_I2C1   (6 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_UART   (7 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_EMAC   (8 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_CAM    (9 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_SDU    (12 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_PWM0   (16 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_DBI_B  (22 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_DBI_C  (23 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_PEC    (27 << GPIO_FUNC_SHIFT)
#define GPIO_FUNC_CLKOUT (31 << GPIO_FUNC_SHIFT)
#endif

#define GPIO_MODE_SHIFT                      (5) /* Bits 5-6: Port Mode */
#define GPIO_MODE_MASK                       (3 << GPIO_MODE_SHIFT)
#define GPIO_INPUT                           (0 << GPIO_MODE_SHIFT) /* Input Enable */
#define GPIO_OUTPUT                          (1 << GPIO_MODE_SHIFT) /* Output Enable */
#define GPIO_ANALOG                          (2 << GPIO_MODE_SHIFT) /* Analog Enable */
#define GPIO_ALTERNATE                       (3 << GPIO_MODE_SHIFT) /* Alternate Enable */

#define GPIO_PUPD_SHIFT                      (7) /* Bits 7-8: Pull-up/down */
#define GPIO_PUPD_MASK                       (3 << GPIO_PUPD_SHIFT)
#define GPIO_FLOAT                           (0 << GPIO_PUPD_SHIFT) /* No pull-up, pull-down */
#define GPIO_PULLUP                          (1 << GPIO_PUPD_SHIFT) /* Pull-up */
#define GPIO_PULLDOWN                        (2 << GPIO_PUPD_SHIFT) /* Pull-down */

#define GPIO_SMT_SHIFT                       (9) /* Bits 9: SMT Enable */
#define GPIO_SMT_MASK                        (1 << GPIO_SMT_SHIFT)
#define GPIO_SMT_DIS                         (0 << GPIO_SMT_SHIFT)
#define GPIO_SMT_EN                          (1 << GPIO_SMT_SHIFT)

#define GPIO_DRV_SHIFT                       (10) /* Bits 10-11: Drive */
#define GPIO_DRV_MASK                        (3 << GPIO_DRV_SHIFT)
#define GPIO_DRV_0                           (0 << GPIO_DRV_SHIFT)
#define GPIO_DRV_1                           (1 << GPIO_DRV_SHIFT)
#define GPIO_DRV_2                           (2 << GPIO_DRV_SHIFT)
#define GPIO_DRV_3                           (3 << GPIO_DRV_SHIFT)

/** @defgroup GPIO_INT_TRIG_MODE gpio interrupt trigger mode definition
  * @{
  */
#define GPIO_INT_TRIG_MODE_SYNC_FALLING_EDGE 0
#define GPIO_INT_TRIG_MODE_SYNC_RISING_EDGE  1
#define GPIO_INT_TRIG_MODE_SYNC_LOW_LEVEL    2
#define GPIO_INT_TRIG_MODE_SYNC_HIGH_LEVEL   3
#if defined(BL602) || defined(BL702)
#define GPIO_INT_TRIG_MODE_ASYNC_FALLING_EDGE 4
#define GPIO_INT_TRIG_MODE_ASYNC_RISING_EDGE  5
#define GPIO_INT_TRIG_MODE_ASYNC_LOW_LEVEL    6
#define GPIO_INT_TRIG_MODE_ASYNC_HIGH_LEVEL   7
#else
#define GPIO_INT_TRIG_MODE_SYNC_FALLING_RISING_EDGE 4
#define GPIO_INT_TRIG_MODE_ASYNC_FALLING_EDGE       8
#define GPIO_INT_TRIG_MODE_ASYNC_RISING_EDGE        9
#define GPIO_INT_TRIG_MODE_ASYNC_LOW_LEVEL          10
#define GPIO_INT_TRIG_MODE_ASYNC_HIGH_LEVEL         11
#endif
/**
  * @}
  */

/** @defgroup GPIO_UART_FUNC gpio uart function definition
  * @{
  */
#define GPIO_UART_FUNC_UART0_RTS 0
#define GPIO_UART_FUNC_UART0_CTS 1
#define GPIO_UART_FUNC_UART0_TX  2
#define GPIO_UART_FUNC_UART0_RX  3
#define GPIO_UART_FUNC_UART1_RTS 4
#define GPIO_UART_FUNC_UART1_CTS 5
#define GPIO_UART_FUNC_UART1_TX  6
#define GPIO_UART_FUNC_UART1_RX  7
#if defined(BL808) || defined(BL606P)
#define GPIO_UART_FUNC_UART2_RTS 8
#define GPIO_UART_FUNC_UART2_CTS 9
#define GPIO_UART_FUNC_UART2_TX  10
#define GPIO_UART_FUNC_UART2_RX  11
#endif
/**
  * @}
  */

/** @defgroup GPIO_ISO11898_FUNC gpio iso11898 function definition
  * @{
  */
#if defined(BL808) || defined(BL606P)|| defined(BL616)|| defined(BL628)
#define GPIO_ISO11898_FUNC_TX 10
#define GPIO_ISO11898_FUNC_RX 11
#endif
/**
  * @}
  */

/** @defgroup GPIO_CMD gpio feature control cmd definition
  * @{
  */
#define GPIO_CMD_GET_GPIO_FUN (0x01)
/**
  * @}
  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize gpio pin.
 *
 * @param [in] dev device handle
 * @param [in] pin gpio pin, use @ref GPIO_PIN
 * @param [in] cfgset gpio config mask
 */
void bflb_gpio_init(struct bflb_device_s *dev, uint8_t pin, uint32_t cfgset);

/**
 * @brief Deinitialize gpio pin with input float.
 *
 * @param [in] dev device handle
 * @param [in] pin gpio pin, use @ref GPIO_PIN
 */
void bflb_gpio_deinit(struct bflb_device_s *dev, uint8_t pin);

/**
 * @brief Write gpio pin with high level.
 *
 * @param [in] dev device handle
 * @param [in] pin gpio pin, use @ref GPIO_PIN
 */
void bflb_gpio_set(struct bflb_device_s *dev, uint8_t pin);

/**
 * @brief Write gpio pin with low level.
 *
 * @param [in] dev device handle
 * @param [in] pin gpio pin, use @ref GPIO_PIN
 */
void bflb_gpio_reset(struct bflb_device_s *dev, uint8_t pin);

/**
 * @brief Read level from gpio pin.
 *
 * @param [in] dev device handle
 * @param [in] pin gpio pin, use @ref GPIO_PIN
 * @return true means high level, otherwise low level
 */
bool bflb_gpio_read(struct bflb_device_s *dev, uint8_t pin);

/**
 * @brief Write gpio pin 0~31.
 *
 * @param [in] dev device handle
 * @param [in] val gpio pin 0~31 value
 */
void bflb_gpio_pin0_31_write(struct bflb_device_s *dev, uint32_t val);

/**
 * @brief Write gpio pin 32~63.
 *
 * @param [in] dev device handle
 * @param [in] val gpio pin 32~63 value
 */
void bflb_gpio_pin32_63_write(struct bflb_device_s *dev, uint32_t val);

/**
 * @brief Read level from gpio pin 0~31.
 *
 * @param [in] dev device handle
 * @return level of gpio pin 0~31
 */
uint32_t bflb_gpio_pin0_31_read(struct bflb_device_s *dev);

/**
 * @brief Read level from gpio pin 32~63.
 *
 * @param [in] dev device handle
 * @return level of gpio pin32~63
 */
uint32_t bflb_gpio_pin32_63_read(struct bflb_device_s *dev);

/**
 * @brief Config gpio pin interrupt.
 *
 * @param [in] dev device handle
 * @param [in] pin gpio pin, use @ref GPIO_PIN
 * @param [in] trig_mode mode to trigger interrupt
 */
void bflb_gpio_int_init(struct bflb_device_s *dev, uint8_t pin, uint8_t trig_mode);

/**
 * @brief Enable or disable gpio pin interrupt.
 *
 * @param [in] dev device handle
 * @param [in] pin gpio pin, use @ref GPIO_PIN
 * @param [in] mask true means disable, false means enable
 */
void bflb_gpio_int_mask(struct bflb_device_s *dev, uint8_t pin, bool mask);

/**
 * @brief Get gpio pin interrupt status.
 *
 * @param [in] dev device handle
 * @param [in] pin gpio pin, use @ref GPIO_PIN
 * @return true means yes, false means no
 */
bool bflb_gpio_get_intstatus(struct bflb_device_s *dev, uint8_t pin);

/**
 * @brief Clear gpio pin interrupt status.
 *
 * @param [in] dev device handle
 * @param [in] pin gpio pin, use @ref GPIO_PIN
 */
void bflb_gpio_int_clear(struct bflb_device_s *dev, uint8_t pin);

/**
 * @brief Config gpio pin with uart function.
 *
 * @param [in] dev device handle
 * @param [in] pin gpio pin, use @ref GPIO_PIN
 * @param [in] uart_func uart function, use @ref GPIO_UART_FUNC
 */
void bflb_gpio_uart_init(struct bflb_device_s *dev, uint8_t pin, uint8_t uart_func);

/**
 * @brief Config gpio pin with iso11898 function.
 *
 * @param [in] dev device handle
 * @param [in] pin gpio pin, use @ref GPIO_PIN
 * @param [in] iso11898_func iso11898 function, use @ref GPIO_ISO11898_FUNC
 */
void bflb_gpio_iso11898_init(struct bflb_device_s *dev, uint8_t pin, uint8_t iso11898_func);

/**
 * @brief Control gpio feature.
 *
 * @param [in] dev device handle
 * @param [in] cmd feature command, use @ref GPIO_CMD
 * @param [in] arg user data
 * @return A negated errno value on failure.
 */

int bflb_gpio_feature_control(struct bflb_device_s *dev, int cmd, size_t arg);

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
