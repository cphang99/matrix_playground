
#Compiler options and linking libraries
CC=gcc
AR=ar
AR_FLAGS=-cr
CFLAGS= $(INC_DIR) -std=c99 -Wall -Wextra -pedantic -Wstrict-prototypes \
	   -Wmissing-prototypes -Wshadow -Wpointer-arith -Wcast-qual \
	   $(patsubst %, -D%, $(TYPE))
LIBS = -lm -L$(LIB_DIR) $(patsubst lib%,-l%, $(LIB_NAME))

# Specification of library and test objects
# TEST_NAMES specifies the name of the generated test binaries
OBJ = $(patsubst %.c, %.o, $(wildcard $(SRC_DIR)/*.c))

TEST_NAMES = $(notdir $(patsubst %.c, %, $(wildcard $(TEST_DIR)/*.c)))
TEST_OBJ = $(patsubst %, $(TEST_DIR)/%.o, $(TEST_NAMES))

MAPLA_LIB = libmapla
FIXED_LIB = libfixmath
LIB_NAME = $(MAPLA_LIB) $(FIXED_LIB)

# Location of various directories
BIN_DIR = ./bin
SRC_DIR = ./src
INC_DIR = -I./include -I./libfixmath
LIB_DIR = ./lib
TEST_DIR = ./$(SRC_DIR)/tests

#Make declarative commands
all: $(TEST_NAMES)

mkDirs:
	mkdir -p $(BIN_DIR) $(LIB_DIR)

mk_$(FIXED_LIB):
	$(MAKE) -C ./$(FIXED_LIB)/$(FIXED_LIB)
	cp ./$(FIXED_LIB)/$(FIXED_LIB)/$(FIXED_LIB).a $(LIB_DIR)

$(MAPLA_LIB): mkDirs $(OBJ)
	$(AR) $(AR_FLAGS) $(LIB_DIR)/$(MAPLA_LIB).a $(OBJ)

$(TEST_NAMES): $(TEST_OBJ) $(MAPLA_LIB) mk_$(FIXED_LIB)
	$(CC) -o $(BIN_DIR)/$@ $(TEST_DIR)/$@.o $(CFLAGS) $(LIBS)

.PHONY: all install clean

clean:
	rm -rf $(BIN_DIR) $(LIB_DIR) $(SRC_DIR)/*.o $(TEST_DIR)/*.o
	$(MAKE) -C ./$(FIXED_LIB)/$(FIXED_LIB) clean



