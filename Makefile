COMPILER := gcc
COMPILER_FLAGS := -Wall -fdiagnostics-color -g
LINKER_FLAGS :=

SRC := src
BIN := bin
EXECUTABLE := main
INCLUDES := include
INCLUDE := -Iinclude/

all: $(BIN)/$(EXECUTABLE)

clean:
	rm bin/*

run:
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c $(INCLUDES)/*.h
	$(COMPILER) $(COMPILER_FLAGS) $(INCLUDE) $^ -o $@ $(LINKER_FLAGS)

