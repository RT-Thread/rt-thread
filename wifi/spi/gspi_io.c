/*
 * 	File: gspi_io.c
 * 	Desc: Low level SSP driver on pxa27x for GSPI
 *
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */
/********************************************************
Change log:
	01/30/06: Add kernel 2.6 support for GSPI8xxx/Bulverde
********************************************************/
#include    "sep4020.h"
#include    "rtthread.h"
#include	"gspi_io.h"
#include	"gspi_debug.h"
static int DMA_ENABLE=1;
int g_dummy_clk_reg = 0;
int g_dummy_clk_ioport = 0;
int g_bus_mode_reg = 0x02;
gspihost_info_t *G_gspiinfo;
static struct rt_semaphore gspi_lock;
static struct   rt_event txrxevent;	 //only set or rec the 0x01
#define DMA_TX_ONLY (1)
#define DMA_TX_RX (2)
#define DMA_Dummy_TX (4)
#define DMA_NO_ACTION (0)
static char DMA_ACTION; 
#define MaskWarning(x) ((x)=(x))
extern void rt_hw_interrupt_install(rt_uint32_t vector, rt_isr_handler_t new_handler, rt_isr_handler_t *old_handler);
extern void rt_hw_interrupt_umask(rt_uint32_t vector);
static int gspi_acquire_io(void)
{

   	rt_sem_take(&gspi_lock, RT_WAITING_FOREVER);
       return 0;
}
static void gspi_release_io(void)
{
   
   rt_sem_release(&gspi_lock);
   return;
}
static char transmittembuf[2048];
void setup_write_dma(char * data ,int n)
{
       unsigned int regval=0; 
	int i;

    /*clear the interupt*/
    /*0 is  tx channel */
    *(volatile unsigned long*)DMAC_INTINTERRCLR_V |= 0x1;
    *(volatile unsigned long*)DMAC_INTINTERRCLR_V &= (~0x1); //clear the erro interupt

    *(volatile unsigned long*)DMAC_INTTCCLEAR_V |= 0x1;
    *(volatile unsigned long*)DMAC_INTTCCLEAR_V &= (~0x1); //clear the  interupt
    
    
    /*set source address*/
    *(volatile unsigned long*)DMAC_C0SRCADDR_V = (unsigned int)data;
   
   /*set target address*/
   *(volatile unsigned long*)DMAC_C0DESTADDR_V = SSI_DR;
   
    /*clear the size*/
    //*(volatile unsigned long*)DMAC_C0CONTROL_V = 0;
    
    //desc->dcmd |= DCMD_ENDIRQEN | n;
    
    /*set transfer size,data width is 2 bytes,burst size is 4*2bytes,source Address Increment*/
    regval=((n/2) <<14)+(0x1<<12)+(0x1<<9)+(0x1<<6)+((0x0)<<3)+(0x0);
    *(volatile unsigned long*)DMAC_C0CONTROL_V = regval;

    /*write data from memory to ssi*/
 //   *(volatile unsigned long*)DMAC_C0CONFIGURATION_V=0;
    *(volatile unsigned long*)DMAC_C0DESCRIPTOR_V = 0; 
    
   
    /* 2) start DMA channel */

    /*spi dma set*/
    *(volatile unsigned long*)SSI_DMATDLR_V=0x2;	//	(0x10009050)//tx DMA threadthold
    if(DMA_ACTION==DMA_TX_RX)
   {
 #if 0
	*(volatile unsigned long*)SSI_DMARDLR_V=0x2;
		*(volatile unsigned long*)SSI_DMACR_V|=(0x3);	//0x1 rxDMAenable 0x2 txDMAenable	
	   *(volatile unsigned long*)DMAC_C1CONFIGURATION_V =  ((0x5)<<7) +((0x2)<<1)+0x01;
	   *(volatile unsigned long*)DMAC_C0CONFIGURATION_V =  ((0x5)<<11)+((0x1)<<1)+0x01;
  #else	
	*(volatile unsigned long*)SSI_DMARDLR_V=0x4;
	*(volatile unsigned long*)SSI_DMACR_V|=(0x1);	//0x1 rxDMAenable 0x2 txDMAenable	
	*(volatile unsigned long*)DMAC_C1CONFIGURATION_V =  ((0x5)<<7) +((0x2)<<1)+0x01;
	for(i=0;i<n/2;i++)
	{
		while((*(volatile unsigned long*)SSI_SR_V&2)==0);
    	 	*(volatile unsigned long* )SSI_DR_V = 0;
	}
 #endif	
    }else if(DMA_ACTION==DMA_TX_ONLY)
    {
    	*(volatile unsigned long*)SSI_DMACR_V|=(0x1<<1);	//0x1 rxDMAenable 0x2 txDMAenable
    	*(volatile unsigned long*)DMAC_C0CONFIGURATION_V =  ((0x5)<<11)+((0x1)<<1)+0x01;
    	
    }


}


int gspi_write_data_direct(u8 * data, u16 reg, u16 n)
{
   
	int i;
	u16 *dat;
	rt_uint32_t e;
   	gspi_acquire_io();
    	/* N bytes are sent wrt to 16 bytes, convert it to 8 bytes */
    	n = (n * 2);

    	/*active CS signal*/
    	*(volatile unsigned long*)(GPIO_PORTD_DATA_V)&=~0x04;
    	reg |= 0x8000;

       rt_memcpy(transmittembuf, &reg, sizeof(u16));
       rt_memcpy(transmittembuf + sizeof(u16), data, (n - 2));

     if((n>16)&&(DMA_ENABLE==1))
   	{
     		//Write data  by DMA mode
     		DMA_ACTION=DMA_TX_ONLY;
     	 	setup_write_dma(transmittembuf,n);
		
     		rt_event_recv(&txrxevent,0x01,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&e);
     }else{
	 //Write data through SSDR by CPU mode
    		dat = (u16 *) transmittembuf;
              *(volatile unsigned long*)SSI_DMACR_V&=(~0x3);	//0x1 rxDMAenable 0x2 txDMAenable	
   		 for (i = 0; i < (n / 2); i++) {
            
        		while((*(volatile unsigned long*)SSI_SR_V&2)==0){}
        		*(volatile unsigned long*)SSI_DR_V = *dat++; //add  for 4020
		}
   	       if ((n % 4) != 0) {
           
                    while((*(volatile unsigned long*)SSI_SR_V&2)==0){}
      	             *(volatile unsigned long*)SSI_DR_V = 0;//add  for 4020
              }
         while((*(volatile unsigned long*)SSI_SR_V&1)==1);
   }   
   /*inactive CS frame*/
   	*(volatile unsigned long*)(GPIO_PORTD_DATA_V)|=0x04;
    	gspi_release_io();

    return 0;
}

int gspi_write_reg( u16 reg, u16 val)
{
    gspi_write_data_direct((u8 *) & val, reg, 2);

    return 0;
}

int gspi_write_data( u16 * data, u16 size)
{
    gspi_write_data_direct((u8 *) & data[1], data[0], 2);

    return 0;
}

static char rectembuf[2048+1024];
static char rxtxdummybuf[2048+1024];
void
gspi_write_to_read(int n,u16 reg,u16*data)
{
	u16 temp;
   /*config the receive channel*/
   /*set source address*/
    *(volatile unsigned long*)DMAC_C1SRCADDR_V = SSI_DR;
   
   /*set target address*/
   *(volatile unsigned long*)DMAC_C1DESTADDR_V = (unsigned int)data;
   
    /*clear the size*/
  //  *(volatile unsigned long*)DMAC_C1CONTROL_V = 0;	//~(0x3ffd000)
    
    /*set transfer size,data width is 2 bytes,burst size is 4*2bytes,source Address Increment*/
    *(volatile unsigned long*)DMAC_C1CONTROL_V =  ((n /2)<<14)+(1<<13) + (1<<9) + (1<<6)+((0x3)<<3) +(0x3);

    /*receive data from ssi*/  
    *(volatile unsigned long*)DMAC_C1CONFIGURATION_V =  ((0x5)<<7) +((0x2)<<1)+0x01;
    *(volatile unsigned long*)DMAC_C1DESCRIPTOR_V = 0;
#if 0	
   /*config the transfer channel*/
   /*set source address*/
    *(volatile unsigned long*)DMAC_C0SRCADDR_V = gspiinfo->phys_addr_rw;
   
   /*set target address*/
   *(volatile unsigned long*)DMAC_C0DESTADDR_V = SSI_DR;
   
    /*clear the size*/
    *(volatile unsigned long*)DMAC_C0CONTROL_V = ~(0x3ffd000);
    
    
    /*set transfer size,data width is 2 bytes,burst size is 4*2bytes,source Address Increment*/
    *(volatile unsigned long*)DMAC_C0CONTROL_V =  (n <<14)|(1<<12) | (1<<9) | (1<<6) |((011)<<3) | (011);

    /*write data from memory to ssi*/
    *(volatile unsigned long*)DMAC_C0CONFIGURATION_V =  ((0101)<<11) | ((01)<<1);
	
   /*set address of next descripor */
    *(volatile unsigned long*)DMAC_C0DESCRIPTOR_V = 0;
    *(volatile unsigned long*)DMAC_C1DESCRIPTOR_V = 0;

    /* Start Rx for read */
    *(volatile unsigned long*)DMAC_C1CONFIGURATION_V = 0x01; //enable channel 1
    /* Start Tx for dummy write */
    *(volatile unsigned long*)DMAC_C0CONFIGURATION_V = 0x01; //enable channel 0
#endif

#if 1
    /* Write the register to read */
    *(volatile unsigned long*)SSI_DMACR_V&=(~0x3);	//0x1 rxDMAenable 0x2 txDMAenable	
    *(volatile unsigned long* )SSI_DR_V = reg;
    while((*(volatile unsigned long*)SSI_SR_V&8))
    temp = *(volatile unsigned long* )SSI_DR_V;
	temp=temp;
#endif
	setup_write_dma(rxtxdummybuf ,n);
}

void setup_read_dma(u16 reg, u16 * data, int n)
{
  
   /*clear the interupt*/
   *(volatile unsigned long*)DMAC_INTINTERRCLR_V |= 0x2;
   *(volatile unsigned long*)DMAC_INTINTERRCLR_V &= (~0x2); //clear the erro interupt

   *(volatile unsigned long*)DMAC_INTTCCLEAR_V |= 0x2;
   *(volatile unsigned long*)DMAC_INTTCCLEAR_V &= (~0x2);
   


    gspi_write_to_read(n, reg,data);
}

int gspi_read_data_direct(u8 * data, u16 reg, u16 n)
{ 
    int fifonum=0;
    int i;
    u32 nothing;
    u16 *dat;
    rt_uint32_t e;
    int retry = 0;
    int timeout = 100;
	int dmaflag=0;

	MaskWarning(nothing);

    if (gspi_acquire_io()) {
        return -1;
    }
     
   	for(fifonum=0;fifonum<16;fifonum++)//clear fifo add by vincent for 4020 
   	{   
   	 	nothing = *(volatile unsigned long* )SSI_DR_V;
   	}   

   	n = ((n + g_dummy_clk_ioport) * 2);
  
       

   	/*active SPI CS */
   	 *(volatile unsigned long*)(GPIO_PORTD_DATA_V)&=~0x04;

        ///Process the data
#if 1
  	if(n>16&&(DMA_ENABLE==1))
       //if((DMA_ENABLE==1))
 	{  
 		DMA_ACTION=DMA_TX_RX;
		dmaflag=1;

 		do {
        		retry = 0;
			spi_debug3("DMA MODEL");	
			DMA_ACTION=DMA_TX_RX;
        		setup_read_dma(reg,(u16*) rectembuf, n);
        		rt_event_recv(&txrxevent,0x01,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&e);

        		if (rectembuf[(g_dummy_clk_ioport + 1) * 2] == 0xff) {
            			if (!rt_memcmp(&rectembuf[(g_dummy_clk_ioport + 1) * 2],&rxtxdummybuf[2], 5)) {
                		retry = 1;
            			}
        		}
    		} while ( retry && --timeout);

   		 if (!timeout) 
        	spi_debug1("Timeout for gspi_read_data_direct\n");
  	}else
#endif
      {    
  		dat=(u16*)rectembuf;
  	       *(volatile unsigned long*)SSI_DMACR_V&=(~0x3);	//0x1 rxDMAenable 0x2 txDMAenable	
    		 while((*(volatile unsigned long*)SSI_SR_V&2)==0); 
     		 *(volatile unsigned long* )SSI_DR_V = reg;
     		for (i = 0; i < (n / 2); i++) {  
        		while((*(volatile unsigned long*)SSI_SR_V&2)==0);
    	 		*(volatile unsigned long* )SSI_DR_V = 0;

	 		while((*(volatile unsigned long*)SSI_SR_V&8)==0);
     			*dat = *(volatile unsigned long* )SSI_DR_V;
     	
        		 dat++;    
     		}
  	}
    	*(volatile unsigned long*)(GPIO_PORTD_DATA_V)|=0x04;
	if(dmaflag==1)
	rt_memcpy(data, rectembuf + (g_dummy_clk_ioport + 1) * 2+12,
           (n - (g_dummy_clk_ioport + 1) * 2+12));
	else
	rt_memcpy(data, rectembuf + (g_dummy_clk_ioport + 1) * 2,
           (n - (g_dummy_clk_ioport + 1) * 2));

   	 gspi_release_io();

    return 0;
}

int gspi_read_data( u16 * data, u16 size)
{
    return gspi_read_data_direct((u8 *) & data[1], data[0], 2);
}

int gspi_read_reg( u16 reg, u16 * val)
{
    gspi_read_data_direct((u8 *) val, reg, 2);

    return 0;
}
extern  void sbi_interrupt(int vector);
static  void spi_interrupt(int dev)
{
   	unsigned int intstate;
	unsigned int rcl;
	MaskWarning(rcl);
	intstate=*(volatile unsigned long*)SSI_ISR_V;
     //  spi_debug1("spi spi_interrupt\r\n");
  	if(intstate&0x01)
  	{
	 spi_debug1("spi tx fifo empty\r\n");
	}
	if(intstate&(0x01<<1))
	{
	 spi_debug1("spi tx fifo up over\r\n");
	 rcl=*(volatile unsigned long*)SSI_TXOICR_V;
	}
	if(intstate&(0x01<<2))
	{
	 spi_debug1("spi Rx fifo down over\r\n");
	  rcl=*(volatile unsigned long*)SSI_RXUICR_V;
	}
	if(intstate&(0x01<<3))
	{
	 spi_debug1("spi rx fifo up over\r\n");
	 rcl=*(volatile unsigned long*)SSI_RXOICR_V;
	}
	if(intstate&(0x01<<4))
	{
	
	  spi_debug1("spi rx fifo full\r\n");
	
	}
	rcl=*(volatile unsigned long*)SSI_ICR_V;
	
}
 static void dma_interrupt(int dev)
{
   	unsigned int intstatus;
	unsigned int  endstatus;
	unsigned int errstatus;
	unsigned int rcl;
	rcl=rcl;
	intstatus=*(volatile unsigned long*)DMAC_INTSTATUS_V;
	endstatus=*(volatile unsigned long*)DMAC_INTTCSTATUS_V;
	errstatus=*(volatile unsigned long*)DMAC_INTERRORSTATUS_V;
	spi_debug1("dma int int 0x%x,end 0x%x,err0x%x\r\n",intstatus,endstatus,errstatus);
	
	if(intstatus&0x01) //channel 0 tx channel
	{
		if(endstatus&0x01)
		{
			
			*(volatile unsigned long*)DMAC_INTTCCLEAR_V=endstatus|0x01;
			*(volatile unsigned long*)DMAC_INTTCCLEAR_V=endstatus&(~0x01);
		}
		if(errstatus&0x01)
		{
			*(volatile unsigned long*)DMAC_INTERRORSTATUS_V=endstatus|0x01;
			*(volatile unsigned long*)DMAC_INTERRORSTATUS_V=endstatus&(~0x01);
		}
		if(DMA_ACTION==DMA_TX_ONLY)
		{
				rt_event_send(&txrxevent, 0X01);
				
		}
		 *(volatile unsigned long*)SSI_DMACR_V&=(~0x01);	//0x1 rxDMAenable 0x2 txDMAenable	

	}
	if(intstatus&0x02) //channel 1 rx channel
	{
		if(endstatus&0x02)
		{
			
			*(volatile unsigned long*)DMAC_INTTCCLEAR_V=endstatus|0x02;
			*(volatile unsigned long*)DMAC_INTTCCLEAR_V=endstatus&(~0x02);
		}
		if(errstatus&0x02)
		{
			*(volatile unsigned long*)DMAC_INTERRORSTATUS_V=endstatus|0x02;
			*(volatile unsigned long*)DMAC_INTERRORSTATUS_V=endstatus&(~0x02);
		}
		if(DMA_ACTION==DMA_TX_RX)
		{
				rt_event_send(&txrxevent, 0X01);
				 *(volatile unsigned long*)SSI_DMACR_V&=(~0x02);	//0x1 rxDMAenable 0x2 txDMAenable	
		}

	}
//	*(volatile unsigned long*)(SSI_SSIENR_V)= 0x00;  //disable SSI   
 //      *(volatile unsigned long*)(SSI_SER_V)= 0x00;  //disable SSI channel0  
	
	rcl=*(volatile unsigned long*)SSI_ICR_V;
	rcl=*(volatile unsigned long*)SSI_RXOICR_V;
	rcl=*(volatile unsigned long*)SSI_RXUICR_V;
	
//	*(volatile unsigned long*)(SSI_SSIENR_V)= 0x01;  //disable SSI   
 //       *(volatile unsigned long*)(SSI_SER_V)= 0x01;  //disable SSI channel0  
	DMA_ACTION=0;
}
extern void rt_hw_interrupt_install(rt_uint32_t vector, rt_isr_handler_t new_handler, rt_isr_handler_t *old_handler);
int gspi_register_irq(int * irqnum)
{

     disable_irq(INTSRC_EXINT4)	;
    *(volatile unsigned long*)(GPIO_PORTA_DIR_V) |= (0X1)<<4;
    *(volatile unsigned long*)(GPIO_PORTA_SEL_V )|= (0X1)<<4;
    *(volatile unsigned long*)(GPIO_PORTA_INCTL_V) |= (0X1)<<4; 
    *(volatile unsigned long*)(GPIO_PORTA_INTRCTL_V) |= (0X11)<<8;//low level enable irq
    *(volatile unsigned long*)(GPIO_PORTA_INTRCLR_V) |= (0X1)<<4; //add for 4020  GPA6
    *irqnum= INTSRC_EXINT4;
    rt_hw_interrupt_install(INTSRC_EXINT4, sbi_interrupt, RT_NULL);
    rt_hw_interrupt_umask(INTSRC_EXINT4);

		
    return 0;
}

void gspi_irq_clear(void)
{   
	*(volatile unsigned long*)(GPIO_PORTA_INTRCLR_V) |= (0X1)<<4; //add for 4020  GPA6
}
static int dma_init( void )
{	
   // *(volatile unsigned long*)(DMAC_ENBLDCHNS_V ) = (1<<0)+(1<<1);	//enable the channels
   if(DMA_ENABLE==1)
	{  
   		rt_memset(rxtxdummybuf,0x00,(2048+1024));
    	rt_hw_interrupt_install(INTSRC_SSI, spi_interrupt, RT_NULL);
    	rt_hw_interrupt_umask(INTSRC_SSI);
		enable_irq(INTSRC_SSI);
	}
   
    rt_hw_interrupt_install(INTSRC_DMAC, dma_interrupt, RT_NULL);
    rt_hw_interrupt_umask(INTSRC_DMAC);
    enable_irq(INTSRC_DMAC);
    spi_debug3("\nDMA Initialization done....\n");

    return 0;
}
static int gspihost_init_hw(void)
{
    *(volatile unsigned long*)(GPIO_PORTD_DIR_V)&=~0x04;
    *(volatile unsigned long*)(GPIO_PORTD_SEL_V)&=~0x1b;
    *(volatile unsigned long*)(GPIO_PORTD_SEL_V)|= 0x04;
    
    *(volatile unsigned long*)(SSI_SSIENR_V)= 0x00;  //disable SSI            
	
    *(volatile unsigned long*)(SSI_BAUDR_V) = 0x08; //set baudrate 


    *(volatile unsigned long*)(SSI_TXFLR_V) = 0x00;
    *(volatile unsigned long*)(SSI_RXFLR_V) = 0x00;
    
    *(volatile unsigned long*)(SSI_CONTROL0_V) = 0x0f; //?configure SSI channel0  
    *(volatile unsigned long*)(SSI_IMR_V) = 0x00;//0x1f;  //mask all irqs of ssi  
       
    *(volatile unsigned long*)(SSI_SER_V)= 0x01;  //enable SSI channel0   
    *(volatile unsigned long*)(SSI_SSIENR_V)= 0x01;  //enable SSI            



    return 0;
}

int gspihost_init(void) 
{
  int ret=RT_EOK;
  spi_debug1("gspihost_init\n");

  ret=rt_sem_init(&gspi_lock, "wifi_gspi", 1, RT_IPC_FLAG_FIFO);
  if(ret!=RT_EOK)
  ret=rt_event_init(&txrxevent, "spievent", RT_IPC_FLAG_FIFO);
  if(ret!=RT_EOK)
  return ret;
  gspihost_init_hw();
  if( DMA_ENABLE==1)
  dma_init();
  return 0;
}
