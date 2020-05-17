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

#ifndef DRAUTOMATON_SRC_PROFILING_H
#define DRAUTOMATON_SRC_PROFILING_H

#include <chrono>
#include <iostream>
#include <tuple>
#include <unordered_map>

namespace drprof {

extern std::unordered_map<
    std::string,
    std::tuple<
        std::chrono::high_resolution_clock::time_point,
        unsigned int,
        unsigned int
      >
  > tags_;

unsigned int getTime(const std::string&);
unsigned int getPasses(const std::string&);

} // namespace drprof

#ifdef DRAUTO_PROFILING

#define DRPROF_START(tag) \
do { \
  auto it = drprof::tags_.insert(std::make_pair(tag, std::make_tuple(std::chrono::high_resolution_clock::time_point{}, 0, 0))).first; \
  std::get<0>(std::get<1>(*it)) = std::chrono::high_resolution_clock::now(); \
} while(0)

#define DRPROF_STOP(tag) \
do { \
  auto it = drprof::tags_.find(tag); \
  assert(it != drprof::tags_.end() && "No such tag: " # tag); \
  auto t1 = std::chrono::high_resolution_clock::now(); \
  std::get<1>(std::get<1>(*it)) += std::chrono::duration_cast<std::chrono::microseconds>( \
      t1 - std::get<0>(std::get<1>(*it)) \
    ).count(); \
  std::get<2>(std::get<1>(*it)) += 1; \
} while(0)

#define DRPROF_PRINT(tag) \
do { \
  auto it = drprof::tags_.find(tag); \
  assert(it != drprof::tags_.end() && "No such tag: " # tag); \
  std::cout << "DrProf: " << tag << ": " << std::get<1>(std::get<1>(*it)) / 1000 << "ms" << "; " << std::get<2>(std::get<1>(*it)) << " passes" << std::endl; \
} while(0)

#define DRPROF_PRINT_ALL() \
do { \
  for (const auto& tag : drprof::tags_) \
  { \
    DRPROF_PRINT(std::get<0>(tag)); \
  } \
} while(0)

#else

// If profiling is disabled, ignore the macros.
#define DRPROF_START(...)
#define DRPROF_STOP(...)
#define DRPROF_PRINT(...)
#define DRPROF_PRINT_ALL(...)

#endif

#endif /* DRAUTOMATON_SRC_PROFILING_H */
