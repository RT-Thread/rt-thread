/******************************************************************************
**
** \file      gd_dma.h
**
** \brief     DEMO test application.
**
**            (C) Goke Microelectronics China 2002 - 2007
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version   \$Id: gd_timer.h,v 1.8 2007/01/04 15:13:22 mneuma Exp $
**
******************************************************************************/

#ifndef _GD_DMA_H_
#define _GD_DMA_H_

#include <gtypes.h>
#include <gmodids.h>

//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************

#ifdef GK710X
    #define DMA_RX_REG (REG_I2S_RX_DMA-0x30000000)
    #define DMA_TX_REG (REG_I2S_TX_LEFT_DMA-0x30000000)
#else
    #define DMA_RX_REG (REG_I2S_RX_DMA)
    #define DMA_TX_REG (REG_I2S_TX_LEFT_DMA)
#endif

/****************************/
/* DMA Channel Assignments  */
/****************************/

#define DMA_CHAN_MAX_NUM    4  
#define DMA_CHAN_MAX_DESC   32 /* max descriptor per channel */
#define DMA_BUFF_ADDR_ALIGN 8 


/* General DMA instance channel */
#define DMA_CHAN_NULL       0
#define DMA_CHAN_I2S_RX     1
#define DMA_CHAN_I2S_TX     2
#define DMA_CHAN_AUDIO_RX   1
#define DMA_CHAN_AUDIO_TX   2
#define DMA_CHAN_USB        3


#define DMA_MODE_NORMAL 	0
#define DMA_MODE_DESCRIPTOR 1


/* DMA_CHAN_CTRL_REG */
#define DMA_CHAN_CTRL_EN        0x80000000
#define DMA_CHAN_CTRL_D         0x40000000
#define DMA_CHAN_CTRL_WM        0x20000000
#define DMA_CHAN_CTRL_RM        0x10000000
#define DMA_CHAN_CTRL_NI        0x08000000
#define DMA_CHAN_CTRL_BLK_1024B 0x07000000
#define DMA_CHAN_CTRL_BLK_512B  0x06000000
#define DMA_CHAN_CTRL_BLK_256B  0x05000000
#define DMA_CHAN_CTRL_BLK_128B  0x04000000
#define DMA_CHAN_CTRL_BLK_64B   0x03000000
#define DMA_CHAN_CTRL_BLK_32B   0x02000000
#define DMA_CHAN_CTRL_BLK_16B   0x01000000
#define DMA_CHAN_CTRL_BLK_8B    0x00000000
#define DMA_CHAN_CTRL_TS_8B     0x00C00000
#define DMA_CHAN_CTRL_TS_4B     0x00800000
#define DMA_CHAN_CTRL_TS_2B     0x00400000
#define DMA_CHAN_CTRL_TS_1B     0x00000000

/* DMA descriptor bit fields */
#define DMA_DESC_EOC            0x01000000
#define DMA_DESC_WM             0x00800000
#define DMA_DESC_RM             0x00400000
#define DMA_DESC_NI             0x00200000
#define DMA_DESC_TS_8B          0x00180000
#define DMA_DESC_TS_4B          0x00100000
#define DMA_DESC_TS_2B          0x00080000
#define DMA_DESC_TS_1B          0x00000000
#define DMA_DESC_BLK_1024B      0x00070000
#define DMA_DESC_BLK_512B       0x00060000
#define DMA_DESC_BLK_256B       0x00050000
#define DMA_DESC_BLK_128B       0x00040000
#define DMA_DESC_BLK_64B        0x00030000
#define DMA_DESC_BLK_32B        0x00020000
#define DMA_DESC_BLK_16B        0x00010000
#define DMA_DESC_BLK_8B         0x00000000
#define DMA_DESC_ID             0x00000004
#define DMA_DESC_IE             0x00000002
#define DMA_DESC_ST             0x00000001

/* DMA_CHAN_STATE_REG */
#define DMA_CHAN_STATE_DM        0x80000000
#define DMA_CHAN_STATE_OE        0x40000000
#define DMA_CHAN_STATE_DA        0x20000000
#define DMA_CHAN_STATE_DD        0x10000000
#define DMA_CHAN_STATE_OD        0x08000000
#define DMA_CHAN_STATE_ME        0x04000000
#define DMA_CHAN_STATE_BE        0x02000000
#define DMA_CHAN_STATE_RWE       0x01000000
#define DMA_CHAN_STATE_AE        0x00800000
#define DMA_CHAN_STATE_DN        0x00400000


//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Data Structures
//*****************************************************************************
//*****************************************************************************

typedef void (*GD_DMA_NOTIFIER_F)(void);

typedef struct dma_descriptor_s
{
    U32 srcAddr;        /*  Source address */
    U32 dstAddr;        /* Destination address */
    struct dma_descriptor_s *next; /* Pointing to next descriptor */
    U32 reportAddr;     /* The physical address to store DMA hardware reporting status */
    U32 dataLength;     /* Transfer byte count , max value = 2^22 */
    U32 descAttr;       /* Descriptor 's attribute */
}GD_DMA_DESCRIPTOR_S;

typedef struct
{
    U32      channel;
    U32      mode;
	GD_DMA_NOTIFIER_F intNotifier;
}GD_DMA_OPEN_PARAM_S;


//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

GERR GD_DMA_Init(void);
GERR GD_DMA_Exit(void);
GERR GD_DMA_Open(GD_DMA_OPEN_PARAM_S *openParam, GD_HANDLE *handle);
GERR GD_DMA_Close(GD_HANDLE handle);
GERR GD_DMA_AddDescriptor(GD_HANDLE handle, GD_DMA_DESCRIPTOR_S *descriptor);
GERR GD_DMA_Start(GD_HANDLE handle, U32 desc);
GERR GD_DMA_Stop(GD_HANDLE handle);



#ifdef __cplusplus
}
#endif

#endif /* _GD_DMA_H_ */

