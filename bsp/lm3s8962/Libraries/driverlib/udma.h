//*****************************************************************************
//
// udma.h - Prototypes and macros for the uDMA controller.
//
// Copyright (c) 2007-2010 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 6459 of the Stellaris Peripheral Driver Library.
//
//*****************************************************************************

#ifndef __UDMA_H__
#define __UDMA_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// A structure that defines an entry in the channel control table.  These
// fields are used by the uDMA controller and normally it is not necessary for
// software to directly read or write fields in the table.
//
//*****************************************************************************
typedef struct
{
    //
    // The ending source address of the data transfer.
    //
    volatile void *pvSrcEndAddr;

    //
    // The ending destination address of the data transfer.
    //
    volatile void *pvDstEndAddr;

    //
    // The channel control mode.
    //
    volatile unsigned long ulControl;

    //
    // An unused location.
    //
    volatile unsigned long ulSpare;
}
tDMAControlTable;

//*****************************************************************************
//
// Flags that can be passed to uDMAChannelAttributeEnable(),
// uDMAChannelAttributeDisable(), and returned from uDMAChannelAttributeGet().
//
//*****************************************************************************
#define UDMA_ATTR_USEBURST      0x00000001
#define UDMA_ATTR_ALTSELECT     0x00000002
#define UDMA_ATTR_HIGH_PRIORITY 0x00000004
#define UDMA_ATTR_REQMASK       0x00000008
#define UDMA_ATTR_ALL           0x0000000F

//*****************************************************************************
//
// DMA control modes that can be passed to uDMAModeSet() and returned
// uDMAModeGet().
//
//*****************************************************************************
#define UDMA_MODE_STOP          0x00000000
#define UDMA_MODE_BASIC         0x00000001
#define UDMA_MODE_AUTO          0x00000002
#define UDMA_MODE_PINGPONG      0x00000003
#define UDMA_MODE_MEM_SCATTER_GATHER                                          \
                                0x00000004
#define UDMA_MODE_PER_SCATTER_GATHER                                          \
                                0x00000006
#define UDMA_MODE_ALT_SELECT    0x00000001

//*****************************************************************************
//
// Channel configuration values that can be passed to uDMAControlSet().
//
//*****************************************************************************
#define UDMA_DST_INC_8          0x00000000
#define UDMA_DST_INC_16         0x40000000
#define UDMA_DST_INC_32         0x80000000
#define UDMA_DST_INC_NONE       0xc0000000
#define UDMA_SRC_INC_8          0x00000000
#define UDMA_SRC_INC_16         0x04000000
#define UDMA_SRC_INC_32         0x08000000
#define UDMA_SRC_INC_NONE       0x0c000000
#define UDMA_SIZE_8             0x00000000
#define UDMA_SIZE_16            0x11000000
#define UDMA_SIZE_32            0x22000000
#define UDMA_ARB_1              0x00000000
#define UDMA_ARB_2              0x00004000
#define UDMA_ARB_4              0x00008000
#define UDMA_ARB_8              0x0000c000
#define UDMA_ARB_16             0x00010000
#define UDMA_ARB_32             0x00014000
#define UDMA_ARB_64             0x00018000
#define UDMA_ARB_128            0x0001c000
#define UDMA_ARB_256            0x00020000
#define UDMA_ARB_512            0x00024000
#define UDMA_ARB_1024           0x00028000
#define UDMA_NEXT_USEBURST      0x00000008

//*****************************************************************************
//
// Channel numbers to be passed to API functions that require a channel number
// ID.
//
//*****************************************************************************
#define UDMA_CHANNEL_USBEP1RX   0
#define UDMA_CHANNEL_USBEP1TX   1
#define UDMA_CHANNEL_USBEP2RX   2
#define UDMA_CHANNEL_USBEP2TX   3
#define UDMA_CHANNEL_USBEP3RX   4
#define UDMA_CHANNEL_USBEP3TX   5
#define UDMA_CHANNEL_ETH0RX     6
#define UDMA_CHANNEL_ETH0TX     7
#define UDMA_CHANNEL_UART0RX    8
#define UDMA_CHANNEL_UART0TX    9
#define UDMA_CHANNEL_SSI0RX     10
#define UDMA_CHANNEL_SSI0TX     11
#define UDMA_CHANNEL_ADC0       14
#define UDMA_CHANNEL_ADC1       15
#define UDMA_CHANNEL_ADC2       16
#define UDMA_CHANNEL_ADC3       17
#define UDMA_CHANNEL_TMR0A      18
#define UDMA_CHANNEL_TMR0B      19
#define UDMA_CHANNEL_TMR1A      20
#define UDMA_CHANNEL_TMR1B      21
#define UDMA_CHANNEL_UART1RX    22
#define UDMA_CHANNEL_UART1TX    23
#define UDMA_CHANNEL_SSI1RX     24
#define UDMA_CHANNEL_SSI1TX     25
#define UDMA_CHANNEL_I2S0RX     28
#define UDMA_CHANNEL_I2S0TX     29
#define UDMA_CHANNEL_SW         30

//*****************************************************************************
//
// Flags to be OR'd with the channel ID to indicate if the primary or alternate
// control structure should be used.
//
//*****************************************************************************
#define UDMA_PRI_SELECT         0x00000000
#define UDMA_ALT_SELECT         0x00000020

//*****************************************************************************
//
// uDMA interrupt sources, to be passed to uDMAIntRegister() and
// uDMAIntUnregister().
//
//*****************************************************************************
#define UDMA_INT_SW             62
#define UDMA_INT_ERR            63

//*****************************************************************************
//
// Channel numbers to be passed to API functions that require a channel number
// ID.  These are for secondary peripheral assignments.
//
//*****************************************************************************
#define UDMA_SEC_CHANNEL_UART2RX_0                                            \
                                0
#define UDMA_SEC_CHANNEL_UART2TX_1                                            \
                                1
#define UDMA_SEC_CHANNEL_TMR3A  2
#define UDMA_SEC_CHANNEL_TMR3B  3
#define UDMA_SEC_CHANNEL_TMR2A_4                                              \
                                4
#define UDMA_SEC_CHANNEL_TMR2B_5                                              \
                                5
#define UDMA_SEC_CHANNEL_TMR2A_6                                              \
                                6
#define UDMA_SEC_CHANNEL_TMR2B_7                                              \
                                7
#define UDMA_SEC_CHANNEL_UART1RX                                              \
                                8
#define UDMA_SEC_CHANNEL_UART1TX                                              \
                                9
#define UDMA_SEC_CHANNEL_SSI1RX 10
#define UDMA_SEC_CHANNEL_SSI1TX 11
#define UDMA_SEC_CHANNEL_UART2RX_12                                           \
                                12
#define UDMA_SEC_CHANNEL_UART2TX_13                                           \
                                13
#define UDMA_SEC_CHANNEL_TMR2A_14                                             \
                                14
#define UDMA_SEC_CHANNEL_TMR2B_15                                             \
                                15
#define UDMA_SEC_CHANNEL_TMR1A  18
#define UDMA_SEC_CHANNEL_TMR1B  19
#define UDMA_SEC_CHANNEL_EPI0RX 20
#define UDMA_SEC_CHANNEL_EPI0TX 21
#define UDMA_SEC_CHANNEL_ADC10  24
#define UDMA_SEC_CHANNEL_ADC11  25
#define UDMA_SEC_CHANNEL_ADC12  26
#define UDMA_SEC_CHANNEL_ADC13  27
#define UDMA_SEC_CHANNEL_SW     30

//*****************************************************************************
//
// uDMA default/secondary peripheral selections, to be passed to
// uDMAChannelSelectSecondary() and uDMAChannelSelectDefault().
//
//*****************************************************************************
#define UDMA_DEF_USBEP1RX_SEC_UART2RX                                         \
                                0x00000001
#define UDMA_DEF_USBEP1TX_SEC_UART2TX                                         \
                                0x00000002
#define UDMA_DEF_USBEP2RX_SEC_TMR3A                                           \
                                0x00000004
#define UDMA_DEF_USBEP2TX_SEC_TMR3B                                           \
                                0x00000008
#define UDMA_DEF_USBEP3RX_SEC_TMR2A                                           \
                                0x00000010
#define UDMA_DEF_USBEP3TX_SEC_TMR2B                                           \
                                0x00000020
#define UDMA_DEF_ETH0RX_SEC_TMR2A                                             \
                                0x00000040
#define UDMA_DEF_ETH0TX_SEC_TMR2B                                             \
                                0x00000080
#define UDMA_DEF_UART0RX_SEC_UART1RX                                          \
                                0x00000100
#define UDMA_DEF_UART0TX_SEC_UART1TX                                          \
                                0x00000200
#define UDMA_DEF_SSI0RX_SEC_SSI1RX                                            \
                                0x00000400
#define UDMA_DEF_SSI0TX_SEC_SSI1TX                                            \
                                0x00000800
#define UDMA_DEF_RESERVED_SEC_UART2RX                                         \
                                0x00001000
#define UDMA_DEF_RESERVED_SEC_UART2TX                                         \
                                0x00002000
#define UDMA_DEF_ADC00_SEC_TMR2A                                              \
                                0x00004000
#define UDMA_DEF_ADC01_SEC_TMR2B                                              \
                                0x00008000
#define UDMA_DEF_ADC02_SEC_RESERVED                                           \
                                0x00010000
#define UDMA_DEF_ADC03_SEC_RESERVED                                           \
                                0x00020000
#define UDMA_DEF_TMR0A_SEC_TMR1A                                              \
                                0x00040000
#define UDMA_DEF_TMR0B_SEC_TMR1B                                              \
                                0x00080000
#define UDMA_DEF_TMR1A_SEC_EPI0RX                                             \
                                0x00100000
#define UDMA_DEF_TMR1B_SEC_EPI0TX                                             \
                                0x00200000
#define UDMA_DEF_UART1RX_SEC_RESERVED                                         \
                                0x00400000
#define UDMA_DEF_UART1TX_SEC_RESERVED                                         \
                                0x00800000
#define UDMA_DEF_SSI1RX_SEC_ADC10                                             \
                                0x01000000
#define UDMA_DEF_SSI1TX_SEC_ADC11                                             \
                                0x02000000
#define UDMA_DEF_RESERVED_SEC_ADC12                                           \
                                0x04000000
#define UDMA_DEF_RESERVED_SEC_ADC13                                           \
                                0x08000000
#define UDMA_DEF_I2S0RX_SEC_RESERVED                                          \
                                0x10000000
#define UDMA_DEF_I2S0TX_SEC_RESERVED                                          \
                                0x20000000

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
extern void uDMAEnable(void);
extern void uDMADisable(void);
extern unsigned long uDMAErrorStatusGet(void);
extern void uDMAErrorStatusClear(void);
extern void uDMAChannelEnable(unsigned long ulChannel);
extern void uDMAChannelDisable(unsigned long ulChannel);
extern tBoolean uDMAChannelIsEnabled(unsigned long ulChannel);
extern void uDMAControlBaseSet(void *pControlTable);
extern void *uDMAControlBaseGet(void);
extern void uDMAChannelRequest(unsigned long ulChannel);
extern void uDMAChannelAttributeEnable(unsigned long ulChannel,
                                       unsigned long ulAttr);
extern void uDMAChannelAttributeDisable(unsigned long ulChannel,
                                        unsigned long ulAttr);
extern unsigned long uDMAChannelAttributeGet(unsigned long ulChannel);
extern void uDMAChannelControlSet(unsigned long ulChannel,
                                  unsigned long ulControl);
extern void uDMAChannelTransferSet(unsigned long ulChannel,
                                   unsigned long ulMode, void *pvSrcAddr,
                                   void *pvDstAddr,
                                   unsigned long ulTransferSize);
extern unsigned long uDMAChannelSizeGet(unsigned long ulChannel);
extern unsigned long uDMAChannelModeGet(unsigned long ulChannel);
extern void uDMAIntRegister(unsigned long ulIntChannel,
                            void (*pfnHandler)(void));
extern void uDMAIntUnregister(unsigned long ulIntChannel);
extern void uDMAChannelSelectDefault(unsigned long ulDefPeriphs);
extern void uDMAChannelSelectSecondary(unsigned long ulSecPeriphs);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  __UDMA_H__
