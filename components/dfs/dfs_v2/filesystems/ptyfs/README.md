# The Pseudo Terminal Filesystem

The device register on ptyfs is also registered in device frameworks with `rt_device_register()`.

It's possible to mount a new ptyfs instance on another path. Each instance is isolated to each other. And they don't share the id system. But generally speaking, you have to mount the ptyfs on `/dev` root, since all the file nodes in ptyfs are devices.
