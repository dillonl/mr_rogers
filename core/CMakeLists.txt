INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${EIGEN_INCLUDE_DIR}
	${EXTERNAL_SORT_INCLUDE_DIR}
)

#set(CMAKE_BUILD_TYPE Debug) # uncomment this when you need a debug build

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # clang Doesnt use pthread
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

set(CORE_SOURCES
    file/FileWriter.cpp
	database/Database.cpp
  )

add_library(mr_rogers_core STATIC
  ${CORE_SOURCES}
  )

SET(CORE_LIB mr_rogers_core CACHE STRING "THE CORE LIBRARY") #add mr_rogers_core and utils to the list of core libs

TARGET_LINK_LIBRARIES(${CORE_LIB}
)

add_dependencies(${CORE_LIB} ${MR_ROGERS_EXTERNAL_PROJECT})

