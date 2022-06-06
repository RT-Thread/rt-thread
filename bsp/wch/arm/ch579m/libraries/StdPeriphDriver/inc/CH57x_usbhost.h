


#ifndef __CH57x_USBHOST_H__
#define __CH57x_USBHOST_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "CH579SFR.h"
#include "core_cm0.h"

/***************************************** 不使用U盘文件系统库或者U盘挂载USBhub下面，需要关闭下面定义 */
#define FOR_ROOT_UDISK_ONLY
/***************************************** 使用U盘文件系统库，需要开启下面定义, 不使用请关闭 */
#define DISK_BASE_BUF_LEN       512         /* 默认的磁盘数据缓冲区大小为512字节,建议选择为2048甚至4096以支持某些大扇区的U盘,为0则禁止在.H文件中定义缓冲区并由应用程序在pDISK_BASE_BUF中指定 */



// 各子程序返回状态码
#define ERR_SUCCESS         0x00    // 操作成功
#define ERR_USB_CONNECT     0x15    /* 检测到USB设备连接事件,已经连接 */
#define ERR_USB_DISCON      0x16    /* 检测到USB设备断开事件,已经断开 */
#define ERR_USB_BUF_OVER    0x17    /* USB传输的数据有误或者数据太多缓冲区溢出 */
#define ERR_USB_DISK_ERR    0x1F    /* USB存储器操作失败,在初始化时可能是USB存储器不支持,在读写操作中可能是磁盘损坏或者已经断开 */
#define ERR_USB_TRANSFER    0x20    /* NAK/STALL等更多错误码在0x20~0x2F */
#define ERR_USB_UNSUPPORT   0xFB    /*不支持的USB设备*/
#define ERR_USB_UNKNOWN     0xFE    /*设备操作出错*/
#define ERR_AOA_PROTOCOL    0x41    /*协议版本出错 */

/*USB设备相关信息表,最多支持1个设备*/
#define ROOT_DEV_DISCONNECT  0
#define ROOT_DEV_CONNECTED   1
#define ROOT_DEV_FAILED      2
#define ROOT_DEV_SUCCESS     3
#define DEV_TYPE_KEYBOARD   ( USB_DEV_CLASS_HID | 0x20 )
#define DEV_TYPE_MOUSE      ( USB_DEV_CLASS_HID | 0x30 )
#define DEF_AOA_DEVICE       0xF0
#define DEV_TYPE_UNKNOW      0xFF


/*
约定: USB设备地址分配规则(参考USB_DEVICE_ADDR)
地址值  设备位置
0x02    内置Root-HUB下的USB设备或外部HUB
0x1x    内置Root-HUB下的外部HUB的端口x下的USB设备,x为1~n
*/
#define HUB_MAX_PORTS           4
#define WAIT_USB_TOUT_200US     800   // 等待USB中断超时时间


typedef struct
{
    UINT8   DeviceStatus;              // 设备状态,0-无设备,1-有设备但尚未初始化,2-有设备但初始化枚举失败,3-有设备且初始化枚举成功
    UINT8   DeviceAddress;             // 设备被分配的USB地址
    UINT8   DeviceSpeed;               // 0为低速,非0为全速
    UINT8   DeviceType;                // 设备类型
    UINT16  DeviceVID;
    UINT16  DevicePID;
    UINT8   GpVar[4];                    // 通用变量，存放端点
    UINT8   GpHUBPortNum;                // 通用变量,如果是HUB，表示HUB端口数
} _RootHubDev;


extern _RootHubDev  ThisUsbDev;
extern UINT8  UsbDevEndp0Size;              // USB设备的端点0的最大包尺寸 */
extern UINT8  FoundNewDev;

extern PUINT8  pHOST_RX_RAM_Addr;
extern PUINT8  pHOST_TX_RAM_Addr;
#define pSetupReq   ((PUSB_SETUP_REQ)pHOST_TX_RAM_Addr)
extern UINT8  Com_Buffer[];

/* 以下为USB主机请求包 */
extern const UINT8  SetupGetDevDescr[];    //*获取设备描述符*/
extern const UINT8  SetupGetCfgDescr[];    //*获取配置描述符*/
extern const UINT8  SetupSetUsbAddr[];     //*设置USB地址*/
extern const UINT8  SetupSetUsbConfig[];   //*设置USB配置*/
extern const UINT8  SetupSetUsbInterface[];//*设置USB接口配置*/
extern const UINT8  SetupClrEndpStall[];   //*清除端点STALL*/


void  DisableRootHubPort(void)  ;                   // 关闭ROOT-HUB端口,实际上硬件已经自动关闭,此处只是清除一些结构状态
UINT8   AnalyzeRootHub( void ) ;         // 分析ROOT-HUB状态,处理ROOT-HUB端口的设备插拔事件
// 返回ERR_SUCCESS为没有情况,返回ERR_USB_CONNECT为检测到新连接,返回ERR_USB_DISCON为检测到断开
void    SetHostUsbAddr( UINT8 addr );                 // 设置USB主机当前操作的USB设备地址
void    SetUsbSpeed( UINT8 FullSpeed );               // 设置当前USB速度
void    ResetRootHubPort(void);                          // 检测到设备后,复位相应端口的总线,为枚举设备准备,设置为默认为全速
UINT8   EnableRootHubPort(void);                          // 使能ROOT-HUB端口,相应的bUH_PORT_EN置1开启端口,设备断开可能导致返回失败
void    SelectHubPort( UINT8 HubPortIndex );// HubPortIndex=0选择操作指定的ROOT-HUB端口,否则选择操作指定的ROOT-HUB端口的外部HUB的指定端口
UINT8   WaitUSB_Interrupt( void );                    // 等待USB中断
// 传输事务,输入目的端点地址/PID令牌,同步标志,以20uS为单位的NAK重试总时间(0则不重试,0xFFFF无限重试),返回0成功,超时/出错重试
UINT8   USBHostTransact( UINT8 endp_pid, UINT8 tog, UINT32 timeout );  // endp_pid: 高4位是token_pid令牌, 低4位是端点地址
UINT8   HostCtrlTransfer( PUINT8 DataBuf, PUINT8 RetLen );  // 执行控制传输,8字节请求码在pSetupReq中,DataBuf为可选的收发缓冲区
// 如果需要接收和发送数据,那么DataBuf需指向有效缓冲区用于存放后续数据,实际成功收发的总长度返回保存在ReqLen指向的字节变量中


void CopySetupReqPkg( PCCHAR pReqPkt );            // 复制控制传输的请求包
UINT8 CtrlGetDeviceDescr( void );                    // 获取设备描述符,返回在 pHOST_TX_RAM_Addr 中
UINT8 CtrlGetConfigDescr( void );                    // 获取配置描述符,返回在 pHOST_TX_RAM_Addr 中
UINT8 CtrlSetUsbAddress( UINT8 addr );                         // 设置USB设备地址
UINT8 CtrlSetUsbConfig( UINT8 cfg );                           // 设置USB设备配置
UINT8 CtrlClearEndpStall( UINT8 endp ) ;                       // 清除端点STALL
UINT8 CtrlSetUsbIntercace( UINT8 cfg );                        // 设置USB设备接口


void    USB_HostInit( void );                                  // 初始化USB主机



/*************************************************************/


UINT8 InitRootDevice( void );

UINT8   CtrlGetHIDDeviceReport( UINT8 infc );          // HID类命令，SET_IDLE和GET_REPORT
UINT8   CtrlGetHubDescr( void );                       // 获取HUB描述符,返回在TxBuffer中
UINT8   HubGetPortStatus( UINT8 HubPortIndex );        // 查询HUB端口状态,返回在TxBuffer中
UINT8   HubSetPortFeature( UINT8 HubPortIndex, UINT8 FeatureSelt );  // 设置HUB端口特性
UINT8   HubClearPortFeature( UINT8 HubPortIndex, UINT8 FeatureSelt );  // 清除HUB端口特性



#ifdef __cplusplus
}
#endif

#endif  // __CH57x_USBHOST_H__

