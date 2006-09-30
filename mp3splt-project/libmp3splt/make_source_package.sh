#!/bin/bash

#we move in the current script directory
script_dir=$(readlink -f $0)
script_dir=${script_dir%\/*.sh}
PROGRAM_DIR=$script_dir
cd $PROGRAM_DIR

#we compile
./autogen.sh && \
./configure --prefix=/usr && \
make dist

mv libmp3splt*.tar.gz ../