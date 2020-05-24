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
#include <vector>
#include <unordered_map>

namespace drprof {

struct Time
{
  // Return duration in microseconds.
  unsigned int getDuration() const
  {
    return std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
  }

  // Check if both time points have been set.
  bool isComplete() const
  {
    // ...by checking that `stop` isn't equal to the clock's epoch.
    return stop != std::chrono::high_resolution_clock::time_point{};
  }

  // Note: Default value is the clock's epoch.
  std::chrono::high_resolution_clock::time_point start{};
  std::chrono::high_resolution_clock::time_point stop{};
};

extern std::unordered_map<std::string, std::vector<Time>> data_;

void start(const std::string&);
void stop(const std::string&);
unsigned int getTime(const std::string&);  // In milliseconds.
unsigned int getPasses(const std::string&);
unsigned int getSlowestPass(const std::string&);
unsigned int getFastestPass(const std::string&);

} // namespace drprof

#ifdef DRAUTO_PROFILING

#define DRPROF_START(tag) drprof::start(tag)

#define DRPROF_STOP(tag) drprof::stop(tag)

#define DRPROF_PRINT(tag) \
do { \
  auto it = drprof::data_.find(tag); \
  assert(it != drprof::data_.end() && "No such tag: " # tag); \
  std::cout << "DrProf: " << tag << ": " << drprof::getTime(tag) << "ms" << "; " << drprof::getPasses(tag) << " passes" << std::endl; \
} while(0)

#define DRPROF_PRINT_ALL() \
do { \
  for (const auto& tag : drprof::data_) \
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
