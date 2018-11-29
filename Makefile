COMPILER := gcc
COMPILER_FLAGS := -Wall -fdiagnostics-color -g
LINKER_FLAGS :=

SRC := src
BIN := bin
EXECUTABLE := main
INCLUDES := include
INCLUDE := -Iinclude/ -Iinclude/test

all: $(BIN)/$(EXECUTABLE)

clean:
	rm bin/*

run:
	./$(BIN)/$(EXECUTABLE) ${ARGS} /home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb02 /home/gabriel/Documents/ufrgs/courses/oc/trab/solutions/

$(BIN)/$(EXECUTABLE): $(SRC)/*.c $(SRC)/**/*.c $(INCLUDES)/*.h $(INCLUDES)/**/*.h
	$(COMPILER) $(COMPILER_FLAGS) $(INCLUDE) $^ -o $@ $(LINKER_FLAGS)
