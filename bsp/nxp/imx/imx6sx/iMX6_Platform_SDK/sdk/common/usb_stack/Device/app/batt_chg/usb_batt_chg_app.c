/**HEADER**********************************************************************
*
* Copyright (c) Freescale Semiconductor
* All rights reserved 
*
*******************************************************************************
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
* THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************
*
* $FileName: usb_batt_chg_app.c$
* $Version : 1.0.0.0$
* $Date    : Apr-22-2011$
*END**************************************************************************/

#include "types.h"
#include "usb_devapi.h"
#include "derivative.h"   /* Include peripheral declarations */
/* Specific file header */
#include "usb_batt_chg.h"
/* Specific MAX3353 files header */
#if (defined __MK_xxx_H__)	
  #include "usb_otg_max3353_kinetis.h"
  #include "sci.h"
  #include "IIC_kinetis.h"
#elif (defined MCU_mcf51jf128)
  #include "usb_otg_max3353_cfv1_plus.h"
  #include "sci_cfv1_plus.h"
  #include "IIC_cfv1_plus.h"      
  #include "printf_cfv1_plus.h"
#endif
#include "hidef.h"

#include <stdio.h>

/* Private definitions *******************************************************/
#define T_UNIT_CON                        (1000)
#define T_CHECK_DM                        (3)

/* Interrupts enabled pins on the external VBUS Detection IC */
#define IRQ_H_ENABLED                     (FALSE)
#define IRQ_F_ENABLED                     (FALSE)
#define IRQ_D_ENABLED                     (TRUE)
#define IRQ_B_ENABLED                     (FALSE)
/* Interrupt type for external VBUS detect circuit */
#define IRQC_FALLING_EDGE                 (0xa)
#define IRQC_BOTH_EDGES                   (0xb)
#define USB0_USBTRC0_USBPU				  (1<<6)

#if defined (MCU_MK20D5)
	#define USE_MAX3353  				  (FALSE)
#endif

/* Private variables *********************************************************/
USB_BATT_CHG_INIT_STRUCT batt_chg_app_init;
//USB_BATT_CHG_STATUS* batt_chg_status_app_ptr;

/* Private functions prototyping *********************************************/
void TestApp_Init(void);
void TestApp_Task(void);
/* Application callback function */
void BatteryCharging_AppCallback(USB_BATT_CHG_EVENT event, const USB_BATT_CHG_STATUS* app_bat_chg_status_ptr);
void BatteryCharging_VbusDetPinsInit(void);
/* Function to enable/disable the battery management circuit */
void BatteryCharging_EnableDisableCircuit(boolean enable_ic);
/* Function to update the VBUS status */
boolean BatteryCharging_VbusStatusUpdate(void);
/* VBUS detection ISR */
#if (defined __MK_xxx_H__)
	void VbusDetect_ISR(void);
#elif (defined MCU_mcf51jf128)
	void interrupt VectorNumber_Virq VbusDetect_ISR(void);
#endif

/*FUNCTION*----------------------------------------------------------------
*
* Function Name  :  TestApp_Init
* Returned Value :  none
* Comments       :  Battery Charging test application init function 
*     
*
*END*--------------------------------------------------------------------*/
void TestApp_Init(void)
{
	uint_32 status = USB_OK;
  
  /* Uart initialization */
#ifdef MCU_MK70F12
	sci2_init();
#else
  #if (defined __MK_xxx_H__)
	sci_init();
  #elif (defined MCU_mcf51jf128)
	sci1_init();       
  #endif  
#endif
	
#if !HIGH_SPEED_DEVICE
	/* IIC module initialization; it is used to communicate with the MAX3353 */
	IIC_ModuleInit();
#endif // HIGH_SPEED_DEVICE
  
	/* USBDCD module clock enable */
	SIM_SCGC6 |= SIM_SCGC6_USBDCD_MASK;

#if (defined __MK_xxx_H__)
	/* USBDCD interrupt enable */  
	#ifdef MCU_MK20D5
		NVICICPR1 = (uint32_t)(1 << ((36)%32));
		NVICISER1 = (uint32_t)(1 << ((36)%32));
	#elif defined MCU_MK21D5
		NVICICPR1 = (uint32_t)(1 << ((54)%32));
		NVICISER1 = (uint32_t)(1 << ((54)%32));
	#else
	NVICICPR2 |= (uint32_t)(1 << ((74)%32));
	NVICISER2 |= (uint32_t)(1 << ((74)%32));
	#endif
	
#if (defined MCU_MK40N512VMD100) || (defined MCU_MK53N512CMD100) || (defined MCU_MK60N512VMD100) || (defined MCU_MK21D5)
    /* Ensure that the internal pull-up resistor is selected, otherwise the charge detection won't work */
	if(!(USB0_USBTRC0 & USB0_USBTRC0_USBPU))
	{
		USB0_USBTRC0 = USB0_USBTRC0_USBPU;
	}
#endif
#endif
  
	/* Ensure that the interrupts are enabled from the CPU register */
	EnableInterrupts;

	printf("\n============================================");
	printf("\n=  USB Battery Charging Application Demo.  =");
	printf("\n============================================\n");
#if (defined __MK_xxx_H__) && !defined(__IAR_SYSTEMS_ICC__) 
	fflush(stdout);
#endif
  
	/* Initialize the pins used to detect the VBUS via external IC */
	BatteryCharging_VbusDetPinsInit();
  
	/* Prepare the application init variable */
	/* External VBUS detect circuit initialization */
	batt_chg_app_init.ext_vbus_detect_circuit_use               = TRUE;
	batt_chg_app_init.ext_vbus_detect_enable_disable_func       = _otg_max3353_enable_disable;
	batt_chg_app_init.ext_vbus_detect_update_vbus_status_func   = BatteryCharging_VbusStatusUpdate; 
	/* External Battery Charging circuit initialization */
	batt_chg_app_init.ext_batt_chg_circuit_use                  = TRUE;
	batt_chg_app_init.ext_batt_chg_circuit_enable_disable_func  = BatteryCharging_EnableDisableCircuit; 
	/* Timing initialization */
	batt_chg_app_init.usb_batt_chg_timings_config.time_dcd_dbnc      = T_DCD_DBNC;
	batt_chg_app_init.usb_batt_chg_timings_config.time_vdpsrc_on     = T_VDPSRC_ON;
	batt_chg_app_init.usb_batt_chg_timings_config.time_vdpsrc_con    = T_VDPSRC_CON;
	batt_chg_app_init.usb_batt_chg_timings_config.time_seq_init      = T_UNIT_CON;
	batt_chg_app_init.usb_batt_chg_timings_config.time_check_d_minus = T_CHECK_DM;
	
	/* Initialize the USB Battery Charger module */
	status = _usb_batt_chg_init(&batt_chg_app_init);
	if(status == USB_OK) 
	{
		status = _usb_batt_chg_register_callback(BatteryCharging_AppCallback); 
	}
  
	if(status == USB_OK)
	{   
		printf("\nInitialization passed. Plug in the USB portable device to the USB charger port.\n");
#if (defined __MK_xxx_H__) && !defined(__IAR_SYSTEMS_ICC__)
		fflush(stdout);
#endif
	}
	else
	{
		printf("\nERROR!!! Initialization failed!!!\n");
#if (defined __MK_xxx_H__) && !defined(__IAR_SYSTEMS_ICC__)
		fflush(stdout);
#endif
		return;
	}  
}


/*FUNCTION*----------------------------------------------------------------
*
* Function Name  :  TestApp_Task
* Returned Value :  none
* Comments       :  Battery charging application task function
*     
*
*END*--------------------------------------------------------------------*/
void TestApp_Task(void)
{
  _usb_batt_chg_task();
}


/*FUNCTION*----------------------------------------------------------------
*
* Function Name  :  BatteryCharging_AppCallback
* Returned Value :  none
* Comments       :  Battery charging application callback function; informs 
*                   the application about the status of charging port type 
*                   detection
*
*END*--------------------------------------------------------------------*/
void BatteryCharging_AppCallback(USB_BATT_CHG_EVENT event, const USB_BATT_CHG_STATUS* app_bat_chg_status_ptr)
{
  /* Treats the battery charging detection error event */
  if(event & USB_BATT_CHG_EVENT_ERROR)
  {
    /* Information message about the error occurrence */
    printf("\nERROR: The charging port detection has failed!!!\n"); 
    #if (defined __MK_xxx_H__) && !defined(__IAR_SYSTEMS_ICC__)
      fflush(stdout);
    #endif
      
    /* check and inform the application about the error type */
    if(app_bat_chg_status_ptr->error_type == error_seq_timeout)
    {
      printf("\nERROR: The sequence timeout has occured!!!\n"); 
      #if (defined __MK_xxx_H__) && !defined(__IAR_SYSTEMS_ICC__) 
        fflush(stdout);
      #endif
    }
    else
    {
      if(app_bat_chg_status_ptr->error_type == error_unknown_port_type)
      {
        printf("\nERROR: Unknown port type!!!\n");
        #if (defined __MK_xxx_H__) && !defined(__IAR_SYSTEMS_ICC__)
          fflush(stdout);
        #endif
      }
    }
  }
  
  /* Treats the battery charging detection completion event */
  if(event & USB_BATT_CHG_EVENT_PHASE_COMPLETE)
  {
    /* Information message */
    printf("\nThe charging port detection has been successfully done.\n");
    #if (defined __MK_xxx_H__) && !defined(__IAR_SYSTEMS_ICC__)
      fflush(stdout);
    #endif
    
    if(app_bat_chg_status_ptr->dev_state == USB_BATT_CHG_STATE_COMPLETE)
    {
      /* Charging port type message */
      switch(app_bat_chg_status_ptr->charger_type)
      {
        case USB_BATT_CHG_PORT_TYPE_SDP:
                printf("\nThe Portable Device (PD) is attached to a Standard Downstream Port (SDP)."); 
                printf("\nThe maximum current allowed to be drawn is 500mA, after configuration step.\n");             
                break;
                
        case USB_BATT_CHG_PORT_TYPE_CDP:
                printf("\nThe Portable Device (PD) is attached to a Charging Downstream Port (CDP).");
                printf("\nThe maximum current allowed to be drawn is 1.5A.\n");              
                break;
                
        case USB_BATT_CHG_PORT_TYPE_DCP:
                printf("\nThe Portable Device (PD) is attached to a Dedicated Charging Port (DCP)."); 
                printf("\nThe maximum current allowed to be drawn is 1.8A.\n");              
                break;
      }
      #if (defined __MK_xxx_H__) && !defined(__IAR_SYSTEMS_ICC__)  
        fflush(stdout);
      #endif
    }
  }
  
  /* Treats the battery charging detection unplug event */
  if(event & USB_BATT_CHG_EVENT_UNPLUGGED)
  {
    /* Information message about the unplug event */
	printf("\nThe Portable Device (PD) has been unplugged.\n");
	#if (defined __MK_xxx_H__) && !defined(__IAR_SYSTEMS_ICC__)
	  fflush(stdout);
	#endif	  
  }
}


/*FUNCTION*----------------------------------------------------------------
*
* Function Name  :  BatteryCharging_EnableDisableCircuit
* Returned Value :  none
* Comments       :  Enable the Battery Charging IC  
*
*END*--------------------------------------------------------------------*/
void BatteryCharging_EnableDisableCircuit(boolean enable_ic)
{
  if(enable_ic == TRUE)
  {
    /* Enable the Battery Charging IC */    
    printf("\nThe Battery Charger IC is enabled.");
    #if (defined __MK_xxx_H__) && !defined(__IAR_SYSTEMS_ICC__) 
      fflush(stdout);
    #endif
  }
  else
  {
    /* Disable the Battery Charging IC */     
    printf("\nThe Battery Charger IC is disabled.");
    #if (defined __MK_xxx_H__) && !defined(__IAR_SYSTEMS_ICC__)
      fflush(stdout);
    #endif
  }
}


/*FUNCTION*----------------------------------------------------------------
*
* Function Name  :  BatteryCharging_ExtVbusDetPinsInit
* Returned Value :  none
* Comments       :  Initialize the GPIO pins used to detect the VBUS voltage
*                   via the external IC (MAX3353)
*
*END*--------------------------------------------------------------------*/
void BatteryCharging_VbusDetPinsInit(void)
{
	#if (defined MCU_MK20D5)
		NVICICER1 =(1 << (42%32));                     /* Clear any pending interrupts */
		NVICISER1 =(1 << (42%32));                     /* Enable interrupts PORTC */	
	
		/* PTC11 */
		/* Enable the corresponding pin as GPIO */
		PORTC_PCR11 = PORT_PCR_MUX(1);
		/* Set input on PTC11 */
		GPIOC_PDDR &= ~((uint_32)1 << 11);
		/* Pull up */
		PORTC_PCR11 |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
		/* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
		PORTC_PCR11 |= PORT_PCR_ISF_MASK;
		/* Configure the interrupt on both edges */
		PORTC_PCR11 |= PORT_PCR_IRQC(IRQC_BOTH_EDGES);
	#elif (defined MCU_MK20D7) || (defined MCU_MK40D7)
		NVICICPR2 |= (1<<23);                    /* Clear any pending interrupts */
		NVICISER2 |= (1<<23);                    /* Enable interrupts PORTA */
		
		/* Enable clock for the Port A */
		SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
		
		GPIOA_PDDR &= ~((uint_32)1 << 17);		/* Set input PTA 17 */	
	#elif(defined MCU_MK40N512VMD100) || (defined MCU_MK53N512CMD100)
		NVICICER2 =(1<<24);                     /* Clear any pending interrupts */
		NVICISER2 =(1<<24);                     /* Enable interrupts PORTB */
	
		/* Enable clock for the Port B */
		SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
		
		GPIOB_PDDR &= ~((uint_32)1 << 7);		/* set input PTB 7*/
	#elif defined MCU_MK60N512VMD100
		NVICICER2 = (1<<23);                    /* Clear any pending interrupts */
		NVICISER2 = (1<<23);                    /* Enable interrupts PORTA */
		
		/* Enable clock for the Port A */
		SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
		
		GPIOA_PDDR &= ~((uint_32)1 << 26);		/* Set input PTA 26 */ 
	#elif defined MCU_MK21D5
		NVICICER1 = (1<<27);                    /* Clear any pending interrupts */
		NVICISER1 = (1<<27);                    /* Enable interrupts PORTA */
	
		/* Enable clock for the Port A */
		SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
		GPIOA_PDDR &= ~((uint_32)1 << 16);
	#elif defined MCU_MK70F12
		NVICICER2=(1<<24);                     /* Clear any pending interrupts */
		NVICISER2=(1<<24);                     /* Enable interrupts PORTB*/
		
		/* Enable clock for the Port B */
		SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
		
		/* set IRQ_D pin */
		GPIOB_PDDR &= ~((uint_32)1 << 6);		/* set input PTB 6*/
	#elif defined MCU_mcf51jf128
	   /* Enable the PORTC clock */
	   SIM_SCGC6 |= SIM_SCGC6_PORTC_MASK;	
	#endif
 	
	#if(TRUE == IRQ_H_ENABLED)	  
		#if(defined MCU_MK20D7) || (defined MCU_MK40D7)
			/* PTE25 */
			/* Enable the corresponding pin as GPIO */
			PORTE_PCR25 = PORT_PCR_MUX(1);
			/* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			PORTE_PCR25 |= PORT_PCR_ISF_MASK;
			/* Configure the interrupt on falling edge */
			PORTE_PCR25 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE);
		#endif		  
		#if(defined MCU_MK40N512VMD100) || (defined MCU_MK53N512CMD100)
			/* PTB5 */
			/* Enable the corresponding pin as GPIO */
			PORTB_PCR5 = PORT_PCR_MUX(1);
			/* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			PORTB_PCR5 |= PORT_PCR_ISF_MASK;
			/* Configure the interrupt on falling edge */
			PORTB_PCR5 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE);
		#endif
		#if (defined MCU_MK60N512VMD100) || (defined MCU_MK70F12)
			/* PTA24 */
			/* Enable the corresponding pin as GPIO */
			PORTA_PCR24 = PORT_PCR_MUX(1);
			/* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			PORTA_PCR24 |= PORT_PCR_ISF_MASK;
			/* Configure the interrupt on falling edge */
			PORTA_PCR24 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE);
		#endif
		#if (defined MCU_MK21D5)
			/* PTE6 */
			/* Enable the corresponding pin as GPIO */
			PORTE_PCR6 = PORT_PCR_MUX(1);
			/* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			PORTE_PCR6 |= PORT_PCR_ISF_MASK;
			/* Configure the interrupt on falling edge */
			PORTE_PCR6 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE);
		#endif
		#if (defined MCU_mcf51jf128)
			/* Configure the PTB0 pin package as external interrupt (IRQ) function */
			/* Only the PTB0 is altered */
			MXC_PTBPF4 &= ~MXC_PTBPF4_B0(0x5);
			MXC_PTBPF4 |= MXC_PTBPF4_B0(0x5);
			
			/* Enable the clock to the IRQ module */
			SIM_SCGC4 |= SIM_SCGC4_IRQ_MASK;
			
			/* Enable the IRQ pin in falling edge mode */
			/* For falling edge only: IRQEDG = 0, IRQMOD = 0 */
			/* Assure that the IRQF flag is cleared before enabling the interrupt */
			IRQ_SC |= IRQ_SC_IRQACK_MASK;
			IRQ_SC = IRQ_SC_IRQPE_MASK | IRQ_SC_IRQIE_MASK;
		#endif	 
	#endif // IRQ_H_ENABLED

	#if(TRUE == IRQ_F_ENABLED)	 
		#if(defined MCU_MK20D7) || (defined MCU_MK40D7)
			/* PTE6 */
			/* Enable the corresponding pin as GPIO */
			PORTE_PCR6 = PORT_PCR_MUX(1);
			/* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			PORTE_PCR6 |= PORT_PCR_ISF_MASK;
			/* Configure the interrupt on falling edge */
			PORTE_PCR6 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE);
		#endif		  	  
		#if(defined MCU_MK40N512VMD100) || (defined MCU_MK53N512CMD100)
			/* PTB6 */
			/* Enable the corresponding pin as GPIO */   
			PORTB_PCR6 = PORT_PCR_MUX(1);
			/* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			PORTB_PCR6 |= PORT_PCR_ISF_MASK;  
			/* Configure the interrupt on falling edge */
			PORTB_PCR6 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE);  
		#endif
		#if (defined MCU_MK60N512VMD100) || (defined MCU_MK70F12)
			/* PTA25 */
			/* Enable the corresponding pin as GPIO */
			PORTA_PCR25 = PORT_PCR_MUX(1);
			/* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			PORTA_PCR25 |= PORT_PCR_ISF_MASK;
			/* Configure the interrupt on falling edge */
			PORTA_PCR25 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE);  
		#endif	  
		#if (defined MCU_MK21D5)
			/* PTB8 */
			/* Enable the corresponding pin as GPIO */
			PORTB_PCR8 = PORT_PCR_MUX(1);
			/* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			PORTB_PCR8 |= PORT_PCR_ISF_MASK;
			/* Configure the interrupt on falling edge */
			PORTB_PCR8 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE);
		#endif	
	#endif // IRQ_F_ENABLED

	#if(TRUE == IRQ_D_ENABLED)	  
		#if(defined MCU_MK40N512VMD100) || (defined MCU_MK53N512CMD100)
			  /* PTB7 */
			  /* Enable the corresponding pin as GPIO */
			  PORTB_PCR7 = PORT_PCR_MUX(1);
			  /* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			  PORTB_PCR7 |= PORT_PCR_ISF_MASK;   
			  /* Configure the interrupt on falling edge */
			  PORTB_PCR7 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE);     
		#elif (defined MCU_MK20D7) || (defined MCU_MK40D7)	  
			  /* PTA17 */
			  /* Enable the corresponding pin as GPIO */
			  PORTA_PCR17 = PORT_PCR_MUX(1);
			  /* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			  PORTA_PCR17 |= PORT_PCR_ISF_MASK;
			  /* Configure the interrupt on falling edge */
			  PORTA_PCR17 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE); 	  	  
		#elif (defined MCU_MK60N512VMD100)
			  /* PTA26 */
			  /* Enable the corresponding pin as GPIO */
			  PORTA_PCR26 = PORT_PCR_MUX(1);
			  /* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			  PORTA_PCR26 |= PORT_PCR_ISF_MASK;
			  /* Configure the interrupt on falling edge */
			  PORTA_PCR26 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE);
		#elif (defined MCU_MK21D5)
			  /* PTA16 */
			  /* Enable the corresponding pin as GPIO */
			  PORTA_PCR16 = PORT_PCR_MUX(1);
			  /* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			  PORTA_PCR16 |= PORT_PCR_ISF_MASK;
			  /* Configure the interrupt on falling edge */
			  PORTA_PCR16 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE);
		#elif defined MCU_MK70F12
			  /* PTB6 */
			  /* Enable the corresponding pin as GPIO */
			  PORTB_PCR6 = PORT_PCR_MUX(1);
			  /* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			  PORTB_PCR6 |= PORT_PCR_ISF_MASK;
			  /* Configure the interrupt on falling edge */
			  PORTB_PCR6 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE);
		#endif	 
	#endif // IRQ_D_ENABLED

	#if(TRUE == IRQ_B_ENABLED)	  
		#if(defined MCU_MK20D7) || (defined MCU_MK40D7)
			/* PTC6 */
			/* Enable the corresponding pin as GPIO */
			PORTC_PCR6 = PORT_PCR_MUX(1);
			/* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			PORTC_PCR6 |= PORT_PCR_ISF_MASK;
			/* Configure the interrupt on falling edge */
			PORTC_PCR6 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE);
		#endif		  	  
		#if(defined MCU_MK40N512VMD100) || (defined MCU_MK53N512CMD100)
		  /* PTB8 */
		  /* Enable the corresponding pin as GPIO */  
		  PORTB_PCR8 = PORT_PCR_MUX(1); 
		  /* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
		  PORTB_PCR8 |= PORT_PCR_ISF_MASK;
		  /* Configure the interrupt on falling edge */
		  PORTB_PCR8 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE); 
		#endif
		#if (defined MCU_MK60N512VMD100) || (defined MCU_MK70F12)
			/* PTA27 */
			/* Enable the corresponding pin as GPIO */
			PORTA_PCR27 = PORT_PCR_MUX(1);
			/* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			PORTA_PCR27 |= PORT_PCR_ISF_MASK;
			/* Configure the interrupt on falling edge */
			PORTA_PCR27 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE);
		#endif
		#if (defined MCU_MK21D5)
			/* PTC6 */
			/* Enable the corresponding pin as GPIO */
			PORTC_PCR6= PORT_PCR_MUX(1);
			/* Assure that the Interrupt Status Flag (ISF) is cleared before enabling interrupt */
			PORTC_PCR6 |= PORT_PCR_ISF_MASK;
			/* Configure the interrupt on falling edge */
			PORTC_PCR6 |= PORT_PCR_IRQC(IRQC_FALLING_EDGE);
		#endif
		#if (defined MCU_mcf51jf128)
			/* Configure the PTC4 as external interrupt function */
			/* Only the PTC4 is altered */
			MXC_PTCPF2 &= ~MXC_PTCPF2_C4(1);
			MXC_PTCPF2 |= MXC_PTCPF2_C4(1);
			
			/* Enable the PTC4 as interrupt input pin */		
			PCTLC_IC   = PCTL_IC_PTIE_MASK;
			/* Be sure that the flag is cleared before interrupt enabling */
			PCTLC_IF  |= PCTL_PTC4_MASK;
			/* The edge detection is falling only */
			PCTLC_IES &= ~PCTL_PTC4_MASK;
			/* Enable the individual pin PTC4 */		
			PCTLC_IPE |= PCTL_PTC4_MASK;
		#endif	  
	#endif //IRQ_B_ENABLED
}


/*FUNCTION*----------------------------------------------------------------
*
* Function Name  :  BatteryCharging_VbusStatusUpdate
* Returned Value :  none
* Comments       :  Function to update VBUS status 
*
*END*--------------------------------------------------------------------*/
boolean BatteryCharging_VbusStatusUpdate(void)
{
	uint_8    otg_status_reg;
	boolean   vbus_valid_status;
  
  	#if defined (MCU_MK20D5)
    	#if (USE_MAX3353 == TRUE)
			/* Update the status from the MAX3353 circuit */  
			otg_status_reg = _otg_max3353_get_status();  
	  
			/* Update the VBUS status */
			vbus_valid_status = (otg_status_reg & OTG_STAT_VBUS_VALID) ? TRUE : FALSE;    
    	#else
			/* Get the VBUS status from the PTC11 input state */
			otg_status_reg = (uint8_t)(GPIOC_PDIR >> 11);
			vbus_valid_status = otg_status_reg & 0x01; 
    	#endif
	#else
		/* Update the status from the MAX3353 circuit */
		otg_status_reg = _otg_max3353_get_status();  
	  
		/* Update the VBUS status */
		vbus_valid_status = (otg_status_reg & OTG_STAT_VBUS_VALID) ? TRUE : FALSE;
  	#endif
  
	return vbus_valid_status;
}


/*FUNCTION*----------------------------------------------------------------
*
* Function Name  :  VbusDetect_ISR
* Returned Value :  none
* Comments       :  VBUS Detection ISR function
*
* Note: The VbusDetect_ISR() function should be also assigned in the vector 
*       table from the 'vectors.c' file (Vector: 104, IRQ: 88)
*END*--------------------------------------------------------------------*/
#if (defined __MK_xxx_H__)
	void VbusDetect_ISR(void)
#elif (defined MCU_mcf51jf128)
	void interrupt VectorNumber_Virq VbusDetect_ISR(void)
#endif
{
	static volatile uint8_t new_state, old_state;
  
	#ifndef MCU_MK20D5  
		/* Acknowledge the interrupt */
	  	#if(TRUE == IRQ_H_ENABLED)  
			#if(defined MCU_MK20D7) || (defined MCU_MK40D7)
				/* If PTE25 is used */
	  	  	  	if(PORTE_PCR25 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTE_PCR25 |= PORT_PCR_ISF_MASK;
	  	  	  	} 	  
			#endif	
			#if(defined MCU_MK40N512VMD100) || (defined MCU_MK53N512CMD100)
	  	  	  	/* If PTB5 is used */
	  	  	  	if(PORTB_PCR5 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTB_PCR5 |= PORT_PCR_ISF_MASK;
	  	  	  	} 
			#endif
			#if (defined MCU_MK60N512VMD100) || (defined MCU_MK70F12)
	  	  	  	/* If PTA24 is used */
	  	  	  	if(PORTA_PCR24 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTA_PCR24 |= PORT_PCR_ISF_MASK;
	  	  	  	}
			#endif
			#if (defined MCU_MK21D5)
	  	  	  	/* If PTE6 is used */
	  	  	  	if(PORTE_PCR6 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTE_PCR6 |= PORT_PCR_ISF_MASK;
	  	  	  	}
			#endif
			#if (defined MCU_mcf51jf128)
	  	  	  	/* Acknowledge the interrupt; thus the interrupt flag is automatically cleared */
	  	  	  	IRQ_SC |= IRQ_SC_IRQACK_MASK;
			#endif  
		#endif // IRQ_H_ENABLED
  
		#if(TRUE == IRQ_F_ENABLED)      
			#if(defined MCU_MK20D7) || (defined MCU_MK40D7)
	  	  	  	/* If PTE6 is used */
	  	  	  	if(PORTE_PCR6 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTE_PCR6 |= PORT_PCR_ISF_MASK;
	  	  	  	} 	  
			#endif		  
			#if(defined MCU_MK40N512VMD100) || (defined MCU_MK53N512CMD100)
	  	  	  	/* If PTB6 is used */
	  	  	  	if(PORTB_PCR6 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTB_PCR6 |= PORT_PCR_ISF_MASK;
	  	  	  	}
			#endif
			#if (defined MCU_MK60N512VMD100) || (defined MCU_MK70F12)
	  	  	  	/* If PTA25 is used */
	  	  	  	if(PORTA_PCR25 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTA_PCR25 |= PORT_PCR_ISF_MASK;
	  	  	  	}
			#endif    
			#if (defined MCU_MK21D5)
	  	  	  	/* If PTB8 is used */
	  	  	  	if(PORTB_PCR8 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTB_PCR8 |= PORT_PCR_ISF_MASK;
	  	  	  	}
			#endif
		#endif // IRQ_F_ENABLED
  
		#if(TRUE == IRQ_D_ENABLED)  
			#if(defined MCU_MK40N512VMD100) || (defined MCU_MK53N512CMD100)
	  	  	  	/* If PTB7 is used */
	  	  	  	if(PORTB_PCR7 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTB_PCR7 |= PORT_PCR_ISF_MASK;
	  	  	  	}  
			#elif (defined MCU_MK20D7) || (defined MCU_MK40D7)
	  	  	  	/* If PTA17 is used */
	  	  	  	if(PORTA_PCR17 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTA_PCR17 |= PORT_PCR_ISF_MASK;
	  	  	  	}	  
			#elif (defined MCU_MK60N512VMD100)
	  	  	  	/* If PTA26 is used */
	  	  	  	if(PORTA_PCR26 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTA_PCR26 |= PORT_PCR_ISF_MASK;  		  	  	  	  		
	  	  	  	}
			#elif (defined MCU_MK21D5)
	  	  	  	/* If PTA16 is used */
	  	  	  	if(PORTA_PCR16 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTA_PCR16 |= PORT_PCR_ISF_MASK;
	  	  	  	}
			#elif defined MCU_MK70F12
	  	  	  	/* If PTB6 is used */
	  	  	  	if(PORTB_PCR6 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTB_PCR6 |= PORT_PCR_ISF_MASK;
	  	  	  	}
			#endif  
		#endif // IRQ_D_ENABLED
  
		#if(TRUE == IRQ_B_ENABLED)   
			#if(defined MCU_MK20D7) || (defined MCU_MK40D7)
	  	  	  	/* If PTC6 is used */
	  	  	  	if(PORTC_PCR6 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTC_PCR6 |= PORT_PCR_ISF_MASK;
	  	  	  	} 	  
			#endif
			#if(defined MCU_MK40N512VMD100) || (defined MCU_MK53N512CMD100)
	  	  	  	/* If PTB8 is used */
	  	  	  	if(PORTB_PCR8 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTB_PCR8 |= PORT_PCR_ISF_MASK;
	  	  	  	} 
			#endif
			#ifdef MCU_MK60N512VMD100
	  	  	  	/* If PTA27 is used */
	  	  	  	if(PORTA_PCR27 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTA_PCR27 |= PORT_PCR_ISF_MASK;
	  	  	  	}
			#endif
			#ifdef MCU_MK21D5
	  	  	  	/* If PTC6 is used */
	  	  	  	if(PORTC_PCR6 & PORT_PCR_ISF_MASK)
	  	  	  	{
	  	  	  		PORTC_PCR6 |= PORT_PCR_ISF_MASK;
	  	  	  	}
			#endif
			#ifdef MCU_mcf51jf128
	  	  	  	/* If PTC4 is used clear the interrupt flag */
	  	  	  	if(PCTLC_IF & PCTL_PTC4_MASK)
	  	  	  	{
	  	  	  		PCTLC_IF  |= PCTL_PTC4_MASK;		  
	  	  	  	}	  
			#endif 
		#endif // IRQ_B_ENABLED
   
	  	/* Enable the pending interrupt if and only if the VBUS status 
     	is changed since the last value */
	  	new_state = _otg_max3353_get_status() & OTG_STAT_VBUS_VALID;
	  	if(new_state != old_state) 
	  	{
	  		/* Update the old status */
	  		old_state = new_state;

	  		/* Enable the pending vbus detect external interrupt */
	  		_usb_batt_chg_ext_isr(); 
	  	}  

	  	/* Read the latch to clear any pending interrupts */
	  	(void)_otg_max3353_get_interrupts();	    
	#else
	  	/* Acknowledge the interrupt */
	  	/* If PTC11 is used */
	  	if(PORTC_PCR11 & PORT_PCR_ISF_MASK)
	  	{
	  		PORTC_PCR11 |= PORT_PCR_ISF_MASK;
	  	}   
	
	  	/* Enable the pending interrupt if and only if the VBUS status 
		is changed since the last value */		
		#if (USE_MAX3353 == TRUE)
			new_state = _otg_max3353_get_status() & OTG_STAT_VBUS_VALID;
		#else
			new_state = (uint8_t)((GPIOC_PDIR >> 11) & 0x01);
		#endif		
		if(new_state != old_state) 
		{
			/* Update the old status */
			old_state = new_state;

			/* Enable the pending vbus detect external interrupt */
			_usb_batt_chg_ext_isr();
		}	
	#endif
}

