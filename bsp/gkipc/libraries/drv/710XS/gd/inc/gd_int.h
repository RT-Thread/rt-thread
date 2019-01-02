/*!
*******************************************************************************
**
** \file      gd_int.h
**
** \brief     INT (interrupt) driver
**
**            This driver provides functions and structures required to
**            access the GK6202 interrupt engine.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version
**
******************************************************************************/
#ifndef GD_INT_H
#define GD_INT_H

#include <gtypes.h>
#include <gmodids.h>

#define GD_VIC_INSTANCES        2
#define GD_INT_VEC_OFFSET       32
/*---------------------------------------------------------------------------*/
/* constants and macros                                                      */
/*---------------------------------------------------------------------------*/
#define GD_INT_ERR_BASE (GD_INT_MODULE_ID<<16) //!< The INT base error code.

/*!
*******************************************************************************
**
** \anchor int_defines
** \name   interrupt driver specific macros
**
** This section defines various macros required to control interrupts.
**
******************************************************************************/
/*@{*/
#define GD_INT_NO_INVERT_IRQ    0 //!< The IRQ signal is not inverted.
#define GD_INT_INVERT_IRQ       1 //!< The IRQ signal is inverted.

#define GD_INT_LOW_PRIORITY     0 //!< Fast Interrupt Request (FIQ) for fast, low latency interrupt handling
#define GD_INT_MID_PRIORITY     1 //!< Interrupt Request (IRQ) for more general interrupts

#define GD_INT_DISABLED         0 //!< Interrupts are disabled.
#define GD_INT_ENABLED          1 //!< Interrupts are enabled.
/*@}*/
#define GD_INT_RISING_EDGE      0
#define GD_INT_FALLING_EDGE     1
#define GD_INT_BOTH_EDGES       2
#define GD_INT_LEVEL_LOW        3
#define GD_INT_LEVEL_HIGH       4
/*!
*******************************************************************************
**
** \brief Interrupt vectors
**
** The list below describes all available interrupt sources,
** a table containing the real interrupt service routines can
** be stored in the ARC aux. register 0x0203.
**
** The first three interrupt vectors are non-maskable, their
** priorty is high.
** All other interrupts are maskable and the priority can be set
** either to medium (1) or low (2).
**
******************************************************************************/
enum
{
    GD_INT_RESERVED1_00_IRQ   =  0,  //!<
    GD_INT_ETH_IRQ            =  1,  //!< level, Ethernet 1
    GD_INT_IDSP_ERROR_IRQ     =  2,  //!< edge, iDSP error
	  GD_INT_XIU_TIMEOUT_IRQ		=  3,  //!< edge
    GD_INT_RESERVED1_04_IRQ   =  4,  //!<
    GD_INT_RESERVED1_05_IRQ   =  5,  //!<	
    GD_INT_RESERVED1_06_IRQ   =  6,  //!<
	  GD_INT_CODING_ORC_VOUT1_IRQ =7,  //!< edge, Coding Orc VOUT1
    GD_INT_SD_CONTROLLER_IRQ  =  8,  //!< level, SD controller
    GD_INT_IDC_IRQ            =  9,  //!< level, i2c read/write, I2C0
    GD_INT_SSI_SPI_IRQ        = 10,  //!< level, Synchronous Serial Interface (SSI, SPI)    
    GD_INT_WDT_IRQ            = 11,  //!< edge, Watchdog (WDT)
    GD_INT_RESERVED1_12_IRQ   = 12,  //!<
    GD_INT_SD2_CARD_DETECT_IRQ   = 13,  //!<
    GD_INT_SD_CARD_DETECT_IRQ = 14,  //!< Both edges, SD card detect (state of SMIO5 pin)
    GD_INT_UART1_IRQ          = 15,  //!< level, uart read/write, UART1
    GD_INT_GPIO0_IRQ          = 16,  //!< level, GPIO0
    GD_INT_RESERVED1_17_IRQ   = 17,  //!< level, UART2
    GD_INT_TIMER1_IRQ         = 18,  //!< edge, timer#1
    GD_INT_TIMER2_IRQ         = 19,  //!< edge, timer#2
    GD_INT_TIMER3_IRQ         = 20,  //!< edge, timer#3
    GD_INT_DMA_IRQ            = 21,  //!< level, DMA
    GD_INT_SD2_CONTROLLER_IRQ = 22,  //!< level, SD2 controller
    GD_INT_RESERVED1_23_IRQ   = 23,  //!<
    GD_INT_CODING_ORC_VIN_IRQ = 24,  //!< edge, Coding Orc VIN
    GD_INT_CORDING_ORC_VDSP_IRQ   = 25,  //!< edge, Cording Orc vDSP
    GD_INT_USB_IRQ            = 26,  //!< level, USB
    GD_INT_UART2_IRQ          = 27,  //!<
    GD_INT_RESERVED1_28_IRQ   = 28,  //!<
    GD_INT_AUDIO_I2S_TX_IRQ 	= 29,  //!< level, Audio (I2S) TX    
    GD_INT_AUDIO_I2S_RX_IRQ 	= 30,  //!< level, Audio (I2S) RX
    GD_INT_UART_IRQ           = 31,  //!< level, UART0
#if (GD_VIC_INSTANCES >= 2)
    GD_INT_RESERVED2_00_IRQ   = ( 0 + 32),  //!<
    GD_INT_RESERVED2_01_IRQ   = ( 1 + 32),  //!<
    GD_INT_RESERVED2_02_IRQ   = ( 2 + 32),  //!<
    GD_INT_RESERVED2_03_IRQ   = ( 3 + 32),  //!<
    GD_INT_RESERVED2_04_IRQ   = ( 4 + 32),  //!<
    GD_INT_RESERVED2_05_IRQ   = ( 5 + 32),  //!<
    GD_INT_RESERVED2_06_IRQ   = ( 6 + 32),  //!<
    GD_INT_RESERVED2_07_IRQ   = ( 7 + 32),  //!<
    GD_INT_AUDIO_PHY_TX_IRQ   = ( 8 + 32),  //!<level, Audio PHY TX INT
    GD_INT_AUDIO_PHY_RX_IRQ   = ( 9 + 32),  //!<level, Audio PHY RX INT 
    GD_INT_RESERVED2_10_IRQ   = (10 + 32),  //!<
    GD_INT_RESERVED2_11_IRQ   = (11 + 32),  //!<
    GD_INT_RESERVED2_12_IRQ   = (12 + 32),  //!<
    GD_INT_RESERVED2_13_IRQ   = (13 + 32),  //!<
    GD_INT_RESERVED2_14_IRQ   = (14 + 32),  //!<
    GD_INT_RESERVED2_15_IRQ   = (15 + 32),  //!<
    GD_INT_RESERVED2_16_IRQ   = (16 + 32),  //!<
    GD_INT_RESERVED2_17_IRQ   = (17 + 32),  //!<*/
    GD_INT_CODING_ORC_VOUT0_IRQ=(18 + 32),  //!< edge, Coding Orc VOUT0	 
    GD_INT_AES_OUTPUT_READY_IRQ=(19 + 32),  //!< edge, AES output ready from Crypt block--AES finished
    GD_INT_DES_OUTPUT_READY_IRQ=(20 + 32),  //!< edge, DES output ready from Crypt block--DES finished
    GD_INT_RESERVED2_21_IRQ    = (21 + 32),  //!< 
    GD_INT_GDMA_COMPLETION_IRQ = (22 + 32),  //!<edge, GDMA Completion
    GD_INT_RESERVED2_23_IRQ   = (23 + 32),  //!<
    GD_INT_ADC_LEVEL_CHANGE_IRQ=(24 + 32),  //!< level, ADC level change
    GD_INT_RESERVED2_25_IRQ   = (25 + 32),  //!<
    GD_INT_IDC2_IRQ           = (26 + 32),  //!< level, IDC2
    GD_INT_IDSP_LAST_PIXEL_IRQ= (27 + 32),  //!< edge, iDSP last pixel
    GD_INT_IDSP_VSYNC_IRQ     = (28 + 32),  //!< edge, iDSP Vsync (VIN on master mode)  
    GD_INT_IDSP_SENSOR_VSYNC_IRQ=(29+ 32),  //!< edge, iDSP sensor Vsync (VIN on slave mode)
    GD_INT_PMU_IRQ            = (30 + 32),  //!< level, PMU
    GD_INT_SSI2_IRQ           = (31 + 32),  //!< level, SSI2
#endif

};

// modify for rtos
#define GD_INT_LAST_IRQ         (31 + 32)
/*---------------------------------------------------------------------------*/
/* types, enums and structures                                               */
/*---------------------------------------------------------------------------*/
/*!
*******************************************************************************
**
** \brief Interrupt initialization parameter structure.
**
** \sa    GD_INT_Init()
**
******************************************************************************/
typedef struct
{
    void (*resetFct)(void);         //!< The reset handler.
    void (*memExceptionFct)(void);  //!< The memory exception handler.
    void (*instructErrorFct)(void); //!< The Instruction Error handler.
} GD_INT_INIT_PARAMS_S;

/*!
*******************************************************************************
**
** \brief Interrupt driver open parameter structure.
**
** \sa    GD_INT_Open()
**
******************************************************************************/
typedef struct
{
    S8 type;        //!< the interrupt vector to access
    S8 active;      //!< activation, either GD_INT_INVERT_IRQ or GD_INT_NO_INVERT_IRQ
    S8 sensitivity; //!< sensitivity, GD_INT_RISING_EDGE or GD_INT_FALLING_EDGE
                    //!<    or GD_INT_BOTH_EDGES or GD_INT_LEVEL_LOW or GD_INT_LEVEL_HIGH
    S8 priority;    //!< priority, either GD_INT_MID_PRIORITY or GD_INT_LOW_PRIORITY
    union
    {
        GISR1 (*lowPrio)(void);
        GISR2 (*midPrio)(void);
    }isrFct;   //!< the interrupt service function
} GD_INT_OPEN_PARAMS_S;

/*!
*******************************************************************************
**
** \brief Interrupt processor function type.
**
******************************************************************************/
/*! Pointer to the interrupt handler function of the driver. */
typedef GISR1(*GD_ARM_INTR_IsrFuncT)(void);
/*! //!< Pointer to the processing function of the driver. */
typedef void(*GD_INT_PROCESSOR_F)(void* data);

/*!
*******************************************************************************
**
** \brief Interrupt driver data structure
**
******************************************************************************/
typedef struct
{
    U32                     length;    //!< The length of the driver data in bytes.
    void*                   data;      //!< Pointer to driver specific data structure.
    GD_INT_PROCESSOR_F      processor; //!< Pointer to interrupt processing function.
} GD_INT_DATA_S;

/*!
*******************************************************************************
**
** \brief Interrupt handler function type
**
******************************************************************************/
/*! Pointer to the interrupt handler function of the driver. */
typedef GD_INT_DATA_S*(*GD_INT_HANDLER_F)(void);


/*---------------------------------------------------------------------------*/
/* function prototypes                                                       */
/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

void GD_INT_Close(GD_HANDLE *handleP);
GERR GD_INT_Init(GD_INT_INIT_PARAMS_S *initParams);
GERR GD_INT_Open(GD_INT_OPEN_PARAMS_S *openParams, GD_HANDLE *handle);
void GD_INT_GetIrqSettings(S8 type, S8 *prio, S8 *act, S8 *sens, S8 *mask);
U32  GD_INT_GetUsedIrqs(void);
void GD_INT_SetInterruptTrigger(S8 vec);
void GD_INT_SetVector(S8 vector, void (*target)());
void GD_INT_SetHandler(S8 vector, GD_INT_HANDLER_F handler);
GD_INT_HANDLER_F GD_INT_GetHandler(S8 vector);
void GD_INT_InvalidateDataCache(void);
void GD_INT_InvalidateInstructionCache(void);
void GD_INT_Enable(GD_HANDLE *handleP,U8 enable);

void GD_INT_DisableAllInterrupts(void);
void GD_INT_EnableAllInterrupts(void);

void GD_IRQ_ISR(void);
void GD_FIQ_ISR(void);

#ifdef __cplusplus
}
#endif

#endif
/* end of gd_int.h */
