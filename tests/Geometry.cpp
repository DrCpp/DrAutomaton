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

#include <DrMock/Test.h>

#include "geometry/Border.h"
#include "geometry/Projective.h"
#include "geometry/Torus.h"
#include "geometry/WrapX.h"
#include "geometry/WrapY.h"
#include "Space.h"

using namespace drautomaton;

DRTEST_DATA(projective)
{
  drtest::addColumn<int>("width");
  drtest::addColumn<int>("height");
  drtest::addColumn<int>("x");  // Coordinate in fundamental domain.
  drtest::addColumn<int>("y");
  drtest::addColumn<int>("u");  // Input coord.
  drtest::addColumn<int>("v");

  drtest::addRow("no wrap", 5, 7, 3, 4, 3, 4);
  drtest::addRow("wrap x",  5, 7, 2, 3, 7, 3);
  drtest::addRow("wrap y",  5, 7, 2, 1, 2, 8);
  drtest::addRow("wrap xy (multiple times)", 5, 7, 4, 1, 19, 19);
}

DRTEST_TEST(projective)
{
  DRTEST_FETCH(int, width);
  DRTEST_FETCH(int, height);
  DRTEST_FETCH(int, x);
  DRTEST_FETCH(int, y);
  DRTEST_FETCH(int, u);
  DRTEST_FETCH(int, v);

  // Configure space before setting geometry.
  Space<int> space(width, height);
  space.fill(0);
  space.cell(x, y) = 1;

  // Set geometry.
  auto geometry = std::make_shared<geometry::Projective<int>>();
  space.setGeometry(std::move(geometry));

  DRTEST_ASSERT_EQ(space.geometricCell(u, v), 1);
}

DRTEST_DATA(wrapY)
{
  drtest::addColumn<int>("width");
  drtest::addColumn<int>("height");
  drtest::addColumn<int>("x");  // Coordinate in fundamental domain.
  drtest::addColumn<int>("y");
  drtest::addColumn<int>("u");  // Input coord.
  drtest::addColumn<int>("v");

  drtest::addRow("no wrap", 5, 7, 3, 4, 3, 4);
  drtest::addRow("wrap y",  5, 7, 0, 3, 0, 10);
  drtest::addRow("wrap y (multiple times)", 5, 7, 1, 2, 1, -19);
}

DRTEST_TEST(wrapY)
{
  DRTEST_FETCH(int, width);
  DRTEST_FETCH(int, height);
  DRTEST_FETCH(int, x);
  DRTEST_FETCH(int, y);
  DRTEST_FETCH(int, u);
  DRTEST_FETCH(int, v);

  // Configure space before setting geometry.
  Space<int> space(width, height);
  space.fill(0);
  space.cell(x, y) = 1;

  // Set geometry.
  auto geometry = std::make_shared<geometry::WrapY<int>>();
  geometry->setDefault(2);
  space.setGeometry(std::move(geometry));

  DRTEST_ASSERT_EQ(space.geometricCell(u, v), 1);
}

DRTEST_DATA(wrapYDefault)
{
  drtest::addColumn<int>("width");
  drtest::addColumn<int>("height");
  drtest::addColumn<int>("u");  // Input coord.
  drtest::addColumn<int>("v");

  drtest::addRow("x too large", 5, 7,  6,  4);
  drtest::addRow("x too small", 5, 7, -2, 19);
}

DRTEST_TEST(wrapYDefault)
{
  DRTEST_FETCH(int, width);
  DRTEST_FETCH(int, height);
  DRTEST_FETCH(int, u);
  DRTEST_FETCH(int, v);

  // Configure space before setting geometry.
  Space<int> space(width, height);
  space.fill(0);

  // Set geometry.
  auto geometry = std::make_shared<geometry::WrapY<int>>();
  geometry->setDefault(1);
  space.setGeometry(std::move(geometry));

  DRTEST_ASSERT_EQ(space.geometricCell(u, v), 1);
}

DRTEST_DATA(wrapX)
{
  drtest::addColumn<int>("width");
  drtest::addColumn<int>("height");
  drtest::addColumn<int>("x");  // Coordinate in fundamental domain.
  drtest::addColumn<int>("y");
  drtest::addColumn<int>("u");  // Input coord.
  drtest::addColumn<int>("v");

  drtest::addRow("no wrap", 5, 7, 3, 4, 3, 4);
  drtest::addRow("wrap x",  5, 7, 0, 3, 5, 3);
  drtest::addRow("wrap x (multiple times)", 5, 7, 1, 2, 21, 2);
}

DRTEST_TEST(wrapX)
{
  DRTEST_FETCH(int, width);
  DRTEST_FETCH(int, height);
  DRTEST_FETCH(int, x);
  DRTEST_FETCH(int, y);
  DRTEST_FETCH(int, u);
  DRTEST_FETCH(int, v);

  // Configure space before setting geometry.
  Space<int> space(width, height);
  space.fill(0);
  space.cell(x, y) = 1;

  // Set geometry.
  auto geometry = std::make_shared<geometry::WrapX<int>>();
  geometry->setDefault(2);
  space.setGeometry(std::move(geometry));

  DRTEST_ASSERT_EQ(space.geometricCell(u, v), 1);
}

DRTEST_DATA(wrapXDefault)
{
  drtest::addColumn<int>("width");
  drtest::addColumn<int>("height");
  drtest::addColumn<int>("u");  // Input coord.
  drtest::addColumn<int>("v");

  drtest::addRow("y too large", 5, 7, 1,   9);
  drtest::addRow("y too small", 5, 7, 1, -37);
}

DRTEST_TEST(wrapXDefault)
{
  DRTEST_FETCH(int, width);
  DRTEST_FETCH(int, height);
  DRTEST_FETCH(int, u);
  DRTEST_FETCH(int, v);

  // Configure space before setting geometry.
  Space<int> space(width, height);
  space.fill(0);

  // Set geometry.
  auto geometry = std::make_shared<geometry::WrapX<int>>();
  geometry->setDefault(1);
  space.setGeometry(std::move(geometry));

  DRTEST_ASSERT_EQ(space.geometricCell(u, v), 1);
}

DRTEST_DATA(torus)
{
  drtest::addColumn<int>("width");
  drtest::addColumn<int>("height");
  drtest::addColumn<int>("x");  // Coordinate in fundamental domain.
  drtest::addColumn<int>("y");
  drtest::addColumn<int>("u");  // Input coord.
  drtest::addColumn<int>("v");

  drtest::addRow("no wrap", 5, 7, 3, 4, 3, 4);
  drtest::addRow("wrap x",  5, 7, 0, 3, 5, 3);
  drtest::addRow("wrap y",  5, 7, 1, 2, 1, 9);
  drtest::addRow("wrap x (multiple times)", 5, 7, 1, 2, 21, 2);
  drtest::addRow("wrap y (multiple times)", 5, 7, 4, 5,  4, 19);
}

DRTEST_TEST(torus)
{
  DRTEST_FETCH(int, width);
  DRTEST_FETCH(int, height);
  DRTEST_FETCH(int, x);
  DRTEST_FETCH(int, y);
  DRTEST_FETCH(int, u);
  DRTEST_FETCH(int, v);

  // Configure space before setting geometry.
  Space<int> space(width, height);
  space.fill(0);
  space.cell(x, y) = 1;

  // Set geometry.
  auto geometry = std::make_shared<geometry::Torus<int>>();
  space.setGeometry(std::move(geometry));

  DRTEST_ASSERT_EQ(space.geometricCell(u, v), 1);
}

DRTEST_DATA(borderDefault)
{
  drtest::addColumn<int>("width");
  drtest::addColumn<int>("height");
  drtest::addColumn<int>("u");  // Input coord.
  drtest::addColumn<int>("v");

  drtest::addRow("outside x", 5, 7, 5, 3);
  drtest::addRow("outside y", 5, 7, 1, 9);
}

DRTEST_TEST(borderDefault)
{
  DRTEST_FETCH(int, width);
  DRTEST_FETCH(int, height);
  DRTEST_FETCH(int, u);
  DRTEST_FETCH(int, v);

  // Configure space before setting geometry.
  Space<int> space(width, height);
  space.fill(0);

  // Set geometry.
  auto geometry = std::make_shared<geometry::Border<int>>();
  geometry->setDefault(1);
  space.setGeometry(std::move(geometry));

  DRTEST_ASSERT_EQ(space.geometricCell(u, v), 1);
}
