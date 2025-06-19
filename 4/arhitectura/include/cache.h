#include "mytype.h"

#define MAX_PAGES 5
#define SIZE_PAGES 10

typedef struct {
    int offset;
    int age;
    int is_dirty;
    int_15bit values[SIZE_PAGES];
} cacheLine;

extern cacheLine cache[MAX_PAGES];

int sc_cacheLineIndex(int offsetLine);
int sc_cacheLineLoad(int offsetLine);
int sc_cacheLineFflush(int offsetLine);
void sc_cacheLruIncriment();
int sc_memoryControllerGet(int address, int* value);

void sc_cacheInit();