#include <gtest/gtest.h>
#include <matrix.hpp>

// ------------------------------------------------------------------
TEST(MatrixTest, MatrixTest) {
    matrix<int, -1> m;
    ASSERT_EQ(m.size(), 0);
    m[0][0] = 100;
    ASSERT_EQ(m.size(), 1);
    ASSERT_EQ(m[0][0], 100);
}

// ------------------------------------------------------------------
int main( int argc, char* argv[] ) {
    testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}