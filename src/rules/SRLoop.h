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

#ifndef DRAUTOMATON_SRC_RULES_SRLOOP_H
#define DRAUTOMATON_SRC_RULES_SRLOOP_H

#include <map>

#include "../Space.h"

// FIXME Abstract this into a general rotationally symmetric VonNeumann
// neighborhood automaton.

namespace drautomaton {

/* SRLoop

Implementation of Langton's self-replicating loop rule (SRLoop).
Requires an underyling space equipped with a geometry.
*/

class SRLoop
{
public:
  enum class State
  {
    background, core, sheath, bonder, guide, messenger, umbilical, gene
  };

  SRLoop();

  State transition(int x, int y, const Space<State>&) const;
  State increment(const State&) const;

private:
  // Push rotationally symmetric (c, t, r, b, l) -> rule.
  void push(int, int, int, int, int, int);

  // ctrbl-> map
  std::map<std::tuple<int, int, int, int, int>, int> transitions_;
};

} // namespace drautomaton

#endif /* DRAUTOMATON_SRC_RULES_SRLOOP_H */
