/*
 * Copyright (C) 2021 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 */

#ifndef __ES_CONF_INFO_UART_H__
#define __ES_CONF_INFO_UART_H__

#define ES_C_UART_PARITY_NONE        ALD_UART_PARITY_NONE
#define ES_C_UART_PARITY_ODD         ALD_UART_PARITY_ODD
#define ES_C_UART_PARITY_EVEN        ALD_UART_PARITY_EVEN

#define ES_C_UART_STOP_1          ALD_UART_STOP_BITS_1
#define ES_C_UART_STOP_2          ALD_UART_STOP_BITS_2


/* UART 配置 */




#ifndef  ES_DEVICE_NAME_EUART0
#define  ES_DEVICE_NAME_EUART0     "euart0"
#endif
#ifndef  ES_DEVICE_NAME_EUART1
#define  ES_DEVICE_NAME_EUART1     "euart1"
#endif
#ifndef  ES_DEVICE_NAME_CUART0
#define  ES_DEVICE_NAME_CUART0     "cuart0"
#endif
#ifndef  ES_DEVICE_NAME_CUART1
#define  ES_DEVICE_NAME_CUART1     "cuart1"
#endif
#ifndef  ES_DEVICE_NAME_CUART2
#define  ES_DEVICE_NAME_CUART2     "cuart2"
#endif


#ifndef ES_CONF_CUART0_BAUD_RATE
#define ES_CONF_CUART0_BAUD_RATE         115200
#endif
#ifndef ES_CONF_CUART0_PARITY
#define ES_CONF_CUART0_PARITY         ES_C_UART_PARITY_NONE
#endif
#ifndef ES_CONF_CUART0_STOP_BITS
#define ES_CONF_CUART0_STOP_BITS        ES_C_UART_STOP_1
#endif

#ifndef ES_CONF_CUART1_BAUD_RATE
#define ES_CONF_CUART1_BAUD_RATE         115200
#endif
#ifndef ES_CONF_CUART1_PARITY
#define ES_CONF_CUART1_PARITY         ES_C_UART_PARITY_NONE
#endif
#ifndef ES_CONF_CUART1_STOP_BITS
#define ES_CONF_CUART1_STOP_BITS        ES_C_UART_STOP_1
#endif

#ifndef ES_CONF_CUART0_BAUD_RATE
#define ES_CONF_CUART0_BAUD_RATE         115200
#endif
#ifndef ES_CONF_CUART0_PARITY
#define ES_CONF_CUART0_PARITY         ES_C_UART_PARITY_NONE
#endif
#ifndef ES_CONF_CUART0_STOP_BITS
#define ES_CONF_CUART0_STOP_BITS        ES_C_UART_STOP_1
#endif

#ifndef ES_CONF_CUART1_BAUD_RATE
#define ES_CONF_CUART1_BAUD_RATE         115200
#endif
#ifndef ES_CONF_CUART1_PARITY
#define ES_CONF_CUART1_PARITY         ES_C_UART_PARITY_NONE
#endif
#ifndef ES_CONF_CUART1_STOP_BITS
#define ES_CONF_CUART1_STOP_BITS        ES_C_UART_STOP_1
#endif

#ifndef ES_CONF_CUART2_BAUD_RATE
#define ES_CONF_CUART2_BAUD_RATE         115200
#endif
#ifndef ES_CONF_CUART2_PARITY
#define ES_CONF_CUART2_PARITY         ES_C_UART_PARITY_NONE
#endif
#ifndef ES_CONF_CUART2_STOP_BITS
#define ES_CONF_CUART2_STOP_BITS        ES_C_UART_STOP_1
#endif


#define ES_EUART0_CONFIG                         \
{                                               \
    ES_CONF_EUART0_BAUD_RATE,                           \
    DATA_BITS_8,                                \
    ES_CONF_EUART0_STOP_BITS,                                \
    ES_CONF_EUART0_PARITY,                                \
    BIT_ORDER_LSB,                              \
    NRZ_NORMAL,                                 \
    RT_SERIAL_RB_BUFSZ,                         \
    0                                           \
}


#define ES_EUART1_CONFIG                         \
{                                               \
    ES_CONF_EUART1_BAUD_RATE,                           \
    DATA_BITS_8,                                \
    ES_CONF_EUART1_STOP_BITS,                                \
    ES_CONF_EUART1_PARITY,                                \
    BIT_ORDER_LSB,                              \
    NRZ_NORMAL,                                 \
    RT_SERIAL_RB_BUFSZ,                         \
    0                                           \
}


#define ES_CUART0_CONFIG                         \
{                                               \
    ES_CONF_CUART0_BAUD_RATE,                           \
    DATA_BITS_8,                                \
    ES_CONF_CUART0_STOP_BITS,                                \
    ES_CONF_CUART0_PARITY,                                \
    BIT_ORDER_LSB,                              \
    NRZ_NORMAL,                                 \
    RT_SERIAL_RB_BUFSZ,                         \
    0                                           \
}


#define ES_CUART1_CONFIG                         \
{                                               \
    ES_CONF_CUART1_BAUD_RATE,                           \
    DATA_BITS_8,                                \
    ES_CONF_CUART1_STOP_BITS,                                \
    ES_CONF_CUART1_PARITY,                                \
    BIT_ORDER_LSB,                              \
    NRZ_NORMAL,                                 \
    RT_SERIAL_RB_BUFSZ,                         \
    0                                           \
}


#define ES_CUART2_CONFIG                         \
{                                               \
    ES_CONF_CUART2_BAUD_RATE,                           \
    DATA_BITS_8,                                \
    ES_CONF_CUART2_STOP_BITS,                                \
    ES_CONF_CUART2_PARITY,                                \
    BIT_ORDER_LSB,                              \
    NRZ_NORMAL,                                 \
    RT_SERIAL_RB_BUFSZ,                         \
    0                                           \
}



#endif
