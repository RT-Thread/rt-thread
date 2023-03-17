#ifndef __BL702_IRQ_H
#define __BL702_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define BL702_IRQ_NUM_BASE 16

#define BL702_IRQ_MSOFT          3
#define BL702_IRQ_MTIME          7
#define BL702_IRQ_MEXT           11
#define BL702_IRQ_CLIC_SOFT_PEND 12

#define BL702_IRQ_BMX_MCU_BUS_ERR      (BL702_IRQ_NUM_BASE + 0)
#define BL702_IRQ_BMX_MCU_TO           (BL702_IRQ_NUM_BASE + 1)
#define BL702_IRQ_L1C_BMX_ERR          (BL702_IRQ_NUM_BASE + 2)
#define BL702_IRQ_L1C_BMX_TO           (BL702_IRQ_NUM_BASE + 3)
#define BL702_IRQ_SEC_BMX_ERR          (BL702_IRQ_NUM_BASE + 4)
#define BL702_IRQ_RF_TOP_INT0          (BL702_IRQ_NUM_BASE + 5)
#define BL702_IRQ_RF_TOP_INT1          (BL702_IRQ_NUM_BASE + 6)
#define BL702_IRQ_RESERVED0            (BL702_IRQ_NUM_BASE + 7)
#define BL702_IRQ_DMA_BMX_ERR          (BL702_IRQ_NUM_BASE + 8)
#define BL702_IRQ_SEC_GMAC             (BL702_IRQ_NUM_BASE + 9)
#define BL702_IRQ_SEC_CDET             (BL702_IRQ_NUM_BASE + 10)
#define BL702_IRQ_SEC_PKA              (BL702_IRQ_NUM_BASE + 11)
#define BL702_IRQ_SEC_TRNG             (BL702_IRQ_NUM_BASE + 12)
#define BL702_IRQ_SEC_AES              (BL702_IRQ_NUM_BASE + 13)
#define BL702_IRQ_SEC_SHA              (BL702_IRQ_NUM_BASE + 14)
#define BL702_IRQ_DMA0_ALL             (BL702_IRQ_NUM_BASE + 15)
#define BL702_IRQ_MJPEG                (BL702_IRQ_NUM_BASE + 16)
#define BL702_IRQ_CAM                  (BL702_IRQ_NUM_BASE + 17)
#define BL702_IRQ_I2S                  (BL702_IRQ_NUM_BASE + 18)
#define BL702_IRQ_IRTX                 (BL702_IRQ_NUM_BASE + 19)
#define BL702_IRQ_IRRX                 (BL702_IRQ_NUM_BASE + 20)
#define BL702_IRQ_USB                  (BL702_IRQ_NUM_BASE + 21)
#define BL702_IRQ_EMAC                 (BL702_IRQ_NUM_BASE + 22)
#define BL702_IRQ_SF_CTRL              (BL702_IRQ_NUM_BASE + 23)
#define BL702_IRQ_RESERVED1            (BL702_IRQ_NUM_BASE + 24)
#define BL702_IRQ_GPADC_DMA            (BL702_IRQ_NUM_BASE + 25)
#define BL702_IRQ_EFUSE                (BL702_IRQ_NUM_BASE + 26)
#define BL702_IRQ_SPI0                 (BL702_IRQ_NUM_BASE + 27)
#define BL702_IRQ_RESERVED2            (BL702_IRQ_NUM_BASE + 28)
#define BL702_IRQ_UART0                (BL702_IRQ_NUM_BASE + 29)
#define BL702_IRQ_UART1                (BL702_IRQ_NUM_BASE + 30)
#define BL702_IRQ_RESERVED3            (BL702_IRQ_NUM_BASE + 31)
#define BL702_IRQ_I2C0                 (BL702_IRQ_NUM_BASE + 32)
#define BL702_IRQ_RESERVED4            (BL702_IRQ_NUM_BASE + 33)
#define BL702_IRQ_PWM                  (BL702_IRQ_NUM_BASE + 34)
#define BL702_IRQ_RESERVED5            (BL702_IRQ_NUM_BASE + 35)
#define BL702_IRQ_TIMER0               (BL702_IRQ_NUM_BASE + 36)
#define BL702_IRQ_TIMER1               (BL702_IRQ_NUM_BASE + 37)
#define BL702_IRQ_WDT                  (BL702_IRQ_NUM_BASE + 38)
#define BL702_IRQ_KYS                  (BL702_IRQ_NUM_BASE + 39)
#define BL702_IRQ_QDEC0                (BL702_IRQ_NUM_BASE + 40)
#define BL702_IRQ_QDEC1                (BL702_IRQ_NUM_BASE + 41)
#define BL702_IRQ_QDEC2                (BL702_IRQ_NUM_BASE + 42)
#define BL702_IRQ_RESERVED6            (BL702_IRQ_NUM_BASE + 43)
#define BL702_IRQ_GPIO_INT0            (BL702_IRQ_NUM_BASE + 44)
#define BL702_IRQ_TOUCH                (BL702_IRQ_NUM_BASE + 45)
#define BL702_IRQ_RESERVED7            (BL702_IRQ_NUM_BASE + 46)
#define BL702_IRQ_M154_REQ_ENH_ACK     (BL702_IRQ_NUM_BASE + 47)
#define BL702_IRQ_M154                 (BL702_IRQ_NUM_BASE + 48)
#define BL702_IRQ_M154_AES             (BL702_IRQ_NUM_BASE + 49)
#define BL702_IRQ_PDS_WAKEUP           (BL702_IRQ_NUM_BASE + 50)
#define BL702_IRQ_HBN_OUT0             (BL702_IRQ_NUM_BASE + 51)
#define BL702_IRQ_HBN_OUT1             (BL702_IRQ_NUM_BASE + 52)
#define BL702_IRQ_BOR                  (BL702_IRQ_NUM_BASE + 53)
#define BL702_IRQ_WIFI                 (BL702_IRQ_NUM_BASE + 54)
#define BL616_IRQ_BZ_PHY_INT           (BL702_IRQ_NUM_BASE + 55)
#define BL702_IRQ_BLE                  (BL702_IRQ_NUM_BASE + 56)
#define BL702_IRQ_MAC_INT_TIMER        (BL702_IRQ_NUM_BASE + 57)
#define BL702_IRQ_MAC_INT_MISC         (BL702_IRQ_NUM_BASE + 58)
#define BL702_IRQ_MAC_INT_RX_TRIGGER   (BL702_IRQ_NUM_BASE + 59)
#define BL702_IRQ_MAC_INT_TX_TRIGGER   (BL702_IRQ_NUM_BASE + 60)
#define BL702_IRQ_MAC_INT_GEN          (BL702_IRQ_NUM_BASE + 61)
#define BL702_IRQ_MAC_INT_PROT_TRIGGER (BL702_IRQ_NUM_BASE + 62)
#define BL702_IRQ_WIFI_IPC             (BL702_IRQ_NUM_BASE + 63)

#endif
