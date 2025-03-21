#include "../external/Unity/src/unity.h"
#include "../src/sax.h"

void setUp(void) {}
void tearDown(void) {}

void test_z_normalize(void)
{
    TimeSeries ts1 = {{1, 3}, 2};
    init_breakpoint();
    z_normalize(&ts1);
    TEST_ASSERT_EQUAL_FLOAT(ts1.data[0], -1);
}

void test_promote_cardinality(void)
{
    SaxPair symbol1 = {0, 2};
    SaxPair symbol2 = {6, 8};
    SaxPairPair promoted = promote_cardinality(symbol1, symbol2);
    TEST_ASSERT_EQUAL_UINT8(promoted.first.value, 3);
    TEST_ASSERT_EQUAL_UINT8(promoted.second.value, 6);
}

// void test_sax_distance(void)
// {
//     SaxPair symbol1 = {6, 8};
//     SaxPair symbol2 = {0, 2};
//     double distance = sax_pair_distance(symbol1, symbol2);
//     TEST_ASSERT_FLOAT_WITHIN(0.04, 0.67, distance);
// }

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_z_normalize);
    RUN_TEST(test_promote_cardinality);
    // RUN_TEST(test_sax_distance);
    return UNITY_END();
}