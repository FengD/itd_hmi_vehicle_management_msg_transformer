cmake_minimum_required(VERSION 2.8)

project(vm_s32_v)

# add cxx flags
SET(CMAKE_C_COMPILER "/usr/bin/gcc")
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")
SET(CMAKE_BUILD_TYPE Release)
add_definitions(-Wall -std=c++11)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

aux_source_directory(s32v/src SRCS)
aux_source_directory(s32v/api SRCS)
aux_source_directory(module/communication/tcp/src SRCS)
aux_source_directory(module/communication/udp/src SRCS)
aux_source_directory(module/our_thread/src SRCS)


message(${SRCS})

include_directories(
  s32v/include
  s32v/api
  module/communication/tcp/include
  module/communication/udp/include
  module/our_thread/include
  module/common/include
)

add_executable(vm_s32_v ${SRCS})

target_link_libraries(vm_s32_v
  pthread
  yaml-cpp
  protobuf
)
