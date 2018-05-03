/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file ieee11073_phd_types.h
 *
 * @author 
 *
 * @version 
 *
 * @date Mar-31-2009
 *
 * @brief This file contains definitions of the data types and the structures 
 *        for the data that appears on the network (specific to IEEE_11073)
 *****************************************************************************/
#ifndef PHD_TYPES
#define PHD_TYPES

#ifndef __HIWARE__
#pragma pack(1)
#endif
/*
The following typedefs may need to be changed depending on the
Compiler and machine architecture.
*/
typedef unsigned char intu8;
typedef unsigned short intu16;
typedef unsigned long intu32;

typedef struct _Any
{    
    intu16 length;
    intu8 value[1]; /* first element of the array */
} Any;

typedef intu16 OID_Type;

typedef intu16 PrivateOid;

typedef intu16 HANDLE;

typedef intu16 InstNumber;

typedef intu16 NomPartition;

#define NOM_PART_UNSPEC 0
#define NOM_PART_OBJ 1
#define NOM_PART_METRIC 2
#define NOM_PART_ALERT 3
#define NOM_PART_DIM 4
#define NOM_PART_VATTR 5
#define NOM_PART_PGRP 6
#define NOM_PART_SITES 7
#define NOM_PART_INFRASTRUCT 8
#define NOM_PART_FEF 9
#define NOM_PART_ECG_EXTN 10
#define NOM_PART_PHD_DM 128
#define NOM_PART_PHD_HF 129
#define NOM_PART_PHD_AI 130
#define NOM_PART_RET_CODE 255
#define NOM_PART_EXT_NOM 256
#define NOM_PART_PRIV 1024

typedef struct _TYPE
{
    NomPartition partition;
    OID_Type code;
} TYPE;

typedef struct _AVA_Type
{
    OID_Type attribute_id;
    Any attribute_value;
} AVA_Type;

typedef struct _AttributeList
{
    intu16 count;
    intu16 length;
    AVA_Type value[1]; /* first element of the array */
} AttributeList;

typedef struct _AttributeIdList
{
    intu16 count;
    intu16 length;
    OID_Type value[1]; /* first element of the array */
} AttributeIdList;

typedef intu32 FLOAT_Type;
typedef intu16 SFLOAT_Type;
typedef intu32 RelativeTime;

typedef struct _HighResRelativeTime
{
    intu8 value[8];
} HighResRelativeTime;

typedef struct _AbsoluteTimeAdjust
{
    intu8 value[6];
} AbsoluteTimeAdjust;

typedef struct _AbsoluteTime
{
    intu8 century;
    intu8 year;
    intu8 month;
    intu8 day;
    intu8 hour;
    intu8 minute;
    intu8 second;
    intu8 sec_fractions;
} AbsoluteTime;

typedef intu16 OperationalState;
#define OS_DISABLED 0
#define OS_ENABLED 1

#define OS_NOT_AVAILABLE 2
typedef struct _octet_string
{
    intu16 length;
    intu8 value[1]; /* first element of the array */
} octet_string;

typedef struct _SystemModel 
{
    octet_string manufacturer;
    octet_string model_number;
} SystemModel;

typedef struct _ProdSpecEntry
{
    intu16 spec_type;
#define UNSPECIFIED 0
#define SERIAL_NUMBER 1
#define PART_NUMBER 2
#define HW_REVISION 3
#define SW_REVISION 4
#define FW_REVISION 5
#define PROTOCOL_REVISION 6
#define PROD_SPEC_GMDN 7
    PrivateOid component_id;
    octet_string prod_spec;
} ProdSpecEntry;

typedef struct _ProductionSpec
{
    intu16 count;
    intu16 length;
    ProdSpecEntry value[1]; /* first element of the array */
} ProductionSpec;

typedef intu16 _PowerStatus;

#define ON_MAINS 0x8000
#define ON_BATTERY 0x4000
#define CHARGING_FULL 0x0080
#define CHARGING_TRICKLE 0x0040
#define CHARGING_OFF 0x0020

typedef struct _BatMeasure
{
    FLOAT_Type value;
    OID_Type unit;
} BatMeasure;

typedef intu16 MeasurementStatus;

#define MS_INVALID 0x8000
#define MS_QUESTIONABLE 0x4000
#define MS_NOT_AVAILABLE 0x2000
#define MS_CALIBRATION_ONGOING 0x1000
#define MS_TEST_DATA 0x0800
#define MS_DEMO_DATA 0x0400
#define MS_VALIDATED_DATA 0x0080

#define MS_EARLY_INDICATION 0x0040
#define MS_MSMT_ONGOING 0x0020

typedef struct _NuObsValue
{
    OID_Type metric_id;
    MeasurementStatus state;
    OID_Type unit_code;
    FLOAT_Type value;
} NuObsValue;

typedef struct _NuObsValueCmp
{
    intu16 count;
    intu16 length;
    NuObsValue value[1]; /* first element of the array */
} NuObsValueCmp;

typedef struct _SampleType
{
    intu8 sample_size;
    intu8 significant_bits;
} SampleType;

#define SAMPLE_TYPE_SIGNIFICANT_BITS_SIGNED_SAMPLES 255

typedef intu16 SaFlags;

#define SMOOTH_CURVE 0x8000
#define DELAYED_CURVE 0x4000
#define STATIC_SCALE 0x2000
#define SA_EXT_VAL_RANGE 0x1000

typedef struct _SaSpec
{
    intu16 array_size;
    SampleType sample_type;
    SaFlags flags;
} SaSpec;

typedef struct _ScaleRangeSpec8
{
    FLOAT_Type lower_absolute_value;
    FLOAT_Type upper_absolute_value;
    intu8 lower_scaled_value;
    intu8 upper_scaled_value;
} ScaleRangeSpec8;

typedef struct _ScaleRangeSpec16
{
    FLOAT_Type lower_absolute_value;
    FLOAT_Type upper_absolute_value;
    intu16 lower_scaled_value;
    intu16 upper_scaled_value;
} ScaleRangeSpec16;

typedef struct _ScaleRangeSpec32
{
    FLOAT_Type lower_absolute_value;
    FLOAT_Type upper_absolute_value;
    intu32 lower_scaled_value;
    intu32 upper_scaled_value;
} ScaleRangeSpec32;

typedef struct _EnumVal
{
    intu16 choice;
    intu16 length;
#define OBJ_ID_CHOSEN 0x0001
#define TEXT_STRING_CHOSEN 0x0002
#define BIT_STR_CHOSEN 0x0010

    union
    {
        OID_Type enum_obj_id;
        octet_string enum_text_string;
        intu32 enum_bit_str; /* BITS-32 */
    } u;
} EnumVal;

typedef struct _EnumObsValue
{
    OID_Type metric_id;
    MeasurementStatus state;
    EnumVal value;
} EnumObsValue;

typedef struct _AttrValMapEntry
{
    OID_Type attribute_id;
    intu16 attribute_len;
} AttrValMapEntry;

typedef struct _AttrValMap
{
    intu16 count;
    intu16 length;
    AttrValMapEntry value[1]; /* first element of the array */
} AttrValMap;

typedef struct _HandleAttrValMapEntry
{
    HANDLE obj_handle;
    AttrValMap attr_val_map;
} HandleAttrValMapEntry;

typedef intu16 ConfirmMode;

#define UNCONFIRMED 0x0000
#define CONFIRMED 0x0001

typedef struct _HandleAttrValMap
{
    intu16 count;
    intu16 length;
    HandleAttrValMapEntry value[1]; /* first element of the array */
} HandleAttrValMap;

typedef intu16 StoSampleAlg;

#define ST_ALG_NOS 0x0000
#define ST_ALG_MOVING_AVERAGE 0x0001
#define ST_ALG_RECURSIVE_ 0x0002
#define ST_ALG_MIN_PICK 0x0003
#define ST_ALG_MAX_PICK 0x0004
#define ST_ALG_MEDIAN 0x0005
#define ST_ALG_TRENDED 0x0200
#define ST_ALG_NO_DOWNSAMPLING 0x0400

typedef struct _SetTimeInvoke
{
    AbsoluteTime date_time;
    FLOAT_Type accuracy;
} SetTimeInvoke;

typedef struct _SegmIdList
{
    intu16 count;
    intu16 length;
    InstNumber value[1]; /* first element of the array */
} SegmIdList;

typedef struct _AbsTimeRange
{
    AbsoluteTime from_time;
    AbsoluteTime to_time;
} AbsTimeRange;

typedef struct _SegmentInfo
{
    InstNumber seg_inst_no;
    AttributeList seg_info;
} SegmentInfo;

typedef struct _SegmentInfoList
{
    intu16 count;
    intu16 length;
    SegmentInfo value[1]; /* first element of the array */
} SegmentInfoList;

typedef struct _SegmSelection
{
    intu16 choice;
    intu16 length;
#define ALL_SEGMENTS_CHOSEN 0x0001
#define SEGM_ID_LIST_CHOSEN 0x0002
#define ABS_TIME_RANGE_CHOSEN 0x0003
    union
    {
        intu16 all_segments;
        SegmIdList segm_id_list;
        AbsTimeRange abs_time_range;
    } u;
} SegmSelection;

typedef intu16 PMStoreCapab;

#define PMSC_VAR_NO_OF_SEGM 0x8000
#define PMSC_EPI_SEG_ENTRIES 0x0800
#define PMSC_PERI_SEG_ENTRIES 0x0400
#define PMSC_ABS_TIME_SELECT 0x0200
#define PMSC_CLEAR_SEGM_BY_LIST_SUP 0x0100
#define PMSC_CLEAR_SEGM_BY_TIME_SUP 0x0080
#define PMSC_CLEAR_SEGM_REMOVE 0x0040
#define PMSC_MULTI_PERSON 0x0008

typedef intu16 SegmEntryHeader;

#define SEG_ELEM_HDR_ABSOLUTE_TIME 0x8000
#define SEG_ELEM_HDR_RELATIVE_TIME 0x4000
#define SEG_ELEM_HDR_HIRES_RELATIVE_TIME 0x2000

typedef struct _SegmEntryElem
{
    OID_Type class_id;
    TYPE metric_type;
    HANDLE handle;
    AttrValMap attr_val_map;
} SegmEntryElem;

typedef struct _SegmEntryElemList
{
    intu16 count;
    intu16 length;
    SegmEntryElem value[1]; /* first element of the array */
} SegmEntryElemList;

typedef struct _PmSegmentEntryMap
{
    SegmEntryHeader segm_entry_header;
    SegmEntryElemList segm_entry_elem_list;
} PmSegmentEntryMap;

typedef struct _SegmElemStaticAttrEntry
{
    OID_Type class_id;
    TYPE metric_type;
    AttributeList attribute_list;
} SegmElemStaticAttrEntry;

typedef struct _PmSegmElemStaticAttrList
{
    intu16 count;
    intu16 length;
    SegmElemStaticAttrEntry value[1]; /* first element of the array */
} PmSegmElemStaticAttrList;

typedef struct _TrigSegmDataXferReq
{
    InstNumber seg_inst_no;
} TrigSegmDataXferReq;

typedef intu16 TrigSegmXferRsp;

#define TSXR_SUCCESSFUL 0
#define TSXR_FAIL_NO_SUCH_SEGMENT 1
#define TSXR_FAIL_SEGM_TRY_LATER 2
#define TSXR_FAIL_SEGM_EMPTY 3
#define TSXR_FAIL_OTHER 512

typedef struct _TrigSegmDataXferRsp
{
    InstNumber seg_inst_no;
    TrigSegmXferRsp trig_segm_xfer_rsp;
} TrigSegmDataXferRsp;

typedef intu16 SegmEvtStatus;

#define SEVTSTA_FIRST_ENTRY 0x8000
#define SEVTSTA_LAST_ENTRY 0x4000
#define SEVTSTA_AGENT_ABORT 0x0800
#define SEVTSTA_MANAGER_CONFIRM 0x0080
#define SEVTSTA_MANAGER_ABORT 0x0008

typedef struct _SegmDataEventDescr
{
    InstNumber segm_instance;
    intu32 segm_evt_entry_index;
    intu32 segm_evt_entry_count;
    SegmEvtStatus segm_evt_status;
} SegmDataEventDescr;

typedef struct _SegmentDataEvent
{
    SegmDataEventDescr segm_data_event_descr;
    octet_string segm_data_event_entries;
} SegmentDataEvent;

typedef struct _SegmentDataResult
{
    SegmDataEventDescr segm_data_event_descr;
} SegmentDataResult;

typedef intu16 SegmStatType;

#define SEGM_STAT_TYPE_MINIMUM 1
#define SEGM_STAT_TYPE_MAXIMUM 2
#define SEGM_STAT_TYPE_AVERAGE 3

typedef struct _SegmentStatisticEntry
{
    SegmStatType segm_stat_type;
    octet_string segm_stat_entry;
} SegmentStatisticEntry;

typedef struct _SegmentStatistics
{
    intu16 count;
    intu16 length;
    SegmentStatisticEntry value[1]; /* first element of the array */
} SegmentStatistics;

typedef struct _ObservationScan
{
    HANDLE obj_handle;
    AttributeList attributes;
} ObservationScan;

typedef OID_Type TimeProtocolId;

typedef intu32 AssociationVersion;
#define ASSOC_VERSION1 0x80000000

typedef intu32 ProtocolVersion;
#define PROTOCOL_VERSION1 0x80000000

typedef intu16 EncodingRules;
#define MDER 0x8000
#define XER 0x4000
#define PER 0x2000

typedef struct _UUID_Ident
{
    intu8 value[16];
} UUID_Ident;

typedef intu16 DataProtoId;
#define DATA_PROTO_ID_20601 20601
#define DATA_PROTO_ID_EXTERNAL 65535

typedef struct _DataProto
{
    DataProtoId data_proto_id;
    Any data_proto_info;
} DataProto;

typedef struct _DataProtoList
{
    intu16 count;
    intu16 length;
    DataProto value[1]; /* first element of the array */
} DataProtoList;

typedef struct _AARQ_apdu
{
    AssociationVersion assoc_version;
    DataProtoList data_proto_list;
} AARQ_apdu;

typedef intu16 Associate_result;
#define ACCEPTED 0
#define REJECTED_PERMANENT 1
#define REJECTED_TRANSIENT 2
#define ACCEPTED_UNKNOWN_CONFIG 3
#define REJECTED_NO_COMMON_PROTOCOL 4
#define REJECTED_NO_COMMON_PARAMETER 5
#define REJECTED_UNKNOWN 6
#define REJECTED_UNAUTHORIZED 7
#define REJECTED_UNSUPPORTED_ASSOC_VERSION 8

typedef struct _AARE_apdu
{
    Associate_result result;
    DataProto selected_data_proto;
} AARE_apdu;

typedef intu16 Release_request_reason;
#define RELEASE_REQUEST_REASON_NORMAL 0

typedef struct _RLRQ_apdu
{
    Release_request_reason reason;
} RLRQ_apdu;

typedef intu16 Release_response_reason;
#define RELEASE_RESPONSE_REASON_NORMAL 0

typedef struct _RLRE_apdu
{
    Release_response_reason reason;
} RLRE_apdu;

typedef intu16 Abort_reason;
#define ABORT_REASON_UNDEFINED 0
#define ABORT_REASON_BUFFER_OVERFLOW 1
#define ABORT_REASON_RESPONSE_TIMEOUT 2
#define ABORT_REASON_CONFIGURATION_TIMEOUT 3

typedef struct _ABRT_apdu
{
    Abort_reason reason;
} ABRT_apdu;

typedef octet_string PRST_apdu;
typedef intu16 InvokeIDType;

typedef struct _EventReportArgumentSimple
{
    HANDLE obj_handle;
    RelativeTime event_time;
    OID_Type event_type;
    Any event_info;
} EventReportArgumentSimple;

typedef struct _GetArgumentSimple
{
    HANDLE obj_handle;
    AttributeIdList attribute_id_list;
} GetArgumentSimple;

typedef intu16 ModifyOperator;
#define REPLACE 0
#define ADD_VALUES 1
#define REMOVE_VALUES 2
#define SET_TO_DEFAULT 3

typedef struct _AttributeModEntry
{
    ModifyOperator modify_operator;
    AVA_Type attribute;
} AttributeModEntry;

typedef struct _ModificationList
{
    intu16 count;
    intu16 length;
    AttributeModEntry value[1]; /* first element of the array */
} ModificationList;

typedef struct _SetArgumentSimple
{
    HANDLE obj_handle;
    ModificationList modification_list;
} SetArgumentSimple;

typedef struct _ActionArgumentSimple
{
    HANDLE obj_handle;
    OID_Type action_type;
    Any action_info_args;
} ActionArgumentSimple;

typedef struct _EventReportResultSimple
{
    HANDLE obj_handle;
    RelativeTime currentTime;
    OID_Type event_type;
    Any event_reply_info;
} EventReportResultSimple;

typedef struct _GetResultSimple
{
    HANDLE obj_handle;
    AttributeList attribute_list;
} GetResultSimple;

typedef struct _TypeVer
{
    OID_Type type;
    intu16 version;
} TypeVer;

typedef struct _TypeVerList
{
    intu16 count;
    intu16 length;
    TypeVer value[1]; /* first element of the array */
} TypeVerList;

typedef struct _SetResultSimple
{
    HANDLE obj_handle;
    AttributeList attribute_list;
} SetResultSimple;

typedef struct _ActionResultSimple
{
    HANDLE obj_handle;
    OID_Type action_type;
    Any action_info_args;
} ActionResultSimple;

typedef intu16 ERROR;
#define NO_SUCH_OBJECT_INSTANCE 1
#define ACCESS_DENIED 2
#define NO_SUCH_ACTION 9
#define INVALID_OBJECT_INSTANCE 17
#define PROTOCOL_VIOLATION 23
#define NOT_ALLOWED_BY_OBJECT 24
#define ACTION_TIMED_OUT 25
#define ACTION_ABORTED 26

typedef struct _ErrorResult
{
    ERROR error_value;
    Any parameter;
} ErrorResult;

typedef intu16 RorjProblem;
#define UNRECOGNIZED_APDU 0
#define BADLY_STRUCTURED_APDU 2
#define UNRECOGNIZED_OPERATION 101
#define RESOURCE_LIMITATION 103
#define UNEXPECTED_ERROR 303

typedef struct _RejectResult
{
    RorjProblem problem;
} RejectResult;

typedef struct _DATA_apdu
{            
    InvokeIDType invoke_id;
    struct
    {
        intu16 choice;
        intu16 length;
#define ROIV_CMIP_EVENT_REPORT_CHOSEN 0x0100
#define ROIV_CMIP_CONFIRMED_EVENT_REPORT_CHOSEN 0x0101
#define ROIV_CMIP_GET_CHOSEN 0x0103
#define ROIV_CMIP_SET_CHOSEN 0x0104
#define ROIV_CMIP_CONFIRMED_SET_CHOSEN 0x0105
#define ROIV_CMIP_ACTION_CHOSEN 0x0106
#define ROIV_CMIP_CONFIRMED_ACTION_CHOSEN 0x0107
#define RORS_CMIP_CONFIRMED_EVENT_REPORT_CHOSEN 0x0201
#define RORS_CMIP_GET_CHOSEN 0x0203
#define RORS_CMIP_CONFIRMED_SET_CHOSEN 0x0205
#define RORS_CMIP_CONFIRMED_ACTION_CHOSEN 0x0207
#define ROER_CHOSEN 0x0300
#define RORJ_CHOSEN 0x0400

        union
        {
            EventReportArgumentSimple roiv_cmipEventReport;
            EventReportArgumentSimple roiv_cmipConfirmedEventReport;
            GetArgumentSimple roiv_cmipGet;
            SetArgumentSimple roiv_cmipSet;
            SetArgumentSimple roiv_cmipConfirmedSet;
            ActionArgumentSimple roiv_cmipAction;
            ActionArgumentSimple roiv_cmipConfirmedAction;
            EventReportResultSimple rors_cmipConfirmedEventReport;
            GetResultSimple rors_cmipGet;
            SetResultSimple rors_cmipConfirmedSet;
            ActionResultSimple rors_cmipConfirmedAction;
            ErrorResult roer;
            RejectResult rorj;
        } u;
    } choice;
} DATA_apdu;
typedef struct _APDU
{
    intu16 choice;
    intu16 length;
#define AARQ_CHOSEN 0xE200
#define AARE_CHOSEN 0xE300
#define RLRQ_CHOSEN 0xE400
#define RLRE_CHOSEN 0xE500
#define ABRT_CHOSEN 0xE600
#define PRST_CHOSEN 0xE700
    union
    {
        AARQ_apdu aarq;
        AARE_apdu aare;
        RLRQ_apdu rlrq;
        RLRE_apdu rlre;
        ABRT_apdu abrt;
        PRST_apdu prst;
    } u;
} APDU;

typedef intu32 NomenclatureVersion;
#define NOM_VERSION1 0x80000000

typedef intu32 FunctionalUnits;
#define FUN_UNITS_UNIDIRECTIONAL 0x80000000
#define FUN_UNITS_HAVETESTCAP 0x40000000
#define FUN_UNITS_CREATETESTASSOC 0x20000000

typedef intu32 SystemType;
#define SYS_TYPE_MANAGER 0x80000000
#define SYS_TYPE_AGENT 0x00800000

typedef intu16 ConfigId;
#define MANAGER_CONFIG_RESPONSE 0x0000
#define STANDARD_CONFIG_START 0x0001
#define STANDARD_CONFIG_END 0x3FFF
#define EXTENDED_CONFIG_START 0x05DC 

#define EXTENDED_CONFIG_END 0x7FFF
#define RESERVED_START 0x8000
#define RESERVED_END 0xFFFF

typedef intu16 DataReqModeFlags;
#define DATA_REQ_SUPP_STOP 0x8000
#define DATA_REQ_SUPP_SCOPE_ALL 0x0800
#define DATA_REQ_SUPP_SCOPE_CLASS 0x0400
#define DATA_REQ_SUPP_SCOPE_HANDLE 0x0200
#define DATA_REQ_SUPP_MODE_SINGLE_RSP 0x0080
#define DATA_REQ_SUPP_MODE_TIME_PERIOD 0x0040
#define DATA_REQ_SUPP_MODE_TIME_NO_LIMIT 0x0020
#define DATA_REQ_SUPP_PERSON_ID 0x0010
#define DATA_REQ_SUPP_INIT_AGENT 0x0001

typedef struct _DataReqModeCapab
{
    DataReqModeFlags data_req_mode_flags;
    intu8 data_req_init_agent_count;
    intu8 data_req_init_manager_count;
} DataReqModeCapab;

typedef struct _PhdAssociationInformation
{
    ProtocolVersion protocolVersion;
    EncodingRules encodingRules;
    NomenclatureVersion nomenclatureVersion;
    FunctionalUnits functionalUnits;
    SystemType systemType;
    octet_string system_id; 
    intu16 dev_config_id;
    DataReqModeCapab data_req_mode_capab;
    AttributeList optionList; 
} PhdAssociationInformation;

typedef struct _ManufSpecAssociationInformation
{
    UUID_Ident data_proto_id_ext;
    Any data_proto_info_ext;
} ManufSpecAssociationInformation;

typedef intu16 MdsTimeCapState;
#define MDS_TIME_CAPAB_REAL_TIME_CLOCK 0x8000
#define MDS_TIME_CAPAB_SET_CLOCK 0x4000
#define MDS_TIME_CAPAB_RELATIVE_TIME 0x2000
#define MDS_TIME_CAPAB_HIGH_RES_RELATIVE_TIME 0x1000
#define MDS_TIME_CAPAB_SYNC_ABS_TIME 0x0800
#define MDS_TIME_CAPAB_SYNC_REL_TIME 0x0400
#define MDS_TIME_CAPAB_SYNC_HI_RES_RELATIVE_TIME 0x0200
#define MDS_TIME_STATE_ABS_TIME_SYNCED 0x0080
#define MDS_TIME_STATE_REL_TIME_SYNCED 0x0040
#define MDS_TIME_STATE_HI_RES_RELATIVE_TIME_SYNCED 0x0020
#define MDS_TIME_MGR_SET_TIME 0x0010

typedef struct _MdsTimeInfo
{
    MdsTimeCapState mds_time_cap_state;
    TimeProtocolId time_sync_protocol;
    RelativeTime time_sync_accuracy;
    intu16 time_resolution_abs_time;
    intu16 time_resolution_rel_time;
    intu32 time_resolution_high_res_time;
} MdsTimeInfo;

typedef octet_string EnumPrintableString;

typedef intu16 PersonId;
#define UNKNOWN_PERSON_ID 0xFFFF

typedef intu16 MetricSpecSmall;
#define MSS_AVAIL_INTERMITTENT 0x8000
#define MSS_AVAIL_STORED_DATA 0x4000
#define MSS_UPD_APERIODIC 0x2000
#define MSS_MSMT_APERIODIC 0x1000
#define MSS_MSMT_PHYS_EV_ID 0x0800
#define MSS_MSMT_BTB_METRIC 0x0400
#define MSS_ACC_MANAGER_INITIATED 0x0080
#define MSS_ACC_AGENT_INITIATED 0x0040
#define MSS_CAT_MANUAL 0x0008
#define MSS_CAT_SETTING 0x0004
#define MSS_CAT_CALCULATION 0x0002

typedef struct _MetricStructureSmall
{
    intu8 ms_struct;
#define MS_STRUCT_SIMPLE 0
#define MS_STRUCT_COMPOUND 1
#define MS_STRUCT_RESERVED 2
#define MS_STRUCT_COMPOUND_FIX 3
    intu8 ms_comp_no;
} MetricStructureSmall;

typedef struct _MetricIdList
{
    intu16 count;
    intu16 length;
    OID_Type value[1]; /* first element of the array */
} MetricIdList;

typedef struct _SupplementalTypeList
{
    intu16 count;
    intu16 length;
    TYPE value[1]; /* first element of the array */
} SupplementalTypeList;

typedef struct _ObservationScanList
{
    intu16 count;
    intu16 length;
    ObservationScan value[1]; /* first element of the array */
} ObservationScanList;

typedef struct _ScanReportPerVar
{
    intu16 person_id;
    ObservationScanList obs_scan_var;
} ScanReportPerVar;

typedef struct _ScanReportPerVarList
{
    intu16 count;
    intu16 length;
    ScanReportPerVar value[1]; /* first element of the array */
} ScanReportPerVarList;

typedef intu16 DataReqId;
#define DATA_REQ_ID_MANAGER_INITIATED_MIN 0x0000
#define DATA_REQ_ID_MANAGER_INITIATED_MAX 0xEFFF
#define DATA_REQ_ID_AGENT_INITIATED 0xF000

typedef struct _ScanReportInfoMPVar
{
    DataReqId data_req_id;
    intu16 scan_report_no;
    ScanReportPerVarList scan_per_var;
} ScanReportInfoMPVar;

typedef struct _ObservationScanFixed
{
    HANDLE obj_handle;
    octet_string obs_val_data;
} ObservationScanFixed;

typedef struct _ObservationScanFixedList
{
    intu16 count;
    intu16 length;
    ObservationScanFixed value[1]; /* first element of the array */
} ObservationScanFixedList;

typedef struct _ScanReportPerFixed
{
    intu16 person_id;
    ObservationScanFixedList obs_scan_fix;
} ScanReportPerFixed;

typedef struct _ScanReportPerFixedList
{
    intu16 count;
    intu16 length;
    ScanReportPerFixed value[1]; /* first element of the array */
} ScanReportPerFixedList;

typedef struct _ScanReportInfoMPFixed
{
    DataReqId data_req_id;
    intu16 scan_report_no;
    ScanReportPerFixedList scan_per_fixed;
} ScanReportInfoMPFixed;

typedef struct _ScanReportInfoVar
{
    DataReqId data_req_id;
    intu16 scan_report_no;
    ObservationScanList obs_scan_var;
} ScanReportInfoVar;

typedef struct _ScanReportInfoFixed
{
    DataReqId data_req_id;
    intu16 scan_report_no;
    ObservationScanFixedList obs_scan_fixed;
} ScanReportInfoFixed;

typedef octet_string ObservationScanGrouped;

typedef struct _ScanReportInfoGroupedList
{
    intu16 count;
    intu16 length;
    ObservationScanGrouped value[1]; /* first element of the array */
} ScanReportInfoGroupedList;

typedef struct _ScanReportInfoGrouped
{
    intu16 data_req_id;
    intu16 scan_report_no;
    ScanReportInfoGroupedList obs_scan_grouped;
} ScanReportInfoGrouped;

typedef struct _ScanReportPerGrouped
{
    PersonId person_id;
    ObservationScanGrouped obs_scan_grouped;
} ScanReportPerGrouped;

typedef struct _ScanReportPerGroupedList
{
    intu16 count;
    intu16 length;
    ScanReportPerGrouped value[1]; /* first element of the array */
} ScanReportPerGroupedList;

typedef struct _ScanReportInfoMPGrouped
{
    intu16 data_req_id;
    intu16 scan_report_no;
    ScanReportPerGroupedList scan_per_grouped;
} ScanReportInfoMPgrouped;

typedef struct _ConfigObject
{
    OID_Type obj_class;
    HANDLE obj_handle;
    AttributeList attributes;
} ConfigObject;

typedef struct _ConfigObjectList
{
    intu16 count;
    intu16 length;
    ConfigObject value[1]; /* first element of the array */
} ConfigObjectList;

typedef struct _ConfigReport
{
    ConfigId config_report_id;
    ConfigObjectList config_obj_list;
} ConfigReport;

typedef intu16 ConfigResult;
#define ACCEPTED_CONFIG 0x0000
#define UNSUPPORTED_CONFIG 0x0001
#define STANDARD_CONFIG_UNKNOWN 0x0002

typedef struct _ConfigReportRsp
{
    ConfigId config_report_id;
    ConfigResult config_result;
} ConfigReportRsp;

typedef intu16 DataReqMode;
#define DATA_REQ_START_STOP 0x8000
#define DATA_REQ_CONTINUATION 0x4000
#define DATA_REQ_SCOPE_ALL 0x0800
#define DATA_REQ_SCOPE_TYPE 0x0400
#define DATA_REQ_SCOPE_HANDLE 0x0200
#define DATA_REQ_MODE_SINGLE_RSP 0x0080
#define DATA_REQ_MODE_TIME_PERIOD 0x0040
#define DATA_REQ_MODE_TIME_NO_LIMIT 0x0020
#define DATA_REQ_MODE_DATA_REQ_PERSON_ID 0x0008

typedef struct _HANDLEList
{
    intu16 count;
    intu16 length;
    HANDLE value[1]; /* first element of the array */
} HANDLEList;

typedef struct _DataRequest
{
    DataReqId data_req_id;
    DataReqMode data_req_mode;
    RelativeTime data_req_time;
    intu16 DataRequest_data_req_person_id;
    OID_Type data_req_class;
    HANDLEList data_req_obj_handle_list;
} DataRequest;

typedef intu16 DataReqResult;
#define DATA_REQ_RESULT_NO_ERROR 0
#define DATA_REQ_RESULT_UNSPECIFIC_ERROR 1
#define DATA_REQ_RESULT_NO_STOP_SUPPORT 2

#define DATA_REQ_RESULT_NO_SCOPE_ALL_SUPPORT 3
#define DATA_REQ_RESULT_NO_SCOPE_CLASS_SUPPORT 4
#define DATA_REQ_RESULT_NO_SCOPE_HANDLE_SUPPORT 5
#define DATA_REQ_RESULT_NO_MODE_SINGLE_RSP_SUPPORT 6
#define DATA_REQ_RESULT_NO_MODE_TIME_PERIOD_SUPPORT 7
#define DATA_REQ_RESULT_NO_MODE_TIME_NO_LIMIT_SUPPORT 8
#define DATA_REQ_RESULT_NO_PERSON_ID_SUPPORT 9
#define DATA_REQ_RESULT_UNKNOWN_PERSON_ID 11
#define DATA_REQ_RESULT_UNKNOWN_CLASS 12
#define DATA_REQ_RESULT_UNKNOWN_HANDLE 13
#define DATA_REQ_RESULT_UNSUPP_SCOPE 14
#define DATA_REQ_RESULT_UNSUPP_MODE 15
#define DATA_REQ_RESULT_INIT_MANAGER_OVERFLOW 16
#define DATA_REQ_RESULT_CONTINUATION_NOT_SUPPORTED 17
#define DATA_REQ_RESULT_INVALID_REQ_ID 18

typedef struct _DataResponse
{
    RelativeTime rel_time_stamp;
    DataReqResult data_req_result;
    OID_Type event_type;
    Any event_info;
} DataResponse;

typedef FLOAT_Type SimpleNuObsValue;

typedef struct _SimpleNuObsValueCmp
{
    intu16 count;
    intu16 length;
    SimpleNuObsValue value[1]; /* first element of the array */
} SimpleNuObsValueCmp;

typedef SFLOAT_Type BasicNuObsValue;

typedef struct _BasicNuObsValueCmp
{
    intu16 count;
    intu16 length;
    BasicNuObsValue value[1]; /* first element of the array */
} BasicNuObsValueCmp;

#ifndef __HIWARE__
#pragma options align=reset
#endif

#endif /* PHD_TYPES */