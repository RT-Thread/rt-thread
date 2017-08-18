#include <rtthread.h>
#include <rthw.h>
#include <bsp.h>


typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned int    DWORD;

#include "pci-main.h"

#define     TRUE        RT_TRUE
#define     FALSE       RT_FALSE
#define     NULL        RT_NULL

extern void rt_console_putc(int c);
extern rt_bool_t rt_hw_irq_set_level_trigger(int irq_num);
extern rt_bool_t rt_hw_irq_set_edge_trigger(int irq_num);

#define _sys_printf  rt_kprintf
#define _sys_kmalloc rt_malloc
#define _sys_memset32  rt_memset
#define _sys_memcpy  rt_memcpy
#define _sys_putchar  rt_console_putc

#define disable_IRQ_line rt_hw_interrupt_mask
#define enable_IRQ_line  rt_hw_interrupt_umask
#define _sys_set_irq_handle(irq, handle)     rt_hw_interrupt_install(irq, handler, RT_NULL, "pci");
#define _sys_irq_set_level_trigger rt_hw_irq_set_level_trigger
#define _sys_irq_set_edge_trigger  rt_hw_irq_set_edge_trigger

#define     CONFIG_ADDRESS_REG          0x0cf8
#define     CONFIG_DATA_REG             0x0cfc

#define     STATUS_REG_OFFSET           0x06
#define     CONFIG_COMMAND_OFFSET       0x04

#define     MAX_DEVICE                  256

#define     DEVICE(vid, did, name)                              \
    {PCI_VENDOR_ID_##vid, PCI_DEVICE_ID_##did, (name), 0xff}

#define     BRIDGE(vid, did, name, bridge)                          \
    {PCI_VENDOR_ID_##vid, PCI_DEVICE_ID_##did, (name), (bridge)}
    

static pci_dev  *pci_root = NULL;

static void do_pci_search_all_device(void);
void pci_search_all_device(void);
static pci_vendor_info *search_vendor_info(WORD vendor_id, WORD device_id);
static int insert_new_pcidev(pci_dev *pci);

static void print_device_type(pci_dev *device);
//static void print_pci_resouce(BYTE bus_id, BYTE device_num, BYTE function_num);

static int check_multiple(pci_dev *device);
static void get_pci_resouce(pci_dev *device);
static void pciDecodeBar(pci_dev *device, BYTE offset, DWORD *base_addr, DWORD *addr_size, int *prefetch);

static pci_vendor_info  vendor_list[] = {
    DEVICE( COMPAQ,     COMPAQ_1280,    "QVision 1280/p"),
    DEVICE( COMPAQ,     COMPAQ_NETELL100,"Netelligent 10/100"),
    DEVICE( COMPAQ,     COMPAQ_NETELL10,"Netelligent 10"),
    DEVICE( COMPAQ,     COMPAQ_NETFLEX3,"NetFlex 3"),
    DEVICE( COMPAQ,     COMPAQ_THUNDER, "ThunderLAN"),
    DEVICE( NCR,        NCR_53C810, "53c810"),
    DEVICE( NCR,        NCR_53C820, "53c820"),
    DEVICE( NCR,        NCR_53C825, "53c825"),
    DEVICE( NCR,        NCR_53C815, "53c815"),
    DEVICE( NCR,        NCR_53C860, "53c860"),
    DEVICE( NCR,        NCR_53C896, "53c896"),
    DEVICE( NCR,        NCR_53C895, "53c895"),
    DEVICE( NCR,        NCR_53C885, "53c885"),
    DEVICE( NCR,        NCR_53C875, "53c875"),
    DEVICE( ATI,        ATI_68800,      "68800AX"),
    DEVICE( ATI,        ATI_215CT222,   "215CT222"),
    DEVICE( ATI,        ATI_210888CX,   "210888CX"),
    DEVICE( ATI,        ATI_215GT,  "Mach64 GT (Rage II)"),
    DEVICE( ATI,        ATI_210888GX,   "210888GX"),
    DEVICE( ATI,        ATI_264VT,  "Mach64 VT"),
    DEVICE( VLSI,       VLSI_82C592,    "82C592-FC1"),
    DEVICE( VLSI,       VLSI_82C593,    "82C593-FC1"),
    DEVICE( VLSI,       VLSI_82C594,    "82C594-AFC2"),
    DEVICE( VLSI,       VLSI_82C597,    "82C597-AFC2"),
    DEVICE( VLSI,       VLSI_VAS96011,  "VAS96011 PowerPC"),
    DEVICE( ADL,        ADL_2301,   "2301"),
    DEVICE( NS,     NS_87410,   "87410"),
    DEVICE( TSENG,      TSENG_W32P_2,   "ET4000W32P"),
    DEVICE( TSENG,      TSENG_W32P_b,   "ET4000W32P rev B"),
    DEVICE( TSENG,      TSENG_W32P_c,   "ET4000W32P rev C"),
    DEVICE( TSENG,      TSENG_W32P_d,   "ET4000W32P rev D"),
    DEVICE( TSENG,      TSENG_ET6000,   "ET6000"),
    DEVICE( WEITEK,     WEITEK_P9000,   "P9000"),
    DEVICE( WEITEK,     WEITEK_P9100,   "P9100"),
    BRIDGE( DEC,        DEC_BRD,    "DC21050",      0x00),
    DEVICE( DEC,        DEC_TULIP,  "DC21040"),
    DEVICE( DEC,        DEC_TGA,    "DC21030"),
    DEVICE( DEC,        DEC_TULIP_FAST, "DC21140"),
    DEVICE( DEC,        DEC_FDDI,   "DEFPA"),
    DEVICE( DEC,        DEC_TULIP_PLUS, "DC21041"),
    DEVICE( DEC,        DEC_21142,  "DC21142"),
    DEVICE( DEC,        DEC_21052,  "DC21052"),
    DEVICE( DEC,        DEC_21152,  "DC21152"),
    DEVICE( CIRRUS,     CIRRUS_7548,    "GD 7548"),
    DEVICE( CIRRUS,     CIRRUS_5430,    "GD 5430"),
    DEVICE( CIRRUS,     CIRRUS_5434_4,  "GD 5434"),
    DEVICE( CIRRUS,     CIRRUS_5434_8,  "GD 5434"),
    DEVICE( CIRRUS,     CIRRUS_5436,    "GD 5436"),
    DEVICE( CIRRUS,     CIRRUS_5446,    "GD 5446"),
    DEVICE( CIRRUS,     CIRRUS_5480,    "GD 5480"),
    DEVICE( CIRRUS,     CIRRUS_5464,    "GD 5464"),
    DEVICE( CIRRUS,     CIRRUS_5465,    "GD 5465"),
    DEVICE( CIRRUS,     CIRRUS_6729,    "CL 6729"),
    DEVICE( CIRRUS,     CIRRUS_6832,    "PD 6832"),
    DEVICE( CIRRUS,     CIRRUS_7542,    "CL 7542"),
    DEVICE( CIRRUS,     CIRRUS_7543,    "CL 7543"),
    DEVICE( CIRRUS,     CIRRUS_7541,    "CL 7541"),
    DEVICE( IBM,        IBM_FIRE_CORAL, "Fire Coral"),
    DEVICE( IBM,        IBM_82G2675,    "82G2675"),
    DEVICE( IBM,        IBM_82351,  "82351"),
    DEVICE( WD,     WD_7197,    "WD 7197"),
    DEVICE( AMD,        AMD_LANCE,  "79C970"),
    DEVICE( AMD,        AMD_SCSI,   "53C974"),
    DEVICE( TRIDENT,    TRIDENT_9420,   "TG 9420"),
    DEVICE( TRIDENT,    TRIDENT_9440,   "TG 9440"),
    DEVICE( TRIDENT,    TRIDENT_9660,   "TG 9660"),
    DEVICE( AI,     AI_M1435,   "M1435"),
    DEVICE( MATROX,     MATROX_MGA_2,   "Atlas PX2085"),
    DEVICE( MATROX,     MATROX_MIL, "Millennium"),
    DEVICE( MATROX,     MATROX_MYS, "Mystique"),
    DEVICE( MATROX,     MATROX_MIL_2,   "Millennium II"),
    DEVICE( MATROX,     MATROX_MGA_IMP, "MGA Impression"),
    DEVICE( CT,     CT_65545,   "65545"),
    DEVICE( CT,     CT_65548,   "65548"),
    DEVICE( CT,     CT_65550,   "65550"),
    DEVICE( CT,     CT_65554,   "65554"),
    DEVICE( MIRO,       MIRO_36050, "ZR36050"),
    DEVICE( FD,     FD_36C70,   "TMC-18C30"),
    DEVICE( SI,     SI_6201,    "6201"),
    DEVICE( SI,     SI_6202,    "6202"),
    DEVICE( SI,     SI_503,     "85C503"),
    DEVICE( SI,     SI_6205,    "6205"),
    DEVICE( SI,     SI_501,     "85C501"),
    DEVICE( SI,     SI_496,     "85C496"),
    DEVICE( SI,     SI_601,     "85C601"),
    DEVICE( SI,     SI_5107,    "5107"),
    DEVICE( SI,     SI_5511,        "85C5511"),
    DEVICE( SI,     SI_5513,        "85C5513"),
    DEVICE( SI,     SI_5571,    "5571"),
    DEVICE( SI,     SI_7001,    "7001"),
    DEVICE( HP,     HP_J2585A,  "J2585A"),
    DEVICE( HP,     HP_J2585B,  "J2585B (Lassen)"),
    DEVICE( PCTECH,     PCTECH_RZ1000,  "RZ1000 (buggy)"),
    DEVICE( PCTECH,     PCTECH_RZ1001,  "RZ1001 (buggy?)"),
    DEVICE( DPT,        DPT,        "SmartCache/Raid"),
    DEVICE( OPTI,       OPTI_92C178,    "92C178"),
    DEVICE( OPTI,       OPTI_82C557,    "82C557"),
    DEVICE( OPTI,       OPTI_82C558,    "82C558"),
    DEVICE( OPTI,       OPTI_82C621,    "82C621"),
    DEVICE( OPTI,       OPTI_82C822,    "82C822"),
    DEVICE( SGS,        SGS_2000,   "STG 2000X"),
    DEVICE( SGS,        SGS_1764,   "STG 1764X"),
    DEVICE( BUSLOGIC,   BUSLOGIC_MULTIMASTER_NC, "MultiMaster NC"),
    DEVICE( BUSLOGIC,   BUSLOGIC_MULTIMASTER,    "MultiMaster"),
    DEVICE( BUSLOGIC,   BUSLOGIC_FLASHPOINT,     "FlashPoint"),
    DEVICE( TI,     TI_PCI1130, "PCI1130"),
    DEVICE( TI,     TI_PCI1131, "PCI1131"),
    DEVICE( OAK,        OAK_OTI107, "OTI107"),
    DEVICE( WINBOND2,   WINBOND2_89C940,"NE2000-PCI"),
    DEVICE( MOTOROLA,   MOTOROLA_MPC105,"MPC105 Eagle"),
    DEVICE( MOTOROLA,   MOTOROLA_MPC106,"MPC106 Grackle"),
    DEVICE( MOTOROLA,   MOTOROLA_RAVEN, "Raven"),
    DEVICE( PROMISE,    PROMISE_5300,   "DC5030"),
    DEVICE( N9,     N9_I128,    "Imagine 128"),
    DEVICE( N9,     N9_I128_2,  "Imagine 128v2"),
    DEVICE( UMC,        UMC_UM8673F,    "UM8673F"),
    BRIDGE( UMC,        UMC_UM8891A,    "UM8891A",      0x01),
    DEVICE( UMC,        UMC_UM8886BF,   "UM8886BF"),
    DEVICE( UMC,        UMC_UM8886A,    "UM8886A"),
    BRIDGE( UMC,        UMC_UM8881F,    "UM8881F",      0x02),
    DEVICE( UMC,        UMC_UM8886F,    "UM8886F"),
    DEVICE( UMC,        UMC_UM9017F,    "UM9017F"),
    DEVICE( UMC,        UMC_UM8886N,    "UM8886N"),
    DEVICE( UMC,        UMC_UM8891N,    "UM8891N"),
    DEVICE( X,      X_AGX016,   "ITT AGX016"),
    DEVICE( APPLE,      APPLE_BANDIT,   "Bandit"),
    DEVICE( APPLE,      APPLE_GC,   "Grand Central"),
    DEVICE( APPLE,      APPLE_HYDRA,    "Hydra"),
    DEVICE( NEXGEN,     NEXGEN_82C501,  "82C501"),
    DEVICE( QLOGIC,     QLOGIC_ISP1020, "ISP1020"),
    DEVICE( QLOGIC,     QLOGIC_ISP1022, "ISP1022"),
    DEVICE( LEADTEK,    LEADTEK_805,    "S3 805"),
    DEVICE( CONTAQ,     CONTAQ_82C599,  "82C599"),
    DEVICE( OLICOM,     OLICOM_OC3136,  "OC-3136/3137"),
    DEVICE( OLICOM,     OLICOM_OC2315,  "OC-2315"),
    DEVICE( OLICOM,     OLICOM_OC2325,  "OC-2325"),
    DEVICE( OLICOM,     OLICOM_OC2183,  "OC-2183/2185"),
    DEVICE( OLICOM,     OLICOM_OC2326,  "OC-2326"),
    DEVICE( OLICOM,     OLICOM_OC6151,  "OC-6151/6152"),
    DEVICE( CMD,        CMD_640,    "640 (buggy)"),
    DEVICE( CMD,        CMD_643,    "643"),
    DEVICE( CMD,        CMD_646,    "646"),
    DEVICE( CMD,        CMD_670,    "670"),
    DEVICE( VISION,     VISION_QD8500,  "QD-8500"),
    DEVICE( VISION,     VISION_QD8580,  "QD-8580"),
    DEVICE( BROOKTREE,  BROOKTREE_848,  "Bt848"),
    DEVICE( SIERRA,     SIERRA_STB, "STB Horizon 64"),
    DEVICE( ACC,        ACC_2056,   "2056"),
    DEVICE( WINBOND,    WINBOND_83769,  "W83769F"),
    DEVICE( WINBOND,    WINBOND_82C105, "SL82C105"),
    DEVICE( WINBOND,    WINBOND_83C553, "W83C553"),
    DEVICE( DATABOOK,       DATABOOK_87144, "DB87144"),
    DEVICE( 3COM,       3COM_3C590, "3C590 10bT"),
    DEVICE( 3COM,       3COM_3C595TX,   "3C595 100bTX"),
    DEVICE( 3COM,       3COM_3C595T4,   "3C595 100bT4"),
    DEVICE( 3COM,       3COM_3C595MII,  "3C595 100b-MII"),
    DEVICE( 3COM,       3COM_3C900TPO,  "3C900 10bTPO"),
    DEVICE( 3COM,       3COM_3C900COMBO,"3C900 10b Combo"),
    DEVICE( 3COM,       3COM_3C905TX,   "3C905 100bTX"),
    DEVICE( AL,     AL_M1445,   "M1445"),
    DEVICE( AL,     AL_M1449,   "M1449"),
    DEVICE( AL,     AL_M1451,   "M1451"),
    DEVICE( AL,     AL_M1461,   "M1461"),
    DEVICE( AL,     AL_M1489,   "M1489"),
    DEVICE( AL,     AL_M1511,   "M1511"),
    DEVICE( AL,     AL_M1513,   "M1513"),
    DEVICE( AL,     AL_M4803,   "M4803"),
    DEVICE( NEOMAGIC,       NEOMAGIC_MAGICGRAPH_NM2070,     "Magicgraph NM2070"),
    DEVICE( NEOMAGIC,   NEOMAGIC_MAGICGRAPH_128V, "MagicGraph 128V"),
    DEVICE( ASP,        ASP_ABP940, "ABP940"),
    DEVICE( ASP,        ASP_ABP940U,    "ABP940U"),
    DEVICE( CERN,       CERN_SPSB_PMC,  "STAR/RD24 SCI-PCI (PMC)"),
    DEVICE( CERN,       CERN_SPSB_PCI,  "STAR/RD24 SCI-PCI (PMC)"),
    DEVICE( IMS,        IMS_8849,   "8849"),
    DEVICE( TEKRAM2,    TEKRAM2_690c,   "DC690c"),
    DEVICE( TUNDRA,     TUNDRA_CA91C042,"CA91C042 Universe"),
    DEVICE( AMCC,       AMCC_MYRINET,   "Myrinet PCI (M2-PCI-32)"),
    DEVICE( AMCC,       AMCC_S5933, "S5933"),
    DEVICE( INTERG,     INTERG_1680,    "IGA-1680"),
    DEVICE( INTERG,         INTERG_1682,    "IGA-1682"),
    DEVICE( REALTEK,    REALTEK_8029,   "8029"),
    DEVICE( REALTEK,    REALTEK_8129,   "8129"),
    DEVICE( TRUEVISION, TRUEVISION_T1000,"TARGA 1000"),
    DEVICE( INIT,       INIT_320P,  "320 P"),
    DEVICE( VIA,        VIA_82C505, "VT 82C505"),
    DEVICE( VIA,        VIA_82C561, "VT 82C561"),
    DEVICE( VIA,        VIA_82C586_1,   "VT 82C586 Apollo VP-1"),
    DEVICE( VIA,        VIA_82C576, "VT 82C576 3V"),
    DEVICE( VIA,        VIA_82C585, "VT 82C585VP Apollo VP-1"),
    DEVICE( VIA,        VIA_82C586_0,   "VT 82C586 Apollo VP-1"),
    DEVICE( VIA,        VIA_82C926, "VT 82C926 Amazon"),
    DEVICE( VIA,        VIA_82C416, "VT 82C416MV"),
    DEVICE( VORTEX,     VORTEX_GDT60x0, "GDT 60x0"),
    DEVICE( VORTEX,     VORTEX_GDT6000B,"GDT 6000b"),
    DEVICE( VORTEX,     VORTEX_GDT6x10, "GDT 6110/6510"),
    DEVICE( VORTEX,     VORTEX_GDT6x20, "GDT 6120/6520"),
    DEVICE( VORTEX,     VORTEX_GDT6530, "GDT 6530"),
    DEVICE( VORTEX,     VORTEX_GDT6550, "GDT 6550"),
    DEVICE( VORTEX,     VORTEX_GDT6x17, "GDT 6117/6517"),
    DEVICE( VORTEX,     VORTEX_GDT6x27, "GDT 6127/6527"),
    DEVICE( VORTEX,     VORTEX_GDT6537, "GDT 6537"),
    DEVICE( VORTEX,     VORTEX_GDT6557, "GDT 6557"),
    DEVICE( VORTEX,     VORTEX_GDT6x15, "GDT 6115/6515"),
    DEVICE( VORTEX,     VORTEX_GDT6x25, "GDT 6125/6525"),
    DEVICE( VORTEX,     VORTEX_GDT6535, "GDT 6535"),
    DEVICE( VORTEX,     VORTEX_GDT6555, "GDT 6555"),
    DEVICE( EF,     EF_ATM_FPGA,        "155P-MF1 (FPGA)"),
    DEVICE( EF,     EF_ATM_ASIC,    "155P-MF1 (ASIC)"),
    DEVICE( FORE,       FORE_PCA200PC, "PCA-200PC"),
    DEVICE( FORE,       FORE_PCA200E,    "PCA-200E"),
    DEVICE( IMAGINGTECH,    IMAGINGTECH_ICPCI, "MVC IC-PCI"),
    DEVICE( PHILIPS,    PHILIPS_SAA7146,"SAA7146"),
    DEVICE( PLX,        PLX_9060,   "PCI9060 i960 bridge"),
    DEVICE( ALLIANCE,   ALLIANCE_PROMOTIO, "Promotion-6410"),
    DEVICE( ALLIANCE,   ALLIANCE_PROVIDEO, "Provideo"),
    DEVICE( VMIC,       VMIC_VME,   "VMIVME-7587"),
    DEVICE( DIGI,       DIGI_RIGHTSWITCH, "RightSwitch SE-6"),
    DEVICE( MUTECH,     MUTECH_MV1000,  "MV-1000"),
    DEVICE( RENDITION,  RENDITION_VERITE,"Verite 1000"),
    DEVICE( TOSHIBA,    TOSHIBA_601,    "Laptop"),
    DEVICE( RICOH,      RICOH_RL5C466,  "RL5C466"),
    DEVICE( ZEITNET,    ZEITNET_1221,   "1221"),
    DEVICE( ZEITNET,    ZEITNET_1225,   "1225"),
    DEVICE( OMEGA,      OMEGA_82C092G,  "82C092G"),
    DEVICE( NP,     NP_PCI_FDDI,    "NP-PCI"),       
    DEVICE( SPECIALIX,  SPECIALIX_XIO,  "XIO/SIO host"),
    DEVICE( SPECIALIX,  SPECIALIX_RIO,  "RIO host"),
    DEVICE( IKON,       IKON_10115, "10115 Greensheet"),
    DEVICE( IKON,       IKON_10117, "10117 Greensheet"),
    DEVICE( ZORAN,      ZORAN_36057,    "ZR36057"),
    DEVICE( ZORAN,      ZORAN_36120,    "ZR36120"),
    DEVICE( COMPEX,     COMPEX_ENET100VG4, "Readylink ENET100-VG4"),
    DEVICE( COMPEX,     COMPEX_RL2000,  "ReadyLink 2000"),
    DEVICE( RP,             RP8OCTA,        "RocketPort 8 Oct"),
    DEVICE( RP,             RP8INTF,        "RocketPort 8 Intf"),
    DEVICE( RP,             RP16INTF,       "RocketPort 16 Intf"),
    DEVICE( RP,             RP32INTF,       "RocketPort 32 Intf"),
    DEVICE( CYCLADES,   CYCLOM_Y_Lo,    "Cyclom-Y below 1Mbyte"),
    DEVICE( CYCLADES,   CYCLOM_Y_Hi,    "Cyclom-Y above 1Mbyte"),
    DEVICE( CYCLADES,   CYCLOM_Z_Lo,    "Cyclom-Z below 1Mbyte"),
    DEVICE( CYCLADES,   CYCLOM_Z_Hi,    "Cyclom-Z above 1Mbyte"),
    DEVICE( 3DFX,       3DFX_VOODOO,    "Voodoo"),
    DEVICE( SIGMADES,   SIGMADES_6425,  "REALmagic64/GX"),
    DEVICE( OPTIBASE,   OPTIBASE_FORGE, "MPEG Forge"),
    DEVICE( OPTIBASE,   OPTIBASE_FUSION,"MPEG Fusion"),
    DEVICE( OPTIBASE,   OPTIBASE_VPLEX, "VideoPlex"),
    DEVICE( OPTIBASE,   OPTIBASE_VPLEXCC,"VideoPlex CC"),
    DEVICE( OPTIBASE,   OPTIBASE_VQUEST,"VideoQuest"),
    DEVICE( SYMPHONY,   SYMPHONY_101,   "82C101"),
    DEVICE( TEKRAM,     TEKRAM_DC290,   "DC-290"),
    DEVICE( 3DLABS,     3DLABS_300SX,   "GLINT 300SX"),
    DEVICE( 3DLABS,     3DLABS_500TX,   "GLINT 500TX"),
    DEVICE( 3DLABS,     3DLABS_DELTA,   "GLINT Delta"),
    DEVICE( 3DLABS,     3DLABS_PERMEDIA,"PERMEDIA"),
    DEVICE( AVANCE,     AVANCE_ALG2064, "ALG2064i"),
    DEVICE( AVANCE,     AVANCE_2302,    "ALG-2302"),
    DEVICE( NETVIN,     NETVIN_NV5000SC,"NV5000"),
    DEVICE( S3,     S3_PLATO_PXS,   "PLATO/PX (system)"),
    DEVICE( S3,     S3_ViRGE,   "ViRGE"),
    DEVICE( S3,     S3_TRIO,    "Trio32/Trio64"),
    DEVICE( S3,     S3_AURORA64VP,  "Aurora64V+"),
    DEVICE( S3,     S3_TRIO64UVP,   "Trio64UV+"),
    DEVICE( S3,     S3_ViRGE_VX,    "ViRGE/VX"),
    DEVICE( S3,     S3_868, "Vision 868"),
    DEVICE( S3,     S3_928,     "Vision 928-P"),
    DEVICE( S3,     S3_864_1,   "Vision 864-P"),
    DEVICE( S3,     S3_864_2,   "Vision 864-P"),
    DEVICE( S3,     S3_964_1,   "Vision 964-P"),
    DEVICE( S3,     S3_964_2,   "Vision 964-P"),
    DEVICE( S3,     S3_968,     "Vision 968"),
    DEVICE( S3,     S3_TRIO64V2,    "Trio64V2/DX or /GX"),
    DEVICE( S3,     S3_PLATO_PXG,   "PLATO/PX (graphics)"),
    DEVICE( S3,     S3_ViRGE_DXGX,  "ViRGE/DX or /GX"),
    DEVICE( S3,     S3_ViRGE_GX2,   "ViRGE/GX2"),
    DEVICE( INTEL,      INTEL_82375,    "82375EB"),
    BRIDGE( INTEL,      INTEL_82424,    "82424ZX Saturn",   0x00),
    DEVICE( INTEL,      INTEL_82378,    "82378IB"),
    DEVICE( INTEL,      INTEL_82430,    "82430ZX Aries"),
    BRIDGE( INTEL,      INTEL_82434,    "82434LX Mercury/Neptune", 0x00),
    DEVICE( INTEL,      INTEL_82092AA_0,"82092AA PCMCIA bridge"),
    DEVICE( INTEL,      INTEL_82092AA_1,"82092AA EIDE"),
    DEVICE( INTEL,      INTEL_7116, "SAA7116"),
    DEVICE( INTEL,      INTEL_82596,    "82596"),
    DEVICE( INTEL,      INTEL_82865,    "82865"),
    DEVICE( INTEL,      INTEL_82557,    "82557"),
    DEVICE( INTEL,      INTEL_82437,    "82437"),
    DEVICE( INTEL,      INTEL_82371_0,  "82371 Triton PIIX"),
    DEVICE( INTEL,      INTEL_82371_1,  "82371 Triton PIIX"),
    DEVICE( INTEL,      INTEL_82371MX,  "430MX - 82371MX MPIIX"),
    DEVICE( INTEL,      INTEL_82437MX,  "430MX - 82437MX MTSC"),
    DEVICE( INTEL,      INTEL_82441,    "82441FX Natoma"),
    DEVICE( INTEL,      INTEL_82439,    "82439HX Triton II"),
    DEVICE( INTEL,      INTEL_82371SB_0,"82371SB Natoma/Triton II PIIX3"),
    DEVICE( INTEL,      INTEL_82371SB_1,"82371SB Natoma/Triton II PIIX3"),
    DEVICE( INTEL,      INTEL_82371SB_2,"82371SB Natoma/Triton II PIIX3"),
    DEVICE( INTEL,      INTEL_82437VX,  "82437VX Triton II"),
    DEVICE( INTEL,      INTEL_82439TX,  "82439TX"),
    DEVICE( INTEL,      INTEL_82371AB_0,"82371AB PIIX4"),
    DEVICE( INTEL,      INTEL_82371AB,  "82371AB 430TX PIIX4"),
    DEVICE( INTEL,      INTEL_82371AB_2,"82371AB PIIX4"),
    DEVICE( INTEL,      INTEL_82371AB_3,"82371AB PIIX4 Power Management"),
    DEVICE( INTEL,      INTEL_P6,   "Orion P6"),
    DEVICE( INTEL,      INTEL_82450GX,  "82450GX Orion P6"),
    DEVICE( KTI,        KTI_ET32P2, "ET32P2"),
    DEVICE( ADAPTEC,    ADAPTEC_7850,   "AIC-7850"),
    DEVICE( ADAPTEC,    ADAPTEC_7855,   "AIC-7855"),
    DEVICE( ADAPTEC,    ADAPTEC_7860,   "AIC-7860"),
    DEVICE( ADAPTEC,    ADAPTEC_7861,   "AIC-7861"),
    DEVICE( ADAPTEC,    ADAPTEC_7870,   "AIC-7870"),
    DEVICE( ADAPTEC,    ADAPTEC_7871,   "AIC-7871"),
    DEVICE( ADAPTEC,    ADAPTEC_7872,   "AIC-7872"),
    DEVICE( ADAPTEC,    ADAPTEC_7873,   "AIC-7873"),
    DEVICE( ADAPTEC,    ADAPTEC_7874,   "AIC-7874"),
    DEVICE( ADAPTEC,    ADAPTEC_7880,   "AIC-7880U"),
    DEVICE( ADAPTEC,    ADAPTEC_7881,   "AIC-7881U"),
    DEVICE( ADAPTEC,    ADAPTEC_7882,   "AIC-7882U"),
    DEVICE( ADAPTEC,    ADAPTEC_7883,   "AIC-7883U"),
    DEVICE( ADAPTEC,    ADAPTEC_7884,   "AIC-7884U"),
    DEVICE( ATRONICS,   ATRONICS_2015,  "IDE-2015PL"),
    DEVICE( ARK,        ARK_STING,  "Stingray"),
    DEVICE( ARK,        ARK_STINGARK,   "Stingray ARK 2000PV"),
    DEVICE( ARK,        ARK_2000MT, "2000MT")
};

/*
  バイナリーサーチで、デバイスを探す
*/
static pci_vendor_info *search_vendor_info(WORD vendor_id, WORD device_id)
{    
    int min, max;
    int median;
    int tmp;
    
    min = 0;
    max = (sizeof(vendor_list) / sizeof(pci_vendor_info)) - 1;
    
    while (min <= max) {       
        median  = min + ((max - min) >> 1);
        tmp = vendor_list[median].vendor_id - vendor_id;
        
        if (tmp == 0) {
            /* vendorは等しいようです */
            tmp = vendor_list[median].device_id - device_id;
        }
        
        if (tmp < 0) {
            /* vendor_idの方が大きい */
            min = median + 1;
        } else if(tmp > 0) {
            /* vendor_idのほうが小さい */
            max = median - 1;
        } else {
            /* hit! */
            return &(vendor_list[median]);
        }
    }
    return NULL;
}

static int insert_new_pcidev(pci_dev *pci)
{
    pci_dev *ptr, *new_ptr;
    int i = 0;
    
    new_ptr = (pci_dev*)_sys_kmalloc(sizeof(pci_dev));
    
    if (new_ptr == NULL) {
        _sys_printf("pci malloc error!\n");
        return i;
    }
    
    _sys_memcpy((void*)new_ptr, (void*)pci, sizeof(pci_dev));
    
    new_ptr->next = NULL;
    ptr = pci_root;
    
    if (ptr != NULL) {
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = new_ptr;
        ++i;
    } else {
        pci_root = new_ptr;
        ++i;
    }
    return i;
}


static int traverse_pci_dev(void)
{    
    pci_dev *p;
    int i;    
    char *intr_pin[] = {
        "INTA#",
        "INTB#",
        "INTC#",
        "INTD#"
    };
    
    for (p = pci_root ; (p!=NULL) ; p = p->next) {
        if (p->vendor != NULL) {
            _sys_printf(" pci%d: vendor:%x device:%x (%s)\n", 
                        p->pci_num, p->vendor->vendor_id, 
                        p->vendor->device_id, p->vendor->name);
        } else {
            _sys_printf(" pci%d: vendor:%x device:%x\n", 
                        p->pci_num, p->vendor_id, p->device_id);
        }
        
        _sys_printf(" Bus:%d Dev:%d Fnc:%d MultiFunction:", 
                    p->dev.bus, p->dev.dev, p->dev.fn);
        
        if (check_multiple(p)) {
            _sys_printf("Yes");
        } else {
            _sys_printf("No");
        }
        
        _sys_putchar('\n');
        
        if (p->intr_num != 0) {
            _sys_printf(" IRQ:%d(%s)\n", p->irq_num, 
                        intr_pin[p->intr_num - 1]);
        }
        
        for (i = 0 ; i < 6 ; i++) {
            if (p->mem_addr[i] != 0 && 
                p->mem_size[i] != 0){
                _sys_printf(" mem: %x..%x\n", p->mem_addr[i], 
                            p->mem_addr[i] + p->mem_size[i]);
            }
        }
        
        for (i = 0 ; i < 6 ; i++) {
            if (p->io_addr[i] != 0) {
                _sys_printf(" i/o: %x..%x\n", p->io_addr[i], 
                            p->io_addr[i] + p->io_size[i]);
            }
        }
        _sys_putchar('\n');
    }
    return 1;
}

pci_dev *find_pci_dev_from_id(DWORD vendor_id, DWORD device_id)
{
    pci_dev *ptr;
    
    for (ptr = pci_root ; !(ptr==NULL) ; ptr = ptr->next) {
        if (ptr->vendor_id == vendor_id && 
            ptr->device_id == device_id){
            return ptr;
        }
    }
    
    return NULL;
    
}

pci_dev *find_pci_dev_from_reg(pci_reg *reg)
{    
    pci_dev     *p;   
    /* たいした数じゃないし全数探査でよか */
    for (p = pci_root ; !(p==NULL) ; p = p->next) {
        if ((p->dev.bus & p->dev.dev & p->dev.fn) ==
            (reg->bus & reg->dev & reg->fn)){
            return p;
        }
    }
    return NULL;
}

static void do_pci_search_all_device(void)
{
    pci_dev device;
    DWORD   tmp;
    int     i = 0;
    DWORD   bus_id, device_num, function_num;
    
    for (bus_id = 0 ; bus_id <= 255 ; bus_id++) {        
        for (device_num = 0 ; device_num <= 31 ; device_num++) {            
            for (function_num = 0 ; function_num <= 7 ; function_num++) {
                _sys_memset32((void*)&device, 0, sizeof(pci_dev));
                
                device.dev.fn = function_num;
                device.dev.bus = bus_id;
                device.dev.dev = device_num;
                
                if ((pci_read_config_reg16(&device.dev, 0x0)) == 0xFFFF) {
                    break;
                } else {
                    pci_vendor_info *vendor;

                    tmp = pci_read_config_reg32(&device.dev, 0x0);
                    
                    device.vendor_id    = (DWORD)tmp;
                    device.device_id    = (DWORD)(tmp >> 16);
                    device.pci_num      = i;
                    
                    device.irq_num = (BYTE)(pci_read_config_reg16(&device.dev, 0x3c) & 0xff);
                    device.intr_num = (BYTE)((pci_read_config_reg16(&device.dev, 0x3c) >> 8) & 0xff);
                    
                    device.dev.bus  = bus_id;
                    device.dev.dev  = device_num;
                    device.dev.fn   = function_num;
                    
                    device.vendor = search_vendor_info(device.vendor_id, device.device_id);
                    
                    get_pci_resouce(&device);
                    
                    insert_new_pcidev(&device);

                    i++;
                }

				disable_pci_resource(&device);
            }
        }
    }
    
    if (i == 0) {
        _sys_printf(" pci device not find\n");
    } else {
        traverse_pci_dev();
    }    
}

void pci_search_all_device(void)
{
    do_pci_search_all_device();
}


/* Lunatic */
DWORD pci_read_config_reg32(pci_reg *reg, BYTE offset)
{
    DWORD value, orig;
    DWORD ret;
    
    value = 0x80000000UL;
    value |= (offset & 0xfc);
    value |= reg->fn << 8;
    value |= reg->dev << 11;
    value |= reg->bus << 16;
    
    orig = inl(CONFIG_ADDRESS_REG);
    outl(CONFIG_ADDRESS_REG, value);
    
    ret = inl(CONFIG_DATA_REG);
    outl(CONFIG_ADDRESS_REG, orig);
    
    return ret;
}

WORD pci_read_config_reg16(pci_reg *reg, BYTE offset)
{
    DWORD value, orig;
    WORD  ret;
    
    value = 0x80000000UL;
    value |= (offset & 0xfc);
    value |= reg->fn << 8;
    value |= reg->dev << 11;
    value |= reg->bus << 16;
    
    orig = inl(CONFIG_ADDRESS_REG);
    outl(CONFIG_ADDRESS_REG, value);
    
    ret = inw(CONFIG_DATA_REG);
    outl(CONFIG_ADDRESS_REG, orig);
    
    return ret;
}

BYTE pci_read_config_reg8(pci_reg *reg, BYTE offset)
{    
    DWORD value, orig;
    BYTE  ret;
    
    value = 0x80000000UL;
    value |= (offset & 0xfc);
    value |= reg->fn << 8;
    value |= reg->dev << 11;
    value |= reg->bus << 16;
    
    orig = inl(CONFIG_ADDRESS_REG);
    outl(CONFIG_ADDRESS_REG, value);
    
    ret = inb(CONFIG_DATA_REG);
    outl(CONFIG_ADDRESS_REG, orig);
    
    return ret;
}

void pci_write_config_reg32(pci_reg *reg, BYTE offset, const DWORD value)
{
    DWORD tmp_reg, orig;
    
    tmp_reg = 0x80000000UL;
    tmp_reg |= (offset & 0xfc);
    tmp_reg |= reg->fn << 8;
    tmp_reg |= reg->dev << 11;
    tmp_reg |= reg->bus << 16;
    
    orig = inl(CONFIG_ADDRESS_REG);
    
    outl(CONFIG_ADDRESS_REG, tmp_reg);
    outl(CONFIG_DATA_REG, value);
    outl(CONFIG_ADDRESS_REG, orig);
}

void pci_write_config_reg16(pci_reg *reg, BYTE offset ,const WORD value)
{
    DWORD  tmp_reg, orig;
    
    tmp_reg = 0x80000000UL;
    tmp_reg |= (offset & 0xfc);
    tmp_reg |= reg->fn << 8;
    tmp_reg |= reg->dev << 11;
    tmp_reg |= reg->bus << 16;
    
    orig = inl(CONFIG_ADDRESS_REG);
    
    outl(CONFIG_ADDRESS_REG, tmp_reg);
    outw(CONFIG_DATA_REG, value);
    outl(CONFIG_ADDRESS_REG, orig);
}

void pci_write_config_reg8(pci_reg *reg, BYTE offset, const BYTE value)
{
    DWORD tmp_reg, orig;

    tmp_reg = 0x80000000UL;
    tmp_reg |= (offset & 0xfc);
    tmp_reg |= reg->fn << 8;
    tmp_reg |= reg->dev << 11;
    tmp_reg |= reg->bus << 16;
    
    orig = inl(CONFIG_ADDRESS_REG);
    
    outl(CONFIG_ADDRESS_REG, tmp_reg);
    outb(CONFIG_DATA_REG, value);
    outl(CONFIG_ADDRESS_REG, orig);
}

static int check_multiple(pci_dev *device)
{
    DWORD value;
    value = pci_read_config_reg32(&device->dev, 0x0c);
    if ((BYTE)(value >> 16) & 0x80) {
        return 1;
    } else {
        return 0;
    }
}

static void print_device_type(pci_dev *device)
{    
    DWORD value;
    value = pci_read_config_reg32(&device->dev, 0xc);    
    switch ((BYTE)(value >> 16) & 0x7F) {
    case 0x0:
        _sys_printf(" (normal device)");
        break;
    case 0x1:
        _sys_printf(" (PCI-PCI bridge)");
        break;
    case 0x2:
        _sys_printf(" (Card Bus bridge)");
        break;
    }
}

static void get_pci_resouce(pci_dev *device)
{
    DWORD offset;
    int   i;
    DWORD base_addr, addr_size;
    int   prefetch;
    
    for (i = 0 ; i < 6 ; i++) {
        device->mem_size[i] = device->io_size[i] = device->mem_addr[i] 
            = device->io_addr[i] = 0x0;
    }
    
    for (offset = 0x10,i = 0 ; offset <= 0x24 ; offset += 0x4,i++) {
        pciDecodeBar(device, offset, &base_addr, &addr_size, &prefetch);
        if (prefetch == -1) {
            device->io_addr[i] = base_addr;
            device->io_size[i] = addr_size;
        } else {
            device->mem_addr[i] = base_addr;
            device->mem_size[i] = addr_size;
        }
    }
    
}

int pci_register_irq(DWORD irq_num, void (*handler)())
{
    disable_IRQ_line(irq_num);
    if (_sys_irq_set_level_trigger(irq_num)) {
        _sys_set_irq_handle(irq_num, handler);
        enable_IRQ_line(irq_num);
        return 1;
    }
    return 0;
}


int pci_unregister_irq(DWORD irq_num)
{
    disable_IRQ_line(irq_num);
    return (_sys_irq_set_edge_trigger(irq_num));
}



void disable_pci_resource(pci_dev *device)
{
    WORD value;
    value = pci_read_config_reg16(&device->dev, 0x04);
    value &= ~0x3;
    pci_write_config_reg16(&device->dev, 0x04, value);
}


void enable_pci_resource(pci_dev *device)
{
    WORD value;
    value = pci_read_config_reg16(&device->dev, 0x04);
    value |= 0x3;
    pci_write_config_reg16(&device->dev, 0x04, value);
}


void enable_pci_interrupt(pci_dev *device)
{
    WORD value;
    value = pci_read_config_reg16(&device->dev, 0x04);
    value |= 0x400;
    pci_write_config_reg16(&device->dev, 0x04, value);
}


void disable_pci_interrupt(pci_dev *device)
{
    WORD value;
    value = pci_read_config_reg16(&device->dev, 0x04);
    value &= ~0x400;
    pci_write_config_reg16(&device->dev, 0x04, value);
}



static void pciDecodeBar(pci_dev *device, BYTE offset, DWORD *base_addr, 
                         DWORD *addr_size, int *prefetch)
{    
    DWORD orig = pci_read_config_reg32(&device->dev, offset);
    DWORD type = orig & 0xf;
    DWORD addr;
    DWORD size;
    DWORD tmp;
    
    disable_pci_resource(device);
    pci_write_config_reg32(&device->dev, offset, 0xffffffff);
    
    *addr_size = *base_addr = 0;
    
    switch(type & 1){
    case 0:
        /* mem */
        tmp = pci_read_config_reg32(&device->dev, offset) & ~0xf;
        //tmp = pci_read_config_reg32(bus_id, device_num, function_num, offset);
            
        addr = orig & ~0xf;
            
        if(addr <= 0){
            break;
        }
            
        switch (type & 6) {
        case 0:
        case 2:
            if (0x10 > tmp) {
                /* これは無効 */
                pci_write_config_reg32(&device->dev, offset, orig);
                return;
            } else if(0x10 <= tmp && 0xff >= tmp) {
                //size = (~tmp & ~0xf) & 0xff;
                size = ~tmp & 0xff;
            } else if(0x100 <= tmp && 0xffff >= tmp) {
                //size = (~tmp & ~0xf) & 0xffff;
                size = ~tmp & 0xffff;
            } else if(0x10000 <= tmp && 0xffffff >= tmp) {
                //size = (~tmp & ~0xf) & 0xffffff;
                size = ~tmp & 0xffffff;
            } else if(0x1000000 <= tmp && 0xffffffff >= tmp) {
                //size = (~tmp & ~0xf) & 0xffffffff;
                size = ~tmp & 0xffffffff;
            }
            break;
        case 4:
            /* 64bitだよ～ん */
            break;
        }
        //_sys_printf(" mem: %x..%x ", addr, addr+size);
            
        *base_addr  = addr;
        *addr_size  = size;
            
        if (type & 8) {
            //_sys_printf("(prefetchable)\n");
            *prefetch = 1;
        } else {
            //_sys_printf("(no prefetch)\n");
            *prefetch = 0;
        }
        break;
        
    case 1:
        /* i/o */
        tmp = pci_read_config_reg32(&device->dev, offset) & ~0x3;
        //tmp = pci_read_config_reg32(bus_id, device_num, function_num, offset);
        addr = orig & ~0x3;
        
        if (addr <= 0) {
            break;
        }
        
        if(0x4 > tmp) {
            /* これは無効 */
            break;
        } else if (0x4 <= tmp && 0xff >= tmp) {
            //size = (~tmp & ~0x3) & 0xff;
            size = ~tmp & 0xff;
        } else if (0x100 <= tmp && 0xffff >= tmp) {
            //size = (~tmp & ~0x3) & 0xffff;
            size = ~tmp & 0xffff;
        } else if(0x10000 <= tmp && 0xffffff >= tmp) {
            //size = (~tmp & ~0x3) & 0xffffff;
            size =  ~tmp & 0xffffff;
        } else if(0x1000000 <= tmp && 0xffffffff >= tmp) {
            //size = (~tmp & ~0x3) & 0xffffffff;
            size = ~tmp & 0xffffffff;
        }
            
        //_sys_printf(" i/o: %x..%x\n", addr, addr+size);
            
        *base_addr  = addr;
        *addr_size  = size;
            
        /* type i/o */
        *prefetch = -1;
            
        break;
        
    }   
    pci_write_config_reg32(&device->dev, offset, orig);
    enable_pci_resource(device);    
}

