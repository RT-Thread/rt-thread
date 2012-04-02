#!/bin/sh

git ls-tree --name-only --full-name -r $1 | xargs tar -jcvf uffs-$1.tar.bz2