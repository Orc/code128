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
