CC=gcc
CFLAGS=-I$(INC_DIR) -std=c99 -Wall -Wextra

OBJ_F = 2D_matrix_arithmetic 2D_element_arithmetic 2D_matrix_ops
OBJ = $(patsubst %, $(SRC_DIR)/%.o, $(OBJ_F))

LIBS = -lm
BIN = ./bin
SRC_DIR = ./src
INC_DIR = ./include
TEST_DIR = ./$(SRC_DIR)/tests

PRG_N = $(notdir $(patsubst %.c, %, $(wildcard $(TEST_DIR)/*.c)))
PRG_O = $(patsubst %, $(TEST_DIR)/%.o, $(PRG_N))

all: mkBin $(PRG_N)

mkBin:
	mkdir -p $(BIN)

$(PRG_N): $(OBJ) $(PRG_O)
	$(CC) -o $(BIN)/$@ $(TEST_DIR)/$@.o $(OBJ) $(CFLAGS) $(LIBS)

.PHONY: all install clean

clean:
	rm -rf $(BIN) $(SRC_DIR)/*.o $(TEST_DIR)/*.o



