/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : usb_conf.h
* Author             : MCD Application Team
* Version            : V3.1.0
* Date               : 10/30/2009
* Description        : Mass Storage Demo configuration header
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CONF_H
#define __USB_CONF_H

/*-------------------------------------------------------------*/
/* EP_NUM */
/* defines how many endpoints are used by the device */
/*-------------------------------------------------------------*/
#define EP_NUM                          (3)

#ifndef STM32F10X_CL
/*-------------------------------------------------------------*/
/* --------------   Buffer Description Table  -----------------*/
/*-------------------------------------------------------------*/
/* buffer table base address */

#define BTABLE_ADDRESS      (0x00)

/* EP0  */
/* rx/tx buffer base address */
#define ENDP0_RXADDR        (0x18)
#define ENDP0_TXADDR        (0x58)

/* EP1  */
/* tx buffer base address */
#define ENDP1_TXADDR        (0x98)

/* EP2  */
/* Rx buffer base address */
#define ENDP2_RXADDR        (0xD8)


/* ISTR events */
/* IMR_MSK */
/* mask defining which events has to be handled */
/* by the device application software */
#define IMR_MSK (CNTR_CTRM  | CNTR_RESETM)
#endif /* STM32F10X_CL */

/* CTR service routines */
/* associated to defined endpoints */
//#define  EP1_IN_Callback   NOP_Process
#define  EP2_IN_Callback   NOP_Process
#define  EP3_IN_Callback   NOP_Process
#define  EP4_IN_Callback   NOP_Process
#define  EP5_IN_Callback   NOP_Process
#define  EP6_IN_Callback   NOP_Process
#define  EP7_IN_Callback   NOP_Process


#define  EP1_OUT_Callback   NOP_Process
//#define  EP2_OUT_Callback   NOP_Process
#define  EP3_OUT_Callback  NOP_Process
#define  EP4_OUT_Callback   NOP_Process
#define  EP5_OUT_Callback   NOP_Process
#define  EP6_OUT_Callback   NOP_Process
#define  EP7_OUT_Callback   NOP_Process

#ifdef STM32F10X_CL

/* OTGD-FS-DEVICE IP interrupts Enable definitions */
/* Uncomment the define to enable the selected interrupt */
//#define INTR_MODEMISMATCH
#define INTR_SOFINTR
#define INTR_RXSTSQLVL           /* Mandatory */
//#define INTR_NPTXFEMPTY
//#define INTR_GINNAKEFF
//#define INTR_GOUTNAKEFF
//#define INTR_ERLYSUSPEND
#define INTR_USBSUSPEND          /* Mandatory */
#define INTR_USBRESET            /* Mandatory */
#define INTR_ENUMDONE            /* Mandatory */
//#define INTR_ISOOUTDROP
#define INTR_EOPFRAME
//#define INTR_EPMISMATCH
#define INTR_INEPINTR            /* Mandatory */
#define INTR_OUTEPINTR           /* Mandatory */
//#define INTR_INCOMPLISOIN
//#define INTR_INCOMPLISOOUT
#define INTR_WKUPINTR            /* Mandatory */

/* OTGD-FS-DEVICE IP interrupts subroutines */
/* Comment the define to enable the selected interrupt subroutine and replace it
   by user code */
#define  INTR_MODEMISMATCH_Callback      NOP_Process
#define  INTR_SOFINTR_Callback           NOP_Process
#define  INTR_RXSTSQLVL_Callback         NOP_Process
#define  INTR_NPTXFEMPTY_Callback        NOP_Process
#define  INTR_NPTXFEMPTY_Callback        NOP_Process
#define  INTR_GINNAKEFF_Callback         NOP_Process
#define  INTR_GOUTNAKEFF_Callback        NOP_Process
#define  INTR_ERLYSUSPEND_Callback       NOP_Process
#define  INTR_USBSUSPEND_Callback        NOP_Process
#define  INTR_USBRESET_Callback          NOP_Process
#define  INTR_ENUMDONE_Callback          NOP_Process
#define  INTR_ISOOUTDROP_Callback        NOP_Process
#define  INTR_EOPFRAME_Callback          NOP_Process
#define  INTR_EPMISMATCH_Callback        NOP_Process
#define  INTR_INEPINTR_Callback          NOP_Process
#define  INTR_OUTEPINTR_Callback         NOP_Process
#define  INTR_INCOMPLISOIN_Callback      NOP_Process
#define  INTR_INCOMPLISOOUT_Callback     NOP_Process
#define  INTR_WKUPINTR_Callback          NOP_Process

/* Isochronous data update */
#define  INTR_RXSTSQLVL_ISODU_Callback   NOP_Process  

/* Isochronous transfer parameters */
/* Size of a single Isochronous buffer (size of a single transfer) */
#define ISOC_BUFFER_SZE                  1
/* Number of sub-buffers (number of single buffers/transfers), should be even */
#define NUM_SUB_BUFFERS                  2

#endif /* STM32F10X_CL */

#endif /* __USB_CONF_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
