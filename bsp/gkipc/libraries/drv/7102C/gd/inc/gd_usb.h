/*!
*****************************************************************************
** \file        gd_lib/GK7101/inc/gd_usb.h
**
** \version     $Id$
**
** \brief       1
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2013 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/
#ifndef _GD_USB_H_
#define _GD_USB_H_



//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************
#define     HS_MSC_TEST
//#define     FS_MSC_TEST

//Switch of DMA FIFO CLR BUG Test 
//#define DMA_FIFO_CLR_TEST

//USB data transfer mode choose
//#define  USB_DATA_TRAN_MODE_PIO   // about 5.9MB ws, 4.4M rs;
#define  USB_DATA_TRAN_MODE_DMA
//#define  USB_DATA_TRAN_MODE_INT


#define TBLK_SZ_BYTES_8   8
#define TBLK_SZ_BYTES_16  16
#define TBLK_SZ_BYTES_32  32
#define TBLK_SZ_BYTES_64  64

#define DMA_TBLK_SZ_BYTES_8     0
#define DMA_TBLK_SZ_BYTES_16    1
#define DMA_TBLK_SZ_BYTES_32    2
#define DMA_TBLK_SZ_BYTES_64    3
// DMA transfer mode. The maximum of USB DMA Tx transfer is limited by USB PHY ahb general Reg(0x90020E08) to 64 Bytes.
#define USB_DMA_TBLK_SZ   TBLK_SZ_BYTES_32

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

extern void gd_clk_disable_usb();
extern void gd_clk_enable_usb();
extern void gd_clk_disable_all();
extern GERR GD_USB_PHY_FPGA_Init(void);
extern GERR GD_USB_PHY_Init(U8 GpioNumber);
extern GERR GD_USB_Init(void);
extern void GD_USB_In_tranTx(U8 *p, U32 len);
extern void GD_USB_Control_in(const U8 *p, U32 *length, U32 len0_flag);
extern void GD_USB_Init_msc_pipe(void);
extern GERR GD_USB_Set_EP_Index(U8 idx);
extern GERR GD_USB_Set_CSR0L(U8 data);
extern GERR GD_USB_Get_CSR0L(U8 *pdata);
extern GERR GD_USB_Set_FADDR(U8 data);
extern GERR GD_USB_Set_RXCSRL(U8 data);
extern GERR GD_USB_Get_RXCSRL(U8 *data);
extern GERR GD_USB_Set_TXCSRH(U8 data);
extern GERR GD_USB_Get_POWER(U8 *data);
extern GERR GD_USB_Read_Rx_Count(U8 cntType, U32 *data);
extern GERR GD_USB_Read_EP_FIFOx(U8 aryData[], U32 reqBytesNum, U8 epIdx);
extern GERR GD_USB_DMA_In_TranRx(U32 host_write_addr, U32 host_write_len);
extern GERR GD_USB_DMA_Out_TranTx(U32 read_addr, U32 read_len);
extern GERR GD_USB_DMA_Out_TranTx_Fix_BugDMA(U32 read_addr, U32 read_len);

#ifdef GK710X
extern GERR GD_USB_Read_Clear_IntrRx(U16 *pINT);
extern GERR GD_USB_Read_Clear_IntrTx(U16 *pINT);
#else
extern GERR GD_USB_IRQ_In_TranRx_Set(U32 host_write_addr, U32 host_write_len);
extern GERR GD_USB_IRQ_Out_TranTx_Set(U32 hs_read_addr, U32 hs_read_len);
extern GERR GD_USB_Read_Clear_IntrTx_L(U8 *pINT);
extern GERR GD_USB_Read_Clear_IntrRx_L(U8 *pINT);
extern void GD_USB_PIO_In_tran_tx(U32 *p, U32 len);
extern void GD_USB_PIO_In_tran_rx(U32 *p, U32 len);
#endif

#ifdef __cplusplus
}
#endif



#endif /* _GD_USB_H_ */

