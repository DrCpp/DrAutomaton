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

#ifndef DRAUTOMATON_TESTS_VIEWTEST_MODELMOCK_H
#define DRAUTOMATON_TESTS_VIEWTEST_MODELMOCK_H

#include "IModel.h"

#include <QRect>

/* ModelMock

Unfortunately, DrMock can't configure mocked methods to emit signals
(yet!), so we're mocking `Model` manually. This mock sends a fixed test
image with some flashing pixels to test that the View/Renderer pair
works properly.

*/

namespace drautomaton { namespace mock {

class ModelMock final : public IModel
{
public:
  ModelMock();

  const std::vector<int>& vertices() const override;
  int width() const override;
  int height() const override;

public slots:
  void doUpdate() override;
  void onCellularUpdated() override;
  void setViewport(int, int, int, int) override;
  void increment(int, int) override;

private:
  int width_ = 16;
  int height_ = 12;
  std::vector<int> vertices_{};
  QRect viewport_;
};

}} // namespace drautomaton::mock

#endif /* DRAUTOMATON_TESTS_VIEWTEST_MODELMOCK_H */
