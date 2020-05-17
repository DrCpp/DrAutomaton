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

#define DRTEST_USE_QT
#include <DrMock/Test.h>

#include "Space.h"

using namespace drautomaton;

DRTEST_TEST(zeroWidthOrHeight)
{
  // Check that an error is thrown on zero width or height.
  DRTEST_ASSERT_THROW(Space<float> space(0, 33), std::runtime_error);
  DRTEST_ASSERT_THROW(Space<float> space(34, 0), std::runtime_error);
}

DRTEST_TEST(fillAll)
{
  Space<int> space(5, 6);
  space.fill(9);

  for (int x = 0; x < space.width(); ++x)
  {
    for (int y = 0; y < space.height(); ++y)
    {
      DRTEST_ASSERT_EQ(space.cell(x, y), 9);
    }
  }
}

DRTEST_TEST(fillByMap)
{
  Space<int> space(7, 7);
  space.fill(
      2, 3,
      {{".", 1}, {"O", 2}},  // dict
      {"....O",              // data
       "O",
       "..O",
       ".O.O."}
    );

  DRTEST_ASSERT_EQ(space.cell(0, 0), 0);
  DRTEST_ASSERT_EQ(space.cell(1, 0), 0);
  DRTEST_ASSERT_EQ(space.cell(2, 0), 0);
  DRTEST_ASSERT_EQ(space.cell(3, 0), 0);
  DRTEST_ASSERT_EQ(space.cell(4, 0), 0);
  DRTEST_ASSERT_EQ(space.cell(5, 0), 0);
  DRTEST_ASSERT_EQ(space.cell(6, 0), 0);

  DRTEST_ASSERT_EQ(space.cell(0, 1), 0);
  DRTEST_ASSERT_EQ(space.cell(1, 1), 0);
  DRTEST_ASSERT_EQ(space.cell(2, 1), 0);
  DRTEST_ASSERT_EQ(space.cell(3, 1), 0);
  DRTEST_ASSERT_EQ(space.cell(4, 1), 0);
  DRTEST_ASSERT_EQ(space.cell(5, 1), 0);
  DRTEST_ASSERT_EQ(space.cell(6, 1), 0);

  DRTEST_ASSERT_EQ(space.cell(0, 2), 0);
  DRTEST_ASSERT_EQ(space.cell(1, 2), 0);
  DRTEST_ASSERT_EQ(space.cell(2, 2), 0);
  DRTEST_ASSERT_EQ(space.cell(3, 2), 0);
  DRTEST_ASSERT_EQ(space.cell(4, 2), 0);
  DRTEST_ASSERT_EQ(space.cell(5, 2), 0);
  DRTEST_ASSERT_EQ(space.cell(6, 2), 0);

  DRTEST_ASSERT_EQ(space.cell(0, 3), 0);
  DRTEST_ASSERT_EQ(space.cell(1, 3), 0);
  DRTEST_ASSERT_EQ(space.cell(2, 3), 1);
  DRTEST_ASSERT_EQ(space.cell(3, 3), 1);
  DRTEST_ASSERT_EQ(space.cell(4, 3), 1);
  DRTEST_ASSERT_EQ(space.cell(5, 3), 1);
  DRTEST_ASSERT_EQ(space.cell(6, 3), 2);

  DRTEST_ASSERT_EQ(space.cell(0, 4), 0);
  DRTEST_ASSERT_EQ(space.cell(1, 4), 0);
  DRTEST_ASSERT_EQ(space.cell(2, 4), 2);
  DRTEST_ASSERT_EQ(space.cell(3, 4), 0);
  DRTEST_ASSERT_EQ(space.cell(4, 4), 0);
  DRTEST_ASSERT_EQ(space.cell(5, 4), 0);
  DRTEST_ASSERT_EQ(space.cell(6, 4), 0);

  DRTEST_ASSERT_EQ(space.cell(0, 5), 0);
  DRTEST_ASSERT_EQ(space.cell(1, 5), 0);
  DRTEST_ASSERT_EQ(space.cell(2, 5), 1);
  DRTEST_ASSERT_EQ(space.cell(3, 5), 1);
  DRTEST_ASSERT_EQ(space.cell(4, 5), 2);
  DRTEST_ASSERT_EQ(space.cell(5, 5), 0);
  DRTEST_ASSERT_EQ(space.cell(6, 5), 0);

  DRTEST_ASSERT_EQ(space.cell(0, 6), 0);
  DRTEST_ASSERT_EQ(space.cell(1, 6), 0);
  DRTEST_ASSERT_EQ(space.cell(2, 6), 1);
  DRTEST_ASSERT_EQ(space.cell(3, 6), 2);
  DRTEST_ASSERT_EQ(space.cell(4, 6), 1);
  DRTEST_ASSERT_EQ(space.cell(5, 6), 2);
  DRTEST_ASSERT_EQ(space.cell(6, 6), 1);
}
