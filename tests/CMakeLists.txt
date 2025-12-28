

include(FetchContent)

# ------------------------------------------------------------------------------
# GoogleTest
# ------------------------------------------------------------------------------

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)

# Prevent overriding parent project compiler flags
set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

add_executable(address_book_tests
  address_book_test.cpp
)

target_link_libraries(address_book_tests
  PUBLIC
    address_book
    protobuf::libprotobuf
    gtest_main
)
