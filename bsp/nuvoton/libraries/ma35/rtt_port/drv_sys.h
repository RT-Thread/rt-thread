#ifndef __DRV_SYS_H__
#define __DRV_SYS_H__

#include <rtthread.h>
#include "drv_common.h"
#include "NuMicro.h"

typedef enum
{
    USB0_ID_DEVICE,
    USB0_ID_HOST,
    USB0_ID_CNT
} E_SYS_USB0_ID;

struct nu_module
{
    char      *name;
    void      *m_pvBase;
    uint32_t   u32RstId;
    IRQn_Type  eIRQn;
} ;
typedef struct nu_module *nu_module_t;

typedef struct
{
    vu32     vu32RegAddr;
    char    *szRegName;
    vu32     vu32BitMask;
    char    *szBMName;
    vu32     vu32Value;
    char    *szVName;
} S_NU_REG;

#define SYS_GPA_MFPL       (SYS_BASE + 0x0080U)
#define SYS_GPA_MFPH       (SYS_BASE + 0x0084U)
#define SYS_GPB_MFPL       (SYS_BASE + 0x0088U)
#define SYS_GPB_MFPH       (SYS_BASE + 0x008CU)
#define SYS_GPC_MFPL       (SYS_BASE + 0x0090U)
#define SYS_GPC_MFPH       (SYS_BASE + 0x0094U)
#define SYS_GPD_MFPL       (SYS_BASE + 0x0098U)
#define SYS_GPD_MFPH       (SYS_BASE + 0x009CU)
#define SYS_GPE_MFPL       (SYS_BASE + 0x00A0U)
#define SYS_GPE_MFPH       (SYS_BASE + 0x00A4U)
#define SYS_GPF_MFPL       (SYS_BASE + 0x00A8U)
#define SYS_GPF_MFPH       (SYS_BASE + 0x00ACU)
#define SYS_GPG_MFPL       (SYS_BASE + 0x00B0U)
#define SYS_GPG_MFPH       (SYS_BASE + 0x00B4U)
#define SYS_GPH_MFPL       (SYS_BASE + 0x00B8U)
#define SYS_GPH_MFPH       (SYS_BASE + 0x00BCU)
#define SYS_GPI_MFPL       (SYS_BASE + 0x00C0U)
#define SYS_GPI_MFPH       (SYS_BASE + 0x00C4U)
#define SYS_GPJ_MFPL       (SYS_BASE + 0x00C8U)
#define SYS_GPJ_MFPH       (SYS_BASE + 0x00CCU)
#define SYS_GPK_MFPL       (SYS_BASE + 0x00D0U)
#define SYS_GPK_MFPH       (SYS_BASE + 0x00D4U)
#define SYS_GPL_MFPL       (SYS_BASE + 0x00D8U)
#define SYS_GPL_MFPH       (SYS_BASE + 0x00DCU)
#define SYS_GPM_MFPL       (SYS_BASE + 0x00E0U)
#define SYS_GPM_MFPH       (SYS_BASE + 0x00E4U)
#define SYS_GPN_MFPL       (SYS_BASE + 0x00E8U)
#define SYS_GPN_MFPH       (SYS_BASE + 0x00ECU)

#define SYS_USBPMISCR      (SYS_BASE + 0x0060U)
#define SYS_USBP0PCR       (SYS_BASE + 0x0064U)
#define SYS_USBP1PCR       (SYS_BASE + 0x0068U)

#define CLK_PWRCTL         (CLK_BASE + 0x0000U)
#define CLK_SYSCLK0        (CLK_BASE + 0x0004U)
#define CLK_SYSCLK1        (CLK_BASE + 0x0008U)
#define CLK_APBCLK0        (CLK_BASE + 0x000CU)
#define CLK_APBCLK1        (CLK_BASE + 0x0010U)
#define CLK_APBCLK2        (CLK_BASE + 0x0014U)
#define CLK_CLKSEL0        (CLK_BASE + 0x0018U)
#define CLK_CLKSEL1        (CLK_BASE + 0x001CU)
#define CLK_CLKSEL2        (CLK_BASE + 0x0020U)
#define CLK_CLKSEL3        (CLK_BASE + 0x0024U)
#define CLK_CLKSEL4        (CLK_BASE + 0x0028U)

#define CLK_CLKDIV0        (CLK_BASE + 0x002CU)
#define CLK_CLKDIV1        (CLK_BASE + 0x0030U)
#define CLK_CLKDIV2        (CLK_BASE + 0x0034U)
#define CLK_CLKDIV3        (CLK_BASE + 0x0038U)
#define CLK_CLKDIV4        (CLK_BASE + 0x003CU)
#define CLK_CLKOCTL        (CLK_BASE + 0x0040U)

#define NUREG_EXPORT(vu32RegAddr, vu32BitMask, vu32Value)  { vu32RegAddr, #vu32RegAddr, vu32BitMask, #vu32BitMask, vu32Value, #vu32Value }

void nu_clock_base_init(void);
void nu_sys_ip_reset(uint32_t u32ModuleIndex);
void nu_sys_ipclk_enable(uint32_t eIPClkIdx);
void nu_sys_ipclk_disable(uint32_t eIPClkIdx);
E_SYS_USB0_ID nu_sys_usb0_role(void);
void nu_sys_check_register(S_NU_REG *psNuReg);

#endif
