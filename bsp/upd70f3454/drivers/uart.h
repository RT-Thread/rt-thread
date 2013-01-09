#ifndef __UART_H__
#define __UART_H__

#define BAUD_RATE 9600

/*
	UARTAn control register 0 (UAnCTL0)
*/
#define	_10_UARTA_UAnCTL0_INITIALVALUE			0x10U
/* UARTAn operation control (UAnPWR) */
#define	_00_UARTA_OPERATION_DISABLE			0x00U	/* disable UARTAn operation (UARTAn reset asynchronously) */
#define	_80_UARTA_OPERATION_ENABLE			0x80U	/* enable UARTAn operation */
/* Transmission operation enable (UAnTXE) */
#define	_00_UARTA_TRANSMISSION_DISABLE			0x00U	/* disable transmission operation */
#define	_40_UARTA_TRANSMISSION_ENABLE			0x40U	/* enable transmission operation */
/* Reception operation enable (UAnRXE) */
#define	_00_UARTA_RECEPTION_DISABLE			0x00U	/* disable reception operation */
#define	_20_UARTA_RECEPTION_ENABLE			0x20U	/* enable reception operation */
/* Transfer direction selection (UAnDIR) */
#define	_00_UARTA_TRANSFDIR_MSB				0x00U	/* MSB-first transfer */
#define	_10_UARTA_TRANSFDIR_LSB				0x10U	/* LSB-first transfer */
/* Parity selection during transmission/reception (UAnPS1,UAnPS0) */
#define	_00_UARTA_PARITY_NONE				0x00U	/* no parity output/reception with no parity */
#define	_04_UARTA_PARITY_ZREO				0x04U	/* 0 parity output/reception with 0 parity */
#define	_08_UARTA_PARITY_ODD				0x08U	/* odd parity output/odd parity check */
#define	_0C_UARTA_PARITY_EVEN				0x0CU	/* even parity output/even parity check */
/* Specification of data character length of 1 frame of transmit/receive data (UAnCL) */
#define	_00_UARTA_DATALENGTH_7BIT			0x00U	/* 7 bits */
#define	_02_UARTA_DATALENGTH_8BIT			0x02U	/* 8 bits */
/* Specification of length of stop bit for transmit data (UAnSL) */
#define	_00_UARTA_STOPLENGTH_1BIT			0x00U	/* 1 bit */
#define	_01_UARTA_STOPLENGTH_2BIT			0x01U	/* 2 bits */

/*
	UARTAn base clock selects register (UAnCTL1)
*/
/* UAnCTL1 register (UAnCKS3 - UAnCKS0) */
#define	_00_UARTA_BASECLK_FXX_2				0x00U	/* fXX/2 */
#define	_01_UARTA_BASECLK_FXX_4				0x01U	/* fXX/2^2 */
#define	_02_UARTA_BASECLK_FXX_8				0x02U	/* fXX/2^3 */
#define	_03_UARTA_BASECLK_FXX_16			0x03U	/* fXX/2^4 */
#define	_04_UARTA_BASECLK_FXX_32			0x04U	/* fXX/2^5 */
#define	_05_UARTA_BASECLK_FXX_64			0x05U	/* fXX/2^6 */
#define	_06_UARTA_BASECLK_FXX_128			0x06U	/* fXX/2^7 */
#define	_07_UARTA_BASECLK_FXX_256			0x07U	/* fXX/2^8 */
#define	_08_UARTA_BASECLK_FXX_512			0x08U	/* fXX/2^9 */
#define	_09_UARTA_BASECLK_FXX_1024			0x09U	/* fXX/2^10 */
#define	_0A_UARTA_BASECLK_FXX_2048			0x0AU	/* fXX/2^11 */
#define	_0B_UARTA_BASECLK_FXX_4096			0x0BU	/* fXX/2^12 */

/*
	UARTAn option control register 0 (UAnOPT0)
*/
#define	_14_UARTA_UAnOPT0_INITIALVALUE			0x14U
/* Transmit data level bit(UAnTDL) */
#define	_00_UARTA_TRAN_DATALEVEL_NORMAL			0x00U	/* normal output of transfer data */
#define	_02_UARTA_TRAN_DATALEVEL_INVERTED		0x02U	/* inverted output of transfer data */
/* Receive data level bit(UAnRDL) */
#define	_00_UARTA_REC_DATALEVEL_NORMAL			0x00U	/* normal input of transfer data */
#define	_01_UARTA_REC_DATALEVEL_INVERTED		0x01U	/* inverted input of transfer data */

/*
	CSIBn control register 0 (CBnCTL0)
*/
/* Specification of CSIBn operation disable/enable (CBnPWR)*/
#define	_00_CSIB_OPERATION_DISABLE		0x00U	/* disable CSIBn operation and reset the CBnSTR register */
#define	_80_CSIB_OPERATION_ENABLE		0x80U	/* enable CSIBn operation */
/* Specification of transmit operation disable/enable (CBnTXE)*/
#define	_00_CSIB_TRANSMIT_DISABLE		0x00U	/* disable transmit operation */
#define	_40_CSIB_TRANSMIT_ENABLE		0x40U	/* enable transmit operation */
/* Specification of receive operation disable/enable (CBnRXE)*/
#define	_00_CSIB_RECEIVE_DISABLE		0x00U	/* disable receive operation */
#define	_20_CSIB_RECEIVE_ENABLE			0x20U	/* enable receive operation */
/* Specification of transfer direction mode (MSB/LSB) (CBnDIR) */
#define	_00_CSIB_DATA_MSB			0x00U	/* MSB first */ 
#define	_10_CSIB_DATA_LSB			0x10U	/* LSB first */
/* Transfer mode specification (CBnTMS) */
#define	_00_CSIB_MODE_SINGLE			0x00U	/* single transfer mode */
#define	_02_CSIB_MODE_CONTINUOUS		0x02U	/* continuous transfer mode */
/* Specification of start transfer disable/enable (CBnSCE) */
#define	_00_CSIB_STARTTRG_INVALID		0x00U	/* communication start trigger invalid */
#define	_01_CSIB_STARTTRG_VALID			0x01U	/* communication start trigger valid */

/*
	CSIBn control register 1 (CBnCTL1)
*/
/* Specification of data transmission/reception timing in relation to SCKBn (CBnCKP, CBnDAP) */
#define	_00_CSIB_DATA_TIMING1			0x00U	/* communication type 1 */
#define	_08_CSIB_DATA_TIMING2			0x08U	/* communication type 2 */
#define	_10_CSIB_DATA_TIMING3			0x10U	/* communication type 3 */
#define	_18_CSIB_DATA_TIMING4			0x18U	/* communication type 4 */
/* Specification of input clock (CBnCKS2 - CBnCKS0) */
#define	_00_CSIB_CLOCK_1			0x00U	/* fXX /2 */
#define	_01_CSIB_CLOCK_2			0x01U	/* fXX/4 */
#define	_02_CSIB_CLOCK_3			0x02U	/* fXX /8 */	
#define	_03_CSIB_CLOCK_4			0x03U	/* fXX /16 */
#define	_04_CSIB_CLOCK_5			0x04U	/* fXX /32 */
#define	_05_CSIB_CLOCK_6			0x05U	/* fXX /64 */
#define	_06_CSIB_CLOCK_7			0x06U	/* fBRGm */
#define	_07_CSIB_CLOCK_EXT			0x07U	/* external clock SCKBn */

/*
	CSIBn control register 2 (CBnCTL2)
*/
/* Serial register bit length (CBnCL3,CBnCL2,CBnCL1,CBnCL0) */
#define	_00_CSIB_DATA_LENGTH_8			0x00U	/* 8 bits */
#define	_01_CSIB_DATA_LENGTH_9			0x01U	/* 9 bits */
#define	_02_CSIB_DATA_LENGTH_10			0x02U	/* 10 bits */
#define	_03_CSIB_DATA_LENGTH_11			0x03U	/* 11 bits */
#define	_04_CSIB_DATA_LENGTH_12			0x04U	/* 12 bits */
#define	_05_CSIB_DATA_LENGTH_13			0x05U	/* 13 bits */
#define	_06_CSIB_DATA_LENGTH_14			0x06U	/* 14 bits */
#define	_07_CSIB_DATA_LENGTH_15			0x07U	/* 15 bits */
#define	_08_CSIB_DATA_LENGTH_16			0x08U	/* 16 bits */

/*
	CSIBn status register (CBnSTR)
*/
/* Communication status flag (CBnTSF) */
#define	_00_CSIB_COMMUNICATION_STOP		0x00U	/* communication stopped */
#define	_80_CSIB_COMMUNICATING			0x80U	/* communicating */
/* Overrun error flag (CBnOVE) */
#define	_00_CSIB_OVERRUN_NONE			0x00U	/* no overrun */
#define	_01_CSIB_OVERRUN			0x01U	/* overrun */

/*
	BRGm prescaler mode registers (PRSMm)
*/
/* Baud rate output(BGCEm) */
#define	_00_CSIB_FBRGM_DISABLE			0x00U	/* baudrate output disabled */
#define	_10_CSIB_FBRGM_ENABLE			0x10U	/* baudrate output enabled */
/* Input clock selection (BGCSm1,BGCSm0) */
#define	_00_CSIB_FBGCS_0			0x00U	/* fXX */	
#define	_01_CSIB_FBGCS_1			0x01U	/* fXX/2 */
#define	_02_CSIB_FBGCS_2			0x02U	/* fXX/4 */
#define	_03_CSIB_FBGCS_3			0x03U	/* fXX/8 */
#define	CB4RIC		UA0RIC
#define	CB4TIC		UA0TIC
#define	CB0RIC		IICIC1

/*
	IIC control register (IICCn)
*/
/* IIC operation enable	(IICEn)	*/
#define	_80_IIC_OPERATION			0x80U
#define	_00_IIC_OPERATION_DISABLE		0x00U	/* stop operation */
#define	_80_IIC_OPERATION_ENABLE		0x80U	/* enable operation */
/* Exit	from communications (LRELn)	*/
#define	_40_IIC_COMMUNICATION			0x40U
#define	_00_IIC_COMMUNICATION_NORMAL		0x00U	/* normal operation	*/
#define	_40_IIC_COMMUNICATION_EXIT		0x40U	/* exit	from current communication */
/* Wait	cancellation (WRELn) */
#define	_20_IIC_WAITCANCEL			0x20U
#define	_00_IIC_WAIT_NOTCANCEL			0x00U	/* do not cancel wait */
#define	_20_IIC_WAIT_CANCEL			0x20U	/* cancel wait */
/* Generation of interrupt when	stop condition (SPIEn) */
#define	_10_IIC_STOPINT				0x10U
#define	_00_IIC_STOPINT_DISABLE			0x00U	/* disable */
#define	_10_IIC_STOPINT_ENABLE			0x10U	/* enable */
/* Wait	and interrupt generation (WTIMn) */
#define	_08_IIC_WAITINT				0x08U
#define	_00_IIC_WAITINT_CLK8FALLING		0x00U	/* generate at the eighth clock falling edge */
#define	_08_IIC_WAITINT_CLK9FALLING		0x08U	/* generated at the ninth clock falling edge */
/* Acknowledgement control (ACKEn) */
#define	_04_IIC_ACK				0x04
#define	_00_IIC_ACK_DISABLE			0x00U	/* disable acknowledgement */
#define	_04_IIC_ACK_ENABLE			0x04U	/* enable acknowledgement */
/* Start condition trigger (STTn) */
#define	_02_IIC_STARTCONDITION			0x02U
#define	_00_IIC_START_NOTGENERATE		0x00U	/* do not generate start condition */
#define	_02_IIC_START_GENERATE			0x02U	/* generate start condition */
/* Stop	condition trigger (SPTn) */
#define	_01_IIC_STOPCONDITION			0x01U
#define	_00_IIC_STOP_NOTGENERATE		0x00U	/* do not generate stop condition */
#define	_01_IIC_STOP_GENERATE			0x01U	/* generate stop condition */

/*
	IIC Status Register (IICSn)
*/
/* Master device status (MSTSn) */
#define	_80_IIC_MASTERSTATUS			0x80U
#define	_00_IIC_STATUS_NOTMASTER		0x00U	/* slave device status or communication standby status */
#define	_80_IIC_STATUS_MASTER			0x80U	/* master device communication status */
/* Detection of arbitration loss (ALDn) */
#define	_40_IIC_ARBITRATION			0x40U
#define	_00_IIC_ARBITRATION_NO			0x00U	/* arbitration win or no arbitration */
#define	_40_IIC_ARBITRATION_LOSS		0x40U	/* arbitration loss */
/* Detection of extension code reception (EXCn) */
#define	_20_IIC_EXTENSIONCODE			0x20U
#define	_00_IIC_EXTCODE_NOT			0x00U	/* extension code not received */
#define	_20_IIC_EXTCODE_RECEIVED		0x20U	/* extension code received */
/* Detection of matching addresses (COIn) */
#define	_10_IIC_ADDRESSMATCH			0x10U
#define	_00_IIC_ADDRESS_NOTMATCH		0x00U	/* addresses do not match */
#define	_10_IIC_ADDRESS_MATCH			0x10U	/* addresses match */
/* Detection of transmit/receive status	(TRCn) */
#define	_08_IIC_STATUS				0x08U
#define	_00_IIC_STATUS_RECEIVE			0x00U	/* receive status */
#define	_08_IIC_STATUS_TRANSMIT			0x08U	/* transmit status */
/* Detection of acknowledge signal (ACKDn) */
#define	_04_IIC_ACKDETECTION			0x04U
#define	_00_IIC_ACK_NOTDETECTED			0x00U	/* ACK signal was not detected */
#define	_04_IIC_ACK_DETECTED			0x04U	/* ACK signal was detected */
/* Detection of start condition (STDn) */
#define	_02_IIC_STARTDETECTION			0x02U
#define	_00_IIC_START_NOTDETECTED		0x00U	/* start condition not detected */
#define	_02_IIC_START_DETECTED			0x02U	/* start condition detected */
/* Detection of stop condition (SPDn) */
#define	_01_IIC_STOPDETECTION			0x01U
#define	_00_IIC_STOP_NOTDETECTED		0x00U	/* stop	condition not detected */
#define	_01_IIC_STOP_DETECTED			0x01U	/* stop	condition detected */

/*
	IIC	Flag Register (IICFn)
*/
/* STTn	clear flag (STCFn) */
#define	_80_IIC_STARTFLAG			0x80U
#define	_00_IIC_STARTFLAG_GENERATE		0x00U	/* generate start condition */
#define	_80_IIC_STARTFLAG_UNSUCCESSFUL		0x80U	/* start condition generation unsuccessful */
/* IIC bus status flag (IICBSYn)	*/
#define	_40_IIC_BUSSTATUS			0x40U
#define	_00_IIC_BUS_RELEASE			0x00U	/* bus release status */
#define	_40_IIC_BUS_COMMUNICATION		0x40U	/* bus communication status */
/* Initial start enable trigger (STCENn)	*/
#define	_02_IIC_STARTWITHSTOP			0x02U
#define	_00_IIC_START_WITHSTOP			0x00U	/* generation of a start condition upon detection of a stop condition */
#define	_02_IIC_START_WITHOUTSTOP		0x02U	/* generation of a start condition without detecting a stop condition */
/* Communication reservation function disable bit (IICRSVn) */
#define	_01_IIC_RESERVATION			0x01U
#define	_00_IIC_RESERVATION_ENABLE		0x00U	/* enable communication reservation */
#define	_01_IIC_RESERVATION_DISABLE		0x01U	/* disable communication reservation */

/*
	IIC clock selection register (IICCLn)
*/
#define _00_IICCL_INITIALVALUE 				0x00U
/* Detection of SCL0n pin level (CLDn) */
#define	_20_IIC_SCLLEVEL				0x20U
#define	_00_IIC_SCL_LOW					0x00U	/* clock line at low level */
#define	_20_IIC_SCL_HIGH				0x20U	/* clock line at high level */
/* Detection of SDA0 pin level (DADn) */
#define	_10_IIC_SDALEVEL				0x10U
#define	_00_IIC_SDA_LOW					0x00U	/* data	line at low level */
#define	_10_IIC_SDA_HIGH				0x10U	/* data	line at high level */
/* Operation mode switching (SMCn) */
#define	_08_IIC_OPERATIONMODE				0x08U
#define	_00_IIC_MODE_STANDARD				0x00U	/* operates in standard mode */
#define	_08_IIC_MODE_HIGHSPEED				0x08U	/* operates in high-speed mode */
/* Digital filter operation control (DFCn) */
#define	_04_IIC_DIGITALFILTER				0x04U
#define	_00_IIC_FILTER_OFF				0x00U	/* digital filter off */
#define	_04_IIC_FILTER_ON				0x04U	/* digital filter on */
/* Operation mode switching (CLn1, CLn0) */
#define	_03_IIC_CLOCKSELECTION				0x03U
/*	Combine of (CLn1, CLn0)*/
#define	_00_IIC_CLOCK0					0x00U
#define	_01_IIC_CLOCK1					0x01U
#define	_02_IIC_CLOCK2					0x02U
#define	_03_IIC_CLOCK3					0x03U

/*
	IIC division clock select register (OCKSn)
*/
#define	_10_IIC_SELECTED0				0x10U
#define	_11_IIC_SELECTED1				0x11U
#define	_12_IIC_SELECTED2				0x12U
#define	_13_IIC_SELECTED3				0x13U
#define	_18_IIC_SELECTED4				0x18U

/*
	IIC function expansion register	0 (IICXn)
*/
/* IIC clock expension (CLXn) */
#define	_01_IIC_CLOCKEXPENSION				0x01U
#define	_00_IIC_EXPENSION0				0x00U
#define	_01_IIC_EXPENSION1				0x01U
#define	_80_ADDRESS_COMPLETE				0x80U
#define	_00_IIC_MASTER_FLAG_CLEAR			0x00U
#define	IICIC2		UA1RIC
#define	IICIC0		UA2RIC
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
/* Selection of 8-bit counter output clock (UA1BRS7~UA1BRS0) */
#define	_D0_UARTA1_BASECLK_DIVISION		0xD0U	/* 4 ~ 255 */ //9600
#define	_11_UARTA1_BASECLK_DIVISION		0x11U	/* 4 ~ 255 */ //115200
enum TransferMode 
{
	SEND, RECEIVE
};

void rt_hw_uart_init(void);

#endif
