#include "../external/Unity/src/unity.h"
#include "../src/sax.h"

void setUp(void) {}
void tearDown(void) {}

void test_z_normalize(void)
{
    TimeSeries ts1 = {{1, 3}, 2};
    initializeSaxBreakpoint();
    z_normalize(&ts1);
    TEST_ASSERT_EQUAL_FLOAT(ts1.data[0], -1);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_z_normalize);
    return UNITY_END();
}