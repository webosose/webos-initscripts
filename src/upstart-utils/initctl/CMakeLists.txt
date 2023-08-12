# Copyright (c) 2017-2018 LG Electronics, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0

include(FindPkgConfig)

# Basic
set(BIN_NAME initctl)
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Compiling
webos_add_compiler_flags(ALL --std=c++11)
webos_configure_source_files(cfg ${CMAKE_CURRENT_SOURCE_DIR}/Environment.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR}/Configured/src/upstart-utils/initctl)
add_executable(${BIN_NAME} ${SRC_FILES})

# Linking
set(LIBS
    -lsystemd
)
target_link_libraries(${BIN_NAME} ${LIBS})

# Install
install(TARGETS ${BIN_NAME} RUNTIME DESTINATION ${WEBOS_INSTALL_BASE_SBINDIR})
