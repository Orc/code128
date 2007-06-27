#! /bin/sh

# local options:  ac_help is the help message that describes them
# and LOCAL_AC_OPTIONS is the script that interprets them.  LOCAL_AC_OPTIONS
# is a script that's processed with eval, so you need to be very careful to
# make certain that what you quote is what you want to quote.

# load in the configuration file
#
TARGET=code128

test -r configure.inc || test -d SCCS && get configure.inc
. ./configure.inc


find_gd() {
    gd_found=1
    if AC_QUIET AC_CHECK_HEADERS gd.h $1; then
	AC_CFLAGS="$AC_CFLAGS -I$1"
	AC_LDFLAGS="$AC_LDFLAGS -L$1"
	AC_INCLUDE '<gd.h>'
	LOG "gd.h found in $1"
    elif AC_QUIET AC_CHECK_HEADERS gd/gd.h $1; then
	AC_CFLAGS="$AC_CFLAGS -I$1"
	AC_LDFLAGS="$AC_LDFLAGS -L$1"
	AC_INCLUDE '<gd/gd.h>'
	LOG "gd.h found in $1/gd"
    elif AC_QUIET AC_CHECK_HEADERS gd.h $1/include; then
	AC_CFLAGS="$AC_CFLAGS -I$1/include"
	AC_LDFLAGS="$AC_LDFLAGS -L$1/lib"
	AC_INCLUDE '<gd.h>'
	LOG "gd.h found in $1/include"
    elif AC_QUIET AC_CHECK_HEADERS gd/gd.h $1/include; then
	AC_CFLAGS="$AC_CFLAGS -I$1/include"
	AC_LDFLAGS="$AC_LDFLAGS -L$1/lib"
	AC_INCLUDE '<gd/gd.h>'
	LOG "gd.h found in $1/include/gd"
    fi
}


AC_INIT $TARGET

test "x$WITH_GD"  != "x" && find_gd $WITH_GD

if [ "$OS_FREEBSD" -a -z "$gd_found" ]; then
    find_gd /usr/local
fi

if [ "$gd_found" ]; then
    AC_LIBRARY gdImageCreate -lgd || unset gd_found
fi

if [ -z "$gd_found" ]; then
    LOG "Cannot find libgd;  you need to have a copy of Tom Boutell's"
    LOG "GD library before $TARGET will work.  You can get gd from"
    AC_FAIL "http://www.boutell.com/gd"
fi

if AC_LIBRARY jpeg_destroy -ljpeg; then
    AC_LIBS="$AC_LIBS -ljpeg"
    LOG "Using JPG format"
elif AC_CHECK_FUNCS gdImageGif; then
    AC_DEFINE GD_SUPPORTS_GIF 1
else
    LOG "There is no libjpeg on this system and the copy of"
    AC_FAIL "libgd here does not support the GIF format."
fi

AC_OUTPUT Makefile

