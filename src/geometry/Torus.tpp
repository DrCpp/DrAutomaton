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
Torus<T>::cell(
    int x,
    int y,
    int width,
    int height,
    const std::vector<std::vector<T>>& data
  ) const
{
  int u = x;
  int v = y;

  // Prevent slow modulo computation if possible.
  if (x < 0 or x >= width)
  {
    u = detail::mod(x, width);
  }
  if (y < 0 or y >= height)
  {
    v = detail::mod(y, height);
  }
  return data[u][v];
}

}} // namespace drautomaton::geometry
