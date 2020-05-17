/* Copyright 2020 Malte Kliemann, Ole Kliemann
 *
 * This file is part of DrAutomaton.
 *
 * DrAutomaton is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * DrAutomaton is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DrAutomaton.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "Profiling.h"

#include <cassert>

namespace drprof {

std::unordered_map<
    std::string,
    std::tuple<
        std::chrono::high_resolution_clock::time_point,
        unsigned int,
        unsigned int
      >
  > tags_{};

unsigned int
getTime(const std::string& tag)
{
  auto it = drprof::tags_.find(tag);
  assert(it != drprof::tags_.end() && "No such tag");
  return std::get<1>(std::get<1>(*it)) / 1000;
}

unsigned int
getPasses(const std::string& tag)
{
  auto it = drprof::tags_.find(tag);
  assert(it != drprof::tags_.end() && "No such tag");
  return std::get<2>(std::get<1>(*it));
}

} // namespace drprof
