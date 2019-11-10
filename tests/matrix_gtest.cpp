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

#define PRINT_RANGE(_x_) for(const auto& i: (_x_)) {\
                             std::cout << i << " "; \
                         }                          \
                         std::cout << std::endl;    \

template<typename T>
struct ST {
    ST() = default;
    template<typename TT = T, std::enable_if_t<!std::is_const<TT>::value, int> = 0>
    void f() {
        std::cout << "f1" << std::endl;
    }
    template<typename TT = T, std::enable_if_t<std::is_const<TT>::value, int> = 0>
    void f() {
        std::cout << "f2" << std::endl;
    }

};

// ------------------------------------------------------------------
TEST(MatrixTest, MatrixTest) {
    matrix<int, -1> m;
 // m[10][20] = 100;
    ASSERT_EQ(m[10][21],  -1);

    ST<const std::string> s;
    s.f();


}


// ------------------------------------------------------------------
int main( int argc, char* argv[] ) {
    testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}