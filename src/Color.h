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

#ifndef DRAUTOMATON_SRC_COLOR_H
#define DRAUTOMATON_SRC_COLOR_H

#include <QColor>

namespace drautomaton {

/* Note. When initializing a Color using `auto x = qRgba(r, g, b, a)`,
 * the resulting 32-bit unsigned int has pixel format ARGB (most
 * significant byte holds alpha value, etc.). */
using Color = QRgb;

} // namespace drautomaton

#endif /* DRAUTOMATON_SRC_COLOR_H */
