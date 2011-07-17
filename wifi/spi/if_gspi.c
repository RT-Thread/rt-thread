/** @file if_gspi.c
  * @brief This file contains generic GSPI functions
  * 
  *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2007
  */
/********************************************************
Change log:
	09/26/05: Add Doxygen format comments
	10/20/05: Add GSPI8686 support
	01/30/06: Add kernel 2.6 support for GSPI8xxx/Bulverde
	
********************************************************/
#include	"if_gspi.h"
#include	"if_gspi_debug.h"
#include	"gspi_io.h"

//#include	"helper.h"

//#include	"gspi8686.h"
#include	"rtthread.h"
#include    "sep4020.h"
#define HIC_DEFAULT_VALUE 0
/********************************************************
		Local Variables
********************************************************/

/********************************************************
		Global Variables
********************************************************/
extern int gspi_register_irq(int * irqnum);

extern int g_dummy_clk_reg;
extern int g_dummy_clk_ioport;

/********************************************************
		Local Functions
********************************************************/

static int gspi_read_reg32(wlan_private * priv,u16 offset, u32 * data);
static int gspi_read_host_int_status(wlan_private * priv,u8 * data);
static int gspi_read_event_scratch(wlan_private * priv);
static wlan_private *pwlanpriv;
static wlan_private *(*wlan_add_callback) (void *dev_id);
static int (*wlan_remove_callback) (void *dev_id);

/** 
 *  @brief clear the auto generate interrupt bit in Host
 *  Interrupt Control register
 * 
 *  @param priv    A pointer to wlan_private structure
 *  @return 	   NA
 */
static void gspi_init_HOST_INT_CTRL_REG(wlan_private * priv)
{
    gspi_write_reg(HOST_INT_CTRL_REG,HIC_DEFAULT_VALUE & ~(HIC_TxDnldAuto|HIC_RxUpldAuto | HIC_CmdDnldAuto|HIC_CmdUpldAuto));
}

/**
 *  @brief This function re-enable the interrupt of the mask bit.
 * 
 *  @param priv    A pointer to wlan_private structure
 *  @param mask    interrupt mask 	
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int gspi_write_host_int_status(wlan_private * priv,u16 mask)
{
    if (gspi_write_reg(HOST_INT_STATUS_REG, ~mask)) {
        rt_kprintf("gspi_write_reg failed\n");
        return WLAN_STATUS_FAILURE;
    }
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function used to poll CmdDnLdRdy bit of Host Interrupt Status Register
 * 
 *  @param cardp   A pointer to gspi_card_rec structure
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int wait_for_hostintstatus(void *card)
{
#define MAX_WAIT_TRIES 100
    int i = 0,y;
    u16 stat;

    for (i = 0; i < MAX_WAIT_TRIES; ++i) {
        gspi_read_reg(HOST_INT_STATUS_REG, &stat);

        if (stat & GHIS_CmdDnLdRdy)
            return WLAN_STATUS_SUCCESS;
	for(y=0;y<1000;y++);
        //rt_thread_delay(1);//may be for loop more suitable
    }

    return WLAN_STATUS_FAILURE;
}

/** 
 *  @brief This function read a 32bit value from GSPI register
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @param reg          GSPI hardware register
 *  @param data		A pointer to return the register value    
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int gspi_read_reg32(wlan_private * priv, u16 reg, u32 * data)
{
    u16 readdt[3];

    if (gspi_read_data_direct((u8 *) readdt, reg, 4) < 0) {
        rt_kprintf( "Error on gspi_read_reg32(%02x)\n", reg);
        return WLAN_STATUS_FAILURE;
    }

    memcpy(data, readdt, 4);
#ifdef 	GSPI_TX_RX_DEBUG
    rt_kprintf("read reg32(0x%x) = 0x%x\n", reg, *data);
#endif
    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function read the host inerrrupt status register
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @param curHIS	A pointer to return the value of Host Interrupt Status register
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int gspi_read_host_int_status(wlan_private * priv, u8 * curHIS)
{
    int ret;
    u16 his;
 	  
	ret = gspi_read_reg(HOST_INT_STATUS_REG, &his);
    if (!ret)
        *curHIS = (u8) his;

    return ret;
}

/**
 *  @brief Read Event cause from the event scratch register
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int
gspi_read_event_scratch(wlan_private * priv)
{
    int ret;

    ENTER();

    ret = gspi_read_reg32(priv, SCRATCH_3_REG, &priv->adapter->EventCause);
    if (ret < 0) {
        rt_kprintf("ERROR: Event Scratch Pad Register Read!\n");
        return ret;
    }

    rt_kprintf("The event is %x\n", priv->adapter->EventCause);

    priv->adapter->EventCause <<= 3;
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief This function enables the host interrupts mask
 *  
 *  @param priv    A pointer to wlan_private structure
 *  @param mask	   the interrupt mask
 *  @return 	   WLAN_STATUS_SUCCESS
 */
static int
enable_host_int_mask(wlan_private * priv, u8 mask)
{
    int ret = WLAN_STATUS_SUCCESS;
    /* Enabling TxDnldRdy, RxDnldRdy, CmdUpldRdy, CmdDnldRdy, CardEvent
     * interrupts */
    gspi_write_reg(HOST_INT_STATUS_MASK_REG,HISM_TxDnLdRdy | HISM_RxUpLdRdy | HISM_CmdDnLdRdy|HISM_CardEvent | HISM_CmdUpLdRdy);

    return ret;
}

/**  @brief This function disables the host interrupts mask.
 *  
 *  @param priv    A pointer to wlan_private structure
 *  @param mask	   the interrupt mask
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
static int disable_host_int_mask(wlan_private * priv,u8 int_mask)
{
    return gspi_write_reg(HOST_INT_STATUS_MASK_REG, 0x00);
}

/********************************************************
		Global Functions
********************************************************/
/** 
 *  @brief This is the interrupt handler for GSPI device
 *
 *  @param irq 	   The irq of GSPI device.
 *  @param dev_id  A pointer to net_device structure
 *  @param fp	   A pointer to pt_regs structure
 *  @return 	   n/a
 */

 void sbi_interrupt(int dev)
{
   
	disable_irq(INTSRC_EXINT4)	;
  	
	wlan_interrupt((struct rt_wlan_dev *)dev);

}
/** 
 *  @brief Call back function when New Hardware insert.
 *
 *  This function will notify wlan driver a new hardware insert.
 *
 *  @param card	   A pointer to struct net_device 
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int sbi_add_card(void* card)
{
    if (!wlan_add_callback)
        return WLAN_STATUS_FAILURE;

    pwlanpriv = wlan_add_callback(card);

    return (pwlanpriv != NULL) ? WLAN_STATUS_SUCCESS : WLAN_STATUS_FAILURE;
}

/** 
 *  @brief Call back function when Hardware been removed.
 *
 *  This function will notify wlan driver a hardware removed.
 *
 *  @param card	   A pointer to struct net_device 
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_remove_card(void *card)
{
    if (!wlan_remove_callback)
        return WLAN_STATUS_FAILURE;

    pwlanpriv = NULL;
    return wlan_remove_callback(card);
}

/** 
 *  @brief wlan driver call this function to register to bus driver
 *
 *  This function will be used to register wlan driver's add/remove callback function.
 *
 *  @param add	   wlan driver's call back funtion for add card.
 *  @param remove  wlan driver's call back funtion for remove card.
 *  @param arg     not been used
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
/*
struct gspi_card_rec cardp;
int sbi_register(wlan_notifier_fn_add add, wlan_notifier_fn_remove remove,void *arg)
{
    struct gspi_card_rec cardp;
	wlan_add_callback = add;
    wlan_remove_callback = remove;
	cardp.add = sbi_add_card;
    cardp.remove = sbi_remove_card;
//    cardp.user_isr = sbi_interrupt;
	sbi_add_card(&cardp);
    return 0;
}
*/
/**
 *  @brief wlan driver call this function to unregister to bus driver
 *
 *  This function will be used to unregister wlan driver.
 *
 *  @return 	   NA
 */
void
sbi_unregister(void)
{
  //  unregister_user(&gspi_notifier);
}

/** 
 *  @brief fake function for gspi interface hardware
 *
 *  @param priv    A pointer to wlan_private structure	
 *  @return 	   WLAN_STATUS_SUCCESS
 */
int
sbi_get_cis_info(wlan_private * priv)
{
   
    return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief fake function for gspi interface hardware
 *
 *  @param card_p  not used
 *  @return 	   WLAN_STATUS_SUCCESS
 */
int
sbi_probe_card(void *card_p)
{
    return WLAN_STATUS_SUCCESS;
}

#define IPFIELD_ALIGN_OFFSET    2

/** 
 *  @brief This function read the current interrupt status register.
 * 
 *  @param priv    A pointer to wlan_private structure
 *  @param ireg    A pointer to hold the return interrupt status value 	
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int sbi_get_int_status(wlan_private * priv, u8 * ireg)
{
    int ret = WLAN_STATUS_SUCCESS;
    u8 tmp;
    struct sk_buff *skb=RT_NULL;
    u8 *cmdBuf;
    wlan_adapter *Adapter = priv->adapter;

    disable_host_int_mask(priv, HIM_DISABLE);
    ret = gspi_read_host_int_status(priv, &tmp);
    gspi_irq_clear();
    enable_irq(priv->wlan_dev.netdev->irq);

    /* re-map bit 0 and bit 1 for WLAN module since the definition is different */

    *ireg = tmp & (~(GHIS_TxDnLdRdy | GHIS_RxUpLdRdy));

    if (tmp & GHIS_TxDnLdRdy) {
        priv->wlan_dev.dnld_sent = DNLD_RES_RECEIVED;
        *ireg |= HIS_TxDnLdRdy;
    }

    if (tmp & GHIS_RxUpLdRdy) {
        *ireg |= HIS_RxUpLdRdy;
    }

    if (*ireg & HIS_RxUpLdRdy) {
    	 if((skb=rt_malloc(sizeof(struct sk_buff)))==RT_NULL)
     	{
		ifspi_debug1 ("no memry for skb\n\r");
		goto done;

     	}
     rt_memset(skb,0x00,sizeof(struct sk_buff));
     INIT_LIST_HEAD((struct list_head *)skb);
	 skb->data = rt_malloc(MRVDRV_ETH_RX_PACKET_BUFFER_SIZE);
     if (!skb->data) {
            ifspi_debug1("No free skb data buf\n");
            priv->stats.rx_dropped++;
            ret = WLAN_STATUS_FAILURE;
	     	rt_free(skb);
            goto done;
     }
     
        /*16 Byte Align the IP fields */ /*why the IPFIELD_ALIGN_OFFSET is 2 not 16*/
	 skb->head=skb->data;
	 skb->data=(unsigned char *)(((u32)skb->data+3)&0xfffffffc);
     wlan_debug3("data buf skb %x data %x",(u32)skb,(u32)skb->head);
        /* skb->tail is passed as we are calling skb_put after we
         * are reading the data */
     if (sbi_card_to_host(priv, MVMS_DAT,
                             &priv->wlan_dev.upld_len,
                             skb->data,
                             MRVDRV_ETH_RX_PACKET_BUFFER_SIZE) < 0) {
            ifspi_debug1("ERROR: Data Transfer from device failed\n");
            if (skb)
            {  
            		rt_free(skb);
			if(skb->head!=RT_NULL)
			rt_free(skb->head);
            }
            ret = WLAN_STATUS_FAILURE;
            goto done;
        }
        ifspi_debug3( "Data <= FW\n");

        skb->len+= priv->wlan_dev.upld_len;       
        list_add_tail((struct list_head *) skb,
                      (struct list_head *) &Adapter->RxSkbQ);
    }

    if (*ireg & HIS_CmdUpLdRdy) {

        if (!Adapter->CurCmd) {
            cmdBuf = priv->wlan_dev.upld_buf;
        } else {
            cmdBuf = Adapter->CurCmd->BufVirtualAddr;
        }

        if (sbi_card_to_host(priv, MVMS_CMD,
                             &priv->wlan_dev.upld_len,
                             cmdBuf, WLAN_UPLD_SIZE) < 0) {
            ifspi_debug1("ERROR: Data Transfer from device failed\n");
            ret = WLAN_STATUS_FAILURE;
            goto done;
        }
    }
  done:
    enable_host_int_mask(priv, HIM_ENABLE);
  //  ifspi_debug2("GSPI int status = %02x:%02x\n", *ireg, Adapter->HisRegCpy);

    return ret;
}

/** 
 *  @brief initial the gspi hardware
 * 
 *  @param priv    A pointer to wlan_private structure
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int sbi_card_init(wlan_private * priv)
{
	
    u16 host_int_mask;
	u16 chiprev;
	u32 irq_num;
   
    gspi_write_reg( SPU_BUS_MODE_REG, BUS_MODE_16_NO_DELAY);
    gspi_read_reg( CHIPREV_REG, &chiprev);
    ifspi_debug2("Chiprev is %x", chiprev);
    priv->adapter->chip_rev = chiprev;

    /* Read the HOST_INT_STATUS_REG for ACK the first interrrupt got
     * from the bootloader. If we don't do this we get a interrupt
     * as soon as we register the irq. */
    gspi_read_reg(HOST_INT_STATUS_REG, &host_int_mask);
	
    if (gspi_register_irq((int*)&irq_num) != GSPI_OK){
        ifspi_debug1("gspi_register_irq failed\n");
        return WLAN_STATUS_FAILURE;
    }

	
   	enable_host_int_mask(priv, HIM_ENABLE);
	gspi_init_HOST_INT_CTRL_REG(priv);
	priv->wlan_dev.netdev->irq = irq_num;
	

    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function check the firmware download status
 * 
 *  @param priv    A pointer to wlan_private structure
 *  @return 	   WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_verify_fw_download(wlan_private * priv)
{
    int i;
    u32 scr4;

    for (i = 0; i < MAX_FIRMWARE_POLL_TRIES; ++i) {

        if (gspi_read_reg32(priv,SCRATCH_4_REG, &scr4) < 0) {
            rt_kprintf( "Read from Scratch 4 failed !!!\n");
            return WLAN_STATUS_FAILURE;
        }

        if (scr4 == FIRMWARE_DNLD_OK) {
            rt_kprintf("FW download successful !!!\n");
            return WLAN_STATUS_SUCCESS;
        }

        rt_thread_delay(100);
    }

    return WLAN_STATUS_FAILURE;
}

/** 
 *  @brief This function download the firmware to the hardware
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @param firmware     A pointer to firmware 
 *  @param firmwarelen  the len of firmware
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_download_wlan_fw_image( wlan_private * priv,const u8 * firmware,
                           int firmwarelen)
{
    int ret,i;
    u16 dlimage[1024];
    u16 len;
    u32 cnt = 0;
	
//    rt_kprintf("Downloading FW of size %d bytes\n", firmwarelen);
    //printk(KERN_ERR "Downloading--FW of size %d bytes\n", firmwarelen);

    /* Wait initially for the first non-zero value */

    do {
     
	for(i=0;i<1000;i++);
        gspi_read_reg(SCRATCH_1_REG, &len);
    } while (!len);
    //printk(KERN_ERR "LEN size %d bytes\n", len);

    for (;;) {
        if (wait_for_hostintstatus(RT_NULL)) {
            rt_kprintf("FW download died\n");
            return WLAN_STATUS_FAILURE;
        }

        gspi_read_reg(SCRATCH_1_REG, &len);

        if (!len) {
            break;
        }

        if (len & 1) {
 //           rt_kprintf("CRC Error\n");
            len &= ~1;
        } else {
        //    rt_kprintf(".");
        }

        memcpy(dlimage, firmware + cnt, len);
        gspi_write_data_direct((u8 *) dlimage, CMD_RDWRPORT_REG,
                               (len / 2) + 1);
        gspi_write_reg(HOST_INT_STATUS_REG, 0x0000);
        gspi_write_reg(CARD_INT_CAUSE_REG, CIC_CmdDnLdOvr);
        cnt += len;
    }

    
/*printk(KERN_ERR "\nFW Image of Size %d bytes downloaded, cnt %d\n",
			firmwarelen,cnt);*/
 //   rt_kprintf("\nFW Image of Size bytes downloaded, cnt %d\n",
 //          firmwarelen, cnt);

    ret = WLAN_STATUS_SUCCESS;
    return ret;
}

/** 
 *  @brief This function will call sbi_download_wlan_fw_image to download the firmware
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_prog_firmware_w_helper(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;
    if (Adapter->fmimage != NULL) {
        return sbi_download_wlan_fw_image(priv,
                                          Adapter->fmimage,
                                          Adapter->fmimage_len);
    } else {
        rt_kprintf("No external FW image\n");
        return WLAN_STATUS_FAILURE;
    }
}

/**
 *  @brief This function is used to download firmware to hardware
 * 
 *  @param priv         	A pointer to wlan_private structure
 *  @param firmware 		A pointer to fimware
 *  @param firmwarelen		firmware length
 *  @return 	        	WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_prog_firmware_image(wlan_private * priv, const u8 * firmware,
                        int firmwarelen)
{
    int ret = WLAN_STATUS_SUCCESS;
    u16 dlimage[FIRMWARE_DNLD_PCKCNT];
    int fwblknow;
  

    for (fwblknow = 0; fwblknow < firmwarelen;
         fwblknow += FIRMWARE_DNLD_PCKCNT) {
         gspi_write_reg(SCRATCH_1_REG, FIRMWARE_DNLD_PCKCNT);

        if (wait_for_hostintstatus(RT_NULL)) {
            rt_kprintf("FW download died\n");
            return WLAN_STATUS_FAILURE;
        }

        rt_memcpy(dlimage, firmware + fwblknow, FIRMWARE_DNLD_PCKCNT);
        gspi_write_data_direct((u8 *) dlimage, CMD_RDWRPORT_REG,
                               (FIRMWARE_DNLD_PCKCNT / 2) + 1);
        gspi_write_reg(HOST_INT_STATUS_REG, 0x0000);
        gspi_write_reg(CARD_INT_CAUSE_REG, CIC_CmdDnLdOvr);
    }

    /* Writing 0 to Scr1 is to indicate the end of Firmware dwld */
    gspi_write_reg(SCRATCH_1_REG, FIRMWARE_DNLD_END);
    gspi_write_reg(HOST_INT_STATUS_REG, 0x0000);
    gspi_write_reg(CARD_INT_CAUSE_REG, CIC_CmdDnLdOvr);
   
    ret = WLAN_STATUS_SUCCESS;
    return ret;
}

/** 
 *  @brief This function will call sbi_prog_firmware_image to
 *  download the firmware
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_prog_firmware(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;
    if (Adapter->fmimage != NULL) {
        return sbi_prog_firmware_image(priv,
                                       Adapter->fmimage,
                                       Adapter->fmimage_len);
    } else {
        ifspi_debug3( "No external FW image\n");
        return WLAN_STATUS_FAILURE;
    }
}

/** 
 *  @brief This function will call sbi_prog_firmware_image to
 *  download the helperimage
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_prog_helper(wlan_private * priv)
{
    wlan_adapter *Adapter = priv->adapter;
    if (Adapter->helper != NULL) {
        return sbi_prog_firmware_image(priv,
                                       Adapter->helper, Adapter->helper_len);
    } else {
        rt_kprintf("No external helper image\n");
        return WLAN_STATUS_FAILURE;
    }
}

/** 
 *  @brief wlan driver call this function to register the device 
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS
 */
int spi_register_dev(wlan_private * priv)
{
    int ret = WLAN_STATUS_SUCCESS;

    ENTER();

    /* Initialize the private structure */
    strncpy(priv->wlan_dev.name, "gspi0", sizeof(priv->wlan_dev.name));
    priv->wlan_dev.ioport = 0;
    priv->wlan_dev.upld_rcv = 0;
    priv->wlan_dev.upld_typ = 0;
    priv->wlan_dev.upld_len = 0;

    sbi_card_init(priv);

    LEAVE();

    return ret;
}
/** 
 *  @brief enable the host interrupt on the GSPI device
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS
 */
int
sbi_enable_host_int(wlan_private * priv)
{	
	gspi_irq_clear();
       enable_irq(priv->wlan_dev.netdev->irq);
       return WLAN_STATUS_SUCCESS;
}

/** 
 *  @brief Disable the Host interrupt on the GSPI device
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS
 */
int sbi_disable_host_int(wlan_private * priv)
{
    disable_irq(priv->wlan_dev.netdev->irq);
    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief This function is used to send the data/cmd to hardware
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @param type 	1--Cmd, 0--Data
 *  @param payload	A point to the data or cmd buffer
 *  @param nb           len of data/cmd buffer 
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_host_to_card(wlan_private * priv, u8 type, u8 * payload, u16 nb)
{
    int ret = WLAN_STATUS_SUCCESS;
    u16 writeReg;
    u8 intType;
    ENTER();

    intType = type ? CIC_CmdDnLdOvr : CIC_TxDnLdOvr;
    writeReg = (type) ? CMD_RDWRPORT_REG : DATA_RDWRPORT_REG;
    priv->wlan_dev.dnld_sent = (type) ? DNLD_CMD_SENT : DNLD_DATA_SENT;

    if (nb & 0x0001)
        nb += 1;

    /* 
     * If the bytes written is not a multiple of four then make it 
     * a multiple of four as the RWPORT is 4 byte aligned from
     * the host
     */

    if (!(nb % 4))
        ret = gspi_write_data_direct(payload, writeReg, (nb / 2) + 1);
    else
        ret = gspi_write_data_direct(payload, writeReg, (nb / 2) + 2);

    gspi_write_reg(CARD_INT_CAUSE_REG, intType);

    LEAVE();

    return ret;
}

/**
 *  @brief This function is used to read data/cmd from the card.
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @param type 	1--Cmd, 0--Data
 *  @param nb    	A point to return how many bytes has been read back from hardware
 *  @param payload      A point to data buffer for receive data/cmd
 *  @param npayload     the size of payload buffer
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_card_to_host(wlan_private * priv, u32 type,
                 u32 * nb, u8 * payload, u16 npayload)
{
    int ret = WLAN_STATUS_SUCCESS;
    u16 len;
    u16 intType = 0, readReg;
 
    ENTER();

    intType = type ? CIC_CmdUpLdOvr : CIC_RxUpLdOvr;
    readReg = type ? CMD_RDWRPORT_REG : DATA_RDWRPORT_REG;

    gspi_read_reg((type) ? SCRATCH_2_REG : SCRATCH_1_REG, &len);

    if (!len || len > npayload) {
        ifspi_debug3( "Error packet of len %d\n", len);
        len = MRVDRV_ETH_RX_PACKET_BUFFER_SIZE;
    }

    if (len & 0x0001)
        len += 1;

    if (!(len % 4))
        ret = gspi_read_data_direct(payload, readReg, (len / 2) + 1);
    else
        ret = gspi_read_data_direct(payload, readReg, (len / 2) + 2);

    gspi_write_reg(CARD_INT_CAUSE_REG, intType);

    *nb = len;

    LEAVE();

    return ret;
}

/** 
 *  @brief This function is used to read the event cause from card
 *  and re-enable event interrupt.
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int
sbi_read_event_cause(wlan_private * priv)
{
    gspi_read_event_scratch(priv);

    /* re-enable the interrupt */
    gspi_write_host_int_status(priv, GHIS_CardEvent);

    /* generate interrupt to firmware */
    gspi_write_reg(CARD_INT_CAUSE_REG, CIC_HostEvent);

    return WLAN_STATUS_SUCCESS;
}

/**
 *  @brief configure hardware to quit deep sleep state
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int sbi_exit_deep_sleep(wlan_private * priv)
{

    /* set Wakeup bit */
    return gspi_write_reg(HOST_INT_CTRL_REG,
                          HIC_DEFAULT_VALUE | HIC_WakeUp);
}

/** 
 *  @brief clear the Wake up bit in Host Interrupt Control Register
 * 
 *  @param priv         A pointer to wlan_private structure
 *  @return 	        WLAN_STATUS_SUCCESS or WLAN_STATUS_FAILURE
 */
int sbi_reset_deepsleep_wakeup( wlan_private *priv)
{

    /* clear wakeup bit */
    return gspi_write_reg(HOST_INT_CTRL_REG,
                          HIC_DEFAULT_VALUE & ~HIC_WakeUp);
}

