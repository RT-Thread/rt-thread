#ifndef DRV_SPI_H
#define DRV_SPI_H

#include <rtthread.h>
#include <rthw.h>



#define RFEMPTY 1
#define KSEG1_STORE8(addr,val)	 *(volatile char *)(0xffffffffa0000000 | addr) = val
#define KSEG1_LOAD8(addr)	 *(volatile char *)(0xffffffffa0000000 | addr) 

#define APB_MAX_SPEED 125000000U
#define APB_FREQSCALE (((KSEG1_LOAD8(0xffffffffbfe104d2)>>4)&0x7)+1)

#define SPI_BASE  0x1fff0220
#define PMON_ADDR 0xa1000000
#define FLASH_ADDR 0x000000

#define SPCR      0x0
#define SPSR      0x1
#define FIFO	  0x2
#define TXFIFO    0x2
#define RXFIFO    0x2
#define SPER      0x3
#define PARAM     0x4
#define SOFTCS    0x5
#define PARAM2    0x6




#define SET_SPI(addr,val)        KSEG1_STORE8(SPI_BASE+addr,val)
#define GET_SPI(addr)            KSEG1_LOAD8(SPI_BASE+addr)



//void spi_init(uint8_t ,uint8_t,uint8_t);
//void spi_set_csn(uint8_t);
//uint8_t spi_write_for_response(uint8_t);


#endif
