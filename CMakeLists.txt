cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(matrix VERSION 0.0.1)
endif()

find_package(Threads REQUIRED)
find_package(GTest   REQUIRED)

add_executable(matrix       sources/matrix.cpp)
add_executable(matrix_gtest tests/matrix_gtest.cpp)

set_target_properties(matrix PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(matrix_gtest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/sources
)

target_link_libraries(matrix_gtest
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

if (MSVC)
    target_compile_options(matrix PRIVATE
        /W4 -O3
    )
    target_compile_options(matrix_gtest PRIVATE
        /W4 -O3
    )
else ()
    target_compile_options(matrix PRIVATE
        -Wall -Wextra -pedantic -Werror -O3
    )
    target_compile_options(matrix_gtest PRIVATE
        -Wall -Wextra -pedantic -Werror -O3
    )
endif()

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT matrix@mail.ru)

include(CPack)

enable_testing()

add_test(matrix_gtest matrix_gtest)

add_custom_command(
    TARGET matrix_gtest
    POST_BUILD 
    COMMAND ./matrix_gtest
    COMMENT "Run matrix test..."
)