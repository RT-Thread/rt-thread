#include "bl808_common.h"
#include "bl808_glb.h"
#include "bl808_clock.h"

/** @addtogroup  BL808_Periph_Driver
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
#ifndef BFLB_USE_ROM_DRIVER
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
        "lui      a3,0xF0000\n\t"
        "lw       a3,0(a3)\n\t"
        "j        1b\n\t"
        "nop\n\t"
        "nop\n\t"
        "2   :\n\t"
        "nop\n"
        :             /* output */
        : "r"(cycNum) /* input */
        : "a3", "a4", "a5"  /* destruct description */
    );
}
#endif
#endif

/****************************************************************************/ /**
 * @brief      delay us
 *
 * @param[in]  cnt:  delay cnt us
 *
 * @return none
 *
 *******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
const uint32_t ATTR_TCM_CONST_SECTION m0Cyc00[] = {46,46,66,69};
const uint32_t ATTR_TCM_CONST_SECTION m0Cyc10[] = {10,10,66,69};
const uint32_t ATTR_TCM_CONST_SECTION m0Cyc11[] = {10,10,66,69};
const uint32_t ATTR_TCM_CONST_SECTION d0Cyc00[] = { 5, 5,62,34};
const uint32_t ATTR_TCM_CONST_SECTION d0Cyc11[] = { 5, 5,13,13};
const uint32_t ATTR_TCM_CONST_SECTION lpCyc00[] = { 6, 6,55,85};
__WEAK
void ATTR_TCM_SECTION arch_delay_us(uint32_t cnt)
{
    GLB_CORE_ID_Type coreID;
    uint32_t coreFreq;
    uint32_t loopTick = 5;
    const uint32_t *pCyc = NULL;
    uint32_t iCacheEn = 1;
    uint32_t dCacheEn = 1;

    /* requirement: icache enable && dcache enable */
    /* otherwise the latency depends on the code address */

    coreID = GLB_Get_Core_Type();

    if(GLB_CORE_ID_M0 == coreID){
        coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_CLK);
#ifdef __RV32
        iCacheEn = (__get_MHCR() & CLIC_INTIE_IE_Msk) >> CLIC_INTIE_IE_Pos;
        dCacheEn = (__get_MHCR() & CACHE_MHCR_DE_Msk) >> CACHE_MHCR_DE_Pos;
#endif
        if(iCacheEn && dCacheEn){
            pCyc = m0Cyc11;
        }else if(iCacheEn && !dCacheEn){
            pCyc = m0Cyc10;
        }else if(!iCacheEn && !dCacheEn){
            pCyc = m0Cyc00;
        }else{
            pCyc = m0Cyc11;
        }
    }else if(GLB_CORE_ID_D0 == coreID){
        coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_DSP_CLK);
#ifdef __RV64
        iCacheEn = (__get_MHCR() & CACHE_MHCR_IE_Msk) >> CACHE_MHCR_IE_Pos;
        dCacheEn = (__get_MHCR() & CACHE_MHCR_DE_Msk) >> CACHE_MHCR_DE_Pos;
#endif
        if(iCacheEn && dCacheEn){
            pCyc = d0Cyc11;
        }else if(!iCacheEn && !dCacheEn){
            pCyc = d0Cyc00;
        }else{
            pCyc = d0Cyc11;
        }
    }else if(GLB_CORE_ID_LP == coreID){
        coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_LP_CLK);
        pCyc = lpCyc00;
    }else{
        coreFreq = 32 * 1000 * 1000;
        pCyc = lpCyc00;
    }

    switch(((uint32_t)(uintptr_t)&ASM_Delay_Us)>>24){
        case 0x22:
            loopTick = pCyc[0];
            break;
        case 0x62:
            loopTick = pCyc[0];
            break;
        case 0x3F:
            loopTick = pCyc[2];
            break;
        case 0x3E:
            loopTick = pCyc[3];
            break;
        default :
            break;
    }

    coreFreq = coreFreq ? coreFreq : (32 * 1000 * 1000);

    ASM_Delay_Us(coreFreq, cnt, loopTick);
}
#endif

/****************************************************************************/ /**
 * @brief      delay ms
 *
 * @param[in]  cnt:  delay cnt ms
 *
 * @return none
 *
 *******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
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
#endif

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

/****************************************************************************/ /**
 * @brief  MM_Sys All interrupt handler
 *
 * @param  None
 *
 * @return None
 *
 *******************************************************************************/
#if defined(CPU_M0) || defined(CPU_LP)
#ifndef BFLB_USE_HAL_DRIVER
void AWB2_IRQHandler(void);
void UART4_IRQHandler(void);
void UART3_IRQHandler(void);
void I2C2_IRQHandler(void);
void I2C3_IRQHandler(void);
void SPI1_IRQHandler(void);
void AE_IRQHandler(void);
void AWB0_IRQHandler(void);
void SEOF0_IRQHandler(void);
void SEOF1_IRQHandler(void);
void SEOF2_IRQHandler(void);
void CAM0_IRQHandler(void);
void CAM1_IRQHandler(void);
void CAM2_IRQHandler(void);
void CAM3_IRQHandler(void);
void MJPEG_IRQHandler(void);
void DMA2_INT0_IRQHandler(void);
void DMA2_INT1_IRQHandler(void);
void DMA2_INT2_IRQHandler(void);
void DMA2_INT3_IRQHandler(void);
void DMA2_INT4_IRQHandler(void);
void DMA2_INT5_IRQHandler(void);
void DMA2_INT6_IRQHandler(void);
void DMA2_INT7_IRQHandler(void);
void IPC_D0_IRQHandler(void);
void MJDEC_IRQHandler(void);
void CAM4_IRQHandler(void);
void CAM5_IRQHandler(void);
void CAM6_IRQHandler(void);
void CAM7_IRQHandler(void);
void DMA2D_INT0_IRQHandler(void);
void DMA2D_INT1_IRQHandler(void);
void Display_IRQHandler(void);
void PWM_IRQHandler(void);
void SEOF3_IRQHandler(void);
void DBI_IRQHandler(void);
void WDR_IRQHandler(void);
void OSD_PB_IRQHandler(void);
void AWB1_IRQHandler(void);
void DSI_IRQHandler(void);
void AE_HIST_IRQHandler(void);
void TIMER1_CH0_IRQHandler(void);
void TIMER1_CH1_IRQHandler(void);
void TIMER1_WDT_IRQHandler(void);
void AUDIO_IRQHandler(void);



void C906_ALL_IRQHandler(void)
{
    AWB2_IRQHandler();
    UART4_IRQHandler();
    UART3_IRQHandler();
    I2C2_IRQHandler();
    I2C3_IRQHandler();
    SPI1_IRQHandler();
    AE_IRQHandler();
    AWB0_IRQHandler();
    SEOF0_IRQHandler();
    SEOF1_IRQHandler();
    SEOF2_IRQHandler();
    CAM0_IRQHandler();
    CAM1_IRQHandler();
    CAM2_IRQHandler();
    CAM3_IRQHandler();
    MJPEG_IRQHandler();
    DMA2_INT0_IRQHandler();
    DMA2_INT1_IRQHandler();
    DMA2_INT2_IRQHandler();
    DMA2_INT3_IRQHandler();
    DMA2_INT4_IRQHandler();
    DMA2_INT5_IRQHandler();
    DMA2_INT6_IRQHandler();
    DMA2_INT7_IRQHandler();
    IPC_D0_IRQHandler();
    MJDEC_IRQHandler();
    CAM4_IRQHandler();
    CAM5_IRQHandler();
    CAM6_IRQHandler();
    CAM7_IRQHandler();
    DMA2D_INT0_IRQHandler();
    DMA2D_INT1_IRQHandler();
    Display_IRQHandler();
    PWM_IRQHandler();
    SEOF3_IRQHandler();
    DBI_IRQHandler();
    WDR_IRQHandler();
    OSD_PB_IRQHandler();
    AWB1_IRQHandler();
    DSI_IRQHandler();
    AE_HIST_IRQHandler();
    TIMER1_CH0_IRQHandler();
    TIMER1_CH1_IRQHandler();
    TIMER1_WDT_IRQHandler();
    AUDIO_IRQHandler();
}
#endif
#endif

/****************************************************************************/ /**
 * @brief  Enable MM_Sys All interrupt
 *
 * @param  None
 *
 * @return None
 *
 *******************************************************************************/
#if defined(CPU_M0) || defined(CPU_LP)
void C906_All_Int_Enable(void)
{
#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(MM_ALL_IRQn, C906_ALL_IRQHandler);
#endif
    CPU_Interrupt_Enable(MM_ALL_IRQn);
}
#endif

/****************************************************************************/ /**
 * @brief  Dsiable MM_Sys All interrupt
 *
 * @param  None
 *
 * @return None
 *
 *******************************************************************************/
#if defined(CPU_M0) || defined(CPU_LP)
void C906_All_Int_Disable(void)
{
    CPU_Interrupt_Disable(MM_ALL_IRQn);
}
#endif

/*@} end of group DRIVER_Public_Functions */

/*@} end of group DRIVER_COMMON */

/*@} end of group BL808_Periph_Driver */
