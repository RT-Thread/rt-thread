#include "hal.h"
#include "uart/uart.h"
#include "osc/osc.h"
#include "os_except.h"

/*
 *********************************************************************************************************
 *                                      Register Exception Handlers
 *
 * Description : This function is called to register general exception handler.
 *               The total number of general exception is 16.
 *
 * Arguments   : ipc
 *
 * Notes       :
 *********************************************************************************************************
 */
inline void register_exception_handler(int genneral_except_num, void (*handler)(unsigned int ipc))
{
	if (genneral_except_num >= 16)
	{
		puts("Non-exist general exception number.\n");
		while (1);
	}

        General_Exception_Handler_Table[genneral_except_num] = handler;
}

/*
 *********************************************************************************************************
 *                                      Exception Dispatcher
 *
 * Description : This function is called from exception handler to dispatch different
 *               exception handler according to register itype.
 *
 * Arguments   : ipc
 *
 * Notes       :
 *********************************************************************************************************
 */
void OS_CPU_EXCEPTION_Dispatcher(unsigned int ipc)
{
    /* Interrupt is still disabled at this point */
    /* get all needed system registers' values before re-enable interrupt */
    unsigned int itype = __nds32__mfsr (NDS32_SR_ITYPE);
    unsigned int exception_num;
    void (*pHandler)(unsigned int ipc);

    exception_num = itype & 0xf;

    pHandler = General_Exception_Handler_Table[exception_num];

    pHandler(ipc);
}
