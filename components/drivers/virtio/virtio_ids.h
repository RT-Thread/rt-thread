/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __VIRTIO_IDS_H__
#define __VIRTIO_IDS_H__

enum
{
    /* virtio 1.0 */
    VIRTIO_DEVICE_ID_INVALID                = 0,    /* Invalid device */
    VIRTIO_DEVICE_ID_NET                    = 1,    /* Net */
    VIRTIO_DEVICE_ID_BLOCK                  = 2,    /* Block */
    VIRTIO_DEVICE_ID_CONSOLE                = 3,    /* Console */
    VIRTIO_DEVICE_ID_RNG                    = 4,    /* Rng */
    VIRTIO_DEVICE_ID_BALLOON                = 5,    /* Balloon */
    VIRTIO_DEVICE_ID_IOMEM                  = 6,    /* IO memory */
    VIRTIO_DEVICE_ID_RPMSG                  = 7,    /* Remote processor messaging */
    VIRTIO_DEVICE_ID_SCSI                   = 8,    /* SCSI */
    VIRTIO_DEVICE_ID_9P                     = 9,    /* 9p console */
    VIRTIO_DEVICE_ID_MAC80211_WLAN          = 10,   /* Mac80211 wlan */
    VIRTIO_DEVICE_ID_RPROC_SERIAL           = 11,   /* Remoteproc serial link */
    VIRTIO_DEVICE_ID_CAIF                   = 12,   /* CAIF */
    VIRTIO_DEVICE_ID_MEM_BALLOON            = 13,   /* Memory balloon */
    VIRTIO_DEVICE_ID_GPU                    = 16,   /* GPU */
    VIRTIO_DEVICE_ID_TIME                   = 17,   /* Timer/clock device */
    VIRTIO_DEVICE_ID_INPUT                  = 18,   /* Input */
    /* virtio 1.1 */
    VIRTIO_DEVICE_ID_SOCKET                 = 19,   /* Socket device */
    VIRTIO_DEVICE_ID_CRYPTO                 = 20,   /* Crypto device */
    VIRTIO_DEVICE_ID_SIG_DIS_MOD            = 21,   /* Signal Distribution Module */
    VIRTIO_DEVICE_ID_PSTORE                 = 22,   /* Pstore device */
    VIRTIO_DEVICE_ID_IOMMU                  = 23,   /* IOMMU device */
    VIRTIO_DEVICE_ID_MEM                    = 24,   /* Memory device */
    /* virtio 1.2 */
    VIRTIO_DEVICE_ID_AUDIO                  = 25,   /* Audio device */
    VIRTIO_DEVICE_ID_FS                     = 26,   /* File system device */
    VIRTIO_DEVICE_ID_PMEM                   = 27,   /* PMEM device */
    VIRTIO_DEVICE_ID_RPMB                   = 28,   /* Replay protected memory block device */
    VIRTIO_DEVICE_ID_MAC80211_HWSIM         = 29,   /* Mac80211 hwsim wireless simulation device */
    VIRTIO_DEVICE_ID_VIDEO_ENCODER          = 30,   /* Video encoder device */
    VIRTIO_DEVICE_ID_VIDEO_DECODER          = 31,   /* Video decoder device */
    VIRTIO_DEVICE_ID_SCMI                   = 32,   /* SCMI device */
    VIRTIO_DEVICE_ID_NITRO_SEC_MOD          = 33,   /* NitroSecureModule */
    VIRTIO_DEVICE_ID_I2C_ADAPTER            = 34,   /* I2C adapter */
    VIRTIO_DEVICE_ID_WATCHDOG               = 35,   /* Watchdog */
    VIRTIO_DEVICE_ID_CAN                    = 36,   /* CAN device */
    VIRTIO_DEVICE_ID_DMABUF                 = 37,   /* Virtio dmabuf */
    VIRTIO_DEVICE_ID_PARAM_SERV             = 38,   /* Parameter Server */
    VIRTIO_DEVICE_ID_AUDIO_POLICY           = 39,   /* Audio policy device */
    VIRTIO_DEVICE_ID_BT                     = 40,   /* Bluetooth device */
    VIRTIO_DEVICE_ID_GPIO                   = 41,   /* GPIO device */
    VIRTIO_DEVICE_ID_RDMA                   = 42,   /* RDMA device */
    /* virtio 1.3 */
    VIRTIO_DEVICE_ID_CAMERA                 = 43,   /* Camera device */
    VIRTIO_DEVICE_ID_ISM                    = 44,   /* Internal shared memory device */
    VIRTIO_DEVICE_ID_SPI_MASTER             = 45,   /* SPI master */

    VIRTIO_DEVICE_ID_MAX
};

enum
{
    VIRTIO_PCI_SUBSYSTEM_DEVICE_ID_NET      = 0x1000,  /* Network card */
    VIRTIO_PCI_SUBSYSTEM_DEVICE_ID_BLOCK    = 0x1001,  /* Block device */
    VIRTIO_PCI_SUBSYSTEM_DEVICE_ID_BALLOON  = 0x1002,  /* Memory ballooning (traditional) */
    VIRTIO_PCI_SUBSYSTEM_DEVICE_ID_CONSOLE  = 0x1003,  /* Console */
    VIRTIO_PCI_SUBSYSTEM_DEVICE_ID_SCSI     = 0x1004,  /* SCSI host */
    VIRTIO_PCI_SUBSYSTEM_DEVICE_ID_RNG      = 0x1005,  /* Entropy source */
    VIRTIO_PCI_SUBSYSTEM_DEVICE_ID_9P       = 0x1009,  /* 9P transport */

    VIRTIO_PCI_SUBSYSTEM_DEVICE_ID_MAX
};

#endif /* __VIRTIO_IDS_H__ */
