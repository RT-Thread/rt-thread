/*************************************************************!
 *     技术讨论：QQ群  123763203
 *     官网    ：www.navota.com
 *
 * @file       ics.c
 * @brief      时钟模块（ICS)函数库
 * @author     Navota
 * @date       2017-1-1
 ****************************************************************/
#include "common.h"
#include "ics.h"

/* 复位后ICS和OSC模块寄存器的默认值 */
#define ICS_C1_DEFAULT  0x04
#define ICS_C2_DEFAULT  0x20
#define ICS_C3_DEFAULT  0x54
#define ICS_C4_DEFAULT  0x00
#define ICS_S_DEFAULT   0x50
#define OSC_CR_DEFAULT  0


/*****************************************************************************//*!
   *
   * @ 概要  ICS的工作模式由当前的FEI模式切换为FEE模式，对选中的时钟源做1分频
   *         OSC模块的输出时钟选择振荡器时钟源
   *
   * @ 参数【输入】 pConfig  指向ICS配置结构体
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   *****************************************************************************/
void FEI_to_FEE(ICS_ConfigType *pConfig)
{
    /*
     * 使能OSC模块
     */
    OSC_Init(&pConfig->oscConfig); /*OSC模块初始化 */

    /*
     * 对外部参考时钟进行分频，可将外部时钟分频到31.25k~39.0625k之间
     */

    ICS_SetClkDivider(pConfig->u32ClkFreq);

        /*将FLL的参考时钟选择为外部时钟*/
    ICS->C1 =  ICS->C1 & ~ICS_C1_IREFS_MASK;

        /*等待FLL参考时钟变为外部时钟*/

#if defined(IAR)
    asm(
        "nop \n"
        "nop \n"
    );
#elif defined(__MWERKS__)
    asm{
        nop
        nop
};
#endif
    while(ICS->S & ICS_S_IREFST_MASK);

        /* 等待FLL时钟成为ICS输出时钟源*/
    while(!(ICS->S & ICS_S_LOCK_MASK));

    /*
     *现在FLL输出时钟变时钟频率等于FLL参考时钟分频结果乘以FLL的倍频系数
     * FLL的倍频系数请参考参考手册
     */
#if defined(CPU_NV32)
  /*对选中的ICS输出时钟源做1分频*/
    if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) == 1)
    {
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
    }
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif

    /*
     * 完成对选中的时钟源做1分频，系统/总线时钟时频率为设置的目标频率
     */
    /*LOLS清0*/
    ICS->S |= ICS_S_LOLS_MASK;
}

/*****************************************************************************//*!
   *
   * @ 概要  ICS的工作模式由当前的FEI模式转变成FBI模式，对选中的ICS输出时钟源
   *         进行2分频
   *
   * @ 参数  pConfig    指向ICS配置结构体.
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/
void FEI_to_FBI(ICS_ConfigType *pConfig)
{

        /*ICS输出时钟源选择内部参考时钟*/
    ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(1);
    ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK);
        /*等待内部时钟成为ICS输出时钟源*/
#if defined(IAR)
    asm(
        "nop \n"
        "nop \n"
    );
#elif defined(__MWERKS__)
    asm{
        nop
        nop
        };
#endif
    while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=1);

    /*
     * 现在内部参考时钟为ICS输出时钟源
     */
#if defined(BUS_CLK_EQU_CORE_DIVIDE_BY_2)||defined(CPU_NV32)
         /*对选中的ICS输出时钟源做2分频*/
    if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
    {
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
    }

#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK));
#endif

     /*LOLS清零*/
    ICS->S |= ICS_S_LOLS_MASK;
}

/*****************************************************************************//*!
   *
   * @ 概要  ICS的工作模式由当前的FEI模式转换成FBE模式，对选中的ICS输出时钟源做2分频
   *         OSC模块的输出时钟选择振荡器时钟源
   *
   * @ 参数  pConfig   指向ICS的配置结构体 .
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/

void FEI_to_FBE(ICS_ConfigType *pConfig)
{
    OSC_Init(&pConfig->oscConfig); /*初始化OSC 模块 */

         /*设置FLL的参考时钟为外部时钟*/

    ICS->C1 =  ICS->C1 & ~(ICS_C1_IREFS_MASK);
    ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(2);
    ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK);

        /*等在参考时钟发生改变*/
#if defined(IAR)
    asm(
        "nop \n"
        "nop \n"
    );
#elif defined(__MWERKS__)
    asm{
        nop
        nop
        };
#endif

    while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=2);  /*外部时钟成为ICS时钟输出源*/
        while(ICS->S & ICS_S_IREFST_MASK);  /*FLL参考时钟成为外部时钟*/

    /*
     * 现在外部时钟成为ICS输出时钟源
     */
#if defined(CPU_NV32)
        /*对选中的ICS输出时钟源做2分频*/
    if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
    {
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
    }
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
    /*
     * 现在ICS输出时钟频率为选中的输出时钟源的2分频
     */
        /* LOLS清零 */
    ICS->S |= ICS_S_LOLS_MASK;
}


/*****************************************************************************//*!
   *
   * @ 概要  ICS的工作模式由当前的FEI模式转换成FBE模式，对选中的输出时钟源做2分频
   *         OSC输出时钟选择EXTAL引脚的外部时钟源
   *
   * @ 参数 pConfig  指向配置结构体.
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/
void FEI_to_FBE_OSC(ICS_ConfigType *pConfig)
{

    OSC_Init(&pConfig->oscConfig); /* 初始化OSC */

    /*
     * 设置外部参考时钟的分频系数，将参考时钟的分频结果设定在FLL可以锁定的31.25k~39.0625k范围内，
     */
    ICS_SetClkDivider(pConfig->u32ClkFreq);

        /*改变参考时钟源，将FLL的参考时钟设置为而外部时钟*/
        ICS->C1 =  ICS->C1 & ~(ICS_C1_IREFS_MASK);/*将FLL的参考时钟设置为而外部时钟*/
    ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(2);  /*输出时钟源选择外部时钟*/
    ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK);

        /* 等待参考时钟发生改变*/

#if defined(IAR)
    asm(
        "nop \n"
        "nop \n"
    );
#elif defined(__MWERKS__)
    asm{
        nop
        nop
        };
#endif
    while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=2);/*外部时钟成为ICS时钟输出时钟源*/
        while(ICS->S & ICS_S_IREFST_MASK);   /*外部时钟成为FLL参考时钟*/

    /*
     * 现在外部时钟成为FLL参考时钟和ICS输出时钟源
     */
#if defined(CPU_NV32)
             /*对选中的ICS输出时钟源做2分频*/
    if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
    {
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
    }
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
    /*
     * 现在ICS的输出时钟频率，为外部参考时钟的2分频
     */
        /*LOLS 清零*/
    ICS->S |= ICS_S_LOLS_MASK;
}

/*****************************************************************************//*!
   *
   * @ 概要  ICS的工作模式由当前的FEI模式转换FEE模式，对选中的ICS输出时钟源做2分频
   *         OSC输出时钟选择EXTAL引脚的外部时钟源
   *
   * @ 参数  pConfig    指向配置结构体
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/

void FEI_to_FEE_OSC(ICS_ConfigType *pConfig)
{

    OSC_Init(&pConfig->oscConfig); /* 初始化OSC */

    /*
     * 设置外部参考时钟的分频系数，将参考时钟的分频结果设定在FLL可以锁定的31.25k~39.0625k范围内
     */
    ICS_SetClkDivider(pConfig->u32ClkFreq);

        /* 将FLL的参考时钟设置为外部时钟 */

    ICS->C1 =  ICS->C1 & ~(ICS_C1_IREFS_MASK);

        /*等待参考时钟变化*/
#if defined(IAR)
    asm(
        "nop \n"
        "nop \n"
    );
#elif defined(__MWERKS__)
    asm{
        nop
        nop
        };
#endif
    while(ICS->S & ICS_S_IREFST_MASK); /*FLL参考时钟变为外部时钟*/

        /*等待FLL成为ICS输出时钟源 */
    while(!(ICS->S & ICS_S_LOCK_MASK));
#if defined(CPU_NV32)
       /*对选中的时钟源做2分频*/
    if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
    {
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
    }
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
    /*
     * 现在ICS输出时钟频率，成为要设置的目标频率
     */

     /* LOLS清零 */
    ICS->S |= ICS_S_LOLS_MASK;
}

/*****************************************************************************//*!
   *
   * @ 概要 将ICS的工作模式由当前的FEE模式转换成FEI模式.
   *
   * @ 参数  pConfig  指向配置结构体
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/
void FEE_to_FEI(ICS_ConfigType *pConfig)
{
       /*选择内部时钟作为FLL的参考时钟*/
    ICS->C1 =  ICS->C1 | (ICS_C1_IREFS_MASK);

        /*等待参考时钟发生改变*/
#if defined(IAR)
    asm(
        "nop \n"
        "nop \n"
    );
#elif defined(__MWERKS__)
    asm{
        nop
        nop
        };
#endif
    while(!(ICS->S & ICS_S_IREFST_MASK)); /*FLL参考时钟成为内部时钟*/

        /*FLL时钟成为ICS输出时钟源 */
    while(!(ICS->S & ICS_S_LOCK_MASK));
         /*LOLS清零*/
    ICS->S |= ICS_S_LOLS_MASK;

    /*
     * 现在FLL输出成为ICS输出时钟源
     */
#if defined(CPU_NV32)
        /*对选中的ICS输出时钟源做2分频*/
    if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
    {
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
    }
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
    /*
     * 现在系统/总线时钟大约为 16MHz
     */
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
      OSC_Disable();            /* 禁用 OSC模块 */
}

/*****************************************************************************//*!
   *
   * @ 概要 将ICS的工作模式由当前的FEE模式转换成FBI模式.
   *
   * @ 参数 pConfig    指向配置结构体
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/
void FEE_to_FBI(ICS_ConfigType *pConfig)
{
        /*LOLS清零*/
    ICS->S |= ICS_S_LOLS_MASK;

  /* 选择内部时钟作为ICS输出时钟源 */
    /* 选择内部时钟作为FLL参考时钟 */
    /* LP = 0 在bypass模式FLL不会被禁止*/

    ICS->C1 =  ICS->C1 | (ICS_C1_IREFS_MASK);
    ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(1);
    ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK);

        /* 等待参考时钟发生改变 */
#if defined(IAR)
    asm(
        "nop \n"
        "nop \n"
    );
#elif defined(__MWERKS__)
    asm{
        nop
        nop
        };
#endif
    while(!(ICS->S & ICS_S_IREFST_MASK));  /*FLL参考时钟成为内部时钟*/
    while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=1);  /*内部时成为ICS输出时钟源*/

#if defined(BUS_CLK_EQU_CORE_DIVIDE_BY_2)||defined(CPU_NV32)
         /*对所选中的ICS输出时钟源做2分频*/
    if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
    {
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
    }

#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK));

#endif
        OSC_Disable();
}

/*****************************************************************************//*!
   *
   * @ 概要  将ICS的工作模式由当前的FEE模式转变成FBE模式
   *
   * @ 参数  pConfig  指向配置结构体
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/

void FEE_to_FBE(ICS_ConfigType *pConfig)
{
        /*LOLS清零*/
    ICS->S |= ICS_S_LOLS_MASK;


        /* LP = 0 */
        /*选择外部时钟作为ICS输出时钟源*/
        /* LP = 0 在bypass模式FLL不会被禁止*/

    ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(2);
    ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK);

        /*等待输出时钟源发生改变*/
#if defined(IAR)
    asm(
        "nop \n"
        "nop \n"
    );
#elif defined(__MWERKS__)
    asm{
        nop
        nop
        };
#endif
    while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=2);

   /* 现在ICS输出时钟源选择外部时钟源
     * 注释: 确保外部时钟频率在20MHz以内
     */
#if defined(CPU_NV32)
        /*对选择的ICS输出时钟源做2分频*/
    if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
    {
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
    }
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
}

/*****************************************************************************//*!
   *
   * @ 概要 将ICS的工作模式由当前的FBI模式转换成FBE模式
   *
   * @ 参数  pConfig   指向配置结构体.
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/
void FBI_to_FBE(ICS_ConfigType *pConfig)
{
    OSC_Init(&pConfig->oscConfig); /*初始化OSC*/

    /* 选择外部时钟做为FLL的参考时钟 */
    /*选择外部时钟作为输出时钟源*/

       ICS->C1 =  ICS->C1 & ~(ICS_C1_IREFS_MASK);
    ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(2);


    /* 等待输出时钟源发生改变 */

#if defined(IAR)
    asm(
        "nop \n"
        "nop \n"
    );
#elif defined(__MWERKS__)
    asm{
        nop
        nop
        };
#endif
    while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=2); /*外部时钟成为ICS输出时钟源*/
    while((ICS->S & ICS_S_IREFST_MASK));/*外部时钟成为FLL的参考时钟*/

        /* 现在系统时钟源是外部参考时钟
     * 注释:确保外部时钟源的频率在20MHz内
     */
#if defined(CPU_NV32)
         /*对选中的时钟源做2分频*/
    if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
    {
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
    }
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
}

/*****************************************************************************//**
   *
   * @ 概要 将ICS的工作模式由当前的FBI模式转换成FEE模式
   *
   * @ 参数  pConfig    指向配置结构体
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/
void FBI_to_FEE(ICS_ConfigType *pConfig)
{
    OSC_Init(&pConfig->oscConfig); /*初始化OSC*/

    /* 选择外部时钟作为FLL的参考时钟 */
    /* 选择FLL输出作为做为ICS输出时钟源*/

    ICS->C1 =  ICS->C1 & ~(ICS_C1_IREFS_MASK);
    ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK));

        /*等待时钟源改变*/
#if defined(IAR)
    asm(
        "nop \n"
        "nop \n"
    );
#elif defined(__MWERKS__)
    asm{
        nop
        nop
        };
#endif

    while((ICS->S & ICS_S_CLKST_MASK));   /*FLL时钟成为ICS输出时钟源*/
    while((ICS->S & ICS_S_IREFST_MASK));  /*外部时钟成为FLL参考时钟*/

     /* 现在系统时钟源为外部时钟
     * 注释: 确保外部时钟源的频率在20MHz内
     */
#if defined(CPU_NV32)
        /*对选中的时钟源做2分频*/
    if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
    {
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
    }
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
       /*LOLS清零*/
    ICS->S |= ICS_S_LOLS_MASK;
}

/*****************************************************************************//*!
   *
   * @ 概要 将ICS的工作模式由当前的FBI模式转换成FBIP模式
   *
   * @ 参数  pConfig   输出指向配置结构体
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 警告 必须运行在调试接口没有没有接线的状态下
   * @ 参看  ICS_ConfigType
   *****************************************************************************/
void FBI_to_FBILP(ICS_ConfigType *pConfig)
{
    /*
     * 假设外部晶振时8MHz或者4MHz
     */
    ICS->C2 |= ICS_C2_LP_MASK;  /*进入低功耗模式 */
}



/*****************************************************************************//*!
   *
   * @ 概要 将ICS的工作模式由当前的FBI模式转变为FEI模式
   *
   * @ 参数 pConfig  指向配置结构体.
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/
void FBI_to_FEI(ICS_ConfigType *pConfig)
{
     /* 选择内部时钟为FLL的参考时钟 */
    /*选择FLL输出作为ICS输出时钟源*/
    ICS->C1 =  ICS->C1 | (ICS_C1_IREFS_MASK);
    ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK));

        /*等待时钟源发生改变*/

#if defined(IAR)
    asm(
        "nop \n"
        "nop \n"
    );
#elif defined(__MWERKS__)
    asm{
        nop
        nop
        };
#endif
    while((ICS->S & ICS_S_CLKST_MASK));    /*FLL输出成为ICS输出时钟源*/
    while(!(ICS->S & ICS_S_IREFST_MASK));  /*FLL的参考时钟选择为外部时钟*/


    /*
     * 现在ICS输出时钟源为FLL输出
     */
#if defined(CPU_NV32)
         /*对选中的时钟源做2分频*/
    if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
    {
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
    }
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif

        /*LOLS清零 */
    ICS->S |= ICS_S_LOLS_MASK;
}

/*****************************************************************************//*!
   *
   * @ 概要  将ICS的工作模式由当前的FBE模式转换成FBI模式
   *
   * @ 参数  pConfig   指向配置结构体
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/
void FBE_to_FBI(ICS_ConfigType *pConfig)
{
        /*选择内部时钟作为FLL的参考时钟*/
    /*选择内部时钟作为ICS输出时钟源*/
    ICS->C1 =  ICS->C1 | (ICS_C1_IREFS_MASK);
    ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(1);

        /*等待时钟源发生改变*/
#if defined(IAR)
    asm(
        "nop \n"
        "nop \n"
    );
#elif defined(__MWERKS__)
    asm{
        nop
        nop
        };
#endif
    while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) != 1);/*内部时钟成为ICS输出时钟源*/
    while(!(ICS->S & ICS_S_IREFST_MASK)); /*内部时钟成为FLL的参考时钟*/

    /*
     * 现在ICS输出时钟源为内部时钟
     */

#if defined(CPU_NV32)
        /*对选中的时钟源做2分频*/
    if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
    {
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
    }
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif

    /*
     * 禁用OSC模块
     */
    OSC_Disable();
}


/*****************************************************************************//*!
   *
   * @ 概要 将ICS的工作模式由当前的FBE模式转换成FEE模式
   *
   * @ 参数 pConfig   指向配置结构体.
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/
void FBE_to_FEE(ICS_ConfigType *pConfig)
{

        /*选择FLL输出作为输出时钟源*/
    ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK));

        /*等待ICS输出时钟源发生改变*/
#if defined(IAR)
    asm(
        "nop \n"
        "nop \n"
    );
#elif defined(__MWERKS__)
    asm{
        nop
        nop
        };
#endif
    while(ICS->S & ICS_S_CLKST_MASK);


    /*
    * 现在ICS输出时钟源为FLL输出
     * 注释: 外部时钟频率 <= 20MHz
     */
#if defined(CPU_NV32)
         /*对选中的ICS输出时钟源做2分频*/
    if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
    {
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
    }
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
         /* LOLS清零 */
    ICS->S |= ICS_S_LOLS_MASK;
}


/*****************************************************************************//*!
   *
   * @ 概要 将ICS的工作模式由当前的FBE模式转变成FEI模式
   *
   * @ 参数 pConfig    指向配置结构体
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/
void FBE_to_FEI(ICS_ConfigType *pConfig)
{
    /* 选择内部时钟作为FLL的参考时钟*/
    /*选择FLL输出做为ICS输出时钟源*/

    ICS->C1 =  ICS->C1 | (ICS_C1_IREFS_MASK);
    ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK));

        /*等待时钟源改变*/
#if defined(IAR)
    asm(
        "nop \n"
        "nop \n"
    );
#elif defined(__MWERKS__)
    asm{
        nop
        nop
        };
#endif
    while((ICS->S & ICS_S_CLKST_MASK));   /*FLL输出成为ICS输出时钟源*/
    while(!(ICS->S & ICS_S_IREFST_MASK)); /*内部时钟中成为FLL参考时钟*/

  /*
   * 现在FLL输出成为ICS输出时钟源
   */

#if defined(CPU_NV32)

       /*对选中的时钟源做2分频*/
    if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
    {
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
    }
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
         /*LOLS清零*/
    ICS->S |= ICS_S_LOLS_MASK;

    /*
     *禁用OSC模块
     */
    OSC_Disable();
}

/*****************************************************************************//*!
   *
   * @ 概要 将ICS的工作模式由当前的FBE模式转变为FBELP模式
   *
   * @ 参数  pConfig   指向配置结构体.
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/
void FBE_to_FBELP(ICS_ConfigType *pConfig)
{
    /* enter low power mode */
        /*进入低功耗模式*/
    ICS->C2 = ICS->C2 | (ICS_C2_LP_MASK);
}
/*****************************************************************************//*!
   *
   * @ 概要 将ICS的工作模式由当前的FBELP模式转换成FBE模式
   *
   * @ 参数  pConfig     指向配置结构体.
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/
void FBELP_to_FBE(ICS_ConfigType *pConfig)
{
    /* enter low power mode */
        /*禁用低功耗模式*/
    ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK);
}

/*****************************************************************************//*!
   *
   * @ 概要 将ICS的工作模式由当前的FBILP转换到FBI模式
   *
   * @ 参数  pConfig  指向配置结构体.
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/
void FBILP_to_FBI(ICS_ConfigType *pConfig)
{
    /* enter low power mode */
        /*禁用低功耗模式*/
    ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK);
}

/*****************************************************************************//*!
   *
   * @ 概要 调整内部内部时钟 (IRC).
   *
   * @ 参数  u16TrimValue   调整值
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   *****************************************************************************/

void ICS_Trim(uint16_t u16TrimValue)
{
   ICS->C3 =  (uint8_t) u16TrimValue;  /*将调整值写入寄存器*/
   ICS->C4 = (ICS->C4 & ~(ICS_C4_SCFTRIM_MASK)) | ((u16TrimValue>>8) & 0x01);
   while(!(ICS->S & ICS_S_LOCK_MASK));
}
/*****************************************************************************//*!
   *
   * @ 概要 对外部参考时钟进行分频，使得分频结果在FLL可以锁定的31.25k~39.0625k内
   *
   * @ 参数 u32ClkFreqKHz    参考时钟频率.
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   *****************************************************************************/

void ICS_SetClkDivider(uint32_t u32ClkFreqKHz)
{

    switch(u32ClkFreqKHz)
    {
        case 8000L:
        case 10000L:
            /* 8MHz or 10MHz*/
            ICS->C1 = (ICS->C1 & ~(ICS_C1_RDIV_MASK)) | ICS_C1_RDIV(3);
                                                                         /*8MHz分频结果是 8000/256 = 31.25K */
                                                                        /*10MHz分频结果是 8000/256 = 31.25K*/
            break;
        case 4000L:
            /* 4MHz */
            ICS->C1 = (ICS->C1 & ~(ICS_C1_RDIV_MASK)) | ICS_C1_RDIV(2);
                                                                        /*4MHz分频结果是 4000/128 = 31.25K*/
            break;
        case 12000L:
            /* 12MHz */
            ICS->C1 = (ICS->C1 & ~(ICS_C1_RDIV_MASK)) | ICS_C1_RDIV(3);
                                                                        /*12MHz分频结果是12000/512 = 23.43K*/
            break;
        case 16000L:
            /* 16MHz */
            ICS->C1 = (ICS->C1 & ~(ICS_C1_RDIV_MASK)) | ICS_C1_RDIV(4);
                                                                        /* 16MHz分频结果是 16000/512 = 31.25K */
            break;
        case 20000L:
            /* 20MHz */
            ICS->C1 = (ICS->C1 & ~(ICS_C1_RDIV_MASK)) | ICS_C1_RDIV(4);
                                                                        /*20MHz分频结果是 20000/512 = 39.0625K */
            break;
        case 32L:
            /* 32KHz */
            ICS->C1  &= ~(ICS_C1_RDIV_MASK);
            break;
        default:
            break;
    }
}
/*****************************************************************************//*!
   *
   * @ 概要 初始化ICS模块根据定义所需要的总线时钟频率.
   *
   * @ 参数 pConfig  指向配置结构体.
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_ConfigType
   *****************************************************************************/


void ICS_Init(ICS_ConfigType *pConfig)
{
  if(pConfig->u8ClkMode == ICS_CLK_MODE_FEE)
  {
        pConfig->oscConfig.bIsCryst = 1;   /* OSC的输出选择选择振动器时钟源 */
        pConfig->oscConfig.bWaitInit = 1;  /* 等待振荡器初始化化完成 */

      /*选择FEE模式，OSC输出选择振荡器时钟源*/
        FEI_to_FEE(pConfig);
  }
  else if (pConfig->u8ClkMode == ICS_CLK_MODE_FEE_OSC)
  {
        pConfig->oscConfig.bIsCryst = 0;     /*OSC输出时钟选择EEXTAL引脚的外部时钟源*/

     /*选择FEE工作模式；OSC输出时钟选择EEXTAL引脚的外部时钟源*/
        FEI_to_FEE_OSC(pConfig);
  }
  else if (pConfig->u8ClkMode == ICS_CLK_MODE_FBE_OSC)
  {
        pConfig->oscConfig.bIsCryst = 0;  /* is clock：OSC输出时钟选择EXTAL引脚的外部时钟源 */
        /* 选择FBE工作模式；OSC输出时钟选择EXTAL引脚的外部时钟源*/
        FEI_to_FBE_OSC(pConfig);
  }
    else if(pConfig->u8ClkMode == ICS_CLK_MODE_FBELP )
    {
    pConfig->oscConfig.bIsCryst = 1;        /* OSC的输出时钟选择选择振动器时钟源 */
        pConfig->oscConfig.bWaitInit = 1;       /*等待振荡器初始化化完成 */

        /* 选择FBE模式，OSC的输出时钟选择选择振动器时钟源*/
                    FEI_to_FBE(pConfig);    /*先选择PBE模式*/
            FBE_to_FBELP(pConfig);   /*选择FBELP*/
            ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
    }
        else if(pConfig->u8ClkMode == ICS_CLK_MODE_FBILP )
    {

            /* OSC输出时钟选择EXTAL引脚的外部时钟源*/
            pConfig->oscConfig.bIsCryst = 0;

            /* 选择FBE模式，OSC输出时钟选择EXTAL引脚的外部时钟源*/
              FEI_to_FBI(pConfig);
          FBI_to_FBILP(pConfig);
          ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
    }
  else
  {

       /*ICS默认工作模式FEI模式*/
        #if defined(CPU_NV32)
        if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) == 1)
        {
            ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
        }
        #else
            ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
        #endif
  }

}
/*****************************************************************************//*!
   *
   * @ 概要 对ICS模块各寄存器进行复位.
   *
   * @ 无参数
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看  ICS_Init
   *****************************************************************************/

void ICS_DeInit(void)
{
    ICS->C1 = ICS_C1_DEFAULT;
    ICS->C2 = ICS_C2_DEFAULT;
    ICS->C3 = ICS_C3_DEFAULT;
    ICS->C4 = ICS_C4_DEFAULT;
    while(ICS->S != ICS_S_DEFAULT)
        ;
}

/*****************************************************************************//*!
   *
   * @ 概要 通过设定的参数初始化XOSC
   *
   * @ 参数  pConfig   指向osc配置结构体
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   *****************************************************************************/
void OSC_Init(OSC_ConfigType *pConfig)
{
    uint8   cr = 0;
    /*
     *
     */
    if(pConfig->bGain) /*高增益振荡器选择*/
    {
        /* high gain：选择高增益模式 */
        cr |= OSC_CR_HGO_MASK ;
    }

    if(pConfig->bRange)  /*频率范围的选择*/
    {
        cr |= OSC_CR_RANGE_MASK; /*选择高频范围 */
    }

    if(pConfig->bStopEnable) /*停止模式下的OSC使能*/
    {
        cr |= OSC_CR_OSCSTEN_MASK; /*OSC在停止模式下保持使能*/
    }

    if(pConfig->bIsCryst)     /*OSC输出选择*/
    {
        cr |= OSC_CR_OSCOS_MASK; /*选择振荡器时钟*/
    }

    if(pConfig->bEnable)  /*OSC使能*/
    {
        cr |= OSC_CR_OSCEN_MASK;
    }

    OSC->CR = cr;   /*数值写入控制寄存器*/

    if(pConfig->bWaitInit)
    {

        /*
     *等待初始化完成
         */
        while(!(OSC->CR & OSC_CR_OSCINIT_MASK));

    }
}

/*****************************************************************************//*!
   *
   * @ 概要 重置OSC模块，使其恢复到默认状态.
   *
   * @ 无输参数
   *
   * @ 无返回
   *
   * @ 成功/失败的标准 ：无
   * @ 参看   ICS_Init
   *****************************************************************************/

void OSC_DeInit(void)
{
    OSC->CR = OSC_CR_DEFAULT;
}





