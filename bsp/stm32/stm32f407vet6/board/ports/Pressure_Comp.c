/*!
 *	 ----------------------PRELIMINARY VERSION--------------------------------
 *
 *   <b> COPYRIGHT(C) & copy; 2016-2017 Honeywell Inc. All rights reserved.</b>
 *
 *   This software is a copyrighted work and/or information protected as a
 *   trade secret. Legal rights of Honeywell Inc in this software is distinct
 *   from ownership of any medium in which the software is embodied. Copyright
 *   or trade secret notices included must be reproduced in any copy authorized
 *   by Honeywell Inc.  The information in this software is subject to change
 *   without notice and should not be considered as a commitment by Honeywell.
 *
 *   \file     Pressure_Comp.c
 *
 *   \brief    This source file will compensate uncompensated Pressure input.
 *
 *   \details  This file will be part of application build and provides
 *             implementation to compensate pressure trough Polynomial
 *             correction. The source fie contains two function one to initialize
 *             the module and another to Compensate the uncompensated pressure
 *             w.r.t Temperature read from TSUHR sensor.
 *
 *   \author   Vikram Bhat
 *
 *   \date     25.05.2016
 *
 *   \version  \a 5.0
 *
 *      \li \a Version 5.0 -  Modifed Engineering Offset Convention, Changed the Sign.
 *      \li \a Version 4.0 -  Modifed the algorithm to accomodate Auto zero compensation.
 *      \li \a Version 3.0 -  Updated math to have Full scale output followed
 *							  by range and offset corrected output.
 *      \li \a Version 2.0 -  Updated as per CER Comments.
 *      \li \a Version 1.0 -  Initial version.
 */

/*
 -------------------------------------------------------------------------------
    Include Files
 -------------------------------------------------------------------------------
 */

#include <float.h>
#include "Pressure_Comp.h"
#include "crc.h"
/*
 -------------------------------------------------------------------------------
    List of defines
 -------------------------------------------------------------------------------
 */

/*! \def     DEGREE_POLYNOMIAL
 *  \brief   Degree of polynomial correction applied
 */
#define DEGREE_POLYNOMIAL               4       /* For 3rd degree polynomial set 4 */

/*! \def
 *  \brief   Relative EEPROM address of Part Number
 */
#define PARTNUMBER_ADDRESS              0
#define SERIALNUMBER_ADDRESS            16
#define PRESSURERANGE_ADDRESS           27
#define PRESSUREOFFSET_ADDRESS          31
#define PRESSUREUNITS_ADDRESS           35
#define PRESSUREREFERENCE_ADDRESS       40
#define RESERVED_ADDRESS                41
#define ADCCONFIG_ADDRESS               60
#define COEFF1_ADDRESS                  130
#define COEFF2_ADDRESS                  210
#define COEFF3_ADDRESS                  290
#define CHECKSUM_ADDRESS                450
#define EEPROM_END_ADDRESS              451

/*! \def     Size
 *  \brief   Information on Element Size
 */
#define PART_NO_SIZE                    (SERIALNUMBER_ADDRESS - PARTNUMBER_ADDRESS)
#define SERIAL_NO_SIZE                  (PRESSURERANGE_ADDRESS - SERIALNUMBER_ADDRESS)
#define PRESSURE_UNIT_SIZE              (PRESSUREREFERENCE_ADDRESS - PRESSUREUNITS_ADDRESS)
#define RESERVED_SIZE                   (ADCCONFIG_ADDRESS - RESERVED_ADDRESS)

/*! \def     MAX_EEPROM_SIZE
 *  \brief   Maximum Number of EEPROM size in bytes
 */
#define MAX_EEPROM_SIZE                (EEPROM_END_ADDRESS + 1)

/*! \def     OP_PRESSURE_MIN
 *  \brief   Minimum value below which pressure is invalid
 */
#define OP_PRESSURE_MIN                 -0.10f

/*! \def     OP_PRESSURE_MAX
 *  \brief   Maximum value above which pressure is invalid
 */
#define OP_PRESSURE_MAX                 1.10f

/*! \def     DEFAULT_AUTOZERO
 *  \brief   Default value of Auto Zero offset
 */
#define DEFAULT_AUTOZERO				0.00f

/*! \def     READ8
 *  \brief   Read 8 bits of data
 */
#define READ8(address)                  ((unsigned char)(*(unsigned char*)(address)))

/*! \def     READ16_ADV, READ32_ADV
 *  \brief   Read 16,32 Bits of Address from memory.
 */
#ifdef LITTLE_ENDIAN_FORMAT
    #define READ16_ADV(addr)             ((unsigned short int)(((unsigned short int)READ8(addr+1)) << 8)|((READ8(addr) & 0x00FF)))
    #define READ32_ADV(addr)             ((unsigned long int)(((unsigned long int)READ16_ADV(addr+2)) << 16)|((READ16_ADV(addr) & 0x0000FFFF)))
#else
    #ifdef BIG_ENDIAN_FORMAT
        #define READ16_ADV(addr)             ((unsigned short int)(((unsigned short int)READ8(addr)) << 8)|((READ8(addr+1) & 0x00FF)))
        #define READ32_ADV(addr)             ((unsigned long int)(((unsigned long int)READ16_ADV(addr)) << 16)|((READ16_ADV(addr+2) & 0x0000FFFF)))
    #else
        #error "Endianness Not defined define either 'LITTLE_ENDIAN' or 'BIG_ENDIAN'"
    #endif
#endif

/*! \typedef  struct EEPROM_MAP_Tag
 *  \brief    Structure that hold EEPROM Memory Map.
 *            It also defines the required EEPROM elements in it.
 */
typedef struct EEPROM_MAP_Tag
{
  /* Intel/Motorola format not considered as there is no bit wise access */
    unsigned char au8PartNumber[PART_NO_SIZE];
    unsigned char au8SerialNumber[SERIAL_NO_SIZE];
    float   f32Pressure_Range;
    float   f32PressureOffset;
    unsigned char au8PressureUnit[PRESSURE_UNIT_SIZE];
    unsigned char u8PressureReference;
    unsigned char u8Reserved[RESERVED_SIZE];
    unsigned short int au16ADC_Config[4];
    float af32Coeff1[DEGREE_POLYNOMIAL];
    float af32Coeff2[DEGREE_POLYNOMIAL];
    float af32Coeff3[DEGREE_POLYNOMIAL];
    unsigned short int u16EepromChecksum;
}EEPROM_LAYOUT;

/*
 -------------------------------------------------------------------------------
     Global Variables
 -------------------------------------------------------------------------------
*/

/*! Structure variable to hold a copy of EEPROM contents */
static EEPROM_LAYOUT EEPROM_MAP;

/*! Static variable to hold the status of Compensation functionality */
static CompStatus_Enum eCompStatus = COMPINIT_NOK;

/*! Static variable to hold Return data & status of Compensation function */
static CompReturn_Struct strCompReturn = {0x0000, PRESSURE_INVALID};

/*! Static variable to hold Auto Zero Pressure Data */
static float f32PressureAutoZero = DEFAULT_AUTOZERO;

/*
 --------------------------------------------------------------------------------
    Global Function Definitions
 --------------------------------------------------------------------------------
 */

/*! \fn       Compensate_Pressure_Init
 *  \brief    Functional To Initialize the Compensate Pressure module.
 *  \details  Functional To Initialize the Compensate Pressure module,
 *            By validating EEPROM map and extracting the coefficients.
 *  \param    u8EEPROM_ptr  - Pointer to EEPROM image which is read bytewise
 *                            in a contiguous memory buffer.
 *  \return   CompStatus_Enum
 *                          COMPINIT_OK - Compensation init successful
 *                          COMPINIT_NOK - Compensation init failure
 *
 *  \verbatim
 *  \endverbatim
 */
CompStatus_Enum Compensate_Pressure_Init(unsigned char *u8EEPROM_ptr)
{
    unsigned char u8i;
    unsigned short int u16k = 0u;
    unsigned short int CRC16_Computed = 0xFFFF;
    unsigned long int u32temp;

    /*! Copy EEPROM Contents */
    /*! Copy Part number from EEPROM MAP */
    for(u8i = 0u; u8i < PART_NO_SIZE; u8i++)
    {
        EEPROM_MAP.au8PartNumber[u8i] = (unsigned char)*((unsigned char *)u8EEPROM_ptr + PARTNUMBER_ADDRESS + u8i);
    }

    /*! Copy Serial number from EEPROM MAP */
    for(u8i = 0u; u8i < SERIAL_NO_SIZE; u8i++)
    {
        EEPROM_MAP.au8SerialNumber[u8i] = (unsigned char)*((unsigned char *)u8EEPROM_ptr + SERIALNUMBER_ADDRESS + u8i);
    }

    /*! Copy Pressure Range from EEPROM MAP */
    u32temp = READ32_ADV((unsigned char *)u8EEPROM_ptr + PRESSURERANGE_ADDRESS);
    EEPROM_MAP.f32Pressure_Range = *((float*)&u32temp);

    /*! Copy Pressure Offset from EEPROM MAP */
    u32temp = READ32_ADV((unsigned char *)u8EEPROM_ptr + PRESSUREOFFSET_ADDRESS);
    EEPROM_MAP.f32PressureOffset = *((float*)&u32temp);

    /*! Copy Pressure unit from EEPROM MAP */
    for(u8i = 0u; u8i < PRESSURE_UNIT_SIZE; u8i++)
    {
        EEPROM_MAP.au8PressureUnit[u8i] = (unsigned char)*((unsigned char *)u8EEPROM_ptr + PRESSUREUNITS_ADDRESS + u8i);
    }

    /*! Copy Pressure reference from EEPROM MAP */
    EEPROM_MAP.u8PressureReference = (unsigned char)*((unsigned char *)u8EEPROM_ptr + PRESSUREREFERENCE_ADDRESS);

    /*! Copy ADC default configuration data from EEPROM MAP */
    for(u8i = 0u, u16k = 0u; u8i < 4u; u8i++, u16k += 2u)
    {
        EEPROM_MAP.au16ADC_Config[u8i] = (unsigned short int)READ16_ADV(((unsigned char *)u8EEPROM_ptr + ADCCONFIG_ADDRESS + u16k));
    }

    /*! Copy coefficients set 1 from EEPROM MAP */
    for(u8i = 0u, u16k = 0u; u8i < DEGREE_POLYNOMIAL; u8i++, u16k += 4u)
    {
        u32temp = READ32_ADV((unsigned char *)u8EEPROM_ptr + COEFF1_ADDRESS + u16k);
        EEPROM_MAP.af32Coeff1[u8i] = *((float*)&u32temp);
    }

    /*! Copy coefficients set 2 from EEPROM MAP */
    for(u8i = 0u, u16k = 0u; u8i < DEGREE_POLYNOMIAL; u8i++, u16k += 4u)
    {
        u32temp = READ32_ADV((unsigned char *)u8EEPROM_ptr + COEFF2_ADDRESS + u16k);
        EEPROM_MAP.af32Coeff2[u8i] = *((float*)&u32temp);
    }

    /*! Copy coefficients set 3 from EEPROM MAP */
    for(u8i = 0u, u16k = 0u; u8i < DEGREE_POLYNOMIAL; u8i++, u16k += 4u)
    {
        u32temp = READ32_ADV((unsigned char *)u8EEPROM_ptr + COEFF3_ADDRESS + u16k);
        EEPROM_MAP.af32Coeff3[u8i] = *((float*)&u32temp);
    }

    /*! Copy Stored Checksum from EEPROM MAP */
    EEPROM_MAP.u16EepromChecksum = (unsigned short int)READ16_ADV(((unsigned char *)u8EEPROM_ptr + CHECKSUM_ADDRESS));

    /*! Compute CRC checksum over entire EEPROM range */
    for(u16k = 0u; u16k < (MAX_EEPROM_SIZE - 2u); u16k++)
    {
        CRC16_Computed = CrcComputeCrc16(*(u8EEPROM_ptr + u16k), CRC16_Computed);
    }

    /*! Check whether the Computed CRC is same as the CRC stored in EEPROM */
    if(CRC16_Computed == EEPROM_MAP.u16EepromChecksum)
    {
        eCompStatus = COMPINIT_OK;
    }
    else
    {
        eCompStatus = COMPINIT_NOK;
    }
    /* Return the status of Compensation Init function */
    return(eCompStatus);
}

/*! \fn       Compensate_Pressure
 *  \brief    Functional To Compensate Pressure.
 *  \details  Functional To Compensate Pressure based on Polynomial correction.
 *  \param    u32PressureInput  - Input Uncompensated Pressure as read by TSHUR sensor.
 *            u32Temperature    - Input Temperature as read by TSHUR sensor.
 *  \return   CompReturn_Struct
 *              f32Pressureoutput - Compensated Pressure Output
 *              CompStatus        - Status of Compensation Correction
 *
 *  \verbatim
 *  \endverbatim
 */
CompReturn_Struct Compensate_Pressure(unsigned long int u32PressureInput,unsigned long int u32Temperature)
{
    float f32PressureCorrected1;
    float f32PressureCorrected2;
    float f32PressureCorrected3;
    float f32temp2;
    float f32temp3;
    float f32Denom;
    long int s32PressureInput = 0;
    long int s32Temperature = 0;

    /*! Copy the Status of Pressure Compensation Initialization */
    strCompReturn.CompStatus = eCompStatus;

    /*! check if Initialization is successful */
    if(strCompReturn.CompStatus == COMPINIT_OK)
    {
        /*! Format Pressure data */
        /*! Check if Pressure Input is outside 24bit Unsigned data boundary */
        if(u32PressureInput < 16777216u)
        {
            /*! If the Input Pressure is negative */
            /*! Check if Pressure Input falls in 24bit signed negative data boundary */
            if(u32PressureInput > 8388607u)
            {
                s32PressureInput = (u32PressureInput - 16777216u);
            }
            else
            {
                s32PressureInput = u32PressureInput;
            }
            /*! Format Temperature data */
            /*! Check if Temperature Input is outside 14bit Unsigned data boundary */
            if(u32Temperature < 16384u)
            {
                /*! If the Input Temperature is negative */
                /*! Check if Pressure Input falls in 14bit signed negative data boundary */
                if(u32Temperature > 8191u)
                {
                    s32Temperature = (u32Temperature - 16384u);
                }
                else
                {
                    s32Temperature = u32Temperature;
                }

                /*! Compute temporary values */
                f32temp2 = s32Temperature * s32Temperature;
                f32temp3 = f32temp2 * (float)s32Temperature;

                /*! Calculate the Pressure Corrected output 1 */
                f32PressureCorrected1 = (((float)s32PressureInput + f32PressureAutoZero) -
                                          ((EEPROM_MAP.af32Coeff1[3] * f32temp3) +
                                              (EEPROM_MAP.af32Coeff1[2] * f32temp2) +
                                                (EEPROM_MAP.af32Coeff1[1] * (float)s32Temperature) +
                                                    EEPROM_MAP.af32Coeff1[0]));

                f32Denom = ((EEPROM_MAP.af32Coeff2[3] * f32temp3) +
                              (EEPROM_MAP.af32Coeff2[2] * f32temp2) +
                                (EEPROM_MAP.af32Coeff2[1] * (float)s32Temperature) +
                                    EEPROM_MAP.af32Coeff2[0]);

                /*! Catch the Possibility of 0/0 Exception */
                if(f32Denom != 0.00f)
                {
                    /*! Calculate the Pressure Corrected output 2 */
                    f32PressureCorrected2 = (f32PressureCorrected1 / f32Denom);

                    /*! Compute temporary values */
                    f32temp2 = f32PressureCorrected2 * f32PressureCorrected2;
                    f32temp3 = f32temp2 * f32PressureCorrected2;

                    /*! Calculate the Pressure Corrected output 3 */
                    f32PressureCorrected3 = ((EEPROM_MAP.af32Coeff3[3] * f32temp3) +
                                              (EEPROM_MAP.af32Coeff3[2] * f32temp2) +
                                                (EEPROM_MAP.af32Coeff3[1] * f32PressureCorrected2) +
                                                    EEPROM_MAP.af32Coeff3[0]);

                    /*! Check if Output Pressure is within Range */
                    if((f32PressureCorrected3 > OP_PRESSURE_MIN)&&(f32PressureCorrected3 < OP_PRESSURE_MAX))
                    {
                        /*! Indicate Output Pressure is Valid */
                        strCompReturn.CompStatus = PRESSURE_VALID;
                    }/*! If Corrected Pressure within range */
                    else
                    {
                        /*! Indicate the Output Pressure is invalid */
                        strCompReturn.CompStatus = PRESSURE_INVALID;
                    }
                }/*! If Denominator is equal to 0 */
                else
                {
                    /*! Output a High value default value */
                    f32PressureCorrected3 = OP_PRESSURE_MAX + 0.01f;
                    /*! Indicate the Output Pressure is invalid */
                    strCompReturn.CompStatus = PRESSURE_INVALID;
                }

                /*! Convert the output data to Engineering units */
				strCompReturn.f32PressureOutput = ((f32PressureCorrected3 * EEPROM_MAP.f32Pressure_Range) + EEPROM_MAP.f32PressureOffset);

            }/*! if Temperature in Range */
            else
            {
                /*! Input Temperature data out of range */
                strCompReturn.CompStatus = IP_TEMP_OUTOFRANGE;
            }
        }/*! If Pressue in Range */
        else
        {
            /*! Input pressure data out of range */
            strCompReturn.CompStatus = IP_PRESSURE_OUTOFRANGE;
        }
    }/*! COMPINIT_OK */

    /*! Return the Compensated Pressure */
    return(strCompReturn);
}

/*! \fn       AutoZero_Pressure
 *  \brief    This functional is to Auto Zero Pressure.Upon trigger of this function the pressure
 *			  will be set to 50% full scale pressure.
 *			  Note: This function should only be called at known preset pressure that has to
 *                  be output as 50% Full scale pressure.
 *					Auto zero referred in these files refers to 50% fullscale pressure.
 *  \details  Functional to Auto Zero Pressure based on Pressure and Temperature inputs
 *			  captured at preset pressure state that needs to be output as zero.
 *  \param    u32PressureZero - Input uncompensated pressure as read by TSHUR sensor
 *								at preset 50% full scale pressure.
 *            u32TemperatureZero - Input temperature as read by TSHUR sensor
 *								   at preset autozero temperature.
 *  \return   CompStatus_Enum    - Status of Auto Zero Correction
 *
 *  \verbatim
 *  \endverbatim
 */
CompStatus_Enum AutoZero_Pressure(unsigned long int u32PressureZero,unsigned long int u32TemperatureZero)
{
    /*! Variable to hold the status of Compensation functionality */
    CompStatus_Enum eAZCompStatus;
    float f32AZtemp2;
    float f32AZtemp3;
    long int s32PressureZero = 0;
    long int s32TemperatureZero = 0;

    /*! Get the latest status of Pressure_Comp module */
    eAZCompStatus = eCompStatus;

	/*! Check if initialization is successful */
	if(eAZCompStatus == COMPINIT_OK)
	{
		/*! Format Pressure data */
		/*! Check if Pressure Input is outside 24bit Unsigned data boundary */
		if(u32PressureZero < 16777216u)
		{
			/*! If the Input Pressure is negative */
			/*! Check if Pressure Input falls in 24bit signed negative data boundary */
			if(u32PressureZero > 8388607u)
			{
				s32PressureZero = (u32PressureZero - 16777216u);
			}
			else
			{
				s32PressureZero = u32PressureZero;
			}
			/*! Format Temperature data */
			/*! Check if Temperature Input is outside 14bit Unsigned data boundary */
			if(u32TemperatureZero < 16384u)
			{
				/*! If the Input Temperature is negative */
				/*! Check if Pressure Input falls in 14bit signed negative data boundary */
				if(u32TemperatureZero > 8191u)
				{
					s32TemperatureZero = (u32TemperatureZero - 16384u);
				}
				else
				{
					s32TemperatureZero = u32TemperatureZero;
				}

				/*! Compute temporary values */
				f32AZtemp2 = s32TemperatureZero * s32TemperatureZero;
				f32AZtemp3 = f32AZtemp2 * (float)s32TemperatureZero;

				/*! Calculate the Auto Zero Pressure Corrected output */
				f32PressureAutoZero = (((EEPROM_MAP.af32Coeff1[3] * f32AZtemp3) +
											  (EEPROM_MAP.af32Coeff1[2] * f32AZtemp2) +
												(EEPROM_MAP.af32Coeff1[1] * (float)s32TemperatureZero) +
													EEPROM_MAP.af32Coeff1[0]) - (float)s32PressureZero);

            }/*! if Temperature in Range */
            else
            {
                /*! Input Temperature data out of range */
                eAZCompStatus = IP_TEMP_OUTOFRANGE;
            }
        }/*! If Pressue in Range */
        else
        {
            /*! Input pressure data out of range */
            eAZCompStatus = IP_PRESSURE_OUTOFRANGE;
        }
    }/*! COMPINIT_OK */

    /*! Return the Compensated Pressure */
    return(eAZCompStatus);
}
