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

  auto cellular = std::make_shared<Cellular<SRLoop>>(200, 200);
  /* Data found in section 3.4 of
   * 
   * Hiroki Sayama, Constructing evolutionary systems on a simple
   * deterministic cellular automata space (1998), URL:
   * https://pdfs.semanticscholar.org/9662/d07e5550cd82268dedee87d21c5f431865a8.pdf
   * */
  cellular->space().fill(
      95, 95,
      {{"0", SRLoop::State::background},  // black
       {"1", SRLoop::State::core},        // blue
       {"2", SRLoop::State::sheath},      // red
       {"3", SRLoop::State::bonder},      // pink
       {"4", SRLoop::State::guide},       // green
       {"5", SRLoop::State::messenger},   // teal
       {"6", SRLoop::State::umbilical},   // yellow
       {"7", SRLoop::State::gene}},       // white
      {"022222222000000",
       "217014014200000",
       "202222220200000",
       "272000021200000",
       "212000021200000",
       "202000021200000",
       "272000021200000",
       "212222221222220",
       "207107107111112",
       "022222222222220"}
    );

  // Geometry & model.
  auto geometry = std::make_shared<geometry::Border<SRLoop::State>>();
  geometry->setDefault(SRLoop::State::background);
  cellular->setGeometry(std::move(geometry));
  auto model = std::make_shared<Model<SRLoop>>(std::move(cellular));
  model->setViewport(45, 45, 110, 110);

  /* **********************************
   * Configure QQuickView
   * ********************************** */

  QQuickView view;
  view.setSource(QUrl{"qrc:/srloop.qml"});

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

  automaton_view->setColor(0, 0,     0,   0);
  automaton_view->setColor(1, 0,     0, 255);
  automaton_view->setColor(2, 255,   0,   0);
  automaton_view->setColor(3, 255,   0, 255);
  automaton_view->setColor(4, 0,   255,   0);
  automaton_view->setColor(5, 0,   255, 255);
  automaton_view->setColor(6, 255, 255,   0);
  automaton_view->setColor(7, 255, 255, 255);

  automaton_view->setFramerate(15);

  // Run the app.
  view.show();
  return app.exec();
}

