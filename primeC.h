typedef struct {
    char * pBuf;
    int    iSize;
} sieve_t;

sieve_t* createSieve(int);
void destroySieve(sieve_t*);
void printList(sieve_t*); 
void printPrimes(sieve_t*); 
int countPrimes(sieve_t*); 
unsigned int usqrt(int);


