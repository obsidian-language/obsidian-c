CC      = gcc
AR      = ar rc
RANLIB  = ranlib
RM      = rm -rf
MKDIR   = mkdir -p

SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
INC_DIR = src/include

MYCFLAGS  = -std=c17 -O2 -march=native
MYLDFLAGS = -Wl,-E
MYLIBS    = -ldl

CWARNSCPP = \
    -Wfatal-errors \
    -Wextra \
    -Wshadow \
    -Wundef \
    -Wwrite-strings \
    -Wredundant-decls \
    -Wdisabled-optimization \
    -Wdouble-promotion \
    -Wmissing-declarations \
    -Wconversion \
    -Wstrict-overflow=2

CWARNGCC = \
    -Wlogical-op \
    -Wno-aggressive-loop-optimizations

CWARNSC = \
    -Wdeclaration-after-statement \
    -Wmissing-prototypes \
    -Wnested-externs \
    -Wstrict-prototypes \
    -Wc++-compat \
    -Wold-style-definition

CWARNS = $(CWARNSCPP) $(CWARNSC) $(CWARNGCC)

CPPFLAGS = -I$(INC_DIR) $(CWARNS)
CFLAGS   = $(MYCFLAGS) -Wall -fno-stack-protector -fno-common
LDFLAGS  = $(MYLDFLAGS)

ifeq ($(OS), Windows_NT)
    LDFLAGS += -static
endif

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
DEP = $(OBJ:.o=.d)

TARGET = $(BIN_DIR)/obsidian

all: $(TARGET)

$(TARGET): $(OBJ)
	@$(MKDIR) $(BIN_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(MYLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

-include $(DEP)

clean:
	$(RM) $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
