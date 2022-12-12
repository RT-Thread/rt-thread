/* Auto-generated config file hpl_mcan_config.h */
#ifndef HPL_MCAN_CONFIG_H
#define HPL_MCAN_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

#ifndef CONF_CAN1_ENABLED
#define CONF_CAN1_ENABLED 1
#endif
// <h> Basic Configuration

// <o> CAN Mode Enable
// <i> decide whether enable CAN FD mode
// <0=> ISO11898_1
// <1=> FD
// <id> can_cccr_niso
#ifndef CONF_CAN1_CCCR_NISO
#define CONF_CAN1_CCCR_NISO 0
#endif

// </h>

// <h> Normal Bit Timing and Prescaler Configuration

// <o> Baud Rate Prescaler <1-512>
// <i> The value by which the oscillator frequency is divided for generating the CAN time quanta. CAN time quantum (tq) = (This value) x CAN core clock cycles (tcore clock)
// <id> can_nbtp_nbrp
#ifndef CONF_CAN1_NBTP_NBRP
#define CONF_CAN1_NBTP_NBRP 4
#endif

// <o> time segment before sample point <2-256>
// <i> The duration of time segment = (This value) x CAN time quantum (tq)
// <id> can_nbtp_ntseg1
#ifndef CONF_CAN1_NBTP_NTSEG1
#define CONF_CAN1_NBTP_NTSEG1 31
#endif

// <o> time segment after sample point <2-128>
// <i> The duration of time segment = (This value) x CAN time quantum (tq)
// <id> can_nbtp_ntseg2
#ifndef CONF_CAN1_NBTP_NTSEG2
#define CONF_CAN1_NBTP_NTSEG2 8
#endif

// <o> Data (Re)Syncronization Jump Width <1-128>
// <i> The duration of a synchronization jump = (This value) x CAN time quantum (tq)
// <id> can_nbtp_nsjw
#ifndef CONF_CAN1_NBTP_NSJW
#define CONF_CAN1_NBTP_NSJW 10
#endif

// </h>
// <h> Data Bit Timing and Prescaler Configuration

// <o> Data Baud Rate Prescaler <1-32>
// <i> The value by which the peripheral clock is divided for generating the bit time quanta. CAN time quantum (tq) = (This value) x CAN core clock cycles (tcore clock)
// <id> can_dbtp_dbrp
#ifndef CONF_CAN1_DBTP_DBRP
#define CONF_CAN1_DBTP_DBRP 1
#endif

// <o> Data time segment before sample point <2-32>
// <i> The duration of time segment = (This value) x CAN time quantum (tq)
// <id> can_dbtp_dtseg1
#ifndef CONF_CAN1_DBTP_DTSEG1
#define CONF_CAN1_DBTP_DTSEG1 31
#endif

// <o> Data time segment after sample point <1-16>
// <i> The duration of time segment = (This value) x CAN time quantum (tq)
// <id> can_dbtp_dtseg2
#ifndef CONF_CAN1_DBTP_DTSEG2
#define CONF_CAN1_DBTP_DTSEG2 8
#endif

// <o> Data (Re)Syncronization Jump Width <1-8>
// <i> The duration of a synchronization jump = (This value) x CAN time quantum (tq)
// <id> can_dbtp_dsjw
#ifndef CONF_CAN1_DBTP_DSJW
#define CONF_CAN1_DBTP_DSJW 4
#endif

// <q> Transceiver Delay Compensation Enable
// <i> Transceiver Delay Compensation Enable
// <id> can_dbtp_tdc
#ifndef CONF_CAN1_DBTP_TDC
#define CONF_CAN1_DBTP_TDC 0
#endif

// <o> Transceiver Delay Compensation Offset <0-127>
// <i> Transceiver Delay Compensation Offset
// <id> can_tdcr_tdco
#ifndef CONF_CAN1_TDCR_TDCO
#define CONF_CAN1_TDCR_TDCO 11
#endif

// <o> Transmitter Delay Compensation Filter <0-127>
// <i> Transmitter Delay Compensation Filter
// <id> can_tdcr_tdcf
#ifndef CONF_CAN1_TDCR_TDCF
#define CONF_CAN1_TDCR_TDCF 11
#endif

// </h>

// <h> RX FIFO Configuration

// <o> Operation Mode
// <i> Select Operation Mode
// <0=> blocking mode
// <1=> overwrite mode
// <id> can_rxf0c_f0om
#ifndef CONF_CAN1_RXF0C_F0OM
#define CONF_CAN1_RXF0C_F0OM 0
#endif

// <o> Watermark <0-64>
// <i> Watermark, 0 for disable watermark interrupt
// <id> can_rxf0c_f0wm
#ifndef CONF_CAN1_RXF0C_F0WM
#define CONF_CAN1_RXF0C_F0WM 0
#endif

// <o> Size <0-64>
// <i> Number of Rx FIFO 0 element
// <id> can_rxf0c_f0s
#ifndef CONF_CAN1_RXF0C_F0S
#define CONF_CAN1_RXF0C_F0S 32
#endif

// <o> Data Field Size
// <i> Rx FIFO 0 Data Field Size
// <0=> 8 byte data field.
// <1=> 12 byte data field.
// <2=> 16 byte data field.
// <3=> 20 byte data field.
// <4=> 24 byte data field.
// <5=> 32 byte data field.
// <6=> 48 byte data field.
// <7=> 64 byte data field.
// <id> can_rxesc_f0ds
#ifndef CONF_CAN1_RXESC_F0DS
#define CONF_CAN1_RXESC_F0DS 0
#endif

/* Bytes size for CAN FIFO 0 element, plus 8 bytes for R0,R1 */
#undef CONF_CAN1_F0DS
#define CONF_CAN1_F0DS                                                                                                 \
	((CONF_CAN1_RXESC_F0DS < 5) ? ((CONF_CAN1_RXESC_F0DS << 2) + 16) : (40 + ((CONF_CAN1_RXESC_F0DS % 5) << 4)))

// </h>

// <h> TX FIFO Configuration

// <o> Transmit FIFO Size <0-32>
// <i> Number of Tx Buffers used for Tx FIFO
// <id> can_txbc_tfqs
#ifndef CONF_CAN1_TXBC_TFQS
#define CONF_CAN1_TXBC_TFQS 32
#endif

// <o> Tx Buffer Data Field Size
// <i> Tx Buffer Data Field Size
// <0=> 8 byte data field.
// <1=> 12 byte data field.
// <2=> 16 byte data field.
// <3=> 20 byte data field.
// <4=> 24 byte data field.
// <5=> 32 byte data field.
// <6=> 48 byte data field.
// <7=> 64 byte data field.
// <id> can_txesc_tbds
#ifndef CONF_CAN1_TXESC_TBDS
#define CONF_CAN1_TXESC_TBDS 0
#endif

/* Bytes size for CAN Transmit Buffer element, plus 8 bytes for R0,R1 */
#undef CONF_CAN1_TBDS
#define CONF_CAN1_TBDS                                                                                                 \
	((CONF_CAN1_TXESC_TBDS < 5) ? ((CONF_CAN1_TXESC_TBDS << 2) + 16) : (40 + ((CONF_CAN1_TXESC_TBDS % 5) << 4)))

// </h>

// <h> TX Event Configuration

// <o> Watermark <0-32>
// <i> Watermark, 0 for disable watermark interrupt
// <id> can_txefc_efwm
#ifndef CONF_CAN1_TXEFC_EFWM
#define CONF_CAN1_TXEFC_EFWM 0
#endif

// <o> Size <0-32>
// <i> Number of Event FIFO element
// <id> can_txefc_efs
#ifndef CONF_CAN1_TXEFC_EFS
#define CONF_CAN1_TXEFC_EFS 32
#endif

// </h>

// <h> Filter Configuration

// <o> Accept Non-matching Frames Standard
// <i> Defines how received messages with 11-bit IDs that do not match any
// <i> element of the filter list are treated.
// <0=> Accept in Rx FIFO 0
// <1=> Accept in Rx FIFO 1
// <2=> Reject
// <id> can_gfc_anfs
#ifndef CONF_CAN1_GFC_ANFS
#define CONF_CAN1_GFC_ANFS 2
#endif

// <o> Accept Non-matching Frames Extended
// <i> Defines how received messages with 29-bit IDs that do not match any
// <i> element of the filter list are treated.
// <0=> Accept in Rx FIFO 0
// <1=> Accept in Rx FIFO 1
// <2=> Reject
// <id> can_gfc_anfe
#ifndef CONF_CAN1_GFC_ANFE
#define CONF_CAN1_GFC_ANFE 2
#endif

// <o> Reject Remote Frames Standard
// <i> Defines how received remote frames with 11-bit standard IDs.
// <0=> Filter remote frames with 11-bit standard IDs
// <1=> Reject all remote frames with 11-bit standard IDs
// <id> can_gfc_rrfs
#ifndef CONF_CAN1_GFC_RRFS
#define CONF_CAN1_GFC_RRFS 0
#endif

// <o> Reject Remote Frames Extended
// <i> Defines how received remote frames with 29-bit standard IDs.
// <0=> Filter remote frames with 29-bit standard IDs
// <1=> Reject all remote frames with 29-bit standard IDs
// <id> can_gfc_rrfe
#ifndef CONF_CAN1_GFC_RRFE
#define CONF_CAN1_GFC_RRFE 0
#endif

// <o> Number of standard Message ID filter elements <0-128>
// <i> Number of standard Message ID filter elements
// <id> can_sidfc_lss
#ifndef CONF_CAN1_SIDFC_LSS
#define CONF_CAN1_SIDFC_LSS 128
#endif

// <o> Number of Extended Message ID filter elements <0-64>
// <i> Number of Extended Message ID filter elements
// <id> can_xidfc_lss
#ifndef CONF_CAN1_XIDFC_LSS
#define CONF_CAN1_XIDFC_LSS 64
#endif

// <o> Extended ID Mask <0x0000-0x1FFFFFFF>
// <i> For acceptance filtering of extended frames the Extended ID AND Mask is
// <i> ANDed with the Message ID of a received frame. Intended for masking of
// <i> 29-bit IDs in SAE J1939. With the reset value of all bits set to one the
// <i> mask is not active.
// <id> can_xidam_eidm
#ifndef CONF_CAN1_XIDAM_EIDM
#define CONF_CAN1_XIDAM_EIDM 0x0
#endif

// </h>

// <h> Interrupt Configuration

// <q> Error Warning
// <i> Indicates whether to not disable CAN error warning interrupt
// <id> can_ie_ew
#ifndef CONF_CAN1_IE_EW
#define CONF_CAN1_IE_EW 1
#endif

// <q> Error Active
// <i> Indicates whether to not disable CAN error active interrupt
// <id> can_ie_ea
#ifndef CONF_CAN1_IE_EA
#define CONF_CAN1_IE_EA 1
#endif

// <q> Error Passive
// <i> Indicates whether to not disable CAN error passive interrupt
// <id> can_ie_ep
#ifndef CONF_CAN1_IE_EP
#define CONF_CAN1_IE_EP 1
#endif

// <q> Bus Off
// <i> Indicates whether to not disable CAN bus off interrupt
// <id> can_ie_bo
#ifndef CONF_CAN1_IE_BO
#define CONF_CAN1_IE_BO 1
#endif

// <q> Data Overrun
// <i> Indicates whether to not disable CAN data overrun interrupt
// <id> can_ie_do
#ifndef CONF_CAN1_IE_DO
#define CONF_CAN1_IE_DO 1
#endif

// </h>

#ifndef CONF_CAN1_CCCR_REG
#define CONF_CAN1_CCCR_REG (CONF_CAN1_CCCR_NISO << MCAN_CCCR_NISO_Pos)
#endif

#ifndef CONF_CAN1_NBTP_REG
#define CONF_CAN1_NBTP_REG                                                                                             \
	MCAN_NBTP_NBRP(CONF_CAN1_NBTP_NBRP - 1) | MCAN_NBTP_NTSEG1(CONF_CAN1_NBTP_NTSEG1 - 1)                              \
	    | MCAN_NBTP_NTSEG2(CONF_CAN1_NBTP_NTSEG2 - 1) | MCAN_NBTP_NSJW(CONF_CAN1_NBTP_NSJW - 1)
#endif

#ifndef CONF_CAN1_DBTP_REG
#define CONF_CAN1_DBTP_REG                                                                                             \
	(CONF_CAN1_DBTP_TDC << MCAN_DBTP_TDC_Pos) | MCAN_DBTP_DBRP(CONF_CAN1_DBTP_DBRP - 1)                                \
	    | MCAN_DBTP_DTSEG1(CONF_CAN1_DBTP_DTSEG1 - 1) | MCAN_DBTP_DTSEG2(CONF_CAN1_DBTP_DTSEG2 - 1)                    \
	    | MCAN_DBTP_DSJW(CONF_CAN1_DBTP_DSJW - 1)
#endif

#ifndef CONF_CAN1_TDCR_REG
#define CONF_CAN1_TDCR_REG MCAN_TDCR_TDCF(CONF_CAN1_TDCR_TDCF) | MCAN_TDCR_TDCO(CONF_CAN1_TDCR_TDCO)
#endif

#ifndef CONF_CAN1_RXF0C_REG
#define CONF_CAN1_RXF0C_REG                                                                                            \
	(CONF_CAN1_RXF0C_F0OM << MCAN_RXF0C_F0OM_Pos) | MCAN_RXF0C_F0WM(CONF_CAN1_RXF0C_F0WM)                              \
	    | MCAN_RXF0C_F0S(CONF_CAN1_RXF0C_F0S)
#endif

#ifndef CONF_CAN1_RXESC_REG
#define CONF_CAN1_RXESC_REG MCAN_RXESC_F0DS(CONF_CAN1_RXESC_F0DS)
#endif

#ifndef CONF_CAN1_TXESC_REG
#define CONF_CAN1_TXESC_REG MCAN_TXESC_TBDS(CONF_CAN1_TXESC_TBDS)
#endif

#ifndef CONF_CAN1_TXBC_REG
#define CONF_CAN1_TXBC_REG MCAN_TXBC_TFQS(CONF_CAN1_TXBC_TFQS)
#endif

#ifndef CONF_CAN1_TXEFC_REG
#define CONF_CAN1_TXEFC_REG MCAN_TXEFC_EFWM(CONF_CAN1_TXEFC_EFWM) | MCAN_TXEFC_EFS(CONF_CAN1_TXEFC_EFS)
#endif

#ifndef CONF_CAN1_GFC_REG
#define CONF_CAN1_GFC_REG                                                                                              \
	MCAN_GFC_ANFS(CONF_CAN1_GFC_ANFS) | MCAN_GFC_ANFE(CONF_CAN1_GFC_ANFE) | (CONF_CAN1_GFC_RRFS << MCAN_GFC_RRFS_Pos)  \
	    | (CONF_CAN1_GFC_RRFE << MCAN_GFC_RRFE_Pos)
#endif

#ifndef CONF_CAN1_SIDFC_REG
#define CONF_CAN1_SIDFC_REG MCAN_SIDFC_LSS(CONF_CAN1_SIDFC_LSS)
#endif

#ifndef CONF_CAN1_XIDFC_REG
#define CONF_CAN1_XIDFC_REG MCAN_XIDFC_LSE(CONF_CAN1_XIDFC_LSS)
#endif

#ifndef CONF_CAN1_XIDAM_REG
#define CONF_CAN1_XIDAM_REG MCAN_XIDAM_EIDM(CONF_CAN1_XIDAM_EIDM)
#endif

#ifndef CONF_CAN0_IE_REG
#define CONF_CAN0_IE_REG                                                                                               \
	(CONF_CAN1_IE_EW << MCAN_IR_EW_Pos) | (CONF_CAN1_IE_EA << MCAN_IR_EP_Pos) | (CONF_CAN1_IE_EP << MCAN_IR_EP_Pos)    \
	    | (CONF_CAN1_IE_BO << MCAN_IR_BO_Pos) | (CONF_CAN1_IE_DO << MCAN_IR_RF0L_Pos)
#endif

// <<< end of configuration section >>>

#endif // HPL_MCAN_CONFIG_H
