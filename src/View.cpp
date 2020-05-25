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

#include "View.h"

#include <cmath>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QSGSimpleTextureNode>

#include "detail/Profiling.h"
#include "Model.h"

namespace drautomaton {

View::View()
{
  // Observe windowChanged() in order to expose window()->frameSwapped().
  QObject::connect(
      this, &QQuickItem::windowChanged,
      this, &View::onWindowChanged
    );

  // Make update() schedule updatePaintNode(...).
  setFlag(ItemHasContents, true);

  // Setup timer.
  QObject::connect(
      &timer_, &QTimer::timeout,
      &gate_, &Gate::lhs
    );

  // Default framerate value.
  setFramerate(1);
}

QSGNode*
View::updatePaintNode(QSGNode* old, UpdatePaintNodeData*)
{
  DRPROF_START("View::rendering");
  DRPROF_START("View::updatePaintNode");
  assert(model_);

  auto openGL = QOpenGLContext::currentContext()->functions();
  auto node = static_cast<QSGSimpleTextureNode*>(old);

  // Initialize texture on the first call.
  if (not node)
  {
    node = new QSGSimpleTextureNode{};
    node->setRect(boundingRect());

    // Create an empty texture whose size is that of the model.
    auto texture = window()->createTextureFromImage(
        QPixmap(model_->width(), model_->height()).toImage()
      );
    texture->bind();

    // The magnification filter will be used to magnify each texel
    // (cell). When doing so, we don't want sharp edges, so we're using
    // GL_NEAREST instead of GL_LINEAR.
    openGL->glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_NEAREST
      );

    node->setTexture(texture);
  }

  // Update the texture.
  auto texture = node->texture();
  texture->bind();
  openGL->glTexSubImage2D(
      GL_TEXTURE_2D,
      0, 0, 0,
      model_->width(), model_->height(),
      GL_BGRA,
      GL_UNSIGNED_INT_8_8_8_8_REV,  // REV to convert Qt's ARGB to BGRA.
      pixels_.data()
    );  // Note: We're using TexSubImage2D instead of TexImage2D, as the
        // former updates the texture while the latter recreates it.
  node->markDirty(QSGNode::DirtyGeometry);
  DRPROF_STOP("View::updatePaintNode");

  return node;
}

void
View::start()
{
  timer_.start();
}

void
View::stop()
{
  timer_.stop();
}

void
View::toggle()
{
  if (timer_.isActive())
  {
    timer_.stop();
  }
  else
  {
    timer_.start();
  }
}

void
View::showNextGeneration()
{
  assert(model_);
  emit updateModel();
  gate_.ready();  // Inform gate to let this update pass.
}

void
View::onClicked(qreal x, qreal y)
{
  assert(model_);

  // Ignore out-of-bounds coordinates.
  if (x >= width() or x < 0 or y >= height() or y < 0)
  {
    return;
  }

  // Get relative coordinates.
  float u = x / width();
  float v = y / height();

  // Get cell coords.
  int xcell = model_->width()  * u;
  int ycell = model_->height() * v;

  // Ignore if current cell is previous cell.
  if (xcell == xcell_ and ycell == ycell_)
  {
    return;
  }

  // Save new coords.
  xcell_ = xcell;
  ycell_ = ycell;

  model_->increment(xcell, ycell);
}

void
View::onWindowChanged(QQuickWindow* window)
{
  // If the window was disconnected, don't act. (We expect the previous
  // window to be destroyed and the connection to be lost.)
  if (not window)
  {
    return;
  }

  // We catch the frameSwapped signal to know when rendering is done.
  QObject::connect(
      window, &QQuickWindow::frameSwapped,
      &gate_, &Gate::rhs
    );
}

void
View::updatePixels()
{
  DRPROF_START("View::updatePixels");

  // If no model is available, ignore the call.
  if (!model_)
  {
    DRPROF_STOP("View::updatePixels");
    return;
  }

  // Compute vertex colors.
  std::transform(
      model_->vertices().begin(),
      model_->vertices().end(),
      pixels_.begin(),
      [&](int x) { return coloring_[x]; }
    );

  DRPROF_STOP("View::updatePixels");

  // Load pixels.
  update();
}

void
View::setModel(std::shared_ptr<IModel> model)
{
  // Disconnect previous model.
  if (model_)
  {
    QObject::disconnect(
        &gate_, &Gate::ready,
        model_.get(), &IModel::doUpdate
      );
    QObject::disconnect(
        model_.get(), &IModel::updated,
        this, &View::updatePixels
      );
  }

  // Save and connect the new model.
  model_ = std::move(model);
  QObject::connect(
      &gate_, &Gate::ready,
      model_.get(), &IModel::doUpdate
    );
  QObject::connect(
      model_.get(), &IModel::updated,
      this, &View::updatePixels
    );

  // Resize the pixel array accordingly, and update the pixel array.
  pixels_.resize(model_->width() * model_->height());
  // updatePixels();
}

void
View::setFramerate(int fps)
{
  int frame_duration = std::floor(1000.0f / fps);
  timer_.setInterval(frame_duration);
}

void
View::setColor(int vertex, int r, int g, int b)
{
  coloring_[vertex] = qRgb(r, g, b);
  updatePixels();
}

void
View::setColor(int vertex, QColor color)
{
  setColor(vertex, color.red(), color.green(), color.blue());
}

} // namespace drautomaton
