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

add_library(${PROJECT_NAME} SHARED
  detail/Gate.cpp
  detail/Profiling.cpp
  detail/Utility.cpp
  rules/Brain.cpp
  rules/GameOfLife.cpp
  rules/SRLoop.cpp
  IModel.h
  ICellular.h
  CellularQObject.h
  View.cpp
)

target_link_libraries(${PROJECT_NAME}
  Qt5::Core
  Qt5::Quick
  pthread
)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_compile_options(${PROJECT_NAME} PRIVATE ${compileOptions})

# If DrMock is installed, create the mock module.
if (${DrMock_FOUND})
  DrMockModule(
    TARGET ${PROJECT_NAME}Mock
    QTMODULES
      Qt5::Core
      Qt5::Quick
    HEADERS
      IModel.h
      ICellular.h
    LIBS
      DrAutomaton
  )
  target_compile_options(${PROJECT_NAME}Mock PRIVATE ${compileOptions})
endif()
