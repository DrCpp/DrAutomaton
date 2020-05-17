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

#ifndef DRAUTOMATON_SRC_VIEW_H
#define DRAUTOMATON_SRC_VIEW_H

#include <memory>

#include <QQuickItem>
#include <QQuickWindow>
#include <QTimer>

#include "detail/Gate.h"
#include "Color.h"
#include "IModel.h"

/* View

Qt view class of `Cellular` class template.

Before being displayed in a QML secene, an instance of this class must
receive a pointer to an instance of `Model`. Every value present in the
model's vertex container must be mapped to a color. The

{ vertex -> color }

mapping may be configured using `setColor`. Unconfigured vertices will
appear solid black.

Using `setFramerate`, the frequency with which the model is updated may
be specified in Hz. This update tick can be started and stopped using
the `start`, `stop` and `toggle` methods.

*** Implementation details ***

* `timer_` handles the framerate, start/stop/toggle methods.

* Order of execution in the render loop: 

  (1) When `timer_` has timed out and `window()` has rendered the
      previous frame (indicated by the `frameSwapped()` signal), call
      `updateModel()`.

  (2) When `IModel::updated()` is received, run `updatePixels()` to update
      the `pixels_` array. Then run `update()` to transfer the `pixels_`
      array to the texture.
*/

namespace drautomaton {

class View : public QQuickItem
{
  Q_OBJECT

public:
  View();

public slots:
  void setModel(std::shared_ptr<IModel>);

  // Set framerate in Hz.
  Q_INVOKABLE void setFramerate(int fps);

  // Set the color of `vertex` in terms of RGB values or as `QColor`.
  // The `r`, `g`, `b` values must lie in [0, 256).
  Q_INVOKABLE void setColor(int vertex, int r, int g, int b);
  void setColor(int, QColor);

  // Start, stop and toggle on/off.
  Q_INVOKABLE void start();
  Q_INVOKABLE void stop();
  Q_INVOKABLE void toggle();

  // Handle click on the View's surface. 
  //
  // The mouse coordinates are converted to cell coordinates (relative
  // to the model's viewport, then the handler of the model is called
  // with the cell coords as parameters.
  Q_INVOKABLE void onClicked(qreal, qreal);

  // Compute the next generation of cells, even if the CA/view is
  // stopped.
  Q_INVOKABLE void showNextGeneration();

protected:
  QSGNode* updatePaintNode(QSGNode*, UpdatePaintNodeData*) override;

private slots:
  // Grab `QQuickWindow::frameSwapped` from new window.
  void onWindowChanged(QQuickWindow*);

  // Update the private pixel vector. Asserts that if `model_` is not
  // null, then `pixels_` has size (at least)
  // `model_->width() * model_->height()`.
  void updatePixels();

signals:
  // Emit to update the model.
  void updateModel();

private:
  // Control flow.
  QTimer timer_;
  Gate gate_;

  // Data.
  std::map<int, Color> coloring_;
  std::vector<Color> pixels_{};
  std::shared_ptr<IModel> model_{};

  // Coordinates of the previously hovered cell. Equal to -1 if mouse is
  // not clicked.
  int xcell_ = -1;
  int ycell_ = -1;
};

} // namespace drautomaton

#endif /* DRAUTOMATON_SRC_VIEW_H */
