#ifndef __BL808_CAN_H__
#define __BL808_CAN_H__

#include "can_reg.h"
#include "bl808_common.h"

#define CAN_BASE            CAN_FD_BASE
#define CAN_TIMEOUT_MAX     (32 * 1000)

typedef enum {
    CAN_FRAME_FORMAT_STANDARD = 0,
    CAN_FRAME_FORMAT_EXTENDED,
}CAN_FRAME_FORMAT_Type;

typedef enum {
    CAN_FRAME_TYPE_DATA = 0,
    CAN_FRAME_TYPE_REMOTE,
}CAN_FRAME_Type;

typedef enum {
    CAN_MODE_TYPE_RESET = 0,
    CAN_MODE_TYPE_LISTEN_ONLY,
    CAN_MODE_TYPE_SELF_TSET,
    CAN_MODE_TYPE_ACCEPTANCE_FILTER,
}CAN_MODE_Type;

typedef enum
{
    CAN_MODE_VALUE_NORMAL = 0,
    CAN_MODE_VALUE_RESET = 1,
    CAN_MODE_VALUE_LISTEN_ONLY = 1,
    CAN_MODE_VALUE_SELF_TSET = 1,
    CAN_MODE_VALUE_ACCEPTANCE_FILTER_DUAL = 0,
    CAN_MODE_VALUE_ACCEPTANCE_FILTER_SINGLE = 1,
} CAN_MODE_VALUE_Type;

typedef enum {
    CAN_INT_RECEIVE = 0,
    CAN_INT_TRANSMIT,
    CAN_INT_ERROR_WARNING,
    CAN_INT_OVERRUN,
    CAN_INT_RESERVED,
    CAN_INT_PASSIVE = 5,
    CAN_INT_ARBITRATION_LOST,
    CAN_INT_BUS_ERROR,
    CAN_INT_ALL,
}CAN_INT_Type;

typedef enum {
    CAN_STATUS_RECEIVE_BUFFER = 0,
    CAN_STATUS_DATA_OVERRUN,
    CAN_STATUS_TRANSMIT_BUFFER,
    CAN_STATUS_TRANSMISSION_COMPLETE,
    CAN_STATUS_RECEIVE,
    CAN_STATUS_TRANSMIT,
    CAN_STATUS_ERROR,
    CAN_STATUS_BUS,
}CAN_STATUS_Type;

typedef enum {
    CAN_STATUS_RECEIVE_BUFFER_EMPTY = 0,
    CAN_STATUS_RECEIVE_BUFFER_NONEMPTY = 1,
    CAN_STATUS_DATA_OVERRUN_NULL = 0,
    CAN_STATUS_DATA_OVERRUN_EXIST = 1,
    CAN_STATUS_TRANSMIT_BUFFER_LOCKED = 0,
    CAN_STATUS_TRANSMIT_BUFFER_ACCESSIBLE = 1,
    CAN_STATUS_TRANSMISSION_COMPLETE_NOT = 0,
    CAN_STATUS_TRANSMISSION_COMPLETE_YES = 1,
    CAN_STATUS_RECEIVE_IDLE = 0,
    CAN_STATUS_RECEIVE_ONGOING = 1,
    CAN_STATUS_TRANSMIT_IDLE = 0,
    CAN_STATUS_TRANSMIT_ONGOING = 1,
    CAN_STATUS_ERROR_NULL = 0,
    CAN_STATUS_ERROR_EXIST = 1,
    CAN_STATUS_BUS_ON = 0,
    CAN_STATUS_BUS_OFF = 1,
}CAN_STATUS_VALUE_Type;

typedef enum {
    CAN_ERROR_TYPE_BIT = 0,
    CAN_ERROR_TYPE_FORM,
    CAN_ERROR_TYPE_STUFF,
    CAN_ERROR_TYPE_OTHERS,
}CAN_ERROR_CODE_Type;

typedef enum {
    CAN_ERROR_DIRECTION_TX = 0,
    CAN_ERROR_DIRECTION_RX,
}CAN_ERROR_DIRECTION_Type;

typedef enum {
    CAN_ERROR_LOCATION_ID28_TO_ID21 = 2,
    CAN_ERROR_LOCATION_START_OF_FRAME = 3,
    CAN_ERROR_LOCATION_BIT_SRTR = 4,
    CAN_ERROR_LOCATION_BIT_IDE = 5,
    CAN_ERROR_LOCATION_ID20_TO_ID18 = 6,
    CAN_ERROR_LOCATION_ID17_TO_ID13 = 7,
    CAN_ERROR_LOCATION_CRC_SEQUENCE = 8,
    CAN_ERROR_LOCATION_BIT_RESERVED_0 = 9,
    CAN_ERROR_LOCATION_DATA_FIELD = 10,
    CAN_ERROR_LOCATION_DATA_LENGTH_CODE = 11,
    CAN_ERROR_LOCATION_BIT_RTR = 12,
    CAN_ERROR_LOCATION_BIT_RESERVED_1 = 13,
    CAN_ERROR_LOCATION_ID4_TO_ID0 = 14,
    CAN_ERROR_LOCATION_ID12_TO_ID15 = 15,
    CAN_ERROR_LOCATION_ACTIVE_ERROR_FLAG = 17,
    CAN_ERROR_LOCATION_INTERMISSION = 18,
    CAN_ERROR_LOCATION_BIT_TOLERATE_DOMINANT = 19,
    CAN_ERROR_LOCATION_PASSIVE_ERROR_FLAG = 22,
    CAN_ERROR_LOCATION_ERROR_DELIMITER = 23,
    CAN_ERROR_LOCATION_CRC_DELIMITER = 24,
    CAN_ERROR_LOCATION_ACK_SLOT = 25,
    CAN_ERROR_LOCATION_END_OF_FRAME = 26,
    CAN_ERROR_LOCATION_ACK_DELIMITER = 27,
    CAN_ERROR_LOCATION_OVERLOAD_FLAG = 28,
} CAN_ERROR_LOCATION_Type;

typedef enum {
    CAN_FILTER_REGISTER_ACR0 = 0,
    CAN_FILTER_REGISTER_ACR1,
    CAN_FILTER_REGISTER_ACR2,
    CAN_FILTER_REGISTER_ACR3,
    CAN_FILTER_REGISTER_AMR0,
    CAN_FILTER_REGISTER_AMR1,
    CAN_FILTER_REGISTER_AMR2,
    CAN_FILTER_REGISTER_AMR3,
} CAN_FILTER_REGISTER_Type;

typedef struct {
    CAN_ERROR_CODE_Type code;
    CAN_ERROR_DIRECTION_Type dir;
    CAN_ERROR_LOCATION_Type location;
} CAN_ERROR_Type;

typedef struct {
    CAN_FRAME_FORMAT_Type formatType;
    CAN_MODE_VALUE_Type filterMode;
    CAN_FRAME_Type matchRtr1;
    CAN_FRAME_Type matchRtr2;
    uint8_t matchData1;
    uint8_t matchData2;
    uint32_t matchId1;
    uint32_t matchId2;
    BL_Mask_Type maskRtr1;
    BL_Mask_Type maskRtr2;
    uint8_t maskData1;
    uint8_t maskData2;
    uint32_t maskId1;
    uint32_t maskId2;
}CAN_FILTER_CFG_Type;

typedef struct {
    CAN_FRAME_Type frameType;
    CAN_FRAME_FORMAT_Type frameFormat;
    uint8_t dataLen;
    uint8_t *dataAddr;
    uint32_t id;
    uint32_t timeout;
}CAN_CFG_Type;

#define IS_CAN_FRAME_FORMAT_TYPE(type)                   (((type) == CAN_FRAME_FORMAT_STANDARD) || \
                                                          ((type) == CAN_FRAME_FORMAT_EXTENDED))

#define IS_CAN_FRAME_TYPE(type)                          (((type) == CAN_FRAME_TYPE_DATA) || \
                                                          ((type) == CAN_FRAME_TYPE_REMOTE))

#define IS_CAN_MODE_TYPE(type)                           (((type) == CAN_MODE_TYPE_RESET) || \
                                                          ((type) == CAN_MODE_TYPE_LISTEN_ONLY) || \
                                                          ((type) == CAN_MODE_TYPE_SELF_TSET) || \
                                                          ((type) == CAN_MODE_TYPE_ACCEPTANCE_FILTER) || \

#define IS_CAN_MODE_VALUE_TYPE(type)                     (((type) == CAN_MODE_VALUE_NORMAL) || \
                                                          ((type) == CAN_MODE_VALUE_RESET) || \
                                                          ((type) == CAN_MODE_VALUE_LISTEN_ONLY) || \
                                                          ((type) == CAN_MODE_VALUE_SELF_TSET) || \
                                                          ((type) == CAN_MODE_VALUE_ACCEPTANCE_FILTER_DUAL) || \
                                                          ((type) == CAN_MODE_VALUE_ACCEPTANCE_FILTER_SINGLE) || \

#define IS_CAN_INT_TYPE(type)                            (((type) == CAN_INT_RECEIVE) || \
                                                          ((type) == CAN_INT_TRANSMIT) || \
                                                          ((type) == CAN_INT_ERROR_WARNING) || \
                                                          ((type) == CAN_INT_OVERRUN) || \
                                                          ((type) == CAN_INT_PASSIVE) || \
                                                          ((type) == CAN_INT_ARBITRATION_LOST) || \
                                                          ((type) == CAN_INT_BUSERROR) || \
                                                          ((type) == CAN_INT_ALL))

#define IS_CAN_STATUS_TYPE(type)                         (((type) == CAN_STATUS_RECEIVE_BUFFER) || \
                                                          ((type) == CAN_STATUS_DATA_OVERRUN) || \
                                                          ((type) == CAN_STATUS_TRANSMIT_BUFFER) || \
                                                          ((type) == CAN_STATUS_TRANSMISSION_COMPLETE) || \
                                                          ((type) == CAN_STATUS_RECEIVE) || \
                                                          ((type) == CAN_STATUS_TRANSMIT) || \
                                                          ((type) == CAN_STATUS_ERROR) || \
                                                          ((type) == CAN_STATUS_BUS))

#define IS_CAN_STATUS_VALUE_TYPE(type)                   (((type) == CAN_STATUS_VALUE_RECEIVE_BUFFER_EMPTY || \
                                                          ((type) == CAN_STATUS_VALUE_RECEIVE_BUFFER_NONEMPTY || \
                                                          ((type) == CAN_STATUS_VALUE_DATA_OVERRUN_NULL || \
                                                          ((type) == CAN_STATUS_VALUE_DATA_OVERRUN_EXIST || \
                                                          ((type) == CAN_STATUS_VALUE_TRANSMIT_BUFFER_LOCKED || \
                                                          ((type) == CAN_STATUS_VALUE_TRANSMIT_BUFFER_ACCESSIBLE || \
                                                          ((type) == CAN_STATUS_VALUE_TRANSMISSION_COMPLETE_NOT || \
                                                          ((type) == CAN_STATUS_VALUE_TRANSMISSION_COMPLETE_YES || \
                                                          ((type) == CAN_STATUS_VALUE_RECEIVE_IDLE || \
                                                          ((type) == CAN_STATUS_VALUE_RECEIVE_ONGOING || \
                                                          ((type) == CAN_STATUS_VALUE_TRANSMIT_IDLE || \
                                                          ((type) == CAN_STATUS_VALUE_TRANSMIT_ONGOING || \
                                                          ((type) == CAN_STATUS_VALUE_ERROR_NULL || \
                                                          ((type) == CAN_STATUS_VALUE_ERROR_EXIST || \
                                                          ((type) == CAN_STATUS_VALUE_BUS_ON || \
                                                          ((type) == CAN_STATUS_VALUE_BUS_OFF))

void CAN_Init(void);
void CAN_Mode_Set(CAN_MODE_Type type, CAN_MODE_VALUE_Type value);
CAN_MODE_VALUE_Type CAN_Mode_Get(CAN_MODE_Type type);
void CAN_Int_Enable(CAN_INT_Type intType, BL_Fun_Type enable);
void CAN_Cmd_Request_Transmit(void);
void CAN_Cmd_Abort_Transmit(void);
void CAN_Cmd_Release_Recv_Buff(void);
void CAN_Cmd_Clear_Data_Overrun(void);
void CAN_Cmd_Request_Self_Reception(void);
CAN_STATUS_VALUE_Type CAN_Status_Get(CAN_STATUS_Type type);
uint8_t CAN_Arbitration_Lost_Position_Get(void);
void CAN_Error_Get(CAN_ERROR_Type *const code);
BL_Err_Type CAN_Error_Warning_Limit_Set(uint8_t limit);
uint8_t CAN_Error_Warning_Limit_Get(void);
uint8_t CAN_Error_Rx_Counter_Get(void);
uint8_t CAN_Error_Tx_Counter_Get(void);
BL_Err_Type CAN_Transmit(const CAN_CFG_Type *cfg);
BL_Err_Type CAN_Receive(CAN_CFG_Type *cfg);
uint8_t CAN_Receive_Buff_Frame_Count_Get(void);
BL_Err_Type CAN_Clock_Div_Set(uint8_t div);
uint8_t CAN_Clock_Div_Get(void);
BL_Err_Type CAN_Synchronization_Jump_Width_Set(uint8_t width);
uint8_t CAN_Synchronization_Jump_Width_Get(void);
BL_Err_Type CAN_Sample_Parameter_Set(uint8_t num, uint8_t head, uint8_t tail);
void CAN_Sample_Parameter_Get(uint8_t *num, uint8_t *head, uint8_t *tail);
void CAN_Filter_Set(const CAN_FILTER_CFG_Type *cfg);
void CAN_Filter_Register_Set(CAN_FILTER_REGISTER_Type reg, uint8_t value);
void CAN_Filter_Registers_Set(uint8_t *valueArr);

BL_Err_Type CAN_Int_Callback_Install(CAN_INT_Type intType, intCallback_Type *cbFun);
#endif /* __BL606p_CAN_H__ */
