
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/tests/data)
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/TestConfig.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/TestConfig.h"
)
