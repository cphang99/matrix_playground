
#Compiler options and linking libraries
CC=gcc
AR=ar
AR_FLAGS=-cr
CFLAGS= $(patsubst %, -I%, $(INC_DIR)) \
	   -std=c99 -Wall -Wextra -pedantic -Wstrict-prototypes \
	   -Wmissing-prototypes -Wshadow -Wpointer-arith -Wcast-qual \
	   -Werror
LIBS = -L$(LIB_DIR) $(patsubst lib%,-l%, $(MAPLA_LIB)_$(TYPE) $(FIXED_LIB)) -lm

# Specification of library and test objects
# TEST_NAMES specifies the name of the generated test binaries
OBJ = $(patsubst %.c, %.o, $(wildcard $(SRC_DIR)/*.c))
OBJ_INT = $(patsubst %.o, %_INT.o, $(OBJ))
OBJ_FLOAT = $(patsubst %.o, %_FLOAT.o, $(OBJ))
OBJ_FIXED = $(patsubst %.o, %_FIXED.o, $(OBJ))

TEST_NAMES = $(notdir $(patsubst %.c, %, $(wildcard $(TEST_DIR)/*.c)))
TEST_OBJ = $(patsubst %, $(TEST_DIR)/%.o, $(TEST_NAMES))

MAPLA_LIB = libmapla
MAPLA_LIBS = $(patsubst %, $(MAPLA_LIB)_%, $(TYPES))
MAPLA_NAME = matrix_playground
FIXED_LIB = libfixmath
TYPE ?= INT
TYPES = INT FIXED FLOAT
LIB_NAME = $(MAPLA_LIB) $(FIXED_LIB)

# Location of various directories
BIN_DIR = ./bin
SRC_DIR = ./src
INC_DIR = ./include ./libfixmath
LIB_DIR = ./lib
TEST_DIR = ./$(SRC_DIR)/tests
PREFIX = /usr/local
DEST_LIB_DIR = $(PREFIX)/lib/
DEST_INC_DIR = $(PREFIX)/include/$(MAPLA_NAME)

#Make declarative commands
all: $(MAPLA_LIBS) mk_$(FIXED_LIB)

tests: $(TEST_NAMES) $(MAPLA_LIB)_$(TYPE) mk_$(FIXED_LIB)

mkDirs:
	mkdir -p $(BIN_DIR) $(LIB_DIR)

mk_$(FIXED_LIB):
	$(MAKE) -C ./$(FIXED_LIB)/$(FIXED_LIB)
	cp ./$(FIXED_LIB)/$(FIXED_LIB)/$(FIXED_LIB).a $(LIB_DIR)

%.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS) -D$(TYPE)

%_INT.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS) -DINT

%_FLOAT.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS) -DFLOAT

%_FIXED.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS) -DFIXED

$(MAPLA_LIB)_INT: $(OBJ_INT) mkDirs
	$(AR) $(AR_FLAGS) $(LIB_DIR)/$@.a $(OBJ_INT)

$(MAPLA_LIB)_FLOAT: $(OBJ_FLOAT) mkDirs
	$(AR) $(AR_FLAGS) $(LIB_DIR)/$@.a $(OBJ_FLOAT)

$(MAPLA_LIB)_FIXED: $(OBJ_FIXED) mkDirs
	$(AR) $(AR_FLAGS) $(LIB_DIR)/$@.a $(OBJ_FIXED)

$(TEST_NAMES): $(TEST_OBJ) $(MAPLA_LIB)_$(TYPE) mk_$(FIXED_LIB)
	$(CC) -o $(BIN_DIR)/$@ $(TEST_DIR)/$@.o $(CFLAGS) $(LIBS)

.PHONY: all install uninstall clean tests

clean:
	rm -rf $(BIN_DIR) $(LIB_DIR) $(SRC_DIR)/*.o $(TEST_DIR)/*.o
	$(MAKE) -C ./$(FIXED_LIB)/$(FIXED_LIB) clean

install: $(LIB_DIR)/$(MAPLA_LIB)*.a $(LIB_DIR)/$(FIXED_LIB)*.a
	mkdir -p $(DEST_INC_DIR)
	cp $(LIB_DIR)/$(MAPLA_LIB)*.a $(DEST_LIB_DIR)
	cp $(LIB_DIR)/$(FIXED_LIB).a $(DEST_LIB_DIR)
	cp include/*.h $(DEST_INC_DIR)
	cp -ar $(FIXED_LIB) $(DEST_INC_DIR)
	cp $(MAPLA_NAME).h $(PREFIX)/include
	@echo "Libraries installed in $(DEST_LIB_DIR) and headers in $(DEST_INC_DIR)"

uninstall:
	- rm -r $(DEST_INC_DIR)
	- rm $(PREFIX)/include/$(MAPLA_NAME).h
	- rm $(DEST_LIB_DIR)/$(MAPLA_LIB)*
	- rm $(DEST_LIB_DIR)/$(FIXED_LIB).a
	@echo "Libraries uninstalled from $(DEST_LIB_DIR) and headers in $(DEST_INC_DIR)"
