/** @file sys_vim.c 
*   @brief VIM Driver Inmplmentation File
*   @date 
*   @version 03.05.02
*
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */


#include "sys_vim.h"
#include "system.h"


/* Vim Ram Definition */
/** @struct vimRam
*   @brief Vim Ram Definition
*
*   This type is used to access the Vim Ram.
*/
/** @typedef vimRAM_t
*   @brief Vim Ram Type Definition
*
*   This type is used to access the Vim Ram.
*/
typedef volatile struct vimRam
{
    t_isrFuncPTR ISR[VIM_CHANNELS + 1U];
} vimRAM_t;

#define vimRAM ((vimRAM_t *)0xFFF82000U)

/** @fn void vimInit(void)
*   @brief Initializes VIM module
*
*   This function initializes VIM RAM and registers
*/

void vimInit(void)
{
	/* Set Fall-Back Address Parity Error Register */
    /*VIM_FBPARERR = (uint32)&vimParityErrorHandler;*/

    /* set IRQ/FIQ priorities */
    vimREG->FIRQPR0 =  SYS_FIQ
                    | (SYS_FIQ <<  1U)
                    | (SYS_IRQ <<  2U)
                    | (SYS_IRQ <<  3U)
                    | (SYS_IRQ <<  4U)
                    | (SYS_IRQ <<  5U)
                    | (SYS_IRQ <<  6U)
                    | (SYS_IRQ <<  7U)
                    | (SYS_IRQ <<  8U)
                    | (SYS_IRQ <<  9U)
                    | (SYS_IRQ << 10U)
                    | (SYS_IRQ << 11U)
                    | (SYS_IRQ << 12U)
                    | (SYS_IRQ << 13U)
                    | (SYS_IRQ << 14U)
                    | (SYS_IRQ << 15U)
                    | (SYS_IRQ << 16U)
                    | (SYS_IRQ << 17U)
                    | (SYS_IRQ << 18U)
                    | (SYS_IRQ << 19U)
                    | (SYS_IRQ << 20U)
                    | (SYS_IRQ << 21U)
                    | (SYS_IRQ << 22U)
                    | (SYS_IRQ << 23U)
                    | (SYS_IRQ << 24U)
                    | (SYS_IRQ << 25U)
                    | (SYS_IRQ << 26U)
                    | (SYS_IRQ << 27U)
                    | (SYS_IRQ << 28U)
                    | (SYS_IRQ << 29U)
                    | (SYS_IRQ << 30U)
                    | (SYS_IRQ << 31U);

    vimREG->FIRQPR1 =  SYS_IRQ
                    | (SYS_IRQ <<  1U)
                    | (SYS_IRQ <<  2U)
                    | (SYS_IRQ <<  3U)
                    | (SYS_IRQ <<  4U)
                    | (SYS_IRQ <<  5U)
                    | (SYS_IRQ <<  6U)
                    | (SYS_IRQ <<  7U)
                    | (SYS_IRQ <<  8U)
                    | (SYS_IRQ <<  9U)
                    | (SYS_IRQ << 10U)
                    | (SYS_IRQ << 11U)
                    | (SYS_IRQ << 12U)
                    | (SYS_IRQ << 13U)
                    | (SYS_IRQ << 14U)
                    | (SYS_IRQ << 15U)
                    | (SYS_IRQ << 16U)
                    | (SYS_IRQ << 17U)
                    | (SYS_IRQ << 18U)
                    | (SYS_IRQ << 19U)
                    | (SYS_IRQ << 20U)
                    | (SYS_IRQ << 21U)
                    | (SYS_IRQ << 22U)
                    | (SYS_IRQ << 23U)
                    | (SYS_IRQ << 24U)
                    | (SYS_IRQ << 25U)
                    | (SYS_IRQ << 26U)
                    | (SYS_IRQ << 27U)
                    | (SYS_IRQ << 28U)
                    | (SYS_IRQ << 29U)
                    | (SYS_IRQ << 30U)
                    | (SYS_IRQ << 31U);


    vimREG->FIRQPR2 =  SYS_IRQ
                    | (SYS_IRQ << 1U)
                    | (SYS_IRQ << 2U)
                    | (SYS_IRQ << 3U)
                    | (SYS_IRQ << 4U)
                    | (SYS_IRQ << 5U)
                    | (SYS_IRQ << 6U)
                    | (SYS_IRQ << 7U)
                    | (SYS_IRQ << 8U)
                    | (SYS_IRQ << 9U)
                    | (SYS_IRQ << 10U)
                    | (SYS_IRQ << 11U)
                    | (SYS_IRQ << 12U)
                    | (SYS_IRQ << 13U)
                    | (SYS_IRQ << 14U)
                    | (SYS_IRQ << 15U)
                    | (SYS_IRQ << 16U)
                    | (SYS_IRQ << 17U)
                    | (SYS_IRQ << 18U)
                    | (SYS_IRQ << 19U)
                    | (SYS_IRQ << 20U)
                    | (SYS_IRQ << 21U)
                    | (SYS_IRQ << 22U)
                    | (SYS_IRQ << 23U)
                    | (SYS_IRQ << 24U)
                    | (SYS_IRQ << 25U)
					| (SYS_IRQ << 26U)
                    | (SYS_IRQ << 27U)
                    | (SYS_IRQ << 28U)
                    | (SYS_IRQ << 29U)
                    | (SYS_IRQ << 30U)
                    | (SYS_IRQ << 31U);

    vimREG->FIRQPR3 =  SYS_IRQ
                    | (SYS_IRQ << 1U)
                    | (SYS_IRQ << 2U)
                    | (SYS_IRQ << 3U)
                    | (SYS_IRQ << 4U)
                    | (SYS_IRQ << 5U)
                    | (SYS_IRQ << 6U)
                    | (SYS_IRQ << 7U)
                    | (SYS_IRQ << 8U)
                    | (SYS_IRQ << 9U)
                    | (SYS_IRQ << 10U)
                    | (SYS_IRQ << 11U)
                    | (SYS_IRQ << 12U)
                    | (SYS_IRQ << 13U)
                    | (SYS_IRQ << 14U)
                    | (SYS_IRQ << 15U)
                    | (SYS_IRQ << 16U)
                    | (SYS_IRQ << 17U)
                    | (SYS_IRQ << 18U)
                    | (SYS_IRQ << 19U)
                    | (SYS_IRQ << 20U)
                    | (SYS_IRQ << 21U)
                    | (SYS_IRQ << 22U)
                    | (SYS_IRQ << 23U)
                    | (SYS_IRQ << 24U)
                    | (SYS_IRQ << 25U)
					| (SYS_IRQ << 26U)
                    | (SYS_IRQ << 27U)
                    | (SYS_IRQ << 28U)
                    | (SYS_IRQ << 29U)
                    | (SYS_IRQ << 30U)
                    | (SYS_IRQ << 31U);

					
    /* enable interrupts */
    vimREG->REQMASKSET0 = 1U
                        | (1U << 1U)
                        | (0U << 2U)
                        | (0U << 3U)
                        | (0U << 4U)
                        | (1U << 5U)
                        | (0U << 6U)
                        | (0U << 7U)
                        | (0U << 8U)
                        | (0U << 9U)
                        | (0U << 10U)
                        | (0U << 11U)
                        | (0U << 12U)
                        | (1U << 13U)
                        | (0U << 14U)
                        | (0U << 15U)
                        | (0U << 16U)
                        | (0U << 17U)
                        | (0U << 18U)
                        | (0U << 19U)
                        | (0U << 20U)
                        | (0U << 21U)
                        | (0U << 22U)
                        | (0U << 23U)
                        | (0U << 24U)
                        | (0U << 25U)
                        | (0U << 26U)
                        | (0U << 27U)
                        | (0U << 28U)
                        | (0U << 29U)
                        | (0U << 30U)
                        | (0U << 31U);

    vimREG->REQMASKSET1 = 0U
                        | (0U << 1U)
                        | (0U << 2U)
                        | (0U << 3U)
                        | (0U << 4U)
                        | (0U << 5U)
                        | (0U << 6U)
                        | (0U << 7U)
                        | (0U << 8U)
                        | (0U << 9U)
                        | (0U << 10U)
                        | (0U << 11U)
                        | (0U << 12U)
                        | (0U << 13U)
                        | (0U << 14U)
                        | (0U << 15U)
                        | (0U << 16U)
                        | (0U << 17U)
                        | (0U << 18U)
                        | (0U << 19U)
                        | (0U << 20U)
                        | (0U << 21U)
                        | (0U << 22U)
                        | (0U << 23U)
                        | (0U << 24U)
                        | (0U << 25U)
                        | (0U << 26U)
                        | (0U << 27U)
                        | (0U << 28U)
                        | (0U << 29U)
                        | (0U << 30U)
                        | (0U << 31U);

    vimREG->REQMASKSET2 = 0U
                        | (0U << 1U)
                        | (0U << 2U)
                        | (0U << 3U)
                        | (0U << 4U)
                        | (0U << 5U)
                        | (0U << 6U)
                        | (0U << 7U)
                        | (0U << 8U)
                        | (0U << 9U)
                        | (0U << 10U)
                        | (0U << 11U)
                        | (0U << 12U)
                        | (0U << 13U)
                        | (0U << 14U)
                        | (0U << 15U)
                        | (0U << 16U)
                        | (0U << 17U)
                        | (0U << 18U)
                        | (0U << 19U)
                        | (0U << 20U)
                        | (0U << 21U)
                        | (0U << 22U)
                        | (0U << 23U)
                        | (0U << 24U)
                        | (0U << 25U)
					    | (0U << 26U)
                        | (0U << 27U)
                        | (0U << 28U)
                        | (0U << 29U)
                        | (0U << 30U)
                        | (0U << 31U);
						
    vimREG->REQMASKSET3 =  0U
                        | (0U << 1U)
                        | (0U << 2U)
                        | (0U << 3U)
                        | (0U << 4U)
                        | (0U << 5U)
                        | (0U << 6U)
                        | (0U << 7U)
                        | (0U << 8U)
                        | (0U << 9U)
                        | (0U << 10U)
                        | (0U << 11U)
                        | (0U << 12U)
                        | (0U << 13U)
                        | (0U << 14U)
                        | (0U << 15U)
                        | (0U << 16U)
                        | (0U << 17U)
                        | (0U << 18U)
                        | (0U << 19U)
                        | (0U << 20U)
                        | (0U << 21U)
                        | (0U << 22U)
                        | (0U << 23U)
                        | (0U << 24U)
                        | (0U << 25U)
						| (0U << 26U)
                        | (0U << 27U)
                        | (0U << 28U)
                        | (0U << 29U)
                        | (0U << 30U)
                        | (0U << 31U);	
}

/** @fn void vimChannelMap(uint32 request, uint32 channel, t_isrFuncPTR handler)
*   @brief Map selected interrupt request to the selected channel
*
*	@param[in] request: Interrupt request number 2..95
*	@param[in] channel: VIM Channel number 2..95
*	@param[in] handler: Address of the interrupt handler
*
*   This function will map selected interrupt request to the selected channel.
*
*/
void vimChannelMap(uint32 request, uint32 channel, t_isrFuncPTR handler)
{
	uint32 i,j;
    i = channel >> 2U;              /* Find the register to configure */
    j = channel -(i<<2U);           /* Find the offset of the type    */
    j = 3U-j;                       /* reverse the byte order         */
    j = j<<3U;                      /* find the bit location          */

    /*Mapping the required interrupt request to the required channel*/
    vimREG->CHANCTRL[i] &= ~(0xFFU << j);
    vimREG->CHANCTRL[i] |= (request << j);

    /*Updating VIMRAM*/
    vimRAM->ISR[channel+1] = handler;
}

/** @fn void vimEnableInterrupt(uint32 channel, boolean inttype)
*   @brief Enable interrupt for the the selected channel
*
*	@param[in] channel: VIM Channel number 2..95
*	@param[in] handler: Interrupt type
*						- SYS_IRQ: Selected channel will be enabled as IRQ
*						- SYS_FIQ: Selected channel will be enabled as FIQ
*
*   This function will enable interrupt for the selected channel.
*
*/
void vimEnableInterrupt(uint32 channel, boolean inttype)
{
	if (channel >= 64)
	{
		if(inttype == SYS_IRQ)
		{
			vimREG->FIRQPR2 &= ~(1 << (channel-64));
		}
		else
		{
			vimREG->FIRQPR2 |= 1 << (channel-64);
		}
		vimREG->REQMASKSET2 = 1 << (channel-64);
	}
	else if (channel >= 32)
	{
		if(inttype == SYS_IRQ)
		{
			vimREG->FIRQPR1 &= ~(1 << (channel-32));
		}
		else
		{
			vimREG->FIRQPR1 |= 1 << (channel-32);
		}
		vimREG->REQMASKSET1 = 1 << (channel-32);
	}
	else if (channel >= 2)
	{
		if(inttype == SYS_IRQ)
		{
			vimREG->FIRQPR0 &= ~(1 << channel);
		}
		else
		{
			vimREG->FIRQPR0 |= 1 << channel;
		}
		vimREG->REQMASKSET0 = 1 << channel;
	}
	else
	{

	}
}

/** @fn void vimDisableInterrupt(uint32 channel)
*   @brief Disable interrupt for the the selected channel
*
*	@param[in] channel: VIM Channel number 2..95
*
*   This function will disable interrupt for the selected channel.
*
*/
void vimDisableInterrupt(uint32 channel)
{
	if (channel >= 64)
	{
		vimREG->REQMASKCLR2 = 1 << (channel-64);
	}
	else if (channel >=32)
	{
		vimREG->REQMASKCLR1 = 1 << (channel-32);
	}
	else if (channel >= 2)
	{
		vimREG->REQMASKCLR0 = 1 << channel;
	}
	else
	{

	}
}

/** @fn void vimGetConfigValue(vim_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration registers
*
*	@param[in] *config_reg: pointer to the struct to which the initial or current value of the configuration registers need to be stored
*	@param[in] type: 	whether initial or current value of the configuration registers need to be stored
*						- InitialValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*						- CurrentValue: initial value of the configuration registers will be stored in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') of the configuration registers to the struct pointed by config_reg
*
*/

void vimGetConfigValue(vim_config_reg_t *config_reg, config_value_type_t type)
{
	uint32 temp[24U] = VIM_CHANCTRL_CONFIGVALUE;
	uint32 i;
	
	if (type == InitialValue)
	{
		config_reg->CONFIG_FIRQPR0 = VIM_FIRQPR0_CONFIGVALUE;
		config_reg->CONFIG_FIRQPR1 = VIM_FIRQPR1_CONFIGVALUE;
		config_reg->CONFIG_FIRQPR2 = VIM_FIRQPR2_CONFIGVALUE;
		config_reg->CONFIG_FIRQPR3 = VIM_FIRQPR3_CONFIGVALUE;
		config_reg->CONFIG_REQMASKSET0 = VIM_REQMASKSET0_CONFIGVALUE;
		config_reg->CONFIG_REQMASKSET1 = VIM_REQMASKSET1_CONFIGVALUE;
		config_reg->CONFIG_REQMASKSET2 = VIM_REQMASKSET2_CONFIGVALUE;
		config_reg->CONFIG_REQMASKSET3 = VIM_REQMASKSET3_CONFIGVALUE;
		config_reg->CONFIG_WAKEMASKSET0 = VIM_WAKEMASKSET0_CONFIGVALUE;
		config_reg->CONFIG_WAKEMASKSET1 = VIM_WAKEMASKSET1_CONFIGVALUE;
		config_reg->CONFIG_WAKEMASKSET2 = VIM_WAKEMASKSET2_CONFIGVALUE;
		config_reg->CONFIG_WAKEMASKSET3 = VIM_WAKEMASKSET3_CONFIGVALUE;
		config_reg->CONFIG_CAPEVT = VIM_CAPEVT_CONFIGVALUE;

		for (i=0U; i<24U;i++)
		{
			config_reg->CONFIG_CHANCTRL[i] = temp[i];
		}
	}
	else
	{
		config_reg->CONFIG_FIRQPR0 = vimREG->FIRQPR0;
		config_reg->CONFIG_FIRQPR1 = vimREG->FIRQPR1;
		config_reg->CONFIG_FIRQPR2 = vimREG->FIRQPR2;
		config_reg->CONFIG_FIRQPR3 = vimREG->FIRQPR3;
		config_reg->CONFIG_REQMASKSET0 = vimREG->REQMASKSET0;
		config_reg->CONFIG_REQMASKSET1 = vimREG->REQMASKSET1;
		config_reg->CONFIG_REQMASKSET2 = vimREG->REQMASKSET2;
		config_reg->CONFIG_REQMASKSET3 = vimREG->REQMASKSET3;
		config_reg->CONFIG_WAKEMASKSET0 = vimREG->WAKEMASKSET0;
		config_reg->CONFIG_WAKEMASKSET1 = vimREG->WAKEMASKSET1;
		config_reg->CONFIG_WAKEMASKSET2 = vimREG->WAKEMASKSET2;
		config_reg->CONFIG_WAKEMASKSET3 = vimREG->WAKEMASKSET3;
		config_reg->CONFIG_CAPEVT = vimREG->CAPEVT;

		for (i=0U; i<24U; i++)
		{
				config_reg->CONFIG_CHANCTRL[i] = vimREG->CHANCTRL[i];
		}

		
	}
}


#if 0
#pragma CODE_STATE(vimParityErrorHandler, 32)
#pragma INTERRUPT(vimParityErrorHandler, IRQ)

void vimParityErrorHandler(void)
{
	/* Identify the corrupted address */
	uint32 error_addr = VIM_ADDERR;

	/* Identify the channel number */
	uint32 error_channel = ((error_addr & 0x1FF) >> 2) - 1;

	/* Correct the corrupted location */
	vimRAM->ISR[error_channel + 1] = s_vim_init[error_channel + 1];

	/* Clear Parity Error Flag */
	VIM_PARFLG = 1;

	/* Disable and enable the highest priority pending channel */
	sint32 channel;
	channel = vimREG->FIQINDEX - 1;
	if (vimREG->FIQINDEX != 0)
	{
		channel = vimREG->FIQINDEX - 1;
	}
	else 
	{
		channel = vimREG->IRQINDEX - 1;
	}
	if (channel >= 0)
	{
		if (channel < 32)
		{
			vimREG->REQMASKCLR0 = 1 << channel;
			vimREG->REQMASKSET0 = 1 << channel;
		}
		else if (channel < 64)
		{
			vimREG->REQMASKCLR1 = 1 << (channel-32);
			vimREG->REQMASKSET1 = 1 << (channel-32);
		}
		else
		{
			vimREG->REQMASKCLR2 = 1 << (channel-64);
			vimREG->REQMASKSET2 = 1 << (channel-64);
		}
	}
}
#endif
