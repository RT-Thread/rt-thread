/******************************************************************************************************************************************
* 文件名称: usbh_mtp.c
* 功能说明: This file includes the PTP operations layer.
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.1.0      2020年11月3日
* 升级记录:
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology
*******************************************************************************************************************************************/
#include <string.h>
#include "SWM341.h"
#include "usbh_core.h"
#include "usbh_mtp.h"


/******************************************************************************************************************************************
* 函数名称: PTP_GetDevicePropValue()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PTP_GetDevicePropValue(USBH_Info_t *phost, uint32_t *offset, uint32_t total, PTP_PropertyValue_t *value, uint16_t datatype)
{
    uint8_t *data = USBH_MTP_Info.data_container.payload;
    uint16_t len;
    switch(datatype)
    {
    case PTP_DTC_INT8:
        value->i8 = *(int8_t *)(void *) & (data[*offset]);
        *offset += 1U;
        break;

    case PTP_DTC_UINT8:
        value->u8 = *(uint8_t *) & (data[*offset]);
        *offset += 1U;
        break;

    case PTP_DTC_INT16:
        value->i16 = *(int16_t *)(void *) & (data[*offset]);
        *offset += 2U;
        break;

    case PTP_DTC_UINT16:
        value->u16 = PTP_LE16(&(data[*offset]));
        *offset += 2U;
        break;

    case PTP_DTC_INT32:
        value->i32 = *(int32_t *)(void *)(&(data[*offset]));
        *offset += 4U;
        break;

    case PTP_DTC_UINT32:
        value->u32 = PTP_LE32(&(data[*offset]));
        *offset += 4U;
        break;

    case PTP_DTC_INT64:
        value->i64 = *(int64_t *)(void *)(&(data[*offset]));
        *offset += 8U;
        break;

    case PTP_DTC_UINT64:
        value->u64 = PTP_LE64(&(data[*offset]));
        *offset += 8U;
        break;

    case PTP_DTC_UINT128:
        *offset += 16U;
        break;

    case PTP_DTC_INT128:
        *offset += 16U;
        break;

    case PTP_DTC_STR:
        PTP_GetString((uint8_t *)(void *)value->str, (uint8_t *) & (data[*offset]), &len);
        *offset += (uint32_t)(len * 2U) + 1U;
        break;

    default:
        break;
    }
}


/******************************************************************************************************************************************
* 函数名称: PTP_GetString()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PTP_GetString(uint8_t *str, uint8_t *data, uint16_t *len)
{
    uint16_t strlength;
    uint16_t idx;

    *len = data[0];
    strlength = (uint16_t)(2U * (uint32_t)data[0]);
    data ++; /* Adjust the offset ignoring the String Len */

    for (idx = 0U; idx < strlength; idx += 2U)
    {
        /* Copy Only the string and ignore the UNICODE ID, hence add the src */
        *str = data[idx];
        str++;
    }
    *str = 0U; /* mark end of string */
}


/******************************************************************************************************************************************
* 函数名称: PTP_GetArray16()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t PTP_GetArray16(uint16_t *array, uint8_t *data, uint32_t offset)
{
    uint32_t size, idx = 0U;

    size = PTP_LE32(&data[offset]);
    while(size > idx)
    {
        array[idx] = (uint16_t)data[offset + (sizeof(uint16_t) * (idx + 2U))];
        idx++;
    }
    return size;
}


/******************************************************************************************************************************************
* 函数名称: PTP_GetArray32()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t PTP_GetArray32(uint32_t *array, uint8_t *data, uint32_t offset)
{
    uint32_t size, idx = 0U;

    size = PTP_LE32(&data[offset]);
    while(size > idx)
    {
        array[idx] = PTP_LE32(&data[offset + (sizeof(uint32_t) * (idx + 1U))]);
        idx++;
    }
    return size;
}


/******************************************************************************************************************************************
* 函数名称: PTP_DecodeDeviceInfo()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PTP_DecodeDeviceInfo(USBH_Info_t *phost, PTP_DeviceInfo_t *dev_info)
{
    uint8_t *data = USBH_MTP_Info.data_container.payload;
    uint32_t totallen;
    uint16_t len;

    dev_info->StandardVersion = PTP_LE16(&data[PTP_di_StandardVersion]);
    dev_info->VendorExtensionID = PTP_LE32(&data[PTP_di_VendorExtensionID]);
    dev_info->VendorExtensionVersion = PTP_LE16(&data[PTP_di_VendorExtensionVersion]);
    PTP_GetString(dev_info->VendorExtensionDesc, &data[PTP_di_VendorExtensionDesc], &len);

    totallen = (uint32_t)(len * 2U) + 1U;
    dev_info->FunctionalMode = PTP_LE16(&data[PTP_di_FunctionalMode + totallen]);
    dev_info->OperationsSupportedNbr = PTP_GetArray16((uint16_t *)(void *)&dev_info->OperationsSupported, data, PTP_di_OperationsSupported + totallen);

    totallen = totallen + (dev_info->OperationsSupportedNbr * sizeof(uint16_t)) + sizeof(uint32_t);
    dev_info->EventsSupportedNbr = PTP_GetArray16((uint16_t *)(void *)&dev_info->EventsSupported, data, PTP_di_OperationsSupported + totallen);

    totallen = totallen + (dev_info->EventsSupportedNbr * sizeof(uint16_t)) + sizeof(uint32_t);
    dev_info->DevicePropertiesSupportedNbr = PTP_GetArray16((uint16_t *)(void *)&dev_info->DevicePropertiesSupported, data, PTP_di_OperationsSupported + totallen);

    totallen = totallen + (dev_info->DevicePropertiesSupportedNbr * sizeof(uint16_t)) + sizeof(uint32_t);

    dev_info->CaptureFormatsNbr = PTP_GetArray16((uint16_t *)(void *)&dev_info->CaptureFormats, data, PTP_di_OperationsSupported + totallen);

    totallen = totallen + (dev_info->CaptureFormatsNbr * sizeof(uint16_t)) + sizeof(uint32_t);
    dev_info->ImageFormatsNbr =  PTP_GetArray16((uint16_t *)(void *)&dev_info->ImageFormats, data, PTP_di_OperationsSupported + totallen);

    totallen = totallen + (dev_info->ImageFormatsNbr * sizeof(uint16_t)) + sizeof(uint32_t);
    PTP_GetString(dev_info->Manufacturer, &data[PTP_di_OperationsSupported + totallen], &len);

    totallen += (uint32_t)(len * 2U) + 1U;
    PTP_GetString(dev_info->Model, &data[PTP_di_OperationsSupported + totallen], &len);

    totallen += (uint32_t)(len * 2U) + 1U;
    PTP_GetString(dev_info->DeviceVersion, &data[PTP_di_OperationsSupported + totallen], &len);

    totallen += (uint32_t)(len * 2U) + 1U;
    PTP_GetString(dev_info->SerialNumber, &data[PTP_di_OperationsSupported + totallen], &len);
}


/******************************************************************************************************************************************
* 函数名称: PTP_DecodeStorageInfo()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PTP_DecodeStorageInfo(USBH_Info_t *phost, PTP_StorageInfo_t *storage_info)
{
    uint8_t *data = USBH_MTP_Info.data_container.payload;
    uint16_t len;

    storage_info->StorageType = PTP_LE16(&data[PTP_si_StorageType]);
    storage_info->FilesystemType = PTP_LE16(&data[PTP_si_FilesystemType]);
    storage_info->AccessCapability = PTP_LE16(&data[PTP_si_AccessCapability]);
    storage_info->MaxCapability = PTP_LE64(&data[PTP_si_MaxCapability]);
    storage_info->FreeSpaceInBytes = PTP_LE64(&data[PTP_si_FreeSpaceInBytes]);
    storage_info->FreeSpaceInImages = PTP_LE32(&data[PTP_si_FreeSpaceInImages]);

    PTP_GetString(storage_info->StorageDescription, &data[PTP_si_StorageDescription], &len);
    PTP_GetString(storage_info->VolumeLabel, &data[PTP_si_StorageDescription + (len * 2U) + 1U], &len);
}


/******************************************************************************************************************************************
* 函数名称: PTP_DecodeObjectInfo()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PTP_DecodeObjectInfo(USBH_Info_t *phost, PTP_ObjectInfo_t *object_info)
{
    uint8_t *data = USBH_MTP_Info.data_container.payload;
    uint16_t filenamelen;

    object_info->StorageID = PTP_LE32(&data[PTP_oi_StorageID]);
    object_info->ObjectFormat = PTP_LE16(&data[PTP_oi_ObjectFormat]);
    object_info->ProtectionStatus = PTP_LE16(&data[PTP_oi_ProtectionStatus]);
    object_info->ObjectCompressedSize = PTP_LE64(&data[PTP_oi_ObjectCompressedSize]);

    /* For Samsung Galaxy */
    if((data[PTP_oi_filenamelen] == 0U) && (data[PTP_oi_filenamelen + 4U] != 0U))
    {
        data += 4;
    }
    object_info->ThumbFormat = PTP_LE16(&data[PTP_oi_ThumbFormat]);
    object_info->ThumbCompressedSize = PTP_LE32(&data[PTP_oi_ThumbCompressedSize]);
    object_info->ThumbPixWidth = PTP_LE32(&data[PTP_oi_ThumbPixWidth]);
    object_info->ThumbPixHeight = PTP_LE32(&data[PTP_oi_ThumbPixHeight]);
    object_info->ImagePixWidth = PTP_LE32(&data[PTP_oi_ImagePixWidth]);
    object_info->ImagePixHeight = PTP_LE32(&data[PTP_oi_ImagePixHeight]);
    object_info->ImageBitDepth = PTP_LE32(&data[PTP_oi_ImageBitDepth]);
    object_info->ParentObject = PTP_LE32(&data[PTP_oi_ParentObject]);
    object_info->AssociationType = PTP_LE16(&data[PTP_oi_AssociationType]);
    object_info->AssociationDesc = PTP_LE32(&data[PTP_oi_AssociationDesc]);
    object_info->SequenceNumber = PTP_LE32(&data[PTP_oi_SequenceNumber]);
    PTP_GetString(object_info->Filename, &data[PTP_oi_filenamelen], &filenamelen);
}


/******************************************************************************************************************************************
* 函数名称: PTP_DecodeObjectPropDesc()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PTP_DecodeObjectPropDesc(USBH_Info_t *phost, PTP_ObjectPropDesc_t *opd, uint32_t opdlen)
{
    uint8_t *data = USBH_MTP_Info.data_container.payload;
    uint32_t offset = 0U, i;

    opd->ObjectPropertyCode = PTP_LE16(&data[PTP_opd_ObjectPropertyCode]);
    opd->DataType = PTP_LE16(&data[PTP_opd_DataType]);
    opd->GetSet = *(uint8_t *)(&data[PTP_opd_GetSet]);

    offset = PTP_opd_FactoryDefaultValue;
    PTP_GetDevicePropValue(phost, &offset, opdlen, &opd->FactoryDefaultValue, opd->DataType);

    opd->GroupCode = PTP_LE32(&data[offset]);
    offset += sizeof(uint32_t);

    opd->FormFlag = *(uint8_t *)(&data[offset]);
    offset += sizeof(uint8_t);

    switch(opd->FormFlag)
    {
    case PTP_OPFF_Range:
        PTP_GetDevicePropValue(phost, &offset, opdlen, &opd->FORM.Range.MinimumValue, opd->DataType);
        PTP_GetDevicePropValue(phost, &offset, opdlen, &opd->FORM.Range.MaximumValue, opd->DataType);
        PTP_GetDevicePropValue(phost, &offset, opdlen, &opd->FORM.Range.StepSize, opd->DataType);
        break;

    case PTP_OPFF_Enumeration:
        opd->FORM.Enum.NumberOfValues = PTP_LE16(&data[offset]);
        offset += sizeof(uint16_t);

        for(i = 0U; i < opd->FORM.Enum.NumberOfValues ; i++)
        {
            PTP_GetDevicePropValue(phost, &offset, opdlen, &opd->FORM.Enum.SupportedValue[i], opd->DataType);
        }
        break;

    default:
        break;
    }
}


/******************************************************************************************************************************************
* 函数名称: PTP_DecodeObjectPropList()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t PTP_DecodeObjectPropList(USBH_Info_t *phost, MTP_Properties_t *props, uint32_t len)
{
    uint8_t *data = USBH_MTP_Info.data_container.payload;
    uint32_t prop_count;
    uint32_t offset = 0U, i;

    prop_count = PTP_LE32(data);
    if(prop_count == 0U)
    {
        return 0;
    }

    data += sizeof(uint32_t);
    len -= sizeof(uint32_t);

    for(i = 0U; i < prop_count; i++)
    {
        if(len <= 0U)
        {
            return 0;
        }

        props[i].ObjectHandle = PTP_LE32(data);
        data += sizeof(uint32_t);
        len -= sizeof(uint32_t);

        props[i].property = PTP_LE16(data);
        data += sizeof(uint16_t);
        len -= sizeof(uint16_t);

        props[i].datatype = PTP_LE16(data);
        data += sizeof(uint16_t);
        len -= sizeof(uint16_t);

        offset = 0U;

        PTP_GetDevicePropValue(phost, &offset, len, &props[i].propval, props[i].datatype);

        data += offset;
        len -= offset;
    }

    return prop_count;
}
