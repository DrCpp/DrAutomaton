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

#ifndef DRAUTOMATON_SRC_IMODEL_H
#define DRAUTOMATON_SRC_IMODEL_H

#include <vector>
#include <QObject>

namespace drautomaton {

/* IModel

Qt model interface of `Cellular` class.

The model provides access to a _vertex container_, which represents the
states of a selection of the CA's states and may be obtained using
`vertices()`.  The selection, or _viewport_, is a rectangular subspace
of the CA's underlying space and set using the `setViewport` method.
The CA's width and height are the width and heigh of the viewport.  In
particular, the width and height of the model may differ from the size
and height of the CA's underlying space.

The size of the vertex container is `width() * height()`, and its values
represent the states of the cells held in the viewport line-by-line,
top-to-bottom.  The values are obtained by `static_cast`ing the cell's
states.  The vertex container is updated every time the CA emits
`CellularQObject::updated`.

The `Cellular` object should be inserted into the model via a ctor.
*/

class IModel : public QObject
{
  Q_OBJECT

public:
  virtual ~IModel() = default;

  // Return the current vertices, a vector of size `width() * height()`.
  // The vertices are organized row-major. The top-left vertex is
  // vertices()[0].
  virtual const std::vector<int>& vertices() const = 0;
  virtual int width() const = 0;
  virtual int height() const = 0;

public slots:
  // Compute the CA's next generation.
  virtual void doUpdate() = 0;

  // Handle CA's update signal.
  virtual void onCellularUpdated() = 0;

  // Set the viewport to a rectangle with top left corner at `(x, y)`
  // (in cell coords) and width and height as specified.
  virtual void setViewport(int x, int y, int width, int height) = 0;

  // Increment the CA's cell at `(x, y)`.
  virtual void increment(int x, int y) = 0;

signals:
  // Emit when the vertices are updated.
  void updated();

  // Emit when the viewport is changed.
  void viewportChanged();
};

} // namespace drautomaton

#endif /* DRAUTOMATON_SRC_IMODEL_H */
