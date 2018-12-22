/*
 * @brief UART ROM API declarations and functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "error.h"
#include "hw_uart_rom_api.h"

#define UART_IDLE_FIX	/* Remove once IDLE problem is fixed */

/* UART Driver internal data structure */
typedef struct {
	void            *pUserData;		/* Pointer to user data */
	UART_REGS_T     *pREGS;			/* Pointer to Registers */
	UART_DATA_T xfer[2];			/* TX/RX transfer data */
#ifdef UART_IDLE_FIX
	uint32_t    dly;				/* Delay to count 1 bit time; REMOVE: when H/W is fixed */
#endif
	void(*cbTable[UART_CB_RESERVED]) (UART_HANDLE_T, UART_EVENT_T, void *);	/* Call-back index table */
} UART_DRIVER_T;

/* PRIVATE: Division logic to divide without integer overflow */
static uint32_t _UART_DivClk(uint32_t pclk, uint32_t m)
{
	uint32_t q, r, u = pclk >> 24, l = pclk << 8;
	m = m + 256;
	q = (1 << 24) / m;
	r = (1 << 24) - (q * m);
	return ((q * u) << 8) + (((r * u) << 8) + l) / m;
}

/* PRIVATE: Get highest Over sampling value */
static uint32_t _UART_GetHighDiv(uint32_t val, uint8_t strict)
{
	int32_t i, max = strict ? 16 : 5;
	for (i = 16; i >= max; i--) {
		if (!(val % i)) {
			return i;
		}
	}
	return 0;
}

/* PRIVATE: Queue a transfer in UART */
static ErrorCode_t _UART_Xfer(UART_DRIVER_T *pUART, void *buff, uint16_t len, uint8_t op)
{
	UART_DATA_T *xfr = &pUART->xfer[op];

	/* Xfer of 0 bytes in a UART should always be successful */
	if (!len) {
		return LPC_OK;
	}

	/* Check if a Xfer is alredy in progress */
	if (xfr->count > xfr->offset) {
		return ERR_BUSY;
	}

	xfr->buf = (void *) buff;
	xfr->count = len;
	xfr->offset = 0;
	xfr->state = UART_ST_BUSY;
	if (!op) {
		pUART->pREGS->INTENSET = UART_INT_TXRDY;
	}
	else {
		pUART->pREGS->INTENSET = UART_INT_RXRDY | UART_INT_FRMERR | UART_INT_RXNOISE | UART_INT_START | UART_INT_OVR;
	}

	return LPC_OK;
}

/* Calculate error difference */
static int32_t _CalcErr(uint32_t n, uint32_t d, uint32_t *prev)
{
	uint32_t err = n - (n / d) * d;
	uint32_t herr = ((n / d) + 1) * d - n;
	if (herr < err) {
		err = herr;
	}

	if (*prev <= err) {
		return 0;
	}
	*prev = err;
	return (herr == err) + 1;
}

/* Calculate the base DIV value */
static ErrorCode_t _UART_CalcDiv(UART_BAUD_T *ub)
{
	int32_t i = 0;
	uint32_t perr = ~0UL;

	if (!ub->div) {
		i = ub->ovr ? ub->ovr : 16;
	}

	for (; i > 4; i--) {
		int32_t tmp = _CalcErr(ub->clk, ub->baud * i, &perr);

		/* Continue when no improvement seen in err value */
		if (!tmp) {
			continue;
		}

		ub->div = tmp - 1;
		if (ub->ovr == i) {
			break;
		}
		ub->ovr = i;
	}

	if (!ub->ovr) {
		return ERR_UART_BAUDRATE;
	}

	ub->div += ub->clk / (ub->baud * ub->ovr);
	if (!ub->div) {
		return ERR_UART_BAUDRATE;
	}

	ub->baud = ub->clk / (ub->div * ub->ovr);
	return LPC_OK;
}

/* Calculate the best MUL value */
static void _UART_CalcMul(UART_BAUD_T *ub)
{
	uint32_t m, perr = ~0UL, pclk = ub->clk, ovr = ub->ovr;

	/* If clock is UART's base clock calculate only the divider */
	for (m = 0; m < 256; m++) {
		uint32_t ov = ovr, x, v, tmp;

		/* Get clock and calculate error */
		x = _UART_DivClk(pclk, m);
		tmp = _CalcErr(x, ub->baud, &perr);
		v = (x / ub->baud) + tmp - 1;

		/* Update if new error is better than previous best */
		if (!tmp || (ovr && (v % ovr)) ||
			(!ovr && ((ov = _UART_GetHighDiv(v, ovr)) == 0))) {
			continue;
		}

		ub->ovr = ov;
		ub->mul = m;
		ub->clk = x;
		ub->div = tmp - 1;
	}
}

/* PRIVATE: Invoke UART Call back functions */
static void _UART_InvokeCB(UART_DRIVER_T *pUART, UART_EVENT_T event, void *arg)
{
	void (*cbfn)(UART_HANDLE_T, UART_EVENT_T, void *);
	cbfn = pUART->cbTable[(uint32_t) event >> 1];
	if (cbfn != NULL) {
		cbfn((UART_HANDLE_T) pUART, event, arg);
	}
}

/* PRIVATE: Handler for data transfers */
static void _UART_HandleTxRx(UART_HANDLE_T hUART, UART_EVENT_T event, void *arg)
{
	UART_DATA_T *dat = (UART_DATA_T *) arg;
	UART_DRIVER_T *pUART = (UART_DRIVER_T *) hUART;
	uint16_t *buf16 = dat->buf;
	uint8_t *buf8 = dat->buf;

	/* Transmit data */
	if (event == UART_TX_DATA) {
		while (dat->count && (pUART->pREGS->INTSTAT & UART_INT_TXRDY)) {
			if (dat->dwidth) {
				pUART->pREGS->TXDAT = *buf16++;
			}
			else {
				pUART->pREGS->TXDAT = *buf8++;
			}
			dat->count--;
		}
		return;
	}

	/* Receive data */
	while (dat->count && (pUART->pREGS->INTSTAT & UART_INT_RXRDY)) {
		if (dat->dwidth) {
			*buf16++ = pUART->pREGS->RXDAT & 0x1FF;
		}
		else {
			*buf8++ = pUART->pREGS->RXDAT & 0xFF;
		}
		dat->count--;
	}
}

/* Handle UART Receive event */
static int32_t _UART_HandleXfer(UART_DRIVER_T *pUART, uint8_t op)
{
	UART_DATA_T dat;
	UART_DATA_T *xfr = &pUART->xfer[op];

	/* See if the transfer is already complete */
	if (xfr->offset >= xfr->count) {
		return 2;
	}

	/* Fill the buffer data structure */
	dat.count  = xfr->count - xfr->offset;
	dat.dwidth = ((pUART->pREGS->CFG >> 2) & 3) > 1;
	if (dat.dwidth) {
		dat.buf = &((uint16_t *) xfr->buf)[xfr->offset];
	}
	else {
		dat.buf = &((uint8_t *) xfr->buf)[xfr->offset];
	}

	if (!xfr->offset && xfr->count) {
		_UART_InvokeCB(pUART, UART_TX_START, xfr);
	}

	pUART->cbTable[UART_CB_DATA]((UART_HANDLE_T) pUART, (UART_EVENT_T) (UART_TX_DATA + op), &dat);
	xfr->offset = (xfr->count - dat.count);

	if (xfr->offset >= xfr->count) {
		if (!op) {
			pUART->pREGS->INTENCLR = UART_INT_TXRDY;
		}
		else {
			pUART->pREGS->INTENCLR = UART_INT_RXRDY;
		}

		_UART_InvokeCB(pUART, (UART_EVENT_T) (UART_TX_DONE + op), xfr);
		if (xfr->state == UART_ST_BUSY) {
			xfr->state = UART_ST_DONE;
		}
		return 1;
	}
	return 0;
}

/* STOP Receive under progress */
static void _UART_StopRx(UART_HANDLE_T hUART)
{
	UART_DRIVER_T *pUART = (UART_DRIVER_T *) hUART;
	UART_DATA_T *rx = &pUART->xfer[1];
	volatile uint16_t *idx = (volatile uint16_t *) &rx->offset;

	if (*idx >= rx->count) {
		return;
	}

	/* Disable further receive interrupts */
	pUART->pREGS->INTENCLR = UART_INT_RXRDY;
	rx->count = *idx;
	_UART_InvokeCB(pUART, UART_RX_DONE, rx);
}

/* EXPROTED API: Returns memory required for UART ROM driver */
uint32_t UART_GetMemSize(void)
{
	return sizeof(UART_DRIVER_T);
}

/* EXPORTED API: Calculate UART Baudrate divisors */
ErrorCode_t UART_CalculateBaud(UART_BAUD_T *ub)
{
	if (!ub->mul) {
		_UART_CalcMul(ub);
	}

	return _UART_CalcDiv(ub);
}

/* EXPORTED API: UART Initialization function */
UART_HANDLE_T UART_Init(void *mem, uint32_t base_addr, void *args)
{
	UART_DRIVER_T *pUART;

	/* Check if the memory is word aligned */
	if ((uint32_t) mem & 0x3) {
		return NULL;
	}

	/* Assign memory provided by application */
	pUART = (UART_DRIVER_T *) mem;
	memset(pUART, 0, sizeof(UART_DRIVER_T));

	/* Assign the base address */
	pUART->pREGS = (UART_REGS_T *) base_addr;
	pUART->pUserData = args;

	/* Set default handler for TX and RX */
	pUART->cbTable[UART_CB_DATA] = _UART_HandleTxRx;
	return (UART_HANDLE_T) pUART;
}

/* EXPORTED API: Configure UART parameters */
ErrorCode_t UART_Configure(UART_HANDLE_T hUART, const UART_CFG_T *cfg)
{
	UART_DRIVER_T *pUART = (UART_DRIVER_T *) hUART;
	UART_REGS_T *pREGS = pUART->pREGS;

	if (((cfg->cfg & UART_PAR_MASK) == (1 << 4)) ||
		( (cfg->cfg & UART_DATA_MASK) == (3 << 2)) ) {
		return ERR_UART_PARAM;
	}

	/* Enable parity error when parity is enabled */
	if ((cfg->cfg & UART_PAR_MASK) >> 4) {
		pREGS->INTENSET = UART_INT_PARERR;
	}

	if (((int32_t) cfg->div <= 0) || ((int32_t) cfg->ovr <= 0)) {
		return ERR_UART_PARAM;
	}

	pREGS->OSR = (cfg->ovr - 1) & 0x0F;
	pREGS->BRG = (cfg->div - 1) & 0xFFFF;
	pREGS->CFG = UART_CFG_ENABLE | (cfg->cfg & ~UART_CFG_RES);

	/* Enabled RX of BREAK event */
	if (cfg->cfg & UART_CFG_BRKRX) {
		pREGS->INTENSET = UART_INT_BREAK;
	}

	/* Enable CTS interrupt if requested */
	if (cfg->cfg & UART_CFG_CTSEV) {
		pREGS->INTENSET = UART_INT_CTS;
	}

#ifdef UART_IDLE_FIX
	/* REMOVE: if/else block after H/W idle is fixed */
	if (cfg->res > 224) {
		pUART->dly = 3072 * (cfg->res - 224);
	}
	else {
		pUART->dly = cfg->res << 2;
	}
#endif

	return LPC_OK;
}

/* EXPORTED API: UART setup special operation like BREAK etc. */
void UART_SetControl(UART_HANDLE_T hUART, uint32_t cfg)
{
	uint32_t en, dis;
	UART_REGS_T *pREGS = ((UART_DRIVER_T *) hUART)->pREGS;

	/* Get list of enabled and disabled options */
	en  = ((cfg >> 16) & (cfg & 0xFFFF)) << 1;
	dis = ((cfg >> 16) & ~(cfg & 0xFFFF)) << 1;

	/* See if it is RX Stop request */
	if (cfg & UART_RX_STOP) {
		_UART_StopRx(hUART);
	}

	/* See if any IDLEs are enabled */
	if (cfg & (UART_IDLE_MASK << 16)) {
		pREGS->INTENSET = (en >> 1)  & UART_IDLE_MASK;
		pREGS->INTENCLR = (dis >> 1) & UART_IDLE_MASK;
	}

	/* See if it is a request BREAK after TX */
	if (en & UART_CTL_TXDIS) {
		if (en & UART_CTL_TXBRKEN) {
			pREGS->CTL = (pREGS->CTL & ~UART_CTL_RES) | UART_CTL_TXDIS;
			while (!(pREGS->STAT & UART_INT_TXDIS)) {}
#ifdef UART_IDLE_FIX
			if (1) {
				volatile uint32_t dly = ((UART_DRIVER_T *) hUART)->dly;
				while (dly--) {}/* Provide some idling time H/W does not do this */
			}
#endif
		}
		else {
			pREGS->INTENSET = UART_INT_TXDIS;
		}
	}

	/* See if we are releasing break and resume TX operation */
	if ((dis & UART_CTL_TXDIS) && (dis & UART_CTL_TXBRKEN)) {
		pREGS->CTL = pREGS->CTL & ~(UART_CTL_RES | UART_CTL_TXBRKEN);
#ifdef UART_IDLE_FIX
		if (1) {
			volatile uint32_t dly = ((UART_DRIVER_T *) hUART)->dly;
			while (dly--) {}	/* Provide some idling time H/W does not do this */
		}
#endif
	}

	/* Check for autobaud and enable autobaud err interrupt */
	if (en & UART_CTL_AUTOBAUD) {
		pREGS->INTENSET = UART_INT_ABAUDERR;
	}

	pREGS->CTL = ((pREGS->CTL | en) & ~dis) & ~UART_CTL_RES;
}

/* EXPORTED API: Register a call-back function */
ErrorCode_t UART_RegisterCB(UART_HANDLE_T hUART,
							UART_CBINDEX_T idx,
							void (*cb_func)(UART_HANDLE_T, UART_EVENT_T, void *))
{
	if (idx < UART_CB_RESERVED) {
		((UART_DRIVER_T *) hUART)->cbTable[idx] = cb_func;
	}
	else {
		return ERR_UART_PARAM;
	}

	/* Restore internal data handlers when external ones are un-registered */
	if ((idx == UART_CB_DATA) && (cb_func == NULL)) {
		((UART_DRIVER_T *) hUART)->cbTable[idx] = _UART_HandleTxRx;
	}

	return LPC_OK;
}

/* EXPORTED API: UART Event handler */
void UART_Handler(UART_HANDLE_T hUART)
{
	UART_DRIVER_T *pUART = (UART_DRIVER_T *) hUART;
	uint32_t flags = pUART->pREGS->INTENSET & pUART->pREGS->INTSTAT;

	if (flags & UART_INT_TXRDY) {
		_UART_HandleXfer(pUART, 0);
	}

	if (flags & UART_INT_FRMERR) {
		pUART->pREGS->STAT = UART_INT_FRMERR;
		if (pUART->xfer[1].state == UART_ST_BUSY) {
			pUART->xfer[1].state = UART_ST_ERRFRM;
		}
		_UART_InvokeCB(pUART, UART_EV_ERROR, (void *) UART_ERROR_FRAME);
	}

	if (flags & UART_INT_PARERR) {
		pUART->pREGS->STAT = UART_INT_PARERR;
		if (pUART->xfer[1].state == UART_ST_BUSY) {
			pUART->xfer[1].state = UART_ST_ERRPAR;
		}
		_UART_InvokeCB(pUART, UART_EV_ERROR, (void *) UART_ERROR_PARITY);
	}

	if (flags & UART_INT_ABAUDERR) {
		pUART->pREGS->STAT = UART_INT_ABAUDERR;
		if (pUART->xfer[1].state == UART_ST_BUSY) {
			pUART->xfer[1].state = UART_ST_ERR;
		}
		_UART_InvokeCB(pUART, UART_EV_ERROR, (void *) UART_ERROR_AUTOBAUD);
	}

	if (flags & UART_INT_RXNOISE) {
		pUART->pREGS->STAT = UART_INT_RXNOISE;
		if (pUART->xfer[1].state == UART_ST_BUSY) {
			pUART->xfer[1].state = UART_ST_ERRNOISE;
		}
		_UART_InvokeCB(pUART, UART_EV_ERROR, (void *) UART_ERROR_RXNOISE);
	}

	if (flags & UART_INT_OVR) {
		pUART->pREGS->STAT = UART_INT_OVR;
		if (pUART->xfer[1].state == UART_ST_BUSY) {
			pUART->xfer[1].state = UART_ST_ERROVR;
		}
		_UART_InvokeCB(pUART, UART_EV_ERROR, (void *) UART_ERROR_OVERRUN);
	}

	if (flags & UART_INT_RXRDY) {
		_UART_HandleXfer(pUART, 1);
#ifdef UART_IDLE_FIX
		if (1) {
			volatile uint32_t dly = ((UART_DRIVER_T *) hUART)->dly;
			while ((pUART->pREGS->STAT & UART_STAT_RXIDLE) && dly--) {}
		}
#else
		while (pUART->pREGS->STAT & UART_STAT_RXIDLE) {}
#endif
		_UART_InvokeCB(pUART, (UART_EVENT_T) (UART_RX_INPROG + ((pUART->pREGS->STAT >> 1) & 1)), &pUART->xfer[1]);
	}

	if (flags & UART_INT_TXIDLE) {
		_UART_InvokeCB(pUART, UART_EV_EVENT, (void *) UART_EVENT_TXIDLE);
	}

	if (flags & UART_INT_TXDIS) {
		pUART->pREGS->INTENCLR = UART_INT_TXDIS;/* Disable interrupt */
		_UART_InvokeCB(pUART, UART_EV_EVENT, (void *) UART_EVENT_TXPAUSED);
	}

	if (flags & UART_INT_CTS) {
		pUART->pREGS->STAT = UART_INT_CTS;
		_UART_InvokeCB(pUART, UART_EV_EVENT,
					   (void *) ((pUART->pREGS->STAT & UART_STAT_CTS) ? UART_EVENT_CTSHI : UART_EVENT_CTSLO));
	}

	if (flags & UART_INT_BREAK) {
		pUART->pREGS->STAT = UART_INT_BREAK | UART_INT_FRMERR;
		_UART_InvokeCB(pUART, UART_EV_EVENT,
					   (void *) ((pUART->pREGS->STAT & UART_STAT_BREAK) ? UART_EVENT_BREAK : UART_EVENT_NOBREAK));
	}

	if (flags & UART_INT_START) {
		pUART->pREGS->STAT = UART_INT_START;
		_UART_InvokeCB(pUART, UART_RX_START, &pUART->xfer[1]);
	}

}

/* EXPORTED API: UART Transmit API */
ErrorCode_t UART_Tx(UART_HANDLE_T hUART, const void *buff, uint16_t len)
{
	return _UART_Xfer((UART_DRIVER_T *) hUART, (void *) buff, len, 0);
}

/* EXPORTED API: UART Receive API */
ErrorCode_t UART_Rx(UART_HANDLE_T hUART, void *buff, uint16_t len)
{
	return _UART_Xfer((UART_DRIVER_T *) hUART, buff, len, 1);
}

/* EXPORTED API: Flush the TX buffer */
void UART_WaitTX(UART_HANDLE_T hUART)
{
	while (!_UART_HandleXfer(hUART, 0)) {}
}

/* EXPORTED API: Fetch the data from UART into RX buffer */
void UART_WaitRX(UART_HANDLE_T hUART)
{
	UART_REGS_T *pREGS = ((UART_DRIVER_T *) hUART)->pREGS;
	/* See if the data needs to be discarded */
	if (_UART_HandleXfer(hUART, 1) == 2) {
		volatile uint32_t dummy;
		while ((pREGS->STAT & UART_INT_RXRDY) || !(pREGS->STAT & UART_STAT_RXIDLE)) {
			dummy = pREGS->RXDAT;
		}
	}
	while (!_UART_HandleXfer(hUART, 1)) {}
}

/* EXPORTED API: Function to Get the firmware Version */
uint32_t UART_GetDriverVersion(void)
{
	return UART_DRIVER_VERSION;
}

/**
 * @brief	Table of the addresses of all the UART ROM APIs
 * @note	This table of function pointers is the API interface.
 */
const ROM_UART_API_T  uartrom_api = {
	UART_GetMemSize,
	UART_CalculateBaud,
	UART_Init,
	UART_Configure,
	UART_SetControl,
	UART_RegisterCB,
	UART_Handler,
	UART_Tx,
	UART_Rx,
	UART_WaitTX,
	UART_WaitRX,
	UART_GetDriverVersion,
};
