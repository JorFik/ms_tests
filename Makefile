RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code

LIB_DIR = ../lib
LIBFT_PATH = $(LIB_DIR)/libft
LDFLAGS = -L$(LIBFT_PATH) -lft

HEADERS_DIR = includes/ ../includes/ $(LIBFT_PATH)/includes/
INCLUDES = $(addprefix -I, $(HEADERS_DIR))

################################################################################
# Source files
################################################################################
EXEC_TEST_DEPS = includes/test_exec.h
_EXEC_TEST_SRC = test_create_argv.c
EXEC_TEST_SRC = $(addprefix src/exec/, $(_EXEC_TEST_SRC))


################################################################################
# Creating binaries
################################################################################
OBJ_EXEC_ARGV_TEST = $(EXEC_TEST_SRC:src/exec/%.c=bin/exec/%.o)


################################################################################
# Rules
################################################################################
e_argv_test: $(OBJ_EXEC_ARGV_TEST) $(EXEC_TEST_DEPS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(OBJ_EXEC_ARGV_TEST) -o e_argv_test

bin/exec:
	@mkdir -p bin/exec

bin/exec%.o : src/exec/%.c | bin/exec
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) bin/*

fclean: clean
	@$(RM) e_argv_test


################################################################################
# Debug
################################################################################
DEBUG ?= 0
ifeq ($(DEBUG), 1)
CFLAGS += -g3
endif