/**
  **************************************************************************
  * @file     at32f423_usart.h
  * @brief    at32f423 usart header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F423_USART_H
#define __AT32F423_USART_H

#ifdef __cplusplus
extern "C" {
#endif


/* includes ------------------------------------------------------------------*/
#include "at32f423.h"

/** @addtogroup AT32F423_periph_driver
  * @{
  */

/** @addtogroup USART
  * @{
  */

/** @defgroup USART_flags_definition
  * @brief usart flag
  * @{
  */

#define USART_PERR_FLAG                  ((uint32_t)0x00000001) /*!< usart parity error flag */
#define USART_FERR_FLAG                  ((uint32_t)0x00000002) /*!< usart framing error flag */
#define USART_NERR_FLAG                  ((uint32_t)0x00000004) /*!< usart noise error flag */
#define USART_ROERR_FLAG                 ((uint32_t)0x00000008) /*!< usart receiver overflow error flag */
#define USART_IDLEF_FLAG                 ((uint32_t)0x00000010) /*!< usart idle flag */
#define USART_RDBF_FLAG                  ((uint32_t)0x00000020) /*!< usart receive data buffer full flag */
#define USART_TDC_FLAG                   ((uint32_t)0x00000040) /*!< usart transmit data complete flag */
#define USART_TDBE_FLAG                  ((uint32_t)0x00000080) /*!< usart transmit data buffer empty flag */
#define USART_BFF_FLAG                   ((uint32_t)0x00000100) /*!< usart break frame flag */
#define USART_CTSCF_FLAG                 ((uint32_t)0x00000200) /*!< usart cts change flag */
#define USART_RTODF_FLAG                 ((uint32_t)0x00000800) /*!< usart receiver time out detection flag */
#define USART_OCCUPY_FLAG                ((uint32_t)0x00010000) /*!< usart receiver occupy flag */
#define USART_CMDF_FLAG                  ((uint32_t)0x00020000) /*!< usart character match detection flag */
#define USART_LPWUF_FLAG                 ((uint32_t)0x00100000) /*!< usart low power wake up flag */
#define USART_TXON_FLAG                  ((uint32_t)0x00200000) /*!< usart transmitter turned on flag */
#define USART_RXON_FLAG                  ((uint32_t)0x00400000) /*!< usart receiver turned on flag */

/**
  * @}
  */

/** @defgroup USART_interrupts_definition
  * @brief usart interrupt
  * @{
  */

#define USART_IDLE_INT                   MAKE_VALUE(0x0C,0x04) /*!< usart idle interrupt */
#define USART_RDBF_INT                   MAKE_VALUE(0x0C,0x05) /*!< usart receive data buffer full interrupt */
#define USART_TDC_INT                    MAKE_VALUE(0x0C,0x06) /*!< usart transmit data complete interrupt */
#define USART_TDBE_INT                   MAKE_VALUE(0x0C,0x07) /*!< usart transmit data buffer empty interrupt */
#define USART_PERR_INT                   MAKE_VALUE(0x0C,0x08) /*!< usart parity error interrupt */
#define USART_BF_INT                     MAKE_VALUE(0x10,0x06) /*!< usart break frame interrupt */
#define USART_ERR_INT                    MAKE_VALUE(0x14,0x00) /*!< usart error interrupt */
#define USART_CTSCF_INT                  MAKE_VALUE(0x14,0x0A) /*!< usart cts change interrupt */
#define USART_LPWUF_INT                  MAKE_VALUE(0x14,0x0D) /*!< usart low power wakeup flag interrupt */
#define USART_RTOD_INT                   MAKE_VALUE(0x0C,0x1A) /*!< usart receiver time out detection flag interrupt */
#define USART_CMD_INT                    MAKE_VALUE(0x0C,0x0E) /*!< usart character match detection flag interrupt */

/**
  * @}
  */

/** @defgroup USART_exported_types
  * @{
  */

/**
  * @brief  usart parity selection type
  */
typedef enum
{
  USART_PARITY_NONE                      = 0x00, /*!< usart no parity */
  USART_PARITY_EVEN                      = 0x01, /*!< usart even parity */
  USART_PARITY_ODD                       = 0x02  /*!< usart odd parity */
} usart_parity_selection_type;

/**
  * @brief  usart wakeup mode type
  */
typedef enum
{
  USART_WAKEUP_BY_IDLE_FRAME             = 0x00, /*!< usart wakeup by idle frame */
  USART_WAKEUP_BY_MATCHING_ID            = 0x01  /*!< usart wakeup by matching id */
} usart_wakeup_mode_type;

/**
  * @brief  usart data bit num type
  */
typedef enum
{
  USART_DATA_8BITS                       = 0x00, /*!< usart data size is 8 bits */
  USART_DATA_9BITS                       = 0x01, /*!< usart data size is 9 bits */
  USART_DATA_7BITS                       = 0x02  /*!< usart data size is 7 bits */
} usart_data_bit_num_type;

/**
  * @brief  usart break frame bit num type
  */
typedef enum
{
  USART_BREAK_10BITS                     = 0x00, /*!< usart lin mode berak frame detection 10 bits */
  USART_BREAK_11BITS                     = 0x01  /*!< usart lin mode berak frame detection 11 bits */
} usart_break_bit_num_type;

/**
  * @brief  usart phase of the clock type
  */
typedef enum
{
  USART_CLOCK_PHASE_1EDGE                = 0x00, /*!< usart data capture is done on the clock leading edge */
  USART_CLOCK_PHASE_2EDGE                = 0x01  /*!< usart data capture is done on the clock trailing edge */
} usart_clock_phase_type;

/**
  * @brief  usart polarity of the clock type
  */
typedef enum
{
  USART_CLOCK_POLARITY_LOW               = 0x00, /*!< usart clock stay low level outside transmission window */
  USART_CLOCK_POLARITY_HIGH              = 0x01  /*!< usart clock stay high level outside transmission window */
} usart_clock_polarity_type;

/**
  * @brief  usart last bit clock pulse type
  */
typedef enum
{
  USART_CLOCK_LAST_BIT_NONE              = 0x00, /*!< usart clock pulse of the last data bit is not outputted */
  USART_CLOCK_LAST_BIT_OUTPUT            = 0x01  /*!< usart clock pulse of the last data bit is outputted */
} usart_lbcp_type;

/**
  * @brief  usart stop bit num type
  */
typedef enum
{
  USART_STOP_1_BIT                       = 0x00, /*!< usart stop bits num is 1 */
  USART_STOP_0_5_BIT                     = 0x01, /*!< usart stop bits num is 0.5 */
  USART_STOP_2_BIT                       = 0x02, /*!< usart stop bits num is 2 */
  USART_STOP_1_5_BIT                     = 0x03  /*!< usart stop bits num is 1.5 */
} usart_stop_bit_num_type;

/**
  * @brief  usart hardware flow control type
  */
typedef enum
{
  USART_HARDWARE_FLOW_NONE               = 0x00, /*!< usart without hardware flow */
  USART_HARDWARE_FLOW_RTS                = 0x01, /*!< usart hardware flow only rts */
  USART_HARDWARE_FLOW_CTS                = 0x02, /*!< usart hardware flow only cts */
  USART_HARDWARE_FLOW_RTS_CTS            = 0x03  /*!< usart hardware flow both rts and cts */
} usart_hardware_flow_control_type;

/**
  * @brief  usart identification bit num type
  */
typedef enum
{
  USART_ID_FIXED_4_BIT                   = 0x00, /*!< usart id bit num fixed 4 bits */
  USART_ID_RELATED_DATA_BIT              = 0x01  /*!< usart id bit num related data bits */
} usart_identification_bit_num_type;

/**
  * @brief  usart de polarity type
  */
typedef enum
{
  USART_DE_POLARITY_HIGH                 = 0x00, /*!< usart de polarity high */
  USART_DE_POLARITY_LOW                  = 0x01  /*!< usart de polarity low */
} usart_de_polarity_type;

/**
  * @brief  usart wakeup method type
  */
typedef enum
{
  USART_WAKEUP_METHOD_ID                 = 0x00, /*!< usart low power wakeup method id match */
  USART_WAKEUP_METHOD_START              = 0x02, /*!< usart low power wakeup method start bit */
  USART_WAKEUP_METHOD_RDBF               = 0x03, /*!< usart low power wakeup method receive data buffer full */
} usart_wakeup_method_type;

/**
  * @brief type define usart register all
  */
typedef struct
{
  /**
    * @brief usart sts register, offset:0x00
    */
  union
  {
    __IO uint32_t sts;
    struct
    {
      __IO uint32_t perr                 : 1; /* [0] */
      __IO uint32_t ferr                 : 1; /* [1] */
      __IO uint32_t nerr                 : 1; /* [2] */
      __IO uint32_t roerr                : 1; /* [3] */
      __IO uint32_t idlef                : 1; /* [4] */
      __IO uint32_t rdbf                 : 1; /* [5] */
      __IO uint32_t tdc                  : 1; /* [6] */
      __IO uint32_t tdbe                 : 1; /* [7] */
      __IO uint32_t bff                  : 1; /* [8] */
      __IO uint32_t ctscf                : 1; /* [9] */
      __IO uint32_t reserved1            : 1; /* [10] */
      __IO uint32_t rtodf                : 1; /* [11] */
      __IO uint32_t reserved2            : 4; /* [12:15] */
      __IO uint32_t occupy               : 1; /* [16] */
      __IO uint32_t cmdf                 : 1; /* [17] */
      __IO uint32_t reserved3            : 2; /* [18:19] */
      __IO uint32_t lpwuf                : 1; /* [20] */
      __IO uint32_t txon                 : 1; /* [21] */
      __IO uint32_t rxon                 : 1; /* [22] */
      __IO uint32_t reserved4            : 9; /* [31:23] */
    } sts_bit;
  };

  /**
    * @brief usart dt register, offset:0x04
    */
  union
  {
    __IO uint32_t dt;
    struct
    {
      __IO uint32_t dt                   : 9; /* [8:0] */
      __IO uint32_t reserved1            : 23;/* [31:9] */
    } dt_bit;
  };

  /**
    * @brief usart baudr register, offset:0x08
    */
  union
  {
    __IO uint32_t baudr;
    struct
    {
      __IO uint32_t div                  : 16;/* [15:0] */
      __IO uint32_t reserved1            : 16;/* [31:16] */
    } baudr_bit;
  };

  /**
    * @brief usart ctrl1 register, offset:0x0C
    */
  union
  {
    __IO uint32_t ctrl1;
    struct
    {
      __IO uint32_t sbf                  : 1; /* [0] */
      __IO uint32_t rm                   : 1; /* [1] */
      __IO uint32_t ren                  : 1; /* [2] */
      __IO uint32_t ten                  : 1; /* [3] */
      __IO uint32_t idleien              : 1; /* [4] */
      __IO uint32_t rdbfien              : 1; /* [5] */
      __IO uint32_t tdcien               : 1; /* [6] */
      __IO uint32_t tdbeien              : 1; /* [7] */
      __IO uint32_t perrien              : 1; /* [8] */
      __IO uint32_t psel                 : 1; /* [9] */
      __IO uint32_t pen                  : 1; /* [10] */
      __IO uint32_t wum                  : 1; /* [11] */
      __IO uint32_t dbn0                 : 1; /* [12] */
      __IO uint32_t uen                  : 1; /* [13] */
      __IO uint32_t cmdie                : 1; /* [14] */
      __IO uint32_t reserved1            : 1; /* [15] */
      __IO uint32_t tcdt                 : 5; /* [20:16] */
      __IO uint32_t tsdt                 : 5; /* [25:21] */
      __IO uint32_t retodie              : 1; /* [26] */
      __IO uint32_t rtoden               : 1; /* [27] */
      __IO uint32_t dbn1                 : 1; /* [28] */
      __IO uint32_t reserved2            : 3; /* [31:29] */
    } ctrl1_bit;
  };

  /**
    * @brief usart ctrl2 register, offset:0x10
    */
  union
  {
    __IO uint32_t ctrl2;
    struct
    {
      __IO uint32_t idl                  : 4; /* [3:0] */
      __IO uint32_t idbn                 : 1; /* [4] */
      __IO uint32_t bfbn                 : 1; /* [5] */
      __IO uint32_t bfien                : 1; /* [6] */
      __IO uint32_t reserved1            : 1; /* [7] */
      __IO uint32_t lbcp                 : 1; /* [8] */
      __IO uint32_t clkpha               : 1; /* [9] */
      __IO uint32_t clkpol               : 1; /* [10] */
      __IO uint32_t clken                : 1; /* [11] */
      __IO uint32_t stopbn               : 2; /* [13:12] */
      __IO uint32_t linen                : 1; /* [14] */
      __IO uint32_t trpswap              : 1; /* [15] */
      __IO uint32_t rxrev                : 1; /* [16] */
      __IO uint32_t txrev                : 1; /* [17] */
      __IO uint32_t dtrev                : 1; /* [18] */
      __IO uint32_t mtf                  : 1; /* [19] */
      __IO uint32_t reserved2            : 8; /* [27:20] */
      __IO uint32_t idh                  : 4; /* [31:28] */
    } ctrl2_bit;
  };

  /**
    * @brief usart ctrl3 register, offset:0x14
    */
  union
  {
    __IO uint32_t ctrl3;
    struct
    {
      __IO uint32_t errien               : 1; /* [0] */
      __IO uint32_t irdaen               : 1; /* [1] */
      __IO uint32_t irdalp               : 1; /* [2] */
      __IO uint32_t slben                : 1; /* [3] */
      __IO uint32_t scnacken             : 1; /* [4] */
      __IO uint32_t scmen                : 1; /* [5] */
      __IO uint32_t dmaren               : 1; /* [6] */
      __IO uint32_t dmaten               : 1; /* [7] */
      __IO uint32_t rtsen                : 1; /* [8] */
      __IO uint32_t ctsen                : 1; /* [9] */
      __IO uint32_t ctscfien             : 1; /* [10] */
      __IO uint32_t smusen               : 1; /* [11] */
      __IO uint32_t reserved1            : 1; /* [12] */
      __IO uint32_t lpwufie              : 1; /* [13] */
      __IO uint32_t rs485en              : 1; /* [14] */
      __IO uint32_t dep                  : 1; /* [15] */
      __IO uint32_t lpwum                : 2; /* [17:16] */
      __IO uint32_t reserved2            : 14;/* [31:18] */
    } ctrl3_bit;
  };

  /**
    * @brief usart gdiv register, offset:0x18
    */
  union
  {
    __IO uint32_t gdiv;
    struct
    {
      __IO uint32_t isdiv                : 8; /* [7:0] */
      __IO uint32_t scgt                 : 8; /* [15:8] */
      __IO uint32_t reserved1            : 16;/* [31:16] */
    } gdiv_bit;
  };

  /**
  * @brief usart rtov register, offset:0x1C
  */
  union
  {
    __IO uint32_t rtov;
    struct
    {
      __IO uint32_t rtov                 : 24;/* [23:0] */
      __IO uint32_t reserved1            : 8; /* [31:24] */
    } rtov_bit;
  };

  /**
  * @brief usart ifc register, offset:0x20
  */
  union
  {
    __IO uint32_t ifc;
    struct
    {
      __IO uint32_t reserved1            : 11;/* [10:0] */
      __IO uint32_t lpwufc               : 1; /* [11] */
      __IO uint32_t reserved2            : 5; /* [16:12] */
      __IO uint32_t cmdfc                : 1; /* [17] */
      __IO uint32_t reserved3            : 2; /* [19:18] */
      __IO uint32_t rtodfc               : 1; /* [20] */
      __IO uint32_t reserved4            : 11;/* [31:21] */
    } ifc_bit;
  };
} usart_type;

/**
  * @}
  */

#define USART1                           ((usart_type *) USART1_BASE)
#define USART2                           ((usart_type *) USART2_BASE)
#define USART3                           ((usart_type *) USART3_BASE)
#define USART4                           ((usart_type *) USART4_BASE)
#define USART5                           ((usart_type *) USART5_BASE)
#define USART6                           ((usart_type *) USART6_BASE)
#define USART7                           ((usart_type *) USART7_BASE)
#if defined (AT32F423Kx) || defined (AT32F423Tx) || defined (AT32F423Cx) || \
    defined (AT32F423Rx) || defined (AT32F423Vx)
#define USART8                           ((usart_type *) USART8_BASE)
#endif

/** @defgroup USART_exported_functions
  * @{
  */

void usart_reset(usart_type* usart_x);
void usart_init(usart_type* usart_x, uint32_t baud_rate, usart_data_bit_num_type data_bit, usart_stop_bit_num_type stop_bit);
void usart_parity_selection_config(usart_type* usart_x, usart_parity_selection_type parity);
void usart_enable(usart_type* usart_x, confirm_state new_state);
void usart_transmitter_enable(usart_type* usart_x, confirm_state new_state);
void usart_receiver_enable(usart_type* usart_x, confirm_state new_state);
void usart_clock_config(usart_type* usart_x, usart_clock_polarity_type clk_pol, usart_clock_phase_type clk_pha, usart_lbcp_type clk_lb);
void usart_clock_enable(usart_type* usart_x, confirm_state new_state);
void usart_interrupt_enable(usart_type* usart_x, uint32_t usart_int, confirm_state new_state);
void usart_dma_transmitter_enable(usart_type* usart_x, confirm_state new_state);
void usart_dma_receiver_enable(usart_type* usart_x, confirm_state new_state);
void usart_wakeup_id_set(usart_type* usart_x, uint8_t usart_id);
void usart_wakeup_mode_set(usart_type* usart_x, usart_wakeup_mode_type wakeup_mode);
void usart_receiver_mute_enable(usart_type* usart_x, confirm_state new_state);
void usart_break_bit_num_set(usart_type* usart_x, usart_break_bit_num_type break_bit);
void usart_lin_mode_enable(usart_type* usart_x, confirm_state new_state);
void usart_data_transmit(usart_type* usart_x, uint16_t data);
uint16_t usart_data_receive(usart_type* usart_x);
void usart_break_send(usart_type* usart_x);
void usart_smartcard_guard_time_set(usart_type* usart_x, uint8_t guard_time_val);
void usart_irda_smartcard_division_set(usart_type* usart_x, uint8_t div_val);
void usart_smartcard_mode_enable(usart_type* usart_x, confirm_state new_state);
void usart_smartcard_nack_set(usart_type* usart_x, confirm_state new_state);
void usart_single_line_halfduplex_select(usart_type* usart_x, confirm_state new_state);
void usart_irda_mode_enable(usart_type* usart_x, confirm_state new_state);
void usart_irda_low_power_enable(usart_type* usart_x, confirm_state new_state);
void usart_hardware_flow_control_set(usart_type* usart_x,usart_hardware_flow_control_type flow_state);
flag_status usart_flag_get(usart_type* usart_x, uint32_t flag);
void usart_flag_clear(usart_type* usart_x, uint32_t flag);
void usart_rs485_delay_time_config(usart_type* usart_x, uint8_t start_delay_time, uint8_t complete_delay_time);
void usart_transmit_receive_pin_swap(usart_type* usart_x, confirm_state new_state);
void usart_id_bit_num_set(usart_type* usart_x, usart_identification_bit_num_type id_bit_num);
void usart_de_polarity_set(usart_type* usart_x, usart_de_polarity_type de_polarity);
void usart_rs485_mode_enable(usart_type* usart_x, confirm_state new_state);
void usart_low_power_wakeup_set(usart_type* usart_x, usart_wakeup_method_type wakeup_method);
void usart_deep_sleep_mode_enable(usart_type* usart_x, confirm_state new_state);
void usart_msb_transmit_first_enable(usart_type* usart_x, confirm_state new_state);
void usart_dt_polarity_reverse(usart_type* usart_x, confirm_state new_state);
void usart_transmit_pin_polarity_reverse(usart_type* usart_x, confirm_state new_state);
void usart_receive_pin_polarity_reverse(usart_type* usart_x, confirm_state new_state);
void usart_receiver_timeout_detection_enable(usart_type* usart_x, confirm_state new_state);
void usart_receiver_timeout_value_set(usart_type* usart_x, uint32_t time);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
