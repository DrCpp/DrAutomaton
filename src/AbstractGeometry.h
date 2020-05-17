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

#ifndef DRAUTOMATON_SRC_ABSTRACTGEOMETRY_H
#define DRAUTOMATON_SRC_ABSTRACTGEOMETRY_H

#include <vector>

namespace drautomaton {

/* AbstractGeometry
 
Abstract interface for plane geometries obtained by glueing a rectangle along its sides. Every geometry (torus, projective plane, etc.) requires a seperate implementation of this interface.
*/
template<typename T>
class AbstractGeometry
{
public:
  virtual ~AbstractGeometry() = default;

  // Return `data[u][v]`, where `(u, v)` are the coordinates of the
  // representative of `(x, y)` in the fundamental domain of the
  // implemented geometry.
  //
  // The parameters `width` and `height` specify the width and height of
  // the glued rectangle.
  virtual const T& cell(
      int x,
      int y,
      int width,
      int height,
      const std::vector<std::vector<T>>& data
    ) const = 0;
};

} // namespace drautomaton

#endif /* DRAUTOMATON_SRC_ABSTRACTGEOMETRY_H */
