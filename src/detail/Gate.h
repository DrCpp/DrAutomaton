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

#ifndef DRAUTOMATON_SRC_DETAIL_GATE_H
#define DRAUTOMATON_SRC_DETAIL_GATE_H

#include <QObject>

#define DRAUTO_PROFILING

namespace drautomaton {

/* Gate

AND Gate object that sends a singal once both input slots are signaled.
*/

class Gate : public QObject
{
  Q_OBJECT

public slots:
  // Input slots.
  void lhs();
  void rhs();

signals:
  void ready();

private:
  void emitIfReady();

  bool lhs_;
  bool rhs_;
};

} // namespace drautomaton

#endif /* DRAUTOMATON_SRC_DETAIL_GATE_H */
