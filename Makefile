CC=gcc
CFLAGS=-I$(INC_DIR) -std=c99 -Wall -Wextra

OBJ_F = 2D_matrix_arithmetic 2D_element_arithmetic 2D_matrix_ops
OBJ = $(patsubst %, $(SRC_DIR)/%.o, $(OBJ_F))

LIBS = -lm
BIN = ./bin
SRC_DIR = ./src
INC_DIR = ./include

all: mkBin tests

mkBin:
	mkdir -p $(BIN)

tests:  2D_matrix_ops-tests \
        2D_matrix_arithmetic-tests \
	2D_element_arithmetic-tests

2D_matrix_arithmetic-tests: $(SRC_DIR)/2D_matrix_arithmetic-tests.o $(OBJ)
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS) $(LIBS)

2D_element_arithmetic-tests: $(SRC_DIR)/2D_element_arithmetic-tests.o  $(OBJ)
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS) $(LIBS)

2D_matrix_ops-tests: $(SRC_DIR)/2D_matrix_ops-tests.o $(OBJ)
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: all install clean

clean:
	rm -rf $(BIN) $(SRC_DIR)/*.o



