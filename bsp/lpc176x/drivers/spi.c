/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "LPC17xx.h"                              /* LPC17xx definitions    */
#include "spi.h"

/* bit definitions for register SSPCR0. */
#define SSPCR0_DSS      0
#define SSPCR0_CPOL     6
#define SSPCR0_CPHA     7
#define SSPCR0_SCR      8
/* bit definitions for register SSPCR1. */
#define SSPCR1_SSE      1
/* bit definitions for register SSPSR. */
#define SSPSR_TFE       0
#define SSPSR_TNF       1
#define SSPSR_RNE       2
#define SSPSR_RFF       3
#define SSPSR_BSY       4

/* Local functions */
static uint8_t LPC17xx_SPI_SendRecvByte (uint8_t byte_s);

/* Initialize the SSP0, SSP0_PCLK=CCLK=72MHz */
void LPC17xx_SPI_Init (void)
{
    uint32_t dummy;

    dummy = dummy; // avoid warning

#if 0
    /* Initialize and enable the SSP0 Interface module. */
    LPC_SC->PCONP |= (1 << 21);          /* Enable power to SSPI0 block  */

    /* SSEL is GPIO, output set to high. */
    LPC_GPIO0->FIODIR  |=  (1<<16);             /* P0.16 is output */
    LPC_PINCON->PINSEL1 &= ~(3<<0);             /* P0.16 SSEL (used as GPIO) */
    LPC17xx_SPI_DeSelect ();                    /* set P0.16 high (SSEL inactiv) */

    /* SCK, MISO, MOSI are SSP pins. */
    LPC_PINCON->PINSEL0 &= ~(3UL<<30);          /* P0.15 cleared */
    LPC_PINCON->PINSEL0 |=  (2UL<<30);          /* P0.15 SCK0 */
    LPC_PINCON->PINSEL1 &= ~((3<<2) | (3<<4));  /* P0.17, P0.18 cleared */
    LPC_PINCON->PINSEL1 |=  ((2<<2) | (2<<4));  /* P0.17 MISO0, P0.18 MOSI0 */
#else
    LPC_SC->PCONP       |= (1 << 21);           /* Enable power to SSPI0 block */

    /* SSEL is GPIO, output set to high. */
    LPC_GPIO1->FIODIR   |=  (1<<21);            /* P1.21 is output             */
    LPC_GPIO1->FIOPIN   |=  (1<<21);            /* set P1.21 high (SSEL inact.)*/
    LPC_PINCON->PINSEL3 &= ~(0<<10);             /* P1.21 SSEL (used as GPIO)   */

    /* P3.26 is SD Card Power Supply Enable Pin */
    LPC_GPIO3->FIODIR   |=  (1<<26);            /* P3.26 is output             */
    LPC_GPIO3->FIOPIN   &= ~(1<<26);            /* set P3.26 low(enable power) */

    /* SCK, MISO, MOSI are SSP pins. */
    LPC_PINCON->PINSEL3 &= ~(3UL<<8);          /* P1.20 cleared               */
    LPC_PINCON->PINSEL3 |=  (3UL<<8);          /* P1.20 SCK0                  */
    LPC_PINCON->PINSEL3 &= ~((3<<14) | (3<<16));  /* P1.23, P1.24 cleared        */
    LPC_PINCON->PINSEL3 |=  ((3<<14) | (3<<16));  /* P1.23 MISO0, P1.24 MOSI0    */
#endif

    /* PCLK_SSP0=CCLK */
    LPC_SC->PCLKSEL1 &= ~(3<<10);               /* PCLKSP0 = CCLK/4 (18MHz) */
    LPC_SC->PCLKSEL1 |=  (1<<10);               /* PCLKSP0 = CCLK   (72MHz) */

    LPC_SSP0->CR0  = 0x0007;                    /* 8Bit, CPOL=0, CPHA=0         */
    LPC_SSP0->CR1  = 0x0002;                    /* SSP0 enable, master          */

    LPC17xx_SPI_SetSpeed (SPI_SPEED_400kHz);

    /* wait for busy gone */
    while( LPC_SSP0->SR & ( 1 << SSPSR_BSY ) );

    /* drain SPI RX FIFO */
    while( LPC_SSP0->SR & ( 1 << SSPSR_RNE ) )
    {
        dummy = LPC_SSP0->DR;
    }
}

/* Close SSP0 */
void LPC17xx_SPI_DeInit( void )
{
    // disable SPI
    LPC_SSP0->CR1  = 0;

#if 0
    // Pins to GPIO
    LPC_PINCON->PINSEL0 &= ~(3UL<<30);
    LPC_PINCON->PINSEL1 &= ~((3<<2) | (3<<4));
#else
    LPC_PINCON->PINSEL3 &= ~(3UL<<8);          /* P1.20 cleared               */
    LPC_PINCON->PINSEL3 &= ~((3<<14) | (3<<16));  /* P1.23, P1.24 cleared        */
#endif

    // disable SSP power
    LPC_SC->PCONP &= ~(1 << 21);
}

/* Set a SSP0 clock speed to desired value. */
void LPC17xx_SPI_SetSpeed (uint8_t speed)
{
    speed &= 0xFE;
    if ( speed < 2  ) {
        speed = 2 ;
    }
    LPC_SSP0->CPSR = speed;
}

/* SSEL: low */
void LPC17xx_SPI_Select ()
{
#if 0
    LPC_GPIO0->FIOPIN &= ~(1<<16);
#else
    LPC_GPIO1->FIOPIN &= ~(1<<21);            /* SSEL is GPIO, set to high.  */
#endif
}

/* SSEL: high */
void LPC17xx_SPI_DeSelect ()
{
#if 0
    LPC_GPIO0->FIOPIN |= (1<<16);
#else
    LPC_GPIO1->FIOPIN |= (1<<21);             /* SSEL is GPIO, set to high.  */
#endif
}

/* Send one byte then recv one byte of response. */
static uint8_t LPC17xx_SPI_SendRecvByte (uint8_t byte_s)
{
    uint8_t byte_r;

    LPC_SSP0->DR = byte_s;
    while (LPC_SSP0->SR & (1 << SSPSR_BSY) /*BSY*/);    /* Wait for transfer to finish */
    byte_r = LPC_SSP0->DR;

    return byte_r;                      /* Return received value */
}

/* Send one byte */
void LPC17xx_SPI_SendByte (uint8_t data)
{
    LPC17xx_SPI_SendRecvByte (data);
}

/* Recv one byte */
uint8_t LPC17xx_SPI_RecvByte ()
{
    return LPC17xx_SPI_SendRecvByte (0xFF);
}

/* Release SSP0 */
void LPC17xx_SPI_Release (void)
{
    LPC17xx_SPI_DeSelect ();
    LPC17xx_SPI_RecvByte ();
}


#if USE_FIFO
/* on LPC17xx the FIFOs have 8 elements which each can hold up to 16 bits */
#define FIFO_ELEM 8

/* Receive btr (must be multiple of 4) bytes of data and store in buff. */
void LPC17xx_SPI_RecvBlock_FIFO (uint8_t *buff, uint32_t btr)
{
    uint32_t hwtr, startcnt, i, rec;

    hwtr = btr/2;  /* byte number in unit of short */
    if ( btr < FIFO_ELEM ) {
        startcnt = hwtr;
    } else {
        startcnt = FIFO_ELEM;
    }

    LPC_SSP0 -> CR0 |= 0x0f;  /* DSS to 16 bit */

    for ( i = startcnt; i; i-- ) {
        LPC_SSP0 -> DR = 0xffff;  /* fill TX FIFO, prepare clk for receive */
    }

    do {
        while ( !(LPC_SSP0->SR & ( 1 << SSPSR_RNE ) ) ) {
            // wait for data in RX FIFO (RNE set)
        }
        rec = LPC_SSP0->DR;
        if ( i < ( hwtr - startcnt ) ) {
            LPC_SSP0->DR = 0xffff;  /* fill TX FIFO, prepare clk for receive */
        }
        *buff++ = (uint8_t)(rec>>8);
        *buff++ = (uint8_t)(rec);
        i++;
    } while ( i < hwtr );

    LPC_SSP0->CR0 &= ~0x08;  /* DSS to 8 bit */
}

/* Send 512 bytes of data block (stored in buff). */
void LPC17xx_SPI_SendBlock_FIFO (const uint8_t *buff)
{
    uint32_t cnt;
    uint16_t data;

    LPC_SSP0->CR0 |= 0x0f;  /* DSS to 16 bit */

    /* fill the FIFO unless it is full */
    for ( cnt = 0; cnt < ( 512 / 2 ); cnt++ )
    {
        /* wait for TX FIFO not full (TNF) */
        while ( !( LPC_SSP0->SR & ( 1 << SSPSR_TNF ) ) );

        data  = (*buff++) << 8;
        data |= *buff++;
        LPC_SSP0->DR = data;
    }

    /* wait for BSY gone */
    while ( LPC_SSP0->SR & ( 1 << SSPSR_BSY ) );

    /* drain receive FIFO */
    while ( LPC_SSP0->SR & ( 1 << SSPSR_RNE ) ) {
        data = LPC_SSP0->DR;
    }

    LPC_SSP0->CR0 &= ~0x08;  /* DSS to 8 bit */
}
#endif /* USE_FIFO */
