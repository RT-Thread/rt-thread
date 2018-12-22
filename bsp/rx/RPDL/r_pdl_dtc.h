/*""FILE COMMENT""*******************************************************
* System Name	: DTC API for RX62N
* File Name		: r_pdl_dtc.h
* Version		: 1.02
* Contents		: DTC API header
* Customer		: 
* Model			: 
* Order			: 
* CPU			: RX
* Compiler		: RXC
* OS			: Nothing
* Programmer	: 
* Note			: 
************************************************************************
* Copyright, 2011. Renesas Electronics Corporation
* and Renesas Solutions Corporation
************************************************************************
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FILE COMMENT END""**************************************************/

#ifndef R_PDL_DTC_H
#define R_PDL_DTC_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool R_DTC_Set(
	uint8_t,
	uint32_t *
);
bool R_DTC_Create(
	uint32_t,
	uint32_t *,
	void *,
	void *,
	uint16_t,
	uint8_t
);
bool R_DTC_Destroy(
	void
);
bool R_DTC_Control(
	uint32_t,
	uint32_t *,
	void *,
	void *,
	uint16_t,
	uint8_t
);
bool R_DTC_GetStatus(
	uint32_t *,
	uint16_t *,
	uint32_t *,
	uint32_t *,
 	uint16_t *,
 	uint8_t *
);

/* Read skip control */
#define PDL_DTC_READ_SKIP_DISABLE			0x01u
#define PDL_DTC_READ_SKIP_ENABLE			0x02u

/* Address size control */
#define PDL_DTC_ADDRESS_FULL				0x04u
#define PDL_DTC_ADDRESS_SHORT				0x08u

/* Transfer mode selection */
#define PDL_DTC_NORMAL						0x00000001ul
#define PDL_DTC_REPEAT						0x00000002ul
#define PDL_DTC_BLOCK						0x00000004ul
#define PDL_DTC_SOURCE						0x00000008ul
#define PDL_DTC_DESTINATION					0x00000010ul

/* Address direction selection */
#define PDL_DTC_SOURCE_ADDRESS_FIXED		0x00000020ul
#define PDL_DTC_SOURCE_ADDRESS_PLUS			0x00000040ul
#define PDL_DTC_SOURCE_ADDRESS_MINUS		0x00000080ul
#define PDL_DTC_DESTINATION_ADDRESS_FIXED	0x00000100ul
#define PDL_DTC_DESTINATION_ADDRESS_PLUS	0x00000200ul
#define PDL_DTC_DESTINATION_ADDRESS_MINUS	0x00000400ul

/* Transfer data size */
#define PDL_DTC_SIZE_8						0x00000800ul
#define PDL_DTC_SIZE_16						0x00001000ul
#define PDL_DTC_SIZE_32						0x00002000ul

/* Chain transfer control */
#define PDL_DTC_CHAIN_DISABLE				0x00004000ul
#define PDL_DTC_CHAIN_CONTINUOUS			0x00008000ul
#define PDL_DTC_CHAIN_0						0x00010000ul

/* Interrupt generation */
#define PDL_DTC_IRQ_COMPLETE				0x00020000ul
#define PDL_DTC_IRQ_TRANSFER				0x00040000ul

/* Trigger selection */
#define PDL_DTC_TRIGGER_CHAIN		(uint32_t)(0x00u << 24)
#define PDL_DTC_TRIGGER_SW			(uint32_t)(VECT_ICU_SWINT << 24)
#define PDL_DTC_TRIGGER_CMT0		(uint32_t)(VECT_CMT0_CMI0 << 24)
#define PDL_DTC_TRIGGER_CMT1		(uint32_t)(VECT_CMT1_CMI1 << 24)
#define PDL_DTC_TRIGGER_CMT2		(uint32_t)(VECT_CMT2_CMI2 << 24)
#define PDL_DTC_TRIGGER_CMT3		(uint32_t)(VECT_CMT3_CMI3 << 24)
#define PDL_DTC_TRIGGER_USB0_D0		(uint32_t)(VECT_USB0_D0FIFO0 << 24)
#define PDL_DTC_TRIGGER_USB1_D0		(uint32_t)(VECT_USB1_D0FIFO1 << 24)
#define PDL_DTC_TRIGGER_USB0_D1		(uint32_t)(VECT_USB0_D1FIFO0 << 24)
#define PDL_DTC_TRIGGER_USB1_D1		(uint32_t)(VECT_USB1_D1FIFO1 << 24)
#define PDL_DTC_TRIGGER_SPI0_RX		(uint32_t)(VECT_RSPI0_SPRI0 << 24)
#define PDL_DTC_TRIGGER_SPI1_RX		(uint32_t)(VECT_RSPI1_SPRI1 << 24)
#define PDL_DTC_TRIGGER_SPI0_TX		(uint32_t)(VECT_RSPI0_SPTI0 << 24)
#define PDL_DTC_TRIGGER_SPI1_TX		(uint32_t)(VECT_RSPI1_SPTI1 << 24)
#define PDL_DTC_TRIGGER_IRQ0		(uint32_t)(VECT_ICU_IRQ0 << 24)
#define PDL_DTC_TRIGGER_IRQ1		(uint32_t)(VECT_ICU_IRQ1 << 24)
#define PDL_DTC_TRIGGER_IRQ2		(uint32_t)(VECT_ICU_IRQ2 << 24)
#define PDL_DTC_TRIGGER_IRQ3		(uint32_t)(VECT_ICU_IRQ3 << 24)
#define PDL_DTC_TRIGGER_IRQ4		(uint32_t)(VECT_ICU_IRQ4 << 24)
#define PDL_DTC_TRIGGER_IRQ5		(uint32_t)(VECT_ICU_IRQ5 << 24)
#define PDL_DTC_TRIGGER_IRQ6		(uint32_t)(VECT_ICU_IRQ6 << 24)
#define PDL_DTC_TRIGGER_IRQ7		(uint32_t)(VECT_ICU_IRQ7 << 24)
#define PDL_DTC_TRIGGER_IRQ8		(uint32_t)(VECT_ICU_IRQ8 << 24)
#define PDL_DTC_TRIGGER_IRQ9		(uint32_t)(VECT_ICU_IRQ9 << 24)
#define PDL_DTC_TRIGGER_IRQ10		(uint32_t)(VECT_ICU_IRQ10 << 24)
#define PDL_DTC_TRIGGER_IRQ11		(uint32_t)(VECT_ICU_IRQ11 << 24)
#define PDL_DTC_TRIGGER_IRQ12		(uint32_t)(VECT_ICU_IRQ12 << 24)
#define PDL_DTC_TRIGGER_IRQ13		(uint32_t)(VECT_ICU_IRQ13 << 24)
#define PDL_DTC_TRIGGER_IRQ14		(uint32_t)(VECT_ICU_IRQ14 << 24)
#define PDL_DTC_TRIGGER_IRQ15		(uint32_t)(VECT_ICU_IRQ15 << 24)
#define PDL_DTC_TRIGGER_ADI0		(uint32_t)(VECT_AD0_ADI0 << 24)
#define PDL_DTC_TRIGGER_ADI1		(uint32_t)(VECT_AD1_ADI1 << 24)
#define PDL_DTC_TRIGGER_ADC12		(uint32_t)(VECT_S12AD_ADI << 24)
#define PDL_DTC_TRIGGER_TGIA0		(uint32_t)(VECT_MTU0_TGIA0 << 24)
#define PDL_DTC_TRIGGER_TGIA1		(uint32_t)(VECT_MTU1_TGIA1 << 24)
#define PDL_DTC_TRIGGER_TGIA2		(uint32_t)(VECT_MTU2_TGIA2 << 24)
#define PDL_DTC_TRIGGER_TGIA3		(uint32_t)(VECT_MTU3_TGIA3 << 24)
#define PDL_DTC_TRIGGER_TGIA4		(uint32_t)(VECT_MTU4_TGIA4 << 24)
#define PDL_DTC_TRIGGER_TGIA6		(uint32_t)(VECT_MTU6_TGIA6 << 24)
#define PDL_DTC_TRIGGER_TGIA7		(uint32_t)(VECT_MTU7_TGIA7 << 24)
#define PDL_DTC_TRIGGER_TGIA8		(uint32_t)(VECT_MTU8_TGIA8 << 24)
#define PDL_DTC_TRIGGER_TGIA9		(uint32_t)(VECT_MTU9_TGIA9 << 24)
#define PDL_DTC_TRIGGER_TGIA10		(uint32_t)(VECT_MTU10_TGIA10 << 24)
#define PDL_DTC_TRIGGER_TGIB0		(uint32_t)(VECT_MTU0_TGIB0 << 24)
#define PDL_DTC_TRIGGER_TGIB1		(uint32_t)(VECT_MTU1_TGIB1 << 24)
#define PDL_DTC_TRIGGER_TGIB2		(uint32_t)(VECT_MTU2_TGIB2 << 24)
#define PDL_DTC_TRIGGER_TGIB3		(uint32_t)(VECT_MTU3_TGIB3 << 24)
#define PDL_DTC_TRIGGER_TGIB4		(uint32_t)(VECT_MTU4_TGIB4 << 24)
#define PDL_DTC_TRIGGER_TGIB6		(uint32_t)(VECT_MTU6_TGIB6 << 24)
#define PDL_DTC_TRIGGER_TGIB7		(uint32_t)(VECT_MTU7_TGIB7 << 24)
#define PDL_DTC_TRIGGER_TGIB8		(uint32_t)(VECT_MTU8_TGIB8 << 24)
#define PDL_DTC_TRIGGER_TGIB9		(uint32_t)(VECT_MTU9_TGIB9 << 24)
#define PDL_DTC_TRIGGER_TGIB10		(uint32_t)(VECT_MTU10_TGIB10 << 24)
#define PDL_DTC_TRIGGER_TGIC0		(uint32_t)(VECT_MTU0_TGIC0 << 24)
#define PDL_DTC_TRIGGER_TGIC3		(uint32_t)(VECT_MTU3_TGIC3 << 24)
#define PDL_DTC_TRIGGER_TGIC4		(uint32_t)(VECT_MTU4_TGIC4 << 24)
#define PDL_DTC_TRIGGER_TGIC6		(uint32_t)(VECT_MTU6_TGIC6 << 24)
#define PDL_DTC_TRIGGER_TGIC9		(uint32_t)(VECT_MTU9_TGIC9 << 24)
#define PDL_DTC_TRIGGER_TGIC10		(uint32_t)(VECT_MTU10_TGIC10 << 24)
#define PDL_DTC_TRIGGER_TGID0		(uint32_t)(VECT_MTU0_TGID0 << 24)
#define PDL_DTC_TRIGGER_TGID3		(uint32_t)(VECT_MTU3_TGID3 << 24)
#define PDL_DTC_TRIGGER_TGID4		(uint32_t)(VECT_MTU4_TGID4 << 24)
#define PDL_DTC_TRIGGER_TGID6		(uint32_t)(VECT_MTU6_TGID6 << 24)
#define PDL_DTC_TRIGGER_TGID9		(uint32_t)(VECT_MTU9_TGID9 << 24)
#define PDL_DTC_TRIGGER_TGID10		(uint32_t)(VECT_MTU10_TGID10 << 24)
#define PDL_DTC_TRIGGER_TGIU5		(uint32_t)(VECT_MTU5_TGIU5 << 24)
#define PDL_DTC_TRIGGER_TGIU11		(uint32_t)(VECT_MTU11_TGIU11 << 24)
#define PDL_DTC_TRIGGER_TGIV5		(uint32_t)(VECT_MTU5_TGIV5 << 24)
#define PDL_DTC_TRIGGER_TGIV11		(uint32_t)(VECT_MTU11_TGIV11 << 24)
#define PDL_DTC_TRIGGER_TGIW5		(uint32_t)(VECT_MTU5_TGIW5 << 24)
#define PDL_DTC_TRIGGER_TGIW11		(uint32_t)(VECT_MTU11_TGIW11 << 24)
#define PDL_DTC_TRIGGER_TCIV4		(uint32_t)(VECT_MTU4_TCIV4 << 24)
#define PDL_DTC_TRIGGER_TCIV10		(uint32_t)(VECT_MTU10_TCIV10 << 24)
#define PDL_DTC_TRIGGER_CMIA0		(uint32_t)(VECT_TMR0_CMIA0 << 24)
#define PDL_DTC_TRIGGER_CMIA1		(uint32_t)(VECT_TMR1_CMIA1 << 24)
#define PDL_DTC_TRIGGER_CMIA2		(uint32_t)(VECT_TMR2_CMIA2 << 24)
#define PDL_DTC_TRIGGER_CMIA3		(uint32_t)(VECT_TMR3_CMIA3 << 24)
#define PDL_DTC_TRIGGER_CMIB0		(uint32_t)(VECT_TMR0_CMIB0 << 24)
#define PDL_DTC_TRIGGER_CMIB1		(uint32_t)(VECT_TMR1_CMIB1 << 24)
#define PDL_DTC_TRIGGER_CMIB2		(uint32_t)(VECT_TMR2_CMIB2 << 24)
#define PDL_DTC_TRIGGER_CMIB3		(uint32_t)(VECT_TMR3_CMIB3 << 24)
#define PDL_DTC_TRIGGER_DMACI0		(uint32_t)(VECT_DMAC_DMAC0I << 24)
#define PDL_DTC_TRIGGER_DMACI1		(uint32_t)(VECT_DMAC_DMAC1I << 24)
#define PDL_DTC_TRIGGER_DMACI2		(uint32_t)(VECT_DMAC_DMAC2I << 24)
#define PDL_DTC_TRIGGER_DMACI3		(uint32_t)(VECT_DMAC_DMAC3I << 24)
#define PDL_DTC_TRIGGER_EXDMACI0	(uint32_t)(VECT_EXDMAC_EXDMAC0I << 24)
#define PDL_DTC_TRIGGER_EXDMACI1	(uint32_t)(VECT_EXDMAC_EXDMAC1I << 24)
#define PDL_DTC_TRIGGER_RXI0		(uint32_t)(VECT_SCI0_RXI0 << 24)
#define PDL_DTC_TRIGGER_RXI1		(uint32_t)(VECT_SCI1_RXI1 << 24)
#define PDL_DTC_TRIGGER_RXI2		(uint32_t)(VECT_SCI2_RXI2 << 24)
#define PDL_DTC_TRIGGER_RXI3		(uint32_t)(VECT_SCI3_RXI3 << 24)
#define PDL_DTC_TRIGGER_RXI5		(uint32_t)(VECT_SCI5_RXI5 << 24)
#define PDL_DTC_TRIGGER_RXI6		(uint32_t)(VECT_SCI6_RXI6 << 24)
#define PDL_DTC_TRIGGER_TXI0		(uint32_t)(VECT_SCI0_TXI0 << 24)
#define PDL_DTC_TRIGGER_TXI1		(uint32_t)(VECT_SCI1_TXI1 << 24)
#define PDL_DTC_TRIGGER_TXI2		(uint32_t)(VECT_SCI2_TXI2 << 24)
#define PDL_DTC_TRIGGER_TXI3		(uint32_t)(VECT_SCI3_TXI3 << 24)
#define PDL_DTC_TRIGGER_TXI5		(uint32_t)(VECT_SCI5_TXI5 << 24)
#define PDL_DTC_TRIGGER_TXI6		(uint32_t)(VECT_SCI6_TXI6 << 24)
#define PDL_DTC_TRIGGER_ICRXI0		(uint32_t)(VECT_RIIC0_ICRXI0 << 24)
#define PDL_DTC_TRIGGER_ICRXI1		(uint32_t)(VECT_RIIC1_ICRXI1 << 24)
#define PDL_DTC_TRIGGER_ICTXI0		(uint32_t)(VECT_RIIC0_ICTXI0 << 24)
#define PDL_DTC_TRIGGER_ICTXI1		(uint32_t)(VECT_RIIC1_ICTXI1 << 24)

/* Stop / Start control */
#define PDL_DTC_STOP				0x01u
#define PDL_DTC_START				0x02u

/* Register modification control */
#define PDL_DTC_UPDATE_SOURCE		0x04ul
#define PDL_DTC_UPDATE_DESTINATION	0x08ul
#define PDL_DTC_UPDATE_COUNT		0x10ul
#define PDL_DTC_UPDATE_BLOCK_SIZE	0x20ul

#endif
/* End of file */
