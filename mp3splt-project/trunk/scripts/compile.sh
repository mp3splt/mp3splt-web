#!/bin/bash

################# variables to set ############

LIBMP3SPLT_DIR=libmp3splt
MP3SPLT_DIR=newmp3splt
MP3SPLT_GTK_DIR=mp3splt-gtk

LIBMP3SPLT_REAL_VERSION="0.7.0.946"
MP3SPLT_REAL_VERSION="2.4.0.946"
MP3SPLT_GTK_REAL_VERSION="0.7.0.946"

BUILD_SOURCE_PACKAGES=1

RUN_UNIT_TESTS=1
RUN_FUNCTIONAL_TESTS=1
BUILD_BINARY_PACKAGES=1

BUILD_UBUNTU_PACKAGES=$BUILD_BINARY_PACKAGES
BUILD_DEBIAN_PACKAGES=$BUILD_BINARY_PACKAGES
BUILD_WINDOWS_PACKAGES=$BUILD_BINARY_PACKAGES

CHROOT_FLAGS=-d

unset SHELL

################## end variables to set ############

#print functions
function print_red()
{
    echo -e "\033[1;31m${@}\033[0m"
}
function print_yellow()
{
    echo -e "\033[1;33m${@}\033[0m"
}
function print_cyan()
{
    echo -e "\033[36m${@}\033[0m"
}
function print_green()
{
    echo -e "\033[1;32m${@}\033[0m"
}

################## confirmation question ############
#the confirmation question
function confirmation_question()
{
    echo
    print_red "This script is used by the developers to auto-create packages for releases."
    print_red "You should modify this script in order to use it on your computer."
    print_red "This script must be run on a x86_64 system (not i386)."
    print_red "Please remember that you are using the script at your own risk !"
    echo

    option1="I know what I'm doing and I use it at my own risk"
    select=("$option1" "Quit")
    select continue in "${select[@]}";do
        if [[ $continue = "$option1" ]]; then
          break
        else
          exit 0
        fi
    done
    
    #don't run the script as root
    if [[ `id -u` == 0 ]]; then
        print_red "The script must not be run as root"
        exit 1
    fi    
}
################## end confirmation question ############

################## update versions ############
function update_versions()
{
  echo
  print_yellow "Updating versions..."
  echo

  #we update the real versions
  #libmp3splt
  sed -i "s/LIBMP3SPLT_VERSION=.*/LIBMP3SPLT_VERSION=$LIBMP3SPLT_REAL_VERSION/" ./${LIBMP3SPLT_DIR}/include_variables.sh
  #mp3splt + its libmp3splt library
  sed -i "s/MP3SPLT_VERSION=.*/MP3SPLT_VERSION=$MP3SPLT_REAL_VERSION/" ./${MP3SPLT_DIR}/include_variables.sh
  sed -i "s/LIBMP3SPLT_VERSION=.*/LIBMP3SPLT_VERSION=$LIBMP3SPLT_REAL_VERSION/" ./${MP3SPLT_DIR}/include_variables.sh
  #mp3splt-gtk + its libmp3splt library
  sed -i "s/MP3SPLT_GTK_VERSION=.*/MP3SPLT_GTK_VERSION=$MP3SPLT_GTK_REAL_VERSION/" ./${MP3SPLT_GTK_DIR}/include_variables.sh
  sed -i "s/LIBMP3SPLT_VERSION=.*/LIBMP3SPLT_VERSION=$LIBMP3SPLT_REAL_VERSION/" ./${MP3SPLT_GTK_DIR}/include_variables.sh

  #we update the versions
  ./${LIBMP3SPLT_DIR}/update_version.sh || exit 1
  ./${MP3SPLT_DIR}/update_version.sh || exit 1
  ./${MP3SPLT_GTK_DIR}/update_version.sh || exit 1

  cd $PROJECT_DIR
}
################## end update versions ############

################## remove pot files ############
function remove_pot_files()
{
  echo
  print_yellow "Removing pot files..."
  echo

  #we update the versions
  rm -f ./${LIBMP3SPLT_DIR}/po/libmp3splt.pot
  rm -f ./${MP3SPLT_DIR}/po/mp3splt.pot
  rm -f ./${MP3SPLT_GTK_DIR}/po/mp3splt-gtk.pot

  cd $PROJECT_DIR
}
################## end remove pot files ############

############# source packages ################
function source_packages()
{
  echo
  print_yellow "Creating source distribution..."

  make -s source_packages || exit 1
  make -C ${LIBMP3SPLT_DIR} || exit 1
  make -C ${MP3SPLT_DIR} || exit 1
  make -C ${MP3SPLT_GTK_DIR} || exit 1
}
############# end source packages ################

############# debian packages ################
#puts .sarge or .etch version
#$1=.sarge or $1=.etch
function put_debian_version()
{
    sed -i "1,4s/libmp3splt (\(.*\)) .*;/libmp3splt (\1.$1) $1;/" ${LIBMP3SPLT_DIR}/debian/changelog
    sed -i "1,4s/mp3splt (\(.*\)) .*;/mp3splt (\1.$1) $1;/" ${MP3SPLT_DIR}/debian/changelog
    sed -i "1,4s/mp3splt-gtk (\(.*\)) .*;/mp3splt-gtk (\1.$1) $1;/" ${MP3SPLT_GTK_DIR}/debian/changelog
}

#cleans .sarge or .etch
#$1=.sarge or $1=.etch
function clean_debian_version()
{
    sed -i "1,4s/libmp3splt (\(.*\)\.$1)/libmp3splt (\1)/" ${LIBMP3SPLT_DIR}/debian/changelog
    sed -i "1,4s/mp3splt (\(.*\)\.$1)/mp3splt (\1)/" ${MP3SPLT_DIR}/debian/changelog
    sed -i "1,4s/mp3splt-gtk (\(.*\)\.$1)/mp3splt-gtk (\1)/" ${MP3SPLT_GTK_DIR}/debian/changelog
}

#make the chroot debian flavors
#example : make_debian_flavor "ubuntu" "breezy" "i386"
#example : make_debian_flavor "debian" "sarge" "amd64"
function make_debian_flavor()
{
    echo
    print_yellow "Creating $3 $1 $2 packages..."
    echo
    
    #if we don't have the distribution files
    if [[ ! -f "mp3splt-gtk-${MP3SPLT_GTK_REAL_VERSION}.${2}_${3}.deb" ||
          ! -f "mp3splt-${MP3SPLT_REAL_VERSION}.${2}_${3}.deb" ||
          ! -f "libmp3splt-${LIBMP3SPLT_REAL_VERSION}.${2}_${3}.deb" ]];then
        
        put_debian_version "$2"
        dchroot $CHROOT_FLAGS -c $2_$3 "export LC_ALL=\"C\" && make -s debian_packages " || \
        {
          clean_debian_version "$2"
          exit 1
        }
        clean_debian_version "$2"
        cd $PROJECT_DIR
    fi
}

function debian_packages()
{
    DEBIAN_FLAVORS="squeeze wheezy unstable"

    echo
    print_yellow "Creating debian packages..."

    for deb_version in $DEBIAN_FLAVORS;do
      make_debian_flavor "debian" $deb_version "i386"
      make_debian_flavor "debian" $deb_version "amd64"
    done

    cd $PROJECT_DIR
}
############# end debian packages ################

############# ubuntu packages ##########################
function ubuntu_packages()
{
    UBUNTU_FLAVORS="maverick natty oneiric"

    echo
    print_yellow "Creating ubuntu packages..."
    
    for deb_version in $UBUNTU_FLAVORS;do
      make_debian_flavor "ubuntu" $deb_version "i386"
      make_debian_flavor "ubuntu" $deb_version "amd64"
    done

    cd $PROJECT_DIR
}
############# end ubuntu packages ##########################


############# gentoo ebuilds ################
function gentoo_packages()
{
  echo
  print_yellow "Creating gentoo ebuilds..."
  echo

  dchroot $CHROOT_FLAGS -c gentoo "make -s gentoo_ebuilds" || exit 1
  cd $PROJECT_DIR
}
############# end gentoo ebuilds ################

############# windows installers ################
function windows_cross_installers()
{
  echo
  print_yellow "Creating windows installers and zips ..."

  #if we don't have the distribution files
  DIST_FILE1="./mp3splt_${MP3SPLT_VERSION}_i386.exe"
  DIST_FILE2="./mp3splt-gtk_${MP3SPLT_GTK_VERSION}_i386.exe"
  if [[ ! -f $DIST_FILE1 || ! -f $DIST_FILE2 ]];then
    make -s windows_cross_installers || exit 1
  else
    echo
    print_cyan "We already have the $DIST_FILE1 distribution file"
    print_cyan "and the $DIST_FILE2 distribution file !"
  fi

  #suppose architecture is i386
  #if [[ -f mp3splt_${MP3SPLT_VERSION}_x86_64.exe ]];then
  #  mv mp3splt_${MP3SPLT_VERSION}_x86_64.exe $DIST_FILE1
  #fi
  #if [[ -f mp3splt-gtk_${MP3SPLT_GTK_VERSION}_x86_64.exe ]];then
  #  mv mp3splt-gtk_${MP3SPLT_GTK_VERSION}_x86_64.exe $DIST_FILE2
  #fi

  cd $PROJECT_DIR
}
############# end windows installers ################

############# RPM packages creation ################
function rpm_packages()
{
    echo
    print_yellow "Creating RPMs..."
    
    make -s rpm_packages || exit 1
    cd $PROJECT_DIR
}
############# end RPM packages creation ################

############# archlinux packages #########
function archlinux_packages()
{
    echo
    print_yellow "Creating archlinux packages..."
    echo
    
    dchroot $CHROOT_FLAGS -c arch "make -s arch_packages" || exit 1
    cd $PROJECT_DIR
}
############# end archlinux packages #########

############# slackware packages #########
function slackware_packages()
{
    echo
    print_yellow "Creating slackware packages..."
    echo
    
    dchroot $CHROOT_FLAGS -c slackware "make -s slackware_fakeroot_packages" || exit 1
    cd $PROJECT_DIR
}
############# end slackware packages #####

############# openbsd packages #####
function openbsd_packages()
{
  echo
  print_yellow "Creating openbsd packages..."

  #if we don't have the distribution file
  DIST_FILE1="libmp3splt_obsd_i386-${LIBMP3SPLT_VERSION}.tgz"
  DIST_FILE2="mp3splt_obsd_i386-${MP3SPLT_VERSION}.tgz"
  DIST_FILE3="mp3splt-gtk_obsd_i386-${MP3SPLT_GTK_VERSION}.tgz"
  #if the 3 files do not exist
  if ! [[ -f $DIST_FILE1 || -f $DIST_FILE2 || -f $DIST_FILE3 ]];then
    cd /mnt/personal/systems/bsd-based/openbsd && ./openbsd || exit 1
    cd $PROJECT_DIR
  else
    echo
    print_cyan "We already have the OpenBSD packages !"
  fi
}
############# end openbsd packages #####

############# netbsd packages #####
function netbsd_packages()
{
  echo
  print_yellow "Creating netbsd packages..."

  #if we don't have the distribution file
  DIST_FILE1="libmp3splt_nbsd_i386-${LIBMP3SPLT_VERSION}.tgz"
  DIST_FILE2="mp3splt_nbsd_i386-${MP3SPLT_VERSION}.tgz"
  DIST_FILE3="mp3splt-gtk_nbsd_i386-${MP3SPLT_GTK_VERSION}.tgz"
  if [[ ! -f $DIST_FILE1 || ! -f $DIST_FILE2 || ! -f $DIST_FILE3 ]];then
    cd /mnt/personal/systems/bsd-based/netbsd && ./netbsd || exit 1
    cd $PROJECT_DIR
  else
    echo
    print_cyan "We already have the NetBSD packages !"
  fi
}
############# end netbsd packages #####

############# freebsd packages #####
function freebsd_packages
{
  echo
  print_yellow "Creating freebsd packages..."

  #we change 2.2_rc1 to 2.2.r1
  TEMP_MP3SPLT_VERSION=${MP3SPLT_VERSION/_/.}
  NEW_MP3SPLT_VERSION=${TEMP_MP3SPLT_VERSION/rc/r}
  #we change 0.4_rc1 to 0.4.r1
  TEMP_LIBMP3SPLT_VERSION=${LIBMP3SPLT_VERSION/_/.}
  NEW_LIBMP3SPLT_VERSION=${TEMP_LIBMP3SPLT_VERSION/rc/r}
  #we change 0.4_rc1 to 0.4.r1
  TEMP_MP3SPLT_GTK_VERSION=${MP3SPLT_GTK_VERSION/_/.}
  NEW_MP3SPLT_GTK_VERSION=${TEMP_MP3SPLT_GTK_VERSION/rc/r}

  #if we don't have the distribution file
  DIST_FILE1="./libmp3splt_fbsd_i386-${NEW_LIBMP3SPLT_VERSION}.tbz"
  DIST_FILE2="./mp3splt_fbsd_i386-${NEW_MP3SPLT_VERSION}.tbz"
  DIST_FILE3="./mp3splt-gtk_fbsd_i386-${NEW_MP3SPLT_GTK_VERSION}.tbz"
  if [[ ! -f $DIST_FILE1 || ! -f $DIST_FILE2 || ! -f $DIST_FILE3 ]];then
    cd /mnt/personal/systems/bsd-based/freebsd && ./freebsd || exit 1
    cd $PROJECT_DIR
  else
    echo
    print_cyan "We already have the FreeBSD packages !"
  fi
}
############# end freebsd packages #####

############# nexenta gnu/opensolaris packages #####
function nexenta_packages()
{
  echo
  print_yellow "Creating nexenta gnu/opensolaris packages..."
  echo

  #if we don't have the distribution file
  DIST_FILE1="./libmp3splt_${LIBMP3SPLT_VERSION}_solaris-i386.deb"
  DIST_FILE2="./mp3splt_${MP3SPLT_VERSION}_solaris-i386.deb"
  DIST_FILE3="./mp3splt-gtk_${MP3SPLT_GTK_VERSION}_solaris-i386.deb"
  if [[ ! -f $DIST_FILE1 || ! -f $DIST_FILE2 || ! -f $DIST_FILE3 ]];then
    cd /mnt/personal/systems/opensolaris/ && ./nexenta || exit 1
    cd $PROJECT_DIR
  else
    echo
    print_cyan "We already have the Nexenta packages !"
  fi
}
############# end nexenta gnu/opensolaris packages #####

function run_functional_tests
{
  echo
  print_yellow "Running functional tests..."
  echo

  cd ../tests && ./tests.sh || exit 1

  cd $PROJECT_DIR
}

function run_unit_tests
{
  echo
  print_yellow "Running unit tests..."
  echo

  ${LIBMP3SPLT_DIR}/test/run-tests.sh || exit 1
}

###########
##  MAIN ##
###########

DATE_START=`date`

if [[ $1 != "quiet_root" ]];then
  confirmation_question
fi

script_dir=$(readlink -f $0)
script_dir=${script_dir%\/*.sh}
PROJECT_DIR=$script_dir/..
cd $PROJECT_DIR

. ./${LIBMP3SPLT_DIR}/include_variables.sh "quiet_noflags"
. ./${MP3SPLT_DIR}/include_variables.sh "quiet_noflags"
. ./${MP3SPLT_GTK_DIR}/include_variables.sh "quiet_noflags"

###################################
#update the versions
update_versions
remove_pot_files

###################################
#build source packages

if [[ $BUILD_SOURCE_PACKAGES -eq 1 ]];then
  source_packages
fi

###################################
#tests

if [[ $RUN_UNIT_TESTS -eq 1 ]];then
  run_unit_tests
fi

if [[ $RUN_FUNCTIONAL_TESTS -eq 1 ]];then
  run_functional_tests
fi

###################################
#build packages

if [[ $BUILD_DEBIAN_PACKAGES -eq 1 ]];then
  debian_packages
fi
if [[ $BUILD_UBUNTU_PACKAGES -eq 1 ]];then
  ubuntu_packages
fi
if [[ $BUILD_WINDOWS_PACKAGES -eq 1 ]];then
  windows_cross_installers
fi

##gentoo_packages
##rpm_packages
##archlinux_packages
##slackware_packages
##amd64 gnu/linux packages :
##i386 bsd-like packages :
##openbsd_packages
##netbsd_packages
##freebsd_packages
##i386 gnu/opensolaris packages :
##nexenta_packages #slow

###################################
#finish packaging ...

#date info
echo
print_green "The packaging is finished :)"

DATE_END=`date`

echo
echo "Start_date : "$DATE_START
echo "End_date : "$DATE_END
echo

################################
######### end main program #####
################################

