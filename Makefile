CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c17 -Iinclude -Wno-newline-eof
LDFLAGS = 

ifeq ($(OS), Windows_NT)
	LDFLAGS += -static
endif

SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
INC_DIR = include

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
TARGET = $(BIN_DIR)/obsidian

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

DEP = $(OBJ:.o=.d)
-include $(DEP)

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MM $< -MF $@

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean