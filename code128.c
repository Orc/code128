#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "config.h"
#include "code128.h"
#include "gethopt.h"

int
controlpoint(int c)
{
    return controlmap[c];
}

int
codeA(int c)
{
    int i;

    if ( c & 0x80 )
	return -1;

    return codeAmap[c];
}

int
codeB(int c)
{
    int i;

    if ( c & 0x80 )
	return -1;

    return codeBmap[c];
}


int
digitpair(char *p)
{
    return ((p[0]-'0')*10) + (p[1]-'0');
}


char *pgm;

void
die(char *msg, ...)
{
    va_list ptr;

    fprintf(stderr, "%s: ", pgm);
    va_start(ptr, msg);
    vfprintf(stderr, msg, ptr);
    va_end(ptr);
    fputc('\n', stderr);
    exit(1);
}


int
codefor(int c)
{
    int i;

    if ( c & 0x80 )
	return -1;

    if ( codeAmap[c] != -1 )
	return CODEA;
    else if ( codeBmap[c] != -1 )
	return CODEB;

    return -1;
}


int
code128string(char *p, char **res)
{
    int code = 0;
    char *out = malloc(1+(strlen(p) * 2));
    int i, sz;
    unsigned int ch;

    if ( out == 0 ) {
	die("cannot allocate buffer for code 128 string");
	return -1;
    }

    for ( sz=0; *p; ++p ) {
	if ( isdigit(*p) ) {
	    /* can we haz CODEC compression? */
	    int j, usecodeC;

	    for (j=1; isdigit(p[j]); ++j)
		;

	    /* cheaper to use codeC is there is a string of
	     *  6+ digits, OR
	     *  4+ digits at start or end of pattern, OR
	     *  either 2 or 4+ digits as the entire pattern
	     */
	    if ( code && p[j] )
		usecodeC = ( j >= 6 );
	    else if ( code || p[j] )
		usecodeC = ( j >= 4 );
	    else
		usecodeC = ( j == 2 || j >= 4 );

	    if ( usecodeC ) {
		/* not worth our while unless there are at least six digits
		 * to compress (4 if at start/end of text)
		 */
		out[sz++] = code ? controlpoint(CODEC)
				 : controlpoint(STARTC);
		code = CODEC;
		while ( j > 1 ) {
		    out[sz++] = digitpair(p);
		    j-=2;
		    p += 2;
		}
		--p;
		continue;
	    }
	}
	
	ch = *p;

	if  ( (i = codeB(ch)) >= 0 ) {
	    if ( code != CODEB ) {
		if ( codefor(p[1]) == code ) {
		    /* shift for single character code flips */
		    out[sz++] = controlpoint(SHIFT);
		}
		else {
		    out[sz++] = code ? controlpoint(CODEB)
				     : controlpoint(STARTB);
		    code = CODEB;
		}
	    }
	    out[sz++] = i;
	}
	else if ( (i = codeA(ch)) >= 0 ) {
	    if ( code != CODEA ) {
		if ( codefor(p[1]) == code ) {
		    /* shift for single character code flips */
		    out[sz++] = controlpoint(SHIFT);
		}
		else {
		    out[sz++] = code ? controlpoint(CODEA)
				     : controlpoint(STARTA);
		    code = CODEA;
		}
	    }
	    out[sz++] = i;
	}
	else  /* whoops? canthappen? */
	    die("illegal (non-ascii) character $%02x (after %d chars)", ch, sz);
    }
    *res = out;
    return sz;
}


static int black, white;
static int barwidth;
static int height;
static int xp = 0;

void
add(gdImagePtr barcode, char *s)
{
    gdPoint pt[4];
    unsigned int dx;
    unsigned int color = 1;
    unsigned int sz;
    unsigned int e;
    char *p;

    for (p = s; *p; ++p) {
	e = *p - '0';
	dx = barwidth * e;
	sz += e;
	if (color) {
	    pt[0].x = xp;    pt[0].y = 0;
	    pt[1].x = xp+dx-1; pt[1].y = 0;
	    pt[2].x = xp+dx-1; pt[2].y = height;
	    pt[3].x = xp;    pt[3].y = height;
	    gdImageFilledPolygon(barcode, pt, 4, color ? black : white);
	}
	color = !color;
	xp += dx;
    }
}

struct h_opt opts[] = {
#if GD_SUPPORTS_JPEG
    { 0, "jpeg",   'j', 0, "write the barcode in jpeg format" },
    { 0, "jpg",     0,  0, "(synonym for -jpeg)" },
#endif
#if GD_SUPPORTS_GIF
    { 1, "GIF",    'g', 0, "write the barcode in GIF format" },
    { 1, "gif",     0,  0, "(synonym for -GIF)" },
#endif
#if GD_SUPPORTS_PNG
    { 2, "png",    'p', 0, "write the barcode in PNG format" },
#endif
    { 3, "help",   '?', 0, "help message" },
    { 4, "version",'V', 0, "print the version#, then exit" },
} ;

#define NROPT (sizeof opts/sizeof opts[0])





int
main(int argc, char **argv)
{
    enum { GIF, JPEG, PNG } output;
    char *imagetype[] = { "GIF", "JPEG", "PNG" };
    int i;
    int sum, size;
    int width;
    char *encoded;
    gdImagePtr barcode;
    gdPoint pt[4];
    FILE *f;
    struct h_opt *opt;
    struct h_context args;

    extern char version[];

#if GD_SUPPORTS_PNG
    output = PNG;
#elif GD_SUPPORTS_JPEG
    output = JPEG;
#else
    output = GIF;
#endif

    if (( pgm = strrchr(argv[0], '/') ))
	++pgm;
    else
	pgm = argv[0];

    hoptset(&args, argc, argv);
    hopterr(&args, 1);
    
    while ( opt = gethopt(&args, opts, NROPT) ) {
	if ( opt == HOPTERR )
	    exit(1);

	switch ( opt->option ) {
	case 0: output = JPEG;
		break;
	case 1: output = GIF;
		break;
	case 2: output = PNG;
		break;
	case 3: hoptusage(pgm, opts, NROPT, "scale string");
		exit(0);
	case 4: printf("%s (%s)\n", version, imagetype[output]);
		exit(0);
	}
    }

    if (argc < 3) {
	hoptusage(pgm, opts, NROPT, "scale string");
	exit(1);
    }
    if ( (barwidth = atoi(argv[1])) < 1)
	die("bad scale <%s>", argv[1]);

    size = code128string(argv[2], &encoded);

    /* convert to pixel width, add 20 for quiet zones, 11 for checksum, 13 for EOM */
    width = (size * 11) + 44;

    height = barwidth*35;
    width *= barwidth;
    xp = 10 * barwidth;

    barcode = gdImageCreate( width, height);
    white = gdImageColorAllocate(barcode,255,255,255);
    gdImageColorTransparent(barcode, white);
    black = gdImageColorAllocate(barcode, 0, 0, 0);

    for (sum=i=0; i < size; ++i) {
	add(barcode, code128[encoded[i]].encode);
	sum += (encoded[i]) * (i ? i : 1);
    }
    sum %= 103;
    add(barcode,code128[sum].encode);
    add(barcode,"2331112");

    switch (output) {
#if GD_SUPPORTS_PNG
    case PNG:   gdImagePng(barcode, stdout);
		break;
#elif GD_SUPPORTS_JPEG
    case JPEG:  gdImageJpeg(barcode, stdout, 70);
		break;
#elif GD_SUPPORTS_GIF
    case GIF:	gdImageGif(barcode, stdout);
		break;
#endif
    default:    die("unsupported output format %d", output);
		exit(1);
    }
    exit(0);
}
