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

#include <DrAutomaton/DrAutomaton.h>

using namespace drautomaton;

// Change this to change the number of states.
constexpr int N = 26;

int main(int argc, char** argv)
{
  QGuiApplication app{argc, argv};
  qmlRegisterType<View>("DrAutomaton", 0, 0, "CellularView");

  /* **********************************
   * Create and populate model/cellular
   * ********************************** */

  auto cellular = std::make_shared<Cellular<Cyclic<N>>>(400, 400);

  // Generate random configuration.
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<> dis{0, N - 1};
  for (int x = 0; x < cellular->space().width(); ++x)
  {
    for (int y = 0; y < cellular->space().height(); ++y)
    {
      cellular->space().cell(x, y).value = dis(gen);
    }
  }

  // Geometry.
  auto geometry = std::make_shared<geometry::Torus<Cyclic<N>::State>>();
  cellular->setGeometry(std::move(geometry));

  auto model = std::make_shared<Model<Cyclic<N>>>(std::move(cellular));
  // (No viewport configuration required.)

  /* **********************************
   * Configure QQuickView
   * ********************************** */

  QQuickView view;
  view.setSource(QUrl{"qrc:/cyclic.qml"});

  // Disable resizing.
  QSize size{view.width(), view.height()};
  view.setMinimumSize(size);
  view.setMaximumSize(size);

  /* **********************************
   * Configure drautomaton::View
   * ********************************** */

  auto automaton_view = static_cast<View*>(view.rootObject());

  // Compute colors.
  for (int i = 0; i < N; ++i)
  {
    QColor color;
    color.setHsvF(static_cast<float>(i) / N, 1.0, 1.0);
    automaton_view->setColor(i, color.red(), color.green(), color.blue());
  }
  automaton_view->setModel(std::move(model));

  // Run the app.
  view.show();
  return app.exec();
}
