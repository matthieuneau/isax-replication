#include <gsl/gsl_cdf.h>
#include "sax.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void init_breakpoint()
{
    for (int i = 0; i < MAX_CARDINALITY - 1; i++)
    {
        for (int j = 0; j < MAX_CARDINALITY; j++)
        {
            saxBreakpoint[i][j] = gsl_cdf_gaussian_Pinv((double)(i + 1) / (double)(j + 1), 1.0);
        }
    }
}

SaxPairPair promote_cardinality(SaxPair symbol1, SaxPair symbol2)
{
    if (symbol1.cardinality == symbol2.cardinality)
    {
        return (SaxPairPair){symbol1, symbol2};
    }
    else
    {
        // ensure that symbol2 has largest cardinality
        if (symbol1.cardinality > symbol2.cardinality)
        {
            SaxPair temp = symbol1;
            symbol1 = symbol2;
            symbol2 = temp;
        }
        if (symbol2.value >> (int)log((double)(symbol2.cardinality - symbol1.cardinality)) == symbol1.value)
        {
            return (SaxPairPair){symbol2, symbol2};
        }
        else
        {
            if (symbol2.value >> (int)log((double)(symbol2.cardinality - symbol1.cardinality)) > symbol1.value)
            {
                while (symbol1.cardinality < symbol2.cardinality)
                {
                    symbol1.value = (symbol1.value << 1) + 1;
                    symbol1.cardinality *= 2;
                }
            }
            else
            {
                while (symbol1.cardinality < symbol2.cardinality)
                {
                    symbol1.value = symbol1.value << 1;
                    symbol1.cardinality *= 2;
                }
            }
        }
        return (SaxPairPair){symbol1, symbol2};
    }
}

double sax_pair_distance(SaxPair symbol1, SaxPair symbol2)
{
    // start by casting the pair with lowest cardinality to the highest cardinality
    SaxPairPair promoted = promote_cardinality(symbol1, symbol2);
    uint8_t cardinality = promoted.first.cardinality;

    symbol1 = promoted.first;
    symbol2 = promoted.second;

    if (abs(symbol1.value - symbol2.value) <= 1)
        return 0;

    else
    {
        if (symbol1.value < symbol2.value)
        {
            return saxBreakpoint[symbol1.value][cardinality - 1] - saxBreakpoint[symbol2.value - 1][cardinality - 1];
        }
        else
        {
            return saxBreakpoint[symbol2.value][cardinality - 1] - saxBreakpoint[symbol1.value - 1][cardinality - 1];
        }
    }
}

void z_normalize(TimeSeries *ts)
{
    double mean = 0;
    double std = 0;

    for (int i = 0; i < ts->length; i++)
    {
        mean += ts->data[i];
    }
    mean /= ts->length;

    for (int i = 0; i < ts->length; i++)
    {
        std += (ts->data[i] - mean) * (ts->data[i] - mean);
    }
    std /= ts->length;
    std = sqrt(std);

    for (int i = 0; i < ts->length; i++)
    {
        ts->data[i] = (ts->data[i] - mean) / std;
    }
}

// TODO: fix behavior for when n / w is not an integer. last
TimeSeries compute_paa(TimeSeries *ts, short word_length)
{
    // TODO : Add a constructor to be able to initialize only with length
    TimeSeries ts_PAA = {.length = ts->length / word_length};
    for (int i = 0; i < ts->length / word_length; i++)
    {
        float span_sum = 0.0;
        for (int j = 0; j < word_length; j++)
        {
            span_sum += ts->data[word_length * i + j];
        }
        ts_PAA.data[i] = span_sum / word_length;
    }
    return ts_PAA;
}

SaxRepresentation paa_to_symbols(TimeSeries *ts, short cardinality)
{
    SaxRepresentation sax = {.length = ts->length};
    for (int i = 0; i < ts->length; i++)
    {
        // need to find to which breakpoint the data point is mapped to
        double data_point = ts->data[i];
        int symbol = 0;
        while (saxBreakpoint[symbol][cardinality - 1] <= data_point && symbol < cardinality - 1)
        {
            symbol++;
        }
        sax.data[i].value = symbol;
        sax.data[i].cardinality = cardinality;
    }
    return sax;
}

// float minDist(SaxRepresentation *sax1, SaxRepresentation *sax2)
// {
//     float min_dist = 0;
//     for (int i = 0; i < sax1->length; i++)
//     {
//         // min_dist += sax_pair_distance()
//     }
// }

// int main()
// {
//     TimeSeries ts1 = {{-4, 0.5, -0.66, 0.4, 0.3, 0.0, 8}, 7};
//     init_breakpoint();
//     // z_normalize(&ts1);
//     // TimeSeries ts1_PAA = compute_paa(&ts1, 2);
//     SaxRepresentation ts1_symbols = paa_to_symbols(&ts1, 8);
//     printf("%u\n", ts1_symbols.data[0].value);
//     printf("%u\n", ts1_symbols.data[1].value);
//     printf("%u\n", ts1_symbols.data[2].value);
//     printf("%u\n", ts1_symbols.data[3].value);
//     return 0;
// }
