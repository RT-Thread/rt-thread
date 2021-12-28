/*!
 *	 ----------------------PRELIMINARY VERSION--------------------------------
 *
 *   <b> COPYRIGHT(C) & copy; 2014-2015 Honeywell Inc. All rights reserved.</b>
 *
 *   This software is a copyrighted work and/or information protected as a
 *   trade secret. Legal rights of Honeywell Inc in this software is distinct
 *   from ownership of any medium in which the software is embodied. Copyright
 *   or trade secret notices included must be reproduced in any copy authorized
 *   by Honeywell Inc.  The information in this software is subject to change
 *   without notice and should not be considered as a commitment by Honeywell.
 *
 *   \file     Pressure_Comp.h
 *
 *   \brief    This contains the Pressure_Comp header file.
 *
 *   \details  Interface file providing interfaces to Pressure compensation
 *             Functions.
 *
 *   \author   Vikram Bhat
 *
 *   \date     15.12.2015
 *
 *   \version  \a 3.0
 *
 *      \li \a Version 3.0 -  Modifed the algorithm to accomodate Auto zero compensation.
 *      \li \a Version 2.0 -  Updated as per CER Comments.
 *      \li \a Version 1.0 -  Initial version.
 */

#ifndef PRESSURE_COMP_H
#define PRESSURE_COMP_H

/*
 -------------------------------------------------------------------------------
    Include Files
 -------------------------------------------------------------------------------
 */


/*
 -------------------------------------------------------------------------------
    List of defines
 -------------------------------------------------------------------------------
 */

/*! \def     BIG_ENDIAN_FORMAT
 *  \brief   Define "BIG_ENDIAN_FORMAT" macro for Big Endian format.
 *           define "LITTLE_ENDIAN_FORMAT" for Little Endian format.
 */
#define LITTLE_ENDIAN_FORMAT
//#define BIG_ENDIAN_FORMAT

/*
 -------------------------------------------------------------------------------
    Typedefinitions
 -------------------------------------------------------------------------------
 */

/*! \typedef  enum CompStatus_Enum_Tag
 *  \brief    Enumeration to hold Pressure Compensation status.
 */
typedef enum CompStatus_Enum_Tag
{
    COMPINIT_OK,            /*! Compensation init successful */
    COMPINIT_NOK,           /*! Compensation init failure */
    CRC_FAILURE,            /*! CRC Check Failure */
    IP_PRESSURE_OUTOFRANGE, /*! Input Pressure Out of Range */
    IP_TEMP_OUTOFRANGE,     /*! Input Temperature Out of Range */
    PRESSURE_VALID,         /*! Output Pressure Valid */
    PRESSURE_INVALID        /*! Output Pressure InValid */
}CompStatus_Enum;

/*! \typedef  enum CompReturn_Tag
 *  \brief    Structure returning Compensated Pressure and status .
 */
typedef struct CompReturn_Tag
{
    float f32PressureOutput;    /*! Compensated Pressure output */
    CompStatus_Enum CompStatus; /*! Status of Compensation */
}CompReturn_Struct;

/*
 -------------------------------------------------------------------------------
    Exported Function Declarations
 -------------------------------------------------------------------------------
 */

/*! \fn       Compensate_Pressure_Init
 *  \brief    Functional To Initialize the Compensate Pressure module.
 *  \details  Functional To Initialize the Compensate Pressure module,
 *            By validating EEPROM map and extracting the coeffecients.
 */
CompStatus_Enum Compensate_Pressure_Init(unsigned char *u8EEPROM_ptr);

/*! \fn       Compensate_Pressure
 *  \brief    Functional To Compensate Pressure.
 *  \details  Functional To Compensate Pressure based on Polynomial Correction.
 */
CompReturn_Struct Compensate_Pressure(unsigned long int u32PressureInput,unsigned long int u32Temperature);

/*! \fn       AutoZero_Pressure
 *  \brief    This functional is to Auto Zero Pressure.Upon trigger of this function the pressure
 *			  will be set to 50% full scale pressure.
 *			  Note: This function should only be called at known preset pressure that has to
 *                  be output as 50% Full scale pressure.
 *					Auto zero referred in these files refers to 50% fullscale pressure.
 *  \details  Functional to Auto Zero Pressure based on Pressure and Temperature inputs
 *			  captured at preset pressure state that needs to be output as zero.
 */
CompStatus_Enum AutoZero_Pressure(unsigned long int u32PressureZero,unsigned long int u32TemperatureZero);

#endif /*! PRESSURE_COMP_H */
