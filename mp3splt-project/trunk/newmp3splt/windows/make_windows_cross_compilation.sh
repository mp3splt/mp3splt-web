#!/bin/bash

################# variables to set ############


#Debian GNU/Linux settings
export CC="i686-mingw32-gcc"
HOST="i686-mingw32"

################# end variables to set ############

#we move in the current script directory
script_dir=$(readlink -f $0) || exit 1
script_dir=${script_dir%\/*.sh}
cd $script_dir/../..

. ./newmp3splt/include_variables.sh

put_package "cross_windows"

#we run autoconf and automake..
cd newmp3splt && ./autogen.sh && cd .. || exit 1

#untar and copy the required libraries
cd ../libs
cp lib/libmad.a lib/libvorbis.a lib/libogg.a lib/libid3tag.a lib/libz.a \
    lib/libvorbisfile.a ../trunk/newmp3splt/ || exit 1
cp lib/libmad.a lib/libvorbis.a lib/libogg.a lib/libid3tag.a lib/libz.a \
    lib/libvorbisfile.a ../trunk/newmp3splt/src || exit 1
cd ..

#cross compile flags
export CFLAGS=" -mms-bitfields -enable-stdcall-fixup -I`pwd`/libs/include -D_WIN32 -D__MINGW32__ $CFLAGS"
export LDFLAGS="-L`pwd`/libs/lib $LDFLAGS"
export PKG_CONFIG_PATH="`pwd`/libs/lib/pkgconfig"
export PATH="`pwd`/libs/bin:$PATH"

#we compile mp3splt
cd trunk/newmp3splt &&\
cp ../../libs/lib/libmp3splt.a . &&\
cp ../../libs/lib/libmp3splt.a ./src &&\
./configure --prefix=`pwd`/../../libs --host=$HOST &&\
make clean && make && make install &&\
${HOST}-strip ./src/mp3splt.exe || exit 1

