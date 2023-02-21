/**
 ****************************************************************************************
 *
 * @file rwprf_config.h
 *
 * @brief Header file - Profile Configuration
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 ****************************************************************************************
 */


#ifndef _RWPRF_CONFIG_H_
#define _RWPRF_CONFIG_H_


/**
 ****************************************************************************************
 * @addtogroup PRF_CONFIG
 * @ingroup PROFILE
 * @brief Profile configuration
 *
 * @{
 ****************************************************************************************
 */

//ATT DB,Testing and Qualification related flags
#if (BLE_CENTRAL || BLE_PERIPHERAL)
/// Proximity Profile Monitor Role
#if defined(CFG_PRF_PXPM)
#define BLE_PROX_MONITOR        1
#else
#define BLE_PROX_MONITOR        0
#endif // defined(CFG_PRF_PXPM)

/// Proximity Profile Reporter Role
#if defined(CFG_PRF_PXPR)
#define BLE_PROX_REPORTER       1
#else
#define BLE_PROX_REPORTER       0
#endif // defined(CFG_PRF_PXPR)

///Find Me Profile Locator role
#if defined(CFG_PRF_FMPL)
#define BLE_FINDME_LOCATOR      1
#else
#define BLE_FINDME_LOCATOR      0
#endif // defined(CFG_PRF_FMPL)

///Find Me Profile Target role
#if defined(CFG_PRF_FMPT)
#define BLE_FINDME_TARGET       1
#else
#define BLE_FINDME_TARGET       0
#endif // defined(CFG_PRF_FMPT)

///Health Thermometer Profile Collector Role
#if defined(CFG_PRF_HTPC)
#define BLE_HT_COLLECTOR        1
#else
#define BLE_HT_COLLECTOR        0
#endif // defined(CFG_PRF_HTPC)

///Health Thermometer Profile Thermometer Role
#if defined(CFG_PRF_HTPT)
#define BLE_HT_THERMOM          1
#else
#define BLE_HT_THERMOM          0
#endif // defined(CFG_PRF_HTPT)

///Device Information Service Client Role
#if defined(CFG_PRF_DISC)
#define BLE_DIS_CLIENT          1
#else
#define BLE_DIS_CLIENT          0
#endif // defined(CFG_PRF_DISC)

///Device Information Service Server Role
#if defined(CFG_PRF_DISS)
#define BLE_DIS_SERVER          1
#else
#define BLE_DIS_SERVER          0
#endif // defined(CFG_PRF_DISS)

///Blood Pressure Profile Collector Role
#if defined(CFG_PRF_BLPC)
#define BLE_BP_COLLECTOR        1
#else
#define BLE_BP_COLLECTOR        0
#endif // defined(CFG_PRF_BLPC)

///Blood Pressure Profile Sensor Role
#if defined(CFG_PRF_BLPS)
#define BLE_BP_SENSOR           1
#else
#define BLE_BP_SENSOR           0
#endif // defined(CFG_PRF_BLPS)

///Time Profile Client Role
#if defined(CFG_PRF_TIPC)
#define BLE_TIP_CLIENT          1
#else
#define BLE_TIP_CLIENT          0
#endif // defined(CFG_PRF_TIPC)

///Time Profile Server Role
#if defined(CFG_PRF_TIPS)
#define BLE_TIP_SERVER          1
#else
#define BLE_TIP_SERVER          0
#endif // defined(CFG_PRF_TIPS)

///Heart Rate Profile Collector Role
#if defined(CFG_PRF_HRPC)
#define BLE_HR_COLLECTOR        1
#else
#define BLE_HR_COLLECTOR        0
#endif // defined(CFG_PRF_HRPC)

///Heart Rate Profile Sensor Role
#if defined(CFG_PRF_HRPS)
#define BLE_HR_SENSOR           1
#else
#define BLE_HR_SENSOR           0
#endif // defined(CFG_PRF_HRPS)

///Scan Parameter Profile Client Role
#if defined(CFG_PRF_SCPPC)
#define BLE_SP_CLIENT           1
#else
#define BLE_SP_CLIENT           0
#endif // defined(CFG_PRF_SCPPC)

///Scan Parameter Profile Server Role
#if defined(CFG_PRF_SCPPS)
#define BLE_SP_SERVER           1
#else
#define BLE_SP_SERVER           0
#endif // defined(CFG_PRF_SCPPS)

///Battery Service Client Role
#if defined(CFG_PRF_BASC)
#define BLE_BATT_CLIENT         1
#else
#define BLE_BATT_CLIENT         0
#endif // defined(CFG_PRF_BASC)

///Battery Service Server Role
#if defined(CFG_PRF_BASS)
#define BLE_BATT_SERVER         1
#else
#define BLE_BATT_SERVER         0
#endif // defined(CFG_PRF_BASS)

///HID Device Role
#if defined(CFG_PRF_HOGPD)
#define BLE_HID_DEVICE          1
#else
#define BLE_HID_DEVICE          0
#endif // defined(CFG_PRF_HOGPD)

///HID Boot Host Role
#if defined(CFG_PRF_HOGPBH)
#define BLE_HID_BOOT_HOST       1
#else
#define BLE_HID_BOOT_HOST       0
#endif // defined(CFG_PRF_HOGPBH)

///HID Report Host Role
#if defined(CFG_PRF_HOGPRH)
#define BLE_HID_REPORT_HOST     1
#else
#define BLE_HID_REPORT_HOST     0
#endif // defined(CFG_PRF_HOGPRH)

/// Glucose Profile Collector Role
#if defined(CFG_PRF_GLPC)
#define BLE_GL_COLLECTOR        1
#else
#define BLE_GL_COLLECTOR        0
#endif // defined(CFG_PRF_GLPC)

/// Glucose Profile Sensor Role
#if defined(CFG_PRF_GLPS)
#define BLE_GL_SENSOR           1
#else
#define BLE_GL_SENSOR           0
#endif // defined(CFG_PRF_GLPS)

/// Running Speed and Cadence Profile Collector Role
#if defined(CFG_PRF_RSCPC)
#define BLE_RSC_COLLECTOR       1
#else
#define BLE_RSC_COLLECTOR       0
#endif // defined(CFG_PRF_RSCPC)

/// Running Speed and Cadence Profile Server Role
#if defined(CFG_PRF_RSCPS)
#define BLE_RSC_SENSOR          1
#else
#define BLE_RSC_SENSOR          0
#endif // defined(CFG_PRF_RSCPS)

/// Cycling Speed and Cadence Profile Collector Role
#if defined(CFG_PRF_CSCPC)
#define BLE_CSC_COLLECTOR       1
#else
#define BLE_CSC_COLLECTOR       0
#endif // defined(CFG_PRF_CSCPC)

/// Cycling Speed and Cadence Profile Server Role
#if defined(CFG_PRF_CSCPS)
#define BLE_CSC_SENSOR          1
#else
#define BLE_CSC_SENSOR          0
#endif // defined(CFG_PRF_CSCPS)

/// Cycling Power Profile Collector Role
#if defined(CFG_PRF_CPPC)
#define BLE_CP_COLLECTOR        1
#else
#define BLE_CP_COLLECTOR        0
#endif // defined (CFG_PRF_CPPC)

/// Cycling Power Profile Server Role
#if defined(CFG_PRF_CPPS)
#define BLE_CP_SENSOR            1
#else
#define BLE_CP_SENSOR            0
#endif // defined (CFG_PRF_CPPS)

/// Location and Navigation Profile Collector Role
#if defined(CFG_PRF_LANC)
#define BLE_LN_COLLECTOR        1
#else
#define BLE_LN_COLLECTOR        0
#endif // defined (CFG_PRF_LANC)

/// Location and Navigation Profile Server Role
#if defined(CFG_PRF_LANS)
#define BLE_LN_SENSOR            1
#else
#define BLE_LN_SENSOR            0
#endif // defined (CFG_PRF_LANS)

/// Alert Notification Profile Client Role
#if defined(CFG_PRF_ANPC)
#define BLE_AN_CLIENT           1
#else
#define BLE_AN_CLIENT           0
#endif // defined(CFG_PRF_ANPC)

/// Alert Notification Profile Server Role
#if defined(CFG_PRF_ANPS)
#define BLE_AN_SERVER           1
#else
#define BLE_AN_SERVER           0
#endif // defined(CFG_PRF_ANPS)

/// Phone Alert Status Profile Client Role
#if defined(CFG_PRF_PASPC)
#define BLE_PAS_CLIENT          1
#else
#define BLE_PAS_CLIENT          0
#endif // defined(CFG_PRF_PASPC)

/// Phone Alert Status Profile Server Role
#if defined(CFG_PRF_PASPS)
#define BLE_PAS_SERVER          1
#else
#define BLE_PAS_SERVER          0
#endif // defined(CFG_PRF_PASPS)

/// Internet Protocol Support Profile Server Role
#if defined(CFG_PRF_IPSS)
#define BLE_IPS_SERVER          1
#else
#define BLE_IPS_SERVER          0
#endif // defined(CFG_PRF_IPSS)

/// Internet Protocol Support Profile Client Role
#if defined(CFG_PRF_IPSC)
#define BLE_IPS_CLIENT          1
#else
#define BLE_IPS_CLIENT          0
#endif // defined(CFG_PRF_IPSC)

/// Environmental Sensing Profile Server Role
#if defined(CFG_PRF_ENVS)
#define BLE_ENV_SERVER          1
#else
#define BLE_ENV_SERVER          0
#endif // defined(CFG_PRF_ENVS)

/// Environmental Sensing Profile Client Role
#if defined(CFG_PRF_ENVC)
#define BLE_ENV_CLIENT          1
#else
#define BLE_ENV_CLIENT          0
#endif // defined(CFG_PRF_ENVC)

/// Weight Scale Profile Server Role
#if defined(CFG_PRF_WSCS)
#define BLE_WSC_SERVER          1
#else
#define BLE_WSC_SERVER          0
#endif // defined(CFG_PRF_WSCS)

/// Weight Scale Profile Client Role
#if defined(CFG_PRF_WSCC)
#define BLE_WSC_CLIENT          1
#else
#define BLE_WSC_CLIENT          0
#endif // defined(CFG_PRF_WSCC)

/// Body Composition Server Role
#if defined(CFG_PRF_BCSS)
#define BLE_BCS_SERVER          1
#else
#define BLE_BCS_SERVER          0
#endif // defined(CFG_PRF_BCSS)

/// Body Composition Client Role
#if defined(CFG_PRF_BCSC)
#define BLE_BCS_CLIENT          1
#else
#define BLE_BCS_CLIENT          0
#endif // defined(CFG_PRF_BCSC)

/// User Data Service Server Role
#if defined(CFG_PRF_UDSS)
#define BLE_UDS_SERVER          1
#else
#define BLE_UDS_SERVER          0
#endif // defined(CFG_PRF_UDSS)

/// User Data Service Client Role
#if defined(CFG_PRF_UDSC)
#define BLE_UDS_CLIENT          1
#else
#define BLE_UDS_CLIENT          0
#endif // defined(CFG_PRF_UDSC)

/// Wireless Power Transfer Profile Server Role
#if defined(CFG_PRF_WPTS)
#define BLE_WPT_SERVER          1
#else
#define BLE_WPT_SERVER          0
#endif // defined(CFG_PRF_WPTS)

/// Wireless Power Transfer Profile Client Role
#if defined(CFG_PRF_WPTC)
#define BLE_WPT_CLIENT          1
#else
#define BLE_WPT_CLIENT          0
#endif // defined(CFG_PRF_WPTC)
///Health Thermometer Profile Thermometer Role
#if defined(CFG_APP_USER)
#define BLE_APP_SERVER        1
#else
#define BLE_APP_SERVER          0
#endif // defined(CFG_PRF_HTPT)
/// BLE_CLIENT_PRF indicates if at least one client profile is present
#if (BLE_PROX_MONITOR || BLE_FINDME_LOCATOR || BLE_HT_COLLECTOR || BLE_BP_COLLECTOR \
        || BLE_HR_COLLECTOR || BLE_DIS_CLIENT || BLE_TIP_CLIENT || BLE_SP_CLIENT \
        || BLE_BATT_CLIENT || BLE_GL_COLLECTOR || BLE_HID_BOOT_HOST || BLE_HID_REPORT_HOST \
        || BLE_RSC_COLLECTOR || BLE_CSC_COLLECTOR || BLE_CP_COLLECTOR || BLE_LN_COLLECTOR || BLE_AN_CLIENT \
        || BLE_PAS_CLIENT || BLE_IPS_CLIENT || BLE_ENV_CLIENT || BLE_WSC_CLIENT \
        || BLE_UDS_CLIENT || BLE_BCS_CLIENT || BLE_WPT_CLIENT)
#define BLE_CLIENT_PRF          1
#else
#define BLE_CLIENT_PRF          0
#endif //(BLE_PROX_MONITOR || BLE_FINDME_LOCATOR ...)

/// BLE_SERVER_PRF indicates if at least one server profile is present
#if (BLE_PROX_REPORTER || BLE_FINDME_TARGET || BLE_HT_THERMOM || BLE_BP_SENSOR \
        || BLE_TIP_SERVER || BLE_HR_SENSOR || BLE_DIS_SERVER || BLE_SP_SERVER \
        || BLE_BATT_SERVER || BLE_HID_DEVICE || BLE_GL_SENSOR || BLE_RSC_SENSOR  \
        || BLE_CSC_SENSOR || BLE_CP_SENSOR || BLE_LN_SENSOR || BLE_AN_SERVER \
        || BLE_PAS_SERVER || BLE_IPS_SERVER || BLE_ENV_SERVER || BLE_WSC_SERVER \
        || BLE_UDS_SERVER || BLE_BCS_SERVER || BLE_WPT_SERVER||BLE_APP_SERVER)
#define BLE_SERVER_PRF          1
#else
#define BLE_SERVER_PRF          0
#endif //(BLE_PROX_REPORTER || BLE_FINDME_TARGET ...)

//Force ATT parts depending on profile roles or compile options
/// Attribute Client
#if (BLE_CLIENT_PRF)
#define BLE_ATTC                    1
#endif //(BLE_CLIENT_PRF)

/// Attribute Server
#if (BLE_SERVER_PRF)
#define BLE_ATTS                    1
#endif //(BLE_SERVER_PRF)


#elif (BLE_OBSERVER || BLE_BROADCASTER)
/// Proximity Profile Monitor Role
#define BLE_PROX_MONITOR            0
/// Proximity Profile Reporter Role
#define BLE_PROX_REPORTER           0
///Find Me Profile Locator role
#define BLE_FINDME_LOCATOR          0
///Find Me Profile Target role
#define BLE_FINDME_TARGET           0
///Health Thermometer Profile Collector Role
#define BLE_HT_COLLECTOR            0
///Health Thermometer Profile Thermometer Role
#define BLE_HT_THERMOM              0
///Blood Pressure Profile Collector Role
#define BLE_BP_COLLECTOR            0
///Blood Pressure Profile Sensor Role
#define BLE_BP_SENSOR               0
///Heart Rate Profile Collector Role
#define BLE_HR_COLLECTOR            0
///Heart Rate Profile Sensor Role
#define BLE_HR_SENSOR               0
///Time Profile Client Role
#define BLE_TIP_CLIENT              0
///Time Profile Server Role
#define BLE_TIP_SERVER              0
/// Device Information Service Client Role
#define BLE_DIS_CLIENT              0
/// Device Information Service Server Role
#define BLE_DIS_SERVER              0
/// Scan Parameter Profile Client Role
#define BLE_SP_CLIENT               0
/// Scan Parameter Profile Server Role
#define BLE_SP_SERVER               0
/// Battery Service Client Role
#define BLE_BATT_CLIENT             0
/// Battery Service Server Role
#define BLE_BATT_SERVER             0
/// HID Device Role
#define BLE_HID_DEVICE              0
/// HID Boot Host Role
#define BLE_HID_BOOT_HOST           0
/// HID Report Host Role
#define BLE_HID_REPORT_HOST         0
/// Glucose Profile Collector Role
#define BLE_GL_COLLECTOR            0
/// Glucose Profile Sensor Role
#define BLE_GL_SENSOR               0
/// Running Speed and Cadence Collector Role
#define BLE_RSC_COLLECTOR           0
/// Running Speed and Cadence Server Role
#define BLE_RSC_SENSOR              0
/// Cycling Speed and Cadence Collector Role
#define BLE_CSC_COLLECTOR           0
/// Cycling Speed and Cadence Server Role
#define BLE_CSC_SENSOR              0
/// Cycling Power Collector Role
#define BLE_CP_COLLECTOR            0
/// Cycling Power Server Role
#define BLE_CP_SENSOR               0
/// Location and Navigation Collector Role
#define BLE_LN_COLLECTOR            0
/// Location and Navigation Server Role
#define BLE_LN_SENSOR               0
/// Alert Notification Client Role
#define BLE_AN_CLIENT               0
/// Alert Notification Server Role
#define BLE_AN_SERVER               0
/// Phone Alert Status Client Role
#define BLE_PAS_CLIENT              0
/// Phone Alert Status Server Role
#define BLE_PAS_SERVER              0
/// Internet Protocol Support Profile Server Role
#define BLE_IPS_SERVER              0
/// Internet Protocol Support Profile Client Role
#define BLE_IPS_CLIENT              0
/// Environmental Sensing Profile Server Role
#define BLE_ENV_SERVER              0
/// Environmental Sensing Profile Client Role
#define BLE_ENV_CLIENT              0
/// Weight Scale Profile Server Role
#define BLE_WSC_SERVER              0
/// Weight Scale Profile Client Role
#define BLE_WSC_CLIENT              0
/// Body Composition Profile Client Role
#define BLE_BCS_CLIENT          0
/// Body Composition Profile Server Role
#define BLE_BCS_SERVER          0
/// User Data Service Server Role
#define BLE_UDS_SERVER              0
/// User Data Service Client Role
#define BLE_UDS_CLIENT              0
/// Wireless Power Transfer Profile Server Role
#define BLE_WPT_SERVER              0
/// Wireless Power Transfer Profile Client Role
#define BLE_WPT_CLIENT              0

//Force ATT parts to 0
/// External database management
#define BLE_EXT_ATTS_DB             0
/// Profile Server
#define BLE_SERVER_PRF              0
/// Profile Client
#define BLE_CLIENT_PRF              0
#endif //(BLE_OBSERVER || BLE_BROADCASTER)


/// @} PRF_CONFIG

#endif /* _RWPRF_CONFIG_H_ */
