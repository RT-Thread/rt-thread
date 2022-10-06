/**
 *  \file   cppi41dma.h
 *
 *  \brief  CPPI 4.1 DMA related function prototypes
 *
 *  This file contains the API prototypes for CPPI 4.1 DMA
*/

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
#ifndef __CPPI41DMA_H
#define __CPPI41DMA_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "usb.h"
#include "hw_usb.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

#if defined(ccs) ||             \
    defined(codered) ||         \
    defined(gcc) ||             \
    defined(rvmdk) ||           \
    defined(__ARMCC_VERSION) || \
    defined(sourcerygxx)
#define CPPI_DMA_PACKED __attribute__ ((packed))
#elif defined(ewarm) || defined(__IAR_SYSTEMS_ICC__)
#define CPPI_DMA_PACKED
#elif defined(__TMS470__)
#if defined(__TI_TMS470_V7__) || (__TI_COMPILER_VERSION__ >= 5000000)
#define CPPI_DMA_PACKED __attribute__ ((packed))
#else
#warn The packed attribute is not supported by this version of the TI ARM CGT. \
      Please upgrade to version 5.x or use an alternate toolchain instead.
#define CPPI_DMA_PACKED
#endif
#elif defined(_TMS320C6X)
#define CPPI_DMA_PACKED __attribute__ ((packed))
#else
#error Unrecognized COMPILER!
#endif

#if defined (am335x_15x15) || defined(am335x) || defined(c6a811x)
#define USB_TX_MODE_SHIFT(n)       (((n) * 2) - 2)
#define USB_RX_MODE_SHIFT(n)       (((n) * 2) - 2)
#else
#define USB_TX_MODE_SHIFT(n)       (((((n) - 1) << 1) * 2))
#define USB_RX_MODE_SHIFT(n)       ((((((n) - 1) << 1) * 2) + 16))

#endif
#if defined (am335x_15x15) || defined(am335x) || defined(c6a811x)
#define USB_OTGBASE USBSS_BASE

//Interrupt status macros
#define CPDMA_TX_PENDING 0x60000000
#define CPDMA_RX_PENDING 0x00006000

#define NUMOF_USB_INSTANCE                    2
#else
#define USB_OTGBASE USB_0_OTGBASE

//Interrupt status macros
#define CPDMA_TX_PENDING 0x03000000
#define CPDMA_RX_PENDING 0x0C000000

#define NUMOF_USB_INSTANCE                    USB_CONTROLLER_NUM_INSTANCES
#endif

#define CPDMA_STAR_0_PEND    0x1
#define CPDMA_STAR_1_PEND    0x2
//
//Link RAM size  = 4* number of Descriptors
//                                           4000                   
#define LINK_RAM0_SIZE                       1024 //  max value would be (512 + 20) * 4
#define DESC0_REGION_SIZE                    (1024 * 20) + SOC_CACHELINE_SIZE_MAX //16384 // > (512 + 20)*64 + SOC_CACHELINE_SIZE_MAX

//#define LINK_RAM_SIZE                        1024
//#define DESC_REGION_SIZE                    (1024 * 20) + SOC_CACHELINE_SIZE_MAX
//
// Link and Desc Region1  - this is where TDs would be stored
// Why : Our BDs or PDs are 64 bytes long and the TDs 32. Data structures of
// only similar sizes can be stored in the same Descriptor region . Link RAM though
// can be shared , but we define another Linking RAM region  .. Paranoia
//
#define LINK_RAM1_SIZE                       32  //  max value would be (32 * 4)
#define DESC1_REGION_SIZE                    1088  // > 32 * 32 + SOC_CACHELINE_SIZE_MAX


// Maximum packet length for GRNDIS mode
#define GRNDIS_MAX_PACKET_LENGTH             512 * 8

#define  CPDMA_NUMOF_BUFFERS                 512

#ifdef USB_MODE_FULLSPEED
    #define USB_PACKET_LENGTH                64
#else
    #define USB_PACKET_LENGTH                512
#endif /* USB_MODE_FULLSPEED */

//Encoded as 2^(5+ desc_size)
#define QUEUE_MGR_DESCSIZE                   0x100
//Encoded as 2^(5+ reg_size)

#define QUEUE_MGR_REGSIZE                    0x3

// Defines for The tear down Q
#define QUEUE_TDDESC_MGR_DESCSIZE            0x0   // DescSize in # of bytes: 2^(5+0) = 32 Bytes
#define QUEUE_TDDESC_MGR_REGSIZE             0x0   // RegionSize in # of desc: 2^(5+1) = 64 Desc
#define QUEUE_TDDESC_STARTINDEX_SHIFT        16
#define QUEUE_TDDESC_STARTINDEX      	     0
#define MAX_TDD_NUM                          32 	  //Max TearDown Desc Count: QUEUE_TDDESC_MGR_REGSIZE

#define CPDMA_DESC_TYPE_TD_SHIFT    		 27
#define CPDMA_DESC_TYPE_TD                	 0x13

//Maximum number of data endpoints in one USB Intance
#define MAX_NUM_EP                           15

//
// Maximum number of BDs to be reduced to 64 so as to reduce memory foot print
//
#define MAX_BD_NUM                           512
#define NUM_OF_RX_BDs                        20

#define BYTE_ALIGNMENT                       SOC_CACHELINE_SIZE_MAX

#define SCHEDULER_ENABLE_SHFT                31
#define CLAER_INTDO_STATUS                   0x03

//encoded in 4-byte increments with values 0 to 31 representing 24 and so on to 148 bytes.
#define SIZE_OF_SINGLE_BD                	 0X0A
#define SIZE_OF_TEARDOWNDESC             	 0x02 //32 bytes

#define CPDMA_BUFFER_NOT_USED                0
#define CPDMA_BUFFER_USED                    1

#define CPDMA_BD_PACKET_TYPE                 16
#define CPDMA_TEARDOWN_DESC_TYPE             0x13

#define SOP                                 1
#define MOP                                 2
#define EOP                                 4

#define DMA_TX_IN_PROGRESS                  1
#define DMA_TX_COMPLETED                    0

#if defined (am335x_15x15) || defined(am335x) || defined(c6a811x)
//DMA registers

#define CPDMA_TD_FD_QUEUE_CONTROL_REG       0x2004
#define CPDMA_TX_CHANNEL_CONFIG_REG         0x2800 
#define CPDMA_RX_CHANNEL_CONFIG_REG         0x2808 
#define CPDMA_RX_CHANNEL_REG_A              0x280C
#define CPDMA_RX_CHANNEL_REG_B              0x2810
#define CPDMA_SCHED_CONTROL_REG             0x3000
#define CPDMA_SCHED_TABLE_0                 0x3800
#define CPDMA_SCHED_TABLE_1                 0x3804
#define CPDMA_SCHED_TABLE_2                 0x3808
#define CPDMA_SCHED_TABLE_3                 0x380C

#define NUM_OF_SCHEDULER_ENTRIES            16
#else
//DMA registers
#define CPDMA_TD_FD_QUEUE_CONTROL_REG       0x1004
#define CPDMA_TX_CHANNEL_CONFIG_REG         0x1800 
#define CPDMA_RX_CHANNEL_CONFIG_REG         0x1808 
#define CPDMA_RX_CHANNEL_REG_A              0x180C
#define CPDMA_RX_CHANNEL_REG_B              0x1810
#define CPDMA_SCHED_CONTROL_REG             0x2000
#define CPDMA_SCHED_TABLE_0                 0x2800
#define CPDMA_SCHED_TABLE_1                 0x2804
#define NUM_OF_SCHEDULER_ENTRIES            8
#endif

#define CPDMA_INTD_0_REGISTER                0x3200
#define CPDMA_CLEAR_INTD_0_STATUS            0x3280
#define CPDMA_LRAM_0_BASE                 	 0x4080
#define CPDMA_LRAM_0_SIZE                    0x4084
#define CPDMA_LRAM_1_BASE                    0x4088
#define CPDMA_PEND_0_REGISTER                0x4090
#define CPDMA_PEND_1_REGISTER                0x4094
#define CPDMA_PEND_2_REGISTER                0x4098
#define CPDMA_PEND_3_REGISTER                0x409C
#define CPDMA_PEND_4_REGISTER                0x40A0
#define CPDMA_QUEUEMGR_REGION_0              0x5000
#define CPDMA_QUEUEMGR_REGION_0_CONTROL      0x5004
#define CPDMA_QUEUEMGR_REGION_1              0x5010
#define CPDMA_QUEUEMGR_REGION_1_CONTROL      0x5014
#define CPDMA_QUEUEMGR_QUEUE_N_REGISTER_A    0x6000
#define CPDMA_QUEUE_REGISTER_D               0x600C
#define CPDMA_QUEUE_STATUS_A                 0x7000
#define CPDMA_QUEUE_STATUS_A_COUNT_MASK   	 0x3FFF

//Bit Fields for Channel Config
#define SCHEDULE_RX_CHANNEL                 0x83828180
#define SCHEDULE_TX_CHANNEL                 0x03020100

#define SCHEDULE_RX1_CHANNEL                0x9291908F
#define SCHEDULE_TX1_CHANNEL                0x1211100F

// Changed by vineeth - Writing to reserved Location
//#define CPDMA_RX_CHANNEL_ENABLE             0x81004000
#define CPDMA_RX_CHANNEL_ENABLE             0x81004000
#define CPDMA_TX_CHANNEL_ENABLE             0x80000000

/* Tx Channel N Global Configuration Register bits */
#define DMA_CH_TX_ENABLE_SHIFT		31
#define DMA_CH_TX_ENABLE_MASK		(1 << DMA_CH_TX_ENABLE_SHIFT)
#define DMA_CH_TX_TEARDOWN_SHIFT	30
#define DMA_CH_TX_TEARDOWN_MASK		(1 << DMA_CH_TX_TEARDOWN_SHIFT)
#define DMA_CH_TX_DEFAULT_QMGR_SHIFT	12
#define DMA_CH_TX_DEFAULT_QMGR_MASK	(3 << DMA_CH_TX_DEFAULT_QMGR_SHIFT)
#define DMA_CH_TX_DEFAULT_QNUM_SHIFT	0
#define DMA_CH_TX_DEFAULT_QNUM_MASK	(0xfff << DMA_CH_TX_DEFAULT_QNUM_SHIFT)

//Clear Auto set for TX endpoint
#define CPDMA_TX_CLR_AUTO_SET               0x7FFF

// Set DMAReqEnab 
#define CPDMA_TX_SET_REQ_ENABLE             0x1400
#define CPDMA_TX_SET_DMAMODE                0x0400     

// Clear AUTOCLEAR and DMAReqMode
#define CPDMA_RX_CLR_AUTO_CLEAR             0x77FF

// Set DMAReqEnab
#define CPDMA_RX_SET_REQ_ENABLE             0x2000
// Clear DMAReqEnab & DMAReqMode
#define CPDMA_RX_CLR_REQ_ENABLE             0xDFFF

// Clear DMAReqEnab & DMAReqMode
#define CPDMA_TX_CLR_REQ_ENABLE             0xEBFF

// Clear DMA Request Enable 
#define CPDMA_TX_CLEAR_REQ_ENABLE             0xEFFF

// Bit fields  for Schduler control reg
#define ENABLE_CPPIDMA                      0x1
#define DISABLE_CPPIDMA                     0x0

//DMA directions
#define CPDMA_DIR_RX                        0x1
#define CPDMA_DIR_TX                        0x0

//Bit Fields to set the DMA Mode
#define CPDMA_MODE_ENABLE_GLOBAL_RNDIS       0x00000010

//DMA mode
#define CPDMA_MODE_SET_TRANSPARENT          0x0
#define CPDMA_MODE_SET_RNDIS                0x1
#define CPDMA_MODE_SET_LINUXCDC             0x2
#define CPDMA_MODE_SET_GRNDIS               0x3

#if defined (am335x_15x15) || defined(am335x) || defined(c6a811x)
#define NUM_TX_SUBMITQ                      60
#define NUM_TX_COMPQ                        30
#define NUM_RX_COMPQ                        30

//TX submit q
#define    TX_SUBMITQ1                      32
#define TX_SUBMITQ2                         33
#define TX_SUBMITQ3                         34
#define TX_SUBMITQ4                         35
#define TX_SUBMITQ5                         36
#define TX_SUBMITQ6                         37
#define TX_SUBMITQ7                         38
#define TX_SUBMITQ8                         39
#define TX_SUBMITQ9                         40
#define TX_SUBMITQ10                        41
#define TX_SUBMITQ11                        42
#define TX_SUBMITQ12                        43
#define TX_SUBMITQ13                        44
#define TX_SUBMITQ14                        45
#define TX_SUBMITQ15                        46
#define TX_SUBMITQ16                        47
#define TX_SUBMITQ17                        48
#define TX_SUBMITQ18                        49
#define TX_SUBMITQ19                        50
#define TX_SUBMITQ20                        51
#define TX_SUBMITQ21                        52
#define TX_SUBMITQ22                        53
#define TX_SUBMITQ23                        54
#define TX_SUBMITQ24                        55
#define TX_SUBMITQ25                        56
#define TX_SUBMITQ26                        57
#define TX_SUBMITQ27                        58
#define TX_SUBMITQ28                        59
#define TX_SUBMITQ29                        60
#define TX_SUBMITQ30                        61

//TX Completion queue
#define TX_COMPQ1                           93
#define TX_COMPQ2                           94
#define TX_COMPQ3                           95
#define TX_COMPQ4                           96
#define TX_COMPQ5                           97
#define TX_COMPQ6                           98
#define TX_COMPQ7                           99
#define TX_COMPQ8                           100
#define TX_COMPQ9                           101
#define TX_COMPQ10                          102
#define TX_COMPQ11                          103
#define TX_COMPQ12                          104
#define TX_COMPQ13                          105
#define TX_COMPQ14                          106
#define TX_COMPQ15                          107

#define TX_COMPQ16                          125

//RX Completion queue
#define RX_COMPQ1                           109
#define RX_COMPQ2                           110
#define RX_COMPQ3                           111
#define RX_COMPQ4                           112
#define RX_COMPQ5                           113
#define RX_COMPQ6                           114
#define RX_COMPQ7                           115
#define RX_COMPQ8                           116
#define RX_COMPQ9                           117
#define RX_COMPQ10                          118
#define RX_COMPQ11                          119
#define RX_COMPQ12                          120
#define RX_COMPQ13                          121
#define RX_COMPQ14                          122
#define RX_COMPQ15                          123

#define RX_COMPQ16                          141
//
// Teardown descriptor Queue
//
#define USB0_TEARDOWNQ1             	    31

#else
#define NUM_TX_SUBMITQ                      8
#define NUM_TX_COMPQ                        4
#define NUM_RX_COMPQ                        4

//TX submit q
#define TX_SUBMITQ1                      	16
#define TX_SUBMITQ2                         17
#define TX_SUBMITQ3                         18
#define TX_SUBMITQ4                         19
#define TX_SUBMITQ5                         20
#define TX_SUBMITQ6                         21
#define TX_SUBMITQ7                         22
#define TX_SUBMITQ8                         23

//TX Completion queue
#define TX_COMPQ1                           24
#define TX_COMPQ2                           25

//RX Completion queue
#define RX_COMPQ1                           26
#define RX_COMPQ2                           27

// This needs to be verified for AM18x
#define USB0_TEARDOWNQ1             	    15
#endif

#define CPPI41_TEARDOWN_TX_RX_SHIFT	16
#define CPPI41_TEARDOWN_TX_RX_MASK	(1 << CPPI41_TEARDOWN_TX_RX_SHIFT)
#define CPPI41_TEARDOWN_DMA_NUM_SHIFT	10
#define CPPI41_TEARDOWN_DMA_NUM_MASK	(0x3f << CPPI41_TEARDOWN_DMA_NUM_SHIFT)
#define CPPI41_TEARDOWN_CHAN_NUM_SHIFT	0
#define CPPI41_TEARDOWN_CHAN_NUM_MASK	(0x3f << CPPI41_TEARDOWN_CHAN_NUM_SHIFT)

/*
 * CPPI 4.1 Teardown Descriptor
 */
typedef struct
{
	unsigned int channelNumber:6;
	unsigned int reserved2:4;
	unsigned int dmaNumber:6; /*DMA number*/
	unsigned int txrx:1; /*Tx=0; Rx=1*/
	unsigned int reserved1:10;
	unsigned int tearDownDescType:5;	/* Teardown information */
}CPPI_DMA_PACKED cppi41TearDownInfo;

typedef struct
{
	unsigned int teardown_info;	/* Teardown information */
	unsigned int reserved[7];	/* 28 byte padding */
}CPPI_DMA_PACKED cppi41TearDownDesc;


//BD-PD structure
typedef struct {
    unsigned int pktLength:22;
    unsigned int protSize:5;
    unsigned int hostPktType:5;     // This should be 16
}hPDWord0;

typedef struct {
    unsigned int dstTag:16;         //bits[15:0] always Zero
    unsigned int srcSubChNum:5;    //bits[20:16] always Zero
    unsigned int srcChNum:6;         //bits[26:21]
    unsigned int srcPrtNum:5;         //bits[31:27]
}hPDWord1;

typedef struct {
    unsigned int pktRetQueue:12;     //bits[11:0]
    unsigned int pktRetQM:2;         //bits[13:12]
    unsigned int onChip:1;         //bit[14]
    unsigned int retPolicy:1;         //bit[15]
    unsigned int protoSpecific:4;    //bits[19:16]
    unsigned int rsv:6;             //bits[25:20]
    unsigned int pktType:5;         //bits[30:26]
    unsigned int pktErr:1;         //bit[31]
}hPDWord2;

typedef struct hostPacketDesc {
    hPDWord0 hPDword0;
    hPDWord1 hPDword1;
    hPDWord2 hPDword2;
    unsigned int buffLength;
    unsigned int buffAdd;
    struct hostPacketDesc *nextHBDptr;
    unsigned int gBuffLength;
    unsigned int gBuffAdd;

    unsigned char packetId;
    unsigned short endPoint;
    unsigned short channel;
    unsigned char devInst;
    void * reqContext;
    unsigned char reserved[18];
    
} hostPacketDesc ;

// End point info structure for the application
typedef struct  
{
     unsigned int endPoint;
     unsigned short direction;
     unsigned short dmaMode;

}endpointInfo;

//End point inf for internal USB configuration.
typedef struct
{
    unsigned int submitq;
    unsigned int complettionq;
    unsigned int tearDownq;
	unsigned short channel;
    unsigned short mode;
}configEndPointInfo;

typedef struct
{
//unsigned int usbBaseAddress;
//unsigned int otgBaseAddress;

unsigned int usbSubSysBaseAddress;
unsigned int usbInstBaseAddress;

 unsigned int usbInstPhyBaseAddress;
 unsigned int usbInstCoreBaseAddress;

configEndPointInfo rxEndPoint[NUM_USB_EP/2];
configEndPointInfo txEndPoint[NUM_USB_EP/2];

}usbInstance;

typedef struct
{
    //TX submit queues
    unsigned int txSubmitq[NUM_TX_SUBMITQ/2][2];

    //TX Completion queues
    unsigned int txCompletionq[NUM_TX_COMPQ];

    //RX Completion queues
    unsigned int rxCompletionq[NUM_RX_COMPQ];
    //TearDown queue - for Queuing Up 
    unsigned int tearDownq;
    //Pointers for BD Management
    hostPacketDesc *tail_bd ;
    hostPacketDesc *head_bd;    
    //Pointers for TD Management
    cppi41TearDownDesc *tail_tdd ;
    cppi41TearDownDesc *head_tdd;
    unsigned int *region0DescriptorAddress;
    unsigned int *region1DescriptorAddress;
    
    //Array of USB Instances
    usbInstance usbInst[NUMOF_USB_INSTANCE];
}cppi41DmaInfo;

extern endpointInfo epInfo[];

void Cppi41DmaInit(unsigned short usbDevInst, endpointInfo *epInfo, unsigned short numOfEndPoints);

unsigned int dmaTxCompletion(unsigned short usbDevInst, unsigned int ulEndpoint);
unsigned int  dmaRxCompletion(unsigned short usbDevInst, unsigned int ulEndpoint);

void doDmaTxTransfer(unsigned short usbDevInst, unsigned char *buff, 
                                unsigned int length, unsigned int endPoint);

void doDmaRxTransfer(unsigned short usbDevInst, unsigned int length, 
                                unsigned char *buff, unsigned int endPoint);

void enableCoreTxDMA(unsigned short usbDevInst, unsigned int ulEndpoint);
void enableCoreRxDMA(unsigned short usbDevInst, unsigned int ulEndpoint);
void disableCoreRxDMA(unsigned short usbDevIns, unsigned int ulEndpoint);
void disableCoreTxDMA(unsigned short usbDevIns, unsigned int ulEndpoint);

unsigned int CppiDmaGetPendStatus(unsigned short usbDevInst);

unsigned int * cppiDmaAllocBuffer();
void cppiDmaFreeBuffer(unsigned int *dataBuffer);
unsigned int * cppiDmaAllocnBuffer(unsigned int numOfBlocks);
void cppiDmaFreenBuffer(unsigned int *dataBuffer);
void cppiDmaHandleError(unsigned int usbDevInst); 
unsigned int CppiDmaGetINTD0Status(unsigned short usbDevInst);

void print_pend ( );
// Teardown related function declarations
void Cppi41DmaInitTddPool(unsigned short usbDevInst );
int Cppi41DmaRxChTeardown(unsigned short usbDevInst, unsigned int ulEndpoint );
int Cppi41DmaTxChTeardown(unsigned short usbDevInst, unsigned int ulEndpoint );
#ifdef __cplusplus
}
#endif
#endif

