#ifndef __DRV_SPI_NRF24L01_H__
#include <rtthread.h>

#define u8	uint8_t
#define u16 uint16_t
#define u32 uint32_t

//NRF24L01寄存器操作命令 //SPI commands for nRF24L01
#define R_REGISTER         0x00  //读配置寄存器,低5位为寄存器地址
#define W_REGISTER         0x20  //写配置寄存器,低5位为寄存器地址
#define R_RX_PAYLOAD       0x61  //读RX有效数据,1~32字节
#define W_TX_PAYLOAD       0xA0  //写TX有效数据,1~32字节
#define FLUSH_TX           0xE1  //清除TX FIFO寄存器.发射模式下用
#define FLUSH_RX           0xE2  //清除RX FIFO寄存器.接收模式下用
#define REUSE_TX_PL        0xE3  //重新使用上一包数据,CE为高,数据包被不断发送
#define ACTIVATE	       0x50  //用命令后跟数据0x73，将激活：R_RX_PL_WID，W_ACK_PAYLOAD，W_TX_PAYLOAD_NOACK
								 //再次使用该令后跟同样的数据，将关闭上述功能
#define R_RX_PL_WID        0x60  //接收到的数据长度
#define W_ACK_PAYLOAD      0xA8  //写应答数据
#define W_TX_PAYLOAD_NOACK 0xB0  //写TX数据,不应答
#define NOP                0xFF  //空操作,可以用来读状态寄存器

//NRF24L01寄存器地址
#define CONFIG        0x00  //配置寄存器;bit0:1接收模式,0发射模式;bit1:电选择;bit2:CRC模式;bit3:CRC使能;
                            //bit4:中断MAX_RT(最大重发次数中断)使能;bit5:中断TX_DS使能;bit6:中断RX_DR使能
#define EN_AA         0x01  //使能自动应答;bit0~5,对应通道0~5
#define EN_RXADDR     0x02  //接收地址允许;bit0~5,对应通道0~5
#define SETUP_AW      0x03  //设置地址宽度(所有数据通道);bit1:0;00,3字节;01,4字节;02,5字节;
#define SETUP_RETR    0x04  //建立自动重发;bit3:0;自动重发计数器;bit7:4,自动重发延时 250*x+86us
#define RF_CH         0x05  //RF通道;bit6:0;工作通道频率;
#define RF_SETUP      0x06  //RF寄存器;bit3:传输速率(0:1Mbps,1:2Mbps);bit2:1,发射功率;bit0:低噪声放大器增益
#define STATUS        0x07  //状态寄存器;bit0:TX FIFO满标志;bit3:1,接收数据通道号(最大:6);bit4,达到最多次重发
                            //bit5:数据发送完成中断;bit6:接收数据中断;
#define OBSERVE_TX    0x08  //发送检测寄存器,bit7:4,数据包丢失计数器;bit3:0,重发计数器
#define CD            0x09  //载波检测寄存器,bit0,载波检测;
#define RX_ADDR_P0    0x0A  //数据通道0接收地址,最大长度5个字节,低字节在前
#define RX_ADDR_P1    0x0B  //数据通道1接收地址,最大长度5个字节,低字节在前
#define RX_ADDR_P2    0x0C  //数据通道2接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P3    0x0D  //数据通道3接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P4    0x0E  //数据通道4接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P5    0x0F  //数据通道5接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define TX_ADDR       0x10  //发送地址(低字节在前),ShockBurstTM模式下,RX_ADDR_P0与此地址相等
#define RX_PW_P0      0x11  //接收数据通道0有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P1      0x12  //接收数据通道1有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P2      0x13  //接收数据通道2有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P3      0x14  //接收数据通道3有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P4      0x15  //接收数据通道4有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P5      0x16  //接收数据通道5有效数据宽度(1~32字节),设置为0则非法
#define FIFO_STATUS   0x17  //FIFO状态寄存器;bit0,RX FIFO寄存器空标志;bit1,RX FIFO满标志;bit2,3,保留
                            //bit4,TX FIFO空标志;bit5,TX FIFO满标志;bit6,1,循环发送上一数据包.0,不循环;

#define DYNPD         0x1C  //使能动态数据长度通道,bit0~5,对应通道0~5
#define FEATRUE       0x1D  //bit2,使能动态数据长度;bit1,使能数据应答;bit0,使能数据不应答;

#define MAX_RT        0x10  //达到最大发送次数中断
#define TX_DS         0x20  //TX发送完成中断
#define RX_DR         0x40  //接收到数据中断

#define RX_P_NO_MASK  0x0E
#define IRQ_ALL       (TX_DS|RX_DR|MAX_RT)

#define DataPipe0     0
#define DataPipe1     1
#define DataPipe2     2
#define DataPipe3     3
#define DataPipe4     4
#define DataPipe5     5
#define TxPipe        6

#define MAC_LEN				(5)
#define PAYLOAD_LEN			(32)

#define NRF_EVENT			(1<<0)
#define NRF_SEND_FINISH		(1<<1)
#define NRF_SEND_MAXCOUNT	(1<<2)

typedef void(*nrf_hw_recv_callback_t)(rt_uint8_t pipe_num, rt_uint8_t *rxdata, rt_uint8_t length);

void nrf_reg_hw_recv_callback(nrf_hw_recv_callback_t recv);
void NRF_Config(const u8 *addr,const u8 channel);
u8 NRF_SendPayload(const u8 ack,const u8 *addr,const u8 channel,const u8 *buf);
void NRF_RxMode(const u8 *addr,const u8 channel);
u8 NRF_DisturbanceDetect(void);
void NRF_SetChannel(const u8 channel);
u8 NRF_ReadChannel(void);
u8 NRF_SetRfPower(const u8 level);//(0-3)
u8 NRF_Check(void);
void NRF_SetPipe1Mac(u8 *addr);
void NRF_SetPipe2Mac(u8 *addr);

#endif

