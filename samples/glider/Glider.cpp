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

#include <DrAutomaton/DrAutomaton.h>

using namespace drautomaton;

int main(int argc, char** argv)
{
  QGuiApplication app{argc, argv};
  qmlRegisterType<View>("DrAutomaton", 0, 0, "CellularView");

  /* **********************************
   * Create and populate model/cellular
   * ********************************** */

  auto cellular = std::make_shared<Cellular<GameOfLife>>(70, 70);
  cellular->space().fill(
      1, 1,
      {{".", GameOfLife::State::dead},
       {"O", GameOfLife::State::live}},
      // Gosper's glider gun, created by Bill Gosper in 1970.
      {".......................O",
       ".....................O.O",
       "............O.......O.O...........OO",
       "...........OO......O..O...........OO",
       "OO........OO....OO..O.O",
       "OO.......OOO....OO...O.O",
       "..........OO....OO.....O",
       "...........OO",
       "............O"}
    );

  // Geometry.
  auto geometry = std::make_shared<geometry::Border<GameOfLife::State>>();
  geometry->setDefault(GameOfLife::State::dead);
  cellular->setGeometry(std::move(geometry));

  auto model = std::make_shared<Model<GameOfLife>>(std::move(cellular));
  model->setViewport(0, 0, 52, 39);

  /* **********************************
   * Configure QQuickView
   * ********************************** */

  QQuickView view;
  view.setSource(QUrl{"qrc:/glider.qml"});

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

  // Run the app.
  view.show();
  return app.exec();
}
