# Copyright 1999-2006 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header:  $

# THIS FILE IS NOT SUPPORTED BY GENTOO, CAN HARM AND BREAK YOUR SYSTEM FOR GOOD!
# THERE IS NO GUARANTEE OR WARRANTY OF ANY KIND USE IT ON YOUR OWN RISK!
#
# e-build by Miklos Bagi Jr. <mbjr@mbjr.hu>
# modified by Munteanu Alexandru Ionut <io_alex_2002@yahoo.fr>

DESCRIPTION="Libmp3splt is a library created from mp3splt v2.1c to split mp3 and ogg files"
HOMEPAGE="http://mp3splt.sourceforge.net/"
SRC_URI="mirror://sourceforge/mp3splt/${P}.tar.gz"

LICENSE="GPL-2"
SLOT="0"
KEYWORDS="~x86"
#we can put the use tags for vorbis and id3tag if we want
IUSE=""

DEPEND="media-libs/libmad
        media-libs/libvorbis
        media-libs/libid3tag"

src_compile() {
	econf || die "configure failed"
	emake || die "compilation failed"
}

src_install() {
	einstall
    dodoc AUTHORS ChangeLog COPYING INSTALL NEWS README TODO LIMITS
}