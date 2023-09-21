/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_ENET_DRV_H
#define HPM_ENET_DRV_H

/*---------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------
 */
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

/*---------------------------------------------------------------------
 *  Macro Constant Declarations
 *---------------------------------------------------------------------
 */
#define ENET_HEADER               (14U)    /**< 6-byte Dest addr, 6-byte Src addr, 2-byte type */
#define ENET_EXTRA                (2U)     /**< Extra bytes in some cases */
#define ENET_VLAN_TAG             (4U)     /**< optional 802.1q VLAN Tag */
#define ENET_CRC                  (4U)     /**< Ethernet CRC */
#define ENET_MIN_PAYLOAD          (46U)    /**< Minimum Ethernet payload size */
#define ENET_MAX_PAYLOAD          (1500U)  /**< Maximum Ethernet payload size */
#define ENET_MAX_FRAME_SIZE       (1524U)  /**< ENET_HEADER + ENET_EXTRA + VLAN_TAG + MAX_ENET_PAYLOAD + ENET_CRC */
#define ENET_JUMBO_FRAME_PAYLOAD  (9000U)  /**< Jumbo frame payload size */
#define ENET_MAC                  (6)      /**< Ethernet MAC size */
#define ENET_ERROR                (0)      /**< ENET error */
#define ENET_SUCCESS              (1)      /**< ENET success */

#define ENET_ADJ_FREQ_BASE_ADDEND (0x80000000UL)  /**< PTP base adjustment addend */
#define ENET_ONE_SEC_IN_NANOSEC   (1000000000UL)  /**< one second in nanoseconds */

#define ENET_PPS_CMD_MASK         (0x07UL) /**< Enet PPS CMD Mask */
#define ENET_PPS_CMD_OFS_FAC      (3U)     /**< Enet PPS CMD OFS Factor */

#ifndef ENET_RETRY_CNT
#define ENET_RETRY_CNT            (10000UL)   /**< Enet retry count for PTP */
#endif

/*---------------------------------------------------------------------
 *  Typedef Enum Declarations
 *---------------------------------------------------------------------
 */

/** @brief Programmable burst length selections */
typedef enum {
    enet_normal_int_sum_en   = ENET_DMA_INTR_EN_NIE_MASK,
    enet_aboarmal_int_sum_en = ENET_DMA_INTR_EN_AIE_MASK,
    enet_receive_int_en      = ENET_DMA_INTR_EN_RIE_MASK
} enet_interrupt_enable_t;

/** @brief Programmable burst length selections */
typedef enum {
    enet_lpi_int_mask    = ENET_INTR_MASK_LPIIM_MASK,
    enet_rgsmii_int_mask = ENET_INTR_MASK_RGSMIIIM_MASK
} enet_interrupt_mask_t;


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
    enet_cic_disable            = 0,
    enet_cic_ip                 = 1,
    enet_cic_ip_no_pseudoheader = 2,
    enet_cic_ip_pseudoheader    = 3
} enet_cic_insertion_control_t;

/** @brief VLAN insertion control selections */
typedef enum {
    enet_vlic_disable          = 0,
    enet_vlic_remove_vlan_tag  = 1,
    enet_vlic_insert_vlan_tag  = 2,
    enet_vlic_replace_vlan_tag = 3
} enet_vlan_insertion_control_t;

/** @brief SA insertion or replacement control selections for any selective frames */
typedef enum {
    enet_saic_disable      = 0,
    enet_saic_insert_mac0  = 1,
    enet_saic_replace_mac0 = 2,
    enet_saic_insert_mac1  = 5,
    enet_saic_replace_mac1 = 6
} enet_saic_insertion_replacement_control_t;

/** @brief SA insertion or replacement control selections for all transmit frames */
typedef enum {
    enet_sarc_disable      = 0,
    enet_sarc_insert_mac0  = 2,
    enet_sarc_replace_mac0 = 3,
    enet_sarc_insert_mac1  = 6,
    enet_sarc_replace_mac1 = 7
} enet_sarc_insertion_replacement_control_t;

/** @brief PHY operation selections */
typedef enum {
    enet_phy_op_read = 0,
    enet_phy_op_write
} enet_phy_op_t;


/** @brief PHY status */
typedef enum {
    enet_gmii_idle = 0,
    enet_gmii_busy
} enet_gmii_status_t;

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

/** @brief enet line speed */
typedef enum {
    enet_line_speed_1000mbps  = 0,
    enet_line_speed_10mbps    = 2,
    enet_line_speed_100mbps   = 3
} enet_line_speed_t;

/** @brief enet duplex mode */
typedef enum {
    enet_half_duplex = 0,
    enet_full_duplex
} enet_duplex_mode_t;

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

/** @brief PTP timer rollover modes */
typedef enum {
    enet_ts_bin_rollover_control = 0,  /* timestamp rolls over after 0x7fffffff */
    enet_ts_dig_rollover_control       /* timestamp rolls over after 0x3b9ac9ff */
} enet_ts_rollover_control_t;

/** @brief PPS indexes */
typedef enum {
    enet_pps_0 = -1,
    enet_pps_1 = 0,
    enet_pps_2 = 1,
    enet_pps_3 = 2
} enet_pps_idx_t;

/** @brief PPS0 control for output frequency selections */
typedef enum {
    enet_pps_ctrl_pps = 0,
    enet_pps_ctrl_bin_2hz_digital_1hz,
    enet_pps_ctrl_bin_4hz_digital_2hz,
    enet_pps_ctrl_bin_8hz_digital_4hz,
    enet_pps_ctrl_bin_16hz_digital_8hz,
    enet_pps_ctrl_bin_32hz_digital_16hz,
    enet_pps_ctrl_bin_64hz_digital_32hz,
    enet_pps_ctrl_bin_128hz_digital_64hz,
    enet_pps_ctrl_bin_256hz_digital_128hz,
    enet_pps_ctrl_bin_512hz_digital_256hz,
    enet_pps_ctrl_bin_1024hz_digital_512hz,
    enet_pps_ctrl_bin_2048hz_digital_1024hz,
    enet_pps_ctrl_bin_4096hz_digital_2048hz,
    enet_pps_ctrl_bin_8192hz_digital_4096hz,
    enet_pps_ctrl_bin_16384hz_digital_8192hz,
    enet_pps_ctrl_bin_32867hz_digital_16384hz
} enet_pps_ctrl_t;

/** @brief PPS0 commands */
typedef enum {
    enet_pps_cmd_no_command = 0,
    enet_pps_cmd_start_single_pulse,
    enet_pps_cmd_start_pulse_train,
    enet_pps_cmd_cancel_start,
    enet_pps_cmd_stop_pulse_train_at_time,
    enet_pps_cmd_stop_pulse_train_immediately,
    enet_pps_cmd_cancel_stop_pulse_train
} enet_pps_cmd_t;

/*---------------------------------------------------------------------
 *  Typedef Struct Declarations
 *---------------------------------------------------------------------
 */
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
    uint8_t  dma_pbl;
    uint8_t  sarc;
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
            uint32_t saic    :  3; /**< SA Insertion Control */
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
typedef struct {
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
    } rdes6_bm;

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

/** @brief enet control config struct for transmission */
typedef struct {
    bool enable_ioc;        /* interrupt on completion */
    bool disable_crc;       /* disable CRC */
    bool disable_pad;       /* disable Pad */
    bool enable_ttse;       /* enable transmit timestamp */
    bool enable_crcr;       /* CRC replacement control */
    uint8_t cic;            /* checksum insertion control */
    uint8_t vlic;           /* VLAN insertion control */
    uint8_t saic;           /* SA insertion control */
} enet_tx_control_config_t;

/** @brief enet description struct */
typedef struct {
    enet_tx_desc_t *tx_desc_list_head;
    enet_rx_desc_t *rx_desc_list_head;
    enet_tx_desc_t *tx_desc_list_cur;
    enet_rx_desc_t *rx_desc_list_cur;
    enet_buff_config_t tx_buff_cfg;
    enet_buff_config_t rx_buff_cfg;
    enet_rx_frame_info_t rx_frame_info;
    enet_tx_control_config_t tx_control_config;
} enet_desc_t;

/** @brief PTP system timestamp struct */
typedef struct {
    uint32_t sec;
    uint32_t nsec;
} enet_ptp_ts_system_t;

/** @brief PTP update timestamp struct */
typedef struct {
    uint32_t sec;
    uint32_t nsec;
    uint8_t sign;
} enet_ptp_ts_update_t;

/** @brief PTP target timestamp struct */
typedef struct {
    uint32_t sec;
    uint32_t nsec;
} enet_ptp_ts_target_t;

/** @brief PTP config strcut */
typedef struct {
    uint8_t ssinc;
    uint8_t timestamp_rollover_mode;
    uint8_t update_method;
    uint32_t addend;
} enet_ptp_config_t;

/** @brief PTP PPS command output config strcut */
typedef struct {
    uint32_t pps_interval;
    uint32_t pps_width;
    uint32_t target_sec;
    uint32_t target_nsec;
} enet_pps_cmd_config_t;

/** @brief Enet interrupt config struct */
typedef struct {
    uint32_t int_enable;       /* DMA_INTR_EN */
    uint32_t int_mask;         /* INTR MASK */
    uint32_t mmc_intr_rx;
    uint32_t mmc_intr_mask_rx;
    uint32_t mmc_intr_tx;
    uint32_t mmc_intr_mask_tx;
} enet_int_config_t;

/*
 *  @brief Bit definition of TDES1
 */
#define ENET_DMATxDesc_TBS2  ((uint32_t)0x1FFF0000)  /**< Transmit Buffer2 Size */
#define ENET_DMATxDesc_TBS1  ((uint32_t)0x00001FFF)  /**< Transmit Buffer1 Size */

#if defined __cplusplus
extern "C" {
#endif /* __cplusplus */
/*---------------------------------------------------------------------
 * Exported Functions
 *---------------------------------------------------------------------
 */
/**
 * @brief Get a default control config for tranmission
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] config A pointer to a control config structure for tranmission
 */
void enet_get_default_tx_control_config(ENET_Type *ptr, enet_tx_control_config_t *config);

/**
 * @brief Get interrupt status
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @return A result of interrupt status
 */
uint32_t enet_get_interrupt_status(ENET_Type *ptr);

/**
 * @brief Mask the specified mmc interrupt evenets of received frames
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] config A mask of the specified evenets
 */
void enet_mask_mmc_rx_interrupt_event(ENET_Type *ptr, uint32_t mask);

/**
 * @brief Mask the specified mmc interrupt evenets of transmitted frames
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] config A mask of the specified evenets
 */
void enet_mask_mmc_tx_interrupt_event(ENET_Type *ptr, uint32_t mask);

/**
 * @brief Get a staus of mmc receive interrupt events
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @return A result of interrupt status
 */
uint32_t enet_get_mmc_rx_interrupt_status(ENET_Type *ptr);
/**
 * @brief et a staus of mmc transmission interrupt events
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @return A result of interrupt status
 */
uint32_t enet_get_mmc_tx_interrupt_status(ENET_Type *ptr);

/**
 * @brief Initialize controller
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] inf_type the specified interface
 * @param[in] desc A pointer to descriptor config
 * @param[in] cfg A pointer to mac config
 * @param[in] int_cfg A pointer to the masks of the specified enabled interrupts and the specified masked interrupts
 */
int enet_controller_init(ENET_Type *ptr, enet_inf_type_t inf_type, enet_desc_t *desc, enet_mac_config_t *cfg, enet_int_config_t *int_config);

/**
 * @brief Set port line speed
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] line_speed An enum variable of @ref enet_line_speed_t
 */
void enet_set_line_speed(ENET_Type *ptr, enet_line_speed_t speed);

/**
 * @brief Set duplex mode
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] mode An enum variable of @ref enet_duplex_mode_t
 */
void enet_set_duplex_mode(ENET_Type *ptr, enet_duplex_mode_t mode);

/**
 * @brief Read phy
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] phy_addr the specified address of phy
 * @param[in] addr the specified address of register
 * @retval A value corresponding to the specified register address
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
 * @param[out] parent_rx_desc_list_cur a parent pointer to the current reception description list
 * @param[in] rx_frame_info A pointer to the information of the reception frames
 * @retval A result of reception frame.
 *         1 means that a reception of frame is successful.
 *         0 means that a reception of frame is unsuccessful.
 */
uint32_t enet_check_received_frame(enet_rx_desc_t **parent_rx_desc_list_cur, enet_rx_frame_info_t *rx_frame_info);

/**
 * @brief get a received frame
 *
 * @param[out] parent_rx_desc_list_cur A parent pointer to the current reception description list
 * @param[in] rx_frame_info A pointer to the information of the reception frames
 * @retval A struct of the current reception frame
 */
enet_frame_t enet_get_received_frame(enet_rx_desc_t **parent_rx_desc_list_cur, enet_rx_frame_info_t *rx_frame_info);

/**
 * @brief get a received frame from interrupt
 *
 * @param[out] parent_rx_desc_list_cur the parent pointer to the current reception description list
 * @param[in] rx_frame_info A pointer to the information of the reception frames
 * @param[in] rx_desc_count A total count of the reception descriptors
 * @retval A struct of the current reception frame
 */
enet_frame_t enet_get_received_frame_interrupt(enet_rx_desc_t **parent_rx_desc_list_cur, enet_rx_frame_info_t *rx_frame_info, uint32_t rx_desc_count);

/**
 * @brief prepare for the transmission descriptors (It will be deprecated.)
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[out] parent_tx_desc_list_cur a pointer to the information of the reception frames
 * @param[in] frame_length the length of the transmission
 * @param[in] tx_buff_size the size of the transmission buffer
 * @retval a result of the transmission preparation.
 *         1 means that the preparation is successful.
 *         0 means that the preparation is unsuccessful.
 */
uint32_t enet_prepare_transmission_descriptors(ENET_Type *ptr, enet_tx_desc_t **parent_tx_desc_list_cur, uint16_t frame_length, uint16_t tx_buff_size);

/**
 * @brief prepare for the transmission descriptors
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[out] parent_tx_desc_list_cur a pointer to the information of the reception frames
 * @param[in] config a pointer to the control configuration for the transmission frames
 * @param[in] frame_length the length of the transmission
 * @param[in] tx_buff_size the size of the transmission buffer
 * @retval a result of the transmission preparation.
 *         1 means that the preparation is successful.
 *         0 means that the preparation is unsuccessful.
 */
uint32_t enet_prepare_tx_desc(ENET_Type *ptr, enet_tx_desc_t **parent_tx_desc_list_cur, enet_tx_control_config_t *config, uint16_t frame_length, uint16_t tx_buff_size);

/**
 * @brief prepare for the transmission descriptors with a timestamp record
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[out] parent_tx_desc_list_cur a pointer to the information of the reception frames
 * @param[in] config a pointer to the control configuration for the transmission frames
 * @param[in] frame_length the length of the transmission
 * @param[in] tx_buff_size the size of the transmission buffer
 * @param[out] timestamp a pointer to the timestamp record of a transmitted frame
 * @retval a result of the transmission preparation.
 *         1 means that the preparation is successful.
 *         0 means that the preparation is unsuccessful.
 */
uint32_t enet_prepare_tx_desc_with_ts_record(ENET_Type *ptr,
                                             enet_tx_desc_t **parent_tx_desc_list_cur,
                                             enet_tx_control_config_t *config,
                                             uint16_t frame_length, uint16_t tx_buff_size,
                                             enet_ptp_ts_system_t *timestamp);

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
 * @param[in] timestamp A pointer to a update timestamp structure instance
 */
void enet_set_ptp_timestamp(ENET_Type *ptr, enet_ptp_ts_update_t *timestamp);

/**
 * @brief Get a timestamp from the PTP timer
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[out] timestamp A pointer to a system timestamp structure instance
 */
void enet_get_ptp_timestamp(ENET_Type *ptr, enet_ptp_ts_system_t *timestamp);

/**
 * @brief Update a timestamp to the PTP timer
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] timeoffset A pointer to a update timestamp structure instance
 */
void enet_update_ptp_timeoffset(ENET_Type *ptr, enet_ptp_ts_update_t *timeoffset);

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

/**
 * @brief Set the pps0 control output
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] enet_pps_ctrl_t An enum value indicating the specified pps frequency
 */
void enet_set_pps0_control_output(ENET_Type *ptr, enet_pps_ctrl_t freq);

/**
 * @brief Set a pps command for ppsx
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] cmd An enum value indicating the specified pps command
 * @param[in] idx An enum value indicating the index of pps instance
 * @retval hpm_stat_t @ref status_invalid_argument or @ref status_success
 */
hpm_stat_t enet_set_ppsx_command(ENET_Type *ptr, enet_pps_cmd_t cmd, enet_pps_idx_t idx);

/**
 * @brief Set a pps config for ppsx
 *
 * @param[in] ptr An Ethernet peripheral base address
 * @param[in] cmd An enum value indicating the specified pps config
 * @param[in] idx An enum value indicating the index of pps instance
 * @retval hpm_stat_t @ref status_invalid_argument or @ref status_success
 */
hpm_stat_t enet_set_ppsx_config(ENET_Type *ptr, enet_pps_cmd_config_t *cmd_cfg, enet_pps_idx_t idx);

#if defined __cplusplus
}
#endif /* __cplusplus */

/** @} */
#endif /* HPM_ENET_DRV_H */
