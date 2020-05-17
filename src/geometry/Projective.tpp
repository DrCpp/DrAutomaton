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

#include "../detail/Utility.h"

namespace drautomaton { namespace geometry {

template<typename T>
const T&
Projective<T>::cell(
    int x,
    int y,
    int width,
    int height,
    const std::vector<std::vector<T>>& data
  ) const
{
  int s = std::abs(x / width);
  int t = std::abs(y / height);

  // If coords are within bounds, return normally.
  if (s == 0 and t == 0)
  {
    return data[x][y];
  }

  // Wrap the coordinates.
  x = detail::mod(x, width);
  y = detail::mod(y, height);

  // Reverse x coord `t` times, and y coord `s` times.
  if (t % 2 != 0)
  {
    x = width - (x + 1);
  }
  if (s % 2 != 0)
  {
    y = height - (y + 1);
  }

  return data[x][y];
}

}} // namespace drautomaton::geometry
