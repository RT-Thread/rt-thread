# Summary

This directory contains legacy applications and tests examples.
These applications were moved from open-amp repository.


# Initialization

The first step is to initialize the workspace folder (``my-workspace``) where
the examples and all Zephyr modules will be cloned. You can do
that by running:

```shell
# initialize my-workspace for the example-application (main branch)
west init -m https://github.com/OpenAMP/openamp-system-reference --mf examples/legacy_apps/west.yml --mr main my-workspace
# update modules
cd my-workspace
west update
```

# Build

Following steps to build legacy apps on host machine.

```
export PROJECT_ROOT=$PWD
```

## Build libmetal
```shell
  $ cd $PROJECT_ROOT/libmetal
  $ cmake . -Bbuild -DCMAKE_INSTALL_PREFIX=$PROJECT_ROOT/target
  $ make -C build VERBOSE=1 install
```

## Build open_amp
```shell
  $ cd $PROJECT_ROOT/open-amp
  $ cmake . -Bbuild -DCMAKE_INCLUDE_PATH=$PROJECT_ROOT/libmetal/build/lib/include/   -DCMAKE_LIBRARY_PATH=$PROJECT_ROOT/libmetal/build/lib/ -DCMAKE_INSTALL_PREFIX=$PROJECT_ROOT/target
  $ make -C build VERBOSE=1 install
```
## Build legacy Apps
```shell
  $ cd $PROJECT_ROOT/openamp-system-reference/examples/legacy_apps
  $ cmake -Bbuild \
-DCMAKE_INCLUDE_PATH="$PROJECT_ROOT/libmetal/build/lib/include/;$PROJECT_ROOT/open-amp/build/lib/include/" \
-DCMAKE_LIBRARY_PATH="$PROJECT_ROOT/libmetal/build/lib/;$PROJECT_ROOT/open-amp/build/lib/" \
-DCMAKE_INSTALL_PREFIX=$PROJECT_ROOT/target
  $ make -C build VERBOSE=1 install
```

## Run application on a Linux PC
It is possible to run application on a Linux PC to communicate between two Linux processes.

```shell
  $ cd $PROJECT_ROOT/target
  $ echo "################### run ping test #####################"
  $ LD_LIBRARY_PATH=./lib  ./bin/rpmsg-echo-static &
  $ sleep 1
  $ LD_LIBRARY_PATH=./lib  ./bin//msg-test-rpmsg-ping-static 1

  $ echo "################### run ping test #####################"
  $ LD_LIBRARY_PATH=./lib  ./bin/rpmsg-nocopy-echo-static &
  $ sleep 1
  $ LD_LIBRARY_PATH=./lib  ./bin//rpmsg-nocopy-ping-static  1
```
