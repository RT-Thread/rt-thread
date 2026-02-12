/**
 ****************************************************************************************
 *
 * @file att.h
 *
 * @brief Header file - ATT.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef ATT_H_
#define ATT_H_

/**
 ****************************************************************************************
 * @addtogroup ATT Attribute Protocol
 * @ingroup HOST
 * @brief Attribute Protocol.
 *
 * The ATT block contains the procedures for discovering, reading, writing
 * and indicating attributes to peer device . It also defines a number of items
 * that caters to the security aspect of the block as access to some information
 * may require both authorization and an authenticated and encrypted physical
 * link before an attribute can be read or written
 *
 * @{
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/// Macro used to convert CPU integer define to LSB first 16-bits UUID
#define ATT_UUID_16(uuid)                          (uuid)

/// Invalid attribute handle
#define ATT_INVALID_HDL                            (0x0000)
/// Invalid attribute idx (used for profiles)
#define ATT_INVALID_IDX                            (0xff)

#define ATT_1ST_REQ_START_HDL                      0x0001
#define ATT_1ST_REQ_END_HDL                        0xFFFF

/// Maximum possible attribute handle
#define ATT_MAX_ATTR_HDL                           ATT_1ST_REQ_END_HDL

/// Offset of value in signed PDU
#define ATT_SIGNED_PDU_VAL_OFFSET               0x03

/// Attribute Features
#define ATT_SERVER_CONFIG                       0x0001
#define ATT_SERVICE_DISC                        0x0002
#define ATT_RELATIONSHIP_DISC                   0x0004
#define ATT_CHAR_DISC                           0x0008
#define ATT_CHAR_DESC_DISC                      0x0010
#define ATT_RD_CHAR_VALUE                       0x0020
#define ATT_WR_CHAR_VALUE                       0x0040
#define ATT_NOTIF_CHAR_VALUE                    0x0080
#define ATT_IND_CHAR_VALUE                      0x0100
#define ATT_RD_CHAR_DESC                        0x0200
#define ATT_WR_CHAR_DESC                        0x0400

/// Length, number, offset defines
#define ATT_SVC_VALUE_MAX_LEN                   0x0030
#define ATT_CHAR_NAME_MAX_LEN                   0x0030
#define ATT_UUID_16_LEN                         0x0002
#define ATT_UUID_32_LEN                         0x0004
#define ATT_UUID_128_LEN                        0x0010

/// offset - l2cap header and ATT code
#define ATT_PDU_DATA_OFFSET                     0x05

/// Characteristic Properties Bit
#define ATT_CHAR_PROP_BCAST                     0x01
#define ATT_CHAR_PROP_RD                        0x02
#define ATT_CHAR_PROP_WR_NO_RESP                0x04
#define ATT_CHAR_PROP_WR                        0x08
#define ATT_CHAR_PROP_NTF                       0x10
#define ATT_CHAR_PROP_IND                       0x20
#define ATT_CHAR_PROP_AUTH                      0x40
#define ATT_CHAR_PROP_EXT_PROP                  0x80
/// Invalid Attribute Handle
#define ATT_INVALID_SEARCH_HANDLE               0x0000
#define ATT_INVALID_HANDLE                      0x0000
/// Read Information Request
#define ATT_UUID_FILTER_0                       0x00
#define ATT_UUID_FILTER_2                       0x02
#define ATT_UUID_FILTER_16                      0x10
/// Read Information Response
#define ATT_FORMAT_LEN                          0x0001
#define ATT_FORMAT_16BIT_UUID                   0x01
#define ATT_FORMAT_128BIT_UUID                  0x02
/// For No fix length PDU
#define ATT_HANDLE_LEN                          0x0002
#define ATT_EACHLEN_LEN                         0x0001
#define ATT_PROP_LEN                            0x0001
#define ATT_CODE_LEN                            0x0001
#define ATT_CODE_AND_DATA_LEN                   0x0002
#define ATT_CODE_AND_HANDLE_LEN                 0x0003
#define ATT_CODE_AND_HANDLE_LEN_AND_OFFSET      0x0005
#define ATT_SIGNATURE_LEN                       0x0C

/// extended characteristics
#define ATT_EXT_RELIABLE_WRITE                  0x0001
#define ATT_EXT_WRITABLE_AUX                    0x0002
#define ATT_EXT_RFU                             0xFFFC

/// PDU size for error response
#define ATT_ERROR_RESP_LEN                      0x05

/// Offset of value in signed PDU
#define ATT_SIGNED_PDU_VAL_OFFSET               0x03



#define ATT_BT_UUID_128 {0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80, \
                          0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}



/* Attribute Specification Defines */

/// Common 16-bit Universal Unique Identifier
enum {
    ATT_INVALID_UUID                            = ATT_UUID_16(0x0000),
    /*----------------- SERVICES ---------------------*/
    /// Generic Access Profile
    ATT_SVC_GENERIC_ACCESS                      = ATT_UUID_16(0x1800),
    /// Attribute Profile
    ATT_SVC_GENERIC_ATTRIBUTE                   = ATT_UUID_16(0x1801),
    /// Immediate alert Service
    ATT_SVC_IMMEDIATE_ALERT                     = ATT_UUID_16(0x1802),
    /// Link Loss Service
    ATT_SVC_LINK_LOSS                           = ATT_UUID_16(0x1803),
    /// Tx Power Service
    ATT_SVC_TX_POWER                            = ATT_UUID_16(0x1804),
    /// Current Time Service Service
    ATT_SVC_CURRENT_TIME                        = ATT_UUID_16(0x1805),
    /// Reference Time Update Service
    ATT_SVC_REF_TIME_UPDATE                     = ATT_UUID_16(0x1806),
    /// Next DST Change Service
    ATT_SVC_NEXT_DST_CHANGE                     = ATT_UUID_16(0x1807),
    /// Glucose Service
    ATT_SVC_GLUCOSE                             = ATT_UUID_16(0x1808),
    /// Health Thermometer Service
    ATT_SVC_HEALTH_THERMOM                      = ATT_UUID_16(0x1809),
    /// Device Information Service
    ATT_SVC_DEVICE_INFO                         = ATT_UUID_16(0x180A),
    /// Heart Rate Service
    ATT_SVC_HEART_RATE                          = ATT_UUID_16(0x180D),
    /// Phone Alert Status Service
    ATT_SVC_PHONE_ALERT_STATUS                  = ATT_UUID_16(0x180E),
    /// Battery Service
    ATT_SVC_BATTERY_SERVICE                     = ATT_UUID_16(0x180F),
    /// Blood Pressure Service
    ATT_SVC_BLOOD_PRESSURE                      = ATT_UUID_16(0x1810),
    /// Alert Notification Service
    ATT_SVC_ALERT_NTF                           = ATT_UUID_16(0x1811),
    /// HID Service
    ATT_SVC_HID                                 = ATT_UUID_16(0x1812),
    /// Scan Parameters Service
    ATT_SVC_SCAN_PARAMETERS                     = ATT_UUID_16(0x1813),
    /// Running Speed and Cadence Service
    ATT_SVC_RUNNING_SPEED_CADENCE               = ATT_UUID_16(0x1814),
    /// Cycling Speed and Cadence Service
    ATT_SVC_CYCLING_SPEED_CADENCE               = ATT_UUID_16(0x1816),
    /// Cycling Power Service
    ATT_SVC_CYCLING_POWER                       = ATT_UUID_16(0x1818),
    /// Location and Navigation Service
    ATT_SVC_LOCATION_AND_NAVIGATION             = ATT_UUID_16(0x1819),
    /// Environmental Sensing Service
    ATT_SVC_ENVIRONMENTAL_SENSING               = ATT_UUID_16(0x181A),
    /// Body Composition Service
    ATT_SVC_BODY_COMPOSITION                    = ATT_UUID_16(0x181B),
    /// User Data Service
    ATT_SVC_USER_DATA                           = ATT_UUID_16(0x181C),
    /// Weight Scale Service
    ATT_SVC_WEIGHT_SCALE                        = ATT_UUID_16(0x181D),
    /// Bond Management Service
    ATT_SVC_BOND_MANAGEMENT                     = ATT_UUID_16(0x181E),
    /// Continuous Glucose Monitoring Service
    ATT_SVC_CONTINUOUS_GLUCOSE_MONITORING       = ATT_UUID_16(0x181F),
    /// Internet Protocol Support Service
    ATT_SVC_IP_SUPPORT                          = ATT_UUID_16(0x1820),
    /// Indoor Positioning Service
    ATT_SVC_INDOOR_POSITIONING                  = ATT_UUID_16(0x1821),
    /// Pulse Oximeter Service
    ATT_SVC_PULSE_OXIMETER                      = ATT_UUID_16(0x1822),
    /// HTTP Proxy Service
    ATT_SVC_HTTP_PROXY                          = ATT_UUID_16(0x1823),
    /// Transport Discovery Service
    ATT_SVC_TRANSPORT_DISCOVERY                 = ATT_UUID_16(0x1824),
    /// Object Transfer Service
    ATT_SVC_OBJECT_TRANSFER                     = ATT_UUID_16(0x1825),
    //USER-DEFINED by wq
    ATT_SVC_DATA_TRANSFER                       = ATT_UUID_16(0xFF00),

    /*------------------- UNITS ---------------------*/
    /// No defined unit
    ATT_UNIT_UNITLESS                           = ATT_UUID_16(0x2700),
    /// Length Unit - Metre
    ATT_UNIT_METRE                              = ATT_UUID_16(0x2701),
    ///Mass unit - Kilogram
    ATT_UNIT_KG                                 = ATT_UUID_16(0x2702),
    ///Time unit - second
    ATT_UNIT_SECOND                             = ATT_UUID_16(0x2703),
    ///Electric current unit - Ampere
    ATT_UNIT_AMPERE                             = ATT_UUID_16(0x2704),
    ///Thermodynamic Temperature unit - Kelvin
    ATT_UNIT_KELVIN                             = ATT_UUID_16(0x2705),
    /// Amount of substance unit - mole
    ATT_UNIT_MOLE                               = ATT_UUID_16(0x2706),
    ///Luminous intensity unit - candela
    ATT_UNIT_CANDELA                            = ATT_UUID_16(0x2707),
    ///Area unit - square metres
    ATT_UNIT_SQ_METRE                           = ATT_UUID_16(0x2710),
    ///Colume unit - cubic metres
    ATT_UNIT_CUBIC_METRE                        = ATT_UUID_16(0x2710),
    ///Velocity unit - metres per second
    ATT_UNIT_METRE_PER_SECOND                   = ATT_UUID_16(0x2711),
    ///Acceleration unit - metres per second squared
    ATT_UNIT_METRES_PER_SEC_SQ                  = ATT_UUID_16(0x2712),
    ///Wavenumber unit - reciprocal metre
    ATT_UNIT_RECIPROCAL_METRE                   = ATT_UUID_16(0x2713),
    ///Density unit - kilogram per cubic metre
    ATT_UNIT_DENS_KG_PER_CUBIC_METRE            = ATT_UUID_16(0x2714),
    ///Surface density unit - kilogram per square metre
    ATT_UNIT_KG_PER_SQ_METRE                    = ATT_UUID_16(0x2715),
    ///Specific volume unit - cubic metre per kilogram
    ATT_UNIT_CUBIC_METRE_PER_KG                 = ATT_UUID_16(0x2716),
    ///Current density unit - ampere per square metre
    ATT_UNIT_AMPERE_PER_SQ_METRE                = ATT_UUID_16(0x2717),
    ///Magnetic field strength unit - Ampere per metre
    ATT_UNIT_AMPERE_PER_METRE                   = ATT_UUID_16(0x2718),
    ///Amount concentration unit - mole per cubic metre
    ATT_UNIT_MOLE_PER_CUBIC_METRE               = ATT_UUID_16(0x2719),
    ///Mass Concentration unit - kilogram per cubic metre
    ATT_UNIT_MASS_KG_PER_CUBIC_METRE            = ATT_UUID_16(0x271A),
    ///Luminance unit - candela per square metre
    ATT_UNIT_CANDELA_PER_SQ_METRE               = ATT_UUID_16(0x271B),
    ///Refractive index unit
    ATT_UNIT_REFRACTIVE_INDEX                   = ATT_UUID_16(0x271C),
    ///Relative permeability unit
    ATT_UNIT_RELATIVE_PERMEABILITY              = ATT_UUID_16(0x271D),
    ///Plane angle unit - radian
    ATT_UNIT_RADIAN                             = ATT_UUID_16(0x2720),
    ///Solid angle unit - steradian
    ATT_UNIT_STERADIAN                          = ATT_UUID_16(0x2721),
    ///Frequency unit - Hertz
    ATT_UNIT_HERTZ                              = ATT_UUID_16(0x2722),
    ///Force unit - Newton
    ATT_UNIT_NEWTON                             = ATT_UUID_16(0x2723),
    ///Pressure unit - Pascal
    ATT_UNIT_PASCAL                             = ATT_UUID_16(0x2724),
    ///Energy unit - Joule
    ATT_UNIT_JOULE                              = ATT_UUID_16(0x2725),
    ///Power unit - Watt
    ATT_UNIT_WATT                               = ATT_UUID_16(0x2726),
    ///electric Charge unit - Coulomb
    ATT_UNIT_COULOMB                            = ATT_UUID_16(0x2727),
    ///Electric potential difference - Volt
    ATT_UNIT_VOLT                               = ATT_UUID_16(0x2728),
    ///Capacitance unit - Farad
    ATT_UNIT_FARAD                              = ATT_UUID_16(0x2729),
    ///electric resistance unit - Ohm
    ATT_UNIT_OHM                                = ATT_UUID_16(0x272A),
    ///Electric conductance - Siemens
    ATT_UNIT_SIEMENS                            = ATT_UUID_16(0x272B),
    ///Magnetic flux unit - Weber
    ATT_UNIT_WEBER                              = ATT_UUID_16(0x272C),
    ///Magnetic flux density unit - Tesla
    ATT_UNIT_TESLA                              = ATT_UUID_16(0x272D),
    ///Inductance unit - Henry
    ATT_UNIT_HENRY                              = ATT_UUID_16(0x272E),
    ///Temperature unit - degree Celsius
    ATT_UNIT_CELSIUS                            = ATT_UUID_16(0x272F),
    ///Luminous flux unit - lumen
    ATT_UNIT_LUMEN                              = ATT_UUID_16(0x2730),
    ///Illuminance unit - lux
    ATT_UNIT_LUX                                = ATT_UUID_16(0x2731),
    ///Activity referred to a radionuclide unit - becquerel
    ATT_UNIT_BECQUEREL                          = ATT_UUID_16(0x2732),
    ///Absorbed dose unit - Gray
    ATT_UNIT_GRAY                               = ATT_UUID_16(0x2733),
    ///Dose equivalent unit - Sievert
    ATT_UNIT_SIEVERT                            = ATT_UUID_16(0x2734),
    ///Catalytic activity unit - Katal
    ATT_UNIT_KATAL                              = ATT_UUID_16(0x2735),
    ///Synamic viscosity unit - Pascal second
    ATT_UNIT_PASCAL_SECOND                      = ATT_UUID_16(0x2740),
    ///Moment of force unit - Newton metre
    ATT_UNIT_NEWTON_METRE                       = ATT_UUID_16(0x2741),
    ///surface tension unit - Newton per metre
    ATT_UNIT_NEWTON_PER_METRE                   = ATT_UUID_16(0x2742),
    ///Angular velocity unit - radian per second
    ATT_UNIT_RADIAN_PER_SECOND                  = ATT_UUID_16(0x2743),
    ///Angular acceleration unit - radian per second squared
    ATT_UNIT_RADIAN_PER_SECOND_SQ               = ATT_UUID_16(0x2744),
    ///Heat flux density unit - Watt per square metre
    ATT_UNIT_WATT_PER_SQ_METRE                  = ATT_UUID_16(0x2745),
    ///HEat capacity unit - Joule per Kelvin
    ATT_UNIT_JOULE_PER_KELVIN                   = ATT_UUID_16(0x2746),
    ///Specific heat capacity unit - Joule per kilogram kelvin
    ATT_UNIT_JOULE_PER_KG_KELVIN                = ATT_UUID_16(0x2747),
    ///Specific Energy unit - Joule per kilogram
    ATT_UNIT_JOULE_PER_KG                       = ATT_UUID_16(0x2748),
    ///Thermal conductivity - Watt per metre Kelvin
    ATT_UNIT_WATT_PER_METRE_KELVIN              = ATT_UUID_16(0x2749),
    ///Energy Density unit - joule per cubic metre
    ATT_UNIT_JOULE_PER_CUBIC_METRE              = ATT_UUID_16(0x274A),
    ///Electric field strength unit - volt per metre
    ATT_UNIT_VOLT_PER_METRE                     = ATT_UUID_16(0x274B),
    ///Electric charge density unit - coulomb per cubic metre
    ATT_UNIT_COULOMB_PER_CUBIC_METRE            = ATT_UUID_16(0x274C),
    ///Surface charge density unit - coulomb per square metre
    ATT_UNIT_SURF_COULOMB_PER_SQ_METRE          = ATT_UUID_16(0x274D),
    ///Electric flux density unit - coulomb per square metre
    ATT_UNIT_FLUX_COULOMB_PER_SQ_METRE          = ATT_UUID_16(0x274E),
    ///Permittivity unit - farad per metre
    ATT_UNIT_FARAD_PER_METRE                    = ATT_UUID_16(0x274F),
    ///Permeability unit - henry per metre
    ATT_UNIT_HENRY_PER_METRE                    = ATT_UUID_16(0x2750),
    ///Molar energy unit - joule per mole
    ATT_UNIT_JOULE_PER_MOLE                     = ATT_UUID_16(0x2751),
    ///Molar entropy unit - joule per mole kelvin
    ATT_UNIT_JOULE_PER_MOLE_KELVIN              = ATT_UUID_16(0x2752),
    ///Exposure unit - coulomb per kilogram
    ATT_UNIT_COULOMB_PER_KG                     = ATT_UUID_16(0x2753),
    ///Absorbed dose rate unit - gray per second
    ATT_UNIT_GRAY_PER_SECOND                    = ATT_UUID_16(0x2754),
    ///Radiant intensity unit - watt per steradian
    ATT_UNIT_WATT_PER_STERADIAN                 = ATT_UUID_16(0x2755),
    ///Radiance unit - watt per square meter steradian
    ATT_UNIT_WATT_PER_SQ_METRE_STERADIAN        = ATT_UUID_16(0x2756),
    ///Catalytic activity concentration unit - katal per cubic metre
    ATT_UNIT_KATAL_PER_CUBIC_METRE              = ATT_UUID_16(0x2757),
    ///Time unit - minute
    ATT_UNIT_MINUTE                             = ATT_UUID_16(0x2760),
    ///Time unit - hour
    ATT_UNIT_HOUR                               = ATT_UUID_16(0x2761),
    ///Time unit - day
    ATT_UNIT_DAY                                = ATT_UUID_16(0x2762),
    ///Plane angle unit - degree
    ATT_UNIT_ANGLE_DEGREE                       = ATT_UUID_16(0x2763),
    ///Plane angle unit - minute
    ATT_UNIT_ANGLE_MINUTE                       = ATT_UUID_16(0x2764),
    ///Plane angle unit - second
    ATT_UNIT_ANGLE_SECOND                       = ATT_UUID_16(0x2765),
    ///Area unit - hectare
    ATT_UNIT_HECTARE                            = ATT_UUID_16(0x2766),
    ///Volume unit - litre
    ATT_UNIT_LITRE                              = ATT_UUID_16(0x2767),
    ///Mass unit - tonne
    ATT_UNIT_TONNE                              = ATT_UUID_16(0x2768),
    ///Pressure unit - bar
    ATT_UNIT_BAR                                = ATT_UUID_16(0x2780),
    ///Pressure unit - millimetre of mercury
    ATT_UNIT_MM_MERCURY                         = ATT_UUID_16(0x2781),
    ///Length unit - angstrom
    ATT_UNIT_ANGSTROM                           = ATT_UUID_16(0x2782),
    ///Length unit - nautical mile
    ATT_UNIT_NAUTICAL_MILE                      = ATT_UUID_16(0x2783),
    ///Area unit - barn
    ATT_UNIT_BARN                               = ATT_UUID_16(0x2784),
    ///Velocity unit - knot
    ATT_UNIT_KNOT                               = ATT_UUID_16(0x2785),
    ///Logarithmic radio quantity unit - neper
    ATT_UNIT_NEPER                              = ATT_UUID_16(0x2786),
    ///Logarithmic radio quantity unit - bel
    ATT_UNIT_BEL                                = ATT_UUID_16(0x2787),
    ///Length unit - yard
    ATT_UNIT_YARD                               = ATT_UUID_16(0x27A0),
    ///Length unit - parsec
    ATT_UNIT_PARSEC                             = ATT_UUID_16(0x27A1),
    ///length unit - inch
    ATT_UNIT_INCH                               = ATT_UUID_16(0x27A2),
    ///length unit - foot
    ATT_UNIT_FOOT                               = ATT_UUID_16(0x27A3),
    ///length unit - mile
    ATT_UNIT_MILE                               = ATT_UUID_16(0x27A4),
    ///pressure unit - pound-force per square inch
    ATT_UNIT_POUND_FORCE_PER_SQ_INCH            = ATT_UUID_16(0x27A5),
    ///velocity unit - kilometre per hour
    ATT_UNIT_KM_PER_HOUR                        = ATT_UUID_16(0x27A6),
    ///velocity unit - mile per hour
    ATT_UNIT_MILE_PER_HOUR                      = ATT_UUID_16(0x27A7),
    ///angular velocity unit - revolution per minute
    ATT_UNIT_REVOLUTION_PER_MINUTE              = ATT_UUID_16(0x27A8),
    ///energy unit - gram calorie
    ATT_UNIT_GRAM_CALORIE                       = ATT_UUID_16(0x27A9),
    ///energy unit - kilogram calorie
    ATT_UNIT_KG_CALORIE                         = ATT_UUID_16(0x27AA),
    /// energy unit - kilowatt hour
    ATT_UNIT_KILOWATT_HOUR                      = ATT_UUID_16(0x27AB),
    ///thermodynamic temperature unit - degree Fahrenheit
    ATT_UNIT_FAHRENHEIT                         = ATT_UUID_16(0x27AC),
    ///percentage
    ATT_UNIT_PERCENTAGE                         = ATT_UUID_16(0x27AD),
    ///per mille
    ATT_UNIT_PER_MILLE                          = ATT_UUID_16(0x27AE),
    ///period unit - beats per minute)
    ATT_UNIT_BEATS_PER_MINUTE                   = ATT_UUID_16(0x27AF),
    ///electric charge unit - ampere hours
    ATT_UNIT_AMPERE_HOURS                       = ATT_UUID_16(0x27B0),
    ///mass density unit - milligram per decilitre
    ATT_UNIT_MILLIGRAM_PER_DECILITRE            = ATT_UUID_16(0x27B1),
    ///mass density unit - millimole per litre
    ATT_UNIT_MILLIMOLE_PER_LITRE                = ATT_UUID_16(0x27B2),
    ///time unit - year
    ATT_UNIT_YEAR                               = ATT_UUID_16(0x27B3),
    ////time unit - month
    ATT_UNIT_MONTH                              = ATT_UUID_16(0x27B4),


    /*---------------- DECLARATIONS -----------------*/
    /// Primary service Declaration
    ATT_DECL_PRIMARY_SERVICE                     = ATT_UUID_16(0x2800),
    /// Secondary service Declaration
    ATT_DECL_SECONDARY_SERVICE                   = ATT_UUID_16(0x2801),
    /// Include Declaration
    ATT_DECL_INCLUDE                             = ATT_UUID_16(0x2802),
    /// Characteristic Declaration
    ATT_DECL_CHARACTERISTIC                      = ATT_UUID_16(0x2803),


    /*----------------- DESCRIPTORS -----------------*/
    /// Characteristic extended properties
    ATT_DESC_CHAR_EXT_PROPERTIES                 = ATT_UUID_16(0x2900),
    /// Characteristic user description
    ATT_DESC_CHAR_USER_DESCRIPTION               = ATT_UUID_16(0x2901),
    /// Client characteristic configuration
    ATT_DESC_CLIENT_CHAR_CFG                     = ATT_UUID_16(0x2902),
    /// Server characteristic configuration
    ATT_DESC_SERVER_CHAR_CFG                     = ATT_UUID_16(0x2903),
    /// Characteristic Presentation Format
    ATT_DESC_CHAR_PRES_FORMAT                    = ATT_UUID_16(0x2904),
    /// Characteristic Aggregate Format
    ATT_DESC_CHAR_AGGREGATE_FORMAT               = ATT_UUID_16(0x2905),
    /// Valid Range
    ATT_DESC_VALID_RANGE                         = ATT_UUID_16(0x2906),
    /// External Report Reference
    ATT_DESC_EXT_REPORT_REF                      = ATT_UUID_16(0x2907),
    /// Report Reference
    ATT_DESC_REPORT_REF                          = ATT_UUID_16(0x2908),
    /// Environmental Sensing Configuration
    ATT_DESC_ES_CONFIGURATION                    = ATT_UUID_16(0x290B),
    /// Environmental Sensing Measurement
    ATT_DESC_ES_MEASUREMENT                      = ATT_UUID_16(0x290C),
    /// Environmental Sensing Trigger Setting
    ATT_DESC_ES_TRIGGER_SETTING                  = ATT_UUID_16(0x290D),


    /*--------------- CHARACTERISTICS ---------------*/
    /// Device name
    ATT_CHAR_DEVICE_NAME                        = ATT_UUID_16(0x2A00),
    /// Appearance
    ATT_CHAR_APPEARANCE                         = ATT_UUID_16(0x2A01),
    /// Privacy flag
    ATT_CHAR_PRIVACY_FLAG                       = ATT_UUID_16(0x2A02),
    /// Reconnection address
    ATT_CHAR_RECONNECTION_ADDR                  = ATT_UUID_16(0x2A03),
    /// Peripheral preferred connection parameters
    ATT_CHAR_PERIPH_PREF_CON_PARAM              = ATT_UUID_16(0x2A04),
    /// Service handles changed
    ATT_CHAR_SERVICE_CHANGED                    = ATT_UUID_16(0x2A05),
    /// Alert Level characteristic
    ATT_CHAR_ALERT_LEVEL                        = ATT_UUID_16(0x2A06),
    /// Tx Power Level
    ATT_CHAR_TX_POWER_LEVEL                     = ATT_UUID_16(0x2A07),
    /// Date Time
    ATT_CHAR_DATE_TIME                          = ATT_UUID_16(0x2A08),
    /// Day of Week
    ATT_CHAR_DAY_WEEK                           = ATT_UUID_16(0x2A09),
    /// Day Date Time
    ATT_CHAR_DAY_DATE_TIME                      = ATT_UUID_16(0x2A0A),
    /// Exact time 256
    ATT_CHAR_EXACT_TIME_256                     = ATT_UUID_16(0x2A0C),
    /// DST Offset
    ATT_CHAR_DST_OFFSET                         = ATT_UUID_16(0x2A0D),
    /// Time zone
    ATT_CHAR_TIME_ZONE                          = ATT_UUID_16(0x2A0E),
    /// Local time Information
    ATT_CHAR_LOCAL_TIME_INFO                    = ATT_UUID_16(0x2A0F),
    /// Time with DST
    ATT_CHAR_TIME_WITH_DST                      = ATT_UUID_16(0x2A11),
    /// Time Accuracy
    ATT_CHAR_TIME_ACCURACY                      = ATT_UUID_16(0x2A12),
    ///Time Source
    ATT_CHAR_TIME_SOURCE                        = ATT_UUID_16(0x2A13),
    /// Reference Time Information
    ATT_CHAR_REFERENCE_TIME_INFO                = ATT_UUID_16(0x2A14),
    /// Time Update Control Point
    ATT_CHAR_TIME_UPDATE_CNTL_POINT             = ATT_UUID_16(0x2A16),
    /// Time Update State
    ATT_CHAR_TIME_UPDATE_STATE                  = ATT_UUID_16(0x2A17),
    /// Glucose Measurement
    ATT_CHAR_GLUCOSE_MEAS                       = ATT_UUID_16(0x2A18),
    /// Battery Level
    ATT_CHAR_BATTERY_LEVEL                      = ATT_UUID_16(0x2A19),
    /// Temperature Measurement
    ATT_CHAR_TEMPERATURE_MEAS                   = ATT_UUID_16(0x2A1C),
    /// Temperature Type
    ATT_CHAR_TEMPERATURE_TYPE                   = ATT_UUID_16(0x2A1D),
    /// Intermediate Temperature
    ATT_CHAR_INTERMED_TEMPERATURE               = ATT_UUID_16(0x2A1E),
    /// Measurement Interval
    ATT_CHAR_MEAS_INTERVAL                      = ATT_UUID_16(0x2A21),
    /// Boot Keyboard Input Report
    ATT_CHAR_BOOT_KB_IN_REPORT                  = ATT_UUID_16(0x2A22),
    /// System ID
    ATT_CHAR_SYS_ID                             = ATT_UUID_16(0x2A23),
    /// Model Number String
    ATT_CHAR_MODEL_NB                           = ATT_UUID_16(0x2A24),
    /// Serial Number String
    ATT_CHAR_SERIAL_NB                          = ATT_UUID_16(0x2A25),
    /// Firmware Revision String
    ATT_CHAR_FW_REV                             = ATT_UUID_16(0x2A26),
    /// Hardware revision String
    ATT_CHAR_HW_REV                             = ATT_UUID_16(0x2A27),
    /// Software Revision String
    ATT_CHAR_SW_REV                             = ATT_UUID_16(0x2A28),
    /// Manufacturer Name String
    ATT_CHAR_MANUF_NAME                         = ATT_UUID_16(0x2A29),
    /// IEEE Regulatory Certification Data List
    ATT_CHAR_IEEE_CERTIF                        = ATT_UUID_16(0x2A2A),
    /// CT Time
    ATT_CHAR_CT_TIME                            = ATT_UUID_16(0x2A2B),
    /// Magnetic Declination
    ATT_CHAR_MAGN_DECLINE                       = ATT_UUID_16(0x2A2C),
    /// Scan Refresh
    ATT_CHAR_SCAN_REFRESH                       = ATT_UUID_16(0x2A31),
    /// Boot Keyboard Output Report
    ATT_CHAR_BOOT_KB_OUT_REPORT                 = ATT_UUID_16(0x2A32),
    /// Boot Mouse Input Report
    ATT_CHAR_BOOT_MOUSE_IN_REPORT               = ATT_UUID_16(0x2A33),
    /// Glucose Measurement Context
    ATT_CHAR_GLUCOSE_MEAS_CTX                   = ATT_UUID_16(0x2A34),
    /// Blood Pressure Measurement
    ATT_CHAR_BLOOD_PRESSURE_MEAS                = ATT_UUID_16(0x2A35),
    /// Intermediate Cuff Pressure
    ATT_CHAR_INTERMEDIATE_CUFF_PRESSURE         = ATT_UUID_16(0x2A36),
    /// Heart Rate Measurement
    ATT_CHAR_HEART_RATE_MEAS                    = ATT_UUID_16(0x2A37),
    /// Body Sensor Location
    ATT_CHAR_BODY_SENSOR_LOCATION               = ATT_UUID_16(0x2A38),
    /// Heart Rate Control Point
    ATT_CHAR_HEART_RATE_CNTL_POINT              = ATT_UUID_16(0x2A39),
    /// Alert Status
    ATT_CHAR_ALERT_STATUS                       = ATT_UUID_16(0x2A3F),
    /// Ringer Control Point
    ATT_CHAR_RINGER_CNTL_POINT                  = ATT_UUID_16(0x2A40),
    /// Ringer Setting
    ATT_CHAR_RINGER_SETTING                     = ATT_UUID_16(0x2A41),
    /// Alert Category ID Bit Mask
    ATT_CHAR_ALERT_CAT_ID_BIT_MASK              = ATT_UUID_16(0x2A42),
    /// Alert Category ID
    ATT_CHAR_ALERT_CAT_ID                       = ATT_UUID_16(0x2A43),
    /// Alert Notification Control Point
    ATT_CHAR_ALERT_NTF_CTNL_PT                  = ATT_UUID_16(0x2A44),
    /// Unread Alert Status
    ATT_CHAR_UNREAD_ALERT_STATUS                = ATT_UUID_16(0x2A45),
    /// New Alert
    ATT_CHAR_NEW_ALERT                          = ATT_UUID_16(0x2A46),
    /// Supported New Alert Category
    ATT_CHAR_SUP_NEW_ALERT_CAT                  = ATT_UUID_16(0x2A47),
    /// Supported Unread Alert Category
    ATT_CHAR_SUP_UNREAD_ALERT_CAT               = ATT_UUID_16(0x2A48),
    /// Blood Pressure Feature
    ATT_CHAR_BLOOD_PRESSURE_FEATURE             = ATT_UUID_16(0x2A49),
    /// HID Information
    ATT_CHAR_HID_INFO                           = ATT_UUID_16(0x2A4A),
    /// Report Map
    ATT_CHAR_REPORT_MAP                         = ATT_UUID_16(0x2A4B),
    /// HID Control Point
    ATT_CHAR_HID_CTNL_PT                        = ATT_UUID_16(0x2A4C),
    /// Report
    ATT_CHAR_REPORT                             = ATT_UUID_16(0x2A4D),
    /// Protocol Mode
    ATT_CHAR_PROTOCOL_MODE                      = ATT_UUID_16(0x2A4E),
    /// Scan Interval Window
    ATT_CHAR_SCAN_INTV_WD                       = ATT_UUID_16(0x2A4F),
    /// PnP ID
    ATT_CHAR_PNP_ID                             = ATT_UUID_16(0x2A50),
    /// Glucose Feature
    ATT_CHAR_GLUCOSE_FEATURE                    = ATT_UUID_16(0x2A51),
    /// Record access control point
    ATT_CHAR_REC_ACCESS_CTRL_PT                 = ATT_UUID_16(0x2A52),
    /// RSC Measurement
    ATT_CHAR_RSC_MEAS                           = ATT_UUID_16(0x2A53),
    /// RSC Feature
    ATT_CHAR_RSC_FEAT                           = ATT_UUID_16(0x2A54),
    /// SC Control Point
    ATT_CHAR_SC_CNTL_PT                         = ATT_UUID_16(0x2A55),
    /// CSC Measurement
    ATT_CHAR_CSC_MEAS                           = ATT_UUID_16(0x2A5B),
    /// CSC Feature
    ATT_CHAR_CSC_FEAT                           = ATT_UUID_16(0x2A5C),
    /// Sensor Location
    ATT_CHAR_SENSOR_LOC                         = ATT_UUID_16(0x2A5D),
    /// CP Measurement
    ATT_CHAR_CP_MEAS                            = ATT_UUID_16(0x2A63),
    /// CP Vector
    ATT_CHAR_CP_VECTOR                          = ATT_UUID_16(0x2A64),
    /// CP Feature
    ATT_CHAR_CP_FEAT                            = ATT_UUID_16(0x2A65),
    /// CP Control Point
    ATT_CHAR_CP_CNTL_PT                         = ATT_UUID_16(0x2A66),
    /// Location and Speed
    ATT_CHAR_LOC_SPEED                          = ATT_UUID_16(0x2A67),
    /// Navigation
    ATT_CHAR_NAVIGATION                         = ATT_UUID_16(0x2A68),
    /// Position Quality
    ATT_CHAR_POS_QUALITY                        = ATT_UUID_16(0x2A69),
    /// LN Feature
    ATT_CHAR_LN_FEAT                            = ATT_UUID_16(0x2A6A),
    /// LN Control Point
    ATT_CHAR_LN_CNTL_PT                         = ATT_UUID_16(0x2A6B),
    /// Elevation
    ATT_CHAR_ELEVATION                          = ATT_UUID_16(0x2A6C),
    /// Pressure
    ATT_CHAR_PRESSURE                           = ATT_UUID_16(0x2A6D),
    /// Temperature
    ATT_CHAR_TEMPERATURE                        = ATT_UUID_16(0x2A6E),
    /// Humidity
    ATT_CHAR_HUMIDITY                           = ATT_UUID_16(0x2A6F),
    /// True Wind Speed
    ATT_CHAR_TRUE_WIND_SPEED                    = ATT_UUID_16(0x2A70),
    /// True Wind Direction
    ATT_CHAR_TRUE_WIND_DIR                      = ATT_UUID_16(0x2A71),
    /// Apparent Wind Speed
    ATT_CHAR_APRNT_WIND_SPEED                   = ATT_UUID_16(0x2A72),
    /// Apparent Wind Direction
    ATT_CHAR_APRNT_WIND_DIRECTION               = ATT_UUID_16(0x2A73),
    /// Gust Factor
    ATT_CHAR_GUST_FACTOR                        = ATT_UUID_16(0x2A74),
    /// Pollen Concentration
    ATT_CHAR_POLLEN_CONC                        = ATT_UUID_16(0x2A75),
    /// UV Index
    ATT_CHAR_UV_INDEX                           = ATT_UUID_16(0x2A76),
    /// Irradiance
    ATT_CHAR_IRRADIANCE                         = ATT_UUID_16(0x2A77),
    /// Rainfall
    ATT_CHAR_RAINFALL                           = ATT_UUID_16(0x2A78),
    /// Wind Chill
    ATT_CHAR_WIND_CHILL                         = ATT_UUID_16(0x2A79),
    /// Heat Index
    ATT_CHAR_HEAT_INDEX                         = ATT_UUID_16(0x2A7A),
    /// Dew Point
    ATT_CHAR_DEW_POINT                          = ATT_UUID_16(0x2A7B),
    /// Descriptor Value Changed
    ATT_CHAR_DESCRIPTOR_VALUE_CHANGED           = ATT_UUID_16(0x2A7D),
    /// Aerobic Heart Rate Lower Limit
    ATT_CHAR_AEROBIC_HEART_RATE_LOWER_LIMIT     = ATT_UUID_16(0x2A7E),
    /// Aerobic Threshhold
    ATT_CHAR_AEROBIC_THRESHHOLD                 = ATT_UUID_16(0x2A7F),
    /// Age
    ATT_CHAR_AGE                                = ATT_UUID_16(0x2A80),
    /// Anaerobic Heart Rate Lower Limit
    ATT_CHAR_ANAEROBIC_HEART_RATE_LOWER_LIMIT   = ATT_UUID_16(0x2A81),
    /// Anaerobic Heart Rate Upper Limit
    ATT_CHAR_ANAEROBIC_HEART_RATE_UPPER_LIMIT   = ATT_UUID_16(0x2A82),
    /// Anaerobic Threshhold
    ATT_CHAR_ANAEROBIC_THRESHHOLD               = ATT_UUID_16(0x2A83),
    /// Aerobic Heart Rate Upper Limit
    ATT_CHAR_AEROBIC_HEART_RATE_UPPER_LIMIT     = ATT_UUID_16(0x2A84),
    /// Date Of Birth
    ATT_CHAR_DATE_OF_BIRTH                      = ATT_UUID_16(0x2A85),
    /// Date Of Threshold Assessment
    ATT_CHAR_DATE_OF_THRESHOLD_ASSESSMENT       = ATT_UUID_16(0x2A86),
    /// Email Address
    ATT_CHAR_EMAIL_ADDRESS                      = ATT_UUID_16(0x2A87),
    /// Fat Burn Heart Rate Lower Limit
    ATT_CHAR_FAT_BURN_HEART_RATE_LOWER_LIMIT    = ATT_UUID_16(0x2A88),
    /// Fat Burn Heart Rate Upper Limit
    ATT_CHAR_FAT_BURN_HEART_RATE_UPPER_LIMIT    = ATT_UUID_16(0x2A89),
    /// First Name
    ATT_CHAR_FIRST_NAME                         = ATT_UUID_16(0x2A8A),
    /// Five Zone Heart Rate Limits
    ATT_CHAR_FIVE_ZONE_HEART_RATE_LIMITS        = ATT_UUID_16(0x2A8B),
    /// Gender
    ATT_CHAR_GENDER                             = ATT_UUID_16(0x2A8C),
    /// Max Heart Rate
    ATT_CHAR_MAX_HEART_RATE                     = ATT_UUID_16(0x2A8D),
    /// Height
    ATT_CHAR_HEIGHT                             = ATT_UUID_16(0x2A8E),
    /// Hip Circumference
    ATT_CHAR_HIP_CIRCUMFERENCE                  = ATT_UUID_16(0x2A8F),
    /// Last Name
    ATT_CHAR_LAST_NAME                          = ATT_UUID_16(0x2A90),
    /// Maximum Recommended Heart Rate
    ATT_CHAR_MAXIMUM_RECOMMENDED_HEART_RATE     = ATT_UUID_16(0x2A91),
    /// Resting Heart Rate
    ATT_CHAR_RESTING_HEART_RATE                 = ATT_UUID_16(0x2A92),
    /// Sport Type For Aerobic And Anaerobic Thresholds
    ATT_CHAR_SPORT_TYPE_FOR_AEROBIC_AND_ANAEROBIC_THRESHOLDS = ATT_UUID_16(0x2A93),
    /// Three Zone Heart Rate Limits
    ATT_CHAR_THREE_ZONE_HEART_RATE_LIMITS       = ATT_UUID_16(0x2A94),
    /// Two Zone Heart Rate Limit
    ATT_CHAR_TWO_ZONE_HEART_RATE_LIMIT          = ATT_UUID_16(0x2A95),
    /// Vo2 Max
    ATT_CHAR_VO2_MAX                            = ATT_UUID_16(0x2A96),
    /// Waist Circumference
    ATT_CHAR_WAIST_CIRCUMFERENCE                = ATT_UUID_16(0x2A97),
    /// Weight
    ATT_CHAR_WEIGHT                             = ATT_UUID_16(0x2A98),
    /// Database Change Increment
    ATT_CHAR_DATABASE_CHANGE_INCREMENT          = ATT_UUID_16(0x2A99),
    /// User Index
    ATT_CHAR_USER_INDEX                         = ATT_UUID_16(0x2A9A),
    /// Body Composition Feature
    ATT_CHAR_BODY_COMPOSITION_FEATURE           = ATT_UUID_16(0x2A9B),
    /// Body Composition Measurement
    ATT_CHAR_BODY_COMPOSITION_MEASUREMENT       = ATT_UUID_16(0x2A9C),
    /// Weight Measurement
    ATT_CHAR_WEIGHT_MEASUREMENT                 = ATT_UUID_16(0x2A9D),
    /// Weight Scale Feature
    ATT_CHAR_WEIGHT_SCALE_FEATURE               = ATT_UUID_16(0x2A9E),
    /// User Control Point
    ATT_CHAR_USER_CONTROL_POINT                 = ATT_UUID_16(0x2A9F),
    /// Flux Density - 2D
    ATT_CHAR_MAGN_FLUX_2D                       = ATT_UUID_16(0x2AA0),
    /// Magnetic Flux Density - 3D
    ATT_CHAR_MAGN_FLUX_3D                       = ATT_UUID_16(0x2AA1),
    /// Language string
    ATT_CHAR_LANGUAGE                           = ATT_UUID_16(0x2AA2),
    /// Barometric Pressure Trend
    ATT_CHAR_BAR_PRES_TREND                     = ATT_UUID_16(0x2AA3),
    /// Central Address Resolution Support
    ATT_CHAR_CTL_ADDR_RESOL_SUPP                = ATT_UUID_16(0x2AA6),
    //by wq
    ATT_SVC_UKEY_SERVICE                        = ATT_UUID_16(0xFEE7),
    ATT_CHAR_WRITE_NOTIFY                       = ATT_UUID_16(0xFEC1),
    ATT_CHAR_READ_NOTIFY                        = ATT_UUID_16(0xFEC2),

//  ATT_SVC_USER_DEF1                           = ATT_UUID_16(0xFF06),
//  ATT_CHAR_READ_WRITE1                        = ATT_UUID_16(0xFF60),
//    ATT_CHAR_DATA_NOTIFY1                       = ATT_UUID_16(0xFF61),
//    ATT_CHAR_DATA_WRITE1                        = ATT_UUID_16(0xFF62),
//
//  ATT_SVC_USER_DEF2                           = ATT_UUID_16(0xFF07),
//  ATT_CHAR_READ_WRITE2                        = ATT_UUID_16(0xFF70),
//    ATT_CHAR_DATA_NOTIFY2                       = ATT_UUID_16(0xFF71),
//    ATT_CHAR_DATA_WRITE2                        = ATT_UUID_16(0xFF72),
};

/// Format for Characteristic Presentation
enum {
    /// unsigned 1-bit: true or false
    ATT_FORMAT_BOOL     = 0x01,
    /// unsigned 2-bit integer
    ATT_FORMAT_2BIT,
    /// unsigned 4-bit integer
    ATT_FORMAT_NIBBLE,
    /// unsigned 8-bit integer
    ATT_FORMAT_UINT8,
    /// unsigned 12-bit integer
    ATT_FORMAT_UINT12,
    /// unsigned 16-bit integer
    ATT_FORMAT_UINT16,
    /// unsigned 24-bit integer
    ATT_FORMAT_UINT24,
    /// unsigned 32-bit integer
    ATT_FORMAT_UINT32,
    /// unsigned 48-bit integer
    ATT_FORMAT_UINT48,
    /// unsigned 64-bit integer
    ATT_FORMAT_UINT64,
    /// unsigned 128-bit integer
    ATT_FORMAT_UINT128,
    /// signed 8-bit integer
    ATT_FORMAT_SINT8,
    /// signed 12-bit integer
    ATT_FORMAT_SINT12,
    /// signed 16-bit integer
    ATT_FORMAT_SINT16,
    /// signed 24-bit integer
    ATT_FORMAT_SINT24,
    /// signed 32-bit integer
    ATT_FORMAT_SINT32,
    /// signed 48-bit integer
    ATT_FORMAT_SINT48,
    /// signed 64-bit integer
    ATT_FORMAT_SINT64,
    /// signed 128-bit integer
    ATT_FORMAT_SINT128,
    /// IEEE-754 32-bit floating point
    ATT_FORMAT_FLOAT32,
    /// IEEE-754 64-bit floating point
    ATT_FORMAT_FLOAT64,
    /// IEEE-11073 16-bit SFLOAT
    ATT_FORMAT_SFLOAT,
    /// IEEE-11073 32-bit FLOAT
    ATT_FORMAT_FLOAT,
    /// IEEE-20601 format
    ATT_FORMAT_DUINT16,
    /// UTF-8 string
    ATT_FORMAT_UTF8S,
    /// UTF-16 string
    ATT_FORMAT_UTF16S,
    /// Opaque structure
    ATT_FORMAT_STRUCT,
    /// Last format
    ATT_FORMAT_LAST
};


/// Client Characteristic Configuration Codes
enum att_ccc_val
{
    /// Stop notification/indication
    ATT_CCC_STOP_NTFIND = 0x0000,
    /// Start notification
    ATT_CCC_START_NTF,
    /// Start indication
    ATT_CCC_START_IND
};

/*
 * Type Definition
 ****************************************************************************************
 */

/// Attribute length type
typedef uint16_t att_size_t;


/// UUID - 128-bit type
struct att_uuid_128
{
    /// 128-bit UUID
    uint8_t uuid[ATT_UUID_128_LEN];
};

/// UUID - 32-bit type
struct att_uuid_32
{
    /// 32-bit UUID
    uint8_t uuid[ATT_UUID_32_LEN];
};



/// Characteristic Value Descriptor
struct att_char_desc
{
    /// properties
    uint8_t prop;
    /// attribute handle
    uint8_t attr_hdl[ATT_HANDLE_LEN];
    /// attribute type
    uint8_t attr_type[ATT_UUID_16_LEN];
};

/// Characteristic Value Descriptor
struct att_char128_desc
{
    /// properties
    uint8_t prop;
    /// attribute handle
    uint8_t attr_hdl[ATT_HANDLE_LEN];
    /// attribute type
    uint8_t attr_type[ATT_UUID_128_LEN];
};

/// Service Value Descriptor - 16-bit
typedef uint16_t att_svc_desc_t;

/// include service entry element
struct att_incl_desc
{
    /// start handle value of included service
    uint16_t start_hdl;
    /// end handle value of included service
    uint16_t end_hdl;
    /// attribute value UUID
    uint16_t uuid;
};

/// include service entry element
struct att_incl128_desc
{
    /// start handle value of included service
    uint16_t start_hdl;
    /// end handle value of included service
    uint16_t end_hdl;
};


// -------------------------- PDU HANDLER Definition  --------------------------

/// used to know if PDU handler has been found
#define ATT_PDU_HANDLER_NOT_FOUND       (0xff)

/// Format of a pdu handler function
typedef int (*att_func_t)(uint8_t conidx, void *pdu);

/// Element of a pdu handler table.
struct att_pdu_handler
{
    /// PDU identifier of the message
    uint8_t pdu_id;
    /// Pointer to the handler function for the pdu above.
    att_func_t handler;
};


// --------------------------- Database permissions -----------------------------

/// Macro used to retrieve access permission rights
#define PERM_GET(perm, access)\
        (((perm) & (PERM_MASK_ ## access)) >> (PERM_POS_ ## access))

/// Macro used to retrieve permission value from access and rights on attribute.
#define PERM(access, right) \
    (((PERM_RIGHT_ ## right) << (PERM_POS_ ## access)) & (PERM_MASK_ ## access))

/// Macro used know if permission is set or not.
#define PERM_IS_SET(perm, access, right) \
    (((perm) & (((PERM_RIGHT_ ## right) << (PERM_POS_ ## access))) \
                & (PERM_MASK_ ## access)) == PERM(access, right))

/// Macro used to create permission value
#define PERM_VAL(access, perm) \
    ((((perm) << (PERM_POS_ ## access))) & (PERM_MASK_ ## access))



/// Retrieve attribute security level from attribute right and service right
#define ATT_GET_SEC_LVL(att_right, svc_right) \
    co_max(((att_right) & PERM_RIGHT_AUTH), ((svc_right) & PERM_RIGHT_AUTH));

/// Retrieve UUID LEN from UUID Length Permission
#define ATT_UUID_LEN(uuid_len_perm) ((uuid_len_perm == 0) ? ATT_UUID_16_LEN : \
        ((uuid_len_perm == 1) ? ATT_UUID_32_LEN  :                        \
        ((uuid_len_perm == 2) ? ATT_UUID_128_LEN : 0)))

/// Initialization of attribute element
#define ATT_ELEMT_INIT                                   {{NULL}, false}

/**
 *   15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 * |EXT | WS | I  | N  | WR | WC | RD | B  |    NP   |    IP   |   WP    |    RP   |
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 *
 * Bit [0-1]  : Read Permission         (0 = NO_AUTH, 1 = UNAUTH, 2 = AUTH, 3 = SEC_CON)
 * Bit [2-3]  : Write Permission        (0 = NO_AUTH, 1 = UNAUTH, 2 = AUTH, 3 = SEC_CON)
 * Bit [4-5]  : Indication Permission   (0 = NO_AUTH, 1 = UNAUTH, 2 = AUTH, 3 = SEC_CON)
 * Bit [6-7]  : Notification Permission (0 = NO_AUTH, 1 = UNAUTH, 2 = AUTH, 3 = SEC_CON)
 *
 * Bit [8]    : Extended properties present (only relevant for a characteristic value)
 * Bit [9]    : Broadcast permission        (only relevant for a characteristic value)
 * Bit [10]   : Write Command accepted
 * Bit [11]   : Write Signed accepted
 * Bit [12]   : Write Request accepted
 * Bit [13]   : Encryption key Size must be 16 bytes
 */
enum attm_perm_mask
{
    /// retrieve all permission info
    PERM_MASK_ALL            = 0x0000,
    /// Read Permission Mask
    PERM_MASK_RP             = 0x0003,
    PERM_POS_RP              = 0,
    /// Write Permission Mask
    PERM_MASK_WP             = 0x000C,
    PERM_POS_WP              = 2,
    /// Indication Access Mask
    PERM_MASK_IP            = 0x0030,
    PERM_POS_IP             = 4,
    /// Notification Access Mask
    PERM_MASK_NP            = 0x00C0,
    PERM_POS_NP             = 6,
    /// Broadcast descriptor present
    PERM_MASK_BROADCAST     = 0x0100,
    PERM_POS_BROADCAST      = 8,
    /// Read Access Mask
    PERM_MASK_RD            = 0x0200,
    PERM_POS_RD             = 9,
    /// Write Command Enabled attribute Mask
    PERM_MASK_WRITE_COMMAND = 0x0400,
    PERM_POS_WRITE_COMMAND  = 10,
    /// Write Request Enabled attribute Mask
    PERM_MASK_WRITE_REQ     = 0x0800,
    PERM_POS_WRITE_REQ      = 11,
    /// Notification Access Mask
    PERM_MASK_NTF           = 0x1000,
    PERM_POS_NTF            = 12,
    /// Indication Access Mask
    PERM_MASK_IND           = 0x2000,
    PERM_POS_IND            = 13,
    /// Write Signed Enabled attribute Mask
    PERM_MASK_WRITE_SIGNED  = 0x4000,
    PERM_POS_WRITE_SIGNED   = 14,
    /// Extended properties descriptor present
    PERM_MASK_EXT           = 0x8000,
    PERM_POS_EXT            = 15,

    /// Properties
    PERM_MASK_PROP          = 0xFF00,
    PERM_POS_PROP           = 8,
};

/**
 * Value permission bit field
 *
 *   15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 * | RI |UUID_LEN |EKS |    MAX_LEN (RI = 1) / Value Offset  (RI = 0)              |
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 *
 * Bit [0-11] : Maximum Attribute Length or Value Offset pointer
 * Bit [12]   : Encryption key Size must be 16 bytes
 * Bit [14-13]: UUID Length             (0 = 16 bits, 1 = 32 bits, 2 = 128 bits, 3 = RFU)
 * Bit [15]   : Trigger Read Indication (0 = Value present in Database, 1 = Value not present in Database)
 */
enum attm_value_perm_mask
{
    /// Maximum Attribute Length
    PERM_MASK_MAX_LEN     = 0x0FFF,
    PERM_POS_MAX_LEN      = 0,
    /// Attribute value Offset
    PERM_MASK_VAL_OFFSET  = 0x0FFF,
    PERM_POS_VAL_OFFSET   = 0,
    /// Check Encryption key size Mask
    PERM_MASK_EKS         = 0x1000,
    PERM_POS_EKS          = 12,
    /// UUID Length
    PERM_MASK_UUID_LEN    = 0x6000,
    PERM_POS_UUID_LEN     = 13,
    /// Read trigger Indication
    PERM_MASK_RI          = 0x8000,
    PERM_POS_RI           = 15,
};


/**
 * Service permissions
 *
 *    7    6    5    4    3    2    1    0
 * +----+----+----+----+----+----+----+----+
 * |SEC |UUID_LEN |DIS |  AUTH   |EKS | MI |
 * +----+----+----+----+----+----+----+----+
 *
 * Bit [0]  : Task that manage service is multi-instantiated (Connection index is conveyed)
 * Bit [1]  : Encryption key Size must be 16 bytes
 * Bit [2-3]: Service Permission      (0 = NO_AUTH, 1 = UNAUTH, 2 = AUTH, 3 = Secure Connect)
 * Bit [4]  : Disable the service
 * Bit [5-6]: UUID Length             (0 = 16 bits, 1 = 32 bits, 2 = 128 bits, 3 = RFU)
 * Bit [7]  : Secondary Service       (0 = Primary Service, 1 = Secondary Service)
 */
enum attm_svc_perm_mask
{
    /// Task that manage service is multi-instantiated
    PERM_MASK_SVC_MI        = 0x01,
    PERM_POS_SVC_MI         = 0,
    /// Check Encryption key size for service Access
    PERM_MASK_SVC_EKS       = 0x02,
    PERM_POS_SVC_EKS        = 1,
    /// Service Permission authentication
    PERM_MASK_SVC_AUTH      = 0x0C,
    PERM_POS_SVC_AUTH       = 2,
    /// Disable the service
    PERM_MASK_SVC_DIS       = 0x10,
    PERM_POS_SVC_DIS        = 4,
    /// Service UUID Length
    PERM_MASK_SVC_UUID_LEN  = 0x60,
    PERM_POS_SVC_UUID_LEN   = 5,
    /// Service type Secondary
    PERM_MASK_SVC_SECONDARY = 0x80,
    PERM_POS_SVC_SECONDARY  = 7,
};

/// Attribute & Service access mode
enum
{
    /// Disable access
    PERM_RIGHT_DISABLE   = 0,
    /// Enable access
    PERM_RIGHT_ENABLE   = 1,
};

/// Attribute & Service access rights
enum
{
    /// No Authentication
    PERM_RIGHT_NO_AUTH  = 0,
    /// Access Requires Unauthenticated link
    PERM_RIGHT_UNAUTH   = 1,
    /// Access Requires Authenticated link
    PERM_RIGHT_AUTH     = 2,
    /// Access Requires Secure Connection link
    PERM_RIGHT_SEC_CON  = 3,
};

/// Attribute & Service UUID Length
enum
{
    /// 16  bits UUID
    PERM_UUID_16         = 0,
    PERM_RIGHT_UUID_16         = 0,
    /// 32  bits UUID
    PERM_UUID_32         = 1,
    PERM_RIGHT_UUID_32         = 1,
    /// 128 bits UUID
    PERM_UUID_128        = 2,
    PERM_RIGHT_UUID_128        = 2,
    /// Invalid
    PERM_UUID_RFU        = 3,
};

/// execute flags
enum
{
    /// Cancel All the Reliable Writes
    ATT_CANCEL_ALL_PREPARED_WRITES = 0x00,
    /// Write All the Reliable Writes
    ATT_EXECUTE_ALL_PREPARED_WRITES
};



/// @} ATT
#endif // ATT_H_
