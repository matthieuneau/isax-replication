#define MAX_LENGTH 2048
#include <stdlib.h>
#define MAX_CARDINALITY 256
#define WORD_LENGTH 4

double saxBreakpoint[MAX_CARDINALITY - 1][MAX_CARDINALITY];

typedef struct
{
    double data[MAX_LENGTH];
    int length;

} TimeSeries;

typedef struct
{
    uint8_t value;
    uint8_t cardinality;
} SaxPair;

typedef struct
{
    SaxPair data[MAX_LENGTH];
    int length;
} SaxRepresentation;

typedef struct
{
    SaxPair first;
    SaxPair second;
} SaxPairPair;
