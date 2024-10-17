# Note

## Support Chip List

### NXP

Modify USB_NOCACHE_RAM_SECTION

```
#define USB_NOCACHE_RAM_SECTION __attribute__((section(".NonCacheable")))
```

- MCXC444/MCXA153 (device only)
- MCXN947

### MM32

- MM32F3/MM32F5
