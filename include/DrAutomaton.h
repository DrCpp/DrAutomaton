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

#include "geometry/Border.h"
#include "geometry/Projective.h"
#include "geometry/Torus.h"
#include "geometry/WrapX.h"
#include "geometry/WrapY.h"
#include "rules/Brain.h"
#include "rules/Cyclic.h"
#include "rules/GameOfLife.h"
#include "rules/SRLoop.h"
#include "AbstractGeometry.h"
#include "Cellular.h"
#include "Model.h"
#include "Space.h"
#include "View.h"
