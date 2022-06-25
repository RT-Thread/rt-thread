#include "GigaDevice/ioGD32VF103.h"
#include "intrinsics.h"
#include "csr.h"
#include "stdlib.h"
#include "stdint.h"

#pragma language=extended


extern __weak void   eclic_msip_handler(void);
extern __weak void   eclic_mtip_handler(void);
extern __weak void   eclic_bwei_handler(void);
extern __weak void   eclic_pmovi_handler(void);
extern __weak void   WWDGT_IRQHandler(void);
extern __weak void   LVD_IRQHandler(void);
extern __weak void   TAMPER_IRQHandler(void);
extern __weak void   RTC_IRQHandler(void);
extern __weak void   FMC_IRQHandler(void);
extern __weak void   RCU_IRQHandler(void);
extern __weak void   EXTI0_IRQHandler(void);
extern __weak void   EXTI1_IRQHandler(void);
extern __weak void   EXTI2_IRQHandler(void);
extern __weak void   EXTI3_IRQHandler(void);
extern __weak void   EXTI4_IRQHandler(void);
extern __weak void   DMA0_Channel0_IRQHandler(void);
extern __weak void   DMA0_Channel1_IRQHandler(void);
extern __weak void   DMA0_Channel2_IRQHandler(void);
extern __weak void   DMA0_Channel3_IRQHandler(void);
extern __weak void   DMA0_Channel4_IRQHandler(void);
extern __weak void   DMA0_Channel5_IRQHandler(void);
extern __weak void   DMA0_Channel6_IRQHandler(void);
extern __weak void   ADC0_1_IRQHandler(void);
extern __weak void   CAN0_TX_IRQHandler(void);
extern __weak void   CAN0_RX0_IRQHandler(void);
extern __weak void   CAN0_RX1_IRQHandler(void);
extern __weak void   CAN0_EWMC_IRQHandler(void);
extern __weak void   EXTI5_9_IRQHandler(void);
extern __weak void   TIMER0_BRK_IRQHandler(void);
extern __weak void   TIMER0_UP_IRQHandler(void);
extern __weak void   TIMER0_TRG_CMT_IRQHandler(void);
extern __weak void   TIMER0_Channel_IRQHandler(void);
extern __weak void   TIMER1_IRQHandler(void);
extern __weak void   TIMER2_IRQHandler(void);
extern __weak void   TIMER3_IRQHandler(void);
extern __weak void   I2C0_EV_IRQHandler(void);
extern __weak void   I2C0_ER_IRQHandler(void);
extern __weak void   I2C1_EV_IRQHandler(void);
extern __weak void   I2C1_ER_IRQHandler(void);
extern __weak void   SPI0_IRQHandler(void);
extern __weak void   SPI1_IRQHandler(void);
extern __weak void   USART0_IRQHandler(void);
extern __weak void   USART1_IRQHandler(void);
extern __weak void   USART2_IRQHandler(void);
extern __weak void   EXTI10_15_IRQHandler(void);
extern __weak void   RTC_Alarm_IRQHandler(void);
extern __weak void   USBFS_WKUP_IRQHandler(void);
extern __weak void   EXMC_IRQHandler(void);
extern __weak void   TIMER4_IRQHandler(void);
extern __weak void   SPI2_IRQHandler(void);
extern __weak void   UART3_IRQHandler(void);
extern __weak void   UART4_IRQHandler(void);
extern __weak void   TIMER5_IRQHandler(void);
extern __weak void   TIMER6_IRQHandler(void);
extern __weak void   DMA1_Channel0_IRQHandler(void);
extern __weak void   DMA1_Channel1_IRQHandler(void);
extern __weak void   DMA1_Channel2_IRQHandler(void);
extern __weak void   DMA1_Channel3_IRQHandler(void);
extern __weak void   DMA1_Channel4_IRQHandler(void);
extern __weak void   CAN1_TX_IRQHandler(void);
extern __weak void   CAN1_RX0_IRQHandler(void);
extern __weak void   CAN1_RX1_IRQHandler(void);
extern __weak void   CAN1_EWMC_IRQHandler(void);
extern __weak void   USBFS_IRQHandler(void);

typedef void(*__fp)(void);
const __fp gd_vector_base[96] =
{
    0,
    0,
    0,
    eclic_msip_handler,
    0,
    0,
    0,
    eclic_mtip_handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    eclic_bwei_handler,
    eclic_pmovi_handler,
    WWDGT_IRQHandler,
    LVD_IRQHandler,
    TAMPER_IRQHandler,
    RTC_IRQHandler,
    FMC_IRQHandler,
    RCU_IRQHandler,
    EXTI0_IRQHandler,
    EXTI1_IRQHandler,
    EXTI2_IRQHandler,
    EXTI3_IRQHandler,
    EXTI4_IRQHandler,
    DMA0_Channel0_IRQHandler,
    DMA0_Channel1_IRQHandler,
    DMA0_Channel2_IRQHandler,
    DMA0_Channel3_IRQHandler,
    DMA0_Channel4_IRQHandler,
    DMA0_Channel5_IRQHandler,
    DMA0_Channel6_IRQHandler,
    ADC0_1_IRQHandler,
    CAN0_TX_IRQHandler,
    CAN0_RX0_IRQHandler,
    CAN0_RX1_IRQHandler,
    CAN0_EWMC_IRQHandler,
    EXTI5_9_IRQHandler,
    TIMER0_BRK_IRQHandler,
    TIMER0_UP_IRQHandler,
    TIMER0_TRG_CMT_IRQHandler,
    TIMER0_Channel_IRQHandler,
    TIMER1_IRQHandler,
    TIMER2_IRQHandler,
    TIMER3_IRQHandler,
    I2C0_EV_IRQHandler,
    I2C0_ER_IRQHandler,
    I2C1_EV_IRQHandler,
    I2C1_ER_IRQHandler,
    SPI0_IRQHandler,
    SPI1_IRQHandler,
    USART0_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    EXTI10_15_IRQHandler,
    RTC_Alarm_IRQHandler,
    USBFS_WKUP_IRQHandler,
    0,
    0,
    0,
    0,
    0,
    EXMC_IRQHandler,
    0,
    TIMER4_IRQHandler,
    SPI2_IRQHandler,
    UART3_IRQHandler,
    UART4_IRQHandler,
    TIMER5_IRQHandler,
    TIMER6_IRQHandler,
    DMA1_Channel0_IRQHandler,
    DMA1_Channel1_IRQHandler,
    DMA1_Channel2_IRQHandler,
    DMA1_Channel3_IRQHandler,
    DMA1_Channel4_IRQHandler,
    0,
    0,
    CAN1_TX_IRQHandler,
    CAN1_RX0_IRQHandler,
    CAN1_RX1_IRQHandler,
    CAN1_EWMC_IRQHandler,
    USBFS_IRQHandler

};

extern unsigned int __minterrupt_clic_base;
extern __interrupt __machine void __minterrupt_single(void);

__interrupt __machine void __default_minterrupt_handler(void);

__interrupt __machine void __default_minterrupt_handler(void)
{
  abort();
}

extern uintptr_t handle_trap(uintptr_t mcause, uintptr_t sp);

uintptr_t handle_trap(uintptr_t mcause, uintptr_t sp)
{
  __fp fp;
  mcause &= 0xFFF;
  fp = gd_vector_base[mcause];
  if (fp)
    fp();
  return 0;
}

__interrupt void trap_entry()
{
  uintptr_t mcause = __read_csr(_CSR_MCAUSE);
  handle_trap(mcause, 0);
}

__interrupt void irq_entry()
{
  uintptr_t mcause = __read_csr(_CSR_MCAUSE);
  uintptr_t mepc = __read_csr(_CSR_MEPC);
  uintptr_t msubm = __read_csr(0x7C4);
  __enable_interrupt();
  handle_trap(mcause, 0);
  //asm("csrrw ra,0x7ED, ra");
  __disable_interrupt();
  __write_csr(_CSR_MCAUSE, mcause);
  __write_csr(_CSR_MEPC, mepc);
  __write_csr(0x7C4, msubm);
}

int __low_level_init()
{
  __disable_interrupt();
  /* Set the the NMI base to share with mtvec by setting CSR_MMISC_CTL */
  /* li t0, 0x200           */
  /* csrs CSR_MMISC_CTL, t0 */
  __set_bits_csr(/*CSR_MMISC_CTL*/ 0x7D0, 0x200);

  /* Initialize the mtvt */
  /* la t0, vector_base      */
  /* csrw CSR_MTVT, t0       */
  __write_csr(_CSR_MTVT, ((unsigned int)&gd_vector_base));
  /* Initialize the mtvt2 and enable it */
  /* la t0, irq_entry
     csrw CSR_MTVT2, t0
     csrs CSR_MTVT2, 0x1
  */
  __write_csr(/*_CSR_MTVT2*/ 0x7EC, 0x1 | ((unsigned int)&irq_entry));

  /* Initialize the CSR MTVEC for the Trap ane NMI base addr*/
  /* la t0, trap_entry
     csrw CSR_MTVEC, t0
  */
  __write_csr(_CSR_MTVEC, 0x03 | ((unsigned int)&trap_entry));

  /* Enable mycycle_minstret */
  __clear_bits_csr(/*CSR_MCOUNTINHIBIT*/ 0x320, 0x5);
  return 1;
}
