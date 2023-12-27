#ifndef __USBH_MTP_PTP_H__
#define __USBH_MTP_PTP_H__

#include <stdint.h>

#define PTP_USB_BULK_HDR_LEN    ((2 * sizeof(uint32_t)) + (2 * sizeof(uint16_t)))

typedef struct {
    uint32_t length;
    uint16_t type;
    uint16_t code;
    uint32_t trans_id;
    uint32_t param1;
    uint32_t param2;
    uint32_t param3;
    uint32_t param4;
    uint32_t param5;
} PTP_OpContainer_t;

typedef struct {
    uint32_t length;
    uint16_t type;
    uint16_t code;
    uint32_t trans_id;
    uint8_t payload[4096];
} PTP_DataContainer_t;

typedef struct {
    uint32_t length;
    uint16_t type;
    uint16_t code;
    uint32_t trans_id;
    uint32_t param1;
    uint32_t param2;
    uint32_t param3;
    uint32_t param4;
    uint32_t param5;
} PTP_RespContainer_t;

/* PTP USB Asynchronous Event Interrupt Data Format */
typedef struct {
    uint32_t length;
    uint16_t type;
    uint16_t code;
    uint32_t trans_id;
    uint32_t param1;
    uint32_t param2;
    uint32_t param3;
} PTP_EventContainer_t;


/* Operation Codes */

/* PTP v1.0 operation codes */
#define PTP_OC_Undefined                    0x1000U
#define PTP_OC_GetDeviceInfo                0x1001U
#define PTP_OC_OpenSession                  0x1002U
#define PTP_OC_CloseSession                 0x1003U
#define PTP_OC_GetStorageIDs                0x1004U
#define PTP_OC_GetStorageInfo               0x1005U
#define PTP_OC_GetNumObjects                0x1006U
#define PTP_OC_GetObjectHandles             0x1007U
#define PTP_OC_GetObjectInfo                0x1008U
#define PTP_OC_GetObject                    0x1009U
#define PTP_OC_GetThumb                     0x100AU
#define PTP_OC_DeleteObject                 0x100BU
#define PTP_OC_SendObjectInfo               0x100CU
#define PTP_OC_SendObject                   0x100DU
#define PTP_OC_InitiateCapture              0x100EU
#define PTP_OC_FormatStore                  0x100FU
#define PTP_OC_ResetDevice                  0x1010U
#define PTP_OC_SelfTest                     0x1011U
#define PTP_OC_SetObjectProtection          0x1012U
#define PTP_OC_PowerDown                    0x1013U
#define PTP_OC_GetDevicePropDesc            0x1014U
#define PTP_OC_GetDevicePropValue           0x1015U
#define PTP_OC_SetDevicePropValue           0x1016U
#define PTP_OC_ResetDevicePropValue         0x1017U
#define PTP_OC_TerminateOpenCapture         0x1018U
#define PTP_OC_MoveObject                   0x1019U
#define PTP_OC_CopyObject                   0x101AU
#define PTP_OC_GetPartialObject             0x101BU
#define PTP_OC_InitiateOpenCapture          0x101CU

/* PTP v1.1 operation codes */
#define PTP_OC_StartEnumHandles             0x101DU
#define PTP_OC_EnumHandles                  0x101EU
#define PTP_OC_StopEnumHandles              0x101FU
#define PTP_OC_GetVendorExtensionMaps       0x1020U
#define PTP_OC_GetVendorDeviceInfo          0x1021U
#define PTP_OC_GetResizedImageObject        0x1022U
#define PTP_OC_GetFilesystemManifest        0x1023U
#define PTP_OC_GetStreamInfo                0x1024U
#define PTP_OC_GetStream                    0x1025U

/* Microsoft / MTP extension codes */
#define PTP_OC_GetObjectPropsSupported      0x9801U
#define PTP_OC_GetObjectPropDesc            0x9802U
#define PTP_OC_GetObjectPropValue           0x9803U
#define PTP_OC_SetObjectPropValue           0x9804U
#define PTP_OC_GetObjPropList               0x9805U
#define PTP_OC_SetObjPropList               0x9806U
#define PTP_OC_GetInterdependendPropdesc    0x9807U
#define PTP_OC_SendObjectPropList           0x9808U
#define PTP_OC_GetObjectReferences          0x9810U
#define PTP_OC_SetObjectReferences          0x9811U
#define PTP_OC_UpdateDeviceFirmware         0x9812U
#define PTP_OC_Skip                         0x9820U


/* Response Codes */

/* PTP v1.0 response codes */
#define PTP_RC_Undefined                    0x2000U
#define PTP_RC_OK                           0x2001U
#define PTP_RC_GeneralError                 0x2002U
#define PTP_RC_SessionNotOpen               0x2003U
#define PTP_RC_InvalidTransactionID         0x2004U
#define PTP_RC_OperationNotSupported        0x2005U
#define PTP_RC_ParameterNotSupported        0x2006U
#define PTP_RC_IncompleteTransfer           0x2007U
#define PTP_RC_InvalidStorageId             0x2008U
#define PTP_RC_InvalidObjectHandle          0x2009U
#define PTP_RC_DevicePropNotSupported       0x200AU
#define PTP_RC_InvalidObjectFormatCode      0x200BU
#define PTP_RC_StoreFull                    0x200CU
#define PTP_RC_ObjectWriteProtected         0x200DU
#define PTP_RC_StoreReadOnly                0x200EU
#define PTP_RC_AccessDenied                 0x200FU
#define PTP_RC_NoThumbnailPresent           0x2010U
#define PTP_RC_SelfTestFailed               0x2011U
#define PTP_RC_PartialDeletion              0x2012U
#define PTP_RC_StoreNotAvailable            0x2013U
#define PTP_RC_SpecByFormatUnsupported      0x2014U
#define PTP_RC_NoValidObjectInfo            0x2015U
#define PTP_RC_InvalidCodeFormat            0x2016U
#define PTP_RC_UnknownVendorCode            0x2017U
#define PTP_RC_CaptureAlreadyTerminated     0x2018U
#define PTP_RC_DeviceBusy                   0x2019U
#define PTP_RC_InvalidParentObject          0x201AU
#define PTP_RC_InvalidDevicePropFormat      0x201BU
#define PTP_RC_InvalidDevicePropValue       0x201CU
#define PTP_RC_InvalidParameter             0x201DU
#define PTP_RC_SessionAlreadyOpened         0x201EU
#define PTP_RC_TransactionCanceled          0x201FU
#define PTP_RC_SpecOfDestinationUnsupported 0x2020U

/* PTP v1.1 response codes */
#define PTP_RC_InvalidEnumHandle            0x2021U
#define PTP_RC_NoStreamEnabled              0x2022U
#define PTP_RC_InvalidDataSet               0x2023U


/* USB container types */
#define PTP_USB_CONTAINER_UNDEFINED         0x0000U
#define PTP_USB_CONTAINER_COMMAND           0x0001U
#define PTP_USB_CONTAINER_DATA              0x0002U
#define PTP_USB_CONTAINER_RESPONSE          0x0003U
#define PTP_USB_CONTAINER_EVENT             0x0004U


/* Transaction data phase description */
#define PTP_DP_NODATA                       0x0000U // no data phase
#define PTP_DP_SENDDATA                     0x0001U // sending data
#define PTP_DP_GETDATA                      0x0002U // receiving data
#define PTP_DP_DATA_MASK                    0x00ffU // data phase mask


/* DeviceInfo data offset */
#define PTP_di_StandardVersion                            0U
#define PTP_di_VendorExtensionID                          2U
#define PTP_di_VendorExtensionVersion                     6U
#define PTP_di_VendorExtensionDesc                        8U
#define PTP_di_FunctionalMode                             8U
#define PTP_di_OperationsSupported                        10U

/* Max info items size */
#define PTP_SUPPORTED_OPERATIONS_NBR                      100U
#define PTP_SUPPORTED_EVENTS_NBR                          100U
#define PTP_SUPPORTED_PROPRIETIES_NBR                     100U
#define PTP_CAPTURE_FORMATS_NBR                           100U
#define PTP_IMAGE_FORMATS_NBR                             100U
#define PTP_MAX_STR_SIZE                                  255U

/* PTP device info structure */
typedef struct {
    uint16_t StandardVersion;
    uint32_t VendorExtensionID;
    uint16_t VendorExtensionVersion;
    uint8_t  VendorExtensionDesc[PTP_MAX_STR_SIZE];
    uint16_t FunctionalMode;
    uint32_t OperationsSupportedNbr;
    uint16_t OperationsSupported[PTP_SUPPORTED_OPERATIONS_NBR];
    uint32_t EventsSupportedNbr;
    uint16_t EventsSupported[PTP_SUPPORTED_EVENTS_NBR];
    uint32_t DevicePropertiesSupportedNbr;
    uint16_t DevicePropertiesSupported[PTP_SUPPORTED_PROPRIETIES_NBR];
    uint32_t CaptureFormatsNbr;
    uint16_t CaptureFormats[PTP_CAPTURE_FORMATS_NBR];
    uint32_t ImageFormatsNbr;
    uint16_t ImageFormats[PTP_IMAGE_FORMATS_NBR];
    uint8_t  Manufacturer[PTP_MAX_STR_SIZE];
    uint8_t  Model[PTP_MAX_STR_SIZE];
    uint8_t  DeviceVersion[PTP_MAX_STR_SIZE];
    uint8_t  SerialNumber[PTP_MAX_STR_SIZE];
} PTP_DeviceInfo_t;


#define PTP_MAX_STORAGE_UNITS_NBR   3

/* PTP storageIDs structute (returned by GetStorageIDs) */
typedef struct {
    uint32_t n;
    uint32_t Storage[PTP_MAX_STORAGE_UNITS_NBR];
} PTP_StorageIDs_t;


/* PTP StorageInfo structure (returned by GetStorageInfo) */
#define PTP_si_StorageType                                0U
#define PTP_si_FilesystemType                             2U
#define PTP_si_AccessCapability                           4U
#define PTP_si_MaxCapability                              6U
#define PTP_si_FreeSpaceInBytes                           14U
#define PTP_si_FreeSpaceInImages                          22U
#define PTP_si_StorageDescription                         26U

/* PTP Storage Types */
#define PTP_ST_Undefined                                  0x0000U
#define PTP_ST_FixedROM                                   0x0001U
#define PTP_ST_RemovableROM                               0x0002U
#define PTP_ST_FixedRAM                                   0x0003U
#define PTP_ST_RemovableRAM                               0x0004U

/* PTP FilesystemType Values */
#define PTP_FST_Undefined                                 0x0000U
#define PTP_FST_GenericFlat                               0x0001U
#define PTP_FST_GenericHierarchical                       0x0002U
#define PTP_FST_DCF                                       0x0003U

/* PTP StorageInfo AccessCapability Values */
#define PTP_AC_ReadWrite                                  0x0000U
#define PTP_AC_ReadOnly                                   0x0001U
#define PTP_AC_ReadOnly_with_Object_Deletion              0x0002U

typedef struct {
    uint16_t StorageType;
    uint16_t FilesystemType;
    uint16_t AccessCapability;
    uint64_t MaxCapability;
    uint64_t FreeSpaceInBytes;
    uint32_t FreeSpaceInImages;
    uint8_t  StorageDescription[PTP_MAX_STR_SIZE];
    uint8_t  VolumeLabel[PTP_MAX_STR_SIZE];
} PTP_StorageInfo_t;


/* PTP Object Format Codes */
/* ancillary formats */
#define PTP_OFC_Undefined                                 0x3000U
#define PTP_OFC_Defined                                   0x3800U
#define PTP_OFC_Association                               0x3001U
#define PTP_OFC_Script                                    0x3002U
#define PTP_OFC_Executable                                0x3003U
#define PTP_OFC_Text                                      0x3004U
#define PTP_OFC_HTML                                      0x3005U
#define PTP_OFC_DPOF                                      0x3006U
#define PTP_OFC_AIFF                                      0x3007U
#define PTP_OFC_WAV                                       0x3008U
#define PTP_OFC_MP3                                       0x3009U
#define PTP_OFC_AVI                                       0x300AU
#define PTP_OFC_MPEG                                      0x300BU
#define PTP_OFC_ASF                                       0x300CU
#define PTP_OFC_QT                                        0x300DU /* guessing */
/* image formats */
#define PTP_OFC_EXIF_JPEG                                 0x3801U
#define PTP_OFC_TIFF_EP                                   0x3802U
#define PTP_OFC_FlashPix                                  0x3803U
#define PTP_OFC_BMP                                       0x3804U
#define PTP_OFC_CIFF                                      0x3805U
#define PTP_OFC_Undefined_0x3806                          0x3806U
#define PTP_OFC_GIF                                       0x3807U
#define PTP_OFC_JFIF                                      0x3808U
#define PTP_OFC_PCD                                       0x3809U
#define PTP_OFC_PICT                                      0x380AU
#define PTP_OFC_PNG                                       0x380BU
#define PTP_OFC_Undefined_0x380C                          0x380CU
#define PTP_OFC_TIFF                                      0x380DU
#define PTP_OFC_TIFF_IT                                   0x380EU
#define PTP_OFC_JP2                                       0x380FU
#define PTP_OFC_JPX                                       0x3810U
/* ptp v1.1 has only DNG new */
#define PTP_OFC_DNG                                       0x3811U

/* MTP extensions */
#define PTP_OFC_MTP_MediaCard                             0xb211U
#define PTP_OFC_MTP_MediaCardGroup                        0xb212U
#define PTP_OFC_MTP_Encounter                             0xb213U
#define PTP_OFC_MTP_EncounterBox                          0xb214U
#define PTP_OFC_MTP_M4A                                   0xb215U
#define PTP_OFC_MTP_ZUNEUNDEFINED                         0xb217U/* Unknown file type */
#define PTP_OFC_MTP_Firmware                              0xb802U
#define PTP_OFC_MTP_WindowsImageFormat                    0xb881U
#define PTP_OFC_MTP_UndefinedAudio                        0xb900U
#define PTP_OFC_MTP_WMA                                   0xb901U
#define PTP_OFC_MTP_OGG                                   0xb902U
#define PTP_OFC_MTP_AAC                                   0xb903U
#define PTP_OFC_MTP_AudibleCod                            0xb904U
#define PTP_OFC_MTP_FLAC                                  0xb906U
#define PTP_OFC_MTP_SamsungPlaylist                       0xb909U
#define PTP_OFC_MTP_UndefinedVideo                        0xb980U
#define PTP_OFC_MTP_WMV                                   0xb981U
#define PTP_OFC_MTP_MP4                                   0xb982U
#define PTP_OFC_MTP_MP2                                   0xb983U
#define PTP_OFC_MTP_3GP                                   0xb984U
#define PTP_OFC_MTP_UndefinedCollection                   0xba00U
#define PTP_OFC_MTP_AbstractMultimediaAlbum               0xba01U
#define PTP_OFC_MTP_AbstractImageAlbum                    0xba02U
#define PTP_OFC_MTP_AbstractAudioAlbum                    0xba03U
#define PTP_OFC_MTP_AbstractVideoAlbum                    0xba04U
#define PTP_OFC_MTP_AbstractAudioVideoPlaylist            0xba05U
#define PTP_OFC_MTP_AbstractContactGroup                  0xba06U
#define PTP_OFC_MTP_AbstractMessageFolder                 0xba07U
#define PTP_OFC_MTP_AbstractChapteredProduction           0xba08U
#define PTP_OFC_MTP_AbstractAudioPlaylist                 0xba09U
#define PTP_OFC_MTP_AbstractVideoPlaylist                 0xba0aU
#define PTP_OFC_MTP_AbstractMediacast                     0xba0bU
#define PTP_OFC_MTP_WPLPlaylist                           0xba10U
#define PTP_OFC_MTP_M3UPlaylist                           0xba11U
#define PTP_OFC_MTP_MPLPlaylist                           0xba12U
#define PTP_OFC_MTP_ASXPlaylist                           0xba13U
#define PTP_OFC_MTP_PLSPlaylist                           0xba14U
#define PTP_OFC_MTP_UndefinedDocument                     0xba80U
#define PTP_OFC_MTP_AbstractDocument                      0xba81U
#define PTP_OFC_MTP_XMLDocument                           0xba82U
#define PTP_OFC_MTP_MSWordDocument                        0xba83U
#define PTP_OFC_MTP_MHTCompiledHTMLDocument               0xba84U
#define PTP_OFC_MTP_MSExcelSpreadsheetXLS                 0xba85U
#define PTP_OFC_MTP_MSPowerpointPresentationPPT           0xba86U
#define PTP_OFC_MTP_UndefinedMessage                      0xbb00U
#define PTP_OFC_MTP_AbstractMessage                       0xbb01U
#define PTP_OFC_MTP_UndefinedContact                      0xbb80U
#define PTP_OFC_MTP_AbstractContact                       0xbb81U
#define PTP_OFC_MTP_vCard2                                0xbb82U
#define PTP_OFC_MTP_vCard3                                0xbb83U
#define PTP_OFC_MTP_UndefinedCalendarItem                 0xbe00U
#define PTP_OFC_MTP_AbstractCalendarItem                  0xbe01U
#define PTP_OFC_MTP_vCalendar1                            0xbe02U
#define PTP_OFC_MTP_vCalendar2                            0xbe03U
#define PTP_OFC_MTP_UndefinedWindowsExecutable            0xbe80U
#define PTP_OFC_MTP_MediaCast                             0xbe81U
#define PTP_OFC_MTP_Section                               0xbe82U

/* MTP specific Object Properties */
#define PTP_OPC_StorageID                                 0xDC01U
#define PTP_OPC_ObjectFormat                              0xDC02U
#define PTP_OPC_ProtectionStatus                          0xDC03U
#define PTP_OPC_ObjectSize                                0xDC04U
#define PTP_OPC_AssociationType                           0xDC05U
#define PTP_OPC_AssociationDesc                           0xDC06U
#define PTP_OPC_ObjectFileName                            0xDC07U
#define PTP_OPC_DateCreated                               0xDC08U
#define PTP_OPC_DateModified                              0xDC09U
#define PTP_OPC_Keywords                                  0xDC0AU
#define PTP_OPC_ParentObject                              0xDC0BU
#define PTP_OPC_AllowedFolderContents                     0xDC0CU
#define PTP_OPC_Hidden                                    0xDC0DU
#define PTP_OPC_SystemObject                              0xDC0EU
#define PTP_OPC_PersistantUniqueObjectIdentifier          0xDC41U
#define PTP_OPC_SyncID                                    0xDC42U
#define PTP_OPC_PropertyBag                               0xDC43U
#define PTP_OPC_Name                                      0xDC44U
#define PTP_OPC_CreatedBy                                 0xDC45U
#define PTP_OPC_Artist                                    0xDC46U
#define PTP_OPC_DateAuthored                              0xDC47U
#define PTP_OPC_Description                               0xDC48U
#define PTP_OPC_URLReference                              0xDC49U
#define PTP_OPC_LanguageLocale                            0xDC4AU
#define PTP_OPC_CopyrightInformation                      0xDC4BU
#define PTP_OPC_Source                                    0xDC4CU
#define PTP_OPC_OriginLocation                            0xDC4DU
#define PTP_OPC_DateAdded                                 0xDC4EU
#define PTP_OPC_NonConsumable                             0xDC4FU
#define PTP_OPC_CorruptOrUnplayable                       0xDC50U
#define PTP_OPC_ProducerSerialNumber                      0xDC51U
#define PTP_OPC_RepresentativeSampleFormat                0xDC81U
#define PTP_OPC_RepresentativeSampleSize                  0xDC82U
#define PTP_OPC_RepresentativeSampleHeight                0xDC83U
#define PTP_OPC_RepresentativeSampleWidth                 0xDC84U
#define PTP_OPC_RepresentativeSampleDuration              0xDC85U
#define PTP_OPC_RepresentativeSampleData                  0xDC86U
#define PTP_OPC_Width                                     0xDC87U
#define PTP_OPC_Height                                    0xDC88U
#define PTP_OPC_Duration                                  0xDC89U
#define PTP_OPC_Rating                                    0xDC8AU
#define PTP_OPC_Track                                     0xDC8BU
#define PTP_OPC_Genre                                     0xDC8CU
#define PTP_OPC_Credits                                   0xDC8DU
#define PTP_OPC_Lyrics                                    0xDC8EU
#define PTP_OPC_SubscriptionContentID                     0xDC8FU
#define PTP_OPC_ProducedBy                                0xDC90U
#define PTP_OPC_UseCount                                  0xDC91U
#define PTP_OPC_SkipCount                                 0xDC92U
#define PTP_OPC_LastAccessed                              0xDC93U
#define PTP_OPC_ParentalRating                            0xDC94U
#define PTP_OPC_MetaGenre                                 0xDC95U
#define PTP_OPC_Composer                                  0xDC96U
#define PTP_OPC_EffectiveRating                           0xDC97U
#define PTP_OPC_Subtitle                                  0xDC98U
#define PTP_OPC_OriginalReleaseDate                       0xDC99U
#define PTP_OPC_AlbumName                                 0xDC9AU
#define PTP_OPC_AlbumArtist                               0xDC9BU
#define PTP_OPC_Mood                                      0xDC9CU
#define PTP_OPC_DRMStatus                                 0xDC9DU
#define PTP_OPC_SubDescription                            0xDC9EU
#define PTP_OPC_IsCropped                                 0xDCD1U
#define PTP_OPC_IsColorCorrected                          0xDCD2U
#define PTP_OPC_ImageBitDepth                             0xDCD3U
#define PTP_OPC_Fnumber                                   0xDCD4U
#define PTP_OPC_ExposureTime                              0xDCD5U
#define PTP_OPC_ExposureIndex                             0xDCD6U
#define PTP_OPC_DisplayName                               0xDCE0U
#define PTP_OPC_BodyText                                  0xDCE1U
#define PTP_OPC_Subject                                   0xDCE2U
#define PTP_OPC_Priority                                  0xDCE3U
#define PTP_OPC_GivenName                                 0xDD00U
#define PTP_OPC_MiddleNames                               0xDD01U
#define PTP_OPC_FamilyName                                0xDD02U
#define PTP_OPC_Prefix                                    0xDD03U
#define PTP_OPC_Suffix                                    0xDD04U
#define PTP_OPC_PhoneticGivenName                         0xDD05U
#define PTP_OPC_PhoneticFamilyName                        0xDD06U
#define PTP_OPC_EmailPrimary                              0xDD07U
#define PTP_OPC_EmailPersonal1                            0xDD08U
#define PTP_OPC_EmailPersonal2                            0xDD09U
#define PTP_OPC_EmailBusiness1                            0xDD0AU
#define PTP_OPC_EmailBusiness2                            0xDD0BU
#define PTP_OPC_EmailOthers                               0xDD0CU
#define PTP_OPC_PhoneNumberPrimary                        0xDD0DU
#define PTP_OPC_PhoneNumberPersonal                       0xDD0EU
#define PTP_OPC_PhoneNumberPersonal2                      0xDD0FU
#define PTP_OPC_PhoneNumberBusiness                       0xDD10U
#define PTP_OPC_PhoneNumberBusiness2                      0xDD11U
#define PTP_OPC_PhoneNumberMobile                         0xDD12U
#define PTP_OPC_PhoneNumberMobile2                        0xDD13U
#define PTP_OPC_FaxNumberPrimary                          0xDD14U
#define PTP_OPC_FaxNumberPersonal                         0xDD15U
#define PTP_OPC_FaxNumberBusiness                         0xDD16U
#define PTP_OPC_PagerNumber                               0xDD17U
#define PTP_OPC_PhoneNumberOthers                         0xDD18U
#define PTP_OPC_PrimaryWebAddress                         0xDD19U
#define PTP_OPC_PersonalWebAddress                        0xDD1AU
#define PTP_OPC_BusinessWebAddress                        0xDD1BU
#define PTP_OPC_InstantMessengerAddress                   0xDD1CU
#define PTP_OPC_InstantMessengerAddress2                  0xDD1DU
#define PTP_OPC_InstantMessengerAddress3                  0xDD1EU
#define PTP_OPC_PostalAddressPersonalFull                 0xDD1FU
#define PTP_OPC_PostalAddressPersonalFullLine1            0xDD20U
#define PTP_OPC_PostalAddressPersonalFullLine2            0xDD21U
#define PTP_OPC_PostalAddressPersonalFullCity             0xDD22U
#define PTP_OPC_PostalAddressPersonalFullRegion           0xDD23U
#define PTP_OPC_PostalAddressPersonalFullPostalCode       0xDD24U
#define PTP_OPC_PostalAddressPersonalFullCountry          0xDD25U
#define PTP_OPC_PostalAddressBusinessFull                 0xDD26U
#define PTP_OPC_PostalAddressBusinessLine1                0xDD27U
#define PTP_OPC_PostalAddressBusinessLine2                0xDD28U
#define PTP_OPC_PostalAddressBusinessCity                 0xDD29U
#define PTP_OPC_PostalAddressBusinessRegion               0xDD2AU
#define PTP_OPC_PostalAddressBusinessPostalCode           0xDD2BU
#define PTP_OPC_PostalAddressBusinessCountry              0xDD2CU
#define PTP_OPC_PostalAddressOtherFull                    0xDD2DU
#define PTP_OPC_PostalAddressOtherLine1                   0xDD2EU
#define PTP_OPC_PostalAddressOtherLine2                   0xDD2FU
#define PTP_OPC_PostalAddressOtherCity                    0xDD30U
#define PTP_OPC_PostalAddressOtherRegion                  0xDD31U
#define PTP_OPC_PostalAddressOtherPostalCode              0xDD32U
#define PTP_OPC_PostalAddressOtherCountry                 0xDD33U
#define PTP_OPC_OrganizationName                          0xDD34U
#define PTP_OPC_PhoneticOrganizationName                  0xDD35U
#define PTP_OPC_Role                                      0xDD36U
#define PTP_OPC_Birthdate                                 0xDD37U
#define PTP_OPC_MessageTo                                 0xDD40U
#define PTP_OPC_MessageCC                                 0xDD41U
#define PTP_OPC_MessageBCC                                0xDD42U
#define PTP_OPC_MessageRead                               0xDD43U
#define PTP_OPC_MessageReceivedTime                       0xDD44U
#define PTP_OPC_MessageSender                             0xDD45U
#define PTP_OPC_ActivityBeginTime                         0xDD50U
#define PTP_OPC_ActivityEndTime                           0xDD51U
#define PTP_OPC_ActivityLocation                          0xDD52U
#define PTP_OPC_ActivityRequiredAttendees                 0xDD54U
#define PTP_OPC_ActivityOptionalAttendees                 0xDD55U
#define PTP_OPC_ActivityResources                         0xDD56U
#define PTP_OPC_ActivityAccepted                          0xDD57U
#define PTP_OPC_Owner                                     0xDD5DU
#define PTP_OPC_Editor                                    0xDD5EU
#define PTP_OPC_Webmaster                                 0xDD5FU
#define PTP_OPC_URLSource                                 0xDD60U
#define PTP_OPC_URLDestination                            0xDD61U
#define PTP_OPC_TimeBookmark                              0xDD62U
#define PTP_OPC_ObjectBookmark                            0xDD63U
#define PTP_OPC_ByteBookmark                              0xDD64U
#define PTP_OPC_LastBuildDate                             0xDD70U
#define PTP_OPC_TimetoLive                                0xDD71U
#define PTP_OPC_MediaGUID                                 0xDD72U
#define PTP_OPC_TotalBitRate                              0xDE91U
#define PTP_OPC_BitRateType                               0xDE92U
#define PTP_OPC_SampleRate                                0xDE93U
#define PTP_OPC_NumberOfChannels                          0xDE94U
#define PTP_OPC_AudioBitDepth                             0xDE95U
#define PTP_OPC_ScanDepth                                 0xDE97U
#define PTP_OPC_AudioWAVECodec                            0xDE99U
#define PTP_OPC_AudioBitRate                              0xDE9AU
#define PTP_OPC_VideoFourCCCodec                          0xDE9BU
#define PTP_OPC_VideoBitRate                              0xDE9CU
#define PTP_OPC_FramesPerThousandSeconds                  0xDE9DU
#define PTP_OPC_KeyFrameDistance                          0xDE9EU
#define PTP_OPC_BufferSize                                0xDE9FU
#define PTP_OPC_EncodingQuality                           0xDEA0U
#define PTP_OPC_EncodingProfile                           0xDEA1U
#define PTP_OPC_BuyFlag                                   0xD901U

/* WiFi Provisioning MTP Extension property codes */
#define PTP_OPC_WirelessConfigurationFile                 0xB104U


/* PTP Association Types */
#define PTP_AT_Undefined                                  0x0000U
#define PTP_AT_GenericFolder                              0x0001U
#define PTP_AT_Album                                      0x0002U
#define PTP_AT_TimeSequence                               0x0003U
#define PTP_AT_HorizontalPanoramic                        0x0004U
#define PTP_AT_VerticalPanoramic                          0x0005U
#define PTP_AT_2DPanoramic                                0x0006U
#define PTP_AT_AncillaryData                              0x0007U


#define PTP_MAX_HANDLER_NBR                               0x255U

typedef struct {
    uint32_t n;
    uint32_t Handler[PTP_MAX_HANDLER_NBR];
} PTP_ObjectHandles_t;


#define PTP_oi_StorageID                                  0U
#define PTP_oi_ObjectFormat                               4U
#define PTP_oi_ProtectionStatus                           6U
#define PTP_oi_ObjectCompressedSize                       8U
#define PTP_oi_ThumbFormat                                12U
#define PTP_oi_ThumbCompressedSize                        14U
#define PTP_oi_ThumbPixWidth                              18U
#define PTP_oi_ThumbPixHeight                             22U
#define PTP_oi_ImagePixWidth                              26U
#define PTP_oi_ImagePixHeight                             30U
#define PTP_oi_ImageBitDepth                              34U
#define PTP_oi_ParentObject                               38U
#define PTP_oi_AssociationType                            42U
#define PTP_oi_AssociationDesc                            44U
#define PTP_oi_SequenceNumber                             48U
#define PTP_oi_filenamelen                                52U
#define PTP_oi_Filename                                   53U

typedef struct {
    uint32_t StorageID;
    uint16_t ObjectFormat;
    uint16_t ProtectionStatus;
    /* In the regular objectinfo this is 32bit, but we keep the general object size here
     that also arrives via other methods and so use 64bit */
    uint64_t ObjectCompressedSize;
    uint16_t ThumbFormat;
    uint32_t ThumbCompressedSize;
    uint32_t ThumbPixWidth;
    uint32_t ThumbPixHeight;
    uint32_t ImagePixWidth;
    uint32_t ImagePixHeight;
    uint32_t ImageBitDepth;
    uint32_t ParentObject;
    uint16_t AssociationType;
    uint32_t AssociationDesc;
    uint32_t SequenceNumber;
    uint8_t  Filename[PTP_MAX_STR_SIZE];
    uint32_t CaptureDate;
    uint32_t ModificationDate;
    uint8_t  Keywords[PTP_MAX_STR_SIZE];
} PTP_ObjectInfo_t;


/* Object Property Describing Dataset (DevicePropDesc) */
typedef union  _PTP_PropertyValue_t {
    char str[PTP_MAX_STR_SIZE];
    uint8_t u8;
    int8_t i8;
    uint16_t u16;
    int16_t i16;
    uint32_t u32;
    int32_t i32;
    uint64_t u64;
    int64_t i64;
    struct array
    {
        uint32_t count;
        union _PTP_PropertyValue_t *v;
    } a;
} PTP_PropertyValue_t;

typedef struct {
    PTP_PropertyValue_t MinimumValue;
    PTP_PropertyValue_t MaximumValue;
    PTP_PropertyValue_t StepSize;
} PTP_PropDescRangeForm_t;

/* Property Describing Dataset, Enum Form */
typedef struct {
    uint16_t NumberOfValues;
    PTP_PropertyValue_t SupportedValue[PTP_SUPPORTED_PROPRIETIES_NBR];
} PTP_PropDescEnumForm_t;


/* (MTP) Object Property pack/unpack */
#define PTP_opd_ObjectPropertyCode                        0U
#define PTP_opd_DataType                                  2U
#define PTP_opd_GetSet                                    4U
#define PTP_opd_FactoryDefaultValue                       5U

typedef struct {
    uint16_t    ObjectPropertyCode;
    uint16_t    DataType;
    uint8_t     GetSet;
    PTP_PropertyValue_t FactoryDefaultValue;
    uint32_t    GroupCode;
    uint8_t     FormFlag;
    union
    {
        PTP_PropDescEnumForm_t Enum;
        PTP_PropDescRangeForm_t  Range;
    } FORM;
} PTP_ObjectPropDesc_t;


/* Metadata lists for MTP operations */
typedef struct {
    uint16_t   property;
    uint16_t   datatype;
    uint32_t   ObjectHandle;
    PTP_PropertyValue_t propval;
} MTP_Properties_t;


/* Device Property Form Flag */
#define PTP_DPFF_None                                     0x00U
#define PTP_DPFF_Range                                    0x01U
#define PTP_DPFF_Enumeration                              0x02U

/* Object Property Codes used by MTP (first 3 are same as DPFF codes) */
#define PTP_OPFF_None                                     0x00U
#define PTP_OPFF_Range                                    0x01U
#define PTP_OPFF_Enumeration                              0x02U
#define PTP_OPFF_DateTime                                 0x03U
#define PTP_OPFF_FixedLengthArray                         0x04U
#define PTP_OPFF_RegularExpression                        0x05U
#define PTP_OPFF_ByteArray                                0x06U
#define PTP_OPFF_LongString                               0xFFU


/* Device Property pack/unpack */
#define PTP_dpd_DevicePropertyCode                        0U
#define PTP_dpd_DataType                                  2U
#define PTP_dpd_GetSet                                    4U
#define PTP_dpd_FactoryDefaultValue                       5U

/* Device Property Describing Dataset (DevicePropDesc) */
typedef struct
{
    uint16_t  DevicePropertyCode;
    uint16_t  DataType;
    uint8_t   GetSet;
    PTP_PropertyValue_t FactoryDefaultValue;
    PTP_PropertyValue_t CurrentValue;
    uint8_t   FormFlag;
    union
    {
        PTP_PropDescEnumForm_t  Enum;
        PTP_PropDescRangeForm_t  Range;
    } FORM;
} PTP_DevicePropDesc_t;


/* DataType Codes */
#define PTP_DTC_UNDEF                                     0x0000U
#define PTP_DTC_INT8                                      0x0001U
#define PTP_DTC_UINT8                                     0x0002U
#define PTP_DTC_INT16                                     0x0003U
#define PTP_DTC_UINT16                                    0x0004U
#define PTP_DTC_INT32                                     0x0005U
#define PTP_DTC_UINT32                                    0x0006U
#define PTP_DTC_INT64                                     0x0007U
#define PTP_DTC_UINT64                                    0x0008U
#define PTP_DTC_INT128                                    0x0009U
#define PTP_DTC_UINT128                                   0x000AU

#define PTP_DTC_ARRAY_MASK                                0x4000U

#define PTP_DTC_AINT8                                     (PTP_DTC_ARRAY_MASK | PTP_DTC_INT8)
#define PTP_DTC_AUINT8                                    (PTP_DTC_ARRAY_MASK | PTP_DTC_UINT8)
#define PTP_DTC_AINT16                                    (PTP_DTC_ARRAY_MASK | PTP_DTC_INT16)
#define PTP_DTC_AUINT16                                   (PTP_DTC_ARRAY_MASK | PTP_DTC_UINT16)
#define PTP_DTC_AINT32                                    (PTP_DTC_ARRAY_MASK | PTP_DTC_INT32)
#define PTP_DTC_AUINT32                                   (PTP_DTC_ARRAY_MASK | PTP_DTC_UINT32)
#define PTP_DTC_AINT64                                    (PTP_DTC_ARRAY_MASK | PTP_DTC_INT64)
#define PTP_DTC_AUINT64                                   (PTP_DTC_ARRAY_MASK | PTP_DTC_UINT64)
#define PTP_DTC_AINT128                                   (PTP_DTC_ARRAY_MASK | PTP_DTC_INT128)
#define PTP_DTC_AUINT128                                  (PTP_DTC_ARRAY_MASK | PTP_DTC_UINT128)

#define PTP_DTC_STR                                       0xFFFFU


/* PTP Event Codes */
#define PTP_EC_Undefined                                  0x4000U
#define PTP_EC_CancelTransaction                          0x4001U
#define PTP_EC_ObjectAdded                                0x4002U
#define PTP_EC_ObjectRemoved                              0x4003U
#define PTP_EC_StoreAdded                                 0x4004U
#define PTP_EC_StoreRemoved                               0x4005U
#define PTP_EC_DevicePropChanged                          0x4006U
#define PTP_EC_ObjectInfoChanged                          0x4007U
#define PTP_EC_DeviceInfoChanged                          0x4008U
#define PTP_EC_RequestObjectTransfer                      0x4009U
#define PTP_EC_StoreFull                                  0x400AU
#define PTP_EC_DeviceReset                                0x400BU
#define PTP_EC_StorageInfoChanged                         0x400CU
#define PTP_EC_CaptureComplete                            0x400DU
#define PTP_EC_UnreportedStatus                           0x400EU


void PTP_GetDevicePropValue(USBH_Info_t *phost, uint32_t *offset, uint32_t total, PTP_PropertyValue_t *value, uint16_t datatype);

void PTP_GetString(uint8_t *str, uint8_t *data, uint16_t *len);

uint32_t PTP_GetArray16(uint16_t *array, uint8_t *data, uint32_t offset);
uint32_t PTP_GetArray32(uint32_t *array, uint8_t *data, uint32_t offset);

void PTP_DecodeDeviceInfo(USBH_Info_t *phost, PTP_DeviceInfo_t *dev_info);

void PTP_DecodeStorageInfo(USBH_Info_t *phost, PTP_StorageInfo_t *storage_info);

void PTP_DecodeObjectInfo(USBH_Info_t *phost, PTP_ObjectInfo_t *object_info);

void PTP_DecodeObjectPropDesc(USBH_Info_t *phost, PTP_ObjectPropDesc_t *opd, uint32_t opdlen);

uint32_t PTP_DecodeObjectPropList(USBH_Info_t *phost, MTP_Properties_t *props, uint32_t len);


#define PTP_LE16(addr)  *((uint16_t *)(addr))
#define PTP_LE32(addr)  *((uint32_t *)(addr))
#define PTP_LE64(addr)  *((uint64_t *)(addr))


#endif  // __USBH_MTP_PTP_H__
