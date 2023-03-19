#ifndef __BL702_H__
#define __BL702_H__

/* This file had been modified, add USB_IRQn=43 for temp test, the irq value 43 should be checked after all. */

/** @addtogroup Configuration_section_for_RISCV
  * @{
  */

/**
  * @brief Configuration of the Processor and Core Peripherals
   */

/* fix 57.6M */
#define SystemCoreClockSet(val)                     \
    if (val == 57 * 6000 * 1000) {                  \
        BL_WR_WORD(0x4000F108, 57.6 * 1000 * 1000); \
    } else {                                        \
        BL_WR_WORD(0x4000F108, val);                \
    }
#define SystemCoreClockGet(val) BL_RD_WORD(0x4000F108)

/**
  * @}
  */

/** @addtogroup Peripheral_interrupt_number_definition
  * @{
  */

#ifdef ARCH_ARM
#define IRQ_NUM_BASE 0
#endif

#ifdef ARCH_RISCV
#define IRQ_NUM_BASE 16
#endif
/**
 * @brief BL702 Interrupt Number Definition, according to the selected device
 *        in @ref Library_configuration_section
 */
typedef enum {
#ifdef ARCH_ARM
    /******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
    NonMaskableInt_IRQn = -14,   /*!< 2 Cortex-M4 Non Maskable Interrupt                                */
    HardFault_IRQn = -13,        /*!< 3 Cortex-M4 Hard Fault Interrupt                                  */
    MemoryManagement_IRQn = -12, /*!< 4 Cortex-M4 Memory Management Interrupt                           */
    BusFault_IRQn = -11,         /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
    UsageFault_IRQn = -10,       /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
    SVCall_IRQn = -5,            /*!< 11 Cortex-M4 SV Call Interrupt                                    */
    DebugMonitor_IRQn = -4,      /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
    PendSV_IRQn = -2,            /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
    SysTick_IRQn = -1,           /*!< 15 Cortex-M4 System Tick Interrupt                                */
#endif
#ifdef ARCH_RISCV
    MSOFT_IRQn = 3,           /*!< 3 RISCV machine software Interrupt                                */
    MTIME_IRQn = 7,           /*!< 7 RISCV machine time Interrupt                                    */
    MEXT_IRQn = 11,           /*!< 11 RISCV external  Interrupt                                      */
    CLIC_SOFT_PEND_IRQn = 12, /*!< 12 RISCV CLIC software pending  Interrupt                         */
#endif
    /******  BL702 specific Interrupt Numbers **********************************************************************/
    BMX_ERR_IRQn = IRQ_NUM_BASE + 0,           /*!< BMX Error Interrupt                                               */
    BMX_TO_IRQn = IRQ_NUM_BASE + 1,            /*!< BMX Timeout Interrupt                                             */
    L1C_BMX_ERR_IRQn = IRQ_NUM_BASE + 2,       /*!< L1C BMX Error Interrupt                                           */
    L1C_BMX_TO_IRQn = IRQ_NUM_BASE + 3,        /*!< L1C BMX Timeout Interrupt                                         */
    SEC_BMX_ERR_IRQn = IRQ_NUM_BASE + 4,       /*!< SEC BMX Error Interrupt                                           */
    RF_TOP_INT0_IRQn = IRQ_NUM_BASE + 5,       /*!< RF_TOP_INT0 Interrupt                                             */
    RF_TOP_INT1_IRQn = IRQ_NUM_BASE + 6,       /*!< RF_TOP_INT1 Interrupt                                             */
    RESERVED0 = IRQ_NUM_BASE + 7,              /*!< RESERVED Interrupt                                                */
    DMA_BMX_ERR_IRQn = IRQ_NUM_BASE + 8,       /*!< DMA BMX Error Interrupt                                           */
    SEC_GMAC_IRQn = IRQ_NUM_BASE + 9,          /*!< SEC_ENG_GMAC_INT Interrupt                                        */
    SEC_CDET_IRQn = IRQ_NUM_BASE + 10,         /*!< SEC_ENG_CDET_INT Interrupt                                        */
    SEC_PKA_IRQn = IRQ_NUM_BASE + 11,          /*!< SEC_ENG_PKA_INT  Interrupt                                        */
    SEC_TRNG_IRQn = IRQ_NUM_BASE + 12,         /*!< SEC_ENG_TRNG_INT Interrupt                                        */
    SEC_AES_IRQn = IRQ_NUM_BASE + 13,          /*!< SEC_ENG_AES_INT  Interrupt                                        */
    SEC_SHA_IRQn = IRQ_NUM_BASE + 14,          /*!< SEC_ENG_SHA_INT  Interrupt                                        */
    DMA_ALL_IRQn = IRQ_NUM_BASE + 15,          /*!< DMA ALL Interrupt                                                 */
    MJPEG_IRQn = IRQ_NUM_BASE + 16,            /*!< MJPEG Interrupt                                                   */
    CAM_IRQn = IRQ_NUM_BASE + 17,              /*!< CAM Interrupt                                                     */
    I2S_IRQn = IRQ_NUM_BASE + 18,              /*!< I2S Interrupt                                                     */
    IRTX_IRQn = IRQ_NUM_BASE + 19,             /*!< IR TX Interrupt                                                   */
    IRRX_IRQn = IRQ_NUM_BASE + 20,             /*!< IR RX Interrupt                                                   */
    USB_IRQn = IRQ_NUM_BASE + 21,              /*!< USB Interrupt                                                     */
    EMAC_IRQn = IRQ_NUM_BASE + 22,             /*!< EMAC  Interrupt                                                   */
    SF_CTRL_IRQn = IRQ_NUM_BASE + 23,          /*!< SF_CTRL   Interrupt                                               */
    RESERVED1 = IRQ_NUM_BASE + 24,             /*!< RESERVED  Interrupt                                               */
    GPADC_DMA_IRQn = IRQ_NUM_BASE + 25,        /*!< GPADC_DMA Interrupt                                               */
    EFUSE_IRQn = IRQ_NUM_BASE + 26,            /*!< Efuse Interrupt                                                   */
    SPI_IRQn = IRQ_NUM_BASE + 27,              /*!< SPI   Interrupt                                                   */
    RESERVED2 = IRQ_NUM_BASE + 28,             /*!< RESERVED Interrupt                                                */
    UART0_IRQn = IRQ_NUM_BASE + 29,            /*!< UART  Interrupt                                                   */
    UART1_IRQn = IRQ_NUM_BASE + 30,            /*!< UART1 Interrupt                                                   */
    RESERVED3 = IRQ_NUM_BASE + 31,             /*!< RESERVED Interrupt                                                */
    I2C_IRQn = IRQ_NUM_BASE + 32,              /*!< I2C   Interrupt                                                   */
    RESERVED4 = IRQ_NUM_BASE + 33,             /*!< RESERVED Interrupt                                                */
    PWM_IRQn = IRQ_NUM_BASE + 34,              /*!< PWM   Interrupt                                                   */
    RESERVED5 = IRQ_NUM_BASE + 35,             /*!< RESERVED Interrupt                                                */
    TIMER_CH0_IRQn = IRQ_NUM_BASE + 36,        /*!< Timer Channel 0 Interrupt                                         */
    TIMER_CH1_IRQn = IRQ_NUM_BASE + 37,        /*!< Timer Channel 1 Interrupt                                         */
    TIMER_WDT_IRQn = IRQ_NUM_BASE + 38,        /*!< Timer Watch Dog Interrupt                                         */
    KYS_IRQn = IRQ_NUM_BASE + 39,              /*!< KYS Interrupt                                                     */
    QDEC0_IRQn = IRQ_NUM_BASE + 40,            /*!< QDEC0 Interrupt                                                   */
    QDEC1_IRQn = IRQ_NUM_BASE + 41,            /*!< QDEC1 Interrupt                                                   */
    QDEC2_IRQn = IRQ_NUM_BASE + 42,            /*!< QDEC2 Interrupt                                                   */
    RESERVED6 = IRQ_NUM_BASE + 43,             /*!< RESERVED Interrupt                                                */
    GPIO_INT0_IRQn = IRQ_NUM_BASE + 44,        /*!< GPIO_INT0 Interrupt                                               */
    TOUCH_IRQn = IRQ_NUM_BASE + 45,            /*!< TOUCH Interrupt                                                   */
    RESERVED7 = IRQ_NUM_BASE + 46,             /*!< RESERVED Interrupt                                                */
    M154_REQ_ENH_ACK_IRQn = IRQ_NUM_BASE + 47, /*!< M154_REQ Interrupt                                                */
    M154_IRQn = IRQ_NUM_BASE + 48,             /*!< M154 Interrupt                                                    */
    M154_AES_IRQn = IRQ_NUM_BASE + 49,         /*!< M154_AES Interrupt                                                */
    PDS_WAKEUP_IRQn = IRQ_NUM_BASE + 50,       /*!< PDS Wakeup Interrupt                                              */
    HBN_OUT0_IRQn = IRQ_NUM_BASE + 51,         /*!< Hibernate out 0 Interrupt                                         */
    HBN_OUT1_IRQn = IRQ_NUM_BASE + 52,         /*!< Hibernate out 1 Interrupt                                         */
    BOR_IRQn = IRQ_NUM_BASE + 53,              /*!< BOR Interrupt                                                     */
    WIFI_IRQn = IRQ_NUM_BASE + 54,             /*!< WIFI To CPU Interrupt                                             */
    BZ_PHY_IRQn = IRQ_NUM_BASE + 55,           /*!< BZ_PHY Interrupt                                                  */
    BLE_IRQn = IRQ_NUM_BASE + 56,              /*!< BLE Interrupt                                                     */
    MAC_TXRX_TIMER_IRQn = IRQ_NUM_BASE + 57,   /*!< mac_int_tx_rx_timer Interrupt                                     */
    MAC_TXRX_MISC_IRQn = IRQ_NUM_BASE + 58,    /*!< mac_int_tx_rx_misc Interrupt                                      */
    MAC_RX_TRG_IRQn = IRQ_NUM_BASE + 59,       /*!< mac_int_rx_trigger Interrupt                                      */
    MAC_TX_TRG_IRQn = IRQ_NUM_BASE + 60,       /*!< mac_int_tx_trigger Interrupt                                      */
    MAC_GEN_IRQn = IRQ_NUM_BASE + 61,          /*!< mac_int_gen Interrupt                                             */
    MAC_PORT_TRG_IRQn = IRQ_NUM_BASE + 62,     /*!< mac_int_port_trigger Interrupt                                    */
    WIFI_IPC_PUBLIC_IRQn = IRQ_NUM_BASE + 63,  /*!< wifi IPC public Interrupt                                         */
    IRQn_LAST,
} IRQn_Type;

/**
 * @brief BL702 Memory Map Definitions
 */
#define BL702_FLASH_XIP_BASE        0x23000000
#define BL702_FLASH_XIP_END         (0x23000000 + 16 * 1024 * 1024)
#define BL702_FLASH_XIP_REMAP0_BASE 0x33000000
#define BL702_FLASH_XIP_REMAP0_END  (0x33000000 + 16 * 1024 * 1024)
#define BL702_FLASH_XIP_REMAP1_BASE 0x43000000
#define BL702_FLASH_XIP_REMAP1_END  (0x43000000 + 16 * 1024 * 1024)
#define BL702_FLASH_XIP_REMAP2_BASE 0x53000000
#define BL702_FLASH_XIP_REMAP2_END  (0x53000000 + 16 * 1024 * 1024)

#define BL702_PSRAM_XIP_BASE        0x24000000
#define BL702_PSRAM_XIP_END         (0x24000000 + 16 * 1024 * 1024)
#define BL702_PSRAM_XIP_REMAP0_BASE 0x34000000
#define BL702_PSRAM_XIP_REMAP0_END  (0x34000000 + 16 * 1024 * 1024)
#define BL702_PSRAM_XIP_REMAP1_BASE 0x44000000
#define BL702_PSRAM_XIP_REMAP1_END  (0x44000000 + 16 * 1024 * 1024)
#define BL702_PSRAM_XIP_REMAP2_BASE 0x54000000
#define BL702_PSRAM_XIP_REMAP2_END  (0x54000000 + 16 * 1024 * 1024)

#define BL702_WRAM_BASE        0x42020000
#define BL702_WRAM_END         (0x42020000 + 56 * 1024)
#define BL702_WRAM_REMAP0_BASE 0x22020000
#define BL702_WRAM_REMAP0_END  (0x22020000 + 56 * 1024)
#define BL702_WRAM_REMAP1_BASE 0x32020000
#define BL702_WRAM_REMAP1_END  (0x32020000 + 56 * 1024)
#define BL702_WRAM_REMAP2_BASE 0x52020000
#define BL702_WRAM_REMAP2_END  (0x52020000 + 56 * 1024)

#define BL702_TCM_BASE        0x22010000
#define BL702_TCM_END         (0x22010000 + (16 + 48) * 1024)
#define BL702_TCM_REMAP0_BASE 0x32010000
#define BL702_TCM_REMAP0_END  (0x32010000 + (16 + 48) * 1024)
#define BL702_TCM_REMAP1_BASE 0x42010000
#define BL702_TCM_REMAP1_END  (0x42010000 + (16 + 48) * 1024)
#define BL702_TCM_REMAP2_BASE 0x52010000
#define BL702_TCM_REMAP2_END  (0x52010000 + (16 + 48) * 1024)
/*@} end of group Memory_Map_Section */

/* BL702 peripherals base address */
#define GLB_BASE         ((uint32_t)0x40000000)
#define RF_BASE          ((uint32_t)0x40001000)
#define BZ_PHY_BASE      ((uint32_t)0x40001000)
#define BZ_PHY_AGC_BASE  ((uint32_t)0x40001000)
#define GPIP_BASE        ((uint32_t)0x40002000) /*!< AUX module base address */
#define SEC_DBG_BASE     ((uint32_t)0x40003000) /*!< Security Debug module base address */
#define SEC_ENG_BASE     ((uint32_t)0x40004000) /*!< Security Engine module base address */
#define TZC_SEC_BASE     ((uint32_t)0x40005000) /*!< Trustzone control security base address */
#define TZC_NSEC_BASE    ((uint32_t)0x40006000) /*!< Trustzone control none-security base address */
#define EF_DATA_BASE     ((uint32_t)0x40007000)
#define EF_CTRL_BASE     ((uint32_t)0x40007000)
#define CCI_BASE         ((uint32_t)0x40008000)
#define L1C_BASE         ((uint32_t)0x40009000) /*!< L1 cache config base address */
#define UART0_BASE       ((uint32_t)0x4000A000)
#define UART1_BASE       ((uint32_t)0x4000A100)
#define SPI_BASE         ((uint32_t)0x4000A200)
#define I2C_BASE         ((uint32_t)0x4000A300)
#define PWM_BASE         ((uint32_t)0x4000A400)
#define TIMER_BASE       ((uint32_t)0x4000A500)
#define IR_BASE          ((uint32_t)0x4000A600)
#define CKS_BASE         ((uint32_t)0x4000A700)
#define QDEC0_BASE       ((uint32_t)0x4000A800)
#define QDEC1_BASE       ((uint32_t)0x4000A840)
#define QDEC2_BASE       ((uint32_t)0x4000A880)
#define KYS_BASE         ((uint32_t)0x4000A900)
#define I2S_BASE         ((uint32_t)0x4000AA00)
#define CAM_BASE         ((uint32_t)0x4000AD00)
#define MJPEG_BASE       ((uint32_t)0x4000AE00)
#define SF_CTRL_BASE     ((uint32_t)0x4000B000)
#define SF_CTRL_BUF_BASE ((uint32_t)0x4000B700)
#define DMA_BASE         ((uint32_t)0x4000C000)
#define EMAC_BASE        ((uint32_t)0x4000D000)
#define USB_BASE         ((uint32_t)0x4000D800)
#define PDS_BASE         ((uint32_t)0x4000E000) /*!< Power down sleep module base address */
#define HBN_BASE         ((uint32_t)0x4000F000) /*!< Hibernate module base address */
#define AON_BASE         ((uint32_t)0x4000F000) /*!< Always on module base address */
#define MAC154_BASE      ((uint32_t)0x4C000000) /*!< MAC154 module base address */

#define HBN_RAM_BASE ((uint32_t)0x40010000)

typedef enum {
    BL_AHB_SLAVE1_GLB = 0x00,
    BL_AHB_SLAVE1_MIX = 0x01,
    BL_AHB_SLAVE1_GPIP = 0x02,
    BL_AHB_SLAVE1_SEC_DBG = 0x03,
    BL_AHB_SLAVE1_SEC = 0x04,
    BL_AHB_SLAVE1_TZ1 = 0x05,
    BL_AHB_SLAVE1_TZ2 = 0x06,
    BL_AHB_SLAVE1_EFUSE = 0x07,
    BL_AHB_SLAVE1_CCI = 0x08,
    BL_AHB_SLAVE1_L1C = 0x09,
    BL_AHB_SLAVE1_S1A_ALL = 0x0A,
    BL_AHB_SLAVE1_SFC = 0x0B,
    BL_AHB_SLAVE1_DMA = 0x0C,
    BL_AHB_SLAVE1_EMAC = 0x0D,
    BL_AHB_SLAVE1_PDS_HBN_AON_HBNRAM = 0x0E,
    BL_AHB_SLAVE1_RSVD0F = 0x0F,
    BL_AHB_SLAVE1_UART0 = 0x10,
    BL_AHB_SLAVE1_UART1 = 0x11,
    BL_AHB_SLAVE1_SPI = 0x12,
    BL_AHB_SLAVE1_I2C = 0x13,
    BL_AHB_SLAVE1_PWM = 0x14,
    BL_AHB_SLAVE1_TMR = 0x15,
    BL_AHB_SLAVE1_IRR = 0x16,
    BL_AHB_SLAVE1_CKS = 0x17,
    BL_AHB_SLAVE1_QDEC = 0x18,
    BL_AHB_SLAVE1_KYS = 0x19,
    BL_AHB_SLAVE1_I2S = 0x1A,
    BL_AHB_SLAVE1_RSVD1B = 0x1B,
    BL_AHB_SLAVE1_USB = 0x1C,
    BL_AHB_SLAVE1_CAM = 0x1D,
    BL_AHB_SLAVE1_MJPEG = 0x1E,
    BL_AHB_SLAVE1_MAX = 0x1F,
} BL_AHB_Slave1_Type;

typedef enum {
    BL_AHB_SEC_ENG_AES0 = 0,
    BL_AHB_SEC_ENG_AES1,
    BL_AHB_SEC_ENG_SHA0,
    BL_AHB_SEC_ENG_SHA1,
} BL_AHB_Sec_Eng_Type;

typedef enum {
    BL_AHB_DMA0_CH0 = 0,
    BL_AHB_DMA0_CH1,
    BL_AHB_DMA0_CH2,
    BL_AHB_DMA0_CH3,
    BL_AHB_DMA0_CH4,
    BL_AHB_DMA0_CH5,
    BL_AHB_DMA0_CH6,
    BL_AHB_DMA0_CH7,
} BL_AHB_DMA0_CHNL_Type;

typedef enum {
    BL_AHB_SLAVE2_WIFI_CFG = 0,
    BL_AHB_SLAVE2_MAX,
} BL_AHB_Slave2_Type;

typedef enum {
    BL_AHB_SLAVE3_BLE = 0,
    BL_AHB_SLAVE3_MAX,
} BL_AHB_Slave3_Type;

typedef enum {
    BL_CORE_MASTER_IBUS_CPU = 0,
    BL_CORE_MASTER_DBUS_CPU,
    BL_CORE_MASTER_BUS_S2F,
    BL_CORE_MASTER_MAX,
} BL_Core_Master_Type;

typedef enum {
    BL_CORE_SLAVE0_DTCM_CPU = 0,
    BL_CORE_SLAVE0_MAX,
} BL_Core_Slave0_Type;

typedef enum {
    BL_CORE_SLAVE1_XIP_CPU = 0,
    BL_CORE_SLAVE1_ITCM_CPU,
    BL_CORE_SLAVE1_ROM,
    BL_CORE_SLAVE1_MAX,
} BL_Core_Slave1_Type;

typedef enum {
    BL_CORE_SLAVE2_F2S = 0,
    BL_CORE_SLAVE2_MAX,
} BL_Core_Slave2_Type;

/**
  * @}
  */
#include <stdint.h>

/**
  * @}
  */

#endif
