cmake_minimum_required(VERSION 3.15)
project(fetchcontent_protobuf_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# ---------------------------
# Fetch protobuf
# ---------------------------
FetchContent_Declare(
  protobuf
  GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
  GIT_TAG v21.12
)

# Disable tests (faster build)
set(protobuf_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(protobuf)
include(${protobuf_SOURCE_DIR}/cmake/protobuf-generate.cmake)

# ---------------------------
# Generate C++ from .proto
# ---------------------------
set(PROTO_FILE ${CMAKE_CURRENT_SOURCE_DIR}/proto/person.proto)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILE})

# ---------------------------
# Application target
# ---------------------------
add_executable(protobuf_app
    src/main.cpp
    ${PROTO_SRCS}
    ${PROTO_HDRS}
)

# Generated files live in the build directory
target_include_directories(protobuf_app
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(protobuf_app
    PRIVATE
    protobuf::libprotobuf
)
