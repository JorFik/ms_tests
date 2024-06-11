RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code

LIB_DIR = ../lib
LIBFT_PATH = $(LIB_DIR)/libft
LDFLAGS = -L$(LIBFT_PATH) -lft

HEADERS_DIR = includes/ ../includes/ $(LIBFT_PATH)/includes/
INCLUDES = $(addprefix -I, $(HEADERS_DIR))
default_rule: all
.PHONY: default_rule
################################################################################
# Source files
################################################################################
EXEC_TEST_DEPS = includes/test_exec.h

_EXEC_TEST_SRC = test_transform_to_array.c main.c token_utils.c\
	test_divide_tokens.c utils_test_divide_tokens.c
EXEC_TEST_SRC = $(addprefix src/exec/, $(_EXEC_TEST_SRC))

_TESTED_EXEC_SRC = exec.c
TESTED_EXEC_SRC = $(addprefix ../src/exec/, $(_TESTED_EXEC_SRC))


################################################################################
# Creating binaries
################################################################################
EXEC_ARGV_TEST_OBJ = $(EXEC_TEST_SRC:src/exec/%.c=bin/exec/%.o)
TESTED_EXEC_OBJ = $(TESTED_EXEC_SRC:../src/exec/%.c=bin/exec/%.o)

bin/exec:
	@mkdir -p bin/exec

bin/exec%.o : src/exec/%.c | bin/exec
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bin/exec/%.o : ../src/exec/%.c | bin/exec
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


################################################################################
# Rules
################################################################################
all: e_argv_test
.PHONY: all

e_argv_test: $(EXEC_ARGV_TEST_OBJ) $(TESTED_EXEC_OBJ) $(EXEC_TEST_DEPS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(EXEC_ARGV_TEST_OBJ) $(TESTED_EXEC_OBJ) -o $@

clean:
	@$(RM) bin/*
.PHONY: clean

fclean: clean
	@$(RM) e_argv_test
.PHONY: fclean


################################################################################
# Debug
################################################################################
DEBUG ?= 0
ifeq ($(DEBUG), 1)
CFLAGS += -g3
endif