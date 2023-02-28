#ifndef __BL808_H__
#define __BL808_H__

/** @addtogroup Configuration_section_for_RISCV
  * @{
  */

/**
  * @brief Configuration of the Processor and Core Peripherals
   */

#define CORE_ID_ADDRESS (0xF0000000)
#define CORE_ID_M0      (0xE9070000)
#define CORE_ID_D0      (0xDEAD5500)
#define CORE_ID_LP      (0xDEADE902)

#define CORE_M0_JTAG_TCK_PIN  (GLB_GPIO_PIN_27)
#define CORE_M0_JTAG_TMS_PIN  (GLB_GPIO_PIN_28)
#define CORE_M0_JTAG_TCK_FUNC (GPIO_FUN_M_CJTAG)
#define CORE_M0_JTAG_TMS_FUNC (GPIO_FUN_M_CJTAG)

#define IPC_SYNC_ADDR1 0x40000000
#define IPC_SYNC_ADDR2 0x40000004
#define IPC_SYNC_FLAG  0x12345678

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
#if (__riscv_xlen == 64)
#define IRQ_NUM_BASE 16 /* PLIC ===> MEXT_IRQn */
#else
#define IRQ_NUM_BASE 16
#endif
#endif
/**
 * @brief BL808 Interrupt Number Definition, according to the selected device
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
    SSOFT_IRQn = 1,           /*!< 1 RISCV supervisor software Interrupt                             */
    MSOFT_IRQn = 3,           /*!< 3 RISCV machine software Interrupt                                */
    STIME_IRQn = 5,           /*!< 5 RISCV supervisor time Interrupt                                 */
    MTIME_IRQn = 7,           /*!< 7 RISCV machine time Interrupt                                    */
    SEXT_IRQn = 9,            /*!< 9 RISCV S-mode external  Interrupt                                */
    MEXT_IRQn = 11,           /*!< 11 RISCV M-mode external  Interrupt                               */
    CLIC_SOFT_PEND_IRQn = 12, /*!< 12 RISCV CLIC software pending  Interrupt                         */
#if (__riscv_xlen == 64)
    HPM_OVF_IRQn = 17, /*!< 17 RISCV HPM counter overflow Interrupt                           */
#endif
#endif
#if defined(CPU_M0) || defined(CPU_LP)
#ifdef CPU_LP
#define CPU_LP_MAX_IRQ_NUM (IRQ_NUM_BASE + 32)
#endif
    /******  BL808 specific Interrupt Numbers **********************************************************************/
    BMX_MCU_BUS_ERR_IRQn = IRQ_NUM_BASE + 0,                    /*!< bmx mcu bus_err_int Interrupt                                     */
    BMX_MCU_TO_IRQn = IRQ_NUM_BASE + 1,                         /*!< bmx_timeout_int|mcu_timeout_int Interrupt                         */
    M0_RESERVED2_IRQn = IRQ_NUM_BASE + 2,                       /*!< reserved Interrupt                                                */
    IPC_M0_IRQn = IRQ_NUM_BASE + 3,                             /*!< ipc0_m0_irq Interrupt                                             */
    AUDIO_IRQn = IRQ_NUM_BASE + 4,                              /*!< Audio Interrupt                                                   */
    RF_TOP_INT0_IRQn = IRQ_NUM_BASE + 5,                        /*!< RF_TOP_INT0 Interrupt                                             */
    RF_TOP_INT1_IRQn = IRQ_NUM_BASE + 6,                        /*!< RF_TOP_INT1 Interrupt                                             */
    LZ4D_IRQn = IRQ_NUM_BASE + 7,                               /*!< LZ4 decompressor Interrupt                                        */
    GAUGE_ITF_IRQn = IRQ_NUM_BASE + 8,                          /*!< gauge_itf_int Interrupt                                           */
    SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC_IRQn = IRQ_NUM_BASE + 9,  /*!< sec_eng_id1 Interrupt                                             */
    SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn = IRQ_NUM_BASE + 10, /*!< sec_eng_id0 Interrupt                                             */
    SEC_ENG_ID1_CDET_IRQn = IRQ_NUM_BASE + 11,                  /*!< sec_eng_id1_cdet  Interrupt                                       */
    SEC_ENG_ID0_CDET_IRQn = IRQ_NUM_BASE + 12,                  /*!< sec_eng_id0_cdet Interrupt                                        */
    SF_CTRL_ID1_IRQn = IRQ_NUM_BASE + 13,                       /*!< sf_ctrl_id1 Interrupt                                             */
    SF_CTRL_ID0_IRQn = IRQ_NUM_BASE + 14,                       /*!< sf_ctrl_id0 Interrupt                                             */
    DMA0_ALL_IRQn = IRQ_NUM_BASE + 15,                          /*!< DMA0_INTR_ALL Interrupt                                           */
    DMA1_ALL_IRQn = IRQ_NUM_BASE + 16,                          /*!< DMA1_INTR_ALL Interrupt                                           */
    SDH_IRQn = IRQ_NUM_BASE + 17,                               /*!< sdh Interrupt                                                     */
    MM_ALL_IRQn = IRQ_NUM_BASE + 18,                            /*!< MM System All Interrupt                                           */
    IRTX_IRQn = IRQ_NUM_BASE + 19,                              /*!< IR TX Interrupt                                                   */
    IRRX_IRQn = IRQ_NUM_BASE + 20,                              /*!< IR RX Interrupt                                                   */
    USB_IRQn = IRQ_NUM_BASE + 21,                               /*!< USB  Interrupt                                                    */
    AUPDM_TOUCH_IRQn = IRQ_NUM_BASE + 22,                       /*!< aupdm_touch_int Interrupt                                         */
    M0_RESERVED23_IRQn = IRQ_NUM_BASE + 23,                     /*!< reserved Interrupt                                                */
    EMAC_IRQn = IRQ_NUM_BASE + 24,                              /*!< EMAC  Interrupt                                                   */
    GPADC_DMA_IRQn = IRQ_NUM_BASE + 25,                         /*!< GPADC_DMA Interrupt                                               */
    EFUSE_IRQn = IRQ_NUM_BASE + 26,                             /*!< Efuse Interrupt                                                   */
    SPI0_IRQn = IRQ_NUM_BASE + 27,                              /*!< SPI0  Interrupt                                                   */
    UART0_IRQn = IRQ_NUM_BASE + 28,                             /*!< UART0 Interrupt                                                   */
    UART1_IRQn = IRQ_NUM_BASE + 29,                             /*!< UART1 Interrupt                                                   */
    UART2_IRQn = IRQ_NUM_BASE + 30,                             /*!< UART2 Interrupt                                                   */
    GPIO_DMA_IRQn = IRQ_NUM_BASE + 31,                          /*!< GPIO DMA Interrupt                                                */
    I2C0_IRQn = IRQ_NUM_BASE + 32,                              /*!< I2C0  Interrupt                                                   */
    PWM_IRQn = IRQ_NUM_BASE + 33,                               /*!< PWM Interrupt                                                     */
    IPC_RSVD_IRQn = IRQ_NUM_BASE + 34,                          /*!< ipc reserved Interrupt                                            */
    IPC_LP_IRQn = IRQ_NUM_BASE + 35,                            /*!< ipc lp_irq Interrupt                                              */
    TIMER0_CH0_IRQn = IRQ_NUM_BASE + 36,                        /*!< Timer0 Channel 0 Interrupt                                        */
    TIMER0_CH1_IRQn = IRQ_NUM_BASE + 37,                        /*!< Timer0 Channel 1 Interrupt                                        */
    TIMER0_WDT_IRQn = IRQ_NUM_BASE + 38,                        /*!< Timer0 Watch Dog Interrupt                                        */
    I2C1_IRQn = IRQ_NUM_BASE + 39,                              /*!< I2C1  Interrupt                                                   */
    I2S_IRQn = IRQ_NUM_BASE + 40,                               /*!< I2S  Interrupt                                                    */
    ANA_OCP_OUT_TO_CPU_0_IRQn = IRQ_NUM_BASE + 41,              /*!< ana_ocp_out_to_cpu_irq0 Interrupt                                 */
    ANA_OCP_OUT_TO_CPU_1_IRQn = IRQ_NUM_BASE + 42,              /*!< ana_ocp_out_to_cpu_irq1 Interrupt                                 */
    ANA_OCP_OUT_TO_CPU_2_IRQn = IRQ_NUM_BASE + 43,              /*!< ana_ocp_out_to_cpu_irq2 Interrupt                                 */
    GPIO_INT0_IRQn = IRQ_NUM_BASE + 44,                         /*!< GPIO Interrupt                                                    */
    DM_IRQn = IRQ_NUM_BASE + 45,                                /*!< DM Interrupt                                                      */
    BT_IRQn = IRQ_NUM_BASE + 46,                                /*!< BT Interrupt                                                      */
    M154_REQ_ACK_IRQn = IRQ_NUM_BASE + 47,                      /*!< M154 req enh ack Interrupt                                        */
    M154_INT_IRQn = IRQ_NUM_BASE + 48,                          /*!< M154 Interrupt                                                    */
    M154_AES_IRQn = IRQ_NUM_BASE + 49,                          /*!< m154 aes Interrupt                                                */
    PDS_WAKEUP_IRQn = IRQ_NUM_BASE + 50,                        /*!< PDS Wakeup Interrupt                                              */
    HBN_OUT0_IRQn = IRQ_NUM_BASE + 51,                          /*!< Hibernate out 0 Interrupt                                         */
    HBN_OUT1_IRQn = IRQ_NUM_BASE + 52,                          /*!< Hibernate out 1 Interrupt                                         */
    BOR_IRQn = IRQ_NUM_BASE + 53,                               /*!< BOR Interrupt                                                     */
    WIFI_IRQn = IRQ_NUM_BASE + 54,                              /*!< WIFI To CPU Interrupt                                             */
    BZ_PHY_INT_IRQn = IRQ_NUM_BASE + 55,                        /*!< BZ phy Interrupt                                                  */
    BLE_IRQn = IRQ_NUM_BASE + 56,                               /*!< BLE Interrupt                                                     */
    MAC_TXRX_TIMER_IRQn = IRQ_NUM_BASE + 57,                    /*!< MAC Tx Rx Timer Interrupt                                         */
    MAC_TXRX_MISC_IRQn = IRQ_NUM_BASE + 58,                     /*!< MAC Tx Rx Misc Interrupt                                          */
    MAC_RX_TRG_IRQn = IRQ_NUM_BASE + 59,                        /*!< MAC Rx Trigger Interrupt                                          */
    MAC_TX_TRG_IRQn = IRQ_NUM_BASE + 60,                        /*!< MAC tx Trigger Interrupt                                          */
    MAC_GEN_IRQn = IRQ_NUM_BASE + 61,                           /*!< MAC Gen Interrupt                                                 */
    MAC_PORT_TRG_IRQn = IRQ_NUM_BASE + 62,                      /*!< MAC Prot Trigger Interrupt                                        */
    WIFI_IPC_PUBLIC_IRQn = IRQ_NUM_BASE + 63,                   /*!< WIFI Ipc Interrupt                                                */
    IRQn_LAST,
#endif

#if defined(CPU_D0)
    /******  BL808 specific Interrupt Numbers **********************************************************************/
    BMX_DSP_BUS_ERR_IRQn = IRQ_NUM_BASE + 0,  /*!< BMX DSP BUS Error Interrupt                                       */
    DSP2_AWB2_IRQn = IRQ_NUM_BASE + 1,         /*!< DSP2 AWB3 Interrupt                                                */
    D0_RESERVED2_IRQn = IRQ_NUM_BASE + 2,     /*!< IPC reserved Interrupt                                            */
    D0_RESERVED3_IRQn = IRQ_NUM_BASE + 3,     /*!< UART4 reserved Interrupt                                          */
    UART3_IRQn = IRQ_NUM_BASE + 4,            /*!< UART3 Interrupt                                                   */
    I2C2_IRQn = IRQ_NUM_BASE + 5,             /*!< I2C2 Interrupt                                                    */
    I2C3_IRQn = IRQ_NUM_BASE + 6,             /*!< I2C3 Interrupt                                                    */
    SPI1_IRQn = IRQ_NUM_BASE + 7,             /*!< SPI1 Interrupt                                                    */
    DSP2_AE_IRQn = IRQ_NUM_BASE + 8,           /*!< DSP2 AE Interrupt                                                  */
    DSP2_AWB0_IRQn = IRQ_NUM_BASE + 9,         /*!< DSP2 AWB1 Interrupt                                                */
    SEOF_INT0_IRQn = IRQ_NUM_BASE + 10,       /*!< SEOF INT0 Interrupt                                               */
    SEOF_INT1_IRQn = IRQ_NUM_BASE + 11,       /*!< SEOF INT1 Interrupt                                               */
    SEOF_INT2_IRQn = IRQ_NUM_BASE + 12,       /*!< SEOF INT2 Interrupt                                               */
    DVP2BUS_INT0_IRQn = IRQ_NUM_BASE + 13,    /*!< DVP2BUS INT0 Interrupt                                            */
    DVP2BUS_INT1_IRQn = IRQ_NUM_BASE + 14,    /*!< DVP2BUS INT1 Interrupt                                            */
    DVP2BUS_INT2_IRQn = IRQ_NUM_BASE + 15,    /*!< DVP2BUS INT2 Interrupt                                            */
    DVP2BUS_INT3_IRQn = IRQ_NUM_BASE + 16,    /*!< DVP2BUS INT3 Interrupt                                            */
    H264_BS_IRQn = IRQ_NUM_BASE + 17,         /*!< H264 BS Interrupt                                                 */
    H264_FRAME_IRQn = IRQ_NUM_BASE + 18,      /*!< H264 Frame Interrupt                                              */
    H264_SEQ_DONE_IRQn = IRQ_NUM_BASE + 19,   /*!< H264 SEQ Done Interrupt                                           */
    MJPEG_IRQn = IRQ_NUM_BASE + 20,           /*!< MJPEG Interrupt                                                   */
    H264_S_BS_IRQn = IRQ_NUM_BASE + 21,       /*!< H264 S BS Interrupt                                               */
    H264_S_FRAME_IRQn = IRQ_NUM_BASE + 22,    /*!< H264 S Frame Interrupt                                            */
    H264_S_SEQ_DONE_IRQn = IRQ_NUM_BASE + 23, /*!< H264 S SEQ Done Interrupt                                         */
    DMA2_INT0_IRQn = IRQ_NUM_BASE + 24,       /*!< DMA2 INT0 Interrupt                                               */
    DMA2_INT1_IRQn = IRQ_NUM_BASE + 25,       /*!< DMA2 INT1 Interrupt                                               */
    DMA2_INT2_IRQn = IRQ_NUM_BASE + 26,       /*!< DMA2 INT2 Interrupt                                               */
    DMA2_INT3_IRQn = IRQ_NUM_BASE + 27,       /*!< DMA2 INT3 Interrupt                                               */
    DMA2_INT4_IRQn = IRQ_NUM_BASE + 28,       /*!< DMA2 INT4 Interrupt                                               */
    DMA2_INT5_IRQn = IRQ_NUM_BASE + 29,       /*!< DMA2 INT5 Interrupt                                               */
    DMA2_INT6_IRQn = IRQ_NUM_BASE + 30,       /*!< DMA2 INT6 Interrupt                                               */
    DMA2_INT7_IRQn = IRQ_NUM_BASE + 31,       /*!< DMA2 INT7 Interrupt                                               */
    SDH_MMC1_IRQn = IRQ_NUM_BASE + 32,        /*!< SDH MMC1 Interrupt                                                */
    SDH_MMC3_IRQn = IRQ_NUM_BASE + 33,        /*!< SDH MMC3 Interrupt                                                */
    SDH2PMU_WAKEUP1_IRQn = IRQ_NUM_BASE + 34, /*!< SDH2PMU Wakeup1 Interrupt                                         */
    SDH2PMU_WAKEUP3_IRQn = IRQ_NUM_BASE + 35, /*!< SDH2PMU Wakeup3 Interrupt                                         */
    EMAC2_IRQn = IRQ_NUM_BASE + 36,           /*!< EMAC2 Interrupt                                                   */
    MIPI_CSI_IRQn = IRQ_NUM_BASE + 37,        /*!< MIPI CSI Interrupt                                                */
    IPC_D0_IRQn = IRQ_NUM_BASE + 38,          /*!< IPC D0 Interrupt                                                  */
    APU_IRQn = IRQ_NUM_BASE + 39,             /*!< APU Interrupt                                                     */
    MJDEC_IRQn = IRQ_NUM_BASE + 40,           /*!< MJDEC Interrupt                                                   */
    DVP2BUS_INT4_IRQn = IRQ_NUM_BASE + 41,    /*!< DVP2BUS INT4 Interrupt                                            */
    DVP2BUS_INT5_IRQn = IRQ_NUM_BASE + 42,    /*!< DVP2BUS INT5 Interrupt                                            */
    DVP2BUS_INT6_IRQn = IRQ_NUM_BASE + 43,    /*!< DVP2BUS INT6 Interrupt                                            */
    DVP2BUS_INT7_IRQn = IRQ_NUM_BASE + 44,    /*!< DVP2BUS INT7 Interrupt                                            */
    DMA2D_INT0_IRQn = IRQ_NUM_BASE + 45,      /*!< DMA2D INT0 Interrupt                                              */
    DMA2D_INT1_IRQn = IRQ_NUM_BASE + 46,      /*!< DMA2D INT1 Interrupt                                              */
    DISPLAY_IRQn = IRQ_NUM_BASE + 47,         /*!< Display Interrupt                                                 */
    PWM_IRQn = IRQ_NUM_BASE + 48,             /*!< PWM1 Interrupt                                                    */
    SEOF_INT3_IRQn = IRQ_NUM_BASE + 49,       /*!< SEOF INT0 Interrupt                                               */
    RESERVED1_IRQn = IRQ_NUM_BASE + 50,       /*!< Reserved Interrupt                                                */
    RESERVED2_IRQn = IRQ_NUM_BASE + 51,       /*!< Reserved Interrupt                                                */
    OSD_IRQn = IRQ_NUM_BASE + 52,             /*!< OSD Interrupt                                                     */
    DBI_IRQn = IRQ_NUM_BASE + 53,             /*!< DBI Interrupt                                                     */
    DSP2_WDR_IRQn = IRQ_NUM_BASE + 54,         /*!< DSP2 WDR Interrupt                                                 */
    OSDA_BUS_DRAIN_IRQn = IRQ_NUM_BASE + 55,  /*!< OSDA Bus Drain Interrupt                                          */
    OSDB_BUS_DRAIN_IRQn = IRQ_NUM_BASE + 56,  /*!< OSDB Bus Drain Interrupt                                          */
    OSD_PB_IRQn = IRQ_NUM_BASE + 57,          /*!< OSD PB Interrupt                                                  */
    DSP2_AWB1_IRQn = IRQ_NUM_BASE + 58,        /*!< DSP2 AWB2 Interrupt                                                */
    MIPI_DSI_IRQn = IRQ_NUM_BASE + 59,        /*!< MIPI DSI Interrupt                                                */
    DSP2_AE_HIST_IRQn = IRQ_NUM_BASE + 60,     /*!< DSP2 AE HIST Interrupt                                             */
    TIMER1_CH0_IRQn = IRQ_NUM_BASE + 61,      /*!< Timer1 Channel 0 Interrupt                                        */
    TIMER1_CH1_IRQn = IRQ_NUM_BASE + 62,      /*!< Timer1 Channel 1 Interrupt                                        */
    TIMER1_WDT_IRQn = IRQ_NUM_BASE + 63,      /*!< Timer1 Watch Dog Interrupt                                        */
    AUDIO_IRQn = IRQ_NUM_BASE + 64,           /*!< Audio Interrupt                                                   */
    WL_ALL_IRQn = IRQ_NUM_BASE + 65,          /*!< WL System All Interrupt                                           */
    PDS_IRQn = IRQ_NUM_BASE + 66,             /*!< PDS Interrupt                                                     */
    IRQn_LAST,
#endif
} IRQn_Type;

/* Add following macro definition in order to pass the compilation */
#if defined(CPU_M0) || defined(CPU_LP)
#define BMX_DSP_BUS_ERR_IRQn (IRQn_LAST)
#define DSP2_AWB2_IRQn        (IRQn_LAST)
#define D0_RESERVED2_IRQn    (IRQn_LAST)
#define UART3_IRQn           (IRQn_LAST)
#define I2C2_IRQn            (IRQn_LAST)
#define I2C3_IRQn            (IRQn_LAST)
#define SPI1_IRQn            (IRQn_LAST)
#define DSP2_AE_IRQn          (IRQn_LAST)
#define DSP2_AWB0_IRQn        (IRQn_LAST)
#define SEOF_INT0_IRQn       (IRQn_LAST)
#define SEOF_INT1_IRQn       (IRQn_LAST)
#define SEOF_INT2_IRQn       (IRQn_LAST)
#define DVP2BUS_INT0_IRQn    (IRQn_LAST)
#define DVP2BUS_INT1_IRQn    (IRQn_LAST)
#define DVP2BUS_INT2_IRQn    (IRQn_LAST)
#define DVP2BUS_INT3_IRQn    (IRQn_LAST)
#define H264_BS_IRQn         (IRQn_LAST)
#define H264_FRAME_IRQn      (IRQn_LAST)
#define H264_SEQ_DONE_IRQn   (IRQn_LAST)
#define MJPEG_IRQn           (IRQn_LAST)
#define H264_S_BS_IRQn       (IRQn_LAST)
#define H264_S_FRAME_IRQn    (IRQn_LAST)
#define H264_S_SEQ_DONE_IRQn (IRQn_LAST)
#define DMA2_INT0_IRQn       (IRQn_LAST)
#define DMA2_INT1_IRQn       (IRQn_LAST)
#define DMA2_INT2_IRQn       (IRQn_LAST)
#define DMA2_INT3_IRQn       (IRQn_LAST)
#define DMA2_INT4_IRQn       (IRQn_LAST)
#define DMA2_INT5_IRQn       (IRQn_LAST)
#define DMA2_INT6_IRQn       (IRQn_LAST)
#define DMA2_INT7_IRQn       (IRQn_LAST)
#define SDH_MMC1_IRQn        (IRQn_LAST)
#define SDH_MMC3_IRQn        (IRQn_LAST)
#define SDH2PMU_WAKEUP1_IRQn (IRQn_LAST)
#define SDH2PMU_WAKEUP3_IRQn (IRQn_LAST)
#define EMAC2_IRQn           (IRQn_LAST)
#define MIPI_CSI_IRQn        (IRQn_LAST)
#define IPC_D0_IRQn          (IRQn_LAST)
#define APU_IRQn             (IRQn_LAST)
#define MJDEC_IRQn           (IRQn_LAST)
#define DVP2BUS_INT4_IRQn    (IRQn_LAST)
#define DVP2BUS_INT5_IRQn    (IRQn_LAST)
#define DVP2BUS_INT6_IRQn    (IRQn_LAST)
#define DVP2BUS_INT7_IRQn    (IRQn_LAST)
#define DMA2D_INT0_IRQn      (IRQn_LAST)
#define DMA2D_INT1_IRQn      (IRQn_LAST)
#define DISPLAY_IRQn         (IRQn_LAST)
#define SEOF_INT3_IRQn       (IRQn_LAST)
#define RESERVED1_IRQn       (IRQn_LAST)
#define RESERVED2_IRQn       (IRQn_LAST)
#define OSD_IRQn             (IRQn_LAST)
#define DBI_IRQn             (IRQn_LAST)
#define DSP2_WDR_IRQn         (IRQn_LAST)
#define OSDA_BUS_DRAIN_IRQn  (IRQn_LAST)
#define OSDB_BUS_DRAIN_IRQn  (IRQn_LAST)
#define OSD_PB_IRQn          (IRQn_LAST)
#define DSP2_AWB1_IRQn        (IRQn_LAST)
#define MIPI_DSI_IRQn        (IRQn_LAST)
#define DSP2_AE_HIST_IRQn     (IRQn_LAST)
#define TIMER1_CH0_IRQn      (IRQn_LAST)
#define TIMER1_CH1_IRQn      (IRQn_LAST)
#define TIMER1_WDT_IRQn      (IRQn_LAST)
#define WL_ALL_IRQn          (IRQn_LAST)
#define PDS_IRQn             (IRQn_LAST)
#endif

#if defined(CPU_D0)
#define BMX_MCU_BUS_ERR_IRQn                   (IRQn_LAST)
#define BMX_MCU_TO_IRQn                        (IRQn_LAST)
#define M0_RESERVED2_IRQn                      (IRQn_LAST)
#define IPC_M0_IRQn                            (IRQn_LAST)
#define RF_TOP_INT0_IRQn                       (IRQn_LAST)
#define RF_TOP_INT1_IRQn                       (IRQn_LAST)
#define LZ4D_IRQn                              (IRQn_LAST)
#define GAUGE_ITF_IRQn                         (IRQn_LAST)
#define SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC_IRQn (IRQn_LAST)
#define SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn (IRQn_LAST)
#define SEC_ENG_ID1_CDET_IRQn                  (IRQn_LAST)
#define SEC_ENG_ID0_CDET_IRQn                  (IRQn_LAST)
#define SF_CTRL_ID1_IRQn                       (IRQn_LAST)
#define SF_CTRL_ID0_IRQn                       (IRQn_LAST)
#define DMA0_ALL_IRQn                          (IRQn_LAST)
#define DMA1_ALL_IRQn                          (IRQn_LAST)
#define SDH_IRQn                               (IRQn_LAST)
#define MM_ALL_IRQn                            (IRQn_LAST)
#define IRTX_IRQn                              (IRQn_LAST)
#define IRRX_IRQn                              (IRQn_LAST)
#define USB_IRQn                               (IRQn_LAST)
#define AUPDM_TOUCH_IRQn                       (IRQn_LAST)
#define M0_RESERVED23_IRQn                     (IRQn_LAST)
#define EMAC_IRQn                              (IRQn_LAST)
#define GPADC_DMA_IRQn                         (IRQn_LAST)
#define EFUSE_IRQn                             (IRQn_LAST)
#define SPI0_IRQn                              (IRQn_LAST)
#define UART0_IRQn                             (IRQn_LAST)
#define UART1_IRQn                             (IRQn_LAST)
#define UART2_IRQn                             (IRQn_LAST)
#define GPIO_DMA_IRQn                          (IRQn_LAST)
#define I2C0_IRQn                              (IRQn_LAST)
#define IPC_RSVD_IRQn                          (IRQn_LAST)
#define IPC_LP_IRQn                            (IRQn_LAST)
#define TIMER0_CH0_IRQn                        (IRQn_LAST)
#define TIMER0_CH1_IRQn                        (IRQn_LAST)
#define TIMER0_WDT_IRQn                        (IRQn_LAST)
#define I2C1_IRQn                              (IRQn_LAST)
#define I2S_IRQn                               (IRQn_LAST)
#define ANA_OCP_OUT_TO_CPU_0_IRQn              (IRQn_LAST)
#define ANA_OCP_OUT_TO_CPU_1_IRQn              (IRQn_LAST)
#define ANA_OCP_OUT_TO_CPU_2_IRQn              (IRQn_LAST)
#define GPIO_INT0_IRQn                         (IRQn_LAST)
#define DM_IRQn                                (IRQn_LAST)
#define BT_IRQn                                (IRQn_LAST)
#define M154_REQ_ACK_IRQn                      (IRQn_LAST)
#define M154_INT_IRQn                          (IRQn_LAST)
#define M154_AES_IRQn                          (IRQn_LAST)
#define PDS_WAKEUP_IRQn                        (IRQn_LAST)
#define HBN_OUT0_IRQn                          (IRQn_LAST)
#define HBN_OUT1_IRQn                          (IRQn_LAST)
#define BOR_IRQn                               (IRQn_LAST)
#define WIFI_IRQn                              (IRQn_LAST)
#define BZ_PHY_INT_IRQn                        (IRQn_LAST)
#define BLE_IRQn                               (IRQn_LAST)
#define MAC_TXRX_TIMER_IRQn                    (IRQn_LAST)
#define MAC_TXRX_MISC_IRQn                     (IRQn_LAST)
#define MAC_RX_TRG_IRQn                        (IRQn_LAST)
#define MAC_TX_TRG_IRQn                        (IRQn_LAST)
#define MAC_GEN_IRQn                           (IRQn_LAST)
#define MAC_PORT_TRG_IRQn                      (IRQn_LAST)
#define WIFI_IPC_PUBLIC_IRQn                   (IRQn_LAST)
#endif

/**
 * @brief BL808 Memory Map Definitions
 */
#define BL808_OCRAM_BASE                (0x22020000)
#define BL808_OCRAM_END                 (0x22020000 + 64 * 1024)
#define BL808_OCRAM_CACHEABLE_BASE      (0x62020000)
#define BL808_OCRAM_CACHEABLE_END       (0x62020000 + 64 * 1024)

#define BL808_WRAM_BASE                 (0x22030000)
#define BL808_WRAM_END                  (0x22030000 + 160 * 1024)
#define BL808_WRAM_CACHEABLE_BASE       (0x62030000)
#define BL808_WRAM_CACHEABLE_END        (0x62030000 + 160 * 1024)

#define BL808_MCU_ALLRAM_BASE           (0x22020000)
#define BL808_MCU_ALLRAM_END            (0x22020000 + 64 * 1024 + 160 * 1024)
#define BL808_MCU_ALLRAM_CACHEABLE_BASE (0x62020000)
#define BL808_MCU_ALLRAM_CACHEABLE_END  (0x62020000 + 64 * 1024 + 160 * 1024)

#define BL808_DRAM_BASE                 (0x3EF80000)
#define BL808_DRAM_END                  (0x3EF80000 + 512 * 1024)
#define BL808_DRAM_CACHEABLE_BASE       (0x7EF80000)
#define BL808_DRAM_CACHEABLE_END        (0x7EF80000 + 512 * 1024)

#define BL808_VRAM_BASE                 (0x3F000000)
#define BL808_VRAM_END                  (0x3F000000 + 32 * 1024)
#define BL808_VRAM_CACHEABLE_BASE       (0x7F000000)
#define BL808_VRAM_CACHEABLE_END        (0x7F000000 + 32 * 1024)

#define BL808_MM_ALLRAM_BASE            (0x3EF80000)
#define BL808_MM_ALLRAM_END             (0x3EF80000 + 512 * 1024 + 32 * 1024)
#define BL808_MM_ALLRAM_CACHEABLE_BASE  (0x7EF80000)
#define BL808_MM_ALLRAM_CACHEABLE_END   (0x7EF80000 + 512 * 1024 + 32 * 1024)

#define BL808_FLASH_XIP_BASE            (0x58000000)
#define BL808_FLASH_XIP_END             (0x58000000 + 64 * 1024 * 1024)
#define BL808_FLASH2_XIP_BASE           (0x5C000000)
#define BL808_FLASH2_XIP_END            (0x5C000000 + 64 * 1024 * 1024)
#define BL808_FLASH_XIP_REMAP0_BASE     (0xD8000000)
#define BL808_FLASH_XIP_REMAP0_END      (0xD8000000 + 64 * 1024 * 1024)
#define BL808_FLASH2_XIP_REMAP0_BASE    (0xDC000000)
#define BL808_FLASH2_XIP_REMAP0_END     (0xDC000000 + 64 * 1024 * 1024)

#define BL808_MM_WHOLERAM_BASE              (0x3EF80000)
#define BL808_MM_WHOLERAM_END               (0x3EF80000 + 512 * 1024 + 96 * 1024)
#define BL808_MM_WHOLERAM_CACHEABLE_BASE    (0x7EF80000)
#define BL808_MM_WHOLERAM_CACHEABLE_END     (0x7EF80000 + 512 * 1024 + 96 * 1024)

/*@} end of group Memory_Map_Section */

/* BL808 peripherals base address */
/* WLSYS */
#define GLB_BASE         ((uint32_t)0x20000000)
#define MIX_BASE         ((uint32_t)0x20001000)
#define GPIP_BASE        ((uint32_t)0x20002000)
#define PHY_BASE         ((uint32_t)0x20002800)
#define AGC_BASE         ((uint32_t)0x20002c00)
#define SEC_DBG_BASE     ((uint32_t)0x20003000)
#define SEC_ENG_BASE     ((uint32_t)0x20004000)
#define TZ1_BASE         ((uint32_t)0x20005000)
#define TZC_SEC_BASE     ((uint32_t)0x20005000)
#define TZ2_BASE         ((uint32_t)0x20006000)
#define TZC_NSEC_BASE    ((uint32_t)0x20006000)
#define EFUSE_BASE       ((uint32_t)0x20056000)
#define EF_DATA_BASE     ((uint32_t)0x20056000)
#define EF_CTRL_BASE     ((uint32_t)0x20056000)
#define CCI_BASE         ((uint32_t)0x20008000)
#define MCU_MISC_BASE    ((uint32_t)0x20009000)
#define L1C_BASE         ((uint32_t)0x20009000)
#define UART0_BASE       ((uint32_t)0x2000a000)
#define UART1_BASE       ((uint32_t)0x2000a100)
#define SPI0_BASE        ((uint32_t)0x2000a200)
#define I2C0_BASE        ((uint32_t)0x2000a300)
#define PWM_BASE         ((uint32_t)0x2000a400)
#define TIMER0_BASE      ((uint32_t)0x2000a500)
#define IR_BASE          ((uint32_t)0x2000a600)
#define CKS_BASE         ((uint32_t)0x2000a700)
#define IPC0_BASE        ((uint32_t)0x2000a800)
#define IPC1_BASE        ((uint32_t)0x2000a840)
#define I2C1_BASE        ((uint32_t)0x2000a900)
#define UART2_BASE       ((uint32_t)0x2000aa00)
#define ISO11898_BASE    ((uint32_t)0x2000aa00)
#define I2S_BASE         ((uint32_t)0x2000ab00)
#define PDM0_BASE        ((uint32_t)0x2000a000)
#define LZ4D_BASE        ((uint32_t)0x2000ad00)
#define QSPI_BASE        ((uint32_t)0x2000b000)
#define SF_CTRL_BASE     ((uint32_t)0x2000b000)
#define SF_CTRL_BUF_BASE ((uint32_t)0x2000b600)
#define DMA0_BASE        ((uint32_t)0x2000c000)
#define PDS_BASE         ((uint32_t)0x2000e000)
#define HBN_BASE         ((uint32_t)0x2000f000)
#define AON_BASE         ((uint32_t)0x2000f000)
#define EMI_MISC_BASE    ((uint32_t)0x20050000)
#define PSRAM_CTRL_BASE  ((uint32_t)0x20052000)
#define USB_BASE         ((uint32_t)0x20072000)
#define AUDIO_BASE       ((uint32_t)0x20055000)
#define SDH_BASE         ((uint32_t)0x20060000)
#define EMAC_BASE        ((uint32_t)0x20070000)
#define DMA1_BASE        ((uint32_t)0x20071000)

/* MMSYS */
#define MM_MISC_BASE     ((uint32_t)0x30000000)
#define DMA2_BASE        ((uint32_t)0x30001000)
#define UART3_BASE       ((uint32_t)0x30002000)
#define I2C2_BASE        ((uint32_t)0x30003000)
#define I2C3_BASE        ((uint32_t)0x30004000)
#define IPC2_BASE        ((uint32_t)0x30005000)
#define DMA2D_BASE       ((uint32_t)0x30006000)
#define CLKRST_CTRL_BASE ((uint32_t)0x30007000)
#define MM_GLB_BASE      ((uint32_t)0x30007000)
#define SPI1_BASE        ((uint32_t)0x30008000)
#define TIMER1_BASE      ((uint32_t)0x30009000)
#define PSRAM_UHS_BASE   ((uint32_t)0x3000f000)

/* DSP2_SUBSYS */
#define DSP2_MISC_BASE        ((uint32_t)0x30010000)
#define DSP2_BASE             ((uint32_t)0x30011000)
#define DVP0_BASE            ((uint32_t)0x30012000)
#define DVP1_BASE            ((uint32_t)0x30012100)
#define DVP2_BASE            ((uint32_t)0x30012200)
#define DVP3_BASE            ((uint32_t)0x30012300)
#define DVP4_BASE            ((uint32_t)0x30012400)
#define DVP5_BASE            ((uint32_t)0x30012500)
#define DVP6_BASE            ((uint32_t)0x30012600)
#define DVP7_BASE            ((uint32_t)0x30012700)
#define DVP_TSRC0_BASE       ((uint32_t)0x30012800)
#define DVP_TSRC1_BASE       ((uint32_t)0x30012900)
#define AXI_CTRL_NR3D_BASE   ((uint32_t)0x30012a00)
#define OSD_PROBE_BASE       ((uint32_t)0x30012b00)
#define OSD_A_BASE           ((uint32_t)0x30013000)
#define OSD_B_BASE           ((uint32_t)0x30014000)
#define OSD_DP_BASE          ((uint32_t)0x30015000)
#define OSD_BLEND0_OFFSET    (0x000)
#define OSD_BLEND1_OFFSET    (0x100)
#define OSD_BLEND2_OFFSET    (0x200)
#define OSD_BLEND3_OFFSET    (0x300)
#define OSD_DRAW_LOW_OFFSET  (0x400)
#define OSD_DRAW_HIGH_OFFSET (0x504)
#define MIPI_BASE            ((uint32_t)0x3001a000)
#define DBI_BASE             ((uint32_t)0x3001b000)
#define DSI_BASE             ((uint32_t)0x3001a100)

/* CODEC_SUBSYS */
#define CODEC_MISC_BASE ((uint32_t)0x30020000)
#define MJPEG_BASE      ((uint32_t)0x30021000)
#define VIDEO_BASE      ((uint32_t)0x30022000)
#define MJPEG_DEC_BASE  ((uint32_t)0x30023000)
#define BL_CNN_BASE     ((uint32_t)0x30024000)

#define HBN_RAM_BASE ((uint32_t)0x20010000)

#define RF_BASE ((uint32_t)0x20001000)

typedef enum {
    BL_AHB_MASTER_CPU = 0x00,
    BL_AHB_MASTER_SDU = 0x01,
    BL_AHB_MASTER_SEC = 0x02,
    BL_AHB_MASTER_DMA = 0x03,
    BL_AHB_MASTER_CCI = 0x04,
    BL_AHB_MASTER_WIFI_PLATFORM = 0x05,
    BL_AHB_MASTER_WIFI_MAC_PHY = 0x06,
    BL_AHB_MASTER_WIFI_PHY = 0x07,
    BL_AHB_MASTER_MAX = 0x08,
} BL_AHB_Master_Type;

typedef enum {
    BL_AHB_SLAVE1_GLB = 0x00,    //cgen rsvd
    BL_AHB_SLAVE1_RF_TOP = 0x01, //swrst mix
    BL_AHB_SLAVE1_GPIP = 0x02,
    BL_AHB_SLAVE1_SEC_DBG = 0x03,
    BL_AHB_SLAVE1_SEC_ENG = 0x04,
    BL_AHB_SLAVE1_TZ = 0x05,    //swrst tz1,cgen tz1+tz2
    BL_AHB_SLAVE1_RSVD6 = 0x06, //swrst tz2,
    BL_AHB_SLAVE1_EF_CTRL = 0x07,
    BL_AHB_SLAVE1_CCI = 0x08, //cgen rsvd
    BL_AHB_SLAVE1_L1C = 0x09, //cgen rsvd
    BL_AHB_SLAVE1_RSVD10 = 0x0A,
    BL_AHB_SLAVE1_SF_CTRL = 0x0B,
    BL_AHB_SLAVE1_DMA = 0x0C,
    BL_AHB_SLAVE1_SDU = 0x0D, //cgen rsvd
    BL_AHB_SLAVE1_PDS = 0x0E, //cgen rsvd
    BL_AHB_SLAVE1_RSVD15 = 0x0F,
    BL_AHB_SLAVE1_UART0 = 0x10,
    BL_AHB_SLAVE1_UART1 = 0x11,
    BL_AHB_SLAVE1_SPI = 0x12,
    BL_AHB_SLAVE1_I2C = 0x13,
    BL_AHB_SLAVE1_PWM = 0x14,
    BL_AHB_SLAVE1_TIMER = 0x15,
    BL_AHB_SLAVE1_IRR = 0x16,
    BL_AHB_SLAVE1_CKS = 0x17,
    BL_AHB_SLAVE1_QDEC = 0x18,
    BL_AHB_SLAVE1_KYS = 0x19,
    BL_AHB_SLAVE1_UART2 = 0x1A,
    BL_AHB_SLAVE1_RSVD27 = 0x1B,
    BL_AHB_SLAVE1_RSVD28 = 0x1C,
    BL_AHB_SLAVE1_RSVD29 = 0x1D,
    BL_AHB_SLAVE1_RSVD30 = 0x1E,
    BL_AHB_SLAVE1_RSVD31 = 0x1F,
    BL_AHB_SLAVE1_MAX = 0x20,
    BL_AHB_SLAVE1_GPADC = 0x21, /* not used for cgen and swrst */
    BL_AHB_SLAVE1_GPDAC = 0x22, /* not used for cgen and swrst */
    BL_AHB_SLAVE1_I2S = 0x23,   /* not used for cgen and swrst */
    BL_AHB_SLAVE1_CAM = 0x24,   /* not used for cgen and swrst */
} BL_AHB_Slave1_Type;

typedef enum {
    BL_AHB_SLAVE2_RSVD0 = 0x00,
    BL_AHB_SLAVE2_RSVD1 = 0x01,
    BL_AHB_SLAVE2_RSVD2 = 0x02,
    BL_AHB_SLAVE2_RSVD3 = 0x03,
    BL_AHB_SLAVE2_WIFI = 0x04,
    BL_AHB_SLAVE2_RSVD5 = 0x05,
    BL_AHB_SLAVE2_RSVD6 = 0x06,
    BL_AHB_SLAVE2_RSVD7 = 0x07,
    BL_AHB_SLAVE2_BT_BLE = 0x08,
    BL_AHB_SLAVE2_M154 = 0x09,
    BL_AHB_SLAVE2_BT_BLE2 = 0x0A,
    BL_AHB_SLAVE2_M1542 = 0x0B,
    BL_AHB_SLAVE2_RSVD12 = 0x0C,
    BL_AHB_SLAVE2_RSVD13 = 0x0D,
    BL_AHB_SLAVE2_RSVD14 = 0x0E,
    BL_AHB_SLAVE2_RSVD15 = 0x0F,
    BL_AHB_SLAVE2_EXT_EMI_MISC = 0x10,
    BL_AHB_SLAVE2_EXT_PSRAM0_CTRL = 0x11,
    BL_AHB_SLAVE2_EXT_PSRAM1_CTRL = 0x12,
    BL_AHB_SLAVE2_EXT_USB = 0x13,
    BL_AHB_SLAVE2_EXT_MIX2 = 0x14,
    BL_AHB_SLAVE2_EXT_AUDIO = 0x15,
    BL_AHB_SLAVE2_EXT_SDH = 0x16,
    BL_AHB_SLAVE2_EXT_EMAC = 0x17,
    BL_AHB_SLAVE2_EXT_DMA2 = 0x18,
    BL_AHB_SLAVE2_EXT_RSVD25 = 0x19,
    BL_AHB_SLAVE2_EXT_RSVD26 = 0x1A,
    BL_AHB_SLAVE2_EXT_RSVD27 = 0x1B,
    BL_AHB_SLAVE2_MAX = 0x1C,
} BL_AHB_Slave2_Type;

typedef enum {
    BL_AHB_SLAVE3_WIFIPLL_240M = 0x00,
    BL_AHB_SLAVE3_CPUPLL_120M = 0x01,
    BL_AHB_SLAVE3_CPUPLL_300M = 0x02,
    BL_AHB_SLAVE3_CPUPLL_600M = 0x03,
    BL_AHB_SLAVE3_MAX = 0x04,
} BL_AHB_Slave3_Type;

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
#include <system_bl808.h>
/* ARM CPU include files */
#ifdef ARCH_ARM
#ifdef CPU_AP_CM4
#include "core_cm4.h" /* Cortex-M4 processor and core peripherals */
#endif
#ifdef CPU_NP_CM0
#include "core_cm0.h" /* Cortex-M0 processor and core peripherals */
#endif
#endif
/* RISCV CPU include files */
#ifdef ARCH_RISCV
#ifdef __GNUC__
#include <csi_core.h>
#endif
#endif

#endif
