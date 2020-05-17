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

#ifndef DRAUTOMATON_SRC_GEOMETRY_BORDER_H
#define DRAUTOMATON_SRC_GEOMETRY_BORDER_H

#include "../AbstractGeometry.h"

namespace drautomaton { namespace geometry {

/* Border

AbstractGeometry that returns a reference to a default value when
out-of-bounds coords are accessed.
*/

template<typename T>
class Border : public AbstractGeometry<T>
{
public:
  const T& cell(
      int x,
      int y,
      int width,
      int height,
      const std::vector<std::vector<T>>& data
    ) const override;

  void setDefault(T);

private:
  T default_{};
};

}} // namespace drautomaton::geometry

#include "Border.tpp"

#endif /* DRAUTOMATON_SRC_GEOMETRY_BORDER_H */
