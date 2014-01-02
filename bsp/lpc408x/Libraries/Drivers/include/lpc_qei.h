/**********************************************************************
* $Id$      lpc_qei.h           2011-06-02
*//**
* @file     lpc_qei.h
* @brief    Contains all macro definitions and function prototypes
*           support for QEI firmware library on LPC
* @version  1.0
* @date     02. June. 2011
* @author   NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup QEI QEI (Quadrature Encoder Interface)
 * @ingroup LPC_CMSIS_FwLib_Drivers
 * @{
 */

#ifndef __LPC17X_8X_QEI_H_
#define __LPC17X_8X_QEI_H_

/* Includes ------------------------------------------------------------------- */
#include "LPC407x_8x_177x_8x.h"
#include "lpc_types.h"


#ifdef __cplusplus
extern "C"
{
#endif

/* Public Macros -------------------------------------------------------------- */
/** @defgroup QEI_Public_Macros QEI Public Macros
 * @{
 */

#define QEI_0                   (0)

/* QEI Reset types */
/** QEI Reset types - Reset position counter */
#define QEI_RESET_POS           QEI_CON_RESP
/** QEI Reset types - Reset Posistion Counter on Index */
#define QEI_RESET_POSOnIDX      QEI_CON_RESPI
/** QEI Reset types - Reset Velocity */
#define QEI_RESET_VEL           QEI_CON_RESV
/** QEI Reset types - Reset Index Counter */
#define QEI_RESET_IDX           QEI_CON_RESI

/* QEI Direction Invert Type Option */
/** QEI Direction Invert Type Option - Direction is not inverted */
#define QEI_DIRINV_NONE     ((uint32_t)(0))
/** QEI Direction Invert Type Option - Direction is complemented */
#define QEI_DIRINV_CMPL     ((uint32_t)(1))

/* QEI Signal Mode Option */
/** Signal operation: Quadrature phase mode */
#define QEI_SIGNALMODE_QUAD     ((uint32_t)(0))
/** Signal operation: Clock/Direction mode */
#define QEI_SIGNALMODE_CLKDIR   ((uint32_t)(1))

/* QEI Capture Mode Option */
/** Capture mode: Only Phase-A edges are counted (2X) */
#define QEI_CAPMODE_2X          ((uint32_t)(0))
/** Capture mode: BOTH PhA and PhB edges are counted (4X)*/
#define QEI_CAPMODE_4X          ((uint32_t)(1))

/* QEI Invert Index Signal Option */
/** Invert Index signal option: None */
#define QEI_INVINX_NONE         ((uint32_t)(0))
/** Invert Index signal option: Enable */
#define QEI_INVINX_EN           ((uint32_t)(1))

/* QEI timer reload option */
/** Reload value in absolute value */
#define QEI_TIMERRELOAD_TICKVAL ((uint8_t)(0))
/** Reload value in microsecond value */
#define QEI_TIMERRELOAD_USVAL   ((uint8_t)(1))

/* QEI Flag Status type */
/** Direction status */
#define QEI_STATUS_DIR          ((uint32_t)(1<<0))

/* QEI Compare Position channel option */
/** QEI compare position channel 0 */
#define QEI_COMPPOS_CH_0            ((uint8_t)(0))
/** QEI compare position channel 1 */
#define QEI_COMPPOS_CH_1            ((uint8_t)(1))
/** QEI compare position channel 2 */
#define QEI_COMPPOS_CH_2            ((uint8_t)(2))

/* QEI interrupt flag type */
/** index pulse was detected interrupt */
#define QEI_INTFLAG_INX_Int         ((uint32_t)(1<<0))
/** Velocity timer over flow interrupt */
#define QEI_INTFLAG_TIM_Int         ((uint32_t)(1<<1))
/** Capture velocity is less than compare interrupt */
#define QEI_INTFLAG_VELC_Int        ((uint32_t)(1<<2))
/** Change of direction interrupt */
#define QEI_INTFLAG_DIR_Int         ((uint32_t)(1<<3))
/** An encoder phase error interrupt */
#define QEI_INTFLAG_ERR_Int         ((uint32_t)(1<<4))
/** An encoder clock pulse was detected interrupt */
#define QEI_INTFLAG_ENCLK_Int       ((uint32_t)(1<<5))
/** position 0 compare value is equal to the current position interrupt */
#define QEI_INTFLAG_POS0_Int        ((uint32_t)(1<<6))
/** position 1 compare value is equal to the current position interrupt */
#define QEI_INTFLAG_POS1_Int        ((uint32_t)(1<<7))
/** position 2 compare value is equal to the current position interrupt */
#define QEI_INTFLAG_POS2_Int        ((uint32_t)(1<<8))
/** Index compare value is equal to the current index count interrupt */
#define QEI_INTFLAG_REV_Int         ((uint32_t)(1<<9))
/** Combined position 0 and revolution count interrupt */
#define QEI_INTFLAG_POS0REV_Int     ((uint32_t)(1<<10))
/** Combined position 1 and revolution count interrupt */
#define QEI_INTFLAG_POS1REV_Int     ((uint32_t)(1<<11))
/** Combined position 2 and revolution count interrupt */
#define QEI_INTFLAG_POS2REV_Int     ((uint32_t)(1<<12))

/**
 * @}
 */


/* Private Macros ------------------------------------------------------------- */
/** @defgroup QEI_Private_Macros QEI Private Macros
 * @{
 */

/* --------------------- BIT DEFINITIONS -------------------------------------- */
/* Quadrature Encoder Interface Control Register Definition --------------------- */
/*********************************************************************//**
 * Macro defines for QEI Control register
 **********************************************************************/
/** Reset position counter */
#define QEI_CON_RESP        ((uint32_t)(1<<0))
/** Reset Posistion Counter on Index */
#define QEI_CON_RESPI       ((uint32_t)(1<<1))
/** Reset Velocity */
#define QEI_CON_RESV        ((uint32_t)(1<<2))
/** Reset Index Counter */
#define QEI_CON_RESI        ((uint32_t)(1<<3))
/** QEI Control register bit-mask */
#define QEI_CON_BITMASK     ((uint32_t)(0x0F))

/*********************************************************************//**
 * Macro defines for QEI Configuration register
 **********************************************************************/
/** Direction Invert */
#define QEI_CONF_DIRINV     ((uint32_t)(1<<0))
/** Signal mode */
#define QEI_CONF_SIGMODE    ((uint32_t)(1<<1))
/** Capture mode */
#define QEI_CONF_CAPMODE    ((uint32_t)(1<<2))
/** Invert index */
#define QEI_CONF_INVINX     ((uint32_t)(1<<3))
/** QEI Configuration register bit-mask */
#define QEI_CONF_BITMASK    ((uint32_t)(0x0F))

/*********************************************************************//**
 * Macro defines for QEI Status register
 **********************************************************************/
/** Direction bit */
#define QEI_STAT_DIR        ((uint32_t)(1<<0))
/** QEI status register bit-mask */
#define QEI_STAT_BITMASK    ((uint32_t)(1<<0))

/* Quadrature Encoder Interface Interrupt registers definitions --------------------- */
/*********************************************************************//**
 * Macro defines for QEI Interrupt Status register
 **********************************************************************/
/** Indicates that an index pulse was detected */
#define QEI_INTSTAT_INX_Int         ((uint32_t)(1<<0))
/** Indicates that a velocity timer overflow occurred */
#define QEI_INTSTAT_TIM_Int         ((uint32_t)(1<<1))
/** Indicates that capture velocity is less than compare velocity */
#define QEI_INTSTAT_VELC_Int        ((uint32_t)(1<<2))
/** Indicates that a change of direction was detected */
#define QEI_INTSTAT_DIR_Int         ((uint32_t)(1<<3))
/** Indicates that an encoder phase error was detected */
#define QEI_INTSTAT_ERR_Int         ((uint32_t)(1<<4))
/** Indicates that and encoder clock pulse was detected */
#define QEI_INTSTAT_ENCLK_Int       ((uint32_t)(1<<5))
/** Indicates that the position 0 compare value is equal to the current position */
#define QEI_INTSTAT_POS0_Int        ((uint32_t)(1<<6))
/** Indicates that the position 1compare value is equal to the current position */
#define QEI_INTSTAT_POS1_Int        ((uint32_t)(1<<7))
/** Indicates that the position 2 compare value is equal to the current position */
#define QEI_INTSTAT_POS2_Int        ((uint32_t)(1<<8))
/** Indicates that the index compare value is equal to the current index count */
#define QEI_INTSTAT_REV_Int         ((uint32_t)(1<<9))
/** Combined position 0 and revolution count interrupt. Set when
* both the POS0_Int bit is set and the REV_Int is set */
#define QEI_INTSTAT_POS0REV_Int     ((uint32_t)(1<<10))
/** Combined position 1 and revolution count interrupt. Set when
both the POS1_Int bit is set and the REV_Int is set */
#define QEI_INTSTAT_POS1REV_Int     ((uint32_t)(1<<11))
/** Combined position 2 and revolution count interrupt. Set when
both the POS2_Int bit is set and the REV_Int is set */
#define QEI_INTSTAT_POS2REV_Int     ((uint32_t)(1<<12))
/** QEI Interrupt Status register bit-mask */
#define QEI_INTSTAT_BITMASK         ((uint32_t)(0x1FFF))

/*********************************************************************//**
 * Macro defines for QEI Interrupt Set register
 **********************************************************************/
/** Set Bit Indicates that an index pulse was detected */
#define QEI_INTSET_INX_Int          ((uint32_t)(1<<0))
/** Set Bit Indicates that a velocity timer overflow occurred */
#define QEI_INTSET_TIM_Int          ((uint32_t)(1<<1))
/** Set Bit Indicates that capture velocity is less than compare velocity */
#define QEI_INTSET_VELC_Int         ((uint32_t)(1<<2))
/** Set Bit Indicates that a change of direction was detected */
#define QEI_INTSET_DIR_Int          ((uint32_t)(1<<3))
/** Set Bit Indicates that an encoder phase error was detected */
#define QEI_INTSET_ERR_Int          ((uint32_t)(1<<4))
/** Set Bit Indicates that and encoder clock pulse was detected */
#define QEI_INTSET_ENCLK_Int        ((uint32_t)(1<<5))
/** Set Bit Indicates that the position 0 compare value is equal to the current position */
#define QEI_INTSET_POS0_Int         ((uint32_t)(1<<6))
/** Set Bit Indicates that the position 1compare value is equal to the current position */
#define QEI_INTSET_POS1_Int         ((uint32_t)(1<<7))
/** Set Bit Indicates that the position 2 compare value is equal to the current position */
#define QEI_INTSET_POS2_Int         ((uint32_t)(1<<8))
/** Set Bit Indicates that the index compare value is equal to the current index count */
#define QEI_INTSET_REV_Int          ((uint32_t)(1<<9))
/** Set Bit that combined position 0 and revolution count interrupt */
#define QEI_INTSET_POS0REV_Int      ((uint32_t)(1<<10))
/** Set Bit that Combined position 1 and revolution count interrupt */
#define QEI_INTSET_POS1REV_Int      ((uint32_t)(1<<11))
/** Set Bit that Combined position 2 and revolution count interrupt */
#define QEI_INTSET_POS2REV_Int      ((uint32_t)(1<<12))
/** QEI Interrupt Set register bit-mask */
#define QEI_INTSET_BITMASK          ((uint32_t)(0x1FFF))

/*********************************************************************//**
 * Macro defines for QEI Interrupt Clear register
 **********************************************************************/
/** Clear Bit Indicates that an index pulse was detected */
#define QEI_INTCLR_INX_Int          ((uint32_t)(1<<0))
/** Clear Bit Indicates that a velocity timer overflow occurred */
#define QEI_INTCLR_TIM_Int          ((uint32_t)(1<<1))
/** Clear Bit Indicates that capture velocity is less than compare velocity */
#define QEI_INTCLR_VELC_Int         ((uint32_t)(1<<2))
/** Clear Bit Indicates that a change of direction was detected */
#define QEI_INTCLR_DIR_Int          ((uint32_t)(1<<3))
/** Clear Bit Indicates that an encoder phase error was detected */
#define QEI_INTCLR_ERR_Int          ((uint32_t)(1<<4))
/** Clear Bit Indicates that and encoder clock pulse was detected */
#define QEI_INTCLR_ENCLK_Int        ((uint32_t)(1<<5))
/** Clear Bit Indicates that the position 0 compare value is equal to the current position */
#define QEI_INTCLR_POS0_Int         ((uint32_t)(1<<6))
/** Clear Bit Indicates that the position 1compare value is equal to the current position */
#define QEI_INTCLR_POS1_Int         ((uint32_t)(1<<7))
/** Clear Bit Indicates that the position 2 compare value is equal to the current position */
#define QEI_INTCLR_POS2_Int         ((uint32_t)(1<<8))
/** Clear Bit Indicates that the index compare value is equal to the current index count */
#define QEI_INTCLR_REV_Int          ((uint32_t)(1<<9))
/** Clear Bit that combined position 0 and revolution count interrupt */
#define QEI_INTCLR_POS0REV_Int      ((uint32_t)(1<<10))
/** Clear Bit that Combined position 1 and revolution count interrupt */
#define QEI_INTCLR_POS1REV_Int      ((uint32_t)(1<<11))
/** Clear Bit that Combined position 2 and revolution count interrupt */
#define QEI_INTCLR_POS2REV_Int      ((uint32_t)(1<<12))
/** QEI Interrupt Clear register bit-mask */
#define QEI_INTCLR_BITMASK          ((uint32_t)(0xFFFF))

/*********************************************************************//**
 * Macro defines for QEI Interrupt Enable register
 **********************************************************************/
/** Enabled Interrupt Bit Indicates that an index pulse was detected */
#define QEI_INTEN_INX_Int           ((uint32_t)(1<<0))
/** Enabled Interrupt Bit Indicates that a velocity timer overflow occurred */
#define QEI_INTEN_TIM_Int           ((uint32_t)(1<<1))
/** Enabled Interrupt Bit Indicates that capture velocity is less than compare velocity */
#define QEI_INTEN_VELC_Int          ((uint32_t)(1<<2))
/** Enabled Interrupt Bit Indicates that a change of direction was detected */
#define QEI_INTEN_DIR_Int           ((uint32_t)(1<<3))
/** Enabled Interrupt Bit Indicates that an encoder phase error was detected */
#define QEI_INTEN_ERR_Int           ((uint32_t)(1<<4))
/** Enabled Interrupt Bit Indicates that and encoder clock pulse was detected */
#define QEI_INTEN_ENCLK_Int         ((uint32_t)(1<<5))
/** Enabled Interrupt Bit Indicates that the position 0 compare value is equal to the current position */
#define QEI_INTEN_POS0_Int          ((uint32_t)(1<<6))
/** Enabled Interrupt Bit Indicates that the position 1compare value is equal to the current position */
#define QEI_INTEN_POS1_Int          ((uint32_t)(1<<7))
/** Enabled Interrupt Bit Indicates that the position 2 compare value is equal to the current position */
#define QEI_INTEN_POS2_Int          ((uint32_t)(1<<8))
/** Enabled Interrupt Bit Indicates that the index compare value is equal to the current index count */
#define QEI_INTEN_REV_Int           ((uint32_t)(1<<9))
/** Enabled Interrupt Bit that combined position 0 and revolution count interrupt */
#define QEI_INTEN_POS0REV_Int       ((uint32_t)(1<<10))
/** Enabled Interrupt Bit that Combined position 1 and revolution count interrupt */
#define QEI_INTEN_POS1REV_Int       ((uint32_t)(1<<11))
/** Enabled Interrupt Bit that Combined position 2 and revolution count interrupt */
#define QEI_INTEN_POS2REV_Int       ((uint32_t)(1<<12))
/** QEI Interrupt Enable register bit-mask */
#define QEI_INTEN_BITMASK           ((uint32_t)(0x1FFF))

/*********************************************************************//**
 * Macro defines for QEI Interrupt Enable Set register
 **********************************************************************/
/** Set Enable Interrupt Bit Indicates that an index pulse was detected */
#define QEI_IESET_INX_Int           ((uint32_t)(1<<0))
/** Set Enable Interrupt Bit Indicates that a velocity timer overflow occurred */
#define QEI_IESET_TIM_Int           ((uint32_t)(1<<1))
/** Set Enable Interrupt Bit Indicates that capture velocity is less than compare velocity */
#define QEI_IESET_VELC_Int          ((uint32_t)(1<<2))
/** Set Enable Interrupt Bit Indicates that a change of direction was detected */
#define QEI_IESET_DIR_Int           ((uint32_t)(1<<3))
/** Set Enable Interrupt Bit Indicates that an encoder phase error was detected */
#define QEI_IESET_ERR_Int           ((uint32_t)(1<<4))
/** Set Enable Interrupt Bit Indicates that and encoder clock pulse was detected */
#define QEI_IESET_ENCLK_Int         ((uint32_t)(1<<5))
/** Set Enable Interrupt Bit Indicates that the position 0 compare value is equal to 
* the current position */
#define QEI_IESET_POS0_Int          ((uint32_t)(1<<6))
/** Set Enable Interrupt Bit Indicates that the position 1compare value is equal to 
* the current position */
#define QEI_IESET_POS1_Int          ((uint32_t)(1<<7))
/** Set Enable Interrupt Bit Indicates that the position 2 compare value is equal to 
* the current position */
#define QEI_IESET_POS2_Int          ((uint32_t)(1<<8))
/** Set Enable Interrupt Bit Indicates that the index compare value is equal to the 
* current index count */
#define QEI_IESET_REV_Int           ((uint32_t)(1<<9))
/** Set Enable Interrupt Bit that combined position 0 and revolution count interrupt */
#define QEI_IESET_POS0REV_Int       ((uint32_t)(1<<10))
/** Set Enable Interrupt Bit that Combined position 1 and revolution count interrupt */
#define QEI_IESET_POS1REV_Int       ((uint32_t)(1<<11))
/** Set Enable Interrupt Bit that Combined position 2 and revolution count interrupt */
#define QEI_IESET_POS2REV_Int       ((uint32_t)(1<<12))
/** QEI Interrupt Enable Set register bit-mask */
#define QEI_IESET_BITMASK           ((uint32_t)(0x1FFF))

/*********************************************************************//**
 * Macro defines for QEI Interrupt Enable Clear register
 **********************************************************************/
/** Clear Enabled Interrupt Bit Indicates that an index pulse was detected */
#define QEI_IECLR_INX_Int           ((uint32_t)(1<<0))
/** Clear Enabled Interrupt Bit Indicates that a velocity timer overflow occurred */
#define QEI_IECLR_TIM_Int           ((uint32_t)(1<<1))
/** Clear Enabled Interrupt Bit Indicates that capture velocity is less than compare velocity */
#define QEI_IECLR_VELC_Int          ((uint32_t)(1<<2))
/** Clear Enabled Interrupt Bit Indicates that a change of direction was detected */
#define QEI_IECLR_DIR_Int           ((uint32_t)(1<<3))
/** Clear Enabled Interrupt Bit Indicates that an encoder phase error was detected */
#define QEI_IECLR_ERR_Int           ((uint32_t)(1<<4))
/** Clear Enabled Interrupt Bit Indicates that and encoder clock pulse was detected */
#define QEI_IECLR_ENCLK_Int         ((uint32_t)(1<<5))
/** Clear Enabled Interrupt Bit Indicates that the position 0 compare value is equal to the
* current position */
#define QEI_IECLR_POS0_Int          ((uint32_t)(1<<6))
/** Clear Enabled Interrupt Bit Indicates that the position 1compare value is equal to the
* current position */
#define QEI_IECLR_POS1_Int          ((uint32_t)(1<<7))
/** Clear Enabled Interrupt Bit Indicates that the position 2 compare value is equal to the
* current position */
#define QEI_IECLR_POS2_Int          ((uint32_t)(1<<8))
/** Clear Enabled Interrupt Bit Indicates that the index compare value is equal to the current
* index count */
#define QEI_IECLR_REV_Int           ((uint32_t)(1<<9))
/** Clear Enabled Interrupt Bit that combined position 0 and revolution count interrupt */
#define QEI_IECLR_POS0REV_Int       ((uint32_t)(1<<10))
/** Clear Enabled Interrupt Bit that Combined position 1 and revolution count interrupt */
#define QEI_IECLR_POS1REV_Int       ((uint32_t)(1<<11))
/** Clear Enabled Interrupt Bit that Combined position 2 and revolution count interrupt */
#define QEI_IECLR_POS2REV_Int       ((uint32_t)(1<<12))
/** QEI Interrupt Enable Clear register bit-mask */
#define QEI_IECLR_BITMASK           ((uint32_t)(0xFFFF))


/* ---------------- CHECK PARAMETER DEFINITIONS ---------------------------- */
/* Macro check QEI peripheral */
#define PARAM_QEIx(n)   ((n==LPC_QEI))

/* Macro check QEI reset type */
#define PARAM_QEI_RESET(n)  ((n==QEI_CON_RESP) \
                                    || (n==QEI_RESET_POSOnIDX) \
                                    || (n==QEI_RESET_VEL) \
                                    || (n==QEI_RESET_IDX))

/* Macro check QEI Direction invert mode */
#define PARAM_QEI_DIRINV(n) ((n==QEI_DIRINV_NONE) || (n==QEI_DIRINV_CMPL))

/* Macro check QEI signal mode */
#define PARAM_QEI_SIGNALMODE(n) ((n==QEI_SIGNALMODE_QUAD) || (n==QEI_SIGNALMODE_CLKDIR))

/* Macro check QEI Capture mode */
#define PARAM_QEI_CAPMODE(n)    ((n==QEI_CAPMODE_2X) || (n==QEI_CAPMODE_4X))

/* Macro check QEI Invert index mode */
#define PARAM_QEI_INVINX(n)     ((n==QEI_INVINX_NONE) || (n==QEI_INVINX_EN))

/* Macro check QEI Direction invert mode */
#define PARAM_QEI_TIMERRELOAD(n)    ((n==QEI_TIMERRELOAD_TICKVAL) || (n==QEI_TIMERRELOAD_USVAL))

/* Macro check QEI status type */
#define PARAM_QEI_STATUS(n)     ((n==QEI_STATUS_DIR))

/* Macro check QEI combine position type */
#define PARAM_QEI_COMPPOS_CH(n)     ((n==QEI_COMPPOS_CH_0) || (n==QEI_COMPPOS_CH_1) || (n==QEI_COMPPOS_CH_2))

/* Macro check QEI interrupt flag type */
#define PARAM_QEI_INTFLAG(n)    ((n==QEI_INTFLAG_INX_Int) \
                                    || (n==QEI_INTFLAG_TIM_Int) \
                                    || (n==QEI_INTFLAG_VELC_Int) \
                                    || (n==QEI_INTFLAG_DIR_Int) \
                                    || (n==QEI_INTFLAG_ERR_Int) \
                                    || (n==QEI_INTFLAG_ENCLK_Int) \
                                    || (n==QEI_INTFLAG_POS0_Int) \
                                    || (n==QEI_INTFLAG_POS1_Int) \
                                    || (n==QEI_INTFLAG_POS2_Int) \
                                    || (n==QEI_INTFLAG_REV_Int) \
                                    || (n==QEI_INTFLAG_POS0REV_Int) \
                                    || (n==QEI_INTFLAG_POS1REV_Int) \
                                    || (n==QEI_INTFLAG_POS2REV_Int))
/**
 * @}
 */

/* Public Types --------------------------------------------------------------- */
/** @defgroup QEI_Public_Types QEI Public Types
 * @{
 */

/**
 * @brief QEI Configuration structure type definition
 */
typedef struct 
{
    uint32_t DirectionInvert    :1;     /**< Direction invert option:
                                        - QEI_DIRINV_NONE: QEI Direction is normal
                                        - QEI_DIRINV_CMPL: QEI Direction is complemented
                                        */
    uint32_t SignalMode         :1;     /**< Signal mode Option:
                                        - QEI_SIGNALMODE_QUAD: Signal is in Quadrature phase mode
                                        - QEI_SIGNALMODE_CLKDIR: Signal is in Clock/Direction mode
                                        */
    uint32_t CaptureMode        :1;     /**< Capture Mode Option:
                                        - QEI_CAPMODE_2X: Only Phase-A edges are counted (2X)
                                        - QEI_CAPMODE_4X: BOTH Phase-A and Phase-B edges are counted (4X)
                                        */
    uint32_t InvertIndex        :1;     /**< Invert Index Option:
                                        - QEI_INVINX_NONE: the sense of the index input is normal
                                        - QEI_INVINX_EN: inverts the sense of the index input
                                        */
} QEI_CFG_Type;

/**
 * @brief Timer Reload Configuration structure type definition
 */
typedef struct 
{

    uint8_t ReloadOption;       /**< Velocity Timer Reload Option, should be:
                                - QEI_TIMERRELOAD_TICKVAL: Reload value in absolute value
                                - QEI_TIMERRELOAD_USVAL: Reload value in microsecond value
                                */
    uint8_t Reserved[3];
    uint32_t ReloadValue;       /**< Velocity Timer Reload Value, 32-bit long, should be matched
                                with Velocity Timer Reload Option
                                */
} QEI_RELOADCFG_Type;

/**
 * @brief Filter Settings for QEI registers on PHA, PHB and IDX
 */

typedef struct
{
    uint32_t PHA_FilterVal;/**< Digital Filter Register on PHA input */
    uint32_t PHB_FilterVal;/**< Digital Filter Register on PHB input */
    uint32_t INX_FilterVal;/**< Digital Filter Register on IDX input */
} st_Qei_FilterCfg;


/**
 * @}
 */





/* Public Functions ----------------------------------------------------------- */
/** @defgroup QEI_Public_Functions QEI Public Functions
 * @{
 */

void QEI_Reset(uint8_t qeiId, uint32_t ulResetType);
void QEI_Init(uint8_t qeiId, QEI_CFG_Type *QEI_ConfigStruct);
void QEI_GetCfgDefault(QEI_CFG_Type *QIE_InitStruct);
void QEI_DeInit(uint8_t qeiId);
FlagStatus QEI_GetStatus(uint8_t qeiId, uint32_t ulFlagType);
uint32_t QEI_GetPosition(uint8_t qeiId);
void QEI_SetMaxPosition(uint8_t qeiId, uint32_t ulMaxPos);
void QEI_SetPositionComp(uint8_t qeiId, uint8_t bPosCompCh, uint32_t ulPosComp);
uint32_t QEI_GetIndex(uint8_t qeiId);
void QEI_SetIndexComp(uint8_t qeiId, uint32_t ulIndexComp);
void QEI_SetTimerReload(uint8_t qeiId, QEI_RELOADCFG_Type *QEIReloadStruct);
uint32_t QEI_GetTimer(uint8_t qeiId);
uint32_t QEI_GetVelocity(uint8_t qeiId);
uint32_t QEI_GetVelocityCap(uint8_t qeiId);
void QEI_SetVelocityComp(uint8_t qeiId, uint32_t ulVelComp);
void QEI_SetDigiFilter(uint8_t qeiId, st_Qei_FilterCfg FilterVal);
FlagStatus QEI_GetIntStatus(uint8_t qeiId, uint32_t ulIntType);
void QEI_IntCmd(uint8_t qeiId, uint32_t ulIntType, FunctionalState NewState);
void QEI_IntSet(uint8_t qeiId, uint32_t ulIntType);
void QEI_IntClear(uint8_t qeiId, uint32_t ulIntType);
uint32_t QEI_CalculateRPM(uint8_t qeiId, uint32_t ulVelCapValue, uint32_t ulPPR);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __LPC_QEI_H_ */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
