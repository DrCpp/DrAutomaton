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

#ifndef DRAUTOMATON_SRC_MODEL_H
#define DRAUTOMATON_SRC_MODEL_H

#include <memory>
#include <vector>

#include <QRect>

#include "IModel.h"
#include "ICellular.h"

namespace drautomaton {

template<typename Rule>
class Model final : public IModel
{
public:
  Model(std::shared_ptr<ICellular<typename Rule::State>>);
  Model(int width, int height);

  const std::vector<int>& vertices() const override;
  int width() const override;
  int height() const override;

public slots:
  void doUpdate() override;
  void onCellularUpdated() override;
  void setViewport(int x, int y, int width, int height) override;
  void increment(int x, int y) override;

private:
  // Convert space to vertices.
  void updateVertices();

  std::shared_ptr<ICellular<typename Rule::State>> cellular_;
  std::vector<int> vertices_;

  QRect viewport_;
};

} // namespace drautomaton

#include "Model.tpp"

#endif /* DRAUTOMATON_SRC_MODEL_H */
