#include <stdio.h>
#include <string.h>
#include "code128.h"

void
tabprint(char *label, int *tab, int sztab)
{
    int i;
    
    printf("int %s[] = {\n", label);
    for (i=0; i < sztab; i++ ) {
	if (i % 16 == 0 )
	    putchar('\t');
	printf("%2d,", tab[i]);
	if ( i % 16 == 15)
	    putchar('\n');
	else
	    putchar(' ');
    }
    printf("};\n\n");
}

int
main()
{
    int i;
    int tab[256];


    /*
    code lookup (traditional)

    for ( i=0; i < CODEPT; i++ )
	if ( code128[i].code? == c )
	    return i;

    array lookup:   map[c] = i;
	 for i=0; i < CODEPT; i++)
	     map[c] = i; -> map[code128[i].code?] = i;
    */

    memset(tab, -1, sizeof tab);
    for (i=0; i< CODEPT; i++)
	tab[code128[i].codeA] = i;
    tabprint("codeAmap", tab, SZ(tab));

    memset(tab, -1, sizeof tab);
    for (i=0; i < CODEPT; i++)
	tab[code128[i].codeB] = i;
    tabprint("codeBmap", tab, SZ(tab));
    return 0;
}
