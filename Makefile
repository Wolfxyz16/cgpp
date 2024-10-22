NAME := cgpp
STD := -std=c23
CFLAGS := -ftree-parallelize-loops=4 -O2 -march=native
CC := gcc
SRC := $(wildcard src/*.c)
OBJS := $(patsubst %.c, %.o, $(SRC))

BIN_DIR := bin
BUILD_DIR := build

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking..."
	$(CC) $(CFLAGS) $(STD) -o $(BIN_DIR)/cgpp $(OBJS)

clean:
	@echo "Cleaning ALL"
	rm build/$(OBJS)

