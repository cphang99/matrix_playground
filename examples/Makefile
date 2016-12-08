CC=gcc
CFLAGS = -std=c99 -Wall -Wextra
LIBS = -lmapla_$(TYPE) -lfixmath -lm
TYPE ?= FLOAT
BIN_DIR = ./bin

EX_NAMES = $(patsubst %.c, %, $(wildcard *.c))
OBJ = $(patsubst %.c, %.o, $(wildcard *.c))

mkDirs:
	mkdir -p $(BIN_DIR)

%.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS) -D$(TYPE)

$(EX_NAMES): $(OBJ) mkDirs
	$(CC) -o $(BIN_DIR)/$@ $@.o $(CFLAGS) $(LIBS) -D$(TYPE)

.PHONY: clean

clean:
	rm *.o
	rm -rf $(BIN_DIR)



