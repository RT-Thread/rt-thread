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
#include "gh_vic.h"


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
** a table containing the real interrupt service routines
** All other interrupts are maskable and the priority can be set
** either to medium (1) or low (2).
**
******************************************************************************/
#define    GD_INT_CODING_ORC_VOUT1_IRQ   GH_INT_CODING_ORC_VOUT1_IRQ 
#define    GD_INT_CODING_ORC_VIN_IRQ     GH_INT_CODING_ORC_VIN_IRQ   
#define    GD_INT_CORDING_ORC_VDSP_IRQ   GH_INT_CORDING_ORC_VDSP_IRQ 
#define    GD_INT_USB_IRQ                GH_INT_USB_IRQ              
#define    GD_INT_UART2_IRQ              GH_INT_UART2_IRQ            
#define    GD_INT_XIU_TIMEOUT_IRQ        GH_INT_XIU_TIMEOUT_IRQ      
#define    GD_INT_AUDIO_I2S_TX_IRQ       GH_INT_AUDIO_I2S_TX_IRQ     
#define    GD_INT_AUDIO_I2S_RX_IRQ       GH_INT_AUDIO_I2S_RX_IRQ     
#define    GD_INT_UART_IRQ               GH_INT_UART_IRQ   
#define    GD_INT_GPIO0_IRQ              GH_INT_GPIO0_IRQ            
#define    GD_INT_TIMER1_IRQ             GH_INT_TIMER1_IRQ           
#define    GD_INT_TIMER2_IRQ             GH_INT_TIMER2_IRQ           
#define    GD_INT_TIMER3_IRQ             GH_INT_TIMER3_IRQ           
#define    GD_INT_DMA_IRQ                GH_INT_DMA_IRQ              
#define    GD_INT_SD_CONTROLLER_IRQ      GH_INT_SD_CONTROLLER_IRQ    
#define    GD_INT_IDC_IRQ                GH_INT_IDC_IRQ              
#define    GD_INT_SSI_SPI_IRQ            GH_INT_SSI_SPI_IRQ          
#define    GD_INT_WDT_IRQ                GH_INT_WDT_IRQ              
#define    GD_INT_IRIF_IRQ               GH_INT_IRIF_IRQ             
#define    GD_INT_RESERVED1_23_IRQ       GH_INT_RESERVED1_23_IRQ     
#define    GD_INT_SD_CARD_DETECT_IRQ     GH_INT_SD_CARD_DETECT_IRQ   
#define    GD_INT_UART1_IRQ              GH_INT_UART1_IRQ            
#define    GD_INT_SSI_SLAVE_IRQ          GH_INT_SSI_SLAVE_IRQ        
#define    GD_INT_ETH_IRQ                GH_INT_ETH_IRQ              
#define    GD_INT_IDSP_ERROR_IRQ         GH_INT_IDSP_ERROR_IRQ       
#if (GD_VIC_INSTANCES >= 2)
#define    GD_INT_RESERVED2_00_IRQ       GH_INT_RESERVED2_00_IRQ     
#define    GD_INT_RESERVED2_01_IRQ       GH_INT_RESERVED2_01_IRQ     
#define    GD_INT_ADC_LEVEL_CHANGE_IRQ   GH_INT_ADC_LEVEL_CHANGE_IRQ 
#define    GD_INT_RESERVED2_03_IRQ       GH_INT_RESERVED2_03_IRQ     
#define    GD_INT_IDC2_IRQ               GH_INT_IDC2_IRQ             
#define    GD_INT_IDSP_LAST_PIXEL_IRQ    GH_INT_IDSP_LAST_PIXEL_IRQ  
#define    GD_INT_IDSP_VSYNC_IRQ         GH_INT_IDSP_VSYNC_IRQ       
#define    GD_INT_IDSP_SENSOR_VSYNC_IRQ  GH_INT_IDSP_SENSOR_VSYNC_IRQ
#define    GD_INT_PMU_IRQ                GH_INT_PMU_IRQ              
#define    GD_INT_SSI2_IRQ               GH_INT_SSI2_IRQ             
#define    GD_INT_RESERVED2_10_IRQ       GH_INT_RESERVED2_10_IRQ     
#define    GD_INT_RESERVED2_11_IRQ       GH_INT_RESERVED2_11_IRQ     
#define    GD_INT_CODING_ORC_VOUT0_IRQ   GH_INT_CODING_ORC_VOUT0_IRQ 
#define    GD_INT_AES_OUTPUT_READY_IRQ   GH_INT_AES_OUTPUT_READY_IRQ 
#define    GD_INT_DES_OUTPUT_READY_IRQ   GH_INT_DES_OUTPUT_READY_IRQ 
#define    GD_INT_RESERVED2_15_IRQ       GH_INT_RESERVED2_15_IRQ     
#define    GD_INT_GDMA_COMPLETION_IRQ    GH_INT_GDMA_COMPLETION_IRQ  
#define    GD_INT_MOTOR_INTERRUPT_IRQ    GH_INT_MOTOR_INTERRUPT_IRQ  
#define    GD_INT_AUDIO_PHY_RX_IRQ       GH_INT_AUDIO_PHY_RX_IRQ     
#define    GD_INT_AUDIO_PHY_TX_IRQ       GH_INT_AUDIO_PHY_TX_IRQ     
#endif

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
