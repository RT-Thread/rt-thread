/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_dcmipp.h
  * @author  MCD Application Team
  * @brief   Header file of DCMIPP HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32H7RSxx_HAL_DCMIPP_H
#define __STM32H7RSxx_HAL_DCMIPP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal_def.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
  * @{
  */

#if defined (DCMIPP)

/** @addtogroup DCMIPP DCMIPP
  * @brief DCMIPP HAL module driver
  * @{
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup DCMIPP_Exported_Types DCMIPP Exported Types
  * @brief    DCMIPP Exported Types
  * @{
  */
/**
  * @brief   DCMIPP Embedded Synchronisation Unmask codes structure definition
  */
typedef struct
{
  uint8_t FrameStartUnmask; /*!< Specifies the frame start delimiter unmask. */
  uint8_t LineStartUnmask;  /*!< Specifies the line start delimiter unmask.  */
  uint8_t LineEndUnmask;    /*!< Specifies the line end delimiter unmask.    */
  uint8_t FrameEndUnmask;   /*!< Specifies the frame end delimiter unmask.   */
} DCMIPP_EmbeddedSyncUnmaskTypeDef;

/**
  * @brief   DCMIPP Embedded Synchronisation codes structure definition (CCIR656)
  */
typedef struct
{
  uint8_t FrameStartCode;  /*!< Specifies the code of the frame start delimiter. */
  uint8_t LineStartCode;   /*!< Specifies the code of the line start delimiter.  */
  uint8_t LineEndCode;     /*!< Specifies the code of the line end delimiter.    */
  uint8_t FrameEndCode;    /*!< Specifies the code of the frame end delimiter.   */
} DCMIPP_EmbeddedSyncCodesTypeDef;


/**
  * @brief  HAL DCMIPP Parallel configuration structure definition
  */
typedef struct
{
  uint32_t  Format;                             /*!< Configures the DCMIPP Format
                                                  This parameter can be one value of @ref DCMIPP_Format              */
  uint32_t  VSPolarity;                         /*!< Specifies the Vertical synchronization polarity: High or Low.
                                                  This parameter can be a value of @ref DCMIPP_VSYNC_Polarity        */
  uint32_t  HSPolarity;                         /*!< Specifies the Horizontal synchronization polarity: High or Low.
                                                  This parameter can be a value of @ref DCMIPP_HSYNC_Polarity        */
  uint32_t  PCKPolarity;                        /*!< Specifies the Pixel clock polarity: Falling or Rising.
                                                  This parameter can be a value of @ref DCMIPP_PIXCK_Polarity        */
  uint32_t  ExtendedDataMode ;                  /*!< Specifies the data width: 8-bit, 10-bit, 12-bit 14-bit or 16-bits.
                                                  This parameter can be a value of @ref DCMIPP_Extended_Data_Mode    */
  uint32_t  SynchroMode;                        /*!< Specifies the Synchronization Mode: Hardware or Embedded.
                                                  This parameter can be a value of @ref DCMIPP_Synchronization_Mode  */
  DCMIPP_EmbeddedSyncCodesTypeDef SynchroCodes; /*!< Specifies the code of the line/frame start delimiter and the
                                                  line/frame end delimiter                                           */
  uint32_t  SwapBits;                           /*!< Enable or Disable the Swap Bits.
                                                  This parameter can be a value of @ref DCMIPP_SWAP_BITS             */
  uint32_t  SwapCycles;                         /*!<  Enable or Disable the Swap Cycles.
                                                  This parameter can be a value of @ref DCMIPP_SWAP_CYCLES           */
} DCMIPP_ParallelConfTypeDef;

/**
  * @brief  HAL DCMIPP Pipe configuration structure definition
  */
typedef struct
{
  uint32_t FrameRate;         /*!< Configures the DCMIPP Pipe Frame Rate
                                   This parameter can be one value of @ref DCMIPP_Frame_Rates      */
} DCMIPP_PipeConfTypeDef;

/**
  * @brief  HAL DCMIPP IPPLUG configuration structure definition
  */
typedef struct
{
  uint32_t Client;                      /*!< Configures the DCMIPP IPPLUG Client
                                             This parameter can be a value from @ref DCMIPP_IPPLUG_Client      */
  uint32_t MemoryPageSize;              /*!< Configures the DCMIPP IPPLUG Memory page size
                                             This parameter can be a value from @ref DCMIPP_Memory_Page_Size   */
  uint32_t Traffic;                     /*!< Configures the DCMIPP IPPLUG Traffic
                                             This parameter can be a value from @ref DCMIPP_Traffic_Burst_Size */
  uint32_t MaxOutstandingTransactions ; /*!< Configures the DCMIPP IPPLUG Maximum outstanding transactions
                                             This parameter can be a value from
                                             DCMIPP_Maximum_Outstanding_Transactions                           */
  uint32_t DPREGStart;                  /*!< Configures the End word of the FIFO of Clientx
                                             This parameter can be a value between 0 and  0x3FF                */
  uint32_t DPREGEnd;                    /*!< Configures the Start word of the FIFO of Clientx
                                             This parameter can be a value between 0 and  0x3FF                */
  uint32_t WLRURatio;                   /*!< Configures the DCMIPP Ratio for WLRU arbitration
                                             This parameter can be a value between 0 and 15                    */
} DCMIPP_IPPlugConfTypeDef;

/**
  * @brief  HAL DCMIPP Crop configuration structure definition
  */
typedef struct
{
  uint32_t VStart;   /*!< Configures the DCMIPP Crop Vertical Start
                          This parameter can be one value between 0 and 4095          */
  uint32_t HStart;   /*!< Configures the DCMIPP Crop Horizontal Start
                          This parameter can be one value between 0 and 4095          */
  uint32_t VSize;    /*!< Configures the DCMIPP Crop Vertical Size
                          This parameter can be one value between 0 and 4095          */
  uint32_t HSize;    /*!< Configures the DCMIPP Crop Horizontal Size
                          This parameter can be one value between 1 and 4095          */
  uint32_t PipeArea; /*!< Configures the DCMIPP Crop Area for the pipe0
                          This parameter can be one value of @ref DCMIPP_Crop_Area    */
} DCMIPP_CropConfTypeDef;


/**
  * @brief  HAL DCMIPP State enumeration definition
  */
typedef enum
{
  HAL_DCMIPP_STATE_RESET = 0x00U,  /*!< DCMIPP not yet initialized or disabled  */
  HAL_DCMIPP_STATE_INIT  = 0x01U,  /*!< DCMIPP initialized                      */
  HAL_DCMIPP_STATE_READY = 0x02U,  /*!< DCMIPP configured and ready for use     */
  HAL_DCMIPP_STATE_BUSY  = 0x03U,  /*!< DCMIPP internal processing is ongoing   */
  HAL_DCMIPP_STATE_ERROR = 0x04U,  /*!< DCMIPP state error                      */
} HAL_DCMIPP_StateTypeDef;

/**
  * @brief  HAL DCMIPP Pipe State enumeration definition
  */

typedef enum
{
  HAL_DCMIPP_PIPE_STATE_RESET             = 0x00U,  /*!< DCMIPP Pipe not yet initialized or disabled */
  HAL_DCMIPP_PIPE_STATE_READY             = 0x01U,  /*!< DCMIPP Pipe initialized and ready for use   */
  HAL_DCMIPP_PIPE_STATE_BUSY              = 0x02U,  /*!< DCMIPP internal processing is ongoing       */
  HAL_DCMIPP_PIPE_STATE_SUSPEND           = 0x03U,  /*!< DCMIPP pipe process is suspended            */
  HAL_DCMIPP_PIPE_STATE_ERROR             = 0x04U,  /*!< DCMIPP pipe error state                     */
} HAL_DCMIPP_PipeStateTypeDef;

#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL DCMIPP common Callback ID enumeration definition
  */
typedef enum
{
  HAL_DCMIPP_MSPINIT_CB_ID                = 0x00U,    /*!< DCMIPP MspInit callback ID                 */
  HAL_DCMIPP_MSPDEINIT_CB_ID              = 0x01U,    /*!< DCMIPP MspDeInit callback ID               */
  HAL_DCMIPP_ERROR_CB_ID                  = 0x02U,    /*!< DCMIPP Error callback ID                   */
} HAL_DCMIPP_CallbackIDTypeDef;

/**
  * @brief  HAL DCMIPP pipe Callback ID enumeration definition
  */
typedef enum
{
  HAL_DCMIPP_PIPE_LIMIT_EVENT_CB_ID       = 0x01U,    /*!< DCMIPP Pipe Limit event callback ID        */
  HAL_DCMIPP_PIPE_LINE_EVENT_CB_ID        = 0x02U,    /*!< DCMIPP Pipe Line event callback ID         */
  HAL_DCMIPP_PIPE_FRAME_EVENT_CB_ID       = 0x03U,    /*!< DCMIPP Pipe Frame event callback ID        */
  HAL_DCMIPP_PIPE_VSYNC_EVENT_CB_ID       = 0x04U,    /*!< DCMIPP Pipe Vsync event callback ID        */
  HAL_DCMIPP_PIPE_ERROR_CB_ID             = 0x05U,    /*!< DCMIPP Pipe Error callback ID              */
} HAL_DCMIPP_PIPE_CallbackIDTypeDef;
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */

/**
  * @brief  HAL DCMIPP handle structures definition
  */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
typedef struct __DCMIPP_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
{
  DCMIPP_TypeDef                    *Instance;                                             /*!< Register the DCMIPP base
                                                                                                address               */
  __IO HAL_DCMIPP_StateTypeDef      State;                                                 /*!< DCMIPP state          */
  __IO HAL_DCMIPP_PipeStateTypeDef  PipeState[DCMIPP_NUM_OF_PIPES];                        /*!< DCMIPP Pipes state    */
  __IO uint32_t                     ErrorCode;                                             /*!< DCMIPP Error code     */
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
  void (* PIPE_FrameEventCallback)(struct __DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe); /*!< DCMIPP Pipe Frame Event
                                                                                                Callback              */
  void (* PIPE_VsyncEventCallback)(struct __DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe); /*!< DCMIPP Pipe Vsync Event
                                                                                                Callback              */
  void (* PIPE_LineEventCallback)(struct __DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);  /*!< DCMIPP Pipe Line Event
                                                                                                Callback              */
  void (* PIPE_LimitEventCallback)(struct __DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe); /*!< DCMIPP Pipe Limit Event
                                                                                                Callback              */
  void (* PIPE_ErrorCallback)(struct __DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);      /*!< DCMIPP Pipe Error
                                                                                                Callback              */
  void (* ErrorCallback)(struct __DCMIPP_HandleTypeDef *hdcmipp);                         /*!< DCMIPP Error Callback */
  void (* MspInitCallback)(struct __DCMIPP_HandleTypeDef *hdcmipp);                       /*!< DCMIPP Msp Init
                                                                                                Callback              */
  void (* MspDeInitCallback)(struct __DCMIPP_HandleTypeDef *hdcmipp);                     /*!< DCMIPP Msp DeInit
                                                                                                Callback              */
#endif  /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
} DCMIPP_HandleTypeDef;

#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL DCMIPP Callback pointer definition
  */
typedef void (*pDCMIPP_CallbackTypeDef)(DCMIPP_HandleTypeDef *hdcmipp); /*!< Pointer to a DCMIPP common callback
                                                                              function */
typedef void (*pDCMIPP_PIPE_CallbackTypeDef)(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe); /*!< Pointer to a DCMIPP
                                                                                               Pipe callback function */
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup DCMIPP_Exported_Constants DCMIPP Exported Constants
  * @brief    DCMIPP Exported constants
  * @{
  */

/** @defgroup DCMIPP_Pipes DCMIPP Pipes
  * @{
  */
#define  DCMIPP_PIPE0      0U     /*!< DCMIPP Pipe0 (Dump pipe)       */
/**
  * @}
  */

/** @defgroup DCMIPP_Error_Codes DCMIPP Error Codes
  * @{
  */
#define HAL_DCMIPP_ERROR_NONE            (0x00000000U)             /*!< No error                  */
#define HAL_DCMIPP_ERROR_AXI_TRANSFER    (0x00000001U)             /*!< IPPLUG AXI Transfer error */
#define HAL_DCMIPP_ERROR_PARALLEL_SYNC   (0x00000002U)             /*!< Synchronization error     */
#define HAL_DCMIPP_ERROR_PIPE0_LIMIT     (0x00000004U)             /*!< Limit error on pipe0      */
#define HAL_DCMIPP_ERROR_PIPE0_OVR       (0x00000008U)             /*!< Overrun error on pipe0    */

#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
#define  HAL_DCMIPP_ERROR_INVALID_CALLBACK ((uint32_t)0x00000040U) /*!< Invalid Callback error  */
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup DCMIPP_Capture_Mode DCMIPP Capture Mode
  * @{
  */
#define  DCMIPP_MODE_CONTINUOUS   0U                      /*!< DCMIPP continuous mode (preview) */
#define  DCMIPP_MODE_SNAPSHOT     DCMIPP_P0FCTCR_CPTMODE  /*!< DCMIPP snapshot mode             */
/**
  * @}
  */


/** @defgroup DCMIPP_IPPLUG_Client DCMIPP IPPLUG Client
  * @{
  */
#define DCMIPP_CLIENT1  1U /*!< Client 1 identifier */
/**
  * @}
  */

/** @defgroup DCMIPP_Traffic_Burst_Size DCMIPP Traffic Burst Size
  * @{
  */
#define DCMIPP_TRAFFIC_BURST_SIZE_8BYTES   0U                                   /*!< Traffic Burst size 8 Bytes   */
#define DCMIPP_TRAFFIC_BURST_SIZE_16BYTES  (0x01U << DCMIPP_IPC1R1_TRAFFIC_Pos) /*!< Traffic Burst size 16 Bytes  */
#define DCMIPP_TRAFFIC_BURST_SIZE_32BYTES  (0x02U << DCMIPP_IPC1R1_TRAFFIC_Pos) /*!< Traffic Burst size 32 Bytes  */
#define DCMIPP_TRAFFIC_BURST_SIZE_64BYTES  (0x03U << DCMIPP_IPC1R1_TRAFFIC_Pos) /*!< Traffic Burst size 64 Bytes  */
#define DCMIPP_TRAFFIC_BURST_SIZE_128BYTES (0x04U << DCMIPP_IPC1R1_TRAFFIC_Pos) /*!< Traffic Burst size 128 Bytes */
/**
  * @}
  */

/** @defgroup DCMIPP_Memory_Page_Size DCMIPP Memory Page Size
  * @{
  */
#define DCMIPP_MEMORY_PAGE_SIZE_64BYTES  0U                                     /*!< Memory Page size 64 Bytes  */
#define DCMIPP_MEMORY_PAGE_SIZE_128BYTES (0x01U << DCMIPP_IPGR1_MEMORYPAGE_Pos) /*!< Memory Page size 128 Bytes */
#define DCMIPP_MEMORY_PAGE_SIZE_256BYTES (0x02U << DCMIPP_IPGR1_MEMORYPAGE_Pos) /*!< Memory Page size 256 Bytes */
#define DCMIPP_MEMORY_PAGE_SIZE_512BYTES (0x03U << DCMIPP_IPGR1_MEMORYPAGE_Pos) /*!< Memory Page size 512 Bytes */
#define DCMIPP_MEMORY_PAGE_SIZE_1KBYTES  (0x04U << DCMIPP_IPGR1_MEMORYPAGE_Pos) /*!< Memory Page size 1 Bytes   */
#define DCMIPP_MEMORY_PAGE_SIZE_2KBYTES  (0x05U << DCMIPP_IPGR1_MEMORYPAGE_Pos) /*!< Memory Page size 2 Bytes   */
#define DCMIPP_MEMORY_PAGE_SIZE_4KBYTES  (0x06U << DCMIPP_IPGR1_MEMORYPAGE_Pos) /*!< Memory Page size 4 Bytes   */
#define DCMIPP_MEMORY_PAGE_SIZE_8KBYTES  (0x07U << DCMIPP_IPGR1_MEMORYPAGE_Pos) /*!< Memory Page size 8 Bytes   */
/**
  * @}
  */
/** @defgroup DCMIPP_Maximum_Outstanding_Transactions DCMIPP Maximum Outstanding Transactions
  * @{
  */
#define DCMIPP_OUTSTANDING_TRANSACTION_NONE 0U                               /*!< Nooutstanding transaction limitation*/
#define DCMIPP_OUTSTANDING_TRANSACTION_2    (0x01U << DCMIPP_IPC1R1_OTR_Pos) /*!< Two outstanding transactions        */
#define DCMIPP_OUTSTANDING_TRANSACTION_3    (0x02U << DCMIPP_IPC1R1_OTR_Pos) /*!< Three outstanding transactions      */
#define DCMIPP_OUTSTANDING_TRANSACTION_4    (0x03U << DCMIPP_IPC1R1_OTR_Pos) /*!< Four outstanding transactions       */
/**
  * @}
  */

/** @defgroup DCMIPP_Frame_Rates  DCMIPP Frame Rates
  * @{
  */
#define DCMIPP_FRAME_RATE_ALL       0U                               /*!< All frames captured     */
#define DCMIPP_FRAME_RATE_1_OVER_2  (1U << DCMIPP_P0FCTCR_FRATE_Pos) /*!< 1 frame over 2 captured */
#define DCMIPP_FRAME_RATE_1_OVER_4  (2U << DCMIPP_P0FCTCR_FRATE_Pos) /*!< 1 frame over 4 captured */
#define DCMIPP_FRAME_RATE_1_OVER_8  (3U << DCMIPP_P0FCTCR_FRATE_Pos) /*!< 1 frame over 8 captured */
/**
  * @}
  */

/** @defgroup DCMIPP_Crop_Area  DCMIPP Crop Area
  * @{
  */
#define DCMIPP_POSITIVE_AREA  0U                    /*!< Positive Area chosen for crop */
#define DCMIPP_NEGATIVE_AREA  DCMIPP_P0SCSZR_POSNEG /*!< Negative Area chosen for crop */
/**
  * @}
  */



/** @defgroup DCMIPP_Format  DCMIPP Format
  * @{
  */
#define  DCMIPP_FORMAT_BYTE             0U                               /*!< DCMIPP Format BYTE    */
#define  DCMIPP_FORMAT_YUV422          (0x1EU << DCMIPP_PRCR_FORMAT_Pos) /*!< DCMIPP Format YUV422  */
#define  DCMIPP_FORMAT_RGB565          (0x22U << DCMIPP_PRCR_FORMAT_Pos) /*!< DCMIPP Format RGB565  */
#define  DCMIPP_FORMAT_RGB666          (0x23U << DCMIPP_PRCR_FORMAT_Pos) /*!< DCMIPP Format RGB666  */
#define  DCMIPP_FORMAT_RGB888          (0x24U << DCMIPP_PRCR_FORMAT_Pos) /*!< DCMIPP Format RGB888  */
#define  DCMIPP_FORMAT_RAW8            (0x2AU << DCMIPP_PRCR_FORMAT_Pos) /*!< DCMIPP Format RAW8    */
#define  DCMIPP_FORMAT_RAW10           (0x2BU << DCMIPP_PRCR_FORMAT_Pos) /*!< DCMIPP Format RAW10   */
#define  DCMIPP_FORMAT_RAW12           (0x2CU << DCMIPP_PRCR_FORMAT_Pos) /*!< DCMIPP Format RAW12   */
#define  DCMIPP_FORMAT_RAW14           (0x2DU << DCMIPP_PRCR_FORMAT_Pos) /*!< DCMIPP Format RAW14   */
#define  DCMIPP_FORMAT_MONOCHROME_8B   (0x4AU << DCMIPP_PRCR_FORMAT_Pos) /*!< DCMIPP Format 8-bits  */
#define  DCMIPP_FORMAT_MONOCHROME_10B  (0x4BU << DCMIPP_PRCR_FORMAT_Pos) /*!< DCMIPP Format 10-bits */
#define  DCMIPP_FORMAT_MONOCHROME_12B  (0x4CU << DCMIPP_PRCR_FORMAT_Pos) /*!< DCMIPP Format 12-bits */
#define  DCMIPP_FORMAT_MONOCHROME_14B  (0x4DU << DCMIPP_PRCR_FORMAT_Pos) /*!< DCMIPP Format 14-bits */
/**
  * @}
  */

/** @defgroup DCMIPP_Extended_Data_Mode  DCMIPP Extended Data Mode
  * @{
  */
#define  DCMIPP_INTERFACE_8BITS   0U                         /*!< Interface captures 8bits on every pixel clock  */
#define  DCMIPP_INTERFACE_10BITS (1U << DCMIPP_PRCR_EDM_Pos) /*!< Interface captures 10bits on every pixel clock */
#define  DCMIPP_INTERFACE_12BITS (2U << DCMIPP_PRCR_EDM_Pos) /*!< Interface captures 12bits on every pixel clock */
#define  DCMIPP_INTERFACE_14BITS (3U << DCMIPP_PRCR_EDM_Pos) /*!< Interface captures 14bits on every pixel clock */
#define  DCMIPP_INTERFACE_16BITS (4U << DCMIPP_PRCR_EDM_Pos) /*!< Interface captures 16bits on every pixel clock */
/**
  * @}
  */

/** @defgroup DCMIPP_HSYNC_Polarity DCMIPP HSYNC Polarity
  * @{
  */
#define DCMIPP_HSPOLARITY_LOW       0U                 /*!< Horizontal synchronization active Low  */
#define DCMIPP_HSPOLARITY_HIGH      DCMIPP_PRCR_HSPOL  /*!< Horizontal synchronization active High */
/**
  * @}
  */
/** @defgroup DCMIPP_VSYNC_Polarity DCMIPP VSYNC Polarity
  * @{
  */
#define DCMIPP_VSPOLARITY_LOW       0U                 /*!< Vertical synchronization active Low  */
#define DCMIPP_VSPOLARITY_HIGH      DCMIPP_PRCR_VSPOL  /*!< Vertical synchronization active High */
/**
  * @}
  */
/** @defgroup DCMIPP_PIXCK_Polarity DCMIPP PIXCK Polarity
  * @{
  */
#define DCMIPP_PCKPOLARITY_FALLING  0U                  /*!< Pixel clock active on Falling edge */
#define DCMIPP_PCKPOLARITY_RISING   DCMIPP_PRCR_PCKPOL  /*!< Pixel clock active on Rising edge  */
/**
  * @}
  */

/** @defgroup DCMIPP_Synchronization_Mode DCMIPP Synchronization Mode
  * @{
  */
#define DCMIPP_SYNCHRO_HARDWARE     0U                          /*!< Hardware Synchronization */
#define DCMIPP_SYNCHRO_EMBEDDED    DCMIPP_PRCR_ESS              /*!< Embedded Synchronization */
/**
  * @}
  */

/** @defgroup DCMIPP_SWAP_CYCLES  DCMIPP Swap Cycles
  * @{
  */
#define DCMIPP_SWAPCYCLES_DISABLE  0U                       /*!< swap data from cycle 0 vs cycle 1 */
#define DCMIPP_SWAPCYCLES_ENABLE   (DCMIPP_PRCR_SWAPCYCLES) /*!< swap data from cycle 0 vs cycle 1 */
/**
  * @}
  */

/** @defgroup DCMIPP_SWAP_BITS  DCMIPP Swap Bits
  * @{
  */
#define DCMIPP_SWAPBITS_DISABLE  0U                     /*!< swap lsb vs msb within each received component */
#define DCMIPP_SWAPBITS_ENABLE   (DCMIPP_PRCR_SWAPBITS) /*!< swap lsb vs msb within each received component */
/**
  * @}
  */

/** @defgroup DCMIPP_Pipe_Line_Decimation DCMIPP Pipe Line Decimation
  * @{
  */
/** @defgroup DCMIPP_Line_Select_Mode DCMIPP Line Select Mode
  * @{
  */
#define DCMIPP_LSM_ALL          0U                              /*!< Interface captures all received lines */
#define DCMIPP_LSM_ALTERNATE_2 (1U << DCMIPP_P0PPCR_LSM_Pos )   /*!< Interface captures one line out of two */
/**
  * @}
  */
/** @defgroup DCMIPP_Line_Start_Mode DCMIPP Line Start Mode
  * @{
  */
#define DCMIPP_OELS_ODD         0U                              /*!< Interface captures first line from the frame start,
                                                                     second one is dropped */
#define DCMIPP_OELS_EVEN       (1U << DCMIPP_P0PPCR_OELS_Pos)   /*!< Interface captures second line from the frame
                                                                     start, first one is dropped */
/**
  * @}
  */
/**
  * @}
  */

/** @defgroup DCMIPP_Pipe_Byte_Decimation DCMIPP Pipe Byte Decimation
  * @{
  */
/** @defgroup DCMIPP_Byte_Select_Mode DCMIPP Byte Select Mode
  * @{
  */
#define DCMIPP_BSM_ALL          0U                              /*!< Interface captures all received data */
#define DCMIPP_BSM_DATA_OUT_2  (1U << DCMIPP_P0PPCR_BSM_Pos)    /*!< Interface captures 1 data out of 2   */
#define DCMIPP_BSM_BYTE_OUT_4  (2U << DCMIPP_P0PPCR_BSM_Pos)    /*!< Interface captures 1 byte out of 4   */
#define DCMIPP_BSM_2BYTE_OUT_4 (3U << DCMIPP_P0PPCR_BSM_Pos)    /*!< Interface captures 2 byte out of 4   */
/**
  * @}
  */
/** @defgroup DCMIPP_Byte_Start_Mode DCMIPP Byte Start Mode
  * @{
  */
#define DCMIPP_OEBS_ODD        0U                              /*!< Interface captures first data (byte or double byte)
                                                                   from the frame/line start,second one being dropped */
#define DCMIPP_OEBS_EVEN      (1U << DCMIPP_P0PPCR_OEBS_Pos)   /*!< Interface captures second data (byte or double byte)
                                                                    from the frame/line start, first one is dropped   */
/**
  * @}
  */
/**
  * @}
  */

/** @defgroup DCMIPP_Memory DCMIPP Memory
  * @{
  */
#define DCMIPP_MEMORY_ADDRESS_0 0U   /*!< Base destination address   */
#define DCMIPP_MEMORY_ADDRESS_1 1U   /*!< Second destination address */
/**
  * @}
  */
/** @defgroup DCMIPP_LineMult DCMIPP Line Mult
  * @{
  */
#define  DCMIPP_MULTILINE_1_LINE      0U                                  /*!< Event after every 1   line   */
#define  DCMIPP_MULTILINE_2_LINES    (1U << DCMIPP_P0PPCR_LINEMULT_Pos)   /*!< Event after every 2   lines  */
#define  DCMIPP_MULTILINE_4_LINES    (2U << DCMIPP_P0PPCR_LINEMULT_Pos)   /*!< Event after every 4   lines  */
#define  DCMIPP_MULTILINE_8_LINES    (3U << DCMIPP_P0PPCR_LINEMULT_Pos)   /*!< Event after every 8   lines  */
#define  DCMIPP_MULTILINE_16_LINES   (4U << DCMIPP_P0PPCR_LINEMULT_Pos)   /*!< Event after every 16  lines  */
#define  DCMIPP_MULTILINE_32_LINES   (5U << DCMIPP_P0PPCR_LINEMULT_Pos)   /*!< Event after every 32  lines  */
#define  DCMIPP_MULTILINE_64_LINES   (6U << DCMIPP_P0PPCR_LINEMULT_Pos)   /*!< Event after every 64  lines  */
#define  DCMIPP_MULTILINE_128_LINES  (7U << DCMIPP_P0PPCR_LINEMULT_Pos)   /*!< Event after every 128 lines  */
/**
  * @}
  */
/** @defgroup DCMIPP_Interrupt_Sources  DCMIPP Interrupt sources
  * @{
  */
#define DCMIPP_IT_AXI_TRANSFER_ERROR  DCMIPP_CMIER_ATXERRIE  /*!< IPPLUG AXI Transfer error interrupt        */
#define DCMIPP_IT_PARALLEL_SYNC_ERROR DCMIPP_CMIER_PRERRIE   /*!< Sync error interrupt on parallel interface */
#define DCMIPP_IT_PIPE0_FRAME         DCMIPP_CMIER_P0FRAMEIE /*!< Frame capture interrupt complete for pipe0 */
#define DCMIPP_IT_PIPE0_VSYNC         DCMIPP_CMIER_P0VSYNCIE /*!< Vertical sync interrupt for pipe0          */
#define DCMIPP_IT_PIPE0_LINE          DCMIPP_CMIER_P0LINEIE  /*!< Multiline interrupt for pipe0              */
#define DCMIPP_IT_PIPE0_LIMIT         DCMIPP_CMIER_P0LIMITIE /*!< Limit interrupt for pipe0                  */
#define DCMIPP_IT_PIPE0_OVR           DCMIPP_CMIER_P0OVRIE   /*!< Overrun interrupt for pipe0                */
/**
  * @}
  */

/** @defgroup DCMIPP_Interrupt_Flags  DCMIPP Interrupt Flags
  * @{
  */
#define DCMIPP_FLAG_AXI_TRANSFER_ERROR  DCMIPP_CMSR2_ATXERRF /*!< IPPLUG AXI Transfer error interrupt flag            */
#define DCMIPP_FLAG_PARALLEL_SYNC_ERROR DCMIPP_CMSR2_PRERRF  /*!< Synchronization error interrupt on parallel interface
                                                                  flag */
#define DCMIPP_FLAG_PIPE0_FRAME       DCMIPP_CMSR2_P0FRAMEF  /*!< Frame capture interrupt complete for pipe0 flag     */
#define DCMIPP_FLAG_PIPE0_VSYNC       DCMIPP_CMSR2_P0VSYNCF  /*!< Vertical synch interrupt for pipe0 flag             */
#define DCMIPP_FLAG_PIPE0_LINE        DCMIPP_CMSR2_P0LINEF   /*!< Multiline interrupt for pipe0 flag                  */
#define DCMIPP_FLAG_PIPE0_LIMIT       DCMIPP_CMSR2_P0LIMITF  /*!< Limit interrupt for pipe0 flag                      */
#define DCMIPP_FLAG_PIPE0_OVR         DCMIPP_CMSR2_P0OVRF    /*!< Overrun interrupt for pipe0 flag                    */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup DCMIPP_Exported_Macros DCMIPP Exported Macros
  * @brief    DCMIPP Exported Macros
  * @{
  */
/**
  * @brief  Enable the specified DCMIPP interrupts.
  * @param  __HANDLE__    DCMIPP handle
  * @param  __INTERRUPT__ specifies the DCMIPP interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg DCMIPP_IT_AXI_TRANSFER_ERR IPPLUG AXI Transfer error interrupt
  *            @arg DCMIPP_IT_PARALLEL_SYNC_ERR Synchronization error interrupt on parallel interface
  *            @arg DCMIPP_IT_PIPE0_FRAME Frame capture complete interrupt for the pipe0
  *            @arg DCMIPP_IT_PIPE0_VSYNC Vertical sync interrupt for the pipe0
  *            @arg DCMIPP_IT_PIPE0_LINE Multi-line capture complete interrupt for the pipe0
  *            @arg DCMIPP_IT_PIPE0_LIMIT Limit interrupt for the pipe0
  *            @arg DCMIPP_IT_PIPE0_OVR Overrun interrupt for the pipe0
  * @retval None
  */
#define __HAL_DCMIPP_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->CMIER |= (__INTERRUPT__))

/**
  * @brief  Disable the specified DCMIPP interrupts.
  * @param  __HANDLE__    DCMIPP handle
  * @param  __INTERRUPT__ specifies the DCMIPP interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg DCMIPP_IT_AXI_TRANSFER_ERR IPPLUG AXI Transfer error interrupt
  *            @arg DCMIPP_IT_PARALLEL_SYNC_ERR Synchronization error interrupt on parallel interface
  *            @arg DCMIPP_IT_PIPE0_FRAME Frame capture complete interrupt for the pipe0
  *            @arg DCMIPP_IT_PIPE0_VSYNC Vertical sync interrupt for the pipe0
  *            @arg DCMIPP_IT_PIPE0_LINE Multi-line capture complete interrupt for the pipe0
  *            @arg DCMIPP_IT_PIPE0_LIMIT Limit interrupt for the pipe0
  *            @arg DCMIPP_IT_PIPE0_OVR Overrun interrupt for the pipe0
  * @retval None
  */
#define __HAL_DCMIPP_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->CMIER &= ~(__INTERRUPT__))

/**
  * @brief  Get the DCMIPP pending interrupt flags.
  * @param  __HANDLE__ DCMIPP handle
  * @param  __FLAG__   Get the specified flag.
  *         This parameter can be any combination of the following values:
  *            @arg DCMIPP_FLAG_AXI_TRANSFER_ERR IPPLUG AXI Transfer error interrupt flag
  *            @arg DCMIPP_FLAG_PARALLEL_SYNC_ERR Synchronization error interrupt flag on parallel interface
  *            @arg DCMIPP_FLAG_PIPE0_FRAME Frame capture complete interrupt flag for the pipe0
  *            @arg DCMIPP_FLAG_PIPE0_VSYNC Vertical sync interrupt flag for the pipe0
  *            @arg DCMIPP_FLAG_PIPE0_LINE Multi-line capture complete interrupt flag for the pipe0
  *            @arg DCMIPP_FLAG_PIPE0_LIMIT Limit interrupt flag for the pipe0
  *            @arg DCMIPP_FLAG_PIPE0_OVR Overrun interrupt flag for the pipe0
  * @retval The state of FLAG (SET or RESET).
  */
#define __HAL_DCMIPP_GET_FLAG(__HANDLE__, __FLAG__)  ((__HANDLE__)->Instance->CMSR2 & (__FLAG__))

/**
  * @brief  Clear the DCMIPP pending interrupt flags.
  * @param  __HANDLE__ DCMIPP handle
  * @param  __FLAG__   specifies the flag to clear.
  *         This parameter can be any combination of the following values:
  *            @arg DCMIPP_FLAG_AXI_TRANSFER_ERR IPPLUG AXI Transfer error interrupt
  *            @arg DCMIPP_FLAG_PARALLEL_SYNC_ERR Synchronization error interrupt on parallel interface
  *            @arg DCMIPP_FLAG_PIPE0_FRAME Frame capture complete interrupt for the pipe0
  *            @arg DCMIPP_FLAG_PIPE0_VSYNC Vertical sync interrupt for the pipe0
  *            @arg DCMIPP_FLAG_PIPE0_LINE Multi-line capture complete interrupt for the pipe0
  *            @arg DCMIPP_FLAG_PIPE0_LIMIT Limit interrupt for the pipe0
  *            @arg DCMIPP_FLAG_PIPE0_OVR Overrun interrupt for the pipe0
  * @retval None
  */
#define __HAL_DCMIPP_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->CMFCR = (__FLAG__))

/**
  * @brief  Checks whether the specified DCMIPP interrupt is enabled or not.
  * @param  __HANDLE__    DCMIPP handle
  * @param  __INTERRUPT__ specifies the DCMIPP interrupt sources to be checked.
  *         This parameter can be any combination of the following values:
  *            @arg DCMIPP_IT_AXI_TRANSFER_ERR IPPLUG AXI Transfer error interrupt
  *            @arg DCMIPP_IT_PARALLEL_SYNC_ERR Synchronization error interrupt on parallel interface
  *            @arg DCMIPP_IT_PIPE0_FRAME Frame capture complete interrupt for the pipe0
  *            @arg DCMIPP_IT_PIPE0_VSYNC Vertical sync interrupt for the pipe0
  *            @arg DCMIPP_IT_PIPE0_LINE Multi-line capture complete interrupt for the pipe0
  *            @arg DCMIPP_IT_PIPE0_LIMIT Limit interrupt for the pipe0
  *            @arg DCMIPP_IT_PIPE0_OVR Overrun interrupt for the pipe0
  * @retval The state of DCMIPP interrupt (SET or RESET).
  */
#define __HAL_DCMIPP_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->CMIER & \
                                                                 (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup DCMIPP_Exported_Functions
  * @{
  */

/** @addtogroup DCMIPP_Initialization_De-Initialization_Functions DCMIPP Initialization De-Initialization Functions
  * @brief      Initialization and De-Initialization Functions
  * @{
  */
HAL_StatusTypeDef HAL_DCMIPP_Init(DCMIPP_HandleTypeDef *hdcmipp);
HAL_StatusTypeDef HAL_DCMIPP_DeInit(DCMIPP_HandleTypeDef *hdcmipp);
void HAL_DCMIPP_MspInit(DCMIPP_HandleTypeDef *hdcmipp);
void HAL_DCMIPP_MspDeInit(DCMIPP_HandleTypeDef *hdcmipp);
/**
  * @}
  */

/** @defgroup DCMIPP_Configuration_Functions DCMIPP Configuration Functions
  * @brief    Configuration Functions
  * @{
  */

HAL_StatusTypeDef HAL_DCMIPP_PARALLEL_SetConfig(DCMIPP_HandleTypeDef *hdcmipp,
                                                const DCMIPP_ParallelConfTypeDef *pParallelConfig);

HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                            const DCMIPP_PipeConfTypeDef *pPipeConfig);
HAL_StatusTypeDef HAL_DCMIPP_SetIPPlugConfig(DCMIPP_HandleTypeDef *hdcmipp,
                                             const DCMIPP_IPPlugConfTypeDef *pIPPlugConfig);
/**
  * @}
  */

/** @addtogroup DCMIPP_IO_operation_Functions DCMIPP IO operation Functions
  * @brief      IO Operation Functions
  * @{
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_Start(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t DstAddress,
                                        uint32_t CaptureMode);
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DoubleBufferStart(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t DstAddress0,
                                                    uint32_t DstAddress1, uint32_t CaptureMode);
HAL_StatusTypeDef HAL_DCMIPP_PIPE_Stop(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
HAL_StatusTypeDef HAL_DCMIPP_PIPE_Suspend(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
HAL_StatusTypeDef HAL_DCMIPP_PIPE_Resume(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);

/**
  * @}
  */

/** @addtogroup DCMIPP_IRQ_and_Callbacks_Functions DCMIPP IRQ and Callbacks Functions
  * @brief      IRQ and Callbacks functions
  * @{
  */
/** @addtogroup DCMIPP_IRQHandler_Functions IRQHandler Functions
  * @{
  */
void HAL_DCMIPP_IRQHandler(DCMIPP_HandleTypeDef *hdcmipp);
/**
  * @}
  */
/** @addtogroup DCMIPP_Callback_Functions Callback Functions
  * @{
  */
void HAL_DCMIPP_PIPE_FrameEventCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
void HAL_DCMIPP_PIPE_VsyncEventCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
void HAL_DCMIPP_PIPE_LineEventCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
void HAL_DCMIPP_PIPE_LimitEventCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
void HAL_DCMIPP_PIPE_ErrorCallback(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
void HAL_DCMIPP_ErrorCallback(DCMIPP_HandleTypeDef *hdcmipp);
/**
  * @}
  */

/** @addtogroup DCMIPP_RegisterCallback_Functions Register Callback Functions
  * @{
  */
/* Callbacks Register/UnRegister functions  ***********************************/
#if (USE_HAL_DCMIPP_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_DCMIPP_RegisterCallback(DCMIPP_HandleTypeDef *hdcmipp, HAL_DCMIPP_CallbackIDTypeDef CallbackID,
                                              pDCMIPP_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_DCMIPP_UnRegisterCallback(DCMIPP_HandleTypeDef *hdcmipp,
                                                HAL_DCMIPP_CallbackIDTypeDef CallbackID);

HAL_StatusTypeDef HAL_DCMIPP_PIPE_RegisterCallback(DCMIPP_HandleTypeDef *hdcmipp,
                                                   HAL_DCMIPP_PIPE_CallbackIDTypeDef CallbackID,
                                                   pDCMIPP_PIPE_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_DCMIPP_PIPE_UnRegisterCallback(DCMIPP_HandleTypeDef *hdcmipp,
                                                     HAL_DCMIPP_PIPE_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_DCMIPP_REGISTER_CALLBACKS */
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup DCMIPP_Decimation_Functions DCMIPP Decimation Functions
  * @{
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetBytesDecimationConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                           uint32_t SelectStart, uint32_t SelectMode);
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetLinesDecimationConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                           uint32_t SelectStart, uint32_t SelectMode);
/**
  * @}
  */
/** @defgroup DCMIPP_Crop_Functions DCMIPP Crop Functions
  * @{
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetCropConfig(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                const DCMIPP_CropConfTypeDef *pCropConfig);
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableCrop(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableCrop(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
/**
  * @}
  */
/** @defgroup DCMIPP_Line_Event_Functions DCMIPP Line Event Functions
  * @{
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableLineEvent(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t Line);
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableLineEvent(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
/**
  * @}
  */
/** @defgroup DCMIPP_LimitEvent_Functions DCMIPP Limit Event Functions
  * @{
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableLimitEvent(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t Limit);
HAL_StatusTypeDef HAL_DCMIPP_PIPE_DisableLimitEvent(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
/**
  * @}
  */

/** @defgroup DCMIPP_PeripheralControl_Functions DCMIPP Peripheral Control Functions
  * @{
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetFrameRate(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t FrameRate);
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetCaptureMode(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t CaptureMode);
HAL_StatusTypeDef HAL_DCMIPP_PIPE_EnableCapture(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
HAL_StatusTypeDef HAL_DCMIPP_PIPE_SetMemoryAddress(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe, uint32_t Memory,
                                                   uint32_t DstAddress);
HAL_StatusTypeDef HAL_DCMIPP_PIPE_PARALLEL_SetInputPixelFormat(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                               uint32_t InputPixelFormat);
HAL_StatusTypeDef HAL_DCMIPP_PARALLEL_SetSyncUnmask(DCMIPP_HandleTypeDef *hdcmipp,
                                                    const DCMIPP_EmbeddedSyncUnmaskTypeDef *SyncUnmask);
/**
  * @}
  */

/** @defgroup DCMIPP_Frame_Counter_Functions DCMIPP Frame Counter Functions
  * @{
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_ResetFrameCounter(DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
HAL_StatusTypeDef HAL_DCMIPP_PIPE_ReadFrameCounter(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                   uint32_t *pCounter);
/**
  * @}
  */
/** @defgroup DCMIPP_Data_Counter_Functions DCMIPP Data Counter Functions
  * @{
  */
HAL_StatusTypeDef HAL_DCMIPP_PIPE_GetDataCounter(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe,
                                                 uint32_t *pCounter);
/**
  * @}
  */

/** @addtogroup DCMIPP_State_and_Error_Functions DCMIPP State and Error Functions
  * @{
  */
HAL_DCMIPP_StateTypeDef HAL_DCMIPP_GetState(const DCMIPP_HandleTypeDef *hdcmipp);
HAL_DCMIPP_PipeStateTypeDef HAL_DCMIPP_PIPE_GetState(const DCMIPP_HandleTypeDef *hdcmipp, uint32_t Pipe);
uint32_t HAL_DCMIPP_GetError(const DCMIPP_HandleTypeDef *hdcmipp);

/**
  * @}
  */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup DCMIPP_Private_Macros DCMIPP Private Macros
  * @{
  */
#define IS_DCMIPP_PIPE(PIPE) ((PIPE) == DCMIPP_PIPE0)
#define IS_DCMIPP_FORMAT(FORMAT) (((FORMAT) == DCMIPP_FORMAT_BYTE)   ||\
                                  ((FORMAT) == DCMIPP_FORMAT_YUV422) ||\
                                  ((FORMAT) == DCMIPP_FORMAT_RGB565) ||\
                                  ((FORMAT) == DCMIPP_FORMAT_RGB666) ||\
                                  ((FORMAT) == DCMIPP_FORMAT_RGB888) ||\
                                  ((FORMAT) == DCMIPP_FORMAT_RAW8  ) ||\
                                  ((FORMAT) == DCMIPP_FORMAT_RAW10 ) ||\
                                  ((FORMAT) == DCMIPP_FORMAT_RAW12 ) ||\
                                  ((FORMAT) == DCMIPP_FORMAT_RAW14 ) ||\
                                  ((FORMAT) == DCMIPP_FORMAT_MONOCHROME_8B)  ||\
                                  ((FORMAT) == DCMIPP_FORMAT_MONOCHROME_10B) ||\
                                  ((FORMAT) == DCMIPP_FORMAT_MONOCHROME_12B) ||\
                                  ((FORMAT) == DCMIPP_FORMAT_MONOCHROME_14B))


#define IS_DCMIPP_PCKPOLARITY(POLARITY)(((POLARITY) == DCMIPP_PCKPOLARITY_FALLING) || \
                                        ((POLARITY) == DCMIPP_PCKPOLARITY_RISING))

#define IS_DCMIPP_VSPOLARITY(POLARITY)(((POLARITY) == DCMIPP_VSPOLARITY_LOW) || \
                                       ((POLARITY) == DCMIPP_VSPOLARITY_HIGH))

#define IS_DCMIPP_HSPOLARITY(POLARITY)(((POLARITY) == DCMIPP_HSPOLARITY_LOW) || \
                                       ((POLARITY) == DCMIPP_HSPOLARITY_HIGH))


#define IS_DCMIPP_EXTENDED_DATA_MODE(INTERFACE)(((INTERFACE) == DCMIPP_INTERFACE_8BITS ) ||\
                                                ((INTERFACE) == DCMIPP_INTERFACE_10BITS) ||\
                                                ((INTERFACE) == DCMIPP_INTERFACE_12BITS) ||\
                                                ((INTERFACE) == DCMIPP_INTERFACE_14BITS) ||\
                                                ((INTERFACE) == DCMIPP_INTERFACE_16BITS))


#define IS_DCMIPP_SYNC_MODE(SYNC_MODE) (((SYNC_MODE) == DCMIPP_SYNCHRO_HARDWARE) ||\
                                        ((SYNC_MODE) == DCMIPP_SYNCHRO_EMBEDDED))

#define IS_DCMIPP_SWAP_BITS(SWAP_BITS)  (((SWAP_BITS) == DCMIPP_SWAPBITS_ENABLE) ||\
                                         ((SWAP_BITS) == DCMIPP_SWAPBITS_DISABLE))

#define IS_DCMIPP_SWAP_CYCLES(SWAP_CYCLES) (((SWAP_CYCLES) == DCMIPP_SWAPCYCLES_ENABLE) ||\
                                            ((SWAP_CYCLES) == DCMIPP_SWAPCYCLES_DISABLE))



#define IS_DCMIPP_FRAME_RATE(FRAME_RATE) (((FRAME_RATE) == DCMIPP_FRAME_RATE_ALL)      ||\
                                          ((FRAME_RATE) == DCMIPP_FRAME_RATE_1_OVER_2) ||\
                                          ((FRAME_RATE) == DCMIPP_FRAME_RATE_1_OVER_4) ||\
                                          ((FRAME_RATE) == DCMIPP_FRAME_RATE_1_OVER_8))


#define IS_DCMIPP_CLIENT(CLIENT) (((CLIENT) == DCMIPP_CLIENT1))

#define IS_DCMIPP_DPREG_END(DPREG_END) ((DPREG_END) <= 0x1FU)
#define IS_DCMIPP_DPREG_START(DPREG_START) ((DPREG_START) <= 0x1FU)

#define IS_DCMIPP_MAX_OUTSTANDING_TRANSACTIONS(OUTS_TRANS) (((OUTS_TRANS) == DCMIPP_OUTSTANDING_TRANSACTION_NONE )||\
                                                            ((OUTS_TRANS) == DCMIPP_OUTSTANDING_TRANSACTION_2    )||\
                                                            ((OUTS_TRANS) == DCMIPP_OUTSTANDING_TRANSACTION_3    )||\
                                                            ((OUTS_TRANS) == DCMIPP_OUTSTANDING_TRANSACTION_4    ))
#define IS_DCMIPP_MEMORY_PAGE_SIZE(MEMORY_PAGE_SIZE) (((MEMORY_PAGE_SIZE) ==  DCMIPP_MEMORY_PAGE_SIZE_64BYTES)  ||\
                                                      ((MEMORY_PAGE_SIZE) ==  DCMIPP_MEMORY_PAGE_SIZE_128BYTES) ||\
                                                      ((MEMORY_PAGE_SIZE) ==  DCMIPP_MEMORY_PAGE_SIZE_256BYTES) ||\
                                                      ((MEMORY_PAGE_SIZE) ==  DCMIPP_MEMORY_PAGE_SIZE_512BYTES) ||\
                                                      ((MEMORY_PAGE_SIZE) ==  DCMIPP_MEMORY_PAGE_SIZE_1KBYTES)  ||\
                                                      ((MEMORY_PAGE_SIZE) ==  DCMIPP_MEMORY_PAGE_SIZE_2KBYTES)  ||\
                                                      ((MEMORY_PAGE_SIZE) ==  DCMIPP_MEMORY_PAGE_SIZE_4KBYTES)  ||\
                                                      ((MEMORY_PAGE_SIZE) ==  DCMIPP_MEMORY_PAGE_SIZE_8KBYTES))
#define IS_DCMIPP_TRAFFIC(TRAFFIC) (((TRAFFIC) == DCMIPP_TRAFFIC_BURST_SIZE_8BYTES ) ||\
                                    ((TRAFFIC) == DCMIPP_TRAFFIC_BURST_SIZE_16BYTES) ||\
                                    ((TRAFFIC) == DCMIPP_TRAFFIC_BURST_SIZE_32BYTES) ||\
                                    ((TRAFFIC) == DCMIPP_TRAFFIC_BURST_SIZE_64BYTES) ||\
                                    ((TRAFFIC) == DCMIPP_TRAFFIC_BURST_SIZE_128BYTES))
#define IS_DCMIPP_WLRU_RATIO(WLRU_RATIO) ((WLRU_RATIO)<= 0xFU)

#define IS_DCMIPP_CAPTURE_MODE(CAPTURE_MODE) (((CAPTURE_MODE) == DCMIPP_MODE_CONTINUOUS)||\
                                              ((CAPTURE_MODE) == DCMIPP_MODE_SNAPSHOT))

#define IS_DCMIPP_PIPE_CROP_AREA(CROP_AREA)(((CROP_AREA) == DCMIPP_POSITIVE_AREA) ||\
                                            ((CROP_AREA) == DCMIPP_NEGATIVE_AREA))

#define IS_DCMIPP_PIPE_CROP_HSIZE(CROP_HSIZE) (((CROP_HSIZE) >= 0x1U) && ((CROP_HSIZE) <= 0xFFFU))
#define IS_DCMIPP_PIPE_CROP_VSIZE(CROP_VSIZE) (((CROP_VSIZE) >= 0x1U) && ((CROP_VSIZE) <= 0xFFFU))
#define IS_DCMIPP_PIPE_CROP_VSTART(CROP_VSTART) ((CROP_VSTART) <= 0xFFFU)
#define IS_DCMIPP_PIPE_CROP_HSTART(CROP_HSTART) ((CROP_HSTART) <= 0xFFFU)

#define IS_DCMIPP_BYTE_SELECT_MODE(BYTE_SELECT) (((BYTE_SELECT) == DCMIPP_BSM_ALL)        ||\
                                                 ((BYTE_SELECT) == DCMIPP_BSM_DATA_OUT_2) ||\
                                                 ((BYTE_SELECT) == DCMIPP_BSM_BYTE_OUT_4) ||\
                                                 ((BYTE_SELECT) == DCMIPP_BSM_2BYTE_OUT_4))

#define IS_DCMIPP_BYTE_SELECT_START(BYTE_START)(((BYTE_START) == DCMIPP_OEBS_ODD) ||\
                                                ((BYTE_START) == DCMIPP_OEBS_EVEN))

#define IS_DCMIPP_LINE_SELECT_MODE(LINE_SELECT) (((LINE_SELECT) == DCMIPP_LSM_ALL) ||\
                                                 ((LINE_SELECT) == DCMIPP_LSM_ALTERNATE_2))

#define IS_DCMIPP_LINE_SELECT_START(LINE__START)(((LINE__START) == DCMIPP_OELS_ODD) ||\
                                                 ((LINE__START) == DCMIPP_OELS_EVEN))


#define IS_DCMIPP_MEMORY_ADDRESS(MEMORY_ADDRESS) (((MEMORY_ADDRESS) == DCMIPP_MEMORY_ADDRESS_0) ||\
                                                  ((MEMORY_ADDRESS) == DCMIPP_MEMORY_ADDRESS_1))

#define IS_DCMIPP_DATA_LIMIT(DATA_LIMIT) (((DATA_LIMIT) >=1U ) && ((DATA_LIMIT) <= 0xFFFFFFU))


#define IS_DCMIPP_PIPE_MULTILINE(MULTILINE) (((MULTILINE) == DCMIPP_MULTILINE_1_LINE )   ||\
                                             ((MULTILINE) == DCMIPP_MULTILINE_2_LINES)  ||\
                                             ((MULTILINE) == DCMIPP_MULTILINE_4_LINES)  ||\
                                             ((MULTILINE) == DCMIPP_MULTILINE_8_LINES)  ||\
                                             ((MULTILINE) == DCMIPP_MULTILINE_16_LINES) ||\
                                             ((MULTILINE) == DCMIPP_MULTILINE_32_LINES) ||\
                                             ((MULTILINE) == DCMIPP_MULTILINE_64_LINES) ||\
                                             ((MULTILINE) == DCMIPP_MULTILINE_128_LINES))

/**
  * @}
  */

/**
  * @}
  */

#endif /* DCMIPP */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32H7RSxx_HAL_DCMIPP_H */

