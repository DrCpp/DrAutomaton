# Discover operating system.
uname := $(shell uname -s)

# Get number of threads.
ifeq ($(uname), Darwin)
	num_threads := $(shell sysctl -n hw.activecpu)
else  # Assuming Linux.
  num_threads := $(shell nproc)
endif

.PHONY: default
default:
	mkdir -p build && cd build && cmake .. -DCMAKE_PREFIX_PATH="../../prefix;${DRAUTO_QT_PATH}"
	mkdir -p build && cd build && make -j$(num_threads) && ctest --output-on-failure
	./build/brain

.PHONY: clean
clean:
	rm -fr build
