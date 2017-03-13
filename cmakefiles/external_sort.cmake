#  For more information, please see: http://software.sci.utah.edu
# 
#  The MIT License
# 
#  Copyright (c) 2015 Scientific Computing and Imaging Institute,
#  University of Utah.
# 
#  
#  Permission is hereby granted, free of charge, to any person obtaining a
#  copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the
#  Software is furnished to do so, subject to the following conditions:
# 
#  The above copyright notice and this permission notice shall be included
#  in all copies or substantial portions of the Software. 
# 
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
#  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#  DEALINGS IN THE SOFTWARE.

# Setting up external library external_sort, we don't build it because we only need the include directories

SET_PROPERTY(DIRECTORY PROPERTY "EP_BASE" ${ep_base})

SET(EXTERNAL_SORT_PROJECT external_sort_project CACHE INTERNAL "external_sort project name")
SET(EXTERNAL_SORT_DIR ${CMAKE_BINARY_DIR}/externals/external_sort CACHE INTERNAL "external_sort project directory")
SET(EXTERNAL_SORT_LIB)
ExternalProject_Add(${EXTERNAL_SORT_PROJECT}
	GIT_REPOSITORY https://github.com/alveko/external_sort.git
	GIT_TAG 978cec45c4883ee5b34277b83d5fb9d929f0d3ee #lock in the commit id so we don't this doesn't break in the future
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
    INSTALL_COMMAND ""
	PREFIX ${EXTERNAL_SORT_DIR}
)

ExternalProject_Get_Property(${EXTERNAL_SORT_PROJECT} INSTALL_DIR)
ExternalProject_Get_Property(${EXTERNAL_SORT_PROJECT} SOURCE_DIR)
ExternalProject_Get_Property(${EXTERNAL_SORT_PROJECT} BINARY_DIR)

SET(EXTERNAL_SORT_INCLUDE_DIR ${SOURCE_DIR} CACHE INTERNAL "EXTERNAL_SORT Include")
