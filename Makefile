
#Compiler options and linking libraries
CC=gcc
CFLAGS=-I$(INC_DIR) -std=c99 -Wall -Wextra
AR=ar
AR_FLAGS=-cr
LIBS = -lm -L$(LIB_DIR) -l$(patsubst lib%,%, $(LIB_NAME))

# Specification of library and test objects
# TEST_NAMES specifies the name of the generated test binaries
OBJ = $(patsubst %.c, %.o, $(wildcard $(SRC_DIR)/*.c))

TEST_NAMES = $(notdir $(patsubst %.c, %, $(wildcard $(TEST_DIR)/*.c)))
TEST_OBJ = $(patsubst %, $(TEST_DIR)/%.o, $(TEST_NAMES))

LIB_NAME = libmapla

# Location of various directories
BIN_DIR = ./bin
SRC_DIR = ./src
INC_DIR = ./include
LIB_DIR = ./lib
TEST_DIR = ./$(SRC_DIR)/tests

#Make declarative commands
all: mkDirs $(TEST_NAMES)

mkDirs:
	mkdir -p $(BIN_DIR) $(LIB_DIR)

mk_matrix_lib: mkDirs $(OBJ)
	$(AR) $(AR_FLAGS) $(LIB_DIR)/$(LIB_NAME).a $(OBJ)

$(TEST_NAMES): $(TEST_OBJ) mk_matrix_lib
	$(CC) -o $(BIN_DIR)/$@ $(TEST_DIR)/$@.o $(CFLAGS) $(LIBS)

.PHONY: all install clean

clean:
	rm -rf $(BIN_DIR) $(LIB_DIR) $(SRC_DIR)/*.o $(TEST_DIR)/*.o



