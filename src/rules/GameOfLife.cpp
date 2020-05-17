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

#include "GameOfLife.h"

namespace drautomaton {

GameOfLife::State
GameOfLife::transition(
    int x,
    int y,
    const Space<State>& space
  )
{
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

      live_count += (space.geometricCell(x + i, y + j) == State::live ? 1 : 0);
    }
  }

  // Do the transition.
  if (live_count == 3)
  {
    return State::live;
  }
  else if (live_count != 2)  // Equivalent to: (live_count < 2) or (live_count > 3)
  {
    return State::dead;
  }
  return space.cell(x, y);
}

GameOfLife::State
GameOfLife::increment(const State& state)
{
  if (state == State::dead)
  {
    return State::live;
  }
  else
  {
    return State::dead;
  }
}

} // namespace drautomaton
