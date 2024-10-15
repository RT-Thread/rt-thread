# Note

## Support Chip List

### BouffaloLab

- BouffaloLab BL616/BL808

### HPMicro

- HPM all series

### AllwinnerTech

- F133

### Nuvoton

- Nuvoton all series

### Artinchip

- d13x, d21x

### NXP

Modify USB_NOCACHE_RAM_SECTION

```
#define USB_NOCACHE_RAM_SECTION __attribute__((section(".NonCacheable")))
```

- IMRT10XX/IMRT11XX
- MCXN9XX/MCXN236

### Intel

- Intel 6 Series Chipset and Intel C200 Series Chipset
