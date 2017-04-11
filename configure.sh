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
unset _MK_LIBRARIAN

# make sure that the math libraries are included
case "$AC_LDFLAGS" in
*-lm*) ;;
*) LIBS="$LIBS -lm" ;;
esac

AC_PROG_CC

if AC_CHECK_HEADERS gd.h; then
    AC_TEXT "#include <gd.h>"
elif AC_CHECK_HEADERS gd/gd.h; then
    AC_TEXT "#include <gd/gd.h>"
else
    exit 1
fi

# gd can have a bucketload of dependencies on other libraries, and if it's a
# shared library ALL OF THEM need to be linked in.
echo "main() { }" > ngc$$.c
for x in -lz -lpng -ljpeg -ltiff -lta; do
    $AC_CC $AC_CFLAGS -o ngc$$ ngc$$.c $x && LIBS="$LIBS $x"
done
rm -f ngc$$.c ngc$$

AC_LIBRARY gdImageCreate -lgd || exit 1


if AC_CHECK_FUNCS gdImagePng; then
    AC_DEFINE GD_SUPPORTS_PNG 1
elif AC_CHECK_FUNCS gdImageJpeg; then
    AC_DEFINE GD_SUPPORTS_GIF 1
elif AC_CHECK_FUNCS gdImageGif; then
    AC_DEFINE GD_SUPPORTS_GIF 1
else
    AC_FAIL "The copy of libgd here does not support GIF, JPG, or PNG format."
fi

AC_OUTPUT Makefile
