#ifndef __SYSTEM_BL808_H__
#define __SYSTEM_BL808_H__

#define RV_EXCEPTION_NUM (16)
typedef uintptr_t (*exception_handler)(uintptr_t cause, uintptr_t val, uintptr_t *regs);
typedef void (*pFunc)(void);

extern void System_Interrupt_Init(void);
extern void CPU_Interrupt_Enable(uint32_t irq_num);
extern void CPU_Interrupt_Disable(uint32_t irq_num);
extern void CPU_Interrupt_Pending_Clear(uint32_t irq_num);
void Interrupt_Handler_Register(IRQn_Type irq, pFunc interruptFun);
extern void System_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);

exception_handler exception_handler_install(uintptr_t vec, exception_handler handler);

int32_t drv_get_cpu_id(void);
int32_t drv_get_cpu_freq(int32_t idx);

#endif
