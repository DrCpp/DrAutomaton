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

#include <future>

#include "detail/Profiling.h"
#include "geometry/Torus.h"
#include "rules/GameOfLife.h"

namespace drautomaton {

template<typename Rule>
Cellular<Rule>::Cellular(int width, int height)
:
  space_{width, height},
  tmp_{width, height},
  rule_{}
{
  // Note: These asserts are already enforced by the Space ctor.
  assert(width  > 0);
  assert(height > 0);

  // Get number of available threads.
  auto num_threads = std::thread::hardware_concurrency();
  if (num_threads == 0)
  {
    throw std::runtime_error{"Failed to obtain number of concurrent threads."};
  }

  // Determine blocksize.
  auto blocksize = space_.width() / num_threads;
  auto remainder = space_.width() % num_threads;
  int start = 0;
  for (std::size_t i = 0; i < num_threads; ++i)
  {
    auto end = start + blocksize;
    if (remainder > 0)
    {
      ++end;
      --remainder;
    }
    blocks_.push_back({start, end});
    start = end;
  }
}

template<typename Rule>
const Space<typename Rule::State>&
Cellular<Rule>::space() const
{
  return space_;
}

template<typename Rule>
Space<typename Rule::State>&
Cellular<Rule>::space()
{
  return space_;
}

template<typename Rule>
void
Cellular<Rule>::processBlock(
    const Space<typename Rule::State>& from,
    Space<typename Rule::State>& to,
    int from_index,
    int to_index,
    std::function<void(int, int, typename Rule::State&)> trans
  )
{
  for (int x = from_index; x < to_index; ++x)
  {
    std::vector<typename Rule::State>& to_data = to.data()[x];
    for (int y = 0; y < from.height(); ++y)
    {
      trans(x, y, to_data[y]);
    }
  }
}

template<typename Rule>
void
Cellular<Rule>::setGeometry(std::shared_ptr<AbstractGeometry<typename Rule::State>> geometry)
{
  geometry_ = std::move(geometry);
}

template<typename Rule>
void
Cellular<Rule>::doUpdate()
{
  DRPROF_START("Cellular::doUpdate");

  // Update the geometry of the underlying space.
  space_.setGeometry(geometry_);

  DRPROF_START("Cellular::doUpdate::update");
  std::vector<std::future<void>> futures{};
  for (const auto& block : blocks_)
  {
    futures.push_back(std::async(
        std::launch::async,
        &Cellular<Rule>::processBlock,
          this,
          std::ref(space_),
          std::ref(tmp_),
          std::get<0>(block),
          std::get<1>(block),
          [&] (int x, int y, typename Rule::State& out)
              {
                out = rule_.transition(x, y, space_);
              }
      ));
  }

  futures[0].wait();
  DRPROF_START("Cellular::wait");
  for (const auto& f : futures)
  {
    f.wait();
  }
  DRPROF_STOP("Cellular::wait");
  futures.clear();
  DRPROF_STOP("Cellular::doUpdate::update");

  DRPROF_START("Cellular::doUpdate::copy");
  space_ = std::move(tmp_);
  tmp_ = Space<typename Rule::State>(space_.width(), space_.height());
  space_.setGeometry(geometry_);
  DRPROF_STOP("Cellular::doUpdate::copy");

  DRPROF_STOP("Cellular::doUpdate");
  emit CellularQObject::updated();
}

template<typename Rule>
void
Cellular<Rule>::increment(int x, int y)
{
  space_.cell(x, y) = rule_.increment(space_.cell(x, y));
  emit CellularQObject::updated();
}

} // namespace drautomaton
