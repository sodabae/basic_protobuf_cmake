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
)

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

# ------------------------------------------------------------------------------
# End of file
# ------------------------------------------------------------------------------
