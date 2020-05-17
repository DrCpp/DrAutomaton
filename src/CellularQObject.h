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

#ifndef DRAUTOMATON_SRC_CELLULARQOBJECT_H
#define DRAUTOMATON_SRC_CELLULARQOBJECT_H

#include <QObject>

namespace drautomaton {

/* CellularQObject
 *
 * QObject part of `ICellular`. For detailed documentation, see
 * `ICellular.h`. */

class CellularQObject : public QObject
{
  Q_OBJECT

public:
  virtual ~CellularQObject() = default;

public slots:
  // Compute the next generation of cells.
  virtual void doUpdate() = 0;

  // Increment cell with coords `(x, y)`.
  virtual void increment(int x, int y) = 0;

signals:
  // Emit following after an update of the CA's cell states (`doUpdate`,
  // `increment`, ...).
  void updated();
};


} // namespace drautomaton

#endif /* DRAUTOMATON_SRC_CELLULARQOBJECT_H */
