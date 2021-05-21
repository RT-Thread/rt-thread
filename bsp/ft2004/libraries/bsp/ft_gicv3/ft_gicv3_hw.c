/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-18 18:08:20
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_types.h"
#include "ft_assert.h"
#include "ft_io.h"
#include "ft_status.h"
#include "ft_printf.h"
#include "ft_cpu.h"
#include "ft_aarch32_asm.h"
#include "ft_parameters.h"
#include "asmArm.h"
#include "ft_gicv3.h"
#include "ft_gicv3_hw.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

#define GIC_IPI_PRIORITY 0
#define GIC_PRIORITY_LEVEL_STEP 0x10
#define GIC_SPI_PRIORITY_DEFAULT 0x10101010
#define ARM_GICV3_MSI_START 125
#define ARM_GICV3_MSI_CNT 34

#define ARM_GICV3_PHYS_REG(offset) (armGicBase + offset)
#define ARM_GICV3_VIRT_REG(offset) (armGicBase + offset)

#define ARM_GICV3_MSI_CAP_ADDR_OFF 0x40
#define ARM_GICV3_MSI_ANSWER_OFF 0x48
#define ARM_GICV3_MSI_CAP_PHYS_ADDR ARM_GICV3_PHYS_REG(ARM_GICV3_MSI_CAP_ADDR_OFF)
#define ARM_GICV3_MSI_ANSWER_ADDR ARM_GICV3_VIRT_REG(ARM_GICV3_MSI_ANSWER_OFF)

/********************************Variable Definitions************************************************/
extern FGicv3_Config_t g_FGicv3_Config_tTable[FT_GICV3_INSTANCES_NUM];
static u32 g_FGicVersion = 3;

/************************** Function Prototypes ******************************/

/* assembly functions */

/**
 * @name: FGiv3_ClrMsiIntr 
 * @msg:  清除msi 中断，暂时没有启用
 * @param {Ft_Gicv3_Config} *Config
 * @param {u32} irq
 * @return {*}
 */
void FGiv3_ClrMsiIntr(FGicv3_Config_t *Config, u32 irq)
{
    // *(volatile u32 *)(ARM_GICV3_MSI_ANSWER_ADDR) = irq;
    return;
}

static __inline__ void __dsb(void)
{
    __asm__ volatile(
        "dsb"
        : /* no output */
        : /* no input */
        : "memory");
}

/**
 * @name: Gicv3_Init
 * @msg: 
 * @param {*}
 * @return {*}
 */
// static void
// Gicv3_Init(FGicv3_Config_t *Config, s32 CpuID)
// {
//     u32 value = 0;
//     u32 count = 1000;
//     s32 regGicLineNum = 0;

//     u32 aGicCfg = 0;
//     s32 i = 0;

//     Ft_out32((UINTPTR)(Config->Gicv3DistributorAddress + GICD_CTLR_OFFSET), 0xB7);
//     while (1)
//     {
//         if ((Ft_in32((UINTPTR)(Config->Gicv3DistributorAddress + GICD_CTLR_OFFSET)) & 0x80000000) == 0)
//         {
//             break;
//         }
//     }
//     //<! GICD_CTLR_OFFSET result is 0x12
//     //<! wakeup Cpu
//     value = Ft_in32(Ft_in32(GICR_WAKER_CPU(Config->Gicv3RdAddress, CpuID)));
//     value &= ~GICC_WAKER_PROCESSORSLEEP_IN;
//     Ft_out32(Ft_in32(GICR_WAKER_CPU(Config->Gicv3RdAddress, CpuID)), value);
//     while (--count)
//     {
//         value = Ft_in32(Ft_in32(GICR_WAKER_CPU(Config->Gicv3RdAddress, CpuID)));
//         if (1 ^ (value & GICC_WAKER_CHILDRENASLEEP_QUIESCENT))
//             break;
//     }

//     //!< GICR_WAKER_OFFSET is 0
//     value = Ft_in32(Config->Gicv3SgiAddress + GICR_ISENABLER0_OFFSET);
//     Ft_out32(GICR_INTENCLR_CPU(Config->Gicv3SgiAddress, CpuID), Swap32(ALL_PPI_INT_MASK));
//     Ft_out32(GICR_INTENABLE_CPU(Config->Gicv3SgiAddress, CpuID), ALL_SGI_INT_MASK);

//     // val = *GICR_IntEnable;
//     // *GICR_INTENCLR_CPU(Config->Gicv3SgiAddress, CpuID) = SWAP32(ALL_PPI_INT_MASK);
//     // *GICR_INTENABLE_CPU(Config->Gicv3SgiAddress, CpuID) = ALL_SGI_INT_MASK;

//     if (CpuID == 0 && g_FGicVersion < 3)
//     {
//         Ft_out32(Config->Gicv3DistributorAddress + GICD_CTLR_OFFSET, 0);
//         //<! 0x12
//     }

//     value = sys_icc_sre_get();
//     value |= ICC_SRE_SRE;
//     sys_icc_sre_set(value);

//     sys_icc_ctlr_set(0);
//     sys_icc_pmr_set(GICV3_INTR_PRIO_MASK);

//     sys_icc_igrpen0_set(1);

//     if (sys_icc_igrpen0_get() != 1)
//     {
//         Ft_assertVoid(0);
//     }

//     sys_icc_igrpen1_set(1);
//     if ((sys_icc_igrpen1_get() & 1) != 1)
//     {
//         Ft_assertVoid(0);
//     }

//     regGicLineNum = (s32)(Swap32(*(volatile u32 *)(Config->Gicv3DistributorAddress + GICD_TYPER_OFFSET)) & 0x1f);
//     regGicLineNum = (regGicLineNum + 1) * SPI_START_INT_NUM;
//     //<! GICD IS 0x7b0464

//     if (CpuID == 0 && g_FGicVersion >= 3)
//     {
//         /*
//         The Distributor control register (GICD_CTLR) must be configured to enable the interrupt groups and to set the routing mode.
//         Enable Affinity routing (ARE bits) The ARE bits in GICD_CTLR control whether affinity routing is enabled.
//         If affinity routing is not enabled, GICv3 can be configured for legacy operation .
//         Whether affinity routing is enabled or not can be controlled separately for Secure and Non-secure state.
//         Enables GICD_CTLR contains separate enable bits for Group 0, Secure Group 1 and Non-secure Group 1:
//         GICD_CTLR.EnableGrp1S enables distribution of Secure Group 1 interrupts.
//         GICD_CTLR.EnableGrp1NS enables distribution of Non-secure Group 1 interrupts.
//         GICD_CTLR.EnableGrp0 enables distribution of Group 0 interrupts.
//       */
//         Ft_out32(Config->Gicv3DistributorAddress + GICD_CTLR_OFFSET, 0x37);
//         Ft_out32(Config->Gicv3SgiAddress + GICR_ICENABLER0_OFFSET, Swap32(ALL_PPI_INT_MASK));
//         Ft_out32(Config->Gicv3SgiAddress + GICR_ISENABLER0_OFFSET, ALL_SGI_INT_MASK);
//     }
//     else if (g_FGicVersion < 2)
//     {
//         Ft_out32(Config->Gicv3DistributorAddress + GICD_ICENABLE_OFFSET, 0);
//     }

//     /* Get the max priority */
//     Ft_out32((UINTPTR)GIC_PRIO(Config->Gicv3DistributorAddress, SPI_START_INT_NUM), Swap32(0xff));
//     g_FGicv3_PriorityLevelMax = Ft_in32((UINTPTR)GIC_PRIO(Config->Gicv3DistributorAddress, SPI_START_INT_NUM));
//     Ft_out32((UINTPTR)GIC_PRIO(Config->Gicv3DistributorAddress, SPI_START_INT_NUM), Swap32(0));

//     /* clear all pending PPI and SGI interrupts in the distributor */
//     if (g_FGicVersion >= 3)
//     {
//         Ft_out32((Config->Gicv3SgiAddress + GICR_ICPENDR0_OFFSET), Swap32(ALL_PPI_INT_MASK | ALL_SGI_INT_MASK));
//     }
//     else
//     {
//         Ft_out32((Config->Gicv3DistributorAddress + GICD_ICPENDR_OFFSET), Swap32(ALL_PPI_INT_MASK | ALL_SGI_INT_MASK));
//     }

//     /* set default priority for all PPI and SGI interrupts to level 0(highest) */
//     for (i = 0; i < SPI_START_INT_NUM; i += 4)
//     {
//         /* code */
//         Ft_out32((UINTPTR)GIC_PRIO(Config->Gicv3DistributorAddress, i), GIC_IPI_PRIORITY);
//     }

//     if (CpuID == 0)
//     {
//         /*
//          * Disable all SPI interrupts
//          * Clear all pending SPI interrupts in the distributor
//          */
//         for (i = SPI_START_INT_NUM; i < GIC_INT_MAX_NUM; i += BITS_PER_WORD)
//         {
//             Ft_out32((UINTPTR)GIC_INTPENDCLR(Config->Gicv3DistributorAddress, i), 0xffffffff);
//             //<! 0x280  1000

//             Ft_out32((UINTPTR)GIC_INTENCLR(Config->Gicv3DistributorAddress, i), 0xffffffff);
//             //<! 0x180  3c0
//         }

//         /*
//          * set default priority for all SPI interrupts to level 0 and direct all
//          * interrupts to go to CPU 0
//          */

//         for (i = SPI_START_INT_NUM; i < regGicLineNum;)
//         {
//             Ft_out32((UINTPTR)GIC_PRIO(Config->Gicv3DistributorAddress, i), GIC_SPI_PRIORITY_DEFAULT);
//             if (g_FGicVersion < 3)
//             {
//                 Ft_out32((UINTPTR)GIC_CPUTARG(Config->Gicv3DistributorAddress, i), Swap32(GIC_CPU_DIR_DEFAULT));
//                 i += 4;
//             }
//             else
//             {
//                 Ft_out32((UINTPTR)GIC_INTRPUTE_HIGH(Config->Gicv3DistributorAddress, i), GIC_V3_CPU_DIR_DEFAULT_HIGH);
//                 Ft_out32((UINTPTR)GIC_INTRPUTE_LOW(Config->Gicv3DistributorAddress, i), GIC_V3_CPU_DIR_DEFAULT_LOW);
//                 i++;
//             }
//         }
//     }

//     /* setting whether 1-N/N-N and Level/Edge triggered */

//     for (i = SPI_START_INT_NUM; i < regGicLineNum; i += CONFIGS_PER_WORD)
//     {
//         Ft_out32((UINTPTR)GIC_CONFIG(Config->Gicv3DistributorAddress, i), 0x55555555); /* 1-N, Level */
//     }

//     for (i = ARM_GICV3_MSI_START; i < ARM_GICV3_MSI_CNT; i++)
//     {
//         /*
// 		data =  arm_gicv3_drv.rd32(ARM_GICV3_ICDICRn(i));
//         data |= EDGE_TRIGGER << ((i % 16) << 1);
//         arm_gicv3_drv.wr32(ARM_GICV3_ICDICRn(i), data);
// 		*/

//         aGicCfg = Swap32(Ft_in32((UINTPTR)GIC_CONFIG(Config->Gicv3DistributorAddress, i)));
//         aGicCfg |= BIT(((i % CONFIGS_PER_WORD) * GIC_INT_TRIGGER_SHIFT + 1));
//         Ft_out32((UINTPTR)GIC_CONFIG(Config->Gicv3DistributorAddress, i), aGicCfg);
//     }

//     sys_icc_bpr_set(0); //<! 所有抢占优先级
//     /* enable this processor's CPU interface */
//     sys_icc_ctlr_set(GIC_CONTROL_ENABLE);

//     __dsb();

//     if (CpuID == 0 && g_FGicVersion < 3)
//     {
//         /* enable distributor */
//         Ft_out32(Config->Gicv3DistributorAddress + GICD_CTLR_OFFSET, Swap32(GIC_CONTROL_ENABLE));
//     }
// }

static ft_error_t FGicv3_DistInit(u32 Gicv3DistributorAddress, s32 CpuID)
{
    s32 i = 0;
    s32 regGicLineNum = 0;

    regGicLineNum = (s32)(Swap32(*(volatile u32 *)(Gicv3DistributorAddress + GICD_TYPER_OFFSET)) & 0x1f);
    regGicLineNum = (regGicLineNum + 1) * SPI_START_INT_NUM;

    Ft_out32((UINTPTR)(Gicv3DistributorAddress + GICD_CTLR_OFFSET), 0xB7);
    while (1)
    {
        if ((Ft_in32((UINTPTR)(Gicv3DistributorAddress + GICD_CTLR_OFFSET)) & 0x80000000) == 0)
        {
            break;
        }
    }

    if (CpuID == 0 && g_FGicVersion >= 3)
    {
        /*
        The Distributor control register (GICD_CTLR) must be configured to enable the interrupt groups and to set the routing mode.
        Enable Affinity routing (ARE bits) The ARE bits in GICD_CTLR control whether affinity routing is enabled. 
        If affinity routing is not enabled, GICv3 can be configured for legacy operation . 
        Whether affinity routing is enabled or not can be controlled separately for Secure and Non-secure state.
        Enables GICD_CTLR contains separate enable bits for Group 0, Secure Group 1 and Non-secure Group 1:
        GICD_CTLR.EnableGrp1S enables distribution of Secure Group 1 interrupts.
        GICD_CTLR.EnableGrp1NS enables distribution of Non-secure Group 1 interrupts.
        GICD_CTLR.EnableGrp0 enables distribution of Group 0 interrupts.
      */
        Ft_out32(Gicv3DistributorAddress + GICD_CTLR_OFFSET, 0x37);
    }

    for (i = 0; i < SPI_START_INT_NUM; i += 4)
    {
        /* code */
        Ft_out32((UINTPTR)GIC_PRIO(Gicv3DistributorAddress, i), GIC_IPI_PRIORITY);
    }

    if (CpuID == 0)
    {
        /*
         * Disable all SPI interrupts
         * Clear all pending SPI interrupts in the distributor
         */
        for (i = SPI_START_INT_NUM; i < GIC_INT_MAX_NUM; i += BITS_PER_WORD)
        {
            Ft_out32((UINTPTR)GIC_INTPENDCLR(Gicv3DistributorAddress, i), 0xffffffff);
            //<! 0x280  1000

            Ft_out32((UINTPTR)GIC_INTENCLR(Gicv3DistributorAddress, i), 0xffffffff);
            //<! 0x180  3c0
        }

        for (i = SPI_START_INT_NUM; i < regGicLineNum;)
        {

            Ft_out32((UINTPTR)GIC_PRIO(Gicv3DistributorAddress, i), GIC_SPI_PRIORITY_DEFAULT);

            Ft_out32((UINTPTR)GIC_INTRPUTE_HIGH(Gicv3DistributorAddress, i), GIC_V3_CPU_DIR_DEFAULT_HIGH);
            Ft_out32((UINTPTR)GIC_INTRPUTE_LOW(Gicv3DistributorAddress, i), GIC_V3_CPU_DIR_DEFAULT_LOW);
            i++;
        }
    }

    /* setting whether 1-N/N-N and Level/Edge triggered */

    for (i = SPI_START_INT_NUM; i < regGicLineNum; i += CONFIGS_PER_WORD)
    {
        Ft_out32((UINTPTR)GIC_CONFIG(Gicv3DistributorAddress, i), 0x55555555); /* 1-N, Level */
    }

    return FST_SUCCESS;
}

static ft_error_t FGicv3_RdInit(u32 Gicv3RdAddress, s32 CpuId)
{
    u32 value = 0;
    u32 count = 1000;
    //<! wakeup Cpu
    value = Ft_in32(Ft_in32((UINTPTR)GICR_WAKER_CPU(Gicv3RdAddress, CpuId)));
    value &= ~GICC_WAKER_PROCESSORSLEEP_IN;
    Ft_out32(Ft_in32((UINTPTR)GICR_WAKER_CPU(Gicv3RdAddress, CpuId)), value);
    while (--count)
    {
        value = Ft_in32(Ft_in32((UINTPTR)GICR_WAKER_CPU(Gicv3RdAddress, CpuId)));
        if (1 ^ (value & GICC_WAKER_CHILDRENASLEEP_QUIESCENT))
            break;
    }
    return FST_SUCCESS;
}

static ft_error_t FGicv3_SgiInit(u32 Gicv3SgiAddress, s32 CpuId)
{
    Ft_out32((UINTPTR)GICR_INTENCLR_CPU(Gicv3SgiAddress, CpuId), Swap32(ALL_PPI_INT_MASK));
    Ft_out32((UINTPTR)GICR_INTENABLE_CPU(Gicv3SgiAddress, CpuId), ALL_SGI_INT_MASK);

    if (g_FGicVersion >= 3)
    {
        Ft_out32((Gicv3SgiAddress + GICR_ICPENDR0_OFFSET), Swap32(ALL_PPI_INT_MASK | ALL_SGI_INT_MASK));
    }

    if (CpuId == 0 && g_FGicVersion >= 3)
    {
        Ft_out32(Gicv3SgiAddress + GICR_ICENABLER0_OFFSET, Swap32(ALL_PPI_INT_MASK));
        Ft_out32(Gicv3SgiAddress + GICR_ISENABLER0_OFFSET, ALL_SGI_INT_MASK);
    }
    return FST_SUCCESS;
}

static ft_error_t FGicv3_CpuInit(void)
{
    u32 value = 0;

    value = sys_icc_sre_get();
    value |= ICC_SRE_SRE;
    sys_icc_sre_set(value);

    sys_icc_ctlr_set(0);
    sys_icc_pmr_set(GICV3_INTR_PRIO_MASK);

    sys_icc_igrpen0_set(1);

    if (sys_icc_igrpen0_get() != 1)
    {
        Ft_assertNonvoid(0);
    }

    sys_icc_igrpen1_set(1);
    if ((sys_icc_igrpen1_get() & 1) != 1)
    {
        Ft_assertNonvoid(0);
    }

    sys_icc_bpr_set(0); //<! 所有抢占优先级
    /* enable this processor's CPU interface */
    sys_icc_ctlr_set(GIC_CONTROL_ENABLE);

    __dsb();
    return FST_SUCCESS;
}

static void Gicv3_Init(FGicv3_Config_t *Config, s32 CpuID)
{
    FGicv3_DistInit(Config->Gicv3DistributorAddress, CpuID);
    FGicv3_RdInit(Config->Gicv3RdAddress, CpuID);
    FGicv3_SgiInit(Config->Gicv3SgiAddress, CpuID);
    FGicv3_CpuInit();
}

/**
 * @name: FGicV3_Stop
 * @msg:  此方法用于移除当前CPU 所有的中断 并且停止GIC。
 * @return {*}
 */
void FGicV3_Stop(FGicv3_Config_t *Config, u8 CpuID)
{
    u32 RegValue = 0;
    u32 LocalCpuID = ((u32)0x1 << CpuID);
    u32 InterruptID = 0;
    u32 DistDisable = 0;

    if (NULL == Config)
    {
        Ft_assertVoid(0);
    }

    /* if distributor is already disable , no need to do anything */
    RegValue = Ft_in32(Config->Gicv3DistributorAddress + GICD_CTLR_OFFSET);

    if ((RegValue & GICD_CTLR_MASK) == 0U)
    {
        return;
    }

    LocalCpuID |= (LocalCpuID << 8U);
    LocalCpuID |= (LocalCpuID << 16U);

    for (InterruptID = 32U; InterruptID < GIC_INT_MAX_NUM; InterruptID += 4)
    {
        RegValue = Ft_in32((UINTPTR)GIC_CPUTARG(Config->Gicv3DistributorAddress, InterruptID));

        if ((RegValue != LocalCpuID) && (RegValue != 0))
        {
            /* 如果其他 */
            DistDisable = 0;
        }

        /* Remove current CPU from interrupt target register */
        RegValue &= (~LocalCpuID);
        Ft_out32((UINTPTR)GIC_CPUTARG(Config->Gicv3DistributorAddress, InterruptID), RegValue);
    }

    /*
	 * If GIC distributor is safe to be disabled, disable all the interrupt
	 * and then disable distributor.
	 */
    if (DistDisable == 1)
    {
        for (InterruptID = 0; InterruptID < GIC_INT_MAX_NUM; InterruptID += 32U)
        {
            Ft_out32((UINTPTR)GIC_INTENCLR(Config->Gicv3DistributorAddress, InterruptID), 0xFFFFFFFFU);
        }
        Ft_out32(Config->Gicv3DistributorAddress + GICD_CTLR_OFFSET, 0U);
    }
}

/**
 * @name:  FGicv3_InstanceInitialize
 * @msg: 
 * @param {u32} InstanceId 对应的gic 编号
 * @return {*}
 */
s32 FGicv3_InstanceInitialize(FGicv3_Config_t *Config)
{
    s32 CpuId = 0;

    CpuId = FCpu_IdGet();

    Gicv3_Init(Config, CpuId);
    return FST_SUCCESS;
}

/**
 * @name: FGicv3_InterruptHandler 
 * @msg:  
 * @param {void} InstanceId,选择对应的gic 控制器
 * @return {*}
 */
void FGicv3_InterruptHandler(u32 CurrentLevel, u32 InstanceId)
{
    FGicv3_Config_t *Config = NULL;
    FGicv3_VectorTableEntry_t *TablePtr = NULL;

    Config = &g_FGicv3_Config_tTable[(u32)InstanceId];
    /* Read the icc_iar register to identify the hightest priority interrupt ID
        and make sure it is valid. */
    // Ft_printf("is vaild InstanceId %d \r\n", CurrentLevel);
    if (GIC_INT_SPURIOUS == CurrentLevel)
    {
        goto _exit;
    }

    if (GIC_INT_MAX_NUM < CurrentLevel)
    {
        goto _exit;
    }

    /*
    * Jump into the  Isr handler .
    */
    TablePtr = &(Config->HanderTable[CurrentLevel]);
    if (NULL != TablePtr)
    {
        TablePtr->Handler(TablePtr->Args);
    }

    if (ARM_GICV3_MSI_START < CurrentLevel && (CurrentLevel <= ARM_GICV3_MSI_START + ARM_GICV3_MSI_CNT))
    {
        // arm_gicv3_msi_intr_clear(CurrentLevel);
    }
_exit:
    return;
}

/**
 * @name: FGicv3_RegisterHandler 
 * @msg: 
 * @param {u32} InstanceId 选择对应的gic 控制器
 * @param {Ft_FGicv3_InterruptHandler} InterruptHandler 将会被添加进入向量表中的中断函数
 * @param {void} *Args ,参数将会被传入到 InterruptHandler 中
 * @return {*}
 */
s32 FGicv3_RegisterHandler(FGicv3_Config_t *Config, u32 InterruptID, FGicv3_InterruptHandler_t InterruptHandler, void *Args)
{
    Ft_assertNonvoid(Config != NULL);

    if (InterruptID > FT_GICV3_VECTORTABLE_NUM)
    {
        return FST_FAILURE;
    }

    if (NULL != InterruptHandler)
    {
        Config->HanderTable[InterruptID].Handler = InterruptHandler;
    }

    if (NULL != Args)
    {
        Config->HanderTable[InterruptID].Args = Args;
    }

    return FST_SUCCESS;
}

/**
 * @name: GicV3_LookupConfigByBaseAddress
 * @msg: 
 * @param {*}
 * @return {*}
 */
static FGicv3_Config_t *Gicv3_LookupConfigByBaseAddress(u32 GicBaseAddress)
{
    FGicv3_Config_t *Config = NULL;
    u32 instance = 0;

    for (instance = 0; instance < FT_GICV3_INSTANCES_NUM; instance++)
    {
        if (g_FGicv3_Config_tTable[instance].Gicv3BaseAddress == GicBaseAddress)
            Config = &g_FGicv3_Config_tTable[instance];
        break;
    }

    return Config;
}

/**
 * @name: FGicV3_SetPriTrigTypeByDistAddr 
 * @msg: 
 * @param {u32} GicBaseAddress
 * @param {u32} InterruptID
 * @param { u8} Trigger 0b00 Corresponding interrupt is level-sensitive.  0b01 Corresponding interrupt is edge-triggered.
 * @param { u8} Priorty 
 * @return {*}
 */
s32 FGicV3_SetPriTrigTypeByDistAddr(u32 GicBaseAddress, u32 InterruptID, u8 Trigger, u8 Priorty)
{
    FGicv3_Config_t *Config = NULL;
    u32 RegValue = 0;
    Ft_assertNonvoid(InterruptID < FT_GICV3_VECTORTABLE_NUM);
    Ft_assertNonvoid(Trigger <= GIC_TRIGGER_EDGE_SENSITIVE);
    Ft_assertNonvoid(Priorty <= GICV3_MAX_INTR_PRIO_VAL);
    Config = Gicv3_LookupConfigByBaseAddress(GicBaseAddress);
    Ft_assertNonvoid(Config != NULL);

    if (InterruptID < SPI_START_INT_NUM)
    {
        /*   读出当前对应32 位 4组中断优先级配置参数 ,并设置对应的中断优先级*/
        RegValue = Ft_in32((UINTPTR)GIR_PRIO(Config->Gicv3SgiAddress, InterruptID));
        RegValue &= ~(GICD_IPRIORITYR_MASK << ((InterruptID % 4U) * 8U));
        RegValue |= (u32)Priorty << ((InterruptID % 4U) * 8U);
        Ft_out32((UINTPTR)GIR_PRIO(Config->Gicv3SgiAddress, InterruptID), RegValue);
    }
    else
    {
        /*   读出当前对应32 位 4组中断优先级配置参数 ,并设置对应的中断优先级*/
        RegValue = Ft_in32((UINTPTR)GIC_PRIO(Config->Gicv3DistributorAddress, InterruptID));
        RegValue &= ~(GICD_IPRIORITYR_MASK << ((InterruptID % 4U) * 8U));
        RegValue |= (u32)Priorty << ((InterruptID % 4U) * 8U);
        Ft_out32((UINTPTR)GIC_PRIO(Config->Gicv3DistributorAddress, InterruptID), RegValue);

        /* 读取出32位  16 组 中断触发源配置，并且进行设置*/
        RegValue = Ft_in32((UINTPTR)GIC_CONFIG(Config->Gicv3DistributorAddress, InterruptID));
        RegValue &= ~(GICD_ICFGR_MASK << ((InterruptID % 16U) * 2U));
        RegValue |= (u32)Trigger << ((InterruptID % 16U) * 2U);
        Ft_out32((UINTPTR)GIC_CONFIG(Config->Gicv3DistributorAddress, InterruptID), RegValue);
    }
    return FST_SUCCESS;
}

/**
 * @name: FGicV3_GetPriTrigTypeByDistAddr 
 * @msg: 
 * @param {u32} GicBaseAddress
 * @param {u32} InterruptID
 * @param { u8} Trigger
 * @param { u8} Priorty
 * @return {*}
 */
void FGicV3_GetPriTrigTypeByDistAddr(u32 GicBaseAddress, u32 InterruptID, u8 *Trigger, u8 *Priorty)
{
    u32 RegValue = 0;
    Ft_assertVoid(InterruptID < FT_GICV3_VECTORTABLE_NUM);
    Ft_assertVoid(*Trigger <= GIC_TRIGGER_EDGE_SENSITIVE);
    Ft_assertVoid(*Priorty <= GICV3_MAX_INTR_PRIO_VAL);

    /*
    *   获取中断优先级      
    */
    RegValue = Ft_in32((UINTPTR)GIC_PRIO(GicBaseAddress, InterruptID));
    RegValue = RegValue >> ((InterruptID % 4U) * 8U);
    *Priorty = (u8)(RegValue & GICD_IPRIORITYR_MASK);

    /*
    *   获取当前中断触发信息  
    */
    RegValue = Ft_in32((UINTPTR)GIC_CONFIG(GicBaseAddress, InterruptID));
    RegValue = RegValue >> ((InterruptID % 16U) * 2U);
    *Trigger = (u8)RegValue & GICD_ICFGR_MASK;
}

/**
 * @name: FGicV3_InterruptUnmapByDistAddr 
 * @msg:  清除寄存器中的CPU中的 target PEs
 * @param {u32} GicBaseAddress
 * @param {u32} InterruptID
 * @param { u8} cpu
 * @return {*}
 */
void FGicV3_InterruptUnmapByDistAddr(u32 GicBaseAddress, u32 InterruptID, u8 CpuID)
{
    u32 RegValue = 0;
    Ft_assertVoid(InterruptID < GIC_INT_MAX_NUM);
    RegValue = Ft_in32((UINTPTR)GIC_CPUTARG(GicBaseAddress, InterruptID));
    RegValue &= ~(1U << (((InterruptID % 4) * 8U) + CpuID));
    Ft_out32((UINTPTR)GIC_CPUTARG(GicBaseAddress, InterruptID), RegValue);
}

/**
 * @name: 
 * @msg: 
 * @param {Ft_Gicv3_Config} *Config
 * @param {u32} InterruptID
 * @return {*}
 */
void FGicV3_DisableInterrupt(FGicv3_Config_t *Config, u32 InterruptID)
{
    u32 RegValue;
    s32 CpuId = 0;
    Ft_assertVoid(InterruptID < GIC_INT_MAX_NUM);

    // RegValue = 0x1U << (InterruptID % 32U);

    if (InterruptID < SPI_START_INT_NUM)
    {
        CpuId = FCpu_IdGet();
        RegValue = Ft_in32(GICR_INTENCLR_CPU(Config->Gicv3SgiAddress, CpuId));
        RegValue |= (0x1U << (InterruptID % 32U));
        Ft_out32(GICR_INTENCLR_CPU(Config->Gicv3SgiAddress, CpuId), RegValue);
    }
    else
    {
        RegValue = Ft_in32((UINTPTR)GIC_INTENCLR(Config->Gicv3SgiAddress, InterruptID));
        RegValue |= (0x1U << (InterruptID % 32U));
        Ft_out32((UINTPTR)GIC_INTENCLR(Config->Gicv3SgiAddress, InterruptID), RegValue);
    }
}

/**
 * @name: FGicV3_EnableInterrupt 
 * @msg: 
 * @param {u32} GicBaseAddress
 * @param {u32} InterruptID
 * @return {*}
 */
void FGicV3_EnableInterrupt(FGicv3_Config_t *Config, u32 InterruptID)
{
    u32 RegValue;
    s32 CpuId = 0;
    Ft_assertVoid(InterruptID < GIC_INT_MAX_NUM);

    if (InterruptID < SPI_START_INT_NUM)
    {
        CpuId = FCpu_IdGet();
        // Ft_printf("cpuid is %x \r\n", CpuId);
        // Ft_printf("before GICR_ISENABLER0_OFFSET %x \r\n", Ft_in32(GICR_INTENABLE_CPU(Config->Gicv3SgiAddress, CpuId)));
        RegValue = Ft_in32(GICR_INTENABLE_CPU(Config->Gicv3SgiAddress, CpuId));
        RegValue |= (0x1U << (InterruptID % 32U));
        Ft_out32(GICR_INTENABLE_CPU(Config->Gicv3SgiAddress, CpuId), RegValue);
        // Ft_printf("GICR_ISENABLER0_OFFSET %x \r\n", Ft_in32(GICR_INTENABLE_CPU(Config->Gicv3SgiAddress, CpuId)));
    }
    else
    {
        RegValue = Ft_in32((UINTPTR)GICD_ISENABLER(Config->Gicv3DistributorAddress, InterruptID));
        RegValue |= (0x1U << (InterruptID % 32U));
        Ft_out32((UINTPTR)GICD_ISENABLER(Config->Gicv3DistributorAddress, InterruptID), RegValue);
    }
}

/**
 * @name: FGicv3_Ack
 * @msg: Writes to this register to inform the CPU interface that it has completed the processing of the 
        specified Group 1 interrupt.
 * @in param {u32} InterruptID
 * @in param {s32} SrcCpu
 * @return {*}
 */
ft_error_t FGicv3_Ack(u32 InterruptID, s32 CpuId)
{
    sys_icc_eoir1_set(InterruptID);
    return FST_SUCCESS;
}
