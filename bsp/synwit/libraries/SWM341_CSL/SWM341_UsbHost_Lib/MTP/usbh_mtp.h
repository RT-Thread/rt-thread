#ifndef __USBH_MTP_H__
#define __USBH_MTP_H__

#include "usbh_mtp_ptp.h"


typedef enum {
    USBH_MTP_IDLE = 0,
    USBH_MTP_GETDEVICEINFO,
    USBH_MTP_OPENSESSION,
    USBH_MTP_GETSTORAGEIDS,
    USBH_MTP_GETSTORAGEINFO,
    USBH_MTP_TRANSFER,
    USBH_MTP_EVENT,
    USBH_MTP_EVENT_WAIT,

    /* Events may be interleaved within a data stream during a transaction.
       It may be assumed that the Operation Request Phase and Response Phase are atomic, but the Data Phase
       must allow for events to be communicated in either direction without interrupting data transfer.
    */
    USBH_MTP_EVENT_CHECK,
} USBH_MTP_State;

typedef enum {
    USBH_MTP_OP_IDLE = 0,
    USBH_MTP_OP_SEND,
    USBH_MTP_OP_WAIT,
    USBH_MTP_OP_ERROR,
} USBH_MTP_OpState;

typedef enum {
    USBH_MTP_XFER_IDLE = 0,
    USBH_MTP_XFER_OP_REQ,
    USBH_MTP_XFER_OP_REQ_WAIT,
    USBH_MTP_XFER_DATA_OUT,
    USBH_MTP_XFER_DATA_OUT_WAIT,
    USBH_MTP_XFER_DATA_IN,
    USBH_MTP_XFER_DATA_IN_WAIT,
    USBH_MTP_XFER_RESP,
    USBH_MTP_XFER_RESP_WAIT,
    USBH_MTP_XFER_ERROR,
} USBH_MTP_XferState;


typedef struct {
    uint32_t timer;
    uint16_t poll;
    PTP_EventContainer_t container;
} MTP_EventHandle_t;


typedef struct {
    uint8_t  InEp;
    uint8_t  OutEp;
    uint8_t  NotifyEp;
    uint16_t InEpSize;
    uint16_t OutEpSize;
    uint16_t NotifyEpSize;
    uint8_t  InEpDATAX;
    uint8_t  OutEpDATAX;
    uint8_t  NotifyEpDATAX;

    USBH_MTP_State      state;
    USBH_MTP_State      stateReq;
    USBH_MTP_State      stateBkp;

    USBH_MTP_OpState    OpState;
    USBH_MTP_XferState  XferState;

    USBH_Status         XferStatus;

    PTP_OpContainer_t   op_container;
    PTP_DataContainer_t data_container;
    PTP_RespContainer_t resp_container;

    uint32_t  session_id;
    uint32_t  transaction_id;

    uint32_t  flags;

    uint8_t  *data_ptr;
    uint32_t  data_len;
    uint8_t   first_packet;     // 1 数据第一帧   3 数据第一帧，且需丢弃 header 不存储

    PTP_DeviceInfo_t    devinfo;
    PTP_StorageIDs_t    storids;
    PTP_StorageInfo_t   storinfo[PTP_MAX_STORAGE_UNITS_NBR];

    MTP_EventHandle_t   events;

    uint32_t CurrentStorage;
    uint32_t is_ready;
} USBH_MTP_Info_t;

extern USBH_MTP_Info_t USBH_MTP_Info;


static uint32_t USBH_MTP_Ready(void)
{
    return USBH_MTP_Info.is_ready;
}

static uint32_t USBH_MTP_StorageCount(void)
{
    return USBH_MTP_Info.storids.n;
}

static uint32_t USBH_MTP_Storage(uint32_t index)
{
    return USBH_MTP_Info.storids.Storage[index];
}


USBH_Status USBH_MTP_GetDeviceInfo(USBH_Info_t *phost, PTP_DeviceInfo_t *dev_info);

USBH_Status USBH_MTP_OpenSession(USBH_Info_t *phost, uint32_t session);

USBH_Status USBH_MTP_GetStorageIds(USBH_Info_t *phost, PTP_StorageIDs_t *storage_ids);
USBH_Status USBH_MTP_GetStorageInfo(USBH_Info_t *phost, uint32_t storage_id, PTP_StorageInfo_t *storage_info);

USBH_Status USBH_MTP_GetNumObjects(USBH_Info_t *phost, uint32_t storage_id, uint32_t format, uint32_t folder, uint32_t *numobs);
USBH_Status USBH_MTP_GetObjectHandles(USBH_Info_t *phost, uint32_t storage_id, uint32_t format, uint32_t folder, PTP_ObjectHandles_t *handles);

USBH_Status USBH_MTP_GetObjectInfo(USBH_Info_t *phost, uint32_t handle, PTP_ObjectInfo_t *object_info);

USBH_Status USBH_MTP_GetObject(USBH_Info_t *phost, uint32_t handle, uint8_t *object);
USBH_Status USBH_MTP_GetPartialObject(USBH_Info_t *phost, uint32_t handle, uint32_t offset, uint32_t maxbytes, uint8_t *object, uint32_t *len);

USBH_Status USBH_MTP_DeleteObject(USBH_Info_t *phost, uint32_t handle, uint32_t format);
USBH_Status USBH_MTP_SendObject(USBH_Info_t *phost, uint32_t handle, uint8_t *object, uint32_t size);

USBH_Status USBH_MTP_GetDevicePropDesc(USBH_Info_t *phost, uint16_t propcode, PTP_DevicePropDesc_t *devicepropertydesc);

USBH_Status USBH_MTP_GetObjectPropsSupported(USBH_Info_t *phost, uint16_t ofc, uint32_t *propnum, uint16_t *props);
USBH_Status USBH_MTP_GetObjectPropDesc(USBH_Info_t *phost, uint16_t opc, uint16_t ofc, PTP_ObjectPropDesc_t *opd);
USBH_Status USBH_MTP_GetObjectPropList(USBH_Info_t *phost, uint32_t handle, MTP_Properties_t *pprops, uint32_t *nrofprops);


void USBH_MTP_EventsCallback(USBH_Info_t *phost, uint32_t event, uint32_t param);


#define USBH_TObreak(ms)                            \
    {                                               \
        static int start;                           \
        start = USBH->FRAMENR;                      \
        if(abs((int)USBH->FRAMENR - start) > ms)    \
        {                                           \
            break;                                  \
        }                                           \
    }


#endif // __USBH_MTP_H__
