/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file phd_device_spec.h
 *
 * @author
 *
 * @version
 *
 * @date June-16-2009

 * @brief This file contains macros and constants required by the various 
 *        device specializations
 *****************************************************************************/

#ifndef _PHD_DEVICE_SPEC_H
#define _PHD_DEVICE_SPEC_H

#include "types.h"
#if (defined LITTLE_ENDIAN)
#include "ieee11073_phd_types_kinetis.h"    /* IEEE11073 Data Structures */
#else
#include "ieee11073_phd_types.h"    /* IEEE11073 Data Structures */
#endif  
#include "ieee11073_nom_codes.h"    

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/

/* Weigh Scale */
#define PHD_WSL_CNFG_EVT_RPT_SIZE           166
#define PHD_WSL_DIM_GET_RSP_SIZE            114
#define PHD_WSL_DIM_DATA_TX_SIZE            94

/* Glucometer */
#define PHD_GLUCO_CNFG_EVT_RPT_SIZE         158
#define PHD_GLUCO_DIM_GET_RSP_SIZE          114
#define PHD_GLUCO_DIM_DATA_TX_SIZE          104

/* Blood pressure monitor */
#define PHD_BPM_CNFG_EVT_RPT_SIZE           152
#define PHD_BPM_DIM_GET_RSP_SIZE            114
#define PHD_BPM_DIM_DATA_TX_SIZE            66

/* Thermometer */
#define PHD_THERMO_CNFG_EVT_RPT_SIZE        72
#define PHD_THERMO_DIM_GET_RSP_SIZE         92
#define PHD_THERMO_DIM_DATA_TX_SIZE         46

/* pulse oximeter */
#define PHD_PULSE_CNFG_EVT_RPT_SIZE         172
#define PHD_PULSE_DIM_GET_RSP_SIZE          114
#define PHD_PULSE_DIM_DATA_TX_SIZE          58

/*****************************************************************************
 * Types
 *****************************************************************************/
#ifndef __HIWARE__
#pragma pack(1)
#endif

/* structure for the measurements that are changing */
typedef struct _phd_measurement
{
    AbsoluteTime msr_time;
    uint_16 weight[2];
    uint_16 bmi[2];
}PHD_MEASUREMENT, *PHD_MEASUREMENT_PTR;

#if defined(__CWCC__)
#pragma align_array_members off
#pragma options align=reset
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma pack()
#endif

/*****************************************************************************
 * Global variables 
 *****************************************************************************/  
extern uint_16 scanReportNo;
/*****************************************************************************
 * Global Functions - None
 *****************************************************************************/
#endif