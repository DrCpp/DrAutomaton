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

#ifndef DRAUTOMATON_SRC_SPACE_H
#define DRAUTOMATON_SRC_SPACE_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "AbstractGeometry.h"

/* Space

Row-major matrix class. Every entry of the matrix represents one cell of
a cellular automaton./

The space may be equipped with a _geometry_, which transforms
coordinates into the range of the underlying vector.


*/

namespace drautomaton {

template<typename T>
class Space
{
public:
  Space(int width, int height);

  int width() const;
  int height() const;

  // Get the (x, y)^th cell. 
  //
  // This call does _not_ use the space's geometry to transform (x, y)
  // into valid coordinates. In particular, using coordinates that are
  // out of bounds (i.e. do not satisfy 0 <= x < width and
  // 0 <= y < height) will result in obtaining a reference to the wrong
  // cell, or undefined behavior.
  T& cell(int x, int y);
  const T& cell(int x, int y) const;

  // Return pointer to vector memory (for concurrent access).
  std::vector<T>* data();
  const std::vector<T>* data() const;

  void setGeometry(std::shared_ptr<AbstractGeometry<T>>);

  // Get the (x, y)^th cell. `x` and `y` may be _any_ integer. The
  // geometry must be set prior to calling `geometricCell`.
  const T& geometricCell(int x, int y) const;

  // Fill all space with `t`.
  void fill(const T& t);

  // Fill a subcellular offset by `(x, y)` with data.
  //
  // Each `std::string` entry of `data` specifies the values of one row,
  // each character of each string specifies one cell. The data is
  // translated from character to `T` using `dict`.
  //
  // Note: The strings are not required to have the same length.
  void fill(
      int x,
      int y,
      const std::unordered_map<std::string, T>& dict,
      const std::vector<std::string>& data
    );

private:
  std::vector<std::vector<T>> space_{};
  std::shared_ptr<AbstractGeometry<T>> geometry_{};
};

} // namespace drautomaton

#include "Space.tpp"

#endif /* DRAUTOMATON_SRC_SPACE_H */
