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

#include "SRLoop.h"

namespace drautomaton {

SRLoop::SRLoop()
{
  /* Transition table found in Appendix A of 
   * 
   * Hiroki Sayama, Constructing evolutionary systems on a simple
   * deterministic cellular automata space (1998), URL:
   * https://pdfs.semanticscholar.org/9662/d07e5550cd82268dedee87d21c5f431865a8.pdf
   * */
  push(0, 0, 0, 0, 0, 0);
  push(0, 0, 0, 0, 1, 2);
  push(0, 0, 0, 0, 2, 0);
  push(0, 0, 0, 0, 3, 0);
  push(0, 0, 0, 0, 5, 0);
  push(0, 0, 0, 0, 6, 3);
  push(0, 0, 0, 0, 7, 1);
  push(0, 0, 0, 1, 1, 2);
  push(0, 0, 0, 1, 2, 2);
  push(0, 0, 0, 1, 3, 2);
  push(0, 0, 0, 2, 1, 2);
  push(0, 0, 0, 2, 2, 0);
  push(0, 0, 0, 2, 3, 0);
  push(0, 0, 0, 2, 6, 2);
  push(0, 0, 0, 2, 7, 2);
  push(0, 0, 0, 3, 2, 0);
  push(0, 0, 0, 5, 2, 5);
  push(0, 0, 0, 6, 2, 2);
  push(0, 0, 0, 7, 2, 2);
  push(0, 0, 1, 0, 2, 2);
  push(0, 0, 1, 1, 2, 0);
  push(0, 0, 2, 0, 2, 0);
  push(0, 0, 2, 0, 3, 0);
  push(0, 0, 2, 0, 5, 0);
  push(0, 0, 2, 1, 2, 5);
  push(0, 0, 2, 2, 2, 0);
  push(0, 0, 2, 3, 2, 2);
  push(0, 0, 5, 2, 2, 2);
  push(0, 1, 2, 3, 2, 1);
  push(0, 1, 2, 4, 2, 1);
  push(0, 1, 2, 5, 2, 5);
  push(0, 1, 2, 6, 2, 1);
  push(0, 1, 2, 7, 2, 1);
  push(0, 1, 2, 7, 5, 1);
  push(0, 1, 4, 2, 2, 1);
  push(0, 1, 4, 3, 2, 1);
  push(0, 1, 4, 4, 2, 1);

  push(0, 1, 4, 7, 2, 1);
  push(0, 1, 6, 2, 5, 1);
  push(0, 1, 7, 2, 2, 1);
  push(0, 1, 7, 2, 5, 5);
  push(0, 1, 7, 5, 2, 1);
  push(0, 1, 7, 6, 2, 1);
  push(0, 1, 7, 7, 2, 1);
  push(0, 2, 5, 2, 7, 1);
  push(1, 0, 0, 0, 1, 1);
  push(1, 0, 0, 0, 6, 1);
  push(1, 0, 0, 0, 7, 7);
  push(1, 0, 0, 1, 1, 1);
  push(1, 0, 0, 1, 2, 1);
  push(1, 0, 0, 2, 1, 1);
  push(1, 0, 0, 2, 4, 4);
  push(1, 0, 0, 2, 7, 7);
  push(1, 0, 0, 5, 1, 1);
  push(1, 0, 1, 0, 1, 1);
  push(1, 0, 1, 1, 1, 1);
  push(1, 0, 1, 2, 4, 4);
  push(1, 0, 1, 2, 7, 7);
  push(1, 0, 2, 0, 2, 6);
  push(1, 0, 2, 1, 2, 1);
  push(1, 0, 2, 2, 1, 1);
  push(1, 0, 2, 2, 4, 4);
  push(1, 0, 2, 2, 6, 3);
  push(1, 0, 2, 2, 7, 7);
  push(1, 0, 2, 3, 2, 7);
  push(1, 0, 2, 4, 2, 4);
  push(1, 0, 2, 6, 2, 6);
  push(1, 0, 2, 6, 4, 4);
  push(1, 0, 2, 6, 7, 7);
  push(1, 0, 2, 7, 1, 0);
  push(1, 0, 2, 7, 2, 7);
  push(1, 0, 5, 4, 2, 7);
  push(1, 1, 1, 1, 2, 1);
  push(1, 1, 1, 2, 2, 1);

  push(1, 1, 1, 2, 4, 4);
  push(1, 1, 1, 2, 5, 1);
  push(1, 1, 1, 2, 6, 1);
  push(1, 1, 1, 2, 7, 7);
  push(1, 1, 1, 5, 2, 2);
  push(1, 1, 2, 1, 2, 1);
  push(1, 1, 2, 2, 2, 1);
  push(1, 1, 2, 2, 4, 4);
  push(1, 1, 2, 2, 5, 1);
  push(1, 1, 2, 2, 7, 7);
  push(1, 1, 2, 3, 2, 1);
  push(1, 1, 2, 4, 2, 4);
  push(1, 1, 2, 6, 2, 1);
  push(1, 1, 2, 7, 2, 7);
  push(1, 1, 3, 2, 2, 1);
  push(1, 2, 2, 2, 4, 4);
  push(1, 2, 2, 2, 7, 7);
  push(1, 2, 2, 4, 3, 4);
  push(1, 2, 2, 5, 4, 7);
  push(1, 2, 3, 2, 4, 4);
  push(1, 2, 3, 2, 7, 7);
  push(1, 2, 4, 2, 5, 5);
  push(1, 2, 4, 2, 6, 7);
  push(1, 2, 5, 2, 7, 5);
  push(2, 0, 0, 0, 1, 2);
  push(2, 0, 0, 0, 2, 2);
  push(2, 0, 0, 0, 4, 2);
  push(2, 0, 0, 0, 7, 1);
  push(2, 0, 0, 1, 2, 2);
  push(2, 0, 0, 1, 5, 2);
  push(2, 0, 0, 2, 1, 2);
  push(2, 0, 0, 2, 2, 2);
  push(2, 0, 0, 2, 3, 2);
  push(2, 0, 0, 2, 4, 2);
  push(2, 0, 0, 2, 5, 0);
  push(2, 0, 0, 2, 6, 2);
  push(2, 0, 0, 2, 7, 2);

  push(2, 0, 0, 3, 2, 6);
  push(2, 0, 0, 4, 2, 3);
  push(2, 0, 0, 5, 1, 7);
  push(2, 0, 0, 5, 2, 2);
  push(2, 0, 0, 5, 7, 5);
  push(2, 0, 0, 7, 2, 2);
  push(2, 0, 1, 0, 2, 2);
  push(2, 0, 1, 1, 2, 2);
  push(2, 0, 1, 2, 2, 2);
  push(2, 0, 1, 4, 2, 2);
  push(2, 0, 1, 7, 2, 2);
  push(2, 0, 2, 0, 2, 2);
  push(2, 0, 2, 0, 3, 2);
  push(2, 0, 2, 0, 5, 2);
  push(2, 0, 2, 0, 7, 3);
  push(2, 0, 2, 1, 2, 2);
  push(2, 0, 2, 1, 5, 2);
  push(2, 0, 2, 2, 1, 2);
  push(2, 0, 2, 2, 2, 2);
  push(2, 0, 2, 2, 7, 2);
  push(2, 0, 2, 3, 2, 1);
  push(2, 0, 2, 4, 2, 2);
  push(2, 0, 2, 4, 5, 2);
  push(2, 0, 2, 5, 2, 0);
  push(2, 0, 2, 5, 5, 2);
  push(2, 0, 2, 6, 2, 2);
  push(2, 0, 2, 7, 2, 2);
  push(2, 0, 3, 1, 2, 2);
  push(2, 0, 3, 2, 1, 6);
  push(2, 0, 3, 2, 2, 6);
  push(2, 0, 3, 4, 2, 2);
  push(2, 0, 4, 2, 2, 2);
  push(2, 0, 5, 1, 2, 2);
  push(2, 0, 5, 2, 2, 2);
  push(2, 0, 5, 5, 2, 1);
  push(2, 0, 5, 7, 2, 5);

  push(2, 0, 6, 2, 2, 2);
  push(2, 0, 6, 7, 2, 2);
  push(2, 0, 7, 1, 2, 2);
  push(2, 0, 7, 2, 2, 2);
  push(2, 0, 7, 4, 2, 2);
  push(2, 0, 7, 7, 2, 2);
  push(2, 1, 1, 2, 2, 2);
  push(2, 1, 1, 2, 6, 1);
  push(2, 1, 2, 2, 2, 2);
  push(2, 1, 2, 2, 4, 2);
  push(2, 1, 2, 2, 6, 2);
  push(2, 1, 2, 2, 7, 2);
  push(2, 1, 4, 2, 2, 2);
  push(2, 1, 5, 2, 2, 2);
  push(2, 1, 6, 2, 2, 2);
  push(2, 1, 7, 2, 2, 2);
  push(2, 2, 2, 2, 7, 2);
  push(2, 2, 2, 4, 4, 2);
  push(2, 2, 2, 4, 6, 2);
  push(2, 2, 2, 7, 6, 2);
  push(2, 2, 2, 7, 7, 2);
  push(3, 0, 0, 0, 1, 3);
  push(3, 0, 0, 0, 2, 2);
  push(3, 0, 0, 0, 4, 1);
  push(3, 0, 0, 0, 7, 6);
  push(3, 0, 0, 1, 2, 3);
  push(3, 0, 0, 4, 2, 1);
  push(3, 0, 0, 6, 2, 2);
  push(3, 0, 1, 0, 2, 1);
  push(3, 0, 1, 2, 2, 0);
  push(3, 0, 2, 5, 1, 1);
  push(4, 0, 1, 1, 2, 0);
  push(4, 0, 1, 2, 2, 0);
  push(4, 0, 1, 2, 5, 0);
  push(4, 0, 2, 1, 2, 0);
  push(4, 0, 2, 2, 2, 1);
  push(4, 0, 2, 3, 2, 6);

  push(4, 0, 2, 5, 2, 0);
  push(4, 0, 3, 2, 2, 1);
  push(5, 0, 0, 0, 2, 2);
  push(5, 0, 0, 2, 1, 5);
  push(5, 0, 0, 2, 2, 5);
  push(5, 0, 0, 2, 3, 2);
  push(5, 0, 0, 2, 7, 2);
  push(5, 0, 0, 5, 2, 0);
  push(5, 0, 2, 0, 2, 2);
  push(5, 0, 2, 1, 2, 2);
  push(5, 0, 2, 1, 5, 2);
  push(5, 0, 2, 2, 2, 0);
  push(5, 0, 2, 2, 4, 4);
  push(5, 0, 2, 7, 2, 2);
  push(5, 1, 2, 1, 2, 2);
  push(5, 1, 2, 2, 2, 0);
  push(5, 1, 2, 4, 2, 2);
  push(5, 1, 2, 7, 2, 2);
  push(6, 0, 0, 0, 1, 1);
  push(6, 0, 0, 0, 2, 1);
  push(6, 0, 2, 1, 2, 0);
  push(6, 1, 2, 1, 2, 5);
  push(6, 1, 2, 1, 3, 1);
  push(6, 1, 2, 2, 2, 5);
  push(7, 0, 0, 0, 7, 7);
  push(7, 0, 1, 1, 2, 0);
  push(7, 0, 1, 2, 2, 0);
  push(7, 0, 1, 2, 5, 0);
  push(7, 0, 2, 1, 2, 0);
  push(7, 0, 2, 2, 2, 1);
  push(7, 0, 2, 2, 5, 1);
  push(7, 0, 2, 3, 2, 1);
  push(7, 0, 2, 5, 2, 5);
  push(7, 0, 2, 7, 2, 0);
}

SRLoop::State
SRLoop::transition(int x, int y, const Space<State>& space) const
{
  // Get states.
  State state = space.cell(x, y);
  int c = static_cast<int>(state);
  int t = static_cast<int>(space.geometricCell(x, y - 1));
  int b = static_cast<int>(space.geometricCell(x, y + 1));
  int r = static_cast<int>(space.geometricCell(x + 1, y));
  int l = static_cast<int>(space.geometricCell(x - 1, y));

  // Find matching pattern.
  auto it = transitions_.find(std::make_tuple(c, t, r, b, l));
  if (it != transitions_.end())
  {
    return static_cast<State>(it->second);
  }

  // If no transition is found, leave the cell unchanged.
  return state;
}

SRLoop::State
SRLoop::increment(const State& x) const
{
  return static_cast<State>(static_cast<int>(x) % 8);
}

// Push rotationally symmetric (c, t, r, b, l) -> rule.
void
SRLoop::push(int c, int t, int r, int b, int l, int n)
{
  transitions_[std::make_tuple(c, t, r, b, l)] = n;
  transitions_[std::make_tuple(c, r, b, l, t)] = n;
  transitions_[std::make_tuple(c, b, l, t, r)] = n;
  transitions_[std::make_tuple(c, l, t, r, b)] = n;
}

} // namespace drautomaton
