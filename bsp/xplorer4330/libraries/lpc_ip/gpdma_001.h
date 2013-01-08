/*
 * @brief GPDMA Registers and control functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __GPDMA_001_H_
#define __GPDMA_001_H_

#include "sys_config.h"
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup IP_GPDMA_001 IP: GPDMA register block and driver
 * @ingroup IP_Drivers
 * General Purpose DMA
 * @{
 */

/**
 * @brief GPDMA Channel register block structure
 */
typedef struct {
	__IO uint32_t  SRCADDR;				/*!< DMA Channel Source Address Register */
	__IO uint32_t  DESTADDR;			/*!< DMA Channel Destination Address Register */
	__IO uint32_t  LLI;					/*!< DMA Channel Linked List Item Register */
	__IO uint32_t  CONTROL;				/*!< DMA Channel Control Register */
	__IO uint32_t  CONFIG;				/*!< DMA Channel Configuration Register */
	__I  uint32_t  RESERVED1[3];
} IP_GPDMA_001_CH_Type;

#define GPDMA_CHANNELS 8

/**
 * @brief GPDMA register block
 */
typedef struct {						/*!< GPDMA Structure */
	__I  uint32_t  INTSTAT;				/*!< DMA Interrupt Status Register */
	__I  uint32_t  INTTCSTAT;			/*!< DMA Interrupt Terminal Count Request Status Register */
	__O  uint32_t  INTTCCLEAR;			/*!< DMA Interrupt Terminal Count Request Clear Register */
	__I  uint32_t  INTERRSTAT;			/*!< DMA Interrupt Error Status Register */
	__O  uint32_t  INTERRCLR;			/*!< DMA Interrupt Error Clear Register */
	__I  uint32_t  RAWINTTCSTAT;		/*!< DMA Raw Interrupt Terminal Count Status Register */
	__I  uint32_t  RAWINTERRSTAT;		/*!< DMA Raw Error Interrupt Status Register */
	__I  uint32_t  ENBLDCHNS;			/*!< DMA Enabled Channel Register */
	__IO uint32_t  SOFTBREQ;			/*!< DMA Software Burst Request Register */
	__IO uint32_t  SOFTSREQ;			/*!< DMA Software Single Request Register */
	__IO uint32_t  SOFTLBREQ;			/*!< DMA Software Last Burst Request Register */
	__IO uint32_t  SOFTLSREQ;			/*!< DMA Software Last Single Request Register */
	__IO uint32_t  CONFIG;				/*!< DMA Configuration Register */
	__IO uint32_t  SYNC;				/*!< DMA Synchronization Register */
	__I  uint32_t  RESERVED0[50];
	IP_GPDMA_001_CH_Type CH[GPDMA_CHANNELS];
} IP_GPDMA_001_Type;

/**
 * @brief Macro defines for DMA channel control registers
 */
#define GPDMA_DMACCxControl_TransferSize(n) (((n & 0xFFF) << 0))	/**< Transfer size*/
#define GPDMA_DMACCxControl_SBSize(n)       (((n & 0x07) << 12))	/**< Source burst size*/
#define GPDMA_DMACCxControl_DBSize(n)       (((n & 0x07) << 15))	/**< Destination burst size*/
#define GPDMA_DMACCxControl_SWidth(n)       (((n & 0x07) << 18))	/**< Source transfer width*/
#define GPDMA_DMACCxControl_DWidth(n)       (((n & 0x07) << 21))	/**< Destination transfer width*/
#define GPDMA_DMACCxControl_SI              ((1UL << 26))			/**< Source increment*/
#define GPDMA_DMACCxControl_DI              ((1UL << 27))			/**< Destination increment*/
#if defined(CHIP_LPC43XX) || defined(CHIP_LPC18XX)
#define GPDMA_DMACCxControl_SrcTransUseAHBMaster1   ((1UL << 24))	/**< Source AHB master select in 18xx43xx*/
#define GPDMA_DMACCxControl_DestTransUseAHBMaster1  ((1UL << 25))	/**< Destination AHB master select in 18xx43xx*/
#else
#define GPDMA_DMACCxControl_SrcTransUseAHBMaster1   0
#define GPDMA_DMACCxControl_DestTransUseAHBMaster1  0
#endif
#define GPDMA_DMACCxControl_Prot1           ((1UL << 28))			/**< Indicates that the access is in user mode or privileged mode*/
#define GPDMA_DMACCxControl_Prot2           ((1UL << 29))			/**< Indicates that the access is bufferable or not bufferable*/
#define GPDMA_DMACCxControl_Prot3           ((1UL << 30))			/**< Indicates that the access is cacheable or not cacheable*/
#define GPDMA_DMACCxControl_I               ((1UL << 31))			/**< Terminal count interrupt enable bit */

/**
 * @brief Macro defines for DMA Configuration register
 */
#define GPDMA_DMACConfig_E              ((0x01))	/**< DMA Controller enable*/
#define GPDMA_DMACConfig_M              ((0x02))	/**< AHB Master endianness configuration*/
#define GPDMA_DMACConfig_BITMASK        ((0x03))

/**
 * @brief Macro defines for DMA Channel Configuration registers
 */
#define GPDMA_DMACCxConfig_E                    ((1UL << 0))			/**< DMA control enable*/
#define GPDMA_DMACCxConfig_SrcPeripheral(n)     (((n & 0x1F) << 1))		/**< Source peripheral*/
#define GPDMA_DMACCxConfig_DestPeripheral(n)    (((n & 0x1F) << 6))		/**< Destination peripheral*/
#define GPDMA_DMACCxConfig_TransferType(n)      (((n & 0x7) << 11))		/**< This value indicates the type of transfer*/
#define GPDMA_DMACCxConfig_IE                   ((1UL << 14))			/**< Interrupt error mask*/
#define GPDMA_DMACCxConfig_ITC                  ((1UL << 15))			/**< Terminal count interrupt mask*/
#define GPDMA_DMACCxConfig_L                    ((1UL << 16))			/**< Lock*/
#define GPDMA_DMACCxConfig_A                    ((1UL << 17))			/**< Active*/
#define GPDMA_DMACCxConfig_H                    ((1UL << 18))			/**< Halt*/

/**
 * @brief GPDMA Interrupt Clear Status
 */
typedef enum {
	GPDMA_STATCLR_INTTC,	/**< GPDMA Interrupt Terminal Count Request Clear */
	GPDMA_STATCLR_INTERR	/**< GPDMA Interrupt Error Clear */
} GPDMA_StateClear_Type;

/**
 * @brief GPDMA Type of Interrupt Status
 */
typedef enum {
	GPDMA_STAT_INT,			/**< GPDMA Interrupt Status */
	GPDMA_STAT_INTTC,		/**< GPDMA Interrupt Terminal Count Request Status */
	GPDMA_STAT_INTERR,		/**< GPDMA Interrupt Error Status */
	GPDMA_STAT_RAWINTTC,	/**< GPDMA Raw Interrupt Terminal Count Status */
	GPDMA_STAT_RAWINTERR,	/**< GPDMA Raw Error Interrupt Status */
	GPDMA_STAT_ENABLED_CH	/**< GPDMA Enabled Channel Status */
} GPDMA_Status_Type;

/**
 * @brief GPDMA Type of DMA controller
 */
typedef enum {
	GPDMA_TRANSFERTYPE_M2M_CONTROLLER_DMA              = ((0UL)),	/**< Memory to memory - DMA control */
	GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA              = ((1UL)),	/**< Memory to peripheral - DMA control */
	GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA              = ((2UL)),	/**< Peripheral to memory - DMA control */
	GPDMA_TRANSFERTYPE_P2P_CONTROLLER_DMA              = ((3UL)),	/**< Source peripheral to destination peripheral - DMA control */
	GPDMA_TRANSFERTYPE_P2P_CONTROLLER_DestPERIPHERAL   = ((4UL)),	/**< Source peripheral to destination peripheral - destination peripheral control */
	GPDMA_TRANSFERTYPE_M2P_CONTROLLER_PERIPHERAL       = ((5UL)),	/**< Memory to peripheral - peripheral control */
	GPDMA_TRANSFERTYPE_P2M_CONTROLLER_PERIPHERAL       = ((6UL)),	/**< Peripheral to memory - peripheral control */
	GPDMA_TRANSFERTYPE_P2P_CONTROLLER_SrcPERIPHERAL    = ((7UL))	/**< Source peripheral to destination peripheral - source peripheral control */
} FlowControlType;

/**
 * @brief GPDMA structure using for DMA configuration
 */
typedef struct {
	uint32_t ChannelNum;	/**< DMA channel number, should be in
							 *  range from 0 to 7.
							 *  Note: DMA channel 0 has the highest priority
							 *  and DMA channel 7 the lowest priority.
							 */
	uint32_t TransferSize;	/**< Length/Size of transfer */
	uint32_t TransferWidth;	/**< Transfer width - used for TransferType is GPDMA_TRANSFERTYPE_M2M only */
	uint32_t SrcAddr;	/**< Physical Source Address, used in case TransferType is chosen as
						 *       GPDMA_TRANSFERTYPE_M2M or GPDMA_TRANSFERTYPE_M2P */
	uint32_t DstAddr;	/**< Physical Destination Address, used in case TransferType is chosen as
						 *       GPDMA_TRANSFERTYPE_M2M or GPDMA_TRANSFERTYPE_P2M */
	uint32_t TransferType;	/**< Transfer Type, should be one of the following:
							 * - GPDMA_TRANSFERTYPE_M2M: Memory to memory - DMA control
							 * - GPDMA_TRANSFERTYPE_M2P: Memory to peripheral - DMA control
							 * - GPDMA_TRANSFERTYPE_P2M: Peripheral to memory - DMA control
							 * - GPDMA_TRANSFERTYPE_P2P: Source peripheral to destination peripheral - DMA control
							 */
} GPDMA_Channel_CFG_Type;

/**
 * @brief	Initialize the GPDMA
 * @param	pGPDMA	: The Base Address of GPDMA on the chip
 * @return	Nothing
 */
void IP_GPDMA_Init(IP_GPDMA_001_Type *pGPDMA);

/**
 * @brief	Set up the DPDMA according to the specification configuration details
 * @param	pGPDMA						: The Base Address of GPDMA on the chip
 * @param	GPDMAChannelConfig			: Configuration struct
 * @param	GPDMA_LUTPerBurstSrcConn	: Peripheral Source burst size
 * @param	GPDMA_LUTPerBurstDstConn	: Peripheral Destination burst size
 * @param	GPDMA_LUTPerWidSrcConn		: Peripheral Source transfer width
 * @param	GPDMA_LUTPerWidDstConn		: Peripheral Destination transfer width
 * @param	GPDMA_LUTPerAddrSrcConn		: Peripheral Source Address
 * @param	GPDMA_LUTPerAddrDstConn		: Peripheral Destination Address
 * @param	SrcPeripheral				: Peripheral Source ID
 * @param	DstPeripheral				: Peripheral Destination ID
 * @return	SUCCESS or ERROR on setup failure
 */
Status IP_GPDMA_Setup(IP_GPDMA_001_Type *pGPDMA,
					  GPDMA_Channel_CFG_Type *GPDMAChannelConfig,
					  uint32_t GPDMA_LUTPerBurstSrcConn,
					  uint32_t GPDMA_LUTPerBurstDstConn,
					  uint32_t GPDMA_LUTPerWidSrcConn,
					  uint32_t GPDMA_LUTPerWidDstConn,
					  uint32_t GPDMA_LUTPerAddrSrcConn,
					  uint32_t GPDMA_LUTPerAddrDstConn,
					  uint8_t  SrcPeripheral,
					  uint8_t  DstPeripheral);

/**
 * @brief	Read the status from different registers according to the type
 * @param	pGPDMA		: The Base Address of GPDMA on the chip
 * @param	type		: Status mode, should be:
 *							- GPDMA_STAT_INT		: GPDMA Interrupt Status
 *							- GPDMA_STAT_INTTC		: GPDMA Interrupt Terminal Count Request Status
 *							- GPDMA_STAT_INTERR		: GPDMA Interrupt Error Status
 *							- GPDMA_STAT_RAWINTTC	: GPDMA Raw Interrupt Terminal Count Status
 *							- GPDMA_STAT_RAWINTERR	: GPDMA Raw Error Interrupt Status
 *							- GPDMA_STAT_ENABLED_CH	: GPDMA Enabled Channel Status
 * @param	channel		: The GPDMA channel : 0 - 7
 * @return	SET is interrupt is pending or RESET if not pending
 */
IntStatus IP_GPDMA_IntGetStatus(IP_GPDMA_001_Type *pGPDMA, GPDMA_Status_Type type, uint8_t channel);

/**
 * @brief	Clear the Interrupt Flag from different registers according to the type
 * @param	pGPDMA	: The Base Address of GPDMA on the chip
 * @param	type	: Flag mode, should be:
 *						- GPDMA_STATCLR_INTTC	: GPDMA Interrupt Terminal Count Request
 *						- GPDMA_STATCLR_INTERR	: GPDMA Interrupt Error
 * @param	channel	: The GPDMA channel : 0 - 7
 * @return	Nothing
 */
void IP_GPDMA_ClearIntPending(IP_GPDMA_001_Type *pGPDMA, GPDMA_StateClear_Type type, uint8_t channel);

/**
 * @brief	Enable or Disable the GPDMA Channel
 * @param	pGPDMA		: The Base Address of GPDMA on the chip
 * @param	channelNum	: The GPDMA channel : 0 - 7
 * @param	NewState	: ENABLE to enable GPDMA or DISABLE to disable GPDMA
 * @return	Nothing
 */
void IP_GPDMA_ChannelCmd(IP_GPDMA_001_Type *pGPDMA, uint8_t channelNum, FunctionalState NewState);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __GPDMA_001_H_ */
