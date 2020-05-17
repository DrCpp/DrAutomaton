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

import QtQuick 2.0
import DrAutomaton 0.0

Item
{
  id: root
  width: 800
  height: 600

  // Key mapping.
  focus: true
  Keys.onPressed:
  {
    switch(event.key)
    {
      case Qt.Key_1: { view.setFramerate( 3); break; }
      case Qt.Key_2: { view.setFramerate( 8); break; }
      case Qt.Key_3: { view.setFramerate(20); break; }
      case Qt.Key_4: { view.setFramerate(60); break; }
      case Qt.Key_Space: { view.toggle(); break; }
      case Qt.Key_Return: { view.showNextGeneration(); break; }
    }
  }

  // Forward mouse events.
  MouseArea
  {
    anchors.fill: parent
    acceptedButtons: Qt.LeftButton

    onPressed:
    {
      view.onClicked(mouse.x, mouse.y)
      mouse.accepted = true
    }
    onPositionChanged:
    {
      view.onClicked(mouse.x, mouse.y)
      mouse.accepted = true
    }
  }

  CellularView
  {
    id: view
    objectName: "view"

    anchors.fill: parent
    anchors.margins: 0
  }
}
