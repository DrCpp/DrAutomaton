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

#ifndef DRAUTOMATON_SRC_DETAIL_UTILITY_H
#define DRAUTOMATON_SRC_DETAIL_UTILITY_H

namespace drautomaton { namespace detail {

// Return x (mod) y. Example: `mod(-1, 10)` equals `9`.
int mod(int x, int y);

}} // namespace drautomaton::detail

#endif /* DRAUTOMATON_SRC_DETAIL_UTILITY_H */
