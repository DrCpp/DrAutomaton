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

#include <QSignalSpy>

#define DRTEST_USE_QT
#include <DrMock/Test.h>

#include "mock/CellularMock.h"
#include "Model.h"
#include "Test.h"

using namespace drautomaton;

DRTEST_TEST(updateVertices)
{
  // Setup first generation (for const getter).
  auto cellular = std::make_shared<CellularMock<Test::State>>();
  Space<Test::State> space{5, 3};
  space.cell(0, 0) = Test::State::dead;  // Beware! Order differs from that in Cellular.cpp.
  space.cell(0, 1) = Test::State::dead;
  space.cell(0, 2) = Test::State::dead;
  space.cell(1, 0) = Test::State::live;
  space.cell(1, 1) = Test::State::live;
  space.cell(1, 2) = Test::State::live;
  space.cell(2, 0) = Test::State::dead;
  space.cell(2, 1) = Test::State::dead;
  space.cell(2, 2) = Test::State::dead;
  space.cell(3, 0) = Test::State::live;
  space.cell(3, 1) = Test::State::live;
  space.cell(3, 2) = Test::State::live;
  space.cell(4, 0) = Test::State::dead;
  space.cell(4, 1) = Test::State::dead;
  space.cell(4, 2) = Test::State::dead;
  cellular->mock.space<drmock::Const>().push().returns(space).persists();
  cellular->mock.space<>().push().returns(space).persists();

  // Create SUT. Note: During construction, `updateVertices` is called
  // for the first time. Thus, it is important to construct the
  // QSignalSpy only later, in order to not count the update run during
  // the ctor.
  auto model = std::make_shared<Model<Test>>(cellular);
  model->setViewport(2, 0, 2, 3);

  // Setup signal spy so that we may check that the `updated` signal is
  // emitted when calling `updateVertices`.
  QSignalSpy updated{model.get(), &IModel::updated};

  // Forcefully emit signal from cellular to invoke updateVertices.
  emit cellular->updated();

  // Check that `updated` is emitted within good time.
  if (updated.size() == 0)
  {
    updated.wait(100);  // 100ms.
  }
  DRTEST_ASSERT_EQ(updated.size(), 1);
  updated.clear();

  // Check that all vertices are correctly computed. In particular, make
  // sure that the output is row-major. 
  std::vector<int> expected = {0, 1, 0, 1, 0, 1};
  DRTEST_ASSERT_EQ(model->vertices(), expected);
}

DRTEST_DATA(viewportFailure)
{
  drtest::addColumn<int>("x");
  drtest::addColumn<int>("y");
  drtest::addColumn<int>("width");
  drtest::addColumn<int>("height");

  drtest::addRow("x out of bounds", 2, 1, 3, 1);  // Out of bounds.
  drtest::addRow("y out of bounds", 1, 1, 2, 5);
  drtest::addRow("xoffset < 0", -1,  1, 2, 1);  // Negative offset.
  drtest::addRow("yoffset < 0",  0, -2, 2, 3);
  drtest::addRow("width < 1" , 1, 1, 0, 1);  // Non-positive width/height.
  drtest::addRow("height < 1", 1, 0, 2, 0);
}

DRTEST_TEST(viewportFailure)
{
  DRTEST_FETCH(int, x);
  DRTEST_FETCH(int, y);
  DRTEST_FETCH(int, width);
  DRTEST_FETCH(int, height);

  auto cellular = std::make_shared<CellularMock<Test::State>>();
  Space<Test::State> space{4, 3};
  cellular->mock.space<drmock::Const>().push().returns(space).persists();
  cellular->mock.space<>().push().returns(space).persists();
  auto model = std::make_shared<Model<Test>>(cellular);

  DRTEST_ASSERT_THROW(model->setViewport(x, y, width, height), std::runtime_error);
}

DRTEST_TEST(doUpdate)
{
  // Configure first generation (only required so potential calls to
  // cellular->space() made by the SUT don't cause an exception).
  auto cellular = std::make_shared<CellularMock<Test::State>>();
  Space<Test::State> space{1, 1};
  space.cell(0, 0) = Test::State::dead;
  cellular->mock.space().push().returns(space).persists();

  // Expect cellular->doUpdate to be called exactly once.
  cellular->mock.doUpdate().push().expects().times(1);

  // Create SUT and run the test.
  auto model = std::make_shared<Model<Test>>(cellular);
  model->doUpdate();
  DRTEST_VERIFY_MOCK(cellular->mock);
}

DRTEST_TEST(increment)
{
  // Fill space.
  Space<Test::State> space(5, 6);
  for (int x = 0; x < space.width(); ++x)
  {
    for (int y = 0; y < space.height(); ++y)
    {
      space.cell(x, y) = Test::State::dead;
    }
  }

  // Configure cellular.
  auto cellular = std::make_shared<CellularMock<Test::State>>();
  cellular->mock.space().push().returns(space).persists();
  cellular->mock.increment().push().expects(2, 4).times(1);

  // Configure model.
  auto model = std::make_shared<Model<Test>>(cellular);
  model->setViewport(1, 2, 3, 4);

  // Run test.
  model->increment(1, 2);
  DRTEST_VERIFY_MOCK(cellular->mock);
}
