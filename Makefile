CC=gcc
CFLAGS=-I. -std=c99 -Wall -Wextra
DEPS = 2D_matrix_ops.h
OBJ = 2D_matrix_ops.o
LIBS = -lm
BIN = ./bin

MAKE_TARGETS = 2D_matrix_ops

all: $(MAKE_TARGETS).o
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/$(MAKE_TARGETS) $^ $(CFLAGS) $(LIBS)

%.o: %.c $(DEPS)
	$(CC) -c $< $(CFLAGS)



