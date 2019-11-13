#include <gtest/gtest.h>
#include <matrix_impl.hpp>
#include <memory>

// ------------------------------------------------------------------
TEST(matrix_test, matrix_base_functionality_test) {
    constexpr auto def{1};
    constexpr auto dim = 2;
    matrix<int, dim, def> m;
    m[0][0] = 100;
    ASSERT_EQ(m[0][0], 100);
    ASSERT_EQ(m.size(), 1);

    m[0][0] = def;
    ASSERT_EQ(m[0][0], def);
    ASSERT_EQ(m.size(), 0);

    m[0][0] = 100;
    ASSERT_TRUE(m[0][0] == 100);
    m[0][1] = 200;
    ASSERT_TRUE(m[0][1] == 200);
    m[0][2] = 300;
    ASSERT_TRUE(m[0][2] == 300);
    
    auto it = m.begin();
    ASSERT_EQ(*it, std::make_tuple(0, 0, 100));
    ++it;
    ASSERT_EQ(*it, std::make_tuple(0, 1, 200));
    ++it;
    ASSERT_EQ(*it, std::make_tuple(0, 2, 300));
}

// ------------------------------------------------------------------
TEST(matrix_test, matrix_of_char_test) {
    constexpr auto def = 'e';
    constexpr auto dim = 4;
    matrix<char, dim, def> m;

    m[0][0][0][0] = 'a';
    ASSERT_TRUE(m[0][0][0][0] == 'a');
    ASSERT_TRUE(m[0][0][0][1] == def);
    ASSERT_EQ(m.size(), 1);
    m[0][0][0][0] = def;
    ASSERT_EQ(m.size(), 0);
}

// ------------------------------------------------------------------
TEST(matrix_test, matrix_constraints_test) {
    constexpr auto def = -1;
    constexpr auto dim = 2;

    matrix<int, dim, def> m;
    ASSERT_THROW(m[0][0][0] = 100, std::out_of_range);
    ASSERT_THROW(m[0]       = 200, std::out_of_range);
}

// ------------------------------------------------------------------
int main( int argc, char* argv[] ) {
    testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}