Memory DMA
==========

Memory DMA is middleware which provides DMA-based versions of memcpy and memset
functions.

Architecture and provided functionality
---------------------------------------

Memory DMA uses system DMA driver which varies depending on MCU. User must configure
system DMA driver before using Memory DMA middleware.

DMA-based versions of memcpy and memset functions work asynchronously. Application
can be notifications about completion of copy or set operation via callbacks.
A callback can be registered via dma_memory_register_callback function.