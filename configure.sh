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

AC_PROG_CC
unset _MK_LIBRARIAN

# make sure that the math libraries are included
case "$AC_LDFLAGS $LIBS" in
*-lm*) ;;
*) LIBS="$LIBS -lm" ;;
esac

if [ "IS_BROKEN_CC" ]; then
    case "$AC_CC $AC_CFLAGS" in
    *-pedantic*) ;;
    *)  # hack around deficiencies in gcc and clang
	#
	AC_DEFINE 'while(x)' 'while( (x) != 0 )'
	AC_DEFINE 'if(x)' 'if( (x) != 0 )'

	if [ "$IS_CLANG" -o "$IS_GCC" ]; then
	    AC_CC="$AC_CC -Wno-return-type -Wno-implicit-int"
	fi ;;
    esac
fi


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
for x in -lz -lpng -ljpeg -ltiff -lxpm -lwebp -limagequant -lfontconfig -lfreetype -lraqm; do
    $AC_CC $AC_CFLAGS $AC_LDFLAGS -o ngc$$ ngc$$.c $x && LIBS="$LIBS $x"
done
rm -f ngc$$.c ngc$$

AC_LIBRARY gdImageCreate -lgd || exit 1


unset oformat
if AC_QUIET AC_CHECK_FUNCS gdImagePng; then
    AC_DEFINE GD_SUPPORTS_PNG 1
    oformat="png"
fi
if AC_QUIET AC_CHECK_FUNCS gdImageJpeg; then
    AC_DEFINE GD_SUPPORTS_JPEG 1
    oformat="${oformat}${oformat:+, }jpeg"
fi
if AC_QUIET AC_CHECK_FUNCS gdImageGif; then
    AC_DEFINE GD_SUPPORTS_GIF 1
    oformat="${oformat}${oformat:+, }gif"
fi

test "$oformat" || AC_FAIL "The copy of libgd here does not support GIF, JPG, or PNG format."

AC_OUTPUT Makefile

LOG
LOG "$TARGET supports $oformat output"
LOG
