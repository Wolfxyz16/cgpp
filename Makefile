NAME := cgpp
CFLAGS := -ftree-parallelize-loops=4 -O2 -march=native -std=c23
CC := gcc
SRC := $(wildcard src/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

SRC_DIR := src
BIN_DIR := bin
BUILD_DIR := build

all: $(BIN_DIR) $(NAME)

$(NAME): $(OBJS)
	@echo "Linking..."
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN_DIR)/cgpp

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning ALL"
	rm $(BUILD_DIR)/*

