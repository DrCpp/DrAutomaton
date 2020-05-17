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

#include "Cellular.h"
#include "Test.h"

using namespace drautomaton;

DRTEST_TEST(doUpdate)
{
  // Setup first generation.
  auto cellular = std::make_shared<Cellular<Test>>(4, 3);
  cellular->space().cell(0, 0) = Test::State::live;
  cellular->space().cell(0, 1) = Test::State::dead;
  cellular->space().cell(0, 2) = Test::State::live;
  cellular->space().cell(1, 0) = Test::State::dead;
  cellular->space().cell(1, 1) = Test::State::live;
  cellular->space().cell(1, 2) = Test::State::dead;
  cellular->space().cell(2, 0) = Test::State::live;
  cellular->space().cell(2, 1) = Test::State::dead;
  cellular->space().cell(2, 2) = Test::State::live;
  cellular->space().cell(3, 0) = Test::State::dead;
  cellular->space().cell(3, 1) = Test::State::live;
  cellular->space().cell(3, 2) = Test::State::dead;

  // Setup signal spy so that we may check that the `updated` signal is
  // emitted when calling `doUpdate`.
  QSignalSpy updated{cellular.get(), &CellularQObject::updated};

  // Advance to next generation. We do this via QueuedConnection to show
  // off that DRTEST_USE_QT does it's job.
  QMetaObject::invokeMethod(cellular.get(), "doUpdate", Qt::QueuedConnection);

  // Check that `updated` is emitted within good time.
  if (updated.size() == 0)
  {
    updated.wait(100);  // 100ms.
  }
  DRTEST_ASSERT_EQ(updated.size(), 1);

  // Check that all space are correctly transformed.
  for (int i = 0; i < cellular->space().width(); ++i)
  {
    for (int j = 0; j < cellular->space().height(); ++j)
    {
      DRTEST_ASSERT_EQ(
          cellular->space().cell(i, j),
          static_cast<Test::State>((i + j) % 2)
        );
    }
  }
}

DRTEST_TEST(increment)
{
  // Setup first generation.
  auto cellular = std::make_shared<Cellular<Test>>(4, 3);
  cellular->space().cell(0, 0) = Test::State::live;
  cellular->space().cell(0, 1) = Test::State::dead;
  cellular->space().cell(0, 2) = Test::State::live;
  cellular->space().cell(1, 0) = Test::State::dead;
  cellular->space().cell(1, 1) = Test::State::live;
  cellular->space().cell(1, 2) = Test::State::dead;
  cellular->space().cell(2, 0) = Test::State::live;
  cellular->space().cell(2, 1) = Test::State::dead;
  cellular->space().cell(2, 2) = Test::State::live;
  cellular->space().cell(3, 0) = Test::State::dead;
  cellular->space().cell(3, 1) = Test::State::live;
  cellular->space().cell(3, 2) = Test::State::dead;

  cellular->increment(2, 1);
  cellular->increment(3, 0);
  cellular->increment(3, 0);
  cellular->increment(1, 1);
  cellular->increment(1, 1);
  cellular->increment(1, 1);

  DRTEST_ASSERT_EQ(cellular->space().cell(0, 0), Test::State::live);
  DRTEST_ASSERT_EQ(cellular->space().cell(0, 1), Test::State::dead);
  DRTEST_ASSERT_EQ(cellular->space().cell(0, 2), Test::State::live);
  DRTEST_ASSERT_EQ(cellular->space().cell(1, 0), Test::State::dead);
  DRTEST_ASSERT_EQ(cellular->space().cell(1, 1), Test::State::dead);  // x3
  DRTEST_ASSERT_EQ(cellular->space().cell(1, 2), Test::State::dead);
  DRTEST_ASSERT_EQ(cellular->space().cell(2, 0), Test::State::live);
  DRTEST_ASSERT_EQ(cellular->space().cell(2, 1), Test::State::live);  // x1
  DRTEST_ASSERT_EQ(cellular->space().cell(2, 2), Test::State::live);
  DRTEST_ASSERT_EQ(cellular->space().cell(3, 0), Test::State::dead);  // x2
  DRTEST_ASSERT_EQ(cellular->space().cell(3, 1), Test::State::live);
  DRTEST_ASSERT_EQ(cellular->space().cell(3, 2), Test::State::dead);
}
