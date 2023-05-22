#ifndef __BL616_IRQ_H
#define __BL616_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define BL616_IRQ_NUM_BASE       16

#define BL616_IRQ_SSOFT          1
#define BL616_IRQ_MSOFT          3
#define BL616_IRQ_STIME          5
#define BL616_IRQ_MTIME          7
#define BL616_IRQ_SEXT           9
#define BL616_IRQ_MEXT           11
#define BL616_IRQ_CLIC_SOFT_PEND 12
#if (__riscv_xlen == 64)
#define BL616_IRQ_HPM_OVF 17
#endif

#define BL616_IRQ_BMX_MCU_BUS_ERR                   (BL616_IRQ_NUM_BASE + 0)
#define BL616_IRQ_BMX_MCU_TO                        (BL616_IRQ_NUM_BASE + 1)
#define BL616_IRQ_DBI                               (BL616_IRQ_NUM_BASE + 2)
#define BL616_IRQ_SDU_SOFT_RST                      (BL616_IRQ_NUM_BASE + 3)
#define BL616_IRQ_AUDAC                             (BL616_IRQ_NUM_BASE + 4)
#define BL616_IRQ_RF_TOP_INT0                       (BL616_IRQ_NUM_BASE + 5)
#define BL616_IRQ_RF_TOP_INT1                       (BL616_IRQ_NUM_BASE + 6)
#define BL616_IRQ_SDIO                              (BL616_IRQ_NUM_BASE + 7)
#define BL616_IRQ_WIFI_TBTT_SLEEP                   (BL616_IRQ_NUM_BASE + 8)
#define BL616_IRQ_SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC (BL616_IRQ_NUM_BASE + 9)
#define BL616_IRQ_SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC (BL616_IRQ_NUM_BASE + 10)
#define BL616_IRQ_SEC_ENG_ID1_CDET                  (BL616_IRQ_NUM_BASE + 11)
#define BL616_IRQ_SEC_ENG_ID0_CDET                  (BL616_IRQ_NUM_BASE + 12)
#define BL616_IRQ_SF_CTRL_ID1                       (BL616_IRQ_NUM_BASE + 13)
#define BL616_IRQ_SF_CTRL_ID0                       (BL616_IRQ_NUM_BASE + 14)
#define BL616_IRQ_DMA0_ALL                          (BL616_IRQ_NUM_BASE + 15)
#define BL616_IRQ_DVP2BUS_INT0                      (BL616_IRQ_NUM_BASE + 16)
#define BL616_IRQ_SDH                               (BL616_IRQ_NUM_BASE + 17)
#define BL616_IRQ_DVP2BUS_INT1                      (BL616_IRQ_NUM_BASE + 18)
#define BL616_IRQ_WIFI_TBTT_WAKEUP                  (BL616_IRQ_NUM_BASE + 19)
#define BL616_IRQ_IRRX                              (BL616_IRQ_NUM_BASE + 20)
#define BL616_IRQ_USB                               (BL616_IRQ_NUM_BASE + 21)
#define BL616_IRQ_AUADC                             (BL616_IRQ_NUM_BASE + 22)
#define BL616_IRQ_MJPEG                             (BL616_IRQ_NUM_BASE + 23)
#define BL616_IRQ_EMAC                              (BL616_IRQ_NUM_BASE + 24)
#define BL616_IRQ_GPADC_DMA                         (BL616_IRQ_NUM_BASE + 25)
#define BL616_IRQ_EFUSE                             (BL616_IRQ_NUM_BASE + 26)
#define BL616_IRQ_SPI0                              (BL616_IRQ_NUM_BASE + 27)
#define BL616_IRQ_UART0                             (BL616_IRQ_NUM_BASE + 28)
#define BL616_IRQ_UART1                             (BL616_IRQ_NUM_BASE + 29)
#define BL616_IRQ_GPIO_DMA                          (BL616_IRQ_NUM_BASE + 31)
#define BL616_IRQ_I2C0                              (BL616_IRQ_NUM_BASE + 32)
#define BL616_IRQ_PWM                               (BL616_IRQ_NUM_BASE + 33)
#define BL616_IRQ_RESERVED0                         (BL616_IRQ_NUM_BASE + 34)
#define BL616_IRQ_RESERVED1                         (BL616_IRQ_NUM_BASE + 35)
#define BL616_IRQ_TIMER0                            (BL616_IRQ_NUM_BASE + 36)
#define BL616_IRQ_TIMER1                            (BL616_IRQ_NUM_BASE + 37)
#define BL616_IRQ_WDG                               (BL616_IRQ_NUM_BASE + 38)
#define BL616_IRQ_I2C1                              (BL616_IRQ_NUM_BASE + 39)
#define BL616_IRQ_I2S                               (BL616_IRQ_NUM_BASE + 40)
#define BL616_IRQ_ANA_OCP_OUT_TO_CPU_0              (BL616_IRQ_NUM_BASE + 41)
#define BL616_IRQ_ANA_OCP_OUT_TO_CPU_1              (BL616_IRQ_NUM_BASE + 42)
#define BL616_IRQ_XTAL_RDY_SCAN                     (BL616_IRQ_NUM_BASE + 43)
#define BL616_IRQ_GPIO_INT0                         (BL616_IRQ_NUM_BASE + 44)
#define BL616_IRQ_DM                                (BL616_IRQ_NUM_BASE + 45)
#define BL616_IRQ_BT                                (BL616_IRQ_NUM_BASE + 46)
#define BL616_IRQ_M154_REQ_ACK                      (BL616_IRQ_NUM_BASE + 47)
#define BL616_IRQ_M154                              (BL616_IRQ_NUM_BASE + 48)
#define BL616_IRQ_M154_AES                          (BL616_IRQ_NUM_BASE + 49)
#define BL616_IRQ_PDS_WAKEUP                        (BL616_IRQ_NUM_BASE + 50)
#define BL616_IRQ_HBN_OUT0                          (BL616_IRQ_NUM_BASE + 51)
#define BL616_IRQ_HBN_OUT1                          (BL616_IRQ_NUM_BASE + 52)
#define BL616_IRQ_BOD                               (BL616_IRQ_NUM_BASE + 53)
#define BL616_IRQ_WIFI                              (BL616_IRQ_NUM_BASE + 54)
#define BL616_IRQ_BZ_PHY_INT                        (BL616_IRQ_NUM_BASE + 55)
#define BL616_IRQ_BLE                               (BL616_IRQ_NUM_BASE + 56)
#define BL616_IRQ_MAC_INT_TIMER                     (BL616_IRQ_NUM_BASE + 57)
#define BL616_IRQ_MAC_INT_MISC                      (BL616_IRQ_NUM_BASE + 58)
#define BL616_IRQ_MAC_INT_RX_TRIGGER                (BL616_IRQ_NUM_BASE + 59)
#define BL616_IRQ_MAC_INT_TX_TRIGGER                (BL616_IRQ_NUM_BASE + 60)
#define BL616_IRQ_MAC_INT_GEN                       (BL616_IRQ_NUM_BASE + 61)
#define BL616_IRQ_MAC_INT_PROT_TRIGGER              (BL616_IRQ_NUM_BASE + 62)
#define BL616_IRQ_WIFI_IPC                          (BL616_IRQ_NUM_BASE + 63)

#endif
