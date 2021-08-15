# Copyright 2020 Ole Kliemann, Malte Kliemann
#
# This file is part of DrAutomaton.
#
# DrAutomaton is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation, either version 3 of the License, or (at your
# option) any later version.
#
# DrAutomaton is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with DrAutomaton.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.10)

#######################################
# Project data.
#######################################

project(DrAutomaton
  VERSION 0.0.0
  DESCRIPTION "C++17 cellular automaton framework"
  LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)

#######################################
# Dependencies.
#######################################

# Import DrMock if installed.
find_package(DrMock COMPONENTS DrMock REQUIRED)
if (${DrMock_FOUND})
  drmock_enable_qt()
else()
  set(CMAKE_AUTOMOC ON)
endif()
find_package(Qt5 COMPONENTS Core Test Quick REQUIRED)
set(CMAKE_AUTORCC ON)

#######################################
# Sources.
#######################################

set(compileOptions
  -Wall -Werror -g -fPIC -pedantic -O2 -fdiagnostics-color=always
)

add_subdirectory(src)

#######################################
# Configure install.
#######################################

set(CMAKE_INSTALL_INCLUDEDIR "include/${PROJECT_NAME}")
set(CMAKE_INSTALL_LIBDIR "lib")
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(
  DIRECTORY pkgconfig/
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
  FILES_MATCHING
    PATTERN "*.pc"
)
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Uncomment to alias the libraries on export.
set_target_properties(${PROJECT_NAME} PROPERTIES EXPORT_NAME ${PROJECT_NAME})

install(
  DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
  DIRECTORY src/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING
    PATTERN "*.h"
    PATTERN "*.tpp"
)

#######################################
# pkgconfig
#######################################

configure_file(
  ${CMAKE_SOURCE_DIR}/pkgconfig/${PROJECT_NAME}.pc.in
  ${CMAKE_SOURCE_DIR}/pkgconfig/${PROJECT_NAME}.pc
)

#######################################
# Configure export.
#######################################

install(
  EXPORT
    ${PROJECT_NAME}Targets
  FILE
    ${PROJECT_NAME}Targets.cmake
  NAMESPACE
    ${PROJECT_NAME}::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION
    ${PROJECT_VERSION}
  COMPATIBILITY
    SameMajorVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION
    ${INSTALL_CONFIGDIR}
)

# Install config files.
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

export(
  EXPORT
    ${PROJECT_NAME}Targets
  FILE
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake
  NAMESPACE
    ${PROJECT_NAME}::
)

export(PACKAGE ${PROJECT_NAME})

#######################################
# Testing.
#######################################

enable_testing()
add_subdirectory(tests)
