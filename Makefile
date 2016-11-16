
#Compiler options and linking libraries
CC=gcc
CFLAGS=-I$(INC_DIR) -std=c99 -Wall -Wextra
LIBS = -lm

# Specification of library and test objects
# TEST_NAMES specifies the name of the generated test binaries
OBJ = $(patsubst %.c, %.o, $(wildcard $(SRC_DIR)/*.c))

TEST_NAMES = $(notdir $(patsubst %.c, %, $(wildcard $(TEST_DIR)/*.c)))
TEST_OBJ = $(patsubst %, $(TEST_DIR)/%.o, $(TEST_NAMES))

# Location of various directories
BIN_DIR = ./bin
SRC_DIR = ./src
INC_DIR = ./include
TEST_DIR = ./$(SRC_DIR)/tests

#Make declarative commands
all: mkBin $(TEST_NAMES)

mkBin:
	mkdir -p $(BIN_DIR)

$(TEST_NAMES): $(OBJ) $(TEST_OBJ)
	$(CC) -o $(BIN_DIR)/$@ $(TEST_DIR)/$@.o $(OBJ) $(CFLAGS) $(LIBS)

.PHONY: all install clean

clean:
	rm -rf $(BIN_DIR) $(SRC_DIR)/*.o $(TEST_DIR)/*.o



