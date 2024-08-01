#ifndef __SDHCI_DMA_H__
#define __SDHCI_DMA_H__


#define dma_map_sg(d, s, n, r) __sdhci_dma_map_sg(d, s, n, r)
#define dma_unmap_sg(d, s, n, r) __dma_unmap_sg_attrs(d, s, n, r, 0)

enum dma_data_direction
{
    DMA_BIDIRECTIONAL = 0,
    DMA_TO_DEVICE = 1,
    DMA_FROM_DEVICE = 2,
    DMA_NONE = 3,
};

struct dma_chan
{
    const char *name;
};

#define DMA_BIT_MASK(n) (((n) == 64) ? ~0ULL : ((1ULL<<(n))-1))


int dma_set_mask_and_coherent(struct rt_device *dev, rt_uint64_t mask)
{
    return 0;
}

void *dma_alloc_coherent(struct rt_device *dev, size_t size,
        rt_uint64_t *dma_handle, unsigned gfp)
{
    
    void *v;

    v = rt_malloc_align(size, 2048);
    if (v)
    {
        *dma_handle = virt_to_phys(v);
        v = rt_ioremap((void *)*dma_handle, size);
    }

    return v;

}

void dma_free_coherent(struct rt_device *dev, size_t size,
        void *cpu_addr, unsigned long dma_handle)
{
    rt_free(cpu_addr);
}

#endif