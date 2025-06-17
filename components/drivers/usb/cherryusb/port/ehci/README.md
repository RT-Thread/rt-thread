# Note

## Support Chip List

### BouffaloLab

- BouffaloLab BL616/BL808 (bouffalolab + EHCI)

### HPMicro

- HPM all series (hpmicro + EHCI)

### AllwinnerTech

- F133/T113

### Nuvoton

- Nuvoton all series

### Artinchip

- d13x, d21x

### NXP

Modify USB_NOCACHE_RAM_SECTION

```
#define USB_NOCACHE_RAM_SECTION __attribute__((section(".NonCacheable")))
```

- IMRT10XX/IMRT11XX (chipidea + EHCI)
- MCXN9XX/MCXN236 (chipidea + EHCI)

### Intel

- Intel 6 Series Chipset and Intel C200 Series Chipset
