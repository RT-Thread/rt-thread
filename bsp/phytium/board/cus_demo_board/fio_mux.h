#ifndef  FIO_MUX_H
#define  FIO_MUX_H

#include "ftypes.h"
#include "fboard_port.h"
#ifdef __cplusplus
extern "C"
{
#endif

void FIOPadSetSpimMux(u32 spim_id);
void FIOPadSetGpioMux(u32 gpio_id, u32 pin_id);
void FIOPadSetCanMux(u32 can_id);
void FIOPadSetQspiMux(u32 qspi_id, u32 cs_id);
void FIOPadSetPwmMux(u32 pwm_id, u32 pwm_channel);
void FIOPadSetAdcMux(u32 adc_id, u32 adc_channel);
void FIOPadSetMioMux(u32 mio_id);
void FIOPadSetTachoMux(u32 pwm_in_id);
void FIOPadSetUartMux(u32 uart_id);
void FIOPadSetI2sMux(void);
void FIOPadSetSdMux(u32 sd_id);

_WEAK void FIOMuxInit(void);
_WEAK void FIOMuxDeInit(void);
#ifdef __cplusplus
}
#endif

#endif
