/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __VIRTIO_SCSI_H__
#define __VIRTIO_SCSI_H__

#include <drivers/core/dm.h>

#define VIRTIO_SCSI_CDB_DEFAULT_SIZE   32
#define VIRTIO_SCSI_SENSE_DEFAULT_SIZE 96

#ifndef VIRTIO_SCSI_CDB_SIZE
#define VIRTIO_SCSI_CDB_SIZE VIRTIO_SCSI_CDB_DEFAULT_SIZE
#endif
#ifndef VIRTIO_SCSI_SENSE_SIZE
#define VIRTIO_SCSI_SENSE_SIZE VIRTIO_SCSI_SENSE_DEFAULT_SIZE
#endif

/* SCSI command request, followed by data-out */
rt_packed(struct virtio_scsi_cmd_req
{
    rt_uint8_t lun[8];      /* Logical Unit Number */
    rt_le64_t tag;          /* Command identifier */
    rt_uint8_t task_attr;   /* Task attribute */
    rt_uint8_t prio;        /* SAM command priority field */
    rt_uint8_t crn;
    rt_uint8_t cdb[VIRTIO_SCSI_CDB_SIZE];
});

/* SCSI command request, followed by protection information */
rt_packed(struct virtio_scsi_cmd_req_pi
{
    rt_uint8_t lun[8];      /* Logical Unit Number */
    rt_le64_t tag;          /* Command identifier */
    rt_uint8_t task_attr;   /* Task attribute */
    rt_uint8_t prio;        /* SAM command priority field */
    rt_uint8_t crn;
    rt_le32_t pi_bytesout;  /* DataOUT PI Number of bytes */
    rt_le32_t pi_bytesin;   /* DataIN PI Number of bytes */
    rt_uint8_t cdb[VIRTIO_SCSI_CDB_SIZE];
});

/* Response, followed by sense data and data-in */
rt_packed(struct virtio_scsi_cmd_resp
{
    rt_le32_t sense_len;        /* Sense data length */
    rt_le32_t resid;            /* Residual bytes in data buffer */
    rt_le16_t status_qualifier; /* Status qualifier */
    rt_uint8_t status;          /* Command completion status */
    rt_uint8_t response;        /* Response values */
    rt_uint8_t sense[VIRTIO_SCSI_SENSE_SIZE];
});

/* Task Management Request */
rt_packed(struct virtio_scsi_ctrl_tmf_req
{
    rt_le32_t type;
    rt_le32_t subtype;
    rt_uint8_t lun[8];
    rt_le64_t tag;
});

rt_packed(struct virtio_scsi_ctrl_tmf_resp
{
    rt_uint8_t response;
});

/* Asynchronous notification query/subscription */
rt_packed(struct virtio_scsi_ctrl_an_req
{
    rt_le32_t type;
    rt_uint8_t lun[8];
    rt_le32_t event_requested;
});

rt_packed(struct virtio_scsi_ctrl_an_resp
{
    rt_le32_t event_actual;
    rt_uint8_t response;
});

rt_packed(struct virtio_scsi_event
{
    rt_le32_t event;
    rt_uint8_t lun[8];
    rt_le32_t reason;
});

rt_packed(struct virtio_scsi_config
{
    rt_le32_t num_queues;
    rt_le32_t seg_max;
    rt_le32_t max_sectors;
    rt_le32_t cmd_per_lun;
    rt_le32_t event_info_size;
    rt_le32_t sense_size;
    rt_le32_t cdb_size;
    rt_le16_t max_channel;
    rt_le16_t max_target;
    rt_le32_t max_lun;
});

/* Feature Bits */
#define VIRTIO_SCSI_F_INOUT                    0
#define VIRTIO_SCSI_F_HOTPLUG                  1
#define VIRTIO_SCSI_F_CHANGE                   2
#define VIRTIO_SCSI_F_T10_PI                   3

/* Response codes */
#define VIRTIO_SCSI_S_OK                       0
#define VIRTIO_SCSI_S_OVERRUN                  1
#define VIRTIO_SCSI_S_ABORTED                  2
#define VIRTIO_SCSI_S_BAD_TARGET               3
#define VIRTIO_SCSI_S_RESET                    4
#define VIRTIO_SCSI_S_BUSY                     5
#define VIRTIO_SCSI_S_TRANSPORT_FAILURE        6
#define VIRTIO_SCSI_S_TARGET_FAILURE           7
#define VIRTIO_SCSI_S_NEXUS_FAILURE            8
#define VIRTIO_SCSI_S_FAILURE                  9
#define VIRTIO_SCSI_S_FUNCTION_SUCCEEDED       10
#define VIRTIO_SCSI_S_FUNCTION_REJECTED        11
#define VIRTIO_SCSI_S_INCORRECT_LUN            12

/* Controlq type codes */
#define VIRTIO_SCSI_T_TMF                      0
#define VIRTIO_SCSI_T_AN_QUERY                 1
#define VIRTIO_SCSI_T_AN_SUBSCRIBE             2

/* Valid TMF subtypes */
#define VIRTIO_SCSI_T_TMF_ABORT_TASK           0
#define VIRTIO_SCSI_T_TMF_ABORT_TASK_SET       1
#define VIRTIO_SCSI_T_TMF_CLEAR_ACA            2
#define VIRTIO_SCSI_T_TMF_CLEAR_TASK_SET       3
#define VIRTIO_SCSI_T_TMF_I_T_NEXUS_RESET      4
#define VIRTIO_SCSI_T_TMF_LOGICAL_UNIT_RESET   5
#define VIRTIO_SCSI_T_TMF_QUERY_TASK           6
#define VIRTIO_SCSI_T_TMF_QUERY_TASK_SET       7

/* Events */
#define VIRTIO_SCSI_T_EVENTS_MISSED            0x80000000
#define VIRTIO_SCSI_T_NO_EVENT                 0
#define VIRTIO_SCSI_T_TRANSPORT_RESET          1
#define VIRTIO_SCSI_T_ASYNC_NOTIFY             2
#define VIRTIO_SCSI_T_PARAM_CHANGE             3

/* Reasons of transport reset event */
#define VIRTIO_SCSI_EVT_RESET_HARD             0
#define VIRTIO_SCSI_EVT_RESET_RESCAN           1
#define VIRTIO_SCSI_EVT_RESET_REMOVED          2

#define VIRTIO_SCSI_S_SIMPLE                   0
#define VIRTIO_SCSI_S_ORDERED                  1
#define VIRTIO_SCSI_S_HEAD                     2
#define VIRTIO_SCSI_S_ACA                      3

#endif /* __VIRTIO_SCSI_H__ */
