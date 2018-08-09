Implementations detail.

No changes to original FreeRTOS code was made.
Directories was reorganized to move all changed or optional items outside the original, copied code.
That way just copying new version of FreeRTOS should give functional code.

Folders:
- source:  Original Source directory from FreeRTOS. Deleted all port files from portable subdirectory.
           In portable subdirectory only MemMang was left.
- license: Original License directory from FreeRTOS.
- config:  Base (clean) FreeRTOS configuration file.
- portable: Port files created for nrf5x microcontroller.
