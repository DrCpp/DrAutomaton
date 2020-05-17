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

#ifndef DRAUTOMATON_SRC_CELLULAR_H
#define DRAUTOMATON_SRC_CELLULAR_H

#include "AbstractGeometry.h"
#include "Space.h"
#include "ICellular.h"

namespace drautomaton {

/* Cellular
 
Cellular automaton class template. For interface documentation, see
`ICellular.h`.

*** Implementation details ***

* The CA is implemented using two `Space` objects. he _underlying space_
  is returned by `space()`, The _temporary space_ `tmp_` is used for
  interior computation only.

* The CA holds an `AbstractGeometry` which serves as the geometry of
  _both_ `Space` objects. 
*/

template<typename Rule>
class Cellular : public ICellular<typename Rule::State>
{
public:
  Cellular(int width, int height);

  const Space<typename Rule::State>& space() const override;
  Space<typename Rule::State>& space() override;

public slots:
  void doUpdate() override;
  void increment(int, int) override;

  void setGeometry(std::shared_ptr<AbstractGeometry<typename Rule::State>> geometry);

private:
  void processBlock(
      const Space<typename Rule::State>&,
      Space<typename Rule::State>&,
      int,
      int,
      std::function<void(int, int, typename Rule::State&)>
    );

  std::vector<std::tuple<int, int>> blocks_{};
  Space<typename Rule::State> space_;
  Space<typename Rule::State> tmp_;
  std::shared_ptr<AbstractGeometry<typename Rule::State>> geometry_{};
  Rule rule_;
};

} // namespace drautomaton

#include "Cellular.tpp"

#endif /* DRAUTOMATON_SRC_CELLULAR_H */
