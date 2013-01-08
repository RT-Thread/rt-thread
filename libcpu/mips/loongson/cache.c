#include "../common/mipsregs.h"
#include "cache.h"

#define K0BASE			0x80000000
#define PRID_3210I 		0x4200

typedef struct cacheinfo_t {
	unsigned int	icache_size;
	unsigned int	dcache_size;
	unsigned int	icacheline_size;
	unsigned int	dcacheline_size;
} cacheinfo_t ;

typedef struct cacheop_t {
	void (*Clear_TagLo) (void);
	void (*Invalidate_Icache) (unsigned int);
	void (*Invalidate_Dcache_Fill) (unsigned int);
	void (*Invalidate_Dcache_ClearTag) (unsigned int);
	void (*Init_Cache)(void);
} cacheop_t ;

static cacheop_t cacheop, *pcacheop;
static cacheinfo_t cacheinfo, *pcacheinfo;

int identify_cpu (void)
{
    unsigned int cpu_id;
    void invalidate_cache (void);

    pcacheop = &cacheop;
    pcacheinfo = &cacheinfo;

	rt_kprintf("CPU configure: 0x%08x\n", read_c0_config());
    cpu_id = read_c0_prid();
    switch (cpu_id)
	{
	case PRID_3210I: 
	    rt_kprintf ("CPU:SoC3210\n");
	    pcacheop->Clear_TagLo = Clear_TagLo;
	    pcacheop->Invalidate_Icache = Invalidate_Icache_Gc3210I;
	    pcacheop->Invalidate_Dcache_Fill = Invalidate_Dcache_Fill_Gc3210I;
	    pcacheop->Invalidate_Dcache_ClearTag = Invalidate_Dcache_ClearTag_Gc3210I;
	    break;
	default:
	    rt_kprintf ("Unknown CPU type, system halted!\n");
	    while (1) {}
	    break;
    }

    return 0;
}

void probe_cache(void)
{
    unsigned int config = read_c0_config ();
    unsigned int icache_size, ic_lsize;
    unsigned int dcache_size, dc_lsize;

    icache_size = 1 << (12 + ((config >> 9) & 7)); 
    dcache_size = 1 << (12 + ((config >> 6) & 7));
    ic_lsize = 16 << ((config >> 5) & 1);
    dc_lsize = 16 << ((config >> 4) & 1);

    rt_kprintf("DCache %2dkb, linesize %d bytes.\n",
	    dcache_size >> 10, dc_lsize);
    rt_kprintf("ICache %2dkb, linesize %d bytes.\n",
	    icache_size >> 10, ic_lsize);

    pcacheinfo->icache_size = icache_size;
    pcacheinfo->dcache_size = dcache_size;
    pcacheinfo->icacheline_size = ic_lsize;
    pcacheinfo->dcacheline_size = dc_lsize;

    return ;
}

void invalidate_writeback_dcache_all(void)
{
	unsigned int start = K0BASE;
	unsigned int end = (start + pcacheinfo->dcache_size);

	start = K0BASE;
	while(start < end) {
		Writeback_Invalidate_Dcache(start);  //hit writeback invalidate 
		start += pcacheinfo->dcacheline_size;
	}
}

void invalidate_writeback_dcache(unsigned long addr, int size)
{
	unsigned long start, end;
			
	start = (addr +pcacheinfo->dcacheline_size -1) & (- pcacheinfo->dcacheline_size);
	end = (end + size + pcacheinfo->dcacheline_size -1) & ( -pcacheinfo->dcacheline_size);
	
	while(start <end){
		Writeback_Invalidate_Dcache(start);
		start += pcacheinfo->dcacheline_size;
	}		
}


void invalidate_icache_all(void)
{
	unsigned int start = K0BASE;
	unsigned int end = (start + pcacheinfo->icache_size);

	while(start < end) {
		pcacheop->Invalidate_Icache(start); 
		start += pcacheinfo->icacheline_size;
	}
}

void invalidate_dcache_all()
{ 
	unsigned int start = K0BASE;
	unsigned int end  = (start + pcacheinfo->dcache_size);
	while(start <end){
		Invalidate_Dcache_Fill_Gc3210I(start);
		start += pcacheinfo->icacheline_size;
	}
}

//with cache disabled
void init_dcache(void)
{
	unsigned int start = K0BASE;
	unsigned int end = (start + pcacheinfo->dcache_size);

	while(start < end){
		pcacheop->Invalidate_Dcache_ClearTag(start);
		start += pcacheinfo->dcacheline_size;
	}

}

void rt_hw_cache_init(void)
{
    unsigned int start, end;
	
	/* 1. identify cpu and probe cache */
	identify_cpu();
	probe_cache();

	start = K0BASE;
	end = (start + pcacheinfo->icache_size);

    /*
     *	2. clear CP0 taglo/taghi register;
     */
    pcacheop->Clear_TagLo();

	/*
     *	3. invalidate instruction cache;
     */
    while(start < end) {
		pcacheop->Invalidate_Icache(start); //index invalidate icache 
		start += pcacheinfo->icacheline_size;
    }

    /*
     *	4. invalidate data cache;
     */
    start = K0BASE;
    end = (start + pcacheinfo->dcache_size);
    while(start < end) {
		pcacheop->Invalidate_Dcache_ClearTag(start); 
		start += pcacheinfo->dcacheline_size;
    }

    start = K0BASE;
    while(start < end) {
		pcacheop->Invalidate_Dcache_Fill(start);  //index invalidate dcache
		start += pcacheinfo->dcacheline_size;
    }

    start = K0BASE;
    while(start < end) {
		pcacheop->Invalidate_Dcache_ClearTag(start); 
		start += pcacheinfo->dcacheline_size;
    }

	/* enable cache */
	enable_cpu_cache();
	rt_kprintf("enable cpu cache done\n");

	return ;
}
