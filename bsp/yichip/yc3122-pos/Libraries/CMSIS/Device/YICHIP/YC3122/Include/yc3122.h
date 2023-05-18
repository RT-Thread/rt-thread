/******************************************************************************
 * @file     yc3122.h
 * @brief    CMSIS Cortex-M0 Core Peripheral Access Layer Header File for
 *           YC3122
 * @version  V1.00
 * @date     15. July 2021
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2012 ARM LIMITED

    All rights reserved.
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    - Redistributions of source code must retain the above copyright
        notice, this list ofC conditions and the following disclaimer.
    - Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
    - Neither the name of ARM nor the names of its contributors may be used
        to endorse or promote products derived from this software without
        specific prior written permission.
    *
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
    ---------------------------------------------------------------------------*/

/** @addtogroup
  * @{
  */

/** @addtogroup YC3122
  * @{
  */

#ifndef __YC3122_H__
#define __YC3122_H__

#ifdef __cplusplus
extern "C" {
#endif


  /** @addtogroup Configuration_of_CMSIS
   * @{
   */



/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */
typedef enum IRQn
{
    /******  Cortex-M# Processor Exceptions Numbers ***************************************************/
    Reset_IRQn                = -15,              /*!< -15  Reset Vector, invoked on Power up and warm reset                     */
    NonMaskableInt_IRQn       = -14,              /*!< -14  Non maskable Interrupt, cannot be stopped or preempted               */
    HardFault_IRQn            = -13,              /*!< -13  Hard Fault, all classes of Fault                                     */
    SVCall_IRQn               =  -5,              /*!< -5 System Service Call via SVC instruction                                */
    PendSV_IRQn               =  -2,              /*!< -2 Pendable request for system service                                    */
    SysTick_IRQn              =  -1,              /*!< -1 System Tick Timer                                                      */
    /******  Device Specific Interrupt Numbers ********************************************************/
    USB_IRQn                  = 0,
    I2C0_IRQn                 = 1,
    I2C1_IRQn                 = 2,
    QSPI_IRQn                 = 3,
    SPI0_IRQn                 = 4,
    SPI1_IRQn                 = 5,
    HSPI_IRQn                 = 6,
    SEC_IRQn                  = 7,
    UART0_IRQn                = 8,
    UART1_IRQn                = 9,
    UART2_IRQn                = 10,
    UART3_IRQn                = 11,
    MEMCP_IRQn                = 12,
    SCI0_IRQn                 = 13,
    SCI1_IRQn                 = 14,
    MSR_IRQn                  = 15,
    GPIO_IRQn                 = 16,
    TMRG0_IRQn                = 17,
    TMRG1_IRQn                = 18,
    SDIO_IRQn                 = 19,
    PSARM_IRQn                = 20,
    RSA_IRQn                  = 21,
    SM4_IRQn                  = 22,
    TRNG_IRQn                 = 23,
    WDT_IRQn                  = 24,
    DCMI_IRQn                 = 25,
    ADC_IRQn                  = 26,
    RTC_IRQn                  = 27,
    RSVD1_IRQn                = 28,
    POWER_IRQn                = 29,
    SOFTWARE_IRQn             = 30,
    RISCV_IRQn                = 31
} IRQn_Type;

/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M# Processor and Core Peripherals */
#define __CM0_REV                 0x0000U    /*!< Core Revision r0p0                             */
#define __NVIC_PRIO_BITS          2U         /*!< Number of 2 Bits used for Priority Levels      */
#define __Vendor_SysTickConfig    0U         /*!< Set to 1 if different SysTick Config is used   */

/*@}*/ /* end of group <Device>_CMSIS */

#if defined(__USE_YC_M0__)
#include "core_cm0.h"                       /* Cortex-M# processor and core peripherals          */
#elif defined(__USE_YC_RISC_V__)
#include "core_rv_31xx.h"
#endif

#include "system_yc3122.h"                  /* <Device> System  include file                     */


#ifndef __IM                                    /*!< Fallback for older CMSIS versions                                         */
#define __IM   __I
#endif
#ifndef __OM                                    /*!< Fallback for older CMSIS versions                                         */
#define __OM   __O
#endif
#ifndef __IOM                                   /*!< Fallback for older CMSIS versions                                         */
#define __IOM  __IO
#endif

/* ========================================  Start of section using anonymous unions  ======================================== */
#if defined (__CC_ARM)
#pragma push
#pragma anon_unions
#elif defined (__ICCARM__)
#pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#pragma clang diagnostic ignored "-Wnested-anon-types"
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#else
#warning Not supported compiler type
#endif


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/
/** @addtogroup Device_Peripheral_peripherals
  * @{
  */

#include <stdint.h>
#include <string.h>

/* ToDo: add here your device specific peripheral access structure typedefs
         following is an example for a timer                                  */
#define BIT0        (0x00000001U)
#define BIT1        (0x00000002U)
#define BIT2        (0x00000004U)
#define BIT3        (0x00000008U)
#define BIT4        (0x00000010U)
#define BIT5        (0x00000020U)
#define BIT6        (0x00000040U)
#define BIT7        (0x00000080U)
#define BIT8        (0x00000100U)
#define BIT9        (0x00000200U)
#define BIT10       (0x00000400U)
#define BIT11       (0x00000800U)
#define BIT12       (0x00001000U)
#define BIT13       (0x00002000U)
#define BIT14       (0x00004000U)
#define BIT15       (0x00008000U)
#define BIT16       (0x00010000U)
#define BIT17       (0x00020000U)
#define BIT18       (0x00040000U)
#define BIT19       (0x00080000U)
#define BIT20       (0x00100000U)
#define BIT21       (0x00200000U)
#define BIT22       (0x00400000U)
#define BIT23       (0x00800000U)
#define BIT24       (0x01000000U)
#define BIT25       (0x02000000U)
#define BIT26       (0x04000000U)
#define BIT27       (0x08000000U)
#define BIT28       (0x10000000U)
#define BIT29       (0x20000000U)
#define BIT30       (0x40000000U)
#define BIT31       (0x80000000U)

#define BIT(n)      (1UL << (n))


/*Todo: DMA MPU*/

#define MPU_DMA_REGION_LEN      4
typedef struct
{
    __IO uint32_t REGION_SADDR      :25;
    __IO uint32_t REGION_SADDR_RSVD :7 ;
    __IO uint32_t REGION_EADDR      :25;
    __IO uint32_t REGION_EADDR_RSVD :7 ;
} REGION_ADDR_TypeDef;

typedef struct
{
    __IO uint32_t MPU_DMA_CTRL          :1 ;
    __I  uint32_t MPU_DMA_CTRL_RSVD     :31;

    __IO uint32_t REGION0_RW_ENABLE     :2 ;
    __IO uint32_t REGION1_RW_ENABLE     :2 ;
    __IO uint32_t REGION2_RW_ENABLE     :2 ;
    __IO uint32_t REGION3_RW_ENABLE     :2 ;
    __I  uint32_t MPU_DMA_PROT_RSVD     :24;
    __IO uint32_t MPU_DMA0_FAULT        :2 ;   /* !< MEMCP                               */
    __IO uint32_t MPU_DMA1_FAULT        :2 ;   /* !< USB/QSPI/DAC/SDIO/I2C/SPI/UART/7811 */
    __IO uint32_t MPU_DMA2_FAULT        :2 ;   /* !< DCMI_DMA0                           */
    __IO uint32_t MPU_DMA3_FAULT        :2 ;   /* !< DCMI_DMA1                           */
    __IO uint32_t MPU_DMA4_FAULT        :2 ;   /* !< DCMI_DMA2                           */
    __IO uint32_t MPU_DMA5_FAULT        :2 ;   /* !< PSRAM                               */
    __IO uint32_t MPU_DMA6_FAULT        :2 ;   /* !< HSPI                                */
    __IO uint32_t MPU_DMA7_FAULT        :2 ;   /* !< QR_BINARIZE                         */
    __IO uint32_t MPU_DMA8_FAULT        :2 ;   /* !< QSORT                               */
    __IO uint32_t MPU_DMA9_FAULT        :2 ;   /* !< CANNY_BINARIZE                      */
    __IO uint32_t MPU_DMA10_FAULT       :2 ;   /* !< FAST_BINRIZE                        */
    __I  uint32_t MPU_DMA_FAULT_RSVD    :10;
    __I  uint32_t MPU_DMA_RSVD1[5]         ;

    REGION_ADDR_TypeDef REGION_ADDRS[MPU_DMA_REGION_LEN];
    __I  uint32_t MPU_DMA_RSVD2[16]        ;
    __I  uint32_t DMA_FAULT_ADDR        :25;
    __I  uint32_t DMA_FAULT_ADDR_RSVD   :7 ;
} MPU_DMA_TypeDef;  /*132byte*/

/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripherals
  * @{
  */



/* =========================================================================================================================== */
/* ================                                           MMCU                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief MMCU (MMCU)
  */

typedef struct {                                /*!< (@ 0x000D0000) MMCU Structure                                             */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * CTRL *                                                   */

    struct {
      __OM  uint32_t LTSLEEP_EN : 1;            /*!< [0..0] 使能 lightsleep                                                  */
      __IOM uint32_t LTSLEEP    : 1;            /*!< [1..1] 写1 M0,进入浅睡眠模式
                                                     注意:此BIT写1后必须要有6个以上的NOP指令,否则退
                                                     出浅睡眠时可能会出错                                            */
      __IOM uint32_t WFI_EN     : 1;            /*!< [2..2] m0 WFI的使能                                                    */
      __IM  uint32_t            : 1;
      __IOM uint32_t DCLK_EN    : 1;            /*!< [4..4] m0 dclk的使能                                                   */
      __IOM uint32_t FCLK_EN    : 1;            /*!< [5..5] m0 fclk的使能                                                   */
      __IOM uint32_t SCSCLK_EN  : 1;            /*!< [6..6] m0 scsclk的使能                                                 */
      __IM  uint32_t            : 1;
      __IOM uint32_t BITBAND_CFG : 1;           /*!< [8..8] bitband 每一BIT对应的地址长度(0x2
                                                     0000对应的地址是0x800000)
                                                     0: RAM每一BIT对应的地址长度是8-bit
                                                     1: RAM每一BIT对应的地址长度是32-bit                             */
    } bit;
  } CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) * WKUP_SRC *                                               */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] 唤醒中断源设置: 每1bit对应0~31号中断                 */
    } bit;
  } WKUP_SRC;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) * ERROR_STATUS *                                           */

    struct {
      __IM  uint32_t CODE_CRC   : 1;            /*!< [0..0] 当这1bit置1,代表M0的代码 CRC校验错误                   */
      __IM  uint32_t MEM        : 1;            /*!< [1..1] 当这1bit置1,代表ROM或RAM奇偶校验错误                   */
      __IM  uint32_t MPU        : 1;            /*!< [2..2] 当这1bit置1,代表M0 MPU错误                                  */
      __IM  uint32_t RAM_NOEXE  : 1;            /*!< [3..3] 当这1bit置1,代表M0 RAM执行代码错误                      */
      __IM  uint32_t RV_MPU     : 1;            /*!< [4..4] 当这1bit置1,代表RV MPU错误                                  */
      __IM  uint32_t RV_ACCESS  : 1;            /*!< [5..5] 当这1bit置1,代表risc-v访问不存在的地
                                                     址空间                                                                 */
      __IM  uint32_t RCODE_CRC  : 1;            /*!< [6..6] 当这1bit置1,代表RV代码读取CRC校验错误                 */
      __IM  uint32_t MPU_ROM    : 1;            /*!< [7..7] 当这1bit置1,代表rom区域非法访问                         */
      __IM  uint32_t DMA_MPU    : 1;            /*!< [8..8] 当这1bit置1,代表DMA MPU错误                                 */
      __IM  uint32_t            : 7;
      __IOM uint32_t ERR_CLR    : 1;            /*!< [16..16] 写1会清除所有的CPU ERROR状态                            */
    } bit;
  } ERROR_STATUS;
  __IM  uint32_t  RESERVED[5];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) * IRQ_ADDR0 *                                              */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] M0的中断起始地址                                           */
    } bit;
  } IRQ_ADDR0;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) * CURR_CLK *                                               */

    struct {
      __IOM uint32_t MS_CLK     : 20;           /*!< [19..0] DELAY_MS所需时钟(单位CLK)                                   */
      __IOM uint32_t US_CLK     : 12;           /*!< [31..20] DELAY_US所需时钟(单位CLK)                                  */
    } bit;
  } CURR_CLK;
  __IM  uint32_t  RESERVED1[54];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000100) * RV_CTRL *                                                */

    struct {
      __IOM uint32_t CLK_EN     : 4;            /*!< [3..0] RV 时钟使能
                                                     0x0a: 使能 risc-v clock
                                                     others: 失能 risc-v clock                                               */
      __IM  uint32_t            : 4;
      __IOM uint32_t RESET      : 4;            /*!< [11..8] RV复位使能
                                                     0x0a: enable risc-v
                                                     others: reset riscv                                                       */
      __IM  uint32_t            : 4;
      __IOM uint32_t FS_EN      : 4;            /*!< [19..16] RV独立睡眠配置
                                                     0xa: M0和RV独立睡眠
                                                     others: M0睡眠会强制RV一起睡眠                                   */
      __IOM uint32_t FS_LOCK    : 1;            /*!< [20..20] RV独立睡眠配置锁定
                                                     1: 锁定 FS_LOCK和FS_EN                                                 */
      __IM  uint32_t            : 3;
      __IM  uint32_t RST_STATUS : 1;            /*!< [24..24] RV复位状态
                                                     1:复位
                                                     0:没有复位                                                            */
      __IM  uint32_t SLP_STATUS : 1;            /*!< [25..25] RV睡眠状态
                                                     1:睡眠
                                                     0:没有睡眠                                                            */
    } bit;
  } RV_CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000104) * RV_IRQ *                                                 */

    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] rv_to_m0中断使能                                               */
      __IM  uint32_t            : 7;
      __IOM uint32_t IRQ        : 1;            /*!< [8..8] rv_to_m0中断状态位,使能之前必须先清除一
                                                     下该标志位,否则上次中断状态会直接触发中断             */
      __IM  uint32_t            : 7;
      __IOM uint32_t TRIG       : 1;            /*!< [16..16] 写‘1’会触发m0_to_rv中断,中断pend
                                                     ing寄存器和wakeup enable配置在riscv
                                                     寄存器中
                                                     必须写0清除,否则会导致一直触发                              */
    } bit;
  } RV_IRQ;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000108) * SW_IRQ *                                                 */

    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] M0软件中断使能                                               */
      __IOM uint32_t TRIG       : 1;            /*!< [1..1] 软件写1会触发软件中断                                    */
      __IM  uint32_t            : 6;
      __IOM uint32_t CODE       : 8;            /*!< [15..8] 用户软件自己可以操作的8BIT                             */
    } bit;
  } SW_IRQ;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000010C) * BIN_IRQ *                                                */

    struct {
      __IOM uint32_t QR_IE      : 1;            /*!< [0..0] 二维码二值化中断使能                                     */
      __IOM uint32_t ONED_IE    : 1;            /*!< [1..1] 一维码二值化中断使能                                     */
    } bit;
  } BIN_IRQ;
} MMCU_Type;                                    /*!< Size = 272 (0x110)                                                        */



/* =========================================================================================================================== */
/* ================                                           MMPU                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief MMPU (MMPU)
  */

typedef struct {                                /*!< (@ 0x000D8080) MMPU Structure                                             */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * CTRL_ID *                                                */

    struct {
      __IM  uint32_t VAL        : 32;           /*!< [31..0] MPU ID                                                            */
    } bit;
  } CTRL_ID;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) * CTRL *                                                   */

    struct {
      __IOM uint32_t VAL        : 1;            /*!< [0..0] MPU使能                                                          */
    } bit;
  } CTRL;
  __IM  uint32_t  RESERVED;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) * CTRL_FSR *                                               */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [4:2] fault region
                                                     [1:0] fault status                                                        */
    } bit;
  } CTRL_FSR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) * CTRL_FAR *                                               */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] fault address                                                     */
    } bit;
  } CTRL_FAR;

  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000014) * PROTECTION *                                             */

    struct {
      __IOM uint16_t VAL        : 16;           /*!< [15..0] protection15：0
                                                     00：no access
                                                     01：private only
                                                     10：private + user read only
                                                     11：Full Access                                                          */
    } bit;
  } PROTECTION;
  __IM  uint16_t  RESERVED1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) * USER_START *                                             */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] 用户程序起始地址                                          */
    } bit;
  } USER_START;
  __IM  uint32_t  RESERVED2[9];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000040) * REGION_BASE0 *                                           */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [0]regionx_enable [20:6]
                                                     BASEx_REG                                                                 */
    } bit;
  } REGION_BASE0;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000044) * REGION_BASE1 *                                           */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [0]regionx_enable [20:6]
                                                     BASEx_REG                                                                 */
    } bit;
  } REGION_BASE1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000048) * REGION_BASE2 *                                           */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [0]regionx_enable [20:6]
                                                     BASEx_REG                                                                 */
    } bit;
  } REGION_BASE2;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) * REGION_BASE3 *                                           */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [0]regionx_enable [20:6]
                                                     BASEx_REG                                                                 */
    } bit;
  } REGION_BASE3;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000050) * REGION_BASE4 *                                           */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [0]regionx_enable [20:6]
                                                     BASEx_REG                                                                 */
    } bit;
  } REGION_BASE4;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000054) * REGION_BASE5 *                                           */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [0]regionx_enable [20:6]
                                                     BASEx_REG                                                                 */
    } bit;
  } REGION_BASE5;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000058) * REGION_BASE6 *                                           */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [0]regionx_enable [20:6]
                                                     BASEx_REG                                                                 */
    } bit;
  } REGION_BASE6;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000005C) * REGION_BASE7 *                                           */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [0]regionx_enable [20:6]
                                                     BASEx_REG                                                                 */
    } bit;
  } REGION_BASE7;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000060) * REGION_LIMIT0 *                                          */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [20:6] LIMIT0_REG                                                 */
    } bit;
  } REGION_LIMIT0;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000064) * REGION_LIMIT1 *                                          */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [20:6] LIMIT1_REG                                                 */
    } bit;
  } REGION_LIMIT1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000068) * REGION_LIMIT2 *                                          */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [20:6] LIMIT2_REG                                                 */
    } bit;
  } REGION_LIMIT2;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000006C) * REGION_LIMIT3 *                                          */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [20:6] LIMIT3_REG                                                 */
    } bit;
  } REGION_LIMIT3;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000070) * REGION_LIMIT4 *                                          */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [20:6] LIMIT4_REG                                                 */
    } bit;
  } REGION_LIMIT4;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000074) * REGION_LIMIT5 *                                          */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [20:6] LIMIT5_REG                                                 */
    } bit;
  } REGION_LIMIT5;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000078) * REGION_LIMIT6 *                                          */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [20:6] LIMIT6_REG                                                 */
    } bit;
  } REGION_LIMIT6;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000007C) * REGION_LIMIT7 *                                          */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] [20:6] LIMIT7_REG                                                 */
    } bit;
  } REGION_LIMIT7;
} MMPU_Type;                                    /*!< Size = 128 (0x80)                                                         */



/* =========================================================================================================================== */
/* ================                                           DCMI                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief 32 DCMI (DCMI)
  */

typedef struct {                                /*!< (@ 0x000D8200) DCMI Structure                                             */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) DCMI_CR Control Register                                   */

    struct {
      __IOM uint32_t CAPTURE    : 1;            /*!< [0..0] CAPTURE enable                                                     */
      __IOM uint32_t CM         : 1;            /*!< [1..1] CAPTURE_MODE                                                       */
      __IOM uint32_t CROP       : 1;            /*!< [2..2] crop feature                                                       */
      __IOM uint32_t JPEG       : 1;            /*!< [3..3] JPEG format                                                        */
      __IOM uint32_t ESS        : 1;            /*!< [4..4] Embedded synchronization select                                    */
      __IOM uint32_t PCKPOL     : 1;            /*!< [5..5] Pixel clock sampling along selection                               */
      __IOM uint32_t HSPOL      : 1;            /*!< [6..6] Horizontal synchronization polarity                                */
      __IOM uint32_t VSPOL      : 1;            /*!< [7..7] Vertical synchronization polarity                                  */
      __IOM uint32_t FCRC       : 2;            /*!< [9..8] Frame capture rate control                                         */
      __IOM uint32_t EDM        : 3;            /*!< [12..10] Extended data mode control                                       */
      __IOM uint32_t SPI_MODE   : 1;            /*!< [13..13] SPI ddr mode select                                              */
      __IOM uint32_t ENABLE     : 1;            /*!< [14..14] DCMI enable                                                      */
      __IM  uint32_t            : 1;
      __IOM uint32_t BSM        : 2;            /*!< [17..16] Byte select mode                                                 */
      __IOM uint32_t OEBS       : 1;            /*!< [18..18] Odd enable of byte select                                        */
      __IOM uint32_t LSM        : 1;            /*!< [19..19] Line select mode                                                 */
      __IOM uint32_t OELS       : 1;            /*!< [20..20] Odd enable of line select                                        */
      __IM  uint32_t            : 3;
      __IOM uint32_t IN_WIRE    : 1;            /*!< [24..24] DCMI input data line bit sequence                                */
      __IOM uint32_t IN_DDR     : 1;            /*!< [25..25] DDR double - edge sequential selection                           */
      __IM  uint32_t            : 1;
      __IOM uint32_t DATA_LSB   : 1;            /*!< [27..27] data mode select                                                 */
      __IOM uint32_t BIT_LSB    : 1;            /*!< [28..28] BIT mode select                                                  */
    } bit;
  } DCMI_CR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) DCMI_SR Control Register                                   */

    struct {
      __IM  uint32_t HSYNC      : 1;            /*!< [0..0] DCMI_HSYNC,pin status                                              */
      __IM  uint32_t VSYNC      : 1;            /*!< [1..1] DCMI_VSYNC,pin status                                              */
      __IM  uint32_t            : 6;
      __IM  uint32_t AFIFO_STU  : 8;            /*!< [15..8] afifo status                                                      */
      __IM  uint32_t CURR_ST    : 4;            /*!< [19..16] curr st                                                          */
      __IM  uint32_t            : 4;
      __IM  uint32_t BLOCK_EN   : 1;            /*!< [24..24] block enable                                                     */
      __IM  uint32_t CAPTURE_EN : 1;            /*!< [25..25] capture enable                                                   */
      __IM  uint32_t SNAPSHOT_MODE : 1;         /*!< [26..26] snapshot mode                                                    */
    } bit;
  } DCMI_SR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) DCMI_RIS Control Register                                  */

    struct {
      __IOM uint32_t FRAME      : 1;            /*!< [0..0] interrupt status                                                   */
      __IOM uint32_t ERR        : 1;            /*!< [1..1] interrupt status                                                   */
      __IOM uint32_t VSYNC      : 1;            /*!< [2..2] interrupt status                                                   */
      __IOM uint32_t LINE       : 1;            /*!< [3..3] interrupt status                                                   */
      __IOM uint32_t DMA0_LINES : 1;            /*!< [4..4] interrupt status                                                   */
      __IOM uint32_t DMA0_OVFL  : 1;            /*!< [5..5] interrupt status                                                   */
      __IOM uint32_t DMA0_FRAEND : 1;           /*!< [6..6] interrupt status                                                   */
      __IOM uint32_t DMA1_LINES : 1;            /*!< [7..7] interrupt status                                                   */
      __IOM uint32_t DMA1_OVFL  : 1;            /*!< [8..8] interrupt status                                                   */
      __IOM uint32_t DMA1_FRAEND : 1;           /*!< [9..9] interrupt status                                                   */
      __IOM uint32_t DMA2_LINES : 1;            /*!< [10..10] interrupt status                                                 */
      __IOM uint32_t DMA2_OVFL  : 1;            /*!< [11..11] interrupt status                                                 */
      __IOM uint32_t DMA2_FRAEND : 1;           /*!< [12..12] interrupt status                                                 */
      __IM  uint32_t            : 11;
      __IM  uint32_t DMA0_HALF  : 1;            /*!< [24..24] buffer status                                                    */
      __IM  uint32_t DMA1_HALF  : 1;            /*!< [25..25] buffer status                                                    */
      __IM  uint32_t DMA2_HALF  : 1;            /*!< [26..26] buffer status                                                    */
    } bit;
  } RIS;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) DCMI_IER Control Register                                  */

    struct {
      __IOM uint32_t FRAME      : 1;            /*!< [0..0] capture complete interrupt enable                                  */
      __IOM uint32_t ERR        : 1;            /*!< [1..1] synochronization error interrupt enable                            */
      __IOM uint32_t VSYNC      : 1;            /*!< [2..2] VSYNC interrupt enable                                             */
      __IOM uint32_t LINE       : 1;            /*!< [3..3] Line interrupt enable                                              */
      __IOM uint32_t DMA0_LINES : 1;            /*!< [4..4] DAM0 lines interrupt enable                                        */
      __IOM uint32_t DMA0_OVFL  : 1;            /*!< [5..5] DAM0 OVFL interrupt enable                                         */
      __IOM uint32_t DMA0_FRAEND : 1;           /*!< [6..6] DAM0 frame end interrupt enable                                    */
      __IOM uint32_t DMA1_LINES : 1;            /*!< [7..7] DAM1 lines interrupt enable                                        */
      __IOM uint32_t DMA1_OVFL  : 1;            /*!< [8..8] DAM1 OVFL interrupt enable                                         */
      __IOM uint32_t DMA1_FRAEND : 1;           /*!< [9..9] DAM1 frame end interrupt enable                                    */
      __IOM uint32_t DMA2_LINES : 1;            /*!< [10..10] DAM2 lines interrupt enable                                      */
      __IOM uint32_t DMA2_OVFL  : 1;            /*!< [11..11] DAM2 OVFL interrupt enable                                       */
      __IOM uint32_t DMA2_FRAEND : 1;           /*!< [12..12] DAM2 frame end interrupt enable                                  */
    } bit;
  } IER;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) DCMI_MIR Control Register                                  */

    struct {
      __IOM uint32_t FRAME      : 1;            /*!< [0..0] capture complete masked interrupt status                           */
      __IOM uint32_t ERR        : 1;            /*!< [1..1] Synochronization error masked interrupt status                     */
      __IOM uint32_t VSYNC      : 1;            /*!< [2..2] VSYNC masked interrupt status                                      */
      __IOM uint32_t LINE       : 1;            /*!< [3..3] Line masked interrupt status                                       */
      __IOM uint32_t DMA0_LINES : 1;            /*!< [4..4] DMA0 Line masked interrupt status                                  */
      __IOM uint32_t DMA0_OVFL  : 1;            /*!< [5..5] DMA0 OVFL masked interrupt status                                  */
      __IOM uint32_t DMA0_FRAEND : 1;           /*!< [6..6] DMA0 frame end masked interrupt status                             */
      __IOM uint32_t DMA1_LINES : 1;            /*!< [7..7] DMA1 Line masked interrupt status                                  */
      __IOM uint32_t DMA1_OVFL  : 1;            /*!< [8..8] DMA1 OVFL masked interrupt status                                  */
      __IOM uint32_t DMA1_FRAEND : 1;           /*!< [9..9] DMA1 frame end masked interrupt status                             */
      __IOM uint32_t DMA2_LINES : 1;            /*!< [10..10] DMA2 Line masked interrupt status                                */
      __IOM uint32_t DMA2_OFVL  : 1;            /*!< [11..11] DMA2 OVFL masked interrupt status                                */
      __IOM uint32_t DMA2_FRAEND : 1;           /*!< [12..12] DMA2 frame end masked interrupt status                           */
      __IM  uint32_t            : 11;
      __IM  uint32_t DMA0_HALF  : 1;            /*!< [24..24] buffer interrupt status                                          */
      __IM  uint32_t DMA1_HALF  : 1;            /*!< [25..25] buffer interrupt status                                          */
      __IM  uint32_t DMA2_HALF  : 1;            /*!< [26..26] buffer interrupt status                                          */
    } bit;
  } MIR;
  __IM  uint32_t  RESERVED;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) DCMI_ESCR control register                                 */

    struct {
      __IOM uint32_t FSC        : 8;            /*!< [7..0] frame start delimiter code                                         */
      __IOM uint32_t LSC        : 8;            /*!< [15..8] line start delimiter code                                         */
      __IOM uint32_t LEC        : 8;            /*!< [23..16] line end delimiter code                                          */
      __IOM uint32_t FEC        : 8;            /*!< [31..24] Frame end delimiter code                                         */
    } bit;
  } ESCR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) DCMI_ESUR control register                                 */

    struct {
      __IOM uint32_t FSU        : 8;            /*!< [7..0] frame start delimiter unmask                                       */
      __IOM uint32_t LSU        : 8;            /*!< [15..8] Line start delimiter unmask                                       */
      __IOM uint32_t LEU        : 8;            /*!< [23..16] Line end delimiter unmask                                        */
      __IOM uint32_t FEU        : 8;            /*!< [31..24] frame end delimiter unmask                                       */
    } bit;
  } ESUR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) DCMI_CWSTRT control register                               */

    struct {
      __IOM uint32_t HOFFCNT    : 14;           /*!< [13..0] Horizontal offset count,start index is 0                          */
      __IM  uint32_t            : 2;
      __IOM uint32_t VST        : 14;           /*!< [29..16] Vertical start line count,start index is 0                       */
    } bit;
  } CWSTRT;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) DCMI_CWSIZE control register                               */

    struct {
      __IOM uint32_t CAPCNT     : 14;           /*!< [13..0] capture count                                                     */
      __IM  uint32_t            : 2;
      __IOM uint32_t VLINE      : 14;           /*!< [29..16] Vertical line count                                              */
    } bit;
  } CWSIZE;
  __IM  uint32_t  RESERVED1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) DCMI_ESHR control register                                 */

    struct {
      __IM  uint32_t            : 4;
      __IOM uint32_t AFIFO_WR_FBD : 1;          /*!< [4..4] afifo write allow or prohibit                                      */
      __IOM uint32_t AFIFO_RST_SW : 1;          /*!< [5..5] afifo rst_sw                                                       */
      __IOM uint32_t END_AFIFO_RST_EN : 1;      /*!< [6..6] Reset the FIFO at the end of DCMI sampling                         */
      __IOM uint32_t START_AFIFO_RST_EN : 1;    /*!< [7..7] Reset the FIFO at the start of DCMI sampling                       */
      __IOM uint32_t ESS_HEADER1 : 8;           /*!< [15..8] Embedded synchronization word byte 1 value                        */
      __IOM uint32_t ESS_HEADER2 : 8;           /*!< [23..16] Embedded synchronization word byte 2 value                       */
      __IOM uint32_t ESS_HEADER3 : 8;           /*!< [31..24] Embedded synchronization word byte 3 value                       */
    } bit;
  } ESHR;
  __IM  uint32_t  RESERVED2[3];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000003C) RX_CNT register                                            */

    struct {
      __IM  uint32_t PIXELS     : 20;           /*!< [19..0] The number of pixels received on the last frame                   */
      __IM  uint32_t LINES      : 12;           /*!< [31..20] The number of rows                                               */
    } bit;
  } RX_CNT;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000040) DCMI_DMA0_CTRL register                                    */

    struct {
      __IOM uint32_t DMA_EN     : 1;            /*!< [0..0] DMA enable                                                         */
      __IOM uint32_t CROP_EN    : 1;            /*!< [1..1] CROP enable                                                        */
      __IM  uint32_t            : 6;
      __IOM uint32_t PIXEL_SEL_MODE : 2;        /*!< [9..8] column selection mode                                              */
      __IOM uint32_t PIXEL_SEL_START : 1;       /*!< [10..10] column selection start                                           */
      __IM  uint32_t            : 1;
      __IOM uint32_t LINE_SEL_MODE_LO : 2;      /*!< [13..12] line selection mode                                              */
      __IOM uint32_t LINE_SEL_START : 2;        /*!< [15..14] line selection start                                             */
      __IOM uint32_t FORMAT_TRANSFER : 2;       /*!< [17..16] Format transfer                                                  */
      __IOM uint32_t YUV_TO_RGB_MODE : 1;       /*!< [18..18] rgb mode selection                                               */
      __IOM uint32_t RGB565_BYTE_SEQ : 1;       /*!< [19..19] rgb byte seq                                                     */
      __IOM uint32_t YUV422_Y_LOC : 1;          /*!< [20..20] Y location of YUV422                                             */
      __IOM uint32_t YUV422_UV_LOC : 1;         /*!< [21..21] UV location of YUV422                                            */
      __IM  uint32_t            : 2;
      __IOM uint32_t WORD_SEQ_PRE_FT : 1;       /*!< [24..24] WORD_SEQ_PRE_FT                                                  */
      __IOM uint32_t WORD_SEQ_POST_FT : 1;      /*!< [25..25] WORD_SEQ_POST_FT                                                 */
      __IM  uint32_t            : 2;
      __IOM uint32_t LINE_SEL_MODE_HI : 4;      /*!< [31..28] LINE_SEL_MODE_HI                                                 */
    } bit;
  } DMA0_CTRL;
  __IM  uint32_t  RESERVED3;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000048) crop position                                              */

    struct {
      __IOM uint32_t HSIZE      : 14;           /*!< [13..0] horizonal crop start position                                     */
      __IM  uint32_t            : 2;
      __IOM uint32_t VSTART     : 14;           /*!< [29..16] vertical crop start position                                     */
    } bit;
  } DMA0_CSTART;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) crop SIZE                                                  */

    struct {
      __IOM uint32_t HSIZE      : 14;           /*!< [13..0] horizonal crop size                                               */
      __IM  uint32_t            : 2;
      __IOM uint32_t VSIZE      : 14;           /*!< [29..16] vertical crop size                                               */
    } bit;
  } DMA0_CSIZE;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000050) DMA buffer status                                          */

    struct {
      __IOM uint32_t LINES_IRQ_EN : 1;          /*!< [0..0] IRQ status                                                         */
      __IOM uint32_t FRAME_START_REFRESH : 1;   /*!< [1..1] When a frame_start is encountered, update dma_addr to
                                                     start_addr                                                                */
      __IOM uint32_t DMA_SADDR_REFRESH_EN : 1;  /*!< [2..2] Enable                                                             */
      __IM  uint32_t            : 5;
      __IM  uint32_t BUFFER_EMPTY : 1;          /*!< [8..8] buffer_status                                                      */
      __IM  uint32_t BUFFER_VALID : 1;          /*!< [9..9] buffer status                                                      */
      __IM  uint32_t            : 6;
      __IOM uint32_t LINES_IRQ_SEL : 8;         /*!< [23..16] IRQ selection                                                    */
    } bit;
  } DMA0_BUF;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000054) DMA buffer start address                                   */

    struct {
      __IOM uint32_t SADDR      : 24;           /*!< [23..0] DMA buffer start address                                          */
    } bit;
  } DMA0_SADDR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000058) DMA buffer length                                          */

    struct {
      __IOM uint32_t LEN        : 24;           /*!< [23..0] DMA buffer length                                                 */
    } bit;
  } DMA0_LEN;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000005C) DMA current                                                */

    struct {
      __IM  uint32_t WADDR      : 24;           /*!< [23..0] DMA current write address                                         */
    } bit;
  } DMA0_WADDR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000060) DCMI_DMA0_CTRL register                                    */

    struct {
      __IOM uint32_t DMA_EN     : 1;            /*!< [0..0] DMA enable                                                         */
      __IOM uint32_t CROP_EN    : 1;            /*!< [1..1] CROP enable                                                        */
      __IM  uint32_t            : 6;
      __IOM uint32_t PIXEL_SEL_MODE : 2;        /*!< [9..8] column selection mode                                              */
      __IOM uint32_t PIXEL_SEL_START : 1;       /*!< [10..10] column selection start                                           */
      __IM  uint32_t            : 1;
      __IOM uint32_t LINE_SEL_MODE_LO : 2;      /*!< [13..12] line selection mode                                              */
      __IOM uint32_t LINE_SEL_START : 2;        /*!< [15..14] line selection start                                             */
      __IOM uint32_t FORMAT_TRANSFER : 2;       /*!< [17..16] Format transfer                                                  */
      __IOM uint32_t YUV_TO_RGB_MODE : 1;       /*!< [18..18] rgb mode selection                                               */
      __IOM uint32_t RGB565_BYTE_SEQ : 1;       /*!< [19..19] rgb byte seq                                                     */
      __IOM uint32_t YUV422_Y_LOC : 1;          /*!< [20..20] Y location of YUV422                                             */
      __IOM uint32_t YUV422_UV_LOC : 1;         /*!< [21..21] UV location of YUV422                                            */
      __IM  uint32_t            : 2;
      __IOM uint32_t WORD_SEQ_PRE_FT : 1;       /*!< [24..24] WORD_SEQ_PRE_FT                                                  */
      __IOM uint32_t WORD_SEQ_POST_FT : 1;      /*!< [25..25] WORD_SEQ_POST_FT                                                 */
      __IM  uint32_t            : 2;
      __IOM uint32_t LINE_SEL_MODE_HI : 4;      /*!< [31..28] LINE_SEL_MODE_HI                                                 */
    } bit;
  } DMA1_CTRL;
  __IM  uint32_t  RESERVED4;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000068) crop position                                              */

    struct {
      __IOM uint32_t HSIZE      : 14;           /*!< [13..0] horizonal crop start position                                     */
      __IM  uint32_t            : 2;
      __IOM uint32_t VSTART     : 14;           /*!< [29..16] vertical crop start position                                     */
    } bit;
  } DMA1_CSTART;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000006C) crop SIZE                                                  */

    struct {
      __IOM uint32_t HSIZE      : 14;           /*!< [13..0] horizonal crop size                                               */
      __IM  uint32_t            : 2;
      __IOM uint32_t VSIZE      : 14;           /*!< [29..16] vertical crop size                                               */
    } bit;
  } DMA1_CSIZE;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000070) DMA buffer status                                          */

    struct {
      __IOM uint32_t LINES_IRQ_EN : 1;          /*!< [0..0] IRQ status                                                         */
      __IOM uint32_t FRAME_START_REFRESH : 1;   /*!< [1..1] When a frame_start is encountered, update dma_addr to
                                                     start_addr                                                                */
      __IOM uint32_t DMA_SADDR_REFRESH_EN : 1;  /*!< [2..2] Enable                                                             */
      __IM  uint32_t            : 5;
      __IM  uint32_t BUFFER_EMPTY : 1;          /*!< [8..8] buffer_status                                                      */
      __IM  uint32_t BUFFER_VALID : 1;          /*!< [9..9] buffer status                                                      */
      __IM  uint32_t            : 6;
      __IOM uint32_t LINES_IRQ_SEL : 8;         /*!< [23..16] IRQ selection                                                    */
    } bit;
  } DMA1_BUF;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000074) DMA buffer start address                                   */

    struct {
      __IOM uint32_t SADDR      : 24;           /*!< [23..0] DMA buffer start address                                          */
    } bit;
  } DMA1_SADDR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000078) DMA buffer length                                          */

    struct {
      __IOM uint32_t LEN        : 24;           /*!< [23..0] DMA buffer length                                                 */
    } bit;
  } DMA1_LEN;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000007C) DMA current                                                */

    struct {
      __IM  uint32_t WADDR      : 24;           /*!< [23..0] DMA current write address                                         */
    } bit;
  } DMA1_WADDR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000080) DCMI_DMA0_CTRL register                                    */

    struct {
      __IOM uint32_t DMA_EN     : 1;            /*!< [0..0] DMA enable                                                         */
      __IOM uint32_t CROP_EN    : 1;            /*!< [1..1] CROP enable                                                        */
      __IM  uint32_t            : 6;
      __IOM uint32_t PIXEL_SEL_MODE : 2;        /*!< [9..8] column selection mode                                              */
      __IOM uint32_t PIXEL_SEL_START : 1;       /*!< [10..10] column selection start                                           */
      __IM  uint32_t            : 1;
      __IOM uint32_t LINE_SEL_MODE_LO : 2;      /*!< [13..12] line selection mode                                              */
      __IOM uint32_t LINE_SEL_START : 2;        /*!< [15..14] line selection start                                             */
      __IOM uint32_t FORMAT_TRANSFER : 2;       /*!< [17..16] Format transfer                                                  */
      __IOM uint32_t YUV_TO_RGB_MODE : 1;       /*!< [18..18] rgb mode selection                                               */
      __IOM uint32_t RGB565_BYTE_SEQ : 1;       /*!< [19..19] rgb byte seq                                                     */
      __IOM uint32_t YUV422_Y_LOC : 1;          /*!< [20..20] Y location of YUV422                                             */
      __IOM uint32_t YUV422_UV_LOC : 1;         /*!< [21..21] UV location of YUV422                                            */
      __IM  uint32_t            : 2;
      __IOM uint32_t WORD_SEQ_PRE_FT : 1;       /*!< [24..24] WORD_SEQ_PRE_FT                                                  */
      __IOM uint32_t WORD_SEQ_POST_FT : 1;      /*!< [25..25] WORD_SEQ_POST_FT                                                 */
      __IM  uint32_t            : 2;
      __IOM uint32_t LINE_SEL_MODE_HI : 4;      /*!< [31..28] LINE_SEL_MODE_HI                                                 */
    } bit;
  } DMA2_CTRL;
  __IM  uint32_t  RESERVED5;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000088) crop position                                              */

    struct {
      __IOM uint32_t HSIZE      : 14;           /*!< [13..0] horizonal crop start position                                     */
      __IM  uint32_t            : 2;
      __IOM uint32_t VSTART     : 14;           /*!< [29..16] vertical crop start position                                     */
    } bit;
  } DMA2_CSTART;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000008C) crop SIZE                                                  */

    struct {
      __IOM uint32_t HSIZE      : 14;           /*!< [13..0] horizonal crop size                                               */
      __IM  uint32_t            : 2;
      __IOM uint32_t VSIZE      : 14;           /*!< [29..16] vertical crop size                                               */
    } bit;
  } DMA2_CSIZE;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000090) DMA buffer status                                          */

    struct {
      __IOM uint32_t LINES_IRQ_EN : 1;          /*!< [0..0] IRQ status                                                         */
      __IOM uint32_t FRAME_START_REFRESH : 1;   /*!< [1..1] When a frame_start is encountered, update dma_addr to
                                                     start_addr                                                                */
      __IOM uint32_t DMA_SADDR_REFRESH_EN : 1;  /*!< [2..2] Enable                                                             */
      __IM  uint32_t            : 5;
      __IM  uint32_t BUFFER_EMPTY : 1;          /*!< [8..8] buffer_status                                                      */
      __IM  uint32_t BUFFER_VALID : 1;          /*!< [9..9] buffer status                                                      */
      __IM  uint32_t            : 6;
      __IOM uint32_t LINES_IRQ_SEL : 8;         /*!< [23..16] IRQ selection                                                    */
    } bit;
  } DMA2_BUF;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000094) DMA buffer start address                                   */

    struct {
      __IOM uint32_t SADDR      : 24;           /*!< [23..0] DMA buffer start address                                          */
    } bit;
  } DMA2_SADDR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000098) DMA buffer length                                          */

    struct {
      __IOM uint32_t LEN        : 24;           /*!< [23..0] DMA buffer length                                                 */
    } bit;
  } DMA2_LEN;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000009C) DMA current                                                */

    struct {
      __IM  uint32_t WADDR      : 24;           /*!< [23..0] DMA current write address                                         */
    } bit;
  } DMA2_WADDR;
} MDCMI_Type;                                    /*!< Size = 160 (0xa0)                                                         */

/* =========================================================================================================================== */
/* ================                                           MHSPI                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief MHSPI (MHSPI)
  */

typedef struct {                                /*!< (@ 0x000D8400) MHSPI Structure                                            */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * CTRL *                                                   */

    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] 接收相位调整使能开关
                                                     0：失能HSPI
                                                     1：使能HSPI                                                            */
      __IOM uint32_t START_EN   : 1;            /*!< [1..1] DCMI多行中断启动spi使能
                                                     0: 禁止硬件启动spi
                                                     1: 允许硬件启动spi                                                  */
      __IOM uint32_t START_SEL  : 1;            /*!< [2..2] DCMI多行中断选择
                                                     0: DCMI DMA0
                                                     1: DCMI DMA1                                                              */
      __IOM uint32_t START      : 1;            /*!< [3..3] HSPI启动位，自动开启DMA_START
                                                     0：无动作
                                                     1：硬件启动一次HSPI收发                                          */
      __IOM uint32_t CPOL       : 1;            /*!< [4..4] 时钟极性位
                                                     0：失能相位调整
                                                     1：使能相位调整                                                    */
      __IOM uint32_t CPHA       : 1;            /*!< [5..5] 时钟相位
                                                     0：空闲状态时，SCK保持低电平；
                                                     1：空闲状态时，SCK保持高电平；                               */
      __IOM uint32_t RTX_SEQ    : 1;            /*!< [6..6] 收发序列控制位
                                                     0：收发同时进行，长度为tx_len;
                                                     1：先进行tx_len次发送, 再进行rx_len次接收
                                                     （rx_len为0时跳过接收）                                           */
      __IOM uint32_t RXD_EN     : 1;            /*!< [7..7] 接收相位调整使能开关
                                                     0：失能相位调整;
                                                     1：使能相位调整。                                                 */
      __IOM uint32_t NCS_DLY    : 3;            /*!< [10..8] NCS提前拉低和滞后拉高的延时位
                                                     0-7：spi_clk*(ncs_dly+1)。                                              */
      __IOM uint32_t FIFO_CTRL  : 1;            /*!< [11..11] FIFO软件控制权限使能位
                                                     0: 软件无法操作FIFO,仅运行DMA自动操作
                                                     1: 软件可以操作FIFO,不使用DMA时,可以直接使用
                                                     FIFO进行收发                                                          */
      __IOM uint32_t TRX_DLY    : 4;            /*!< [15..12] 发送和接收保护间隔位
                                                     0-7：软件增加Hspi_clk*(trx_dly+1)
                                                     *4个周期时长。                                                      */
      __IOM uint32_t CLK_DIV    : 4;            /*!< [19..16] HSPI预分频位
                                                     0-7：分频值为(clk_div + 1)*2。                                      */
      __IOM uint32_t RX_PHASE   : 4;            /*!< [23..20] 控制接收相位调整值位,按bit采样位偏移N个cl
                                                     k个 个数
                                                     0-7: 采样时间延后(rx_adj_clk + 1)*
                                                     Hspi_clk不得大于clk_div。
                                                                                                                               */
      __IM  uint32_t            : 1;
      __IOM uint32_t Y2RGB      : 1;            /*!< [25..25] buff内容转RGB565控制位
                                                     0：无操作;
                                                     1：buffer内容为8-bit灰度，实际发送时会自动转
                                                     换为16-bit RGB565发送。                                              */
      __IOM uint32_t FIRST_BIT  : 1;            /*!< [26..26] 帧格式位
                                                     0：先发送MSB;
                                                     1：先发送LSB
                                                     注：y_to_rgb_mode为1时,先进行y转rgb操
                                                     作,再按配置比特顺序进行发送                                  */
    } bit;
  } CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) * FIFO *                                                   */

    struct {
      __IOM uint32_t TX_RPTR_INC : 1;           /*!< [0..0] 读取TXFIFO字节位，写1, TX_DATA读
                                                     地址加1
                                                     0：无操作；
                                                     1：读取FIFO中一个字节；                                          */
      __IM  uint32_t TX_EMPTY   : 1;            /*!< [1..1] TXFIFO状态位
                                                     0：非空;
                                                     1：空。                                                                */
      __IM  uint32_t TX_FULL    : 1;            /*!< [2..2] TXFIFO状态位
                                                     0：非满;
                                                     1：满。                                                                */
      __IOM uint32_t RST        : 1;            /*!< [3..3] 软件复位FIFO
                                                     0: do not effect
                                                     1: reset fifo                                                             */
      __IM  uint32_t            : 4;
      __IOM uint32_t RX_RPTR_INC : 1;           /*!< [8..8] 读取RXFIFO字节位，写1, RX_DATA读
                                                     地址加1
                                                     0：无操作；
                                                     1：读取FIFO中一个字节                                             */
      __IM  uint32_t RX_EMPTY   : 1;            /*!< [9..9] RXFIFO状态位
                                                     0：非空;
                                                     1：空。                                                                */
      __IM  uint32_t RX_FULL    : 1;            /*!< [10..10] RXFIFO状态位
                                                     0：非满;
                                                     1：满。                                                                */
      __IOM uint32_t AUTO_RST   : 1;            /*!< [11..11] fifo自动复位
                                                     0: do not effect
                                                     1: 每次传输完成后,自动复位一下fifo                           */
      __IM  uint32_t            : 4;
      __IOM uint32_t TX_DATA    : 8;            /*!< [23..16] 读取Tx_FIFO数据
                                                     0-7：写寄存器时，直接将此字节写入Tx_FIFO，
                                                     读取此寄存器时，表示Tx_FIFO当前值;                           */
      __IOM uint32_t RX_DATA    : 8;            /*!< [31..24] 读取RX_FIFO数据
                                                     0-7：写寄存器时，直接将此字节写入Rx_FIFO，
                                                     读取此寄存器时，表示Rx_FIFO当前值;                           */
    } bit;
  } FIFO;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) * DMA *                                                    */

    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] DMA控制位
                                                     0：失能DMA;
                                                     1：使能DMA。                                                          */
      __IOM uint32_t AUTO_START : 1;            /*!< [1..1] DMA自动传输位
                                                     0：dma不会自动启动，必须手动通过dma_start_
                                                     man启动;
                                                     1：spi_start自动启动dma，无须手动启动dma
                                                     。                                                                       */
      __IM  uint32_t            : 1;
      __IOM uint32_t START      : 1;            /*!< [3..3] 启动DMA传输位，同AUTO_START搭配使用
                                                     0：无操作；
                                                     1：启动一次dma传输任务                                           */
      __IOM uint32_t TX_PTR_INC : 1;            /*!< [4..4] TXFIFO状态位
                                                     0：tx_addr自增
                                                     1：tx_addr不自增。                                                   */
      __IOM uint32_t RX_PTR_INC : 1;            /*!< [5..5] RXFIFO状态位
                                                     0：rx_addr自增;
                                                     1：rx_addr不自增。                                                   */
      __IOM uint32_t PINGPANG_EN : 1;           /*!< [6..6] SPI发送数据时,DMA从内存中乒乓buffer
                                                     取数
                                                     0: disable pingpang
                                                     1: enable pingpang,tx_saddr~
                                                     tx_saddr+tx_len和tx_saddr+tx_
                                                     len ~ tx_saddr+tx_len*2                                                   */
    } bit;
  } DMA;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) * IRQ *                                                    */

    struct {
      __IOM uint32_t DMA_RIS    : 1;            /*!< [0..0] DMA发送完成标志位
                                                     0: DMA发送未完成；
                                                     1: DMA完成一次传输发送；                                         */
      __IOM uint32_t TXFL_RIS   : 1;            /*!< [1..1] 发送FIFO低水准线标志位
                                                     0: 不低于低水准线；
                                                     1: 低于低水准线；                                                  */
      __IOM uint32_t TXFO_RIS   : 1;            /*!< [2..2] 发送FIFO溢出标志位
                                                     0: 发送FIFO未溢出设定字节个数;
                                                     1: 发送FIFO溢出设定字节个数。                                  */
      __IOM uint32_t RXFH_RIS   : 1;            /*!< [3..3] 接收FIFO高水准线标志位
                                                     0: 不高于低水准线;
                                                     1: 高于水准线。                                                     */
      __IOM uint32_t RXFO_RIS   : 1;            /*!< [4..4] 接收FIFO溢出标志位
                                                     0: 接收FIFO未溢出设定字节个数;
                                                     1: 接收FIFO溢出设定字节个数。                                  */
      __IOM uint32_t SOQ_RIS    : 1;            /*!< [5..5] HSPI start信号来临时，上次传输还未完成
                                                     ，
                                                     此时会错过一个HSPI任务，出现错误。
                                                     0: 未错过任务；
                                                     1: 出错，错过一次任务                                            */
      __IM  uint32_t            : 2;
      __IOM uint32_t DMA_MIS    : 1;            /*!< [8..8] DMA传输状态位
                                                     0: DMA发送未完成;
                                                     1: DMA发送完成。                                                     */
      __IOM uint32_t TXFL_MIS   : 1;            /*!< [9..9] 发送FIFO低水准线状态位
                                                     0: 不低于低水准线；
                                                     1: 低于低水准线。                                                  */
      __IOM uint32_t TXFO_MIS   : 1;            /*!< [10..10] 发送FIFO溢出状态位
                                                     0: 发送FIFO未溢出设定字节个数;
                                                     1: 发送FIFO溢出设定字节个数。                                  */
      __IOM uint32_t RXFH_MIS   : 1;            /*!< [11..11] 接收FIFO高水准线状态位
                                                     0: 不高于低水准线;
                                                     1: 高于水准线。                                                     */
      __IOM uint32_t RXFO_MIS   : 1;            /*!< [12..12] 接收FIFO溢出状态位
                                                     0: 接收FIFO未溢出设定字节个数;
                                                     1: 接收FIFO溢出设定字节个数。                                  */
      __IOM uint32_t SOQ_MIS    : 1;            /*!< [13..13] 丢失一次HSPI任务状态位
                                                     0: 未错过任务；
                                                     1: 出错，错过一次任务。                                         */
      __IM  uint32_t            : 2;
      __IOM uint32_t DMA_EN     : 1;            /*!< [16..16] DMA发送完成控制位
                                                     0: 失能DMA发送;
                                                     1: 使能DMA发送。                                                     */
      __IOM uint32_t TXFL_EN    : 1;            /*!< [17..17] 发送FIFO低水准线控制位
                                                     0: 失能低于低水准线；
                                                     1: 使能低于低水准线。                                            */
      __IOM uint32_t TXFO_EN    : 1;            /*!< [18..18] 发送FIFO溢出控制位
                                                     0: 失能发送FIFO未溢出;
                                                     1: 使能发送FIFO溢出。                                              */
      __IOM uint32_t RXFH_EN    : 1;            /*!< [19..19] 接收FIFO高水准线控制位
                                                     0: 失能高于低水准线;
                                                     1: 使能高于水准线。                                               */
      __IOM uint32_t RXFO_EN    : 1;            /*!< [20..20] 接收FIFO溢出控制位
                                                     0: 失能接收FIFO未溢出;
                                                     1: 使能接收FIFO溢出;                                                */
      __IOM uint32_t SOQ_EN     : 1;            /*!< [21..21] 检测START信号丢失使能位
                                                     0: 失能；
                                                     1: 使能。                                                              */
    } bit;
  } IRQ;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) * DMA_TX_SADDR *                                           */

    struct {
      __IOM uint32_t VAL        : 20;           /*!< [19..0] 存放发送数据起始地址，必须四字节对齐。         */
    } bit;
  } DMA_TX_SADDR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) * DMA_RX_SADDR *                                           */

    struct {
      __IOM uint32_t VAL        : 20;           /*!< [19..0] 接收数据的起始地址，必须四字节对齐               */
    } bit;
  } DMA_RX_SADDR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) * DMA_TX_LEN *                                             */

    struct {
      __IOM uint32_t VAL        : 20;           /*!< [19..0] HSPI发送数据字节长度，配置为0时，表示仅接收    */
    } bit;
  } DMA_TX_LEN;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) * DMA_RX_LEN *                                             */

    struct {
      __IOM uint32_t VAL        : 20;           /*!< [19..0] HSPI接收数据字节长度，配置为0时，表示仅发送    */
    } bit;
  } DMA_RX_LEN;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) * DMA_TX_ADDR *                                            */

    struct {
      __IM  uint32_t VAL        : 20;           /*!< [19..0] 存放当前发送数据的地址。                              */
    } bit;
  } DMA_TX_ADDR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) * DMA_RX_ADDR *                                            */

    struct {
      __IM  uint32_t VAL        : 20;           /*!< [19..0] 存放当前接收数据的地址。                              */
    } bit;
  } DMA_RX_ADDR;
  __IM  uint32_t  RESERVED[2];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000030) * FIFO_CTRL *                                              */

    struct {
      __IOM uint32_t RX_WATERLEVEL : 5;         /*!< [4..0] 发送FIFO低水线，
                                                     发送FIFO数据小于等于此长度，并且水线值不为0时，
                                                     触发tx_fifo_lo中断。                                                 */
      __IM  uint32_t            : 3;
      __IOM uint32_t TX_WATERLEVEL : 5;         /*!< [12..8] 接收FIFO高水线，
                                                     接收FIFO数据大于等于此长度，并且水线值不为0时，
                                                     触发rx_fifo_hi中断。                                                 */
      __IM  uint32_t            : 3;
      __IM  uint32_t RX_ITEMS   : 5;            /*!< [20..16] 读取Tx_FIFO的数据个数。                                  */
      __IM  uint32_t            : 3;
      __IM  uint32_t TX_ITEMS   : 5;            /*!< [28..24] 读取RX_FIFO的数据个数。                                  */
    } bit;
  } FIFO_CTRL;
} MHSPI_Type;                                   /*!< Size = 52 (0x34)                                                          */



/* =========================================================================================================================== */
/* ================                                           MWDT                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief MWDT (MWDT)
  */

typedef struct {                                /*!< (@ 0x000F0000) MWDT Structure                                             */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * CONFIG *                                                 */

    struct {
      __IOM uint32_t RELOAD     : 5;            /*!< [4..0] WDT计数时长为(2^(wdt_preset-1
                                                     ))个hclk_div时钟周期                                                 */
      __IOM uint32_t MODE       : 1;            /*!< [5..5] 0 :复位 1:中断                                                 */
      __IOM uint32_t EN         : 1;            /*!< [6..6] 0 :WDT功能关闭. 1: WDT 功能打开.                           */
      __IOM uint32_t CLK_DIV    : 4;            /*!< [10..7] hclk预分频,最大16分频,实际使用的时钟频率
                                                     是clk/(wdt_clk_div+1)                                                    */
      __IOM uint32_t OFF        : 1;            /*!< [11..11] 关闭wdt
                                                     wdt_off_lock为0,并且wdt_on为0时,设
                                                     置wdt_off为1,再设置wdt_off为0,可关闭w
                                                     dt                                                                        */
      __IOM uint32_t OFF_LOCK   : 1;            /*!< [12..12] wdt_off_lock
                                                     1: wdt_off不起作用
                                                     0: wdt_off起作用                                                       */
    } bit;
  } CONFIG;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) * CNT *                                                    */

    struct {
      __IM  uint32_t CNT        : 32;           /*!< [31..0] WDT CNT                                                           */
    } bit;
  } CNT;

  union {
    union {
      __IOM uint32_t reg;                       /*!< (@ 0x00000008) WDT IRQ STATUS                                             */

      struct {
        __IM  uint32_t STATE    : 1;            /*!< [0..0] WDT IRQ STATUS                                                     */
      } bit;
    } IRQ_STATUS;

    union {
      __IOM uint32_t reg;                       /*!< (@ 0x00000008) WDT KICK, 必须写 0x5937                                 */

      struct {
        __OM  uint32_t VALUE    : 32;           /*!< [31..0] WDT KICK,必须写 0x5937                                         */
      } bit;
    } KICK;
  };

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) * CLEAR *                                                  */

    struct {
      __IOM uint32_t CLEAR      : 1;            /*!< [0..0] 向这个寄存器中写1清除WDT 中断                          */
    } bit;
  } CLEAR;
} MWDT_Type;                                    /*!< Size = 16 (0x10)                                                          */



/* =========================================================================================================================== */
/* ================                                           MSCI0                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief MSCI0 (MSCI0)
  */

typedef struct {                                /*!< (@ 0x000F0400) MSCI0 Structure                                            */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * MODE *                                                   */

    struct {
      __IOM uint32_t TPS        : 1;            /*!< [0..0] 模式控制位
                                                     0:T=0
                                                     1:T=1                                                                     */
      __IOM uint32_t CODE_DRT   : 1;            /*!< [1..1] 编码选择控制位
                                                     0:正向编码
                                                     1:反向编码                                                            */
      __IOM uint32_t OD         : 1;            /*!< [2..2] OD控制位
                                                     0: 开漏模式
                                                     1: 推挽模式(default)                                                  */
      __IOM uint32_t ETU_NUM    : 2;            /*!< [4..3] ETU个数控制位                                                 */
      __IOM uint32_t RET_TIME   : 3;            /*!< [7..5] 重传次数                                                       */
      __IOM uint32_t RET_EN     : 1;            /*!< [8..8] 重传使能位
                                                     0:失能
                                                     1:使能                                                                  */
      __IOM uint32_t EN         : 1;            /*!< [9..9] SCI7816使能
                                                     0: 失能
                                                     1: 使能                                                                 */
      __IOM uint32_t BGT_EN     : 1;            /*!< [10..10] 块保护时间使能
                                                     0: 失能
                                                     1: 使能                                                                 */
      __IOM uint32_t CWT_EN     : 1;            /*!< [11..11] CWT计时器使能
                                                     0: 失能
                                                     1: 使能                                                                 */
      __IOM uint32_t CLK_SEL    : 3;            /*!< [14..12] CLK时钟源控制位(PWM0~PWM7)                                 */
      __IOM uint32_t MST_EN     : 1;            /*!< [15..15] 主机模式使能
                                                     0: 失能
                                                     1: 使能                                                                 */
      __IOM uint32_t EDC_EN     : 1;            /*!< [16..16] EDC错误检测使能
                                                     0: 失能
                                                     1: 使能                                                                 */
    } bit;
  } MODE;
  __IM  uint32_t  RESERVED;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) * CTRL *                                                   */

    struct {
      __IOM uint32_t RFIFO_CL   : 1;            /*!< [0..0] 接收FIFO内容清除控制位
                                                     0:不起作用
                                                     1:清除FIFO内数据                                                     */
      __IOM uint32_t TFIFO_CL   : 1;            /*!< [1..1] 发送FIFO内容清除控制位
                                                     0:不起作用
                                                     1:清除FIFO内数据                                                     */
      __IOM uint32_t TS_TEST    : 1;            /*!< [2..2] 检测TS字节
                                                     0:不起作用
                                                     1:接收到数据为03时校验位电平取反                            */
    } bit;
  } CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) * STATUS *                                                 */

    struct {
      __IOM uint32_t RFIFO_N    : 1;            /*!< [0..0] 接收缓冲器空状态位
                                                     0:接收缓冲器空
                                                     1:接收缓冲器中不空                                                */
      __IOM uint32_t RFIFO_F    : 1;            /*!< [1..1] 接收缓冲器满状态位
                                                     0:接收缓冲器不满
                                                     1:接收缓冲器满                                                      */
      __IOM uint32_t PRT_CHK    : 1;            /*!< [2..2] 奇偶校验状态位
                                                     0: 奇偶校验正确
                                                     1: 奇偶校验错误                                                     */
      __IOM uint32_t TFIFO_N    : 1;            /*!< [3..3] 发送缓冲器空状态位
                                                     0: 发送缓冲器空
                                                     1: 发送缓冲器中不空                                               */
      __IOM uint32_t TFIFO_F    : 1;            /*!< [4..4] 发送缓冲器满状态位
                                                     0: 发送缓冲器不满
                                                     1: 发送缓冲器满                                                     */
      __IOM uint32_t RET_CHK    : 1;            /*!< [5..5] 重传奇偶校验检测状态位
                                                     0: 奇偶校验正确
                                                     1: 奇偶校验错误（在重传功能开启时,只有在发送达到重
                                                     ��
                                                     次数时仍有错误发生,此位才被置位）                         */
      __IOM uint32_t BGT_OT     : 1;            /*!< [6..6] BGT超时状态位
                                                     0:没超时
                                                     1:超时 (参考:SCI7816_BGT寄存器说明）                            */
      __IOM uint32_t CWT_OT     : 1;            /*!< [7..7] CWT超时状态位
                                                     0:没超时
                                                     1:超时 (参考:SCI7816_CWT寄存器说明）                            */
      __IOM uint32_t CHK_BIT    : 1;            /*!< [8..8] 检验位状态
                                                     0:检验位正确
                                                     1:检验位错误                                                         */
    } bit;
  } STATUS;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) * INT_IO *                                                 */

    struct {
      __IOM uint32_t R_FNS      : 1;            /*!< [0..0] 接收完成标志位
                                                     0:没接收完成
                                                     1:已接收完成                                                         */
      __IOM uint32_t T_FNS      : 1;            /*!< [1..1] 发送完成标志位
                                                     0:没发送完成
                                                     1:已发送完成                                                         */
    } bit;
  } INT_IO;
  __IM  uint32_t  RESERVED1[3];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) * DATA *                                                   */

    struct {
      __IOM uint32_t VAL        : 8;            /*!< [7..0] 在发送或接收模式下分别充当发送或接收buffer
                                                     角色                                                                    */
    } bit;
  } DATA;
  __IM  uint32_t  RESERVED2;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) * ETU *                                                    */

    struct {
      __IOM uint32_t VAL        : 13;           /*!< [12..0] 配置SCI7816通讯速率                                         */
    } bit;
  } ETU;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) * BGT *                                                    */

    struct {
      __IOM uint32_t VAL        : 6;            /*!< [5..0] 配置SCI7816块反向发送时间间隔,max 6
                                                     3                                                                         */
    } bit;
  } BGT;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000030) * CWT *                                                    */

    struct {
      __IOM uint32_t CWT_TMR    : 24;           /*!< [23..0] 配置SCI7816CWT定时值,发送字节完成,接
                                                     收起始时启动计时                                                  */
      __IOM uint32_t CWT_SRT    : 1;            /*!< [24..24] CWT计时开始
                                                     0:CWT未开始计时
                                                     1:CWT计时立即生效                                                   */
    } bit;
  } CWT;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000034) * EDC *                                                    */

    struct {
      __IOM uint32_t VAL        : 8;            /*!< [7..0] 保存 LRC 计算结果                                            */
    } bit;
  } EDC;
  __IM  uint32_t  RESERVED3[10];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000060) * IS *                                                     */

    struct {
      __IOM uint32_t R_DONE     : 1;            /*!< [0..0] 成功接收到1个字节                                          */
      __IOM uint32_t R_ERR      : 1;            /*!< [1..1] 接收错误中断,T0 重试次数超过配置,T1 奇偶
                                                     校验错误                                                              */
      __IOM uint32_t CWT_TO     : 1;            /*!< [2..2] 接收 CWT 定时器超时中断                                   */
      __IOM uint32_t BWT_TO     : 1;            /*!< [3..3] 接收 BWT 定时器超时中断                                   */
      __IOM uint32_t T_DONE     : 1;            /*!< [4..4] 成功传输 FIFO 中的最后一个字节                         */
      __IOM uint32_t T_ERR      : 1;            /*!< [5..5] 发送错误,T0 重试次数超过配置,T1 从未触发
                                                     此错误                                                                 */
      __IOM uint32_t RFIFO_HA   : 1;            /*!< [6..6] R_ITEMS <= RH_WTL
                                                     发生中断后,应首先读取rx_fifo至水线以下,或改变水
                                                     线,才能清除中断
                                                     RH_WTL为0时,不触发此中断                                          */
      __IOM uint32_t TFIFO_LA   : 1;            /*!< [7..7] T_ITEMS <= TL_WTL
                                                     发生中断后,应首先填充T_ITEMS至水线以上,或改变水
                                                     线,才能清除中断
                                                     TL_WTL为0时,不触发此中断                                          */
      __IOM uint32_t RFIFO_OVF  : 1;            /*!< [8..8] 设备接收字节时 接收FIFO 满,RFIFO_O
                                                     VF 溢出中断                                                           */
      __IOM uint32_t TFIFO_OVF  : 1;            /*!< [9..9] 主机写入 发送FIFO 时 发送FIFO 满,T
                                                     FIFO_OVF 溢出中断
                                                     接收时,主机读 FIFO 下溢可能会导致此中断断言             */
      __IOM uint32_t SHTCUT     : 1;            /*!< [10..10] tbd                                                              */
      __IOM uint32_t T_FNS      : 1;            /*!< [11..11] 发送完成                                                     */
      __IOM uint32_t R_FNS      : 1;            /*!< [12..12] 接收完成                                                     */
      __IOM uint32_t CWT_FLG    : 1;            /*!< [13..13] cwt标志, 写 '1' 清除 IS 和 IES                             */
      __IOM uint32_t R_SRT      : 1;            /*!< [14..14] 接收到毛刺信号,会触发此中断,仅rx_en使能时
                                                     会触发
                                                     bwt期间,bwt会自动恢复重启,可以触发超时
                                                     cwt期间,毛刺到来会重置cwt计数器,wt超时时间会变
                                                     长                                                                       */
    } bit;
  } IS;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000064) * IE *                                                     */

    struct {
      __IOM uint32_t R_DONE     : 1;            /*!< [0..0] 使能 R_DONE 中断控制位                                      */
      __IOM uint32_t R_ERR      : 1;            /*!< [1..1] 使能 R_ERR 中断控制位                                       */
      __IOM uint32_t CWT_TO     : 1;            /*!< [2..2] 使能 CWT_TO 中断控制位                                      */
      __IOM uint32_t BWT_TO     : 1;            /*!< [3..3] 使能 BWT_TO 中断控制位                                      */
      __IOM uint32_t T_DONE     : 1;            /*!< [4..4] 使能 T_DONE 中断控制位                                      */
      __IOM uint32_t T_ERR      : 1;            /*!< [5..5] 使能 T_ERR 中断控制位                                       */
      __IOM uint32_t RFIFO_HA   : 1;            /*!< [6..6] 使能 RFIFO_HA 中断控制位                                    */
      __IOM uint32_t TFIFO_LA   : 1;            /*!< [7..7] 使能 TFIFO_LA 中断控制位                                    */
      __IOM uint32_t RFIFO_OVF  : 1;            /*!< [8..8] 使能 RFIFO_OVF 中断控制位                                   */
      __IOM uint32_t TFIFO_OVF  : 1;            /*!< [9..9] 使能 TFIFO_OVF 中断控制位                                   */
      __IOM uint32_t SHTCUT     : 1;            /*!< [10..10] 使能 SHTCUT 中断控制位                                    */
      __IOM uint32_t T_FNS      : 1;            /*!< [11..11] 使能 T_FNS 中断控制位                                     */
      __IOM uint32_t R_FNS      : 1;            /*!< [12..12] 使能 R_FNS 中断控制位                                     */
      __IOM uint32_t CWT_FLG    : 1;            /*!< [13..13] 使能 CWT_FLG 中断控制位                                   */
      __IOM uint32_t R_SRT      : 1;            /*!< [14..14] 使能 R_SRT 中断控制位                                     */
    } bit;
  } IE;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000068) * IES *                                                    */

    struct {
      __IOM uint32_t R_DONE     : 1;            /*!< [0..0] 使能 R_DONE 中断状态控制位                                */
      __IOM uint32_t R_ERR      : 1;            /*!< [1..1] 使能 R_ERR 中断状态控制位                                 */
      __IOM uint32_t CWT_TO     : 1;            /*!< [2..2] 使能 CWT_TO 中断状态控制位                                */
      __IOM uint32_t BWT_TO     : 1;            /*!< [3..3] 使能 BWT_TO 中断状态控制位                                */
      __IOM uint32_t T_DONE     : 1;            /*!< [4..4] 使能 T_DONE 中断状态控制位                                */
      __IOM uint32_t T_ERR      : 1;            /*!< [5..5] 使能 T_ERR 中断状态控制位                                 */
      __IOM uint32_t RFIFO_HA   : 1;            /*!< [6..6] 使能 RFIFO_HA 中断状态控制位                              */
      __IOM uint32_t TFIFO_LA   : 1;            /*!< [7..7] 使能 TFIFO_LA 中断状态控制位                              */
      __IOM uint32_t RFIFO_OVF  : 1;            /*!< [8..8] 使能 RFIFO_OVF 中断状态控制位                             */
      __IOM uint32_t TFIFO_OVF  : 1;            /*!< [9..9] 使能 TFIFO_OVF 中断状态控制位                             */
      __IOM uint32_t SHTCUT     : 1;            /*!< [10..10] 使能 SHTCUT 中断状态控制位                              */
      __IOM uint32_t T_FNS      : 1;            /*!< [11..11] 使能 T_FNS 中断状态控制位                               */
      __IOM uint32_t R_FNS      : 1;            /*!< [12..12] 使能 R_FNS 中断状态控制位                               */
      __IOM uint32_t CWT_FLG    : 1;            /*!< [13..13] 使能 CWT_FLG 中断状态控制位                             */
      __IOM uint32_t R_SRT      : 1;            /*!< [14..14] 使能 R_SRT 中断状态控制位                               */
    } bit;
  } IES;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000006C) * CTRL2 *                                                  */

    struct {
      __IOM uint32_t TX_EN      : 1;            /*!< [0..0] 使能发送数据控制位
                                                     0:失能
                                                     1:使能                                                                  */
      __IOM uint32_t RX_EN      : 1;            /*!< [1..1] 使能接收数据控制位
                                                     0:失能
                                                     1:使能                                                                  */
      __IM  uint32_t            : 6;
      __IOM uint32_t FST_EN     : 1;            /*!< [8..8] 使能发送第一个字节控制位
                                                     0:第一个字节传输失能
                                                     1:第一个字节发送开始或当 BGT_FLG 置'1'                        */
      __OM  uint32_t FST_RF     : 1;            /*!< [9..9] 写1将刷新 FST_FLG 置1                                         */
      __IOM uint32_t FST_W      : 1;            /*!< [10..10] 发送第一个字节等待块保护时间
                                                     0:第一个字节发送不考虑 BGT_FLG
                                                     1:当发送第一个字节时,等待 BGT_FLG 置”1”                   */
      __IM  uint32_t FST_FLG    : 1;            /*!< [11..11] 发送第一个字节标志位
                                                     0:不传输第一个字节
                                                     1:下面的字节是要传送的第一个字节                           */
      __IOM uint32_t BGTS_SL    : 1;            /*!< [12..12] BGT开始选择控制位
                                                     0:接收开始
                                                     1:接收启动位,更可重新定位                                      */
      __IOM uint32_t CWTS_SL    : 1;            /*!< [13..13] CWT开始选择控制位
                                                     0:接收缓冲器等待或者发送字节结束
                                                     1:接收起始位或发送起始位                                       */
      __IOM uint32_t CWTC_DSA   : 1;            /*!< [14..14] 清除 CWT 计数器控制位
                                                     0:使用发送开始位或接收开始位清除 CWT 计数器
                                                     1:不清除 CWT 计数器                                                 */
      __IM  uint32_t            : 1;
      __IOM uint32_t CWT_EN     : 1;            /*!< [16..16] 接收 CWT 定时器使能控制位
                                                     0:接收 CWT 定时器失能
                                                     1:接收 CWT 定时器使能                                              */
      __OM  uint32_t CWT_ST     : 1;            /*!< [17..17] 写”1”接收 CWT 停止,始终读回”0”                  */
      __OM  uint32_t CWT_SRT    : 1;            /*!< [18..18] 写”1”接收 CWT 开始,始终读回”0”                  */
      __OM  uint32_t CWT_RLD    : 1;            /*!< [19..19] 写”1”接收 CWT 重新装载,始终读回”0”            */
      __IOM uint32_t CWTA_SRT   : 1;            /*!< [20..20] 接收 CWT 自动启动使能控制位
                                                     0:接收 CWT 定时器不会自动启动
                                                     1:当发送”CWTA_SRT”位时,接收 CWT 定时器
                                                     将自动启动                                                           */
      __IM  uint32_t CWT_RNG    : 1;            /*!< [21..21] 接收 CWT 定时器运行状态                                 */
      __IM  uint32_t            : 2;
      __IOM uint32_t BWT_EN     : 1;            /*!< [24..24] 接收 BWT 使能控制位
                                                     0:接收 BWT 定时器失能
                                                     1:接收 BWT 定时器使能                                              */
      __OM  uint32_t BWT_ST     : 1;            /*!< [25..25] 写”1”接收 BWT 停止,始终读回”0”                  */
      __OM  uint32_t BWT_SRT    : 1;            /*!< [26..26] 写”1”接收 BWT 开始,始终读回”0”                  */
      __OM  uint32_t BWT_RLD    : 1;            /*!< [27..27] 写”1”接收 BWT 重新装载,始终读回”0”            */
      __IOM uint32_t BWTA_SRT   : 1;            /*!< [28..28] 接收 BWT 自动启动使能控制位
                                                     0:接收 BWT 定时器不会自动启动
                                                     1:当发送”BWTA_SRT”位时,接收 BWT 定时器
                                                     将自动启动                                                           */
      __IOM uint32_t BWTA_ST    : 1;            /*!< [29..29] 接收 BWT 自动停止使能控制位
                                                     0:接收 BWT 定时器不会自动停止
                                                     1:当发送”BWTA_ST”位时,接收 BWT 定时器将
                                                     自动停止                                                              */
      __IM  uint32_t BWT_RNG    : 1;            /*!< [30..30] 接收 BWT 定时器运行状态                                 */
    } bit;
  } CTRL2;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000070) * CWT_TO *                                                 */

    struct {
      __IOM uint32_t VAL        : 24;           /*!< [23..0] 接收 CWT 超时预设值                                        */
    } bit;
  } CWT_TO;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000074) * CWT_RLD *                                                */

    struct {
      __IOM uint32_t VAL        : 24;           /*!< [23..0] 接收 CWT 重新加载值                                        */
    } bit;
  } CWT_RLD;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000078) * CWT_CNT *                                                */

    struct {
      __IOM uint32_t VAL        : 24;           /*!< [23..0] 接收 CWT 当前计数值                                        */
    } bit;
  } CWT_CNT;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000007C) * STATUS_FSM *                                             */

    struct {
      __IM  uint32_t TX_IDLE    : 1;            /*!< [0..0] TX_IDLE_STATE                                                      */
      __IM  uint32_t TX_STR     : 1;            /*!< [1..1] TX_START_STATE                                                     */
      __IM  uint32_t TX_LD_DTA  : 1;            /*!< [2..2] TX_LOAD_DATA_STATE                                                 */
      __IM  uint32_t TX_DTA     : 1;            /*!< [3..3] TX_DATA_STATE                                                      */
      __IM  uint32_t TX_PRT     : 1;            /*!< [4..4] TX_PARITY_STATE                                                    */
      __IM  uint32_t TX_INT_GAD : 1;            /*!< [5..5] TX_INT_GUARD_STATE                                                 */
      __IM  uint32_t TX_ERR_DET : 1;            /*!< [6..6] TX_ERROR_DETECT_STATE                                              */
      __IM  uint32_t TX_ERR_GAD : 1;            /*!< [7..7] TX_ERROR_GUARD_STATE                                               */
      __IM  uint32_t TX_GAD     : 1;            /*!< [8..8] TX_GUARD_STATE                                                     */
      __IM  uint32_t            : 7;
      __IM  uint32_t RX_IDLE    : 1;            /*!< [16..16] RX_IDLE_STATE                                                    */
      __IM  uint32_t RX_RDY     : 1;            /*!< [17..17] RX_READY_STATE                                                   */
      __IM  uint32_t RX_STR     : 1;            /*!< [18..18] RX_START_STATE                                                   */
      __IM  uint32_t RX_DTA     : 1;            /*!< [19..19] RX_DATA_STATE                                                    */
      __IM  uint32_t RX_PRT     : 1;            /*!< [20..20] RX_PARITY_STATE                                                  */
      __IM  uint32_t RX_PRT_CHK : 1;            /*!< [21..21] RX_PARITY_CHECK_STATE                                            */
      __IM  uint32_t RX_ERR     : 1;            /*!< [22..22] RX_ERROR_STATE                                                   */
      __IM  uint32_t RX_GARD    : 1;            /*!< [23..23] RX_GUARD_STATE                                                   */
      __IM  uint32_t RX_ERR_GAD : 1;            /*!< [24..24] RX_ERROR_GUARD_STATE                                             */
      __IM  uint32_t RX_WAIT    : 1;            /*!< [25..25] RX_WAIT_STATE                                                    */
    } bit;
  } STATUS_FSM;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000080) * BWT_TO *                                                 */

    struct {
      __IOM uint32_t VAL        : 24;           /*!< [23..0] 接收 BWT 超时预设值                                        */
    } bit;
  } BWT_TO;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000084) * BWT_RLD *                                                */

    struct {
      __IOM uint32_t VAL        : 24;           /*!< [23..0] 接收 BWT 重装载值                                           */
    } bit;
  } BWT_RLD;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000088) * BWT_CNT *                                                */

    struct {
      __IOM uint32_t VAL        : 24;           /*!< [23..0] 接收 BWT 当前计数值                                        */
    } bit;
  } BWT_CNT;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000008C) * FIFO_CTRL *                                              */

    struct {
      __IOM uint32_t TL_WTL     : 4;            /*!< [3..0] T_ITEMS <= TL_WTL 时,触发 T
                                                     FIFO_LA 中断
                                                     注意：TL_WTL 为0时,不触发中断                                   */
      __IOM uint32_t RH_WTL     : 4;            /*!< [7..4] FIFO_ITEMS >= RH_WTL 时,触
                                                     发 RFIFO_HA 中断
                                                     注意:RH_WTL 为0时,不触发中断                                     */
      __IM  uint32_t T_ITEMS    : 4;            /*!< [11..8] 发送 FIFO 字节数                                             */
      __IM  uint32_t R_ITEMS    : 4;            /*!< [15..12] 接收 FIFO 字节数                                            */
    } bit;
  } FIFO_CTRL;
} MSCI0_Type;                                   /*!< Size = 144 (0x90)                                                         */



/* =========================================================================================================================== */
/* ================                                           MTIM                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief 32 TIMER (MTIM)
  */

typedef struct {                                /*!< (@ 0x000F0C00) MTIM Structure                                             */

  union {
    __IOM uint32_t reg[18];                     /*!< (@ 0x00000000) period Register                                            */

    struct {
      __IOM uint32_t period     : 32;           /*!< [31..0] period                                                            */
    } bit[18];
  } PERIOD;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000048) pwm Control Register(0~7)                                  */

    struct {
      __IOM uint32_t PWM0EN     : 1;            /*!< [0..0] Enable or disable TIMER                                            */
      __IOM uint32_t PWM0FIR    : 1;            /*!< [1..1] TIMER initial level                                                */
      __IOM uint32_t PWM0MD     : 1;            /*!< [2..2] TIMER mode                                                         */
      __IOM uint32_t PWM0REL    : 1;            /*!< [3..3] TIMER AUTO RELOAD                                                  */
      __IOM uint32_t PWM1EN     : 1;            /*!< [4..4] Enable or disable TIMER1                                           */
      __IOM uint32_t PWM1FIR    : 1;            /*!< [5..5] TIMER initial level                                                */
      __IOM uint32_t PWM1MD     : 1;            /*!< [6..6] TIMER mode                                                         */
      __IOM uint32_t PWM1REL    : 1;            /*!< [7..7] TIMER AUTO RELOAD                                                  */
      __IOM uint32_t PWM2EN     : 1;            /*!< [8..8] Enable or disable TIMER2                                           */
      __IOM uint32_t PWM2FIR    : 1;            /*!< [9..9] TIMER initial level                                                */
      __IOM uint32_t PWM2MD     : 1;            /*!< [10..10] TIMER mode                                                       */
      __IOM uint32_t PWM2REL    : 1;            /*!< [11..11] TIMER AUTO RELOAD                                                */
      __IOM uint32_t PWM3EN     : 1;            /*!< [12..12] Enable or disable TIMER3                                         */
      __IOM uint32_t PWM3FIR    : 1;            /*!< [13..13] TIMER initial level                                              */
      __IOM uint32_t PWM3MD     : 1;            /*!< [14..14] TIMER mode                                                       */
      __IOM uint32_t PWM3REL    : 1;            /*!< [15..15] TIMER AUTO RELOAD                                                */
      __IOM uint32_t PWM4EN     : 1;            /*!< [16..16] Enable or disable TIMER4                                         */
      __IOM uint32_t PWM4FIR    : 1;            /*!< [17..17] TIMER initial level                                              */
      __IOM uint32_t PWM4MD     : 1;            /*!< [18..18] TIMER mode                                                       */
      __IOM uint32_t PWM4REL    : 1;            /*!< [19..19] TIMER AUTO RELOAD                                                */
      __IOM uint32_t PWM5EN     : 1;            /*!< [20..20] Enable or disable TIMER5                                         */
      __IOM uint32_t PWM5FIR    : 1;            /*!< [21..21] TIMER initial level                                              */
      __IOM uint32_t PW5MD      : 1;            /*!< [22..22] TIMER mode                                                       */
      __IOM uint32_t PWM5REL    : 1;            /*!< [23..23] TIMER AUTO RELOAD                                                */
      __IOM uint32_t PWM6EN     : 1;            /*!< [24..24] Enable or disable TIMER6                                         */
      __IOM uint32_t PWM6FIR    : 1;            /*!< [25..25] TIMER initial level                                              */
      __IOM uint32_t PWM6MD     : 1;            /*!< [26..26] TIMER mode                                                       */
      __IOM uint32_t PWM6REL    : 1;            /*!< [27..27] TIMER AUTO RELOAD                                                */
      __IOM uint32_t PWM7EN     : 1;            /*!< [28..28] Enable or disable TIMER7                                         */
      __IOM uint32_t PWM7FIR    : 1;            /*!< [29..29] TIMER initial level                                              */
      __IOM uint32_t PWM7MD     : 1;            /*!< [30..30] TIMER mode                                                       */
      __IOM uint32_t PWM7REL    : 1;            /*!< [31..31] TIMER AUTO RELOAD                                                */
    } bit;
  } CTRL1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) pwm Control Register(8)                                    */

    struct {
      __IOM uint32_t PWM8EN     : 1;            /*!< [0..0] Enable or disable TIMER                                            */
      __IOM uint32_t PWM8FIR    : 1;            /*!< [1..1] TIMER initial level                                                */
      __IOM uint32_t PWM8MD     : 1;            /*!< [2..2] TIMER mode                                                         */
      __IOM uint32_t PWM8REL    : 1;            /*!< [3..3] TIMER AUTO RELOAD                                                  */
      __IOM uint32_t IRQ_EN     : 9;            /*!< [12..4] The timer crresponds to the interrupt enable control
                                                     bit                                                                       */
      __IOM uint32_t IRQ_CLR    : 9;            /*!< [21..13] Clear interrupt control bits                                     */
    } bit;
  } CTRL2;

  union {
    __IM  uint32_t reg[9];                      /*!< (@ 0x00000050) [0..8]                                                     */

    struct {
      __IM  uint32_t cnt        : 32;           /*!< [31..0] cnt                                                               */
    } bit[9];
  } CNT;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000074) pwm IRQ status Register                                    */

    struct {
      __IM  uint32_t PWM_IRQ_PEND : 9;          /*!< [8..0] PWM_IRQ status                                                     */
    } bit;
  } IRQ_NUM;
} MTIM_Type;                                    /*!< Size = 120 (0x78)                                                         */



/* =========================================================================================================================== */
/* ================                                           MCRC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief MCRC (MCRC)
  */

typedef struct {                                /*!< (@ 0x000F8204) MCRC Structure                                             */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * RESULT *                                                 */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] 存放CRC运算的初值及结果                                 */
    } bit;
  } RESULT;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) * MASK *                                                   */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] 计算掩码,不影响CRC最终运算结果                       */
    } bit;
  } MASK;
  __IM  uint32_t  RESERVED[29];

  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000007C) * DATA *                                                   */

    struct {
      __IOM uint16_t VAL        : 16;           /*!< [15..0] 存放参与CRC运算的数据                                    */
    } bit;
  } DATA;
  __IM  uint16_t  RESERVED1;
} MCRC_Type;                                    /*!< Size = 128 (0x80)                                                         */



/* =========================================================================================================================== */
/* ================                                           MRCC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief MRCC (MRCC)
  */

typedef struct {                                /*!< (@ 0x000F8400) MRCC Structure                                             */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * HCLK_CTRL *                                              */

    struct {
      __IM  uint32_t            : 12;
      __IOM uint32_t USB_SEL    : 2;            /*!< [13..12] USB时钟clk_usb选择。
                                                     0: rc192m分频后生成的48M时钟
                                                     1: pll_hsi_48m,切换PLL频率会抖动
                                                     2: pll_hse_48m,切换PLL频率会抖动                                   */
      __IOM uint32_t UART_SEL   : 2;            /*!< [15..14] UART时钟clk_uart选择。
                                                     0: rc192m分频后生成的48M时钟
                                                     1: pll_hsi_48m,切换PLL频率会抖动
                                                     2: pll_hse_48m,切换PLL频率会抖动                                   */
    } bit;
  } HCLK_CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) * PCLK_CTRL *                                              */

    struct {
      __IOM uint32_t SEL        : 2;            /*!< [1..0] PCLK使用的分频值选择
                                                     0: 1分频
                                                     1: 2分频
                                                     2: 4分频
                                                     3: 8分频                                                                */
      __IOM uint32_t DIV_EN     : 1;            /*!< [2..2] PCLK分频使能                                                   */
    } bit;
  } PCLK_CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) * RSA_CLK *                                                */

    struct {
      __IOM uint32_t CLK_CFG    : 4;            /*!< [3..0] 每16个clk_rsa中,前n个可以强制为0,此
                                                     寄存器用于选择n值,从这里输出的时钟最终给到RSA模块1
                                                     : 每16个clk_rsa中,前3个周期强制为0
                                                     2, 4, 5 :每16个clk_rsa中,前2个周期强
                                                     制为0
                                                     3 : 每16个clk_rsa中,第一个强制为0
                                                     6, 7 :clk_rsa输入等于输出
                                                     Others : 每16个clk_rsa中,前7个周期强
                                                     制为0                                                                   */
    } bit;
  } RSA_CLK;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) * CLK_EN *                                                 */

    struct {
      __IOM uint32_t RNG        : 1;            /*!< [0..0] rng数字模块时钟开关                                        */
      __IOM uint32_t QSPI       : 1;            /*!< [1..1] qspi数字模块时钟开关                                       */
      __IOM uint32_t SHA        : 1;            /*!< [2..2] SHA数字模块时钟开关                                        */
      __IOM uint32_t CRC        : 1;            /*!< [3..3] CRC数字模块时钟开关                                        */
      __IOM uint32_t PWM        : 1;            /*!< [4..4] PWM数字模块时钟开关                                        */
      __IOM uint32_t WDT        : 1;            /*!< [5..5] WDT数字模块时钟开关                                        */
      __IOM uint32_t USB        : 1;            /*!< [6..6] USB数字模块时钟开关                                        */
      __IOM uint32_t SPI        : 1;            /*!< [7..7] SPI数字模块时钟开关                                        */
      __IOM uint32_t DES        : 1;            /*!< [8..8] DES数字模块时钟开关                                        */
      __IOM uint32_t RSA        : 1;            /*!< [9..9] RSA数字模块时钟开关                                        */
      __IOM uint32_t AES        : 1;            /*!< [10..10] AES数字模块时钟开关                                      */
      __IOM uint32_t GPIO       : 1;            /*!< [11..11] GPIO数字模块时钟开关                                     */
      __IOM uint32_t SCI0       : 1;            /*!< [12..12] SCI0数字模块时钟开关                                     */
      __IOM uint32_t SCI1       : 1;            /*!< [13..13] SCI1数字模块时钟开关                                     */
      __IOM uint32_t SM4        : 1;            /*!< [14..14] SM4数字模块时钟开关                                      */
      __IOM uint32_t UART       : 1;            /*!< [15..15] UART数字模块时钟开关                                     */
      __IOM uint32_t MSR        : 1;            /*!< [16..16] 7811数字模块时钟开关                                     */
      __IOM uint32_t MSR_ADC    : 1;            /*!< [17..17] 7811_ADC数字模块时钟开关                                 */
      __IM  uint32_t            : 1;
      __IOM uint32_t PSRAM      : 1;            /*!< [19..19] PSRAM数字模块时钟开关                                    */
      __IOM uint32_t HSPI       : 1;            /*!< [20..20] HSPI数字模块时钟开关                                     */
      __IOM uint32_t DAC        : 1;            /*!< [21..21] DAC数字模块时钟开关                                      */
      __IOM uint32_t DCMI       : 1;            /*!< [22..22] DCMI数字模块时钟开关                                     */
      __IOM uint32_t SD         : 1;            /*!< [23..23] SD数字模块时钟开关                                       */
      __IOM uint32_t CHGPUMP    : 1;            /*!< [24..24] CHGPUMP数字模块时钟开关                                  */
      __IOM uint32_t MEMCP      : 1;            /*!< [25..25] MEMCP数字模块时钟开关                                    */
      __IOM uint32_t MPU_DMA    : 1;            /*!< [26..26] MPU_DMA数字模块时钟开关                                  */
      __IOM uint32_t RV_SYS     : 1;            /*!< [27..27] RV_SYS数字模块时钟开关                                   */
      __IOM uint32_t RV_REG     : 1;            /*!< [28..28] RV_REG数字模块时钟开关                                   */
      __IOM uint32_t RC48M      : 1;            /*!< [29..29] RC48M数字模块时钟开关                                    */
    } bit;
  } CLK_EN;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) * MCU_CLK *                                                */

    struct {
      __IOM uint32_t SEL        : 2;            /*!< [1..0] MCU时钟来源选择
                                                     0: rc192m
                                                     1: pll_192M
                                                     2: pll_256M
                                                     3: pll_48M,                                                               */
      __IOM uint32_t RC_32K     : 1;            /*!< [2..2] 为1则使能内部RC32K（LSI）为系统时钟,同
                                                     时屏蔽其他所有的设置                                            */
      __IOM uint32_t DIV_EN     : 1;            /*!< [3..3] 为1则使能MCU时钟分频                                       */
      __IOM uint32_t DIV_SEL    : 1;            /*!< [4..4] MCU时钟分频选择
                                                     0：选择非分频时钟作为 clk_mcu
                                                     1：选择分频时钟作为clk_mcu
                                                     注意：当从'1'变为'0'时,应先设置div_sel为'
                                                     0',延迟至少两个周期,然后清除div_en,不要同时清
                                                     除这两位。当从'0'变为'1'时,应先设置div_en为
                                                     '1',延迟至少两个周期,然后设置                                 */
      __IOM uint32_t RAND_EN    : 1;            /*!< [5..5] 为1则使能MCU时钟随机功能                                 */
      __IM  uint32_t            : 2;
      __IOM uint32_t DIV_LO     : 8;            /*!< [15..8] 输入给MCU的时钟的低电平持续时间 = (DIV
                                                     _LO+1)个clk                                                              */
      __IOM uint32_t DIV_HI     : 8;            /*!< [23..16] 输入给MCU的时钟的低电平持续时间 = (DIV
                                                     _HI +1)个clk                                                             */
      __IOM uint32_t RAND_MASK  : 4;            /*!< [27..24] DIV_HI和DIV_LO会加上(随机数& RA
                                                     ND_MASK)                                                                  */
    } bit;
  } MCU_CLK;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) * PER1_CLK *                                               */

    struct {
      __IOM uint32_t AHB_SEL    : 2;            /*!< [1..0] AHB总线时钟来源选择
                                                     0: CLK_MCU
                                                     1: RC192M
                                                     2: pll_192M
                                                     3: pll_48M                                                                */
      __IM  uint32_t            : 1;
      __IOM uint32_t AHB_RAND_EN : 1;           /*!< [3..3] 为1则使能AHB总线时钟随机功能                           */
      __IOM uint32_t AHB_RAND_MASK : 4;         /*!< [7..4] AHB_DIV_HI和AHB_DIV_LO会加上
                                                     (随机数&AHB_RAND_MASK)                                                 */
      __IOM uint32_t AHB_DIV_LO : 4;            /*!< [11..8] 输入给AHB的时钟的低电平持续时间 = (AHB
                                                     _DIV_LO+1)个clk                                                          */
      __IOM uint32_t AHB_DIV_HI : 4;            /*!< [15..12] 输入给AHB的时钟的高电平持续时间 = (AHB
                                                     _DIV_HI +1)个clk                                                         */
      __IOM uint32_t QSPI_SEL   : 2;            /*!< [17..16] QSPI总线时钟来源选择
                                                     0: CLK_MCU
                                                     1: RC192M
                                                     2: pll_192M
                                                     3: pll_48M                                                                */
      __IM  uint32_t            : 6;
      __IOM uint32_t QSPI_DIV_LO : 4;           /*!< [27..24] 输入给QSPI的时钟的低电平持续时间 = (QS
                                                     PI_DIV_LO+1)个clk                                                        */
      __IOM uint32_t QSPI_DIV_HI : 4;           /*!< [31..28] 输入给QSPI的时钟的低电平持续时间 = (QS
                                                     PI_DIV_HI+1)个clk                                                        */
    } bit;
  } PER1_CLK;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) * PER2_CLK *                                               */

    struct {
      __IOM uint32_t PSRAM_SEL  : 2;            /*!< [1..0] PSRAM总线时钟来源选择
                                                     0: CLK_MCU
                                                     1: RC192M
                                                     2: pll_192M
                                                     3: pll_256M                                                               */
      __IM  uint32_t            : 1;
      __IOM uint32_t PSRAM_PLL_SEL : 1;         /*!< [3..3] PSRAM时钟来源选择
                                                     0: pll_hsi
                                                     1: pll_hse                                                                */
      __IOM uint32_t PSRAM_DIV_SEL : 1;         /*!< [4..4] PSRAM时钟分频选择
                                                     0：选择非分频时钟作为 clk_psram
                                                     1：选择分频时钟作为clk_psram                                     */
      __IOM uint32_t PSRAM_DIV_EN : 1;          /*!< [5..5] 为1则使能PSRAM时钟分频                                     */
      __IM  uint32_t            : 2;
      __IOM uint32_t PSRAM_DIV_LO : 4;          /*!< [11..8] 输入给PSRAM的时钟的低电平持续时间 = (P
                                                     SRAM_DIV_LO+1)个clk                                                      */
      __IOM uint32_t PSRAM_DIV_HI : 4;          /*!< [15..12] 输入给PSRAM的时钟的高电平持续时间 = (P
                                                     SRAM_DIV_HI +1)个clk                                                     */
      __IOM uint32_t HSPI_SEL   : 2;            /*!< [17..16] PSRAM总线时钟来源选择
                                                     0: CLK_MCU
                                                     1: RC192M
                                                     2: pll_192M
                                                     3: pll_256M                                                               */
      __IM  uint32_t            : 1;
      __IOM uint32_t HSPI_PLL_SEL : 1;          /*!< [19..19] HSPI时钟来源选择
                                                     0: pll_hsi
                                                     1: pll_hse                                                                */
      __IOM uint32_t HSPI_DIV_SEL : 1;          /*!< [20..20] HSPI时钟分频选择
                                                     0：选择非分频时钟作为 clk_hspi
                                                     1：选择分频时钟作为 clk_hspi                                     */
      __IOM uint32_t HSPI_DIV_EN : 1;           /*!< [21..21] 为1则使能HSPI时钟分频                                    */
      __IM  uint32_t            : 2;
      __IOM uint32_t HSPI_DIV_LO : 4;           /*!< [27..24] 输入给HSPI的时钟的低电平持续时间 = (HS
                                                     PI_DIV_LO+1)个clk                                                        */
      __IOM uint32_t HSPI_DIV_HI : 4;           /*!< [31..28] 输入给HSPI的时钟的高电平持续时间 = (HS
                                                     PI_DIV_HI +1)个clk                                                       */
    } bit;
  } PER2_CLK;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) * PER3_CLK *                                               */

    struct {
      __IOM uint32_t ICE_SEL    : 2;            /*!< [1..0] ICE时钟来源选择
                                                     0: rc48m
                                                     1: pll_hsi_48m
                                                     2: pll_hse_48m                                                            */
      __IM  uint32_t            : 1;
      __IOM uint32_t ICE_EN     : 1;            /*!< [3..3] ICE时钟分频使能来源选择
                                                     0：选择非分频时钟作为 clk_ice
                                                     1：选择分频时钟作为clk_ice                                       */
      __IOM uint32_t ICE_DIV_LO : 2;            /*!< [5..4] 输入给ICE的时钟的低电平持续时间 = (ICE
                                                     _DIV_LO+1)个clk                                                          */
      __IOM uint32_t ICE_DIV_HI : 2;            /*!< [7..6] 输入给ICE的时钟的高电平持续时间 = (ICE
                                                     _DIV_HI +1)个clk                                                         */
      __IOM uint32_t ADAC_SEL   : 2;            /*!< [9..8] ADAC时钟来源选择
                                                     0: rc48m
                                                     1: pll_hsi_48m
                                                     2: pll_hse_48m                                                            */
      __IM  uint32_t            : 1;
      __IOM uint32_t ADAC_EN    : 1;            /*!< [11..11] ADAC时钟分频使能来源选择
                                                     0：选择非分频时钟作为 clk_adac
                                                     1：选择分频时钟作为clk_adac                                      */
      __IOM uint32_t ADAC_DIV_LO : 2;           /*!< [13..12] 输入给ADAC的时钟的低电平持续时间 = (AD
                                                     AC_DIV_LO+1)个clk                                                        */
      __IOM uint32_t ADAC_DIV_HI : 2;           /*!< [15..14] 输入给ADAC的时钟的高电平持续时间 = (AD
                                                     AC_DIV_HI +1)个clk                                                       */
      __IOM uint32_t GPIO0_SEL  : 2;            /*!< [17..16] GPIO偶数脚时钟输出,需要把偶数的GPIO配置
                                                     成 55:GPIO_CLK_OUT
                                                     0: clk_rc48m
                                                     1: clk_pll_hsi_48m
                                                     2: clk_pll_hse_48m                                                        */
      __IM  uint32_t            : 1;
      __IOM uint32_t GPIO0_EN   : 1;            /*!< [19..19] GPIO偶数脚时钟输出使能                                  */
      __IOM uint32_t GPIO0_DIV_LO : 2;          /*!< [21..20] GPIO偶数脚输出的时钟的低电平持续时间
                                                     = (
                                                     GPIO0_DIV_LO+1)个clk                                                     */
      __IOM uint32_t GPIO0_DIV_HI : 2;          /*!< [23..22] GPIO偶数脚输出的时钟的高电平持续时间
                                                     = (
                                                     GPIO0_DIV_HI+1)个clk                                                     */
      __IOM uint32_t GPIO1_SEL  : 2;            /*!< [25..24] GPIO奇数脚时钟输出,需要把奇数的GPIO配置
                                                     成 55:GPIO_CLK_OUT
                                                     0: clk_rc48m
                                                     1: clk_pll_hsi_48m
                                                     2: clk_pll_hse_48m                                                        */
      __IM  uint32_t            : 1;
      __IOM uint32_t GPIO1_EN   : 1;            /*!< [27..27] GPIO奇数脚时钟输出使能                                  */
      __IOM uint32_t GPIO1_DIV_LO : 2;          /*!< [29..28] GPIO奇数脚输出的时钟的低电平持续时间
                                                     = (
                                                     GPIO1_DIV_LO+1)个clk                                                     */
      __IOM uint32_t GPIO1_DIV_HI : 2;          /*!< [31..30] GPIO奇数脚输出的时钟的高电平持续时间
                                                     = (
                                                     GPIO1_DIV_HI+1)个clk                                                     */
    } bit;
  } PER3_CLK;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) * CLK_PLL_SEL *                                            */

    struct {
      __IOM uint32_t PLL_SEL_LOCK : 1;          /*!< [0..0] 为1后锁定AHB,QSPI,MCU,RSA的时钟
                                                     选择,且无法解锁。                                                 */
      __IM  uint32_t            : 7;
      __IOM uint32_t AHB_PLL_SEL : 4;           /*!< [11..8] AHB的时钟来源选择
                                                     0x5: PLL_HSE
                                                     Others:PLL_HSI                                                            */
      __IM  uint32_t            : 4;
      __IOM uint32_t QSPI_PLL_SEL : 4;          /*!< [19..16] QSPI的时钟来源选择
                                                     0x5: PLL_HSE
                                                     Others:PLL_HSI                                                            */
      __IM  uint32_t            : 4;
      __IOM uint32_t MCU_PLL_SEL : 4;           /*!< [27..24] MCU的时钟来源选择
                                                     0x5: PLL_HSE
                                                     Others:PLL_HSI                                                            */
      __IOM uint32_t RSA_PLL_SEL : 4;           /*!< [31..28] RSA的时钟来源选择
                                                     0x5: PLL_HSE
                                                     Others:PLL_HSI                                                            */
    } bit;
  } CLK_PLL_SEL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) * OSC32K_CALI *                                            */

    struct {
      __IM  uint32_t CNT        : 24;           /*!< [23..0] time所表示的时间长度内,48M时钟计数值
                                                     注意：校准时钟源使用的是clk_gpio1_sel选择的
                                                     48M时钟                                                                 */
      __IOM uint32_t START      : 1;            /*!< [24..24] 校准启动信号
                                                     写'1'后,延迟1us,再写'0',上升沿触发校准开始                 */
      __IM  uint32_t DONE       : 1;            /*!< [25..25] 校准完成信号
                                                     校准开始后,此信号会变成'0',校准完成后,此信号会变为
                                                     '1'                                                                       */
      __IM  uint32_t            : 2;
      __IOM uint32_t TIME       : 4;            /*!< [31..28] 校准持续时长,校准时间长度为(2^cali_ti
                                                     me)个 OSC32K 周期                                                      */
    } bit;
  } OSC32K_CALI;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) * CLK_RSA *                                                */

    struct {
      __IOM uint32_t SEL        : 2;            /*!< [1..0] RSA时钟来源选择
                                                     0: cpu
                                                     1: rc192m
                                                     2: pll_out_norm, (192M)
                                                     3: pll_out_max, (256M)                                                    */
      __IM  uint32_t            : 1;
      __IOM uint32_t RAND_EN    : 1;            /*!< [3..3] RSA时钟随机使能
                                                     0:失能RSA时钟随机
                                                     1:使能RSA时钟随机                                                   */
      __IOM uint32_t RAND_MASK  : 4;            /*!< [7..4] DIV_HI和DIV_LO会加上(随机数& RA
                                                     ND_MASK)                                                                  */
      __IOM uint32_t DIV_LO     : 4;            /*!< [11..8] 输入给RSA的时钟的低电平持续时间 = (DIV
                                                     _LO+1)个clk                                                              */
      __IOM uint32_t DIV_HI     : 4;            /*!< [15..12] 输入给RSA的时钟的高电平持续时间 = (DIV
                                                     _HI+1)个clk                                                              */
    } bit;
  } CLK_RSA;
} MRCC_Type;                                    /*!< Size = 44 (0x2c)                                                          */



/* =========================================================================================================================== */
/* ================                                         MSYSCTRL                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief MSYSCTRL (MSYSCTRL)
  */

typedef struct {                                /*!< (@ 0x000F8520) MSYSCTRL Structure                                         */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * CHGR_EVENT_IRQ *                                         */

    struct {
      __IOM uint32_t VBAT_LV    : 1;            /*!< [0..0] ad_lpm_chgr_state_vbat_l
                                                     v                                                                         */
      __IOM uint32_t RCH_EN     : 1;            /*!< [1..1] ad_lpm_chgr_state_rch_en                                           */
      __IOM uint32_t IND        : 1;            /*!< [2..2] ad_lpm_chgr_state_ind                                              */
      __IOM uint32_t ICHG       : 1;            /*!< [3..3] ad_lpm_chgr_state_ichg                                             */
      __IOM uint32_t RESET      : 1;            /*!< [4..4] ad_lpm_chgr_reset                                                  */
      __IOM uint32_t UVLO_OK_AON : 1;           /*!< [5..5] ad_lpm_chgr_uvlo_ok_aon                                            */
      __IOM uint32_t PGOOD      : 1;            /*!< [6..6] ad_lpm_chgr_pgood                                                  */
      __IOM uint32_t DPPM_OV_CV : 1;            /*!< [7..7] ad_lpm_chgr_dppm_ov_cv                                             */
      __IOM uint32_t DPPM_OV_CC : 1;            /*!< [8..8] ad_lpm_chgr_dppm_ov_cc                                             */
      __IOM uint32_t CC_OV_CV   : 1;            /*!< [9..9] ad_lpm_chgr_cc_ov_cv                                               */
      __IOM uint32_t DET_AON    : 1;            /*!< [10..10] ad_lpm_chgr_in_det_aon                                           */
      __IOM uint32_t VBAT_OV    : 1;            /*!< [11..11] ad_lpm_vbat_ov_flag                                              */
      __IOM uint32_t PWK        : 1;            /*!< [12..12] power key irq                                                    */
      __IM  uint32_t            : 3;
      __IOM uint32_t IE         : 1;            /*!< [16..16] chgr中断使能总开关                                        */
      __IOM uint32_t EVENT0_EN  : 1;            /*!< [17..17] chgr_event[9:0]事件检测使能,使能
                                                     中断前必须先使能这一比特                                      */
      __IOM uint32_t EVENT1_EN  : 1;            /*!< [18..18] chgr_event[11:10]事件检测使能,
                                                     使能中断前必须先使能这一比特,power_key一直使能
                                                     ,无法更改                                                             */
    } bit;
  } CHGR_EVENT_IRQ;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) * CHGR_EVENT_ICTRL *                                       */

    struct {
      __IOM uint32_t VBAT_LV_IE : 1;            /*!< [0..0] ad_lpm_chgr_state_vbat_l
                                                     v 中断使能
                                                     0: 禁止
                                                     1: 使能                                                                 */
      __IM  uint32_t RCH_EN_IE  : 1;            /*!< [1..1] ad_lpm_chgr_state_rch_en                                           */
      __IOM uint32_t IND_IE     : 1;            /*!< [2..2] ad_lpm_chgr_state_ind                                              */
      __IM  uint32_t ICHG_IE    : 1;            /*!< [3..3] ad_lpm_chgr_state_ichg                                             */
      __IOM uint32_t RESET_IE   : 1;            /*!< [4..4] ad_lpm_chgr_reset                                                  */
      __IM  uint32_t UVLO_OK_AON_IE : 1;        /*!< [5..5] ad_lpm_chgr_uvlo_ok_aon                                            */
      __IOM uint32_t PGOOD_IE   : 1;            /*!< [6..6] ad_lpm_chgr_pgood                                                  */
      __IM  uint32_t DPPM_OV_CV_IE : 1;         /*!< [7..7] ad_lpm_chgr_dppm_ov_cv                                             */
      __IOM uint32_t DPPM_OV_CC_IE : 1;         /*!< [8..8] ad_lpm_chgr_dppm_ov_cc                                             */
      __IM  uint32_t CC_OV_CV_IE : 1;           /*!< [9..9] ad_lpm_chgr_cc_ov_cv                                               */
      __IOM uint32_t DET_AON_IE : 1;            /*!< [10..10] ad_lpm_chgr_in_det_aon                                           */
      __IM  uint32_t VBAT_OV_IE : 1;            /*!< [11..11] ad_lpm_vbat_ov_flag                                              */
      __IOM uint32_t PWK_IE     : 1;            /*!< [12..12] power_key                                                        */
      __IM  uint32_t            : 3;
      __IOM uint32_t VBAT_LV_IT : 1;            /*!< [16..16] ad_lpm_chgr_state_vbat_l
                                                     v 中断类型
                                                     0: 低电平
                                                     1: 高电平                                                              */
      __IM  uint32_t RCH_EN_IT  : 1;            /*!< [17..17] ad_lpm_chgr_state_rch_en                                         */
      __IOM uint32_t IND_IT     : 1;            /*!< [18..18] ad_lpm_chgr_state_ind                                            */
      __IM  uint32_t ICHG_IT    : 1;            /*!< [19..19] ad_lpm_chgr_state_ichg                                           */
      __IOM uint32_t RESET_IT   : 1;            /*!< [20..20] ad_lpm_chgr_reset                                                */
      __IM  uint32_t UVLO_OK_AON_IT : 1;        /*!< [21..21] ad_lpm_chgr_uvlo_ok_aon                                          */
      __IOM uint32_t PGOOD_IT   : 1;            /*!< [22..22] ad_lpm_chgr_pgood                                                */
      __IM  uint32_t DPPM_OV_CV_IT : 1;         /*!< [23..23] ad_lpm_chgr_dppm_ov_cv                                           */
      __IOM uint32_t DPPM_OV_CC_IT : 1;         /*!< [24..24] ad_lpm_chgr_dppm_ov_cc                                           */
      __IM  uint32_t CC_OV_CV_IT : 1;           /*!< [25..25] ad_lpm_chgr_cc_ov_cv                                             */
      __IOM uint32_t DET_AON_IT : 1;            /*!< [26..26] ad_lpm_chgr_in_det_aon                                           */
      __IM  uint32_t VBAT_OV_IT : 1;            /*!< [27..27] ad_lpm_vbat_ov_flag                                              */
      __IOM uint32_t PWK_IT     : 1;            /*!< [28..28] power_key                                                        */
    } bit;
  } CHGR_EVENT_ICTRL;
  __IOM uint32_t  RNG_CTRL;                     /*!< (@ 0x00000008) * RNG_CTRL *                                               */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) * RNG_DATA0 *                                              */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] 访问此寄存器可以获得随机数                           */
    } bit;
  } RNG_DATA0;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) * RNG_DATA1 *                                              */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] 访问此寄存器可以获得随机数                           */
    } bit;
  } RNG_DATA1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) * RNG_DATA2 *                                              */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] 访问此寄存器可以获得随机数                           */
    } bit;
  } RNG_DATA2;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) * RNG_DATA3 *                                              */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] 访问此寄存器可以获得随机数                           */
    } bit;
  } RNG_DATA3;

  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000001C) * rom_switch *                                             */

    struct {
      __IOM uint8_t ROM_SW      : 1;            /*!< [0..0] 写1后置位,写0无效,模块复位后,恢复到0。(产
                                                     品阶段固定为1)
                                                     锁定的寄存器：
                                                     ALARM_EN
                                                     BTM_EN
                                                     gpio_ICE
                                                     gpio_SWDAT
                                                     sfr_ramkey_sel
                                                     sfr_medcon_wr
                                                     QAES regs                                                                 */
      __IOM uint8_t LOCK_SEC    : 1;            /*!< [1..1] loc_sec                                                            */
      __IM  uint8_t             : 1;
      __IOM uint8_t DEBUG_EN    : 1;            /*!< [3..3] 使能DEBUG功能(产品阶段固定为0)
                                                     0: 失能debug功能;
                                                     1: 使能debug功能                                                      */
      __IOM uint8_t LOCK_OTP    : 1;            /*!< [4..4] lock_otp
                                                     写1锁定寄存器 sfr_otphid_addr / sf
                                                     r_otpuser_addr                                                            */
      __IOM uint8_t LOCK_ANA    : 1;            /*!< [5..5] 锁定模拟寄存器                                              */
      __IOM uint8_t SRAM_NEXE   : 1;            /*!< [6..6] RAM不能跑程序,写0无效(产品阶段固定为1)              */
      __IOM uint8_t ALARM_EN    : 1;            /*!< [7..7] 报警使能
                                                     1：使能报警
                                                     0：失能报警                                                          */
    } bit;
  } rom_switch;
  __IM  uint8_t   RESERVED;
  __IM  uint16_t  RESERVED1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) * LPM_BUSY_CFG *                                           */

    struct {
      __IOM uint32_t RTC_EN     : 1;            /*!< [0..0] 0: 总线访问RTC时,不等待RTC完成直接返回
                                                     ,软件查询STATE标志确定是否访问完成
                                                     1: 总线访问RTC时,等待LPM访问完成才释放总线,软
                                                     件无须查询STATE标志                                                */
      __IOM uint32_t LPM_EN     : 1;            /*!< [1..1] 0: 总线访问LPM时,不等待LPM完成直接返回
                                                     ,软件查询STATE标志确定是否访问完成
                                                     1: 总线访问LPM时,等待LPM访问完成才释放总线,软
                                                     件无须查询STATE标志                                                */
      __IM  uint32_t RTC_STATE  : 1;            /*!< [2..2] 0: rtc access finish
                                                     1: rtc access ongoing                                                     */
      __IM  uint32_t LPM_STATE  : 1;            /*!< [3..3] 0: lpm access finish
                                                     1: lpm access ongoing                                                     */
      __IM  uint32_t AON_STATE  : 1;            /*!< [4..4] 0: lpm/rtc register acce
                                                     ss finish
                                                     1: lpm/rtc register access o
                                                     ngoing                                                                    */
    } bit;
  } LPM_BUSY_CFG;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) * LPM_RDATA *                                              */

    struct {
      __IM  uint32_t RDATA      : 32;           /*!< [31..0] lpm access read data                                              */
    } bit;
  } LPM_RDATA;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) * RTC_RDATA *                                              */

    struct {
      __IM  uint32_t RDATA      : 32;           /*!< [31..0] rtc access read data                                              */
    } bit;
  } RTC_RDATA;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) * AON_RDATA *                                              */

    struct {
      __IM  uint32_t RDATA      : 32;           /*!< [31..0] lpm/rtc access read data
                                                     , the last read value of lpm
                                                     or rtc                                                                    */
    } bit;
  } AON_RDATA;
  __IM  uint32_t  RESERVED2[4];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000040) * pwk_state *                                              */

    struct {
      __IM  uint32_t STATE      : 1;            /*!< [0..0] POWER_KEY按键状态                                              */
    } bit;
  } pwk_state;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000044) * VIO_IRQ *                                                */

    struct {
      __IOM uint32_t IE         : 1;            /*!< [0..0] vio 中断总开关                                                */
      __IOM uint32_t VIO0_EN    : 1;            /*!< [1..1] vio0 pgood 中断开关                                            */
      __IOM uint32_t VIO1_EN    : 1;            /*!< [2..2] vio1 pgood 中断开关                                            */
      __IM  uint32_t            : 1;
      __IM  uint32_t IRQ_STATE  : 1;            /*!< [4..4] vio pgood 中断总状态
                                                     1: vio0或vio1其中之一电压低于配置值                           */
      __IOM uint32_t VIO0_IRQ   : 1;            /*!< [5..5] vio pgood irq 状态
                                                     1: vio 电压低于配置值,vio_pgood由高变为
                                                     低                                                                       */
      __IOM uint32_t VIO1_IRQ   : 1;            /*!< [6..6] vio1 pgood irq 状态
                                                     1: vio1 电压低于配置值,vio1_pgood由高
                                                     变为低                                                                 */
      __IM  uint32_t            : 1;
      __IM  uint32_t VIO0_STATUS : 1;           /*!< [8..8] vio pgood状态
                                                     1: vio 电源电压正常
                                                     0: vio电源电压低于设定值                                         */
      __IM  uint32_t VIO1_STATUS : 1;           /*!< [9..9] vio1 pgood状态
                                                     1: vio1 电源电压正常
                                                     0: vio1电源电压低于设定值                                        */
    } bit;
  } VIO_IRQ;
} MSYSCTRL_Type;                                /*!< Size = 72 (0x48)                                                          */



/* =========================================================================================================================== */
/* ================                                          MRSTGEN                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief MRSTGEN (MRSTGEN)
  */

typedef struct {                                /*!< (@ 0x000F8574) MRSTGEN Structure                                          */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * RST_EN *                                                 */

    struct {
      __IOM uint32_t SOFT       : 1;            /*!< [0..0] 1: 使能软件复位功能                                        */
      __IOM uint32_t WDT        : 1;            /*!< [1..1] 1: 使能看门狗复位功能                                     */
      __IM  uint32_t            : 2;
      __IOM uint32_t VDDSEC_U   : 1;            /*!< [4..4] 1: 使能安全域电源1.2v输出低压自检复位功能         */
      __IOM uint32_t VSEC_O     : 1;            /*!< [5..5] 1: 使能锂电池3.3v输出高压自检复位功能               */
      __IOM uint32_t VSEC_U     : 1;            /*!< [6..6] 1: 使能锂电池3.3v输出低压自检复位功能               */
      __IOM uint32_t DVDD_U     : 1;            /*!< [7..7] 1: 使能纽扣电池1.2v输出低压自检复位功能            */
      __IOM uint32_t VBUT_O     : 1;            /*!< [8..8] 1: 使能纽扣电池3.3v输出高压自检复位功能            */
      __IOM uint32_t VBUT_U     : 1;            /*!< [9..9] 1: 使能纽扣电池3.3v输出低压自检复位功能            */
      __IOM uint32_t TS_O       : 1;            /*!< [10..10] 1: 使能高温自检复位功能                                */
      __IOM uint32_t TS_U       : 1;            /*!< [11..11] 1: 使能低温自检复位功能                                */
      __IM  uint32_t            : 4;
      __IOM uint32_t GPIO_SEL   : 1;            /*!< [16..16] 复位GPIO选择
                                                     0: ice_rst/m0_dbg_rst复位外设时,不
                                                     复位GPIO
                                                     1: ice_rst/m0_dbg_rst复位外设时,复
                                                     位GPIO                                                                   */
    } bit;
  } RST_EN;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) * RST_TYPE *                                               */

    struct {
      __IOM uint32_t SOFT       : 1;            /*!< [0..0] 软件可读写,若对应的复位信号触发,则硬件自动置1
                                                     ,清0需由软件完成。                                                */
      __IOM uint32_t WDT        : 1;            /*!< [1..1] 软件可读写,若对应的复位信号触发,则硬件自动置1
                                                     ,清0需由软件完成。                                                */
      __IM  uint32_t            : 2;
      __IOM uint32_t VDDSEC_U   : 1;            /*!< [4..4] 软件可读写,若对应的复位信号触发,则硬件自动置1
                                                     ,清0需由软件完成。                                                */
      __IOM uint32_t VSEC_O     : 1;            /*!< [5..5] 软件可读写,若对应的复位信号触发,则硬件自动置1
                                                     ,清0需由软件完成。                                                */
      __IOM uint32_t VSEC_U     : 1;            /*!< [6..6] 软件可读写,若对应的复位信号触发,则硬件自动置1
                                                     ,清0需由软件完成。                                                */
      __IOM uint32_t DVDD_U     : 1;            /*!< [7..7] 软件可读写,若对应的复位信号触发,则硬件自动置1
                                                     ,清0需由软件完成。                                                */
      __IOM uint32_t VBUT_O     : 1;            /*!< [8..8] 软件可读写,若对应的复位信号触发,则硬件自动置1
                                                     ,清0需由软件完成。                                                */
      __IOM uint32_t VBUT_U     : 1;            /*!< [9..9] 软件可读写,若对应的复位信号触发,则硬件自动置1
                                                     ,清0需由软件完成。                                                */
      __IOM uint32_t TS_O       : 1;            /*!< [10..10] 软件可读写,若对应的复位信号触发,则硬件自动置1
                                                     ,清0需由软件完成。                                                */
      __IOM uint32_t TS_U       : 1;            /*!< [11..11] 软件可读写,若对应的复位信号触发,则硬件自动置1
                                                     ,清0需由软件完成。                                                */
    } bit;
  } RST_TYPE;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) * RESET *                                                  */

    struct {
      __OM  uint32_t RESET      : 8;            /*!< [7..0] 复位使能:
                                                     写入 '0x55' ,触发软件复位,sw_rst
                                                     写入 '0x50' ,触发软件复位,ic_rst
                                                     写入 '0xAB“ ,触发sci复位,rst_sci
                                                     写入 '0xAE“ ,触发sci2复位,rst_sci_
                                                     2
                                                     写入 '0xC3' ,触发7811复位,rst_7811                                  */
    } bit;
  } RESET;
} MRSTGEN_Type;                                 /*!< Size = 12 (0xc)                                                           */



/* =========================================================================================================================== */
/* ================                                          MSECURE                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief MSECURE (MSECURE)
  */

typedef struct {                                /*!< (@ 0x000F85C0) MSECURE Structure                                          */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * CTRL *                                                   */

    struct {
      __IOM uint32_t SEC_EN     : 8;            /*!< [7..0] 1: sensor检测使能。
                                                     [7]: 低温自检,ad_ts_uth/uthb
                                                     [6]: 高温自检,ad_ts_oth/othb
                                                     [5]: 纽扣电池3.3v输出低压自检,ad_vbat_
                                                     uvh/uvhb
                                                     [4]: 纽扣电池3.3v输出高压自检,ad_vbat_
                                                     ovh/ovhb
                                                     [3]: 纽扣电池1.2v输出低压自检,ad_dvddl
                                                     pm_uvh/uvhb
                                                     [2]: 锂电池3.3v输出低压自检,ad_vsec_u
                                                     v/uvb
                                                     [1]: 锂电池3.3v输出高压自检,ad_vsec_o
                                                     v/ovb
                                                     [0]: 安全域电源1.2v输出低压自检,ad_vdds
                                                     ec_uv/uvb                                                                 */
      __IOM uint32_t THRESHOLD  : 4;            /*!< [11..8] sensor检测警报持续时间门限,大于此门限发出
                                                     警报,否则不报警。
                                                     时间门限值: (2^sensor_delay)*hclk                                    */
    } bit;
  } CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) * result *                                                 */

    struct {
      __IM  uint32_t            : 1;
      __IM  uint32_t STATE      : 8;            /*!< [8..1] 1: 对应检测项报警。
                                                     [8]: 低温自检警报
                                                     [7]: 高温自检警报
                                                     [6]: 纽扣电池3.3v输出低压自检警报
                                                     [5]: 纽扣电池3.3v输出高压自检警报
                                                     [4]: 纽扣电池1.2v输出低压自检警报
                                                     [3]: 锂电池3.3v输出低压自检警报
                                                     [2]: 锂电池3.3v输出高压自检警报
                                                     [1]: 安全域电源1.2v输出低压自检警报                          */
      __IM  uint32_t VDDSEC_UVH : 1;            /*!< [9..9] 安全域电源1.2v输出低压自检电路结果输出            */
      __IM  uint32_t VDDSEC_UHVB : 1;           /*!< [10..10] 安全域电源1.2v输出低压自检电路结果输出          */
      __IM  uint32_t VSEC_OVH   : 1;            /*!< [11..11] 锂电池3.3v输出高压自检电路结果输出                */
      __IM  uint32_t VSEC_OVHB  : 1;            /*!< [12..12] 锂电池3.3v输出高压自检电路结果输出                */
      __IM  uint32_t VSEC_UVH   : 1;            /*!< [13..13] 锂电池3.3v输出低压自检电路结果输出                */
      __IM  uint32_t VSEC_UHVB  : 1;            /*!< [14..14] 锂电池3.3v输出低压自检电路结果输出                */
      __IM  uint32_t DVDDLPM_UVH : 1;           /*!< [15..15] 纽扣电池1.2v输出低压自检电路结果输出             */
      __IM  uint32_t DVDDLPM_UVHB : 1;          /*!< [16..16] 纽扣电池1.2v输出低压自检电路结果输出             */
      __IM  uint32_t VBUT_OVH   : 1;            /*!< [17..17] 纽扣电池3.3v输出高压自检电路结果输出             */
      __IM  uint32_t VBUT_OVHB  : 1;            /*!< [18..18] 纽扣电池3.3v输出高压自检电路结果输出             */
      __IM  uint32_t VBUT_UVH   : 1;            /*!< [19..19] 纽扣电池3.3v输出低压自检电路结果输出             */
      __IM  uint32_t VBUT_UVHB  : 1;            /*!< [20..20] 纽扣电池3.3v输出低压自检电路结果输出             */
      __IM  uint32_t TS_OTH     : 1;            /*!< [21..21] 高温自检电路结果输出                                   */
      __IM  uint32_t TS_OTHB    : 1;            /*!< [22..22] 高温自检电路结果输出                                   */
      __IM  uint32_t TS_UTH     : 1;            /*!< [23..23] 低温自检电路结果输出                                   */
      __IM  uint32_t TS_UTHB    : 1;            /*!< [24..24] 低温自检电路结果输出                                   */
    } bit;
  } result;
  __IM  uint32_t  RESERVED[2];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) * RTC_IE *                                                 */

    struct {
      __IOM uint32_t LSI_IE     : 1;            /*!< [0..0] 1: enable rtc_lsi irq                                              */
      __IOM uint32_t LSE_IE     : 1;            /*!< [1..1] 1: enable rtc_lse irq                                              */
      __IM  uint32_t            : 14;
      __IM  uint32_t LSI_IRQ    : 1;            /*!< [16..16] rtc_lsi_irq flag, 仅指中断标志
                                                     ,清除需要使用RTC_LSI寄存器                                       */
      __IM  uint32_t LSE_IRQ    : 1;            /*!< [17..17] rtc_lse_irq flag, 仅指中断标志
                                                     ,清除需要使用RTC_LSE寄存器                                       */
    } bit;
  } RTC_IE;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) * IE *                                                     */

    struct {
      __IOM uint32_t IE         : 1;            /*!< [0..0] SEC中断总开关
                                                     both lpm security events and
                                                     core security events will t
                                                     rigger secure_irq                                                         */
      __IOM uint32_t CORE_IE    : 1;            /*!< [1..1] CORE SEC中断开关
                                                     1: enable core security even
                                                     t interrupt                                                               */
      __IM  uint32_t            : 14;
      __IM  uint32_t LPM_IRQ    : 1;            /*!< [16..16] lpm security irq status                                          */
    } bit;
  } IE;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) * SENSOR_CTRL *                                            */

    struct {
      __IOM uint32_t VSEC_EN    : 4;            /*!< [3..0] 0x5, disable sensor, els
                                                     e enable sensor                                                           */
      __IOM uint32_t VDDSEC_EN  : 4;            /*!< [7..4] 0x5, disable sensor, els
                                                     e enable sensor                                                           */
      __IM  uint32_t            : 8;
      __IOM uint32_t VSEC_L_SEL : 4;            /*!< [19..16] threshold voltage select
                                                     ion(sim tt 50deg, voltage fr
                                                     om low to high):
                                                     0000: 1.938
                                                     0001: 1.971
                                                     0010: 2.005
                                                     0011: 2.040
                                                     0100: 2.076
                                                     0101: 2.113
                                                     0110: 2.152
                                                     0111: 2.193
                                                     1000: 2.235
                                                     1001: 2.278
                                                     1010: 2.324
                                                     1011: 2.371
                                                     1100: 2.420
                                                     1101: 2.471
                                                     1110: 2.525
                                                     1111: 2.580                                                               */
      __IOM uint32_t VSEC_H_SEL : 4;            /*!< [23..20] threshold voltage select
                                                     ion(sim tt 50deg, voltage fr
                                                     om low to high):
                                                     0000: 3.369
                                                     0001: 3.419
                                                     0010: 3.469
                                                     0011: 3.522
                                                     0100: 3.576
                                                     0101: 3.631
                                                     0110: 3.688
                                                     0111: 3.748
                                                     1000: 3.809
                                                     1001: 3.872
                                                     1010: 3.937
                                                     1011: 4.005
                                                     1100: 4.074
                                                     1101: 4.147
                                                     1110: 4.222
                                                     1111: 4.299                                                               */
      __IOM uint32_t VDDSEC_SEL : 4;            /*!< [27..24] threshold voltage select
                                                     ion(sim tt 50deg, voltage fr
                                                     om low to high):
                                                     0000: 867mV
                                                     0001: 887mV
                                                     0010: 907mV
                                                     0011: 927mV
                                                     0100: 947mV
                                                     0101: 967mV
                                                     0110: 987mV
                                                     0111: 1005mV
                                                     1000: 1025mV
                                                     1001: 1045mV
                                                     1010: 1065mV
                                                     1011: 1085mV
                                                     1100: 1105mV
                                                     1101: 1125mV
                                                     1110: 1145mV
                                                     1111: 1165mV                                                              */
    } bit;
  } SENSOR_CTRL;
} MSECURE_Type;                                 /*!< Size = 28 (0x1c)                                                          */



/* =========================================================================================================================== */
/* ================                                           MGPIO                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief 8 GPIO (MGPIO)
  */

typedef struct {                                /*!< (@ 0x000F8700) MGPIO Structure                                            */

  union {
    __IOM uint8_t reg[80];                      /*!< (@ 0x00000000) [0..79]                                                    */

    struct {
      __IOM uint8_t FUNC        : 6;            /*!< [5..0] GPIO function                                                      */
      __IOM uint8_t MODE        : 2;            /*!< [7..6] GPIO mode                                                          */
    } bit[80];
  } CTRL;
  __IM  uint16_t  RESERVED[24];

  union {
    __IOM uint16_t reg[5];                      /*!< (@ 0x00000080) [0..4]                                                     */

    struct {
      __IOM uint16_t PIN0       : 1;            /*!< [0..0] PIN0                                                               */
      __IOM uint16_t PIN1       : 1;            /*!< [1..1] PIN1                                                               */
      __IOM uint16_t PIN2       : 1;            /*!< [2..2] PIN2                                                               */
      __IOM uint16_t PIN3       : 1;            /*!< [3..3] PIN3                                                               */
      __IOM uint16_t PIN4       : 1;            /*!< [4..4] PIN4                                                               */
      __IOM uint16_t PIN5       : 1;            /*!< [5..5] PIN5                                                               */
      __IOM uint16_t PIN6       : 1;            /*!< [6..6] PIN6                                                               */
      __IOM uint16_t PIN7       : 1;            /*!< [7..7] PIN7                                                               */
      __IOM uint16_t PIN8       : 1;            /*!< [8..8] PIN8                                                               */
      __IOM uint16_t PIN9       : 1;            /*!< [9..9] PIN9                                                               */
      __IOM uint16_t PIN10      : 1;            /*!< [10..10] PIN10                                                            */
      __IOM uint16_t PIN11      : 1;            /*!< [11..11] PIN11                                                            */
      __IOM uint16_t PIN12      : 1;            /*!< [12..12] PIN12                                                            */
      __IOM uint16_t PIN13      : 1;            /*!< [13..13] PIN13                                                            */
      __IOM uint16_t PIN14      : 1;            /*!< [14..14] PIN14                                                            */
      __IOM uint16_t PIN15      : 1;            /*!< [15..15] PIN15                                                            */
    } bit[5];
  } INTR;
  __IM  uint16_t  RESERVED1[3];

  union {
    __IOM uint16_t reg[5];                      /*!< (@ 0x00000090) [0..4]                                                     */

    struct {
      __IOM uint16_t PIN0       : 1;            /*!< [0..0] PIN0                                                               */
      __IOM uint16_t PIN1       : 1;            /*!< [1..1] PIN1                                                               */
      __IOM uint16_t PIN2       : 1;            /*!< [2..2] PIN2                                                               */
      __IOM uint16_t PIN3       : 1;            /*!< [3..3] PIN3                                                               */
      __IOM uint16_t PIN4       : 1;            /*!< [4..4] PIN4                                                               */
      __IOM uint16_t PIN5       : 1;            /*!< [5..5] PIN5                                                               */
      __IOM uint16_t PIN6       : 1;            /*!< [6..6] PIN6                                                               */
      __IOM uint16_t PIN7       : 1;            /*!< [7..7] PIN7                                                               */
      __IOM uint16_t PIN8       : 1;            /*!< [8..8] PIN8                                                               */
      __IOM uint16_t PIN9       : 1;            /*!< [9..9] PIN9                                                               */
      __IOM uint16_t PIN10      : 1;            /*!< [10..10] PIN10                                                            */
      __IOM uint16_t PIN11      : 1;            /*!< [11..11] PIN11                                                            */
      __IOM uint16_t PIN12      : 1;            /*!< [12..12] PIN12                                                            */
      __IOM uint16_t PIN13      : 1;            /*!< [13..13] PIN13                                                            */
      __IOM uint16_t PIN14      : 1;            /*!< [14..14] PIN14                                                            */
      __IOM uint16_t PIN15      : 1;            /*!< [15..15] PIN15                                                            */
    } bit[5];
  } IRQ_LEVEL;
  __IM  uint16_t  RESERVED2[3];

  union {
    __IOM uint16_t reg[5];                      /*!< (@ 0x000000A0) [0..4]                                                     */

    struct {
      __IOM uint16_t PIN0       : 1;            /*!< [0..0] PIN0                                                               */
      __IOM uint16_t PIN1       : 1;            /*!< [1..1] PIN1                                                               */
      __IOM uint16_t PIN2       : 1;            /*!< [2..2] PIN2                                                               */
      __IOM uint16_t PIN3       : 1;            /*!< [3..3] PIN3                                                               */
      __IOM uint16_t PIN4       : 1;            /*!< [4..4] PIN4                                                               */
      __IOM uint16_t PIN5       : 1;            /*!< [5..5] PIN5                                                               */
      __IOM uint16_t PIN6       : 1;            /*!< [6..6] PIN6                                                               */
      __IOM uint16_t PIN7       : 1;            /*!< [7..7] PIN7                                                               */
      __IOM uint16_t PIN8       : 1;            /*!< [8..8] PIN8                                                               */
      __IOM uint16_t PIN9       : 1;            /*!< [9..9] PIN9                                                               */
      __IOM uint16_t PIN10      : 1;            /*!< [10..10] PIN10                                                            */
      __IOM uint16_t PIN11      : 1;            /*!< [11..11] PIN11                                                            */
      __IOM uint16_t PIN12      : 1;            /*!< [12..12] PIN12                                                            */
      __IOM uint16_t PIN13      : 1;            /*!< [13..13] PIN13                                                            */
      __IOM uint16_t PIN14      : 1;            /*!< [14..14] PIN14                                                            */
      __IOM uint16_t PIN15      : 1;            /*!< [15..15] PIN15                                                            */
    } bit[5];
  } IRQ_RISE;
  __IM  uint16_t  RESERVED3[3];

  union {
    __IOM uint16_t reg[5];                      /*!< (@ 0x000000B0) [0..4]                                                     */

    struct {
      __IOM uint16_t PIN0       : 1;            /*!< [0..0] PIN0                                                               */
      __IOM uint16_t PIN1       : 1;            /*!< [1..1] PIN1                                                               */
      __IOM uint16_t PIN2       : 1;            /*!< [2..2] PIN2                                                               */
      __IOM uint16_t PIN3       : 1;            /*!< [3..3] PIN3                                                               */
      __IOM uint16_t PIN4       : 1;            /*!< [4..4] PIN4                                                               */
      __IOM uint16_t PIN5       : 1;            /*!< [5..5] PIN5                                                               */
      __IOM uint16_t PIN6       : 1;            /*!< [6..6] PIN6                                                               */
      __IOM uint16_t PIN7       : 1;            /*!< [7..7] PIN7                                                               */
      __IOM uint16_t PIN8       : 1;            /*!< [8..8] PIN8                                                               */
      __IOM uint16_t PIN9       : 1;            /*!< [9..9] PIN9                                                               */
      __IOM uint16_t PIN10      : 1;            /*!< [10..10] PIN10                                                            */
      __IOM uint16_t PIN11      : 1;            /*!< [11..11] PIN11                                                            */
      __IOM uint16_t PIN12      : 1;            /*!< [12..12] PIN12                                                            */
      __IOM uint16_t PIN13      : 1;            /*!< [13..13] PIN13                                                            */
      __IOM uint16_t PIN14      : 1;            /*!< [14..14] PIN14                                                            */
      __IOM uint16_t PIN15      : 1;            /*!< [15..15] PIN15                                                            */
    } bit[5];
  } IRQ_FALL;
  __IM  uint16_t  RESERVED4[3];

  union {
    __IOM uint16_t reg[5];                      /*!< (@ 0x000000C0) [0..4]                                                     */

    struct {
      __IOM uint16_t PIN0       : 1;            /*!< [0..0] PIN0                                                               */
      __IOM uint16_t PIN1       : 1;            /*!< [1..1] PIN1                                                               */
      __IOM uint16_t PIN2       : 1;            /*!< [2..2] PIN2                                                               */
      __IOM uint16_t PIN3       : 1;            /*!< [3..3] PIN3                                                               */
      __IOM uint16_t PIN4       : 1;            /*!< [4..4] PIN4                                                               */
      __IOM uint16_t PIN5       : 1;            /*!< [5..5] PIN5                                                               */
      __IOM uint16_t PIN6       : 1;            /*!< [6..6] PIN6                                                               */
      __IOM uint16_t PIN7       : 1;            /*!< [7..7] PIN7                                                               */
      __IOM uint16_t PIN8       : 1;            /*!< [8..8] PIN8                                                               */
      __IOM uint16_t PIN9       : 1;            /*!< [9..9] PIN9                                                               */
      __IOM uint16_t PIN10      : 1;            /*!< [10..10] PIN10                                                            */
      __IOM uint16_t PIN11      : 1;            /*!< [11..11] PIN11                                                            */
      __IOM uint16_t PIN12      : 1;            /*!< [12..12] PIN12                                                            */
      __IOM uint16_t PIN13      : 1;            /*!< [13..13] PIN13                                                            */
      __IOM uint16_t PIN14      : 1;            /*!< [14..14] PIN14                                                            */
      __IOM uint16_t PIN15      : 1;            /*!< [15..15] PIN15                                                            */
    } bit[5];
  } IRQ_STATUS;
  __IM  uint16_t  RESERVED5[2];
  __IM  uint8_t   RESERVED6;

  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000CF) GPIO_IRQ_INDEX register                                    */

    struct {
      __IM  uint8_t INDEX       : 8;            /*!< [7..0] GPIO_IRQ_INDEX                                                     */
    } bit;
  } IRQ_NUM;

  union {
    __IOM uint16_t reg[5];                      /*!< (@ 0x000000D0) [0..4]                                                     */

    struct {
      __IOM uint16_t PIN0       : 1;            /*!< [0..0] PIN0                                                               */
      __IOM uint16_t PIN1       : 1;            /*!< [1..1] PIN1                                                               */
      __IOM uint16_t PIN2       : 1;            /*!< [2..2] PIN2                                                               */
      __IOM uint16_t PIN3       : 1;            /*!< [3..3] PIN3                                                               */
      __IOM uint16_t PIN4       : 1;            /*!< [4..4] PIN4                                                               */
      __IOM uint16_t PIN5       : 1;            /*!< [5..5] PIN5                                                               */
      __IOM uint16_t PIN6       : 1;            /*!< [6..6] PIN6                                                               */
      __IOM uint16_t PIN7       : 1;            /*!< [7..7] PIN7                                                               */
      __IOM uint16_t PIN8       : 1;            /*!< [8..8] PIN8                                                               */
      __IOM uint16_t PIN9       : 1;            /*!< [9..9] PIN9                                                               */
      __IOM uint16_t PIN10      : 1;            /*!< [10..10] PIN10                                                            */
      __IOM uint16_t PIN11      : 1;            /*!< [11..11] PIN11                                                            */
      __IOM uint16_t PIN12      : 1;            /*!< [12..12] PIN12                                                            */
      __IOM uint16_t PIN13      : 1;            /*!< [13..13] PIN13                                                            */
      __IOM uint16_t PIN14      : 1;            /*!< [14..14] PIN14                                                            */
      __IOM uint16_t PIN15      : 1;            /*!< [15..15] PIN15                                                            */
    } bit[5];
  } IN_LEVEL;
  __IM  uint16_t  RESERVED7[3];

  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000E0) GPIO_OD register                                           */

    struct {
      __IOM uint8_t PA10        : 1;            /*!< [0..0] GPIO_OD                                                            */
      __IOM uint8_t PB6         : 1;            /*!< [1..1] GPIO_OD                                                            */
      __IOM uint8_t PC1         : 1;            /*!< [2..2] GPIO_OD                                                            */
      __IOM uint8_t PC8         : 1;            /*!< [3..3] GPIO_OD                                                            */
      __IOM uint8_t PD0         : 1;            /*!< [4..4] GPIO_OD                                                            */
      __IOM uint8_t PD12        : 1;            /*!< [5..5] GPIO_OD                                                            */
      __IOM uint8_t PE12        : 1;            /*!< [6..6] GPIO_OD                                                            */
      __IOM uint8_t PE6         : 1;            /*!< [7..7] GPIO_OD                                                            */
    } bit;
  } OD_CTRL;
  __IM  uint8_t   RESERVED8;
  __IM  uint16_t  RESERVED9;
} MGPIO_Type;                                   /*!< Size = 228 (0xe4)                                                         */



/* =========================================================================================================================== */
/* ================                                           MDMA                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief 32 DMA (MDMA)
  */

typedef struct {                                /*!< (@ 0x000F8800) MDMA Structure                                             */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) DMA_SRC_ADDR register                                      */

    struct {
      __OM  uint32_t VAL        : 32;           /*!< [31..0] source address                                                    */
    } bit;
  } SRC_ADDR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) DMA_DEST_ADDR register                                     */

    struct {
      __OM  uint32_t VAL        : 32;           /*!< [31..0] dest address                                                      */
    } bit;
  } DEST_ADDR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) DMA_LEN_LOW register                                       */

    struct {
      __IOM uint32_t RX_LEN_L   : 16;           /*!< [15..0] buff len                                                          */
      __IOM uint32_t TX_LEN_L   : 16;           /*!< [31..16] buff len                                                         */
    } bit;
  } LEN_LOW;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) DMA control register                                       */

    struct {
      __IOM uint32_t LOOPBACK   : 1;            /*!< [0..0] loop back mode                                                     */
      __IOM uint32_t INT_MODE   : 1;            /*!< [1..1] enable interrupt                                                   */
      __IOM uint32_t RADDR_LOCK : 1;            /*!< [2..2] lock read addr                                                     */
      __IOM uint32_t WADDR_LOCK : 1;            /*!< [3..3] lock write addr                                                    */
      __IM  uint32_t            : 4;
      __IOM uint32_t RX_LEN_H   : 4;            /*!< [11..8] rx len                                                            */
      __IOM uint32_t TX_LEN_H   : 4;            /*!< [15..12] tx len                                                           */
      __IOM uint32_t PP_BUF     : 1;            /*!< [16..16] flag slave/dcmi                                                  */
      __IM  uint32_t            : 12;
      __IOM uint32_t RESET      : 1;            /*!< [29..29] init write 0,write 1                                             */
      __IOM uint32_t CLEAR_INT  : 1;            /*!< [30..30] clear DMA int                                                    */
      __IOM uint32_t START      : 1;            /*!< [31..31] enable DMA                                                       */
    } bit;
  } CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) DMA status                                                 */

    struct {
      __IM  uint32_t DONE       : 1;            /*!< [0..0] DMA status                                                         */
    } bit;
  } STATUS;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) Sends the current address of the BUF read pointer          */

    struct {
      __IM  uint32_t VAL        : 32;           /*!< [31..0] Sends the current address of the BUF read pointer                 */
    } bit;
  } RPTR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) received the current address of the BUF read
                                                                    pointer                                                    */

    struct {
      __IM  uint32_t VAL        : 32;           /*!< [31..0] receiced the current address of the BUF read pointer              */
    } bit;
  } WPRT;
} MDMA_Type;                                    /*!< Size = 28 (0x1c)                                                          */



/* =========================================================================================================================== */
/* ================                                           MSPI                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief MSPI (MSPI)
  */

typedef struct {                                /*!< (@ 0x000F891C) MSPI Structure                                             */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * CTRL *                                                   */

    struct {
      __IOM uint32_t CLK_DIV    : 3;            /*!< [2..0] SPICLK 分频系数 (1<<CTRL[2:0
                                                     ])                                                                        */
      __IOM uint32_t MODE       : 1;            /*!< [3..3] 0: Master Mode 1：Slave
                                                     Mode                                                                      */
      __IOM uint32_t CPHA       : 1;            /*!< [4..4] CPHA 1: 偶数边沿采样 0: 奇数边沿
                                                     采样                                                                    */
      __IOM uint32_t CPOL       : 1;            /*!< [5..5] CPOL （空闲状态时钟电平） 1: High
                                                     0: Low                                                                    */
      __IOM uint32_t RESET      : 1;            /*!< [6..6] spi_reset                                                          */
      __IOM uint32_t DCMI_EN    : 1;            /*!< [7..7] 0: 8-bit spi mode
                                                     1: 8-bit byte y extended to
                                                     16-bit rgb565                                                             */
      __IOM uint32_t RW_DELAY   : 7;            /*!< [14..8] 反向间隔（value*16个clock）                                */
      __IOM uint32_t AUTO_START : 1;            /*!< [15..15] 1: spi dma可以被dcmi多行中断自动启
                                                     动                                                                       */
      __IOM uint32_t SCK_DIR    : 1;            /*!< [16..16] ncs 与 sck 输入输出选择
                                                     0: 输出(master mode)
                                                     1: 输入(slave mode)                                                     */
      __IOM uint32_t RX_PHASE   : 1;            /*!< [17..17] 0: normal receive sample
                                                     point
                                                     1: receive sample point dela
                                                     y one clock of ahb_bus                                                    */
      __IOM uint32_t FIRST_BIT  : 1;            /*!< [18..18] 1: 先发送lsb
                                                     0:先发送MSB                                                            */
      __IOM uint32_t WAIT_DMA   : 1;            /*!< [19..19] 0: ignore dma status
                                                     1: 等待dma 完全写入ram ,再开始接收下1 by
                                                     te                                                                        */
    } bit;
  } CTRL;
} MSPI_Type;                                    /*!< Size = 4 (0x4)                                                            */



/* =========================================================================================================================== */
/* ================                                           MUART                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief MUART (MUART)
  */

typedef struct {                                /*!< (@ 0x000F8B1C) MUART Structure                                            */

  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000000) * CTRL *                                                   */

    struct {
      __IOM uint8_t RX_EN       : 1;            /*!< [0..0] UART 使能位
                                                     0：失能Rx功能
                                                     1：使能Rx功能
                                                                                                                               */
      __IOM uint8_t PARITY      : 1;            /*!< [1..1] UART 校验位
                                                     0：Parity_Even(偶校验)
                                                     1：Parity_Odd(奇校验)
                                                                                                                               */
      __IOM uint8_t DATA_BITS   : 1;            /*!< [2..2] UART 校验使能位
                                                     0：无校验位,仅发送8bit数据
                                                     1：有校验位,发送9bit数据。
                                                                                                                               */
      __IOM uint8_t STOP_BITS   : 1;            /*!< [3..3] UART 停止位
                                                     0：1bit停止位
                                                     1：2bit停止位
                                                                                                                               */
      __IOM uint8_t FLOW_CTRL   : 1;            /*!< [4..4] UART 模块流控控制位
                                                     0：无流控模式
                                                     1：有流控模式
                                                                                                                               */
      __IOM uint8_t SMART_CARD  : 1;            /*!< [5..5] UART 智能卡模式控制位
                                                     0：关闭智能卡
                                                     1：开启智能卡模式                                                 */
      __IOM uint8_t HDX_EN      : 1;            /*!< [6..6] UART全双工/双工模式控制位
                                                     0：全双工
                                                     1：半双工
                                                                                                                               */
      __IOM uint8_t RESET_BAUD  : 1;            /*!< [7..7] UART重置波特率位
                                                     0：无操作
                                                     1：必须先配置好波特率，置位1后 波特率才能生效。
                                                                                                                               */
    } bit;
  } CTRL;

  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000001) * RX_INT_LEN *                                             */

    struct {
      __IOM uint8_t VAL         : 8;            /*!< [7..0] 控制串口接收中断长度，为0不触发中断               */
    } bit;
  } RX_INT_LEN;

  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000002) * BAUD *                                                   */

    struct {
      __IOM uint16_t BAUD_RATE  : 15;           /*!< [14..0] 配置波特率 (波特率=时钟/寄存器的值)                */
      __IOM uint16_t TX_INT_EN  : 1;            /*!< [15..15] 发送中断使能位 0：失能tx中断 1：使能tx
                                                     中断                                                                    */
    } bit;
  } BAUD;

  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000004) * TIMEOUT_INT *                                            */

    struct {
      __IOM uint16_t VAL        : 16;           /*!< [15..0] 0：不启用。当收到数据后开始计时，超时未收到下一

                                                     个字节则触发中断，接收超时中断时间值（48*value）
                                                     。                                                                       */
    } bit;
  } TIMEOUT_INT;
  __IM  uint16_t  RESERVED;

  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000008) * RX_DATA *                                                */

    struct {
      __IM  uint8_t VAL         : 8;            /*!< [7..0] 读取UART的数据                                                */
    } bit;
  } RX_DATA;
  __IM  uint8_t   RESERVED1;
  __IM  uint16_t  RESERVED2;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) * STATUS *                                                 */

    struct {
      __IOM uint32_t RX_EMPTY   : 1;            /*!< [0..0] 0:rx buf 非空 1:rx buf 为空                                    */
      __IOM uint32_t RX_FULL    : 1;            /*!< [1..1] 0:rx buf 未满 1:rx buf 满                                       */
      __IOM uint32_t RX_NEAR_FULL : 1;          /*!< [2..2] 0:rx buf 数据未接近满 1:rx bu
                                                     f 数据接近满                                                         */
      __IM  uint32_t            : 9;
      __IOM uint32_t RX_ITEMS_H : 4;            /*!< [15..12] 当前RX BUF中的数据个数高4位                            */
      __IOM uint32_t RX_ITEMS_L : 16;            /*!< [23..16] 当前RX BUF中的数据个数低16位                           */
    } bit;
  } STATUS;
} MUART_Type;                                   /*!< Size = 16 (0x10)                                                          */



/* =========================================================================================================================== */
/* ================                                           MIIC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief MIIC (MIIC)
  */

typedef struct {                                /*!< (@ 0x000F911C) MIIC Structure                                             */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * CTRL1 *                                                  */

    struct {
      __IOM uint32_t SCLL       : 8;            /*!< [7..0] scll scl低电平时间                                            */
      __IOM uint32_t SCLH       : 8;            /*!< [15..8] sclh scl高电平时间                                           */
      __IOM uint32_t STSU       : 8;            /*!< [23..16] stsu 起始位建立时间                                       */
      __IOM uint32_t STHD       : 8;            /*!< [31..24] sthd 起始位保持时间                                       */
    } bit;
  } CTRL1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) * CTRL2 *                                                  */

    struct {
      __IOM uint32_t SOSU       : 8;            /*!< [7..0] sosu 停止位建立时间                                         */
      __IOM uint32_t DTSU       : 8;            /*!< [15..8] dtsu 数据位的建立时间                                     */
      __IOM uint32_t DTHD       : 8;            /*!< [23..16] dthd 数据位的保持时间                                    */
      __IOM uint32_t RESTART    : 1;            /*!< [24..24] restart 注意！！！这一bit是控
                                                     制I2C协议中restart时序的,而不是复位I2C寄存
                                                     器；在写从设备的时候置0,在读从设备的时候要置1        */
    } bit;
  } CTRL2;
} MIIC_Type;                                    /*!< Size = 8 (0x8)                                                            */



/* =========================================================================================================================== */
/* ================                                           MLPM                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief MLPM (MLPM)
  */

typedef struct {                                /*!< (@ 0x000FA800) MLPM Structure                                             */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) analog register                                            */

    struct {
      __IOM uint32_t RG_LPM_LDO_LPM_VSEL : 5;   /*!< [4..0] digital aon ldo vout sel                                           */
      __IOM uint32_t RG_LPM_LDO_LPM_0P33VDD_BYPB : 1;/*!< [5..5] LPM 0.33vdd ldo bypass to gnd enable control, low active      */
      __IOM uint32_t RG_LPM_HVLDO_OCP_EN : 1;   /*!< [6..6] HVLDO over current protection enable                               */
      __IOM uint32_t RG_LPM_POR_DEGLITCH_OPT : 1;/*!< [7..7] Vcoin POR deglitch optimization control, high active              */
      __IOM uint32_t RG_LPM_VSEC_POR_DEGLITCH_OPT : 1;/*!< [8..8] Vlion POR deglitch optimization control, high active         */
      __IM  uint32_t            : 3;
      __IOM uint32_t RG_LPM_LDO_SEC_VTRIM : 4;  /*!< [15..12] Security main LDO output voltage control                         */
      __IOM uint32_t RG_LPM_OSC192M_VC : 9;     /*!< [24..16] RC OSC 192MHz frequency control                                  */
      __IM  uint32_t            : 3;
      __IOM uint32_t RG_LPM_LDO_SEC_EN : 1;     /*!< [28..28] Security main LDO enable                                         */
      __IOM uint32_t RG_LPM_LDO_OSC192M_EN : 1; /*!< [29..29] RC OSC 192MHz LDO enable                                         */
      __IOM uint32_t RG_LPM_OSC192M_RSTN : 1;   /*!< [30..30] RC OSC 192MHz resetn                                             */
      __IOM uint32_t RG_LPM_OSC192M_EN : 1;     /*!< [31..31] RC OSC 192MHz enable                                             */
    } bit;
  } LDO_POR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) analog register                                            */

    struct {
      __IOM uint32_t OSC_XTAL_REF_MODE_EN : 1;  /*!< [0..0] mode cfg                                                           */
      __IOM uint32_t OSC_XTAL_IB_OBUF : 2;      /*!< [2..1] xtal output buffer bias current ctrl                               */
      __IM  uint32_t            : 1;
      __IOM uint32_t OSC_XTAL_IB_CTRL : 4;      /*!< [7..4] xtal core bias current ctrl                                        */
      __IOM uint32_t OSC_XTAL_CTRIM : 5;        /*!< [12..8] xtal cap bank selection                                           */
      __IOM uint32_t OSC_XTAL_EN_REG : 1;       /*!< [13..13] xtal regulator enable, high active                               */
      __IOM uint32_t OSC_XTAL_EN : 1;           /*!< [14..14] xtal core enable, high active                                    */
      __IOM uint32_t OSC_XTAL_DIV2_EN : 1;      /*!< [15..15] xtal to clkpll ref freq div2 enable, high active                 */
    } bit;
  } OSC_XTAL;
  __IM  uint32_t  RESERVED[2];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) XO32K control                                              */

    struct {
      __IOM uint32_t RG_LPM_XO32K_RG_XTAL_CGM_ISEL : 2;/*!< [1..0] xo32k constant-gm current selection                         */
      __IOM uint32_t RG_LPM_XO32K_RDC_SEL : 3;  /*!< [4..2] xo32k gm gate-drain dc res type selection                          */
      __IOM uint32_t RG_LPM_XO32K_ITUNE : 5;    /*!< [9..5] xo32k gm current selection                                         */
      __IOM uint32_t RG_LPM_XO32K_GMP_BYPASS : 1;/*!< [10..10] xo32k gm pmos bypass, high active. when xo32k mode              */
      __IOM uint32_t RG_LPM_XO32K_DISCONNECT : 1;/*!< [11..11] disconnect xo32k analog circuit from gpio pad, high
                                                     active                                                                    */
      __IOM uint32_t RG_LPM_XO32K_COMP_VREF_TUNE : 2;/*!< [13..12] xo32k comp voltage selection when vrefn from vgen,
                                                     control bits higher                                                       */
      __IOM uint32_t RG_LPM_XO32K_COMP_VN_SEL : 1;/*!< [14..14] xo32k hysteresis comp negative input signal selection          */
      __IOM uint32_t RG_LPM_XO32K_COMP_VGEN_EN : 1;/*!< [15..15] xo32k comp vrefn voltage gen circuit enable, high active      */
      __IOM uint32_t RG_LPM_XO32K_COMP_TH_SEL : 2;/*!< [17..16] xo32k hysteresis comp threshold voltage selection,
                                                     control bits higher, vth higher                                           */
      __IOM uint32_t RG_LPM_XO32K_COMP_ISEL : 2;/*!< [19..18] xo32k hysteresis comp current selection                          */
      __IOM uint32_t RG_LPM_XO32K_COMP_IB_LARGE : 1;/*!< [20..20] xo32k hysteresis comp and current-starved invter bais
                                                     current enlarge control, high active                                      */
      __IOM uint32_t DA_LPM_XO32K_EN : 1;       /*!< [21..21] xo32k enable, high active                                        */
    } bit;
  } XO32K;
  __IM  uint32_t  RESERVED1[3];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) CHGR control register                                      */

    struct {
      __IOM uint32_t RG_LPM_CHGR_TERMC : 2;     /*!< [1..0] Charging termination current control                               */
      __IOM uint32_t RG_LPM_CHGR_TCC : 2;       /*!< [3..2] analog register                                                    */
      __IOM uint32_t RG_LPM_CHGR_SHUTDOWN_SW : 1;/*!< [4..4] Force off charger pass transistor                                 */
      __IOM uint32_t RG_LPM_CHGR_SHUTDOWN_CORE : 1;/*!< [5..5] Force off charger CC/CV loop                                    */
      __IOM uint32_t RG_LPM_CHGR_SHUTDOWN_BIAS : 1;/*!< [6..6] Force off charger bias                                          */
      __IM  uint32_t            : 1;
      __IOM uint32_t RG_LPM_CHGR_RCHC : 4;      /*!< [11..8] Battery voltage threshold adjustments for re-charging
                                                     in 53mV/steps                                                             */
      __IOM uint32_t RG_LPM_CHGR_INSC_ENB : 1;  /*!< [12..12] Charger input sink current enable. Used to wake up
                                                     charger case and to be turned off upon the end of charging
                                                     process                                                                   */
      __IM  uint32_t            : 3;
      __IOM uint32_t RG_LPM_CHGR_ICHG_SET : 4;  /*!< [19..16] Charging current control in CC phase                             */
      __IOM uint32_t RG_LPM_CHGR_FORCE_CV : 1;  /*!< [20..20] Charger CV mode force enable                                     */
      __IOM uint32_t RG_LPM_CHGR_FORCE_CORE_ON : 1;/*!< [21..21] Force on charger CC/CV loop when charger is in standby
                                                     mode                                                                      */
      __IOM uint32_t RG_LPM_CHGR_FORCE_CC : 1;  /*!< [22..22] Charger CC mode force enable                                     */
      __IM  uint32_t            : 1;
      __IOM uint32_t RG_LPM_CHGR_CVC : 4;       /*!< [27..24] analog register                                                  */
      __IOM uint32_t RG_LPM_CHGR_RLIMIT_ENB : 1;/*!< [28..28] analog register                                                  */
    } bit;
  } CHGR_CTRL;
  __IM  uint32_t  RESERVED2[119];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000200) * GPIO_WKEN_W0 *                                           */

    struct {
      __IOM uint32_t LOW        : 32;           /*!< [31..0] gpio[31:0] 深度睡眠唤醒使能                               */
    } bit;
  } GPIO_WKEN_W0;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000204) * GPIO_WKEN_W1 *                                           */

    struct {
      __IOM uint32_t MID        : 32;           /*!< [31..0] gpio[63:32] 深度睡眠唤醒使能                              */
    } bit;
  } GPIO_WKEN_W1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000208) * GPIO_WKEN_W2 *                                           */

    struct {
      __IOM uint32_t HIGH       : 16;           /*!< [15..0] gpio[79:64] 深度睡眠唤醒使能                              */
    } bit;
  } GPIO_WKEN_W2;
  __IM  uint32_t  RESERVED3;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000210) * GPIO_WK_LEVEL *                                          */

    struct {
      __IOM uint32_t LEVEL      : 1;            /*!< [0..0] GPIO唤醒电平设置
                                                     0: GPIO高电平唤醒深度睡眠
                                                     1: GPIO低电平唤醒深度睡眠                                        */
    } bit;
  } GPIO_WK_LEVEL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000214) * GPIO_LATCH *                                             */

    struct {
      __IOM uint32_t LATCH      : 1;            /*!< [0..0] nan                                                                */
    } bit;
  } GPIO_LATCH;
  __IM  uint32_t  RESERVED4[2];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000220) * DEEP_SLEEP *                                             */

    struct {
      __OM  uint32_t EN         : 8;            /*!< [7..0] 写0x5a会进入深度睡眠                                       */
    } bit;
  } DEEP_SLEEP;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000224) * WAKEUP_CTRL *                                            */

    struct {
      __IOM uint32_t SEC_EN     : 1;            /*!< [0..0] 1: 使能安全事件唤醒深度睡眠                            */
      __IOM uint32_t RTC_LSI    : 1;            /*!< [1..1] 1:使能LSI定时唤醒深度睡眠                                */
      __IOM uint32_t RTC_LSE    : 1;            /*!< [2..2] 1: 使能LSE定时唤醒深度睡眠                               */
    } bit;
  } WAKEUP_CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000228) * WAIT_LDO_CTRL *                                          */

    struct {
      __IOM uint32_t CNT        : 10;           /*!< [9..0] core_ldo打开后,等待cnt个osc32k
                                                     周期后,开始启动系统,首次上电默认值为32ms
                                                     deep_sleep时,可通过合理设置此延迟值,减少系统
                                                     退出deep_sleep时间                                                    */
    } bit;
  } WAIT_LDO_CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000022C) * WKUP_HVLDO_CTRL *                                        */

    struct {
      __IOM uint32_t FIRST      : 1;            /*!< [0..0] 1: 深度睡眠唤醒时,先打开HVLDO,再进行上
                                                     电过程                                                                 */
      __IM  uint32_t            : 15;
      __IOM uint32_t CHGR_IN_TURN_ON : 8;       /*!< [23..16] chgr_in事件打开系统使能
                                                     0xaa: 关闭chgr_in事件打开系统功能
                                                     others: 打开chgr_in事件打开系统功能                             */
      __IOM uint32_t PWK_OFF_DISABLE : 8;       /*!< [31..24] power key off disable
                                                     0xaa: 禁用power key 关闭系统功能
                                                     others: 使能power 关闭系统功能                                    */
    } bit;
  } WKUP_HVLDO_CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000230) * RTC_LSE_CTRL *                                           */

    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] 使能 RTC LSE的时钟                                            */
      __IOM uint32_t SEL        : 1;            /*!< [1..1] RTC_LSE的时钟选择
                                                     0: 用LSI作为RTC_LSE的时钟
                                                     1:用LSEZ作为RTC_LSE的时钟                                           */
    } bit;
  } RTC_LSE_CTRL;
  __IM  uint32_t  RESERVED5[3];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000240) * CHGR_EVENT_EN *                                          */

    struct {
      __IOM uint32_t EVENT0     : 1;            /*!< [0..0] 1: 使能CHGR_WKUP[9:0]充电标志位
                                                     检测和唤醒,使能后需要延时1ms再配置CHGR_WKUP
                                                     _HI_EN[9:0]/CHGR_WKUP_LO_EN[
                                                     9:0]                                                                      */
      __IOM uint32_t EVENT1     : 1;            /*!< [1..1] 1: 使能CHGR_WKUP[11:10]充电标
                                                     志位检测和唤醒,使能后需要延时1ms再配置CHGR_WK
                                                     UP_HI_EN[11:10]/CHGR_WKUP_LO
                                                     _EN[11:10]                                                                */
    } bit;
  } CHGR_EVENT_EN;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000244) * CHGR_WKUP_HI_EN *                                        */

    struct {
      __IOM uint32_t VBAT_LV    : 1;            /*!< [0..0] ad_lpm_chgr_state_vbat_l
                                                     v                                                                         */
      __IOM uint32_t RCH_EN     : 1;            /*!< [1..1] ad_lpm_chgr_state_rch_en                                           */
      __IOM uint32_t IND        : 1;            /*!< [2..2] ad_lpm_chgr_state_ind                                              */
      __IOM uint32_t ICHG       : 1;            /*!< [3..3] ad_lpm_chgr_state_ichg                                             */
      __IOM uint32_t RESET      : 1;            /*!< [4..4] ad_lpm_chgr_reset                                                  */
      __IOM uint32_t UVLO_OK_AON : 1;           /*!< [5..5] ad_lpm_chgr_uvlo_ok_aon                                            */
      __IOM uint32_t PGOOD      : 1;            /*!< [6..6] ad_lpm_chgr_pgood                                                  */
      __IOM uint32_t DPPM_OV_CV : 1;            /*!< [7..7] ad_lpm_chgr_dppm_ov_cv                                             */
      __IOM uint32_t DPPM_OV_CC : 1;            /*!< [8..8] ad_lpm_chgr_dppm_ov_cc                                             */
      __IOM uint32_t CC_OV_CV   : 1;            /*!< [9..9] ad_lpm_chgr_cc_ov_cv                                               */
      __IOM uint32_t DET_AON    : 1;            /*!< [10..10] ad_lpm_chgr_in_det_aon                                           */
      __IOM uint32_t VBAT_OV    : 1;            /*!< [11..11] ad_lpm_vbat_ov_flag                                              */
      __IOM uint32_t PWK        : 1;            /*!< [12..12] power_key                                                        */
    } bit;
  } CHGR_WKUP_HI_EN;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000248) * CHGR_WKUP_LO_EN *                                        */

    struct {
      __IOM uint32_t VBAT_LV    : 1;            /*!< [0..0] ad_lpm_chgr_state_vbat_l
                                                     v                                                                         */
      __IOM uint32_t RCH_EN     : 1;            /*!< [1..1] ad_lpm_chgr_state_rch_en                                           */
      __IOM uint32_t IND        : 1;            /*!< [2..2] ad_lpm_chgr_state_ind                                              */
      __IOM uint32_t ICHG       : 1;            /*!< [3..3] ad_lpm_chgr_state_ichg                                             */
      __IOM uint32_t RESET      : 1;            /*!< [4..4] ad_lpm_chgr_reset                                                  */
      __IOM uint32_t UVLO_OK_AON : 1;           /*!< [5..5] ad_lpm_chgr_uvlo_ok_aon                                            */
      __IOM uint32_t PGOOD      : 1;            /*!< [6..6] ad_lpm_chgr_pgood                                                  */
      __IOM uint32_t DPPM_OV_CV : 1;            /*!< [7..7] ad_lpm_chgr_dppm_ov_cv                                             */
      __IOM uint32_t DPPM_OV_CC : 1;            /*!< [8..8] ad_lpm_chgr_dppm_ov_cc                                             */
      __IOM uint32_t CC_OV_CV   : 1;            /*!< [9..9] ad_lpm_chgr_cc_ov_cv                                               */
      __IOM uint32_t DET_AON    : 1;            /*!< [10..10] ad_lpm_chgr_in_det_aon                                           */
      __IOM uint32_t VBAT_OV    : 1;            /*!< [11..11] ad_lpm_vbat_ov_flag                                              */
      __IOM uint32_t PWK        : 1;            /*!< [12..12] power_key                                                        */
    } bit;
  } CHGR_WKUP_LO_EN;
  __IM  uint32_t  RESERVED6[5];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000260) * PWK_CTRL *                                               */

    struct {
      __IOM uint32_t ON_TIME    : 2;            /*!< [1..0] power key 按下多长时间唤醒系统配置
                                                     00: 128ms
                                                     01: 384ms
                                                     10: 640ms
                                                     11: 896ms                                                                 */
      __IM  uint32_t            : 2;
      __IOM uint32_t OFF_TIME   : 2;            /*!< [5..4] power_key按下多长时间关闭系统配置
                                                     00: 4s
                                                     01: 5s
                                                     10: 6s
                                                     11: 7s                                                                    */
      __IM  uint32_t            : 10;
      __OM  uint32_t LDO_OFF    : 1;            /*!< [16..16] 写1 关闭HVLDO                                                 */
      __OM  uint32_t LDO_EN     : 1;            /*!< [17..17] 写1 打开HVLDO                                                 */
    } bit;
  } PWK_CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000264) * LDO_EXEN_CTRL *                                          */

    struct {
      __IOM uint32_t OEN        : 1;            /*!< [0..0] 0: enable output
                                                     1: disable output                                                         */
      __IM  uint32_t            : 1;
      __IOM uint32_t OUT        : 1;            /*!< [2..2] nan                                                                */
      __IM  uint32_t            : 1;
      __IOM uint32_t PD         : 1;            /*!< [4..4] 1: enable pull-down                                                */
      __IOM uint32_t PU         : 1;            /*!< [5..5] 1: enable pull-up                                                  */
      __IM  uint32_t            : 2;
      __IOM uint32_t IE         : 1;            /*!< [8..8] 0: disable input
                                                     1: enable input                                                           */
      __IM  uint32_t IN         : 1;            /*!< [9..9] ldo_exen input value                                               */
      __IM  uint32_t            : 14;
      __IOM uint32_t GPIO       : 8;            /*!< [31..24] 0xaa: gpio 模式,pu/pd/ie/o
                                                     /oen受寄存器控制
                                                     others: ldo_exen模式,pu/pd/ie始
                                                     终为0,oen为0允许输出,o输出hvldo_en信号                         */
    } bit;
  } LDO_EXEN_CTRL;
  __IM  uint32_t  RESERVED7[6];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000280) * CLK_CTRL *                                               */

    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] 1: 使能寄存器时钟                                           */
    } bit;
  } CLK_CTRL;
  __IM  uint32_t  RESERVED8[7];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002A0) * ACCESS_CODE *                                            */

    struct {
      __IOM uint32_t ACCESS_CODE : 8;           /*!< [7..0] 按照顺序写入'0x55->0xaa->0x17'
                                                     来设置或者清除 'access_en'                                         */
    } bit;
  } ACCESS_CODE;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002A4) * ACCESS_EN *                                              */

    struct {
      __IOM uint32_t ACCESS_EN  : 1;            /*!< [0..0] 这1bit 只能在ACCESS_CODE设置后写
                                                     入
                                                     1: 打开LPM寄存器写入权限
                                                     0: 关闭LPM寄存器写入权限
                                                     注：每次退出深度睡眠后,access_code和acce
                                                     ss_en会自动清0,必须重新使能                                     */
    } bit;
  } ACCESS_EN;
  __IM  uint32_t  RESERVED9[22];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000300) * BAKEUP_REG0 *                                            */

    struct {
      __IOM uint32_t REG        : 32;           /*!< [31..0] 复位值是0x5555_5555                                           */
    } bit;
  } BAKEUP_REG0;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000304) * BAKEUP_REG1 *                                            */

    struct {
      __IOM uint32_t REG        : 32;           /*!< [31..0] 复位值是0xaaaa_aaaa                                           */
    } bit;
  } BAKEUP_REG1;
  __IM  uint32_t  RESERVED10[6];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000320) * BAKEUP_REG2 *                                            */

    struct {
      __IOM uint32_t REG        : 32;           /*!< [31..0] 无复位功能寄存器                                          */
    } bit;
  } BAKEUP_REG2;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000324) * BAKEUP_REG3 *                                            */

    struct {
      __IOM uint32_t REG        : 32;           /*!< [31..0] 无复位功能寄存器                                          */
    } bit;
  } BAKEUP_REG3;
} MLPM_Type;                                    /*!< Size = 808 (0x328)                                                        */



/* =========================================================================================================================== */
/* ================                                           MBPK                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief MBPK (MBPK)
  */

typedef struct {                                /*!< (@ 0x000FAC00) MBPK Structure                                             */
  __IOM uint32_t  KEY[32];                      /*!< (@ 0x00000000) key                                                        */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000080) * RST *                                                    */

    struct {
      __OM  uint32_t RESET      : 1;            /*!< [0..0] 写1会复位KEY,BPK的配置,SENSOR的配
                                                     置。                                                                    */
    } bit;
  } RST;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000084) * CLR *                                                    */

    struct {
      __OM  uint32_t CLR        : 4;            /*!< [3..0] 每一bit控制256-bit 的KEY清除 ,
                                                     写“1”将清除相应的区域                                        */
    } bit;
  } CLR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000088) * LR *                                                     */

    struct {
      __IOM uint32_t LOCK_READ  : 4;            /*!< [3..0] 每一bit控制256-bit 的KEY的锁定 ,
                                                     写“1”将锁定读取相应的区域                                  */
    } bit;
  } LR;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000008C) * LW *                                                     */

    struct {
      __IOM uint32_t LOCK_WRITE : 4;            /*!< [3..0] 每一bit控制256-bit 的KEY的锁定 ,
                                                     写“1”将锁定写入相应的区域                                  */
    } bit;
  } LW;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000090) * LOCK *                                                   */

    struct {
      __IOM uint32_t LOCK_SELF  : 1;            /*!< [0..0] 1:锁定LOCK寄存器本身(通常用于配置好其他的
                                                     锁定过后,且无法解锁)                                             */
      __IOM uint32_t LKW_LOCK   : 1;            /*!< [1..1] 1:锁定LOCK_WRITE寄存器                                        */
      __IOM uint32_t LKR_LOCK   : 1;            /*!< [2..2] 1:锁定LOCK_READ寄存器                                         */
      __IOM uint32_t CLR_LOCK   : 1;            /*!< [3..3] 1:锁定CLR寄存器                                               */
      __IOM uint32_t RESET_LOCK : 1;            /*!< [4..4] 1:锁定RESET寄存器                                             */
    } bit;
  } LOCK;
} MBPK_Type;                                    /*!< Size = 148 (0x94)                                                         */



/* =========================================================================================================================== */
/* ================                                           MSEC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief MSEC (MSEC)
  */

typedef struct {                                /*!< (@ 0x000FAE00) MSEC Structure                                             */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * LC *                                                     */

    struct {
      __IOM uint32_t VAL        : 8;            /*!< [7..0] 仅支持比特置1操作,不支持清0回退
                                                     0x01: 上电非安全状态
                                                     其他值：用户自定义                                               */
    } bit;
  } LC;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) * LOCK *                                                   */

    struct {
      __IOM uint32_t LOCK_SELF  : 1;            /*!< [0..0] 1:锁定LOCK寄存器本身(通常用于配置好其他的
                                                     锁定过后,且无法解锁)                                             */
      __IOM uint32_t ACTION     : 1;            /*!< [1..1] 1:锁定 ALERT_ACTION寄存器                                     */
      __IOM uint32_t TAMPER     : 1;            /*!< [2..2] 1:锁定TAMP_EN/TAMP_CTRL/TA
                                                     MP_STA_CTRL/TAMP_DYN_CTRL寄存器                                        */
      __IOM uint32_t SENSOR     : 1;            /*!< [3..3] 1:锁定SENSOR_EN/SENSOR_CTR
                                                     L/SENSOR_THRES寄存器                                                   */
      __IOM uint32_t SHIELD     : 1;            /*!< [4..4] 1:锁定SHIELD_EN/SHIELD_CTR
                                                     L寄存器                                                                */
    } bit;
  } LOCK;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) * ALERT_FILT *                                             */

    struct {
      __IM  uint32_t CNT        : 4;            /*!< [3..0] 当TAMPER/SENSOR/SHIELD的报警
                                                     发生时cnt寄存器会加1                                              */
      __IM  uint32_t            : 4;
      __IOM uint32_t THOLD      : 4;            /*!< [11..8] 当THOLD的配置大于等于CNT的值的时候会触发
                                                     ALERT_ACTION                                                              */
      __IM  uint32_t            : 4;
      __OM  uint32_t CNT_CLR    : 1;            /*!< [16..16] 写1 清除CNT寄存器的是值                                 */
    } bit;
  } ALERT_FILT;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) * ALERT_ACTION *                                           */

    struct {
      __IOM uint32_t CLEAR_KEY  : 4;            /*!< [3..0] 当ALERT_ACTION发生时,除了该寄存器配
                                                     置成0x5能失能清除秘钥动作,其他配置都会导致清除秘钥
                                                                                                                               */
      __IM  uint32_t            : 12;
      __IOM uint32_t RESET_SYSTEM : 4;          /*!< [19..16] 当ALERT_ACTION发生时,除了该寄存器配
                                                     置成0x5能失能复位系统动作,其他配置都会导致复位系统
                                                                                                                               */
    } bit;
  } ALERT_ACTION;
  __IM  uint32_t  RESERVED[4];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) * SOFT_ATTACK_EN *                                         */

    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] 置‘1’后无法清0
                                                     1: 使能soft_attack功能                                                */
    } bit;
  } SOFT_ATTACK_EN;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) * SOFT_ATTACK_LOCK *                                       */

    struct {
      __IOM uint32_t LOCK       : 1;            /*!< [0..0] 软件攻击锁定
                                                     0: 解锁 soft attack
                                                     1: 锁定 soft attack
                                                     注：写此寄存器可置1和清0,写其他任意寄存器,此寄存器
                                                     ��
                                                     置1                                                                      */
    } bit;
  } SOFT_ATTACK_LOCK;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) * SOFT_ATTACK *                                            */

    struct {
      __OM  uint32_t TRIGGER    : 1;            /*!< [0..0] 写1触发软件攻击
                                                     注：必须先写soft_attack_lock为0,再写此
                                                     寄存器,中间不能插入其他寄存器读写操作                   */
      __IM  uint32_t            : 3;
      __IOM uint32_t TYPE       : 4;            /*!< [7..4] soft_attack位检测到1时,锁存写数据的
                                                     比特7到4                                                               */
    } bit;
  } SOFT_ATTACK;
  __IM  uint32_t  RESERVED1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000030) * IE *                                                     */

    struct {
      __IOM uint32_t TAMPER     : 1;            /*!< [0..0] 1:使能TAMPER触发中断                                         */
      __IOM uint32_t SENSOR     : 1;            /*!< [1..1] 1:使能SENSOR触发中断                                         */
      __IOM uint32_t SHIELD     : 1;            /*!< [2..2] 1:使能SHIELD触发中断                                         */
      __IOM uint32_t SOFT_ATTACK : 1;           /*!< [3..3] 1:使能soft attact触发中断                                    */
      __IOM uint32_t KEY_CLEAR  : 1;            /*!< [4..4] 1:使能清除秘钥触发中断                                   */
    } bit;
  } IE;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000034) * IRQ *                                                    */

    struct {
      __IOM uint32_t TAMPER     : 1;            /*!< [0..0] 写‘1’清除TAMPER中断状态                                 */
      __IOM uint32_t SENSOR     : 1;            /*!< [1..1] 写‘1’清除SENSOR中断状态                                 */
      __IOM uint32_t SHIELD     : 1;            /*!< [2..2] 写‘1’清除SHIELD中断状态                                 */
      __IOM uint32_t SOFT_ATTACK : 1;           /*!< [3..3] 写‘1’清除SOFT_ATTACK中断状态                            */
      __IOM uint32_t KEY_CLEAR  : 1;            /*!< [4..4] 写‘1’清除KEY_CLEAR中断状态                              */
    } bit;
  } IRQ;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000038) * STATUS *                                                 */

    struct {
      __IM  uint32_t TAMP_ALARM : 8;            /*!< [7..0] TAMPER中断状态,每1BIT代表一个TAMP
                                                     ER触发中断                                                            */
      __IM  uint32_t SENSOR_ALARM : 1;          /*!< [8..8] SENSOR中断状态                                                 */
      __IM  uint32_t            : 7;
      __IM  uint32_t SHIELD_ALARM : 1;          /*!< [16..16] SHIELD中断状态                                               */
      __IM  uint32_t SOFT_ATTACK : 1;           /*!< [17..17] 软件攻击中断状态                                         */
      __IM  uint32_t KEY_CLEAR  : 1;            /*!< [18..18] 清除秘钥中断状态                                         */
    } bit;
  } STATUS;
  __IM  uint32_t  RESERVED2;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000040) * TAMP_EN *                                                */

    struct {
      __IOM uint32_t TAMP_0     : 4;            /*!< [3..0] TAMPER0 使能
                                                     0x5:使能
                                                     Others:使能                                                             */
      __IOM uint32_t TAMP_1     : 4;            /*!< [7..4] TAMPER1 使能
                                                     0x5:使能
                                                     Others:使能                                                             */
      __IOM uint32_t TAMP_2     : 4;            /*!< [11..8] TAMPER2 使能
                                                     0x5:使能
                                                     Others:使能                                                             */
      __IOM uint32_t TAMP_3     : 4;            /*!< [15..12] TAMPER3 使能
                                                     0x5:使能
                                                     Others:使能                                                             */
      __IOM uint32_t TAMP_4     : 4;            /*!< [19..16] TAMPER4 使能
                                                     0x5:使能
                                                     Others:使能                                                             */
      __IOM uint32_t TAMP_5     : 4;            /*!< [23..20] TAMPER5 使能
                                                     0x5:使能
                                                     Others:使能                                                             */
      __IOM uint32_t TAMP_6     : 4;            /*!< [27..24] TAMPER6 使能
                                                     0x5:使能
                                                     Others:使能                                                             */
      __IOM uint32_t TAMP_7     : 4;            /*!< [31..28] TAMPER7 使能
                                                     0x5:使能
                                                     Others:使能                                                             */
    } bit;
  } TAMP_EN;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000044) * TAMP_CTRL *                                              */

    struct {
      __IOM uint32_t MODE       : 4;            /*!< [3..0] TAMPER IO模式(每1BIT控制两个IO,
                                                     按顺序对应IO0~7)
                                                     0:静态模式
                                                     1:动态模式                                                            */
      __IM  uint32_t            : 4;
      __IOM uint32_t IE         : 8;            /*!< [15..8] TAMPER IO使能
                                                     动态模式,输入管脚需要使能IE,输出管脚不需要
                                                     静态模式,所有管脚均需要使能IE,PULL_AUTO为1
                                                     时,自动在静态检测期间使能IE,其他时间禁止IE,以减少
                                                     功耗                                                                    */
      __IOM uint32_t PD_EN      : 8;            /*!< [23..16] TAMPER IO下拉使能(每1BIT对应控制一
                                                     个 TAMPER IO)
                                                     动态模式:需要把输入脚上拉或下拉
                                                     静态模式:把对应IO下拉,PULL_AUTO为1时,自动
                                                     在静态检测期间使能下拉,其他时间禁止下拉,以减少功�
                                                                                                                               */
      __IOM uint32_t PU_EN      : 8;            /*!< [31..24] TAMPER IO上拉使能(每1BIT对应控制一
                                                     个 TAMPER IO)
                                                     动态模式:需要把输入脚上拉或下拉
                                                     静态模式:把对应IO上拉,PULL_AUTO为1时,自动
                                                     在静态检测期间使能上拉,其他时间禁止上拉,以减少功�

                                                     注：Tamper IO 上电默认开启上拉,每个IO上拉或
                                                     下拉只能选择一个                                                  */
    } bit;
  } TAMP_CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000048) * TAMP_STA_CTRL *                                          */

    struct {
      __IOM uint32_t PERIOD     : 2;            /*!< [1..0] 静态检测周期
                                                     0: 32ms
                                                     1: 125ms
                                                     2: 500ms
                                                     3: 0.9999s                                                                */
      __IOM uint32_t CHK_WIN    : 2;            /*!< [3..2] 窗口内采样过滤选择
                                                     0: 窗口内进行一次采样,一次采样成功即触发窗口报警
                                                     1: 窗口内进行两次采样,连续两次采样成功即触发窗口报
                                                     ��
                                                     2: 窗口内进行三次采样,连续三次采样成功即触发窗口报
                                                     ��
                                                     3: 窗口内进行四次采样,连续四次采样成功即触发窗口报
                                                     ��                                                                        */
      __IOM uint32_t FILT_WIN   : 2;            /*!< [5..4] 静态检测窗口报警过滤选择
                                                     0: 一个窗口检测到报警即为报警
                                                     1: 连续两个窗口检测到报警即为报警
                                                     2: 连续三个窗口检测到报警即为报警
                                                     3: 连续四个窗口检测到报警即为报警                          */
      __IM  uint32_t            : 2;
      __IOM uint32_t PROT_EN    : 1;            /*!< [8..8] 静态报警触发后,IO是否启动自动保护
                                                     0: 不开启 ,继续进行检测
                                                     1: 开启 ,停止检测,进入保护模式,保护模式由PROT
                                                     _MODE确定                                                               */
      __IOM uint32_t PROT_MODE  : 1;            /*!< [9..9] 静态报警触发后,保护模式选择
                                                     0: 引脚处于高阻状态
                                                     1: 引脚自动上下拉（取决于外部电平）                       */
      __IOM uint32_t PULL_AUTO  : 1;            /*!< [10..10] 0: 静态上下拉由软件控制
                                                     1: 静态上下拉只在配置工作期间有效,由硬件自动控制    */
      __IM  uint32_t            : 9;
      __IOM uint32_t CHK_GAP    : 2;            /*!< [21..20] 静态检测间隔
                                                     0: 1ms
                                                     1: 2ms
                                                     2: 4ms
                                                     3: 8ms                                                                    */
      __IOM uint32_t CHK_DLY    : 2;            /*!< [23..22] 静态上下拉开启后,延迟多长时间后进行检测
                                                     0: 1ms
                                                     1: 4ms
                                                     2: 8ms
                                                     3: 16ms                                                                   */
      __IOM uint32_t ALERT_LEVEL : 8;           /*!< [31..24] 分别对应8个引脚的静态报警电平
                                                     0: 低电平报警
                                                     1: 高电平报警                                                        */
    } bit;
  } TAMP_STA_CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) * TAMP_DYN_CTRL *                                          */

    struct {
      __IOM uint32_t PERIOD     : 2;            /*!< [1..0] 动态检测周期
                                                     0: 32ms
                                                     1: 125ms
                                                     2: 500ms
                                                     3: 0.9999s                                                                */
      __IOM uint32_t CHK_WIN    : 2;            /*!< [3..2] 窗口内采样过滤选择
                                                     0: 窗口内进行一次采样,一次采样成功即触发窗口报警
                                                     1: 窗口内进行两次采样,连续两次采样成功即触发窗口报
                                                     ��
                                                     2: 窗口内进行三次采样,连续三次采样成功即触发窗口报
                                                     ��
                                                     3: 窗口内进行四次采样,连续四次采样成功即触发窗口报
                                                     ��                                                                        */
      __IM  uint32_t            : 4;
      __IOM uint32_t PROT_EN    : 1;            /*!< [8..8] 动态报警触发后,IO是否启动自动保护
                                                     0: 不开启
                                                     1: 开启 ,保护模式由PROT_MODE确定                                 */
      __IOM uint32_t PROT_MODE  : 1;            /*!< [9..9] 动态报警触发后,保护模式选择
                                                     0: 引脚处于高阻状态
                                                     1: 引脚自动上下拉（取决于外部电平）                       */
    } bit;
  } TAMP_DYN_CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000050) * TAMP_IO_STATUS *                                         */

    struct {
      __IM  uint32_t IE         : 8;            /*!< [7..0] IO IE状态                                                        */
      __IM  uint32_t OEN        : 8;            /*!< [15..8] IO使能状态                                                    */
      __IM  uint32_t PD         : 8;            /*!< [23..16] IO下拉状态                                                   */
      __IM  uint32_t PU         : 8;            /*!< [31..24] IO上拉状态                                                   */
    } bit;
  } TAMP_IO_STATUS;
  __IM  uint32_t  RESERVED3[11];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000080) * SENSOR_EN *                                              */

    struct {
      __IOM uint32_t VBUT_1_2_EN : 4;           /*!< [3..0] 纽扣电池1.2V输出电压传感器使能:
                                                     0x5:失能
                                                     Others:使能                                                             */
      __IOM uint32_t VBUT_3_3_EN : 4;           /*!< [7..4] 纽扣电池3.3V输入电压传感器使能:
                                                     0x5:失能
                                                     Others:使能                                                             */
      __IOM uint32_t TEMP_EN    : 4;            /*!< [11..8] 温度传感器使能:
                                                     0x5:失能
                                                     Others:使能                                                             */
    } bit;
  } SENSOR_EN;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000084) * SENSOR_CTRL *                                            */

    struct {
      __IM  uint32_t            : 16;
      __IOM uint32_t DUR        : 2;            /*!< [17..16] Sensor检测时间长度。
                                                     00: always on
                                                     01: 2ms
                                                     10: 8ms
                                                     11: 16ms                                                                  */
      __IOM uint32_t DELAY      : 2;            /*!< [19..18] 警报持续时间门限,大于门限的信号,将触发报警。用
                                                     于滤除毛刺,防止虚警。
                                                     00: 1*(1/32k)=31.25us
                                                     01: 8*(1/32k)=250us
                                                     10: 32*(1/32k)=1ms
                                                     11: 128*(1/32k)=4ms
                                                     注：这个时间必须小于sensor_duration时间                       */
      __IM  uint32_t            : 4;
      __IOM uint32_t CHK_EN     : 5;            /*!< [28..24] 传感器检测使能
                                                     [4]: 低温检测使能
                                                     [3]: 高温检测使能
                                                     [2]: 纽扣电池3.3v输出低压检测使能
                                                     [1]: 纽扣电池3.3v输出高压检测使能
                                                     [0]: 纽扣电池1.2v输出低压检测使能                             */
    } bit;
  } SENSOR_CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000088) * SENSOR_THRES *                                           */

    struct {
      __IOM uint32_t DVDDLPM_L  : 4;            /*!< [3..0] 纽扣电池1.2V输出电压低报警设置
                                                     报警值等于 0.83+DVDDLPM_L*0.02                                       */
      __IM  uint32_t            : 4;
      __IOM uint32_t VBUT_L     : 4;            /*!< [11..8] 纽扣电池3.3V输入电压低报警设置
                                                     0000: 1.938
                                                     0001: 1.971
                                                     0010: 2.005
                                                     0011: 2.040
                                                     0100: 2.076
                                                     0101: 2.113
                                                     0110: 2.152
                                                     0111: 2.193
                                                     1000: 2.235
                                                     1001: 2.278
                                                     1010: 2.324
                                                     1011: 2.371
                                                     1100: 2.420
                                                     1101: 2.471
                                                     1110: 2.525
                                                     1111: 2.580                                                               */
      __IOM uint32_t VBUT_H     : 4;            /*!< [15..12] 纽扣电池3.3V输入电压高报警设置
                                                     0000: 3.471
                                                     0001: 3.577
                                                     0010: 3.690
                                                     0011: 3.810
                                                     0100: 3.938
                                                     0101: 4.076
                                                     0110: 4.223
                                                     0111: 4.381
                                                     1000: 4.552
                                                     1001: 4.736
                                                     1010: 4.936
                                                     1011: 5.154
                                                     1100: 5.392
                                                     1101: 5.653
                                                     1110: 5.926
                                                     1111: 6.115                                                               */
      __IOM uint32_t TS_UTC     : 3;            /*!< [18..16] 低温报警温度设置
                                                     0: -40
                                                     1: -35
                                                     2: -30
                                                     3: -25
                                                     4: -20                                                                    */
      __IM  uint32_t            : 1;
      __IOM uint32_t TS_OTC     : 3;            /*!< [22..20] 高温报警温度设置
                                                     0: 85
                                                     1: 90
                                                     2: 95
                                                     3: 100
                                                     4: 105                                                                    */
    } bit;
  } SENSOR_THRES;
  __IM  uint32_t  RESERVED4[13];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000C0) * SHIELD_EN *                                              */

    struct {
      __IOM uint32_t EN_0       : 4;            /*!< [3..0] SHIELD 0使能
                                                     0x5 :失能
                                                     Others: 使能                                                            */
      __IOM uint32_t EN_1       : 4;            /*!< [7..4] SHIELD 1使能
                                                     0x5 :失能
                                                     Others: 使能                                                            */
      __IOM uint32_t EN_2       : 4;            /*!< [11..8] SHIELD 2使能
                                                     0x5 :失能
                                                     Others: 使能                                                            */
      __IOM uint32_t EN_3       : 4;            /*!< [15..12] SHIELD 3使能
                                                     0x5 :失能
                                                     Others: 使能                                                            */
      __IOM uint32_t EN_4       : 4;            /*!< [19..16] SHIELD 4使能
                                                     0x5 :失能
                                                     Others: 使能                                                            */
      __IOM uint32_t EN_5       : 4;            /*!< [23..20] SHIELD 5使能
                                                     0x5 :失能
                                                     Others: 使能                                                            */
      __IOM uint32_t EN_6       : 4;            /*!< [27..24] SHIELD 6使能
                                                     0x5 :失能
                                                     Others: 使能                                                            */
      __IOM uint32_t EN_7       : 4;            /*!< [31..28] SHIELD 7使能
                                                     0x5 :失能
                                                     Others: 使能                                                            */
    } bit;
  } SHIELD_EN;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000C4) * SHIELD_CTRL *                                            */

    struct {
      __IOM uint32_t PERIOD     : 2;            /*!< [1..0] Shield工作周期
                                                     0: 32ms
                                                     1: 125ms
                                                     2: 500ms
                                                     3: 0.9999s                                                                */
      __IM  uint32_t            : 6;
      __IOM uint32_t CHK_WIN    : 2;            /*!< [9..8] 窗口内采样过滤选择
                                                     0: 窗口内进行一次采样,一次采样成功即触发窗口报警
                                                     1: 窗口内进行两次采样,连续两次采样成功即触发窗口报
                                                     ��
                                                     2: 窗口内进行三次采样,连续三次采样成功即触发窗口报
                                                     ��
                                                     3: 窗口内进行四次采样,连续四次采样成功即触发窗口报
                                                     ��                                                                        */
    } bit;
  } SHIELD_CTRL;
} MSEC_Type;                                    /*!< Size = 200 (0xc8)                                                         */



/* =========================================================================================================================== */
/* ================                                           MRTC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief MRTC (MRTC)
  */

typedef struct {                                /*!< (@ 0x000FAF00) MRTC Structure                                             */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * EN *                                                     */

    struct {
      __IOM uint32_t VAL        : 1;            /*!< [0..0] 1: 使能RTC 0:失能RTC                                           */
    } bit;
  } EN;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) * SEC_CNT *                                                */

    struct {
      __IOM uint32_t VAL        : 16;           /*!< [15..0] 设置一秒校准值                                             */
    } bit;
  } SEC_CNT;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) * IE *                                                     */

    struct {
      __IOM uint32_t SEC        : 1;            /*!< [0..0] 1: 允许秒中断 0:禁止秒中断                               */
      __IOM uint32_t ALARM      : 1;            /*!< [1..1] 1: 允许闹钟中断 0:禁止闹钟中断                         */
    } bit;
  } IE;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) * IRQ_STATUS *                                             */

    struct {
      __IOM uint32_t SEC        : 1;            /*!< [0..0] 1: 秒中断,scnd_ie为0时也会置位,但不
                                                     会触发中断                                                           */
      __IOM uint32_t ALARM      : 1;            /*!< [1..1] 1: 闹钟中断,clk_alm_ie为0时也会置
                                                     位,但不会触发中断                                                 */
    } bit;
  } IRQ_STATUS;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) * ALARM *                                                  */

    struct {
      __IOM uint32_t IRQPREVAL  : 32;           /*!< [31..0] 闹钟中断预设值                                             */
    } bit;
  } ALARM;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) * TIME *                                                   */

    struct {
      __IOM uint32_t VAL        : 32;           /*!< [31..0] 读操作读取当前RTC计数器值
                                                     写操作改写当前RTC计数器值,仅支持32-bit操作                */
    } bit;
  } TIME;
} MRTC_Type;                                    /*!< Size = 24 (0x18)                                                          */



/* =========================================================================================================================== */
/* ================                                           MADC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief MADC (MADC)
  */

typedef struct {                                /*!< (@ 0x000FBB00) MADC Structure                                             */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * CTRL1 *                                                  */

    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] adc模块数字开关
                                                     0: 失能ADC模块
                                                     1: 使能ADC模块                                                        */
      __IOM uint32_t AWD_EN     : 1;            /*!< [1..1] ADC看门狗使能,ADC采样值超过看门狗门限时会
                                                     触发ADC看门狗中断
                                                     0::失能
                                                     1::使能                                                                 */
      __IOM uint32_t SAMP_EDGE  : 1;            /*!< [2..2] ADC采样边沿选择
                                                     0:下降沿采样
                                                     1: 上升沿采样                                                        */
    } bit;
  } CTRL1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) * CTRL2 *                                                  */

    struct {
      __OM  uint32_t SGL_START  : 1;            /*!< [0..0] 软件写'1',启动一次ADC采(仅在SAMP_M
                                                     ODE为0时生效)                                                         */
      __IM  uint32_t            : 7;
      __IOM uint32_t SAMP_MODE  : 1;            /*!< [8..8] 采样模式
                                                     0:单次采样模式
                                                     1:连续采样模式                                                      */
      __IM  uint32_t            : 7;
      __IOM uint32_t TRIG_EN    : 9;            /*!< [24..16] 定时器溢出触发ADC采样(仅适用于单次采样模式)
                                                     0:失能
                                                     1:使能                                                                  */
    } bit;
  } CTRL2;
  __IM  uint32_t  RESERVED[2];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) * IE *                                                     */

    struct {
      __IOM uint32_t DONE       : 1;            /*!< [0..0] 采样结束中断使能
                                                     0:失能
                                                     1.使能                                                                  */
      __IOM uint32_t FIFO_OVER  : 1;            /*!< [1..1] FIFO数据超过FIFO_LIMIT中断使能
                                                     0:失能
                                                     1.使能                                                                  */
      __IOM uint32_t FIFO_FULL  : 1;            /*!< [2..2] FIFO数据溢出中断使能
                                                     0:失能
                                                     1.使能                                                                  */
      __IOM uint32_t AWD        : 1;            /*!< [3..3] ADC看门狗中断使能
                                                     0:失能
                                                     1.使能                                                                  */
    } bit;
  } IE;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) * STATUS *                                                 */

    struct {
      __IOM uint32_t DONE       : 1;            /*!< [0..0] 采样结束中断状态,写1清除中断                          */
      __IOM uint32_t FIFO_OVER  : 1;            /*!< [1..1] FIFO数据超过FIFO_LIMIT中断状态,写
                                                     1清除中断                                                             */
      __IOM uint32_t FIFO_FULL  : 1;            /*!< [2..2] FIFO数据溢出中断状态,写1清除中断                      */
      __IOM uint32_t AWD        : 1;            /*!< [3..3] ADC看门狗中断状态,写1清除中断                          */
    } bit;
  } STATUS;
  __IM  uint32_t  RESERVED1[2];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) * FIFO_CTRL *                                              */

    struct {
      __IOM uint32_t LIMIT      : 5;            /*!< [4..0] 当LIMIT>0,且ITEMS>=LIMIT时触
                                                     发FIFO_OVER中断                                                        */
      __IM  uint32_t            : 3;
      __IM  uint32_t ITEMS      : 5;            /*!< [12..8] FIFO中的有效数据量                                         */
      __IM  uint32_t            : 3;
      __IOM uint32_t RST        : 1;            /*!< [16..16] ADC FIFO复位                                                   */
      __IOM uint32_t EN         : 1;            /*!< [17..17] ADC FIFO使能
                                                     1:ADC数据有效转换值会写入FIFO
                                                     0:ADC数据有效转换值不会写入FIFO                                */
    } bit;
  } FIFO_CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) * FIFO *                                                   */

    struct {
      __IM  uint32_t DATA       : 13;           /*!< [12..0] 使用FIFO时的ADC取数寄存器(未使能电压转换
                                                     功能时,读到的为原始AD值;使能电压转换功能时,读到的�

                                                     电压值的二进制补码,单位为mv)                                  */
    } bit;
  } FIFO;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) * DATA *                                                   */

    struct {
      __IM  uint32_t VAL        : 13;           /*!< [12..0] 不使用FIFO时的ADC取数寄存器(未使能电压转
                                                     换功能时,读到的为原始AD值;使能电压转换功能时,读到�

                                                     为电压值的二进制补码,单位为mv)                               */
    } bit;
  } DATA;
  __IM  uint32_t  RESERVED2;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000030) * AWD *                                                    */

    struct {
      __IOM uint32_t LOW_LIMIT  : 13;           /*!< [12..0] ADC看门狗的低阈值(使能电压转换时,需同时启用
                                                     负电压归零功能才能使用ADC看门狗功能)                      */
      __IM  uint32_t            : 3;
      __IOM uint32_t HIGH_LIMIT : 13;           /*!< [28..16] ADC看门狗的高阈值(使能电压转换时,需同时启用
                                                     负电压归零功能才能使用ADC看门狗功能)                      */
    } bit;
  } AWD;
  __IM  uint32_t  RESERVED3[3];

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000040) * REF_AD *                                                 */

    struct {
      __IOM uint32_t VAL        : 10;           /*!< [9..0] 基准电压AD值                                                  */
    } bit;
  } REF_AD;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000044) * REF_VOL *                                                */

    struct {
      __IOM uint32_t VAL        : 13;           /*!< [12..0] 基准电压(mV)                                                  */
    } bit;
  } REF_VOL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000048) * SLOPE *                                                  */

    struct {
      __IOM uint32_t VAL        : 10;           /*!< [9..0] 电压转换斜率((vol_high-vol_low
                                                     )/(vol_high_ref-vol_low_ref)
                                                     )*64计算得到的10-bit整数值                                        */
    } bit;
  } SLOPE;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) * CONVERT_CTRL *                                           */

    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] 电压转换功能开关
                                                     1: 使能电压转换
                                                     0: 失能电压转换(输出原始ADC采样值)                           */
      __IOM uint32_t NEG_ZERO   : 1;            /*!< [1..1] 负电压归零控制(写1时,负电压以0V输出)                */
    } bit;
  } CONVERT_CTRL;
} MADC_Type;                                    /*!< Size = 80 (0x50)                                                          */



/* =========================================================================================================================== */
/* ================                                         MISO7811                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief MISO7811 (MISO7811)
  */

typedef struct {                                /*!< (@ 0x000F8F00) MISO7811 Structure                                         */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) * BASE_ADDR_T1 *                                           */

    struct {
      __IOM uint32_t ISO_BASE_ADDR : 20;        /*!< [19..0] Character write base add
                                                     ress for track 1                                                          */
    } bit;
  } BASE_ADDR_T1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) * BASE_ADDR_T2 *                                           */

    struct {
      __IOM uint32_t ISO_BASE_ADDR : 20;        /*!< [19..0] Character write base add
                                                     ress for track 2                                                          */
    } bit;
  } BASE_ADDR_T2;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) * BASE_ADDR_T3 *                                           */

    struct {
      __IOM uint32_t ISO_BASE_ADDR : 20;        /*!< [19..0] Character write base add
                                                     ress for track 3                                                          */
    } bit;
  } BASE_ADDR_T3;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) * CTRL *                                                   */

    struct {
      __IOM uint32_t RX_EN      : 1;            /*!< [0..0] 7811 decoder enable                                                */
      __IOM uint32_t T1_IRQ_EN  : 1;            /*!< [1..1] 7811 track 1 interrupt
                                                     enable                                                                    */
      __IOM uint32_t T1_CLR_IRQ : 1;            /*!< [2..2] Clear 7811 track 1 inter
                                                     rupt                                                                      */
      __IOM uint32_t T2_IRQ_EN  : 1;            /*!< [3..3] 7811 track 2 interrupt
                                                     enable                                                                    */
      __IOM uint32_t T2_CLR_IRQ : 1;            /*!< [4..4] Clear 7811 track 2 inter
                                                     rupt                                                                      */
      __IOM uint32_t T3_IRQ_EN  : 1;            /*!< [5..5] 7811 track 3 interrupt
                                                     enable                                                                    */
      __IOM uint32_t T3_CLR_IRQ : 1;            /*!< [6..6] Clear 7811 track 3 inter
                                                     rupt                                                                      */
      __IOM uint32_t SOFT_RESET : 1;            /*!< [7..7] soft reset for AHB bus c
                                                     ontrol                                                                    */
      __IOM uint32_t TIMER_EN   : 1;            /*!< [8..8] Timer enable                                                       */
      __IOM uint32_t TIMER_IRQ_EN : 1;          /*!< [9..9] 7811 timer interrupt ena
                                                     ble                                                                       */
      __IOM uint32_t TIMER_CLR_IRQ : 1;         /*!< [10..10] Clear 7811 timer interru
                                                     pt                                                                        */
      __IOM uint32_t T1_DC_CANCEL_EN : 1;       /*!< [11..11] Enable DC cancellation f
                                                     or track 1                                                                */
      __IOM uint32_t T1_DC_CALC_WIN : 2;        /*!< [13..12] DC calculation window co
                                                     nfiguration for track 1                                                   */
      __IOM uint32_t T2_DC_CANCEL_EN : 1;       /*!< [14..14] Enable DC cancellation f
                                                     or track 2                                                                */
      __IOM uint32_t T2_DC_CALC_WIN : 2;        /*!< [16..15] DC calculation window co
                                                     nfiguration for track 2                                                   */
      __IOM uint32_t T3_DC_CANCEL_EN : 1;       /*!< [17..17] Enable DC cancellation f
                                                     or track 3                                                                */
      __IOM uint32_t T3_DC_CALC_WIN : 2;        /*!< [19..18] DC calculation window co
                                                     nfiguration for track 3                                                   */
      __IOM uint32_t T1_CHANNEL_SEL : 2;        /*!< [21..20] Channel select signal fo
                                                     r track 1                                                                 */
      __IOM uint32_t T2_CHANNEL_SEL : 2;        /*!< [23..22] Channel select signal fo
                                                     r track 2                                                                 */
      __IOM uint32_t T3_CHANNEL_SEL : 2;        /*!< [25..24] Channel select signal fo
                                                     r track 3                                                                 */
      __IOM uint32_t T1_BUFFULL_IRQ_EN : 1;     /*!< [26..26] 7811 track 1 buffer full
                                                     interrupt enable                                                          */
      __IOM uint32_t T1_BUFFULL_CLR_IRQ : 1;    /*!< [27..27] Clear 7811 track 1 buffe
                                                     r full interrupt                                                          */
      __IOM uint32_t T2_BUFFULL_IRQ_EN : 1;     /*!< [28..28] 7811 track 2 buffer full
                                                     interrupt enable                                                          */
      __IOM uint32_t T2_BUFFULL_CLR_IRQ : 1;    /*!< [29..29] Clear 7811 track 2 buffe
                                                     r full interrupt                                                          */
      __IOM uint32_t T3_BUFFULL_IRQ_EN : 1;     /*!< [30..30] 7811 track 3 buffer full
                                                     interrupt enable                                                          */
      __IOM uint32_t T3_BUFFULL_CLR_IRQ : 1;    /*!< [31..31] Clear 7811 track 3 buffe
                                                     r full interrupt                                                          */
    } bit;
  } CTRL;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) * T1_PEAK_VALUE_CFG *                                      */

    struct {
      __IOM uint32_t THLD_INIT  : 9;            /*!< [8..0] Initial peak value thres
                                                     hold                                                                      */
      __IOM uint32_t ALPHA      : 4;            /*!< [12..9] Coefficient for peak val
                                                     ue update IIR filter                                                      */
      __IOM uint32_t THLD_RATIO : 4;            /*!< [16..13] Peak value threshold rat
                                                     io                                                                        */
    } bit;
  } T1_PEAK_VALUE_CFG;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) * T1_PEAK_WIDTH_CFG *                                      */

    struct {
      __IOM uint32_t THLD_INIT  : 15;           /*!< [14..0] Initial peak value thres
                                                     hold                                                                      */
      __IM  uint32_t            : 1;
      __IOM uint32_t UPDATA_RATIO1 : 4;         /*!< [19..16] Pulse width update ratio
                                                     1                                                                         */
      __IOM uint32_t UPDATA_RATIO2 : 4;         /*!< [23..20] Pulse width update ratio
                                                     2                                                                         */
      __IOM uint32_t UPDATA_RATIO3 : 4;         /*!< [27..24] Pulse width update ratio
                                                     3                                                                         */
      __IOM uint32_t UPDATA_RATIO4 : 4;         /*!< [31..28] Pulse width update ratio
                                                     4                                                                         */
    } bit;
  } T1_PEAK_WIDTH_CFG;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) * T1_PULSE_WIDTH_CFG *                                     */

    struct {
      __IOM uint32_t SYNC_ZERO_WIN : 3;         /*!< [2..0] Synchronized zero judgem
                                                     ent window                                                                */
      __IOM uint32_t PULSE_WID_MAX : 15;        /*!< [17..3] Maximum pulse width valu
                                                     e                                                                         */
      __IOM uint32_t PULSE_WID_BETA : 4;        /*!< [21..18] Coefficient for pulse wi
                                                     dth threshold IIR filter                                                  */
      __IM  uint32_t            : 2;
      __IOM uint32_t PEAK_SEL_RATIO1 : 4;       /*!< [27..24] Pulse width thld ratio1
                                                     for peak select                                                           */
      __IOM uint32_t PEAK_SEL_RATIO2 : 4;       /*!< [31..28] Pulse width thld ratio2
                                                     for peak select                                                           */
    } bit;
  } T1_PULSE_WIDTH_CFG;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) * T1_DECODE_CFG *                                          */

    struct {
      __IOM uint32_t RATIO1     : 4;            /*!< [3..0] Pulse width threshold1 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO2     : 4;            /*!< [7..4] Pulse width threshold2 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO3     : 4;            /*!< [11..8] Pulse width threshold3 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO4     : 4;            /*!< [15..12] Pulse width threshold4 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO5     : 4;            /*!< [19..16] Pulse width threshold5 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO6     : 4;            /*!< [23..20] Pulse width threshold6 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO7     : 4;            /*!< [27..24] Pulse width threshold7 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO8     : 4;            /*!< [31..28] Pulse width threshold8 f
                                                     or decode                                                                 */
    } bit;
  } T1_DECODE_CFG;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) * T2_PEAK_VALUE_CFG *                                      */

    struct {
      __IOM uint32_t THLD_INIT  : 9;            /*!< [8..0] Initial peak value thres
                                                     hold                                                                      */
      __IOM uint32_t ALPHA      : 4;            /*!< [12..9] Coefficient for peak val
                                                     ue update IIR filter                                                      */
      __IOM uint32_t THLD_RATIO : 4;            /*!< [16..13] Peak value threshold rat
                                                     io                                                                        */
    } bit;
  } T2_PEAK_VALUE_CFG;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) * T2_PEAK_WIDTH_CFG *                                      */

    struct {
      __IOM uint32_t THLD_INIT  : 15;           /*!< [14..0] Initial peak value thres
                                                     hold                                                                      */
      __IM  uint32_t            : 1;
      __IOM uint32_t PULSE_WID_RATIO1 : 4;      /*!< [19..16] Pulse width update ratio
                                                     1                                                                         */
      __IOM uint32_t PULSE_WID_RATIO2 : 4;      /*!< [23..20] Pulse width update ratio
                                                     2                                                                         */
      __IOM uint32_t PULSE_WID_RATIO3 : 4;      /*!< [27..24] Pulse width update ratio
                                                     3                                                                         */
      __IOM uint32_t PULSE_WID_RATIO4 : 4;      /*!< [31..28] Pulse width update ratio
                                                     4                                                                         */
    } bit;
  } T2_PEAK_WIDTH_CFG;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) * T2_PULSE_WIDTH_CFG *                                     */

    struct {
      __IOM uint32_t SYNC_ZERO_WIN : 3;         /*!< [2..0] Synchronized zero judgem
                                                     ent window                                                                */
      __IOM uint32_t PULSE_WID_MAX : 15;        /*!< [17..3] Maximum pulse width valu
                                                     e                                                                         */
      __IOM uint32_t PULSE_WID_BETA : 4;        /*!< [21..18] Coefficient for pulse wi
                                                     dth threshold IIR filter                                                  */
      __IM  uint32_t            : 2;
      __IOM uint32_t PEAK_SEL_RATIO1 : 4;       /*!< [27..24] Pulse width thld ratio1
                                                     for peak select                                                           */
      __IOM uint32_t PEAK_SEL_RATIO2 : 4;       /*!< [31..28] Pulse width thld ratio2
                                                     for peak select                                                           */
    } bit;
  } T2_PULSE_WIDTH_CFG;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) * T2_DECODE_CFG *                                          */

    struct {
      __IOM uint32_t RATIO1     : 4;            /*!< [3..0] Pulse width threshold1 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO2     : 4;            /*!< [7..4] Pulse width threshold2 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO3     : 4;            /*!< [11..8] Pulse width threshold3 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO4     : 4;            /*!< [15..12] Pulse width threshold4 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO5     : 4;            /*!< [19..16] Pulse width threshold5 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO6     : 4;            /*!< [23..20] Pulse width threshold6 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO7     : 4;            /*!< [27..24] Pulse width threshold7 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO8     : 4;            /*!< [31..28] Pulse width threshold8 f
                                                     or decode                                                                 */
    } bit;
  } T2_DECODE_CFG;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000030) * T3_PEAK_VALUE_CFG *                                      */

    struct {
      __IOM uint32_t THLD_INIT  : 9;            /*!< [8..0] Initial peak value thres
                                                     hold                                                                      */
      __IOM uint32_t ALPHA      : 4;            /*!< [12..9] Coefficient for peak val
                                                     ue update IIR filter                                                      */
      __IOM uint32_t THLD_RATIO : 4;            /*!< [16..13] Peak value threshold rat
                                                     io                                                                        */
    } bit;
  } T3_PEAK_VALUE_CFG;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000034) * T3_PEAK_WIDTH_CFG *                                      */

    struct {
      __IOM uint32_t THLD_INIT  : 15;           /*!< [14..0] Initial peak value thres
                                                     hold                                                                      */
      __IM  uint32_t            : 1;
      __IOM uint32_t PULSE_WID_RATIO1 : 4;      /*!< [19..16] Pulse width update ratio
                                                     1                                                                         */
      __IOM uint32_t PULSE_WID_RATIO2 : 4;      /*!< [23..20] Pulse width update ratio
                                                     2                                                                         */
      __IOM uint32_t PULSE_WID_RATIO3 : 4;      /*!< [27..24] Pulse width update ratio
                                                     3                                                                         */
      __IOM uint32_t PULSE_WID_RATIO4 : 4;      /*!< [31..28] Pulse width update ratio
                                                     4                                                                         */
    } bit;
  } T3_PEAK_WIDTH_CFG;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000038) * T3_PULSE_WIDTH_CFG *                                     */

    struct {
      __IOM uint32_t SYNC_ZERO_WIN : 3;         /*!< [2..0] Synchronized zero judgem
                                                     ent window                                                                */
      __IOM uint32_t PULSE_WID_MAX : 15;        /*!< [17..3] Maximum pulse width valu
                                                     e                                                                         */
      __IOM uint32_t PULSE_WID_BETA : 4;        /*!< [21..18] Coefficient for pulse wi
                                                     dth threshold IIR filter                                                  */
      __IM  uint32_t            : 2;
      __IOM uint32_t PEAK_SEL_RATIO1 : 4;       /*!< [27..24] Pulse width thld ratio1
                                                     for peak select                                                           */
      __IOM uint32_t PEAK_SEL_RATIO2 : 4;       /*!< [31..28] Pulse width thld ratio2
                                                     for peak select                                                           */
    } bit;
  } T3_PULSE_WIDTH_CFG;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000003C) * T3_DECODE_CFG *                                          */

    struct {
      __IOM uint32_t RATIO1     : 4;            /*!< [3..0] Pulse width threshold1 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO2     : 4;            /*!< [7..4] Pulse width threshold2 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO3     : 4;            /*!< [11..8] Pulse width threshold3 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO4     : 4;            /*!< [15..12] Pulse width threshold4 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO5     : 4;            /*!< [19..16] Pulse width threshold5 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO6     : 4;            /*!< [23..20] Pulse width threshold6 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO7     : 4;            /*!< [27..24] Pulse width threshold7 f
                                                     or decode                                                                 */
      __IOM uint32_t RATIO8     : 4;            /*!< [31..28] Pulse width threshold8 f
                                                     or decode                                                                 */
    } bit;
  } T3_DECODE_CFG;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000040) * STATUS *                                                 */

    struct {
      __IM  uint32_t T1_WR_DONE : 1;            /*!< [0..0] Shared memory write done
                                                     signal for track1                                                         */
      __IM  uint32_t T2_WR_DONE : 1;            /*!< [1..1] Shared memory write done
                                                     signal for track2                                                         */
      __IM  uint32_t T3_WR_DONE : 1;            /*!< [2..2] Shared memory write done
                                                     signal for track3                                                         */
      __IM  uint32_t TIMER_MEET : 1;            /*!< [3..3] Timer meet limit                                                   */
      __IM  uint32_t T1_BUF_FULL : 1;           /*!< [4..4] Track 1 buffer full                                                */
      __IM  uint32_t T2_BUF_FULL : 1;           /*!< [5..5] Track 2 buffer full                                                */
      __IM  uint32_t T3_BUF_FULL : 1;           /*!< [6..6] Track 3 buffer full                                                */
      __IM  uint32_t            : 1;
      __IM  uint32_t T1_RX_DONE : 1;            /*!< [8..8] 7811 decoder rx done sig
                                                     nal for track1                                                            */
      __IM  uint32_t T2_RX_DONE : 1;            /*!< [9..9] 7811 decoder rx done sig
                                                     nal for track2                                                            */
      __IM  uint32_t T3_RX_DONE : 1;            /*!< [10..10] 7811 decoder rx done sig
                                                     nal for track3                                                            */
      __IM  uint32_t T1_FIFO_WR_ERR : 1;        /*!< [11..11] Track 1 fifo write error                                         */
      __IM  uint32_t T2_FIFO_WR_ERR : 1;        /*!< [12..12] Track 2 fifo write error                                         */
      __IM  uint32_t T3_FIFO_WR_ERR : 1;        /*!< [13..13] Track 3 fifo write error                                         */
    } bit;
  } STATUS;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000044) * CHAR_NUM *                                               */

    struct {
      __IM  uint32_t TRACK1     : 8;            /*!< [7..0] Track 1 character number                                           */
      __IM  uint32_t TRACK2     : 8;            /*!< [15..8] Track 2 character number                                          */
      __IM  uint32_t TRACK3     : 8;            /*!< [23..16] Track 3 character number                                         */
    } bit;
  } CHAR_NUM;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000048) * INTERFER_CHAR_NUM *                                      */

    struct {
      __IM  uint32_t TRACK1     : 8;            /*!< [7..0] Track 1 interference cha
                                                     racter number                                                             */
      __IM  uint32_t TRACK2     : 8;            /*!< [15..8] Track 2 interference cha
                                                     racter number                                                             */
      __IM  uint32_t TRACK3     : 8;            /*!< [23..16] Track 3 interference cha
                                                     racter number                                                             */
    } bit;
  } INTERFER_CHAR_NUM;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) * DC_EST *                                                 */

    struct {
      __IM  uint32_t TRACK1     : 10;           /*!< [9..0] Track 1 dc value for dco
                                                     c                                                                         */
      __IM  uint32_t TRACK2     : 10;           /*!< [19..10] Track 2 dc value for dco
                                                     c                                                                         */
      __IM  uint32_t TRACK3     : 10;           /*!< [29..20] Track 3 dc value for dco
                                                     c                                                                         */
    } bit;
  } DC_EST;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000050) * END_ADDR_T1 *                                            */

    struct {
      __IOM uint32_t ISO_END_ADDR : 20;         /*!< [19..0] Character write end addr
                                                     ess for track 1                                                           */
    } bit;
  } END_ADDR_T1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000054) * END_ADDR_T2 *                                            */

    struct {
      __IOM uint32_t ISO_END_ADDR : 20;         /*!< [19..0] Character write end addr
                                                     ess for track 2                                                           */
    } bit;
  } END_ADDR_T2;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000058) * END_ADDR_T3 *                                            */

    struct {
      __IOM uint32_t ISO_END_ADDR : 20;         /*!< [19..0] Character write end addr
                                                     ess for track 3                                                           */
    } bit;
  } END_ADDR_T3;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000005C) * TIMER_LIMIT *                                            */

    struct {
      __IOM uint32_t LIMIT      : 32;           /*!< [31..0] Timer limit for interrup
                                                     t                                                                         */
    } bit;
  } TIMER_LIMIT;
} MISO7811_Type;                                /*!< Size = 96 (0x60)                                                          */



/* =========================================================================================================================== */
/* ================                                        ANA_LDO_CLK                                        ================ */
/* =========================================================================================================================== */


/**
  * @brief 32 ANA_LDO_CLK (ANA_LDO_CLK)
  */

typedef struct {                                /*!< (@ 0x000FB200) ANA_LDO_CLK Structure                                      */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) LDO control                                                */

    struct {
      __IOM uint32_t OTP_LDO_VSEL : 3;          /*!< [2..0] OTP ldo25 voitage selction                                         */
      __IOM uint32_t OTP_LDO_EN : 1;            /*!< [3..3] OTP ldo25 enable                                                   */
      __IOM uint32_t LDO_CARD_VSEL : 2;         /*!< [5..4] 7816 LDO output voltage select                                     */
      __IOM uint32_t LDO_CARD_EN : 1;           /*!< [6..6] 7816 LDO enable                                                    */
      __IOM uint32_t LDO_CARD_OCP_EN : 1;       /*!< [7..7] 7816 LDO over-current protection                                   */
      __IOM uint32_t LDO_CARD_VTRIM : 3;        /*!< [10..8] 7816 LDO output voltage trim                                      */
      __IOM uint32_t LDO_CARD_0P33VDD : 1;      /*!< [11..11] 7816 sink LDO for GPIO floating ground pull down                 */
      __IOM uint32_t LDO_BBPLLVCO_VSEL : 2;     /*!< [13..12] bbpll vco ldo output voltage select                              */
      __IOM uint32_t LDO_BBPLL_VSEL : 2;        /*!< [15..14] bbpll ldo output voltage select                                  */
      __IOM uint32_t LDO_IBLOAD_SEL : 1;        /*!< [16..16] bbpll bleed current sel                                          */
      __IOM uint32_t LDO_HVSEL  : 1;            /*!< [17..17] bbpll ldo high voltage sel                                       */
      __IOM uint32_t LDO_EN_BBPLL2 : 1;         /*!< [18..18] bbpll2 ldo enable                                                */
      __IOM uint32_t LDO_EN_BBPLL1 : 1;         /*!< [19..19] bbpll1 ldo enable                                                */
    } bit;
  } LDO_CTRL;
} ANA_LDO_CLK_Type;                             /*!< Size = 4 (0x4)                                                            */



/* =========================================================================================================================== */
/* ================                                         ANA_BBPLL                                         ================ */
/* =========================================================================================================================== */


/**
  * @brief 32 ANA_BBPLL (ANA_BBPLL)
  */

typedef struct {                                /*!< (@ 0x000FB210) ANA_BBPLL Structure                                        */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) BBPLL1 control                                             */

    struct {
      __IOM uint32_t BBPLL1_CP_IBSEL : 3;       /*!< [2..0] lcp sel                                                            */
      __IM  uint32_t            : 1;
      __IOM uint32_t BBPLL1_CLKGEN_CK48M_WIDTH : 2;/*!< [5..4] pulse width select                                              */
      __IM  uint32_t            : 2;
      __IOM uint32_t BBPLL1_CLKGEN_CK48M_SEL : 1;/*!< [8..8] Pulse width select mode enable                                    */
      __IM  uint32_t            : 7;
      __IOM uint32_t BBPLL1_CLKGEN_CK48M_DIVN : 7;/*!< [22..16] div_ratio of 48MHz                                             */
    } bit;
  } BBPLL1_CTRL0;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) BBPLL1 control                                             */

    struct {
      __IOM uint32_t BBPLL1_DIVR_FRAC : 24;     /*!< [23..0] divr of pll                                                       */
    } bit;
  } BBPLL1_CTRL1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) BBPLL1 control                                             */

    struct {
      __IOM uint32_t BBPLL1_VCO_IBSEL : 2;      /*!< [1..0] Bias current select of vco                                         */
      __IOM uint32_t BBPLL1_RSTN : 1;           /*!< [2..2] Reset signal of pll                                                */
      __IM  uint32_t            : 1;
      __IOM uint32_t BBPLL1_LOOPDIV_WIDTH : 2;  /*!< [5..4] Pulse width select                                                 */
      __IOM uint32_t BBPLL1_LOOPDIV_SEL : 1;    /*!< [6..6] Pulse width select mode enable                                     */
      __IOM uint32_t BBPLL1_FREFDIV2_SEL : 1;   /*!< [7..7] Reference clk div sel                                              */
      __IOM uint32_t BBPLL1_EN_VCO : 1;         /*!< [8..8] VCO enable                                                         */
      __IOM uint32_t BBPLL1_EN_PFDCP : 1;       /*!< [9..9] pfd and chargepump enable                                          */
      __IOM uint32_t BBPLL1_EN_LOOPDIV : 1;     /*!< [10..10] loopdivider enable                                               */
      __IOM uint32_t BBPLL1_EN_CLKGEN_CK48M_DIV2 : 1;/*!< [11..11] 48M div2 enable                                             */
      __IOM uint32_t BBPLL1_EN_CLKGEN_256M : 1; /*!< [12..12] 256M clk_gen enable                                              */
      __IOM uint32_t BBPLL1_EN_CLKGEN_192M : 1; /*!< [13..13] 192M clk_gen enable                                              */
      __IOM uint32_t BBPLL1_EN_CLKGEN_48M : 1;  /*!< [14..14] 48M clk_gen enable                                               */
      __IOM uint32_t BBPLL1_EN_CLKGEN : 1;      /*!< [15..15] clk_gen enable                                                   */
      __IOM uint32_t BBPLL1_DIVR_INT : 6;       /*!< [21..16] divr of pll                                                      */
    } bit;
  } BBPLL1_CTRL2;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) BBPLL2 control                                             */

    struct {
      __IOM uint32_t BBPLL2_CP_IBSEL : 3;       /*!< [2..0] lcp sel                                                            */
      __IM  uint32_t            : 1;
      __IOM uint32_t BBPLL2_CLKGEN_CK48M_WIDTH : 2;/*!< [5..4] pulse width select                                              */
      __IM  uint32_t            : 2;
      __IOM uint32_t BBPLL2_CLKGEN_CK48M_SEL : 1;/*!< [8..8] Pulse width select mode enable                                    */
      __IM  uint32_t            : 7;
      __IOM uint32_t BBPLL2_CLKGEN_CK48M_DIVN : 7;/*!< [22..16] div_ratio of 48MHz                                             */
    } bit;
  } BBPLL2_CTRL0;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) BBPLL2 control                                             */

    struct {
      __IOM uint32_t BBPLL2_DIVR_FRAC : 24;     /*!< [23..0] divr of pll                                                       */
    } bit;
  } BBPLL2_CTRL1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) BBPLL2 control                                             */

    struct {
      __IOM uint32_t BBPLL2_VCO_IBSEL : 2;      /*!< [1..0] Bias current select of vco                                         */
      __IOM uint32_t BBPLL2_RSTN : 1;           /*!< [2..2] Reset signal of pll                                                */
      __IM  uint32_t            : 1;
      __IOM uint32_t BBPLL2_LOOPDIV_WIDTH : 2;  /*!< [5..4] Pulse width select                                                 */
      __IOM uint32_t BBPLL2_LOOPDIV_SEL : 1;    /*!< [6..6] Pulse width select mode enable                                     */
      __IOM uint32_t BBPLL2_FREFDIV2_SEL : 1;   /*!< [7..7] Reference clk div sel                                              */
      __IOM uint32_t BBPLL2_EN_VCO : 1;         /*!< [8..8] VCO enable                                                         */
      __IOM uint32_t BBPLL2_EN_PFDCP : 1;       /*!< [9..9] pfd and chargepump enable                                          */
      __IOM uint32_t BBPLL2_EN_LOOPDIV : 1;     /*!< [10..10] loopdivider enable                                               */
      __IOM uint32_t BBPLL2_EN_CLKGEN_CK48M_DIV2 : 1;/*!< [11..11] 48M div2 enable                                             */
      __IOM uint32_t BBPLL2_EN_CLKGEN_256M : 1; /*!< [12..12] 256M clk_gen enable                                              */
      __IOM uint32_t BBPLL2_EN_CLKGEN_192M : 1; /*!< [13..13] 192M clk_gen enable                                              */
      __IOM uint32_t BBPLL2_EN_CLKGEN_48M : 1;  /*!< [14..14] 48M clk_gen enable                                               */
      __IOM uint32_t BBPLL2_EN_CLKGEN : 1;      /*!< [15..15] clk_gen enable                                                   */
      __IOM uint32_t BBPLL2_DIVR_INT : 6;       /*!< [21..16] divr of pll                                                      */
    } bit;
  } BBPLL2_CTRL2;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) BBPLL control                                              */

    struct {
      __IOM uint32_t BBPLL_TST_SEL : 3;         /*!< [2..0] pll test select                                                    */
      __IOM uint32_t BBPLL_TST_EN_VCTRL : 1;    /*!< [3..3] vctrl test enable                                                  */
      __IOM uint32_t BBPLL_TST_EN_CK : 1;       /*!< [4..4] clk test enable                                                    */
      __IOM uint32_t BBPLL_TST_EN : 1;          /*!< [5..5] pll test enable                                                    */
      __IOM uint32_t BBPLL_TST_CKSEL : 1;       /*!< [6..6] clk test select                                                    */
      __IOM uint32_t BBPLL_PFD_TONSEL : 1;      /*!< [7..7] pfd ton select                                                     */
      __IOM uint32_t BBPLL_PFD_PWERES_SEL : 2;  /*!< [9..8] Power Res select                                                   */
      __IOM uint32_t BBPLL_DSM_ORDER_SEL : 1;   /*!< [10..10] DSM mesh order select                                            */
      __IOM uint32_t BBPLL_DSM_DITHEREN : 1;    /*!< [11..11] DSM dither enable                                                */
      __IOM uint32_t BBPLL2_PFD_FREF_PHSEL : 1; /*!< [12..12] fref phase select                                                */
      __IOM uint32_t BBPLL2_PFD_FDIV_PHSEL : 1; /*!< [13..13] fdiv phase select                                                */
      __IOM uint32_t BBPLL2_DSM_CKSEL : 1;      /*!< [14..14] DSM clk select                                                   */
      __IOM uint32_t BBPLL2_DSM_CK_PHSEL : 1;   /*!< [15..15] DSM clk phase select                                             */
      __IOM uint32_t BBPLL1_PFD_FREF_PHSEL : 1; /*!< [16..16] fref phase select                                                */
      __IOM uint32_t BBPLL1_PFD_FDIV_PHSEL : 1; /*!< [17..17] fdiv phase select                                                */
      __IOM uint32_t BBPLL1_DSM_CKSEL : 1;      /*!< [18..18] DSM clk select                                                   */
      __IOM uint32_t BBPLL1_DSM_CK_PHSEL : 1;   /*!< [19..19] DSM clk phase select                                             */
      __IOM uint32_t BBPLL_CKIN_SEL : 2;        /*!< [21..20] PLL clk input select                                             */
      __IOM uint32_t RG_BBPLL_CLKGEN_PWERES_SEL : 2;/*!< [23..22] Power Res select                                             */
    } bit;
  } BBPLL_CTRL;
} ANA_BBPLL_Type;                               /*!< Size = 28 (0x1c)                                                          */



/* =========================================================================================================================== */
/* ================                                          ANA_MCR                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief 32 ANA_MCR (ANA_MCR)
  */

typedef struct {                                /*!< (@ 0x000FB230) ANA_MCR Structure                                          */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) MCR control                                                */

    struct {
      __IM  uint32_t            : 9;
      __IOM uint32_t ADC_CLK_EN : 1;            /*!< [9..9] MCR ADC clock enable                                               */
      __IOM uint32_t ADC_EN     : 1;            /*!< [10..10] MCR ADC enable                                                   */
      __IOM uint32_t ADC_EN_BIASGEN : 1;        /*!< [11..11] MCR ADC reference voltage enable                                 */
      __IOM uint32_t ADC_EN_CONSTGM : 1;        /*!< [12..12] MCR ADC constant Gm bias enable                                  */
      __IOM uint32_t ADC_EN_REG : 1;            /*!< [13..13] MCR ADC regulator enable                                         */
      __IOM uint32_t ADC_CLKSEL : 2;            /*!< [15..14] MCR ADC clock select                                             */
      __IOM uint32_t DCOC_PGA0  : 6;            /*!< [21..16] MCR CH0 PGA DCOC DAC input                                       */
      __IOM uint32_t ADC_REFBUF_VREF : 2;       /*!< [23..22] MCR ADC differential reference voltage control                   */
      __IOM uint32_t DCOC_PGA1  : 6;            /*!< [29..24] MCR CH1 PGA DCOC DAC input                                       */
      __IOM uint32_t ADC_REGA_VCTRL : 2;        /*!< [31..30] MCR ADC analog regulator output voltage control                  */
    } bit;
  } CTRL0;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) MCR control                                                */

    struct {
      __IOM uint32_t DCOC_PGA2  : 6;            /*!< [5..0] MCR CH2 PGA DCOC DAC input                                         */
      __IOM uint32_t ADC_REGD_VCTRL : 2;        /*!< [7..6] MCR ADC digital regulator output voltage control                   */
      __IOM uint32_t ADC_IBC_REFBUF : 3;        /*!< [10..8] MCR ADC differential reference voltage buffer bias current
                                                     control                                                                   */
      __IOM uint32_t ADC_IBC_REFBUF2 : 1;       /*!< [11..11] MCR ADC bias voltage buffer bias current control                 */
      __IOM uint32_t ADC_VCTRL_BIASGEN : 3;     /*!< [14..12] MCR ADC bias voltage control                                     */
      __IOM uint32_t PGA0_EN    : 1;            /*!< [15..15] MCR CH0 PGA enable                                               */
      __IOM uint32_t PGA_CSEL   : 3;            /*!< [18..16] MCR lowpass cap selection cap                                    */
      __IOM uint32_t PGA1_EN    : 1;            /*!< [19..19] MCR CH1 PGA enable                                               */
      __IOM uint32_t PGA_IOUTSEL : 3;           /*!< [22..20] MCR PAG output current enhance                                   */
      __IOM uint32_t PGA2_EN    : 1;            /*!< [23..23] MCR CH2 PGA enable                                               */
      __IOM uint32_t PGA_R1SEL  : 3;            /*!< [26..24] pag input resistor selection                                     */
      __IOM uint32_t PGA_VCM_GEN_EN : 1;        /*!< [27..27] MCR PGA input common mode buffer enable                          */
      __IM  uint32_t            : 3;
      __IOM uint32_t PGA_CM_EN  : 1;            /*!< [31..31] MCR PGA input common mode feedback enable                        */
    } bit;
  } CTRL1;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) MCR control                                                */

    struct {
      __IM  uint32_t            : 8;
      __IOM uint32_t PGA_RES_BYPASS : 1;        /*!< [8..8] MCR control                                                        */
      __IM  uint32_t            : 2;
      __IOM uint32_t PGA_LDO_EN : 1;            /*!< [11..11] MCR PGA LDO enable                                               */
      __IOM uint32_t ADC_CHANNEL_SEL : 2;       /*!< [13..12] mcr adc test channel sel                                         */
      __IOM uint32_t ADC_CHANNEL_EN : 1;        /*!< [14..14] mcr adc test channel enable                                      */
      __IOM uint32_t ADC_OUT_EN : 1;            /*!< [15..15] MCR adc input connect to test pad enable                         */
      __IOM uint32_t PGA0_GC    : 5;            /*!< [20..16] MCR CH0 PGA gain control                                         */
      __IOM uint32_t PGA1_GC    : 5;            /*!< [25..21] MCR CH1 PGA gain control                                         */
      __IOM uint32_t PGA2_GC    : 5;            /*!< [30..26] MCR CH2 PGA gain control                                         */
    } bit;
  } CTRL2;
} ANA_MCR_Type;                                 /*!< Size = 12 (0xc)                                                           */



/* =========================================================================================================================== */
/* ================                                        ADC_ANALOG                                         ================ */
/* =========================================================================================================================== */


/**
  * @brief 32 ADC_ANALOG (ADC_ANALOG)
  */

typedef struct {                                /*!< (@ 0x000FB240) ADC_ANALOG Structure                                       */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) ADC_CTRL0                                                  */

    struct {
      __IOM uint32_t MISC_SARADC_EN_REG : 1;    /*!< [0..0] GPADC regulator enable. 0: off; 1: on                              */
      __IOM uint32_t MISC_SARADC_EN_CONSTGM : 1;/*!< [1..1] GPADC constant Gm bias enable. 0: off; 1: on                       */
      __IOM uint32_t MISC_SARADC_EN_BIASGEN : 1;/*!< [2..2] GPADC reference voltage enable. 0: off; 1: on                      */
      __IOM uint32_t MISC_SARADC_EN : 1;        /*!< [3..3] GPADC enable. 0: off; 1: on                                        */
      __IOM uint32_t MISC_SARADC_clk            : 2;
      __IM  uint32_t  							: 2;
      __IOM uint32_t MISC_GBG_FASTSETTLING : 1; /*!< [8..8] The global bandgap fast settling enable                            */
      __IOM uint32_t MISC_GBG_EN : 1;           /*!< [9..9] The global bandgap enable                                          */
    } bit;
  } ADC_CTRL0;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) ADC_CTRL1                                                  */

    struct {
      __IOM uint32_t MISC_SARADC_VCTRL_BIASGEN : 3;/*!< [2..0] GPADC bias voltage control 425mV+25mV*misc_saradc_vctrl_biasgen */
      __IOM uint32_t MISC_SARADC_SEL_CH_S : 3;  /*!< [5..3] GPADC channel select                                               */
      __IOM uint32_t MISC_SARADC_REGD_VCTRL : 2;/*!< [7..6] GPADC digital regulator output voltage control. 0: 1.0V;
                                                     1: 1.1V; 2: 1.2V; 3: 1.3V                                                 */
      __IOM uint32_t MISC_SARADC_REGA_VCTRL : 2;/*!< [9..8] GPADC analog regulator output voltage control. 0: 1.0V;
                                                     1: 1.1V; 2: 1.2V; 3: 1.3V                                                 */
      __IOM uint32_t MISC_SARADC_REFBUF_VREF_CTRL : 2;/*!< [11..10] GPADC differential reference voltage control.              */
      __IOM uint32_t MISC_SARADC_MODE : 3;      /*!< [14..12] 0=gpio,1=gpio diff,2=hvin,3=vinlpm,4=temperature                 */
      __IOM uint32_t MISC_SARADC_IBUF_GC : 2;   /*!< [16..15] GPADC full scale control                                         */
      __IOM uint32_t MISC_SARADC_IBUF_EN_RC : 1;/*!< [17..17] GPADC input buffer feedback capacitor enable                     */
      __IOM uint32_t MISC_SARADC_IBUF_BW : 2;   /*!< [19..18] GPADC input buffer bandwidth control                             */
      __IOM uint32_t MISC_SARADC_IBC_REFBUF : 3;/*!< [22..20] GPADC differential reference voltage buffer bias current
                                                     control                                                                   */
      __IOM uint32_t MISC_SARADC_IBC_REFBUF2 : 1;/*!< [23..23] GPADC bias voltage buffer bias current control                  */
      __IOM uint32_t MISC_SARADC_IBC_IBUF : 3;  /*!< [26..24] GPAADC input buffer bias control                                 */
      __IOM uint32_t MISC_SARADC_IBC_CMBUF : 1; /*!< [27..27] GPADC biasgen buffer bias current control                        */
    } bit;
  } ADC_CTRL1;
} ADC_ANALOG_Type;                              /*!< Size = 8 (0x8)                                                            */



/* =========================================================================================================================== */
/* ================                                          ANA_RNG                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief 32 ANA_RNG (ANA_RNG)
  */

typedef struct {                                /*!< (@ 0x000FB260) ANA_RNG Structure                                          */

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) RNG control                                                */

    struct {
      __IM  uint32_t            : 17;
      __IOM uint32_t RG_NCS_I_SET : 3;          /*!< [19..17] NCS current setting                                              */
      __IOM uint32_t DA_NCS_EN  : 1;            /*!< [20..20] NCS enable                                                       */
      __IOM uint32_t DA_NCS_RESETN : 1;         /*!< [21..21] NCS reset                                                        */
      __IOM uint32_t DA_LDO_TRNG_EN : 1;        /*!< [22..22] Security TRNG LDO enable.                                        */
      __IOM uint32_t DA_TRNG_BIAS_EN : 1;       /*!< [23..23] TRNG bias enable signal, high active                             */
      __IOM uint32_t DA_TRNG_TRNGA_OSCJ_EN : 1; /*!< [24..24] TRNGA LFOSC enable signal,high active                            */
      __IOM uint32_t DA_TRNG_TRNGB_OSCJ_EN : 1; /*!< [25..25] TRNGB LFOSC enable signal,high active                            */
      __IOM uint32_t DA_TRNG_TRNGC_OSCJ_EN : 1; /*!< [26..26] TRNGC LFOSC enable signal,high active                            */
      __IOM uint32_t DA_TRNG_TRNGD_OSCJ_EN : 1; /*!< [27..27] TRNGD LFOSC enable signal,high active                            */
      __IOM uint32_t DA_TRNG_TRNGOA_EN : 1;     /*!< [28..28] TRNGA HFOSC enable signal,high active                            */
      __IOM uint32_t DA_TRNG_TRNGOB_EN : 1;     /*!< [29..29] TRNGB HFOSC enable signal,high active                            */
      __IOM uint32_t DA_TRNG_TRNGOC_EN : 1;     /*!< [30..30] TRNGC HFOSC enable signal,high active                            */
      __IOM uint32_t DA_TRNG_TRNGOD_EN : 1;     /*!< [31..31] TRNGD HFOSC enable signal,high active                            */
    } bit;
  } RNG_CTRL0;

  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) RNG control                                                */

    struct {
      __IOM uint32_t RG_TRNG_TRNGA_ON_JITTER : 2;/*!< [1..0] TRNGA LFOSC jitter control signal                                 */
      __IOM uint32_t RG_TRNG_TRNGA_OSCJ_TRIM : 2;/*!< [3..2] TRNGA LFOSC frequency control signal                              */
      __IOM uint32_t RG_TRNG_TRNGA_OSCJ_VREF : 3;/*!< [6..4] TRNGA LFOSC vref control signal                                   */
      __IOM uint32_t DA_TRNG_TRNGOA_CLR : 1;    /*!< [7..7] TRNGA sample DFF output clear signal,low active                    */
      __IOM uint32_t RG_TRNG_TRNGB_ON_JITTER : 2;/*!< [9..8] TRNGB LFOSC jitter control signal                                 */
      __IOM uint32_t RG_TRNG_TRNGB_OSCJ_TRIM : 2;/*!< [11..10] TRNGB LFOSC frequency control signal                            */
      __IOM uint32_t RG_TRNG_TRNGB_OSCJ_VREF : 3;/*!< [14..12] TRNGB LFOSC vref control signal                                 */
      __IOM uint32_t DA_TRNG_TRNGOB_CLR : 1;    /*!< [15..15] TRNGB sample DFF output clear signal,low active                  */
      __IOM uint32_t RG_TRNG_TRNGC_ON_JITTER : 2;/*!< [17..16] TRNGC LFOSC jitter control signal                               */
      __IOM uint32_t RG_TRNG_TRNGC_OSCJ_TRIM : 2;/*!< [19..18] TRNGC LFOSC frequency control signal                            */
      __IOM uint32_t RG_TRNG_TRNGC_OSCJ_VREF : 3;/*!< [22..20] TRNGC LFOSC vref control signal                                 */
      __IOM uint32_t DA_TRNG_TRNGOC_CLR : 1;    /*!< [23..23] TRNGC sample DFF output clear signal,low active                  */
      __IOM uint32_t RG_TRNG_TRNGD_ON_JITTER : 2;/*!< [25..24] TRNGD LFOSC jitter control signal                               */
      __IOM uint32_t RG_TRNG_TRNGD_OSCJ_TRIM : 2;/*!< [27..26] TRNGD LFOSC frequency control signal                            */
      __IOM uint32_t RG_TRNG_TRNGD_OSCJ_VREF : 3;/*!< [30..28] TRNGD LFOSC vref control signal                                 */
      __IOM uint32_t DA_TRNG_TRNGOD_CLR : 1;    /*!< [31..31] TRNGD sample DFF output clear signal,low active                  */
    } bit;
  } RNG_CTRL1;
} ANA_RNG_Type;                                 /*!< Size = 8 (0x8)                                                            */

/* =========================================================================================================================== */
/* ================                                          ANA_CHGR                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief 32 ANA_CHGR (ANA_CHGR)
  */

typedef struct {                                /*!< (@ 0x000FB270) ANA_CHGR Structure                                          */

    union {
        __IM uint32_t reg;                         /*!< (@ 0x00000000) CHGR state                                                */

        struct {
            __IM uint32_t CHGR_STATE_VBAT_LV : 1;
            __IM uint32_t CHGR_STATE_RCH_EN : 1;
            __IM uint32_t CHGR_STATE_IND : 1;
            __IM uint32_t CHGR_STATE_ICHG : 1;
            __IM uint32_t CHGR_RESET : 1;
            __IM uint32_t CHGR_UVLO_OK_AON : 1;
            __IM uint32_t CHGR_PGOOD : 1;
            __IM uint32_t CHGR_DPPM_OV_CV : 1;
            __IM uint32_t CHGR_DPPM_OV_CC : 1;
            __IM uint32_t CHGR_CC_OV_CV : 1;
            __IM uint32_t CHGR_IN_DET_AON : 1;
            __IM uint32_t VBAT_OV_FLAG : 1;
        } bit;
    } STATE;
} ANA_CHGR_Type;                                 /*!< Size = 4 (0x4)                                                            */
/** @} */ /* End of group Device_Peripheral_peripherals */


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */

#define MMCU_BASE                   0x000D0000UL
#define MMPU_BASE                   0x000D8080UL
#define MDCMI_BASE                  0x000D8200UL
#define MHSPI_BASE                  0x000D8400UL
#define MWDT_BASE                   0x000F0000UL
#define MSCI0_BASE                  0x000F0400UL
#define MSCI1_BASE                  0x000F0800UL
#define MTIM_BASE                   0x000F0C00UL
#define MCRC_BASE                   0x000F8204UL
#define MRCC_BASE                   0x000F8400UL
#define MSYSCTRL_BASE               0x000F8520UL
#define MRSTGEN_BASE                0x000F8574UL
#define MSECURE_BASE                0x000F85C0UL
#define MGPIO_BASE                  0x000F8700UL
#define MDMA_BASE                   0x000F8800UL
#define MDMA_QSPI_BASE              0x000F8800UL
#define MDMA_SPI0_BASE              0x000F8900UL
#define MDMA_SPI1_BASE              0x000F8A00UL
#define MDMA_UART0_BASE             0x000F8B00UL
#define MDMA_UART1_BASE             0x000F8C00UL
#define MDMA_UART2_BASE             0x000F8D00UL
#define MDMA_UART3_BASE             0x000F8E00UL
#define MDMA_7811_BASE              0x000F8F00UL
#define MDMA_MEMCP_BASE             0x000F9000UL
#define MDMA_IIC0_BASE              0x000F9100UL
#define MDMA_IIC1_BASE              0x000F9200UL
#define MSPI_BASE                   0x000F891CUL
#define MSPI0_BASE                  0x000F891CUL
#define MSPI1_BASE                  0x000F8A1CUL
#define MUART_BASE                  0x000F8B1CUL
#define MUART0_BASE                 0x000F8B1CUL
#define MUART1_BASE                 0x000F8C1CUL
#define MUART2_BASE                 0x000F8D1CUL
#define MUART3_BASE                 0x000F8E1CUL
#define MIIC_BASE                   0x000F911CUL
#define MI2C0_BASE                  0x000F911CUL
#define MI2C1_BASE                  0x000F921CUL
#define MLPM_BASE                   0x000FA800UL
#define MBPK_BASE                   0x000FAC00UL
#define MSEC_BASE                   0x000FAE00UL
#define MRTC_BASE                   0x000FAF00UL
#define MRTCLSI_BASE                0x000FAF00UL
#define MRTCLSE_BASE                0x000FB000UL
#define MADC_BASE                   0x000FBB00UL
#define MISO7811_BASE               0x000F8F00UL
#define ANA_LDO_CLK_BASE            0x000FB200UL
#define ANA_BBPLL_BASE              0x000FB210UL
#define ANA_MCR_BASE                0x000FB230UL
#define ADC_ANALOG_BASE             0x000FB240UL
#define ANA_RNG_BASE                0x000FB260UL
#define ANA_CHGR_BASE               0x000FB270UL
/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define MMCU                        ((MMCU_Type*)              MMCU_BASE)
#define MMPU                        ((MMPU_Type*)			   MMPU_BASE)
#define MDCMI                       ((MDCMI_Type*) 			   MDCMI_BASE)
#define MHSPI                       ((MHSPI_Type*)             MHSPI_BASE)
#define MWDT                        ((MWDT_Type*)              MWDT_BASE)
#define MSCI0                       ((MSCI0_Type*)             MSCI0_BASE)
#define MSCI1                       ((MSCI0_Type*)             MSCI1_BASE)
#define MTIM                        ((MTIM_Type*)              MTIM_BASE)
#define MCRC                        ((MCRC_Type*)              MCRC_BASE)
#define MRCC                        ((MRCC_Type*)              MRCC_BASE)
#define MSYSCTRL                    ((MSYSCTRL_Type*)          MSYSCTRL_BASE)
#define MRSTGEN                     ((MRSTGEN_Type*)           MRSTGEN_BASE)
#define MSECURE                     ((MSECURE_Type*)           MSECURE_BASE)
#define MGPIO                       ((MGPIO_Type*)             MGPIO_BASE)
#define MDMA                        ((MDMA_Type*)              MDMA_BASE)
#define MDMA_QSPI                   ((MDMA_Type*)              MDMA_QSPI_BASE)
#define MDMA_SPI0                   ((MDMA_Type*)              MDMA_SPI0_BASE)
#define MDMA_SPI1                   ((MDMA_Type*)              MDMA_SPI1_BASE)
#define MDMA_UART0                  ((MDMA_Type*)              MDMA_UART0_BASE)
#define MDMA_UART1                  ((MDMA_Type*)              MDMA_UART1_BASE)
#define MDMA_UART2                  ((MDMA_Type*)              MDMA_UART2_BASE)
#define MDMA_UART3                  ((MDMA_Type*)              MDMA_UART3_BASE)
#define MDMA_7811                   ((MDMA_Type*)              MDMA_7811_BASE)
#define MDMA_MEMCP                  ((MDMA_Type*)              MDMA_MEMCP_BASE)
#define MDMA_IIC0                   ((MDMA_Type*)              MDMA_IIC0_BASE)
#define MDMA_IIC1                   ((MDMA_Type*)              MDMA_IIC1_BASE)
#define MSPI                        ((MSPI_Type*)              MSPI_BASE)
#define MSPI0                       ((MSPI_Type*)              MSPI0_BASE)
#define MSPI1                       ((MSPI_Type*)              MSPI1_BASE)
#define MUART                       ((MUART_Type*)             MUART_BASE)
#define MUART0                      ((MUART_Type*)             MUART0_BASE)
#define MUART1                      ((MUART_Type*)             MUART1_BASE)
#define MUART2                      ((MUART_Type*)             MUART2_BASE)
#define MUART3                      ((MUART_Type*)             MUART3_BASE)
#define MIIC                        ((MIIC_Type*)              MIIC_BASE)
#define MI2C0                       ((MIIC_Type*)              MI2C0_BASE)
#define MI2C1                       ((MIIC_Type*)              MI2C1_BASE)
#define MLPM                        ((MLPM_Type*)              MLPM_BASE)
#define MBPK                        ((MBPK_Type*)              MBPK_BASE)
#define MSEC                        ((MSEC_Type*)              MSEC_BASE)
#define MRTC                        ((MRTC_Type*)              MRTC_BASE)
#define MRTCLSI                     ((MRTC_Type*)              MRTCLSI_BASE)
#define MRTCLSE                     ((MRTC_Type*)              MRTCLSE_BASE)
#define MADC                        ((MADC_Type*)              MADC_BASE)
#define MISO7811                    ((MISO7811_Type*)          MISO7811_BASE)
#define ANA_LDO_CLK                 ((ANA_LDO_CLK_Type*)       ANA_LDO_CLK_BASE)
#define ANA_BBPLL                   ((ANA_BBPLL_Type*)         ANA_BBPLL_BASE)
#define ANA_MCR                     ((ANA_MCR_Type*)           ANA_MCR_BASE)
#define ADC_ANALOG                  ((ADC_ANALOG_Type*)        ADC_ANALOG_BASE)
#define ANA_RNG                     ((ANA_RNG_Type*)           ANA_RNG_BASE)
#define ANA_CHGR                    ((ANA_CHGR_Type*)          ANA_CHGR_BASE)


#define MCU_TypeDef                 MMCU_Type
#define DCMI_TypeDef                MDCMI_Type
#define HSPI_TypeDef                MHSPI_Type
#define WDT_TypeDef                 MWDT_Type
#define SCI7816_TypeDef             MSCI0_Type
#define TIM_Module_TypeDef          MTIM_Type
#define RCC_TypeDef                 MRCC_Type
#define SYSCTRL_TypeDef             MSYSCTRL_Type
#define RSTGEN_TypeDef              MRSTGEN_Type
#define SECURE_TypeDef              MSECURE_Type
#define DMA_TypeDef                 MDMA_Type
#define SPI_TypeDef                 MSPI_Type
#define UART_TypeDef                MUART_Type
#define ISO7811_TypeDef             MISO7811_Type
#define I2C_TypeDef                 MIIC_Type
#define LPM_TypeDef                 MLPM_Type
#define BPK_TypeDef                 MBPK_Type
#define SEC_TypeDef                 MSEC_Type
#define RTC_TypeDef                 MRTC_Type
#define ANA_LDO_CLK_TypeDef         ANA_LDO_CLK_Type
#define ANA_BBPLL_TypeDef           ANA_BBPLL_Type
#define ANA_MCR_TypeDef             ANA_MCR_Type
#define ADC_ANALOG_TypeDef          ADC_ANALOG_Type
#define ANA_RNG_TypeDef             ANA_RNG_Type
#define ANA_CHGR_TypeDef            ANA_CHGR_Type
#define ADC_TypeDef                 MADC_Type
/** @} */ /* End of group Device_Peripheral_peripherals */

#define YC3122_FLASH_BASE           (0x01000000UL)   /*!< (FLASH     )      Base Address */
#define YC3122_SRAM_BASE            (0x00020000UL)   /*!< (SRAM      )      Base Address */
#define YC3122_PERIPH_BASE          (0x000B0000UL)   /*!< (Peripheral)      Base Address */
#define YC3122_FPERIPH_BASE         (0x000D0000UL)   /*!< (fast Peripheral) Base Address>*/
#define YC3122_SRAM_SIZE            (0x80000)
#define YC3122_OTP_BASE             (0x00000000UL)
#define YC3122_OTP_SIZE             (0x2000)


/* =========================================  End of section using anonymous unions  ========================================= */
#if defined (__CC_ARM)
#pragma pop
#elif defined (__ICCARM__)
/* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic pop
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#elif defined (__TMS470__)
/* anonymous unions are enabled by default */
#elif defined (__TASKING__)
#pragma warning restore
#elif defined (__CSMC__)
/* anonymous unions are enabled by default */
#endif

/** @addtogroup Exported_constants
  * @{
  */

/** @addtogroup Peripheral_Registers_Bits_Definition
  * @{
  */

/******************************************************************************/
/*                     Peripheral Registers_Bits_Definition                   */
/******************************************************************************/
/******************  Bit definition for TIM_CTRL register  ********************/
#define TIM_CTRL_ENABLE         BIT0
#define TIM_CTRL_START_LEVEL    BIT1
#define TIM_CTRL_MODE           BIT2
#define TIM_CTRL_AUTO_RELOAD    BIT3

/********************  Bit definition for rst register  ***********************/
#define SW_RST                  ((uint8_t)0x55)
#define SCI_RST                 ((uint8_t)0xAB)
#define MSR_RST                 ((uint8_t)0xC3)

/*******************  Bit definition for BPK_LR register  *********************/
#define BPK_LR_LOCK_SELF        BIT0
#define BPK_LR_LOCK_KEYWRITE    BIT1
#define BPK_LR_LOCK_KEYREAD     BIT2
#define BPK_LR_LOCK_KEYCLEAR    BIT3
#define BPK_LR_LOCK_RESET       BIT4
#define BPK_LR_LOCK_ALL         (BIT1|BIT2|BIT3|BIT4)

/******************  Bit definition for SENSOR_LR register  *******************/
#define SEC_LOCK_LOCK           BIT0
#define ACTION_LOCK             BIT1
#define TAMPER_LOCK             BIT2
#define SENSOR_LOCK             BIT3
#define SHIELD_LOCK             BIT4
#define SENSOR_LOCK_ALL         (BIT1|BIT2|BIT3|BIT4)

/******************  Bit definition for RTC_IRQ register  *********************/
#define RTC_SECOND_IRQ          BIT0
#define RTC_ALARM_IRQ           BIT1
#define RTC_ALL_IRQ             (BIT0|BIT1)

#ifdef __cplusplus
}
#endif

#endif  /* __YC3122_H__ */

/** @} */ /* End of group YC3122 */

/** @} */ /* End of group  */
