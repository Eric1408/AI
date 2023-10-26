# Nombre del compilador y flags
CC=g++
CFLAGS=-std=c++17 -Wall -Wextra -Iinclude
LDFLAGS=
EXECUTABLE=myProgram
RESU=resultados.txt

# Listado de archivos fuente y objetos
SRC_DIR=src
INCLUDE_DIR=include
BUILD_DIR=build

# Obtén la lista de archivos fuente y genera la lista de archivos objeto
SRCS=$(wildcard $(SRC_DIR)/*.cc)
OBJS=$(patsubst $(SRC_DIR)/%.cc,$(BUILD_DIR)/%.o,$(SRCS))

# Reglas de construcción
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -rf $(BUILD_DIR) $(EXECUTABLE) $(RESU)
	@echo "All cleaned!"

.PHONY: clean

