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

std::unordered_map<std::string, std::vector<Time>> data_{};

void start(const std::string& tag)
{
  // Push a new time stamp. (Default construct vector on first call)
  auto& x = data_[tag];
  x.push_back(Time{});
  x.back().start = std::chrono::high_resolution_clock::now();  // Note: Take time _last_.
}

void stop(const std::string& tag)
{
  // Take time _first_.
  auto t = std::chrono::high_resolution_clock::now();

  auto it = data_.find(tag);
  assert(it != data_.end() && "No such tag");
  it->second.back().stop = t;
}

unsigned int
getTime(const std::string& tag)
{
  auto it = data_.find(tag);
  assert(it != data_.end() && "No such tag");

  // Add up all complete time stamps.
  unsigned int t = 0;
  for (const auto& time : it->second)
  {
    if (time.isComplete())
    {
      t += time.getDuration();
    }
  }
  return t / 1000;
}

unsigned int
getPasses(const std::string& tag)
{
  auto it = data_.find(tag);
  assert(it != data_.end() && "No such tag");

  return std::count_if(
      it->second.begin(), it->second.end(),
      [&](const auto& time)
      {
        return time.isComplete();
      }
    );
}

unsigned int
getIncompletePasses(const std::string& tag)
{
  auto it = data_.find(tag);
  assert(it != data_.end() && "No such tag");

  return std::count_if(
      it->second.begin(), it->second.end(),
      [&](const auto& time)
      {
        return (not time.isComplete());
      }
    );
}

unsigned int
getSlowestPass(const std::string& tag)
{
  auto it = data_.find(tag);
  assert(it != data_.end() && "No such tag");

  unsigned int t = 0;
  std::for_each(
      it->second.begin(), it->second.end(),
      [&](const auto& time)
      {
        if (time.isComplete())
        {
          t = std::max(t, time.getDuration());
        }
      }
    );
  return t;
}

unsigned int getFastestPass(const std::string& tag)
{
  auto it = data_.find(tag);
  assert(it != data_.end() && "No such tag");

  unsigned int t = 0;
  bool initialized = false;
  std::for_each(
      it->second.begin(), it->second.end(),
      [&](const auto& time)
      {
        if (time.isComplete())
        {
          if (not initialized)
          {
            t = time.getDuration();
            initialized = true;
            return;
          }
          t = std::min(t, time.getDuration());
        }
      }
    );
  return t;
}

} // namespace drprof
