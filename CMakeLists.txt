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

set(protobuf_BUILD_TESTS OFF CACHE BOOL "" FORCE)

#If symlinks aren't working... and you have a late enough version of protobufs
#  note, you can find the CMake options by looking at the CMakeList.txt of the protobufs
#  i.e. grep -R "option(protobuf" ./build/_deps/
set(protobuf_DISABLE_SYMLINKS ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(protobuf)

# ---------------------------
# Protobuf code generation
# ---------------------------
set(PROTO_FILE ${CMAKE_CURRENT_SOURCE_DIR}/proto/person.proto)

set(GENERATED_SRC ${CMAKE_CURRENT_BINARY_DIR}/person.pb.cc)
set(GENERATED_HDR ${CMAKE_CURRENT_BINARY_DIR}/person.pb.h)

add_custom_command(
  OUTPUT ${GENERATED_SRC} ${GENERATED_HDR}
  COMMAND protobuf::protoc
  ARGS
    --cpp_out=${CMAKE_CURRENT_BINARY_DIR}
    -I ${CMAKE_CURRENT_SOURCE_DIR}/proto
    ${PROTO_FILE}
  DEPENDS ${PROTO_FILE} protobuf::protoc
  COMMENT "Generating C++ protobuf sources"
)

# Group generated files into a target
add_library(person_proto ${GENERATED_SRC} ${GENERATED_HDR})
target_link_libraries(person_proto PUBLIC protobuf::libprotobuf)
target_include_directories(person_proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# ---------------------------
# Application
# ---------------------------
add_executable(protobuf_app src/main.cpp)
target_link_libraries(protobuf_app PRIVATE person_proto)

