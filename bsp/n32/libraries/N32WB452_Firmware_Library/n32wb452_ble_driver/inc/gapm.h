/**
 ****************************************************************************************
 *
 * @file gapm.h
 *
 * @brief Generic Access Profile Manager Header.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 ****************************************************************************************
 */


#ifndef _GAPM_H_
#define _GAPM_H_

/**
 ****************************************************************************************
 * @addtogroup GAPM Generic Access Profile Manager
 * @ingroup GAP
 * @brief Generic Access Profile Manager.
 *
 * The GAP Manager module is responsible for providing an API to the application in order
 * to manage all non connected stuff such as configuring device to go in desired mode
 * (discoverable, connectable, etc.) and perform required actions (scanning, connection,
 * etc.). GAP Manager is also responsible of managing GAP Controller state according to
 * corresponding BLE connection states.
 *
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"
#include "ke_task.h"
#include "gap.h"

/*
 * DEFINES
 ****************************************************************************************
 */
/// Bit checking
#define GAPM_ISBITSET(flag, mask)                   (((flag)&(mask)) == mask)





/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Initialize Generic Access Profile Manager Module.
 *
 * @param[in] reset  true if it's requested by a reset; false if it's boot initialization
 *
 ****************************************************************************************
 */
void gapm_init(bool reset);


/**
 ****************************************************************************************
 * @brief Retrieve Task Identifier from Task number
 * (automatically update index of task in returned task id)
 *
 * @param task Task number
 * @return Task Identifier
 ****************************************************************************************
 */
ke_task_id_t gapm_get_id_from_task(ke_msg_id_t task);

/**
 ****************************************************************************************
 * @brief Retrieve Task Number from Task Identifier
 * (automatically update index of task in returned task id)
 *
 * @param id Task Identifier
 * @return Task Number
 ****************************************************************************************
 */
ke_task_id_t gapm_get_task_from_id(ke_msg_id_t id);



#if (BLE_GAPC)
/**
 ****************************************************************************************
 * @brief Created link connection parameters (from bond data) has been set, connection
 * ready to be used.
 *
 * @param[in] conidx     Connection Index
 *
 ****************************************************************************************
 */
void gapm_con_enable(uint8_t conidx);


/**
 ****************************************************************************************
 * @brief A link has been disconnected, clean-up host stack for this connection.
 *
 * @param[in] conidx     Connection Index
 * @param[in] conhdl     Connection Handle
 * @param[in] reason     Reason of the disconnection
 *
 ****************************************************************************************
 */
void gapm_con_cleanup(uint8_t conidx, uint16_t conhdl, uint8_t reason);

#endif // (BLE_GAPC)


/**
 ****************************************************************************************
 * @brief Retrieve device identity key.
 *
 * @return Device Identity Key
 ****************************************************************************************
 */
struct gap_sec_key* gapm_get_irk(void);


/**
 ****************************************************************************************
 * @brief Retrieve local public address.
 *
 * @return Return local public address
 ****************************************************************************************
 */
bd_addr_t* gapm_get_bdaddr(void);



#ifdef BLE_AUDIO_AM0_TASK
/**
 ****************************************************************************************
 * @brief Return if LE Audio Mode 0 is supported or not
 *
 * @return True if supported, False else
 ****************************************************************************************
 */
bool gapm_is_audio_am0_sup(void);
#endif // BLE_AUDIO_AM0_TASK


#if (BLE_EMB_PRESENT && HCI_TL_SUPPORT)
/**
 ****************************************************************************************
 * @brief Retrieve if host is embedded or not
 *
 * @return True if embedded host is enabled, false else.
 ****************************************************************************************
 */
bool gapm_is_embedded_host(void);

/**
 ****************************************************************************************
 * @brief Set if host is embedded or not
 *
 * @param[in] enable True to enable embedded host, false else.
 ****************************************************************************************
 */
void gapm_set_embedded_host(bool enable);
#endif // (BLE_EMB_PRESENT && HCI_TL_SUPPORT)



/**
 ****************************************************************************************
 * @brief Retrieve the device address type (@see enum gapm_addr_type)
 *
 * @return address type
 ****************************************************************************************
 */
uint8_t gapm_get_address_type(void);


#if (BLE_ATTS)

/**
 ****************************************************************************************
 * @brief Get if preferred connection parameters present in GAP ATT database
 *
 * @return True if referred connection parameters present in GAP ATT database, False else
 ****************************************************************************************
 */
bool gapm_is_pref_con_param_pres(void);

/**
 ****************************************************************************************
 * @brief retrieve gap attribute handle from attribute index.
 *
 * @param[in] att_idx Attribute index
 *
 * @return Attribute handle
 ****************************************************************************************
 */
uint16_t gapm_get_att_handle(uint8_t att_idx);

#endif // (BLE_ATTS)

#if (SECURE_CONNECTIONS)
/**
 ****************************************************************************************
 * @brief Returns the local Public Key
 *
 * @return pointer to the local Public Key
 ****************************************************************************************
 */
public_key_t* gapm_get_local_public_key(void);
#endif // (SECURE_CONNECTIONS)

/**
 ****************************************************************************************
 * @brief Retrieve if Legacy pairing is supported on local device
 *
 * @return True if legacy pairing is supported
 ****************************************************************************************
 */
bool gapm_is_legacy_pairing_supp(void);


/**
 ****************************************************************************************
  * @brief Retrieve if Secure Connection pairing is supported on local device
 *
 * @return True if Secure Connection pairing is supported
 ****************************************************************************************
 */
bool gapm_is_sec_con_pairing_supp(void);


#if (BLE_LECB)
/**
 ****************************************************************************************
 * @brief Check if LECB connection can be registered (established)
 *
 * @param[in]  le_psm        LE Protocol/Service Multiplexer
 * @param[in]  conidx        Connection index for app_task computation
 * @param[out] app_task      Destination application/profile task
 * @param[out] sec_lvl       Security level requirements
 *
 *
 * @return GAP_ERR_NOT_FOUND if LE_PSM not register, GAP_ERR_NO_ERROR else
 ****************************************************************************************
 */
uint8_t gapm_le_psm_get_info(uint16_t le_psm, uint8_t conidx, ke_task_id_t *app_task, uint8_t *sec_lvl);


/**
 ****************************************************************************************
 * @brief Check if LECB connection can be registered (established)
 *
 * @param[in] le_psm        LE Protocol/Service Multiplexer
 * @param[in] peer_con_init Info to know if connection is initiated by peer device
 *
 * @return L2C_ERR_NO_RES_AVAIL if all LECB link are established, GAP_ERR_NO_ERROR else
 ****************************************************************************************
 */
uint8_t gapm_lecb_register(uint16_t le_psm, bool peer_con_init);


/**
 ****************************************************************************************
 * @brief Unregister an existing LECB connection
 *
 * @param[in] le_psm        LE Protocol/Service Multiplexer
 * @param[in] peer_con_init Info to know if connection is initiated by peer device
 *
 * @return GAP_ERR_NO_ERROR
 ****************************************************************************************
 */
uint8_t gapm_lecb_unregister(uint16_t le_psm, bool peer_con_init);

#endif // (BLE_LECB)

/**
 ****************************************************************************************
 * @brief Return the maximal MTU value
 *
 * @param[out] Maximal MTU value
 ****************************************************************************************
 */
uint16_t gapm_get_max_mtu(void);
void gapm_set_max_mtu(uint16_t mtu);

/**
 ****************************************************************************************
 * @brief Return the maximal MPS value
 *
 * @param[out] Maximal MPS value
 ****************************************************************************************
 */
uint16_t gapm_get_max_mps(void);



/**
 ****************************************************************************************
 * @brief Check If Service changed feature is enabled or not
 *
 * @return true if enabled, false else.
 *
 ****************************************************************************************
 */
bool gapm_svc_chg_en(void);

#if (BLE_DEBUG)
/**
 ****************************************************************************************
 * @brief Check If Debug mode feature is enabled or not
 *
 * @return true if enabled, false else.
 *
 ****************************************************************************************
 */
bool gapm_dbg_mode_en(void);

/**
 ****************************************************************************************
 * @brief Force the GAP service start handle
 ****************************************************************************************
 */
void gapm_set_svc_start_hdl(uint16_t start_hdl);
#endif // (BLE_DEBUG)

/**
 ****************************************************************************************
 * Retrieve if current connection index is used for a discovery purpose such as
 * Name discovery
 *
 * @param conidx Index of the specific connection
 *
 * @return true if connection has a discovery purpose, False else
 ****************************************************************************************
 */
bool gapm_is_disc_connection(uint8_t conidx);

/// @} GAPM

#endif /* _GAPM_H_ */
