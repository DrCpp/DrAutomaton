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

namespace drautomaton {

template<int N>
bool
CyclicState<N>::isSucceededBy(const CyclicState<N>& x) const
{
  auto m = (value + 1) % N;
  return (m == x.value);
}

template<int N>
CyclicState<N>::operator int() const
{
  return value;
}

template<int N>
CyclicState<N>
Cyclic<N>::transition(int x, int y, const Space<State>& space)
{
  auto state = space.cell(x, y);

  // Check if there is a cell in the Moore neighborhood of `(x, y)` that
  // the current state is succeeded by.
  for (int i = -1; i <=1; ++i)
  {
    for (int j = -1; j <= 1; ++j)
    {
      // Ignore center cell.
      if ((i == 0) and (j == 0))
      {
        continue;
      }

      // If the cell is found, return its state.
      auto neighbor = space.geometricCell(x + i, y + j);
      if (state.isSucceededBy(neighbor))
      {
        return neighbor;
      }
    }
  }

  // If no such cell is found, the state remains the same.
  return state;
}

template<int N>
CyclicState<N>
Cyclic<N>::increment(const State& state)
{
  CyclicState<N> x;
  x.value = (state.value + 1) % N;
  return x;
}

} // namespace drautomaton
