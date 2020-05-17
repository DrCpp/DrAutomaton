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

#include <QGuiApplication>
#include <QQuickView>
#include <QSignalSpy>

#include <DrMock/Test.h>

#include "mock/ModelMock.h"
#include "View.h"
#include "Cellular.h"
#include "Test.h"

using namespace drautomaton;

DRTEST_DATA(onClicked)
{
  drtest::addColumn<qreal>("x");  // Click position.
  drtest::addColumn<qreal>("y");
  drtest::addColumn<int>("u");  // Expected target cell.
  drtest::addColumn<int>("v");

  drtest::addRow("top left",     0.01, 0.12, 0, 0);
  drtest::addRow("bottom right", 5.67, 7.99, 1, 3);
  drtest::addRow("random",       3.45, 2.34, 1, 1);
}

DRTEST_TEST(onClicked)
{
  DRTEST_FETCH(qreal, x);
  DRTEST_FETCH(qreal, y);
  DRTEST_FETCH(int, u);
  DRTEST_FETCH(int, v);

  // Configure mock component.
  auto model = std::make_shared<ModelMock>();
  int width = 2;
  int height = 4;
  model->mock.width().push()
      .returns(width)
      .persists();
  model->mock.height().push()
      .returns(height)
      .persists();
  model->mock.increment().push().expects(u, v).times(1);

  // Configure SUT.
  View cell_view{};
  cell_view.setWidth(6);
  cell_view.setHeight(8);
  cell_view.setModel(model);

  // Run the test.
  cell_view.onClicked(x, y);
  DRTEST_VERIFY_MOCK(model->mock.increment());
}

DRTEST_DATA(onClickedFailure)
{
  drtest::addColumn<qreal>("x");  // Click position.
  drtest::addColumn<qreal>("y");

  drtest::addRow("x out of bounds",  6.12,  1.23);
  drtest::addRow("x out of bounds", -5.67,  1.23);
  drtest::addRow("y out of bounds",  1.23,  8.00);
  drtest::addRow("y out of bounds",  1.23, -0.12);
}

DRTEST_TEST(onClickedFailure)
{
  DRTEST_FETCH(qreal, x);
  DRTEST_FETCH(qreal, y);

  // Configure mock component.
  auto model = std::make_shared<ModelMock>();
  int width = 2;
  int height = 4;
  model->mock.width().push()
      .returns(width)
      .persists();
  model->mock.height().push()
      .returns(height)
      .persists();

  // model->mock.increment().  // No configuration necessary.

  // Configure SUT.
  View cell_view{};
  cell_view.setWidth(6);
  cell_view.setHeight(8);
  cell_view.setModel(model);

  // Run the test.
  cell_view.onClicked(x, y);
  DRTEST_VERIFY_MOCK(model->mock.increment());
}
