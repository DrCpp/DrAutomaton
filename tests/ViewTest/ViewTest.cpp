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

#include "mock/ModelMock.h"
#include "View.h"

using namespace drautomaton;

int main(int argc, char** argv)
{
  QGuiApplication app{argc, argv};
  qmlRegisterType<View>("DrAutomaton", 1, 0, "CellularAutomaton");

  /* **********************************
   * Create mock model
   * ********************************** */

  // Create and configure mock object.
  int width = 16;
  int height = 12;
  std::vector<int> frame1 = {
      1, 1, 1, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
      1, 1, 1, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
      1, 1, 1, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
      1, 1, 1, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,

      0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
      0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
      0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
      0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,

      0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  3, 3, 3, 3,
      0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  3, 3, 3, 3,
      0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  3, 3, 3, 3,
      0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  3, 3, 3, 3,
    };
  std::vector<int> frame2 = {
      1, 1, 1, 1,  0, 0, 0, 0,  0, 0, 0, 0,  2, 2, 2, 2,
      1, 1, 1, 1,  0, 0, 0, 0,  0, 0, 0, 0,  2, 2, 2, 2,
      1, 1, 1, 1,  0, 0, 0, 0,  0, 0, 0, 0,  2, 2, 2, 2,
      1, 1, 1, 1,  0, 0, 0, 0,  0, 0, 0, 0,  2, 2, 2, 2,

      0, 0, 0, 0,  2, 2, 2, 2,  0, 0, 0, 0,  0, 0, 0, 0,
      0, 0, 0, 0,  2, 2, 2, 2,  0, 0, 0, 0,  0, 0, 0, 0,
      0, 0, 0, 0,  2, 2, 2, 2,  0, 0, 0, 0,  0, 0, 0, 0,
      0, 0, 0, 0,  2, 2, 2, 2,  0, 0, 0, 0,  0, 0, 0, 0,

      0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  3, 3, 3, 3,
      0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  3, 3, 3, 3,
      0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  3, 3, 3, 3,
      0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  3, 3, 3, 3,
    };
  assert(frame1.size() == width * height);
  assert(frame2.size() == width * height);
  auto model = std::make_shared<drautomaton::ModelMock>();
  model->mock.width().state().returns("*", 16);
  model->mock.height().state().returns("*", 12);
  model->mock.vertices().state().returns("", std::move(frame1))
                                .returns("state1", std::move(frame2));
  model->mock.doUpdate().state().emits("*", &IModel::updated);
  model->mock.doUpdate().state().transition("", "state1")
                                .transition("state1", "");

  // auto x = model->vertices()[32];
  // assert(x == 0);
  // model->doUpdate();
  // assert(model->vertices()[32] == 1);

  /* **********************************
   * Configure view
   * ********************************** */

  QQuickView view;

  view.setSource(QUrl{"qrc:/viewtest.qml"});

  View* automaton = static_cast<View*>(view.rootObject());
  assert(automaton);
  automaton->setColor(0,   0,   0,   0);
  automaton->setColor(1, 255,   0,   0);
  automaton->setColor(2,   0, 255,   0);
  automaton->setColor(3,   0,   0, 255);
  automaton->setModel(model);
  // automaton->setFramerate(3);
  automaton->start();
  QMetaObject::invokeMethod(model.get(), "updated", Qt::DirectConnection);

  view.show();

  // Run app for five seconds.
  QTimer::singleShot(1000 * 5, &app, &QCoreApplication::quit);
  auto r = app.exec();
  return r;
}
