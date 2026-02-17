/**
 ****************************************************************************************
 *
 * @file prf_utils.h
 *
 * @brief  Header file - Profile Utilities
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */


#ifndef _PRF_UTILS_H_
#define _PRF_UTILS_H_

/**
 ****************************************************************************************
 * @addtogroup PRF_UTILS
 * @ingroup PROFILE
 *
 * @brief Definitions of shared profiles functions that can be used by several profiles
 *
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"
#if (BLE_SERVER_PRF || BLE_CLIENT_PRF)
#include "ke_msg.h"
#include "prf_types.h"
#include "gattc_task.h"
#include "gapc.h"
#include "gapc_task.h"
#include "attm.h"
#include "prf.h"
#endif /* (BLE_SERVER_PRF || BLE_CLIENT_PRF) */

/*
 * MACROS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Macro used to called the prf_client_get_env function.
 *
 * @param prf_id    Profile Task ID   (In Upper case, ex: HTPC, DISC, ...)
 * @param type      Profile task type (In lower case, ex: htpc, disc, ...)
 ****************************************************************************************
 */
#define PRF_ENV_GET(prf_id, type) \
        ((struct type ## _env_tag *)prf_env_get((TASK_ID_##prf_id)))





/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

#if (BLE_BATT_SERVER)
/**
 ****************************************************************************************
 * @brief Pack Characteristic Presentation Format descriptor value
 ****************************************************************************************
 */
void prf_pack_char_pres_fmt(uint8_t *packed_val, const struct prf_char_pres_fmt* char_pres_fmt);
#endif // (BLE_BATT_SERVER)

#if (BLE_BATT_CLIENT)
/**
 ****************************************************************************************
 * @brief Unpack Characteristic Presentation Format descriptor value
 ****************************************************************************************
 */
void prf_unpack_char_pres_fmt(const uint8_t *packed_val, struct prf_char_pres_fmt* char_pres_fmt);
#endif // (BLE_BATT_CLIENT)

#if (BLE_CLIENT_PRF)
/**
 ****************************************************************************************
 * @brief Request  peer device to read an attribute
 *
 * @param[in] prf_env Pointer to profile information
 *
 * @param conidx   Connection index
 * @param shdl     Search Start Handle
 * @param ehdl     Search End Handle
 *
 * @param valhdl   Value Handle
 *
 * @note: if attribute is invalid, nothing is registered
 ****************************************************************************************
 */
void prf_read_char_send(prf_env_t *prf_env, uint8_t conidx,
                        uint16_t shdl, uint16_t ehdl, uint16_t valhdl);


/**
 ****************************************************************************************
 * @brief register attribute handle in GATT
 *
 * @param[in] prf_env Pointer to profile information
 *
 * @param conidx   Connection index
 * @param svc   Service to register
 *
 * @note: if attribute is invalid, nothing is registered
 ****************************************************************************************
 */
void prf_register_atthdl2gatt(prf_env_t *prf_env, uint8_t conidx, struct prf_svc *svc);

/**
 ****************************************************************************************
 * @brief Unregister attribute handle in GATT
 *
 * @param[in] prf_env Pointer to profile information
 *
 * @param conidx   Connection index
 * @param svc   Service to register
 *
 * @note: if attribute is invalid, nothing is registered
 ****************************************************************************************
 */
void prf_unregister_atthdl2gatt(prf_env_t *prf_env, uint8_t conidx, struct prf_svc *svc);

/**
 ****************************************************************************************
 * @brief Request service discovery on peer device.
 *
 * This request will be used to retrieve start and end handles of the service.
 *
 * @param[in] prf_env Pointer to profile information
 *
 * @param conidx   Connection index
 * @param uuid     Service UUID
 ****************************************************************************************
 */
void prf_disc_svc_send(prf_env_t *prf_env,uint8_t conidx,  uint16_t uuid);


/**
 ****************************************************************************************
 * @brief Write peer characteristic using GATT.
 *
 * It will request write modification of peer handle
 *
 * @param[in] prf_env Pointer to profile information
 * @param[in] conidx   Connection index
 * @param[in] handle Peer handle to modify
 * @param[in] value  New Peer handle value
 * @param[in] length Value length
 ****************************************************************************************
 */
void prf_gatt_write(prf_env_t *prf_env, uint8_t conidx,
                    uint16_t handle, uint8_t* value, uint16_t length, uint8_t operation);

/**
 ****************************************************************************************
 * @brief Modify peer client configuration descriptor using GATT
 *
 * It will request write modification of peer client configuration descriptor handle
 *
 * @param[in] prf_env Pointer to profile information
 *
 * @param[in] conidx   Connection index
 * @param[in] handle Peer client configuration descriptor handle to modify
 *
 * @param[in] ntf_ind_cfg  Indication/Notification configuration
 ****************************************************************************************
 */
void prf_gatt_write_ntf_ind(prf_env_t *prf_env, uint8_t conidx, uint16_t handle,
        uint16_t ntf_ind_cfg);

/**
 ****************************************************************************************
 * @brief Check service characteristic validity
 *
 * For each characteristic in service it verifies handles.
 *
 * If some handles are not present, it checks if they shall be present or they are optional.
 *
 * @param nb_chars   Number of Characteristics in the service
 * @param chars      Characteristics values (char handles, val handles, properties)
 * @param chars_req  Characteristics requirements.
 *
 * @return 0x1 if service is valid, 0x00 else.
 ****************************************************************************************
 */
uint8_t prf_check_svc_char_validity(uint8_t nb_chars,
                                    const struct prf_char_inf* chars,
                                    const struct prf_char_def* chars_req);

/**
 ****************************************************************************************
 * @brief Check service characteristic validity
 *
 * For each characteristic in service it verifies handles.
 *
 * If some handles are not present, it checks if they shall be present or they are optional.
 *
 * @param nb_chars   Number of Characteristics in the service
 * @param chars      Characteristics values (char handles, val handles, properties)
 * @param chars_req  Characteristics requirements.
 *
 * @return 0x1 if service is valid, 0x00 else.
 ****************************************************************************************
 */
uint8_t prf_check_svc_char_uuid128_validity(uint8_t nb_chars,
                                    const struct prf_char_inf* chars,
                                    const struct prf_char_uuid128_def* chars_req);

/**
 ****************************************************************************************
 * @brief Check service characteristic descriptors validity
 *
 * For each characteristic descriptors in service it verifies handles.
 *
 * If some handles are not present, according to characteristic properties it verify if
 * descriptor is optional or not.
 *
 * @param descs_size Number of Characteristic descriptors in the service
 * @param descs      Characteristic descriptors values (handles)
 * @param descs_req  Characteristics descriptors requirements.
 *
 * @return 0x1 if service is valid, 0x00 else.
 ****************************************************************************************
 */
uint8_t prf_check_svc_char_desc_validity(uint8_t descs_size,
                                        const struct prf_char_desc_inf* descs,
                                        const struct prf_char_desc_def* descs_req,
                                        const struct prf_char_inf* chars);

/**
 ****************************************************************************************
 * @brief Check service characteristic descriptors validity
 *
 * For each characteristic descriptors in service it verifies handles.
 *
 * If some handles are not present, according to characteristic properties it verify if
 * descriptor is optional or not.
 *
 * @param descs_size Number of Characteristic descriptors in the service
 * @param descs      Characteristic descriptors values (handles)
 * @param descs_req  Characteristics descriptors requirements.
 *
 * @return 0x1 if service is valid, 0x00 else.
 ****************************************************************************************
 */
uint8_t prf_check_svc_char_desc_uuid128_validity(uint8_t descs_size,
                                        const struct prf_char_desc_inf* descs,
                                        const struct prf_char_desc_uuid128_def* descs_req,
                                        const struct prf_char_inf* chars);

/**
 ****************************************************************************************
 * @brief Extract information of the service according to the service description
 *
 * @param param            Service information
 * @param nb_chars         Length of provided arrays (chars and chars_req)
 * @param chars_req        Characteristics requirements
 * @param chars            Characteristics
 * @param nb_descs         Length of provided arrays (descs and descs_req)
 * @param descs_req        Descriptors requirements
 * @param descs            Descriptors
 ****************************************************************************************
 */
void prf_extract_svc_info(const struct gattc_sdp_svc_ind* param,
        uint8_t nb_chars, const struct prf_char_def* chars_req, struct prf_char_inf* chars,
        uint8_t nb_descs, const struct prf_char_desc_def* descs_req, struct prf_char_desc_inf* descs);

/**
 ****************************************************************************************
 * @brief Extract information of the service according to the service description
 *
 * @param param            Service information
 * @param nb_chars         Length of provided arrays (chars and chars_req)
 * @param chars_req        Characteristics requirements in UUID128 format
 * @param chars            Characteristics
 * @param nb_descs         Length of provided arrays (descs and descs_req)
 * @param descs_req        Descriptors requirements in UUID128 format
 * @param descs            Descriptors
 ****************************************************************************************
 */
void prf_extract_svc_uuid128_info(const struct gattc_sdp_svc_ind* param,
        uint8_t nb_chars, const struct prf_char_uuid128_def* chars_uuid128_req, struct prf_char_inf* chars,
        uint8_t nb_descs, const struct prf_char_desc_uuid128_def* descs_uuid128_req, struct prf_char_desc_inf* descs);

#endif //(BLE_CLIENT_PRF)


#if (BLE_CLIENT_PRF || BLE_TIP_SERVER || BLE_AN_SERVER || BLE_PAS_SERVER)

/**
 ****************************************************************************************
 * @brief The function is used to send information about peer attribute value
 *
 * @param[in] prf_env       Pointer to the profile environment variable
 * @param[in] conidx        Connection index
 * @param[in] msg_id        Profile message ID to trigger
 * @param[in] status        Response status code
 * @param[in] read_ind      GATT read message indication
 ****************************************************************************************
 */
void prf_client_att_info_rsp(prf_env_t *prf_env, uint8_t conidx, uint16_t msg_id,
                             uint8_t status, struct gattc_read_ind const* read_ind);

#endif //(BLE_CLIENT_PRF || BLE_TIP_SERVER || BLE_AN_SERVER || BLE_PAS_SERVER)

#if (BLE_SERVER_PRF || BLE_CLIENT_PRF)
/**
 ****************************************************************************************
 * @brief Pack date time value
 *
 * @param[out] packed_date packed date time
 * @param[in] date_time structure date time
 *
 * @return size of packed value
 ****************************************************************************************
 */
uint8_t prf_pack_date_time(uint8_t *packed_date, const struct prf_date_time* date_time);

/**
 ****************************************************************************************
 * @brief Unpack date time value
 *
 * @param[in] packed_date packed date time
 * @param[out] date_time structure date time
 *
 * @return size of packed value
 ****************************************************************************************
 */
uint8_t prf_unpack_date_time(uint8_t *packed_date, struct prf_date_time* date_time);

#endif /* (BLE_SERVER_PRF || BLE_CLIENT_PRF) */

/// @} prf_utils

#endif /* _PRF_UTILS_H_ */
