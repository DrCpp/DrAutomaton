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

#include "ModelMock.h"
#include "View.h"

using namespace drautomaton;

int main(int argc, char** argv)
{
  QGuiApplication app{argc, argv};
  qmlRegisterType<View>("DrAutomaton", 1, 0, "CellularAutomaton");

  /* **********************************
   * Create mock model
   * ********************************** */

  // Create mock object.
  auto model = std::make_shared<drautomaton::mock::ModelMock>();

  /* **********************************
   * Configure view
   * ********************************** */

  QQuickView view;

  view.setSource(QUrl{"qrc:/viewtest.qml"});

  View* automaton = static_cast<View*>(view.rootObject());
  assert(automaton);
  automaton->setModel(model);
  automaton->setColor(0,   0,   0,   0);
  automaton->setColor(1, 255,   0,   0);
  automaton->setColor(2,   0, 255,   0);
  automaton->setColor(3,   0,   0, 255);
  automaton->start();
  view.show();

  // Run app for five seconds.
  QTimer::singleShot(1000 * 5, &app, &QCoreApplication::quit);
  auto r = app.exec();

  return r;
}
