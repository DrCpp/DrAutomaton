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

cmake_minimum_required(VERSION 3.7)

include_directories(../src)

if (${DrMock_FOUND})
  drmock_test(
    LIBS DrAutomatonMock Qt5::Test  # Qt5::Test required for QSignalSpy.
    TESTS
      Space.cpp
      Geometry.cpp
      Model.cpp
      Cellular.cpp
      View.cpp
      Profiling.cpp
    OPTIONS ${compileOptions}
    RESOURCES Profiling.qrc
  )
endif()

add_subdirectory(ViewTest)
