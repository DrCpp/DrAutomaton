<!--
Copyright 2020 Malte Kliemann, Ole Kliemann

This file is part of DrAutomaton.

DrAutomaton is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

DrAutomaton is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License along
with DrAutomaton.  If not, see <https://www.gnu.org/licenses/>.
-->

# Building DrAutomaton

## Requirements for building and using DrAutomaton

Build requirements and supported platforms are found in the [README.md](../README.md).

## Building

**DrAutomaton** may be configured manually, or using the delivered Makefiles.

### Using the Makefile

Set the environment variable `$DRAUTO_QT_PATH` to the location of the Qt library.
For example:
```
export DRAUTO_QT_PATH="$HOME/Qt/5.14.2/clang_64
```
Next, do `make`, then `make install` in the source directory.
This will install the **DrAutomaton** cmake package in `{SOURCE_DIR}/prefix`.
Move the contents of that folder wherever you please.
For example,
```
rsync -a prefix/ /usr/local
```

### Manually using CMake

If you do not wish to use the presupplied Makefile,
you can use CMake manually to install **DrAutomaton**:
```
cmake . -DCMAKE_PREFIX_PATH=/path/to/qt ... [-DCMAKE_INSTALL_PREFIX=...]
```

Then `make` and `make install`.
If you want to run the tests,
don't forget to add the location of DrMock to the `CMAKE_PREFIX_PATH`.

## Fetching dependencies

Some notes on fetching dependencies
(shamelessly taken from [DrMock](https://github.com/DrCpp/DrMock)).

### CMake

On some Linux systems, CMake 3.13 might not be available via the package
manager you're using (this seems to be the case with Ubuntu 18.04). It's
not difficult to build CMake from source, following
[https://cmake.org/install/ ](https://cmake.org/install/).

We've noticed that on a mint Ubuntu installation, the following error
will occur when doing `./bootstrap`: [CMake not able to find OpenSSL
library](https://stackoverflow.com/questions/16248775/cmake-not-able-to-find-openssl-library),
which we were able to solve by installing `openssl-dev`:
```
sudo apt-get install openssl-dev
```
(or similar for other package managers).

## Troubleshooting

### `libgl` missing

You might encounter the following error on Linux:
```
${DRMOCK_QT_PATH}/lib/cmake/Qt5Gui/Qt5GuiConfigExtras.cmake:9 (message):
  Failed to find "GL/gl.h" in "/usr/include/libdrm".
```
The solution is to install `libgl-dev`:
```
sudo apt-get install libgl-dev
```
(or similar for other package managers).

