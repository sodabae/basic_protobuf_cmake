cmake_minimum_required(VERSION 3.16)

project(address_book
  VERSION 1.0
  LANGUAGES CXX
)

# ------------------------------------------------------------------------------
# C++ standard
# ------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include(FetchContent)

# ------------------------------------------------------------------------------
# Coverage option
# ------------------------------------------------------------------------------
option(ENABLE_COVERAGE "Enable gcov coverage" OFF)

if (ENABLE_COVERAGE)
  add_library(coverage_compile_flags INTERFACE)
  target_compile_options(coverage_compile_flags INTERFACE
    --coverage
    -O0
    -g
  )
  add_library(coverage_link_flags INTERFACE)
  target_link_options(coverage_link_flags INTERFACE
   --coverage
  )
endif()

# ------------------------------------------------------------------------------
# spdlog
#   if spdlog is installed on the system/container, could just use:
#     find_package(spdlog REQUIRED)
#   otherwise, need to fetch it using the commands below...
# ------------------------------------------------------------------------------

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        v1.13.0
)

# Disable unneeded spdlog features
set(SPDLOG_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_BENCH    OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(spdlog)

# ------------------------------------------------------------------------------
# Discover Protobuf (system-installed)
# ------------------------------------------------------------------------------

# This provides:
#   protobuf::libprotobuf  - runtime library
#   protobuf::protoc       - protocol compiler
find_package(Protobuf CONFIG REQUIRED)

# ------------------------------------------------------------------------------
# Protobuf code generation
# ------------------------------------------------------------------------------

# Input .proto file
set(PROTO_FILE
  ${CMAKE_CURRENT_SOURCE_DIR}/proto/person.proto
)

# Output directory for generated files
set(GENERATED_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/generated
)

# Generated source/header
set(GENERATED_SRC
  ${GENERATED_DIR}/person.pb.cc
)

set(GENERATED_HDR
  ${GENERATED_DIR}/person.pb.h
)

# Ensure the generated directory exists at configure time
file(MAKE_DIRECTORY ${GENERATED_DIR})

# Custom command that runs protoc
add_custom_command(
  OUTPUT
    ${GENERATED_SRC}
    ${GENERATED_HDR}

  COMMAND
    protobuf::protoc

  ARGS
    --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/proto
    --cpp_out=${GENERATED_DIR}
    ${PROTO_FILE}

  DEPENDS
    ${PROTO_FILE}

  COMMENT
    "Generating C++ protobuf sources from person.proto"

  VERBATIM
)

# ------------------------------------------------------------------------------
# Address book library
# ------------------------------------------------------------------------------

add_library(address_book
  src/address_book.cpp
  ${GENERATED_SRC}
  ${GENERATED_HDR}
)

# Public headers live in hdrs/
# Generated protobuf headers are private implementation details
target_include_directories(address_book
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/hdrs
    ${GENERATED_DIR}
)

# Link against protobuf runtime
target_link_libraries(address_book
  PUBLIC
    protobuf::libprotobuf
    spdlog::spdlog
)

if (ENABLE_COVERAGE)
  #only propogate the link flags forward since only want coverage of the files in the address_book library
  target_link_libraries(address_book
    PUBLIC coverage_link_flags
    PRIVATE coverage_compile_flags
  )
endif()

# ------------------------------------------------------------------------------
# Executable
# ------------------------------------------------------------------------------

add_executable(address_book_app
  src/main.cpp
)

target_link_libraries(address_book_app
  PRIVATE
    address_book
)

add_subdirectory(tests)
# ------------------------------------------------------------------------------
# End of file
# ------------------------------------------------------------------------------
