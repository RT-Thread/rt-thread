#ifndef __BL602_IRQ_H
#define __BL602_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define BL602_IRQ_NUM_BASE 16

#define BL602_IRQ_MSOFT          3
#define BL602_IRQ_MTIME          7
#define BL602_IRQ_MEXT           11
#define BL602_IRQ_CLIC_SOFT_PEND 12

#define BL602_IRQ_BMX_MCU_BUS_ERR      (BL602_IRQ_NUM_BASE + 0)
#define BL602_IRQ_BMX_MCU_TO           (BL602_IRQ_NUM_BASE + 1)
#define BL602_IRQ_L1C_BMX_ERR          (BL602_IRQ_NUM_BASE + 2)
#define BL602_IRQ_L1C_BMX_TO           (BL602_IRQ_NUM_BASE + 3)
#define BL602_IRQ_SEC_BMX_ERR          (BL602_IRQ_NUM_BASE + 4)
#define BL602_IRQ_RF_TOP_INT0          (BL602_IRQ_NUM_BASE + 5)
#define BL602_IRQ_RF_TOP_INT1          (BL602_IRQ_NUM_BASE + 6)
#define BL602_IRQ_SDIO                 (BL602_IRQ_NUM_BASE + 7)
#define BL602_IRQ_DMA_BMX_ERR          (BL602_IRQ_NUM_BASE + 8)
#define BL602_IRQ_SEC_GMAC             (BL602_IRQ_NUM_BASE + 9)
#define BL602_IRQ_SEC_CDET             (BL602_IRQ_NUM_BASE + 10)
#define BL602_IRQ_SEC_PKA              (BL602_IRQ_NUM_BASE + 11)
#define BL602_IRQ_SEC_TRNG             (BL602_IRQ_NUM_BASE + 12)
#define BL602_IRQ_SEC_AES              (BL602_IRQ_NUM_BASE + 13)
#define BL602_IRQ_SEC_SHA              (BL602_IRQ_NUM_BASE + 14)
#define BL602_IRQ_DMA0_ALL             (BL602_IRQ_NUM_BASE + 15)
#define BL602_IRQ_RESERVED0            (BL602_IRQ_NUM_BASE + 16)
#define BL602_IRQ_RESERVED1            (BL602_IRQ_NUM_BASE + 17)
#define BL602_IRQ_RESERVED2            (BL602_IRQ_NUM_BASE + 18)
#define BL602_IRQ_IRTX                 (BL602_IRQ_NUM_BASE + 19)
#define BL602_IRQ_IRRX                 (BL602_IRQ_NUM_BASE + 20)
#define BL602_IRQ_RESERVED3            (BL602_IRQ_NUM_BASE + 21)
#define BL602_IRQ_RESERVED4            (BL602_IRQ_NUM_BASE + 22)
#define BL602_IRQ_SF_CTRL              (BL602_IRQ_NUM_BASE + 23)
#define BL602_IRQ_RESERVED5            (BL602_IRQ_NUM_BASE + 24)
#define BL602_IRQ_GPADC_DMA            (BL602_IRQ_NUM_BASE + 25)
#define BL602_IRQ_EFUSE                (BL602_IRQ_NUM_BASE + 26)
#define BL602_IRQ_SPI0                 (BL602_IRQ_NUM_BASE + 27)
#define BL602_IRQ_RESERVED6            (BL602_IRQ_NUM_BASE + 28)
#define BL602_IRQ_UART0                (BL602_IRQ_NUM_BASE + 29)
#define BL602_IRQ_UART1                (BL602_IRQ_NUM_BASE + 30)
#define BL602_IRQ_RESERVED7            (BL602_IRQ_NUM_BASE + 31)
#define BL602_IRQ_I2C0                 (BL602_IRQ_NUM_BASE + 32)
#define BL602_IRQ_RESERVED8            (BL602_IRQ_NUM_BASE + 33)
#define BL602_IRQ_PWM                  (BL602_IRQ_NUM_BASE + 34)
#define BL602_IRQ_RESERVED9            (BL602_IRQ_NUM_BASE + 35)
#define BL602_IRQ_TIMER0               (BL602_IRQ_NUM_BASE + 36)
#define BL602_IRQ_TIMER1               (BL602_IRQ_NUM_BASE + 37)
#define BL602_IRQ_WDT                  (BL602_IRQ_NUM_BASE + 38)
#define BL602_IRQ_RESERVED10           (BL602_IRQ_NUM_BASE + 39)
#define BL602_IRQ_RESERVED11           (BL602_IRQ_NUM_BASE + 40)
#define BL602_IRQ_RESERVED12           (BL602_IRQ_NUM_BASE + 41)
#define BL602_IRQ_RESERVED13           (BL602_IRQ_NUM_BASE + 42)
#define BL602_IRQ_RESERVED14           (BL602_IRQ_NUM_BASE + 43)
#define BL602_IRQ_GPIO_INT0            (BL602_IRQ_NUM_BASE + 44)
#define BL602_IRQ_RESERVED15           (BL602_IRQ_NUM_BASE + 45)
#define BL602_IRQ_RESERVED16           (BL602_IRQ_NUM_BASE + 46)
#define BL602_IRQ_RESERVED17           (BL602_IRQ_NUM_BASE + 47)
#define BL602_IRQ_RESERVED18           (BL602_IRQ_NUM_BASE + 48)
#define BL602_IRQ_RESERVED19           (BL602_IRQ_NUM_BASE + 49)
#define BL602_IRQ_PDS_WAKEUP           (BL602_IRQ_NUM_BASE + 50)
#define BL602_IRQ_HBN_OUT0             (BL602_IRQ_NUM_BASE + 51)
#define BL602_IRQ_HBN_OUT1             (BL602_IRQ_NUM_BASE + 52)
#define BL602_IRQ_BOR                  (BL602_IRQ_NUM_BASE + 53)
#define BL602_IRQ_WIFI                 (BL602_IRQ_NUM_BASE + 54)
#define BL616_IRQ_BZ_PHY_INT           (BL602_IRQ_NUM_BASE + 55)
#define BL602_IRQ_BLE                  (BL602_IRQ_NUM_BASE + 56)
#define BL602_IRQ_MAC_INT_TIMER        (BL602_IRQ_NUM_BASE + 57)
#define BL602_IRQ_MAC_INT_MISC         (BL602_IRQ_NUM_BASE + 58)
#define BL602_IRQ_MAC_INT_RX_TRIGGER   (BL602_IRQ_NUM_BASE + 59)
#define BL602_IRQ_MAC_INT_TX_TRIGGER   (BL602_IRQ_NUM_BASE + 60)
#define BL602_IRQ_MAC_INT_GEN          (BL602_IRQ_NUM_BASE + 61)
#define BL602_IRQ_MAC_INT_PROT_TRIGGER (BL602_IRQ_NUM_BASE + 62)
#define BL602_IRQ_WIFI_IPC             (BL602_IRQ_NUM_BASE + 63)

#endif
