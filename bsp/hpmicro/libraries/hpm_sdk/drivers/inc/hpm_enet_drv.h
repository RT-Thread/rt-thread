/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_ENET_DRV_H
#define HPM_ENET_DRV_H

/*---------------------------------------------------------------------*
 * Includes
 *---------------------------------------------------------------------*/
#include "hpm_common.h"
#include "hpm_enet_regs.h"
#include "hpm_soc_feature.h"
#include "hpm_enet_soc_drv.h"

/**
 * @brief Enet driver APIs
 * @defgroup enet_interface Enet driver APIs
 * @ingroup communication_interfaces
 * @{
 */

/*---------------------------------------------------------------------*
 *  Macro Constant Declarations
 *---------------------------------------------------------------------*/
#define ENET_HEADER               (14U)    /**< 6-byte Dest addr, 6-byte Src addr, 2-byte type */
#define ENET_EXTRA                (2U)     /**< Extra bytes in some cases */
#define ENET_VLAN_TAG             (4U)     /**< optional 802.1q VLAN Tag */
#define ENET_CRC                  (4U)     /**< Ethernet CRC */
#define ENET_MIN_PAYLOAD          (46U)    /**< Minimum Ethernet payload size */
#define ENET_MAX_PAYLOAD          (1500U)  /**< Maximum Ethernet payload size */
#define ENET_MAX_FRAME_SIZE       (1524U)  /**< ENET_HEADER + ENET_EXTRA + VLAN_TAG + MAX_ENET_PAYLOAD + ENET_CRC */
#define ENET_JUMBO_FRAME_PAYLOAD  (9000U)  /**< Jumbo frame payload size */

#define ENET_ERROR                (0)   /**< ENET error */
#define ENET_SUCCESS              (1)   /**< ENET success */

#define ENET_ADJ_FREQ_BASE_ADDEND (0x7fffffffUL)  /**< PTP base adjustment addend */
#define ENET_ONE_SEC_IN_NANOSEC   (1000000000UL)  /**< one second in nanoseconds */
/*---------------------------------------------------------------------*
 *  Typedef Enum Declarations
 *---------------------------------------------------------------------*/
/** @brief Programmable burst length selections */
typedef enum {
    enet_pbl_1  = 1,
    enet_pbl_2  = 2,
    enet_pbl_4  = 4,
    enet_pbl_8  = 8,
    enet_pbl_16 = 16,
    enet_pbl_32 = 32
} enet_pbl_t;

/** @brief Checksum insertion control selections */
typedef enum {
    enet_cic_bypass = 0,
    enet_cic_insert_ipv4_header,
    enet_cic_insert_tcp_udp_icmp,
    enet_cic_insert_tcp_upd_icmp,
} enet_insert_t;

/** @brief PHY opeartion selections */
typedef enum {
    enet_phy_op_read = 0,
    enet_phy_op_write
} enet_phy_op_t;


/** @brief PHY status */
typedef enum {
    enet_phy_idle = 0,
    enet_phy_busy
} enet_phy_status_t;

/** @brief CSR clock range and MDC clock selections */
/** @note The suggested range of CSR clock is approximately
 *        between the frequency range 1.0MHz-2.5MHz.
 *        You can achieve higher frequency of the MDC clock than the frequency limit of 2.5MHz(specified in the IEEE Std 802.3)
 *        and program a clock divider of lower value. Program the value which is no less than enet_csr_60m_to_100m_mdc_csr_div_4
 *        only if the interfacing chips support faster MDC clocks.
 */
typedef enum {
    enet_csr_60m_to_100m_mdc_csr_div_42 = 0,    /**< CSR clock range: 60-100MHz <==> MDC clock: CSR clock / 42 */
    enet_csr_100m_to_150m_mdc_csr_div_62,       /**< CSR clock range: 100-150MHz <==> MDC clock: CSR clock / 62 */
    enet_csr_20m_to_35m_mdc_csr_div_16,         /**< CSR clock range: 20-35MHz <==> MDC clock: CSR clock / 16 */
    enet_csr_35m_to_60m_mdc_csr_div_26,         /**< CSR clock range: 35-60MHz <==> MDC clock: CSR clock / 26 */
    enet_csr_150m_to_250m_mdc_csr_div_102,      /**< CSR clock range: 150-250MHz <==> MDC clock: CSR clock / 102 */
    enet_csr_250m_to_300m_mdc_csr_div_124,      /**< CSR clock range: 250-300MHz <==> MDC clock: CSR clock / 124 */

    enet_csr_60m_to_100m_mdc_csr_div_4 = 8,     /**< CSR clock / 4 */
    enet_csr_60m_to_100m_mdc_csr_div_6,         /**< CSR clock / 6 */
    enet_csr_60m_to_100m_mdc_csr_div_8,         /**< CSR clock / 8 */
    enet_csr_60m_to_100m_mdc_csr_div_10,        /**< CSR clock / 10 */
    enet_csr_60m_to_100m_mdc_csr_div_12,        /**< CSR clock / 12 */
    enet_csr_60m_to_100m_mdc_csr_div_14,        /**< CSR clock / 14 */
    enet_csr_60m_to_100m_mdc_csr_div_16,        /**< CSR clock / 16 */
    enet_csr_60m_to_100m_mdc_csr_div_18         /**< CSR clock / 18 */
} enet_csr_clk_range_t;

/** @brief enet interface selections */
typedef enum {
    enet_inf_rmii = 4,
    enet_inf_rgmii = 1
} enet_inf_type_t;

/** @brief enet timestamp update methods */
typedef enum {
    enet_ptp_time_coarse_update = 0,
    enet_ptp_time_fine_update
} enet_ptp_time_update_method_t;

/** @brief PTP versions */
typedef enum {
    enet_ptp_v1 = 0,
    enet_ptp_v2
} enet_ptp_version_t;

/** @brief PTP frame types */
typedef enum {
    enet_ptp_frame_ipv4 = 0,
    enet_ptp_frame_ipv6,
    enet_ptp_frame_ethernet
} enet_ptp_frame_type_t;

/** @brief PTP message type for snapshots */
typedef enum {
    enet_ts_ss_ptp_msg_0 = 0, /* SYNC, Follow_Up, Delay_Req, Delay_Resp */
    enet_ts_ss_ptp_msg_1 = 1, /* SYNC */
    enet_ts_ss_ptp_msg_2 = 3, /* Delay_Req */
    enet_ts_ss_ptp_msg_3 = 4, /* SYNC, Follow_Up, Delay_Req, Delay_Resp, Pdelay_Req, Pdelay_Resp, Pdelay_Resp_Follow_Up */
    enet_ts_ss_ptp_msg_4 = 5, /* SYNC, Pdelay_Req, Pdelay_Resp */
    enet_ts_ss_ptp_msg_5 = 7, /* Delay_Req, Pdelay_Req, Pdelay_Resp */
    enet_ts_ss_ptp_msg_6 = 8, /* SYNC, Delay_Req */
    enet_ts_ss_ptp_msg_7 = 12 /* Pdelay_Req, Pdelay_Resp */
} enet_ts_ss_ptp_msg_t;

typedef enum {
    enet_ptp_count_res_high = 0,  /* ptp sub-second count resolution at 0.465 ns */
    enet_ptp_count_res_low        /* ptp su-second count resolution at 1 ns */
} enet_ptp_count_res_t;

/*---------------------------------------------------------------------*
 *  Typedef Struct Declarations
 *---------------------------------------------------------------------*/
/** @brief enet buffer config struct */
typedef struct {
    uint32_t buffer;
    uint32_t count;
    uint16_t size;
} enet_buff_config_t;


/** @brief enet mac config struct */
typedef struct {
    uint32_t mac_addr_high[ENET_SOC_ADDR_MAX_COUNT];
    uint32_t mac_addr_low[ENET_SOC_ADDR_MAX_COUNT];
    uint8_t  valid_max_count;
} enet_mac_config_t;

/** @brief transmission descriptor struct */
typedef struct {
    union {
        uint32_t tdes0;
        struct {
            uint32_t db:   1; /**< * Deferred Bit*/
            uint32_t uf:   1; /**< * Underflow Error */
            uint32_t ed:   1; /**< * Excessive Deferral */
            uint32_t cc:   4; /**< * Collision Count */
            uint32_t vf:   1; /**< * VLAN Frame */
            uint32_t ec:   1; /**< * Excessive Collision */
            uint32_t lc:   1; /**< * Late Collision */
            uint32_t nc:   1; /**< * No Carrier */
            uint32_t loc:  1; /**< * Loss of Carrier */
            uint32_t ipe:  1; /**< * IP Payload Error */
            uint32_t ff:   1; /**< * Frame Flushed */
            uint32_t jt:   1; /**< * Jabber Timeout */
            uint32_t es:   1; /**< * Error Summary */
            uint32_t ihe:  1; /**< * IP Header Error */
            uint32_t ttss: 1; /**< * Transmit Timestamp Status */
            uint32_t vlic: 2; /**< * VLAN Insertion Control */
            uint32_t tch:  1; /**< * Second Address Chained */
            uint32_t ter:  1; /**< * Transmit End of Ring */
            uint32_t cic:  2; /**< * Checksum Insertion Control */
            uint32_t crcr: 1; /**< * CRC Replacement Control */
            uint32_t ttse: 1; /**< * Transmit Timestamp Enable */
            uint32_t dp:   1; /**< * Disable Pad */
            uint32_t dc:   1; /**< * Disable CRC */
            uint32_t fs:   1; /**< * First Segment */
            uint32_t ls:   1; /**< * Last Segment */
            uint32_t ic:   1; /**< * Interrupt on Completion */
            uint32_t own:  1; /**< * Own Bit */
        } tdes0_bm;
    };

    union {
        uint32_t tdes1;
        struct {
            uint32_t tbs1    : 13; /**< Transmit Buffer 1 Size */
            uint32_t reserved:  3; /**< Reserved */
            uint32_t tbs2    : 13; /**< Transmit Buffer 2 Size */
            uint32_t saic    :  3; /**< SA Inertion Control */
        } tdes1_bm;
    };

    union {
        uint32_t tdes2;
        struct {
             uint32_t buffer1;  /**< Buffer 1 Address */
        } tdes2_bm;
    };

    union {
        uint32_t tdes3;
        union {
            uint32_t buffer2;   /**< Buffer 2 Address */
            uint32_t next_desc; /**< Next Descriptor Address */
        } tdes3_bm;
    };

#if ENET_SOC_ALT_EHD_DES_LEN == ENET_SOC_ALT_EHD_DES_MAX_LEN
    struct {
        uint32_t reserved;
    } tdes4_bm;

    struct {
        uint32_t reserved;
    } tdes5_bm;

    struct {
        uint32_t ttsl;  /**< Transmit Frame Timestamp Low */
    } tdes6_bm;

    struct {
        uint32_t ttsh;  /**< Transmit Frame Timestamp High */
    } tdes7_bm;
#endif
} enet_tx_desc_t;


/** @brief reception descriptor struct */
typedef struct
{
    union {
        uint32_t rdes0;

        struct {
                uint32_t ex_sta_rx_addr      : 1;  /**< Extended Status Available or Rx MAC Address*/
                uint32_t ce                  : 1;  /**< CRC Error */
                uint32_t dbe                 : 1;  /**< Dribble Bit Error */
                uint32_t re                  : 1;  /**< Receive Error */
                uint32_t rwt                 : 1;  /**< Receive Watchdog Timeout */
                uint32_t ft                  : 1;  /**< Frame Type */
                uint32_t lc                  : 1;  /**< Late Collision */
                uint32_t ts_ip_gf            : 1;  /**< Timestamp Available, IP Checksum Error or Giant Frame*/
                uint32_t ls                  : 1;  /**< Last Descriptor */
                uint32_t fs                  : 1;  /**< First Descriptor */
                uint32_t vlan                : 1;  /**< VLAN Tag */
                uint32_t oe                  : 1;  /**< Overflow Error */
                uint32_t le                  : 1;  /**< Length Error */
                uint32_t saf                 : 1;  /**< Source Address Filter Fail */
                uint32_t dse                 : 1;  /**< Descriptor Error */
                uint32_t es                  : 1;  /**< Error Summary */
                uint32_t fl                  : 14; /**< Frame Length */
                uint32_t afm                 : 1;  /**< Destination Address Filter Fail */
                uint32_t own                 : 1;  /**< Own Bit */
        } rdes0_bm;
    };

    union {
        uint32_t rdes1;
        struct {
            uint32_t rbs1     : 13; /**< Receive Buffer 1 Size */
            uint32_t reserved0: 1;  /**< Reserved */
            uint32_t rch      : 1;  /**< Second Address Chained */
            uint32_t rer      : 1;  /**< Receive End of Ring */
            uint32_t rbs2     : 13; /**< Receive Buffer 2 Size */
            uint32_t reserved1: 2;  /**< Reserved */
            uint32_t dic      : 1;  /**< Disable Interrupt on Completion */
        } rdes1_bm;
    };

    union {
        uint32_t rdes2;
        struct {
        uint32_t buffer1;       /**< Buffer 1 Address */
        } rdes2_bm;
    };

    union {
        uint32_t rdes3;
        union {
            uint32_t buffer2;   /**< Buffer 2 Address */
            uint32_t next_desc; /**< Next Descriptor Address */
        } rdes3_bm;
    };

#if ENET_SOC_ALT_EHD_DES_LEN == ENET_SOC_ALT_EHD_DES_MAX_LEN
    union {
        uint32_t rdes4;
        struct {
                uint32_t ip_payload_type     : 3; /**< IP Payload Type */
                uint32_t ip_header_err       : 1; /**< IP Header Error */
                uint32_t ip_payload_err      : 1; /**< IP Payload Error */
                uint32_t ip_chksum_bypassed  : 1; /**< IP Checksum Bypassed */
                uint32_t ipv4_pkt_received   : 1; /**< IPv4 Packet Received */
                uint32_t ipv6_pkt_received   : 1; /**< IPv6 Packet Received */
                uint32_t msg_type            : 4; /**< Message Type */
                uint32_t ptp_frame_type      : 1; /**< PTP Frame Type */
                uint32_t ptp_version         : 1; /**< PTP Version */
                uint32_t ts_dp               : 1; /**< Timestamp Dropped */
                uint32_t reserved0           : 1; /**< Reserved */
                uint32_t av_pkt_recv         : 1; /**< AV Packet Received */
                uint32_t av_tagged_pkt_recv  : 1; /**< AV Tagged Packet Received */
                uint32_t vlan_tag_pri_value  : 3; /**< VLAN Tag Priority Value */
                uint32_t reserved1           : 3; /**< Reserved */
                uint32_t l3_fm               : 1; /**< Layer 3 Filter Matched */
                uint32_t l4_fm               : 1; /**< Layer 4 Filter Matched */
                uint32_t l3_l4_fnl           : 2; /**< Layer 3 and Layer 4 Filter Number Matched */
                uint32_t reserved2           : 4; /**< Reserved */
            } rdes4_bm;
    };

    struct {
        uint32_t reserved;
    } rdes5_bm;

    struct {
        uint32_t rtsl;  /**< Receive Frame Timestamp Low */
    }rdes6_bm;

    struct {
        uint32_t rtsh;  /**< Receive Frame Timestamp High */
    } rdes7_bm;
#endif
} enet_rx_desc_t;

/** @brief enet frame struct */
typedef struct{
    uint32_t length;
    uint32_t buffer;
    enet_rx_desc_t *rx_desc;
} enet_frame_t;

/** @brief enet reception frame info struct */
typedef struct  {
    enet_rx_desc_t *fs_rx_desc;
    enet_rx_desc_t *ls_rx_desc;
    uint32_t  seg_count;
} enet_rx_frame_info_t;

/** @brief enet description struct */
typedef struct {
    enet_tx_desc_t *tx_desc_list_head;
    enet_rx_desc_t *rx_desc_list_head;
    enet_tx_desc_t *tx_desc_list_cur;
    enet_rx_desc_t *rx_desc_list_cur;
    enet_buff_config_t tx_buff_cfg;
    enet_buff_config_t rx_buff_cfg;
    enet_rx_frame_info_t rx_frame_info;
} enet_desc_t;

/** @brief PTP timestamp struct */
typedef struct {
    uint32_t sec;
    uint32_t nsec;
    uint8_t sign;
} enet_ptp_time_t;

/* PTP config strcut */
typedef struct {
    uint8_t ssinc;
    uint8_t sub_sec_count_res;
    uint8_t update_method;
    uint32_t addend;
} enet_ptp_config_t;

/*
 *  @brief Bit definition of TDES1
 */
#define ENET_DMATxDesc_TBS2  ((uint32_t)0x1FFF0000)  /**< Transmit Buffer2 Size */
#define ENET_DMATxDesc_TBS1  ((uint32_t)0x00001FFF)  /**< Transmit Buffer1 Size */

#if defined __cplusplus
extern "C" {
#endif /* __cplusplus */
/*---------------------------------------------------------------------*
 * Exported Functions
 *---------------------------------------------------------------------*/
/**
 * @brief Initialize controller
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] inf_type the specified interface
 * @param[in] desc A pointer to descriptor config
 * @param[in] config A pointer to mac config
 * @param[in] intr A mask of all required interrupts
 * @pramm[in] mask_intr A mask of all not required interrupts
 */
int enet_controller_init(ENET_Type *ptr, enet_inf_type_t inf_type, enet_desc_t *desc, enet_mac_config_t *config, uint32_t intr, uint32_t mask_intr);
/**
 * @brief Read phy
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] phy_addr the specified address of phy
 * @param[in] addr the specified address of register
 * @retval A value corresponding to the specifeid register address
 */
uint16_t enet_read_phy(ENET_Type *ptr, uint32_t phy_addr, uint32_t addr);

/**
 * @brief Write phy
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] phy_addr a specified address of phy
 * @param[in] addr a specified address of the register
 * @param[in] data a specified data to be written
 */
void enet_write_phy(ENET_Type *ptr, uint32_t phy_addr, uint32_t addr, uint32_t data);

/**
 * @brief Check if there is a received frame
 *
 * @param[out] parent_rx_desc_list_cur a parrent pointer to the current reception descritpion list
 * @param[in] rx_frame_info A pointer to the information of the reception frames
 * @retval A result of reception frame.
 *         1 means that a reception of frame is successful.
 *         0 means that a reception of frame is unsuccessful.
 */
uint32_t enet_check_received_frame(enet_rx_desc_t **parent_rx_desc_list_cur, enet_rx_frame_info_t *rx_frame_info);

/**
 * @brief get a received frame
 *
 * @param[out] parent_rx_desc_list_cur A parrent pointer to the current reception descritpion list
 * @param[in] rx_frame_info A pointer to the information of the reception frames
 * @retval A struct of the current reception frame
 */
enet_frame_t enet_get_received_frame(enet_rx_desc_t **parent_rx_desc_list_cur, enet_rx_frame_info_t *rx_frame_info);

/**
 * @brief get a received frame from interrupt
 *
 * @param[out] parent_rx_desc_list_cur the parrent pointer to the current reception descritpion list
 * @param[in] rx_frame_info A pointer to the information of the reception frames
 * @param[in] rx_desc_count A total count of the reception descriptors
 * @retval A struct of the current reception frame
 */
enet_frame_t enet_get_received_frame_interrupt(enet_rx_desc_t **parent_rx_desc_list_cur, enet_rx_frame_info_t *rx_frame_info, uint32_t rx_desc_count);

/**
 * @brief prepare for the transmission descriptors
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[out] parent_tx_desc_list_cur a pointer to the information of the reception frames
 * @param[in] frame_length the length of the transmission
 * @param[in] tx_buff_size the size of the transmission buffer
 * @retval a result of the transmission preparation.
 *         1 means that the preparation is successful.
 *         0 means that the prepartion is unsuccessful.
 */
uint32_t enet_prepare_transmission_descriptors(ENET_Type *ptr, enet_tx_desc_t **parent_tx_desc_list_cur, uint16_t frame_length, uint16_t tx_buff_size);

/**
 * @brief Initialize DMA transmission descriptors in chain mode
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] desc A pointer to transmission descriptors
 */
void enet_dma_tx_desc_chain_init(ENET_Type *ptr, enet_desc_t *desc);

/**
 * @brief Initialize DMA reception descriptors in chain mode
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] desc A pointer to reception descriptors
 */
void enet_dma_rx_desc_chain_init(ENET_Type *ptr,  enet_desc_t *desc);

/**
 * @brief Flush DMA
 *
 * @param[in] ptr An Ethernet peripheral base address
 */
void enet_dma_flush(ENET_Type *ptr);

/**
 * @brief Initialize a PTP timer
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] config A pointer to an enet_ptp_config struct instance
 */
void enet_init_ptp(ENET_Type *ptr, enet_ptp_config_t *config);

/**
 * @brief Set a timestamp to the PTP timer
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] timestamp A pointer to a timestamp structure instance
 */
void enet_set_ptp_timestamp(ENET_Type *ptr, enet_ptp_time_t *timestamp);

/**
 * @brief Get a timestamp from the PTP timer
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[out] timestamp A pointer to a timestamp structure instance
 */
void enet_get_ptp_timestamp(ENET_Type *ptr, enet_ptp_time_t *timestamp);

/**
 * @brief Update a timestamp to the PTP timer
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] timeoffset A pointer to a timestamp structure instance
 */
void enet_update_ptp_timeoffset(ENET_Type *ptr, enet_ptp_time_t *timeoffset);

/**
 * @brief Adjust the count frequency of the PTP timer
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] adj An adjustment value for the count frequency of the PTP timer
 */
void enet_adjust_ptp_time_freq(ENET_Type *ptr, int32_t adj);

/**
 * @brief Set the PTP version
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] ptp_ver An enum value indicating the PTP protocol
 */
void enet_set_ptp_version(ENET_Type *ptr, enet_ptp_version_t ptp_ver);

/**
 * @brief Enable the specified ptp frame type for MAC process
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] ptp_frame_type An enum value indicating the transport protocol of PTP frames
 * @param[in] enable A value to enable or disable the transport protocol of PTP frames which is specified by ptp_frame_type parameter
 * @retval hpm_stat_t @ref status_invalid_argument or @ref status_success
 */
hpm_stat_t enet_enable_ptp_frame_type(ENET_Type *ptr, enet_ptp_frame_type_t ptp_frame_type, bool enable);

/**
 * @brief Set the ptp message type for snapshots
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] ts_ss_ptp_msg An enum value indicating the specified ptp message type for snapshots
 */
void enet_set_snapshot_ptp_message_type(ENET_Type *ptr, enet_ts_ss_ptp_msg_t ts_ss_ptp_msg);

#if defined __cplusplus
}
#endif /* __cplusplus */

/** @} */
#endif /* HPM_ENET_DRV_H */
