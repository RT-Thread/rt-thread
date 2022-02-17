/********************************** (C) COPYRIGHT *******************************
* File Name          : CH57x_SPI1.c
* Author             : WCH
* Version            : V1.0
* Date               : 2019/4/29
* Description
*******************************************************************************/

#include "CH57x_common.h"


/*******************************************************************************
* Function Name  : SPI1_MasterDefInit
* Description    : 主机模式默认初始化：模式0+3线全双工+8MHz
* Input          : None
* Return         : None
*******************************************************************************/
void SPI1_MasterDefInit( void )
{
    R8_SPI1_CLOCK_DIV = 4;      // 主频时钟4分频
    R8_SPI1_CTRL_MOD = RB_SPI_ALL_CLEAR;
    R8_SPI1_CTRL_MOD = RB_SPI_MOSI_OE | RB_SPI_SCK_OE ;
    R8_SPI1_CTRL_CFG |= RB_SPI_AUTO_IF;        // 访问BUFFER/FIFO自动清除IF_BYTE_END标志
    R8_SPI1_CTRL_CFG &= ~RB_SPI_DMA_ENABLE;    // 不启动DMA方式
}

/*******************************************************************************
* Function Name  : SPI1_CLKCfg
* Description    : SPI1 基准时钟配置，= d*Tsys
* Input          : c: 时钟分频系数
* Return         : None
*******************************************************************************/
void SPI1_CLKCfg( UINT8 c )
{
    if(c==2)
        R8_SPI1_CTRL_CFG |= RB_SPI_MST_DLY_EN;
    else
        R8_SPI1_CTRL_CFG &= ~RB_SPI_MST_DLY_EN;
    R8_SPI1_CLOCK_DIV = c;
}

/*******************************************************************************
* Function Name  : SPI1_DataMode
* Description    : 设置数据流模式
* Input          : m: 数据流模式
                    refer to ModeBitOrderTypeDef
* Return         : None
*******************************************************************************/
void SPI1_DataMode( ModeBitOrderTypeDef m )
{
    switch( m )
    {
        case Mode0_LowBitINFront:
            R8_SPI1_CTRL_MOD &= ~RB_SPI_MST_SCK_MOD;
            R8_SPI1_CTRL_CFG |= RB_SPI_BIT_ORDER;
            break;
        case Mode0_HighBitINFront:
            R8_SPI1_CTRL_MOD &= ~RB_SPI_MST_SCK_MOD;
            R8_SPI1_CTRL_CFG &= ~RB_SPI_BIT_ORDER;
            break;
        case Mode3_LowBitINFront:
            R8_SPI1_CTRL_MOD |= RB_SPI_MST_SCK_MOD;
            R8_SPI1_CTRL_CFG |= RB_SPI_BIT_ORDER;
            break;
        case Mode3_HighBitINFront:
            R8_SPI1_CTRL_MOD |= RB_SPI_MST_SCK_MOD;
            R8_SPI1_CTRL_CFG &= ~RB_SPI_BIT_ORDER;
            break;
        default:
            break;
    }
}

/*******************************************************************************
* Function Name  : SPI1_MasterSendByte
* Description    : 发送单字节 (buffer)
* Input          : d: 发送字节
* Return         : None
*******************************************************************************/
void SPI1_MasterSendByte( UINT8 d )
{
    R8_SPI1_CTRL_MOD &= ~RB_SPI_FIFO_DIR;
    R8_SPI1_BUFFER = d;
    while( !(R8_SPI1_INT_FLAG & RB_SPI_FREE) );
}

/*******************************************************************************
* Function Name  : SPI1_MasterRecvByte
* Description    : 接收单字节 (buffer)
* Input          : None
* Return         : 接收到的字节
*******************************************************************************/
UINT8 SPI1_MasterRecvByte( void )
{
    R8_SPI1_CTRL_MOD &= ~RB_SPI_FIFO_DIR;
    R8_SPI1_BUFFER = 0xFF;           // 启动传输
    while( !(R8_SPI1_INT_FLAG & RB_SPI_FREE) );
    return ( R8_SPI1_BUFFER );
}


/*******************************************************************************
* Function Name  : SPI1_MasterTrans
* Description    : 使用FIFO连续发送多字节
* Input          : pbuf: 待发送的数据内容首地址
                   len: 请求发送的数据长度，最大4095
* Return         : None
*******************************************************************************/
void SPI1_MasterTrans( UINT8 *pbuf, UINT16 len )
{
    UINT16 sendlen;

    sendlen = len;
    R8_SPI1_CTRL_MOD &= ~RB_SPI_FIFO_DIR;                     // 设置数据方向为输出
    R16_SPI1_TOTAL_CNT = sendlen;                             // 设置要发送的数据长度
    R8_SPI1_INT_FLAG = RB_SPI_IF_CNT_END;
    while( sendlen )
    {
        if( R8_SPI1_FIFO_COUNT < SPI_FIFO_SIZE )
        {
            R8_SPI1_FIFO = *pbuf;
            pbuf++;
            sendlen--;
        }
    }
    while( R8_SPI1_FIFO_COUNT != 0 );                         // 等待FIFO中的数据全部发送完成
}

/*******************************************************************************
* Function Name  : SPI1_MasterRecv
* Description    : 使用FIFO连续接收多字节
* Input          : pbuf: 待发送的数据内容首地址
                   len: 请求发送的数据长度，最大4095
* Return         : None
*******************************************************************************/
void SPI1_MasterRecv( UINT8 *pbuf, UINT16 len )
{
    UINT16  readlen;

    readlen = len;
    R8_SPI1_CTRL_MOD |= RB_SPI_FIFO_DIR;                     // 设置数据方向为输入
    R16_SPI1_TOTAL_CNT = len;                                // 设置需要接收的数据长度，FIFO方向为输入长度不为0则会启动传输 */
    R8_SPI1_INT_FLAG = RB_SPI_IF_CNT_END;
    while( readlen )
    {
        if( R8_SPI1_FIFO_COUNT )
        {
            *pbuf = R8_SPI1_FIFO;
            pbuf++;
            readlen--;
        }
    }
}



