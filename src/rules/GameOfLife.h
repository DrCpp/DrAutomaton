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

#ifndef DRAUTOMATON_SRC_RULES_GAMEOFLIFE_H
#define DRAUTOMATON_SRC_RULES_GAMEOFLIFE_H

#include "../Space.h"

namespace drautomaton {

/* Cyclic

Implementation of J.H. Conway's Game of Life rule. Requires an
underlying space equipped with a geometry.
*/

class GameOfLife
{
public:
  enum class State : bool
  {
    dead = false, live = true
  };

  static State transition(int x, int y, const Space<State>&);
  static State increment(const State&);
};

} // namespace drautomaton

#endif /* DRAUTOMATON_SRC_RULES_GAMEOFLIFE_H */
