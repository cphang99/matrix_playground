CC=gcc
CFLAGS=-I$(INC_DIR) -std=c99 -Wall -Wextra
DEPS = 2D_matrix_ops.h 2D_matrix_arithmetic.h 2D_element_arithmetic.h
OBJ = 2D_matrix_ops.o
LIBS = -lm
BIN = ./bin
SRC_DIR = ./src
INC_DIR = ./include

MAKE_TARGETS = 2D_matrix_ops-tests

all: mkBin tests

mkBin:
	mkdir -p $(BIN)

tests: 2D_matrix_ops-tests 2D_matrix_arithmetic-tests 2D_element_arithmetic-tests

2D_matrix_arithmetic-tests: $(SRC_DIR)/2D_matrix_arithmetic-tests.o $(SRC_DIR)/2D_matrix_arithmetic.o $(SRC_DIR)/2D_element_arithmetic.o $(SRC_DIR)/$(OBJ)
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS) $(LIBS)

2D_element_arithmetic-tests: $(SRC_DIR)/2D_element_arithmetic-tests.o $(SRC_DIR)/2D_element_arithmetic.o $(SRC_DIR)/$(OBJ)
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS) $(LIBS)

2D_matrix_ops-tests: $(SRC_DIR)/2D_matrix_ops-tests.o $(SRC_DIR)/2D_element_arithmetic.o  $(SRC_DIR)/2D_matrix_ops.o
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS) $(LIBS)

$(SRC_DIR)/%.o: %.c $(INC_DIR)/$(DEPS)
	$(CC) -c $< $(CFLAGS)

.PHONY: all install clean

clean:
	rm -rf $(BIN) $(SRC_DIR)/*.o



