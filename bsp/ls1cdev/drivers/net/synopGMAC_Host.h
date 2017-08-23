#ifndef SYNOP_GMAC_HOST_H
#define SYNOP_GMAC_HOST_H 1

/*
#include <linux/pci.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
*/

#include "synopGMAC_plat.h"
//#include "synopGMAC_pci_bus_interface.h"
#include "synopGMAC_Dev.h"
#include "mii.h"

//#define ENH_DESC
//#define ENH_DESC_8W


struct net_device_stats
{
	unsigned long	rx_packets;		/* total packets received	*/
	unsigned long	tx_packets;		/* total packets transmitted	*/
	unsigned long	rx_bytes;		/* total bytes received 	*/
	unsigned long	tx_bytes;		/* total bytes transmitted	*/
	unsigned long	rx_errors;		/* bad packets received		*/
	unsigned long	tx_errors;		/* packet transmit problems	*/
	unsigned long	rx_dropped;		/* no space in linux buffers	*/
	unsigned long	tx_dropped;		/* no space available in linux	*/
	unsigned long	multicast;		/* multicast packets received	*/
	unsigned long	collisions;

	/* detailed rx_errors: */
	unsigned long	rx_length_errors;
	unsigned long	rx_over_errors;		/* receiver ring buff overflow	*/
	unsigned long	rx_crc_errors;		/* recved pkt with crc error	*/
	unsigned long	rx_frame_errors;	/* recv'd frame alignment error */
	unsigned long	rx_fifo_errors;		/* recv'r fifo overrun		*/
	unsigned long	rx_missed_errors;	/* receiver missed packet	*/

	/* detailed tx_errors */
	unsigned long	tx_aborted_errors;
	unsigned long	tx_carrier_errors;
	unsigned long	tx_fifo_errors;
	unsigned long	tx_heartbeat_errors;
	unsigned long	tx_window_errors;
	
	/* for cslip etc */
	unsigned long	rx_compressed;
	unsigned long	tx_compressed;
};

/*
struct	PmonInet{
	struct device sc_dev;
	void *sc_ih;

	struct arpcom arpcom;
		
//	struct mii_data sc_mii;		// MII media information 
	char  dev_addr[6]; //the net interface's address
	unsigned long ioaddr;

//	int flags;
//	int mc_count;

};
*/	


//typedef struct synopGMACAdapterStruct{
#if 0
struct synopGMACAdapterStruct{

/*Device Dependent Data structur*/
struct synopGMACdevice * synopGMACdev;

/*Os/Platform Dependent Data Structures*/
//struct pci_dev * synopGMACpcidev;

//struct net_device *synopGMACnetdev;

struct net_device_stats synopGMACNetStats;
//u32 synopGMACPciState[16];

struct PmonInet * PInetdev;

//} synopGMACPciNetworkAdapter;
}synopGMACNetworkAdapter;
#endif
typedef struct synopGMACNetworkAdapter{

/*Device Dependent Data structur*/
synopGMACdevice * synopGMACdev;

/*Os/Platform Dependent Data Structures*/
//struct pci_dev * synopGMACpcidev;

//struct net_device *synopGMACnetdev;

struct net_device_stats synopGMACNetStats;
//u32 synopGMACPciState[16];

//struct PmonInet * PInetdev;

struct mii_if_info mii;
} synopGMACPciNetworkAdapter;

/*
static struct mbuf * getmbuf(struct synopGMACNetworkAdapter * tp)
{
	struct mbuf *m;
//	struct PomnInet * tp = adapter->PInetDev;

	MGETHDR(m, M_DONTWAIT, MT_DATA);
	if(m == NULL){
		printf("getmbuf failed, Out of memory!!!\n");
		return  NULL;
	} else {
		MCLGET(m, M_DONTWAIT);
		if ((m->m_flags & M_EXT) == 0) {
			m_freem(m);
			return NULL;
		}
		if(m->m_data != m->m_ext.ext_buf){
			printf("m_data not equal to ext_buf!!!\n");
		}
	}
	
#if defined(__mips__)

//	pci_sync_cache(tp->sc_pc, (vm_offset_t)tp->tx_buffer[entry], len, SYNC_W);

	;
#define RFA_ALIGNMENT_FUDGE 2
	m->m_data += RFA_ALIGNMENT_FUDGE;
#else
	m->m_data += RFA_ALIGNMENT_FUDGE;
#endif
	return m;
}
*/




#endif
