/* ===================================================================================
 * Copyright (c) <2009> Synopsys, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software annotated with this license and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including without
 * limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * =================================================================================== */


/** \file
 * This is the network dependent layer to handle network related functionality.
 * This file is tightly coupled to neworking frame work of linux 2.6.xx kernel.
 * The functionality carried out in this file should be treated as an example only
 * if the underlying operating system is not Linux.
 *
 * \note Many of the functions other than the device specific functions
 *  changes for operating system other than Linux 2.6.xx
 * \internal
 *-----------------------------REVISION HISTORY-----------------------------------
 * Synopsys         01/Aug/2007             Created
 */

#include "NuMicro.h"
#include "synopGMAC_network_interface.h"


void synopGMAC_powerup_mac(synopGMACdevice *gmacdev)
{
    gmacdev->GMAC_Power_down = 0;    // Let ISR know that MAC is out of power down now
    if (synopGMAC_is_magic_packet_received(gmacdev))
        TR("GMAC wokeup due to Magic Pkt Received\n");
    if (synopGMAC_is_wakeup_frame_received(gmacdev))
        TR("GMAC wokeup due to Wakeup Frame Received\n");
    //Disable the assertion of PMT interrupt
    synopGMAC_pmt_int_disable(gmacdev);
    //Enable the mac and Dma rx and tx paths
    synopGMAC_rx_enable(gmacdev);
    synopGMAC_enable_dma_rx(gmacdev);

    synopGMAC_tx_enable(gmacdev);
    synopGMAC_enable_dma_tx(gmacdev);

    return;
}

void synopGMAC_powerdown_mac(synopGMACdevice *gmacdev)
{
    TR("Put the GMAC to power down mode..\n");

    // Disable the Dma engines in tx path
    gmacdev->GMAC_Power_down = 1;    // Let ISR know that Mac is going to be in the power down mode
    synopGMAC_disable_dma_tx(gmacdev);
    plat_delay(DEFAULT_LOOP_VARIABLE);      //allow any pending transmission to complete
    // Disable the Mac for both tx and rx
    synopGMAC_tx_disable(gmacdev);
    synopGMAC_rx_disable(gmacdev);
    plat_delay(DEFAULT_LOOP_VARIABLE);      //Allow any pending buffer to be read by host
    //Disable the Dma in rx path
    synopGMAC_disable_dma_rx(gmacdev);

    //enable the power down mode
    //synopGMAC_pmt_unicast_enable(gmacdev);

    //prepare the gmac for magic packet reception and wake up frame reception
    synopGMAC_magic_packet_enable(gmacdev);

    //gate the application and transmit clock inputs to the code. This is not done in this driver :).

    //enable the Mac for reception
    synopGMAC_rx_enable(gmacdev);

    //Enable the assertion of PMT interrupt
    synopGMAC_pmt_int_enable(gmacdev);

    //enter the power down mode
    synopGMAC_power_down_enable(gmacdev);

    return;
}

#if 0
void synopGMAC_powerdown_mac(synopGMACdevice *gmacdev)
{
    TR0("Put the GMAC to power down mode..\n");
    // Disable the Dma engines in tx path
    GMAC_Power_down = 1;    // Let ISR know that Mac is going to be in the power down mode
    synopGMAC_disable_dma_tx(gmacdev);
    plat_delay(DEFAULT_LOOP_VARIABLE);      //allow any pending transmission to complete
    // Disable the Mac for both tx and rx
    synopGMAC_tx_disable(gmacdev);
    synopGMAC_rx_disable(gmacdev);
    plat_delay(DEFAULT_LOOP_VARIABLE);      //Allow any pending buffer to be read by host
    //Disable the Dma in rx path
    synopGMAC_disable_dma_rx(gmacdev);

    //enable the power down mode
    //synopGMAC_pmt_unicast_enable(gmacdev);

    //prepare the gmac for magic packet reception and wake up frame reception
    synopGMAC_magic_packet_enable(gmacdev);

    //gate the application and transmit clock inputs to the code. This is not done in this driver :).

    //enable the Mac for reception
    synopGMAC_rx_enable(gmacdev);

    //Enable the assertion of PMT interrupt
    synopGMAC_pmt_int_enable(gmacdev);
    //enter the power down mode
    synopGMAC_power_down_enable(gmacdev);
    return;
}

void synopGMAC_powerup_mac(synopGMACdevice *gmacdev)
{
    GMAC_Power_down = 0;    // Let ISR know that MAC is out of power down now
    if (synopGMAC_is_magic_packet_received(gmacdev))
        TR("GMAC wokeup due to Magic Pkt Received\n");
    if (synopGMAC_is_wakeup_frame_received(gmacdev))
        TR("GMAC wokeup due to Wakeup Frame Received\n");
    //Disable the assertion of PMT interrupt
    synopGMAC_pmt_int_disable(gmacdev);
    //Enable the mac and Dma rx and tx paths
    synopGMAC_rx_enable(gmacdev);
    synopGMAC_enable_dma_rx(gmacdev);

    synopGMAC_tx_enable(gmacdev);
    synopGMAC_enable_dma_tx(gmacdev);
    return;
}
#endif

/**
  * This sets up the transmit Descriptor queue in ring or chain mode.
  * This function is tightly coupled to the platform and operating system
  * Device is interested only after the descriptors are setup. Therefore this function
  * is not included in the device driver API. This function should be treated as an
  * example code to design the descriptor structures for ring mode or chain mode.
  * This function depends on the pcidev structure for allocation consistent dma-able memory in case of linux.
  * This limitation is due to the fact that linux uses pci structure to allocate a dmable memory
  * - Allocates the memory for the descriptors.
  * - Initialize the Busy and Next descriptors indices to 0(Indicating first descriptor).
  * - Initialize the Busy and Next descriptors to first descriptor address.
  *     - Initialize the last descriptor with the endof ring in case of ring mode.
  * - Initialize the descriptors in chain mode.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] pointer to pci_device structure.
  * @param[in] number of descriptor expected in tx descriptor queue.
  * @param[in] whether descriptors to be created in RING mode or CHAIN mode.
  * \return 0 upon success. Error code upon failure.
  * \note This function fails if allocation fails for required number of descriptors in Ring mode, but in chain mode
  *  function returns -ESYNOPGMACNOMEM in the process of descriptor chain creation. once returned from this function
  *  user should for gmacdev->TxDescCount to see how many descriptors are there in the chain. Should continue further
  *  only if the number of descriptors in the chain meets the requirements
  */

s32 synopGMAC_setup_tx_desc_queue(synopGMACdevice *gmacdev, DmaDesc *first_desc, u32 no_of_desc, u32 desc_mode)
{
    s32 i;

    TR("Total size of memory required for Tx Descriptors in Ring Mode = 0x%08x\n", ((sizeof(DmaDesc) * no_of_desc)));

    gmacdev->TxDescCount = no_of_desc;

#ifdef CACHE_ON
    gmacdev->TxDesc      = (DmaDesc *)((u32)first_desc | UNCACHEABLE) ;
#else
    gmacdev->TxDesc      = first_desc;
#endif

    gmacdev->TxDescDma   = (dma_addr_t)first_desc;

    for (i = 0; i < gmacdev -> TxDescCount; i++)
    {
        synopGMAC_tx_desc_init_ring((DmaDesc *)gmacdev->TxDesc + i, i == gmacdev->TxDescCount - 1);

        TR("%02d %08x \n", i, (unsigned int)(gmacdev->TxDesc + i));
        TR("status: %08x\n", (unsigned int)((gmacdev->TxDesc + i))->status);
        TR("length: %08x\n", (unsigned int)((gmacdev->TxDesc + i)->length));
        TR("buffer1: %08x\n", (unsigned int)((gmacdev->TxDesc + i)->buffer1));
        TR("buffer2: %08x\n", (unsigned int)((gmacdev->TxDesc + i)->buffer2));
        TR("extstatus: %08x\n", (unsigned int)((gmacdev->TxDesc + i)->extstatus));
        TR("reserved1: %08x\n", (unsigned int)((gmacdev->TxDesc + i)->reserved1));
        TR("timestamplow: %08x\n", (unsigned int)((gmacdev->TxDesc + i)->timestamplow));
        TR("timestamphigh: %08x\n", (unsigned int)((gmacdev->TxDesc + i)->timestamphigh));
//        TR("data1: %08x\n", (unsigned int)((gmacdev->TxDesc + i)->data1));
//        TR("data2: %08x\n", (unsigned int)((gmacdev->TxDesc + i)->data2));
    }

    gmacdev->TxNext = 0;
    gmacdev->TxBusy = 0;
    gmacdev->TxNextDesc = gmacdev->TxDesc;
    gmacdev->TxBusyDesc = gmacdev->TxDesc;
    gmacdev->BusyTxDesc  = 0;

    return 0;
}


/**
  * This sets up the receive Descriptor queue in ring or chain mode.
  * This function is tightly coupled to the platform and operating system
  * Device is interested only after the descriptors are setup. Therefore this function
  * is not included in the device driver API. This function should be treated as an
  * example code to design the descriptor structures in ring mode or chain mode.
  * This function depends on the pcidev structure for allocation of consistent dma-able memory in case of linux.
  * This limitation is due to the fact that linux uses pci structure to allocate a dmable memory
  * - Allocates the memory for the descriptors.
  * - Initialize the Busy and Next descriptors indices to 0(Indicating first descriptor).
  * - Initialize the Busy and Next descriptors to first descriptor address.
  *     - Initialize the last descriptor with the endof ring in case of ring mode.
  * - Initialize the descriptors in chain mode.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] pointer to pci_device structure.
  * @param[in] number of descriptor expected in rx descriptor queue.
  * @param[in] whether descriptors to be created in RING mode or CHAIN mode.
  * \return 0 upon success. Error code upon failure.
  * \note This function fails if allocation fails for required number of descriptors in Ring mode, but in chain mode
  *  function returns -ESYNOPGMACNOMEM in the process of descriptor chain creation. once returned from this function
  *  user should for gmacdev->RxDescCount to see how many descriptors are there in the chain. Should continue further
  *  only if the number of descriptors in the chain meets the requirements
  */
s32 synopGMAC_setup_rx_desc_queue(synopGMACdevice *gmacdev, DmaDesc *first_desc, u32 no_of_desc, u32 desc_mode)
{
    s32 i;

    TR("total size of memory required for Rx Descriptors in Ring Mode = 0x%08x\n", ((sizeof(DmaDesc) * no_of_desc)));

    gmacdev->RxDescCount = no_of_desc;
#ifdef CACHE_ON
    gmacdev->RxDesc      = (DmaDesc *)((u32)first_desc | UNCACHEABLE) ;
#else
    gmacdev->RxDesc      = first_desc;
#endif
    gmacdev->RxDescDma   = (dma_addr_t)((u32)first_desc);

    for (i = 0; i < gmacdev -> RxDescCount; i++)
    {
        synopGMAC_rx_desc_init_ring((DmaDesc *)gmacdev->RxDesc + i, i == gmacdev->RxDescCount - 1);
        TR("%02d %08x \n", i, (unsigned int)(gmacdev->RxDesc + i));
    }


    gmacdev->RxNext = 0;
    gmacdev->RxBusy = 0;
    gmacdev->RxNextDesc = gmacdev->RxDesc;
    gmacdev->RxBusyDesc = gmacdev->RxDesc;

    gmacdev->BusyRxDesc   = 0;

    return 0;
}

/**
  * This gives up the receive Descriptor queue in ring or chain mode.
  * This function is tightly coupled to the platform and operating system
  * Once device's Dma is stopped the memory descriptor memory and the buffer memory deallocation,
  * is completely handled by the operating system, this call is kept outside the device driver Api.
  * This function should be treated as an example code to de-allocate the descriptor structures in ring mode or chain mode
  * and network buffer deallocation.
  * This function depends on the pcidev structure for dma-able memory deallocation for both descriptor memory and the
  * network buffer memory under linux.
  * The responsibility of this function is to
  *     - Free the network buffer memory if any.
  * - Fee the memory allocated for the descriptors.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] pointer to pci_device structure.
  * @param[in] number of descriptor expected in rx descriptor queue.
  * @param[in] whether descriptors to be created in RING mode or CHAIN mode.
  * \return 0 upon success. Error code upon failure.
  * \note No referece should be made to descriptors once this function is called. This function is invoked when the device is closed.
  */
void synopGMAC_giveup_rx_desc_queue(synopGMACdevice *gmacdev, u32 desc_mode)
{
    gmacdev->RxDesc    = NULL;
    gmacdev->RxDescDma = 0;
    return;
}

/**
  * This gives up the transmit Descriptor queue in ring or chain mode.
  * This function is tightly coupled to the platform and operating system
  * Once device's Dma is stopped the memory descriptor memory and the buffer memory deallocation,
  * is completely handled by the operating system, this call is kept outside the device driver Api.
  * This function should be treated as an example code to de-allocate the descriptor structures in ring mode or chain mode
  * and network buffer deallocation.
  * This function depends on the pcidev structure for dma-able memory deallocation for both descriptor memory and the
  * network buffer memory under linux.
  * The responsibility of this function is to
  *     - Free the network buffer memory if any.
  * - Fee the memory allocated for the descriptors.
  * @param[in] pointer to synopGMACdevice.
  * @param[in] pointer to pci_device structure.
  * @param[in] number of descriptor expected in tx descriptor queue.
  * @param[in] whether descriptors to be created in RING mode or CHAIN mode.
  * \return 0 upon success. Error code upon failure.
  * \note No reference should be made to descriptors once this function is called. This function is invoked when the device is closed.
  */
void synopGMAC_giveup_tx_desc_queue(synopGMACdevice *gmacdev, u32 desc_mode)
{


    gmacdev->TxDesc    = NULL;
    gmacdev->TxDescDma = 0;
    return;
}

void synopGMAC_set_speed(synopGMACdevice *gmacdev)
{
    switch (gmacdev->Speed)
    {
    case SPEED1000:
        synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacMiiGmii);
        break;
    case SPEED100:
        synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacMiiGmii);
        synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacFESpeed100);
        break;
    case SPEED10:
        synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacMiiGmii);
        synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacFESpeed100);
    default:
        break;
    }
}

/**
 * Function to transmit a given packet on the wire.
 * Whenever Linux Kernel has a packet ready to be transmitted, this function is called.
 * The function prepares a packet and prepares the descriptor and
 * enables/resumes the transmission.
 * @param[in] pointer to sk_buff structure.
 * @param[in] pointer to net_device structure.
 * \return Returns 0 on success and Error code on failure.
 * \note structure sk_buff is used to hold packet in Linux networking stacks.
 */
s32 synopGMAC_xmit_frames(synopGMACdevice *gmacdev, u8 *pkt_data, u32 pkt_len, u32 offload_needed, u32 ts)
{
    s32 status = 0;
    u32 dma_addr = (u32)pkt_data;

    /*Now we have skb ready and OS invoked this function. Lets make our DMA know about this*/
    status = synopGMAC_set_tx_qptr(gmacdev, dma_addr, pkt_len, dma_addr, offload_needed, ts);
    if (status < 0)
    {
        TR0("%s No More Free Tx Descriptors\n", __FUNCTION__);
        return -1;
    }

    /*Now force the DMA to start transmission*/
    synopGMAC_resume_dma_tx(gmacdev);

    return 0;
}


/**
 * Function to handle housekeeping after a packet is transmitted over the wire.
 * After the transmission of a packet DMA generates corresponding interrupt
 * (if it is enabled). It takes care of returning the sk_buff to the linux
 * kernel, updating the networking statistics and tracking the descriptors.
 * @param[in] pointer to net_device structure.
 * \return void.
 * \note This function runs in interrupt context
 */
void synop_handle_transmit_over(synopGMACdevice *gmacdev)
{
    s32 desc_index;
    u32 data1;
    u32 status;
    u32 length1;
    u32 dma_addr1;

    u32 ext_status;
    //u16 time_stamp_higher;
    u32 time_stamp_high;
    u32 time_stamp_low;

    /*Handle the transmit Descriptors*/
    do
    {
        desc_index = synopGMAC_get_tx_qptr(gmacdev, &status, &dma_addr1, &length1, &data1, &ext_status, &time_stamp_high, &time_stamp_low);
        //synopGMAC_TS_read_timestamp_higher_val(gmacdev, &time_stamp_higher);

        if (desc_index >= 0 /*&& data1 != 0*/)
        {
            TR("Finished Transmit at Tx Descriptor %d for buffer = %08x whose status is %08x \n", desc_index, dma_addr1, status);

            if (synopGMAC_is_tx_ipv4header_checksum_error(gmacdev, status))
            {
                TR("Harware Failed to Insert IPV4 Header Checksum\n");
                gmacdev->synopGMACNetStats.tx_ip_header_errors++;
            }
            if (synopGMAC_is_tx_payload_checksum_error(gmacdev, status))
            {
                TR("Harware Failed to Insert Payload Checksum\n");
                gmacdev->synopGMACNetStats.tx_ip_payload_errors++;
            }

            if (synopGMAC_is_desc_valid(status))
            {
                gmacdev->synopGMACNetStats.tx_bytes += length1;
                gmacdev->synopGMACNetStats.tx_packets++;
                if (status & DescTxTSStatus)
                {
                    gmacdev->tx_sec = time_stamp_high;
                    gmacdev->tx_subsec = time_stamp_low;
                }
                else
                {
                    gmacdev->tx_sec = 0;
                    gmacdev->tx_subsec = 0;
                }
            }
            else
            {
                TR("Error in Status %08x\n", status);
                gmacdev->synopGMACNetStats.tx_errors++;
                gmacdev->synopGMACNetStats.tx_aborted_errors += synopGMAC_is_tx_aborted(status);
                gmacdev->synopGMACNetStats.tx_carrier_errors += synopGMAC_is_tx_carrier_error(status);
            }
        }
        gmacdev->synopGMACNetStats.collisions += synopGMAC_get_tx_collision_count(status);
    }
    while (desc_index >= 0);
}

/**
 * Function to Receive a packet from the interface.
 * After Receiving a packet, DMA transfers the received packet to the system memory
 * and generates corresponding interrupt (if it is enabled). This function prepares
 * the sk_buff for received packet after removing the ethernet CRC, and hands it over
 * to linux networking stack.
 *  - Updataes the networking interface statistics
 *  - Keeps track of the rx descriptors
 * @param[in] pointer to net_device structure.
 * \return void.
 * \note This function runs in interrupt context.
 */
extern DmaDesc *prevtx;   // for CRC test
s32 synop_handle_received_data(synopGMACdevice *gmacdev, PKT_FRAME_T **ppsPktFrame)
{
    u32 data1;
    u32 len;
    u32 status;
    u32 dma_addr1;

    u32 ext_status;
    //u16 time_stamp_higher;
    u32 time_stamp_high;
    u32 time_stamp_low;

    /* Handle the Receive Descriptors */
    if (synopGMAC_get_rx_qptr(gmacdev, &status,
                              &dma_addr1, NULL, &data1,
                              &ext_status, &time_stamp_high, &time_stamp_low) >= 0)
    {
        //synopGMAC_TS_read_timestamp_higher_val(gmacdev, &time_stamp_higher);
        //TR("S:%08x ES:%08x DA1:%08x d1:%08x TSH:%08x TSL:%08x TSHW:%08x \n",status,ext_status,dma_addr1, data1,time_stamp_high,time_stamp_low,time_stamp_higher);
        TR("S:%08x ES:%08x DA1:%08x d1:%08x TSH:%08x TSL:%08x\n", status, ext_status, dma_addr1, data1, time_stamp_high, time_stamp_low);

        TR("Received Data at Rx Descriptor for skb 0x%08x whose status is %08x\n", data1, status);

        if (synopGMAC_is_rx_desc_valid(status))
        {
            // Always enter this loop. synopGMAC_is_rx_desc_valid() also report invalid descriptor
            // if there's packet error generated by test code and drop it. But we need to execute ext_status
            // check code to tell what's going on.                                          --ya

            len =  synopGMAC_get_rx_desc_frame_length(status) - 4; //Not interested in Ethernet CRC bytes


            // Now lets check for the IPC offloading
            /*  Since we have enabled the checksum offloading in hardware, lets inform the kernel
                not to perform the checksum computation on the incoming packet. Note that ip header
                checksum will be computed by the kernel immaterial of what we inform. Similary TCP/UDP/ICMP
                pseudo header checksum will be computed by the stack. What we can inform is not to perform
                payload checksum.
                When CHECKSUM_UNNECESSARY is set kernel bypasses the checksum computation.
            */

            TR("Checksum Offloading will be done now\n");

            if (synopGMAC_is_ext_status(gmacdev, status))  // extended status present indicates that the RDES4 need to be probed
            {
                TR("Extended Status present\n");
                if (synopGMAC_ES_is_IP_header_error(gmacdev, ext_status))      // IP header (IPV4) checksum error
                {
                    //Linux Kernel doesnot care for ipv4 header checksum. So we will simply proceed by printing a warning ....
                    TR("(EXTSTS)Error in IP header error\n");
                    gmacdev->synopGMACNetStats.rx_ip_header_errors++;
                }
                if (synopGMAC_ES_is_rx_checksum_bypassed(gmacdev, ext_status))  // Hardware engine bypassed the checksum computation/checking
                {
                    TR("(EXTSTS)Hardware bypassed checksum computation\n");
                }
                if (synopGMAC_ES_is_IP_payload_error(gmacdev, ext_status))      // IP payload checksum is in error (UDP/TCP/ICMP checksum error)
                {
                    TR("(EXTSTS) Error in EP payload\n");
                    gmacdev->synopGMACNetStats.rx_ip_payload_errors++;
                }
            }
            else     // No extended status. So relevant information is available in the status itself
            {
                if (synopGMAC_is_rx_checksum_error(gmacdev, status) == RxNoChkError)
                {
                    TR("Ip header and TCP/UDP payload checksum Bypassed <Chk Status = 4>  \n");
                }
                if (synopGMAC_is_rx_checksum_error(gmacdev, status) == RxIpHdrChkError)
                {
                    //Linux Kernel doesnot care for ipv4 header checksum. So we will simply proceed by printing a warning ....
                    TR(" Error in 16bit IPV4 Header Checksum <Chk Status = 6>  \n");
                    gmacdev->synopGMACNetStats.rx_ip_header_errors++;
                }
                if (synopGMAC_is_rx_checksum_error(gmacdev, status) == RxLenLT600)
                {
                    TR("IEEE 802.3 type frame with Length field Lesss than 0x0600 <Chk Status = 0> \n");
                }
                if (synopGMAC_is_rx_checksum_error(gmacdev, status) == RxIpHdrPayLoadChkBypass)
                {
                    TR("Ip header and TCP/UDP payload checksum Bypassed <Chk Status = 1>\n");
                }
                if (synopGMAC_is_rx_checksum_error(gmacdev, status) == RxChkBypass)
                {
                    TR("Ip header and TCP/UDP payload checksum Bypassed <Chk Status = 3>  \n");
                }
                if (synopGMAC_is_rx_checksum_error(gmacdev, status) == RxPayLoadChkError)
                {
                    TR(" TCP/UDP payload checksum Error <Chk Status = 5>  \n");
                    gmacdev->synopGMACNetStats.rx_ip_payload_errors++;
                }
                if (synopGMAC_is_rx_checksum_error(gmacdev, status) == RxIpHdrPayLoadChkError)
                {
                    //Linux Kernel doesnot care for ipv4 header checksum. So we will simply proceed by printing a warning ....
                    TR(" Both IP header and Payload Checksum Error <Chk Status = 7>  \n");
                    gmacdev->synopGMACNetStats.rx_ip_header_errors++;
                    gmacdev->synopGMACNetStats.rx_ip_payload_errors++;
                }
            }
            *ppsPktFrame = (PKT_FRAME_T *)dma_addr1;
#if 0
#ifdef CACHE_ON
            memcpy((void *)pu8rb, (void *)((u32)dma_addr1 | UNCACHEABLE), len);
#else
            memcpy((void *)pu8rb, (void *)((u32)dma_addr1), len);
#endif
            if (prevtx != NULL)
            {
#ifdef CACHE_ON
                memcpy((void *)pu8rb + len, (void *)((u32)(dma_addr1 | UNCACHEABLE) + len), 4);
#else
                memcpy((void *)pu8rb + len, (void *)((u32)dma_addr1 + len), 4);
#endif
            }
//            rb->rdy = 1;
//            rb->len = len;
#endif
            gmacdev->synopGMACNetStats.rx_packets++;
            gmacdev->synopGMACNetStats.rx_bytes += len;
            if (status & DescRxTSAvailable)
            {
                gmacdev->rx_sec = time_stamp_high;
                gmacdev->rx_subsec = time_stamp_low;
            }
            else
            {
                gmacdev->rx_sec = 0;
                gmacdev->rx_subsec = 0;
            }
            return len;
        } // if ( synopGMAC_is_rx_desc_valid(status) )
        else
        {
            /*Now the present skb should be set free*/
            TR("s: %08x\n", status);
            gmacdev->synopGMACNetStats.rx_errors++;
            gmacdev->synopGMACNetStats.collisions       += synopGMAC_is_rx_frame_collision(status);
            gmacdev->synopGMACNetStats.rx_crc_errors    += synopGMAC_is_rx_crc(status);
            gmacdev->synopGMACNetStats.rx_frame_errors  += synopGMAC_is_frame_dribbling_errors(status);
            gmacdev->synopGMACNetStats.rx_length_errors += synopGMAC_is_rx_frame_length_errors(status);
        }

    } //    /*Handle the Receive Descriptors*/

    return 0;
}

// mode 0: 1000Mbps, 1: 100Mbps, 2: 10Mbps
void synopGMAC_set_mode(synopGMACdevice *gmacdev, int mode)
{
    // Must stop Tx/Rx before change speed/mode
    synopGMAC_tx_disable(gmacdev);
    synopGMAC_rx_disable(gmacdev);
    switch (mode)
    {
    case SPEED1000:
        synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacMiiGmii);
        gmacdev->Speed = SPEED1000;
        break;
    case SPEED100:
        synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacMiiGmii);
        synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacFESpeed100);
        gmacdev->Speed = SPEED100;
        break;
    case SPEED10:
        synopGMACSetBits(gmacdev->MacBase, GmacConfig, GmacMiiGmii);
        synopGMACClearBits(gmacdev->MacBase, GmacConfig, GmacFESpeed100);
        gmacdev->Speed = SPEED10;
    default:
        break;
    }
    synopGMAC_tx_enable(gmacdev);
    synopGMAC_rx_enable(gmacdev);
}
