/**************************************************************************//**
* @file     cap.c
* @version  V1.00
* @brief    N9H30 CAP driver source file
*
* SPDX-License-Identifier: Apache-2.0
* @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "N9H30.h"
#include "nu_sys.h"
#include "nu_cap.h"

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_CAP_Driver CAP Driver
  @{
*/

/** @addtogroup N9H30_CAP_EXPORTED_FUNCTIONS CAP Exported Functions
  @{
*/

/// @cond HIDDEN_SYMBOLS
PFN_CAP_CALLBACK(pfnCAP_IntHandlerTable)[4] = {0};
/// @endcond HIDDEN_SYMBOLS

/**
 * @brief       CAP interrupt Handler
 *
 * @param       None
 *
 * @return      None
 *
 * @details     Driver internal use API to process the interrupt of CAP
 *              As interrupt occurrence, the register call back function will be executed
 */
static UINT32 u32EscapeFrame = 0;
//static UINT32 g_u32DeviceType = 0;
static void CAP_IntHandler(void)
{
    UINT32 u32CapInt;
    UINT32 uBuf = 0;

    if ((inp32(REG_CLK_HCLKEN) & (0x1 << 26)) == (0x1 << 26)) /* CMOS sensor interface controller clock enabled */
    {
        u32CapInt = inp32(REG_CAP_INT);
        if ((u32CapInt & (VIEN | VINTF)) == (VIEN | VINTF))
        {
            if (pfnCAP_IntHandlerTable[0] != 0)
                pfnCAP_IntHandlerTable[0](uBuf, uBuf, u32EscapeFrame);
            outp32(REG_CAP_INT, (u32CapInt & ~(MDINTF | ADDRMINTF | MEINTF)));    /* Clear Frame end interrupt */
            u32EscapeFrame = u32EscapeFrame + 1;
        }
        else if ((u32CapInt & (ADDRMIEN | ADDRMINTF)) == (ADDRMIEN | ADDRMINTF))
        {
            if (pfnCAP_IntHandlerTable[1] != 0)
                pfnCAP_IntHandlerTable[1](uBuf, uBuf, u32EscapeFrame);
            outp32(REG_CAP_INT, (u32CapInt & ~(MDINTF | VINTF | MEINTF)));      /* Clear Address match interrupt */
        }
        else if ((u32CapInt & (MEIEN | MEINTF)) == (MEIEN | MEINTF))
        {
            if (pfnCAP_IntHandlerTable[2] != 0)
                pfnCAP_IntHandlerTable[2](uBuf, uBuf, u32EscapeFrame);
            outp32(REG_CAP_INT, (u32CapInt & ~(MDINTF | VINTF | ADDRMINTF)));   /* Clear Memory error interrupt */
        }
        else if ((u32CapInt & (MDIEN | MDINTF)) == (MDIEN | MDINTF))
        {
            if (pfnCAP_IntHandlerTable[3] != 0)
                pfnCAP_IntHandlerTable[3](uBuf, uBuf, u32EscapeFrame);
            outp32(REG_CAP_INT, (u32CapInt & ~(VINTF | MEINTF | ADDRMINTF)));       /* Clear Memory error interrupt */
        }
    }
}

/**
 * @brief       Set Inital Frame
 *
 * @return      None
 *
 * @details     If enable interrupt, there is internal counter that records how many frames have pass.
 *              Set the internal counters to zero. The internal counter may be not a constant
 */
void CAP_SetInitFrame(void)
{
    u32EscapeFrame = 0;
}

/**
 * @brief       Get Inital Frame
 *
 * @retval      >0 Internal counters
 *
 * @details     If enable interrupt, there is internal counter that records how many frames have pass.
 *              Get the internal counters. The internal counter may be not a constant
 */
UINT32 CAP_GetSkipFrame(void)
{
    return u32EscapeFrame;
}

/**
 * @brief       CAP Initial
 *
 * @param[in]       bIsEnableSnrClock  Enable/Disable sensor clock
 *                  1 : Enable
 *                  0 : Disable
 * @param[in]       eSnrSrc            Set CAP clock source. Including :
 *                  - \ref   eCAP_SNR_APLL
 *                  - \ref   eCAP_SNR_UPLL
 * @param[in]       u32SensorFreqKHz   Specify the sensor clock
 *
 * @return      None
 *
 * @details     To Initial sensor source clock and frequency for CAP interface
 */
void CAP_Init(BOOL bIsEnableSnrClock, E_CAP_SNR_SRC eSnrSrc, UINT32 u32SensorFreqKHz/*KHz unit*/)
{
    UINT32 u32PllClock, u32SenDiv;// u32ExtFreq;
    UINT32 u32Div0, u32Div1;
    UINT32 u32SenSrc;
    volatile UINT32 u32Divider;

    /* MFP_GPI_L : I3=SEN_CLK0, I4=SEN_PCLK, I5=SEN_HSYNC, I6=SEN_VSYNC, I7=SEN_FIFLD*/
    outpw(REG_SYS_GPI_MFPL, (inpw(REG_SYS_GPI_MFPL) & (0x00000FFF)) | 0x33333000);

    /* MFP_GPI_H : SEN_PDATA[0~7]*/
    outpw(REG_SYS_GPI_MFPH, (inpw(REG_SYS_GPI_MFPH) & (0xFFFFFFFF)) | 0x33333333);

    u32SensorFreqKHz = u32SensorFreqKHz * 1000;
    switch (eSnrSrc)
    {
    case eCAP_SNR_APLL:
        u32PllClock = sysGetClock(SYS_APLL) * 1000000;
        u32SenSrc = 0x2 << 19; //APLL for sensor clock
        break;
    case eCAP_SNR_UPLL:
        u32PllClock = sysGetClock(SYS_UPLL) * 1000000;
        u32SenSrc = 0x3 << 19; //UPLL for sensor clock
        break;
    }


    u32SenDiv = u32PllClock / (u32SensorFreqKHz);
    if (u32PllClock % u32SensorFreqKHz != 0) u32SenDiv = u32SenDiv + 1;
    for (u32Div1 = 1; u32Div1 <= 16; u32Div1 = u32Div1 + 1)
    {
        for (u32Div0 = 1; u32Div0 <= 8; u32Div0 = u32Div0 + 1)
            if (u32SenDiv == u32Div0 * u32Div1)  break;
        if (u32Div0 >= 9)    continue;
        if (u32SenDiv == u32Div0 * u32Div1)  break;
    }
    //sysprintf("Div0 and Div1 = %d, %d ", u32Div0, u32Div1);
    u32Div0 = u32Div0 - 1;
    u32Div1 = u32Div1 - 1;

    if (bIsEnableSnrClock)
    {
        outp32(REG_CLK_HCLKEN, inp32(REG_CLK_HCLKEN) | (1 << 27));          /* CMOS Sensor Reference Clock Output Enable */
        outp32(REG_CLK_HCLKEN, inp32(REG_CLK_HCLKEN) | (1 << 26));          /* CMOS Sensor Interface Controller Clock Enable */
    }
    else
    {
        outp32(REG_CLK_HCLKEN, inp32(REG_CLK_HCLKEN) & ~(1 << 27));           /* CMOS Sensor Reference Clock Output Disabled */
        outp32(REG_CLK_HCLKEN, inp32(REG_CLK_HCLKEN) & ~(1 << 26));           /* CMOS Sensor Interface Controller Clock Disabled */
    }
    u32Divider  = u32SenSrc | ((u32Div0 << 16) | (u32Div1 << 24)) ;
    //sysprintf("Sensor Divider = 0x%08x\n", u32Divider);

    outp32(REG_CLK_DIVCTL3, (inp32(REG_CLK_DIVCTL3) & ~((0x3 << 19) | (0x7 << 16) | (0xF << 24))) | u32Divider);


}

/**
 * @brief       CAP Open
 *
 * @param[in]   u32SensorFreqKHz  Specify the sensor clock
 *
 * @retval      0 Success
 * @retval      <0 Error code
 *
 * @details     Initialize the CAP engine. Register a call back for driver internal using
 */
INT32 CAP_Open(UINT32 u32SensorFreqKHz)
{

    UINT32 u32PllClock;// u32ExtFreq;
    UINT32 u32SenDiv;
    UINT32 u32Div0, u32Div1;
    UINT32 u32SenSrc;
    volatile UINT32 u32Divider;

    u32SensorFreqKHz = u32SensorFreqKHz * 1000;

    outp32(REG_CLK_PMCON, inpw(REG_CLK_PMCON) | (0x1 << 4)) ; /* Sensor clock keep on high level */
    outp32(REG_CLK_HCLKEN, inpw(REG_CLK_HCLKEN) | (0x1 << 26)); /* CMOS sensor interface controller clock enable */
    outp32(REG_SYS_AHBIPRST, inp32(REG_SYS_AHBIPRST) | (1 << 10)); /* Video capture (CMOS sensor interface) reset enable. */
    outp32(REG_SYS_AHBIPRST, inp32(REG_SYS_AHBIPRST) & ~(1 << 10)); /* Video capture (CMOS sensor interface) reset disable */

    switch ((inpw(REG_CLK_DIVCTL3) >> 19) & 0x3)
    {
    case eCAP_SNR_APLL:
        u32PllClock = sysGetClock(SYS_APLL) * 1000000;
        u32SenSrc = 0x2 << 19; //APLL for sensor clock
        break;
    case eCAP_SNR_UPLL:
        u32PllClock = sysGetClock(SYS_UPLL) * 1000000;
        u32SenSrc = 0x3 << 19; //APLL for sensor clock
        break;
    }

    u32SenDiv = u32PllClock / (u32SensorFreqKHz);
    if (u32PllClock % u32SensorFreqKHz != 0)
        u32SenDiv = u32SenDiv + 1;
    for (u32Div1 = 1; u32Div1 <= 16; u32Div1 = u32Div1 + 1)
    {
        for (u32Div0 = 1; u32Div0 <= 8; u32Div0 = u32Div0 + 1)
        {
            if (u32SenDiv == u32Div0 * u32Div1)
                break;
        }
        if (u32Div0 >= 9)    continue;
        if (u32SenDiv == u32Div0 * u32Div1)
            break;
    }
    //sysprintf("Div0 and Div1 = %d, %d ", u32Div0, u32Div1);
    u32Div0 = u32Div0 - 1;
    u32Div1 = u32Div1 - 1;
    u32Divider  = u32SenSrc | ((u32Div0 << 16) | (u32Div1 << 24)) ;
    //sysprintf("Sensor Divider = 0x%08x\n", u32Divider);

    outp32(REG_CLK_DIVCTL3, (inp32(REG_CLK_DIVCTL3) & ~((0x3 << 19) | (0x7 << 16) | (0xF << 24))) | u32Divider);

    sysInstallISR(IRQ_LEVEL_1, CAP_IRQn, (PVOID)CAP_IntHandler);
    sysEnableInterrupt(CAP_IRQn);

    return Successful;
}


/**
 * @brief       videoIn Reset
 *
 * @return      None
 *
 * @details     Capture interface reset.
 */
void CAP_Reset(void)
{
    outp32(REG_CAP_CTL, inp32(REG_CAP_CTL) | (VPRST));
    outp32(REG_CAP_CTL, inp32(REG_CAP_CTL) & (~VPRST));
}

/**
 * @brief       videoIn Close
 *
 * @return      None
 *
 * @details     Disable pin function,engine clock and interrupt
 */
void CAP_Close(void)
{
    // 1. Disable IP's interrupt
    sysDisableInterrupt(CAP_IRQn);
    // 2. Disable IP's clock
    outp32(REG_CLK_HCLKEN, inp32(REG_CLK_HCLKEN) & ~(0x1 << 25));
    CAP_Reset();
    outp32(REG_CLK_HCLKEN, inp32(REG_CLK_HCLKEN) & ~(0x1 << 26));
    // 3. Disable Capture pin function
}

/**
 * @brief       Configure packet frame buffer.
 *
 * @param[in]   bFrameSwitch    Software mode buffer select
 *                              0: Packet buffer 0
 *                              1: Packet buffer 1
 * @return      None
 *
 * @details     This function set packet frame buffer control
 */
void CAP_SetPacketFrameBufferControl(BOOL bFrameSwitch)
{
    UINT32 u32Ctl;
    u32Ctl = inp32(REG_CAP_CTL) & ~(ADDRSW);
    outp32(REG_CAP_CTL, u32Ctl | (bFrameSwitch ? ADDRSW : 0));
}

/**
* @brief        Get packet frame buffer.
 *
 * @param       pbFrameSwitch   Software mode buffer select
 *                              0: Packet buffer 0
 *                              1: Packet buffer 1
 * @return      None
 *
 * @details     This function get packet frame buffer control
 */
void CAP_GetPacketFrameBufferControl(PBOOL pbFrameSwitch)
{
    UINT32 u32Ctl = inp32(REG_CAP_CTL);
    *pbFrameSwitch = (u32Ctl & ADDRSW) >> 3;
}

/**
* @brief        Configure callback function
 *
 * @param[in]   eIntType         Set interrupt type. Including :
 *                               - \ref eCAP_MDINTF
 *                               - \ref eCAP_ADDRMINTF
 *                               - \ref eCAP_MEINTF
 *                               - \ref eCAP_VINTF
 * @param[in]   pfnCallback      Set Callback function.
 *                                The callbakc function :
 *                                  void (*PFN_CAP_CALLBACK)(UINT8 u8PacketBufID,UINT8 u8PlanarBufID, UINT8 u8FrameRate);
 * @param[in]   pfnOldCallback   Set Old callback function
 *                                The callbakc function :
 *                                  void *(*PFN_CAP_CALLBACK)(UINT8 u8PacketBufID,UINT8 u8PlanarBufID, UINT8 u8FrameRate);
 * @retval      0 Success
 * @retval      <0 Error code
 *
 * @details     This function configure callback function and set trigger level
 */
INT32 CAP_InstallCallback(E_CAP_INT_TYPE eIntType, PFN_CAP_CALLBACK pfnCallback, PFN_CAP_CALLBACK *pfnOldCallback)
{
    if (eIntType == eCAP_VINTF)
    {
        *pfnOldCallback = pfnCAP_IntHandlerTable[0];
        pfnCAP_IntHandlerTable[0] = (PFN_CAP_CALLBACK)(pfnCallback);
    }
    else if (eIntType == eCAP_ADDRMINTF)
    {
        *pfnOldCallback = pfnCAP_IntHandlerTable[1];
        pfnCAP_IntHandlerTable[1] = (PFN_CAP_CALLBACK)(pfnCallback);
    }
    else if (eIntType == eCAP_MEINTF)
    {
        *pfnOldCallback = pfnCAP_IntHandlerTable[2];
        pfnCAP_IntHandlerTable[2] = (PFN_CAP_CALLBACK)(pfnCallback);
    }
    else if (eIntType == eCAP_MDINTF)
    {
        *pfnOldCallback = pfnCAP_IntHandlerTable[3];
        pfnCAP_IntHandlerTable[3] = (PFN_CAP_CALLBACK)(pfnCallback);
    }
    else
        return E_CAP_INVALID_INT;
    return Successful;
}

/**
 * @brief       Enable videoIn interrupt.
 *
 * @param[in]   eIntType     Interrupt type. Incuding:
 *                           - \ref eCAP_MDINTF
 *                           - \ref eCAP_ADDRMINTF
 *                           - \ref eCAP_MEINTF
 *                           - \ref eCAP_VINTF
 * @retval      0 Success
 * @retval      <0 Error code
 *
 * @details     This function is used to enable videoIn interrupt.
 */
INT32 CAP_EnableInt(E_CAP_INT_TYPE eIntType)
{
    switch (eIntType)
    {
    case eCAP_MDINTF:
    case eCAP_ADDRMINTF:
    case eCAP_MEINTF:
    case eCAP_VINTF:
        outp32(REG_CAP_INT, inp32(REG_CAP_INT) | eIntType);
        break;
    default:
        return E_CAP_INVALID_INT;
    }
    return Successful;
}

/**
 * @brief       Disable videoIn interrupt
 *
 * @param[in]   eIntType     Interrupt type. Incuding:
 *                           - \ref eCAP_MDINTF
 *                           - \ref eCAP_ADDRMINTF
 *                           - \ref eCAP_MEINTF
 *                           - \ref eCAP_VINTF
 * @retval      0 Success
 * @retval      <0 Error code
 *
 * @details     This function is used to disable videoIn interrupt.
 */
INT32 CAP_DisableInt(E_CAP_INT_TYPE eIntType)
{
    switch (eIntType)
    {
    case eCAP_MDINTF:
    case eCAP_ADDRMINTF:
    case eCAP_MEINTF:
    case eCAP_VINTF:
        outp32(REG_CAP_INT, inp32(REG_CAP_INT) & ~eIntType);
        break;
    default:
        return E_CAP_INVALID_INT;
    }
    return Successful;
}

/**
 * @brief       Check videoIn interrupt
 *
 * @param[in]   eIntType     Interrupt type. Incuding:
 *                           - \ref eCAP_MDINTF
 *                           - \ref eCAP_ADDRMINTF
 *                           - \ref eCAP_MEINTF
 *                           - \ref eCAP_VINTF
 * @retval      1 Enable
 * @retval      0 Disable
 *
 * @details     This function is used to check videoIn interrupt.
 */
BOOL CAP_IsIntEnabled(E_CAP_INT_TYPE eIntType)
{
    UINT32 u32IntEnable = inp32(REG_CAP_INT);
    switch (eIntType)
    {
    case eCAP_MDINTF:
        u32IntEnable = u32IntEnable & eCAP_MDINTF;
        break;
    case eCAP_ADDRMINTF:
        u32IntEnable = u32IntEnable & eCAP_ADDRMINTF;
        break;
    case eCAP_MEINTF:
        u32IntEnable = u32IntEnable & eCAP_MEINTF;
        break;
    case eCAP_VINTF:
        u32IntEnable = u32IntEnable & eCAP_VINTF;
        break;
    }
    return (u32IntEnable ? TRUE : FALSE);
}

/**
 * @brief       Clear videoIn interrupt flag.
 *
 * @param[in]   eIntType    Interrupt type. Incuding:
 *                          - \ref eCAP_MDINTF
 *                          - \ref eCAP_ADDRMINTF
 *                          - \ref eCAP_MEINTF
 *                          - \ref eCAP_VINTF
 * @retval      0 Success
 * @retval      <0 Error code
 *
 * @details     This function is used to clear videoIn interrupt flag.
 */
INT32 CAP_ClearInt(E_CAP_INT_TYPE eIntType)
{
    UINT32 u32IntChannel = eIntType >> 16;
    switch (eIntType)
    {
    case eCAP_MDINTF:
        outp32(REG_CAP_INT, (inp32(REG_CAP_INT) & ~((eCAP_ADDRMINTF | eCAP_MEINTF | eCAP_VINTF) >> 16)) |
               u32IntChannel);
        break;
    case eCAP_ADDRMINTF:
        outp32(REG_CAP_INT, (inp32(REG_CAP_INT) & ~((eCAP_MDINTF | eCAP_MEINTF | eCAP_VINTF) >> 16)) |
               u32IntChannel);
        break;
    case eCAP_MEINTF:
        outp32(REG_CAP_INT, (inp32(REG_CAP_INT) & ~((eCAP_MDINTF | eCAP_ADDRMINTF | eCAP_VINTF) >> 16)) |
               u32IntChannel);
        break;
    case eCAP_VINTF:
        outp32(REG_CAP_INT, (inp32(REG_CAP_INT) & ~((eCAP_MDINTF | eCAP_MEINTF | eCAP_ADDRMINTF) >> 16)) |
               u32IntChannel);
        break;
    default:
        return E_CAP_INVALID_INT;
    }
    return Successful;


}

/**
 * @brief       Polling videoIn interrupt flag.
 *
 * @param[in]   eIntType    Interrupt type. Incuding:
 *                          - \ref eCAP_MDINTF
 *                          - \ref eCAP_ADDRMINTF
 *                          - \ref eCAP_MEINTF
 *                          - \ref eCAP_VINTF
 * @retval      0 Success
 * @retval      <0 Error code
 *
 * @details     This function is used to poll videoIn interrupt flag.
 */
BOOL CAP_PollInt(E_CAP_INT_TYPE eIntType)
{
    UINT32 u32IntStatus = inp32(REG_CAP_INT);
    switch (eIntType)
    {
    case eCAP_MDINTF:
        u32IntStatus = u32IntStatus & (eCAP_MDINTF >> 16);
        break;
    case eCAP_ADDRMINTF:
        u32IntStatus = u32IntStatus & (eCAP_ADDRMINTF >> 16);
        break;
    case eCAP_MEINTF:
        u32IntStatus = u32IntStatus & (eCAP_MEINTF >> 16);
        break;
    case eCAP_VINTF:
        u32IntStatus = u32IntStatus & (eCAP_VINTF >> 16);
        break;
    }
    return (u32IntStatus ? TRUE : FALSE);
}

/**
 * @brief       Enable engine clock and turn on the pipe.
 *
 * @param[in]   bEngEnable      Enable engine clock.
 *                              1 : Enable engine clock.
 *                              0 : Disable engine clock.
 * @param[in]   ePipeEnable     Enable pipe type. Incuding:
 *                              - \ref eCAP_BOTH_PIPE_DISABLE
 *                              - \ref eCAP_PLANAR
 *                              - \ref eCAP_PACKET
 *                              - \ref eCAP_BOTH_PIPE_ENABLE
 * @retval      0 Success
 * @retval      <0 Error code
 *
 * @details     This function is used to enable engine clock and pipe type.
 */
void CAP_SetPipeEnable(
    BOOL bEngEnable,
    E_CAP_PIPE ePipeEnable
)
{
    outp32(REG_CAP_CTL, (inp32(REG_CAP_CTL) & ~(CAPEN | PKTEN | PLNEN))
           | (((bEngEnable ? CAPEN : 0x0))
              // | ((ePipeEnable & ~(PKTEN | PLNEN))<<5)) );
              | ((ePipeEnable & 0x03) << 5)));
} // DrvVideoIn_SetPipeEnable

/**
 * @brief       Get engine clock and pipe type.
 *
 * @param[out]  pbEngEnable     Enable engine clock.
 *                              1 : Enable engine clock.
 *                              0 : Disable engine clock.
 * @param[out]  pePipeEnable    Pipe type. Incuding:
 *                              - \ref eCAP_BOTH_PIPE_DISABLE
 *                              - \ref eCAP_PLANAR
 *                              - \ref eCAP_PACKET
 *                              - \ref eCAP_BOTH_PIPE_ENABLE
 * @return      None
 *
 * @details     This function is used to get engin clock and pipe type.
 */
void CAP_GetPipeEnable(PBOOL pbEngEnable, E_CAP_PIPE *pePipeEnable)
{
    UINT32 u32Temp = inp32(REG_CAP_CTL);

    *pbEngEnable = (u32Temp & CAPEN) ? TRUE : FALSE;
    *pePipeEnable = (E_CAP_PIPE)((u32Temp & (PKTEN | PLNEN)) >> 5);
} // DrvVideoIn_GetPipeEnable


/**
 * @brief       Set Shadow(Update) Register
 *
 * @details     This function is used to reload frame buffer address after
 *              setting shoaw(update) register.
 */
void CAP_SetShadowRegister(void)
{
    outp32(REG_CAP_CTL,  inp32(REG_CAP_CTL) | UPDATE);
} // DrvVideoIn_SetShadowRegister


/**
 * @brief      Set sensor polarity.
 *
 * @param[in]   bVsync     Sensor Vsync Polarity.
 *                         1  : High Active
 *                         0  : Low Active
 * @param[in]   bHsync     Sensor Hsync Polarity.
 *                         1  : High Active
 *                         0  : Low Active
 * @param[in]   bPixelClk  Sensor Vsync Polarity.
 *                         1  : Falling Edge
 *                         0  : Rising Edig
 * @return       None
 *
 * @details     This function is used to set sensor polarity.
 */
void CAP_SetSensorPolarity(BOOL bVsync, BOOL bHsync, BOOL bPixelClk)
{
    UINT32 u32Polarity, u32RegVal;
    u32RegVal = inp32(REG_CAP_PAR);
    //sysprintf("Enter Register addr = 0x%x\n", (REG_CAP_PAR));
    //sysprintf("Enter Register value = 0x%x\n", u32RegVal);
    u32Polarity = (((bVsync ? VSP : 0x0) | (bHsync ? HSP : 0x0)) | (bPixelClk ? PCLKP : 0x0));
    u32RegVal = (inp32(REG_CAP_PAR) & ~(VSP | HSP | PCLKP)) ;
    //sysprintf("REG_VPEPAR = 0x%x", (u32RegVal | u32Polarity));
    outp32((REG_CAP_PAR), (u32RegVal | u32Polarity));
}

/**
 * @brief      Get sensor polarity.
 *
 * @param[out]   pbVsync     Sensor Vsync Polarity.
 *                           1  : High Active
 *                           0  : Low Active
 * @param[out]   pbHsync     Sensor Hsync Polarity.
 *                           1  : High Active
 *                           0  : Low Active
 * @param[out]   pbPixelClk  Sensor Vsync Polarity.
 *                           1  : Falling Edge
 *                           0  : Rising Edig
 * @return       None
 *
 * @details     This function is used to get sensor polarity.
 */
void CAP_GetSensorPolarity(PBOOL pbVsync, PBOOL pbHsync, PBOOL pbPixelClk)
{
    UINT32 u32Temp = inp32(REG_CAP_PAR);

    *pbVsync = (u32Temp & VSP)  ? TRUE : FALSE;
    *pbHsync = (u32Temp & HSP) ? TRUE : FALSE;
    *pbPixelClk = (u32Temp & PCLKP) ? TRUE : FALSE;
}

/**
 * @brief      Set data format and order.
 *
 * @param[in]   eInputOrder     Data order for input format.Including :
 *                              - \ref eCAP_IN_UYVY = Y0 U0 Y1 V0
 *                              - \ref eCAP_IN_YUYV = Y0 V0 Y1 U0
 *                              - \ref eCAP_IN_VYUY = U0 Y0 V0 Y1
 *                              - \ref eCAP_IN_YVYU = V0 Y0 U0 Y1
 * @param[in]   eInputFormat    Input data format.Including :
 *                              - \ref eCAP_IN_YUV422
 *                              - \ref eCAP_IN_RGB565
 * @param[in]   eOutputFormat   Sensor Vsync Polarity.Including :
 *                              - \ref eCAP_OUT_YUV422 = YCbCr422
 *                              - \ref eCAP_OUT_ONLY_Y = only output Y
 *                              - \ref eCAP_OUT_RGB555 = rgb555
 *                              - \ref eCAP_OUT_RGB565 = rgb565
 * @return      None
 *
 * @details     This function is used to set data format and order.
 */
void CAP_SetDataFormatAndOrder(E_CAP_ORDER eInputOrder, E_CAP_IN_FORMAT eInputFormat, E_CAP_OUT_FORMAT eOutputFormat)
{
    outp32((REG_CAP_PAR), (inp32(REG_CAP_PAR) & ~(OUTFMT | INDATORD | INFMT))
           | ((((eInputOrder << 2) & INDATORD)
               | (eInputFormat & INFMT))
              | ((eOutputFormat << 4) & OUTFMT)));
} // DrvVideoIn_SetDataFormatAndOrder

/**
 * @brief      Get data format and order.
 *
 * @param[out]   peInputOrder    Data order for input format.Including :
 *                               - \ref eCAP_IN_UYVY
 *                               - \ref eCAP_IN_YUYV
 *                               - \ref eCAP_IN_VYUY
 *                               - \ref eCAP_IN_YVYU
 * @param[out]   peInputFormat   Input data format.Including :
 *                               - \ref eCAP_IN_YUV422
 *                               - \ref eCAP_IN_RGB565
 * @param[out]   peOutputFormat  Sensor Vsync Polarity.Including :
 *                               - \ref eCAP_OUT_YUV422 = YCbCr422
 *                               - \ref eCAP_OUT_ONLY_Y = only output Y
 *                               - \ref eCAP_OUT_RGB555 = rgb555
 *                               - \ref eCAP_OUT_RGB565 = rgb565
 * @return      None
 *
 * @details     This function is used to get data format and order.
 */
void CAP_GetDataFormatAndOrder(E_CAP_ORDER *peInputOrder, E_CAP_IN_FORMAT *peInputFormat, E_CAP_OUT_FORMAT *peOutputFormat)
{
    UINT32 u32Temp = inp32(REG_CAP_PAR);

    *peInputOrder = (E_CAP_ORDER)((u32Temp & INDATORD) >> 2);
    *peInputFormat = (E_CAP_IN_FORMAT)(u32Temp & INFMT);
    *peOutputFormat = (E_CAP_OUT_FORMAT)((u32Temp & OUTFMT) >> 4);
}

/**
 * @brief      Set planar format.
 *
 * @param[in]   ePlanarFmt     Data order for input format.Including :
 *                              - \ref eCAP_PLANAR_YUV422
 *                              - \ref eCAP_PLANAR_YUV420
 * @return      None
 *
 * @details     This function is used to set planar format.
 */
void CAP_SetPlanarFormat(E_CAP_PLANAR_FORMAT ePlanarFmt)
{
    switch (ePlanarFmt)
    {
    case eCAP_PLANAR_YUV422:
        outp32((REG_CAP_PAR), (inp32(REG_CAP_PAR) & ~(PLNFMT)));
        break;
    case eCAP_PLANAR_YUV420:
        outp32((REG_CAP_PAR), ((inp32(REG_CAP_PAR) | (PLNFMT))));
        break;
    }
}

/**
 * @brief      Get planar format.
 *
 * @retval      - \ref eCAP_PLANAR_YUV422 : Planar format is YUV420.
 * @retval      - \ref eCAP_PLANAR_YUV420 : Planar format is YUV422.
 *
 * @details     This function is used to get planar format.
 */
BOOL CAP_GetPlanarFormat(void)
{
    return ((inp32(REG_CAP_PAR) & PLNFMT) >> 7);
}

/**
 * @brief      Set motion detection parameter.
 *
 * @param[in]   bEnable      Enable Motion Detection.Including :
 *                           0  : Disable motion detection.
 *                           1  : Enable motion detection.
 * @param[in]   bBlockSize   Motion Detection Block Size.Including :
 *                           0  : Block size is set to 16x16.
 *                           1  : Block size is set to 8x8.
 * @param[in]   bSaveMode    Motion Detection Save Mode.Including :
 *                           0  : 1 bit DIFF + 7 Y Differential.
 *                           1  : 1 bit DIFF only.
 * @return      None
 *
 * @details     This function is used to set motion detection parameter.
 */
void CAP_SetMotionDet(BOOL bEnable, BOOL bBlockSize, BOOL bSaveMode)
{
    outp32(REG_CAP_MD, (inp32(REG_CAP_MD) & ~(MDSM | MDBS | MDEN)) |
           (((bEnable ? MDEN : 0) | (bBlockSize ? MDBS : 0)) |
            (bSaveMode ? MDSM : 0)));
}

/**
 * @brief      Get motion detection parameter.
 *
 * @param[out]   pbEnable      Enable Motion Detection.Including :
 *                             0  : Disable motion detection.
 *                             1  : Enable motion detection.
 * @param[out]   pbBlockSize   Motion Detection Block Size.Including :
 *                             0  : Block size is set to 16x16.
 *                             1  : Block size is set to 8x8.
 * @param[out]   pbSaveMode    Motion Detection Save Mode.Including :
 *                             0  : 1 bit DIFF + 7 Y Differential.
 *                             1  : 1 bit DIFF only.
 * @return       None
 *
 * @details      This function is used to get motion detection parameter.
 */
void CAP_GetMotionDet(PBOOL pbEnable, PBOOL pbBlockSize, PBOOL pbSaveMode)
{
    UINT32 u32RegData = inp32(REG_CAP_MD);
    *pbEnable = (u32RegData & MDEN);
    *pbBlockSize = (u32RegData & MDBS) >> 8;
    *pbSaveMode = (u32RegData & MDSM) >> 9;
}

/**
 * @brief      Set motion detection parameter externtion.
 *
 * @param[in]   u32DetFreq        Motion Detection frequency.Including :
 *                                0 : Each frame
 *                                1 : Every 2 frame
 *                                2 : Every 3 frame
 *                                3 : Every 4 frame
 * @param[in]   u32Threshold      Motion detection threshold.It should be 0~31.
 *
 * @param[in]   u32OutBuffer      Motion Detection Output Address Register.(Word Alignment)
 *
 * @param[in]   u32LumBuffer      Motion Detection Temp Y Output Address Register.(Word Alignment)
 *
 * @return       None
 *
 * @details      This function is used to set motion detection parameter externtion.
 */
void CAP_SetMotionDetEx(UINT32 u32DetFreq, UINT32 u32Threshold, UINT32 u32OutBuffer, UINT32 u32LumBuffer)
{
    outp32(REG_CAP_MD, (inp32(REG_CAP_MD) & ~MDDF) | ((u32DetFreq << 10) & MDDF));
    outp32(REG_CAP_MD, (inp32(REG_CAP_MD) & ~MDTHR) | ((u32Threshold << 16) & MDTHR));
    outp32(REG_CAP_MDADDR, u32OutBuffer);
    outp32(REG_CAP_MDYADDR, u32LumBuffer);
}

/**
 * @brief      Get motion detection parameter externtion.
 *
 * @param[out]   pu32DetFreq        Motion Detection frequency.Including :
 *                                  0 : Each frame
 *                                  1 : Every 2 frame
 *                                  2 : Every 3 frame
 *                                  3 : Every 4 frame
 * @param[out]   pu32Threshold      Motion detection threshold.It should be 0~31.
 *
 * @param[out]   pu32OutBuffer      Motion Detection Output Address Register.(Word Alignment)
 *
 * @param[out]   pu32LumBuffer      Motion Detection Temp Y Output Address Register.(Word Alignment)
 *
 * @return       None
 *
 * @details      This function is used to get motion detection parameter externtion.
 */
void CAP_GetMotionDetEx(PUINT32 pu32DetFreq, PUINT32 pu32Threshold, PUINT32 pu32OutBuffer, PUINT32 pu32LumBuffer)
{
    UINT32 u32RegData;
    u32RegData = inp32(REG_CAP_MD);
    *pu32DetFreq = u32RegData & MDDF;
    *pu32Threshold = u32RegData & MDTHR;
    *pu32OutBuffer = inp32(REG_CAP_MDADDR);
    *pu32LumBuffer = inp32(REG_CAP_MDYADDR);
}

/**
 * @brief      Set motion detection frequency.
 *
 * @param[in]  u32DetFreq        Motion Detection frequency.Including :
 *                               0 : Each frame
 *                               1 : Every 2 frame
 *                               2 : Every 3 frame
 *                               3 : Every 4 frame
 * @return     None
 *
 * @details    This function is used to set motion detection frequency.
 */
void CAP_SetMotionDetFreq(UINT32 u32DetFreq)
{
    outp32(REG_CAP_MD, (inp32(REG_CAP_MD) & ~MDDF) |
           ((u32DetFreq << 10) & MDDF));
}

/**
 * @brief      Get motion detection frequency.
 *
 * @param[out]  pu32DetFreq      Motion Detection frequency.Including :
 *                               0 : Each frame
 *                               1 : Every 2 frame
 *                               2 : Every 3 frame
 *                               3 : Every 4 frame
 * @return     None
 *
 * @details    This function is used to get motion detection frequency.
 */
void CAP_GetMotionDetFreq(PUINT32 pu32DetFreq)
{
    UINT32 u32RegData;
    u32RegData = inp32(REG_CAP_MD);
    *pu32DetFreq = u32RegData & MDDF;
}

/**
 * @brief      Set One shutte or continuous mode.
 *
 * @param[in]  bIsOneSutterMode      Enable One shutte.Including :
 *                                   1 :  Enable  One shutte mode.
 *                                   0 : Disable One shutte mode.
 * @return     None
 *
 * @details    This function is used to set one shutte or continuous mode.
 *             Image capture interface automatically disable the capture
 *             inteface after a frame bad been captured.
 */
void CAP_SetOperationMode(BOOL bIsOneSutterMode)
{
    outp32(REG_CAP_CTL, (inp32(REG_CAP_CTL) & ~SHUTTER) |
           ((bIsOneSutterMode << 16) & SHUTTER));
} // DrvVideoIn_SetOperationMode

/**
 * @brief      Get One shutte or continuous mode.
 *
 * @retval     1 : Disable one shutte mode
 * @retval     0 : Enable one shutte mode
 *
 * @details    This function is used to get one shutte or continuous mode.
 *             Image capture interface automatically disable the capture
 *             inteface after a frame bad been captured.
 */
BOOL CAP_GetOperationMode(void)
{
    return ((inp32(REG_CAP_CTL) & SHUTTER) ? TRUE : FALSE);
} // DrvVideoIn_GetOperationMode


/**
 * @brief        Get packet/planar processed data count.
 *
 * @param[in]    ePipe  Pipe type. Including :
 *               - \ref eCAP_PACKET
 *               - \ref eCAP_PLANAR
 *
 * @return       Get current packet/planar processed data count.
 *
 * @details    This function is used to get packet/planar processed data count.
 */
UINT32 CAP_GetProcessedDataCount(E_CAP_PIPE ePipe)
{
    if (ePipe == eCAP_PACKET)
        return inp32(REG_CAP_CURADDRP);       /* Packet pipe */
    else if (ePipe == eCAP_PLANAR)
        return inp32(REG_CAP_CURADDRY);       /* Planar pipe */
    else
        return 0;
}


/**
 * @brief        Set cropping window vertical/horizontal starting address.
 *
 * @param[in]    u32VerticalStart   Cropping window vertical starting address.
 * @param[in]    u32HorizontalStart Cropping window horizontal starting address.
 *
 * @return       None.
 *
 * @details    This function is used to set cropping window vertical/horizontal starting address.
 */
void CAP_SetCropWinStartAddr(UINT32 u32VerticalStart, UINT32 u32HorizontalStart)
{
    outp32(REG_CAP_CWSP, (inp32(REG_CAP_CWSP) & ~(CWSADDRV | CWSADDRH)) //(Y|X)
           | ((u32VerticalStart << 16)
              | u32HorizontalStart));
}


/**
 * @brief        Get cropping window vertical/horizontal starting address.
 *
 * @param[out]   pu32VerticalStart   Cropping window vertical starting address.
 * @param[out]   pu32HorizontalStart Cropping window horizontal starting address.
 *
 * @return       None.
 *
 * @details    This function is used to get cropping window vertical/horizontal starting address.
 */
void CAP_GetCropWinStartAddr(PUINT32 pu32VerticalStart, PUINT32 pu32HorizontalStart)
{
    UINT32 u32Temp = inp32(REG_CAP_CWSP);

    *pu32VerticalStart = (u32Temp & CWSADDRV) >> 16;
    *pu32HorizontalStart = u32Temp & CWSADDRH;
}

/**
 * @brief        Set cropping window size.
 *
 * @param[in]    u32Width   Cropping window width.
 * @param[in]    u32Height  Cropping window heigh.
 *
 * @return       None.
 *
 * @details    This function is used to set cropping window size.
 */
void CAP_SetCropWinSize(UINT32 u32Height, UINT32 u32Width)
{
    outp32(REG_CAP_CWS, (inp32(REG_CAP_CWS) & ~(CWH | CWW))
           | ((u32Height << 16)
              | u32Width));
}


/**
 * @brief        Get cropping window size.
 *
 * @param[out]   pu32Width   Cropping window width.
 * @param[out]   pu32Height  Cropping window heigh.
 *
 * @return       None.
 *
 * @details    This function is used to get cropping window size.
 */
void CAP_GetCropWinSize(PUINT32 pu32Height, PUINT32 pu32Width)
{
    UINT32 u32Temp = inp32(REG_CAP_CWS);

    *pu32Height = (u32Temp & CWH) >> 16;
    *pu32Width = u32Temp & CWW;
}

/**
 * @brief       Set packet/planar scaling vertical factor.
 *
 * @param[in]   ePipe   Pipe type.Including.
 *                      - \ref eCAP_PACKET.
 *                      - \ref eCAP_PLANAR.
 * @param[in]   u16Numerator  Scaling Vertical Factor N.
 * @param[in]   u16Denominator  Scaling Vertical Factor M.
 *
 * @retval      0 Success
 * @retval      <0 Error code
 *
 * @details     This function is used to set packet/planar scaling vertical factor.
 *              The output image width will be equal to the image width * N/M.
 *              Note: The value of N must be equal to or less than M
 */
INT32 CAP_SetVerticalScaleFactor(E_CAP_PIPE ePipe, UINT16 u16Numerator, UINT16 u16Denominator)
{
    UINT8 u8NumeratorL = u16Numerator & 0xFF, u8NumeratorH = u16Numerator >> 8;
    UINT8 u8DenominatorL = u16Denominator & 0xFF, u8DenominatorH = u16Denominator >> 8;
    if (ePipe == eCAP_PACKET)
    {
        outp32(REG_CAP_PKTSL, (inp32(REG_CAP_PKTSL) & ~(PKTSVNL | PKTSVML))
               | ((u8NumeratorL << 24)
                  | (u8DenominatorL << 16)));
        outp32(REG_CAP_PKTSM, (inp32(REG_CAP_PKTSM) & ~(PKTSHMH | PKTSVMH))
               | ((u8NumeratorH << 24)
                  | (u8DenominatorH << 16)));
    }
    else if (ePipe == eCAP_PLANAR)
    {
        outp32(REG_CAP_PLNSL, (inp32(REG_CAP_PLNSL) & ~(PKTSVNL | PKTSVML))
               | ((u8NumeratorL << 24)
                  | (u8DenominatorL << 16)));
        outp32(REG_CAP_PLNSM, (inp32(REG_CAP_PLNSM) & ~(PKTSHMH | PKTSVMH))
               | ((u8NumeratorH << 24)
                  | (u8DenominatorH << 16)));
    }
    else
        return E_CAP_INVALID_PIPE;
    return Successful;
}

/**
 * @brief       Get packet/planar scaling vertical factor.
 *
 * @param[in]   ePipe   Pipe type.Including.
 *                      - \ref eCAP_PACKET.
 *                      - \ref eCAP_PLANAR.
 * @param[out]  pu16Numerator  Scaling Vertical Factor N.
 * @param[out]  pu16Denominator  Scaling Vertical Factor M.
 *
 * @retval      0 Success
 * @retval      <0 Error code
 *
 * @details     This function is used to get packet/planar scaling vertical factor.
 *              The output image width will be equal to the image width * N/M.
 *              Note: The value of N must be equal to or less than M
 */
INT32 DrvCAP_GetVerticalScaleFactor(E_CAP_PIPE ePipe, PUINT16 pu16Numerator, PUINT16 pu16Denominator)
{
    UINT32 u32Temp1, u32Temp2;
    if (ePipe == eCAP_PACKET)
    {
        u32Temp1 = inp32(REG_CAP_PKTSL);
        u32Temp2 = inp32(REG_CAP_PKTSM);
    }
    else if (ePipe == eCAP_PLANAR)
    {
        u32Temp1 = inp32(REG_CAP_PLNSL);
        u32Temp2 = inp32(REG_CAP_PLNSM);
    }
    else
        return E_CAP_INVALID_PIPE;
    *pu16Numerator = ((u32Temp1 & PKTSVNL) >> 24) | (((u32Temp2 & PKTSHMH) >> 24) << 8);
    *pu16Denominator = (u32Temp1 & PKTSVML) >> 16 | (((u32Temp2 & PKTSVMH) >> 16) << 8);
    return Successful;
}

/**
 * @brief       Set packet/planar scaling horizontal factor.
 *
 * @param[in]   bPipe   Pipe type.Including.
 *                      - \ref eCAP_PACKET.
 *                      - \ref eCAP_PLANAR.
 * @param[in]   u16Numerator  Scaling Horizontal Factor N.
 * @param[in]   u16Denominator  Scaling Horizontal Factor M.
 *
 * @retval      0 Success
 * @retval      <0 Error code
 *
 * @details     This function is used to set packet/planar scaling horizontal factor.
 *              The output image width will be equal to the image width * N/M.
 *              Note: The value of N must be equal to or less than M
 */
INT32 CAP_SetHorizontalScaleFactor(E_CAP_PIPE bPipe, UINT16 u16Numerator, UINT16 u16Denominator)
{
    UINT8 u8NumeratorL = u16Numerator & 0xFF, u8NumeratorH = u16Numerator >> 8;
    UINT8 u8DenominatorL = u16Denominator & 0xFF, u8DenominatorH = u16Denominator >> 8;
    if (bPipe == eCAP_PACKET)
    {
        outp32(REG_CAP_PKTSL, (inp32(REG_CAP_PKTSL) & ~(PKTSHNL | PKTSHML))
               | ((u8NumeratorL << 8)
                  | u8DenominatorL));
        outp32(REG_CAP_PKTSM, (inp32(REG_CAP_PKTSM) & ~(PKTSHNH | PKTSHMH))
               | ((u8NumeratorH << 8)
                  | u8DenominatorH));
    }
    else  if (bPipe == eCAP_PLANAR)
    {
        outp32(REG_CAP_PLNSL, (inp32(REG_CAP_PLNSL) & ~(PKTSHNL | PKTSHML))
               | ((u8NumeratorL << 8)
                  | u8DenominatorL));
        outp32(REG_CAP_PLNSM, (inp32(REG_CAP_PLNSM) & ~(PKTSHNH | PKTSHMH))
               | ((u8NumeratorH << 8)
                  | u8DenominatorH));
    }
    else
        return E_CAP_INVALID_PIPE;
    return Successful;
}

/**
 * @brief       Get packet/planar scaling horizontal factor.
 *
 * @param[in]   bPipe   Pipe type.Including.
 *                      - \ref eCAP_PACKET.
 *                      - \ref eCAP_PLANAR.
 * @param[out]  pu16Numerator  Scaling Horizontal Factor N.
 * @param[out]  pu16Denominator  Scaling Horizontal Factor M.
 *
 * @retval      0 Success
 * @retval      <0 Error code
 *
 * @details     This function is used to get packet/planar scaling horizontal factor.
 *              The output image width will be equal to the image width * N/M.
 *              Note: The value of N must be equal to or less than M.
 */
INT32 CAP_GetHorizontalScaleFactor(E_CAP_PIPE bPipe, PUINT16 pu16Numerator, PUINT16 pu16Denominator)
{
    UINT32 u32Temp1, u32Temp2;
    if (bPipe == eCAP_PACKET)
    {
        u32Temp1 = inp32(REG_CAP_PKTSL);
        u32Temp2 = inp32(REG_CAP_PKTSM);
    }
    else  if (bPipe == eCAP_PLANAR)
    {
        u32Temp1 = inp32(REG_CAP_PLNSL);
        u32Temp2 = inp32(REG_CAP_PLNSM);
    }
    else
        return E_CAP_INVALID_PIPE;
    *pu16Numerator = ((u32Temp1 & PKTSHNL) >> 8) | (u32Temp2 & PKTSHNH);
    *pu16Denominator = (u32Temp1 & PKTSHML) | ((u32Temp2 & PKTSHMH) << 8);
    return Successful;
}

/**
 * @brief      Set scaling frame rate factor.
 *
 * @param[in]  u8Numerator  Scaling Frame Rate Factor N.
 * @param[in]  u8Denominator  Scaling Frame Rate Factor M.
 *
 * @return     None.
 *
 * @details    This function is used to set scaling frame rate factor..
 *             The output image frame rate will be equal to input image frame rate * (N/M).
 *             Note: The value of N must be equal to or less than M.
 */
void DrvCAP_SetFrameRateScaleFactor(UINT8 u8Numerator, UINT8 u8Denominator)
{
    outp32(REG_CAP_FRCTL, (inp32(REG_CAP_FRCTL) & ~(FRN | FRM))
           | (((u8Numerator << 8) & FRN)
              | (u8Denominator & FRM)));
} // DrvVideoIn_SetFrameRateScaleFactor

/**
 * @brief      Get scaling frame rate factor.
 *
 * @param[out] pu8Numerator  Scaling Frame Rate Factor N.
 * @param[out] pu8Denominator  Scaling Frame Rate Factor M.
 *
 * @return     None.
 *
 * @details    This function is used to get scaling frame rate factor..
 *             The output image frame rate will be equal to input image frame rate * (N/M).
 *             Note: The value of N must be equal to or less than M.
 */
void DrvCAP_GetFrameRateScaleFactor(PUINT8 pu8Numerator, PUINT8 pu8Denominator)
{
    UINT32 u32Temp = inp32(REG_CAP_FRCTL);

    *pu8Numerator = (u32Temp & FRN) >> 8;
    *pu8Denominator = u32Temp & FRM;
}

/**
 * @brief      Set address match
 *
 * @param[in]  u32AddressMatch  Compare Memory Base Address.It should be 0~0xFFFFFFFF.
 *
 * @return     None.
 *
 * @details    This function is used to set compare memory base address.
 */
void DrvCAP_SetAddressMatch(UINT32 u32AddressMatch)
{
    outp32(REG_CAP_CMPADDR, u32AddressMatch);
}

/**
 * @brief      Get address match
 *
 * @param[out] pu32AddressMatch  Compare Memory Base Address.It should be 0~0xFFFFFFFF.
 *
 * @return     None.
 *
 * @details    This function is used to get compare memory base address.
 */
void CAP_GetAddressMatch(PUINT32 pu32AddressMatch)
{
    *pu32AddressMatch = inp32(REG_CAP_CMPADDR);
}

/**
 * @brief      Set frame output pixel stride width.
 *
 * @param[in] u32PacketStride  Packet frame output pixel stride width.It should be 0~0x3FFF.
 * @param[in] u32PlanarStride  Planar frame output pixel stride width.It should be 0~0x3FFF.
 *
 * @return     None.
 *
 * @details    This function is used to set frame output pixel stride width.
 */
void CAP_SetStride(UINT32 u32PacketStride, UINT32 u32PlanarStride)
{
    outp32(REG_CAP_STRIDE, ((u32PlanarStride << 16) & PLNSTRIDE) |
           (u32PacketStride & PKTSTRIDE));
}

/**
 * @brief      Get frame output pixel stride width.
 *
 * @param[out] pu32PacketStride  Packet frame output pixel stride width.It should be 0~0x3FFF.
 * @param[out] pu32PlanarStride  Planar frame output pixel stride width.It should be 0~0x3FFF.
 *
 * @return     None.
 *
 * @details    This function is used to get frame output pixel stride width.
 */
void CAP_GetStride(PUINT32  pu32PacketStride, PUINT32 pu32PlanarStride)
{
    UINT32 u32Tmp =  inp32(REG_CAP_STRIDE);
    *pu32PlanarStride = (u32Tmp & PLNSTRIDE) >> 16;
    *pu32PacketStride = u32Tmp & PKTSTRIDE;
}

/**
 * @brief      Set system memory packet/planar base address.
 *
 * @param[in] ePipe             Pipe type.Including:
 *                              - \ref eCAP_PACKET
 *                              - \ref eCAP_PLANAR
 *
 * @param[in] eBuf              Packet/Planar buffer address.
 *                              - \ref eCAP_BUF0 :
 *                                     Packet : Packet base address 0
 *                                     Planar : Planar Y base address
 *                              - \ref eCAP_BUF1
 *                                     Packet : Packet base address 1
 *                                     Planar : Planar U base address
 *                              - \ref eCAP_BUF2
 *                                     Packet : None.
 *                                     Planar : Planar V base address
 *
 * @param[in] u32BaseStartAddr  System Memory Base Address.It should be 0~0xFFFFFFFF.
 *
 * @retval      0 Success
 * @retval      <0 Error code
 *
 * @details    This function is used to set system memory packet/planar base address.
 */
INT32 CAP_SetBaseStartAddress(E_CAP_PIPE ePipe, E_CAP_BUFFER eBuf, UINT32 u32BaseStartAddr)
{
    if (ePipe == eCAP_PACKET)
    {
        if (eBuf > eCAP_BUF1)
            return E_CAP_INVALID_BUF;
        outp32(REG_CAP_PKTBA0 + eBuf * 4, u32BaseStartAddr);
    }
    else if (ePipe == eCAP_PLANAR)
    {
        if (eBuf > eCAP_BUF2)
            return E_CAP_INVALID_BUF;
        outp32(REG_CAP_YBA + eBuf * 4, u32BaseStartAddr);
    }
    else
        return E_CAP_INVALID_PIPE;
    return Successful;
}

/**
 * @brief      Get system memory packet/planar base address.
 *
 * @param[in]  ePipe              Pipe type.Including:
 *                                - \ref eCAP_PACKET
 *                                - \ref eCAP_PLANAR
 *
 * @param[in]  eBuf               Packet/Planar buffer address.
 *                                - \ref eCAP_BUF0 :
 *                                     Packet : Packet base address 0
 *                                     Planar : Planar Y base address
 *                                - \ref eCAP_BUF1
 *                                     Packet : Packet base address 1
 *                                     Planar : Planar U base address
 *                                - \ref eCAP_BUF2
 *                                     Packet : None.
 *                                     Planar : Planar V base address
 *
 * @param[out] pu32BaseStartAddr  System Memory Base Address.It should be 0~0xFFFFFFFF.
 *
 * @retval     0 Success
 * @retval     <0 Error code
 *
 * @details    This function is used to get system memory packet/planar base address.
 */
INT32 CAP_GetBaseStartAddress(E_CAP_PIPE ePipe, E_CAP_BUFFER eBuf, PUINT32 pu32BaseStartAddr)
{
    if (ePipe == eCAP_PACKET)
    {
        if (eBuf > eCAP_BUF1)
            return E_CAP_INVALID_BUF;
        *pu32BaseStartAddr = inp32(REG_CAP_PKTBA0 + eBuf * 4);
    }
    else if (ePipe == eCAP_PLANAR)
    {
        if (eBuf > eCAP_BUF2)
            return E_CAP_INVALID_BUF;
        *pu32BaseStartAddr = inp32(REG_CAP_YBA + eBuf * 4);
    }
    else
        return E_CAP_INVALID_PIPE;
    return Successful;
}

/**
 * @brief       Set standard CCIR656.
 *
 * @param[in]   bIsStandard      Standard CCIR656.
 *                               - 1 : Standard CCIR656 mode.
 *                               - 0 : Non-Standard CCIR656 mode. (OV7725 or Hynix 702)
 * @return      None.
 *
 * @details    This function is used to set standard CCIR65/non-standard CCIR65.
 */
void CAP_SetStandardCCIR656(BOOL bIsStandard)
{
    if (bIsStandard == TRUE)
        outp32(REG_CAP_PAR, inp32(REG_CAP_PAR) & ~FBB);   // Standard
    else
        outp32(REG_CAP_PAR, inp32(REG_CAP_PAR) | FBB);      // Non-Standard
}

/**
 * @brief      Set color effect
 *
 * @param[in]  eColorMode  Available as following.
 *                         - \ref eCAP_CEF_NORMAL : Normal Color.
 *                         - \ref eCAP_CEF_SEPIA : Sepia effect,
 *                         corresponding U,V component value is set at register - \ref REG_CAP_SEPIA.
 *                         - \ref eCAP_CEF_NEGATIVE  : Negative picture.
 *                         - \ref eCAP_CEF_POSTERIZE : Posterize image,
 *                         the Y, U, V components posterizing factor are set at register - \ref REG_CAP_POSTERIZE.
 *
 * @retval     0 Success
 * @retval     <0 Error code
 *
 * @details    This function is used to set color effect.
 */
INT32 CAP_SetColorEffect(E_CAP_CEF eColorMode)
{
    if (eColorMode > eCAP_CEF_POSTERIZE)
        return E_CAP_INVALID_COLOR_MODE;
    outp32(REG_CAP_PAR, (inp32(REG_CAP_PAR) & ~COLORCTL) |
           (eColorMode << 11));
    return Successful;
}

/**
 * @brief      Get color effect
 *
 * @param[out] peColorMode  Available as following.
 *                         - \ref eCAP_CEF_NORMAL : Normal Color.
 *                         - \ref eCAP_CEF_SEPIA : Sepia effect,
 *                         corresponding U,V component value is set at register - \ref REG_CAP_SEPIA.
 *                         - \ref eCAP_CEF_NEGATIVE  : Negative picture.
 *                         - \ref eCAP_CEF_POSTERIZE : Posterize image,
 *                         the Y, U, V components posterizing factor are set at register - \ref REG_CAP_POSTERIZE.
 *
 * @return     None.
 *
 * @details    This function is used to get color effect.
 */
void DrvCAP_GetColorEffect(E_CAP_CEF   *peColorMode)
{
    UINT32 u32Tmp = inp32(REG_CAP_PAR);
    *peColorMode = (E_CAP_CEF)((u32Tmp & COLORCTL) >> 11);
}

/**
 * @brief      Set color effect parameter
 *
 * @param[in]  u8YComp  The constant Y component.If eColorMode is set to
 *                      eCAP_CEF_SEPIA : the constant Y component in - \ref REG_CAP_SEPIA.
 *                      eCAP_CEF_POSTERIZE : the constant Y component in - \ref REG_CAP_POSTERIZE.
 * @param[in]  u8UComp  The constant U component.
 *                      eCAP_CEF_SEPIA : the constant U component in - \ref REG_CAP_SEPIA.
 *                      eCAP_CEF_POSTERIZE : the constant U component in - \ref REG_CAP_POSTERIZE.
 * @param[in]  u8VComp  The constant V component.
 *                      eCAP_CEF_SEPIA : the constant V component in - \ref REG_CAP_SEPIA.
 *                      eCAP_CEF_POSTERIZE : the constant V component in - \ref REG_CAP_POSTERIZE.
 * @retval     0 Success
 * @retval     <0 Error code
 *
 * @details    This function is used to set color effect parameter.
 */
INT32 CAP_SetColorEffectParameter(UINT8 u8YComp, UINT8 u8UComp, UINT8 u8VComp)
{
    UINT32 u32Tmp = inp32(REG_CAP_PAR);
    UINT32 u32ColorMode = (u32Tmp & COLORCTL) >> 11;
    if (u32ColorMode == eCAP_CEF_SEPIA)
    {
        outp32(REG_CAP_SEPIA, (((UINT32)u8UComp << 8) | u8VComp));
    }
    else if (u32ColorMode == eCAP_CEF_POSTERIZE)
    {
        outp32(REG_CAP_POSTERIZE, (((UINT32)u8YComp << 16) | ((UINT32)u8UComp << 8) | u8VComp));
    }
    else
    {
        return E_CAP_WRONG_COLOR_PARAMETER;
    }
    return Successful;
}

/**
 * @brief      Get color effect parameter
 *
 * @param[out] pu8YComp  The constant Y component.If eColorMode is set to
 *                       eCAP_CEF_SEPIA : the constant Y component in - \ref REG_CAP_SEPIA.
 *                       eCAP_CEF_POSTERIZE : the constant Y component in - \ref REG_CAP_POSTERIZE.
 * @param[out] pu8UComp  The constant U component.
 *                       eCAP_CEF_SEPIA : the constant U component in - \ref REG_CAP_SEPIA.
 *                       eCAP_CEF_POSTERIZE : the constant U component in - \ref REG_CAP_POSTERIZE.
 * @param[out] pu8VComp  The constant V component.
 *                       eCAP_CEF_SEPIA : the constant V component in - \ref REG_CAP_SEPIA.
 *                       eCAP_CEF_POSTERIZE : the constant V component in - \ref REG_CAP_POSTERIZE.
 * @retval     0 Success
 * @retval     <0 Error code
 *
 * @details    This function is used to get color effect parameter.
 */
INT32 CAP_GetColorEffectParameter(PUINT8 pu8YComp, PUINT8 pu8UComp, PUINT8 pu8VComp)
{
    UINT32 u32Tmp = inp32(REG_CAP_PAR);
    UINT32 u32ColorMode = (u32Tmp & COLORCTL) >> 11;
    if (u32ColorMode == eCAP_CEF_SEPIA)
    {
        u32Tmp = inp32(REG_CAP_SEPIA);
        *pu8UComp = (u32Tmp & 0xFF00) >> 8;
        *pu8VComp = u32Tmp & 0xFF;
    }
    else if (u32ColorMode == eCAP_CEF_POSTERIZE)
    {
        u32Tmp = inp32(REG_CAP_POSTERIZE);
        *pu8YComp = (u32Tmp & 0xFF0000) >> 16;
        *pu8UComp = (u32Tmp & 0xFF00) >> 8;
        *pu8VComp = u32Tmp & 0xFF;
    }
    else
    {
        return E_CAP_WRONG_COLOR_PARAMETER;
    }
    return Successful;
}

/// @cond HIDDEN_SYMBOLS
CAPDEV_T CAP =
{
    CAP_Init,                         // void  (*Init)(BOOL bIsEnableSnrClock, E_CAP_SNR_SRC eSnrSrc, UINT32 u32SensorFreqKHz, E_CAP_DEV_TYPE eDevType):
    CAP_Open,                         // INT32 (*Open)(UINT32 u32SensorFreqKHz);
    CAP_Close,                        // void  (*Close)(void);
    CAP_SetPipeEnable,                // void  (*SetPipeEnable)(BOOL bEngEnable, E_CAP_PIPE ePipeEnable);
    CAP_SetPlanarFormat,              // void  (*SetPlanarFormat)(E_CAP_PLANAR_FORMAT ePlanarFmt);
    CAP_SetCropWinSize,               // void  (*SetCropWinSize)(UINT32 u32height, UINT32 u32width);
    CAP_SetCropWinStartAddr,          // void  (*SetCropWinStartAddr)(UINT32 u32VerticalStart, UINT32 u32HorizontalStart);
    CAP_SetStride,                    // void  (*SetStride)(UINT32 u16packetstride, UINT32 u32planarstride);
    CAP_GetStride,                    // void  (*GetStride)(PUINT32 pu32PacketStride, PUINT32 pu32PlanarStride);
    CAP_EnableInt,                    // INT32 (*EnableInt)(E_CAP_INT_TYPE eIntType);
    CAP_DisableInt,                   // INT32 (*DisableInt)(E_CAP_INT_TYPE eIntType);
    CAP_InstallCallback,              // INT32 (*InstallCallback)(E_CAP_INT_TYPE eIntType, PFN_CAP_CALLBACK pfnCallback, PFN_CAP_CALLBACK *pfnOldCallback);
    CAP_SetBaseStartAddress,          // INT32 (*SetBaseStartAddress(E_CAP_PIPE ePipe, E_CAP_BUFFER eBuf, UINT32 u32BaseStartAddr);
    CAP_SetOperationMode,             // void  (*SetOperationMode(BOOL bIsOneSutterMode);
    CAP_GetOperationMode,             // BOOL  (*GetOperationMode)(void);
    CAP_SetPacketFrameBufferControl,  // void  (*videoIn1_SetPacketFrameBufferControl)(BOOL bFrameSwitch, BOOL bFrameBufferSel);
    CAP_SetSensorPolarity,            // void  (*videoIn1_SetSensorPolarity)(BOOL bVsync, BOOL bHsync,  BOOL bPixelClk);
    CAP_SetColorEffectParameter,      // INT32 (*SetColorEffectParameter)(UINT8 u8YComp, UINT8 u8UComp, UINT8 u8VComp);
    CAP_SetDataFormatAndOrder,        // void  (*SetDataFormatAndOrder)(E_CAP_ORDER eInputOrder, E_CAP_IN_FORMAT eInputFormat, E_CAP_OUT_FORMAT eOutputFormat)
    CAP_SetMotionDet,                 // void  (*SetMotionDet)(BOOL bEnable, BOOL bBlockSize,BOOL bSaveMode);
    CAP_SetMotionDetEx,               // void  (*SetMotionDetEx)(UINT32 u32Threshold, UINT32 u32OutBuffer, UINT32 u32LumBuffer);
    CAP_SetStandardCCIR656,           // void  (*SetStandardCcir656)(BOOL);
    CAP_SetShadowRegister             // void  (*SetShadowRegister)(void);
};
/// @endcond HIDDEN_SYMBOLS

/*@}*/ /* end of group N9H30_CAP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_CAP_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

