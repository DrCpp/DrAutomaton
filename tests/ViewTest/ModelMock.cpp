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

#include "ModelMock.h"

namespace drautomaton { namespace mock {

ModelMock::ModelMock()
:
  vertices_(width_ * height_)
{
  // First line.
  vertices_[0] = 1;
  vertices_[1] = 2;
  vertices_[2] = 3;

  // Last line.
  auto end = width_ * height_;
  vertices_[end - 3] = 1;
  vertices_[end - 2] = 2;
  vertices_[end - 1] = 3;

  // Second line.
  vertices_[width_ + 0] = 1;
  vertices_[width_ + 1] = 2;
  vertices_[width_ + 2] = 3;
}

const std::vector<int>&
ModelMock::vertices() const
{
  return vertices_;
}

int
ModelMock::width() const
{
  return width_;
}

int
ModelMock::height() const
{
  return height_;
}

void
ModelMock::doUpdate()
{
  // Flash some pixels on the third line.
  auto probe = vertices_[2 * width_ + 0];
  if (probe == 0)
  {
    vertices_[2 * width_ + 0] = 1;
    vertices_[2 * width_ + 1] = 2;
    vertices_[2 * width_ + 2] = 3;
  }
  else
  {
    vertices_[2 * width_ + 0] = 0;
    vertices_[2 * width_ + 1] = 0;
    vertices_[2 * width_ + 2] = 0;
  }

  // We're immediately done, no Cellular to update!
  emit IModel::updated();
}

void
ModelMock::onCellularUpdated()
{
  // Nothing.
}

void
ModelMock::setViewport(int x, int y, int width, int height)
{
  viewport_ = {x, y, width, height};
}

void
ModelMock::increment(int, int)
{
  // Not implemented.
}

}} // namespace drautomaton::mock
