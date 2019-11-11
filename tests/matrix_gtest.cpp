#include <gtest/gtest.h>
#include <matrix_impl.hpp>
#include <type_traits>

// // ------------------------------------------------------------------
// TEST(MatrixTest, MatrixTest) {
//     matrix<int, -1> m;
//     ASSERT_EQ(m.size(), 0);
//     m[0][0] = 100;
//     ASSERT_EQ(m.size(), 1);
//     ASSERT_EQ(m[0][0], 100);
// }

// ------------------------------------------------------------------
TEST(MatrixTest, MatrixFunctionalityTest) {
    constexpr auto def = -1;

    matrix<int, 2, def> m;
    // m[0][0] = 100;
    // ASSERT_EQ(m[0][0], 100);
    // ASSERT_EQ(m.size(), 1);
    
    // m[0][0] = def;
    // ASSERT_EQ(m[0][0], def);
    // ASSERT_EQ(m.size(), 0);

    m[0][0] = 200;
    ASSERT_EQ(m[0][0], 100);
    // ASSERT_EQ(m[0][1], 200);
    // ASSERT_EQ(m[0][2], 300);
    
    // auto it = m.begin();
    // ASSERT_EQ(*it, std::make_tuple(0, 0, 100));
    // ++it;
    // ASSERT_EQ(*it, std::make_tuple(0, 1, 200));
    // ++it;
    // ASSERT_EQ(*it, std::make_tuple(0, 2, 300));


 //   ASSERT_EQ(m[100][100], -1);
}


// ------------------------------------------------------------------
int main( int argc, char* argv[] ) {
    testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}