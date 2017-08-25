/*****************************************************************************
 *
 *            Copyright Andes Technology Corporation 2007-2008
 *                         All Rights Reserved.
 *
 *  Revision History:
 *
 *    Aug.21.2007     Created.
 ****************************************************************************/

/*****************************************************************************
 *
 * FILE NAME                                         VERSION
 *
 *   dmad.h                     
 *
 * DESCRIPTION
 *
 *   DMA controller driver internal supplement library.
 *
 * DATA STRUCTURES
 *
 *   None
 *
 * DEPENDENCIES
 *
 *   ag101regs.h
 *   ag101defs.h
 *
 ****************************************************************************/
#ifndef __DMAD_H__
#define __DMAD_H__

#include <hal.h>

/*****************************************************************************
 * Configuration section 
 ****************************************************************************/
/* Code size control */
#define DMAD_SMALL_FOOTPRINT	0 /* non-zero to disable extra features for small footprint */

/* Debug trace enable switch */
#define DMAD_DEBUG_TRACE	0 /* non-zero to enable debug trace message */

/* DMAD globals section */
enum DMAD_DMAC_CORE { DMAD_DMAC_AHB_CORE, DMAD_DMAC_APB_CORE };

/*
 * AHB Channel Request
 *
 * Notes for developers:
 *   These should be channel-only properties. Controller-specific properties
 *   should be separated as other driver structure or driver buildin-hardcode.
 *   If controller properties are embeded in this union, request for a channel
 *   may unexpectedly override the controller setting of the request of other
 *   channels.
 */
typedef struct DMAD_AHBCH_REQUEST_STRUCT{

	/* controller property (removed! should not exist in this struct) */
	// uint8_t	big_endian;	/* (in) currently only M0 is designed, and transfer endian is default to little */

	/* channel property */
	uint32_t	sync;		/* (in) non-zero if src and dst have different clock domain */
	uint32_t	priority;	/* (in) DMAC_CSR_CHPRI_0 (lowest) ~ DMAC_CSR_CHPRI_3 (highest) */
	uint32_t	hw_handshake;	/* (in) non-zero to enable hardware handshake mode */
	/*       (required when need multiple bursts or in chain mode?) */
	uint32_t	burst_size;	/* (in) DMAC_CSR_SIZE_1 ~ DMAC_CSR_SIZE_256 */

	/* source property */
	uint32_t	src_width;	/* (in) DMAC_CSR_WIDTH_8, DMAC_CSR_WIDTH_16, or DMAC_CSR_WIDTH_32 */
	uint32_t	src_addr_ctrl;	/* (in) DMAC_CSR_AD_INC, DMAC_CSR_AD_DEC, or DMAC_CSR_AD_FIX */
	uint32_t	src_reqn;	/* (in) DMAC_REQN_xxx (also used to help determine channel number) */
	uint32_t        src_index;

	/* destination property */
	uint32_t	dst_width;	/* (in) DMAC_CSR_WIDTH_8, DMAC_CSR_WIDTH_16, or DMAC_CSR_WIDTH_32 */
	uint32_t	dst_addr_ctrl;	/* (in) DMAC_CSR_AD_INC, DMAC_CSR_AD_DEC, or DMAC_CSR_AD_FIX */
	uint32_t	dst_reqn;	/* (in) DMAC_REQN_xxx (also used to help determine channel number) */
	uint32_t        dst_index;

} DMAD_AHBCH_REQUEST;

/*
 * APB Channel Request
 *
 * Notes for developers:
 *   These should be channel-only properties. Controller-specific properties
 *   should be separated as other driver structure or driver buildin-hardcode.
 *   If controller properties are embeded in this union, request for a channel
 *   may unexpectedly override the controller setting of the request of other
 *   channels.
 */
typedef struct DMAD_APBCH_REQUEST_STRUCT{

	/* controller property (removed! should not exist in this struct) */

	/* channel property */
	uint32_t	burst_mode;	/* (in) Burst mode (0: no burst 1-, 1: burst 4- data cycles per dma cycle) */
	uint32_t	data_width;	/* (in) APBBR_DATAWIDTH_4(word), APBBR_DATAWIDTH_2(half-word), APBBR_DATAWIDTH_1(byte) */

	/* source property */
	uint32_t	src_addr_ctrl;	/* (in) APBBR_ADDRINC_xxx */
	uint32_t	src_reqn;	/* (in) APBBR_REQN_xxx (also used to help determine bus selection) */
	uint32_t        src_index;

	/* destination property */
	uint32_t	dst_addr_ctrl;	/* (in) APBBR_ADDRINC_xxx */
	uint32_t	dst_reqn;	/* (in) APBBR_REQN_xxx (also used to help determine bus selection) */
	uint32_t        dst_index;

} DMAD_APBCH_REQUEST;

/* Channel Request Descriptor */
typedef struct DMAD_CHANNEL_REQUEST_DESC_STRUCT{

	uint32_t	controller;	/* (in)  Use DMA controller in AHB or APB - one of the enum value of DMAD_DMAC_CORE */
	uint32_t	channel;	/* (out) Allocated/granted channel */

	void		*drq;		/* (out) Handle to DMA request queue (ptr to DMAD_DRQ, internal use) */

	/*
	 * Properties for channel-alloc request
	 * Notes for developers:
	 *   These should be channel-only properties. Controller-specific properties
	 *   should be separated as other driver structure or driver buildin-hardcode.
	 *   If controller properties are embeded in this union, request for a channel
	 *   may unexpectedly override the controller setting of the request of other
	 *   channels.
	 */
	union {
		DMAD_AHBCH_REQUEST ahbch_req; /* (in)  parameters for AHB DMAC channel request */
		DMAD_APBCH_REQUEST apbch_req; /* (in)  parameters for APB Bridge embeded DMA conteoller channel request */
	};

} DMAD_CHANNEL_REQUEST_DESC;


enum DMAD_DRB_STATE{

	DMAD_DRB_STATE_FREE = 0,
	DMAD_DRB_STATE_READY,
	DMAD_DRB_STATE_SUBMITTED,
	DMAD_DRB_STATE_TRANSFERRING,
	DMAD_DRB_STATE_COMPLETED,
	DMAD_DRB_STATE_ERROR,
	DMAD_DRB_STATE_ABORT,
};

/* DMA request block */
typedef struct DMAD_DRB_STRUCT{

	uint32_t	prev;		/* (internal) Linked list previous node */
	uint32_t	next;		/* (internal) Linked list next node */
	uint32_t	node;		/* (internal) Linked list this node */

	uint32_t	state;		/* (out) DRB's current state in the whole submission cycle. */

	void		*src_addr;	/* (in)  Source address in this request */

	void		*dst_addr;	/* (in)  Destination address in this submission request */

	uint32_t	req_size;	/* (in)  AHB DMA (12 bits): 0 ~ 4095, unit is number of "data width" */
					/*       APB DMA (24 bits): 0 ~ 16M-1, unit is number of "data width * burst size" */
	uint32_t	transfer_size;	/* req_size * data_width*/
	hal_semaphore_t	*completion_sem;/* (in)  Application supplied semaphore to signal completion of this */
					/*       DMA request block.  Specify null to by-pass this mechanism. */
	void		(*psp)(void*);	/* pre-submission programming */
	void		(*rcp)(void*);	/* completion-of-submission programming */
	void		*data;
	uint32_t        src_index;       /* to indicate it's device or memory */
        uint32_t        dst_index;       /* to indicate it's device or memory */
//	uint32_t	src_reqn;	/* to indicate it's device or memory */
//	uint32_t	dst_reqn;	/* to indicate it's device or memory */

} DMAD_DRB;

enum DMAD_CHDIR
{
	DMAD_DIR_A0_TO_A1       = 0,
	DMAD_DIR_A1_TO_A0       = 1,
};
/* Debug Trace Mechanism */
#if (DMAD_DEBUG_TRACE)

#define DMAD_TRACE(x)      printf x
#define DMAD_STRACE(x)     printf x

#else /* DMAD_DEBUG_TRACE */

#define DMAD_TRACE(x)
#define DMAD_STRACE(x)

#endif /* DMAD_DEBUG_TRACE */


/*****************************************************************************
 * DMAD Driver Interface
 *
 * [Structures]
 *
 * [Functions]
 *
 *
 ****************************************************************************/

extern uint32_t _dmad_channel_alloc(DMAD_CHANNEL_REQUEST_DESC *ch_req, uint8_t init);
extern uint32_t _dmad_channel_free(const DMAD_CHANNEL_REQUEST_DESC *ch_req);
extern uint32_t _dmad_channel_init(const DMAD_CHANNEL_REQUEST_DESC *ch_req);
extern uint32_t _dmad_channel_enable(const DMAD_CHANNEL_REQUEST_DESC *ch_req, uint8_t enable);

extern uint32_t _dmad_alloc_drb(DMAD_CHANNEL_REQUEST_DESC *ch_req, DMAD_DRB **drb);
extern uint32_t _dmad_free_drb(DMAD_CHANNEL_REQUEST_DESC *ch_req, DMAD_DRB *drb);

extern uint32_t _dmad_submit_request(DMAD_CHANNEL_REQUEST_DESC *ch_req, DMAD_DRB *drb);
extern uint32_t _dmad_cancel_request(DMAD_CHANNEL_REQUEST_DESC *ch_req, DMAD_DRB *drb);
extern uint32_t _dmad_wait(DMAD_CHANNEL_REQUEST_DESC *ch_req);

extern uint32_t _dmad_get_reqn(uint32_t dma_controller, uint32_t device);

enum ahp_reqn_index_t {
        AHB_NONE,
        AHB_CFC,
        AHB_SSP,
        AHB_UART1TX,
        AHB_UART1RX,
        AHB_I2SAC97,
        AHB_USB,
        AHB_EXT0,
        AHB_EXT1,
        AHB_SSP1TX,
        AHB_SSP1RX,
        AHB_UART2TX,
        AHB_UART2RX,
        AHB_UART4TX,
        AHB_UART4RX,
        AHB_SDC,
        AHB_SSP2TX,
        AHB_SSP2RX,
        AHB_USB_2_0,
        AHB_USB_1_1_EP1,
        AHB_USB_1_1_EP2,
        AHB_USB_1_1_EP3,
        AHB_USB_1_1_EP4
};

enum apb_reqn_index_t {
        APB_NONE,
        APB_CFC,
        APB_SSP,
        APB_BTUART,
        APB_I2SAC97,
        APB_STUART,
        APB_I2S,
        APB_SSP2,
        APB_EXT0,
        APB_EXT1,
        APB_SSP1TX,
        APB_SSP1RX,
        APB_UART2TX,
        APB_UART2RX,
        APB_UART4TX,
        APB_UART4RX,
        APB_SDC,
        APB_SSP2TX,
        APB_SSP2RX,
        APB_USB_2_0,
        APB_USB_1_1_EP1,
        APB_USB_1_1_EP2,
        APB_USB_1_1_EP3,
        APB_USB_1_1_EP4,
        APB_MAX
};

#endif /* __DMAD_H__ */
