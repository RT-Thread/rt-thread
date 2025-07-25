# Note

## Support Chip List

### MCX

Modify USB_NOCACHE_RAM_SECTION

```
#define USB_NOCACHE_RAM_SECTION __attribute__((section(".NonCacheable")))
```

- MCXN9XX/MCXN236 (chipidea + EHCI)

## IMRT

- IMRT10XX/IMRT11XX (chipidea + EHCI)