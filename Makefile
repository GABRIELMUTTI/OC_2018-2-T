COMPILER := gcc
COMPILER_FLAGS := -Wall -fdiagnostics-color
LINKER_FLAGS :=

SRC := src
BIN := bin
EXECUTABLE := main
INCLUDE := -Iinclude/

all: $(BIN)/$(EXECUTABLE)

clean:
	rm bin/*

run:
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c
	$(COMPILER) $(COMPILER_FLAGS) $(INCLUDE) $^ -o $@ $(LINKER_FLAGS)

