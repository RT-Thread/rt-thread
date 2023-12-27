#ifndef __SYSTEM_SWM320_H__
#define __SYSTEM_SWM320_H__

#ifdef __cplusplus
 extern "C" {
#endif


extern uint32_t SystemCoreClock;        // System Clock Frequency (Core Clock)
extern uint32_t CyclesPerUs;            // Cycles per micro second


extern void SystemInit(void);

extern void SystemCoreClockUpdate (void);



extern void switchCLK_20MHz(void);
extern void switchCLK_40MHz(void);
extern void switchCLK_32KHz(void);
extern void switchCLK_XTAL(void);
extern void switchCLK_PLL(void);

extern void PLLInit(void);


#ifdef __cplusplus
}
#endif

#endif //__SYSTEM_SWM320_H__
