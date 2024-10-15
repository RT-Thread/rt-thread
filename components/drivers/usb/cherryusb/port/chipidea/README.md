# Note

## Support Chip List

### NXP

Modify USB_NOCACHE_RAM_SECTION

```
#define USB_NOCACHE_RAM_SECTION __attribute__((section(".NonCacheable")))
```

- IMRT10XX/IMRT11XX
- MCXN9XX/MCXN236
