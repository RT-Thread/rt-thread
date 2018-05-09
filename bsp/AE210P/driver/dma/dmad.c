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
 *   dmad.c
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
 *   dmad.h
 *
 ****************************************************************************/
#include "dmad.h"
#include "cache.h"
#include "bsp_hal.h"

// #define DMAD_POLLING
#define DMAD_AHB_MAX_CHANNELS		DMAC_MAX_CHANNELS
#define DMAD_APB_MAX_CHANNELS		APBBR_DMA_MAX_CHANNELS
#define DMAD_DRB_POOL_SIZE		128 /*  64 // 128*/

//#define DMAD_HISR_PRIORITY		0           // 0: highest, 2: lowest
#define DMAD_HISR_STACK_SIZE		4096        // Please align to 32-bit

#ifdef CONFIG_PLAT_AG101P_4GB
	#define NTC0_BONDER_START	0x00000000
	#define NTC0_BONDER_END		0x40000000
#else
	#define NTC0_BONDER_START	0x00000000
	#define NTC0_BONDER_END		0x00400000
#endif

/*
 * DMA module is shared between drivers and has no specific
 * initialization entry point.  For this reason, it's stack
 * pool is declared in the global data or bss section.
 */
static uint32_t dmad_hisr_stack[DMAD_HISR_STACK_SIZE];

/* Driver data structure, one instance per system */
typedef struct DMAD_DATA_STRUCT{

	/* Driver data initialization flag */
	uint32_t	init;				/* init flag for this object */
	uint32_t	drq_pool_mutex_init;		/* init flag for DMA queue pool access control object */
	uint32_t	ahb_lisr_registered;		/* init flag for AHB DMA LISR */
	uint32_t	apb_lisr_registered;		/* init flag for APB DMA LISR */
	uint32_t	hisr_registered;		/* init flag for HISR */

	/*  DMA queue pool access control object */
	hal_mutex_t	drq_pool_mutex;			/* Mutex for access control of DRQ (DMA Request Queue) pool between tasks */

	/* DMA HISR resources */
	hal_bh_t	hisr;				/* HISR kernel object, used to perform deffered tasks of DMA LISR */
	uint32_t	hisr_as;			/* HISR activation state (for the single HISR to identify who activated it) */

} DMAD_DATA;

/* Driver data structure instance, one instance per system */
static DMAD_DATA dmad;

/* DMA request queue, one instance per channel */
typedef struct DMAD_DRQ_STRUCT{

	uint32_t	allocated;			/* Flag to indicate the channel allocation status */
	DMAD_DATA	*dmad;				/* Pointer to driver object (DMAD_DATA) */

	uint32_t	channel_base;			/* DMA channel register base address */

	hal_mutex_t	drb_pool_mutex;			/* Mutex for access control of DRB (DMA Request Block) pool between tasks */
	DMAD_DRB	drb_pool[DMAD_DRB_POOL_SIZE];	/* DRB (DMA Request Block) pool for this channel */
	hal_semaphore_t	drb_sem;

	uint32_t	fre_head;			/* Free(un-allocated, completed) DRB linked list head */
	uint32_t	fre_tail;			/* Free(un-allocated, completed) DRB linked list tail */

	uint32_t	rdy_head;			/* Ready(allocated, un-submitted) DRB linked list head */
	uint32_t	rdy_tail;			/* Ready(allocated, un-submitted) DRB linked list tail */

	uint32_t	sbt_head;			/* Submitted DRB linked list head */
	uint32_t	sbt_tail;			/* Submitted DRB linked list tail */

	uint32_t	cpl_head;			/* Completed (those need to notify client) DRB linked list head */
	uint32_t	cpl_tail;			/* Completed (those need to notify client) DRB linked list tail */

	/*
	 * cache writeback function
	 *
	 * source    destination   writeback                invalidate              function
	 * ---------------------------------------------------------------------------------------------------
	 * memory -> memory        v (for src data)     v (for dest readback)   NDS_DCache_Invalidate_Flush()
	 * device -> memory        v (for invalidate)   v (for dest readback)   NDS_DCache_Invalidate_Flush()
	 * memory -> device        v (for src data)     x                       NDS_DCache_Flush()
	 * device -> device        x                    x                       null
	 */
	void		(*dc_writeback)(unsigned long start, unsigned long end);
	void		(*dc_invalidate)(unsigned long start, unsigned long end);

} DMAD_DRQ;

/* DMA queue for AHB DMA channels */
static DMAD_DRQ ahb_drq_pool[DMAD_AHB_MAX_CHANNELS];

/* DMA queue for APB DMA channels */
static DMAD_DRQ apb_drq_pool[DMAD_APB_MAX_CHANNELS];

/* AHB DMAC channel re-route table structure */
typedef struct _DMAD_AHB_CH_ROUTE {

//	uint32_t dev_reqn; /* device req/gnt number */
	uint32_t route_cr; /* routing control register address */

} DMAD_AHB_CH_ROUTE;

/* AHB DMAC channel re-route table.  Indexed by AHB DMAC req/ack number. */
static DMAD_AHB_CH_ROUTE dmad_ahb_ch_route_table[] = {
	{ 0 },
	{ PMU_CFC_REQACK_CFG },		/* CFC REQ/ACK connection configuration register */
	{ PMU_SSP1_REQACK_CFG },	/* SSP1 REQ/ACK connection configuration register */
	{ PMU_UART1TX_REQACK_CFG },	/* UART1 TX REQ/ACK connection configuration register */
	{ PMU_UART1RX_REQACK_CFG },	/* UART1 RX REQ/ACK connection configuration register */
	{ PMU_UART2TX_REQACK_CFG },	/* UART2 TX REQ/ACK connection configuration register */
	{ PMU_UART2RX_REQACK_CFG },	/* UART2 RX REQ/ACK connection configuration register */
	{ PMU_SDC_REQACK_CFG },		/* SDC REQ/ACK connection configuration register */
	{ PMU_I2SAC97_REQACK_CFG },	/* I2S/AC97 REQ/ACK connection configuration register */
	{ 0 },
	{ 0 },
	{ PMU_USB_REQACK_CFG },		/* USB 2.0 REQ/ACK connection configuration register */
	{ 0 },
	{ 0 },
	{ PMU_EXT0_REQACK_CFG },	/* External device0 REQ/ACK connection configuration register */
	{ PMU_EXT1_REQACK_CFG },	/* External device1 REQ/ACK connection configuration register */
};

/* APB Bridge DMA request number re-route table */
typedef struct _DMAD_APB_REQN_ROUTE{

//	uint32_t apb_reqn;	/* APB device req/gnt number */
	uint32_t ahb_reqn;	/* AHB DMAC req/ack number */

	uint32_t bus_sel;	/* Address selection: APBBR_ADDRSEL_APB(0) or APBBR_ADDRSEL_AHB(1) */
} DMAD_APB_REQN_ROUTE;

/* APB Bridge DMA request number re-route table.  Indexed by APB DMA req/gnt number. */
static DMAD_APB_REQN_ROUTE dmad_apb_reqn_route_table[] = {
	{ 0x00, APBBR_ADDRSEL_AHB }, /* APBBR_REQN_NONE */
	{ 0x01, APBBR_ADDRSEL_APB }, /* APBBR_REQN_CFC */
	{ 0x02, APBBR_ADDRSEL_APB }, /* APBBR_REQN_SSP */
	{ 0x00, APBBR_ADDRSEL_AHB }, /* APB reserved */
	{ 0x05, APBBR_ADDRSEL_APB }, /* APBBR_REQN_BTUART (AHB TX reqn: 5, AHB RX reqn: 6) */
	{ 0x07, APBBR_ADDRSEL_APB }, /* APBBR_REQN_SDC */
	{ 0x08, APBBR_ADDRSEL_APB }, /* APBBR_REQN_I2SAC97 */
	{ 0x00, APBBR_ADDRSEL_AHB }, /* APB reserved */
	{ 0x03, APBBR_ADDRSEL_APB }, /* APBBR_REQN_STUART (AHB TX reqn: 3, AHB RX reqn: 4) */
	{ 0x00, APBBR_ADDRSEL_AHB }, /* APB reserved (comment out following fields to save code size) */
	{ 0x00, APBBR_ADDRSEL_AHB }, /* APB reserved */
	{ 0x00, APBBR_ADDRSEL_AHB }, /* APB reserved */
	{ 0x00, APBBR_ADDRSEL_AHB }, /* APB reserved */
	{ 0x00, APBBR_ADDRSEL_AHB }, /* APB reserved */
	{ 0x00, APBBR_ADDRSEL_AHB }, /* APB reserved */
	{ 0x00, APBBR_ADDRSEL_AHB }, /* APB reserved */
};

/* AHB DMA Request number */
/* Used to record DMA request numbers in different platform */
typedef struct _APB_DMA_REQN {

        uint32_t xc5_reqn;
        uint32_t xc7_reqn;

} APB_DMA_REQN;

static APB_DMA_REQN apb_dma_reqn_table[] = {

        {APBBR_REQN_NONE,       APBBR_REQN_NONE},//APB_REQN_NONE
        /* REQN in XC5 */
        {XC5_APBBR_REQN_CFC,      APBBR_REQN_RESERVED},//APB_REQN_CFC
        {XC5_APBBR_REQN_SSP,      APBBR_REQN_RESERVED},//APB_REQN_SSP
        {XC5_APBBR_REQN_BTUART,   APBBR_REQN_RESERVED},//APBBR_REQN_BTUART
        {XC5_APBBR_REQN_I2SAC97,  XC7_APBBR_REQN_I2SAC97},//APB_REQN_I2SAC97
        {XC5_APBBR_REQN_STUART,   APBBR_REQN_RESERVED},//APB_REQN_STUART
        {XC5_APBBR_REQN_I2S,      APBBR_REQN_RESERVED},//APB_REQN_I2S
        {XC5_APBBR_REQN_SSP2,     APBBR_REQN_RESERVED},//APB_REQN_SSP2
        {APBBR_REQN_RESERVED,     XC7_APBBR_REQN_EXTREQ0},//APB_REQN_EXT0
        {APBBR_REQN_RESERVED,     XC7_APBBR_REQN_EXTREQ1},//APB_REQN_EXT1
        /* REQN in XC7 */
        {APBBR_REQN_RESERVED,     XC7_APBBR_REQN_SSP1TX},//APB_REQN_SSP1TX
        {APBBR_REQN_RESERVED,     XC7_APBBR_REQN_SSP1RX},//APB_REQN_SSP1RX
        {APBBR_REQN_RESERVED,     XC7_APBBR_REQN_UART2TX},//APB_REQN_UART2TX
        {APBBR_REQN_RESERVED,     XC7_APBBR_REQN_UART2RX},//APB_REQN_UART2RX
        {APBBR_REQN_RESERVED,     XC7_APBBR_REQN_UART4TX},//APB_REQN_UART4TX
        {APBBR_REQN_RESERVED,     XC7_APBBR_REQN_UART4RX},//APB_REQN_UART4RX
        {XC5_APBBR_REQN_SDC,      XC7_APBBR_REQN_SDC},//APB_REQN_SDC
        {APBBR_REQN_RESERVED,     XC7_APBBR_REQN_SSP2TX},//APB_REQN_SSP2TX
        {APBBR_REQN_RESERVED,     XC7_APBBR_REQN_SSP2RX},//APB_REQN_SSP2RX
        {APBBR_REQN_RESERVED,     XC7_APBBR_REQN_USB_2_0},//APB_REQN_USB_2_0
        {APBBR_REQN_RESERVED,     XC7_APBBR_REQN_USB_1_1_EP1},//APB_REQN_USB_1_1_EP1
        {APBBR_REQN_RESERVED,     XC7_APBBR_REQN_USB_1_1_EP2},//APB_REQN_USB_1_1_EP2
        {APBBR_REQN_RESERVED,     XC7_APBBR_REQN_USB_1_1_EP3},//APB_REQN_USB_1_1_EP3
        {APBBR_REQN_RESERVED,     XC7_APBBR_REQN_USB_1_1_EP4},//AHB_REQN_USB_1_1_EP4
        {XC5_APBBR_REQN_MAX,      XC7_APBBR_REQN_MAX},//APB_REQN_MAX
};

/* AHB DMA Request number */
/* Used to record DMA request numbers in different platform */
typedef struct _AHB_DMA_REQN {

        uint32_t xc5_reqn;
        uint32_t xc7_reqn;

} AHB_DMA_REQN;

static AHB_DMA_REQN ahb_dma_reqn_table[] = {

        {AHB_REQN_NONE,         AHB_REQN_NONE},//AHB_REQN_NONE
        /* REQN in XC5 */
        {XC5_AHB_REQN_CFC,      AHB_REQN_RESERVED},//AHB_REQN_CFC
        {XC5_AHB_REQN_SSP,      AHB_REQN_RESERVED},//AHB_REQN_SSP
        {XC5_AHB_REQN_UART1TX,  AHB_REQN_RESERVED},//AHB_REQN_UART1TX
        {XC5_AHB_REQN_UART1RX,  AHB_REQN_RESERVED},//AHB_REQN_UART1RX
        {XC5_AHB_REQN_I2SAC97,  XC7_AHB_REQN_I2SAC97},//AHB_REQN_I2SAC97
        {XC5_AHB_REQN_USB,      AHB_REQN_RESERVED},//AHB_REQN_USB
        {XC5_AHB_REQN_EXT0,     XC7_AHB_REQN_EXTREQ0},//AHB_REQN_EXT0
        {XC5_AHB_REQN_EXT1,     XC7_AHB_REQN_EXTREQ1},//AHB_REQN_EXT1
        /* REQN in XC7 */
        {AHB_REQN_RESERVED,             XC7_AHB_REQN_SSP1TX},//AHB_REQN_SSP1TX
        {AHB_REQN_RESERVED,             XC7_AHB_REQN_SSP1RX},//AHB_REQN_SSP1RX
        {AHB_REQN_RESERVED,             XC7_AHB_REQN_UART2TX},//AHB_REQN_UART2TX
        {AHB_REQN_RESERVED,             XC7_AHB_REQN_UART2RX},//AHB_REQN_UART2RX
        {AHB_REQN_RESERVED,             XC7_AHB_REQN_UART4TX},//AHB_REQN_UART4TX
        {AHB_REQN_RESERVED,             XC7_AHB_REQN_UART4RX},//AHB_REQN_UART4RX
        {XC5_AHB_REQN_SDC,      XC7_AHB_REQN_SDC},//AHB_REQN_SDC
        {AHB_REQN_RESERVED,             XC7_AHB_REQN_SSP2TX},//AHB_REQN_SSP2TX
        {AHB_REQN_RESERVED,             XC7_AHB_REQN_SSP2RX},//AHB_REQN_SSP2RX
        {AHB_REQN_RESERVED,             XC7_AHB_REQN_USB_2_0},//AHB_REQN_USB_2_0
        {AHB_REQN_RESERVED,             XC7_AHB_REQN_USB_1_1_EP1},//AHB_REQN_USB_1_1_EP1
        {AHB_REQN_RESERVED,             XC7_AHB_REQN_USB_1_1_EP2},//AHB_REQN_USB_1_1_EP2
        {AHB_REQN_RESERVED,             XC7_AHB_REQN_USB_1_1_EP3},//AHB_REQN_USB_1_1_EP3
        {AHB_REQN_RESERVED,             XC7_AHB_REQN_USB_1_1_EP4},//AHB_REQN_USB_1_1_EP4
};

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_get_reqn
 *
 * DESCRIPTION
 *
 *   Get DMA request number from various platform.
 *
 * INPUTS
 *
 *   dma_controller	: (in) AHB or APB
 *   device		: (in) Device and peripheral.
 *
 * OUTPUTS
 *
 *   none
 *
 ****************************************************************************/
uint32_t _dmad_get_reqn(uint32_t dma_controller, uint32_t device){

	uint32_t reqn;
	uint32_t platform_id = IN32(PMU_IDNMBR0);

	if (dma_controller == DMAD_DMAC_APB_CORE){	/* APB */
		if ((platform_id & PRODUCT_ID_MASK) == AG101P_EMERALD)
			reqn = apb_dma_reqn_table[device].xc7_reqn;
		else
			reqn = apb_dma_reqn_table[device].xc5_reqn;
	} else {					/* AHB */
		if ((platform_id & PRODUCT_ID_MASK) == AG101P_EMERALD)
                	reqn = ahb_dma_reqn_table[device].xc7_reqn;
        	else
                	reqn = ahb_dma_reqn_table[device].xc5_reqn;
	}
	
	return reqn;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_detach_node
 *
 * DESCRIPTION
 *
 *   Detach a DRB node from a specified list.  The list is acknowledged in the
 *   form of a head node and a tail one.
 *
 * INPUTS
 *
 *   drb_pool   : (in) The DRB pool of a DMA queue for a DMA channel
 *   head       : (in/out) Pointer to the head node of the list
 *   tail       : (in/out) Pointer to the tail node of the list
 *   node       : (in) The node to detach from the list
 *
 * OUTPUTS
 *
 *   none
 *
 ****************************************************************************/
static void _dmad_detach_node(DMAD_DRB *drb_pool, uint32_t *head, uint32_t *tail, uint32_t node){

	if (drb_pool[node].prev != 0){

		/* prev->next = this->next (= 0, if this is a tail) */
		drb_pool[drb_pool[node].prev].next = drb_pool[node].next;
	}
	else {
		/* this node is head, move head to next node (= 0, if this is the only one node) */
		*head = drb_pool[node].next;
	}

	if (drb_pool[node].next != 0){

		/* next->prev = this->prev (= 0, if this is a head) */
		drb_pool[drb_pool[node].next].prev = drb_pool[node].prev;
	}
	else {
		/* this node is tail, move tail to previous node (= 0, if this is the only one node) */
		*tail = drb_pool[node].prev;
	}

	drb_pool[node].prev = drb_pool[node].next = 0;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_detach_head
 *
 * DESCRIPTION
 *
 *   Detach a DRB node from the head of a specified list.  The list is
 *   acknowledged in the form of a head node and a tail one.
 *
 * INPUTS
 *
 *   drb_pool   : (in) The DRB pool of a DMA queue for a DMA channel
 *   head       : (in/out) Pointer to the head node of the list
 *   tail       : (in/out) Pointer to the tail node of the list
 *   drb        : (out) Reference to the detached node pointer
 *
 * OUTPUTS
 *
 *   none
 *
 ****************************************************************************/
static void _dmad_detach_head(DMAD_DRB *drb_pool, uint32_t *head, uint32_t *tail, DMAD_DRB **drb){

	if (*head == 0){

		*drb = HAL_NULL;
		return;
	}

	*drb = &drb_pool[*head];

	if ((*drb)->next != 0){

		/* next->prev = this->prev (= 0, if this is a head) */
		drb_pool[(*drb)->next].prev = 0;

		/* prev->next = this->next (do nothing, if this is a head) */

		/* head = this->next */
		*head = (*drb)->next;
	}
	else {
		/* head = tail = 0 */
		*head = 0;
		*tail = 0;
	}

	/* this->prev = this->next = 0 (do nothing, if save code size) */
	(*drb)->prev = (*drb)->next = 0;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_detach_tail
 *
 * DESCRIPTION
 *
 *   Detach a DRB node from the tail of a specified list.  The list is
 *   acknowledged in the form of a head node and a tail one.
 *
 * INPUTS
 *
 *   drb_pool   : (in) The DRB pool of a DMA queue for a DMA channel
 *   head       : (in/out) Pointer to the head node of the list
 *   tail       : (in/out) Pointer to the tail node of the list
 *   drb        : (out) Reference to the detached node pointer
 *
 * OUTPUTS
 *
 *   none
 *
 ****************************************************************************/
static inline void _dmad_detach_tail(DMAD_DRB *drb_pool, uint32_t *head, uint32_t *tail, DMAD_DRB **drb){

	if (*tail == 0){

		*drb = HAL_NULL;
		return;
	}

	*drb = &drb_pool[*tail];

	if ((*drb)->prev != 0){

		/* prev->next = this->next (= 0, if this is a tail) */
		drb_pool[(*drb)->prev].next = 0;

		/* next->prev = this->prev (do nothing, if this is a tail) */

		/* tail = this->prev */
		*tail = (*drb)->prev;
	}
	else {
		/* head = tail = 0 */
		*head = 0;
		*tail = 0;
	}

	/* this->next = this->prev = 0 (do nothing, if save code size) */
	(*drb)->prev = (*drb)->next = 0;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_attach_head
 *
 * DESCRIPTION
 *
 *   Attach a DRB node to the head of a specified list.  The list is
 *   acknowledged in the form of a head node and a tail one.
 *
 * INPUTS
 *
 *   drb_pool   : (in) The DRB pool of a DMA queue for a DMA channel
 *   head       : (in/out) Pointer to the head node of the list
 *   tail       : (in/out) Pointer to the tail node of the list
 *   drb        : (in) The node number of the node to attach
 *
 * OUTPUTS
 *
 *   none
 *
 ****************************************************************************/
static inline void _dmad_attach_head(DMAD_DRB *drb_pool, uint32_t *head, uint32_t *tail, uint32_t node){

	if (*head != 0){

		drb_pool[*head].prev = node;	/* head->prev = this */
		drb_pool[node].next = *head;	/* this->next = head */
		drb_pool[node].prev = 0;	/* this->prev = 0 */
		*head = node;			/* head = node */
	}
	else {
		*head = *tail = node;		/* head = tail = node */
		drb_pool[node].prev = drb_pool[node].next = 0;
	}
}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_attach_tail
 *
 * DESCRIPTION
 *
 *   Attach a DRB node to the tail of a specified list.  The list is
 *   acknowledged in the form of a head node and a tail one.
 *
 * INPUTS
 *
 *   drb_pool   : (in) The DRB pool of a DMA queue for a DMA channel
 *   head       : (in/out) Pointer to the head node of the list
 *   tail       : (in/out) Pointer to the tail node of the list
 *   drb        : (in) The node number of the node to attach
 *
 * OUTPUTS
 *
 *   none
 *
 ****************************************************************************/
static void _dmad_attach_tail(DMAD_DRB *drb_pool, uint32_t *head, uint32_t *tail, uint32_t node){

	if (*tail != 0){

		drb_pool[*tail].next = node;	/* tail->next = this */
		drb_pool[node].prev = *tail;	/* this->prev = tail */
		drb_pool[node].next = 0;	/* this->next = 0 */
		*tail = node;			/* tail = node */
	}
	else {
		*head = *tail = node;		/* head = tail = node */
		drb_pool[node].prev = drb_pool[node].next = 0;
	}
}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_ahb_lisr
 *
 * DESCRIPTION
 *
 *   This is the ISR that services all AHB DMA channels on the NDS32
 *   Integrator.
 *
 * NOTE
 *   Currently this ISR processes one channel at a time.  This replies the
 *   assumption that the ISR will be invoked again as long as it's status
 *   bit remains not-cleared, if interrupts for multiple channels happens
 *   simultaneously.
 *
 *   [todo] Above assumption may not be the real world case. Check it and
 *   implement processing of multiple channels at once in the ISR, if
 *   necessary.
 *
 * INPUTS
 *
 *   vector     : Interrupt vector number
 *
 * OUTPUTS
 *
 *   none
 *
 ****************************************************************************/
static void _dmad_ahb_lisr(int vector){

	DMAD_DRQ	*drq;
	DMAD_DRB	*drb;
	uint32_t	channel;	/* interrupt channel number */
	uint8_t		tc_int = 0;	/* interrupt reason is terminal count */
	uint8_t		err_int = 0;	/* interrupt reason is DMA error */
	//uint8_t		abt_int = 0;	/* interrupt reason is abort DMA transfer of this channel */
	uint32_t	prv_msk = 0;

	if (vector != INTC_DMA_BIT)
		hal_system_error(HAL_ERR_UNHANDLED_INTERRUPT);


	prv_msk = hal_intc_irq_mask(IRQ_DMA_VECTOR);	
	/* Check DMA status register to get channel number */
	for (channel = 0; channel < DMAD_AHB_MAX_CHANNELS; ++channel){

		if (GETB32(DMAC_INT_TC, channel)){

			tc_int = 1; /* Mark as TC int */
			SETB32(DMAC_INT_TC_CLR, channel); /* DMAC INT TC status clear */
			hal_intc_irq_clean(IRQ_DMA_VECTOR);
			break;
		}
	}

	/* Perform DMA error checking if no valid channel was found who assert the TC signal. */
	if (channel == DMAD_AHB_MAX_CHANNELS){

		for (channel = 0; channel < DMAD_AHB_MAX_CHANNELS; ++channel){

			if (GETB32(DMAC_INT_ERRABT, channel + DMAC_INT_ERR_SHIFT)){

				err_int = 1; /* Mark as ERR int */
				SETB32(DMAC_INT_ERRABT_CLR, channel + DMAC_INT_ERR_CLR_SHIFT); /* DMAC INT ERR status clear */
				hal_intc_irq_clean(IRQ_DMA_VECTOR);
				break;
			}
		}

		if (channel == DMAD_AHB_MAX_CHANNELS){

			for (channel = 0; channel < DMAD_AHB_MAX_CHANNELS; ++channel){

				if (GETB32(DMAC_INT_ERRABT, channel + DMAC_INT_ABT_SHIFT)){

					//abt_int = 1; /* Mark as ABT int */
					SETB32(DMAC_INT_ERRABT_CLR, channel + DMAC_INT_ABT_CLR_SHIFT); /* DMAC INT ABT status clear */
					hal_intc_irq_clean(IRQ_DMA_VECTOR);	
					break;
				}
			}

			if (channel == DMAD_AHB_MAX_CHANNELS){

				/* Unknown reason ... (check why) */
				hal_system_error(HAL_ERR_UNHANDLED_INTERRUPT); /*return; */
			}
		}
	}

	/* Lookup channel's DRQ (DMA Request Queue) */
	drq = (DMAD_DRQ *)&ahb_drq_pool[channel];

	/* DMAC */
	/* Stop DMA channel temporarily */
	CLRB32(drq->channel_base + DMAC_CSR_OFFSET, DMAC_CSR_CH_EN_BIT);

	/*
	 * Lookup/detach latest submitted DRB (DMA Request Block) from
	 * the DRQ (DMA Request Queue), so ISR could kick off next DRB
	 */
	_dmad_detach_head(drq->drb_pool, &drq->sbt_head, &drq->sbt_tail, &drb);
	if (drb == HAL_NULL){

		/* Check why DMA is triggered while submitted list is empty. */
		hal_system_error(HAL_ERR_UNHANDLED_INTERRUPT); /*return; */
	}

	/* Enable nested interrupt */
	GIE_ENABLE();

	/* Notify that new node is going to be available in the free list */
	if (drb->completion_sem != HAL_NULL){

		dmad.hisr_as |= (1 << channel);	/* [15:0] AHB channel indicator */
		hal_raise_bh(&dmad.hisr); /* Call HISR to complete deferred tasks */
	}
	/* Process DRBs according to interrupt reason */
	if (tc_int){

		/* Mark DRB state as completed */
		drb->state = DMAD_DRB_STATE_COMPLETED;

		/* destination is memory */
		if (drq->dc_invalidate != HAL_NULL && drb->dst_index == DMAC_REQN_NONE) 
			drq->dc_invalidate((unsigned long)(drb->dst_addr),
				           (unsigned long)(drb->dst_addr) + (unsigned long)(drb->transfer_size));
		
		_dmad_attach_tail(drq->drb_pool, &drq->cpl_head, &drq->cpl_tail, drb->node);

		/* Check whether there are pending requests in the DRQ */
		if (drq->sbt_head != 0){

			drb = &drq->drb_pool[drq->sbt_head]; /* Lookup next DRB (DMA Request Block) */

			/* pre-submission-programming */
			if (drb->psp)
				drb->psp(drb->data);

			/* Kick-off DMA for next DRB */
			/* - Source and destination address */
			OUT32(drq->channel_base + DMAC_SRC_ADDR_OFFSET, drb->src_addr);
			OUT32(drq->channel_base + DMAC_DST_ADDR_OFFSET, drb->dst_addr);

			/* - Transfer size (in units of source width) */
			OUT32(drq->channel_base + DMAC_SIZE_OFFSET, drb->req_size);

			/* - Re-enable DMA channel */
			SETB32(drq->channel_base + DMAC_CSR_OFFSET, DMAC_CSR_CH_EN_BIT);
		}
	}
	else if (err_int){

		/* Mark DRB state as error */
		drb->state = DMAD_DRB_STATE_ERROR;

		_dmad_attach_tail(drq->drb_pool, &drq->cpl_head, &drq->cpl_tail, drb->node);

		/* Check whether there are pending requests in the DRQ */
		if (drq->sbt_head != 0){

			/* Lookup next DRB (DMA Request Block) */
			drb = &drq->drb_pool[drq->sbt_head];

			/* pre-submission-programming */
			if (drb->psp)
				drb->psp(drb->data);

			/*
			 * Kick-off DMA for next DRB
			 */

			/* Source and destination address */
			OUT32(drq->channel_base + DMAC_SRC_ADDR_OFFSET, drb->src_addr);
			OUT32(drq->channel_base + DMAC_DST_ADDR_OFFSET, drb->dst_addr);

			/* Transfer size (in units of source width) */
			OUT32(drq->channel_base + DMAC_SIZE_OFFSET, drb->req_size);

			/* Re-enable DMA channel */
			SETB32(drq->channel_base + DMAC_CSR_OFFSET, DMAC_CSR_CH_EN_BIT);
		}
	}
	else { /* abt_int */

		/* Remove all pending requests in the queue */
		while (1){

			/* Mark DRB state as abort */
			drb->state = DMAD_DRB_STATE_ABORT;

			_dmad_attach_tail(drq->drb_pool, &drq->cpl_head, &drq->cpl_tail, drb->node);

			/* Detach next submitted DRB (DMA Request Block) from the DRQ (DMA Request Queue) */
			_dmad_detach_head(drq->drb_pool, &drq->sbt_head, &drq->sbt_tail, &drb);
			if (drb == HAL_NULL)
				break;
		}
	}

#ifdef DMAD_POLLING
	if (dmad.hisr_as & 0x0000ffff){

		while (drq->cpl_head != 0){

			_dmad_detach_head(drq->drb_pool, &drq->cpl_head, &drq->cpl_tail, &drb);
			_dmad_attach_tail(drq->drb_pool, &drq->fre_head, &drq->fre_tail, drb->node);

			/* completion-of-submission-programming */
			if (drb->rcp)
				drb->rcp(drb->data);
		}
	}
#endif
	GIE_DISABLE();

	hal_intc_irq_unmask(prv_msk);	

}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_apb_lisr
 *
 * DESCRIPTION
 *
 *   This is the ISR that services all APB DMA channels on the NDS32
 *   Integrator.
 *
 * NOTE
 *   Currently this ISR processes one channel at a time.  This replies the
 *   assumption that the ISR will be invoked again as long as it's status
 *   bit remains not-cleared, if interrupts for multiple channels happens
 *   simultaneously.
 *
 *   [todo] Above assumption may not be the real world case. Check it and
 *   implement processing of multiple channels at once in the ISR, if
 *   necessary.
 *
 * INPUTS
 *
 *   vector     : Interrupt vector number
 *
 * OUTPUTS
 *
 *   none
 *
 ****************************************************************************/
static void _dmad_apb_lisr(int vector){

	DMAD_DRQ	*drq;
	DMAD_DRB	*drb;
	uint32_t	channel;	/* interrupt channel number */
	uint8_t		finish_int = 0;	/* interrupt reason is transfer completed */
	uint8_t		err_int = 0;	/* interrupt reason is DMA error */

	uint32_t 	prv_msk = 0;
	if (vector != INTC_APB_BIT)
		hal_system_error(HAL_ERR_UNHANDLED_INTERRUPT);

	/* Mask priority <= apb_bridge's interrupt */
	prv_msk = hal_intc_irq_mask(IRQ_APBBRIDGE_VECTOR);	

	/* Check DMA status register to get channel number & clean pending */
	for (channel = 0; channel < DMAD_APB_MAX_CHANNELS; ++channel){

		uint32_t channel_base = APBBR_DMA_BASE_CH(channel);

		if (GETB32(channel_base + APBBR_DMA_CMD_OFFSET, APBBR_DMA_FINTST_BIT)){

			/* Mark as finish int */
			finish_int = 1;

			/* APB DMA finish int status clear */
			CLRB32(channel_base + APBBR_DMA_CMD_OFFSET, APBBR_DMA_FINTST_BIT);
			hal_intc_irq_clean(IRQ_APBBRIDGE_VECTOR);	
			break;
		}
	}

	/* Perform DMA error checking if no valid channel was found who assert the finish signal 
 	 * & clean pending
 	 */
	if (channel == DMAD_APB_MAX_CHANNELS){

		for (channel = 0; channel < DMAD_APB_MAX_CHANNELS; ++channel){

			uint32_t channel_base = APBBR_DMA_BASE_CH(channel);

			if (GETB32(channel_base + APBBR_DMA_CMD_OFFSET, APBBR_DMA_ERRINTST_BIT)){

				/* Mark as error int */
				err_int = 1;

				/* APB DMA error int status clear */
				CLRB32(channel_base + APBBR_DMA_CMD_OFFSET, APBBR_DMA_ERRINTST_BIT);
				hal_intc_irq_clean(IRQ_APBBRIDGE_VECTOR);
				break;
			}
		}

		if (channel == DMAD_AHB_MAX_CHANNELS)
			hal_system_error(HAL_ERR_UNHANDLED_INTERRUPT);
	}

	/* Lookup channel's DRQ (DMA Request Queue) */
	drq = (DMAD_DRQ *)&apb_drq_pool[channel];

	/*
	 * APB
	 */

	/* Stop DMA channel temporarily */
	CLRB32(drq->channel_base + APBBR_DMA_CMD_OFFSET, APBBR_DMA_CHEN_BIT);

	/*
	 * Lookup/detach latest submitted DRB (DMA Request Block) from
	 * the DRQ (DMA Request Queue), so ISR could kick off next DRB
	 */
	_dmad_detach_head(drq->drb_pool, &drq->sbt_head, &drq->sbt_tail, &drb);
	if (drb == HAL_NULL){

		/* Check why DMA is triggered while submitted list is empty. */
		hal_system_error(HAL_ERR_UNHANDLED_INTERRUPT);
	}

	GIE_ENABLE();

	/* Notify that new node is going to be available in the free list */
	dmad.hisr_as |= (0x00010000 << channel); /* [31:16] APB channel indicator */
	hal_raise_bh(&dmad.hisr); /* Call HISR to complete deferred tasks */

	/* Process DRBs according to the cause of this interrupt */
	if (finish_int){

		/* Mark DRB state as completed */
		drb->state = DMAD_DRB_STATE_COMPLETED;

		_dmad_attach_tail(drq->drb_pool, &drq->cpl_head, &drq->cpl_tail, drb->node);

		/* destination is memory */
		if (drq->dc_invalidate != HAL_NULL && drb->dst_index == DMAC_REQN_NONE) 
			drq->dc_invalidate((unsigned long)(drb->dst_addr),
				           (unsigned long)(drb->dst_addr) + (unsigned long)(drb->transfer_size));
		
		/* Check whether there are pending requests in the DRQ */
		if (drq->sbt_head != 0){

			/* Lookup next DRB (DMA Request Block) */
			drb = &drq->drb_pool[drq->sbt_head];

			/* pre-submission-programming */
			if (drb->psp)
				drb->psp(drb->data);

			/*
			 * Kick-off DMA for next DRB
			 */

			/* Source and destination address */
			OUT32(drq->channel_base + APBBR_DMA_SAD_OFFSET, drb->src_addr);
			OUT32(drq->channel_base + APBBR_DMA_DAD_OFFSET, drb->dst_addr);

			/* - Transfer size (in units of source width) */
			OUT32(drq->channel_base + APBBR_DMA_CYC_OFFSET, drb->req_size & APBBR_DMA_CYC_MASK);

			/* - Re-enable DMA channel */
			SETB32(drq->channel_base + APBBR_DMA_CMD_OFFSET, APBBR_DMA_CHEN_BIT);
		}
	}
	else if (err_int){

		/* Remove all pending requests in the queue */
		while (1){

			/* Mark DRB state as abort */
			drb->state = DMAD_DRB_STATE_ABORT;

			_dmad_attach_tail(drq->drb_pool, &drq->cpl_head, &drq->cpl_tail, drb->node);
			_dmad_detach_head(drq->drb_pool, &drq->sbt_head, &drq->sbt_tail, &drb);

			if (drb == HAL_NULL)
				break;
		}
	}
	
#ifdef DMAD_POLLING
	if (dmad.hisr_as & 0xffff0000){

		while (drq->cpl_head != 0){

			_dmad_detach_head(drq->drb_pool, &drq->cpl_head, &drq->cpl_tail, &drb);
			_dmad_attach_tail(drq->drb_pool, &drq->fre_head, &drq->fre_tail, drb->node);

			/* completion-of-submission-programming */
			if (drb->rcp)
				drb->rcp(drb->data);
		}

		dmad.hisr_as &= ~(0x00010000 << channel);
	}
#endif
	GIE_DISABLE();
	hal_intc_irq_unmask(prv_msk);	

}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_hisr
 *
 * DESCRIPTION
 *
 *   This HISR performs the defferred tasks from LISR.
 *
 * NOTE
 *
 *   Current task list of this HISR
 *
 *     - Signal DRQ available event for waiting DRQ allocations.
 *
 * INPUTS
 *
 *   vector     : Interrupt vector number
 *
 * OUTPUTS
 *
 *   none
 *
 ****************************************************************************/
static inline void _dmad_hisr(void *param){

	DMAD_DRQ	*drq;
	DMAD_DRB	*drb = NULL;
	//uint32_t	core_intl;
	uint32_t	channel;

	while(1){

		hal_bh_t *bh = (hal_bh_t *)param;
		hal_pend_semaphore(&bh->sem, HAL_SUSPEND);

		//core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);
		
		/* Signal free-list available event */
		if ((dmad.hisr_as & 0xffff0000) != 0){
			
			/* Disable apb_bridge interrupt to avoid race condition */	
			HAL_INTC_IRQ_ATOMIC_DISABLE(IRQ_APBBRIDGE_VECTOR);
			/* APB LISR */
			for (channel = 0; channel < DMAD_APB_MAX_CHANNELS; ++channel){
				
				if (dmad.hisr_as & (0x00010000 << channel)){

					drq = (DMAD_DRQ *)&apb_drq_pool[channel];

					while (drq->cpl_head != 0){
	
						_dmad_detach_head(drq->drb_pool, &drq->cpl_head, &drq->cpl_tail, &drb);
						_dmad_attach_tail(drq->drb_pool, &drq->fre_head, &drq->fre_tail, drb->node);

						hal_post_semaphore(&drq->drb_sem);

						/* completion-of-submission-programming */
						if (drb->rcp)
							drb->rcp(drb->data);

						if(drb->completion_sem != HAL_NULL)
						{
//							puts("APB DMA HISR Complete!!!\r\n");
							hal_post_semaphore(drb->completion_sem);
							
						}
					}

					dmad.hisr_as &= ~(0x00010000 << channel);
				}
			}
			/* Re-enable apb_bridge interrupt */
			HAL_INTC_IRQ_ATOMIC_ENABLE(IRQ_APBBRIDGE_VECTOR);
		}
		else if ((dmad.hisr_as & 0x0000ffff) != 0){
			/* Disable AHB_DMA  interrupt to avoid race condition */
			HAL_INTC_IRQ_ATOMIC_DISABLE(IRQ_DMA_VECTOR);

			/* AHB LISR */
			for (channel = 0; channel < DMAD_AHB_MAX_CHANNELS; ++channel){

				if (dmad.hisr_as & (1 << channel)){

					drq = (DMAD_DRQ *)&ahb_drq_pool[channel];

					while (drq->cpl_head != 0){

						_dmad_detach_head(drq->drb_pool, &drq->cpl_head, &drq->cpl_tail, &drb);
						_dmad_attach_tail(drq->drb_pool, &drq->fre_head, &drq->fre_tail, drb->node);
						
						hal_post_semaphore(&drq->drb_sem);

						/* completion-of-submission-programming */
						if (drb->rcp)
							drb->rcp(drb->data);
					}

					if (drb->completion_sem != HAL_NULL)
						hal_post_semaphore(drb->completion_sem);

					dmad.hisr_as &= ~(1 << channel);
				}
			}
			HAL_INTC_IRQ_ATOMIC_ENABLE(IRQ_DMA_VECTOR);
		}

	//	hal_global_int_ctl(core_intl);
	}
}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_channel_alloc
 *
 * DESCRIPTION
 *
 *   This function allocates a DMA channel for client's request.  If the
 *   channel is already used by other clients, then this function will
 *   fail the allocation.
 *
 * INPUTS
 *
 *   ch_req     : Pointer to the DMA request descriptor structure
 *   init       : Specify whether to initialize the DMA channel HW if the
 *                allocation is successfull.  Clients could also postpone
 *                the initialization task to the _dmad_channel_init()
 *                routine.
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful allocation,
 *                else positive value is DMAD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _dmad_channel_alloc(DMAD_CHANNEL_REQUEST_DESC *ch_req, uint8_t init){

	uint32_t	status;
	DMAD_DRQ	*drq_iter;
	DMAD_DRB	*drb_iter;
	uint32_t	i = 0;

	if (ch_req == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	if (ch_req->controller == DMAD_DMAC_AHB_CORE)
		drq_iter = ahb_drq_pool;
	else if (ch_req->controller == DMAD_DMAC_APB_CORE)
		drq_iter = apb_drq_pool;
	else
		return HAL_ERR_NOT_PRESENT;

	/* First-time initialization for DMA queue pool access control object */
	if (dmad.drq_pool_mutex_init == 0){

		status = hal_create_mutex(&dmad.drq_pool_mutex, "drqpool");
		if (status != HAL_SUCCESS){

			DMAD_TRACE(("[dmad] failed to create drq_pool mutex!\r\n"));
			return status;
		}
		dmad.drq_pool_mutex_init = 1;
	}

	/* Obtain exclusive access to the pool of channel queues */

	if (hal_current() != HAL_NULL){

		/* Suspending is only valid to the current task -- no need to lock if invoked from HISR. */
		status = hal_wait_for_mutex(&dmad.drq_pool_mutex, HAL_SUSPEND);
		if (status != HAL_SUCCESS){

			DMAD_TRACE(("[dmad] failed to lock drq_pool! status(0x%08lx)\r\n", status));
			return status;
		}
	}

	/* Locate an available DMA channel */
	if (ch_req->controller == DMAD_DMAC_AHB_CORE){

#if 0
		/* UART - TX/RX channel is limitted */
		if ((ch_req->ahbch_req.src_index == DMAC_REQN_UART1TX) ||
				(ch_req->ahbch_req.dst_index == DMAC_REQN_UART1TX) ||
				(ch_req->ahbch_req.src_index == DMAC_REQN_UART2TX) ||
				(ch_req->ahbch_req.dst_index == DMAC_REQN_UART2TX))
		{
			/* TX channel is limitied to C/D */
			drq_iter = &ahb_drq_pool[2];
			for (i = 2; i < 4; ++i, ++drq_iter){
				if (drq_iter->allocated == 0)
					break;
			}
		}
		else if ((ch_req->ahbch_req.src_index == DMAC_REQN_UART1RX) ||
				(ch_req->ahbch_req.dst_index == DMAC_REQN_UART1RX) ||
				(ch_req->ahbch_req.src_index == DMAC_REQN_UART2RX) ||
				(ch_req->ahbch_req.dst_index == DMAC_REQN_UART2RX)){

			/* RX channel is limitied to A/B */
			for (i = 0; i < 2; ++i, ++drq_iter){

				if (drq_iter->allocated == 0)
					break;
			}
		}
		else
#endif
		{
			if ((ch_req->ahbch_req.src_index != DMAC_REQN_NONE) ||
					(ch_req->ahbch_req.dst_index != DMAC_REQN_NONE)){

				/*
				 * [2007-12-03] It looks current board have problem to do dma
				 * traffic for APB devices on DMAC channel 0/1.  Redirect all
				 * APB devices to start from channel 2.
				 * [todo] include USB controller ?
				 */
				drq_iter = &ahb_drq_pool[2];
				for (i = 2; i < DMAD_AHB_MAX_CHANNELS; ++i, ++drq_iter){

					if (drq_iter->allocated == 0)
						break;
				}
			}
			else {
				/* channel for other devices is free to allocate */
				for (i = 0; i < DMAD_AHB_MAX_CHANNELS; ++i, ++drq_iter){

					if (drq_iter->allocated == 0)
						break;
				}
			}
		}

		if (i == DMAD_AHB_MAX_CHANNELS){

			DMAD_TRACE(("out of available channels (AHB DMAC)!\r\n"));
			return HAL_ERR_UNAVAILABLE;
		}

		DMAD_TRACE(("allocated channel: %d (AHB DMAC)\r\n"));
	}
	else if (ch_req->controller == DMAD_DMAC_APB_CORE){

		for (i = 0; i < DMAD_APB_MAX_CHANNELS; ++i, ++drq_iter){

			if (drq_iter->allocated == 0)
				break;
		}

		if (i == DMAD_APB_MAX_CHANNELS){

			DMAD_TRACE(("out of available channels (APB DMAC)!\r\n"));
			return HAL_ERR_UNAVAILABLE;
		}

		DMAD_TRACE(("allocated channel: %d (APB DMAC)\r\n", i));
	}

	/* Allocate the DMA channel */
	drq_iter->allocated = 1;

	if (hal_current() != HAL_NULL){

		/*
		 * Suspending is only valid to the current task -- no need to lock if invoked from HISR.
		 * Release exclusive access to the pool of channel queues
		 */
		status = hal_release_mutex(&dmad.drq_pool_mutex);
		if (status != HAL_SUCCESS){

			DMAD_TRACE(("[dmad] failed to unlock drq_pool!\r\n"));
			return status;
		}
	}

	/* Create mutex object for DMA queue access control */
	status = hal_create_mutex(&drq_iter->drb_pool_mutex, "drq");
	if (status != HAL_SUCCESS){

		DEBUG(1, 1, "failed to create mutex for drb_pool!\n");
		return status;
	}

	/* Create semaphores for free-list allocation operation */
	status = hal_create_semaphore(&drq_iter->drb_sem, DMAD_DRB_POOL_SIZE - 1, (void*)0);
	if (status != HAL_SUCCESS){

		DEBUG(1, 1, "failed to create semaphores for drb_pool!\n");
		return status;
	}

	/* Record the channel number in client's struct */
	ch_req->channel = i;

	/* Record the channel's queue handle in client's struct */
	ch_req->drq = drq_iter;

	if (ch_req->controller == DMAD_DMAC_AHB_CORE){

		//drq_iter->controller_base = DMAC_BASE;
		drq_iter->channel_base = DMAC_BASE_CH(i);
	}
	else {
		//drq_iter->controller_base = APBBR_BASE;
		drq_iter->channel_base = APBBR_DMA_BASE_CH(i);
	}

	/* Initialize DMA channel's DRB pool as list of free DRBs */
	drb_iter = &drq_iter->drb_pool[0];
	drb_iter->prev = 0;
	drb_iter->next = 0;
	drb_iter->node = 0;
	//drb_iter->src_addr = 0;
	//drb_iter->dst_addr = 0;
	//drb_iter->req_size = 0;
	++drb_iter;

	for (i = 1; i < DMAD_DRB_POOL_SIZE; ++i, ++drb_iter){

		drb_iter->prev = i - 1;
		drb_iter->next = i + 1;
		drb_iter->node = i;
		//drb_iter->src_addr = 0;
		//drb_iter->dst_addr = 0;
		//drb_iter->req_size = 0;
	}
	drq_iter->drb_pool[DMAD_DRB_POOL_SIZE - 1].next = 0;

	/* Initialize DMA channel's DRB free-list, ready-list, and submitted-list */
	drq_iter->fre_head = 1;
	drq_iter->fre_tail = DMAD_DRB_POOL_SIZE - 1;
	drq_iter->rdy_head = drq_iter->rdy_tail = 0;
	drq_iter->sbt_head = drq_iter->sbt_tail = 0;
	drq_iter->cpl_head = drq_iter->cpl_tail = 0;

	/* Initialize the channel */
	if (init)
		_dmad_channel_init(ch_req);

	/* Initialize cache writeback function */
#ifndef CONFIG_CPU_DCACHE_ENABLE
	drq_iter->dc_writeback = HAL_NULL;
	drq_iter->dc_invalidate = HAL_NULL;
#else
	drq_iter->dc_writeback = nds32_dma_flush_range;
	drq_iter->dc_invalidate = nds32_dma_inv_range;
#endif
	return HAL_SUCCESS;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_channel_free
 *
 * DESCRIPTION
 *
 *   This function frees a DMA channel for future clients' request.
 *
 * INPUTS
 *
 *   ch_req     : Pointer to the DMA request descriptor structure
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful channel free,
 *                else positive value is DMAD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _dmad_channel_free(const DMAD_CHANNEL_REQUEST_DESC *ch_req){

	uint32_t status;
	DMAD_DRQ *drq;

	if (ch_req == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	drq = (DMAD_DRQ *)ch_req->drq;

	if (drq == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	if (drq->allocated == 0)
		return HAL_ERR_INVALID_POINTER;

	if (hal_current() != HAL_NULL){

		/*
		 * Suspending is only valid to the current task -- no need to lock if invoked from HISR.
		 * Obtain exclusive access to the pool of channel queues
		 */
		status = hal_wait_for_mutex(&dmad.drq_pool_mutex, HAL_SUSPEND);
		if (status != HAL_SUCCESS)
			return status;
	}

	/* Todo: Stop/abort channel I/O if it's busy ? */

	/* Delete mutex object of DMA queue access control */
	status = hal_destroy_mutex(&drq->drb_pool_mutex);
	if (status != HAL_SUCCESS)
		return status;

	/* Delete semaphores of free-list allocation operation */
	status = hal_destroy_semaphore(&drq->drb_sem);
	if (status != HAL_SUCCESS)
		return status;

	/* Reset HISR activation state */
	if (ch_req->controller == DMAD_DMAC_AHB_CORE)
		dmad.hisr_as &= ~(1 << ch_req->channel);
	else
		dmad.hisr_as &= ~(1 << (ch_req->channel + 16));

	/* Set released flag. */
	drq->allocated = 0;

	if (hal_current() != HAL_NULL){

		/*
		 * Suspending is only valid to the current task -- no need to lock if invoked from HISR.
		 * Release exclusive access to the pool of channel queues
		 */
		status = hal_release_mutex(&dmad.drq_pool_mutex);
		if (status != HAL_SUCCESS)
			return status;
	}

	return HAL_SUCCESS;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_ahb_init
 *
 * DESCRIPTION
 *
 *   This function performs the AHB DMAC channel initialization.
 *
 * INPUTS
 *
 *   ch_req     : Pointer to the DMA request descriptor structure
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is DMAD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
static uint32_t _dmad_ahb_init(const DMAD_CHANNEL_REQUEST_DESC *ch_req){

	uint32_t		status = HAL_SUCCESS;
	DMAD_DRQ		*drq = (DMAD_DRQ *)ch_req->drq;
	DMAD_AHBCH_REQUEST	*ahb_req = (DMAD_AHBCH_REQUEST *)(&ch_req->ahbch_req);
	uint32_t		channel = (uint32_t)ch_req->channel;
	uint32_t		channel_base = drq->channel_base;
	uint32_t		core_intl;

	/* Register LISR */
	if (dmad.ahb_lisr_registered == 0){
		status = hal_register_isr(IRQ_DMA_VECTOR, _dmad_ahb_lisr, (void*)0);
	//	status = hal_register_isr(INTC_DMA_BIT, _dmad_ahb_lisr, (void*)0);
	
	if (status != HAL_SUCCESS)
			return status;

		dmad.ahb_lisr_registered = 1;
	}

	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);

	/* Following code require _safe_exit return path */

	/* INTC */
	/* Disable DMAC interrupt */
	hal_intc_irq_disable(IRQ_DMA_VECTOR);
 	
	/* Clear DMAC interrupt status */
	hal_intc_irq_clean(IRQ_DMA_VECTOR);

	/* Setup DMAC interrupt trigger mode - level trigger */
	/* Setup DMAC interrupt trigger level - assert high */
	hal_intc_irq_config(IRQ_DMA_VECTOR, IRQ_LEVEL_TRIGGER, IRQ_ACTIVE_HIGH);
	
	/* Enable DMAC interrupt */	
	hal_intc_irq_enable(IRQ_DMA_VECTOR);

#if 0
#if ( NO_EXTERNAL_INT_CTL == 1 )
	/*
	 *	IVIC without INTC   
	 */
	/* FIXME add trigger mode */
	/* Enable DMAC interupt	  */
	SR_SETB32(NDS32_SR_INT_MASK2,IRQ_DMA_VECTOR);
	

#else
	/*
	 * INTC
	 */

	/* Clear DMAC interrupt status */
	SETB32(INTC_HW1_CLR, INTC_DMA_BIT);

	/* Setup DMAC interrupt trigger mode - level trigger */
	CLRB32(INTC_HW1_TMR, INTC_DMA_BIT);

	/* Setup DMAC interrupt trigger level - assert high */
	CLRB32(INTC_HW1_TLR, INTC_DMA_BIT);

	/* Enable DMAC interrupt */
	SETB32(INTC_HW1_ER, INTC_DMA_BIT);
#endif
#endif

	/*
	 * PMU
	 */

	/*
	 * Route APB device DMA to an AHB DMAC channel and specify the channel
	 * number. (connection status could be read back from PMU_AHBDMA_REQACK
	 * register)
	 * Note: Only one device is routed per AHB DMA channel, the other target
	 * should be either (1) the same device (same reqn), or (2) the AHB
	 * device (reqn = 0).
	 */
	if (ahb_req->dst_index != PMU_REQN_NONE){

		/* DMA transfer to device */
		if ((ahb_req->dst_index > PMU_REQN_EXT1) ||
				(dmad_ahb_ch_route_table[ahb_req->dst_index].route_cr == 0)){

			status = HAL_ERR_NOT_PRESENT;
			goto _safe_exit;
		}

		OUT32(dmad_ahb_ch_route_table[ahb_req->dst_index].route_cr,
				PMU_DMACUSED_MASK | ((ahb_req->dst_reqn << PMU_CHANNEL_SHIFT) & PMU_CHANNEL_MASK));
	}
	else if (ahb_req->src_index != PMU_REQN_NONE){

		/* DMA transfer from device */
		if ((ahb_req->src_index > PMU_REQN_EXT1) ||
				(dmad_ahb_ch_route_table[ahb_req->src_index].route_cr == 0)){

			status = HAL_ERR_NOT_PRESENT;
			goto _safe_exit;
		}

		OUT32(dmad_ahb_ch_route_table[ahb_req->src_index].route_cr,
				PMU_DMACUSED_MASK | ((ahb_req->src_reqn << PMU_CHANNEL_SHIFT) & PMU_CHANNEL_MASK));
	}


	/*
	 * DMAC (Controller Setting)
	 *   Note: Controller global setting actually should not placed in this channel
	 *         specific setup routine.  However, currently the only global setting
	 *         is a fixed value, so it is ok to set it here.  In this way, we save
	 *         the effert to setup the global parameters elsewhere.
	 */

	/* INT TC/ERR/ABT status clear */
	SETB32(DMAC_INT_TC_CLR, channel); /* TC clear */
	SETB32(DMAC_INT_ERRABT_CLR, channel + DMAC_INT_ERR_CLR_SHIFT); /* ERR clear */
	SETB32(DMAC_INT_ERRABT_CLR, channel + DMAC_INT_ABT_CLR_SHIFT); /* ABT clear */

	/* CSR (enable DMAC, set M0 & M1 endian default to little endian transfer) */
	OUT32(DMAC_CSR, DMAC_DMACEN_MASK |
			((DMAC_ENDIAN_LITTLE << DMAC_M0ENDIAN_BIT) & DMAC_M0ENDIAN_MASK) |
			((DMAC_ENDIAN_LITTLE << DMAC_M1ENDIAN_BIT) & DMAC_M1ENDIAN_MASK));

	/* DMAC (Channel-Specific Setting) */
	/* SYNC */
	if (ahb_req->sync)
		SETB32(DMAC_SYNC, channel);
	else
		CLRB32(DMAC_SYNC, channel);

	/*
	 * Channel CSR
	 *    CH_EN     : 0 (disable)
	 *    DST_SEL   : 0 (Master 0)
	 *    SRC_SEL   : 0 (Master 0)
	 *    DSTAD_CTL : ahb_req->dst_addr_ctrl
	 *    SRCAD_CTL : ahb_req->src_addr_ctrl
	 *    MODE      : 0 (normal)
	 *    DST_WIDTH : ahb_req->dst_width
	 *    SRC_WIDTH : ahb_req->src_width
	 *    ABT       : 0 (not abort)
	 *    SRC_SIZE  : 0 (burst size = 1 byte)
	 *    PROT1     : 0 (user mode)
	 *    PROT2     : 0 (bot bufferable)
	 *    PROT3     : 0 (not cacheable)
	 *    CHPRI     : ahb_req->priority
	 *    DMA_FF_TH : 0 (FIA320 only, threshold = 1)
	 *    TC_MSK    : 0 (TC counter status enable)
	 */
	OUT32(channel_base + DMAC_CSR_OFFSET,
			((ahb_req->src_width << DMAC_CSR_SRC_WIDTH_SHIFT) & DMAC_CSR_SRC_WIDTH_MASK) |
			((ahb_req->src_addr_ctrl << DMAC_CSR_SRCAD_CTL_SHIFT) & DMAC_CSR_SRCAD_CTL_MASK) |
			((ahb_req->dst_width << DMAC_CSR_DST_WIDTH_SHIFT) & DMAC_CSR_DST_WIDTH_MASK) |
			((ahb_req->dst_addr_ctrl << DMAC_CSR_DSTAD_CTL_SHIFT) & DMAC_CSR_DSTAD_CTL_MASK) |
			((ahb_req->priority << DMAC_CSR_CHPRI_SHIFT) & DMAC_CSR_CHPRI_MASK));

	/* Channel CFG
	 *    INT_TC_MSK  : 0 (enable TC int)
	 *    INT_ERR_MSK : 0 (enable ERR int)
	 *    INT_ABT_MSK : 0 (enable ABT int)
	 *    SRC_RS      : 0
	 *    SRC_HE      : 0
	 *    BUSY        : r/o
	 *    DST_RS      : 0
	 *    DST_HE      : 0
	 *    LLP_CNT     : r/o
	 */
	OUT32(channel_base + DMAC_CFG_OFFSET, 0);
	/*(DMAC_CFG_INT_TC_MSK | DMAC_CFG_INT_ERR_MSK | DMAC_CFG_INT_ABT_MSK)); */

#if 1 /* (Not found in AG101 spec -- has removed this setting?) */
	/* - HW handshake mode: CSR & CFG */
	if (ahb_req->hw_handshake != 0){

		/* Channel CFG - Device REQN and HW-handshake mode */
		uint32_t cfg = IN32(channel_base + DMAC_CFG_OFFSET);

		if (ahb_req->src_index != DMAC_REQN_NONE){

			OUT32(channel_base + DMAC_CFG_OFFSET, cfg |
					((ahb_req->src_reqn << DMAC_CFG_INT_SRC_RS_SHIFT) & DMAC_CFG_INT_SRC_RS_MASK) |
					((1 << DMAC_CFG_INT_SRC_HE_BIT) & DMAC_CFG_INT_SRC_HE_MASK) |
					((0 << DMAC_CFG_INT_DST_RS_SHIFT) & DMAC_CFG_INT_DST_RS_MASK) |
					((0 << DMAC_CFG_INT_DST_HE_BIT) & DMAC_CFG_INT_DST_HE_MASK));
		}
		else {
			OUT32(channel_base + DMAC_CFG_OFFSET, cfg |
					((0 << DMAC_CFG_INT_SRC_RS_SHIFT) & DMAC_CFG_INT_SRC_RS_MASK) |
					((0 << DMAC_CFG_INT_SRC_HE_BIT) & DMAC_CFG_INT_SRC_HE_MASK) |
					((ahb_req->dst_reqn << DMAC_CFG_INT_DST_RS_SHIFT) & DMAC_CFG_INT_DST_RS_MASK) |
					((1 << DMAC_CFG_INT_DST_HE_BIT) & DMAC_CFG_INT_DST_HE_MASK));
		}

		/* Channel CSR - Enable HW-handshake mode */
		SETB32(channel_base + DMAC_CSR_OFFSET, DMAC_CSR_MODE_BIT);
	}
#endif
	/* SRC_ADDR and DST_ADDR - not now */

	/* LLP */
	OUT32(channel_base + DMAC_LLP_OFFSET, 0);

	/* TOT_SIZE - not now */

_safe_exit:
	hal_global_int_ctl(core_intl);

	return status;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_apb_init
 *
 * DESCRIPTION
 *
 *   This function performs the APB bridge DMA channel initialization.
 *
 * INPUTS
 *
 *   ch_req     : Pointer to the DMA request descriptor structure
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is DMAD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
static uint32_t _dmad_apb_init(const DMAD_CHANNEL_REQUEST_DESC *ch_req){

	uint32_t		status = HAL_SUCCESS;
	DMAD_DRQ		*drq = (DMAD_DRQ *)ch_req->drq;
	DMAD_APBCH_REQUEST	*apb_req = (DMAD_APBCH_REQUEST *)(&ch_req->apbch_req);
	uint32_t		channel = (uint32_t)ch_req->channel;
	uint32_t		channel_base = drq->channel_base;
	uint32_t		channel_cmd = 0;
	uint32_t		core_intl;
	uint32_t		dst_bus_sel;
	uint32_t                src_bus_sel;

	/* Register LISR */
	if (dmad.apb_lisr_registered == 0){
		status = hal_register_isr(IRQ_APBBRIDGE_VECTOR , _dmad_apb_lisr, (void*)0);
		
		if (status != HAL_SUCCESS)
			return status;

		dmad.apb_lisr_registered = 1;
	}

	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);

	/* Following code require _safe_exit return path */

	/* INTC */ 
	/* Disable APB Bridge interrupt */
	hal_intc_irq_disable(IRQ_APBBRIDGE_VECTOR);
		
	/* Clear APB Bridge interrupt status */
	hal_intc_irq_clean(IRQ_APBBRIDGE_VECTOR);

	/* Setup APB Bridge interrupt trigger mode - level trigger */
	/* Setup APB Bridge interrupt trigger level - assert high */
	hal_intc_irq_config(IRQ_APBBRIDGE_VECTOR, IRQ_LEVEL_TRIGGER, IRQ_ACTIVE_HIGH);	

	/* Enable APB Bridge interrupt */
	hal_intc_irq_enable(IRQ_APBBRIDGE_VECTOR);

#if 0
#if ( NO_EXTERNAL_INT_CTL == 1 )
	/*
	 *	IVIC without INTC 
	 */
	/* FIXME add trigger mode */
	/* Enable APB Bridge interrupt */
	SR_SETB32(NDS32_SR_INT_MASK2,IRQ_APBBRIDGE_VECTOR);
#else
	/*
	 * INTC
	 */

	/* Clear APB Bridge interrupt status */
	SETB32(INTC_HW1_CLR, INTC_APB_BIT);

	/* Setup APB Bridge interrupt trigger mode - level trigger */
	CLRB32(INTC_HW1_TMR, INTC_APB_BIT);

	/* Setup APB Bridge interrupt trigger level - assert high */
	CLRB32(INTC_HW1_TLR, INTC_APB_BIT);

	/* Enable APB Bridge interrupt */
	SETB32(INTC_HW1_ER, INTC_APB_BIT);
#endif
#endif
	/* PMU */

	/* Check platform version */
        uint32_t max_reqn = _dmad_get_reqn(DMAD_DMAC_APB_CORE, APB_MAX);

	/*
	 * Undo APB device DMA to AHB DMAC channel routing. (connection status
	 * is obtained from reading back the PMU_AHBDMA_REQACK register)
	 */

	if ((apb_req->src_index > max_reqn) ||
			(apb_req->dst_index > max_reqn)){

		status = HAL_ERR_NOT_PRESENT;
		goto _safe_exit;
	}

	if (apb_req->src_index != APBBR_REQN_NONE){ /* quick filter out non-APB reqn */

		uint32_t ahb_ch;

		/* Search for source device whether it is re-routed to AHB DMA channel */
		for (ahb_ch = 0; ahb_ch < DMAD_AHB_MAX_CHANNELS; ++ahb_ch){

			uint32_t ahb_reqn = (IN32(PMU_AHBDMA_REQACK) >> (ahb_ch << 2)) & 0x0000000f;

			if ((ahb_reqn != APBBR_REQN_NONE) &&
					(ahb_reqn == dmad_apb_reqn_route_table[apb_req->src_index].ahb_reqn)){

				DMAD_TRACE(("src: re-route DMAC ch %2d to APB.\r\n", ahb_ch));

				/* got it! un-route from AHB back to APB */
				OUT32(dmad_ahb_ch_route_table[ahb_reqn].route_cr,
						((channel << PMU_CHANNEL_SHIFT) & PMU_CHANNEL_MASK));
				break;
			}
		}
	}

	if (apb_req->dst_index != APBBR_REQN_NONE){ /* quick filter out non-APB reqn */

		uint32_t ahb_ch;

		/* Search for source device whether it is re-routed to AHB DMA channel */
		for (ahb_ch = 0; ahb_ch < DMAD_AHB_MAX_CHANNELS; ++ahb_ch){

			uint32_t ahb_reqn = (IN32(PMU_AHBDMA_REQACK) >> (ahb_ch << 2)) & 0x0000000f;

			if ((ahb_reqn != APBBR_REQN_NONE) &&
					(ahb_reqn == dmad_apb_reqn_route_table[apb_req->dst_index].ahb_reqn)){

				DMAD_TRACE(("dst: re-route DMAC ch %2d to APB.\r\n", ahb_ch));

				/* got it! un-route from AHB back to APB */
				OUT32(dmad_ahb_ch_route_table[ahb_reqn].route_cr,
						((channel << PMU_CHANNEL_SHIFT) & PMU_CHANNEL_MASK));
				break;
			}
		}
	}

	/* APB Bridge DMA (Channel Setting) */

	/*
	 * - CMD
	 *    ENBDIS    : 0 (disable for now)
	 *    FININTSTS : 0 (clear finishing interrupt status)
	 *    FININTENB : 1 (enable finishing interrupt)
	 *    BURMOD    : apb_req->burst_mode
	 *    ERRINTSTS : 0 (clear error interrupt status)
	 *    ERRINTENB : 1 (enable error interrupt)
	 *    SRCADRSEL : AHB/APB, driver auto-conf according to apb_req->src_index
	 *    DESADRSEL : AHB/APB, driver auto-conf according to apb_req->dst_index
	 *    SRCADR    : apb_req->src_addr_ctrl
	 *    DESADR    : apb_req->dst_addr_ctrl
	 *    REQSEL    : apb_req->src_index (? a "req/gnt" device looks to be a src... check to use reqn of src or dst)
	 *    DATAWIDTH : apb_req->data_width
	 */

	/*
	 * - CMD
	 *    ENBDIS
	 *    FININTSTS
	 *    FININTENB
	 *    BURMOD
	 *    ERRINTSTS
	 *    ERRINTENB
	 *    SRCADR
	 *    DESADR
	 *    DATAWIDTH
	 */
	channel_cmd = ((uint32_t)APBBR_DMA_FINTEN_MASK | APBBR_DMA_ERRINTEN_MASK |
			((apb_req->burst_mode << APBBR_DMA_BURST_BIT) & APBBR_DMA_BURST_MASK) |
			((apb_req->src_addr_ctrl << APBBR_DMA_SRCADDRINC_SHIFT) & APBBR_DMA_SRCADDRINC_MASK) |
			((apb_req->dst_addr_ctrl << APBBR_DMA_DSTADDRINC_SHIFT) & APBBR_DMA_DSTADDRINC_MASK) |
			((apb_req->data_width << APBBR_DMA_DATAWIDTH_SHIFT) & APBBR_DMA_DATAWIDTH_MASK));

	/*
	 * - CMD
	 *    DSTADRSEL
	 *    DREQSEL (todo: this is FIA320 bit-mask, check AG101 bit-mask location)
	 */
	if (apb_req->dst_index != APBBR_REQN_NONE)
		dst_bus_sel = APBBR_ADDRSEL_APB;
	else
		dst_bus_sel = APBBR_ADDRSEL_AHB;

	channel_cmd |= ((uint32_t)(APBBR_DMA_DSTADDRSEL_MASK &
				(dst_bus_sel << APBBR_DMA_DSTADDRSEL_BIT)) |
			(((uint32_t)apb_req->dst_index << APBBR_DMA_DREQSEL_SHIFT) & APBBR_DMA_DREQSEL_MASK));

	/*
	 * - CMD
	 *    SRCADRSEL
	 *    SREQSEL (todo: this is FIA320 bit-mask, check AG101 bit-mask location)
	 */
        if (apb_req->src_index != APBBR_REQN_NONE)
                src_bus_sel = APBBR_ADDRSEL_APB;
        else
                src_bus_sel = APBBR_ADDRSEL_AHB;

	channel_cmd |= ((uint32_t)(APBBR_DMA_SRCADDRSEL_MASK &
				(src_bus_sel << APBBR_DMA_SRCADDRSEL_BIT)) |
			(((uint32_t)apb_req->src_index << APBBR_DMA_SREQSEL_SHIFT) & APBBR_DMA_SREQSEL_MASK));

	/* - CMD outport */
	OUT32(channel_base + APBBR_DMA_CMD_OFFSET, channel_cmd);

	/* SRCADR and DESADR - not now */

	/* CYC - not now */

_safe_exit:
	hal_global_int_ctl(core_intl);

	return status;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_channel_init
 *
 * DESCRIPTION
 *
 *   This function performs the DMA channel HW initialization abstraction.
 *   The real initialization task is dispatched according to the requested
 *   DMA controller type (AHB DMAC or APB bridge DMA controller).
 *
 * INPUTS
 *
 *   ch_req     : Pointer to the DMA request descriptor structure
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful initialization,
 *                else positive value is DMAD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _dmad_channel_init(const DMAD_CHANNEL_REQUEST_DESC *ch_req){

	uint32_t status;

	DMAD_TRACE(("_dmad_channel_init\r\n"));

	if (ch_req == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	if (ch_req->drq == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	/* Initialize DMA controller */
	if (ch_req->controller == DMAD_DMAC_AHB_CORE)
		status = _dmad_ahb_init(ch_req);
	else
		status = _dmad_apb_init(ch_req);

	/* Register HISR to perform deffered DMA ISR tasks */
	if (dmad.hisr_registered == 0){
		printf("_dmad_channel_init Register HISR\n");

		dmad.hisr.th.fn    = _dmad_hisr;
		dmad.hisr.th.arg   = &dmad.hisr;
		dmad.hisr.th.prio  = CONFIG_DMAD_HISR_PRIORITY;
		dmad.hisr.th.ptos  = &dmad_hisr_stack[DMAD_HISR_STACK_SIZE];
		dmad.hisr.th.stack_size = sizeof(dmad_hisr_stack);
		dmad.hisr.th.name  = "DMA BH";

		status = hal_create_bh(&dmad.hisr);
		if (status != HAL_SUCCESS)
			return status;
		

		dmad.hisr_registered = 1;
	}

	return status;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_channel_enable
 *
 * DESCRIPTION
 *
 *   This function is a abstraction routine to enable or disable a DMA
 *   channel.
 *
 * INPUTS
 *
 *   ch_req     : Pointer to the DMA request descriptor structure
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful enable/disable,
 *                else positive value is DMAD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _dmad_channel_enable(const DMAD_CHANNEL_REQUEST_DESC *ch_req, uint8_t enable){

	DMAD_DRQ *drq;

	if (ch_req == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	drq = (DMAD_DRQ *)ch_req->drq;

	if (drq == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	/* Enable/disable DMA channel */
	if (ch_req->controller == DMAD_DMAC_AHB_CORE){

		if (enable)
			SETB32(drq->channel_base + DMAC_CSR_OFFSET, DMAC_CSR_CH_EN_BIT);
		else
			CLRB32(drq->channel_base + DMAC_CSR_OFFSET, DMAC_CSR_CH_EN_BIT);
	}
	else { /* APB */

		if (enable)
			SETB32(drq->channel_base + APBBR_DMA_CMD_OFFSET, APBBR_DMA_CHEN_BIT);
		else
			CLRB32(drq->channel_base + APBBR_DMA_CMD_OFFSET, APBBR_DMA_CHEN_BIT);
	}

	return HAL_SUCCESS;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_alloc_drb
 *
 * DESCRIPTION
 *
 *   This function is used to allocate a DRB (DMA request block) within a DMA
 *   channel.  DRB is used to queue all DMA submission requests for the
 *   channel.  Allocated DRB node is moved from the free-list to the ready-
 *   list.
 *
 * INPUTS
 *
 *   ch_req     : (in) Pointer to the DMA request descriptor structure
 *   drb        : (out) Reference to the pointer of allocated DRB.
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful allocation,
 *                else positive value is DMAD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
volatile int taskId=0;
uint32_t _dmad_alloc_drb(DMAD_CHANNEL_REQUEST_DESC *ch_req, DMAD_DRB **drb){

	uint32_t	status = HAL_SUCCESS;
	DMAD_DRQ	*drq;
	uint32_t	core_intl;

	if (ch_req == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	drq = (DMAD_DRQ *)ch_req->drq;

	if (drq == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	/* Obtain exclusive access to the drq from other tasks */
	if (hal_current() != HAL_NULL){

		/*
		 * Suspending is only valid to the current task -- no need to lock if invoked from HISR.
		 * Lock DMA queue to prevent been updated by other tasks
		 */
		status = hal_wait_for_mutex(&drq->drb_pool_mutex, HAL_SUSPEND);
		if (status != HAL_SUCCESS)
			return status;
	}

	/* Initialize drb ptr in case of fail allocation */
	*drb = HAL_NULL;

#ifdef DMAD_POLLING
	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);

	while (drq->fre_head == 0){

		/* Wait for free urbs. Sleep for 50 ms before polling again. */
		hal_global_int_ctl(core_intl);
		hal_sleep(50);
		core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);
	}
#else
	status = hal_pend_semaphore(&drq->drb_sem, HAL_SUSPEND);

	if (status == HAL_ERR_TIMEOUT){

		status = HAL_ERR_NO_MEMORY;
		goto _safe_exit;
	}
	else if (status != HAL_SUCCESS){

		goto _safe_exit;
	}

	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);
#endif
	_dmad_detach_head(drq->drb_pool, &drq->fre_head, &drq->fre_tail, drb);

	hal_global_int_ctl(core_intl);

	_dmad_attach_tail(drq->drb_pool, &drq->rdy_head, &drq->rdy_tail, (*drb)->node);
	(*drb)->state = DMAD_DRB_STATE_READY;
	(*drb)->completion_sem = HAL_NULL;
	(*drb)->psp = HAL_NULL;
	(*drb)->rcp = HAL_NULL;
	if (ch_req->controller == DMAD_DMAC_AHB_CORE) {
		(*drb)->src_index = ch_req->ahbch_req.src_index;
		(*drb)->dst_index = ch_req->ahbch_req.dst_index;
	} else if (ch_req->controller == DMAD_DMAC_APB_CORE) {
		(*drb)->src_index = ch_req->apbch_req.src_index;
		(*drb)->dst_index = ch_req->apbch_req.dst_index;
	} else
		status = HAL_ERR_NOT_PRESENT;

	goto _safe_exit;

_safe_exit:

	/* Release locking of this function from other tasks */
	if (hal_current() != HAL_NULL){

		/*
		 * Suspending is only valid to the current task -- no need to lock if invoked from HISR.
		 * Unlock DMA queue to allow its access from other tasks
		 */
		hal_release_mutex(&drq->drb_pool_mutex);
	}

	return status;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_free_drb
 *
 * DESCRIPTION
 *
 *   This function is used to free a DRB (DMA request block) within a DMA
 *   channel.  DRB is used to queue all DMA submission requests for the
 *   channel.  Freed DRB node is moved from the ready-list to the free-
 *   list.
 *
 * INPUTS
 *
 *   ch_req     : (in) Pointer to the DMA request descriptor structure
 *   drb        : (in) Pointer of a DRB struct to be freed.
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful freeing,
 *                else positive value is DMAD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _dmad_free_drb(DMAD_CHANNEL_REQUEST_DESC *ch_req, DMAD_DRB *drb){

	uint32_t	status = HAL_SUCCESS;
	DMAD_DRQ	*drq;
	uint32_t	core_intl;

	if (ch_req == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	drq = (DMAD_DRQ *)ch_req->drq;

	if (drq == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	/* Obtain exclusive access to the drq from other tasks */
	if (hal_current() != HAL_NULL){

		/* Suspending is only valid to the current task -- no need to lock if invoked from HISR. */
		status = hal_wait_for_mutex(&drq->drb_pool_mutex, HAL_SUSPEND);
		if (status != HAL_SUCCESS)
			return status;
	}

	/* Following code require _safe_exit return path */

	if ((drq->rdy_head == 0) || (drb->node == 0) ||
			(drb->node >= DMAD_DRB_POOL_SIZE)){

		DMAD_TRACE(("Ready-queue is empty or invalid node!\r\n"));
		/* Unlock DMA queue to allow its access from other tasks */
		status = HAL_ERR_INVALID_ENTRY;
		goto _safe_exit;
	}

	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);

	_dmad_detach_node(drq->drb_pool, &drq->rdy_head, &drq->rdy_tail, drb->node);
	_dmad_attach_tail(drq->drb_pool, &drq->fre_head, &drq->fre_tail, drb->node);

	hal_global_int_ctl(core_intl);

	drb->state = DMAD_DRB_STATE_FREE;
	drb->completion_sem = HAL_NULL;

_safe_exit:

	/* Release locking of this function from other tasks */
	if (hal_current() != HAL_NULL){

		/*
		 * Suspending is only valid to the current task -- no need to lock if invoked from HISR
		 * Unlock DMA queue to allow its access from other tasks
		 */
		hal_release_mutex(&drq->drb_pool_mutex);
	}

	return status;
}


int dmad_apb_config_dir(const DMAD_CHANNEL_REQUEST_DESC *ch_req, uint8_t dir)
{
	uint32_t		status = HAL_SUCCESS;
	DMAD_DRQ		*drq = (DMAD_DRQ *)ch_req->drq;
	DMAD_APBCH_REQUEST	*apb_req = (DMAD_APBCH_REQUEST *)(&ch_req->apbch_req);
	uint32_t		channel_base = drq->channel_base;
	uint32_t		channel_cmd = 0;
	uint32_t                dst_bus_sel;
	uint32_t                src_bus_sel;

	channel_cmd = IN32(channel_base + APBBR_DMA_CMD_OFFSET);
	channel_cmd &= ~(uint32_t)
		(APBBR_DMA_SRCADDRINC_MASK | APBBR_DMA_DSTADDRINC_MASK |
		 APBBR_DMA_DSTADDRSEL_MASK | APBBR_DMA_DREQSEL_MASK |
		 APBBR_DMA_SRCADDRSEL_MASK | APBBR_DMA_SREQSEL_MASK);
	if( dir == 0){
		channel_cmd = ((uint32_t)APBBR_DMA_FINTEN_MASK | APBBR_DMA_ERRINTEN_MASK |
				((apb_req->src_addr_ctrl << APBBR_DMA_SRCADDRINC_SHIFT) & APBBR_DMA_SRCADDRINC_MASK) |
				((apb_req->dst_addr_ctrl << APBBR_DMA_DSTADDRINC_SHIFT) & APBBR_DMA_DSTADDRINC_MASK));

		/*
		 * - CMD
		 *    DSTADRSEL
		 *    DREQSEL (todo: this is FIA320 bit-mask, check AG101 bit-mask location)
		 */
		if (apb_req->dst_index != APBBR_REQN_NONE)
			dst_bus_sel = APBBR_ADDRSEL_APB;
		else
			dst_bus_sel = APBBR_ADDRSEL_AHB;

		channel_cmd |= ((uint32_t)(APBBR_DMA_DSTADDRSEL_MASK &
					(dst_bus_sel << APBBR_DMA_DSTADDRSEL_BIT)) |
				(((uint32_t)apb_req->dst_index << APBBR_DMA_DREQSEL_SHIFT) & APBBR_DMA_DREQSEL_MASK));

		/*
		 * - CMD
		 *    SRCADRSEL
		 *    SREQSEL (todo: this is FIA320 bit-mask, check AG101 bit-mask location)
		 */
		if (apb_req->src_index != APBBR_REQN_NONE)
                        src_bus_sel = APBBR_ADDRSEL_APB;
                else
                        src_bus_sel = APBBR_ADDRSEL_AHB;

		channel_cmd |= ((uint32_t)(APBBR_DMA_SRCADDRSEL_MASK &
					(src_bus_sel << APBBR_DMA_SRCADDRSEL_BIT)) |
				(((uint32_t)apb_req->src_index << APBBR_DMA_SREQSEL_SHIFT) & APBBR_DMA_SREQSEL_MASK));

		/* - CMD outport */
		OUT32(channel_base + APBBR_DMA_CMD_OFFSET, channel_cmd);

	} else {
		channel_cmd = ((uint32_t)APBBR_DMA_FINTEN_MASK | APBBR_DMA_ERRINTEN_MASK |
				((apb_req->dst_addr_ctrl << APBBR_DMA_SRCADDRINC_SHIFT) & APBBR_DMA_SRCADDRINC_MASK) |
				((apb_req->src_addr_ctrl << APBBR_DMA_DSTADDRINC_SHIFT) & APBBR_DMA_DSTADDRINC_MASK));

		/*
		 * - CMD
		 *    DSTADRSEL
		 *    DREQSEL (todo: this is FIA320 bit-mask, check AG101 bit-mask location)
		 */
		if (apb_req->src_index != APBBR_REQN_NONE)
                        src_bus_sel = APBBR_ADDRSEL_APB;
                else
                        src_bus_sel = APBBR_ADDRSEL_AHB;

		channel_cmd |= ((uint32_t)(APBBR_DMA_DSTADDRSEL_MASK &
					(src_bus_sel << APBBR_DMA_DSTADDRSEL_BIT)) |
				(((uint32_t)apb_req->src_index << APBBR_DMA_DREQSEL_SHIFT) & APBBR_DMA_DREQSEL_MASK));

		/*
		 * - CMD
		 *    SRCADRSEL
		 *    SREQSEL (todo: this is FIA320 bit-mask, check AG101 bit-mask location)
		 */
		if (apb_req->dst_index != APBBR_REQN_NONE)
                        dst_bus_sel = APBBR_ADDRSEL_APB;
                else
                        dst_bus_sel = APBBR_ADDRSEL_AHB;

		channel_cmd |= ((uint32_t)(APBBR_DMA_SRCADDRSEL_MASK &
					(dst_bus_sel << APBBR_DMA_SRCADDRSEL_BIT)) |
				(((uint32_t)apb_req->dst_index << APBBR_DMA_SREQSEL_SHIFT) & APBBR_DMA_SREQSEL_MASK));

		/* - CMD outport */
		OUT32(channel_base + APBBR_DMA_CMD_OFFSET, channel_cmd);

	}
	return status;

}
void set_drq_transfer_size(DMAD_CHANNEL_REQUEST_DESC *ch_req, DMAD_DRB *drb)
{
	int data_width =  -1;
	if (ch_req->controller == DMAD_DMAC_AHB_CORE) {
		/* AHB DMA */
		DMAD_AHBCH_REQUEST *ahb_req = (DMAD_AHBCH_REQUEST *)(&ch_req->ahbch_req);
		if (drb->src_index == DMAC_REQN_NONE && drb->src_index == DMAC_REQN_NONE) 
			data_width = 0; 
		else {
			if (drb->src_index != DMAC_REQN_NONE)
				data_width = 2 - ahb_req->src_width;
			else if (drb->dst_index != DMAC_REQN_NONE)
				data_width = 2 - ahb_req->dst_width;
		}
	} else {
		/* APB DMA */
		DMAD_APBCH_REQUEST *apb_req = (DMAD_APBCH_REQUEST *)(&ch_req->apbch_req);
		data_width = 2 - apb_req->data_width; 
	}
	if (data_width < 0) 
		KASSERT(1);

	drb->transfer_size = drb->req_size << data_width;
}
/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_submit_request
 *
 * DESCRIPTION
 *
 *   This function is used to submit a DRB (DMA request block) to a DMA
 *   channel.  DRB is used to queue all DMA submission requests for the
 *   channel.  Submitted DRB node is moved from the ready-list to the
 *   submitted-list.  DMA kick-off is performed automatically if the DMA
 *   transaction has not started.  When the DRB is completed, it will be
 *   removed from the submittied-list to the free-list in the DMA ISR.
 *
 * INPUTS
 *
 *   ch_req     : (in) Pointer to the DMA request descriptor structure
 *   drb        : (in) Pointer of a DRB struct to be submitted.
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful submission,
 *                else positive value is DMAD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _dmad_submit_request(DMAD_CHANNEL_REQUEST_DESC *ch_req, DMAD_DRB *drb){

	uint32_t	status = HAL_SUCCESS;
	DMAD_DRQ	*drq;
	uint32_t	core_intl;

	if (ch_req == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	drq = (DMAD_DRQ *)ch_req->drq;

	if (drq == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	/* Obtain exclusive access to the drq from other tasks */
	if (hal_current() != HAL_NULL){

		/*
		 * Suspending is only valid to the current task -- no need to lock if invoked from HISR
		 * Lock DMA queue to prevent been updated by other tasks
		 */
		status = hal_wait_for_mutex(&drq->drb_pool_mutex, HAL_SUSPEND);
		if (status != HAL_SUCCESS)
			return status;
	}

	/* Following code require _safe_exit return path */
	if ((drq->rdy_head == 0) || (drb->node == 0) || (drb->node >= DMAD_DRB_POOL_SIZE)){

		status = HAL_ERR_INVALID_ENTRY;
		goto _safe_exit;
	}

	_dmad_detach_node(drq->drb_pool, &drq->rdy_head, &drq->rdy_tail, drb->node);

	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);

	/*
	 * writeback d-cache if necessary
	 *
	 * Note: Here we take the assumption that, after writeback, the memory
	 *       contents is in physical ram and valid for for dma transfer.
	 *       Hence, we only need to do writeback at the beginning of the drb
	 *       submission, and ignore the writeback before kicking off every
	 *       drb in isr.
	 *
	 *       Place writeback code before interrupt-disable to shorten the
	 *       disable time.  This might generate a penalty of cache-miss
	 *       if the writeback routine also invalidated the cache contents.
	 */

	set_drq_transfer_size(ch_req, drb);
#if ( defined(CONFIG_CPU_DCACHE_ENABLE) && !defined(CONFIG_CPU_DCACHE_WRITETHROUGH) )
	/* source is memory */
	//if (drq->dc_writeback != HAL_NULL && drb->src_index == DMAC_REQN_NONE) 
	if ( (unsigned long)drb->src_addr >= NTC0_BONDER_START && (unsigned long)drb->src_addr < NTC0_BONDER_END )//JUNIOR@2013/05/16	
		drq->dc_writeback((unsigned long)(drb->src_addr),(unsigned long)(drb->src_addr) + (unsigned long)(drb->transfer_size));
#endif
	/* Check if submission is performed to an empty queue */
	if (drq->sbt_head == 0){

		_dmad_attach_tail(drq->drb_pool, &drq->sbt_head, &drq->sbt_tail, drb->node);
		drb->state = DMAD_DRB_STATE_SUBMITTED;

		hal_global_int_ctl(core_intl);

		/* pre-submission-programming */
		if (drb->psp)
			drb->psp(drb->data);

		/* DMA is not running, so kick off transmission */
		if (ch_req->controller == DMAD_DMAC_AHB_CORE){ /* AHB */

			/* Source and destination address */
			OUT32(drq->channel_base + DMAC_SRC_ADDR_OFFSET, drb->src_addr);
			OUT32(drq->channel_base + DMAC_DST_ADDR_OFFSET, drb->dst_addr);

			/* Transfer size (in units of source width) */
			OUT32(drq->channel_base + DMAC_SIZE_OFFSET, drb->req_size);

			/* Enable DMA channel (Kick off transmission when client enable it's transfer state) */
			SETB32(drq->channel_base + DMAC_CSR_OFFSET, DMAC_CSR_CH_EN_BIT);
		}
		else { /* APB */

			/* Source and destination address */
			OUT32(drq->channel_base + APBBR_DMA_SAD_OFFSET, drb->src_addr);
			OUT32(drq->channel_base + APBBR_DMA_DAD_OFFSET, drb->dst_addr);

			/* Transfer size (in units of source width) */
			OUT32(drq->channel_base + APBBR_DMA_CYC_OFFSET, drb->req_size & APBBR_DMA_CYC_MASK);

			/* Enable DMA channel (Kick off transmission when client enable it's transfer state) */
			SETB32(drq->channel_base + APBBR_DMA_CMD_OFFSET, APBBR_DMA_CHEN_BIT);
		}
	}
	else {
		/* DMA is already running, so only queue DRB to the end of the list */
		_dmad_attach_tail(drq->drb_pool, &drq->sbt_head, &drq->sbt_tail, drb->node);
		drb->state = DMAD_DRB_STATE_SUBMITTED;

		hal_global_int_ctl(core_intl);
	}

_safe_exit:

	/* Release locking of this function from other tasks */
	if (hal_current() != HAL_NULL){

		/*
		 * Suspending is only valid to the current task -- no need to lock if invoked from HISR
		 * Unlock DMA queue to allow its access from other tasks
		 */
		hal_release_mutex(&drq->drb_pool_mutex);
	}

	return status;
}

/*****************************************************************************
 * FUNCTION
 *
 *   _dmad_cancel_request
 *
 * DESCRIPTION
 *
 *   This function is used to cancel a submitted DRB (DMA request block)
 *   of a DMA channel.  DRB is used to queue all DMA submission requests for
 *   the channel.  Submitted DRB node is moved from the ready-list to the
 *   submitted-list.  Cancellation will fail if the DRB has already been
 *   kicked off and is waiting to be completed.
 *
 * INPUTS
 *
 *   ch_req     : (in) Pointer to the DMA request descriptor structure
 *   drb        : (in) Pointer of a DRB struct to be cancelled.
 *
 * OUTPUTS
 *
 *   uint32_t     : Returns HAL_SUCCESS if successful cancellation,
 *                else positive value is DMAD-specific error code,
 *                else negative value is NU system error code.
 *
 ****************************************************************************/
uint32_t _dmad_cancel_request(DMAD_CHANNEL_REQUEST_DESC *ch_req, DMAD_DRB *drb){

	DMAD_DRQ *drq;;

	if (ch_req == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	drq = (DMAD_DRQ *)ch_req->drq;

	if (drq == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	if (drq->sbt_head == 0)
		return HAL_ERR_INVALID_ENTRY;

	if ((drb->node == 0) || (drb->node >= DMAD_DRB_POOL_SIZE))
		return HAL_ERR_INVALID_ENTRY;

	if (drb->completion_sem != HAL_NULL)
		hal_destroy_semaphore(drb->completion_sem);

	// NDS_DCache_Enable();

	return HAL_ERR_UNAVAILABLE;
}

uint32_t _dmad_wait(DMAD_CHANNEL_REQUEST_DESC *ch_req){

	uint32_t	status = HAL_SUCCESS;
	DMAD_DRQ	*drq;
	uint32_t	core_intl;

	if (ch_req == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	drq = (DMAD_DRQ *)ch_req->drq;

	if (drq == HAL_NULL)
		return HAL_ERR_INVALID_POINTER;

	/* Obtain exclusive access to the drq from other tasks */
	if (hal_current() != HAL_NULL){

		/*
		 * Suspending is only valid to the current task -- no need to lock if invoked from HISR.
		 * Lock DMA queue to prevent been updated by other tasks
		 */
		status = hal_wait_for_mutex(&drq->drb_pool_mutex, HAL_SUSPEND);
		if (status != HAL_SUCCESS)
			return status;
	}

#ifdef DMAD_POLLING
	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);

	while (drq->sbt_head != 0){

		hal_global_int_ctl(core_intl);
		hal_sleep(50);
		core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);
	}
#else
	status = hal_pend_semaphore(&drq->drb_sem, 300);

	if (status == HAL_ERR_TIMEOUT){

		status = HAL_ERR_NO_MEMORY;
		goto _safe_exit;
	}
	else if (status != HAL_SUCCESS){

		goto _safe_exit;
	}

	core_intl = hal_global_int_ctl(HAL_DISABLE_INTERRUPTS);
#endif
	hal_global_int_ctl(core_intl);
	goto _safe_exit;

_safe_exit:

	/* Release locking of this function from other tasks */
	if (hal_current() != HAL_NULL){

		/*
		 * Suspending is only valid to the current task -- no need to lock if invoked from HISR.
		 * Unlock DMA queue to allow its access from other tasks
		 */
		hal_release_mutex(&drq->drb_pool_mutex);
	}

	return status;
}
