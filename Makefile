CC=gcc
CFLAGS=-I$(INC_DIR) -std=c99 -Wall -Wextra
DEPS = 2D_matrix_ops.h
OBJ = 2D_matrix_ops.o
LIBS = -lm
BIN = ./bin
SRC_DIR = ./src
INC_DIR = ./include

MAKE_TARGETS = 2D_matrix_ops-tests

all: $(SRC_DIR)/$(MAKE_TARGETS).o $(SRC_DIR)/$(OBJ)
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/$(MAKE_TARGETS) $^ $(CFLAGS) $(LIBS)

$(SRC_DIR)/%.o: %.c $(INC_DIR)/$(DEPS)
	$(CC) -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf $(BIN) $(SRC_DIR)/*.o



