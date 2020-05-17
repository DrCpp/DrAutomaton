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

#include "Space.h"

/* Cellular automaton rule for testing. */

class Test
{
public:
  enum class State : bool
  {
    dead = false, live = true
  };

  static State transition(std::size_t x, std::size_t y, const drautomaton::Space<State>& space)
  {
    auto state = space.cell(x, y);
    return flip(state);
  }

  static State increment(const State& state)
  {
    return flip(state);
  }

private:
  static State flip(const State& state)
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
};
