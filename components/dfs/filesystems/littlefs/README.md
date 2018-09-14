## The little filesystem

A little fail-safe filesystem designed for embedded systems.

```
   | | |     .---._____
  .-----.   |          |
--|o    |---| littlefs |
--|     |---|          |
  '-----'   '----------'
   | | |
```

**Bounded RAM/ROM** - The littlefs is designed to work with a limited amount
of memory. Recursion is avoided and dynamic memory is limited to configurable
buffers that can be provided statically.

**Power-loss resilient** - The littlefs is designed for systems that may have
random power failures. The littlefs has strong copy-on-write guarantees and
storage on disk is always kept in a valid state.

**Wear leveling** - Since the most common form of embedded storage is erodible
flash memories, littlefs provides a form of dynamic wear leveling for systems
that can not fit a full flash translation layer.

## Example

Here's a simple example that updates a file named `boot_count` every time
main runs. The program can be interrupted at any time without losing track
of how many times it has been booted and without corrupting the filesystem:

``` c
#include "lfs.h"

// variables used by the filesystem
lfs_t lfs;
lfs_file_t file;

// configuration of the filesystem is provided by this struct
const struct lfs_config cfg = {
    // block device operations
    .read  = user_provided_block_device_read,
    .prog  = user_provided_block_device_prog,
    .erase = user_provided_block_device_erase,
    .sync  = user_provided_block_device_sync,

    // block device configuration
    .read_size = 16,
    .prog_size = 16,
    .block_size = 4096,
    .block_count = 128,
    .lookahead = 128,
};

// entry point
int main(void) {
    // mount the filesystem
    int err = lfs_mount(&lfs, &cfg);

    // reformat if we can't mount the filesystem
    // this should only happen on the first boot
    if (err) {
        lfs_format(&lfs, &cfg);
        lfs_mount(&lfs, &cfg);
    }

    // read current count
    uint32_t boot_count = 0;
    lfs_file_open(&lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
    lfs_file_read(&lfs, &file, &boot_count, sizeof(boot_count));

    // update boot count
    boot_count += 1;
    lfs_file_rewind(&lfs, &file);
    lfs_file_write(&lfs, &file, &boot_count, sizeof(boot_count));

    // remember the storage is not updated until the file is closed successfully
    lfs_file_close(&lfs, &file);

    // release any resources we were using
    lfs_unmount(&lfs);

    // print the boot count
    printf("boot_count: %d\n", boot_count);
}
```

## Usage

Detailed documentation (or at least as much detail as is currently available)
can be found in the comments in [lfs.h](lfs.h).

As you may have noticed, littlefs takes in a configuration structure that
defines how the filesystem operates. The configuration struct provides the
filesystem with the block device operations and dimensions, tweakable
parameters that tradeoff memory usage for performance, and optional
static buffers if the user wants to avoid dynamic memory.

The state of the littlefs is stored in the `lfs_t` type which is left up
to the user to allocate, allowing multiple filesystems to be in use
simultaneously. With the `lfs_t` and configuration struct, a user can
format a block device or mount the filesystem.

Once mounted, the littlefs provides a full set of POSIX-like file and
directory functions, with the deviation that the allocation of filesystem
structures must be provided by the user.

All POSIX operations, such as remove and rename, are atomic, even in event
of power-loss. Additionally, no file updates are actually committed to the
filesystem until sync or close is called on the file.

## Other notes

All littlefs have the potential to return a negative error code. The errors
can be either one of those found in the `enum lfs_error` in [lfs.h](lfs.h),
or an error returned by the user's block device operations.

In the configuration struct, the `prog` and `erase` function provided by the
user may return a `LFS_ERR_CORRUPT` error if the implementation already can
detect corrupt blocks. However, the wear leveling does not depend on the return
code of these functions, instead all data is read back and checked for
integrity.

If your storage caches writes, make sure that the provided `sync` function
flushes all the data to memory and ensures that the next read fetches the data
from memory, otherwise data integrity can not be guaranteed. If the `write`
function does not perform caching, and therefore each `read` or `write` call
hits the memory, the `sync` function can simply return 0.

## Reference material

[DESIGN.md](DESIGN.md) - DESIGN.md contains a fully detailed dive into how
littlefs actually works. I would encourage you to read it since the
solutions and tradeoffs at work here are quite interesting.

[SPEC.md](SPEC.md) - SPEC.md contains the on-disk specification of littlefs
with all the nitty-gritty details. Can be useful for developing tooling.

## Testing

The littlefs comes with a test suite designed to run on a PC using the
[emulated block device](emubd/lfs_emubd.h) found in the emubd directory.
The tests assume a Linux environment and can be started with make:

``` bash
make test
```

## License

The littlefs is provided under the [BSD-3-Clause](https://spdx.org/licenses/BSD-3-Clause.html)
license. See [LICENSE.md](LICENSE.md) for more information. Contributions to
this project are accepted under the same license.

Individual files contain the following tag instead of the full license text.

    SPDX-License-Identifier:    BSD-3-Clause

This enables machine processing of license information based on the SPDX
License Identifiers that are here available: http://spdx.org/licenses/

## Related projects

[Mbed OS](https://github.com/ARMmbed/mbed-os/tree/master/features/filesystem/littlefs) -
The easiest way to get started with littlefs is to jump into [Mbed](https://os.mbed.com/),
which already has block device drivers for most forms of embedded storage. The
littlefs is available in Mbed OS as the [LittleFileSystem](https://os.mbed.com/docs/latest/reference/littlefilesystem.html)
class.

[littlefs-fuse](https://github.com/geky/littlefs-fuse) - A [FUSE](https://github.com/libfuse/libfuse)
wrapper for littlefs. The project allows you to mount littlefs directly on a
Linux machine. Can be useful for debugging littlefs if you have an SD card
handy.

[littlefs-js](https://github.com/geky/littlefs-js) - A javascript wrapper for
littlefs. I'm not sure why you would want this, but it is handy for demos.
You can see it in action [here](http://littlefs.geky.net/demo.html).
