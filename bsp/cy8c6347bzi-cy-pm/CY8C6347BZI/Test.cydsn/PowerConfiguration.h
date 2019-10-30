/************************************************************************************************
 *
 * Filename: PowerConfiguration.h
 *
 * Version 1.00
 *
 * Configure CM0 and CM4 power mode.
 *
 ********************************************************************************
 * copyright
 * Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
 * You may use this file only in accordance with the license, terms, conditions,
 * disclaimers, and limitations in the end user license agreement accompanying
 * the software package with which this file was provided.
 *******************************************************************************/

#ifndef __POWER_CONFIGURATION_H__
#define __POWER_CONFIGURATION_H__

#define ACTIVE          (0)    
#define SLEEP           (1)
#define DEEPSLEEP       (2)
#define HIBERINATE      (3)
    
#define CM0_POWER_MODE     (SLEEP)   
#define CM4_POWER_MODE     (SLEEP)
    
#endif    
    
/* [] END OF FILE */
