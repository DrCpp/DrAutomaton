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

#define DRAUTO_PROFILING
#include <DrAutomaton/DrAutomaton.h>

using namespace drautomaton;

int main(int argc, char** argv)
{
  QGuiApplication app{argc, argv};
  qmlRegisterType<View>("DrAutomaton", 0, 0, "CellularView");

  /* **********************************
   * Create and populate model/cellular
   * ********************************** */

  auto cellular = std::make_shared<Cellular<Brain>>(400, 300);
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<> dis{0, 2};
  auto xlo = cellular->space().width() / 2 - 20;
  auto xhi = cellular->space().width() / 2 + 20;
  auto ylo = cellular->space().height() / 2 - 20;
  auto yhi = cellular->space().height() / 2 + 20;
  for (int x = 0; x < cellular->space().width(); ++x)
  {
    for (int y = 0; y < cellular->space().height(); ++y)
    {
      if (xlo <= x and x < xhi and ylo <= y and y < yhi)
      {
        cellular->space().cell(x, y) = static_cast<Brain::State>(dis(gen));
      }
      else
      {
        cellular->space().cell(x, y) = Brain::State::off;
      }
    }
  }

  // Geometry & model.
  auto geometry = std::make_shared<geometry::Torus<Brain::State>>();
  cellular->setGeometry(std::move(geometry));
  auto model = std::make_shared<Model<Brain>>(std::move(cellular));

  /* **********************************
   * Configure QQuickView
   * ********************************** */

  QQuickView view;
  view.setSource(QUrl{"qrc:/brain.qml"});

  // Disable resizing.
  QSize size{view.width(), view.height()};
  view.setMinimumSize(size);
  view.setMaximumSize(size);

  /* **********************************
   * Configure drautomaton::View
   * ********************************** */

  auto automaton_view = view.rootObject()->findChild<View*>("view");
  assert(automaton_view);
  automaton_view->setModel(std::move(model));
  automaton_view->setColor(0,   0,   0,   0);
  automaton_view->setColor(1,  77,   5, 232);
  automaton_view->setColor(2, 255, 255, 255);
  automaton_view->setFramerate(20);
  automaton_view->start();

  // Run the app.
  view.show();
  app.exec();

  // Print profiling results.
  DRPROF_PRINT_ALL();
}

