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

#ifndef DRAUTOMATON_SRC_ICELLULAR_H
#define DRAUTOMATON_SRC_ICELLULAR_H

#include "Space.h"
#include "CellularQObject.h"

/* Cellular
 *
 * Cellular automaton class template. The template parameter specifies
 * the rule of the CA. `Rule` must satisfy a certain interface, which is
 * found in `IRule.h`. */

namespace drautomaton {

template<typename T>
class ICellular : public CellularQObject
{
public:
  // Return the CA's underlying cell space. The top-left cell has
  // coordinates (0, 0).
  virtual const drautomaton::Space<T>& space() const = 0;
  virtual drautomaton::Space<T>& space() = 0;

  // Compute the next generation of cells.
  //
  // Listed as public slot in `CellularQObject` - put here so that it
  // get's implemented in mock code.
  virtual void doUpdate() = 0;

  // Increment cell with coords `(x, y)`.
  //
  // Listed as public slot in `CellularQObject` - put here so that it
  // get's implemented in mock code.
  virtual void increment(int x, int y) = 0;
};

} // namespace drautomaton

#endif /* DRAUTOMATON_SRC_ICELLULAR_H */
