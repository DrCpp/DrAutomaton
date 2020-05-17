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

#include <random>

#include <QGuiApplication>
#include <QQuickView>
#include <DrMock/Test.h>

#define DRAUTO_PROFILING
#include "View.h"
#include "Model.h"
#include "rules/GameOfLife.h"
#include "geometry/Torus.h"
#include "geometry/Border.h"

using namespace drautomaton;

DRTEST_TEST(droppedFrames)
{
  int argc = 0;
  QGuiApplication app{argc, nullptr};
  qmlRegisterType<View>("DrAutomaton", 1, 0, "Automaton");

  /* **********************************
   * Create and populate model/cellular
   * ********************************** */

  auto cellular = std::make_shared<Cellular<GameOfLife>>(1024, 768);
  auto geometry = std::make_shared<geometry::Torus<GameOfLife::State>>();
  // geometry->setDefault(GameOfLife::State::dead);
  cellular->setGeometry(geometry);

  // Random dead/live population.
  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<> dis(0, 1);
  for (int x = 0; x < cellular->space().width(); ++x)
  {
    for (int y = 0; y < cellular->space().height(); ++y)
    {
      cellular->space().cell(x, y) = static_cast<GameOfLife::State>(dis(gen));
    }
  }

  auto model = std::make_shared<Model<GameOfLife>>(std::move(cellular));

  /* **********************************
   * Configure view
   * ********************************** */

  QQuickView view;

  view.setSource(QUrl{"qrc:/profiling.qml"});

  // Configure colors.
  View* automaton = static_cast<View*>(view.rootObject());
  assert(automaton);

  // Setup Model <-> View connection.
  automaton->setModel(model);
  view.show();
  automaton->start();

  // Run app for five seconds.
  QTimer::singleShot(1000 * 10, &app, &QCoreApplication::quit);
  app.exec();
  DRPROF_PRINT_ALL();

  // Test for dropped frames.
  int doUpdate_count = drprof::getPasses("Cellular::doUpdate");
  int updateVertices_count = drprof::getPasses("Model::updateVertices");
  auto diff = std::abs(doUpdate_count - updateVertices_count);
  DRTEST_ASSERT_LT(diff, 2);
}
