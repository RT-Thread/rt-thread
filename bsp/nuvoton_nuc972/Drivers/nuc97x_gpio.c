/*
 * File      : nuc97x_gpio.c
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "nuc97x_conf.h"


static GPIO_CFG gpioCfg = {0};
static INT32 maskTbl[] = {GPIOA_MASK, GPIOB_MASK, GPIOC_MASK, GPIOD_MASK, GPIOE_MASK, GPIOF_MASK, GPIOG_MASK, GPIOH_MASK, GPIOI_MASK, GPIOJ_MASK};

void GPIO_IRQHandler(int vector,void *param)
{
    UINT32 reg;
    INT32 i,mask;
    reg = inpw(REG_AIC_ISRH);
    mask = 0x02000000; /* INT56 */
    reg = inpw(REG_GPIO_ISR);
	for (i = 0; i < MAX_PORT; i++)
		if (gpioCfg.IRQCallback[i] != NULL && (reg & (1 << i)))
		{
			gpioCfg.IRQCallback[i](inpw(REG_GPIOA_ISR+i*0x40), gpioCfg.IRQUserData[i]);
		}
    outpw(REG_AIC_SCCRH, mask);   /* Clear interrupt */
}

/**
 * @brief       External interrupt 0 handler
 * @return      None
 * @details     This function is used to external interrupt 0 handler.
 */
void GPIO_EINT_IRQHandler(int vector,void *param)
{
    UINT32 reg;
    INT32 mask;
    reg = inpw(REG_AIC_ISR);
    mask = 0x10;
    if((vector < EINT0_IRQn) || (vector > EINT7_IRQn))
    	return;

	if (gpioCfg.EINTIRQCallback[vector - EINT0_IRQn] != NULL)
	{
		gpioCfg.EINTIRQCallback[vector - EINT0_IRQn](reg, gpioCfg.EINTIRQUserData[vector - EINT0_IRQn]);
	}
    outpw(REG_AIC_SCCR, mask);   /* Clear interrupt */
}

/**
 * @brief       Open GPIO Port
 *
 * @param[in]   port       GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 * @param[in]   direction  Operation mode. It could be \ref DIR_INPUT or \ref DIR_OUTPUT
 * @param[in]   pull       Operation mode. \ref PULL_UP, \ref NO_PULL_UP
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     This function is used to open gpio port and set gpio port.
 */
INT32 GPIO_Open(GPIO_PORT port, GPIO_DIR direction, GPIO_PULL pull)
{
    UINT32 mask;
    INT32 portIndex;
    INT32 offset;

    outpw(REG_CLK_PCLKEN0,inpw(REG_CLK_PCLKEN0) | (1<<3)); //Enable GPIO engin clock.
    offset = (INT32)port;
    portIndex = port / 0x40;
    mask = maskTbl[portIndex];

    if(gpioCfg.bitBusyFlag[portIndex] != 0) {
        return GPIO_ERR_PORT_BUSY;
    }

    /* Set all bits in the port to busy */
    gpioCfg.bitBusyFlag[portIndex] = mask;

    /* Set port direction */
    if(direction == DIR_OUTPUT) {
        outpw(REG_GPIOA_DIR + offset , mask);
    } else {
        outpw(REG_GPIOA_DIR + offset , 0);
    }

    if(pull == PULL_UP) {
        outpw(REG_GPIOA_PUEN + offset , mask);
    } else {
        outpw(REG_GPIOA_PUEN + offset , 0);
    }

    return SUCCESSFUL;
}

/**
 * @brief       Close GPIO Port
 *
 * @param[in]   port       GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     This function is used to close GPIO port.The GPIO port is restore to default value.
 */
INT32 GPIO_Close(GPIO_PORT port)
{
    INT32 offset;
    INT32 portIndex;

    offset = (INT32)port;
    portIndex = (port / 0x40);

    /* Clean the busy flag */
    gpioCfg.bitBusyFlag[portIndex] = 0;

    /* Reset to input */
    outpw(REG_GPIOA_DIR + offset, 0);

    /* Reset to pull-up */
    outpw(REG_GPIOA_PUEN + offset, 0);

    return SUCCESSFUL;
}

/**
 * @brief       Set GPIO Port
 *
 * @param[in]   port       GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 * @param[in]   bitMap     GPIO port. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     This function is used to set GPIO port output data.
 */
INT32 GPIO_Set(GPIO_PORT port, UINT32 bitMap)
{
    INT32 offset;
    INT32 reg;

    offset = (INT32)port;

    reg = inpw(REG_GPIOA_DATAOUT + offset);
    reg = reg | bitMap;
    outpw(REG_GPIOA_DATAOUT + offset, reg);

    return SUCCESSFUL;
}

/**
* @brief       Clear GPIO port OUT Data
*
* @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
* @param[in]   bitMap      GPIO port data. It could be 0x00 ~ 0xFF.
*
* @retval      <0          Fail
* @retval      0           Success
*
* @details     Clear GPIO port output data to 0.
*/
INT32 GPIO_Clr(GPIO_PORT port, UINT32 bitMap)
{
    INT32 offset;
    INT32 reg;

    offset = (INT32)port;

    reg = inpw(REG_GPIOA_DATAOUT + offset);
    reg = reg & (~bitMap);
    outpw(REG_GPIOA_DATAOUT + offset, reg);

    return SUCCESSFUL;
}

/**
* @brief       Read GPIO port in data
*
* @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
*
* @retval      It could be 0 to 0xFF. If port is  \ref GPIOA ,  \ref BIT0 is PA0 input data,
*               \ref BIT1 is PA1 input data, ...  \ref BIT15 is PA15 input data.
*
* @details     Read the input data from GPIO port.
*/
UINT32 GPIO_ReadPort(GPIO_PORT port)
{
    UINT32 reg;
    INT32 offset;

    offset = (INT32)port;

    reg = inpw(REG_GPIOA_DATAIN + offset);

    return reg;
}

/**
* @brief       Set GPIO port direction
*
* @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
* @param[in]   direction   GPIO port direction. It could be \ref DIR_INPUT, \ref DIR_OUTPUT.
* @retval      <0              Fail
* @retval      0               Success
*
* @details     Set the direction into specified GPIO port.
*/
INT32 GPIO_SetPortDir(GPIO_PORT port, GPIO_DIR direction)
{
    INT32 offset;
    INT32 mask;
    INT32 portIndex;

    offset = (INT32)port;
    portIndex = (port / 0x40);
    mask = maskTbl[portIndex];

    if(direction == DIR_OUTPUT) {
        outpw(REG_GPIOA_DIR + offset, mask);
    } else {
        outpw(REG_GPIOA_DIR + offset, 0x0);
    }

    return SUCCESSFUL;
}

/**
 * @brief       Open GPIO bit
 *
 * @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 * @param[in]   bit         GPIO pin. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
 * @param[in]   direction   GPIO direction. It could be \ref DIR_INPUT or \ref DIR_OUTPUT
 * @param[in]   pull        GPIO pull-up. It could be \ref NO_PULL_UP or \ref PULL_UP
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     This function is used to open gpio pin.
 */
INT32 GPIO_OpenBit(GPIO_PORT port, UINT32 bit, GPIO_DIR direction, GPIO_PULL pull)
{
    UINT32 reg;
    UINT32 mask;
    INT32 portIndex;
    INT32 offset;

    offset = (INT32)port;
    portIndex = (port / 0x040);
    mask = (UINT32)bit;

    if ((gpioCfg.bitBusyFlag[portIndex] & mask) != 0)
    {
        return GPIO_ERR_BIT_BUSY;
    }

    gpioCfg.bitBusyFlag[portIndex] = gpioCfg.bitBusyFlag[portIndex] | mask;

    reg = inpw(REG_GPIOA_DIR + offset);
    reg = reg & (~mask);

    if (direction == DIR_OUTPUT)
    {
        reg = reg | mask;
    }

    outpw(REG_GPIOA_DIR + offset, reg);

    reg = inpw(REG_GPIOA_PUEN + offset);
    reg = reg & (~mask);

    if(pull == PULL_UP) {
        reg = reg | mask;
    }

    outpw(REG_GPIOA_PUEN + offset, reg);

    return SUCCESSFUL;
}

/**
* @brief       Set GPIO pin OUT Data
*
* @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
* @param[in]   bit         GPIO pin. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
*
* @retval      <0              Fail
* @retval      0               Success
*
* @details     Set the Data into specified GPIO pin.
*/
INT32 GPIO_CloseBit(GPIO_PORT port, UINT32 bit)
{
    UINT32 reg;
    UINT32 mask;
    INT32 portIndex;
    INT32 offset;

    offset = (INT32)port;
    portIndex = (port / 0x40);
    mask = (UINT32)bit;

    gpioCfg.bitBusyFlag[portIndex] = gpioCfg.bitBusyFlag[portIndex] & (~mask);

    reg = inpw(REG_GPIOA_DIR + offset);
    reg = reg & (~mask);
    outpw(REG_GPIOA_DIR + offset, reg);

    reg = inpw(REG_GPIOA_PUEN + offset);
    reg = reg & (~mask);
    outpw(REG_GPIOA_PUEN + offset, reg);

    return SUCCESSFUL;
}


/**
 * @brief       Set GPIO pin OUT Data
 *
 * @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 * @param[in]   bit          GPIO pin. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     Set the Data into specified GPIO pin.
 */
INT32 GPIO_SetBit(GPIO_PORT port, UINT32 bit)
{
    UINT32 bitMap;
    INT32 offset;
    INT32 reg;

    offset = (INT32)port;
    bitMap = (UINT32)bit;

    reg = inpw(REG_GPIOA_DATAOUT + offset);
    reg = reg | bitMap;
    outpw(REG_GPIOA_DATAOUT + offset, reg);

    return SUCCESSFUL;
}

/**
* @brief       Clear GPIO port Interrupt Flag
*
* @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
* @param[in]   bitMap      GPIO port data. It could be 0x00 ~ 0xFF.
*
* @retval      <0              Fail
* @retval      0               Success
*
* @details     Clear the interrupt status of specified GPIO port.
*/
INT32 GPIO_ClrISR(GPIO_PORT port, UINT32 bitMap)
{
    INT32 offset;

    offset = (INT32)port;

    outpw(REG_GPIOA_ISR + offset, bitMap);

    return SUCCESSFUL;
}

/**
 * @brief       Clear GPIO Pin Interrupt Flag
 *
 * @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 * @param[in]   bit         GPIO pin. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     Clear the interrupt status of specified GPIO pin.
 */
INT32 GPIO_ClrISRBit(GPIO_PORT port, UINT32 bit)
{
    UINT32 bitMap;
    INT32 offset;

    offset = (INT32)port;
    bitMap = (UINT32)bit;

    outpw(REG_GPIOA_ISR + offset, bitMap);

    return SUCCESSFUL;
}

/**
* @brief       Clear GPIO pin OUT Data
*
* @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
* @param[in]   bit         GPIO pin. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
*
* @retval      <0              Fail
* @retval      0               Success
*
* @details     Set the Data into specified GPIO pin.
*/
INT32 GPIO_ClrBit(GPIO_PORT port, UINT32 bit)
{
    UINT32 bitMap;
    INT32 offset;
    INT32 reg;

    offset = (INT32)port;
    bitMap = (UINT32)bit;

    reg = inpw(REG_GPIOA_DATAOUT + offset);
    reg = reg & (~bitMap);
    outpw(REG_GPIOA_DATAOUT + offset, reg);

    return SUCCESSFUL;
}

/**
* @brief       Read GPIO pin In Data
*
* @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
* @param[in]   bit         GPIO pin. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
*
* @retval      1/0         GPIO pin input data.
*
* @details     Read the In Data from GPIO pin.
*/
INT32 GPIO_ReadBit(GPIO_PORT port, UINT32 bit)
{
    UINT32 reg;
    UINT32 bitMap;
    INT32 offset;

    offset = (INT32)port;
    bitMap = (UINT32)bit;

    reg = inpw(REG_GPIOA_DATAIN + offset);

    return ((reg & bitMap)?1:0);
}

/**
* @brief       Set GPIO pin direction
*
* @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
* @param[in]   bit         GPIO pin. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
* @param[in]   direction   GPIO direction. It could be \ref DIR_INPUT, \ref DIR_OUTPUT.
*
* @retval      <0              Fail
* @retval      0               Success
*
* @details     Set the GPIO direction into specified GPIO pin.
*/
INT32 GPIO_SetBitDir(GPIO_PORT port, UINT32 bit, GPIO_DIR direction)
{
    UINT32 reg;
    UINT32 bitMap;
    INT32 offset;

    offset = (INT32)port;
    bitMap = (UINT32)bit;

    reg = inpw(REG_GPIOA_DIR + offset);
    reg = reg & (~bitMap);

    if(direction == DIR_OUTPUT) {
        reg = reg | bitMap;
    }

    outpw(REG_GPIOA_DIR + offset, reg);

    return SUCCESSFUL;
}

/**
* @brief       Check GPIO pin is used
*
* @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
* @param[in]   bit         GPIO pin. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
* @retval      None
*
* @details     It is function is used to check GPIO pin is used.
*/
BOOL GPIO_BitIsUsed(GPIO_PORT port, UINT32 bit)
{
    UINT32 mask;
    INT32 portIndex;

    portIndex = (port / 0x40);
    mask = (UINT32)bit;

    return ((gpioCfg.bitBusyFlag[portIndex] & mask)?TRUE:FALSE);
}

/**
 * @brief       Enable GPIO port interrupt
 *
 * @param[in]   port            GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 * @param[in]   callback        The callback function.It could be " INT32 GpioCallback(UINT32 status, UINT32 userData); "
 * @param[in]   userData        This paramater is used by callback functions.
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     This function is used to enable specified GPIO port interrupt.
 */
INT32 GPIO_EnableInt(GPIO_PORT port, GPIO_CALLBACK callback, UINT32 userData)
{
    INT32 portIndex;
    portIndex = (INT32)port/0x40;
	if (callback != NULL)
	{
		gpioCfg.IRQCallback[portIndex] = (GPIO_CALLBACK) callback;
		gpioCfg.IRQUserData[portIndex] = userData;
	}

	rt_hw_interrupt_install(GPIO_IRQn,GPIO_IRQHandler,RT_NULL,"gpioIsr");
    rt_hw_interrupt_umask(GPIO_IRQn);

    return SUCCESSFUL;
}

/**
 * @brief       Disable GPIO port interrupt
 *
 * @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     This function is used to disable specified GPIO port interrupt.
 */
INT32 GPIO_DisableInt(GPIO_PORT port)
{
    INT32 i,portIndex;
    portIndex = (INT32)port/0x40;

    gpioCfg.IRQCallback[portIndex] = NULL;
    gpioCfg.IRQUserData[portIndex] = 0;

    for(i=0; i<MAX_PORT; i++)
        if(gpioCfg.IRQCallback[i]!=0)
            return SUCCESSFUL;
    rt_hw_interrupt_mask(GPIO_IRQn);
    return SUCCESSFUL;
}

/**
 * @brief       Enable external I/O interrupt
 *
 * @param[in]   nIrq            External interrupt. It could be \ref NIRQ0, \ref NIRQ1, ... or \ref NIRQ7
 * @param[in]   callback        The callback function.It could be " INT32 GpioCallback(UINT32 status, UINT32 userData); "
 * @param[in]   userData        This paramater is used by callback functions.
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     This function is used to enable specified external I/O interrupt.
 */
INT32 GPIO_EnableEINT(GPIO_NIRQ nIrq, GPIO_CALLBACK callback, UINT32 userData)
{
	if (callback != NULL)
	{
		gpioCfg.EINTIRQCallback[nIrq] = (GPIO_CALLBACK) callback;
		gpioCfg.EINTIRQUserData[nIrq] = userData;
	}

	switch(nIrq)
    {
    case 0:
    	rt_hw_interrupt_install(EINT0_IRQn,GPIO_EINT_IRQHandler,RT_NULL,"ENIT0");
    	rt_hw_interrupt_umask(EINT0_IRQn);
        break;

    case 1:
    	rt_hw_interrupt_install(EINT1_IRQn,GPIO_EINT_IRQHandler,RT_NULL,"ENIT0");
    	rt_hw_interrupt_umask(EINT1_IRQn);
        break;

    case 2:
    	rt_hw_interrupt_install(EINT2_IRQn,GPIO_EINT_IRQHandler,RT_NULL,"ENIT0");
    	rt_hw_interrupt_umask(EINT2_IRQn);
        break;

    case 3:
    	rt_hw_interrupt_install(EINT3_IRQn,GPIO_EINT_IRQHandler,RT_NULL,"ENIT0");
    	rt_hw_interrupt_umask(EINT3_IRQn);
        break;

    case 4:
    	rt_hw_interrupt_install(EINT4_IRQn,GPIO_EINT_IRQHandler,RT_NULL,"ENIT0");
    	rt_hw_interrupt_umask(EINT4_IRQn);
        break;

    case 5:
    	rt_hw_interrupt_install(EINT5_IRQn,GPIO_EINT_IRQHandler,RT_NULL,"ENIT0");
    	rt_hw_interrupt_umask(EINT5_IRQn);
        break;

    case 6:
    	rt_hw_interrupt_install(EINT6_IRQn,GPIO_EINT_IRQHandler,RT_NULL,"ENIT0");
    	rt_hw_interrupt_umask(EINT6_IRQn);
        break;

    case 7:
    	rt_hw_interrupt_install(EINT7_IRQn,GPIO_EINT_IRQHandler,RT_NULL,"ENIT0");
    	rt_hw_interrupt_umask(EINT7_IRQn);
        break;
    };
    return SUCCESSFUL;
}

/**
 * @brief       Enable GPIO trigger type.
 *
 * @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 * @param[in]   bitMap      GPIO port. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
 * @param[in]   triggerType The triggerType of specified GPIO pin. It could be \n
 *                          \ref RISING, \ref FALLING, \ref BOTH_EDGE, \ref HIGH, \ref LOW.
 *
 * @retval      <0          Fail
 * @retval      0           Success
 *
 * @details     This function is used to enable trigger type.
 */
INT32 GPIO_EnableTriggerType(GPIO_PORT port, UINT32 bitMap, GPIO_TRIGGER_TYPE triggerType)
{
    UINT32 reg;
    INT32 offset;

    offset = (INT32)port;

    switch(triggerType) {
    case LOW:
        reg = inpw(REG_GPIOA_IMD+offset);
        outpw(REG_GPIOA_IMD+offset,reg | bitMap);

        reg = inpw(REG_GPIOA_IREN+offset);
        outpw(REG_GPIOA_IREN+offset,reg & ~bitMap);

        reg = inpw(REG_GPIOA_IFEN+offset);
        outpw(REG_GPIOA_IFEN+offset,reg  | bitMap);
        break;
    case HIGH:
        reg = inpw(REG_GPIOA_IMD+offset);
        outpw(REG_GPIOA_IMD+offset,reg | bitMap);

        reg = inpw(REG_GPIOA_IREN+offset);
        outpw(REG_GPIOA_IREN+offset,reg | bitMap);

        reg = inpw(REG_GPIOA_IFEN+offset);
        outpw(REG_GPIOA_IFEN+offset,reg & ~bitMap);
        break;
    case FALLING:
        reg = inpw(REG_GPIOA_IMD+offset);
        outpw(REG_GPIOA_IMD+offset,reg & ~bitMap);

        reg = inpw(REG_GPIOA_IREN+offset);
        outpw(REG_GPIOA_IREN+offset,reg & ~bitMap);

        reg = inpw(REG_GPIOA_IFEN+offset);
        outpw(REG_GPIOA_IFEN+offset,reg  | bitMap);
        break;
    case RISING:
        reg = inpw(REG_GPIOA_IMD+offset);
        outpw(REG_GPIOA_IMD+offset,reg & ~bitMap);

        reg = inpw(REG_GPIOA_IREN+offset);
        outpw(REG_GPIOA_IREN+offset,reg | bitMap);

        reg = inpw(REG_GPIOA_IFEN+offset);
        outpw(REG_GPIOA_IFEN+offset,reg & ~bitMap);
        break;
    case BOTH_EDGE:
        reg = inpw(REG_GPIOA_IMD+offset);
        outpw(REG_GPIOA_IMD+offset,reg & ~bitMap);

        reg = inpw(REG_GPIOA_IREN+offset);
        outpw(REG_GPIOA_IREN+offset,reg | bitMap);

        reg = inpw(REG_GPIOA_IFEN+offset);
        outpw(REG_GPIOA_IFEN+offset,reg | bitMap);
        break;
    }
    return SUCCESSFUL;
}

/**
 * @brief       Disable GPIO trigger type.
 *
 * @param[in]   port        GPIO port. It could be \ref GPIOA, \ref GPIOB, ... or \ref GPIOJ
 * @param[in]   bitMap      GPIO port. It could be \ref BIT0 \ref BIT1, ... or \ref BIT31
 *
 * @retval      <0          Fail
 * @retval      0           Success
 *
 * @details     This function is used to disable trigger type.
 */
INT32 GPIO_DisableTriggerType(GPIO_PORT port, UINT32 bitMap)
{
    UINT32 reg;
    INT32 offset;

    offset = (INT32)port;

    reg = inpw(REG_GPIOA_IMD+offset);
    outpw(REG_GPIOA_IMD +offset,reg & ~bitMap);

    reg = inpw(REG_GPIOA_IREN+offset);
    outpw(REG_GPIOA_IREN+offset,reg & ~bitMap);

    reg = inpw(REG_GPIOA_IFEN+offset);
    outpw(REG_GPIOA_IFEN+offset,reg & ~bitMap);

    return SUCCESSFUL;
}

/**
 * @brief       Disable external I/O interrupt
 *
 * @param[in]   nIrq            External I/O interrupt. It could be \ref NIRQ1, \ref NIRQ2, ... or \ref NIRQ7
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     This function is used to disable external I/O interrupt.
 */
INT32 GPIO_DisableEINT(GPIO_NIRQ nIrq)
{
	rt_hw_interrupt_mask(EINT0_IRQn + nIrq);

    gpioCfg.IRQCallback[nIrq] = NULL;
    gpioCfg.IRQUserData[nIrq] = 0;

    return SUCCESSFUL;
}

/**
 * @brief       Enable GPIO De-bounce Function
 *
 * @param[in]   debounceClkSel        The de-bounce sampling cycle selection. It could be 0~0xF.  \n
 *                                     0 = Sample interrupt input once per 1 clocks. \n
 *                                     1 = Sample interrupt input once per 2 clocks. \n
 *                                     2 = Sample interrupt input once per 4 clocks. \n
 *                                     3 = Sample interrupt input once per 8 clocks. \n
 *                                     4 = Sample interrupt input once per 16 clocks. \n
 *                                     5 = Sample interrupt input once per 32 clocks. \n
 *                                     6 = Sample interrupt input once per 64 clocks. \n
 *                                     7 = Sample interrupt input once per 128 clocks. \n
 *                                     8 = Sample interrupt input once per 256 clocks. \n
 *                                     9 = Sample interrupt input once per 2*256 clocks. \n
 *                                    10 = Sample interrupt input once per 4*256 clocks. \n
 *                                    11 = Sample interrupt input once per 8*256 clocks. \n
 *                                    12 = Sample interrupt input once per 16*256 clocks. \n
 *                                    13 = Sample interrupt input once per 32*256 clocks. \n
 *                                    14 = Sample interrupt input once per 64*256 clocks. \n
 *                                    15 = Sample interrupt input once per 128*256 clocks
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     Enable the interrupt de-bounce function of specified GPIO.
 */
INT32 GPIO_EnableDebounce(INT32 debounceClkSel)
{
    UINT32 reg;

    reg = inpw(REG_GPIO_DBNCECON);

    /* Setting the debounce timing */
    reg = ((reg & ~0xf) | debounceClkSel);

    /* Enable the debounce function */
    reg = reg | 0x20;
    outpw(REG_GPIO_DBNCECON, reg);

    return SUCCESSFUL;
}

/**
 * @brief       Disable GPIO De-bounce Function.
 *
 * @retval      <0              Fail
 * @retval      0               Success
 *
 * @details     Disable the interrupt de-bounce function of specified GPIO.
 */
INT32 GPIO_DisableDebounce(void)
{
    UINT32 reg;

    reg = inpw(REG_GPIO_DBNCECON);

    /* Setting the debounce timing */
    reg = ((reg & ~0xf));

    /* Enable the debounce function */
    reg = reg | 0x20;
    outpw(REG_GPIO_DBNCECON, reg);

    return SUCCESSFUL;
}


#ifdef RT_USING_PIN
#include <rtdevice.h>

#define LED1_PORT   GPIOB
#define LED1_PIN    GPIO_Pin_3

#define LED2_PORT   GPIOF
#define LED2_PIN    GPIO_Pin_10

int rt_hw_led_init(void)
{
    GPIO_CloseBit(LED1_PORT,LED1_PIN);
    GPIO_OpenBit(LED1_PORT,LED1_PIN,DIR_OUTPUT,NO_PULL_UP);
    GPIO_CloseBit(LED2_PORT,LED2_PIN);
    GPIO_OpenBit(LED2_PORT,LED2_PIN,DIR_OUTPUT,NO_PULL_UP);
}
//INIT_BOARD_EXPORT(rt_hw_led_init);


void rt_hw_led_set(rt_uint8_t value)
{
    if(value & 0x01)
        GPIO_SetBit(LED1_PORT,LED1_PIN);
    else
        GPIO_ClrBit(LED1_PORT,LED1_PIN);

    if(value & 0x02)
        GPIO_SetBit(LED2_PORT,LED2_PIN);
    else
        GPIO_ClrBit(LED2_PORT,LED2_PIN);
}

#endif
