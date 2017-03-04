# =================================
# mr_rogers - test
#
# test/CMakeLists.txt
# =================================

# set header and source files
set(MR_ROGERS_TEST_SOURCES
  gtest_main.cpp
)

# Where Google Test's .h files can be found.
include_directories(
  ${CMAKE_SOURCE_DIR}
  ${GTEST_SOURCE_DIR}/include
  ${GTEST_SOURCE_DIR}
  ${EIGEN_INCLUDE_DIR}
 )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # clang Doesnt use pthread
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()
#set(CMAKE_BUILD_TYPE Debug)


#create binary
add_executable(mr_rogers_tests
  gtest_main.cpp
)

target_link_libraries(mr_rogers_tests
  ${CORE_LIB}
  ${GTEST_LIB}
)

add_dependencies(mr_rogers_tests ${MR_ROGERS_EXTERNAL_PROJECT})
