/*
  ******************************************************************************
  * @file    HAL_DMA.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of DMA HAL module.
  ******************************************************************************
*/
#ifndef __HAL_DMA_H__
#define __HAL_DMA_H__

#include "ACM32Fxx_HAL.h"

#define DMA_CHANNEL_NUM     (5)

/** @defgroup DMA_DATA_FLOW
 *  @{
 */
#define    DMA_DATA_FLOW_M2M    (0x00000000)
#define    DMA_DATA_FLOW_M2P    (0x00000800)
#define    DMA_DATA_FLOW_P2M    (0x00001000)
/**
  * @}
  */


/** @defgroup REQUEST_ID
 *  @{
 */
#define    REG_M2M                        (0)

#define    REQ0_ADC                       (0)
#define    REQ1_SPI1_SEND                 (1)
#define    REQ2_SPI1_RECV                 (2)
#define    REQ3_SPI2_SEND                 (3)
#define    REQ4_SPI2_RECV                 (4)
#define    REQ5_UART1_SEND                (5)
#define    REQ6_UART1_RECV                (6)
#define    REQ7_UART2_SEND                (7)
#define    REQ8_UART2_RECV                (8)
#define    REQ9_I2C1_SEND                 (9)
#define    REQ10_I2C1_RECV                (10)
#define    REQ11_I2C2_SEND                (11)
#define    REQ12_I2C2_RECV                (12)
#define    REQ13_TIM1_CH1                 (13)
#define    REQ14_TIM1_CH2                 (14)
#define    REQ15_TIM1_CH3                 (15)
#define    REQ16_TIM1_CH4                 (16)
#define    REQ17_TIM1_UP                  (17)
#define    REQ18_TIM1_TRIG_COM            (18)
#define    REQ19_TIM3_CH3                 (19)
#define    REQ20_TIM3_CH4_OR_UP           (20)
#define    REQ21_TIM3_CH1_OR_TRIG         (21)
#define    REQ22_TIM3_CH2_LCDFRAME        (22)
#define    REQ23_TIM6_UP                  (23)
#define    REQ24_TIM15_CH1_UP_TRIG_COM    (24)
#define    REQ25_TIM15_CH2                (25)
#define    REQ26_TIM16_CH1_UP             (26)
#define    REQ27_UART3_SEND               (27)
#define    REQ28_TIM17_CH1_UP             (28)
#define    REQ29_UART3_RECV               (29)
#define    REQ30_LPUART_SEND              (30)
#define    REQ31_LPUART_RECV              (31)

#define    REQ_MAX_LIMIT                  (32)
/**
  * @}
  */


/** @defgroup DMA_SOURCE_ADDR_INCREASE
 *  @{
 */
#define    DMA_SOURCE_ADDR_INCREASE_DISABLE    (0x00000000)
#define    DMA_SOURCE_ADDR_INCREASE_ENABLE     (0x04000000)
/**
  * @}
  */


/** @defgroup DMA_DST_ADDR_INCREASE
 *  @{
 */
#define    DMA_DST_ADDR_INCREASE_DISABLE    (0x00000000)
#define    DMA_DST_ADDR_INCREASE_ENABLE     (0x08000000)
/**
  * @}
  */


/** @defgroup DMA_SRC_WIDTH
 *  @{
 */
#define    DMA_SRC_WIDTH_BYTE         (0x00000000)    /*  8bit */
#define    DMA_SRC_WIDTH_HALF_WORD    (0x00040000)    /* 16bit */
#define    DMA_SRC_WIDTH_WORD         (0x00080000)    /* 36bit */
/**
  * @}
  */

/** @defgroup DMA_DST_WIDTH
 *  @{
 */
#define    DMA_DST_WIDTH_BYTE         (0x00000000)    /*  8bit */
#define    DMA_DST_WIDTH_HALF_WORD    (0x00200000)    /* 16bit */
#define    DMA_DST_WIDTH_WORD         (0x00400000)    /* 36bit */
/**
  * @}
  */



 /** @defgroup DMA_MODE DMA MODE
 *  @{
 */
#define DMA_NORMAL                    0x00000000U                  /*!< Normal mode                  */
#define DMA_CIRCULAR                  0x00000001U                  /*!< Circular mode                */
/**
  * @}
  */

/**
  * @brief  DMA burst length Structure definition
  */
typedef enum
{
    DMA_BURST_LENGTH_1   = 0,
    DMA_BURST_LENGTH_4   = 1,
    DMA_BURST_LENGTH_8   = 2,
    DMA_BURST_LENGTH_16  = 3,
    DMA_BURST_LENGTH_32  = 4,
    DMA_BURST_LENGTH_64  = 5,
    DMA_BURST_LENGTH_128 = 6,
    DMA_BURST_LENGTH_256 = 7,
}DMA_BURST_LENGTH;


/**
  * @brief  DMA Configuration Structure definition
  */
typedef struct
{
    uint32_t Mode;                  /* This parameter can be a value of @ref DMA_MODE */

    uint32_t Data_Flow;             /* This parameter can be a value of @ref DMA_DATA_FLOW */

    uint32_t Request_ID;            /* This parameter can be a value of @ref REQUEST_ID */

    uint32_t Source_Inc;            /* This parameter can be a value of @ref DMA_SOURCE_ADDR_INCREASE */

    uint32_t Desination_Inc;        /* This parameter can be a value of @ref DMA_DST_ADDR_INCREASE */

    uint32_t Source_Width;          /* This parameter can be a value of @ref DMA_SRC_WIDTH */

    uint32_t Desination_Width;      /* This parameter can be a value of @ref DMA_DST_WIDTH */

}DMA_InitParaTypeDef;


/**
  * @brief  DMA handle Structure definition
  */
typedef struct
{
    DMA_Channel_TypeDef    *Instance;    /* DMA registers base address */

    DMA_InitParaTypeDef     Init;        /* DMA initialization parameters */

    void (*DMA_ITC_Callback)(void);      /* DMA transfer complete callback */

    void (*DMA_IE_Callback)(void);       /* DMA error complete callback */

}DMA_HandleTypeDef;

/**
  * @brief  DMA Link List Item Structure
  */
typedef struct DMA_NextLink
{
    uint32_t SrcAddr;               /* source address */

    uint32_t DstAddr;               /* desination address */

    struct DMA_NextLink *Next;      /* Next Link */

    uint32_t Control;               /* Control */

}DMA_LLI_InitTypeDef;


/** @defgroup  GPIO Private Macros
  * @{
  */
#define IS_DMA_MODE(MODE) (((MODE) == DMA_NORMAL )  || \
                           ((MODE) == DMA_CIRCULAR))

#define IS_DMA_ALL_INSTANCE(INSTANCE)    (((INSTANCE) == DMA_Channel0) || \
                                          ((INSTANCE) == DMA_Channel1) || \
                                          ((INSTANCE) == DMA_Channel2) || \
                                          ((INSTANCE) == DMA_Channel3) || \
                                          ((INSTANCE) == DMA_Channel4))

#define IS_DMA_DATA_FLOW(DATA_FLOW)      (((DATA_FLOW) == DMA_DATA_FLOW_M2M) || \
                                          ((DATA_FLOW) == DMA_DATA_FLOW_M2P) || \
                                          ((DATA_FLOW) == DMA_DATA_FLOW_P2M))

#define IS_DMA_REQUEST_ID(REQUEST_ID)     ((REQUEST_ID < REQ_MAX_LIMIT) ? true : false)

#define IS_DMA_SRC_WIDTH(WIDTH)          (((WIDTH) == DMA_SRC_WIDTH_BYTE)      || \
                                          ((WIDTH) == DMA_SRC_WIDTH_HALF_WORD) || \
                                          ((WIDTH) == DMA_SRC_WIDTH_WORD))

#define IS_DMA_DST_WIDTH(WIDTH)          (((WIDTH) == DMA_DST_WIDTH_BYTE)      || \
                                          ((WIDTH) == DMA_DST_WIDTH_HALF_WORD) || \
                                          ((WIDTH) == DMA_DST_WIDTH_WORD))
/**
  * @}
  */

/******************************************************************************/
/*                    Peripheral Registers Bits Definition                    */
/******************************************************************************/

/******************************************************************************/
/*                                    (DMA)                                   */
/******************************************************************************/

/****************  Bit definition for DMA CONFIG register  ***********************/
#define DMA_CONFIG_M2ENDIAN             BIT2
#define DMA_CONFIG_M1ENDIAN             BIT1
#define DMA_CONFIG_EN                   BIT0

/****************  Bit definition for DMA Channel CTRL register  ***********************/
#define DMA_CHANNEL_CTRL_ITC     BIT31
#define DMA_CHANNEL_CTRL_DI      BIT27
#define DMA_CHANNEL_CTRL_SI      BIT26


/****************  Bit definition for DMA Channel CONFIG register  ***********************/
#define DMA_CHANNEL_CONFIG_HALT                 BIT18
#define DMA_CHANNEL_CONFIG_ACTIVE               BIT17
#define DMA_CHANNEL_CONFIG_LOCK                 BIT16
#define DMA_CHANNEL_CONFIG_ITC                  BIT15
#define DMA_CHANNEL_CONFIG_IE                   BIT14
#define DMA_CHANNEL_CONFIG_FLOW_CTRL           (BIT11|BIT12|BIT13)
#define DMA_CHANNEL_CONFIG_DEST_PERIPH         (BIT6|BIT7|BIT8|BIT9|BIT10)
#define DMA_CHANNEL_CONFIG_DEST_PERIPH_POS     (6)
#define DMA_CHANNEL_CONFIG_SRC_PERIPH          (BIT1|BIT2|BIT3|BIT4|BIT5)
#define DMA_CHANNEL_CONFIG_SRC_PERIPH_POS      (1)
#define DMA_CHANNEL_CONFIG_EN                   BIT0


/* Exported functions --------------------------------------------------------*/

#define __HAL_LINK_DMA(_HANDLE_, _DMA_LINK_, _DMA_HANDLE_)    (_HANDLE_._DMA_LINK_ = &_DMA_HANDLE_)

/* HAL_DMA_IRQHandler */
void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma);

/* HAL_DMA_Init */
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma);

/* HAL_DMA_DeInit */
HAL_StatusTypeDef HAL_DMA_DeInit(DMA_HandleTypeDef *hdma);

/* HAL_DMA_Start */
HAL_StatusTypeDef HAL_DMA_Start(DMA_HandleTypeDef *hdma, uint32_t fu32_SrcAddr, uint32_t fu32_DstAddr, uint32_t fu32_Size);

/* HAL_DMA_Start */
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t fu32_SrcAddr, uint32_t fu32_DstAddr, uint32_t fu32_Size);

/* HAL_DMA_Abort */
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma);

/* HAL_DMA_GetState */
HAL_StatusTypeDef HAL_DMA_GetState(DMA_HandleTypeDef *hdma);

#endif
