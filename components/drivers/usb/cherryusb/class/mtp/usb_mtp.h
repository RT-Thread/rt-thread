/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Copyright (c) 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_MTP_H
#define USB_MTP_H

// clang-format off
#define MTP_STANDARD_VERSION            100

// Container Types
#define MTP_CONTAINER_TYPE_UNDEFINED    0
#define MTP_CONTAINER_TYPE_COMMAND      1
#define MTP_CONTAINER_TYPE_DATA         2
#define MTP_CONTAINER_TYPE_RESPONSE     3
#define MTP_CONTAINER_TYPE_EVENT        4

// Container Offsets
#define MTP_CONTAINER_LENGTH_OFFSET             0
#define MTP_CONTAINER_TYPE_OFFSET               4
#define MTP_CONTAINER_CODE_OFFSET               6
#define MTP_CONTAINER_TRANSACTION_ID_OFFSET     8
#define MTP_CONTAINER_PARAMETER_OFFSET          12
#define MTP_CONTAINER_HEADER_SIZE               12

// Maximum buffer size for a MTP packet.
#define MTP_BUFFER_SIZE 16384

// MTP Data Types
#define MTP_TYPE_UNDEFINED      0x0000          // Undefined
#define MTP_TYPE_INT8           0x0001          // Signed 8-bit integer
#define MTP_TYPE_UINT8          0x0002          // Unsigned 8-bit integer
#define MTP_TYPE_INT16          0x0003          // Signed 16-bit integer
#define MTP_TYPE_UINT16         0x0004          // Unsigned 16-bit integer
#define MTP_TYPE_INT32          0x0005          // Signed 32-bit integer
#define MTP_TYPE_UINT32         0x0006          // Unsigned 32-bit integer
#define MTP_TYPE_INT64          0x0007          // Signed 64-bit integer
#define MTP_TYPE_UINT64         0x0008          // Unsigned 64-bit integer
#define MTP_TYPE_INT128         0x0009          // Signed 128-bit integer
#define MTP_TYPE_UINT128        0x000A          // Unsigned 128-bit integer
#define MTP_TYPE_AINT8          0x4001          // Array of signed 8-bit integers
#define MTP_TYPE_AUINT8         0x4002          // Array of unsigned 8-bit integers
#define MTP_TYPE_AINT16         0x4003          // Array of signed 16-bit integers
#define MTP_TYPE_AUINT16        0x4004          // Array of unsigned 16-bit integers
#define MTP_TYPE_AINT32         0x4005          // Array of signed 32-bit integers
#define MTP_TYPE_AUINT32        0x4006          // Array of unsigned 32-bit integers
#define MTP_TYPE_AINT64         0x4007          // Array of signed 64-bit integers
#define MTP_TYPE_AUINT64        0x4008          // Array of unsigned 64-bit integers
#define MTP_TYPE_AINT128        0x4009          // Array of signed 128-bit integers
#define MTP_TYPE_AUINT128       0x400A          // Array of unsigned 128-bit integers
#define MTP_TYPE_STR            0xFFFF          // Variable-length Unicode string

// MTP Format Codes
#define MTP_FORMAT_UNDEFINED                            0x3000   // Undefined object
#define MTP_FORMAT_ASSOCIATION                          0x3001   // Association (for example, a folder)
#define MTP_FORMAT_SCRIPT                               0x3002   // Device model-specific script
#define MTP_FORMAT_EXECUTABLE                           0x3003   // Device model-specific binary executable
#define MTP_FORMAT_TEXT                                 0x3004   // Text file
#define MTP_FORMAT_HTML                                 0x3005   // Hypertext Markup Language file (text)
#define MTP_FORMAT_DPOF                                 0x3006   // Digital Print Order Format file (text)
#define MTP_FORMAT_AIFF                                 0x3007   // Audio clip
#define MTP_FORMAT_WAV                                  0x3008   // Audio clip
#define MTP_FORMAT_MP3                                  0x3009   // Audio clip
#define MTP_FORMAT_AVI                                  0x300A   // Video clip
#define MTP_FORMAT_MPEG                                 0x300B   // Video clip
#define MTP_FORMAT_ASF                                  0x300C   // Microsoft Advanced Streaming Format (video)
#define MTP_FORMAT_DEFINED                              0x3800   // Unknown image object
#define MTP_FORMAT_EXIF_JPEG                            0x3801   // Exchangeable File Format, JEIDA standard
#define MTP_FORMAT_TIFF_EP                              0x3802   // Tag Image File Format for Electronic Photography
#define MTP_FORMAT_FLASHPIX                             0x3803   // Structured Storage Image Format
#define MTP_FORMAT_BMP                                  0x3804   // Microsoft Windows Bitmap file
#define MTP_FORMAT_CIFF                                 0x3805   // Canon Camera Image File Format
#define MTP_FORMAT_GIF                                  0x3807   // Graphics Interchange Format
#define MTP_FORMAT_JFIF                                 0x3808   // JPEG File Interchange Format
#define MTP_FORMAT_CD                                   0x3809   // PhotoCD Image Pac
#define MTP_FORMAT_PICT                                 0x380A   // Quickdraw Image Format
#define MTP_FORMAT_PNG                                  0x380B   // Portable Network Graphics
#define MTP_FORMAT_TIFF                                 0x380D   // Tag Image File Format
#define MTP_FORMAT_TIFF_IT                              0x380E   // Tag Image File Format for Information Technology (graphic arts)
#define MTP_FORMAT_JP2                                  0x380F   // JPEG2000 Baseline File Format
#define MTP_FORMAT_JPX                                  0x3810   // JPEG2000 Extended File Format
#define MTP_FORMAT_DNG                                  0x3811   // Digital Negative
#define MTP_FORMAT_HEIF                                 0x3812   // HEIF images
#define MTP_FORMAT_UNDEFINED_FIRMWARE                   0xB802
#define MTP_FORMAT_WINDOWS_IMAGE_FORMAT                 0xB881
#define MTP_FORMAT_UNDEFINED_AUDIO                      0xB900
#define MTP_FORMAT_WMA                                  0xB901
#define MTP_FORMAT_OGG                                  0xB902
#define MTP_FORMAT_AAC                                  0xB903
#define MTP_FORMAT_AUDIBLE                              0xB904
#define MTP_FORMAT_FLAC                                 0xB906
#define MTP_FORMAT_UNDEFINED_VIDEO                      0xB980
#define MTP_FORMAT_WMV                                  0xB981
#define MTP_FORMAT_MP4_CONTAINER                        0xB982  // ISO 14496-1
#define MTP_FORMAT_MP2                                  0xB983
#define MTP_FORMAT_3GP_CONTAINER                        0xB984  // 3GPP file format. Details: http://www.3gpp.org/ftp/Specs/html-info/26244.htm (page title - \u201cTransparent end-to-end packet switched streaming service, 3GPP file format\u201d).
#define MTP_FORMAT_UNDEFINED_COLLECTION                 0xBA00
#define MTP_FORMAT_ABSTRACT_MULTIMEDIA_ALBUM            0xBA01
#define MTP_FORMAT_ABSTRACT_IMAGE_ALBUM                 0xBA02
#define MTP_FORMAT_ABSTRACT_AUDIO_ALBUM                 0xBA03
#define MTP_FORMAT_ABSTRACT_VIDEO_ALBUM                 0xBA04
#define MTP_FORMAT_ABSTRACT_AV_PLAYLIST                 0xBA05
#define MTP_FORMAT_ABSTRACT_CONTACT_GROUP               0xBA06
#define MTP_FORMAT_ABSTRACT_MESSAGE_FOLDER              0xBA07
#define MTP_FORMAT_ABSTRACT_CHAPTERED_PRODUCTION        0xBA08
#define MTP_FORMAT_ABSTRACT_AUDIO_PLAYLIST              0xBA09
#define MTP_FORMAT_ABSTRACT_VIDEO_PLAYLIST              0xBA0A
#define MTP_FORMAT_ABSTRACT_MEDIACAST                   0xBA0B // For use with mediacasts; references multimedia enclosures of RSS feeds or episodic content
#define MTP_FORMAT_WPL_PLAYLIST                         0xBA10
#define MTP_FORMAT_M3U_PLAYLIST                         0xBA11
#define MTP_FORMAT_MPL_PLAYLIST                         0xBA12
#define MTP_FORMAT_ASX_PLAYLIST                         0xBA13
#define MTP_FORMAT_PLS_PLAYLIST                         0xBA14
#define MTP_FORMAT_UNDEFINED_DOCUMENT                   0xBA80
#define MTP_FORMAT_ABSTRACT_DOCUMENT                    0xBA81
#define MTP_FORMAT_XML_DOCUMENT                         0xBA82
#define MTP_FORMAT_MS_WORD_DOCUMENT                     0xBA83
#define MTP_FORMAT_MHT_COMPILED_HTML_DOCUMENT           0xBA84
#define MTP_FORMAT_MS_EXCEL_SPREADSHEET                 0xBA85
#define MTP_FORMAT_MS_POWERPOINT_PRESENTATION           0xBA86
#define MTP_FORMAT_UNDEFINED_MESSAGE                    0xBB00
#define MTP_FORMAT_ABSTRACT_MESSSAGE                    0xBB01
#define MTP_FORMAT_UNDEFINED_CONTACT                    0xBB80
#define MTP_FORMAT_ABSTRACT_CONTACT                     0xBB81
#define MTP_FORMAT_VCARD_2                              0xBB82

// MTP Object Property Codes
#define MTP_PROPERTY_STORAGE_ID                             0xDC01
#define MTP_PROPERTY_OBJECT_FORMAT                          0xDC02
#define MTP_PROPERTY_PROTECTION_STATUS                      0xDC03
#define MTP_PROPERTY_OBJECT_SIZE                            0xDC04
#define MTP_PROPERTY_ASSOCIATION_TYPE                       0xDC05
#define MTP_PROPERTY_ASSOCIATION_DESC                       0xDC06
#define MTP_PROPERTY_OBJECT_FILE_NAME                       0xDC07
#define MTP_PROPERTY_DATE_CREATED                           0xDC08
#define MTP_PROPERTY_DATE_MODIFIED                          0xDC09
#define MTP_PROPERTY_KEYWORDS                               0xDC0A
#define MTP_PROPERTY_PARENT_OBJECT                          0xDC0B
#define MTP_PROPERTY_ALLOWED_FOLDER_CONTENTS                0xDC0C
#define MTP_PROPERTY_HIDDEN                                 0xDC0D
#define MTP_PROPERTY_SYSTEM_OBJECT                          0xDC0E
#define MTP_PROPERTY_PERSISTENT_UID                         0xDC41
#define MTP_PROPERTY_SYNC_ID                                0xDC42
#define MTP_PROPERTY_PROPERTY_BAG                           0xDC43
#define MTP_PROPERTY_NAME                                   0xDC44
#define MTP_PROPERTY_CREATED_BY                             0xDC45
#define MTP_PROPERTY_ARTIST                                 0xDC46
#define MTP_PROPERTY_DATE_AUTHORED                          0xDC47
#define MTP_PROPERTY_DESCRIPTION                            0xDC48
#define MTP_PROPERTY_URL_REFERENCE                          0xDC49
#define MTP_PROPERTY_LANGUAGE_LOCALE                        0xDC4A
#define MTP_PROPERTY_COPYRIGHT_INFORMATION                  0xDC4B
#define MTP_PROPERTY_SOURCE                                 0xDC4C
#define MTP_PROPERTY_ORIGIN_LOCATION                        0xDC4D
#define MTP_PROPERTY_DATE_ADDED                             0xDC4E
#define MTP_PROPERTY_NON_CONSUMABLE                         0xDC4F
#define MTP_PROPERTY_CORRUPT_UNPLAYABLE                     0xDC50
#define MTP_PROPERTY_PRODUCER_SERIAL_NUMBER                 0xDC51
#define MTP_PROPERTY_REPRESENTATIVE_SAMPLE_FORMAT           0xDC81
#define MTP_PROPERTY_REPRESENTATIVE_SAMPLE_SIZE             0xDC82
#define MTP_PROPERTY_REPRESENTATIVE_SAMPLE_HEIGHT           0xDC83
#define MTP_PROPERTY_REPRESENTATIVE_SAMPLE_WIDTH            0xDC84
#define MTP_PROPERTY_REPRESENTATIVE_SAMPLE_DURATION         0xDC85
#define MTP_PROPERTY_REPRESENTATIVE_SAMPLE_DATA             0xDC86
#define MTP_PROPERTY_WIDTH                                  0xDC87
#define MTP_PROPERTY_HEIGHT                                 0xDC88
#define MTP_PROPERTY_DURATION                               0xDC89
#define MTP_PROPERTY_RATING                                 0xDC8A
#define MTP_PROPERTY_TRACK                                  0xDC8B
#define MTP_PROPERTY_GENRE                                  0xDC8C
#define MTP_PROPERTY_CREDITS                                0xDC8D
#define MTP_PROPERTY_LYRICS                                 0xDC8E
#define MTP_PROPERTY_SUBSCRIPTION_CONTENT_ID                0xDC8F
#define MTP_PROPERTY_PRODUCED_BY                            0xDC90
#define MTP_PROPERTY_USE_COUNT                              0xDC91
#define MTP_PROPERTY_SKIP_COUNT                             0xDC92
#define MTP_PROPERTY_LAST_ACCESSED                          0xDC93
#define MTP_PROPERTY_PARENTAL_RATING                        0xDC94
#define MTP_PROPERTY_META_GENRE                             0xDC95
#define MTP_PROPERTY_COMPOSER                               0xDC96
#define MTP_PROPERTY_EFFECTIVE_RATING                       0xDC97
#define MTP_PROPERTY_SUBTITLE                               0xDC98
#define MTP_PROPERTY_ORIGINAL_RELEASE_DATE                  0xDC99
#define MTP_PROPERTY_ALBUM_NAME                             0xDC9A
#define MTP_PROPERTY_ALBUM_ARTIST                           0xDC9B
#define MTP_PROPERTY_MOOD                                   0xDC9C
#define MTP_PROPERTY_DRM_STATUS                             0xDC9D
#define MTP_PROPERTY_SUB_DESCRIPTION                        0xDC9E
#define MTP_PROPERTY_IS_CROPPED                             0xDCD1
#define MTP_PROPERTY_IS_COLOUR_CORRECTED                    0xDCD2
#define MTP_PROPERTY_IMAGE_BIT_DEPTH                        0xDCD3
#define MTP_PROPERTY_F_NUMBER                               0xDCD4
#define MTP_PROPERTY_EXPOSURE_TIME                          0xDCD5
#define MTP_PROPERTY_EXPOSURE_INDEX                         0xDCD6
#define MTP_PROPERTY_TOTAL_BITRATE                          0xDE91
#define MTP_PROPERTY_BITRATE_TYPE                           0xDE92
#define MTP_PROPERTY_SAMPLE_RATE                            0xDE93
#define MTP_PROPERTY_NUMBER_OF_CHANNELS                     0xDE94
#define MTP_PROPERTY_AUDIO_BIT_DEPTH                        0xDE95
#define MTP_PROPERTY_SCAN_TYPE                              0xDE97
#define MTP_PROPERTY_AUDIO_WAVE_CODEC                       0xDE99
#define MTP_PROPERTY_AUDIO_BITRATE                          0xDE9A
#define MTP_PROPERTY_VIDEO_FOURCC_CODEC                     0xDE9B
#define MTP_PROPERTY_VIDEO_BITRATE                          0xDE9C
#define MTP_PROPERTY_FRAMES_PER_THOUSAND_SECONDS            0xDE9D
#define MTP_PROPERTY_KEYFRAME_DISTANCE                      0xDE9E
#define MTP_PROPERTY_BUFFER_SIZE                            0xDE9F
#define MTP_PROPERTY_ENCODING_QUALITY                       0xDEA0
#define MTP_PROPERTY_ENCODING_PROFILE                       0xDEA1
#define MTP_PROPERTY_DISPLAY_NAME                           0xDCE0
#define MTP_PROPERTY_BODY_TEXT                              0xDCE1
#define MTP_PROPERTY_SUBJECT                                0xDCE2
#define MTP_PROPERTY_PRIORITY                               0xDCE3
#define MTP_PROPERTY_GIVEN_NAME                             0xDD00
#define MTP_PROPERTY_MIDDLE_NAMES                           0xDD01
#define MTP_PROPERTY_FAMILY_NAME                            0xDD02
#define MTP_PROPERTY_PREFIX                                 0xDD03
#define MTP_PROPERTY_SUFFIX                                 0xDD04
#define MTP_PROPERTY_PHONETIC_GIVEN_NAME                    0xDD05
#define MTP_PROPERTY_PHONETIC_FAMILY_NAME                   0xDD06
#define MTP_PROPERTY_EMAIL_PRIMARY                          0xDD07
#define MTP_PROPERTY_EMAIL_PERSONAL_1                       0xDD08
#define MTP_PROPERTY_EMAIL_PERSONAL_2                       0xDD09
#define MTP_PROPERTY_EMAIL_BUSINESS_1                       0xDD0A
#define MTP_PROPERTY_EMAIL_BUSINESS_2                       0xDD0B
#define MTP_PROPERTY_EMAIL_OTHERS                           0xDD0C
#define MTP_PROPERTY_PHONE_NUMBER_PRIMARY                   0xDD0D
#define MTP_PROPERTY_PHONE_NUMBER_PERSONAL                  0xDD0E
#define MTP_PROPERTY_PHONE_NUMBER_PERSONAL_2                0xDD0F
#define MTP_PROPERTY_PHONE_NUMBER_BUSINESS                  0xDD10
#define MTP_PROPERTY_PHONE_NUMBER_BUSINESS_2                0xDD11
#define MTP_PROPERTY_PHONE_NUMBER_MOBILE                    0xDD12
#define MTP_PROPERTY_PHONE_NUMBER_MOBILE_2                  0xDD13
#define MTP_PROPERTY_FAX_NUMBER_PRIMARY                     0xDD14
#define MTP_PROPERTY_FAX_NUMBER_PERSONAL                    0xDD15
#define MTP_PROPERTY_FAX_NUMBER_BUSINESS                    0xDD16
#define MTP_PROPERTY_PAGER_NUMBER                           0xDD17
#define MTP_PROPERTY_PHONE_NUMBER_OTHERS                    0xDD18
#define MTP_PROPERTY_PRIMARY_WEB_ADDRESS                    0xDD19
#define MTP_PROPERTY_PERSONAL_WEB_ADDRESS                   0xDD1A
#define MTP_PROPERTY_BUSINESS_WEB_ADDRESS                   0xDD1B
#define MTP_PROPERTY_INSTANT_MESSANGER_ADDRESS              0xDD1C
#define MTP_PROPERTY_INSTANT_MESSANGER_ADDRESS_2            0xDD1D
#define MTP_PROPERTY_INSTANT_MESSANGER_ADDRESS_3            0xDD1E
#define MTP_PROPERTY_POSTAL_ADDRESS_PERSONAL_FULL           0xDD1F
#define MTP_PROPERTY_POSTAL_ADDRESS_PERSONAL_LINE_1         0xDD20
#define MTP_PROPERTY_POSTAL_ADDRESS_PERSONAL_LINE_2         0xDD21
#define MTP_PROPERTY_POSTAL_ADDRESS_PERSONAL_CITY           0xDD22
#define MTP_PROPERTY_POSTAL_ADDRESS_PERSONAL_REGION         0xDD23
#define MTP_PROPERTY_POSTAL_ADDRESS_PERSONAL_POSTAL_CODE    0xDD24
#define MTP_PROPERTY_POSTAL_ADDRESS_PERSONAL_COUNTRY        0xDD25
#define MTP_PROPERTY_POSTAL_ADDRESS_BUSINESS_FULL           0xDD26
#define MTP_PROPERTY_POSTAL_ADDRESS_BUSINESS_LINE_1         0xDD27
#define MTP_PROPERTY_POSTAL_ADDRESS_BUSINESS_LINE_2         0xDD28
#define MTP_PROPERTY_POSTAL_ADDRESS_BUSINESS_CITY           0xDD29
#define MTP_PROPERTY_POSTAL_ADDRESS_BUSINESS_REGION         0xDD2A
#define MTP_PROPERTY_POSTAL_ADDRESS_BUSINESS_POSTAL_CODE    0xDD2B
#define MTP_PROPERTY_POSTAL_ADDRESS_BUSINESS_COUNTRY        0xDD2C
#define MTP_PROPERTY_POSTAL_ADDRESS_OTHER_FULL              0xDD2D
#define MTP_PROPERTY_POSTAL_ADDRESS_OTHER_LINE_1            0xDD2E
#define MTP_PROPERTY_POSTAL_ADDRESS_OTHER_LINE_2            0xDD2F
#define MTP_PROPERTY_POSTAL_ADDRESS_OTHER_CITY              0xDD30
#define MTP_PROPERTY_POSTAL_ADDRESS_OTHER_REGION            0xDD31
#define MTP_PROPERTY_POSTAL_ADDRESS_OTHER_POSTAL_CODE       0xDD32
#define MTP_PROPERTY_POSTAL_ADDRESS_OTHER_COUNTRY           0xDD33
#define MTP_PROPERTY_ORGANIZATION_NAME                      0xDD34
#define MTP_PROPERTY_PHONETIC_ORGANIZATION_NAME             0xDD35
#define MTP_PROPERTY_ROLE                                   0xDD36
#define MTP_PROPERTY_BIRTHDATE                              0xDD37
#define MTP_PROPERTY_MESSAGE_TO                             0xDD40
#define MTP_PROPERTY_MESSAGE_CC                             0xDD41
#define MTP_PROPERTY_MESSAGE_BCC                            0xDD42
#define MTP_PROPERTY_MESSAGE_READ                           0xDD43
#define MTP_PROPERTY_MESSAGE_RECEIVED_TIME                  0xDD44
#define MTP_PROPERTY_MESSAGE_SENDER                         0xDD45
#define MTP_PROPERTY_ACTIVITY_BEGIN_TIME                    0xDD50
#define MTP_PROPERTY_ACTIVITY_END_TIME                      0xDD51
#define MTP_PROPERTY_ACTIVITY_LOCATION                      0xDD52
#define MTP_PROPERTY_ACTIVITY_REQUIRED_ATTENDEES            0xDD54
#define MTP_PROPERTY_ACTIVITY_OPTIONAL_ATTENDEES            0xDD55
#define MTP_PROPERTY_ACTIVITY_RESOURCES                     0xDD56
#define MTP_PROPERTY_ACTIVITY_ACCEPTED                      0xDD57
#define MTP_PROPERTY_ACTIVITY_TENTATIVE                     0xDD58
#define MTP_PROPERTY_ACTIVITY_DECLINED                      0xDD59
#define MTP_PROPERTY_ACTIVITY_REMAINDER_TIME                0xDD5A
#define MTP_PROPERTY_ACTIVITY_OWNER                         0xDD5B
#define MTP_PROPERTY_ACTIVITY_STATUS                        0xDD5C
#define MTP_PROPERTY_OWNER                                  0xDD5D
#define MTP_PROPERTY_EDITOR                                 0xDD5E
#define MTP_PROPERTY_WEBMASTER                              0xDD5F
#define MTP_PROPERTY_URL_SOURCE                             0xDD60
#define MTP_PROPERTY_URL_DESTINATION                        0xDD61
#define MTP_PROPERTY_TIME_BOOKMARK                          0xDD62
#define MTP_PROPERTY_OBJECT_BOOKMARK                        0xDD63
#define MTP_PROPERTY_BYTE_BOOKMARK                          0xDD64
#define MTP_PROPERTY_LAST_BUILD_DATE                        0xDD70
#define MTP_PROPERTY_TIME_TO_LIVE                           0xDD71
#define MTP_PROPERTY_MEDIA_GUID                             0xDD72

// MTP Device Property Codes
#define MTP_DEVICE_PROPERTY_UNDEFINED                       0x5000
#define MTP_DEVICE_PROPERTY_BATTERY_LEVEL                   0x5001
#define MTP_DEVICE_PROPERTY_FUNCTIONAL_MODE                 0x5002
#define MTP_DEVICE_PROPERTY_IMAGE_SIZE                      0x5003
#define MTP_DEVICE_PROPERTY_COMPRESSION_SETTING             0x5004
#define MTP_DEVICE_PROPERTY_WHITE_BALANCE                   0x5005
#define MTP_DEVICE_PROPERTY_RGB_GAIN                        0x5006
#define MTP_DEVICE_PROPERTY_F_NUMBER                        0x5007
#define MTP_DEVICE_PROPERTY_FOCAL_LENGTH                    0x5008
#define MTP_DEVICE_PROPERTY_FOCUS_DISTANCE                  0x5009
#define MTP_DEVICE_PROPERTY_FOCUS_MODE                      0x500A
#define MTP_DEVICE_PROPERTY_EXPOSURE_METERING_MODE          0x500B
#define MTP_DEVICE_PROPERTY_FLASH_MODE                      0x500C
#define MTP_DEVICE_PROPERTY_EXPOSURE_TIME                   0x500D
#define MTP_DEVICE_PROPERTY_EXPOSURE_PROGRAM_MODE           0x500E
#define MTP_DEVICE_PROPERTY_EXPOSURE_INDEX                  0x500F
#define MTP_DEVICE_PROPERTY_EXPOSURE_BIAS_COMPENSATION      0x5010
#define MTP_DEVICE_PROPERTY_DATETIME                        0x5011
#define MTP_DEVICE_PROPERTY_CAPTURE_DELAY                   0x5012
#define MTP_DEVICE_PROPERTY_STILL_CAPTURE_MODE              0x5013
#define MTP_DEVICE_PROPERTY_CONTRAST                        0x5014
#define MTP_DEVICE_PROPERTY_SHARPNESS                       0x5015
#define MTP_DEVICE_PROPERTY_DIGITAL_ZOOM                    0x5016
#define MTP_DEVICE_PROPERTY_EFFECT_MODE                     0x5017
#define MTP_DEVICE_PROPERTY_BURST_NUMBER                    0x5018
#define MTP_DEVICE_PROPERTY_BURST_INTERVAL                  0x5019
#define MTP_DEVICE_PROPERTY_TIMELAPSE_NUMBER                0x501A
#define MTP_DEVICE_PROPERTY_TIMELAPSE_INTERVAL              0x501B
#define MTP_DEVICE_PROPERTY_FOCUS_METERING_MODE             0x501C
#define MTP_DEVICE_PROPERTY_UPLOAD_URL                      0x501D
#define MTP_DEVICE_PROPERTY_ARTIST                          0x501E
#define MTP_DEVICE_PROPERTY_COPYRIGHT_INFO                  0x501F
#define MTP_DEVICE_PROPERTY_SYNCHRONIZATION_PARTNER         0xD401
#define MTP_DEVICE_PROPERTY_DEVICE_FRIENDLY_NAME            0xD402
#define MTP_DEVICE_PROPERTY_VOLUME                          0xD403
#define MTP_DEVICE_PROPERTY_SUPPORTED_FORMATS_ORDERED       0xD404
#define MTP_DEVICE_PROPERTY_DEVICE_ICON                     0xD405
#define MTP_DEVICE_PROPERTY_PLAYBACK_RATE                   0xD410
#define MTP_DEVICE_PROPERTY_PLAYBACK_OBJECT                 0xD411
#define MTP_DEVICE_PROPERTY_PLAYBACK_CONTAINER_INDEX        0xD412
#define MTP_DEVICE_PROPERTY_SESSION_INITIATOR_VERSION_INFO  0xD406
#define MTP_DEVICE_PROPERTY_PERCEIVED_DEVICE_TYPE           0xD407

// MTP Operation Codes
#define MTP_OPERATION_GET_DEVICE_INFO                       0x1001
#define MTP_OPERATION_OPEN_SESSION                          0x1002
#define MTP_OPERATION_CLOSE_SESSION                         0x1003
#define MTP_OPERATION_GET_STORAGE_IDS                       0x1004
#define MTP_OPERATION_GET_STORAGE_INFO                      0x1005
#define MTP_OPERATION_GET_NUM_OBJECTS                       0x1006
#define MTP_OPERATION_GET_OBJECT_HANDLES                    0x1007
#define MTP_OPERATION_GET_OBJECT_INFO                       0x1008
#define MTP_OPERATION_GET_OBJECT                            0x1009
#define MTP_OPERATION_GET_THUMB                             0x100A
#define MTP_OPERATION_DELETE_OBJECT                         0x100B
#define MTP_OPERATION_SEND_OBJECT_INFO                      0x100C
#define MTP_OPERATION_SEND_OBJECT                           0x100D
#define MTP_OPERATION_INITIATE_CAPTURE                      0x100E
#define MTP_OPERATION_FORMAT_STORE                          0x100F
#define MTP_OPERATION_RESET_DEVICE                          0x1010
#define MTP_OPERATION_SELF_TEST                             0x1011
#define MTP_OPERATION_SET_OBJECT_PROTECTION                 0x1012
#define MTP_OPERATION_POWER_DOWN                            0x1013
#define MTP_OPERATION_GET_DEVICE_PROP_DESC                  0x1014
#define MTP_OPERATION_GET_DEVICE_PROP_VALUE                 0x1015
#define MTP_OPERATION_SET_DEVICE_PROP_VALUE                 0x1016
#define MTP_OPERATION_RESET_DEVICE_PROP_VALUE               0x1017
#define MTP_OPERATION_TERMINATE_OPEN_CAPTURE                0x1018
#define MTP_OPERATION_MOVE_OBJECT                           0x1019
#define MTP_OPERATION_COPY_OBJECT                           0x101A
#define MTP_OPERATION_GET_PARTIAL_OBJECT                    0x101B
#define MTP_OPERATION_INITIATE_OPEN_CAPTURE                 0x101C
#define MTP_OPERATION_GET_OBJECT_PROPS_SUPPORTED            0x9801
#define MTP_OPERATION_GET_OBJECT_PROP_DESC                  0x9802
#define MTP_OPERATION_GET_OBJECT_PROP_VALUE                 0x9803
#define MTP_OPERATION_SET_OBJECT_PROP_VALUE                 0x9804
#define MTP_OPERATION_GET_OBJECT_PROP_LIST                  0x9805
#define MTP_OPERATION_SET_OBJECT_PROP_LIST                  0x9806
#define MTP_OPERATION_GET_INTERDEPENDENT_PROP_DESC          0x9807
#define MTP_OPERATION_SEND_OBJECT_PROP_LIST                 0x9808
#define MTP_OPERATION_GET_OBJECT_REFERENCES                 0x9810
#define MTP_OPERATION_SET_OBJECT_REFERENCES                 0x9811
#define MTP_OPERATION_SKIP                                  0x9820

// Android extensions for direct file IO

// Same as GetPartialObject, but with 64 bit offset
#define MTP_OPERATION_GET_PARTIAL_OBJECT_64                 0x95C1
// Same as GetPartialObject64, but copying host to device
#define MTP_OPERATION_SEND_PARTIAL_OBJECT                   0x95C2
// Truncates file to 64 bit length
#define MTP_OPERATION_TRUNCATE_OBJECT                       0x95C3
// Must be called before using SendPartialObject and TruncateObject
#define MTP_OPERATION_BEGIN_EDIT_OBJECT                     0x95C4
// Called to commit changes made by SendPartialObject and TruncateObject
#define MTP_OPERATION_END_EDIT_OBJECT                       0x95C5

// MTP Response Codes
#define MTP_RESPONSE_UNDEFINED                                  0x2000
#define MTP_RESPONSE_OK                                         0x2001
#define MTP_RESPONSE_GENERAL_ERROR                              0x2002
#define MTP_RESPONSE_SESSION_NOT_OPEN                           0x2003
#define MTP_RESPONSE_INVALID_TRANSACTION_ID                     0x2004
#define MTP_RESPONSE_OPERATION_NOT_SUPPORTED                    0x2005
#define MTP_RESPONSE_PARAMETER_NOT_SUPPORTED                    0x2006
#define MTP_RESPONSE_INCOMPLETE_TRANSFER                        0x2007
#define MTP_RESPONSE_INVALID_STORAGE_ID                         0x2008
#define MTP_RESPONSE_INVALID_OBJECT_HANDLE                      0x2009
#define MTP_RESPONSE_DEVICE_PROP_NOT_SUPPORTED                  0x200A
#define MTP_RESPONSE_INVALID_OBJECT_FORMAT_CODE                 0x200B
#define MTP_RESPONSE_STORAGE_FULL                               0x200C
#define MTP_RESPONSE_OBJECT_WRITE_PROTECTED                     0x200D
#define MTP_RESPONSE_STORE_READ_ONLY                            0x200E
#define MTP_RESPONSE_ACCESS_DENIED                              0x200F
#define MTP_RESPONSE_NO_THUMBNAIL_PRESENT                       0x2010
#define MTP_RESPONSE_SELF_TEST_FAILED                           0x2011
#define MTP_RESPONSE_PARTIAL_DELETION                           0x2012
#define MTP_RESPONSE_STORE_NOT_AVAILABLE                        0x2013
#define MTP_RESPONSE_SPECIFICATION_BY_FORMAT_UNSUPPORTED        0x2014
#define MTP_RESPONSE_NO_VALID_OBJECT_INFO                       0x2015
#define MTP_RESPONSE_INVALID_CODE_FORMAT                        0x2016
#define MTP_RESPONSE_UNKNOWN_VENDOR_CODE                        0x2017
#define MTP_RESPONSE_CAPTURE_ALREADY_TERMINATED                 0x2018
#define MTP_RESPONSE_DEVICE_BUSY                                0x2019
#define MTP_RESPONSE_INVALID_PARENT_OBJECT                      0x201A
#define MTP_RESPONSE_INVALID_DEVICE_PROP_FORMAT                 0x201B
#define MTP_RESPONSE_INVALID_DEVICE_PROP_VALUE                  0x201C
#define MTP_RESPONSE_INVALID_PARAMETER                          0x201D
#define MTP_RESPONSE_SESSION_ALREADY_OPEN                       0x201E
#define MTP_RESPONSE_TRANSACTION_CANCELLED                      0x201F
#define MTP_RESPONSE_SPECIFICATION_OF_DESTINATION_UNSUPPORTED   0x2020
#define MTP_RESPONSE_INVALID_OBJECT_PROP_CODE                   0xA801
#define MTP_RESPONSE_INVALID_OBJECT_PROP_FORMAT                 0xA802
#define MTP_RESPONSE_INVALID_OBJECT_PROP_VALUE                  0xA803
#define MTP_RESPONSE_INVALID_OBJECT_REFERENCE                   0xA804
#define MTP_RESPONSE_GROUP_NOT_SUPPORTED                        0xA805
#define MTP_RESPONSE_INVALID_DATASET                            0xA806
#define MTP_RESPONSE_SPECIFICATION_BY_GROUP_UNSUPPORTED         0xA807
#define MTP_RESPONSE_SPECIFICATION_BY_DEPTH_UNSUPPORTED         0xA808
#define MTP_RESPONSE_OBJECT_TOO_LARGE                           0xA809
#define MTP_RESPONSE_OBJECT_PROP_NOT_SUPPORTED                  0xA80A
#define MTP_RESPONSE_NO_RESPONSE                                0xFFFF

// MTP Event Codes
#define MTP_EVENT_UNDEFINED                         0x4000
#define MTP_EVENT_CANCEL_TRANSACTION                0x4001
#define MTP_EVENT_OBJECT_ADDED                      0x4002
#define MTP_EVENT_OBJECT_REMOVED                    0x4003
#define MTP_EVENT_STORE_ADDED                       0x4004
#define MTP_EVENT_STORE_REMOVED                     0x4005
#define MTP_EVENT_DEVICE_PROP_CHANGED               0x4006
#define MTP_EVENT_OBJECT_INFO_CHANGED               0x4007
#define MTP_EVENT_DEVICE_INFO_CHANGED               0x4008
#define MTP_EVENT_REQUEST_OBJECT_TRANSFER           0x4009
#define MTP_EVENT_STORE_FULL                        0x400A
#define MTP_EVENT_DEVICE_RESET                      0x400B
#define MTP_EVENT_STORAGE_INFO_CHANGED              0x400C
#define MTP_EVENT_CAPTURE_COMPLETE                  0x400D
#define MTP_EVENT_UNREPORTED_STATUS                 0x400E
#define MTP_EVENT_OBJECT_PROP_CHANGED               0xC801
#define MTP_EVENT_OBJECT_PROP_DESC_CHANGED          0xC802
#define MTP_EVENT_OBJECT_REFERENCES_CHANGED         0xC803

// Storage Type
#define MTP_STORAGE_FIXED_ROM                       0x0001
#define MTP_STORAGE_REMOVABLE_ROM                   0x0002
#define MTP_STORAGE_FIXED_RAM                       0x0003
#define MTP_STORAGE_REMOVABLE_RAM                   0x0004

// Storage File System
#define MTP_STORAGE_FILESYSTEM_FLAT                 0x0001
#define MTP_STORAGE_FILESYSTEM_HIERARCHICAL         0x0002
#define MTP_STORAGE_FILESYSTEM_DCF                  0x0003

// Storage Access Capability
#define MTP_STORAGE_READ_WRITE                      0x0000
#define MTP_STORAGE_READ_ONLY_WITHOUT_DELETE        0x0001
#define MTP_STORAGE_READ_ONLY_WITH_DELETE           0x0002

// Association Type
#define MTP_ASSOCIATION_TYPE_UNDEFINED              0x0000
#define MTP_ASSOCIATION_TYPE_GENERIC_FOLDER         0x0001

// MTP class reqeusts
#define MTP_REQUEST_CANCEL              0x64
#define MTP_REQUEST_GET_EXT_EVENT_DATA  0x65
#define MTP_REQUEST_RESET               0x66
#define MTP_REQUEST_GET_DEVICE_STATUS   0x67
// clang-format on

#define USB_MTP_CLASS 0x06

#define USB_MTP_SUB_CLASS 0x01U
#define USB_MTP_PROTOCOL  0x01U

struct mtp_header {
    uint32_t conlen;
    uint16_t contype;
    uint16_t code;
    uint32_t trans_id;
    uint32_t param[];
};

struct mtp_string {
    uint8_t len;
    uint16_t string[255];
};

struct mtp_device_info {
    uint16_t StandardVersion;
    uint32_t VendorExtensionID;
    uint16_t VendorExtensionVersion;
    uint8_t VendorExtensionDesc_len;
    uint16_t VendorExtensionDesc[255];
    uint16_t FunctionalMode;
    uint32_t OperationsSupported_len;
    uint16_t OperationsSupported[255];
    uint32_t EventsSupported_len;
    uint16_t EventsSupported[255];
    uint32_t DevicePropertiesSupported_len;
    uint16_t DevicePropertiesSupported[255];
    uint32_t CaptureFormats_len;
    uint16_t CaptureFormats[255];
    uint32_t ImageFormats_len;
    uint16_t ImageFormats[255];
    uint8_t Manufacturer_len;
    uint16_t Manufacturer[255];
    uint8_t Model_len;
    uint16_t Model[255];
    uint8_t DeviceVersion_len;
    uint16_t DeviceVersion[255];
    uint8_t SerialNumber_len;
    uint16_t SerialNumber[255];
} __PACKED;

struct mtp_object_props_support {
    uint32_t ObjectPropCode_len;
    uint16_t ObjectPropCode[255];
} __PACKED;

struct mtp_device_prop_desc {
    uint16_t DevicePropertyCode;
    uint16_t DataType;
    uint8_t GetSet;
    uint16_t DefaultValue[1];
    uint16_t CurrentValue[1];
    uint8_t FormFlag;
} __PACKED;

struct mtp_storage_id {
    uint32_t StorageIDS_len;
    uint32_t StorageIDS[255];
} __PACKED;

struct mtp_storage_info {
    uint16_t StorageType;
    uint16_t FilesystemType;
    uint16_t AccessCapability;
    uint64_t MaxCapability;
    uint64_t FreeSpaceInBytes;
    uint32_t FreeSpaceInObjects;
    uint8_t StorageDescription_len;
    uint8_t StorageDescription[255];
    uint8_t VolumeIdentifier_len;
    uint8_t VolumeIdentifier[255];
} __PACKED;

struct mtp_object_handles {
    uint32_t ObjectHandle_len;
    uint32_t ObjectHandle[255];
} __PACKED;

struct mtp_object_prop_desc {
    uint16_t ObjectPropertyCode;
    uint16_t DataType;
    uint8_t GetSet;
    uint8_t DefValue[16];
    uint32_t GroupCode;
    uint8_t FormFlag;
} __PACKED;

struct mtp_object_prop_element {
    uint32_t ObjectHandle;
    uint16_t PropertyCode;
    uint16_t Datatype;
    uint8_t value[8];
} __PACKED;

struct mtp_object_prop_list {
    uint32_t element_len;
    struct mtp_object_prop_element element[1];
} __PACKED;

struct mtp_object_info {
    uint32_t StorageId;
    uint16_t ObjectFormat;
    uint16_t ProtectionStatus;
    uint32_t ObjectCompressedSize;
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
    uint8_t Filename_len;
    uint16_t Filename[CONFIG_USBDEV_MTP_MAX_PATHNAME];
    uint8_t CaptureDate[6];
    uint8_t ModificationDate[6];
} __PACKED;

struct mtp_object {
    uint32_t storage_id;
    uint32_t handle;
    uint32_t parent_handle;
    uint16_t format;
    bool is_dir;
    bool is_readonly;
    bool is_hidden;
    uint32_t file_size;
    uint32_t file_full_name_length;
    char file_full_name[CONFIG_USBDEV_MTP_MAX_PATHNAME];
    bool in_use;
};

/*Length of template descriptor: 23 bytes*/
#define MTP_DESCRIPTOR_LEN (9 + 7 + 7 + 7)

// clang-format off
#define MTP_DESCRIPTOR_INIT(bFirstInterface, out_ep, in_ep, int_ep, wMaxPacketSize, str_idx) \
    /* Interface */                                                      \
    0x09,                          /* bLength */                         \
    USB_DESCRIPTOR_TYPE_INTERFACE, /* bDescriptorType */                 \
    bFirstInterface,               /* bInterfaceNumber */                \
    0x00,                          /* bAlternateSetting */               \
    0x03,                          /* bNumEndpoints */                   \
    USB_DEVICE_CLASS_IMAGE,        /* bInterfaceClass */                 \
    USB_MTP_SUB_CLASS,             /* bInterfaceSubClass */              \
    USB_MTP_PROTOCOL,              /* bInterfaceProtocol */              \
    str_idx,                       /* iInterface */                      \
    0x07,                          /* bLength */                         \
    USB_DESCRIPTOR_TYPE_ENDPOINT,  /* bDescriptorType */                 \
    out_ep,                        /* bEndpointAddress */                \
    0x02,                          /* bmAttributes */                    \
    WBVAL(wMaxPacketSize),         /* wMaxPacketSize */                  \
    0x00,                          /* bInterval */                       \
    0x07,                          /* bLength */                         \
    USB_DESCRIPTOR_TYPE_ENDPOINT,  /* bDescriptorType */                 \
    in_ep,                         /* bEndpointAddress */                \
    0x02,                          /* bmAttributes */                    \
    WBVAL(wMaxPacketSize),         /* wMaxPacketSize */                  \
    0x00,                          /* bInterval */                       \
    0x07,                          /* bLength */                         \
    USB_DESCRIPTOR_TYPE_ENDPOINT,  /* bDescriptorType */                 \
    int_ep,                        /* bEndpointAddress */                \
    0x03,                          /* bmAttributes */                    \
    0x1c,                          /* wMaxPacketSize */                  \
    0x00,                          /* bInterval */                       \
    0x06                           /* bLength */
// clang-format on

#endif