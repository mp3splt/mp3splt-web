#!/bin/bash

################# variables to set ############

ARCH=i386;
MP3SPLT_GTK_VERSION=0.4_rc1;
MP3SPLT_GTK_DOC_FILES=(AUTHORS ChangeLog COPYING INSTALL NEWS README TODO)

################# end variables to set ############

#we move in the current script directory
script_dir=$(readlink -f $0)
script_dir=${script_dir%\/*.sh}
PROGRAM_DIR=$script_dir
cd $PROGRAM_DIR

#we put the flags, to find out libmp3splt headers and libraries
export CFLAGS="-I/tmp/dynamic_tmp/libmp3splt/usr/local/include $CFLAGS"
export LDFLAGS="-L/tmp/dynamic_tmp/libmp3splt/usr/local/lib $LDFLAGS"

#create the directories we need
DYNAMIC_DIR=/tmp/dynamic_tmp/mp3splt-gtk
rm -rf $DYNAMIC_DIR/*
mkdir -p $DYNAMIC_DIR
mkdir -p $DYNAMIC_DIR/usr/local/share/doc/mp3splt-gtk

#we compile
./autogen.sh && \
./configure --enable-bmp --enable-shared --disable-static && \
make clean && \
make && \
make DESTDIR=$DYNAMIC_DIR install && \
cp "${MP3SPLT_GTK_DOC_FILES[@]}" $DYNAMIC_DIR/usr/local/share/doc/mp3splt-gtk &&\
tar -c -z -C $DYNAMIC_DIR -f mp3splt-gtk-${MP3SPLT_GTK_VERSION}_dynamic_$ARCH.tar.gz . &&\
mv mp3splt-gtk*dynamic*.tar.gz ../