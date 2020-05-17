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

#include "Cellular.h"

namespace drautomaton {

template<typename Rule>
Model<Rule>::Model(std::shared_ptr<ICellular<typename Rule::State>> cellular)
:
  cellular_{std::move(cellular)},
  vertices_(cellular_->space().width() * cellular_->space().height()),
  viewport_{0, 0, cellular_->space().width(), cellular_->space().height()}
{
  QObject::connect(
      cellular_.get(), &CellularQObject::updated,
      this, &IModel::onCellularUpdated
    );

  updateVertices();
}

template<typename Rule>
Model<Rule>::Model(int width, int height)
:
  Model{std::make_shared<Cellular<Rule>>(width, height)}
{}

template<typename Rule>
void
Model<Rule>::doUpdate()
{
  cellular_->doUpdate();
}

template<typename Rule>
void
Model<Rule>::onCellularUpdated()
{
  updateVertices();
  emit IModel::updated();
}

template<typename Rule>
void
Model<Rule>::setViewport(int x, int y, int width, int height)
{
  if (x < 0 or y < 0)
  {
    throw std::runtime_error{"Invalid model viewport coordinates"};
  }
  if (width < 1 or height < 1)
  {
    throw std::runtime_error{"Invalid model viewport size"};
  }
  if (cellular_->space().width() < x + width or cellular_->space().height() < y + height)
  {
    throw std::runtime_error{"Model viewport out of bounds"};
  }

  viewport_ = {x, y, width, height};
  vertices_.resize(viewport_.width() * viewport_.height());

  emit viewportChanged();
  updateVertices();
}

template<typename Rule>
void
Model<Rule>::updateVertices()
{
  /* Beware! OpenGL/Vulkan draw row-by-row. Therefore, the vertices must
   * be row-major. For example, if `cellular_`has dimensions 3x4, then the
   * first three elements of `vertices_` must be 
   * 
   * space_.cell(0, 0), 
   * space_.cell(1, 0),
   * space_.cell(2, 0),
   * 
   * and so on... Hence, the outer iteration goes over the y-component
   * of the space.
   *
   * Note that OpenGL also renders from the bottom up. We solve this
   * problem by flipping the y-coordinate in the OpenGL shader.
   * */

  DRPROF_START("Model::updateVertices");
  for (int y = 0; y < viewport_.height(); ++y)
  {
    int offset = y * viewport_.width();
    for (int x = 0; x < viewport_.width(); ++x)
    {
      vertices_[x + offset] = static_cast<int>(cellular_->space().cell(viewport_.x() + x, viewport_.y() + y));
    }
  }
  DRPROF_STOP("Model::updateVertices");
}

template<typename Rule>
void
Model<Rule>::increment(int x, int y)
{
  cellular_->increment(viewport_.x() + x, viewport_.y() + y);
}

template<typename Rule>
const std::vector<int>&
Model<Rule>::vertices() const
{
  return vertices_;
}

template<typename Rule>
int
Model<Rule>::width() const
{
  return viewport_.width();
}

template<typename Rule>
int
Model<Rule>::height() const
{
  return viewport_.height();
}

} // namespace drautomaton
