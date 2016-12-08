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

define MK_EXE
$(1): $(1).o mkDirs
	$(CC) -o $(BIN_DIR)/$(1) $(1).o $(CFLAGS) $(LIBS) -D$(TYPE)
endef
$(foreach ex, $(EX_NAMES), $(eval $(call MK_EXE,$(ex))))

.PHONY: clean

clean:
	rm *.o
	rm -rf $(BIN_DIR)



