# Copyright © 2019, Amelia Coutard
#
# This file is part of Cafet.
#
# Cafet is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Cafet is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Cafet.  If not, see <https://www.gnu.org/licenses/>.

.PHONY: build build-and-run clean


OUT_DIR ?= out/
SRC_DIR ?= src/
DEPS_DIR ?= deps/
EXEC_NAME ?= cafet

C++ ?= g++
C++_OPTIONS ?= -O2
C++_OPTIONS := $(C++_OPTIONS) -std=c++2a -Wall -Wextra -Werror=return-type $(shell pkg-config gtkmm-3.0 --cflags)
C++ := $(C++) $(C++_OPTIONS)

LINKER ?= g++
LINKER_OPTIONS ?= -O2
LINKER_OPTIONS := $(LINKER_OPTIONS) -pthread $(shell pkg-config gtkmm-3.0 --libs)
LINKER := $(LINKER) $(LINKER_OPTIONS)

OBJECTS := $(patsubst $(SRC_DIR)%.cpp,$(OUT_DIR)%.o,$(wildcard $(SRC_DIR)*.cpp) $(wildcard $(SRC_DIR)*/*.cpp) $(wildcard $(SRC_DIR)*/*/*.cpp))

build: $(OUT_DIR)$(EXEC_NAME)

build-and-run: $(OUT_DIR)$(EXEC_NAME)
	./$(OUT_DIR)$(EXEC_NAME)

clean:
	find out -type f -delete
	find deps -type f -delete


$(OUT_DIR)$(EXEC_NAME): $(OBJECTS)
	$(LINKER) $+ $(LINKER_OPTIONS) -o $@

$(OUT_DIR)%.o: $(SRC_DIR)%.cpp
	mkdir -p $(dir $@)
	mkdir -p $(dir deps/$*.o)
	$(C++) -MMD -MF $(DEPS_DIR)$*.d -MT $@ -c $< -o $@


-include deps/*.d
