#ifndef __BL808_ISO11898_H__
#define __BL808_ISO11898_H__

#include "iso11898_reg.h"
#include "bl808_common.h"

#define ISO11898_TIMEOUT_MAX     (32 * 1000)

typedef enum {
    ISO11898_FRAME_FORMAT_STANDARD = 0,
    ISO11898_FRAME_FORMAT_EXTENDED,
} ISO11898_FRAME_FORMAT_Type;

typedef enum {
    ISO11898_FRAME_TYPE_DATA = 0,
    ISO11898_FRAME_TYPE_REMOTE,
} ISO11898_FRAME_Type;

typedef enum {
    ISO11898_MODE_TYPE_RESET = 0,
    ISO11898_MODE_TYPE_LISTEN_ONLY,
    ISO11898_MODE_TYPE_SELF_TSET,
    ISO11898_MODE_TYPE_ACCEPTANCE_FILTER,
} ISO11898_MODE_Type;

typedef enum {
    ISO11898_MODE_VALUE_NORMAL = 0,
    ISO11898_MODE_VALUE_RESET = 1,
    ISO11898_MODE_VALUE_LISTEN_ONLY = 1,
    ISO11898_MODE_VALUE_SELF_TSET = 1,
    ISO11898_MODE_VALUE_ACCEPTANCE_FILTER_DUAL = 0,
    ISO11898_MODE_VALUE_ACCEPTANCE_FILTER_SINGLE = 1,
} ISO11898_MODE_VALUE_Type;

typedef enum {
    ISO11898_INT_RECEIVE = 0,
    ISO11898_INT_TRANSMIT,
    ISO11898_INT_ERROR_WARNING,
    ISO11898_INT_OVERRUN,
    ISO11898_INT_RESERVED,
    ISO11898_INT_PASSIVE = 5,
    ISO11898_INT_ARBITRATION_LOST,
    ISO11898_INT_BUS_ERROR,
    ISO11898_INT_ALL,
} ISO11898_INT_Type;

typedef enum {
    ISO11898_STATUS_RECEIVE_BUFFER = 0,
    ISO11898_STATUS_DATA_OVERRUN,
    ISO11898_STATUS_TRANSMIT_BUFFER,
    ISO11898_STATUS_TRANSMISSION_COMPLETE,
    ISO11898_STATUS_RECEIVE,
    ISO11898_STATUS_TRANSMIT,
    ISO11898_STATUS_ERROR,
    ISO11898_STATUS_BUS,
} ISO11898_STATUS_Type;

typedef enum {
    ISO11898_STATUS_RECEIVE_BUFFER_EMPTY = 0,
    ISO11898_STATUS_RECEIVE_BUFFER_NONEMPTY = 1,
    ISO11898_STATUS_DATA_OVERRUN_NULL = 0,
    ISO11898_STATUS_DATA_OVERRUN_EXIST = 1,
    ISO11898_STATUS_TRANSMIT_BUFFER_LOCKED = 0,
    ISO11898_STATUS_TRANSMIT_BUFFER_ACCESSIBLE = 1,
    ISO11898_STATUS_TRANSMISSION_COMPLETE_NOT = 0,
    ISO11898_STATUS_TRANSMISSION_COMPLETE_YES = 1,
    ISO11898_STATUS_RECEIVE_IDLE = 0,
    ISO11898_STATUS_RECEIVE_ONGOING = 1,
    ISO11898_STATUS_TRANSMIT_IDLE = 0,
    ISO11898_STATUS_TRANSMIT_ONGOING = 1,
    ISO11898_STATUS_ERROR_NULL = 0,
    ISO11898_STATUS_ERROR_EXIST = 1,
    ISO11898_STATUS_BUS_ON = 0,
    ISO11898_STATUS_BUS_OFF = 1,
} ISO11898_STATUS_VALUE_Type;

typedef enum {
    ISO11898_ERROR_TYPE_BIT = 0,
    ISO11898_ERROR_TYPE_FORM,
    ISO11898_ERROR_TYPE_STUFF,
    ISO11898_ERROR_TYPE_OTHERS,
} ISO11898_ERROR_CODE_Type;

typedef enum {
    ISO11898_ERROR_DIRECTION_TX = 0,
    ISO11898_ERROR_DIRECTION_RX,
} ISO11898_ERROR_DIRECTION_Type;

typedef enum {
    ISO11898_ERROR_LOCATION_ID28_TO_ID21 = 2,
    ISO11898_ERROR_LOCATION_START_OF_FRAME = 3,
    ISO11898_ERROR_LOCATION_BIT_SRTR = 4,
    ISO11898_ERROR_LOCATION_BIT_IDE = 5,
    ISO11898_ERROR_LOCATION_ID20_TO_ID18 = 6,
    ISO11898_ERROR_LOCATION_ID17_TO_ID13 = 7,
    ISO11898_ERROR_LOCATION_CRC_SEQUENCE = 8,
    ISO11898_ERROR_LOCATION_BIT_RESERVED_0 = 9,
    ISO11898_ERROR_LOCATION_DATA_FIELD = 10,
    ISO11898_ERROR_LOCATION_DATA_LENGTH_CODE = 11,
    ISO11898_ERROR_LOCATION_BIT_RTR = 12,
    ISO11898_ERROR_LOCATION_BIT_RESERVED_1 = 13,
    ISO11898_ERROR_LOCATION_ID4_TO_ID0 = 14,
    ISO11898_ERROR_LOCATION_ID12_TO_ID15 = 15,
    ISO11898_ERROR_LOCATION_ACTIVE_ERROR_FLAG = 17,
    ISO11898_ERROR_LOCATION_INTERMISSION = 18,
    ISO11898_ERROR_LOCATION_BIT_TOLERATE_DOMINANT = 19,
    ISO11898_ERROR_LOCATION_PASSIVE_ERROR_FLAG = 22,
    ISO11898_ERROR_LOCATION_ERROR_DELIMITER = 23,
    ISO11898_ERROR_LOCATION_CRC_DELIMITER = 24,
    ISO11898_ERROR_LOCATION_ACK_SLOT = 25,
    ISO11898_ERROR_LOCATION_END_OF_FRAME = 26,
    ISO11898_ERROR_LOCATION_ACK_DELIMITER = 27,
    ISO11898_ERROR_LOCATION_OVERLOAD_FLAG = 28,
} ISO11898_ERROR_LOCATION_Type;

typedef enum {
    ISO11898_FILTER_REGISTER_ACR0 = 0,
    ISO11898_FILTER_REGISTER_ACR1,
    ISO11898_FILTER_REGISTER_ACR2,
    ISO11898_FILTER_REGISTER_ACR3,
    ISO11898_FILTER_REGISTER_AMR0,
    ISO11898_FILTER_REGISTER_AMR1,
    ISO11898_FILTER_REGISTER_AMR2,
    ISO11898_FILTER_REGISTER_AMR3,
} ISO11898_FILTER_REGISTER_Type;

typedef struct {
    ISO11898_ERROR_CODE_Type code;
    ISO11898_ERROR_DIRECTION_Type dir;
    ISO11898_ERROR_LOCATION_Type location;
} ISO11898_ERROR_Type;

typedef struct {
    ISO11898_FRAME_FORMAT_Type formatType;
    ISO11898_MODE_VALUE_Type filterMode;
    ISO11898_FRAME_Type matchRtr1;
    ISO11898_FRAME_Type matchRtr2;
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
} ISO11898_FILTER_CFG_Type;

typedef struct {
    ISO11898_FRAME_Type frameType;
    ISO11898_FRAME_FORMAT_Type frameFormat;
    uint8_t dataLen;
    uint8_t *dataAddr;
    uint32_t id;
    uint32_t timeout;
} ISO11898_CFG_Type;

#define IS_ISO11898_FRAME_FORMAT_TYPE(type)              (((type) == ISO11898_FRAME_FORMAT_STANDARD) || \
                                                          ((type) == ISO11898_FRAME_FORMAT_EXTENDED))

#define IS_ISO11898_FRAME_TYPE(type)                     (((type) == ISO11898_FRAME_TYPE_DATA) || \
                                                          ((type) == ISO11898_FRAME_TYPE_REMOTE))

#define IS_ISO11898_MODE_TYPE(type)                      (((type) == ISO11898_MODE_TYPE_RESET) || \
                                                          ((type) == ISO11898_MODE_TYPE_LISTEN_ONLY) || \
                                                          ((type) == ISO11898_MODE_TYPE_SELF_TSET) || \
                                                          ((type) == ISO11898_MODE_TYPE_ACCEPTANCE_FILTER) || \

#define IS_ISO11898_MODE_VALUE_TYPE(type)                (((type) == ISO11898_MODE_VALUE_NORMAL) || \
                                                          ((type) == ISO11898_MODE_VALUE_RESET) || \
                                                          ((type) == ISO11898_MODE_VALUE_LISTEN_ONLY) || \
                                                          ((type) == ISO11898_MODE_VALUE_SELF_TSET) || \
                                                          ((type) == ISO11898_MODE_VALUE_ACCEPTANCE_FILTER_DUAL) || \
                                                          ((type) == ISO11898_MODE_VALUE_ACCEPTANCE_FILTER_SINGLE) || \

#define IS_ISO11898_INT_TYPE(type)                       (((type) == ISO11898_INT_RECEIVE) || \
                                                          ((type) == ISO11898_INT_TRANSMIT) || \
                                                          ((type) == ISO11898_INT_ERROR_WARNING) || \
                                                          ((type) == ISO11898_INT_OVERRUN) || \
                                                          ((type) == ISO11898_INT_PASSIVE) || \
                                                          ((type) == ISO11898_INT_ARBITRATION_LOST) || \
                                                          ((type) == ISO11898_INT_BUSERROR) || \
                                                          ((type) == ISO11898_INT_ALL))

#define IS_ISO11898_STATUS_TYPE(type)                    (((type) == ISO11898_STATUS_RECEIVE_BUFFER) || \
                                                          ((type) == ISO11898_STATUS_DATA_OVERRUN) || \
                                                          ((type) == ISO11898_STATUS_TRANSMIT_BUFFER) || \
                                                          ((type) == ISO11898_STATUS_TRANSMISSION_COMPLETE) || \
                                                          ((type) == ISO11898_STATUS_RECEIVE) || \
                                                          ((type) == ISO11898_STATUS_TRANSMIT) || \
                                                          ((type) == ISO11898_STATUS_ERROR) || \
                                                          ((type) == ISO11898_STATUS_BUS))

#define IS_ISO11898_STATUS_VALUE_TYPE(type)              (((type) == ISO11898_STATUS_VALUE_RECEIVE_BUFFER_EMPTY || \
                                                          ((type) == ISO11898_STATUS_VALUE_RECEIVE_BUFFER_NONEMPTY || \
                                                          ((type) == ISO11898_STATUS_VALUE_DATA_OVERRUN_NULL || \
                                                          ((type) == ISO11898_STATUS_VALUE_DATA_OVERRUN_EXIST || \
                                                          ((type) == ISO11898_STATUS_VALUE_TRANSMIT_BUFFER_LOCKED || \
                                                          ((type) == ISO11898_STATUS_VALUE_TRANSMIT_BUFFER_ACCESSIBLE || \
                                                          ((type) == ISO11898_STATUS_VALUE_TRANSMISSION_COMPLETE_NOT || \
                                                          ((type) == ISO11898_STATUS_VALUE_TRANSMISSION_COMPLETE_YES || \
                                                          ((type) == ISO11898_STATUS_VALUE_RECEIVE_IDLE || \
                                                          ((type) == ISO11898_STATUS_VALUE_RECEIVE_ONGOING || \
                                                          ((type) == ISO11898_STATUS_VALUE_TRANSMIT_IDLE || \
                                                          ((type) == ISO11898_STATUS_VALUE_TRANSMIT_ONGOING || \
                                                          ((type) == ISO11898_STATUS_VALUE_ERROR_NULL || \
                                                          ((type) == ISO11898_STATUS_VALUE_ERROR_EXIST || \
                                                          ((type) == ISO11898_STATUS_VALUE_BUS_ON || \
                                                          ((type) == ISO11898_STATUS_VALUE_BUS_OFF))

void ISO11898_Init(void);
void ISO11898_Mode_Set(ISO11898_MODE_Type type, ISO11898_MODE_VALUE_Type value);
ISO11898_MODE_VALUE_Type ISO11898_Mode_Get(ISO11898_MODE_Type type);
void ISO11898_Int_Enable(ISO11898_INT_Type intType, BL_Fun_Type enable);
void ISO11898_Cmd_Request_Transmit(void);
void ISO11898_Cmd_Abort_Transmit(void);
void ISO11898_Cmd_Release_Recv_Buff(void);
void ISO11898_Cmd_Clear_Data_Overrun(void);
void ISO11898_Cmd_Request_Self_Reception(void);
ISO11898_STATUS_VALUE_Type ISO11898_Status_Get(ISO11898_STATUS_Type type);
uint8_t ISO11898_Arbitration_Lost_Position_Get(void);
void ISO11898_Error_Get(ISO11898_ERROR_Type *const code);
BL_Err_Type ISO11898_Error_Warning_Limit_Set(uint8_t limit);
uint8_t ISO11898_Error_Warning_Limit_Get(void);
uint8_t ISO11898_Error_Rx_Counter_Get(void);
uint8_t ISO11898_Error_Tx_Counter_Get(void);
BL_Err_Type ISO11898_Transmit(const ISO11898_CFG_Type *cfg);
BL_Err_Type ISO11898_Receive(ISO11898_CFG_Type *cfg);
uint8_t ISO11898_Receive_Buff_Frame_Count_Get(void);
BL_Err_Type ISO11898_Clock_Div_Set(uint8_t div);
uint8_t ISO11898_Clock_Div_Get(void);
BL_Err_Type ISO11898_Synchronization_Jump_Width_Set(uint8_t width);
uint8_t ISO11898_Synchronization_Jump_Width_Get(void);
BL_Err_Type ISO11898_Sample_Parameter_Set(uint8_t num, uint8_t head, uint8_t tail);
void ISO11898_Sample_Parameter_Get(uint8_t *num, uint8_t *head, uint8_t *tail);
void ISO11898_Filter_Set(const ISO11898_FILTER_CFG_Type *cfg);
void ISO11898_Filter_Register_Set(ISO11898_FILTER_REGISTER_Type reg, uint8_t value);
void ISO11898_Filter_Registers_Set(uint8_t *valueArr);

BL_Err_Type ISO11898_Int_Callback_Install(ISO11898_INT_Type intType, intCallback_Type *cbFun);
#endif /* __BL606p_ISO11898_H__ */
