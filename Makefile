RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code

LIB_DIR = ../lib
LIBFT_PATH = $(LIB_DIR)/libft
LDFLAGS = -L$(LIBFT_PATH) -lft

HEADERS_DIR = includes/ ../includes/ $(LIBFT_PATH)/includes/
INCLUDES = $(addprefix -I, $(HEADERS_DIR))
all: exec_test
.PHONY: all
################################################################################
# Source files
################################################################################
EXEC_TEST_DEPS = includes/test_exec.h

_EXEC_TEST_SRC = test_transform_to_array.c main.c test_token_utils.c\
	test_divide_tokens.c utils_test_divide_tokens.c
EXEC_TEST_SRC = $(addprefix src/exec/, $(_EXEC_TEST_SRC))


################################################################################
# Creating binaries
################################################################################
EXEC_TEST_OBJ = $(EXEC_TEST_SRC:src/exec/%.c=bin/exec/%.o)

bin/exec:
	@mkdir -p bin/exec

bin/exec%.o : src/exec/%.c | bin/exec
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Tested binaries
_TESTED_EXEC_OBJ += exec.o token_utils.o pipe_utils.o
TESTED_EXEC_OBJ = $(addprefix exec/, $(_TESTED_EXEC_OBJ))

_TESTED_UTILS_OBJ = exit_error.o
TESTED_UTILS_OBJ = $(addprefix utils/, $(_TESTED_UTILS_OBJ))

_TESTED_PARSER_OBJ = parser_utils.o
TESTED_PARSER_OBJ = $(addprefix parser/, $(_TESTED_PARSER_OBJ))

_TESTED_OBJ = $(TESTED_EXEC_OBJ) $(TESTED_UTILS_OBJ) $(TESTED_PARSER_OBJ)
TESTED_OBJ = $(addprefix bin/, $(_TESTED_OBJ))
TESTED_OBJ_PATH += $(addprefix ../, $(TESTED_OBJ))

$(TESTED_OBJ_PATH):
	@$(MAKE) -C ../ $(DEBUG_FLAG) $(TESTED_OBJ) > /dev/null


################################################################################
# Rules
################################################################################

$(LIBFT_PATH)/libft.a:
	@$(MAKE) -C ../ $(subst ../,,$(LIBFT_PATH))/libft.a > /dev/null

exec_test: $(EXEC_TEST_OBJ) $(TESTED_OBJ_PATH) $(EXEC_TEST_DEPS) $(LIBFT_PATH)/libft.a
	@$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(EXEC_TEST_OBJ) $(TESTED_OBJ_PATH) -o $@

clean:
	@$(RM) bin/*
	@$(RM) ../bin/*
.PHONY: clean

fclean: clean
	@$(RM) exec_test
.PHONY: fclean

re: fclean all
.PHONY: re

################################################################################
# Debug
################################################################################
DEBUG ?= 0
ifeq ($(DEBUG), 1)
CFLAGS += -g3
DEBUG_FLAG= DEBUG=1
endif