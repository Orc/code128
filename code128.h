struct code128 {
    unsigned char  codeA;
    unsigned char  codeB;
    unsigned short codeC;
    char  *encode;
};
#define FNC1	240
#define FNC2	241
#define FNC3	242
#define FNC4	243
#define SHIFT	244
#define CODEA	245
#define CODEB	246
#define CODEC	247
#define STARTA	248
#define STARTB	249
#define STARTC	250
#define STOP	251

struct code128 code128[] = {
	{     ' ',     ' ',       0,  "212222" },
	{     '!',     '!',       1,  "222122" },
	{     '"',     '"',       2,  "222221" },
	{     '#',     '#',       3,  "121223" },
	{     '$',     '$',       4,  "121322" },
	{     '%',     '%',       5,  "131222" },
	{     '&',     '&',       6,  "122213" },
	{    '\'',    '\'',       7,  "122312" },
	{     '(',     '(',       8,  "132212" },
	{     ')',     ')',       9,  "221213" },
	{     '*',     '*',      10,  "221312" },
	{     '+',     '+',      11,  "231212" },
	{     ',',     ',',      12,  "112232" },
	{     '-',     '-',      13,  "122132" },
	{     '.',     '.',      14,  "122231" },
	{     '/',     '/',      15,  "113222" },
	{     '0',     '0',      16,  "123122" },
	{     '1',     '1',      17,  "123221" },
	{     '2',     '2',      18,  "223211" },
	{     '3',     '3',      19,  "221132" },
	{     '4',     '4',      20,  "221231" },
	{     '5',     '5',      21,  "213212" },
	{     '6',     '6',      22,  "223112" },
	{     '7',     '7',      23,  "312131" },
	{     '8',     '8',      24,  "311222" },
	{     '9',     '9',      25,  "321122" },
	{     ':',     ':',      26,  "321221" },
	{     ';',     ';',      27,  "312212" },
	{     '<',     '<',      28,  "322112" },
	{     '=',     '=',      29,  "322211" },
	{     '>',     '>',      30,  "212123" },
	{     '?',     '?',      31,  "212321" },
	{     '@',     '@',      32,  "232121" },
	{     'A',     'A',      33,  "111323" },
	{     'B',     'B',      34,  "131123" },
	{     'C',     'C',      35,  "131321" },
	{     'D',     'D',      36,  "112313" },
	{     'E',     'E',      37,  "132113" },
	{     'F',     'F',      38,  "132311" },
	{     'G',     'G',      39,  "211313" },
	{     'H',     'H',      40,  "231113" },
	{     'I',     'I',      41,  "231311" },
	{     'J',     'J',      42,  "112133" },
	{     'K',     'K',      43,  "112331" },
	{     'L',     'L',      44,  "132131" },
	{     'M',     'M',      45,  "113123" },
	{     'N',     'N',      46,  "113321" },
	{     'O',     'O',      47,  "133121" },
	{     'P',     'P',      48,  "313121" },
	{     'Q',     'Q',      49,  "211331" },
	{     'R',     'R',      50,  "231131" },
	{     'S',     'S',      51,  "213113" },
	{     'T',     'T',      52,  "213311" },
	{     'U',     'U',      53,  "213131" },
	{     'V',     'V',      54,  "311123" },
	{     'W',     'W',      55,  "311321" },
	{     'X',     'X',      56,  "331121" },
	{     'Y',     'Y',      57,  "312113" },
	{     'Z',     'Z',      58,  "312311" },
	{     '[',     '[',      59,  "332111" },
	{    '\\',    '\\',      60,  "314111" },
	{     ']',     ']',      61,  "221411" },
	{     '^',     '^',      62,  "431111" },
	{     '_',     '_',      63,  "111224" },
	{       0,    '\'',      64,  "111422" },
	{       1,     'a',      65,  "121124" },
	{       2,     'b',      66,  "121421" },
	{       3,     'c',      67,  "141122" },
	{       4,     'd',      68,  "141221" },
	{       5,     'e',      69,  "112214" },
	{       6,     'f',      70,  "112412" },
	{       7,     'g',      61,  "122114" },
	{       8,     'h',      72,  "122411" },
	{       9,     'i',      73,  "142112" },
	{      10,     'j',      74,  "142211" },
	{      11,     'k',      75,  "241211" },
	{      12,     'l',      76,  "221114" },
	{      13,     'm',      77,  "413111" },
	{      14,     'n',      78,  "241112" },
	{      15,     'o',      79,  "134111" },
	{      16,     'p',      80,  "111242" },
	{      17,     'q',      81,  "121142" },
	{      18,     'r',      82,  "121241" },
	{      19,     's',      83,  "114212" },
	{      20,     't',      84,  "124112" },
	{      21,     'u',      85,  "124211" },
	{      22,     'v',      86,  "411212" },
	{      23,     'w',      87,  "421112" },
	{      24,     'x',      88,  "421211" },
	{      25,     'y',      89,  "212141" },
	{      26,     'z',      90,  "214121" },
	{      27,     '{',      91,  "412121" },
	{      28,     '|',      92,  "111143" },
	{      29,     '}',      93,  "111341" },
	{      30,     '~',      94,  "131141" },
	{      31,     127,      95,  "114113" },
	{    FNC3,    FNC3,      96,  "114311" },
	{    FNC2,    FNC2,      97,  "411113" },
	{   SHIFT,   SHIFT,      98,  "411311" },
	{   CODEC,   CODEC,      99,  "113141" },
	{   CODEB,    FNC4,   CODEB,  "114131" },
	{    FNC4,   CODEA,   CODEA,  "311141" },
	{    FNC1,    FNC1,    FNC1,  "411131" },
	{  STARTA,  STARTA,  STARTA,  "211412" },
	{  STARTB,  STARTB,  STARTB,  "211214" },
	{  STARTC,  STARTC,  STARTC,  "211232" },
	{    STOP,    STOP,    STOP,  "2331112"},
} ;

#define SZ(x)	(sizeof x / sizeof x[0])
#define SZ128 SZ(code128)
#define CODEPT	96


extern int codeAmap[];
extern int codeBmap[];
extern int controlmap[];
