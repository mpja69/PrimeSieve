#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

//#define WORD unsigned char
//#define BITS_PER_WORD (int) (sizeof(WORD))

typedef struct {
    unsigned char * pBuf;
    int    iSize;
} SIEVE;


char getBit(unsigned char * buf, unsigned int index) {
	unsigned int  index8  = index / 8;
	unsigned char shifts  = index % 8; 
	unsigned char bitmask = 1 << shifts;
	unsigned char byte    =  buf[index8];
	byte &= bitmask;		
	return byte != 0;	
}

void clearBit(unsigned char * buf, unsigned int index) {
	unsigned int index8 = index / 8;
	unsigned char shifts  = index % 8; 
	unsigned char bitmask = ~(1 << shifts);
	buf[index8] &= bitmask;
}

void setBit(unsigned char * buf, unsigned int index) {
	unsigned int index8 = index / 8;
	unsigned char shifts  = index % 8; 
	unsigned char bitmask = (1 << shifts);
	buf[index8] |= bitmask;
}
/*
void printByte(unsigned char b) {
	printf("%d: [", b);
	for (int i=7; i>=0; i--) {
		printf("%d", getBit(&b, i));;
	}
	printf("]\n");
}
*/
unsigned int usqrt(int n)
{
    unsigned int x;
    unsigned int xLast;

    xLast = 0;
    x = n / 2;

    while (x != xLast) {
        xLast = x;
        x = (x + n / x) / 2;
    }
    return x;
}


void findPrimes(SIEVE * pS) {
	unsigned char * b = pS->pBuf;
	unsigned int p = 3; 	// börja på första primtalet
	unsigned int i = 0; 	// temp räknanre
	unsigned int j = 0; 	// temp räknanre
	unsigned int r = 0; 	// roten av max

	r = (unsigned int)usqrt(pS->iSize);
	while ( p <= r ) {
		if ( getBit(b, p)  ) {	 		// Om detta är ett printal
			i = p * p;			// Starta på kvadraten av primtalet
			j = 2 * p; 			// Stega fram dubbla primtalet
			while( i < pS->iSize ) {	// Loopa resten av vektorn
				clearBit(b,i);	 	// Markera följande komposit-tal som  FALSE
				i += j; 		// Stega fram dubbla primtalet, hoppa över jämna tal
			}
    		}
		p+=2;					// Hoppa över jämna tal
    	}
}

SIEVE * createSieve(int m){
	SIEVE * pS = NULL;
	int i = 0;

	pS = (SIEVE *) malloc(  sizeof(SIEVE) );
        pS->iSize = m; 
	pS->pBuf = (unsigned char *) calloc( (pS->iSize / 8) + 1, 1 ); // size/8 ger bits (+1 för säkerhet)

	// Initiera listans primtalskandidater:  från 3 och vartannat tal med 1 (true) 
        for (i=3; i<pS->iSize; i+=2) {
            setBit(pS->pBuf,i); 
        }
	return pS;
}

void destroySieve(SIEVE * pS) {
	free (pS->pBuf);
    	free (pS);
}

void printList(SIEVE *pS) {
	printf("Listan:\n");
	for(int i=0; i < pS->iSize; i++){
		if(i%8 == 0) printf(" ");
		if( i%32 == 0) printf("\n");
		printf("%d",getBit(pS->pBuf, i));
	}
	printf("\n");
}
void printPrimes(SIEVE *pS) {
	int i=0;
	int j=1;
	printf("%3d: %3d\n", 1, 2);
	for (i = 3; i < (pS->iSize); i+=2) {
		if ( getBit(pS->pBuf, i) ) {
			j++;
			printf("%3d: %3d\n", j, i);
		}
	}
	printf("Antal: %d\n", j);
}

int countPrimes(SIEVE *pS) {
	int i = 0;
	int j = 1;
	for (i = 3; i < (pS->iSize); i+=2)  j +=  getBit(pS->pBuf, i);
	return j;
}

int main(int argc, char**  argv) {
    	int i;
    	int max = 1000 * 1000;
    	int iPasses = 0;
    	int iPrimes = 0;
    	clock_t start = 0;
    	clock_t stop = 0;;
    	double dTime = 0;

    	SIEVE *pSieve = NULL;

    	// Ta in maxvärdet från kommandoraden
    	if (argc == 2) {
		max = atoi(argv[1]);
    	}
	if (max < 3) {
		printf("argc=%d, max=%d...Exiting!\n", argc, max);
		return 0;
	}

	// Diagnostics
	start = clock();
	pSieve = createSieve(max);
	findPrimes(pSieve);
	iPrimes = countPrimes(pSieve);
	stop = clock();
	
	if( argc == 2 ) {
		printPrimes(pSieve);
		printList(pSieve);
		printf("Hittade %d primtal under %d på %lu ms.\n", iPrimes, max, stop-start);
	}
	destroySieve(pSieve);
	if( argc == 1 ) {
		printf("Beräknar hur många pass som kan köras på 5 sekunder...\n");
		start = clock();
		while ( (argc==1) && (dTime<5.0)){
			pSieve = createSieve(max);
	        	findPrimes(pSieve);
        		stop = clock();
			destroySieve(pSieve);
        		dTime = (double) (stop - start) / CLOCKS_PER_SEC;
        		iPasses++;
    		}
    		printf("Antal pass: %d  Medeltid %f sekunder.\n", iPasses, dTime / iPasses);
	}
    return stop-start;
}


