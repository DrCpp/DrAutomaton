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

project(cyclic)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)
find_package(DrAutomaton COMPONENTS DrAutomaton)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(compileOptions -Wall -Werror -g -fPIC -pedantic -O2 -fdiagnostics-color=always)
add_executable(cyclic
  Cyclic.cpp
  Cyclic.qrc
)
target_link_libraries(cyclic
  DrAutomaton::DrAutomaton
  Qt5::Core
  Qt5::Quick
)
