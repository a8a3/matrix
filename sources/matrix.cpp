#include <iostream>
#include "matrix_impl.hpp"

// ------------------------------------------------------------------
int main( int, char** ) {
   try {
      matrix<int, 2, 0> m;

      for (int i = 0, j = 9; i < 10 && j >= 0; ++i, --j) {
         m[i][i] = i;
         m[i][j] = j;
      }

      for (int i = 1; i < 9; ++i) {
         for (int j = 1; j < 9; ++j) {
            std::cout << m[i][j] << " ";
         }
         std::cout << std::endl;
      }

      std::cout << m.size() << std::endl;

      for(const auto& i: m) {
         size_t x;
         size_t y;
         int val;
         std::tie(x, y, val) = i;
         std::cout << x << y << val << std::endl;
      }
   }
   catch(const std::out_of_range& e) {
      std::cout << e.what() << std::endl;
   }
   catch(...){
      std::cout << "unknown exception\n";
   }
   return 0;
}