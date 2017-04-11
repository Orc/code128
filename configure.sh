#! /bin/sh

# local options:  ac_help is the help message that describes them
# and LOCAL_AC_OPTIONS is the script that interprets them.  LOCAL_AC_OPTIONS
# is a script that's processed with eval, so you need to be very careful to
# make certain that what you quote is what you want to quote.

# load in the configuration file
#
TARGET=code128

. ./configure.inc

AC_INIT $TARGET

case "$AC_LDFLAGS" in
*-lm*) ;;
*) AC_LDFLAGS="$AC_LDFLAGS -lm" ;;
esac

if AC_CHECK_HEADERS gd.h; then
    AC_TEXT "#include <gd.h>"
elif AC_CHECK_HEADERS gd/gd.h; then
    AC_TEXT "#include <gd/gd.h>"
else
    exit 1
fi

if AC_LIBRARY gdImageGif -lgd; then
    AC_DEFINE GD_SUPPORTS_GIF 1
else
    AC_FAIL "The copy of libgd here does not support the GIF format."
fi

AC_OUTPUT Makefile
