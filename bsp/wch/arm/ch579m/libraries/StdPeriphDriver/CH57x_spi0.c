/********************************** (C) COPYRIGHT *******************************
* File Name          : CH57x_SPI0.c
* Author             : WCH
* Version            : V1.0
* Date               : 2018/12/15
* Description
*******************************************************************************/

#include "CH57x_common.h"


/*******************************************************************************
* Function Name  : SPI0_MasterDefInit
* Description    : 主机模式默认初始化：模式0+3线全双工+8MHz
* Input          : None
* Return         : None
*******************************************************************************/
void SPI0_MasterDefInit( void )
{
    R8_SPI0_CLOCK_DIV = 4;      // 主频时钟4分频
    R8_SPI0_CTRL_MOD = RB_SPI_ALL_CLEAR;
    R8_SPI0_CTRL_MOD = RB_SPI_MOSI_OE | RB_SPI_SCK_OE ;
    R8_SPI0_CTRL_CFG |= RB_SPI_AUTO_IF;        // 访问BUFFER/FIFO自动清除IF_BYTE_END标志
    R8_SPI0_CTRL_CFG &= ~RB_SPI_DMA_ENABLE;    // 不启动DMA方式
}

/*******************************************************************************
* Function Name  : SPI0_CLKCfg
* Description    : SPI0 基准时钟配置，= d*Tsys
* Input          : c: 时钟分频系数
* Return         : None
*******************************************************************************/
void SPI0_CLKCfg( UINT8 c )
{
    if(c==2)
        R8_SPI0_CTRL_CFG |= RB_SPI_MST_DLY_EN;
    else
        R8_SPI0_CTRL_CFG &= ~RB_SPI_MST_DLY_EN;
    R8_SPI0_CLOCK_DIV = c;
}

/*******************************************************************************
* Function Name  : SPI0_DataMode
* Description    : 设置数据流模式
* Input          : m: 数据流模式
                    refer to ModeBitOrderTypeDef
* Return         : None
*******************************************************************************/
void SPI0_DataMode( ModeBitOrderTypeDef m )
{
    switch( m )
    {
        case Mode0_LowBitINFront:
            R8_SPI0_CTRL_MOD &= ~RB_SPI_MST_SCK_MOD;
            R8_SPI0_CTRL_CFG |= RB_SPI_BIT_ORDER;
            break;
        case Mode0_HighBitINFront:
            R8_SPI0_CTRL_MOD &= ~RB_SPI_MST_SCK_MOD;
            R8_SPI0_CTRL_CFG &= ~RB_SPI_BIT_ORDER;
            break;
        case Mode3_LowBitINFront:
            R8_SPI0_CTRL_MOD |= RB_SPI_MST_SCK_MOD;
            R8_SPI0_CTRL_CFG |= RB_SPI_BIT_ORDER;
            break;
        case Mode3_HighBitINFront:
            R8_SPI0_CTRL_MOD |= RB_SPI_MST_SCK_MOD;
            R8_SPI0_CTRL_CFG &= ~RB_SPI_BIT_ORDER;
            break;
        default:
            break;
    }
}

/*******************************************************************************
* Function Name  : SPI0_MasterSendByte
* Description    : 发送单字节 (buffer)
* Input          : d: 发送字节
* Return         : None
*******************************************************************************/
void SPI0_MasterSendByte( UINT8 d )
{
    R8_SPI0_CTRL_MOD &= ~RB_SPI_FIFO_DIR;
    R8_SPI0_BUFFER = d;
    while( !(R8_SPI0_INT_FLAG & RB_SPI_FREE) );
}

/*******************************************************************************
* Function Name  : SPI0_MasterRecvByte
* Description    : 接收单字节 (buffer)
* Input          : None
* Return         : 接收到的字节
*******************************************************************************/
UINT8 SPI0_MasterRecvByte( void )
{
    R8_SPI0_CTRL_MOD &= ~RB_SPI_FIFO_DIR;
    R8_SPI0_BUFFER = 0xFF;           // 启动传输
    while( !(R8_SPI0_INT_FLAG & RB_SPI_FREE) );
    return ( R8_SPI0_BUFFER );
}


/*******************************************************************************
* Function Name  : SPI0_MasterTrans
* Description    : 使用FIFO连续发送多字节
* Input          : pbuf: 待发送的数据内容首地址
                   len: 请求发送的数据长度，最大4095
* Return         : None
*******************************************************************************/
void SPI0_MasterTrans( UINT8 *pbuf, UINT16 len )
{
    UINT16 sendlen;

    sendlen = len;
    R8_SPI0_CTRL_MOD &= ~RB_SPI_FIFO_DIR;                     // 设置数据方向为输出
    R16_SPI0_TOTAL_CNT = sendlen;                             // 设置要发送的数据长度
    R8_SPI0_INT_FLAG = RB_SPI_IF_CNT_END;
    while( sendlen )
    {
        if( R8_SPI0_FIFO_COUNT < SPI_FIFO_SIZE )
        {
            R8_SPI0_FIFO = *pbuf;
            pbuf++;
            sendlen--;
        }
    }
    while( R8_SPI0_FIFO_COUNT != 0 );                         // 等待FIFO中的数据全部发送完成
}

/*******************************************************************************
* Function Name  : SPI0_MasterRecv
* Description    : 使用FIFO连续接收多字节
* Input          : pbuf: 待发送的数据内容首地址
                   len: 请求发送的数据长度，最大4095
* Return         : None
*******************************************************************************/
void SPI0_MasterRecv( UINT8 *pbuf, UINT16 len )
{
    UINT16  readlen;

    readlen = len;
    R8_SPI0_CTRL_MOD |= RB_SPI_FIFO_DIR;                     // 设置数据方向为输入
    R16_SPI0_TOTAL_CNT = len;                                // 设置需要接收的数据长度，FIFO方向为输入长度不为0则会启动传输 */
    R8_SPI0_INT_FLAG = RB_SPI_IF_CNT_END;
    while( readlen )
    {
        if( R8_SPI0_FIFO_COUNT )
        {
            *pbuf = R8_SPI0_FIFO;
            pbuf++;
            readlen--;
        }
    }
}

/*******************************************************************************
* Function Name  : SPI0_MasterDMATrans
* Description    : DMA方式连续发送数据
* Input          : pbuf: 待发送数据起始地址
*                  len : 待发送数据长度
* Return         : None
*******************************************************************************/
void SPI0_MasterDMATrans( PUINT8 pbuf, UINT16 len)
{
    R8_SPI0_CTRL_MOD &= ~RB_SPI_FIFO_DIR;
    R16_SPI0_DMA_BEG = (UINT32)pbuf;
    R16_SPI0_DMA_END = (UINT32)(pbuf + len);
    R16_SPI0_TOTAL_CNT = len;
    R8_SPI0_INT_FLAG = RB_SPI_IF_CNT_END|RB_SPI_IF_DMA_END;
    R8_SPI0_CTRL_CFG |= RB_SPI_DMA_ENABLE;
    while(!(R8_SPI0_INT_FLAG & RB_SPI_IF_CNT_END));
    R8_SPI0_CTRL_CFG &= ~RB_SPI_DMA_ENABLE;
}

/*******************************************************************************
* Function Name  : SPI0_MasterDMARecv
* Description    : DMA方式连续接收数据
* Input          : pbuf: 待接收数据存放起始地址
*                  len : 待接收数据长度
* Return         : None
*******************************************************************************/
void SPI0_MasterDMARecv( PUINT8 pbuf, UINT16 len)
{
    R8_SPI0_CTRL_MOD |= RB_SPI_FIFO_DIR;
    R16_SPI0_DMA_BEG = (UINT32)pbuf;
    R16_SPI0_DMA_END = (UINT32)(pbuf + len);
    R16_SPI0_TOTAL_CNT = len;
    R8_SPI0_INT_FLAG = RB_SPI_IF_CNT_END|RB_SPI_IF_DMA_END;
    R8_SPI0_CTRL_CFG |= RB_SPI_DMA_ENABLE;
    while(!(R8_SPI0_INT_FLAG & RB_SPI_IF_CNT_END));
    R8_SPI0_CTRL_CFG &= ~RB_SPI_DMA_ENABLE;
}



/*******************************************************************************
* Function Name  : SPI0_SlaveInit
* Description    : 设备模式默认初始化，建议设置MISO的GPIO对应为输入模式
* Input          : None
* Return         : None
*******************************************************************************/
void SPI0_SlaveInit( void )
{
    R8_SPI0_CTRL_MOD = RB_SPI_ALL_CLEAR;
    R8_SPI0_CTRL_MOD = RB_SPI_MISO_OE | RB_SPI_MODE_SLAVE;
    R8_SPI0_CTRL_CFG |= RB_SPI_AUTO_IF;
}

/*******************************************************************************
* Function Name  : SPI0_SlaveRecvByte
* Description    : 从机模式，接收一字节数据
* Input          : None
* Return         : 接收到数据
*******************************************************************************/
UINT8 SPI0_SlaveRecvByte( void )
{
    R8_SPI0_CTRL_MOD |= RB_SPI_FIFO_DIR;
    while( R8_SPI0_FIFO_COUNT == 0 );
    return R8_SPI0_FIFO;
}

/*******************************************************************************
* Function Name  : SPI0_SlaveSendByte
* Description    : 从机模式，发送一字节数据
* Input          : d -待发送数据
* Return         : None
*******************************************************************************/
void SPI0_SlaveSendByte( UINT8 d )
{
    R8_SPI0_CTRL_MOD &= ~RB_SPI_FIFO_DIR;
    R8_SPI0_FIFO = d;
    while( R8_SPI0_FIFO_COUNT != 0 );               // 等待发送完成
}

/*******************************************************************************
* Function Name  : SPI0_SlaveRecv
* Description    : 从机模式，接收多字节数据
* Input          : pbuf: 接收收数据存放起始地址
*                  len : 请求接收数据长度
* Return         : None
*******************************************************************************/
void SPI0_SlaveRecv( PUINT8 pbuf, UINT16 len )
{
    UINT16 revlen;

    revlen = len;
    R8_SPI0_CTRL_MOD |= RB_SPI_FIFO_DIR;
    R8_SPI0_INT_FLAG = RB_SPI_IF_CNT_END;
    while( revlen )
    {
        if( R8_SPI0_FIFO_COUNT )
        {
            *pbuf = R8_SPI0_FIFO;
            pbuf++;
            revlen--;
        }
    }
}

/*******************************************************************************
* Function Name  : SPI0_SlaveTrans
* Description    : 从机模式，发送多字节数据
* Input          : pbuf: 待发送的数据内容首地址
                   len: 请求发送的数据长度，最大4095
* Return         : None
*******************************************************************************/
void SPI0_SlaveTrans( UINT8 *pbuf, UINT16 len )
{
    UINT16 sendlen;

    sendlen = len;
    R8_SPI0_CTRL_MOD &= ~RB_SPI_FIFO_DIR;                     // 设置数据方向为输出
    R8_SPI0_INT_FLAG = RB_SPI_IF_CNT_END;
    while( sendlen )
    {
        if( R8_SPI0_FIFO_COUNT < SPI_FIFO_SIZE )
        {
            R8_SPI0_FIFO = *pbuf;
            pbuf++;
            sendlen--;
        }
    }
    while( R8_SPI0_FIFO_COUNT != 0 );                         // 等待FIFO中的数据全部发送完成
}

/*******************************************************************************
* Function Name  : SPI0_SlaveDMARecv
* Description    : DMA方式连续接收数据
* Input          : pbuf: 待接收数据存放起始地址
*                  len : 待接收数据长度
* Return         : None
*******************************************************************************/
void SPI0_SlaveDMARecv( PUINT8 pbuf, UINT16 len)
{
    R8_SPI0_CTRL_MOD |= RB_SPI_FIFO_DIR;
    R16_SPI0_DMA_BEG = (UINT32)pbuf;
    R16_SPI0_DMA_END = (UINT32)(pbuf + len);
    R16_SPI0_TOTAL_CNT = len;
    R8_SPI0_INT_FLAG = RB_SPI_IF_CNT_END|RB_SPI_IF_DMA_END;
    R8_SPI0_CTRL_CFG |= RB_SPI_DMA_ENABLE;
    while(!(R8_SPI0_INT_FLAG & RB_SPI_IF_CNT_END));
    R8_SPI0_CTRL_CFG &= ~RB_SPI_DMA_ENABLE;
}

/*******************************************************************************
* Function Name  : SPI0_SlaveDMATrans
* Description    : DMA方式连续发送数据
* Input          : pbuf: 待发送数据起始地址
*                  len : 待发送数据长度
* Return         : None
*******************************************************************************/
void SPI0_SlaveDMATrans( PUINT8 pbuf, UINT16 len)
{
    R8_SPI0_CTRL_MOD &= ~RB_SPI_FIFO_DIR;
    R16_SPI0_DMA_BEG = (UINT32)pbuf;
    R16_SPI0_DMA_END = (UINT32)(pbuf + len);
    R16_SPI0_TOTAL_CNT = len;
    R8_SPI0_INT_FLAG = RB_SPI_IF_CNT_END|RB_SPI_IF_DMA_END;
    R8_SPI0_CTRL_CFG |= RB_SPI_DMA_ENABLE;
    while(!(R8_SPI0_INT_FLAG & RB_SPI_IF_CNT_END));
    R8_SPI0_CTRL_CFG &= ~RB_SPI_DMA_ENABLE;
}



