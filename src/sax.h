#define MAX_LENGTH 2048
#include <stdlib.h>
#define MAX_CARDINALITY 256
#define WORD_LENGTH 4

double saxBreakpoint[MAX_CARDINALITY - 1][MAX_CARDINALITY];

typedef struct TimeSeries
{
    double data[MAX_LENGTH];
    int length;

} TimeSeries;

typedef struct SaxPair
{
    uint8_t value;
    uint8_t cardinality;
} SaxPair;

typedef struct SaxRepresentation
{
    SaxPair data[MAX_LENGTH];
    int length;
} SaxRepresentation;

typedef struct SaxPairPair
{
    SaxPair first;
    SaxPair second;
} SaxPairPair;

void init_breakpoint();

SaxPairPair promote_cardinality(SaxPair symbol1, SaxPair symbol2);

double sax_pair_distance(SaxPair symbol1, SaxPair symbol2);

void z_normalize(TimeSeries *ts);

TimeSeries compute_paa(TimeSeries *ts, short word_length);

SaxRepresentation paa_to_symbols(TimeSeries *ts, short cardinality);
