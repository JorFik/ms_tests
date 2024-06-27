RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code

LIB_DIR = ../lib
LIBFT_PATH = $(LIB_DIR)/libft
LDFLAGS = -L$(LIBFT_PATH) -lft

HEADERS_DIR = includes/ ../includes/ $(LIBFT_PATH)/includes/
INCLUDES = $(addprefix -I, $(HEADERS_DIR))
ifeq ($(DEBUG), 1)
re: fclean all
.PHONY: re
endif
all: exec_test exec_integration_test
.PHONY: all
################################################################################
# Source files
################################################################################
EXEC_TEST_DEPS = includes/test_exec.h

_EXEC_TEST_SRC = test_transform_to_array.c main.c test_token_utils.c\
	test_divide_tokens.c utils_test_divide_tokens.c test_exec_utils.c\
	test_redir.c
EXEC_TEST_SRC = $(addprefix src/exec/, $(_EXEC_TEST_SRC))

_EXEC_INTEGRATION_TEST_SRC = test_exec_integration.c
EXEC_INTEGRATION_TEST_SRC = $(addprefix src/, $(_EXEC_INTEGRATION_TEST_SRC))


################################################################################
# Creating binaries
################################################################################
EXEC_TEST_OBJ = $(EXEC_TEST_SRC:src/exec/%.c=bin/exec/%.o)
EXEC_INTEGRATION_TEST_OBJ = $(EXEC_INTEGRATION_TEST_SRC:src/%.c=bin/%.o)\
	$(filter-out bin/exec/main.o, $(EXEC_TEST_OBJ))

bin/exec:
	@mkdir -p bin/exec

bin/:
	@mkdir -p bin

bin/exec%.o : src/exec/%.c  $(EXEC_TEST_DEPS) | bin/exec
	@printf "%-100s\r" "	Compiling $@"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bin/%.o : src/%.c  $(EXEC_TEST_DEPS) | bin/
	@printf "%-100s\r" "	Compiling $@"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Tested binaries
_TESTED_EXEC_OBJ += exec.o token_utils.o pipe_utils.o exec_utils.o heredoc.o
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

exec_test: $(EXEC_TEST_OBJ) $(TESTED_OBJ_PATH) $(LIBFT_PATH)/libft.a
	@$(CC) -o $@ $(EXEC_TEST_OBJ) $(TESTED_OBJ_PATH) $(CFLAGS) $(INCLUDES) $(LDFLAGS)

exec_integration_test: $(EXEC_INTEGRATION_TEST_OBJ) $(TESTED_OBJ_PATH) $(LIBFT_PATH)/libft.a
	@$(CC) -o $@ $(EXEC_INTEGRATION_TEST_OBJ) $(TESTED_OBJ_PATH) $(CFLAGS) $(INCLUDES) $(LDFLAGS)

clean:
	@$(RM) bin/*
	@$(RM) ../bin/*
.PHONY: clean

fclean: clean
	@$(RM) exec_test
	@$(RM) exec_integration_test
.PHONY: fclean


################################################################################
# Debug
################################################################################
DEBUG ?= 0
ifeq ($(DEBUG), 1)
CFLAGS += -g3
DEBUG_FLAG= DEBUG=1
endif