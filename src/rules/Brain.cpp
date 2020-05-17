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

#include "Brain.h"

namespace drautomaton {

Brain::State
Brain::transition(
    int x,
    int y,
    const Space<State>& space
  )
{
  auto state = space.cell(x, y);

  if (state == State::on)
  {
    return State::dying;
  }
  else if (state == State::dying)
  {
    return State::off;
  }

  // Count number of live space.
  auto live_count = 0;
  for (int i = -1; i <= 1; ++i)
  {
    for (int j = -1; j <= 1; ++j)
    {
      if ((i == 0) and (j == 0))
      {
        continue;
      }

      live_count += (space.geometricCell(x + i, y + j) == State::on ? 1 : 0);
    }
  }

  // Do the transition.
  if (live_count == 2)
  {
    return State::on;
  }
  return state;  // dead
}

Brain::State
Brain::increment(const State& state)
{
  return static_cast<Brain::State>((static_cast<int>(state) + 1) % 3);
}

} // namespace drautomaton
