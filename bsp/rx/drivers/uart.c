/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "uart.h"
#include <stdint.h>
#include <stdbool.h>
#include "r_pdl_sci.h"
/* General RPDL function definitions */
#include "r_pdl_definitions.h"
#include "intrinsics.h"
#include "iorx62n.h"

//#include <string.h>


                          /* Clock selection control */
#define SCI_CKS_MIN     0
#define SCI_CKS_MAX     3
#define SCI_CKS_STEP    1


#define IPR_ADDRESS(a) ((volatile unsigned char *)&ICU.IPR[IPR_SCI0_ + a])
//#define IER_ADDRESS(a) ((volatile unsigned char *)&(ICU.IER[IER_SCI0_ERI0 + a])/sizeof(unsigned char))
#define ERI_ADDRESS(a) ((volatile unsigned char *)&ICU.IR[IR_SCI0_ERI0] + ((4 * a) / sizeof(unsigned char)) )
#define IER_ADDRESS(a) ((volatile unsigned char *)&ICU.IER[IER_SCI0_ERI0] + ((4 * a) / sizeof(unsigned char)) )
#define RXI_ADDRESS(a) ((volatile unsigned char *)&ICU.IR[IR_SCI0_RXI0] + ((4 * a) / sizeof(unsigned char)) )
#define TXI_ADDRESS(a) ((volatile unsigned char *)&ICU.IR[IR_SCI0_TXI0] + ((4 * a) / sizeof(unsigned char)) )
#define TEI_ADDRESS(a) ((volatile unsigned char *)&ICU.IR[IR_SCI0_TEI0] + ((4 * a) / sizeof(unsigned char)) )
#define  RXI_DTCER_ADDRESS(a) (( volatile unsigned char *)&ICU.DTCER[IR_SCI0_RXI0]+ ((4*a)/sizeof(unsigned char)))
#define  TXI_DTCER_ADDRESS(a) (( volatile unsigned char *)&ICU.DTCER[IR_SCI0_TXI0]+ ((4*a) / sizeof(unsigned char)))
//#define SCI1_USE_B
//#define SCI2_USE_B
//#define SCI3_USE_B
//#define SCI6_USE_B

#define SourceClk 12000000
#define rpdl_CGC_f_pclk SourceClk * 4
/* Idle output options */
#define SPACE   0
#define MARK    1

typedef int UART_ID_Type;
typedef int IRQn_Type;

#define SCI2_USE_B

struct rx_uart
{
    UART_ID_Type UART;
    volatile struct st_sci __sfr * sci;
};

static rt_err_t rx_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    #if 1
    struct rx_uart *uart;

    unsigned char smr_copy;
    unsigned char semr_copy;
    unsigned char scr_copy;
    unsigned char scmr_copy;
    unsigned long brr_divider;
    unsigned long bit_interval_counter;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct rx_uart *)serial->parent.user_data;

    if (uart->UART > 6) {
        return -RT_ERROR;
    }
    /* Initialise the working copies */
    smr_copy = 0x00u;
    scr_copy = 0x00u;
    semr_copy = 0x00u;
    scmr_copy = 0x72u;
    brr_divider = 0;

    switch (uart->UART) {
case 0:
        SYSTEM.MSTPCRB.BIT.MSTPB31 = 0;
        /* Enable the input buffer */
        PORT2.ICR.BIT.B2 = 1;
        /* Ensure the pin is set to input */
        PORT2.DDR.BIT.B2 = 0;
        /* Disable the USB0_DRPD output */
        IOPORT.PFKUSB.BIT.USBE = 0;
        /* Disable the MTIOC3B-A output */
        MTU3.TIORH.BIT.IOB = 0;
        /* Disable the TMO0 output */
        TMR0.TCSR.BIT.OSA = 0;
        TMR0.TCSR.BIT.OSB = 0;
        /* Disable the MTIOC1A output */
        MTU1.TIOR.BIT.IOA = 0;
        /* Set the idle state direction */
        PORT2.DDR.BIT.B0 = 1;
        PORT2.DR.BIT.B0 = 1;
        PORT2.ICR.BIT.B0 = 1;
        PORT2.ICR.BIT.B1 = 1;
        break;
    case 1:
        SYSTEM.MSTPCRB.BIT.MSTPB30 = 0;

        /* Disable the CS6#-C output */
        IOPORT.PF0CSE.BIT.CS6E = 0;
        /* Disable the MOSIB-A output */
        IOPORT.PFHSPI.BIT.MOSIE = 0;
        /* Disable the MTIOC2A output */
        MTU2.TIOR.BIT.IOA = 0;
        /* Disable the TMO1 output */
        TMR1.TCSR.BYTE = 0xF0u;
#ifdef SCI1_USE_B

        IOPORT.PFFSCI.BIT.SCI1S = 1;
        PORTF.DDR.BIT.B2 = 0;
        PORTF.ICR.BIT.B2 = 1;
        PORTF.DDR.BIT.B0 = 1;
        PORTF.DR.BIT.B0 = 1;
#else
        IOPORT.PFFSCI.BIT.SCI1S = 0;

        /* Set the idle state direction */
        PORT2.DDR.BIT.B6 = 1;
        PORT2.DR.BIT.B6 = 1;
//  PORT2.DR.BIT.B6 = 1;
        /* Enable the input buffer */
        //PORT3.ICR.BIT.B0 = 1;
        /* Ensure the pin is set to input */
        PORT3.DDR.BIT.B0 = 0;


#endif

        break;
    case 2:
        SYSTEM.MSTPCRB.BIT.MSTPB29 = 0;
        /* Disable the SSLB2-A output */
        IOPORT.PFHSPI.BIT.SSL2E = 0;

#ifdef SCI2_USE_B
        IOPORT.PFFSCI.BIT.SCI2S = 1;
        PORT5.DDR.BIT.B0 = 1;
        PORT5.DR.BIT.B0 = 1;
        PORT5.DDR.BIT.B2 = 0;
        PORT5.ICR.BIT.B2 = 1;
        /* Disable the SSLB1-A output */
        IOPORT.PFHSPI.BIT.SSL1E = 0;

#else
        IOPORT.PFFSCI.BIT.SCI2S = 0;
        /* Enable the input buffer */
        PORT1.ICR.BIT.B2 = 1;
        /* Ensure the pin is set to input */
        PORT1.DDR.BIT.B2 = 0;
        PORT1.DDR.BIT.B3 = 1;
        PORT1.DR.BIT.B3 = 1;
        /* Disable the TMO3 output */
        TMR3.TCSR.BYTE = 0xF0u;
#endif
        break;
    case 3:
        SYSTEM.MSTPCRB.BIT.MSTPB28 = 0;
#ifdef SCI3_USE_B
        IOPORT.PFFSCI.BIT.SCI3S = 1;
        PORT2.DDR.BIT.B5 = 0;
        PORT2.ICR.BIT.B5 = 1;
        PORT2.DDR.BIT.B3 = 1;
        PORT2.DR.BIT.B3 = 1;
        IOPORT.PF0CSE.BIT.CS4E = 0;
        /* Disable the USB0_VBUSEN-A output */
        IOPORT.PFKUSB.BIT.USBE = 0;
        /* Disable the MTIOC4A-A output */
        MTU4.TIORH.BIT.IOA = 0;
        /* Disable the USB0_DPUPE-A output */
        IOPORT.PFKUSB.BIT.USBE = 0;
        /* Disable the EDACK0-B output */
        EXDMAC0.EDMOMD.BIT.DACKE = 0;
        /* Disable the MTIOC3D-A output */
        MTU3.TIORL.BIT.IOD = 0;

#else

        IOPORT.PFFSCI.BIT.SCI3S = 0;
        /* Disable the MTIOC0B output */
        MTU0.TIORH.BIT.IOB = 0;
        PORT1.DDR.BIT.B6 = 0;
        PORT1.ICR.BIT.B6 = 1;
        PORT1.DDR.BIT.B7 = 1;
        PORT1.DR.BIT.B7 = 1;
        MTU3.TIORH.BIT.IOA = 0;
        /* Set the idle state direction */
#endif
        break;
        //case UartPort4:
        //  SYSTEM.MSTPCRB.BIT.MSTPB27 = 0;
        //  break;
    case 5:
        SYSTEM.MSTPCRB.BIT.MSTPB26 = 0;
        /* Enable the input buffer */
        PORTC.ICR.BIT.B1 = 1;
        /* Ensure the pin is set to input */
        PORTC.DDR.BIT.B1 = 0;
        PORTC.DDR.BIT.B3 = 1;
        PORTC.DR.BIT.B3 = 1;
        /* Disable the A17-A output */
        IOPORT.PF3BUS.BIT.A17E = 0;
        break;
    case 6:


        SYSTEM.MSTPCRB.BIT.MSTPB25 = 0;

#ifdef SCI6_USE_B
        IOPORT.PFFSCI.BIT.SCI6S = 1;
        PORT3.DDR.BIT.B3 = 0;
        //PORT3.ICR.BIT.B3 = 1;
        PORT3.DDR.BIT.B2 = 1;
        PORT3.DR.BIT.B2 = 1;
        /* Disable the MTIOC0A output */
        MTU0.TIORH.BIT.IOA = 0;
        /* Disable the CTX0 output */
        IOPORT.PFJCAN.BIT.CAN0E = 0;
        /* Disable the MTIOC0C output */
        MTU0.TIORL.BIT.IOC = 0;
#else
        IOPORT.PFFSCI.BIT.SCI6S = 0;
        PORT0.DDR.BIT.B0 = 1;
        PORT0.DR.BIT.B0 = 1;
        PORT0.ICR.BIT.B1 = 1;
        PORT0.DDR.BIT.B1 = 0;

#endif
        break;
    default:
        break;
    }


  /*stop bit*/
    if (cfg->stop_bits == STOP_BITS_2) {
        smr_copy |= BIT_3;
    } else if (cfg->stop_bits != STOP_BITS_1) {
        return  -RT_ERROR;
    }

    /*data bit*/
    if (cfg->data_bits == 7) {
        smr_copy |= BIT_6;
    } else if (cfg->data_bits != DATA_BITS_8) {
        return  -RT_ERROR;
    }

    /*parity*/
    if (cfg->parity == PARITY_ODD)
        smr_copy |= BIT_5;
        else if (cfg->parity == PARITY_EVEN)
            smr_copy |= BIT_4 | BIT_5;



    brr_divider = rpdl_CGC_f_pclk / cfg->baud_rate;
    /* There is a fixed division by 2 */
    brr_divider /= 16;

    /* Select 8 base clock cycles (ABCS = 1) */
    semr_copy |= (unsigned char)BIT_4;
    //brr_divider /= 8;
    /* More division required? */
    if (brr_divider > 256) {
        /* Select 16 base clock cycles (ABCS = 0) */
        semr_copy &= (unsigned char)INV_BIT_4;
        brr_divider /= 2;
    }

    /* Load the BRR reset value */
    //brr_copy = 0xFFu;


    /* Ensure bits TIE, RIE, TE, RE and TEIE in the SCR are 0 */
    uart->sci->SCR.BYTE = 0x00;

    /* Configure the CKE & MPIE bits */
    uart->sci->SCR.BYTE = scr_copy & (BIT_0 | BIT_1 | BIT_3);

    /* Configure the SMR register */
    uart->sci->SMR.BYTE = smr_copy;
    /* Configure the SCMR register */
    uart->sci->SCMR.BYTE = scmr_copy;
    /* Configure the SEMR register */
    uart->sci->SEMR.BYTE = semr_copy;
    /* Configure the BRR register */
    uart->sci->BRR = brr_divider - 1;

    bit_interval_counter = rpdl_CGC_f_pclk  / cfg->baud_rate;
    /* Wait for at least a 1-bit duration */
    do {
        bit_interval_counter--;
    }while (bit_interval_counter != 0);

    scr_copy = 0x00u;

    /*enable rx an tx*/
    scr_copy |= BIT_5  | BIT_4 ;

    uart->sci->SCR.BYTE &= 0x5B;
    uart->sci->SCR.BYTE |= scr_copy;

    *(IPR_ADDRESS(uart->UART)) = 5;
    uart->sci->SSR.BYTE = 0xC0;
    uart->sci->SSR.BYTE &= INV_BIT_5;
    while (uart->sci->SSR.BYTE & BIT_4);
    uart->sci->SSR.BYTE &= INV_BIT_3;
         #else
         struct rx_uart *uart;
            /* Declare error flag */
  bool err = true;
  uint32_t flag = 0;
  RT_ASSERT(serial != RT_NULL);
  uart = (struct rx_uart *)serial->parent.user_data;


  /* Configure the pin selection of SCI channel */
  err &=    R_SCI_Set
    (
    PDL_SCI_PIN_SCI2_B
    );

  uart->sci->SCR.BYTE |= BIT_4 | BIT_5;
  switch (cfg->parity) {
  case PARITY_ODD:
      flag |= PDL_SCI_PARITY_ODD;
      break;
  case PARITY_EVEN:
      flag |= PDL_SCI_PARITY_EVEN;
      break;
  default:
      flag |= PDL_SCI_PARITY_NONE;
      break;

  }

  switch (cfg->data_bits) {
  case DATA_BITS_7:
      flag |= PDL_SCI_7_BIT_LENGTH;
      break;
  case DATA_BITS_8:
      flag |= PDL_SCI_8_BIT_LENGTH;
      break;
  }

  switch (cfg->stop_bits) {
  case STOP_BITS_1:
      flag |= PDL_SCI_STOP_1;
      break;
  case STOP_BITS_2:
      flag |= PDL_SCI_STOP_2;
          break;
  }

  flag |= PDL_SCI_ASYNC |
      PDL_SCI_TX_CONNECTED |
      PDL_SCI_RX_CONNECTED |
      PDL_SCI_CLK_INT_IO ;
  /* Configure the RS232 port */
  err &=    R_SCI_Create(
    uart->UART,
    flag,
    cfg->baud_rate,
    5);

  uart->sci->SCR.BYTE |= BIT_4|BIT_5;

 __enable_interrupt();
    #endif

    switch (uart->UART) {
    case 0:

        //ier_copy |= BIT_6 | BIT_7;
        ICU.IER[IER_SCI0_ERI0].BIT.IEN_SCI0_ERI0 = 1;
        ICU.IER[IER_SCI0_RXI0].BIT.IEN_SCI0_RXI0 = 1;
        ICU.IER[IER_SCI0_TEI0].BIT.IEN_SCI0_TEI0 = 1;
        ICU.IER[IER_SCI0_TXI0].BIT.IEN_SCI0_TXI0 = 1;

        break;
    case 1:

        ICU.IER[IER_SCI1_ERI1].BIT.IEN_SCI1_ERI1 = 1;
        ICU.IER[IER_SCI1_RXI1].BIT.IEN_SCI1_RXI1 = 1;
        //ICU.IER[IER_SCI1_TEI1].BIT.IEN_SCI1_TEI1 = 1;
        //ICU.IER[IER_SCI1_TXI1].BIT.IEN_SCI1_TXI1 = 1;

        break;
    case 2:

        ICU.IER[IER_SCI2_ERI2].BIT.IEN_SCI2_ERI2 = 1;
        ICU.IER[IER_SCI2_RXI2].BIT.IEN_SCI2_RXI2 = 1;
        ICU.IER[IER_SCI2_RXI2].BIT.IEN_SCI2_TEI2 = 0;
        ICU.IER[IER_SCI2_TXI2].BIT.IEN_SCI2_TXI2 = 0;

        break;
    case 3:

        ICU.IER[IER_SCI3_ERI3].BIT.IEN_SCI3_ERI3 = 1;
        ICU.IER[IER_SCI3_RXI3].BIT.IEN_SCI3_RXI3 = 1;
        ICU.IER[IER_SCI3_TEI3].BIT.IEN_SCI3_TEI3 = 1;
        ICU.IER[IER_SCI3_TXI3].BIT.IEN_SCI3_TXI3 = 1;

        break;
    case 5:

        ICU.IER[IER_SCI5_ERI5].BIT.IEN_SCI5_ERI5 = 1;
        ICU.IER[IER_SCI5_RXI5].BIT.IEN_SCI5_RXI5 = 1;
        ICU.IER[IER_SCI5_TEI5].BIT.IEN_SCI5_TEI5 = 1;
        ICU.IER[IER_SCI5_TXI5].BIT.IEN_SCI5_TXI5 = 1;

        break;
    case 6:

        ICU.IER[IER_SCI6_ERI6].BIT.IEN_SCI6_ERI6 = 1;
        ICU.IER[IER_SCI6_RXI6].BIT.IEN_SCI6_RXI6 = 1;
        ICU.IER[IER_SCI6_TEI6].BIT.IEN_SCI6_TEI6 = 1;
        ICU.IER[IER_SCI6_TXI6].BIT.IEN_SCI6_TXI6 = 1;

        break;
    }

    return RT_EOK;
}

static rt_err_t rx_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct rx_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct rx_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        uart->sci->SCR.BIT.RIE = 0;
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        (void)(uart->sci->RDR);
        uart->sci->SCR.BIT.RIE = 1;
        break;
    }

    return RT_EOK;
}

static int rx_putc(struct rt_serial_device *serial, char c)
{
    struct rx_uart *uart;

    uart = (struct rx_uart *)serial->parent.user_data;
    while (uart->sci->SSR.BIT.TDRE == 0);
    uart->sci->TDR = c;
    return 1;
}

static int rx_getc(struct rt_serial_device *serial)
{

    struct rx_uart *uart;

    uart = (struct rx_uart *)serial->parent.user_data;
    if (uart->sci->SSR.BIT.RDRF)
        return (int) (uart->sci->RDR);

    return -1;
}

static const struct rt_uart_ops rx_uart_ops =
{
    rx_configure,
    rx_control,
    rx_putc,
    rx_getc,
};

#if defined(RT_USING_UART2)
/* UART0 device driver structure */
struct rx_uart uart2 =
{
    2,
    &SCI2,
};
struct rt_serial_device serial2;


#pragma vector = VECT_SCI2_ERI2
__interrupt void Interrupt_SCI2_ERI2(void)
{
  /* Will the user handle the errors? */
    /* Clear the error flags */
    SCI2.SSR.BYTE = (uint8_t)(BIT_7 | BIT_6);
}

#pragma vector = VECT_SCI2_RXI2
__interrupt void Interrupt_SCI2_RXI2(void)
{
  rt_interrupt_enter();
     rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
     rt_interrupt_leave();
}

#endif

void rt_hw_uart_init(void)
{
    struct rx_uart *uart;
    struct serial_configure config;

#ifdef RT_USING_UART2
    uart = &uart2;
    config.baud_rate = BAUD_RATE_38400;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    serial2.ops    = &rx_uart_ops;
    serial2.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR |
                          RT_DEVICE_FLAG_INT_RX |
                          RT_DEVICE_FLAG_STREAM,
                          uart);
#endif

}

