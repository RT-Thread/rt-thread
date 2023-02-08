/*-----------------------------------------------------------------------*/
/* MMC/SDC (in SPI mode) control module  (C)ChaN, 2007                   */
/*-----------------------------------------------------------------------*/
/* Only rcvr_spi(), xmit_spi(), disk_timerproc() and some macros         */
/* are platform dependent.                                               */
/*-----------------------------------------------------------------------*/

/*
 * This file was modified from a sample available from the FatFs
 * web site. It was modified to work with a Luminary Micro
 * EK-LM3S6965 evaluation board.
 *
 * Note that the SSI port is shared with the osram display. The code
 * in this file does not attempt to share the SSI port with the osram,
 * it assumes the osram is not being used.
 */
#include <rtthread.h>

#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <driverlib/ssi.h>
#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>

/* Status of Disk Functions */
typedef rt_uint8_t	DSTATUS;

/* Results of Disk Functions */
typedef enum {
	RES_OK = 0,		/* 0: Successful */
	RES_ERROR,		/* 1: R/W Error */
	RES_WRPRT,		/* 2: Write Protected */
	RES_NOTRDY,		/* 3: Not Ready */
	RES_PARERR		/* 4: Invalid Parameter */
} DRESULT;

/* Disk Status Bits (DSTATUS) */

#define STA_NOINIT		0x01	/* Drive not initialized */
#define STA_NODISK		0x02	/* No medium in the drive */
#define STA_PROTECT		0x04	/* Write protected */

/* Definitions for MMC/SDC command */
#define CMD0    (0x40+0)    /* GO_IDLE_STATE */
#define CMD1    (0x40+1)    /* SEND_OP_COND */
#define CMD8    (0x40+8)    /* SEND_IF_COND */
#define CMD9    (0x40+9)    /* SEND_CSD */
#define CMD10    (0x40+10)    /* SEND_CID */
#define CMD12    (0x40+12)    /* STOP_TRANSMISSION */
#define CMD16    (0x40+16)    /* SET_BLOCKLEN */
#define CMD17    (0x40+17)    /* READ_SINGLE_BLOCK */
#define CMD18    (0x40+18)    /* READ_MULTIPLE_BLOCK */
#define CMD23    (0x40+23)    /* SET_BLOCK_COUNT */
#define CMD24    (0x40+24)    /* WRITE_BLOCK */
#define CMD25    (0x40+25)    /* WRITE_MULTIPLE_BLOCK */
#define CMD41    (0x40+41)    /* SEND_OP_COND (ACMD) */
#define CMD55    (0x40+55)    /* APP_CMD */
#define CMD58    (0x40+58)    /* READ_OCR */

/* Command code for disk_ioctrl() */

/* Generic command */
#define CTRL_SYNC			0	/* Mandatory for write functions */
#define GET_SECTOR_COUNT	1	/* Mandatory for only f_mkfs() */
#define GET_SECTOR_SIZE		2	/* Mandatory for multiple sector size cfg */
#define GET_BLOCK_SIZE		3	/* Mandatory for only f_mkfs() */
#define CTRL_POWER			4
#define CTRL_LOCK			5
#define CTRL_EJECT			6
/* MMC/SDC command */
#define MMC_GET_TYPE		10
#define MMC_GET_CSD			11
#define MMC_GET_CID			12
#define MMC_GET_OCR			13
#define MMC_GET_SDSTAT		14
/* ATA/CF command */
#define ATA_GET_REV			20
#define ATA_GET_MODEL		21
#define ATA_GET_SN			22

/* Peripheral definitions for EK-LM3S6965 board */
// SSI port
#define SDC_SSI_BASE            SSI0_BASE
#define SDC_SSI_SYSCTL_PERIPH   SYSCTL_PERIPH_SSI0

// GPIO for SSI pins
#define SDC_GPIO_PORT_BASE      GPIO_PORTA_BASE
#define SDC_GPIO_SYSCTL_PERIPH  SYSCTL_PERIPH_GPIOA
#define SDC_SSI_CLK             GPIO_PIN_2
#define SDC_SSI_TX              GPIO_PIN_5
#define SDC_SSI_RX              GPIO_PIN_4
#define SDC_SSI_FSS             GPIO_PIN_3
#define SDC_SSI_PINS            (SDC_SSI_TX | SDC_SSI_RX | SDC_SSI_CLK)

// GPIO for card chip select
#define SDC_CS_GPIO_PORT_BASE      GPIO_PORTG_BASE
#define SDC_CS_GPIO_SYSCTL_PERIPH  SYSCTL_PERIPH_GPIOG
#define SDC_CS                     GPIO_PIN_0

// asserts the CS pin to the card
static
void SELECT (void)
{
    GPIOPinWrite(SDC_CS_GPIO_PORT_BASE, SDC_CS, 0);
}

// de-asserts the CS pin to the card
static
void DESELECT (void)
{
    GPIOPinWrite(SDC_CS_GPIO_PORT_BASE, SDC_CS, SDC_CS);
}


/*--------------------------------------------------------------------------

   Module Private Functions

---------------------------------------------------------------------------*/

static volatile
DSTATUS Stat = STA_NOINIT;    /* Disk status */

static volatile
rt_uint8_t Timer1, Timer2;    /* 100Hz decrement timer */

static
rt_uint8_t CardType;            /* b0:MMC, b1:SDC, b2:Block addressing */

static
rt_uint8_t PowerFlag = 0;     /* indicates if "power" is on */

/*-----------------------------------------------------------------------*/
/* Transmit a byte to MMC via SPI  (Platform dependent)                  */
/*-----------------------------------------------------------------------*/

static
void xmit_spi (rt_uint8_t dat)
{
    rt_uint32_t rcvdat;

    SSIDataPut(SDC_SSI_BASE, dat); /* Write the data to the tx fifo */

    SSIDataGet(SDC_SSI_BASE, &rcvdat); /* flush data read during the write */
}


/*-----------------------------------------------------------------------*/
/* Receive a byte from MMC via SPI  (Platform dependent)                 */
/*-----------------------------------------------------------------------*/

static
rt_uint8_t rcvr_spi (void)
{
    rt_uint32_t rcvdat;

    SSIDataPut(SDC_SSI_BASE, 0xFF); /* write dummy data */

    SSIDataGet(SDC_SSI_BASE, &rcvdat); /* read data frm rx fifo */

    return (rt_uint8_t)rcvdat;
}


static
void rcvr_spi_m (rt_uint8_t *dst)
{
    *dst = rcvr_spi();
}

/*-----------------------------------------------------------------------*/
/* Wait for card ready                                                   */
/*-----------------------------------------------------------------------*/

static
rt_uint8_t wait_ready (void)
{
    rt_uint8_t res;


    Timer2 = 50;    /* Wait for ready in timeout of 500ms */
    rcvr_spi();
    do
        res = rcvr_spi();
    while ((res != 0xFF) && Timer2);

    return res;
}

/*-----------------------------------------------------------------------*/
/* Send 80 or so clock transitions with CS and DI held high. This is     */
/* required after card power up to get it into SPI mode                  */
/*-----------------------------------------------------------------------*/
static
void send_initial_clock_train(void)
{
    unsigned int i;
    rt_uint32_t dat;

    /* Ensure CS is held high. */
    DESELECT();

    /* Switch the SSI TX line to a GPIO and drive it high too. */
    GPIOPinTypeGPIOOutput(SDC_GPIO_PORT_BASE, SDC_SSI_TX);
    GPIOPinWrite(SDC_GPIO_PORT_BASE, SDC_SSI_TX, SDC_SSI_TX);

    /* Send 10 bytes over the SSI. This causes the clock to wiggle the */
    /* required number of times. */
    for(i = 0 ; i < 10 ; i++)
    {
        /* Write DUMMY data. SSIDataPut() waits until there is room in the */
        /* FIFO. */
        SSIDataPut(SDC_SSI_BASE, 0xFF);

        /* Flush data read during data write. */
        SSIDataGet(SDC_SSI_BASE, &dat);
    }

    /* Revert to hardware control of the SSI TX line. */
    GPIOPinTypeSSI(SDC_GPIO_PORT_BASE, SDC_SSI_TX);
}

/*-----------------------------------------------------------------------*/
/* Power Control  (Platform dependent)                                   */
/*-----------------------------------------------------------------------*/
/* When the target system does not support socket power control, there   */
/* is nothing to do in these functions and chk_power always returns 1.   */

static
void power_on (void)
{
    /*
     * This doesn't really turn the power on, but initializes the
     * SSI port and pins needed to talk to the card.
     */

    /* Enable the peripherals used to drive the SDC on SSI, and the CS */
    SysCtlPeripheralEnable(SDC_SSI_SYSCTL_PERIPH);
    SysCtlPeripheralEnable(SDC_GPIO_SYSCTL_PERIPH);
    SysCtlPeripheralEnable(SDC_CS_GPIO_SYSCTL_PERIPH);

    /* Configure the appropriate pins to be SSI instead of GPIO */
    GPIOPinTypeSSI(SDC_GPIO_PORT_BASE, SDC_SSI_PINS);
    GPIOPinTypeGPIOOutput(SDC_CS_GPIO_PORT_BASE, SDC_CS);
    GPIOPadConfigSet(SDC_GPIO_PORT_BASE, SDC_SSI_PINS, GPIO_STRENGTH_4MA,
                     GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(SDC_CS_GPIO_PORT_BASE, SDC_CS, GPIO_STRENGTH_4MA,
                     GPIO_PIN_TYPE_STD_WPU);

    /* Deassert the SSI0 chip select */
    GPIOPinWrite(SDC_CS_GPIO_PORT_BASE, SDC_CS, SDC_CS);

    /* Configure the SSI0 port */
    SSIConfigSetExpClk(SDC_SSI_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
                       SSI_MODE_MASTER, 400000, 8);
    SSIEnable(SDC_SSI_BASE);

    /* Set DI and CS high and apply more than 74 pulses to SCLK for the card */
    /* to be able to accept a native command. */
    send_initial_clock_train();

    PowerFlag = 1;
}

// set the SSI speed to the max setting
static
void set_max_speed(void)
{
    unsigned long i;

    /* Disable the SSI */
    SSIDisable(SDC_SSI_BASE);

    /* Set the maximum speed as half the system clock, with a max of 12.5 MHz. */
    i = SysCtlClockGet() / 2;
    if(i > 12500000)
    {
        i = 12500000;
    }

    /* Configure the SSI0 port */
    SSIConfigSetExpClk(SDC_SSI_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
                       SSI_MODE_MASTER, i, 8);

    /* Enable the SSI */
    SSIEnable(SDC_SSI_BASE);
}

static
void power_off (void)
{
    PowerFlag = 0;
}

static
int chk_power(void)        /* Socket power state: 0=off, 1=on */
{
    return PowerFlag;
}



/*-----------------------------------------------------------------------*/
/* Receive a data packet from MMC                                        */
/*-----------------------------------------------------------------------*/

static
rt_bool_t rcvr_datablock (
    rt_uint8_t *buff,            /* Data buffer to store received data */
    unsigned int btr            /* Byte count (must be even number) */
)
{
    rt_uint8_t token;


    Timer1 = 10;
    do {                            /* Wait for data packet in timeout of 100ms */
        token = rcvr_spi();
    } while ((token == 0xFF) && Timer1);
    if(token != 0xFE) return RT_FALSE;    /* If not valid data token, retutn with error */

    do {                            /* Receive the data block into buffer */
        rcvr_spi_m(buff++);
        rcvr_spi_m(buff++);
    } while (btr -= 2);
    rcvr_spi();                        /* Discard CRC */
    rcvr_spi();

    return RT_TRUE;                    /* Return with success */
}



/*-----------------------------------------------------------------------*/
/* Send a data packet to MMC                                             */
/*-----------------------------------------------------------------------*/

#if _READONLY == 0
static
rt_bool_t xmit_datablock (
    const rt_uint8_t *buff,    /* 512 byte data block to be transmitted */
    rt_uint8_t token            /* Data/Stop token */
)
{
    rt_uint8_t resp, wc;


    if (wait_ready() != 0xFF) return RT_FALSE;

    xmit_spi(token);                    /* Xmit data token */
    if (token != 0xFD) {    /* Is data token */
        wc = 0;
        do {                            /* Xmit the 512 byte data block to MMC */
            xmit_spi(*buff++);
            xmit_spi(*buff++);
        } while (--wc);
        xmit_spi(0xFF);                    /* CRC (Dummy) */
        xmit_spi(0xFF);
        resp = rcvr_spi();                /* Reveive data response */
        if ((resp & 0x1F) != 0x05)        /* If not accepted, return with error */
            return RT_FALSE;
    }

    return RT_TRUE;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Send a command packet to MMC                                          */
/*-----------------------------------------------------------------------*/

static
rt_uint8_t send_cmd (
    rt_uint8_t cmd,        /* Command byte */
    rt_uint32_t arg        /* Argument */
)
{
    rt_uint8_t n, res;


    if (wait_ready() != 0xFF) return 0xFF;

    /* Send command packet */
    xmit_spi(cmd);                        /* Command */
    xmit_spi((rt_uint8_t)(arg >> 24));        /* Argument[31..24] */
    xmit_spi((rt_uint8_t)(arg >> 16));        /* Argument[23..16] */
    xmit_spi((rt_uint8_t)(arg >> 8));            /* Argument[15..8] */
    xmit_spi((rt_uint8_t)arg);                /* Argument[7..0] */
    n = 0;
    if (cmd == CMD0) n = 0x95;            /* CRC for CMD0(0) */
    if (cmd == CMD8) n = 0x87;            /* CRC for CMD8(0x1AA) */
    xmit_spi(n);

    /* Receive command response */
    if (cmd == CMD12) rcvr_spi();        /* Skip a stuff byte when stop reading */
    n = 10;                                /* Wait for a valid response in timeout of 10 attempts */
    do
        res = rcvr_spi();
    while ((res & 0x80) && --n);

    return res;            /* Return with the response value */
}



/*--------------------------------------------------------------------------

   Public Functions

---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/
static
DSTATUS sdcard_initialize (
    rt_uint8_t drv        /* Physical drive nmuber (0) */
)
{
    rt_uint8_t n, ty, ocr[4];


    if (drv) return STA_NOINIT;            /* Supports only single drive */
    if (Stat & STA_NODISK) return Stat;    /* No card in the socket */

    power_on();                            /* Force socket power on */
    send_initial_clock_train();

    SELECT();                /* CS = L */
    ty = 0;
    if (send_cmd(CMD0, 0) == 1) {            /* Enter Idle state */
        Timer1 = 100;                        /* Initialization timeout of 1000 msec */
        if (send_cmd(CMD8, 0x1AA) == 1) {    /* SDC Ver2+ */
            for (n = 0; n < 4; n++) ocr[n] = rcvr_spi();
            if (ocr[2] == 0x01 && ocr[3] == 0xAA) {    /* The card can work at vdd range of 2.7-3.6V */
                do {
                    if (send_cmd(CMD55, 0) <= 1 && send_cmd(CMD41, 1UL << 30) == 0)    break;    /* ACMD41 with HCS bit */
                } while (Timer1);
                if (Timer1 && send_cmd(CMD58, 0) == 0) {    /* Check CCS bit */
                    for (n = 0; n < 4; n++) ocr[n] = rcvr_spi();
                    ty = (ocr[0] & 0x40) ? 6 : 2;
                }
            }
        } else {                            /* SDC Ver1 or MMC */
            ty = (send_cmd(CMD55, 0) <= 1 && send_cmd(CMD41, 0) <= 1) ? 2 : 1;    /* SDC : MMC */
            do {
                if (ty == 2) {
                    if (send_cmd(CMD55, 0) <= 1 && send_cmd(CMD41, 0) == 0) break;    /* ACMD41 */
                } else {
                    if (send_cmd(CMD1, 0) == 0) break;                                /* CMD1 */
                }
            } while (Timer1);
            if (!Timer1 || send_cmd(CMD16, 512) != 0)    /* Select R/W block length */
                ty = 0;
        }
    }
    CardType = ty;
    DESELECT();            /* CS = H */
    rcvr_spi();            /* Idle (Release DO) */

    if (ty) {            /* Initialization succeded */
        Stat &= ~STA_NOINIT;        /* Clear STA_NOINIT */
        set_max_speed();
    } else {            /* Initialization failed */
        power_off();
    }

    return Stat;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/
static
DRESULT sdcard_read (
    rt_uint8_t drv,            /* Physical drive nmuber (0) */
    rt_uint8_t *buff,            /* Pointer to the data buffer to store read data */
    rt_uint32_t sector,        /* Start sector number (LBA) */
    rt_uint8_t count            /* Sector count (1..255) */
)
{
    if (drv || !count) return RES_PARERR;
    if (Stat & STA_NOINIT) return RES_NOTRDY;

    if (!(CardType & 4)) sector *= 512;    /* Convert to byte address if needed */

    SELECT();            /* CS = L */

    if (count == 1) {    /* Single block read */
        if ((send_cmd(CMD17, sector) == 0)    /* READ_SINGLE_BLOCK */
            && rcvr_datablock(buff, 512))
            count = 0;
    }
    else {                /* Multiple block read */
        if (send_cmd(CMD18, sector) == 0) {    /* READ_MULTIPLE_BLOCK */
            do {
                if (!rcvr_datablock(buff, 512)) break;
                buff += 512;
            } while (--count);
            send_cmd(CMD12, 0);                /* STOP_TRANSMISSION */
        }
    }

    DESELECT();            /* CS = H */
    rcvr_spi();            /* Idle (Release DO) */

    return count ? RES_ERROR : RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _READONLY == 0
static
DRESULT sdcard_write (
    rt_uint8_t drv,            /* Physical drive nmuber (0) */
    const rt_uint8_t *buff,    /* Pointer to the data to be written */
    rt_uint32_t sector,        /* Start sector number (LBA) */
    rt_uint8_t count            /* Sector count (1..255) */
)
{
    if (drv || !count) return RES_PARERR;
    if (Stat & STA_NOINIT) return RES_NOTRDY;
    if (Stat & STA_PROTECT) return RES_WRPRT;

    if (!(CardType & 4)) sector *= 512;    /* Convert to byte address if needed */

    SELECT();            /* CS = L */

    if (count == 1) {    /* Single block write */
        if ((send_cmd(CMD24, sector) == 0)    /* WRITE_BLOCK */
            && xmit_datablock(buff, 0xFE))
            count = 0;
    }
    else {                /* Multiple block write */
        if (CardType & 2) {
            send_cmd(CMD55, 0); send_cmd(CMD23, count);    /* ACMD23 */
        }
        if (send_cmd(CMD25, sector) == 0) {    /* WRITE_MULTIPLE_BLOCK */
            do {
                if (!xmit_datablock(buff, 0xFC)) break;
                buff += 512;
            } while (--count);
            if (!xmit_datablock(0, 0xFD))    /* STOP_TRAN token */
                count = 1;
        }
    }

    DESELECT();            /* CS = H */
    rcvr_spi();            /* Idle (Release DO) */

    return count ? RES_ERROR : RES_OK;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/
static
DRESULT sdcard_ioctl (
    rt_uint8_t drv,        /* Physical drive nmuber (0) */
    rt_uint8_t ctrl,        /* Control code */
    void *buff        /* Buffer to send/receive control data */
)
{
    DRESULT res;
    rt_uint8_t n, csd[16], *ptr = buff;
    rt_uint16_t csize;


    if (drv) return RES_PARERR;

    res = RES_ERROR;

    if (ctrl == CTRL_POWER) {
        switch (*ptr) {
        case 0:        /* Sub control code == 0 (POWER_OFF) */
            if (chk_power())
                power_off();        /* Power off */
            res = RES_OK;
            break;
        case 1:        /* Sub control code == 1 (POWER_ON) */
            power_on();                /* Power on */
            res = RES_OK;
            break;
        case 2:        /* Sub control code == 2 (POWER_GET) */
            *(ptr+1) = (rt_uint8_t)chk_power();
            res = RES_OK;
            break;
        default :
            res = RES_PARERR;
        }
    }
    else {
        if (Stat & STA_NOINIT) return RES_NOTRDY;

        SELECT();        /* CS = L */

        switch (ctrl) {
        case GET_SECTOR_COUNT :    /* Get number of sectors on the disk (rt_uint32_t) */
            if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {
                if ((csd[0] >> 6) == 1) {    /* SDC ver 2.00 */
                    csize = csd[9] + ((rt_uint16_t)csd[8] << 8) + 1;
                    *(rt_uint32_t*)buff = (rt_uint32_t)csize << 10;
                } else {                    /* MMC or SDC ver 1.XX */
                    n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
                    csize = (csd[8] >> 6) + ((rt_uint16_t)csd[7] << 2) + ((rt_uint16_t)(csd[6] & 3) << 10) + 1;
                    *(rt_uint32_t*)buff = (rt_uint32_t)csize << (n - 9);
                }
                res = RES_OK;
            }
            break;

        case GET_SECTOR_SIZE :    /* Get sectors on the disk (rt_uint16_t) */
            *(rt_uint16_t*)buff = 512;
            res = RES_OK;
            break;

        case CTRL_SYNC :    /* Make sure that data has been written */
            if (wait_ready() == 0xFF)
                res = RES_OK;
            break;

        case MMC_GET_CSD :    /* Receive CSD as a data block (16 bytes) */
            if (send_cmd(CMD9, 0) == 0        /* READ_CSD */
                && rcvr_datablock(ptr, 16))
                res = RES_OK;
            break;

        case MMC_GET_CID :    /* Receive CID as a data block (16 bytes) */
            if (send_cmd(CMD10, 0) == 0        /* READ_CID */
                && rcvr_datablock(ptr, 16))
                res = RES_OK;
            break;

        case MMC_GET_OCR :    /* Receive OCR as an R3 resp (4 bytes) */
            if (send_cmd(CMD58, 0) == 0) {    /* READ_OCR */
                for (n = 0; n < 4; n++)
                    *ptr++ = rcvr_spi();
                res = RES_OK;
            }

//        case MMC_GET_TYPE :    /* Get card type flags (1 byte) */
//            *ptr = CardType;
//            res = RES_OK;
//            break;

        default:
            res = RES_PARERR;
        }

        DESELECT();            /* CS = H */
        rcvr_spi();            /* Idle (Release DO) */
    }

    return res;
}

/*
 * RT-Thread SD Card Driver
 * 20090705 Yi.Qiu
 */
#include <rtthread.h>
#include <dfs_fs.h>

struct rt_device sdcard_device;
struct dfs_partition part;

/* RT-Thread Device Driver Interface */
static rt_err_t rt_sdcard_init(rt_device_t dev)
{
	return RT_EOK;
}

static rt_err_t rt_sdcard_open(rt_device_t dev, rt_uint16_t oflag)
{

	return RT_EOK;
}

static rt_err_t rt_sdcard_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_ssize_t rt_sdcard_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	DRESULT status;

	status = sdcard_read(0, buffer, part.offset + pos, size);
	if (status != RES_OK)
	{
		rt_kprintf("sd card read failed\n");
		return 0;
	}

	return size;
}

static rt_ssize_t rt_sdcard_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	DRESULT status;

	status = sdcard_write(0, buffer, part.offset + pos, size);
	if (status != RES_OK)
	{
		rt_kprintf("sd card write failed\n");
		return 0;
	}

	return size;
}

static rt_err_t rt_sdcard_control(rt_device_t dev, int cmd, void *args)
{
	return RT_EOK;
}

void rt_hw_sdcard_init(void)
{
	if (sdcard_initialize(0) == RES_OK)
	{
		DRESULT status;
		rt_uint8_t *sector;

		/* get the first sector to read partition table */
		sector = (rt_uint8_t*) rt_malloc (512);
		if (sector == RT_NULL) 
		{
			rt_kprintf("allocate partition sector buffer failed\n");
			return;
		}
		status = sdcard_read(0, sector, 0, 1);
		if (status == RES_OK)
		{
			/* get the first partition */
			if (dfs_filesystem_get_partition(&part, sector, 0) != 0)
			{
			    /* there is no partition */
			    part.offset = 0;
			    part.size   = 0;
			}
		}
		else
		{
			/* there is no partition table */
			part.offset = 0;
			part.size   = 0;
		}
		
		/* release sector buffer */
		rt_free(sector);
		
		/* register sdcard device */
		sdcard_device.type  = RT_Device_Class_Block;
		sdcard_device.init 	= rt_sdcard_init;
		sdcard_device.open 	= rt_sdcard_open;
		sdcard_device.close = rt_sdcard_close;
		sdcard_device.read 	= rt_sdcard_read;
		sdcard_device.write = rt_sdcard_write;
		sdcard_device.control = rt_sdcard_control;
		
		/* no private */
		sdcard_device.user_data = RT_NULL;
		
		rt_device_register(&sdcard_device, "sd0", 
			RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);
		
		return;
	}
	rt_kprintf("sdcard init failed\n");
}

