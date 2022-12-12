/* Auto-generated config file hpl_xdmac_config.h */
#ifndef HPL_XDMAC_CONFIG_H
#define HPL_XDMAC_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <e> XDMAC enable
// <i> Indicates whether xdmac is enabled or not
// <id> xdmac_enable
#ifndef CONF_DMA_ENABLE
#define CONF_DMA_ENABLE 0
#endif

// <e> Channel 0 settings
// <id> dmac_channel_0_settings
#ifndef CONF_DMAC_CHANNEL_0_SETTINGS
#define CONF_DMAC_CHANNEL_0_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_0
#ifndef CONF_DMAC_BURSTSIZE_0
#define CONF_DMAC_BURSTSIZE_0 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_0
#ifndef CONF_DMAC_CHUNKSIZE_0
#define CONF_DMAC_CHUNKSIZE_0 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_0
#ifndef CONF_DMAC_BEATSIZE_0
#define CONF_DMAC_BEATSIZE_0 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_0
#ifndef CONF_DMAC_SRC_INTERFACE_0
#define CONF_DMAC_SRC_INTERFACE_0 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_0
#ifndef CONF_DMAC_DES_INTERFACE_0
#define CONF_DMAC_DES_INTERFACE_0 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_0
#ifndef CONF_DMAC_SRCINC_0
#define CONF_DMAC_SRCINC_0 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_0
#ifndef CONF_DMAC_DSTINC_0
#define CONF_DMAC_DSTINC_0 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_0
#ifndef CONF_DMAC_TRANS_TYPE_0
#define CONF_DMAC_TRANS_TYPE_0 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_0
#ifndef CONF_DMAC_TRIGSRC_0
#define CONF_DMAC_TRIGSRC_0 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_0 == 0
#define CONF_DMAC_TYPE_0 0
#define CONF_DMAC_DSYNC_0 0
#elif CONF_DMAC_TRANS_TYPE_0 == 1
#define CONF_DMAC_TYPE_0 1
#define CONF_DMAC_DSYNC_0 0
#elif CONF_DMAC_TRANS_TYPE_0 == 2
#define CONF_DMAC_TYPE_0 1
#define CONF_DMAC_DSYNC_0 1
#endif

#if CONF_DMAC_TRIGSRC_0 == 0xFF
#define CONF_DMAC_SWREQ_0 1
#else
#define CONF_DMAC_SWREQ_0 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_0_SETTINGS == 1 && CONF_DMAC_BEATSIZE_0 != 2 && ((!CONF_DMAC_SRCINC_0) || (!CONF_DMAC_DSTINC_0)))
#if (!CONF_DMAC_SRCINC_0)
#define CONF_DMAC_SRC_STRIDE_0 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_0)
#define CONF_DMAC_DES_STRIDE_0 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_0
#define CONF_DMAC_SRC_STRIDE_0 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_0
#define CONF_DMAC_DES_STRIDE_0 0
#endif

// <e> Channel 1 settings
// <id> dmac_channel_1_settings
#ifndef CONF_DMAC_CHANNEL_1_SETTINGS
#define CONF_DMAC_CHANNEL_1_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_1
#ifndef CONF_DMAC_BURSTSIZE_1
#define CONF_DMAC_BURSTSIZE_1 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_1
#ifndef CONF_DMAC_CHUNKSIZE_1
#define CONF_DMAC_CHUNKSIZE_1 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_1
#ifndef CONF_DMAC_BEATSIZE_1
#define CONF_DMAC_BEATSIZE_1 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_1
#ifndef CONF_DMAC_SRC_INTERFACE_1
#define CONF_DMAC_SRC_INTERFACE_1 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_1
#ifndef CONF_DMAC_DES_INTERFACE_1
#define CONF_DMAC_DES_INTERFACE_1 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_1
#ifndef CONF_DMAC_SRCINC_1
#define CONF_DMAC_SRCINC_1 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_1
#ifndef CONF_DMAC_DSTINC_1
#define CONF_DMAC_DSTINC_1 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_1
#ifndef CONF_DMAC_TRANS_TYPE_1
#define CONF_DMAC_TRANS_TYPE_1 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_1
#ifndef CONF_DMAC_TRIGSRC_1
#define CONF_DMAC_TRIGSRC_1 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_1 == 0
#define CONF_DMAC_TYPE_1 0
#define CONF_DMAC_DSYNC_1 0
#elif CONF_DMAC_TRANS_TYPE_1 == 1
#define CONF_DMAC_TYPE_1 1
#define CONF_DMAC_DSYNC_1 0
#elif CONF_DMAC_TRANS_TYPE_1 == 2
#define CONF_DMAC_TYPE_1 1
#define CONF_DMAC_DSYNC_1 1
#endif

#if CONF_DMAC_TRIGSRC_1 == 0xFF
#define CONF_DMAC_SWREQ_1 1
#else
#define CONF_DMAC_SWREQ_1 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_1_SETTINGS == 1 && CONF_DMAC_BEATSIZE_1 != 2 && ((!CONF_DMAC_SRCINC_1) || (!CONF_DMAC_DSTINC_1)))
#if (!CONF_DMAC_SRCINC_1)
#define CONF_DMAC_SRC_STRIDE_1 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_1)
#define CONF_DMAC_DES_STRIDE_1 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_1
#define CONF_DMAC_SRC_STRIDE_1 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_1
#define CONF_DMAC_DES_STRIDE_1 0
#endif

// <e> Channel 2 settings
// <id> dmac_channel_2_settings
#ifndef CONF_DMAC_CHANNEL_2_SETTINGS
#define CONF_DMAC_CHANNEL_2_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_2
#ifndef CONF_DMAC_BURSTSIZE_2
#define CONF_DMAC_BURSTSIZE_2 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_2
#ifndef CONF_DMAC_CHUNKSIZE_2
#define CONF_DMAC_CHUNKSIZE_2 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_2
#ifndef CONF_DMAC_BEATSIZE_2
#define CONF_DMAC_BEATSIZE_2 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_2
#ifndef CONF_DMAC_SRC_INTERFACE_2
#define CONF_DMAC_SRC_INTERFACE_2 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_2
#ifndef CONF_DMAC_DES_INTERFACE_2
#define CONF_DMAC_DES_INTERFACE_2 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_2
#ifndef CONF_DMAC_SRCINC_2
#define CONF_DMAC_SRCINC_2 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_2
#ifndef CONF_DMAC_DSTINC_2
#define CONF_DMAC_DSTINC_2 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_2
#ifndef CONF_DMAC_TRANS_TYPE_2
#define CONF_DMAC_TRANS_TYPE_2 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_2
#ifndef CONF_DMAC_TRIGSRC_2
#define CONF_DMAC_TRIGSRC_2 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_2 == 0
#define CONF_DMAC_TYPE_2 0
#define CONF_DMAC_DSYNC_2 0
#elif CONF_DMAC_TRANS_TYPE_2 == 1
#define CONF_DMAC_TYPE_2 1
#define CONF_DMAC_DSYNC_2 0
#elif CONF_DMAC_TRANS_TYPE_2 == 2
#define CONF_DMAC_TYPE_2 1
#define CONF_DMAC_DSYNC_2 1
#endif

#if CONF_DMAC_TRIGSRC_2 == 0xFF
#define CONF_DMAC_SWREQ_2 1
#else
#define CONF_DMAC_SWREQ_2 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_2_SETTINGS == 1 && CONF_DMAC_BEATSIZE_2 != 2 && ((!CONF_DMAC_SRCINC_2) || (!CONF_DMAC_DSTINC_2)))
#if (!CONF_DMAC_SRCINC_2)
#define CONF_DMAC_SRC_STRIDE_2 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_2)
#define CONF_DMAC_DES_STRIDE_2 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_2
#define CONF_DMAC_SRC_STRIDE_2 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_2
#define CONF_DMAC_DES_STRIDE_2 0
#endif

// <e> Channel 3 settings
// <id> dmac_channel_3_settings
#ifndef CONF_DMAC_CHANNEL_3_SETTINGS
#define CONF_DMAC_CHANNEL_3_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_3
#ifndef CONF_DMAC_BURSTSIZE_3
#define CONF_DMAC_BURSTSIZE_3 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_3
#ifndef CONF_DMAC_CHUNKSIZE_3
#define CONF_DMAC_CHUNKSIZE_3 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_3
#ifndef CONF_DMAC_BEATSIZE_3
#define CONF_DMAC_BEATSIZE_3 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_3
#ifndef CONF_DMAC_SRC_INTERFACE_3
#define CONF_DMAC_SRC_INTERFACE_3 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_3
#ifndef CONF_DMAC_DES_INTERFACE_3
#define CONF_DMAC_DES_INTERFACE_3 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_3
#ifndef CONF_DMAC_SRCINC_3
#define CONF_DMAC_SRCINC_3 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_3
#ifndef CONF_DMAC_DSTINC_3
#define CONF_DMAC_DSTINC_3 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_3
#ifndef CONF_DMAC_TRANS_TYPE_3
#define CONF_DMAC_TRANS_TYPE_3 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_3
#ifndef CONF_DMAC_TRIGSRC_3
#define CONF_DMAC_TRIGSRC_3 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_3 == 0
#define CONF_DMAC_TYPE_3 0
#define CONF_DMAC_DSYNC_3 0
#elif CONF_DMAC_TRANS_TYPE_3 == 1
#define CONF_DMAC_TYPE_3 1
#define CONF_DMAC_DSYNC_3 0
#elif CONF_DMAC_TRANS_TYPE_3 == 2
#define CONF_DMAC_TYPE_3 1
#define CONF_DMAC_DSYNC_3 1
#endif

#if CONF_DMAC_TRIGSRC_3 == 0xFF
#define CONF_DMAC_SWREQ_3 1
#else
#define CONF_DMAC_SWREQ_3 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_3_SETTINGS == 1 && CONF_DMAC_BEATSIZE_3 != 2 && ((!CONF_DMAC_SRCINC_3) || (!CONF_DMAC_DSTINC_3)))
#if (!CONF_DMAC_SRCINC_3)
#define CONF_DMAC_SRC_STRIDE_3 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_3)
#define CONF_DMAC_DES_STRIDE_3 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_3
#define CONF_DMAC_SRC_STRIDE_3 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_3
#define CONF_DMAC_DES_STRIDE_3 0
#endif

// <e> Channel 4 settings
// <id> dmac_channel_4_settings
#ifndef CONF_DMAC_CHANNEL_4_SETTINGS
#define CONF_DMAC_CHANNEL_4_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_4
#ifndef CONF_DMAC_BURSTSIZE_4
#define CONF_DMAC_BURSTSIZE_4 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_4
#ifndef CONF_DMAC_CHUNKSIZE_4
#define CONF_DMAC_CHUNKSIZE_4 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_4
#ifndef CONF_DMAC_BEATSIZE_4
#define CONF_DMAC_BEATSIZE_4 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_4
#ifndef CONF_DMAC_SRC_INTERFACE_4
#define CONF_DMAC_SRC_INTERFACE_4 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_4
#ifndef CONF_DMAC_DES_INTERFACE_4
#define CONF_DMAC_DES_INTERFACE_4 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_4
#ifndef CONF_DMAC_SRCINC_4
#define CONF_DMAC_SRCINC_4 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_4
#ifndef CONF_DMAC_DSTINC_4
#define CONF_DMAC_DSTINC_4 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_4
#ifndef CONF_DMAC_TRANS_TYPE_4
#define CONF_DMAC_TRANS_TYPE_4 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_4
#ifndef CONF_DMAC_TRIGSRC_4
#define CONF_DMAC_TRIGSRC_4 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_4 == 0
#define CONF_DMAC_TYPE_4 0
#define CONF_DMAC_DSYNC_4 0
#elif CONF_DMAC_TRANS_TYPE_4 == 1
#define CONF_DMAC_TYPE_4 1
#define CONF_DMAC_DSYNC_4 0
#elif CONF_DMAC_TRANS_TYPE_4 == 2
#define CONF_DMAC_TYPE_4 1
#define CONF_DMAC_DSYNC_4 1
#endif

#if CONF_DMAC_TRIGSRC_4 == 0xFF
#define CONF_DMAC_SWREQ_4 1
#else
#define CONF_DMAC_SWREQ_4 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_4_SETTINGS == 1 && CONF_DMAC_BEATSIZE_4 != 2 && ((!CONF_DMAC_SRCINC_4) || (!CONF_DMAC_DSTINC_4)))
#if (!CONF_DMAC_SRCINC_4)
#define CONF_DMAC_SRC_STRIDE_4 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_4)
#define CONF_DMAC_DES_STRIDE_4 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_4
#define CONF_DMAC_SRC_STRIDE_4 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_4
#define CONF_DMAC_DES_STRIDE_4 0
#endif

// <e> Channel 5 settings
// <id> dmac_channel_5_settings
#ifndef CONF_DMAC_CHANNEL_5_SETTINGS
#define CONF_DMAC_CHANNEL_5_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_5
#ifndef CONF_DMAC_BURSTSIZE_5
#define CONF_DMAC_BURSTSIZE_5 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_5
#ifndef CONF_DMAC_CHUNKSIZE_5
#define CONF_DMAC_CHUNKSIZE_5 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_5
#ifndef CONF_DMAC_BEATSIZE_5
#define CONF_DMAC_BEATSIZE_5 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_5
#ifndef CONF_DMAC_SRC_INTERFACE_5
#define CONF_DMAC_SRC_INTERFACE_5 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_5
#ifndef CONF_DMAC_DES_INTERFACE_5
#define CONF_DMAC_DES_INTERFACE_5 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_5
#ifndef CONF_DMAC_SRCINC_5
#define CONF_DMAC_SRCINC_5 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_5
#ifndef CONF_DMAC_DSTINC_5
#define CONF_DMAC_DSTINC_5 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_5
#ifndef CONF_DMAC_TRANS_TYPE_5
#define CONF_DMAC_TRANS_TYPE_5 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_5
#ifndef CONF_DMAC_TRIGSRC_5
#define CONF_DMAC_TRIGSRC_5 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_5 == 0
#define CONF_DMAC_TYPE_5 0
#define CONF_DMAC_DSYNC_5 0
#elif CONF_DMAC_TRANS_TYPE_5 == 1
#define CONF_DMAC_TYPE_5 1
#define CONF_DMAC_DSYNC_5 0
#elif CONF_DMAC_TRANS_TYPE_5 == 2
#define CONF_DMAC_TYPE_5 1
#define CONF_DMAC_DSYNC_5 1
#endif

#if CONF_DMAC_TRIGSRC_5 == 0xFF
#define CONF_DMAC_SWREQ_5 1
#else
#define CONF_DMAC_SWREQ_5 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_5_SETTINGS == 1 && CONF_DMAC_BEATSIZE_5 != 2 && ((!CONF_DMAC_SRCINC_5) || (!CONF_DMAC_DSTINC_5)))
#if (!CONF_DMAC_SRCINC_5)
#define CONF_DMAC_SRC_STRIDE_5 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_5)
#define CONF_DMAC_DES_STRIDE_5 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_5
#define CONF_DMAC_SRC_STRIDE_5 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_5
#define CONF_DMAC_DES_STRIDE_5 0
#endif

// <e> Channel 6 settings
// <id> dmac_channel_6_settings
#ifndef CONF_DMAC_CHANNEL_6_SETTINGS
#define CONF_DMAC_CHANNEL_6_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_6
#ifndef CONF_DMAC_BURSTSIZE_6
#define CONF_DMAC_BURSTSIZE_6 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_6
#ifndef CONF_DMAC_CHUNKSIZE_6
#define CONF_DMAC_CHUNKSIZE_6 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_6
#ifndef CONF_DMAC_BEATSIZE_6
#define CONF_DMAC_BEATSIZE_6 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_6
#ifndef CONF_DMAC_SRC_INTERFACE_6
#define CONF_DMAC_SRC_INTERFACE_6 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_6
#ifndef CONF_DMAC_DES_INTERFACE_6
#define CONF_DMAC_DES_INTERFACE_6 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_6
#ifndef CONF_DMAC_SRCINC_6
#define CONF_DMAC_SRCINC_6 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_6
#ifndef CONF_DMAC_DSTINC_6
#define CONF_DMAC_DSTINC_6 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_6
#ifndef CONF_DMAC_TRANS_TYPE_6
#define CONF_DMAC_TRANS_TYPE_6 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_6
#ifndef CONF_DMAC_TRIGSRC_6
#define CONF_DMAC_TRIGSRC_6 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_6 == 0
#define CONF_DMAC_TYPE_6 0
#define CONF_DMAC_DSYNC_6 0
#elif CONF_DMAC_TRANS_TYPE_6 == 1
#define CONF_DMAC_TYPE_6 1
#define CONF_DMAC_DSYNC_6 0
#elif CONF_DMAC_TRANS_TYPE_6 == 2
#define CONF_DMAC_TYPE_6 1
#define CONF_DMAC_DSYNC_6 1
#endif

#if CONF_DMAC_TRIGSRC_6 == 0xFF
#define CONF_DMAC_SWREQ_6 1
#else
#define CONF_DMAC_SWREQ_6 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_6_SETTINGS == 1 && CONF_DMAC_BEATSIZE_6 != 2 && ((!CONF_DMAC_SRCINC_6) || (!CONF_DMAC_DSTINC_6)))
#if (!CONF_DMAC_SRCINC_6)
#define CONF_DMAC_SRC_STRIDE_6 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_6)
#define CONF_DMAC_DES_STRIDE_6 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_6
#define CONF_DMAC_SRC_STRIDE_6 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_6
#define CONF_DMAC_DES_STRIDE_6 0
#endif

// <e> Channel 7 settings
// <id> dmac_channel_7_settings
#ifndef CONF_DMAC_CHANNEL_7_SETTINGS
#define CONF_DMAC_CHANNEL_7_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_7
#ifndef CONF_DMAC_BURSTSIZE_7
#define CONF_DMAC_BURSTSIZE_7 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_7
#ifndef CONF_DMAC_CHUNKSIZE_7
#define CONF_DMAC_CHUNKSIZE_7 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_7
#ifndef CONF_DMAC_BEATSIZE_7
#define CONF_DMAC_BEATSIZE_7 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_7
#ifndef CONF_DMAC_SRC_INTERFACE_7
#define CONF_DMAC_SRC_INTERFACE_7 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_7
#ifndef CONF_DMAC_DES_INTERFACE_7
#define CONF_DMAC_DES_INTERFACE_7 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_7
#ifndef CONF_DMAC_SRCINC_7
#define CONF_DMAC_SRCINC_7 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_7
#ifndef CONF_DMAC_DSTINC_7
#define CONF_DMAC_DSTINC_7 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_7
#ifndef CONF_DMAC_TRANS_TYPE_7
#define CONF_DMAC_TRANS_TYPE_7 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_7
#ifndef CONF_DMAC_TRIGSRC_7
#define CONF_DMAC_TRIGSRC_7 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_7 == 0
#define CONF_DMAC_TYPE_7 0
#define CONF_DMAC_DSYNC_7 0
#elif CONF_DMAC_TRANS_TYPE_7 == 1
#define CONF_DMAC_TYPE_7 1
#define CONF_DMAC_DSYNC_7 0
#elif CONF_DMAC_TRANS_TYPE_7 == 2
#define CONF_DMAC_TYPE_7 1
#define CONF_DMAC_DSYNC_7 1
#endif

#if CONF_DMAC_TRIGSRC_7 == 0xFF
#define CONF_DMAC_SWREQ_7 1
#else
#define CONF_DMAC_SWREQ_7 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_7_SETTINGS == 1 && CONF_DMAC_BEATSIZE_7 != 2 && ((!CONF_DMAC_SRCINC_7) || (!CONF_DMAC_DSTINC_7)))
#if (!CONF_DMAC_SRCINC_7)
#define CONF_DMAC_SRC_STRIDE_7 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_7)
#define CONF_DMAC_DES_STRIDE_7 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_7
#define CONF_DMAC_SRC_STRIDE_7 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_7
#define CONF_DMAC_DES_STRIDE_7 0
#endif

// <e> Channel 8 settings
// <id> dmac_channel_8_settings
#ifndef CONF_DMAC_CHANNEL_8_SETTINGS
#define CONF_DMAC_CHANNEL_8_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_8
#ifndef CONF_DMAC_BURSTSIZE_8
#define CONF_DMAC_BURSTSIZE_8 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_8
#ifndef CONF_DMAC_CHUNKSIZE_8
#define CONF_DMAC_CHUNKSIZE_8 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_8
#ifndef CONF_DMAC_BEATSIZE_8
#define CONF_DMAC_BEATSIZE_8 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_8
#ifndef CONF_DMAC_SRC_INTERFACE_8
#define CONF_DMAC_SRC_INTERFACE_8 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_8
#ifndef CONF_DMAC_DES_INTERFACE_8
#define CONF_DMAC_DES_INTERFACE_8 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_8
#ifndef CONF_DMAC_SRCINC_8
#define CONF_DMAC_SRCINC_8 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_8
#ifndef CONF_DMAC_DSTINC_8
#define CONF_DMAC_DSTINC_8 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_8
#ifndef CONF_DMAC_TRANS_TYPE_8
#define CONF_DMAC_TRANS_TYPE_8 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_8
#ifndef CONF_DMAC_TRIGSRC_8
#define CONF_DMAC_TRIGSRC_8 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_8 == 0
#define CONF_DMAC_TYPE_8 0
#define CONF_DMAC_DSYNC_8 0
#elif CONF_DMAC_TRANS_TYPE_8 == 1
#define CONF_DMAC_TYPE_8 1
#define CONF_DMAC_DSYNC_8 0
#elif CONF_DMAC_TRANS_TYPE_8 == 2
#define CONF_DMAC_TYPE_8 1
#define CONF_DMAC_DSYNC_8 1
#endif

#if CONF_DMAC_TRIGSRC_8 == 0xFF
#define CONF_DMAC_SWREQ_8 1
#else
#define CONF_DMAC_SWREQ_8 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_8_SETTINGS == 1 && CONF_DMAC_BEATSIZE_8 != 2 && ((!CONF_DMAC_SRCINC_8) || (!CONF_DMAC_DSTINC_8)))
#if (!CONF_DMAC_SRCINC_8)
#define CONF_DMAC_SRC_STRIDE_8 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_8)
#define CONF_DMAC_DES_STRIDE_8 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_8
#define CONF_DMAC_SRC_STRIDE_8 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_8
#define CONF_DMAC_DES_STRIDE_8 0
#endif

// <e> Channel 9 settings
// <id> dmac_channel_9_settings
#ifndef CONF_DMAC_CHANNEL_9_SETTINGS
#define CONF_DMAC_CHANNEL_9_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_9
#ifndef CONF_DMAC_BURSTSIZE_9
#define CONF_DMAC_BURSTSIZE_9 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_9
#ifndef CONF_DMAC_CHUNKSIZE_9
#define CONF_DMAC_CHUNKSIZE_9 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_9
#ifndef CONF_DMAC_BEATSIZE_9
#define CONF_DMAC_BEATSIZE_9 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_9
#ifndef CONF_DMAC_SRC_INTERFACE_9
#define CONF_DMAC_SRC_INTERFACE_9 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_9
#ifndef CONF_DMAC_DES_INTERFACE_9
#define CONF_DMAC_DES_INTERFACE_9 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_9
#ifndef CONF_DMAC_SRCINC_9
#define CONF_DMAC_SRCINC_9 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_9
#ifndef CONF_DMAC_DSTINC_9
#define CONF_DMAC_DSTINC_9 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_9
#ifndef CONF_DMAC_TRANS_TYPE_9
#define CONF_DMAC_TRANS_TYPE_9 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_9
#ifndef CONF_DMAC_TRIGSRC_9
#define CONF_DMAC_TRIGSRC_9 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_9 == 0
#define CONF_DMAC_TYPE_9 0
#define CONF_DMAC_DSYNC_9 0
#elif CONF_DMAC_TRANS_TYPE_9 == 1
#define CONF_DMAC_TYPE_9 1
#define CONF_DMAC_DSYNC_9 0
#elif CONF_DMAC_TRANS_TYPE_9 == 2
#define CONF_DMAC_TYPE_9 1
#define CONF_DMAC_DSYNC_9 1
#endif

#if CONF_DMAC_TRIGSRC_9 == 0xFF
#define CONF_DMAC_SWREQ_9 1
#else
#define CONF_DMAC_SWREQ_9 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_9_SETTINGS == 1 && CONF_DMAC_BEATSIZE_9 != 2 && ((!CONF_DMAC_SRCINC_9) || (!CONF_DMAC_DSTINC_9)))
#if (!CONF_DMAC_SRCINC_9)
#define CONF_DMAC_SRC_STRIDE_9 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_9)
#define CONF_DMAC_DES_STRIDE_9 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_9
#define CONF_DMAC_SRC_STRIDE_9 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_9
#define CONF_DMAC_DES_STRIDE_9 0
#endif

// <e> Channel 10 settings
// <id> dmac_channel_10_settings
#ifndef CONF_DMAC_CHANNEL_10_SETTINGS
#define CONF_DMAC_CHANNEL_10_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_10
#ifndef CONF_DMAC_BURSTSIZE_10
#define CONF_DMAC_BURSTSIZE_10 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_10
#ifndef CONF_DMAC_CHUNKSIZE_10
#define CONF_DMAC_CHUNKSIZE_10 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_10
#ifndef CONF_DMAC_BEATSIZE_10
#define CONF_DMAC_BEATSIZE_10 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_10
#ifndef CONF_DMAC_SRC_INTERFACE_10
#define CONF_DMAC_SRC_INTERFACE_10 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_10
#ifndef CONF_DMAC_DES_INTERFACE_10
#define CONF_DMAC_DES_INTERFACE_10 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_10
#ifndef CONF_DMAC_SRCINC_10
#define CONF_DMAC_SRCINC_10 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_10
#ifndef CONF_DMAC_DSTINC_10
#define CONF_DMAC_DSTINC_10 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_10
#ifndef CONF_DMAC_TRANS_TYPE_10
#define CONF_DMAC_TRANS_TYPE_10 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_10
#ifndef CONF_DMAC_TRIGSRC_10
#define CONF_DMAC_TRIGSRC_10 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_10 == 0
#define CONF_DMAC_TYPE_10 0
#define CONF_DMAC_DSYNC_10 0
#elif CONF_DMAC_TRANS_TYPE_10 == 1
#define CONF_DMAC_TYPE_10 1
#define CONF_DMAC_DSYNC_10 0
#elif CONF_DMAC_TRANS_TYPE_10 == 2
#define CONF_DMAC_TYPE_10 1
#define CONF_DMAC_DSYNC_10 1
#endif

#if CONF_DMAC_TRIGSRC_10 == 0xFF
#define CONF_DMAC_SWREQ_10 1
#else
#define CONF_DMAC_SWREQ_10 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_10_SETTINGS == 1 && CONF_DMAC_BEATSIZE_10 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_10) || (!CONF_DMAC_DSTINC_10)))
#if (!CONF_DMAC_SRCINC_10)
#define CONF_DMAC_SRC_STRIDE_10 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_10)
#define CONF_DMAC_DES_STRIDE_10 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_10
#define CONF_DMAC_SRC_STRIDE_10 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_10
#define CONF_DMAC_DES_STRIDE_10 0
#endif

// <e> Channel 11 settings
// <id> dmac_channel_11_settings
#ifndef CONF_DMAC_CHANNEL_11_SETTINGS
#define CONF_DMAC_CHANNEL_11_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_11
#ifndef CONF_DMAC_BURSTSIZE_11
#define CONF_DMAC_BURSTSIZE_11 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_11
#ifndef CONF_DMAC_CHUNKSIZE_11
#define CONF_DMAC_CHUNKSIZE_11 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_11
#ifndef CONF_DMAC_BEATSIZE_11
#define CONF_DMAC_BEATSIZE_11 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_11
#ifndef CONF_DMAC_SRC_INTERFACE_11
#define CONF_DMAC_SRC_INTERFACE_11 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_11
#ifndef CONF_DMAC_DES_INTERFACE_11
#define CONF_DMAC_DES_INTERFACE_11 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_11
#ifndef CONF_DMAC_SRCINC_11
#define CONF_DMAC_SRCINC_11 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_11
#ifndef CONF_DMAC_DSTINC_11
#define CONF_DMAC_DSTINC_11 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_11
#ifndef CONF_DMAC_TRANS_TYPE_11
#define CONF_DMAC_TRANS_TYPE_11 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_11
#ifndef CONF_DMAC_TRIGSRC_11
#define CONF_DMAC_TRIGSRC_11 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_11 == 0
#define CONF_DMAC_TYPE_11 0
#define CONF_DMAC_DSYNC_11 0
#elif CONF_DMAC_TRANS_TYPE_11 == 1
#define CONF_DMAC_TYPE_11 1
#define CONF_DMAC_DSYNC_11 0
#elif CONF_DMAC_TRANS_TYPE_11 == 2
#define CONF_DMAC_TYPE_11 1
#define CONF_DMAC_DSYNC_11 1
#endif

#if CONF_DMAC_TRIGSRC_11 == 0xFF
#define CONF_DMAC_SWREQ_11 1
#else
#define CONF_DMAC_SWREQ_11 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_11_SETTINGS == 1 && CONF_DMAC_BEATSIZE_11 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_11) || (!CONF_DMAC_DSTINC_11)))
#if (!CONF_DMAC_SRCINC_11)
#define CONF_DMAC_SRC_STRIDE_11 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_11)
#define CONF_DMAC_DES_STRIDE_11 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_11
#define CONF_DMAC_SRC_STRIDE_11 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_11
#define CONF_DMAC_DES_STRIDE_11 0
#endif

// <e> Channel 12 settings
// <id> dmac_channel_12_settings
#ifndef CONF_DMAC_CHANNEL_12_SETTINGS
#define CONF_DMAC_CHANNEL_12_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_12
#ifndef CONF_DMAC_BURSTSIZE_12
#define CONF_DMAC_BURSTSIZE_12 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_12
#ifndef CONF_DMAC_CHUNKSIZE_12
#define CONF_DMAC_CHUNKSIZE_12 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_12
#ifndef CONF_DMAC_BEATSIZE_12
#define CONF_DMAC_BEATSIZE_12 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_12
#ifndef CONF_DMAC_SRC_INTERFACE_12
#define CONF_DMAC_SRC_INTERFACE_12 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_12
#ifndef CONF_DMAC_DES_INTERFACE_12
#define CONF_DMAC_DES_INTERFACE_12 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_12
#ifndef CONF_DMAC_SRCINC_12
#define CONF_DMAC_SRCINC_12 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_12
#ifndef CONF_DMAC_DSTINC_12
#define CONF_DMAC_DSTINC_12 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_12
#ifndef CONF_DMAC_TRANS_TYPE_12
#define CONF_DMAC_TRANS_TYPE_12 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_12
#ifndef CONF_DMAC_TRIGSRC_12
#define CONF_DMAC_TRIGSRC_12 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_12 == 0
#define CONF_DMAC_TYPE_12 0
#define CONF_DMAC_DSYNC_12 0
#elif CONF_DMAC_TRANS_TYPE_12 == 1
#define CONF_DMAC_TYPE_12 1
#define CONF_DMAC_DSYNC_12 0
#elif CONF_DMAC_TRANS_TYPE_12 == 2
#define CONF_DMAC_TYPE_12 1
#define CONF_DMAC_DSYNC_12 1
#endif

#if CONF_DMAC_TRIGSRC_12 == 0xFF
#define CONF_DMAC_SWREQ_12 1
#else
#define CONF_DMAC_SWREQ_12 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_12_SETTINGS == 1 && CONF_DMAC_BEATSIZE_12 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_12) || (!CONF_DMAC_DSTINC_12)))
#if (!CONF_DMAC_SRCINC_12)
#define CONF_DMAC_SRC_STRIDE_12 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_12)
#define CONF_DMAC_DES_STRIDE_12 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_12
#define CONF_DMAC_SRC_STRIDE_12 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_12
#define CONF_DMAC_DES_STRIDE_12 0
#endif

// <e> Channel 13 settings
// <id> dmac_channel_13_settings
#ifndef CONF_DMAC_CHANNEL_13_SETTINGS
#define CONF_DMAC_CHANNEL_13_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_13
#ifndef CONF_DMAC_BURSTSIZE_13
#define CONF_DMAC_BURSTSIZE_13 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_13
#ifndef CONF_DMAC_CHUNKSIZE_13
#define CONF_DMAC_CHUNKSIZE_13 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_13
#ifndef CONF_DMAC_BEATSIZE_13
#define CONF_DMAC_BEATSIZE_13 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_13
#ifndef CONF_DMAC_SRC_INTERFACE_13
#define CONF_DMAC_SRC_INTERFACE_13 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_13
#ifndef CONF_DMAC_DES_INTERFACE_13
#define CONF_DMAC_DES_INTERFACE_13 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_13
#ifndef CONF_DMAC_SRCINC_13
#define CONF_DMAC_SRCINC_13 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_13
#ifndef CONF_DMAC_DSTINC_13
#define CONF_DMAC_DSTINC_13 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_13
#ifndef CONF_DMAC_TRANS_TYPE_13
#define CONF_DMAC_TRANS_TYPE_13 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_13
#ifndef CONF_DMAC_TRIGSRC_13
#define CONF_DMAC_TRIGSRC_13 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_13 == 0
#define CONF_DMAC_TYPE_13 0
#define CONF_DMAC_DSYNC_13 0
#elif CONF_DMAC_TRANS_TYPE_13 == 1
#define CONF_DMAC_TYPE_13 1
#define CONF_DMAC_DSYNC_13 0
#elif CONF_DMAC_TRANS_TYPE_13 == 2
#define CONF_DMAC_TYPE_13 1
#define CONF_DMAC_DSYNC_13 1
#endif

#if CONF_DMAC_TRIGSRC_13 == 0xFF
#define CONF_DMAC_SWREQ_13 1
#else
#define CONF_DMAC_SWREQ_13 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_13_SETTINGS == 1 && CONF_DMAC_BEATSIZE_13 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_13) || (!CONF_DMAC_DSTINC_13)))
#if (!CONF_DMAC_SRCINC_13)
#define CONF_DMAC_SRC_STRIDE_13 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_13)
#define CONF_DMAC_DES_STRIDE_13 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_13
#define CONF_DMAC_SRC_STRIDE_13 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_13
#define CONF_DMAC_DES_STRIDE_13 0
#endif

// <e> Channel 14 settings
// <id> dmac_channel_14_settings
#ifndef CONF_DMAC_CHANNEL_14_SETTINGS
#define CONF_DMAC_CHANNEL_14_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_14
#ifndef CONF_DMAC_BURSTSIZE_14
#define CONF_DMAC_BURSTSIZE_14 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_14
#ifndef CONF_DMAC_CHUNKSIZE_14
#define CONF_DMAC_CHUNKSIZE_14 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_14
#ifndef CONF_DMAC_BEATSIZE_14
#define CONF_DMAC_BEATSIZE_14 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_14
#ifndef CONF_DMAC_SRC_INTERFACE_14
#define CONF_DMAC_SRC_INTERFACE_14 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_14
#ifndef CONF_DMAC_DES_INTERFACE_14
#define CONF_DMAC_DES_INTERFACE_14 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_14
#ifndef CONF_DMAC_SRCINC_14
#define CONF_DMAC_SRCINC_14 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_14
#ifndef CONF_DMAC_DSTINC_14
#define CONF_DMAC_DSTINC_14 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_14
#ifndef CONF_DMAC_TRANS_TYPE_14
#define CONF_DMAC_TRANS_TYPE_14 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_14
#ifndef CONF_DMAC_TRIGSRC_14
#define CONF_DMAC_TRIGSRC_14 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_14 == 0
#define CONF_DMAC_TYPE_14 0
#define CONF_DMAC_DSYNC_14 0
#elif CONF_DMAC_TRANS_TYPE_14 == 1
#define CONF_DMAC_TYPE_14 1
#define CONF_DMAC_DSYNC_14 0
#elif CONF_DMAC_TRANS_TYPE_14 == 2
#define CONF_DMAC_TYPE_14 1
#define CONF_DMAC_DSYNC_14 1
#endif

#if CONF_DMAC_TRIGSRC_14 == 0xFF
#define CONF_DMAC_SWREQ_14 1
#else
#define CONF_DMAC_SWREQ_14 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_14_SETTINGS == 1 && CONF_DMAC_BEATSIZE_14 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_14) || (!CONF_DMAC_DSTINC_14)))
#if (!CONF_DMAC_SRCINC_14)
#define CONF_DMAC_SRC_STRIDE_14 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_14)
#define CONF_DMAC_DES_STRIDE_14 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_14
#define CONF_DMAC_SRC_STRIDE_14 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_14
#define CONF_DMAC_DES_STRIDE_14 0
#endif

// <e> Channel 15 settings
// <id> dmac_channel_15_settings
#ifndef CONF_DMAC_CHANNEL_15_SETTINGS
#define CONF_DMAC_CHANNEL_15_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_15
#ifndef CONF_DMAC_BURSTSIZE_15
#define CONF_DMAC_BURSTSIZE_15 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_15
#ifndef CONF_DMAC_CHUNKSIZE_15
#define CONF_DMAC_CHUNKSIZE_15 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_15
#ifndef CONF_DMAC_BEATSIZE_15
#define CONF_DMAC_BEATSIZE_15 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_15
#ifndef CONF_DMAC_SRC_INTERFACE_15
#define CONF_DMAC_SRC_INTERFACE_15 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_15
#ifndef CONF_DMAC_DES_INTERFACE_15
#define CONF_DMAC_DES_INTERFACE_15 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_15
#ifndef CONF_DMAC_SRCINC_15
#define CONF_DMAC_SRCINC_15 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_15
#ifndef CONF_DMAC_DSTINC_15
#define CONF_DMAC_DSTINC_15 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_15
#ifndef CONF_DMAC_TRANS_TYPE_15
#define CONF_DMAC_TRANS_TYPE_15 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_15
#ifndef CONF_DMAC_TRIGSRC_15
#define CONF_DMAC_TRIGSRC_15 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_15 == 0
#define CONF_DMAC_TYPE_15 0
#define CONF_DMAC_DSYNC_15 0
#elif CONF_DMAC_TRANS_TYPE_15 == 1
#define CONF_DMAC_TYPE_15 1
#define CONF_DMAC_DSYNC_15 0
#elif CONF_DMAC_TRANS_TYPE_15 == 2
#define CONF_DMAC_TYPE_15 1
#define CONF_DMAC_DSYNC_15 1
#endif

#if CONF_DMAC_TRIGSRC_15 == 0xFF
#define CONF_DMAC_SWREQ_15 1
#else
#define CONF_DMAC_SWREQ_15 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_15_SETTINGS == 1 && CONF_DMAC_BEATSIZE_15 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_15) || (!CONF_DMAC_DSTINC_15)))
#if (!CONF_DMAC_SRCINC_15)
#define CONF_DMAC_SRC_STRIDE_15 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_15)
#define CONF_DMAC_DES_STRIDE_15 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_15
#define CONF_DMAC_SRC_STRIDE_15 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_15
#define CONF_DMAC_DES_STRIDE_15 0
#endif

// <e> Channel 16 settings
// <id> dmac_channel_16_settings
#ifndef CONF_DMAC_CHANNEL_16_SETTINGS
#define CONF_DMAC_CHANNEL_16_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_16
#ifndef CONF_DMAC_BURSTSIZE_16
#define CONF_DMAC_BURSTSIZE_16 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_16
#ifndef CONF_DMAC_CHUNKSIZE_16
#define CONF_DMAC_CHUNKSIZE_16 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_16
#ifndef CONF_DMAC_BEATSIZE_16
#define CONF_DMAC_BEATSIZE_16 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_16
#ifndef CONF_DMAC_SRC_INTERFACE_16
#define CONF_DMAC_SRC_INTERFACE_16 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_16
#ifndef CONF_DMAC_DES_INTERFACE_16
#define CONF_DMAC_DES_INTERFACE_16 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_16
#ifndef CONF_DMAC_SRCINC_16
#define CONF_DMAC_SRCINC_16 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_16
#ifndef CONF_DMAC_DSTINC_16
#define CONF_DMAC_DSTINC_16 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_16
#ifndef CONF_DMAC_TRANS_TYPE_16
#define CONF_DMAC_TRANS_TYPE_16 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_16
#ifndef CONF_DMAC_TRIGSRC_16
#define CONF_DMAC_TRIGSRC_16 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_16 == 0
#define CONF_DMAC_TYPE_16 0
#define CONF_DMAC_DSYNC_16 0
#elif CONF_DMAC_TRANS_TYPE_16 == 1
#define CONF_DMAC_TYPE_16 1
#define CONF_DMAC_DSYNC_16 0
#elif CONF_DMAC_TRANS_TYPE_16 == 2
#define CONF_DMAC_TYPE_16 1
#define CONF_DMAC_DSYNC_16 1
#endif

#if CONF_DMAC_TRIGSRC_16 == 0xFF
#define CONF_DMAC_SWREQ_16 1
#else
#define CONF_DMAC_SWREQ_16 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_16_SETTINGS == 1 && CONF_DMAC_BEATSIZE_16 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_16) || (!CONF_DMAC_DSTINC_16)))
#if (!CONF_DMAC_SRCINC_16)
#define CONF_DMAC_SRC_STRIDE_16 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_16)
#define CONF_DMAC_DES_STRIDE_16 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_16
#define CONF_DMAC_SRC_STRIDE_16 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_16
#define CONF_DMAC_DES_STRIDE_16 0
#endif

// <e> Channel 17 settings
// <id> dmac_channel_17_settings
#ifndef CONF_DMAC_CHANNEL_17_SETTINGS
#define CONF_DMAC_CHANNEL_17_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_17
#ifndef CONF_DMAC_BURSTSIZE_17
#define CONF_DMAC_BURSTSIZE_17 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_17
#ifndef CONF_DMAC_CHUNKSIZE_17
#define CONF_DMAC_CHUNKSIZE_17 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_17
#ifndef CONF_DMAC_BEATSIZE_17
#define CONF_DMAC_BEATSIZE_17 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_17
#ifndef CONF_DMAC_SRC_INTERFACE_17
#define CONF_DMAC_SRC_INTERFACE_17 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_17
#ifndef CONF_DMAC_DES_INTERFACE_17
#define CONF_DMAC_DES_INTERFACE_17 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_17
#ifndef CONF_DMAC_SRCINC_17
#define CONF_DMAC_SRCINC_17 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_17
#ifndef CONF_DMAC_DSTINC_17
#define CONF_DMAC_DSTINC_17 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_17
#ifndef CONF_DMAC_TRANS_TYPE_17
#define CONF_DMAC_TRANS_TYPE_17 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_17
#ifndef CONF_DMAC_TRIGSRC_17
#define CONF_DMAC_TRIGSRC_17 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_17 == 0
#define CONF_DMAC_TYPE_17 0
#define CONF_DMAC_DSYNC_17 0
#elif CONF_DMAC_TRANS_TYPE_17 == 1
#define CONF_DMAC_TYPE_17 1
#define CONF_DMAC_DSYNC_17 0
#elif CONF_DMAC_TRANS_TYPE_17 == 2
#define CONF_DMAC_TYPE_17 1
#define CONF_DMAC_DSYNC_17 1
#endif

#if CONF_DMAC_TRIGSRC_17 == 0xFF
#define CONF_DMAC_SWREQ_17 1
#else
#define CONF_DMAC_SWREQ_17 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_17_SETTINGS == 1 && CONF_DMAC_BEATSIZE_17 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_17) || (!CONF_DMAC_DSTINC_17)))
#if (!CONF_DMAC_SRCINC_17)
#define CONF_DMAC_SRC_STRIDE_17 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_17)
#define CONF_DMAC_DES_STRIDE_17 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_17
#define CONF_DMAC_SRC_STRIDE_17 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_17
#define CONF_DMAC_DES_STRIDE_17 0
#endif

// <e> Channel 18 settings
// <id> dmac_channel_18_settings
#ifndef CONF_DMAC_CHANNEL_18_SETTINGS
#define CONF_DMAC_CHANNEL_18_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_18
#ifndef CONF_DMAC_BURSTSIZE_18
#define CONF_DMAC_BURSTSIZE_18 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_18
#ifndef CONF_DMAC_CHUNKSIZE_18
#define CONF_DMAC_CHUNKSIZE_18 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_18
#ifndef CONF_DMAC_BEATSIZE_18
#define CONF_DMAC_BEATSIZE_18 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_18
#ifndef CONF_DMAC_SRC_INTERFACE_18
#define CONF_DMAC_SRC_INTERFACE_18 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_18
#ifndef CONF_DMAC_DES_INTERFACE_18
#define CONF_DMAC_DES_INTERFACE_18 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_18
#ifndef CONF_DMAC_SRCINC_18
#define CONF_DMAC_SRCINC_18 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_18
#ifndef CONF_DMAC_DSTINC_18
#define CONF_DMAC_DSTINC_18 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_18
#ifndef CONF_DMAC_TRANS_TYPE_18
#define CONF_DMAC_TRANS_TYPE_18 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_18
#ifndef CONF_DMAC_TRIGSRC_18
#define CONF_DMAC_TRIGSRC_18 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_18 == 0
#define CONF_DMAC_TYPE_18 0
#define CONF_DMAC_DSYNC_18 0
#elif CONF_DMAC_TRANS_TYPE_18 == 1
#define CONF_DMAC_TYPE_18 1
#define CONF_DMAC_DSYNC_18 0
#elif CONF_DMAC_TRANS_TYPE_18 == 2
#define CONF_DMAC_TYPE_18 1
#define CONF_DMAC_DSYNC_18 1
#endif

#if CONF_DMAC_TRIGSRC_18 == 0xFF
#define CONF_DMAC_SWREQ_18 1
#else
#define CONF_DMAC_SWREQ_18 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_18_SETTINGS == 1 && CONF_DMAC_BEATSIZE_18 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_18) || (!CONF_DMAC_DSTINC_18)))
#if (!CONF_DMAC_SRCINC_18)
#define CONF_DMAC_SRC_STRIDE_18 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_18)
#define CONF_DMAC_DES_STRIDE_18 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_18
#define CONF_DMAC_SRC_STRIDE_18 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_18
#define CONF_DMAC_DES_STRIDE_18 0
#endif

// <e> Channel 19 settings
// <id> dmac_channel_19_settings
#ifndef CONF_DMAC_CHANNEL_19_SETTINGS
#define CONF_DMAC_CHANNEL_19_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_19
#ifndef CONF_DMAC_BURSTSIZE_19
#define CONF_DMAC_BURSTSIZE_19 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_19
#ifndef CONF_DMAC_CHUNKSIZE_19
#define CONF_DMAC_CHUNKSIZE_19 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_19
#ifndef CONF_DMAC_BEATSIZE_19
#define CONF_DMAC_BEATSIZE_19 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_19
#ifndef CONF_DMAC_SRC_INTERFACE_19
#define CONF_DMAC_SRC_INTERFACE_19 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_19
#ifndef CONF_DMAC_DES_INTERFACE_19
#define CONF_DMAC_DES_INTERFACE_19 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_19
#ifndef CONF_DMAC_SRCINC_19
#define CONF_DMAC_SRCINC_19 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_19
#ifndef CONF_DMAC_DSTINC_19
#define CONF_DMAC_DSTINC_19 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_19
#ifndef CONF_DMAC_TRANS_TYPE_19
#define CONF_DMAC_TRANS_TYPE_19 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_19
#ifndef CONF_DMAC_TRIGSRC_19
#define CONF_DMAC_TRIGSRC_19 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_19 == 0
#define CONF_DMAC_TYPE_19 0
#define CONF_DMAC_DSYNC_19 0
#elif CONF_DMAC_TRANS_TYPE_19 == 1
#define CONF_DMAC_TYPE_19 1
#define CONF_DMAC_DSYNC_19 0
#elif CONF_DMAC_TRANS_TYPE_19 == 2
#define CONF_DMAC_TYPE_19 1
#define CONF_DMAC_DSYNC_19 1
#endif

#if CONF_DMAC_TRIGSRC_19 == 0xFF
#define CONF_DMAC_SWREQ_19 1
#else
#define CONF_DMAC_SWREQ_19 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_19_SETTINGS == 1 && CONF_DMAC_BEATSIZE_19 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_19) || (!CONF_DMAC_DSTINC_19)))
#if (!CONF_DMAC_SRCINC_19)
#define CONF_DMAC_SRC_STRIDE_19 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_19)
#define CONF_DMAC_DES_STRIDE_19 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_19
#define CONF_DMAC_SRC_STRIDE_19 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_19
#define CONF_DMAC_DES_STRIDE_19 0
#endif

// <e> Channel 20 settings
// <id> dmac_channel_20_settings
#ifndef CONF_DMAC_CHANNEL_20_SETTINGS
#define CONF_DMAC_CHANNEL_20_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_20
#ifndef CONF_DMAC_BURSTSIZE_20
#define CONF_DMAC_BURSTSIZE_20 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_20
#ifndef CONF_DMAC_CHUNKSIZE_20
#define CONF_DMAC_CHUNKSIZE_20 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_20
#ifndef CONF_DMAC_BEATSIZE_20
#define CONF_DMAC_BEATSIZE_20 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_20
#ifndef CONF_DMAC_SRC_INTERFACE_20
#define CONF_DMAC_SRC_INTERFACE_20 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_20
#ifndef CONF_DMAC_DES_INTERFACE_20
#define CONF_DMAC_DES_INTERFACE_20 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_20
#ifndef CONF_DMAC_SRCINC_20
#define CONF_DMAC_SRCINC_20 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_20
#ifndef CONF_DMAC_DSTINC_20
#define CONF_DMAC_DSTINC_20 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_20
#ifndef CONF_DMAC_TRANS_TYPE_20
#define CONF_DMAC_TRANS_TYPE_20 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_20
#ifndef CONF_DMAC_TRIGSRC_20
#define CONF_DMAC_TRIGSRC_20 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_20 == 0
#define CONF_DMAC_TYPE_20 0
#define CONF_DMAC_DSYNC_20 0
#elif CONF_DMAC_TRANS_TYPE_20 == 1
#define CONF_DMAC_TYPE_20 1
#define CONF_DMAC_DSYNC_20 0
#elif CONF_DMAC_TRANS_TYPE_20 == 2
#define CONF_DMAC_TYPE_20 1
#define CONF_DMAC_DSYNC_20 1
#endif

#if CONF_DMAC_TRIGSRC_20 == 0xFF
#define CONF_DMAC_SWREQ_20 1
#else
#define CONF_DMAC_SWREQ_20 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_20_SETTINGS == 1 && CONF_DMAC_BEATSIZE_20 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_20) || (!CONF_DMAC_DSTINC_20)))
#if (!CONF_DMAC_SRCINC_20)
#define CONF_DMAC_SRC_STRIDE_20 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_20)
#define CONF_DMAC_DES_STRIDE_20 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_20
#define CONF_DMAC_SRC_STRIDE_20 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_20
#define CONF_DMAC_DES_STRIDE_20 0
#endif

// <e> Channel 21 settings
// <id> dmac_channel_21_settings
#ifndef CONF_DMAC_CHANNEL_21_SETTINGS
#define CONF_DMAC_CHANNEL_21_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_21
#ifndef CONF_DMAC_BURSTSIZE_21
#define CONF_DMAC_BURSTSIZE_21 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_21
#ifndef CONF_DMAC_CHUNKSIZE_21
#define CONF_DMAC_CHUNKSIZE_21 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_21
#ifndef CONF_DMAC_BEATSIZE_21
#define CONF_DMAC_BEATSIZE_21 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_21
#ifndef CONF_DMAC_SRC_INTERFACE_21
#define CONF_DMAC_SRC_INTERFACE_21 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_21
#ifndef CONF_DMAC_DES_INTERFACE_21
#define CONF_DMAC_DES_INTERFACE_21 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_21
#ifndef CONF_DMAC_SRCINC_21
#define CONF_DMAC_SRCINC_21 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_21
#ifndef CONF_DMAC_DSTINC_21
#define CONF_DMAC_DSTINC_21 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_21
#ifndef CONF_DMAC_TRANS_TYPE_21
#define CONF_DMAC_TRANS_TYPE_21 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_21
#ifndef CONF_DMAC_TRIGSRC_21
#define CONF_DMAC_TRIGSRC_21 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_21 == 0
#define CONF_DMAC_TYPE_21 0
#define CONF_DMAC_DSYNC_21 0
#elif CONF_DMAC_TRANS_TYPE_21 == 1
#define CONF_DMAC_TYPE_21 1
#define CONF_DMAC_DSYNC_21 0
#elif CONF_DMAC_TRANS_TYPE_21 == 2
#define CONF_DMAC_TYPE_21 1
#define CONF_DMAC_DSYNC_21 1
#endif

#if CONF_DMAC_TRIGSRC_21 == 0xFF
#define CONF_DMAC_SWREQ_21 1
#else
#define CONF_DMAC_SWREQ_21 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_21_SETTINGS == 1 && CONF_DMAC_BEATSIZE_21 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_21) || (!CONF_DMAC_DSTINC_21)))
#if (!CONF_DMAC_SRCINC_21)
#define CONF_DMAC_SRC_STRIDE_21 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_21)
#define CONF_DMAC_DES_STRIDE_21 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_21
#define CONF_DMAC_SRC_STRIDE_21 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_21
#define CONF_DMAC_DES_STRIDE_21 0
#endif

// <e> Channel 22 settings
// <id> dmac_channel_22_settings
#ifndef CONF_DMAC_CHANNEL_22_SETTINGS
#define CONF_DMAC_CHANNEL_22_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_22
#ifndef CONF_DMAC_BURSTSIZE_22
#define CONF_DMAC_BURSTSIZE_22 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_22
#ifndef CONF_DMAC_CHUNKSIZE_22
#define CONF_DMAC_CHUNKSIZE_22 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_22
#ifndef CONF_DMAC_BEATSIZE_22
#define CONF_DMAC_BEATSIZE_22 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_22
#ifndef CONF_DMAC_SRC_INTERFACE_22
#define CONF_DMAC_SRC_INTERFACE_22 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_22
#ifndef CONF_DMAC_DES_INTERFACE_22
#define CONF_DMAC_DES_INTERFACE_22 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_22
#ifndef CONF_DMAC_SRCINC_22
#define CONF_DMAC_SRCINC_22 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_22
#ifndef CONF_DMAC_DSTINC_22
#define CONF_DMAC_DSTINC_22 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_22
#ifndef CONF_DMAC_TRANS_TYPE_22
#define CONF_DMAC_TRANS_TYPE_22 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_22
#ifndef CONF_DMAC_TRIGSRC_22
#define CONF_DMAC_TRIGSRC_22 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_22 == 0
#define CONF_DMAC_TYPE_22 0
#define CONF_DMAC_DSYNC_22 0
#elif CONF_DMAC_TRANS_TYPE_22 == 1
#define CONF_DMAC_TYPE_22 1
#define CONF_DMAC_DSYNC_22 0
#elif CONF_DMAC_TRANS_TYPE_22 == 2
#define CONF_DMAC_TYPE_22 1
#define CONF_DMAC_DSYNC_22 1
#endif

#if CONF_DMAC_TRIGSRC_22 == 0xFF
#define CONF_DMAC_SWREQ_22 1
#else
#define CONF_DMAC_SWREQ_22 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_22_SETTINGS == 1 && CONF_DMAC_BEATSIZE_22 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_22) || (!CONF_DMAC_DSTINC_22)))
#if (!CONF_DMAC_SRCINC_22)
#define CONF_DMAC_SRC_STRIDE_22 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_22)
#define CONF_DMAC_DES_STRIDE_22 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_22
#define CONF_DMAC_SRC_STRIDE_22 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_22
#define CONF_DMAC_DES_STRIDE_22 0
#endif

// <e> Channel 23 settings
// <id> dmac_channel_23_settings
#ifndef CONF_DMAC_CHANNEL_23_SETTINGS
#define CONF_DMAC_CHANNEL_23_SETTINGS 0
#endif

// <o> Burst Size
// <0x0=> 1 burst size
// <0x1=> 4 burst size
// <0x2=> 8 burst size
// <0x3=> 16 burst size
// <i> Define the memory burst size
// <id> dmac_burstsize_23
#ifndef CONF_DMAC_BURSTSIZE_23
#define CONF_DMAC_BURSTSIZE_23 0x0
#endif

// <o> Chunk Size
// <0x0=> 1 data transferred
// <0x1=> 2 data transferred
// <0x2=> 4 data transferred
// <0x3=> 8 data transferred
// <0x4=> 16 data transferred
// <i> Define the peripheral chunk size
// <id> dmac_chunksize_23
#ifndef CONF_DMAC_CHUNKSIZE_23
#define CONF_DMAC_CHUNKSIZE_23 0x0
#endif

// <o> Beat Size
// <0=> 8-bit bus transfer
// <1=> 16-bit bus transfer
// <2=> 32-bit bus transfer
// <i> Defines the size of one beat
// <id> dmac_beatsize_23
#ifndef CONF_DMAC_BEATSIZE_23
#define CONF_DMAC_BEATSIZE_23 0x0
#endif

// <o> Source Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is read through the system bus interface 0 or 1
// <id> dma_src_interface_23
#ifndef CONF_DMAC_SRC_INTERFACE_23
#define CONF_DMAC_SRC_INTERFACE_23 0x0
#endif

// <o> Destination Interface Identifier
// <0x0=> AHB_IF0
// <0x1=> AHB_IF1
// <i> Define the data is written through the system bus interface 0 or 1
// <id> dma_des_interface_23
#ifndef CONF_DMAC_DES_INTERFACE_23
#define CONF_DMAC_DES_INTERFACE_23 0x0
#endif

// <q> Source Address Increment
// <i> Indicates whether the source address incremented as beat size or not
// <id> dmac_srcinc_23
#ifndef CONF_DMAC_SRCINC_23
#define CONF_DMAC_SRCINC_23 0
#endif

// <q> Destination Address Increment
// <i> Indicates whether the destination address incremented as beat size or not
// <id> dmac_dstinc_23
#ifndef CONF_DMAC_DSTINC_23
#define CONF_DMAC_DSTINC_23 0
#endif

// <o> Transfer Type
// <0x0=> Memory to Memory Transfer
// <0x1=> Peripheral to Memory Transfer
// <0x2=> Memory to Peripheral Transfer
// <i> Define the data transfer type
// <id> dma_trans_type_23
#ifndef CONF_DMAC_TRANS_TYPE_23
#define CONF_DMAC_TRANS_TYPE_23 0x0
#endif

// <o> Trigger source
// <0xFF=> Software Trigger
// <0x00=> HSMCI TX/RX Trigger
// <0x01=> SPI0 TX Trigger
// <0x02=> SPI0 RX Trigger
// <0x03=> SPI1 TX Trigger
// <0x04=> SPI1 RX Trigger
// <0x05=> QSPI TX Trigger
// <0x06=> QSPI RX Trigger
// <0x07=> USART0 TX Trigger
// <0x08=> USART0 RX Trigger
// <0x09=> USART1 TX Trigger
// <0x0A=> USART1 RX Trigger
// <0x0B=> USART2 TX Trigger
// <0x0C=> USART2 RX Trigger
// <0x0D=> PWM0 TX Trigger
// <0x0E=> TWIHS0 TX Trigger
// <0x0F=> TWIHS0 RX Trigger
// <0x10=> TWIHS1 TX Trigger
// <0x11=> TWIHS1 RX Trigger
// <0x12=> TWIHS2 TX Trigger
// <0x13=> TWIHS2 RX Trigger
// <0x14=> UART0 TX Trigger
// <0x15=> UART0 RX Trigger
// <0x16=> UART1 TX Trigger
// <0x17=> UART1 RX Trigger
// <0x18=> UART2 TX Trigger
// <0x19=> UART2 RX Trigger
// <0x1A=> UART3 TX Trigger
// <0x1B=> UART3 RX Trigger
// <0x1C=> UART4 TX Trigger
// <0x1D=> UART4 RX Trigger
// <0x1E=> DACC TX Trigger
// <0x20=> SSC TX Trigger
// <0x21=> SSC RX Trigger
// <0x22=> PIOA RX Trigger
// <0x23=> AFEC0 RX Trigger
// <0x24=> AFEC1 RX Trigger
// <0x25=> AES TX Trigger
// <0x26=> AES RX Trigger
// <0x27=> PWM1 TX Trigger
// <0x28=> TC0 RX Trigger
// <0x29=> TC3 RX Trigger
// <0x2A=> TC6 RX Trigger
// <0x2B=> TC9 RX Trigger
// <0x2C=> I2SC0 TX Left Trigger
// <0x2D=> I2SC0 RX Left Trigger
// <0x2E=> I2SC1 TX Left Trigger
// <0x2F=> I2SC1 RX Left Trigger
// <0x30=> I2SC0 TX Right Trigger
// <0x31=> I2SC0 RX Right Trigger
// <0x32=> I2SC1 TX Right Trigger
// <0x33=> I2SC1 RX Right Trigger
// <i> Define the DMA trigger source
// <id> dmac_trifsrc_23
#ifndef CONF_DMAC_TRIGSRC_23
#define CONF_DMAC_TRIGSRC_23 0xff
#endif

// </e>

#if CONF_DMAC_TRANS_TYPE_23 == 0
#define CONF_DMAC_TYPE_23 0
#define CONF_DMAC_DSYNC_23 0
#elif CONF_DMAC_TRANS_TYPE_23 == 1
#define CONF_DMAC_TYPE_23 1
#define CONF_DMAC_DSYNC_23 0
#elif CONF_DMAC_TRANS_TYPE_23 == 2
#define CONF_DMAC_TYPE_23 1
#define CONF_DMAC_DSYNC_23 1
#endif

#if CONF_DMAC_TRIGSRC_23 == 0xFF
#define CONF_DMAC_SWREQ_23 1
#else
#define CONF_DMAC_SWREQ_23 0
#endif

/* Errata: If XDMA is used to transfer 8-bit or 16-bit data in fixed source address
 * or fixed destination address mode, source and destination addresses are incremented
 * by 8-bit or 16-bit.
 * Workaround: The user can fix the problem by setting the source addressing mode to
 * use microblock and data striding with microblock stride set to 0 and data stride set to -1.
 */
#if (CONF_DMAC_CHANNEL_23_SETTINGS == 1 && CONF_DMAC_BEATSIZE_23 != 2                                                  \
     && ((!CONF_DMAC_SRCINC_23) || (!CONF_DMAC_DSTINC_23)))
#if (!CONF_DMAC_SRCINC_23)
#define CONF_DMAC_SRC_STRIDE_23 ((int16_t)(-1))
#endif
#if (!CONF_DMAC_DSTINC_23)
#define CONF_DMAC_DES_STRIDE_23 ((int16_t)(-1))
#endif
#endif

#ifndef CONF_DMAC_SRC_STRIDE_23
#define CONF_DMAC_SRC_STRIDE_23 0
#endif

#ifndef CONF_DMAC_DES_STRIDE_23
#define CONF_DMAC_DES_STRIDE_23 0
#endif

// </e>

// <<< end of configuration section >>>

#endif // HPL_XDMAC_CONFIG_H
