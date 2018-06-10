# Author: Lucas David
# Date: 2018-04-13

rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

CC = gcc
CFLAGS = -g -std=c11 -Wall
EXEC = bin/snake-io
LIB = -lm -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_ttf

SRC_DIR = src/
OBJ_DIR = obj/
SRC = $(call rwildcard,$(SRC_DIR),*.c)
OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))
_OBJ_DIR = $(dir $(OBJ))

all: $(EXEC)
	mkdir -pv --mode=777 $(_OBJ_DIR)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIB)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: check clean cclean

check:
	echo $(OBJ)

clean:
	rm -rfv $(OBJ_DIR)*.o

cclean: clean
	rm -rfv $(EXEC)

