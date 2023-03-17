#include "bl616_common.h"
#include "bl616_glb.h"
#include "bl616_clock.h"

/** @addtogroup  BL616_Periph_Driver
 *  @{
 */

/** @defgroup DRIVER_COMMON DRIVER_COMMON
 *  @brief Digger driver common functions
 *  @{
 */

/** @defgroup DRIVER_Private_Type
 *  @{
 */

/*@} end of group DRIVER_Private_Type*/

/** @defgroup DRIVER_Private_Defines
 *  @{
 */

/*@} end of group DRIVER_Private_Defines */

/** @defgroup DRIVER_Private_Variables
 *  @{
 */

/*@} end of group DRIVER_Private_Variables */

/** @defgroup DRIVER_Global_Variables
 *  @{
 */

/*@} end of group DRIVER_Global_Variables */

/** @defgroup DRIVER_Private_FunctionDeclaration
 *  @{
 */

/*@} end of group DRIVER_Private_FunctionDeclaration */

/** @defgroup DRIVER_Private_Functions
 *  @{
 */

/*@} end of group DRIVER_Private_Functions */

/** @defgroup DRIVER_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief      delay us
 *
 * @param[in]  core:  systemcoreclock
 *
 * @param[in]  cnt:  delay cnt us
 *
 * @return none
 *
 *******************************************************************************/
#ifdef ARCH_RISCV
__WEAK
void ATTR_TCM_SECTION ASM_Delay_Us(uint32_t core, uint32_t cnt, uint32_t loopT)
{
    volatile uint32_t divVal = loopT;
    volatile uint32_t speed = 0;
    volatile uint32_t cycNum = 0;

    /* 1M=100K*10, so multiple is 10 */
    /* loop function take 4 instructions, so instructionNum is 4 */
    /* divVal = multiple*instructionNum */

    if (core >= 1 * 1000 * 1000) {
        /* CPU clock >= 1MHz */
        speed = core / (100 * 1000);
        cycNum = speed * cnt;
        cycNum = cycNum / 10;
        cycNum = cycNum / divVal;
        /* cycNum >= 0 */
    } else {
        /* CPU clock < 1MHz */
        speed = core / 1000;
        cycNum = speed * cnt;
        cycNum = cycNum / 1000;
        cycNum = cycNum / divVal;
        /* cycNum >= 0 */
    }

    if (!cycNum) {
        return;
    }

    __asm__ __volatile__(
        "mv       a4,%0\n\t"
        "li       a5,0x0\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        ".align 4\n\t"
        "1  :\n"
        "beq      a5,a4,2f\n\t"
        "addi     a5,a5,0x1\n\t"
        "j        1b\n\t"
        "nop\n\t"
        "nop\n\t"
        "2   :\n\t"
        "nop\n"
        :             /* output */
        : "r"(cycNum) /* input */
        : "a4", "a5"  /* destruct description */
    );
}
#endif

/****************************************************************************/ /**
 * @brief      delay us
 *
 * @param[in]  cnt:  delay cnt us
 *
 * @return none
 *
 *******************************************************************************/
__WEAK
void ATTR_TCM_SECTION arch_delay_us(uint32_t cnt)
{
    uint32_t coreFreq;
    uint32_t loopTick = 3;
#if defined(__riscv_xthead) || defined(__riscv_xtheadc)
#if ((__ICACHE_PRESENT == 1U) && (__DCACHE_PRESENT == 1U))
    uint32_t iCacheEn;
    uint32_t dCacheEn;

    /* requirement: icache enable && dcache enable */
    /* otherwise the latency depends on the code address */
    iCacheEn = (__get_MHCR() & CACHE_MHCR_IE_Msk) >> CACHE_MHCR_IE_Pos;
    dCacheEn = (__get_MHCR() & CACHE_MHCR_DE_Msk) >> CACHE_MHCR_DE_Pos;

    if(iCacheEn && dCacheEn){
        loopTick = 3;
    }else if(iCacheEn && !dCacheEn){
        loopTick = 4;
    }else if(!iCacheEn && !dCacheEn){
        loopTick = 24;
    }else{
        /* not recommend */
    }
#endif
#endif

#if defined(DUAL_CORE)
    GLB_CORE_ID_Type coreID;
    coreID = GLB_Get_Core_Type();
    switch (coreID) {
        case GLB_CORE_ID_M0:
#endif
            coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_CLK);
#if defined(DUAL_CORE)
            break;
        default:
            coreFreq = 32 * 1000 * 1000;
            break;
    }
#endif

    coreFreq = coreFreq ? coreFreq : (32 * 1000 * 1000);

    ASM_Delay_Us(coreFreq, cnt, loopTick);
}

/****************************************************************************/ /**
 * @brief      delay ms
 *
 * @param[in]  cnt:  delay cnt ms
 *
 * @return none
 *
 *******************************************************************************/
__WEAK
void ATTR_TCM_SECTION arch_delay_ms(uint32_t cnt)
{
    uint32_t i = 0;
    uint32_t count = 0;

    if (cnt >= 1024) {
        /* delay (n*1024) ms */
        for (i = 0; i < (cnt / 1024); i++) {
            arch_delay_us(1024 * 1000);
        }
    }

    count = cnt & 0x3FF;

    if (count) {
        /* delay (1-1023)ms */
        arch_delay_us(count * 1000);
    }
}

#ifdef DEBUG
/*******************************************************************************
* @brief  Reports the name of the source file and the source line number
*         where the CHECK_PARAM error has occurred.

* @param  file: Pointer to the source file name
* @param  line: assert_param error line source number

* @return None
*******************************************************************************/
void ATTR_TCM_SECTION check_failed(uint8_t *file, uint32_t line)
{
    /* Infinite loop */
    while (1)
        ;
}
#endif /* DEBUG */

/*@} end of group DRIVER_Public_Functions */

/*@} end of group DRIVER_COMMON */

/*@} end of group BL616_Periph_Driver */
