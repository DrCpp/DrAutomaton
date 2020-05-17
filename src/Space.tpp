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

#include <cassert>

namespace drautomaton {

template<typename T>
Space<T>::Space(int width, int height)
:
  space_(width)
{
  if (width < 1 or height < 1)
  {
    throw std::runtime_error{"invalid Space dimensions"};
  }

  for (int x = 0; x < width; ++x)
  {
    space_[x].resize(height);
  }
}

template<typename T>
int
Space<T>::width() const
{
  return space_.size();
}

template<typename T>
int
Space<T>::height() const
{
  return space_[0].size();
}

template<typename T>
void
Space<T>::setGeometry(std::shared_ptr<AbstractGeometry<T>> geometry)
{
  geometry_ = std::move(geometry);
}

template<typename T>
T&
Space<T>::cell(int x, int y)
{
  return space_[x][y];
}

template<typename T>
const T&
Space<T>::cell(int x, int y) const
{
  return space_[x][y];
}

template<typename T>
const T&
Space<T>::geometricCell(int x, int y) const
{
  assert(geometry_);
  return geometry_->cell(x, y, width(), height(), space_);
}

template<typename T>
std::vector<T>*
Space<T>::data()
{
  return space_.data();
}

template<typename T>
const std::vector<T>*
Space<T>::data() const
{
  return space_.data();
}

template<typename T>
void
Space<T>::fill(const T& t)
{
  for (int x = 0; x < width(); ++x)
  {
    for (int y = 0; y < height(); ++y)
    {
      space_[x][y] = t;
    }
  }
}

template<typename T>
void
Space<T>::fill(
    int x,
    int y,
    const std::unordered_map<std::string, T>& dict,
    const std::vector<std::string>& data
  )
{
  for (std::size_t v = 0; v < data.size(); ++v)
  {
    auto line = data[v];
    for (std::size_t u = 0; u < line.size(); ++u)
    {
      std::string key{line[u]};
      space_[x + u][y + v] = dict.at(key);
    }
  }
}

} // namespace drautomaton
